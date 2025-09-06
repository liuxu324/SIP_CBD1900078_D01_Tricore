/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Eth_30_Tc3xx_TimeSync.c
 *        \brief  Timer sub-module source file of the Ethernet controller driver
 *
 *      \details  Containes the implementation of the hardware timer related API of the Ethernet controller driver.
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

/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */

/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777 */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */
#define ETH_30_TC3XX_TIME_SYNC_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Eth_30_Tc3xx_TimeSync.h"
#include "Eth_30_Tc3xx_TimeSync_Int.h"
#include "Eth_30_Tc3xx_LL_TimeSync.h"
#include "Eth_30_Tc3xx.h"
#include "Eth_30_Tc3xx_Int.h"
#include "Eth_30_Tc3xx_LL_Cfg.h"
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

#if (ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON )
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#if !defined (ETH_30_TC3XX_TIME_SYNC_LOCAL)
# define ETH_30_TC3XX_TIME_SYNC_LOCAL static
#endif /* ETH_30_TC3XX_TIME_SYNC_LOCAL */

#if !defined (ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE)
# define ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE LOCAL_INLINE
#endif /* ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE */

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define ETH_30_TC3XX_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS PROTOTYPES
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetGlobalTime
 **********************************************************************************************************************/
/*! \brief       Retrieves the current time of the Eth controllers timer
 *  \details     -
 *  \param[in]   ctrlIdx              Identifier of the Eth controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]  timestampPtr         Retrieve time stamp
 *  \param[out]  timestampQualityPtr  Quality of the time stamp
 *                                    ETH_TIMESTAMP_VALID: Time stamp is valid
 *                                    ETH_TIMESTAMP_INVALID: Time stamp is not valid
 *                                    ETH_TIMESTAMP_UNCERTAIN: Time stamp is uncertain
 *  \return      E_OK - Time stamp successfully retrieved
 *  \return      E_NOT_OK - Time stamp couldn't be retrieved
 *  \context     ANY
 *  \reentrant   TRUE for different Eth controllers
 *  \synchronous TRUE
 *  \config      ETH_30_TC3XX_TIME_SYNC_ENABLED
 *  \pre         -
 */
ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetGlobalTime(
        uint8                                           ctrlIdx,
  P2VAR(Eth_TimeStampType,        AUTOMATIC, AUTOMATIC) timestampPtr,
  P2VAR(Eth_TimestampQualityType, AUTOMATIC, AUTOMATIC) timestampQualityPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_EnableEgressTimestamp
 **********************************************************************************************************************/
/*! \brief       Enables time stamping for the given frame on transmission
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Eth controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   bufIdx   Identifier of the buffer holding the frame to be transmitted
 *               [range: 0 <= bufIdx < Eth_30_Tc3xx_GetSizeOfTxBufferState()]
 *  \return      E_OK - Time stamping of frame successfully enabled
 *  \return      E_NOT_OK - Time stamping of the frame wasn't enabled
 *  \context     ANY
 *  \reentrant   TRUE for different frames
 *  \synchronous TRUE
 *  \config      ETH_30_TC3XX_TIME_SYNC_ENABLED
 *  \pre         -
 */
ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_EnableEgressTimestamp(
  uint8 ctrlIdx,
  uint8 bufIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetEgressTimestamp
 **********************************************************************************************************************/
/*! \brief       Retrieves the time stamp for a frame transmitted
 *  \details     -
 *  \param[in]   ctrlIdx              Identifier of the Eth controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   bufIdx               Identifier of the buffer holding the frame to be transmitted
 *               [range: 0 <= bufIdx < Eth_30_Tc3xx_GetSizeOfTxBufferState()]
 *  \param[out]  timestampPtr         Time stamp taken on transmission
 *  \param[out]  timestampQualityPtr  Quality of the time stamp
 *                                    ETH_TIMESTAMP_VALID: Time stamp is valid
 *                                    ETH_TIMESTAMP_INVALID: Time stamp is not valid
 *                                    ETH_TIMESTAMP_UNCERTAIN: Time stamp is uncertain
 *  \return      E_OK - Time stamp successfully retrieved
 *  \return      E_NOT_OK - Time stamp couldn't be retrieved
 *  \context     ANY
 *  \reentrant   TRUE for different frames
 *  \synchronous TRUE
 *  \config      ETH_30_TC3XX_TIME_SYNC_ENABLED
 *  \pre         -
 */
ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetEgressTimestamp(
        uint8                                           ctrlIdx,
        uint8                                           bufIdx,
  P2VAR(Eth_TimeStampType,        AUTOMATIC, AUTOMATIC) timestampPtr,
  P2VAR(Eth_TimestampQualityType, AUTOMATIC, AUTOMATIC) timestampQualityPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetIngressTimestamp
 **********************************************************************************************************************/
/*! \brief       Retrieves the time stamp for a frame received
 *  \details     -
 *  \param[in]   ctrlIdx              Identifier of the Eth controller
 *               [range: 0 <= CtrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]  timestampPtr         Time stamp taken on reception
 *  \param[out]  timestampQualityPtr  Quality of the time stamp
 *                                    ETH_TIMESTAMP_VALID: Time stamp is valid
 *                                    ETH_TIMESTAMP_INVALID: Time stamp is not valid
 *                                    ETH_TIMESTAMP_UNCERTAIN: Time stamp is uncertain
 *  \return      E_OK - Time stamp successfully retrieved
 *  \return      E_NOT_OK - Time stamp couldn't be retrieved
 *  \context     ANY
 *  \reentrant   TRUE for different frames
 *  \synchronous TRUE
 *  \config      ETH_30_TC3XX_TIME_SYNC_ENABLED
 *  \pre         -
 */
ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetIngressTimestamp(
        uint8                                           ctrlIdx,
  P2VAR(Eth_TimeStampType,        AUTOMATIC, AUTOMATIC) timestampPtr,
  P2VAR(Eth_TimestampQualityType, AUTOMATIC, AUTOMATIC) timestampQualityPtr);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/
#if (ETH_30_TC3XX_IMPLEMENTATION_GET_GLOBAL_TIME == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetGlobalTime
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetGlobalTime(
        uint8                                           ctrlIdx,
  P2VAR(Eth_TimeStampType,        AUTOMATIC, AUTOMATIC) timestampPtr,
  P2VAR(Eth_TimestampQualityType, AUTOMATIC, AUTOMATIC) timestampQualityPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* Call the hardware dependent interface to trigger a timer capture operation */
  retVal = Eth_30_Tc3xx_TimeSync_LL_CaptureHwTime(ctrlIdx, timestampPtr); /*lint !e522 */

   /* If the time stamp could be retrieved successfully from the hardware */
  if (retVal == E_OK)
  {
    /* Mark time stamp as valid */
    (*timestampQualityPtr) = ETH_TIMESTAMP_VALID;
  }
  /* If the time stamp could not be retrieved successfully from the hardware */
  else
  {
    /* Mark time stamp as invalid */
    (*timestampQualityPtr) = ETH_TIMESTAMP_INVALID;
  }

  return retVal;
} /* Eth_30_Tc3xx_Internal_GetGlobalTime() */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_GET_GLOBAL_TIME */

#if (ETH_30_TC3XX_IMPLEMENTATION_ENABLE_EGRESS_TIMESTAMP == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_EnableEgressTimestamp
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_EnableEgressTimestamp(
  uint8 ctrlIdx,
  uint8 bufIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* If the buffer holding the frame that shall be timestamped is locked */
  if( Eth_30_Tc3xx_Cfg_GetTxBufferBusyState(ctrlIdx, bufIdx) == ETH_30_TC3XX_BUFFER_BUSY )
  {
    /* Set the global state variable to indicate that a timestamp is requested for the requested buffer */
    Eth_30_Tc3xx_Cfg_SetTxTsRequest(ctrlIdx, bufIdx, ETH_30_TC3XX_TIMESYNC_TS_REQUESTED);
    retVal = E_OK;
  }

  return retVal;
} /* Eth_30_Tc3xx_Internal_EnableEgressTimestamp() */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_ENABLE_EGRESS_TIMESTAMP */

#if (ETH_30_TC3XX_IMPLEMENTATION_GET_EGRESS_TIMESTAMP == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetEgressTimestamp
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetEgressTimestamp(
        uint8                                           ctrlIdx,
        uint8                                           bufIdx,
  P2VAR(Eth_TimeStampType,        AUTOMATIC, AUTOMATIC) timestampPtr,
  P2VAR(Eth_TimestampQualityType, AUTOMATIC, AUTOMATIC) timestampQualityPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* Buffer is still locked, timestamp was requested and transmit trigger was cleared by Hardware. */
  /* PRQA S 3415 2 */ /* MD_Eth_30_Tc3xx_3415 */
  if( (Eth_30_Tc3xx_Cfg_GetTxBufferBusyState(ctrlIdx, bufIdx) == ETH_30_TC3XX_BUFFER_BUSY) &&
      (Eth_30_Tc3xx_Cfg_GetTxTsRequest(ctrlIdx, bufIdx) == ETH_30_TC3XX_TIMESYNC_TS_REQUESTED) )
  {
    /* Retrieve the context (ring and descriptor) the time stamp shall be retrieved for */
    P2VAR(Eth_30_Tc3xx_TsContextType, AUTOMATIC, AUTOMATIC) txTsContext = Eth_30_Tc3xx_Cfg_GetTxTsContext(ctrlIdx, bufIdx);

    /* Retrieve the egress timestamp */
    retVal = Eth_30_Tc3xx_TimeSync_LL_GetTxTimeStamp(ctrlIdx, txTsContext->RingIdx, (uint8)txTsContext->DescrIdx, timestampPtr); /*lint !e522 */

    /* Check timestamp value for validity */
    if( retVal == E_OK )
    {
      (*timestampQualityPtr) = ETH_TIMESTAMP_VALID;
    }
    else
    {
      (*timestampQualityPtr) = ETH_TIMESTAMP_INVALID;
    }
  }

  return retVal;
} /* Eth_30_Tc3xx_Internal_GetEgressTimestamp() */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_GET_EGRESS_TIMESTAMP */

#if (ETH_30_TC3XX_IMPLEMENTATION_GET_INGRESS_TIMESTAMP == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetIngressTimestamp
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetIngressTimestamp(
        uint8                                           ctrlIdx,
  P2VAR(Eth_TimeStampType,        AUTOMATIC, AUTOMATIC) timestampPtr,
  P2VAR(Eth_TimestampQualityType, AUTOMATIC, AUTOMATIC) timestampQualityPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* Retrieve the context (ring and descriptor) the time stamp shall be retrieved for */
  P2VAR(Eth_30_Tc3xx_TsContextType, AUTOMATIC, AUTOMATIC) rxTsContext = Eth_30_Tc3xx_Cfg_GetRxTsContext(ctrlIdx);

  /* Retrieve the ingress timestamp */
  retVal = Eth_30_Tc3xx_TimeSync_LL_GetRxTimeStamp(ctrlIdx, rxTsContext->RingIdx, (uint8)rxTsContext->DescrIdx, timestampPtr); /*lint !e522 */

  /* Check timestamp value for validity */
  if( retVal == E_OK )
  {
    (*timestampQualityPtr) = ETH_TIMESTAMP_VALID;
  }
  else
  {
    (*timestampQualityPtr) = ETH_TIMESTAMP_INVALID;
  }

  return retVal;
} /* Eth_30_Tc3xx_Internal_GetIngressTimestamp() */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_GET_INGRESS_TIMESTAMP */
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_TimeSync_Init
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_TimeSync_Init(
  uint8 CtrlIdx)
{
  Std_ReturnType    retVal;
  Eth_TimeStampType timestamp;
  
  /* Set hardware time to zero */
  timestamp.seconds = 0u;
  timestamp.secondsHi = 0u;
  timestamp.nanoseconds = 0u;

  /* Call lower layer function to set the hardware time */
  retVal = Eth_30_Tc3xx_TimeSync_LL_SetHwTime(CtrlIdx, &timestamp); /*lint !e522 */
  
  return retVal;
} /* Eth_30_Tc3xx_TimeSync_Init() */
 
#if (ETH_30_TC3XX_IMPLEMENTATION_GET_GLOBAL_TIME == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetGlobalTime
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetGlobalTime(
        uint8                                            CtrlIdx,
  P2VAR(Eth_TimeStampType,        AUTOMATIC, AUTOMATIC)  TimestampPtr,
  P2VAR(Eth_TimestampQualityType, AUTOMATIC, AUTOMATIC)  TimestampQualityPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETH_30_TC3XX_E_NO_ERROR;

# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_OFF)
  ETH_30_TC3XX_DUMMY_STATEMENT(retVal); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

  CtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);
  /* ----- Development Error Checks ------------------------------------- */
# if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
  /* Check module state and input parameters */
  if( Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT )
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if( CtrlIdx >= ETH_30_TC3XX_MAX_CTRLS_TOTAL )
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if( Eth_30_Tc3xx_CtrlMode[CtrlIdx] == ETH_MODE_DOWN )
  {
    errorId = ETH_30_TC3XX_E_INV_MODE;
  }
  else if( TimestampPtr == NULL_PTR )
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else if( TimestampQualityPtr == NULL_PTR )
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* Call the internal interface to retrieve the global time */
    retVal = Eth_30_Tc3xx_Internal_GetGlobalTime(CtrlIdx, TimestampPtr, TimestampQualityPtr);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  /* Report default errors if any occurred */
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx), ETH_30_TC3XX_TIME_SYNC_SID_GET_GLOBAL_TIME, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* Eth_30_Tc3xx_GetGlobalTime() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_GET_GLOBAL_TIME */

#if (ETH_30_TC3XX_IMPLEMENTATION_ENABLE_EGRESS_TIMESTAMP == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_EnableEgressTimestamp
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_EnableEgressTimestamp(
  uint8 CtrlIdx,
  uint8 BufIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETH_30_TC3XX_E_NO_ERROR;

# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_OFF)
  ETH_30_TC3XX_DUMMY_STATEMENT(retVal); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

  CtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);
  /* ----- Development Error Checks ------------------------------------- */
# if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
  /* Check module state and input parameters */
  if( Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT )
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if( CtrlIdx >= ETH_30_TC3XX_MAX_CTRLS_TOTAL )
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if( Eth_30_Tc3xx_CtrlMode[CtrlIdx] == ETH_MODE_DOWN )
  {
    errorId = ETH_30_TC3XX_E_INV_MODE;
  }
  else if( BufIdx >= Eth_30_Tc3xx_Cfg_GetTxBufferNum(CtrlIdx) )
  {
    errorId = ETH_30_TC3XX_E_INV_PARAM;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* Call the internal interface to enable egress timestamping */
    retVal = Eth_30_Tc3xx_Internal_EnableEgressTimestamp(CtrlIdx, BufIdx);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  /* Report default errors if any occurred */
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx), ETH_30_TC3XX_TIME_SYNC_SID_ENABLE_EGRESS_TIMESTAMP, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* Eth_30_Tc3xx_EnableEgressTimestamp() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_ENABLE_EGRESS_TIMESTAMP */

#if (ETH_30_TC3XX_IMPLEMENTATION_GET_EGRESS_TIMESTAMP == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetEgressTimestamp
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetEgressTimestamp(
        uint8                                            CtrlIdx,
        uint8                                            BufIdx,
  P2VAR(Eth_TimeStampType,        AUTOMATIC, AUTOMATIC)  TimestampPtr,
  P2VAR(Eth_TimestampQualityType, AUTOMATIC, AUTOMATIC)  TimestampQualityPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETH_30_TC3XX_E_NO_ERROR;

# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_OFF)
  ETH_30_TC3XX_DUMMY_STATEMENT(retVal); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

  CtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);
  /* ----- Development Error Checks ------------------------------------- */
# if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
  /* Check module state and input parameters */
  if( Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT )
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if( CtrlIdx >= ETH_30_TC3XX_MAX_CTRLS_TOTAL )
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if( Eth_30_Tc3xx_CtrlMode[CtrlIdx] == ETH_MODE_DOWN )
  {
    errorId = ETH_30_TC3XX_E_INV_MODE;
  }
  else if( BufIdx >= Eth_30_Tc3xx_Cfg_GetTxBufferNum(CtrlIdx) )
  {
    errorId = ETH_30_TC3XX_E_INV_PARAM;
  }
  else if( TimestampPtr == NULL_PTR )
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else if( TimestampQualityPtr == NULL_PTR )
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* Call the internal interface to retrieve an egress timestamp */
    retVal = Eth_30_Tc3xx_Internal_GetEgressTimestamp(CtrlIdx, BufIdx, TimestampPtr, TimestampQualityPtr);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  /* Report default errors if any occurred */
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx), ETH_30_TC3XX_TIME_SYNC_SID_GET_EGRESS_TIMESTAMP, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* Eth_30_Tc3xx_GetEgressTimestamp() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_GET_EGRESS_TIMESTAMP */

#if (ETH_30_TC3XX_IMPLEMENTATION_GET_INGRESS_TIMESTAMP == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetIngressTimestamp
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetIngressTimestamp(
        uint8                                            CtrlIdx,
  P2VAR(Eth_DataType,             AUTOMATIC, AUTOMATIC)  DataPtr,            /* PRQA S 3673 */ /* MD_Eth_30_Tc3xx_3673 */
  P2VAR(Eth_TimeStampType,        AUTOMATIC, AUTOMATIC)  TimestampPtr,
  P2VAR(Eth_TimestampQualityType, AUTOMATIC, AUTOMATIC)  TimestampQualityPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETH_30_TC3XX_E_NO_ERROR;

  ETH_30_TC3XX_DUMMY_STATEMENT(DataPtr); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_OFF)
  ETH_30_TC3XX_DUMMY_STATEMENT(retVal); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

  CtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);
  /* ----- Development Error Checks ------------------------------------- */
# if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
  /* Check module state and input parameters */
  if( Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT )
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if( CtrlIdx >= ETH_30_TC3XX_MAX_CTRLS_TOTAL )
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if( Eth_30_Tc3xx_CtrlMode[CtrlIdx] == ETH_MODE_DOWN )
  {
    errorId = ETH_30_TC3XX_E_INV_MODE;
  }
  else if( DataPtr == NULL_PTR )
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else if( TimestampPtr == NULL_PTR )
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else if( TimestampQualityPtr == NULL_PTR )
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* Call the internal interface to retrieve an ingress timestamp */
    retVal = Eth_30_Tc3xx_Internal_GetIngressTimestamp(CtrlIdx, TimestampPtr, TimestampQualityPtr);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  /* Report default errors if any occurred */
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx), ETH_30_TC3XX_TIME_SYNC_SID_GET_INGRESS_TIMESTAMP, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* Eth_30_Tc3xx_GetIngressTimestamp() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_GET_INGRESS_TIMESTAMP */

#define ETH_30_TC3XX_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ETH_30_TC3XX_ENABLE_TIMESYNC */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_TimeSync.c
 *********************************************************************************************************************/
 
