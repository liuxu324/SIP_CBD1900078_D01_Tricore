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
/**        \file  EthTSyn_Slave_Int.c
 *        \brief  EthTSyn Slave source file - Internal Functions
 *
 *      \details  EthTSyn Slave source file containing the EthTSyn Slave implementation of the EthTSyn module.
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

#define ETHTSYN_SLAVE_INT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EthTSyn_Slave_Int.h" /* PRQA S 3219, 0883 */ /* MD_EthTSyn_3219, MD_EthTSyn_0883 */

#if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
# include "EthTSyn_Pdelay_Int.h"
# include "EthTSyn_SwtMgmt_Int.h"
# include "EthTSyn_Crc_Int.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of EthTSyn header file */
# if (  (ETHTSYN_SW_MAJOR_VERSION != (7u)) \
     || (ETHTSYN_SW_MINOR_VERSION != (0u)) \
     || (ETHTSYN_SW_PATCH_VERSION != (0u)) )
#  error "Vendor specific version numbers of EthTSyn_Slave_Int.c and EthTSyn.h are inconsistent"
# endif

/* Check the version of the configuration header file */
# if (  (ETHTSYN_CFG_MAJOR_VERSION != (7u)) \
     || (ETHTSYN_CFG_MINOR_VERSION != (0u)) )
#  error "Version numbers of EthTSyn_Slave_Int.c and EthTSyn_Cfg.h are inconsistent!"
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

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETHTSYN_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  EthTSyn_Slave_InitPortInternal
 *********************************************************************************************************************/
/*! \brief      Initializes the passed Slave-Port.
 *  \details    Initializes all component variables directly related to the passed EthTSyn Slave-Port.
 *  \param[in]  SlavePortIdx  Index of the slave port
 *                            [range: SlavePortIdx < EthTSyn_GetSizeOfSlavePort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_InitPortInternal(
  EthTSyn_SlavePortIterType SlavePortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Slave_ProcessSmSyncReceive
 *********************************************************************************************************************/
/*! \brief      Handles the processing of the Sync Receive state-machine for the passed Slave-Port.
 *  \details    -
 *  \param[in]  SlavePortIdx    Index of the slave port which state-machine should be processed
 *                              [range: SlavePortIdx < EthTSyn_GetSizeOfSlavePort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Slave-Port indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_ProcessSmSyncReceive(
  EthTSyn_SlavePortIterType SlavePortIdx);

# if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Slave_ProcessSmAnnounceReceive
 *********************************************************************************************************************/
/*! \brief      Processing of the Announce receive state-machine for the passed Slave-Port.
 *  \details    -
 *  \param[in]  SlavePortIdx    Index of the slave port which state-machine should be processed
 *                              [range: SlavePortIdx < EthTSyn_GetSizeOfSlavePort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Slave-Port indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_ProcessSmAnnounceReceive(
  EthTSyn_SlavePortIterType SlavePortIdx);
# endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_IsPortReadyToReceiveSync
 *********************************************************************************************************************/
/*! \brief      Checks if the passed Port is ready to receive a sync message.
 *  \details    Checks the PortRole, AsCapableState, SyncReceiveSm state and handles the
 *              Master-Slave-Conflict Detection.
 *  \param[in]  PortIdx             Index of EthTSyn port that shall receive the sync message
 *                                  [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - Port is ready to receive the sync message
 *  \return     FALSE - Port is not ready to receive the sync message
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_SlaveRx_IsPortReadyToReceiveSync(
  EthTSyn_IntPortIdxType    PortIdx);
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

# if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_HandleArFollowUpTlvs
 *********************************************************************************************************************/
/*! \brief         Handles the AUTOSAR (Sub-)Tlvs included in a FollowUp message.
 *  \details       This function validates the CRC of each AR (Sub-)Tlv included in the received FollowUp message
 *                 (if applicable), extracts the Status and UserData from the corresponding Sub-Tlv and handles the
 *                 Offset TimeDomain Sub-Tlvs.
 *  \param[in]     PortIdx       Index of the Port the message was received on
 *                               [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]     ComMsgHdrPtr  The common message header of the received FollowUp message
 *  \param[out]    StatusPtr     Pointer to where to store the retrieved Status
 *  \param[in,out] UserDataPtr   In:  Pointer to Pointer to where to store the extracted UserData
 *                               Out: NULL_PTR if UserData are not applicable
 *  \return        E_OK - Successfully retrieved handled Tlvs. FollowUp message can be received
 *  \return        E_NOT_OK - Failed to process the SubTlvs.
 *  \pre           Constraint for PortIdx: EthTSyn_IsSlavePortUsedOfPort() == TRUE
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different Port indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_HandleArFollowUpTlvs(
                  EthTSyn_IntPortIdxType            PortIdx,
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType)         ComMsgHdrPtr,
    ETHTSYN_P2VAR(StbM_TimeBaseStatusType)          StatusPtr,
    ETHTSYN_P2VAR(ETHTSYN_P2VAR(StbM_UserDataType)) UserDataPtrPtr);

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_GetFirstArSubTlvPtrAndCnt
 *********************************************************************************************************************/
/*! \brief      Gets the pointer to the first Ar Sub-Tlv and the Ar Sub-Tlv count.
 *  \details    Gets the amount of Ar Sub-Tlvs and the Pointer to the first Sub-Tlv. Furthermore some general checks
 *              regarding the Ar (Sub-) Tlvs are performed (if applicable: check Crc as well).
 *  \param[in]  PortIdx            Index of the Port the message was received on
 *                                 [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  ComMsgHdrPtr       Pointer to the common message header of the received FollowUp message
 *  \param[out] FirstSubTlvPtrPtr  Pointer to the first Ar Sub-Tlv of the message (NULL_PTR) if no Sub-Tlvs is found
 *  \param[out] SubTlvCnt          The number of found Ar Sub-Tlvs (will also be increased for unknown TLV Types)
 *  \return     E_OK - Successfully retrieved the SubTlv Ptr and count. General checks passed.
 *  \return     E_NOT_OK - Failed to retrieve the SubTlvPtr/count or general checks failed.
 *  \pre        Constraint for PortIdx: EthTSyn_IsSlavePortUsedOfPort() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_GetFirstArSubTlvPtrAndCnt(
                                EthTSyn_IntPortIdxType                PortIdx,
                ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType)             ComMsgHdrPtr,
  ETHTSYN_P2VAR(ETHTSYN_P2CONST(EthTSyn_ArSubTlvAbstractHeaderType))  FirstSubTlvPtrPtr,
                  ETHTSYN_P2VAR(uint8)                                SubTlvCnt);

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_CheckArTlvHeader
 *********************************************************************************************************************/
/*! \brief      Checks the validity of the AR Tlv-Header (if present) and extracts the total length of the Sub-Tlvs.
 *  \details    -
 *  \param[in]  ArTlvHdrPtr        Pointer to the potential Ar Tlv header of the received FollowUp message
 *  \param[in]  FollowUpMsgLength  The total length of the FollowUp message in byte.
 *  \param[out] TotalSubTlvLength  The total length of all Ar Sub-Tlvs (i.e. Length field of the Ar Tlv-Header -
 *                                 length of the Ar Tlv-Header itself)
 *  \return     E_OK - Check of Ar Tlv Header passed.
 *  \return     E_NOT_OK - Check of Ar Tlv Header failed.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_CheckArTlvHeader(
  ETHTSYN_P2CONST(EthTSyn_ArTlvHeaderType)  ArTlvHdrPtr,
                  uint16                    FollowUpMsgLength,
    ETHTSYN_P2VAR(uint16)                   TotalSubTlvLength);

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_CheckArSubTlvCrc
 *********************************************************************************************************************/
/*! \brief      Validates the Type and the Crc (if applicable) of the given FollowUp Ar Sub-Tlv.
 *  \details    -
 *  \param[in]  PortIdx            Index of the Port the FollowUp message was received on
 *                                 [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  ComMsgPtr          Pointer to the common message header of the FollowUp message
 *  \param[in]  ArTlvHdrPtr        Pointer to the potential Ar Tlv header of the received FollowUp message
 *  \return     E_OK - Check of Ar Sub Tlv passed.
 *  \return     E_NOT_OK - Check of Ar Sub Tlv failed.
 *  \pre        Constraint for PortIdx: EthTSyn_IsSlavePortUsedOfPort() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_CheckArSubTlvCrc(
                  EthTSyn_IntPortIdxType              PortIdx,
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType)           ComMsgPtr,
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvAbstractHeaderType) ArSubTlvPtr);

#  if (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_HandleOfsSubTlvs
 *********************************************************************************************************************/
/*! \brief      Unpacks all Ofs-Sub-Tlvs and forwards the new Offset to the StbM.
 *  \details    -
 *  \param[in]  TimeDomainIdx   Index of the TimeDomain the FollowUp was received for
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \param[in]  FirstSubTlvPtr  Pointer to the first Ar Sub-Tlv
 *  \param[in]  SubTlvCount     The amount of the Ar Sub-Tlvs (including unknown Tlv-Types)
 *  \pre        The Pointer to the FirstSubTlv and the SubTlvCount must have been retrieved using
 *              EthTSyn_SlaveRx_GetFirstArSubTlvPtrAndCnt
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TimeDomain indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SlaveRx_HandleOfsSubTlvs(
                  EthTSyn_IntTimeDomainIdxType         TimeDomainIdx,
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvAbstractHeaderType)  FirstSubTlvPtr,
                  uint8                                SubTlvCount);
#  endif /* (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON) */

#  if (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_ProcessOfsSubTlv
 *********************************************************************************************************************/
/*! \brief      Processes the given Ofs Sub-Tlv.
 *  \details    Checks if the Offset TimeDomain passed via Ofs Sub-Tlv is valid for the passed TimeDomain. If it is
 *              valid, the new offset is forwarded to the StbM.
 *  \param[in]  TimeDomainIdx   Index of the TimeDomain the FollowUp was received for
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \param[in]  FirstSubTlvPtr  Pointer to the Offset time domain Sub-Tlv
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TimeDomain indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SlaveRx_ProcessOfsSubTlv(
                  EthTSyn_IntTimeDomainIdxType  TimeDomainIdx,
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvOfsType)      OfsSubTlvPtr);
#  endif /* (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_GetUserDataFromSubTlv
 *********************************************************************************************************************/
/*! \brief      Checks if a UserData Sub-Tlv is present and retrieve the UserData.
 *  \details    -
 *  \param[in]  FirstSubTlvPtr  Pointer to the first Ar Sub-Tlv
 *  \param[in]  SubTlvCount     The amount of the Ar Sub-Tlvs (including unknown Tlv-Types)
 *  \param[out] UserDataPtr     Pointer to where to store the retrieved UserData
 *  \return     E_OK - UserData Sub-Tlv found and successfully retrieved the UserData
 *  \return     E_NOT_OK - No UserData Sub-Tlv found or failed to retrieve the UserData
 *  \pre        The Pointer to the FirstSubTlv and the SubTlvCount must have been retrieved using
 *              EthTSyn_SlaveRx_GetFirstArSubTlvPtrAndCnt
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_GetUserDataFromSubTlv(
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvAbstractHeaderType)  FirstSubTlvPtr,
                  uint8                                SubTlvCount,
    ETHTSYN_P2VAR(StbM_UserDataType)                   UserDataPtr);

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_GetStatusFromSubTlv
 *********************************************************************************************************************/
/*! \brief      Checks if a Status Sub-Tlv is present and retrieve the Status.
 *  \details    -
 *  \param[in]  FirstSubTlvPtr  Pointer to the first Ar Sub-Tlv
 *  \param[in]  SubTlvCount     The amount of the Ar Sub-Tlvs (including unknown Tlv-Types)
 *  \param[out] StatusPtr       Pointer to where to store the retrieved Status
 *  \return     E_OK - Status Sub-Tlv found and successfully retrieved the Status
 *  \return     E_NOT_OK - No Status Sub-Tlv found or failed to retrieve the Status
 *  \pre        The Pointer to the FirstSubTlv and the SubTlvCount must have been retrieved using
 *              EthTSyn_SlaveRx_GetFirstArSubTlvPtrAndCnt
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_GetStatusFromSubTlv(
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvAbstractHeaderType)  FirstSubTlvPtr,
                  uint8                                SubTlvCount,
    ETHTSYN_P2VAR(StbM_TimeBaseStatusType)             StatusPtr);
# endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_GetTimeDiffSinceSyncRx
 *********************************************************************************************************************/
/*! \brief      Computes the time passed since the reception of the corresponding Sync message.
 *  \details    -
 *  \param[in]  PortIdx                  Index of the Port the FollowUp message was received on
 *                                       [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  SyncIngressTimestampPtr  The ingress timestamp of the corresponding Sync message
 *  \param[out] TimeDiffSinceSyncRxPtr   The time difference since the reception of the Sync message
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_GetTimeDiffSinceSyncRx(
                  EthTSyn_IntPortIdxType        PortIdx,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType)  SyncIngressTimestampPtr,
    ETHTSYN_P2VAR(EthTSyn_TimediffType)         TimeDiffSinceSyncRxPtr);

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_ProvideTimeToStbm
 *********************************************************************************************************************/
/*! \brief      Handles the call of StbM_BusSetGlobalTime() for a received FollowUp message (no Offset time domain).
 *  \details    -
 *  \param[in]  PortIdx                   Index of the Port the FollowUp message was received on
 *                                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  TimeDiffSinceSyncRx       The time difference passed since reception of the corresponding Sync message
 *  \param[in]  TimeBaseStatus            The Time base status extracted from Status TLV (if present)
 *  \param[in]  ComMsgPtr                 Pointer to the Rx Buffer (message header) of the FollowUp message
 *  \param[in]  UserDataPtr               The User Data extracted form the UserData TLV (if present)
 *  \pre        Constraint for PortIdx: EthTSyn_IsSlavePortUsedOfPort() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SlaveRx_ProvideTimeToStbm(
                  EthTSyn_IntPortIdxType       PortIdx,
                  EthTSyn_TimediffType         TimeDiffSinceSyncRx,
                  StbM_TimeBaseStatusType      TimeBaseStatus,
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType)    ComMsgPtr,
  ETHTSYN_P2CONST(StbM_UserDataType)           UserDataPtr);

/**********************************************************************************************************************
 *  EthTSyn_Slave_SyncReceiveHandleFollowUpTimeout
 *********************************************************************************************************************/
/*! \brief      Handles a FollowUp Rx timeout.
 *  \details    Changes the state of every SyncSend state machine assigned to the passed TimeDomain to
 *              ETHTSYN_S_SYNC_SEND_SM_SSS_PENDING and the state of the SiteSyncSync state machine to
 *              ETHTSYN_S_SSS_SM_PENDING.
 *  \param[in]  TimeDomainIdx     Index of the TimeDomain
 *                                [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \pre        FollowUp timeout was detected on the Slave-Port of the passed TimeDomain
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_SyncReceiveHandleFollowUpTimeout(
  EthTSyn_IntTimeDomainIdxType  TimeDomainIdx);
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_Slave_SyncReceiveHandleSyncTimeout
 *********************************************************************************************************************/
/*! \brief      Checks if a sync receive timeout occurred and handles it.
 *  \details    Checks if a sync receive timeout occurred for the provided SyncReceive state machine. If so,
 *              the SyncReceive state machine is set to state ETHTSYN_S_SYNC_RCV_SM_SYNC_TIMEOUT, the SiteSyncSync
 *              state machine is set to state ETHTSYN_S_SSS_SM_SYNC_TIMEOUT and all SyncSend state machines assigned
 *              to the passed TimeDomain are set to state ETHTSYN_S_SYNC_SEND_SM_INITIALIZING.
 *  \param[in]  TimeDomainIdx     Index of the TimeDomain
 *                                [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \param[in]  SyncReceiveSmPtr  Pointer to the Sync receive state machine
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
# if ((ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) && (ETHTSYN_SWT_MGMT_IS_GM_CAPABLE == STD_ON))
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_SyncReceiveHandleSyncTimeout(
                EthTSyn_IntTimeDomainIdxType   TimeDomainIdx,
  ETHTSYN_P2VAR(EthTSyn_SyncReceiveSmType)     SyncReceiveSmPtr); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# endif /* ((ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) && (ETHTSYN_SWT_MGMT_IS_GM_CAPABLE == STD_ON)) */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Slave_InitPortInternal
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_InitPortInternal(EthTSyn_SlavePortIterType SlavePortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_P2VAR(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(SlavePortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize sync receive state machine. */
  IpBase_Fill((ETHTSYN_P2VAR(IpBase_CopyDataType))syncReceiveSmPtr, 0, sizeof(EthTSyn_SyncReceiveSmType)); /* PRQA S 0310 */ /* MD_EthTSyn_0310_IpBase */ /* SBSW_ETHTSYN_API_ARGUMENT_IDX */

# if (ETHTSYN_SRC_PORT_IDENT_CHECK_SUPPORT == STD_ON)
  /* #20 Initialize optional master identity. */
  if(EthTSyn_IsMasterPortIdentityUsedOfSlavePort(SlavePortIdx) == TRUE)
  {
    const EthTSyn_MasterPortIdentityIdxOfSlavePortType masterPortIdentIdx =
      EthTSyn_GetMasterPortIdentityIdxOfSlavePort(SlavePortIdx);
    const EthTSyn_PortIdxOfSlavePortType portIdx = EthTSyn_GetPortIdxOfSlavePort(SlavePortIdx);
    const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(portIdx);
    const EthTSyn_ClockIdentityOfMasterPortIdentityType clockIdentity =
      EthTSyn_GetClockIdentityOfMasterPortIdentity(masterPortIdentIdx);

    EthTSyn_SetGmPresentOfSystemState(timeDomainIdx, TRUE);                                                            /* SBSW_ETHTSYN_CSL03 */
    EthTSyn_SetGmClockIdentityOfSystemState(timeDomainIdx, clockIdentity);                                             /* SBSW_ETHTSYN_CSL03 */
  }
# endif /* (ETHTSYN_SRC_PORT_IDENT_CHECK_SUPPORT == STD_ON) */
} /* EthTSyn_Slave_InitPortInternal() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_Slave_ProcessSmSyncReceive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_ProcessSmSyncReceive(EthTSyn_SlavePortIterType SlavePortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_CONSTP2VAR(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(SlavePortIdx);
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
  const EthTSyn_PortIdxOfSlavePortType portIdx = EthTSyn_GetPortIdxOfSlavePort(SlavePortIdx);
  const EthTSyn_IntTimeDomainIdxType timeDomainIdx= EthTSyn_GetTimeDomainIdxOfPort(portIdx);
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

  /* ----- Implementation ----------------------------------------------- */
  ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #10 Check sync receive state machine state. */
  switch(syncReceiveSmPtr->State)
  {
  case ETHTSYN_S_SYNC_RCV_SM_WAIT_FUP:
    {
      /* #100 State: Waiting for follow up -> check for FollowUp receive timeout. */
      if(EthTSyn_GetFollowUpAlloweRxDelayOfSlavePort(SlavePortIdx) > 0)
      {
        if(syncReceiveSmPtr->FollowUp.FollowUpRxTimeoutCnt == 0)
        {
          syncReceiveSmPtr->State = ETHTSYN_S_SYNC_RCV_SM_DISCARD;                                                       /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
          if (EthTSyn_Util_IsSwitchPort((EthTSyn_IntPortIdxType)portIdx) == TRUE)
          {
            EthTSyn_Slave_SyncReceiveHandleFollowUpTimeout(timeDomainIdx);
          }
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
        }
      }
      break;
    }

# if ((ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) && (ETHTSYN_SWT_MGMT_IS_GM_CAPABLE == STD_ON))
  case ETHTSYN_S_SYNC_RCV_SM_WAIT_SYNC:
    {
      /* #101 State: Waiting for sync (with switch management only) -> Check if system is currently acting as bridge.
       *      If so handle possible sync timeout. */
      /* PRQA S 3415 2 */ /* MD_EthTSyn_3415_ReadOnly */
      if( (EthTSyn_GetSwtMgmtSyncTimeoutOfTimeDomain(timeDomainIdx) > 0) &&
        (EthTSyn_Util_IsSwitchPort((EthTSyn_IntPortIdxType)portIdx) == TRUE) )
      {
        EthTSyn_Slave_SyncReceiveHandleSyncTimeout(timeDomainIdx, syncReceiveSmPtr);                                     /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
      }
      break;
    }
# endif /* ((ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) && (ETHTSYN_SWT_MGMT_IS_GM_CAPABLE == STD_ON)) */
  default:
    {
      /* Nothing to do here. */
      break;
    }
  }
  ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

} /* EthTSyn_Slave_ProcessSmSyncReceive() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

# if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Slave_ProcessSmAnnounceReceive
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_ProcessSmAnnounceReceive(
  EthTSyn_SlavePortIterType SlavePortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_PortIdxOfSlavePortType portIdx = EthTSyn_GetPortIdxOfSlavePort(SlavePortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if port is AsCapable. */
  if(EthTSyn_Util_IsAsCapable(portIdx) == TRUE)
  {
    const EthTSyn_AnnounceInfoIdxOfSlavePortType announceInfoIdx = EthTSyn_GetAnnounceInfoIdxOfSlavePort(SlavePortIdx);
    EthTSyn_AnnounceReceiveSmPtrType announceRcvSmPtr = EthTSyn_GetAddrAnnounceReceiveSm(announceInfoIdx);
    /* #20 Check for announce receive timeout and handle it. */
    if(announceRcvSmPtr->RxTimeoutCnt == 0u)
    {
      const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(portIdx);
      EthTSyn_Slave_ResetMasterPriorityVector(timeDomainIdx);
    }
  }

} /* EthTSyn_Slave_ProcessSmAnnounceReceive() */
# endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_IsPorTReadyToReceiveSync
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_SlaveRx_IsPortReadyToReceiveSync(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isReady = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if port is AsCapable. */
  if (EthTSyn_Util_IsAsCapable(PortIdx) == TRUE)
  {
    const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
    ETHTSYN_CONSTP2VAR(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(slavePortIdx);
    /* #20 Check sync receive state machine state. */
    if ((syncReceiveSmPtr->State == ETHTSYN_S_SYNC_RCV_SM_DISCARD) ||
      (syncReceiveSmPtr->State == ETHTSYN_S_SYNC_RCV_SM_WAIT_SYNC))
    {
      isReady = TRUE;
    }
  }

  return isReady;
}
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

# if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_HandleArFollowUpTlvs
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
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_HandleArFollowUpTlvs(
                  EthTSyn_IntPortIdxType    PortIdx,
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) ComMsgHdrPtr,
    ETHTSYN_P2VAR(StbM_TimeBaseStatusType)  StatusPtr,
    ETHTSYN_P2VAR(StbM_UserDataType*)       UserDataPtrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  uint8 subTlvCnt = 0u;
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvAbstractHeaderType) firstSubTlvPtr = NULL_PTR;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle possible FollowUp Tlvs: Retrieve Pointer to the first Ar Sub-Tlv and the Sub-Tlv count. */
  retVal = EthTSyn_SlaveRx_GetFirstArSubTlvPtrAndCnt(PortIdx, ComMsgHdrPtr, &firstSubTlvPtr, &subTlvCnt);              /* SBSW_ETHTSYN_PASSING_API_POINTER */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
  if ((retVal == E_OK) && (firstSubTlvPtr != NULL_PTR))
  {
    /* #20 Get User data from corresponding Sub-Tlv. */
    if (EthTSyn_SlaveRx_GetUserDataFromSubTlv(firstSubTlvPtr, subTlvCnt, *UserDataPtrPtr) == E_NOT_OK)                 /* SBSW_ETHTSYN_PASSING_API_POINTER */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
    {
      /* #200 Failed to retrieve the UserData. Set UserDataPtrPtr to NULL_PTR. */
      *UserDataPtrPtr = NULL_PTR; /* SBSW_ETHTSYN_VALID_API_POINTER */
    }
    /* #30 Get Status from corresponding Sub-Tlv. */
    if (EthTSyn_SlaveRx_GetStatusFromSubTlv(firstSubTlvPtr, subTlvCnt, StatusPtr) == E_NOT_OK)                         /* SBSW_ETHTSYN_PASSING_API_POINTER */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
    {
      /* #300 Failed to retrieve the status. Set status to '0'. */
      *StatusPtr = 0; /* SBSW_ETHTSYN_VALID_API_POINTER */
    }

    /* #40 Handle Offset Sub-Tlvs. */
#  if (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON)
    EthTSyn_SlaveRx_HandleOfsSubTlvs(EthTSyn_GetTimeDomainIdxOfPort(PortIdx), firstSubTlvPtr, subTlvCnt);              /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
#  endif /* (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON) */
  }

  return retVal;
} /* EthTSyn_SlaveRx_HandleArFollowUpTlvs() */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_GetFirstArSubTlvPtrAndCnt
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
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_GetFirstArSubTlvPtrAndCnt(
                  EthTSyn_IntPortIdxType                               PortIdx,
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType)                            ComMsgHdrPtr,
    ETHTSYN_P2VAR(ETHTSYN_P2CONST(EthTSyn_ArSubTlvAbstractHeaderType)) FirstSubTlvPtrPtr,
    ETHTSYN_P2VAR(uint8)                                               SubTlvCnt)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  ETHTSYN_P2CONST(EthTSyn_ArTlvHeaderType) arTlvHdrPtr;
  uint16 offsetToArTlvHdr;
  sint32 remainingLength;
  uint16 subTlvTotalLength = 0u;
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvAbstractHeaderType) subTlvPtr;
  const uint16 msgLength = (uint16)EthTSyn_Ntohs(ComMsgHdrPtr->MessageLength);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize out parameters */
  (*FirstSubTlvPtrPtr) = NULL_PTR;                                                                                     /* SBSW_ETHTSYN_VALID_API_POINTER */
  (*SubTlvCnt) = 0u;                                                                                                   /* SBSW_ETHTSYN_VALID_API_POINTER */

  /* #20 Check if the message length indicates at least one Ar-Tlv */
  if(msgLength >= (ETHTSYN_MSG_FOLLOW_UP_RX_MIN_LENGTH + ETHTSYN_AR_TLV_HEADER_LENGTH))
  {
    /* PRQA S 0310 2 */ /* MD_EthTSyn_0310_SubType */
    arTlvHdrPtr = (ETHTSYN_P2CONST(EthTSyn_ArTlvHeaderType))
      &((ETHTSYN_P2CONST(uint8))ComMsgHdrPtr)[ETHTSYN_MSG_FOLLOW_UP_RX_MIN_LENGTH];

    /* #30 Check Ar Tlv Header */
    retVal = EthTSyn_SlaveRx_CheckArTlvHeader(arTlvHdrPtr, msgLength, &subTlvTotalLength);                             /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */

    if(retVal == E_OK)
    {
      /* #40 Unpack and check Sub-Tlvs */
      offsetToArTlvHdr = ETHTSYN_AR_TLV_HEADER_LENGTH;
      remainingLength = (sint32)subTlvTotalLength;

      /* PRQA S 0310 2 */ /* MD_EthTSyn_0310_SubType */
      (*FirstSubTlvPtrPtr) = (ETHTSYN_P2CONST(EthTSyn_ArSubTlvAbstractHeaderType))
        &((ETHTSYN_P2CONST(uint8))arTlvHdrPtr)[offsetToArTlvHdr];                                                      /* SBSW_ETHTSYN_VALID_API_POINTER */

      do
      {
        uint8 tlvLength;

        /* PRQA S 0310 2 */ /* MD_EthTSyn_0310_SubType */
        subTlvPtr = (ETHTSYN_P2CONST(EthTSyn_ArSubTlvAbstractHeaderType))
          &((ETHTSYN_P2CONST(uint8))arTlvHdrPtr)[offsetToArTlvHdr];
        tlvLength = ETHTSYN_AR_SUB_TLV_ABSTRACT_HDR_LENGTH;
        tlvLength += subTlvPtr->Length;

        remainingLength -= (sint32)tlvLength;

        /* #50 Check if Sub Tlv fits in the message */
        if(remainingLength >= 0)
        {
          offsetToArTlvHdr += tlvLength;
          (*SubTlvCnt)++;                                                                                              /* SBSW_ETHTSYN_VALID_API_POINTER */

          /* Process Sub-Tlv */
          /* #500 Check if Crc is included and valid */
          retVal = EthTSyn_SlaveRx_CheckArSubTlvCrc(PortIdx, ComMsgHdrPtr, subTlvPtr);                                 /* SBSW_ETHTSYN_PASSING_API_POINTER */ /* SBSW_ETHTSYN_POINTER_VARIABLE */
        }
        else
        {
          /* #501 Message is to small to hold this Sub Tlv -> Drop message */
          retVal = E_NOT_OK;
        }
      } while((retVal == E_OK) && (remainingLength > (sint32)ETHTSYN_AR_SUB_TLV_ABSTRACT_HDR_LENGTH));
    }
  }
  else
  {
    /* According to message length, no Ar Tlv can be included in the message. This is valid. */
    retVal = E_OK;
  }

  return retVal;
} /* EthTSyn_SlaveRx_GetFirstArSubTlvPtrAndCnt() */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_CheckArTlvHeader
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_CheckArTlvHeader(
  ETHTSYN_P2CONST(EthTSyn_ArTlvHeaderType) ArTlvHdrPtr,
                  uint16                   FollowUpMsgLength,
    ETHTSYN_P2VAR(uint16)                  TotalSubTlvLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint16 arTlvTypeField;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Ar-Tlv Header is present */
  ETHTSYN_GET_UINT16(ArTlvHdrPtr->TlvType, 0u, arTlvTypeField);

  if(arTlvTypeField == ETHTSYN_AR_TLV_TYPE)
  {
    /* #20 Perform general checks of the AR-Tlv Header fields */
    uint16 arTlvLengthField;
    const uint16 maxAllowedArTlvLength = (uint16)
        (FollowUpMsgLength - ETHTSYN_MSG_FOLLOW_UP_RX_MIN_LENGTH - ETHTSYN_AR_TLV_HEADER_TYPE_LENGTH_FIELDS_LENGTH);

    ETHTSYN_GET_UINT16(ArTlvHdrPtr->LengthField, 0u, arTlvLengthField);

    if((arTlvLengthField > (ETHTSYN_AR_TLV_HEADER_LENGTH_FIELD_VALUE + ETHTSYN_AR_SUB_TLV_ABSTRACT_HDR_LENGTH)) &&
        (arTlvLengthField <= maxAllowedArTlvLength))
    {
      uint32 arTlvOrgaId;
      uint32 arTlvOrgaSubType;

      ETHTSYN_GET_3_BYTE(ArTlvHdrPtr->OrganisationId, 0u, arTlvOrgaId);
      ETHTSYN_GET_3_BYTE(ArTlvHdrPtr->OrganisationSubType, 0u, arTlvOrgaSubType);

      if((arTlvOrgaId == ETHTSYN_AR_TLV_ORGANIZATION_ID) &&
        (arTlvOrgaSubType == ETHTSYN_AR_TLV_ORGANIZATION_SUB_TYPE))
      {
        /* #30 Ar Tlv Header valid. Extract total length of Sub-Tlvs */
        (*TotalSubTlvLength) = (uint16)(arTlvLengthField - ETHTSYN_AR_TLV_HEADER_LENGTH_FIELD_VALUE);                  /* SBSW_ETHTSYN_VALID_API_POINTER */
        retVal = E_OK;
      }
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_CheckArSubTlvCrc
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
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_CheckArSubTlvCrc(
                  EthTSyn_IntPortIdxType              PortIdx,
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType)           ComMsgPtr,
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvAbstractHeaderType) ArSubTlvPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
  const EthTSyn_RxCrcValidatedEnumType rxCrcValidated = EthTSyn_GetRxCrcValidatedOfSlavePort(slavePortIdx);
#  if (ETHTSYN_CRC_SUPPORT == STD_ON)
  const uint8 rxCrcValidatedFlags = EthTSyn_GetCrcFlagsRxValidatedOfSlavePort(slavePortIdx);
  boolean timeSecuredCrcFlagsValid = TRUE;
#  endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Crc is included and matches the configuration. Validate Crc if required. */
  switch(ArSubTlvPtr->Type)
  {
    case ETHTSYN_AR_SUB_TLV_TYPE_TIME_SECURED:
      {
        /* #100 Time secured Tlv. Check if the CrcTimeFlags match the configuration. */
#  if (ETHTSYN_CRC_SUPPORT == STD_ON)
        timeSecuredCrcFlagsValid = (boolean)(
          ((ETHTSYN_P2CONST(EthTSyn_ArSubTlvTimeSecuredType))ArSubTlvPtr)->CrcTimeFlags == rxCrcValidatedFlags); /* PRQA S 0310 */ /* MD_EthTSyn_0310_SubType */
#  endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */
      }
      /* no break */
    case ETHTSYN_AR_SUB_TLV_TYPE_OFS_SECURED: /* PRQA S 2003 */ /* MD_EthTSyn_2003 */
    case ETHTSYN_AR_SUB_TLV_TYPE_STATUS_SECURED:
    case ETHTSYN_AR_SUB_TLV_TYPE_USER_DATA_SECURED:
      {
        /* #101 Secured Tlv. Check if this is valid and if Crc validation is required. */
        if(rxCrcValidated == ETHTSYN_RX_CRC_VALIDATED_CRC_IGNORED)
        {
          /* #1010 Secured type valid. No validation of Crc required. */
          retVal = E_OK;
        }
#  if (ETHTSYN_CRC_SUPPORT == STD_ON)
        else if((rxCrcValidated == ETHTSYN_RX_CRC_VALIDATED_CRC_OPTIONAL) ||
          (rxCrcValidated == ETHTSYN_RX_CRC_VALIDATED_CRC_VALIDATED) )
        {
          /* #1011 Secured type valid. Validation of Crc required -> Validate Crc. */
          const uint8 dataId = EthTSyn_Util_GetFollowUpDataIdListEntry(EthTSyn_GetTimeDomainIdxOfPort(PortIdx),
            (uint16)EthTSyn_Ntohs(ComMsgPtr->SequenceId));
          /* PRQA S 3415 2 */ /* MD_EthTSyn_3415_ReadOnly */
          if((timeSecuredCrcFlagsValid == TRUE) &&
              (EthTSyn_Crc_ValidateSubTlvCrc(dataId, ComMsgPtr, ArSubTlvPtr) == TRUE))                                 /* SBSW_ETHTSYN_PASSING_API_POINTER */
          {
            retVal = E_OK;
          }
        }
#  endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */
        else
        {
          /* Nothing to do here. */
        }
        break;
      }

    case ETHTSYN_AR_SUB_TLV_TYPE_OFS_NOT_SECURED:
    case ETHTSYN_AR_SUB_TLV_TYPE_STATUS_NOT_SECURED:
    case ETHTSYN_AR_SUB_TLV_TYPE_USER_DATA_NOT_SECURED:
      {
        /* #102 Not Secured Sub-Tlv --> Check if this is valid. */
#  if (ETHTSYN_CRC_SUPPORT == STD_ON)
        if(rxCrcValidated != ETHTSYN_RX_CRC_VALIDATED_CRC_VALIDATED)
#  endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */
        {
          /* #1020 No Crc required -> receive message. */
          retVal = E_OK;
        }
        break;
      }

    default:
      {
        /* #103 Unknown Tlv-Type --> skip. */
        retVal = E_OK;
        break;
      }
  }

#  if (ETHTSYN_CRC_SUPPORT == STD_OFF)
  ETHTSYN_DUMMY_STATEMENT(ComMsgPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#  endif /* (ETHTSYN_CRC_SUPPORT == STD_OFF) */

  return retVal;
} /* EthTSyn_SlaveRx_CheckArSubTlvCrc() */

#  if (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_HandleOfsSubTlvs
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SlaveRx_HandleOfsSubTlvs(
                  EthTSyn_IntTimeDomainIdxType        TimeDomainIdx,
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvAbstractHeaderType) FirstSubTlvPtr,
                  uint8                               SubTlvCount)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least subTlvCounter;
  uint16 currentOffsetFromFirstSubTlv = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if there are any offset time domains for the passed time domain. */
  if(EthTSyn_IsOffsetTimeDomainUsedOfTimeDomain(TimeDomainIdx) == TRUE)
  {
    /* #20 Iterate over all Sub-Tlvs. */
    for(subTlvCounter = 0u; subTlvCounter < SubTlvCount; subTlvCounter++)
    {
      /* Set current sub tlv pointer */
      /* PRQA S 0310 3 */ /* MD_EthTSyn_0310_SubType */
      ETHTSYN_CONSTP2CONST(EthTSyn_ArSubTlvAbstractHeaderType) currentSubTlvPtr =
        (ETHTSYN_P2CONST(EthTSyn_ArSubTlvAbstractHeaderType))
        &((ETHTSYN_P2CONST(uint8))FirstSubTlvPtr)[currentOffsetFromFirstSubTlv];

      currentOffsetFromFirstSubTlv += ETHTSYN_AR_SUB_TLV_ABSTRACT_HDR_LENGTH;
      currentOffsetFromFirstSubTlv += currentSubTlvPtr->Length;

      /* #30 Check if Sub-Tlv is Ofs Tlv. */
      if((currentSubTlvPtr->Type == ETHTSYN_AR_SUB_TLV_TYPE_OFS_NOT_SECURED) ||
        (currentSubTlvPtr->Type == ETHTSYN_AR_SUB_TLV_TYPE_OFS_SECURED))
      {
        /* Ofs Tlv-found */
        ETHTSYN_P2CONST(EthTSyn_ArSubTlvOfsType) ofsTlvPtr = (ETHTSYN_P2CONST(EthTSyn_ArSubTlvOfsType))currentSubTlvPtr; /* PRQA S 0310 */ /* MD_EthTSyn_0310_SubType */

        /* #40 Process the offset time domain Sub-Tlv. */
        EthTSyn_SlaveRx_ProcessOfsSubTlv(TimeDomainIdx, ofsTlvPtr);                                                    /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */

      } /* END: if(Ofs-Sub-Tlv) */
    } /* END: Iteration of Sub-Tlvs */
  } /* END: if(TimeDomain has Offset time domains) */

} /* EthTSyn_SlaveRx_HandleOfsSubTlvs() */
#  endif /* (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON) */

#  if (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_ProcessOfsSubTlv
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SlaveRx_ProcessOfsSubTlv(
                  EthTSyn_IntTimeDomainIdxType TimeDomainIdx,
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvOfsType)     OfsSubTlvPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_OffsetTimeDomainIterType ofsTimeDomainIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Search matching offset time domain by iterating all offset time domains for the TimeDomain of the FollowUp. */
  for(ofsTimeDomainIter = EthTSyn_GetOffsetTimeDomainStartIdxOfTimeDomain(TimeDomainIdx);
      ofsTimeDomainIter < EthTSyn_GetOffsetTimeDomainEndIdxOfTimeDomain(TimeDomainIdx);
      ofsTimeDomainIter++)
  {
    if(OfsSubTlvPtr->OfsTimeDomain == EthTSyn_GetIdOfOffsetTimeDomain(ofsTimeDomainIter))
    {
      /* #20 Matching Offset TimeDomain found -> Forward new offset to StbM. */
      StbM_TimeStampType timeStamp;
      StbM_UserDataType userData;
      StbM_MeasurementType measureData;
      const StbM_SynchronizedTimeBaseType synchronizedTimeBaseId =
          EthTSyn_GetSynchronizedTimeBaseIdOfOffsetTimeDomain(ofsTimeDomainIter);


      ETHTSYN_AR_SUB_TLV_STATUS_TO_TIME_BASE_STATUS(OfsSubTlvPtr->Status, timeStamp.timeBaseStatus);

      ETHTSYN_GET_UINT16(OfsSubTlvPtr->OfsTimeSec, 0u, timeStamp.secondsHi);
      ETHTSYN_GET_UINT32(OfsSubTlvPtr->OfsTimeSec, ETHTSYN_AR_SUB_TLV_OFS_TIME_SEC_SECONDS_OFFSET, timeStamp.seconds);
      ETHTSYN_GET_UINT32(OfsSubTlvPtr->OfsTimeNSec, 0u, timeStamp.nanoseconds);

      userData.userDataLength = OfsSubTlvPtr->UserDataLength;
      userData.userByte0 = OfsSubTlvPtr->UserByte0;
      userData.userByte1 = OfsSubTlvPtr->UserByte1;
      userData.userByte2 = OfsSubTlvPtr->UserByte2;

      /* Pdelay not required for Offset TimeDomains. Therefore it can be set to '0' */
      measureData.pathDelay = 0;

      (void)StbM_BusSetGlobalTime(synchronizedTimeBaseId, &timeStamp, &userData, &measureData);                        /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */

      break;
    }
  } /* END: Iteration of Offset time domains */
} /* EthTSyn_SlaveRx_ProcessOfsSubTlv() */
#  endif /* (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_GetUserDataFromSubTlv
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_GetUserDataFromSubTlv(
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvAbstractHeaderType) FirstSubTlvPtr,
                  uint8                               SubTlvCount,
    ETHTSYN_P2VAR(StbM_UserDataType)                  UserDataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 subTlvCounter;
  uint16 currentOffsetFromFirstSubTlv = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all Ar Sub-Tlvs. */
  for(subTlvCounter = 0; subTlvCounter < SubTlvCount; subTlvCounter++)
  {
    /* Set current sub tlv pointer */
    /* PRQA S 0310 3 */ /* MD_EthTSyn_0310_SubType */
    ETHTSYN_CONSTP2CONST(EthTSyn_ArSubTlvAbstractHeaderType) currentSubTlvPtr =
      (ETHTSYN_P2CONST(EthTSyn_ArSubTlvAbstractHeaderType))
      &((ETHTSYN_P2CONST(uint8))FirstSubTlvPtr)[currentOffsetFromFirstSubTlv];

    currentOffsetFromFirstSubTlv += ETHTSYN_AR_SUB_TLV_ABSTRACT_HDR_LENGTH;
    currentOffsetFromFirstSubTlv += currentSubTlvPtr->Length;

    /* #20 Check if Sub-Tlv is UserData Tlv as required. */
    if((currentSubTlvPtr->Type == ETHTSYN_AR_SUB_TLV_TYPE_USER_DATA_NOT_SECURED) ||
      (currentSubTlvPtr->Type == ETHTSYN_AR_SUB_TLV_TYPE_USER_DATA_SECURED))
    {
      /* #30 UserData Tlv-found -> store the UserData. */
      ETHTSYN_P2CONST(EthTSyn_ArSubTlvUserDataType) userDataTlvPtr =
        (ETHTSYN_P2CONST(EthTSyn_ArSubTlvUserDataType))currentSubTlvPtr; /* PRQA S 0310 */ /* MD_EthTSyn_0310_SubType */

      UserDataPtr->userDataLength = userDataTlvPtr->UserDataLength;                                                    /* SBSW_ETHTSYN_VALID_API_POINTER */
      UserDataPtr->userByte0 = userDataTlvPtr->UserByte0;                                                              /* SBSW_ETHTSYN_VALID_API_POINTER */
      UserDataPtr->userByte1 = userDataTlvPtr->UserByte1;                                                              /* SBSW_ETHTSYN_VALID_API_POINTER */
      UserDataPtr->userByte2 = userDataTlvPtr->UserByte2;                                                              /* SBSW_ETHTSYN_VALID_API_POINTER */

      retVal = E_OK;

      break; /* UserData found and retrieved -> Stop iteration of Sub-Tlvs */
    }
  }

  return retVal;
} /* EthTSyn_SlaveRx_GetUserDataFromSubTlv() */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_GetStatusFromSubTlv
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_GetStatusFromSubTlv(
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvAbstractHeaderType) FirstSubTlvPtr,
                  uint8                               SubTlvCount,
    ETHTSYN_P2VAR(StbM_TimeBaseStatusType)            StatusPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 subTlvCounter;
  uint16 currentOffsetFromFirstSubTlv = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all Ar Sub-Tlvs. */
  for(subTlvCounter = 0; subTlvCounter < SubTlvCount; subTlvCounter++)
  {
    /* Set current sub tlv pointer */
    /* PRQA S 0310 3 */ /* MD_EthTSyn_0310_SubType */
    ETHTSYN_CONSTP2CONST(EthTSyn_ArSubTlvAbstractHeaderType) currentSubTlvPtr =
      (ETHTSYN_P2CONST(EthTSyn_ArSubTlvAbstractHeaderType))
      &((ETHTSYN_P2CONST(uint8))FirstSubTlvPtr)[currentOffsetFromFirstSubTlv];

    currentOffsetFromFirstSubTlv += ETHTSYN_AR_SUB_TLV_ABSTRACT_HDR_LENGTH;
    currentOffsetFromFirstSubTlv += currentSubTlvPtr->Length;

    /* #20 Check if Sub-Tlv is Status Tlv as required. */
    if((currentSubTlvPtr->Type == ETHTSYN_AR_SUB_TLV_TYPE_STATUS_NOT_SECURED) ||
      (currentSubTlvPtr->Type == ETHTSYN_AR_SUB_TLV_TYPE_STATUS_SECURED))
    {
      /* #30 Status Tlv-found -> store the Status. */
      ETHTSYN_P2CONST(EthTSyn_ArSubTlvStatusType) statusTlvPtr =
        (ETHTSYN_P2CONST(EthTSyn_ArSubTlvStatusType))currentSubTlvPtr; /* PRQA S 0310 */ /* MD_EthTSyn_0310_SubType */

      ETHTSYN_AR_SUB_TLV_STATUS_TO_TIME_BASE_STATUS(statusTlvPtr->Status, (*StatusPtr));                               /* SBSW_ETHTSYN_VALID_API_POINTER */

      retVal = E_OK;

      break; /* Status found and retrieved -> Stop iteration of Sub-Tlvs */
    }
  }

  return retVal;
} /* EthTSyn_SlaveRx_GetStatusFromSubTlv() */
# endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_GetTimeDiffSinceSyncRx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SlaveRx_GetTimeDiffSinceSyncRx(
                  EthTSyn_IntPortIdxType       PortIdx,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) SyncIngressTimestampPtr,
    ETHTSYN_P2VAR(EthTSyn_TimediffType)        TimeDiffSinceSyncRxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  Eth_TimeStampQualType timeStampQual;
  EthTSyn_GlobalTimestampType timeStampRef; /* used as reference Timestamp when HW-Timestamping is used */
# else
  StbM_TimeStampRawType timeStampDiff; /* used to show the time passed between Sync and FollowUp reception */
  const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
  const StbM_SynchronizedTimeBaseType timeBaseId = EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(timeDomainIdx);
# endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

  /* ----- Implementation ----------------------------------------------- */
# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  /* HW-Timestamping */
  if(EthIf_GetCurrentTime(EthTSyn_Util_GetEthIfCtrlIdxOfPort(PortIdx), &timeStampQual, &timeStampRef) == E_OK)         /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
  {
    if(timeStampQual == ETH_VALID)
    {
      retVal = EthTSyn_Util_TimestampMinusTimestamp(&timeStampRef, SyncIngressTimestampPtr, TimeDiffSinceSyncRxPtr);   /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */ /* SBSW_ETHTSYN_PASSING_API_POINTER */
    }
  }
# else
  /* SW-Timestamping */
  if(StbM_GetCurrentTimeDiff(timeBaseId, SyncIngressTimestampPtr->nanoseconds, &timeStampDiff) == E_OK)                /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
  {
    *TimeDiffSinceSyncRxPtr = (EthTSyn_TimediffType)timeStampDiff;                                                     /* SBSW_ETHTSYN_VALID_API_POINTER */
    retVal = E_OK;
  }
# endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

  return retVal;
} /* EthTSyn_SlaveRx_GetTimeDiffSinceSyncRx() */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_ProvideTimeToStbm
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SlaveRx_ProvideTimeToStbm(
                  EthTSyn_IntPortIdxType    PortIdx,
                  EthTSyn_TimediffType      TimeDiffSinceSyncRx,
                  StbM_TimeBaseStatusType   TimeBaseStatus,
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) ComMsgPtr,
  ETHTSYN_P2CONST(StbM_UserDataType)        UserDataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_PdelayType pDelay;
  EthTSyn_GlobalTimestampType preciseOriginTimestamp;
  ETHTSYN_P2CONST(EthTSyn_FollowUpMsgType) followUpMsgPtr;

  /* ----- Implementation ----------------------------------------------- */
  followUpMsgPtr =
    (ETHTSYN_P2CONST(EthTSyn_FollowUpMsgType)) &((ETHTSYN_P2CONST(uint8))ComMsgPtr)[ETHTSYN_HDR_COM_LENGTH]; /* PRQA S 0310 */ /* MD_EthTSyn_0310_SubType */

  /* #10 Get the precise origin timestamp from FollowUp message */
  /* PRQA S 0310 2 */ /* MD_EthTSyn_0310_Timestamp */
  EthTSyn_NtohTimestamp(&preciseOriginTimestamp,
    (ETHTSYN_P2CONST(EthTSyn_TimestampType))followUpMsgPtr->PreciseOriginTimestampSeconds);                            /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */ /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */

  /* #20 Add the FollowUp correction field to the time difference */
  TimeDiffSinceSyncRx += (EthTSyn_TimediffType)
    ETHTSYN_GET_FOLLOW_UP_CORRECTION_VALUE_NS_FROM_MSG(ComMsgPtr->CorrectionField);

  /* #30 Add current Pdelay to the time difference */
  pDelay = EthTSyn_Pdelay_GetCurrentPdelay(PortIdx);
  TimeDiffSinceSyncRx += (EthTSyn_TimediffType)pDelay;

  /* #40 Compute the new time which should be passed to the Stbm */
  if(EthTSyn_Util_TimestampPlusTimediff(&preciseOriginTimestamp, &TimeDiffSinceSyncRx) == E_OK)                        /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
  {
    const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
    StbM_TimeStampType timeStampStbm;
    StbM_MeasurementType measureData;

    ETHTSYN_COPY_GLOBAL_TS_TO_STBM_TS_W_TBS(preciseOriginTimestamp, timeStampStbm, TimeBaseStatus);
    measureData.pathDelay = pDelay;

    /* #50 Provide new Time to the StbM */
    (void)StbM_BusSetGlobalTime(EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(timeDomainIdx),
      &timeStampStbm, UserDataPtr, &measureData);                                                                      /* SBSW_ETHTSYN_VALID_API_POINTER */ /* SBSW_ETHTSYN_PASSING_API_POINTER */
  }

} /* EthTSyn_SlaveRx_ProvideTimeToStbm() */

/**********************************************************************************************************************
 *  EthTSyn_Slave_SyncReceiveHandleFollowUpTimeout
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_SyncReceiveHandleFollowUpTimeout(
  EthTSyn_IntTimeDomainIdxType TimeDomainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_MasterPortIterType masterPortIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset state of all SyncSend state machines (Ports) of the TimeDomain. */
  for (masterPortIter = EthTSyn_GetMasterPortStartIdxOfTimeDomain(TimeDomainIdx);
       masterPortIter < EthTSyn_GetMasterPortEndIdxOfTimeDomain(TimeDomainIdx);
       masterPortIter++)
  {
    (EthTSyn_GetAddrSyncSendSm(masterPortIter))->State = ETHTSYN_S_SYNC_SEND_SM_SSS_PENDING;                           /* SBSW_ETHTSYN_CSL01 */
  }
  /* #20 Reset state of SiteSyncSync state machine */
  if((EthTSyn_GetAddrSiteSyncSyncSm(TimeDomainIdx))->State == ETHTSYN_S_SSS_SM_TX_FUP)
  {
    (EthTSyn_GetAddrSiteSyncSyncSm(TimeDomainIdx))->State = ETHTSYN_S_SSS_SM_PENDING;                                  /* SBSW_ETHTSYN_CSL01 */
  }
} /* EthTSyn_Slave_SyncReceiveHandleFollowUpTimeout() */
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_Slave_SyncReceiveHandleSyncTimeout
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
# if ((ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) && (ETHTSYN_SWT_MGMT_IS_GM_CAPABLE == STD_ON))
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_SyncReceiveHandleSyncTimeout(
                EthTSyn_IntTimeDomainIdxType TimeDomainIdx,
  ETHTSYN_P2VAR(EthTSyn_SyncReceiveSmType)   SyncReceiveSmPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_MasterPortIterType masterPortIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check for Sync receive timeout. */
  if(SyncReceiveSmPtr->Sync.SyncRxTimeoutCnt == 0u)
  {
    ETHTSYN_CONSTP2VAR(EthTSyn_SiteSyncSyncSmType) siteSyncSyncSmPtr = EthTSyn_GetAddrSiteSyncSyncSm(TimeDomainIdx);
    ETHTSYN_CONSTP2VAR(EthTSyn_TimeDomainStateType) timeDomainStatePtr = EthTSyn_GetAddrTimeDomainState(TimeDomainIdx);
    /* #20 Sync receive timeout occurred -> Take up role as master now. */
    siteSyncSyncSmPtr->State = ETHTSYN_S_SSS_SM_SYNC_TIMEOUT;                                                          /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
    SyncReceiveSmPtr->State = ETHTSYN_S_SYNC_RCV_SM_SYNC_TIMEOUT;                                                      /* SBSW_ETHTSYN_VALID_API_POINTER */
    timeDomainStatePtr->SlavePortIdx = EthTSyn_GetSizeOfSlavePort();                                                   /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
    /* #30 Initialize the SyncSendSm of each Master-Port of the TimeDomain. */
    for(masterPortIter = EthTSyn_GetMasterPortStartIdxOfTimeDomain(TimeDomainIdx);
        masterPortIter < EthTSyn_GetMasterPortEndIdxOfTimeDomain(TimeDomainIdx);
        masterPortIter++)
    {
      ETHTSYN_P2VAR(EthTSyn_SyncSendSmType) syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIter);
      syncSendSmPtr->SyncTxBuf.Index = ETHTSYN_INV_BUF_IDX;                                                            /* SBSW_ETHTSYN_CSL03 */
      syncSendSmPtr->FollowUpTxBuf.Index = ETHTSYN_INV_BUF_IDX;                                                        /* SBSW_ETHTSYN_CSL03 */
      syncSendSmPtr->TxConfirmationPending = 0;                                                                        /* SBSW_ETHTSYN_CSL03 */
      syncSendSmPtr->SequenceId = 0u;                                                                                  /* SBSW_ETHTSYN_CSL03 */
      syncSendSmPtr->LogMessageInterval = EthTSyn_GetSyncLogMsgIntervalOfMasterPort(masterPortIter);                   /* SBSW_ETHTSYN_CSL03 */
      syncSendSmPtr->TxIntervalCnt = 0u;                                                                               /* SBSW_ETHTSYN_CSL03 */

      syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_INITIALIZING;                                                      /* SBSW_ETHTSYN_CSL03 */
    }
  }

} /* EthTSyn_Slave_SyncReceiveHandleSyncTimeout() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
# endif /* ((ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) && (ETHTSYN_SWT_MGMT_IS_GM_CAPABLE == STD_ON)) */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Slave_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_Init(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SlavePortIterType slavePortIter;
  EthTSyn_SystemStateIterType systemStateIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset system state. */
  for(systemStateIter = 0u;
      systemStateIter < EthTSyn_GetSizeOfSystemState();
      systemStateIter++)
  {
    EthTSyn_SetGmPresentOfSystemState(systemStateIter, FALSE);                                                         /* SBSW_ETHTSYN_CSL01 */
  }
  /* #20 Initialize all slave ports. */
  for(slavePortIter = 0u; slavePortIter < EthTSyn_GetSizeOfSlavePort(); slavePortIter++)
  {
    EthTSyn_Slave_InitPortInternal(slavePortIter);
  }
} /* EthTSyn_Slave_Init() */

/**********************************************************************************************************************
 *  EthTSyn_Slave_InitPort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_InitPort(
  EthTSyn_IntSlavePortIdxType SlavePortIdx)
{
  EthTSyn_Slave_InitPortInternal(SlavePortIdx);
} /* EthTSyn_Slave_InitPort() */

/**********************************************************************************************************************
 *  EthTSyn_Slave_HandleCyclicTasks
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
FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_HandleCyclicTasks(
  EthTSyn_TimeDomainIterType TimeDomainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SlavePortIterType slavePortIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all Slave-Ports of the given TimeDomain */
  for(slavePortIter = EthTSyn_GetSlavePortStartIdxOfTimeDomain(TimeDomainIdx);
      slavePortIter < EthTSyn_GetSlavePortEndIdxOfTimeDomain(TimeDomainIdx);
      slavePortIter++)
  {
    EthTSyn_SyncReceiveSmPtrType syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(slavePortIter);

    ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #20 Handle announce receive state machine timeouts if applicable. */
# if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
    if(EthTSyn_IsAnnounceInfoUsedOfSlavePort(slavePortIter) == TRUE)
    {
      const EthTSyn_AnnounceInfoIdxOfSlavePortType announceInfoIdx =
          EthTSyn_GetAnnounceInfoIdxOfSlavePort(slavePortIter);
      EthTSyn_AnnounceReceiveSmPtrType announceReceiveSmPtr = EthTSyn_GetAddrAnnounceReceiveSm(announceInfoIdx);
      if(announceReceiveSmPtr->RxTimeoutCnt > 0)
      {
        (announceReceiveSmPtr->RxTimeoutCnt)--;                                                                        /* SBSW_ETHTSYN_CSL03 */
      }
      /* #200 Process announce receive state machine */
      EthTSyn_Slave_ProcessSmAnnounceReceive(slavePortIter);
    }
# endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */

    /* #30 Handle sync receive state machine timeouts */
    if(syncReceiveSmPtr->FollowUp.FollowUpRxTimeoutCnt > 0)
    {
      syncReceiveSmPtr->FollowUp.FollowUpRxTimeoutCnt--;                                                               /* SBSW_ETHTSYN_CSL01 */
    }

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
    if(syncReceiveSmPtr->Sync.SyncRxTimeoutCnt > 0)
    {
      syncReceiveSmPtr->Sync.SyncRxTimeoutCnt--;                                                                       /* SBSW_ETHTSYN_CSL01 */
    }
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

    ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #40 Process sync receive state machine. */
    EthTSyn_Slave_ProcessSmSyncReceive(slavePortIter);
  } /* END: Iteration Slave Ports */
} /* EthTSyn_Slave_HandleCyclicTasks() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_ProcRcvdSyncMsg
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
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
FUNC(void, ETHTSYN_CODE) EthTSyn_SlaveRx_ProcRcvdSyncMsg(
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) ComMsgPtr,
                  EthTSyn_IntPortIdxType    PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
  /* Get Sync receive state machine Pointer */
  ETHTSYN_CONSTP2VAR(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(slavePortIdx);
#  if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF)
  const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
  const StbM_SynchronizedTimeBaseType timeBaseId = EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(timeDomainIdx);
#  endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if port is able to receive the sync message. */
  if(EthTSyn_SlaveRx_IsPortReadyToReceiveSync(PortIdx) == TRUE)                                                        /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
  {
    /* #20 Get sync ingress timestamp. */
#  if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
    /* HW-Timestamping */
    {
      Eth_TimestampQualityType timestampQuality;
      syncReceiveSmPtr->Sync.IngressTimestampMgmt.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_NOT_AVAILABLE;    /* SBSW_ETHTSYN_CSL02_03 */

      /* PRQA S 0310, 0311 2 */ /* MD_EthTSyn_0310_MsgStructRev, MD_EthTSyn_0311 */
      if(EthIf_GetIngressTimestamp(
        EthTSyn_Util_GetEthIfCtrlIdxOfPort(PortIdx), (ETHTSYN_P2VAR(Eth_DataType))ComMsgPtr,
        &syncReceiveSmPtr->Sync.IngressTimestampMgmt.Timestamp, &timestampQuality) == E_OK)                            /* SBSW_ETHTSYN_PASSING_API_POINTER */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */ /* SBSW_ETHTSYN_CSL02_03 */
      {
        if(timestampQuality == ETH_VALID)
        {
          syncReceiveSmPtr->Sync.IngressTimestampMgmt.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_AVAILABLE;    /* SBSW_ETHTSYN_CSL02_03 */
        }
      }
    }
#  else
    /* SW-Timestamping */
    if(StbM_GetCurrentTimeRaw(timeBaseId, &syncReceiveSmPtr->Sync.IngressTimestampMgmt.Timestamp.nanoseconds) == E_OK) /* SBSW_ETHTSYN_CSL02_03 */
    {
      syncReceiveSmPtr->Sync.IngressTimestampMgmt.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_AVAILABLE;        /* SBSW_ETHTSYN_CSL02_03 */
    }
    else
    {
      syncReceiveSmPtr->Sync.IngressTimestampMgmt.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_NOT_AVAILABLE;    /* SBSW_ETHTSYN_CSL02_03 */
    }
#  endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

    ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #30 Ensure that Sync ingress timestamp is available. */
    if(syncReceiveSmPtr->Sync.IngressTimestampMgmt.State == ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_AVAILABLE)
    {
      /* #40 Ingress timestamp available -> store required message attributes for later processing. */
      /* Set Sync message attributes */
      syncReceiveSmPtr->Sync.LogMessageInterval = ComMsgPtr->LogMessageInterval;                                       /* SBSW_ETHTSYN_CSL02_03 */

      EthTSyn_SetClockIdentity(syncReceiveSmPtr->Sync.SourcePortIdentity.ClockIdentity,
          ComMsgPtr->SourceClockIdentity);                                                                             /* SBSW_ETHTSYN_CSL02_03 */ /* SBSW_ETHTSYN_PASSING_API_POINTER */

      syncReceiveSmPtr->Sync.SourcePortIdentity.PortNumber =
          (EthTSyn_PortNumberType)EthTSyn_Ntohs(ComMsgPtr->SourcePortNumber);                                          /* SBSW_ETHTSYN_CSL02_03 */

      syncReceiveSmPtr->Sync.SequenceId = (uint16)EthTSyn_Ntohs(ComMsgPtr->SequenceId);                                /* SBSW_ETHTSYN_CSL02_03 */

      /*#50 Set FollowUp receive timeout if required. */
      if(EthTSyn_GetFollowUpAlloweRxDelayOfSlavePort(slavePortIdx) > 0u)
      {
        syncReceiveSmPtr->FollowUp.FollowUpRxTimeoutCnt = EthTSyn_GetFollowUpAlloweRxDelayOfSlavePort(slavePortIdx);   /* SBSW_ETHTSYN_CSL02_03 */
      }

      /* #60 Change state of sync receive sm to waiting for FollowUp. */
      syncReceiveSmPtr->State = ETHTSYN_S_SYNC_RCV_SM_WAIT_FUP;                                                        /* SBSW_ETHTSYN_CSL02_03 */
    }
    else
    {
      /* #70 Ingress timestamp is not available -> change state of sync receive sm to DISCARD. */
      syncReceiveSmPtr->State = ETHTSYN_S_SYNC_RCV_SM_DISCARD;                                                         /* SBSW_ETHTSYN_CSL02_03 */
    }

    ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
  else
  {
    /* #80 Port is not ready to receive sync message -> change state of sync receive sm to DISCARD. */
    syncReceiveSmPtr->State = ETHTSYN_S_SYNC_RCV_SM_DISCARD;                                                           /* SBSW_ETHTSYN_CSL02_03 */
  }

} /* EthTSyn_SlaveRx_ProcRcvdSyncMsg() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

/**********************************************************************************************************************
 *  EthTSyn_SlaveRx_ProcRcvdFupMsg
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
FUNC(void, ETHTSYN_CODE) EthTSyn_SlaveRx_ProcRcvdFupMsg(
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) ComMsgPtr,
                  EthTSyn_IntPortIdxType    PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean processMsg = FALSE;

  /* ----- Implementation ----------------------------------------------- */
# if (ETHTSYN_MASTER_SUPPORT == STD_ON)
  /* #10 Check that Rx-Port is Slave Port */
  if(EthTSyn_IsSlavePortUsedOfPort(PortIdx) == TRUE) /* This check is always TRUE when Master support is disabled. */
# endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */
  {
    const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
    ETHTSYN_CONSTP2VAR(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(slavePortIdx);

    /* #20 Check sync receive state machine state and matching sequence id */
    if((syncReceiveSmPtr->State == ETHTSYN_S_SYNC_RCV_SM_WAIT_FUP) && /* PRQA S 3415 */ /* MD_EthTSyn_3415_ReadOnly */
        (syncReceiveSmPtr->Sync.SequenceId == (uint16)EthTSyn_Ntohs(ComMsgPtr->SequenceId)))
    {
      /* Waiting for FollowUp + matching Sequence Id -> continue message processing */

      /* #30 Check for matching source port identity */
      /* PRQA S 0310 3 */ /* MD_EthTSyn_0310_PortIdent */
      if(EthTSyn_PortIdentityIsEqual(
          (ETHTSYN_P2CONST(EthTSyn_PortIdentityType))&syncReceiveSmPtr->Sync.SourcePortIdentity,
          (ETHTSYN_P2CONST(EthTSyn_PortIdentityType))ComMsgPtr->SourceClockIdentity) == TRUE)                          /* SBSW_ETHTSYN_CSL03 */ /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
      {
        processMsg = TRUE;
      }
    }

    /* #40 Check if message should be processed */
    if(processMsg == TRUE)
    {
      EthTSyn_TimediffType timeDiff = 0;
      StbM_TimeBaseStatusType status = 0;
# if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
      StbM_UserDataType userData;
      ETHTSYN_P2VAR(StbM_UserDataType) userDataPtr = &userData;
# else
      ETHTSYN_P2VAR(StbM_UserDataType) userDataPtr = NULL_PTR;
# endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */

# if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
      /* #50 Check for Ar Tlvs */
      if(EthTSyn_SlaveRx_HandleArFollowUpTlvs(PortIdx, ComMsgPtr, &status, &userDataPtr) == E_OK)                      /* SBSW_ETHTSYN_PASSING_API_POINTER */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
# endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */
      {
        /* #60 Provide time information to StbM. */
        if(EthTSyn_SlaveRx_GetTimeDiffSinceSyncRx(PortIdx, &syncReceiveSmPtr->Sync.IngressTimestampMgmt.Timestamp,
            &timeDiff) == E_OK)                                                                                        /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
        {
          EthTSyn_SlaveRx_ProvideTimeToStbm(PortIdx, timeDiff, status, ComMsgPtr, userDataPtr);                        /* SBSW_ETHTSYN_PASSING_API_POINTER */ /* SBSW_ETHTSYN_POINTER_VARIABLE */
        }
        syncReceiveSmPtr->State = ETHTSYN_S_SYNC_RCV_SM_WAIT_SYNC;                                                     /* SBSW_ETHTSYN_CSL03 */
      }
    } /* END: if(processMsg == TRUE) */
  } /* END: if(Slave-Port) */

} /* EthTSyn_SlaveRx_ProcRcvdFupMsg() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

# if ( (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) && (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) )
/**********************************************************************************************************************
 *  EthTSyn_Slave_ProcRcvdAnnounceMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_ProcRcvdAnnounceMsg(
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) ComMsgPtr, EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_IntTimeDomainIdxType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if announce message can be received on the Port. */
  if(EthTSyn_UtilRx_IsPortReadyToReceiveAnnounce(PortIdx) == TRUE)
  {
    ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    /* #20 Validated the Announce Message. */
    if(EthTSyn_UtilRx_QualifyAnnounceMsg(PortIdx, ComMsgPtr) == E_OK)                                                  /* SBSW_ETHTSYN_PASSING_API_POINTER */
    {
      const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
      const EthTSyn_AnnounceInfoIdxOfSlavePortType announceInfoIdx =
        EthTSyn_GetAnnounceInfoIdxOfSlavePort(slavePortIdx);
      ETHTSYN_CONSTP2VAR(EthTSyn_AnnounceReceiveSmType) announceReceiveSmPtr =
        EthTSyn_GetAddrAnnounceReceiveSm(announceInfoIdx);
      ETHTSYN_CONSTP2CONST(EthTSyn_AnnounceMsgType) announceMsgPtr =
        (ETHTSYN_P2CONST(EthTSyn_AnnounceMsgType))&((ETHTSYN_P2CONST(uint8))ComMsgPtr)[ETHTSYN_HDR_COM_LENGTH]; /* PRQA S 0310 */ /* MD_EthTSyn_0310_SubType */

      /* Reset announce timeout */
      announceReceiveSmPtr->RxTimeoutCnt = EthTSyn_GetAnnounceAllowedRxDelayOfAnnounceInfo(announceInfoIdx);           /* SBSW_ETHTSYN_CSL02_03 */

      /* #30 Set new Grandmaster if applicable. */
      if(EthTSyn_IsGmPresentOfSystemState(timeDomainIdx) == FALSE)
      {
        EthTSyn_Slave_SetMasterPriorityVector(announceMsgPtr, timeDomainIdx);                                          /* SBSW_ETHTSYN_POINTER_VARIABLE */
      }
    }
    ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }

} /* EthTSyn_Slave_ProcRcvdAnnounceMsg() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
# endif /* ( (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) && (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) ) */

/**********************************************************************************************************************
 *  EthTSyn_EndStation_Slave_ProcRcvdSyncMsg
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
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
FUNC(void, ETHTSYN_CODE) EthTSyn_EndStation_Slave_ProcRcvdSyncMsg(
                  EthTSyn_IntPortIdxType           PortIdx,
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType)        ComMsgHdrPtr,
  ETHTSYN_P2CONST(EthTSyn_SwtMgmt_RxFrameInfoType) RxFrameInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) SyncIngressTimestampPtr = &RxFrameInfoPtr->IngressTimestamp;
  uint8 errorId = ETHTSYN_E_NO_ERROR;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check for min/correct Sync message length. */
  if(ETHTSYN_MSG_SYNC_LENGTH == EthTSyn_Ntohs(ComMsgHdrPtr->MessageLength))
  {
    if(EthTSyn_IsSlavePortUsedOfPort(PortIdx) == TRUE)
    {
      const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
      ETHTSYN_CONSTP2VAR(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(slavePortIdx);
      ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

      /* #20 Verify sync receive state machine state. */
      if( (syncReceiveSmPtr->State == ETHTSYN_S_SYNC_RCV_SM_DISCARD) ||
        (syncReceiveSmPtr->State == ETHTSYN_S_SYNC_RCV_SM_WAIT_SYNC) )
      {
        /* #30 Store the current ingress timestamp. */
#  if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
        /* HW-Timestamping */
        syncReceiveSmPtr->Sync.IngressTimestampMgmt.Timestamp = *SyncIngressTimestampPtr;                              /* SBSW_ETHTSYN_CSL02_03 */
#  else
        /* SW-Timestamping */
        syncReceiveSmPtr->Sync.IngressTimestampMgmt.Timestamp.nanoseconds = SyncIngressTimestampPtr->nanoseconds;      /* SBSW_ETHTSYN_CSL02_03 */
#  endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */
        syncReceiveSmPtr->Sync.IngressTimestampMgmt.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_AVAILABLE;      /* SBSW_ETHTSYN_CSL02_03 */

        /* #40 Set Sync message attributes in sync receive state machine. */
        syncReceiveSmPtr->Sync.LogMessageInterval = ComMsgHdrPtr->LogMessageInterval;                                  /* SBSW_ETHTSYN_CSL02_03 */

        EthTSyn_SetClockIdentity(syncReceiveSmPtr->Sync.SourcePortIdentity.ClockIdentity,
          ComMsgHdrPtr->SourceClockIdentity);                                                                          /* SBSW_ETHTSYN_CSL02_03 */ /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
        syncReceiveSmPtr->Sync.SourcePortIdentity.PortNumber =
          (uint16)EthTSyn_Ntohs(ComMsgHdrPtr->SourcePortNumber);                                                       /* SBSW_ETHTSYN_CSL02_03 */

        /* store sequence id */
        syncReceiveSmPtr->Sync.SequenceId = (uint16)EthTSyn_Ntohs(ComMsgHdrPtr->SequenceId);                           /* SBSW_ETHTSYN_CSL02_03 */

        /* set FollowUp receive timeout time */
        syncReceiveSmPtr->FollowUp.FollowUpRxTimeoutCnt = EthTSyn_GetFollowUpAlloweRxDelayOfSlavePort(slavePortIdx);   /* SBSW_ETHTSYN_CSL02_03 */

        /* #50 Change state to waiting for FollowUp. */
        syncReceiveSmPtr->State = ETHTSYN_S_SYNC_RCV_SM_WAIT_FUP;                                                      /* SBSW_ETHTSYN_CSL02_03 */
      }
      ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    }
  }
  else
  {
    errorId = ETHTSYN_E_MSG_LENGTH;
  }

  /* ----- Development Error Report ------------------------------------- */
#  if (ETHTSYN_DEV_ERROR_REPORT == STD_ON)
  /* #60 Report error to default error tracer (DET) if any occurred. */
  if(errorId != ETHTSYN_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID, ETHTSYN_SID_RX_INDICATION, errorId);
  }
#  else
  ETHTSYN_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#  endif /*  */
} /* EthTSyn_EndStation_Slave_ProcRcvdSyncMsg() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

# if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Slave_SetMasterPriorityVector
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_SetMasterPriorityVector(
  ETHTSYN_P2CONST(EthTSyn_AnnounceMsgType)     AnnounceMsgPtr,
                  EthTSyn_IntTimeDomainIdxType TimeDomainIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  EthTSyn_SetGmClockIdentityOfSystemState(TimeDomainIdx,                                                               /* SBSW_ETHTSYN_API_ARGUMENT_IDX */ /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
    EthTSyn_Util_TransformClockIdentityToUint64(AnnounceMsgPtr->ClockIdentity));
  EthTSyn_SetGmPresentOfSystemState(TimeDomainIdx, TRUE);                                                              /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
} /* EthTSyn_Slave_SetMasterPriorityVector() */

/**********************************************************************************************************************
 *  EthTSyn_Slave_ResetMasterPriorityVector
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Slave_ResetMasterPriorityVector(
  EthTSyn_IntTimeDomainIdxType TimeDomainIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  EthTSyn_SetGmClockIdentityOfSystemState(TimeDomainIdx, 0);                                                           /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
  EthTSyn_SetGmPresentOfSystemState(TimeDomainIdx, FALSE);                                                             /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
} /* EthTSyn_Slave_ResetMasterPriorityVector() */
# endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */


# define ETHTSYN_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */

/* Justification for module-specific MISRA deviations:
 * see file EthTSyn.c
*/
/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Slave_Int.c
 *********************************************************************************************************************/
