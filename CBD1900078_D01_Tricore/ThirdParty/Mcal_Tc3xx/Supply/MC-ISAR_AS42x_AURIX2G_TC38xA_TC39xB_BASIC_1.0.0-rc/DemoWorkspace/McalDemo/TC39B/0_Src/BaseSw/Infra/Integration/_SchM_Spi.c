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
**  FILENAME     : SchM_Spi.c                                                 **
**                                                                            **
**  VERSION      : 0.0.2                                                      **
**                                                                            **
**  DATE         : 2016-09-09                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : SchM file for Spi driver                                   **
**                                                                            **
**  SPECIFICATION(S) : Specification of RTE, AUTOSAR Release 4.2.2            **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#include "IFX_Os.h"
#include "SchM_Spi.h"

#if(LATENCY_CALC_SPI==1U)
	#include "Test_Latency.h"
#endif
void SchM_Enter_Spi_Queue_Update(void)
{
	SuspendAllInterrupts();
	#if(LATENCY_CALC_SPI==1U)
		Measure_Start_Value(0);
    #endif
}
	
void SchM_Exit_Spi_Queue_Update(void)
{
	#if(LATENCY_CALC_SPI==1U)
		Measure_End_Value(0);
    #endif
	ResumeAllInterrupts();
}

void SchM_Enter_Spi_ChannelLock(void)
{
	SuspendAllInterrupts();
	#if(LATENCY_CALC_SPI==1U)
		Measure_Start_Value(1);
    #endif
}

void SchM_Exit_Spi_ChannelLock(void)
{
	#if(LATENCY_CALC_SPI==1U)
		Measure_End_Value(1);
    #endif
	ResumeAllInterrupts();
}

void SchM_Enter_Spi_SyncLock(void)
{
	SuspendAllInterrupts();
	#if(LATENCY_CALC_SPI==1U)
		Measure_Start_Value(2);
    #endif
}

void SchM_Exit_Spi_SyncLock(void)
{ 
	#if(LATENCY_CALC_SPI==1U)
		Measure_End_Value(2);
    #endif
	ResumeAllInterrupts();
}
