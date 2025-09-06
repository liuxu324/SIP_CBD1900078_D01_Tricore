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
**  FILENAME  : Adc_PBcfg.c                                                   **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE      : 2018-09-11                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Adc.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={81FD6066-3472-4246-A659-CC828B57C140}]    **
**                                                                            **
**  DESCRIPTION  : Code template source file for Adc Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Adc Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*************************************************************************/!][!//
[!//
/*****************************************************************************
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
**  FILENAME  : Adc_PBcfg.c                                                   **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                                          **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                                            **
**                                                                            **
**  BSW MODULE DECRIPTION : Adc.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION :  Adc configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of ADC Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Inclusion of module header file */
/* [cover parentID={B2A31D0F-3CF7-47d9-BD9E-36AE5295CFEF}] */
#include "Adc.h"
/* [/cover] */
[!//
[!NOCODE!][!//
[!INCLUDE "Adc.m"!][!//
[!ENDNOCODE!][!//
[!//
[!NOCODE!][!//
[!/*[cover parentID={DE6EB695-89E0-4a47-B354-EFE3CADF580B}]Imported Interfaces [/cover] */!][!//
[!/*[cover parentID={13507698-914A-4299-8995-F5090DA46256}]Dependent Module Checks[/cover] */!][!//
[!IF "not(node:exists(as:modconf('ResourceM')[1]))"!]
  [!ERROR!][!//
    ADC Code Generator: ResourceM module is not added to the project.
  [!ENDERROR!][!//
[!ENDIF!]

[!IF "not(node:exists(as:modconf('Mcu')[1]))"!]
  [!ERROR!][!//
    ADC Code Generator: Mcu module is not added to the project.
  [!ENDERROR!][!//
[!ENDIF!]


[!VAR "AdcConfigShortName"="'_Config'"!][!//
[!SELECT "as:modconf('EcuC')[1]"!][!//
[!IF "node:exists(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!][!//
  [!VAR "PredefinedVarName" = "(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!][!//
  [!VAR "AdcConfigShortName" = "text:split($PredefinedVarName,'/')[4]"!][!//
  [!VAR "AdcConfigShortName" = "concat('_Config_',$AdcConfigShortName)"!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!//
[!ENDNOCODE!][!//
[!//
[!//
[!SELECT "as:modconf('Adc')[1]"!][!//
[!AUTOSPACING!]
[!//
[!NOCODE!]
[!VAR "CGCoreUsed" = "''"!][!//
[!VAR "CGModuleMap" = "''"!][!//
[!VAR "CGAllocatedResources" = "''"!][!//
[!VAR "CGMasterCoreId" = "''"!][!//
[!CALL "Adc_GenerateModuleMap", "Module"="'ADC'"!][!//
[!LOOP "AdcConfigSet/AdcHwUnit/*"!][!//
  [!/* Append the missing resources to master core */!][!//
  [!CALL "Adc_ValidateChAllocation", "Item" = "node:name(node:current())"!][!//
  [!IF "$CGResult = 'FALSE'"!][!//
    [!VAR "CGModuleMap" = "concat($CGModuleMap, 'CORE', $CGMasterCoreId, '_', node:name(node:current()), ',')"!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!]
[!//
[!LOOP "AdcConfigSet/AdcHwUnit/*"!][!//
  [!LOOP "AdcGroup/*"!][!//
    [!IF "node:exists(AdcNotification/*[1])"!][!//
      [!IF "not(num:isnumber(AdcNotification/*[1]))"!][!//
        [!IF "node:value(AdcNotification/*[1])!='NULL' and node:value(AdcNotification/*[1])!='NULL_PTR'"!][!//
          [!WS"0"!]/*Function declaration for Notification Function of [!"@name"!]*/
          [!WS"0"!]extern void [!"(AdcNotification/*[1])"!](void);
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
[!ENDLOOP!][!//

[!NOCODE!]
[!VAR "SyncGrpA" = "num:i(0)"!][!//
[!VAR "SyncGrpAMaster" = "num:i(255)"!][!//
[!VAR "SyncGrpASlave" = "num:i(0)"!][!//
[!VAR "SyncGrpACore" = "num:i(255)"!][!//
[!VAR "SyncGrpB" = "num:i(0)"!][!//
[!VAR "SyncGrpBMaster" = "num:i(255)"!][!//
[!VAR "SyncGrpBSlave" = "num:i(0)"!][!//
[!VAR "SyncGrpBCore" = "num:i(255)"!][!//
[!VAR "SyncGrpC" = "num:i(0)"!][!//
[!VAR "SyncGrpCMaster" = "num:i(255)"!][!//
[!VAR "SyncGrpCSlave" = "num:i(0)"!][!//
[!VAR "SyncGrpCCore" = "num:i(255)"!][!//

[!LOOP "AdcConfigSet/AdcHwUnit/*"!][!//
  [!VAR "AdcHwId" = "num:i(text:split(AdcHwUnitId,'_ADC')[2])"!]
  [!IF "$AdcHwId >= num:i(0) and $AdcHwId <= num:i(3)"!]
    [!IF "AdcSyncConvMode = 'ADC_SYNC_MASTER'"!]
      [!IF "num:i($SyncGrpAMaster) != num:i(255)"!]
        [!ERROR!]
ADC Code Generator:  Only one master per synchronization group allowed.
        [!ENDERROR!]
      [!ENDIF!]
      [!VAR "SyncGrpAMaster" = "num:i($AdcHwId)"!]
      [!VAR "SyncGrpA" = "bit:or($SyncGrpA, bit:shl(1,$AdcHwId))"!]
      [!CALL "Adc_GetHwUnitCoreId", "ModuleMap"="$CGModuleMap", "Item" = "node:name(node:current())"!]
      [!VAR "SyncGrpACore" = "$HwUnitCoreId"!]
    [!ELSEIF "AdcSyncConvMode = 'ADC_SYNC_SLAVE'"!]
      [!VAR "SyncGrpASlave" = "bit:or($SyncGrpASlave, bit:shl(1,$AdcHwId))"!]
      [!VAR "SyncGrpA" = "bit:or($SyncGrpA, bit:shl(1,$AdcHwId))"!]
    [!ENDIF!]

  [!ELSEIF "$AdcHwId >= num:i(4) and $AdcHwId <= num:i(7)"!]
    [!IF "AdcSyncConvMode = 'ADC_SYNC_MASTER'"!]
      [!IF "num:i($SyncGrpBMaster) != num:i(255)"!]
        [!ERROR!]
ADC Code Generator:  Only one master per synchronization group allowed.
        [!ENDERROR!]
      [!ENDIF!]
      [!VAR "SyncGrpBMaster" = "num:i($AdcHwId)"!]
      [!VAR "SyncGrpB" = "bit:or($SyncGrpB, bit:shl(1,$AdcHwId))"!]
      [!CALL "Adc_GetHwUnitCoreId", "ModuleMap"="$CGModuleMap", "Item" = "node:name(node:current())"!]
      [!VAR "SyncGrpBCore" = "$HwUnitCoreId"!]
    [!ELSEIF "AdcSyncConvMode = 'ADC_SYNC_SLAVE'"!]
      [!VAR "SyncGrpBSlave" = "bit:or($SyncGrpBSlave, bit:shl(1,$AdcHwId))"!]
      [!VAR "SyncGrpB" = "bit:or($SyncGrpB, bit:shl(1,$AdcHwId))"!]
    [!ENDIF!]

  [!ELSEIF "$AdcHwId >= num:i(8) and $AdcHwId <= num:i(11)"!]
    [!IF "AdcSyncConvMode = 'ADC_SYNC_MASTER'"!]
      [!IF "num:i($SyncGrpCMaster) != num:i(255)"!]
        [!ERROR!]
ADC Code Generator:  Only one master per synchronization group allowed.
        [!ENDERROR!]
      [!ENDIF!]
      [!VAR "SyncGrpCMaster" = "num:i($AdcHwId)"!]
      [!VAR "SyncGrpC" = "bit:or($SyncGrpC, bit:shl(1,$AdcHwId))"!]
      [!CALL "Adc_GetHwUnitCoreId", "ModuleMap"="$CGModuleMap", "Item" = "node:name(node:current())"!]
      [!VAR "SyncGrpCCore" = "$HwUnitCoreId"!]
    [!ELSEIF "AdcSyncConvMode = 'ADC_SYNC_SLAVE'"!]
      [!VAR "SyncGrpCSlave" = "bit:or($SyncGrpCSlave, bit:shl(1,$AdcHwId))"!]
      [!VAR "SyncGrpC" = "bit:or($SyncGrpC, bit:shl(1,$AdcHwId))"!]
    [!ENDIF!]
  [!ENDIF!]
[!ENDLOOP!][!//

[!ENDNOCODE!]
[!/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]Configuration Memory section as per AS [/cover] */!][!//
/***********Configuration for External HW trigger and gating signals***********/
[!VAR "AdcHwUnitCount" = "num:i(count(AdcConfigSet/AdcHwUnit/*))"!][!//
[!FOR "HwUnitIdx" ="num:i(1)" TO "num:i($AdcHwUnitCount)"!][!//
[!SELECT "AdcConfigSet/AdcHwUnit/*[num:i($HwUnitIdx)]"!][!//
[!CALL "Adc_GetHwUnitCoreId", "ModuleMap"="$CGModuleMap", "Item" = "node:name(node:current())"!][!//
[!VAR "AdcHwId" = "num:i(text:split(AdcHwUnitId,'_ADC')[2])"!][!//
[!LOOP "node:order(./AdcGroup/*, './AdcGroupId')"!][!//
[!//
[!IF "AdcGroupTriggSrc = 'ADC_TRIGG_SRC_HW' and (contains(AdcHwExtTrigSelect,'ERUIOUT') = 'true')"!]
/*Eru Trigger Configuration for [!"@name"!] of HW Unit [!"num:i($AdcHwId)"!]*/
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
[!/* [cover parentID={6B89CB2C-D732-4934-9783-3C2522C66736}]Start memory map section for ERU Trig Configuration structure[/cover] */!][!//
#define ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($HwUnitCoreId)"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"
[!VAR "EruEicrCfg" = "num:i(0)"!][!//
[!VAR "EruIgcrCfg" = "bit:shl(1,14)"!][!//
[!VAR "ErsInputPin" = "num:i(text:split(./EruTriggerConfig/*[1]/AdcEruErsInputPin,'_SEL')[2])"!]
[!VAR "ErsChannel" = "num:i(substring-after(./EruTriggerConfig/*[1]/AdcEruErsRef,'McuEruChannelInputLineConf_'))"!][!//
[!VAR "OguChannel" = "num:i(substring-after(./EruTriggerConfig/*[1]/AdcEruOguRef,'McuEruChannelOutputUnitConf_'))"!][!//
[!VAR "EruEicrCfg" = "bit:or(bit:shl(num:i($OguChannel),12), bit:shl(num:i($ErsInputPin),4))"!][!//
[!VAR "EruEicrCfg" = "bit:or($EruEicrCfg, bit:shl(1,11))"!][!//
[!IF "AdcHwTrigSignal/*[1] = 'ADC_HW_TRIG_RISING_EDGE'"!][!//
  [!VAR "EruEicrCfg" = "bit:or($EruEicrCfg, bit:shl(1,9))"!][!//
[!ELSEIF "AdcHwTrigSignal/*[1] = 'ADC_HW_TRIG_FALLING_EDGE'"!][!//
  [!VAR "EruEicrCfg" = "bit:or($EruEicrCfg, bit:shl(1,8))"!][!//
[!ELSE!][!//
  [!VAR "EruEicrCfg" = "bit:or($EruEicrCfg, bit:shl(3,8))"!][!//
[!ENDIF!][!//
[!/* [cover parentID={A2C2A7BA-4190-4709-8A59-009F661BBB7A}]Adc_kHwUnit[x]Grp[Symbolic Name]EruTrig_Config[_Variant][/cover] */!][!//
static const Adc_EruChannelCfgType Adc_kHwUnit[!"num:i($AdcHwId)"!]Grp[!"@name"!]EruTrig[!"$AdcConfigShortName"!]=
{
  [!"num:inttohex($EruEicrCfg,4)"!]U, /*EICR register configuration*/
  [!"num:inttohex($EruIgcrCfg,4)"!]U, /*IGCR register configuration*/
  [!"num:i($ErsChannel)"!]U, /*ERS channel*/
  [!"num:i($OguChannel)"!]U /*OGU channel*/
};
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
[!/* [cover parentID={4E5D45E1-C061-4f6e-904B-9217D2E48B14}]Stop memory map section for ERU Trig Configuration structure[/cover] */!][!//
#define ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($HwUnitCoreId)"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"

[!IF "node:ref(./EruTriggerConfig/*[1]/AdcEruErsRef)/McuEruChannelInputLineConf != 'ERU_CHANNEL_INP_USED_BY_ADC_DRIVER'"!][!//
  [!ERROR!][!//
    ADC Code Generator: The ERU channel configured at [!"@name"!]/EruTriggerConfig/AdcEruErsRef is not reserved for ADC in the MCU container - [!"./EruTriggerConfig/*[1]/AdcEruErsRef"!]
  [!ENDERROR!][!//
[!ENDIF!][!//
[!//
[!IF "node:ref(./EruTriggerConfig/*[1]/AdcEruOguRef)/McuEruChannelOutputUnitConf != 'ERU_CHANNEL_OUT_USED_BY_ADC_DRIVER'"!][!//
  [!ERROR!][!//
    ADC Code Generator: The ERU channel configured at [!"@name"!]/EruTriggerConfig/AdcEruOguRef is not reserved for ADC in the MCU container - [!"./EruTriggerConfig/*[1]/AdcEruOguRef"!]
  [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!//
[!IF "AdcGroupTriggSrc = 'ADC_TRIGG_SRC_HW' and (contains(AdcHwExtTrigSelect,'_GTM_') = 'true')"!][!//
/*Gtm Trigger Configuration for [!"@name"!] of HW Unit [!"num:i($AdcHwId)"!] */
/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
[!/* [cover parentID={1B666336-84B3-40ef-B7C8-A6C0A821B514}]Start memory map section for GTM Trig Configuration structure[/cover] */!][!//   
#define ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($HwUnitCoreId)"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"

[!VAR "TomChCtrlReg" = "num:i(0)"!][!//
[!VAR "TomChCM0Reg" = "num:i(0)"!][!//
[!VAR "TomChIntEnMode" = "num:i(0)"!][!//
[!VAR "GtmTimerType" = "num:i(0)"!][!//
[!VAR "GtmTimerModNo" = "num:i(0)"!][!//
[!VAR "GtmTimerChNo" = "num:i(0)"!][!//
[!VAR "GtmTimerTicks" = "num:i(0)"!][!//
[!CALL "Adc_ConfigGetGtmParams","GtmChannelRef"= "GtmTriggerTimerConfig/*[1]/GtmTimerUsed",
"GtmTimePeriod"="GtmTriggerTimerConfig/*[1]/GtmTimerTimePeriod","GtmTimerContainer"="'./GtmTriggerTimerConfig/*[1]'",
"GtmClockRef"="../../../../AdcSystemClock",,"GtmTimerTicks"="$GtmTimerTicks",
"GtmTimerType"="$GtmTimerType","GtmTimerModNo"="$GtmTimerModNo","GtmTimerChNo"="$GtmTimerChNo"!][!//
[!IF "GtmTriggerTimerConfig/*[1]/GtmTimerCM0Ticks = num:i(0)"!][!//
  [!VAR "TomChCM0Reg" = "num:i($GtmTimerTicks)"!][!//
[!ELSE!][!/*CM0 ticks are directly available*/!][!//
  [!VAR "TomChCM0Reg" = "GtmTriggerTimerConfig/*[1]/GtmTimerCM0Ticks"!][!//
[!ENDIF!][!//
[!VAR "TomChCtrlReg" = "bit:or($TomChCtrlReg,bit:shl(substring-after((GtmTriggerTimerConfig/*[1]/GtmTimerClockSelect),'CLOCK_'),12))"!][!//
[!VAR "TomChCtrlReg" = "bit:or($TomChCtrlReg,bit:shl(1,11))"!][!//
[!IF "$GtmTimerType = 'ATOM'"!][!//
[!VAR "TomChCtrlReg" = "bit:or($TomChCtrlReg,num:i(2))"!][!//
[!ENDIF!]
[!/* [cover parentID={1780843B-3214-47bb-9950-CC55E4A418C0}]Adc_kHwUnit[x]Grp[Symbolic Name]GtmTrig_Config[_Variant][/cover] */!][!//
static const Mcu_17_Gtm_TomAtomChConfigType Adc_kHwUnit[!"num:i($AdcHwId)"!]Grp[!"@name"!]GtmTrig[!"$AdcConfigShortName"!]=
{
  [!IF "$GtmTimerType = 'ATOM'"!][!//
  MCU_GTM_TIMER_ATOM, /*GTM_[!"$GtmTimerType"!] Timer Type Used*/
  [!ELSE!][!//
  MCU_GTM_TIMER_TOM, /*GTM_[!"$GtmTimerType"!] Timer Type Used*/
  [!ENDIF!][!//
  [!"num:inttohex(bit:or(bit:shl($GtmTimerModNo,8),$GtmTimerChNo),8)"!]U, /* Timer ID */
  [!"num:inttohex($TomChCtrlReg,8)"!]U, /*Control Register Value for GTM_[!"$GtmTimerType"!]_[!"$GtmTimerModNo"!] */
  [!"num:inttohex(0,8)"!]U, /*CN0 Register value*/
  [!"num:inttohex($TomChCM0Reg,8)"!]U, /*CM0 register value*/
  [!"num:inttohex($TomChCM0Reg div num:i(2),8)"!]U, /*CM1 register value*/
  [!"num:inttohex($TomChCM0Reg,8)"!]U, /*SR0 register value*/
  [!"num:inttohex($TomChCM0Reg div num:i(2),8)"!]U, /*SR1 register value*/
  0U, /*Timer Channel output Config*/
  [!"num:inttohex($TomChIntEnMode,2)"!]U /*Interrupt Enable and Interrupt Mode values*/
};
/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
[!/* [cover parentID={D3A49C37-56BD-404c-B7F1-5ECF5B648E2F}]Stop memory map section for GTM Trig Configuration structure[/cover] */!][!//   
#define ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($HwUnitCoreId)"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"


[!ENDIF!][!//
[!IF "AdcGroupTriggSrc = 'ADC_TRIGG_SRC_HW' and (contains(AdcHwExtGateSelect,'ERUPDOUT') = 'true')"!][!//
/*Eru Gate Configuration for [!"@name"!] of HW Unit [!"num:i($AdcHwId)"!] */
/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
[!/* [cover parentID={EC8999F9-4125-437a-B619-281EB4161841}]Start memory map section for ERU Gate Configuration structure[/cover] */!][!//   
#define ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($HwUnitCoreId)"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"

[!VAR "EruEicrCfg" = "num:i(0)"!][!//
[!VAR "EruIgcrCfg" = "num:i(0)"!][!//
[!VAR "ErsInputPin" = "num:i(text:split(./EruGatingConfig/*[1]/AdcEruErsInputPin,'_SEL')[2])"!]
[!VAR "ErsChannel" = "num:i(substring-after(./EruGatingConfig/*[1]/AdcEruErsRef,'McuEruChannelInputLineConf_'))"!][!//
[!VAR "OguChannel" = "num:i(substring-after(./EruGatingConfig/*[1]/AdcEruOguRef,'McuEruChannelOutputUnitConf_'))"!][!//
[!VAR "EruEicrCfg" = "bit:shl(num:i($ErsInputPin),4)"!][!//
[!IF "AdcHwGateSignal = 'ADC_GATE_LVL_HIGH'"!]
  [!VAR "EruEicrCfg" = "bit:or($EruEicrCfg, bit:shl(1,9))"!][!//
[!ELSE!]
    [!VAR "EruEicrCfg" = "bit:or($EruEicrCfg, bit:shl(1,8))"!][!//
[!ENDIF!]
[!VAR "EruEicrCfg" = "bit:or($EruEicrCfg, bit:shl(1,10))"!][!//
[!VAR "EruIgcrCfg" = "bit:shl(1,$ErsChannel)"!][!//
[!/* [cover parentID={17D5E1AD-73CA-4163-AC7F-7AA307C62FFF}]Adc_kHwUnit[x]Grp[Symbolic Name]EruGate_Config[_Variant][/cover] */!][!//
static const Adc_EruChannelCfgType Adc_kHwUnit[!"num:i($AdcHwId)"!]Grp[!"@name"!]EruGate[!"$AdcConfigShortName"!]=
{
  [!"num:inttohex($EruEicrCfg,4)"!]U, /*EICR register configuration*/
  [!"num:inttohex($EruIgcrCfg,4)"!]U, /*IGCR register configuration*/
  [!"num:i($ErsChannel)"!]U, /*ERS channel*/
  [!"num:i($OguChannel)"!]U /*OGU channel*/
};
/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
[!/* [cover parentID={2D9E2035-24BB-4763-9840-55F55D05B9D1}]Stop memory map section for ERU Gate Configuration structure[/cover] */!][!//   
#define ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($HwUnitCoreId)"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"

[!IF "node:ref(./EruGatingConfig/*[1]/AdcEruErsRef)/McuEruChannelInputLineConf != 'ERU_CHANNEL_INP_USED_BY_ADC_DRIVER'"!][!//
  [!ERROR!][!//
    ADC Code Generator: The ERU channel configured at [!"@name"!]/EruGatingConfig/AdcEruErsRef is not reserved for ADC in the MCU container - [!"./EruGatingConfig/*[1]/AdcEruErsRef"!]
  [!ENDERROR!][!//
[!ENDIF!][!//
[!//
[!IF "node:ref(./EruGatingConfig/*[1]/AdcEruOguRef)/McuEruChannelOutputUnitConf != 'ERU_CHANNEL_OUT_USED_BY_ADC_DRIVER'"!][!//
  [!ERROR!][!//
    ADC Code Generator: The ERU channel configured at [!"@name"!]/EruGatingConfig/AdcEruOguRef is not reserved for ADC in the MCU container - [!"./EruGatingConfig/*[1]/AdcEruOguRef"!]
  [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "AdcGroupTriggSrc = 'ADC_TRIGG_SRC_HW' and (contains(AdcHwExtGateSelect,'_GTM_') = 'true')"!][!//
/*Gtm Gate Configuration for [!"@name"!] of HW Unit [!"num:i($AdcHwId)"!] */
/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
[!/* [cover parentID={09B611AE-AE47-4071-98C2-4E975B1FD3C8}]Start memory map section for GTM Gate Configuration structure[/cover] */!][!//   
#define ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($HwUnitCoreId)"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"

[!VAR "TomChCtrlReg" = "num:i(0)"!][!//
[!VAR "TomChCM0Reg" = "num:i(0)"!][!//
[!VAR "TomChIntEnMode" = "num:i(0)"!][!//
[!VAR "GtmTimerType" = "num:i(0)"!][!//
[!VAR "GtmTimerModNo" = "num:i(0)"!][!//
[!VAR "GtmTimerChNo" = "num:i(0)"!][!//
[!VAR "GtmTimerTicks" = "num:i(0)"!][!//
[!CALL "Adc_ConfigGetGtmParams","GtmChannelRef"= "GtmGatingTimerConfig/*[1]/GtmTimerUsed",
"GtmTimePeriod"="GtmGatingTimerConfig/*[1]/GtmTimerTimePeriod","GtmTimerContainer"="'./GtmGatingTimerConfig/*[1]'",
"GtmClockRef"="../../../../AdcSystemClock",,"GtmTimerTicks"="$GtmTimerTicks",
"GtmTimerType"="$GtmTimerType","GtmTimerModNo"="$GtmTimerModNo","GtmTimerChNo"="$GtmTimerChNo"!][!//
[!IF "GtmGatingTimerConfig/*[1]/GtmTimerCM0Ticks = num:i(0)"!][!//
  [!VAR "TomChCM0Reg" = "num:i($GtmTimerTicks)"!][!//
[!ELSE!][!/*CM0 ticks are directly available*/!][!//
  [!VAR "TomChCM0Reg" = "GtmGatingTimerConfig/*[1]/GtmTimerCM0Ticks"!][!//
[!ENDIF!][!//
[!VAR "TomChCtrlReg" = "bit:or($TomChCtrlReg,bit:shl(substring-after((GtmGatingTimerConfig/*[1]/GtmTimerClockSelect),'CLOCK_'),12))"!][!//
[!VAR "TomChCtrlReg" = "bit:or($TomChCtrlReg,bit:shl(1,11))"!][!//
[!IF "$GtmTimerType = 'ATOM'"!][!//
[!VAR "TomChCtrlReg" = "bit:or($TomChCtrlReg,num:i(2))"!][!//
[!ENDIF!]
[!/* [cover parentID={16189B91-4787-41e0-9AA5-4B6921644C22}]Adc_kHwUnit[x]Grp[Symbolic Name]GtmGate_Config[_Variant][/cover] */!][!//
static const Mcu_17_Gtm_TomAtomChConfigType Adc_kHwUnit[!"num:i($AdcHwId)"!]Grp[!"@name"!]GtmGate[!"$AdcConfigShortName"!]=
{
  [!IF "$GtmTimerType = 'ATOM'"!][!//
  MCU_GTM_TIMER_ATOM, /*GTM_[!"$GtmTimerType"!] Timer Type Used*/
  [!ELSE!][!//
  MCU_GTM_TIMER_TOM, /*GTM_[!"$GtmTimerType"!] Timer Type Used*/
  [!ENDIF!][!//
  [!"num:inttohex(bit:or(bit:shl($GtmTimerModNo,8),$GtmTimerChNo),8)"!]U, /* Timer ID */
  [!"num:inttohex($TomChCtrlReg,8)"!]U, /*Control Register Value for GTM_[!"$GtmTimerType"!]_[!"$GtmTimerModNo"!] */
  [!"num:inttohex(0,8)"!]U, /*CN0 Register value*/
  [!"num:inttohex($TomChCM0Reg,8)"!]U, /*CM0 register value*/
  [!"num:inttohex($TomChCM0Reg div num:i(2),8)"!]U, /*CM1 register value*/
  [!"num:inttohex($TomChCM0Reg,8)"!]U, /*SR0 register value*/
  [!"num:inttohex($TomChCM0Reg div num:i(2),8)"!]U, /*SR1 register value*/
  0U, /*Timer Channel output Config*/
  [!"num:inttohex($TomChIntEnMode,2)"!]U /*Interrupt Enable and Interrupt Mode values*/
};
/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
[!/* [cover parentID={97D8E534-F049-4e26-A801-87D0E74A8A39}]Stop memory map section for GTM Gate Configuration structure[/cover] */!][!//   
#define ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($HwUnitCoreId)"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"

[!ENDIF!][!//
[!ENDLOOP!][!//Loop End for Groups[!//
[!ENDSELECT!][!//
[!ENDFOR!][!//
[!//

/*******************Group Definition - Channel Sequence*******************/

[!VAR "AdcHwUnitCount" = "num:i(count(AdcConfigSet/AdcHwUnit/*))"!][!//
[!FOR "HwUnitIdx" ="num:i(1)" TO "num:i($AdcHwUnitCount)"!][!//
[!SELECT "AdcConfigSet/AdcHwUnit/*[num:i($HwUnitIdx)]"!][!//
[!CALL "Adc_GetHwUnitCoreId", "ModuleMap"="$CGModuleMap", "Item" = "node:name(node:current())"!][!//
[!VAR "AdcHwId" = "num:i(text:split(AdcHwUnitId,'_ADC')[2])"!][!//
[!VAR "AdcGroupCount" = "num:i(count(AdcGroup/*))"!][!//
[!LOOP "node:order(./AdcGroup/*, './AdcGroupId')"!][!//
[!VAR "AdcChannelCount" = "num:i(count(AdcGroupDefinition/*))"!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
[!/* [cover parentID={30B896AD-031E-4b05-9B3A-C7B9794FAD89}]Start memory map section for Group Channel sequence Configuration structure[/cover] */!][!//   
#define ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($HwUnitCoreId)"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"
/**Group Definition of [!"@name"!]- ID[!"./AdcGroupId"!] of HW Unit [!"num:i($AdcHwId)"!] */
[!/* [cover parentID={64825D49-CC0C-4395-BD3C-7BA988388F15}]Adc_kHwUnit[x]Grp[Symbolic Name]_Config[_Variant][y][/cover] */!][!//
static const Adc_GroupDefType Adc_kHwUnit[!"num:i($AdcHwId)"!]Grp[!"@name"!][!"$AdcConfigShortName"!][[!"$AdcChannelCount"!]]=
{
  /*AS Logical Channel*/ /*Analog Channel*/ /*Result Register*/
[!NOCODE!][!//
[!//START - Error check for Same analog channel with different input class cannot be configured in the same AdcGroup
[!VAR "ChannelIdx" = "num:i(0)"!][!//
[!FOR "ChannelIdx" ="num:i(1)" TO "num:i($AdcChannelCount)"!][!//
[!VAR "CurrentAnCh"="node:ref(AdcGroupDefinition/*[num:i($ChannelIdx)])/AdcAnChannelNum"!]
[!FOR "ChannelIdx1" ="num:i(1)" TO "num:i($AdcChannelCount)"!][!//
  [!IF "$ChannelIdx1!=$ChannelIdx"!]
    [!VAR "CheckCurrentAnCh"="node:ref(AdcGroupDefinition/*[num:i($ChannelIdx1)])/AdcAnChannelNum"!]
    [!IF "$CheckCurrentAnCh = $CurrentAnCh"!]
      [!ERROR!]
       ADC Code Generator: Same Analog Channel-[!"$CurrentAnCh"!] of HW Unit-[!"$AdcHwId"!] is repeated multiple times at the NODE: [!"node:path(.)"!]/AdcGroupDefinition.
      [!ENDERROR!]
    [!ENDIF!]
  [!ENDIF!]
[!ENDFOR!]
[!ENDFOR!]
[!//END - Error check for Same analog channel with different input class cannot be configured in the same AdcGroup
[!ENDNOCODE!][!//
[!//
[!VAR "AdcChannelCount" = "num:i(count(AdcGroupDefinition/*))"!][!//
[!VAR "ChannelIdx" = "num:i(0)"!][!//
[!FOR "ChannelIdx" ="num:i(1)" TO "num:i($AdcChannelCount)"!][!//
  [!VAR "TempNodeName" = "node:name(node:ref(AdcGroupDefinition/*[num:i($ChannelIdx)]))"!][!//
  [!VAR "AdcGrpAnChNum" = "num:i(0)"!]
  [!VAR "AdcGrpAsChNum" = "num:i(0)"!]
  [!LOOP "../../AdcChannel/*"!][!//
    [!IF "@name = $TempNodeName"!][!//
      [!VAR "AdcGrpAsChNum" = "AdcChannelId"!][!//
      [!VAR "AdcGrpAnChNum" = "text:split(AdcAnChannelNum,'CH')[2]"!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
  [!WS"2"!]{  [!"$AdcGrpAsChNum"!]U,                   [!"$AdcGrpAnChNum"!]U,                [!"AdcResRegDefinition/*[num:i($ChannelIdx)]"!]U  }[!IF "$ChannelIdx != num:i($AdcChannelCount)"!],[!ENDIF!][!//

[!ENDFOR!]
};
/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
[!/* [cover parentID={D7D98DF0-0215-4963-BF07-6791BD6F2240}]Stop memory map section for Group Channel sequence Configuration structure[/cover] */!][!//   
#define ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($HwUnitCoreId)"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"

[!ENDLOOP!]

[!ENDSELECT!][!//
[!ENDFOR!][!//
/***********************Group Configuration Definition***********************/
[!VAR "AdcHwUnitCount" = "num:i(count(AdcConfigSet/AdcHwUnit/*))"!][!//
[!FOR "HwUnitIdx" ="num:i(1)" TO "num:i($AdcHwUnitCount)"!][!//
[!SELECT "AdcConfigSet/AdcHwUnit/*[num:i($HwUnitIdx)]"!][!//
[!CALL "Adc_GetHwUnitCoreId", "ModuleMap"="$CGModuleMap", "Item" = "node:name(node:current())"!][!//
[!VAR "AdcHwId" = "num:i(text:split(AdcHwUnitId,'_ADC')[2])"!][!//
[!VAR "AdcGroupCount" = "num:i(count(AdcGroup/*))"!][!//
[!VAR "GroupIdx" = "num:i(0)"!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/ 
[!/* [cover parentID={999B62F7-08BE-4c9e-8AD8-ABC4DC0126C3}]Start memory map section for Group Configuration structure[/cover] */!][!//  
#define ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($HwUnitCoreId)"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"

/*****Group Configuration Definition of HW Unit [!"num:i($AdcHwId)"!] ******/
[!/* [cover parentID={5C537AAD-9B54-4740-B1E5-974B80FA3585}]Adc_kHwUnit[x]Grp_Config[_Variant][y][/cover] */!][!//
static const Adc_GroupCfgType Adc_kHwUnit[!"num:i($AdcHwId)"!]Grp[!"$AdcConfigShortName"!][[!"$AdcGroupCount"!]]=
{
[!LOOP "node:order(./AdcGroup/*, './AdcGroupId')"!][!//
[!/* [cover parentID={EA4597FA-5ABC-4241-995D-312B958022BC}]Generate Null pointer[/cover] */!][!//
[!VAR "AdcNotifyPtr" = "'(Adc_NotifyFnPtrType)0U'"!][!//
[!VAR "GtmTrigCfg" = "'0U'"!][!//
[!VAR "EruTrigCfg" = "'0U'"!][!//
[!VAR "AdcHwTrigType" = "'ADC_OTHER_HW_USED'"!][!//
[!VAR "GtmGateCfg" = "'0U'"!][!//
[!VAR "EruGateCfg" = "'0U'"!][!//
[!VAR "AdcHwGateType" = "'ADC_OTHER_HW_USED'"!][!//
[!VAR "AdcGroupQCtrlVal" = "num:i(0)"!][!//
[!VAR "AdcGroupQModeVal" = "num:i(0)"!][!//
[!VAR "AdcAliasChCfg" = "num:i(0)"!][!//
[!VAR "AdcChannelMask" = "num:i(0)"!][!//
[!VAR "AdcResultRegMask" = "num:i(0)"!][!//
[!VAR "AdcSyncChannelMask" = "num:i(0)"!][!//
[!VAR "AdcSyncResRegMask" = "num:i(0)"!][!//
[!VAR "AdcLimitCheckGrp" = "num:i(0)"!][!//
[!VAR "AdcPriotityLevel" = "num:i(0)"!][!//
[!VAR "AdcChannelCount" = "num:i(count(AdcGroupDefinition/*))"!][!//
[!VAR "AdcReqTmVal" = "num:i(0)"!][!//
[!VAR "AdcReqTmCfgVal" = "num:i(0)"!][!//

[!//
[!NOCODE!]
[!IF "node:exists(AdcNotification/*[1])"!][!//
  [!/* [cover parentID={CC5E98B6-CA62-4ffd-B4FF-ED6D5C3C6C66}]Generate Notification Function POinter[/cover] */!][!//
  [!IF "node:value(AdcNotification/*[1]) != '' and node:value(AdcNotification/*[1]) != ' ' and node:value(AdcNotification/*[1]) != 'NULL_PTR'"!][!//
    [!VAR "AdcNotifyPtr" = "node:value(AdcNotification/*[1])"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "AdcGroupTriggSrc='ADC_TRIGG_SRC_HW' and 
text:contains(node:value(AdcHwExtTrigSelect),'_GTM_' ) = 'true'"!][!//
  [!VAR "GtmTrigCfg" = "concat('&Adc_k','HwUnit',num:i($AdcHwId),'Grp',@name,'GtmTrig',$AdcConfigShortName)"!][!//
  [!VAR "AdcHwTrigType" = "'ADC_GTM_HW_USED'"!][!//
[!ELSEIF "AdcGroupTriggSrc='ADC_TRIGG_SRC_HW' and
text:contains(node:value(AdcHwExtTrigSelect),'ERUIOUT' ) = 'true'"!][!//
  [!VAR "EruTrigCfg" = "concat('&Adc_k','HwUnit',num:i($AdcHwId),'Grp',@name,'EruTrig',$AdcConfigShortName)"!][!//
  [!VAR "AdcHwTrigType" = "'ADC_ERU_HW_USED'"!][!//
[!ENDIF!][!//
[!//
[!IF "AdcGroupTriggSrc='ADC_TRIGG_SRC_HW' and 
text:contains(node:value(AdcHwExtGateSelect),'_GTM_' ) = 'true'"!][!//
  [!VAR "GtmGateCfg" = "concat('&Adc_k','HwUnit',num:i($AdcHwId),'Grp',@name,'GtmGate',$AdcConfigShortName)"!][!//
  [!VAR "AdcHwGateType" = "'ADC_GTM_HW_USED'"!][!//
[!ELSEIF "AdcGroupTriggSrc='ADC_TRIGG_SRC_HW' and 
text:contains(node:value(AdcHwExtGateSelect),'ERUPDOUT' ) = 'true'"!][!//
  [!VAR "EruGateCfg" = "concat('&Adc_k','HwUnit',num:i($AdcHwId),'Grp',@name,'EruGate',$AdcConfigShortName)"!][!//
  [!VAR "AdcHwGateType" = "'ADC_ERU_HW_USED'"!][!//
[!ENDIF!][!//
[!IF "AdcGroupTriggSrc='ADC_TRIGG_SRC_HW' and node:exists(./AdcHwTrigTimer/*[1])"!][!//
    [!VAR "AdcReqTmVal" = "node:value(./AdcHwTrigTimer/*[1])"!][!//
    [!IF "$AdcReqTmVal != num:i(0)"!][!//
      [!VAR "AdcReqTmCfgVal" = "bit:shl($AdcReqTmVal, 6)"!][!//
      [!VAR "AdcReqTmCfgVal" = "bit:or($AdcReqTmCfgVal, bit:shl($AdcReqTmCfgVal, 16))"!][!//
      [!VAR "AdcReqTmCfgVal" = "bit:or($AdcReqTmCfgVal, 3)"!][!//
    [!ENDIF!][!//
[!ENDIF!][!//
[!CALL "Adc_ConfigGroupQCtrlVal","GroupTriggSrc"= "AdcGroupTriggSrc",
"HwTrigSignal" ="./AdcHwTrigSignal/*[1]","HwExtTrigSelect"= "AdcHwExtTrigSelect",
"HwExtGateSelect"= "AdcHwExtGateSelect","HwGateSignal"= "AdcHwGateSignal",[!//
"ReqTimerVal"="$AdcReqTmVal","AdcGroupQCtrlVal"="$AdcGroupQCtrlVal"!][!//
[!CALL "Adc_ConfigGroupQModeVal","GroupTriggSrc"= "AdcGroupTriggSrc",
"HwTrigSignal" ="./AdcHwTrigSignal/*[1]","HwExtTrigSelect"= "AdcHwExtTrigSelect",
"HwExtGateSelect"= "AdcHwExtGateSelect","HwGateSignal"= "AdcHwGateSignal","ReqTimerVal"="$AdcReqTmVal",
"AdcGroupQModeVal"="$AdcGroupQModeVal"!][!//
[!VAR "ChannelIdx" = "num:i(0)"!][!//
[!FOR "ChannelIdx" ="num:i(1)" TO "num:i($AdcChannelCount)"!][!//
  [!VAR "TempNodeName" = "node:name(node:ref(AdcGroupDefinition/*[num:i($ChannelIdx)]))"!][!//
  [!VAR "TempSyncConvEnable" = "num:i(0)"!][!//
  [!LOOP "../../AdcChannel/*"!][!//
    [!VAR "AdcGrpAnChNum" = "'NONE'"!][!//
    [!IF "@name = $TempNodeName"!][!//
      [!VAR "AdcGrpAnChNum" = "text:split(AdcAnChannelNum,'CH')[2]"!][!//
      [!VAR "AdcChannelMask" = "bit:or($AdcChannelMask, bit:shl(1,$AdcGrpAnChNum))"!][!//
      [!IF "../../AdcSyncConvMode = 'ADC_SYNC_MASTER' and AdcSyncConvChannelEnable = 'true'"!][!//
        [!VAR "AdcSyncChannelMask" = "bit:or($AdcSyncChannelMask, bit:shl(1,$AdcGrpAnChNum))"!][!//
        [!VAR "TempSyncConvEnable" = "num:i(1)"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
  [!VAR "AdcResultRegMask" =" bit:or($AdcResultRegMask, bit:shl(1,node:value(AdcResRegDefinition/*[num:i($ChannelIdx)])))"!][!//
  [!IF "$TempSyncConvEnable = num:i(1)"!][!//
    [!VAR "AdcSyncResRegMask" = "bit:or($AdcSyncResRegMask,bit:shl(1,node:value(AdcResRegDefinition/*[num:i($ChannelIdx)])))"!][!//
  [!ENDIF!]
[!ENDFOR!][!//
[!//
[!VAR "ChannelIdx" = "num:i(0)"!][!//
[!FOR "ChannelIdx" ="num:i(1)" TO "num:i($AdcChannelCount)"!][!//
  [!IF "node:exists(node:ref(AdcGroupDefinition/*[num:i($ChannelIdx)])/AdcChannelLimitCheck/*[1])"!][!//
    [!IF "node:ref(AdcGroupDefinition/*[num:i($ChannelIdx)])/AdcChannelLimitCheck/*[1] = 'true'"!][!//
      [!VAR "AdcLimitCheckGrp" = "num:i(1)"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDFOR!][!//
[!IF "$AdcLimitCheckGrp = num:i(1) and $AdcChannelCount != num:i(1)"!][!//
  [!ERROR!][!//
    ADC Code Generator: A Limit checking group can have only one channel for conversion. [!"node:path(.)"!] contains more than one entires in AdcGroupDefinition.
  [!ENDERROR!][!//
[!ENDIF!][!//

[!IF "$AdcLimitCheckGrp = num:i(1) and AdcGroupTriggSrc = 'ADC_TRIGG_SRC_SW' and AdcGroupConversionMode = 'ADC_CONV_MODE_ONESHOT'"!][!//
  [!WARNING!][!//
    ADC Code Generator: A SW triggered, Limit checking group is configured in One Shot Mode at [!"node:path(.)"!]. 
    Conversion occurs only once and Group will stay in BUSY state if conversion result is not in the configured range.
  [!ENDWARNING!][!//
[!ENDIF!][!//

[!IF "AdcGroupTriggSrc = 'ADC_TRIGG_SRC_HW' and AdcGroupConversionMode = 'ADC_CONV_MODE_CONTINUOUS'"!][!//
  [!WARNING!][!//
    ADC Code Generator: A HW triggered group, is configured in ADC_CONV_MODE_CONTINUOUS mode at the node:[!"node:path(.)"!]. 
    HW triggered groups should only be configured in ADC_CONV_MODE_ONESHOT mode.
  [!ENDWARNING!][!//
[!ENDIF!][!//
[!IF "../../../../../AdcGeneral/AdcPriorityImplementation = 'ADC_PRIORITY_NONE'"!]
  [!VAR "AdcPriotityLevel" = "num:i(0)"!][!// 
[!ELSEIF "../../../../../AdcGeneral/AdcPriorityImplementation = 'ADC_PRIORITY_HW'"!]
  [!IF "./AdcGroupPriority/*[1] = num:i(255)"!]
    [!VAR "AdcPriotityLevel" = "num:i(2)"!][!// 
  [!ELSEIF "./AdcGroupPriority/*[1] = num:i(254)"!]
    [!VAR "AdcPriotityLevel" = "num:i(1)"!][!// 
  [!ELSE!]
    [!VAR "AdcPriotityLevel" = "num:i(0)"!][!// 
  [!ENDIF!]
[!ELSEIF "../../../../../AdcGeneral/AdcPriorityImplementation = 'ADC_PRIORITY_HW_SW'"!] 
    [!VAR "AdcPriotityLevel" = "./AdcGroupPriority/*[1]"!][!//
[!ENDIF!]

[!//
[!VAR "AdcAliasChCfg"="bit:or(AdcChannel0Alias,bit:shl(AdcChannel1Alias,8))"!][!//
[!ENDNOCODE!][!//
[!//
[!VAR "GroupIdx" = "$GroupIdx + num:i(1)"!][!//
  {/*Group Configuration structure for [!"@name"!] - ID[!"./AdcGroupId"!]*/
    /*
      Group Properties:
      Trigger Source: [!"AdcGroupTriggSrc"!]
      Trigger Edge: [!"./AdcHwTrigSignal/*[1]"!]
      HW Trigger Source: [!"AdcHwExtTrigSelect"!]
      HW Gate Source: [!"AdcHwExtGateSelect"!]
      Gate Level: [!"AdcHwGateSignal"!]
    */
    /* Notification Function Address */
    [!"$AdcNotifyPtr"!],
    /*Address for Group Definition Structure*/
    &Adc_kHwUnit[!"num:i($AdcHwId)"!]Grp[!"@name"!][!"$AdcConfigShortName"!][0U],
    /*Address for the GTM trigger configuration structure*/
    (const Mcu_17_Gtm_TomAtomChConfigType *)[!"$GtmTrigCfg"!],
    /*Address for the GTM gate configuration structure*/
    (const Mcu_17_Gtm_TomAtomChConfigType *)[!"$GtmGateCfg"!],
    /*Address for the ERU trigger configuration structure*/
    (const Adc_EruChannelCfgType *)[!"$EruTrigCfg"!],
    /*Address for the ERU gate configuration structure*/
    (const Adc_EruChannelCfgType *)[!"$EruGateCfg"!],
    /*Configuration value for the G[!"num:i($AdcHwId)"!]QCTRL register*/
    [!"num:inttohex($AdcGroupQCtrlVal,8)"!]U,
    /*Configuration value for the G[!"num:i($AdcHwId)"!]QMR register*/
    [!"num:inttohex($AdcGroupQModeVal,8)"!]U,
    /*Configuration value for the G[!"num:i($AdcHwId)"!]ALIAS register*/
    [!"num:inttohex($AdcAliasChCfg,8)"!]U,
    /* Configuration value for G[!"num:i($AdcHwId)"!]REQTM register*/
    [!"num:inttohex($AdcReqTmCfgVal,8)"!]U,
    /*Bit Mask for all the analog channels configured for the group*/
    [!"num:inttohex($AdcChannelMask,4)"!]U,
    /*Bit Mask for all the result registers configured for the group*/
    [!"num:inttohex($AdcResultRegMask,4)"!]U,
    /*Bit Mask for all the analog channels configured for synchronous conversion*/
    [!"num:inttohex($AdcSyncChannelMask,4)"!]U,
    /*Bit Mask for all the result registers configured for synchronous conversion*/
    [!"num:inttohex($AdcSyncResRegMask,4)"!]U,
    [!"AdcGroupTriggSrc"!],
    [!"AdcGroupConversionMode"!],
    [!"AdcGroupAccessMode"!],
    [!"AdcStreamingBufferMode"!],
    [!"AdcStreamingNumSamples"!]U, /*Number of streaming samples for the group*/
    [!"$AdcHwTrigType"!], /*HW peripheral used for Trigger*/
    [!"$AdcHwGateType"!], /*HW peripheral used for Gate*/
    [!"$AdcPriotityLevel"!]U, /*Priority Level for the group*/
    [!"num:i(count(AdcGroupDefinition/*))"!]U, /*Channel Count for the group*/
    [!"$AdcLimitCheckGrp"!]U /*Limit Check enabled for the group*/
  }[!IF "$GroupIdx < $AdcGroupCount"!],[!ENDIF!][!//

[!ENDLOOP!][!//
[!//
};
/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
[!/* [cover parentID={DFF7F3DC-E181-46b1-93FE-AC378F7D3A12}]Stop memory map section for Group Configuration structure[/cover] */!][!//     
#define ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($HwUnitCoreId)"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"

[!ENDSELECT!][!//
[!ENDFOR!][!//


/***********************Channel Configuration Definition***********************/
[!VAR "AdcHwUnitCount" = "num:i(count(AdcConfigSet/AdcHwUnit/*))"!][!//
[!FOR "HwUnitIdx" ="num:i(1)" TO "num:i($AdcHwUnitCount)"!][!//
[!SELECT "AdcConfigSet/AdcHwUnit/*[num:i($HwUnitIdx)]"!][!//
[!CALL "Adc_GetHwUnitCoreId", "ModuleMap"="$CGModuleMap", "Item" = "node:name(node:current())"!][!//
[!VAR "AdcHwId" = "num:i(text:split(AdcHwUnitId,'_ADC')[2])"!][!//
[!VAR "AdcChannelCount" = "num:i(count(AdcChannel/*))"!][!//
[!VAR "ChannelIdx" = "num:i(0)"!][!//
/*****Channel Configuration Definition of HW Unit [!"num:i($AdcHwId)"!] *****/
/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
[!/* [cover parentID={9AFFCC25-9EC2-4e0c-86CE-EAF73C118DD1}]Start memory map section for Channel Configuration structure[/cover] */!][!//   
#define ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($HwUnitCoreId)"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"
[!/* [cover parentID={08D8E97D-8ACA-4814-9308-FDA8A6435FE7}]Adc_kHwUnit[x]Ch_Config[_Variant][y][/cover] */!][!//
static const Adc_ChannelCfgType Adc_kHwUnit[!"num:i($AdcHwId)"!]Ch[!"$AdcConfigShortName"!][[!"$AdcChannelCount"!]]=
{
[!LOOP "node:order(./AdcChannel/*, './AdcChannelId')"!]
[!VAR "AdcChctrVal" = "num:i(0)"!][!//
[!VAR "AdcBoundVal" = "num:i(0)"!][!//
[!VAR "AdcGrpAnChNum" = "num:i(0)"!]
[!VAR "AdcChLimitChk" = "num:i(0)"!][!//
[!VAR "AdcSyncConvCh" = "num:i(0)"!][!//
[!VAR "AdcChRangeSelect" = "'ADC_RANGE_ALWAYS'"!][!//
[!VAR "AdcChHighLimit" = "num:i(4095)"!][!//
[!VAR "AdcChLowLimit" = "num:i(0)"!][!//
[!//
[!NOCODE!]
[!IF "node:exists(AdcChannelLimitCheck/*[1])"!][!//
  [!IF "node:value(AdcChannelLimitCheck/*[1]) = 'true'"!][!//
    [!/* [cover parentID={42573891-DF9A-49f1-8FEF-E06912FBDEC3}]Extarct Limit check configuration[/cover] */!][!//
    [!VAR "AdcChLimitChk" = "num:i(1)"!][!//
    [!IF "node:exists(AdcChannelRangeSelect/*[1])"!][!//
      [!VAR "AdcChRangeSelect" = "node:value(AdcChannelRangeSelect/*[1])"!][!//
    [!ENDIF!][!//
    [!//
    [!IF "node:exists(AdcChannelLowLimit/*[1])"!][!//
      [!VAR "AdcChLowLimit" = "node:value(AdcChannelLowLimit/*[1])"!][!//
    [!ENDIF!][!//
    [!//
    [!IF "node:exists(AdcChannelHighLimit/*[1])"!][!//
      [!VAR "AdcChHighLimit" = "node:value(AdcChannelHighLimit/*[1])"!][!//
    [!ENDIF!][!//
    [!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "AdcSyncConvChannelEnable = 'true'"!][!//
[!VAR "AdcSyncConvCh" = "num:i(1)"!][!//
[!ENDIF!][!//
[!ENDNOCODE!]
[!//
[!CALL "Adc_ConfigChctrVal","InputClassSelection" ="AdcInputClassSelection",
"ChannelRangeSelect"= "$AdcChRangeSelect","ChLimitChk"= "$AdcChLimitChk", "ChSyncConv"= "$AdcSyncConvCh",
"ChannelRefVoltsrcHigh"="AdcChannelRefVoltsrcHigh/*[1]","ResultAlignment"="../../../../../AdcGeneral/AdcResultAlignment",
"AdcChctrVal"="$AdcChctrVal"!][!//
[!//
[!CALL "Adc_ConfigBoundVal","ChannelRangeSelect"= "$AdcChRangeSelect",
"ChannelHighLimit" ="$AdcChHighLimit","ChannelLowLimit"= "$AdcChLowLimit",
"AdcBoundVal"="$AdcBoundVal"!][!//
[!//
[!VAR "AdcGrpAnChNum" = "text:split(AdcAnChannelNum,'CH')[2]"!][!//
[!//
[!VAR "ChannelIdx" = "$ChannelIdx + num:i(1)"!][!//
  {
    [!"num:inttohex($AdcChctrVal,8)"!]U, /*Configuration value for the G[!"num:i($AdcHwId)"!]CHCTR[!"num:i($AdcGrpAnChNum)"!] register*/
    [!"num:inttohex($AdcBoundVal,8)"!]U, /*Configuration value for the G[!"num:i($AdcHwId)"!]BOUND register*/
    [!"num:i($AdcGrpAnChNum)"!]U, /*Analog Channel number for the corresponding Logical Channel*/
    [!"num:i($AdcChLimitChk)"!]U /*Limit Check channel or not */
  }[!IF "$ChannelIdx < $AdcChannelCount"!],[!ENDIF!][!//

[!ENDLOOP!]
};
/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
[!/* [cover parentID={B7D86E82-1E6C-4a04-A844-1A6EF4694BD7}]Stop memory map section for Channel Configuration structure[/cover] */!][!//
#define ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($HwUnitCoreId)"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"

[!ENDSELECT!][!//
[!ENDFOR!][!//
/********************HW Unit Converter Configurations********************/
[!VAR "AdcHwUnitCount" = "num:i(count(AdcConfigSet/AdcHwUnit/*))"!][!//
[!FOR "HwUnitIdx" ="num:i(1)" TO "num:i($AdcHwUnitCount)"!][!//
[!SELECT "AdcConfigSet/AdcHwUnit/*[num:i($HwUnitIdx)]"!][!//
[!CALL "Adc_GetHwUnitCoreId", "ModuleMap"="$CGModuleMap", "Item" = "node:name(node:current())"!][!//
[!VAR "AdcHwId" = "num:i(text:split(AdcHwUnitId,'_ADC')[2])"!][!//
[!VAR "AdcAnCfgVal" = "num:i(0)"!][!//
[!VAR "AdcArbCfgVal" = "num:i(3)"!][!//
[!VAR "AdcArbPrioVal" = "num:i(0)"!][!//
[!VAR "AdcHwUnitIClass0Val" = "num:i(0)"!][!//
[!VAR "AdcHwUnitIClass1Val" = "num:i(0)"!][!//
[!VAR "AdcSyncCtrlVal" = "num:i(0)"!][!//
[!VAR "AdcSyncMaster" = "num:i(0)"!][!//
[!VAR "AdcSyncSlave" = "num:i(0)"!][!//
[!VAR "AdcSyncGroup" = "num:i(0)"!][!//
[!VAR "AdcSyncCore" = "num:i(255)"!][!//
[!//
[!VAR "AdcChClassVal" = "num:i(0)"!][!//
[!CALL "Adc_ConfigIClassVal","ChSampleTime" ="AdcHwUnitInputClass/*[1]/AdcChSampleTime",
"ChPreChargeClkCycles"= "AdcHwUnitInputClass/*[1]/AdcChPreChargeClkCycles",
"ChConvMode"="AdcHwUnitInputClass/*[1]/AdcChConvMode",
"ChSESPSEnable"="AdcHwUnitInputClass/*[1]/AdcChSESPSEnable",
"AdcChClassVal"="$AdcChClassVal"!][!//
[!VAR "AdcHwUnitIClass0Val" = "num:i($AdcChClassVal)"!][!//
[!VAR "AdcChClassVal" = "num:i(0)"!][!//
[!CALL "Adc_ConfigIClassVal","ChSampleTime" ="AdcHwUnitInputClass/*[2]/AdcChSampleTime",
"ChPreChargeClkCycles"= "AdcHwUnitInputClass/*[2]/AdcChPreChargeClkCycles",
"ChConvMode"="AdcHwUnitInputClass/*[2]/AdcChConvMode",
"ChSESPSEnable"="AdcHwUnitInputClass/*[2]/AdcChSESPSEnable",
"AdcChClassVal"="$AdcChClassVal"!][!//
[!VAR "AdcHwUnitIClass1Val" = "num:i($AdcChClassVal)"!][!//
[!//
[!CALL "Adc_ConfigAnCfgVal","IdlePrechargeEnable" ="AdcIdlePrechargeEnable","InputBufferEnable"= "AdcInputBufferEnable",
"PrechargeReference"="AdcPrechargeReference","ReferencePrechargePhases"="AdcReferencePrechargePhases", 
"CalibrationSampleTime"="AdcCalibrationSampleTime","PostCalibrationDisable"="AdcPostCalibrationDisable",
 "AnalogClockSyncDelay"="AdcAnalogClockSyncDelay", "SampleSyncEnable"="AdcSampleSyncEnable",
"Prescale"="AdcPrescale/*[1]", "MSBDoubleClkEnable"="AdcMSBDoubleClkEnable",
"AdcAnCfgVal"="$AdcAnCfgVal"!][!//
[!//
[!//
[!CALL "Adc_ConfigArbPrioVal",
"RequestSource0ConvMode"= "AdcRequestSource0ConvMode","RequestSource1ConvMode"= "AdcRequestSource1ConvMode",
"RequestSource2ConvMode"= "AdcRequestSource2ConvMode","PrioImplementation"= "../../../AdcGeneral/AdcPriorityImplementation",
"AdcArbPrioVal"="$AdcArbPrioVal"!][!//
[!//
[!IF "AdcSyncConvMode = 'ADC_SYNC_SLAVE' or AdcSyncConvMode = 'ADC_SYNC_MASTER'"!]
  [!IF "$AdcHwId >= num:i(0) and $AdcHwId <= num:i(3)"!][!//
    [!VAR "AdcSyncHwId" = "num:i($AdcHwId)"!][!//
    [!VAR "AdcSyncMaster" = "num:i($SyncGrpAMaster)"!][!//
    [!VAR "AdcSyncSlave" = "num:i($SyncGrpASlave)"!][!//
    [!VAR "AdcSyncGroup" = "num:i($SyncGrpA)"!][!//
    [!VAR "AdcSyncCore" = "num:i($SyncGrpACore)"!][!//
  [!ELSEIF "$AdcHwId >= num:i(4) and $AdcHwId <= num:i(7)"!][!//
    [!VAR "AdcSyncHwId" = "num:i($AdcHwId) - num:i(4)"!][!//
    [!VAR "AdcSyncMaster" = "num:i($SyncGrpBMaster) - num:i(4)"!][!//
    [!VAR "AdcSyncSlave" = "bit:shr(num:i($SyncGrpBSlave),4)"!][!//
    [!VAR "AdcSyncGroup" = "bit:shr(num:i($SyncGrpB),4)"!][!//
    [!VAR "AdcSyncCore" = "num:i($SyncGrpBCore)"!][!//
  [!ELSEIF "$AdcHwId >= num:i(8) and $AdcHwId <= num:i(11)"!][!//
    [!VAR "AdcSyncHwId" = "num:i($AdcHwId) - num:i(8)"!][!//
    [!VAR "AdcSyncMaster" = "num:i($SyncGrpCMaster) - num:i(8)"!][!//
    [!VAR "AdcSyncSlave" = "bit:shr(num:i($SyncGrpCSlave),8)"!][!//
    [!VAR "AdcSyncGroup" = "bit:shr(num:i($SyncGrpC),8)"!][!//
    [!VAR "AdcSyncCore" = "num:i($SyncGrpCCore)"!][!//
  [!ENDIF!]
[!//
[!IF "AdcSyncConvMode = 'ADC_SYNC_SLAVE'"!][!//
   [!IF "(num:i($AdcSyncMaster) = num:i(255)) or (num:i($AdcSyncMaster) = num:i(251)) or (num:i($AdcSyncMaster) = num:i(247))"!][!//
      [!ERROR!][!//
ADC Code Generator: Master kernel is not allocated for slave kernel - HWUNIT_ADC[!"num:i($AdcHwId)"!]
      [!ENDERROR!][!//
   [!ENDIF!]
[!ENDIF!]
[!//
[!IF "AdcSyncConvMode = 'ADC_SYNC_MASTER'"!][!//
   [!IF "num:i($AdcSyncSlave) = num:i(0)"!][!//
      [!ERROR!][!//
ADC Code Generator: Slave kernel is not allocated for Master kernel - HWUNIT_ADC[!"num:i($AdcHwId)"!]
      [!ENDERROR!][!//
   [!ENDIF!][!//
[!ENDIF!][!//
[!//
  [!IF "AdcSyncConvMode = 'ADC_SYNC_SLAVE'"!][!//
    [!IF "num:i($AdcSyncCore) != num:i($HwUnitCoreId)"!][!//
      [!ERROR!][!//
ADC Code Generator: All HW Units of a synchronization group must be assigned to the same CPU core
      [!ENDERROR!][!//
    [!ENDIF!][!//
    [!VAR "AdcArbCfgVal" = "num:i(0)"!][!//
    [!IF "num:i($AdcSyncHwId) > num:i($AdcSyncMaster)"!][!//
      [!VAR "AdcSyncCtrlVal" = "bit:or($AdcSyncCtrlVal, (num:i($AdcSyncMaster)+1) )"!][!//
    [!ELSEIF "num:i($AdcSyncHwId) < num:i($AdcSyncMaster)"!][!//
      [!VAR "AdcSyncCtrlVal" = "bit:or($AdcSyncCtrlVal, num:i($AdcSyncMaster))"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
  [!FOR "LoopIdx" ="num:i(0)" TO "num:i(3)"!][!//
    [!IF "bit:getbit($AdcSyncGroup,$LoopIdx)"!][!//
      [!IF "num:i($LoopIdx) > num:i($AdcSyncHwId)"!][!//
        [!VAR "AdcSyncCtrlVal" = "bit:or($AdcSyncCtrlVal, bit:shl(1, (3+num:i($LoopIdx)) ) )"!][!//
      [!ELSEIF "num:i($LoopIdx) < num:i($AdcSyncHwId)"!][!//
        [!VAR "AdcSyncCtrlVal" = "bit:or($AdcSyncCtrlVal, bit:shl(1, (4+num:i($LoopIdx)) ) )"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
[!ENDIF!][!//

/**HW Unit [!"num:i($AdcHwId)"!] Converter Configurations **/
/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/ 
[!/* [cover parentID={2C13CBAA-CD40-4c8f-BE76-0551561E6148}]Start memory map section for Hardware Uinit Converter Configuration structure[/cover] */!][!//
#define ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($HwUnitCoreId)"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"
[!/* [cover parentID={2060853A-CF4A-498d-9D93-4993909EB9DD}]Adc_kHwUnit[x]Hw_Config[_Variant][/cover] */!][!//
static const Adc_HwCfgType Adc_kHwUnit[!"num:i($AdcHwId)"!]Hw[!"$AdcConfigShortName"!]=
{
  [!"num:inttohex($AdcAnCfgVal,8)"!]U, /*Configuration value for G[!"num:i($AdcHwId)"!]ANCFG register*/
  [!"num:inttohex($AdcArbCfgVal,8)"!]U, /*Configuration value for G[!"num:i($AdcHwId)"!]ARBCFG register*/
  [!"num:inttohex($AdcArbPrioVal,8)"!]U, /*Configuration value for G[!"num:i($AdcHwId)"!]ARBPR register*/
  [!"num:inttohex($AdcHwUnitIClass0Val,8)"!]U, /*Configuration value for G[!"num:i($AdcHwId)"!]ICLASS0 register*/
  [!"num:inttohex($AdcHwUnitIClass1Val,8)"!]U, /*Configuration value for G[!"num:i($AdcHwId)"!]ICLASS1 register*/
  [!"num:inttohex($AdcSyncCtrlVal,8)"!]U /*Configuration value for G[!"num:i($AdcHwId)"!]SYNCTR register*/
};
/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/ 
[!/* [cover parentID={8F358F60-C56B-4681-98D8-4C7EA562B24D}]Stop memory map section for Hardware Unit Converter Configuration structure[/cover] */!][!//
#define ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($HwUnitCoreId)"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"


[!ENDSELECT!][!//
[!ENDFOR!]

/***************************HW Unit Configuration ***************************/
[!VAR "AdcHwUnitCount" = "num:i(count(AdcConfigSet/AdcHwUnit/*))"!][!//
[!FOR "HwUnitIdx" ="num:i(1)" TO "num:i($AdcHwUnitCount)"!][!//

[!VAR "SRNUsed" = "num:i(0)"!][!//
[!VAR "AdcSWGroupMask" = "num:i(0)"!][!//
[!VAR "AdcHWGroupMask" = "num:i(0)"!][!//
[!VAR "AdcSyncGroupSlave" = "num:i(0)"!][!//
[!VAR "AdcSlaveKernel0" = "num:i(255)"!][!//
[!VAR "AdcSlaveKernel1" = "num:i(255)"!][!//
[!VAR "AdcSlaveKernel2" = "num:i(255)"!][!//
[!IF "AdcGeneral/AdcPriorityImplementation = 'ADC_PRIORITY_NONE'"!][!//
  [!VAR "SRNUsed" = "num:i(1)"!][!//
[!ELSE!][!//
  [!VAR "SRNUsed" = "num:i(7)"!][!//
[!ENDIF!][!//
[!SELECT "AdcConfigSet/AdcHwUnit/*[num:i($HwUnitIdx)]"!][!//
[!VAR "AdcHwId" = "num:i(text:split(AdcHwUnitId,'_ADC')[2])"!][!//
[!VAR "SyncConvMode" = "'ADC_SYNC_CONV_MODE_NONE'"!][!//
[!IF "AdcSyncConvMode = 'ADC_SYNC_MASTER'"!][!//
  [!VAR "SyncConvMode" = "'ADC_SYNC_CONV_MODE_MASTER'"!][!//
  [!IF "$AdcHwId >= num:i(0) and $AdcHwId <= num:i(3)"!][!//
    [!VAR "AdcSyncGroupSlave" = "num:i($SyncGrpASlave)"!][!//
  [!ELSEIF "$AdcHwId >= num:i(4) and $AdcHwId <= num:i(7)"!][!//
    [!VAR "AdcSyncGroupSlave" = "num:i($SyncGrpBSlave)"!][!//
  [!ELSEIF "$AdcHwId >= num:i(8) and $AdcHwId <= num:i(11)"!][!//
    [!VAR "AdcSyncGroupSlave" = "num:i($SyncGrpCSlave)"!][!//
  [!ENDIF!][!//
  [!FOR "LoopIdx" = "num:i(0)" TO "num:i(ecu:get('Adc.MaxHwUnitId')) - num:i(1)"!][!//
    [!IF "bit:getbit($AdcSyncGroupSlave,$LoopIdx)"!][!//
      [!IF "num:i($AdcSlaveKernel0) = num:i(255)"!][!//
        [!VAR "AdcSlaveKernel0" = "num:i($LoopIdx)"!][!//
      [!ELSEIF "num:i($AdcSlaveKernel1) = num:i(255)"!][!//
        [!VAR "AdcSlaveKernel1" = "num:i($LoopIdx)"!][!//
      [!ELSE!][!//
        [!VAR "AdcSlaveKernel2" = "num:i($LoopIdx)"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
[!ELSEIF "AdcSyncConvMode = 'ADC_SYNC_SLAVE'"!][!//
  [!VAR "SyncConvMode" = "'ADC_SYNC_CONV_MODE_SLAVE'"!][!//
[!ENDIF!][!//
[!CALL "Adc_GetHwUnitCoreId", "ModuleMap"="$CGModuleMap", "Item" = "node:name(node:current())"!][!//
[!VAR "AdcGroupCount" = "num:i(count(AdcGroup/*))"!][!//
[!//
[!NOCODE!]
[!LOOP "node:order(./AdcGroup/*, './AdcGroupId')"!][!//
  [!//
  [!IF "./AdcGroupTriggSrc = 'ADC_TRIGG_SRC_SW'"!][!//
    [!VAR "AdcSWGroupMask" = "bit:or($AdcSWGroupMask, bit:shl(num:i(1),bit:and(./AdcGroupId,num:i(31))))"!][!//
  [!ELSE!][!//
    [!VAR "AdcHWGroupMask" = "bit:or($AdcHWGroupMask, bit:shl(num:i(1),bit:and(./AdcGroupId,num:i(31))))"!][!//
  [!ENDIF!]
  [!VAR "ChannelCount"="num:i(count(AdcGroupDefinition/*))"!]
  [!FOR "ChannelIdx" ="num:i(1)" TO "num:i($ChannelCount)"!][!//
    [!VAR "ChannelNodeName" = "node:name(node:ref(AdcGroupDefinition/*[num:i($ChannelIdx)]))"!][!//
    [!LOOP "../../AdcChannel/*"!][!//
      [!IF "@name = $ChannelNodeName"!][!//
        [!IF "node:exists(AdcChannelLimitCheck/*[1])"!]
          [!IF "node:value(AdcChannelLimitCheck/*[1])"!]
            [!VAR "SRNUsed" = "bit:or($SRNUsed,bit:shl(1,3))"!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ENDFOR!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!]
/*************HW Unit [!"num:i($AdcHwId)"!] Configuration **************/
/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/ 
[!/* [cover parentID={D784CB66-640D-4ee5-8B60-F39C09C3ECA1}]Start memory map section for Hardware Unit Configuration structure[/cover] */!][!//
   #define ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($HwUnitCoreId)"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"
[!/* [cover parentID={832CC668-D5B3-4980-9B50-20BF0EEE72B2}]Adc_kHwUnit[x]_Config[_Variant][/cover] */!][!//
static const Adc_HwUnitCfgType Adc_kHwUnit[!"num:i($AdcHwId)"!][!"$AdcConfigShortName"!]=
{
  &Adc_kHwUnit[!"num:i($AdcHwId)"!]Hw[!"$AdcConfigShortName"!], /*Analog Converter Configuration*/
  &Adc_kHwUnit[!"num:i($AdcHwId)"!]Ch[!"$AdcConfigShortName"!][0U], /*Channel Configuration structure*/
  &Adc_kHwUnit[!"num:i($AdcHwId)"!]Grp[!"$AdcConfigShortName"!][0U], /*Group Configuration structure*/
  [!"num:inttohex($AdcSWGroupMask,8)"!]U, /* Mask for SW triggered groups*/
  [!"num:inttohex($AdcHWGroupMask,8)"!]U,/* Mask for HW triggered groups*/
  [!"$SyncConvMode"!], /* Synchronous conversion mode */
  { [!"num:inttohex($AdcSlaveKernel0,2)"!]U, [!"num:inttohex($AdcSlaveKernel1,2)"!]U, [!"num:inttohex($AdcSlaveKernel2,2)"!]U }, /* Slave Kernels */
  [!"num:i($AdcGroupCount)"!]U, /* Group Count for HW Unit [!"num:i($AdcHwId)"!]*/
  [!"num:i($SRNUsed)"!]U /* Bit Mask for SRNs used for HW Unit [!"num:i($AdcHwId)"!]*/
};
/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/ 
[!/* [cover parentID={36F2738B-724B-4a84-9A1A-FFC270A80F30}]Stop memory map section for Hardware Unit Configuration structure */!][!//
#define ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($HwUnitCoreId)"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"

[!ENDSELECT!][!//
[!ENDFOR!][!// 

/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
[!/* [cover parentID={8ADB5CAF-3A22-47f7-9AF5-7613AEC2392E}]Start memory map section for Global Configuration structure[/cover] */!][!//    
#define ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"$CGMasterCoreId"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"
/******************Global Configuration*******************/
[!/* [cover parentID={48A240C5-31A0-4957-A290-398E6C1D8F36}]Adc_kGlob_Config[_Variant][/cover] */!][!// 
static const Adc_GlobalCfgType Adc_kGlob[!"$AdcConfigShortName"!]=
{
[!VAR "AdcGlobCfgVal" = "num:i(0)"!][!//
[!SELECT "AdcConfigSet"!][!//
[!CALL "Adc_ConfigGlobalCfgVal","SyncClockDisable"="AdcSyncClockDisable",
"SupplyVoltage"="../AdcGeneral/AdcSupplyVoltage",
"AdcGlobCfgVal"="$AdcGlobCfgVal"!][!//
[!ENDSELECT!]
[!//
[!SELECT "AdcConfigSet/AdcGlobalInputClass/*[1]"!][!//
[!VAR "AdcChClassVal" = "num:i(0)"!][!//
[!CALL "Adc_ConfigIClassVal","ChSampleTime" ="AdcChSampleTime",
"ChPreChargeClkCycles"= "AdcChPreChargeClkCycles","ChConvMode"="AdcChConvMode",
"ChSESPSEnable"="AdcChSESPSEnable","AdcChClassVal"="$AdcChClassVal"!][!//
[!VAR "AdcGlob0ClassVal" = "num:i($AdcChClassVal)"!][!//
[!ENDSELECT!][!//
[!SELECT "AdcConfigSet/AdcGlobalInputClass/*[2]"!][!//
[!VAR "AdcChClassVal" = "num:i(0)"!][!//
[!CALL "Adc_ConfigIClassVal","ChSampleTime" ="AdcChSampleTime",
"ChPreChargeClkCycles"= "AdcChPreChargeClkCycles","ChConvMode"="AdcChConvMode",
"ChSESPSEnable"="AdcChSESPSEnable","AdcChClassVal"="$AdcChClassVal"!][!//
[!VAR "AdcGlob1ClassVal" = "num:i($AdcChClassVal)"!][!//
[!ENDSELECT!][!//
[!//
  [!"num:inttohex($AdcGlobCfgVal,8)"!]U, /*Configuration value for GLOBCFG register */
  [!"num:inttohex($AdcGlob0ClassVal,8)"!]U, /*Configuration value for GLOBICLASS0 register */
  [!"num:inttohex($AdcGlob1ClassVal,8)"!]U /*Configuration value for GLOBICLASS1 register */
};
/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
[!/* [cover parentID={6B6ECF1B-B87D-4258-B882-42FD6227E71D}]Stop memory map section for Global Configuration structure[/cover] */!][!//    
#define ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"$CGMasterCoreId"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"


/***************************Core Configuration ***************************/

[!FOR "CoreIndex" = "num:i(1)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable'))"!][!//
  [!VAR "corePattern" = "concat( 'CORE', num:i($CoreIndex - 1) )"!][!//
  [!VAR "matchCore" = "concat( '^.*(', $corePattern, ').*$' )"!][!//
  [!IF "text:match($CGCoreUsed, $matchCore)"!][!// Fetch all strings matching the core.
/*******Core[!"num:i($CoreIndex - 1)"!] Configuration*******/
/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
[!/* [cover parentID={A31367B1-3356-4edf-BFD2-FAAD844A255B}]Start memory map section for Core configuration structure[/cover] */!][!//   
#define ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($CoreIndex - 1)"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"
[!/* [cover parentID={C635E2CD-A050-40bf-BB84-018AA3DD7C57}]Adc_kCore[x]_Config[_Variant][/cover] */!][!//
static const Adc_CoreConfigType Adc_kCore[!"num:i($CoreIndex - 1)"!][!"$AdcConfigShortName"!]=
{
  {
    [!VAR "AdcHwUnitUsed"= "num:i(0)"!][!//
    [!VAR "AdcHwUnitCount" = "num:i(count(AdcConfigSet/AdcHwUnit/*))"!][!//
    [!FOR "HwUnitIdx" ="num:i(1)" TO "num:i($AdcHwUnitCount)"!][!//
      [!SELECT "AdcConfigSet/AdcHwUnit/*[num:i($HwUnitIdx)]"!][!//
        [!VAR "hwUnitPattern" = "node:name(node:current())"!]
        [!VAR "matchPattern" = "concat( '^.*(', $corePattern, '_', $hwUnitPattern,',', ').*$' )"!][!//
        [!IF "text:match($CGModuleMap, $matchPattern)"!][!//
          [!VAR "AdcHwId" = "num:i(text:split(AdcHwUnitId,'_ADC')[2])"!][!//
          [!VAR "AdcHwUnitUsed" = "bit:or($AdcHwUnitUsed, bit:shl(1,$AdcHwId))"!][!//
        [!ENDIF!][!//
      [!ENDSELECT!][!//
    [!ENDFOR!][!//
    [!FOR "BitIdx" ="num:i(1)" TO "num:i(ecu:get('Adc.MaxHwUnitId'))"!][!//
      [!IF "bit:getbit($AdcHwUnitUsed, num:i($BitIdx - 1))"!][!//
    &Adc_kHwUnit[!"num:i($BitIdx - 1)"!][!"$AdcConfigShortName"!][!IF "num:i($BitIdx) != ecu:get('Adc.MaxHwUnitId')"!],[!ENDIF!] /* HW Unit [!"num:i($BitIdx)"!] Configuration */
      [!ELSE!][!//
    (Adc_HwUnitCfgType*)0U[!IF "num:i($BitIdx) != num:i(ecu:get('Adc.MaxHwUnitId'))"!],[!ENDIF!] /* HW Unit [!"num:i($BitIdx)"!] Configuration */
      [!ENDIF!][!//
    [!ENDFOR!][!//
  }
};
/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/ 
[!/* [cover parentID={E8EF3403-A7EB-48c9-A5C9-C14ADA52C1D1}]Stop memory map section for Core configuration structure[/cover] */!][!// 
#define ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($CoreIndex - 1)"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"
  
  [!ENDIF!][!//
[!ENDFOR!][!//

/*******Configuration Root*******/
/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/ 
[!/* [cover parentID={E956AB56-4DA0-4400-AE6C-BDA633BA6BF2}]Start memory map section for Adc configuration structure[/cover] */!][!//
#define ADC_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar 
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"

/* MISRA2012_RULE_8_7_JUSTIFICATION: Module configuration data structure
   declaration is as per Autosar guidelines. This data structure is needed
   by SW units using Adc Driver APIs hence it should be declared as extern in 
   the SW unit from where it is used */
/* MISRA2012_RULE_8_4_JUSTIFICATION: Module configuration data structure
   declaration is as per Autosar guidelines. This data structure is needed
   by SW units using Adc Driver APIs hence it should be declared as extern in 
   the SW unit from where it is used */
[!/* [cover parentID={1A02A0E1-94EB-487e-940C-124A1B7323ED}]Adc_Config[_Variant][/cover] */!][!//
const Adc_ConfigType Adc[!"$AdcConfigShortName"!]=
{
  &Adc_kGlob[!"$AdcConfigShortName"!], /* Global Configuration */
  {
[!FOR "CoreIndex" = "num:i(1)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable'))"!]
  [!VAR "corePattern" = "concat( 'CORE', num:i($CoreIndex - 1) )"!]
  [!VAR "matchCore" = "concat( '^.*(', $corePattern, ').*$' )"!]
  [!IF "text:match($CGCoreUsed, $matchCore)"!] [!// Fetch all strings matching the core.
    &Adc_kCore[!"num:i($CoreIndex - 1)"!][!"$AdcConfigShortName"!][!IF "num:i($CoreIndex) != num:i(ecu:get('Mcu.NoOfCoreAvailable'))"!],[!ENDIF!] /* Core[!"num:i($CoreIndex - 1)"!] Configuration */
  [!ELSE!]
    (const Adc_CoreConfigType*)0U[!IF "num:i($CoreIndex) != num:i(ecu:get('Mcu.NoOfCoreAvailable'))"!],[!ENDIF!] /* Core[!"num:i($CoreIndex - 1)"!] Configuration */
  [!ENDIF!]
[!ENDFOR!][!//
  }
};
/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the ADC module*/
[!/* [cover parentID={B607D32E-9C8E-4356-BB75-CB92E9D59777}]Stop memory map section for Adc configuration structure[/cover] */!][!//   
#define ADC_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */ 
#include "Adc_MemMap.h"

[!ENDSELECT!][!//

