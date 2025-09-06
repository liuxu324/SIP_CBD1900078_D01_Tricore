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
 *         \file  EthTSyn_Master_Int.h
 *        \brief  EthTSyn Master internal header file
 *
 *      \details  Contains internal definitions and declarations used by EthTSyn (Master role) only
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

#if !defined(ETHTSYN_MASTER_INT_H)
# define ETHTSYN_MASTER_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthTSyn_Util_Int.h"

# if (ETHTSYN_MASTER_SUPPORT == STD_ON)
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
 *  EthTSyn_Master_Init
 *********************************************************************************************************************/
/*! \brief      Initializes the Master sub-module.
 *  \details    Initializes all component variables directly related to the Master sub-module.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Master_Init(void);

/**********************************************************************************************************************
 *  EthTSyn_Master_InitPort
 *********************************************************************************************************************/
/*! \brief      Initializes the passed Master-Port.
 *  \details    Initializes all component variables directly related to the passed Master-Port.
 *  \param[in]  MasterPortIdx    Index of the Master port to be initialized
 *                               [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Master_InitPort(
  EthTSyn_IntMasterPortIdxType MasterPortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Master_ProcessSmSyncSend
 *********************************************************************************************************************/
/*! \brief      Handles the processing of the Sync Send state-machine for the given Port.
 *  \details    -
 *  \param[in]  PortIdx    Index of the Port that state-machine should be processed
 *                         [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre        Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Master_ProcessSmSyncSend(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Master_HandleCyclicTasks
 *********************************************************************************************************************/
/*! \brief      Handles the cyclic tasks of each Master-Port of the passed TimeDomain.
 *  \details    -
 *  \param[in]  TimeDomainIdx    Index of the TimeDomain
 *                               [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \pre        -
 *  \context    TASK
 *  \reentrant  TRUE for different TimeDomain indices
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Master_HandleCyclicTasks(
  EthTSyn_TimeDomainIterType TimeDomainIdx);

#  define ETHTSYN_STOP_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_19.1 */

# endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */
#endif /* ETHTSYN_MASTER_INT_H */
/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Master_Int.h
 *********************************************************************************************************************/
