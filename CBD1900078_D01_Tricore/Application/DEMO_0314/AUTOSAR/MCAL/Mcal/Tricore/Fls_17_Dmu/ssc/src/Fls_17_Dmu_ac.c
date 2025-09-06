/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2018)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Fls_17_Dmu_ac.c                                             **
**                                                                           **
**  VERSION :  7.0.0                                                         **
**                                                                           **
**  DATE       :  2018-09-24                                                 **
**                                                                           **
**  VARIANT   : Variant PB                                                   **
**                                                                           **
**  PLATFORM  : Infineon AURIX2G                                             **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION  : This file contains command sequences of Flash driver      **
**                                                                           **
**  SPECIFICATION(S) : Specification of FLS Driver, AUTOSAR Release 4.2.2    **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: No                                      **
**                                                                           **
******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* [cover parentID={4D611C8D-52AA-42d4-92A1-B4280952EE29}][/cover] */

/* Inclusion of Tasking sfr file */
#include "IfxDmu_reg.h"

/* Inclusion of Flash header file */
#include "Fls_17_Dmu.h"

/* Include Flash Module access code File */
#include "Fls_17_Dmu_ac.h"

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
/* size of data loaded into page buffer at a time - 8bytes */
#define FLS_LOAD_PAGE_SIZE   (8U)

/* number of words per FLS_LOAD_PAGE_SIZE */
#define FLS_17_TWO_WORDS     (2U)

/* Hardare Timeout for Command cycle*/
#define FLS_17_DMU_CMDCYCLE_TIMEOUT            (25U)

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

LOCAL_INLINE boolean Fls_lCmdCycleTimeout05(uint32 InnerCount);

LOCAL_INLINE boolean Fls_lCmdCycleTimeout06(uint32 InnerCount);

LOCAL_INLINE void Cycle5554(volatile uint32 Address, uint32 Data);

LOCAL_INLINE void CycleAAA8(volatile uint32 Address, uint32 Data);

LOCAL_INLINE void CycleAA50(volatile uint32 Address, uint32 Data);

LOCAL_INLINE void CycleAA58(volatile uint32 Address, uint32 Data);

LOCAL_INLINE void EnterPageMode(volatile uint32 Address, uint32 Data);

LOCAL_INLINE void LoadPage(volatile uint32 Address,
                                     const Fls_17_Dmu_AddressType* DataPtr);

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Fls_17_Dmu_MemMap.h"
extern const Fls_17_Dmu_ConfigType *Fls_ConfigPtr;

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
 #include "Fls_17_Dmu_MemMap.h"
/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*******************************************************************************
** Syntax : void Fls_WriteCmdCycles( volatile uint32 StartAddress,            **
**                                   uint32 PageAddress,                      **
**                             const Fls_17_Dmu_AddressType* ProgramDataPtr   **
**                                   uint8 WriteMode                          **
**                                )                                           **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : StartAddress,PageAddress, ProgramDataPtr and WriteMode   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : This routine contains flash write command cycles             **
*******************************************************************************/
#define FLS_17_DMU_START_SEC_CODE_ASIL_B_LOCAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* CYCLOMATIC_Fls_WriteCmdCycles_JUSTIFICATION: This Function is the command
 sequence for WRITE operation and has to check for many error conditions(as
per HW manual) which is leading to many conditional blocks. Breaking it into
local function will break the continuity of the command sequence*/
#include "Fls_17_Dmu_MemMap.h"
void Fls_WriteCmdCycles( volatile uint32 StartAddress,
                         uint32 PageAddress, 
                         const Fls_17_Dmu_AddressType* ProgramDataPtr,
                         uint8 WriteMode
                       )
{
  volatile uint32 InnerCount;
  const Fls_17_Dmu_AddressType* pdata;
  Fls_17_Dmu_StateType* StatePtr;
  uint8 FlsSqerProtErr;
  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  StatePtr->FlsTimeoutErr = 0U;
  FlsSqerProtErr = 0U;
  pdata = ProgramDataPtr;
   
  /* Enter the Page Mode */
  EnterPageMode(StartAddress, VALUE_5D);

  InnerCount = 0U;
    /*MISRA2012_RULE_11_4_JUSTIFICATION: Conversion between pointer to 
      object and integer type is permitted for special function registers*/
    /*MISRA2012_RULE_13_5_JUSTIFICATION: Volatile qualifier is needed for 
    proper functioning of this opertaion.*/
while((DMU_HF_STATUS.B.DFPAGE != 1U) && \
                         (InnerCount < FLS_17_DMU_CMDCYCLE_TIMEOUT) && \
        ((DMU_HF_ERRSR.B.SQER != 1U) && (DMU_HF_ERRSR.B.PROER != 1U)))
  {
    InnerCount++;
  }
/*MISRA2012_RULE_13_5_JUSTIFICATION: This warning is due to the volatile
 qualifier in the SFRs, which is permitted.*/
if((DMU_HF_ERRSR.B.SQER != 0U) || (DMU_HF_ERRSR.B.PROER != 0U))
  {
      FlsSqerProtErr = (uint8)1;
  }
  /* Check for command cycle Timeout */
  if ((boolean)TRUE == Fls_lCmdCycleTimeout05(InnerCount))
  {
    StatePtr->FlsTimeoutErr = FLS_17_DMU_WRITE;
  }
  else if (FlsSqerProtErr == (uint8)0)
  /* Check DFPAGE bit was SET */
  {
    if(WriteMode == FLS_17_DMU_BURST_WRITE)
    {
      InnerCount = (FLS_17_DMU_BURST_PAGE_SIZE / FLS_LOAD_PAGE_SIZE);
    }
    else
    {
      InnerCount = (FLS_17_DMU_PAGE_SIZE / FLS_LOAD_PAGE_SIZE);
    }
    while(InnerCount != 0U)
    {
      /* Load the data */
      LoadPage(StartAddress, pdata);

      /* Page assembly buffer pointer gets incremented automatically */
      /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than 
      array indexing used for buffer address calculation and for subsequent 
      traversal.The access range is within the valid range.*/
      pdata += FLS_17_TWO_WORDS;
      InnerCount--;
    }   
          
    /* cycle 1 */
    CycleAA50(StartAddress, PageAddress);
    /* cycle 2 */
    CycleAA58(StartAddress, VALUE_00);
 
    /* cycle 3 */
    CycleAAA8(StartAddress, VALUE_A0);

    /* cycle 4 */
    if(WriteMode == FLS_17_DMU_BURST_WRITE)
    {
      CycleAAA8(StartAddress, VALUE_A6);
    }
    else
    {
      CycleAAA8(StartAddress, VALUE_AA);
    }
     
    InnerCount = 0U;
    /*MISRA2012_RULE_11_4_JUSTIFICATION: Conversion between pointer to 
      object and integer type is permitted for special function registers*/
    /*MISRA2012_RULE_13_5_JUSTIFICATION: Volatile qualifier is needed for 
    proper functioning of this opertaion.*/
    while((DMU_HF_OPERATION.B.PROG != 1U) &&    \
                  (InnerCount < FLS_17_DMU_CMDCYCLE_TIMEOUT) && \
             ((DMU_HF_ERRSR.B.SQER != 1U) && (DMU_HF_ERRSR.B.PROER != 1U)))
    {
      InnerCount++;
    }

    if ((boolean)TRUE == Fls_lCmdCycleTimeout06(InnerCount))
    {
      StatePtr->FlsTimeoutErr = FLS_17_DMU_WRITE;
    }
  }

  else
  {
      /*dummy else*/
  }
}
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */


/*******************************************************************************
** Syntax : void Fls_EraseCmdCycles(volatile uint32 EraseAddress)             **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : StartAddress                                             **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : This routine contains flash Erase command cycles             **
*******************************************************************************/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
void Fls_EraseCmdCycles(volatile uint32 EraseAddress)
{ 
  volatile uint32 InnerCount;
  volatile uint32 StartAddress;
  volatile uint8 EraseNumSec;
  Fls_17_Dmu_StateType* StatePtr;

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  StatePtr->FlsTimeoutErr = 0U;
  EraseNumSec  = StatePtr->FlsEraseNumSecPerCmd;
  StartAddress = FLS_17_DMU_BASE_ADDRESS;
  /* cycle 1 */
  CycleAA50(StartAddress, EraseAddress);
  /* cycle 2 */
  CycleAA58(StartAddress, EraseNumSec);
  /* cycle 3 */
  CycleAAA8(StartAddress, VALUE_80);
  /* cycle 4 */
  CycleAAA8(StartAddress, VALUE_50);

  InnerCount = 0U;
    /*MISRA2012_RULE_11_4_JUSTIFICATION: Conversion between pointer to 
   object and integer type is permitted for special function registers*/
   /*MISRA2012_RULE_13_5_JUSTIFICATION: Volatile qualifier is needed for
    proper functioning of this opertaion.*/
  while((DMU_HF_OPERATION.B.ERASE != 1U) &&   \
                (InnerCount < FLS_17_DMU_CMDCYCLE_TIMEOUT) && \
            ((DMU_HF_ERRSR.B.SQER != 1U) && (DMU_HF_ERRSR.B.PROER != 1U)))
  {
    InnerCount++;
  }
  
  /*return Error there is a Timeout has happened */
  if ((boolean)TRUE == Fls_lCmdCycleTimeout05(InnerCount))
  {
    StatePtr->FlsTimeoutErr = FLS_17_DMU_ERASE;
  }
}
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */

/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/*******************************************************************************
** Syntax : void Fls_CallEraseCommand(volatile uint32 PhysicalAddress)        **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : PhysicalAddress                                          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : This routine calls flash Erase command cycles                **
*******************************************************************************/
void Fls_CallEraseCommand(volatile uint32 PhysicalAddress)
{
  Fls_EraseCmdCycles(PhysicalAddress);
  
}

/*******************************************************************************
** Syntax : void Fls_CallWriteCommand(volatile uint32 PhysicalAddress, 
                          const Fls_17_Dmu_StateType *s_ptr,
                          uint8 WriteMode)                                    **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : PhysicalAddress, s_ptr, WriteMode                        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : This routine calls flash write command cycles                **
*******************************************************************************/
void Fls_CallWriteCommand(volatile uint32 PhysicalAddress, 
                          const Fls_17_Dmu_StateType *s_ptr,
                          uint8 WriteMode)
{
  Fls_WriteCmdCycles(PhysicalAddress,
                s_ptr->FlsWriteAddress,
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast
       is required to match the object types.The access range 
       is within the flash address range */
                (const Fls_17_Dmu_AddressType*)s_ptr->FlsWriteBufferPtr,
                WriteMode);
}

/*******************************************************************************
** Syntax : void Fls_ResetReadCmdCycle(void)                                  **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : This routine contains flash Reset command cycles             **
*******************************************************************************/
void Fls_ResetReadCmdCycle(void)
{ 
  Cycle5554(FLS_17_DMU_BASE_ADDRESS, VALUE_F0);
}

/*******************************************************************************
** Syntax : void Fls_ClearStatusCmdCycle(void)                                **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : This routine contains flash clear status command cycles      **
*******************************************************************************/
void Fls_ClearStatusCmdCycle(void)
{ 
  Cycle5554(FLS_17_DMU_BASE_ADDRESS, VALUE_FA);

}
#if (FLS_17_DMU_USE_ERASESUSPEND == STD_ON)
/*******************************************************************************
** Syntax : void Fls_ResumeEraseCmdCycle(volatile uint32 StartAddress)        **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : StartAddress                                             **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : This routine contains flash resume erase command cycles      **
*******************************************************************************/
void Fls_ResumeEraseCmdCycle(volatile uint32 EraseAddress)
{

  volatile uint32 StartAddress;
  volatile uint8 EraseNumSec;
  const Fls_17_Dmu_StateType* StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  EraseNumSec  = StatePtr->FlsEraseNumSecPerCmd;
  StartAddress = FLS_17_DMU_BASE_ADDRESS;

  /* cycle 1 */
  CycleAA50(StartAddress, EraseAddress);

  /* cycle 2 */
  CycleAA58(StartAddress, EraseNumSec);
  /* cycle 3 */
  CycleAAA8(StartAddress, VALUE_70);
  /* cycle 4 */
  CycleAAA8(StartAddress, VALUE_CC);
}
#endif /* FLS_17_DMU_USE_ERASESUSPEND == STD_ON */

/*******************************************************************************
** Syntax : void Fls_UserContentCountCmdCycle(uint32 WordLineAddress)         **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : WordLineAddress                                          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : This routine contains user content count command cycles      **
*******************************************************************************/
void Fls_UserContentCountCmdCycle(volatile uint32 WordLineAddress)
{ 
  volatile uint32 StartAddress;
  StartAddress = FLS_17_DMU_BASE_ADDRESS;
  /* cycle 1 */
  CycleAA50(StartAddress, WordLineAddress);
  /* cycle 2 */
  CycleAA58(StartAddress, VALUE_00);
  /* cycle 3 */
  CycleAAA8(StartAddress, VALUE_60);
  /* cycle 4 */
  CycleAAA8(StartAddress, VALUE_14);

}
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

/*******************************************************************************
** Syntax: LOCAL_INLINE boolean Fls_lCmdCycleTimeout05(uint32 InnerCount) **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : InnerCount - Delay count                                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : boolean                                                  **
**                                                                            **
** Description : This routine checks if command cycle timeout occured         **
*******************************************************************************/
LOCAL_INLINE boolean Fls_lCmdCycleTimeout05(uint32 InnerCount)
{
  boolean RetVal;

  if (InnerCount >= (uint32)FLS_17_DMU_CMDCYCLE_TIMEOUT)
  {
    RetVal = (boolean)TRUE; 
  }
  else
  {
    RetVal = (boolean)FALSE; 
  }
  return (RetVal);
}

/*******************************************************************************
** Syntax: LOCAL_INLINE boolean Fls_lCmdCycleTimeout06(uint32 InnerCount) **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : InnerCount - Delay count                                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : boolean                                                  **
**                                                                            **
** Description : This routine checks if command cycle timeout occured         **
*******************************************************************************/
LOCAL_INLINE boolean Fls_lCmdCycleTimeout06(uint32 InnerCount)
{
  boolean RetVal;
  if (InnerCount >= FLS_17_DMU_CMDCYCLE_TIMEOUT)
  {
    RetVal = (boolean)TRUE; 
  }
  else
  {
    RetVal = (boolean)FALSE; 
  }
  return (RetVal);
}

/*******************************************************************************
** Syntax: LOCAL_INLINE void Cycle5554(volatile uint32 Address, uint32 Data)  **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : Address, Data                                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value : None                                                        **
**                                                                            **
** Description : cmd cycle formation                                          **
*******************************************************************************/
LOCAL_INLINE void Cycle5554(volatile uint32 Address, uint32 Data)
{
  uint32 StartAddress;
  StartAddress = ((Address) & MASK_HIGHER4_NIBBLES) + CYCLE_5554;
    /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
       is required to store the FLASH address/target address in state var 
       structure to perform easy arithmethic operations. */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
       type is required to access the FLASH address/target address which 
       is defined as unsigned long. */
  *((uint32*)StartAddress) = Data;
  DSYNC();
  return;
}

/*******************************************************************************
** Syntax: LOCAL_INLINE void CycleAAA8(volatile uint32 Address, uint32 Data)  **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : Address, Data                                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value : None                                                        **
**                                                                            **
** Description : cmd cycle formation                                          **
*******************************************************************************/
LOCAL_INLINE void CycleAAA8(volatile uint32 Address, uint32 Data)
{
  uint32 StartAddress;
  StartAddress = ((Address) & MASK_HIGHER4_NIBBLES) + CYCLE_AAA8;
    /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
       is required to store the FLASH address/target address in state var 
       structure to perform easy arithmethic operations. */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
       type is required to access the FLASH address/target address which 
       is defined as unsigned long. */
  *((uint32*)StartAddress) = Data;
  DSYNC();
  return;
}

/*******************************************************************************
** Syntax: LOCAL_INLINE void CycleAA50(volatile uint32 Address, uint32 Data)  **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : Address, Data                                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value : None                                                        **
**                                                                            **
** Description : cmd cycle formation                                          **
*******************************************************************************/
LOCAL_INLINE void CycleAA50(volatile uint32 Address, uint32 Data)
{
  uint32 StartAddress;
  StartAddress = ((Address) & MASK_HIGHER4_NIBBLES) + CYCLE_AA50;
    /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
       is required to store the FLASH address/target address in state var 
       structure to perform easy arithmethic operations. */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
       type is required to access the FLASH address/target address which 
       is defined as unsigned long. */
  *((uint32*)StartAddress) = Data;
  DSYNC();
  return;
}

/*******************************************************************************
** Syntax: LOCAL_INLINE void CycleAA58(volatile uint32 Address, uint32 Data)  **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : Address, Data                                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value : None                                                        **
**                                                                            **
** Description : cmd cycle formation                                          **
*******************************************************************************/
LOCAL_INLINE void CycleAA58(volatile uint32 Address, uint32 Data)
{
  uint32 StartAddress;
  StartAddress = ((Address) & MASK_HIGHER4_NIBBLES) + CYCLE_AA58;
    /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
       is required to store the FLASH address/target address in state var 
       structure to perform easy arithmethic operations. */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
       type is required to access the FLASH address/target address which 
       is defined as unsigned long. */
  *((uint32*)StartAddress) = Data;
  DSYNC();
  return;
}


/*******************************************************************************
** Syntax: LOCAL_INLINE void EnterPageMode(volatile uint32 address,           **
**                                                  uint32 Data)              **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : address , Data                                           **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value : None                                                        **
**                                                                            **
** Description : cmd cycle formation                                          **
*******************************************************************************/
LOCAL_INLINE void EnterPageMode(volatile uint32 Address, uint32 Data)
{
  uint32 StartAddress;
  
  StartAddress = ((Address) & MASK_HIGHER4_NIBBLES) + CYCLE_5554;
    /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
       is required to store the FLASH address/target address in state var 
       structure to perform easy arithmethic operations. */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
       type is required to access the FLASH address/target address which 
       is defined as unsigned long. */
  *((uint32*)StartAddress) = Data;
  DSYNC();
 
  return;
}

/*******************************************************************************
** Syntax: LOCAL_INLINE void LoadPage(volatile uint32 Address,                **
**                                    const Fls_AddressType* DataPtr)         **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : address                                                  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value : None                                                        **
**                                                                            **
** Description : cmd cycle formation                                          **
*******************************************************************************/
LOCAL_INLINE void LoadPage(volatile uint32 Address,
                                     const Fls_17_Dmu_AddressType* DataPtr)
{
  Fls_17_Dmu_AddressType* StartAddress;
  StartAddress = (Fls_17_Dmu_AddressType *)
    /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
       is required to store the FLASH address/target address in state var 
       structure to perform easy arithmethic operations. */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
       type is required to access the FLASH address/target address which 
       is defined as unsigned long. */
   /* MISRA2012_RULE_10_8_JUSTIFICATION: conversion between pointer and integer
       type is required to access the FLASH address/target address which 
       is defined as unsigned long. */
               (((Address) & MASK_HIGHER4_NIBBLES) + CYCLE_55F0);

  *StartAddress = *DataPtr;
  DSYNC();
  /* Page assembly buffer pointer gets incremented automatically */
      /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than 
      array indexing used for page assembly buffer and for subsequent 
      traversal.The access range is within the valid range.*/
  *(StartAddress + 1) = *(DataPtr + 1U);
  DSYNC();
  return;
}




/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_STOP_SEC_CODE_ASIL_B_LOCAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Fls_17_Dmu_MemMap.h"

