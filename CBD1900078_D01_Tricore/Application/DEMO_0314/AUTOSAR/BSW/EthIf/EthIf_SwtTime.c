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
/*!        \file  EthIf_SwtTime.c
 *        \brief  EthIf SwtTime public API source file
 *
 *      \details  Implementation of the public API of the sub-module SwtTime of EthIf.
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

#define ETHIF_SWTTIME_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
#include "EthIf_SwtTime.h"
#include "EthIf_SwtTime_Cbk.h"
#include "EthIf_SwtTime_Int.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of Msn header file */
#if (  (ETHIF_SW_MAJOR_VERSION != (10u)) \
    || (ETHIF_SW_MINOR_VERSION != (0u)) \
    || (ETHIF_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of EthIf_SwtTime.c and EthIf.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (ETHIF_CFG_MAJOR_VERSION != (7u)) \
    || (ETHIF_CFG_MINOR_VERSION != (0u)) )
# error "Version numbers of EthIf_SwtTime.c and EthIf_Cfg.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (ETHIF_SWTTIME_LOCAL)                                                                                      /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_SWTTIME_LOCAL static
#endif

#if !defined (ETHIF_SWTTIME_LOCAL_INLINE)                                                                               /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_SWTTIME_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define ETHIF_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#if ( ETHIF_ETHSWT_TIME_STAMP_SUPPORT == STD_ON )                                                                       /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 * EthIf_RestoreSwtTimeStampRxInfo
 **********************************************************************************************************************/
/*! \brief          Restores time stamp related information stored during reception of a frame
 *  \details        Function restores information related to a time stamp for being able to pass the time stamp to the
 *                  designated upper layer.
 *  \param[in]      ethCtrlIdx        Eth controller the time stamp is related to
 *                                    [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \param[in]      ctxtFlag          Flag indicating the time stamp context (ingress or egress time stamp)
 *  \param[in]      frameId           Identifier of the frame the time stamp is related to
 *  \param[out]     ethIfCtrlIdxPtr   EthIf controller the frame related to the time stamp was passed to
 *  \param[out]     frameOwnerIdxPtr  User the frame related to the time stamp was passed to
 *  \param[out]     dataPtr           Pointer to the payload of the frame related to the time stamp passed to the user
 *  \return         TRUE - there was information related to the time stamp stored previously
 *  \return         FALSE - there was no information related to the time stamp stored previously
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 **********************************************************************************************************************/
ETHIF_SWTTIME_LOCAL_INLINE FUNC(boolean, ETHIF_SWTTIME_INLINE_CODE) EthIf_RestoreSwtTimeStampRxInfo(
        EthIf_EthCtrlIterType                                ethCtrlIdx,
        EthIf_SwtTsProcFlagsType                             ctxtFlag,
        Eth_FrameIdType                                      frameId,
  P2VAR(EthIf_EthIfCtrlIterType,  AUTOMATIC, ETHIF_APPL_VAR) ethIfCtrlIdxPtr,
  P2VAR(EthIf_UserIterType,       AUTOMATIC, ETHIF_APPL_VAR) frameOwnerIdxPtr,
  P2VAR(EthIf_FrameBufferPtrType, AUTOMATIC, ETHIF_APPL_VAR) dataPtr);

/**********************************************************************************************************************
 * EthIf_GetSwtTimeStampTxInfo
 **********************************************************************************************************************/
/*! \brief          Retrieves a time stamp handling data element related to frame buffer
 *  \details        Function retrieves the transmission time stamp handling data element related to the given buffer if
 *                  available.
 *  \param[in]      ethCtrlIdx  Eth controller the frame buffer is related to
 *                              [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \param[in]      bufIdx      Identifier of the buffer in context of the Eth controller
 *                              [range: bufIdx <= EthIf_GetMaxTxBufForEthCtrl(ethCtrlIdx)]
 *  \param[in]      frameId     Ethernet frame identifier
 *  \param[out]     txInfoPtr   Pointer to the retrieved tx time stamp handling data element
 *  \return         TRUE - there was a data element stored for the frame buffer
 *  \return         FALSE - there wasn't a data element stored for the frame buffer
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 **********************************************************************************************************************/
ETHIF_SWTTIME_LOCAL_INLINE FUNC(boolean, ETHIF_SWTTIME_INLINE_CODE) EthIf_GetSwtTimeStampTxInfo(
        EthIf_EthCtrlIterType                                     ethCtrlIdx,
        uint8                                                     bufIdx,
        Eth_FrameIdType                                           frameId,
  P2VAR(EthIf_SwtTsTxCtxtPoolIterType, AUTOMATIC, ETHIF_APPL_VAR) swtTsTxCtxtPoolElemIdx);

/**********************************************************************************************************************
 * EthIf_RestoreSwtTimeStampTxInfo
 **********************************************************************************************************************/
/*! \brief          Restores time stamp related information stored during transmission of a frame
 *  \details        Function restores information related to a time stamp for being able to pass the time stamp to the
 *                  designated upper layer.
 *  \param[in]      ethCtrlIdx        Eth controller the time stamp is related to
 *                                    [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \param[in]      ctxtFlag          Flag indicating the time stamp context (ingress or egress time stamp)
 *  \param[in]      frameId           Identifier of the frame the time stamp is related to
 *  \param[out]     ethIfCtrlIdxPtr   EthIf controller the frame related to the time stamp was passed to
 *  \param[out]     frameOwnerIdxPtr  User the frame related to the time stamp was passed to
 *  \param[out]     dataPtr           Pointer to the payload of the frame related to the time stamp passed to the user
 *  \return         TRUE - there was information related to the time stamp stored previously
 *  \return         FALSE - there was no information related to the time stamp stored previously
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 **********************************************************************************************************************/
ETHIF_SWTTIME_LOCAL_INLINE FUNC(boolean, ETHIF_SWTTIME_INLINE_CODE) EthIf_RestoreSwtTimeStampTxInfo(
        EthIf_EthCtrlIterType                                ethCtrlIdx,
        EthIf_SwtTsProcFlagsType                             ctxtFlag,
        Eth_FrameIdType                                      frameId,
  P2VAR(EthIf_EthIfCtrlIterType,  AUTOMATIC, ETHIF_APPL_VAR) ethIfCtrlIdxPtr,
  P2VAR(EthIf_UserIterType,       AUTOMATIC, ETHIF_APPL_VAR) frameOwnerIdxPtr,
  P2VAR(EthIf_FrameBufferPtrType, AUTOMATIC, ETHIF_APPL_VAR) dataPtr);

/**********************************************************************************************************************
 * EthIf_SetSwtTimeStampTxInfoPending
 **********************************************************************************************************************/
/*! \brief          Sets up the data element for later handling of time stamp information
 *  \details        Function sets up the passed data element so it is possible to handle time stamp information indicated
 *                  by the Eth switch driver later on.
 *  \param[in]      txInfoPtr   Pointer to the tx time stamp handling data element
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 **********************************************************************************************************************/
ETHIF_SWTTIME_LOCAL_INLINE FUNC(void, ETHIF_SWTTIME_INLINE_CODE) EthIf_SetSwtTimeStampTxInfoPending(
  EthIf_SwtTsTxCtxtPoolIterType swtTsTxCtxtPoolElemIdx);
#endif /* ETHIF_ETHSWT_TIME_STAMP_SUPPORT */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if ( ETHIF_ETHSWT_TIME_STAMP_SUPPORT == STD_ON )                                                                       /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 * EthIf_RestoreSwtTimeStampRxInfo
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
 */
ETHIF_SWTTIME_LOCAL_INLINE FUNC(boolean, ETHIF_SWTTIME_INLINE_CODE) EthIf_RestoreSwtTimeStampRxInfo(
        EthIf_EthCtrlIterType                                ethCtrlIdx,
        EthIf_SwtTsProcFlagsType                             ctxtFlag,
        Eth_FrameIdType                                      frameId,
  P2VAR(EthIf_EthIfCtrlIterType,  AUTOMATIC, ETHIF_APPL_VAR) ethIfCtrlIdxPtr,
  P2VAR(EthIf_UserIterType,       AUTOMATIC, ETHIF_APPL_VAR) frameOwnerIdxPtr,
  P2VAR(EthIf_FrameBufferPtrType, AUTOMATIC, ETHIF_APPL_VAR) dataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_SwtTsRxCtxtPoolIterType poolElemIdx;
  boolean result;

  /* ----- Implementation ----------------------------------------------- */
  result = FALSE;

  /* #10 Enter exclusive area (Reason: Ensure consistency of switch reception timestamp elements) */
  EthIf_EnterExclusiveArea(SWT_TIME_STAMP_RX_CTXT_POOL); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Query for the information related to the frame */
  for( poolElemIdx = EthIf_GetSwtTsRxCtxtPoolStartIdxOfEthCtrl(ethCtrlIdx);
       poolElemIdx < EthIf_GetSwtTsRxCtxtPoolEndIdxOfEthCtrl(ethCtrlIdx);
       poolElemIdx++ )
  {
    if( EthIf_GetFrameIdOfSwtTsRxCtxtPool(poolElemIdx) == frameId )
    {
      EthIf_SwtTsProcFlagsType procFlags = EthIf_GetProcFlagsOfSwtTsRxCtxtPool(poolElemIdx);

      /* #200 Entry found -> retrieve the information stored for being able to pass the time stamp to the
       *      designated upper layer */
      (*ethIfCtrlIdxPtr)  = EthIf_GetEthIfCtrlIdxOfSwtTsRxCtxtPool(poolElemIdx);                                        /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
      (*frameOwnerIdxPtr) = EthIf_GetUserIdxOfSwtTsRxCtxtPool(poolElemIdx);                                             /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
      (*dataPtr)          = EthIf_GetDataPtrOfSwtTsRxCtxtPool(poolElemIdx);                                             /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */

      /* #210 Check if information is restored for both ingress and egress time stamp indication.
       *      If so, invalidate the information, otherwise keep it for restoring the information
       *      in the other context. */
      procFlags &= (EthIf_SwtTsProcFlagsType)~ctxtFlag;

      if( procFlags == 0x00U )
      {
        EthIf_SetDataPtrOfSwtTsRxCtxtPool(poolElemIdx, NULL_PTR);                                                       /* SBSW_ETHIF_INT_FCT_PARAM_PTR_NULL_CSL_STRUCT_MEM_CSL03 */
        EthIf_SetFrameIdOfSwtTsRxCtxtPool(poolElemIdx, ETH_INVALID_FRAME_ID);                                           /* SBSW_ETHIF_COMMON_CSL03 */
      }

      EthIf_SetProcFlagsOfSwtTsRxCtxtPool(poolElemIdx, procFlags);                                                      /* SBSW_ETHIF_COMMON_CSL03 */
      result = TRUE;
      break;
    }
  }

  /* #30 Leave exclusive area -> processing on elements finished */
  EthIf_ExitExclusiveArea(SWT_TIME_STAMP_RX_CTXT_POOL); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return result;
} /* EthIf_RestoreSwtTimeStampRxInfo() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/**********************************************************************************************************************
 * EthIf_RestoreSwtTimeStampTxInfo
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
 */
ETHIF_SWTTIME_LOCAL_INLINE FUNC(boolean, ETHIF_SWTTIME_INLINE_CODE) EthIf_RestoreSwtTimeStampTxInfo(
        EthIf_EthCtrlIterType                                ethCtrlIdx,
        EthIf_SwtTsProcFlagsType                             ctxtFlag,
        Eth_FrameIdType                                      frameId,
  P2VAR(EthIf_EthIfCtrlIterType,  AUTOMATIC, ETHIF_APPL_VAR) ethIfCtrlIdxPtr,
  P2VAR(EthIf_UserIterType,       AUTOMATIC, ETHIF_APPL_VAR) frameOwnerIdxPtr,
  P2VAR(EthIf_FrameBufferPtrType, AUTOMATIC, ETHIF_APPL_VAR) dataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_SwtTsTxCtxtPoolIterType poolElemIdx;
  boolean result;

  /* ----- Implementation ----------------------------------------------- */
  result = FALSE;

  /* #10 Enter exclusive area (Reason: Ensure consistency of switch transmission timestamp elements) */
  EthIf_EnterExclusiveArea(SWT_TIME_STAMP_TX_CTXT_POOL); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Query for the information related to the frame */
  for( poolElemIdx = EthIf_GetSwtTsTxCtxtPoolStartIdxOfEthCtrl(ethCtrlIdx);
       poolElemIdx < EthIf_GetSwtTsTxCtxtPoolEndIdxOfEthCtrl(ethCtrlIdx);
       poolElemIdx++ )
  {
    if( EthIf_GetStateOfSwtTsTxCtxtPool(poolElemIdx) == ETHIF_TX_SWT_TS_ELEM_TX_PEND_STATEOFSWTTSTXCTXTPOOL )
    {
      if( EthIf_GetFrameIdOfSwtTsTxCtxtPool(poolElemIdx) == frameId )
      {
        EthIf_SwtTsProcFlagsType procFlags = EthIf_GetProcFlagsOfSwtTsTxCtxtPool(poolElemIdx);

        /* #200 Entry found -> retrieve the information stored for being able to pass the time stamp to the
         *      designated upper layer */
        (*ethIfCtrlIdxPtr)  = EthIf_GetEthIfCtrlIdxOfSwtTsTxCtxtPool(poolElemIdx);                                        /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
        (*frameOwnerIdxPtr) = EthIf_GetUserIdxOfSwtTsTxCtxtPool(poolElemIdx);                                             /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
        (*dataPtr)          = EthIf_GetDataPtrOfSwtTsTxCtxtPool(poolElemIdx);                                             /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */

        /* #210 Check if information is restored for both ingress and egress time stamp indication.
         *      If so, invalidate the information, otherwise keep it for restoring the information
         *      in the other context. */
        procFlags &= (EthIf_SwtTsProcFlagsType)~ctxtFlag;

        if( procFlags == 0x00U )
        {
         EthIf_SetDataPtrOfSwtTsTxCtxtPool(poolElemIdx, NULL_PTR);                                                        /* SBSW_ETHIF_INT_FCT_PARAM_PTR_NULL_CSL_STRUCT_MEM_CSL03 */
         EthIf_SetFrameIdOfSwtTsTxCtxtPool(poolElemIdx, ETH_INVALID_FRAME_ID);                                            /* SBSW_ETHIF_COMMON_CSL03 */
         EthIf_SetBufIdxOfSwtTsTxCtxtPool(poolElemIdx, EthIf_GetMaxTxBufPerEthCtrl());                                    /* SBSW_ETHIF_COMMON_CSL03 */
         EthIf_SetStateOfSwtTsTxCtxtPool(poolElemIdx, ETHIF_TX_SWT_TS_ELEM_FREE_STATEOFSWTTSTXCTXTPOOL);                  /* SBSW_ETHIF_COMMON_CSL03 */
        }

        EthIf_SetProcFlagsOfSwtTsTxCtxtPool(poolElemIdx, procFlags);                                                      /* SBSW_ETHIF_COMMON_CSL03 */
        result = TRUE;
        break;
      }
    }
  }

  /* #30 Leave exclusive area -> Processing of elements finished */
  EthIf_ExitExclusiveArea(SWT_TIME_STAMP_TX_CTXT_POOL); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return result;
} /* EthIf_RestoreSwtTimeStampTxInfo() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/**********************************************************************************************************************
 * EthIf_GetSwtTimeStampTxInfo
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHIF_SWTTIME_LOCAL_INLINE FUNC(boolean, ETHIF_SWTTIME_INLINE_CODE) EthIf_GetSwtTimeStampTxInfo(
        EthIf_EthCtrlIterType                                     ethCtrlIdx,
        uint8                                                     bufIdx,
        Eth_FrameIdType                                           frameId,
  P2VAR(EthIf_SwtTsTxCtxtPoolIterType, AUTOMATIC, ETHIF_APPL_VAR) swtTsTxCtxtPoolElemIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_SwtTsTxCtxtPoolIterType poolElemIdx;
  boolean result;

  /* ----- Implementation ----------------------------------------------- */
  result     = FALSE;

  /* #10 Enter exclusive area (Reason: Ensure consistency of switch transmission timestamp elements) */
  EthIf_EnterExclusiveArea(SWT_TIME_STAMP_TX_CTXT_POOL); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Query for the information related to the frame buffer */
  for( poolElemIdx = EthIf_GetSwtTsTxCtxtPoolStartIdxOfEthCtrl(ethCtrlIdx);
       poolElemIdx < EthIf_GetSwtTsTxCtxtPoolEndIdxOfEthCtrl(ethCtrlIdx);
       poolElemIdx++ )
  {
    if( EthIf_GetStateOfSwtTsTxCtxtPool(poolElemIdx) != ETHIF_TX_SWT_TS_ELEM_FREE_STATEOFSWTTSTXCTXTPOOL )
    {
      if( (EthIf_GetBufIdxOfSwtTsTxCtxtPool(poolElemIdx)  == bufIdx) &&
          (EthIf_GetFrameIdOfSwtTsTxCtxtPool(poolElemIdx) == frameId)    )
      {
        (*swtTsTxCtxtPoolElemIdx) = poolElemIdx;                                                                          /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
        result       = TRUE;
        break;
      }
    }
  }

  /* #30 Leave exclusive area -> Processing of elements finished */
  EthIf_ExitExclusiveArea(SWT_TIME_STAMP_TX_CTXT_POOL); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return result;
} /* EthIf_GetSwtTimeStampTxInfo() */

/**********************************************************************************************************************
 * EthIf_SetSwtTimeStampTxInfoPending
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHIF_SWTTIME_LOCAL_INLINE FUNC(void, ETHIF_SWTTIME_INLINE_CODE) EthIf_SetSwtTimeStampTxInfoPending(
  EthIf_SwtTsTxCtxtPoolIterType swtTsTxCtxtPoolElemIdx)
{
  /* #10 Set the flags to indicate the context the information wasn't retrieved for yet. */
  EthIf_SetProcFlagsOfSwtTsTxCtxtPool(swtTsTxCtxtPoolElemIdx, (ETHIF_SWT_TIMESTAMP_PROC_FLAG_INGRESS_TS_PENDING |       /* SBSW_ETHIF_INT_FCT_IDX_PASS */
                                                               ETHIF_SWT_TIMESTAMP_PROC_FLAG_EGRESS_TS_PENDING    ));
} /* EthIf_SetSwtTimeStampTxInfoPending() */
#endif /* ETHIF_ETHSWT_TIME_STAMP_SUPPORT */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#if ( ETHIF_ETHSWT_TIME_STAMP_SUPPORT == STD_ON )                                                                       /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 * EthIf_SwitchEnableEgressTimeStamp
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
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SwitchEnableEgressTimeStamp(
          uint8                                             EthIfCtrlIdx,
          uint8                                             BufIdx,
  P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, ETHIF_APPL_DATA)  MgmtInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( EthIfCtrlIdx >= EthIf_GetSizeOfEthIfCtrl() )
  {
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else if( BufIdx > EthIf_GetMaxTxBufIdxForEthIfCtrl(EthIfCtrlIdx) )
  {
    errorId = ETHIF_E_INV_PARAM;
  }
  else if( MgmtInfo == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthCtrlIdxOfEthIfCtrlType ethCtrlIdx = EthIf_GetEthCtrlIdxOfEthIfCtrl(EthIfCtrlIdx);
    EthIf_TxContextIterType txCtxtIdx = EthIf_CalcTxCtxtIdx(ethCtrlIdx, BufIdx);

    /* #30 Check if tx buffer was acquired during EthIf_ProvideTxBuffer() and EthIf_Transmit() wasn't called yet */
    if ( (EthIf_IsValidOfTxContext(txCtxtIdx) == TRUE) &&
         (EthIf_GetEthIfCtrlIdxOfTxContext(txCtxtIdx) == EthIfCtrlIdx) )
    {
      /* #40 Check if driver provides the API */
      if( EthIf_IsEthSwtDrvApiUsedOfEthIfCtrl(EthIfCtrlIdx) == TRUE )
      {
        EthIf_EthSwtDrvApiIdxOfEthIfCtrlType ethSwtDrvIdx = EthIf_GetEthSwtDrvApiIdxOfEthIfCtrl(EthIfCtrlIdx);

        if( EthIf_GetSwtEnableEgressTimeStampOfEthSwtDrvApi(ethSwtDrvIdx) != NULL_PTR )
        {
          EthIf_SwtTsTxCtxtPoolIterType swtTsTCtxtPoolElemIdx;

          /* #400 Retrieve the tx context element */
          if( EthIf_GetSwtTimeStampTxInfo(ethCtrlIdx,
                                          BufIdx,
                                          MgmtInfo->FrameId,
                                          &swtTsTCtxtPoolElemIdx) == TRUE )                                             /* SBSW_ETHIF_REF_OF_STACK_VAR */
          {
            EthSwt_MgmtInfoType ethIfMgmtInfo;

            /* #410 Prepare information for driver call */
            ethIfMgmtInfo.SwitchIdx = MgmtInfo->SwitchIdx;
            ethIfMgmtInfo.PortIdx   = MgmtInfo->PortIdx;
            ethIfMgmtInfo.FrameId   = MgmtInfo->FrameId;

            /* #420 Redirect call to the driver */
            retVal = EthIf_GetSwtEnableEgressTimeStampOfEthSwtDrvApi(ethSwtDrvIdx)(EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                                                   BufIdx,
                                                                                   (P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, ETHIF_CONST))&ethIfMgmtInfo); /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_REF_OF_STACK_VAR_PARAM_PTR_CSL03 */

            if( retVal == E_OK )
            {
              /* #430 Arm tx context element for processing in timestamp indication context */
              EthIf_SetSwtTimeStampTxInfoPending(swtTsTCtxtPoolElemIdx);
            }
          }
        }
      }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_QM_FEAT_INNER */
      else
      {
        errorId = ETHIF_E_INV_DRIVER_API_CALL;
      }
# endif /* ETHIF_DEV_ERROR_DETECT */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #50 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_SWITCH_ENABLE_EGRESS_TIME_STAMP, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_SwitchEnableEgressTimeStamp() */ /* PRQA S 6080, 6030 */ /* MD_MSR_STMIF, MD_MSR_STCYC */

/**********************************************************************************************************************
 *  EthIf_SwitchEgressTimeStampIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, ETHIF_CODE) EthIf_SwitchEgressTimeStampIndication(
          uint8                                             CtrlIdx,
    P2VAR(uint8,               AUTOMATIC, ETHIF_APPL_VAR)   DataPtr,
  P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, ETHIF_APPL_DATA)  MgmtInfo,
  P2CONST(Eth_TimeStampType,   AUTOMATIC, ETHIF_APPL_DATA)  timeStamp)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHIF_E_NO_ERROR;
  EthIf_EthCtrlIterType ethCtrlIdx = EthIf_QueryForEthIfEthCtrl(CtrlIdx);

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( ethCtrlIdx >= EthIf_GetSizeOfEthCtrl() )
  {
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else if( MgmtInfo == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else if( EthIf_IsSwtTsRxCtxtPoolUsedOfEthCtrl(ethCtrlIdx) == FALSE )
  {
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    boolean                 isIndicationRequested = FALSE;
    EthIf_EthIfCtrlIterType ethIfCtrlIdx          = ETHIF_MIN_ETHIFCTRLIDXOFSWTTSRXCTXTPOOL;
    EthIf_UserIterType      userIdx               = ETHIF_MIN_USERIDXOFSWTTSRXCTXTPOOL;

    /* #30 Check if there was information related to the time stamp stored either during rx or tx processing. */
    if( EthIf_RestoreSwtTimeStampTxInfo(ethCtrlIdx,
                                        ETHIF_SWT_TIMESTAMP_PROC_FLAG_EGRESS_TS_PENDING,
                                        MgmtInfo->FrameId,
                                        &ethIfCtrlIdx,
                                        &userIdx,
                                        &DataPtr) == TRUE )                                                             /* SBSW_ETHIF_INT_FCT_PUB_PARAM_PTR_PASS_AND_REF_OF_STACK_VAR */
    {
      isIndicationRequested = TRUE;
    }
    else if( EthIf_RestoreSwtTimeStampRxInfo(ethCtrlIdx,
                                             ETHIF_SWT_TIMESTAMP_PROC_FLAG_EGRESS_TS_PENDING,
                                             MgmtInfo->FrameId,
                                             &ethIfCtrlIdx,
                                             &userIdx,
                                             &DataPtr) == TRUE )                                                        /* SBSW_ETHIF_INT_FCT_PUB_PARAM_PTR_PASS_AND_REF_OF_STACK_VAR */
    {
      isIndicationRequested = TRUE;
    }
    else
    {
      /* Either RX nor TX information was retrieved -> indication must not be called */
    }

    /* #40 If information was stored and could be retrieved inform the related owner about the time stamp information */
    if( isIndicationRequested == TRUE )
    {
      /* handle upper layer indication */
      EthIf_EgressTsIndsIndIterType indIdx;

      for( indIdx = EthIf_GetEgressTsIndsIndStartIdxOfUser(userIdx);
           indIdx < EthIf_GetEgressTsIndsIndEndIdxOfUser(userIdx);
           indIdx++ )
      {
        EthIf_EgressTsIndsIndType egrTsIndIdx = EthIf_GetEgressTsIndsInd(indIdx);
        EthIf_GetEgressTsInds(egrTsIndIdx)((uint8)ethIfCtrlIdx,
                                           DataPtr,
                                           MgmtInfo,
                                           timeStamp);                                                                  /* SBSW_ETHIF_USERAPI_FCT_PTR_WITH_PUB_PARAM_PTR_CSL03 */
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #50 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_SWITCH_EGRESS_TIME_STAMP_INDICATION, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

} /* EthIf_SwitchEgressTimeStampIndication() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  EthIf_SwitchIngressTimeStampIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, ETHIF_CODE) EthIf_SwitchIngressTimeStampIndication(
          uint8                                             CtrlIdx,
    P2VAR(uint8,               AUTOMATIC, ETHIF_APPL_VAR)   DataPtr,
  P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, ETHIF_APPL_DATA)  MgmtInfo,
  P2CONST(Eth_TimeStampType,   AUTOMATIC, ETHIF_APPL_DATA)  timeStamp)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHIF_E_NO_ERROR;
  EthIf_EthCtrlIterType ethCtrlIdx = EthIf_QueryForEthIfEthCtrl(CtrlIdx);

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( ethCtrlIdx >= EthIf_GetSizeOfEthCtrl()  )
  {
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else if( MgmtInfo == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else if( EthIf_IsSwtTsRxCtxtPoolUsedOfEthCtrl(CtrlIdx) == FALSE )
  {
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    boolean                 isIndicationRequested = FALSE;
    EthIf_EthIfCtrlIterType ethIfCtrlIdx          = ETHIF_MIN_ETHIFCTRLIDXOFSWTTSRXCTXTPOOL;
    EthIf_UserIterType      userIdx               = ETHIF_MIN_USERIDXOFSWTTSRXCTXTPOOL;

    /* #30 Check if there was information related to the time stamp stored either during rx or tx processing. */
    if( EthIf_RestoreSwtTimeStampTxInfo(ethCtrlIdx,
                                        ETHIF_SWT_TIMESTAMP_PROC_FLAG_INGRESS_TS_PENDING,
                                        MgmtInfo->FrameId,
                                        &ethIfCtrlIdx,
                                        &userIdx,
                                        &DataPtr) == TRUE )                                                             /* SBSW_ETHIF_INT_FCT_PUB_PARAM_PTR_PASS_AND_REF_OF_STACK_VAR */
    {
      isIndicationRequested = TRUE;
    }
    else if( EthIf_RestoreSwtTimeStampRxInfo(ethCtrlIdx,
                                             ETHIF_SWT_TIMESTAMP_PROC_FLAG_INGRESS_TS_PENDING,
                                             MgmtInfo->FrameId,
                                             &ethIfCtrlIdx,
                                             &userIdx,
                                             &DataPtr) == TRUE )                                                        /* SBSW_ETHIF_INT_FCT_PUB_PARAM_PTR_PASS_AND_REF_OF_STACK_VAR */
    {
      isIndicationRequested = TRUE;
    }
    else
    {
      /* Either RX nor TX information was retrieved -> indication must not be called */
    }

    /* #40 If information was stored and could be retrieved inform the related owner about the time stamp information */
    if( isIndicationRequested == TRUE )
    {
      /* handle upper layer indication */
      EthIf_IngressTsIndsIndIterType indIdx;

      for( indIdx = EthIf_GetIngressTsIndsIndStartIdxOfUser(userIdx);
           indIdx < EthIf_GetIngressTsIndsIndEndIdxOfUser(userIdx);
           indIdx++ )
      {
        EthIf_IngressTsIndsIndType ingrTsIndIdx = EthIf_GetIngressTsIndsInd(indIdx);
        EthIf_GetIngressTsInds(ingrTsIndIdx)((uint8)ethIfCtrlIdx,
                                             DataPtr,
                                             MgmtInfo,
                                             timeStamp);                                                                /* SBSW_ETHIF_USERAPI_FCT_PTR_WITH_PUB_PARAM_PTR_CSL03 */
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #50 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_SWITCH_INGRESS_TIME_STAMP_INDICATION, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

} /* EthIf_SwitchIngressTimeStampIndication() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

#endif /* ETHIF_ETHSWT_TIME_STAMP_SUPPORT */

#define ETHIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_SwtTime.c
 *********************************************************************************************************************/

