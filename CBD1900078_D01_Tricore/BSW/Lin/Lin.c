/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Lin.c
 *        \brief  AUTOSAR LIN Driver
 *
 *      \details  Core part of AUTOSAR LIN Driver
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#define LIN_SOURCE
/**********************************************************************************************************************
 *  MISRA
 *********************************************************************************************************************/
/* Disable the following MISRA warnings because they would appear too often for individual suppression.
   See justification at the end of file */




/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Lin.h"
#include "EcuM_Cbk.h"
#include "LinIf_Cbk.h"

#if ( LIN_DEV_ERROR_REPORT == STD_ON )
# include "Det.h"
#endif

#if ( LIN_E_TIMEOUT_TYPE_DET == STD_OFF )
# include "Dem.h"
#endif

#if ( LIN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON )
# include "Rtm.h"
#endif

#if ( LIN_USE_ECUM_BSW_ERROR_HOOK == STD_ON )
# include "EcuM_Error.h"
#endif


/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
#if ( LIN_SW_MAJOR_VERSION != 14 )
# error "Source and Header are inconsistent (LIN_SW_MAJOR_VERSION)!"
#endif
#if ( LIN_SW_MINOR_VERSION != 1 )
# error "Source and Header are inconsistent (LIN_SW_MINOR_VERSION)!"
#endif
#if ( LIN_SW_PATCH_VERSION != 1 )
# error "Source and Header are inconsistent (LIN_SW_PATCH_VERSION)!"
#endif


/**********************************************************************************************************************
 *  CONFIGURATION CHECK
 **********************************************************************************************************************/
#if   ( LIN_CONFIGURATION_VARIANT != LIN_CONFIGURATION_VARIANT_PRECOMPILE ) && \
      ( LIN_CONFIGURATION_VARIANT != LIN_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
# error "LIN_CONFIGURATION_VARIANT not in valid range, check settings in generation tool!"
#endif


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/
/* States of channel LIN state machine */
#define LIN_STATE_SLEEP             0U /*!< Wake-up detection from slave nodes is enabled */
#define LIN_STATE_SLEEP_PENDING     1U /*!< Go-to-sleep-command is on the bus */
#define LIN_STATE_WAKEUP_EXTERNAL   2U /*!< A external wake-up request from a slave node was detected */
#define LIN_STATE_RX_BUSY           3U /*!< A LIN Frame with a response generated from a remote slave node is on the bus */
#define LIN_STATE_WAKEUP_PENDING    4U /*!< A wake-up request from this master node is on the bus */
#define LIN_STATE_S2S_BUSY          5U /*!< A LIN Frame with a response generated from one slave to another slave is on the bus */
#define LIN_STATE_TX_BUSY           6U /*!< A LIN Frame with a response generated from this master node is on the bus */
#define LIN_STATE_RX_ERROR          7U /*!< A error in the response generated from a remote slave node was erroneous */
#define LIN_STATE_RX_NO_RESPONSE    8U /*!< No response generated from a remote slave node */
#define LIN_STATE_RX_OK             9U /*!< A LIN Frame with a response generated from a remote slave node was succesful */
#define LIN_STATE_TX_ERROR         10U /*!< A error in the response generated from this master node was erroneous */
#define LIN_STATE_TX_HEADER_ERROR  11U /*!< A error in the LIN Frame header */
#define LIN_STATE_TX_OK            12U /*!< A LIN Frame with a response generated from this master node was succesful */
#define LIN_STATE_WAKE             13U /*!< Inital state and wake-up request from this master node is done */
#define LIN_MAX_STATES             14U /*!< State counter for mapping array of LIN state to Lin_StatusType */


/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/
/* Get and set state of LIN state machine */
/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#define Lin_GetState( ChannelConfigIdx )       (Lin_GetInternalStateOfChannelData(ChannelConfigIdx))
#define Lin_SetState( ChannelConfigIdx, state ) Lin_SetInternalStateOfChannelData(ChannelConfigIdx,state)

/* Get the current Lin_StatusType */
/* PRQA S 3453 1 */ /* MD_MSR_FctLikeMacro */
#define Lin_GetLinStatus( ChannelConfigIdx )   (Lin_StatusOfState[Lin_GetInternalStateOfChannelData( ChannelConfigIdx )])

/* DET Report Handling */
/* PRQA S 3453 1 */ /* MD_MSR_FctLikeMacro */
#define Lin_Det_ReportError( ApiId, ErrorCode) (Det_ReportError(LIN_MODULE_ID, 0, (ApiId), (ErrorCode)))

/* RTM Support */
#if ( LIN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON )
  /* PRQA S 3453, 342 2 */ /* MD_MSR_FctLikeMacro, MD_MSR_Rule20.10_0342 */
# define Lin_Rtm_Start(RtmMeasurementPoint_id)  Rtm_Start( RtmConf_RtmMeasurementPoint_##RtmMeasurementPoint_id )
# define Lin_Rtm_Stop(RtmMeasurementPoint_id)   Rtm_Stop( RtmConf_RtmMeasurementPoint_##RtmMeasurementPoint_id )
#else
# define Lin_Rtm_Start(RtmMeasurementPoint_id)
# define Lin_Rtm_Stop(RtmMeasurementPoint_id)
#endif


/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/
/* Define if not already defined */
#if !defined (LIN_LOCAL) /* COV_LIN_COMPATIBILITY */
# define LIN_LOCAL static
#endif

#if !defined (LIN_LOCAL_INLINE) /* COV_LIN_COMPATIBILITY */
# define LIN_LOCAL_INLINE LOCAL_INLINE
#endif


/***********************************************************************************************************************
 *  Include Frame Processor Interface and Implementation (inc)
 **********************************************************************************************************************/
#include "Lin_Fp.h"
#include "Lin_Fp.inc"


/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/
#if (LIN_USE_INIT_POINTER == STD_ON)

# define LIN_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Pointer to Global Configuration */
P2CONST(Lin_ConfigType, LIN_VAR_NOINIT, LIN_PBCFG) Lin_ConfigDataPtr;

# define LIN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif

#if ( LIN_DEV_ERROR_DETECT == STD_ON )
# define LIN_DEV_UNINITVALUE                              ((uint8)0x00U)
# define LIN_DEV_INITVALUE                                ((uint8)0xA5U)

# define LIN_START_SEC_VAR_ZERO_INIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Variable Lin_Dev_InitDetect must be initialized after reset for working debug check */
LIN_LOCAL VAR(uint8, LIN_VAR_ZERO_INIT) Lin_Dev_InitDetect = LIN_DEV_UNINITVALUE;
# define LIN_STOP_SEC_VAR_ZERO_INIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif


/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/
#define LIN_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Mapping table of LIN state to ASR Lin_StatusType */
LIN_LOCAL CONST(Lin_StatusType, AUTOMATIC) Lin_StatusOfState[LIN_MAX_STATES] = {
  /* LIN_STATE_SLEEP           */     LIN_CH_SLEEP        ,
  /* LIN_STATE_SLEEP_PENDING   */     LIN_CH_SLEEP        ,
  /* LIN_STATE_WAKEUP_EXTERNAL */     LIN_CH_SLEEP        ,
  /* LIN_STATE_RX_BUSY         */     LIN_RX_BUSY         ,
  /* LIN_STATE_WAKEUP_PENDING  */     LIN_OPERATIONAL     ,
  /* LIN_STATE_S2S_BUSY        */     LIN_TX_BUSY         ,
  /* LIN_STATE_TX_BUSY         */     LIN_TX_BUSY         ,
  /* LIN_STATE_RX_ERROR        */     LIN_RX_ERROR        ,
  /* LIN_STATE_RX_NO_RESPONSE  */     LIN_RX_NO_RESPONSE  ,
  /* LIN_STATE_RX_OK           */     LIN_RX_OK           ,
  /* LIN_STATE_TX_ERROR        */     LIN_TX_ERROR        ,
  /* LIN_STATE_TX_HEADER_ERROR */     LIN_TX_HEADER_ERROR ,
  /* LIN_STATE_TX_OK           */     LIN_TX_OK           ,
  /* LIN_STATE_WAKE            */     LIN_OPERATIONAL     };

#define LIN_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Internal Functions Implementation
 *********************************************************************************************************************/
#define LIN_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Lin_GetTxBusyStatus
 *********************************************************************************************************************/
/*! \brief       Handle the frame processor state for Tx busy state
 *  \details     Handles the subordinate switch case for the Tx busy state.
 *  \param[in]   ChannelConfigIdx: Access to all Channel data (register, data, ...)
 *  \param[in]   FpStatus: The state of the frame processor
 *  \pre         Internal function. Do not call.
 *  \context     TASK
 *  \reentrant   TRUE for different LIN channels
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_GetTxBusyStatus( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx,
                                                                             uint8 FpStatus );

/**********************************************************************************************************************
 *  Lin_GetRxBusyStatus
 *********************************************************************************************************************/
/*! \brief       Handle the frame processor state for Rx busy state
 *  \details     Handles the subordinate switch case for the Rx busy state.
 *  \param[in]   ChannelConfigIdx: Access to all Channel data (register, data, ...)
 *  \param[in]   FpStatus: The state of the frame processor
 *  \param[out]  SduPtr: Pointer to pointer to shadow buffer or memory mapped LIN Hardware receive buffer.
 *  \pre         Internal function. Do not call.
 *  \context     TASK
 *  \reentrant   TRUE for different LIN channels
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_GetRxBusyStatus( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx,
                                                                             uint8 FpStatus,
                                                                             P2VAR(Lin_u8PtrType, AUTOMATIC, LIN_APPL_VAR) SduPtr);

/**********************************************************************************************************************
 *  Lin_GetS2SBusyStatus
 *********************************************************************************************************************/
/*! \brief       Handle the frame processor state for S2S busy state
 *  \details     Handles the subordinate switch case for the S2S busy state.
 *  \param[in]   ChannelConfigIdx: Access to all Channel data (register, data, ...)
 *  \param[in]   FpStatus: The state of the frame processor
 *  \pre         Internal function. Do not call.
 *  \context     TASK
 *  \reentrant   TRUE for different LIN channels
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_GetS2SBusyStatus( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx,
                                                                             uint8 FpStatus );

/**********************************************************************************************************************
 *  Lin_GetTxBusyStatus
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_GetTxBusyStatus( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx,
                                                                             uint8 FpStatus )
{
  /* Check frame processor status */
  switch( FpStatus )
  {
    /* If frame processor status LIN_FP_STATUS_SUCCESSFUL, execute transition to LIN_STATE_TX_OK */
    case LIN_FP_STATUS_SUCCESSFUL:
      /* Set state to LIN_STATE_TX_OK */
      Lin_SetState( ChannelConfigIdx, LIN_STATE_TX_OK ); /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
      break;

    /* If frame processor status LIN_FP_STATUS_NO_RESPONSE of LIN_FP_STATUS_ERROR, execute transition to
       LIN_STATE_TX_ERROR */
    case LIN_FP_STATUS_NO_RESPONSE: /* COV_LIN_DEFENSIVE_PROGRAMMING */
    case LIN_FP_STATUS_ERROR:
      /* Set state to LIN_STATE_TX_ERROR */
      Lin_SetState( ChannelConfigIdx, LIN_STATE_TX_ERROR ); /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
      break;

    /* If frame processor status LIN_FP_STATUS_HEADERERROR, execute transition to LIN_STATE_TX_HEADER_ERROR */
    case LIN_FP_STATUS_HEADERERROR:
      /* Set state to LIN_STATE_TX_HEADER_ERROR */
      Lin_SetState( ChannelConfigIdx, LIN_STATE_TX_HEADER_ERROR ); /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
      break;

    /* If frame processor status LIN_FP_EMPTY, execute no transition */
    default:
      /* no transition, stay in current state */
      break;
  }
}

/**********************************************************************************************************************
 *  Lin_GetRxBusyStatus
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_GetRxBusyStatus( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx,
                                                                             uint8 FpStatus,
                                                                             P2VAR(Lin_u8PtrType, AUTOMATIC, LIN_APPL_VAR) SduPtr)
{
  VAR(boolean, AUTOMATIC) noResponseBytes;
  VAR(boolean, AUTOMATIC) rxByteNotStarted;

  /* Check frame processor status */
  switch( FpStatus )
  {
    /* If frame processor status LIN_FP_STATUS_SUCCESSFUL, execute transition to LIN_STATE_RX_OK */
    case LIN_FP_STATUS_SUCCESSFUL:
      /* Set state to LIN_STATE_RX_OK, save received data in buffer */
      Lin_SetState( ChannelConfigIdx, LIN_STATE_RX_OK ); /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
      Lin_Fp_SaveRxData( ChannelConfigIdx );

      /* Set a pointer of the buffer to the out parameter */
      *SduPtr = Lin_Fp_GetReceiveBufferPointer( ChannelConfigIdx ); /* SBSW_LIN_PTR */
      break;

    /* If frame processor status LIN_FP_STATUS_ERROR, execute transition to LIN_STATE_RX_ERROR */
    case LIN_FP_STATUS_ERROR:
      /* Set state to LIN_STATE_RX_ERROR */
      Lin_SetState( ChannelConfigIdx, LIN_STATE_RX_ERROR ); /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
      break;

    /* If frame processor status LIN_FP_STATUS_HEADERERROR, execute transition to LIN_STATE_TX_HEADER_ERROR */
    case LIN_FP_STATUS_HEADERERROR:
      /* Set state to LIN_STATE_TX_HEADER_ERROR */
      Lin_SetState( ChannelConfigIdx, LIN_STATE_TX_HEADER_ERROR ); /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
      break;

    /* If frame processor status LIN_FP_STATUS_NO_RESPONSE, execute transition to LIN_STATE_RX_NO_RESPONSE */
    case LIN_FP_STATUS_NO_RESPONSE: /* COV_LIN_HW_TIMEOUT */
      /* Set state to LIN_STATE_RX_NO_RESPONSE */
      Lin_SetState( ChannelConfigIdx, LIN_STATE_RX_NO_RESPONSE ); /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
      break;

    /* If frame processor status LIN_FP_EMPTY, search a valid transition */
    default:
      /* Check if no response bytes received and if no start bit received, execute transition to LIN_STATE_RX_NO_RESPONSE */
      noResponseBytes = Lin_Fp_HasNoResponseBytes( ChannelConfigIdx );
      rxByteNotStarted = Lin_Hw_IfRxByteNotStarted( ChannelConfigIdx );

      if( ( TRUE == noResponseBytes ) && ( TRUE == rxByteNotStarted ) ) /* COV_LIN_HW_TIMEOUT */
      {
        /* Set state to LIN_STATE_RX_NO_RESPONSE */
        Lin_SetState( ChannelConfigIdx, LIN_STATE_RX_NO_RESPONSE ); /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
      }
      break;
  }
}

/**********************************************************************************************************************
 *  Lin_GetS2SBusyStatus
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_GetS2SBusyStatus( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx,
                                                                             uint8 FpStatus )
{
  /* Check frame processor status */
  switch( FpStatus )
  {
    /* If frame processor status LIN_FP_STATUS_HEADERERROR, execute transition to LIN_STATE_TX_HEADER_ERROR */
    case LIN_FP_STATUS_HEADERERROR:
      /* Set state to LIN_STATE_TX_HEADER_ERROR */
      Lin_SetState( ChannelConfigIdx, LIN_STATE_TX_HEADER_ERROR ); /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
      break;

    /* If frame processor status LIN_FP_STATUS_SUCCESSFUL, LIN_FP_STATUS_ERROR or LIN_FP_STATUS_NO_RESPONSE,
       execute transition to LIN_STATE_TX_OK */
    case LIN_FP_STATUS_NO_RESPONSE: /* COV_LIN_DEFENSIVE_PROGRAMMING */
    case LIN_FP_STATUS_SUCCESSFUL: /* COV_LIN_DEFENSIVE_PROGRAMMING */
    case LIN_FP_STATUS_ERROR: /* COV_LIN_DEFENSIVE_PROGRAMMING */
      /* Set state to LIN_STATE_TX_OK */
      Lin_SetState( ChannelConfigIdx, LIN_STATE_TX_OK ); /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
      break;

    /* If frame processor status LIN_FP_EMPTY, execute no transition */
    default:
      /* no transition, stay in current state */
      break;
  }
}

#define LIN_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  FUNCTIONS
 **********************************************************************************************************************/
#define LIN_START_SEC_CODE_ISR
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  Lin_Interrupt
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, LIN_CODE_ISR) Lin_Interrupt( uint8 ChannelHw ) /* PRQA S 3206 */ /* MD_LIN_3206 */
{
  VAR(Lin_ChannelConfigIdxOfChannelIdType, AUTOMATIC) ChannelConfigIdx;
#if ( ( LIN_DEV_ERROR_DETECT == STD_ON ) )
  VAR(uint8, AUTOMATIC) ErrorId = LIN_E_NO_ERROR; /*PRQA S 2981 */ /* MD_LIN_ErrorId */
#endif

  /* Runtime Measurement start */
  Lin_Rtm_Start(Lin_Interrupt)

  /* Check hardware channel parameter validity against configuration */
#if ( LIN_DEV_ERROR_DETECT == STD_ON )
  if ( Lin_GetSizeOfChannelHw() <= ChannelHw )
  {
    ErrorId = LIN_E_INVALID_CHANNEL; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
# if( LIN_INVALIDHNDOFCHANNELHW == STD_ON )
  else if ( Lin_IsInvalidHndOfChannelHw( ChannelHw ) )
  {
    ErrorId = LIN_E_INVALID_CHANNEL; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
# endif
  else
#endif
  {
    ChannelConfigIdx = Lin_GetChannelConfigIdxOfChannelHw( ChannelHw );

    /*
    - In case of SOFTWARE frame processor: Forward interrupt to provide calculate time for the software frame processor.
    - In case of HARDWARE frame processor: No implementation needed because the hardware needs no calculation time. If
                                           hardware frame processor needs the interrupt this function could implement.
    */
    Lin_Fp_Interrupt( ChannelConfigIdx );

#if( LIN_LEAST_ONE_CHANNEL_WAKEUP_SUPPORT_ENABLED == STD_ON )
    /* If in LIN_STATE_SLEEP, search a valid transition */
    if( Lin_GetState( ChannelConfigIdx ) == LIN_STATE_SLEEP )
    {
      /* If a wake up source configured */
# if( LIN_LEAST_ONE_CHANNEL_WAKEUP_SUPPORT_DISABLED == STD_ON ) /* COV_LIN_DERIVATIVE */
      if ( Lin_GetEcuMWakeupSourceOfChannelConfig( ChannelConfigIdx ) != 0u )
# endif
      {
        /* Set state to LIN_STATE_WAKEUP_EXTERNAL, notify the EcuM */
        Lin_SetState( ChannelConfigIdx, LIN_STATE_WAKEUP_EXTERNAL ); /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
        EcuM_CheckWakeup( Lin_GetEcuMWakeupSourceOfChannelConfig( ChannelConfigIdx ) );
      }
    }
#endif
  }

#if ( LIN_DEV_ERROR_REPORT == STD_ON )
  if( ErrorId != LIN_E_NO_ERROR )
  {
    Lin_Det_ReportError( LIN_SID_INTERRUPT_ID, ErrorId );
  }
#elif ( ( LIN_DEV_ERROR_DETECT == STD_ON ) )
  LIN_DUMMY_STATEMENT(ErrorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#else
#endif

  /* Runtime Measurement stop */
  Lin_Rtm_Stop(Lin_Interrupt)
}

#define LIN_STOP_SEC_CODE_ISR
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define LIN_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  Lin_SendFrame
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, LIN_CODE) Lin_SendFrame( uint8 Channel,  /* PRQA S 3206 */ /* MD_LIN_3206 */
                                              P2VAR(Lin_PduType, AUTOMATIC, LIN_APPL_VAR) PduInfoPtr ) /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
  VAR(Lin_ChannelConfigIdxOfChannelIdType, AUTOMATIC) ChannelConfigIdx;
  VAR(Std_ReturnType, AUTOMATIC) RetTmp = E_NOT_OK;
#if ( ( LIN_DEV_ERROR_DETECT == STD_ON ) )
  VAR(uint8, AUTOMATIC) ErrorId = LIN_E_NO_ERROR; /*PRQA S 2981 */ /* MD_LIN_ErrorId */
#endif

  /* Check if component is initialized */
#if ( LIN_DEV_ERROR_DETECT == STD_ON )
  if ( Lin_Dev_InitDetect != LIN_DEV_INITVALUE )
  {
    ErrorId = LIN_E_UNINIT; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
  /* Check PduInfoPtr parameter for NULL pointer */
  else if ( (void*)PduInfoPtr == NULL_PTR ) /* PRQA S 0314 */ /* MD_LIN_NullPtr */
  {
    ErrorId = LIN_E_PARAM_POINTER; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
  /* Check if data length parameter is in range (1-8 data bytes) */
  else if( (PduInfoPtr->Dl == 0u) || (PduInfoPtr->Dl > 8u)  )
  {
    ErrorId = LIN_E_PARAM_VALUE; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
  /* Check Channel parameter validity against configuration */
  else if ( Lin_GetSizeOfChannelId() <= Channel )
  {
    ErrorId = LIN_E_INVALID_CHANNEL; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
# if( LIN_INVALIDHNDOFCHANNELID == STD_ON )
  /* Check validity of channel handle */
  else if ( Lin_IsInvalidHndOfChannelId( Channel ) )
  {
    ErrorId = LIN_E_INVALID_CHANNEL; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
# endif
  else
#endif
  {
    /* Get channel RAM/ROM array index of Channel ID */
    ChannelConfigIdx = Lin_GetChannelConfigIdxOfChannelId( Channel );

    /* If in LIN_CH_SLEEP report a state transiton error else process response */
    if( Lin_GetLinStatus( ChannelConfigIdx ) == LIN_CH_SLEEP )
    {
#if ( ( LIN_DEV_ERROR_DETECT == STD_ON ) )
      ErrorId = LIN_E_STATE_TRANSITION; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
#endif
    }
    else
    {
      RetTmp = E_OK;

      /* Check the frame response type */
      switch( PduInfoPtr->Drc )
      {
        /* If response is generated from this (master) node, execute transition to LIN_STATE_TX_BUSY  */
        case (Lin_FrameResponseType)LIN_MASTER_RESPONSE:
          /* Start a TX Frame, set state to LIN_STATE_TX_BUSY */
          Lin_Fp_StartTxFrame( ChannelConfigIdx, PduInfoPtr ); /* SBSW_LIN_CONST_PTR_CONST */
          Lin_SetState( ChannelConfigIdx, LIN_STATE_TX_BUSY ); /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
          break;

        /* If response is generated from a remote slave node, execute transition to LIN_STATE_RX_BUSY  */
        case (Lin_FrameResponseType)LIN_SLAVE_RESPONSE:
          /* Start a RX Frame, set state to LIN_STATE_RX_BUSY */
          Lin_Fp_StartRxFrame( ChannelConfigIdx, PduInfoPtr ); /* SBSW_LIN_CONST_PTR_CONST */
          Lin_SetState( ChannelConfigIdx, LIN_STATE_RX_BUSY ); /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
          break;

        /* If response is generated from one slave to another slave, execute transition to LIN_STATE_S2S_BUSY  */
        default:
          /* Start a S2S Frame, set state to LIN_STATE_S2S_BUSY */
          Lin_Fp_StartS2sFrame( ChannelConfigIdx, PduInfoPtr ); /* SBSW_LIN_CONST_PTR_CONST */
          Lin_SetState( ChannelConfigIdx, LIN_STATE_S2S_BUSY ); /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
          break;
      }
    }
  }
#if ( LIN_DEV_ERROR_REPORT == STD_ON )
  if( ErrorId != LIN_E_NO_ERROR )
  {
    Lin_Det_ReportError( LIN_SID_SENDFRAME_ID, ErrorId );
  }
#elif ( ( LIN_DEV_ERROR_DETECT == STD_ON ) )
  LIN_DUMMY_STATEMENT(ErrorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#else
#endif

  LIN_DUMMY_STATEMENT(Channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */

  return(RetTmp);
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/***********************************************************************************************************************
 *  Lin_GetStatus
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Lin_StatusType, LIN_CODE) Lin_GetStatus( uint8 Channel,  /* PRQA S 3206 */ /* MD_LIN_3206 */
                                     P2VAR(Lin_u8PtrType, AUTOMATIC, LIN_APPL_VAR) SduPtr )
{
  VAR(Lin_ChannelConfigIdxOfChannelIdType, AUTOMATIC) ChannelConfigIdx;
  VAR(Lin_StatusType, AUTOMATIC) RetTmp = LIN_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
#if ( ( LIN_DEV_ERROR_DETECT == STD_ON ) )
  VAR(uint8, AUTOMATIC) ErrorId = LIN_E_NO_ERROR; /*PRQA S 2981 */ /* MD_LIN_ErrorId */
#endif
  VAR(uint8, AUTOMATIC) FpStatus;

  /* Check if component is initialized */
#if ( LIN_DEV_ERROR_DETECT == STD_ON )
  if ( Lin_Dev_InitDetect != LIN_DEV_INITVALUE )
  {
    ErrorId = LIN_E_UNINIT; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
  /* Check SduPtr parameter for NULL pointer */
  else if ( (void*)SduPtr == NULL_PTR ) /* PRQA S 0314 */ /* MD_LIN_NullPtr */
  {
    ErrorId = LIN_E_PARAM_POINTER; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
  /* Check Channel parameter validity against configuration */
  else if ( Lin_GetSizeOfChannelId() <= Channel )
  {
    ErrorId = LIN_E_INVALID_CHANNEL; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
# if( LIN_INVALIDHNDOFCHANNELID == STD_ON )
  /* Check validity of channel handle */
  else if ( Lin_IsInvalidHndOfChannelId( Channel ) )
  {
    ErrorId = LIN_E_INVALID_CHANNEL; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
# endif
  else
#endif
  {
    ChannelConfigIdx = Lin_GetChannelConfigIdxOfChannelId( Channel );

    /* Dequeue frame processor status */
    FpStatus = Lin_Fp_DequeueStatus( ChannelConfigIdx );

    /* Handling the current LIN state */
    switch( Lin_GetState( ChannelConfigIdx ) )
    {
      /* If in LIN_STATE_SLEEP_PENDING, execute transition to LIN_STATE_SLEEP */
      case LIN_STATE_SLEEP_PENDING:
        /* Set current state to LIN_STATE_SLEEP, enable wakeup detection */
        Lin_SetState( ChannelConfigIdx, LIN_STATE_SLEEP ); /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
        Lin_Fp_EnableWakupDetection( ChannelConfigIdx );
        break;

      /* If in LIN_STATE_WAKEUP_PENDING, execute transition to LIN_STATE_WAKE */
      case LIN_STATE_WAKEUP_PENDING:
        /* Set current state to LIN_STATE_WAKE, disable wakeup detection */
        Lin_SetState( ChannelConfigIdx, LIN_STATE_WAKE ); /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
        Lin_Fp_DisableWakupDetection( ChannelConfigIdx );
        break;

      /* If in LIN_STATE_TX_BUSY, search a valid transition */
      case LIN_STATE_TX_BUSY:
        /* Check frame processor status */
        Lin_GetTxBusyStatus(ChannelConfigIdx,FpStatus);
        break;

      /* If in LIN_STATE_RX_BUSY, search a valid transition */
      case LIN_STATE_RX_BUSY:
        /* Check frame processor status */
        Lin_GetRxBusyStatus(ChannelConfigIdx,FpStatus,SduPtr); /* SBSW_LIN_PTR */
        break;

      /* If in LIN_STATE_S2S_BUSY, search a valid transition */
      case LIN_STATE_S2S_BUSY:
        /* Check frame processor status */
        Lin_GetS2SBusyStatus(ChannelConfigIdx,FpStatus);
        break;

      /* If in state LIN_FP_WAKE, LIN_FP_SLEEP or LIN_FP_WAKEUP_EXTERNAL stay in state */
      default:
        /* no transition, stay in current state */
        break;
    }

    /* return the ASR status of LIN state */
    RetTmp = Lin_GetLinStatus( ChannelConfigIdx );
  }

#if ( LIN_DEV_ERROR_REPORT == STD_ON )
  if( ErrorId != LIN_E_NO_ERROR )
  {
    Lin_Det_ReportError( LIN_SID_GETSTATUS_ID, ErrorId );
  }
#elif ( ( LIN_DEV_ERROR_DETECT == STD_ON ) )
  LIN_DUMMY_STATEMENT(ErrorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#else
#endif

  return(RetTmp);
} /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */


/***********************************************************************************************************************
 *  Lin_CheckWakeup
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, LIN_CODE) Lin_CheckWakeup( uint8 Channel ) /* PRQA S 3206 */ /* MD_LIN_3206 */
{
#if( LIN_LEAST_ONE_CHANNEL_WAKEUP_SUPPORT_ENABLED == STD_ON )
  VAR(Std_ReturnType, AUTOMATIC) RetTmp = E_NOT_OK;  /* PRQA S 2981 */ /* MD_MSR_RetVal */
  VAR(Lin_ChannelConfigIdxOfChannelIdType, AUTOMATIC) ChannelConfigIdx;
#if ( ( LIN_DEV_ERROR_DETECT == STD_ON ) )
  VAR(uint8, AUTOMATIC) ErrorId = LIN_E_NO_ERROR; /*PRQA S 2981 */ /* MD_LIN_ErrorId */
#endif
  /* Check if component is initialized */
# if( LIN_DEV_ERROR_DETECT == STD_ON )
  if ( Lin_Dev_InitDetect != LIN_DEV_INITVALUE )
  {
    ErrorId = LIN_E_UNINIT; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
  /* Check Channel parameter validity against configuration */
  else if ( Lin_GetSizeOfChannelId() <= Channel )
  {
    ErrorId = LIN_E_INVALID_CHANNEL; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
#  if( LIN_INVALIDHNDOFCHANNELID == STD_ON )
  /* Check validity of channel handle */
  else if ( Lin_IsInvalidHndOfChannelId( Channel ) )
  {
    ErrorId = LIN_E_INVALID_CHANNEL; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
#  endif
  else
# endif
  {
    RetTmp = E_OK;
    ChannelConfigIdx = Lin_GetChannelConfigIdxOfChannelId( Channel );

    /* If in LIN_STATE_WAKEUP_EXTERNAL, execute transition to LIN_STATE_SLEEP */
    if ( Lin_GetState( ChannelConfigIdx ) == LIN_STATE_WAKEUP_EXTERNAL )
    {
      /* Inform EcuM and LinIf about wakeup */
      EcuM_SetWakeupEvent( Lin_GetEcuMWakeupSourceOfChannelConfig( ChannelConfigIdx ) ); /* PRQA S 2985 */ /* MD_LIN_2985 */
      LinIf_WakeupConfirmation( Lin_GetEcuMWakeupSourceOfChannelConfig( ChannelConfigIdx ) ); /* PRQA S 2985 */ /* MD_LIN_2985 */

      /* Set state to LIN_STATE_SLEEP, Enable wakeup detection */
      Lin_SetState( ChannelConfigIdx, LIN_STATE_SLEEP ); /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
      Lin_Fp_EnableWakupDetection( ChannelConfigIdx );
    }
  }

# if ( LIN_DEV_ERROR_REPORT == STD_ON )
  if( ErrorId != LIN_E_NO_ERROR )
  {
    Lin_Det_ReportError( LIN_SID_CHECKWAKEUP_ID, ErrorId );
  }
#elif ( ( LIN_DEV_ERROR_DETECT == STD_ON ) )
  LIN_DUMMY_STATEMENT(ErrorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#else
# endif

  return (RetTmp);
#else
  return E_OK;
#endif
}


/***********************************************************************************************************************
 *  Lin_Wakeup
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, LIN_CODE) Lin_Wakeup( uint8 Channel ) /* PRQA S 3206 */ /* MD_LIN_3206 */
{
  VAR(Lin_ChannelConfigIdxOfChannelIdType, AUTOMATIC) ChannelConfigIdx;
  VAR(Std_ReturnType, AUTOMATIC) RetTmp = E_NOT_OK;
#if ( ( LIN_DEV_ERROR_DETECT == STD_ON ) )
  VAR(uint8, AUTOMATIC) ErrorId = LIN_E_NO_ERROR; /*PRQA S 2981 */ /* MD_LIN_ErrorId */
#endif

  /* Check if component is initialized */
#if ( LIN_DEV_ERROR_DETECT == STD_ON )
  if ( Lin_Dev_InitDetect != LIN_DEV_INITVALUE )
  {
    ErrorId = LIN_E_UNINIT; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
  /* Check Channel parameter validity against configuration */
  else if ( Lin_GetSizeOfChannelId() <= Channel )
  {
    ErrorId = LIN_E_INVALID_CHANNEL; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
# if( LIN_INVALIDHNDOFCHANNELID == STD_ON )
  /* Check validity of channel handle */
  else if ( Lin_IsInvalidHndOfChannelId( Channel ) )
  {
    ErrorId = LIN_E_INVALID_CHANNEL; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
# endif
  else
#endif
  {
    ChannelConfigIdx = Lin_GetChannelConfigIdxOfChannelId( Channel );

    /* If in LIN_CH_SLEEP state, execute transition to LIN_STATE_WAKEUP_PENDING else set state transition error */
    if( Lin_GetLinStatus( ChannelConfigIdx ) == LIN_CH_SLEEP )
    {
      RetTmp = E_OK;

      /* Set state to LIN_STATE_WAKEUP_PENDING, disable wake up detection, start a wakeup pulse */
      Lin_SetState( ChannelConfigIdx, LIN_STATE_WAKEUP_PENDING ); /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
      Lin_Fp_DisableWakupDetection( ChannelConfigIdx );
      Lin_Fp_StartWakeupPulse( ChannelConfigIdx );
    }
    else
    {
#if ( ( LIN_DEV_ERROR_DETECT == STD_ON ) )
      ErrorId = LIN_E_STATE_TRANSITION; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
#endif
    }
  }

#if ( LIN_DEV_ERROR_REPORT == STD_ON )
  if( ErrorId != LIN_E_NO_ERROR )
  {
    Lin_Det_ReportError( LIN_SID_WAKEUP_ID, ErrorId );
  }
#elif ( ( LIN_DEV_ERROR_DETECT == STD_ON ) )
  LIN_DUMMY_STATEMENT(ErrorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#else
#endif

  LIN_DUMMY_STATEMENT(Channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */

  return(RetTmp);
}


/***********************************************************************************************************************
 *  Lin_GoToSleep
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, LIN_CODE) Lin_GoToSleep( uint8 Channel ) /* PRQA S 3206 */ /* MD_LIN_3206 */
{
  VAR(Lin_ChannelConfigIdxOfChannelIdType, AUTOMATIC) ChannelConfigIdx;
  VAR(Std_ReturnType, AUTOMATIC) RetTmp = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
#if ( ( LIN_DEV_ERROR_DETECT == STD_ON ) )
  VAR(uint8, AUTOMATIC) ErrorId = LIN_E_NO_ERROR; /*PRQA S 2981 */ /* MD_LIN_ErrorId */
#endif
  VAR(Lin_PduType, AUTOMATIC) PduTmp;
  VAR(uint8, AUTOMATIC) DataTmp[8];

  /* Check if component is initialized */
#if ( LIN_DEV_ERROR_DETECT == STD_ON )
  if ( Lin_Dev_InitDetect != LIN_DEV_INITVALUE )
  {
    ErrorId = LIN_E_UNINIT; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
  /* Check Channel parameter validity against configuration */
  else if ( Lin_GetSizeOfChannelId() <= Channel )
  {
    ErrorId = LIN_E_INVALID_CHANNEL; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
# if( LIN_INVALIDHNDOFCHANNELID == STD_ON )
  /* Check validity of channel handle */
  else if ( Lin_IsInvalidHndOfChannelId( Channel ) )
  {
    ErrorId = LIN_E_INVALID_CHANNEL; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
# endif
  else
#endif
  {
    RetTmp = E_OK;

    ChannelConfigIdx = Lin_GetChannelConfigIdxOfChannelId( Channel );

    /* Set state to LIN_STATE_SLEEP_PENDING */
    Lin_SetState( ChannelConfigIdx, LIN_STATE_SLEEP_PENDING ); /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */

    /* Set-up and transmit a go-to-sleep frame */
    PduTmp.Cs        = LIN_CLASSIC_CS;
    PduTmp.Dl        = 8;
    PduTmp.Drc       = LIN_MASTER_RESPONSE;
    PduTmp.Pid       = 0x3CU;
    PduTmp.SduPtr    = DataTmp;
    PduTmp.SduPtr[0] = 0x00U; /* SBSW_LIN_BUFFER_WRITE */
    PduTmp.SduPtr[1] = 0xFFU; /* SBSW_LIN_BUFFER_WRITE */
    PduTmp.SduPtr[2] = 0xFFU; /* SBSW_LIN_BUFFER_WRITE */
    PduTmp.SduPtr[3] = 0xFFU; /* SBSW_LIN_BUFFER_WRITE */
    PduTmp.SduPtr[4] = 0xFFU; /* SBSW_LIN_BUFFER_WRITE */
    PduTmp.SduPtr[5] = 0xFFU; /* SBSW_LIN_BUFFER_WRITE */
    PduTmp.SduPtr[6] = 0xFFU; /* SBSW_LIN_BUFFER_WRITE */
    PduTmp.SduPtr[7] = 0xFFU; /* SBSW_LIN_BUFFER_WRITE */

    Lin_Fp_StartTxFrame( ChannelConfigIdx, &PduTmp ); /* SBSW_LIN_CONST_PTR_CONST_LOCAL */
  }

#if ( LIN_DEV_ERROR_REPORT == STD_ON )
  if( ErrorId != LIN_E_NO_ERROR )
  {
    Lin_Det_ReportError( LIN_SID_GOTOSLEEP_ID, ErrorId );
  }
#elif ( ( LIN_DEV_ERROR_DETECT == STD_ON ) )
  LIN_DUMMY_STATEMENT(ErrorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#else
#endif

  LIN_DUMMY_STATEMENT(Channel); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */

  return(RetTmp);
}


/***********************************************************************************************************************
 *  Lin_GoToSleepInternal
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, LIN_CODE) Lin_GoToSleepInternal( uint8 Channel ) /* PRQA S 3206 */ /* MD_LIN_3206 */
{
  VAR(Lin_ChannelConfigIdxOfChannelIdType, AUTOMATIC) ChannelConfigIdx;
  VAR(Std_ReturnType, AUTOMATIC) RetTmp = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
#if ( ( LIN_DEV_ERROR_DETECT == STD_ON ) )
  VAR(uint8, AUTOMATIC) ErrorId = LIN_E_NO_ERROR; /*PRQA S 2981 */ /* MD_LIN_ErrorId */
#endif

  /* Check if component is initialized */
#if ( LIN_DEV_ERROR_DETECT == STD_ON )
  if ( Lin_Dev_InitDetect != LIN_DEV_INITVALUE )
  {
    ErrorId = LIN_E_UNINIT; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
  /* Check Channel parameter validity against configuration */
  else if ( Lin_GetSizeOfChannelId() <= Channel )
  {
    ErrorId = LIN_E_INVALID_CHANNEL; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
# if( LIN_INVALIDHNDOFCHANNELID == STD_ON )
  /* Check validity of channel handle */
  else if ( Lin_IsInvalidHndOfChannelId( Channel ) )
  {
    ErrorId = LIN_E_INVALID_CHANNEL; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
# endif
  else
#endif
  {
    RetTmp = E_OK;
    ChannelConfigIdx = Lin_GetChannelConfigIdxOfChannelId( Channel );

    /* Set state to LIN_STATE_SLEEP, enable wakeup detection */
    Lin_SetState( ChannelConfigIdx, LIN_STATE_SLEEP ); /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
    Lin_Fp_EnableWakupDetection( ChannelConfigIdx );
  }

#if ( LIN_DEV_ERROR_REPORT == STD_ON )
  if( ErrorId != LIN_E_NO_ERROR )
  {
    Lin_Det_ReportError( LIN_SID_GOTOSLEEPINTERNAL_ID, ErrorId );
  }
#elif ( ( LIN_DEV_ERROR_DETECT == STD_ON ) )
  LIN_DUMMY_STATEMENT(ErrorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#else
#endif

  return(RetTmp);
}


/***********************************************************************************************************************
 *  Lin_WakeupInternal
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, LIN_CODE) Lin_WakeupInternal( uint8 Channel ) /* PRQA S 3206 */ /* MD_LIN_3206 */
{
  VAR(Lin_ChannelConfigIdxOfChannelIdType, AUTOMATIC) ChannelConfigIdx;
  VAR(Std_ReturnType, AUTOMATIC) RetTmp = E_NOT_OK;
#if ( ( LIN_DEV_ERROR_DETECT == STD_ON ) )
  VAR(uint8, AUTOMATIC) ErrorId = LIN_E_NO_ERROR; /*PRQA S 2981 */ /* MD_LIN_ErrorId */
#endif

  /* Check if component is initialized */
#if ( LIN_DEV_ERROR_DETECT == STD_ON )
  if ( Lin_Dev_InitDetect != LIN_DEV_INITVALUE )
  {
    ErrorId = LIN_E_UNINIT; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
  /* Check Channel parameter validity against configuration */
  else if ( Lin_GetSizeOfChannelId() <= Channel )
  {
    ErrorId = LIN_E_INVALID_CHANNEL; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
# if( LIN_INVALIDHNDOFCHANNELID == STD_ON )
  /* Check validity of channel handle */
  else if ( Lin_IsInvalidHndOfChannelId( Channel ) )
  {
    ErrorId = LIN_E_INVALID_CHANNEL; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
# endif
  else
#endif
  {
    ChannelConfigIdx = Lin_GetChannelConfigIdxOfChannelId( Channel );

    /* If in LIN_CH_SLEEP state, execute transition to LIN_STATE_WAKE */
    if( Lin_GetLinStatus( ChannelConfigIdx ) == LIN_CH_SLEEP )
    {
      RetTmp = E_OK;

      /* Set state to LIN_STATE_WAKE, disable wakeup detection */
      Lin_SetState( ChannelConfigIdx, LIN_STATE_WAKE ); /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */
      Lin_Fp_DisableWakupDetection( ChannelConfigIdx );
    }
    else
    {
#if ( ( LIN_DEV_ERROR_DETECT == STD_ON ) )
      ErrorId = LIN_E_STATE_TRANSITION; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
#endif
    }
  }
#if ( LIN_DEV_ERROR_REPORT == STD_ON )
  if( ErrorId != LIN_E_NO_ERROR )
  {
    Lin_Det_ReportError( LIN_SID_WAKEUPINTERNAL_ID, ErrorId );
  }
#elif ( ( LIN_DEV_ERROR_DETECT == STD_ON ) )
  LIN_DUMMY_STATEMENT(ErrorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#else
#endif

  return(RetTmp);
}

#if ( LIN_VERSION_INFO_API == STD_ON )
/***********************************************************************************************************************
 *  Lin_GetVersionInfo
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, LIN_CODE) Lin_GetVersionInfo( P2VAR(Std_VersionInfoType, AUTOMATIC, LIN_APPL_VAR) versioninfo )
{
#if ( ( LIN_DEV_ERROR_DETECT == STD_ON ) )
  VAR(uint8, AUTOMATIC) ErrorId = LIN_E_NO_ERROR; /*PRQA S 2981 */ /* MD_LIN_ErrorId */
#endif

# if ( LIN_DEV_ERROR_DETECT == STD_ON )
  /* Check versioninfo for NULL pointer */
  if ( versioninfo == (P2VAR(Std_VersionInfoType, AUTOMATIC, LIN_APPL_VAR))NULL_PTR )
  {
    ErrorId = LIN_E_PARAM_POINTER; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
  else
# endif
  {
    /* Set versioninfo with corresponding macros from component header */
    versioninfo->vendorID           = LIN_VENDOR_ID; /* SBSW_LIN_PTR */
    versioninfo->moduleID           = LIN_MODULE_ID; /* SBSW_LIN_PTR */
    versioninfo->sw_major_version   = LIN_PLATFORM_MAJOR_VERSION; /* SBSW_LIN_PTR */
    versioninfo->sw_minor_version   = LIN_PLATFORM_MINOR_VERSION; /* SBSW_LIN_PTR */
    versioninfo->sw_patch_version   = LIN_PLATFORM_PATCH_VERSION; /* SBSW_LIN_PTR */
  }

#if ( LIN_DEV_ERROR_REPORT == STD_ON )
  if( ErrorId != LIN_E_NO_ERROR )
  {
    Lin_Det_ReportError( LIN_SID_GETVERSIONINFO_ID, ErrorId );
  }
#elif ( ( LIN_DEV_ERROR_DETECT == STD_ON ) )
  LIN_DUMMY_STATEMENT(ErrorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#else
#endif
}
#endif /* LIN_VERSION_INFO_API == STD_ON */


/***********************************************************************************************************************
 *  Lin_InitMemory
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, LIN_CODE) Lin_InitMemory( void )
{
#if ( LIN_DEV_ERROR_DETECT == STD_ON )
  /* Set state to uninitialized */
  Lin_Dev_InitDetect = LIN_DEV_UNINITVALUE;
#endif
}


/***********************************************************************************************************************
 *  Lin_Init
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, LIN_CODE) Lin_Init( P2CONST(Lin_ConfigType, AUTOMATIC, LIN_PBCFG) Config ) /* PRQA S 3206 */ /* MD_LIN_3206 */
{
  VAR(Lin_ChannelConfigIdxOfChannelIdType, AUTOMATIC) ChannelConfigIdx;
#if ( ( LIN_DEV_ERROR_DETECT == STD_ON ) )
  VAR(uint8, AUTOMATIC) ErrorId = LIN_E_NO_ERROR; /*PRQA S 2981 */ /* MD_LIN_ErrorId */
#endif

  /* Runtime Measurement start */
  Lin_Rtm_Start(Lin_Init)

#if ( LIN_DEV_ERROR_DETECT == STD_ON )
  /* Check if component is uninitialized */
  if ( Lin_Dev_InitDetect == LIN_DEV_INITVALUE )
  {
    ErrorId = LIN_E_STATE_TRANSITION; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
  }
  else
#endif
  {

#if (LIN_USE_INIT_POINTER == STD_ON)
    /* Check Config parameter for NULL pointer */
    if ( Config == NULL_PTR )
    {
# if ( LIN_DEV_ERROR_DETECT == STD_ON )
      ErrorId = LIN_E_INVALID_POINTER; /*PRQA S 2983 */ /* MD_LIN_ErrorId */
# endif

# if( LIN_USE_ECUM_BSW_ERROR_HOOK == STD_ON )
      EcuM_BswErrorHook((uint16) LIN_MODULE_ID, ECUM_BSWERROR_NULLPTR);
# endif
    }
    else
#endif
    {

#if (LIN_USE_INIT_POINTER == STD_ON)
      Lin_ConfigDataPtr = Config;
#else
      LIN_DUMMY_STATEMENT( Config ); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif

#if( LIN_USE_ECUM_BSW_ERROR_HOOK == STD_ON )
      /* Check version and magic number */
      if (Lin_GetFinalMagicNumber() != LIN_FINAL_MAGIC_NUMBER)
      {
        EcuM_BswErrorHook((uint16) LIN_MODULE_ID, ECUM_BSWERROR_MAGICNUMBER);
      }
      else
#endif
      {
#if ( LIN_DEV_ERROR_DETECT == STD_ON )
        /* Set state to initialized */
        Lin_Dev_InitDetect = LIN_DEV_INITVALUE;
#endif
        /* Set channel independent hardware configuration */
        Lin_Fp_GlobalInit();

        /* Loop over all configured hardware channels */
        for (ChannelConfigIdx = 0; ChannelConfigIdx < Lin_GetSizeOfChannelConfig(); ChannelConfigIdx++)
        {
          /* Set initial state to LIN_STATE_WAKE */
          Lin_SetState( ChannelConfigIdx, LIN_STATE_WAKE ); /* SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID */

          /* Call frame processor initialization */
          Lin_Fp_ChannelInit( ChannelConfigIdx );
        }
      }
    }
  }

#if ( LIN_DEV_ERROR_REPORT == STD_ON )
  if( ErrorId != LIN_E_NO_ERROR )
  {
    Lin_Det_ReportError( LIN_SID_INIT_ID, ErrorId );
  }
#elif ( ( LIN_DEV_ERROR_DETECT == STD_ON ) )
  LIN_DUMMY_STATEMENT(ErrorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#else
#endif

  /* Runtime Measurement stop */
  Lin_Rtm_Stop(Lin_Init)
}


#define LIN_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* module specific MISRA deviations:

  MD_LIN_TESTSUITE_WORKAROUND:
    Reason: The Lin_MemMap.inc file has no include guard. This file will be included into the MemMap.h file which will
            be included multiple times.
    Risk: N/A
    Prevention: N/A

  MD_LIN_ErrorId:
    Reason: This initialization/assignment is redundant. The ErrorId is initialized and in ervery case assigned with a
            new value which is never subsequently used. If the dummy statement is none and error detect is on.
    Risk: No Risk because an unused variable has no sied effect.
    Prevention: N/A

  MD_LIN_NullPtr:
    Reason: Nullpointer check: Cast the pointer to void pointer and check if it is a Null pointer.
    Risk: None, the product of this cast is only used for this comparison.
    Prevention: N/A

  MD_LIN_0303:
    Reason: The size of integer required to hold the result of a pointer cast is implementation-defined. This type
            of operation is not uncommon in embedded software applications where memory mapped I/O ports must be
            addressed.
    Risk: Cast a pointer to an integer type or vice versa may be non-portable.
    Prevention: The code inspection and tests on hardware ensure that the memory location referenced contains the
                registers with the same structure as specified.

    MD_LIN_0324:
    Reason: Cast between an integer and a pointer to incomplete type. Map the register struct to the Memory address of
            the device. see also [MD_LIN_0303]
    Risk: Cast a pointer to an integer type or vice versa may be non-portable.
    Prevention: The code inspection and tests on hardware ensure that the memory location referenced contains the
                registers with the same structure as specified.

  MD_LIN_2985:
    Reason: This Warning occures because of the Test Suite. The function is replaced by macros. This operation is
            redundant. The value of the result is always that of the left-hand operand.
    Risk: No Risk because only in the Test Suite, is this function redefined through a macro.
    Prevention: N/A

  MD_LIN_3206:
    Reason: The parameter is not used in every possible configuration
    Risk: None, an unused parameter has no side effect.
    Prevention: N/A

*/

/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_LIN_CONST_PTR_CONST
  \DESCRIPTION The PduInfo pointer is passed in this function call.
  \COUNTERMEASURE \N The pointer is passed as input parameter to this function. It is not modified until used as
                     parameter in the function call. The caller of this function ensures that the pointer is valid, so
                     it’s also still valid when passed in the function call.

  \ID SBSW_LIN_CONST_PTR_CONST_LOCAL
  \DESCRIPTION The PduTmp pointer is passed in this function call.
  \COUNTERMEASURE \N The pointer always points to the local stack variable PduTmp, therefore it's always valid.

  \ID SBSW_LIN_CSL03_INTERNALSTATE_CHANNELID
  \DESCRIPTION Access to InternalState via indirection over ChannelId.
  \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib.

  \ID SBSW_LIN_BUFFER_WRITE
  \DESCRIPTION Write to the array of constant size.
  \COUNTERMEASURE \R The index based access to the array uses constant index values. The buffer is statically allocated
                     with fixed size (e.g. 8 bytes). The size is sufficient for the largest used index value (e.g. 7).

  \ID SBSW_LIN_PTR
  \DESCRIPTION The function writes to the object referenced by parameter.
  \COUNTERMEASURE \N The caller ensures that the pointers passed to the parameter is valid.

SBSW_JUSTIFICATION_END */

/* START_COVERAGE_JUSTIFICATION

  \ID COV_LIN_DERIVATIVE
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT XX
  \REASON The source code covers different derivatives. There is however only a subset of the derivatives released for
          safeBSW, therefore the code of the unsupported derivatives features or existing/not existing erratas is not
          covered.

  \ID COV_LIN_DEFENSIVE_PROGRAMMING
  \ACCEPT XX
  \REASON The source code of the core trys to cover all theoretically possible transitions, but some of them are
          logically impossible or not supported by the hardware specific extension part. A review garantees that the
          following source code is covered by another condition.

  \ID COV_LIN_HW_TIMEOUT
  \ACCEPT XX
  \ACCEPT XF xf xx
  \ACCEPT TF tf tx
  \REASON The source code covers different derivatives. There is however only a subset of the derivatives released for
          safeBSW, therefore the covered code depends on the hardware frame time out feature.

  \ID COV_LIN_COMPATIBILITY
  \ACCEPT TX
  \ACCEPT XF
  \REASON [COV_MSR_COMPATIBILITY]

END_COVERAGE_JUSTIFICATION */

/**********************************************************************************************************************
 *  END OF FILE: Lin.c
 *********************************************************************************************************************/


