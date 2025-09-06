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
**  FILENAME     : SchM_Pwm_17_GtmCcu6.h                                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2017-09-12                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : SchM file for Pwm driver                                   **
**                                                                            **
**  SPECIFICATION(S) : Specification of RTE, AUTOSAR Release 4.2.2            **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

#include "IFX_Os.h"
#include "SchM_Pwm_17_GtmCcu6.h"

#if(LATENCY_CALC_PWM==1U)
#include "Test_Latency.h"
#endif
/* [cover parentID={08F29853-464C-4882-8042-7797B2E031CD}]
 Schm Definition for HandleNotification
[/cover] */
void SchM_Enter_Pwm_17_GtmCcu6_HandleNotification(void)
{
    SuspendAllInterrupts();
    #if(LATENCY_CALC_PWM==1U)
    Measure_Start_Value(0);
    #endif
}
void SchM_Exit_Pwm_17_GtmCcu6_HandleNotification(void)
{
    #if(LATENCY_CALC_PWM==1U)
    Measure_End_Value(0);
    #endif
    ResumeAllInterrupts();
}
/* [cover parentID={387AB8B7-BB77-450b-9419-CB4493C29C27}]
Schm Definition for PeriodAndDutyUpdate
[/cover] */
void SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate(void)
{
    SuspendAllInterrupts();
    #if(LATENCY_CALC_PWM==1U)
    Measure_Start_Value(1);
    #endif
}

void SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate(void)
{
    #if(LATENCY_CALC_PWM==1U)
    Measure_End_Value(1);
    #endif
    ResumeAllInterrupts();
}
