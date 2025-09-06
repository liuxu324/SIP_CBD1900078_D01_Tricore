/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Os_Cfg.h
 *        Config:  TC397START.dpa
 *   ECU-Project:  MyECU
 *
 *     Generator:  MICROSAR RTE Generator Version 4.19.0
 *                 RTE Core Version 1.19.0
 *       License:  CBD1900078
 *
 *   Description:  Os definitions
 *********************************************************************************************************************/

#ifndef _OS_CFG_H_
# define _OS_CFG_H_

/* Os definitions */

/* Tasks */
# define ApplTask_Core0 (0U)
# define ApplTask_Core1 (1U)
# define ApplTask_Core2 (2U)
# define ApplTask_Core3 (3U)
# define ApplTask_Core4 (4U)
# define ApplTask_Core5 (5U)
# define SchMTask_Core0 (6U)
# define SchMTask_Core1 (7U)
# define SchMTask_Core2 (8U)
# define SchMTask_Core3 (9U)
# define SchMTask_Core4 (10U)
# define SchMTask_Core5 (11U)

/* Alarms */
# define Rte_Al_TE_CtLed0Type_Led0BlinkRunnable (0U)
# define Rte_Al_TE_CtLed1Type_Led1BlinkRunnable (1U)
# define Rte_Al_TE_CtLed2Type_Led2BlinkRunnable (2U)
# define Rte_Al_TE_CtLed3Type_Led3BlinkRunnable (3U)
# define Rte_Al_TE_CtLed4Type_Led4BlinkRunnable (4U)
# define Rte_Al_TE_CtLed5Type_Led5BlinkRunnable (5U)
# define Rte_Al_TE2_SchMTask_Core0_0_10ms (6U)
# define Rte_Al_TE2_SchMTask_Core0_0_20ms (7U)
# define Rte_Al_TE_CanTp_CanTp_MainFunction (8U)
# define Rte_Al_TE1_EcuM_EcuM_MainFunction (9U)
# define Rte_Al_TE2_EcuM_EcuM_MainFunction (10U)
# define Rte_Al_TE3_EcuM_EcuM_MainFunction (11U)
# define Rte_Al_TE5_EcuM_EcuM_MainFunction (12U)
# define Rte_Al_TE6_EcuM_EcuM_MainFunction (13U)

/* Events */
# define Rte_Ev_Cyclic2_SchMTask_Core0_0_10ms (0x01)
# define Rte_Ev_Cyclic2_SchMTask_Core0_0_20ms (0x04)
# define Rte_Ev_Run_CanTp_CanTp_MainFunction (0x02)

/* Spinlocks */
# define Rte_Spinlock_sig_RearInteriorLight_omsg_Transmit_oCAN00_49a633c1_Tx (0U)

/* Resources */

/* ScheduleTables */

/* Cores */
# define OS_CORE_ID_0 (0U)
# define OS_CORE_ID_1 (1U)
# define OS_CORE_ID_2 (2U)
# define OS_CORE_ID_3 (3U)
# define OS_CORE_ID_4 (4U)
# define OS_CORE_ID_5 (5U)
# include "usrostyp.h"

/* Trusted Functions */


#endif /* _OS_CFG_H_ */
