/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2017)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : DemoApp.c                                                   **
**                                                                           **
**  VERSION    : 2.0.0                                                       **
**                                                                           **
**  DATE       : 2017-03-07                                                  **
**                                                                           **
**  VARIANT    : NA                                                          **
**                                                                           **
**  PLATFORM   : Infineon AURIX2G                                            **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : This file contains                                         **
**                - DemoApp Framework for MCAL driver Demo Applications      **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Std_Types.h"
#include "IfxCpu_reg.h"
#include "Test_Print.h"
#include "Test_Time.h"
#include "DemoApp_Cfg.h"
#include "Mcu.h"
#include "Port.h"
#include "DemoApp.h"

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
#if (MCU_DEMO_EN == STD_ON)
#include "Mcu_Demo.h"
#endif

 #if (DIO_DEMO_EN == STD_ON)
 #include "Dio_Demo.h"
 #endif

#if (GPT_DEMO_EN == STD_ON)
 #include "Gpt_Demo.h"
 #endif

 #if (SPI_DEMO_EN == STD_ON)
 #include "Spi_Demo.h"
 #endif

 #if (PWM_DEMO_EN == STD_ON)
 #include "Pwm_17_GtmCcu6_Demo.h"
 #endif

 #if (ADC_DEMO_EN == STD_ON)
 #include "Adc_Demo.h"
 #endif

 #if (ICU_DEMO_EN == STD_ON)
 #include "Icu_17_TimerIp_Demo.h"
 #endif

 #if (FLS_DEMO_EN == STD_ON)
 #include "Fls_17_Dmu_Demo.h"
 #endif

 #if (FEE_DEMO_EN == STD_ON)
 #include "Fee_Demo.h"
 #endif

 #if (CAN_DEMO_EN == STD_ON)
 #include "Can_17_McmCan_Demo.h"
 #endif

 #if (FR_DEMO_EN == STD_ON)
 #include "Fr_17_Eray_Demo.h"
 #endif

 #if (ETH_DEMO_EN == STD_ON)
 #include "Eth_17_GEthMac_Demo.h"
 #endif

 #if (DMA_DEMO_EN == STD_ON)
 #include "Dma_Demo.h"
 #endif

 #if (WDG_DEMO_EN == STD_ON)
 #include "Wdg_17_Scu_Demo.h"
 #endif

#if (CRC_DEMO_EN == STD_ON)
#include "Crc_Demo.h"
#endif

#if (FLSLDR_DEMO_EN == STD_ON)
#include "FlsLoader_Demo.h"
#endif

#if (SMU_DEMO_EN == STD_ON)
#include "Smu_Demo.h"
#endif
/*******************************************************************************
**               Private Macro Definitions                                    **
*******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
void DemoApp(void);
void DemoApp_PrintChoices(void);
void DemoApp_CallMenuFct  (char *my_fct_name) __attribute__ ((noinline));

void DemoApp_GotoDemoMenu(void);
void DemoApp_GotoMainMenu(void);
void DemoApp_DummyFct(void);

void DemoApp_Init(void);
void DemoApp_Mcu_Init(void);
void DemoApp_Port_Init(void);

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
const DemoApp_FctListType DemoApp_FctList[] =
{
  {" "  , DemoApp_DummyFct, "............ AUTOSAR DRIVERS..............."},
  #if (ADC_DEMO_EN == STD_ON)
  {"a",Adc_Demo, "  Adc: Demo"},
  #endif
  
  #if (CAN_DEMO_EN == STD_ON)
  {"b",Can_17_McmCan_Demo, "  Can_17_McmCan: Demo"},
  #endif
  
  #if (DIO_DEMO_EN == STD_ON)
  {"c",Dio_Demo, "  Dio: Demo"},
  #endif
  
  #if (DMA_DEMO_EN == STD_ON)
  {"d",Dma_Demo, "  Dma: Demo "},
  #endif
  
 #if (ETH_DEMO_EN == STD_ON)
  {"e",Eth_17_Demo, "  Eth_17_GEthmac: Demo "},
  #endif
  
  #if (FEE_DEMO_EN == STD_ON)
  {"f",Fee_Demo, "  Fee: Demo"},
  #endif
  
  #if (FLS_DEMO_EN == STD_ON)
  {"g",Fls_17_Dmu_Demo, "  Fls_17_Dmu: Demo"},
  #endif
  
  #if (FR_DEMO_EN == STD_ON)
  #ifdef FR_17_ERAY_PBCFG_0
  {"h",Fr_17_Eray_Demo, "  Fr_17_Eray: Demo"},
  #endif
  #endif
  
  #if (GPT_DEMO_EN == STD_ON)
  {"i",Gpt_Demo, "  Gpt: Demo"},
  #endif
  
  #if (ICU_DEMO_EN == STD_ON)
  {"j",Icu_17_TimerIp_Demo, "  Icu_17_TimerIp: Demo"},
  #endif  
  
  #if (MCU_DEMO_EN == STD_ON)
  {"k",Mcu_Demo, "  Mcu: Demo"},
  #endif
  
  #if (PWM_DEMO_EN == STD_ON)
  {"l",Pwm_17_GtmCcu6_Demo,"  Pwm_17_GtmCcu6: Demo"},
  #endif
  
   #if (SPI_DEMO_EN == STD_ON)
  {"m",Spi_Demo, "  Spi: Demo"},
  #endif

  #if (WDG_DEMO_EN == STD_ON)
  {"n",Wdg_17_Scu_Demo, "  Wdg_17_Scu: Demo"},
  #endif
  
    #if (CRC_DEMO_EN == STD_ON)
  {"o",Crc_Demo, "  Crc: Demo"},
  #endif 
  
  #if (FLSLDR_DEMO_EN == STD_ON)
  {"p",FlsLoader_Demo, "  FlsLoader: Demo"},
  #endif
  
  #if (SMU_DEMO_EN == STD_ON)
  {"q",Smu_Demo, "  Smu: Demo"},
  #endif
  
  { ".", DemoApp_GotoMainMenu , "Go to Main Menu" }

};

const DemoApp_MenuType DemoApp_DemoMenu=
{
  sizeof(DemoApp_FctList) / sizeof(DemoApp_FctListType),
  &DemoApp_FctList[0]
};

const DemoApp_FctListType DemoApp_MainList[]=
{
  { " " , DemoApp_DummyFct , "------------- Main Menu ------------- "  },
  { "0" , DemoApp_GotoDemoMenu,   "Goto MCAL DemoApp List"  },
};
const DemoApp_MenuType DemoApp_MainMenu=
{
  sizeof(DemoApp_MainList) / sizeof(DemoApp_FctListType),
  &DemoApp_MainList[0]
};

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
DemoApp_MenuType const *DemoApp_Menu_p;
char szString[80];
uint32 str_pos; /* position of the pointer in the receive buffer */
uint8 DemoApp_FlsInitDone; /* Flag to check FLS init is already called */
 #define MCU_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
 #include "Mcu_MemMap.h"

extern const Mcu_ConfigType Mcu_Config;

 #define MCU_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
 #include "Mcu_MemMap.h"

 #define PORT_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
 #include "Port_MemMap.h"

extern const Port_ConfigType Port_Config;

 #define PORT_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
 #include "Port_MemMap.h"

/*******************************************************************************
**                      Private  Constant Definitions                         **
*******************************************************************************/
/*******************************************************************************
**                     Private  Variable Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*******************************************************************************
** Syntax : void DemoApp(void)                                                **
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
** Return value: none                                                         **
**                                                                            **
** Description : Demo Tests for all the delivered Modules.                    **
*******************************************************************************/
void DemoApp(void)
{
/*******************************************************************************
**                    Menu options on the hyperterminal                       **
*******************************************************************************/


  DemoApp_Menu_p = &DemoApp_MainMenu;
  str_pos=0;

  Test_InitTime(); /* Initialize Time Measurement For Run Time Calc */
  Test_InitPrint();/* Initialize ASC0 for Hyperterminal Communication*/

  print_flushfifo();

#ifdef DEMO_APP_NODE_1
   for (;;)
   {   
	    print_f("\n\n/*******************************************************/\n");                                        
	    print_f("\n 1.  FR Node 1              \n ");                                        
	    /*print_f("2.  HSSL Slave Node                                 \n ");  */                                      
	    print_f("                                                            \n ");                                        
	    print_f("\n/*********************************************************/\n");                                        
	    print_f("  Enter Your Option :: ");     
	    getline(szString, sizeof szString - 1);                                                                            
	    switch (*szString)                                                                                                 
	    {                                                                                                                  
	       case '1':                                                                                                       
	       {    /*
	            Call FlexRay node 1 demo application. This application infinitely
	            waits for Flexray node 0 to synchronise and transmit/receive data.
	            This is done in an infinite loop, so it never goes to next statement in
	            this program.
	            Preprocessor switch DEMO_APP_NODE_1 is defined during build time.
	           */
	           Fr_17_Eray_Demo();
	           break;                                                                                                      
	       }                                                                                                               
	     /*  case '2' :                                                                                                      
	       {                                                                                                               
	           //Hssl_Demo();                                                                                      
	           break;                                                                                                      
	       }   */    
	           default :                                                                                                       
	         print_f(" \n\n Invalid option, Enter Again \n ");                                                                          
	       break;                                                                                                          
	    }       
   }
#else

  int char_val;

  print_f("\n\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  print_f("\nCompiled@[%s %s]",__TIME__,__DATE__);
  print_f("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n\n\n");  
  DemoApp_PrintChoices();
  print_f("\nEnter Option Number: ");
  for (;;)
  {
    char_val = getlineWithPos(szString, sizeof szString - 1,&str_pos);
    if (char_val == CR)
    {
	    str_pos = 0;
	    print_f("\n\n");
	    DemoApp_CallMenuFct(szString);
	    DemoApp_PrintChoices();
      print_f("\nEnter Option Number: ");
    }
  }
#endif
}/*End of Demo App */

/*******************************************************************************
** Syntax : void DemoApp_CallMenuFct(char *)                                  **
**                                                                            **
** Service ID:   : NA                                                         **
**                                                                            **
** Sync/Async:   : Synchronous                                                **
**                                                                            **
** Reentrancy:   : Non Reentrant                                              **
**                                                                            **
** Parameters (in): char describing the function                              **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : call the demo function corresponding to the parameter        **
*******************************************************************************/
void DemoApp_CallMenuFct (char *my_fct_name)
{
  uint32 cnt;
  uint32 cnt_max = DemoApp_Menu_p->size;

  for (cnt=0;cnt<cnt_max;cnt++)
  {
    if(DemoApp_Menu_p->list[cnt].fct_name[0] == my_fct_name[0])
    {
        (* DemoApp_Menu_p->list[cnt].fct_p)();

        return;
    }
  }
}

/*******************************************************************************
** Syntax : void DemoApp_PrintChoices(void)                                   **
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
** Return value: none                                                         **
**                                                                            **
** Description : print choices                                                **
*******************************************************************************/
void DemoApp_PrintChoices(void)
{
  uint32 cnt;
  uint32 cnt_max = DemoApp_Menu_p->size;
  
  print_f("\n");
  for (cnt=0;cnt<cnt_max;cnt++)
  {
    print_f(" <%s>: %s\n",DemoApp_Menu_p->list[cnt].fct_name,
                          DemoApp_Menu_p->list[cnt].fct_desc);
  }
}
/*******************************************************************************
** Syntax : void DemoApp_GotoDemoMenu(void)                                   **
**                                                                            **
** Service ID:   : NA                                                         **
**                                                                            **
** Sync/Async:   : Synchronous                                                **
**                                                                            **
** Reentrancy:   : Reentrant                                                  **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : Initializes the Menu Pointer to the Demo Menu.               **
*******************************************************************************/
void DemoApp_GotoDemoMenu(void)
{
  DemoApp_Menu_p = &DemoApp_DemoMenu;
}

/*******************************************************************************
** Syntax : void DemoApp_GotoMainMenu(void)                                   **
**                                                                            **
** Service ID:   : NA                                                         **
**                                                                            **
** Sync/Async:   : Synchronous                                                **
**                                                                            **
** Reentrancy:   : Reentrant                                                  **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : Initializes the Menu Pointer to the Main Menu.               **
*******************************************************************************/
void DemoApp_GotoMainMenu(void)
{
  DemoApp_Menu_p = &DemoApp_MainMenu;
}
/*******************************************************************************
** Syntax : void DemoApp_DummyFct(void)                                       **
**                                                                            **
** Service ID:   : NA                                                         **
**                                                                            **
** Sync/Async:   : Synchronous                                                **
**                                                                            **
** Reentrancy:   : Reentrant                                                  **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : Dummy function to call when no operation has to be performed **
*******************************************************************************/
void DemoApp_DummyFct(void)
{
}

/*******************************************************************************
** Syntax : void DemoApp_Init(void)                                       **
**                                                                            **
** Service ID:   : NA                                                         **
**                                                                            **
** Sync/Async:   : Synchronous                                                **
**                                                                            **
** Reentrancy:   : Reentrant                                                  **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : Initialise Mcu and Port module to enable serial communication**
*******************************************************************************/
void DemoApp_Init(void)
{
  DemoApp_Mcu_Init();
  DemoApp_Port_Init();
}

/*******************************************************************************
** Syntax : void DemoApp_Mcu_Init(void)                                       **
**                                                                            **
** Service ID:   : NA                                                         **
**                                                                            **
** Sync/Async:   : Synchronous                                                **
**                                                                            **
** Reentrancy:   : Reentrant                                                  **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : Initialise Mcu module to enable clocks                       **
*******************************************************************************/
void DemoApp_Mcu_Init(void)
{
  const Mcu_ConfigType * ConfigPtr = NULL_PTR;
  volatile Mcu_ClockType ClockID = 0;
  Std_ReturnType InitClockRetVal;
  Mcu_PllStatusType Mcu_GetPllStatusRetVal = MCU_PLL_STATUS_UNDEFINED;  
  
  ConfigPtr = &Mcu_Config;
  Mcu_Init(ConfigPtr);  
  InitClockRetVal = Mcu_InitClock(ClockID); 
  
  if(InitClockRetVal == E_OK)
  {
    do
    {
      Mcu_GetPllStatusRetVal = Mcu_GetPllStatus ();
    }while(Mcu_GetPllStatusRetVal != MCU_PLL_LOCKED);
    
#if (MCU_DISTRIBUTE_PLL_CLOCK_API == STD_ON)
    Mcu_DistributePllClock ();
#endif
  } 
}

/*******************************************************************************
** Syntax : void DemoApp_Port_Init(void)                                      **
**                                                                            **
** Service ID:   : NA                                                         **
**                                                                            **
** Sync/Async:   : Synchronous                                                **
**                                                                            **
** Reentrancy:   : Reentrant                                                  **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : Initialise Port module to enable serial communication        **
*******************************************************************************/
void DemoApp_Port_Init(void)
{
  const Port_ConfigType * ConfigPtr = NULL_PTR;
  ConfigPtr = &Port_Config;
  Port_Init(ConfigPtr);
}
