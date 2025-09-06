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
/**        \file  EthTSyn_SwtMgmt.c
 *        \brief  EthTSyn Switch Management source file
 *
 *      \details  EthTSyn Switch Management source file containing the EthTSyn Switch Management implementation of the
 *                EthTSyn module.
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

#define ETHTSYN_SWTMGMT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EthTSyn_SwtMgmt_Int.h"
#include "EthTSyn_SwtMgmt_Cbk.h"

#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
# include "EthTSyn_Int.h" /* PRQA S 0883, 3219 */ /* MD_EthTSyn_0883, MD_MSR_14.1_3219 */
# include "EthTSyn_Util_Int.h" /* PRQA S 3219 */ /* MD_EthTSyn_3219 */
# include "EthTSyn_Slave_Int.h" /* PRQA S 3219 */ /* MD_EthTSyn_3219 */
# include "EthTSyn_Master_Int.h"
# include "EthTSyn_Pdelay_Int.h"
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
#  include "EthTSyn_SwtTimeSync_Int.h" /* PRQA S 0777 */ /* MD_MSR_5.1_777 */
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* Check the version of EthTSyn header file */
# if (  (ETHTSYN_SW_MAJOR_VERSION != (7u)) \
     || (ETHTSYN_SW_MINOR_VERSION != (0u)) \
     || (ETHTSYN_SW_PATCH_VERSION != (0u)) )
#  error "Vendor specific version numbers of EthTSyn_SwtMgmt.c and EthTSyn.h are inconsistent"
# endif

/* Check the version of the configuration header file */
# if (  (ETHTSYN_CFG_MAJOR_VERSION != (7u)) \
     || (ETHTSYN_CFG_MINOR_VERSION != (0u)) )
#  error "Version numbers of EthTSyn_SwtMgmt.c and EthTSyn_Cfg.h are inconsistent!"
# endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

# if !defined (ETHTSYN_LOCAL) /* COV_MSR_COMPATIBILITY */
#  define ETHTSYN_LOCAL static
# endif

# if !defined (ETHTSYN_LOCAL_INLINE) /* COV_MSR_COMPATIBILITY */
#  define ETHTSYN_LOCAL_INLINE LOCAL_INLINE
# endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
# define ETHTSYN_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

ETHTSYN_LOCAL VAR(EthTSyn_SwtMgmt_MsgBufferType, ETHTSYN_VAR_NOINIT) EthTSyn_SwtMgmt_MsgBuffer[
                                                                                    ETHTSYN_SWT_MGMT_MSG_BUFFER_COUNT];

# define ETHTSYN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETHTSYN_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_StoreSwitchEgressTimestamp
 *********************************************************************************************************************/
/*! \brief      Stores a Switch egress timestamp.
 *  \details    Checks if the Timestamp belongs to an received or transmitted message, stores it and triggers possible
 *              further processing.
 *  \param[in]  CtrlIdx        Index of the EthTSyn controller
 *                             [range: CtrlIdx < EthTSyn_GetSizeOfCtrl()]
 *  \param[in]  DataPtr        Buffer Pointer to map the Timestamp indication to the received/transmitted frame
 *  \param[in]  MgmtInfoPtr    Management information
 *  \param[in]  TimeStampPtr   Current timestamp
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different MgmtInfos
 *********************************************************************************************************************/
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_StoreSwitchEgressTimestamp(
                  EthTSyn_IntCtrlIdxType   CtrlIdx,
  ETHTSYN_P2CONST(uint8)                   DataPtr,
  ETHTSYN_P2CONST(EthTSyn_SwtMgmtInfoType) MgmtInfoPtr,
  ETHTSYN_P2CONST(Eth_TimeStampType)       TimeStampPtr);
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_StoreSwitchIngressTimestamp
 *********************************************************************************************************************/
/*! \brief      Stores a Switch ingress timestamp.
 *  \details    Checks if the Timestamp belongs to an received or transmitted message, stores it and triggers possible
 *              further processing.
 *  \param[in]  CtrlIdx        Index of the EthTSyn controller
 *                             [range: CtrlIdx < EthTSyn_GetSizeOfCtrl()]
 *  \param[in]  DataPtr        Buffer Pointer to map the Timestamp indication to the received/transmitted frame
 *  \param[in]  MgmtInfoPtr    Management information
 *  \param[in]  TimeStampPtr   Current timestamp
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different MgmtInfos
 *********************************************************************************************************************/
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_StoreSwitchIngressTimestamp(
                  EthTSyn_IntCtrlIdxType   CtrlIdx,
  ETHTSYN_P2CONST(uint8)                   DataPtr,
  ETHTSYN_P2CONST(EthTSyn_SwtMgmtInfoType) MgmtInfoPtr,
  ETHTSYN_P2CONST(Eth_TimeStampType)       TimeStampPtr);
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtRx_StoreSwitchMgmtInfo
 *********************************************************************************************************************/
/*! \brief      Stores the passed Switch management information.
 *  \details    Gets the EthTSyn message buffer which belongs to the given Switch management information and stores the
 *              information and triggers the processing of the message buffer if applicable.
 *  \param[in]  CtrlIdx       Index of the EthTSyn controller
 *                            [range: CtrlIdx < EthTSyn_GetSizeOfCtrl()]
 *  \param[in]  DataPtr       Buffer Pointer to map the Switch management info to the received frame
 *  \param[in]  MgmtInfoPtr   Pointer to the Switch management information
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different MgmtInfos
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmtRx_StoreSwitchMgmtInfo(
                  EthTSyn_IntCtrlIdxType   CtrlIdx,
  ETHTSYN_P2CONST(uint8)                   DataPtr,
  ETHTSYN_P2CONST(EthTSyn_SwtMgmtInfoType) MgmtInfoPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtRx_ProcessMsgBuffer
 *********************************************************************************************************************/
/*! \brief          Processes a received message.
 *  \details        Checks if all required information for the received message are available and optionally processes
 *                  the message.
 *  \param[in,out]  MsgBufferPtr   In:  Pointer to the message buffer to be processed
 *                                 Out: Adopted message buffer state/information
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different message buffers
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmtRx_ProcessMsgBuffer(
  ETHTSYN_P2VAR(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtRx_IsMsgBufferReadyForProcessing
 *********************************************************************************************************************/
/*! \brief      Checks if the given message buffer is ready for processing.
 *  \details    Checks if all required timestamps and the Switch management information are available for the message.
 *  \param[in]  MsgBufferPtr   Pointer to the message buffer to be checked
 *  \return     TRUE - Message buffer is ready for processing
 *  \return     FALSE - Message buffer is not ready for processing
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_SwtMgmtRx_IsMsgBufferReadyForProcessing(
  ETHTSYN_P2CONST(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtRx_GetPortForMsgBuffer
 *********************************************************************************************************************/
/*! \brief      Retrieves the EthTSyn Port which matches the information of the buffered message.
 *  \details    -
 *  \param[in]  MsgBufferPtr   Pointer to the message buffer
 *  \return     EthTSyn_GetSizeOfPort() - no matching port was found
 *  \return     other values - the matching EthTSyn Port index
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntPortIdxType, ETHTSYN_CODE) EthTSyn_SwtMgmtRx_GetPortForMsgBuffer(
  ETHTSYN_P2CONST(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtRx_ProcRcvdMsg
 *********************************************************************************************************************/
/*! \brief          Handles the processing of a received message (switch management).
 *  \details        -
 *  \param[in]      PortIdx        Index of the port the message was received on
 *                                 [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in,out]  MsgBufferPtr   In:  Pointer to the message buffer
 *                                 Out: Modified state of the message buffer and message type dependent values
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different MsgBuffers
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmtRx_ProcRcvdMsg(
                EthTSyn_IntPortIdxType          PortIdx,
  ETHTSYN_P2VAR(EthTSyn_SwtMgmt_MsgBufferType)  MsgBufferPtr);

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtRx_ForwardSyncMsgToEndStation
 *********************************************************************************************************************/
/*! \brief      Handles the forwarding of a received Sync message to the End-Station implementation.
 *  \details    -
 *  \param[in]  TimeDomainIdx   Index of the time domain the message was received on
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \param[in]  MsgBufferPtr    Pointer to the message buffer
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TimeDomain indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmtRx_ForwardSyncMsgToEndStation(
                  EthTSyn_IntTimeDomainIdxType    TimeDomainIdx,
  ETHTSYN_P2CONST(EthTSyn_SwtMgmt_MsgBufferType)  MsgBufferPtr);
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtRx_ForwardFollowUpMsgToEndStation
 *********************************************************************************************************************/
/*! \brief          Handles the forwarding of a received FollowUp message to the End-Station implementation.
 *  \details        -
 *  \param[in]      PortIdx         Index of the port the message was received on
 *                                  [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]      TimeDomainIdx   Index of the time domain the message was received on
 *  \param[in,out]  MsgBufferPtr    In:  Pointer to the message buffer
 *                                  Out: Adopted correction field
 *  \pre            Constraint for PortIdx: EthTSyn_IsSlavePortUsedOfPort() == TRUE
 *  \pre            TimeDomainIdx has to identify the TimeDomain of the passed Port
 *  \context        TAKS|ISR2
 *  \reentrant      TRUE for different Port indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmtRx_ForwardFollowUpMsgToEndStation(
                EthTSyn_IntPortIdxType          PortIdx,
                EthTSyn_IntTimeDomainIdxType    TimeDomainIdx,
  ETHTSYN_P2VAR(EthTSyn_SwtMgmt_MsgBufferType)  MsgBufferPtr);
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_TriggerStateMachine
 *********************************************************************************************************************/
/*! \brief      Trigger the processing of the passed state machine.
 *  \details    -
 *  \param[in]  StateMachine   Identification of the state machine to be processed
 *  \param[in]  PortIdx        Index of the EthTSyn port the state machine should be processed for
 *                             [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices and/or state machines
 *********************************************************************************************************************/
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_TriggerStateMachine(
  EthTSyn_SmIdentEnumType  StateMachine,
  EthTSyn_IntPortIdxType   PortIdx);
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_ProcRcvdPdReqMsg
 *********************************************************************************************************************/
/*! \brief      Processes a received Pdelay_Req message.
 *  \details    Checks if passed Port is ready to receive a Pdelay_Req message and optionally processes the message.
 *  \param[in]  PortIdx        Index of the EthTSyn Port the message was received on
 *                             [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  MsgBufferPtr   Pointer to the message buffer to be processed
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_ProcRcvdPdReqMsg(
                  EthTSyn_IntPortIdxType         PortIdx,
  ETHTSYN_P2CONST(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_ProcRcvdPdRespMsg
 *********************************************************************************************************************/
/*! \brief      Processes a received Pdelay_Resp message.
 *  \details    Checks if passed Port is ready to receive a Pdelay_Resp message and optionally processes the message.
 *  \param[in]  PortIdx        Index of the EthTSyn Port the message was received on
 *                             [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  MsgBufferPtr   Pointer to the message buffer to be processed
 *  \pre        -
 *  \context    TAKS|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_ProcRcvdPdRespMsg(
                  EthTSyn_IntPortIdxType         PortIdx,
  ETHTSYN_P2CONST(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_ProcRcvdPdRespFupMsg
 *********************************************************************************************************************/
/*! \brief      Processing of a received Pdelay_Resp_FollowUp message.
 *  \details    Checks if passed Port is ready to receive a Pdelay_Resp_FollowUp message and optionally processes the
 *              message.
 *  \param[in]  PortIdx        Index of the EthTSyn Port the message was received on
 *                             [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  MsgBufferPtr   Pointer to the message buffer to be processed
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_ProcRcvdPdRespFupMsg(
                  EthTSyn_IntPortIdxType         PortIdx,
  ETHTSYN_P2CONST(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_ProcRcvdSyncMsg
 **********************************************************************************************************************/
/*! \brief      Processing of a received Sync message.
 *  \details    Checks if passed Port is ready to receive a Sync message and optionally processes the message.
 *  \param[in]  PortIdx        Index of the EthTSyn Port the message was received on
 *                             [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  MsgBufferPtr   Pointer to the message buffer to be processed
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_ProcRcvdSyncMsg(
                  EthTSyn_IntPortIdxType         PortIdx,
  ETHTSYN_P2CONST(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtRx_CheckSyncMsgReception
 **********************************************************************************************************************/
/*! \brief      Checks if a sync message can currently be received on the passed Port.
 *  \details    Checks if a sync message can currently be received on the passed Port based on the following criteria:
 *              PortRole, AsCapable, SyncReceive state machine state, source port identity of the sync message.
 *              In addition Master-Slave-Conflict detection is handled.
 *  \param[in]  PortIdx     Index of the EthTSyn Port the message was received on
 *                          [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  ComMsgPtr   Pointer to the common message header of the sync message
 *  \return     TRUE - Receive message
 *  \return     FALSE - Drop message
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_SwtMgmtRx_CheckSyncMsgReception(
                  EthTSyn_IntPortIdxType        PortIdx,
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType)     ComMsgPtr);
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtRx_IsPortReadyToReceiveSync
 **********************************************************************************************************************/
/*! \brief      Checks if the given port is ready to receive a sync message.
 *  \details    Checks the PortRole, AsCapableState, SyncReceiveSm state and source port identity.
 *              In addition the Master-Slave-Conflict Detection is handled.
 *  \param[in]  PortIdx            Index of the EthTSyn Port the message was received on
 *                                 [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  SrcClockIdentity   The source clock identity of the received Sync message
 *  \return     TRUE - Port is ready to receive sync message
 *  \return     FALSE - Port is not ready to receive sync message
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_SwtMgmtRx_IsPortReadyToReceiveSync(
  EthTSyn_IntPortIdxType  PortIdx,
  uint64                  SrcClockIdentity);
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_ProcRcvdFupMsg
 *********************************************************************************************************************/
/*! \brief          Processing of a received FollowUp message.
 *  \details        Checks if passed Port is ready to receive a FollowUp message and optionally processes the message.
 *                  Processing the message includes forwarding the message to the End-Station if applicable.
 *  \param[in]      PortIdx        Index of the EthTSyn Port the message was received on
 *                                 [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]      TimeDomainIdx  Index of the TimeDomain the message was received on
 *                                 [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \param[in,out]  MsgBufferPtr   In:  Pointer to the message buffer to be processed
 *                                 Out: Adopted follow up correction field
 *  \pre            TimeDomainIdx has to identify the TimeDomain of the passed Port
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different Port indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_ProcRcvdFupMsg(
                EthTSyn_IntPortIdxType         PortIdx,
  ETHTSYN_P2VAR(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_ProcRcvdAnnounceMsg
 *********************************************************************************************************************/
/*! \brief      Processing of a received Announce message.
 *  \details    Checks if passed Port is ready to receive an Announce message and optionally processes the message.
 *  \param[in]  PortIdx        Index of the EthTSyn Port the message was received on
 *                             [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  MsgBufferPtr   Pointer to the message buffer to be processed
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_ProcRcvdAnnounceMsg(
                  EthTSyn_IntPortIdxType         PortIdx,
  ETHTSYN_P2CONST(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_ReleaseMsgBuffer
 *********************************************************************************************************************/
/*! \brief          Release the provided message buffer.
 *  \details        -
 *  \param[in,out]  MsgBufferPtr   In:  Pointer to the message buffer element to be released
 *                                 Out: Information like state set within the message buffer struct
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_ReleaseMsgBuffer(
  ETHTSYN_P2VAR(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtRx_PerformBasicMsgChecksAngGetMsgBuffer
 *********************************************************************************************************************/
/*! \brief       Performs basic message checks and gets a free message buffer.
 *  \details     Checks basic message information (e.g. ProtocolVersion), gets and locks a free message buffer.
 *               If any of the performed message checks fails, the message buffer is released.
 *  \param[in]   LenByte           The received message length passed to EthTSyn_RxIndication() from EthIf
 *  \param[in]   DataPtr           Pointer to the Rx-Buffer passed to the EthTSyn_RxIndication from EthIf
 *  \param[out]  MsgBufferPtrPtr   Pointer to the free message buffer element
 *  \return      ETHTSYN_E_NO_ERROR - Message checks passed and message buffer available.
 *  \return      other values - Message checks failed or no message buffer available. Corresponding error id is returned
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_SwtMgmtRx_PerformBasicMsgChecksAngGetMsgBuffer(
                  uint16                                        LenByte,
  ETHTSYN_P2CONST(uint8)                                        DataPtr,
    ETHTSYN_P2VAR(ETHTSYN_P2VAR(EthTSyn_SwtMgmt_MsgBufferType)) MsgBufferPtrPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtRx_HandleIngressTimestamp
 *********************************************************************************************************************/
/*! \brief          Handles the ingress timestamping of a received frame.
 *  \details        -
 *  \param[in]      EthIfCtrlIdx   Index of the EthIf controller the message was received on
 *  \param[in]      DataPtr        Pointer to the received message
 *  \param[in,out]  MsgBufferPtr   In:  Pointer to the used message buffer
 *                                 Out: Timestamp informations set within the message buffer struct
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmtRx_HandleIngressTimestamp(
                  uint8                           EthIfCtrlIdx,
  ETHTSYN_P2CONST(uint8)                          DataPtr,
    ETHTSYN_P2VAR(EthTSyn_SwtMgmt_MsgBufferType)  MsgBufferPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_ProvideMsgBuffer
 *********************************************************************************************************************/
/*! \brief       Get a free message buffer, prepare and lock it.
 *  \details     -
 *  \param[out]  MsgBufferPtrPtr   Pointer to the free message buffer element
 *  \return      E_OK - Free message buffer available (MsgBufferPtrPtr always set to a valid MsgBuffer)
 *  \return      E_NOT_OK - No message buffer available (MsgBufferPtrPtr might be set to NULL_PTR)
 *  \pre         -
 *  \context     TAKS|ISR2
 *  \reentrant   FALSE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtMgmt_ProvideMsgBuffer(
    ETHTSYN_P2VAR(EthTSyn_SwtMgmt_MsgBufferType) *MsgBufferPtrPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_GetMappedMsgBuffer
 *********************************************************************************************************************/
/*! \brief       Get the message buffer mapped to the passed FrameId and Rx-Buffer Address.
 *  \details     -
 *  \param[in]   CtrlIdx           Index of the EthTSyn controller the frame was received on
 *  \param[in]   RxBufAddr         Address of the corresponding Rx-Buffer
 *  \param[in]   FrameId           The Frame ID of the frame the message buffer is requested for
 *  \param[out]  MsgBufferPtrPtr   Pointer to the mapped message buffer element
 *  \return      E_OK - Message buffer available (MsgBufferPtrPtr is always set to a valid MsgBuffer)
 *  \return      E_NOT_OK - No message buffer mapped (MsgBufferPtrPtr might be set to NULL_PTR)
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtMgmt_GetMappedMsgBuffer(
                    EthTSyn_IntCtrlIdxType          CtrlIdx,
    ETHTSYN_P2CONST(uint8)                          RxBufAddr,
                    EthTSyn_FrameIdType             FrameId,
      ETHTSYN_P2VAR(EthTSyn_SwtMgmt_MsgBufferType) *MsgBufferPtrPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_GetEndStationSlavePortIdx
 *********************************************************************************************************************/
/*! \brief      Get the End-Station Slave-Port Index of the passed TimeDomain.
 *  \details    -
 *  \param[in]  TimeDomainIdx   Index of the TimeDomain the slave port should be retrieved for
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \return     EthTSyn_GetSizeOfPort() - no End-Station Slave-Port found
 *  \return     other values - the corresponding port index of the End-Station Slave-Port
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntPortIdxType, ETHTSYN_CODE) EthTSyn_SwtMgmt_GetEndStationSlavePortIdx(
  EthTSyn_IntTimeDomainIdxType TimeDomainIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_GetSwitchSlavePortIdx
 *********************************************************************************************************************/
/*! \brief      Get the Switch Slave-Port Index of the given TimeDomain.
 *  \details    -
 *  \param[in]  TimeDomainIdx   Index of the TimeDomain the slave port should be retrieved for
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \return     EthTSyn_GetSizeOfSlavePort() - no Switch Slave-Port found
 *  \return     other values - the corresponding port index of the Switch Slave-Port
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntSlavePortIdxType, ETHTSYN_CODE) EthTSyn_SwtMgmt_GetSwitchSlavePortIdx(
  EthTSyn_TimeDomainIterType TimeDomainIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_GetIngressTimestamp
 *********************************************************************************************************************/
/*! \brief      Handles the ingress timestamping.
 *  \details    -
 *  \param[in]  EthIfCtrlIdx          Ethernet interface controller index
 *  \param[in]  TimeDomainIdx         Index of the TimeDomain the message was received for
 *  \param[in]  DataPtr               Pointer to the Rx-Buffer
 *  \param[out] IngressTimestampPtr   The Ingress timestamp
 *  \return     E_OK - Succeeded
 *  \return     E_NOT_OK - Failed
 *  \pre        This function has to be called in the context of EthTSyn_RxIndication()
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtMgmt_GetIngressTimestamp(
                  uint8                         EthIfCtrlIdx,
                  EthTSyn_IntTimeDomainIdxType  TimeDomainIdx,
  ETHTSYN_P2CONST(uint8)                        DataPtr,
    ETHTSYN_P2VAR(EthTSyn_GlobalTimestampType)  IngressTimestampPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_GetMappedStateMachine
 *********************************************************************************************************************/
/*! \brief       Gets the state machine mapped to the passed FrameId and Rx-Buffer Address.
 *  \details     -
 *  \param[in]   CtrlIdx      Index of the corresponding EthTSyn controller
 *                            [range: CtrlIdx < EthTSyn_GetSizeOfCtrl()]
 *  \param[in]   TxBufPtr     Address of the corresponding Tx-Buffer
 *  \param[in]   FrameId      The Frame ID of the frame the state machine is requested for
 *  \param[out]  PortIdxPtr   Pointer to the mapped message buffer element
 *  \return      ETHTSYN_SM_IDENT_INVALID - no corresponding state machine found
 *  \return      other values - the mapped state machine indication value
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *********************************************************************************************************************/
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SmIdentEnumType, ETHTSYN_CODE) EthTSyn_SwtMgmt_GetMappedStateMachine(
                  EthTSyn_IntCtrlIdxType     CtrlIdx,
  ETHTSYN_P2CONST(uint8)                     TxBufPtr,
                  EthTSyn_FrameIdType        FrameId,
    ETHTSYN_P2VAR(EthTSyn_IntPortIdxType)    PortIdxPtr);
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_GetStateMachineTxTimestampInfo
 *********************************************************************************************************************/
/*! \brief       Gets the timestamp info of the passed state machine.
 *  \details     Gets the timestamp and its state of the passed Port and state machine for the passed direction.
 *  \param[in]   StateMachine           The State machine 'type' for which the timestamp info is required
 *  \param[in]   PortIdx                The Port index of the state machine
 *                                      [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]   TimestampDir           Direction of the Timestamp (ingress/egress)
 *  \param[out]  TimestampPtrPtr        Pointer to the corresponding Timestamp
 *  \param[out]  TimestampStatePtrPtr   Pointer to the corresponding Timestamp state
 *  \return      E_OK - Successfully retrieved the Timestamp info
 *               E_NOT_OK - Failed to retrieve the Timestamp info
 *  \pre         Constraints for PortIdx depending on StateMachine:
 *               ETHTSYN_SM_IDENT_SYNC_SEND:
 *                    EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *               ETHTSYN_SM_IDENT_PDELAY_REQ:
 *                    EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                    EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                    EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig() == TRUE
 *               ETHTSYN_SM_IDENT_PDELAY_RESP:
 *                    EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                    EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                    EthTSyn_IsPdelayResponderUsedOfPdelayConfig() == TRUE
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *********************************************************************************************************************/
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtMgmt_GetStateMachineTxTimestampInfo(
                EthTSyn_SmIdentEnumType                     StateMachine,
                EthTSyn_IntPortIdxType                      PortIdx,
                EthTSyn_TimestampDirEnumType                TimestampDir,
  ETHTSYN_P2VAR(ETHTSYN_P2VAR(EthTSyn_GlobalTimestampType)) TimestampPtrPtr,
  ETHTSYN_P2VAR(ETHTSYN_P2VAR(EthTSyn_TimestampStateType))  TimestampStatePtrPtr);
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtTx_TxSyncMsg
 *********************************************************************************************************************/
/*! \brief       Transmits a Sync message on the passed Master-Port.
 *  \details     Transmits a Sync message on the passed port. This includes getting a TxBuffer and timestamp handling.
 *  \param[in]   MasterPortIdx   Index of the Master Port the Sync message should be transmitted on
 *                               [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \pre         Port has to be AsCapable (EthTSyn_Util_IsAsCapable()) and tx ready (EthTSyn_IsTxReady())
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different Master-Port indices
 *  \note        In case of any error, the possibly locked TxBuffer is released by this function
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmtTx_TxSyncMsg(
  EthTSyn_MasterPortIterType MasterPortIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtTx_CopySyncMsgFromSiteSyncSyncSmToTxBuffer
 *********************************************************************************************************************/
/*! \brief       Copies the Sync message from the SiteSyncSync state machine to the provided TxBuffer.
 *  \details     Copies the Sync message from the SiteSyncSync state machine to the provided Ethernet TxBuffer in
 *               Network-Byte-Order and adepts the Source-Port-Identity (if applicable).
 *  \param[in]   PortIdx     Index of the Port the Sync message should be transmitted on
 *                           [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[out]  BufferPtr   Pointer to the Ethernet Tx-Buffer. The Sync message will be copied here
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmtTx_CopySyncMsgFromSiteSyncSyncSmToTxBuffer(
                EthTSyn_PortIdxOfMasterPortType  PortIdx,
  ETHTSYN_P2VAR(uint8)                           BufferPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtTx_TxFollowUpMsg
 *********************************************************************************************************************/
/*! \brief       Transmits a FollowUp message on the passed Port.
 *  \details     Transmits a FollowUp message on the passed port. This includes getting a TxBuffer.
 *  \param[in]   MasterPortIdx   Index of the Master Port the FollowUp message should be transmitted on
 *                               [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \pre         -
 *  \context     TAKS|ISR2
 *  \reentrant   TRUE for different Master-Port indices
 *  \note        In case of any error, the possibly locked TxBuffer is released by this function
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmtTx_TxFollowUpMsg(
  EthTSyn_MasterPortIterType MasterPortIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtTx_CopyFollowUpMsgFromSiteSyncSyncSmToTxBuffer
 *********************************************************************************************************************/
/*! \brief       Copies the FollowUp message of the SiteSyncSync state machine to the provided TxBuffer.
 *  \details     Copies the FollowUp message of the SiteSyncSync state machine to the provided Ethernet TxBuffer in
 *               Network-Byte-Order and adepts the Source-Port-Identity (if applicable).
 *  \param[in]   PortIdx     Index of the Port the FollowUp message should be transmitted on
 *                           [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[out]  BufferPtr   Pointer to the Ethernet Tx-Buffer. The FollowUp message will be copied here
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmtTx_CopyFollowUpMsgFromSiteSyncSyncSmToTxBuffer(
                EthTSyn_PortIdxOfMasterPortType  PortIdx,
  ETHTSYN_P2VAR(uint8)                           BufferPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtTx_ComputeAndSetFollowUpCorrectionField
 *********************************************************************************************************************/
/*! \brief      Calculates the FollowUp correction field value and sets it in the corresponding FollowUp message.
 *  \details    Computes the Switch/Software residence time of the corresponding sync message and adds it to the
 *              correction field of the FollowUp message. Adds the Pdelay of the Slave-Port as well.
 *  \param[in]  PortIdx     Index of the Port the FollowUp message should be transmitted on
 *                          [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  ComMsgPtr   Pointer to the header of the FollowUp message
 *  \pre        The FollowUp message (at least the old correction field) was already copied to the TxBuffer
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmtTx_ComputeAndSetFollowUpCorrectionField(
                  EthTSyn_PortIdxOfMasterPortType  PortIdx,
    ETHTSYN_P2VAR(EthTSyn_CommonMsgHdrType)        ComMsgPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_HandleSendSyncStateOfSiteSyncSyncSm
 *********************************************************************************************************************/
/*! \brief      Handles the state ETHTSYN_S_SSS_SM_TX_SYNC of the SiteSyncSync state machine.
 *  \details    -
 *  \param[in]  TimeDomainIdx   Index of the TimeDomain the SiteSyncSync state machine is processed for
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \pre        Should be called in the context of EthTSyn_SwtMgmt_ProcessSmSiteSyncSync() only
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TimeDomain indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_HandleSendSyncStateOfSiteSyncSyncSm(
  EthTSyn_TimeDomainIterType TimeDomainIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_HandleSendFollowUpStateOfSiteSyncSyncSm
 *********************************************************************************************************************/
/*! \brief      Handles the state ETHTSYN_S_SSS_SM_TX_FUP of the SiteSyncSync state machine.
 *  \details    -
 *  \param[in]  TimeDomainIdx   Index of the TimeDomain the SiteSyncSync state machine is processed for
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \pre        Should be called in the context of EthTSyn_SwtMgmt_ProcessSmSiteSyncSync() only
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TimeDomain indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_HandleSendFollowUpStateOfSiteSyncSyncSm(
  EthTSyn_TimeDomainIterType TimeDomainIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_HandleReceivedFupAfterTimeoutStateOfSiteSyncSyncSm
 *********************************************************************************************************************/
/*! \brief      Handles the state ETHTSYN_S_SSS_SM_RCVD_FUP_AFTER_TIMEOUT of the SiteSyncSync state machine.
 *  \details    -
 *  \param[in]  TimeDomainIdx   Index of the TimeDomain the SiteSyncSync state machine is processed for
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \pre        Should be called in the context of EthTSyn_SwtMgmt_ProcessSmSiteSyncSync() only
 *  \context    TAKS|ISR2
 *  \reentrant  TRUE for different TimeDomain indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_HandleReceivedFupAfterTimeoutStateOfSiteSyncSyncSm(
  EthTSyn_TimeDomainIterType TimeDomainIdx);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_StoreSwitchEgressTimestamp
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
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_StoreSwitchEgressTimestamp(
                  EthTSyn_IntCtrlIdxType   CtrlIdx,
  ETHTSYN_P2CONST(uint8)                   DataPtr,
  ETHTSYN_P2CONST(EthTSyn_SwtMgmtInfoType) MgmtInfoPtr,
  ETHTSYN_P2CONST(Eth_TimeStampType)       TimeStampPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_P2VAR(EthTSyn_SwtMgmt_MsgBufferType) msgBufferPtr = NULL_PTR;
  ETHTSYN_P2VAR(Eth_TimeStampType) egressTsPtr = NULL_PTR;
  ETHTSYN_P2VAR(EthTSyn_TimestampStateType) egressTsStatePtr = NULL_PTR;
  EthTSyn_SmIdentEnumType stateMachine = ETHTSYN_SM_IDENT_INVALID;
  EthTSyn_IntPortIdxType portIdx = EthTSyn_GetSizeOfPort();

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the timestamp is given for received or transmitted message. */
  if(EthTSyn_SwtMgmt_GetMappedMsgBuffer(CtrlIdx, DataPtr, MgmtInfoPtr->FrameId, &msgBufferPtr) == E_OK)                /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
  {
    if(msgBufferPtr != NULL_PTR)
    {
      egressTsPtr = &msgBufferPtr->EgressTimestampHostPortMgmt.Timestamp;
      egressTsStatePtr = &msgBufferPtr->EgressTimestampHostPortMgmt.State;
    }
  }
  else
  {
    /* Try to get mapped state machine (Tx) */
    stateMachine = EthTSyn_SwtMgmt_GetMappedStateMachine( CtrlIdx, DataPtr, MgmtInfoPtr->FrameId, &portIdx);           /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
    if(stateMachine != ETHTSYN_SM_IDENT_INVALID)
    {
      (void)EthTSyn_SwtMgmt_GetStateMachineTxTimestampInfo(stateMachine, portIdx,
          ETHTSYN_TS_DIR_EGRESS, &egressTsPtr, &egressTsStatePtr);                                                     /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
    }
  }


  /* #20 Check if either Rx or Tx message/state machine is available. */
  if( (egressTsPtr != NULL_PTR) && (egressTsStatePtr != NULL_PTR) )
  {
    /* #200 Check if egress timestamp is available. */
    if(TimeStampPtr == NULL_PTR)
    {
      /* #2000 Timestamp is not available -> mark TimeStamp as not available. */
      *egressTsStatePtr |= ETHTSYN_TIMESTAMP_STATE_AVAILABLE_FLAG_VALID_MASK;                                          /* SBSW_ETHTSYN_POINTER_VARIABLE_WRITE */
      *egressTsStatePtr &= (EthTSyn_TimestampStateType)~(ETHTSYN_TIMESTAMP_STATE_AVAILABLE_MASK);                      /* SBSW_ETHTSYN_POINTER_VARIABLE_WRITE */
    }
    else
    {
      /* #2001 Timestamp available -> Copy timestamp and mark it as available. */
      *egressTsStatePtr |=
        (ETHTSYN_TIMESTAMP_STATE_AVAILABLE_FLAG_VALID_MASK | ETHTSYN_TIMESTAMP_STATE_AVAILABLE_MASK);                  /* SBSW_ETHTSYN_POINTER_VARIABLE_WRITE */
      *egressTsPtr = *TimeStampPtr;                                                                                    /* SBSW_ETHTSYN_POINTER_VARIABLE_WRITE */
    }
  }

  /* #30 Trigger processing of message buffer (received message) or state machine (transmitted message). */
  if(msgBufferPtr != NULL_PTR)
  {
    EthTSyn_SwtMgmtRx_ProcessMsgBuffer(msgBufferPtr);                                                                  /* SBSW_ETHTSYN_POINTER_VARIABLE */
  }
  else if((stateMachine != ETHTSYN_SM_IDENT_INVALID) && (portIdx < EthTSyn_GetSizeOfPort())) /* PRQA S 3415 */ /* MD_EthTSyn_3415_CslReadOnly */
  {
    EthTSyn_SwtMgmt_TriggerStateMachine(stateMachine, portIdx);
  }
  else
  {
    /* Nothing to do here. */
  }
} /* EthTSyn_SwtMgmt_StoreSwitchEgressTimestamp() */
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_StoreSwitchIngressTimestamp
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
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_StoreSwitchIngressTimestamp(
                  EthTSyn_IntCtrlIdxType   CtrlIdx,
  ETHTSYN_P2CONST(uint8)                   DataPtr,
  ETHTSYN_P2CONST(EthTSyn_SwtMgmtInfoType) MgmtInfoPtr,
  ETHTSYN_P2CONST(Eth_TimeStampType)       TimeStampPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_P2VAR(EthTSyn_SwtMgmt_MsgBufferType) msgBufferPtr = NULL_PTR;
  ETHTSYN_P2VAR(Eth_TimeStampType) ingressTsPtr = NULL_PTR;
  ETHTSYN_P2VAR(EthTSyn_TimestampStateType) ingressTsStatePtr = NULL_PTR;
  EthTSyn_SmIdentEnumType stateMachine = ETHTSYN_SM_IDENT_INVALID;
  EthTSyn_IntPortIdxType portIdx = EthTSyn_GetSizeOfPort();

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the timestamp is given for received or transmitted message. */
  if(EthTSyn_SwtMgmt_GetMappedMsgBuffer(CtrlIdx, DataPtr, MgmtInfoPtr->FrameId, &msgBufferPtr) == E_OK)                /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
  {
    if(msgBufferPtr != NULL_PTR)
    {
      ingressTsPtr = &msgBufferPtr->IngressTimestampMgmt.Timestamp;
      ingressTsStatePtr = &msgBufferPtr->IngressTimestampMgmt.State;
    }
  }
  else
  {
    /* Initialize message buffer ptr */
    msgBufferPtr = NULL_PTR;
    /* Try to get mapped state machine (Tx) */
    stateMachine = EthTSyn_SwtMgmt_GetMappedStateMachine(CtrlIdx, DataPtr, MgmtInfoPtr->FrameId, &portIdx);            /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
    if(stateMachine != ETHTSYN_SM_IDENT_INVALID)
    {
      (void)EthTSyn_SwtMgmt_GetStateMachineTxTimestampInfo(stateMachine, portIdx,
          ETHTSYN_TS_DIR_INGRESS, &ingressTsPtr, &ingressTsStatePtr);                                                  /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
    }
  }


  /* #20 Check if either Rx or Tx message/state machine is available. */
  if( (ingressTsPtr != NULL_PTR) && (ingressTsStatePtr != NULL_PTR) )
  {
    /* #200 Check if egress timestamp is available. */
    if(TimeStampPtr == NULL_PTR)
    {
      /* #2000 Timestamp is not available -> mark TimeStamp as not available */
      *ingressTsStatePtr |= ETHTSYN_TIMESTAMP_STATE_AVAILABLE_FLAG_VALID_MASK;                                         /* SBSW_ETHTSYN_POINTER_VARIABLE_WRITE */
      *ingressTsStatePtr &= (EthTSyn_TimestampStateType)~(ETHTSYN_TIMESTAMP_STATE_AVAILABLE_MASK);                     /* SBSW_ETHTSYN_POINTER_VARIABLE_WRITE */
    }
    else
    {
      /* #2001 Timestamp available -> copy timestamp and mark it as available. */
      *ingressTsStatePtr |=
        (ETHTSYN_TIMESTAMP_STATE_AVAILABLE_FLAG_VALID_MASK | ETHTSYN_TIMESTAMP_STATE_AVAILABLE_MASK);                  /* SBSW_ETHTSYN_POINTER_VARIABLE_WRITE */
      *ingressTsPtr = *TimeStampPtr;                                                                                   /* SBSW_ETHTSYN_POINTER_VARIABLE_WRITE */
    }
  }

  /* #30 Trigger processing of message buffer (received message) or state machine (transmitted message). */
  if(msgBufferPtr != NULL_PTR)
  {
    EthTSyn_SwtMgmtRx_ProcessMsgBuffer(msgBufferPtr);                                                                  /* SBSW_ETHTSYN_POINTER_VARIABLE */
  }
  else if((stateMachine != ETHTSYN_SM_IDENT_INVALID) && (portIdx < EthTSyn_GetSizeOfPort())) /* PRQA S 3415 */ /* MD_EthTSyn_3415_CslReadOnly */
  {
    EthTSyn_SwtMgmt_TriggerStateMachine(stateMachine, portIdx);
  }
  else
  {
    /* Nothing to do here. */
  }

} /* EthTSyn_SwtMgmt_StoreSwitchIngressTimestamp() */
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtRx_StoreSwitchMgmtInfo
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmtRx_StoreSwitchMgmtInfo(EthTSyn_IntCtrlIdxType CtrlIdx,
  ETHTSYN_P2CONST(uint8) DataPtr, ETHTSYN_P2CONST(EthTSyn_SwtMgmtInfoType) MgmtInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_P2VAR(EthTSyn_SwtMgmt_MsgBufferType) msgBufferPtr = NULL_PTR;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Try to get the corresponding message buffer. */
  if(EthTSyn_SwtMgmt_GetMappedMsgBuffer(CtrlIdx, DataPtr, MgmtInfoPtr->FrameId, &msgBufferPtr) == E_OK)                /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
  {
    if(msgBufferPtr != NULL_PTR)
    {
      /* #20 Verify the passed management info. */
      if( (MgmtInfoPtr->SwitchIdx == ETHTSYN_INVALID_ETHIF_SWITCH_IDX) ||
          (MgmtInfoPtr->PortIdx == ETHTSYN_INVALID_SWITCH_PORT_IDX) )
      {
        /* #200 Passed management info invalid -> release message buffer and drop message. */
        EthTSyn_SwtMgmt_ReleaseMsgBuffer(msgBufferPtr);                                                                /* SBSW_ETHTSYN_POINTER_VARIABLE */
      }
      else
      {
        /* #201 Passed management info valid -> store switch management information in the message buffer and process
         * the message buffer. */
        msgBufferPtr->SwtMgmtInfo.SwitchIdx = MgmtInfoPtr->SwitchIdx;                                                  /* SBSW_ETHTSYN_POINTER_VARIABLE_WRITE */
        msgBufferPtr->SwtMgmtInfo.PortIdx = MgmtInfoPtr->PortIdx;                                                      /* SBSW_ETHTSYN_POINTER_VARIABLE_WRITE */

        /* Set message buffer state to port info available. */
        msgBufferPtr->MsgBufferState = ETHTSYN_S_MSG_BUFFER_PORT_INFO_AVAILABLE;                                       /* SBSW_ETHTSYN_POINTER_VARIABLE_WRITE */

        EthTSyn_SwtMgmtRx_ProcessMsgBuffer(msgBufferPtr);                                                              /* SBSW_ETHTSYN_POINTER_VARIABLE */
      }
    }
  }
} /* EthTSyn_SwtMgmtRx_StoreSwitchMgmtInfo() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtRx_ProcessMsgBuffer
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmtRx_ProcessMsgBuffer(
    ETHTSYN_P2VAR(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr)
{
  /*
  * TimeDomainId is known from message
  * TimeDomainIdx can be retrieved using the TimeDomainId
  * The EthTSyn-Port can be found by iterating all Ports of the TimeDomain(Idx)
  * The EthTSyn-Port has to match the CtrlIdx and the SwtPortIdx
  * Within a TimeDomain only one Port for the pair of EthIf-Ctrl and Swt-Port can exist
  */

  /* ----- Implementation --------------------------------------------- */
  /* #10 Check if message is ready for processing. */
  if(EthTSyn_SwtMgmtRx_IsMsgBufferReadyForProcessing(MsgBufferPtr) == TRUE)                                            /* SBSW_ETHTSYN_PASSING_API_POINTER */
  {
    /* #20 Message is ready for processing -> get matching EthTSyn Port and set message buffer state to processing. */
    const EthTSyn_IntPortIdxType portIdx = EthTSyn_SwtMgmtRx_GetPortForMsgBuffer(MsgBufferPtr);                        /* SBSW_ETHTSYN_PASSING_API_POINTER */

    MsgBufferPtr->MsgBufferState = ETHTSYN_S_MSG_BUFFER_MSG_PROCESSING;                                                /* SBSW_ETHTSYN_VALID_API_POINTER */

    if(portIdx < EthTSyn_GetSizeOfPort())
    {
      /* #30 Valid port found --> process message */
      EthTSyn_SwtMgmtRx_ProcRcvdMsg(portIdx, MsgBufferPtr);                                                            /* SBSW_ETHTSYN_PASSING_API_POINTER */
    }
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
    else
    {
      /* #40 No valid port found. Maybe a switch sync frame was received. Handle it. */
      EthTSyn_SwtTimeSync_SwtSyncFrameHandleRx(MsgBufferPtr);
    }
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */

    /* #50 Release the message buffer. */
    EthTSyn_SwtMgmt_ReleaseMsgBuffer(MsgBufferPtr);                                                                    /* SBSW_ETHTSYN_PASSING_API_POINTER */
  }
} /* EthTSyn_SwtMgmtRx_ProcessMsgBuffer() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtRx_IsMsgBufferReadyForProcessing
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_SwtMgmtRx_IsMsgBufferReadyForProcessing(
  ETHTSYN_P2CONST(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isReady = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if timestamp indications were already called. */
  /* PRQA S 3415 3 */ /* MD_EthTSyn_3415_ReadOnly */
  if( (EthTSyn_IsTimestampReadyToProcess(MsgBufferPtr->IngressTimestampMgmt.State) == TRUE)
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
      && (EthTSyn_IsTimestampReadyToProcess(MsgBufferPtr->EgressTimestampHostPortMgmt.State) == TRUE)
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */
  )
  {
    /* #20 Check if Port info is available. */
    if(MsgBufferPtr->MsgBufferState == ETHTSYN_S_MSG_BUFFER_PORT_INFO_AVAILABLE)
    {
      /* #30 Ready to process message. */
      isReady = TRUE;
    }
  }

  return isReady;
} /* EthTSyn_SwtMgmtRx_IsMsgBufferReadyForProcessing() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtRx_GetPortForMsgBuffer
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
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntPortIdxType, ETHTSYN_CODE) EthTSyn_SwtMgmtRx_GetPortForMsgBuffer(
  ETHTSYN_P2CONST(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_PortIndIterType portIndIter;
  EthTSyn_IntPortIdxType portIdx = EthTSyn_GetSizeOfPort();

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all EthTSyn ports. */
  for(portIndIter = EthTSyn_GetPortIndStartIdxOfCtrl(MsgBufferPtr->CtrlIdx);
      portIndIter < EthTSyn_GetPortIndEndIdxOfCtrl(MsgBufferPtr->CtrlIdx);
      portIndIter++)
  {
    const EthTSyn_PortIndType tmpPortIdx = EthTSyn_GetPortInd(portIndIter);
    /* #20 Verify that port is a switch port. */
    if(EthTSyn_IsSwitchPortMgmtUsedOfPort(tmpPortIdx) == TRUE)
    {
      const EthTSyn_SwitchPortMgmtIdxOfPortType swtPortMgmtIdx = EthTSyn_GetSwitchPortMgmtIdxOfPort(tmpPortIdx);
      /* #30 For Switch port, check if switch port info matches. */
      /* PRQA S 3415 2 */ /* MD_EthTSyn_3415_CslReadOnly */
      if((EthTSyn_GetSwitchIdxOfSwitchPortMgmt(swtPortMgmtIdx) == MsgBufferPtr->SwtMgmtInfo.SwitchIdx) &&
          (EthTSyn_GetPortIdxOfSwitchPortMgmt(swtPortMgmtIdx) == MsgBufferPtr->SwtMgmtInfo.PortIdx))
      {
        const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(tmpPortIdx);
        /* #40 Matching HW-Port found. Verify time domain. */
        if(EthTSyn_GetIdOfTimeDomain(timeDomainIdx) == MsgBufferPtr->Msg.MsgHdr.DomainNumber)
        {
          /* #400 Matching EthTSyn port found -> stop iteration. */
          portIdx = (EthTSyn_IntPortIdxType)tmpPortIdx;
          break;
        }
      }
    }
  }

  return portIdx;
} /* EthTSyn_SwtMgmtRx_GetPortForMsgBuffer() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtRx_ProcRcvdMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmtRx_ProcRcvdMsg(EthTSyn_IntPortIdxType PortIdx,
  ETHTSYN_P2VAR(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr) /* PRQA S 3673 */ /* MD_EthTSyn_3673_Pre */
{
  /* ----- Implementation ----------------------------------------------- */
  switch(ETHTSYN_HDR_COM_MSG_TYPE(MsgBufferPtr->Msg.MsgHdr.TransSpecific_MessageType))
  {
# if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_PDELAY_REQ:
    {
      /* Process Pdelay_Req message. */
      EthTSyn_SwtMgmt_ProcRcvdPdReqMsg(PortIdx, MsgBufferPtr);                                                         /* SBSW_ETHTSYN_PASSING_API_POINTER */
      break;
    }
# endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_PDELAY_RESP:
    {
      EthTSyn_SwtMgmt_ProcRcvdPdRespMsg(PortIdx, MsgBufferPtr);                                                        /* SBSW_ETHTSYN_PASSING_API_POINTER */
      break;
    }

  case ETHTSYN_MSG_TYPE_PDELAY_RES_FOLLOW_UP:
    {
      EthTSyn_SwtMgmt_ProcRcvdPdRespFupMsg(PortIdx, MsgBufferPtr);                                                     /* SBSW_ETHTSYN_PASSING_API_POINTER */
      break;
    }
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_SYNC:
    {
      EthTSyn_SwtMgmt_ProcRcvdSyncMsg(PortIdx, MsgBufferPtr);                                                          /* SBSW_ETHTSYN_PASSING_API_POINTER */
      break;
    }

  case ETHTSYN_MSG_TYPE_FOLLOW_UP:
    {
      EthTSyn_SwtMgmt_ProcRcvdFupMsg(PortIdx, MsgBufferPtr);                                                           /* SBSW_ETHTSYN_PASSING_API_POINTER */
      break;
    }
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_ANNOUNCE:
    {
      EthTSyn_SwtMgmt_ProcRcvdAnnounceMsg(PortIdx, MsgBufferPtr);                                                      /* SBSW_ETHTSYN_PASSING_API_POINTER */
      break;
    }
# endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */

  default:
    {
      /* Nothing to do here. */
      break;
    }
  } /* END: switch(msgType) */
} /* EthTSyn_SwtMgmtRx_ProcRcvdMsg() */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtRx_ForwardSyncMsgToEndStation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmtRx_ForwardSyncMsgToEndStation(
                  EthTSyn_IntTimeDomainIdxType   TimeDomainIdx,
  ETHTSYN_P2CONST(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwtMgmt_RxFrameInfoType rxFrameInfo;
  EthTSyn_IntPortIdxType portIdxOfEndStationSlavePort = EthTSyn_SwtMgmt_GetEndStationSlavePortIdx(TimeDomainIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the message has to be forwarded to the EthTSyn End-Station. */
  if(portIdxOfEndStationSlavePort < EthTSyn_GetSizeOfPort())
  {
    ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) ingressTimestampPtr = NULL_PTR;
#  if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
    if(MsgBufferPtr->IngressTimestampHostCtrlMgmt.State ==
        ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_AVAILABLE)
    {
      ingressTimestampPtr = (ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType))
                                  &MsgBufferPtr->IngressTimestampHostCtrlMgmt.Timestamp;
    }
#  else
    if(MsgBufferPtr->IngressTimestampMgmt.State ==
        ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_AVAILABLE)
    {
      ingressTimestampPtr = (ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType))
                                  &MsgBufferPtr->IngressTimestampMgmt.Timestamp;
    }
#  endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */
    if(ingressTimestampPtr != NULL_PTR)
    {
      /* #20 Pass the message to the End-Station. */
      rxFrameInfo.IngressTimestamp = *ingressTimestampPtr;
      EthTSyn_EndStation_Slave_ProcRcvdSyncMsg(portIdxOfEndStationSlavePort, &MsgBufferPtr->Msg.MsgHdr,
          &rxFrameInfo);                                                                                               /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
    }
  }
} /* EthTSyn_SwtMgmtRx_ForwardSyncMsgToEndStation() */
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtRx_ForwardFollowUpMsgToEndStation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmtRx_ForwardFollowUpMsgToEndStation(
                EthTSyn_IntPortIdxType         PortIdx,
                EthTSyn_IntTimeDomainIdxType   TimeDomainIdx,
  ETHTSYN_P2VAR(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr) /* PRQA S 3673 */ /* MD_EthTSyn_3673_Pre */
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_IntPortIdxType endStationSlavePortIdx = EthTSyn_SwtMgmt_GetEndStationSlavePortIdx(TimeDomainIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the message has to be forwarded to the EthTSyn End-Station. */
  if(endStationSlavePortIdx < EthTSyn_GetSizeOfPort())
  {
    /* #20 Adopt the follow up correction field by adding the switch residence time and Pdelay. */
#  if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
    const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
    ETHTSYN_CONSTP2VAR(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(slavePortIdx);
    EthTSyn_PdelayType pDelay = EthTSyn_Pdelay_GetCurrentPdelay(PortIdx);
    EthTSyn_TimediffType followUpCorrectionFieldNs = (EthTSyn_TimediffType)
        ETHTSYN_GET_FOLLOW_UP_CORRECTION_VALUE_NS_FROM_MSG(MsgBufferPtr->Msg.MsgHdr.CorrectionField);

    followUpCorrectionFieldNs += (EthTSyn_TimediffType)pDelay;
    /* PRQA S 3415 2 */ /* MD_EthTSyn_3415_ReadOnly */
    if((EthTSyn_IsTimestampReadyToProcess(syncReceiveSmPtr->Sync.IngressTimestampMgmt.State) == TRUE) &&
        (EthTSyn_IsTimestampReadyToProcess(syncReceiveSmPtr->Sync.EgressTimestampMgmtHostPort.State) == TRUE))
    {
      EthTSyn_TimediffType residenceTime;
      if(EthTSyn_Util_TimestampMinusTimestamp(&syncReceiveSmPtr->Sync.EgressTimestampMgmtHostPort.Timestamp,
          &syncReceiveSmPtr->Sync.IngressTimestampMgmt.Timestamp, &residenceTime) == E_OK)                             /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
      {
        followUpCorrectionFieldNs += residenceTime;
      }
    }
    else
    {
      /* Use default residence Time */
      followUpCorrectionFieldNs += (EthTSyn_TimediffType)ETHTSYN_SWT_RX_TO_UPLINK_RESIDENCE_TIME_NS;
    }
    EthTSyn_CopyFollowUpCorrectionField((uint64)followUpCorrectionFieldNs, MsgBufferPtr->Msg.MsgHdr.CorrectionField);  /* SBSW_ETHTSYN_ARRAY_SIZE */
#  else
    ETHTSYN_DUMMY_STATEMENT(PortIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#  endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */
    /* #30 Pass the message to the end station implementation. */
    EthTSyn_SlaveRx_ProcRcvdFupMsg(
      (ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType))&MsgBufferPtr->Msg, endStationSlavePortIdx); /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */ /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
  }
} /* EthTSyn_SwtMgmtRx_ForwardFollowUpMsgToEndStation() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_TriggerStateMachine
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_TriggerStateMachine(
    EthTSyn_SmIdentEnumType StateMachine, EthTSyn_IntPortIdxType PortIdx)
{
  switch(StateMachine)
  {
#  if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
    case ETHTSYN_SM_IDENT_PDELAY_RESP:
      {
        EthTSyn_Pdelay_ProcSmPdResp(PortIdx);
        break;
      }
#  endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

    case ETHTSYN_SM_IDENT_SYNC_SEND:
      {
        EthTSyn_Master_ProcessSmSyncSend(PortIdx);
        break;
      }

    default:
      {
        /* Nothing to do here. */
        break;
      }
  }
} /* EthTSyn_SwtMgmt_TriggerStateMachine() */
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_ProcRcvdPdReqMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_ProcRcvdPdReqMsg(EthTSyn_IntPortIdxType PortIdx,
  ETHTSYN_P2CONST(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Port is pdelay responder. */
  if(EthTSyn_Util_IsPdelayResponder(PortIdx) == TRUE)
  {
    const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    const EthTSyn_PdelayResponderIdxOfPdelayConfigType pDelayResponderIdx =
        EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pDelayCfgIdx);
    const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pDelayRespSmIdx =
        EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pDelayResponderIdx);
    EthTSyn_PdelayRespSmPtrType pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);
    /* #20 Check if Pdelay_Req is expected */
    if(pDelayRespSmPtr->State == ETHTSYN_S_PD_RESP_SM_WAIT_REQ)
    {
      /* #30 Check if ingress timestamp is available */
      if(EthTSyn_Util_IsTimestampAvailable(MsgBufferPtr->IngressTimestampMgmt.State) == TRUE)
      {
        /* #40 Process message. */
        ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

        /* set PdelayResp procedure as in progress to avoid clock change settings in this phase */
        pDelayRespSmPtr->InProgress = TRUE;                                                                            /* SBSW_ETHTSYN_CSL03 */

        /* store message attributes */
        EthTSyn_SetClockIdentity(pDelayRespSmPtr->PdelayReq.SourcePortIdentity.ClockIdentity,
            MsgBufferPtr->Msg.MsgHdr.SourceClockIdentity);                                                             /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */ /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */

        pDelayRespSmPtr->PdelayReq.SourcePortIdentity.PortNumber =
            (uint16)EthTSyn_Ntohs(MsgBufferPtr->Msg.MsgHdr.SourcePortNumber);                                          /* SBSW_ETHTSYN_CSL03 */

        pDelayRespSmPtr->PdelayReq.SequenceId = (uint16)EthTSyn_Ntohs(MsgBufferPtr->Msg.MsgHdr.SequenceId);            /* SBSW_ETHTSYN_CSL03 */

        pDelayRespSmPtr->PdelayReq.IngressTimestampMgmt = MsgBufferPtr->IngressTimestampMgmt;                          /* SBSW_ETHTSYN_CSL03 */

        /* trigger transmission of PdelayResp message */
        pDelayRespSmPtr->State = ETHTSYN_S_PD_RESP_SM_TX_RESP;                                                         /* SBSW_ETHTSYN_CSL03 */

        ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

        EthTSyn_Pdelay_ProcSmPdResp(PortIdx);
      }
    }
  }
} /* EthTSyn_SwtMgmt_ProcRcvdPdReqMsg() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
# endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_ProcRcvdPdRespMsg
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
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_ProcRcvdPdRespMsg(
                  EthTSyn_IntPortIdxType         PortIdx,
  ETHTSYN_P2CONST(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_P2CONST(EthTSyn_PdelayRespMsgType) pDelayRespMsgPtr;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if port is Pdelay initiator. */
  if(EthTSyn_Util_IsPdelayInitiator(PortIdx) == TRUE)
  {
    const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
      EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
    const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
      EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
    ETHTSYN_CONSTP2VAR(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);

    ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    pDelayRespMsgPtr = (ETHTSYN_P2CONST(EthTSyn_PdelayRespMsgType))&MsgBufferPtr->Msg.Payload[0]; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */

    /* #20 Check Pdelay request state machine state. */
    switch(pDelayReqSmPtr->State)
    {
    case ETHTSYN_S_PD_REQ_SM_WAIT_RESP:
      {
        /* #200 State: Waiting for Pdelay response -> Check message attributes. */
        /* PRQA S 0310, 3415 4 */ /* MD_EthTSyn_0310_PortIdent, MD_EthTSyn_3415_ReadOnly */
        if((EthTSyn_PortIdentityIsEqualLocalPort(PortIdx,
            (ETHTSYN_P2CONST(EthTSyn_PortIdentityType))pDelayRespMsgPtr->RequestingClockIdentity) == TRUE) &&
            (EthTSyn_Ntohs(MsgBufferPtr->Msg.MsgHdr.SequenceId) == pDelayReqSmPtr->PdelayReq.SequenceId))              /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */
        {
          /* #2000 Check if Pdelay request ingress timestamp is available and process message if available. */
          if(EthTSyn_Util_IsTimestampAvailable(MsgBufferPtr->IngressTimestampMgmt.State) == TRUE)
          {
            pDelayReqSmPtr->PdelayResp.IngressTimestampMgmt = MsgBufferPtr->IngressTimestampMgmt;                      /* SBSW_ETHTSYN_CSL03 */
#  if ( (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) && (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF) )
            pDelayReqSmPtr->PdelayResp.IngressTimestampRaw = MsgBufferPtr->IngressTimestampMgmt.Timestamp.nanoseconds; /* SBSW_ETHTSYN_CSL03 */
#  endif /* ( (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) && (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF) ) */

            pDelayReqSmPtr->PdelayResp.SequenceId = (uint16)EthTSyn_Ntohs(MsgBufferPtr->Msg.MsgHdr.SequenceId);        /* SBSW_ETHTSYN_CSL03 */
            EthTSyn_SetClockIdentity(pDelayReqSmPtr->PdelayResp.SourcePortIdentity.ClockIdentity,
                MsgBufferPtr->Msg.MsgHdr.SourceClockIdentity);                                                         /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */ /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
            pDelayReqSmPtr->PdelayResp.SourcePortIdentity.PortNumber =
                (uint16)EthTSyn_Ntohs(MsgBufferPtr->Msg.MsgHdr.SourcePortNumber);                                      /* SBSW_ETHTSYN_CSL03 */
            /* PRQA S 0310 2 */ /* MD_EthTSyn_0310_Timestamp */
            EthTSyn_NtohTimestamp(&pDelayReqSmPtr->PdelayResp.RequestReceiptTimestamp,
                (ETHTSYN_P2VAR(EthTSyn_TimestampType))pDelayRespMsgPtr->RequestReceiptTimestampSeconds);               /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */ /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */

            pDelayReqSmPtr->State = ETHTSYN_S_PD_REQ_SM_WAIT_RESP_FUP;                                                 /* SBSW_ETHTSYN_CSL03 */
          }
        }
        else
        {
          /* #2001 PdelayResp message has incorrect attributes -> Reset */
          /* check for lost responses limit */
          if(pDelayReqSmPtr->LostResponses < EthTSyn_GetAllowedLostResponsesOfPdelayInitiator(pDelayInitiatorIdx))
          {
            pDelayReqSmPtr->LostResponses++;                                                                           /* SBSW_ETHTSYN_CSL03 */
          }
          else /* lost responses limit is exceeded */
          {
            EthTSyn_Util_SetAsCapable(PortIdx, FALSE);
          }

          pDelayReqSmPtr->State = ETHTSYN_S_PD_REQ_SM_TX_REQ;                                                          /* SBSW_ETHTSYN_CSL03 */
        }
        break;
      }

    case ETHTSYN_S_PD_REQ_SM_WAIT_RESP_FUP:
      {
        /* #201 State: Waiting for Pdelay response follow up -> check for double PdelayResp message. */
        if(pDelayReqSmPtr->PdelayReq.SequenceId == EthTSyn_Ntohs(MsgBufferPtr->Msg.MsgHdr.SequenceId))
        {
          /* #2010 Received PdelayResp message with same SequenceId twice -> Reset */
          /* check for lost responses limit */
          if(pDelayReqSmPtr->LostResponses < EthTSyn_GetAllowedLostResponsesOfPdelayInitiator(pDelayInitiatorIdx))
          {
            pDelayReqSmPtr->LostResponses++;                                                                           /* SBSW_ETHTSYN_CSL03 */
          }
          else /* lost responses limit is exceeded */
          {
            EthTSyn_Util_SetAsCapable(PortIdx, FALSE);
          }

          pDelayReqSmPtr->State = ETHTSYN_S_PD_REQ_SM_TX_REQ;                                                          /* SBSW_ETHTSYN_CSL03 */
        }
        break;
      }

    default:
      {
        /* Nothing to do here. */
        break;
      }

    } /* END: switch(pDelayReqSmPtr->State) */

    ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  } /* END: if(IsPdelayInitiator) */
} /* EthTSyn_SwtMgmt_ProcRcvdPdRespMsg() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_ProcRcvdPdRespFupMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_ProcRcvdPdRespFupMsg(
                  EthTSyn_IntPortIdxType         PortIdx,
  ETHTSYN_P2CONST(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_P2CONST(EthTSyn_PDelayResFollowUpMsgType) pDelayRespFollowUpMsgPtr;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if port is Pdelay initiator. */
  if(EthTSyn_Util_IsPdelayInitiator(PortIdx) == TRUE)
  {
    const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
      EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
    const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
      EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
    ETHTSYN_CONSTP2VAR(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);
    ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    pDelayRespFollowUpMsgPtr = (ETHTSYN_P2CONST(EthTSyn_PDelayResFollowUpMsgType)) &MsgBufferPtr->Msg.Payload[0]; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */

    /* #20 Check Pdelay request state machine state. */
    if(pDelayReqSmPtr->State == ETHTSYN_S_PD_REQ_SM_WAIT_RESP_FUP)
    {
      /* #30 Verify message attributes. */
      /* PRQA S 3415, 0310 7 */ /* MD_EthTSyn_3415_ReadOnly, MD_EthTSyn_0310_PortIdent */
      if((EthTSyn_Ntohs(MsgBufferPtr->Msg.MsgHdr.SequenceId) == pDelayReqSmPtr->PdelayReq.SequenceId ) &&
          (EthTSyn_PortIdentityIsEqual(
              (ETHTSYN_P2CONST(EthTSyn_PortIdentityType))&pDelayReqSmPtr->PdelayResp.SourcePortIdentity,
              (ETHTSYN_P2CONST(EthTSyn_PortIdentityType))MsgBufferPtr->Msg.MsgHdr.SourceClockIdentity) == TRUE) &&
          (EthTSyn_PortIdentityIsEqualLocalPort(
              PortIdx,
              (ETHTSYN_P2CONST(EthTSyn_PortIdentityType))pDelayRespFollowUpMsgPtr->RequestingClockIdentity) == TRUE))  /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */ /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
      {
        /* #40 Receive message and handle state machine. */
        /* store massage attributes */
        /* PRQA S 0310 2 */ /* MD_EthTSyn_0310_Timestamp */
        EthTSyn_NtohTimestamp(&pDelayReqSmPtr->PdelayRespFollowUp.ResponseOriginTimestampMgmt.Timestamp,
            (ETHTSYN_P2VAR(EthTSyn_TimestampType))pDelayRespFollowUpMsgPtr->ResponseOriginTimestampSeconds);           /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */

        /* reset LostResponses counter */
        pDelayReqSmPtr->LostResponses = 0;                                                                             /* SBSW_ETHTSYN_CSL03 */

        /* check if the PdelayResp was not from own system */
        /* PRQA S 3415 3 */ /* MD_EthTSyn_3415_ReadOnly */
        if(EthTSyn_ClockIdentityIsEqual(MsgBufferPtr->Msg.MsgHdr.SourceClockIdentity,
          (EthTSyn_GetAddrCtrlState(EthTSyn_GetCtrlIdxOfPort(PortIdx)))->ClockIdentity) == FALSE)                      /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
        {
          /* valid PdelayResp and PdelayRespFollowUp were received -> path delay calculation in MainFunction context
        is possible, after PdelayReq message was transmitted successfully (indicated by TxConfirmationPending
        flag)*/
          pDelayReqSmPtr->State = ETHTSYN_S_PD_REQ_SM_COMPUTE_PDELAY; /* SBSW_ETHTSYN_CSL03 */
        }
      }
    }

    ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  } /* END: if(IsPdelayInitiator) */
} /* EthTSyn_SwtMgmt_ProcRcvdPdRespMsg() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_ProcRcvdSyncMsg
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_ProcRcvdSyncMsg(
                  EthTSyn_IntPortIdxType         PortIdx,
  ETHTSYN_P2CONST(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_IntTimeDomainIdxType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if sync message can be received on given Port.  */
  if(EthTSyn_SwtMgmtRx_CheckSyncMsgReception(PortIdx,
      (ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType))&MsgBufferPtr->Msg.MsgHdr) == TRUE)                                   /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
  {
    const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
    ETHTSYN_CONSTP2VAR(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(slavePortIdx);
    ETHTSYN_CONSTP2VAR(EthTSyn_SiteSyncSyncSmType) siteSyncSyncSmPtr = EthTSyn_GetAddrSiteSyncSyncSm(timeDomainIdx);

    /* #20 Check if ingress timestamp is available. */
    if(EthTSyn_Util_IsTimestampAvailable(MsgBufferPtr->IngressTimestampMgmt.State) == TRUE)
    {
      /* #30 Store required message attributes and handle sync receive state machine. */
      /* Store the timestamp */
      syncReceiveSmPtr->Sync.IngressTimestampMgmt.Timestamp = MsgBufferPtr->IngressTimestampMgmt.Timestamp;            /* SBSW_ETHTSYN_CSL03 */
      syncReceiveSmPtr->Sync.IngressTimestampMgmt.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_AVAILABLE;        /* SBSW_ETHTSYN_CSL03 */

#  if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
      if(EthTSyn_Util_IsTimestampAvailable(MsgBufferPtr->EgressTimestampHostPortMgmt.State) == TRUE)
      {
        syncReceiveSmPtr->Sync.EgressTimestampMgmtHostPort.Timestamp =
          MsgBufferPtr->EgressTimestampHostPortMgmt.Timestamp;                                                         /* SBSW_ETHTSYN_CSL03 */
        syncReceiveSmPtr->Sync.EgressTimestampMgmtHostPort.State =
          ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_AVAILABLE;                                                        /* SBSW_ETHTSYN_CSL03 */
      }
      else
      {
        syncReceiveSmPtr->Sync.EgressTimestampMgmtHostPort.State =
            ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_NOT_AVAILABLE;                                                  /* SBSW_ETHTSYN_CSL03 */
      }
#  endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */
    }

    /* Store Sync message attributes */
    syncReceiveSmPtr->Sync.LogMessageInterval = MsgBufferPtr->Msg.MsgHdr.LogMessageInterval;                           /* SBSW_ETHTSYN_CSL03 */

    EthTSyn_SetClockIdentity(syncReceiveSmPtr->Sync.SourcePortIdentity.ClockIdentity,
        MsgBufferPtr->Msg.MsgHdr.SourceClockIdentity);                                                                 /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */ /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */

    syncReceiveSmPtr->Sync.SourcePortIdentity.PortNumber =
        (uint16)EthTSyn_Ntohs(MsgBufferPtr->Msg.MsgHdr.SourcePortNumber);                                              /* SBSW_ETHTSYN_CSL03 */

    syncReceiveSmPtr->Sync.SequenceId = (uint16)EthTSyn_Ntohs(MsgBufferPtr->Msg.MsgHdr.SequenceId);                    /* SBSW_ETHTSYN_CSL03 */

    /* change state to waiting for FollowUp */
    syncReceiveSmPtr->State = ETHTSYN_S_SYNC_RCV_SM_WAIT_FUP;                                                          /* SBSW_ETHTSYN_CSL03 */
    /* set FollowUp receive timeout time */
    syncReceiveSmPtr->FollowUp.FollowUpRxTimeoutCnt =
        EthTSyn_GetFollowUpAlloweRxDelayOfSlavePort(EthTSyn_GetSlavePortIdxOfPort(PortIdx));                           /* SBSW_ETHTSYN_CSL03 */

    /* rest sync rx timeout cnt */
    syncReceiveSmPtr->Sync.SyncRxTimeoutCnt = EthTSyn_GetSwtMgmtSyncTimeoutOfTimeDomain(timeDomainIdx);                /* SBSW_ETHTSYN_CSL03 */

    /* #40 Handle SiteSyncSync state machine. */
    switch(siteSyncSyncSmPtr->State)
    {
    case ETHTSYN_S_SSS_SM_RCVD_FUP_AFTER_TIMEOUT:
    case ETHTSYN_S_SSS_SM_PENDING:
    case ETHTSYN_S_SSS_SM_TX_FUP:
      {
        /* Copy Message to SiteSyncSync Sync Message Buffer */
        /* PRQA S 0310 2 */ /* MD_EthTSyn_0310_IpBase */
        IpBase_Copy((ETHTSYN_P2VAR(IpBase_CopyDataType))&siteSyncSyncSmPtr->Msg.MsgHdr,                                /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */
            (ETHTSYN_P2CONST(IpBase_CopyDataType))
            &MsgBufferPtr->Msg.MsgHdr, ETHTSYN_HDR_COM_LENGTH);                                                        /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */

        /* PRQA S 0310 3 */ /* MD_EthTSyn_0310_IpBase */
        IpBase_Copy((ETHTSYN_P2VAR(IpBase_CopyDataType))siteSyncSyncSmPtr->Msg.Payload,                                /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */
            (ETHTSYN_P2CONST(IpBase_CopyDataType))MsgBufferPtr->Msg.Payload,
            ETHTSYN_SWT_MGMT_MSG_BUFFER_PAYLOAD_SIZE);                                                                 /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */

        /* Reset TxConfirmationPending of the SiteSyncSync state machine */
        if(EthTSyn_IsMasterPortUsedOfTimeDomain(timeDomainIdx) == TRUE)
        {
          siteSyncSyncSmPtr->TxConfirmationPending = EthTSyn_GetMasterPortLengthOfTimeDomain(timeDomainIdx);           /* SBSW_ETHTSYN_CSL03 */
        }
        else
        {
          siteSyncSyncSmPtr->TxConfirmationPending = 0;                                                                /* SBSW_ETHTSYN_CSL03 */
        }

        /* Change SiteSyncSyncSm state to 'SendSync' */
        siteSyncSyncSmPtr->State = ETHTSYN_S_SSS_SM_TX_SYNC;                                                           /* SBSW_ETHTSYN_CSL03 */

        /* Process Sm SiteSyncSync */
        EthTSyn_SwtMgmt_ProcessSmSiteSyncSync(timeDomainIdx);

        break;
      }

    case ETHTSYN_S_SSS_SM_SYNC_TIMEOUT:
      {
        siteSyncSyncSmPtr->State = ETHTSYN_S_SSS_SM_RCVD_SYNC_AFTER_TIMEOUT;                                           /* SBSW_ETHTSYN_CSL03 */
        break;
      }

    default:
      {
        /* Nothing to do here. */
        break;
      }
    }

    /* #50 Forward Sync message to End-Station if applicable. */
    EthTSyn_SwtMgmtRx_ForwardSyncMsgToEndStation(timeDomainIdx, MsgBufferPtr);                                         /* SBSW_ETHTSYN_PASSING_API_POINTER */
  }

} /* EthTSyn_SwtMgmt_ProcRcvdSyncMsg() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtRx_CheckSyncMsgReception
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_SwtMgmtRx_CheckSyncMsgReception(
                  EthTSyn_IntPortIdxType    PortIdx,
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) ComMsgPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint64 srcPortIdentity;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get source clock identity for later processing. */
  srcPortIdentity = EthTSyn_Util_TransformClockIdentityToUint64(ComMsgPtr->SourceClockIdentity);                       /* SBSW_ETHTSYN_STRUCT_ELEMENT_ARRAY_AS_POINTER */

  /* #20 Check if port is ready to receive the sync message. */
  return EthTSyn_SwtMgmtRx_IsPortReadyToReceiveSync(PortIdx, srcPortIdentity);
} /* EthTSyn_SwtMgmtRx_CheckSyncMsgReception() */
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtRx_IsPortReadyToReceiveSync
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_SwtMgmtRx_IsPortReadyToReceiveSync(
  EthTSyn_IntPortIdxType PortIdx,
  uint64                 SrcClockIdentity)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isReady = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Verify port role and handle possible Master-Slave conflict. */
  if(EthTSyn_UtilRx_SyncPortRoleCheckWithMasterSlaveConflictDetection(PortIdx, SrcClockIdentity) == TRUE)              /* SBSW_ETHTSYN_PASSING_API_POINTER */
  {
    const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
    ETHTSYN_CONSTP2VAR(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(slavePortIdx);
    /* #20 Check if port is AsCapable. */
    if(EthTSyn_Util_IsAsCapable(PortIdx) == TRUE)
    {
      /* #30 Check state of sync receive state machine. */
      if((syncReceiveSmPtr->State == ETHTSYN_S_SYNC_RCV_SM_DISCARD ) ||
          (syncReceiveSmPtr->State == ETHTSYN_S_SYNC_RCV_SM_WAIT_SYNC ) ||
          (syncReceiveSmPtr->State == ETHTSYN_S_SYNC_RCV_SM_SYNC_TIMEOUT))
      {
        isReady = TRUE;
      }
    }

    /* #40 If port is not ready to receive the sync message, change state of sync receive sm to DISCARD */
    if (isReady == FALSE)
    {
      const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
      const EthTSyn_IntPortIdxType portIdxOfEndStationSlavePort =
        EthTSyn_SwtMgmt_GetEndStationSlavePortIdx(timeDomainIdx);
      syncReceiveSmPtr->State = ETHTSYN_S_SYNC_RCV_SM_DISCARD;                                                         /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX_PTR_BY_INDIRECTION */
      /* Change state of end station sync receive sm to DISCARD as well (if applicable) */
      if (portIdxOfEndStationSlavePort < EthTSyn_GetSizeOfPort())
      {
        const EthTSyn_SlavePortIdxOfPortType endStationSlavePortIdx =
          EthTSyn_GetSlavePortIdxOfPort(portIdxOfEndStationSlavePort);
        ETHTSYN_CONSTP2VAR(EthTSyn_SyncReceiveSmType) endStationSyncReceiveSmPtr =
          EthTSyn_GetAddrSyncReceiveSm(endStationSlavePortIdx);
        endStationSyncReceiveSmPtr->State = ETHTSYN_S_SYNC_RCV_SM_DISCARD;                                             /* SBSW_ETHTSYN_CSL03 */
      }
    }
  }

  return isReady;
} /* EthTSyn_SwtMgmtRx_IsPortReadyToReceiveSync() */
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_ProcRcvdFupMsg
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
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_ProcRcvdFupMsg(
                EthTSyn_IntPortIdxType         PortIdx,
  ETHTSYN_P2VAR(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean receiveMessage = FALSE;
  const EthTSyn_IntTimeDomainIdxType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Verify that port is slave port. */
  if(EthTSyn_IsSlavePortUsedOfPort(PortIdx) == TRUE)
  {
    const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
    ETHTSYN_CONSTP2VAR(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(slavePortIdx);

    /* #20 Verify sync receive state machine state and matching sequence id (sync and follow up). */
    if ((syncReceiveSmPtr->State == ETHTSYN_S_SYNC_RCV_SM_WAIT_FUP) && /* PRQA S 3415 */ /* MD_EthTSyn_3415_ReadOnly */
      (EthTSyn_Ntohs(MsgBufferPtr->Msg.MsgHdr.SequenceId) == syncReceiveSmPtr->Sync.SequenceId))
    {
      /* #30 Check for matching source port identity of Sync and FollowUp. */
      /* PRQA S 3415 4 */ /* MD_EthTSyn_3415_ReadOnly */
      if ((EthTSyn_ClockIdentityIsEqual(MsgBufferPtr->Msg.MsgHdr.SourceClockIdentity,
        syncReceiveSmPtr->Sync.SourcePortIdentity.ClockIdentity) == TRUE) &&
        (EthTSyn_Ntohs(MsgBufferPtr->Msg.MsgHdr.SourcePortNumber) ==
          syncReceiveSmPtr->Sync.SourcePortIdentity.PortNumber))                                                       /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */ /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */
      {
        /* Received FollowUp from same node as the former Sync --> receive message */
        receiveMessage = TRUE;
      }
    }

    if (receiveMessage == TRUE)
    {
      EthTSyn_SiteSyncSyncSmPtrType siteSyncSyncSmPtr = EthTSyn_GetAddrSiteSyncSyncSm(timeDomainIdx);

      /* #40 Store message attributes. */
      syncReceiveSmPtr->FollowUp.SequenceId = (uint16)EthTSyn_Ntohs(MsgBufferPtr->Msg.MsgHdr.SequenceId);              /* SBSW_ETHTSYN_CSL02_03 */

      /* #50 Handle SiteSyncSyncSm. */
      switch (siteSyncSyncSmPtr->State)
      {
      case ETHTSYN_S_SSS_SM_PENDING:
      case ETHTSYN_S_SSS_SM_TX_SYNC:
        {
          /* #500 Copy FollowUp message to SiteSyncSync state machine */
          /* PRQA S 0310 2 */ /* MD_EthTSyn_0310_IpBase */
          IpBase_Copy((ETHTSYN_P2VAR(IpBase_CopyDataType))&siteSyncSyncSmPtr->Msg.MsgHdr,                              /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */
            (ETHTSYN_P2CONST(IpBase_CopyDataType))&MsgBufferPtr->Msg.MsgHdr, ETHTSYN_HDR_COM_LENGTH);                  /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */

          /* PRQA S 0310 3 */ /* MD_EthTSyn_0310_IpBase */
          IpBase_Copy((ETHTSYN_P2VAR(IpBase_CopyDataType))siteSyncSyncSmPtr->Msg.Payload,                              /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */
            (ETHTSYN_P2CONST(IpBase_CopyDataType))MsgBufferPtr->Msg.Payload,                                           /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
            ETHTSYN_SWT_MGMT_MSG_BUFFER_PAYLOAD_SIZE);

          /* #501 Reset TxConfirmationPending of SiteSyncSync state machine. */
          if (EthTSyn_IsMasterPortUsedOfTimeDomain(timeDomainIdx) == TRUE)
          {
            siteSyncSyncSmPtr->TxConfirmationPending = EthTSyn_GetMasterPortLengthOfTimeDomain(timeDomainIdx);         /* SBSW_ETHTSYN_CSL02 */
          }
          else
          {
            siteSyncSyncSmPtr->TxConfirmationPending = 0;                                                              /* SBSW_ETHTSYN_CSL02 */
          }

          /* #502 Change state of SiteSyncSyncSm to ETHTSYN_S_SSS_SM_TX_FUP. */
          siteSyncSyncSmPtr->State = ETHTSYN_S_SSS_SM_TX_FUP;                                                          /* SBSW_ETHTSYN_CSL02 */

          /* #503 Trigger provision of timestamp information for synchronization of switch if required. */
#  if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
          siteSyncSyncSmPtr->ProvideSwtTimeSyncTimestamps =                                                            /* SBSW_ETHTSYN_CSL02 */
            EthTSyn_SwtTimeSync_IsTimeDomainUsedForSwtSync(timeDomainIdx);
#  endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */

          /* #504 Process the SiteSyncSync state machine. */
          EthTSyn_SwtMgmt_ProcessSmSiteSyncSync(timeDomainIdx);

          break;
        }

      case ETHTSYN_S_SSS_SM_RCVD_SYNC_AFTER_TIMEOUT:
        {
          /* #505 Change state of site sync sync sm to RCVD_FUP_AFTER_TIMEOUT when state was RCVD_SYNC_AFTER_TIMEOUT. */
          siteSyncSyncSmPtr->State = ETHTSYN_S_SSS_SM_RCVD_FUP_AFTER_TIMEOUT;                                          /* SBSW_ETHTSYN_CSL02 */

          EthTSyn_SwtMgmt_ProcessSmSiteSyncSync(timeDomainIdx);

          break;
        }

      default:
        {
          /* Nothing to do here. */
          break;
        }
      }

      syncReceiveSmPtr->State = ETHTSYN_S_SYNC_RCV_SM_WAIT_SYNC;                                                       /* SBSW_ETHTSYN_CSL02_03 */


      /* #60 Forward FollowUp to End-Station if applicable. */
      EthTSyn_SwtMgmtRx_ForwardFollowUpMsgToEndStation(PortIdx, timeDomainIdx,
        (ETHTSYN_P2VAR(EthTSyn_SwtMgmt_MsgBufferType))MsgBufferPtr);                                                   /* SBSW_ETHTSYN_PASSING_API_POINTER */
    }

  } /* END: if(IsSlavePort) */

} /* EthTSyn_SwtMgmt_ProcRcvdFupMsg() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_ProcRcvdAnnounceMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_ProcRcvdAnnounceMsg(
                  EthTSyn_IntPortIdxType          PortIdx,
  ETHTSYN_P2CONST(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if port is ready to receive announce message. */
  if(EthTSyn_UtilRx_IsPortReadyToReceiveAnnounce(PortIdx) == TRUE)
  {
    /* #20 Check for valid Announce message. */
    if(EthTSyn_UtilRx_QualifyAnnounceMsg(PortIdx, &MsgBufferPtr->Msg.MsgHdr) == E_OK)                                  /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
    {
      const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
      const EthTSyn_AnnounceInfoIdxOfSlavePortType announceInfoIdx =
        EthTSyn_GetAnnounceInfoIdxOfSlavePort(slavePortIdx);
      const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
      ETHTSYN_CONSTP2VAR(EthTSyn_AnnounceReceiveSmType) announceRcvSmPtr =
        EthTSyn_GetAddrAnnounceReceiveSm(announceInfoIdx);
      ETHTSYN_CONSTP2CONST(EthTSyn_AnnounceMsgType)announceMsgPtr =
        (ETHTSYN_P2CONST(EthTSyn_AnnounceMsgType))&MsgBufferPtr->Msg.Payload[0]; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */

      /* reset announce timeout counter */
      announceRcvSmPtr->RxTimeoutCnt = EthTSyn_GetAnnounceAllowedRxDelayOfAnnounceInfo(announceInfoIdx);               /* SBSW_ETHTSYN_CSL02_03 */
      /* check if no Grandmaster is available */
      if(EthTSyn_IsGmPresentOfSystemState(timeDomainIdx) == FALSE)
      {
        EthTSyn_Slave_SetMasterPriorityVector(announceMsgPtr, timeDomainIdx);                                          /* SBSW_ETHTSYN_POINTER_VARIABLE */
      }
    }
  }
} /* EthTSyn_SwtMgmt_ProcRcvdAnnounceMsg() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
# endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_ReleaseMsgBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_ReleaseMsgBuffer(
    ETHTSYN_P2VAR(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr)
{
  ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #10 Release the message buffer. */
  MsgBufferPtr->MsgBufferState = ETHTSYN_S_MSG_BUFFER_UNUSED;                                                          /* SBSW_ETHTSYN_VALID_API_POINTER */
  /* #20 Reset the timestamp states */
  MsgBufferPtr->IngressTimestampMgmt.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_INVALID;                                /* SBSW_ETHTSYN_VALID_API_POINTER */
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
  MsgBufferPtr->EgressTimestampHostPortMgmt.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_INVALID;                         /* SBSW_ETHTSYN_VALID_API_POINTER */
# endif
  /* #30 Reset the switch mgmt info. */
  MsgBufferPtr->CtrlIdx = EthTSyn_GetSizeOfCtrl();                                                                     /* SBSW_ETHTSYN_VALID_API_POINTER */
  MsgBufferPtr->SwtMgmtInfo.SwitchIdx = ETHTSYN_INVALID_ETHIF_SWITCH_IDX;                                              /* SBSW_ETHTSYN_VALID_API_POINTER */
  MsgBufferPtr->SwtMgmtInfo.PortIdx = ETHTSYN_INVALID_SWITCH_PORT_IDX;                                                 /* SBSW_ETHTSYN_VALID_API_POINTER */

  /* #40 Reset Rx buffer pointer. */
  MsgBufferPtr->RxBufAddr = NULL_PTR;                                                                                  /* SBSW_ETHTSYN_VALID_API_POINTER */

  ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

} /* EthTSyn_SwtMgmt_ReleaseMsgBuffer() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtRx_PerformBasicMsgChecksAngGetMsgBuffer
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
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_SwtMgmtRx_PerformBasicMsgChecksAngGetMsgBuffer(
                  uint16                          LenByte,
  ETHTSYN_P2CONST(uint8)                          DataPtr,
    ETHTSYN_P2VAR(EthTSyn_SwtMgmt_MsgBufferType*) MsgBufferPtrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) comMsgHdrPtr;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Try to get a free message buffer. */
  if(EthTSyn_SwtMgmt_ProvideMsgBuffer(MsgBufferPtrPtr) == E_OK)                                                        /* SBSW_ETHTSYN_PASSING_API_POINTER */
  {
    /* #20 Message buffer available and locked. Perform general message checks. */
    errorId = EthTSyn_UtilRx_CheckMessageGeneral((ETHTSYN_P2CONST(uint8))DataPtr, LenByte);                            /* SBSW_ETHTSYN_PASSING_API_POINTER */
    if(errorId == ETHTSYN_E_NO_ERROR)
    {
      comMsgHdrPtr = (ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType))&DataPtr[0]; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */
      /* #30 General message checks passed. Check message type and length. */
      errorId = EthTSyn_UtilRx_CheckMessageTypeAndLength(comMsgHdrPtr, LenByte);                                       /* SBSW_ETHTSYN_POINTER_VARIABLE */
      if(errorId == ETHTSYN_E_NO_ERROR)
      {
        /* #40 Message type and length check passed. Ensure that message buffer is sufficient for the message. */
        if(ETHTSYN_SWT_MGMT_MSG_BUFFER_PAYLOAD_SIZE < (LenByte - ETHTSYN_HDR_COM_LENGTH))
        {
          /* insufficient buffer --> drop message */
          errorId = ETHTSYN_SWT_MGMT_E_MSG_BUFFER_PAYLOAD_OVERFLOW;
        }
      }
    }

    /* #50 Release message buffer if any message check failed. */
    if(errorId != ETHTSYN_E_NO_ERROR)
    {
      EthTSyn_SwtMgmt_ReleaseMsgBuffer(*MsgBufferPtrPtr);                                                              /* SBSW_ETHTSYN_VALID_API_POINTER */
    }
  }
  else
  {
    /* No message buffer available --> drop message */
    errorId = ETHTSYN_SWT_MGMT_E_MSG_BUFFER_OVERFLOW;
  }

  return errorId;
} /* EthTSyn_SwtMgmtRx_PerformBasicMsgChecksAngGetMsgBuffer() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtRx_HandleIngressTimestamp
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmtRx_HandleIngressTimestamp(
                  uint8                          EthIfCtrlIdx,
  ETHTSYN_P2CONST(uint8)                         DataPtr,
    ETHTSYN_P2VAR(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) comMsgHdrPtr = (ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType))&DataPtr[0]; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */
  const EthTSyn_IntTimeDomainIdxType timeDomainIdx = EthTSyn_Util_GetTimeDomainIdxFromId(comMsgHdrPtr->DomainNumber);

  /* ----- Implementation ----------------------------------------------- */
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
  /* #10 Switch Timestamping enabled. Mark timestamp states according to message type necessity. */
  switch(ETHTSYN_HDR_COM_MSG_TYPE(comMsgHdrPtr->TransSpecific_MessageType))
  {
  case ETHTSYN_MSG_TYPE_SYNC:
    {
      MsgBufferPtr->IngressTimestampMgmt.State =
          ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_WAITING_FOR_TIMESTAMP;                                            /* SBSW_ETHTSYN_VALID_API_POINTER */
      MsgBufferPtr->EgressTimestampHostPortMgmt.State =
          ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_WAITING_FOR_TIMESTAMP;                                            /* SBSW_ETHTSYN_VALID_API_POINTER */
      /* #100 Sync message. Get timestamp of Host Controller if required. */
      if(EthTSyn_SwtMgmt_GetEndStationSlavePortIdx(timeDomainIdx) < EthTSyn_GetSizeOfPort())
      {
        if(EthTSyn_SwtMgmt_GetIngressTimestamp(EthIfCtrlIdx, timeDomainIdx, DataPtr,
            &MsgBufferPtr->IngressTimestampHostCtrlMgmt.Timestamp) == E_OK)                                            /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
        {
          MsgBufferPtr->IngressTimestampHostCtrlMgmt.State =
              ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_AVAILABLE;                                                    /* SBSW_ETHTSYN_VALID_API_POINTER */
        }
        else
        {
          MsgBufferPtr->IngressTimestampHostCtrlMgmt.State =
              ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_NOT_AVAILABLE;                                                /* SBSW_ETHTSYN_VALID_API_POINTER */
        }
      }

      break;
    }

  case ETHTSYN_MSG_TYPE_FOLLOW_UP:
    {
      MsgBufferPtr->IngressTimestampMgmt.State =
          ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_WAITING_FOR_TIMESTAMP;                                            /* SBSW_ETHTSYN_VALID_API_POINTER */
      MsgBufferPtr->EgressTimestampHostPortMgmt.State =
          ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_WAITING_FOR_TIMESTAMP;                                            /* SBSW_ETHTSYN_VALID_API_POINTER */
      break;
    }

  case ETHTSYN_MSG_TYPE_PDELAY_RESP:
  case ETHTSYN_MSG_TYPE_PDELAY_REQ:
    {
      MsgBufferPtr->IngressTimestampMgmt.State =
          ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_WAITING_FOR_TIMESTAMP;                                            /* SBSW_ETHTSYN_VALID_API_POINTER */
      MsgBufferPtr->EgressTimestampHostPortMgmt.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_NOT_REQUIRED;                /* SBSW_ETHTSYN_VALID_API_POINTER */
      break;
    }

  default:
    {
      MsgBufferPtr->IngressTimestampMgmt.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_NOT_REQUIRED;                       /* SBSW_ETHTSYN_VALID_API_POINTER */
      MsgBufferPtr->EgressTimestampHostPortMgmt.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_NOT_REQUIRED;                /* SBSW_ETHTSYN_VALID_API_POINTER */
      break;
    }
  }
# else
  /* #20 No Switch Timestamping. Get the Ingress Timestamp (host controller) if necessary */
  switch(ETHTSYN_HDR_COM_MSG_TYPE(comMsgHdrPtr->TransSpecific_MessageType))
  {
  case ETHTSYN_MSG_TYPE_PDELAY_RESP:
  case ETHTSYN_MSG_TYPE_SYNC:
  case ETHTSYN_MSG_TYPE_PDELAY_REQ:
    {
      if(EthTSyn_SwtMgmt_GetIngressTimestamp(EthIfCtrlIdx, timeDomainIdx, DataPtr,
          &(MsgBufferPtr->IngressTimestampMgmt.Timestamp)) == E_OK)                                                    /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
      {
        /* Successfully retrieved the IngressTimestamp --> Store it */
        MsgBufferPtr->IngressTimestampMgmt.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_AVAILABLE;               /* SBSW_ETHTSYN_VALID_API_POINTER */
      }
      else
      {
        /* Failed to retrieve the IngressTimestamp */
        MsgBufferPtr->IngressTimestampMgmt.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_NOT_AVAILABLE;           /* SBSW_ETHTSYN_VALID_API_POINTER */
      }
      break;
    }

  default:
    {
      /* No Ingress Timestamp needed */
      MsgBufferPtr->IngressTimestampMgmt.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_NOT_REQUIRED_NOT_AVAILABLE;         /* SBSW_ETHTSYN_VALID_API_POINTER */
      break;
    }
  }
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

} /* EthTSyn_SwtMgmtRx_HandleIngressTimestamp() */


/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_ProvideMsgBuffer
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
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtMgmt_ProvideMsgBuffer(
  ETHTSYN_P2VAR(EthTSyn_SwtMgmt_MsgBufferType) *MsgBufferPtrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8_least index;

  /* ----- Implementation ----------------------------------------------- */
  *MsgBufferPtrPtr = NULL_PTR;                                                                                         /* SBSW_ETHTSYN_VALID_API_POINTER */

  ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #10 Iterate through all message buffers. */
  for(index = 0; index < ETHTSYN_SWT_MGMT_MSG_BUFFER_COUNT; index++)
  {
    /* #20 If message buffer is free. */
    if(EthTSyn_SwtMgmt_MsgBuffer[index].MsgBufferState == ETHTSYN_S_MSG_BUFFER_UNUSED)
    {
      /* #30 Lock the message buffer. */
      EthTSyn_SwtMgmt_MsgBuffer[index].MsgBufferState = ETHTSYN_S_MSG_BUFFER_MSG_INVALID;                              /* SBSW_ETHTSYN_MSG_BUFFER_IDX */

      /* #40 Provide the MsgBuffer Pointer. */
      *MsgBufferPtrPtr = &EthTSyn_SwtMgmt_MsgBuffer[index];                                                            /* SBSW_ETHTSYN_VALID_API_POINTER */
      retVal = E_OK;
      /* #50 And stop iteration. */
      break;
    }
  }
  ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return retVal;
} /* EthTSyn_SwtMgmt_ProvideMsgBuffer() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_GetMappedMsgBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtMgmt_GetMappedMsgBuffer(
                  EthTSyn_IntCtrlIdxType          CtrlIdx,
  ETHTSYN_P2CONST(uint8)                          RxBufAddr,
                  EthTSyn_FrameIdType             FrameId,
    ETHTSYN_P2VAR(EthTSyn_SwtMgmt_MsgBufferType) *MsgBufferPtrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8_least index;

  /* ----- Implementation ----------------------------------------------- */
  for(index = 0; index < ETHTSYN_SWT_MGMT_MSG_BUFFER_COUNT; index++)
  {
    if( (EthTSyn_SwtMgmt_MsgBuffer[index].MsgBufferState == ETHTSYN_S_MSG_BUFFER_MSG_VALID) ||
        (EthTSyn_SwtMgmt_MsgBuffer[index].MsgBufferState == ETHTSYN_S_MSG_BUFFER_PORT_INFO_AVAILABLE) )
    {
      if( (EthTSyn_SwtMgmt_MsgBuffer[index].CtrlIdx == CtrlIdx) &&
          (EthTSyn_SwtMgmt_MsgBuffer[index].RxBufAddr == RxBufAddr) &&
          (EthTSyn_SwtMgmt_MsgBuffer[index].SwtMgmtInfo.FrameId == FrameId) )
      {
        retVal = E_OK;
        *MsgBufferPtrPtr = &EthTSyn_SwtMgmt_MsgBuffer[index];                                                          /* SBSW_ETHTSYN_VALID_API_POINTER */
        break;
      }
    }
  }

  return retVal;
} /* EthTSyn_SwtMgmt_GetMappedMsgBuffer() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_GetEndStationSlavePortIdx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntPortIdxType, ETHTSYN_CODE) EthTSyn_SwtMgmt_GetEndStationSlavePortIdx(
  EthTSyn_IntTimeDomainIdxType TimeDomainIdx)
{
/* ----- Local Variables ---------------------------------------------- */
  EthTSyn_IntPortIdxType slavePortIdx = EthTSyn_GetSizeOfPort();
  EthTSyn_SlavePortIterType slavePortIter;

  /* ----- Implementation ----------------------------------------------- */
  for(slavePortIter = EthTSyn_GetSlavePortStartIdxOfTimeDomain(TimeDomainIdx);
      slavePortIter < EthTSyn_GetSlavePortEndIdxOfTimeDomain(TimeDomainIdx);
      slavePortIter++)
  {
    const EthTSyn_IntPortIdxType tempSlavePortIdx =
      (EthTSyn_IntPortIdxType)EthTSyn_GetPortIdxOfSlavePort(slavePortIter);
    if(EthTSyn_Util_IsEndStationPort(tempSlavePortIdx) == TRUE)
    {
      slavePortIdx = (EthTSyn_IntPortIdxType)tempSlavePortIdx;
      break;
    }
  }

  return slavePortIdx;
} /* EthTSyn_SwtMgmt_GetEndStationSlavePortIdx() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_GetPortIdxOfSwitchSlavePort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntSlavePortIdxType, ETHTSYN_CODE) EthTSyn_SwtMgmt_GetSwitchSlavePortIdx(
  EthTSyn_TimeDomainIterType TimeDomainIdx)
{
/* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SlavePortIterType slavePortIter;
  EthTSyn_IntSlavePortIdxType slavePortIdx = EthTSyn_GetSizeOfSlavePort();

  /* ----- Implementation ----------------------------------------------- */
  for(slavePortIter = EthTSyn_GetSlavePortStartIdxOfTimeDomain(TimeDomainIdx);
      slavePortIter < EthTSyn_GetSlavePortEndIdxOfTimeDomain(TimeDomainIdx);
      slavePortIter++)
  {
    const EthTSyn_IntPortIdxType tempPortIdx = (EthTSyn_IntPortIdxType)EthTSyn_GetPortIdxOfSlavePort(slavePortIter);
    if(EthTSyn_Util_IsSwitchPort(tempPortIdx) == TRUE)
    {
      slavePortIdx = (EthTSyn_IntSlavePortIdxType)slavePortIter;
      break;
    }
  }

  return slavePortIdx;
} /* EthTSyn_SwtMgmt_GetPortIdxOfSwitchSlavePort() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_GetIngressTimestamp
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
/* PRQA S 3673 2 */ /* MD_EthTSyn_3673_Ar */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtMgmt_GetIngressTimestamp(
                  uint8                        EthIfCtrlIdx,
                  EthTSyn_IntTimeDomainIdxType TimeDomainIdx,
  ETHTSYN_P2CONST(uint8)                       DataPtr,
    ETHTSYN_P2VAR(EthTSyn_GlobalTimestampType) IngressTimestampPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  EthTSyn_GlobalTimestampType ingressTimestamp;
# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  Eth_TimestampQualityType timestampQual = ETH_INVALID;
# else
  const StbM_SynchronizedTimeBaseType timeBaseId = EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(TimeDomainIdx);
# endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 When HW-Timestamping is used, get the ingress timestamp from HW. Else get the current raw time from StbM. */
# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  ETHTSYN_DUMMY_STATEMENT(TimeDomainIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  /* HW-Timestamping */ /* PRQA S 0310, 0311 2 */ /* MD_EthTSyn_0310_MsgStructRev, MD_EthTSyn_0311 */
  if(EthIf_GetIngressTimestamp(EthIfCtrlIdx, (ETHTSYN_P2VAR(Eth_DataType))DataPtr, &ingressTimestamp,
      &timestampQual) == E_OK)                                                                                         /* SBSW_ETHTSYN_PASSING_API_POINTER */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
  {
    if(timestampQual == ETH_VALID)
    {
      *IngressTimestampPtr = ingressTimestamp;                                                                         /* SBSW_ETHTSYN_VALID_API_POINTER */
      retVal = E_OK;
    }
  }
# else
  /* SW-Timestamping */
  ETHTSYN_DUMMY_STATEMENT(EthIfCtrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETHTSYN_DUMMY_STATEMENT(DataPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  if(StbM_GetCurrentTimeRaw(timeBaseId, &ingressTimestamp.nanoseconds) == E_OK)                                        /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
  {
    IngressTimestampPtr->secondsHi = 0;                                                                                /* SBSW_ETHTSYN_VALID_API_POINTER */
    IngressTimestampPtr->seconds = 0;                                                                                  /* SBSW_ETHTSYN_VALID_API_POINTER */
    IngressTimestampPtr->nanoseconds = ingressTimestamp.nanoseconds;                                                   /* SBSW_ETHTSYN_VALID_API_POINTER */
    retVal = E_OK;
  }
# endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */


  return retVal;
} /* EthTSyn_SwtMgmt_GetIngressTimestamping() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_GetMappedStateMachine
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SmIdentEnumType, ETHTSYN_CODE) EthTSyn_SwtMgmt_GetMappedStateMachine(
                  EthTSyn_IntCtrlIdxType  CtrlIdx,
  ETHTSYN_P2CONST(uint8)                  TxBufPtr,
                  EthTSyn_FrameIdType     FrameId,
    ETHTSYN_P2VAR(EthTSyn_IntPortIdxType) PortIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SmIdentEnumType stateMachine = ETHTSYN_SM_IDENT_INVALID;
  EthTSyn_PortIndIterType portIndIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #20 Iterate through all relevant state machines (i.e. SyncSend, Pdelay_Req, Pdelay_Resp). */
  for(portIndIter = EthTSyn_GetPortIndStartIdxOfCtrl(CtrlIdx);
      portIndIter < EthTSyn_GetPortIndEndIdxOfCtrl(CtrlIdx);
      portIndIter++)
  {
    const EthTSyn_IntPortIdxType portIdx = EthTSyn_GetPortInd(portIndIter);

    if(EthTSyn_IsMasterPortUsedOfPort(portIdx) == TRUE)
    {
      const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(portIdx);
      ETHTSYN_CONSTP2VAR(EthTSyn_SyncSendSmType) syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);

      if((syncSendSmPtr->SyncTxBuf.Address == TxBufPtr) && (syncSendSmPtr->FrameId == FrameId))
      {
        /* SyncSend state machine */
        stateMachine = ETHTSYN_SM_IDENT_SYNC_SEND;
      }
    }
#  if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
    if(EthTSyn_Util_IsPdelayInitiator(portIdx) == TRUE)
    {
      const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(portIdx);
      const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
        EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
      const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
        EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
      ETHTSYN_CONSTP2CONST(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);

      if((pDelayReqSmPtr->TxBuf.Address == TxBufPtr) && (pDelayReqSmPtr->FrameId == FrameId))
      {
        /* Pdelay request state machine */
        stateMachine = ETHTSYN_SM_IDENT_PDELAY_REQ;
      }
    }
#  endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */
#  if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
    if(EthTSyn_Util_IsPdelayResponder(portIdx) == TRUE)
    {
      const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(portIdx);
      const EthTSyn_PdelayResponderIdxOfPdelayConfigType pDelayResponderIdx =
        EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pDelayCfgIdx);
      const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pDelayRespSmIdx =
        EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pDelayResponderIdx);
      ETHTSYN_CONSTP2CONST(EthTSyn_PdelayRespSmType) pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);

      if((pDelayRespSmPtr->TxBuf.Address == TxBufPtr) && (pDelayRespSmPtr->FrameId == FrameId))
      {
        /* Pdelay request state machine */
        stateMachine = ETHTSYN_SM_IDENT_PDELAY_RESP;
      }
    }
#  endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

    if(stateMachine != ETHTSYN_SM_IDENT_INVALID)
    {
      /* #30 State Machine found --> stop iteration and get PortIdx. */
      *PortIdxPtr = portIdx;                                                                                           /* SBSW_ETHTSYN_VALID_API_POINTER */
      break;
    }
  }

  return stateMachine;
} /* EthTSyn_SwtMgmt_GetMappedStateMachine */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_GetStateMachineTxTimestampInfo
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
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtMgmt_GetStateMachineTxTimestampInfo(
                EthTSyn_SmIdentEnumType       StateMachine,
                EthTSyn_IntPortIdxType        PortIdx,
                EthTSyn_TimestampDirEnumType  TimestampDir,
  ETHTSYN_P2VAR(EthTSyn_GlobalTimestampType) *TimestampPtrPtr,
  ETHTSYN_P2VAR(EthTSyn_TimestampStateType)  *TimestampStatePtrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check state machine. */
  switch(StateMachine)
  {
  case ETHTSYN_SM_IDENT_SYNC_SEND:
    {
      const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
      ETHTSYN_CONSTP2VAR(EthTSyn_SyncSendSmType) syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);

      /* #100 Sync send state machine -> check timestamp direction. */
      if(TimestampDir == ETHTSYN_TS_DIR_INGRESS)
      {
        /* #1000 Ingress timestamp -> get sync ingress timestamp host port information. */
        *TimestampPtrPtr = &syncSendSmPtr->SyncIngressTimestampMgmtHostPort.Timestamp;                                 /* SBSW_ETHTSYN_VALID_API_POINTER */
        *TimestampStatePtrPtr = &syncSendSmPtr->SyncIngressTimestampMgmtHostPort.State;                                /* SBSW_ETHTSYN_VALID_API_POINTER */
        if(EthTSyn_IsTimestampReadyToProcess(syncSendSmPtr->SyncEgressTimestampMgmtSwitchPort.State) == TRUE)          /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */
        {
          syncSendSmPtr->SyncTxBuf.Address = NULL_PTR;                                                                 /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
        }
        retVal = E_OK;
      }
      if(TimestampDir == ETHTSYN_TS_DIR_EGRESS)
      {
        /* #1001 Egress timestamp -> get sync egress timestamp switch port information. */
        *TimestampPtrPtr = &syncSendSmPtr->SyncEgressTimestampMgmtSwitchPort.Timestamp;                                /* SBSW_ETHTSYN_VALID_API_POINTER */
        *TimestampStatePtrPtr = &syncSendSmPtr->SyncEgressTimestampMgmtSwitchPort.State;                               /* SBSW_ETHTSYN_VALID_API_POINTER */
        if(EthTSyn_IsTimestampReadyToProcess(syncSendSmPtr->SyncIngressTimestampMgmtHostPort.State) == TRUE)           /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */
        {
          syncSendSmPtr->SyncTxBuf.Address = NULL_PTR;                                                                 /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
        }
        retVal = E_OK;
      }

      break;
    }

#  if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
  case ETHTSYN_SM_IDENT_PDELAY_REQ:
    {
      /* #101 Pdelay request state machine -> check timestamp direction. */
      if(TimestampDir == ETHTSYN_TS_DIR_EGRESS)
      {
        const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
        const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
          EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
        const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
          EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
        ETHTSYN_CONSTP2VAR(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);
        /* #1010 Egress timestamp -> get Pdelay request egress timestamp information. */
        *TimestampPtrPtr = &pDelayReqSmPtr->PdelayReq.EgressTimestampMgmt.Timestamp;                                   /* SBSW_ETHTSYN_VALID_API_POINTER */
        *TimestampStatePtrPtr = &pDelayReqSmPtr->PdelayReq.EgressTimestampMgmt.State;                                  /* SBSW_ETHTSYN_VALID_API_POINTER */
        pDelayReqSmPtr->TxBuf.Address = NULL_PTR;                                                                      /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
        retVal = E_OK;
      }
      break;
    }
#  endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

#  if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
  case ETHTSYN_SM_IDENT_PDELAY_RESP:
    {
      /* #102 Pdelay response state machine -> check timestamp direction. */
      if(TimestampDir == ETHTSYN_TS_DIR_EGRESS)
      {
        const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
        const EthTSyn_PdelayResponderIdxOfPdelayConfigType pDelayResponderIdx =
          EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pDelayCfgIdx);
        const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pDelayRespSmIdx =
          EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pDelayResponderIdx);
        ETHTSYN_CONSTP2VAR(EthTSyn_PdelayRespSmType) pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);

        /* #1020 Egress timestamp -> get Pdelay response egress timestamp information. */
        *TimestampPtrPtr = &pDelayRespSmPtr->PdelayResp.EgressTimestampMgmt.Timestamp;                                 /* SBSW_ETHTSYN_VALID_API_POINTER */
        *TimestampStatePtrPtr = &pDelayRespSmPtr->PdelayResp.EgressTimestampMgmt.State;                                /* SBSW_ETHTSYN_VALID_API_POINTER */
        pDelayRespSmPtr->TxBuf.Address = NULL_PTR;                                                                     /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
        retVal = E_OK;
      }
      break;
    }
#  endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

  default:
    {
      /* Nothing to do here. */
      break;
    }
  }


  return retVal;
} /* EthTSyn_SwtMgmt_GetStateMachineTimestampInfo() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
# endif /* ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtTx_TxSyncMsg
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmtTx_TxSyncMsg(
  EthTSyn_MasterPortIterType MasterPortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_PortIdxOfMasterPortType portIdx = EthTSyn_GetPortIdxOfMasterPort(MasterPortIdx);
  const EthTSyn_CtrlIdxOfPortType ctrlIdx = EthTSyn_GetCtrlIdxOfPort(portIdx);
  const EthTSyn_EthIfCtrlIdxOfCtrlType ethIfCtrlIdx = EthTSyn_GetEthIfCtrlIdxOfCtrl(ctrlIdx);
  EthTSyn_EthTxBufferStructType txBuffer;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get Ethernet transmission buffer. */
  txBuffer.Length = ETHTSYN_MSG_SYNC_LENGTH;
  if(EthTSyn_UtilTx_ProvideTxBuffer(ethIfCtrlIdx, EthTSyn_GetFramePrioOfPort(portIdx), &txBuffer) == E_OK)             /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
  {
    Std_ReturnType tmpRetVal;
    EthTSyn_SwtMgmtInfoType mgmtInfo;
    EthTSyn_SyncSendSmPtrType syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(MasterPortIdx);
    /* #20 Copy the sync message to TxBuffer. */
    EthTSyn_SwtMgmtTx_CopySyncMsgFromSiteSyncSyncSmToTxBuffer(portIdx, txBuffer.BufferPtr);                            /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */

    /* #30 Get and set required information for later processing (transmission and TxConfirmation) */
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
    syncSendSmPtr->SyncEgressTimestampMgmtSwitchPort.State =
      ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_WAITING_FOR_TIMESTAMP;                                                /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
    syncSendSmPtr->SyncIngressTimestampMgmtHostPort.State =
      ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_WAITING_FOR_TIMESTAMP;                                                /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
# else
    syncSendSmPtr->FollowUpPreciseOriginTimestampMgmt.State =
      ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_WAITING_FOR_TIMESTAMP;                                                /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

    /* Get Switch management Info. */
    if(EthTSyn_IsSwitchPortMgmtUsedOfPort(portIdx) == TRUE)
    {
      const EthTSyn_SwitchPortMgmtIdxOfPortType swtPortMgmtIdx = EthTSyn_GetSwitchPortMgmtIdxOfPort(portIdx);
      mgmtInfo.SwitchIdx = EthTSyn_GetSwitchIdxOfSwitchPortMgmt(swtPortMgmtIdx);
      mgmtInfo.PortIdx = EthTSyn_GetPortIdxOfSwitchPortMgmt(swtPortMgmtIdx);
    }
    else
    {
      mgmtInfo.SwitchIdx = ETHTSYN_INVALID_ETHIF_SWITCH_IDX;
      mgmtInfo.PortIdx = ETHTSYN_INVALID_SWITCH_PORT_IDX;
    }

    syncSendSmPtr->SyncTxBuf.Index = txBuffer.BufferIdx;                                                               /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
    syncSendSmPtr->SyncTxBuf.Address = txBuffer.BufferPtr;                                                             /* SBSW_ETHTSYN_API_ARGUMENT_IDX */

    /* Save Frame Id */
    mgmtInfo.FrameId = txBuffer.FrameId;
    syncSendSmPtr->FrameId = mgmtInfo.FrameId;                                                                         /* SBSW_ETHTSYN_API_ARGUMENT_IDX */

    /* #40 Prepare message transmission (i.e. enable egress timestamping). */
    tmpRetVal = EthTSyn_UtilTx_PrepareTransmission(ethIfCtrlIdx, txBuffer.BufferIdx, ETHTSYN_ENABLE_TS_HW_XOR_SWT_TS,
      &mgmtInfo);                                                                                                      /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
    if(tmpRetVal == E_OK)
    {
      /* #50 Successfully prepared transmission. Trigger transmission. */
      tmpRetVal = EthTSyn_UtilTx_Transmit(ethIfCtrlIdx, txBuffer.BufferIdx, ETHTSYN_MSG_SYNC_LENGTH);
    }

    /* #60 If transmission failed, reset buffer values and release Ethernet transmission buffer. */
    if(tmpRetVal != E_OK)
    {
      const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(portIdx);
      EthTSyn_SiteSyncSyncSmPtrType siteSyncSyncSmPtr = EthTSyn_GetAddrSiteSyncSyncSm(timeDomainIdx);
      /* EthTSyn_SiteSyncSyncSm(TimeDomainIdx).TxConfirmationPending is set to the amount of configured
       * MasterPorts for the TimeDomain at the reception of a Sync message. Since this code part can only
       * be reached after the reception of a Sync message no underflow is possible */
      (siteSyncSyncSmPtr->TxConfirmationPending)--;                                                                    /* SBSW_ETHTSYN_CSL02_03 */
      /* Transmission failed */
      syncSendSmPtr->SyncTxBuf.Index = ETHTSYN_INV_BUF_IDX;                                                            /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
      syncSendSmPtr->SyncTxBuf.Address = NULL_PTR;                                                                     /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
      syncSendSmPtr->FrameId = ETHTSYN_INVALID_FRAME_ID;                                                               /* SBSW_ETHTSYN_API_ARGUMENT_IDX */

      EthTSyn_UtilTx_ReleaseTxBuffer(ethIfCtrlIdx, txBuffer.BufferIdx);
    }
  }

} /* EthTSyn_SwtMgmtTx_TxSyncMsg() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtTX_CopySyncMsgFromSiteSyncSyncSmToTxBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmtTx_CopySyncMsgFromSiteSyncSyncSmToTxBuffer(
                EthTSyn_PortIdxOfMasterPortType PortIdx,
  ETHTSYN_P2VAR(uint8)                          BufferPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_P2VAR(EthTSyn_SyncMsgType) syncMsgPtr;
  ETHTSYN_P2VAR(EthTSyn_CommonMsgHdrType) comHdrPtr;
  const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
  ETHTSYN_CONSTP2CONST(EthTSyn_SiteSyncSyncSmType) siteSyncSyncSmPtr = EthTSyn_GetAddrSiteSyncSyncSm(timeDomainIdx);

  /* ----- Implementation ----------------------------------------------- */
  comHdrPtr = (ETHTSYN_P2VAR(EthTSyn_CommonMsgHdrType))BufferPtr; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */
  syncMsgPtr = (ETHTSYN_P2VAR(EthTSyn_SyncMsgType))&BufferPtr[ETHTSYN_HDR_COM_LENGTH]; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */

  /* #10 Copy common Hdr to TxBuffer. */
  /* PRQA S 0310 3 */ /* MD_EthTSyn_0310_IpBase */
  IpBase_Copy((ETHTSYN_P2VAR(IpBase_CopyDataType))comHdrPtr,                                                           /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */
      (ETHTSYN_P2CONST(IpBase_CopyDataType))&(siteSyncSyncSmPtr->Msg.MsgHdr), ETHTSYN_HDR_COM_LENGTH);

  /* #20 Manipulate SourcePortIdentity fields within the common Hdr if required. */
  if(EthTSyn_IsSwtMgmtKeepSrcPortIdentityOfTimeDomain(timeDomainIdx) == FALSE)
  {
    /* Use 'Own' source port identity */
    const uint16 portNumber = (uint16)EthTSyn_GetNumberOfPort(PortIdx);
    const EthTSyn_CtrlIdxOfPortType ctrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);
    ETHTSYN_CONSTP2CONST(EthTSyn_CtrlStateType) ctrlStatePtr = EthTSyn_GetAddrCtrlState(ctrlIdx);

    EthTSyn_SetClockIdentity(comHdrPtr->SourceClockIdentity, ctrlStatePtr->ClockIdentity);                             /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */

    comHdrPtr->SourcePortNumber = (uint16)EthTSyn_Htons(portNumber);                                                   /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
  }

  /* #30 Copy Sync message values to TxBuffer. */
  /* PRQA S 0310 3 */ /* MD_EthTSyn_0310_IpBase */
  IpBase_Copy((ETHTSYN_P2VAR(IpBase_CopyDataType))syncMsgPtr,                                                          /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */
      (ETHTSYN_P2CONST(IpBase_CopyDataType))(siteSyncSyncSmPtr->Msg.Payload), ETHTSYN_MSG_SYNC_PAYLOAD_LENGTH);

} /* EthTSyn_SwtMgmtTX_CopySyncMsgFromSiteSyncSyncSmToTxBuffer() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtTx_TxFollowUpMsg
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
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmtTx_TxFollowUpMsg(
  EthTSyn_MasterPortIterType MasterPortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_PortIdxOfMasterPortType portIdx = EthTSyn_GetPortIdxOfMasterPort(MasterPortIdx);
  EthTSyn_SyncSendSmPtrType syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(MasterPortIdx);
  ETHTSYN_P2CONST(EthTSyn_TimestampStateType) syncEgressTimestampStatePtr;

  /* ----- Implementation ----------------------------------------------- */
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
  syncEgressTimestampStatePtr = &syncSendSmPtr->SyncEgressTimestampMgmtSwitchPort.State;
# else
  syncEgressTimestampStatePtr = &syncSendSmPtr->FollowUpPreciseOriginTimestampMgmt.State;
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

  /* #10 Check if Sync egress timestamp is ready for procession. */
  if(EthTSyn_IsTimestampReadyToProcess(*syncEgressTimestampStatePtr) == TRUE)
  {
    const EthTSyn_CtrlIdxOfPortType ctrlIdx = EthTSyn_GetCtrlIdxOfPort(portIdx);
    const EthTSyn_EthIfCtrlIdxOfCtrlType ethIfCtrlIdx = EthTSyn_GetEthIfCtrlIdxOfCtrl(ctrlIdx);
    const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(portIdx);
    EthTSyn_SiteSyncSyncSmPtrType siteSyncSyncSmPtr = EthTSyn_GetAddrSiteSyncSyncSm(timeDomainIdx);
    EthTSyn_EthTxBufferStructType txBuffer;

    /* #20 Get Ethernet transmission buffer. */
    txBuffer.Length = (uint16)EthTSyn_Ntohs(siteSyncSyncSmPtr->Msg.MsgHdr.MessageLength);

    if(EthTSyn_UtilTx_ProvideTxBuffer(ethIfCtrlIdx, EthTSyn_GetFramePrioOfPort(portIdx), &txBuffer) == E_OK)           /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
    {
      Std_ReturnType tmpRetVal;
      EthTSyn_SwtMgmtInfoType mgmtInfo;

      /* #30 Copy FollowUp message to TxBuffer. */
      EthTSyn_SwtMgmtTx_CopyFollowUpMsgFromSiteSyncSyncSmToTxBuffer(portIdx, txBuffer.BufferPtr);                      /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */

      /* #40 Store information required for later processing in transmit and TxConfirmation. */
      syncSendSmPtr->FollowUpTxBuf.Index = txBuffer.BufferIdx;                                                         /* SBSW_ETHTSYN_CSL02 */
      syncSendSmPtr->FollowUpTxBuf.Address = txBuffer.BufferPtr;                                                       /* SBSW_ETHTSYN_CSL02 */
      mgmtInfo.FrameId = txBuffer.FrameId;
      syncSendSmPtr->FrameId = mgmtInfo.FrameId;                                                                       /* SBSW_ETHTSYN_CSL02 */
      /* Set Switch management Info */
      if(EthTSyn_IsSwitchPortMgmtUsedOfPort(portIdx) == TRUE)
      {
        const EthTSyn_SwitchPortMgmtIdxOfPortType swtPortMgmtIdx = EthTSyn_GetSwitchPortMgmtIdxOfPort(portIdx);
        mgmtInfo.SwitchIdx = EthTSyn_GetSwitchIdxOfSwitchPortMgmt(swtPortMgmtIdx);
        mgmtInfo.PortIdx = EthTSyn_GetPortIdxOfSwitchPortMgmt(swtPortMgmtIdx);
      }
      else
      {
        mgmtInfo.SwitchIdx = ETHTSYN_INVALID_ETHIF_SWITCH_IDX;
        mgmtInfo.PortIdx = ETHTSYN_INVALID_SWITCH_PORT_IDX;
      }

      /* #50 Prepare message transmission (i.e. enable egress timestamping). */
      tmpRetVal = EthTSyn_UtilTx_PrepareTransmission(ethIfCtrlIdx, txBuffer.BufferIdx, ETHTSYN_ENABLE_TS_HW_XOR_SWT_TS,
        &mgmtInfo);                                                                                                    /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
      if(tmpRetVal == E_OK)
      {
        /* #70 Successfully prepared transmission. Trigger transmission. */
        tmpRetVal = EthTSyn_UtilTx_Transmit(ethIfCtrlIdx, txBuffer.BufferIdx, txBuffer.Length);
      }

      /* #80 If transmission failed, reset buffer values and release Ethernet transmission buffer. */
      if(tmpRetVal != E_OK)
      {
        /* EthTSyn_SiteSyncSyncSm(TimeDomainIdx).TxConfirmationPending is set to the amount of configured
         * MasterPorts for the TimeDomain at the reception of a FollowUp message. Since this code part can only
         * be reached after the reception of a FollowUp message no underflow is possible */
        (siteSyncSyncSmPtr->TxConfirmationPending)--;                                                                  /* SBSW_ETHTSYN_CSL02_03 */
        syncSendSmPtr->FollowUpTxBuf.Index = ETHTSYN_INV_BUF_IDX;                                                      /* SBSW_ETHTSYN_CSL02 */
        syncSendSmPtr->FollowUpTxBuf.Address = NULL_PTR;                                                               /* SBSW_ETHTSYN_CSL02 */
        syncSendSmPtr->FrameId = ETHTSYN_INVALID_FRAME_ID;                                                             /* SBSW_ETHTSYN_CSL02 */

        EthTSyn_UtilTx_ReleaseTxBuffer(ethIfCtrlIdx, txBuffer.BufferIdx);
      }
    }
  }
} /* EthTSyn_SwtMgmtTx_TxFollowUpMsg() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtTX_CopyFollowUpMsgFromSiteSyncSyncSmToTxBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmtTx_CopyFollowUpMsgFromSiteSyncSyncSmToTxBuffer(
                EthTSyn_PortIdxOfMasterPortType PortIdx,
  ETHTSYN_P2VAR(uint8)                          BufferPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
  uint16 txLen;
  ETHTSYN_CONSTP2VAR(EthTSyn_CommonMsgHdrType) comHdrPtr = (ETHTSYN_P2VAR(EthTSyn_CommonMsgHdrType))BufferPtr; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */
  ETHTSYN_CONSTP2VAR(EthTSyn_FollowUpMsgType) followUpMsgPtr =
    (ETHTSYN_P2VAR(EthTSyn_FollowUpMsgType))&BufferPtr[ETHTSYN_HDR_COM_LENGTH]; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */
  ETHTSYN_CONSTP2VAR(EthTSyn_SiteSyncSyncSmType) siteSyncSyncSmPtr = EthTSyn_GetAddrSiteSyncSyncSm(timeDomainIdx);

  /* ----- Implementation ----------------------------------------------- */
  txLen = (uint16)EthTSyn_Ntohs((siteSyncSyncSmPtr->Msg.MsgHdr.MessageLength));

  /* #10 Copy Common Hdr to TxBuffer. */
  /* PRQA S 0310 3 */ /* MD_EthTSyn_0310_IpBase */
  IpBase_Copy((ETHTSYN_P2VAR(IpBase_CopyDataType))comHdrPtr,                                                           /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */
      (ETHTSYN_P2CONST(IpBase_CopyDataType))&(siteSyncSyncSmPtr->Msg.MsgHdr), ETHTSYN_HDR_COM_LENGTH);

  /* #20 Copy FollwUp to TxBuffer. */
  /* PRQA S 0310 3 */ /* MD_EthTSyn_0310_IpBase */
  IpBase_Copy((ETHTSYN_P2VAR(IpBase_CopyDataType))followUpMsgPtr,                                                      /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */
      (ETHTSYN_P2CONST(IpBase_CopyDataType))(siteSyncSyncSmPtr->Msg.Payload), (txLen - ETHTSYN_HDR_COM_LENGTH));

  /* #30 Manipulate the SourcePortIdentity if required. */
  if(EthTSyn_IsSwtMgmtKeepSrcPortIdentityOfTimeDomain(timeDomainIdx) == FALSE)
  {
    /* Use 'Own' source port identity */
    const uint16 portNumber = (uint16)EthTSyn_GetNumberOfPort(PortIdx);
    const EthTSyn_CtrlIdxOfPortType ctrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);
    ETHTSYN_CONSTP2CONST(EthTSyn_CtrlStateType) ctrlStatePtr = EthTSyn_GetAddrCtrlState(ctrlIdx);

    EthTSyn_SetClockIdentity(comHdrPtr->SourceClockIdentity, ctrlStatePtr->ClockIdentity);                             /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */

    comHdrPtr->SourcePortNumber = (uint16)EthTSyn_Htons(portNumber);                                                   /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
  }
  /* #50 Compute and set the FollowUp correction field. */
  EthTSyn_SwtMgmtTx_ComputeAndSetFollowUpCorrectionField(PortIdx, comHdrPtr);                                          /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */

} /* EthTSyn_SwtMgmtTX_CopyFollowUpMsgFromSiteSyncSyncSmToTxBuffer() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtTx_ComputeAndSetFollowUpCorrectionField
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmtTx_ComputeAndSetFollowUpCorrectionField(
                EthTSyn_PortIdxOfMasterPortType PortIdx,
  ETHTSYN_P2VAR(EthTSyn_CommonMsgHdrType)       ComMsgPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
  ETHTSYN_P2CONST(EthTSyn_TimestampStateType) syncEgressTimestampStatePtr;
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */
  ETHTSYN_P2VAR(EthTSyn_GlobalTimestampType)  syncEgressTimestampPtr;
  EthTSyn_TimediffType followUpCorrectionFieldNs = 0;
  const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
  const EthTSyn_IntSlavePortIdxType swtSlavePortIdx = EthTSyn_SwtMgmt_GetSwitchSlavePortIdx(timeDomainIdx);
  const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
  ETHTSYN_CONSTP2VAR(EthTSyn_SyncSendSmType) syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);

  /* ----- Implementation ----------------------------------------------- */
  if(swtSlavePortIdx < EthTSyn_GetSizeOfSlavePort())
  {
    ETHTSYN_CONSTP2VAR(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(swtSlavePortIdx);
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
    syncEgressTimestampStatePtr = &syncSendSmPtr->SyncEgressTimestampMgmtSwitchPort.State;
    syncEgressTimestampPtr      = &syncSendSmPtr->SyncEgressTimestampMgmtSwitchPort.Timestamp;
# else
    syncEgressTimestampPtr      = &syncSendSmPtr->FollowUpPreciseOriginTimestampMgmt.Timestamp;
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
    /* #10 Switch timestamping. Check if sync egress timestamp is available. */
    if(EthTSyn_Util_IsTimestampAvailable(*syncEgressTimestampStatePtr) == TRUE)
    {
      /* #100 Sync egress timestamp available. Compute switch residence time of the sync message. */
      if(EthTSyn_Util_TimestampMinusTimestamp(syncEgressTimestampPtr,
          &syncReceiveSmPtr->Sync.IngressTimestampMgmt.Timestamp,
          &followUpCorrectionFieldNs) != E_OK)                                                                         /* SBSW_ETHTSYN_POINTER_VARIABLE */ /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
      {
        /* #1000 Failed to compute switch residence time. Use default value. */
        followUpCorrectionFieldNs = (EthTSyn_TimediffType)
                        (ETHTSYN_SWT_RX_TO_UPLINK_RESIDENCE_TIME_NS + ETHTSYN_SWT_UPLINK_TO_TX_RESIDENCE_TIME_NS);
      }
    }
    else
    {
      /* #101 Sync egress timestamp not available. Use default value for residence time. */
      followUpCorrectionFieldNs = (EthTSyn_TimediffType)
                      (ETHTSYN_SWT_RX_TO_UPLINK_RESIDENCE_TIME_NS + ETHTSYN_SWT_UPLINK_TO_TX_RESIDENCE_TIME_NS);
    }
# else
    /* #20 No Switch timestamping. Compute SW residence time of the sync message. */
    if(EthTSyn_Util_TimestampMinusTimestamp(syncEgressTimestampPtr,
        &syncReceiveSmPtr->Sync.IngressTimestampMgmt.Timestamp,
        &followUpCorrectionFieldNs) == E_OK)                                                                           /* SBSW_ETHTSYN_POINTER_VARIABLE */ /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */
    {
      if(followUpCorrectionFieldNs >= 0)
      {
        uint64 unsignedFupCorrectionField = (uint64)followUpCorrectionFieldNs;
        const EthTSyn_PortIdxOfSlavePortType portIdxOfSwtSlavePort = EthTSyn_GetPortIdxOfSlavePort(swtSlavePortIdx);
        /* Add the Path Delay 'of the Slave Port' to the Residence Time */
        /*
                      +----------+      Sync         +--------------------+ Sync
                      |  Master  +------------------>+S||    Bridge    ||M+--------->
                      +----------+t1               t2+--------------------+t3

                                 +  Pdelay (t2-t1)   + Residence (t3-t2)  +
                                 +<----------------->-<------------------>+
                                 +                   +                    +
         */
        /* #30 Add Pdelay to the correction field. */
        unsignedFupCorrectionField += EthTSyn_Pdelay_GetCurrentPdelay((EthTSyn_IntPortIdxType)portIdxOfSwtSlavePort);

        /* #40 Add the former FollowUpCorrectionValue */
        unsignedFupCorrectionField += ETHTSYN_GET_FOLLOW_UP_CORRECTION_VALUE_NS_FROM_MSG(ComMsgPtr->CorrectionField);

        /* #50 Set the computed value of the correction field. */
        /* Multiply FollwUpCorrectionField by 2^16 (as specified by IEEE802.1AS and copy it to the TxBuffer */
        EthTSyn_CopyFollowUpCorrectionField(unsignedFupCorrectionField, ComMsgPtr->CorrectionField);                   /* SBSW_ETHTSYN_VALID_API_POINTER */

      }
    }
  }
} /* EthTSyn_SwtMgmtTx_ComputeAndSetFollowUpCorrectionField() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_HandleSendSyncStateOfSiteSyncSyncSm
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_HandleSendSyncStateOfSiteSyncSyncSm(
  EthTSyn_TimeDomainIterType TimeDomainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_MasterPortIterType masterPortIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all master Ports. */
  for(masterPortIter = EthTSyn_GetMasterPortStartIdxOfTimeDomain(TimeDomainIdx);
      masterPortIter < EthTSyn_GetMasterPortEndIdxOfTimeDomain(TimeDomainIdx);
      masterPortIter++)
  {
    EthTSyn_SyncSendSmPtrType syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIter);

    /* #20 Check if Sync send state machine of the master port is in a state where the sync message should be send. */
    if( (syncSendSmPtr->State == ETHTSYN_S_SYNC_SEND_SM_SSS_PENDING) ||
        (syncSendSmPtr->State == ETHTSYN_S_SYNC_SEND_SM_SSS_TX_FUP) ||
        (syncSendSmPtr->State == ETHTSYN_S_SYNC_SEND_SM_SSS_TX_SYNC) )
    {
      /* #30 Trigger transmission of the Sync message. */
      syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_SSS_TX_SYNC;                                                       /* SBSW_ETHTSYN_CSL02 */
      EthTSyn_SwtMgmtTx_TxSyncMsg(masterPortIter);
    }
  } /* END: Iteration of master ports */
} /* EthTSyn_SwtMgmt_HandleSendSyncStateOfSiteSyncSyncSm() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_HandleSendFollowUpStateOfSiteSyncSyncSm
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_HandleSendFollowUpStateOfSiteSyncSyncSm(
  EthTSyn_TimeDomainIterType TimeDomainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_IntSlavePortIdxType swtSlavePortIdx = EthTSyn_SwtMgmt_GetSwitchSlavePortIdx(TimeDomainIdx);

  /* ----- Implementation ----------------------------------------------- */
  if(swtSlavePortIdx < EthTSyn_GetSizeOfSlavePort())
  {
    ETHTSYN_CONSTP2VAR(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(swtSlavePortIdx);
    /* #10 Check that sync ingress timestamp is ready for processing. */
    if(EthTSyn_IsTimestampReadyToProcess(syncReceiveSmPtr->Sync.IngressTimestampMgmt.State) == TRUE)
    {
      EthTSyn_MasterPortIterType masterPortIter;

      /* #20 Provide timestamps for switch time synchronization if required. */
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
      if(EthTSyn_GetSiteSyncSyncSm(TimeDomainIdx).ProvideSwtTimeSyncTimestamps == TRUE)
      {
        EthTSyn_SwtTimeSync_ProvideTimestampsFromSwtSlavePort(TimeDomainIdx, swtSlavePortIdx);
      }
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */

      /* #30 Iterate over all master Ports. */
      for(masterPortIter = EthTSyn_GetMasterPortStartIdxOfTimeDomain(TimeDomainIdx);
          masterPortIter < EthTSyn_GetMasterPortEndIdxOfTimeDomain(TimeDomainIdx);
          masterPortIter++)
      {
        EthTSyn_SyncSendSmPtrType syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIter);

        /* #40 Check if Sync send state machine of the master port is in a state where the FollowUp should be send. */
        if( (syncSendSmPtr->State == ETHTSYN_S_SYNC_SEND_SM_SSS_WAIT_FUP) ||
            (syncSendSmPtr->State == ETHTSYN_S_SYNC_SEND_SM_SSS_TX_FUP) )
        {
          /* #50 Trigger transmission of the FollowUp message. */
          syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_SSS_TX_FUP;                                                    /* SBSW_ETHTSYN_CSL02 */
          EthTSyn_SwtMgmtTx_TxFollowUpMsg(masterPortIter);
        }
      }
    }
  }
} /* EthTSyn_SwtMgmt_HandleSendFollowUpStateOfSiteSyncSyncSm() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_HandleReceivedFupAfterTimeoutStateOfSiteSyncSyncSm
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_HandleReceivedFupAfterTimeoutStateOfSiteSyncSyncSm(
  EthTSyn_TimeDomainIterType TimeDomainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_IntSlavePortIdxType slavePortIdx = EthTSyn_SwtMgmt_GetSwitchSlavePortIdx(TimeDomainIdx);
  ETHTSYN_CONSTP2VAR(EthTSyn_TimeDomainStateType) timeDomainStatePtr = EthTSyn_GetAddrTimeDomainState(TimeDomainIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if bridge acted as grand master. */
  if(timeDomainStatePtr->SlavePortIdx != slavePortIdx)
  {
    EthTSyn_MasterPortIterType masterPortIter;
    /* #20 Bridge acted as grand master after sync-timeout --> "enable" the slave port again and start 'normal'
     *     bridge operation again. */
    timeDomainStatePtr->SlavePortIdx = slavePortIdx;                                                                   /* SBSW_ETHTSYN_API_ARGUMENT_IDX */

    /* #30 Iterate over all master Ports. */
    for(masterPortIter = EthTSyn_GetMasterPortStartIdxOfTimeDomain(TimeDomainIdx);
        masterPortIter < EthTSyn_GetMasterPortEndIdxOfTimeDomain(TimeDomainIdx);
        masterPortIter++)
    {
      ETHTSYN_CONSTP2VAR(EthTSyn_SyncSendSmType) syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIter);
      /* #40 Ensure that no Sync/FollowUp cycle is ongoing. */
      if(syncSendSmPtr->State != ETHTSYN_S_SYNC_SEND_SM_TX_FUP)
      {
        /* #50 Enable 'normal' bridge operation for the master Port. */
        syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_SSS_PENDING;                                                     /* SBSW_ETHTSYN_CSL02 */
      }
    }
  }
} /* EthTSyn_SwtMgmt_HandleReceivedFupAfterTimeoutStateOfSiteSyncSyncSm() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Init(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_TimeDomainIterType timeDomainIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize message buffers */
  IpBase_Fill((ETHTSYN_P2VAR(IpBase_CopyDataType))EthTSyn_SwtMgmt_MsgBuffer, 0, sizeof(EthTSyn_SwtMgmt_MsgBuffer)); /* PRQA S 0310 */ /* MD_EthTSyn_0310_IpBase */ /* SBSW_ETHTSYN_VARIABLE_ARRAY_AS_POINTER */

  /* #20 Initialize site sync sync state machine */
  for(timeDomainIter = 0; timeDomainIter < EthTSyn_GetSizeOfTimeDomain(); timeDomainIter++)
  {
    ETHTSYN_CONSTP2VAR(EthTSyn_TimeDomainStateType) timeDomainStatePtr = EthTSyn_GetAddrTimeDomainState(timeDomainIter);
    ETHTSYN_CONSTP2VAR(EthTSyn_SiteSyncSyncSmType) siteSyncSyncSmPtr = EthTSyn_GetAddrSiteSyncSyncSm(timeDomainIter);
    const EthTSyn_IntSlavePortIdxType swtSlavePortIdx = EthTSyn_SwtMgmt_GetSwitchSlavePortIdx(timeDomainIter);
    /* #2000 Initialize site sync sync state machine state */
    if(swtSlavePortIdx < EthTSyn_GetSizeOfSlavePort())
    {
      ETHTSYN_CONSTP2VAR(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(swtSlavePortIdx);
      timeDomainStatePtr->SlavePortIdx = swtSlavePortIdx;                                                              /* SBSW_ETHTSYN_CSL02 */

      siteSyncSyncSmPtr->TxConfirmationPending = 0;                                                                    /* SBSW_ETHTSYN_CSL02 */
      siteSyncSyncSmPtr->State = ETHTSYN_S_SSS_SM_PENDING;                                                             /* SBSW_ETHTSYN_CSL02 */

      syncReceiveSmPtr->Sync.SyncRxTimeoutCnt = EthTSyn_GetSwtMgmtSyncTimeoutOfTimeDomain(timeDomainIter);             /* SBSW_ETHTSYN_CSL02 */
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
      syncReceiveSmPtr->Sync.EgressTimestampMgmtHostPort.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_INVALID;            /* SBSW_ETHTSYN_CSL02 */
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */
    }
    else
    {
      siteSyncSyncSmPtr->State = ETHTSYN_S_SSS_SM_DISABLED;                                                            /* SBSW_ETHTSYN_CSL02 */
      timeDomainStatePtr->SlavePortIdx = EthTSyn_GetSizeOfSlavePort();                                                 /* SBSW_ETHTSYN_CSL02 */
    }
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
    siteSyncSyncSmPtr->ProvideSwtTimeSyncTimestamps = FALSE;
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
  }
} /* EthTSyn_SwtMgmt_Init() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_ProcessSmSiteSyncSync
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_ProcessSmSiteSyncSync(
  EthTSyn_TimeDomainIterType TimeDomainIdx)
{
  /* ----- Implementation --------------------------------------------- */
  /* #10 Check state of the SiteSyncSync state machine. */
  switch((EthTSyn_GetAddrSiteSyncSyncSm(TimeDomainIdx))->State)
  {
  case ETHTSYN_S_SSS_SM_TX_SYNC:
    {
      /* #100 Handle Send Sync state. */
      EthTSyn_SwtMgmt_HandleSendSyncStateOfSiteSyncSyncSm(TimeDomainIdx);
      break; /* END: ETHTSYN_SITE_SYNC_SYNC_SM_SEND_SYNC */
    }

  case ETHTSYN_S_SSS_SM_TX_FUP:
    {
      /* #101 Handle Send FollowUp state. */
      EthTSyn_SwtMgmt_HandleSendFollowUpStateOfSiteSyncSyncSm(TimeDomainIdx);
      break; /* END: ETHTSYN_S_SSS_SM_TX_FUP */
    }

  case ETHTSYN_S_SSS_SM_RCVD_FUP_AFTER_TIMEOUT:
    {
      /* #102 Handle Received FollowUp after timeout state. */
      EthTSyn_SwtMgmt_HandleReceivedFupAfterTimeoutStateOfSiteSyncSyncSm(TimeDomainIdx);
      break; /* END: ETHTSYN_S_SSS_SM_RCVD_FUP_AFTER_TIMEOUT */
    }

  default:
    {
      /* Nothing to do here. */
      break;
    }
  }

} /* EthTSyn_ProcessSmSitySyncSync() */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmtRx_HandleMessageReception
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(uint8, ETHTSYN_CODE) EthTSyn_SwtMgmtRx_HandleMessageReception(
                  EthTSyn_IntCtrlIdxType EthTSynCtrlIdx,
  ETHTSYN_P2CONST(uint8)                 DataPtr,
                  uint16                 LenByte)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_P2VAR(EthTSyn_SwtMgmt_MsgBufferType) msgBufferPtr;
  uint8 errorId;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Perform basic message checks and get a free message buffer. */
  errorId = EthTSyn_SwtMgmtRx_PerformBasicMsgChecksAngGetMsgBuffer(LenByte, DataPtr, &msgBufferPtr);                   /* SBSW_ETHTSYN_PASSING_API_POINTER */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
  if(errorId == ETHTSYN_E_NO_ERROR)
  {
    /* #20 Map message buffer to the Frame. */
    msgBufferPtr->SwtMgmtInfo.FrameId = EthTSyn_Util_GetFrameId(DataPtr, LenByte);                                     /* SBSW_ETHTSYN_POINTER_VARIABLE_WRITE */ /* SBSW_ETHTSYN_PASSING_API_POINTER */
    msgBufferPtr->CtrlIdx = EthTSynCtrlIdx;                                                                            /* SBSW_ETHTSYN_POINTER_VARIABLE_WRITE */
    msgBufferPtr->RxBufAddr = DataPtr;                                                                                 /* SBSW_ETHTSYN_POINTER_VARIABLE_WRITE */

    /* #30 Handle Timestamping. */
    EthTSyn_SwtMgmtRx_HandleIngressTimestamp(EthTSyn_GetEthIfCtrlIdxOfCtrl(EthTSynCtrlIdx), DataPtr, msgBufferPtr);    /* SBSW_ETHTSYN_PASSING_API_POINTER */ /* SBSW_ETHTSYN_POINTER_VARIABLE */

    /* #40 Copy the received message to the message buffer for later processing. */
    /* Copy the Message Header */
    /* PRQA S 0310 2 */ /* MD_EthTSyn_0310_IpBase */
    IpBase_Copy((ETHTSYN_P2VAR(IpBase_CopyDataType))&msgBufferPtr->Msg.MsgHdr,                                         /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */
      (ETHTSYN_P2CONST(IpBase_CopyDataType))DataPtr, ETHTSYN_HDR_COM_LENGTH);

    /* Copy the Message (Payload) */
    /* PRQA S 0310 3 */ /* MD_EthTSyn_0310_IpBase */
    IpBase_Copy((ETHTSYN_P2VAR(IpBase_CopyDataType))msgBufferPtr->Msg.Payload,                                         /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */
        (ETHTSYN_P2CONST(IpBase_CopyDataType))&DataPtr[ETHTSYN_HDR_COM_LENGTH],
        (EthTSyn_Ntohs(msgBufferPtr->Msg.MsgHdr.MessageLength) - ETHTSYN_HDR_COM_LENGTH));

    msgBufferPtr->MsgBufferState = ETHTSYN_S_MSG_BUFFER_MSG_VALID;                                                     /* SBSW_ETHTSYN_POINTER_VARIABLE_WRITE */
  }

  return errorId;
} /* EthTSyn_SwtMgmtRx_HandleMessageReception() */


/**********************************************************************************************************************
 *  EthTSyn_SwitchMgmtInfoIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_SwitchMgmtInfoIndication(
                    uint8                CtrlIdx,
    ETHTSYN_P2CONST(uint8)               DataPtr,
    ETHTSYN_P2CONST(EthSwt_MgmtInfoType) MgmtInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHTSYN_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check input parameters. */
  if(EthTSyn_State == ETHTSYN_STATE_UNINIT)
  {
    errorId = ETHTSYN_E_NOT_INITIALIZED;
  }
  else if(DataPtr == NULL_PTR)
  {
    errorId = ETHTSYN_E_PARAM_POINTER;
  }
  else if(MgmtInfoPtr == NULL_PTR)
  {
    errorId = ETHTSYN_E_PARAM_POINTER;
  }
  else
# endif /* ETHTSYN_DEV_ERROR_DETECT */
  {
    /* ----- Implementation --------------------------------------------- */
    const EthTSyn_IntCtrlIdxType ethTSynCtrlIdx = EthTSyn_Util_GetEthTSynCtrlFromEthIfCtrl(CtrlIdx);
    if(ethTSynCtrlIdx < EthTSyn_GetSizeOfCtrl())
    {
      /* #20 Store Switch management information and trigger processing of message buffer if applicable. */
      EthTSyn_SwtMgmtRx_StoreSwitchMgmtInfo(ethTSynCtrlIdx, DataPtr, MgmtInfoPtr);                                     /* SBSW_ETHTSYN_PASSING_API_POINTER */
    }
# if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
    else
    {
      errorId = ETHTSYN_E_CTRL_IDX;
    }
# endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */
  }

  /* ----- Development Error Report ------------------------------------- */
# if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #30 Report error to default error tracer (DET) if any occurred. */
  if(errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, ETHTSYN_SWT_MGMT_SID_SWITCH_MGMT_INFO_INDICATION,
      errorId);
  }
# else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* ETHTSYN_DEV_ERROR_REPORT */
} /* EthTSyn_SwitchMgmtInfoIndication() */

/**********************************************************************************************************************
 *  EthTSyn_SwitchEgressTimeStampIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_SwitchEgressTimeStampIndication(
                  uint8                CtrlIdx,
  ETHTSYN_P2CONST(uint8)               DataPtr,
  ETHTSYN_P2CONST(EthSwt_MgmtInfoType) MgmtInfoPtr,
  ETHTSYN_P2CONST(Eth_TimeStampType)   timeStampPtr)
{
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHTSYN_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check input parameters */
#  if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  if(EthTSyn_State == ETHTSYN_STATE_UNINIT)
  {
    errorId = ETHTSYN_E_NOT_INITIALIZED;
  }
  else if(DataPtr == NULL_PTR)
  {
    errorId = ETHTSYN_E_PARAM_POINTER;
  }
  else if(MgmtInfoPtr == NULL_PTR)
  {
    errorId = ETHTSYN_E_PARAM_POINTER;
  }
  else
#  endif /* ETHTSYN_DEV_ERROR_DETECT */
  {
    /* ----- Implementation --------------------------------------------- */
    const EthTSyn_IntCtrlIdxType ethTSynCtrlIdx = EthTSyn_Util_GetEthTSynCtrlFromEthIfCtrl(CtrlIdx);
    if(ethTSynCtrlIdx < EthTSyn_GetSizeOfCtrl())
    {
      /* #20 Store the switch egress timestamp and trigger further processing if applicable. */
      EthTSyn_SwtMgmt_StoreSwitchEgressTimestamp(ethTSynCtrlIdx, DataPtr, MgmtInfoPtr, timeStampPtr);                  /* SBSW_ETHTSYN_PASSING_API_POINTER */ /* SBSW_ETHTSYN_POINTER_VARIABLE */
    }
#  if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
    else
    {
      errorId = ETHTSYN_E_CTRL_IDX;
    }
#  endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */
  }

  /* ----- Development Error Report ------------------------------------- */
#  if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #30 Report error to default error tracer (DET) if any occurred. */
  if(errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID,
        ETHTSYN_SWT_MGMT_SID_SWITCH_EGRESS_TIMESTAMP_INDICATION, errorId);
  }
#  else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#  endif /* ETHTSYN_DEV_ERROR_REPORT */
# else
/*(ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF) */
  ETHTSYN_DUMMY_STATEMENT(CtrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETHTSYN_DUMMY_STATEMENT(DataPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETHTSYN_DUMMY_STATEMENT(MgmtInfoPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETHTSYN_DUMMY_STATEMENT(timeStampPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */
} /* EthTSyn_SwitchEgressTimeStampIndication() */

/**********************************************************************************************************************
 *  EthTSyn_SwitchIngressTimeStampIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_SwitchIngressTimeStampIndication(
                  uint8                CtrlIdx,
  ETHTSYN_P2CONST(uint8)               DataPtr,
  ETHTSYN_P2CONST(EthSwt_MgmtInfoType) MgmtInfoPtr,
  ETHTSYN_P2CONST(Eth_TimeStampType)   timeStampPtr)
{
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHTSYN_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check input parameters */
#  if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  if(EthTSyn_State == ETHTSYN_STATE_UNINIT)
  {
    errorId = ETHTSYN_E_NOT_INITIALIZED;
  }
  else if(DataPtr == NULL_PTR)
  {
    errorId = ETHTSYN_E_PARAM_POINTER;
  }
  else if(MgmtInfoPtr == NULL_PTR)
  {
    errorId = ETHTSYN_E_PARAM_POINTER;
  }
  else
#  endif /* ETHTSYN_DEV_ERROR_DETECT */
  {
    /* ----- Implementation --------------------------------------------- */
    const EthTSyn_IntCtrlIdxType ethTSynCtrlIdx = EthTSyn_Util_GetEthTSynCtrlFromEthIfCtrl(CtrlIdx);
    if(ethTSynCtrlIdx < EthTSyn_GetSizeOfCtrl())
    {
      /* #20 Store the switch ingress timestamp and trigger further processing if applicable. */
      EthTSyn_SwtMgmt_StoreSwitchIngressTimestamp(ethTSynCtrlIdx, DataPtr, MgmtInfoPtr, timeStampPtr);                 /* SBSW_ETHTSYN_PASSING_API_POINTER */ /* SBSW_ETHTSYN_POINTER_VARIABLE */
    }
#  if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
    else
    {
      errorId = ETHTSYN_E_CTRL_IDX;
    }
#  endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */
  }

  /* ----- Development Error Report ------------------------------------- */
#  if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #30 Report error to default error tracer (DET) if any occurred. */
  if(errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID,
      ETHTSYN_SWT_MGMT_SID_SWITCH_INGRESS_TIMESTAMP_INDICATION, errorId);
  }
#  else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#  endif /* ETHTSYN_DEV_ERROR_REPORT */
# else
  /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF) */
  ETHTSYN_DUMMY_STATEMENT(CtrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETHTSYN_DUMMY_STATEMENT(DataPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETHTSYN_DUMMY_STATEMENT(MgmtInfoPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETHTSYN_DUMMY_STATEMENT(timeStampPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */
} /* EthTSyn_SwitchIngressTimeStampIndication() */
# define ETHTSYN_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ETHTSYN_SWT_MGMT_SUPPORT */

/* Justification for module-specific MISRA deviations:
 * see file EthTSyn.c
*/


/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_SwtMgmt.c
 *********************************************************************************************************************/
