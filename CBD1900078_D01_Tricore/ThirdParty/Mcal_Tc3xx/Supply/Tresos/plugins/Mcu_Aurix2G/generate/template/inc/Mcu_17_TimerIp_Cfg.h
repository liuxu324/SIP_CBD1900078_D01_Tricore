[!/*****************************************************************************
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
**  FILENAME  : Mcu_17_TimerIp_Cfg.h                                          **
**                                                                            **
**  VERSION   : 6.0.0                                                         **
**                                                                            **
**  DATE      : 2018-07-10                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Mcu.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID=]                                          **
**                                                                            **
**  DESCRIPTION  : Timer IP template header file for Mcu Driver               **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!][!//
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
**  FILENAME  : Mcu_17_TimerIp_Cfg.h                                          **
**                                                                            **
**  VERSION   : 6.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                                      **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                                          **
**                                                                            **
**  BSW MODULE DECRIPTION : Mcu.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Timer IPs configuration file generated by Mcu module       **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
[!/*[cover parentID={4F530B06-BC6F-45e0-B9F2-765750A472FE}][/cover]*/!]
[!/*[cover parentID={E1A714C5-C032-47c4-B181-EEF638ECA1CE}][/cover]*/!]
#ifndef MCU_17_TIMERIP_CFG_H
#define MCU_17_TIMERIP_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Std_Types.h"
#include "Mcu_Cfg.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
[!/* Select MODULE-CONFIGURATION as context-node */!]
[!NOCODE!][!//
[!SELECT "as:modconf('Mcu')[1]"!][!//
[!VAR "AdcUser" = "num:i(0)"!][!//
[!VAR "WdgUser" = "num:i(0)"!][!//
[!VAR "StmUser" = "num:i(0)"!][!//
[!VAR "PwmUser" = "num:i(0)"!][!//
[!VAR "GptUser" = "num:i(0)"!][!//
[!VAR "OcuUser" = "num:i(0)"!][!//
[!VAR "IcuUser" = "num:i(0)"!][!//
[!VAR "DsadcUser" = "num:i(0)"!][!//

[!IF "ecu:get('Gtm.Available')='true'"!][!//
  [!SELECT "./McuHardwareResourceAllocationConf/*[1]/McuGtmAllocationConf/*[1]"!][!//
    [!VAR "TomCount" = "num:i(ecu:get('Gtm.NumberOfTomModules'))"!][!//
    [!VAR "TomChCount" = "num:i(ecu:get('Gtm.NumberOfTomChannels'))"!][!//
    [!VAR "AtomCount" = "num:i(ecu:get('Gtm.NumberOfAtomModules'))"!][!//
    [!VAR "AtomChCount" = "num:i(ecu:get('Gtm.NumberOfAtomChannels'))"!][!//
    [!VAR "TimCount" = "num:i(ecu:get('Gtm.NumberOfTimModules'))"!][!//
    [!VAR "TimChCount" = "num:i(ecu:get('Gtm.NumberOfTimChannels'))"!][!//
    [!IF "$TimCount > num:i(0)"!][!//
      [!IF "node:containsValue(./*/*/McuGtmTimChannelAllocationConf/*/McuGtmTimChannelAllocationConf, 'GTM_TIM_CHANNEL_USED_BY_ICU') = 'true'"!][!//
        [!VAR "IcuUser" = "num:i($IcuUser+1)"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!IF "$TomCount > num:i(0)"!][!//
      [!IF "node:containsValue(./*/*/McuGtmTomChannelAllocationConf/*/McuGtmTomChannelAllocationConf, 'GTM_TOM_CHANNEL_USED_BY_ADC') = 'true'"!][!//
        [!VAR "AdcUser" = "num:i($AdcUser+1)"!][!//
      [!ENDIF!][!//
      [!IF "node:containsValue(./*/*/McuGtmTomChannelAllocationConf/*/McuGtmTomChannelAllocationConf, 'GTM_TOM_CHANNEL_USED_BY_WDG') = 'true'"!][!//
        [!VAR "WdgUser" = "num:i($WdgUser+1)"!][!//
      [!ENDIF!][!//
      [!IF "node:containsValue(./*/*/McuGtmTomChannelAllocationConf/*/McuGtmTomChannelAllocationConf, 'GTM_TOM_CHANNEL_USED_BY_PWM') = 'true'"!][!//
        [!VAR "PwmUser" = "num:i($PwmUser+1)"!][!//
      [!ENDIF!][!//
      [!IF "node:containsValue(./*/*/McuGtmTomChannelAllocationConf/*/McuGtmTomChannelAllocationConf, 'GTM_TOM_CHANNEL_USED_BY_GPT') = 'true'"!][!//
        [!VAR "GptUser" = "num:i($GptUser+1)"!][!//
      [!ENDIF!][!//
      [!IF "node:containsValue(./*/*/McuGtmTomChannelAllocationConf/*/McuGtmTomChannelAllocationConf, 'GTM_TOM_CHANNEL_USED_BY_OCU') = 'true'"!][!//
        [!VAR "OcuUser" = "num:i($OcuUser+1)"!][!//
      [!ENDIF!][!//
      [!IF "node:containsValue(./*/*/McuGtmTomChannelAllocationConf/*/McuGtmTomChannelAllocationConf, 'GTM_TOM_CHANNEL_USED_BY_DSADC') = 'true'"!][!//
        [!VAR "DsadcUser" = "num:i($DsadcUser+1)"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!IF "$AtomCount > num:i(0)"!][!//
      [!IF "node:containsValue(./*/*/McuGtmAtomChannelAllocationConf/*/McuGtmAtomChannelAllocationConf, 'GTM_ATOM_CHANNEL_USED_BY_ADC') = 'true'"!][!//
        [!VAR "AdcUser" = "num:i($AdcUser+1)"!][!//
      [!ENDIF!][!//
      [!IF "node:containsValue(./*/*/McuGtmAtomChannelAllocationConf/*/McuGtmAtomChannelAllocationConf, 'GTM_ATOM_CHANNEL_USED_BY_WDG') = 'true'"!][!//
        [!VAR "WdgUser" = "num:i($WdgUser+1)"!][!//
      [!ENDIF!][!//
      [!IF "node:containsValue(./*/*/McuGtmAtomChannelAllocationConf/*/McuGtmAtomChannelAllocationConf, 'GTM_ATOM_CHANNEL_USED_BY_PWM') = 'true'"!][!//
        [!VAR "PwmUser" = "num:i($PwmUser+1)"!][!//
      [!ENDIF!][!//
      [!IF "node:containsValue(./*/*/McuGtmAtomChannelAllocationConf/*/McuGtmAtomChannelAllocationConf, 'GTM_ATOM_CHANNEL_USED_BY_GPT') = 'true'"!][!//
        [!VAR "GptUser" = "num:i($GptUser+1)"!][!//
      [!ENDIF!][!//
      [!IF "node:containsValue(./*/*/McuGtmAtomChannelAllocationConf/*/McuGtmAtomChannelAllocationConf, 'GTM_ATOM_CHANNEL_USED_BY_OCU') = 'true'"!][!//
        [!VAR "OcuUser" = "num:i($OcuUser+1)"!][!//
      [!ENDIF!][!//
      [!IF "node:containsValue(./*/*/McuGtmAtomChannelAllocationConf/*/McuGtmAtomChannelAllocationConf, 'GTM_ATOM_CHANNEL_USED_BY_DSADC') = 'true'"!][!//
        [!VAR "DsadcUser" = "num:i($DsadcUser+1)"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDSELECT!][!//
[!ENDIF!][!//

[!IF "ecu:get('Ccu6.Available') = 'true'"!][!//
  [!SELECT "./McuHardwareResourceAllocationConf/*[1]/McuCcu6ModuleAllocationConf"!][!//
    [!IF "node:containsValue(./*/McuCcu6ModuleAllocationConf, 'CCU6_MODULE_USED_BY_ICU_DRIVER') = 'true'"!][!//
      [!VAR "IcuUser" = "num:i($IcuUser+1)"!][!//
    [!ENDIF!][!//
    [!IF "node:containsValue(./*/McuCcu6ModuleAllocationConf, 'CCU6_MODULE_USED_BY_PWM_DRIVER') = 'true'"!][!//
      [!VAR "PwmUser" = "num:i($PwmUser+1)"!][!//
    [!ENDIF!][!//
    [!IF "node:containsValue(./*/McuCcu6ModuleAllocationConf, 'CCU6_MODULE_USED_BY_ADC_DRIVER') = 'true'"!][!//
      [!VAR "AdcUser" = "num:i($AdcUser+1)"!][!//
    [!ENDIF!][!//
  [!ENDSELECT!][!//
[!ENDIF!][!//

[!IF "ecu:get('Gpt12.Available') = 'true'"!][!//
  [!SELECT "./McuHardwareResourceAllocationConf/*[1]/McuGpt12ModuleAllocationConf"!][!//
    [!IF "node:containsValue(./*/McuGpt12ModuleAllocationConf, 'GPT_BLOCK_USED_BY_ICU_DRIVER') = 'true'"!][!//
      [!VAR "IcuUser" = "num:i($IcuUser+1)"!][!//
    [!ENDIF!][!//
  [!ENDSELECT!][!//
[!ENDIF!][!//

[!SELECT "./McuHardwareResourceAllocationConf/*[1]/McuEruAllocationConf"!][!//
  [!IF "node:containsValue(./*[1]/*/*/McuEruChannelInputLineConf, 'ERU_CHANNEL_INP_USED_BY_ADC_DRIVER') = 'true'"!][!//
    [!VAR "AdcUser" = "num:i($AdcUser+1)"!][!//
  [!ENDIF!][!//
  [!IF "node:containsValue(./*[1]/*/*/McuEruChannelInputLineConf, 'ERU_CHANNEL_INP_USED_BY_ICU_DRIVER') = 'true'"!][!//
    [!VAR "IcuUser" = "num:i($IcuUser+1)"!][!//
  [!ENDIF!][!//
  [!IF "node:containsValue(./*[1]/*/*/McuEruChannelInputLineConf, 'ERU_CHANNEL_INP_USED_BY_OCU_DRIVER') = 'true'"!][!//
    [!VAR "OcuUser" = "num:i($OcuUser+1)"!][!//
  [!ENDIF!][!//
  [!IF "node:containsValue(./*[1]/*/*/McuEruChannelInputLineConf, 'ERU_CHANNEL_INP_USED_BY_DSADC_DRIVER') = 'true'"!][!//
    [!VAR "DsadcUser" = "num:i($DsadcUser+1)"!][!//
  [!ENDIF!][!//
  [!IF "node:containsValue(./*[1]/*/*/McuEruChannelOutputUnitConf, 'ERU_CHANNEL_INP_USED_BY_ADC_DRIVER') = 'true'"!][!//
    [!VAR "AdcUser" = "num:i($AdcUser+1)"!][!//
  [!ENDIF!][!//
  [!IF "node:containsValue(./*[1]/*/*/McuEruChannelOutputUnitConf, 'ERU_CHANNEL_INP_USED_BY_ICU_DRIVER') = 'true'"!][!//
    [!VAR "IcuUser" = "num:i($IcuUser+1)"!][!//
  [!ENDIF!][!//
  [!IF "node:containsValue(./*[1]/*/*/McuEruChannelOutputUnitConf, 'ERU_CHANNEL_INP_USED_BY_OCU_DRIVER') = 'true'"!][!//
    [!VAR "OcuUser" = "num:i($OcuUser+1)"!][!//
  [!ENDIF!][!//
  [!IF "node:containsValue(./*[1]/*/*/McuEruChannelOutputUnitConf, 'ERU_CHANNEL_INP_USED_BY_DSADC_DRIVER') = 'true'"!][!//
    [!VAR "DsadcUser" = "num:i($DsadcUser+1)"!][!//
  [!ENDIF!][!//
[!ENDSELECT!][!//

[!SELECT "./McuHardwareResourceAllocationConf/*[1]/McuStmAllocationConf"!][!//
  [!IF "node:containsValue(./*/McuStmCmp0RegAllocationConf, 'STM_CMP0_USED_BY_WDG') = 'true'"!][!//
    [!VAR "WdgUser" = "num:i($WdgUser+1)"!][!//
  [!ELSEIF "node:containsValue(./*/McuStmCmp0RegAllocationConf, 'STM_CMP0_USED_BY_STM') = 'true'"!][!//
    [!VAR "StmUser" = "num:i($StmUser+1)"!][!//
  [!ENDIF!][!//
  [!IF "node:containsValue(./*/McuStmCmp1RegAllocationConf, 'STM_CMP1_USED_BY_WDG') = 'true'"!][!//
    [!VAR "WdgUser" = "num:i($WdgUser+1)"!][!//
  [!ELSEIF "node:containsValue(./*/McuStmCmp0RegAllocationConf, 'STM_CMP1_USED_BY_STM') = 'true'"!][!//
    [!VAR "StmUser" = "num:i($StmUser+1)"!][!//
  [!ENDIF!][!//
[!ENDSELECT!][!//

[!ENDSELECT!][!//
[!ENDNOCODE!][!//
[!IF "ecu:get('Gtm.Available')='true'"!][!//
#define MCU_17_GTM_NO_OF_TIM_MODULES              ([!"num:inttohex(ecu:get('Gtm.NumberOfTimModules'))"!]U)
#define MCU_17_GTM_NO_OF_TIM_CHANNELS             ([!"num:inttohex(ecu:get('Gtm.NumberOfTimChannels'))"!]U)

#define MCU_17_GTM_NO_OF_TOM_MODULES              ([!"num:inttohex(ecu:get('Gtm.NumberOfTomModules'))"!]U)
#define MCU_17_GTM_NO_OF_TOM_CHANNELS             ([!"num:inttohex(ecu:get('Gtm.NumberOfTomChannels'))"!]U)
#define MCU_17_GTM_NO_OF_TOM_TGC                  ([!"num:inttohex(ecu:get('Gtm.NumberOfTGCPerTom'))"!]U)

#define MCU_17_GTM_NO_OF_ATOM_MODULES             ([!"num:inttohex(ecu:get('Gtm.NumberOfAtomModules'))"!]U)
#define MCU_17_GTM_NO_OF_ATOM_CHANNELS            ([!"num:inttohex(ecu:get('Gtm.NumberOfAtomChannels'))"!]U)
#define MCU_17_GTM_NO_OF_ATOM_AGC                 ([!"num:inttohex(ecu:get('Gtm.NumberOfAgcPerAtom'))"!]U)
[!ENDIF!][!//
#define MCU_17_CCU6_NO_OF_KERNELS                 ([!"num:inttohex(ecu:get('Ccu6.MaxKernals'))"!]U)
#define MCU_17_CCU6_NO_OF_COMPARATORS             ([!"num:inttohex(ecu:get('Ccu6.MaxComparatorsPerKernel'))"!]U)
#define MCU_17_GPT12_NO_OF_TIMERS                 ([!"num:inttohex(ecu:get('Gpt12.MaxTimers'))"!]U)
#define MCU_17_ERU_NO_OF_OGU                      ([!"num:inttohex(ecu:get('Eru.NoOfEruOutputChannels'))"!]U)
#define MCU_17_STM_NO_OF_TIMERS                   ([!"num:inttohex(ecu:get('Stm.TotalNumberofcores'))"!]U)

[!/*[cover parentID= {83C0C6DB-9053-40ab-96DC-1621E29F4AF2}][/cover]*/!][!//
[!IF "$AdcUser > num:i(0)"!][!//
#define MCU_17_TIMERIP_ADC_USER       (STD_ON)
[!ELSE!][!//
#define MCU_17_TIMERIP_ADC_USER       (STD_OFF)
[!ENDIF!][!//
[!/*[cover parentID= {B5A40752-CD16-43cb-A31D-A933C9075393}][/cover]*/!][!//
[!IF "$WdgUser > num:i(0)"!][!//
#define MCU_17_TIMERIP_WDG_USER       (STD_ON)
[!ELSE!][!//
#define MCU_17_TIMERIP_WDG_USER       (STD_OFF)
[!ENDIF!][!//
[!/*[cover parentID= {8FE7A929-836E-40f8-9471-CEF3EDAE3BC6}]*/!][!//
[!IF "$PwmUser > num:i(0)"!][!//
#define MCU_17_TIMERIP_PWM_USER       (STD_ON)
[!ELSE!][!//
#define MCU_17_TIMERIP_PWM_USER       (STD_OFF)
[!ENDIF!][!//
[!/*[/cover]*/!][!//
[!/*[cover parentID= {C3862AC7-3DEF-4e11-B020-8762314C1F71}][/cover]*/!][!//
[!IF "$GptUser > num:i(0)"!][!//
#define MCU_17_TIMERIP_GPT_USER       (STD_ON)
[!ELSE!][!//
#define MCU_17_TIMERIP_GPT_USER       (STD_OFF)
[!ENDIF!][!//
[!/*[cover parentID= {F1FD2C67-393F-4cd3-AD8F-B526E5135CF2}][/cover]*/!][!//
[!IF "$OcuUser > num:i(0)"!][!//
#define MCU_17_TIMERIP_OCU_USER       (STD_ON)
[!ELSE!][!//
#define MCU_17_TIMERIP_OCU_USER       (STD_OFF)
[!ENDIF!][!//
[!/*[cover parentID= {92C35242-A26F-4793-B176-B59C12D1FA88}][/cover]*/!][!//
[!IF "$IcuUser > num:i(0)"!][!//
#define MCU_17_TIMERIP_ICU_USER       (STD_ON)
[!ELSE!][!//
#define MCU_17_TIMERIP_ICU_USER       (STD_OFF)
[!ENDIF!][!//
[!/*[cover parentID= {023B98B1-85F2-4905-AE33-4DE33510AF7F}][/cover]*/!][!//
[!IF "$DsadcUser > num:i(0)"!][!//
#define MCU_17_TIMERIP_DSADC_USER     (STD_ON)
[!ELSE!][!//
#define MCU_17_TIMERIP_DSADC_USER     (STD_OFF)
[!ENDIF!][!//
[!IF "$StmUser > num:i(0)"!][!//
#define MCU_17_TIMERIP_STM_USER       (STD_ON)
[!ELSE!][!//
#define MCU_17_TIMERIP_STM_USER       (STD_OFF)
[!ENDIF!][!//

#endif /* end of MCU_17_TIMERIP_CFG_H */
