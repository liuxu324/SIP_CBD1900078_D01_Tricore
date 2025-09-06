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
**  FILENAME  : SchM_Wdg_17_Scu.c                                             **
**                                                                            **
**  VERSION      : 2.0.0                                                      **
**                                                                            **
**  DATE         : 2018-03-22                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : SchM file for Wdg driver                                   **
**                                                                            **
**  SPECIFICATION(S) : Specification of RTE, AUTOSAR Release 4.2.2            **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#include "IFX_Os.h"
#include "SchM_Wdg_17_Scu.h"

#if(LATENCY_CALC_WDG==1U)
	#include "Test_Latency.h"
#endif


void SchM_Enter_Wdg_17_Scu_TimerHandling(void)
{
  SuspendAllInterrupts();
  #if(LATENCY_CALC_WDG==1U)
    Measure_Start_Value(0);
  #endif
}

void SchM_Exit_Wdg_17_Scu_TimerHandling(void)
{
  #if(LATENCY_CALC_WDG==1U)
    Measure_End_Value(0);
  #endif
  ResumeAllInterrupts();
}

void SchM_Enter_Wdg_17_Scu_ChangeMode(void)
{
  SuspendAllInterrupts();
  #if(LATENCY_CALC_WDG==1U)
	Measure_Start_Value(1);
  #endif
}

void SchM_Exit_Wdg_17_Scu_ChangeMode(void)
{
  #if(LATENCY_CALC_WDG==1U)
	Measure_End_Value(1);
  #endif
  ResumeAllInterrupts();
}

void SchM_Enter_Wdg_17_Scu_CpuEndInit(void)
{
  SuspendAllInterrupts();
  #if(LATENCY_CALC_WDG==1U)
	Measure_Start_Value(2);
  #endif
}

void SchM_Exit_Wdg_17_Scu_CpuEndInit(void)
{
  #if(LATENCY_CALC_WDG==1U)
	Measure_End_Value(2);
  #endif
  ResumeAllInterrupts();
}

