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
**  FILENAME     : Gpt_Demo.c                                                 **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2016-10-13                                                 **
**                                                                            **
**  VARIANT      : NA                                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Demo application for GPT module                            **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Std_Types.h"
#include "IfxScu_reg.h"
#include "IfxSrc_reg.h"
#include "Mcal_Compiler.h"
#include "Test_Print.h"
#include "Gpt.h"
#include "Mcu.h"
#include "Dio.h"
#include "Irq.h"
#include "Gpt_Demo.h"

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#ifndef TRB_LED
#define TRB_LED DIO_CHANNEL_33_4
#endif

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
#define GPT_START_SEC_CODE_ASIL_B_GLOBAL
#include "Gpt_MemMap.h"

LOCAL_INLINE void Gpt_lStartDemo(void);
LOCAL_INLINE uint32 Gpt_lGetFgtm(void);

#define GPT_STOP_SEC_CODE_ASIL_B_GLOBAL
#include "Gpt_MemMap.h"

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
#define GPT_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
#include "Gpt_MemMap.h"

extern const Gpt_ConfigType Gpt_Config;

#define GPT_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
#include "Gpt_MemMap.h"

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/


static uint8 Gpt_ChannelNotif[1];
static uint8 Gpt_DemoCalled;



/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define GPT_START_SEC_CODE_ASIL_B_GLOBAL
#include "Gpt_MemMap.h"

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void Gpt_Demo(void)                                       **
**                                                                            **
** Description    : In this routine user options handling is done             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : none                                                      **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : none                                                      **
**                                                                            **
*******************************************************************************/
void Gpt_Demo(void)
{
  volatile uint8 LoopVar = 0;
  char InputString[10];
  /*const Gpt_ConfigType * ConfigPtr = &Gpt_Config;*/

  /* Initialiase interrupt request configurations */
  if( Gpt_DemoCalled == 0U )
  {
    IrqGtm_Init();
    SRC_GTMTOM00.B.SRE = 1;
    Gpt_DemoCalled = 1U;
  }

  /* Initialize GPT driver */
  Gpt_Init(&Gpt_Config);

  while (LoopVar == 0)
  {
    print_f("\n");
    print_f("\n < >: ............ GPT DRIVER DEMO MENU ............");
    print_f("\n <1>:  Start continuous timer : LED must start blinking for every 2 seconds");
    print_f("\n <2>:  Stop timer: LED must stop blinking");
    print_f("\n <.>: Go back to previous menu\n");
    print_f("\nEnter option Number: ");

    getline(InputString, sizeof InputString - 1);

    switch (*InputString)
    {
      case '1':
        Gpt_lStartDemo();
        StartResult();
        print_f("Result = Pass;");
        EndResult();
        break;

      case '2':
        /* Stop the timer, LED blinking stops, remains OFF/ON */
        Gpt_StopTimer(0);
        StartResult();
        print_f("Result = Pass;");
        EndResult();
        break;

      case '.':
        /* De-initialize GPT driver */
        Gpt_DeInit();
        LoopVar = 1;
        StartResult();
        print_f("Result = Pass;");
        EndResult();
        break;

      default:
        print_f("\n\n  INVALID OPTION");
        StartResult();
        print_f("Result = Fail;");
        EndResult();
        break;
    }/* End of switch-case */
  }/* End of While loop */
}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void Gpt_Notification(void)                               **
**                                                                            **
** Description    : GPT channel notification functionality, turns ON/OFF LED  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : none                                                      **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : none                                                      **
**                                                                            **
*******************************************************************************/
void IoHwAb_GptNotification0(void)
{
  /* start blinking the LED */
  if( Gpt_ChannelNotif[0] == 0)
  {
    Dio_WriteChannel(TRB_LED, STD_LOW);
    Gpt_ChannelNotif[0] = 1;
  }
  else
  {
    Dio_WriteChannel(TRB_LED, STD_HIGH);
    Gpt_ChannelNotif[0] = 0;
  }
}

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : uint32 Gpt_lGetFgtm(void)                                 **
**                                                                            **
** Description    : Calculates the frequency of the clock source to GTM       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : none                                                      **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : uint32 - Frequency of clock source for GTM                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Gpt_lGetFgtm(void)
{
  uint32 Fsrc0;
  uint32 Fgtm;
  uint8 PDIV = SCU_SYSPLLCON0.B.PDIV;
  uint8 NDIV = SCU_SYSPLLCON0.B.NDIV;
  uint8 K2DIV = SCU_SYSPLLCON1.B.K2DIV;

  Fsrc0 = ((MCU_MAIN_OSC_FREQ * 1000000) * (NDIV + 1)) / ((PDIV + 1)
                                                        * (K2DIV + 1));

  Fgtm = Fsrc0 / (SCU_CCUCON0.B.GTMDIV * GTM_CLS_CLK_CFG.B.CLS0_CLK_DIV);

  return Fgtm;
}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void Gpt_lStartDemo(void)                                 **
**                                                                            **
** Description    : Enables GPT notification and starts timer with defined    **
**                  time out period                                           **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : none                                                      **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : none                                                      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Gpt_lStartDemo(void)
{
  uint32 Fgtm;

  Gpt_EnableNotification(0);

  Fgtm = Gpt_lGetFgtm();
  Fgtm = ((uint32)(Fgtm / 65536)); /* CMU_FXCLK(4) selected, 2^16 divider */

  Gpt_StartTimer(0, (2 * Fgtm));   /* Time out of 2 sec */
}

#define GPT_STOP_SEC_CODE_ASIL_B_GLOBAL
#include "Gpt_MemMap.h"
