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
 *         \file  EthTSyn_Int.h
 *        \brief  EthTSyn internal header file
 *
 *      \details  Contains internal definitions and declarations used by the EthTSyn only
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


#if !defined(ETHTSYN_INT_H)
# define ETHTSYN_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthTSyn.h"
# include "EthTSyn_Util_Int.h"
# include "SchM_EthTSyn.h"
# include "StbM.h"

# if ( (ETHTSYN_DEV_ERROR_REPORT == STD_ON) || (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON) )
#  include "Det.h"
# endif /* ETHTSYN_DEV_ERROR_REPORT || ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION */

# include "IpBase.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# if !defined (ETHTSYN_LOCAL_INLINE) /* COV_MSR_COMPATIBILITY */
#  define ETHTSYN_LOCAL_INLINE LOCAL_INLINE
# endif


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
/* ETHTSYN General */
# define ETHTSYN_SUPPORTED_PROTOCOL_VERSION                   (0x02u)
/* 10^9 nanoseconds per second */
# define ETHTSYN_NANOSECONDS_PER_SECOND                       (1000000000uL)
# define ETHTSYN_RAW_TIME_MAX_NANOSECONDS_UINT64              (0x00000000FFFFFFFFuLL)

/* ETHTSYN Header Length */
# define ETHTSYN_HDR_COM_LENGTH                               (34u)
# define ETHTSYN_HDR_COM_RESERVED_1_LENGTH                    (4u)
# define ETHTSYN_HDR_COM_CORRECTION_FIELD_LENGTH              (8u)
# define ETHTSYN_HDR_COM_TRANSPORT_SPECIFIC                   (0x10u)
# define ETHTSYN_HDR_COM_CONTROL_SYNC                         (0x00u)
# define ETHTSYN_HDR_COM_CONTROL_FOLLOW_UP                    (0x02u)
# define ETHTSYN_HDR_COM_CONTROL_ANNOUNCE                     (0x05u)
# define ETHTSYN_HDR_COM_CONTROL_PDELAY_REQ                   (0x05u)
# define ETHTSYN_HDR_COM_CONTROL_PDELAY_RESP                  (0x05u)
# define ETHTSYN_HDR_COM_CONTROL_PDELAY_RESP_FOLLOW_UP        (0x05u)

# define ETHTSYN_HDR_COM_LOG_MESSAGE_INTERVAL_DEFAULT         (0x7Fu)

/* ETHTSYN Header Flags */
# define ETHTSYN_FLAGS_OCTET_0_TWO_STEP                       (0x02u)
# define ETHTSYN_FLAGS_OCTET_1_LEAP61                         (0x01u)
# define ETHTSYN_FLAGS_OCTET_1_LEAP59                         (0x02u)
# define ETHTSYN_FLAGS_OCTET_1_UTC_OFFSET_VALID               (0x04u)
# define ETHTSYN_FLAGS_OCTET_1_ETHTSYN_TIMESCALE              (0x08u)
# define ETHTSYN_FLAGS_OCTET_1_TIME_TRACEABLE                 (0x10u)
# define ETHTSYN_FLAGS_OCTET_1_FREQUENCY_TRACEABLE            (0x20u)

/* PRQA S 3453 4 */ /* MD_MSR_19.7 */
# define ETHTSYN_HDR_COM_MSG_TYPE(param)                      ((uint8)(param) & 0x0F)
# define ETHTSYN_HDR_COM_VERSION(param)                       ((uint8)(param) & 0x0F)

/* Message Pdelay values */
# define ETHTSYN_MSG_P_DELAY_PAYLOAD_LENGTH                   (20u)

/* Message PdelayReq values */
# define ETHTSYN_MSG_P_DELAY_REQ_LENGTH                       (ETHTSYN_MSG_P_DELAY_PAYLOAD_LENGTH \
                                                              + ETHTSYN_HDR_COM_LENGTH)
# define ETHTSYN_MSG_P_DELAY_REQ_RESERVED_0_LENGTH            (10u)
# define ETHTSYN_MSG_P_DELAY_REQ_RESERVED_1_LENGTH            (10u)

/* Message PdelayResp values */
# define ETHTSYN_MSG_P_DELAY_RESP_LENGTH                      (ETHTSYN_MSG_P_DELAY_PAYLOAD_LENGTH \
                                                              + ETHTSYN_HDR_COM_LENGTH)

/* Message PdelayRespFollowUp values */
# define ETHTSYN_MSG_P_DELAY_RESP_FOLLOW_UP_LENGTH            (ETHTSYN_MSG_P_DELAY_PAYLOAD_LENGTH \
                                                              + ETHTSYN_HDR_COM_LENGTH)

/* Message FollowUp values */
/* FollowUp message lengths -> EthTSyn_Cfg.h */
/* Precise Origin Timestamp length (10) + complete FollowUp IEEE Tlv length (32) */
# define ETHTSYN_FOLLOW_UP_AR_TLV_OFFSET                             (42u)
# define ETHTSYN_FOLLOW_UP_TLV_TYPE                                  (0x03u)
# define ETHTSYN_FOLLOW_UP_TLV_LENGTH_FIELD                          (28u)
# define ETHTSYN_FOLLOW_UP_ORGANISATION_ID                           (0x000080C2uL)
# define ETHTSYN_FOLLOW_UP_ORGANISATION_SUBTYPE                      (0x00000001uL)
# define ETHTSYN_MSG_FOLLOW_UP_PRECISE_ORIGIN_TS_SECONDS_LENGTH      (6u)
# define ETHTSYN_MSG_FOLLOW_UP_PRECISE_ORIGIN_TS_NANOSECONDS_LENGTH  (4u)
# define ETHTSYN_MSG_FOLLOW_UP_ORGANISATION_ID_LENGTH                (3u)
# define ETHTSYN_MSG_FOLLOW_UP_ORGANISATION_SUB_TYPE_LENGTH          (3u)
# define ETHTSYN_MSG_FOLLOW_UP_LAST_GM_PHASE_CHANGE_LENGTH           (12u)
# define ETHTSYN_MSG_FOLLOW_UP_SCALED_LAST_GM_FREQ_CHANGE_LENGTH     (4u)
# define ETHTSYN_MSG_FOLLOW_UP_CORRECTION_FIELD_MULTIPLIER           (65536u)
# define ETHTSYN_MSG_FOLLOW_UP_CORRECTION_FIELD_SHIFT                (16u)
# define ETHTSYN_MSG_FOLLOW_UP_CORRECTION_FIELD_LENGTH               (8u)

/* PRQA S 3453 2 */ /* MD_MSR_19.7 */
# define ETHTSYN_MSG_FOLLOW_UP_CORRECTION_FIELD_TO_NS(CorrectionField)  ((uint64)((CorrectionField) >> 16u))
# define ETHTSYN_MSG_FOLLOW_UP_NS_TO_CORRECTION_FIELD(Nanoseconds)      ((uint64)((Nanoseconds) << 16u))

/* Message Sync values */
# define ETHTSYN_MSG_SYNC_PAYLOAD_LENGTH                      (10u)
# define ETHTSYN_MSG_SYNC_LENGTH                              (ETHTSYN_MSG_SYNC_PAYLOAD_LENGTH \
                                                              + ETHTSYN_HDR_COM_LENGTH)
# define ETHTSYN_MSG_SYNC_RESERVED_LENGTH                     (10u)

/* ETHTSYN Announce values */
# define ETHTSYN_MSG_ANNOUNCE_PAYLOAD_LENGTH                  (42u)
# define ETHTSYN_MSG_ANNOUNCE_LENGTH                          (ETHTSYN_MSG_ANNOUNCE_PAYLOAD_LENGTH \
                                                              + ETHTSYN_HDR_COM_LENGTH)
# define ETHTSYN_MSG_ANNOUNCE_PATH_SEQUENCE_ELEMENT_LENGTH    (8u)
# define ETHTSYN_ANNOUNCE_PRIORITY_1_NETWORK_INFRASTRUCTURE   (246u)
# define ETHTSYN_ANNOUNCE_PRIORITY_1_OTHER_SYSTEM             (248u)
# define ETHTSYN_ANNOUNCE_PRIORITY_1_NOT_GM_CAPABLE           (255u)

# define ETHTSYN_ANNOUNCE_PRIORITY_2_DEFAULT                  (248u)
# define ETHTSYN_ANNOUNCE_CLOCK_CLASS_UNKNOWN                 (248u)
# define ETHTSYN_ANNOUNCE_CLOCK_CLASS_NOT_GM_CAPABLE          (255u)
# define ETHTSYN_ANNOUNCE_CLOCK_ACCURACY_UNKNOWN              (254u)
# define ETHTSYN_ANNOUNCE_OFFSET_SCALED_LOG_UNKNOWN           (0x4100u)
# define ETHTSYN_ANNOUNCE_TIME_SOURCE_INTERNAL_OSCILLATOR     (0xA0u)
# define ETHTSYN_ANNOUNCE_TLV_TYPE                            (0x08u)
# define ETHTSYN_ANNOUNCE_TLV_LENGTH_FIELD                    (0x08u)

/* ETHTSYN Message Types */
# define ETHTSYN_MSG_TYPE_ANNOUNCE                            (0x0Bu)
# define ETHTSYN_MSG_TYPE_SIGNALING                           (0x0Cu)
# define ETHTSYN_MSG_TYPE_SYNC                                (0x00u)
# define ETHTSYN_MSG_TYPE_PDELAY_REQ                          (0x02u)
# define ETHTSYN_MSG_TYPE_PDELAY_RESP                         (0x03u)
# define ETHTSYN_MSG_TYPE_FOLLOW_UP                           (0x08u)
# define ETHTSYN_MSG_TYPE_PDELAY_RES_FOLLOW_UP                (0x0Au)
# define ETHTSYN_MSG_TYPE_INVALID                             (0xFFu)

/* TimeBaseStatus Masks */
# define ETHTSYN_TIME_BASE_STATUS_TIMEOUT_MASK                (0x01u)
# define ETHTSYN_TIME_BASE_STATUS_SYNC_TO_GW_MASK             (0x04u)
# define ETHTSYN_TIME_BASE_STATUS_SYNC_TO_GW_SHIFT            (2u)
# define ETHTSYN_TIME_BASE_STATUS_GLOBAL_TIME_BASE_MASK       (0x08u)
# define ETHTSYN_TIME_BASE_STATUS_TIMELEAP_FUTURE_MASK        (0x10u)
# define ETHTSYN_TIME_BASE_STATUS_TIMELEAP_PAST_MASK          (0x20u)

/* ETHTSYN Ar (Sub)-Tlv values */
# define ETHTSYN_AR_SUB_TLV_OFS_TIME_SEC_SECONDS_OFFSET       (2u)

# define ETHTSYN_UINT16_MAX_VALUE                             (65535u)
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
# define ETHTSYN_START_SEC_VAR_ZERO_INIT_8BIT
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
# include "MemMap.h"

extern VAR(EthTSyn_StateEnumType, ETHTSYN_VAR_ZERO_INIT) EthTSyn_State;

# define ETHTSYN_STOP_SEC_VAR_ZERO_INIT_8BIT
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
# include "MemMap.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define ETHTSYN_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/**********************************************************************************************************************
 *  GLOBAL INLINE FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_SetClockIdentity
 *********************************************************************************************************************/
/*! \brief       Sets a clock identity to the passed value.
 *  \details     -
 *  \param[out]  TargetPtr    Pointer to the clock identity that should be set
 *  \param[in]   SourcePtr    Pointer to the clock identity that should be used as source value
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different target clock identities or same source clock identities
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetClockIdentity(
                  EthTSyn_ClockIdentityType      TargetPtr,
  ETHTSYN_P2CONST(EthTSyn_ClockIdentityBaseType) SourcePtr );

/**********************************************************************************************************************
 *  EthTSyn_ClockIdentityIsEqual
 *********************************************************************************************************************/
/*! \brief      Checks if the passed clock identities are equal.
 *  \details    -
 *  \param[in]  Value                      Clock identity that should be compared.
 *  \param[in]  Reference                  Reference Clock identity that is used for comparison.
 *  \return     TRUE - The passed clock identities are equal.
 *  \return     FALSE - The passed clock identity are not equal.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \note       no side-effects
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_ClockIdentityIsEqual(
  ETHTSYN_P2CONST(EthTSyn_ClockIdentityBaseType) Value,
  ETHTSYN_P2CONST(EthTSyn_ClockIdentityBaseType) Reference);

/**********************************************************************************************************************
 *  EthTSyn_NtohTimestamp
 *********************************************************************************************************************/
/*! \brief       Converts an received Timestamp from Network-Byte-Order to Host-Byte-Order and into the locally used
                 TimestampType.
 *  \details     -
 *  \param[out]  LocalTimestampPtr     Pointer to the local timestamp value in Host-Byte-Order (destination)
 *  \param[in]   GlobalTimestampPtr    Pointer to the EthTSyn timestamp value in Network-Byte-Order (source)
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE for different local timestamps or same global timestamps
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_NtohTimestamp(
    ETHTSYN_P2VAR(EthTSyn_GlobalTimestampType) LocalTimestampPtr,
  ETHTSYN_P2CONST(EthTSyn_TimestampType)       GlobalTimestampPtr );

/**********************************************************************************************************************
 *  EthTSyn_IsTimestampReadyToProcess
 *********************************************************************************************************************/
/*! \brief      Check if the Timestamp of the passed Timestamp state is ready to be processed.
 *  \details    -
 *  \param[in]  TimestampState:    State of the Timestamp to check
 *  \return     TRUE - Timestamp is ready to be processed
 *  \return     FALSE - Timestamp is not ready to be processed
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \note       If Timestamp is actually available has to be checked separately (EthTSyn_Util_IsTimestampAvailable)
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_IsTimestampReadyToProcess(
  EthTSyn_TimestampStateType TimestampState);

/**********************************************************************************************************************
 *  EthTSyn_PortIdentityIsEqual
 *********************************************************************************************************************/
/*! \brief      Checks if the two passed Port Identities are equal.
 *  \details    -
 *  \param[in]  PortIdentity1     Port Identity 1
 *  \param[in]  PortIdentity2Nbo  Port Identity 2 in Network byte order
 *  \return     TRUE - The Port Identities are equal
 *  \return     FALSE - The Port Identities are not equal
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_PortIdentityIsEqual(
  ETHTSYN_P2CONST(EthTSyn_PortIdentityType) PortIdentity1,
  ETHTSYN_P2CONST(EthTSyn_PortIdentityType) PortIdentity2Nbo);

# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_PortIdentityIsEqualLocalPort
 *********************************************************************************************************************/
/*! \brief      Checks if the passed port identity equals the port identity of the passed EthTSyn port.
 *  \details    -
 *  \param[in]  PortIdx           Index of the EthTSyn port
 *                                [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  PortIdentityNbo   Port Identity in Network byte order
 *  \return     TRUE - The Port Identities are equal
 *  \return     FALSE - The Port Identities are not equal
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_PortIdentityIsEqualLocalPort(
                  EthTSyn_IntPortIdxType    PortIdx,
  ETHTSYN_P2CONST(EthTSyn_PortIdentityType) PortIdentityNbo);
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_IsTxReady
 *********************************************************************************************************************/
/*! \brief      Checks if transmission on the passed Port is possible.
 *  \details    -
 *  \param[in]  PortIdx     Index of the EthTSyn port
 *                          [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE  - Port is ready for transmission
 *  \return     FALSE - Port is not ready for transmission
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_IsTxReady(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
# if !defined(ETHTSYN_UNIT_TEST) /* COV_ETHTSYN_TESTSUITE_INSTRUMENTATION */
/**********************************************************************************************************************
 *  EthTSyn_SetClockIdentity
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SetClockIdentity(
                  EthTSyn_ClockIdentityType      TargetPtr,
  ETHTSYN_P2CONST(EthTSyn_ClockIdentityBaseType) SourcePtr )
{
  /* ----- Implementation ----------------------------------------------- */
  /* PRQA S 0310 2 */ /* MD_EthTSyn_0310_IpBase */
  IpBase_Copy( (ETHTSYN_P2VAR(IpBase_CopyDataType)) TargetPtr,                                                         /* SBSW_ETHTSYN_PASSING_API_POINTER */
    (ETHTSYN_P2CONST(IpBase_CopyDataType)) SourcePtr, sizeof(EthTSyn_ClockIdentityType));
} /* EthTSyn_SetClockIdentity() */

/**********************************************************************************************************************
 *  EthTSyn_ClockIdentityIsEqual
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_ClockIdentityIsEqual(
  ETHTSYN_P2CONST(EthTSyn_ClockIdentityBaseType) Value,
  ETHTSYN_P2CONST(EthTSyn_ClockIdentityBaseType) Reference)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isEqual = TRUE;
  uint8_least clockIdentityIter;

  /* ----- Implementation ----------------------------------------------- */
  for(clockIdentityIter = 0; clockIdentityIter < ETHTSYN_CLOCK_IDENTITY_SIZE; clockIdentityIter++)
  {
    if(Value[clockIdentityIter] != Reference[clockIdentityIter])
    {
      isEqual = FALSE;
      break;
    }
  }
  return isEqual;
} /* EthTSyn_ClockIdentityIsEqual() */

/**********************************************************************************************************************
 *  EthTSyn_NtohTimestamp
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_NtohTimestamp(
    ETHTSYN_P2VAR(EthTSyn_GlobalTimestampType) LocalTimestampPtr,
  ETHTSYN_P2CONST(EthTSyn_TimestampType)       GlobalTimestampPtr )
{
  /* ----- Implementation ----------------------------------------------- */
  IPBASE_GET_UINT16(GlobalTimestampPtr->Seconds, 0u, LocalTimestampPtr->secondsHi);                                    /* SBSW_ETHTSYN_VALID_API_POINTER */

  IPBASE_GET_UINT32(GlobalTimestampPtr->Seconds, 2u, LocalTimestampPtr->seconds);                                      /* SBSW_ETHTSYN_VALID_API_POINTER */

  IPBASE_GET_UINT32(GlobalTimestampPtr->NanoSeconds, 0u, LocalTimestampPtr->nanoseconds);                              /* SBSW_ETHTSYN_VALID_API_POINTER */

} /* EthTSyn_NtohTimestamp() */ /* PRQA S 2006 */ /* MD_MSR_14.7 */

/**********************************************************************************************************************
 *  EthTSyn_IsTimestampReadyToProcess
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_IsTimestampReadyToProcess(
  EthTSyn_TimestampStateType TimestampState)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean timestampReadyToProcess = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  if((TimestampState & ETHTSYN_TIMESTAMP_STATE_REQUIRED_FLAG_VALID_MASK) != 0u)
  {
    if((TimestampState & ETHTSYN_TIMESTAMP_STATE_REQUIRED_MASK) == 0u)
    {
      /* Timestamp not required --> processing possible regardless of the availability */
      timestampReadyToProcess = TRUE;
    }
    else
    {
      /* Timestamp required. Check availability */
      if((TimestampState & ETHTSYN_TIMESTAMP_STATE_AVAILABLE_FLAG_VALID_MASK) != 0u)
      {
        timestampReadyToProcess = TRUE;
      }
    }
  }

  return timestampReadyToProcess;
} /* EthTSyn_IsTimestampReadyToProcess() */

/**********************************************************************************************************************
 *  EthTSyn_PortIdentityIsEqual
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_PortIdentityIsEqual(
  ETHTSYN_P2CONST(EthTSyn_PortIdentityType) PortIdentity1,
  ETHTSYN_P2CONST(EthTSyn_PortIdentityType) PortIdentity2Nbo)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isEqual = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  if(PortIdentity1->PortNumber == (EthTSyn_PortNumberType)EthTSyn_Ntohs(PortIdentity2Nbo->PortNumber))
  {
    isEqual = EthTSyn_ClockIdentityIsEqual(PortIdentity1->ClockIdentity, PortIdentity2Nbo->ClockIdentity);             /* SBSW_ETHTSYN_STRUCT_ELEMENT_ARRAY_AS_POINTER */
  }

  return isEqual;
} /* EthTSyn_PortIdentityIsEqual() */

#  if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_PortIdentityIsEqualLocalPort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_PortIdentityIsEqualLocalPort(
                  EthTSyn_IntPortIdxType    PortIdx,
  ETHTSYN_P2CONST(EthTSyn_PortIdentityType) PortIdentityNbo)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isEqual = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  if(EthTSyn_GetNumberOfPort(PortIdx) == (uint16)EthTSyn_Ntohs(PortIdentityNbo->PortNumber))
  {
      isEqual = EthTSyn_ClockIdentityIsEqual(                                                                          /* SBSW_ETHTSYN_STRUCT_ELEMENT_ARRAY_AS_POINTER */
          (EthTSyn_GetAddrCtrlState(EthTSyn_GetCtrlIdxOfPort(PortIdx)))->ClockIdentity,
          PortIdentityNbo->ClockIdentity);
  }

  return isEqual;
} /* EthTSyn_PortIdentityIsEqualLocalPort() */
#  endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_IsTxReady
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_IsTxReady(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean txReady = FALSE;
  const EthTSyn_CtrlIdxOfPortType ethTSynCtrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);
  ETHTSYN_P2CONST(EthTSyn_CtrlStateType) ctrlStatePtr = EthTSyn_GetAddrCtrlState(ethTSynCtrlIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* Check EthTSyn Ctrl State */
  if((ctrlStatePtr->TransmissionMode == ETHTSYN_TX_ON) &&
    (ctrlStatePtr->TrcvLinkState == ETHTRCV_LINK_STATE_ACTIVE))
  {
    txReady = TRUE;
  }

  return txReady;
} /* EthTSyn_IsTxReady() */

# endif /* ETHTSYN_UNIT_TEST */


# define ETHTSYN_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#endif /* ETHTSYN_INT_H */
/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Int.h
 *********************************************************************************************************************/
