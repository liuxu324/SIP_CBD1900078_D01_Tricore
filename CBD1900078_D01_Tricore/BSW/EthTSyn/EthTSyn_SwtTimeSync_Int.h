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
/**        \file  EthTSyn_SwtTimeSync_Int.h
 *        \brief  EthTSyn Switch Time Sync internal header file
 *
 *      \details  Contains internal definitions and declarations used by EthTSyn (Switch Time Sync) only
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

#if !defined (ETHTSYN_SWT_TIME_SYNC_INT_H)
# define ETHTSYN_SWT_TIME_SYNC_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthTSyn_Types.h"

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
#  if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
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

#   define ETHTSYN_START_SEC_CODE
#   include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_Init
 *********************************************************************************************************************/
/*! \brief        Initializes the EthTSyn switch time sync parts.
 *  \details      Initializes all component variables directly related to the SwtTimeSync sub-module.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \note         This function must be called before using the module
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_Init(void);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_HandleCyclicTasks
 *********************************************************************************************************************/
/*! \brief      Handles cyclic switch time sync tasks.
 *  \details    -
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_HandleCyclicTasks(void);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ProvideTimestamps
 *********************************************************************************************************************/
/*! \brief      Provides timestamps of a sync event for the synchronization of a switch.
 *  \details    Verifies that the passed time domain is used for synchronization of the passed switch. If so, the
 *              provided timestamps are stored for later synchronization of the switch.
 *  \param[in]  TimeDomainIdx              Index of the time domain
 *  \param[in]  EthIfSwitchIdx             Index of the switch in the context of the EthIf
 *  \param[in]  SequenceId                 SequenceId of the sync event
 *  \param[in]  PreciseOriginTimestampPtr  Precise origin timestamp of the sync event
 *  \param[in]  SwtIngressTimestampPtr     Switch ingress timestamp of the sync event
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different EthIfSwitchIdx
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ProvideTimestamps(
                  EthTSyn_IntTimeDomainIdxType TimeDomainIdx,
                  uint8                        EthIfSwitchIdx,
                  uint16                       SequenceId,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) PreciseOriginTimestampPtr,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) SwtIngressTimestampPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ProvideTimestampsFromSwtSlavePort
 *********************************************************************************************************************/
/*! \brief      Provides timestamps of a sync event for the synchronization of a switch.
 *  \details    Gets the precise origin timestamp from received FollowUp message and the corresponding sync ingress
 *              timestamp on the slave port of the switch. These timestamps are then provided for time synchronization
 *              of the switch.
 *  \param[in]  TimeDomainIdx              Index of the time domain
 *  \param[in]  SwtSlavePortIdx            Index of the switch slave port in context of the EthTSyn
 *  \pre        Sync/FollowUp message pair was received on the passed switch slave port and all timestamps are ready
 *              for processing.
 *  \pre        The FollowUp message is still stored in the site sync sync state machine.
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ProvideTimestampsFromSwtSlavePort(
  EthTSyn_IntTimeDomainIdxType TimeDomainIdx,
  EthTSyn_IntSlavePortIdxType  SwtSlavePortIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_IsTimeDomainUsedForSwtSync
 *********************************************************************************************************************/
/*! \brief      Checks if the passed time domain is used for time synchronization of a switch.
 *  \details    -
 *  \param[in]  TimeDomainIdx   Index of the time domain.
 *  \return     TRUE - Time domain is used for switch time synchronization
 *  \return     FALSE - Time domain is not used for switch time synchronization
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(boolean, ETHTSYN_CODE) EthTSyn_SwtTimeSync_IsTimeDomainUsedForSwtSync(
  EthTSyn_IntTimeDomainIdxType TimeDomainIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SwtSyncFrameStart
 *********************************************************************************************************************/
/*! \brief      Starts the cyclic switch sync frame transmission for all switches using the passed EthIfCtrl.
 *  \details    -
 *  \param[in]  EthIfCtrlIdx   Index of the EthIf controller.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *  \note       This function should be called when a LINK_ACTIVE was reported for the EthIf controller.
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SwtSyncFrameStart(
  uint8 EthIfCtrlIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SwtSyncFrameStop
 *********************************************************************************************************************/
/*! \brief      Stops the cyclic switch sync frame transmission for all switches using the passed EthIfCtrl.
 *  \details    -
 *  \param[in]  EthIfCtrlIdx   Index of the EthIf controller.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *  \note       This function should be called when a LINK_DOWN was reported for the EthIf controller.
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SwtSyncFrameStop(
  uint8 EthIfCtrlIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SwtSyncFrameTxConfirmation
 *********************************************************************************************************************/
/*! \brief      Checks and handles the tx confirmation for a former transmitted switch sync frame.
 *  \details    -
 *  \param[in]  EthIfCtrlIdx   Index of the EthIf controller.
 *  \param[in]  BufIdx         Index of the transmission buffer.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SwtSyncFrameTxConfirmation(
  uint8 EthIfCtrlIdx,
  uint8 BufIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SwtSyncFrameHandleRx
 *********************************************************************************************************************/
/*! \brief      Handles the reception of a switch sync frame.
 *  \details    Checks if the received frame provided in the message buffer is a switch sync frame and handles the
 *              reception of this switch sync frame.
 *  \param[in]  MsgBufferPtr   The message buffer where the received frame and additional information are stored
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different message buffers
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SwtSyncFrameHandleRx(
  ETHTSYN_P2CONST(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr);

#   define ETHTSYN_STOP_SEC_CODE
#   include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_19.1 */

#  endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
#endif /* ETHTSYN_SWT_TIME_SYNC_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_SwtTimeSync_Int.h
 *********************************************************************************************************************/
