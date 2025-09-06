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
**  FILENAME  : Wdg_17_Scu_PBCfg.c                                            **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE      : 2018-03-28                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Wdg.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : NA                                                         **
**                                                                            **
**  DESCRIPTION  : Code template source file for Wdg Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Wdg Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!]
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
**  FILENAME  : Wdg_17_Scu_PBCfg.c                                            **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                                      **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                                          **
**                                                                            **
**  BSW MODULE DECRIPTION : Wdg.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Wdg configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Wdg Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={4B4C1884-B983-4f00-8290-BEE566E215AA}][/cover] */
/* [cover parentID={E432E53C-D604-46f7-A483-A46751440A85}][/cover] */
/* [cover parentID={7CB9F258-E96D-41d8-9DB1-2E927F96D1DE}][/cover] */
/* [cover parentID={5CA58BDD-0BE1-4869-BE44-333AD4E77E2F}][/cover] */

[!NOCODE!][!//
[!INCLUDE "Wdg_17_Scu.m"!][!//
[!ENDNOCODE!][!//

[!//
[!NOCODE!][!//
[!IF "not(node:exists(as:modconf('ResourceM')[1]))"!]
  [!ERROR!][!//
    WDG Code Generator: ResourceM module is not added to the project.
  [!ENDERROR!][!//
[!ENDIF!]

[!IF "not(node:exists(as:modconf('Mcu')[1]))"!]
  [!ERROR!][!//
    WDG Code Generator: Mcu module is not added to the project.
  [!ENDERROR!][!//
[!ENDIF!]

[!IF "not(node:exists(as:modconf('McalLib')[1]))"!]
  [!ERROR!][!//
    WDG Code Generator: Mcallib module is not added to the project.
  [!ENDERROR!][!//
[!ENDIF!]

[!ENDNOCODE!][!//
/******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Include module header File */

/* Module header file, which includes module configuration(Wdg_17_Cfg.h) file */
#include "Wdg_17_Scu.h"

/******************************************************************************
**                      Imported Compiler Switch Checks                      **
*******************************************************************************/

/******************************************************************************
**                      Private Macro Definitions                            **
*******************************************************************************/


/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
[!//
[!VAR "VariantsConfigured" = "num:i(0)"!]
[!SELECT "as:modconf('EcuC')[1]"!][!//
[!IF "node:exists(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!][!//
[!VAR "PredefinedVarName1" = "(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!]
[!VAR "PredefinedVarName2" = "substring-after($PredefinedVarName1, "/")"!][!//
[!VAR "PredefinedVarName3" = "substring-after($PredefinedVarName2, "/")"!][!//
[!VAR "PredefinedVarName" = "substring-after($PredefinedVarName3, "/")"!][!//
[!VAR "VariantsConfigured" = "num:i(1)"!]
[!ENDIF!][!//
[!ENDSELECT!]

[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Wdg')[1]"!][!//
/*
Configuration: Wdg_17_Scu_ConfigType
Overall configuration of the WDT
*/
[!//
[!VAR "No0fWdgModuleConfig" = "num:i(count(WdgSettingsConfig/*))"!][!//
[!//
[!VAR "GtmChnlCount" = "num:i(0)"!][!//
[!VAR "StmCount" = "num:i(0)"!][!//
[!VAR "GtmchnlArry" = "'#'"!][!//
[!VAR "StmArry" = "'#'"!][!//
[!VAR "RMCoreArry" = "'#'"!][!//
[!VAR "GtmModule" = "''"!][!//
[!VAR "GtmModuleNo" = "num:i(0)"!][!//
[!VAR "GtmChannelNo" = "num:i(0)"!][!//


[!FOR "Index" = "num:i(0)" TO "num:i($No0fWdgModuleConfig - num:i(1))"!][!//
[!//
[!NOCODE!]
[!VAR "StmCmpRegUsed" = "''"!]

[!VAR "WdgCoreID" = "WdgSettingsConfig/*[@index = $Index]/WdgCoreId"!]

/*Code for calculating system clock*/
[!VAR "WdgClockRef" = "WdgSettingsConfig/*[@index = $Index]/WdgSystemClockRef"!]
[!VAR "SystemClock" = "num:f(node:ref(WdgSettingsConfig/*[@index = $Index]/WdgSystemClockRef)/McuPllDistributionSettingConfig/McuSPBFrequency)"!][!//
[!CALL "Wdg_MaxReloadTime", "SystemClockVal"="num:i($SystemClock)", "ClockDivider"="num:i(256)", "MaxReloadTime"="num:i(0)"!][!//
[!VAR "FastTimeout" = "WdgSettingsConfig/*[@index = $Index]/WdgSettingsFast/WdgFastModeTimeoutValue * num:i(1000)"!][!//
[!CALL "Wdg_ReloadValue", "SystemClockVal"="num:i($SystemClock)", "TimeoutVal"="$FastTimeout", "ClockDivider"="num:i(256)", "ReloadValue"="num:i(0)"!][!//
[!CALL "Wdg_TimingValidation", "ReloadValue"="num:i($ReloadValue)", "WdgTimeNodeName"="'WdgFastModeTimeoutValue'","MaxReloadTime"="$MaxReloadTime"!][!//
[!VAR "FastModeReloadValue" = "num:i(65536) - num:i($ReloadValue)"!]

[!CALL "Wdg_MaxReloadTime", "SystemClockVal"="num:i($SystemClock)", "ClockDivider"="num:i(16384)", "MaxReloadTime"="num:i(0)"!][!//
[!VAR "SlowTimeout" = "WdgSettingsConfig/*[@index = $Index]/WdgSettingsSlow/WdgSlowModeTimeoutValue * num:i(1000)"!][!//
[!CALL "Wdg_ReloadValue", "SystemClockVal"="num:i($SystemClock)", "TimeoutVal"="$SlowTimeout", "ClockDivider"="num:i(16384)", "ReloadValue"="num:i(0)"!][!//
[!CALL "Wdg_TimingValidation", "ReloadValue"="num:i($ReloadValue)", "WdgTimeNodeName"="'WdgSlowModeTimeoutValue'","MaxReloadTime"="$MaxReloadTime"!][!//
[!VAR "SlowModeReloadValue" = "num:i(65536) - num:i($ReloadValue)"!]

[!VAR "SlowRefreshTime" = "WdgSettingsConfig/*[@index = $Index]/WdgTriggerTimerSetting/WdgSlowRefreshTime * num:i(1000)"!]
[!VAR "RefreshTPath" = "node:path(WdgSettingsConfig/*[@index = $Index]/WdgTriggerTimerSetting/WdgSlowRefreshTime)"!]
[!CALL "Wdg_RefreshTimeValidation", "RefreshTime" = "$SlowRefreshTime", "WdgTout" = "$SlowTimeout",
 "ModeString" = "'SLOW'","PathVar" = "$RefreshTPath","WdgCoreID" = "$WdgCoreID"!]
[!VAR "FastRefreshTime" = "WdgSettingsConfig/*[@index = $Index]/WdgTriggerTimerSetting/WdgFastRefreshTime * num:i(1000)"!]
[!VAR "RefreshTPath" = "node:path(WdgSettingsConfig/*[@index = $Index]/WdgTriggerTimerSetting/WdgFastRefreshTime)"!]
[!CALL "Wdg_RefreshTimeValidation", "RefreshTime" = "$FastRefreshTime", "WdgTout" = "$FastTimeout", 
"ModeString" = "'FAST'", "PathVar" = "$RefreshTPath", "WdgCoreID" = "$WdgCoreID"!]
[!CALL "Wdg_RefreshTimeValidation", "RefreshTime" = "$FastRefreshTime", "WdgTout" = "$SlowRefreshTime", 
"ModeString" = "'BOTH'", "PathVar" = "$RefreshTPath", "WdgCoreID" = "$WdgCoreID"!]


[!IF "WdgSettingsConfig/*[@index = $Index]/WdgCPUDisableAllowed = 'true'"!]
[!VAR "WdgCoreDisableStatus" = "'TRUE'"!]
[!ELSE!]
[!VAR "WdgCoreDisableStatus" = "'FALSE'"!]
[!ENDIF!]

[!VAR "Wdg_InitialTout" = "WdgSettingsConfig/*[@index = $Index]/WdgCPUInitialTimeout * num:i(1000)"!]
[!VAR "Wdg_MaxTout" = "WdgSettingsConfig/*[@index = $Index]/WdgCPUMaxTimeout * num:i(1000)"!]
[!VAR "WdgPswd" = "WdgSettingsConfig/*[@index = $Index]/WdgCPUInitialPassowrd "!]
[!CALL "Wdg_ValidateInitialTout", "InitialTout" = "$Wdg_InitialTout", "MaxTout" = "$Wdg_MaxTout",
 "SlowRefrehT" = "$SlowRefreshTime", "FastRefreshT" = "$FastRefreshTime", "WdgCoreID" = "$WdgCoreID"!]
[!VAR "DefaultMode" = "WdgSettingsConfig/*[@index = $Index]/WdgDefaultMode"!]

  
/* These are the service time settings for this configuration instance */ [!//

[!IF "WdgGeneral/WdgTriggerTimerSelection = 'GTM_TIMER'"!][!//
[!IF "node:exists(WdgSettingsConfig/*[@index = $Index]/WdgTriggerTimerSetting/GtmTimerConfiguration/*[1])"!]
[!VAR "WdgGtmChannel" = "(WdgSettingsConfig/*[@index = $Index]/WdgTriggerTimerSetting/GtmTimerConfiguration/*[1]/GtmTimerOutputModuleConfiguration/GtmTimerUsed)"!][!//
[!CALL "Wdg_ValidateGtmChannel", "WdgGtmChannelTemp"="$WdgGtmChannel", "WdgCoreID" = "$WdgCoreID"!][!//
[!VAR "GtmTimerTicks" = "num:i(0)"!]
[!CALL "Wdg_ConfigGetGtmParams","GtmChannelRef" = "$WdgGtmChannel","GtmTimePeriod" = "$SlowRefreshTime",
"GtmTimerContainer" = "node:path(./WdgSettingsConfig/*[@index = $Index]/WdgTriggerTimerSetting/GtmTimerConfiguration/*[1]/GtmTimerOutputModuleConfiguration)",
"GtmClockRef" = "$WdgClockRef","GtmTimerTicks" = "$GtmTimerTicks"!]
[!VAR "GtmSlowTimeTick" = "$GtmTimerTicks"!]
[!VAR "GtmTimerTicks" = "num:i(0)"!]
[!CALL "Wdg_ConfigGetGtmParams","GtmChannelRef" = "$WdgGtmChannel","GtmTimePeriod" = "$FastRefreshTime",
"GtmTimerContainer" = "node:path(./WdgSettingsConfig/*[@index = $Index]/WdgTriggerTimerSetting/GtmTimerConfiguration/*[1]/GtmTimerOutputModuleConfiguration)",
"GtmClockRef" = "$WdgClockRef","GtmTimerTicks" = "$GtmTimerTicks"!]
[!VAR "GtmFastTimeTick" = "$GtmTimerTicks"!]
[!VAR "GtmTimerTicks" = "num:i(0)"!]
[!VAR "Clockdiv" = "(WdgSettingsConfig/*[@index = $Index]/WdgTriggerTimerSetting/GtmTimerConfiguration/*[1]/GtmTimerOutputModuleConfiguration/GtmTimerClockSelect)"!]
[!VAR "Clockdiv" = "num:i(text:split($Clockdiv,'_')[4])"!]
[!IF "$GtmModule = 'MCU_GTM_TIMER_ATOM'"!]
[!VAR "CtrlReg" = "num:hextoint('0x00000802')"!][!//Default value, where OSM=0 for continuous mode operation
[!ELSE!]
[!VAR "CtrlReg" = "num:hextoint('0x00000800')"!][!//Default value, where OSM=0 for continuous mode operation
[!ENDIF!]
[!VAR "CtrlReg" = "bit:or($CtrlReg,bit:shl($Clockdiv,12))"!][!//Set Clock Source for the Timer Channel
[!ELSE!]
[!ERROR!]
Error : GtmTimerConfiguration should be configured since GTM_TIMER is selected for WdgTriggerTimerSelection. 
[!ENDERROR!]
[!ENDIF!]
[!ELSE!][!//STM timer
[!VAR "StmTimerUsed" = "num:i(111)"!][!//
[!VAR "StmCmpRegUsed" = "num:i(111)"!][!//
[!CALL "Wdg_StmTimerValidation", "WdgCoreID" = "$WdgCoreID", "StmTimerUsed"="$StmTimerUsed", "StmCmpRegUsed" = "$StmCmpRegUsed"!][!//
[!ENDIF!]
[!ENDNOCODE!]
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* [cover parentID={1ECB14FC-FCA5-456f-A293-EBD310BAA256}][/cover] */
/* [cover parentID={7D8EFFAB-1BCE-4d95-9EAD-78CA0C0D73B9}][/cover] */
/* [cover parentID={215E3BF7-D5CD-4310-9508-58DD1BE281E0}][/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}][/cover] */
#define WDG_17_SCU_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"$WdgCoreID"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
#include "Wdg_17_Scu_MemMap.h"
/* MISRA2012_RULE_8_4_JUSTIFICATION: Prior declaration is not required as it
used same files. scope not limited with static to avoid compiler warning */
/* MISRA2012_RULE_8_7_JUSTIFICATION: Prior declaration is not required as it
used same files. scope not limited with static to avoid compiler warning */
[!IF "WdgGeneral/WdgTriggerTimerSelection = 'GTM_TIMER'"!][!//
/* [cover parentID={6F07A3E6-F4C8-475f-BCEF-60BDE1A5836D}][/cover] */
/* [cover parentID={EEBB0CD6-CB0F-487c-A5CC-86DCB88CE5AA}][/cover] */
[!IF "$VariantsConfigured = num:i(1)"!][!//
static const Mcu_17_Gtm_TomAtomChConfigType Wdg_GtmConfig_[!"$WdgCoreID"!]_[!"$PredefinedVarName"!][2] =
[!ELSE!][!//
static const Mcu_17_Gtm_TomAtomChConfigType Wdg_GtmConfig_[!"$WdgCoreID"!][2] = 
[!ENDIF!][!//
{
/*GTM channel structure for Slow*/
 {
  /*Gtm module used to services wdg*/
  [!"$GtmModule"!],
  /* Timer Number Module No | Timer Channel No */
  [!"num:inttohex(bit:or(bit:shl($GtmModuleNo, num:i(8)), $GtmChannelNo))"!],
  /* Ctrl register load value */
  [!"$CtrlReg"!],
  /*Timer Channel CN0 value*/
  0x0U,
  /*Timer Channel CM0 value*/
  [!"$GtmSlowTimeTick"!]U,
  /*Timer Channel CM1 value*/
  0x0U,
  /*Timer Channel SR0 value*/
  [!"$GtmSlowTimeTick"!]U,
  /*Timer Channel SR1 value*/
  0x0U,
  /*Channel to Port Value*/
  0x0U,
  /*Timer Channel Interrupt Enable value*/
  0x81U
 },
 /*GTM channel structure for Fast*/
 {
  /*Gtm module used to services wdg*/
  [!"$GtmModule"!],
  /* Timer Number Module No | Timer Channel No */
  [!"num:inttohex(bit:or(bit:shl($GtmModuleNo, num:i(8)), $GtmChannelNo))"!],
  /* Ctrl register load value */
  [!"$CtrlReg"!],
  /*Timer Channel CN0 value*/
  0x0U,
  /*Timer Channel CM0 value*/
  [!"$GtmFastTimeTick"!]U,
  /*Timer Channel CM1 value*/
  0x0U,
  /*Timer Channel SR0 value*/
  [!"$GtmFastTimeTick"!]U,
  /*Timer Channel SR1 value*/
  0x0U,
   /*Channel to Port Value*/
  0x0U,
  /*Timer Channel Interrupt Enable value*/
  0x81U
 }
};
[!ELSE!][!// 
/* MISRA2012_RULE_8_4_JUSTIFICATION: Prior declaration is not required as it
used same files. scope not limited with static to avoid compiler warning */
/* MISRA2012_RULE_8_7_JUSTIFICATION: Prior declaration is not required as it
used same files. scope not limited with static to avoid compiler warning */
/* [cover parentID={6F07A3E6-F4C8-475f-BCEF-60BDE1A5836D}][/cover] */
[!IF "$VariantsConfigured = num:i(1)"!][!//
static const Mcu_17_Stm_TimerConfigType Wdg_StmConfig_[!"$WdgCoreID"!]_[!"$PredefinedVarName"!] =
[!ELSE!][!//
static const Mcu_17_Stm_TimerConfigType Wdg_StmConfig_[!"$WdgCoreID"!] = 
[!ENDIF!][!//
{
  /*STM compare Reg */
  0x00000000U,
  /* StmTimerId*/
  0x[!"$StmTimerUsed"!]U,
  /*Cmp Register Id*/
  0x[!"$StmCmpRegUsed"!]U,
  /* Value for the CMCON register */
  0x1FU,
  /* Reserved */
  0x00U
};
[!ENDIF!][!//
/* MISRA2012_RULE_8_4_JUSTIFICATION: Declaration is as per Autosar guidelines
provided in the application where init is invoked */
/* MISRA2012_RULE_8_7_JUSTIFICATION: Declaration is as per Autosar guidelines
provided in the application where init is invoked */
/* [cover parentID={798DB1E7-891C-4148-8C16-7DC3DC9E7A4E}][/cover] */
[!IF "$VariantsConfigured = num:i(1)"!][!//
const struct Wdg_17_Scu_ConfigType Wdg_17_Scu_Config_[!"$WdgCoreID"!]_[!"$PredefinedVarName"!] =
[!ELSE!][!//
const struct Wdg_17_Scu_ConfigType Wdg_17_Scu_Config_[!"$WdgCoreID"!] =
[!ENDIF!][!//
{
[!IF "WdgGeneral/WdgTriggerTimerSelection = 'GTM_TIMER'"!][!//
[!IF "$VariantsConfigured = num:i(1)"!][!//
Wdg_GtmConfig_[!"$WdgCoreID"!]_[!"$PredefinedVarName"!],
[!ELSE!][!//
Wdg_GtmConfig_[!"$WdgCoreID"!],
[!ENDIF!][!//
[!ELSE!][!//
/*STM compare Reg used for Servicing*/
[!IF "$VariantsConfigured = num:i(1)"!][!//
&Wdg_StmConfig_[!"$WdgCoreID"!]_[!"$PredefinedVarName"!],
[!ELSE!][!//
&Wdg_StmConfig_[!"$WdgCoreID"!],
[!ENDIF!][!//

[!ENDIF!][!//
/*FastMode reload value*/
(uint16)[!"num:i($FastModeReloadValue)"!],
/*SlowMode reload value*/     
[!"num:i($SlowModeReloadValue)"!],  
/*Fast refresh time*/     
[!"num:i(round($FastRefreshTime))"!],  
/*Slow refresh time*/      
[!"num:i(round($SlowRefreshTime))"!],  
/*Wdg initial timeout*/    
[!"num:i($Wdg_InitialTout)"!],  
/*Wdg maximum timeout*/   
[!"num:i($Wdg_MaxTout)"!],  
/*Default mode*/      
[!"$DefaultMode"!], 
/*Core Disable allowed status*/       
[!"$WdgCoreDisableStatus"!], 
/*Core Id*/     
[!"$WdgCoreID"!],
/*CPU Wdg Password*/     
[!"$WdgPswd"!]   

};

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* [cover parentID={5EE58D70-1E64-4a21-8825-51D21541C2A2}][/cover] */
/* [cover parentID={21E223CA-7026-47ff-B7ED-F79BD631FB4B}][/cover] */
/* [cover parentID={459E6B9A-27BA-46a8-8288-D1A3AD1F98D6}][/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}][/cover] */
#define WDG_17_SCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"$WdgCoreID"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
#include "Wdg_17_Scu_MemMap.h"
[!ENDFOR!]
[!ENDSELECT!]

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/


/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/


/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/


/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/


/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
