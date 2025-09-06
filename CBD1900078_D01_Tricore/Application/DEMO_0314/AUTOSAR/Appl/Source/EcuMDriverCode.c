/*
 * EcuMDriverCode.c

 *
 *  Created on: 2016-3-1
 *      Author: Administrator
 */

#if 0
#include "EcuMDriverCode.h"

#include "Os.h"
#include "Mcu.h"
#include "Port.h"

#include "Mcu_PBcfg.h"
#include "Port_PBcfg.h"

void EcuMDriverInitOne(void)
{
	if(GetCoreID() == 0)
	{
		Mcu_Init(&Mcu_Config);
		Mcu_InitClock(0);
		while ((Mcu_GetPllStatus()) != MCU_PLL_LOCKED);
		Mcu_DistributePllClock();

		Port_Init(&Port_Config);
	}
	else
	{

	}
}

#endif
