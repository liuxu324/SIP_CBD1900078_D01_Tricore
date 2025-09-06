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
 *         \file  EthTSyn_Types.h
 *        \brief  EthTSyn Types header
 *
 *      \details  Contains all type definitions
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


#if !defined(ETHTSYN_TYPES_H)
# define ETHTSYN_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "EthTSyn_GeneratedSimpleTypes.h"
# include "EthIf.h"
# include "EthTSyn_Cfg.h"
# include "StbM_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 8 */ /* MD_MSR_19.7 */
# define ETHTSYN_P2CONSTCFGROOT(Type)  P2CONST(Type, AUTOMATIC, ETHTSYN_CONST)
# define ETHTSYN_P2CONSTCFG(Type)      P2CONST(Type, AUTOMATIC, ETHTSYN_CONST)
# define ETHTSYN_CONSTP2CONSTCFG(Type) CONSTP2CONST(Type, AUTOMATIC, ETHTSYN_CONST)
# define ETHTSYN_P2CONST(Type)         P2CONST(Type, AUTOMATIC, ETHTSYN_APPL_DATA)
# define ETHTSYN_CONSTP2CONST(Type)    CONSTP2CONST(Type, AUTOMATIC, ETHTSYN_CONST)
# define ETHTSYN_P2VAR(Type)           P2VAR(Type, AUTOMATIC, ETHTSYN_APPL_VAR)
# define ETHTSYN_CONSTP2VAR(Type)      CONSTP2VAR(Type, AUTOMATIC, ETHTSYN_CONST)
# define ETHTSYN_P2FUNC(RType, Type)   P2FUNC(RType, ETHTSYN_CODE, Type)

/* Type sizes */
# define ETHTSYN_PHYS_ADDR_LEN                             (6u)
# define ETHTSYN_CLOCK_IDENTITY_SIZE                       (8u)
# define ETHTSYN_CORRECTION_FIELD_SIZE                     (8u)

/* Ar Tlv values */
# define ETHTSYN_AR_TLV_ORGANIZATION_ID                    (0x1A75FBu)
# define ETHTSYN_AR_TLV_ORGANIZATION_SUB_TYPE              (0x605676u)

# define ETHTSYN_AR_TLV_TYPE                               (0x0003u)
# define ETHTSYN_AR_SUB_TLV_TYPE_TIME_SECURED              (0x28u)
# define ETHTSYN_AR_SUB_TLV_TYPE_STATUS_SECURED            (0x50u)
# define ETHTSYN_AR_SUB_TLV_TYPE_STATUS_NOT_SECURED        (0x51u)
# define ETHTSYN_AR_SUB_TLV_TYPE_USER_DATA_SECURED         (0x60u)
# define ETHTSYN_AR_SUB_TLV_TYPE_USER_DATA_NOT_SECURED     (0x61u)
# define ETHTSYN_AR_SUB_TLV_TYPE_OFS_SECURED               (0x44u)
# define ETHTSYN_AR_SUB_TLV_TYPE_OFS_NOT_SECURED           (0x34u)

# define ETHTSYN_AR_TLV_HEADER_TYPE_LENGTH_FIELDS_LENGTH   (4u) /* Length in byte of tlvType and lengthField */
# define ETHTSYN_AR_TLV_HEADER_LENGTH_FIELD_VALUE          (6u) /* Does not include the Sub-Tlvs length */
# define ETHTSYN_AR_SUB_TLV_TIME_LENGTH_FIELD_VALUE        (3u)
# define ETHTSYN_AR_SUB_TLV_STATUS_LENGTH_FIELD_VALUE      (2u)
# define ETHTSYN_AR_SUB_TLV_USER_DATA_LENGTH_FIELD_VALUE   (5u)
# define ETHTSYN_AR_SUB_TLV_OFS_LENGTH_FIELD_VALUE         (17u)

/* The actual AR Tlv header length is the value of its length field (6) + the type (2) and length field itself (2) */
# define ETHTSYN_AR_TLV_HEADER_LENGTH                      (10u)
/* The actual length of an Ar SubTlv is the value of its length field + the type (1) and the length field itself (1) */
# define ETHTSYN_AR_SUB_TLV_ABSTRACT_HDR_LENGTH            (2u)
# define ETHTSYN_AR_SUB_TLV_TIME_LENGTH                    (5u)
# define ETHTSYN_AR_SUB_TLV_STATUS_LENGTH                  (4u)
# define ETHTSYN_AR_SUB_TLV_USER_DATA_LENGTH               (7u)
# define ETHTSYN_AR_SUB_TLV_OFS_LENGTH                     (19u)

/* EthTSyn Follow_Up AR Sub TLV Status Secured/Not Secured */
# define ETHTSYN_AR_SUB_TLV_STATUS_SGW_MASK                (0x01u)
# define ETHTSYN_AR_SUB_TLV_STATUS_SGW_POS                 (0u)

# define ETHTSYN_AR_SUB_TLV_STATUS_SGW_SYNC_TO_GTM         (0x00u)
# define ETHTSYN_AR_SUB_TLV_STATUS_SGW_SYNC_TO_SUB_DOMAIN  (0x01u)

/* Invalid values */
# define ETHTSYN_INVALID_SWITCH_PORT_IDX                   (0xFFU)
# define ETHTSYN_INVALID_ETHIF_SWITCH_IDX                  (0xFFU)
# define ETHTSYN_SWT_MGMT_MSG_BUFFER_INVALID_IDX           (0xFFU)

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * COM_STACK_LIB_RELATED (INDEX_TYPES)
 *
 * Note: These internal index types are based on the SizeOf-Types provided by ComStackLib and are big enough
 *       to store the highest possible index. Therefore there is now risk when casting the Iteration-Type (which might
 *       be a bigger base type) to the corresponding internal index type.
 *********************************************************************************************************************/
typedef EthTSyn_SizeOfCtrlType             EthTSyn_IntCtrlIdxType;
typedef EthTSyn_SizeOfTimeDomainType       EthTSyn_IntTimeDomainIdxType;
typedef EthTSyn_SizeOfOffsetTimeDomainType EthTSyn_IntOfsTimeDomainIdxType;
typedef EthTSyn_SizeOfPortType             EthTSyn_IntPortIdxType;
typedef EthTSyn_SizeOfMasterPortType       EthTSyn_IntMasterPortIdxType;
typedef EthTSyn_SizeOfSlavePortType        EthTSyn_IntSlavePortIdxType;
typedef EthTSyn_SizeOfPdelayConfigType     EthTSyn_IntPdelayIdxType;
typedef EthTSyn_SizeOfPdelayInitiatorType  EthTSyn_IntPdelayInitiatorIdxType;
typedef EthTSyn_SizeOfPdelayResponderType  EthTSyn_IntPdelayResponderIdxType;

typedef uint16                      EthTSyn_PortNumberType;
typedef uint8                       EthTSyn_DomainNumberType;
typedef StbM_SynchronizedTimeBaseType  EthTSyn_SynchronizedTimeBaseType;
typedef uint8                       EthTSyn_BufferIdxType;
typedef uint8                       EthTSyn_ClockIdentityBaseType;
typedef EthTSyn_ClockIdentityBaseType  EthTSyn_ClockIdentityType[ETHTSYN_CLOCK_IDENTITY_SIZE];
typedef uint8                       EthTSyn_CorrectionFieldType[ETHTSYN_CORRECTION_FIELD_SIZE];
typedef sint8                       EthTSyn_LogMessageIntervalType;
typedef sint64                      EthTSyn_TimediffType;
typedef uint64                      EthTSyn_UTimediffType;
typedef uint8                       EthTSyn_TimestampQualityType;
typedef StbM_TimeStampRawType       EthTSyn_TimestampRawType;
typedef uint32                      EthTSyn_PdelayType;

# if ( (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) || (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) )
typedef Eth_TimeStampType           EthTSyn_GlobalTimestampType;
typedef EthTSyn_GlobalTimestampType EthTSyn_IngressTimestampType;
# else
typedef EthTSyn_TimestampRawType    EthTSyn_IngressTimestampType;
/*! Timestamp struct definition */
typedef struct EthTSyn_GlobalTimestampTypeStruct
{
  uint32 seconds;
  uint16 secondsHi;
  uint32 nanoseconds;
} EthTSyn_GlobalTimestampType;
# endif /* ( (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) || (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) ) */

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
typedef Eth_FrameIdType EthTSyn_FrameIdType;
#  define ETHTSYN_INVALID_FRAME_ID ETH_INVALID_FRAME_ID
# else
typedef uint16 EthTSyn_FrameIdType;
#  define ETHTSYN_INVALID_FRAME_ID 0
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

typedef Eth_TimeIntDiffType EthTSyn_TimeIntDiffType;

typedef P2VAR(uint8, TYPEDEF, ETHTSYN_APPL_VAR)  EthTSyn_PhyAddrPtrType;

/*! Egress timestamp handle struct definition */
typedef struct EthTSyn_EgressTimestampHandleTypeStruct
{
  EthTSyn_GlobalTimestampType  EgressTimestamp;  /*<! HW-Timestamping only: The actual egress timestamp */
  EthTSyn_GlobalTimestampType  GlobalTimestamp;  /*<! Sync msg only: The current time (StbM) at Tx */
  EthTSyn_GlobalTimestampType  SyncRefTimestamp; /*<! Sync msg and HW-Timestamping only: The Time (EthIf) at Tx */
  EthTSyn_TimestampRawType     RawTimestamp;     /*<! SW-Timestamping only: The actual egress timestamp */
} EthTSyn_EgressTimestampHandleType;

/* EthTSyn State Definitions */
typedef enum EthTSyn_StateEnum
{
  ETHTSYN_STATE_UNINIT = 0u,
  ETHTSYN_STATE_INIT
} EthTSyn_StateEnumType;

/* EthTSyn Sync State Definition */
typedef enum EthTSyn_SyncStateEnum
{
  ETHTSYN_SYNC = 0u,
  ETHTSYN_UNSYNC = 1u,
  ETHTSYN_UNCERTAIN = 2u,
  ETHTSYN_NEVERSYNC = 3u
} EthTSyn_SyncStateType;

/* EthTSyn Transmission Mode Definition */
typedef uint8 EthTSyn_TransmissionModeType;
# define ETHTSYN_TX_OFF  (0x00u)
# define ETHTSYN_TX_ON   (0x01u)

/* EthTSyn Timestamp State Definitions */
typedef uint8 EthTSyn_TimestampStateType;
# define ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_INVALID                         (0x00U)
# define ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_NOT_REQUIRED                    (0x02U)
# define ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_NOT_REQUIRED_NOT_AVAILABLE      (0x0AU)
# define ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_NOT_REQUIRED_AVAILABLE          (0x0EU)
# define ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_WAITING_FOR_TIMESTAMP  (0x03U)
# define ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_NOT_AVAILABLE          (0x0BU)
# define ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_AVAILABLE              (0x0FU)
/* EthTSyn Timestamp State Masks */
/*
 * +-------------------------------+
 * |R|R|R|R|Avail_V|Avail|Req_V|Req|
 * +-------------------------------+
 */
# define ETHTSYN_TIMESTAMP_STATE_REQUIRED_MASK                             (0x01U)
# define ETHTSYN_TIMESTAMP_STATE_REQUIRED_FLAG_VALID_MASK                  (0x02U)
# define ETHTSYN_TIMESTAMP_STATE_AVAILABLE_MASK                            (0x04U)
# define ETHTSYN_TIMESTAMP_STATE_AVAILABLE_FLAG_VALID_MASK                 (0x08U)

/* EthTSyn port type type */
typedef uint8 EthTSyn_PortTypeType;
/* Bit-Masks */
/*
 * +--------------------------------+
 * |R|R|R|R|R|Host|Switch|EndStation|
 * | | | | | |Port| Port |   Port   |
 * +--------------------------------+
 */
# define ETHTSYN_PORT_TYPE_INVALID                         (0x00U)
# define ETHTSYN_PORT_TYPE_END_STATION_PORT                (0x01U)
# define ETHTSYN_PORT_TYPE_SWITCH_PORT                     (0x02U)
# define ETHTSYN_PORT_TYPE_SWITCH_AND_END_STATION_PORT     (0x03U)
# define ETHTSYN_PORT_TYPE_SWITCH_HOST_PORT                (0x04U)

/*! EthTSyn Timestamp Format struct definition */
typedef struct EthTSyn_TimestampTypeStruct
{
  uint8 Seconds[6];
  uint8 NanoSeconds[4];
} EthTSyn_TimestampType;

/*! Internal timestamp struct definition (used for arithmetic) */
typedef struct EthTSyn_InternalTimestampTypeStruct
{
  uint64 seconds;
  uint32 nanoseconds;
} EthTSyn_InternalTimestampType;

/*! EthTSyn Timestamp management struct definition */
typedef struct EthTSyn_TimeStampMgmtStruct
{
  EthTSyn_TimestampStateType         State;
  EthTSyn_GlobalTimestampType        Timestamp;
}EthTSyn_TimestampMgmtStructType;

/*! Port identity struct definition */
typedef struct EthTSyn_PortIdentityTypeStruct
{
  EthTSyn_ClockIdentityType ClockIdentity;
  EthTSyn_PortNumberType    PortNumber;
} EthTSyn_PortIdentityType;

/*! EthTSyn Clock Quality format struct definition */
typedef struct EthTSyn_ClockQualityTypeStruct
{
  uint8        ClockClass;
  uint8        ClockAccuracy;
  uint16       OffsetScaledLogVariance;
} EthTSyn_ClockQualityType;

/*! EthTSyn Common Message Header format struct definition */
typedef struct EthTSyn_CommonMsgHdrTypeStruct
{
  uint8                       TransSpecific_MessageType;
  uint8                       Reserved_VersionGPtp;
  uint16                      MessageLength; /*!< Total message length including Header and Payload */ /* 4 byte aligned */
  EthTSyn_DomainNumberType    DomainNumber;
  uint8                       Reserved_0;
  uint8                       Flags[2]; /* 4 byte aligned */
  EthTSyn_CorrectionFieldType CorrectionField;
  uint8                       Reserved_1[4]; /* 4 byte aligned */
  EthTSyn_ClockIdentityType   SourceClockIdentity;
  EthTSyn_PortNumberType      SourcePortNumber;
  uint16                      SequenceId;
  uint8                       Control;
  EthTSyn_LogMessageIntervalType LogMessageInterval;
} EthTSyn_CommonMsgHdrType;


/*! EthTSyn Announce Message Format struct definition */
typedef struct EthTSyn_AnnounceMsgTypeStruct
{
  uint8                     Reserved_0[10];
  sint16                    CurrentUtcOffset;
  uint8                     Reserved_1;
  /* Begin systemIdentity for BMCA evaluation */
  uint8                     GrandmasterPriority_1;
  EthTSyn_ClockQualityType  GrandmasterClockQuality;
  uint8                     GrandmasterPriority_2;
  EthTSyn_ClockIdentityType GrandmasterIdentity;
  /* End systemIdentity for BMCA evaluation */
  /* no uint16 datatype of StepsRemoved possible due to padding / alignment issue */
  uint8                     StepsRemoved[2];
  uint8                     TimeSource;
  uint16                    TlvType;
  uint16                    LengthField;
  EthTSyn_ClockIdentityType ClockIdentity;
} EthTSyn_AnnounceMsgType;

/*! EthTSyn Signaling Message Format struct definition */
typedef struct EthTSyn_SignalingMsgTypeStruct
{
  EthTSyn_PortIdentityType TargetPortIdentity;
  uint16                   TlvType;
  uint16                   LengthField;
  uint8                    OrganisationId[3];
  uint8                    OrganisationSubType[3];
  sint8                    LinkDelayInt;
  sint8                    TimeSyncInt;
  sint8                    AnnounceInt;
  uint8                    Flags;
  uint16                   Reserved;
} EthTSyn_SignalingMsgType;

/*! EthTSyn Sync Message Format struct definition */
typedef struct EthTSyn_SyncMsgTypeStruct
{
  uint8 Reserved[10];
} EthTSyn_SyncMsgType;

/*! EthTSyn Follow Up Message Format struct definition */
typedef struct EthTSyn_FollowUpMsgTypeStruct
{
  uint8        PreciseOriginTimestampSeconds[6];
  uint8        PreciseOriginTimestampNanoSeconds[4];
  uint16       TlvType;
  uint16       LengthField;
  uint8        OrganisationId[3];
  uint8        OrganisationSubType[3];
  uint32       CumulativeScaledRateOffset;
  uint16       GmTimeBaseIndicator;
  uint8        lastGmPhaseChange[12];
  uint8        ScaledLastGmFreqChange[4];
} EthTSyn_FollowUpMsgType;




/*! EthTSyn Follow_Up AR TLV Header struct definition */
typedef struct EthTSyn_ArTlvHeaderTypeStruct
{
  uint8  TlvType[2];
  uint8  LengthField[2];
  uint8  OrganisationId[3];
  uint8  OrganisationSubType[3];
} EthTSyn_ArTlvHeaderType;

/*! EthTSyn Follow_Up AR Sub TLV abstract header struct definition.
 *  It is intended to cast to the corresponding AR Sub Tlv type */
typedef struct EthTSyn_ArSubTlvAbstractHeaderTypeStruct
{
  uint8   Type;
  uint8   Length;
} EthTSyn_ArSubTlvAbstractHeaderType;

/*! EthTSyn Follow_Up AR Sub TLV Time Secured struct definition */
typedef struct EthTSyn_ArSubTlvTimeSecuredTypeStruct
{
  uint8   Type;
  uint8   Length;
  uint8   CrcTimeFlags;
  uint8   CrcTime0;
  uint8   CrcTime1;
} EthTSyn_ArSubTlvTimeSecuredType;

/*! EthTSyn Follow_Up AR Sub TLV Status Secured/Not Secured struct definition */
typedef struct EthTSyn_ArSubTlvStatusTypeStruct
{
  uint8   Type;
  uint8   Length;
  uint8   Status;
  uint8   CrcStatus; /*!< Only applicable for StatusSecured, Reserved otherwise */
} EthTSyn_ArSubTlvStatusType;


/*! EthTSyn Follow_Up AR Sub TLV UserData Secured/Not Secured struct definition */
typedef struct EthTSyn_ArSubTlvUserDataTypeStruct
{
  uint8   Type;
  uint8   Length;
  uint8   UserDataLength;
  uint8   UserByte0;
  uint8   UserByte1;
  uint8   UserByte2;
  uint8   CrcUserData; /*!< Only applicable for UserDataSecured, Reserved otherwise */
} EthTSyn_ArSubTlvUserDataType;


/*! EthTSyn Follow_Up AR Sub TLV OFS Secured/Not Secured struct definition */
typedef struct EthTSyn_ArSubTlvOfsTypeStruct
{
  uint8   Type;
  uint8   Length;
  uint8   OfsTimeDomain;
  uint8   OfsTimeSec[6];
  uint8   OfsTimeNSec[4];
  uint8   Status;
  uint8   UserDataLength;
  uint8   UserByte0;
  uint8   UserByte1;
  uint8   UserByte2;
  uint8   CrcOfs; /*!< Only applicable for OfsSecured, Reserved otherwise */
} EthTSyn_ArSubTlvOfsType;


/*! EthTSyn Pdelay Request Message Format struct definition */
typedef struct EthTSyn_PDelayReqMsgTypeStruct
{
  uint8 Reserved_0[10];
  uint8 Reserved_1[10];
} EthTSyn_PDelayReqMsgType;

/*! EthTSyn Pdelay Response Message Format struct definition */
typedef struct EthTSyn_PdelayRespMsgTypeStruct
{
  uint8                     RequestReceiptTimestampSeconds[6];
  uint8                     RequestReceiptTimestampNanoSeconds[4];
  EthTSyn_ClockIdentityType RequestingClockIdentity;
  EthTSyn_PortNumberType    RequestingPortNumber;
} EthTSyn_PdelayRespMsgType;

/*! EthTSyn Pdelay Response Follow Up Message Format struct definition */
typedef struct EthTSyn_PDelayResFollowUpMsgTypeStruct
{
  uint8                     ResponseOriginTimestampSeconds[6];
  uint8                     ResponseOriginTimestampNanoSeconds[4];
  EthTSyn_ClockIdentityType RequestingClockIdentity;
  EthTSyn_PortNumberType    RequestingPortNumber;
} EthTSyn_PDelayResFollowUpMsgType;

/* Tx Call-backs */
typedef ETHTSYN_P2FUNC(void, EthTSyn_SyncSentCbkPtrType)     (EthTSyn_IntPortIdxType,
                                                        ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType),
                                                        ETHTSYN_P2CONST(EthTSyn_SyncMsgType) );

typedef ETHTSYN_P2FUNC(void, EthTSyn_FollowUpSentCbkPtrType) (EthTSyn_IntPortIdxType,
                                                        ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType),
                                                        ETHTSYN_P2CONST(EthTSyn_FollowUpMsgType) );

/*! EthTSyn Pdelay Request state-machine struct definition */
typedef struct EthTSyn_PdelayReqSmReqTypeStruct
{
  /*!< For SW-Timestamping, only 'raw' timestamps are used.
   * The raw timestamp will be stored in the 'nanoseconds' field of the global timestamp */
  EthTSyn_TimestampMgmtStructType EgressTimestampMgmt;
  uint32                          TxIntervalCnt; /*!< Decremented in each Mf. Tx Pdelay Request when counter reaches '0' */
  uint16                          SequenceId;
} EthTSyn_PdelayReqSmReqType;

/*! EthTSyn Pdelay Response Request state-machine struct definition */
typedef struct EthTSyn_PdelayRespSmReqTypeStruct
{
  /*!< For SW-Timestamping, only 'raw' timestamps are used.
   * The raw timestamp will be stored in the 'nanoseconds' field of the global timestamp */
  EthTSyn_TimestampMgmtStructType IngressTimestampMgmt;
  EthTSyn_PortIdentityType        SourcePortIdentity; /*!< Source Port Identity of the requesting port */
  uint16                          SequenceId;
} EthTSyn_PdelayRespSmReqType;

/*! EthTSyn Pdelay Response state-machine struct definition */
typedef struct EthTSyn_PdelayRespSmRespTypeStruct
{
  /*!< For SW-Timestamping, only 'raw' timestamps are used.
   * The raw timestamp will be stored in the 'nanoseconds' field of the global timestamp */
  EthTSyn_TimestampMgmtStructType EgressTimestampMgmt;
  uint16                          SequenceId;
} EthTSyn_PdelayRespSmRespType;

/*! EthTSyn Pdelay Request Response state-machine struct definition */
typedef struct EthTSyn_PdelayReqSmRespTypeStruct
{
  EthTSyn_TimestampMgmtStructType IngressTimestampMgmt;
  EthTSyn_GlobalTimestampType     RequestReceiptTimestamp;
  EthTSyn_PortIdentityType        SourcePortIdentity; /*!< Source Port Identity of the responding port  */
# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF)
  EthTSyn_TimestampRawType        IngressTimestampRaw;
# endif
  uint16                          SequenceId;
} EthTSyn_PdelayReqSmRespType;

/*! EthTSyn Pdelay Request FollowUp state-machine struct definition */
typedef struct EthTSyn_PdelayReqSmRespFollowUpTypeStruct
{
  EthTSyn_TimestampMgmtStructType ResponseOriginTimestampMgmt;
} EthTSyn_PdelayReqSmRespFollowUpType;

/*! EthTSyn Ethernet Tx buffer identification struct definition */
typedef struct EthTSyn_EthTxBufferIdentTypeStruct
{
  ETHTSYN_P2CONST(uint8)   Address; /*!< Pointer to the Payload of the Ethernet Tx Buffer */
  EthTSyn_BufferIdxType    Index; /*!< Index of the Ethernet Tx Buffer */
} EthTSyn_EthTxBufferIdentType;

typedef enum EthTSyn_PdelayReqSmStateEnum
{
  ETHTSYN_S_PD_REQ_SM_DISABLED = 0u,  /* ETHTSYN_STATE_P_DELAY_REQ_NOT_ENABLED */
  ETHTSYN_S_PD_REQ_SM_TX_REQ,         /* ETHTSYN_STATE_P_DELAY_REQ_SEND_P_DELAY_REQ, ETHTSYN_STATE_P_DELAY_REQ_INITIAL_SEND_P_DELAY_REQ */
  ETHTSYN_S_PD_REQ_SM_WAIT_RESP,      /* ETHTSYN_STATE_P_DELAY_REQ_WAITING_FOR_P_DELAY_RESP */
  ETHTSYN_S_PD_REQ_SM_WAIT_RESP_TS,   /* ETHTSYN_STATE_P_DELAY_REQ_WAITING_FOR_P_DELAY_RESP_INGRESS_TIMESTAMP */
  ETHTSYN_S_PD_REQ_SM_WAIT_RESP_FUP,  /* ETHTSYN_STATE_P_DELAY_REQ_WAITING_FOR_P_DELAY_RESP_FOLLOW_UP */
  ETHTSYN_S_PD_REQ_SM_COMPUTE_PDELAY, /* ETHTSYN_STATE_P_DELAY_REQ_RECEIVED_PDELAY_RESP_AND_PDELAY_RESP_FOLLOW_UP */
  ETHTSYN_S_PD_REQ_SM_WAIT_TX_COUNTER /* ETHTSYN_STATE_P_DELAY_REQ_WAITING_FOR_PDELAY_INTERVAL_COUNTER */
} EthTSyn_PdelayReqSmStateEnumType;

/*! EthTSyn Pdelay Request state-machine struct definition */
typedef struct EthTSyn_PdelayReqSmTypeStruct
{
  EthTSyn_PdelayReqSmRespType         PdelayResp;
  EthTSyn_PdelayReqSmReqType          PdelayReq;
  EthTSyn_PdelayReqSmRespFollowUpType PdelayRespFollowUp;
  EthTSyn_EthTxBufferIdentType        TxBuf;
  uint32                              PdelayRespRespFollowUpTimeout;
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
  EthTSyn_FrameIdType                 FrameId;
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
  uint16                              LostResponses;
  sint8                               TxConfirmationPending;
  /*!< Tx == +1, TxConf == -1 --> == 0: Transmit + TxConfirmation occurred */
  EthTSyn_PdelayReqSmStateEnumType    State;
} EthTSyn_PdelayReqSmType;

typedef enum EthTSyn_PdelayRespSmStateEnum
{
  ETHTSYN_S_PD_RESP_SM_DISABLED = 0u, /* ETHTSYN_STATE_P_DELAY_RESP_NOT_ENABLED */
  ETHTSYN_S_PD_RESP_SM_WAIT_REQ,      /* ETHTSYN_STATE_P_DELAY_RESP_INITAIL_WAITING_FOR_PDELAY_REQ, ETHTSYN_STATE_P_DELAY_RESP_WAITING_FOR_PDELAY_REQ */
  ETHTSYN_S_PD_RESP_SM_WAIT_REQ_TS,   /* ETHTSYN_STATE_P_DELAY_RESP_WAITING_FOR_PDELAY_REQ_INGRESS_TIMESTAMP */
  ETHTSYN_S_PD_RESP_SM_TX_RESP,       /* ETHTSYN_STATE_P_DELAY_RESP_SEND_P_DELAY_RESP */
  ETHTSYN_S_PD_RESP_SM_WAIT_RESP_TS,  /* ETHTSYN_STATE_P_DELAY_RESP_WAITING_FOR_PDELAY_RESP_EGRESS_TIMESTAMP */
  ETHTSYN_S_PD_RESP_SM_TX_RESP_FUP    /* ETHTSYN_STATE_P_DELAY_RESP_SEND_P_DELAY_RESP_FOLLOW_UP */

} EthTSyn_PdelayRespSmStateEnumType;

/*! EthTSyn Pdelay Response state-machine struct definition */
typedef struct EthTSyn_PdelayRespSmTypeStruct
{
  EthTSyn_PdelayRespSmRespType      PdelayResp;
  EthTSyn_PdelayRespSmReqType       PdelayReq;
  EthTSyn_EthTxBufferIdentType      TxBuf;
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
  EthTSyn_FrameIdType               FrameId;
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
  boolean                           InProgress;
  sint8                             TxConfirmationPending;
  /*!< Tx == +1, TxConf == -1 --> == 0: Transmit + TxConfirmation occurred */
  EthTSyn_PdelayRespSmStateEnumType State;
} EthTSyn_PdelayRespSmType;

/*! EthTSyn Master identity struct definition */
typedef struct EthTSyn_MasterIdentityTypeStruct
{
  EthTSyn_PortIdentityType  MasterPortIdentity; /*!< The Port Identity of the valid time master */
  boolean                   IsValid;            /*!< Indicating if the MasterPortIdentity information is valid */
} EthTSyn_MasterIdentityType;

/*! EthTSyn Sync Receive state-machine Sync message struct definition */
typedef struct EthTSyn_SyncReceiveSmSyncTypeStruct
{
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
  EthTSyn_TimestampMgmtStructType  EgressTimestampMgmtHostPort;
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */
  EthTSyn_TimestampMgmtStructType  IngressTimestampMgmt;
  EthTSyn_PortIdentityType         SourcePortIdentity;
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
  uint32                           SyncRxTimeoutCnt;
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
  uint16                           SequenceId;
  /*!< For SW-Timestamping, only 'raw' timestamps are used.
   * The raw timestamp will be stored in the 'nanoseconds' field of the global timestamp */
  EthTSyn_LogMessageIntervalType   LogMessageInterval;
} EthTSyn_SyncReceiveSmSyncType;

/*! EthTSyn Sync Receive state-machine FollowUp message struct definition */
typedef struct EthTSyn_SyncReceiveSmFollowUpTypeStruct
{
  uint32                      FollowUpRxTimeoutCnt;
  uint16                      SequenceId;
} EthTSyn_SyncReceiveSmFollowUpType;

typedef enum EthTSyn_SyncReceiveSmStateEnum
{
  ETHTSYN_S_SYNC_RCV_SM_DISCARD = 0u, /* ETHTSYN_STATE_SYNC_RECEIVE_DISCARD */
  ETHTSYN_S_SYNC_RCV_SM_WAIT_SYNC,    /* ETHTSYN_STATE_SYNC_RECEIVE_WAITING_FOR_SYNC */
  ETHTSYN_S_SYNC_RCV_SM_WAIT_SYNC_TS, /* ETHTSYN_STATE_SYNC_RECEIVE_WAITING_FOR_SYNC_INGRESS_TIMESTAMP */
  ETHTSYN_S_SYNC_RCV_SM_WAIT_FUP,     /* ETHTSYN_STATE_SYNC_RECEIVE_WAITING_FOR_FOLLOW_UP */
  ETHTSYN_S_SYNC_RCV_SM_SYNC_TIMEOUT  /* ETHTSYN_STATE_SYNC_RECEIVE_SYNC_TIMEOUT */
} EthTSyn_SyncReceiveSmStateEnumType;

/*! EthTSyn Sync Receive state-machine struct definition */
typedef struct EthTSyn_SyncReceiveSmTypeStruct
{
  EthTSyn_SyncReceiveSmSyncType      Sync;
  EthTSyn_SyncReceiveSmFollowUpType  FollowUp;
  EthTSyn_SyncReceiveSmStateEnumType State;
} EthTSyn_SyncReceiveSmType;

/*! EthTSyn Announce Received state-machine struct definition */
typedef struct EthTSyn_AnnounceReceiveSmTypeStruct
{
  uint32 RxTimeoutCnt;
} EthTSyn_AnnounceReceiveSmType;

typedef enum EthTSyn_SyncSendSmStateEnum
{
  ETHTSYN_S_SYNC_SEND_SM_DISABLED = 0u,     /* ETHTSYN_STATE_SYNC_SEND_DISABLED */
  ETHTSYN_S_SYNC_SEND_SM_INITIALIZING,      /* ETHTSYN_STATE_SYNC_SEND_INITIALIZING */
  ETHTSYN_S_SYNC_SEND_SM_WAIT_TX_COUNTER,   /* ETHTSYN_STATE_SYNC_SEND_WAITING_FOR_SYNC_SEND */
  ETHTSYN_S_SYNC_SEND_SM_TX_SYNC,           /* ETHTSYN_STATE_SYNC_SEND_SEND_SYNC */
  ETHTSYN_S_SYNC_SEND_SM_TX_IMMEDIATE_SYNC, /* ETHTSYN_STATE_SYNC_SEND_SEND_IMMEDIATE_SYNC */
  ETHTSYN_S_SYNC_SEND_SM_TX_FUP,            /* ETHTSYN_STATE_SYNC_SEND_SEND_FOLLOW_UP */
  ETHTSYN_S_SYNC_SEND_SM_TX_ANNOUNCE,       /* ETHTSYN_STATE_SYNC_SEND_SEND_ANNOUNCE */
  ETHTSYN_S_SYNC_SEND_SM_SSS_PENDING,       /* ETHTSYN_STATE_SYNC_SEND_SITE_SYNC_SYNC_PENDING */
  ETHTSYN_S_SYNC_SEND_SM_SSS_TX_SYNC,       /* ETHTSYN_STATE_SYNC_SEND_SITE_SYNC_SYNC_SEND_SYNC */
  ETHTSYN_S_SYNC_SEND_SM_SSS_WAIT_FUP,      /* ETHTSYN_STATE_SYNC_SEND_SITE_SYNC_SYNC_WAIT_FOLLOW_UP */
  ETHTSYN_S_SYNC_SEND_SM_SSS_TX_FUP         /* ETHTSYN_STATE_SYNC_SEND_SITE_SYNC_SYNC_SEND_FOLLOW_UP */
} EthTSyn_SyncSendSmStateEnumType;

/*! EthTSyn Sync Send state-machine struct definition */
typedef struct EthTSyn_SyncSendSmTypeStruct
{
  EthTSyn_TimestampMgmtStructType FollowUpPreciseOriginTimestampMgmt; /*!< Sync Egress Timestamp */
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
  EthTSyn_TimestampMgmtStructType SyncIngressTimestampMgmtHostPort;
  EthTSyn_TimestampMgmtStructType SyncEgressTimestampMgmtSwitchPort;
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */
  EthTSyn_EthTxBufferIdentType    SyncTxBuf;
  EthTSyn_EthTxBufferIdentType    FollowUpTxBuf;
  uint32                          TxIntervalCnt; /*!< Decrement with each Mf. Tx Sync message when '0' is reached */
  uint16                          SequenceId;
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
  EthTSyn_FrameIdType             FrameId;
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
  EthTSyn_LogMessageIntervalType  LogMessageInterval;
  /*!< Tx == +1, TxConf == -1 --> == 0: Transmit + TxConfirmation occurred */
  sint8                           TxConfirmationPending;
  EthTSyn_SyncSendSmStateEnumType State;
} EthTSyn_SyncSendSmType;

/*! EthTSyn Ctrl State struct definition */
typedef struct EthTSyn_CtrlStateTypeStruct
{
  EthTSyn_TransmissionModeType TransmissionMode; /*!< Current TxMode of the EthTSyn controller */
  EthTrcv_LinkStateType        TrcvLinkState;    /*!< Current link state of the EthTSyn controller */
  EthTSyn_ClockIdentityType    ClockIdentity;    /*!< Clock identity of the EthTSyn controller */
} EthTSyn_CtrlStateType;

/*! EthTSyn Grand Master Priority struct definition */
typedef struct EthTSyn_GmPriorityTypeStruct
{
  EthTSyn_PortIdentityType PortIdentity; /*!< Port Identity of the Grand Master */
} EthTSyn_GmPriorityType;

/*! EthTSyn System State struct definition */
typedef struct EthTSyn_SystemTypeStruct
{
  EthTSyn_GmPriorityType GmPriority; /*!< The Priority of the valid Grand Master */
  boolean GmPresent;
} EthTSyn_SystemType;


/***********************************************************************************************************************
 * ETHTSYN SWITCH MANAGEMENT TYPES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef uint8 EthTSyn_SwtMgmt_MsgBufferIdxType;

typedef enum EthTSyn_SmIdentEnum
{
  ETHTSYN_SM_IDENT_INVALID = 0u,    /* ETHTSYN_STATE_MACHINE_IDENTIFICATION_INVLID_SM */
  ETHTSYN_SM_IDENT_PDELAY_REQ,      /* ETHTSYN_STATE_MACHINE_IDENTIFICATION_P_DELAY_REQ_SM */
  ETHTSYN_SM_IDENT_PDELAY_RESP,     /* ETHTSYN_STATE_MACHINE_IDENTIFICATION_P_DELAY_RESP_SM */
  ETHTSYN_SM_IDENT_SYNC_RECEIVE,    /* ETHTSYN_STATE_MACHINE_IDENTIFICATION_SYNC_RECEIVE_SM */
  ETHTSYN_SM_IDENT_SYNC_SEND,       /* ETHTSYN_STATE_MACHINE_IDENTIFICATION_SYNC_SEND_SM */
  ETHTSYN_SM_IDENT_SITE_SYNC_SYNC,  /* ETHTSYN_STATE_MACHINE_IDENTIFICATION_SITE_SYNC_SYNC_SM */
  ETHTSYN_SM_IDENT_ANNOUNCE_RECEIVE /* ETHTSYN_STATE_MACHINE_IDENTIFICATION_ANNOUNCE_RECEIVE_SM */
} EthTSyn_SmIdentEnumType;

typedef enum EthTSyn_TimestampDirEnum
{
  ETHTSYN_TS_DIR_INGRESS = 0u, /* ETHTSYN_SWT_MGMT_TIMESTAMP_DIRECTION_INGRESS */
  ETHTSYN_TS_DIR_EGRESS        /* ETHTSYN_SWT_MGMT_TIMESTAMP_DIRECTION_EGRESS */
} EthTSyn_TimestampDirEnumType;

/*! EthTSyn Switch Management Info struct definition */
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
typedef EthSwt_MgmtInfoType  EthTSyn_SwtMgmtInfoType;
# else
typedef struct EthTSyn_SwtMgmtInfoTypeStruct
{
  uint8                SwitchIdx; /*!< EthIf switch index */
  uint8                PortIdx;   /*!< EthSwt port index */
  EthTSyn_FrameIdType  FrameId;   /*!< Frame ID to identify the frame */
} EthTSyn_SwtMgmtInfoType;
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

# ifndef ETHTSYN_SWT_MGMT_MSG_BUFFER_PAYLOAD_SIZE
/* Dummy size. SwtMgmt is disabled and type is not used. */
#  define ETHTSYN_SWT_MGMT_MSG_BUFFER_PAYLOAD_SIZE (1u)
# endif

/*! EthTSyn Generic message struct definition (used for message buffer) */
typedef struct EthTSyn_SwtMgmt_GenericMsgTypeStruct
{
  EthTSyn_CommonMsgHdrType   MsgHdr;
  uint8                      Payload[ETHTSYN_SWT_MGMT_MSG_BUFFER_PAYLOAD_SIZE];
} EthTSyn_SwtMgmt_GenericMsgType;

typedef enum EthTSyn_MsgBufferStateEnum
{
  ETHTSYN_S_MSG_BUFFER_UNUSED = 0u,         /* ETHTSYN_SWT_MGMT_MSG_BUFFER_STATE_UNUSED */
  ETHTSYN_S_MSG_BUFFER_MSG_INVALID,         /* ETHTSYN_SWT_MGMT_MSG_BUFFER_STATE_MSG_INVALID */
  ETHTSYN_S_MSG_BUFFER_MSG_VALID,           /* ETHTSYN_SWT_MGMT_MSG_BUFFER_STATE_MSG_VALID */
  ETHTSYN_S_MSG_BUFFER_PORT_INFO_AVAILABLE, /* ETHTSYN_SWT_MGMT_MSG_BUFFER_STATE_PORT_INFO_AVAILABLE */
  ETHTSYN_S_MSG_BUFFER_MSG_PROCESSING,      /* ETHTSYN_SWT_MGMT_MSG_BUFFER_STATE_MSG_PROCESSING */
  ETHTSYN_S_MSG_BUFFER_DROP_MSG             /* ETHTSYN_SWT_MGMT_MSG_BUFFER_STATE_DROP_MESSAGE */
} EthTSyn_MsgBufferStateEnumType;

/*! EthTSyn message buffer struct definition */
typedef struct EthTSyn_SwtMgmt_MsgBufferTypeStruct
{
  EthTSyn_MsgBufferStateEnumType     MsgBufferState;
  EthTSyn_IntCtrlIdxType             CtrlIdx;     /*!< EthTSyn controller index of the received message */
  ETHTSYN_P2CONST(uint8)             RxBufAddr;   /*!< RxBufPtr used to assign MgmtInfo/Ts indications to the message */
  EthTSyn_SwtMgmtInfoType            SwtMgmtInfo; /*!< Indicating the Switch Port the message was received on and the
                                                       Frame Id of the message */
  EthTSyn_TimestampMgmtStructType    IngressTimestampMgmt;
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
  EthTSyn_TimestampMgmtStructType    EgressTimestampHostPortMgmt;
  EthTSyn_TimestampMgmtStructType    IngressTimestampHostCtrlMgmt;
# else
  EthTSyn_TimestampRawType          IngressTimestampRaw;
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */
  EthTSyn_SwtMgmt_GenericMsgType     Msg; /*!< The received message separated into Header and Payload.
                                                Stored in network byte oder. */
} EthTSyn_SwtMgmt_MsgBufferType;

typedef enum EthTSyn_SiteSyncSyncSmStateEnum
{
  ETHTSYN_S_SSS_SM_DISABLED = 0u,           /* ETHTSYN_STATE_SITE_SYNC_SYNC_DISABLED */
  ETHTSYN_S_SSS_SM_PENDING,                 /* ETHTSYN_STATE_SITE_SYNC_SYNC_PENDING */
  ETHTSYN_S_SSS_SM_TX_SYNC,                 /* ETHTSYN_STATE_SITE_SYNC_SYNC_SEND_SYNC */
  ETHTSYN_S_SSS_SM_TX_FUP,                  /* ETHTSYN_STATE_SITE_SYNC_SYNC_SEND_FOLLOW_UP */
  ETHTSYN_S_SSS_SM_SYNC_TIMEOUT,            /* ETHTSYN_STATE_SITE_SYNC_SYNC_SYNC_TIMEOUT */
  ETHTSYN_S_SSS_SM_RCVD_SYNC_AFTER_TIMEOUT, /* ETHTSYN_STATE_SITE_SYNC_SYNC_RECEIVED_SYNC_AFTER_TIMEOUT */
  ETHTSYN_S_SSS_SM_RCVD_FUP_AFTER_TIMEOUT   /* ETHTSYN_STATE_SITE_SYNC_SYNC_RECEIVED_FUP_AFTER_TIMEOUT */
} EthTSyn_SiteSyncSyncSmStateEnumType;

/*! EthTSyn Site Sync Sync state-machine struct definition */
typedef struct EthTSyn_SiteSyncSyncSmTypeStruct
{
  EthTSyn_SwtMgmt_GenericMsgType           Msg;
  uint16                                   TxConfirmationPending;
  EthTSyn_SiteSyncSyncSmStateEnumType      State;
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
  boolean                                  ProvideSwtTimeSyncTimestamps;
# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
} EthTSyn_SiteSyncSyncSmType;

/*! EthTSyn TimeDomain state struct definition */
typedef struct EthTSyn_TimeDomainStateTypeStruct
{
  EthTSyn_SizeOfSlavePortType  SlavePortIdx;
} EthTSyn_TimeDomainStateType;

/*! EthTSyn Rx Frame Info struct definition */
typedef struct EthTSyn_SwtMgmt_RxFrameInfoTypeStruct
{
  EthTSyn_GlobalTimestampType IngressTimestamp;
} EthTSyn_SwtMgmt_RxFrameInfoType;

/*! EthTSyn Switch Time Sync Timestamp Info struct definition. */
typedef struct EthTSyn_SwtTimeSync_TimestampInfoStruct
{
  EthTSyn_GlobalTimestampType  SyncIngressTimestamp;   /*!< Switch sync ingress timestamp of the sync event */
  EthTSyn_GlobalTimestampType  PreciseOriginTimestamp; /*!< Precise origin timestamp of the sync event */
  uint16                       SequenceId;             /*!< Sequence Id of the sync event */
} EthTSyn_SwtTimeSync_TimestampInfoStructType;

/*! Switch Sync State Change callback function pointer type definition */
typedef ETHTSYN_P2FUNC(void, EthTSyn_SwtTimeSync_SwtSyncStateChgFctPtrType) (uint8, EthTSyn_SyncStateType);

#endif /* ETHTSYN_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Types.h
 *********************************************************************************************************************/
