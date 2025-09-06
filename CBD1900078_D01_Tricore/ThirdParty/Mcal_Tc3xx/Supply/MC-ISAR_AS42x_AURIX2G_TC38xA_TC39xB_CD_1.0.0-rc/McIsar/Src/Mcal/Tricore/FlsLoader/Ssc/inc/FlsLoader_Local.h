/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2018)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : FlsLoader_Local.h                                          **
**                                                                            **
**  VERSION      : 8.0.0                                                      **
**                                                                            **
**  DATE         : 2018-08-27                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Flsloader Driver local header definition file              **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={DFF49573-F622-433e-9EC1-2882D1109AF2}] [/cover]*/
#ifndef FLSLOADER_LOCAL_H
#define FLSLOADER_LOCAL_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "FlsLoader.h"

/* Inclusion of Flash header file */
#include "IfxDmu_reg.h"
#include "IfxScu_reg.h"

/* Conditional Inclusion of Developement Error Tracer File */
#if  ( FLSLOADER_DEV_ERROR_DETECT == STD_ON )
#include "Det.h"
#endif
/*******************************************************************************
**                      Global Macro Definitions                             **
*******************************************************************************/

/* Sector Nos */
#define FLSLOADER_INV     ((uint32)(0xFFFFU))
#define FLSLOADER_TRUE    ((uint32)(0x1U))
#define FLSLOADER_FALSE   ((uint32)(0x0U))

#define FLSLOADER_MOD_256               ((uint32)(0x000000FFU))
#define FLSLOADER_MOD_32                ((uint32)(0x0000001FU))
#define FLSLOADER_PFLASH_MASK           ((uint32)(0x0000000FU))
/* Confirmation code is 0x57B5327F */
#define FLSLOADER_CONFIRMATION_CODE     ((uint32)(0x57B5327FU))

/* The following macros are used in the command cycles. */
#define FLSLOADER_CYCLE_5554           ((uint32)(0x00005554U))
#define FLSLOADER_CYCLE_55F0           ((uint32)(0x000055F0U))
#define FLSLOADER_CYCLE_55F4           ((uint32)(0x000055F4U))
#define FLSLOADER_CYCLE_AA50           ((uint32)(0x0000AA50U))
#define FLSLOADER_CYCLE_AA58           ((uint32)(0x0000AA58U))
#define FLSLOADER_CYCLE_AAA8           ((uint32)(0x0000AAA8U))
#define FLSLOADER_CYCLE_553C           ((uint32)(0x0000553CU))
#define FLSLOADER_MASK_HIGHER4_NIBBLES ((uint32)(0xFFFF0000U))
#define FLSLOADER_POSITION_0           ((uint32)0U)

/* The following values are used in the command cycles */
#define FLSLOADER_VALUE_F0             ((uint32)(0x000000F0U))
#define FLSLOADER_VALUE_00             ((uint32)(0x00000000U))
#define FLSLOADER_VALUE_A0             ((uint32)(0x000000A0U))
#define FLSLOADER_VALUE_AA             ((uint32)(0x000000AAU))
#define FLSLOADER_VALUE_A6             ((uint32)(0x000000A6U))
#define FLSLOADER_VALUE_80             ((uint32)(0x00000080U))
#define FLSLOADER_VALUE_50             ((uint32)(0x00000050U))
#define FLSLOADER_VALUE_FA             ((uint32)(0x000000FAU))

#define FLSLOADER_CMD_ADDRESS          ((uint32)(0xAF000000U))

#define FLSLOADER_START_SEC_WRITEERASE_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "Flsloader_MemMap.h"

/*Private functions for command execution*/

/*******************************************************************************
** Syntax           : LOCAL_INLINE void FlsLoader_lCommandCycle(              **
**                                           const uint32 CommandCycle,\      **
**                                                         const uint32 Data) **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : CommandCycle: DMU command cycle ID to be executed       **
**                    Data: Data for the command cycle ID mentioned           **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : This function executes the DMU command cycle for the    **
**                    given identifier                                        **
*******************************************************************************/
LOCAL_INLINE void FlsLoader_lCommandCycle(const uint32 CommandCycle,\
                                                             const uint32 Data)
{
    uint32 CmdAddr;
    volatile uint32 *TargetAddr;
    
    CmdAddr = FLSLOADER_CMD_ADDRESS + CommandCycle;
    
    /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from integer to pointer is
    * necessary to calculate DMU CSI address and store commands*/
    /* MISRA2012_RULE_11_4_JUSTIFICATION: cast from integer to pointer is
    * necessary to calculate DMU CSI address and store commands*/
    TargetAddr = (volatile uint32 *) CmdAddr;

    *(TargetAddr) = Data;
    
    /*Wait until above command sequence is completed*/
    DSYNC();
    
    return;
}

#define FLSLOADER_STOP_SEC_WRITEERASE_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "Flsloader_MemMap.h"

#define FLSLOADER_NUM_2                 (2U)
#define FLSLOADER_NUM_1                 (1U)

#define FLSLOADER_CMDCYCLE_TIMEOUT      (25U)

/*Time in ns for Flash write*/
/*Max time for one PF burst  = 530000ns*/
#define FLSLOADER_MAX_TIME_PER_PF_BURST        (530000U)
#define FLSLOADER_MAX_TIME_PER_DF_BURST        (140000U)
#define FLSLOADER_MAX_TIME_PER_PF_PAGE         (115000U)
#define FLSLOADER_MAX_TIME_PER_DF_PAGE         (75000U)

/*Time in ns for Flash erase*/
#define FLSLOADER_MAX_TIME_PER_PF_ERASE        (500000000U)
#define FLSLOADER_MAX_TIME_PER_DF_ERASE        (1500000000U)

#define FLSLOADER_OVERFLOW_MASK         ((uint32)(0xFFFFFFFFU))

/*Maximum value of "Length" input for DF Erase*/
#define FLSLOADER_MAX_ERASE_SECTOR_DF   ((uint32)256)
/*Maximum value of "Length" input for PF Erase*/
#define FLSLOADER_MAX_ERASE_SECTOR_PF   ((uint32)192)
/*Maximum value of "Length" input for PF Write = 16MB*/
#define FLSLOADER_MAX_PF_WRITE_DATA_LENGTH (0x1000000U)
/*Maximum value of "Length" input for PF Write = 1MB*/
#define FLSLOADER_MAX_DF_WRITE_DATA_LENGTH (0x100000U)

#define FLSLOADER_BIT_POSITION_31       ((uint32)31)

#define FLSLOADER_BIT_SET               (1U)
#define FLSLOADER_BIT_RESET             (0U)
#define FLSLOADER_PFLASH_BANK0          ((uint32)(0x00000000U))
#define FLSLOADER_DFLASH_BANK0          ((uint32)(0x00000010U))

#define FLSLOADER_SHIFT_BY_20           ((uint32)(20U))
#define FLSLOADER_SHIFT_BY_15           (15U)
#define FLSLOADER_SHIFT_BY_8            (8U)
#define FLSLOADER_SHIFT_BY_5            ((uint32)(5U))
#define FLSLOADER_SHIFT_BY_3            (3U)

#define FLSLOADER_DECREMENT_BY_32       ((uint32)(32U))
#define FLSLOADER_REG_FIRST_BIT         ((uint32)(0U))
#define FLSLOADER_REG_32_BIT            ((uint32)(32U))

#define FLSLOADER_UCB_FLASH_CONFIRMED  ((uint32)2U)
#define FLSLOADER_UCB_FLASH_ERRORED    ((uint32)3U)

/* Protection,sequence and operation errors */
#define FLSLOADER_PROER_SQER_OPER_ERROR (0x00000007U)
#define FLSLOADER_OPER_ERROR            (0x00000001U)
#define FLSLOADER_SQER_ERROR            (0x00000002U)
#define FLSLOADER_PROER_ERROR           (0x00000004U)
#define FLSLOADER_INITIALIZED           (1U)
#define FLSLOADER_NUM_4                 (4U)
#define FLSLOADER_NUM_6                 (6U)

#define FLSLOADER_PFPAGE_BIT_MASK       (0x200000U)
#define FLSLOADER_DFPAGE_BIT_MASK       (0x100000U)
#define FLSLOADER_PROG_BIT_MASK         (0x1U)
#define FLSLOADER_ERASE_BIT_MASK        (0x2U)
#define FLSLOADER_MASK_3_BITS           (0x7U)
/*******************************************************************************
**                      Global function like Macros                          **
*******************************************************************************/
/*
Function Like Macro:FlsLoader_lCheckFlashType
macro to get wheter its PFLASH or DFLASH
Input Parameters:
Address: Address of the flash
*/
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used for code
 * simplification and readability*/
#define FlsLoader_lCheckFlashType(Address) \
          ((0xAFU ==(((Address) >> 24U) & 0xFFU)) ? 1U : 0U )

/*
Function Like Macro:FlsLoader_lLoadPage
Loads the page in Write API
Input Parameters: Address
*/
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used for code
 * simplification and readability*/
#define FlsLoader_lLoadPage(Address)   \
          (((Address) & FLSLOADER_MASK_HIGHER4_NIBBLES) + FLSLOADER_CYCLE_55F0)

/*******************************************************************************
**                      Global Variable Definitions                          **
*******************************************************************************/
#if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)
#define FLSLOADER_START_SEC_VAR_CLEARED_QM_LOCAL_8
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "Flsloader_MemMap.h"

extern uint8 FlsLoader_InitStatus;

#define FLSLOADER_STOP_SEC_VAR_CLEARED_QM_LOCAL_8
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "Flsloader_MemMap.h"
#endif

#if (FLSLOADER_CALLOUT_FUNC == STD_ON)
/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the FLSLOADER module*/
#define FLSLOADER_START_SEC_CONST_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Flsloader_MemMap.h"

/* MISRA2012_RULE_8_9_JUSTIFICATION:FlsLoader_PFlashSectorCount is exported 
from FlsLoader_Cfg.c*/
extern const FlsLoader_CallOutFunc FlsLoader_CallOutPtr;

/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the FLSLOADER module*/
#define FLSLOADER_STOP_SEC_CONST_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Flsloader_MemMap.h"
#endif
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
#define FLSLOADER_START_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "Flsloader_MemMap.h"


/*******************************************************************************
**                      Global Inline Function Declarations                   **
*******************************************************************************/
#if (FLSLOADER_LOCK_UNLOCK_API == STD_ON)
extern FlsLoader_ReturnType FlsLoader_lLock(void);
#endif

extern FlsLoader_ReturnType FlsLoader_lCheckOTPWOP(void);

#define FLSLOADER_STOP_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "Flsloader_MemMap.h"

#define FLSLOADER_START_SEC_WRITEERASE_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "Flsloader_MemMap.h"

extern FlsLoader_ReturnType FlsLoader_lBusyCheck(\
                                    const uint32 TimeoutTicks);

extern FlsLoader_ReturnType FlsLoader_lCheckBitSet(\
                                   const volatile void* const RegAddress, \
                                                   const uint32 BitPosMask);

#if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)

extern FlsLoader_ReturnType FlsLoader_lWriteDetCheck(
                                     const FlsLoader_LengthType Length,
                                     const FlsLoader_AddressType TargetAddress);
                                     
FlsLoader_ReturnType FlsLoader_lEraseDetCheck(
                                const FlsLoader_LengthType Length,
                                const FlsLoader_AddressType TargetAddress);

#endif /*#if (FLSLOADER_DEV_ERROR_DETECT == STD_ON)*/

extern uint32 FlsLoader_lGetFlashType(
                        const FlsLoader_AddressType TargetAddress);

extern FlsLoader_ReturnType FlsLoader_lProtSeqOperErrorCheck(void);

#if (FLSLOADER_ENABLE_LOCKCHECK == STD_ON)

extern FlsLoader_ReturnType FlsLoader_lFlashLockCheck(
                        const FlsLoader_AddressType TargetAddress,
                        const uint32 FlashType,
                        const FlsLoader_LengthType Length);

extern FlsLoader_ReturnType FlsLoader_lEraseLockCheck(
                    const FlsLoader_AddressType TargetAddress,
                    const uint32 FlashType,
                    const FlsLoader_LengthType Length);

#endif /*#if (FLSLOADER_ENABLE_LOCKCHECK == STD_ON)*/

#define FLSLOADER_STOP_SEC_WRITEERASE_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Flsloader_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "Flsloader_MemMap.h"
#endif /* End of FLSLOADER_LOCAL_H */
