/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  CanTSyn.c
 *        \brief  Vector AUTOSAR CanTSyn code file
 *
 *      \details  This is the main implementation file of the Vector AUTOSAR module CanTSyn.
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

#define CANTSYN_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "CanTSyn.h"
#include "CanTSyn_Cbk.h"
#include "SchM_CanTSyn.h"
#include "StbM.h"
#if (CANTSYN_MASTERCONFIG == STD_ON)
# include "CanIf.h"
#endif
#if (CANTSYN_CRC_USED)
# include "Crc.h"
#endif
#if (CANTSYN_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of CanTSyn header file */
#if (  (CANTSYN_SW_MAJOR_VERSION != (3u)) \
    || (CANTSYN_SW_MINOR_VERSION != (7u)) \
    || (CANTSYN_SW_PATCH_VERSION != (1u)) )
# error "Vendor specific version numbers of CanTSyn.c and CanTSyn.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (CANTSYN_CFG_MAJOR_VERSION != (3u)) \
    || (CANTSYN_CFG_MINOR_VERSION != (7u)) )
# error "Version numbers of CanTSyn.c and CanTSyn_Cfg.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

#define CANTSYN_INV_DOMAIN_IDX                             (255u)
#define CANTSYN_MAX_SEQUENCE_COUNTER                       (15u)
#define CANTSYN_START_OFFSET_TIME_DOMAIN_ID                (16u)

#define CANTSYN_TIME_SYNC_MESSAGE_DLC                      (8u)
#define CANTSYN_TIME_SYNC_MESSAGE_TYPE_SYNC_NOT_CRC        (0x10u)
#define CANTSYN_TIME_SYNC_MESSAGE_TYPE_SYNC_CRC            (0x20u)
#define CANTSYN_TIME_SYNC_MESSAGE_TYPE_FUP_NOT_CRC         (0x18u)
#define CANTSYN_TIME_SYNC_MESSAGE_TYPE_FUP_CRC             (0x28u)
#ifdef CANTSYN_AR_4_3_X
# define CANTSYN_TIME_SYNC_MESSAGE_TYPE_OFS_NOT_CRC         (0x34u)
# define CANTSYN_TIME_SYNC_MESSAGE_TYPE_OFS_CRC             (0x44u)
# define CANTSYN_TIME_SYNC_MESSAGE_TYPE_OFNS_NOT_CRC        (0x3Cu)
# define CANTSYN_TIME_SYNC_MESSAGE_TYPE_OFNS_CRC            (0x4Cu)
#endif
#ifdef CANTSYN_AR_4_2_X
# define CANTSYN_TIME_SYNC_MESSAGE_TYPE_OFS_NOT_CRC         (0x30u)
# define CANTSYN_TIME_SYNC_MESSAGE_TYPE_OFS_CRC             (0x40u)
# define CANTSYN_TIME_SYNC_MESSAGE_TYPE_OFNS_NOT_CRC        (0x38u)
# define CANTSYN_TIME_SYNC_MESSAGE_TYPE_OFNS_CRC            (0x48u)
#endif

#define CANTSYN_CRC_START_VALUE                            (0xFFu)

#define CANTSYN_TIMESTAMP_MAX_NANOSECONDS                  (999999999uL) /* 10^9 nanoseconds per second */
#define CANTSYN_TIMESTAMP_MAX_SECONDS                      (4294967295uL)
#define CANTSYN_TIMESTAMP_MAX_SECONDSHI                    (65535u)

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

#define CanTSyn_GetGlobalTimeBaseBit(status)               ((status) & StbM_Global_Time_Base_BflMask) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTSyn_GetSyncToGatewayBit(status)                ((status) & StbM_Sync_To_Gateway_BflMask) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTSyn_GetTimeoutBit(status)                      ((status) & StbM_Timeout_BflMask) /* PRQA S 3453 */     /* MD_MSR_FctLikeMacro */

#define CanTSyn_IsSyncMsg(type)                            (((type) == CANTSYN_TIME_SYNC_MESSAGE_TYPE_SYNC_NOT_CRC) || ((type) == CANTSYN_TIME_SYNC_MESSAGE_TYPE_SYNC_CRC)) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTSyn_IsFupMsg(type)                             (((type) == CANTSYN_TIME_SYNC_MESSAGE_TYPE_FUP_NOT_CRC) || ((type) == CANTSYN_TIME_SYNC_MESSAGE_TYPE_FUP_CRC)) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTSyn_IsOfsMsg(type)                             (((type) == CANTSYN_TIME_SYNC_MESSAGE_TYPE_OFS_NOT_CRC) || ((type) == CANTSYN_TIME_SYNC_MESSAGE_TYPE_OFS_CRC)) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTSyn_IsOfnsMsg(type)                            (((type) == CANTSYN_TIME_SYNC_MESSAGE_TYPE_OFNS_NOT_CRC) || ((type) == CANTSYN_TIME_SYNC_MESSAGE_TYPE_OFNS_CRC)) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#define CanTSyn_IsSyncCrcSecured(type)                     (((type) == CANTSYN_TIME_SYNC_MESSAGE_TYPE_SYNC_CRC) || ((type) == CANTSYN_TIME_SYNC_MESSAGE_TYPE_OFS_CRC)) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTSyn_IsFupCrcSecured(type)                      (((type) == CANTSYN_TIME_SYNC_MESSAGE_TYPE_FUP_CRC) || ((type) == CANTSYN_TIME_SYNC_MESSAGE_TYPE_OFNS_CRC)) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* Get Message type (Multiplexer value) */
#define CanTSyn_CanSignal_GetType(msg)                     ((msg)[0]) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* Get CRC */
#define CanTSyn_CanSignal_GetCRC(crcMsg)                   ((crcMsg)[1]) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* Get Sequence counter */
#define CanTSyn_CanSignal_GetSC(msg)                       ((msg)[2] & 0x0Fu) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* Get Time Domain */
#define CanTSyn_CanSignal_GetD(msg)                        ((msg)[2] >> 4u) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* Get the time value (seconds from SYNC/OFS message or nanoseconds from FUP/OFNS message) */
#define CanTSyn_CanSignal_GetTime(msg)                     (((uint32) (msg)[7]) | ((uint32) (msg)[6] << 8u) | ((uint32) (msg)[5] << 16u) | ((uint32) (msg)[4] << 24u)) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* Get OVS from FUP message */
#define CanTSyn_CanSignal_GetOVS(fupMsg)                   ((uint8)((fupMsg)[3] & 0x03u)) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* Get SGW from FUP message */
#define CanTSyn_CanSignal_GetSGW(fupMsg)                   ((uint8)(((fupMsg)[3] & 0x04u) >> 2u)) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* Get User bytes (SYNC: Byte 0 and 1; FUP: Byte 2; Byte 1 and 2 only valid for not CRC secured messages) */
#define CanTSyn_CanSignal_GetUserByte0(syncMsg)            ((syncMsg)[3]) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTSyn_CanSignal_GetUserByte1(syncMsg)            ((syncMsg)[1]) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTSyn_CanSignal_GetUserByte2(fupMsg)             ((fupMsg)[1]) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* Get secondsHi from OFS/OFNS message */
#define CanTSyn_CanSignal_GetSecHi(ofsMsg)                 ((ofsMsg)[3]) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* Set Message type (Multiplexer value) */
#define CanTSyn_CanSignal_SetType(msg, value)              (msg)[0] = (uint8) (value) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* Set CRC */
#define CanTSyn_CanSignal_SetCRC(crcMsg, value)            (crcMsg)[1] = (uint8) (value) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* Set Sequence counter */
#define CanTSyn_CanSignal_SetSC(msg, value)                (msg)[2] = (uint8) (((msg)[2] & 0xF0u) | ((value) & 0x0Fu)) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* Set Time Domain */
#define CanTSyn_CanSignal_SetD(msg, value)                 (msg)[2] = (uint8) (((msg)[2] & 0x0Fu) | ((value) << 4u)) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* Get the time value (seconds from SYNC/OFS message or nanoseconds from FUP/OFNS message) */
#define CanTSyn_CanSignal_SetTime(msg, value)              {(msg)[7] = (uint8) (value);          \
                                                            (msg)[6] = (uint8) ((value) >>  8u); \
                                                            (msg)[5] = (uint8) ((value) >> 16u); \
                                                            (msg)[4] = (uint8) ((value) >> 24u);}

/* Set OVS from FUP message */
#define CanTSyn_CanSignal_SetOVS(fupMsg, value)            (fupMsg)[3] = (uint8) (((fupMsg)[3] & 0xFCu) | ((uint8)((value) & 0x03u))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* Set SGW from FUP message */
#define CanTSyn_CanSignal_SetSGW(fupMsg, value)            (fupMsg)[3] = (uint8) (((fupMsg)[3] & 0xFBu) | ((value) & 0x04u)) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* Clear reserved bits from FUP message */
#define CanTSyn_CanSignal_ClearReservedFup(fupMsg)         (fupMsg)[3] = (uint8) ((fupMsg)[3] & 0x07u) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* Set User bytes (SYNC: Byte 0 and 1; FUP: Byte 2; Byte 1 and 2 only valid for not CRC secured messages) */
#define CanTSyn_CanSignal_SetUserByte0(syncMsg, value)     (syncMsg)[3] = (uint8) (value) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTSyn_CanSignal_SetUserByte1(syncMsg, value)     (syncMsg)[1] = (uint8) (value) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTSyn_CanSignal_SetUserByte2(fupMsg, value)      (fupMsg)[1] = (uint8) (value) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* Set secondsHi from OFS/OFNS message */
#define CanTSyn_CanSignal_SetSecHi(ofsMsg, value)          (ofsMsg)[3] = (uint8) (value) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* Set reserved byte from OFS/OFNS message */
#define CanTSyn_CanSignal_SetReservedOfs(ofsMsg, value)    (ofsMsg)[1] = (uint8) (value) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (CANTSYN_LOCAL) /* COV_CANTSYN_MSR_COMPATIBILITY */
# define CANTSYN_LOCAL static
#endif

#if !defined (CANTSYN_LOCAL_INLINE) /* COV_CANTSYN_MSR_COMPATIBILITY */
# define CANTSYN_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define CANTSYN_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANTSYN_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define CANTSYN_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  CanTSyn_InitDomain()
 *********************************************************************************************************************/
/*! \brief      Initialization of CanTSyn Domain
 *  \details    This function initializes a CanTSyn Domain.
 *  \param[in]  domainIdx         Valid index of Domain that should be initialized.
 *  \pre        -
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_InitDomain(CanTSyn_DomainConfigIterType domainIdx);

/**********************************************************************************************************************
 *  CanTSyn_TimestampPlusTimestampRaw()
 *********************************************************************************************************************/
/*! \brief      Add timestamp and timestamp in raw format
 *  \details    This function calculates the sum of one timestamp and one timestamp in raw format.
 *  \param[in]  timestampPtr      Pointer to timestamp.
 *  \param[in]  timestampRawPtr   Pointer to timestamp in raw format.
 *  \param[out] timesumPtr        Pointer to timestamp with sum of timestamp and timestampRaw.
 *  \pre        Exclusive Area CANTSYN_EXCLUSIVE_AREA_0 is entered
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_TimestampPlusTimestampRaw(
  P2CONST(StbM_TimeStampType, AUTOMATIC, CANTSYN_APPL_DATA) timestampPtr,
  P2CONST(StbM_TimeStampRawType, AUTOMATIC, CANTSYN_APPL_DATA) timestampRawPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, CANTSYN_APPL_VAR) timesumPtr);

#if (CANTSYN_MASTERCONFIG == STD_ON)
/**********************************************************************************************************************
 *  CanTSyn_ProcessSend()
 *********************************************************************************************************************/
/*! \brief      Send processing
 *  \details    This function handles the processing of sending the message.
 *  \param[in]  domainIdx         Valid domain index of the message.
 *  \param[in]  masterIdx         Valid master index that transmits message.
 *  \pre        -
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_ProcessSend(CanTSyn_DomainConfigIterType domainIdx, CanTSyn_MasterConfigIterType masterIdx);

/**********************************************************************************************************************
 *  CanTSyn_SendSyncMsg()
 *********************************************************************************************************************/
/*! \brief      Send processing
 *  \details    This function handles the processing of sending sync message.
 *  \param[in]  domainIdx          Valid domain index of the message.
 *  \param[in]  masterIdx          Valid master index that transmits sync message.
 *  \param[in]  canControllerIdIdx Valid index of the controllerId that send state-machine should be processed.
 *  \param[in]  pduIdIdx           Valid index of the pduId that send state-machine should be processed.
 *  \pre        -
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_SendSyncMsg(CanTSyn_DomainConfigIterType domainIdx, CanTSyn_MasterConfigIterType masterIdx, uint8 canControllerIdIdx, uint32 pduIdIdx);

/**********************************************************************************************************************
 *  CanTSyn_SendFupMsg()
 *********************************************************************************************************************/
/*! \brief      Send processing
 *  \details    This function handles the processing of send.
 *  \param[in]  domainIdx          Valid domain index of the message.
 *  \param[in]  masterIdx          Valid master index that transmits FUP message.
 *  \pre        -
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_SendFupMsg(CanTSyn_DomainConfigIterType domainIdx, CanTSyn_MasterConfigIterType masterIdx);

/**********************************************************************************************************************
 *  CanTSyn_TransmitSync()
 *********************************************************************************************************************/
/*! \brief      Transmit sync messages
 *  \details    This function handles the transmitting of sync messages.
 *  \param[in]  domainIdx         Valid domain index of the message.
 *  \param[in]  masterIdx         Valid master index that transmits sync message.
 *  \return     E_OK     - Message transmission was successful
 *  \return     E_NOT_OK - Message transmission was not successful
 *  \pre        Master is in state CANTSYN_STATE_SEND_WAITING_FOR_SYNC_SEND
 *  \pre        StbM passed a time base with GlobalTimeBaseBit set
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_TransmitSync(CanTSyn_DomainConfigIterType domainIdx, CanTSyn_MasterConfigIterType masterIdx);

/**********************************************************************************************************************
 *  CanTSyn_TransmitFup()
 *********************************************************************************************************************/
/*! \brief      Transmit fup messages
 *  \details    This function handles the transmitting of fup messages.
 *  \param[in]  domainIdx         Valid domain index of the message.
 *  \param[in]  masterIdx         Valid master index that transmits sync message.
 *  \pre        Master is in state CANTSYN_STATE_SEND_WAITING_FOR_FOLLOW_UP_SEND
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_TransmitFup(CanTSyn_DomainConfigIterType domainIdx, CanTSyn_MasterConfigIterType masterIdx);

/**********************************************************************************************************************
 *  CanTSyn_IncrementSequenceCounter()
 *********************************************************************************************************************/
/*! \brief      Increment sequence counter
 *  \details    This function increments the sequence counter.
 *  \param[in]  masterIdx         Valid master index that transmits sync message.
 *  \pre        -
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_IncrementSequenceCounter(CanTSyn_MasterConfigIterType masterIdx);

/**********************************************************************************************************************
 *  CanTSyn_HandleMasterRole()
 *********************************************************************************************************************/
/*! \brief      Handles all actions of the masters of a domain.
 *  \details    Handles the counters and the message transmission of the masters of a time domain.
 *  \param[in]  domainIdx          Valid domain index of the message.
 *  \pre         -
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_HandleMasterRole(CanTSyn_DomainConfigIterType domainIdx);
  
  /**********************************************************************************************************************
 *  CanTSyn_SendMessage()
 *********************************************************************************************************************/
/*! \brief      Send processing
 *  \details    This function handles the processing of SYNC send.
 *  \param[in]  domainIdx         Valid domain index of the message.
 *  \param[in]  masterIdx         Valid master index that processes the send state-machine.
 *  \pre        -
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_SendMessage(CanTSyn_DomainConfigIterType domainIdx, CanTSyn_MasterConfigIterType masterIdx); 

/**********************************************************************************************************************
 *  CanTSyn_PrepareAndSendFUPMsg()
 *********************************************************************************************************************/
/*! \brief      Check the type of message
 *  \details    This function handles the checking of message.
 *  \param[in]  domainIdx       Valid domain index of the message.
 *  \param[in]  masterIdx       Valid master index that send state-machine.
 *  \pre        -
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_PrepareAndSendFUPMsg(CanTSyn_DomainConfigIterType domainIdx, CanTSyn_MasterConfigIterType masterIdx);

/**********************************************************************************************************************
 *  CanTSyn_PrepareAndSendSync()
 *********************************************************************************************************************/
/*! \brief      Prepare SYNC and OFS messages and transmit them.
 *  \details    This function prepares the SYNC and OFS messages and transmits them over CAN.
 *  \param[in]  domainIdx      Valid domain index of the message.
 *  \param[in]  masterIdx      Valid master index that transmits sync message.
 *  \return     E_OK     - Message transmission was successful
 *  \return     E_NOT_OK - Message transmission was not successful
 *  \pre        -
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_PrepareAndSendSync(CanTSyn_DomainConfigIterType domainIdx, CanTSyn_MasterConfigIterType masterIdx);

/**********************************************************************************************************************
 *  CanTSyn_CheckMsgConfirmation()
 *********************************************************************************************************************/
/*! \brief      Check the message confirmation based on type of message
 *  \details    This function handles the checking of confirmation of the message.
 *  \param[in]  TxPduId           ID of the I-PDU that has been transmitted.
 *  \return     domainIdx         Returns domain ID based on the message type
 *  \pre        -
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(CanTSyn_DomainConfigIterType, CANTSYN_CODE) CanTSyn_CheckMsgConfirmation(PduIdType TxPduId);

/**********************************************************************************************************************
 *  CanTSyn_InitPduIdStates()
 *********************************************************************************************************************/
/*! \brief      Initialize the transmit states for each can Id.
 *  \details    This function initializes each index to false.
 *  \pre        -
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_InitPduIdStates(void);
#endif
 
#if (CANTSYN_SLAVECONFIG == STD_ON)
/**********************************************************************************************************************
 *  CanTSyn_ProcessReceive()
 *********************************************************************************************************************/
/*! \brief      Receive processing
 *  \details    This function handles the processing of received message.
 *  \param[in]  slaveIdx          Valid index of the Slave that receive handling should be processed.
 *  \pre        -
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_ProcessReceive(uint8 slaveIdx);

/**********************************************************************************************************************
 *  CanTSyn_HandleSync()
 *********************************************************************************************************************/
/*! \brief      Processing of received sync messages
 *  \details    This function handles the processing of received sync messages.
 *  \param[in]  slaveIdx          Valid index of the Slave that receive handling should be processed.
 *  \param[in]  pduInfoPtr        Pointer to the PDU that contains the received sync message.
 *  \pre        Time slave is in state CANTSYN_STATE_RECEIVE_WAITING_FOR_SYNC
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_HandleSync(
  uint8 slaveIdx,
  P2CONST(PduInfoType, AUTOMATIC, CANTSYN_APPL_DATA) pduInfoPtr);

/**********************************************************************************************************************
 *  CanTSyn_HandleFup()
 *********************************************************************************************************************/
/*! \brief      Processing of received fup messages
 *  \details    This function handles the processing of received fup messages.
 *  \param[in]  domainIdx         Valid domain index of the message.
 *  \param[in]  slaveIdx          Valid index of the Slave that receive handling should be processed.
 *  \param[in]  pduInfoPtr        Pointer to the PDU that contains the received fup message.
 *  \pre        slave is in state CANTSYN_STATE_RECEIVE_WAITING_FOR_FOLLOW_UP
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_HandleFup(
  CanTSyn_DomainConfigIterType domainIdx, uint8 slaveIdx,
  P2CONST(PduInfoType, AUTOMATIC, CANTSYN_APPL_DATA) pduInfoPtr);

/**********************************************************************************************************************
 *  CanTSyn_CheckRxSequenceCounter()
 *********************************************************************************************************************/
/*! \brief      Check received sequence counter
 *  \details    This function checks if the received sequence counter is valid.
 *  \param[in]  slaveIdx          Valid index of the slave of the received sync message.
 *  \param[in]  counter           Received counter value.
 *  \return     E_OK     - Received sequence counter is valid
 *  \return     E_NOT_OK - Received sequence counter is invalid
 *  \pre        CanTSyn_RxSequenceCounter is initialized with invalid value
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_CheckRxSequenceCounter(CanTSyn_DomainConfigIterType domainIdx, uint8 slaveIdx, uint8 counter);
  
  /**********************************************************************************************************************
 *  CanTSyn_CheckSyncMsg()
 *********************************************************************************************************************/
/*! \brief      Validates and saves the received message
 *  \details    Checks if the message is valid depending on the configured CRC check and saves it if valid
 *  \param[in]  PduInfoPtr          Contains the length (SduLength) of the received I-PDU and a pointer to a buffer (SduDataPtr) containing the I-PDU.
 *  \param[in]  domainIdx           Valid domain index of the message.
 *  \param[in]  slaveIdx            Valid index of the slave the message belongs to.
 *  \param[in]  messageType         Message type of the received message.
 *  \pre        -
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_CheckSyncMsg(
  P2CONST(PduInfoType, AUTOMATIC, CANTSYN_APPL_DATA) PduInfoPtr,
  CanTSyn_DomainConfigIterType domainIdx,
  uint8 slaveIdx,
  uint8 messageType);

/**********************************************************************************************************************
 *  CanTSyn_CheckFupMsg()
 *********************************************************************************************************************/
/*! \brief      Validates and saves the received message
 *  \details    Checks if the message is valid depending on the configured CRC check and saves it if valid
 *  \param[in]  PduInfoPtr          Contains the length (SduLength) of the received I-PDU and a pointer to a buffer (SduDataPtr) containing the I-PDU.
 *  \param[in]  domainIdx           Valid domain index of the message.
 *  \param[in]  slaveIdx            Valid index of the slave the message belongs to.
 *  \param[in]  messageType         Message type of the received message.
 *  \pre        -
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_CheckFupMsg(
  P2CONST(PduInfoType, AUTOMATIC, CANTSYN_APPL_DATA) PduInfoPtr,
  CanTSyn_DomainConfigIterType domainIdx,
  uint8 slaveIdx,
  uint8 messageType);

/**********************************************************************************************************************
 *  CanTSyn_CheckAndProcessMsg()
 *********************************************************************************************************************/
/*! \brief      Checks and processes the received message
 *  \details    Checks for the correct RxPduId and validates and saves the message content
 *  \param[in]  RxPduId             ID of the received I-PDU.
 *  \param[in]  PduInfoPtr          Contains the length (SduLength) of the received I-PDU and a pointer to a buffer (SduDataPtr) containing the I-PDU.
 *  \param[in]  domainId            Domain ID of the received message.
 *  \param[in]  messageType         Message type of the received message.
 *  \return     CANTSYN_E_NO_ERROR      - Received message content is valid
 *  \return     CANTSYN_E_INVALID_PDUID - Received message contains wrong PDU ID
 *  \pre        -
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(uint8, CANTSYN_CODE) CanTSyn_CheckAndProcessMsg(
  PduIdType RxPduId,
  P2CONST(PduInfoType, AUTOMATIC, CANTSYN_APPL_DATA) PduInfoPtr,
  uint8 domainId,
  uint8 messageType);

/**********************************************************************************************************************
 *  CanTSyn_CheckPduIdAndMsgReceivedStatus()
 *********************************************************************************************************************/
/*! \brief      Checks the PduId and then the received message
 *  \details    Checks for the correct RxPduId and then checks the received message.
 *  \param[in]  RxPduId             ID of the received I-PDU.
 *  \param[in]  PduInfoPtr          Contains the length (SduLength) of the received I-PDU and a pointer to a buffer (SduDataPtr) containing the I-PDU.
 *  \param[in]  domainIdx           Valid domain index of the message.
 *  \param[in]  messageType         Message type of the received message.
 *  \return     CANTSYN_E_NO_ERROR      - Received message content is valid
 *  \return     CANTSYN_E_INVALID_PDUID - Received message contains wrong PDU ID
 *  \pre        -
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(uint8, CANTSYN_CODE) CanTSyn_CheckPduIdAndMsgReceivedStatus(PduIdType RxPduId,
  P2CONST(PduInfoType, AUTOMATIC, CANTSYN_APPL_DATA) PduInfoPtr,
  CanTSyn_DomainConfigIterType domainIdx,
  uint8 messageType);


/**********************************************************************************************************************
 *  CanTSyn_CheckMessage()
 *********************************************************************************************************************/
/*! \brief      Checks the received message
 *  \details    Checks for the correct RxPduId and validates and saves the message content
 *  \param[in]  PduInfoPtr          Contains the length (SduLength) of the received I-PDU and a pointer to a buffer (SduDataPtr) containing the I-PDU.
 *  \param[in]  domainIdx           Valid domain index of the message.
 *  \param[in]  slaveIdx            Valid index of the slave the message belongs to.
 *  \param[in]  messageType         Message type of the received message.
 *  \pre        -
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_CheckMessage(
  P2CONST(PduInfoType, AUTOMATIC, CANTSYN_APPL_DATA) PduInfoPtr,
  CanTSyn_DomainConfigIterType domainIdx,
  uint8 slaveIdx,  
  uint8 messageType);

/**********************************************************************************************************************
 *  CanTSyn_CheckTypeOfMessage()
 *********************************************************************************************************************/
/*! \brief      Check the type of message
 *  \details    This function handles the checking of message.
 *  \param[in]  messageType       Type of the message
 *  \param[in]  domainId          Domain ID of the received message.
 *  \return     domainId          Returns domain ID based on the message type
 *  \pre        -
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(uint8, CANTSYN_CODE) CanTSyn_CheckTypeOfMessage(uint8 messageType, uint8 domainId);

/**********************************************************************************************************************
 *  CanTSyn_MemCpy()
 *********************************************************************************************************************/
/*! \brief      Copy data from one buffer to another
 *  \details    This function copies data from the source data buffer to the destination data buffer.
 *  \param[in]  destination       Pointer to the destination data buffer.
 *  \param[in]  source            Pointer to the source data buffer.
 *  \param[in]  count             Number of elements to copy.
 *  \pre        destination and source are of size count
 *********************************************************************************************************************/
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_MemCpy(
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_VAR) destination,
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_DATA) source,
  uint8 count);
#endif 

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  CanTSyn_InitDomain()
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
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_InitDomain(CanTSyn_DomainConfigIterType domainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
#if (CANTSYN_SLAVECONFIG == STD_ON)
  uint8 slaveIdx;
#endif
#if (CANTSYN_MASTERCONFIG == STD_ON)
  CanTSyn_MasterConfigIterType masterCount, masterIdx;
#endif

  /* ----- Implementation ----------------------------------------------- */
#if (CANTSYN_SLAVECONFIG == STD_ON)
# if (CanTSyn_GetSizeOfSlaveConfig() != CanTSyn_GetSizeOfDomainConfig())
  /* #10 init slave state */
  if (CanTSyn_IsSlaveConfigUsedOfDomainConfig(domainIdx) == TRUE) /* PRQA S 1881, 4304 */ /* MD_MSR_AutosarBoolean */
# endif
  {
    slaveIdx = CanTSyn_GetSlaveConfigIdxOfDomainConfig(domainIdx);
    CanTSyn_SetStateOfSlaveState(slaveIdx, CANTSYN_STATE_RECEIVE_WAITING_FOR_SYNC); /* SBSW_CANTSYN_ACCESS_SLAVESTATE */
    CanTSyn_SetRxFollowUpTimeoutCountOfSlaveState(slaveIdx, 0u); /* SBSW_CANTSYN_ACCESS_SLAVESTATE */
    /* #20 initialize Rx sequence counter with invalid value to enable detection of first received message */
    CanTSyn_SetRxSequenceCounterOfSlaveState(slaveIdx, (CANTSYN_MAX_SEQUENCE_COUNTER + 1u)); /* SBSW_CANTSYN_ACCESS_SLAVESTATE */
  }
#endif

#if (CANTSYN_MASTERCONFIG == STD_ON)
  for (masterCount = 0u; masterCount < CanTSyn_GetMasterConfigLengthOfDomainConfig(domainIdx); masterCount++)
  {
    masterIdx = CanTSyn_GetMasterConfigStartIdxOfDomainConfig(domainIdx) + masterCount;
    CanTSyn_SetStateOfMasterState(masterIdx, CANTSYN_STATE_SEND_WAITING_FOR_SYNC_SEND); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
    CanTSyn_SetTxIntervalCountOfMasterState(masterIdx, CanTSyn_GetTxPeriodOfMasterConfig(masterIdx)); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
    CanTSyn_SetMasterConfTimeoutCountOfMasterState(masterIdx, 0u); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
# if (CANTSYN_EXISTS_SUPPORTED_IMMEDIATETIMESYNCOFMASTERCONFIG == STD_ON)
    /* #40 initialize Immediate TimeSync counters */
#  if (CANTSYN_EXISTS_NOT_SUPPORTED_IMMEDIATETIMESYNCOFMASTERCONFIG == STD_ON)
    if (CanTSyn_GetImmediateTimeSyncOfMasterConfig(masterIdx) == CANTSYN_SUPPORTED_IMMEDIATETIMESYNCOFMASTERCONFIG)
#  endif
    {
      CanTSyn_SetCyclicMsgResumeCounterOfMasterState(masterIdx, 0u); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
      CanTSyn_SetLastUpdateCounterOfMasterState(masterIdx, 0u); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
    }
# endif
    /* #50 initialize Tx sequence counter */
    CanTSyn_SetTxSequenceCounterOfMasterState(masterIdx, CANTSYN_MAX_SEQUENCE_COUNTER); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
  }
#endif

} /* CanTSyn_InitDomain() */

/**********************************************************************************************************************
 *  CanTSyn_TimestampPlusTimestampRaw()
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
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_TimestampPlusTimestampRaw(
  P2CONST(StbM_TimeStampType, AUTOMATIC, CANTSYN_APPL_DATA) timestampPtr,
  P2CONST(StbM_TimeStampRawType, AUTOMATIC, CANTSYN_APPL_DATA) timestampRawPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, CANTSYN_APPL_VAR) timesumPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 overflowSeconds = 0u;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Calculate the sum of nanoseconds */
  timesumPtr->nanoseconds = timestampPtr->nanoseconds + *timestampRawPtr; /* SBSW_CANTSYN_TIMESUMPTR */

  /* #20 check for overflow of nanoseconds */
  if (timesumPtr->nanoseconds < *timestampRawPtr)
  {
    /* #30 split seconds from timestampRawPtr */
    overflowSeconds = (uint8)(*timestampRawPtr / (CANTSYN_TIMESTAMP_MAX_NANOSECONDS + 1u));
    timesumPtr->nanoseconds = (*timestampRawPtr % (CANTSYN_TIMESTAMP_MAX_NANOSECONDS + 1u)) + timestampPtr->nanoseconds; /* SBSW_CANTSYN_TIMESUMPTR */
  }
  /* #40 check if nanoseconds are still bigger than one second */
  if (timesumPtr->nanoseconds > CANTSYN_TIMESTAMP_MAX_NANOSECONDS)
  {
    /* #50 Split seconds from timesumPtr */
    overflowSeconds += (uint8)(timesumPtr->nanoseconds / (CANTSYN_TIMESTAMP_MAX_NANOSECONDS + 1u));
    timesumPtr->nanoseconds = timesumPtr->nanoseconds % (CANTSYN_TIMESTAMP_MAX_NANOSECONDS + 1u); /* SBSW_CANTSYN_TIMESUMPTR */
  }

  /* #60 Set resulting seconds and secondsHi */
  timesumPtr->seconds = timestampPtr->seconds; /* SBSW_CANTSYN_TIMESUMPTR */
  timesumPtr->secondsHi = timestampPtr->secondsHi; /* SBSW_CANTSYN_TIMESUMPTR */

  /* #70 If a split of seconds occurred */
  if (overflowSeconds > 0u)
  {
    /* #80 Increment secondsHi, if an overflow of seconds occurred */
    if (timestampPtr->seconds > (CANTSYN_TIMESTAMP_MAX_SECONDS - overflowSeconds))
    {
        timesumPtr->secondsHi++; /* SBSW_CANTSYN_TIMESUMPTR */
    }
    /* #90 Adapt the seconds */
    timesumPtr->seconds += overflowSeconds; /* SBSW_CANTSYN_TIMESUMPTR */
  }
} /* CanTSyn_TimestampPlusTimestampRaw() */

#if (CANTSYN_MASTERCONFIG == STD_ON)
/**********************************************************************************************************************
 *  CanTSyn_ProcessSend()
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
 * \trace DSGN-CanTSyn22807, DSGN-CanTSyn22808, DSGN-CanTSyn22809, DSGN-CanTSyn22806
 */
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_ProcessSend(CanTSyn_DomainConfigIterType domainIdx, CanTSyn_MasterConfigIterType masterIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 pduIdIdx;
  uint8 canControllerIdIdx;

  /* ----- Implementation ----------------------------------------------- */
  pduIdIdx = CanTSyn_GetPduIdStatesIdxOfMasterConfig(masterIdx);
  canControllerIdIdx = CanTSyn_GetCanControllerIdStatesIdxOfMasterConfig(masterIdx);

  switch (CanTSyn_GetStateOfMasterState(masterIdx))
  {
    /* #10 If master is in state CANTSYN_STATE_SEND_WAITING_FOR_SYNC_SEND */
    case CANTSYN_STATE_SEND_WAITING_FOR_SYNC_SEND:
      CanTSyn_SendSyncMsg(domainIdx, masterIdx, canControllerIdIdx, pduIdIdx);
      break;

    /* #20 If master is in state CANTSYN_STATE_SEND_WAITING_FOR_SYNC_TX_CONFIRMATIONS */
    case CANTSYN_STATE_SEND_WAITING_FOR_SYNC_TX_CONFIRMATION:
    /* #25 Or if master is in state CANTSYN_STATE_SEND_WAITING_FOR_FOLLOW_UP_TX_CONFIRMATION */
    case CANTSYN_STATE_SEND_WAITING_FOR_FOLLOW_UP_TX_CONFIRMATION:
      /* #30 If the master confirmation timeout expires */
      if (CanTSyn_GetMasterConfTimeoutCountOfMasterState(masterIdx) == 0u)
      {
        /* #40 Set master state to CANTSYN_STATE_SEND_WAITING_FOR_SYNC_SEND */
        SchM_Enter_CanTSyn_CANTSYN_EXCLUSIVE_AREA_0();
        CanTSyn_SetStateOfMasterState(masterIdx, CANTSYN_STATE_SEND_WAITING_FOR_SYNC_SEND); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
        CanTSyn_SetPduIdStates(pduIdIdx, FALSE); /* SBSW_CANTSYN_ACCESS_PDUIDSTATES */
        SchM_Exit_CanTSyn_CANTSYN_EXCLUSIVE_AREA_0();
      }
      break;

    /* #50 If master is in state CANTSYN_STATE_SEND_WAITING_FOR_FOLLOW_UP_SEND */
    case CANTSYN_STATE_SEND_WAITING_FOR_FOLLOW_UP_SEND:
      CanTSyn_SendFupMsg(domainIdx, masterIdx);
      break;

    default: /* COV_CANTSYN_MSR_MISRA */
      break;
  }

} /* CanTSyn_ProcessSend() */

/**********************************************************************************************************************
 *  CanTSyn_SendSyncMsg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_SendSyncMsg(CanTSyn_DomainConfigIterType domainIdx, CanTSyn_MasterConfigIterType masterIdx, uint8 canControllerIdIdx, uint32 pduIdIdx)
{
  /* #10 If transmission is enabled for the associated controller and the debounce counter has expired */
  if ((CanTSyn_GetCanControllerIdStates(canControllerIdIdx) == CANTSYN_TX_ON)
# if (CANTSYN_TXDEBOUNCECOUNTERIDXOFMASTERCONFIG == STD_ON)
    && (CanTSyn_GetTxDebounceCounter(CanTSyn_GetTxDebounceCounterIdxOfMasterConfig(masterIdx)) == 0u)
# endif
# if (CanTSyn_GetSizeOfPduIdStates() != CanTSyn_GetSizeOfMasterConfig())
    && (!CanTSyn_IsPduIdStates(pduIdIdx))
# endif
    )
    {
      /* #20 Send a SYNC message after checking if ImmediateTimeSync is enabled. */
      CanTSyn_SendMessage(domainIdx, masterIdx);
    }
# if (CanTSyn_GetSizeOfPduIdStates() == CanTSyn_GetSizeOfMasterConfig())
  CANTSYN_DUMMY_STATEMENT(pduIdIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* CanTSyn_SendSyncMsg() */

/**********************************************************************************************************************
 *  CanTSyn_SendFupMsg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_SendFupMsg(CanTSyn_DomainConfigIterType domainIdx, CanTSyn_MasterConfigIterType masterIdx)
{
# if (CANTSYN_TXDEBOUNCECOUNTERIDXOFMASTERCONFIG == STD_ON)
  /* #20 Delay FUP/OFNS transmission until debouncing is finished */
  if (CanTSyn_GetTxDebounceCounter(CanTSyn_GetTxDebounceCounterIdxOfMasterConfig(masterIdx)) == 0u)
# endif
  {
    /* #30 Transmit FUP/OFNS message */
    CanTSyn_TransmitFup(domainIdx, masterIdx);
  }
} /* CanTSyn_SendFupMsg() */

/**********************************************************************************************************************
 *  CanTSyn_TransmitSync()
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
CANTSYN_LOCAL_INLINE FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_TransmitSync(
  CanTSyn_DomainConfigIterType domainIdx, 
  CanTSyn_MasterConfigIterType masterIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  PduInfoType pduInfo;
  CanTSyn_CanMsgType syncMsg;
  uint8 counter;
# if (CANTSYN_EXISTS_SUPPORTED_TXCRCSECUREDOFMASTERCONFIG == STD_ON)
  uint8 crcResult, dataId;
# endif

  /* ----- Implementation ----------------------------------------------- */

  /* #10 If the previous actions succeeded, continue with message preparations */
  SchM_Enter_CanTSyn_CANTSYN_EXCLUSIVE_AREA_0();

  pduInfo.SduLength  = CANTSYN_TIME_SYNC_MESSAGE_DLC;
  pduInfo.SduDataPtr = syncMsg;

  /* #20 Increment sequence counter on every transmission request of a SYNC message */
  CanTSyn_IncrementSequenceCounter(masterIdx);
  counter = CanTSyn_GetTxSequenceCounterOfMasterState(masterIdx);
# if (CANTSYN_EXISTS_OFFSET_OFFSETDOMAINOFDOMAINCONFIG == STD_ON)
  if (CanTSyn_GetDomainIdOfDomainConfig(domainIdx) >= CANTSYN_START_OFFSET_TIME_DOMAIN_ID)
  {
    /* #30 Assemble unconditioned parts of OFS message */
    /* Domain numbers of offset time bases (16-31) are carried in TimeSync messages as Domain number - 16 */
    CanTSyn_CanSignal_SetD(syncMsg, CanTSyn_GetDomainIdOfDomainConfig(domainIdx) - CANTSYN_START_OFFSET_TIME_DOMAIN_ID); /* SBSW_CANTSYN_WRITE_SYNCMSG */
    /* write secondsHi portion of Offset Time Base to OfsTimeSecLsbHi */
    CanTSyn_CanSignal_SetSecHi(syncMsg, CanTSyn_GetSyncTimestampOfMasterState(masterIdx).secondsHi); /* SBSW_CANTSYN_WRITE_SYNCMSG */
  }
  else
# endif
  {
    /* #40 Assemble unconditioned parts of SYNC message */
    CanTSyn_CanSignal_SetD(syncMsg, CanTSyn_GetDomainIdOfDomainConfig(domainIdx)); /* SBSW_CANTSYN_WRITE_SYNCMSG */
    CanTSyn_CanSignal_SetUserByte0(syncMsg, CanTSyn_GetUserDataOfMasterState(masterIdx).userByte0); /* SBSW_CANTSYN_WRITE_SYNCMSG */
  }

  /* #50 Add joint message parts */
  /* for SYNC message write second portion of T0 to SyncTimeSec, for OFS message write second portion of Offset Time Base to OfsTimeSecLsbLo */
  /* CanTSyn_CanSignal_SetTime has four separate accesses to the message buffer. Therefore we need four review helper justifications */  
  CanTSyn_CanSignal_SetTime(syncMsg, CanTSyn_GetSyncTimestampOfMasterState(masterIdx).seconds); /* SBSW_CANTSYN_WRITE_SYNCMSG */ /* SBSW_CANTSYN_WRITE_SYNCMSG */ /* SBSW_CANTSYN_WRITE_SYNCMSG */ /* SBSW_CANTSYN_WRITE_SYNCMSG */

  CanTSyn_CanSignal_SetSC(syncMsg, counter); /* SBSW_CANTSYN_WRITE_SYNCMSG */
# if (CANTSYN_EXISTS_NOT_SUPPORTED_TXCRCSECUREDOFMASTERCONFIG == STD_ON)
#  if (CANTSYN_EXISTS_SUPPORTED_TXCRCSECUREDOFMASTERCONFIG == STD_ON)
  /* #60 If no CRC is used, add the message type and user data for the type of the domain */
  if (CanTSyn_GetTxCrcSecuredOfMasterConfig(masterIdx) == CANTSYN_NOT_SUPPORTED_TXCRCSECUREDOFMASTERCONFIG)
#  endif
  {
#  if (CANTSYN_EXISTS_NOT_CRC_OFFSET_CRCANDDOMAINTYPEOFDOMAINCONFIG == STD_ON)
#   if (CANTSYN_EXISTS_NOT_CRC_SYNC_CRCANDDOMAINTYPEOFDOMAINCONFIG == STD_ON)
    if (CanTSyn_GetOffsetDomainOfDomainConfig(domainIdx) == CANTSYN_OFFSET_OFFSETDOMAINOFDOMAINCONFIG)
#   endif
    {
      CanTSyn_CanSignal_SetType(syncMsg, CANTSYN_TIME_SYNC_MESSAGE_TYPE_OFS_NOT_CRC); /* SBSW_CANTSYN_WRITE_SYNCMSG */
      /* set reserved byte to default value 0 */
      CanTSyn_CanSignal_SetReservedOfs(syncMsg, 0u); /* SBSW_CANTSYN_WRITE_SYNCMSG */
    }
#  endif
#  if (CANTSYN_EXISTS_NOT_CRC_SYNC_CRCANDDOMAINTYPEOFDOMAINCONFIG == STD_ON)
#   if (CANTSYN_EXISTS_NOT_CRC_OFFSET_CRCANDDOMAINTYPEOFDOMAINCONFIG == STD_ON)
    if (CanTSyn_GetOffsetDomainOfDomainConfig(domainIdx) == CANTSYN_NOT_OFFSET_OFFSETDOMAINOFDOMAINCONFIG)
#   endif
    {
      CanTSyn_CanSignal_SetType(syncMsg, CANTSYN_TIME_SYNC_MESSAGE_TYPE_SYNC_NOT_CRC); /* SBSW_CANTSYN_WRITE_SYNCMSG */
      CanTSyn_CanSignal_SetUserByte1(syncMsg, CanTSyn_GetUserDataOfMasterState(masterIdx).userByte1); /* SBSW_CANTSYN_WRITE_SYNCMSG */
    }
#  endif
  }
# endif

# if (CANTSYN_EXISTS_SUPPORTED_TXCRCSECUREDOFMASTERCONFIG == STD_ON)
#  if (CANTSYN_EXISTS_NOT_SUPPORTED_TXCRCSECUREDOFMASTERCONFIG == STD_ON)
  if (CanTSyn_GetTxCrcSecuredOfMasterConfig(masterIdx) == CANTSYN_SUPPORTED_TXCRCSECUREDOFMASTERCONFIG)
#  endif
  {
#  if (CANTSYN_EXISTS_CRC_OFFSET_CRCANDDOMAINTYPEOFDOMAINCONFIG == STD_ON)
#   if (CANTSYN_EXISTS_CRC_SYNC_CRCANDDOMAINTYPEOFDOMAINCONFIG == STD_ON)
    if (CanTSyn_GetOffsetDomainOfDomainConfig(domainIdx) == CANTSYN_OFFSET_OFFSETDOMAINOFDOMAINCONFIG)
#   endif
    {
      /* #70 Add the message type for type of the domain */
      CanTSyn_CanSignal_SetType(syncMsg, CANTSYN_TIME_SYNC_MESSAGE_TYPE_OFS_CRC); /* SBSW_CANTSYN_WRITE_SYNCMSG */
    }
#  endif
#  if (CANTSYN_EXISTS_CRC_SYNC_CRCANDDOMAINTYPEOFDOMAINCONFIG == STD_ON)
#   if (CANTSYN_EXISTS_CRC_OFFSET_CRCANDDOMAINTYPEOFDOMAINCONFIG == STD_ON)
   if (CanTSyn_GetOffsetDomainOfDomainConfig(domainIdx) == CANTSYN_NOT_OFFSET_OFFSETDOMAINOFDOMAINCONFIG)
#   endif
    {
      CanTSyn_CanSignal_SetType(syncMsg, CANTSYN_TIME_SYNC_MESSAGE_TYPE_SYNC_CRC); /* SBSW_CANTSYN_WRITE_SYNCMSG */
    }
#  endif

    /* #80 calculate DataID as DataIDList[SC] */
    dataId = CanTSyn_GetSyncDataIDList(CanTSyn_GetSyncDataIDListStartIdxOfDomainConfig(domainIdx) + counter);

    /* #90 Generate CRC and add to message */
    crcResult = Crc_CalculateCRC8H2F(&(syncMsg[2]), 6u, CANTSYN_CRC_START_VALUE, TRUE); /* SBSW_CANTSYN_WRITE_SYNCMSG */
    crcResult = Crc_CalculateCRC8H2F(&dataId, 1u, crcResult, FALSE); /* SBSW_CANTSYN_FUNCTIONCALL_LOCALPTR */
    CanTSyn_CanSignal_SetCRC(syncMsg, crcResult); /* SBSW_CANTSYN_WRITE_SYNCMSG */
  }
# endif

  retVal = CanIf_Transmit(CanTSyn_GetTxPduIdOfMasterConfig(masterIdx), &pduInfo); /* SBSW_CANTSYN_FUNCTIONCALL_PDUINFO */
  /* #100 If transmission on interface succeeded */
  if (retVal == E_OK)
  {
    /* #110 Set master state to CANTSYN_STATE_SEND_WAITING_FOR_SYNC_TX_CONFIRMATION and reset master timeouts */
    CanTSyn_SetStateOfMasterState(masterIdx, CANTSYN_STATE_SEND_WAITING_FOR_SYNC_TX_CONFIRMATION); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
    CanTSyn_SetTxIntervalCountOfMasterState(masterIdx, CanTSyn_GetTxPeriodOfMasterConfig(masterIdx)); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
    CanTSyn_SetMasterConfTimeoutCountOfMasterState(masterIdx, CanTSyn_GetMasterConfTimeoutOfMasterConfig(masterIdx)); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
    CanTSyn_SetPduIdStates(CanTSyn_GetPduIdStatesIdxOfMasterConfig(masterIdx), TRUE); /* SBSW_CANTSYN_ACCESS_PDUIDSTATES */
  }

  SchM_Exit_CanTSyn_CANTSYN_EXCLUSIVE_AREA_0();

  return retVal;

} /* CanTSyn_TransmitSync() */

/**********************************************************************************************************************
 *  CanTSyn_TransmitFup()
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
 */
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_TransmitFup(
  CanTSyn_DomainConfigIterType domainIdx, 
  CanTSyn_MasterConfigIterType masterIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  PduInfoType pduInfo;
  CanTSyn_CanMsgType fupMsg;
  uint8 counter;
# if (CANTSYN_EXISTS_SUPPORTED_TXCRCSECUREDOFMASTERCONFIG == STD_ON)
  uint8 crcResult, dataId;
# endif

  /* ----- Implementation ----------------------------------------------- */
  SchM_Enter_CanTSyn_CANTSYN_EXCLUSIVE_AREA_0();

  pduInfo.SduLength  = CANTSYN_TIME_SYNC_MESSAGE_DLC;
  pduInfo.SduDataPtr = fupMsg;

# if (CANTSYN_EXISTS_OFFSET_OFFSETDOMAINOFDOMAINCONFIG == STD_ON)
  /* #10 Add unconditioned information depending on the type of domain to the message */
  if (CanTSyn_GetDomainIdOfDomainConfig(domainIdx) >= CANTSYN_START_OFFSET_TIME_DOMAIN_ID)
  {
    /* Domain numbers of offset time bases (16-31) are carried in TimeSync messages as Domain number - 16 */
    CanTSyn_CanSignal_SetD(fupMsg, CanTSyn_GetDomainIdOfDomainConfig(domainIdx) - CANTSYN_START_OFFSET_TIME_DOMAIN_ID); /* SBSW_CANTSYN_WRITE_FUPMSG */
    /* write high bytes of secondsHi of Offset Time Base to OfsTimeSecMsbHi */
    CanTSyn_CanSignal_SetSecHi(fupMsg, (uint8)(CanTSyn_GetSyncTimestampOfMasterState(masterIdx).secondsHi >> 8u)); /* SBSW_CANTSYN_WRITE_FUPMSG */
    /* write nanosecond portion of Offset Time Base to OfsTimeNSec */                               /* CanTSyn_CanSignal_SetTime has four separate accesses to the message buffer. Therefore we need four review helper justifications */
    CanTSyn_CanSignal_SetTime(fupMsg, CanTSyn_GetSyncTimestampOfMasterState(masterIdx).nanoseconds) /* SBSW_CANTSYN_WRITE_FUPMSG */ /* SBSW_CANTSYN_WRITE_FUPMSG */ /* SBSW_CANTSYN_WRITE_FUPMSG */ /* SBSW_CANTSYN_WRITE_FUPMSG */
  }
  else
# endif
  {
    CanTSyn_CanSignal_SetD(fupMsg, CanTSyn_GetDomainIdOfDomainConfig(domainIdx)); /* SBSW_CANTSYN_WRITE_FUPMSG */
    /* set reserved bits to default value 0 */
    CanTSyn_CanSignal_ClearReservedFup(fupMsg); /* SBSW_CANTSYN_WRITE_FUPMSG */ 
    CanTSyn_CanSignal_SetSGW(fupMsg, CanTSyn_GetSyncToGatewayBit(CanTSyn_GetSyncTimestampOfMasterState(masterIdx).timeBaseStatus)); /* PRQA S 2985 */ /* MD_CanTSyn_Rule2.2_2985 */ /* SBSW_CANTSYN_WRITE_FUPMSG */
    /* write second portion of T4 to OVS */
    CanTSyn_CanSignal_SetOVS(fupMsg, CanTSyn_GetFupTimeStampOfMasterState(masterIdx).seconds); /* SBSW_CANTSYN_WRITE_FUPMSG */
    /* write nanosecond portion of T4 to SyncTimeNSec */                                           /* CanTSyn_CanSignal_SetTime has four separate accesses to the message buffer. Therefore we need four review helper justifications */ 
    CanTSyn_CanSignal_SetTime(fupMsg, CanTSyn_GetFupTimeStampOfMasterState(masterIdx).nanoseconds); /* SBSW_CANTSYN_WRITE_FUPMSG */ /* SBSW_CANTSYN_WRITE_FUPMSG */ /* SBSW_CANTSYN_WRITE_FUPMSG */ /* SBSW_CANTSYN_WRITE_FUPMSG */
   }

  /* #20 Add the SC to the message */
  counter = CanTSyn_GetTxSequenceCounterOfMasterState(masterIdx);
  CanTSyn_CanSignal_SetSC(fupMsg, counter); /* SBSW_CANTSYN_WRITE_FUPMSG */

# if (CANTSYN_EXISTS_NOT_SUPPORTED_TXCRCSECUREDOFMASTERCONFIG == STD_ON)
#  if (CANTSYN_EXISTS_SUPPORTED_TXCRCSECUREDOFMASTERCONFIG == STD_ON)
  /* #30 Add the message type and user data for the type of the domain */
  if (CanTSyn_GetTxCrcSecuredOfMasterConfig(masterIdx) == CANTSYN_NOT_SUPPORTED_TXCRCSECUREDOFMASTERCONFIG)
#  endif
  {
#  if (CANTSYN_EXISTS_NOT_CRC_OFFSET_CRCANDDOMAINTYPEOFDOMAINCONFIG == STD_ON)
#   if (CANTSYN_EXISTS_NOT_CRC_SYNC_CRCANDDOMAINTYPEOFDOMAINCONFIG == STD_ON)
    if (CanTSyn_GetOffsetDomainOfDomainConfig(domainIdx) == CANTSYN_OFFSET_OFFSETDOMAINOFDOMAINCONFIG)
#   endif
    {
      CanTSyn_CanSignal_SetType(fupMsg, CANTSYN_TIME_SYNC_MESSAGE_TYPE_OFNS_NOT_CRC); /* SBSW_CANTSYN_WRITE_FUPMSG */
      /* set reserved byte to default value 0 */
      CanTSyn_CanSignal_SetReservedOfs(fupMsg, 0u); /* SBSW_CANTSYN_WRITE_FUPMSG */
    }
#  endif
#  if (CANTSYN_EXISTS_NOT_CRC_SYNC_CRCANDDOMAINTYPEOFDOMAINCONFIG == STD_ON)
#   if (CANTSYN_EXISTS_NOT_CRC_OFFSET_CRCANDDOMAINTYPEOFDOMAINCONFIG == STD_ON)
    if (CanTSyn_GetOffsetDomainOfDomainConfig(domainIdx) == CANTSYN_NOT_OFFSET_OFFSETDOMAINOFDOMAINCONFIG)
#   endif
    {
      CanTSyn_CanSignal_SetType(fupMsg, CANTSYN_TIME_SYNC_MESSAGE_TYPE_FUP_NOT_CRC); /* SBSW_CANTSYN_WRITE_FUPMSG */
      CanTSyn_CanSignal_SetUserByte2(fupMsg, CanTSyn_GetUserDataOfMasterState(masterIdx).userByte2); /* SBSW_CANTSYN_WRITE_FUPMSG */
    }
#  endif
  }
# endif

# if (CANTSYN_EXISTS_SUPPORTED_TXCRCSECUREDOFMASTERCONFIG == STD_ON)
#  if (CANTSYN_EXISTS_NOT_SUPPORTED_TXCRCSECUREDOFMASTERCONFIG == STD_ON)
  if (CanTSyn_GetTxCrcSecuredOfMasterConfig(masterIdx) == CANTSYN_SUPPORTED_TXCRCSECUREDOFMASTERCONFIG)
#  endif
  {
#  if (CANTSYN_EXISTS_CRC_OFFSET_CRCANDDOMAINTYPEOFDOMAINCONFIG == STD_ON)
#   if (CANTSYN_EXISTS_CRC_SYNC_CRCANDDOMAINTYPEOFDOMAINCONFIG == STD_ON)
    if (CanTSyn_GetOffsetDomainOfDomainConfig(domainIdx) == CANTSYN_OFFSET_OFFSETDOMAINOFDOMAINCONFIG)
#   endif
    {
      /* #40 Add the message type for type of the domain */
      CanTSyn_CanSignal_SetType(fupMsg, CANTSYN_TIME_SYNC_MESSAGE_TYPE_OFNS_CRC); /* SBSW_CANTSYN_WRITE_FUPMSG */
    }
#  endif
#  if (CANTSYN_EXISTS_CRC_SYNC_CRCANDDOMAINTYPEOFDOMAINCONFIG == STD_ON)
#   if (CANTSYN_EXISTS_CRC_OFFSET_CRCANDDOMAINTYPEOFDOMAINCONFIG == STD_ON)
   if (CanTSyn_GetOffsetDomainOfDomainConfig(domainIdx) == CANTSYN_NOT_OFFSET_OFFSETDOMAINOFDOMAINCONFIG)
#   endif
    {
      CanTSyn_CanSignal_SetType(fupMsg, CANTSYN_TIME_SYNC_MESSAGE_TYPE_FUP_CRC); /* SBSW_CANTSYN_WRITE_FUPMSG */
    }
#  endif

    /* #50 calculate DataID as DataIDList[SC] */
    dataId = CanTSyn_GetFupDataIDList(CanTSyn_GetFupDataIDListStartIdxOfDomainConfig(domainIdx) + counter);

    /* #60 Generate CRC and add to message */
    crcResult = Crc_CalculateCRC8H2F(&(fupMsg[2]), 6u, CANTSYN_CRC_START_VALUE, TRUE); /* SBSW_CANTSYN_WRITE_FUPMSG */
    crcResult = Crc_CalculateCRC8H2F(&dataId, 1u, crcResult, FALSE); /* SBSW_CANTSYN_FUNCTIONCALL_LOCALPTR */
    CanTSyn_CanSignal_SetCRC(fupMsg, crcResult); /* SBSW_CANTSYN_WRITE_FUPMSG */
  }
# endif

  /* #70 Transmit message on interface */
  if (CanIf_Transmit(CanTSyn_GetTxPduIdOfMasterConfig(masterIdx), &pduInfo) == E_OK) /* SBSW_CANTSYN_FUNCTIONCALL_PDUINFO */
  {
    /* #80 If transmission on interface succeeded, set master state to CANTSYN_STATE_SEND_WAITING_FOR_FOLLOW_UP_TX_CONFIRMATION and reset confirmation timeout */
    CanTSyn_SetStateOfMasterState(masterIdx, CANTSYN_STATE_SEND_WAITING_FOR_FOLLOW_UP_TX_CONFIRMATION); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
    CanTSyn_SetMasterConfTimeoutCountOfMasterState(masterIdx, CanTSyn_GetMasterConfTimeoutOfMasterConfig(masterIdx)); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
  }

  SchM_Exit_CanTSyn_CANTSYN_EXCLUSIVE_AREA_0();

} /* CanTSyn_TransmitFup() */

/**********************************************************************************************************************
 *  CanTSyn_IncrementSequenceCounter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_IncrementSequenceCounter(CanTSyn_MasterConfigIterType masterIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 If sequence counter overflow occurs */
  if (CanTSyn_GetTxSequenceCounterOfMasterState(masterIdx) == CANTSYN_MAX_SEQUENCE_COUNTER)
  {
    /* #20 Reset sequence counter */
    CanTSyn_SetTxSequenceCounterOfMasterState(masterIdx, 0u); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
  }
  else
  {
    /* #30 Increment sequence counter */
    CanTSyn_IncTxSequenceCounterOfMasterState(masterIdx); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
  }

} /* CanTSyn_IncrementSequenceCounter() */

/**********************************************************************************************************************
 *  CanTSyn_HandleMasterRole()
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
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_HandleMasterRole(
  CanTSyn_DomainConfigIterType domainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  CanTSyn_MasterConfigIterType masterCount, masterIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the domain has at least one master role */
  
    /* #20 Iterate over all masters of the domain */
    for (masterCount = 0u; masterCount < CanTSyn_GetMasterConfigLengthOfDomainConfig(domainIdx); masterCount++)
    {
      masterIdx = CanTSyn_GetMasterConfigStartIdxOfDomainConfig(domainIdx) + masterCount;

      /* #30 TxPeriod Handling */
      if (CanTSyn_GetTxIntervalCountOfMasterState(masterIdx) > 0u)
      {
        CanTSyn_DecTxIntervalCountOfMasterState(masterIdx); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
      }

      /* #40 MasterConfTimeout Handling */
      if (CanTSyn_GetMasterConfTimeoutCountOfMasterState(masterIdx) > 0u)
      {
        CanTSyn_DecMasterConfTimeoutCountOfMasterState(masterIdx); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
      }

# if (CANTSYN_EXISTS_SUPPORTED_IMMEDIATETIMESYNCOFMASTERCONFIG == STD_ON)
#  if (CANTSYN_EXISTS_NOT_SUPPORTED_IMMEDIATETIMESYNCOFMASTERCONFIG == STD_ON)
      if ((CanTSyn_GetImmediateTimeSyncOfMasterConfig(masterIdx) == CANTSYN_SUPPORTED_IMMEDIATETIMESYNCOFMASTERCONFIG) && (CanTSyn_GetCyclicMsgResumeCounterOfMasterState(masterIdx) > 0u))
#  else
      if (CanTSyn_GetCyclicMsgResumeCounterOfMasterState(masterIdx) > 0u)
#  endif
      {
        /* #50 CyclicMsgResumeCounter Handling */
        CanTSyn_DecCyclicMsgResumeCounterOfMasterState(masterIdx); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
      }
# endif
      /* #60 Message transmission handling */
      CanTSyn_ProcessSend(domainIdx, masterIdx);
    }
  
} /* CanTSyn_HandleMasterRole() */

/**********************************************************************************************************************
 *  CanTSyn_SendMessage()
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
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_SendMessage(
  CanTSyn_DomainConfigIterType domainIdx,
  CanTSyn_MasterConfigIterType masterIdx)
{
  /* ----- Implementation ----------------------------------------------- */
# if (CANTSYN_EXISTS_SUPPORTED_IMMEDIATETIMESYNCOFMASTERCONFIG == STD_ON)
  /* #10 If ImmediateTimeSync is enabled */
#  if (CANTSYN_EXISTS_NOT_SUPPORTED_IMMEDIATETIMESYNCOFMASTERCONFIG == STD_ON)
  if (CanTSyn_GetImmediateTimeSyncOfMasterConfig(masterIdx) == CANTSYN_SUPPORTED_IMMEDIATETIMESYNCOFMASTERCONFIG)
#  endif
  {
    uint8 currentUpdateCounter;
    Std_ReturnType retVal;

    /* #20 Get current TimeBaseUpdateCounter from StbM */
    currentUpdateCounter = StbM_GetTimeBaseUpdateCounter(CanTSyn_GetTimeBaseIdOfDomainConfig(domainIdx));
    
    /* #30 If the TimeBaseUpdateCounter has changed */
    if (currentUpdateCounter != CanTSyn_GetLastUpdateCounterOfMasterState(masterIdx))
    {
      /* #40 Save the current TimeBaseUpdateCounter, send a Sync message and set CyclicMsgResumeCounter */
      CanTSyn_SetLastUpdateCounterOfMasterState(masterIdx, currentUpdateCounter); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
      retVal = CanTSyn_PrepareAndSendSync(domainIdx, masterIdx);
      if (retVal == E_OK)
      {
        CanTSyn_SetCyclicMsgResumeCounterOfMasterState(masterIdx, CanTSyn_GetCyclicMsgResumeTimeOfMasterConfig(masterIdx)); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
      }
    }
    else
    {
      /* #50 Send a message, if master Tx period has expired and CyclicMsgResumeCounter is not running */
      if ((CanTSyn_GetTxIntervalCountOfMasterState(masterIdx) == 0u) && (CanTSyn_GetCyclicMsgResumeCounterOfMasterState(masterIdx) == 0u))
      {
        (void)CanTSyn_PrepareAndSendSync(domainIdx, masterIdx);
      }
    }
  }
#  if (CANTSYN_EXISTS_NOT_SUPPORTED_IMMEDIATETIMESYNCOFMASTERCONFIG == STD_ON)
  else
#  endif
# endif

# if (CANTSYN_EXISTS_NOT_SUPPORTED_IMMEDIATETIMESYNCOFMASTERCONFIG == STD_ON)
  {
    /* #60 Send a message, if master Tx timeout has expired */
    if (CanTSyn_GetTxIntervalCountOfMasterState(masterIdx) == 0u)
    {
      (void)CanTSyn_PrepareAndSendSync(domainIdx, masterIdx);
    }
  }
# endif
} /* CanTSyn_SendMessage() */

/**********************************************************************************************************************
 *  CanTSyn_PrepareAndSendFUPMsg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 * \trace DSGN-CanTSyn22809
 */
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_PrepareAndSendFUPMsg(
  CanTSyn_DomainConfigIterType domainIdx,
  CanTSyn_MasterConfigIterType masterIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  StbM_TimeStampType syncTime;
  StbM_TimeStampRawType syncTimestampRaw, fupTimestampRaw;

  /* ----- Implementation ----------------------------------------------- */
# if (CANTSYN_EXISTS_OFFSET_OFFSETDOMAINOFDOMAINCONFIG == STD_ON)
  /* #10 Prepare transmission of FUP message */
  if (CanTSyn_GetDomainIdOfDomainConfig(domainIdx) >= CANTSYN_START_OFFSET_TIME_DOMAIN_ID)
  {
    /* #30 Set state to CANTSYN_STATE_SEND_WAITING_FOR_FOLLOW_UP_SEND */
    CanTSyn_SetStateOfMasterState(masterIdx, CANTSYN_STATE_SEND_WAITING_FOR_FOLLOW_UP_SEND); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
  }
  else
# endif
  {
    /* retrieve time difference T0diff of the transmission delay */
    SchM_Enter_CanTSyn_CANTSYN_EXCLUSIVE_AREA_0();
    syncTimestampRaw = CanTSyn_GetSyncTimestampRawOfMasterState(masterIdx);
    (void)StbM_GetCurrentTimeDiff(CanTSyn_GetTimeBaseIdOfDomainConfig(domainIdx), syncTimestampRaw, &fupTimestampRaw); /* SBSW_CANTSYN_FUNCTIONCALL_LOCALPTR */

    /* calculate T4 for FUP message as T4 = (T0ns + T0diff) with T0ns as nanosecond portion of T0 */
    syncTime.secondsHi = 0u;
    syncTime.seconds = 0u;
    syncTime.nanoseconds = CanTSyn_GetSyncTimestampOfMasterState(masterIdx).nanoseconds;

    CanTSyn_TimestampPlusTimestampRaw(&syncTime, &fupTimestampRaw, &CanTSyn_GetFupTimeStampOfMasterState(masterIdx)); /* SBSW_CANTSYN_ACCESS_MASTERSTATE_AND_LOCALPTR */
    /* #20 Set state to CANTSYN_STATE_SEND_WAITING_FOR_FOLLOW_UP_SEND */
    CanTSyn_SetStateOfMasterState(masterIdx, CANTSYN_STATE_SEND_WAITING_FOR_FOLLOW_UP_SEND); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
    SchM_Exit_CanTSyn_CANTSYN_EXCLUSIVE_AREA_0();
  }
# if (CANTSYN_EXISTS_OFFSET_OFFSETDOMAINOFDOMAINCONFIG == STD_OFF)
  CANTSYN_DUMMY_STATEMENT(domainIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* CanTSyn_PrepareAndSendFUPMsg() */

/**********************************************************************************************************************
 *  CanTSyn_PrepareAndSendSync()
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
 * \trace DSGN-CanTSyn22759
 */
CANTSYN_LOCAL_INLINE FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_PrepareAndSendSync(
  CanTSyn_DomainConfigIterType domainIdx,
  CanTSyn_MasterConfigIterType masterIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
# if (CANTSYN_EXISTS_OFFSET_OFFSETDOMAINOFDOMAINCONFIG == STD_ON)
  /* #10 If domain is an offset domain */
  if (CanTSyn_GetDomainIdOfDomainConfig(domainIdx) >= CANTSYN_START_OFFSET_TIME_DOMAIN_ID)
  {
    /* #20 get Offset Time Base */
    retVal = StbM_GetOffset(CanTSyn_GetTimeBaseIdOfDomainConfig(domainIdx), &CanTSyn_GetSyncTimestampOfMasterState(masterIdx)); /* PRQA S 2841 */ /* MD_CanTSyn_Dir4.1_2841 */ /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
  }
  else
# endif
  {
    /* #30 get Synchronized Time Base T0 */
    SchM_Enter_CanTSyn_CANTSYN_EXCLUSIVE_AREA_0();
    retVal = StbM_GetCurrentTime(CanTSyn_GetTimeBaseIdOfDomainConfig(domainIdx), &CanTSyn_GetSyncTimestampOfMasterState(masterIdx), &CanTSyn_GetUserDataOfMasterState(masterIdx)); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
    /* #40 If previous operations succeeded and GlobalTimeBaseBit is set */    
    if ((retVal == E_OK) && (CanTSyn_GetGlobalTimeBaseBit(CanTSyn_GetSyncTimestampOfMasterState(masterIdx).timeBaseStatus) != 0u))
    {
      /* #50 get raw time T0raw for time measurement of transmission delay */
      retVal = StbM_GetCurrentTimeRaw(CanTSyn_GetTimeBaseIdOfDomainConfig(domainIdx), &CanTSyn_GetSyncTimestampRawOfMasterState(masterIdx));  /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
    }
    SchM_Exit_CanTSyn_CANTSYN_EXCLUSIVE_AREA_0();
  }

  /* #60 If previous operations succeeded and GlobalTimeBaseBit is set */
  if ((retVal == E_OK) && (CanTSyn_GetGlobalTimeBaseBit(CanTSyn_GetSyncTimestampOfMasterState(masterIdx).timeBaseStatus) != 0u))
  {
    retVal = CanTSyn_TransmitSync(domainIdx, masterIdx);
  }

  return retVal;
} /* CanTSyn_PrepareAndSendSync() */

/**********************************************************************************************************************
 *  CanTSyn_CheckMsgConfirmation()
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
CANTSYN_LOCAL_INLINE FUNC(CanTSyn_DomainConfigIterType, CANTSYN_CODE) CanTSyn_CheckMsgConfirmation(PduIdType TxPduId)
{
  /* ----- Local Variables ---------------------------------------------- */
  CanTSyn_MasterConfigIterType masterIdx;
  CanTSyn_DomainConfigIterType domainIdx;
  boolean foundMaster = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  domainIdx = CANTSYN_INV_DOMAIN_IDX;
  for (masterIdx = 0u; masterIdx < CanTSyn_GetSizeOfMasterConfig(); masterIdx++)
  {
    /* #10 If the confirmation belongs to a SYNC or OFS message */
    if (CanTSyn_GetMasterConfHandleIdOfMasterConfig(masterIdx) == TxPduId)
    {
      domainIdx = CanTSyn_GetDomainConfigIdxOfMasterConfig(masterIdx);
      if (CanTSyn_GetStateOfMasterState(masterIdx) == CANTSYN_STATE_SEND_WAITING_FOR_SYNC_TX_CONFIRMATION)
      {
        CanTSyn_PrepareAndSendFUPMsg(domainIdx, masterIdx);
        foundMaster = TRUE;
      }
      else 
      {
        /* #20 If the confirmation belongs to a FUP message */
        if (CanTSyn_GetStateOfMasterState(masterIdx) == CANTSYN_STATE_SEND_WAITING_FOR_FOLLOW_UP_TX_CONFIRMATION)
        {
          /* #30 Set master state to CANTSYN_STATE_SEND_WAITING_FOR_SYNC_SEND */
          CanTSyn_SetStateOfMasterState(masterIdx, CANTSYN_STATE_SEND_WAITING_FOR_SYNC_SEND); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
          CanTSyn_SetPduIdStates(CanTSyn_GetPduIdStatesIdxOfMasterConfig(masterIdx), FALSE); /* SBSW_CANTSYN_ACCESS_PDUIDSTATES */
          foundMaster = TRUE;
        }
      }
      if (foundMaster == TRUE)
      {
        /* #40 Disable master confirmation timeout */
        CanTSyn_SetMasterConfTimeoutCountOfMasterState(masterIdx, 0u); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */

# if (CANTSYN_TXDEBOUNCECOUNTERIDXOFMASTERCONFIG == STD_ON)
        /* #50 Start debounce timer for this TxPduId */
        CanTSyn_SetTxDebounceCounter(CanTSyn_GetTxDebounceCounterIdxOfMasterConfig(masterIdx), CanTSyn_GetDebounceTimeOfMasterConfig(masterIdx)); /* SBSW_CANTSYN_ACCESS_MASTERSTATE */
# endif
        break;
      }
    }
  }
  return domainIdx;
} /* CanTSyn_CheckMsgConfirmation() */

/**********************************************************************************************************************
 *  CanTSyn_InitPduIdStates()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_InitPduIdStates(void)
{
  CanTSyn_PduIdStatesIterType pduIdIdx;
  for (pduIdIdx = 0; pduIdIdx < CanTSyn_GetSizeOfPduIdStates(); pduIdIdx++)
  {
    /* #10 Initialize each index with false */
    CanTSyn_SetPduIdStates(pduIdIdx, FALSE); /* SBSW_CANTSYN_ACCESS_PDUIDSTATES */
  }
}
#endif

#if (CANTSYN_SLAVECONFIG == STD_ON)
/**********************************************************************************************************************
 *  CanTSyn_ProcessReceive()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 * \trace DSGN-CanTSyn22814, DSGN-CanTSyn22815
 */
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_ProcessReceive(uint8 slaveIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  switch (CanTSyn_GetStateOfSlaveState(slaveIdx))
  {
    /* #10 If the slave is in state CANTSYN_STATE_RECEIVE_WAITING_FOR_FOLLOW_UP */
    case CANTSYN_STATE_RECEIVE_WAITING_FOR_FOLLOW_UP:
      /* #20 check for FollowUp received timeout */
      SchM_Enter_CanTSyn_CANTSYN_EXCLUSIVE_AREA_0();
      if (CanTSyn_GetRxFollowUpTimeoutCountOfSlaveState(slaveIdx) == 0u)
      {
        /* #30 Set slave state to CANTSYN_STATE_RECEIVE_WAITING_FOR_SYNC, if the timeout expired */
        CanTSyn_SetStateOfSlaveState(slaveIdx, CANTSYN_STATE_RECEIVE_WAITING_FOR_SYNC); /* SBSW_CANTSYN_ACCESS_SLAVESTATE */
      }
      SchM_Exit_CanTSyn_CANTSYN_EXCLUSIVE_AREA_0();
      break;
    default: /* COV_CANTSYN_MSR_MISRA */
      break;
  }

} /* CanTSyn_ProcessReceive() */

/**********************************************************************************************************************
 *  CanTSyn_HandleSync()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_HandleSync(
  uint8 slaveIdx,
  P2CONST(PduInfoType, AUTOMATIC, CANTSYN_APPL_DATA) pduInfoPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  SchM_Enter_CanTSyn_CANTSYN_EXCLUSIVE_AREA_0();

  /* #10 get Synchronized Time Base part T0 delivered with SYNC message */
  CanTSyn_MemCpy(CanTSyn_GetSyncMsgOfSlaveState(slaveIdx), pduInfoPtr->SduDataPtr, sizeof(CanTSyn_GetSyncMsgOfSlaveState(slaveIdx))); /* SBSW_CANTSYN_MEMCPY_SYNCMSG */

  /* #20 Set slave state to CANTSYN_STATE_RECEIVE_WAITING_FOR_FOLLOW_UP */
  CanTSyn_SetStateOfSlaveState(slaveIdx, CANTSYN_STATE_RECEIVE_WAITING_FOR_FOLLOW_UP); /* SBSW_CANTSYN_ACCESS_SLAVESTATE */

  /* #30 set FollowUp receive timeout time */
  CanTSyn_SetRxFollowUpTimeoutCountOfSlaveState(slaveIdx, CanTSyn_GetFollowUpTimeoutOfSlaveConfig(slaveIdx)); /* PRQA S 2842 */ /* MD_CanTSyn_Dir4.1_2842 */ /* SBSW_CANTSYN_ACCESS_SLAVESTATE */

  SchM_Exit_CanTSyn_CANTSYN_EXCLUSIVE_AREA_0();

} /* CanTSyn_HandleSync() */

/**********************************************************************************************************************
 *  CanTSyn_HandleFup()
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
 *
 */
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_HandleFup(
  CanTSyn_DomainConfigIterType domainIdx, uint8 slaveIdx,
  P2CONST(PduInfoType, AUTOMATIC, CANTSYN_APPL_DATA) pduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
# if ((CANTSYN_EXISTS_IGNORED_RXCRCVALIDATEDOFSLAVECONFIG == STD_ON) || ((CANTSYN_EXISTS_VALIDATED_RXCRCVALIDATEDOFSLAVECONFIG == STD_ON) && (CANTSYN_EXISTS_NOT_VALIDATED_RXCRCVALIDATEDOFSLAVECONFIG == STD_ON)))
  uint8 messageType;
# endif
  uint32 syncSeconds;
  StbM_TimeStampType syncTime, actualTime;
  StbM_TimeStampRawType fupTimestampRaw;
  StbM_UserDataType userData;
  StbM_MeasurementType measureData;

  /* ----- Implementation ----------------------------------------------- */
  SchM_Enter_CanTSyn_CANTSYN_EXCLUSIVE_AREA_0();
  measureData.pathDelay = 0;
# if (CANTSYN_EXISTS_OFFSET_OFFSETDOMAINOFDOMAINCONFIG == STD_ON)
  /* #10 If the domain is an offset domain */
  if (CanTSyn_GetDomainIdOfDomainConfig(domainIdx) >= CANTSYN_START_OFFSET_TIME_DOMAIN_ID)
  {
    /* #20 assemble second portion of the offset time base */
    actualTime.secondsHi = CanTSyn_CanSignal_GetSecHi(CanTSyn_GetSyncMsgOfSlaveState(slaveIdx)) + ((uint16)CanTSyn_CanSignal_GetSecHi(pduInfoPtr->SduDataPtr) << 8u);
    actualTime.seconds = CanTSyn_CanSignal_GetTime(CanTSyn_GetSyncMsgOfSlaveState(slaveIdx));
    /* #30 get nanosecond portion of the offset time */
    actualTime.nanoseconds = CanTSyn_CanSignal_GetTime(pduInfoPtr->SduDataPtr);
    SchM_Exit_CanTSyn_CANTSYN_EXCLUSIVE_AREA_0();

    /* #40 Set offset time base */
    (void)StbM_BusSetGlobalTime(CanTSyn_GetTimeBaseIdOfDomainConfig(domainIdx), &actualTime, NULL_PTR, &measureData); /* PRQA S 2841 */ /* MD_CanTSyn_Dir4.1_2841 */ /* SBSW_CANTSYN_FUNCTIONCALL_LOCALPTR */
  }
  else
# endif
  {
    /* #50 Handle user data considering if Crc is used */
    userData.userByte0 = CanTSyn_CanSignal_GetUserByte0(CanTSyn_GetSyncMsgOfSlaveState(slaveIdx));

# if ((CANTSYN_EXISTS_VALIDATED_RXCRCVALIDATEDOFSLAVECONFIG == STD_ON) || (CANTSYN_EXISTS_IGNORED_RXCRCVALIDATEDOFSLAVECONFIG == STD_ON))
#  if ((CANTSYN_EXISTS_NOT_VALIDATED_RXCRCVALIDATEDOFSLAVECONFIG == STD_ON) || (CANTSYN_EXISTS_IGNORED_RXCRCVALIDATEDOFSLAVECONFIG == STD_ON))
    messageType = CanTSyn_CanSignal_GetType(pduInfoPtr->SduDataPtr);
    if (CanTSyn_IsFupCrcSecured(messageType))
#  endif
    {
      userData.userDataLength = 1u;
    }
# endif

# if ((CANTSYN_EXISTS_NOT_VALIDATED_RXCRCVALIDATEDOFSLAVECONFIG == STD_ON) || (CANTSYN_EXISTS_IGNORED_RXCRCVALIDATEDOFSLAVECONFIG == STD_ON))
#  if ((CANTSYN_EXISTS_VALIDATED_RXCRCVALIDATEDOFSLAVECONFIG == STD_ON) || (CANTSYN_EXISTS_IGNORED_RXCRCVALIDATEDOFSLAVECONFIG == STD_ON))
    messageType = CanTSyn_CanSignal_GetType(pduInfoPtr->SduDataPtr);
    if (!CanTSyn_IsFupCrcSecured(messageType))
#  endif
    {
      /* user bytes 1 and 2 are only used if the message is not crc secured */
      userData.userByte1 = CanTSyn_CanSignal_GetUserByte1(CanTSyn_GetSyncMsgOfSlaveState(slaveIdx));
      userData.userByte2 = CanTSyn_CanSignal_GetUserByte2(pduInfoPtr->SduDataPtr);
      userData.userDataLength = 3u;
    }
# endif

    /* #60 calculate T0 + T4 */
    syncSeconds = CanTSyn_CanSignal_GetTime(CanTSyn_GetSyncMsgOfSlaveState(slaveIdx));
    syncTime.seconds = syncSeconds + CanTSyn_CanSignal_GetOVS(pduInfoPtr->SduDataPtr);
    if (syncTime.seconds < syncSeconds)
    {
      syncTime.secondsHi = 1u;
    }
    else
    {
      syncTime.secondsHi = 0u;
    }

    /* #70 get Synchronized Time Base part T4 delivered with FUP message */
    syncTime.nanoseconds = CanTSyn_CanSignal_GetTime(pduInfoPtr->SduDataPtr);

    /* #80 If retrieving of the time difference between T3raw and T2raw succeeds */
    if (StbM_GetCurrentTimeDiff(CanTSyn_GetTimeBaseIdOfDomainConfig(domainIdx), CanTSyn_GetSyncTimestampRawOfSlaveState(slaveIdx), &fupTimestampRaw) == E_OK) /* SBSW_CANTSYN_FUNCTIONCALL_LOCALPTR */
    {
      /* #90 calculate GlobalTimeBase as GlobalTimeBase = (T3raw - T2raw) + (T0 + T4) */
      CanTSyn_TimestampPlusTimestampRaw(&syncTime, &fupTimestampRaw, &actualTime); /* SBSW_CANTSYN_FUNCTIONCALL_LOCALPTR */

      /* #100 Get timebase status from message */
      if (CanTSyn_CanSignal_GetSGW(pduInfoPtr->SduDataPtr) == 0u)
      {
        actualTime.timeBaseStatus = 0x00u;
      }
      else
      {
        actualTime.timeBaseStatus = StbM_Sync_To_Gateway_BflMask;
      }

      /* #110 Pass information to StbM */
      (void)StbM_BusSetGlobalTime(CanTSyn_GetTimeBaseIdOfDomainConfig(domainIdx), &actualTime, &userData, &measureData); /* SBSW_CANTSYN_FUNCTIONCALL_LOCALPTR */
    }
    SchM_Exit_CanTSyn_CANTSYN_EXCLUSIVE_AREA_0();
  }

  /* #120 Set slave state to CANTSYN_STATE_RECEIVE_WAITING_FOR_SYNC and deactivate FollowUp received timeout */
  CanTSyn_SetStateOfSlaveState(slaveIdx, CANTSYN_STATE_RECEIVE_WAITING_FOR_SYNC); /* SBSW_CANTSYN_ACCESS_SLAVESTATE */
  CanTSyn_SetRxFollowUpTimeoutCountOfSlaveState(slaveIdx, 0u); /* SBSW_CANTSYN_ACCESS_SLAVESTATE */
} /* CanTSyn_HandleFup() */

/**********************************************************************************************************************
 *  CanTSyn_CheckRxSequenceCounter()
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
CANTSYN_LOCAL_INLINE FUNC(Std_ReturnType, CANTSYN_CODE) CanTSyn_CheckRxSequenceCounter(CanTSyn_DomainConfigIterType domainIdx, uint8 slaveIdx, uint8 counter)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 counterJumpWidth;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Sequence Counter of first received message is not checked*/
  if (CanTSyn_GetRxSequenceCounterOfSlaveState(slaveIdx) <= CANTSYN_MAX_SEQUENCE_COUNTER)
  {
    StbM_TimeBaseStatusType syncTimeBaseStatus;
    StbM_TimeBaseStatusType offsetTimeBaseStatus;

    /* #20 Calculate Sequence Counter Jump Width from last received Sequence Counter */
    if (counter < CanTSyn_GetRxSequenceCounterOfSlaveState(slaveIdx))
    {
      counterJumpWidth = (CANTSYN_MAX_SEQUENCE_COUNTER - CanTSyn_GetRxSequenceCounterOfSlaveState(slaveIdx)) + counter + 1u;
    }
    else
    {
      counterJumpWidth = counter - CanTSyn_GetRxSequenceCounterOfSlaveState(slaveIdx);
    }

    /* #30 Check for stuck Sequence Counter */
    if (counterJumpWidth > 0u)
    {
      /* #40 Sequence Counter Jump Width is only checked, if status retrieval failed or no timeout occurred */
      retVal = StbM_GetTimeBaseStatus(CanTSyn_GetTimeBaseIdOfDomainConfig(domainIdx), &syncTimeBaseStatus, &offsetTimeBaseStatus); /* SBSW_CANTSYN_FUNCTIONCALL_LOCALPTR */

      if ((retVal == E_NOT_OK) || (CanTSyn_GetTimeoutBit(syncTimeBaseStatus) == 0u))
      {
        /* #50 Check if Sequence Counter Jump Width is in the permitted range */
        if (counterJumpWidth <= CanTSyn_GetSequenceCounterJumpWidthOfSlaveConfig(slaveIdx)) /* PRQA S 2842 */ /* MD_CanTSyn_Dir4.1_2842 */
        {
          retVal = E_OK;
        }
        else
        {
          retVal = E_NOT_OK;
        }
      }
    }
    else
    {
      retVal = E_NOT_OK;
    }
  }
  else
  {
    retVal = E_OK;
  }

  /* #60 Update last received Sequence Counter */
  CanTSyn_SetRxSequenceCounterOfSlaveState(slaveIdx, counter); /* SBSW_CANTSYN_ACCESS_SLAVESTATE */

  return retVal;

} /* CanTSyn_CheckRxSequenceCounter() */

/**********************************************************************************************************************
 *  CanTSyn_CheckSyncMsg()
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
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_CheckSyncMsg(
  P2CONST(PduInfoType, AUTOMATIC, CANTSYN_APPL_DATA) PduInfoPtr,
  CanTSyn_DomainConfigIterType domainIdx,
  uint8 slaveIdx,
  uint8 messageType)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 counter;
# if (CANTSYN_EXISTS_VALIDATED_RXCRCVALIDATEDOFSLAVECONFIG == STD_ON)
  uint8 crcResult, dataId;
# endif

  /* ----- Implementation ----------------------------------------------- */
  counter = CanTSyn_CanSignal_GetSC(PduInfoPtr->SduDataPtr);

  /* #10 check if SC matches to the expected value */
  if (CanTSyn_CheckRxSequenceCounter(domainIdx, slaveIdx, counter) == E_OK)
  {
    switch (CanTSyn_GetRxCrcValidatedOfSlaveConfig(slaveIdx))
    {
# if (CANTSYN_EXISTS_IGNORED_RXCRCVALIDATEDOFSLAVECONFIG == STD_ON)
      case CANTSYN_IGNORED_RXCRCVALIDATEDOFSLAVECONFIG:
        CanTSyn_HandleSync(slaveIdx, PduInfoPtr); /* SBSW_CANTSYN_FUNCTIONCALL_PARAMPTR */
        break;
# endif
# if (CANTSYN_EXISTS_NOT_VALIDATED_RXCRCVALIDATEDOFSLAVECONFIG == STD_ON)
      case CANTSYN_NOT_VALIDATED_RXCRCVALIDATEDOFSLAVECONFIG:
        /* #20 check if Type matches depending on the CanTSynRxCrcValidated parameter */
        if (!CanTSyn_IsSyncCrcSecured(messageType))
        {
          CanTSyn_HandleSync(slaveIdx, PduInfoPtr); /* SBSW_CANTSYN_FUNCTIONCALL_PARAMPTR */
        }
        break;
# endif
# if (CANTSYN_EXISTS_VALIDATED_RXCRCVALIDATEDOFSLAVECONFIG == STD_ON)
      case CANTSYN_VALIDATED_RXCRCVALIDATEDOFSLAVECONFIG:
        /* #30 check if Type matches depending on the CanTSynRxCrcValidated parameter */
        if (CanTSyn_IsSyncCrcSecured(messageType))
        {
          /* #40 calculate CRC over received PDU */
          crcResult = Crc_CalculateCRC8H2F(&(PduInfoPtr->SduDataPtr[2]), 6u, CANTSYN_CRC_START_VALUE, TRUE); /* SBSW_CANTSYN_PDUPTR_PARAM */
          dataId = CanTSyn_GetSyncDataIDList(CanTSyn_GetSyncDataIDListStartIdxOfDomainConfig(domainIdx) + counter);
          crcResult = Crc_CalculateCRC8H2F(&dataId, 1u, crcResult, FALSE); /* SBSW_CANTSYN_FUNCTIONCALL_LOCALPTR */

          /* #50 check CRC */
          if (crcResult == CanTSyn_CanSignal_GetCRC(PduInfoPtr->SduDataPtr))
          {
            CanTSyn_HandleSync(slaveIdx, PduInfoPtr); /* SBSW_CANTSYN_FUNCTIONCALL_PARAMPTR */
          }
        }
        break;
# endif
      default: /* COV_CANTSYN_MSR_MISRA */
        break;
    }
  }
# if ((CANTSYN_EXISTS_NOT_VALIDATED_RXCRCVALIDATEDOFSLAVECONFIG == STD_OFF) && (CANTSYN_EXISTS_VALIDATED_RXCRCVALIDATEDOFSLAVECONFIG == STD_OFF))
  CANTSYN_DUMMY_STATEMENT(messageType); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if (CANTSYN_EXISTS_VALIDATED_RXCRCVALIDATEDOFSLAVECONFIG == STD_OFF)
  CANTSYN_DUMMY_STATEMENT(domainIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* CanTSyn_CheckSyncMsg() */

/**********************************************************************************************************************
 *  CanTSyn_CheckFupMsg()
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
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_CheckFupMsg(
  P2CONST(PduInfoType, AUTOMATIC, CANTSYN_APPL_DATA) PduInfoPtr,
  CanTSyn_DomainConfigIterType domainIdx,
  uint8 slaveIdx,
  uint8 messageType)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 counter;
# if (CANTSYN_EXISTS_VALIDATED_RXCRCVALIDATEDOFSLAVECONFIG == STD_ON)
  uint8 crcResult, dataId;
# endif

  /* ----- Implementation ----------------------------------------------- */
  counter = CanTSyn_CanSignal_GetSC(PduInfoPtr->SduDataPtr);

  /* #10 check if SC matches to the expected value and SyncTimeNSec matches the defined range of StbM_TimeStampType.nanoseconds */
  if ((counter != CanTSyn_CanSignal_GetSC(CanTSyn_GetSyncMsgOfSlaveState(slaveIdx))) || (CanTSyn_CanSignal_GetTime(PduInfoPtr->SduDataPtr) > CANTSYN_TIMESTAMP_MAX_NANOSECONDS))
  {
    CanTSyn_SetStateOfSlaveState(slaveIdx, CANTSYN_STATE_RECEIVE_WAITING_FOR_SYNC); /* SBSW_CANTSYN_ACCESS_SLAVESTATE */
    CanTSyn_SetRxFollowUpTimeoutCountOfSlaveState(slaveIdx, 0u); /* SBSW_CANTSYN_ACCESS_SLAVESTATE */
  }
  else
  {
    switch (CanTSyn_GetRxCrcValidatedOfSlaveConfig(slaveIdx))
    {
# if (CANTSYN_EXISTS_IGNORED_RXCRCVALIDATEDOFSLAVECONFIG == STD_ON)
      case CANTSYN_IGNORED_RXCRCVALIDATEDOFSLAVECONFIG:
        CanTSyn_HandleFup(domainIdx, slaveIdx, PduInfoPtr); /* SBSW_CANTSYN_FUNCTIONCALL_PARAMPTR */
        break;
# endif
# if (CANTSYN_EXISTS_NOT_VALIDATED_RXCRCVALIDATEDOFSLAVECONFIG == STD_ON)
      case CANTSYN_NOT_VALIDATED_RXCRCVALIDATEDOFSLAVECONFIG:
        /* #20 check if Type matches depending on the CanTSynRxCrcValidated parameter */
        if (!CanTSyn_IsFupCrcSecured(messageType))
        {
          CanTSyn_HandleFup(domainIdx, slaveIdx, PduInfoPtr); /* SBSW_CANTSYN_FUNCTIONCALL_PARAMPTR */
        }
        break;
# endif
# if (CANTSYN_EXISTS_VALIDATED_RXCRCVALIDATEDOFSLAVECONFIG == STD_ON)
      case CANTSYN_VALIDATED_RXCRCVALIDATEDOFSLAVECONFIG:
        /* #30 check if Type matches depending on the CanTSynRxCrcValidated parameter */
        if (CanTSyn_IsFupCrcSecured(messageType))
        {
          /* #40 calculate CRC over received PDU */
          crcResult = Crc_CalculateCRC8H2F(&(PduInfoPtr->SduDataPtr[2]), 6u, CANTSYN_CRC_START_VALUE, TRUE); /* SBSW_CANTSYN_FUNCTIONCALL_PARAMPTR */
          dataId = CanTSyn_GetFupDataIDList(CanTSyn_GetFupDataIDListStartIdxOfDomainConfig(domainIdx) + counter);
          crcResult = Crc_CalculateCRC8H2F(&dataId, 1u, crcResult, FALSE); /* SBSW_CANTSYN_FUNCTIONCALL_LOCALPTR */
          /* #50 check CRC */
          if (crcResult == CanTSyn_CanSignal_GetCRC(PduInfoPtr->SduDataPtr))
          {
            CanTSyn_HandleFup(domainIdx, slaveIdx, PduInfoPtr); /* SBSW_CANTSYN_FUNCTIONCALL_PARAMPTR */
          }
        }
        break;
# endif
      default: /* COV_CANTSYN_MSR_MISRA */
        break;
    }
  }
# if ((CANTSYN_EXISTS_NOT_VALIDATED_RXCRCVALIDATEDOFSLAVECONFIG == STD_OFF) && (CANTSYN_EXISTS_VALIDATED_RXCRCVALIDATEDOFSLAVECONFIG == STD_OFF))
  CANTSYN_DUMMY_STATEMENT(messageType); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* CanTSyn_CheckFupMsg() */

/**********************************************************************************************************************
 *  CanTSyn_CheckAndProcessMsg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
CANTSYN_LOCAL_INLINE FUNC(uint8, CANTSYN_CODE) CanTSyn_CheckAndProcessMsg(
  PduIdType RxPduId,
  P2CONST(PduInfoType, AUTOMATIC, CANTSYN_APPL_DATA) PduInfoPtr,
  uint8 domainId,
  uint8 messageType)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANTSYN_E_NO_ERROR;
  CanTSyn_DomainConfigIterType domainIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 check if the domain matches to one of the configured Time Domains */
  for (domainIdx = 0u; domainIdx < CanTSyn_GetSizeOfDomainConfig(); domainIdx++)
  {
    /* #20 check if the received PduId matches to the configured PduId */
    if (CanTSyn_GetDomainIdOfDomainConfig(domainIdx) == domainId) 
    {
# if (CanTSyn_GetSizeOfSlaveConfig() != CanTSyn_GetSizeOfDomainConfig())
      if (CanTSyn_IsSlaveConfigUsedOfDomainConfig(domainIdx) == TRUE) /* PRQA S 1881, 4304 */ /* MD_MSR_AutosarBoolean */
# endif
      {
        errorId = CanTSyn_CheckPduIdAndMsgReceivedStatus(RxPduId, PduInfoPtr, domainIdx, messageType); /* SBSW_CANTSYN_FUNCTIONCALL_PARAMPTR */
        break; 
      }
    }
  }
  return errorId;
} /* CanTSyn_CheckAndProcessMsg() */

/**********************************************************************************************************************
 *  CanTSyn_CheckPduIdAndMsgReceivedStatus()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
CANTSYN_LOCAL_INLINE FUNC(uint8, CANTSYN_CODE) CanTSyn_CheckPduIdAndMsgReceivedStatus(PduIdType RxPduId,
  P2CONST(PduInfoType, AUTOMATIC, CANTSYN_APPL_DATA) PduInfoPtr,
  CanTSyn_DomainConfigIterType domainIdx,
  uint8 messageType)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 slaveIdx;
  uint8 errorId = CANTSYN_E_NO_ERROR;

  /* ----- Implementation ----------------------------------------------- */
  slaveIdx = CanTSyn_GetSlaveConfigIdxOfDomainConfig(domainIdx);    
  /* #10 If the received PduId matches to the configured PduId */
  if (CanTSyn_GetSlaveHandleIdOfSlaveConfig(slaveIdx) == RxPduId)
  {
    /* #20 check message */
    CanTSyn_CheckMessage(PduInfoPtr, domainIdx, slaveIdx, messageType); /* SBSW_CANTSYN_FUNCTIONCALL_PARAMPTR */
  }
# if (CANTSYN_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* #30 Domain has configured different RxPduId */
    errorId = CANTSYN_E_INVALID_PDUID;
  }
# endif
  return errorId;
} /* CanTSyn_CheckPduIdAndMsgReceivedStatus() */

/**********************************************************************************************************************
 *  CanTSyn_CheckMessage()
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
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_CheckMessage(
  P2CONST(PduInfoType, AUTOMATIC, CANTSYN_APPL_DATA) PduInfoPtr,
  CanTSyn_DomainConfigIterType domainIdx,
  uint8 slaveIdx,
  uint8 messageType)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 check if SYNC or OFS message was received and expected */
  if ((CanTSyn_GetStateOfSlaveState(slaveIdx) == CANTSYN_STATE_RECEIVE_WAITING_FOR_SYNC) && 
# if (CANTSYN_EXISTS_OFFSET_OFFSETDOMAINOFDOMAINCONFIG == STD_ON)
    (CanTSyn_IsSyncMsg(messageType) || CanTSyn_IsOfsMsg(messageType)))
# else
    (CanTSyn_IsSyncMsg(messageType)))
# endif
  {
    Std_ReturnType retVal = E_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

# if (CANTSYN_EXISTS_OFFSET_OFFSETDOMAINOFDOMAINCONFIG == STD_ON)
    if (CanTSyn_GetDomainIdOfDomainConfig(domainIdx) < CANTSYN_START_OFFSET_TIME_DOMAIN_ID)
# endif
    {
      SchM_Enter_CanTSyn_CANTSYN_EXCLUSIVE_AREA_0();

      /* #20 on SYNC message Rx indication retrieve Local Time Stamp as T2raw */
      retVal = StbM_GetCurrentTimeRaw(CanTSyn_GetTimeBaseIdOfDomainConfig(domainIdx), &CanTSyn_GetSyncTimestampRawOfSlaveState(slaveIdx)); /* SBSW_CANTSYN_ACCESS_SLAVESTATE */
      SchM_Exit_CanTSyn_CANTSYN_EXCLUSIVE_AREA_0();
    }

    if (retVal == E_OK)
    {
      /* #30 check received message */
      CanTSyn_CheckSyncMsg(PduInfoPtr, domainIdx, slaveIdx, messageType); /* SBSW_CANTSYN_FUNCTIONCALL_PARAMPTR */
    }
  }
  else 
  {	  
    /* #40 check if FUP or OFNS message was received and expected */
    if ((CanTSyn_GetStateOfSlaveState(slaveIdx) == CANTSYN_STATE_RECEIVE_WAITING_FOR_FOLLOW_UP) && 
# if (CANTSYN_EXISTS_OFFSET_OFFSETDOMAINOFDOMAINCONFIG == STD_ON)
      (CanTSyn_IsFupMsg(messageType) || CanTSyn_IsOfnsMsg(messageType))) 
# else
      (CanTSyn_IsFupMsg(messageType))) 
# endif
    {
      /* #50 check received message */
      CanTSyn_CheckFupMsg(PduInfoPtr, domainIdx, slaveIdx, messageType); /* SBSW_CANTSYN_FUNCTIONCALL_PARAMPTR */
    }
  }      
} /* CanTSyn_CheckMessage() */


/**********************************************************************************************************************
 *  CanTSyn_CheckTypeOfMessage()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
CANTSYN_LOCAL_INLINE FUNC(uint8, CANTSYN_CODE) CanTSyn_CheckTypeOfMessage(uint8 messageType, uint8 domainId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 updatedDomainId = domainId;
  
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the type of message and update domainId */
  if (CanTSyn_IsOfsMsg(messageType) || CanTSyn_IsOfnsMsg(messageType))
  {
    /* TimeSync messages of Offset Time Bases carry the Domain number - 16 */
    updatedDomainId += CANTSYN_START_OFFSET_TIME_DOMAIN_ID;
  }

  return updatedDomainId;
} /* CanTSyn_CheckTypeOfMessage() */

/**********************************************************************************************************************
 *  CanTSyn_MemCpy()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
CANTSYN_LOCAL_INLINE FUNC(void, CANTSYN_CODE) CanTSyn_MemCpy(
  P2VAR(uint8, AUTOMATIC, CANTSYN_APPL_VAR) destination,
  P2CONST(uint8, AUTOMATIC, CANTSYN_APPL_DATA) source,
  uint8 count)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 i;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 copy from source to destination */
  for (i = count; i > 0u; i--)
  {
    destination[i - 1u] = source[i - 1u]; /* SBSW_CANTSYN_MEMCPY */
  }

} /* CanTSyn_MemCpy() */

#endif

 /**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

 /**********************************************************************************************************************
 *  CanTSyn_InitMemory()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, CANTSYN_CODE)  CanTSyn_InitMemory(void)
{
  /* ----- Implementation ----------------------------------------------- */
#if (CANTSYN_DEV_ERROR_DETECT == STD_ON)
  CanTSyn_SetInitialized(FALSE); /* SBSW_CANTSYN_ACCESS_CSL_VAR */
#endif

} /* CanTSyn_InitMemory() */

/**********************************************************************************************************************
 *  CanTSyn_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 * \trace DSGN-CanTSyn22753
 */
FUNC(void, CANTSYN_CODE) CanTSyn_Init(P2CONST(CanTSyn_ConfigType, AUTOMATIC, CANTSYN_APPL_DATA) configPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  CanTSyn_DomainConfigIterType domainIdx;
#if (CANTSYN_MASTERCONFIG == STD_ON)
  CanTSyn_ControllerIdListIterType canControllerIdx;
#endif

#if (CANTSYN_TXDEBOUNCECOUNTERIDXOFMASTERCONFIG == STD_ON)
  CanTSyn_TxDebounceCounterIterType txDebounceCounterIdx;
#endif

  /* ----- Implementation ----------------------------------------------- */
  CANTSYN_DUMMY_STATEMENT(configPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Init all domains */
  for (domainIdx = 0u; domainIdx < CanTSyn_GetSizeOfDomainConfig(); domainIdx++)
  {
    CanTSyn_InitDomain(domainIdx);
  }
#if (CANTSYN_MASTERCONFIG == STD_ON)
  /* #20 Init controller index and state */
  for (canControllerIdx = 0u; canControllerIdx < CanTSyn_GetSizeOfCanControllerIdStates(); canControllerIdx++)
  {
    CanTSyn_SetCanControllerIdStates(canControllerIdx, CANTSYN_TX_ON); /* SBSW_CANTSYN_ACCESS_CONTROLLERIDSTATES */
  }

# if (CANTSYN_TXDEBOUNCECOUNTERIDXOFMASTERCONFIG == STD_ON)
  /* #30 Init TxDebounceCounter */
  for (txDebounceCounterIdx = 0u; txDebounceCounterIdx < CanTSyn_GetSizeOfTxDebounceCounter(); txDebounceCounterIdx++)
  {
    CanTSyn_SetTxDebounceCounter(txDebounceCounterIdx, 0u); /* SBSW_CANTSYN_ACCESS_TXDEBOUNCECOUNTER */
  }
# endif
  CanTSyn_InitPduIdStates();
#endif

#if (CANTSYN_DEV_ERROR_DETECT == STD_ON)
  CanTSyn_SetInitialized(TRUE); /* SBSW_CANTSYN_ACCESS_CSL_VAR */
#endif

} /* CanTSyn_Init() */

#if (CANTSYN_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  CanTSyn_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, CANTSYN_CODE) CanTSyn_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CANTSYN_APPL_VAR) versioninfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANTSYN_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (CANTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameter versioninfo for NULL pointer */
  if (versioninfo == NULL_PTR)
  {
    errorId = CANTSYN_E_NULL_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Set versioninfo with corresponding macros from component header */
    versioninfo->vendorID = (CANTSYN_VENDOR_ID); /* SBSW_CANTSYN_VERSIONINFOPTR */
    versioninfo->moduleID = (CANTSYN_MODULE_ID); /* SBSW_CANTSYN_VERSIONINFOPTR */
    versioninfo->sw_major_version = (CANTSYN_SW_MAJOR_VERSION); /* SBSW_CANTSYN_VERSIONINFOPTR */
    versioninfo->sw_minor_version = (CANTSYN_SW_MINOR_VERSION); /* SBSW_CANTSYN_VERSIONINFOPTR */
    versioninfo->sw_patch_version = (CANTSYN_SW_PATCH_VERSION); /* SBSW_CANTSYN_VERSIONINFOPTR */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CANTSYN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(CANTSYN_MODULE_ID, CANTSYN_INSTANCE_ID_DET, CANTSYN_SID_GET_VERSION_INFO, errorId);
  }
# else
  CANTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif

} /* CanTSyn_GetVersionInfo() */
#endif /* (CANTSYN_VERSION_INFO_API == STD_ON) */

/**********************************************************************************************************************
 *  CanTSyn_MainFunction()
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
FUNC(void, CANTSYN_CODE) CanTSyn_MainFunction(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANTSYN_E_NO_ERROR;
  CanTSyn_DomainConfigIterType domainIdx;
#if (CANTSYN_SLAVECONFIG == STD_ON)
  uint8 slaveIdx;
#endif
#if (CANTSYN_TXDEBOUNCECOUNTERIDXOFMASTERCONFIG == STD_ON)
  CanTSyn_TxDebounceCounterIterType txDebounceCounterIdx;
#endif

  /* ----- Development Error Checks ------------------------------------- */
#if (CANTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check initialization state of the component */
  if(CanTSyn_IsInitialized() == FALSE) /* PRQA S 1881 */ /* MD_MSR_AutosarBoolean */
  {
    errorId = CANTSYN_E_UNINIT;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Iterate over all domains */
    for (domainIdx = 0u; domainIdx < CanTSyn_GetSizeOfDomainConfig(); domainIdx++)
    {
#if (CANTSYN_SLAVECONFIG == STD_ON)
# if (CanTSyn_GetSizeOfSlaveConfig() != CanTSyn_GetSizeOfDomainConfig())
      /* #30 If the domain has a slave */
      if (CanTSyn_IsSlaveConfigUsedOfDomainConfig(domainIdx) == TRUE) /* PRQA S 1881, 4304 */ /* MD_MSR_AutosarBoolean */
# endif
      {
        slaveIdx = CanTSyn_GetSlaveConfigIdxOfDomainConfig(domainIdx);

        /* #40 Rx Timeout Handling */
        SchM_Enter_CanTSyn_CANTSYN_EXCLUSIVE_AREA_0();
        if (CanTSyn_GetRxFollowUpTimeoutCountOfSlaveState(slaveIdx) > 0u)
        {
          CanTSyn_DecRxFollowUpTimeoutCountOfSlaveState(slaveIdx); /* SBSW_CANTSYN_ACCESS_SLAVESTATE */
        }
        SchM_Exit_CanTSyn_CANTSYN_EXCLUSIVE_AREA_0();

        /* #50 Process the received message */
        CanTSyn_ProcessReceive(slaveIdx);
      }
#endif

#if (CANTSYN_MASTERCONFIG == STD_ON)
      /* #60 Handle the masters of the domain */
      CanTSyn_HandleMasterRole(domainIdx);   
#endif
    }

#if (CANTSYN_TXDEBOUNCECOUNTERIDXOFMASTERCONFIG == STD_ON)
    /* #70 DebounceCounter Handling */
    for (txDebounceCounterIdx = 0u; txDebounceCounterIdx < CanTSyn_GetSizeOfTxDebounceCounter(); txDebounceCounterIdx++)
    {
      if (CanTSyn_GetTxDebounceCounter(txDebounceCounterIdx) > 0u)
      {
        CanTSyn_DecTxDebounceCounter(txDebounceCounterIdx); /* SBSW_CANTSYN_ACCESS_TXDEBOUNCECOUNTER */
      }
    }
#endif
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CANTSYN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(CANTSYN_MODULE_ID, CANTSYN_INSTANCE_ID_DET, CANTSYN_SID_MAIN_FUNCTION, errorId);
  }
#else
  CANTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif

} /* CanTSyn_MainFunction() */

#if (CANTSYN_MASTERCONFIG == STD_ON)
/**********************************************************************************************************************
 *  CanTSyn_TxConfirmation()
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, CANTSYN_CODE) CanTSyn_TxConfirmation(PduIdType TxPduId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANTSYN_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (CANTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check initialization state of the component */
  if(CanTSyn_IsInitialized() == FALSE) /* PRQA S 1881 */ /* MD_MSR_AutosarBoolean */
  {
    errorId = CANTSYN_E_UNINIT;
  }
  else
# endif
  {
    CanTSyn_DomainConfigIterType domainIdx;
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Check message confirmation message and set state accordingly. */
    domainIdx = CanTSyn_CheckMsgConfirmation(TxPduId);        

# if (CANTSYN_DEV_ERROR_DETECT == STD_ON)
    if (domainIdx == CANTSYN_INV_DOMAIN_IDX)
    {
      /* found no corresponding domain index -> drop message */
      errorId = CANTSYN_E_INVALID_PDUID;
    }
# else
    CANTSYN_DUMMY_STATEMENT(domainIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CANTSYN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(CANTSYN_MODULE_ID, CANTSYN_INSTANCE_ID_DET, CANTSYN_SID_TX_CONFIRMATION, errorId);
  }
# else
  CANTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif

} /* CanTSyn_TxConfirmation() */

/**********************************************************************************************************************
 *  CanTSyn_SetTransmissionMode()
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
FUNC(void, CANTSYN_CODE) CanTSyn_SetTransmissionMode(uint8 CtrlIdx, CanTSyn_TransmissionModeType Mode)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANTSYN_E_NO_ERROR;
  CanTSyn_ControllerIdListIterType canControllerIdx;
# if (CANTSYN_DEV_ERROR_DETECT == STD_ON)
  boolean foundCtrlIdx = FALSE;
# endif

  /* ----- Development Error Checks ------------------------------------- */
# if (CANTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check initialization state of the component */
  if(CanTSyn_IsInitialized() == FALSE) /* PRQA S 1881 */ /* MD_MSR_AutosarBoolean */
  {
    errorId = CANTSYN_E_UNINIT;
  }
  /* #20 Check if mode is invalid */
  else if ((Mode != CANTSYN_TX_OFF) && (Mode != CANTSYN_TX_ON))
  {
    errorId = CANTSYN_E_PARAM;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Search for CAN controllers with given CtrlIdx */
    for (canControllerIdx = 0u; canControllerIdx < CanTSyn_GetSizeOfControllerIdList(); canControllerIdx++)
    {
      if (CanTSyn_GetControllerIdList(canControllerIdx) == CtrlIdx)
      {
        /* #40 Set transmission mode to given mode */
        CanTSyn_SetCanControllerIdStates(canControllerIdx, Mode); /* SBSW_CANTSYN_ACCESS_CONTROLLERIDSTATES */
# if (CANTSYN_DEV_ERROR_DETECT == STD_ON)
        foundCtrlIdx = TRUE;
# endif
        break;
      }
    }
# if (CANTSYN_DEV_ERROR_DETECT == STD_ON)
    if (foundCtrlIdx == FALSE)
    {
      /* #50 Controller Id is invalid */
      errorId = CANTSYN_E_INV_CTRL_IDX;
    }
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CANTSYN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(CANTSYN_MODULE_ID, CANTSYN_INSTANCE_ID_DET, CANTSYN_SID_SET_TRANSMISSION_MODE, errorId);
  }
# else
  CANTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif

} /* CanTSyn_SetTransmissionMode() */
#endif

#if (CANTSYN_SLAVECONFIG == STD_ON)
/**********************************************************************************************************************
 *  CanTSyn_RxIndication()
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
FUNC(void, CANTSYN_CODE) CanTSyn_RxIndication(
  PduIdType RxPduId, 
  P2CONST(PduInfoType, AUTOMATIC, CANTSYN_APPL_DATA) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANTSYN_E_NO_ERROR;
  uint8 domainId, messageType;

  /* ----- Development Error Checks ------------------------------------- */
# if (CANTSYN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check initialization state of the component */
  if(CanTSyn_IsInitialized() == FALSE) /* PRQA S 1881 */ /* MD_MSR_AutosarBoolean */
  {
    errorId = CANTSYN_E_UNINIT;
  }
  /* #20 Check parameter 'PduInfoPtr' for NULL pointer */
  else if (PduInfoPtr == NULL_PTR)
  {
    errorId = CANTSYN_E_NULL_POINTER;
  }
  /* #30 Check parameter 'PduInfoPtr->SduDataPtr' */
  else if (PduInfoPtr->SduDataPtr == NULL_PTR)
  {
    errorId = CANTSYN_E_NULL_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #40 check DLC of received message */
    if (PduInfoPtr->SduLength == CANTSYN_TIME_SYNC_MESSAGE_DLC)
    {
      /* #45 Set domainId and messageType based on the received message */
      domainId = CanTSyn_CanSignal_GetD(PduInfoPtr->SduDataPtr);
      messageType = CanTSyn_CanSignal_GetType(PduInfoPtr->SduDataPtr);
      domainId = CanTSyn_CheckTypeOfMessage(messageType, domainId);

      /* #50 check and process received message */
# if (CANTSYN_DEV_ERROR_DETECT == STD_ON)
      errorId = CanTSyn_CheckAndProcessMsg(RxPduId, PduInfoPtr, domainId, messageType); /* SBSW_CANTSYN_FUNCTIONCALL_PARAMPTR */
# else
      (void)CanTSyn_CheckAndProcessMsg(RxPduId, PduInfoPtr, domainId, messageType); /* SBSW_CANTSYN_FUNCTIONCALL_PARAMPTR */
# endif
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CANTSYN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(CANTSYN_MODULE_ID, CANTSYN_INSTANCE_ID_DET, CANTSYN_SID_RX_INDICATION, errorId);
  }
# else 
  CANTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif

} /* CanTSyn_RxIndication() */
#endif

#define CANTSYN_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Justification for module-specific MISRA deviations:
 MD_CanTSyn_Dir4.1_2841:
      Reason:     A function parameter is used to access an array element. The parameter is always passed by an internal function that ensures that the parameter is in a valid range.
      Risk:       Runtime failure might be introduced by later code changes.
      Prevention: Covered by code review.
 MD_CanTSyn_Dir4.1_2842:
      Reason:     A function parameter is used to access an array element. The parameter is always passed by an internal function that ensures that the parameter is in a valid range.
      Risk:       Runtime failure might be introduced by later code changes.
      Prevention: Covered by code review.
 MD_CanTSyn_Rule2.2_2985:
      Reason:     A function like macro is implemented to handle different argument values. In the special case a part of the macro is not required.
      Risk:       no risk
      Prevention: Covered by code review.
*/

/* Safe BSW assumptions:
  Indirections:
    DomainConfig->SlaveConfig  1:0..1
    DomainConfig->MasterConfig 1:0..N
    MasterConfig->PduIdStates  1:1
    MasterConfig->ControllerIdStates  1:1
    MasterConfig->TxDebounceCounter   1:1

  Size Constraints:
    SlaveConfig  <-> SlaveState
    MasterConfig <-> MasterState

  These assumptions are modelled in ComStackLib
*/

/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_CANTSYN_ACCESS_PDUIDSTATES
  \DESCRIPTION Write access to PduIdStates using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

  \ID SBSW_CANTSYN_ACCESS_CONTROLLERIDSTATES
  \DESCRIPTION Write access to ControllerIdStates using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

  \ID SBSW_CANTSYN_ACCESS_TXDEBOUNCECOUNTER
  \DESCRIPTION Write access to TxDebounceCounter using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

  \ID SBSW_CANTSYN_ACCESS_SLAVESTATE
  \DESCRIPTION Write access to SlaveState or referencing from SlaveState using ComStackLib. The index comes from the caller calculated by indirection of the DomainConfig.
               The DomainIndex is given as parameter on external interfaces or by iterating over the domains in the mainfunction.
  \COUNTERMEASURE \N Qualified use-case CSL02 and CSL03 of ComStackLib

  \ID SBSW_CANTSYN_ACCESS_MASTERSTATE
  \DESCRIPTION Write access to MasterState or referencing from MasterState using ComStackLib. The index comes from the caller calculated by indirection of the DomainConfig.
               The DomainIndex is given as parameter on external interfaces or by iterating over the domains in the mainfunction.
  \COUNTERMEASURE \N Qualified use-case CSL02 and CSL03 of ComStackLib

  \ID SBSW_CANTSYN_ACCESS_CSL_VAR
  \DESCRIPTION A ComStackLib generated variable is accessed.
  \COUNTERMEASURE \N The variable is written using a generated macro of the CSL. It immediately dereferences the variables address without pointer arithmetic.
  
  \ID SBSW_CANTSYN_MEMCPY_SYNCMSG
  \DESCRIPTION Call to MemCpy with SyncMsgOfSlaveState as destination buffer. The index comes from the caller calculated by indirection of the DomainConfig.
               The DomainIndex is given as parameter on external interfaces or by iterating over the domains in the mainfunction.
               The size parameter is calculated using sizeof(). The source parameter is a constant pointer.
  \COUNTERMEASURE \N Qualified use-case CSL02 and CSL03 of ComStackLib

  \ID SBSW_CANTSYN_FUNCTIONCALL_LOCALPTR
  \DESCRIPTION Call of a function with pointer parameters where the pointers are pointing to local (stack) objects.
  \COUNTERMEASURE \N Compiler ensures validity of the pointers.

  \ID SBSW_CANTSYN_FUNCTIONCALL_PARAMPTR
  \DESCRIPTION Forwarding the pointer that was given as parameter, without modifying anything.
  \COUNTERMEASURE \N Caller ensures validity of the pointers.

  \ID SBSW_CANTSYN_ACCESS_MASTERSTATE_AND_LOCALPTR
  \DESCRIPTION Write access to MasterState or referencing from MasterState using ComStackLib. The index comes from the caller calculated by indirection of the DomainConfig.
               The DomainIndex is given as parameter on external interfaces or by iterating over the domains in the mainfunction. And call of a function with pointer parameters 
               where the pointers are pointing to local (stack) objects.
  \COUNTERMEASURE \N Qualified use-case CSL02 and CSL03 of ComStackLib and compiler ensures validity of the pointers

  \ID SBSW_CANTSYN_FUNCTIONCALL_PDUINFO
  \DESCRIPTION Call of a function with pointer parameter where PduInfo is a reference to a local (stack) object. SduLength is set to 8 and SduPtr is a reference to a local array with 8 elements.
  \COUNTERMEASURE \N Compiler ensures validity of the pointers.

  \ID SBSW_CANTSYN_PDUPTR_PARAM
  \DESCRIPTION Passing a reference to the 3rd element of PduPtr->SduPtr that was given as parameter, without modifying anything. The size of the object referenced by SduPtr is checked in RxIndication.
  \COUNTERMEASURE \N RxIndication ensures validity of the pointers and size of the array.

  \ID SBSW_CANTSYN_MEMCPY
  \DESCRIPTION Copy bytes from source to destination.
  \COUNTERMEASURE \N Caller ensures validity of the pointers and length.

  \ID SBSW_CANTSYN_WRITE_SYNCMSG
  \DESCRIPTION Write access to sync message using the CanTSyn_CanSignal_* macros or referencing an element with a static index. The macros only access index 0..7. The syncMsg is a local (stack) object.
  \COUNTERMEASURE \N Compiler ensures validity of the pointers.

  \ID SBSW_CANTSYN_WRITE_FUPMSG
  \DESCRIPTION Write access to sync message using the CanTSyn_CanSignal_* macros. The macros only access index 0..7. The fupMsg is a local (stack) object.
  \COUNTERMEASURE \N Compiler ensures validity of the pointers.
  
  \ID SBSW_CANTSYN_TIMESUMPTR 
  \DESCRIPTION The function CanTSyn_TimestampPlusTimestampRaw writes to the object referenced by parameter timesumPtr. 
  \COUNTERMEASURE \N The caller ensures that the pointers passed to the  
                     parameters timesumPtr is valid. 

  \ID SBSW_CANTSYN_VERSIONINFOPTR 
  \DESCRIPTION The function CanTSyn_GetVersionInfo writes to the object referenced by parameter versioninfo. 
  \COUNTERMEASURE \N The caller ensures that the pointers passed to the  
                     parameters versioninfo is valid. 

SBSW_JUSTIFICATION_END */

/* COV_JUSTIFICATION_BEGIN

--- Preprocessor Coverage Justifications ------------------------------------------------------------------------------

  \ID COV_CANTSYN_MSR_COMPATIBILITY
  \ACCEPT TX 
  \REASON [COV_MSR_COMPATIBILITY]

  \ID COV_CANTSYN_MSR_MISRA
  \ACCEPT X 
  \REASON [COV_MSR_MISRA]

COV_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  END OF FILE: CanTSyn.c
 *********************************************************************************************************************/
