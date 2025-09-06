/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2017)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Gpt12_Irq.c                                                **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2017-10-24                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : This file contains the interrupt frames for the GPT12.     **
**                                                                            **
**  SPECIFICATION(S) : Specification of Icu Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* MCAL header file containing global macros, type definitions and functions 
  needed by all MCAL drivers. */
#include "MCAL_Compiler.h"
#include "McalLib.h"
/* #include "IfxCpu_Intrinsics.h" */
/* Include MCU TIMERIP header file */
#include "Mcu_17_TimerIp.h"
#include "IFX_Os.h"


/* MCAL driver utility functions for setting interrupt priority initialization 
  and interrupt category */
#include "Irq.h"


/*******************************************************************************
**                      Imported Compiler Switch Checks                       **
*******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#define ISR(x) void x(void)

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/


/*******************************************************************************
** Syntax:           void GPT12_T2_ISR(void)                                 **
**                                                                            **
** Service ID:       NA                                                       **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  none                                                     **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This is Interrput Service request node T2 for the  GPT12.**
*******************************************************************************/
#if IRQ_GPT120_T2_TOS != IRQ_TOS_DMA
#if((IRQ_GPT120_T2_PRIO > 0) || (IRQ_GPT120_T2_CAT == IRQ_CAT2))
#if((IRQ_GPT120_T2_PRIO > 0) && (IRQ_GPT120_T2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GPT12_T2_ISR, 0, IRQ_GPT120_T2_PRIO)
#elif IRQ_GPT120_T2_CAT == IRQ_CAT2
ISR(GPT12_T2_ISR)
#endif
{
  /* Enable Global Interrupts */
 /* Mcal_EnableAllInterrupts(); */
	 ENABLE();
  Mcu_17_Gpt12_ChannelIsr(0);

}
#endif
#endif

/*******************************************************************************
** Syntax:           void GPT12_T3_ISR(void)                                 **
**                                                                            **
** Service ID:       NA                                                       **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  none                                                     **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This is Interrput Service request node T3 for the  GPT12.**
*******************************************************************************/
#if IRQ_GPT120_T3_TOS != IRQ_TOS_DMA
#if((IRQ_GPT120_T3_PRIO > 0) || (IRQ_GPT120_T3_CAT == IRQ_CAT2))
#if((IRQ_GPT120_T3_PRIO > 0) && (IRQ_GPT120_T3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GPT12_T3_ISR, 0, IRQ_GPT120_T3_PRIO)
#elif IRQ_GPT120_T3_CAT == IRQ_CAT2
ISR(GPT12_T3_ISR)
#endif
{
  /* Enable Global Interrupts */
 /* Mcal_EnableAllInterrupts(); */
	 ENABLE();
  Mcu_17_Gpt12_ChannelIsr(1);

}
#endif
#endif

/*******************************************************************************
** Syntax:           void GPT12_T4_ISR(void)                                 **
**                                                                            **
** Service ID:       NA                                                       **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  none                                                     **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This is Interrput Service request node T4 for the  GPT12.**
*******************************************************************************/
#if IRQ_GPT120_T4_TOS != IRQ_TOS_DMA
#if((IRQ_GPT120_T4_PRIO > 0) || (IRQ_GPT120_T4_CAT == IRQ_CAT2))
#if((IRQ_GPT120_T4_PRIO > 0) && (IRQ_GPT120_T4_CAT == IRQ_CAT1))
IFX_INTERRUPT(GPT12_T4_ISR, 0, IRQ_GPT120_T4_PRIO)
#elif IRQ_GPT120_T4_CAT == IRQ_CAT2
ISR(GPT12_T4_ISR)
#endif
{
  /* Enable Global Interrupts */
 /* Mcal_EnableAllInterrupts(); */
	 ENABLE();
  Mcu_17_Gpt12_ChannelIsr(2);

}
#endif
#endif

/*******************************************************************************
** Syntax:           void GPT12_T5_ISR(void)                                 **
**                                                                            **
** Service ID:       NA                                                       **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  none                                                     **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This is Interrput Service request node T5 for the  GPT12.**
*******************************************************************************/
#if IRQ_GPT120_T5_TOS != IRQ_TOS_DMA
#if((IRQ_GPT120_T5_PRIO > 0) || (IRQ_GPT120_T5_CAT == IRQ_CAT2))
#if((IRQ_GPT120_T5_PRIO > 0) && (IRQ_GPT120_T5_CAT == IRQ_CAT1))
IFX_INTERRUPT(GPT12_T5_ISR, 0, IRQ_GPT120_T5_PRIO)
#elif IRQ_GPT120_T5_CAT == IRQ_CAT2
ISR(GPT12_T5_ISR)
#endif
{
  /* Enable Global Interrupts */
 /* Mcal_EnableAllInterrupts(); */
	 ENABLE();
  Mcu_17_Gpt12_ChannelIsr(3);

}
#endif
#endif

/*******************************************************************************
** Syntax:           void GPT12_T6_ISR(void)                                 **
**                                                                            **
** Service ID:       NA                                                       **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  none                                                     **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This is Interrput Service request node T6 for the  GPT12.**
*******************************************************************************/
#if IRQ_GPT120_T6_TOS != IRQ_TOS_DMA
#if((IRQ_GPT120_T6_PRIO > 0) || (IRQ_GPT120_T6_CAT == IRQ_CAT2))
#if((IRQ_GPT120_T6_PRIO > 0) && (IRQ_GPT120_T6_CAT == IRQ_CAT1))
IFX_INTERRUPT(GPT12_T6_ISR, 0, IRQ_GPT120_T6_PRIO)
#elif IRQ_GPT120_T6_CAT == IRQ_CAT2
ISR(GPT12_T6_ISR)
#endif
{
  /* Enable Global Interrupts */
 /* Mcal_EnableAllInterrupts(); */
	 ENABLE();
  Mcu_17_Gpt12_ChannelIsr(4);

}
#endif
#endif
