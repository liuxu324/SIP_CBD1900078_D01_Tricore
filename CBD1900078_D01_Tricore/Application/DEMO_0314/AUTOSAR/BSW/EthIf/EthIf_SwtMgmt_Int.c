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
/*!        \file  EthIf_SwtMgmt_Int.c
 *        \brief  EthIf SwtMgmt internal source file
 *
 *      \details  Contains the definition of data and implementation of functions of the sub-module SwtMgmt of EthIf
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

#define ETHIF_SWTMGMT_INT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
#include "EthIf_SwtMgmt_Int.h"

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
 *  EthIf_SwtMgmt_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHIF_CODE) EthIf_SwtMgmt_Init( void )
{

} /* EthIf_SwtMgmt_Init() */


#if ( ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT == STD_ON )                                                                 /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 *  EthIf_InitiateRxSwtMgmtInfoProc
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, ETHIF_CODE) EthIf_InitiateRxSwtMgmtInfoProc(
          EthIf_EthCtrlIterType                                      ethCtrlIdx,
          EthIf_UserIterType                                         ownerIdx,
  P2CONST(EthIf_UlRxIndiactionDataType, AUTOMATIC, ETHIF_APPL_DATA)  ulRxIndicationData)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_SwtMgmtRxCtxtPoolIterType poolElemIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Ensure consistency of switch management information elements) */
  EthIf_EnterExclusiveArea(MGMT_RX_CTXT_POOL); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Query for a free element to handle the reception switch frame management information processing */
  for( poolElemIdx = EthIf_GetSwtMgmtRxCtxtPoolStartIdxOfEthCtrl(ethCtrlIdx);
       poolElemIdx < EthIf_GetSwtMgmtRxCtxtPoolEndIdxOfEthCtrl(ethCtrlIdx);
       poolElemIdx++ )
  {
    if( EthIf_GetFrameIdOfSwtMgmtRxCtxtPool(poolElemIdx) == ETH_INVALID_FRAME_ID )
    {
      Eth_FrameIdType frameId = EthIf_GetFrameId(ulRxIndicationData->PayloadPtr, ulRxIndicationData->PayloadLen);       /* SBSW_ETHIF_INT_FCT_PARAM_PTR_PASS */
      /* #200 Entry found -> set the information needed to handle switch frame management information processing */
      EthIf_SetDataPtrOfSwtMgmtRxCtxtPool(poolElemIdx, ulRxIndicationData->PayloadPtr);
      EthIf_SetFrameIdOfSwtMgmtRxCtxtPool(poolElemIdx, frameId);                                                        /* SBSW_ETHIF_COMMON_CSL03 */
      EthIf_SetEthIfCtrlIdxOfSwtMgmtRxCtxtPool(poolElemIdx,(EthIf_EthIfCtrlIdxOfSwtMgmtRxCtxtPoolType)ulRxIndicationData->EthIfCtrlIdx); /* SBSW_ETHIF_COMMON_CSL03 */
      EthIf_SetUserIdxOfSwtMgmtRxCtxtPool(poolElemIdx, (EthIf_UserIdxOfSwtMgmtRxCtxtPoolType)ownerIdx);                 /* SBSW_ETHIF_COMMON_CSL03 */
      break;
    }
  }

  /* #30 Leave exclusive area -> Processing of elements finished */
  EthIf_ExitExclusiveArea(MGMT_RX_CTXT_POOL); /* PRQA S 3109 */ /* MD_MSR_14.3 */
} /* EthIf_InitiateRxSwtMgmtInfoProc() */

#endif /* ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT */

#define ETHIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_SwtMgmt_Int.c
 *********************************************************************************************************************/

