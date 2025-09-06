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
**  FILENAME     : Wdg_17_Scu_Demo.c                                          **
**                                                                            **
**  VERSION      : 1.1.0                                                      **
**                                                                            **
**  DATE         : 2016-12-22                                                 **
**                                                                            **
**  VARIANT      : NA                                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Demo application for WDG module                            **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Wdg_17_Scu_Demo.h"
#include "McalLib.h"
#include "IfxSrc_reg.h"
#include "IfxSmu_reg.h"
#include "IfxScu_reg.h"
#include "Test_Print.h"
#include "Test_Time.h"
#include "IFX_Os.h"
#include "Mcu_Cfg.h"
#include "IfxStm_reg.h"
/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#define MAX_UINT32 0xFFFFFFFF
/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
#define WDG_17_SCU_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
#include "Wdg_17_Scu_MemMap.h"

extern const Wdg_17_Scu_ConfigType Wdg_17_Scu_Config_0;

#define WDG_17_SCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
#include "Wdg_17_Scu_MemMap.h"
/*******************************************************************************
**                      Global Variable Definitions                           **
********************************************************************************/
  volatile uint32 *Address_ptr_1 = NULL;
  volatile uint32 *Address_ptr_2 = NULL;
/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
#define WDG_17_SCU_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
#include "Wdg_17_Scu_MemMap.h"

static uint8 Wdg_DemoCalled;

#define WDG_17_SCU_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
#include "Wdg_17_Scu_MemMap.h"
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*******************************************************************************
** Syntax : void Wdg_17_Scu_Demo(void)                                        **
**                                                                            **
** Service ID:   : NA                                                         **
**                                                                            **
** Sync/Async:   : Synchronous                                                **
**                                                                            **
** Reentrancy:   : Non Reentrant                                              **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Description : In this demo the Wdg can be started in the Fast mode or Slow **
** Mode for the said tiemout period. User should press the trigger key to stop**
** the WDG from resetting.                                                    **
** The user is provided the option to stop the WDG.                           **
** Note that If two consecutive resets are triggered by the WDG the target    **
** needs a Power On Reset.                                                    **
**                                                                            **
*******************************************************************************/

void Wdg_17_Scu_Demo(void)
{
  volatile uint8 LoopVar = 0;
  char InputString[10];
  volatile uint32 Wdg_Cnt_Dif;
  const Wdg_17_Scu_ConfigType * ConfigPtr = &Wdg_17_Scu_Config_0;
  
 
    Mcal_WriteSafetyEndInitProtReg((uint32*)0xF0036834,0xbc); /*KEYS*/
    Mcal_WriteSafetyEndInitProtReg((uint32*)0xF0036820,0x00); /*SMU_CMD*/
    Mcal_WriteSafetyEndInitProtReg((uint32*)0xF0036960,0x00); /*SMU_AGCF8_0*/
    Mcal_WriteSafetyEndInitProtReg((uint32*)0xF0036964,0x0003fc00); /*SMU_AGCF8_1*/
    Mcal_WriteSafetyEndInitProtReg((uint32*)0xF0036968,0x0003fc00); /*SMU_AGCF8_2*/
	Mcal_WriteSafetyEndInitProtReg((uint32*)0xF0036058u, 0x00000040); /*SCU_RSTCON.SMU need to be set to 1 for reset to occur*/
    Mcal_WriteSafetyEndInitProtReg((uint32*)0xF0036834,0x00); /*KEYS*/ 

	Address_ptr_1 = (uint32*)0x90000000;
	Address_ptr_2 = (uint32*)0x90000010;	

  /* Initialiase interrupt request configurations */
  if( Wdg_DemoCalled == 0U )
  {
    /*IrqStm_Init();*/
	Test_IrqStm_Init(), 
    
    /* Initialize WDG driver */
    Wdg_17_Scu_Init(ConfigPtr);

    /* reset the iscr */
    SRC_STM0SR0.B.IOVCLR=1U;
    SRC_STM0SR0.B.CLRR=1U;
    SRC_STM0SR0.B.SWSCLR=1U;
    
    /* Enable the interrupt */
    SRC_STM0SR0.B.SRE = 1;
  
    Wdg_DemoCalled = 1U;
  }
  
  while (LoopVar == 0)
  {  
    print_f("\n");
    print_f("\n < >: ............ WDG DRIVER DEMO MENU ............");

    print_f("\n <s>: Set WDG0 in slow mode");
    print_f("\n      Each press of key 's' will set trigger timeout period of 7 Seconds");

    print_f("\n <f>: Set WDG0 in Fast mode");
    print_f("\n      Each press of key 'f' will set trigger timeout period of 4 Seconds");

    print_f("\n <t>: Press 't' to trigger WDG0 timeout for 4 seconds in current mode.");
	
	print_f("\n <r>: Press 'r' to find the time taken for the previous Reset \n");	

    print_f("\n <x>: Stop WDG0 Timer \n"); 

    print_f("\n <.>: Stop All WDG Timers and exit WDG demo \n");

    print_f("\nEnter option: \n");

    /* Get the Key pressed from user */
    getline(InputString, sizeof InputString - 1);

    if((*InputString == 'S') || (*InputString == 's'))
    {    
      #if(WDG_17_SCU_MAX_TIMERS != 0U)
		*Address_ptr_1 = STM0_TIM0.U;
        /* Start Watchdog in Slow Mode */
        if ( E_OK == Wdg_17_Scu_SetMode(WDGIF_SLOW_MODE))
        {
            Wdg_17_Scu_SetTriggerCondition(7000);			
            print_f("\n\n WDG0 has been started in Slow Mode. \n");
            print_f("\n 1st LED on the Tri-Board toggles until watchdog timeout occurs (at the rate of WdgSlowRefreshTime). \n");
            StartResult();
            print_f("Result = Pass;");
            EndResult();
        }
        else
        {
          StartResult();
          print_f("Result = Fail;");
          EndResult();   
        }
        #endif
    }
    else if((*InputString == 'F') || (*InputString == 'f'))
    {
      #if(WDG_17_SCU_MAX_TIMERS != 0U)
		*Address_ptr_1 = STM0_TIM0.U; 
        /* Start Watchdog in Fast Mode */
        if ( E_OK == Wdg_17_Scu_SetMode(WDGIF_FAST_MODE))
        {
            Wdg_17_Scu_SetTriggerCondition(4000);
            print_f("\n\n WDG0 has been started in Fast Mode \n");
            print_f("\n 1st LED on the Tri-Board toggles until watchdog timeout occurs (at the rate of WdgFastRefreshTime). \n");
            StartResult();
            print_f("Result = Pass;");
            EndResult();
        }
        else
        {
           StartResult();
           print_f("Result = Fail;");
           EndResult();  
            
        }
		
      #endif
    }
    else if((*InputString == 'T') || (*InputString == 't'))
    {
      #if(WDG_17_SCU_MAX_TIMERS != 0U)
        /* Start WDG Triggering */
            Wdg_17_Scu_SetTriggerCondition(4000);
            print_f("\n\n WDG0 has been Triggered \n");
            print_f("\n 1st LED on the Tri-Board toggles until watchdog timeout occurs. \n");
            StartResult();
            print_f("Result = Pass;");
            EndResult();
      #endif
    }
    else if((*InputString == 'X') || (*InputString == 'x'))
    {
      #if(WDG_17_SCU_MAX_TIMERS != 0U)
        /* Stop WDG */
        if ( E_OK == Wdg_17_Scu_SetMode(WDGIF_OFF_MODE))
        {
        print_f("\n WDG0 has been stopped \n");
        StartResult();
        print_f("Result = Pass;");
        EndResult();
        }
        else
        {
           StartResult();
           print_f("Result = Fail;");
           EndResult();
        }
      #endif
    }
    else if((*InputString == 'R') || (*InputString == 'r'))	
	{
		if(*Address_ptr_2 > *Address_ptr_1)
		Wdg_Cnt_Dif = *Address_ptr_2 - *Address_ptr_1;
		else
		Wdg_Cnt_Dif = (MAX_UINT32 - (*Address_ptr_2)) + *Address_ptr_1;
		
		Wdg_Cnt_Dif = Wdg_Cnt_Dif * (0.00000001);
		print_f( "\n The Time taken for the last Reset = %d Seconds\n", Wdg_Cnt_Dif);
	}
	
    else if(*InputString == '.')
    {
      #if(WDG_17_SCU_MAX_TIMERS != 0U)
        /* Stop all WDGs and Exit from the Demo */
        Wdg_17_Scu_SetMode(WDGIF_OFF_MODE);
      #endif
        LoopVar = 1;
        break;
    }
    else
    {
      print_f("\n  Invalid key pressed,  ");
	    StartResult();
        print_f("Result = Fail;");
        EndResult();
    } 
  }/* while */

  print_f("\n----------------------------------\n ");
  print_f("\n       EXIT WDG DEMO              \n ");
  print_f("\n----------------------------------\n ");
  return;
} /* WDG_Demo */
