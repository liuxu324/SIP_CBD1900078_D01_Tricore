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
**  FILENAME  : Schm_Adc.c                                                    **
**                                                                            **
**  VERSION   : 6.0.0                                                         **
**                                                                            **
**  DATE      : 2018.07.30                                                    **
**                                                                            **
**  VARIANT   : Post-Build                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION : This file contains                                          **
**                 - Schm sections of ADC module - To be updated by used      **
**                                                                            **
**  SPECIFICATION(S) : Specification of ADC Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#include "IFX_Os.h"
#include "Schm_Adc.h"
#if(LATENCY_CALC_ADC==1U)
#include "Test_Latency.h"
#endif
 
void SchM_Enter_Adc_KernelData(void)
{
  SuspendAllInterrupts();
    #if(LATENCY_CALC_ADC==1U)
    Measure_Start_Value(0);
    #endif
}
 
void SchM_Exit_Adc_KernelData(void)
{
    #if(LATENCY_CALC_ADC==1U)
    Measure_End_Value(0);
    #endif
  ResumeAllInterrupts();
}
 
void SchM_Enter_Adc_SrcRegAccess(void)
{
  SuspendAllInterrupts();
    #if(LATENCY_CALC_ADC==1U)
    Measure_Start_Value(1);
    #endif
}
 
void SchM_Exit_Adc_SrcRegAccess(void)
{
    #if(LATENCY_CALC_ADC==1U)
    Measure_End_Value(1);
    #endif
  ResumeAllInterrupts();
}
