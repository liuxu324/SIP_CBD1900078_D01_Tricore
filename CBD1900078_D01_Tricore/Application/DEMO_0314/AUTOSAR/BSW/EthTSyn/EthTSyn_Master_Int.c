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
/**        \file  EthTSyn_Master_Int.c
 *        \brief  EthTSyn Master source file - Internal Functions
 *
 *      \details  EthTSyn Master source file containing the EthTSyn Master implementation of the EthTSyn module.
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

#define ETHTSYN_MASTER_INT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EthTSyn_Master_Int.h" /* PRQA S 0883, 3219, 0810 */ /* MD_EthTSyn_0883, MD_EthTSyn_3219, MD_MSR_1.1_810 */

#if (ETHTSYN_MASTER_SUPPORT == STD_ON)
# include "EthTSyn_Int.h" /* PRQA S 3219 */ /* MD_EthTSyn_3219 */
# include "EthTSyn_Crc_Int.h"

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
#  if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
#   include "EthTSyn_SwtTimeSync_Int.h" /* PRQA S 0777 */ /* MD_MSR_5.1_777 */
#  endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of EthTSyn header file */
# if (  (ETHTSYN_SW_MAJOR_VERSION != (7u)) \
     || (ETHTSYN_SW_MINOR_VERSION != (0u)) \
     || (ETHTSYN_SW_PATCH_VERSION != (0u)) )
#  error "Vendor specific version numbers of EthTSyn_Master_Int.c and EthTSyn.h are inconsistent"
# endif

/* Check the version of the configuration header file */
# if (  (ETHTSYN_CFG_MAJOR_VERSION != (7u)) \
     || (ETHTSYN_CFG_MINOR_VERSION != (0u)) )
#  error "Version numbers of EthTSyn_Master_Int.c and EthTSyn_Cfg.h are inconsistent!"
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
 *  EthTSyn_Master_InitPortInternal
 *********************************************************************************************************************/
/*! \brief      Initializes the passed Master port.
 *  \details    Initializes all component variables directly related to the passed EthTSyn Master Port.
 *  \param[in]  MasterPortIdx   Index of the Master port
 *                              [range: MasterPortIdx < EthTSyn_GetSizeOfMasterPort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_InitPortInternal(
  EthTSyn_MasterPortIterType MasterPortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Master_IsImmediateTimeSyncRequired
 *********************************************************************************************************************/
/*! \brief      Checks if the an immediate time sync should be triggered for the given time domain.
 *  \details    Checks if immediate time sync feature is enabled for the passed time domain and if so, checks if an
 *              immediate time sync is required according to SynchronizedTimeBaseStatus and TimeBaseUpdateCounter
 *              (both retrieved from StbM).
 *  \param[in]  TimeDomainIdx   Index of the TimeDomain
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \return     TRUE - Trigger immediate time sync
 *  \return     FALSE - Do not trigger immediate time sync
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Master_IsImmediateTimeSyncRequired(
  EthTSyn_TimeDomainIterType TimeDomainIdx);

/**********************************************************************************************************************
 *  EthTSyn_Master_IsGlobalTimeBaseStatusBit
 *********************************************************************************************************************/
/*! \brief      Checks if the GLOBAL_TIME_BASE status bit of the StbM_TimeBaseStatus is set for the passed time domain.
 *  \details    -
 *  \param[in]  TimeDomainIdx   Index of the TimeDomain
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \return     TRUE - GLOBAL_TIME_BASE status bit is set
 *  \return     FALSE - GLOBAL_TIME_BASE status bit is not set
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Master_IsGlobalTimeBaseStatusBit(
  EthTSyn_TimeDomainIterType TimeDomainIdx);

/**********************************************************************************************************************
 *  EthTSyn_Master_HasTimeBaseUpdateCounterChanged
 *********************************************************************************************************************/
/*! \brief      Check if the time base update counter has changed since last check for the passed time domain.
 *  \details    -
 *  \param[in]  TimeDomainIdx   Index of the TimeDomain
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \return     TRUE - Time base update counter has changed since last check
 *  \return     FALSE - Time base update counter has not changed since last check
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Master_HasTimeBaseUpdateCounterChanged(
  EthTSyn_TimeDomainIterType TimeDomainIdx);

/**********************************************************************************************************************
 *  EthTSyn_MasterTx_TxSyncMsg
 *********************************************************************************************************************/
/*! \brief      Transmits a Sync message on the passed Port.
 *  \details    Gets an Ethernet TxBuffer, copies the Sync message to the buffer, triggers the transmission and handles
 *              the timestamping.
 *  \param[in]  PortIdx         Index of the port that should transmit the message
 *                              [range: PortIdx = EthTSyn_GetSizeOfPort()]
 *  \return     E_OK - Message transmission was successful
 *  \return     E_NOT_OK - Message transmission was not successful
 *  \pre        Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \pre        Port has to be AsCapable (EthTSyn_Util_IsAsCapable()) and tx ready (EthTSyn_IsTxReady())
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *  \note       In case of any error, the possibly locked TxBuffer is released by this function
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_MasterTx_TxSyncMsg(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_MasterTx_TxFollowUpMsg
 *********************************************************************************************************************/
/*! \brief      Transmits a FollowUp message on the passed Port.
 *  \details    Gets an Ethernet TxBuffer, copies the FollowUp message to the buffer and triggers the transmission.
 *  \param[in]  PortIdx         Index of the port that should transmit the message
 *                              [range: PortIdx = EthTSyn_GetSizeOfPort()]
 *  \return     E_OK - Message transmission was successful
 *  \return     E_NOT_OK - Message transmission was not successful
 *  \pre        Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \pre        Port has to be AsCapable (EthTSyn_Util_IsAsCapable()) and tx ready (EthTSyn_IsTxReady())
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *  \note       In case of any error, the possibly locked TxBuffer is released by this function
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_MasterTx_TxFollowUpMsg(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_MasterTx_IsFollowUpTxReady
 *********************************************************************************************************************/
/*! \brief      Checks if FollowUp message is ready for transmission on the given master Port.
 *  \details    -
 *  \param[in]  PortIdx      Index of the port
 *                           [range: PortIdx = EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - FollowUp message is ready for transmission
 *  \return     FALSE - FollowUp message is not ready for transmission
 *  \pre        Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_MasterTx_IsFollowUpTxReady(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_MasterTx_CopyFollowUpToTxBuffer
 *********************************************************************************************************************/
/*! \brief      Copies a FollowUp message to the provided TxBuffer.
 *  \details    Assembles the FollowUp message for the given Port and copies it to the provided TxBuffer in
 *              Network-Byte-Order.
 *  \param[in]  PortIdx         Index of the port
 *                              [range: PortIdx = EthTSyn_GetSizeOfPort()]
 *  \param[out] TxBufPtr        The Assembled FollowUp message in network byte order
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TxBuffers
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_MasterTx_CopyFollowUpToTxBuffer(
                EthTSyn_IntPortIdxType  PortIdx,
  ETHTSYN_P2VAR(uint8)                  TxBufPtr);

# if (ETHTSYN_ANNOUNCE_TX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Master_TxAnnounceMsg
 *********************************************************************************************************************/
/*! \brief      Transmits an Announce message.
 *  \details    Transmits an Announce message on the passed port. This includes getting a TxBuffer.
 *  \param[in]  PortIdx         Index of the port that should transmit the message
 *                              [range: PortIdx = EthTSyn_GetSizeOfPort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *  \note       In case of any error, the possibly locked TxBuffer is released by this function
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_TxAnnounceMsg(
  EthTSyn_IntPortIdxType PortIdx);
# endif /* (ETHTSYN_ANNOUNCE_TX_SUPPORT == STD_ON) */

# if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
/**********************************************************************************************************************
 *  MASTER TX AUTOSAR TLVS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_MasterTx_AppendArFollowUpTlvs
 *********************************************************************************************************************/
/*! \brief         Appends FollowUp AUTOSAR Tlvs.
 *  \details       Appends the optional AUTSAR (Sub)-Tlvs to an already assembled FollowUp message.
 *  \param[in]     PortIdx   Index of the port the FollowUp is transmitted on
 *                           [range: PortIdx = EthTSyn_GetSizeOfPort()]
 *  \param[in,out] TxBufPtr  In:  The assembled FollowUp message in Network-Byte-Order
 *                           Out: The appended FollowUp Ar Tlvs in Network-Byte-Order
 *  \pre           The FollowUp message was already copied to the provided TxBuffer in Network-Byte-Order
 *  \pre           Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different TxBuffers
 *********************************************************************************************************************/
/* AR4.3 message format */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_MasterTx_AppendArFollowUpTlvs(
                  EthTSyn_IntPortIdxType  PortIdx,
    ETHTSYN_P2VAR(uint8)                  TxBufPtr);

/**********************************************************************************************************************
 *  EthTSyn_MasterTx_AppendArFollowUpTimeTlv
 *********************************************************************************************************************/
/*! \brief         Appends FollowUp AUTOSAR Time TLV.
 *  \details       Appends the option AUTOSAR Sub-Tlv TimeSecured to an already assembled FollowUp message.
 *  \param[in]     PortIdx         Index of the port the FollowUp is transmitted on
 *                                 [range: PortIdx = EthTSyn_GetSizeOfPort()]
 *  \param[in]     DataId          DataId used for Crc calculation
 *  \param[in]     ComMsgPtr       Pointer to the common message header of the FollowUp message
 *  \param[out]    BufferPtr       Pointer to the Tx buffer where the Tlv should be appended
 *  \param[in,out] OffsetPtr       In:  Offset in the given buffer where to store the Tlv
 *                                 Out: New offset which has to be used for the next Tlv
 *  \pre           The FollowUp message was already copied to the provided TxBuffer in Network-Byte-Order
 *  \pre           Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different TxBuffers
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_MasterTx_AppendArFollowUpTimeTlv(
                    EthTSyn_IntPortIdxType        PortIdx,
                    uint8                         DataId,
    ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType)     ComMsgPtr,
      ETHTSYN_P2VAR(uint8)                        BufferPtr,
      ETHTSYN_P2VAR(uint16)                       OffsetPtr); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/**********************************************************************************************************************
 *  EthTSyn_MasterTx_AppendArFollowUpStatusTlv
 *********************************************************************************************************************/
/*! \brief         Appends FollowUp AUTOSAR Status TLV.
 *  \details       Appends the optional AUTOSAR Sub-Tlv Status (Secured) to an already assembled FollowUp message.
 *  \param[in]     PortIdx         Index of the port the FollowUp is transmitted on
 *                                 [range: PortIdx = EthTSyn_GetSizeOfPort()]
 *  \param[in]     DataId          DataId used for Crc calculation
 *  \param[out]    BufferPtr       Pointer to the Tx buffer where the Tlv should be appended
 *  \param[in,out] OffsetPtr       In:  Offset in the given buffer where to store the Tlv
 *                                 Out: New offset which has to be used for the next Tlv
 *  \pre           Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different TxBuffers
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_MasterTx_AppendArFollowUpStatusTlv(
                  EthTSyn_IntPortIdxType  PortIdx,
                  uint8                   DataId,
    ETHTSYN_P2VAR(uint8)                  BufferPtr,
    ETHTSYN_P2VAR(uint16)                 OffsetPtr); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/**********************************************************************************************************************
 *  EthTSyn_MasterTx_AppendArFollowUpUserDataTlv
 *********************************************************************************************************************/
/*! \brief         Appends FollowUp AUTOSAR UserData TLV.
 *  \details       Append the optional AUTOSAR Sub-Tlv UserData (Secured) to an already assembled FollowUp message.
 *  \param[in]     PortIdx        Index of the port the FollowUp is transmitted on
 *                                [range: PortIdx = EthTSyn_GetSizeOfPort()]
 *  \param[in]     DataId         DataId used for Crc calculation
 *  \param[out]    BufferPtr      Pointer to the Tx buffer where the Tlv should be appended
 *  \param[in,out] OffsetPtr      In:  Offset in the given buffer where to store the Tlv
 *                                Out: New offset which has to be used for the next Tlv
 *  \pre           Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different TxBuffers
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_MasterTx_AppendArFollowUpUserDataTlv(
                  EthTSyn_IntPortIdxType  PortIdx,
                  uint8                   DataId,
    ETHTSYN_P2VAR(uint8)                  BufferPtr,
    ETHTSYN_P2VAR(uint16)                 OffsetPtr); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

#  if (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_MasterTx_AppendArFollowUpOfsTlvs
 *********************************************************************************************************************/
/*! \brief         Appends FollowUp AUTOSAR Ofs TLVs.
 *  \details       Appends the optional AUTOSAR Sub-Tlv(s) Ofs (Secured) to an already assembled FollowUp message.
 *  \param[in]     PortIdx        Index of the port the FollowUp is transmitted on
 *                                [range: PortIdx = EthTSyn_GetSizeOfPort()]
 *  \param[in]     DataId         DataId used for Crc calculation
 *  \param[out]    BufferPtr      Pointer to the Tx buffer where the Tlv should be appended
 *  \param[in,out] OffsetPtr      In:  Offset in the given buffer where to store the Tlv
 *                                Out: New offset which has to be used for the next Tlv
 *  \pre           Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different TxBuffers
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_MasterTx_AppendArFollowUpOfsTlvs(
                  EthTSyn_IntPortIdxType  PortIdx,
                  uint8                   DataId,
    ETHTSYN_P2VAR(uint8)                  BufferPtr,
    ETHTSYN_P2VAR(uint16)                 OffsetPtr); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#  endif /* (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  END: MASTER TX AUTOSAR TLVS
 *********************************************************************************************************************/
# endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */

/**********************************************************************************************************************
 *  EthTSyn_Master_SyncSendSm_SendSync
 *********************************************************************************************************************/
/*! \brief      Handles the Sync message transmission of the sync send state machine (triggered by
 *              EthTSyn_Master_ProcessSmSyncSend() ).
 *  \details    Triggers the (immediate) sync message transmission and handles the state machine accordingly.
 *  \param[in]  PortIdx          Index of the master port, the sync message should be transmitted on
 *                               [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  IsImmediateSync  Indicating if the sync is an immediate sync
 *  \pre        Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices.
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_SyncSendSm_SendSync(
  EthTSyn_IntPortIdxType  PortIdx,
  boolean                 IsImmediateSync);

/**********************************************************************************************************************
 *  EthTSyn_Master_SyncSendSm_SendFup
 *********************************************************************************************************************/
/*! \brief      Handles the FollowUp message transmission of the sync send state machine (triggered by
 *              EthTSyn_Master_ProcessSmSyncSend() ).
 *  \details    Triggers the FollowUp message transmission, as well as the optional transmission of an Announce message,
 *              and handles the state machine accordingly.
 *  \param[in]  PortIdx    Index of the master port, the follow up message should be transmitted on
 *                         [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre        Constraint for PortIdx: EthTSyn_IsMasterPortUsedOfPort() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices.
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_SyncSendSm_SendFup(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Master_InitPortInternal
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_InitPortInternal(
  EthTSyn_MasterPortIterType MasterPortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_CONSTP2VAR(EthTSyn_SyncSendSmType) syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(MasterPortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set sync send state machine values. */
  syncSendSmPtr->SyncTxBuf.Index = ETHTSYN_INV_BUF_IDX;                                                                /* SBSW_ETHTSYN_CSL01 */
  syncSendSmPtr->FollowUpTxBuf.Index = ETHTSYN_INV_BUF_IDX;                                                            /* SBSW_ETHTSYN_CSL01 */
  syncSendSmPtr->TxConfirmationPending = 0;                                                                            /* SBSW_ETHTSYN_CSL01 */

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
  /* Bridge */
  {
    const EthTSyn_PortIdxOfMasterPortType portIdx = EthTSyn_GetPortIdxOfMasterPort(MasterPortIdx);
    const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(portIdx);
    if(EthTSyn_IsSlavePortUsedOfTimeDomain(timeDomainIdx) == TRUE)
    {
      syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_SSS_PENDING;                                                       /* SBSW_ETHTSYN_CSL01 */
    }
    else
    {
      if(EthTSyn_Util_IsSwitchPort(portIdx) == TRUE)
      {
        /* Switch Port -> Initialize sync send state machine. */
        syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_INITIALIZING;                                                    /* SBSW_ETHTSYN_CSL01 */
        syncSendSmPtr->SequenceId = 0u;                                                                                /* SBSW_ETHTSYN_CSL01 */
        syncSendSmPtr->TxIntervalCnt = 0u;                                                                             /* SBSW_ETHTSYN_CSL01 */
        syncSendSmPtr->LogMessageInterval = EthTSyn_GetSyncLogMsgIntervalOfMasterPort(MasterPortIdx);                  /* SBSW_ETHTSYN_CSL01 */
      }
      else
      {
        /* End-Station Port -> Disable sync send state machine by setting the state to 'DISABLED'. */
        syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_DISABLED;                                                        /* SBSW_ETHTSYN_CSL01 */
      }
    }
  }
# else
  /* End-Station */
  syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_INITIALIZING;                                                          /* SBSW_ETHTSYN_CSL01 */
  syncSendSmPtr->SequenceId = 0u;                                                                                      /* SBSW_ETHTSYN_CSL01 */
  syncSendSmPtr->TxIntervalCnt = 0u;                                                                                   /* SBSW_ETHTSYN_CSL01 */
  syncSendSmPtr->LogMessageInterval = EthTSyn_GetSyncLogMsgIntervalOfMasterPort(MasterPortIdx);                        /* SBSW_ETHTSYN_CSL01 */
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

} /* EthTSyn_Master_InitPortInternal() */

/**********************************************************************************************************************
 *  EthTSyn_Master_IsImmediateTimeSyncRequired
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Master_IsImmediateTimeSyncRequired(
  EthTSyn_TimeDomainIterType TimeDomainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean triggerImmediateTimeSync = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if immediate time sync is activated for the time domain. */
  if(EthTSyn_IsImmediateTimeSyncOfTimeDomain(TimeDomainIdx) == TRUE)
  {
    /* #20 Check global time base status bit. */
    if(EthTSyn_Master_IsGlobalTimeBaseStatusBit(TimeDomainIdx) == TRUE)
    {
      /* #30 Check if time base update counter has changed. */
      triggerImmediateTimeSync = EthTSyn_Master_HasTimeBaseUpdateCounterChanged(TimeDomainIdx);
    }
  }

  return triggerImmediateTimeSync;
} /* EthTSyn_Master_IsImmediateTimeSyncRequired() */

/**********************************************************************************************************************
 *  EthTSyn_Master_IsGlobalTimeBaseStatusBit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Master_IsGlobalTimeBaseStatusBit(
  EthTSyn_TimeDomainIterType TimeDomainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isGlobalTimeBase = FALSE;
  const StbM_SynchronizedTimeBaseType timeBaseId = EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(TimeDomainIdx);
  StbM_TimeBaseStatusType timeBaseStatusLoc;
  StbM_TimeBaseStatusType ofsTimeBaseStatusLoc;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the time base status from Stbm. */
  if(StbM_GetTimeBaseStatus(timeBaseId, &timeBaseStatusLoc, &ofsTimeBaseStatusLoc) == E_OK) /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
  {
    /* #100 Check if the Global Time Base bit is set. */
    if((timeBaseStatusLoc & ETHTSYN_TIME_BASE_STATUS_GLOBAL_TIME_BASE_MASK) != 0)
    {
      isGlobalTimeBase = TRUE;
    }
  }

  return isGlobalTimeBase;
} /* EthTSyn_Master_IsGlobalTimeBaseStatusBit() */

/**********************************************************************************************************************
 *  EthTSyn_Master_HasTimeBaseUpdateCounterChanged
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Master_HasTimeBaseUpdateCounterChanged(
  EthTSyn_TimeDomainIterType TimeDomainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean updateCounterHasChanged = FALSE;
  uint8 updateCounter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get current time base update counter from StbM. */
  updateCounter = StbM_GetTimeBaseUpdateCounter(EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(TimeDomainIdx));

  /* #20 Check if time base update counter has been read before. */
  if(EthTSyn_IsValidOfTimeBaseUpdateCounter(TimeDomainIdx) == TRUE)
  {
    /* #200 Check if value has changed. */
    if(updateCounter != EthTSyn_GetValueOfTimeBaseUpdateCounter(TimeDomainIdx))
    {
      EthTSyn_SetValueOfTimeBaseUpdateCounter(TimeDomainIdx, updateCounter);                                           /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
      updateCounterHasChanged = TRUE;
    }
  }
  else
  {
    /* #201 Store initial value. */
    EthTSyn_SetValueOfTimeBaseUpdateCounter(TimeDomainIdx, updateCounter);                                             /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
    EthTSyn_SetValidOfTimeBaseUpdateCounter(TimeDomainIdx, TRUE);                                                      /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
  }

  return updateCounterHasChanged;
}

/**********************************************************************************************************************
 *  EthTSyn_MasterTx_TxSyncMsg
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
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_MasterTx_TxSyncMsg(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  const EthTSyn_CtrlIdxOfPortType ctrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);
  const EthTSyn_EthIfCtrlIdxOfCtrlType ethIfCtrlIdx = EthTSyn_GetEthIfCtrlIdxOfCtrl(ctrlIdx);
  EthTSyn_EthTxBufferStructType txBuffer;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Try to get Ethernet TxBuffer for the sync message. */
  txBuffer.Length = ETHTSYN_MSG_SYNC_LENGTH;

  if (EthTSyn_UtilTx_ProvideTxBuffer(ethIfCtrlIdx, EthTSyn_GetFramePrioOfPort(PortIdx), &txBuffer) == E_OK)            /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
  {
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
    EthSwt_MgmtInfoType mgmtInfo;
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
    const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
    ETHTSYN_CONSTP2VAR(EthTSyn_SyncSendSmType) syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);
    ETHTSYN_P2CONST(EthTSyn_SwtMgmtInfoType) mgmtInfoPtr = NULL_PTR;
    ETHTSYN_P2VAR(EthTSyn_CommonMsgHdrType) comMsgPtr = (ETHTSYN_P2VAR(EthTSyn_CommonMsgHdrType))txBuffer.BufferPtr; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */

    ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* Reset Timestamp States */
    syncSendSmPtr->FollowUpPreciseOriginTimestampMgmt.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_INVALID;               /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
    syncSendSmPtr->SyncIngressTimestampMgmtHostPort.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_INVALID;                 /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
    syncSendSmPtr->SyncEgressTimestampMgmtSwitchPort.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_INVALID;                /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */


    /* #20 Set common header message attributes. */
    EthTSyn_UtilTx_PrepareCommonMsgHdr(comMsgPtr, ETHTSYN_MSG_TYPE_SYNC, PortIdx);                                     /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */

    /* #30 Set message specific attributes. */

    /* #40 Get switch management information and frame id if applicable. */
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
    if (EthTSyn_UtilTx_GetSwtMgmtInfo(PortIdx, &mgmtInfo) == E_OK)                                                     /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
    {
      mgmtInfo.FrameId = txBuffer.FrameId;
      syncSendSmPtr->FrameId = mgmtInfo.FrameId;                                                                       /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */

      mgmtInfoPtr = &mgmtInfo;
    }
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

    syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_TX_FUP;                                                              /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */

    ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #50 Enable egress timestamping. */
    if(EthTSyn_UtilTx_PrepareTransmission(
      ethIfCtrlIdx, txBuffer.BufferIdx, ETHTSYN_ENABLE_TS_HW_AND_SWT_TS, mgmtInfoPtr) == E_OK)                         /* SBSW_ETHTSYN_POINTER_VARIABLE */
    {
      syncSendSmPtr->FollowUpPreciseOriginTimestampMgmt.State =
        ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_WAITING_FOR_TIMESTAMP;                                              /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
      syncSendSmPtr->SyncIngressTimestampMgmtHostPort.State =
        ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_WAITING_FOR_TIMESTAMP;                                              /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
      syncSendSmPtr->SyncEgressTimestampMgmtSwitchPort.State =
        ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_WAITING_FOR_TIMESTAMP;                                              /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

      /* #60 Trigger transmission. */
      retVal = EthTSyn_UtilTx_Transmit(ethIfCtrlIdx, txBuffer.BufferIdx, ETHTSYN_MSG_SYNC_LENGTH);
    }

    /* #70 Store tx buffer information in case of successful transmission and release Ethernet tx buffer otherwise. */
    if(retVal == E_OK)
    {
      syncSendSmPtr->SyncTxBuf.Index = txBuffer.BufferIdx;                                                             /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
      syncSendSmPtr->SyncTxBuf.Address = txBuffer.BufferPtr;                                                           /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
    }
    else
    {
      EthTSyn_UtilTx_ReleaseTxBuffer(ethIfCtrlIdx, txBuffer.BufferIdx);
    }
  }

  return retVal;
} /* EthTSyn_MasterTx_TxSyncMsg() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  EthTSyn_MasterTx_TxFollowUpMsg
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
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_MasterTx_TxFollowUpMsg(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
  EthTSyn_SwtMgmtInfoType mgmtInfo;
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
  const EthTSyn_CtrlIdxOfPortType ctrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);
  const EthTSyn_EthIfCtrlIdxOfCtrlType ethIfCtrlIdx = EthTSyn_GetEthIfCtrlIdxOfCtrl(ctrlIdx);
  const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
  ETHTSYN_CONSTP2VAR(EthTSyn_SyncSendSmType) syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);
  EthTSyn_EthTxBufferStructType txBuffer;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get Ethernet transmission buffer. */
  txBuffer.Length = EthTSyn_GetFollowUpMsgLengthOfMasterPort(masterPortIdx);
  if (EthTSyn_UtilTx_ProvideTxBuffer(ethIfCtrlIdx, EthTSyn_GetFramePrioOfPort(PortIdx), &txBuffer) == E_OK)            /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
  {
    ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #20 Copy follow up message to Ethernet TxBuffer. */
    EthTSyn_MasterTx_CopyFollowUpToTxBuffer(PortIdx, txBuffer.BufferPtr);                                              /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */


    ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #30 Append FollowUp Ar TLVs if applicable. */
# if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
    EthTSyn_MasterTx_AppendArFollowUpTlvs(PortIdx, txBuffer.BufferPtr);                                                /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */
# endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */

    /* #40 Get switch management information and frame id if applicable. */
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
    if (EthTSyn_UtilTx_GetSwtMgmtInfo(PortIdx, &mgmtInfo) == E_OK)                                                     /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
    {
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
      /* #400 Set switch management info. */
      mgmtInfo.FrameId = txBuffer.FrameId;
      retVal = EthTSyn_UtilTx_PrepareTransmission(ethIfCtrlIdx, txBuffer.BufferIdx, ETHTSYN_ENABLE_TS_NONE, &mgmtInfo);/* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
      if (retVal == E_OK)
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
      {
        /* #50 Trigger transmission. */
        retVal = EthTSyn_UtilTx_Transmit(ethIfCtrlIdx, txBuffer.BufferIdx, txBuffer.Length);
      }
    }

    /* #60 Store bufIdx and bufferPtr for call-back in tx-confirmation in case of successful transmission and release
           Ethernet transmission buffer otherwise. */
    if(retVal == E_OK)
    {
      syncSendSmPtr->FollowUpTxBuf.Index = txBuffer.BufferIdx;                                                         /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
      syncSendSmPtr->FollowUpTxBuf.Address = txBuffer.BufferPtr;                                                       /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
    }
    else
    {
      EthTSyn_UtilTx_ReleaseTxBuffer(ethIfCtrlIdx, txBuffer.BufferIdx);
    }
  }

  return retVal;
} /* EthTSyn_MasterTx_TxFollowUpMsg() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  EthTSyn_MasterTx_IsFollowUpTxReady
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_MasterTx_IsFollowUpTxReady(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isTxReady = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Port is ready for transmission. */
  if(EthTSyn_IsTxReady(PortIdx) == TRUE)
  {
    const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
    ETHTSYN_CONSTP2VAR(EthTSyn_SyncSendSmType) syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);

    /* #20 Check if Precise Origin Timestamp is ready for processing. */
    ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    if(EthTSyn_IsTimestampReadyToProcess(syncSendSmPtr->FollowUpPreciseOriginTimestampMgmt.State) == TRUE)
    {
# if ( (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) && (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) )
      /* #30 Check if Switch Timestamps are available already. */
      /* PRQA S 3415 2 */ /* MD_EthTSyn_3415_ReadOnly */
      if((EthTSyn_IsTimestampReadyToProcess(syncSendSmPtr->SyncEgressTimestampMgmtSwitchPort.State)) &&
        (EthTSyn_IsTimestampReadyToProcess(syncSendSmPtr->SyncIngressTimestampMgmtHostPort.State)))
      {
        isTxReady = TRUE;
      }
# else
      isTxReady = TRUE;
# endif /* ( (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) && (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) ) */
    }
    ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }

  return isTxReady;
} /* EthTSyn_MasterTx_IsFollowUpTxReady() */

/**********************************************************************************************************************
 *  EthTSyn_MasterTx_CopyFollowUpToTxBuffer
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_MasterTx_CopyFollowUpToTxBuffer(
                EthTSyn_IntPortIdxType PortIdx,
  ETHTSYN_P2VAR(uint8)                 TxBufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
  ETHTSYN_CONSTP2VAR(EthTSyn_SyncSendSmType) syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);
  ETHTSYN_P2VAR(EthTSyn_CommonMsgHdrType) comMsgPtr = (ETHTSYN_P2VAR(EthTSyn_CommonMsgHdrType))TxBufPtr; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */
  ETHTSYN_P2VAR(EthTSyn_FollowUpMsgType) followUpPtr =
    (ETHTSYN_P2VAR(EthTSyn_FollowUpMsgType))&TxBufPtr[ETHTSYN_HDR_COM_LENGTH]; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */
  uint64 unsignedFollowUpCorrectionValueNs;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare the common message header. */
  EthTSyn_UtilTx_PrepareCommonMsgHdr(comMsgPtr, ETHTSYN_MSG_TYPE_FOLLOW_UP, PortIdx);                                  /* SBSW_ETHTSYN_PASSING_API_POINTER */

  /* #20 Set FollowUp message specific values. */

  /* Set IEEE Tlv values. */ /*lint -e572 */
  followUpPtr->TlvType = EthTSyn_Htons(ETHTSYN_FOLLOW_UP_TLV_TYPE);                                                    /* SBSW_ETHTSYN_PASSING_API_POINTER */
  followUpPtr->LengthField = EthTSyn_Htons(ETHTSYN_FOLLOW_UP_TLV_LENGTH_FIELD);                                        /* SBSW_ETHTSYN_PASSING_API_POINTER */
  followUpPtr->OrganisationId[0] = (uint8)((ETHTSYN_FOLLOW_UP_ORGANISATION_ID >> 16u) & 0x000000FFu);                  /* SBSW_ETHTSYN_PASSING_API_POINTER */
  followUpPtr->OrganisationId[1] = (uint8)((ETHTSYN_FOLLOW_UP_ORGANISATION_ID >> 8u) & 0x000000FFu);                   /* SBSW_ETHTSYN_PASSING_API_POINTER */
  followUpPtr->OrganisationId[2] = (uint8)((ETHTSYN_FOLLOW_UP_ORGANISATION_ID >> 0u) & 0x000000FFu);                   /* SBSW_ETHTSYN_PASSING_API_POINTER */
  followUpPtr->OrganisationSubType[0] = (uint8)((ETHTSYN_FOLLOW_UP_ORGANISATION_SUBTYPE >> 16u) & 0x000000FFu);        /* SBSW_ETHTSYN_PASSING_API_POINTER */
  followUpPtr->OrganisationSubType[1] = (uint8)((ETHTSYN_FOLLOW_UP_ORGANISATION_SUBTYPE >> 8u) & 0x000000FFu);         /* SBSW_ETHTSYN_PASSING_API_POINTER */
  followUpPtr->OrganisationSubType[2] = (uint8)((ETHTSYN_FOLLOW_UP_ORGANISATION_SUBTYPE >> 0u) & 0x000000FFu);         /* SBSW_ETHTSYN_PASSING_API_POINTER */
  /*lint +e572 */
  /* Set Precise origin timestamp. */ /* PRQA S 0310 2 */ /* MD_EthTSyn_0310_Timestamp */
  EthTSyn_UtilTx_HtonTimestamp((ETHTSYN_P2VAR(EthTSyn_TimestampType))followUpPtr->PreciseOriginTimestampSeconds,
      &syncSendSmPtr->FollowUpPreciseOriginTimestampMgmt.Timestamp);                                                   /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */

  /* #30 Compute follow up correction field if possible. */
# if ( (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) && (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) )
  unsignedFollowUpCorrectionValueNs = ETHTSYN_SWT_UPLINK_TO_TX_RESIDENCE_TIME_NS;

  if((EthTSyn_Util_IsTimestampAvailable(syncSendSmPtr->SyncEgressTimestampMgmtSwitchPort.State) == TRUE) && /* PRQA S 3415 */ /* MD_EthTSyn_3415_ReadOnly */
    (EthTSyn_Util_IsTimestampAvailable(syncSendSmPtr->SyncIngressTimestampMgmtHostPort.State) == TRUE))
  {
    EthTSyn_TimediffType switchResidenceTime;

    /* calculate FollowUp correction value. */
    if(EthTSyn_Util_TimestampMinusTimestamp(&syncSendSmPtr->SyncEgressTimestampMgmtSwitchPort.Timestamp,
        &syncSendSmPtr->SyncIngressTimestampMgmtHostPort.Timestamp, &switchResidenceTime) == E_OK)                     /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
    {
      /* Sanity check of switch residence time. */
      if(switchResidenceTime > 0)
      {
        unsignedFollowUpCorrectionValueNs = (uint64)switchResidenceTime;
      }
    }
    /* #300 Provide timestamps for switch time synchronization if required. */
#  if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
    if(EthTSyn_IsValidForSwtTimeSyncOfMasterPort(masterPortIdx) == TRUE)
    {
      const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
      const EthTSyn_SwitchPortMgmtIdxOfPortType swtPortMgmtIdx = EthTSyn_GetSwitchPortMgmtIdxOfPort(PortIdx);
      const EthTSyn_SwitchIdxOfSwitchPortMgmtType ethIfSwitchIdx = EthTSyn_GetSwitchIdxOfSwitchPortMgmt(swtPortMgmtIdx);

      EthTSyn_SwtTimeSync_ProvideTimestamps(
        timeDomainIdx,
        ethIfSwitchIdx,
        syncSendSmPtr->SequenceId,
        &syncSendSmPtr->FollowUpPreciseOriginTimestampMgmt.Timestamp,
        &syncSendSmPtr->SyncIngressTimestampMgmtHostPort.Timestamp);
    }
#  endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
  }
# else
  unsignedFollowUpCorrectionValueNs = 0;
# endif /* ( (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) && (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) ) */

  /* #40 Set follow up correction field. */
  /* PRQA S 3109 1 */ /* MD_MSR_14_3 */
  EthTSyn_CopyFollowUpCorrectionField(unsignedFollowUpCorrectionValueNs, comMsgPtr->CorrectionField);                  /* SBSW_ETHTSYN_ARRAY_SIZE */

} /* EthTSyn_MasterTx_CopyFollowUpToTxBuffer() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

# if (ETHTSYN_ANNOUNCE_TX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_Master_TxAnnounceMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_TxAnnounceMsg(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_IntCtrlIdxType ctrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);
  const EthTSyn_EthIfCtrlIdxOfCtrlType ethIfCtrlIdx = EthTSyn_GetEthIfCtrlIdxOfCtrl(ctrlIdx);
  EthTSyn_EthTxBufferStructType txBuffer;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Try to get an transmission buffer. */
  txBuffer.Length = ETHTSYN_MSG_ANNOUNCE_LENGTH;
  if (EthTSyn_UtilTx_ProvideTxBuffer(ethIfCtrlIdx, EthTSyn_GetFramePrioOfPort(PortIdx), &txBuffer) == E_OK)            /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
  {
    ETHTSYN_P2VAR(EthTSyn_CommonMsgHdrType) comMsgPtr = (ETHTSYN_P2VAR(EthTSyn_CommonMsgHdrType))txBuffer.BufferPtr; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */
    ETHTSYN_P2VAR(EthTSyn_AnnounceMsgType) announcePtr =
      (ETHTSYN_P2VAR(EthTSyn_AnnounceMsgType))&txBuffer.BufferPtr[ETHTSYN_HDR_COM_LENGTH]; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */
    ETHTSYN_CONSTP2VAR(EthTSyn_CtrlStateType) ctrlStatePtr = EthTSyn_GetAddrCtrlState(ctrlIdx);

    /* #20 Copy announce message to the transmission buffer */
    ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* set common header message attributes */
    EthTSyn_UtilTx_PrepareCommonMsgHdr(comMsgPtr, ETHTSYN_MSG_TYPE_ANNOUNCE, PortIdx);                                 /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */

    /* set specific message type attributes */
    announcePtr->GrandmasterPriority_1 = ETHTSYN_ANNOUNCE_PRIORITY_1_NETWORK_INFRASTRUCTURE;                           /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
    announcePtr->GrandmasterClockQuality.ClockAccuracy = ETHTSYN_ANNOUNCE_CLOCK_ACCURACY_UNKNOWN;                      /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
    announcePtr->GrandmasterClockQuality.ClockClass = ETHTSYN_ANNOUNCE_CLOCK_CLASS_UNKNOWN;                            /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
    announcePtr->GrandmasterClockQuality.OffsetScaledLogVariance =
      (uint16)EthTSyn_Htons(ETHTSYN_ANNOUNCE_OFFSET_SCALED_LOG_UNKNOWN);                                               /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
    announcePtr->GrandmasterPriority_2 = ETHTSYN_ANNOUNCE_PRIORITY_2_DEFAULT;                                          /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */

    EthTSyn_SetClockIdentity(announcePtr->GrandmasterIdentity, ctrlStatePtr->ClockIdentity);                           /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */

    announcePtr->TimeSource = ETHTSYN_ANNOUNCE_TIME_SOURCE_INTERNAL_OSCILLATOR;                                        /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
    /*lint -e572 */
    announcePtr->TlvType = EthTSyn_Ntohs((uint16)ETHTSYN_ANNOUNCE_TLV_TYPE);                                           /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
    announcePtr->LengthField = EthTSyn_Ntohs((uint16)ETHTSYN_ANNOUNCE_TLV_LENGTH_FIELD); /*lint +e572 */               /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */

    /* set Tlv Clock identity */
    EthTSyn_SetClockIdentity(announcePtr->ClockIdentity, ctrlStatePtr->ClockIdentity);                                 /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */
    ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #30 Trigger transmission. */
    if (EthTSyn_UtilTx_Transmit(ethIfCtrlIdx, txBuffer.BufferIdx, ETHTSYN_MSG_ANNOUNCE_LENGTH) != E_OK)
    {
      /* #40 Release Ethernet transmission buffer in case of failure. */
      EthTSyn_UtilTx_ReleaseTxBuffer(ethIfCtrlIdx, txBuffer.BufferIdx);
    }
  }

} /* EthTSyn_Master_TxAnnounceMsg() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
# endif /* (ETHTSYN_ANNOUNCE_TX_SUPPORT == STD_ON) */

# if (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF)
/**********************************************************************************************************************
 *  MASTER TX AUTOSAR TLVS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_MasterTx_AppendArFollowUpTlvs
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
/* AR4.3 message format */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_MasterTx_AppendArFollowUpTlvs(
                EthTSyn_IntPortIdxType PortIdx,
  ETHTSYN_P2VAR(uint8)                 TxBufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 arTlvHdrLengthField = ETHTSYN_AR_TLV_HEADER_LENGTH_FIELD_VALUE; /* Add length sum of Sub-Tlvs later */
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) comMsgPtr = (ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType))TxBufPtr; /* PRQA S 0310 1 */ /* MD_EthTSyn_0310_MsgStruct */
  ETHTSYN_P2VAR(EthTSyn_ArTlvHeaderType) arTlvHdrPtr =
    (ETHTSYN_P2VAR(EthTSyn_ArTlvHeaderType))&TxBufPtr[ETHTSYN_HDR_COM_LENGTH + ETHTSYN_FOLLOW_UP_AR_TLV_OFFSET]; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */
  /* Set bufferPtr to OrganisationId because the Length starts from this field */
  ETHTSYN_P2VAR(uint8) bufferPtr = ((ETHTSYN_P2VAR(uint8))arTlvHdrPtr->OrganisationId);
#  if (ETHTSYN_CRC_SUPPORT == STD_ON)
  uint8 dataId = EthTSyn_Util_GetFollowUpDataIdListEntry(EthTSyn_GetTimeDomainIdxOfPort(PortIdx),
    (uint16)EthTSyn_Ntohs(comMsgPtr->SequenceId));
#  else
  uint8 dataId = 0;
#  endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */

  /* ----- Implementation ----------------------------------------------- */
  if(EthTSyn_Util_IsArTlvTxRequired(EthTSyn_GetMasterPortIdxOfPort(PortIdx)) == TRUE)
  {
    /* #10 Append the Time Secured Sub-Tlv if applicable */
    EthTSyn_MasterTx_AppendArFollowUpTimeTlv(PortIdx, dataId, comMsgPtr, bufferPtr, &arTlvHdrLengthField);             /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */

    /* #20 Append the Status (Not) Secured Sub-Tlv if applicable */
    EthTSyn_MasterTx_AppendArFollowUpStatusTlv(PortIdx, dataId, bufferPtr, &arTlvHdrLengthField);                      /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */

    /* #30 Append the User Data (Not) Secured Sub-Tlv if applicable */
    EthTSyn_MasterTx_AppendArFollowUpUserDataTlv(PortIdx, dataId, bufferPtr, &arTlvHdrLengthField);                    /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */

    /* #40 Append the Ofs (Not) Secured Sub-Tlv if applicable */
#  if (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON)
    EthTSyn_MasterTx_AppendArFollowUpOfsTlvs(PortIdx, dataId, bufferPtr, &arTlvHdrLengthField);                        /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
#  endif /* (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON) */

    /* #50 Init ArTlvHdr */
    /* Set Tlv Type */
    ETHTSYN_PUT_UINT16(arTlvHdrPtr->TlvType, 0, ETHTSYN_AR_TLV_TYPE); /*lint !e572 */                                  /* SBSW_ETHTSYN_ARRAY_SIZE */

    /* Set length field */
    ETHTSYN_PUT_UINT16(arTlvHdrPtr->LengthField, 0u, arTlvHdrLengthField);                                             /* SBSW_ETHTSYN_ARRAY_SIZE */

    /* Set Organization Id and SubType */
    ETHTSYN_PUT_3_BYTE(arTlvHdrPtr->OrganisationId, 0, ETHTSYN_AR_TLV_ORGANIZATION_ID);                                /* SBSW_ETHTSYN_ARRAY_SIZE */
    ETHTSYN_PUT_3_BYTE(arTlvHdrPtr->OrganisationSubType, 0, ETHTSYN_AR_TLV_ORGANIZATION_SUB_TYPE);                     /* SBSW_ETHTSYN_ARRAY_SIZE */
  }

} /* EthTSyn_MasterTx_AppendArFollowUpTlvs() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_MasterTx_AppendArFollowUpTimeTlv
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_MasterTx_AppendArFollowUpTimeTlv(
                  EthTSyn_IntPortIdxType    PortIdx,
                  uint8                     DataId,
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) ComMsgPtr,
    ETHTSYN_P2VAR(uint8)                    BufferPtr,
    ETHTSYN_P2VAR(uint16)                   OffsetPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_SizeOfMasterPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
  ETHTSYN_P2VAR(EthTSyn_ArSubTlvTimeSecuredType) timeSecuredSubTlvPtr;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Time Tlv is required. */
  if(EthTSyn_IsTimeSubTlvOfMasterPort(masterPortIdx) == TRUE)
  {
    /* Get the Time Secured Sub-Tlv pointer */
    timeSecuredSubTlvPtr = (ETHTSYN_P2VAR(EthTSyn_ArSubTlvTimeSecuredType))&BufferPtr[*OffsetPtr]; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */

    /* #20 Increase offset for further Sub-Tlv. */
    (*OffsetPtr) += ETHTSYN_AR_SUB_TLV_TIME_LENGTH;                                                                    /* SBSW_ETHTSYN_VALID_API_POINTER */

    /* #30 Append Time Secured Tlv. */
    /* Set Type and length */
    timeSecuredSubTlvPtr->Type = ETHTSYN_AR_SUB_TLV_TYPE_TIME_SECURED;                                                 /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
    timeSecuredSubTlvPtr->Length = ETHTSYN_AR_SUB_TLV_TIME_LENGTH_FIELD_VALUE;                                         /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */

    /* Set CRC_Time_Flags */
    timeSecuredSubTlvPtr->CrcTimeFlags = EthTSyn_GetCrcTimeFlagsOfMasterPort(masterPortIdx);                           /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */

    /* Calculate and set CRC_Time_0/1 */
#  if (ETHTSYN_CRC_SUPPORT == STD_ON)
    timeSecuredSubTlvPtr->CrcTime0 =
      EthTSyn_Crc_ComputeTime0Crc(DataId, timeSecuredSubTlvPtr->CrcTimeFlags, ComMsgPtr);                              /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */ /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */ /* SBSW_ETHTSYN_PASSING_API_POINTER */
    timeSecuredSubTlvPtr->CrcTime1 =
      EthTSyn_Crc_ComputeTime1Crc(DataId, timeSecuredSubTlvPtr->CrcTimeFlags, ComMsgPtr);                              /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */ /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */
#  else
    ETHTSYN_DUMMY_STATEMENT(DataId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
    ETHTSYN_DUMMY_STATEMENT(ComMsgPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#  endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */
  }
} /* EthTSyn_MasterTx_AppendArFollowUpTimeTlv() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_MasterTx_AppendArFollowUpStatusTlv
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_MasterTx_AppendArFollowUpStatusTlv(
                EthTSyn_IntPortIdxType PortIdx,
                uint8                  DataId,
  ETHTSYN_P2VAR(uint8)                 BufferPtr,
  ETHTSYN_P2VAR(uint16)                OffsetPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_SizeOfMasterPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
  ETHTSYN_P2VAR(EthTSyn_ArSubTlvStatusType) statusSubTlvPtr;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Status Tlv is required. */
  if(EthTSyn_IsStatusSubTlvOfMasterPort(masterPortIdx) == TRUE)
  {
    const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
    const StbM_SynchronizedTimeBaseType timeBaseId = EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(timeDomainIdx);
    StbM_TimeBaseStatusType timeBaseStatusLoc;
    StbM_TimeBaseStatusType ofsTimeBaseStatusLoc;

    /* Get the Status (Not) Secured Sub-Tlv pointer */
    statusSubTlvPtr = (ETHTSYN_P2VAR(EthTSyn_ArSubTlvStatusType))&BufferPtr[*OffsetPtr]; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */

    /* #20 Increase offset for further Sub-Tlv. */
    (*OffsetPtr) += ETHTSYN_AR_SUB_TLV_STATUS_LENGTH;                                                                  /* SBSW_ETHTSYN_VALID_API_POINTER */

    /* Set length */
    statusSubTlvPtr->Length = ETHTSYN_AR_SUB_TLV_STATUS_LENGTH_FIELD_VALUE;                                            /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */

    /* #30 Get the synchronized time base status. */
    if(StbM_GetTimeBaseStatus(timeBaseId, &timeBaseStatusLoc, &ofsTimeBaseStatusLoc) == E_OK)                          /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
    {
      ETHTSYN_TIME_BASE_STATUS_TO_AR_SUB_TLV_STATUS(timeBaseStatusLoc, statusSubTlvPtr->Status);                       /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
    }
    else
    {
      statusSubTlvPtr->Status = 0u; /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
    }

    /* #40 Append Status Tlv. */
    /* Write Type Secured/NotSecured and Crc (if applicable) */
#  if (ETHTSYN_CRC_SUPPORT == STD_ON)
    if(EthTSyn_GetTxCrcSecuredOfMasterPort(masterPortIdx) == ETHTSYN_TX_CRC_SECURED_CRC_SUPPORTED)
    {
      /* Secured */
      statusSubTlvPtr->Type = ETHTSYN_AR_SUB_TLV_TYPE_STATUS_SECURED;                                                  /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
      statusSubTlvPtr->CrcStatus = EthTSyn_Crc_ComputeStatusCrc(DataId, statusSubTlvPtr);                              /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */ /* SBSW_ETHTSYN_POINTER_VARIABLE */
    }
    else
#  else
    ETHTSYN_DUMMY_STATEMENT(DataId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#  endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */
    {
      /* Not Secured */
      statusSubTlvPtr->Type = ETHTSYN_AR_SUB_TLV_TYPE_STATUS_NOT_SECURED;                                              /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
      statusSubTlvPtr->CrcStatus = 0u;                                                                                 /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
    }
  }
} /* EthTSyn_MasterTx_AppendArFollowUpStatusTlv() */

/**********************************************************************************************************************
 *  EthTSyn_MasterTx_AppendArFollowUpUserDataTlv
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_MasterTx_AppendArFollowUpUserDataTlv(
                EthTSyn_IntPortIdxType PortIdx,
                uint8                  DataId,
  ETHTSYN_P2VAR(uint8)                 BufferPtr,
  ETHTSYN_P2VAR(uint16)                OffsetPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_SizeOfMasterPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
  ETHTSYN_P2VAR(EthTSyn_ArSubTlvUserDataType) userDataSubTlvPtr;
  StbM_UserDataType userData;
  StbM_TimeStampType timeStamp;

  /* ----- Implementation ----------------------------------------------- */
  /* Initialize userData */
  userData.userDataLength = 0;
  userData.userByte0 = 0;
  userData.userByte1 = 0;
  userData.userByte2 = 0;

  /* #10 Check if UserData Tlv is required. */
  if(EthTSyn_IsUserDataSubTlvOfMasterPort(masterPortIdx) == TRUE)
  {
    const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
    const StbM_SynchronizedTimeBaseType timeBaseId = EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(timeDomainIdx);

    /* Get the UserData (Not) Secured Sub-Tlv pointer */
    userDataSubTlvPtr = (ETHTSYN_P2VAR(EthTSyn_ArSubTlvUserDataType))&BufferPtr[*OffsetPtr]; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */

    /* #20 Increase offset for further Sub-Tlv. */
    (*OffsetPtr) += ETHTSYN_AR_SUB_TLV_USER_DATA_LENGTH;                                                               /* SBSW_ETHTSYN_VALID_API_POINTER */

    /* Set length field */
    userDataSubTlvPtr->Length = ETHTSYN_AR_SUB_TLV_USER_DATA_LENGTH_FIELD_VALUE;                                       /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */

    /* #30 Get the synchronized time base UserData. */
    if(StbM_GetCurrentTime(timeBaseId, &timeStamp, &userData) != E_OK)                                                 /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
    {
      /* #300 Failed to retrieve user data -> set to '0'. */
      userData.userDataLength = 0;                                                                                     /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
      userData.userByte0 = 0;                                                                                          /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
      userData.userByte1 = 0;                                                                                          /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
      userData.userByte2 = 0;                                                                                          /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
    }

    /* #40 Append UserData Tlv. */
    /* Write UserData */
    userDataSubTlvPtr->UserDataLength = userData.userDataLength;                                                       /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
    userDataSubTlvPtr->UserByte0 = userData.userByte0;                                                                 /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
    userDataSubTlvPtr->UserByte1 = userData.userByte1;                                                                 /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
    userDataSubTlvPtr->UserByte2 = userData.userByte2;                                                                 /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */

    /* Write Type Secured/NotSecured and Crc (if applicable) */
#  if (ETHTSYN_CRC_SUPPORT == STD_ON)
    if(EthTSyn_GetTxCrcSecuredOfMasterPort(masterPortIdx) == ETHTSYN_TX_CRC_SECURED_CRC_SUPPORTED)
    {
      /* Secured */
      userDataSubTlvPtr->Type = ETHTSYN_AR_SUB_TLV_TYPE_USER_DATA_SECURED;                                             /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
      userDataSubTlvPtr->CrcUserData = EthTSyn_Crc_ComputeUserDataCrc(DataId, userDataSubTlvPtr);                      /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */ /* SBSW_ETHTSYN_POINTER_VARIABLE */
    }
    else
#  else
    ETHTSYN_DUMMY_STATEMENT(DataId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#  endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */
    {
      /* Not Secured */
      userDataSubTlvPtr->Type = ETHTSYN_AR_SUB_TLV_TYPE_USER_DATA_NOT_SECURED;                                         /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
      userDataSubTlvPtr->CrcUserData = 0u;                                                                             /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
    }
  }
} /* EthTSyn_MasterTx_AppendArFollowUpUserDataTlv() */

#  if (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_MasterTx_AppendArFollowUpOfsTlvs
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_MasterTx_AppendArFollowUpOfsTlvs(
                EthTSyn_IntPortIdxType PortIdx,
                uint8                  DataId,
  ETHTSYN_P2VAR(uint8)                 BufferPtr,
  ETHTSYN_P2VAR(uint16)                OffsetPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_SizeOfMasterPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
  ETHTSYN_P2VAR(EthTSyn_ArSubTlvOfsType) ofsSubTlvPtr;
  EthTSyn_OffsetTimeDomainIterType offsetTimeDomainIter;
  StbM_UserDataType userData;
  StbM_TimeStampType timeStamp;

  /* ----- Implementation ----------------------------------------------- */
  /* Initialize UserData and Timestamp */
  userData.userDataLength = 0;
  userData.userByte0 = 0;
  userData.userByte1 = 0;
  userData.userByte2 = 0;

  timeStamp.timeBaseStatus = 0;
  timeStamp.secondsHi = 0;
  timeStamp.seconds = 0;
  timeStamp.nanoseconds = 0;

  /* #10 Check if Ofs Tlv is required */
  if(EthTSyn_IsOfsSubTlvOfMasterPort(masterPortIdx) == TRUE)
  {
    const EthTSyn_TimeDomainIdxOfPortType timeDomainIdxOfPort = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
    /* Iterate the offset TimeDomains for the given Port and append an Ofs Sub-Tlv for each of them */
    for(offsetTimeDomainIter = EthTSyn_GetOffsetTimeDomainStartIdxOfTimeDomain(timeDomainIdxOfPort);
        offsetTimeDomainIter < EthTSyn_GetOffsetTimeDomainEndIdxOfTimeDomain(timeDomainIdxOfPort);
        offsetTimeDomainIter++)
    {
      const uint8 ofsTimeDomainId = EthTSyn_GetIdOfOffsetTimeDomain(offsetTimeDomainIter);
      const StbM_SynchronizedTimeBaseType timebaseId =
        EthTSyn_GetSynchronizedTimeBaseIdOfOffsetTimeDomain(offsetTimeDomainIter);

      /* Get Ofs (Not) Secured Sub-Tlv Pointer */
      ofsSubTlvPtr = (ETHTSYN_P2VAR(EthTSyn_ArSubTlvOfsType))&BufferPtr[*OffsetPtr]; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */

      /* #20 Increase offset for further Sub-Tlv */
      (*OffsetPtr) += ETHTSYN_AR_SUB_TLV_OFS_LENGTH;                                                                   /* SBSW_ETHTSYN_VALID_API_POINTER */

      /* Set length field */
      ofsSubTlvPtr->Length = ETHTSYN_AR_SUB_TLV_OFS_LENGTH_FIELD_VALUE;                                                /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */

      /* Set offset time domain */
      ofsSubTlvPtr->OfsTimeDomain = ofsTimeDomainId;                                                                   /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */

      /* #30 Get Offset and user data */
      if(StbM_GetOffset(timebaseId, &timeStamp) != E_OK)                                                               /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
      {
        /* #300 Failed to retrieve the Offset -> set to '0' */
        timeStamp.timeBaseStatus = 0;
        timeStamp.secondsHi = 0;
        timeStamp.seconds = 0;
        timeStamp.nanoseconds = 0;
      }

      /* #40 Append Ofs Tlv */
      /* Write Offset */
      ETHTSYN_PUT_UINT16(ofsSubTlvPtr->OfsTimeSec, 0u, timeStamp.secondsHi);                                           /* SBSW_ETHTSYN_ARRAY_SIZE */
      ETHTSYN_PUT_UINT32(ofsSubTlvPtr->OfsTimeSec, ETHTSYN_AR_SUB_TLV_OFS_TIME_SEC_SECONDS_OFFSET, timeStamp.seconds); /* SBSW_ETHTSYN_ARRAY_SIZE */
      ETHTSYN_PUT_UINT32(ofsSubTlvPtr->OfsTimeNSec, 0u, timeStamp.nanoseconds);                                        /* SBSW_ETHTSYN_ARRAY_SIZE */

      /* Write Status */
      ETHTSYN_TIME_BASE_STATUS_TO_AR_SUB_TLV_STATUS(timeStamp.timeBaseStatus, ofsSubTlvPtr->Status);                   /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */

      /* Write UserData */
      ofsSubTlvPtr->UserDataLength = userData.userDataLength;                                                          /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
      ofsSubTlvPtr->UserByte0 = userData.userByte0;                                                                    /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
      ofsSubTlvPtr->UserByte1 = userData.userByte1;                                                                    /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
      ofsSubTlvPtr->UserByte2 = userData.userByte2;                                                                    /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */

      /* Write Type Secured/NotSecured and Crc (if applicable) */
#   if (ETHTSYN_CRC_SUPPORT == STD_ON)
      if(EthTSyn_GetTxCrcSecuredOfMasterPort(masterPortIdx) == ETHTSYN_TX_CRC_SECURED_CRC_SUPPORTED)
      {
        /* Secured */
        ofsSubTlvPtr->Type = ETHTSYN_AR_SUB_TLV_TYPE_OFS_SECURED;                                                      /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
        ofsSubTlvPtr->CrcOfs = EthTSyn_Crc_ComputeOfsCrc(DataId, ofsSubTlvPtr);                                        /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */ /* SBSW_ETHTSYN_POINTER_VARIABLE */
      }
      else
#   else
      ETHTSYN_DUMMY_STATEMENT(DataId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#   endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */
      {
        /* Not Secured */
        ofsSubTlvPtr->Type = ETHTSYN_AR_SUB_TLV_TYPE_OFS_NOT_SECURED;                                                  /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
        ofsSubTlvPtr->CrcOfs = 0u;                                                                                     /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */
      }
    } /* END: Iteration of all Offset TimeDomains for the given Port */
  }
} /* EthTSyn_MasterTx_AppendArFollowUpOfsTlvs() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
#  endif /* (ETHTSYN_OFS_TIME_DOMAIN_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  END: MASTER TX AUTOSAR TLVS
 *********************************************************************************************************************/
# endif /* (ETHTSYN_MESSAGE_COMPLIANCE == STD_OFF) */

/**********************************************************************************************************************
 *  EthTSyn_Master_SyncSendSm_SendSync
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_SyncSendSm_SendSync(
  EthTSyn_IntPortIdxType PortIdx,
  boolean                IsImmediateSync)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
  EthTSyn_SyncSendSmStateEnumType syncSendSmStateTxFailed;
  uint32 txIntervalCntTxSuccess;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Sync message is an immediate sync and prepare the required values accordingly. */
  if(IsImmediateSync == TRUE)
  {
    syncSendSmStateTxFailed = ETHTSYN_S_SYNC_SEND_SM_TX_IMMEDIATE_SYNC;
    txIntervalCntTxSuccess = EthTSyn_GetCyclicMsgResumeCntOfMasterPort(masterPortIdx);
  }
  else
  {
    syncSendSmStateTxFailed = ETHTSYN_S_SYNC_SEND_SM_TX_SYNC;
    txIntervalCntTxSuccess = EthTSyn_GetSyncSendIntervalOfMasterPort(masterPortIdx);
  }

  /* #20 Verify that port is AsCapable and ready for transmission. */
  if( (EthTSyn_Util_IsAsCapable(PortIdx) == TRUE) && (EthTSyn_IsTxReady(PortIdx) == TRUE) ) /* PRQA S 3415 */ /* MD_EthTSyn_3415_ReadOnly */
  {
    EthTSyn_SyncSendSmPtrType syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);

    /* #30 Trigger transmission of Sync message. */
    if(EthTSyn_MasterTx_TxSyncMsg(PortIdx) == E_OK)
    {
      /* #300 Transmission successful: Recharge tx interval counter. */
      ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
      syncSendSmPtr->TxConfirmationPending++;                                                                          /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
      syncSendSmPtr->TxIntervalCnt = txIntervalCntTxSuccess;                                                           /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
      ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    }
    else
    {
      /* #301 Transmission failed: Retry transmission later by setting the state of the SyncSendSm. */
      syncSendSmPtr->State = syncSendSmStateTxFailed;                                                                  /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
    }
  }
} /* EthTSyn_Master_SyncSendSm_SendSync() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_Master_SyncSendSm_SendFup
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Master_SyncSendSm_SendFup(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Verify that port is AsCapable and ready to transmit FollowUp message. */
  if( (EthTSyn_Util_IsAsCapable(PortIdx) == TRUE) && (EthTSyn_MasterTx_IsFollowUpTxReady(PortIdx) == TRUE) ) /* PRQA S 3415 */ /* MD_EthTSyn_3415_ReadOnly */
  {
    const EthTSyn_SizeOfMasterPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
    EthTSyn_SyncSendSmPtrType syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);
    /* #20 Check if precise origin timestamp is available. */
    if(EthTSyn_Util_IsTimestampAvailable(syncSendSmPtr->FollowUpPreciseOriginTimestampMgmt.State) == TRUE)
    {
      /* #30 Precise origin timestamp is available: Trigger transmission of follow up message. */
      if(EthTSyn_MasterTx_TxFollowUpMsg(PortIdx) == E_OK)
      {
        /* #40 Transmission successful -> Handle sync send state machine. */

        ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

        syncSendSmPtr->SequenceId++;                                                                                   /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
        syncSendSmPtr->FollowUpPreciseOriginTimestampMgmt.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_INVALID;           /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
        syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_WAIT_TX_COUNTER;                                                 /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */

# if ( (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) && (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) )
        syncSendSmPtr->SyncEgressTimestampMgmtSwitchPort.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_INVALID;            /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
        syncSendSmPtr->SyncIngressTimestampMgmtHostPort.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_INVALID;             /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
# endif /* ( (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) && (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) ) */

        ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

        /* #50 Check if announce should be transmitted on the given master port. */
# if (ETHTSYN_ANNOUNCE_TX_SUPPORT == STD_ON)
        if(EthTSyn_IsTxAnnounceMsgOfMasterPort(masterPortIdx) == TRUE)
        {
          /* #500 Trigger transmission of announce message. */
          EthTSyn_Master_TxAnnounceMsg(PortIdx);
        }
# endif /* (ETHTSYN_ANNOUNCE_TX_SUPPORT == STD_ON) */
      }
    }
    else
    {
      /* #60 Precise origin timestamp is not available: Change state to WAIT_TX_COUNTER and increment sequence id. */
      syncSendSmPtr->SequenceId++;                                                                                     /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
      syncSendSmPtr->FollowUpPreciseOriginTimestampMgmt.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_INVALID;             /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
      syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_WAIT_TX_COUNTER;                                                   /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
    }
  }
} /* EthTSyn_Master_SyncSendSm_SendFup() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_Master_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Master_Init(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_MasterPortIterType masterPortIter;
  EthTSyn_TimeBaseUpdateCounterIterType timeBaseUpdateCounterIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset time base updated counter handler. */
  for(timeBaseUpdateCounterIter = 0;
      timeBaseUpdateCounterIter < EthTSyn_GetSizeOfTimeBaseUpdateCounter();
      timeBaseUpdateCounterIter++)
  {
    EthTSyn_SetValueOfTimeBaseUpdateCounter(timeBaseUpdateCounterIter, 0);                                             /* SBSW_ETHTSYN_CSL01 */
    EthTSyn_SetValidOfTimeBaseUpdateCounter(timeBaseUpdateCounterIter, FALSE);                                         /* SBSW_ETHTSYN_CSL01 */
  }

  /* #20 Iterate all master ports. */
  for(masterPortIter = 0;
      masterPortIter < EthTSyn_GetSizeOfMasterPort();
      masterPortIter++)
  {
    EthTSyn_Master_InitPortInternal(masterPortIter);
  }

} /* EthTSyn_Master_Init() */
/**********************************************************************************************************************
 *  EthTSyn_Master_InitPort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Master_InitPort(
  EthTSyn_IntMasterPortIdxType MasterPortIdx)
{
  EthTSyn_Master_InitPortInternal(MasterPortIdx);
} /* EthTSyn_Master_InitPort() */

/**********************************************************************************************************************
 *  EthTSyn_Master_ProcessSmSyncSend
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
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Master_ProcessSmSyncSend(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Verify that port is a master port. */
  if(EthTSyn_IsMasterPortUsedOfPort(PortIdx) == TRUE)
  {
    const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
    EthTSyn_SyncSendSmPtrType syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);
    /* #20 Check state of the sync send state machine. */
    switch(syncSendSmPtr->State)
    {
    case ETHTSYN_S_SYNC_SEND_SM_INITIALIZING:
      {
        const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);

        /* #200 State: Initializing -> Check if GLOBAL_TIME_BASE bit of StbM_TimeBaseStatus is set. */
        if (EthTSyn_Master_IsGlobalTimeBaseStatusBit(timeDomainIdx) == TRUE)
        {
          /* #2000 Change state to TX_SYNC. */
          syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_TX_SYNC;                                                       /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
        }
        break;
      }

    case ETHTSYN_S_SYNC_SEND_SM_WAIT_TX_COUNTER:
      {
        /* #201 State: Waiting for Sync send -> Check sync tx interval counter. */
        if(syncSendSmPtr->TxIntervalCnt == 0)
        {
          EthTSyn_Master_SyncSendSm_SendSync(PortIdx, FALSE);
        } /* END: if(EthTSyn_SyncSendSm(PortIdx).TxIntervalCnt == 0) */
        break;
      }

    case ETHTSYN_S_SYNC_SEND_SM_TX_SYNC:
      {
        /* #202 State: Send Sync -> Transmit sync message. */
        EthTSyn_Master_SyncSendSm_SendSync(PortIdx, FALSE);
        break;
      }

    case ETHTSYN_S_SYNC_SEND_SM_TX_IMMEDIATE_SYNC:
      {
        /* #203 State: Send Immediate Sync -> Transmit sync message. */
        EthTSyn_Master_SyncSendSm_SendSync(PortIdx, TRUE);
        break;
      }

    case ETHTSYN_S_SYNC_SEND_SM_TX_FUP:
      {
        /* #204 State: Send FollowUp -> Transmit follow up message. */
        /* #2040 Check if TxConfirmation for sent Sync message occurred */
        if(syncSendSmPtr->TxConfirmationPending == 0)
        {
          /* #2041 Check if Sync cycle already expired. If so, increment sequence id and change state to TX_SYNC. */
          if(syncSendSmPtr->TxIntervalCnt == 0)
          {
            syncSendSmPtr->SequenceId++;                                                                               /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
            syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_TX_SYNC;                                                     /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
          }
          /* #2042 Transmit follow up message otherwise. */
          else
          {
            EthTSyn_Master_SyncSendSm_SendFup(PortIdx);
          }
        }
        break;
      }

    default:
      {
        /* Nothing to do here. */;
        break;
      }

    } /* END: Switch(SyncSendSm State) */
  } /* END: If MasterPort */

} /* EthTSyn_Master_ProcessSmSyncSend() */ /* PRQA S 6030 */ /* MD_MSR_STCYC */

/**********************************************************************************************************************
 *  EthTSyn_Master_HandleCyclicTasks
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
FUNC(void, ETHTSYN_CODE) EthTSyn_Master_HandleCyclicTasks(EthTSyn_TimeDomainIterType TimeDomainIdx)
{
  /* ----- Implementation ----------------------------------------------- */
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
  ETHTSYN_CONSTP2VAR(EthTSyn_TimeDomainStateType) timeDomainStatePtr = EthTSyn_GetAddrTimeDomainState(TimeDomainIdx);
  /* #10 Check that TimeDomain is not a Bridge TimeDomain */
  if(timeDomainStatePtr->SlavePortIdx >= EthTSyn_GetSizeOfSlavePort())
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
  {
    EthTSyn_MasterPortIterType masterPortIter;
    /* #20 Check if immediate time sync is required. */
    const boolean triggerImmediateTimeSync = EthTSyn_Master_IsImmediateTimeSyncRequired(TimeDomainIdx);

    /* ----- Implementation ----------------------------------------------- */
    /* #30 Iterate all master ports. */
    for(masterPortIter = EthTSyn_GetMasterPortStartIdxOfTimeDomain(TimeDomainIdx);
        masterPortIter < EthTSyn_GetMasterPortEndIdxOfTimeDomain(TimeDomainIdx);
        masterPortIter++)
    {
      const EthTSyn_IntPortIdxType portIdx = (EthTSyn_IntPortIdxType)EthTSyn_GetPortIdxOfMasterPort(masterPortIter);
      /* #40 Check if Port is Tx ready */
      if(EthTSyn_IsTxReady(portIdx) == TRUE)
      {
        EthTSyn_SyncSendSmPtrType syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIter);
        /* #50 Handle timer/counter of the Port */
        ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
        if(syncSendSmPtr->TxIntervalCnt > 0)
        {
          syncSendSmPtr->TxIntervalCnt--;                                                                              /* SBSW_ETHTSYN_CSL02 */
        }

        /* #60 Handle immediate time sync. */
        if((triggerImmediateTimeSync == TRUE) && (EthTSyn_IsImmediateTimeSyncOfMasterPort(masterPortIter) == TRUE)) /* PRQA S 3415 */ /* MD_EthTSyn_3415_CslReadOnly */
        {
          syncSendSmPtr->State = ETHTSYN_S_SYNC_SEND_SM_TX_IMMEDIATE_SYNC;                                             /* SBSW_ETHTSYN_CSL02 */
        }
        ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
        /* #70 Process SyncSend state-machine */
        EthTSyn_Master_ProcessSmSyncSend(portIdx);
      }
    } /* END: Iteration of MasterPorts */
  }

} /* EthTSyn_Master_HandleCyclicTasks() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

# define ETHTSYN_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */

/* Justification for module-specific MISRA deviations:
 * see file EthTSyn.c
*/

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Master_Int.c
 *********************************************************************************************************************/
