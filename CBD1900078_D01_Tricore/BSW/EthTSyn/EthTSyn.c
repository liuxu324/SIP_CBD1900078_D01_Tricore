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
 *         \file  EthTSyn.c
 *        \brief  EthTSyn implementation
 *
 *      \details  Contains the main implementation of the Time Sync over Ethernet (EthTSyn) AUTOSAR module
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


#define ETHTSYN_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* PRQA S 0857 MACRO_LIMIT */ /* MD_MSR_1.1_857 */
#include "EthTSyn_Int.h" /* PRQA S 3219, 0883 */ /* MD_EthTSyn_3219, MD_EthTSyn_0883 */
#include "EthTSyn_Master_Int.h"
#include "EthTSyn_Slave_Int.h" /* PRQA S 3219 */ /* MD_EthTSyn_3219 */
#include "EthTSyn_Pdelay_Int.h"
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
# include "EthTSyn_SwtMgmt_Int.h"
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
#  include "EthTSyn_SwtTimeSync_Int.h" /* PRQA S 0777 */ /* MD_MSR_5.1_777 */
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* vendor specific version information is BCD coded */
#if (  (ETHTSYN_SW_MAJOR_VERSION != (7u)) \
    || (ETHTSYN_SW_MINOR_VERSION != (0u)) \
    || (ETHTSYN_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of EthTSyn.c and EthTSyn.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (ETHTSYN_CFG_MAJOR_VERSION != (7u)) \
    || (ETHTSYN_CFG_MINOR_VERSION != (0u)) )
# error "Version numbers of EthTSyn.c and EthTSyn_Cfg.h are inconsistent!"
#endif


/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define ETHTSYN_IEEE_802_1_AS_CLOCK_IDENTITY_BYTE_3  0xFFu
#define ETHTSYN_IEEE_802_1_AS_CLOCK_IDENTITY_BYTE_4  0xFEu

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
#if !defined (ETHTSYN_LOCAL) /* COV_MSR_COMPATIBILITY */
# define ETHTSYN_LOCAL static
#endif

#if !defined (ETHTSYN_LOCAL_INLINE) /* COV_MSR_COMPATIBILITY */
# define ETHTSYN_LOCAL_INLINE LOCAL_INLINE
#endif


/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/* PRQA L: MACRO_LIMIT */
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
#define ETHTSYN_START_SEC_VAR_ZERO_INIT_8BIT
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

VAR(EthTSyn_StateEnumType, ETHTSYN_VAR_ZERO_INIT) EthTSyn_State = ETHTSYN_STATE_UNINIT;

#define ETHTSYN_STOP_SEC_VAR_ZERO_INIT_8BIT
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define ETHTSYN_START_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

/**********************************************************************************************************************
 *  EthTSyn_SetLocalClockIdentity
 *********************************************************************************************************************/
/*! \brief      Sets the local clock identity of the EthTSyn controller.
 *  \details    -
 *  \param[in]  EthTSynCtrlIdx   Index of the EthTSyn controller the clock identity should be set
 *                               [range: EthTSynCtrlIdx < EthTSyn_GetSizeOfCtrl()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetLocalClockIdentity(
  EthTSyn_IntCtrlIdxType EthTSynCtrlIdx);

/**********************************************************************************************************************
 *  EthTSyn_InitPort
 *********************************************************************************************************************/
/*! \brief      Initializes an EthTSyn Port.
 *  \details    Initializes all component variables directly related to the passed EthTSyn Port.
 *  \param[in]  PortIdx   Index of the Port that should be initialized
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_InitPort(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_InitCtrl
 *********************************************************************************************************************/
/*! \brief      Initializes an EthTSyn controller.
 *  \details    Initializes all component variables directly related to the passed EthTSyn controller.
 *  \param[in]  EthTSynCtrlIdx   Index of the EthTSyn controller
 *                               [range: EthTSynCtrlIdx < EthTSyn_GetSizeOfCtrl()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_InitCtrl(
  EthTSyn_CtrlIterType EthTSynCtrlIdx);

/**********************************************************************************************************************
 *  EthTSyn_ResetPortsAndPdelayOfCtrl
 *********************************************************************************************************************/
/*! \brief      Initializes all Ports of the passed EthTSyn controller.
 *  \details    -
 *  \param[in]  EthTSynCtrlIdx   Index of the EthTSyn controller the Ports should be initialized for.
 *                               [range: EthTSynCtrlIdx < EthTSyn_GetSizeOfCtrl()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_ResetPortsAndPdelayOfCtrl(
  EthTSyn_IntCtrlIdxType EthTSynCtrlIdx);

/**********************************************************************************************************************
 *  EthTSyn_HandleEgressTimestamping
 *********************************************************************************************************************/
/*! \brief      Handles the egress timestamping for the given Port and message type.
 *  \details    Retrieves all required timestamps for the given Port and message type of a former transmitted message
 *              and assigns the timestamps to the corresponding state machine.
 *  \param[in]  PortIdx   Index of the EthTSyn port
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  MsgType   Type of the message
 *  \param[in]  BufIdx    Index of the Ethernet TxBuffer
 *  \pre        Check if egress timestamp is required was already performed (EthTSyn_TxConf_IsEgressTimestampRequired())
 *  \pre        Has to be called in the context of EthTSyn_TxConfirmation()
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices and/or msg types
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_HandleEgressTimestamping(
  EthTSyn_IntPortIdxType PortIdx,
  uint8                  MsgType,
  uint8                  BufIdx);

/**********************************************************************************************************************
 *  EthTSyn_EgressTimestamp_GetSyncRefTime
 *********************************************************************************************************************/
/*! \brief       If the transmitted message was a Sync message, a sync reference time will be retrieved.
 *  \details     Retrieves the sync reference time (i.e. get current global time and HW reference time if applicable)
 *               when the MsgType == SYNC and stores it in provided EgressTimestampHandle. Does nothing otherwise.
 *  \param[in]   PortIdx                    Index of the EthTSyn port the message was transmitted on
 *                                          [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]   MsgType                    The type of the transmitted message
 *  \param[out]  EgressTimestampHandlePtr   The parts of the egress timestamp handle relevant for sync messages
 *  \pre         Egress Timestamp is required (can be checked by EthTSyn_TxConf_IsEgressTimestampRequired())
 *  \return      E_OK - Successfully retrieve sync reference time (or not a sync message)
 *  \return      E_NOT_OK - Failed to retrieve sync reference time
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different egress timestamp handle elements
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_EgressTimestamp_GetSyncRefTime(
                EthTSyn_IntPortIdxType                 PortIdx,
                uint8                                  MsgType,
  ETHTSYN_P2VAR(EthTSyn_EgressTimestampHandleType)     EgressTimestampHandlePtr);

/**********************************************************************************************************************
 *  EthTSyn_EgressTimestamp_GetTimestamp
 *********************************************************************************************************************/
/*! \brief       Get the actual egress timestamp.
 *  \details     Get the transmission timestamp either from HW or SW (StbM) if required for the passes message type.
 *  \param[in]   PortIdx                    Index of the EthTSyn port the message was transmitted on
 *  \param[in]   MsgType                    The type of the transmitted message
 *  \param[in]   BufIdx                     Index of the Ethernet TxBuffer
 *  \param[out]  EgressTimestampHandlePtr   The actual egress timestamp in the egress timestamp handle
 *  \return      E_OK - Successfully retrieve the egress timestamp
 *  \return      E_NOT_OK - Failed to retrieve the egress timestamp
 *  \pre         Egress Timestamp is required (can be checked by EthTSyn_TxConf_IsEgressTimestampRequired())
 *  \pre         Has to be called in the context of EthTSyn_TxConfirmation()
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different egress timestamp handle elements
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_EgressTimestamp_GetTimestamp(
                EthTSyn_IntPortIdxType                 PortIdx,
                uint8                                  MsgType,
                uint8                                  BufIdx,
  ETHTSYN_P2VAR(EthTSyn_EgressTimestampHandleType)     EgressTimestampHandlePtr);

/**********************************************************************************************************************
 *  EthTSyn_EgressTimestamp_AssignTimestamp
 *********************************************************************************************************************/
/*! \brief      Assigns the egress timestamp to state machine.
 *  \details    Assigns the passed egress timestamp to the state machine (and message of the state machine) which
 *              triggered the transmission of the message.
 *  \param[in]  PortIdx                    Index of the EthTSyn port the message was transmitted on
 *                                         [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  MsgType                    The type of the transmitted message
 *  \param[in]  EgressTimestampHandlePtr   The egress timestamp handle
 *  \pre        For PortIdx the following constraints apply depending on MsgType
 *              ETHTSYN_MSG_TYPE_SYNC: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *              ETHTSYN_MSG_TYPE_PDELAY_REQ: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                           EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                           EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig() == TRUE
 *              ETHTSYN_MSG_TYPE_PDELAY_RESP: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                            EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                            EthTSyn_IsPdelayResponderUsedOfPdelayConfig() == TRUE
 *  \pre        Egress Timestamp is required (can be checked by EthTSyn_TxConf_IsEgressTimestampRequired())
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different PortIdx - MsgType tuples
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_EgressTimestamp_AssignTimestamp(
                  EthTSyn_IntPortIdxType                 PortIdx,
                  uint8                                  MsgType,
  ETHTSYN_P2CONST(EthTSyn_EgressTimestampHandleType)     EgressTimestampHandlePtr);

/**********************************************************************************************************************
 *  EthTSyn_TxConf_GetTxPortAndMsgType
 *********************************************************************************************************************/
/*! \brief      Get EthTSyn-Port and message type the TxConfirmation was called for.
 *  \details    -
 *  \param[in]  EthTSynCtrlIdx  Pointer to the common message header
 *  \param[in]  TxBufIdx        Transmission buffer index
 *  \param[out] PortIdxPtr      Index of the Port the message was transmitted on
 *  \param[out] MsgTypePtr      Type of the message the TxConfirmation was called for
 *  \return     E_OK - Port and message type found. All out parameters are valid.
 *  \return     E_NOT_OK - Port or message type not found. Out parameters are invalid.
 *  \pre        Has to be called in the context of EthTSyn_TxConfirmation()
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_TxConf_GetTxPortAndMsgType(
                EthTSyn_IntCtrlIdxType  EthTSynCtrlIdx,
                uint8                   TxBufIdx,
  ETHTSYN_P2VAR(EthTSyn_IntPortIdxType) PortIdxPtr,
  ETHTSYN_P2VAR(uint8)                  MsgTypePtr);

/**********************************************************************************************************************
 *  EthTSyn_TxConf_IsEgressTimestampRequired
 *********************************************************************************************************************/
/*! \brief      Checks if an egress timestamp is required.
 *  \details    Checks if an egress timestamp is required for the passed message type.
 *  \param[in]  PortIdx  Index of the Port the message was transmitted on
 *  \param[in]  MsgType  Type of the message the TxConfirmation was called for
 *  \return     TRUE - Egress timestamp required
 *  \return     FALSE - Egress timestamp not required
 *  \pre        For PortIdx the following constraints apply depending on MsgType
 *              ETHTSYN_MSG_TYPE_SYNC: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_TxConf_IsEgressTimestampRequired(
  EthTSyn_IntPortIdxType  PortIdx,
  uint8                   MsgType);

/**********************************************************************************************************************
 *  EthTSyn_TxConf_ProcessTxConfirmation
 *********************************************************************************************************************/
/*! \brief      Process the TxConfirmation, i.e. handle state machines.
 *  \details    -
 *  \param[in]  PortIdx     Index of the Port the message was transmitted on
 *                          [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  MsgType     Type of the message the TxConfirmation was called for
 *  \pre        For PortIdx the following constraints apply depending on MsgType
 *              ETHTSYN_MSG_TYPE_SYNC: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *              ETHTSYN_MSG_TYPE_FOLLOW_UP: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *              ETHTSYN_MSG_TYPE_PDELAY_REQ: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                           EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                           EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig() == TRUE
 *              ETHTSYN_MSG_TYPE_PDELAY_RESP: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                            EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                            EthTSyn_IsPdelayResponderUsedOfPdelayConfig() == TRUE
 *  \pre        Has to be called in the context of EthTSyn_TxConfirmation()
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different PortIdx - MsgType tuples.
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TxConf_ProcessTxConfirmation(
                EthTSyn_IntPortIdxType  PortIdx,
                uint8                   MsgType);

#if (ETHTSYN_MASTER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_TxConf_ProcessSyncTxConfirmation
 *********************************************************************************************************************/
/*! \brief      Processes the TxConfirmation for a Sync message.
 *  \details    -
 *  \param[in]  PortIdx     Index of the Port the Sync message was transmitted on
 *                          [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre        Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \pre        Has to be called in the context of EthTSyn_TxConfirmation()
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices.
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TxConf_ProcessSyncTxConfirmation(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_TxConf_ProcessFollowUpTxConfirmation
 *********************************************************************************************************************/
/*! \brief      Processes the TxConfirmation for a FollowUp message.
 *  \details    -
 *  \param[in]  PortIdx     Index of the Port the FollowUp message was transmitted on
 *                          [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre        Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \pre        Has to be called in the context of EthTSyn_TxConfirmation()
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices.
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TxConf_ProcessFollowUpTxConfirmation(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_TxConf_HandleSyncSentCallback
 *********************************************************************************************************************/
/*! \brief      Handles the optional callback for a transmitted Sync message.
 *  \details    -
 *  \param[in]  PortIdx  Index of the Port the Sync message was transmitted on
 *  \pre        Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \pre        Has to be called in the context of EthTSyn_TxConfirmation()
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices.
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TxConf_HandleSyncSentCallback(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_TxConf_HandleFollowUpSentCallback
 *********************************************************************************************************************/
/*! \brief      Handles the optional callback for a transmitted FollowUp message.
 *  \details    -
 *  \param[in]  PortIdx  Index of the Port the FollowUp message was transmitted on
 *  \pre        Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \pre        Has to be called in the context of EthTSyn_TxConfirmation()
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices.
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TxConf_HandleFollowUpSentCallback(
  EthTSyn_IntPortIdxType PortIdx);
#endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */

#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_RxInd_ProcRcvdMsg
 *********************************************************************************************************************/
/*! \brief      Processes a received message.
 *  \details    Performs basic message checks, retrieves the port index on which the message was received and triggers
 *              the actual processing of the message.
 *  \param[in]  EthTSynCtrlIdx  Index of the EthTSyn Ctrl the message was received on
 *  \param[in]  LenByte         The received message length passed to EthTSyn_RxIndication() from EthIf
 *  \param[in]  DataPtr         Pointer to the Rx-Buffer passed to the EthTSyn_RxIndication from EthIf
 *  \return     ETHTSYN_E_NO_ERROR - Message was passed to sub-component for reception
 *  \return     other values - Any error occurred and message was not received. Corresponding error id is returned
 *  \pre        Has to be called in the context of EthTSyn_RxIndication()
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different EthTSyn controller indices.
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_RxInd_ProcRcvdMsg(
                  EthTSyn_IntCtrlIdxType  EthTSynCtrlIdx,
                  uint16                  LenByte,
  ETHTSYN_P2CONST(uint8)                  DataPtr);
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_RxInd_PerformBasicMsgChecksAndGetPort
 *********************************************************************************************************************/
/*! \brief      Performs basic message checks and gets the EthTSyn Port the message was received on.
 *  \details    -
 *  \param[in]  EthTSynCtrlIdx  Index of the EthTSyn Ctrl the message was received on
 *  \param[in]  LenByte         The received message length passed to EthTSyn_RxIndication() from EthIf
 *  \param[in]  DataPtr         Pointer to the Rx-Buffer passed to the EthTSyn_RxIndication from EthIf
 *  \param[out] PortIdxPtr      Index of the EthTSyn Port the message was received on
 *  \return     ETHTSYN_E_NO_ERROR - Basic message checks passed. Out parameter is valid.
 *  \return     other values - Basic message check failed. Corresponding error id is returned.
 *  \pre        Has to be called in the context of EthTSyn_RxIndication()
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \note       Verification of message type, length and protocol version.
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_RxInd_PerformBasicMsgChecksAndGetPort(
                  EthTSyn_IntCtrlIdxType   EthTSynCtrlIdx,
                  uint16                   LenByte,
  ETHTSYN_P2CONST(uint8)                   DataPtr,
    ETHTSYN_P2VAR(EthTSyn_IntPortIdxType)  PortIdxPtr);
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_SetLocalClockIdentity
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetLocalClockIdentity(
  EthTSyn_IntCtrlIdxType EthTSynCtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_PhysAddrType physAddr;
  ETHTSYN_P2VAR(EthTSyn_CtrlStateType) ctrlStatePtr = EthTSyn_GetAddrCtrlState(EthTSynCtrlIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the physical address for the EthIf controller of the passed EthTSyn controller. */
  EthIf_GetPhysAddr(EthTSyn_GetEthIfCtrlIdxOfCtrl(EthTSynCtrlIdx), &physAddr[0]);                                      /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */

  /* #20 Derive the clock identity from the physical address according to IEEE802.1As and store it. */
  /* According to IEEE802.1As the clock identity is an EUI-64 derived by the EUI-48 MAC address in the following way:
   * 1. Assign higher three bytes of MAC address (OUI) to higher three of the clock identity
   * 2. Assign 0xFF and 0xFE to bytes 3 respectively 4 to clock identity
   * 3. Assign lower three bytes of MAC address to lower three bytes of the clock identity */
  ctrlStatePtr->ClockIdentity[0] = physAddr[0];                                                                        /* SBSW_ETHTSYN_API_ARGUMENT_IDX */ /* SBSW_ETHTSYN_ARRAY_SIZE */
  ctrlStatePtr->ClockIdentity[1] = physAddr[1];                                                                        /* SBSW_ETHTSYN_API_ARGUMENT_IDX */ /* SBSW_ETHTSYN_ARRAY_SIZE */
  ctrlStatePtr->ClockIdentity[2] = physAddr[2];                                                                        /* SBSW_ETHTSYN_API_ARGUMENT_IDX */ /* SBSW_ETHTSYN_ARRAY_SIZE */
  ctrlStatePtr->ClockIdentity[3] = ETHTSYN_IEEE_802_1_AS_CLOCK_IDENTITY_BYTE_3;                                        /* SBSW_ETHTSYN_API_ARGUMENT_IDX */ /* SBSW_ETHTSYN_ARRAY_SIZE */
  ctrlStatePtr->ClockIdentity[4] = ETHTSYN_IEEE_802_1_AS_CLOCK_IDENTITY_BYTE_4;                                        /* SBSW_ETHTSYN_API_ARGUMENT_IDX */ /* SBSW_ETHTSYN_ARRAY_SIZE */
  ctrlStatePtr->ClockIdentity[5] = physAddr[3];                                                                        /* SBSW_ETHTSYN_API_ARGUMENT_IDX */ /* SBSW_ETHTSYN_ARRAY_SIZE */
  ctrlStatePtr->ClockIdentity[6] = physAddr[4];                                                                        /* SBSW_ETHTSYN_API_ARGUMENT_IDX */ /* SBSW_ETHTSYN_ARRAY_SIZE */
  ctrlStatePtr->ClockIdentity[7] = physAddr[5];                                                                        /* SBSW_ETHTSYN_API_ARGUMENT_IDX */ /* SBSW_ETHTSYN_ARRAY_SIZE */
} /* EthTSyn_SetLocalClockIdentity() */

/**********************************************************************************************************************
 *  EthTSyn_InitPort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_InitPort(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Implementation ----------------------------------------------- */
#if ( (ETHTSYN_MASTER_SUPPORT == STD_ON) && (ETHTSYN_SLAVE_SUPPORT == STD_ON) )
  /* #10 Check Port role. */
  if(EthTSyn_IsMasterPortUsedOfPort(PortIdx) == TRUE)
#endif /* ( (ETHTSYN_MASTER_SUPPORT == STD_ON) && (ETHTSYN_SLAVE_SUPPORT == STD_ON) ) */
  {
#if (ETHTSYN_MASTER_SUPPORT == STD_ON)
    /* #100 Master Port -> Trigger initialization of master port. */
    EthTSyn_Master_InitPort(EthTSyn_GetMasterPortIdxOfPort(PortIdx));
#endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */
  }
#if ( (ETHTSYN_MASTER_SUPPORT == STD_ON) && (ETHTSYN_SLAVE_SUPPORT == STD_ON) )
  else
#endif /* ( (ETHTSYN_MASTER_SUPPORT == STD_ON) && (ETHTSYN_SLAVE_SUPPORT == STD_ON) ) */
  {
    /* #101 Slave Port -> Trigger initialization of slave port. */
#if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
    EthTSyn_Slave_InitPort(EthTSyn_GetSlavePortIdxOfPort(PortIdx));
#endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */
  }
} /* End of EthTSyn_InitPort() */

/**********************************************************************************************************************
 * EthTSyn_InitCtrl
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_InitCtrl(
  EthTSyn_CtrlIterType EthTSynCtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_CONSTP2VAR(EthTSyn_CtrlStateType) ctrlStatePtr = EthTSyn_GetAddrCtrlState(EthTSynCtrlIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* If module was not initialized yet, initialize transceiver link state. */
  if(EthTSyn_State == ETHTSYN_STATE_UNINIT)
  {
    ctrlStatePtr->TrcvLinkState = ETHTRCV_LINK_STATE_DOWN;                                                             /* SBSW_ETHTSYN_CSL01 */
  }
  ctrlStatePtr->TransmissionMode = ETHTSYN_TX_ON;                                                                      /* SBSW_ETHTSYN_CSL01 */
  IpBase_Fill((ETHTSYN_P2VAR(IpBase_CopyDataType))ctrlStatePtr->ClockIdentity, 0, sizeof(EthTSyn_ClockIdentityType));  /* SBSW_ETHTSYN_CSL01 */ /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
} /* EthTSyn_InitCtrl() */

/**********************************************************************************************************************
 * EthTSyn_ResetPortsAndPdelayOfCtrl
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_ResetPortsAndPdelayOfCtrl(
  EthTSyn_IntCtrlIdxType EthTSynCtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_PortIndIterType portIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all EthTSyn ports of the given EthTSyn controller. */
  for(portIter = EthTSyn_GetPortIndStartIdxOfCtrl(EthTSynCtrlIdx);
      portIter < EthTSyn_GetPortIndEndIdxOfCtrl(EthTSynCtrlIdx);
      portIter++)
  {
    const EthTSyn_IntPortIdxType portIdx = EthTSyn_GetPortInd(portIter);

    /* #100 Init the current EthTSyn port. */
    EthTSyn_InitPort(portIdx);

    /* #101 Trigger Pdelay initialization. */
    if(EthTSyn_IsPdelayConfigUsedOfPort(portIdx) == TRUE)
    {
      EthTSyn_Pdelay_InitPdelayOfPort(portIdx);
    }
  }
} /* EthTSyn_ResetPortsAndPdelayOfCtrl() */

/**********************************************************************************************************************
 * EthTSyn_HandleEgressTimestamping
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_HandleEgressTimestamping(
  EthTSyn_IntPortIdxType PortIdx,
  uint8                  MsgType,
  uint8                  BufIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_EgressTimestampHandleType egressTimestampHandle;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the sync reference time if applicable. */
  if(EthTSyn_EgressTimestamp_GetSyncRefTime(PortIdx, MsgType, &egressTimestampHandle) == E_OK)                         /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
  {
    /* #20 Get the actual egress timestamp. */
    if(EthTSyn_EgressTimestamp_GetTimestamp(PortIdx, MsgType, BufIdx, &egressTimestampHandle) == E_OK)                 /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
    {
      /* #30 Assign the timestamp values to the correct state machine. */
      EthTSyn_EgressTimestamp_AssignTimestamp(PortIdx, MsgType, &egressTimestampHandle);                               /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
    }
  }
} /* EthTSyn_HandleEgressTimestamping() */

/**********************************************************************************************************************
 *  EthTSyn_EgressTimestamp_GetSyncRefTime
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_EgressTimestamp_GetSyncRefTime(
                EthTSyn_IntPortIdxType             PortIdx,
                uint8                              MsgType,
  ETHTSYN_P2VAR(EthTSyn_EgressTimestampHandleType) EgressTimestampHandlePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  StbM_TimeStampType timeStampGlobalStbm;
  StbM_UserDataType userData;
#if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  Eth_TimeStampQualType timeStampQual;
#endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if message is sync message. */
  if(MsgType == ETHTSYN_MSG_TYPE_SYNC)
  {
    const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
    const StbM_SynchronizedTimeBaseType synchronizedTimeBaseId =
      EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(timeDomainIdx);
    /* #20 Get the current global time from the StbM. */
    if(StbM_GetCurrentTime(synchronizedTimeBaseId, &timeStampGlobalStbm, &userData) == E_OK)                           /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
    {
      ETHTSYN_COPY_STBM_TS_TO_GLOBAL_TS(timeStampGlobalStbm, EgressTimestampHandlePtr->GlobalTimestamp);               /* SBSW_ETHTSYN_VALID_API_POINTER */ /* SBSW_ETHTSYN_VALID_API_POINTER */ /* SBSW_ETHTSYN_VALID_API_POINTER */
#if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
      /* HW-Timestamping */
      /* #30 If hardware timestamping is enabled, get the current HW time. */
      if(EthIf_GetCurrentTime(EthTSyn_Util_GetEthIfCtrlIdxOfPort(PortIdx), &timeStampQual,
          &EgressTimestampHandlePtr->SyncRefTimestamp) == E_OK)                                                        /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */ /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
      {
        if(timeStampQual == ETH_VALID)
        {
          retVal = E_OK;
        }
      }
#else
      /* SW-Timestamping */
      retVal = E_OK;
#endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

    }
  }
  else
  {
    retVal = E_OK;
  }

  return retVal;
} /* EthTSyn_EgressTimestamp_GetSyncRefTime() */

/**********************************************************************************************************************
 *  EthTSyn_EgressTimestamp_GetTimestamp
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_EgressTimestamp_GetTimestamp(
                EthTSyn_IntPortIdxType             PortIdx,
                uint8                              MsgType,
                uint8                              BufIdx,
  ETHTSYN_P2VAR(EthTSyn_EgressTimestampHandleType) EgressTimestampHandlePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
#if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  Eth_TimeStampQualType timeStampQual;
#endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If hardware timestamping is enabled, get the egress timestamp from the hardware. */
#if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  /* HW-Timestamping */
  ETHTSYN_DUMMY_STATEMENT(MsgType); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  retVal = E_NOT_OK;

  if(EthIf_GetEgressTimestamp(EthTSyn_Util_GetEthIfCtrlIdxOfPort(PortIdx), BufIdx,
      &EgressTimestampHandlePtr->EgressTimestamp, &timeStampQual) == E_OK)                                             /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */ /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
  {
    if(timeStampQual == ETH_VALID)
    {
      retVal = E_OK;
    }
  }
#else
  /* SW-Timestamping */
  /* #20 If hardware timestamping is disabled (i.e. SW timestamping is used) get the current raw time from the StbM */
  ETHTSYN_DUMMY_STATEMENT(BufIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  if((MsgType == ETHTSYN_MSG_TYPE_PDELAY_REQ) || (MsgType == ETHTSYN_MSG_TYPE_PDELAY_RESP))
  {
    const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
    const StbM_SynchronizedTimeBaseType timeBaseId = EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(timeDomainIdx);
    retVal = StbM_GetCurrentTimeRaw(timeBaseId, &EgressTimestampHandlePtr->RawTimestamp);                              /* SBSW_ETHTSYN_PASSING_API_POINTER */
  }
  else
  {
    retVal = E_OK;
  }
#endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

  return retVal;
} /* EthTSyn_EgressTimestamp_GetTimestamp() */

/**********************************************************************************************************************
 *  EthTSyn_EgressTimestamp_AssignTimestamp
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_EgressTimestamp_AssignTimestamp(
                  EthTSyn_IntPortIdxType             PortIdx,
                  uint8                              MsgType,
  ETHTSYN_P2CONST(EthTSyn_EgressTimestampHandleType) EgressTimestampHandlePtr)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the message type and assign the timestamp to the corresponding state machine. */
  switch(MsgType)
  {
#if (ETHTSYN_MASTER_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_SYNC:
    {
      const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
      ETHTSYN_CONSTP2VAR(EthTSyn_SyncSendSmType) syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);
      EthTSyn_GlobalTimestampType timeStampGlobal;
# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
      EthTSyn_TimediffType timeDiffEgressAndRefSync = 0;
# endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

      timeStampGlobal = EgressTimestampHandlePtr->GlobalTimestamp;
      syncSendSmPtr->FollowUpPreciseOriginTimestampMgmt.State |= ETHTSYN_TIMESTAMP_STATE_AVAILABLE_FLAG_VALID_MASK;    /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
      /* HW-Timestamping */
      if(EthTSyn_Util_TimestampMinusTimestamp(&EgressTimestampHandlePtr->EgressTimestamp,
          &EgressTimestampHandlePtr->SyncRefTimestamp, &timeDiffEgressAndRefSync) == E_OK)                             /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
      {
        if(EthTSyn_Util_TimestampPlusTimediff(&timeStampGlobal, &timeDiffEgressAndRefSync) == E_OK)                    /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
        {
          syncSendSmPtr->FollowUpPreciseOriginTimestampMgmt.State |= ETHTSYN_TIMESTAMP_STATE_AVAILABLE_MASK;           /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
        }
      }
# else
      /* SW-Timestamping */
      syncSendSmPtr->FollowUpPreciseOriginTimestampMgmt.State |= ETHTSYN_TIMESTAMP_STATE_AVAILABLE_MASK;               /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
# endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */
      syncSendSmPtr->FollowUpPreciseOriginTimestampMgmt.Timestamp = timeStampGlobal;                                   /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */

      break;
    }
#endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */

#if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_PDELAY_REQ:
    {
      const EthTSyn_PdelayConfigIdxOfPortType pdelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
      const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pdelayInitiatorIdx =
          EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pdelayCfgIdx);
      const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pdelayReqSmIdx =
          EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pdelayInitiatorIdx);
      ETHTSYN_CONSTP2VAR(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pdelayReqSmIdx);

      pDelayReqSmPtr->PdelayReq.EgressTimestampMgmt.State =
          ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_AVAILABLE;                                                        /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
      /* HW-Timestamping */
      pDelayReqSmPtr->PdelayReq.EgressTimestampMgmt.Timestamp = EgressTimestampHandlePtr->EgressTimestamp;             /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
# else
      /* SW-Timestamping */
      pDelayReqSmPtr->PdelayReq.EgressTimestampMgmt.Timestamp =
          EthTSyn_Util_RawTimeToTimestamp(EgressTimestampHandlePtr->RawTimestamp);                                     /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
# endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

      break;
    }
#endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

#if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_PDELAY_RESP:
    {
      const EthTSyn_PdelayConfigIdxOfPortType pdelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
      const EthTSyn_PdelayResponderIdxOfPdelayConfigType pdelayResponderIdx =
          EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pdelayCfgIdx);
      const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pdelayRespSmIdx =
          EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pdelayResponderIdx);
      ETHTSYN_CONSTP2VAR(EthTSyn_PdelayRespSmType) pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pdelayRespSmIdx);

      pDelayRespSmPtr->PdelayResp.EgressTimestampMgmt.State =
        ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_AVAILABLE;                                                          /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
      /* HW-Timestamping */
      pDelayRespSmPtr->PdelayResp.EgressTimestampMgmt.Timestamp = EgressTimestampHandlePtr->EgressTimestamp;           /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
# else
      /* SW-Timestamping */
      /* #20 For Pdelay response and SW-Timestamping: Handle possible timestamp overflow. */
      pDelayRespSmPtr->PdelayResp.EgressTimestampMgmt.Timestamp = EthTSyn_Util_CheckAndHandleRawTimestampOverflow(
          &pDelayRespSmPtr->PdelayReq.IngressTimestampMgmt.Timestamp, EgressTimestampHandlePtr->RawTimestamp);         /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */ /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
# endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

      break;
    }
#endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

  default:
    {
      /* Nothing to do here. */
      break;
    }
  }
} /* EthTSyn_EgressTimestamp_AssignTimestamp() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_TxConf_GetTxPortAndMsgType
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_TxConf_GetTxPortAndMsgType(
                EthTSyn_IntCtrlIdxType  EthTSynCtrlIdx,
                uint8                   TxBufIdx,
  ETHTSYN_P2VAR(EthTSyn_IntPortIdxType) PortIdxPtr,
  ETHTSYN_P2VAR(uint8)                  MsgTypePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_PortIndIterType portIndIter;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all Ports of the EthTSyn controller. */
  for(portIndIter = EthTSyn_GetPortIndStartIdxOfCtrl(EthTSynCtrlIdx);
      portIndIter < EthTSyn_GetPortIndEndIdxOfCtrl(EthTSynCtrlIdx);
      portIndIter++)
  {
    const EthTSyn_PortIndType portIdx = EthTSyn_GetPortInd(portIndIter);
    uint8 msgType = ETHTSYN_MSG_TYPE_INVALID;

    /* #100 Check if any message was transmitted on the current port using the given Tx-Buffer. */
#if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
    if(EthTSyn_Util_IsPdelayInitiator(portIdx) == TRUE)
    {
      const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(portIdx);
      const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
        EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
      const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
        EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
      ETHTSYN_CONSTP2CONST(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);

      if(pDelayReqSmPtr->TxBuf.Index == TxBufIdx)
      {
        /* Port and message type found */
        msgType = ETHTSYN_MSG_TYPE_PDELAY_REQ;
      }
    }
#endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

#if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
    if(EthTSyn_Util_IsPdelayResponder(portIdx) == TRUE)
    {
      const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(portIdx);
      const EthTSyn_PdelayResponderIdxOfPdelayConfigType pDelayResponderIdx =
        EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pDelayCfgIdx);
      const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pDelayRespSmIdx =
        EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pDelayResponderIdx);
      ETHTSYN_CONSTP2CONST(EthTSyn_PdelayRespSmType) pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);

      if(pDelayRespSmPtr->TxBuf.Index == TxBufIdx)
      {
        msgType = ETHTSYN_MSG_TYPE_PDELAY_RESP;
      }
    }
#endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

#if (ETHTSYN_MASTER_SUPPORT == STD_ON)
    if(EthTSyn_IsMasterPortUsedOfPort(portIdx) == TRUE)
    {
      const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(portIdx);
      ETHTSYN_CONSTP2VAR(EthTSyn_SyncSendSmType) syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);

      if(syncSendSmPtr->SyncTxBuf.Index == TxBufIdx)
      {
        msgType = ETHTSYN_MSG_TYPE_SYNC;
      }
      else if(syncSendSmPtr->FollowUpTxBuf.Index == TxBufIdx)
      {
        msgType = ETHTSYN_MSG_TYPE_FOLLOW_UP;
      }
      else
      {
        /* Nothing to do here. */
      }
    }
#endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */

    if(msgType != ETHTSYN_MSG_TYPE_INVALID)
    {
      /* #20 Port and message type found. Set out parameters and stop iteration of Ports. */
      *PortIdxPtr = portIdx; /* SBSW_ETHTSYN_VALID_API_POINTER */
      *MsgTypePtr = msgType; /* SBSW_ETHTSYN_VALID_API_POINTER */
      retVal = E_OK;
      break;
    }
  } /* END: Iteration of Ports for the given Controller */

  return retVal;
} /* EthTSyn_TxConf_GetTxPortAndMsgType() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_TxConf_IsEgressTimestampRequired
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_TxConf_IsEgressTimestampRequired(
  EthTSyn_IntPortIdxType PortIdx,
  uint8                  MsgType)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean egressTimestampRequired = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check message type. */
  switch(MsgType)
  {
#if (ETHTSYN_MASTER_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_SYNC:
    /* #20 Sync message. Check if egress timestamp is required. */
    {
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
      const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
      ETHTSYN_CONSTP2VAR(EthTSyn_SyncSendSmType) syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);
      if ((syncSendSmPtr->FollowUpPreciseOriginTimestampMgmt.State &
        ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_WAITING_FOR_TIMESTAMP) != 0)
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */
      {
        egressTimestampRequired = TRUE;
      }

      break;
    }
#endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */

#if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF)
  case ETHTSYN_MSG_TYPE_PDELAY_REQ:
  case ETHTSYN_MSG_TYPE_PDELAY_RESP:
    {
      /* #30 Pdelay_Req || Pdelay_Resp. Egress timestamp required (no Switch Timestamping). */
      egressTimestampRequired = TRUE;
      break;
    }
#endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF) */

  default:
    {
      /* Nothing to do here. */
      break;
    }
  }

#if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF)
  ETHTSYN_DUMMY_STATEMENT(PortIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF) */

  return egressTimestampRequired;
} /* EthTSyn_TxConf_IsEgressTimestampRequired() */

/**********************************************************************************************************************
 *  EthTSyn_TxConf_ProcessTxConfirmation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TxConf_ProcessTxConfirmation(
  EthTSyn_IntPortIdxType PortIdx,
  uint8                  MsgType)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Perform required actions for the message type. */
  switch(MsgType)
  {
#if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_PDELAY_REQ:
    {
      const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
      const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
          EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
      const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
          EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);

      EthTSyn_PdelayReqSmPtrType pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);

      pDelayReqSmPtr->TxBuf.Index = ETHTSYN_INV_BUF_IDX;                                                               /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
      pDelayReqSmPtr->TxConfirmationPending--;                                                                         /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */

      break;
    }
#endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

#if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_PDELAY_RESP:
    {
      const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
      const EthTSyn_PdelayResponderIdxOfPdelayConfigType pDelayResponderIdx =
          EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pDelayCfgIdx);
      const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pDelayRespSmIdx =
          EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pDelayResponderIdx);

      EthTSyn_PdelayRespSmPtrType pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);

      pDelayRespSmPtr->TxBuf.Index = ETHTSYN_INV_BUF_IDX;                                                              /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
      pDelayRespSmPtr->TxConfirmationPending--;                                                                        /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */

      break;
    }
#endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

#if (ETHTSYN_MASTER_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_SYNC:
    {
      EthTSyn_TxConf_ProcessSyncTxConfirmation(PortIdx);
      break;
    }

  case ETHTSYN_MSG_TYPE_FOLLOW_UP:
    {
      EthTSyn_TxConf_ProcessFollowUpTxConfirmation(PortIdx);
      break;
    }
#endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */

  default:
    {
      /* Nothing to do here. */
      break;
    }
  }
} /* EthTSyn_TxConf_ProcessTxConfirmation() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

#if (ETHTSYN_MASTER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_TxConf_ProcessSyncTxConfirmation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TxConf_ProcessSyncTxConfirmation(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
  EthTSyn_SyncSendSmPtrType syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
  const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
  ETHTSYN_CONSTP2VAR(EthTSyn_TimeDomainStateType) timeDomainStatePtr = EthTSyn_GetAddrTimeDomainState(timeDomainIdx);
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

  /* ----- Implementation ----------------------------------------------- */
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
  if(timeDomainStatePtr->SlavePortIdx < EthTSyn_GetSizeOfSlavePort())
  {
    EthTSyn_SiteSyncSyncSmPtrType siteSyncSyncSmPtr = EthTSyn_GetAddrSiteSyncSyncSm(timeDomainIdx);

    /* #10 Handle site sync sync state machine if applicable. */
    syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_SSS_WAIT_FUP;                                                        /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
    if(siteSyncSyncSmPtr->TxConfirmationPending > 0)
    {
      (siteSyncSyncSmPtr->TxConfirmationPending)--;                                                                    /* SBSW_ETHTSYN_CSL03 */
      if(siteSyncSyncSmPtr->TxConfirmationPending == 0)
      {
        siteSyncSyncSmPtr->State = ETHTSYN_S_SSS_SM_PENDING;                                                           /* SBSW_ETHTSYN_CSL03 */
      }
    }
  }
  else
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
  {
    (syncSendSmPtr->TxConfirmationPending)--;                                                                          /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */

    /* #20 Handle Sync Sent Callback. */
    EthTSyn_TxConf_HandleSyncSentCallback(PortIdx);
  }

  /* #30 TxBuffer index of Sync message not required anymore -> invalidate it. */
  syncSendSmPtr->SyncTxBuf.Index = ETHTSYN_INV_BUF_IDX;                                                                /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
} /* EthTSyn_TxConf_ProcessSyncTxConfirmation() */

/**********************************************************************************************************************
 *  EthTSyn_TxConf_ProcessFollowUpTxConfirmation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TxConf_ProcessFollowUpTxConfirmation(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
  EthTSyn_SyncSendSmPtrType syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
  const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
  ETHTSYN_CONSTP2VAR(EthTSyn_TimeDomainStateType) timeDomainStatePtr = EthTSyn_GetAddrTimeDomainState(timeDomainIdx);
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

    /* ----- Implementation ----------------------------------------------- */
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
  if(timeDomainStatePtr->SlavePortIdx < EthTSyn_GetSizeOfSlavePort())
  {
    EthTSyn_SiteSyncSyncSmPtrType siteSyncSyncSmPtr = EthTSyn_GetAddrSiteSyncSyncSm(timeDomainIdx);
    /* #10 Handle site sync sync state machine if applicable. */
    syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_SSS_PENDING;                                                         /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
    if(siteSyncSyncSmPtr->TxConfirmationPending > 0)
    {
      siteSyncSyncSmPtr->TxConfirmationPending--;                                                                      /* SBSW_ETHTSYN_CSL03 */
      if(siteSyncSyncSmPtr->TxConfirmationPending == 0)
      {
        siteSyncSyncSmPtr->State = ETHTSYN_S_SSS_SM_PENDING;                                                           /* SBSW_ETHTSYN_CSL03 */
      }
    }
  }
  else
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
  {
    /* #20 Handle FollowUp sent callback. */
    EthTSyn_TxConf_HandleFollowUpSentCallback(PortIdx);
  }

  /* #30 TxBuffer index of FollowUp message not required anymore -> invalidate it. */
  syncSendSmPtr->FollowUpTxBuf.Index = ETHTSYN_INV_BUF_IDX;                                                            /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
} /* EthTSyn_TxConf_ProcessFollowUpTxConfirmation() */

/**********************************************************************************************************************
 *  EthTSyn_TxConf_HandleSyncSentCallback
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TxConf_HandleSyncSentCallback(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Sync Sent Callback is configured. */
  if(EthTSyn_GetSyncSentCbkPtrOfMasterPort(masterPortIdx) != NULL_PTR)
  {
    EthTSyn_SyncSendSmPtrType syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);
    /* #100 Call Sync Sent Callback. */
    ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) comMsgPtr =
      (ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType))syncSendSmPtr->SyncTxBuf.Address; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */
    ETHTSYN_P2CONST(EthTSyn_SyncMsgType) syncPtr =
      (ETHTSYN_P2CONST(EthTSyn_SyncMsgType))&comMsgPtr[ETHTSYN_HDR_COM_LENGTH]; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */

    EthTSyn_GetSyncSentCbkPtrOfMasterPort(masterPortIdx)(PortIdx, comMsgPtr, syncPtr);                                 /* SBSW_ETHTSYN_FUNCTION_PTR_CALL */

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
    /* #101 TxBuffer address of Sync message not required anymore -> invalidate it. */
    syncSendSmPtr->SyncTxBuf.Address = NULL_PTR;                                                                       /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */
  }
} /* EthTSyn_TxConf_HandleSyncSentCallback() */

/**********************************************************************************************************************
 *  EthTSyn_TxConf_HandleFollowUpSentCallback
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_TxConf_HandleFollowUpSentCallback(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if FollowUp Sent Callback is configured. */
  if(EthTSyn_GetFollowUpSentCbkPtrOfMasterPort(masterPortIdx) != NULL_PTR)
  {
    EthTSyn_SyncSendSmPtrType syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);
    /* #100 Call FollowUp Sent Callback. */
    /* PRQA S 0310 4 */ /* MD_EthTSyn_0310_MsgStruct */
    ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) comMsgPtr =
      (ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType))syncSendSmPtr->FollowUpTxBuf.Address;
    ETHTSYN_P2CONST(EthTSyn_FollowUpMsgType) followUpPtr =
      (ETHTSYN_P2CONST(EthTSyn_FollowUpMsgType))&comMsgPtr[ETHTSYN_HDR_COM_LENGTH];

    EthTSyn_GetFollowUpSentCbkPtrOfMasterPort(masterPortIdx)(PortIdx, comMsgPtr, followUpPtr);                         /* SBSW_ETHTSYN_FUNCTION_PTR_CALL */

    /* #101 TxBuffer address of FollowUp message not required anymore -> invalidate it. */
    syncSendSmPtr->FollowUpTxBuf.Address = NULL_PTR;                                                                   /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
  }
} /* EthTSyn_TxConf_HandleFollowUpSentCallback */
#endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_RxInd_ProcRcvdMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_RxInd_ProcRcvdMsg(
                  EthTSyn_IntCtrlIdxType EthTSynCtrlIdx,
                  uint16                 LenByte,
  ETHTSYN_P2CONST(uint8)                 DataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  EthTSyn_IntPortIdxType portIdx = EthTSyn_GetSizeOfPort();
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) comMsgPtr = (ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType))DataPtr; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Perform basic message checks and get EthTSyn PortIdx. */
  errorId = EthTSyn_RxInd_PerformBasicMsgChecksAndGetPort(EthTSynCtrlIdx, LenByte, DataPtr, &portIdx);                 /* SBSW_ETHTSYN_PASSING_API_POINTER */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
  if(errorId == ETHTSYN_E_NO_ERROR)
  {
    /* Port found -> continue processing of the message */
    /* #20 Get message type and process the message if applicable. */
    switch(ETHTSYN_HDR_COM_MSG_TYPE(comMsgPtr->TransSpecific_MessageType))
    {
# if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
    case ETHTSYN_MSG_TYPE_PDELAY_REQ:
      {
        EthTSyn_Pdelay_ProcRcvdReqMsg(comMsgPtr, portIdx);                                                             /* SBSW_ETHTSYN_PASSING_API_POINTER */
        break;
      }
# endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
    case ETHTSYN_MSG_TYPE_PDELAY_RESP:
      {
        EthTSyn_Pdelay_ProcRcvdRespMsg(comMsgPtr, portIdx);                                                            /* SBSW_ETHTSYN_PASSING_API_POINTER */
        break;
      }

    case ETHTSYN_MSG_TYPE_PDELAY_RES_FOLLOW_UP:
      {
        EthTSyn_Pdelay_ProcRcvdRespFupMsg(comMsgPtr, portIdx);                                                         /* SBSW_ETHTSYN_PASSING_API_POINTER */
        break;
      }
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

    case ETHTSYN_MSG_TYPE_SYNC:
      {
        uint64 srcClockIdentity = EthTSyn_Util_TransformClockIdentityToUint64(comMsgPtr->SourceClockIdentity);         /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
        if (EthTSyn_UtilRx_SyncPortRoleCheckWithMasterSlaveConflictDetection(portIdx, srcClockIdentity) == TRUE)
        {
          EthTSyn_SlaveRx_ProcRcvdSyncMsg(comMsgPtr, portIdx); /* SBSW_ETHTSYN_PASSING_API_POINTER */
        }
# else
        (void)EthTSyn_UtilRx_SyncPortRoleCheckWithMasterSlaveConflictDetection(portIdx, srcClockIdentity);
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

        break;
      }

# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
    case ETHTSYN_MSG_TYPE_FOLLOW_UP:
      {
        EthTSyn_SlaveRx_ProcRcvdFupMsg(comMsgPtr, portIdx);                                                            /* SBSW_ETHTSYN_PASSING_API_POINTER */
        break;
      }
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

# if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
    case ETHTSYN_MSG_TYPE_ANNOUNCE:
      {
        EthTSyn_Slave_ProcRcvdAnnounceMsg(comMsgPtr, portIdx);                                                         /* SBSW_ETHTSYN_PASSING_API_POINTER */
        break;
      }
# endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */

    default:
      {
        /* Nothing to do here. */
        break;
      }
    }
  }

  return errorId;
} /* EthTSyn_RxInd_ProcRcvdMsg() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

/**********************************************************************************************************************
 *  EthTSyn_RxInd_PerformBasicMsgChecksAndGetPort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_RxInd_PerformBasicMsgChecksAndGetPort(
                  EthTSyn_IntCtrlIdxType  EthTSynCtrlIdx,
                  uint16                  LenByte,
  ETHTSYN_P2CONST(uint8)                  DataPtr,
    ETHTSYN_P2VAR(EthTSyn_IntPortIdxType) PortIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Perform general message checks. */
  errorId = EthTSyn_UtilRx_CheckMessageGeneral(DataPtr, LenByte);                                                      /* SBSW_ETHTSYN_PASSING_API_POINTER */
  if(errorId == ETHTSYN_E_NO_ERROR)
  {
    ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) comMsgPtr = (ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType))DataPtr; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */
    /* #20 General message checks passed. Check message type and length. */
    errorId = EthTSyn_UtilRx_CheckMessageTypeAndLength(comMsgPtr, LenByte);                                            /* SBSW_ETHTSYN_POINTER_VARIABLE */
    if(errorId == ETHTSYN_E_NO_ERROR)
    {
      EthTSyn_PortIndIterType portIndIter;
      errorId = ETHTSYN_E_NO_PORT_FOUND;
      /* #30 Valid message type and length. Get the EthTSyn Port. */
      for(portIndIter = EthTSyn_GetPortIndStartIdxOfCtrl(EthTSynCtrlIdx);
          portIndIter < EthTSyn_GetPortIndEndIdxOfCtrl(EthTSynCtrlIdx);
          portIndIter++)
      {
        const EthTSyn_PortIndType tmpPort = EthTSyn_GetPortInd(portIndIter);
        const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(tmpPort);
        if((EthTSyn_GetIdOfTimeDomain(timeDomainIdx) == comMsgPtr->DomainNumber))
        {
          /* #300 EthTSyn Port found. */
          *PortIdxPtr = tmpPort;                                                                                       /* SBSW_ETHTSYN_VALID_API_POINTER */
          errorId = ETHTSYN_E_NO_ERROR;
          break;
        }
      }
    }
  }

  return errorId;
} /* EthTSyn_RxInd_PerformBasicMsgChecksAndGetPort() */
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_RxIndication
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
/* PRQA S 3673 7 */ /* MD_EthTSyn_3673_Ar */
FUNC(void, ETHTSYN_CODE) EthTSyn_RxIndication(
                uint8                  CtrlIdx,
                Eth_FrameType          FrameType,
                boolean                IsBroadcast,
                EthTSyn_PhyAddrPtrType PhysAddrPtr,
  ETHTSYN_P2VAR(uint8)                 DataPtr,
                uint16                 LenByte)
{
  /* ----- Local Variables ---------------------------------------------- */
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  uint8 errorId;
#else
  uint8 errorId = ETHTSYN_E_NO_ERROR;
#endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters. */
  if (EthTSyn_State == ETHTSYN_STATE_UNINIT)
  {
    errorId = ETHTSYN_E_NOT_INITIALIZED;
  }
  else if ((DataPtr == NULL_PTR) || (PhysAddrPtr == NULL_PTR))
  {
    errorId = ETHTSYN_E_PARAM_POINTER;
  }
  else if (FrameType != ETHTSYN_FRAME_TYPE)
  {
    errorId = ETHTSYN_E_FRAME_TYPE;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Get and verify EthTSyn controller. */
    const EthTSyn_IntCtrlIdxType ethTSynCtrlIdx = EthTSyn_Util_GetEthTSynCtrlFromEthIfCtrl(CtrlIdx);

    if(ethTSynCtrlIdx < EthTSyn_GetSizeOfCtrl())
    {
      /* #30 Verify link state. */
      if(EthTSyn_GetCtrlState(ethTSynCtrlIdx).TrcvLinkState == ETHTRCV_LINK_STATE_ACTIVE)
      {
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
        /* #40 Switch management enabled. Pass the received Frame to the Switch management. */
        errorId = EthTSyn_SwtMgmtRx_HandleMessageReception(ethTSynCtrlIdx, DataPtr, LenByte);                          /* SBSW_ETHTSYN_PASSING_API_POINTER */
#else
        /* #50 Switch management disabled. Handle message reception. */
        errorId = EthTSyn_RxInd_ProcRcvdMsg(ethTSynCtrlIdx, LenByte, DataPtr);                                         /* SBSW_ETHTSYN_PASSING_API_POINTER */
#endif /* ETHTSYN_SWT_MGMT_SUPPORT */
      }
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
      else
      {
        errorId = ETHTSYN_E_TRCV_DOWN;
      }
#endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */
    }
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
    else
    {
      errorId = ETHTSYN_E_CTRL_IDX;
    }
#endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */
  }

#if (ETHTSYN_DEV_ERROR_DETECT == STD_OFF)
  ETHTSYN_DUMMY_STATEMENT(FrameType); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETHTSYN_DUMMY_STATEMENT(PhysAddrPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_OFF) */
  ETHTSYN_DUMMY_STATEMENT(IsBroadcast); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  /* ----- Development Error Report ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #60 Report error to default error tracer (DET) if any occurred. */
  if (errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, ETHTSYN_SID_RX_INDICATION, errorId);
  }
#else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif

} /* EthTSyn_RxIndication() */ /* PRQA S 6060, 6080 */ /* MD_MSR_STPAR, MD_MSR_STMIF */

#if (ETHTSYN_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_GetVersionInfo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_GetVersionInfo(
  ETHTSYN_P2VAR(Std_VersionInfoType) VersionInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHTSYN_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check VersionInfoPtr for NULL pointer. note: no uninit check is performed. */
  if(VersionInfoPtr == NULL_PTR)
  {
    errorId = ETHTSYN_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation --------------------------------------------- */
    /* #20 Set version info with corresponding macros from component header. */
    VersionInfoPtr->vendorID = (uint16)ETHTSYN_VENDOR_ID;                                                              /* SBSW_ETHTSYN_GETVERSION_PARAM */
    VersionInfoPtr->moduleID = (uint16)ETHTSYN_MODULE_ID;                                                              /* SBSW_ETHTSYN_GETVERSION_PARAM */
    VersionInfoPtr->sw_major_version = (uint8)ETHTSYN_SW_MAJOR_VERSION;                                                /* SBSW_ETHTSYN_GETVERSION_PARAM */
    VersionInfoPtr->sw_minor_version = (uint8)ETHTSYN_SW_MINOR_VERSION;                                                /* SBSW_ETHTSYN_GETVERSION_PARAM */
    VersionInfoPtr->sw_patch_version = (uint8)ETHTSYN_SW_PATCH_VERSION;                                                /* SBSW_ETHTSYN_GETVERSION_PARAM */
  }

  /* ----- Development Error Report ------------------------------------- */
# if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #30 Report error to default error tracer (DET) if any occurred. */
  if(errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, ETHTSYN_SID_GET_VERSION_INFO, errorId);
  }
# else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif
} /* EthTSyn_GetVersionInfo() */
#endif /* (ETHTSYN_VERSION_INFO_API == STD_ON) */


/**********************************************************************************************************************
 *  EthTSyn_MainFunction
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
FUNC(void, ETHTSYN_CODE) EthTSyn_MainFunction(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHTSYN_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check initialization state of component. */
  if(EthTSyn_State == ETHTSYN_STATE_UNINIT)
  {
    errorId = ETHTSYN_E_NOT_INITIALIZED;
  }
  else
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthTSyn_TimeDomainIterType timeDomainIter;

    /* #20 Iterate all TimeDomains. */
    for(timeDomainIter = 0; timeDomainIter < EthTSyn_GetSizeOfTimeDomain(); timeDomainIter++)
    {
      /* #200 Handle cyclic tasks for Master-Ports. */
#if (ETHTSYN_MASTER_SUPPORT == STD_ON)
      EthTSyn_Master_HandleCyclicTasks(timeDomainIter);
#endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */

      /* #201 Handle cyclic tasks for Slave-Ports. */
#if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
      EthTSyn_Slave_HandleCyclicTasks(timeDomainIter);
#endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

      /* #202 Process site sync sync state machine if applicable. */
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
      if(EthTSyn_IsSlavePortUsedOfTimeDomain(timeDomainIter) == TRUE)
      {
        /* SiteSyncSync state machine */
        EthTSyn_SwtMgmt_ProcessSmSiteSyncSync(timeDomainIter);
      }
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
    } /* END: Iteration of TimeDomains */

    /* #30 Handle cyclic task for Pdelay. */
#if ( (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) || (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) )
    EthTSyn_Pdelay_HandleCyclicTasks();
#endif /* ( (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) || (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) ) */

    /* #40 Handle cycle tasks for switch time sync. */
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
    EthTSyn_SwtTimeSync_HandleCyclicTasks();
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

  }

  /* ----- Development Error Report ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #50 Report error to default error tracer (DET) if any occurred. */
  if(errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, ETHTSYN_SID_MAIN_FUNCTION, errorId);
  }
#else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */

} /* EthTSyn_MainFunction() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_InitMemory
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE)  EthTSyn_InitMemory(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set module state to unitialized. */
  EthTSyn_State = ETHTSYN_STATE_UNINIT;
}

/**********************************************************************************************************************
 *  EthTSyn_Init
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
FUNC(void, ETHTSYN_CODE) EthTSyn_Init(
  P2CONST(EthTSyn_ConfigType, AUTOMATIC, ETHTSYN_INIT_DATA) CfgPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHTSYN_E_NO_ERROR;
  EthTSyn_CtrlIterType ethTSynCtrlIter;

  EthTSyn_ConfigDataPtr = CfgPtr;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters. */
  if(CfgPtr == NULL_PTR)
  {
    errorId = ETHTSYN_E_PARAM_POINTER;
  }
  else
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* ----- Implementation --------------------------------------------- */
    /* #20 Initialize Master sub module. */
#if (ETHTSYN_MASTER_SUPPORT == STD_ON)
    EthTSyn_Master_Init();
#endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */

    /* #30 Initialize Slave sub module. */
#if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
    EthTSyn_Slave_Init();
#endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

    /* #40 Initialize Pdelay sub module. */
    EthTSyn_Pdelay_Init();

    /* #50 Initialize SwtMgmt sub module. */
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
    EthTSyn_SwtMgmt_Init();
    /* #500 Initialize SwtTimeSync sub module. */
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
    EthTSyn_SwtTimeSync_Init();
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

    /* #60 Initialize all EthTSyn controllers. */
    for(ethTSynCtrlIter = 0u; ethTSynCtrlIter < EthTSyn_GetSizeOfCtrl(); ethTSynCtrlIter++)
    {
      EthTSyn_InitCtrl(ethTSynCtrlIter);
    }

    /* #70 Set module state to initialized. */
    EthTSyn_State = ETHTSYN_STATE_INIT;
  }

  /* ----- Development Error Report ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #80 Report error to default error tracer (DET) if any occurred. */
  if(errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, ETHTSYN_SID_INIT, errorId);
  }
#else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */
} /* EthTSyn_Init() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_TrcvLinkStateChg
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
FUNC(void, ETHTSYN_CODE) EthTSyn_TrcvLinkStateChg(
  uint8                 CtrlIdx,
  EthTrcv_LinkStateType TrcvLinkState)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHTSYN_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check initialization state of the component. */
  if(EthTSyn_State == ETHTSYN_STATE_UNINIT)
  {
    errorId = ETHTSYN_E_NOT_INITIALIZED;
  }
  else
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* ----- Implementation --------------------------------------------- */
    /* #20 Get EthTSyn Controller the. */
    const EthTSyn_IntCtrlIdxType ethTSynCtrlIdx = EthTSyn_Util_GetEthTSynCtrlFromEthIfCtrl(CtrlIdx);

    if(ethTSynCtrlIdx < EthTSyn_GetSizeOfCtrl())
    {
      ETHTSYN_CONSTP2VAR(EthTSyn_CtrlStateType) ctrlStatePtr = EthTSyn_GetAddrCtrlState(ethTSynCtrlIdx);

      /* #30 Check the passed transceiver link state. */
      switch(TrcvLinkState)
      {
      case ETHTRCV_LINK_STATE_DOWN:
        {
          /* #300 Handle transceiver link state down. */
          if(ctrlStatePtr->TrcvLinkState == ETHTRCV_LINK_STATE_ACTIVE)
          {
            /* Trcv Link state changed */
            ctrlStatePtr->TrcvLinkState = ETHTRCV_LINK_STATE_DOWN;                                                     /* SBSW_ETHTSYN_CSL01 */

            /* remove multi-cast frame reception */
            (void)EthIf_UpdatePhysAddrFilter(CtrlIdx, EthTSyn_DestinationMac, ETH_REMOVE_FROM_FILTER);                 /* SBSW_ETHTSYN_CONSTANT_ARRAY_AS_POINTER */
            /* set default values as zero */
            EthTSyn_ResetPortsAndPdelayOfCtrl(ethTSynCtrlIdx);
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
            EthTSyn_SwtTimeSync_SwtSyncFrameStop(CtrlIdx);
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
          }

          break;
        }

      case ETHTRCV_LINK_STATE_ACTIVE:
        {
          /* #301 Handle transceiver link state up. */
          if(ctrlStatePtr->TrcvLinkState == ETHTRCV_LINK_STATE_DOWN)
          {
            /* Trcv Link state changed */
            ctrlStatePtr->TrcvLinkState = ETHTRCV_LINK_STATE_ACTIVE;                                                   /* SBSW_ETHTSYN_CSL01 */

            /* Init default values */
            EthTSyn_InitCtrl(ethTSynCtrlIdx);
            EthTSyn_SetLocalClockIdentity(ethTSynCtrlIdx);
            /* add multicast frame reception */
            (void)EthIf_UpdatePhysAddrFilter(CtrlIdx, EthTSyn_DestinationMac, ETH_ADD_TO_FILTER);                      /* SBSW_ETHTSYN_CONSTANT_ARRAY_AS_POINTER */
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
            EthTSyn_SwtTimeSync_SwtSyncFrameStart(CtrlIdx);
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
          }

          break;
        }

      default:
        {
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
          errorId = ETHTSYN_E_PARAM;
#endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */
          break;
        }
      }
    }
    /* No DET for invalid Ctrl Idx, because EthIf calls TrcvLinkStateChg functions for every registered UpperLayer
       and each configured EthIf controller. */
  }

  /* ----- Development Error Report ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report error to default error tracer (DET) if any occurred. */
  if(errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, ETHTSYN_SID_TRCV_LINK_STATE_CHG, errorId);
  }
#else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */
} /* EthTSyn_TrcvLinkStateChg() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_TxConfirmation
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
FUNC(void, ETHTSYN_CODE) EthTSyn_TxConfirmation(
  uint8 CtrlIdx,
  uint8 BufIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHTSYN_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters. */
  if(EthTSyn_State == ETHTSYN_STATE_UNINIT)
  {
    errorId = ETHTSYN_E_NOT_INITIALIZED;
  }
  else
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* ----- Implementation --------------------------------------------- */
    /* #20 Get the corresponding EthTSyn controller */
    const EthTSyn_IntCtrlIdxType ethtsynCtrlIdx = EthTSyn_Util_GetEthTSynCtrlFromEthIfCtrl(CtrlIdx);

    if(ethtsynCtrlIdx < EthTSyn_GetSizeOfCtrl())
    {
      EthTSyn_IntPortIdxType portIdx = EthTSyn_GetSizeOfPort();
      uint8 msgType = ETHTSYN_MSG_TYPE_INVALID;

      /* #30 Get the EthTSyn Port and Message type */
      if(EthTSyn_TxConf_GetTxPortAndMsgType(ethtsynCtrlIdx, BufIdx, &portIdx, &msgType) == E_OK)                       /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
      {
        /* #40 Port and message type found. Check if egress timestamp is required */
        if(EthTSyn_TxConf_IsEgressTimestampRequired(portIdx, msgType) == TRUE)
        {
          /* #400 Handle egress timestamping */
          EthTSyn_HandleEgressTimestamping(portIdx, msgType, BufIdx);
        }

        /* #50 Process TxConfirmation */
        EthTSyn_TxConf_ProcessTxConfirmation(portIdx, msgType);
      }
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
      /* #60 If EthTSyn port and/or message type could not be retrieved, it might be a switch sync frame. Handle it. */
      else
      {
        EthTSyn_SwtTimeSync_SwtSyncFrameTxConfirmation(CtrlIdx, BufIdx);
      }
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
    }
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
    else
    {
      errorId = ETHTSYN_E_CTRL_IDX;
    }
#endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */
  }

  /* ----- Development Error Report ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #70 Report error to default error tracer (DET) if any occurred. */
  if(errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, ETHTSYN_SID_TX_CONFIRMATION, errorId);
  }
#else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */

} /* EthTSyn_TxConfirmation() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SetTransmissionMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_SetTransmissionMode(
  uint8                        CtrlIdx,
  EthTSyn_TransmissionModeType Mode)
{
  /* ------ Local Variables -----------------------------------------------*/
  uint8 errorId = ETHTSYN_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters. */
  if(EthTSyn_State == ETHTSYN_STATE_UNINIT)
  {
    errorId = ETHTSYN_E_NOT_INITIALIZED;
  }
  else if((Mode != ETHTSYN_TX_ON) && (Mode != ETHTSYN_TX_OFF))
  {
    errorId = ETHTSYN_E_PARAM;
  }
  else
#endif /* (ETHTSYN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* ----- Implementation --------------------------------------------- */
    /* #20 Set the transmission mode of the corresponding EthTSyn controller. */
    const EthTSyn_IntCtrlIdxType ethtsynCtrlIdx = EthTSyn_Util_GetEthTSynCtrlFromEthIfCtrl(CtrlIdx);

    if(ethtsynCtrlIdx < EthTSyn_GetSizeOfCtrl())
    {
      (EthTSyn_GetAddrCtrlState(ethtsynCtrlIdx))->TransmissionMode = Mode;                                             /* SBSW_ETHTSYN_CSL01 */
    }
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
    else
    {
      errorId = ETHTSYN_E_CTRL_IDX;
    }
#endif /* (ETHTSYN_DEV_ERROR_REPORT == STD_ON) */
  }

  /* ----- Development Error Report ------------------------------------- */
#if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #30 Report error to default error tracer (DET) if any occurred. */
  if(errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, ETHTSYN_SID_SET_TRANSMISSION_MODE, errorId);
  }
#else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif

} /* EthTSyn_SetTransmissionMode() */ /* PRQA S 2006 */ /* MD_MSR_14.7 */

#define ETHTSYN_STOP_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

/* Justifications for module-specific MISRA deviations:

  MD_EthTSyn_0310_MsgStruct: MISRA rule 11.4 (A cast should not be performed between a pointer to object type and a
                                              different pointer to object type)
                             QAC: Casting to different object pointer type
      Reason:     Casting Rx/Tx buffer pointer to message structure for easier read/write access of message fields.
      Risk:       Alignment/padding of structures depend on platform/compiler. This might lead to access of
                  wrong/invalid Rx/Tx buffer sections.
      Prevention: Covered by code review (4 Byte alignment of message structures is ensured).
  MD_EthTSyn_0310_MsgStructRev: MISRA rule 11.4 (A cast should not be performed between a pointer to object type and a
                                                 different pointer to object type)
                                QAC: Casting to different object pointer type
      Reason:     Casting pointer to message structure or Rx/Tx uint8 pointer to Eth_DataType pointer for call of EthIf
                  APIs
      Risk:       Casting of pointers to uint8 elements without taking alignment into account may result in unaligned
                  memory access exceptions on certain platforms.
      Prevention: It is expected that The buffers passed to the EthTSyn by EthIf are 4 byte aligned.
  MD_EthTSyn_0310_SubType: MISRA rule 11.4 (A cast should not be performed between a pointer to object type and a
                                              different pointer to object type)
                           QAC: Casting to different object pointer type
      Reason:     Casting abstract/general type to sub-type or vice versa.
      Risk:       Wrong data might be accessed when using a different structure.
      Prevention: The common members of the structures are the same (including the order).
  MD_EthTSyn_0310_IpBase: MISRA rule 11.4 (A cast should not be performed between a pointer to object type and a
                                           different pointer to object type)
                          QAC: Casting to different object pointer type
      Reason:     Casting to IpBase_CopyDataType required for copy optimization done by IpBase.
      Risk:       Risk of an unaligned memory access exception on certain platforms.
      Prevention: IpBase implementation ensures that only aligned memory access is performed.
  MD_EthTSyn_0310_ByteAccess: MISRA rule 11.4 (A cast should not be performed between a pointer to object type and a
                                           different pointer to object type)
                              QAC: Casting to different object pointer type
      Reason:     Byte access required to avoid mis-aligned access on specific platforms.
      Risk:       Casting of pointers to uint8 elements without taking alignment into account may result in unaligned
                  memory access exceptions on certain platforms.
      Prevention: Byte access is applied to a local variable of bigger type (e.g. uint16). Therefor the alignment is
                  implicitly ensured.
  MD_EthTSyn_0310_Timestamp: MISRA rule 11.4 (A cast should not be performed between a pointer to object type and a
                                              different pointer to object type)
                             QAC: Casting to different object pointer type
      Reason:     Internal timestamp type is used for unified handling of message timestamps.
      Risk:       Wrong data might be accessed when using a different structure.
      Prevention: The format of the message timestamps is equivalent to the internal timestamp type. Ensured by code
                  review.
  MD_EthTSyn_0310_PortIdent: MISRA rule 11.4 (A cast should not be performed between a pointer to object type and a
                                              different pointer to object type)
                             QAC: Casting to different object pointer type
      Reason:     Internal port identity type is used for unified handling of message port identities.
      Risk:       Wrong data might be accessed when using a different structure.
      Prevention: The format of the message port identities is equivalent to the internal port identity type. Ensured by
                  code review.
  MD_EthTSyn_0310_PathTrace: MISRA rule 11.4 (A cast should not be performed between a pointer to object type and a
                                              different pointer to object type)
                             QAC: Casting to different object pointer type
      Reason:     Double pointer to EthTSyn_ClockIdentityType is used to iterate through the PathTraceSequence of a
                  received announce message.
      Risk:       Possible out of bounds access when iterating through the PathTraceSequence.
      Prevention: Length check is performed beforehand.
  MD_EthTSyn_0311: MISRA rule 11.5 (A cast shall not be performed that removes any const or volatile qualification
                                    from the type addressed by a pointer)
                   QAC: Dangerous pointer cast results in loss of const qualification
      Reason:     Called API expects a P2VAR.
      Risk:       No risk. The object addressed by the pointer parameter is not modified within the called API.
                  The parameters is specified as 'in' parameter by AUTOSAR.
      Prevention: Covered by code review.
  MD_EthTSyn_3673_Pre: MISRA rule 16.7 (A pointer parameter in a function prototype should be declared as pointer to
                                        const if the pointer is not used to modify the addressed object)
                       QAC: The object addressed by the pointer parameter '%s' is not modified and so the pointer could
                            be of type 'pointer to const'
      Reason:     The parameter is of type P2VAR because its modification depends on preprocessor variant
      Risk:       No risk.
      Prevention: Covered by code review
  MD_EthTSyn_3673_Ar: MISRA rule 16.7 (A pointer parameter in a function prototype should be declared as pointer to
                                       const if the pointer is not used to modify the addressed object)
                      QAC: The object addressed by the pointer parameter '%s' is not modified and so the pointer could
                           be of type 'pointer to const'
      Reason:     The parameter is of type P2VAR due to AUTOSAR specification
      Risk:       Unnoticed/unwilling modification of in-parameter.
      Prevention: Covered by code review
  MD_EthTSyn_3415_CslReadOnly: MISRA rule 12.4 (The right hand operand of a logical && or || operator shall not contain
                                                side effects)
                               QAC: The right hand operand of '&&' or '||' has side effects
     Reason:     No side effects possible because the (inline) function only wraps a read-only access to a 
                 variable/constant. Used to justify read-only access to constants/variables via inline function
                 generated by the ComStackLib (CSL). (e.g.: EthTSyn_Get*())
     Risk:       Right hand operand does not influence the program/control flow therefor the lazy evaluation applied
                 by the compiler has no effect.
     Prevention: None.
  MD_EthTSyn_3415_ReadOnly: MISRA rule 12.4 (The right hand operand of a logical && or || shall not contain side
                                             effects)
                            QAC: The right hand operand of '&&' or '||' has side effects
      Reason:     No side effect possible because the function does not modify any variable.
                  It is intended that this function is only called if the first check failed (||) / succeeded (&&).
      Risk:       No risk. No assignments are done in conditional statements
      Prevention: Covered by code review.
  MD_EthTSyn_2003: MISRA rule 15.2 (An unconditional break statement shall terminate every non-empty switch clause)
                   QAC: The preceding non-empty 'case' or 'default' clause does not end with an explicit 'break' or
                        'return' statement.
      Reason:    Fall through case to reuse code parts common among different cases.
      Risk:      Right hand operand does not influence the program/control flow therefor the lazy evaluation applied
                 by the compiler has no effect.
     Prevention: None.
  MD_EthTSyn_0883: MISRA rule 19.15: Include file code is not protected against repeated inclusion
      Reason:     Wrong MISRA Warning. Standard Include Guard is present.
      Risk:       No risk.
      Prevention: Covered by code review.
  MD_EthTSyn_3219: MISRA rule 14.1 (There shall be no unreachable code).
                   QAC: Static function '%s()' is not used within this translation unit.
      Reason:     Some internal functions are used within different sub-modules of the EthTSyn. However they might not
                  be used in every sub-module.
      Risk:       Functions which are superfluous in a specific configuration may remain undetected which leads to a
                  small resource overhead.
      Prevention: Covered by code review.
  MD_EthTSyn_3355: MISRA rule 13.7 (Boolean operations whose results are invariant shall not be permitted)
                   QAC: The result of this logical operation is always 'true'.
      Reason:     This logical operation is only 'always true' for specific preprocessor variants.
      Risk:       Possible programming error might not be detected.
      Prevention: Covered by runtime tests in different variants.
  MD_EthTSyn_3356: MISRA rule 13.7 (Boolean operations whose results are invariant shall not be permitted)
                   QAC: The result of this logical operation is always 'false'.
      Reason:     This logical operation is only 'always false' for specific preprocessor variants.
      Risk:       Possible programming error might not be detected.
      Prevention: Covered by runtime tests in different variants.
  MD_EthTSyn_6050_CslAccess: MISRA rule N/A
                             QAC:  Number of distinct function calls defined by HIS shall be in range 0..7
      Reason:     Number of distinct function calls is only too high due to trivial inline functions for accessing the
                  ComStackLib data. Complexity of the function does not increase compared to ComStackLib access via
                  macros.
      Risk:       High complexity of functions.
      Prevention: Design and code review + clearly structured and commented code.
  MD_EthTSyn_0779_CslAccessName: MIRA rule 5.1 (Identifiers (internal and external) shall not rely on the significance
                                                of more than 31 characters)
                                 QAC: [U] Identifier does not differ from other identifier(s) (e.g. '%s') within the
                                      specified number of significant characters
      Reason:     The identifiers are generated by the ComStackLib based on the names of the underlying data.
      Risk:       A compiler might not correctly pre-process the software what might result in incorrect code.
      Prevention: Each delivery is integrated and tested on the real target system. In addition, preprocessors and
                  compilers used in current MICROSAR projects are not expected to suffer from this (historic)
                  limitation. Compiler selection and validation is done by ECU supplier.
*/

/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_ETHTSYN_CSL01
    \DESCRIPTION      Access of array elements with index generated by ComStackLib.
    \COUNTERMEASURE   \N Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_ETHTSYN_CSL02
    \DESCRIPTION      Access of array element with index checked against size of different array.
                      (Arrays Xyz[] and XyzDyn[] depend on ComStackLib size relation.)
    \COUNTERMEASURE   \N Qualified use-case CSL02 of ComStackLib.

  \ID SBSW_ETHTSYN_CSL02_PTR
    \DESCRIPTION      Pointer is generated by address of array element with index checked against size of different
                      array. (Arrays Xyz[] and XyzDyn[] depend on ComStackLib size relation.)
    \COUNTERMEASURE   \N Qualified use-case CSL02 of ComStackLib.

  \ID SBSW_ETHTSYN_CSL03
    \DESCRIPTION      Access of array element with index modeled by indirection.
    \COUNTERMEASURE   \N Qualified use-case CSL03 of ComStackLib.

  \ID SBSW_ETHTSYN_CSL02_03
    \DESCRIPTION      Access of array element with index modeled by indirection to different array.
    \COUNTERMEASURE   \N Combination of qualified use-cases CSL02 and CSL03 of ComStackLib.

  \ID SBSW_ETHTSYN_GETVERSION_PARAM
    \DESCRIPTION      The function EthTSyn_GetVersionInfo writes to the objected referenced by parameter VersionInfoPtr
    \COUNTERMEASURE   \N The caller ensures that the pointer passed to the parameter VersionInfoPtr is valid

  \ID SBSW_ETHTSYN_ARRAY_SIZE
    \DESCRIPTION      Access of array element with index is not checked for validity.
    \COUNTERMEASURE   \N The array has a fixed size. The used indices are constant and smaller than the array size.

  \ID SBSW_ETHTSYN_REFERENCE_OF_VARIABLE
    \DESCRIPTION      Pointer to variable is passed as function argument.
    \COUNTERMEASURE   \N Pointer is generated by referencing a variable by the address operator.

  \ID SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT
    \DESCRIPTION      Pointer is passed as function argument.
    \COUNTERMEASURE   \N Pointer is generated by referencing a member of a struct/pointer to struct variable.

  \ID SBSW_ETHTSYN_POINTER_VARIABLE
    \DESCRIPTION      Pointer variable is passed as function argument.
    \COUNTERMEASURE   \N Pointer variable is initialized as NULL_PTR and set to reference a variable by address operator
                         if required.

  \ID SBSW_ETHTSYN_POINTER_VARIABLE_WRITE
    \DESCRIPTION      Pointer write access to pointer variable.
    \COUNTERMEASURE   \R The pointer variable is either NULL_PTR or set to reference a variable by address operator.
                         Setting the pointer to a valid value might be done by sub-function as value.
                         The pointer is valid either when it is set to a value != NULL_PTR or in case of sub-function
                         the sub-function defines the condition for the validity of the pointer (out parameter).

  \ID SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE
    \DESCRIPTION      Pointer variable (pointing to tx buffer) is passed as function argument.
    \COUNTERMEASURE   \N Pointer variable is initialized with pointer to the matching location within the ethernet
                         transmission buffer. The pointer to the ethernet transmission buffer is set by the EthIf.

  \ID SBSW_ETHTSYN_WRITE_TO_TX_BUFFER
    \DESCRIPTION      Pointer write access to ethernet transmission buffer.
    \COUNTERMEASURE   \N Write access to the ethernet transmission buffer with or without former pointer structure cast.
                         The Pointer to the tx buffer is set by the EthIf which ensures a validity.

  \ID SBSW_ETHTSYN_CONSTANT_ARRAY_AS_POINTER
    \DESCRIPTION      Constant array is passed as pointer argument.
    \COUNTERMEASURE   \N Pointer is generated by using a constant array.

  \ID SBSW_ETHTSYN_VARIABLE_ARRAY_AS_POINTER
    \DESCRIPTION      Variable array is passed as pointer argument.
    \COUNTERMEASURE   \N Pointer is generated by using a variable array.

  \ID SBSW_ETHTSYN_STRUCT_ELEMENT_ARRAY_AS_POINTER
    \DESCRIPTION      Struct member array is passed as pointer argument.
    \COUNTERMEASURE   \N Pointer is generated by using an array struct member.

  \ID SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT
    \DESCRIPTION      Pointer is passed as function argument.
    \COUNTERMEASURE   \N Pointer is generated by referencing a member of a struct passed as reference function argument.
                         The validity of the function argument is ensured by the caller.

  \ID SBSW_ETHTSYN_VALID_API_POINTER
    \DESCRIPTION      Write access to element which is passed as function argument.
    \COUNTERMEASURE   \N It is assumed, that the input pointer is valid and the function only writes members of the
                         pointer struct.

  \ID SBSW_ETHTSYN_PASSING_API_POINTER
    \DESCRIPTION      Pointer is passed as function argument.
    \COUNTERMEASURE   \N Pointer was passed as function argument and is used to call sub-function.
                         The validity of the pointer is ensured by the caller.

  \ID SBSW_ETHTSYN_API_ARGUMENT_IDX
    \DESCRIPTION      Access of array element with index given as function argument is not checked for validity.
    \COUNTERMEASURE   \N The valid range of the function argument is defined at the function declaration and
                         has to be ensured by the calling function (Qualified use-case CSL01).

  \ID SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX
    \DESCRIPTION      Access of array element without validity check.
    \COUNTERMEASURE   \N The condition (and value range) of the function argument to be valid is defined at the function
                         declaration and has to be ensured by the calling function (Qualified use-case CSL01).

  \ID SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX_PTR_BY_INDIRECTION
    \DESCRIPTION      Pointer write access without validity check.
    \COUNTERMEASURE   \N The condition (and value range) of the function argument to be valid is defined at the function
                         declaration and has to be ensured by the calling function (Qualified use-case CSL03).

  \ID SBSW_ETHTSYN_FUNCTION_PTR_CALL
    \DESCRIPTION      Calling a function pointer without checking the reference.
    \COUNTERMEASURE   \R It is checked that the corresponding function pointer is configured.

  \ID SBSW_ETHTSYN_MSG_BUFFER_IDX
    \DESCRIPTION      Access of EthTSyn_SwtMgmt_MsgBuffer array.
    \COUNTERMEASURE   \R A Runtime check exists that verifies that the index is smaller than the size
                         (i.e. ETHTSYN_SWT_MGMT_MSG_BUFFER_COUNT) of the array EthTSyn_SwtMgmt_MsgBuffer.

  \ID SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE
    \DESCRIPTION      Access of array (used for crc data) element with index is not checked for validity.
    \COUNTERMEASURE   \N The array has a fixed size which is can hold the maximum possible amount of crc data.
                         The used indices are therefore smaller than the array size.

SBSW_JUSTIFICATION_END */

/* COV_JUSTIFICATION_BEGIN

  \ID COV_ETHTSYN_TESTSUITE_INSTRUMENTATION
    \ACCEPT TX
    \REASON This code is only deactivated by test suite for unit testing purpose.

COV_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn.c
 *********************************************************************************************************************/
