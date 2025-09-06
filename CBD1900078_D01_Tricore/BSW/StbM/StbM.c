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
/*!        \file  StbM.c
 *        \brief  Vector AUTOSAR StbM code file
 *
 *      \details  This is the main implementation file of the Vector AUTOSAR module StbM.
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

#define STBM_SOURCE
/**********************************************************************************************************************
 * MISRA JUSTIFICATION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "StbM.h"
#include "SchM_StbM.h"
#if (STBM_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif
#include "StbM_Cbk.h"
#include "Rte_StbM.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* Check the version of StbM header file */
#if (  (STBM_SW_MAJOR_VERSION != (5u)) \
    || (STBM_SW_MINOR_VERSION != (8u)) \
    || (STBM_SW_PATCH_VERSION != (1u)) )
# error "Vendor specific version numbers of StbM.c and StbM.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (STBM_CFG_MAJOR_VERSION != (5u)) \
    || (STBM_CFG_MINOR_VERSION != (8u)) )
# error "Version numbers of StbM.c and StbM_Cfg.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define STBM_TIMESTAMP_MAX_NANOSECONDS                  (999999999uL)   /* 10^9 nanoseconds per second */
#define STBM_TIMESTAMP_MAX_SECONDS                      (4294967295uL)
#define STBM_TIMESTAMP_MAX_SECONDSHI                    (65535u)

#define STBM_TIMEDIFF_MAX_NANOSECONDS                   (0x7FFFFFFFFFFFFFFFuLL)
#define STBM_TIMEDIFF_MAX_SECONDS                       (STBM_TIMEDIFF_MAX_NANOSECONDS / STBM_NANOSECONDS_IN_ONE_SECOND)

#define STBM_MICROSECOND_IN_ONE_SECOND                  (1000000u)
#define STBM_NANOSECONDS_IN_ONE_MICROSECOND             (1000u)
#define STBM_NANOSECONDS_IN_ONE_SECOND                  (1000000000uL)

#define STBM_TIMELEAP_MAX_FUTURE                        (2147483647LL)
#define STBM_TIMELEAP_MAX_PAST                          (-2147483647LL)

#define STBM_GPT_TIMER_STOPPED                          (0u)
#define STBM_GPT_TIMER_START_REQUIRED                   (1u)
#define STBM_GPT_TIMER_RUNNING                          (2u)

#define STBM_TIMER_STOPPED                              (0u)
#define STBM_TIMER_RUNNING                              (1u)
#define STBM_TIMER_CBK_EXPECTED                         (2u)
#define STBM_TIMER_CALL_CBK                             (3u)

#define STBM_START_OFFSET_TIME_BASE_ID                  (16u)
#define STBM_END_OFFSET_TIME_BASE_ID                    (31u)

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
#define StbM_IsOsLocalTimeUsed(index)                   (StbM_GetOsLocalTimeConfigIdxOfTimeBaseConfig(index) != STBM_NO_OSLOCALTIMECONFIGIDXOFTIMEBASECONFIG) /* PRQA S 3453 */   /* MD_MSR_FctLikeMacro */
#define StbM_IsGptLocalTimeUsed(index)                  (StbM_GetGptLocalTimeConfigIdxOfTimeBaseConfig(index) != STBM_NO_GPTLOCALTIMECONFIGIDXOFTIMEBASECONFIG) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
#define StbM_IsOffsetTimeBase(index)                    ((STBM_START_OFFSET_TIME_BASE_ID <= StbM_GetTimeBaseIdOfTimeBaseConfig(index)) && (StbM_GetTimeBaseIdOfTimeBaseConfig(index) <= STBM_END_OFFSET_TIME_BASE_ID)) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define StbM_GetAbsoluteValue(value)                    (((value) < 0)? ((uint64)-(value)) : ((uint64)(value))) /* PRQA S 3453 */       /* MD_MSR_FctLikeMacro */

#define StbM_SetTimeoutBit(status)                      (status) = ((status) | StbM_Timeout_BflMask) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
#define StbM_SetTimeLeapFutureBit(status)               (status) = ((status) | StbM_TimeLeapFuture_BflMask) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define StbM_SetTimeLeapPastBit(status)                 (status) = ((status) | StbM_TimeLeapPast_BflMask) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define StbM_SetSyncToGatewayBit(status)                (status) = ((status) | StbM_Sync_To_Gateway_BflMask) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
#define StbM_SetGlobalTimeBaseBit(status)               (status) = ((status) | StbM_Global_Time_Base_BflMask) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#define StbM_ClearTimeoutBit(status)                    (status) = ((status) & ~StbM_Timeout_BflMask) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define StbM_ClearTimeLeapFutureBit(status)             (status) = ((status) & ~StbM_TimeLeapFuture_BflMask) /* PRQA S 3453 */        /* MD_MSR_FctLikeMacro */
#define StbM_ClearTimeLeapPastBit(status)               (status) = ((status) & ~StbM_TimeLeapPast_BflMask) /* PRQA S 3453 */        /* MD_MSR_FctLikeMacro */
#define StbM_ClearSyncToGatewayBit(status)              (status) = ((status) & ~StbM_Sync_To_Gateway_BflMask) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define StbM_ClearGlobalTimeBaseBit(status)             (status) = ((status) & ~StbM_Global_Time_Base_BflMask) /* PRQA S 3453 */        /* MD_MSR_FctLikeMacro */

#define StbM_GetTimeoutBit(status)                      ((status) & StbM_Timeout_BflMask) /* PRQA S 3453 */     /* MD_MSR_FctLikeMacro */
#define StbM_GetTimeLeapFutureBit(status)               ((status) & StbM_TimeLeapFuture_BflMask) /* PRQA S 3453 */    /* MD_MSR_FctLikeMacro */
#define StbM_GetTimeLeapPastBit(status)                 ((status) & StbM_TimeLeapPast_BflMask) /* PRQA S 3453 */    /* MD_MSR_FctLikeMacro */
#define StbM_GetSyncToGatewayBit(status)                ((status) & StbM_Sync_To_Gateway_BflMask) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define StbM_GetGlobalTimeBaseBit(status)               ((status) & StbM_Global_Time_Base_BflMask) /* PRQA S 3453 */    /* MD_MSR_FctLikeMacro */

#if (STBM_DEV_ERROR_REPORT == STD_ON)
# define StbM_ReportError(API_ID, ERROR_CODE)           (void) Det_ReportError((STBM_MODULE_ID), 0u, ((uint8)(API_ID)), ((uint8)(ERROR_CODE))) /* PRQA  S 3453 */       /* MD_MSR_FctLikeMacro */
#endif

#if (STBM_STATUSNOTIFICATIONCUSTOMERCONFIG == STD_ON)
# define StbM_SetStatusEvGlobalTimeBase(status)           (status) = ((status) | STBM_EV_GLOBAL_TIME_BASE_MASK) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_SetStatusEvTimeoutOccurred(status)          (status) = ((status) | STBM_EV_TIMEOUT_OCCURRED_MASK) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_SetStatusEvTimeoutRemoved(status)           (status) = ((status) | STBM_EV_TIMEOUT_REMOVED_MASK) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_SetStatusEvTimeleapFuture(status)           (status) = ((status) | STBM_EV_TIMELEAP_FUTURE_MASK) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_SetStatusEvTimeleapFutureRemoved(status)    (status) = ((status) | STBM_EV_TIMELEAP_FUTURE_REMOVED_MASK) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_SetStatusEvTimeleapPast(status)             (status) = ((status) | STBM_EV_TIMELEAP_PAST_MASK) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_SetStatusEvTimeleapPastRemoved(status)      (status) = ((status) | STBM_EV_TIMELEAP_PAST_REMOVED_MASK) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_SetStatusEvSyncToSubdomain(status)          (status) = ((status) | STBM_EV_SYNC_TO_SUBDOMAIN_MASK) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_SetStatusEvSyncToGlobalMaster(status)       (status) = ((status) | STBM_EV_SYNC_TO_GLOBAL_MASTER_MASK) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_SetStatusEvResync(status)                   (status) = ((status) | STBM_EV_RESYNC_MASK) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_SetStatusEvRatecorrection(status)           (status) = ((status) | STBM_EV_RATECORRECTION_MASK) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */

# define StbM_ClearStatusEvGlobalTimeBase(status)         (status) = ((status) & ~STBM_EV_GLOBAL_TIME_BASE_MASK) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_ClearStatusEvTimeoutOccurred(status)        (status) = ((status) & ~STBM_EV_TIMEOUT_OCCURRED_MASK) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_ClearStatusEvTimeoutRemoved(status)         (status) = ((status) & ~STBM_EV_TIMEOUT_REMOVED_MASK) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_ClearStatusEvTimeleapFuture(status)         (status) = ((status) & ~STBM_EV_TIMELEAP_FUTURE_MASK) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_ClearStatusEvTimeleapFutureRemoved(status)  (status) = ((status) & ~STBM_EV_TIMELEAP_FUTURE_REMOVED_MASK) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_ClearStatusEvTimeleapPast(status)           (status) = ((status) & ~STBM_EV_TIMELEAP_PAST_MASK) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_ClearStatusEvTimeleapPastRemoved(status)    (status) = ((status) & ~STBM_EV_TIMELEAP_PAST_REMOVED_MASK) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_ClearStatusEvSyncToSubdomain(status)        (status) = ((status) & ~STBM_EV_SYNC_TO_SUBDOMAIN_MASK) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_ClearStatusEvSyncToGlobalMaster(status)     (status) = ((status) & ~STBM_EV_SYNC_TO_GLOBAL_MASTER_MASK) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_ClearStatusEvResync(status)                 (status) = ((status) & ~STBM_EV_RESYNC_MASK) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_ClearStatusEvRatecorrection(status)         (status) = ((status) & ~STBM_EV_RATECORRECTION_MASK) /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */

# define StbM_IsStatusEvGlobalTimeBaseSet(status)         ((status) & STBM_EV_GLOBAL_TIME_BASE_MASK) != 0u /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_IsStatusEvTimeoutOccurredSet(status)        ((status) & STBM_EV_TIMEOUT_OCCURRED_MASK) != 0u /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_IsStatusEvTimeoutRemovedSet(status)         ((status) & STBM_EV_TIMEOUT_REMOVED_MASK) != 0u /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_IsStatusEvTimeleapFutureSet(status)         ((status) & STBM_EV_TIMELEAP_FUTURE_MASK) != 0u /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_IsStatusEvTimeleapFutureRemovedSet(status)  ((status) & STBM_EV_TIMELEAP_FUTURE_REMOVED_MASK) != 0u /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_IsStatusEvTimeleapPastSet(status)           ((status) & STBM_EV_TIMELEAP_PAST_MASK) != 0u /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_IsStatusEvTimeleapPastRemovedSet(status)    ((status) & STBM_EV_TIMELEAP_PAST_REMOVED_MASK) != 0u /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_IsStatusEvSyncToSubdomainSet(status)        ((status) & STBM_EV_SYNC_TO_SUBDOMAIN_MASK) != 0u /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_IsStatusEvSyncToGlobalMasterSet(status)     ((status) & STBM_EV_SYNC_TO_GLOBAL_MASTER_MASK) != 0u /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_IsStatusEvResyncSet(status)                 ((status) & STBM_EV_RESYNC_MASK) != 0u /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
# define StbM_IsStatusEvRatecorrectionSet(status)         ((status) & STBM_EV_RATECORRECTION_MASK) != 0u /* PRQA S 3453 */  /* MD_MSR_FctLikeMacro */
#endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (STBM_LOCAL)       /* COV_STBM_MSR_COMPATIBILITY */
# define STBM_LOCAL static
#endif

#if !defined (STBM_LOCAL_INLINE)        /* COV_STBM_MSR_COMPATIBILITY */
# define STBM_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define STBM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */   /* MD_MSR_MemMap */

#if (STBM_TIMENOTIFICATIONCUSTOMERCONFIG == STD_ON)
/*! Timer variable of time notification customers */

STBM_LOCAL VAR(uint8, STBM_VAR_NOINIT) StbM_GptTimerState;
#endif

#define STBM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */   /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define STBM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */   /* MD_MSR_MemMap */

#if (STBM_TRIGGEREDCUSTOMERCONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_IncrementCustomerCounter()
 *********************************************************************************************************************/
/*! \brief      Increment the customer counter
 *  \details    This function increments the counter of the given triggered customers state.
 *  \param[in]  customerIdx              The triggered customer, whose counter is incremented.
 *  \pre        Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_IncrementCustomerCounter(StbM_TriggeredCustomerStateIterType customerIdx);
#endif

/**********************************************************************************************************************
 *  StbM_IncrementTimeBaseUpdateCounter()
 *********************************************************************************************************************/
/*! \brief      Increment the timebase update counter
 *  \details    This function increments the update counter of the given time-base.
 *  \param[in]  timeBaseIdx              The synchronized time-base, whose update counter is incremented.
 *  \pre        Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_IncrementTimeBaseUpdateCounter(StbM_SynchronizedTimeBaseType timeBaseIdx);

/**********************************************************************************************************************
 *  StbM_UpdateTimestamp()
 *********************************************************************************************************************/
/*! \brief      Update a timestamp
 *  \details    This function updates the timestamp of the given time-base.
 *  \param[in]  timeBaseId              The synchronized time-base, whose time is updated.
 *  \return     E_OK - Timestamp was updated
 *  \return     E_NOT_OK - Timestamp was not updated
 *  \pre        Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_UpdateTimestamp(StbM_SynchronizedTimeBaseType timeBaseId);

#if ((STBM_OSLOCALTIMECONFIG == STD_ON) || (STBM_GPTLOCALTIMECONFIG == STD_ON))
/**********************************************************************************************************************
 *  StbM_CalculateElapsedTimeFromElapsedCounterValue()
 *********************************************************************************************************************/
/*! \brief      Calculate elapsed time for OS or GPT local time
 *  \details    This function calculates the elapsed time of the given time-base for OS or GPT timer based on the elapsedCounterValue.
 *  \param[in]  timeBaseId              The synchronized time-base, whose time is updated.
 *  \param[in]  elapsedCounterValue     The elapsed counter value calculated for the respective timer.
 *  \param[out] elapsedNanoseconds      Elapsed nanoseconds.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CalculateElapsedTimeFromElapsedCounterValue(
  StbM_SynchronizedTimeBaseType timeBaseId,
  uint32 elapsedCounterValue,
  P2VAR(sint64, AUTOMATIC, STBM_APPL_VAR) elapsedNanoseconds);
#endif

#if (STBM_ETHTSYN_LOCALTIME_USED == STD_ON)
/**********************************************************************************************************************
 *  StbM_CalculateElapsedTimeForEthTSyn()
 *********************************************************************************************************************/
/*! \brief      Calculate elapsed time for Eth local time
 *  \details    This function calculates the elapsed time of the given time-base, if Eth local time is used.
 *  \param[in]  timeBaseId              The synchronized time-base, whose time is updated.
 *  \param[out] elapsedNanoseconds      Elapsed nanoseconds.
 *  \return     E_OK - Timestamp was updated
 *  \return     E_NOT_OK - Timestamp was not updated
 *  \pre        Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalculateElapsedTimeForEthTSyn(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(sint64, AUTOMATIC, STBM_APPL_VAR) elapsedNanoseconds);
#endif

/**********************************************************************************************************************
 *  StbM_TimestampPlusTimestamp()
 *********************************************************************************************************************/
/*! \brief      Adds two timestamps
 *  \details    This function calculates the sum of two timestamps.
 *  \param[in]  timestamp1Ptr          Pointer to timestamp where the first summand is stored.
 *  \param[in]  timestamp2Ptr          Pointer to timestamp where the second summand is stored.
 *  \param[out] timesumPtr             Pointer to timestamp where the calculated sum is stored.
 *  \return     E_OK - Timesum is valid
 *  \return     E_NOT_OK - Timesum is invalid
 *  \pre        Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
 *  \context    TASK
 *  \reentrant  TRUE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_TimestampPlusTimestamp(
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timestamp1Ptr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timestamp2Ptr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_VAR) timesumPtr);

/**********************************************************************************************************************
 *  StbM_TimestampPlusTimediff()
 *********************************************************************************************************************/
/*! \brief      Adds time difference to timestamp
 *  \details    This function adds a time difference in nanoseconds to a timestamp.
 *  \param[in]  timestampPtr           Pointer to a timestamp.
 *  \param[in]  timediff               Time difference in nanoseconds that should be added to the timestamp.
 *  \param[out] timesumPtr             Pointer to timestamp where the calculated sum is stored.
 *  \return     E_OK - Timesum is valid
 *  \return     E_NOT_OK - Timesum is invalid
 *  \pre        Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
 *  \context    TASK
 *  \reentrant  TRUE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_TimestampPlusTimediff(
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timestampPtr,
  sint64 timediff,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_VAR) timesumPtr);

/**********************************************************************************************************************
 *  StbM_TimestampMinusTimestamp()
 *********************************************************************************************************************/
/*! \brief      Subtracts two timestamps
 *  \details    This function calculates the time difference between timestamp1 and timestamp2
 *              (diff = timestamp1 - timestamp2).
 *  \param[in]  timestamp1Ptr     Pointer to first timestamp.
 *  \param[in]  timestamp2Ptr     Pointer to second timestamp.
 *  \param[out] timediffPtr       Pointer to timestamp with difference between timestamp1 and timestamp2.
 *  \return     E_OK - Time difference is valid
 *  \return     E_NOT_OK - Time difference is invalid
 *  \pre        Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
 *  \context    TASK
 *  \reentrant  TRUE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_TimestampMinusTimestamp(
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timestamp1Ptr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timestamp2Ptr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_VAR) timediffPtr);

/**********************************************************************************************************************
 *  StbM_TimestampMinusTimestampInNs
 *********************************************************************************************************************/
/*! \brief      Calculates time difference in nanoseconds
 *  \details    This function calculates the time difference between timestamp1 and timestamp2 in nanoseconds
 *              (diff = timestamp1 - timestamp2).
 *  \param[in]  timestamp1Ptr     Pointer to first timestamp.
 *  \param[in]  timestamp2Ptr     Pointer to second timestamp.
 *  \param[out] timediffPtr       Pointer to timestamp with difference between timestamp1 and timestamp2 in nanoseconds.
 *  \return     E_OK - Time difference is valid
 *  \return     E_NOT_OK - Time difference is invalid. 
 *                         The maximal supported time difference in absolute values is:
 *                         (STBM_TIMEDIFF_MAX_SECONDS - 1) * STBM_NANOSECONDS_IN_ONE_SECOND + STBM_TIMESTAMP_MAX_NANOSECONDS.
 *  \pre        Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
 *  \context    TASK
 *  \reentrant  TRUE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_TimestampMinusTimestampInNs(
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timestamp1Ptr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timestamp2Ptr,
  P2VAR(sint64, AUTOMATIC, STBM_APPL_VAR) timediffPtr);

/**********************************************************************************************************************
 *  StbM_CalcTimeAndGetUserData()
 *********************************************************************************************************************/
/*! \brief       Returns the current time in standard format and updates the user data
 *  \details     This function returns the current time of the submitted time-base in standard format.
 *  \param[in]   timeBaseId              The synchronized time-base, whose time is of interest.
 *  \param[out]  timeStampPtr            Current time stamp in standard format.
 *  \param[out]  userDataPtr             User data of the time base.
 *  \return      E_OK     - Timestamp is valid
 *  \return      E_NOT_OK - Timestamp is invalid
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalcTimeAndGetUserData(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_VAR) timeStampPtr,
  P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_VAR) userDataPtr);

/**********************************************************************************************************************
 *  StbM_CalculateCurrentTime()
 *********************************************************************************************************************/
/*! \brief       Returns the current time in standard format and gets the corresponding user data.
 *  \details     This function returns the current time of the submitted time-base in standard format.
 *  \param[in]   timeBaseId              The synchronized time-base, whose time is of interest.
 *  \param[out]  timeStampPtr            Current time stamp in standard format.
 *  \param[out]  userDataPtr             User data of the time base.
 *  \return      E_OK     - Timestamp is valid
 *  \return      E_NOT_OK - Timestamp is invalid
 *  \pre         Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
 *  \context     TASK
 *  \reentrant   FALSE
 *  \trace       DSGN-STBM_OFFSET_CORRECTION_TIME_BASES
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalculateCurrentTime(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_VAR) timeStampPtr,
  P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_VAR) userDataPtr);

#if ((STBM_RATEMEASUREMENTSTORAGE == STD_ON) || (STBM_MASTERRATECORRECTIONALLOWEDOFTIMEBASECONFIG == STD_ON))
/**********************************************************************************************************************
 *  StbM_CalculationsOfRateAndAdaptiveCorrection()
 *********************************************************************************************************************/
/*! \brief       Calculates the rate corrected current time.
 *  \details     This function calculates the rate corrected current time of the submitted time-base.
 *  \param[in]   timeBaseId              The synchronized time-base, whose time is of interest.
 *  \param[out]  timeStampPtr            Current time stamp in standard format.
 *  \param[in]   diffOffset              Offset difference
 *  \param[in]   diffVirtualLocalTime    Virtual local time difference
 *  \return      E_OK     - Timestamp is valid
 *  \return      E_NOT_OK - Timestamp is invalid
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \trace       DSGN-STBM_OFFSET_CORRECTION_TIME_BASES
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalculationsOfRateAndAdaptiveCorrection(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_VAR) timeStampPtr,
  sint64 diffOffset,
  sint64 diffVirtualLocalTime);
#endif

#if (STBM_TIMEBASECONFIGIDXOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CalculateCurrentOffsetTime()
 *********************************************************************************************************************/
/*! \brief       Returns the current time of an offset time-base in standard format and gets the corresponding user data.
 *  \details     Returns the current time of an offset time-base as the sum of the offset and the current time of the referenced time domain
 *  \param[in]   timeBaseId              The offset time-base, whose time is of interest.
 *  \param[out]  timeStampPtr            Current time stamp in standard format.
 *  \param[out]  userDataPtr             User data of the time base.
 *  \return      E_OK     - Timestamp is valid
 *  \return      E_NOT_OK - Timestamp is invalid
 *  \pre         Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
 *  \context     TASK
 *  \reentrant   FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalculateCurrentOffsetTime(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_VAR) timeStampPtr,
  P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_VAR) userDataPtr);

/**********************************************************************************************************************
 *  StbM_CalculateCombinedOffsetStatus
 *********************************************************************************************************************/
/*! \brief      Calculates the offset status
 *  \details    This function calculates the status of an offset TB depending on the status of the sync TB.
 *  \param[in]  offsetStatus     Offset TB status.
 *  \param[in]  syncStatus       Synchronized TB status.
 *  \return     combined offset status
 *  \pre        -
 *  \context     TASK
 *  \reentrant   TRUE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(StbM_TimeBaseStatusType, STBM_CODE) StbM_CalculateCombinedOffsetStatus(
  StbM_TimeBaseStatusType offsetStatus, StbM_TimeBaseStatusType syncStatus);
#endif

#if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckTimeLeapFuture()
 *********************************************************************************************************************/
/*! \brief       Checks, whether a time leap to the future has occurred and sets the time leap future flag accordingly.
 *  \details     This function allows the recognition of leaps to the future since the last update.
 *  \param[in]   timeBaseId              The synchronized time-base, whose time is set.
 *  \param[in]   timeStampPtr            New time stamp.
 *  \return      E_NOT_OK - Any calculation error has occurred
 *               E_OK     - otherwise
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CheckTimeLeapFuture(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr);
#endif

#if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckTimeLeapPast()
 *********************************************************************************************************************/
/*! \brief       Checks, whether a time leap to the past has occurred and sets the time leap past flag accordingly.
 *  \details     This function allows the recognition of leaps to the past since the last update.
 *  \param[in]   timeBaseId              The synchronized time-base, whose time is set.
 *  \param[in]   timeStampPtr            New time stamp.
 *  \return      E_NOT_OK - Any calculation error has occurred
 *               E_OK     - otherwise
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CheckTimeLeapPast(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr);
#endif

/**********************************************************************************************************************
 *  StbM_CopyUserData()
 *********************************************************************************************************************/
/*! \brief       Copy user data
 *  \details     This function copies user data depending on the user data length of the src param to the dst.
 *  \param[in]   userDataPtrSrc            The user data to be copied.
 *  \param[out]  userDataPtrDst            Destination for the copy operation.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CopyUserData(
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userDataPtrSrc,
  P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userDataPtrDst);

#if ((STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON) && (STBM_RATEMEASUREMENTSTORAGE == STD_ON))
/**********************************************************************************************************************
 *  StbM_EvaluateRateMeasurement()
 *********************************************************************************************************************/
/*! \brief       Evaluate rate measurement
 *  \details     This function evaluates if a running rate measurement should be ended and if a new rate measurement should be started.
 *  \param[in]   timeBaseId              The synchronized time-base, for which rate correction measurement is evaluated.
 *  \param[in]   timeStampPtr            New time stamp.
 *  \param[out]  startNewRateMeasurement TRUE if a new rate measurement should be started, FALSE otherwise
 *  \return      E_NOT_OK - Any calculation error has occurred
 *               E_OK     - otherwise
 *  \pre         Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
 *  \context     TASK
 *  \reentrant   FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_EvaluateRateMeasurement(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr,
  P2VAR(boolean, AUTOMATIC, STBM_APPL_VAR) startNewRateMeasurement);

/**********************************************************************************************************************
*  StbM_CheckRateMeasurementOffset()
*********************************************************************************************************************/
/*! \brief      Check if the rate measurement offset has passed
*  \details     Check if the difference between the actual and the give rate measurement requires the start of a new measurement.
*  \param[in]   timeBaseId              The synchronized time-base, for which rate correction measurement is evaluated.
*  \param[in]   rateMeasurementIdx      The index of the rate measurement to which the actual measurement shall be compared to.
*  \param[out]  startNewRateMeasurement TRUE if a new rate measurement should be started, FALSE otherwise
*  \return      E_NOT_OK - Any calculation error has occurred
*               E_OK     - otherwise
*  \pre         Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
*  \context     TASK
*  \reentrant   FALSE
*********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CheckRateMeasurementOffset(StbM_SynchronizedTimeBaseType timeBaseId,
  StbM_CurrentRateMeasurementIdxOfTimeBaseStateType rateMeasurementIdx,
  P2VAR(boolean, AUTOMATIC, STBM_APPL_VAR) startNewRateMeasurement);

/**********************************************************************************************************************
*  StbM_DiscardRateMeasurements()
*********************************************************************************************************************/
/*! \brief      Discards all rate measurements.
*  \details     This function will loop over all rate measurements and mark them as discared.
*  \param[in]   timeBaseId              The time base id, for which rate measurements should be discarded.
*  \pre         Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
*  \context     TASK
*  \reentrant   FALSE
*********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_DiscardRateMeasurements(StbM_SynchronizedTimeBaseType timeBaseId);

/**********************************************************************************************************************
 *  StbM_RateCorrectionMeasurement()
 *********************************************************************************************************************/
/*! \brief       Perform simultaneous rate measurement
 *  \details     This function performs simultaneous rate measurements and calculates the current rate correction value.
 *  \param[in]   timeBaseId              The synchronized time-base, for which rate correction measurement is performed
 *  \param[in]   timeStampPtr            New time stamp.
 *  \return      E_NOT_OK - Any calculation error has occurred
 *               E_OK     - otherwise
 *  \pre         Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
 *  \context     TASK
 *  \reentrant   FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_RateCorrectionMeasurement(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr);

/**********************************************************************************************************************
 *  StbM_CalculateRateCorrection()
 *********************************************************************************************************************/
/*! \brief       Calculates the rate correction of value of current measurement
 *  \details     -
 *  \param[in]   timeBaseId              The synchronized time-base, for which rate correction measurement is performed
 *  \param[in]   timeStampPtr            New time stamp.
 *  \return      E_NOT_OK - Any calculation error has occurred
 *               E_OK     - otherwise
 *  \pre         Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
 *  \context     TASK
 *  \reentrant   FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalculateRateCorrection(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr);
#endif

#if (STBM_TRIGGEREDCUSTOMERCONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_TriggerCustomers()
 *********************************************************************************************************************/
/*! \brief       Trigger customers
 *  \details     This function triggers customers.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_TriggerCustomers(void);

/**********************************************************************************************************************
 *  StbM_IsCustomerTriggerable()
 *********************************************************************************************************************/
/*! \brief       Check if customer is triggerable.
 *  \details     Checks if the given customer meets all conditions in order to be triggered. 
 *  \pre         -
 *  \param[in]   customerId  - Customer id.
 *  \return      true, if the customer has to be triggered.
 *  \context     TASK
 *  \reentrant   TRUE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(boolean, STBM_CODE) StbM_IsCustomerTriggerable(StbM_TriggeredCustomerStateIterType customerId);
#endif

#if (STBM_STATUSNOTIFICATIONCUSTOMERCONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_ResetStatusEvent()
 *********************************************************************************************************************/
/*! \brief       Initialize notification event customers
 *  \details     -
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \trace       SPEC-2927887
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_ResetStatusEvent(void);

/**********************************************************************************************************************
 *  StbM_CheckAndSetGlobalTimeBaseEv()
 *********************************************************************************************************************/
/*! \brief       Update EV_GLOBAL_TIME_BASE status notification event.
 *  \details     If the GLOBAL_TIME_BASE bit of the time base status has changed from 0 to 1, then the EV_GLOBAL_TIME_BASE event is set.
 *  \param[in]   timeBaseId   - Id of time base whose notification event should be set
 *  \param[in]   customerIdx  - Internal index of notification event variable
 *  \param[in]   customerMask - configured notification mask
 *  \pre         Must be called before GLOBAL_TIME_BASE Bit in timeBaseStatus is going to be set.
 *  \context     ANY
 *  \reentrant   TRUE for different timeBaseIds
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndSetGlobalTimeBaseEv(
  StbM_SynchronizedTimeBaseType timeBaseId,
  StbM_StatusNotificationCustomerConfigIterType customerIdx,
  StbM_StatusNotificationMaskOfStatusNotificationCustomerConfigType customerMask);

# if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckAndSetTimeoutNotificationEv()
 *********************************************************************************************************************/
/*! \brief       Update EV_TIMEOUT_OCCURED status notification event.
 *  \details     If the TIMEOUT bit of the time base status has changed from 0 to 1, then the EV_TIMEOUT_OCCURED event is set.
 *  \param[in]   customerIdx  - Internal index of notification event variable
 *  \param[in]   customerMask - configured notification mask
 *  \pre         Must be called before TIMEOUT Bit in timeBaseStatus is going to be set.
 *  \context     ANY
 *  \reentrant   TRUE for different timeBaseIds
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndSetTimeoutNotificationEv(
  StbM_StatusNotificationCustomerConfigIterType customerIdx,
  StbM_StatusNotificationMaskOfStatusNotificationCustomerConfigType customerMask);
# endif

# if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckAndSetTimeoutRemovedNotificationEv()
 *********************************************************************************************************************/
/*! \brief       Update EV_TIMEOUT_REMOVED status notification event.
 *  \details     If the TIMEOUT bit of the time base status has changed from 1 to 0, then the EV_TIMEOUT_REMOVED event is set.
 *  \param[in]   timeBaseId   - Id of time base whose notification event should be set
 *  \param[in]   customerIdx  - Internal index of notification event variable
 *  \param[in]   customerMask - configured notification mask
 *  \pre         Must be called before TIMEOUT Bit in timeBaseStatus is going to be cleared.
 *  \context     ANY
 *  \reentrant   TRUE for different timeBaseIds
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndSetTimeoutRemovedNotificationEv(
  StbM_SynchronizedTimeBaseType timeBaseId,
  StbM_StatusNotificationCustomerConfigIterType customerIdx,
  StbM_StatusNotificationMaskOfStatusNotificationCustomerConfigType customerMask);
# endif

# if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckAndSetTimeleapFutureNotificationEv()
 *********************************************************************************************************************/
/*! \brief       Update EV_TIMELEAP_FUTURE status notification event.
 *  \details     If the TIMELEAP_FUTURE bit of the time base status has changed from 0 to 1, then the EV_TIMELEAP_FUTURE event is set.
 *  \param[in]   timeBaseId   - Id of time base whose notification event should be set
 *  \pre         Must be called before TIMELEAP_FUTURE Bit in timeBaseStatus is going to be set.
 *  \context     ANY
 *  \reentrant   TRUE for different timeBaseIds
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndSetTimeleapFutureNotificationEv(StbM_SynchronizedTimeBaseType timeBaseId);
# endif

# if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckAndSetTimeleapFutureRemovedNotificationEv()
 *********************************************************************************************************************/
/*! \brief       Update EV_TIMELEAP_FUTURE_REMOVED status notification event.
 *  \details     If the TIMELEAP_FUTURE bit of the time base status has changed from 1 to 0, then the EV_TIMELEAP_FUTURE_REMOVED event is set.
 *  \param[in]   timeBaseId   - Id of time base whose notification event should be set
 *  \pre         Must be called before TIMELEAP_FUTURE Bit in timeBaseStatus is going to be cleared.
 *  \context     ANY
 *  \reentrant   TRUE for different timeBaseIds
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndSetTimeleapFutureRemovedNotificationEv(StbM_SynchronizedTimeBaseType timeBaseId);
# endif

# if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckAndSetTimeleapPastNotificationEv()
 *********************************************************************************************************************/
/*! \brief       Update EV_TIMELEAP_PAST status notification event.
 *  \details     If the TIMELEAP_PAST bit of the time base status has changed from 0 to 1, then the EV_TIMELEAP_PAST event is set.
 *  \param[in]   timeBaseId   - Id of time base whose notification event should be set
 *  \pre         Must be called before TIMELEAP_PAST Bit in timeBaseStatus is going to be set.
 *  \context     ANY
 *  \reentrant   TRUE for different timeBaseIds
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndSetTimeleapPastNotificationEv(StbM_SynchronizedTimeBaseType timeBaseId);
# endif

# if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckAndSetTimeleapPastRemovedNotificationEv()
 *********************************************************************************************************************/
/*! \brief       Update EV_TIMELEAP_PAST_REMOVED status notification event.
 *  \details     If the TIMELEAP_PAST bit of the time base status has changed from 1 to 0, then the EV_TIMELEAP_PAST_REMOVED event is set.
 *  \param[in]   timeBaseId   - Id of time base whose notification event should be set
 *  \pre         Must be called before TIMELEAP_PAST Bit in timeBaseStatus is going to be cleared.
 *  \context     ANY
 *  \reentrant   TRUE for different timeBaseIds
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndSetTimeleapPastRemovedNotificationEv(StbM_SynchronizedTimeBaseType timeBaseId);
# endif

# if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckAndSetSyncToSubdomainEv()
 *********************************************************************************************************************/
/*! \brief       Update EV_SYNC_TO_SUBDOMAIN status notification event.
 *  \details     If the SYNC_TO_GATEWAY bit of the time base status has changed from 0 to 1, then the EV_SYNC_TO_SUBDOMAIN event is set.
 *  \param[in]   timeBaseId      - Id of time base whose notification event should be set
 *  \param[in]   customerIdx     - Internal index of notification event variable
 *  \param[in]   customerMask    - configured notification mask
 *  \param[in]   isUpdateFromBus - TRUE if function is called from StbM_BusSetGlobalTime()
 *                                 FALSE otherwise
 *  \pre         Must be called before SYNC_TO_GATEWAY Bit in timeBaseStatus is going to be set.
 *  \context     ANY
 *  \reentrant   TRUE for different timeBaseIds
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndSetSyncToSubdomainEv(
  StbM_SynchronizedTimeBaseType timeBaseId,
  StbM_StatusNotificationCustomerConfigIterType customerIdx,
  StbM_StatusNotificationMaskOfStatusNotificationCustomerConfigType customerMask,
  boolean isUpdateFromBus);
# endif

# if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckAndSetSyncToGlobalMasterEv()
 *********************************************************************************************************************/
/*! \brief       Update EV_SYNC_TO_GLOBAL_MASTER status notification event.
 *  \details     If the SYNC_TO_GATEWAY bit of the time base status has changed from 1 to 0, then the EV_SYNC_TO_GLOBAL_MASTER event is set.
 *  \param[in]   timeBaseId   - Id of time base whose notification event should be set
 *  \param[in]   customerIdx  - Internal index of notification event variable
 *  \param[in]   customerMask - configured notification mask
 *  \pre         Must be called before SYNC_TO_GATEWAY Bit in timeBaseStatus is going to be cleared.
 *  \context     ANY
 *  \reentrant   TRUE for different timeBaseIds
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndSetSyncToGlobalMasterEv(
  StbM_SynchronizedTimeBaseType timeBaseId,
  StbM_StatusNotificationCustomerConfigIterType customerIdx,
  StbM_StatusNotificationMaskOfStatusNotificationCustomerConfigType customerMask);
# endif

/**********************************************************************************************************************
 *  StbM_CheckAndSetResyncEv()
 *********************************************************************************************************************/
/*! \brief       Update EV_RESYNC status notification event.
 *  \details     If resynchronization has occurred, then the EV_RESYNC event is set.
 *  \param[in]   customerIdx  - Internal index of notification event variable
 *  \param[in]   customerMask - configured notification mask
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE for different timeBaseIds
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndSetResyncEv(
  StbM_StatusNotificationCustomerConfigIterType customerIdx,
  StbM_StatusNotificationMaskOfStatusNotificationCustomerConfigType customerMask);

# if (STBM_RATECORRECTIONSTATUSEVENTACTIVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckAndSetRatecorrectionEv()
 *********************************************************************************************************************/
/*! \brief       Update EV_RATECORRECTION status notification event.
 *  \details     If a valid rate correction value has been calculated, then the EV_RATECORRECTION event is set.
 *  \param[in]   timeBaseId   - Id of time base whose notification event should be set
 *  \pre         Must be called after the new rate correction value has been calculated.
 *  \context     ANY
 *  \reentrant   TRUE for different timeBaseIds
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndSetRatecorrectionEv(StbM_SynchronizedTimeBaseType timeBaseId);
# endif

/**********************************************************************************************************************
 *  StbM_CallStatusNotificationCallbackAndClearEvent()
 *********************************************************************************************************************/
/*! \brief       Calls the configured notification callback and clears the notification event flag.
 *  \details     -
 *  \param[in]   customerIdx - Internal index of notification event variable
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE for different customerIdx
 ********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CallStatusNotificationCallbackAndClearEvent(StbM_StatusNotificationCustomerConfigIterType customerIdx);

# if (STBM_GLOBALTIMEMASTEROFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_SetGlobalTime_SetStatusEvents()
 *********************************************************************************************************************/
/*! \brief       Handle status notification events in context of StbM_SetGlobalTime
 *  \details     -
 *  \param[in]   timeBaseId - Id of the timeBase
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 ********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_SetGlobalTime_SetStatusEvents(StbM_SynchronizedTimeBaseType timeBaseId);
# endif
#endif

#if (STBM_TIMENOTIFICATIONCUSTOMERCONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_GetNextExpirationPoint()
 *********************************************************************************************************************/
/*! \brief       Calculates the minimum of all expiration points.
 *  \details     Next Expiration Point is the minimum of all running timer that might be in the next threshold interval
 *  \param[in]   isCallContextTimerCbk - TRUE if function is called from StbM_TimerCallback, FALSE otherwise
 *  \return      next expiration point
 *  \pre         Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
 *  \context     ANY
 *  \reentrant   TRUE
 ***************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(sint32, STBM_CODE) StbM_GetNextExpirationPoint(boolean isCallContextTimerCbk);

/**********************************************************************************************************************
 *  StbM_CalculateNextExpirationPoint()
 *********************************************************************************************************************/
/*! \brief       Calculates the next expiration points.
 *  \details     Next Expiration Point is the minimum of all running timer that might be in the next threshold interval
 *  \param[in]   timeBaseId - Id of the timeBase
 *  \param[out]  nextExpirationPoint - next expiration point
 *  \param[in]   isCallContextTimerCbk - TRUE if function is called from StbM_TimerCallback, FALSE otherwise
 *  \return      next expiration point
 *  \pre         Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
 *  \context     ANY
 *  \reentrant   TRUE
 ***************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(sint32, STBM_CODE) StbM_CalculateNextExpirationPoint(StbM_SynchronizedTimeBaseType timeBaseId,
  sint32 nextExpirationPoint, boolean isCallContextTimerCbk);

/**********************************************************************************************************************
 *  StbM_GetExpirationPointOfCustomer()
 *********************************************************************************************************************/
/*! \brief       Calculate expiration point and request GPT timer.
 *  \details     This function calculates the expiration point of the given customer and requests the GPT Timer to be started if
 *               expiration point is within the configured threshold.
 *  \param[in]   isCallContextTimerCbk - TRUE if function is called from StbM_TimerCallback, FALSE otherwise
 *  \param[in]   customerId - Id of customer
 *  \param[in]   timeStamp -  current time of time base
 *  \return      next expiration point
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 ***************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(sint32, STBM_CODE) StbM_GetExpirationPointOfCustomer(
  boolean isCallContextTimerCbk,
  StbM_TimeNotificationCustomerConfigIterType customerId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStamp);

/**********************************************************************************************************************
 *  StbM_CheckTimerForCalculatingExpirationPoint()
 *********************************************************************************************************************/
/*! \brief       Calculates the time stamps for calculation of expiration point
 *  \details     -
 *  \param[in]   isCallContextTimerCbk - TRUE if function is called from StbM_TimerCallback, FALSE otherwise
 *  \param[in]   customerId - Id of customer
 *  \param[in]   expirationPoint - temporary expiration point for calculations
 *  \return      next expiration point
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 ***************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(sint32, STBM_CODE) StbM_CheckTimerForCalculatingExpirationPoint(
  boolean isCallContextTimerCbk,
  StbM_TimeNotificationCustomerConfigIterType customerId,
  sint64 expirationPoint);

/**********************************************************************************************************************
 *  StbM_StartGptTimer()
 *********************************************************************************************************************/
/*! \brief       Starts the GPT Timer for given expirationPoint
 *  \details     -
 *  \param[in]   expirationPoint
 *  \pre         Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
 *  \context     ANY
 *  \reentrant   FALSE
 *********************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_StartGptTimer(sint32 expirationPoint);

/**********************************************************************************************************************
 *  StbM_UpdateExpireTime()
 *********************************************************************************************************************/
/*! \brief       Updates all running time notification customer timers of given timeBaseId
 *  \details     This function is called whenever a new time update is received
 *  \param[in]   timeBaseId - Id of Time base
 *  \param[in]   timeStampPtr - New Global Time Value
 *  \pre         Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
 *  \return      E_OK, if calculated current time of time base is valid.
 *               E_NOT_OK, otherwise.
 *  \context     ANY
 *  \reentrant   TRUE for different TimeBase Ids
 *********************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_UpdateExpireTime(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr);

/**********************************************************************************************************************
 *  StbM_CheckTimerAndCalculate()
 *********************************************************************************************************************/
/*! \brief       Checks timer and calculates
 *  \details     This function is called for each time customer start index and calculates expire time based on timer
 *  \param[in]   timeCustomerStartInd - Customer config index
 *  \param[in]   timeBaseId           - Id of Time base
 *  \param[in]   timeStampPtr         - New Global Time Value
 *  \param[in]   currentTime          - Current Time of time base
 *  \return      E_OK, if all time calculations succeeded.
 *               E_NOT_OK, otherwise.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE for different TimeBase Ids
 *********************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CheckTimerAndCalculate(
  StbM_TimeNotificationCustomerConfigIndIterType timeCustomerStartInd,
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) currentTime);

/**********************************************************************************************************************
 *  StbM_StopTimeNotificationCustomers()
 *********************************************************************************************************************/
/*! \brief       Resets the state of all time notification customers
 *  \details     -
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 ********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_StopTimeNotificationCustomers(void);

/**********************************************************************************************************************
 *  StbM_IsExpireTimeValid()
 *********************************************************************************************************************/
/*! \brief       Check whether expire time is valid.
 *  \details     -
 *  \param[in]   expireTime       Time value relative to current Time Base value of the Notification Customer,
 *                                when the Timer shall expire
 *  \return      TRUE       -     valid
 *               FALSE      -     invalid
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(boolean, STBM_CODE) StbM_IsExpireTimeValid(P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) expireTime);
#endif

#if (STBM_OFFSET_TIME_NOTIFICATION_CUSTOMER == STD_ON)
/**********************************************************************************************************************
 *  StbM_CalcElapsedTimeOfOffsetTimeBase()
 *********************************************************************************************************************/
/*! \brief       Update the elapsed time for offset notification customers.
 *  \details     This function updates the elapsed time of all notification customers, which belong to an 
 *               offset time base refering the passed synchronized time base.
 *  \param[in]   timeBaseId - Id of synchronized time base
 *  \pre         Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
 *  \return      E_OK, if all time calculations succeeded.
 *               E_NOT_OK, otherwise.
 *  \context     ANY
 *  \reentrant   TRUE for different timeBaseIds
 *****************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalcElapsedTimeOfOffsetTimeBase(StbM_SynchronizedTimeBaseType timeBaseId);

/**********************************************************************************************************************
 *  StbM_UpdateExpireTimeOfOffsetTimeBase()
 *********************************************************************************************************************/
/*! \brief       Update the expire time of offset notification customers.
 *  \details     This function updates the expire time of all notification customers, which belong to an 
 *               offset time base refering the passed synchronized time base.
 *  \param[in]   timeBaseId - Id of synchronized time base.
 *  \return      E_OK, if all time calculations succeeded.
 *               E_NOT_OK, otherwise.
 *  \pre         The elapsed time has been cached prior calling this function (StbM_CalcElapsedTimeOfOffsetTimeBase
 *               is called before)
 *  \pre         Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
 *  \context     ANY
 *  \reentrant   TRUE for different timeBaseIds
 ****************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_UpdateExpireTimeOfOffsetTimeBase(StbM_SynchronizedTimeBaseType timeBaseId);
#endif

#if (STBM_GLOBALTIMEMASTEROFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_SetNewGlobalTime()
 *********************************************************************************************************************/
/*! \brief       Sets new global time
 *  \details     This function sets the global time to the value given in timeStamp.
 *  \param[in]   timeBaseId              The time base, whose global time is updated.
 *  \param[in]   timeStamp               New time stamp.
 *  \param[in]   userData                New user data.
 *  \return      E_OK - New global time was set
 *  \return      E_NOT_OK - New global time was not set
 *  \pre         -
 *  \context    TASK
 *  \reentrant  FALSE
 ****************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_SetNewGlobalTime(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStamp,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userData);

/**********************************************************************************************************************
 *  StbM_CalcNewGlobalTime()
 *********************************************************************************************************************/
/*! \brief       Calculate new global time
 *  \details     This function calculates the global time to the value given in timeStamp.
 *  \param[in]   timeBaseId              The time base, whose global time is updated.
 *  \param[in]   timeStamp               New time stamp.
 *  \param[in]   userData                New user data.
 *  \return      E_OK, if time notification time calculations succeeded.
 *               E_NOT_OK, otherwise.
 *  \pre         -
 *  \context    TASK
 *  \reentrant  FALSE
 ****************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalcNewGlobalTime(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStamp,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userData);
#endif

#if ((STBM_TIMEBASECONFIGIDXOFTIMEBASECONFIG == STD_ON) && (STBM_GLOBALTIMEMASTEROFTIMEBASECONFIG == STD_ON))
/**********************************************************************************************************************
 *  StbM_CalcNewOffsetTime()
 *********************************************************************************************************************/
/*! \brief       Calculates and sets new global offset time
 *  \details     This function calculates and sets the offset depending on the referenced synchronized time base value and the given timeStamp.
 *  \param[in]   timeBaseId              The offset time base, whose offset is updated.
 *  \param[in]   timeStamp               New time stamp.
 *  \return      E_OK - New global offset time was set
 *  \return      E_NOT_OK - New global offset time was not set
 *  \pre         Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
 *  \context    TASK
 *  \reentrant  FALSE
 ****************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalcNewOffsetTime(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr);

/**********************************************************************************************************************
 *  StbM_SetNewOffsetTime()
 *********************************************************************************************************************/
/*! \brief       Sets new global offset time
 *  \details     This function sets the offset depending on the referenced synchronized time base value and the given timeStamp.
 *  \param[in]   timeBaseId              The offset time base, whose offset is updated.
 *  \param[in]   timeStamp               New time stamp.
 *  \return      E_OK - New global offset time was set
 *  \return      E_NOT_OK - New global offset time was not set
 *  \pre         Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
 *  \context    TASK
 *  \reentrant  FALSE
 ****************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_SetNewOffsetTime(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr);
#endif

#if (STBM_TIME_RECORDING_SUPPORT_USED == STD_ON)
/**********************************************************************************************************************
 *  StbM_GetRecordTableStartIdx()
 *********************************************************************************************************************/
/*! \brief       Returns the record table start index of the given time base
 *  \details     This function returns the record table start index of the given time base for synchronized and offset time bases.
 *  \param[in]   timeBaseId              The time base, whose record table start index shall be retrieved.
 *  \return      Start index
 *  \pre         -
 *  \context    TASK
 *  \reentrant  FALSE
 ****************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(StbM_CurrentRecordTableBlockIdxOfTimeBaseStateType, STBM_CODE) StbM_GetRecordTableStartIdx(StbM_SynchronizedTimeBaseType timeBaseId);

/**********************************************************************************************************************
 *  StbM_GetRecordTableEndIdx()
 *********************************************************************************************************************/
/*! \brief       Returns the record table end index of the given time base
 *  \details     This function returns the record table end index of the given time base for synchronized and offset time bases.
 *  \param[in]   timeBaseId              The time base, whose record table end index shall be retrieved.
 *  \return      End index
 *  \pre         -
 *  \context    TASK
 *  \reentrant  FALSE
 ****************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(StbM_CurrentRecordTableBlockIdxOfTimeBaseStateType, STBM_CODE) StbM_GetRecordTableEndIdx(StbM_SynchronizedTimeBaseType timeBaseId);
#endif

/**********************************************************************************************************************
 *  StbM_InitializeEachTimeBase()
 *********************************************************************************************************************/
/*! \brief       Initialization of time base
 *  \details     This function initializes each time base
 *  \param[in]   timeBaseId    The synchronized time-base, whose time is of interest.
 *  \pre         Interrupts are disabled and StbM_InitMemory has been called.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \note        Specification of module initialization
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_InitializeEachTimeBase(StbM_TimeBaseConfigIterType timeBaseId);

#if (STBM_GPTLOCALTIMECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_SetGptChannel()
 *********************************************************************************************************************/
/*! \brief       Set GPT channel
 *  \details     This function sets the GPT channel active
 *  \param[in]   timeBaseId    The synchronized time-base, whose time is of interest.
 *  \pre         Interrupts are disabled and StbM_InitMemory has been called.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \note        Specification of module initialization
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_SetGptChannel(StbM_TimeBaseConfigIterType timeBaseId);
#endif

#if (STBM_ETHTSYN_LOCALTIME_USED == STD_ON)
/**********************************************************************************************************************
 *  StbM_SetLocalTime()
 *********************************************************************************************************************/
/*! \brief       Set local time
 *  \details     This function sets the local time of time base state
 *  \param[in]   timeBaseId    The synchronized time-base, whose time is of interest.
 *  \pre         Interrupts are disabled and StbM_InitMemory has been called.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \note        Specification of module initialization
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_SetLocalTime(StbM_TimeBaseConfigIterType timeBaseId);
#endif

#if ((STBM_RATEMEASUREMENTSTORAGE == STD_ON) || (STBM_MASTERRATECORRECTIONALLOWEDOFTIMEBASECONFIG == STD_ON))
/**********************************************************************************************************************
 *  StbM_InitializeRateCorrection()
 *********************************************************************************************************************/
/*! \brief       Initialize rate correction
 *  \details     This function initializes the rate correction
 *  \param[in]   timeBaseId    The synchronized time-base, whose rate correction is initialized.
 *  \pre         Interrupts are disabled and StbM_InitMemory has been called.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \note        Specification of module initialization
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_InitializeRateCorrection(StbM_TimeBaseConfigIterType timeBaseId);
#endif

#if (STBM_SYNCRECORDTABLEBLOCK == STD_ON)
/**********************************************************************************************************************
 *  StbM_GetRecordTableForSync()
 *********************************************************************************************************************/
/*! \brief       Get record tables
 *  \details     This function gets the record tables for sync slaves
 *  \param[in]   timeBaseId    The synchronized time-base, whose time is of interest.
 *  \pre         Interrupts are disabled and StbM_InitMemory has been called.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \note        Specification of module initialization
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_GetRecordTableForSync(StbM_TimeBaseConfigIterType timeBaseId);
#endif

#if (STBM_OFFSETRECORDTABLEBLOCK == STD_ON)
/**********************************************************************************************************************
 *  StbM_GetRecordTableForOffset()
 *********************************************************************************************************************/
/*! \brief       Get record tables
 *  \details     This function gets the record tables for offset slaves
 *  \param[in]   timeBaseId    The synchronized time-base, whose time is of interest.
 *  \pre         Interrupts are disabled and StbM_InitMemory has been called.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \note        Specification of module initialization
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_GetRecordTableForOffset(StbM_TimeBaseConfigIterType timeBaseId);
#endif

/**********************************************************************************************************************
 *  StbM_IterateOverTimeBases()
 *********************************************************************************************************************/
/*! \brief       Iterates over all time bases
 *  \details     This function iterates over all time bases if the module is initialized
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_IterateOverTimeBases(void);

#if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckIfTimeoutOccurred()
 *********************************************************************************************************************/
/*! \brief       Checks if the timeout has occurred
 *  \details     This function sets and syncs timeout notification
 *  \param[in]   timeBaseId    The synchronized time-base, whose time is of interest.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckIfTimeoutOccurred(StbM_SynchronizedTimeBaseType timeBaseId);
#endif

#if (STBM_TIME_RECORDING_SUPPORT_USED == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckAndNotify()
 *********************************************************************************************************************/
/*! \brief       Checks if record table is updated
 *  \details     This function checks the record table and notifies the application
 *  \param[in]   timeBaseId    The synchronized time-base, whose time is of interest.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndNotify(StbM_SynchronizedTimeBaseType timeBaseId);
#endif

#if (STBM_SYNCRECORDTABLEBLOCK == STD_ON)
/**********************************************************************************************************************
 *  StbM_NotifyTheApplicationForSyncTime()
 *********************************************************************************************************************/
/*! \brief       Notify the application by calling the callback block by block
 *  \details     This function notifies for synctime
 *  \param[in]   timeBaseId    The synchronized time-base, whose time is of interest.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_NotifyTheApplicationForSyncTime(StbM_SynchronizedTimeBaseType timeBaseId);
#endif

#if (STBM_OFFSETRECORDTABLEBLOCK == STD_ON)
/**********************************************************************************************************************
 *  StbM_NotifyTheApplicationForOffsetTime()
 *********************************************************************************************************************/
/*! \brief       Notify the application by calling the callback block by block
 *  \details     This function notifies for offsettime
 *  \param[in]   timeBaseId    The synchronized time-base, whose time is of interest.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_NotifyTheApplicationForOffsetTime(StbM_SynchronizedTimeBaseType timeBaseId);
#endif

#if (STBM_STATUSNOTIFICATIONCUSTOMERCONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CallNotificationCallBackAndClear()
 *********************************************************************************************************************/
/*! \brief       Call notification callback and clear events
 *  \details     This function clears events
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CallNotificationCallBackAndClear(void);
#endif

#if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckAndSetTime()
 *********************************************************************************************************************/
/*! \brief       Checks and sets the time
 *  \details     This function checks and sets the time and measurements
 *  \param[in]   timeBaseId              The synchronized time-base, whose time is set.
 *  \param[in]   timeStampPtr            New time stamp.
 *  \return      E_OK     - New global time was set
 *  \return      E_NOT_OK - New global time was not set
 *  \pre         Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
 *  \context     TASK
 *  \reentrant   FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CheckAndSetTime(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr);
#endif

#if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CalculationsOfTimestamps()
 *********************************************************************************************************************/
/*! \brief       Calculates expire time and updates the time stamps
 *  \details     This function updates the time stamps
 *  \param[in]   timeBaseId              The synchronized time-base, whose time is set.
 *  \param[in]   timeStampPtr            New time stamp.
 *  \return      E_OK     - New global time was set
 *  \return      E_NOT_OK - New global time was not set
 *  \pre         Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
 *  \context     TASK
 *  \reentrant   FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalculationsOfTimestamps(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr);
#endif

#if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CalculationsOfBusSetGlobalTime()
 *********************************************************************************************************************/
/*! \brief       Calculates the new global time
 *  \details     This function calculates the new global time
 *  \param[in]   timeBaseId              The synchronized time-base, whose time is set.
 *  \param[in]   timeStampPtr            New time stamp.
 *  \param[in]   userDataPtr             Valid pointer to new user data or NULL_PTR if user data shall not be updated
 *  \param[in]   measureDataPtr          New measurement data.
 *  \return      E_OK, if time notification time calculations succeeded.
 *               E_NOT_OK, otherwise.
 *  \pre         Exclusive Area STBM_EXCLUSIVE_AREA_0 is entered
 *  \context     TASK
 *  \reentrant   FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalculationsOfBusSetGlobalTime(StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userDataPtr,
  P2CONST(StbM_MeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr);
#endif

#if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_TimeLeapCheck()
 *********************************************************************************************************************/
/*! \brief       Checks the Time Leap
 *  \details     This function gets the global time base bit and checks the time leaps
 *  \param[in]   timeBaseId              The synchronized time-base, whose time is set.
 *  \param[in]   timeStampPtr            New time stamp.
 *  \return      E_OK     - New global time was set
 *  \return      E_NOT_OK - New global time was not set
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_TimeLeapCheck(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr);
#endif

#if ((STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON) && (STBM_STATUSNOTIFICATIONCUSTOMERCONFIG == STD_ON))
/**********************************************************************************************************************
 *  StbM_CheckAndSetSync()
 *********************************************************************************************************************/
/*! \brief       Checks the sync time base
 *  \details     This function sets various properties in sync time base
 *  \param[in]   timeBaseId              The synchronized time-base, whose time is set.
 *  \param[in]   timeStampPtr            New time stamp.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndSetSync(StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr);
#endif

#if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_SetTheGatewayAndTimeBaseBit()
 *********************************************************************************************************************/
/*! \brief       Sets the sync to gateway bit
 *  \details     This function sets sync time base to gateway bit
 *  \param[in]   timeBaseId              The synchronized time-base, whose time is set.
 *  \param[in]   timeStampPtr            New time stamp.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_SetTheGatewayAndTimeBaseBit(StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr);
#endif

#if ((STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON) && (STBM_TIME_RECORDING_SUPPORT_USED == STD_ON))
/**********************************************************************************************************************
 *  StbM_WriteResidualBlocks()
 *********************************************************************************************************************/
/*! \brief       Writes the residual blocks of record time
 *  \details     This function writes the residual blocks to sync and offset time bases
 *  \param[in]   timeBaseId              The synchronized time-base, whose time is set.
 *  \param[in]   measureDataPtr          New measurement data.
 *  \param[in]   currentRecordTableBlock  Current table block record.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_WriteResidualBlocks(StbM_SynchronizedTimeBaseType timeBaseId, P2CONST(StbM_MeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr);
#endif

#if ((STBM_MASTERRATECORRECTIONALLOWEDOFTIMEBASECONFIG == STD_ON) && (STBM_GLOBALTIMEMASTEROFTIMEBASECONFIG == STD_ON))
/**********************************************************************************************************************
 *  StbM_CalculateAndSetRateCorrection()
 *********************************************************************************************************************/
/*! \brief       Calculates rate correction
 *  \details     This function calculates and sets the rate correction
 *  \param[in]   timeBaseId              The synchronized time-base, whose rate is set.
 *  \param[in]   rateDeviation           New rate.
 *  \return      E_OK     - New rate was set
 *  \return      E_NOT_OK - New rate was not set
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalculateAndSetRateCorrection(
  StbM_SynchronizedTimeBaseType timeBaseId,
  StbM_RateDeviationType rateDeviation);
#endif

#if (STBM_TIMENOTIFICATIONCUSTOMERCONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CalculateExpireTime()
 *********************************************************************************************************************/
/*! \brief       Calculates expire time if expire time is valid
 *  \details     Checks if the timer is not already running
 *  \param[in]   timeBaseId       Time Base reference
 *  \param[in]   customerId       Id of customer
 *  \param[in]   expireTime       Time value relative to current Time Base value of the Notification Customer,
 *                                when the Timer shall expire
 *  \return      E_OK       -     successful
 *               E_NOT_OK   -     failed
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 ********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalculateExpireTime(
  StbM_SynchronizedTimeBaseType timeBaseId,
  StbM_CustomerIdType customerId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) expireTime);
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if (STBM_TRIGGEREDCUSTOMERCONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_IncrementCustomerCounter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_IncrementCustomerCounter(StbM_TriggeredCustomerStateIterType customerIdx)
{
  /* #10 If the customer counter is equal to the configured trigger customer period of the passed customer, it is set to one as overflow treatment. */
  if (StbM_GetTriggeredCustomerState(customerIdx).Counter == StbM_GetTriggeredCustomerPeriodOfTriggeredCustomerConfig(customerIdx))
  {
    /* It is set to one because this function is called after the StbM_MainFunction has run and therefore computed one cycle. */
    StbM_GetTriggeredCustomerState(customerIdx).Counter = 1u; /* SBSW_STBM_ACCESS_TRIGGEREDCUSTOMERSTATE */
  }
  else
  {
    /* #20 Else increment the customer counter of the given triggered customer. */
    StbM_GetTriggeredCustomerState(customerIdx).Counter += 1u; /* SBSW_STBM_ACCESS_TRIGGEREDCUSTOMERSTATE */
  }
}
#endif

/**********************************************************************************************************************
 *  StbM_IncrementTimeBaseUpdateCounter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_IncrementTimeBaseUpdateCounter(StbM_SynchronizedTimeBaseType timeBaseIdx)
{
  /* #10 Reset or increment the update counter of the given time base */
  if (StbM_GetUpdateCounterOfTimeBaseState(timeBaseIdx) == STBM_MAX_UPDATECOUNTEROFTIMEBASESTATE)
  {
    StbM_SetUpdateCounterOfTimeBaseState(timeBaseIdx, 0u); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  }
  else
  {
    StbM_IncUpdateCounterOfTimeBaseState(timeBaseIdx); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  }
}

/**********************************************************************************************************************
 *  StbM_UpdateTimestamp()
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
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_UpdateTimestamp(StbM_SynchronizedTimeBaseType timeBaseId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
#if ((STBM_OSLOCALTIMECONFIG == STD_ON) || (STBM_GPTLOCALTIMECONFIG == STD_ON))
  uint32 elapsedCounterValue;
#endif
  sint64 elapsedNanoseconds = 0;
#if (STBM_OSLOCALTIMECONFIG == STD_ON)
  TickType osTicks, elapsedOsCounterValue;
#endif
#if (STBM_GPTLOCALTIMECONFIG == STD_ON)
  uint32 OldGptChannelValue;
#endif
  StbM_TimeStampType timeStamp;

  /* ----- Implementation ----------------------------------------------- */
#if (STBM_OSLOCALTIMECONFIG == STD_ON)
  /* #10 If OS local time is used, set elapsed counter value to time passed in OS timer ticks and calculate the elapsed nanoseconds */
  if (StbM_IsOsLocalTimeUsed(timeBaseId))
  {
    osTicks = StbM_GetLocalTimeTickValueOfTimeBaseState(timeBaseId);
    (void) GetElapsedValue(StbM_GetOsLocalTimeIDOfOsLocalTimeConfig(StbM_GetOsLocalTimeConfigIdxOfTimeBaseConfig(timeBaseId)), &osTicks, &elapsedOsCounterValue); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */
    StbM_SetLocalTimeTickValueOfTimeBaseState(timeBaseId, (uint32) osTicks); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
    elapsedCounterValue = (uint32) elapsedOsCounterValue;
    StbM_CalculateElapsedTimeFromElapsedCounterValue(timeBaseId, elapsedCounterValue, &elapsedNanoseconds); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */
    retVal = E_OK;
  }
#endif
#if (STBM_GPTLOCALTIMECONFIG == STD_ON)
  /* #20 Else if GPT local time is used, set elapsed counter value to time passed in GPT ticks and calculate the elapsed nanoseconds */
# if ((STBM_OSLOCALTIMECONFIG == STD_ON) || (STBM_ETHTSYN_LOCALTIME_USED == STD_ON))
  if (StbM_IsGptLocalTimeUsed(timeBaseId))
# endif
  {
    OldGptChannelValue = StbM_GetLocalTimeTickValueOfTimeBaseState(timeBaseId);
    StbM_SetLocalTimeTickValueOfTimeBaseState(timeBaseId, (uint32) Gpt_GetTimeElapsed(StbM_GetGptLocalTimeIDOfGptLocalTimeConfig(StbM_GetGptLocalTimeConfigIdxOfTimeBaseConfig(timeBaseId)))); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
    /* check for overflow of tick value */
    if (OldGptChannelValue < StbM_GetLocalTimeTickValueOfTimeBaseState(timeBaseId))
    {
      elapsedCounterValue = StbM_GetLocalTimeTickValueOfTimeBaseState(timeBaseId) - OldGptChannelValue;
    }
    else
    {
      elapsedCounterValue = (StbM_GetLocalTimeMaxValueOfGptLocalTimeConfig(StbM_GetGptLocalTimeConfigIdxOfTimeBaseConfig(timeBaseId)) - OldGptChannelValue) + (1u + StbM_GetLocalTimeTickValueOfTimeBaseState(timeBaseId));
    }
    StbM_CalculateElapsedTimeFromElapsedCounterValue(timeBaseId, elapsedCounterValue, &elapsedNanoseconds); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */
# if ((STBM_OSLOCALTIMECONFIG == STD_ON) || (STBM_ETHTSYN_LOCALTIME_USED == STD_ON))
    retVal = E_OK;
# endif
  }
#endif

#if (STBM_ETHTSYN_LOCALTIME_USED == STD_ON)
  /* #30 Else if Eth TSyn local time is used, calculate the elapsed nanoseconds */
# if ((STBM_OSLOCALTIMECONFIG == STD_ON) || (STBM_GPTLOCALTIMECONFIG == STD_ON))
  if (StbM_IsUsesEthTSynLocalTimeOfTimeBaseConfig(timeBaseId))
# endif
  {
    retVal = StbM_CalculateElapsedTimeForEthTSyn(timeBaseId, &elapsedNanoseconds); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */
  }
#endif

#if ((STBM_OSLOCALTIMECONFIG == STD_ON) || (STBM_ETHTSYN_LOCALTIME_USED == STD_ON))
  if (retVal == E_OK)
#endif
  {
    /* #40 Update the timestamp with the elapsed nanoseconds */
    retVal = StbM_TimestampPlusTimediff(&StbM_GetTimeStampOfTimeBaseState(timeBaseId), elapsedNanoseconds, &timeStamp); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */
    StbM_GetTimeStampOfTimeBaseState(timeBaseId).nanoseconds = timeStamp.nanoseconds; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
    StbM_GetTimeStampOfTimeBaseState(timeBaseId).seconds = timeStamp.seconds; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
    StbM_GetTimeStampOfTimeBaseState(timeBaseId).secondsHi = timeStamp.secondsHi; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  }

  if (retVal == E_OK)
  {
    /* #50 Update the virtual local timestamp with the elapsed nanoseconds */
    retVal = StbM_TimestampPlusTimediff(&StbM_GetVirtualLocalTimeStampOfTimeBaseState(timeBaseId), elapsedNanoseconds, &timeStamp); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */
    StbM_GetVirtualLocalTimeStampOfTimeBaseState(timeBaseId).nanoseconds = timeStamp.nanoseconds; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
    StbM_GetVirtualLocalTimeStampOfTimeBaseState(timeBaseId).seconds = timeStamp.seconds; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
    StbM_GetVirtualLocalTimeStampOfTimeBaseState(timeBaseId).secondsHi = timeStamp.secondsHi; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  }

  return retVal;
} /* StbM_UpdateTimestamp() */

#if ((STBM_OSLOCALTIMECONFIG == STD_ON) || (STBM_GPTLOCALTIMECONFIG == STD_ON))
/**********************************************************************************************************************
 *  StbM_CalculateElapsedTimeFromElapsedCounterValue()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CalculateElapsedTimeFromElapsedCounterValue(
  StbM_SynchronizedTimeBaseType timeBaseId,
  uint32 elapsedCounterValue,
  P2VAR(sint64, AUTOMATIC, STBM_APPL_VAR) elapsedNanoseconds)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint64 elapsedTime;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate elapsed nanoseconds */
  elapsedTime = ((elapsedCounterValue * (uint64)StbM_GetLocalTimeFactorOfTimeBaseConfig(timeBaseId)) / StbM_GetLocalTimeDivisorOfTimeBaseConfig(timeBaseId)) + StbM_GetTimeStampFractionalPartOfTimeBaseState(timeBaseId);
  *elapsedNanoseconds = (sint64)(elapsedTime / 1000000uL); /* PRQA S 4394 */ /* MD_StbM_Rule10.8 */ /* SBSW_STBM_ACCESS_PARAMPTR */
  /* #20 Calculate and store fractional part of nanoseconds */
  StbM_SetTimeStampFractionalPartOfTimeBaseState(timeBaseId, (uint32)(elapsedTime - ((uint64)*elapsedNanoseconds * 1000000uL))); /* SBSW_STBM_ACCESS_TIMEBASESTATE */

} /* StbM_CalculateElapsedTimeFromElapsedCounterValue() */
#endif

#if (STBM_ETHTSYN_LOCALTIME_USED == STD_ON)
/**********************************************************************************************************************
 *  StbM_CalculateElapsedTimeForEthTSyn()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalculateElapsedTimeForEthTSyn(StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(sint64, AUTOMATIC, STBM_APPL_VAR) elapsedNanoseconds)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  Eth_ModeType ethIfMode;
  Eth_TimeStampQualType ethIfTimeQual;
  Eth_TimeStampType ethIfTimeStamp;
  StbM_TimeStampType newLocalTime;
  StbM_TimeStampType oldLocalTime;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Get current time from EthIf after checking its availability */
  retVal = EthIf_GetControllerMode(StbM_GetEthIfCtrlIdxOfTimeBaseConfig(timeBaseId), &ethIfMode); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */
  if ((retVal == E_OK) && (ethIfMode == ETH_MODE_ACTIVE))
  {
    retVal = EthIf_GetCurrentTime(StbM_GetEthIfCtrlIdxOfTimeBaseConfig(timeBaseId), &ethIfTimeQual, &ethIfTimeStamp); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */
    /* #20 If getting the current time was successful */
    if ((retVal == E_OK) && (ethIfTimeQual == ETH_VALID))
    {
      newLocalTime.nanoseconds = ethIfTimeStamp.nanoseconds;
      newLocalTime.seconds = ethIfTimeStamp.seconds;
      newLocalTime.secondsHi = ethIfTimeStamp.secondsHi;

      oldLocalTime.nanoseconds = StbM_GetEthLocalTimeOfTimeBaseState(timeBaseId).nanoseconds;
      oldLocalTime.seconds = StbM_GetEthLocalTimeOfTimeBaseState(timeBaseId).seconds;
      oldLocalTime.secondsHi = StbM_GetEthLocalTimeOfTimeBaseState(timeBaseId).secondsHi;

      /* #30 Calculate nanoseconds passed in Eth TSyn clock */
      retVal = StbM_TimestampMinusTimestampInNs(&newLocalTime, &oldLocalTime, elapsedNanoseconds); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */
      if (retVal == E_OK)
      {
        if (*elapsedNanoseconds >= 0)
        {
          StbM_SetEthLocalTimeOfTimeBaseState(timeBaseId, ethIfTimeStamp); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
        }
        else
        {
          retVal = E_NOT_OK;
        }
      }
    }
  }
  else
  {
    retVal = E_NOT_OK;
  }

  return retVal;
} /* StbM_CalculateElapsedTimeForEthTSyn() */
#endif

/**********************************************************************************************************************
 *  StbM_TimestampPlusTimestamp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_TimestampPlusTimestamp(
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timestamp1Ptr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timestamp2Ptr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_VAR) timesumPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 add the two timestamps */
  timesumPtr->nanoseconds = timestamp1Ptr->nanoseconds + timestamp2Ptr->nanoseconds; /* SBSW_STBM_ACCESS_PARAMPTR */
  timesumPtr->seconds = timestamp1Ptr->seconds + timestamp2Ptr->seconds; /* SBSW_STBM_ACCESS_PARAMPTR */
  timesumPtr->secondsHi = timestamp1Ptr->secondsHi + timestamp2Ptr->secondsHi; /* SBSW_STBM_ACCESS_PARAMPTR */

  /* #20 check for overflow of nanoseconds */
  /* no real overflow of nanoseconds possible, since max value is 10^9 - 1 */
  if (timesumPtr->nanoseconds > STBM_TIMESTAMP_MAX_NANOSECONDS)
  {
    timesumPtr->seconds++; /* SBSW_STBM_ACCESS_PARAMPTR */
    timesumPtr->nanoseconds -= STBM_NANOSECONDS_IN_ONE_SECOND; /* SBSW_STBM_ACCESS_PARAMPTR */
  }

  /* #30 check for overflow of seconds */
  if (timesumPtr->seconds < (timestamp1Ptr->seconds | timestamp2Ptr->seconds))
  {
    timesumPtr->secondsHi++; /* SBSW_STBM_ACCESS_PARAMPTR */
  }

  /* #40 check for overflow of seconds high */
  /* calculated sum is invalid, if overflow of secondsHi occurred */
  if ((timesumPtr->secondsHi >= timestamp1Ptr->secondsHi) && (timesumPtr->secondsHi >= timestamp2Ptr->secondsHi))
  {
    retVal = E_OK;
  }

  return retVal;
} /* StbM_TimestampPlusTimestamp() */

/**********************************************************************************************************************
 *  StbM_TimestampPlusTimediff()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_TimestampPlusTimediff(
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timestampPtr,
  sint64 timediff,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_VAR) timesumPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint64 timediffSeconds;
  StbM_TimeStampType timestampDiff = { 0, 0, 0, 0 };

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If time difference is larger than zero */
  if (timediff > 0)
  {
    /* #20 Calculate and add timestamp for the time difference */
    timediffSeconds = ((uint64)timediff / (uint64)STBM_NANOSECONDS_IN_ONE_SECOND);
    timestampDiff.secondsHi = (uint16) (timediffSeconds >> 32u);
    timestampDiff.seconds = (uint32) timediffSeconds;
    timestampDiff.nanoseconds = (uint32)((uint64)timediff % STBM_NANOSECONDS_IN_ONE_SECOND);
    retVal = StbM_TimestampPlusTimestamp(timestampPtr, &timestampDiff, timesumPtr); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_PARAMPTR */
  }
  /* #30 If time difference is equal or lower than zero */
  else
  {
    /* #40 Calculate and subtract timestamp for the time difference */
    timediffSeconds = ((uint64)-timediff / (uint64)STBM_NANOSECONDS_IN_ONE_SECOND);
    timestampDiff.secondsHi = (uint16) (timediffSeconds >> 32u);
    timestampDiff.seconds = (uint32) timediffSeconds;
    timestampDiff.nanoseconds = ((uint32) - timediff % STBM_NANOSECONDS_IN_ONE_SECOND);
    retVal = StbM_TimestampMinusTimestamp(timestampPtr, &timestampDiff, timesumPtr); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_PARAMPTR */
  }
  return retVal;
} /* StbM_TimestampPlusTimediff() */

/**********************************************************************************************************************
 *  StbM_TimestampMinusTimestamp()
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
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_TimestampMinusTimestamp(
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timestamp1Ptr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timestamp2Ptr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_VAR) timediffPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If seconds high 1 is equal or larger than seconds high 2 */
  if (timestamp1Ptr->secondsHi >= timestamp2Ptr->secondsHi)
  {
    /* #20 Calculate time difference */
    timediffPtr->secondsHi = timestamp1Ptr->secondsHi - timestamp2Ptr->secondsHi; /* SBSW_STBM_ACCESS_PARAMPTR */
    timediffPtr->seconds = timestamp1Ptr->seconds - timestamp2Ptr->seconds; /* SBSW_STBM_ACCESS_PARAMPTR */

    /* #30 Check for overflow of seconds */
    if (timestamp1Ptr->seconds < timestamp2Ptr->seconds)
    {
      timediffPtr->secondsHi--; /* SBSW_STBM_ACCESS_PARAMPTR */
    }

    /* #40 Check for overflow of nanoseconds */
    if (timestamp1Ptr->nanoseconds < timestamp2Ptr->nanoseconds)
    {
      timediffPtr->seconds--; /* SBSW_STBM_ACCESS_PARAMPTR */

      /* #50 Check for overflow of seconds */
      if (timediffPtr->seconds == STBM_TIMESTAMP_MAX_SECONDS)
      {
        timediffPtr->secondsHi--; /* SBSW_STBM_ACCESS_PARAMPTR */
      }

      timediffPtr->nanoseconds = (STBM_TIMESTAMP_MAX_NANOSECONDS - timestamp2Ptr->nanoseconds) + (1u + timestamp1Ptr->nanoseconds); /* SBSW_STBM_ACCESS_PARAMPTR */
    }
    else
    {
      timediffPtr->nanoseconds = timestamp1Ptr->nanoseconds - timestamp2Ptr->nanoseconds; /* SBSW_STBM_ACCESS_PARAMPTR */
    }
    retVal = E_OK;
  }
  return retVal;
} /* StbM_TimestampMinusTimestamp() */

/**********************************************************************************************************************
 *  StbM_TimestampMinusTimestampInNs()
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
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_TimestampMinusTimestampInNs(
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timestamp1Ptr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timestamp2Ptr,
  P2VAR(sint64, AUTOMATIC, STBM_APPL_VAR) timediffPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If secondsHi 1 is equal or larger than secondsHi 2, subtract secondsHi 2 from secondsHi 1 */
  if (timestamp1Ptr->secondsHi >= timestamp2Ptr->secondsHi)
  {
    *timediffPtr = (sint64)(((uint64)timestamp1Ptr->secondsHi << 32u) - ((uint64)timestamp2Ptr->secondsHi << 32u)); /* PRQA S 4394 */ /* MD_StbM_Rule10.8 */ /* SBSW_STBM_ACCESS_PARAMPTR */
  }
  /* #20 Else, subtract secondsHi 1 from secondsHi 2 */
  else
  {
    *timediffPtr = -(sint64)(((uint64)timestamp2Ptr->secondsHi << 32u) - ((uint64)timestamp1Ptr->secondsHi << 32u)); /* PRQA S 4394 */ /* MD_StbM_Rule10.8 */ /* SBSW_STBM_ACCESS_PARAMPTR */
  }

  /* #30 If seconds 1 is equal or larger than seconds 2, subtract seconds 2 from seconds 1 */
  if (timestamp1Ptr->seconds >= timestamp2Ptr->seconds)
  {
    *timediffPtr += ((sint64)timestamp1Ptr->seconds - (sint64)timestamp2Ptr->seconds); /* SBSW_STBM_ACCESS_PARAMPTR */
  }
  /* #40 Else, subtract seconds 1 from seconds 2 */
  else
  {
    *timediffPtr += -((sint64)timestamp2Ptr->seconds - (sint64)timestamp1Ptr->seconds); /* SBSW_STBM_ACCESS_PARAMPTR */
  }

  /* #50 If time difference in seconds is suitable for nanoseconds difference value */
  if ((*timediffPtr > -(sint64)STBM_TIMEDIFF_MAX_SECONDS) && (*timediffPtr < (sint64)STBM_TIMEDIFF_MAX_SECONDS))
  {
    /* #60 Convert time difference to nanoseconds */
    *timediffPtr *= (sint64) STBM_NANOSECONDS_IN_ONE_SECOND; /* SBSW_STBM_ACCESS_PARAMPTR */
    /* #70 If nanoseconds 1 is greater or equal nanoseconds 2, add nanoseconds difference to time difference */
    if (timestamp1Ptr->nanoseconds >= timestamp2Ptr->nanoseconds)
    {
      *timediffPtr += ((sint64)timestamp1Ptr->nanoseconds - (sint64)timestamp2Ptr->nanoseconds); /* SBSW_STBM_ACCESS_PARAMPTR */
    }
    /* #80 Else, subtract nanoseconds difference from time difference */
    else
    {
      *timediffPtr += -((sint64)timestamp2Ptr->nanoseconds - (sint64)timestamp1Ptr->nanoseconds); /* SBSW_STBM_ACCESS_PARAMPTR */
    }
    retVal = E_OK;
  }

  return retVal;
} /* StbM_TimestampMinusTimestampInNs() */

/**********************************************************************************************************************
 *  StbM_CalcTimeAndGetUserData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalcTimeAndGetUserData(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_VAR) timeStampPtr,
  P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_VAR) userDataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate current time of time base */
#if (STBM_TIMEBASECONFIGIDXOFTIMEBASECONFIG == STD_ON)
  if (StbM_IsOffsetTimeBase(timeBaseId))
  {
    retVal = StbM_CalculateCurrentOffsetTime(timeBaseId, timeStampPtr, userDataPtr); /* SBSW_STBM_FUNCTIONCALL_PARAMPTR */
  }
  else
#endif
  {
    retVal = StbM_CalculateCurrentTime(timeBaseId, timeStampPtr, userDataPtr); /* SBSW_STBM_FUNCTIONCALL_PARAMPTR */
  }

  return retVal;
} /* StbM_CalcTimeAndGetUserData() */

/**********************************************************************************************************************
 *  StbM_CalculateCurrentTime()
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
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalculateCurrentTime(StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_VAR) timeStampPtr,
  P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_VAR) userDataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
#if ((STBM_RATEMEASUREMENTSTORAGE == STD_ON) || (STBM_MASTERRATECORRECTIONALLOWEDOFTIMEBASECONFIG == STD_ON))
  sint64 diffVirtualLocalTime;
  sint64 diffOffset;
#endif

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Update local Time-Base */
  retVal = StbM_UpdateTimestamp(timeBaseId);

  /* #20 If Time-Base was correctly updated */
  if (retVal == E_OK)
  {
#if ((STBM_RATEMEASUREMENTSTORAGE == STD_ON) || (STBM_MASTERRATECORRECTIONALLOWEDOFTIMEBASECONFIG == STD_ON))
    /* #30 If rate correction has been set */
    if (StbM_IsRateCorrectionSetOfTimeBaseState(timeBaseId))
    {
      retVal = StbM_TimestampMinusTimestampInNs(&StbM_GetSyncGlobalTimeStampOfTimeBaseState(timeBaseId), &StbM_GetSyncLocalTimeStampOfTimeBaseState(timeBaseId), &diffOffset); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */

      if (retVal == E_OK)
      {
        retVal = StbM_TimestampMinusTimestampInNs(&StbM_GetVirtualLocalTimeStampOfTimeBaseState(timeBaseId), &StbM_GetSyncVirtualLocalTimeStampOfTimeBaseState(timeBaseId), &diffVirtualLocalTime); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */
        if (retVal == E_OK)
        {
          /* #40 Correct local time with last calculated rate */
          retVal = StbM_CalculationsOfRateAndAdaptiveCorrection(timeBaseId, timeStampPtr, diffOffset, diffVirtualLocalTime); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */
          /* #50 Set timeBaseStatus of time stamp pointer to current status of the time base */
          timeStampPtr->timeBaseStatus = StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus; /* SBSW_STBM_ACCESS_PARAMPTR */
        }
      }
    }
    /* #60 Else set current time stamp pointer to updated local time stamp */
    else
#endif
    {
      *timeStampPtr = StbM_GetTimeStampOfTimeBaseState(timeBaseId); /* SBSW_STBM_ACCESS_PARAMPTR */
    }
    /* #70 Get user data */
    *userDataPtr = StbM_GetUserDataOfTimeBaseState(timeBaseId); /* SBSW_STBM_ACCESS_PARAMPTR */
  }

  return retVal;
} /* StbM_CalculateCurrentTime() */

#if ((STBM_RATEMEASUREMENTSTORAGE == STD_ON) || (STBM_MASTERRATECORRECTIONALLOWEDOFTIMEBASECONFIG == STD_ON))
/**********************************************************************************************************************
 *  StbM_CalculationsOfRateAndAdaptiveCorrection()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalculationsOfRateAndAdaptiveCorrection(StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_VAR) timeStampPtr, sint64 diffOffset, sint64 diffVirtualLocalTime)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  sint64 correctedLocalTime;
  uint64 diffOffsetAbs;
  float64 offsetCorrectionRate;

  /* ----- Implementation ----------------------------------------------- */
  diffOffsetAbs = StbM_GetAbsoluteValue(diffOffset);

  /* #10 If absolute difference between start global time and start local time exceeds jump threshold or adaptive rate correction interval is exceeded */
  if (
# if (STBM_MASTERRATECORRECTIONALLOWEDOFTIMEBASECONFIG == STD_ON)
    (StbM_IsMasterRateCorrectionAllowedOfTimeBaseConfig(timeBaseId)) ||
# endif
    (diffOffsetAbs >= StbM_GetOffsetCorrectionJumpThresholdOfTimeBaseConfig(timeBaseId)) || ((uint64)diffVirtualLocalTime > StbM_GetOffsetCorrectionAdaptionIntervalOfTimeBaseConfig(timeBaseId))) /* COV_STBM_RATECORRECTION */
  {
    /* #20 Perform rate correction */
    correctedLocalTime = (sint64)((float64)diffVirtualLocalTime * StbM_GetRateCorrectionOfTimeBaseState(timeBaseId)); /* PRQA S 4395 */ /* MD_StbM_Rule10.8 */
    retVal = StbM_TimestampPlusTimediff(&StbM_GetSyncGlobalTimeStampOfTimeBaseState(timeBaseId), correctedLocalTime, timeStampPtr); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_PARAMPTR */
  }
  else
  {
    /* #30 Else perform rate and adaptive offset correction */
    offsetCorrectionRate = ((float64)diffOffset / (float64)StbM_GetOffsetCorrectionAdaptionIntervalOfTimeBaseConfig(timeBaseId)) + 1.0;
    correctedLocalTime = (sint64)((float64)diffVirtualLocalTime * StbM_GetRateCorrectionOfTimeBaseState(timeBaseId) * offsetCorrectionRate); /* PRQA S 4395 */ /* MD_StbM_Rule10.8 */
    retVal = StbM_TimestampPlusTimediff(&StbM_GetSyncLocalTimeStampOfTimeBaseState(timeBaseId), correctedLocalTime, timeStampPtr); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_PARAMPTR */
  }

  return retVal;
} /* StbM_CalculationsOfRateAndAdaptiveCorrection() */
#endif


#if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckTimeLeapFuture()
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
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CheckTimeLeapFuture(StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  StbM_TimeStampType diffTimeStamp;
  sint64 diffTime;
  boolean decrementCounter = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If time leap future threshold is configured */
  if ((StbM_GetTimeLeapFutureThresholdSecOfTimeBaseConfig(timeBaseId) > 0u) || (StbM_GetTimeLeapFutureThresholdNsecOfTimeBaseConfig(timeBaseId) > 0u)) /* COV_STBM_TIMELEAP_ACTIVE */
  {
    /* #20 Calculate absolute time difference */
    if ((timeStampPtr->secondsHi > StbM_GetTimeStampOfTimeBaseState(timeBaseId).secondsHi)
      || ((timeStampPtr->secondsHi == StbM_GetTimeStampOfTimeBaseState(timeBaseId).secondsHi) && (timeStampPtr->seconds > StbM_GetTimeStampOfTimeBaseState(timeBaseId).seconds))
      || ((timeStampPtr->secondsHi == StbM_GetTimeStampOfTimeBaseState(timeBaseId).secondsHi) && (timeStampPtr->seconds == StbM_GetTimeStampOfTimeBaseState(timeBaseId).seconds) && (timeStampPtr->nanoseconds > StbM_GetTimeStampOfTimeBaseState(timeBaseId).nanoseconds))) /* COV_STBM_TIMELEAP_DIFFERENCE */
    {
      (void) StbM_TimestampMinusTimestamp(timeStampPtr, &StbM_GetTimeStampOfTimeBaseState(timeBaseId), &diffTimeStamp); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */

      /* #30 If absolute time difference has exceeded threshold */
      if ((diffTimeStamp.secondsHi > 0u) || (diffTimeStamp.seconds > StbM_GetTimeLeapFutureThresholdSecOfTimeBaseConfig(timeBaseId)) || ((diffTimeStamp.seconds == StbM_GetTimeLeapFutureThresholdSecOfTimeBaseConfig(timeBaseId)) && (diffTimeStamp.nanoseconds > StbM_GetTimeLeapFutureThresholdNsecOfTimeBaseConfig(timeBaseId)))) /* COV_STBM_TIMELEAP_POSITIVE */
      {
        /* #40 Set time leap future bit and counter */
# if (STBM_STATUSNOTIFICATIONCUSTOMERCONFIG == STD_ON)
        StbM_CheckAndSetTimeleapFutureNotificationEv(timeBaseId);
# endif
        StbM_SetTimeLeapFutureBit(StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
        StbM_SetTimeLeapFutureThresholdCountOfTimeBaseState(timeBaseId, StbM_GetClearTimeleapCountOfTimeBaseConfig(timeBaseId)); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
        decrementCounter = FALSE;
        retVal = StbM_TimestampMinusTimestampInNs(timeStampPtr, &StbM_GetTimeStampOfTimeBaseState(timeBaseId), &diffTime); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */
        if (retVal  == E_OK)
        {
          StbM_SetLastTimeLeapValueOfTimeBaseState(timeBaseId, diffTime); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
        }

# if (STBM_RATEMEASUREMENTSTORAGE == STD_ON)
        /* #50 Discard rate measurements */
        StbM_DiscardRateMeasurements(timeBaseId);
# endif
      }
    }

    /* #60 Handle time leap future counter */
    if ((StbM_GetTimeLeapFutureThresholdCountOfTimeBaseState(timeBaseId) > 0u) && decrementCounter) /* PRQA S 4558 */ /* MD_MSR_AutosarBoolean */
    {
      StbM_DecTimeLeapFutureThresholdCountOfTimeBaseState(timeBaseId); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
      /* #70 Clear time leap future bit, if time leap future counter has expired */
      if (StbM_GetTimeLeapFutureThresholdCountOfTimeBaseState(timeBaseId) == 0u) /* COV_STBM_TIMELEAP_COUNT */
      {
# if (STBM_STATUSNOTIFICATIONCUSTOMERCONFIG == STD_ON)
        StbM_CheckAndSetTimeleapFutureRemovedNotificationEv(timeBaseId);
# endif
        StbM_ClearTimeLeapFutureBit(StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
        StbM_SetLastTimeLeapValueOfTimeBaseState(timeBaseId, 0); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
      }
    }
  }

  return retVal;
} /* StbM_CheckTimeLeapFuture() */
#endif

#if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckTimeLeapPast()
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
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CheckTimeLeapPast(StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  StbM_TimeStampType diffTimeStamp;
  sint64 diffTime;
  boolean decrementCounter = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If time leap past threshold is configured */
  if ((StbM_GetTimeLeapPastThresholdSecOfTimeBaseConfig(timeBaseId) > 0u) || (StbM_GetTimeLeapPastThresholdNsecOfTimeBaseConfig(timeBaseId) > 0u)) /* COV_STBM_TIMELEAP_ACTIVE */
  {
    /* #20 Calculate absolute time difference */
    if ((timeStampPtr->secondsHi < StbM_GetTimeStampOfTimeBaseState(timeBaseId).secondsHi)
      || ((timeStampPtr->secondsHi == StbM_GetTimeStampOfTimeBaseState(timeBaseId).secondsHi) && (timeStampPtr->seconds < StbM_GetTimeStampOfTimeBaseState(timeBaseId).seconds))
      || ((timeStampPtr->secondsHi == StbM_GetTimeStampOfTimeBaseState(timeBaseId).secondsHi) && (timeStampPtr->seconds == StbM_GetTimeStampOfTimeBaseState(timeBaseId).seconds) && (timeStampPtr->nanoseconds < StbM_GetTimeStampOfTimeBaseState(timeBaseId).nanoseconds))) /* COV_STBM_TIMELEAP_DIFFERENCE */
    {
      (void) StbM_TimestampMinusTimestamp(&StbM_GetTimeStampOfTimeBaseState(timeBaseId), timeStampPtr, &diffTimeStamp); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */

      /* #30 If absolute time difference has exceeded threshold */
      if ((diffTimeStamp.secondsHi > 0u) || (diffTimeStamp.seconds > StbM_GetTimeLeapPastThresholdSecOfTimeBaseConfig(timeBaseId)) || ((diffTimeStamp.seconds == StbM_GetTimeLeapPastThresholdSecOfTimeBaseConfig(timeBaseId)) && (diffTimeStamp.nanoseconds > StbM_GetTimeLeapPastThresholdNsecOfTimeBaseConfig(timeBaseId)))) /* COV_STBM_TIMELEAP_NEGATIVE */
      {
        /* #40 Set time leap past bit and counter */
# if (STBM_STATUSNOTIFICATIONCUSTOMERCONFIG == STD_ON)
        StbM_CheckAndSetTimeleapPastNotificationEv(timeBaseId);
# endif
        StbM_SetTimeLeapPastBit(StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
        StbM_SetTimeLeapPastThresholdCountOfTimeBaseState(timeBaseId, StbM_GetClearTimeleapCountOfTimeBaseConfig(timeBaseId)); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
        decrementCounter = FALSE;
        retVal = StbM_TimestampMinusTimestampInNs(timeStampPtr, &StbM_GetTimeStampOfTimeBaseState(timeBaseId), &diffTime); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */
        if (retVal == E_OK)
        {
          StbM_SetLastTimeLeapValueOfTimeBaseState(timeBaseId, diffTime); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
        }

# if (STBM_RATEMEASUREMENTSTORAGE == STD_ON)
        /* #50 Discard rate measurements */
        StbM_DiscardRateMeasurements(timeBaseId);
# endif
      }
    }

    /* #60 Handle time leap past counter */
    if ((StbM_GetTimeLeapPastThresholdCountOfTimeBaseState(timeBaseId) > 0u) && decrementCounter) /* PRQA S 4558 */ /* MD_MSR_AutosarBoolean */
    {
      StbM_DecTimeLeapPastThresholdCountOfTimeBaseState(timeBaseId); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
      /* #70 Clear time leap past bit, if time leap future counter has expired */
      if (StbM_GetTimeLeapPastThresholdCountOfTimeBaseState(timeBaseId) == 0u) /* COV_STBM_TIMELEAP_COUNT */
      {
# if (STBM_STATUSNOTIFICATIONCUSTOMERCONFIG == STD_ON)
        StbM_CheckAndSetTimeleapPastRemovedNotificationEv(timeBaseId);
# endif
        StbM_ClearTimeLeapPastBit(StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
        StbM_SetLastTimeLeapValueOfTimeBaseState(timeBaseId, 0); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
      }
    }
  }

  return retVal;
} /* StbM_CheckTimeLeapPast() */
#endif

/**********************************************************************************************************************
 *  StbM_CopyUserData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CopyUserData(
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userDataPtrSrc,
  P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userDataPtrDst)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Copy as many user data bytes from src to dst, as given in src user data length */
  switch (userDataPtrSrc->userDataLength)
  {
    case 3:
      userDataPtrDst->userByte0 = userDataPtrSrc->userByte0; /* SBSW_STBM_ACCESS_PARAMPTR */
      userDataPtrDst->userByte1 = userDataPtrSrc->userByte1; /* SBSW_STBM_ACCESS_PARAMPTR */
      userDataPtrDst->userByte2 = userDataPtrSrc->userByte2; /* SBSW_STBM_ACCESS_PARAMPTR */
      break;

    case 2:
      userDataPtrDst->userByte0 = userDataPtrSrc->userByte0; /* SBSW_STBM_ACCESS_PARAMPTR */
      userDataPtrDst->userByte1 = userDataPtrSrc->userByte1; /* SBSW_STBM_ACCESS_PARAMPTR */
      break;

    case 1:
      userDataPtrDst->userByte0 = userDataPtrSrc->userByte0; /* SBSW_STBM_ACCESS_PARAMPTR */
      break;

    default:
      /* In this error case nothing is copied. */
      break;
  }

  /* #20 If src user data length is greater than dst user data length, set dst user data length to new value */
  if (userDataPtrSrc->userDataLength > userDataPtrDst->userDataLength)
  {
    userDataPtrDst->userDataLength = userDataPtrSrc->userDataLength; /* SBSW_STBM_ACCESS_PARAMPTR */
  }
} /* StbM_CopyUserData() */

#if ((STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON) && (STBM_RATEMEASUREMENTSTORAGE == STD_ON))
/**********************************************************************************************************************
 *  StbM_EvaluateRateMeasurement()
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
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_EvaluateRateMeasurement(StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr,
  P2VAR(boolean, AUTOMATIC, STBM_APPL_VAR) startNewRateMeasurement)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  sint64 diffVirtualLocalTime;
  StbM_CurrentRateMeasurementIdxOfTimeBaseStateType previousRateMeasurement;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize request for start of new rate measurement with FALSE */
  *startNewRateMeasurement = FALSE; /* SBSW_STBM_ACCESS_PARAMPTR */

  /* #20 If the current measurement was started before */
  if ((StbM_GetRateMeasurementStorage(StbM_GetCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId)).StartGlobalTime.nanoseconds > 0u) ||
     (StbM_GetRateMeasurementStorage(StbM_GetCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId)).StartGlobalTime.seconds > 0u) ||
     (StbM_GetRateMeasurementStorage(StbM_GetCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId)).StartGlobalTime.secondsHi > 0u))
  {
# if (STBM_RATECORRECTIONFOROFFSETTIMEBASEOFTIMEBASECONFIG == STD_ON)
    if (StbM_IsOffsetTimeBase(timeBaseId))
    {
      retVal = StbM_TimestampMinusTimestampInNs(&StbM_GetVirtualLocalTimeStampOfTimeBaseState(StbM_GetTimeBaseConfigIdxOfTimeBaseConfig(timeBaseId)), &StbM_GetRateMeasurementStorage(StbM_GetCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId)).StartVirtualLocalTime, &diffVirtualLocalTime); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */
    }
    else
# endif
    {
      retVal = StbM_TimestampMinusTimestampInNs(&StbM_GetVirtualLocalTimeStampOfTimeBaseState(timeBaseId), &StbM_GetRateMeasurementStorage(StbM_GetCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId)).StartVirtualLocalTime, &diffVirtualLocalTime); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */
    }

    /* #30 Check if measurement duration has passed */
    if ((retVal == E_OK) && ((uint64)diffVirtualLocalTime >= StbM_GetRateCorrectionMeasurementDurationOfTimeBaseConfig(timeBaseId)))
    {
      /* #40 If the measurement does not need to be discarded */
      if (StbM_GetRateMeasurementStorage(StbM_GetCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId)).Discard == FALSE)
      {
        /* #50 Calculate rate correction value */
        retVal = StbM_CalculateRateCorrection(timeBaseId, timeStampPtr); /* SBSW_STBM_FUNCTIONCALL_PARAMPTR */
        /* #60 Request start of new rate measurement */
        *startNewRateMeasurement = TRUE; /* SBSW_STBM_ACCESS_PARAMPTR */
      }
      else
      {
        if (StbM_GetCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId) == StbM_GetRateMeasurementStorageStartIdxOfTimeBaseConfig(timeBaseId))
        {
          previousRateMeasurement = (StbM_GetRateMeasurementStorageEndIdxOfTimeBaseConfig(timeBaseId) - 1u);
        }
        else
        {
          previousRateMeasurement = (StbM_GetCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId) - 1u);
        }
        /* #80 Request start of new rate measurement if offset has passed */
        retVal = StbM_CheckRateMeasurementOffset(timeBaseId, previousRateMeasurement, startNewRateMeasurement); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */
      }
    }
  }
  /* #70 else if previous rate measurement was started */
  else if (StbM_GetCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId) > StbM_GetRateMeasurementStorageStartIdxOfTimeBaseConfig(timeBaseId))
  {
    /* #80 Request start of new rate measurement if offset has passed */
    retVal = StbM_CheckRateMeasurementOffset(timeBaseId, (StbM_GetCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId) - 1u), startNewRateMeasurement); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */
  }
  /* #90 Otherwise request new rate measurement */
  else
  {
    /* start first measurement */
    *startNewRateMeasurement = TRUE; /* SBSW_STBM_ACCESS_PARAMPTR */
  }

  return retVal;
} /* StbM_EvaluateRateMeasurement() */

/**********************************************************************************************************************
*  StbM_CheckRateMeasurementOffset()
*********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
*/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CheckRateMeasurementOffset(StbM_SynchronizedTimeBaseType timeBaseId,
  StbM_CurrentRateMeasurementIdxOfTimeBaseStateType rateMeasurementIdx,
  P2VAR(boolean, AUTOMATIC, STBM_APPL_VAR) startNewRateMeasurement)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  sint64 diffVirtualLocalTime;
  uint64 rateMeasurementOffset;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate offset between rate measurements */
  rateMeasurementOffset = StbM_GetRateCorrectionMeasurementDurationOfTimeBaseConfig(timeBaseId) / (uint64)StbM_GetRateCorrectionsPerMeasurementDurationOfTimeBaseConfig(timeBaseId);
# if (STBM_RATECORRECTIONFOROFFSETTIMEBASEOFTIMEBASECONFIG == STD_ON)
  if (StbM_IsOffsetTimeBase(timeBaseId))
  {
    retVal = StbM_TimestampMinusTimestampInNs(
      &StbM_GetVirtualLocalTimeStampOfTimeBaseState(StbM_GetTimeBaseConfigIdxOfTimeBaseConfig(timeBaseId)),
      &StbM_GetRateMeasurementStorage(rateMeasurementIdx).StartVirtualLocalTime, &diffVirtualLocalTime); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */
  }
  else
# endif
  {
    retVal = StbM_TimestampMinusTimestampInNs(
      &StbM_GetVirtualLocalTimeStampOfTimeBaseState(timeBaseId),
      &StbM_GetRateMeasurementStorage(rateMeasurementIdx).StartVirtualLocalTime, &diffVirtualLocalTime); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */
  }

  /* #20 Request start of new rate measurement if offset has passed */
  /* diffVirtualLocalTime can not jump and can not become negative. */
  if ((retVal == E_OK) && ((uint64)diffVirtualLocalTime >= rateMeasurementOffset))
  {
    *startNewRateMeasurement = TRUE; /* SBSW_STBM_ACCESS_PARAMPTR */
  }

  return retVal;
} /* StbM_CheckRateMeasurementOffset() */

/*!
* Internal comment removed.
 *
 *
*/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_DiscardRateMeasurements(StbM_SynchronizedTimeBaseType timeBaseId)
{
  /* ----- Local Variables ---------------------------------------------- */
  StbM_RateMeasurementStorageIterType rateMeasurementIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all rate measurements and mark them as discared */
  for (rateMeasurementIdx = StbM_GetRateMeasurementStorageStartIdxOfTimeBaseConfig(timeBaseId); rateMeasurementIdx < StbM_GetRateMeasurementStorageEndIdxOfTimeBaseConfig(timeBaseId); rateMeasurementIdx++)
  {
    StbM_GetRateMeasurementStorage(rateMeasurementIdx).Discard = TRUE; /* SBSW_STBM_ACCESS_RATEMEASUREMENTSTORAGE */
  }
} /* StbM_DiscardRateMeasurements() */

/**********************************************************************************************************************
 *  StbM_RateCorrectionMeasurement()
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
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_RateCorrectionMeasurement(StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  StbM_CurrentRateMeasurementIdxOfTimeBaseStateType lastRateMeasurement;
# if (STBM_RATECORRECTIONFOROFFSETTIMEBASEOFTIMEBASECONFIG == STD_ON)
  StbM_UserDataType synchronizedUserData;
  StbM_TimeStampType synchronizedTimeStamp = { 0, 0, 0, 0 };
  StbM_TimeStampType syncGlobalTimeStamp;
# endif
  boolean startNewRateMeasurement;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If Rate Correction Measurement is configured */
  if (StbM_GetRateCorrectionMeasurementDurationOfTimeBaseConfig(timeBaseId) > 0u) /* COV_STBM_RATECORRECTIONMEASUREMENTDURATION */
  {
    /* #20 Save time stamps of last synchronization */
# if (STBM_RATECORRECTIONFOROFFSETTIMEBASEOFTIMEBASECONFIG == STD_ON)
    if (StbM_IsOffsetTimeBase(timeBaseId))
    {
      retVal = StbM_CalculateCurrentTime(StbM_GetTimeBaseConfigIdxOfTimeBaseConfig(timeBaseId), &synchronizedTimeStamp, &synchronizedUserData); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */
      if (retVal == E_OK)
      {
        retVal = StbM_TimestampPlusTimestamp(timeStampPtr, &synchronizedTimeStamp, &syncGlobalTimeStamp); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */
        StbM_SetSyncGlobalTimeStampOfTimeBaseState(timeBaseId, syncGlobalTimeStamp); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
        StbM_SetSyncLocalTimeStampOfTimeBaseState(timeBaseId, synchronizedTimeStamp); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
      }
    }
    else
# endif
    {
      StbM_SetSyncGlobalTimeStampOfTimeBaseState(timeBaseId, *timeStampPtr); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
      StbM_SetSyncLocalTimeStampOfTimeBaseState(timeBaseId, StbM_GetTimeStampOfTimeBaseState(timeBaseId)); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
      StbM_SetSyncVirtualLocalTimeStampOfTimeBaseState(timeBaseId, StbM_GetVirtualLocalTimeStampOfTimeBaseState(timeBaseId)); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
    }

# if (STBM_RATECORRECTIONFOROFFSETTIMEBASEOFTIMEBASECONFIG == STD_ON)
    if (retVal == E_OK)
# endif
    {
      /* #30 Progress rate measurement index */
      lastRateMeasurement = StbM_GetCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId);
      if (StbM_GetCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId) >= (StbM_GetRateMeasurementStorageEndIdxOfTimeBaseConfig(timeBaseId) - 1u))
      {
        StbM_SetCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId, StbM_GetRateMeasurementStorageStartIdxOfTimeBaseConfig(timeBaseId)); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
      }
      else
      {
        StbM_IncCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
      }

      /* #40 Evaluate current rate measurement */
      retVal = StbM_EvaluateRateMeasurement(timeBaseId, timeStampPtr, &startNewRateMeasurement); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */

      /* #50 If new rate measurement was requested and no time leap was recognized */
      if (startNewRateMeasurement && (StbM_GetTimeLeapFutureBit(StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus) == 0u) && (StbM_GetTimeLeapPastBit(StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus) == 0u)) /* PRQA S 4558 */ /* MD_MSR_AutosarBoolean */
      {
        /* #60 Take sample of global and local time for new rate measurement */
        StbM_GetRateMeasurementStorage(StbM_GetCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId)).StartGlobalTime = *timeStampPtr; /* SBSW_STBM_ACCESS_RATEMEASUREMENTSTORAGE_RUNTIMEIDX */
        StbM_GetRateMeasurementStorage(StbM_GetCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId)).StartGlobalTime.timeBaseStatus = StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus; /* SBSW_STBM_ACCESS_RATEMEASUREMENTSTORAGE_RUNTIMEIDX */
# if (STBM_RATECORRECTIONFOROFFSETTIMEBASEOFTIMEBASECONFIG == STD_ON)
        if (StbM_IsOffsetTimeBase(timeBaseId))
        {
          StbM_GetRateMeasurementStorage(StbM_GetCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId)).StartLocalTime = synchronizedTimeStamp; /* SBSW_STBM_ACCESS_RATEMEASUREMENTSTORAGE_RUNTIMEIDX */
          StbM_GetRateMeasurementStorage(StbM_GetCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId)).StartVirtualLocalTime = StbM_GetVirtualLocalTimeStampOfTimeBaseState(StbM_GetTimeBaseConfigIdxOfTimeBaseConfig(timeBaseId)); /* SBSW_STBM_ACCESS_RATEMEASUREMENTSTORAGE_RUNTIMEIDX */
        }
        else
# endif
        {
          StbM_GetRateMeasurementStorage(StbM_GetCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId)).StartVirtualLocalTime = StbM_GetVirtualLocalTimeStampOfTimeBaseState(timeBaseId); /* SBSW_STBM_ACCESS_RATEMEASUREMENTSTORAGE_RUNTIMEIDX */
        }

        /* #70 Initialize Discard state of the new rate measurement with FALSE */
        StbM_GetRateMeasurementStorage(StbM_GetCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId)).Discard = FALSE; /* SBSW_STBM_ACCESS_RATEMEASUREMENTSTORAGE_RUNTIMEIDX */
      }
      /* #80 Otherwise reset rate measurement index */
      else
      {
        StbM_SetCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId, lastRateMeasurement); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
      }
    }
  }

  return retVal;
} /* StbM_RateCorrectionMeasurement() */

/**********************************************************************************************************************
 *  StbM_CalculateRateCorrection()
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
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalculateRateCorrection(StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  sint64 diffGlobalTime;
  sint64 diffLocalTime;

  /* ----- Implementation ----------------------------------------------- */
  retVal = StbM_TimestampMinusTimestampInNs(timeStampPtr, &StbM_GetRateMeasurementStorage(StbM_GetCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId)).StartGlobalTime, &diffGlobalTime); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */

  if (retVal == E_OK)
  {
    /* #10 If Time Base is a Offset Time */
# if (STBM_RATECORRECTIONFOROFFSETTIMEBASEOFTIMEBASECONFIG == STD_ON)
    if (StbM_IsOffsetTimeBase(timeBaseId))
    {
      StbM_TimeStampType synchronizedTimeStamp;
      StbM_UserDataType synchronizedUserData;

      /* #20 Calculate current local time of referred synchronized time base */
      retVal = StbM_CalculateCurrentTime(StbM_GetTimeBaseConfigIdxOfTimeBaseConfig(timeBaseId), &synchronizedTimeStamp, &synchronizedUserData); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */

      /* #30 If no error has occurred */
      if (retVal == E_OK)
      {
        /* #40 Set rate correction to 1 + (diffGlobalTime)/(current local time - local measurement start) */
        retVal =
          StbM_TimestampMinusTimestampInNs(&synchronizedTimeStamp, &StbM_GetRateMeasurementStorage(StbM_GetCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId)).StartLocalTime, &diffLocalTime); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */
        if (retVal == E_OK)
        {
          /* Check EV_RATECORRECTION.*/
          StbM_SetRateCorrectionOfTimeBaseState(timeBaseId, ((float64)diffLocalTime + (float64)diffGlobalTime) / (float64)diffLocalTime); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
          StbM_SetRateCorrectionSetOfTimeBaseState(timeBaseId, TRUE); /* SBSW_STBM_ACCESS_TIMEBASESTATE */

#  if (STBM_RATECORRECTIONSTATUSEVENTACTIVEOFTIMEBASECONFIG == STD_ON)
          /* Check EV_RATECORRECTION */
          /* #41 Check and set Ratecorrection notification event */
          StbM_CheckAndSetRatecorrectionEv(timeBaseId);
#  endif
        }
      }
    }
    /* #50 Otherwise set rate correction to (diffGlobalTime / elapsed time of local time base since last measurement update) */
    else
# endif
    {
      retVal =
        StbM_TimestampMinusTimestampInNs(&StbM_GetVirtualLocalTimeStampOfTimeBaseState(timeBaseId),
                                         &StbM_GetRateMeasurementStorage(StbM_GetCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId)).StartVirtualLocalTime, &diffLocalTime); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */
      if (retVal == E_OK)
      {
        StbM_SetRateCorrectionOfTimeBaseState(timeBaseId, (float64)diffGlobalTime / (float64)diffLocalTime); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
        StbM_SetRateCorrectionSetOfTimeBaseState(timeBaseId, TRUE); /* SBSW_STBM_ACCESS_TIMEBASESTATE */

# if (STBM_RATECORRECTIONSTATUSEVENTACTIVEOFTIMEBASECONFIG == STD_ON)
        /* Check EV_RATECORRECTION */
        /* #51 Check and set Ratecorrection notification event */
        StbM_CheckAndSetRatecorrectionEv(timeBaseId);
# endif
      }
    }
  }

  return retVal;
} /* StbM_CalculateRateCorrection() */
#endif

#if (STBM_TIMEBASECONFIGIDXOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CalculateCurrentOffsetTime()
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
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalculateCurrentOffsetTime(StbM_SynchronizedTimeBaseType timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_VAR) timeStampPtr,
  P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_VAR) userDataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  StbM_TimeStampType synchronizedTimeStamp;
  StbM_UserDataType synchronizedUserData;
# if ((STBM_RATECORRECTIONFOROFFSETTIMEBASEOFTIMEBASECONFIG == STD_ON) || (STBM_MASTERRATECORRECTIONFOROFFSETTIMEBASEOFTIMEBASECONFIG == STD_ON))
  sint64 diffLocalTime;
  sint64 correctedLocalTime;
# endif

  /* ----- Implementation ----------------------------------------------- */
  /* for offset time bases, calculate the time stamp by adding the offset to the current time of the referenced time domain */

  /* #10 Get current Timestamp of reference Time-Base */
  retVal = StbM_CalculateCurrentTime(StbM_GetTimeBaseConfigIdxOfTimeBaseConfig(timeBaseId), &synchronizedTimeStamp, &synchronizedUserData); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */

  /* #20 If timestamp is valid */
  if (retVal == E_OK)
  {
    /* #30 If offset has been set */
    if (StbM_GetGlobalTimeBaseBit(StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus) != 0u)
    {
# if ((STBM_RATECORRECTIONFOROFFSETTIMEBASEOFTIMEBASECONFIG == STD_ON) || (STBM_MASTERRATECORRECTIONFOROFFSETTIMEBASEOFTIMEBASECONFIG == STD_ON))
      /* #40 If rate correction is configured and rate correction value has been set */
      if (StbM_IsRateCorrectionSetOfTimeBaseState(timeBaseId))
      {
        retVal = StbM_TimestampMinusTimestampInNs(&synchronizedTimeStamp, &StbM_GetSyncLocalTimeStampOfTimeBaseState(timeBaseId), &diffLocalTime); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */
        if (retVal == E_OK)
        {
          correctedLocalTime = (sint64)((float64)diffLocalTime * StbM_GetRateCorrectionOfTimeBaseState(timeBaseId)); /* PRQA S 4395 */ /* MD_StbM_Rule10.8 */
          retVal = StbM_TimestampPlusTimediff(&StbM_GetSyncGlobalTimeStampOfTimeBaseState(timeBaseId), correctedLocalTime, timeStampPtr); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_PARAMPTR */
        }
      }
      /* #50 Otherwise calculate current offset time as sum synchronized timestamp + offset */
      else
# endif
      {
        retVal = StbM_TimestampPlusTimestamp(&synchronizedTimeStamp, &StbM_GetTimeStampOfTimeBaseState(timeBaseId), timeStampPtr); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_PARAMPTR */
      }

    }
    /* #60 Otherwise set current time of offset time base equal to time of referred synchronized time base */
    else
    {
      /* no offset value available */
      *timeStampPtr = synchronizedTimeStamp; /* SBSW_STBM_ACCESS_PARAMPTR */
    }

    /* #70 If no calculation error has occurred, set status of offset time base */
    if (retVal == E_OK)
    {
      timeStampPtr->timeBaseStatus = StbM_CalculateCombinedOffsetStatus(StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus, synchronizedTimeStamp.timeBaseStatus); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR_PARAMPTR */
      /* It should be not required to check notification customers as the internal timeBaseStatus is not changed. Only the getCurrentTime Status is affected. */
    }
  }

  /* #80 Get corresponding user data */
  *userDataPtr = StbM_GetUserDataOfTimeBaseState(timeBaseId); /* SBSW_STBM_ACCESS_PARAMPTR */

  return retVal;
} /* StbM_CalculateCurrentOffsetTime() */

/**********************************************************************************************************************
 *  StbM_CalculateCombinedOffsetStatus()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(StbM_TimeBaseStatusType, STBM_CODE) StbM_CalculateCombinedOffsetStatus(
  StbM_TimeBaseStatusType offsetStatus, StbM_TimeBaseStatusType syncStatus)
{
  StbM_TimeBaseStatusType combinedStatus;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate status bits except global time base bit */
  combinedStatus = ((offsetStatus | syncStatus) & ~StbM_Global_Time_Base_BflMask);
  /* #20 Calculate global time base bit */
  combinedStatus = (combinedStatus | (offsetStatus & syncStatus & StbM_Global_Time_Base_BflMask));
  return combinedStatus;
} /* StbM_CalculateCombinedOffsetStatus() */
#endif

#if (STBM_TRIGGEREDCUSTOMERCONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_TriggerCustomers()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_TriggerCustomers(void)
{

  /* ----- Local Variables ---------------------------------------------- */
  StbM_TriggeredCustomerStateIterType customerId;

  /* ----- Implementation ----------------------------------------------- */
  /* trigger customers */
  for (customerId = 0u; customerId < StbM_GetSizeOfTriggeredCustomerConfig(); customerId++)
  {
    /* #10 Increment trigger customer counter */
    StbM_IncrementCustomerCounter(customerId);

    /* #20 Check if customer is triggerable */
    if (StbM_IsCustomerTriggerable(customerId) == TRUE)
    {
      uint64 timestampInUs;
      TickType osTicks;
      StbM_TimeStampType timeStamp;
      timeStamp = StbM_GetTimeStampOfTimeBaseState(StbM_GetTimeBaseIDOfTriggeredCustomerConfig(customerId));
      
      /* #30 Convert current timestamp to ticks and synchronize the schedule table */
      timestampInUs = (uint64) timeStamp.secondsHi << 32u;
      timestampInUs += timeStamp.seconds;
      timestampInUs *= STBM_MICROSECOND_IN_ONE_SECOND;
      timestampInUs += ((uint64) timeStamp.nanoseconds / STBM_NANOSECONDS_IN_ONE_MICROSECOND);

      osTicks = (TickType)((timestampInUs * StbM_GetScheduleTableCounterTicksPerUsOfTriggeredCustomerConfig(customerId)) % StbM_GetScheduleTableDurationOfTriggeredCustomerConfig(customerId));

      (void)SyncScheduleTable(StbM_GetScheduleTableIDOfTriggeredCustomerConfig(customerId), osTicks);
    }
  }
} /* StbM_TriggerCustomers() */

/**********************************************************************************************************************
 *  StbM_IsCustomerTriggerable()
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
STBM_LOCAL_INLINE FUNC(boolean, STBM_CODE) StbM_IsCustomerTriggerable(StbM_TriggeredCustomerStateIterType customerId)
{
  boolean triggeredCustomerIsTriggerable = FALSE;
  StbM_TimeBaseStatusType timeBaseStatus = StbM_GetTimeStampOfTimeBaseState(StbM_GetTimeBaseIDOfTriggeredCustomerConfig(customerId)).timeBaseStatus;

  if (
       /* #10 Check if triggered customer period counter is zero */
          (StbM_GetTriggeredCustomerState(customerId).Counter == StbM_GetTriggeredCustomerPeriodOfTriggeredCustomerConfig(customerId))
       /* #20 Check if time base has been synchronized to global time */
       && (StbM_GetGlobalTimeBaseBit(timeBaseStatus) != 0u)
# if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
       /* #30 Check if timeout has not occurred */
       && (StbM_GetTimeoutBit(timeBaseStatus) == 0u)
       /* #40 Check if no time leap has occurred */
       && (StbM_GetTimeLeapFutureBit(timeBaseStatus) == 0u) && (StbM_GetTimeLeapPastBit(timeBaseStatus) == 0u)
# endif
    )
  {
    /* #50 Check if table status is RUNNING || WAITING || RUNNING_AND_SYNCHRONOUS */
    ScheduleTableStatusType scheduleStatus;
    StatusType currentScheduleTableStatus = GetScheduleTableStatus(StbM_GetScheduleTableIDOfTriggeredCustomerConfig(customerId), &scheduleStatus); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */
    if ((currentScheduleTableStatus == E_OK) 
        && ((scheduleStatus == SCHEDULETABLE_WAITING) || (scheduleStatus == SCHEDULETABLE_RUNNING) || (scheduleStatus == SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS)))
      {
        triggeredCustomerIsTriggerable = TRUE;
      }
  } 
  return triggeredCustomerIsTriggerable;
} /* StbM_IsCustomerTriggerable */
#endif

#if (STBM_STATUSNOTIFICATIONCUSTOMERCONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_ResetStatusEvent()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_ResetStatusEvent(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  StbM_StatusNotificationCustomerConfigIterType notificationCustomerIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize status event variables with zero */
  for (notificationCustomerIdx = 0u; notificationCustomerIdx < StbM_GetSizeOfStatusNotificationCustomerConfig(); notificationCustomerIdx++)
  {
    /*! Status event variable of status notification Time bases */
    StbM_SetStatusNotificationEvent(notificationCustomerIdx, 0u); /* SBSW_STBM_ACCESS_STATUSNOTIFICATIONEVENT */
  }
} /* StbM_ResetStatusEvent() */

/**********************************************************************************************************************
 *  StbM_CheckAndSetGlobalTimeBaseEv()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndSetGlobalTimeBaseEv(
  StbM_SynchronizedTimeBaseType timeBaseId,
  StbM_StatusNotificationCustomerConfigIterType customerIdx,
  StbM_StatusNotificationMaskOfStatusNotificationCustomerConfigType customerMask)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check and set sync to Global TimeBase notification event */
  if (StbM_IsStatusEvGlobalTimeBaseSet(customerMask))
  {
    if ((StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus & StbM_Global_Time_Base_BflMask) == 0u)
    {
      StbM_SetStatusEvGlobalTimeBase(StbM_GetStatusNotificationEvent(customerIdx)); /* SBSW_STBM_ACCESS_STATUSNOTIFICATIONEVENT */
    }
  }
} /* StbM_CheckAndSetGlobalTimeBaseEv() */

# if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckAndSetTimeoutNotificationEv()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndSetTimeoutNotificationEv(
  StbM_StatusNotificationCustomerConfigIterType customerIdx, 
  StbM_StatusNotificationMaskOfStatusNotificationCustomerConfigType customerMask)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 If Timeout Ev is subscribed by notification customer */
  if (StbM_IsStatusEvTimeoutOccurredSet(customerMask))
  {
    /* #20 Set timeout Notification Ev */
    StbM_SetStatusEvTimeoutOccurred(StbM_GetStatusNotificationEvent(customerIdx)); /* SBSW_STBM_ACCESS_STATUSNOTIFICATIONEVENT */
  }
} /* StbM_CheckAndSetTimeoutNotificationEv() */
# endif

# if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckAndSetTimeoutRemovedNotificationEv()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndSetTimeoutRemovedNotificationEv(
  StbM_SynchronizedTimeBaseType timeBaseId,
  StbM_StatusNotificationCustomerConfigIterType customerIdx,
  StbM_StatusNotificationMaskOfStatusNotificationCustomerConfigType customerMask)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 If Timeout Removed Ev is subscribed by notification customer */
  if (StbM_IsStatusEvTimeoutRemovedSet(customerMask))
  {
    /* #20 Set timeout removed Notification Ev if timeout was detected before */
    if ((StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus & StbM_Timeout_BflMask) != 0u)
    {
      StbM_SetStatusEvTimeoutRemoved(StbM_GetStatusNotificationEvent(customerIdx)); /* SBSW_STBM_ACCESS_STATUSNOTIFICATIONEVENT */
    }
  }
} /* StbM_CheckAndSetTimeoutRemovedNotificationEv() */
# endif

# if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckAndSetTimeleapFutureNotificationEv()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndSetTimeleapFutureNotificationEv(StbM_SynchronizedTimeBaseType timeBaseId)
{
  /* ----- Local Variables ---------------------------------------------- */
  StbM_StatusNotificationCustomerConfigIterType customerIdx = StbM_GetStatusNotificationCustomerConfigIdxOfTimeBaseConfig(timeBaseId);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If notification customer is configured */
  if (StbM_IsStatusNotificationCustomerConfigUsedOfTimeBaseConfig(timeBaseId)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    StbM_StatusNotificationMaskOfStatusNotificationCustomerConfigType customerMask = StbM_GetStatusNotificationMaskOfStatusNotificationCustomerConfig(customerIdx);
    /* #20 If Timeleap Future Ev is subscribed by notification customer */
    if (StbM_IsStatusEvTimeleapFutureSet(customerMask))
    {
      /* #30 Set Timeleap Future Notification Ev if time leap was not detected before */
      if ((StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus & StbM_TimeLeapFuture_BflMask) == 0u)
      {
        StbM_SetStatusEvTimeleapFuture(StbM_GetStatusNotificationEvent(customerIdx)); /* SBSW_STBM_ACCESS_STATUSNOTIFICATIONEVENT */
      }
    }
  }
} /* StbM_CheckAndSetTimeleapFutureNotificationEv() */
# endif

# if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckAndSetTimeleapFutureRemovedNotificationEv()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndSetTimeleapFutureRemovedNotificationEv(StbM_SynchronizedTimeBaseType timeBaseId)
{
  /* ----- Local Variables ---------------------------------------------- */
  StbM_StatusNotificationCustomerConfigIterType customerIdx = StbM_GetStatusNotificationCustomerConfigIdxOfTimeBaseConfig(timeBaseId);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If notification customer is configured */
  if (StbM_IsStatusNotificationCustomerConfigUsedOfTimeBaseConfig(timeBaseId)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    StbM_StatusNotificationMaskOfStatusNotificationCustomerConfigType customerMask = StbM_GetStatusNotificationMaskOfStatusNotificationCustomerConfig(customerIdx);
    /* #20 If Timeleap Future Removed Ev is subscribed by notification customer */
    if (StbM_IsStatusEvTimeleapFutureRemovedSet(customerMask))
    {
      /* #30 Set Timeleap Future Removed Notification Ev */
      StbM_SetStatusEvTimeleapFutureRemoved(StbM_GetStatusNotificationEvent(customerIdx)); /* SBSW_STBM_ACCESS_STATUSNOTIFICATIONEVENT */
    }
  }
} /* StbM_CheckAndSetTimeleapFutureRemovedNotificationEv() */
# endif

# if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckAndSetTimeleapPastNotificationEv()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndSetTimeleapPastNotificationEv(StbM_SynchronizedTimeBaseType timeBaseId)
{
  /* ----- Local Variables ---------------------------------------------- */
  StbM_StatusNotificationCustomerConfigIterType customerIdx = StbM_GetStatusNotificationCustomerConfigIdxOfTimeBaseConfig(timeBaseId);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If notification customer is configured */
  if (StbM_IsStatusNotificationCustomerConfigUsedOfTimeBaseConfig(timeBaseId)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    StbM_StatusNotificationMaskOfStatusNotificationCustomerConfigType customerMask = StbM_GetStatusNotificationMaskOfStatusNotificationCustomerConfig(customerIdx);
    /* #20 If Timeleap Past Ev is subscribed by notification customer */
    if (StbM_IsStatusEvTimeleapPastSet(customerMask))
    {
      /* #30 Set Timeleap Past Notification Ev if time leap was not detected before */
      if ((StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus & StbM_TimeLeapPast_BflMask) == 0u)
      {
        StbM_SetStatusEvTimeleapPast(StbM_GetStatusNotificationEvent(customerIdx)); /* SBSW_STBM_ACCESS_STATUSNOTIFICATIONEVENT */
      }
    }
  }
} /* StbM_CheckAndSetTimeleapPastNotificationEv() */
# endif

# if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckAndSetTimeleapPastRemovedNotificationEv()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndSetTimeleapPastRemovedNotificationEv(StbM_SynchronizedTimeBaseType timeBaseId)
{
  /* ----- Local Variables ---------------------------------------------- */
  StbM_StatusNotificationCustomerConfigIterType customerIdx = StbM_GetStatusNotificationCustomerConfigIdxOfTimeBaseConfig(timeBaseId);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If notification customer is configured */
  if (StbM_IsStatusNotificationCustomerConfigUsedOfTimeBaseConfig(timeBaseId)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    StbM_StatusNotificationMaskOfStatusNotificationCustomerConfigType customerMask = StbM_GetStatusNotificationMaskOfStatusNotificationCustomerConfig(customerIdx);
    /* #20 If Timeleap Past Removed Ev is subscribed by notification customer */
    if (StbM_IsStatusEvTimeleapPastRemovedSet(customerMask))
    {
      /* #30 Set Timeleap Past Removed Notification Ev */
      StbM_SetStatusEvTimeleapPastRemoved(StbM_GetStatusNotificationEvent(customerIdx)); /* SBSW_STBM_ACCESS_STATUSNOTIFICATIONEVENT */
    }
  }
} /* StbM_CheckAndSetTimeleapPastRemovedNotificationEv() */
# endif

# if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckAndSetSyncToSubdomainEv()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndSetSyncToSubdomainEv(
  StbM_SynchronizedTimeBaseType timeBaseId,
  StbM_StatusNotificationCustomerConfigIterType customerIdx,
  StbM_StatusNotificationMaskOfStatusNotificationCustomerConfigType customerMask,
  boolean isUpdateFromBus)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check and set sync to subdomain notification event */
  if (StbM_IsStatusEvSyncToSubdomainSet(customerMask))
  {
    if (
#  if (STBM_TIMEGATEWAYOFTIMEBASECONFIG == STD_ON)
      (StbM_IsTimeGatewayOfTimeBaseConfig(timeBaseId)) ||
#  endif
      (isUpdateFromBus == TRUE)) /* COV_STBM_TIMEGATEWAY */
    {
      if ((StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus & StbM_Sync_To_Gateway_BflMask) == 0u)
      {
        StbM_SetStatusEvSyncToSubdomain(StbM_GetStatusNotificationEvent(customerIdx)); /* SBSW_STBM_ACCESS_STATUSNOTIFICATIONEVENT */
      }
    }
  }
} /* StbM_CheckAndSetSyncToSubdomainEv() */
# endif

# if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckAndSetSyncToGlobalMasterEv()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndSetSyncToGlobalMasterEv(
StbM_SynchronizedTimeBaseType timeBaseId,
StbM_StatusNotificationCustomerConfigIterType customerIdx,
StbM_StatusNotificationMaskOfStatusNotificationCustomerConfigType customerMask)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check and set SyncToGlobalMaster event */
  if (StbM_IsStatusEvSyncToGlobalMasterSet(customerMask))
  {
    if ((StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus & StbM_Sync_To_Gateway_BflMask) != 0u)
    {
      StbM_SetStatusEvSyncToGlobalMaster(StbM_GetStatusNotificationEvent(customerIdx)); /* SBSW_STBM_ACCESS_STATUSNOTIFICATIONEVENT */
    }
  }
} /* StbM_CheckAndSetSyncToGlobalMasterEv() */
# endif

/**********************************************************************************************************************
 *  StbM_CheckAndSetResyncEv()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndSetResyncEv(
  StbM_StatusNotificationCustomerConfigIterType customerIdx,
  StbM_StatusNotificationMaskOfStatusNotificationCustomerConfigType customerMask)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check and set ReSync event */
  if (StbM_IsStatusEvResyncSet(customerMask))
  {
    StbM_SetStatusEvResync(StbM_GetStatusNotificationEvent(customerIdx)); /* SBSW_STBM_ACCESS_STATUSNOTIFICATIONEVENT */
  }
} /* StbM_CheckAndSetResyncEv() */

# if (STBM_RATECORRECTIONSTATUSEVENTACTIVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckAndSetRatecorrectionEv()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndSetRatecorrectionEv(StbM_SynchronizedTimeBaseType timeBaseId)
{
  /* ----- Local Variables ---------------------------------------------- */
  StbM_StatusNotificationCustomerConfigIterType customerIdx = StbM_GetStatusNotificationCustomerConfigIdxOfTimeBaseConfig(timeBaseId);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If notification customer is configured */
  if (StbM_IsStatusNotificationCustomerConfigUsedOfTimeBaseConfig(timeBaseId)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    StbM_StatusNotificationMaskOfStatusNotificationCustomerConfigType customerMask = StbM_GetStatusNotificationMaskOfStatusNotificationCustomerConfig(customerIdx);
    /* #20 If Ratecorrection Ev is subscribed by notification customer */
    if (StbM_IsStatusEvRatecorrectionSet(customerMask))
    {
      /* #30 Set Ratecorrection event */
      StbM_SetStatusEvRatecorrection(StbM_GetStatusNotificationEvent(customerIdx)); /* SBSW_STBM_ACCESS_STATUSNOTIFICATIONEVENT */
    }
  }
} /* StbM_CheckAndSetRatecorrectionEv() */
# endif

/**********************************************************************************************************************
 *  StbM_CallStatusNotificationCallbackAndClearEvent()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CallStatusNotificationCallbackAndClearEvent(StbM_StatusNotificationCustomerConfigIterType customerIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  StbM_TimeBaseNotificationType event;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If notification event was registered */
  if (StbM_GetStatusNotificationEvent(customerIdx) != 0u)
  {
    StbMStatusNotificationType StatusNotificationPtr = StbM_GetStatusNotificationOfStatusNotificationCustomerConfig(customerIdx);
    /* #20 Clear notification event and call status notification callback */
    SchM_Enter_StbM_STBM_EXCLUSIVE_AREA_0();
    event =  StbM_GetStatusNotificationEvent(customerIdx);
    StbM_SetStatusNotificationEvent(customerIdx, 0); /* SBSW_STBM_ACCESS_STATUSNOTIFICATIONEVENT */
    SchM_Exit_StbM_STBM_EXCLUSIVE_AREA_0();

    if (StatusNotificationPtr != NULL_PTR) /* COV_STBM_SILENT_TX */
    {
      (void) StatusNotificationPtr(event); /* SBSW_STBM_FCTPTRCALL_NOTIFICATION */
    }
  }
} /* StbM_CallStatusNotificationCallbackAndClearEvent() */

# if (STBM_GLOBALTIMEMASTEROFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_SetGlobalTime_SetStatusEvents()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_SetGlobalTime_SetStatusEvents(StbM_SynchronizedTimeBaseType timeBaseId)
{
  /* ----- Local Variables ---------------------------------------------- */
  StbM_StatusNotificationCustomerConfigIterType customerIdx = StbM_GetStatusNotificationCustomerConfigIdxOfTimeBaseConfig(timeBaseId);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If notification customer is configured */
  if (StbM_IsStatusNotificationCustomerConfigUsedOfTimeBaseConfig(timeBaseId)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    /* Check EV_GLOBAL_TIME_BASE, EV_TIMEOUT_REMOVED, EV_SYNC_TO_GLOBAL_MASTER, EV_RESYNC */
    StbM_StatusNotificationMaskOfStatusNotificationCustomerConfigType customerMask = StbM_GetStatusNotificationMaskOfStatusNotificationCustomerConfig(customerIdx);

    /* #20 Check and set sync to Global TimeBase notification event */
    StbM_CheckAndSetGlobalTimeBaseEv(timeBaseId, customerIdx, customerMask);

    /* #30 Check and set ReSync event */
    StbM_CheckAndSetResyncEv(customerIdx, customerMask);
  }
} /* StbM_SetGlobalTime_SetStatusEvents() */
# endif
#endif

#if (STBM_TIMENOTIFICATIONCUSTOMERCONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_GetNextExpirationPoint()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 ******************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(sint32, STBM_CODE) StbM_GetNextExpirationPoint(boolean isCallContextTimerCbk)
{
  /* ----- Local Variables ---------------------------------------------- */
  StbM_SynchronizedTimeBaseType timeBaseId = 0;
  sint32 nextExpirationPoint = STBM_INVALID_EXPIRATION_POINT;

  /* ----- Implementation ----------------------------------------------- */
  for (; timeBaseId < StbM_GetSizeOfTimeBaseConfig(); timeBaseId++)
  {
    if (StbM_IsTimeNotificationCustomerConfigIndUsedOfTimeBaseConfig(timeBaseId)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */ /* COV_STBM_ALL_TIMEBASES_WITH_TIMENOTIFICATIONCUSTOMER */
    {
      /* #10 Calculate and get the next expiration point */
      nextExpirationPoint = StbM_CalculateNextExpirationPoint(timeBaseId, nextExpirationPoint, isCallContextTimerCbk);
    }
  }

  return nextExpirationPoint;
} /* StbM_GetNextExpirationPoint() */

/**********************************************************************************************************************
 *  StbM_CalculateNextExpirationPoint()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 ******************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(sint32, STBM_CODE) StbM_CalculateNextExpirationPoint(StbM_SynchronizedTimeBaseType timeBaseId,
  sint32 nextExpirationPoint, boolean isCallContextTimerCbk)
{
  /* ----- Local Variables ---------------------------------------------- */
  StbM_TimeStampType timeStamp;
  StbM_UserDataType userData;
  sint32 possibleExpirationPoint = nextExpirationPoint;

  /* ----- Implementation ----------------------------------------------- */
  StbM_TimeNotificationCustomerConfigIndIterType timeCustomerStartInd = StbM_GetTimeNotificationCustomerConfigIndStartIdxOfTimeBaseConfig(timeBaseId);
  /* #10 Get current time of timebase */
  Std_ReturnType timeStampValid = StbM_CalcTimeAndGetUserData(timeBaseId, &timeStamp, &userData); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */

  for (; timeCustomerStartInd < StbM_GetTimeNotificationCustomerConfigIndEndIdxOfTimeBaseConfig(timeBaseId); timeCustomerStartInd++)
  {
    StbM_TimeNotificationCustomerConfigIterType customerId = StbM_GetTimeNotificationCustomerConfigInd(timeCustomerStartInd);
    /* #20 If time is valid */
    if (timeStampValid == E_OK)
    {
      /* #30 Get remaining time of time notification customer */
      sint32 expirationPoint = StbM_GetExpirationPointOfCustomer(isCallContextTimerCbk, customerId, &timeStamp); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */

      /* #40 If current remaining time is the minimum of all remaining times, set as next expiration point */
      if (expirationPoint < possibleExpirationPoint)
      {
        possibleExpirationPoint = expirationPoint;
      }
    }
    /* #50 Otherwise stop timer of belonging customer */
    else
    {
      StbM_GetNotificationCustomerStates(customerId).timerState = STBM_TIMER_STOPPED; /* SBSW_STBM_ACCESS_NOTIFICATIONCUSTOMERSTATE */
    }
  }

  return possibleExpirationPoint;
} /* StbM_CalculateNextExpirationPoint() */

/**********************************************************************************************************************
 *  StbM_GetExpirationPointOfCustomer()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STBM_LOCAL_INLINE FUNC(sint32, STBM_CODE) StbM_GetExpirationPointOfCustomer(boolean isCallContextTimerCbk,  StbM_TimeNotificationCustomerConfigIterType customerId,  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStamp)
{
  /* ----- Local Variables ---------------------------------------------- */
  StbM_TimeDiffType expirationPoint = STBM_INVALID_EXPIRATION_POINT;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If timer of customer is running */
  if (StbM_GetNotificationCustomerStates(customerId).timerState == STBM_TIMER_RUNNING)
  {
    Std_ReturnType retVal;
    sint64 expirationPoint_temp;

    retVal = StbM_TimestampMinusTimestampInNs(&(StbM_GetNotificationCustomerStates(customerId).expireTime), timeStamp, &expirationPoint_temp); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */

    if ((retVal == E_OK) && (expirationPoint_temp > (-2 * (sint64)STBM_NANOSECONDS_IN_ONE_SECOND)) && (expirationPoint_temp < (2 * (sint64)STBM_NANOSECONDS_IN_ONE_SECOND)))
    /* If timeUntilTimeout > 2s --> Can't be in GPT Threshold --> skip */
    {
      expirationPoint = StbM_CheckTimerForCalculatingExpirationPoint(isCallContextTimerCbk, customerId, expirationPoint_temp);
    }
  }
  return expirationPoint;
} /* StbM_GetExpirationPointOfCustomer() */

/**********************************************************************************************************************
 *  StbM_CheckTimerForCalculatingExpirationPoint()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(sint32, STBM_CODE) StbM_CheckTimerForCalculatingExpirationPoint(
  boolean isCallContextTimerCbk,
  StbM_TimeNotificationCustomerConfigIterType customerId,
  sint64 expirationPoint)
{
  /* ----- Implementation ----------------------------------------------- */
  StbM_TimeDiffType retValExpirationPoint = (StbM_TimeDiffType)expirationPoint;
  StbM_GetNotificationCustomerStates(customerId).gptExpirationPoint = retValExpirationPoint; /* SBSW_STBM_ACCESS_NOTIFICATIONCUSTOMERSTATE */

  /* #10 If time has not already exceeded expire time */
  if (retValExpirationPoint > 0)
  {
    /* #20 Check if remaining time till timeout is within configured threshold */
    if (retValExpirationPoint <= StbM_GetTimerStartThresholdOfTimeNotificationCustomerConfig(customerId))
    {
# if (StbM_GetSizeOfTimeNotificationCustomerConfig() > 1u)
      if ((StbM_GptTimerState == STBM_GPT_TIMER_STOPPED) || isCallContextTimerCbk) /* PRQA S 4558 */ /* MD_MSR_AutosarBoolean */
# endif
      {
        /* #30 Set GPT timer state to REQUIRED */
        StbM_GptTimerState = STBM_GPT_TIMER_START_REQUIRED;
      }
    }
  }
  else
  {
    /* #40 Set State of notification customer to CALL_CBK */
    StbM_GetNotificationCustomerStates(customerId).timerState = STBM_TIMER_CALL_CBK; /* SBSW_STBM_ACCESS_NOTIFICATIONCUSTOMERSTATE */
    retValExpirationPoint = STBM_INVALID_EXPIRATION_POINT;
  }

# if (StbM_GetSizeOfTimeNotificationCustomerConfig() == 1u)
  STBM_DUMMY_STATEMENT(isCallContextTimerCbk); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# endif

  return retValExpirationPoint;
} /* StbM_CheckTimerForCalculatingExpirationPoint() */

/**********************************************************************************************************************
 *  StbM_StartGptTimer()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 ********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_StartGptTimer(sint32 expirationPoint)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 If GPT Timer is required */
  if (StbM_GptTimerState == STBM_GPT_TIMER_START_REQUIRED)
  {
    StbM_TimeNotificationCustomerConfigIterType timeCustomerIdx = 0;
    /* #20 Set status of time notification customer to "Callback Expected" if timer will elapse with next expiration point */
    for (; timeCustomerIdx < StbM_GetSizeOfTimeNotificationCustomerConfig(); timeCustomerIdx++)
    {
# if (StbM_GetSizeOfTimeNotificationCustomerConfig() > 1u)
      if ((StbM_GetNotificationCustomerStates(timeCustomerIdx).timerState == STBM_TIMER_RUNNING) && (StbM_GetNotificationCustomerStates(timeCustomerIdx).gptExpirationPoint == expirationPoint))
# endif
      {
        StbM_GetNotificationCustomerStates(timeCustomerIdx).timerState = STBM_TIMER_CBK_EXPECTED; /* SBSW_STBM_ACCESS_NOTIFICATIONCUSTOMERSTATE */
      }
    }

    /* #30 Set GPT Timer State to "RUNNING" */
    StbM_GptTimerState = STBM_GPT_TIMER_RUNNING;

    /* #40 Start GPT Timer */
    Gpt_StartTimer(STBM_TIME_NOTIFICATION_GPT_CHANNEL, ((uint32) expirationPoint) / STBM_NS_TICKS_GPT_NOTIFICATION_TIMER);
  }
} /* StbM_StartGptTimer() */

/**********************************************************************************************************************
 *  StbM_UpdateExpireTime()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 ********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_UpdateExpireTime(StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType currentTimeIsValid = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If Time Notification Customers are configured */
  if (StbM_IsTimeNotificationCustomerConfigIndUsedOfTimeBaseConfig(timeBaseId)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */ /* COV_STBM_ALL_TIMEBASES_WITH_TIMENOTIFICATIONCUSTOMER */
  {
    StbM_TimeNotificationCustomerConfigIndIterType timeCustomerStartInd = StbM_GetTimeNotificationCustomerConfigIndStartIdxOfTimeBaseConfig(timeBaseId);
    StbM_TimeStampType currentTime;
    StbM_UserDataType userDataTemp;

    /* #20 Calculate current time of time base */
    currentTimeIsValid = StbM_CalcTimeAndGetUserData(timeBaseId, &currentTime, &userDataTemp); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */

    /* #25 If TimeValue is valid */
    if (currentTimeIsValid == E_OK) /* COV_STBM_ALL_TIMENOTIFICATIONCUSTOMER_MASTERSYNCTIMEBASE */
    {
      for (; timeCustomerStartInd < StbM_GetTimeNotificationCustomerConfigIndEndIdxOfTimeBaseConfig(timeBaseId); timeCustomerStartInd++)
      {
        currentTimeIsValid |= StbM_CheckTimerAndCalculate(timeCustomerStartInd, timeBaseId, timeStampPtr, &currentTime); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */
      }
    }
    /* #30 Else stop all corresponding timer */
    else
    {
      for (; timeCustomerStartInd < StbM_GetTimeNotificationCustomerConfigIndEndIdxOfTimeBaseConfig(timeBaseId); timeCustomerStartInd++) /* COV_STBM_ALL_TIMENOTIFICATIONCUSTOMER_MASTERSYNCTIMEBASE */
      {
        StbM_TimeNotificationCustomerConfigIterType timeCustomerId = StbM_GetTimeNotificationCustomerConfigInd(timeCustomerStartInd);
        StbM_GetNotificationCustomerStates(timeCustomerId).timerState = STBM_TIMER_STOPPED; /* SBSW_STBM_ACCESS_NOTIFICATIONCUSTOMERSTATE */
      }
    }
  }

  return currentTimeIsValid;
} /* StbM_UpdateExpireTime() */

/**********************************************************************************************************************
 *  StbM_CheckTimerAndCalculate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 ********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CheckTimerAndCalculate(
  StbM_TimeNotificationCustomerConfigIndIterType timeCustomerStartInd,
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) currentTime)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retValPerCustomer = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  StbM_NotificationCustomerStatesIterType timeCustomerId = StbM_GetTimeNotificationCustomerConfigInd(timeCustomerStartInd);
  /* #10 If timer is not stopped, update expire time to expireTime = (expireTime - currentTime) + new TimeValue */
  if (StbM_GetNotificationCustomerStates(timeCustomerId).timerState != STBM_TIMER_STOPPED)
  {
    StbM_TimeStampType remainingTime;
    StbM_TimeStampType newTimeStamp;

    retValPerCustomer = StbM_TimestampMinusTimestamp(&(StbM_GetNotificationCustomerStates(timeCustomerId).expireTime), currentTime, &remainingTime); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */

# if (STBM_TIMENOTIFICATIONCUSTOMERCONFIGOFFSETINDUSEDOFTIMEBASECONFIG == STD_ON)
    if (StbM_IsOffsetTimeBase(timeBaseId))
    {
      StbM_TimeStampType timeWithoutOffset;
      /* remove old offset */
      retValPerCustomer |= StbM_TimestampMinusTimestamp(currentTime, &(StbM_GetTimeStampOfTimeBaseState(timeBaseId)), &timeWithoutOffset); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */

      /* add new offset */
      retValPerCustomer |= StbM_TimestampPlusTimestamp(&timeWithoutOffset, timeStampPtr, &newTimeStamp); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */

    }
    else
# endif
    {
      newTimeStamp = *timeStampPtr;
    }

    retValPerCustomer |= StbM_TimestampPlusTimestamp(&remainingTime, &newTimeStamp, &(StbM_GetNotificationCustomerStates(timeCustomerId).expireTime)); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_GLOBALPTR */

    if (retValPerCustomer == E_NOT_OK)
    {
      /* #20 If any error occurred, stop specific timer */
      StbM_GetNotificationCustomerStates(timeCustomerId).timerState = STBM_TIMER_STOPPED; /* SBSW_STBM_ACCESS_NOTIFICATIONCUSTOMERSTATE */
    }
  }

# if (STBM_TIMENOTIFICATIONCUSTOMERCONFIGOFFSETINDUSEDOFTIMEBASECONFIG == STD_OFF)
  STBM_DUMMY_STATEMENT(timeBaseId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# endif

  return retValPerCustomer;
} /* StbM_CheckTimerAndCalculate() */

/**********************************************************************************************************************
 *  StbM_StopTimeNotificationCustomers()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 ********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_StopTimeNotificationCustomers(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  StbM_TimeNotificationCustomerConfigIterType timeNotificationCustomer = 0;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set GPT Timer State to STOPPED */
  StbM_GptTimerState = STBM_GPT_TIMER_STOPPED;

  /* #20 Stop all time notification customers */
  for (; timeNotificationCustomer < StbM_GetSizeOfTimeNotificationCustomerConfig(); timeNotificationCustomer++)
  {
    StbM_GetNotificationCustomerStates(timeNotificationCustomer).timerState = STBM_TIMER_STOPPED; /* SBSW_STBM_ACCESS_NOTIFICATIONCUSTOMERSTATE */
  }
} /* StbM_StopTimeNotificationCustomers() */

/**********************************************************************************************************************
 *  StbM_IsExpireTimeValid()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *******************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(boolean, STBM_CODE) StbM_IsExpireTimeValid(P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) expireTime)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean retVal = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if expireTime is larger than one main function cycle and larger than the greatest GPT threshold if GPT Timer is not in idle state */
  if (
      (expireTime->secondsHi > 0u) ||
      (expireTime->seconds > STBM_MAINFUNCTION_CYCLETIME_S) ||
      (
# if (STBM_MAINFUNCTION_CYCLETIME_S > 0)
       (expireTime->seconds == STBM_MAINFUNCTION_CYCLETIME_S) &&
# endif
       (expireTime->nanoseconds > STBM_MAINFUNCTION_CYCLETIME_NS)
      )
    )
  {
# if (StbM_GetSizeOfTimeNotificationCustomerConfig() > 1u)
    if ((StbM_GptTimerState == STBM_GPT_TIMER_STOPPED)
        ||  (
            (expireTime->secondsHi > 0u) ||
            (expireTime->seconds > STBM_MAX_GPT_THRESHOLD_S) ||
            ((expireTime->seconds == STBM_MAX_GPT_THRESHOLD_S) && (expireTime->nanoseconds > STBM_MAX_GPT_THRESHOLD_NS))))
# endif
    {
      retVal = TRUE;
    }
  }

  return retVal;
} /* StbM_IsExpireTimeValid() */
#endif

#if (STBM_OFFSET_TIME_NOTIFICATION_CUSTOMER == STD_ON)
/**********************************************************************************************************************
 *  StbM_CalcElapsedTimeOfOffsetTimeBase()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalcElapsedTimeOfOffsetTimeBase(StbM_SynchronizedTimeBaseType timeBaseId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If timeBase is referred by an offset time base having time notification customers */
  if (StbM_IsTimeNotificationCustomerConfigOffsetIndUsedOfTimeBaseConfig(timeBaseId)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    StbM_TimeNotificationCustomerConfigOffsetIndIterType offsetTimeCustomerStartInd = StbM_GetTimeNotificationCustomerConfigOffsetIndStartIdxOfTimeBaseConfig(timeBaseId);

    for (; offsetTimeCustomerStartInd < StbM_GetTimeNotificationCustomerConfigOffsetIndEndIdxOfTimeBaseConfig(timeBaseId); offsetTimeCustomerStartInd++)
    {
      StbM_TimeNotificationCustomerConfigIterType customerId = StbM_GetTimeNotificationCustomerConfigOffsetInd(offsetTimeCustomerStartInd);
      /* #20 Cache current elapsed time since start of running timers */
      if (StbM_GetNotificationCustomerStates(customerId).timerState != STBM_TIMER_STOPPED)
      {
        StbM_SynchronizedTimeBaseType offsetTimeBaseId = StbM_GetTimeBaseConfigIdxOfTimeNotificationCustomerConfig(customerId);
        StbM_TimeStampType currentTime;
        StbM_UserDataType userDataTemp;

        Std_ReturnType currentTimeIsValid = StbM_CalculateCurrentOffsetTime(offsetTimeBaseId, &currentTime, &userDataTemp); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */

        if (currentTimeIsValid == E_OK)
        {
          currentTimeIsValid = StbM_TimestampMinusTimestamp(&(StbM_GetNotificationCustomerStates(customerId).expireTime), &currentTime, &(StbM_GetNotificationCustomerStates(customerId).elapsedOffsetTime)); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_GLOBALPTR */
        }

        /* #30 If any error occurred, stop related timer */
        if (currentTimeIsValid == E_NOT_OK)
        {
          StbM_GetNotificationCustomerStates(customerId).timerState = STBM_TIMER_STOPPED; /* SBSW_STBM_ACCESS_NOTIFICATIONCUSTOMERSTATE */
        }

        retVal |= currentTimeIsValid;
      }
    }
  }

  return retVal;
} /* StbM_CalcElapsedTimeOfOffsetTimeBase() */

/**********************************************************************************************************************
 *  StbM_UpdateExpireTimeOfOffsetTimeBase()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 ******************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_UpdateExpireTimeOfOffsetTimeBase(StbM_SynchronizedTimeBaseType timeBaseId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If timeBase is referred by an offset time base having time notification customers */
  if (StbM_IsTimeNotificationCustomerConfigOffsetIndUsedOfTimeBaseConfig(timeBaseId)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    StbM_TimeNotificationCustomerConfigOffsetIndIterType offsetTimeCustomerStartInd = StbM_GetTimeNotificationCustomerConfigOffsetIndStartIdxOfTimeBaseConfig(timeBaseId);
    for (; offsetTimeCustomerStartInd < StbM_GetTimeNotificationCustomerConfigOffsetIndEndIdxOfTimeBaseConfig(timeBaseId); offsetTimeCustomerStartInd++)
    {
      StbM_TimeNotificationCustomerConfigIterType customerId = StbM_GetTimeNotificationCustomerConfigOffsetInd(offsetTimeCustomerStartInd);
      /* #20 Re-adjust expire time of offset timeBases customer */
      if (StbM_GetNotificationCustomerStates(customerId).timerState != STBM_TIMER_STOPPED)
      {
        StbM_SynchronizedTimeBaseType offsetTimeBaseId = StbM_GetTimeBaseConfigIdxOfTimeNotificationCustomerConfig(customerId);
        StbM_TimeStampType currentTime;
        StbM_UserDataType userDataTemp;

        Std_ReturnType currentTimeIsValid = StbM_CalculateCurrentOffsetTime(offsetTimeBaseId, &currentTime, &userDataTemp); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */

        if (currentTimeIsValid == E_OK)
        {
          currentTimeIsValid = StbM_TimestampPlusTimestamp(&(StbM_GetNotificationCustomerStates(customerId).elapsedOffsetTime), &currentTime, &(StbM_GetNotificationCustomerStates(customerId).expireTime)); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_GLOBALPTR */
        }

        /* #30 If any error occurred, stop related timer */
        if (currentTimeIsValid == E_NOT_OK)
        {
          StbM_GetNotificationCustomerStates(customerId).timerState = STBM_TIMER_STOPPED; /* SBSW_STBM_ACCESS_NOTIFICATIONCUSTOMERSTATE */
        }

        retVal |= currentTimeIsValid;
      }
    }
  }

  return retVal;
} /* StbM_UpdateExpireTimeOfOffsetTimeBase() */
#endif

#if (STBM_GLOBALTIMEMASTEROFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_SetNewGlobalTime()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 ********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_SetNewGlobalTime(StbM_SynchronizedTimeBaseType timeBaseId, P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStamp, P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userData)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  SchM_Enter_StbM_STBM_EXCLUSIVE_AREA_0();
  /* #10 If time base is an Offset time base, handle Offset calculation */
# if (STBM_TIMEBASECONFIGIDXOFTIMEBASECONFIG == STD_ON)
  if (StbM_IsOffsetTimeBase(timeBaseId))
  {
    retVal = StbM_CalcNewOffsetTime(timeBaseId, timeStamp); /* SBSW_STBM_FUNCTIONCALL_PARAMPTR */
  }
  else
# endif
  {
    /* #20 Update local time */
    retVal = StbM_UpdateTimestamp(timeBaseId);

    /* #30 Save time stamps of last synchronization */
    StbM_SetSyncGlobalTimeStampOfTimeBaseState(timeBaseId, *timeStamp); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
    StbM_SetSyncVirtualLocalTimeStampOfTimeBaseState(timeBaseId, StbM_GetVirtualLocalTimeStampOfTimeBaseState(timeBaseId)); /* SBSW_STBM_ACCESS_TIMEBASESTATE */

    if (retVal == E_OK)
    {
      retVal = StbM_CalcNewGlobalTime(timeBaseId, timeStamp, userData); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */

# if (STBM_OFFSET_TIME_NOTIFICATION_CUSTOMER == STD_ON)
      if (retVal == E_OK)
      {
        /* #40 Update expire time Offset Time Notification customers referring the given synchronized Time base */
        retVal = StbM_UpdateExpireTimeOfOffsetTimeBase(timeBaseId);
      }
# endif
    }
  }
  SchM_Exit_StbM_STBM_EXCLUSIVE_AREA_0();

  return retVal;
} /* StbM_SetNewGlobalTime() */

/**********************************************************************************************************************
 *  StbM_CalcNewGlobalTime()
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
 ********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalcNewGlobalTime(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStamp,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userData)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
# if (STBM_TIMENOTIFICATIONCUSTOMERCONFIG == STD_ON)
  /* #10 Update Expire Time of Time Notification Customers */
  retVal = StbM_UpdateExpireTime(timeBaseId, timeStamp); /* SBSW_STBM_FUNCTIONCALL_PARAMPTR */

#  if (STBM_OFFSET_TIME_NOTIFICATION_CUSTOMER == STD_ON)
  if (retVal == E_OK)
  {
    /* #20 Cache elapsed time of Offset Time Notification customers referring the given synchronized Time base */
    retVal = StbM_CalcElapsedTimeOfOffsetTimeBase(timeBaseId);
  }
#  endif
# else
  retVal = E_OK;
# endif

# if (STBM_STATUSNOTIFICATIONCUSTOMERCONFIG == STD_ON)
  /* #30 Set status notification events */
  StbM_SetGlobalTime_SetStatusEvents(timeBaseId);
# endif

  /* #40 Get current time from timeStamp */
  StbM_SetTimeStampOfTimeBaseState(timeBaseId, *timeStamp); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  /* #50 Get current user data from userData, if userData is not NULL */
  if (userData != NULL_PTR)
  {
    StbM_CopyUserData(userData, &StbM_GetUserDataOfTimeBaseState(timeBaseId)); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_GLOBALPTR */
  }

  /* #60 Set the globalTimeBase bit within TimeBaseStatus, clear all other bits */
  StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus = StbM_Global_Time_Base_BflMask; /* SBSW_STBM_ACCESS_TIMEBASESTATE */

  return retVal;
} /* StbM_CalcNewGlobalTime() */
#endif

#if ((STBM_TIMEBASECONFIGIDXOFTIMEBASECONFIG == STD_ON) && (STBM_GLOBALTIMEMASTEROFTIMEBASECONFIG == STD_ON))
/**********************************************************************************************************************
 *  StbM_CalcNewOffsetTime()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 ********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalcNewOffsetTime(StbM_SynchronizedTimeBaseType timeBaseId, P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  StbM_TimeStampType syncTimeStamp, offsetTimeStamp;
  StbM_UserDataType synchronizedUserData;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the globalTimeBase bit within the referenced TimeBaseStatus is set */
  if (StbM_GetGlobalTimeBaseBit(StbM_GetTimeStampOfTimeBaseState(StbM_GetTimeBaseConfigIdxOfTimeBaseConfig(timeBaseId)).timeBaseStatus) != 0u)
  {
    /* #20 Calculate and set the new offset value */
    retVal = StbM_CalculateCurrentTime(StbM_GetTimeBaseConfigIdxOfTimeBaseConfig(timeBaseId), &syncTimeStamp, &synchronizedUserData); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */
    if (retVal == E_OK)
    {
      retVal = StbM_TimestampMinusTimestamp(timeStampPtr, &syncTimeStamp, &offsetTimeStamp); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */
      if (retVal == E_OK)
      {
        retVal = StbM_SetNewOffsetTime(timeBaseId, &offsetTimeStamp); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */
      }
    }
  }
  else
  {
    /* #30 Set return value to E_NOT_OK */
    retVal = E_NOT_OK;
  }

  return retVal;
} /* StbM_CalcNewOffsetTime() */

/**********************************************************************************************************************
 *  StbM_SetNewOffsetTime()
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
 ********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_SetNewOffsetTime(StbM_SynchronizedTimeBaseType timeBaseId, P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  StbM_TimeStampType synchronizedTimeStamp;
  StbM_UserDataType synchronizedUserData;
  StbM_TimeStampType syncGlobalTimeStamp;

  /* ----- Implementation ----------------------------------------------- */
# if (STBM_TIMENOTIFICATIONCUSTOMERCONFIGOFFSETINDUSEDOFTIMEBASECONFIG == STD_ON)
  retVal = StbM_UpdateExpireTime(timeBaseId, timeStampPtr); /* SBSW_STBM_FUNCTIONCALL_PARAMPTR */

  if (retVal == E_OK)
# endif
  {
# if (STBM_STATUSNOTIFICATIONCUSTOMERCONFIG == STD_ON)
    /* #10 If notification customer is configured */
    if (StbM_IsStatusNotificationCustomerConfigUsedOfTimeBaseConfig(timeBaseId)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */ /* COV_STBM_ALL_OFFSET_TIMEBASES_WITH_STATUSNOTIFICATIONS */
    {
      StbM_StatusNotificationCustomerConfigIterType customerIdx = StbM_GetStatusNotificationCustomerConfigIdxOfTimeBaseConfig(timeBaseId);

      /* Check EV_GLOBAL_TIME_BASE, EV_RESYNC */
      StbM_StatusNotificationMaskOfStatusNotificationCustomerConfigType customerMask = StbM_GetStatusNotificationMaskOfStatusNotificationCustomerConfig(customerIdx);

      /* #20 Check and set Global TimeBase notification event */
      StbM_CheckAndSetGlobalTimeBaseEv(timeBaseId, customerIdx, customerMask);

      /* #30 Check and set ReSync event */
      StbM_CheckAndSetResyncEv(customerIdx, customerMask);
    }
# endif

    /* #40 Set globalTimeBase bit and timestamp */
    StbM_SetGlobalTimeBaseBit(StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
    StbM_GetTimeStampOfTimeBaseState(timeBaseId).nanoseconds = timeStampPtr->nanoseconds; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
    StbM_GetTimeStampOfTimeBaseState(timeBaseId).seconds = timeStampPtr->seconds; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
    StbM_GetTimeStampOfTimeBaseState(timeBaseId).secondsHi = timeStampPtr->secondsHi; /* SBSW_STBM_ACCESS_TIMEBASESTATE */

    /* #50 Calculate current local time of referenced synchronized time base */
    retVal = StbM_CalculateCurrentTime(StbM_GetTimeBaseConfigIdxOfTimeBaseConfig(timeBaseId), &synchronizedTimeStamp, &synchronizedUserData); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */

    if (retVal == E_OK) /* COV_STBM_ALL_OFFSET_TIMEBASES_WITH_TIMENOTIFICATIONCUSTOMER */
    {
      /* #60 Save time stamps of last synchronization */
      retVal = StbM_TimestampPlusTimestamp(timeStampPtr, &synchronizedTimeStamp, &syncGlobalTimeStamp); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */
      StbM_SetSyncGlobalTimeStampOfTimeBaseState(timeBaseId, syncGlobalTimeStamp); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
      StbM_SetSyncLocalTimeStampOfTimeBaseState(timeBaseId, synchronizedTimeStamp); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
    }
  }

  return retVal;
}
#endif

#if (STBM_TIME_RECORDING_SUPPORT_USED == STD_ON)
/**********************************************************************************************************************
 *  StbM_GetRecordTableStartIdx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 ********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(StbM_CurrentRecordTableBlockIdxOfTimeBaseStateType, STBM_CODE) StbM_GetRecordTableStartIdx(StbM_SynchronizedTimeBaseType timeBaseId)
{
  /* ----- Local Variables ---------------------------------------------- */
  StbM_CurrentRecordTableBlockIdxOfTimeBaseStateType recordTableStartIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If time base is an offset time base return the offset record table start index */
# if (STBM_OFFSETRECORDTABLEBLOCK == STD_ON)
#  if (STBM_SYNCRECORDTABLEBLOCK == STD_ON)
  if (StbM_IsOffsetTimeBase(timeBaseId))
#  endif
  {
    recordTableStartIdx = StbM_GetOffsetRecordTableBlockStartIdxOfTimeBaseConfig(timeBaseId);
  }
# endif
  /* #20 If time base is an synchronized time base return the sync record table start index */
# if (STBM_SYNCRECORDTABLEBLOCK == STD_ON)
#  if (STBM_OFFSETRECORDTABLEBLOCK == STD_ON)
  else
#  endif
  {
    recordTableStartIdx = StbM_GetSyncRecordTableBlockStartIdxOfTimeBaseConfig(timeBaseId);
  }
# endif

  return recordTableStartIdx;
} /* StbM_GetRecordTableStartIdx() */

/**********************************************************************************************************************
 *  StbM_GetRecordTableEndIdx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 ********************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(StbM_CurrentRecordTableBlockIdxOfTimeBaseStateType, STBM_CODE) StbM_GetRecordTableEndIdx(StbM_SynchronizedTimeBaseType timeBaseId)
{
  /* ----- Local Variables ---------------------------------------------- */
  StbM_CurrentRecordTableBlockIdxOfTimeBaseStateType recordTableEndIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If time base is an offset time base return the offset record table end index */
# if (STBM_OFFSETRECORDTABLEBLOCK == STD_ON)
#  if (STBM_SYNCRECORDTABLEBLOCK == STD_ON)
  if (StbM_IsOffsetTimeBase(timeBaseId))
#  endif
  {
    recordTableEndIdx = StbM_GetOffsetRecordTableBlockEndIdxOfTimeBaseConfig(timeBaseId);
  }
# endif
  /* #20 If time base is an synchronized time base return the sync record table end index */
# if (STBM_SYNCRECORDTABLEBLOCK == STD_ON)
#  if (STBM_OFFSETRECORDTABLEBLOCK == STD_ON)
  else
#  endif
  {
    recordTableEndIdx = StbM_GetSyncRecordTableBlockEndIdxOfTimeBaseConfig(timeBaseId);
  }
# endif

  return recordTableEndIdx;
} /* StbM_GetRecordTableEndIdx() */
#endif

/**********************************************************************************************************************
 *  StbM_InitializeEachTimeBase()
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
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_InitializeEachTimeBase(StbM_TimeBaseConfigIterType timeBaseId)
{
  /* ----- Local Variables ---------------------------------------------- */
#if (STBM_OSLOCALTIMECONFIG == STD_ON)
  TickType osTicks;
#endif

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize sync loss timeout counter */
  StbM_SetSyncLossTimeoutCountOfTimeBaseState(timeBaseId, 0u); /* SBSW_STBM_ACCESS_TIMEBASESTATE */

  /* #20 Initialize timestamp of time base */
  StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus = 0x00u; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  StbM_GetTimeStampOfTimeBaseState(timeBaseId).nanoseconds = 0u; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  StbM_GetTimeStampOfTimeBaseState(timeBaseId).seconds = 0u; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  StbM_GetTimeStampOfTimeBaseState(timeBaseId).secondsHi = 0u; /* SBSW_STBM_ACCESS_TIMEBASESTATE */

  /* #30 Initialize virtual local time */
  StbM_GetVirtualLocalTimeStampOfTimeBaseState(timeBaseId).nanoseconds = 0u; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  StbM_GetVirtualLocalTimeStampOfTimeBaseState(timeBaseId).seconds = 0u; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  StbM_GetVirtualLocalTimeStampOfTimeBaseState(timeBaseId).secondsHi = 0u; /* SBSW_STBM_ACCESS_TIMEBASESTATE */

/* #40 If ethernet controller is used for local time */
#if (STBM_ETHTSYN_LOCALTIME_USED == STD_ON)
  /* #50 Initialize local time */
  StbM_GetEthLocalTimeOfTimeBaseState(timeBaseId).nanoseconds = 0u; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  StbM_GetEthLocalTimeOfTimeBaseState(timeBaseId).seconds = 0u; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  StbM_GetEthLocalTimeOfTimeBaseState(timeBaseId).secondsHi = 0u; /* SBSW_STBM_ACCESS_TIMEBASESTATE */

  /* #60 Set local time using ethernet */
  StbM_SetLocalTime(timeBaseId);
#endif

/* #70 If local time comes from OS counter, initialize local os counter value */
#if (STBM_OSLOCALTIMECONFIG == STD_ON)
  /* get counter value of last update of local time */
  if (StbM_IsOsLocalTimeUsed(timeBaseId))
  {
    (void) GetCounterValue(StbM_GetOsLocalTimeIDOfOsLocalTimeConfig(StbM_GetOsLocalTimeConfigIdxOfTimeBaseConfig(timeBaseId)), &osTicks); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */
    StbM_SetLocalTimeTickValueOfTimeBaseState(timeBaseId, (uint32) osTicks); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  }
#endif

/* #80 If Gpt is used, initialize Gpt */
#if (STBM_GPTLOCALTIMECONFIG == STD_ON)
  StbM_SetGptChannel(timeBaseId);
#endif

  /* #90 Initialize user data */
  StbM_GetUserDataOfTimeBaseState(timeBaseId).userDataLength = 0u; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  StbM_GetUserDataOfTimeBaseState(timeBaseId).userByte0 = 0u; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  StbM_GetUserDataOfTimeBaseState(timeBaseId).userByte1 = 0u; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  StbM_GetUserDataOfTimeBaseState(timeBaseId).userByte2 = 0u; /* SBSW_STBM_ACCESS_TIMEBASESTATE */

#if ((STBM_RATEMEASUREMENTSTORAGE == STD_ON) || (STBM_MASTERRATECORRECTIONALLOWEDOFTIMEBASECONFIG == STD_ON))
  /* #100 Initialize rate correction */
  StbM_InitializeRateCorrection(timeBaseId);
#endif

  /* #110 Initialize update counter */
  StbM_SetUpdateCounterOfTimeBaseState(timeBaseId, 0u); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  
  /* #120 Initialize time leap values */
  StbM_SetTimeLeapFutureThresholdCountOfTimeBaseState(timeBaseId, 0u); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  StbM_SetTimeLeapPastThresholdCountOfTimeBaseState(timeBaseId, 0u); /* SBSW_STBM_ACCESS_TIMEBASESTATE */

/* #130 Initialize time recording */
#if (STBM_TIME_RECORDING_SUPPORT_USED == STD_ON)
# if (STBM_TIMERECORDINGDISABLEDOFTIMEBASECONFIG == STD_ON)
  if (StbM_IsTimeRecordingDisabledOfTimeBaseConfig(timeBaseId) == FALSE) /* PRQA S 1881 */ /* MD_MSR_AutosarBoolean */
# endif
  {
    StbM_SetCurrentRecordTableBlockIdxOfTimeBaseState(timeBaseId, StbM_GetRecordTableStartIdx((StbM_SynchronizedTimeBaseType) timeBaseId)); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
# if (STBM_SYNCRECORDTABLEBLOCK == STD_ON)
    StbM_GetRecordTableForSync(timeBaseId);
# endif

# if (STBM_OFFSETRECORDTABLEBLOCK == STD_ON)
    StbM_GetRecordTableForOffset(timeBaseId);
# endif
  }
#endif
}

#if (STBM_GPTLOCALTIMECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_SetGptChannel()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_SetGptChannel(StbM_TimeBaseConfigIterType timeBaseId)
{
  /* ----- Implementation ----------------------------------------------- */
  if (
# if ((STBM_OSLOCALTIMECONFIG == STD_ON) || (STBM_ETHTSYN_LOCALTIME_USED == STD_ON) || (STBM_TIMEBASECONFIGIDXOFTIMEBASECONFIG == STD_ON))
     StbM_IsGptLocalTimeUsed(timeBaseId) &&
# endif
     (!StbM_IsInitialized()))
  {
    /* #10 If state of Gpt channel is not already active */
    if (StbM_IsGptChannelActive(StbM_GetGptChannelActiveIdxOfGptLocalTimeConfig(StbM_GetGptLocalTimeConfigIdxOfTimeBaseConfig(timeBaseId))) == FALSE) /* PRQA S 1881 */ /* MD_MSR_AutosarBoolean */ /* COV_STBM_NO_GPT_CHANNEL_USED_MULTIPLE_TIMES */
    {
      /* #20 Start Gpt timer */
      Gpt_StartTimer(StbM_GetGptLocalTimeIDOfGptLocalTimeConfig(StbM_GetGptLocalTimeConfigIdxOfTimeBaseConfig(timeBaseId)), (Gpt_ValueType) StbM_GetLocalTimeMaxValueOfGptLocalTimeConfig(StbM_GetGptLocalTimeConfigIdxOfTimeBaseConfig(timeBaseId)));
      
      /* #30 Set state of Gpt channel to active */
      StbM_SetGptChannelActive(StbM_GetGptChannelActiveIdxOfGptLocalTimeConfig(StbM_GetGptLocalTimeConfigIdxOfTimeBaseConfig(timeBaseId)), TRUE); /* SBSW_STBM_ACCESS_GPTCHANNELACTIVE */
    }
    /* #40 Initialize local Gpt timer value */
    StbM_SetLocalTimeTickValueOfTimeBaseState(timeBaseId, 0u); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  }
} /* StbM_SetGptChannel() */
#endif

#if (STBM_ETHTSYN_LOCALTIME_USED == STD_ON)
/**********************************************************************************************************************
 *  StbM_SetLocalTime()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_SetLocalTime(StbM_TimeBaseConfigIterType timeBaseId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_ModeType ethIfMode;
  Eth_TimeStampQualType ethIfTimeQual;
  Eth_TimeStampType ethIfTimeStamp;

  /* ----- Implementation ----------------------------------------------- */
# if ((STBM_OSLOCALTIMECONFIG == STD_ON) || (STBM_GPTLOCALTIMECONFIG == STD_ON) || (STBM_TIMEBASECONFIGIDXOFTIMEBASECONFIG == STD_ON))
  if (StbM_IsUsesEthTSynLocalTimeOfTimeBaseConfig(timeBaseId))
# endif
  {
    Std_ReturnType retVal = EthIf_GetControllerMode(StbM_GetEthIfCtrlIdxOfTimeBaseConfig(timeBaseId), &ethIfMode); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */

    if ((retVal == E_OK) && (ethIfMode == ETH_MODE_ACTIVE))
    {
      if ((EthIf_GetCurrentTime(StbM_GetEthIfCtrlIdxOfTimeBaseConfig(timeBaseId), &ethIfTimeQual, &ethIfTimeStamp) == E_OK) && (ethIfTimeQual == ETH_VALID)) /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */
      {
        /* #10 Set the local time of the time base state */
        StbM_SetEthLocalTimeOfTimeBaseState(timeBaseId, ethIfTimeStamp); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
      }
    }
  }
} /* StbM_SetLocalTime() */
#endif

#if ((STBM_RATEMEASUREMENTSTORAGE == STD_ON) || (STBM_MASTERRATECORRECTIONALLOWEDOFTIMEBASECONFIG == STD_ON))
/**********************************************************************************************************************
 *  StbM_InitializeRateCorrection()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_InitializeRateCorrection(StbM_TimeBaseConfigIterType timeBaseId)
{
  /* ----- Local Variables ---------------------------------------------- */
# if (STBM_RATEMEASUREMENTSTORAGE == STD_ON)
  StbM_RateMeasurementStorageIterType rateMeasurementIdx;
# endif

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize the rate correction */
  StbM_SetRateCorrectionOfTimeBaseState(timeBaseId, 1.0); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  StbM_SetRateCorrectionSetOfTimeBaseState(timeBaseId, FALSE); /* SBSW_STBM_ACCESS_TIMEBASESTATE */

  StbM_GetSyncGlobalTimeStampOfTimeBaseState(timeBaseId).nanoseconds = 0u; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  StbM_GetSyncGlobalTimeStampOfTimeBaseState(timeBaseId).seconds = 0u; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  StbM_GetSyncGlobalTimeStampOfTimeBaseState(timeBaseId).secondsHi = 0u; /* SBSW_STBM_ACCESS_TIMEBASESTATE */

  StbM_GetSyncLocalTimeStampOfTimeBaseState(timeBaseId).nanoseconds = 0u; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  StbM_GetSyncLocalTimeStampOfTimeBaseState(timeBaseId).seconds = 0u; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  StbM_GetSyncLocalTimeStampOfTimeBaseState(timeBaseId).secondsHi = 0u; /* SBSW_STBM_ACCESS_TIMEBASESTATE */

  StbM_GetSyncVirtualLocalTimeStampOfTimeBaseState(timeBaseId).nanoseconds = 0u; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  StbM_GetSyncVirtualLocalTimeStampOfTimeBaseState(timeBaseId).seconds = 0u; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  StbM_GetSyncVirtualLocalTimeStampOfTimeBaseState(timeBaseId).secondsHi = 0u; /* SBSW_STBM_ACCESS_TIMEBASESTATE */

# if (STBM_RATEMEASUREMENTSTORAGE == STD_ON)
  StbM_SetCurrentRateMeasurementIdxOfTimeBaseState(timeBaseId, StbM_GetRateMeasurementStorageEndIdxOfTimeBaseConfig(timeBaseId) - 1u); /* SBSW_STBM_ACCESS_TIMEBASESTATE */

  for (rateMeasurementIdx = StbM_GetRateMeasurementStorageStartIdxOfTimeBaseConfig(timeBaseId); rateMeasurementIdx < StbM_GetRateMeasurementStorageEndIdxOfTimeBaseConfig(timeBaseId); rateMeasurementIdx++)
  {
    StbM_GetRateMeasurementStorage(rateMeasurementIdx).StartGlobalTime = StbM_GetTimeStampOfTimeBaseState(timeBaseId); /* SBSW_STBM_ACCESS_RATEMEASUREMENTSTORAGE */
    StbM_GetRateMeasurementStorage(rateMeasurementIdx).Discard = FALSE; /* SBSW_STBM_ACCESS_RATEMEASUREMENTSTORAGE */
  }
# endif
} /* StbM_GetAndSetRateMeasurements() */
#endif

#if (STBM_SYNCRECORDTABLEBLOCK == STD_ON)
/**********************************************************************************************************************
 *  StbM_GetRecordTableForSync()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_GetRecordTableForSync(StbM_TimeBaseConfigIterType timeBaseId)
{
  /* ----- Implementation ----------------------------------------------- */
# if (STBM_OFFSETRECORDTABLEBLOCK == STD_ON)
  if (!StbM_IsOffsetTimeBase(timeBaseId))
# endif
  {
    StbM_SyncRecordTableBlockIterType syncRecordTableBlockIdx;

    /* #10 Get the record table for sync */
    StbM_GetSyncRecordTableHead(StbM_GetSyncRecordTableHeadIdxOfTimeBaseConfig(timeBaseId)).SynchronizedTimeDomain = StbM_GetTimeBaseIdOfTimeBaseConfig(timeBaseId); /* SBSW_STBM_ACCESS_SYNCRECORDTABLEHEAD */
    StbM_GetSyncRecordTableHead(StbM_GetSyncRecordTableHeadIdxOfTimeBaseConfig(timeBaseId)).HWfrequency = StbM_GetHWfrequencyOfTimeBaseConfig(timeBaseId); /* SBSW_STBM_ACCESS_SYNCRECORDTABLEHEAD */
    StbM_GetSyncRecordTableHead(StbM_GetSyncRecordTableHeadIdxOfTimeBaseConfig(timeBaseId)).HWprescaler = StbM_GetHWprescalerOfTimeBaseConfig(timeBaseId); /* SBSW_STBM_ACCESS_SYNCRECORDTABLEHEAD */

    for (syncRecordTableBlockIdx = StbM_GetSyncRecordTableBlockStartIdxOfTimeBaseConfig(timeBaseId); syncRecordTableBlockIdx < StbM_GetSyncRecordTableBlockEndIdxOfTimeBaseConfig(timeBaseId); syncRecordTableBlockIdx++)
    {
      StbM_GetSyncRecordTableBlock(syncRecordTableBlockIdx).GlbSeconds = 0u; /* SBSW_STBM_ACCESS_SYNCRECORDTABLEBLOCK */
      StbM_GetSyncRecordTableBlock(syncRecordTableBlockIdx).GlbNanoSeconds = 0u; /* SBSW_STBM_ACCESS_SYNCRECORDTABLEBLOCK */
      StbM_GetSyncRecordTableBlock(syncRecordTableBlockIdx).TimeBaseStatus = 0u; /* SBSW_STBM_ACCESS_SYNCRECORDTABLEBLOCK */
      StbM_GetSyncRecordTableBlock(syncRecordTableBlockIdx).HWcounter = 0u; /* SBSW_STBM_ACCESS_SYNCRECORDTABLEBLOCK */
      StbM_GetSyncRecordTableBlock(syncRecordTableBlockIdx).RateDeviation = 0; /* SBSW_STBM_ACCESS_SYNCRECORDTABLEBLOCK */
      StbM_GetSyncRecordTableBlock(syncRecordTableBlockIdx).LocSeconds = 0u; /* SBSW_STBM_ACCESS_SYNCRECORDTABLEBLOCK */
      StbM_GetSyncRecordTableBlock(syncRecordTableBlockIdx).LocNanoSeconds = 0u; /* SBSW_STBM_ACCESS_SYNCRECORDTABLEBLOCK */
      StbM_GetSyncRecordTableBlock(syncRecordTableBlockIdx).PathDelay = 0u; /* SBSW_STBM_ACCESS_SYNCRECORDTABLEBLOCK */
    }
  }
} /* StbM_GetRecordTableForSync() */
#endif

#if (STBM_OFFSETRECORDTABLEBLOCK == STD_ON)
/**********************************************************************************************************************
 *  StbM_GetRecordTableForOffset()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_GetRecordTableForOffset(StbM_TimeBaseConfigIterType timeBaseId)
{
  /* ----- Implementation ----------------------------------------------- */
# if (STBM_SYNCRECORDTABLEBLOCK == STD_ON)
  if (StbM_IsOffsetTimeBase(timeBaseId))
# endif
  {
    StbM_OffsetRecordTableBlockIterType offsetRecordTableBlockIdx;

    /* #10 Get the record table for offset */
    StbM_GetOffsetRecordTableHead(StbM_GetOffsetRecordTableHeadIdxOfTimeBaseConfig(timeBaseId)).OffsetTimeDomain = StbM_GetTimeBaseIdOfTimeBaseConfig(timeBaseId); /* SBSW_STBM_ACCESS_OFFSETRECORDTABLEHEAD */

    for (offsetRecordTableBlockIdx = StbM_GetOffsetRecordTableBlockStartIdxOfTimeBaseConfig(timeBaseId); offsetRecordTableBlockIdx < StbM_GetOffsetRecordTableBlockEndIdxOfTimeBaseConfig(timeBaseId); offsetRecordTableBlockIdx++)
    {
      StbM_GetOffsetRecordTableBlock(offsetRecordTableBlockIdx).GlbSeconds = 0u; /* SBSW_STBM_ACCESS_OFFSETRECORDTABLEBLOCK */
      StbM_GetOffsetRecordTableBlock(offsetRecordTableBlockIdx).GlbNanoSeconds = 0u; /* SBSW_STBM_ACCESS_OFFSETRECORDTABLEBLOCK */
      StbM_GetOffsetRecordTableBlock(offsetRecordTableBlockIdx).TimeBaseStatus = 0u; /* SBSW_STBM_ACCESS_OFFSETRECORDTABLEBLOCK */
    }
  }
} /* StbM_GetRecordTableForOffset() */
#endif

/**********************************************************************************************************************
 *  StbM_IterateOverTimeBases()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_IterateOverTimeBases(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  StbM_SynchronizedTimeBaseType timeBaseId;

  /* ----- Implementation ----------------------------------------------- */
#if (STBM_TIMENOTIFICATIONCUSTOMERCONFIG == STD_ON)
  /* #10 Start GPT Timer for Time Notification Customers if required */
  StbM_StartGptTimer(StbM_GetNextExpirationPoint(FALSE));
#endif

  for (timeBaseId = 0u; timeBaseId < StbM_GetSizeOfTimeBaseConfig(); timeBaseId++)
  {

#if (STBM_TIME_RECORDING_SUPPORT_USED == STD_ON)
    if (StbM_GetCurrentRecordTableBlockIdxOfTimeBaseState(timeBaseId) >= StbM_GetRecordTableEndIdx(timeBaseId))
    {
      StbM_SetCurrentRecordTableBlockIdxOfTimeBaseState(timeBaseId, StbM_GetRecordTableStartIdx(timeBaseId)); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
    }
#endif

    /* #20 Update synchronized local time bases */
#if (STBM_TIMEBASECONFIGIDXOFTIMEBASECONFIG == STD_ON)
    if (!StbM_IsOffsetTimeBase(timeBaseId))
#endif
    {
      (void) StbM_UpdateTimestamp(timeBaseId);
    }

#if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
    /* #30 Check if Timeout has occurred */
    StbM_CheckIfTimeoutOccurred(timeBaseId);
#endif

  }

} /* StbM_IterateOverTimeBases */

#if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckIfTimeoutOccurred()
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
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckIfTimeoutOccurred(StbM_SynchronizedTimeBaseType timeBaseId)
{
  /* ----- Implementation ----------------------------------------------- */
  if (StbM_GetSyncLossTimeoutCountOfTimeBaseState(timeBaseId) > 0u)
  {
    StbM_DecSyncLossTimeoutCountOfTimeBaseState(timeBaseId); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
    if (StbM_GetSyncLossTimeoutCountOfTimeBaseState(timeBaseId) == 0u)
    {
# if (STBM_STATUSNOTIFICATIONCUSTOMERCONFIG == STD_ON)
      StbM_StatusNotificationCustomerConfigIterType customerIdx = StbM_GetStatusNotificationCustomerConfigIdxOfTimeBaseConfig(timeBaseId);

      if (StbM_IsStatusNotificationCustomerConfigUsedOfTimeBaseConfig(timeBaseId)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */ /* COV_STBM_ALL_TIMEBASES_WITH_SYNCLOSSTIMEOUT_STATUSNOTIFICATIONS */
      {
        StbM_StatusNotificationMaskOfStatusNotificationCustomerConfigType customerMask = StbM_GetStatusNotificationMaskOfStatusNotificationCustomerConfig(customerIdx);

        /* #10 Check and set Timeout notification event */
        StbM_CheckAndSetTimeoutNotificationEv(customerIdx, customerMask);

        /* #20 Check and set sync to subdomain notification event */
        StbM_CheckAndSetSyncToSubdomainEv(timeBaseId, customerIdx, customerMask, FALSE);
      }
# endif
      /* #30 Set Timeout Bit */
      StbM_SetTimeoutBit(StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus); /* SBSW_STBM_ACCESS_TIMEBASESTATE */

# if (STBM_TIMEGATEWAYOFTIMEBASECONFIG == STD_ON)
      /* #40 If TimeGateway is present, set Gateway Bit */
      if (StbM_IsTimeGatewayOfTimeBaseConfig(timeBaseId)) /* COV_STBM_ALL_GATEWAYS_NO_SYNCLOSSTIMEOUT */
      {
        StbM_SetSyncToGatewayBit(StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
      }
# endif

# if (STBM_RATEMEASUREMENTSTORAGE == STD_ON)
      /* #50 Discard rate measurements */
      StbM_DiscardRateMeasurements(timeBaseId);
# endif
    }
  }
} /* StbM_CheckIfTimeoutOccurred() */
#endif

#if (STBM_TIME_RECORDING_SUPPORT_USED == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckAndNotify()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndNotify(StbM_SynchronizedTimeBaseType timeBaseId)
{
  /* ----- Implementation ----------------------------------------------- */
  if (StbM_GetCurrentRecordTableBlockIdxOfTimeBaseState(timeBaseId) >= StbM_GetRecordTableEndIdx(timeBaseId))
  {
    /* #10 Notify the application by calling the callback block by block */
# if (STBM_SYNCRECORDTABLEBLOCK == STD_ON)
    StbM_NotifyTheApplicationForSyncTime(timeBaseId);
# endif
# if (STBM_OFFSETRECORDTABLEBLOCK == STD_ON)
    StbM_NotifyTheApplicationForOffsetTime(timeBaseId);
# endif
  }
} /* StbM_CheckAndNotify */
#endif

#if (STBM_SYNCRECORDTABLEBLOCK == STD_ON)
/**********************************************************************************************************************
 *  StbM_NotifyTheApplicationForSyncTime()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_NotifyTheApplicationForSyncTime(StbM_SynchronizedTimeBaseType timeBaseId)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Notify the application by calling the callback block by block */
# if (STBM_OFFSETRECORDTABLEBLOCK == STD_ON)
  if (!StbM_IsOffsetTimeBase(timeBaseId))
# endif
  {
    StbM_SyncRecordTableBlockIterType syncRecordTableBlockIdx;

    for (syncRecordTableBlockIdx = StbM_GetSyncRecordTableBlockStartIdxOfTimeBaseConfig(timeBaseId); syncRecordTableBlockIdx < StbM_GetSyncRecordTableBlockEndIdxOfTimeBaseConfig(timeBaseId); syncRecordTableBlockIdx++)
    {
      StbM_SyncTimeRecordBlockCallbackFctType SyncTimeRecordBlockCallbackPtr = StbM_GetSyncTimeRecordBlockCallbacks(StbM_GetSyncTimeRecordBlockCallbacksIdxOfTimeBaseConfig(timeBaseId));
      if (SyncTimeRecordBlockCallbackPtr != NULL_PTR) /* COV_STBM_SILENT_TX */
      {
        SyncTimeRecordBlockCallbackPtr(&StbM_GetSyncRecordTableBlock(syncRecordTableBlockIdx)); /* SBSW_STBM_FCTPTRCALL_RECORDTABLE */
      }
    }
  }
} /* StbM_NotifyTheApplicationForSyncTime() */
#endif

#if (STBM_OFFSETRECORDTABLEBLOCK == STD_ON)
/**********************************************************************************************************************
 *  StbM_NotifyTheApplicationForOffsetTime()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_NotifyTheApplicationForOffsetTime(StbM_SynchronizedTimeBaseType timeBaseId)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Notify the application by calling the callback block by block */
# if (STBM_SYNCRECORDTABLEBLOCK == STD_ON)
  if (StbM_IsOffsetTimeBase(timeBaseId))
# endif
  {
    StbM_OffsetRecordTableBlockIterType offsetRecordTableBlockIdx;

    for (offsetRecordTableBlockIdx = StbM_GetOffsetRecordTableBlockStartIdxOfTimeBaseConfig(timeBaseId); offsetRecordTableBlockIdx < StbM_GetOffsetRecordTableBlockEndIdxOfTimeBaseConfig(timeBaseId); offsetRecordTableBlockIdx++)
    {
      StbM_OffsetTimeRecordBlockCallbackFctType OffsetTimeRecordBlockCallbackPtr = StbM_GetOffsetTimeRecordBlockCallbacks(StbM_GetOffsetTimeRecordBlockCallbacksIdxOfTimeBaseConfig(timeBaseId));
      if (OffsetTimeRecordBlockCallbackPtr != NULL_PTR) /* COV_STBM_SILENT_TX */
      {
        OffsetTimeRecordBlockCallbackPtr(&StbM_GetOffsetRecordTableBlock(offsetRecordTableBlockIdx)); /* SBSW_STBM_FCTPTRCALL_RECORDTABLE */
      }
    }
  }
} /* StbM_NotifyTheApplicationForOffsetTime() */
#endif

#if (STBM_STATUSNOTIFICATIONCUSTOMERCONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CallNotificationCallBackAndClear()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CallNotificationCallBackAndClear(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call status notification and clear event */
  StbM_StatusNotificationCustomerConfigIterType customerIdx = 0;
  for (; customerIdx < StbM_GetSizeOfStatusNotificationCustomerConfig(); customerIdx++)
  {
    StbM_CallStatusNotificationCallbackAndClearEvent(customerIdx);
  }
} /* StbM_CallNotificationCallBackAndClear() */
#endif

#if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CalculationsOfTimestamps()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalculationsOfTimestamps(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
# if (STBM_TIMENOTIFICATIONCUSTOMERCONFIG == STD_ON)
  retVal = StbM_UpdateExpireTime(timeBaseId, timeStampPtr); /* SBSW_STBM_FUNCTIONCALL_PARAMPTR */
  if (retVal == E_OK)
# endif
  {
# if (STBM_OFFSET_TIME_NOTIFICATION_CUSTOMER == STD_ON)
    retVal = StbM_CalcElapsedTimeOfOffsetTimeBase(timeBaseId);
    if (retVal == E_OK)
# endif
    {
      /* #10 Update local time of synchronized Time-Base */
# if (STBM_TIMEBASECONFIGIDXOFTIMEBASECONFIG == STD_ON)
      if (StbM_IsOffsetTimeBase(timeBaseId))
      {
        retVal = StbM_UpdateTimestamp(StbM_GetTimeBaseConfigIdxOfTimeBaseConfig(timeBaseId));
      }
      else
# endif
      {
        retVal = StbM_UpdateTimestamp(timeBaseId);
      }
    }
  }

# if (STBM_TIMENOTIFICATIONCUSTOMERCONFIG == STD_OFF)
  STBM_DUMMY_STATEMENT(timeStampPtr); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# endif

  return retVal;
} /* StbM_CalculationsOfTimestamps() */
#endif

#if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CheckAndSetTime()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CheckAndSetTime(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  retVal = StbM_TimeLeapCheck(timeBaseId, timeStampPtr); /* SBSW_STBM_FUNCTIONCALL_PARAMPTR */

# if (STBM_STATUSNOTIFICATIONCUSTOMERCONFIG == STD_ON)
  StbM_CheckAndSetSync(timeBaseId, timeStampPtr); /* SBSW_STBM_FUNCTIONCALL_PARAMPTR */
# endif

# if (STBM_RATEMEASUREMENTSTORAGE == STD_ON)
  /* #10 Discard rate measurement if state of the SyncToGatewayBit changed during measurement */
  if (StbM_GetSyncToGatewayBit(StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus) != StbM_GetSyncToGatewayBit(timeStampPtr->timeBaseStatus))
  {
    StbM_DiscardRateMeasurements(timeBaseId);
  }
# endif

  StbM_SetTheGatewayAndTimeBaseBit(timeBaseId, timeStampPtr); /* SBSW_STBM_FUNCTIONCALL_PARAMPTR */

# if (STBM_RATEMEASUREMENTSTORAGE == STD_ON)
  /* #20 If no error occurred */
  if (retVal == E_OK)
  {
    /* #30 Perform rate correction measurement */
    retVal = StbM_RateCorrectionMeasurement(timeBaseId, timeStampPtr); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR */
  }
# endif
  return retVal;
} /* StbM_CheckAndSetTime() */
#endif

#if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CalculationsOfBusSetGlobalTime()
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
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalculationsOfBusSetGlobalTime(StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userDataPtr,
  P2CONST(StbM_MeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Clear timeout bit */
  StbM_ClearTimeoutBit(StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus); /* SBSW_STBM_ACCESS_TIMEBASESTATE */

  /* #20 Start new measuring of timeout */
  StbM_SetSyncLossTimeoutCountOfTimeBaseState(timeBaseId, StbM_GetSyncLossTimeoutOfTimeBaseConfig(timeBaseId)); /* SBSW_STBM_ACCESS_TIMEBASESTATE */

/* #30 If time recording support is enabled */
# if (STBM_TIME_RECORDING_SUPPORT_USED == STD_ON)
  if (StbM_GetCurrentRecordTableBlockIdxOfTimeBaseState(timeBaseId) >= StbM_GetRecordTableEndIdx(timeBaseId))
  {
    StbM_SetCurrentRecordTableBlockIdxOfTimeBaseState(timeBaseId, StbM_GetRecordTableStartIdx(timeBaseId)); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  }

#  if (STBM_SYNCRECORDTABLEBLOCK == STD_ON)
#   if (STBM_TIMERECORDINGDISABLEDOFTIMEBASECONFIG == STD_ON)
  if (StbM_IsTimeRecordingDisabledOfTimeBaseConfig(timeBaseId) == FALSE) /* PRQA S 1881 */ /* MD_MSR_AutosarBoolean */
#   endif
  {
    /* #40 If time base is a synchronized time base */
#   if (STBM_OFFSETRECORDTABLEBLOCK == STD_ON)
    if (!StbM_IsOffsetTimeBase(timeBaseId))
#   endif
    {
      StbM_SyncRecordTableBlockIterType currentRecordTableBlock = StbM_GetCurrentRecordTableBlockIdxOfTimeBaseState(timeBaseId);
      /* #50 Write current local time according to block elements of record table */
      StbM_GetSyncRecordTableBlock(currentRecordTableBlock).LocSeconds = StbM_GetTimeStampOfTimeBaseState(timeBaseId).seconds; /* SBSW_STBM_ACCESS_SYNCRECORDTABLEBLOCK_RUNTIMEIDX */
      StbM_GetSyncRecordTableBlock(currentRecordTableBlock).LocNanoSeconds = StbM_GetTimeStampOfTimeBaseState(timeBaseId).nanoseconds; /* SBSW_STBM_ACCESS_SYNCRECORDTABLEBLOCK_RUNTIMEIDX */
    }
  }
#  endif

# endif
  /* #60 Set local time to global time */
  StbM_GetTimeStampOfTimeBaseState(timeBaseId).nanoseconds = timeStampPtr->nanoseconds; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  StbM_GetTimeStampOfTimeBaseState(timeBaseId).seconds = timeStampPtr->seconds; /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  StbM_GetTimeStampOfTimeBaseState(timeBaseId).secondsHi = timeStampPtr->secondsHi; /* SBSW_STBM_ACCESS_TIMEBASESTATE */

  /* #70 Increment update counter of time base */
  StbM_IncrementTimeBaseUpdateCounter(timeBaseId);

  /* #80 Update User Data if provided data is not NULL */
  if (userDataPtr != NULL_PTR)
  {
    StbM_CopyUserData(userDataPtr, &StbM_GetUserDataOfTimeBaseState(timeBaseId)); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_GLOBALPTR */
  }

  /* #90 If time recording support is enabled */
# if (STBM_TIME_RECORDING_SUPPORT_USED == STD_ON)
  StbM_WriteResidualBlocks(timeBaseId, measureDataPtr); /* SBSW_STBM_FUNCTIONCALL_PARAMPTR */
# endif

# if (STBM_OFFSET_TIME_NOTIFICATION_CUSTOMER == STD_ON)
  retVal = StbM_UpdateExpireTimeOfOffsetTimeBase(timeBaseId);
# else
  retVal = E_OK;
# endif

# if (STBM_TIME_RECORDING_SUPPORT_USED == STD_OFF)
  STBM_DUMMY_STATEMENT(measureDataPtr); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# endif

  return retVal;
} /* StbM_CalculationsOfBusSetGlobalTime() */

/**********************************************************************************************************************
 *  StbM_TimeLeapCheck()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_TimeLeapCheck(
  StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Perform Time Leap Check */
  if (StbM_GetGlobalTimeBaseBit(StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus) != 0u)
  {
    retVal = StbM_CheckTimeLeapFuture(timeBaseId, timeStampPtr); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR */
    if (retVal == E_OK)
    {
      retVal = StbM_CheckTimeLeapPast(timeBaseId, timeStampPtr); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR */
    }
  }
  return retVal;
} /* StbM_TimeLeapCheck() */
#endif

#if ((STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON) && (STBM_STATUSNOTIFICATIONCUSTOMERCONFIG == STD_ON))
/**********************************************************************************************************************
 *  StbM_CheckAndSetSync()
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
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_CheckAndSetSync(StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  StbM_StatusNotificationCustomerConfigIterType customerIdx;

  /* ----- Implementation ----------------------------------------------- */
  customerIdx = StbM_GetStatusNotificationCustomerConfigIdxOfTimeBaseConfig(timeBaseId);

  /* #10 If notification customer is configured */
  if (StbM_IsStatusNotificationCustomerConfigUsedOfTimeBaseConfig(timeBaseId)) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    /* Check EV_GLOBAL_TIME_BASE, EV_TIMEOUT_REMOVED, EV_SYNC_TO_SUBDOMAIN, EV_SYNC_TO_GLOBAL_MASTER, EV_RESYNC */
    StbM_StatusNotificationMaskOfStatusNotificationCustomerConfigType customerMask = StbM_GetStatusNotificationMaskOfStatusNotificationCustomerConfig(customerIdx);

    /* #20 Check and set sync to Global TimeBase notification event */
    StbM_CheckAndSetGlobalTimeBaseEv(timeBaseId, customerIdx, customerMask);

    /* #30 Check and set TimeoutRemoved notification event */
    StbM_CheckAndSetTimeoutRemovedNotificationEv(timeBaseId, customerIdx, customerMask);

    /* #40 Check and set SyncToGlobalMaster event, if SYNC_TO_GATEWAY Bit in status of provided timestamp ptr is not set */
    if (StbM_GetSyncToGatewayBit(timeStampPtr->timeBaseStatus) == 0u)
    {
      StbM_CheckAndSetSyncToGlobalMasterEv(timeBaseId, customerIdx, customerMask);
    }
    /* #50 Otherwise, check and set SyncToSubdomain notification event */
    else
    {
      StbM_CheckAndSetSyncToSubdomainEv(timeBaseId, customerIdx, customerMask, TRUE);
    }

    /* #60 Check and set ReSync event */
    StbM_CheckAndSetResyncEv(customerIdx, customerMask);

    /* Hint: Rate correction ev is set within the context of rate correction value calculation */
  }
} /* StbM_CheckAndSetSync() */
#endif

#if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_SetTheGatewayAndTimeBaseBit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_SetTheGatewayAndTimeBaseBit(StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set syncToGateway bit according syncToGateway bit within timeBaseStatus of the timeStampPtr argument */
  if (StbM_GetSyncToGatewayBit(timeStampPtr->timeBaseStatus) == 0u)
  {
    StbM_ClearSyncToGatewayBit(StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  }
  else
  {
    StbM_SetSyncToGatewayBit(StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  }

  /* #20 Set globalTimeBase bit */
  StbM_SetGlobalTimeBaseBit(StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
} /* StbM_SetTheGatewayAndTimeBaseBit() */
#endif

#if ((STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON) && (STBM_TIME_RECORDING_SUPPORT_USED == STD_ON))
/**********************************************************************************************************************
 * StbM_WriteResidualBlocks()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STBM_LOCAL_INLINE FUNC(void, STBM_CODE) StbM_WriteResidualBlocks(StbM_SynchronizedTimeBaseType timeBaseId, P2CONST(StbM_MeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr)
{
  /* ----- Implementation ----------------------------------------------- */
# if (STBM_TIMERECORDINGDISABLEDOFTIMEBASECONFIG == STD_ON)
  if (StbM_IsTimeRecordingDisabledOfTimeBaseConfig(timeBaseId) == FALSE) /* PRQA S 1881 */ /* MD_MSR_AutosarBoolean */
# endif
  {
    /* #10 Record current state to record table */
# if (STBM_SYNCRECORDTABLEBLOCK == STD_ON)
#  if (STBM_OFFSETRECORDTABLEBLOCK == STD_ON)
    if (!StbM_IsOffsetTimeBase(timeBaseId))
#  endif
    {
      StbM_SyncRecordTableBlockIterType currentRecordTableBlock = StbM_GetCurrentRecordTableBlockIdxOfTimeBaseState(timeBaseId);
      StbM_GetSyncRecordTableBlock(currentRecordTableBlock).GlbSeconds = StbM_GetTimeStampOfTimeBaseState(timeBaseId).seconds; /* SBSW_STBM_ACCESS_SYNCRECORDTABLEBLOCK_RUNTIMEIDX */
      StbM_GetSyncRecordTableBlock(currentRecordTableBlock).GlbNanoSeconds = StbM_GetTimeStampOfTimeBaseState(timeBaseId).nanoseconds; /* SBSW_STBM_ACCESS_SYNCRECORDTABLEBLOCK_RUNTIMEIDX */
      StbM_GetSyncRecordTableBlock(currentRecordTableBlock).TimeBaseStatus = StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus; /* SBSW_STBM_ACCESS_SYNCRECORDTABLEBLOCK_RUNTIMEIDX */
#  if (STBM_OSLOCALTIMECONFIG == STD_ON)
      if (StbM_IsOsLocalTimeUsed(timeBaseId))
      {
        StbM_GetSyncRecordTableBlock(currentRecordTableBlock).HWcounter = StbM_GetLocalTimeTickValueOfTimeBaseState(timeBaseId); /* SBSW_STBM_ACCESS_SYNCRECORDTABLEBLOCK_RUNTIMEIDX */
      }
#  endif
#  if (STBM_GPTLOCALTIMECONFIG == STD_ON)
      if (StbM_IsGptLocalTimeUsed(timeBaseId)) /* COV_STBM_ALL_SYNCTIMEBASES_WITH_TIMERECORDING_GPTLOCALTIME */
      {
        StbM_GetSyncRecordTableBlock(currentRecordTableBlock).HWcounter = StbM_GetLocalTimeTickValueOfTimeBaseState(timeBaseId); /* SBSW_STBM_ACCESS_SYNCRECORDTABLEBLOCK_RUNTIMEIDX */
      }
#  endif
#  if (STBM_ETHTSYN_LOCALTIME_USED == STD_ON)
      if (StbM_IsUsesEthTSynLocalTimeOfTimeBaseConfig(timeBaseId))
      {
        StbM_GetSyncRecordTableBlock(currentRecordTableBlock).HWcounter = StbM_GetEthLocalTimeOfTimeBaseState(timeBaseId).nanoseconds; /* SBSW_STBM_ACCESS_SYNCRECORDTABLEBLOCK_RUNTIMEIDX */
      }
#  endif
      StbM_GetSyncRecordTableBlock(currentRecordTableBlock).RateDeviation = (sint16)((StbM_GetRateCorrectionOfTimeBaseState(timeBaseId) * 1000000.0) - 1000000.0); /* PRQA S 4395 */ /* MD_StbM_Rule10.8 */  /* SBSW_STBM_ACCESS_SYNCRECORDTABLEBLOCK_RUNTIMEIDX */
      StbM_GetSyncRecordTableBlock(currentRecordTableBlock).PathDelay = measureDataPtr->pathDelay; /* SBSW_STBM_ACCESS_SYNCRECORDTABLEBLOCK_RUNTIMEIDX */
    }
# endif

# if (STBM_OFFSETRECORDTABLEBLOCK == STD_ON)
#  if (STBM_SYNCRECORDTABLEBLOCK == STD_ON)
    if (StbM_IsOffsetTimeBase(timeBaseId))
#  endif
    {
      StbM_OffsetRecordTableBlockIterType currentRecordTableBlock = StbM_GetCurrentRecordTableBlockIdxOfTimeBaseState(timeBaseId);
      StbM_GetOffsetRecordTableBlock(currentRecordTableBlock).GlbSeconds = StbM_GetTimeStampOfTimeBaseState(timeBaseId).seconds; /* SBSW_STBM_ACCESS_OFFSETRECORDTABLEBLOCK_RUNTIMEIDX */
      StbM_GetOffsetRecordTableBlock(currentRecordTableBlock).GlbNanoSeconds = StbM_GetTimeStampOfTimeBaseState(timeBaseId).nanoseconds; /* SBSW_STBM_ACCESS_OFFSETRECORDTABLEBLOCK_RUNTIMEIDX */
      StbM_GetOffsetRecordTableBlock(currentRecordTableBlock).TimeBaseStatus = StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus; /* SBSW_STBM_ACCESS_OFFSETRECORDTABLEBLOCK_RUNTIMEIDX */
    }
# endif
    /* #20 Increment the current record table block */
    StbM_IncCurrentRecordTableBlockIdxOfTimeBaseState(timeBaseId); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  }

# if (STBM_SYNCRECORDTABLEBLOCK == STD_OFF)
  STBM_DUMMY_STATEMENT(measureDataPtr); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# endif
} /* StbM_WriteResidualBlocks() */
#endif

#if ((STBM_MASTERRATECORRECTIONALLOWEDOFTIMEBASECONFIG == STD_ON) && (STBM_GLOBALTIMEMASTEROFTIMEBASECONFIG == STD_ON))
/**********************************************************************************************************************
 *  StbM_CalculateAndSetRateCorrection()
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
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalculateAndSetRateCorrection(StbM_SynchronizedTimeBaseType timeBaseId, StbM_RateDeviationType rateDeviation)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
# if (STBM_MASTERRATECORRECTIONFOROFFSETTIMEBASEOFTIMEBASECONFIG == STD_ON)
  StbM_TimeStampType synchronizedTimeStamp;
  StbM_UserDataType synchronizedUserData;
# endif
  sint64 diffLocalTime = 0;
  sint64 correctedLocalTime;
  StbM_TimeStampType syncGlobalTimeStamp;
  StbM_RateDeviationType correctedRateDeviation;

  /* ----- Implementation ----------------------------------------------- */
  SchM_Enter_StbM_STBM_EXCLUSIVE_AREA_0();

  /* #10 Calculate and save local time stamp of last synchronization */
# if (STBM_MASTERRATECORRECTIONFOROFFSETTIMEBASEOFTIMEBASECONFIG == STD_ON)
#  if (STBM_MASTERRATECORRECTIONFORSYNCTIMEBASEOFTIMEBASECONFIG == STD_ON)
  if (StbM_IsOffsetTimeBase(timeBaseId))
#  endif
  {
    retVal = StbM_CalculateCurrentTime(StbM_GetTimeBaseConfigIdxOfTimeBaseConfig(timeBaseId), &synchronizedTimeStamp, &synchronizedUserData); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */

    if (retVal == E_OK)
    {
      retVal = StbM_TimestampMinusTimestampInNs(&synchronizedTimeStamp, &StbM_GetSyncLocalTimeStampOfTimeBaseState(timeBaseId), &diffLocalTime); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */
      StbM_SetSyncLocalTimeStampOfTimeBaseState(timeBaseId, synchronizedTimeStamp); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
    }
  }
# endif
# if (STBM_MASTERRATECORRECTIONFORSYNCTIMEBASEOFTIMEBASECONFIG == STD_ON)
#  if (STBM_MASTERRATECORRECTIONFOROFFSETTIMEBASEOFTIMEBASECONFIG == STD_ON)
  else
#  endif
  {
    retVal = StbM_UpdateTimestamp(timeBaseId);

    if (retVal == E_OK)
    {
      retVal = StbM_TimestampMinusTimestampInNs(&StbM_GetVirtualLocalTimeStampOfTimeBaseState(timeBaseId), &StbM_GetSyncVirtualLocalTimeStampOfTimeBaseState(timeBaseId), &diffLocalTime); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */
      StbM_SetSyncVirtualLocalTimeStampOfTimeBaseState(timeBaseId, StbM_GetVirtualLocalTimeStampOfTimeBaseState(timeBaseId)); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
    }
  }
# endif

  if (retVal == E_OK)
  {
    /* #20 Calculate TGsync as TL based on the previous TGsync value */
    correctedLocalTime = (sint64)((float64)diffLocalTime * StbM_GetRateCorrectionOfTimeBaseState(timeBaseId)); /* PRQA S 4395 */ /* MD_StbM_Rule10.8 */
    retVal = StbM_TimestampPlusTimediff(&StbM_GetSyncGlobalTimeStampOfTimeBaseState(timeBaseId), correctedLocalTime, &syncGlobalTimeStamp); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */
    if (retVal == E_OK)
    {
      /* #30 Save global time stamp of last synchronization */
      StbM_SetSyncGlobalTimeStampOfTimeBaseState(timeBaseId, syncGlobalTimeStamp); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
    }
  }

  /* #40 If rateDeviation exceeds MasterRateDeviationMax, set value to MasterRateDeviationMax */
  if (rateDeviation > StbM_GetMasterRateDeviationMaxOfTimeBaseConfig(timeBaseId))
  {
    correctedRateDeviation = StbM_GetMasterRateDeviationMaxOfTimeBaseConfig(timeBaseId);
  }
  else if (rateDeviation < -StbM_GetMasterRateDeviationMaxOfTimeBaseConfig(timeBaseId))
  {
    correctedRateDeviation = -StbM_GetMasterRateDeviationMaxOfTimeBaseConfig(timeBaseId);
  }
  else
  {
    correctedRateDeviation = rateDeviation;
  }

  /* #50 Convert rateDeviation value to RateCorrection value */
  StbM_SetRateCorrectionOfTimeBaseState(timeBaseId, ((float64)correctedRateDeviation * 0.000001) + 1.0); /* SBSW_STBM_ACCESS_TIMEBASESTATE */
  StbM_SetRateCorrectionSetOfTimeBaseState(timeBaseId, TRUE); /* SBSW_STBM_ACCESS_TIMEBASESTATE */

# if (STBM_RATECORRECTIONSTATUSEVENTACTIVEOFTIMEBASECONFIG == STD_ON)
  /* Check EV_RATECORRECTION */
  /* #60 Check and set Ratecorrection notification event */
  StbM_CheckAndSetRatecorrectionEv(timeBaseId);
# endif

  SchM_Exit_StbM_STBM_EXCLUSIVE_AREA_0();

  return retVal;
} /* StbM_CalculateAndSetRateCorrection() */
#endif

#if (STBM_TIMENOTIFICATIONCUSTOMERCONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_CalculateExpireTime()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 ******************************************************************************************************************/
STBM_LOCAL_INLINE FUNC(Std_ReturnType, STBM_CODE) StbM_CalculateExpireTime(
  StbM_SynchronizedTimeBaseType timeBaseId,
  StbM_CustomerIdType customerId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) expireTime)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  StbM_TimeStampType currentTime;
  StbM_UserDataType userData;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If timer is not already running */
  if (StbM_GetNotificationCustomerStates(customerId).timerState == STBM_TIMER_STOPPED)
  {
    if (StbM_CalcTimeAndGetUserData(timeBaseId, &currentTime, &userData) == E_OK) /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */
    {
      /* #20 If given expireTime is valid */
      if (StbM_IsExpireTimeValid(expireTime) == TRUE) /* SBSW_STBM_FUNCTIONCALL_CONSTPTR */
      {
        /* #30 Calculate expire point as current time + given expire time */
        retVal = StbM_TimestampPlusTimestamp(&currentTime, expireTime, &(StbM_GetNotificationCustomerStates(customerId).expireTime)); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_GLOBALPTR */
        if (retVal == E_OK)
        {
          /* #40 If no error occurred, update state of customer as started */
          StbM_GetNotificationCustomerStates(customerId).timerState = STBM_TIMER_RUNNING; /* SBSW_STBM_ACCESS_NOTIFICATIONCUSTOMERSTATE */
          StbM_GetNotificationCustomerStates(customerId).gptExpirationPoint = STBM_INVALID_EXPIRATION_POINT; /* SBSW_STBM_ACCESS_NOTIFICATIONCUSTOMERSTATE */
        }
      }
    }
  }
  return retVal;
} /* StbM_CalculateExpireTime() */
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  StbM_InitMemory()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, STBM_CODE) StbM_InitMemory(void)
{
  /* ----- Implementation ----------------------------------------------- */
#if ((STBM_DEV_ERROR_DETECT == STD_ON) || (STBM_GPTLOCALTIMECONFIG == STD_ON))  /* COV_STBM_DEV_ERROR_DETECT_TX_tx_tf */
  /* #10 Initialized = FALSE */
  StbM_SetInitialized(FALSE); /* SBSW_STBM_ACCESS_CSL_VAR */
#endif
} /* StbM_InitMemory() */

/***********************************************************************************************************************
 *  StbM_Init()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, STBM_CODE) StbM_Init(P2CONST(StbM_ConfigType, AUTOMATIC, STBM_INIT_DATA) ConfigPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
#if (STBM_GPTLOCALTIMECONFIG == STD_ON)
  StbM_GptChannelActiveIterType gptChannelId;
#endif
  StbM_TimeBaseConfigIterType timeBaseId;

#if (STBM_TRIGGEREDCUSTOMERSTATE == STD_ON)
  StbM_TriggeredCustomerStateIterType customerId;
#endif

  /* ----- Implementation ----------------------------------------------- */
#if (STBM_GPTLOCALTIMECONFIG == STD_ON)
  for (gptChannelId = 0u; gptChannelId < StbM_GetSizeOfGptChannelActive(); gptChannelId++)
  {
    StbM_SetGptChannelActive(gptChannelId, FALSE); /* SBSW_STBM_ACCESS_GPTCHANNELACTIVE */
  }
#endif

  for (timeBaseId = 0u; timeBaseId < StbM_GetSizeOfTimeBaseConfig(); timeBaseId++)
  {
    StbM_InitializeEachTimeBase(timeBaseId);
  }

#if (STBM_TRIGGEREDCUSTOMERSTATE == STD_ON)
for (customerId = 0u; customerId < StbM_GetSizeOfTriggeredCustomerState(); customerId++)
  {
    StbM_GetTriggeredCustomerState(customerId).Counter = 0u; /* SBSW_STBM_ACCESS_TRIGGEREDCUSTOMERSTATE */
  }
#endif

#if (STBM_STATUSNOTIFICATIONCUSTOMERCONFIG == STD_ON)
  StbM_ResetStatusEvent();
#endif

#if (STBM_TIMENOTIFICATIONCUSTOMERCONFIG == STD_ON)
  StbM_StopTimeNotificationCustomers();
  Gpt_EnableNotification(STBM_TIME_NOTIFICATION_GPT_CHANNEL);
#endif

#if ((STBM_DEV_ERROR_DETECT == STD_ON) || (STBM_GPTLOCALTIMECONFIG == STD_ON))  /* COV_STBM_DEV_ERROR_DETECT_TX_tx_tf */
  StbM_SetInitialized(TRUE); /* SBSW_STBM_ACCESS_CSL_VAR */
#endif

  STBM_DUMMY_STATEMENT(ConfigPtr); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
} /* StbM_Init() */

/**********************************************************************************************************************
 *  StbM_MainFunction()
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
FUNC(void, STBM_CODE) StbM_MainFunction(void)
{
  /* ----- Local Variables ---------------------------------------------- */
#if (STBM_TIME_RECORDING_SUPPORT_USED == STD_ON)
  StbM_SynchronizedTimeBaseType timeBaseId;
#endif
  /* ----- Implementation ----------------------------------------------- */
#if (STBM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check If module is initialized */
  if (StbM_IsInitialized())
  {
#endif
#if (STBM_TIME_RECORDING_SUPPORT_USED == STD_ON)
    for (timeBaseId = 0u; timeBaseId < StbM_GetSizeOfTimeBaseConfig(); timeBaseId++)
    {
      /* #20 Handle time recording */
      StbM_CheckAndNotify(timeBaseId);
    }
#endif

    SchM_Enter_StbM_STBM_EXCLUSIVE_AREA_0();
    /* #30 Start GPT Timer and iterate over all time bases */
    StbM_IterateOverTimeBases();

#if (STBM_TRIGGEREDCUSTOMERCONFIG == STD_ON)
    /* #40 Trigger customers */
    StbM_TriggerCustomers();
#endif
    SchM_Exit_StbM_STBM_EXCLUSIVE_AREA_0();

#if (STBM_STATUSNOTIFICATIONCUSTOMERCONFIG == STD_ON)
    /* #50 Call status notification and clear event */
    StbM_CallNotificationCallBackAndClear();
#endif

#if (STBM_DEV_ERROR_DETECT == STD_ON)
  }
#endif
} /* StbM_MainFunction() */

#if (STBM_TIMENOTIFICATIONCUSTOMERCONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_NotificationFunction()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 ********************************************************************************************************************/
FUNC(void, STBM_CODE) StbM_NotificationFunction(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  StbM_TimeNotificationCustomerConfigIterType customerId = 0;
  sint64 deviationTime;
  StbM_TimeStampType timeStamp;
  StbM_UserDataType userData;
  StbM_SynchronizedTimeBaseType timeBaseId;

  /* ----- Implementation ----------------------------------------------- */
  SchM_Enter_StbM_STBM_EXCLUSIVE_AREA_0();
  /* #10 Call callbacks of elapsed timer */
  for (;customerId < StbM_GetSizeOfTimeNotificationCustomerConfig(); customerId++)
  {
# if (StbM_GetSizeOfTimeNotificationCustomerConfig() > 1u)
    if (StbM_GetNotificationCustomerStates(customerId).timerState == STBM_TIMER_CALL_CBK)
# endif
    {
      StbMTimeNotificationType TimeNotificationPtr = StbM_GetTimeNotificationOfTimeNotificationCustomerConfig(customerId);
      timeBaseId = StbM_GetTimeBaseConfigIdxOfTimeNotificationCustomerConfig(customerId);
      (void) StbM_CalcTimeAndGetUserData(timeBaseId, &timeStamp, &userData); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */

      StbM_GetNotificationCustomerStates(customerId).timerState = STBM_TIMER_STOPPED; /* SBSW_STBM_ACCESS_NOTIFICATIONCUSTOMERSTATE */
      StbM_GetNotificationCustomerStates(customerId).gptExpirationPoint = STBM_INVALID_EXPIRATION_POINT; /* SBSW_STBM_ACCESS_NOTIFICATIONCUSTOMERSTATE */
      (void) StbM_TimestampMinusTimestampInNs(&timeStamp, &(StbM_GetNotificationCustomerStates(customerId).expireTime), &deviationTime); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR */

      if (TimeNotificationPtr != NULL_PTR) /* COV_STBM_SILENT_TX */
      {
        (void) TimeNotificationPtr((StbM_TimeDiffType)deviationTime); /* SBSW_STBM_FCTPTRCALL_NOTIFICATION */
      }
    }
  }
  SchM_Exit_StbM_STBM_EXCLUSIVE_AREA_0();
} /* StbM_NotificationFunction() */
#endif

#if (STBM_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  StbM_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, STBM_CODE) StbM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, STBM_APPL_VAR) versioninfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = STBM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (STBM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check version info for NULL pointer */
  if (versioninfo == NULL_PTR)
  {
    errorId = STBM_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Set version info with corresponding macros from component header */
    versioninfo->vendorID = (STBM_VENDOR_ID); /* SBSW_STBM_ACCESS_PARAMPTR */
    versioninfo->moduleID = (STBM_MODULE_ID); /* SBSW_STBM_ACCESS_PARAMPTR */
    versioninfo->sw_major_version = (STBM_SW_MAJOR_VERSION); /* SBSW_STBM_ACCESS_PARAMPTR */
    versioninfo->sw_minor_version = (STBM_SW_MINOR_VERSION); /* SBSW_STBM_ACCESS_PARAMPTR */
    versioninfo->sw_patch_version = (STBM_SW_PATCH_VERSION); /* SBSW_STBM_ACCESS_PARAMPTR */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (STBM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != STBM_E_NO_ERROR)
  {
    /* #30 Report error if applicable */
    StbM_ReportError(STBM_SID_GET_VERSION_INFO, errorId);
  }
# else
  STBM_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# endif
} /* StbM_GetVersionInfo() */
#endif

/**********************************************************************************************************************
 *  StbM_GetCurrentTime()
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
FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentTime(StbM_SynchronizedTimeBaseType timeBaseId, P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_VAR) timeStampPtr, P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_VAR) userDataPtr)  /* PRQA S 1330 */ /* MD_StbM_Rule8.3_1330 */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = STBM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (STBM_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;
  /* #10 Check if component is initialized */
  if (!StbM_IsInitialized())
  {
    errorId = STBM_E_NOT_INITIALIZED;
  }
  /* #20 Check timeBaseId parameter validity against configuration */
  else if ((timeBaseId >= StbM_GetSizeOfTimeBaseConfig())
# if (STBM_RESERVEDTIMEBASEOFTIMEBASECONFIG == STD_ON)
    || (StbM_IsReservedTimeBaseOfTimeBaseConfig(timeBaseId))
# endif
    )
  {
    errorId = STBM_E_PARAM;
  }
  /* #30 Check timeStampPtr parameter for NULL pointer */
  else if (timeStampPtr == NULL_PTR)
  {
    errorId = STBM_E_PARAM_POINTER;
  }
  /* #40 Check userDataPtr parameter for NULL pointer */
  else if (userDataPtr == NULL_PTR)
  {
    errorId = STBM_E_PARAM_POINTER;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    SchM_Enter_StbM_STBM_EXCLUSIVE_AREA_0();
    /* #50 Calculate current time and update user data of the submitted time-base */
    retVal = StbM_CalcTimeAndGetUserData(timeBaseId, timeStampPtr, userDataPtr); /* SBSW_STBM_FUNCTIONCALL_PARAMPTR */
    SchM_Exit_StbM_STBM_EXCLUSIVE_AREA_0();
  }

  /* ----- Development Error Report --------------------------------------- */
#if (STBM_DEV_ERROR_REPORT == STD_ON)
  /* #60 Report error if applicable */
  if (errorId != STBM_E_NO_ERROR)
  {
    StbM_ReportError(STBM_SID_GET_CURRENT_TIME, errorId);
  }
#else
  STBM_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#endif
  return retVal;
} /* StbM_GetCurrentTime() */

#if (STBM_GET_CURRENT_TIME_EXTENDED_API == STD_ON)
/**********************************************************************************************************************
 *  StbM_GetCurrentTimeExtended()
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
FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentTimeExtended(StbM_SynchronizedTimeBaseType timeBaseId, /* PRQA S 1330 */ /* MD_StbM_Rule8.3_1330 */
  P2VAR(StbM_TimeStampExtendedType, AUTOMATIC, STBM_APPL_VAR) timeStampPtr,
  P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_VAR) userDataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = STBM_E_NO_ERROR;
  StbM_TimeStampType currentTime;

  /* ----- Development Error Checks ------------------------------------- */
# if (STBM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if component is initialized */
  if (!StbM_IsInitialized())
  {
    errorId = STBM_E_NOT_INITIALIZED;
  }
  /* #20 Check timeBaseId parameter validity against configuration */
  else if ((timeBaseId >= StbM_GetSizeOfTimeBaseConfig())
#  if (STBM_RESERVEDTIMEBASEOFTIMEBASECONFIG == STD_ON)
    || (StbM_IsReservedTimeBaseOfTimeBaseConfig(timeBaseId))
#  endif
    )
  {
    errorId = STBM_E_PARAM;
  }
  /* #30 Check timeStampPtr and userDataPtr parameter for NULL pointer */
  else if ((timeStampPtr == NULL_PTR) || (userDataPtr == NULL_PTR))
  {
    errorId = STBM_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    SchM_Enter_StbM_STBM_EXCLUSIVE_AREA_0();
    /* #40 Calculate current time of the submitted time-base in standard format and update user data */
    if (StbM_CalcTimeAndGetUserData(timeBaseId, &currentTime, userDataPtr) == E_OK) /* SBSW_STBM_FUNCTIONCALL_LOCALPTR_PARAMPTR */
    {
      /* #50 Convert current time from standard format to extended format */
      timeStampPtr->seconds = (uint64) currentTime.secondsHi << 16u; /* SBSW_STBM_ACCESS_PARAMPTR */
      timeStampPtr->seconds <<= 16u; /* SBSW_STBM_ACCESS_PARAMPTR */
      timeStampPtr->seconds += currentTime.seconds; /* SBSW_STBM_ACCESS_PARAMPTR */
      timeStampPtr->nanoseconds = currentTime.nanoseconds; /* SBSW_STBM_ACCESS_PARAMPTR */
      timeStampPtr->timeBaseStatus = currentTime.timeBaseStatus; /* SBSW_STBM_ACCESS_PARAMPTR */
      retVal = E_OK;
    }
    SchM_Exit_StbM_STBM_EXCLUSIVE_AREA_0();
  }

  /* ----- Development Error Report --------------------------------------- */
  /* #60 Report error if applicable */
# if (STBM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != STBM_E_NO_ERROR)
  {
    StbM_ReportError(STBM_SID_GET_CURRENT_TIME_EXTENDED, errorId);
  }
# else
  STBM_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# endif
  return retVal;
} /* StbM_GetCurrentTimeExtended() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

/**********************************************************************************************************************
 *  StbM_GetCurrentTimeRaw()
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
FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentTimeRaw(StbM_SynchronizedTimeBaseType timeBaseId, P2VAR(StbM_TimeStampRawType, AUTOMATIC, STBM_APPL_VAR) timeStampPtr)      /* PRQA S 1330 */ /* MD_StbM_Rule8.3_1330 */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = STBM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (STBM_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;
  /* #10 Check if component is initialized */
  if (!StbM_IsInitialized())
  {
    errorId = STBM_E_NOT_INITIALIZED;
  }
  /* #20 Check timeBaseId parameter validity against configuration */
  else if ((timeBaseId >= StbM_GetSizeOfTimeBaseConfig())
# if (STBM_TIMEBASECONFIGIDXOFTIMEBASECONFIG == STD_ON)
    || StbM_IsOffsetTimeBase(timeBaseId)
# endif
# if (STBM_RESERVEDTIMEBASEOFTIMEBASECONFIG == STD_ON)
    || (StbM_IsReservedTimeBaseOfTimeBaseConfig(timeBaseId))
# endif
    )
  {
    errorId = STBM_E_PARAM;
  }
  /* #30 Check timeStampPtr parameter for NULL pointer */
  else if (timeStampPtr == NULL_PTR)
  {
    errorId = STBM_E_PARAM_POINTER;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    SchM_Enter_StbM_STBM_EXCLUSIVE_AREA_0();
    /* #40 Update local time of the referenced time base */
    retVal = StbM_UpdateTimestamp(timeBaseId);
    /* #50 Set timeStampPtr to current time in raw format */
    *timeStampPtr = StbM_GetVirtualLocalTimeStampOfTimeBaseState(timeBaseId).nanoseconds; /* SBSW_STBM_ACCESS_PARAMPTR */
    SchM_Exit_StbM_STBM_EXCLUSIVE_AREA_0();
  }

  /* ----- Development Error Report --------------------------------------- */
  /* #60 Report error if applicable */
#if (STBM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != STBM_E_NO_ERROR)
  {
    StbM_ReportError(STBM_SID_GET_CURRENT_TIME_RAW, errorId);
  }
#else
  STBM_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#endif
  return retVal;
} /* StbM_GetCurrentTimeRaw() */

/**********************************************************************************************************************
 *  StbM_GetCurrentTimeDiff()
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
FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentTimeDiff(StbM_SynchronizedTimeBaseType timeBaseId, StbM_TimeStampRawType givenTimeStamp, P2VAR(StbM_TimeStampRawType, AUTOMATIC, STBM_APPL_VAR) timeStampDiffPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = STBM_E_NO_ERROR;
  uint32 currentTimeRaw;

  /* ----- Development Error Checks ------------------------------------- */
#if (STBM_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;
  /* #10 Check if component is initialized */
  if (!StbM_IsInitialized())
  {
    errorId = STBM_E_NOT_INITIALIZED;
  }
  /* #20 Check timeBaseId parameter validity against configuration */
  else if ((timeBaseId >= StbM_GetSizeOfTimeBaseConfig())
# if (STBM_TIMEBASECONFIGIDXOFTIMEBASECONFIG == STD_ON)
    || StbM_IsOffsetTimeBase(timeBaseId)
# endif
# if (STBM_RESERVEDTIMEBASEOFTIMEBASECONFIG == STD_ON)
    || (StbM_IsReservedTimeBaseOfTimeBaseConfig(timeBaseId))
# endif
    )
  {
    errorId = STBM_E_PARAM;
  }
  /* #30 Check timeStampDiffPtr parameter for NULL pointer */
  else if (timeStampDiffPtr == NULL_PTR)
  {
    errorId = STBM_E_PARAM_POINTER;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    SchM_Enter_StbM_STBM_EXCLUSIVE_AREA_0();
    /* #40 Update local time of the referenced time base */
    retVal = StbM_UpdateTimestamp(timeBaseId);
    /* #50 Get current time raw of the referenced time base */
    currentTimeRaw = StbM_GetVirtualLocalTimeStampOfTimeBaseState(timeBaseId).nanoseconds;
    /* #60 Set timeStampDiffPtr to current time raw minus given time raw */
    if (currentTimeRaw < givenTimeStamp)
    {
      *timeStampDiffPtr = (STBM_TIMESTAMP_MAX_NANOSECONDS - givenTimeStamp) + (1u + currentTimeRaw); /* SBSW_STBM_ACCESS_PARAMPTR */
    }
    else
    {
      *timeStampDiffPtr = currentTimeRaw - givenTimeStamp; /* SBSW_STBM_ACCESS_PARAMPTR */
    }
    SchM_Exit_StbM_STBM_EXCLUSIVE_AREA_0();
  }

  /* ----- Development Error Report --------------------------------------- */
  /* #70 Report error if applicable */
#if (STBM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != STBM_E_NO_ERROR)
  {
    StbM_ReportError(STBM_SID_GET_CURRENT_TIME_DIFF, errorId);
  }
#else
  STBM_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#endif
  return retVal;
} /* StbM_GetCurrentTimeDiff() */

#if (STBM_GLOBALTIMEMASTEROFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_SetGlobalTime()
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
FUNC(Std_ReturnType, STBM_CODE) StbM_SetGlobalTime(StbM_SynchronizedTimeBaseType timeBaseId, P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr, P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userDataPtr)     /* PRQA S 1330 */ /* MD_StbM_Rule8.3_1330 */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = STBM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (STBM_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;
  /* #10 Check if component is initialized */
  if (!StbM_IsInitialized())
  {
    errorId = STBM_E_NOT_INITIALIZED;
  }
  /* #20 Check timeBaseId parameter validity against configuration */
  else if ((timeBaseId >= StbM_GetSizeOfTimeBaseConfig())
#  if (STBM_RESERVEDTIMEBASEOFTIMEBASECONFIG == STD_ON)
    || (StbM_IsReservedTimeBaseOfTimeBaseConfig(timeBaseId))
#  endif
    )
  {
    errorId = STBM_E_PARAM;
  }
  /* #30 Check timeStampPtr parameter for NULL pointer */
  else if (timeStampPtr == NULL_PTR)
  {
    errorId = STBM_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #50 Increment update counter of time base */
    StbM_IncrementTimeBaseUpdateCounter(timeBaseId);

    /* #60 Set new global time */
    retVal = StbM_SetNewGlobalTime(timeBaseId, timeStampPtr, userDataPtr); /* SBSW_STBM_FUNCTIONCALL_PARAMPTR */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (STBM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != STBM_E_NO_ERROR)
  {
    StbM_ReportError(STBM_SID_SET_GLOBAL_TIME, errorId);
  }
# else
  STBM_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# endif
  return retVal;
} /* StbM_SetGlobalTime() */
#endif

#if (STBM_GLOBALTIMEMASTEROFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_SetUserData()
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
FUNC(Std_ReturnType, STBM_CODE) StbM_SetUserData(StbM_SynchronizedTimeBaseType timeBaseId, P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userDataPtr)    /* PRQA S 1330 */ /* MD_StbM_Rule8.3_1330 */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = STBM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (STBM_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;
  /* #10 Check if component is initialized */
  if (!StbM_IsInitialized())
  {
    errorId = STBM_E_NOT_INITIALIZED;
  }
  /* #20 Check timeBaseId parameter validity against configuration */
  else if ((timeBaseId >= StbM_GetSizeOfTimeBaseConfig())
#  if (STBM_RESERVEDTIMEBASEOFTIMEBASECONFIG == STD_ON)
    || (StbM_IsReservedTimeBaseOfTimeBaseConfig(timeBaseId))
#  endif
    )
  {
    errorId = STBM_E_PARAM;
  }
  /* #30 Check userDataPtr parameter for NULL pointer */
  else if (userDataPtr == NULL_PTR)
  {
    errorId = STBM_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    SchM_Enter_StbM_STBM_EXCLUSIVE_AREA_0();
    /* #40 Get current user data from userDataPtr */
    StbM_CopyUserData(userDataPtr, &StbM_GetUserDataOfTimeBaseState(timeBaseId)); /* SBSW_STBM_FUNCTIONCALL_CONSTPTR_GLOBALPTR */
    SchM_Exit_StbM_STBM_EXCLUSIVE_AREA_0();
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (STBM_DEV_ERROR_REPORT == STD_ON)
  /* #50 Report error if applicable */  
  if (errorId != STBM_E_NO_ERROR)
  {
    StbM_ReportError(STBM_SID_SET_USER_DATA, errorId);
  }
# else
  STBM_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# endif
  return retVal;
} /* StbM_SetUserData() */
#endif

#if (STBM_TIMEBASECONFIGIDXOFTIMEBASECONFIG == STD_ON)
# if (STBM_GLOBALTIMEMASTEROFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_SetOffset()
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
FUNC(Std_ReturnType, STBM_CODE) StbM_SetOffset(StbM_SynchronizedTimeBaseType timeBaseId, P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr)    /* PRQA S 1330 */ /* MD_StbM_Rule8.3_1330 */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = STBM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#  if (STBM_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;
  /* #10 Check initialization state of the component */
  if (!StbM_IsInitialized())
  {
    errorId = STBM_E_NOT_INITIALIZED;
  }
  /* #20 Check parameter 'timeBaseId' */
  else if ((timeBaseId >= StbM_GetSizeOfTimeBaseConfig()) || (!StbM_IsOffsetTimeBase(timeBaseId)))
  {
    errorId = STBM_E_PARAM;
  }
  /* #30 Check parameter 'timeStampPtr' */
  else if (timeStampPtr == NULL_PTR)
  {
    errorId = STBM_E_PARAM_POINTER;
  }
  else
#  endif
  {
    /* ----- Implementation ----------------------------------------------- */
    SchM_Enter_StbM_STBM_EXCLUSIVE_AREA_0();
    retVal = StbM_SetNewOffsetTime(timeBaseId, timeStampPtr); /* SBSW_STBM_FUNCTIONCALL_PARAMPTR */
    SchM_Exit_StbM_STBM_EXCLUSIVE_AREA_0();
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (STBM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != STBM_E_NO_ERROR)
  {
    StbM_ReportError(STBM_SID_SET_OFFSET, errorId);
  }
#  else
  STBM_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#  endif
  return retVal;
} /* StbM_SetOffset() */
# endif

/**********************************************************************************************************************
 *  StbM_GetOffset()
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
FUNC(Std_ReturnType, STBM_CODE) StbM_GetOffset(StbM_SynchronizedTimeBaseType timeBaseId, P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_VAR) timeStampPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = STBM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (STBM_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;
  /* #10 Check if component is initialized */
  if (!StbM_IsInitialized())
  {
    errorId = STBM_E_NOT_INITIALIZED;
  }
  /* #20 Check timeBaseId parameter validity against configuration */
  else if ((timeBaseId >= StbM_GetSizeOfTimeBaseConfig()) || (!StbM_IsOffsetTimeBase(timeBaseId)))
  {
    errorId = STBM_E_PARAM;
  }
  /* #30 Check timeStampPtr parameter for NULL pointer */
  else if (timeStampPtr == NULL_PTR)
  {
    errorId = STBM_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    SchM_Enter_StbM_STBM_EXCLUSIVE_AREA_0();

    /* #40 Set timeStampPtr to the current offset time of the submitted time-base */
    *timeStampPtr = StbM_GetTimeStampOfTimeBaseState(timeBaseId); /* SBSW_STBM_ACCESS_PARAMPTR */
    
    SchM_Exit_StbM_STBM_EXCLUSIVE_AREA_0();
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (STBM_DEV_ERROR_REPORT == STD_ON)
  /* #50 Report error if applicable */
  if (errorId != STBM_E_NO_ERROR)
  {
    StbM_ReportError(STBM_SID_GET_OFFSET, errorId);
  }
# else
  STBM_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# endif
  return retVal;
} /* StbM_GetOffset() */
#endif

#if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_BusSetGlobalTime()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, STBM_CODE) StbM_BusSetGlobalTime(StbM_SynchronizedTimeBaseType timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStampPtr,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userDataPtr,
  P2CONST(StbM_MeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = STBM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (STBM_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;
  /* #10 Check if component is initialized */
  if (!StbM_IsInitialized())
  {
    errorId = STBM_E_NOT_INITIALIZED;
  }
  /* #20 Check timeBaseId parameter validity against configuration */
  else if ((timeBaseId >= StbM_GetSizeOfTimeBaseConfig())
#  if (STBM_PURELOCALTIMEBASEOFTIMEBASECONFIG == STD_ON)
    || (StbM_IsPureLocalTimeBaseOfTimeBaseConfig(timeBaseId))
#  endif
    )
  {
    errorId = STBM_E_PARAM;
  }
  /* #30 Check timeStampPtr and measureDataPtr parameter for NULL pointer */
  else if ((timeStampPtr == NULL_PTR) || (measureDataPtr == NULL_PTR))
  {
    errorId = STBM_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    SchM_Enter_StbM_STBM_EXCLUSIVE_AREA_0();
    retVal = StbM_CalculationsOfTimestamps(timeBaseId, timeStampPtr); /* SBSW_STBM_FUNCTIONCALL_PARAMPTR */
    /* #40 If Update was successful, calculate the new global time */
    if (retVal == E_OK) /* COV_STBM_ETH_TSYN_RETVAL */
    {
      retVal = StbM_CheckAndSetTime(timeBaseId, timeStampPtr); /* SBSW_STBM_FUNCTIONCALL_PARAMPTR */
      if (retVal == E_OK)
      {
        retVal = StbM_CalculationsOfBusSetGlobalTime(timeBaseId, timeStampPtr, userDataPtr, measureDataPtr); /* SBSW_STBM_FUNCTIONCALL_PARAMPTR */
      }
    }
    SchM_Exit_StbM_STBM_EXCLUSIVE_AREA_0();
  }

  /* ----- Development Error Report --------------------------------------- */
# if (STBM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != STBM_E_NO_ERROR)
  {
    StbM_ReportError(STBM_SID_BUS_SET_GLOBAL_TIME, errorId);
  }
# elif (STBM_SYNCRECORDTABLEBLOCK == STD_OFF)
  STBM_DUMMY_STATEMENT(measureDataPtr);        /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
  STBM_DUMMY_STATEMENT(errorId);        /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# else
  STBM_DUMMY_STATEMENT(errorId);        /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# endif
  return retVal;
} /* StbM_BusSetGlobalTime() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

/**********************************************************************************************************************
 *  StbM_GetRateDeviation()
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
FUNC(Std_ReturnType, STBM_CODE) StbM_GetRateDeviation(StbM_SynchronizedTimeBaseType timeBaseId, P2VAR(StbM_RateDeviationType, AUTOMATIC, STBM_APPL_VAR) rateDeviation)   /* PRQA S 1330 */ /* MD_StbM_Rule8.3_1330 */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = STBM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (STBM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if component is initialized */
  if (!StbM_IsInitialized())
  {
    errorId = STBM_E_NOT_INITIALIZED;
  }
  /* #20 Check timeBaseId parameter validity against configuration */
  else if ((timeBaseId >= StbM_GetSizeOfTimeBaseConfig())
# if (STBM_RESERVEDTIMEBASEOFTIMEBASECONFIG == STD_ON)
    || (StbM_IsReservedTimeBaseOfTimeBaseConfig(timeBaseId))
# endif
    )
  {
    errorId = STBM_E_PARAM;
  }
  /* #30 Check rateDeviation parameter for NULL pointer */
  else if (rateDeviation == NULL_PTR)
  {
    errorId = STBM_E_PARAM_POINTER;
  }
  else
#else
# if ((STBM_RATEMEASUREMENTSTORAGE == STD_OFF) && (STBM_MASTERRATECORRECTIONALLOWEDOFTIMEBASECONFIG == STD_OFF))
  STBM_DUMMY_STATEMENT(timeBaseId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# endif
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    SchM_Enter_StbM_STBM_EXCLUSIVE_AREA_0();
#if ((STBM_RATEMEASUREMENTSTORAGE == STD_ON) || (STBM_MASTERRATECORRECTIONALLOWEDOFTIMEBASECONFIG == STD_ON))
    /* #40 If rate correction value is set */
    if (StbM_IsRateCorrectionSetOfTimeBaseState(timeBaseId))
    {
      /* #50 Convert RateCorrection value to rateDeviation value */
      *rateDeviation = (StbM_RateDeviationType)((StbM_GetRateCorrectionOfTimeBaseState(timeBaseId) * 1000000.0) - 1000000.0); /* PRQA S 4395 */ /* MD_StbM_Rule10.8 */ /* SBSW_STBM_ACCESS_PARAMPTR */
      retVal = E_OK;
    }
    else
#endif
    {
      /* #60 Otherwise set rateDeviation value to 0 */
      *rateDeviation = 0; /* SBSW_STBM_ACCESS_PARAMPTR */
    }
    SchM_Exit_StbM_STBM_EXCLUSIVE_AREA_0();
  }

  /* ----- Development Error Report --------------------------------------- */
#if (STBM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != STBM_E_NO_ERROR)
  {
    StbM_ReportError(STBM_SID_GET_RATE_DEVIATION, errorId);
  }
#else
  STBM_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#endif
  return retVal;
} /* StbM_GetRateDeviation() */

#if (STBM_GLOBALTIMEMASTEROFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_SetRateCorrection()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, STBM_CODE) StbM_SetRateCorrection(StbM_SynchronizedTimeBaseType timeBaseId, StbM_RateDeviationType rateDeviation)   /* PRQA S 1330 */ /* MD_StbM_Rule8.3_1330 */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId;

  /* ----- Development Error Checks ------------------------------------- */
# if (STBM_DEV_ERROR_DETECT == STD_ON)
#  if (STBM_MASTERRATECORRECTIONALLOWEDOFTIMEBASECONFIG == STD_ON)
  errorId = STBM_E_NO_ERROR;
#  endif
  /* #10 Check initialization state of the component */
  if (!StbM_IsInitialized())
  {
    errorId = STBM_E_NOT_INITIALIZED;
  }
  /* #20 Check parameter 'timeBaseId' */
  else if ((timeBaseId >= StbM_GetSizeOfTimeBaseConfig())
#  if (STBM_RESERVEDTIMEBASEOFTIMEBASECONFIG == STD_ON)
    || (StbM_IsReservedTimeBaseOfTimeBaseConfig(timeBaseId))
#  endif
    )
  {
    errorId = STBM_E_PARAM;
  }
  else
# else
  errorId = STBM_E_NO_ERROR;
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 If service is enabled */
# if (STBM_MASTERRATECORRECTIONALLOWEDOFTIMEBASECONFIG == STD_ON)
    if (StbM_IsMasterRateCorrectionAllowedOfTimeBaseConfig(timeBaseId))
    {
      retVal = StbM_CalculateAndSetRateCorrection(timeBaseId, rateDeviation);
    }
# else
    STBM_DUMMY_STATEMENT(rateDeviation); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#  if (STBM_DEV_ERROR_DETECT == STD_OFF)
    STBM_DUMMY_STATEMENT(timeBaseId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#  endif
# endif
# if (STBM_DEV_ERROR_DETECT == STD_ON)
#  if (STBM_MASTERRATECORRECTIONALLOWEDOFTIMEBASECONFIG == STD_ON)
    else
#  endif
    {
      errorId = STBM_E_SERVICE_DISABLED;
    }
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if (STBM_DEV_ERROR_REPORT == STD_ON)
#  if (STBM_MASTERRATECORRECTIONALLOWEDOFTIMEBASECONFIG == STD_ON)
  if (errorId != STBM_E_NO_ERROR)
#  endif
  {
    StbM_ReportError(STBM_SID_SET_RATE_CORRECTION, errorId);
  }
# else
  STBM_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# endif

  return retVal;
} /* StbM_SetRateCorrection() */
#endif

#if (STBM_SYNCRECORDTABLEHEAD == STD_ON)
/**********************************************************************************************************************
 *  StbM_GetSyncTimeRecordHead()
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
FUNC(Std_ReturnType, STBM_CODE) StbM_GetSyncTimeRecordHead(StbM_SynchronizedTimeBaseType timeBaseId, P2VAR(StbM_SyncRecordTableHeadType, AUTOMATIC, STBM_APPL_VAR) syncRecordTableHead)  /* PRQA S 1330 */ /* MD_StbM_Rule8.3_1330 */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = STBM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (STBM_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;
  /* #10 Check if component is initialized */
  if (!StbM_IsInitialized())
  {
    errorId = STBM_E_NOT_INITIALIZED;
  }
  /* #20 Check timeBaseId parameter validity against configuration */
  else if ((timeBaseId >= StbM_GetSizeOfTimeBaseConfig())
#  if (STBM_TIMEBASECONFIGIDXOFTIMEBASECONFIG == STD_ON)
    || StbM_IsOffsetTimeBase(timeBaseId)
#  endif
#  if (STBM_PURELOCALTIMEBASEOFTIMEBASECONFIG == STD_ON)
    || (StbM_IsPureLocalTimeBaseOfTimeBaseConfig(timeBaseId))
#  endif
#  if (STBM_RESERVEDTIMEBASEOFTIMEBASECONFIG == STD_ON)
    || (StbM_IsReservedTimeBaseOfTimeBaseConfig(timeBaseId))
#  endif
    )
  {
    errorId = STBM_E_PARAM;
  }
  /* #30 Check syncRecordTableHead parameter for NULL pointer */
  else if (syncRecordTableHead == NULL_PTR)
  {
    errorId = STBM_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    SchM_Enter_StbM_STBM_EXCLUSIVE_AREA_0();
    /* #40 Set syncRecordTableHead to the recorded snapshot data header of the submitted time-base */
    *syncRecordTableHead = StbM_GetSyncRecordTableHead(StbM_GetSyncRecordTableHeadIdxOfTimeBaseConfig(timeBaseId)); /* SBSW_STBM_ACCESS_PARAMPTR */
    SchM_Exit_StbM_STBM_EXCLUSIVE_AREA_0();
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (STBM_DEV_ERROR_REPORT == STD_ON)
  /* #50 Report error if applicable */
  if (errorId != STBM_E_NO_ERROR)
  {
    StbM_ReportError(STBM_SID_GET_SYNC_TIME_RECORD_HEAD, errorId);
  }
# else
  STBM_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# endif
  return retVal;
} /* StbM_GetSyncTimeRecordHead() */
#endif

#if (STBM_OFFSETRECORDTABLEHEAD == STD_ON)
/**********************************************************************************************************************
 *  StbM_GetOffsetTimeRecordHead()
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
FUNC(Std_ReturnType, STBM_CODE) StbM_GetOffsetTimeRecordHead(StbM_SynchronizedTimeBaseType timeBaseId, P2VAR(StbM_OffsetRecordTableHeadType, AUTOMATIC, STBM_APPL_VAR) offsetRecordTableHead)  /* PRQA S 1330 */ /* MD_StbM_Rule8.3_1330 */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = STBM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (STBM_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;
  /* #10 Check if component is initialized */
  if (!StbM_IsInitialized())
  {
    errorId = STBM_E_NOT_INITIALIZED;
  }
  /* #20 Check timeBaseId parameter validity against configuration */
  else if ((timeBaseId >= StbM_GetSizeOfTimeBaseConfig()) || (!StbM_IsOffsetTimeBase(timeBaseId)))
  {
    errorId = STBM_E_PARAM;
  }
  /* #30 Check offsetRecordTableHead parameter for NULL pointer */
  else if (offsetRecordTableHead == NULL_PTR)
  {
    errorId = STBM_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    SchM_Enter_StbM_STBM_EXCLUSIVE_AREA_0();
    /* #40 Set offsetRecordTableHead to the recorded snapshot data header of the submitted time-base */
    *offsetRecordTableHead = StbM_GetOffsetRecordTableHead(StbM_GetOffsetRecordTableHeadIdxOfTimeBaseConfig(timeBaseId)); /* SBSW_STBM_ACCESS_PARAMPTR */
    SchM_Exit_StbM_STBM_EXCLUSIVE_AREA_0();
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (STBM_DEV_ERROR_REPORT == STD_ON)
  /* #50 Report error if applicable */
  if (errorId != STBM_E_NO_ERROR)
  {
    StbM_ReportError(STBM_SID_GET_OFFSET_TIME_RECORD_HEAD, errorId);
  }
# else
  STBM_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# endif
  return retVal;
} /* StbM_GetOffsetTimeRecordHead() */
#endif

#if (STBM_TIMENOTIFICATIONCUSTOMERCONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_TimerCallback()
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
FUNC(void, STBM_CODE) StbM_TimerCallback(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  StbM_NotificationCustomerStatesIterType customerId = 0;
# if (StbM_GetSizeOfTimeNotificationCustomerConfig() > 1u)
  sint32 nextExpirationPoint;
# endif

  /* ----- Implementation ----------------------------------------------- */
  /* #5 Change state of customers, whose timer has elapsed */
  SchM_Enter_StbM_STBM_EXCLUSIVE_AREA_0();
  for (; customerId < StbM_GetSizeOfNotificationCustomerStates(); customerId++)
  {
    if (StbM_GetNotificationCustomerStates(customerId).timerState == STBM_TIMER_CBK_EXPECTED)
    {
      StbM_GetNotificationCustomerStates(customerId).timerState = STBM_TIMER_CALL_CBK; /* SBSW_STBM_ACCESS_NOTIFICATIONCUSTOMERSTATE */
    }
  }

# if (StbM_GetSizeOfTimeNotificationCustomerConfig() > 1u)
  /* #10 Calculate next expiration point */
  nextExpirationPoint = StbM_GetNextExpirationPoint(TRUE);

  /* #20 Start GPT Timer if requested, otherwise set status of GPT Timer to Stopped */
  if (StbM_GptTimerState == STBM_GPT_TIMER_START_REQUIRED)
  {
    StbM_StartGptTimer(nextExpirationPoint);
  }
  else
# endif
  {
    StbM_GptTimerState = STBM_GPT_TIMER_STOPPED;
  }
  SchM_Exit_StbM_STBM_EXCLUSIVE_AREA_0();

  /* #30 Set Event for StbM_NotificationFunction if event is configured */
# if (STBM_USE_OS_SET_EVENT_API == STD_ON)
  (void) SetEvent(STBM_TIME_CUSTOMER_TASK_NAME, STBM_TIME_CUSTOMER_EVENT_NAME);
# else
  /* #40 Otherwise Activate Task for StbM_NotificationFunction */
  (void) ActivateTask(STBM_TIME_CUSTOMER_TASK_NAME);
# endif
} /* StbM_TimerCallback() */

/**********************************************************************************************************************
 *  StbM_StartTimer()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 ******************************************************************************************************************/
FUNC(Std_ReturnType, STBM_CODE) StbM_StartTimer(StbM_SynchronizedTimeBaseType timeBaseId, StbM_CustomerIdType customerId, /* PRQA S 1330 */ /* MD_StbM_Rule8.3_1330 */
                                                P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) expireTime)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = STBM_E_NO_ERROR;
  Std_ReturnType retVal;

  /* ----- Development Error Checks ------------------------------------- */
# if (STBM_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;
  /* #10 Check initialization state of the component */
  if (!StbM_IsInitialized())
  {
    errorId = STBM_E_NOT_INITIALIZED;
  }
  /* #20 Check timeBaseId and customerId parameter validity against configuration */
  else if (
    (timeBaseId >= StbM_GetSizeOfTimeBaseConfig())
#  if (STBM_RESERVEDTIMEBASEOFTIMEBASECONFIG == STD_ON)
    || (StbM_IsReservedTimeBaseOfTimeBaseConfig(timeBaseId))
#  endif
    || (customerId >= StbM_GetSizeOfTimeNotificationCustomerConfig())
#  if (StbM_GetSizeOfTimeBaseConfig() > 1u)
    || (StbM_GetTimeBaseConfigIdxOfTimeNotificationCustomerConfig(customerId) != timeBaseId)
#  endif
    )
  {
    errorId = STBM_E_PARAM;
  }
  /* #30 Check expireTime against NULL_PTR */
  else if (expireTime == NULL_PTR)
  {
    errorId = STBM_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    SchM_Enter_StbM_STBM_EXCLUSIVE_AREA_0();
    retVal = StbM_CalculateExpireTime(timeBaseId, customerId, expireTime); /* SBSW_STBM_FUNCTIONCALL_LOCALPTR */
    SchM_Exit_StbM_STBM_EXCLUSIVE_AREA_0();
  }

  /* ----- Development Error Report --------------------------------------- */
# if (STBM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != STBM_E_NO_ERROR)
  {
    StbM_ReportError(STBM_SID_START_TIMER, errorId);
  }
# else
  STBM_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# endif

  return retVal;
} /* StbM_StartTimer() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (STBM_GLOBALTIMEMASTEROFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_UpdateGlobalTime()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, STBM_CODE) StbM_UpdateGlobalTime(StbM_SynchronizedTimeBaseType timeBaseId, P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA) timeStamp, P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA) userData)     /* PRQA S 1330 */ /* MD_StbM_Rule8.3_1330 */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = STBM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (STBM_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;
  /* #10 Check if component is initialized */
  if (!StbM_IsInitialized())
  {
    errorId = STBM_E_NOT_INITIALIZED;
  }
  /* #20 Check timeBaseId parameter validity against configuration */
  else if ((timeBaseId >= StbM_GetSizeOfTimeBaseConfig())
#  if (STBM_RESERVEDTIMEBASEOFTIMEBASECONFIG == STD_ON)
    || (StbM_IsReservedTimeBaseOfTimeBaseConfig(timeBaseId))
#  endif
    )
  {
    errorId = STBM_E_PARAM;
  }
  /* #30 Check timeStamp parameter for NULL pointer */
  else if (timeStamp == NULL_PTR)
  {
    errorId = STBM_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #40 Set new global time */
    retVal = StbM_SetNewGlobalTime(timeBaseId, timeStamp, userData); /* SBSW_STBM_FUNCTIONCALL_PARAMPTR */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (STBM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != STBM_E_NO_ERROR)
  {
    StbM_ReportError(STBM_SID_UPDATE_GLOBAL_TIME, errorId);
  }
# else
  STBM_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# endif
  return retVal;
} /* StbM_UpdateGlobalTime() */
#endif

#if (STBM_GLOBALTIMEMASTEROFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_TriggerTimeTransmission()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, STBM_CODE) StbM_TriggerTimeTransmission(StbM_SynchronizedTimeBaseType timeBaseId)   /* PRQA S 1330 */ /* MD_StbM_Rule8.3_1330 */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = STBM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (STBM_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;
  /* #10 Check if component is initialized */
  if (!StbM_IsInitialized())
  {
    errorId = STBM_E_NOT_INITIALIZED;
  }
  /* #20 Check timeBaseId parameter validity against configuration */
  else if ((timeBaseId >= StbM_GetSizeOfTimeBaseConfig())
#  if (STBM_PURELOCALTIMEBASEOFTIMEBASECONFIG == STD_ON)
    || (StbM_IsPureLocalTimeBaseOfTimeBaseConfig(timeBaseId))
#  endif
#  if (STBM_RESERVEDTIMEBASEOFTIMEBASECONFIG == STD_ON)
    || (StbM_IsReservedTimeBaseOfTimeBaseConfig(timeBaseId))
#  endif
    )
  {
    errorId = STBM_E_PARAM;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Increment update counter of time base */
    StbM_IncrementTimeBaseUpdateCounter(timeBaseId);
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (STBM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != STBM_E_NO_ERROR)
  {
    StbM_ReportError(STBM_SID_TRIGGER_TIME_TRANSMISSION, errorId);
  }
# else
  STBM_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# endif
  return retVal;
} /* StbM_TriggerTimeTransmission() */
#endif

/**********************************************************************************************************************
 *  StbM_GetTimeBaseUpdateCounter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(uint8, STBM_CODE) StbM_GetTimeBaseUpdateCounter(StbM_SynchronizedTimeBaseType timeBaseId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 retVal;
  uint8 errorId = STBM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (STBM_DEV_ERROR_DETECT == STD_ON)
  retVal = 0u;
  /* #10 Check if component is initialized */
  if (!StbM_IsInitialized())
  {
    errorId = STBM_E_NOT_INITIALIZED;
  }
  /* #20 Check timeBaseId parameter validity against configuration */
  else if ((timeBaseId >= StbM_GetSizeOfTimeBaseConfig())
# if (STBM_PURELOCALTIMEBASEOFTIMEBASECONFIG == STD_ON)
    || (StbM_IsPureLocalTimeBaseOfTimeBaseConfig(timeBaseId))
# endif
# if (STBM_RESERVEDTIMEBASEOFTIMEBASECONFIG == STD_ON)
    || (StbM_IsReservedTimeBaseOfTimeBaseConfig(timeBaseId))
# endif
    )
  {
    errorId = STBM_E_PARAM;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Set return value to update counter of given time base */
    retVal = StbM_GetUpdateCounterOfTimeBaseState(timeBaseId);
  }

  /* ----- Development Error Report --------------------------------------- */
#if (STBM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != STBM_E_NO_ERROR)
  {
    StbM_ReportError(STBM_SID_GET_TIME_BASE_UPDATE_COUNTER, errorId);
  }
#else
  STBM_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#endif

  return retVal;
} /* StbM_GetTimeBaseUpdateCounter() */

#if (STBM_TIMESLAVEOFTIMEBASECONFIG == STD_ON)
/**********************************************************************************************************************
 *  StbM_GetTimeLeap()
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
FUNC(Std_ReturnType, STBM_CODE) StbM_GetTimeLeap(StbM_SynchronizedTimeBaseType timeBaseId, P2VAR(StbM_TimeDiffType, AUTOMATIC, STBM_APPL_VAR) timeJump) /* PRQA S 1330 */ /* MD_StbM_Rule8.3_1330 */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = STBM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (STBM_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;
  /* #10 Check if component is initialized */
  if (!StbM_IsInitialized())
  {
    errorId = STBM_E_NOT_INITIALIZED;
  }
  /* #20 Check timeBaseId parameter validity against configuration */
  else if ((timeBaseId >= StbM_GetSizeOfTimeBaseConfig())
#  if (STBM_PURELOCALTIMEBASEOFTIMEBASECONFIG == STD_ON)
    || (StbM_IsPureLocalTimeBaseOfTimeBaseConfig(timeBaseId))
#  endif
#  if (STBM_RESERVEDTIMEBASEOFTIMEBASECONFIG == STD_ON)
    || (StbM_IsReservedTimeBaseOfTimeBaseConfig(timeBaseId))
#  endif
    )
  {
    errorId = STBM_E_PARAM;
  }
  /* #30 Check timeJump parameter for NULL pointer */
  else if (timeJump == NULL_PTR)
  {
    errorId = STBM_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #40 If the last time leap fits into the range, set timeJump to the corresponding value */
    if (((StbM_GetTimeLeapFutureBit(StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus) == 0u) && (StbM_GetTimeLeapPastBit(StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus) == 0u))
      || (StbM_GetLastTimeLeapValueOfTimeBaseState(timeBaseId) > STBM_TIMELEAP_MAX_FUTURE) || (StbM_GetLastTimeLeapValueOfTimeBaseState(timeBaseId) < STBM_TIMELEAP_MAX_PAST))
    {
      retVal = E_NOT_OK;
    }
    else
    {
      *timeJump = (sint32) StbM_GetLastTimeLeapValueOfTimeBaseState(timeBaseId); /* SBSW_STBM_ACCESS_PARAMPTR */
      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (STBM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != STBM_E_NO_ERROR)
  {
    StbM_ReportError(STBM_SID_GET_TIMELEAP, errorId);
  }
# else
  STBM_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
# endif
  return retVal;
} /* StbM_GetTimeLeap() */
#endif

/**********************************************************************************************************************
 *  StbM_GetTimeBaseStatus()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, STBM_CODE) StbM_GetTimeBaseStatus(StbM_SynchronizedTimeBaseType timeBaseId, P2VAR(StbM_TimeBaseStatusType, AUTOMATIC, STBM_APPL_VAR) syncTimeBaseStatus, P2VAR(StbM_TimeBaseStatusType, AUTOMATIC, STBM_APPL_VAR) offsetTimeBaseStatus) /* PRQA S 1330 */ /* MD_StbM_Rule8.3_1330 */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = STBM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (STBM_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;
  /* #10 Check if component is initialized */
  if (!StbM_IsInitialized())
  {
    errorId = STBM_E_NOT_INITIALIZED;
  }
  /* #20 Check timeBaseId parameter validity against configuration */
  else if ((timeBaseId >= StbM_GetSizeOfTimeBaseConfig())
# if (STBM_RESERVEDTIMEBASEOFTIMEBASECONFIG == STD_ON)
    || (StbM_IsReservedTimeBaseOfTimeBaseConfig(timeBaseId))
# endif
    )
  {
    errorId = STBM_E_PARAM;
  }
  /* #30 Check syncTimeBaseStatus and offsetTimeBaseStatus parameter for NULL pointer */
  else if ((syncTimeBaseStatus == NULL_PTR) || (offsetTimeBaseStatus == NULL_PTR))
  {
    errorId = STBM_E_PARAM_POINTER;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #40 Set parameters depending on the kind of time base */
#if (STBM_TIMEBASECONFIGIDXOFTIMEBASECONFIG == STD_ON)
    if (StbM_IsOffsetTimeBase(timeBaseId))
    {
      *syncTimeBaseStatus = StbM_GetTimeStampOfTimeBaseState(StbM_GetTimeBaseConfigIdxOfTimeBaseConfig(timeBaseId)).timeBaseStatus; /* SBSW_STBM_ACCESS_PARAMPTR */
      *offsetTimeBaseStatus = StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus; /* SBSW_STBM_ACCESS_PARAMPTR */
    }
    else
#endif
    {
      *syncTimeBaseStatus = StbM_GetTimeStampOfTimeBaseState(timeBaseId).timeBaseStatus; /* SBSW_STBM_ACCESS_PARAMPTR */
      *offsetTimeBaseStatus = 0x00; /* SBSW_STBM_ACCESS_PARAMPTR */
    }

    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
#if (STBM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != STBM_E_NO_ERROR)
  {
    StbM_ReportError(STBM_SID_GET_TIME_BASE_STATUS, errorId);
  }
#else
  STBM_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 2983 */ /* MD_MSR_DummyStmt */
#endif
  return retVal;
} /* StbM_GetTimeBaseStatus() */

#define STBM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */   /* MD_MSR_MemMap */

/* Justification for module-specific MISRA deviations:
 MD_StbM_Rule8.3_1330:  MISRA rule: 8.3
     Reason:     The RTE Generator uses default names for parameter identifiers of port defined arguments of service modules.
                 Therefore the parameter identifiers in the function declaration differs from those of the implementation of the BSW module.
     Risk:       No functional risk.
     Prevention: Not required.
 MD_StbM_Rule10.8:  MISRA rule: 10.8
     Reason:     StbM internally uses the types required for its calculations.
                 Therefore casts to types of specified external data are needed.
     Risk:       Conversion errors might occur for unfitting data or be introduced by later code changes.
     Prevention: Covered by tests and code review.
*/

/* Safe BSW assumptions:
  Indirections:
  TimeBaseConfig->StatusNotificationCustomerConfig  1:0..1
  TimeBaseConfig->TimeNotificationCustomerConfig    1:0..N
  TimeBaseConfig->SyncRecordTableHead               1:0..1
  TimeBaseConfig->SyncRecordTableBlock              1:0..N
  TimeBaseConfig->OffsetRecordTableHead             1:0..1
  TimeBaseConfig->OffsetRecordTableBlock            1:0..N
  TimeBaseConfig->SyncTimeRecordBlockCallbacks      1:0..1
  TimeBaseConfig->OffsetTimeRecordBlockCallbacks    1:0..1
  TimeBaseConfig->TimeBaseConfig                    1:0..1
  TimeBaseConfig->GptChannelActive                  1:0..1
  TimeBaseConfig->RateMeasurementStorage            1:0..N

  TimeNotificationCustomerConfig->TimeBaseConfig    1:1

  Size Constraints:
    TimeBaseConfig <-> TimeBaseState
    StatusNotificationCustomerConfig <-> StatusNotificationEvent
    TimeNotificationCustomerConfig <-> NotificationCustomerStates
  These assumptions are modelled in ComStackLib
*/

/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_STBM_ACCESS_TIMEBASESTATE
  \DESCRIPTION Write access to TimeBaseState or referencing from TimeBaseState using ComStackLib.
               The TimeBaseIndex is given as parameter on external interfaces or by iterating over the timebases.
  \COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

  \ID SBSW_STBM_ACCESS_STATUSNOTIFICATIONEVENT
  \DESCRIPTION Write access to StatusNotificationEvent or referencing from StatusNotificationEvent using ComStackLib. The index comes from the caller calculated by indirection of the TimeBaseConfig.
               The TimeBaseIndex is given as parameter on external interfaces or by iterating over the timebases.
  \COUNTERMEASURE \N Qualified use-case CSL02 and CSL03 of ComStackLib

  \ID SBSW_STBM_ACCESS_NOTIFICATIONCUSTOMERSTATE
  \DESCRIPTION Write access to NotificationCustomerStates or referencing from NotificationCustomerStates using ComStackLib. The index comes from the caller calculated by indirection of the TimeBaseConfig or on external interfaces.
               The TimeBaseIndex is given as parameter on external interfaces or by iterating over the timebases.
  \COUNTERMEASURE \N Qualified use-case CSL02 and CSL03 of ComStackLib

  \ID SBSW_STBM_ACCESS_GPTCHANNELACTIVE
  \DESCRIPTION Write access to GptChannelActive or referencing from GptChannelActive using ComStackLib. The index comes from the caller calculated by indirection of the TimeBaseConfig.
               The TimeBaseIndex is given as parameter on external interfaces or by iterating over the timebases.
  \COUNTERMEASURE \N Qualified use-case CSL02 and CSL03 of ComStackLib

  \ID SBSW_STBM_ACCESS_SYNCRECORDTABLEHEAD
  \DESCRIPTION Write access to SyncRecordTableHead or referencing from SyncRecordTableHead using ComStackLib. The index comes from the caller calculated by indirection of the TimeBaseConfig.
               The TimeBaseIndex is given as parameter on external interfaces or by iterating over the timebases.
  \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

  \ID SBSW_STBM_ACCESS_OFFSETRECORDTABLEHEAD
  \DESCRIPTION Write access to OffsetRecordTableHead or referencing from OffsetRecordTableHead using ComStackLib. The index comes from the caller calculated by indirection of the TimeBaseConfig.
               The TimeBaseIndex is given as parameter on external interfaces or by iterating over the timebases.
  \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

  \ID SBSW_STBM_ACCESS_SYNCRECORDTABLEBLOCK
  \DESCRIPTION Write access to SyncRecordTableBlock or referencing from SyncRecordTableBlock using ComStackLib. The index comes from the caller calculated by indirection of the TimeBaseConfig.
               The TimeBaseIndex is given as parameter on external interfaces or by iterating over the timebases.
  \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

  \ID SBSW_STBM_ACCESS_OFFSETRECORDTABLEBLOCK
  \DESCRIPTION Write access to OffsetRecordTableBlock or referencing from OffsetRecordTableBlock using ComStackLib. The index comes from the caller calculated by indirection of the TimeBaseConfig.
               The TimeBaseIndex is given as parameter on external interfaces or by iterating over the timebases.
  \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

  \ID SBSW_STBM_ACCESS_RATEMEASUREMENTSTORAGE
  \DESCRIPTION Write access to RateMeasurementStorage or referencing from RateMeasurementStorage using ComStackLib. The index comes from the caller calculated by indirection of the TimeBaseConfig.
               The TimeBaseIndex is given as parameter on external interfaces or by iterating over the timebases.
  \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

  \ID SBSW_STBM_ACCESS_RATEMEASUREMENTSTORAGE_RUNTIMEIDX
  \DESCRIPTION Write access to RateMeasurementStorage or referencing from RateMeasurementStorage using ComStackLib. The current RateMeasurementStorage index comes from the TimeBaseState and is calculated by indirection of the TimeBaseConfig.
               The TimeBaseIndex is given as parameter on external interfaces or by iterating over the timebases.
               The current RateMeasurementStorage index stored in TimeBaseState is initialized to be in the correct range in StbM_Init(). It is checked to be in this range before being used, incremented or reset in StbM_RateCorrectionMeasurement().
  \COUNTERMEASURE \N Qualified use-case CSL02 and CSL03 of ComStackLib

  \ID SBSW_STBM_ACCESS_SYNCRECORDTABLEBLOCK_RUNTIMEIDX
  \DESCRIPTION Write access to SyncRecordTableBlock or referencing from SyncRecordTableBlock using ComStackLib. The current RecordTableBlock index comes from the TimeBaseState and is calculated by indirection of the TimeBaseConfig.
               The TimeBaseIndex is given as parameter on external interfaces or by iterating over the timebases.
               The current RecordTableBlock index stored in TimeBaseState is initialized to be in the correct range in StbM_Init(). It is reset to be in this range in StbM_MainFunction().
               It is checked to be in this range before being reset, used and incremented in StbM_BusSetGlobalTime().
  \COUNTERMEASURE \N Qualified use-case CSL02 and CSL03 of ComStackLib

  \ID SBSW_STBM_ACCESS_OFFSETRECORDTABLEBLOCK_RUNTIMEIDX
  \DESCRIPTION Write access to OffsetRecordTableBlock or referencing from OffsetRecordTableBlock using ComStackLib. The current RecordTableBlock index comes from the TimeBaseState and is calculated by indirection of the TimeBaseConfig.
               The TimeBaseIndex is given as parameter on external interfaces or by iterating over the timebases.
               The current RecordTableBlock index stored in TimeBaseState is initialized to be in the correct range in StbM_Init(). It is reset to be in this range in StbM_MainFunction().
               It is checked to be in this range before being reset, used and incremented in StbM_BusSetGlobalTime().
  \COUNTERMEASURE \N Qualified use-case CSL02 and CSL03 of ComStackLib

  \ID SBSW_STBM_ACCESS_TRIGGEREDCUSTOMERSTATE
  \DESCRIPTION Write access to TriggeredCustomerState or referencing from TriggeredCustomerState using ComStackLib.
               The CustomerIndex is given by iterating over the triggered customers.
  \COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

  \ID SBSW_STBM_FUNCTIONCALL_LOCALPTR
  \DESCRIPTION Call of a function with pointer parameters where the pointers are pointing to local (stack) objects.
  \COUNTERMEASURE \N Compiler ensures validity of the pointers.

  \ID SBSW_STBM_FUNCTIONCALL_PARAMPTR
  \DESCRIPTION Forwarding the pointer that was given as parameter, without modifying anything.
  \COUNTERMEASURE \N Caller ensures validity of the pointers.

  \ID SBSW_STBM_FUNCTIONCALL_CONSTPTR
  \DESCRIPTION Call of a function with pointer parameters where the pointers are const and the parameter is only read.
  \COUNTERMEASURE \N Compiler ensures validity of the pointers.

  \ID SBSW_STBM_FUNCTIONCALL_LOCALPTR_PARAMPTR
  \DESCRIPTION Call of a function with pointer parameters where the pointers are pointing to local (stack) objects and forward pointers that were given as parameter, without modifying anything.
  \COUNTERMEASURE \N Compiler and caller ensure validity of the pointers.

  \ID SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR
  \DESCRIPTION Call of a function with pointer parameters where the pointers are const and the parameter is only read or pointing to local (stack) objects.
  \COUNTERMEASURE \N Compiler ensures validity of the pointers.

  \ID SBSW_STBM_FUNCTIONCALL_CONSTPTR_PARAMPTR
  \DESCRIPTION Call of a function with pointer parameters where the pointers are const and the parameter is only read or forwarded without modifying anything.
  \COUNTERMEASURE \N Compiler and caller ensure validity of the pointers.

  \ID SBSW_STBM_FUNCTIONCALL_CONSTPTR_LOCALPTR_PARAMPTR
  \DESCRIPTION Call of a function with pointer parameters where the pointers are const and the parameter is only read or pointing to local (stack) objects or forwarded without modifying anything.
  \COUNTERMEASURE \N Compiler and caller ensure validity of the pointers.

  \ID SBSW_STBM_FUNCTIONCALL_CONSTPTR_GLOBALPTR
  \DESCRIPTION Call of a function with pointer parameters where the pointers are const and the parameter is only read or pointing to an element modelled using ComStackLib.
               The customer index comes from the caller calculated by indirection of the TimeBaseConfig or on external interfaces.
               The TimeBaseIndex is given as parameter on external interfaces or by iterating over the time bases.
  \COUNTERMEASURE \N Compiler and qualified use-case CSL02 and CSL03 of ComStackLib ensure validity of the pointers.

  \ID SBSW_STBM_FCTPTRCALL_NOTIFICATION
  \DESCRIPTION Function pointer stored in table modelled with ComStackLib is called.
               The index is given by iterating over the customers.
               Qualified use-case CSL03 of ComStackLib and compiler ensures type of the pointer from parameters.
  \COUNTERMEASURE \R Pointer is checked against NULL pointer at runtime.

  \ID SBSW_STBM_FCTPTRCALL_RECORDTABLE
  \DESCRIPTION Function pointer stored in table modelled with ComStackLib is called. 
               The index is calculated by indirection of the TimeBaseConfig.
               The TimeBaseIndex is given as parameter on external interfaces or by iterating over the timebases.
               Qualified use-case CSL03 of ComStackLib and compiler ensures type of the pointer from parameters.
  \COUNTERMEASURE \R Pointer is checked against NULL pointer at runtime.

  \ID SBSW_STBM_ACCESS_PARAMPTR
  \DESCRIPTION The function writes to the object referenced by the parameter.
  \COUNTERMEASURE \N The caller ensures that the pointers passed to the parameter is valid.

  \ID SBSW_STBM_ACCESS_CSL_VAR
  \DESCRIPTION A ComStackLib generated variable is accessed.
  \COUNTERMEASURE \N The variable is written using a generated macro of the CSL. It immediately dereferences the variables address without pointer arithmetic.

SBSW_JUSTIFICATION_END */

/* COV_JUSTIFICATION_BEGIN

  \ID COV_STBM_DEV_ERROR_DETECT_TX_tx_tf
    \ACCEPT TX tx tf
    \REASON SafeBSW requires DEV_ERROR_DETECT to be always on. A MSSV Plugin enforces this configuration.

  \ID COV_STBM_MSR_COMPATIBILITY
    \ACCEPT TX
    \REASON [COV_MSR_COMPATIBILITY]

  \ID COV_STBM_SILENT_TX
    \ACCEPT TX
    \REASON This check ensures that no incorrect memory is overwritten. This should never happen in normal configurations.

  \ID COV_STBM_RETURN_CHECK
    \ACCEPT XF
    \REASON This check is fully covered in at least one equivalent pre-compile configuration.

  \ID COV_STBM_RATECORRECTION
    \ACCEPT TX tx xx xx
    \ACCEPT TX tf tx xx
    \ACCEPT TF xf tf tf
    \REASON See COV_STBM_RETURN_CHECK.

  \ID COV_STBM_TIMELEAP_ACTIVE
    \ACCEPT TX xf tx
    \ACCEPT TF xf tf
    \ACCEPT TF tf xf
    \ACCEPT TX tx xx
    \REASON See COV_STBM_RETURN_CHECK.

  \ID COV_STBM_TIMELEAP_DIFFERENCE
    \ACCEPT TF tf tf tf tf tf xf
    \ACCEPT TF tf tf tf tf tf tx
    \REASON See COV_STBM_RETURN_CHECK.

  \ID COV_STBM_TIMELEAP_POSITIVE
    \ACCEPT TF tf tf tx tf
    \ACCEPT TF tf xf tf tx
    \REASON See COV_STBM_RETURN_CHECK.

  \ID COV_STBM_TIMELEAP_NEGATIVE
    \ACCEPT TF tf tf tx tf
    \ACCEPT TF tf xf tf tx
    \ACCEPT TF tf tf tf tx
    \REASON See COV_STBM_RETURN_CHECK.

  \ID COV_STBM_TIMELEAP_COUNT
    \ACCEPT TX
    \REASON See COV_STBM_RETURN_CHECK.

  \ID COV_STBM_TIMEGATEWAY
    \ACCEPT TF xf tf
    \REASON See COV_STBM_RETURN_CHECK.

  \ID COV_STBM_ETH_TSYN_RETVAL
    \ACCEPT TX
    \REASON Return value is always TRUE, if no Ethernet local time is used.

  \ID COV_STBM_RATECORRECTIONMEASUREMENTDURATION
    \ACCEPT TX
    \REASON Condition is always true, if rate correction is configured.

  \ID COV_STBM_ALL_OFFSET_TIMEBASES_WITH_STATUSNOTIFICATIONS
    \ACCEPT TX
    \REASON Condition is always true, if all offset time bases have status notification configured.

  \ID COV_STBM_ALL_OFFSET_TIMEBASES_WITH_TIMENOTIFICATIONCUSTOMER
    \ACCEPT TX
    \REASON Return value is always TRUE, if all Offset Time Bases have Time Notification Customers configured.

  \ID COV_STBM_ALL_TIMEBASES_WITH_TIMENOTIFICATIONCUSTOMER
    \ACCEPT TX
    \REASON Condition is always true, if all time bases have time notification customer configured.

  \ID COV_STBM_ALL_TIMEBASES_WITH_SYNCLOSSTIMEOUT_STATUSNOTIFICATIONS
    \ACCEPT TX
    \REASON Condition is always true, if all time bases with sync loss timeout have also status notification configured.

  \ID COV_STBM_ALL_SYNCTIMEBASES_WITH_TIMERECORDING_GPTLOCALTIME
    \ACCEPT TX
    \ACCEPT XF
    \REASON Condition is always true, if all synchronized time bases with time recording configured have also Gpt configured local time, or condition always false, if no synchronized time base has Gpt configured as local time.

  \ID COV_STBM_ALL_TIMENOTIFICATIONCUSTOMER_MASTERSYNCTIMEBASE
    \ACCEPT TX
    \ACCEPT XX
    \REASON Return value is always TRUE, if all Time Notification Customers are configured at Synchronized Time Bases in the role master.

  \ID COV_STBM_NO_GPT_CHANNEL_USED_MULTIPLE_TIMES
    \ACCEPT TX
    \REASON Condition always true, if no Gpt channel is used as local time by more than one Time Base.

  \ID COV_STBM_ALL_GATEWAYS_NO_SYNCLOSSTIMEOUT
    \ACCEPT TX
    \REASON Condition always true, if time gatesways have no sync loss timeout configured.

COV_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  END OF FILE: StbM.c
 *********************************************************************************************************************/
