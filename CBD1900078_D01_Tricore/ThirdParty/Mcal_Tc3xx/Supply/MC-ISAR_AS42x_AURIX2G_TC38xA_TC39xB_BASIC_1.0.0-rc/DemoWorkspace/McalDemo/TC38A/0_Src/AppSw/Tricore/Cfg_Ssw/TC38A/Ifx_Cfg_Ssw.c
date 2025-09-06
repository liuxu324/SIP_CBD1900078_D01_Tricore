/**
 * \file Ifx_Cfg_Ssw.c
 * \brief Configuration file for the Startup Software
 * \ingroup
 *
 *
 * \copyright Copyright (c) 2016 Infineon Technologies AG. All rights reserved.
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineons microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

#include "Ifx_Cfg_Ssw.h"

#if (IFX_CFG_SSW_ENABLE_MBIST)
void Ifx_Ssw_Mbist(void)
{
	resetPerfCounters();
	IFX_EXTERN const IfxMtu_MbistConfig *const mbistGangConfig[];
	if (IfxMtu_runMbistAll(mbistGangConfig) == 1U)
    {
        __debug();
    }
	updateMbistRuntime();
}
#endif

#if (IFX_CFG_SSW_ENABLE_PLL_INIT)
void Ifx_Ssw_PLL_Init(void)
{
	if (IfxScuCcu_init(&IfxScuCcu_defaultClockConfig) == 1)
    {
        __debug();
    }
}
#endif
#ifdef __DCC__
int main(void){
	return 0;
}
#endif
