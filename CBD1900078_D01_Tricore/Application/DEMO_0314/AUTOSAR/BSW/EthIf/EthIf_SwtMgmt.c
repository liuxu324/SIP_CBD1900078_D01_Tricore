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
/*!        \file  EthIf_SwtMgmt.c
 *        \brief  EthIf SwtMgmt public API source file
 *
 *      \details  Implementation of the public API of the sub-module SwtMgmt of EthIf.
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

#define ETHIF_SWTMGMT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
#include "EthIf_SwtMgmt.h"
#include "EthIf_SwtMgmt_Cbk.h"
#include "EthIf_SwtMgmt_Int.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of Msn header file */
#if (  (ETHIF_SW_MAJOR_VERSION != (10u)) \
    || (ETHIF_SW_MINOR_VERSION != (0u)) \
    || (ETHIF_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of EthIf_SwtMgmt.c and EthIf.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (ETHIF_CFG_MAJOR_VERSION != (7u)) \
    || (ETHIF_CFG_MINOR_VERSION != (0u)) )
# error "Version numbers of EthIf_SwtMgmt.c and EthIf_Cfg.h are inconsistent!"
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

#if !defined (ETHIF_SWTMGMT_LOCAL)                                                                                      /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_SWTMGMT_LOCAL static
#endif

#if !defined (ETHIF_SWTMGMT_LOCAL_INLINE)                                                                               /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_SWTMGMT_LOCAL_INLINE LOCAL_INLINE
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

#if ( ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT == STD_ON )                                                                 /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 * EthIf_RestoreSwtMgmtRxInfo
 **********************************************************************************************************************/
/*! \brief          Restores frame management related information stored during reception of a frame
 *  \details        Function restores information related to management information for being able to pass the information
 *                  to the designated upper layer.
 *  \param[in]      ethCtrlIdx        Eth controller the management information is related to
 *                                    [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \param[in]      frameId           Identifier of the frame the management information is related to
 *  \param[out]     ethIfCtrlIdxPtr   EthIf controller the frame related to the management information was passed to
 *  \param[out]     frameOwnerIdxPtr  User the frame related to the management information was passed to
 *  \param[out]     dataPtr           Pointer to the payload of the frame related to the management information passed to
 *                                    the user
 *  \return         TRUE - there was information related to the management information stored previously
 *  \return         FALSE - there was no information related to the management information stored previously
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 **********************************************************************************************************************/
ETHIF_SWTMGMT_LOCAL_INLINE FUNC(boolean, ETHIF_SWTMGMT_INLINE_CODE) EthIf_RestoreSwtMgmtRxInfo(
        EthIf_EthCtrlIterType                                ethCtrlIdx,
        Eth_FrameIdType                                      frameId,
  P2VAR(EthIf_EthIfCtrlIterType,  AUTOMATIC, ETHIF_APPL_VAR) ethIfCtrlIdxPtr,
  P2VAR(EthIf_UserIterType,       AUTOMATIC, ETHIF_APPL_VAR) frameOwnerIdxPtr,
  P2VAR(EthIf_FrameBufferPtrType, AUTOMATIC, ETHIF_APPL_VAR) dataPtr);
#endif /* ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if ( ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT == STD_ON )                                                                 /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 * EthIf_RestoreSwtMgmtRxInfo
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
ETHIF_SWTMGMT_LOCAL_INLINE FUNC(boolean, ETHIF_SWTMGMT_INLINE_CODE) EthIf_RestoreSwtMgmtRxInfo(
        EthIf_EthCtrlIterType                                ethCtrlIdx,
        Eth_FrameIdType                                      frameId,
  P2VAR(EthIf_EthIfCtrlIterType,  AUTOMATIC, ETHIF_APPL_VAR) ethIfCtrlIdxPtr,
  P2VAR(EthIf_UserIterType,       AUTOMATIC, ETHIF_APPL_VAR) frameOwnerIdxPtr,
  P2VAR(EthIf_FrameBufferPtrType, AUTOMATIC, ETHIF_APPL_VAR) dataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_SwtMgmtRxCtxtPoolIterType poolElemIdx;
  boolean result;

  /* ----- Implementation ----------------------------------------------- */
  result = FALSE;

  /* #10 Enter exclusive area (Reason: Ensure consistency of switch management information elements) */
  EthIf_EnterExclusiveArea(MGMT_RX_CTXT_POOL); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Query for the information related to the frame */
  for( poolElemIdx = EthIf_GetSwtMgmtRxCtxtPoolStartIdxOfEthCtrl(ethCtrlIdx);
       poolElemIdx < EthIf_GetSwtMgmtRxCtxtPoolEndIdxOfEthCtrl(ethCtrlIdx);
       poolElemIdx++ )
  {
    if( EthIf_GetFrameIdOfSwtMgmtRxCtxtPool(poolElemIdx) == frameId )
    {
      /* #200 Entry found -> retrieve the information store for being able to pass the time stamp to the
       *      designated upper layer */
      (*dataPtr)          = EthIf_GetDataPtrOfSwtMgmtRxCtxtPool(poolElemIdx);                                           /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
      (*ethIfCtrlIdxPtr)  = EthIf_GetEthIfCtrlIdxOfSwtMgmtRxCtxtPool(poolElemIdx);                                      /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
      (*frameOwnerIdxPtr) = EthIf_GetUserIdxOfSwtMgmtRxCtxtPool(poolElemIdx);                                           /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
      /* #210 Information was restored so element can be invalidated */
      EthIf_SetDataPtrOfSwtMgmtRxCtxtPool(poolElemIdx, NULL_PTR);                                                       /* SBSW_ETHIF_COMMON_CSL03 */
      EthIf_SetFrameIdOfSwtMgmtRxCtxtPool(poolElemIdx, ETH_INVALID_FRAME_ID);                                           /* SBSW_ETHIF_COMMON_CSL03 */
      EthIf_SetEthIfCtrlIdxOfSwtMgmtRxCtxtPool(poolElemIdx, EthIf_GetSizeOfEthIfCtrl());                                /* SBSW_ETHIF_COMMON_CSL03 */
      EthIf_SetUserIdxOfSwtMgmtRxCtxtPool(poolElemIdx, EthIf_GetSizeOfUser());                                          /* SBSW_ETHIF_COMMON_CSL03 */
      result = TRUE;
      break;
    }
  }

  /* #30 Leave exclusive area -> Processing of elements finished */
  EthIf_ExitExclusiveArea(MGMT_RX_CTXT_POOL); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return result;
} /* EthIf_RestoreSwtMgmtRxInfo() */
#endif /* ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#if ( ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT == STD_ON )                                                                 /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 * EthIf_SetSwitchMgmtInfo
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
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SetSwitchMgmtInfo(
          uint8                                         EthIfCtrlIdx,
          uint8                                         BufIdx,
  P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, ETHIF_CONST)  MgmtInfo)
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
      if( EthIf_IsEthSwtDrvApiUsedOfEthIfCtrl(EthIfCtrlIdx) )
      {
        EthIf_EthSwtDrvApiIdxOfEthIfCtrlType ethSwtDrvIdx = EthIf_GetEthSwtDrvApiIdxOfEthIfCtrl(EthIfCtrlIdx);

        if( EthIf_GetSetSwtMgmtInfoOfEthSwtDrvApi(ethSwtDrvIdx) != NULL_PTR )
        {
          /* #400 Redirect call to the driver */
          retVal = EthIf_GetSetSwtMgmtInfoOfEthSwtDrvApi(ethSwtDrvIdx)(EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                                       BufIdx,
                                                                       MgmtInfo);                                       /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_CSL03 */
        }
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #50 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_SET_SWITCH_MGMT_INFO, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_SetSwitchMgmtInfo() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  EthIf_SwitchMgmtInfoIndication
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
FUNC(void, ETHIF_CODE) EthIf_SwitchMgmtInfoIndication(
          uint8                                             CtrlIdx,
    P2VAR(uint8,               AUTOMATIC, ETHIF_APPL_VAR)   DataPtr,
  P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, ETHIF_APPL_DATA)  MgmtInfo)
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
  else if( DataPtr == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else if( EthIf_IsSwtMgmtRxCtxtPoolUsedOfEthCtrl(ethCtrlIdx) == FALSE )
  {
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthIfCtrlIterType ethIfCtrlIdx = ETHIF_MIN_ETHIFCTRLIDXOFSWTMGMTRXCTXTPOOL;
    EthIf_UserIterType userIdx = ETHIF_MIN_USERIDXOFSWTMGMTRXCTXTPOOL;

    /* #30 Check if there was information to redirect the call stored */
    if( EthIf_RestoreSwtMgmtRxInfo(ethCtrlIdx,
                                   MgmtInfo->FrameId,
                                   &ethIfCtrlIdx,
                                   &userIdx,
                                   &DataPtr) == TRUE )                                                                  /* SBSW_ETHIF_REF_OF_STACK_VAR */
    {
      EthIf_MgmtInfoIndsIndIterType indIdx;

      /* #300 Inform owner about frame related management information from switch if has registered for the indication */
      for( indIdx = EthIf_GetMgmtInfoIndsIndStartIdxOfUser(userIdx);
           indIdx < EthIf_GetMgmtInfoIndsIndEndIdxOfUser(userIdx);
           indIdx++ )
      {
        EthIf_MgmtInfoIndsIndType mgmtIndIdx = EthIf_GetMgmtInfoIndsInd(indIdx);
        EthIf_GetMgmtInfoInds(mgmtIndIdx)((uint8)ethIfCtrlIdx, DataPtr, MgmtInfo);                                      /* SBSW_ETHIF_USERAPI_FCT_PTR_WITH_PUB_PARAM_PTR_CSL03 */
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_SWITCH_MGMT_INFO_INDICATION, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

} /* EthIf_IngressSwitchMngmtInfoIndication() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT */

#define ETHIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_SwtMgmt.c
 *********************************************************************************************************************/

