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
/**        \file  EthTSyn_Util_Int.c
 *        \brief  EthTSyn Util source file - Internal Functions
 *
 *      \details  EthTSyn Util source file containing the implementation of utilities used by different Sub-Modules of
 *                of the EthTSyn
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

#define ETHTSYN_UTIL_INT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EthTSyn_Util_Int.h" /* PRQA S 3219, 0883 */ /* MD_EthTSyn_3219, MD_EthTSyn_0883 */
#include "EthTSyn_Int.h" /* PRQA S 3219 */ /* MD_EthTSyn_3219 */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of EthTSyn header file */
#if (  (ETHTSYN_SW_MAJOR_VERSION != (7u)) \
    || (ETHTSYN_SW_MINOR_VERSION != (0u)) \
    || (ETHTSYN_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of EthTSyn_Util_Int.c and EthTSyn.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (ETHTSYN_CFG_MAJOR_VERSION != (7u)) \
    || (ETHTSYN_CFG_MINOR_VERSION != (0u)) )
# error "Version numbers of EthTSyn_Util_Int.c and EthTSyn_Cfg.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
/* 48 bit seconds */
#define ETHTSYN_TIMESTAMP_MAX_SECONDS                                             (0xFFFFFFFFFFFFLL)
/* 10^9 nanoseconds per second */
#define ETHTSYN_TIMESTAMP_MAX_NANOSECONDS                                         (1000000000UL)
/* 63 bit max timediff in nanoseconds */
#define ETHTSYN_TIMEDIFF_MAX_NANOSECONDS                                          (0x7FFFFFFFFFFFFFFFLL)
#define ETHTSYN_TIMEDIFF_MAX_SECONDS                                              (ETHTSYN_TIMEDIFF_MAX_NANOSECONDS \
                                                                                  / ETHTSYN_TIMESTAMP_MAX_NANOSECONDS)

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/


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

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define ETHTSYN_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  EthTSyn_UtilRx_GetExpectedMsgLengthWithMsgTypeCheck
 *********************************************************************************************************************/
/*! \brief      Gets the expected message length and verifies the message type of the passed message.
 *  \details    -
 *  \param[in]  ComMsgPtr                     Pointer to the message to be checked
 *  \param[out] ExpectedLengthPtr             The expected message length
 *  \param[out] IsExpectedLengthMinLengthPtr  TRUE:  The expected message length is just the minimal length
 *                                            FALSE: The expected message length has to match exactly
 *  \return     ETHTSYN_E_NO_ERROR - Message type valid and expected length successfully retrieved. Out parameter valid.
 *  \return     other value - Message type invalid or failed to retrieve expected length. Out parameter invalid.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_UtilRx_GetExpectedMsgLengthWithMsgTypeCheck(
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType)  ComMsgPtr,
    ETHTSYN_P2VAR(uint16)                    ExpectedLengthPtr,
    ETHTSYN_P2VAR(boolean)                   IsExpectedLengthMinLengthPtr);

/**********************************************************************************************************************
 *  EthTSyn_Util_AddTimediffToTimestamp
 *********************************************************************************************************************/
/*! \brief         Adds the passed time difference to the provided timestamp.
 *  \details       -
 *  \param[in]     TimeDiffNs     The time difference in nanoseconds
 *  \param[in,out] TimestampPtr   In:   The timestamp to be incremented by the given time difference
 *                                Out:  The given Timestamp + the given time difference
 *  \return        E_OK - Successfully added the time difference to the timestamp
 *  \return        E_NOT_OK - Failed to added the time difference to the timestamp
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different Timestamps
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Util_AddTimediffToTimestamp(
                  uint64                          TimeDiffNs,
    ETHTSYN_P2VAR(EthTSyn_InternalTimestampType)  TimestampPtr);

/**********************************************************************************************************************
 *  EthTSyn_Util_SubtractTimediffFromTimestamp
 *********************************************************************************************************************/
/*! \brief         Subtracts the passed time difference from the provided timestamp.
 *  \details       -
 *  \param[in]     TimeDiffNs     The time difference in nanoseconds
 *  \param[in,out] TimestampPtr   In:   The timestamp to be decremented by the given time difference
 *                                Out:  The given Timestamp - the given time difference
 *  \return        E_OK - Successfully subtracted the time difference from the timestamp
 *                 E_NOT_OK - Failed to subtract the time difference from the timestamp
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different Timestamps
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Util_SubtractTimediffFromTimestamp(
                  uint64                          TimeDiffNs,
    ETHTSYN_P2VAR(EthTSyn_InternalTimestampType)  TimestampPtr);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

 /**********************************************************************************************************************
  *  EthTSyn_UtilRx_GetExpectedMsgLengthWithMsgTypeCheck
  *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
 ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_UtilRx_GetExpectedMsgLengthWithMsgTypeCheck(
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) ComMsgPtr,
    ETHTSYN_P2VAR(uint16)                   ExpectedLengthPtr,
    ETHTSYN_P2VAR(boolean)                  IsExpectedLengthMinLengthPtr)
{
   /* ----- Local Variables ---------------------------------------------- */
   uint8 errorId = ETHTSYN_E_NO_ERROR;

   /* ----- Implementation ----------------------------------------------- */
   *ExpectedLengthPtr = 0;                                                                                             /* SBSW_ETHTSYN_VALID_API_POINTER */
   *IsExpectedLengthMinLengthPtr = FALSE;                                                                              /* SBSW_ETHTSYN_VALID_API_POINTER */

   /* #10 Check the message type. */
   switch(ETHTSYN_HDR_COM_MSG_TYPE(ComMsgPtr->TransSpecific_MessageType))
   {
   /* #100 Set the expected length for valid message types. */
   case ETHTSYN_MSG_TYPE_SYNC:
     {
       *ExpectedLengthPtr = ETHTSYN_MSG_SYNC_LENGTH;                                                                   /* SBSW_ETHTSYN_VALID_API_POINTER */
       break;
     }

   case ETHTSYN_MSG_TYPE_FOLLOW_UP:
     {
       *ExpectedLengthPtr = ETHTSYN_MSG_FOLLOW_UP_RX_MIN_LENGTH;                                                       /* SBSW_ETHTSYN_VALID_API_POINTER */
       *IsExpectedLengthMinLengthPtr = TRUE;                                                                           /* SBSW_ETHTSYN_VALID_API_POINTER */
       break;
     }

   case ETHTSYN_MSG_TYPE_PDELAY_REQ:
     {
       *ExpectedLengthPtr = ETHTSYN_MSG_P_DELAY_REQ_LENGTH;                                                            /* SBSW_ETHTSYN_VALID_API_POINTER */
       break;
     }

   case ETHTSYN_MSG_TYPE_PDELAY_RESP:
     {
       *ExpectedLengthPtr = ETHTSYN_MSG_P_DELAY_RESP_LENGTH;                                                           /* SBSW_ETHTSYN_VALID_API_POINTER */
       break;
     }

   case ETHTSYN_MSG_TYPE_PDELAY_RES_FOLLOW_UP:
     {
       *ExpectedLengthPtr = ETHTSYN_MSG_P_DELAY_RESP_FOLLOW_UP_LENGTH;                                                 /* SBSW_ETHTSYN_VALID_API_POINTER */
       break;
     }

   case ETHTSYN_MSG_TYPE_ANNOUNCE:
     {
       *ExpectedLengthPtr = ETHTSYN_MSG_ANNOUNCE_LENGTH;                                                               /* SBSW_ETHTSYN_VALID_API_POINTER */
       *IsExpectedLengthMinLengthPtr = TRUE;                                                                           /* SBSW_ETHTSYN_VALID_API_POINTER */
       break;
     }

   default:
     {
       /* #101 Invalid message type. Set errorId. */
       errorId = ETHTSYN_E_MSG_TYPE;
       break;
     }
   }

   return errorId;
} /* EthTSyn_UtilRx_GetExpectedMsgLengthWithMsgTypeCheck() */

/**********************************************************************************************************************
 *  EthTSyn_Util_AddTimediffToTimestamp
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
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Util_AddTimediffToTimestamp(
                uint64                         TimeDiffNs,
  ETHTSYN_P2VAR(EthTSyn_InternalTimestampType) TimestampPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  EthTSyn_UTimediffType DiffSeconds;
  uint32 DiffNanoseconds;

  /* ----- Implementation ----------------------------------------------- */
  DiffSeconds = (EthTSyn_UTimediffType)(TimeDiffNs / ETHTSYN_TIMESTAMP_MAX_NANOSECONDS);
  DiffNanoseconds = (uint32)(TimeDiffNs % ETHTSYN_TIMESTAMP_MAX_NANOSECONDS);

  /* #10 Overflow check of rounded up seconds -> Check nanoseconds overflow not required */
  if((EthTSyn_UTimediffType)((TimestampPtr->seconds + 1) + DiffSeconds) <=
      (EthTSyn_UTimediffType)ETHTSYN_TIMESTAMP_MAX_SECONDS)
  {
    /* #20 Add nanoseconds of both summands */
    TimestampPtr->nanoseconds += (uint32)DiffNanoseconds;                                                              /* SBSW_ETHTSYN_VALID_API_POINTER */

    /* #30 Add seconds of overflow nanoseconds */
    TimestampPtr->seconds += (uint64)((uint64)TimestampPtr->nanoseconds /
        (uint64)ETHTSYN_TIMESTAMP_MAX_NANOSECONDS);                                                                    /* SBSW_ETHTSYN_VALID_API_POINTER */

    /* #40 Truncate overflow nanoseconds */
    TimestampPtr->nanoseconds = TimestampPtr->nanoseconds % ETHTSYN_TIMESTAMP_MAX_NANOSECONDS;                         /* SBSW_ETHTSYN_VALID_API_POINTER */

    /* #50 Add seconds */
    TimestampPtr->seconds += (EthTSyn_UTimediffType)DiffSeconds;                                                       /* SBSW_ETHTSYN_VALID_API_POINTER */

    retVal = E_OK;
  }

  return retVal;
} /* EthTSyn_Util_AddTimediffToTimestamp() */

/**********************************************************************************************************************
 *  EthTSyn_Util_SubtractTimediffFromTimestamp
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
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Util_SubtractTimediffFromTimestamp(
                uint64                         TimeDiffNs,
  ETHTSYN_P2VAR(EthTSyn_InternalTimestampType) TimestampPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  EthTSyn_UTimediffType DiffSeconds;
  uint32 DiffNanoseconds;

  /* ----- Implementation ----------------------------------------------- */
  DiffSeconds = (EthTSyn_UTimediffType)(TimeDiffNs / ETHTSYN_TIMESTAMP_MAX_NANOSECONDS);
  DiffNanoseconds = (uint32)(TimeDiffNs % ETHTSYN_TIMESTAMP_MAX_NANOSECONDS);

  /* #10 Check that result is not negative. */
  if(DiffSeconds <= TimestampPtr->seconds)
  {
    /* #20 Check for Nanoseconds underflow. */
    if(DiffNanoseconds <= TimestampPtr->nanoseconds)
    {
      /* #200 Calculate timestamp and mark result as valid. */
      TimestampPtr->seconds -= DiffSeconds;                                                                            /* SBSW_ETHTSYN_VALID_API_POINTER */
      TimestampPtr->nanoseconds -= DiffNanoseconds;                                                                    /* SBSW_ETHTSYN_VALID_API_POINTER */

      retVal = E_OK;
    }
    else
    {
      /* #30 Handle Underflow. Destination seconds must be greater than difference seconds. */
      if(TimestampPtr->seconds > DiffSeconds)
      {
        /* #300 Calculate timestamp and mark result as valid. */
        TimestampPtr->seconds--;                                                                                       /* SBSW_ETHTSYN_VALID_API_POINTER */
        TimestampPtr->nanoseconds =
            (uint32)(((ETHTSYN_TIMESTAMP_MAX_NANOSECONDS + TimestampPtr->nanoseconds) - DiffNanoseconds));             /* SBSW_ETHTSYN_VALID_API_POINTER */
        TimestampPtr->seconds -= DiffSeconds; /* SBSW_ETHTSYN_VALID_API_POINTER */

        retVal = E_OK;
      }
    }
  }

  return retVal;
} /* EthTSyn_Util_SubtractTimediffFromTimestamp() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_PrepareCommonMsgHdr
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_UtilTx_PrepareCommonMsgHdr(
  ETHTSYN_P2VAR(EthTSyn_CommonMsgHdrType) ComMsgHdrPtr,
                uint8                     MsgType,
                EthTSyn_IntPortIdxType    PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean prepareHdr = TRUE;
  uint16 msgLength = 0;
  uint16 sequenceId = 0;
  uint8 comHdrControl = 0;
  sint8 logMessageInterval = 0;
  uint8 flagsFieldByte0 = 0;
  const uint16 portNumber = (uint16)EthTSyn_GetNumberOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get message specific values of the common message header from Message type. */
  switch(MsgType)
  {
#if (ETHTSYN_MASTER_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_SYNC:
    {
      const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
      ETHTSYN_CONSTP2VAR(EthTSyn_SyncSendSmType) syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);

      msgLength = ETHTSYN_MSG_SYNC_LENGTH;
      sequenceId = syncSendSmPtr->SequenceId;
      comHdrControl = ETHTSYN_HDR_COM_CONTROL_SYNC;
      logMessageInterval = syncSendSmPtr->LogMessageInterval;
      flagsFieldByte0 = ETHTSYN_FLAGS_OCTET_0_TWO_STEP;
      break;
    }

  case ETHTSYN_MSG_TYPE_FOLLOW_UP:
    {
      const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
      ETHTSYN_CONSTP2VAR(EthTSyn_SyncSendSmType) syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);

      msgLength = EthTSyn_GetFollowUpMsgLengthOfMasterPort(EthTSyn_GetMasterPortIdxOfPort(PortIdx));
      sequenceId = syncSendSmPtr->SequenceId;
      comHdrControl = ETHTSYN_HDR_COM_CONTROL_FOLLOW_UP;
      logMessageInterval = syncSendSmPtr->LogMessageInterval;
      break;
    }
#endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */

#if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_PDELAY_REQ:
    {
      const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
      const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
        EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
      const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
        EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
      ETHTSYN_CONSTP2VAR(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);

      msgLength = ETHTSYN_MSG_P_DELAY_REQ_LENGTH;
      sequenceId = pDelayReqSmPtr->PdelayReq.SequenceId;
      comHdrControl = ETHTSYN_HDR_COM_CONTROL_PDELAY_REQ;
      logMessageInterval = EthTSyn_GetLogMessageIntervalOfPdelayInitiator(pDelayInitiatorIdx);
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
      ETHTSYN_CONSTP2CONST(EthTSyn_PdelayRespSmType) pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);

      msgLength = ETHTSYN_MSG_P_DELAY_RESP_LENGTH;
      sequenceId = pDelayRespSmPtr->PdelayReq.SequenceId;
      comHdrControl = ETHTSYN_HDR_COM_CONTROL_PDELAY_RESP;
      logMessageInterval = ETHTSYN_HDR_COM_LOG_MESSAGE_INTERVAL_DEFAULT;
      flagsFieldByte0 = ETHTSYN_FLAGS_OCTET_0_TWO_STEP;
      break;
    }

  case ETHTSYN_MSG_TYPE_PDELAY_RES_FOLLOW_UP:
    {
      const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
      const EthTSyn_PdelayResponderIdxOfPdelayConfigType pDelayResponderIdx =
        EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pDelayCfgIdx);
      const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pDelayRespSmIdx =
        EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pDelayResponderIdx);
      ETHTSYN_CONSTP2CONST(EthTSyn_PdelayRespSmType) pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);

      msgLength = ETHTSYN_MSG_P_DELAY_RESP_FOLLOW_UP_LENGTH;
      sequenceId = pDelayRespSmPtr->PdelayReq.SequenceId;
      comHdrControl = ETHTSYN_HDR_COM_CONTROL_PDELAY_RESP_FOLLOW_UP;
      logMessageInterval = ETHTSYN_HDR_COM_LOG_MESSAGE_INTERVAL_DEFAULT;
      break;
    }
#endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

#if (ETHTSYN_ANNOUNCE_TX_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_ANNOUNCE:
    {
      const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
      ETHTSYN_CONSTP2VAR(EthTSyn_SyncSendSmType) syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);

      msgLength = ETHTSYN_MSG_ANNOUNCE_LENGTH;
      sequenceId = syncSendSmPtr->SequenceId;
      comHdrControl = ETHTSYN_HDR_COM_CONTROL_ANNOUNCE;
      logMessageInterval = syncSendSmPtr->LogMessageInterval;
      break;
    }
#endif /* (ETHTSYN_ANNOUNCE_TX_SUPPORT == STD_ON) */

  default:
    {
      prepareHdr = FALSE;
      break;
    }
  }

  if (prepareHdr == TRUE)
  {
    /* #20 Set common message header attributes. */
    /* Because the hole Ethernet transmission buffer (at least the part relevant for EthTSyn) is initialized with '0'
     * by the EthTSyn, setting message fields to '0' explicitly is not required (e.g. reserved fields). */
    ComMsgHdrPtr->TransSpecific_MessageType = (uint8)(ETHTSYN_HDR_COM_TRANSPORT_SPECIFIC | MsgType);                   /* SBSW_ETHTSYN_VALID_API_POINTER */
    ComMsgHdrPtr->Reserved_VersionGPtp = ETHTSYN_SUPPORTED_PROTOCOL_VERSION;                                           /* SBSW_ETHTSYN_VALID_API_POINTER */

    ComMsgHdrPtr->MessageLength = (uint16)EthTSyn_Htons(msgLength);                                                    /* SBSW_ETHTSYN_VALID_API_POINTER */
    ComMsgHdrPtr->DomainNumber = EthTSyn_GetIdOfTimeDomain(EthTSyn_GetTimeDomainIdxOfPort(PortIdx));                   /* SBSW_ETHTSYN_VALID_API_POINTER */

    ComMsgHdrPtr->Flags[0] = flagsFieldByte0;                                                                          /* SBSW_ETHTSYN_VALID_API_POINTER */

    EthTSyn_SetClockIdentity(ComMsgHdrPtr->SourceClockIdentity,
      ((EthTSyn_GetAddrCtrlState(EthTSyn_GetCtrlIdxOfPort(PortIdx)))->ClockIdentity));                                 /* SBSW_ETHTSYN_PASSING_API_POINTER */
    ComMsgHdrPtr->SourcePortNumber = (uint16)EthTSyn_Htons(portNumber);                                                /* SBSW_ETHTSYN_VALID_API_POINTER */

    ComMsgHdrPtr->SequenceId = (uint16)EthTSyn_Htons(sequenceId);                                                      /* SBSW_ETHTSYN_VALID_API_POINTER */
    ComMsgHdrPtr->Control = comHdrControl;                                                                             /* SBSW_ETHTSYN_VALID_API_POINTER */
    ComMsgHdrPtr->LogMessageInterval = logMessageInterval;                                                             /* SBSW_ETHTSYN_VALID_API_POINTER */
  }

} /* EthTSyn_UtilTx_PrepareCommonMsgHdr() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/***********************************************************************************************************************
 *  EthTSyn_UtilTx_HtonTimestamp
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_UtilTx_HtonTimestamp(
    ETHTSYN_P2VAR(EthTSyn_TimestampType)       GlobalTimestampPtr,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) LocalTimestampPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  GlobalTimestampPtr->NanoSeconds[0] = (uint8)(LocalTimestampPtr->nanoseconds >> 24u);                                 /* SBSW_ETHTSYN_VALID_API_POINTER */ /* SBSW_ETHTSYN_ARRAY_SIZE */
  GlobalTimestampPtr->NanoSeconds[1] = (uint8)(LocalTimestampPtr->nanoseconds >> 16u);                                 /* SBSW_ETHTSYN_VALID_API_POINTER */ /* SBSW_ETHTSYN_ARRAY_SIZE */
  GlobalTimestampPtr->NanoSeconds[2] = (uint8)(LocalTimestampPtr->nanoseconds >>  8u);                                 /* SBSW_ETHTSYN_VALID_API_POINTER */ /* SBSW_ETHTSYN_ARRAY_SIZE */
  GlobalTimestampPtr->NanoSeconds[3] = (uint8)(LocalTimestampPtr->nanoseconds >>  0u);                                 /* SBSW_ETHTSYN_VALID_API_POINTER */ /* SBSW_ETHTSYN_ARRAY_SIZE */

  GlobalTimestampPtr->Seconds[0] = (uint8)(LocalTimestampPtr->secondsHi >> 8u);                                        /* SBSW_ETHTSYN_VALID_API_POINTER */ /* SBSW_ETHTSYN_ARRAY_SIZE */
  GlobalTimestampPtr->Seconds[1] = (uint8)(LocalTimestampPtr->secondsHi >> 0u);                                        /* SBSW_ETHTSYN_VALID_API_POINTER */ /* SBSW_ETHTSYN_ARRAY_SIZE */

  GlobalTimestampPtr->Seconds[2] = (uint8)(LocalTimestampPtr->seconds >> 24u);                                         /* SBSW_ETHTSYN_VALID_API_POINTER */ /* SBSW_ETHTSYN_ARRAY_SIZE */
  GlobalTimestampPtr->Seconds[3] = (uint8)(LocalTimestampPtr->seconds >> 16u);                                         /* SBSW_ETHTSYN_VALID_API_POINTER */ /* SBSW_ETHTSYN_ARRAY_SIZE */
  GlobalTimestampPtr->Seconds[4] = (uint8)(LocalTimestampPtr->seconds >>  8u);                                         /* SBSW_ETHTSYN_VALID_API_POINTER */ /* SBSW_ETHTSYN_ARRAY_SIZE */
  GlobalTimestampPtr->Seconds[5] = (uint8)(LocalTimestampPtr->seconds >>  0u);                                         /* SBSW_ETHTSYN_VALID_API_POINTER */ /* SBSW_ETHTSYN_ARRAY_SIZE */

} /* EthTSyn_UtilTx_HtonTimestamp() */

/**********************************************************************************************************************
 *  EthTSyn_Util_TimestampPlusTimediff
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
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Util_TimestampPlusTimediff(
    ETHTSYN_P2VAR(EthTSyn_GlobalTimestampType) DestTimestampPtr,
  ETHTSYN_P2CONST(EthTSyn_TimediffType)        TimediffPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  EthTSyn_InternalTimestampType internalTimestamp;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Convert Global to internal Timestamp. */
  internalTimestamp.nanoseconds = DestTimestampPtr->nanoseconds;
  internalTimestamp.seconds     = DestTimestampPtr->seconds;
  internalTimestamp.seconds    |= ((uint64)DestTimestampPtr->secondsHi << 32u);

  /* #20 Check for positive value of time difference. */
  if((*TimediffPtr) > 0)
  {
    /* #200 Positive Timediff. Add Timediff to timestamp. */
    EthTSyn_UTimediffType TimediffU64Ns = (EthTSyn_UTimediffType)(*TimediffPtr);
    retVal = EthTSyn_Util_AddTimediffToTimestamp(TimediffU64Ns, &internalTimestamp);                                   /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
  }
  else if((*TimediffPtr) < 0)
  {
    /* #201 Negative Timediff. Subtract Timediff from timestamp. */
    EthTSyn_UTimediffType TimediffU64Ns = (EthTSyn_UTimediffType)(-(*TimediffPtr));
    retVal = EthTSyn_Util_SubtractTimediffFromTimestamp(TimediffU64Ns, &internalTimestamp);                            /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
  }
  else
  {
    /* #202 Timediff is zero -> add nothing. */
    retVal = E_OK;
  }

  /* The seconds field of the internal timestamp has a value range from 0 - (2^48-1) */
  /* #30 Check if result is valid. */
  if(retVal == E_OK)
  {
    /* #300 Convert Internal to global Timestamp. */
    DestTimestampPtr->nanoseconds = internalTimestamp.nanoseconds;                                                     /* SBSW_ETHTSYN_VALID_API_POINTER */
    DestTimestampPtr->seconds     = (uint32)internalTimestamp.seconds;                                                 /* SBSW_ETHTSYN_VALID_API_POINTER */
    DestTimestampPtr->secondsHi   = (uint16)(internalTimestamp.seconds >> 32u);                                        /* SBSW_ETHTSYN_VALID_API_POINTER */
  }

  return retVal;
} /* EthTSyn_Util_TimestampPlusTimediff() */

/**********************************************************************************************************************
 *  EthTSyn_Util_TimestampMinusTimestamp
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
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Util_TimestampMinusTimestamp(
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) Timestamp1Ptr,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) Timestamp2Ptr,
    ETHTSYN_P2VAR(EthTSyn_TimediffType)        TimediffPtr)
 {
   /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  EthTSyn_TimediffType diffSeconds;
  EthTSyn_TimediffType diffNanoseconds;
  EthTSyn_UTimediffType diffSecondsU64;
  EthTSyn_InternalTimestampType internalTimestamp1;
  EthTSyn_InternalTimestampType internalTimestamp2;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Convert Global to internal Timestamp. */
  internalTimestamp1.nanoseconds = Timestamp1Ptr->nanoseconds;
  internalTimestamp1.seconds     = Timestamp1Ptr->seconds;
  internalTimestamp1.seconds    |= ((uint64)Timestamp1Ptr->secondsHi << 32U);

  internalTimestamp2.nanoseconds = Timestamp2Ptr->nanoseconds;
  internalTimestamp2.seconds     = Timestamp2Ptr->seconds;
  internalTimestamp2.seconds    |= ((uint64)Timestamp2Ptr->secondsHi << 32U);


  /* #20 Check if difference in seconds is suitable for nanoseconds difference value.
   * No overflow is expected due Seconds field of EthTSyn_TimestampType should not exceed 2^48. */
  diffSeconds = (EthTSyn_TimediffType)(internalTimestamp1.seconds - internalTimestamp2.seconds);

  /* check if time difference is less zero */
  if(diffSeconds < 0)
  {
    diffSecondsU64 = (EthTSyn_UTimediffType)(-diffSeconds);
  }
  /* time difference is greater zero */
  else
  {
    diffSecondsU64 = (EthTSyn_UTimediffType)diffSeconds;
  }

  /* #30 Round up difference in seconds due to handle possible nanoseconds overflow in further calculation. */
  diffSecondsU64++;
  /* #40 Check if time difference in seconds is suitable for nanoseconds difference value. */
  if((EthTSyn_UTimediffType)diffSecondsU64 < (EthTSyn_UTimediffType)ETHTSYN_TIMEDIFF_MAX_SECONDS)
  {
    /* #50 Calculate time difference. */
    /* calculate correct nanoseconds time difference */
    diffNanoseconds = (EthTSyn_TimediffType)
      ((EthTSyn_TimediffType)internalTimestamp1.nanoseconds - (EthTSyn_TimediffType)internalTimestamp2.nanoseconds);

    /* set seconds value */
    *TimediffPtr = diffSeconds * ETHTSYN_TIMESTAMP_MAX_NANOSECONDS;                                                    /* SBSW_ETHTSYN_VALID_API_POINTER */

    /* add nanoseconds value */
    *TimediffPtr = *TimediffPtr + diffNanoseconds;                                                                     /* SBSW_ETHTSYN_VALID_API_POINTER */

    retVal = E_OK;
  }
  /* timediff value exceeds max nanoseconds value */
  else
  {
    *TimediffPtr = 0;                                                                                                  /* SBSW_ETHTSYN_VALID_API_POINTER */
  }

  return retVal;
} /* EthTSyn_Util_TimestampMinusTimestamp() */

#if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF)
# if ( (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) || (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) )
/**********************************************************************************************************************
 *  EthTSyn_Util_CheckAndHandleRawTimestampOverflow
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(EthTSyn_GlobalTimestampType, ETHTSYN_CODE) EthTSyn_Util_CheckAndHandleRawTimestampOverflow(
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) Timestamp1Ptr,
                  EthTSyn_TimestampRawType     Timestamp2)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_GlobalTimestampType resultingTimestamp;
  uint64 timestamp2Uint64 = (uint64)Timestamp2;
  const uint32 timestamp1Uint32 =
    ((Timestamp1Ptr->seconds) * ETHTSYN_NANOSECONDS_PER_SECOND) + (Timestamp1Ptr->nanoseconds);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if an overflow occurred. */
  if(timestamp2Uint64 < timestamp1Uint32)
  {
    /* #100 Overflow occurred. Correct timestamp 1 accordingly. */
    timestamp2Uint64 += 1u; /* Add one for handling the wraparound (MaxValue + 1 = 0) */
    timestamp2Uint64 += ETHTSYN_RAW_TIME_MAX_NANOSECONDS_UINT64;
  }

  /* #20 Return the possibly corrected timestamp 1. */
  resultingTimestamp.secondsHi = 0;
  resultingTimestamp.seconds = (uint32)(timestamp2Uint64 / ETHTSYN_NANOSECONDS_PER_SECOND);
  resultingTimestamp.nanoseconds = (uint32)(timestamp2Uint64 % ETHTSYN_NANOSECONDS_PER_SECOND);

  return resultingTimestamp;
} /* EthTSyn_Util_CheckAndHandleRawTimestampOverflow() */

/**********************************************************************************************************************
 *  EthTSyn_Util_RawTimeToTimestamp
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(EthTSyn_GlobalTimestampType, ETHTSYN_CODE) EthTSyn_Util_RawTimeToTimestamp(
  EthTSyn_TimestampRawType RawTimestamp)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_GlobalTimestampType convertedTimestamp;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Convert the given raw timestamp into a full qualified EthTSyn_GlobalTimestampType. */
  convertedTimestamp.secondsHi = 0;
  convertedTimestamp.seconds = (uint32)(RawTimestamp / ETHTSYN_NANOSECONDS_PER_SECOND);
  convertedTimestamp.nanoseconds = (uint32)(RawTimestamp % ETHTSYN_NANOSECONDS_PER_SECOND);

  return convertedTimestamp;
}
# endif /* ( (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) || (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) ) */
#endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) */

/**********************************************************************************************************************
 *  EthTSyn_UtilRx_CheckMessageGeneral
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(uint8, ETHTSYN_CODE) EthTSyn_UtilRx_CheckMessageGeneral(
  ETHTSYN_P2CONST(uint8) MsgPtr,
                  uint16 LenByte)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Message length sanity check */
  if(LenByte < ETHTSYN_HDR_COM_LENGTH)
  {
    /* Invalid message length, message is smaller than common header --> drop message */
    /* Note: This should never happen since the common header length is 34 while the min Eth Frame Payload size is 46 */
    errorId = ETHTSYN_E_MSG_LENGTH;
  }
  else
  {
    /* Get the common message hdr */
    ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) comMsgHdrPtr = (ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType))&MsgPtr[0]; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */

    /* #20 Check header message length vs. LenByte */
    if((uint16)EthTSyn_Ntohs(comMsgHdrPtr->MessageLength) > LenByte)
    {
      errorId = ETHTSYN_E_MSG_LENGTH;
    }
    /* #30 Check EthTSyn Protocol version */
    else if(ETHTSYN_HDR_COM_VERSION(comMsgHdrPtr->Reserved_VersionGPtp) != ETHTSYN_SUPPORTED_PROTOCOL_VERSION)
    {
      /* Invalid EthTSyn protocol version --> drop message */
      errorId = ETHTSYN_E_PROTOCOL_VERSION;
    }
    else
    {
      errorId = ETHTSYN_E_NO_ERROR;
    }
  }

  return errorId;
} /* EthTSyn_UtilRx_CheckMessageGeneral() */

/**********************************************************************************************************************
 *  EthTSyn_UtilRx_CheckMessageTypeAndLength
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(uint8, ETHTSYN_CODE) EthTSyn_UtilRx_CheckMessageTypeAndLength(
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) ComMsgHdrPtr,
                  uint16                    LenByte)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  uint16 expectedMsgLength = 0;
  boolean expectedMsgLengthIsMinLength = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Try to get the expected message length and validate message type. */
  errorId = EthTSyn_UtilRx_GetExpectedMsgLengthWithMsgTypeCheck(ComMsgHdrPtr, &expectedMsgLength,
      &expectedMsgLengthIsMinLength);                                                                                  /* SBSW_ETHTSYN_PASSING_API_POINTER */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */

  if(errorId == ETHTSYN_E_NO_ERROR)
  {
    /* #20 Verify message length. */
    uint16 msgLengthHeader = (uint16)EthTSyn_Ntohs(ComMsgHdrPtr->MessageLength);
    if(expectedMsgLengthIsMinLength == TRUE)
    {
      if( (LenByte < expectedMsgLength) || (msgLengthHeader < expectedMsgLength) )
      {
        errorId = ETHTSYN_E_MSG_LENGTH;
      }
    }
    else
    {
      if( (LenByte < expectedMsgLength) || (msgLengthHeader != expectedMsgLength) )
      {
        errorId = ETHTSYN_E_MSG_LENGTH;
      }
    }
  }

  return errorId;
} /* EthTSyn_UtilRx_CheckMessageTypeAndLength() */

#if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_UtilRx_QualifyAnnounceMsg
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
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_UtilRx_QualifyAnnounceMsg(
                  EthTSyn_IntPortIdxType    PortIdx,
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) ComMsgPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  ETHTSYN_CONSTP2CONST(EthTSyn_AnnounceMsgType) announceMsgPtr =
    (ETHTSYN_P2CONST(EthTSyn_AnnounceMsgType)) &((ETHTSYN_P2CONST(uint8)) ComMsgPtr)[ETHTSYN_HDR_COM_LENGTH]; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */
  uint16 pathSequenceTlvCnt;
  uint16 assumedLenByte;
  uint16 stepsRemovedCnt;
  uint16 lenByte = (uint16)EthTSyn_Ntohs(ComMsgPtr->MessageLength);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get attributes of announce message. */
  ETHTSYN_GET_UINT16(announceMsgPtr->StepsRemoved, 0, stepsRemovedCnt);

  /* #20 Sanity check of announce message length field. */
  if((EthTSyn_Ntohs(announceMsgPtr->LengthField) % ETHTSYN_MSG_ANNOUNCE_PATH_SEQUENCE_ELEMENT_LENGTH) == 0)
  {
    const EthTSyn_CtrlIdxOfPortType ctrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);
    const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
    const EthTSyn_AnnounceInfoIdxOfSlavePortType announceInfoIdx = EthTSyn_GetAnnounceInfoIdxOfSlavePort(slavePortIdx);
    ETHTSYN_CONSTP2CONST(EthTSyn_CtrlStateType) ctrlStatePtr = EthTSyn_GetAddrCtrlState(ctrlIdx);
    pathSequenceTlvCnt = (uint16)(EthTSyn_Ntohs(announceMsgPtr->LengthField) /
        ETHTSYN_MSG_ANNOUNCE_PATH_SEQUENCE_ELEMENT_LENGTH);

    /* #30 Calculate assumed length including the tlv path sequence. Subtract the
     * ETHTSYN_MSG_ANNOUNCE_PATH_SEQUENCE_ELEMENT_LENGTH because the length of one element is already
     * included in the ETHTSYN_MSG_ANNOUNCE_LENGTH. */
    assumedLenByte = (uint16)(ETHTSYN_MSG_ANNOUNCE_LENGTH + ( EthTSyn_Ntohs(announceMsgPtr->LengthField) -
        ETHTSYN_MSG_ANNOUNCE_PATH_SEQUENCE_ELEMENT_LENGTH ));

    /* #40 Check that received Announce message is not from own system and that own system is not included in the path
     * sequence. */
     /* PRQA S 3415 5 */ /* MD_EthTSyn_3415_ReadOnly */
    if(
      (EthTSyn_ClockIdentityIsEqual(ComMsgPtr->SourceClockIdentity, (ctrlStatePtr->ClockIdentity)) == FALSE) &&        /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
      (EthTSyn_ClockIdentityIsEqual(announceMsgPtr->GrandmasterIdentity, (ctrlStatePtr->ClockIdentity)) == FALSE) &&   /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
      (lenByte == assumedLenByte) &&
      (stepsRemovedCnt <= EthTSyn_GetMaxeStepsRemovedOfAnnounceInfo(announceInfoIdx))
      )
    {
      ETHTSYN_P2CONST(EthTSyn_ClockIdentityType) pathSequenceClockIdentityPtr;
      uint16_least i;
      retVal = E_OK;

      /* set message pointer to the clock identity of the path sequence */
      pathSequenceClockIdentityPtr = (ETHTSYN_P2CONST(EthTSyn_ClockIdentityType))announceMsgPtr->ClockIdentity; /* PRQA S 0310 */ /* MD_EthTSyn_0310_PathTrace */
      for(i = 0; i < pathSequenceTlvCnt; i++)
      {
        if(EthTSyn_ClockIdentityIsEqual(pathSequenceClockIdentityPtr[i], ctrlStatePtr->ClockIdentity) == TRUE)         /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */
        {
          retVal = E_NOT_OK;
          break;
        }
      }
    }
  }

  return retVal;
} /* EthTSyn_UtilRx_QualifyAnnounceMsg() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
#endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_UtilRx_SyncPortRoleCheckWithMasterSlaveConflictDetection
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
FUNC(boolean, ETHTSYN_CODE) EthTSyn_UtilRx_SyncPortRoleCheckWithMasterSlaveConflictDetection(
  EthTSyn_IntPortIdxType PortIdx,
  uint64                 SrcClockIdentity)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 runtimeErrorId;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check Port Role. */
#if ( (ETHTSYN_SLAVE_SUPPORT == STD_ON) && (ETHTSYN_MASTER_SUPPORT == STD_ON) )
  if(EthTSyn_IsSlavePortUsedOfPort(PortIdx) == TRUE)
#endif /* ( (ETHTSYN_SLAVE_SUPPORT == STD_ON) && (ETHTSYN_MASTER_SUPPORT == STD_ON) ) */
#if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
  {
# if ( (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) || \
       (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON) || \
       (ETHTSYN_SRC_PORT_IDENT_CHECK_SUPPORT == STD_ON) \
      )
    const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
    runtimeErrorId = ETHTSYN_E_NO_ERROR;
    /* #20 Check if master clock identity is already valid. */
    if(EthTSyn_IsGmPresentOfSystemState(timeDomainIdx) == TRUE)
    {
      /* #200 Master clock identity is valid: Verify the source clock identity and set errorId to ETHTSYN_E_TSCONFLICT
       *      in case of invalid source clock identity. */
      if(SrcClockIdentity != EthTSyn_GetGmClockIdentityOfSystemState(timeDomainIdx))
      {
        runtimeErrorId = ETHTSYN_E_TSCONFLICT;
      }
    }
# else
    runtimeErrorId = ETHTSYN_E_NO_ERROR;
# endif /* ( (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) || \
       (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON) || \
       (ETHTSYN_SRC_PORT_IDENT_CHECK_SUPPORT == STD_ON)) */
# if ( (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) || (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON) )
    else
    {
      /* #201 Master clock identity is not valid: Check if announce is used for the slave port. */
      const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
      if(EthTSyn_IsAnnounceInfoUsedOfSlavePort(slavePortIdx) == TRUE)
      {
        /* #2010 Announce is used: Set errorId to ETHTSYN_E_TSCONFLICT. */
        runtimeErrorId = ETHTSYN_E_TSCONFLICT;
      }
#  if (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON)
      else
      {
        /* #2011 Announce is not used: Store the master clock identity. */
        EthTSyn_SetGmPresentOfSystemState(timeDomainIdx, TRUE);                                                        /* SBSW_ETHTSYN_CSL03 */
        EthTSyn_SetGmClockIdentityOfSystemState(timeDomainIdx, SrcClockIdentity);                                      /* SBSW_ETHTSYN_CSL03 */
      }
#  endif /* (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON) */
    }
# endif /* ( (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) || (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON) ) */
  }
#endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */
#if ( (ETHTSYN_SLAVE_SUPPORT == STD_ON) && (ETHTSYN_MASTER_SUPPORT == STD_ON) )
  else
#endif /* ( (ETHTSYN_SLAVE_SUPPORT == STD_ON) && (ETHTSYN_MASTER_SUPPORT == STD_ON) ) */
#if (ETHTSYN_MASTER_SUPPORT == STD_ON)
  {
    /* #30 Master Port: Set errorId to ETHTSYN_E_TMCONFLICT. */
    runtimeErrorId = ETHTSYN_E_TMCONFLICT;
  }
#endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */

#if (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON)
  /* #40 Report runtime error if any occurred. */
  if(runtimeErrorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportRuntimeError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID,
        ETHTSYN_SID_SYNC_PORT_ROLE_CHECK_WITH_MS_CONFLICT_DETECT, runtimeErrorId);
  }
#endif /* (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON) */

#if ((ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_OFF) && \
     (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_OFF) && \
     (ETHTSYN_SRC_PORT_IDENT_CHECK_SUPPORT == STD_OFF) \
    )
  ETHTSYN_DUMMY_STATEMENT(SrcClockIdentity); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# if ( (ETHTSYN_SLAVE_SUPPORT == STD_OFF) || (ETHTSYN_MASTER_SUPPORT == STD_OFF) )
  ETHTSYN_DUMMY_STATEMENT(PortIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* ( (ETHTSYN_SLAVE_SUPPORT == STD_OFF) || (ETHTSYN_MASTER_SUPPORT == STD_OFF) ) */
#endif

  return (boolean)(runtimeErrorId == ETHTSYN_E_NO_ERROR); /* PRQA S 3355, 3356 */ /* MD_EthTSyn_3355, MD_EthTSyn_3356 */
} /* EthTSyn_UtilRx_SyncPortRoleCheckWithMasterSlaveConflictDetection() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_ProvideTxBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_UtilTx_ProvideTxBuffer(
               EthTSyn_EthIfCtrlIdxOfCtrlType EthIfCtrlIdx,
               uint8                          FramePrio,
 ETHTSYN_P2VAR(EthTSyn_EthTxBufferStructType) TxBufferPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint16 bufferLength = TxBufferPtr->Length;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Request Ethernet tx buffer from EthIf. */
  /* PRQA S 0310 2 */ /* MD_EthTSyn_0310_MsgStructRev */
  if(EthIf_ProvideTxBuffer(EthIfCtrlIdx, ETHTSYN_FRAME_TYPE, FramePrio, &(TxBufferPtr->BufferIdx),
      (ETHTSYN_P2VAR(ETHTSYN_P2VAR(Eth_DataType)))&(TxBufferPtr->BufferPtr), &bufferLength) == BUFREQ_OK)              /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
  {
    /* #20 Tx buffer allocated -> initialize buffer with '0'. */
    IpBase_Fill((ETHTSYN_P2VAR(IpBase_CopyDataType))(TxBufferPtr->BufferPtr), 0, TxBufferPtr->Length);                 /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */

    /* #30 Get the Frame Id if applicable. */
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
    TxBufferPtr->FrameId = EthTSyn_Util_GetFrameId(TxBufferPtr->BufferPtr, bufferLength);                              /* SBSW_ETHTSYN_VALID_API_POINTER */ /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
    retVal = E_OK;
  }

  return retVal;
} /* EthTSyn_UtilTx_ProvideTxBuffer() */

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_PrepareTransmission
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
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_UtilTx_PrepareTransmission(
                  EthTSyn_EthIfCtrlIdxOfCtrlType   EthIfCtrlIdx,
                  uint8                            TxBufferIdx,
                  EthTSyn_EnableTimestampFlagsType EnableTsFlags,
  ETHTSYN_P2CONST(EthTSyn_SwtMgmtInfoType)         SwtMgmtInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK; /* Initialize with E_OK because E_OK should be returned when no action is performed */
#if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  boolean enableHwTimestamp = EthTSyn_Util_AreBitsSet(EnableTsFlags, ETHTSYN_ENABLE_TS_HW_TS_MASK);
#endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

  /* ----- Implementation ----------------------------------------------- */
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
  /* #10 Check if switch information have to be set. */
  if(SwtMgmtInfoPtr != NULL_PTR)
  {
    /* #30 Set switch management information. */
    retVal = EthIf_SetSwitchMgmtInfo(EthIfCtrlIdx, TxBufferIdx, SwtMgmtInfoPtr);                                       /* SBSW_ETHTSYN_PASSING_API_POINTER */
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
    /* #20 Enable switch egress timestamp if required. */
    if((retVal == E_OK) && (EthTSyn_Util_AreBitsSet(EnableTsFlags, ETHTSYN_ENABLE_TS_SWT_TS_MASK) == TRUE)) /* PRQA S 3415 */ /* MD_EthTSyn_3415_ReadOnly */
    {
      retVal = EthIf_SwitchEnableEgressTimeStamp(EthIfCtrlIdx, TxBufferIdx, SwtMgmtInfoPtr);                           /* SBSW_ETHTSYN_PASSING_API_POINTER */
#  if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
      enableHwTimestamp = (boolean)!EthTSyn_Util_AreBitsSet(EnableTsFlags, ETHTSYN_ENABLE_TS_HW_XOR_SWT_TS_MASK);
#  endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */
    }
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */
  }
  if(retVal == E_OK)
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
  {
#if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
    /* #40 Enable egress timestamp (HW) if required. */
    if(enableHwTimestamp == TRUE)
    {
      retVal = EthIf_EnableEgressTimestamp(EthIfCtrlIdx, TxBufferIdx);
    }
#endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */
  }

  /* #50 Handle dummy statements. */
#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
  ETHTSYN_DUMMY_STATEMENT(SwtMgmtInfoPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF)
  ETHTSYN_DUMMY_STATEMENT(EthIfCtrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETHTSYN_DUMMY_STATEMENT(TxBufferIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) */
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */
#if ( (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF) && (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) )
  ETHTSYN_DUMMY_STATEMENT(EnableTsFlags); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* ( (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF) && (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) ) */

  return retVal;
} /* EthTSyn_UtilTx_PrepareTransmission() */

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_Transmit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_UtilTx_Transmit(
  EthTSyn_EthIfCtrlIdxOfCtrlType EthIfCtrlIdx,
  uint8                          TxBufferIdx,
  uint16                         TxLength)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Trigger the transmission of the passed Ethernet transmission buffer with the passed length. */
  /* PRQA S 0311 2 */ /* MD_EthTSyn_0311 */
  return EthIf_Transmit(EthIfCtrlIdx, TxBufferIdx, ETHTSYN_FRAME_TYPE, TRUE, TxLength,
    (ETHTSYN_P2VAR(uint8))EthTSyn_DestinationMac);                                                                     /* SBSW_ETHTSYN_CONSTANT_ARRAY_AS_POINTER */
} /* EthTSyn_UtilTx_Transmit() */

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_ReleaseTxBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_UtilTx_ReleaseTxBuffer(EthTSyn_EthIfCtrlIdxOfCtrlType EthIfCtrlIdx,
  uint8 TxBufferIdx)
{
  /* #10 Release the Ethernet transmission buffer by calling EthIf_Transmit with a length of '0' */
  /* PRQA S 0311 2 */ /* MD_EthTSyn_0311 */
  (void)EthIf_Transmit(EthIfCtrlIdx, TxBufferIdx, ETHTSYN_FRAME_TYPE, FALSE, 0,
    (ETHTSYN_P2VAR(uint8))EthTSyn_DestinationMac);                                                                     /* SBSW_ETHTSYN_CONSTANT_ARRAY_AS_POINTER */
} /* EthTSyn_UtilTx_ReleaseTxBuffer() */

/**********************************************************************************************************************
 *  EthTSyn_Util_TransformClockIdentityToUint64
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(uint64, ETHTSYN_CODE) EthTSyn_Util_TransformClockIdentityToUint64(
  ETHTSYN_P2CONST(EthTSyn_ClockIdentityBaseType) ClockIdentityPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Transform the passed uint8 array clock identity by shifting of each element. The highest byte is stored at
   *     index '0' of the passed array. */
  return (uint64)(
      (((uint64)ClockIdentityPtr[0]) << 56u) |
      (((uint64)ClockIdentityPtr[1]) << 48u) |
      (((uint64)ClockIdentityPtr[2]) << 40u) |
      (((uint64)ClockIdentityPtr[3]) << 32u) |
      (((uint64)ClockIdentityPtr[4]) << 24u) |
      (((uint64)ClockIdentityPtr[5]) << 16u) |
      (((uint64)ClockIdentityPtr[6]) <<  8u) |
      (((uint64)ClockIdentityPtr[7]) <<  0u)
      );
} /* EthTSyn_Util_TransformClockIdentityToUint64() */

#define ETHTSYN_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Justification for module-specific MISRA deviations:
 * see file EthTSyn.c
*/

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Util_Int.c
 *********************************************************************************************************************/
