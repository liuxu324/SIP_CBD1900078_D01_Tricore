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
 *  -------------------------------------------------------------------------------------------------------------------
 *         \file  EthTSyn_SwtMgmt_Int.h
 *        \brief  EthTSyn Switch Management internal header file
 *
 *      \details  Contains internal definitions and declarations used by EthTSyn (for Switch Management) only
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined(ETHTSYN_SWT_MGMT_INT_H)
# define ETHTSYN_SWT_MGMT_INT_H


/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthTSyn_Types.h"

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#  define ETHTSYN_START_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Init
 *********************************************************************************************************************/
/*! \brief        Initializes the EthTSyn switch management parts.
 *  \details      Initializes all component variables directly related to the SwtMgmt sub-module.
 *  \pre          EthTSyn_Slave_Init() was called
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \note         This function must be called before using the module
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Init(void);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_ProcessSmSiteSyncSync
 *********************************************************************************************************************/
/*! \brief      Processing of the Site Sync Sync state-machine.
 *  \details    -
 *  \param[in]  TimeDomainIdx    Index of the TimeDomain that should be processed
 *                               [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TimeDomain indices
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_ProcessSmSiteSyncSync(
  EthTSyn_TimeDomainIterType TimeDomainIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtRx_HandleMessageReception
 *********************************************************************************************************************/
/*! \brief        Processing of received EthTSyn frames on an EthTSyn Bridge Port.
 *  \details      By this API service the EthTSyn Switch management gets an indication and the data of a received frame.
 *                The Service is called by the main RxIndication of the EthTSyn module.
 *  \param[in]    EthTSynCtrlIdx     Index of the EthTSyn controller
 *                                   [range: EthTSynCtrlIdx < EthTSyn_GetSizeOfCtrl()]
 *  \param[in]    DataPtr            Pointer to payload of the received Ethernet frame
 *                                   (i.e. Ethernet header is not provided)
 *  \param[in]    LenByte            Length of received data
 *  \return       ETHTSYN_E_NO_ERROR - Message was received and stored in an EthTSyn message buffer
 *  \return       other values - Message could not be received. Corresponding error id is returned
 *  \pre          -
 *  \context      TAKSE|ISR2
 *  \reentrant    TRUE for different EthTSynCtrl indices
 *  \note         This RxIndication function is wrapped by the main EthTSyn_RxIndication. Thats why the parameters
 *                differ from a the regular RxIndication
 *********************************************************************************************************************/
FUNC(uint8, ETHTSYN_CODE) EthTSyn_SwtMgmtRx_HandleMessageReception(
                  EthTSyn_IntCtrlIdxType  EthTSynCtrlIdx,
  ETHTSYN_P2CONST(uint8)                  DataPtr,
                  uint16                  LenByte);

#  define ETHTSYN_STOP_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_19.1 */

# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
#endif /* ETHTSYN_SWT_MGMT_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_SwtMgmt_Int.h
 *********************************************************************************************************************/
