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
 *         \file  EthTSyn_Util_Int.h
 *        \brief  EthTSyn Util internal header file
 *
 *      \details  Contains internal definitions and declarations used by EthTSyn
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

#if !defined(ETHTSYN_UTIL_INT_H)
# define ETHTSYN_UTIL_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "IpBase.h"
# include "EthTSyn_GeneratedCfgAccess.h"
# include "EthTSyn_Types_Int.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# if !defined (ETHTSYN_LOCAL_INLINE) /* COV_MSR_COMPATIBILITY */
#  define ETHTSYN_LOCAL_INLINE  LOCAL_INLINE
# endif

# define ETHTSYN_INV_BUF_IDX  (0xFFu)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3412 MACRO_CODE */ /* MD_MSR_19.4 */
/* PRQA S 3453 FCT_MACRO */ /* MD_MSR_19.7 */
# define EthTSyn_Htons(HostShort16)                       IPBASE_HTON16(HostShort16)
# define EthTSyn_Htonl(HostLong32)                        IPBASE_HTON32(HostLong32)
# define EthTSyn_Ntohs(NetworkShort16)                    IPBASE_NTOH16(NetworkShort16)
# define EthTSyn_Ntohl(NetworkLong32)                     IPBASE_NTOH32(NetworkLong32)

# define ETHTSYN_PUT_UINT16(Buffer, Offset, Value)    (Buffer)[(Offset)+0] = (uint8)(((uint16_least)(Value)) >> 8u); \
                                                      (Buffer)[(Offset)+1] = (uint8)((uint16_least)(Value))

# define ETHTSYN_PUT_UINT32(Buffer, Offset, Value)    (Buffer)[(Offset)+0] = (uint8)(((uint32_least)(Value)) >> 24u); \
                                                      (Buffer)[(Offset)+1] = (uint8)(((uint32_least)(Value)) >> 16u); \
                                                      (Buffer)[(Offset)+2] = (uint8)(((uint32_least)(Value)) >>  8u); \
                                                      (Buffer)[(Offset)+3] = (uint8)((uint32_least)(Value))

# define ETHTSYN_PUT_3_BYTE(Buffer, Offset, Value)  \
  (Buffer)[(Offset)+0u] = (uint8)((((uint32_least)(Value)) >> 16u) & 0x000000FF); \
  (Buffer)[(Offset)+1u] = (uint8)((((uint32_least)(Value)) >> 8u) & 0x000000FF); \
  (Buffer)[(Offset)+2u] = (uint8)(((uint32_least)(Value)) & 0x000000FF)

# define ETHTSYN_GET_UINT16(Buffer, Offset, Variable)     IPBASE_GET_UINT16((Buffer), (Offset), (Variable))
# define ETHTSYN_GET_UINT32(Buffer, Offset, Variable)     IPBASE_GET_UINT32((Buffer), (Offset), (Variable))
# define ETHTSYN_GET_3_BYTE(Buffer, Offset, Variable)  ( (Variable) = (uint32)(((uint32)(0x00u) << 24u) | \
                                                                           ((uint32)((Buffer)[(Offset)+0u]) << 16u) | \
                                                                           ((uint32)((Buffer)[(Offset)+1u]) <<  8u) | \
                                                                           ((uint32)((Buffer)[(Offset)+2u]))) )

# define ETHTSYN_GET_FOLLOW_UP_CORRECTION_VALUE_NS_FROM_MSG(CorrectionFieldNbo)  ( (uint64)( \
  ((uint64)(CorrectionFieldNbo)[0] << 40U) | \
  ((uint64)(CorrectionFieldNbo)[1] << 32U) | \
  ((uint64)(CorrectionFieldNbo)[2] << 24U) | \
  ((uint64)(CorrectionFieldNbo)[3] << 16U) | \
  ((uint64)(CorrectionFieldNbo)[4] <<  8U) | \
  ((uint64)(CorrectionFieldNbo)[5] <<  0U)) )

# define EthTSyn_CopyFollowUpCorrectionField(FollowUpCorrectionValueNs, FollowUpCorrectionField)  \
  (FollowUpCorrectionField)[0] = (uint8)((FollowUpCorrectionValueNs) >> 40U); \
  (FollowUpCorrectionField)[1] = (uint8)((FollowUpCorrectionValueNs) >> 32U); \
  (FollowUpCorrectionField)[2] = (uint8)((FollowUpCorrectionValueNs) >> 24U); \
  (FollowUpCorrectionField)[3] = (uint8)((FollowUpCorrectionValueNs) >> 16U); \
  (FollowUpCorrectionField)[4] = (uint8)((FollowUpCorrectionValueNs) >>  8U); \
  (FollowUpCorrectionField)[5] = (uint8)((FollowUpCorrectionValueNs) >>  0U); \
  (FollowUpCorrectionField)[6] = 0; \
  (FollowUpCorrectionField)[7] = 0

# define ETHTSYN_COPY_STBM_TS_TO_GLOBAL_TS(StbmTimestamp, GlobalTimestamp) \
  (GlobalTimestamp).secondsHi   = (StbmTimestamp).secondsHi; \
  (GlobalTimestamp).seconds     = (StbmTimestamp).seconds;   \
  (GlobalTimestamp).nanoseconds = (StbmTimestamp).nanoseconds

# define ETHTSYN_COPY_GLOBAL_TS_TO_STBM_TS_WO_TBS(GlobalTimestamp, StbmTimestamp) \
  ETHTSYN_COPY_GLOBAL_TS_TO_STBM_TS_W_TBS((GlobalTimestamp), (StbmTimestamp), (0u))

# define ETHTSYN_COPY_GLOBAL_TS_TO_STBM_TS_W_TBS(GlobalTimestamp, StbmTimestamp, TimeBaseStatus) \
  (StbmTimestamp).timeBaseStatus = (TimeBaseStatus); \
  (StbmTimestamp).secondsHi      = (GlobalTimestamp).secondsHi; \
  (StbmTimestamp).seconds        = (GlobalTimestamp).seconds;   \
  (StbmTimestamp).nanoseconds    = (GlobalTimestamp).nanoseconds

# define ETHTSYN_TIME_BASE_STATUS_TO_AR_SUB_TLV_STATUS(StbmTimeBaseStatus, ArSubTlvStatus) \
  ((ArSubTlvStatus) = (uint8) \
  (((StbmTimeBaseStatus) & ETHTSYN_TIME_BASE_STATUS_SYNC_TO_GW_MASK) >> ETHTSYN_TIME_BASE_STATUS_SYNC_TO_GW_SHIFT))

# define ETHTSYN_AR_SUB_TLV_STATUS_TO_TIME_BASE_STATUS(ArSubTlvStatus, StbmTimeBaseStatus) \
  ((StbmTimeBaseStatus) = (uint8) \
  (((ArSubTlvStatus) << ETHTSYN_TIME_BASE_STATUS_SYNC_TO_GW_SHIFT) & ETHTSYN_TIME_BASE_STATUS_SYNC_TO_GW_MASK))


# define ETHTSYN_ENTER_CRITICAL_SECTION_0()   SchM_Enter_EthTSyn_ETHTSYN_EXCLUSIVE_AREA_0()
# define ETHTSYN_LEAVE_CRITICAL_SECTION_0()   SchM_Exit_EthTSyn_ETHTSYN_EXCLUSIVE_AREA_0()


/* PRQA L: MACRO_CODE */
/* PRQA L: FCT_MACRO */
/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETHTSYN_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_PrepareCommonMsgHdr
 *********************************************************************************************************************/
/*! \brief      Initializes the common message header.
 *  \details    Sets all required fields of the common message header (in Network-Byte-Order) according to the passed
 *              message type.
 *  \param[in]  ComMsgHdrPtr   Pointer to the common message header to be initialized
 *  \param[in]  MsgType        The type of the message the header should be prepared for
 *  \param[in]  PortIdx        Index of the EthTSyn Port the message will be transmitted on
 *                             [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TxBuffers
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_UtilTx_PrepareCommonMsgHdr(
  ETHTSYN_P2VAR(EthTSyn_CommonMsgHdrType) ComMsgHdrPtr,
                uint8                     MsgType,
                EthTSyn_IntPortIdxType    PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_HtonTimestamp
 *********************************************************************************************************************/
/*! \brief       Transforms the passed local timestamp into the timestamp format used for message transmission
 *               (including conversion to Network-Byte-Order).
 *  \details     -
 *  \param[out]  GlobalTimestampPtr    Pointer to the EthTSyn timestamp value (destination)
 *  \param[in]   LocalTimestampPtr     Pointer to the local timestamp value (source)
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different GlobalTimestamps
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_UtilTx_HtonTimestamp(
    ETHTSYN_P2VAR(EthTSyn_TimestampType)       GlobalTimestampPtr,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) LocalTimestampPtr);

/**********************************************************************************************************************
 *  EthTSyn_Util_TimestampPlusTimediff
 *********************************************************************************************************************/
/*! \brief          Adds the passed Timediff to the provided Timestamp.
 *  \details        -
 *  \param[in,out]  DestTimestampPtr   In:  The Timestamp the passed Timediff should be added too
 *                                     Out: The provided Timestamps with the added Timediff
 *  \param[in]      TimediffPtr        Pointer to where the time difference is stored
 *  \return         E_OK - Sum of added timestamps is valid
 *  \return         E_NOT_OK - Sum of added timestamps is invalid
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different Timestamps
 *  \note           DestTimestampPtr is only modified for return value of E_OK.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Util_TimestampPlusTimediff(
    ETHTSYN_P2VAR(EthTSyn_GlobalTimestampType) DestTimestampPtr,
  ETHTSYN_P2CONST(EthTSyn_TimediffType)        TimediffPtr);

/**********************************************************************************************************************
 *  EthTSyn_Util_TimestampMinusTimestamp
 *********************************************************************************************************************/
/*! \brief         Calculates the time difference between two passed Timestamps.
 *  \details       -
 *  \param[in]     Timestamp1Ptr          Pointer to first timestamp of the first timestamp
 *  \param[in]     Timestamp2Ptr          Pointer to second timestamp of the second timestamp
 *  \param[out]    TimediffPtr            Pointer to time difference between Timestamp1 and Timestamp2
 *  \return        E_OK - Timediff is valid
 *  \return        E_NOT_OK - Timediff is invalid
 *  \pre           -
 *  \context       TAKS|ISR2
 *  \reentrant     TRUE
 *  \note          Timediff = Timestamp1 - Timestamp2
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Util_TimestampMinusTimestamp(
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) Timestamp1Ptr,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) Timestamp2Ptr,
    ETHTSYN_P2VAR(EthTSyn_TimediffType)        TimediffPtr);

# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF)
#  if ( (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) || (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) )
/**********************************************************************************************************************
 *  EthTSyn_Util_CheckAndHandleRawTimestampOverflow
 *********************************************************************************************************************/
/*! \brief         Checks and handles a possible overflow between the given raw timestamps.
 *  \details       Timestamp1Ptr and Timestamp2Ptr both represent a raw timestamp retrieved by the StbM. It is assumed
 *                 that Timestamp2Ptr represent a later time than Timestamp1Ptr. Between the two timestamps a overflow
 *                 of the raw StbM time might have been occurred. The possible overflow is detected and handled here.
 *  \param[in]     Timestamp1Ptr       Pointer to timestamp of the first timestamp
 *                 [range: 0 - 2^32 - 1 nanoseconds]
 *  \param[in]     Timestamp2          The second timestamp as raw timestamp
 *                 [range: 0 - 2^32 - 1 nanoseconds]
 *  \return        Timestamp1 with applied overflow correction.
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *********************************************************************************************************************/
FUNC(EthTSyn_GlobalTimestampType, ETHTSYN_CODE) EthTSyn_Util_CheckAndHandleRawTimestampOverflow(
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) Timestamp1Ptr,
                  EthTSyn_TimestampRawType     Timestamp2);

/**********************************************************************************************************************
 *  EthTSyn_Util_RawTimeToTimestamp
 *********************************************************************************************************************/
/*! \brief         Converts a raw timestamp into an EthTSyn_GlobalTimestampType.
 *  \details       -
 *  \param[in]     RawTimestamp  The raw timestamp to be converted
 *                 [range: 0 - 2^32 - 1 nanoseconds]
 *  \return        RawTimestamp converted into an EthTSyn_GlobalTimestampType
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *********************************************************************************************************************/
FUNC(EthTSyn_GlobalTimestampType, ETHTSYN_CODE) EthTSyn_Util_RawTimeToTimestamp(
  EthTSyn_TimestampRawType RawTimestamp);
#  endif /* ( (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) || (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) ) */
# endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) */

/**********************************************************************************************************************
 *  EthTSyn_UtilRx_CheckMessageGeneral
 *********************************************************************************************************************/
/*! \brief      Performs general message checks.
 *  \details    Checks the Frame length and Message length carried in the header for plausibility and verifies the
 *              Protocol version.
 *  \param[in]  MsgPtr           Pointer to the message to be checked
 *  \param[in]  LenByte          Length of the message in Byte
 *  \return     ETHTSYN_E_NO_ERROR - Message checks passed. No error occurred.
 *  \return     other value - Message checks failed. Corresponding error id is returned.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(uint8, ETHTSYN_CODE) EthTSyn_UtilRx_CheckMessageGeneral(
    ETHTSYN_P2CONST(uint8)  MsgPtr,
                    uint16  LenByte);

/**********************************************************************************************************************
 *  EthTSyn_UtilRx_CheckMessageTypeAndLength
 *********************************************************************************************************************/
/*! \brief      Checks if the frame length and the message length of the common message header matches the message type.
 *  \details    Checks if the message type is valid and if the frame length and message length of the common header
 *              matches the message type.
 *  \param[in]  ComMsgHdrPtr    Pointer to the common message header to be checked
 *  \param[in]  LenByte         Length of the message in Byte
 *  \return     ETHTSYN_E_NO_ERROR - Message checks passed. No error occurred.
 *  \return     other value - Message checks failed. Corresponding error id is returned.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(uint8, ETHTSYN_CODE) EthTSyn_UtilRx_CheckMessageTypeAndLength(
    ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) ComMsgHdrPtr,
                    uint16                    LenByte);

# if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_UtilRx_QualifyAnnounceMsg
 *********************************************************************************************************************/
/*! \brief      Validates the passed Announce message.
 *  \details    Checks the Announce message field for plausibility and verifies the GrandMaster identity as well as the
 *              path trace sequence.
 *  \param[in]  PortIdx     Index of EthTSyn port that received the Announce message
 *                          [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  ComMsgPtr   Pointer to the EthTSyn common header of the Announce message
 *  \return     E_OK - Announce message is valid
 *  \return     E_NOT_OK - Announce message is not valid
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_UtilRx_QualifyAnnounceMsg(
                  EthTSyn_IntPortIdxType    PortIdx,
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) ComMsgPtr);
# endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_UtilRx_SyncPortRoleCheckWithMasterSlaveConflictDetection
 *********************************************************************************************************************/
/*! \brief      Performs Port Role check and handles Master-Slave conflict detection.
 *  \details    Verifies that the passed Port is a Slave Port and handles the Master-Slave conflict detection
 *              including optional announce and source port identity checks as well as the report of the possible
 *              runtime error.
 *  \param[in]  PortIdx            Index of EthTSyn port that received the Sync message
 *                                 [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  SrcClockIdentity   The source clock identity of the received Sync message
 *  \return     TRUE - Sync message was received on a Slave Port and no Master-Slave conflict was detected
 *  \return     FALSE - Sync message was received on a Master Port or a Master-Slave conflict was detected
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(boolean, ETHTSYN_CODE) EthTSyn_UtilRx_SyncPortRoleCheckWithMasterSlaveConflictDetection(
  EthTSyn_IntPortIdxType  PortIdx,
  uint64                  SrcClockIdentity);

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_ProvideTxBuffer
 *********************************************************************************************************************/
/*! \brief          Allocates an Ethernet transmission buffer.
 *  \details        Allocates an Ethernet transmission buffer and initialize the buffer with '0' (requested length).
 *  \param[in]      EthIfCtrlIdx Index of the underlying EthIf controller
 *  \param[in]      FramePrio    The desired frame priority
 *  \param[in,out]  TxBufferPtr   In: Requested length of the Tx buffer
 *                               Out: Index and Pointer of the allocated Tx buffer. The FrameId.
 *                                    The Length is not modified.
 *  \return     E_OK - Ethernet buffer allocated and initialized. All out parameters are valid.
 *  \return     E_NOT_OK - Failed to allocate an Ethernet buffer. Out parameters are not valid.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TxBuffer pointers
 *  \note       TxBufferPtr->Length is not modified and therefore can be used to trigger the transmission later.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_UtilTx_ProvideTxBuffer(
                EthTSyn_EthIfCtrlIdxOfCtrlType  EthIfCtrlIdx,
                uint8                           FramePrio,
  ETHTSYN_P2VAR(EthTSyn_EthTxBufferStructType)  TxBufferPtr);

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_PrepareTransmission
 *********************************************************************************************************************/
/*! \brief      Prepares an Ethernet TxBuffer for transmission.
 *  \details    Prepares an Ethernet TxBuffer for transmission, i.e. set switch management info and enable egress
 *              timestamping if required.
 *  \param[in]  EthIfCtrlIdx       Index of the underlying EthIf controller
 *  \param[in]  TxBufferIdx        Index of the Ethernet tx buffer to be prepared
 *  \param[in]  EnableTsFlags      Bit field inidicating which timestamps should be enabled
 *  \param[in]  SwtMgmtInfoPtr  The switch management information which should be set
 *  \return     E_OK - Ethernet buffer is ready for transmission.
 *  \return     E_NOT_OK - Failed to set up the Ethernet buffer for transmission. Release of the buffer required.
 *  \pre        TxBuffer was allocated by EthTSyn_UtilTx_ProvideTxBuffer()
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TxBuffers
 *  \note       Depending on the value of EnableTsFlags and SwtMgmtInfoPtr the following egress timestamps are enabled:
 *              ETHTSYN_ENABLE_TS_HW_XOR_SWT_MASK == TRUE ->  SwtTs is enabled for SwtMgmtInfoPtr != NULL_PTR and
 *                                                            HwTs is enabled for SwtMgmtInfoPtr == NULL_PTR
 *              ETHTSYN_ENABLE_TS_HW_XOR_SWT_MASK == FALSE -> SwtTs is enabled for SwtmgmtInfoPtr != NULL_PTR &&
 *                                                            ETHTSYN_ENABLE_TS_SWT_TS_MASK == TRUE
 *                                                            HwTs is enabled for ETHTSYN_ENABLE_TS_HW_TS_MASK == TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_UtilTx_PrepareTransmission(
                  EthTSyn_EthIfCtrlIdxOfCtrlType   EthIfCtrlIdx,
                  uint8                            TxBufferIdx,
                  EthTSyn_EnableTimestampFlagsType EnableTsFlags,
  ETHTSYN_P2CONST(EthTSyn_SwtMgmtInfoType)         SwtMgmtInfoPtr);

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_Transmit
 *********************************************************************************************************************/
/*! \brief      Triggers the transmission of an Ethernet TxBuffer.
 *  \details    Triggers the transmission of a former allocated (EthTSyn_UtilTx_ProvideTxBuffer) and prepared
 *              (EthTSyn_UtilTx_PrepareTransmission).
 *  \param[in]  EthIfCtrlIdx  Index of the underlying EthIf controller
 *  \param[in]  TxBufferIdx   The Ethernet Tx buffer index for transmission
 *  \param[in]  TxLength      The length to be transmitted in bytes
 *  \return     E_OK - Ethernet buffer successfully transmitted.
 *  \return     E_NOT_OK - Failed to transmit the Ethernet Tx buffer
 *  \pre        TxBuffer was allocated by EthTSyn_UtilTx_ProvideTxBuffer()
 *  \pre        TxBuffer was prepared for transmission by EthTSyn_UtilTx_PrepareTransmission()
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TxBuffers
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_UtilTx_Transmit(
  EthTSyn_EthIfCtrlIdxOfCtrlType  EthIfCtrlIdx,
  uint8                           TxBufferIdx,
  uint16                          TxLength);

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_ReleaseTxBuffer
 *********************************************************************************************************************/
/*! \brief      Releases a former allocate Ethernet transmission buffer.
 *  \details    -
 *  \param[in]  EthIfCtrlIdx    Index of the underlying EthIf controller
 *  \param[in]  TxBufferIndex   Index of the Ethernet Tx buffer to be released
 *  \pre        TxBuffer was allocated by EthTSyn_UtilTx_ProvideTxBuffer()
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TxBuffers
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_UtilTx_ReleaseTxBuffer(
  EthTSyn_EthIfCtrlIdxOfCtrlType EthIfCtrlIdx,
  uint8                          TxBufferIdx);

/**********************************************************************************************************************
 *  EthTSyn_Util_TransformClockIdentityToUint64
 *********************************************************************************************************************/
/*! \brief      Transforms the passed clock identity into an uint64 representation.
 *  \details    Transforms the passed clock identity which is represented as uint8 array with a size of 8 into an
 *              uint64 value.
 *  \param[in]  ClockIdentityPtr   Pointer to the clock identity
 *  \return     The clock identity as uint64 value
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(uint64, ETHTSYN_CODE) EthTSyn_Util_TransformClockIdentityToUint64(
  ETHTSYN_P2CONST(EthTSyn_ClockIdentityBaseType) ClockIdentityPtr);

/**********************************************************************************************************************
 *  GLOBAL INLINE FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Util_IsTimestampAvailable
 *********************************************************************************************************************/
/*! \brief      Checks if the Timestamp with the passed Timestamp state is available.
 *  \details    -
 *  \param[in]  TimestampState   State of the Timestamp to check
 *  \return     TRUE - Timestamp is available
 *  \return     FALSE - Timestamp is not available
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsTimestampAvailable(
  EthTSyn_TimestampStateType TimestampState);

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Util_GetPortType
 *********************************************************************************************************************/
/*! \brief      Gets the Port type of the passed Port.
 *  \details    -
 *  \param[in]  PortIdx   Index of the Port
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     ETHTSYN_PORT_TYPE_END_STATION_PORT - End-Station Port
 *  \return     ETHTSYN_PORT_TYPE_SWITCH_PORT - Switch-Port
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PortTypeType, ETHTSYN_CODE) EthTSyn_Util_GetPortType(
  EthTSyn_IntPortIdxType PortIdx);
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Util_IsSwitchPort
 *********************************************************************************************************************/
/*! \brief      Checks if the passed Port is a Switch-Port.
 *  \details    -
 *  \param[in]  PortIdx   Index of the Port
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - Port is a Switch-Port
 *  \return     FALSE - Port is not a Switch-Port
 *  \pre        -
 *  \context    TAKS|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsSwitchPort(
  EthTSyn_IntPortIdxType PortIdx);
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Util_IsEndStationPort
 *********************************************************************************************************************/
/*! \brief      Checks if the passed Port is an EndStation-Port.
 *  \details    -
 *  \param[in]  PortIdx   Index of the Port
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - Port is an EndStation-Port
 *  \return     FALSE - Port is not an EndStation-Port
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsEndStationPort(
  EthTSyn_IntPortIdxType PortIdx);
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_UtilTx_GetSwtMgmtInfo
 *********************************************************************************************************************/
/*! \brief      Gets the Switch management info of the passed Port.
 *  \details    Gets the Switch management info (including the frame id if applicable) of the passed Port,
 *              if the passed Port is a Switch port.
 *  \param[in]  PortIdx       Index of the Port
 *                            [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[out] MgmtInfoPtr   The retrieved switch management information including the frame id if applicable
 *  \return     E_OK - Port is a Switch-Port and switch management information was retrieved.
 *  \return     E_NOT_OK - Port is not a Switch-Port
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_UtilTx_GetSwtMgmtInfo(
                  EthTSyn_IntPortIdxType    PortIdx,
    ETHTSYN_P2VAR(EthTSyn_SwtMgmtInfoType)  MgmtInfoPtr);
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
/**********************************************************************************************************************
*  EthTSyn_Util_GetFrameId
*********************************************************************************************************************/
/*! \brief     Retrieves the frame identifier contained in the Ethernet frame buffer.
 *  \details   -
 *  \param[in]  DataPtr     Pointer to the Ethernet frame buffer
 *  \param[in]  PayloadLen  Length of the Ethernet frame payload
 *  \return     Frame identifier contained in the Ethernet frame buffer
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_FrameIdType, ETHIF_CODE) EthTSyn_Util_GetFrameId(
  ETHTSYN_P2CONST(uint8)  DataPtr,
                  uint16  PayloadLen);
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

# if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_UtilRx_IsPortReadyToReceiveAnnounce
 *********************************************************************************************************************/
/*! \brief      Checks if the passed Port is ready to receive an Announce message (incl. check of PortRole == SLAVE).
 *  \details    -
 *  \param[in]  PortIdx   Index of EthTSyn port that shall receive the announce message
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - Port is ready to receive the announce message
 *  \return     FALSE - Port is not ready to receive the announce message
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_UtilRx_IsPortReadyToReceiveAnnounce(
  EthTSyn_IntPortIdxType PortIdx);
# endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_Util_IsAsCapable
 *********************************************************************************************************************/
/*! \brief      Checks if the passed Port is AsCapable.
 *  \details    -
 *  \param[in]  PortIdx   Index of the Port
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - Port is AsCapable
 *  \return     FALSE - Port is not AsCapable
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsAsCapable(
  EthTSyn_IntPortIdxType PortIdx);

# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Util_SetAsCapable
 *********************************************************************************************************************/
/*! \brief      Sets AsCapable Flag of the passed Port.
 *  \details    -
 *  \param[in]  PortIdx     Index of the Port
 *                          [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  AsCapable   The new value for AsCapable of the given Port
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Util_SetAsCapable(
  EthTSyn_IntPortIdxType PortIdx,
  boolean                AsCapable);
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_Util_GetEthTSynCtrlFromEthIfCtrl
 *********************************************************************************************************************/
/*! \brief      Gets the EthTSyn controller corresponding to the passed EthIf controller.
 *  \details    -
 *  \param[in]  EthIfCtrlIdx   EthIf controller index.
 *  \return     EthTSyn_GetSizeOfCtrl() - no matching EthTSyn controller found
 *  \return     other values - index of the corresponding EthTSyn controller
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntCtrlIdxType, ETHTSYN_CODE) EthTSyn_Util_GetEthTSynCtrlFromEthIfCtrl(
  uint8 EthIfCtrlIdx);

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Util_GetTimeDomainIdxFromId
 *********************************************************************************************************************/
/*! \brief      Gets the TimeDomain index of the passed TimeDomain Id.
 *  \details    -
 *  \param[in]  TimeDomainId   The TimeDomain Id
 *  \return     EthTSyn_GetSizeOfTimeDomain() - No matching time domain found
 *  \return     other value - Index of the matching time domain
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntTimeDomainIdxType, ETHTSYN_CODE) EthTSyn_Util_GetTimeDomainIdxFromId(
  EthTSyn_DomainNumberType TimeDomainId);
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_Util_GetEthIfCtrlIdxOfPort
 *********************************************************************************************************************/
/*! \brief      Gets the Ethernet interface controller index of the passed Port.
 *  \details    -
 *  \param[in]  PortIdx   EthTSyn port index
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     EthIf controller index
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_Util_GetEthIfCtrlIdxOfPort(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Util_IsActivePdelayPort
 *********************************************************************************************************************/
/*! \brief      Checks if the passed Port is an active Pdelay Port.
 *  \details    -
 *  \param[in]  PortIdx   Index of the port
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - Port is active Pdelay port
 *  \return     FALSE - Port is no active Pdelay port
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsActivePdelayPort(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
*  EthTSyn_Util_AreBitsSet
*********************************************************************************************************************/
/*! \brief      Checks if all bits of the passed bit mask are set in the passed bit field.
*  \details    -
*  \param[in]  BitField   The bit field to check
*  \param[in]  BitMask    The bits which to check
*  \return     TRUE - All bits of the passed bit mask are set in the passed bit field
*  \return     FALSE - At least one bit of the passed bit mask is not set in the passed bit field
*  \pre        -
*  \context    TASK|ISR2
*  \reentrant  TRUE
*********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_AreBitsSet(
  uint8 BitField,
  uint8 BitMask);

# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
/***********************************************************************************************************************
 * PDELAY INITIATOR CFGACCESS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Util_IsPdelayInitiator
 *********************************************************************************************************************/
/*! \brief      Checks if the passed Port is an active Pdelay Initiator.
 *  \details    -
 *  \param[in]  PortIdx   Index of the Port
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - Port is Pdelay initiator
 *  \return     FALSE - Port is no Pdelay initiator
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsPdelayInitiator(
  EthTSyn_IntPortIdxType PortIdx);

/***********************************************************************************************************************
 * END: PDELAY INITIATOR CFGACCESS
 **********************************************************************************************************************/
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
/***********************************************************************************************************************
 * PDELAY RESPONDER CFGACCESS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Util_IsPdelayResponder
 *********************************************************************************************************************/
/*! \brief      Checks if the passed Port is a Pdelay Responder.
 *  \details    -
 *  \param[in]  PortIdx   Index of the Port
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - Port is Pdelay responder
 *  \return     FALSE - Port is no Pdelay responder
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsPdelayResponder(
  EthTSyn_IntPortIdxType PortIdx);

/***********************************************************************************************************************
 *END: PDELAY RESPONDER CFGACCESS
 **********************************************************************************************************************/
# endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

# if (ETHTSYN_CRC_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Util_GetFollowUpDataIdListEntry
 *********************************************************************************************************************/
/*! \brief      Gets the value of the FollowUp Data Id list for the passed FollowUp Sequence Id.
 *  \details    -
 *  \param[in]  TimeDomainIdx   Index of the TimeDomain the DataId is requested for
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \param[in]  SequenceId      The SequenceId
 *  \return     The value of the FollowUp Data Id list for the given Sequence Id
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_Util_GetFollowUpDataIdListEntry(
  EthTSyn_IntTimeDomainIdxType TimeDomainIdx,
  uint16                       SequenceId);
# endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */

# if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_Util_IsArTlvTxRequired
 *********************************************************************************************************************/
/*! \brief      Checks if an Ar Tlv has to be appended to the FollowUp message transmitted on the passed Master-Port.
 *  \details    -
 *  \param[in]  MasterPortIdx   Index of the Master Port the FollowUp message is transmitted on
 *                              [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \return     TRUE - Ar Tlv required
 *  \return     FALSE - Ar Tlv not required
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsArTlvTxRequired(
  EthTSyn_IntMasterPortIdxType  MasterPortIdx);
# endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */

/**********************************************************************************************************************
 *  GLOBAL INLINE FUNCTIONS
 *********************************************************************************************************************/
# if !defined(ETHTSYN_UNIT_TEST) /* COV_ETHTSYN_TESTSUITE_INSTRUMENTATION */
/**********************************************************************************************************************
 *  EthTSyn_Util_IsTimestampAvailable
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsTimestampAvailable(
  EthTSyn_TimestampStateType TimestampState)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean tsAvailable = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  if((TimestampState & ETHTSYN_TIMESTAMP_STATE_AVAILABLE_FLAG_VALID_MASK) != 0)
  {
    if((TimestampState & ETHTSYN_TIMESTAMP_STATE_AVAILABLE_MASK) != 0)
    {
      tsAvailable = TRUE;
    }
  }

  return tsAvailable;
} /* EthTSyn_Util_IsTimestampAvailable() */

/**********************************************************************************************************************
 *  EthTSyn_Util_GetPortType
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
#  if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_PortTypeType, ETHTSYN_CODE) EthTSyn_Util_GetPortType(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_PortTypeType portType;

  /* ----- Implementation ----------------------------------------------- */
  if(EthTSyn_IsSwitchPortMgmtUsedOfPort(PortIdx) == TRUE)
  {
    portType = ETHTSYN_PORT_TYPE_SWITCH_PORT;
  }
  else
  {
    portType = ETHTSYN_PORT_TYPE_END_STATION_PORT;
  }

  return portType;
} /* EthTSyn_Util_GetPortType() */
#  endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_Util_IsSwitchPort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
#  if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsSwitchPort(
  EthTSyn_IntPortIdxType PortIdx)
{
  return (boolean)(EthTSyn_Util_GetPortType(PortIdx) == ETHTSYN_PORT_TYPE_SWITCH_PORT);
} /* EthTSyn_Util_IsSwitchPort() */
#  endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_Util_IsEndStationPort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
#  if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsEndStationPort(
  EthTSyn_IntPortIdxType PortIdx)
{
  return (boolean)(EthTSyn_Util_GetPortType(PortIdx) == ETHTSYN_PORT_TYPE_END_STATION_PORT);
} /* EthTSyn_Util_IsEndStationPort() */
#  endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_GetSwtMgmtInfo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
#  if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_UtilTx_GetSwtMgmtInfo(
                EthTSyn_IntPortIdxType   PortIdx,
  ETHTSYN_P2VAR(EthTSyn_SwtMgmtInfoType) MgmtInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  if(EthTSyn_Util_IsSwitchPort(PortIdx) == TRUE)
  {
    MgmtInfoPtr->PortIdx = EthTSyn_GetPortIdxOfSwitchPortMgmt(EthTSyn_GetSwitchPortMgmtIdxOfPort(PortIdx));            /* SBSW_ETHTSYN_VALID_API_POINTER */
    MgmtInfoPtr->SwitchIdx = EthTSyn_GetSwitchIdxOfSwitchPortMgmt(EthTSyn_GetSwitchPortMgmtIdxOfPort(PortIdx));        /* SBSW_ETHTSYN_VALID_API_POINTER */

    retVal = E_OK;
  }

  return retVal;
} /* EthTSyn_UtilTx_GetSwtMgmtInfo() */
#  endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

#  if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
  /**********************************************************************************************************************
  *  EthTSyn_Util_GetFrameId
  *********************************************************************************************************************/
  /*!
  * Internal comment removed.
 *
 *
  */
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_FrameIdType, ETHIF_CODE) EthTSyn_Util_GetFrameId(
  ETHTSYN_P2CONST(uint8) DataPtr,
                  uint16 PayloadLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_P2VAR(uint8) frameIdPtr;
  EthTSyn_FrameIdType frameId = ETHTSYN_INVALID_FRAME_ID;
  uint8_least frameIdByteIdx;

  /* ----- Implementation ----------------------------------------------- */
  frameIdPtr = (ETHTSYN_P2VAR(uint8))&frameId; /* PRQA S 0310 */ /* MD_EthTSyn_0310_ByteAccess */
  for (frameIdByteIdx = 0; frameIdByteIdx < sizeof(EthTSyn_FrameIdType); frameIdByteIdx++)
  {
    frameIdPtr[frameIdByteIdx] = DataPtr[PayloadLen + frameIdByteIdx];                                                 /* SBSW_ETHTSYN_ARRAY_SIZE */
  }

  return frameId;
} /* EthTSyn_Util_GetFrameId() */
#  endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

#  if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_UtilRx_IsPortReadyToReceiveAnnounce
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_UtilRx_IsPortReadyToReceiveAnnounce(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isReady = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the given Port is a Slave Port. */
  if(EthTSyn_IsSlavePortUsedOfPort(PortIdx) == TRUE)
  {
    /* #20 Check if Port is AsCapable. */
    if(EthTSyn_Util_IsAsCapable(PortIdx) == TRUE)
    {
      const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
      /* #30 Check if Announce is enabled for the Port. */
      if(EthTSyn_IsAnnounceInfoUsedOfSlavePort(slavePortIdx) == TRUE)
      {
        isReady = TRUE;
      }
    }
  }

  return isReady;
} /* EthTSyn_SlaveRx_IsPortReadyToReceiveAnnounce() */
#  endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_Util_IsAsCapable
 *********************************************************************************************************************/
/*!
 *Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsAsCapable(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean asCapable = TRUE; /* Init as TRUE for better readability */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Pdelay is used for the port. */
  if(EthTSyn_IsPdelayConfigUsedOfPort(PortIdx) == TRUE)
  {
    const EthTSyn_PdelayConfigIdxOfPortType pDelayIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    /* #20 Pdelay is used -> get AsCapable flag. */
    asCapable = (boolean)EthTSyn_IsAsCapableOfPdelayInfo(pDelayIdx);
  }

  return asCapable;
} /* EthTSyn_Util_IsAsCapable() */

#  if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Util_SetAsCapable
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Util_SetAsCapable(
  EthTSyn_IntPortIdxType PortIdx,
  boolean                AsCapable)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Port is pdelay initiator because AsCapable can only change for Pdelay initiators. */
  if(EthTSyn_Util_IsPdelayInitiator(PortIdx) == TRUE)
  {
    const EthTSyn_PdelayConfigIdxOfPortType pDelayIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    /* #20 Verify that Port is not always AsCapable. */
    if(EthTSyn_IsAlwaysAsCapableOfPdelayConfig(pDelayIdx) == FALSE)
    {
      /* #30 Only set AsCapable for Ports which are not always AsCapable. */
      EthTSyn_SetAsCapableOfPdelayInfo(pDelayIdx, AsCapable);                                                          /* SBSW_ETHTSYN_CSL03 */
    }
  }
} /* EthTSyn_Util_SetAsCapable() */
#  endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

/***********************************************************************************************************************
 * EthTSyn_Util_GetEthTSynCtrlFromEthIfCtrl
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntCtrlIdxType, ETHTSYN_CODE) EthTSyn_Util_GetEthTSynCtrlFromEthIfCtrl(
  uint8 EthIfCtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_CtrlIterType ethTSynCtrlIter;
  EthTSyn_IntCtrlIdxType ethTSynCtrlIdx = EthTSyn_GetSizeOfCtrl();

  /* ----- Implementation ----------------------------------------------- */
  for(ethTSynCtrlIter = 0; ethTSynCtrlIter < EthTSyn_GetSizeOfCtrl(); ethTSynCtrlIter++)
  {
    if(EthTSyn_GetEthIfCtrlIdxOfCtrl(ethTSynCtrlIter) == EthIfCtrlIdx)
    {
      ethTSynCtrlIdx = (EthTSyn_IntCtrlIdxType)ethTSynCtrlIter;
      break;
    }
  }

  return ethTSynCtrlIdx;
} /* EthTSyn_GetEthTSynCtrlFromEthIfCtrl */

#  if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Util_GetTimeDomainIdxFromId
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_IntTimeDomainIdxType, ETHTSYN_CODE) EthTSyn_Util_GetTimeDomainIdxFromId(
  EthTSyn_DomainNumberType TimeDomainId)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_IntTimeDomainIdxType timeDomainIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Search all configured TimeDomains for the passed TimeDomain Id. If a matching TimeDomain is found,
   *     return its index. */
  for(timeDomainIdx = 0; timeDomainIdx < EthTSyn_GetSizeOfTimeDomain(); timeDomainIdx++)
  {
    if(EthTSyn_GetIdOfTimeDomain(timeDomainIdx) == TimeDomainId)
    {
      break;
    }
  }

  return timeDomainIdx;
} /* EthTSyn_Util_GetTimeDomainIdxFromId() */
#  endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_Util_GetEthIfCtrlIdxOfPort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_Util_GetEthIfCtrlIdxOfPort(EthTSyn_IntPortIdxType PortIdx)
{
  return EthTSyn_GetEthIfCtrlIdxOfCtrl(EthTSyn_GetCtrlIdxOfPort(PortIdx));
} /* EthTSyn_Util_GetEthIfCtrlIdxOfPort() */

/**********************************************************************************************************************
 *  EthTSyn_Util_IsActivePdelayPort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsActivePdelayPort(EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isActivePdelayPort = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  if(EthTSyn_IsPdelayConfigUsedOfPort(PortIdx) == TRUE)
  {
    const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    isActivePdelayPort = (boolean)(EthTSyn_GetPortIdxOfPdelayConfig(pDelayCfgIdx) == PortIdx);
  }

  return isActivePdelayPort;
} /* EthTSyn_Pdelay_IsActivePdelayPort() */

/**********************************************************************************************************************
 *  EthTSyn_Util_AreBitsSet
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_AreBitsSet(
  uint8 BitField,
  uint8 BitMask)
{
  return (boolean)((BitField & BitMask) == BitMask);
} /* EthTSyn_Util_AreBitsSet() */

#  if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
/***********************************************************************************************************************
 * PDELAY INITIATOR CFGACCESS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Util_IsPdelayInitiator
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsPdelayInitiator(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isActiveInitiator = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the passed Port is an active Pdelay Port. */
  if(EthTSyn_Util_IsActivePdelayPort(PortIdx) == TRUE)
  {
    /* #20 Check if Port is Pdelay Initiator. */
    const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    isActiveInitiator = (boolean)EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig(pDelayCfgIdx);
  }

  return isActiveInitiator;
} /* EthTSyn_Util_IsPdelayInitiator() */

/***********************************************************************************************************************
 * END: PDELAY INITIATOR CFGACCESS
 **********************************************************************************************************************/
#  endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

#  if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
/***********************************************************************************************************************
 * PDELAY RESPONDER CFGACCESS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Util_IsPdelayResponder
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsPdelayResponder(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isActiveResponder = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the passed Port is an active Pdelay Port. */
  if(EthTSyn_Util_IsActivePdelayPort(PortIdx) == TRUE)
  {
    /* #20 Check if Port is Pdelay Responder. */
    const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    isActiveResponder = (boolean)EthTSyn_IsPdelayResponderUsedOfPdelayConfig(pDelayCfgIdx);
  }

  return isActiveResponder;
} /* EthTSyn_Util_IsPdelayResponder() */

/***********************************************************************************************************************
 * END: PDELAY RESPONDER CFGACCESS
 **********************************************************************************************************************/
#  endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

#  if (ETHTSYN_CRC_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Util_GetFollowUpDataIdListEntry
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_Util_GetFollowUpDataIdListEntry(
  EthTSyn_IntTimeDomainIdxType TimeDomainIdx, uint16 SequenceId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 dataListEntry = 0;
  uint8 dataListIdx = (uint8)(SequenceId % ETHTSYN_FOLLOW_UP_DATA_ID_LIST_SIZE);

  /* ----- Implementation ----------------------------------------------- */
  if(EthTSyn_IsFollowUpDataIdListUsedOfTimeDomain(TimeDomainIdx) == TRUE)
  {
    dataListEntry = EthTSyn_GetFollowUpDataIdList(
      EthTSyn_GetFollowUpDataIdListStartIdxOfTimeDomain(TimeDomainIdx) + dataListIdx);
  }

  return dataListEntry;
} /* EthTSyn_Util_GetFollowUpDataIdListEntry() */
#  endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */

#  if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_Util_IsArTlvTxRequired
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Util_IsArTlvTxRequired(
  EthTSyn_IntMasterPortIdxType MasterPortIdx)
{
  /* PRQA S 3415 6 */ /* MD_EthTSyn_3415_CslReadOnly */
  return (boolean)(
    (EthTSyn_IsTimeSubTlvOfMasterPort(MasterPortIdx)) ||
    (EthTSyn_IsUserDataSubTlvOfMasterPort(MasterPortIdx)) ||
    (EthTSyn_IsStatusSubTlvOfMasterPort(MasterPortIdx)) ||
    (EthTSyn_IsOfsSubTlvOfMasterPort(MasterPortIdx))
    );
} /* EthTSyn_Util_IsArTlvTxRequired() */
#  endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */

# endif /* !defined(ETHTSYN_UNIT_TEST) */
# define ETHTSYN_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_19.1 */

#endif /* ETHTSYN_UTIL_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Util_Int.h
 *********************************************************************************************************************/
