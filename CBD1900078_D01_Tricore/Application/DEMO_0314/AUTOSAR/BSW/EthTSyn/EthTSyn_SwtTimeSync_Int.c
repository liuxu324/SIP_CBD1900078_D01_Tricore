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
/**        \file  EthTSyn_SwtTimeSync_Int.c
 *        \brief  EthTSyn Switch Time Sync source file - Internal functions
 *
 *      \details  EthTSyn Switch Time Sync source file containing the EthTSyn Switch Time Sync implementation of the
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

#define ETHTSYN_SWT_TIME_SYNC_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EthTSyn_SwtTimeSync_Int.h" /* PRQA S 0777 */ /* MD_MSR_5.1_777 */

#if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
# if (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON)
#  include "EthTSyn_Int.h" /* PRQA S 3219, 0883 */ /* MD_EthTSyn_3219, MD_EthTSyn_0883 */
#  include "EthTSyn_Pdelay_Int.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of EthTSyn header file */
#  if (  (ETHTSYN_SW_MAJOR_VERSION != (7u)) \
      || (ETHTSYN_SW_MINOR_VERSION != (0u)) \
      || (ETHTSYN_SW_PATCH_VERSION != (0u)) )
#   error "Vendor specific version numbers of EthTSyn_SwtTimeSync_Int.c and EthTSyn.h are inconsistent"
#  endif

/* Check the version of the configuration header file */
#  if (  (ETHTSYN_CFG_MAJOR_VERSION != (7u)) \
      || (ETHTSYN_CFG_MINOR_VERSION != (0u)) )
#   error "Version numbers of EthTSyn_SwtTimeSync_Int.c and EthTSyn_Cfg.h are inconsistent!"
#  endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#  define ETHTSYN_SWT_TIME_SYNC_OUT_OF_SYNC_COUNT_MAX_ALLOWED_VALUE (255u)

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#  if !defined (ETHTSYN_LOCAL)
#   define ETHTSYN_LOCAL static
#  endif

#  if !defined (ETHTSYN_LOCAL_INLINE)
#   define ETHTSYN_LOCAL_INLINE LOCAL_INLINE
#  endif

 /* EthTSyn_SwtTimeSync_CorrActionType. */
 /* Bit-Masks */
 /*
 * +---------------------------------------------------+
 * |R|R|R|R|R|RateRegulatorRateRatio|GmRateRatio|Offset|
 * +---------------------------------------------------+
 * Allowed values (x - Don't care):
 * +---------------------------------+
 * | RateRegulator|GmRateRatio|Offset|
 * +---------------------------------+
 * |      0       |     0     |   0  | <- None
 * |      0       |     0     |   1  | <- Offset
 * |      0       |     1     |   0  | <- GmRateRatio
 * |      0       |     1     |   1  | <- OffsetAndGmRateRatio
 * |      1       |     x     |   x  | <- RateRegulator
 * +--------------+-----------+------+
 */
typedef uint8 EthTSyn_SwtTimeSync_CorrActionType;
/* Use mask only to check which corr action should be performed. */
#  define ETHTSYN_SWT_TIME_SYNC_CORR_ACTION_OFFSET_MASK         (0x01u)
#  define ETHTSYN_SWT_TIME_SYNC_CORR_ACTION_GM_RATE_MASK        (0x02u)
#  define ETHTSYN_SWT_TIME_SYNC_CORR_ACTION_RR_RATE_MASK        (0x04u)
/* Only use this value defines for initializing/setting a variable */
#  define ETHTSYN_SWT_TIME_SYNC_CORR_ACTION_NONE                (0x00u)
#  define ETHTSYN_SWT_TIME_SYNC_CORR_ACTION_OFFSET              (0x01u)
#  define ETHTSYN_SWT_TIME_SYNC_CORR_ACTION_GM_RATE             (0x02u)
#  define ETHTSYN_SWT_TIME_SYNC_CORR_ACTION_OFFSET_AND_GM_RATE  (0x03u)
#  define ETHTSYN_SWT_TIME_SYNC_CORR_ACTION_RATE_REGULATOR      (0x04u)

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#  define ETHTSYN_START_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_InitTimeStampInfo
 *********************************************************************************************************************/
/*! \brief      Initializes the passed timestamp information.
 *  \details    -
 *  \param[out] TimeStampInfoPtr   The initialized timestamp information
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_InitTimeStampInfo(
  ETHTSYN_P2VAR(EthTSyn_SwtTimeSync_TimestampInfoStructType) TimeStampInfoPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_HandleSwtSyncFrame
 *********************************************************************************************************************/
/*! \brief      Handles the switch sync frame.
 *  \details    -
 *  \param[in]  SwtSyncFrameCfgIdx   Index of the switch sync frame configuration
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_HandleSwtSyncFrame(
  EthTSyn_SizeOfSwitchSyncFrameCfgType SwtSyncFrameCfgIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_HandleSyncEventTimeout
 *********************************************************************************************************************/
/*! \brief      Handles the optional sync event timeout of the passed switch cascade.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx   Index of the switch cascade in context of the EthTSyn
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_HandleSyncEventTimeout(
  EthTSyn_SwitchTimeSyncCfgIterType SwtTimeSyncCfgIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_HandleSwtTimeSync
 *********************************************************************************************************************/
/*! \brief      Handles the time synchronization of the passed switch cascade.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx   Index of the switch cascade in context of the EthTSyn
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_HandleSwtTimeSync(
  EthTSyn_SwitchTimeSyncCfgIterType SwtTimeSyncCfgIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ComputeSwtOffset
 *********************************************************************************************************************/
/*! \brief      Computes the offset of the passed switch cascade.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx   Index of the switch cascade in context of the EthTSyn
 *  \param[out] SwtOffsetPtr        The computed offset of the switch cascade.
 *                                  Note: Valid for return value of E_OK.
 *  \return     E_OK - Offset calculation succeeded
 *  \return     E_NOT_OK - Offset calculation failed
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ComputeSwtOffset(
                EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  ETHTSYN_P2VAR(EthTSyn_TimediffType)               SwtOffsetPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_CalculateSyncState
 *********************************************************************************************************************/
/*! \brief      Gets the sync state of the passed switch cascade depending on the passed offset.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx   Index of the switch cascade in context of the EthTSyn
 *  \param[in]  SwtOffset           Current offset of the switch cascade.
 *  \return     The sync state.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncStateType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_CalculateSyncState(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  EthTSyn_TimediffType                SwtOffset);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_GetRequiredCorrActions
 *********************************************************************************************************************/
/*! \brief      Gets the required correction actions.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx   Index of the switch cascade in context of the EthTSyn
 *  \param[in]  SwtSyncState        Current sync state of the switch cascade.
 *  \return     The required correction actions.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtTimeSync_CorrActionType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_GetRequiredCorrActions(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  EthTSyn_SyncStateType               SwtSyncState);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_HandleOutOfSyncCounter
 *********************************************************************************************************************/
/*! \brief      Handles the out of sync counter depending on the passed sync state.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx   Index of the switch cascade in context of the EthTSyn
 *  \param[in]  SwtSyncState        Current sync state of the switch cascade.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_HandleOutOfSyncCounter(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  EthTSyn_SyncStateType               SwtSyncState);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ApplyNewSyncState
 *********************************************************************************************************************/
/*! \brief      Sets the new switch sync state and optionally informs the user about a change of the sync state.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx   Index of the switch cascade in context of the EthTSyn
 *  \param[in]  NewSyncState        The new sync state of the switch cascade.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ApplyNewSyncState(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  EthTSyn_SyncStateType               NewSyncState);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ComputeRateRatio
 *********************************************************************************************************************/
/*! \brief      Checks if rate ratio is required and optionally computes it.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx   Index of the switch cascade in context of the EthTSyn
 *  \param[in]  SwtOffset           The current valid offset of the switch cascade
 *  \param[in]  RequiredCorrActions The correction actions which are required for the current sync event
 *  \param[out] SwtRateRatioPtr     The computed RateRatio (valid for return value E_OK)
 *  \return     E_OK - RateRatio required and computation succeeded
 *  \return     E_NOT_OK - RateRatio not required or computation failed
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ComputeRateRatio(
                EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
                EthTSyn_TimediffType                SwtOffset,
                EthTSyn_SwtTimeSync_CorrActionType  RequiredCorrActions,
  ETHTSYN_P2VAR(float64)                            SwtRateRatioPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ComputeMasterAndSwitchTimeDiff
 *********************************************************************************************************************/
/*! \brief      Computes the master and switch time diffs of two consecutive sync events if possible.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx Index of the switch cascade in context of the EthTSyn
 *  \param[out] MasterTimeDiffPtr The computed master time diff (valid for return value E_OK)
 *  \param[out] SwtTimeDiffPtr    The computed switch time diff (valid for return value E_OK)
 *  \return     E_OK - Computation of time differences succeeded
 *  \return     E_NOT_OK - Computation of time differences not possible or failed
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ComputeMasterAndSwitchTimeDiff(
                EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  ETHTSYN_P2VAR(EthTSyn_TimediffType)               MasterTimeDiffPtr,
  ETHTSYN_P2VAR(EthTSyn_TimediffType)               SwtTimeDiffPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ComputeGmRateRatio
 *********************************************************************************************************************/
/*! \brief      Computes the grand master rate ratio.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx   Index of the switch cascade in context of the EthTSyn
 *  \param[in]  MasterTimeDiff      The time passed between two consecutive sync events in the time master
 *                                  [range: MasterTimeDiff > 0]
 *  \param[in]  SwtTimeDiff         The time passed between two consecutive sync events in the switch
 *                                  [range: SwtTimeDiff > 0]
 *  \return     The computed grand master RateRatio
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(float64, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ComputeGmRateRatio(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  EthTSyn_TimediffType                MasterTimeDiff,
  EthTSyn_TimediffType                SwtTimeDiff);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ComputeRegulatorRateRatio
 *********************************************************************************************************************/
/*! \brief      Computes the rate regulator rate ratio.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx   Index of the switch cascade in context of the EthTSyn
 *  \param[in]  SwtOffset           The current valid offset of the switch cascade
 *  \param[in]  MasterTimeDiff      The time passed between two consecutive sync events in the time master
 *                                  [range: MasterTimeDiff > 0]
 *  \param[in]  SwtTimeDiff         The time passed between two consecutive sync events in the switch
 *                                  [range: SwtTimeDiff > 0]
 *  \return     The computed rate regulator RateRatio
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(float64, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ComputeRegulatorRateRatio(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  EthTSyn_TimediffType                SwtOffset,
  EthTSyn_TimediffType                MasterTimeDiff,
  EthTSyn_TimediffType                SwtTimeDiff);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SetSwitchCorrectionTime
 *********************************************************************************************************************/
/*! \brief      Applies the time corrections to the switch cascade.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx   Index of the switch cascade in context of the EthTSyn
 *  \param[in]  SwtOffsetPtr        The offset to be applied or NULL_PTR
 *  \param[in]  RateRatioPtr        The rate ratio to be applied or NULL_PTR
 *  \return     E_OK - Successfully applied corrections to switch cascade
 *  \return     E_NOT_OK - Failed to apply corrections to switch cascade
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SetSwitchCorrectionTime(
                  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  ETHTSYN_P2CONST(EthTSyn_TimediffType)               SwtOffsetPtr,
  ETHTSYN_P2CONST(float64)                            SwtRateRatioPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_TimeDiffToTimeIntDiff
 *********************************************************************************************************************/
/*! \brief      Converts the passed time difference into the AUTOSAR format (TimeIntDiffType).
 *  \details    -
 *  \param[in]  TimeDiff   The TimeDiff to convert
 *  \return     TimeDiff converted to TimeIntDiff
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TimeIntDiffType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_TimeDiffToTimeIntDiff(
  EthTSyn_TimediffType TimeDiff);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_StoreTimestamps
 *********************************************************************************************************************/
/*! \brief      Stores the passed switch timestamps in the passed switch time sync info and updates the state.
 *  \details    -
 *  \param[in]  SwtTimeSyncCfgIdx          Index of the switch cascade in context of the EthTSyn
 *  \param[in]  SequenceId                 The sequence id of the corresponding sync event
 *  \param[in]  PreciseOriginTimestampPtr  The precise origin timestamp of the sync event
 *  \param[in]  SyncIngressTimestamp       The switch sync ingress timestamp
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch cascades
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_StoreTimestamps(
                  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
                  uint16                              SequenceId,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType)        PreciseOriginTimestampPtr,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType)        SyncIngressTimestamp);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SwtSyncFrameTrigger
 *********************************************************************************************************************/
/*! \brief      Triggers the transmission of a switch sync frame.
 *  \details    -
 *  \param[in]  SwtSyncFrameCfgIdx   Index of the switch sync frame.
 *  \return     E_OK - Switch sync frame triggered successfully
 *  \return     E_NOT_OK - Failed to trigger switch sync frame
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch sync frames
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SwtSyncFrameTrigger(
  EthTSyn_SwitchSyncFrameCfgIdxOfSwitchTimeSyncCfgType SwtSyncFrameCfgIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SwtSyncFrameProvideTimestamps
 *********************************************************************************************************************/
/*! \brief      Provides the timestamps of the passed switch sync frame.
 *  \details    Checks for available of the timestamps of the passed switch sync frame. If available, the timestamps
 *              are provided to the corresponding switch cascade for later time synchronization of the switch cascade.
 *  \param[in]  SwtSyncFrameCfgIdx   Index of the switch sync frame.
 *  \return     E_OK - Timestamps of switch sync frame ready to process and provided in case they where available.
 *  \return     E_NOT_OK - Timestamps of switch sync frame not yet ready to process. Retry again later.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different switch sync frames
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SwtSyncFrameProvideTimestamps(
  EthTSyn_SwitchSyncFrameCfgIdxOfSwitchTimeSyncCfgType SwtSyncFrameCfgIdx); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

#  if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SwtSyncFrameHwTimestampCorrectPot
 *********************************************************************************************************************/
/*! \brief         Corrects the precise origin timestamp of a transmitted switch sync frame if HW timestamping is used.
 *  \details       -
 *  \param[in]     EthIfCtrlIdx               Index of the switch sync frame.
 *  \param[in]     BufIdx                     Index of the transmission buffer
 *  \param[in,out] PreciseOriginTimestampPtr  In:  The precise origin timestamp
 *                                            Out: The corrected precise origin timestamp
 *  \pre           Has to be called in the context of the TxConfirmation
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different switch sync frames
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SwtSyncFrameHwTimestampCorrectPot(
                uint8                        EthIfCtrlIdx,
                uint8                        BufIdx,
  ETHTSYN_P2VAR(EthTSyn_GlobalTimestampType) PreciseOriginTimestampPtr); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#  endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_InitTimeStampInfo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_InitTimeStampInfo(
  ETHTSYN_P2VAR(EthTSyn_SwtTimeSync_TimestampInfoStructType) TimeStampInfoPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set all values of the passed TimeStampInfo to zero. */
  TimeStampInfoPtr->SequenceId = 0u;

  TimeStampInfoPtr->PreciseOriginTimestamp.secondsHi = 0u;
  TimeStampInfoPtr->PreciseOriginTimestamp.seconds = 0u;
  TimeStampInfoPtr->PreciseOriginTimestamp.nanoseconds = 0u;

  TimeStampInfoPtr->SyncIngressTimestamp.secondsHi = 0u;
  TimeStampInfoPtr->SyncIngressTimestamp.seconds = 0u;
  TimeStampInfoPtr->SyncIngressTimestamp.nanoseconds = 0u;
} /* EthTSyn_SwtTimeSync_InitTimeStampInfo() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_HandleSwtSyncFrame
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_HandleSwtSyncFrame(
  EthTSyn_SizeOfSwitchSyncFrameCfgType SwtSyncFrameCfgIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if switch sync frame mechanism is running. */
  if(EthTSyn_IsRunningOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx) == TRUE)
  {
    /* #20 Handle switch sync frame tx cycle timer. */
    if(EthTSyn_GetSyncTxCntOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx) > 0u)
    {
      EthTSyn_DecSyncTxCntOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx);

      /* #200 Trigger switch sync frame if tx cycle timer expired. */
      if(EthTSyn_GetSyncTxCntOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx) == 0u)
      {
        if(EthTSyn_SwtTimeSync_SwtSyncFrameTrigger(SwtSyncFrameCfgIdx) == E_NOT_OK)
        {
          /* #2001 Retry transmission of switch sync frame in next MainFunction in case of failure. */
          EthTSyn_IncSyncTxCntOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx);
        }
      }
    }
    else
    {
      /* #30 Switch sync frame was already transmitted. Check for availability of the timestamps and store them for
      later synchronization of the switch. */
      if(EthTSyn_SwtTimeSync_SwtSyncFrameProvideTimestamps(SwtSyncFrameCfgIdx) == E_OK)
      {
        /* #300 Reset switch sync frame tx cycle in case timestamps where available. */
        EthTSyn_SetSyncTxCntOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx,
          EthTSyn_GetSyncTxIntervalOfSwitchSyncFrameCfg(SwtSyncFrameCfgIdx));
      }
    }
  }
} /* EthTSyn_SwtTimeSync_HandleSwtSyncFrame() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_HandleSyncEventTimeout
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_HandleSyncEventTimeout(
  EthTSyn_SwitchTimeSyncCfgIterType SwtTimeSyncCfgIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle sync event timeout. */
  if(EthTSyn_GetSyncEventTimeoutOfSwitchTimeSyncCfg(SwtTimeSyncCfgIdx) > 0u)
  {
    if(EthTSyn_GetSyncEventTimeoutCntOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx) > 0u)
    {
      EthTSyn_DecSyncEventTimeoutCntOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx);
    }
    if(EthTSyn_GetSyncEventTimeoutCntOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx) == 0u)
    {
      EthTSyn_SwtTimeSync_ApplyNewSyncState(SwtTimeSyncCfgIdx, ETHTSYN_UNCERTAIN);
    }
  }
} /* EthTSyn_SwtTimeSync_HandleSyncEventTimeout */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_HandleSwtTimeSync
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_HandleSwtTimeSync(
  EthTSyn_SwitchTimeSyncCfgIterType SwtTimeSyncCfgIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_P2CONST(EthTSyn_TimediffType) swtOffsetPtr = NULL_PTR;
  ETHTSYN_P2CONST(float64) swtRateRatioPtr = NULL_PTR;
  EthTSyn_TimediffType swtOffset = 0;
  float64 swtRateRatio = 1.0;
  EthTSyn_SyncStateType newSwtSyncState;

  /* ----- Implementation ----------------------------------------------- */
  ETHTSYN_ENTER_CRITICAL_SECTION_0();
  /* #10 Check if synchronization event occurred. */
  if((EthTSyn_GetStateOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx) == ETHTSYN_WAIT_SECOND_STATEOFSWITCHTIMESYNCINFO) || /* PRQA S 3415 */ /* MD_EthTSyn_3415_CslReadOnly */
    (EthTSyn_GetStateOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx) == ETHTSYN_READY_STATEOFSWITCHTIMESYNCINFO))
  {
    /* #20 Try to compute current switch offset. */
    if(EthTSyn_SwtTimeSync_ComputeSwtOffset(SwtTimeSyncCfgIdx, &swtOffset) == E_OK)
    {
      EthTSyn_SwtTimeSync_CorrActionType requiredCorrActions;

      /* #30 Get the new switch sync state, the required correction actions, handle the out of sync counter and store
       *     the current switch offset. */
      newSwtSyncState = EthTSyn_SwtTimeSync_CalculateSyncState(SwtTimeSyncCfgIdx, swtOffset);
      requiredCorrActions = EthTSyn_SwtTimeSync_GetRequiredCorrActions(SwtTimeSyncCfgIdx, newSwtSyncState);

      EthTSyn_SwtTimeSync_HandleOutOfSyncCounter(SwtTimeSyncCfgIdx, newSwtSyncState);

      EthTSyn_SetCurrentOffsetNsOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx, swtOffset);

      /* #40 Check if offset correction is required. */
      if(EthTSyn_Util_AreBitsSet(requiredCorrActions, ETHTSYN_SWT_TIME_SYNC_CORR_ACTION_OFFSET_MASK) == TRUE)
      {
        /* #400 Offset correction required -> set offset pointer. */
        swtOffsetPtr = &swtOffset;
      }
      /* #50 Compute and use rate ratio if required. */
      if(EthTSyn_SwtTimeSync_ComputeRateRatio(
        SwtTimeSyncCfgIdx, swtOffset, requiredCorrActions, &swtRateRatio) == E_OK)
      {
        /* #500 Rate correction required and computed successfully -> set rate ratio pointer. */
        swtRateRatioPtr = &swtRateRatio;
      }
    }
    else
    {
      /* #200 Set switch sync state to ETHTSYN_UNCERTAIN in case offset calculation failed. */
      newSwtSyncState = ETHTSYN_UNCERTAIN;
    }

    /* #60 Set state of switch time sync info to ETHTSYN_WAIT_STATEOFSWITCHTIMESYNCINFO to wait for next sync event. */
    EthTSyn_SetStateOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx, ETHTSYN_WAIT_STATEOFSWITCHTIMESYNCINFO);
    ETHTSYN_LEAVE_CRITICAL_SECTION_0();

    /* #70 Provide correction information to switch if any correction is required. */
    if((swtRateRatioPtr != NULL_PTR) || (swtOffsetPtr != NULL_PTR))
    {
      if(EthTSyn_SwtTimeSync_SetSwitchCorrectionTime(SwtTimeSyncCfgIdx, swtOffsetPtr, swtRateRatioPtr) == E_NOT_OK)
      {
        /* #700 Correction failed -> set sync state to ETHTSYN_UNCERTAIN. */
        newSwtSyncState = ETHTSYN_UNCERTAIN;
      }
    }

    /* #80 Set new sync state of the switch cascade. */
    EthTSyn_SwtTimeSync_ApplyNewSyncState(SwtTimeSyncCfgIdx, newSwtSyncState);
  }
  else
  {
    ETHTSYN_LEAVE_CRITICAL_SECTION_0();
  }
} /* EthTSyn_SwtTimeSync_HandleSwtTimeSync() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ComputeSwtOffset
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ComputeSwtOffset(
                EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  ETHTSYN_P2VAR(EthTSyn_TimediffType)               SwtOffsetPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwtTimeSync_TimestampInfoStructType tsInfo;

  /* ----- Implementation ----------------------------------------------- */
  tsInfo = EthTSyn_GetTimeStampInfoOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx);

  /* #10 Compute switch offset. */
  return EthTSyn_Util_TimestampMinusTimestamp(
    &tsInfo.PreciseOriginTimestamp,
    &tsInfo.SyncIngressTimestamp,
    SwtOffsetPtr);
} /* EthTSyn_SwtTimeSync_ComputeSwtOffset() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_CalculateSyncState
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SyncStateType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_CalculateSyncState(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  EthTSyn_TimediffType                SwtOffset)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_UTimediffType unsignedSwtOffset =
    ((SwtOffset < 0) ? ((EthTSyn_UTimediffType)(-SwtOffset)) : ((EthTSyn_UTimediffType)SwtOffset));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Return ETHTSYN_SYNC in case SwtOffset <= SyncPrecisionLimit otherwise return ETHTSYN_UNSYNC. */
  return (
    (unsignedSwtOffset <= EthTSyn_GetSyncPrecisionLimitNsOfSwitchTimeSyncCfg(SwtTimeSyncCfgIdx)) ?
    ETHTSYN_SYNC :
    ETHTSYN_UNSYNC);
} /* EthTSyn_SwtTimeSync_CalculateSyncState() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_GetRequiredCorrActions
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
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_SwtTimeSync_CorrActionType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_GetRequiredCorrActions(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  EthTSyn_SyncStateType               SwtSyncState)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwtTimeSync_CorrActionType requiredCorrActions;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 In case sync state is ETHTSYN_UNSYNC. */
  if(SwtSyncState == ETHTSYN_UNSYNC)
  {
    /* #100 Check if offset correction should be used when sync state was not reached yet. */
    if((EthTSyn_IsUseInitialOffsetCorrectionOfSwtTimeSyncRateRegulatorCfg(SwtTimeSyncCfgIdx) == TRUE) && /* PRQA S 3415 */ /* MD_EthTSyn_3415_CslReadOnly */
      (EthTSyn_IsWasSyncReachedOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx) == FALSE))
    {
      /* #1000 Rate ratio and offset correction is required. */
      requiredCorrActions = ETHTSYN_SWT_TIME_SYNC_CORR_ACTION_OFFSET_AND_GM_RATE;
    }
    else
    {
      /* #1001 Rate regulator is required. */
      requiredCorrActions = ETHTSYN_SWT_TIME_SYNC_CORR_ACTION_RATE_REGULATOR;
    }
  }
  /* #20 In case of any other sync state. */
  else
  {
    /* #200 Rate regulator is required. */
    requiredCorrActions = ETHTSYN_SWT_TIME_SYNC_CORR_ACTION_RATE_REGULATOR;
  }

  return requiredCorrActions;
} /* EthTSyn_SwtTimeSync_GetRequiredCorrActions() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_HandleOutOfSyncCounter
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_HandleOutOfSyncCounter(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  EthTSyn_SyncStateType               SwtSyncState)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset out of sync counter in case of ETHTSYN_SYNC.*/
  if(SwtSyncState == ETHTSYN_SYNC)
  {
    EthTSyn_SetOutOfSyncCntOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx, 0u);
  }
  /* #20 Increment out of sync counter in case of ETHTSYN_UNSYNC. */
  else if(SwtSyncState == ETHTSYN_UNSYNC)
  {
    if(EthTSyn_GetOutOfSyncCntOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx) <
      ETHTSYN_SWT_TIME_SYNC_OUT_OF_SYNC_COUNT_MAX_ALLOWED_VALUE)
    {
      EthTSyn_IncOutOfSyncCntOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx);
    }
  }
  /* #30 Otherwise do nothing. */
  else
  {
    /* Nothing to do here. */
  }
} /* EthTSyn_SwtTimeSync_HandleOutOfSyncCounter() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ApplyNewSyncState
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
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ApplyNewSyncState(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  EthTSyn_SyncStateType               NewSyncState)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SyncStateType syncStateToSet = EthTSyn_GetSwtSyncStateOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 In case of NewSyncState is ETHTSYN_UNSYNC, only set the new state if max out of sync count expired. */
  if(NewSyncState == ETHTSYN_UNSYNC)
  {
    if(EthTSyn_GetOutOfSyncCntOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx) >=
      EthTSyn_GetMaxOutOfSyncCntOfSwitchTimeSyncCfg(SwtTimeSyncCfgIdx))
    {
      syncStateToSet = ETHTSYN_UNSYNC;
    }
  }
  /* #20 Otherwise apply the new sync state. */
  else
  {
    syncStateToSet = NewSyncState;
    /* #200 Mark as sync was reached in case of ETHTSYN_SYNC. */
    if(NewSyncState == ETHTSYN_SYNC)
    {
      EthTSyn_SetWasSyncReachedOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx, TRUE);
    }
  }

  /* #30 Trigger sync state change user notification in case it is enabled and the sync state has changed. */
  if(EthTSyn_GetSwtSyncStateChgFctPtrOfSwitchTimeSyncCfg(SwtTimeSyncCfgIdx) != NULL_PTR)
  {
    if(EthTSyn_GetSwtSyncStateOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx) != syncStateToSet)
    {
      EthTSyn_GetSwtSyncStateChgFctPtrOfSwitchTimeSyncCfg(SwtTimeSyncCfgIdx)(SwtTimeSyncCfgIdx, NewSyncState);
    }
  }

  /* #40 Set the new sync state in the switch time sync info. */
  EthTSyn_SetSwtSyncStateOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx, syncStateToSet);

} /* EthTSyn_SwtTimeSync_ApplyNewSyncState() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ComputeRateRatio
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ComputeRateRatio(
                EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
                EthTSyn_TimediffType                SwtOffset,
                EthTSyn_SwtTimeSync_CorrActionType  RequiredCorrActions,
  ETHTSYN_P2VAR(float64)                            SwtRateRatioPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if rate ratio is required according to required correction actions. */
  if((EthTSyn_Util_AreBitsSet(RequiredCorrActions, ETHTSYN_SWT_TIME_SYNC_CORR_ACTION_GM_RATE_MASK) == TRUE) || /* PRQA S 3415 */ /* MD_EthTSyn_3415_ReadOnly */
    (EthTSyn_Util_AreBitsSet(RequiredCorrActions, ETHTSYN_SWT_TIME_SYNC_CORR_ACTION_RR_RATE_MASK) == TRUE))
  {
    EthTSyn_TimediffType masterTimeDiff = 0;
    EthTSyn_TimediffType swtTimeDiff = 0;

    /* #20 Compute master and switch time differences of two consecutive sync events. */
    if(EthTSyn_SwtTimeSync_ComputeMasterAndSwitchTimeDiff(SwtTimeSyncCfgIdx, &masterTimeDiff, &swtTimeDiff) == E_OK)
    {
      retVal = E_OK;

      /* #30 Compute grand master rate ratio if required. */
      if(EthTSyn_Util_AreBitsSet(RequiredCorrActions, ETHTSYN_SWT_TIME_SYNC_CORR_ACTION_GM_RATE_MASK) == TRUE)
      {
        (*SwtRateRatioPtr) = EthTSyn_SwtTimeSync_ComputeGmRateRatio(SwtTimeSyncCfgIdx, masterTimeDiff, swtTimeDiff);
      }
      /* #40 Compute rate regulator rate ratio otherwise. */
      else
      {
        (*SwtRateRatioPtr) = EthTSyn_SwtTimeSync_ComputeRegulatorRateRatio(
          SwtTimeSyncCfgIdx,
          SwtOffset,
          masterTimeDiff,
          swtTimeDiff);
      }
    }
  }

  return retVal;
} /* EthTSyn_SwtTimeSync_ComputeRateRatio() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ComputeMasterAndSwitchTimeDiff
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
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ComputeMasterAndSwitchTimeDiff(
                EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  ETHTSYN_P2VAR(EthTSyn_TimediffType)               MasterTimeDiffPtr,
  ETHTSYN_P2VAR(EthTSyn_TimediffType)               SwtTimeDiffPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  ETHTSYN_ENTER_CRITICAL_SECTION_0();
  /* #10 Check if calculation of time difference is possible according to switch time sync info state. */
  if(EthTSyn_GetStateOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx) == ETHTSYN_READY_STATEOFSWITCHTIMESYNCINFO)
  {
    ETHTSYN_P2CONST(EthTSyn_SwtTimeSync_TimestampInfoStructType) timeStampInfoPtr =
      EthTSyn_GetAddrTimeStampInfoOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx);
    ETHTSYN_P2CONST(EthTSyn_SwtTimeSync_TimestampInfoStructType) prevTimeStampInfoPtr =
      EthTSyn_GetAddrPrevTimeStampInfoOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx);

    /* #20 Ensure that two consecutive sync events occurred. */
    if(timeStampInfoPtr->SequenceId == (prevTimeStampInfoPtr->SequenceId + 1))
    {
      EthTSyn_TimediffType masterTimeDiff = 0;
      EthTSyn_TimediffType swtTimeDiff = 0;

      /* #30 Compute master and switch time diff between two consecutive sync event. */
      retVal = E_OK;
      retVal |= EthTSyn_Util_TimestampMinusTimestamp(&timeStampInfoPtr->PreciseOriginTimestamp,
        &prevTimeStampInfoPtr->PreciseOriginTimestamp, &masterTimeDiff);
      retVal |= EthTSyn_Util_TimestampMinusTimestamp(&timeStampInfoPtr->SyncIngressTimestamp,
        &prevTimeStampInfoPtr->SyncIngressTimestamp, &swtTimeDiff);

      /* #40 If calculation of both time differences succeeded, adapt switch time diff by last corrected offset. */
      if(retVal == E_OK)
      {
        swtTimeDiff -= EthTSyn_GetLastCorrectedOffsetNsOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx);
        EthTSyn_SetLastCorrectedOffsetNsOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx, 0);

        /* #60 Ensure causality of the time diffs. */
        if((masterTimeDiff > 0) && (swtTimeDiff > 0))
        {
          (*MasterTimeDiffPtr) = masterTimeDiff;
          (*SwtTimeDiffPtr) = swtTimeDiff;
        }
        else
        {
          retVal = E_NOT_OK;
        }
      }
    }
  }
  ETHTSYN_LEAVE_CRITICAL_SECTION_0();

  return retVal;
} /* EthTSyn_SwtTimeSync_ComputeMasterAndSwitchTimeDiff() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ComputeGmRateRatio
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(float64, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ComputeGmRateRatio(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  EthTSyn_TimediffType                MasterTimeDiff,
  EthTSyn_TimediffType                SwtTimeDiff)
{
  /* ----- Local Variables ---------------------------------------------- */
  float64 swtRateRatio;
  const EthTSyn_SwtTimeSyncRateRegulatorCfgIdxOfSwitchTimeSyncCfgType rateRegultorIdx =
    EthTSyn_GetSwtTimeSyncRateRegulatorCfgIdxOfSwitchTimeSyncCfg(SwtTimeSyncCfgIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Compute grand master rate ratio as MasterTimeDiff/SwtTimeDiff. */
  swtRateRatio = ((float64)MasterTimeDiff) / ((float64)SwtTimeDiff);

  /* #20 Apply rate boundaries. */
  if(swtRateRatio > EthTSyn_GetRateRatioMaxOfSwtTimeSyncRateRegulatorCfg(rateRegultorIdx))
  {
    swtRateRatio = EthTSyn_GetRateRatioMaxOfSwtTimeSyncRateRegulatorCfg(rateRegultorIdx);
  }
  else if(swtRateRatio < EthTSyn_GetRateRatioMinOfSwtTimeSyncRateRegulatorCfg(rateRegultorIdx))
  {
    swtRateRatio = EthTSyn_GetRateRatioMinOfSwtTimeSyncRateRegulatorCfg(rateRegultorIdx);
  }
  else
  {
    /* RateRatio is within limits. Nothing to do. */
  }

  return swtRateRatio;
} /* EthTSyn_SwtTimeSync_ComputeGmRateRatio() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ComputeRateRegulatorRateRatio
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
ETHTSYN_LOCAL_INLINE FUNC(float64, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ComputeRegulatorRateRatio(
  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  EthTSyn_TimediffType                SwtOffset,
  EthTSyn_TimediffType                MasterTimeDiff,
  EthTSyn_TimediffType                SwtTimeDiff)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_TimediffType adaptedSwtTimeDiff;
  float64 swtRateRatio;
  const EthTSyn_SwtTimeSyncRateRegulatorCfgIdxOfSwitchTimeSyncCfgType rateRegultorIdx =
    EthTSyn_GetSwtTimeSyncRateRegulatorCfgIdxOfSwitchTimeSyncCfg(SwtTimeSyncCfgIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Adapt switch time diff to take current offset into account. */
  adaptedSwtTimeDiff = SwtTimeDiff - SwtOffset;

  /* #20 Ensure causality of adapted switch time diff. */
  if(adaptedSwtTimeDiff > 0)
  {
    /* #200 Compute rate regulator rate ratio as MasterTimeDiff/adaptedSwtTimeDiff. */
    swtRateRatio = ((float64)MasterTimeDiff) / ((float64)adaptedSwtTimeDiff);

    /* #201 Apply rate boundaries. */
    if(swtRateRatio > EthTSyn_GetRateRatioMaxOfSwtTimeSyncRateRegulatorCfg(rateRegultorIdx))
    {
      swtRateRatio = EthTSyn_GetRateRatioMaxOfSwtTimeSyncRateRegulatorCfg(rateRegultorIdx);
    }
    else if(swtRateRatio < EthTSyn_GetRateRatioMinOfSwtTimeSyncRateRegulatorCfg(rateRegultorIdx))
    {
      swtRateRatio = EthTSyn_GetRateRatioMinOfSwtTimeSyncRateRegulatorCfg(rateRegultorIdx);
    }
    else
    {
      /* RateRatio is within limits. Nothing to do. */
    }
  }
  /* #30 Switch offset is positive and greater than the sync cycle -> turn up clock speed as much as possible. */
  else
  {
    swtRateRatio = EthTSyn_GetRateRatioMaxOfSwtTimeSyncRateRegulatorCfg(rateRegultorIdx);
  }


  return swtRateRatio;
} /* EthTSyn_SwtTimeSync_ComputeRateRegulatorRateRatio() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SetSwitchCorrectionTime
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
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SetSwitchCorrectionTime(
                  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
  ETHTSYN_P2CONST(EthTSyn_TimediffType)               SwtOffsetPtr,
  ETHTSYN_P2CONST(float64)                            SwtRateRatioPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorCount = 0;
  ETHTSYN_P2CONST(float64) slaveSwtRateRatioPtr = NULL_PTR;
  EthTSyn_TimeIntDiffType swtOffsetAsTimeIntDiff;
  ETHTSYN_P2VAR(EthTSyn_TimeIntDiffType) swtOffsetAsTimeIntDiffPtr = NULL_PTR;
  const uint8 masterSwitchIdx = EthTSyn_GetEthIfSwitchIdxOfSwitchTimeSyncCfg(SwtTimeSyncCfgIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If offset is used, transform it to TimeIntDiffType representation. */
  if(SwtOffsetPtr != NULL_PTR)
  {
    swtOffsetAsTimeIntDiff = EthTSyn_SwtTimeSync_TimeDiffToTimeIntDiff((*SwtOffsetPtr));
    swtOffsetAsTimeIntDiffPtr = &swtOffsetAsTimeIntDiff;
  }

  /* #20 Apply correction values to Master-Switch. */
  if(EthIf_SetSwitchCorrectionTime(masterSwitchIdx, swtOffsetAsTimeIntDiffPtr, SwtRateRatioPtr) == E_OK)
  {
    /* #200 Store corrected offset for later calculation of rate ratio in case of success. */
    if(SwtOffsetPtr != NULL_PTR)
    {
      EthTSyn_SetLastCorrectedOffsetNsOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx, (*SwtOffsetPtr));
    }
  }
  else
  {
    /* #201 Increment errorCount in case any error occurred. */
    errorCount++;
  }

  /* #30 Check if rate ratio has to be applied to slave switches separately. */
  if(EthTSyn_IsApplyRateRatioToSlaveSwitchesOfSwitchTimeSyncCfg(SwtTimeSyncCfgIdx) == TRUE)
  {
    slaveSwtRateRatioPtr = SwtRateRatioPtr;
  }

  /* #40 Check if any correction has to be applied to slave switches. */
  if((slaveSwtRateRatioPtr != NULL_PTR) || (SwtOffsetPtr != NULL_PTR))
  {
    EthTSyn_SlaveSwitchIdxListIterType slaveSwitchIter;
    /* #400 Apply correction to every slave switch. */
    for(slaveSwitchIter = EthTSyn_GetSlaveSwitchIdxListStartIdxOfSwitchTimeSyncCfg(SwtTimeSyncCfgIdx);
      slaveSwitchIter < EthTSyn_GetSlaveSwitchIdxListEndIdxOfSwitchTimeSyncCfg(SwtTimeSyncCfgIdx);
      slaveSwitchIter++)
    {
      const uint8 slaveSwitchIdx = EthTSyn_GetSlaveSwitchIdxList(slaveSwitchIter);
      if(EthIf_SetSwitchCorrectionTime(slaveSwitchIdx, swtOffsetAsTimeIntDiffPtr, slaveSwtRateRatioPtr) == E_NOT_OK)
      {
        /* #401 Increment error counter in case of any error. */
        errorCount++;
      }
    }
  }

  return ((errorCount == 0) ? E_OK : E_NOT_OK);
} /* EthTSyn_SwtTimeSync_SetSwitchCorrectionTime() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_TimeDiffToTimeIntDiff
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(EthTSyn_TimeIntDiffType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_TimeDiffToTimeIntDiff(
  EthTSyn_TimediffType TimeDiff)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_TimeIntDiffType timeIntDiff;
  EthTSyn_UTimediffType uTimeDiff;
  uint64 timeDiffSeconds;
  uint32 timeDiffNanoseconds;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get sign and absolute value of time diff. */
  if(TimeDiff < 0)
  {
    timeIntDiff.sign = FALSE;
    uTimeDiff = (EthTSyn_UTimediffType)(-TimeDiff);
  }
  else
  {
    timeIntDiff.sign = TRUE;
    uTimeDiff = (EthTSyn_UTimediffType)TimeDiff;
  }

  /* #20 Split absolute value of time diff into seconds and nanoseconds. */
  timeDiffSeconds = uTimeDiff / ETHTSYN_NANOSECONDS_PER_SECOND;
  timeDiffNanoseconds = (uint32)(uTimeDiff % ETHTSYN_NANOSECONDS_PER_SECOND);

  /* #30 Transform seconds and nanoseconds part into timestamp format. */
  timeIntDiff.diff.secondsHi = (uint16)(timeDiffSeconds >> 32u);
  timeIntDiff.diff.seconds = (uint32)timeDiffSeconds;
  timeIntDiff.diff.nanoseconds = timeDiffNanoseconds;

  return timeIntDiff;
} /* EthTSyn_SwtTimeSync_TimeDiffToTimeIntDiff() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_StoreTimestamps
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_StoreTimestamps(
                  EthTSyn_SizeOfSwitchTimeSyncCfgType SwtTimeSyncCfgIdx,
                  uint16                              SequenceId,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType)        PreciseOriginTimestampPtr,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType)        SyncIngressTimestamp)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_CONSTP2VAR(EthTSyn_SwtTimeSync_TimestampInfoStructType) timeStampInfoPtr =
    EthTSyn_GetAddrTimeStampInfoOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle the state of the switch time sync info structure. */
  if(EthTSyn_GetStateOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx) == ETHTSYN_WAIT_FIRST_STATEOFSWITCHTIMESYNCINFO)
  {
    EthTSyn_SetStateOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx, ETHTSYN_WAIT_SECOND_STATEOFSWITCHTIMESYNCINFO);
  }
  else
  {
    EthTSyn_SetPrevTimeStampInfoOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx,
      EthTSyn_GetTimeStampInfoOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx));
    EthTSyn_SetStateOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx, ETHTSYN_READY_STATEOFSWITCHTIMESYNCINFO);
  }

  /* #20 Reset sync event timeout. */
  EthTSyn_SetSyncEventTimeoutCntOfSwitchTimeSyncInfo(SwtTimeSyncCfgIdx,
    EthTSyn_GetSyncEventTimeoutOfSwitchTimeSyncCfg(SwtTimeSyncCfgIdx));

  /* #30 Store the switch time stamp information. */
  timeStampInfoPtr->SequenceId = SequenceId;
  timeStampInfoPtr->PreciseOriginTimestamp = (*PreciseOriginTimestampPtr);
  timeStampInfoPtr->SyncIngressTimestamp = (*SyncIngressTimestamp);
} /* EthTSyn_SwtTimeSync_StoreTimestamps() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SwtSyncFrameTrigger
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
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SwtSyncFrameTrigger(
  EthTSyn_SwitchSyncFrameCfgIdxOfSwitchTimeSyncCfgType SwtSyncFrameCfgIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  EthTSyn_EthTxBufferStructType ethTxBuffer;
  const EthTSyn_EthIfCtrlIdxOfSwitchSyncFrameCfgType ethIfCtrlIdx =
    EthTSyn_GetEthIfCtrlIdxOfSwitchSyncFrameCfg(SwtSyncFrameCfgIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get an Ethernet transmission buffer for the switch sync frame. */
  ethTxBuffer.Length = ETHTSYN_MSG_SYNC_LENGTH;
  if(EthTSyn_UtilTx_ProvideTxBuffer(ethIfCtrlIdx, EthTSyn_GetFramePrioOfSwitchSyncFrameCfg(SwtSyncFrameCfgIdx),
    &ethTxBuffer) == E_OK)
  {
    ETHTSYN_P2VAR(EthTSyn_CommonMsgHdrType) comHdrPtr = (ETHTSYN_P2VAR(EthTSyn_CommonMsgHdrType))ethTxBuffer.BufferPtr; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */
    const EthTSyn_SwitchTimeSyncCfgIdxOfSwitchSyncFrameCfgType swtTimeSyncCfgIdx =
      EthTSyn_GetSwitchTimeSyncCfgIdxOfSwitchSyncFrameCfg(SwtSyncFrameCfgIdx);
    const EthTSyn_TimeDomainIdxOfSwitchTimeSyncCfgType timeDomainIdx =
      EthTSyn_GetTimeDomainIdxOfSwitchTimeSyncCfg(swtTimeSyncCfgIdx);
    EthTSyn_SwtMgmtInfoType swtMgmtInfo;

    /* #20 Assemble the switch sync message. */
    /* EthTSyn_UtilTx_PrepareCommonMsgHdr() can't be used here due to different handling for switch sync frame. */
    comHdrPtr->TransSpecific_MessageType = (uint8)(ETHTSYN_HDR_COM_TRANSPORT_SPECIFIC | ETHTSYN_MSG_TYPE_SYNC);
    comHdrPtr->Reserved_VersionGPtp = ETHTSYN_SUPPORTED_PROTOCOL_VERSION;

    comHdrPtr->MessageLength = (uint16)EthTSyn_Htons((uint16)ETHTSYN_MSG_SYNC_LENGTH);
    comHdrPtr->DomainNumber = EthTSyn_GetIdOfTimeDomain(timeDomainIdx);

    comHdrPtr->Flags[0u] = ETHTSYN_FLAGS_OCTET_0_TWO_STEP;

    comHdrPtr->SequenceId = (uint16)EthTSyn_Htons(EthTSyn_GetSequenceIdOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx));
    comHdrPtr->Control = ETHTSYN_HDR_COM_CONTROL_SYNC;

    /* #30 Set switch management info and enable timestamping. */
    swtMgmtInfo.FrameId = ethTxBuffer.FrameId;
    swtMgmtInfo.SwitchIdx = EthTSyn_GetMgmtPortEthIfSwitchIdxOfSwitchSyncFrameCfg(SwtSyncFrameCfgIdx);
    swtMgmtInfo.PortIdx = EthTSyn_GetMgmtPortSwitchPortIdxOfSwitchSyncFrameCfg(SwtSyncFrameCfgIdx);

    if(EthTSyn_UtilTx_PrepareTransmission(ethIfCtrlIdx, ethTxBuffer.BufferIdx, ETHTSYN_ENABLE_TS_HW_AND_SWT_TS,
      &swtMgmtInfo) == E_OK)
    {
      /* #40 Store Tx frame information for later identification. */
      EthTSyn_SetBufIdxOfSwitchSyncFrameTxFrameInfo(SwtSyncFrameCfgIdx, ethTxBuffer.BufferIdx);
      EthTSyn_SetBufAddrOfSwitchSyncFrameTxFrameInfo(SwtSyncFrameCfgIdx, ethTxBuffer.BufferPtr);
      EthTSyn_SetValidOfSwitchSyncFrameTxFrameInfo(SwtSyncFrameCfgIdx, TRUE);
      EthTSyn_GetAddrPreciseOriginTsMgmtOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx)->State =
        ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_WAITING_FOR_TIMESTAMP;
      EthTSyn_GetAddrSwtIngressTsMgmtOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx)->State =
        ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_WAITING_FOR_TIMESTAMP;

      /* #50 Trigger transmission. */
      retVal = EthTSyn_UtilTx_Transmit(ethIfCtrlIdx, ethTxBuffer.BufferIdx, ETHTSYN_MSG_SYNC_LENGTH);
    }

    /* #60 Increment switch sync frame sequence id in case of successful transmission and release Tx buffer and
           invalidate tx frame info otherwise. */
    if(retVal == E_OK)
    {
      EthTSyn_IncSequenceIdOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx);
    }
    else
    {
      EthTSyn_SetValidOfSwitchSyncFrameTxFrameInfo(SwtSyncFrameCfgIdx, FALSE);
      EthTSyn_UtilTx_ReleaseTxBuffer(ethIfCtrlIdx, ethTxBuffer.BufferIdx);
    }
  }

  return retVal;
} /* EthTSyn_SwtTimeSync_SwtSyncFrameTrigger() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SwtSyncFrameProvideTimestamps
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SwtSyncFrameProvideTimestamps(
  EthTSyn_SwitchSyncFrameCfgIdxOfSwitchTimeSyncCfgType SwtSyncFrameCfgIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  ETHTSYN_CONSTP2CONST(EthTSyn_TimestampMgmtStructType) potMgmtPtr =
    EthTSyn_GetAddrPreciseOriginTsMgmtOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx);
  ETHTSYN_CONSTP2CONST(EthTSyn_TimestampMgmtStructType) swtSyncIngTsMgmtPtr =
    EthTSyn_GetAddrSwtIngressTsMgmtOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Verify that precise origin timestamp and switch ingress timestamp of switch sync frame are ready for
         processing. */
  if((EthTSyn_IsTimestampReadyToProcess(potMgmtPtr->State) == TRUE) && /* PRQA S 3415 */ /* MD_EthTSyn_3415_ReadOnly */
    (EthTSyn_IsTimestampReadyToProcess(swtSyncIngTsMgmtPtr->State) == TRUE))
  {
    retVal = E_OK;
    /* #20 Verify that precise origin timestamp and switch ingress timestamp of switch sync frame are available. */
    if((EthTSyn_Util_IsTimestampAvailable(potMgmtPtr->State) == TRUE) && /* PRQA S 3415 */ /* MD_EthTSyn_3415_ReadOnly */
      (EthTSyn_Util_IsTimestampAvailable(swtSyncIngTsMgmtPtr->State) == TRUE))
    {
      /* #30 Store the timestamps and update switch time sync info state. */
      EthTSyn_SwtTimeSync_StoreTimestamps(
        EthTSyn_GetSwitchTimeSyncCfgIdxOfSwitchSyncFrameCfg(SwtSyncFrameCfgIdx),
        EthTSyn_GetSequenceIdOfSwitchSyncFrameInfo(SwtSyncFrameCfgIdx),
        &potMgmtPtr->Timestamp,
        &swtSyncIngTsMgmtPtr->Timestamp);
    }
  }

  return retVal;
} /* EthTSyn_SwtTimeSync_SwtSyncFrameProvideTimestamps() */

#  if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SwtSyncFrameHwTimestampCorrectPot
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SwtSyncFrameHwTimestampCorrectPot(
                uint8                        EthIfCtrlIdx,
                uint8                        BufIdx,
  ETHTSYN_P2VAR(EthTSyn_GlobalTimestampType) PreciseOriginTimestampPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_TimestampQualityType timeQual = ETH_TIMESTAMP_INVALID;
  EthTSyn_GlobalTimestampType syncRefTime;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Try to get the current time as sync reference time. */
  if(EthIf_GetCurrentTime(EthIfCtrlIdx, &timeQual, &syncRefTime) == E_OK)
  {
    if(timeQual == ETH_TIMESTAMP_VALID)
    {
      EthTSyn_GlobalTimestampType syncEgressTs;
      timeQual = ETH_TIMESTAMP_INVALID;

      /* #20 Try to get the egress timestamp of the sync message. */
      if(EthIf_GetEgressTimestamp(EthIfCtrlIdx, BufIdx, &syncEgressTs, &timeQual) == E_OK)
      {
        if(timeQual == ETH_TIMESTAMP_VALID)
        {
          EthTSyn_TimediffType runtime;
          /* #30 Compute runtime of the sync from transmission to this point. */
          if(EthTSyn_Util_TimestampMinusTimestamp(&syncEgressTs, &syncRefTime, &runtime) == E_OK)
          {
            /* #40 Compensate the runtime. */
            /* void-cast is okay:
             * In case of E_OK: PreciseOriginTimestamp was corrected successfully and should be used.
             * In case of E_NOT_OK: PreciseOriginTimestamp was not modified. In this case the original precise origin
             *                      timestamp should be used anyway.*/
            (void)EthTSyn_Util_TimestampPlusTimediff(PreciseOriginTimestampPtr, &runtime);
          }
        }
      }
    }
  }
} /* EthTSyn_SwtTimeSync_SwtSyncFrameHwTimestampCorrectPot() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
#  endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_Init
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
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_Init(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwitchTimeSyncCfgIterType swtTimeSyncCfgIter;
  EthTSyn_SwitchSyncFrameCfgIterType swtSyncFrameCfgIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all switch time sync configs. */
  for(swtTimeSyncCfgIter = 0u; swtTimeSyncCfgIter < EthTSyn_GetSizeOfSwitchTimeSyncCfg(); swtTimeSyncCfgIter++)
  {
    /* #20 Initialize dynamic data of each switch time sync config. */
    EthTSyn_SwtTimeSync_InitTimeStampInfo(EthTSyn_GetAddrPrevTimeStampInfoOfSwitchTimeSyncInfo(swtTimeSyncCfgIter));   /* SBSW_ETHTSYN_CSL02_PTR */
    EthTSyn_SwtTimeSync_InitTimeStampInfo(EthTSyn_GetAddrTimeStampInfoOfSwitchTimeSyncInfo(swtTimeSyncCfgIter));       /* SBSW_ETHTSYN_CSL02_PTR */

    EthTSyn_SetStateOfSwitchTimeSyncInfo(swtTimeSyncCfgIter, ETHTSYN_WAIT_FIRST_STATEOFSWITCHTIMESYNCINFO);            /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetLastCorrectedOffsetNsOfSwitchTimeSyncInfo(swtTimeSyncCfgIter, 0);                                       /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetCurrentOffsetNsOfSwitchTimeSyncInfo(swtTimeSyncCfgIter, 0);                                             /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetOutOfSyncCntOfSwitchTimeSyncInfo(swtTimeSyncCfgIter, 0u);                                               /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetWasSyncReachedOfSwitchTimeSyncInfo(swtTimeSyncCfgIter, FALSE);                                          /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetSwtSyncStateOfSwitchTimeSyncInfo(swtTimeSyncCfgIter, ETHTSYN_NEVERSYNC);                                /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetSyncEventTimeoutCntOfSwitchTimeSyncInfo(swtTimeSyncCfgIter,                                             /* SBSW_ETHTSYN_CSL02 */
      EthTSyn_GetSyncEventTimeoutOfSwitchTimeSyncCfg(swtTimeSyncCfgIter));
  }

  /* #30 Iterate all switch sync frame configs. */
  for(swtSyncFrameCfgIter = 0u; swtSyncFrameCfgIter < EthTSyn_GetSizeOfSwitchSyncFrameCfg(); swtSyncFrameCfgIter++)
  {
    /* #40 Initialize dynamic data of each switch sync frame config. */
    EthTSyn_GetAddrPreciseOriginTsMgmtOfSwitchSyncFrameInfo(swtSyncFrameCfgIter)->State =                              /* SBSW_ETHTSYN_CSL02 */
      ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_INVALID;
    EthTSyn_GetAddrSwtIngressTsMgmtOfSwitchSyncFrameInfo(swtSyncFrameCfgIter)->State =                                 /* SBSW_ETHTSYN_CSL02 */
      ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_INVALID;

    EthTSyn_SetSyncTxCntOfSwitchSyncFrameInfo(swtSyncFrameCfgIter,                                                     /* SBSW_ETHTSYN_CSL02 */
      EthTSyn_GetSyncTxIntervalOfSwitchSyncFrameCfg(swtSyncFrameCfgIter));
    EthTSyn_SetSequenceIdOfSwitchSyncFrameInfo(swtSyncFrameCfgIter, 0u);                                               /* SBSW_ETHTSYN_CSL02 */

    EthTSyn_SetValidOfSwitchSyncFrameTxFrameInfo(swtSyncFrameCfgIter, FALSE);                                          /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetBufIdxOfSwitchSyncFrameTxFrameInfo(swtSyncFrameCfgIter, ETHTSYN_INV_BUF_IDX);                           /* SBSW_ETHTSYN_CSL02 */
    EthTSyn_SetBufAddrOfSwitchSyncFrameTxFrameInfo(swtSyncFrameCfgIter, NULL_PTR);                                     /* SBSW_ETHTSYN_CSL02 */

    /* #50 Only initialize 'Running' flag if EthTSyn was not initialized yet. */
    if(EthTSyn_State == ETHTSYN_STATE_UNINIT)
    {
      EthTSyn_SetRunningOfSwitchSyncFrameInfo(swtSyncFrameCfgIter, FALSE);                                             /* SBSW_ETHTSYN_CSL02 */
    }
  }
} /* EthTSyn_SwtTimeSync_Init() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_HandleCyclicTasks
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_HandleCyclicTasks(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwitchTimeSyncCfgIterType swtTimeSyncCfgIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all switch time sync configs. */
  for(swtTimeSyncCfgIter = 0u; swtTimeSyncCfgIter < EthTSyn_GetSizeOfSwitchTimeSyncCfg(); swtTimeSyncCfgIter++)
  {
    /* #20 Handle optional switch sync frame. */
    if(EthTSyn_IsSwitchSyncFrameCfgUsedOfSwitchTimeSyncCfg(swtTimeSyncCfgIter) == TRUE)
    {
      EthTSyn_SwtTimeSync_HandleSwtSyncFrame(EthTSyn_GetSwitchSyncFrameCfgIdxOfSwitchTimeSyncCfg(swtTimeSyncCfgIter));
    }

    /* #30 Handle sync event timeout. */
    EthTSyn_SwtTimeSync_HandleSyncEventTimeout(swtTimeSyncCfgIter);

    /* #40 Handle time synchronization of the switch cascade. */
    EthTSyn_SwtTimeSync_HandleSwtTimeSync(swtTimeSyncCfgIter);
  }
} /* EthTSyn_SwtTimeSync_HandleCyclicTasks() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ProvideTimestamps
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
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ProvideTimestamps(
                  EthTSyn_IntTimeDomainIdxType TimeDomainIdx,
                  uint8                        EthIfSwitchIdx,
                  uint16                       SequenceId,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) PreciseOriginTimestampPtr,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) SwtIngressTimestampPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwitchTimeSyncCfgIterType swtTimeSyncCfgIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all switch time sync configurations. */
  for(swtTimeSyncCfgIter = 0; swtTimeSyncCfgIter < EthTSyn_GetSizeOfSwitchTimeSyncCfg(); swtTimeSyncCfgIter++)
  {
    /* #20 Check for matching EthIfSwitch. */
    if(EthTSyn_GetEthIfSwitchIdxOfSwitchTimeSyncCfg(swtTimeSyncCfgIter) == EthIfSwitchIdx)
    {
      /* #200 Verify time domain and ensure no separate switch sync frame is used. */
      if((EthTSyn_GetTimeDomainIdxOfSwitchTimeSyncCfg(swtTimeSyncCfgIter) == TimeDomainIdx) && /* PRQA S 3415 */ /* MD_EthTSyn_3415_CslReadOnly */
        (EthTSyn_IsSwitchSyncFrameCfgUsedOfSwitchTimeSyncCfg(swtTimeSyncCfgIter) == FALSE))
      {
        /* #2000 Store timestamps for later synchronization of the switch. */
        EthTSyn_SwtTimeSync_StoreTimestamps(
          (EthTSyn_SizeOfSwitchTimeSyncCfgType)swtTimeSyncCfgIter,
          SequenceId,
          PreciseOriginTimestampPtr,
          SwtIngressTimestampPtr);
      }
      /* #201 Stop iteration because only one switch time sync config can exist per switch. */
      break;
    }
  }
} /* EthTSyn_SwtTimeSync_ProvideTimestamps() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_ProvideTimestamps
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
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_ProvideTimestampsFromSwtSlavePort(
  EthTSyn_IntTimeDomainIdxType TimeDomainIdx,
  EthTSyn_IntSlavePortIdxType  SwtSlavePortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_P2CONST(EthTSyn_SyncReceiveSmType) syncReceiveSmPtr = EthTSyn_GetAddrSyncReceiveSm(SwtSlavePortIdx);

  /* ----- Implementation ----------------------------------------------- */
  ETHTSYN_ENTER_CRITICAL_SECTION_0();
  /* #10 Check if sync ingress timestamp is available. */
  if(EthTSyn_Util_IsTimestampAvailable(syncReceiveSmPtr->Sync.IngressTimestampMgmt.State) == TRUE)
  {
    ETHTSYN_P2VAR(EthTSyn_SiteSyncSyncSmType) siteSyncSyncSmPtr = EthTSyn_GetAddrSiteSyncSyncSm(TimeDomainIdx);
    const EthTSyn_PortIdxOfSlavePortType portIdx = EthTSyn_GetPortIdxOfSlavePort(SwtSlavePortIdx);
    const EthTSyn_SwitchPortMgmtIdxOfPortType swtPortMgmtIdx = EthTSyn_GetSwitchPortMgmtIdxOfPort(portIdx);
    ETHTSYN_P2CONST(EthTSyn_FollowUpMsgType) fupMsgPtr;
    EthTSyn_GlobalTimestampType preciseOriginTimestamp;
    uint64 unsignedFollowUpCorrectionField;
    EthTSyn_TimediffType timeDiffToCorrect;

    /* #20 Get the precise origin timestamp from the corresponding FollowUp message stored in the site sync sync state
           machine. */
    fupMsgPtr = (ETHTSYN_P2CONST(EthTSyn_FollowUpMsgType))siteSyncSyncSmPtr->Msg.Payload; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */
    EthTSyn_NtohTimestamp(&preciseOriginTimestamp,
      (ETHTSYN_P2CONST(EthTSyn_TimestampType))fupMsgPtr->PreciseOriginTimestampSeconds); /* PRQA S 0310 */ /* MD_EthTSyn_0310_Timestamp */

    /* #30 Correct precise origin timestamp by correction field and path delay. */
    unsignedFollowUpCorrectionField = ETHTSYN_GET_FOLLOW_UP_CORRECTION_VALUE_NS_FROM_MSG(
      siteSyncSyncSmPtr->Msg.MsgHdr.CorrectionField);
    /* No overflow possible. FollowUp correction field holds a max value of (2^48 - 1)ns and Pdelay (2^32 - 1) -->
     * max value of the sum fits uint64 and sint64 as well. */
    unsignedFollowUpCorrectionField += EthTSyn_Pdelay_GetCurrentPdelay(portIdx);
    timeDiffToCorrect = (EthTSyn_TimediffType)unsignedFollowUpCorrectionField;

    if(EthTSyn_Util_TimestampPlusTimediff(&preciseOriginTimestamp, &timeDiffToCorrect) == E_OK)
    {
      /* #40 Provide the corrected precise origin timestamp and sync ingress timestamp for later time synchronization
             of the switch. */
      EthTSyn_SwtTimeSync_ProvideTimestamps(
        TimeDomainIdx,
        EthTSyn_GetSwitchIdxOfSwitchPortMgmt(swtPortMgmtIdx),
        syncReceiveSmPtr->Sync.SequenceId,
        &preciseOriginTimestamp,
        &syncReceiveSmPtr->Sync.IngressTimestampMgmt.Timestamp);
    }
    /* #50 Reset provide timestamps flag of site sync sync state machine. */
    siteSyncSyncSmPtr->ProvideSwtTimeSyncTimestamps = FALSE;
  }
  ETHTSYN_LEAVE_CRITICAL_SECTION_0();

} /* EthTSyn_SwtTimeSync_ProvideTimestampsFromSwtSlavePort() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_IsTimeDomainUsedForSwtSync
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(boolean, ETHTSYN_CODE) EthTSyn_SwtTimeSync_IsTimeDomainUsedForSwtSync(
  EthTSyn_IntTimeDomainIdxType TimeDomainIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwitchTimeSyncCfgIterType swtTimeSyncCfgIter;
  boolean isUsed = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all switch time sync configs. */
  for(swtTimeSyncCfgIter = 0u; swtTimeSyncCfgIter < EthTSyn_GetSizeOfSwitchTimeSyncCfg(); swtTimeSyncCfgIter++)
  {
    /* #20 If parsed time domain matches time domain of the current switch time sync config, mark result as 'TRUE' and
           stop iteration. */
    if(EthTSyn_GetTimeDomainIdxOfSwitchTimeSyncCfg(swtTimeSyncCfgIter) == TimeDomainIdx)
    {
      isUsed = TRUE;
      break;
    }
  }

  return isUsed;
} /* EthTSyn_SwtTimeSync_IsTimeDomainUsedForSwtSync() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SwtSyncFrameStart
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SwtSyncFrameStart(
  uint8 EthIfCtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwitchSyncFrameCfgIterType swtSyncFrameCfgIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set 'Running' flag of all switch sync frames to 'TRUE'. */
  for(swtSyncFrameCfgIter = 0; swtSyncFrameCfgIter < EthTSyn_GetSizeOfSwitchSyncFrameCfg(); swtSyncFrameCfgIter++)
  {
    if(EthTSyn_GetEthIfCtrlIdxOfSwitchSyncFrameCfg(swtSyncFrameCfgIter) == EthIfCtrlIdx)
    {
      EthTSyn_SetRunningOfSwitchSyncFrameInfo(swtSyncFrameCfgIter, TRUE);
    }
  }
} /* EthTSyn_SwtTimeSync_SwtSyncFrameStart() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SwtSyncFrameStop
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SwtSyncFrameStop(
  uint8 EthIfCtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwitchSyncFrameCfgIterType swtSyncFrameCfgIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set 'Running' flag of all switch sync frames to 'FALSE' and reset the sync frame cycle time. */
  for(swtSyncFrameCfgIter = 0; swtSyncFrameCfgIter < EthTSyn_GetSizeOfSwitchSyncFrameCfg(); swtSyncFrameCfgIter++)
  {
    if(EthTSyn_GetEthIfCtrlIdxOfSwitchSyncFrameCfg(swtSyncFrameCfgIter) == EthIfCtrlIdx)
    {
      EthTSyn_SetRunningOfSwitchSyncFrameInfo(swtSyncFrameCfgIter, FALSE);
      EthTSyn_SetSyncTxCntOfSwitchSyncFrameInfo(swtSyncFrameCfgIter,
        EthTSyn_GetSyncTxIntervalOfSwitchSyncFrameCfg(swtSyncFrameCfgIter));
    }
  }
} /* EthTSyn_SwtTimeSync_SwtSyncFrameStop() */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SwtSyncFrameTxConfirmation
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
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SwtSyncFrameTxConfirmation(
  uint8 EthIfCtrlIdx,
  uint8 BufIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwitchSyncFrameCfgIterType swtSyncFrameCfgIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all switch sync frame configs. */
  for(swtSyncFrameCfgIter = 0; swtSyncFrameCfgIter < EthTSyn_GetSizeOfSwitchSyncFrameCfg(); swtSyncFrameCfgIter++)
  {
    /* #20 Check if EthIf controller matches the passed one. */
    if(EthTSyn_GetEthIfCtrlIdxOfSwitchSyncFrameCfg(swtSyncFrameCfgIter) == EthIfCtrlIdx)
    {
      /* #30 Check if a switch sync frame was transmitted and if the transmission buffer matches. */
      if((EthTSyn_IsValidOfSwitchSyncFrameTxFrameInfo(swtSyncFrameCfgIter) == TRUE) && /* PRQA S 3415 */ /* MD_EthTSyn_3415_CslReadOnly */
        (EthTSyn_GetBufIdxOfSwitchSyncFrameTxFrameInfo(swtSyncFrameCfgIter) == BufIdx))
      {
        /* #40 Matching switch sync frame found. Get the sync egress timestamp (i.e. precise origin timestamp). */
        const EthTSyn_SwitchTimeSyncCfgIdxOfSwitchSyncFrameCfgType swtTimeSyncCfgIdx =
          EthTSyn_GetSwitchTimeSyncCfgIdxOfSwitchSyncFrameCfg(swtSyncFrameCfgIter);
        const EthTSyn_TimeDomainIdxOfSwitchTimeSyncCfgType timeDomainIdx =
          EthTSyn_GetTimeDomainIdxOfSwitchTimeSyncCfg(swtTimeSyncCfgIdx);
        const StbM_SynchronizedTimeBaseType timeBaseId = EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(timeDomainIdx);
        ETHTSYN_P2VAR(EthTSyn_TimestampMgmtStructType) potMgmtPtr =
          EthTSyn_GetAddrPreciseOriginTsMgmtOfSwitchSyncFrameInfo(swtSyncFrameCfgIter);
        StbM_TimeStampType currentTime;
        StbM_UserDataType userData;

        if(StbM_GetCurrentTime(timeBaseId, &currentTime, &userData) == E_OK)
        {
          EthTSyn_GlobalTimestampType preciseOriginTimestamp;

          ETHTSYN_COPY_STBM_TS_TO_GLOBAL_TS(currentTime, preciseOriginTimestamp);

          /* #400 When hardware timestamping is used, correct the precise origin timestamp. */
#  if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
          EthTSyn_SwtTimeSync_SwtSyncFrameHwTimestampCorrectPot(EthIfCtrlIdx, BufIdx, &preciseOriginTimestamp);
#  endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

          /* #401 Store timestamp and mark it as available. */
          potMgmtPtr->Timestamp = preciseOriginTimestamp;
          potMgmtPtr->State |= ETHTSYN_TIMESTAMP_STATE_AVAILABLE_MASK;
        }

        /* #50 Mark ts available flag as valid, invalidate switch sync frame info and stop iteration. */
        potMgmtPtr->State |= ETHTSYN_TIMESTAMP_STATE_AVAILABLE_FLAG_VALID_MASK;
        EthTSyn_SetValidOfSwitchSyncFrameTxFrameInfo(swtSyncFrameCfgIter, FALSE);
        break;
      }
    }
  }
} /* EthTSyn_SwtTimeSync_SwtSyncFrameTxConfirmation() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_SwtTimeSync_SwtSyncFrameHandleRx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtTimeSync_SwtSyncFrameHandleRx(
  ETHTSYN_P2CONST(EthTSyn_SwtMgmt_MsgBufferType) MsgBufferPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_SwitchSyncFrameCfgIterType swtSyncFrameCfgIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all switch sync frame configs. */
  for(swtSyncFrameCfgIter = 0; swtSyncFrameCfgIter < EthTSyn_GetSizeOfSwitchSyncFrameCfg(); swtSyncFrameCfgIter++)
  {
    /* #20 Check for matching EthIf controller and (management) switch port info. */
    if((EthTSyn_GetEthIfCtrlIdxOfSwitchSyncFrameCfg(swtSyncFrameCfgIter) == MsgBufferPtr->CtrlIdx) && /* PRQA S 3415 */ /* MD_EthTSyn_3415_CslReadOnly */
      (EthTSyn_GetMgmtPortEthIfSwitchIdxOfSwitchSyncFrameCfg(swtSyncFrameCfgIter) ==
          MsgBufferPtr->SwtMgmtInfo.SwitchIdx) &&
      (EthTSyn_GetMgmtPortSwitchPortIdxOfSwitchSyncFrameCfg(swtSyncFrameCfgIter) == MsgBufferPtr->SwtMgmtInfo.PortIdx))
    {
      /* #30 Matching switch sync frame found. Store sync ingress timestamp infos and stop iteration. */
      EthTSyn_SetSwtIngressTsMgmtOfSwitchSyncFrameInfo(swtSyncFrameCfgIter, MsgBufferPtr->IngressTimestampMgmt);
      break;
    }
  }
} /* EthTSyn_SwtTimeSync_SwtSyncFrameHandleRx() */

#  define ETHTSYN_STOP_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# endif /* (ETHTSYN_SWT_TIME_SYNC_SUPPORT == STD_ON) */
#endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
/* Justification for module-specific MISRA deviations:
 * see file EthTSyn.c
*/

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_SwtTimeSync_Int.c
 *********************************************************************************************************************/
