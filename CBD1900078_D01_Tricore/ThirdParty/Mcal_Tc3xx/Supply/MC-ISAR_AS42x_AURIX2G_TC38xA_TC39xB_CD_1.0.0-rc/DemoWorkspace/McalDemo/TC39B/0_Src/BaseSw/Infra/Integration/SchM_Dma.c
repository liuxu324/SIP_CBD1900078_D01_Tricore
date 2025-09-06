/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2016)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : SchM_Dma.c                                                 **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2016-09-27                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : SchM file for Dma driver                                   **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#include "IFX_Os.h"
#include "SchM_Dma.h"
#if(LATENCY_CALC_DMA==1U)
#include "Test_Latency.h"
#endif


void SchM_Enter_Dma_ChannelConfigUpdate(void)
{
    SuspendAllInterrupts();
    #if(LATENCY_CALC_DMA==1U)
    Measure_Start_Value(0);
    #endif
}

void SchM_Exit_Dma_ChannelConfigUpdate(void)
{
    #if(LATENCY_CALC_DMA==1U)
    Measure_End_Value(0);
    #endif
    ResumeAllInterrupts();
}
