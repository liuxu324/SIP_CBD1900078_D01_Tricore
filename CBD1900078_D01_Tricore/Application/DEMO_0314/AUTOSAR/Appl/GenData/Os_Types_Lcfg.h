/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: Os
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: Aurix 2G/TC397 B-Step
 *    License Scope : The usage is restricted to CBD1900078_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Os_Types_Lcfg.h
 *   Generation Time: 2024-01-30 19:05:43
 *           Project: TC397START - Version 1.0
 *          Delivery: CBD1900078_D01
 *      Tool Version: DaVinci Configurator (beta) 5.18.42 SP2
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 ! BETA VERSION                                                                                                       !
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 ! This version of DaVinci Configurator Pro and/or the related Basic Software Package is BETA software.               !
 ! BETA Software is basically operable, but not sufficiently tested, verified and/or qualified for use in series      !
 ! production and/or in vehicles operating on public or non-public roads.                                             !
 ! In particular, without limitation, BETA Software may cause unpredictable ECU behavior, may not provide all         !
 ! functions necessary for use in series production and/or may not comply with quality requirements which are         !
 ! necessary according to the state of the art. BETA Software must not be used in series production.                  !
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
**********************************************************************************************************************/

#ifndef OS_TYPES_LCFG_H
# define OS_TYPES_LCFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */

/* Os kernel module dependencies */

/* Os hal dependencies */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* OS-Application identifiers. */
#define SystemApplication_OsCore0 SystemApplication_OsCore0
#define SystemApplication_OsCore1 SystemApplication_OsCore1
#define SystemApplication_OsCore2 SystemApplication_OsCore2
#define SystemApplication_OsCore3 SystemApplication_OsCore3
#define SystemApplication_OsCore4 SystemApplication_OsCore4
#define SystemApplication_OsCore5 SystemApplication_OsCore5

/* Trusted function identifiers. */

/* Non-trusted function identifiers. */

/* Fast trusted function identifiers. */

/* Task identifiers. */
#define ApplTask_Core0 ApplTask_Core0
#define ApplTask_Core1 ApplTask_Core1
#define ApplTask_Core2 ApplTask_Core2
#define ApplTask_Core3 ApplTask_Core3
#define ApplTask_Core4 ApplTask_Core4
#define ApplTask_Core5 ApplTask_Core5
#define IdleTask_OsCore0 IdleTask_OsCore0
#define IdleTask_OsCore1 IdleTask_OsCore1
#define IdleTask_OsCore2 IdleTask_OsCore2
#define IdleTask_OsCore3 IdleTask_OsCore3
#define IdleTask_OsCore4 IdleTask_OsCore4
#define IdleTask_OsCore5 IdleTask_OsCore5
#define OsTask_Init_Core0 OsTask_Init_Core0
#define OsTask_Init_Core1 OsTask_Init_Core1
#define OsTask_Init_Core2 OsTask_Init_Core2
#define OsTask_Init_Core3 OsTask_Init_Core3
#define OsTask_Init_Core4 OsTask_Init_Core4
#define OsTask_Init_Core5 OsTask_Init_Core5
#define SchMTask_Core0 SchMTask_Core0
#define SchMTask_Core1 SchMTask_Core1
#define SchMTask_Core2 SchMTask_Core2
#define SchMTask_Core3 SchMTask_Core3
#define SchMTask_Core4 SchMTask_Core4
#define SchMTask_Core5 SchMTask_Core5

/* Category 2 ISR identifiers. */
#define CounterIsr_SystemTimer_Core0 CounterIsr_SystemTimer_Core0
#define CounterIsr_SystemTimer_Core1 CounterIsr_SystemTimer_Core1
#define CounterIsr_SystemTimer_Core2 CounterIsr_SystemTimer_Core2
#define CounterIsr_SystemTimer_Core3 CounterIsr_SystemTimer_Core3
#define CounterIsr_SystemTimer_Core4 CounterIsr_SystemTimer_Core4
#define CounterIsr_SystemTimer_Core5 CounterIsr_SystemTimer_Core5
#define XSignalIsr_OsCore0 XSignalIsr_OsCore0
#define XSignalIsr_OsCore1 XSignalIsr_OsCore1
#define XSignalIsr_OsCore2 XSignalIsr_OsCore2
#define XSignalIsr_OsCore3 XSignalIsr_OsCore3
#define XSignalIsr_OsCore4 XSignalIsr_OsCore4
#define XSignalIsr_OsCore5 XSignalIsr_OsCore5

/* Alarm identifiers. */
#define Rte_Al_TE1_EcuM_EcuM_MainFunction Rte_Al_TE1_EcuM_EcuM_MainFunction
#define Rte_Al_TE2_EcuM_EcuM_MainFunction Rte_Al_TE2_EcuM_EcuM_MainFunction
#define Rte_Al_TE2_SchMTask_Core0_0_10ms Rte_Al_TE2_SchMTask_Core0_0_10ms
#define Rte_Al_TE2_SchMTask_Core0_0_20ms Rte_Al_TE2_SchMTask_Core0_0_20ms
#define Rte_Al_TE3_EcuM_EcuM_MainFunction Rte_Al_TE3_EcuM_EcuM_MainFunction
#define Rte_Al_TE5_EcuM_EcuM_MainFunction Rte_Al_TE5_EcuM_EcuM_MainFunction
#define Rte_Al_TE6_EcuM_EcuM_MainFunction Rte_Al_TE6_EcuM_EcuM_MainFunction
#define Rte_Al_TE_CanTp_CanTp_MainFunction Rte_Al_TE_CanTp_CanTp_MainFunction
#define Rte_Al_TE_CtLed0Type_Led0BlinkRunnable Rte_Al_TE_CtLed0Type_Led0BlinkRunnable
#define Rte_Al_TE_CtLed1Type_Led1BlinkRunnable Rte_Al_TE_CtLed1Type_Led1BlinkRunnable
#define Rte_Al_TE_CtLed2Type_Led2BlinkRunnable Rte_Al_TE_CtLed2Type_Led2BlinkRunnable
#define Rte_Al_TE_CtLed3Type_Led3BlinkRunnable Rte_Al_TE_CtLed3Type_Led3BlinkRunnable
#define Rte_Al_TE_CtLed4Type_Led4BlinkRunnable Rte_Al_TE_CtLed4Type_Led4BlinkRunnable
#define Rte_Al_TE_CtLed5Type_Led5BlinkRunnable Rte_Al_TE_CtLed5Type_Led5BlinkRunnable

/* Counter identifiers. */
#define SystemTimer_Core0 SystemTimer_Core0
#define SystemTimer_Core1 SystemTimer_Core1
#define SystemTimer_Core2 SystemTimer_Core2
#define SystemTimer_Core3 SystemTimer_Core3
#define SystemTimer_Core4 SystemTimer_Core4
#define SystemTimer_Core5 SystemTimer_Core5

/* ScheduleTable identifiers. */

/* Resource identifiers. */
#define RES_SCHEDULER_OsCore0 RES_SCHEDULER_OsCore0
#define RES_SCHEDULER_OsCore1 RES_SCHEDULER_OsCore1
#define RES_SCHEDULER_OsCore2 RES_SCHEDULER_OsCore2
#define RES_SCHEDULER_OsCore3 RES_SCHEDULER_OsCore3
#define RES_SCHEDULER_OsCore4 RES_SCHEDULER_OsCore4
#define RES_SCHEDULER_OsCore5 RES_SCHEDULER_OsCore5

/* Spinlock identifiers. */
#define Rte_Spinlock_sig_RearInteriorLight_omsg_Transmit_oCAN00_49a633c1_Tx Rte_Spinlock_sig_RearInteriorLight_omsg_Transmit_oCAN00_49a633c1_Tx

/* Peripheral identifiers. */

/* Barrier identifiers. */

/* Trace thread identifiers (Tasks and ISRs inclusive system objects). */

/* Trace spinlock identifiers (All spinlocks inclusive system objects). */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! OS-Application identifiers. */
typedef enum
{
  SystemApplication_OsCore0 = 0, /* 0x00000001 */  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SystemApplication_OsCore1 = 1, /* 0x00000002 */  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SystemApplication_OsCore2 = 2, /* 0x00000004 */  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SystemApplication_OsCore3 = 3, /* 0x00000008 */  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SystemApplication_OsCore4 = 4, /* 0x00000010 */  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SystemApplication_OsCore5 = 5, /* 0x00000020 */  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OS_APPID_COUNT = 6,
  INVALID_OSAPPLICATION = OS_APPID_COUNT
} ApplicationType;

/*! Trusted function identifiers. */
typedef enum
{
  OS_TRUSTEDFUNCTIONID_COUNT = 0
} TrustedFunctionIndexType;

/*! Non-trusted function identifiers. */
typedef enum
{
  OS_NONTRUSTEDFUNCTIONID_COUNT = 0
} Os_NonTrustedFunctionIndexType;

/*! Fast trusted function identifiers. */
typedef enum
{
  OS_FASTTRUSTEDFUNCTIONID_COUNT = 0
} Os_FastTrustedFunctionIndexType;

/*! Task identifiers. */
typedef enum
{
  ApplTask_Core0 = 0,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  ApplTask_Core1 = 1,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  ApplTask_Core2 = 2,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  ApplTask_Core3 = 3,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  ApplTask_Core4 = 4,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  ApplTask_Core5 = 5,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  IdleTask_OsCore0 = 6,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  IdleTask_OsCore1 = 7,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  IdleTask_OsCore2 = 8,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  IdleTask_OsCore3 = 9,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  IdleTask_OsCore4 = 10,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  IdleTask_OsCore5 = 11,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Init_Core0 = 12,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Init_Core1 = 13,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Init_Core2 = 14,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Init_Core3 = 15,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Init_Core4 = 16,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_Init_Core5 = 17,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SchMTask_Core0 = 18,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SchMTask_Core1 = 19,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SchMTask_Core2 = 20,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SchMTask_Core3 = 21,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SchMTask_Core4 = 22,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SchMTask_Core5 = 23,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OS_TASKID_COUNT = 24,
  INVALID_TASK = OS_TASKID_COUNT
} TaskType;

/*! Category 2 ISR identifiers. */
typedef enum
{
  CounterIsr_SystemTimer_Core0 = 0,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  CounterIsr_SystemTimer_Core1 = 1,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  CounterIsr_SystemTimer_Core2 = 2,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  CounterIsr_SystemTimer_Core3 = 3,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  CounterIsr_SystemTimer_Core4 = 4,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  CounterIsr_SystemTimer_Core5 = 5,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  XSignalIsr_OsCore0 = 6,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  XSignalIsr_OsCore1 = 7,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  XSignalIsr_OsCore2 = 8,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  XSignalIsr_OsCore3 = 9,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  XSignalIsr_OsCore4 = 10,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  XSignalIsr_OsCore5 = 11,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OS_ISRID_COUNT = 12,
  INVALID_ISR = OS_ISRID_COUNT
} ISRType;

/*! Alarm identifiers. */
typedef enum
{
  Rte_Al_TE1_EcuM_EcuM_MainFunction = 0,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE2_EcuM_EcuM_MainFunction = 1,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE2_SchMTask_Core0_0_10ms = 2,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE2_SchMTask_Core0_0_20ms = 3,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE3_EcuM_EcuM_MainFunction = 4,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE5_EcuM_EcuM_MainFunction = 5,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE6_EcuM_EcuM_MainFunction = 6,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE_CanTp_CanTp_MainFunction = 7,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE_CtLed0Type_Led0BlinkRunnable = 8,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE_CtLed1Type_Led1BlinkRunnable = 9,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE_CtLed2Type_Led2BlinkRunnable = 10,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE_CtLed3Type_Led3BlinkRunnable = 11,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE_CtLed4Type_Led4BlinkRunnable = 12,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE_CtLed5Type_Led5BlinkRunnable = 13,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OS_ALARMID_COUNT = 14
} AlarmType;

/*! Counter identifiers. */
typedef enum
{
  SystemTimer_Core0 = 0,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SystemTimer_Core1 = 1,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SystemTimer_Core2 = 2,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SystemTimer_Core3 = 3,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SystemTimer_Core4 = 4,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  SystemTimer_Core5 = 5,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OS_COUNTERID_COUNT = 6
} CounterType;

/*! ScheduleTable identifiers. */
typedef enum
{
  OS_SCHTID_COUNT = 0
} ScheduleTableType;

/*! Resource identifiers. */
typedef enum
{
  RES_SCHEDULER_OsCore0 = 0,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  RES_SCHEDULER_OsCore1 = 1,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  RES_SCHEDULER_OsCore2 = 2,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  RES_SCHEDULER_OsCore3 = 3,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  RES_SCHEDULER_OsCore4 = 4,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  RES_SCHEDULER_OsCore5 = 5,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OS_RESOURCEID_COUNT = 6
} ResourceType;

/*! Spinlock identifiers. */
typedef enum
{
  Rte_Spinlock_sig_RearInteriorLight_omsg_Transmit_oCAN00_49a633c1_Tx = 0,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OS_SPINLOCKID_COUNT = 1,
  INVALID_SPINLOCK = OS_SPINLOCKID_COUNT
} SpinlockIdType;

/*! Peripheral identifiers. */
typedef enum
{
  OS_PERIPHERALID_COUNT = 0
} Os_PeripheralIdType;

/*! Barrier identifiers. */
typedef enum
{
  OS_BARRIERID_COUNT = 0
} Os_BarrierIdType;

/*! Trace thread identifiers (Tasks and ISRs inclusive system objects). */
typedef enum
{
  OS_TRACE_THREADID_COUNT = 0,
  OS_TRACE_INVALID_THREAD = OS_TRACE_THREADID_COUNT + 1
} Os_TraceThreadIdType;

/*! Trace spinlock identifiers (All spinlocks inclusive system objects). */
typedef enum
{
  OS_TRACE_NUMBER_OF_CONFIGURED_SPINLOCKS = OS_SPINLOCKID_COUNT,
  OS_TRACE_NUMBER_OF_ALL_SPINLOCKS = OS_SPINLOCKID_COUNT + 0u,  /* PRQA S 4521 */ /* MD_Os_Rule10.1_4521 */
  OS_TRACE_INVALID_SPINLOCK = OS_TRACE_NUMBER_OF_ALL_SPINLOCKS + 1
} Os_TraceSpinlockIdType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


#endif /* OS_TYPES_LCFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Types_Lcfg.h
 *********************************************************************************************************************/
