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
 *              File: Os_Hal_Cfg.h
 *   Generation Time: 2023-11-13 15:45:45
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


                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */

#ifndef OS_HAL_CFG_H
# define OS_HAL_CFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! HAL configuration major version identification. */
# define OS_CFG_HAL_MAJOR_VERSION                (2u)

/*! HAL configuration minor version identification. */
# define OS_CFG_HAL_MINOR_VERSION                (16u)

/* ISR core and level definitions */
# define OS_ISR_COUNTERISR_SYSTEMTIMER_CORE0_CORE      (0)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_CORE0_LEVEL     (12)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_CORE1_CORE      (1)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_CORE1_LEVEL     (20)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_CORE2_CORE      (2)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_CORE2_LEVEL     (20)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_CORE3_CORE      (3)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_CORE3_LEVEL     (20)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_CORE4_CORE      (4)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_CORE4_LEVEL     (20)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_CORE5_CORE      (6)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_CORE5_LEVEL     (21)
# define OS_ISR_XSIGNALISR_OSCORE0_CORE      (0)
# define OS_ISR_XSIGNALISR_OSCORE0_LEVEL     (18)
# define OS_ISR_XSIGNALISR_OSCORE1_CORE      (1)
# define OS_ISR_XSIGNALISR_OSCORE1_LEVEL     (18)
# define OS_ISR_XSIGNALISR_OSCORE2_CORE      (2)
# define OS_ISR_XSIGNALISR_OSCORE2_LEVEL     (18)
# define OS_ISR_XSIGNALISR_OSCORE3_CORE      (3)
# define OS_ISR_XSIGNALISR_OSCORE3_LEVEL     (18)
# define OS_ISR_XSIGNALISR_OSCORE4_CORE      (4)
# define OS_ISR_XSIGNALISR_OSCORE4_LEVEL     (18)
# define OS_ISR_XSIGNALISR_OSCORE5_CORE      (6)
# define OS_ISR_XSIGNALISR_OSCORE5_LEVEL     (18)

/* Hardware counter timing macros */

/* Counter timing macros and constants: SystemTimer_Core0 */
# define OSMAXALLOWEDVALUE_SystemTimer_Core0     (1073741823uL) /* 0x3FFFFFFFuL */
# define OSMINCYCLE_SystemTimer_Core0            (1uL)
# define OSTICKSPERBASE_SystemTimer_Core0        (1uL)
# define OSTICKDURATION_SystemTimer_Core0        (10uL)

/* OSEK compatibility for the system timer. */
# define OSMAXALLOWEDVALUE     (OSMAXALLOWEDVALUE_SystemTimer_Core0)
# define OSMINCYCLE            (OSMINCYCLE_SystemTimer_Core0)
# define OSTICKSPERBASE        (OSTICKSPERBASE_SystemTimer_Core0)
# define OSTICKDURATION        (OSTICKDURATION_SystemTimer_Core0)

/*! Macro OS_NS2TICKS_SystemTimer_Core0 was approximated with a deviation of 0.0ppm. */
# define OS_NS2TICKS_SystemTimer_Core0(x)     ( (TickType) (((((uint32)(x)) * 1) + 5) / 10) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2NS_SystemTimer_Core0 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2NS_SystemTimer_Core0(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 10) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_US2TICKS_SystemTimer_Core0 was approximated with a deviation of 0.0ppm. */
# define OS_US2TICKS_SystemTimer_Core0(x)     ( (TickType) (((((uint32)(x)) * 100) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2US_SystemTimer_Core0 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2US_SystemTimer_Core0(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50) / 100) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_MS2TICKS_SystemTimer_Core0 was approximated with a deviation of 0.0ppm. */
# define OS_MS2TICKS_SystemTimer_Core0(x)     ( (TickType) (((((uint32)(x)) * 100000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2MS_SystemTimer_Core0 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2MS_SystemTimer_Core0(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000) / 100000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_SEC2TICKS_SystemTimer_Core0 was approximated with a deviation of 0.0ppm. */
# define OS_SEC2TICKS_SystemTimer_Core0(x)     ( (TickType) (((((uint32)(x)) * 100000000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2SEC_SystemTimer_Core0 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2SEC_SystemTimer_Core0(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000000) / 100000000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */


/* Counter timing macros and constants: SystemTimer_Core1 */
# define OSMAXALLOWEDVALUE_SystemTimer_Core1     (1073741823uL) /* 0x3FFFFFFFuL */
# define OSMINCYCLE_SystemTimer_Core1            (1uL)
# define OSTICKSPERBASE_SystemTimer_Core1        (1uL)
# define OSTICKDURATION_SystemTimer_Core1        (10uL)

/*! Macro OS_NS2TICKS_SystemTimer_Core1 was approximated with a deviation of 0.0ppm. */
# define OS_NS2TICKS_SystemTimer_Core1(x)     ( (TickType) (((((uint32)(x)) * 1) + 5) / 10) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2NS_SystemTimer_Core1 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2NS_SystemTimer_Core1(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 10) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_US2TICKS_SystemTimer_Core1 was approximated with a deviation of 0.0ppm. */
# define OS_US2TICKS_SystemTimer_Core1(x)     ( (TickType) (((((uint32)(x)) * 100) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2US_SystemTimer_Core1 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2US_SystemTimer_Core1(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50) / 100) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_MS2TICKS_SystemTimer_Core1 was approximated with a deviation of 0.0ppm. */
# define OS_MS2TICKS_SystemTimer_Core1(x)     ( (TickType) (((((uint32)(x)) * 100000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2MS_SystemTimer_Core1 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2MS_SystemTimer_Core1(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000) / 100000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_SEC2TICKS_SystemTimer_Core1 was approximated with a deviation of 0.0ppm. */
# define OS_SEC2TICKS_SystemTimer_Core1(x)     ( (TickType) (((((uint32)(x)) * 100000000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2SEC_SystemTimer_Core1 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2SEC_SystemTimer_Core1(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000000) / 100000000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */


/* Counter timing macros and constants: SystemTimer_Core2 */
# define OSMAXALLOWEDVALUE_SystemTimer_Core2     (1073741823uL) /* 0x3FFFFFFFuL */
# define OSMINCYCLE_SystemTimer_Core2            (1uL)
# define OSTICKSPERBASE_SystemTimer_Core2        (1uL)
# define OSTICKDURATION_SystemTimer_Core2        (10uL)

/*! Macro OS_NS2TICKS_SystemTimer_Core2 was approximated with a deviation of 0.0ppm. */
# define OS_NS2TICKS_SystemTimer_Core2(x)     ( (TickType) (((((uint32)(x)) * 1) + 5) / 10) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2NS_SystemTimer_Core2 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2NS_SystemTimer_Core2(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 10) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_US2TICKS_SystemTimer_Core2 was approximated with a deviation of 0.0ppm. */
# define OS_US2TICKS_SystemTimer_Core2(x)     ( (TickType) (((((uint32)(x)) * 100) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2US_SystemTimer_Core2 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2US_SystemTimer_Core2(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50) / 100) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_MS2TICKS_SystemTimer_Core2 was approximated with a deviation of 0.0ppm. */
# define OS_MS2TICKS_SystemTimer_Core2(x)     ( (TickType) (((((uint32)(x)) * 100000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2MS_SystemTimer_Core2 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2MS_SystemTimer_Core2(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000) / 100000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_SEC2TICKS_SystemTimer_Core2 was approximated with a deviation of 0.0ppm. */
# define OS_SEC2TICKS_SystemTimer_Core2(x)     ( (TickType) (((((uint32)(x)) * 100000000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2SEC_SystemTimer_Core2 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2SEC_SystemTimer_Core2(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000000) / 100000000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */


/* Counter timing macros and constants: SystemTimer_Core3 */
# define OSMAXALLOWEDVALUE_SystemTimer_Core3     (1073741823uL) /* 0x3FFFFFFFuL */
# define OSMINCYCLE_SystemTimer_Core3            (1uL)
# define OSTICKSPERBASE_SystemTimer_Core3        (1uL)
# define OSTICKDURATION_SystemTimer_Core3        (10uL)

/*! Macro OS_NS2TICKS_SystemTimer_Core3 was approximated with a deviation of 0.0ppm. */
# define OS_NS2TICKS_SystemTimer_Core3(x)     ( (TickType) (((((uint32)(x)) * 1) + 5) / 10) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2NS_SystemTimer_Core3 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2NS_SystemTimer_Core3(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 10) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_US2TICKS_SystemTimer_Core3 was approximated with a deviation of 0.0ppm. */
# define OS_US2TICKS_SystemTimer_Core3(x)     ( (TickType) (((((uint32)(x)) * 100) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2US_SystemTimer_Core3 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2US_SystemTimer_Core3(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50) / 100) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_MS2TICKS_SystemTimer_Core3 was approximated with a deviation of 0.0ppm. */
# define OS_MS2TICKS_SystemTimer_Core3(x)     ( (TickType) (((((uint32)(x)) * 100000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2MS_SystemTimer_Core3 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2MS_SystemTimer_Core3(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000) / 100000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_SEC2TICKS_SystemTimer_Core3 was approximated with a deviation of 0.0ppm. */
# define OS_SEC2TICKS_SystemTimer_Core3(x)     ( (TickType) (((((uint32)(x)) * 100000000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2SEC_SystemTimer_Core3 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2SEC_SystemTimer_Core3(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000000) / 100000000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */


/* Counter timing macros and constants: SystemTimer_Core4 */
# define OSMAXALLOWEDVALUE_SystemTimer_Core4     (1073741823uL) /* 0x3FFFFFFFuL */
# define OSMINCYCLE_SystemTimer_Core4            (1uL)
# define OSTICKSPERBASE_SystemTimer_Core4        (1uL)
# define OSTICKDURATION_SystemTimer_Core4        (10uL)

/*! Macro OS_NS2TICKS_SystemTimer_Core4 was approximated with a deviation of 0.0ppm. */
# define OS_NS2TICKS_SystemTimer_Core4(x)     ( (TickType) (((((uint32)(x)) * 1) + 5) / 10) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2NS_SystemTimer_Core4 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2NS_SystemTimer_Core4(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 10) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_US2TICKS_SystemTimer_Core4 was approximated with a deviation of 0.0ppm. */
# define OS_US2TICKS_SystemTimer_Core4(x)     ( (TickType) (((((uint32)(x)) * 100) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2US_SystemTimer_Core4 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2US_SystemTimer_Core4(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50) / 100) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_MS2TICKS_SystemTimer_Core4 was approximated with a deviation of 0.0ppm. */
# define OS_MS2TICKS_SystemTimer_Core4(x)     ( (TickType) (((((uint32)(x)) * 100000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2MS_SystemTimer_Core4 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2MS_SystemTimer_Core4(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000) / 100000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_SEC2TICKS_SystemTimer_Core4 was approximated with a deviation of 0.0ppm. */
# define OS_SEC2TICKS_SystemTimer_Core4(x)     ( (TickType) (((((uint32)(x)) * 100000000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2SEC_SystemTimer_Core4 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2SEC_SystemTimer_Core4(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000000) / 100000000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */


/* Counter timing macros and constants: SystemTimer_Core5 */
# define OSMAXALLOWEDVALUE_SystemTimer_Core5     (1073741823uL) /* 0x3FFFFFFFuL */
# define OSMINCYCLE_SystemTimer_Core5            (1uL)
# define OSTICKSPERBASE_SystemTimer_Core5        (1uL)
# define OSTICKDURATION_SystemTimer_Core5        (10uL)

/*! Macro OS_NS2TICKS_SystemTimer_Core5 was approximated with a deviation of 0.0ppm. */
# define OS_NS2TICKS_SystemTimer_Core5(x)     ( (TickType) (((((uint32)(x)) * 1) + 5) / 10) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2NS_SystemTimer_Core5 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2NS_SystemTimer_Core5(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 10) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_US2TICKS_SystemTimer_Core5 was approximated with a deviation of 0.0ppm. */
# define OS_US2TICKS_SystemTimer_Core5(x)     ( (TickType) (((((uint32)(x)) * 100) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2US_SystemTimer_Core5 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2US_SystemTimer_Core5(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50) / 100) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_MS2TICKS_SystemTimer_Core5 was approximated with a deviation of 0.0ppm. */
# define OS_MS2TICKS_SystemTimer_Core5(x)     ( (TickType) (((((uint32)(x)) * 100000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2MS_SystemTimer_Core5 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2MS_SystemTimer_Core5(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000) / 100000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_SEC2TICKS_SystemTimer_Core5 was approximated with a deviation of 0.0ppm. */
# define OS_SEC2TICKS_SystemTimer_Core5(x)     ( (TickType) (((((uint32)(x)) * 100000000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2SEC_SystemTimer_Core5 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2SEC_SystemTimer_Core5(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000000) / 100000000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */




/* CAT0 and CAT1 ISR core and level definitions */



/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


#endif /* OS_HAL_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Hal_Cfg.h
 *********************************************************************************************************************/
