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
**  FILENAME     : SchM_Mcu.c                                                 **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2018-02-12                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : SchM file for Mcu                                          **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#include "IFX_Os.h"
#include "SchM_Mcu.h"
#if(LATENCY_CALC_MCU==1U)
	#include "Test_Latency.h"
#endif

void SchM_Enter_Mcu_TomTgcReg(void)
{
  SuspendAllInterrupts();
#if(LATENCY_CALC_MCU==1U)
		Measure_Start_Value(0);
#endif
}

void SchM_Exit_Mcu_TomTgcReg(void)
{
#if(LATENCY_CALC_MCU==1U)
		Measure_End_Value(0);
#endif
  ResumeAllInterrupts();
}

void SchM_Enter_Mcu_AtomAgcReg(void)
{
  SuspendAllInterrupts();
#if(LATENCY_CALC_MCU==1U)
		Measure_Start_Value(1);
#endif
}
void SchM_Exit_Mcu_AtomAgcReg(void)
{
#if(LATENCY_CALC_MCU==1U)
		Measure_End_Value(1);
#endif
  ResumeAllInterrupts();
}
