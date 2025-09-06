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
/*!        \file  EthIf_SwtTime_Int.c
 *        \brief  EthIf SwtTime internal source file
 *
 *      \details  Contains the definition of data and implementation of functions of the sub-module SwtTime of EthIf
 *                only to be used EthIf internal.
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

#define ETHIF_SWTTIME_INT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
#include "EthIf_SwtTime_Int.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

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

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthIf_SwtTime_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHIF_CODE) EthIf_SwtTime_Init( void )
{

} /* EthIf_SwtTime_Init() */

#if ( ETHIF_ETHSWT_TIME_STAMP_SUPPORT == STD_ON )                                                                       /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 *  EthIf_InitiateTxSwtTimeStampInfoProc
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, ETHIF_CODE) EthIf_InitiateTxSwtTimeStampInfoProc(
        EthIf_EthCtrlIterType              ethCtrlIdx,
        EthIf_EthIfCtrlIterType            ethIfCtrlIdx,
        uint8                              bufIdx,
        uint16                             bufLen,
  P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR)  dataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_SwtTsTxCtxtPoolIterType poolElemIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Ensure consistency of switch transmission timestamp elements) */
  EthIf_EnterExclusiveArea(SWT_TIME_STAMP_TX_CTXT_POOL); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Query for a free element to handle the transmission switch time stamping processing */
  for( poolElemIdx = EthIf_GetSwtTsTxCtxtPoolStartIdxOfEthCtrl(ethCtrlIdx);
       poolElemIdx < EthIf_GetSwtTsTxCtxtPoolEndIdxOfEthCtrl(ethCtrlIdx);
       poolElemIdx++ )
  {
    if( EthIf_GetStateOfSwtTsTxCtxtPool(poolElemIdx) == ETHIF_TX_SWT_TS_ELEM_FREE_STATEOFSWTTSTXCTXTPOOL )
    {
      Eth_FrameIdType frameId = EthIf_GetFrameId(dataPtr, bufLen);                                                      /* SBSW_ETHIF_INT_FCT_PARAM_PTR_PASS */
      /* #200 Entry found -> set the information needed to handle switch time stamping processing */
      EthIf_SetDataPtrOfSwtTsTxCtxtPool(poolElemIdx, dataPtr);
      EthIf_SetBufLenOfSwtTsTxCtxtPool(poolElemIdx, bufLen);                                                            /* SBSW_ETHIF_COMMON_CSL03 */
      EthIf_SetFrameIdOfSwtTsTxCtxtPool(poolElemIdx, frameId);                                                          /* SBSW_ETHIF_COMMON_CSL03 */
      EthIf_SetEthIfCtrlIdxOfSwtTsTxCtxtPool(poolElemIdx, (EthIf_EthIfCtrlIdxOfSwtTsTxCtxtPoolType)ethIfCtrlIdx);       /* SBSW_ETHIF_COMMON_CSL03 */
      EthIf_SetBufIdxOfSwtTsTxCtxtPool(poolElemIdx, bufIdx);                                                            /* SBSW_ETHIF_COMMON_CSL03 */
      EthIf_SetUserIdxOfSwtTsTxCtxtPool(poolElemIdx, EthIf_GetSizeOfUser());                                            /* SBSW_ETHIF_COMMON_CSL03 */
      EthIf_SetProcFlagsOfSwtTsTxCtxtPool(poolElemIdx, 0x00u);                                                          /* SBSW_ETHIF_COMMON_CSL03 */
      EthIf_SetStateOfSwtTsTxCtxtPool(poolElemIdx, ETHIF_TX_SWT_TS_ELEM_ALLOC_STATEOFSWTTSTXCTXTPOOL);                  /* SBSW_ETHIF_COMMON_CSL03 */
      break;
    }
  }

  /* #30 Leave exclusive area -> Processing on elements finished */
  EthIf_ExitExclusiveArea(SWT_TIME_STAMP_TX_CTXT_POOL); /* PRQA S 3109 */ /* MD_MSR_14.3 */
} /* EthIf_InitiateTxSwtTimeStampInfoProc() */

/**********************************************************************************************************************
 *  EthIf_ArmTxSwtTimeStampInfoProc
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
 */
FUNC(void, ETHIF_CODE) EthIf_ArmTxSwtTimeStampInfoProc(
  EthIf_EthCtrlIterType ethCtrlIdx,
  uint8                 bufIdx,
  EthIf_UserIterType    ownerIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_SwtTsTxCtxtPoolIterType poolElemIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Ensure consistency of switch transmission timestamp elements) */
  EthIf_EnterExclusiveArea(SWT_TIME_STAMP_TX_CTXT_POOL); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Query for the information related to the frame buffer */
  for( poolElemIdx = EthIf_GetSwtTsTxCtxtPoolStartIdxOfEthCtrl(ethCtrlIdx);
       poolElemIdx < EthIf_GetSwtTsTxCtxtPoolEndIdxOfEthCtrl(ethCtrlIdx);
       poolElemIdx++ )
  {
    if( EthIf_GetStateOfSwtTsTxCtxtPool(poolElemIdx) == ETHIF_TX_SWT_TS_ELEM_ALLOC_STATEOFSWTTSTXCTXTPOOL )
    {
      Eth_FrameIdType frameId = EthIf_GetFrameId(EthIf_GetDataPtrOfSwtTsTxCtxtPool(poolElemIdx), EthIf_GetBufLenOfSwtTsTxCtxtPool(poolElemIdx)); /* SBSW_ETHIF_SWT_TS_TX_CTXT_PARAM_PTR_PASS */
      /* check if buffer index isn't used more than once (indicated by a changed frame id) */
      if( (EthIf_GetBufIdxOfSwtTsTxCtxtPool(poolElemIdx) == bufIdx) &&
          (frameId == EthIf_GetFrameIdOfSwtTsTxCtxtPool(poolElemIdx)) )
      {
        /* #200 Entry found -> Check if switch time stamping was requested for the frame.
         *                     If so, store the owner information and keep the information for later usage in
         *                     EthIf_SwitchIngressTimeStampIndication()/EthIf_SwitchEgressTimeStampIndication(). */
        if( EthIf_GetProcFlagsOfSwtTsTxCtxtPool(poolElemIdx) != 0x00U )
        {
          EthIf_SetUserIdxOfSwtTsTxCtxtPool(poolElemIdx, (EthIf_UserIdxOfSwtTsTxCtxtPoolType)ownerIdx);                   /* SBSW_ETHIF_COMMON_CSL03 */
          EthIf_SetStateOfSwtTsTxCtxtPool(poolElemIdx, ETHIF_TX_SWT_TS_ELEM_TX_PEND_STATEOFSWTTSTXCTXTPOOL);              /* SBSW_ETHIF_COMMON_CSL03 */
        }
        break;
      }
    }
  }

  /* #30 Leave exclusive area -> Processing of elements finished */
  EthIf_ExitExclusiveArea(SWT_TIME_STAMP_TX_CTXT_POOL); /* PRQA S 3109 */ /* MD_MSR_14.3 */
} /* EthIf_ArmTxSwtTimeStampInfoProc() */

/**********************************************************************************************************************
 *  EthIf_FinishTxSwtTimeStampInfoProc
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
 */
FUNC(void, ETHIF_CODE) EthIf_FinishTxSwtTimeStampInfoProc(
  EthIf_EthCtrlIterType  ethCtrlIdx,
  uint8                  bufIdx,
  uint16                 len)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_SwtTsTxCtxtPoolIterType poolElemIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Ensure consistency of switch transmission timestamp elements) */
  EthIf_EnterExclusiveArea(SWT_TIME_STAMP_TX_CTXT_POOL); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Query for the information related to the frame buffer */
  for( poolElemIdx = EthIf_GetSwtTsTxCtxtPoolStartIdxOfEthCtrl(ethCtrlIdx);
       poolElemIdx < EthIf_GetSwtTsTxCtxtPoolEndIdxOfEthCtrl(ethCtrlIdx);
       poolElemIdx++ )
  {
    if( (EthIf_GetStateOfSwtTsTxCtxtPool(poolElemIdx) == ETHIF_TX_SWT_TS_ELEM_ALLOC_STATEOFSWTTSTXCTXTPOOL) ||
        (EthIf_GetStateOfSwtTsTxCtxtPool(poolElemIdx) == ETHIF_TX_SWT_TS_ELEM_TX_PEND_STATEOFSWTTSTXCTXTPOOL) )
    {
      Eth_FrameIdType frameId = EthIf_GetFrameId(EthIf_GetDataPtrOfSwtTsTxCtxtPool(poolElemIdx), EthIf_GetBufLenOfSwtTsTxCtxtPool(poolElemIdx)); /* SBSW_ETHIF_SWT_TS_TX_CTXT_PARAM_PTR_PASS */
      /* check if buffer index isn't used more than once (indicated by a changed frame id) */
      if( (EthIf_GetBufIdxOfSwtTsTxCtxtPool(poolElemIdx) == bufIdx) &&
          (frameId == EthIf_GetFrameIdOfSwtTsTxCtxtPool(poolElemIdx)) )
      {
        /* #200 Entry found -> Check if switch time stamping wasn't requested for the frame or transmit call was a
         *                     trigger for releasing the buffer without transmission.
         *                     If so, invalidate the information so it can be used for another frame. */
        if( (EthIf_GetProcFlagsOfSwtTsTxCtxtPool(poolElemIdx) == 0x00U) || (len == ETHIF_TX_BUFFER_RELEASE_LEN) )
        {
          EthIf_SetDataPtrOfSwtTsTxCtxtPool(poolElemIdx, NULL_PTR);                                                     /* SBSW_ETHIF_INT_FCT_PARAM_PTR_NULL_CSL_STRUCT_MEM_CSL03 */
          EthIf_SetFrameIdOfSwtTsTxCtxtPool(poolElemIdx, ETH_INVALID_FRAME_ID);                                         /* SBSW_ETHIF_COMMON_CSL03 */
          EthIf_SetBufIdxOfSwtTsTxCtxtPool(poolElemIdx, EthIf_GetMaxTxBufPerEthCtrl());                                 /* SBSW_ETHIF_COMMON_CSL03 */
          EthIf_SetStateOfSwtTsTxCtxtPool(poolElemIdx, ETHIF_TX_SWT_TS_ELEM_FREE_STATEOFSWTTSTXCTXTPOOL);               /* SBSW_ETHIF_COMMON_CSL03 */
        }
        break;
      }
    }
  }

  /* #30 Leave exclusive area -> Processing of elements finished */
  EthIf_ExitExclusiveArea(SWT_TIME_STAMP_TX_CTXT_POOL); /* PRQA S 3109 */ /* MD_MSR_14.3 */
} /* EthIf_FinishTxSwtTimeStampInfoProc() */

/**********************************************************************************************************************
 *  EthIf_InitiateRxSwtTimeStampInfoProc
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, ETHIF_CODE) EthIf_InitiateRxSwtTimeStampInfoProc(
          EthIf_EthCtrlIterType                                      ethCtrlIdx,
          EthIf_UserIterType                                         ownerIdx,
  P2CONST(EthIf_UlRxIndiactionDataType, AUTOMATIC, ETHIF_APPL_DATA)  ulRxIndicationData)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_SwtTsRxCtxtPoolIterType poolElemIdx;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Enter exclusive area (Reason: Ensure consistency of switch reception timestamp elements) */
  EthIf_EnterExclusiveArea(SWT_TIME_STAMP_RX_CTXT_POOL); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Query for a free element to handle the reception switch time stamping processing */
  for( poolElemIdx = EthIf_GetSwtTsRxCtxtPoolStartIdxOfEthCtrl(ethCtrlIdx);
       poolElemIdx < EthIf_GetSwtTsRxCtxtPoolEndIdxOfEthCtrl(ethCtrlIdx);
       poolElemIdx++ )
  {
    if( EthIf_GetFrameIdOfSwtTsRxCtxtPool(poolElemIdx) == ETH_INVALID_FRAME_ID )
    {
      Eth_FrameIdType frameId = EthIf_GetFrameId(ulRxIndicationData->PayloadPtr, ulRxIndicationData->PayloadLen);       /* SBSW_ETHIF_INT_FCT_PARAM_PTR_PASS */

      /* #200 Entry found -> set the information needed to handle switch time stamping processing */
      EthIf_SetDataPtrOfSwtTsRxCtxtPool(poolElemIdx, ulRxIndicationData->PayloadPtr);                                   /* SBSW_ETHIF_INT_FCT_PARAM_PTR_CSL_STRUCT_MEM_CSL03 */
      EthIf_SetFrameIdOfSwtTsRxCtxtPool(poolElemIdx, frameId);                                                          /* SBSW_ETHIF_COMMON_CSL03 */
      EthIf_SetEthIfCtrlIdxOfSwtTsRxCtxtPool(poolElemIdx, (EthIf_EthIfCtrlIdxOfSwtTsRxCtxtPoolType)ulRxIndicationData->EthIfCtrlIdx); /* SBSW_ETHIF_COMMON_CSL03 */
      EthIf_SetUserIdxOfSwtTsRxCtxtPool(poolElemIdx, (EthIf_UserIdxOfSwtTsRxCtxtPoolType)ownerIdx);                     /* SBSW_ETHIF_COMMON_CSL03 */
      EthIf_SetProcFlagsOfSwtTsRxCtxtPool(poolElemIdx, (ETHIF_SWT_TIMESTAMP_PROC_FLAG_INGRESS_TS_PENDING |              /* SBSW_ETHIF_COMMON_CSL03 */
                                                        ETHIF_SWT_TIMESTAMP_PROC_FLAG_EGRESS_TS_PENDING    ));
      break;
    }
  }

  /* #30 Leave exclusive area -> Processing of elements finished */
  EthIf_ExitExclusiveArea(SWT_TIME_STAMP_RX_CTXT_POOL); /* PRQA S 3109 */ /* MD_MSR_14.3 */
} /* EthIf_InitiateRxSwtTimeStampInfoProc() */
#endif /* ETHIF_ETHSWT_TIME_STAMP_SUPPORT */

#define ETHIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_SwtTime_Int.c
 *********************************************************************************************************************/

