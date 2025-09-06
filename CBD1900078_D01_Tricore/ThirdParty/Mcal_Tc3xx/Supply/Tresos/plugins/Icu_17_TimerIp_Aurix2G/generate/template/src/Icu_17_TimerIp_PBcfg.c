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
**  FILENAME  : Icu_17_TimerIp_PBcfg.c                                        **
**                                                                            **
**  VERSION   : 10.0.0                                                        **
**                                                                            **
**  DATE      : 2018-08-07                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : NA                                                **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID= {D6496C23-F067-4a6b-9096-766E69AEC50A} ]  **
**                                                                            **
**  DESCRIPTION  : Code template source file for Icu Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Icu Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!]
[!//
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
**  FILENAME  : Icu_17_TimerIp_PBcfg.c                                        **
**                                                                            **
**  VERSION   : 10.0.0                                                        **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                                      **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                                          **
**                                                                            **
**  BSW MODULE DECRIPTION : NA                                                **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Icu configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Icu Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion for config data
[/cover] */
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

/* [cover parentID={F285FCB3-45C4-4d79-8FAE-8B06A60000B5}]  [/cover] */ 
[!IF "not(node:exists(as:modconf('Mcu')[1]))"!]
  [!ERROR!][!//
    ICU_17_TIMERIP Code Generator: Mcu module is not added to the project.
  [!ENDERROR!][!//
[!ENDIF!]

/*******************************************************************************
**                       Includes                                             **
*******************************************************************************/

/* Include module header File */
#include "Icu_17_TimerIp.h"

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_GTM_INTERRUPT_LEVEL_MODE          (0U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_GTM_INTERRUPT_PULSE_MODE          (1U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_GTM_INTERRUPT_PULSE_NOTIFY_MODE   (2U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_GTM_INTERRUPT_SINGLE_PULSE_MODE   (3U)

/* GTM TBU selections */
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_TIMEBASE_TBU_TS0 (0U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_TIMEBASE_TBU_TS1 (1U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_TIMEBASE_TBU_TS2 (2U)

/* CCU6 Connections */
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_CCU6_CCINA  (0U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_CCU6_CCINB  (1U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_CCU6_CCINC  (2U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_CCU6_CCIND  (3U)

/* #define for wakeup capable or not */
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_WAKEUPCAPABLE                ((uint8)1)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_NOT_WAKEUPCAPABLE            ((uint8)0)

/* Configurable Clocks used in pbcfg.h*/
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_GTM_CONFIGURABLE_CLOCK_0   (0U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_GTM_CONFIGURABLE_CLOCK_1   (1U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_GTM_CONFIGURABLE_CLOCK_2   (2U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_GTM_CONFIGURABLE_CLOCK_3   (3U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_GTM_CONFIGURABLE_CLOCK_4   (4U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_GTM_CONFIGURABLE_CLOCK_5   (5U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_GTM_CONFIGURABLE_CLOCK_6   (6U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_GTM_CONFIGURABLE_CLOCK_7   (7U)
 /*MISRA2012_RULE_2_5_JUSTIFICATION:
   Uses depends upon configuration done in configuration tool*/
#define ICU_INPUT_OF_CURRENT_TIM_CHANNEL  (0U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_INPUT_OF_PREVIOUS_TIM_CHANNEL  (1U)

/*
Configuration Options:
IcuAssignedHwunit
*/

/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_ERS0   (0U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_ERS1   (1U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_ERS2   (2U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_ERS3   (3U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_ERS4   (4U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_ERS5   (5U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_ERS6   (6U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_ERS7   (7U)

/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_INPUT_CHL_A   (0 << 3U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_INPUT_CHL_B   (1 << 3U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_INPUT_CHL_C   (2 << 3U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_INPUT_CHL_D   (3 << 3U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_INPUT_CHL_E   (4 << 3U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_INPUT_CHL_F   (5 << 3U)

/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_OGU0   (0 << 6U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_OGU1   (1 << 6U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_OGU2   (2 << 6U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_OGU3   (3 << 6U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_OGU4   (4 << 6U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_OGU5   (5 << 6U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_OGU6   (6 << 6U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_OGU7   (7 << 6U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_IMMEDIATE_EDGE_PROPAGATION_MODE   (0U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_DEGLITCH_WITH_HOLD_COUNTER   (3U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_DEGLITCH_WITH_UPDOWN_COUNTER   (1U)
/*
Define for unused ERU Line 
*/
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ERU_OGULINE_UNUSED   ((uint16)(0xFFFFU))

  /* CCU defines */
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_CCU60_CC60 0x00U
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_CCU60_CC61 0x10U
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_CCU60_CC62 0x20U
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_CCU61_CC60 0x01U
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_CCU61_CC61 0x11U
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_CCU61_CC62 0x21U
/*
Define for CCU6 SRC Nodes 
*/
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_CCU6_NODE_SR0   (0U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_CCU6_NODE_SR1   (1U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_CCU6_NODE_SR2   (2U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_CCU6_NODE_SR3   (3U)
/*
Define for GPT12 Timers 
*/
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_GPT12_T2   (0U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_GPT12_T3   (1U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_GPT12_T4   (2U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_GPT12_T5   (3U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_ASSIGN_GPT12_T6   (4U)
/*
Define for GPT12 Timer Prescalar 
*/
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_GPT12_BPS1_FGPT_8   (0U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_GPT12_BPS1_FGPT_4   (1U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_GPT12_BPS1_FGPT_32   (2U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_GPT12_BPS1_FGPT_16   (3U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_GPT12_BPS2_FGPT_4   (0U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_GPT12_BPS2_FGPT_2   (1U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_GPT12_BPS2_FGPT_16   (2U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_GPT12_BPS2_FGPT_8   (3U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_GPT12_BPSX_NONE   (0xFFU)

/*
Define for Core identification 
*/
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_CORE0   (0U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_CORE1   (0x100U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_CORE2   (0x200U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_CORE3   (0x300U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_CORE4   (0x400U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Uses depends upon configuration done in configuration tool*/
#define ICU_CORE5   (0x500U)


/*******************************************************************************
**                      Private Function like Macros                          **
*******************************************************************************/

[!NOCODE!][!//
[!INCLUDE "Icu_17_TimerIp.m"!][!//
[!ENDNOCODE!][!//

[!SELECT "as:modconf('Icu')[1]"!][!//
[!NOCODE!][!//
  [!VAR "IcuEruChannelNum0" = "'ERU_OGULINE_UNUSED'"!]
  [!VAR "IcuEruChannelNum1" = "'ERU_OGULINE_UNUSED'"!]
  [!VAR "IcuEruChannelNum2" = "'ERU_OGULINE_UNUSED'"!]
  [!VAR "IcuEruChannelNum3" = "'ERU_OGULINE_UNUSED'"!]
  [!VAR "IcuEruChannelNum4" = "'ERU_OGULINE_UNUSED'"!]
  [!VAR "IcuEruChannelNum5" = "'ERU_OGULINE_UNUSED'"!]
  [!VAR "IcuEruChannelNum6" = "'ERU_OGULINE_UNUSED'"!]
  [!VAR "IcuEruChannelNum7" = "'ERU_OGULINE_UNUSED'"!]
[!ENDNOCODE!][!//
/*******************************************************************************
**                       Function Declarations                                **
*******************************************************************************/

/******************************************************************************/
[!VAR "ReportWakeupSource" = "IcuGeneral/IcuReportWakeupSource"!][!//
[!NOCODE!][!//
[!VAR "NotifyFunctionDatabase" = "''"!][!//
[!LOOP "node:order(./IcuConfigSet/IcuChannel/*)"!][!//
  /*****BEGIN of Notification function definition from configuration**********/
    [!VAR "NotifyFunction" = "'(Icu_17_TimerIp_NotifiPtrType)(0)'"!][!//
    [!VAR "MeasMode" = "./IcuMeasurementMode"!][!//
    [!IF "$MeasMode = 'ICU_MODE_TIMESTAMP'"!][!//
      [!IF "node:exists(./IcuTimestampMeasurement/*[1]/IcuTimestampNotification/*[1]) = 'true'"!][!//
        [!VAR "NotifyFunction" = "./IcuTimestampMeasurement/*[1]/IcuTimestampNotification/*[1]"!][!//
      [!ENDIF!][!//
    [!ELSEIF "$MeasMode = 'ICU_MODE_SIGNAL_EDGE_DETECT'"!][!//
      [!IF "node:exists(./IcuSignalEdgeDetection/*[1]/IcuSignalNotification/*[1]) = 'true'"!][!//
        [!VAR "NotifyFunction" = "./IcuSignalEdgeDetection/*[1]/IcuSignalNotification/*[1]"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  
    [!IF "string-length($NotifyFunction) = 0"!][!//
      [!VAR "NotifyFunction" = "'(Icu_17_TimerIp_NotifiPtrType)(0)'"!][!//
    [!ENDIF!][!//
    [!IF "num:isnumber($NotifyFunction)= 'true'"!][!//
      [!VAR "NotifyFunction" = "'(Icu_17_TimerIp_NotifiPtrType)(0)'"!][!//
    [!ENDIF!][!//
    [!IF "$NotifyFunction = '"NULL"' or $NotifyFunction = 'NULL'"!][!//
      [!VAR "NotifyFunction" = "'(Icu_17_TimerIp_NotifiPtrType)(0)'"!][!//
    [!ENDIF!][!//
    /*****END of Notification function definition from configuration**********/
  [!IF "$NotifyFunction != '(Icu_17_TimerIp_NotifiPtrType)(0)'"!][!//
    [!VAR "NotifyFunctionDatabase" = "concat($NotifyFunctionDatabase,$NotifyFunction,',')"!][!//
    [!IF "'true' = text:uniq(text:split($NotifyFunctionDatabase,','),$NotifyFunction)"!]
[!CODE!]
extern void [!"$NotifyFunction"!] (void);
[!ENDCODE!]
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!][!//
/******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
[!NOCODE!][!//

/**************************************************************/
/*************** Channel configuration logic ******************/
/**************************************************************/
[!ENDNOCODE!][!//
[!SELECT "as:modconf('Icu')[1]"!][!//
[!NOCODE!][!//
[!VAR "IcuIndex" = "@index"!][!//
[!VAR "EruModuleLookUp" = "num:i(0)"!][!//
[!VAR "OguModuleLookUp" = "num:i(0)"!][!//
[!VAR "CcuModuleLookUp" = "num:i(0)"!][!//
[!VAR "GtmModuleLookUp" = "num:i(0)"!][!//
[!VAR "GptModuleLookUp" = "num:i(0)"!][!//
[!VAR "MaxChannelsCore0"= "num:i(0)"!][!//
[!VAR "MaxChannelsCore1"= "num:i(0)"!][!//
[!VAR "MaxChannelsCore2"= "num:i(0)"!][!//
[!VAR "MaxChannelsCore3"= "num:i(0)"!][!//
[!VAR "MaxChannelsCore4"= "num:i(0)"!][!//
[!VAR "MaxChannelsCore5"= "num:i(0)"!][!//
[!VAR "Ccu6xClockSelectValue" = "num:i(0)"!][!//
[!VAR "GPT1Prescalar" = "'NONE'"!][!//
[!VAR "GPT2Prescalar" = "'NONE'"!][!//
[!VAR "Gpt12ClockSelectValue" = "num:i(0)"!][!//
[!VAR "Gpt12TimerSelection" = "num:i(0)"!][!//
[!CALL "ICU_CG_GenerateModuleMap"!][!//
[!VAR "MaxChannels"= "num:i(count(./IcuConfigSet/IcuChannel/*))"!][!//
[!ENDNOCODE!][!//
[!FOR "CoreId" = "num:i(1)" TO "num:i(6)"!][!//
[!NOCODE!][!//
[!VAR "MaxChannelsCorex"= "num:i(0)"!][!//
[!VAR "EdDe" = "num:i(0)"!][!//
[!VAR "EdCn" = "num:i(0)"!][!//
[!VAR "SgMe" = "num:i(0)"!][!//
[!VAR "TiSt" = "num:i(0)"!][!//
[!VAR "UnionIndex" = "num:i(0)"!][!//
[!ENDNOCODE!][!//
/* 
   Channel Configuration 
 */
/***********Start of CORE [!"num:i(num:i($CoreId) - num:i(1))"!] configurations**************/
[!IF "contains($CGCoreMap,concat('CORE',num:i($CoreId) - num:i(1))) or ((num:i($CGMasterCoreId_Extract) = (num:i($CoreId) - num:i(1))) and (count(text:split($CGCoreMap,',')) != $MaxChannels))"!][!//
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}] */
/* Memory mapping for config data */
/* [/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i(num:i($CoreId) - num:i(1))"!]_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
   guideline.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
/* [cover parentID={63629861-9B79-4f68-A58D-AB55F8757346}] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
[!IF "$VariantsConfigured = num:i(1)"!]
static const Icu_17_TimerIp_ChannelConfigType Icu_17_TimerIp_kChannelConfigCore_[!"num:i(num:i($CoreId) - num:i(1))"!]_[!"$PredefinedVarName"!][ ] =
[!ELSE!]
static const Icu_17_TimerIp_ChannelConfigType Icu_17_TimerIp_kChannelConfigCore_[!"num:i(num:i($CoreId) - num:i(1))"!][ ] =
[!ENDIF!]
{
[!FOR "ChannelId" = "num:i(1)" TO "num:i($MaxChannels)"!][!//
[!SELECT "./IcuConfigSet/IcuChannel/*[IcuChannelId = num:i($ChannelId) - num:i(1)]"!][!//
[!NOCODE!][!//
[!CALL "ICU_CG_ValidateChAllocation", "CoreNumber" = "num:i($CoreId) - num:i(1)", "Channel" = "node:name(node:current())"!][!//
[!ENDNOCODE!][!//
[!IF "$CGAllocationResult = 'TRUE'"!][!//
[!NOCODE!][!//
[!VAR "MaxChannelsCorex"= "num:i($MaxChannelsCorex + 1)"!]
[!ENDNOCODE!][!//
  {
  [!NOCODE!][!//
  [!//      Variable initializations
  [!VAR "WakeupValue" = "'ICU_NOT_WAKEUPCAPABLE'"!][!//
  [!VAR "MeasMode" = "./IcuMeasurementMode"!][!//
  [!VAR "MeasModeValue" = "$MeasMode"!][!//
  [!VAR "ChannelConnection" = "'0U'"!][!//
  [!VAR "nodepath" = "IcuAssignedHwUnit"!][!//
  [!VAR "MeasKindValue" = "'0U'"!][!//
  [!VAR "BufferKind" = "'0'"!][!//
  [!VAR "EdgeValue" = "./IcuDefaultStartEdge"!][!//
  [!VAR "HWused" = "IcuAssignedHwUnit"!]   
  [!VAR "nodeval" = "IcuAssignedHwUnit"!]
  [!VAR "val" = "num:i(0)"!][!//
  [!VAR "NotifyFunction" = "''"!][!//
  [!VAR "TimChannelClockSelectValue" = "'0U'"!][!//
  [!VAR "TimChannelInputSelectValue" = "'ICU_INPUT_OF_CURRENT_TIM_CHANNEL'"!][!//
  [!VAR "TimChannelGpr0InputSelectValue" = "'0U'"!][!//
  [!VAR "TimChFilterTimeForRisingEdgeValue" = "num:i(0)"!][!//
  [!VAR "TimChFilterTimeForFallingEdgeValue" = "num:i(0)"!][!//
  [!VAR "InterruptModeValue" = "'0U'"!][!//
  [!VAR "FilterValue" = "num:i(0)"!][!//
  [!VAR "TimChFilterCounterFreqSelectValue" = "'0U'"!][!//
  [!VAR "TimChFilterModeForRisingEdgeValue" = "'0U'"!][!//
  [!VAR "TimChFilterModeForFallingEdgeValue" = "'0U'"!][!//
  [!//       wakeup
  [!VAR "WakeupComment" = "'Not applicable'"!][!//
  [!VAR "WakeupReason" = "num:i(0)"!][!//
  
  [!IF "$MeasMode = 'ICU_MODE_TIMESTAMP'"!][!//
    [!IF "node:exists(./IcuTimestampMeasurement/*[1]/IcuTimestampNotification/*[1]) = 'true'"!][!// 
      [!VAR "NotifyFunction" = "./IcuTimestampMeasurement/*[1]/IcuTimestampNotification/*[1]"!][!//
    [!ELSE!][!// 
      [!VAR "NotifyFunction" = "''"!][!//
    [!ENDIF!][!// 
  [!ELSEIF "$MeasMode = 'ICU_MODE_SIGNAL_EDGE_DETECT'"!][!//
    [!IF "node:exists(./IcuSignalEdgeDetection/*[1]/IcuSignalNotification/*[1]) = 'true'"!][!// 
      [!VAR "NotifyFunction" = "./IcuSignalEdgeDetection/*[1]/IcuSignalNotification/*[1]"!][!//
    [!ELSE!][!// 
      [!VAR "NotifyFunction" = "''"!][!//
    [!ENDIF!][!// 
  [!ENDIF!][!//
  [!IF "string-length($NotifyFunction) = 0 or $NotifyFunction = '"NULL"' or $NotifyFunction = 'NULL' "!][!//
    [!VAR "NotifyFunction" = "'(Icu_17_TimerIp_NotifiPtrType)0'"!][!//
  [!ELSE!][!//
    [!IF "num:isnumber($NotifyFunction)= 'true'"!][!//
      [!VAR "NotifyFunction" = "concat('(Icu_17_TimerIp_NotifiPtrType)',$NotifyFunction,'U')"!]
    [!ELSE!][!//
      [!VAR "NotifyFunction" = "concat('&',$NotifyFunction)"!]
    [!ENDIF!][!//
  [!ENDIF!][!//
  
  [!IF "$MeasModeValue = 'ICU_MODE_SIGNAL_EDGE_DETECT'"!][!//  
    [!VAR "Wakeup" = "./IcuWakeupCapability"!][!//
    [!VAR "chindex" = "num:i($ChannelId) - num:i(1)"!][!//
    [!IF "$Wakeup = 'true'"!][!//
      [!VAR "WakeupValue" = "'ICU_WAKEUPCAPABLE'"!][!//
    [!ENDIF!][!//
    [!VAR "Wakeupreference" = "''"!][!//
    [!IF "$Wakeup = 'true'"!][!//
      [!IF "node:exists(./IcuWakeup/*[1]/IcuChannelWakeupInfo/*[1]) = 'true' and $ReportWakeupSource = 'true'"!][!//         
        [!VAR "Wakeupreference" = "node:name(node:ref(./IcuWakeup/*[1]/IcuChannelWakeupInfo/*[1]))"!][!//
        [!VAR "WakeupComment" = "concat('WakeupSourceId Value for Channel ',num:i($chindex))"!][!//
      [!ELSEIF "$ReportWakeupSource = 'true'"!][!//
       [!ERROR!][!//
       Error: Wrong Configuration. Channel Wakeup Info not configured for channel [!"num:i($chindex)"!]
       [!ENDERROR!][!//
      [!ENDIF!][!//        
    [!ENDIF!][!//
    [!IF "string-length($Wakeupreference) > 0 and $ReportWakeupSource = 'true'"!][!//
      [!VAR "WakeupReason" = "node:ref(./IcuWakeup/*[1]/IcuChannelWakeupInfo/*[1])/EcuMWakeupSourceId"!][!//
    [!ENDIF!][!//   
  [!ENDIF!][!//
  [!IF "$MeasMode = 'ICU_MODE_SIGNAL_MEASUREMENT'"!][!//
    [!VAR "MeasKind" = "./IcuSignalMeasurement/*[1]/IcuSignalMeasurementProperty"!][!//
    [!IF "(not(string-length($MeasKind))) != 0"!][!//
       [!ERROR!][!//
       Error: Wrong Configuration. Signal Measurement Property is not provided for a Signal Measurement Channel
       [!ENDERROR!][!//
    [!ELSE!]
      [!IF "$MeasKind = 'ICU_HIGH_TIME'"!]
        [!VAR "EdgeValue" = "'ICU_FALLING_EDGE'"!][!//
      [!ELSEIF "$MeasKind = 'ICU_LOW_TIME'"!]
        [!VAR "EdgeValue" = "'ICU_RISING_EDGE'"!][!//
      [!ENDIF!]
    [!ENDIF!][!//
    [!VAR "MeasKindValue" = "$MeasKind"!][!//
  [!ELSEIF "$MeasMode = 'ICU_MODE_TIMESTAMP'"!][!//
    [!VAR "MeasKind" = "./IcuTimestampMeasurement/*[1]/IcuTimestampMeasurementProperty"!][!//
    [!IF "(not(string-length($MeasKind))) != 0"!][!//
       [!ERROR!][!//
       Wrong Configuration:Timestamp Measurement Property is not provided for a Timestamp Channel
       [!ENDERROR!][!//
    [!ENDIF!][!//
    [!VAR "MeasKindValue" = "$MeasKind"!][!//
  [!ENDIF!][!//
  [!VAR "OverflowISRThresholdVal" ="0"!][!//
  [!IF "($HWused = 'GTM')"!][!//
    [!VAR "OverflowISRThresholdVal" ="./GtmTimerInputConfiguration/*[1]/TimChannelGeneral/OverflowISRThreshold"!][!//
    [!VAR "GtmTimPath" = "node:path(node:ref(./GtmTimerInputConfiguration/*[1]/GtmTimerUsed))"!]    
    [!VAR "GtmTimerModNo" = "text:split($GtmTimPath, 'AllocationConf_')[4]"!]
    [!VAR "GtmTimerModNo" = "text:split($GtmTimerModNo,'/')[1]"!]
    [!VAR "GtmTimerChNo" = "text:split($GtmTimPath,'ChannelAllocationConf_')[2]"!]
    [!VAR "GlobalChannelNumber" = "num:i(num:add(num:mul(num:i($GtmTimerModNo) , num:i(8)) , num:i($GtmTimerChNo)))"!][!//
    [!VAR "Cell" = "concat($GlobalChannelNumber,'U')"!][!//
    [!VAR "SetPosition" = "num:i(num:add(num:i($GtmTimerChNo), num:i(bit:shl($GtmTimerModNo, 3))))"!][!//
    [!VAR "CellOption" = "'ICU_GTM_OPTION'"!][!//
    [!IF "(bit:and($GtmModuleLookUp, bit:shl(1,$SetPosition))) != '0'"!][!//
      [!ERROR!][!//
      ICU: GTM TIM[!"$GtmTimerModNo"!] CHL[!"$GtmTimerChNo"!] is configured more than once
      [!ENDERROR!][!//
    [!ENDIF!][!//
    [!VAR "GtmModuleLookUp" = "bit:bitset($GtmModuleLookUp, $SetPosition)"!][!//
    /* Set Port Select Parameters*/
    [!IF "(./GtmTimerInputConfiguration/*[1]/TimChannelGeneral/TimChannelPortPinSelect) = 'NONE_SEL0'"!][!//
      [!VAR "ChannelConnection" = "num:i(0)"!][!// 
    [!ELSE!][!// 
      [!VAR "ChannelConnection" = "num:i(substring-before(substring-after(./GtmTimerInputConfiguration/*[1]/TimChannelGeneral/TimChannelPortPinSelect,'_SEL'),'_PORT'))"!][!//
    [!ENDIF!][!//
    [!VAR "temp1" ="node:value(./GtmTimerInputConfiguration/*[1]/TimChannelGeneral/TimChannelInputSelect)"!][!//
    [!VAR "TimChannelInputSelectValue" = "concat('ICU_',$temp1)"!][!//
    [!VAR "temp1" ="node:value(./GtmTimerInputConfiguration/*[1]/TimChannelGeneral/TimChannelClockSelect)"!][!//
    [!VAR "TimChannelClockSelectValue" = "concat('ICU_',$temp1)"!][!//
    [!VAR "temp1" ="node:value(./GtmTimerInputConfiguration/*[1]/TimChannelGeneral/TimChannelGpr0InputSelect)"!][!//
    [!VAR "TimChannelGpr0InputSelectValue" = "concat('ICU_',$temp1)"!][!//
    [!VAR "TimChFilterTimeForFallingEdgeValue" ="node:value(./GtmTimerInputConfiguration/*[1]/TimChannelFilterConfig/TimChFilterTimeForFallingEdge)"!][!//
    [!VAR "TimChFilterTimeForRisingEdgeValue" ="node:value(./GtmTimerInputConfiguration/*[1]/TimChannelFilterConfig/TimChFilterTimeForRisingEdge)"!][!//
    [!VAR "TimChannelFilterEnableValue" ="node:value(./GtmTimerInputConfiguration/*[1]/TimChannelFilterConfig/TimChannelFilterEnable)"!][!//
    [!VAR "temp1" ="node:value(./GtmTimerInputConfiguration/*[1]/TimChannelFilterConfig/TimChFilterCounterFreqSelect)"!][!//
    [!VAR "TimChFilterCounterFreqSelectValue" = "concat('ICU_',$temp1)"!][!//
    [!VAR "temp1" ="node:value(./GtmTimerInputConfiguration/*[1]/TimChannelFilterConfig/TimChFilterModeForRisingEdge)"!][!//
    [!VAR "TimChFilterModeForRisingEdgeValue" = "concat('ICU_',$temp1)"!][!//
    [!VAR "temp1" ="node:value(./GtmTimerInputConfiguration/*[1]//TimChannelFilterConfig/TimChFilterModeForFallingEdge)"!][!//
    [!VAR "TimChFilterModeForFallingEdgeValue" = "concat('ICU_',$temp1)"!][!//
    [!VAR "temp1" ="node:value(./GtmTimerInputConfiguration/*[1]/TimChannelGeneral/TimInterruptMode)"!][!//
    [!VAR "InterruptModeValue" = "concat('ICU_',$temp1)"!][!//
    [!IF "$TimChannelFilterEnableValue = 'true'"!][!//
      [!VAR "FilterValue" = "num:i(1)"!][!//
    [!ELSE!][!//
      [!VAR "FilterValue" = "num:i(0)"!][!//
    [!ENDIF!][!//
  [!ELSEIF "($HWused = 'ERU')"!][!//
    [!VAR "ChannelLocation" = "node:name(node:ref(./ERUInputConfiguration/*[1]/EruErsReference))"!][!//
    [!VAR "ChannelNumber" = "text:split($ChannelLocation, '_')[position()-1 = 1]"!][!//
    [!VAR "SetPosition" = "($ChannelNumber)"!][!//    
    [!IF "(bit:and($EruModuleLookUp, bit:shl(1,$SetPosition))) != '0'"!][!//
       [!ERROR!][!//
       ERU[!"$ChannelNumber"!] is configured more than once
       [!ENDERROR!][!//
    [!ENDIF!][!//
    [!VAR "EruModuleLookUp" = "bit:bitset($EruModuleLookUp, $SetPosition)"!][!//    
    [!VAR "ChannelLocation" = "node:name(node:ref(./ERUInputConfiguration/*[1]/EruOguReference))"!][!//
    [!VAR "ChannelNumber" = "text:split($ChannelLocation, '_')[position()-1 = 1]"!][!//
    [!VAR "SetPosition" = "($ChannelNumber)"!][!//    
    [!IF "(bit:and($OguModuleLookUp, bit:shl(1,$SetPosition))) != '0'"!][!//
       [!ERROR!][!//
       OGU[!"$ChannelNumber"!] is configured more than once
       [!ENDERROR!][!//
    [!ENDIF!][!//
    [!VAR "OguModuleLookUp" = "bit:bitset($OguModuleLookUp, $SetPosition)"!][!//
    [!VAR "line" = "./ERUInputConfiguration/*[1]/EruInputPin"!][!//
    [!VAR "nodeval" = "node:name(node:ref(./ERUInputConfiguration/*[1]/EruErsReference))"!][!//
    [!VAR "nodevalforogu" = "node:name(node:ref(./ERUInputConfiguration/*[1]/EruOguReference))"!][!//   
    [!VAR "linenum2g" = "substring($line,11,1)"!][!//
    [!VAR "Ersnumber2g" = "text:split($nodeval, '_')[position()-1 = 1]"!][!//
    [!VAR "Ogunumber2g" = "text:split($nodevalforogu, '_')[position()-1 = 1]"!][!//
    [!VAR "temp2" = "concat('ICU_ASSIGN_INPUT_CHL_',$linenum2g)"!][!//
    [!VAR "temp1" = "concat('ICU_ASSIGN_ERS',$Ersnumber2g)"!][!//
    [!VAR "temp3" = "concat('ICU_ASSIGN_OGU',$Ogunumber2g)"!][!//
    [!VAR "Cell" = "concat('(',$temp1,'|',$temp2,'|',$temp3,')')"!][!// 
    [!VAR "CellOption" = "'ICU_ERU_OPTION'"!]
  [!ELSEIF "($HWused = 'CCU6')"!][!//
    [!VAR "nodeval" = "./CCU6CC6Configuration/*[1]/Cc6xChannel"!][!//
    [!VAR "CellOption" = "'ICU_CCU_OPTION'"!][!//
    [!VAR "CcuChannelNumber" = "text:toupper($nodeval)"!][!//
    [!VAR "ChannelNumberid" = "text:split($CcuChannelNumber, 'CC6')[position()- num:i(1) = 0]"!][!//
    [!VAR "KernalNodeName" = "node:name(node:ref(./CCU6CC6Configuration/*[1]/CCU6KernelUsed))"!]
    [!VAR "temp1" = "text:split($KernalNodeName, '_')[position()-num:i(1) = num:i(1)]"!][!//
    [!VAR "CcuKernalNumber" = "concat('CCU6', $temp1)"!][!//
    [!VAR "Cell" = "concat('ICU_',$CcuKernalNumber, '_', $CcuChannelNumber)"!][!//
    [!VAR "CcuChannelInputBase" = "./CCU6CC6Configuration/*[1]/CCChannelInputSelection"!][!//
    [!VAR "CcuChannelInput" = "text:split($CcuChannelInputBase, '_')[position()-num:i(1) = num:i(0)]"!][!//
    [!VAR "SetPosition" = "num:i(num:add(num:i($ChannelNumberid), num:i(bit:shl($temp1, num:i(2)))))"!][!//
    [!VAR "ChannelConnection" = "concat('ICU_CCU6_', $CcuChannelInput)"!][!//
    [!IF "(bit:and($CcuModuleLookUp, bit:shl(num:i(1),$SetPosition))) != num:i(0)"!][!//
      [!ERROR!][!//
      ICU: CCU6[!"$temp1"!] CC6[!"$ChannelNumberid"!] is configured more than once
      [!ENDERROR!][!//
    [!ENDIF!][!//
    [!VAR "CcuModuleLookUp" = "bit:bitset($CcuModuleLookUp, $SetPosition)"!][!//
    [!VAR "TimChannelClockSelectValue" = "./CCU6CC6Configuration/*[1]/CCU6xParamters/T12ClkSelection"!][!//
    [!IF "./CCU6CC6Configuration/*[1]/CCU6xParamters/T12PrescalerEnabled = 'true'"!][!//
      [!VAR "TimChannelClockSelectValue" = "num:i($TimChannelClockSelectValue + num:i(8))"!]
    [!ENDIF!][!//
    
    [!IF "bit:getbit($Ccu6xClockSelectValue,num:i(5)*$temp1)"!][!//
      [!IF "num:i(bit:and(bit:xor(bit:shr($Ccu6xClockSelectValue,num:i(1)+(num:i(5)*$temp1)),$TimChannelClockSelectValue),num:i(15))) = num:i(0)"!][!//
        [!VAR "Ccu6xClockSelectValue" = "bit:or(bit:shl($TimChannelClockSelectValue,(num:i(5)*$temp1) + num:i(1)), bit:and($Ccu6xClockSelectValue,bit:not(bit:shl(num:i(31),num:i(5)*$temp1))))"!]
      [!ELSE!][!//
        [!ERROR!][!//
          ICU: CCU6 Kernal [!"$temp1"!] CC6 timer [!"$ChannelNumberid"!] T12 Clock configuration is not consistent.
        [!ENDERROR!][!//
      [!ENDIF!][!//
    [!ELSE!][!//
      [!VAR "Ccu6xClockSelectValue" = "bit:or(bit:shl($TimChannelClockSelectValue,num:i(1)+(num:i(5)*$temp1)),$Ccu6xClockSelectValue)"!]
    [!ENDIF!][!//
    [!VAR "Ccu6xClockSelectValue" = "bit:bitset($Ccu6xClockSelectValue,(num:i(5)*$temp1))"!]
    [!VAR "TimChannelClockSelectValue" = "concat($TimChannelClockSelectValue,'U')"!]
    [!VAR "TimChannelInputSelectValue" = "'ICU_INPUT_OF_CURRENT_TIM_CHANNEL'"!][!//
    [!VAR "CcuChannelIntNode" = "./CCU6CC6Configuration/*[1]/CCU6xParamters/CCU6InterruptNode"!][!//
    [!VAR "InterruptModeValue" = "concat('ICU_CCU6_',$CcuChannelIntNode)"!][!//
  [!ELSEIF "($HWused = 'GPT12')"!][!//
    [!VAR "CellOption" = "'ICU_GPT12_OPTION'"!][!//
    [!VAR "TimerSelection" = "num:i(substring-after(./GPT12Configuration/*[1]/GPT12TimerSelection,'T'))"!][!//
    [!VAR "ChannelConnection" = "./GPT12Configuration/*[1]/GPT12InputPortSelection"!][!//
    [!IF "contains($ChannelConnection,'INA')"!]
      [!VAR "ChannelConnection" = "'0U'"!][!//
    [!ELSEIF "contains($ChannelConnection,'INB')"!][!//
      [!VAR "ChannelConnection" = "'1U'"!][!//
    [!ELSEIF "contains($ChannelConnection,'INC')"!][!//
      [!VAR "ChannelConnection" = "'2U'"!][!//
    [!ELSEIF "contains($ChannelConnection,'IND')"!][!//
      [!VAR "ChannelConnection" = "'3U'"!][!//
    [!ELSE!][!// 
      [!VAR "ChannelConnection" = "'0U'"!][!//
    [!ENDIF!][!// 
    
    [!VAR "Cell" = "concat('ICU_ASSIGN_GPT12_',./GPT12Configuration/*[1]/GPT12TimerSelection)"!][!//
    [!IF "bit:getbit($Gpt12TimerSelection,$TimerSelection)"!]
      [!ERROR!][!//
      GPT12 Timer T[!"$TimerSelection"!] is selected in multiple GPT12 channels.
      [!ENDERROR!][!//
    [!ELSE!][!// 
      [!VAR "Gpt12TimerSelection" = "bit:bitset($Gpt12TimerSelection,$TimerSelection)"!][!//  
    [!ENDIF!][!//
    [!IF "$TimerSelection < num:i(5)"!]
      [!IF "$GPT1Prescalar = 'NONE'"!]
        [!VAR "TimChannelClockSelectValue" = "concat('ICU_GPT12_BPS1_',./GPT12Configuration/*[1]/GPT12Config/GPTxPrescaler)"!][!//
        [!VAR "GPT1Prescalar" = "./GPT12Configuration/*[1]/GPT12Config/GPTxPrescaler"!]
      [!ELSE!]
        [!IF "$GPT1Prescalar != ./GPT12Configuration/*[1]/GPT12Config/GPTxPrescaler"!]
        [!ERROR!][!//
        ICU: GPT1 Timer block prescaler is not consistent.
        [!ENDERROR!][!//
        [!ENDIF!]  
      [!ENDIF!]
    [!ELSE!][!// 
      [!IF "$GPT2Prescalar = 'NONE'"!]
        [!VAR "TimChannelClockSelectValue" = "concat('ICU_GPT12_BPS2_',./GPT12Configuration/*[1]/GPT12Config/GPTxPrescaler)"!][!//
        [!VAR "GPT2Prescalar" = "./GPT12Configuration/*[1]/GPT12Config/GPTxPrescaler"!]
      [!ELSE!]
        [!IF "$GPT2Prescalar != ./GPT12Configuration/*[1]/GPT12Config/GPTxPrescaler"!]
        [!ERROR!][!//
        ICU: GPT2 Timer block prescaler is not consistent.
        [!ENDERROR!][!//
        [!ENDIF!]  
      [!ENDIF!]
    [!ENDIF!][!//
  [!ENDIF!][!//
  
  [!IF "$HWused = 'ERU'"!][!//
    [!VAR "IndexChannel" = "num:i(1)"!][!//
    [!VAR "CommentIndex" = "'Indexing not required'"!][!//
  [!ELSE!][!//
    [!VAR "UnionIndex" = "num:i($UnionIndex + num:i(1))"!][!//
    [!VAR "IndexChannel" = "$UnionIndex"!][!//
    [!VAR "CommentIndex" = "'Ram needed for this channel'"!][!//
  [!ENDIF!][!//
[!ENDNOCODE!][!//
      /* ICU Channel [!"IcuChannelId"!] */
    [!"$NotifyFunction"!],/*Notification-function name*/
    {
      (uint8)[!"text:replace($MeasModeValue,'ICU_','ICU_17_TIMERIP_')"!],/*Measurement Mode*/
      (uint8)[!"text:replace($EdgeValue,'ICU_','ICU_17_TIMERIP_')"!],/*Default Start Edge */
      (uint8)[!"text:replace($MeasKindValue,'ICU_','ICU_17_TIMERIP_')"!],/*Measurement Property*/
      [!"$WakeupValue"!],/*Wakeup capability*/
      /* Assigned Hardware Resource Number */
      /* MISRA2012_RULE_10_4_JUSTIFICATION: No side effects foreseen
        by violating this MISRA rule.*/
      /* MISRA2012_RULE_10_1_JUSTIFICATION: No side effects foreseen
        by violating this MISRA rule. */
      (uint16)[!"$Cell"!],
      (uint8)[!"text:replace($CellOption,'ICU_','ICU_17_TIMERIP_')"!], /* Assigned Hw Unit */
      [!"$ChannelConnection"!], /* PinSelection */
      0U,/* Reserved */
      [!"$TimChFilterTimeForRisingEdgeValue"!]U,/* Filtering time for rising edge */
      [!"$TimChFilterTimeForFallingEdgeValue"!]U,/* Filtering time for falling edge */
      [!"num:i($OverflowISRThresholdVal)"!]U, /* Overflow ISR threshold */
      [!"$InterruptModeValue"!],/* TIM interrupt mode/ CCU6 Int Node */
      [!"$TimChannelClockSelectValue"!], /* Channel Clock Select */
      [!"$TimChannelGpr0InputSelectValue"!],  /* Gpr0 input select for the Tim channel */
      [!"num:i($FilterValue)"!]U, /* Enables Filter for the Channel */
      /*Decides the filter Counter frequency for the TIM Channel */
      [!"$TimChFilterCounterFreqSelectValue"!],
      /*Decides the filter mode for rising Edge of the TIM Channel Input */
      [!"$TimChFilterModeForRisingEdgeValue"!],
      /*Decides the filter mode for falling Edge of the TIM Channel Input */
      [!"$TimChFilterModeForFallingEdgeValue"!],
      /*Input channel select : current chl or previous chl */
      [!"$TimChannelInputSelectValue"!]
    },
#if (ICU_17_TIMERIP_REPORT_WAKEUP_SOURCE == STD_ON)
    {
      [!"$WakeupReason"!]U /*[!"$WakeupComment"!]*/
    },
#endif
    /* [!"$CommentIndex"!] */
    [!"num:i($IndexChannel - num:i(1))"!]U
  }[!IF "$ChannelId != $MaxChannels"!],[!ENDIF!]
[!/* Validate the CCU channels in MCU which are configured for USED_BY_ICU_DRIVER but are not really used
     for ICU channel 
*/!]
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDFOR!][!// loop for all channels
};

/*  [/cover] */

/* [cover parentID={8C015093-183F-4d05-9AB7-4F5846518315}] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
[!IF "$VariantsConfigured = num:i(1)"!]
static const Icu_17_TimerIp_CoreConfigType Icu_17_TimerIp_kConfigCore_[!"num:i(num:i($CoreId) - num:i(1))"!]_[!"$PredefinedVarName"!] =
[!ELSE!]
static const Icu_17_TimerIp_CoreConfigType Icu_17_TimerIp_kConfigCore_[!"num:i(num:i($CoreId) - num:i(1))"!] =
[!ENDIF!]
{
  /* Pointer to Channel Configuration structure */
[!IF "num:i($MaxChannelsCorex) != num:i(0)"!]
[!IF "$VariantsConfigured = num:i(1)"!]
  &Icu_17_TimerIp_kChannelConfigCore_[!"num:i(num:i($CoreId) - num:i(1))"!]_[!"$PredefinedVarName"!][0],
[!ELSE!]
  &Icu_17_TimerIp_kChannelConfigCore_[!"num:i(num:i($CoreId) - num:i(1))"!][0],
[!ENDIF!]
[!ELSE!][!//
  NULL_PTR,
[!ENDIF!][!//
  /* MaxChannelCore */
  [!"$MaxChannelsCorex"!],
[!NOCODE!][!//
[!IF "num:i($CoreId) = num:i(1)"!]
[!VAR "MaxChannelsCore0"= "num:i($MaxChannelsCorex)"!]
[!ELSEIF "num:i($CoreId) = num:i(2)"!]
[!VAR "MaxChannelsCore1"= "num:i($MaxChannelsCorex)"!]
[!ELSEIF "num:i($CoreId) = num:i(3)"!]
[!VAR "MaxChannelsCore2"= "num:i($MaxChannelsCorex)"!]
[!ELSEIF "num:i($CoreId) = num:i(4)"!]
[!VAR "MaxChannelsCore3"= "num:i($MaxChannelsCorex)"!]
[!ELSEIF "num:i($CoreId) = num:i(5)"!]
[!VAR "MaxChannelsCore4"= "num:i($MaxChannelsCorex)"!]
[!ELSEIF "num:i($CoreId) = num:i(6)"!]
[!VAR "MaxChannelsCore5"= "num:i($MaxChannelsCorex)"!]
[!ENDIF!]
[!ENDNOCODE!][!//
  /* chunks of union required */
  [!"num:i($UnionIndex)"!],

};
/*  [/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i(num:i($CoreId) - num:i(1))"!]_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
   guideline.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
[!ENDIF!][!//
/***********End of CORE [!"num:i(num:i($CoreId) - num:i(1))"!] configurations**************/

[!ENDFOR!][!// loop of all cores
[!ENDSELECT!][!//
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}] */
/* Memory mapping for config data */
/* [/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
   guideline.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
/* MISRA2012_RULE_8_7_JUSTIFICATION: Module configuration data structure
   declaration as per Autosar guidelines. This data structure may be needed
   by SW units using Icu Driver APIs */
/* MISRA2012_RULE_8_4_JUSTIFICATION: Definition is as per Autosar guidelines */
/* [cover parentID={C5A15715-FF71-486f-B715-DE62FDB0275C}] */
[!IF "$VariantsConfigured = num:i(1)"!]
const Icu_17_TimerIp_ConfigType Icu_17_TimerIp_Config_[!"$PredefinedVarName"!] =
[!ELSE!]
const Icu_17_TimerIp_ConfigType Icu_17_TimerIp_Config =
[!ENDIF!]
{
[!SELECT "IcuConfigSet"!][!//
[!AUTOSPACING!][!//
  /* Pointer to channel configuration set per core */
  {
[!IF "num:i($MaxChannelsCore0) != num:i(0)"!]
[!IF "$VariantsConfigured = num:i(1)"!]
    &Icu_17_TimerIp_kConfigCore_0_[!"$PredefinedVarName"!],
[!ELSE!]
    &Icu_17_TimerIp_kConfigCore_0,
[!ENDIF!]
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!][!//
[!IF "num:i($MaxChannelsCore1) != num:i(0)"!]
[!IF "$VariantsConfigured = num:i(1)"!]
    &Icu_17_TimerIp_kConfigCore_1_[!"$PredefinedVarName"!],
[!ELSE!]
    &Icu_17_TimerIp_kConfigCore_1,
[!ENDIF!]
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!][!//
[!IF "num:i($MaxChannelsCore2) != num:i(0)"!]
[!IF "$VariantsConfigured = num:i(1)"!]
    &Icu_17_TimerIp_kConfigCore_2_[!"$PredefinedVarName"!],
[!ELSE!]
    &Icu_17_TimerIp_kConfigCore_2,
[!ENDIF!]
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!][!//
[!IF "num:i($MaxChannelsCore3) != num:i(0)"!]
[!IF "$VariantsConfigured = num:i(1)"!]
    &Icu_17_TimerIp_kConfigCore_3_[!"$PredefinedVarName"!],
[!ELSE!]
    &Icu_17_TimerIp_kConfigCore_3,
[!ENDIF!]
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!][!//
[!IF "num:i($MaxChannelsCore4) != num:i(0)"!]
[!IF "$VariantsConfigured = num:i(1)"!]
    &Icu_17_TimerIp_kConfigCore_4_[!"$PredefinedVarName"!],
[!ELSE!]
    &Icu_17_TimerIp_kConfigCore_4,
[!ENDIF!]
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!][!//
[!IF "num:i($MaxChannelsCore5) != num:i(0)"!]
[!IF "$VariantsConfigured = num:i(1)"!]
    &Icu_17_TimerIp_kConfigCore_5_[!"$PredefinedVarName"!]
[!ELSE!]
    &Icu_17_TimerIp_kConfigCore_5
[!ENDIF!]
[!ELSE!][!//
    NULL_PTR
[!ENDIF!][!//
  },
[!NOCODE!]
[!VAR "MaxChannelsCore0"= "num:i(0)"!][!//
[!VAR "MaxChannelsCore1"= "num:i(0)"!][!//
[!VAR "MaxChannelsCore2"= "num:i(0)"!][!//
[!VAR "MaxChannelsCore3"= "num:i(0)"!][!//
[!VAR "MaxChannelsCore4"= "num:i(0)"!][!//
[!VAR "MaxChannelsCore5"= "num:i(0)"!][!//
[!VAR "MappingValue"= "num:i(0)"!][!//
[!ENDNOCODE!][!//
#if (ICU_17_TIMERIP_SINGLE_CORE == STD_OFF)
  {
[!VAR "MaxChannels"= "num:i(count(IcuChannel/*))"!][!//
[!FOR "ChannelId" = "num:i(1)" TO "num:i($MaxChannels)"!][!//
[!SELECT "IcuChannel/*[IcuChannelId = num:i($ChannelId) - num:i(1)]"!][!//
  [!NOCODE!][!//
  [!CALL "ICU_CG_GetCore", "Channel" = "node:name(node:current())"!][!//
  [!ENDNOCODE!][!//
  [!NOCODE!][!//
  [!IF "num:i($CGCoreId_Extract) = num:i(0)"!]
  [!VAR "MappingValue" = "concat('(ICU_CORE0 | ','(uint8)',$MaxChannelsCore0, ')')"!][!//
  [!VAR "MaxChannelsCore0"= "num:i($MaxChannelsCore0 + 1)"!][!//
  [!ELSEIF "num:i($CGCoreId_Extract) = num:i(1)"!]
  [!VAR "MappingValue" = "concat('(ICU_CORE1 | ','(uint8)',$MaxChannelsCore1, ')')"!][!//
  [!VAR "MaxChannelsCore1"= "num:i($MaxChannelsCore1 + 1)"!][!//
  [!ELSEIF "num:i($CGCoreId_Extract) = num:i(2)"!]
  [!VAR "MappingValue" = "concat('(ICU_CORE2 | ','(uint8)',$MaxChannelsCore2, ')')"!][!//
  [!VAR "MaxChannelsCore2"= "num:i($MaxChannelsCore2 + 1)"!][!//
  [!ELSEIF "num:i($CGCoreId_Extract) = num:i(3)"!]
  [!VAR "MappingValue" = "concat('(ICU_CORE3 | ','(uint8)',$MaxChannelsCore3, ')')"!][!//
  [!VAR "MaxChannelsCore3"= "num:i($MaxChannelsCore3 + 1)"!][!//
  [!ELSEIF "num:i($CGCoreId_Extract) = num:i(4)"!]
  [!VAR "MappingValue" = "concat('(ICU_CORE4 | ','(uint8)',$MaxChannelsCore4, ')')"!][!//
  [!VAR "MaxChannelsCore4"= "num:i($MaxChannelsCore4 + 1)"!][!//
  [!ELSEIF "num:i($CGCoreId_Extract) = num:i(5)"!]
  [!VAR "MappingValue" = "concat('(ICU_CORE5 | ','(uint8)',$MaxChannelsCore5, ')')"!][!//
  [!VAR "MaxChannelsCore5"= "num:i($MaxChannelsCore5 + 1)"!][!//
  [!ENDIF!][!//
  [!VAR "nodeval" = "./ERUInputConfiguration/*[1]/EruOguReference"!][!//
  [!IF "contains($nodeval,'UnitConf_0') = 'true'"!][!//
    [!VAR "IcuEruChannelNum0"= "./IcuChannelId"!][!//
    [!VAR "IcuEruChannelNum0"= "concat('((uint16)','(ICU_CORE',num:i($CGCoreId_Extract),' | ','(uint8)',$IcuEruChannelNum0, '))')"!][!//
    [!IF "contains($IcuEruChannelNum4,'ICU_CORE') = 'true' and num:i(substring($IcuEruChannelNum4,19,1)) != num:i($CGCoreId_Extract)"!][!//
      [!ERROR!][!//
        Error: Wrong Configuration. [!"node:name(../../IcuChannel/*[IcuChannelId = num:i(substring-before(substring-after($IcuEruChannelNum4,'(uint8)'),')'))])"!](using OGU channel 4) and [!"$Channel"!](using OGU channel 0) are not allocated to same core.
      [!ENDERROR!][!//
    [!ENDIF!][!//
  [!ELSEIF "contains($nodeval,'UnitConf_1') = 'true'"!][!//
    [!VAR "IcuEruChannelNum1"= "./IcuChannelId"!][!//
    [!VAR "IcuEruChannelNum1"= "./IcuChannelId"!][!//
    [!VAR "IcuEruChannelNum1"= "concat('((uint16)','(ICU_CORE',num:i($CGCoreId_Extract),' | ','(uint8)',$IcuEruChannelNum1, '))')"!][!//
    [!IF "contains($IcuEruChannelNum5,'ICU_CORE') = 'true' and num:i(substring($IcuEruChannelNum5,19,1)) != num:i($CGCoreId_Extract)"!][!//
      [!ERROR!][!//
        Error: Wrong Configuration. [!"node:name(../../IcuChannel/*[IcuChannelId = num:i(substring-before(substring-after($IcuEruChannelNum5,'(uint8)'),')'))])"!](using OGU channel 5) and [!"$Channel"!](using OGU channel 1) are not allocated to same core.
      [!ENDERROR!][!//
    [!ENDIF!][!//
  [!ELSEIF "contains($nodeval,'UnitConf_2') = 'true'"!][!//
    [!VAR "IcuEruChannelNum2"= "./IcuChannelId"!][!//
    [!VAR "IcuEruChannelNum2"= "concat('((uint16)','(ICU_CORE',num:i($CGCoreId_Extract),' | ','(uint8)',$IcuEruChannelNum2, '))')"!][!//
    [!IF "contains($IcuEruChannelNum6,'ICU_CORE') = 'true' and num:i(substring($IcuEruChannelNum6,19,1)) != num:i($CGCoreId_Extract)"!][!//
      [!ERROR!][!//
        Error: Wrong Configuration. [!"node:name(../../IcuChannel/*[IcuChannelId = num:i(substring-before(substring-after($IcuEruChannelNum6,'(uint8)'),')'))])"!](using OGU channel 6) and [!"$Channel"!](using OGU channel 2) are not allocated to same core.
      [!ENDERROR!][!//
    [!ENDIF!][!//
  [!ELSEIF "contains($nodeval,'UnitConf_3') = 'true'"!][!//
    [!VAR "IcuEruChannelNum3"= "./IcuChannelId"!][!//
    [!VAR "IcuEruChannelNum3"= "concat('((uint16)','(ICU_CORE',num:i($CGCoreId_Extract),' | ','(uint8)',$IcuEruChannelNum3, '))')"!][!//
    [!IF "contains($IcuEruChannelNum7,'ICU_CORE') = 'true' and num:i(substring($IcuEruChannelNum7,19,1)) != num:i($CGCoreId_Extract)"!][!//
      [!ERROR!][!//
        Error: Wrong Configuration. [!"node:name(../../IcuChannel/*[IcuChannelId = num:i(substring-before(substring-after($IcuEruChannelNum7,'(uint8)'),')'))])"!](using OGU channel 7) and [!"$Channel"!](using OGU channel 3) are not allocated to same core.
      [!ENDERROR!][!//
    [!ENDIF!][!//
  [!ELSEIF "contains($nodeval,'UnitConf_4') = 'true'"!][!//
    [!VAR "IcuEruChannelNum4"= "./IcuChannelId"!][!//
    [!VAR "IcuEruChannelNum4"= "concat('((uint16)','(ICU_CORE',num:i($CGCoreId_Extract),' | ','(uint8)',$IcuEruChannelNum4, '))')"!][!//
    [!IF "contains($IcuEruChannelNum0,'ICU_CORE') = 'true' and num:i(substring($IcuEruChannelNum0,19,1)) != num:i($CGCoreId_Extract)"!][!//
      [!ERROR!][!//
        Error: Wrong Configuration. [!"node:name(../../IcuChannel/*[IcuChannelId = num:i(substring-before(substring-after($IcuEruChannelNum0,'(uint8)'),')'))])"!](using OGU channel 0) and [!"$Channel"!](using OGU channel 4) are not allocated to same core.
      [!ENDERROR!][!//
    [!ENDIF!][!//
  [!ELSEIF "contains($nodeval,'UnitConf_5') = 'true'"!][!//
    [!VAR "IcuEruChannelNum5"= "./IcuChannelId"!][!//
    [!VAR "IcuEruChannelNum5"= "concat('((uint16)','(ICU_CORE',num:i($CGCoreId_Extract),' | ','(uint8)',$IcuEruChannelNum5, '))')"!][!//
    [!IF "contains($IcuEruChannelNum1,'ICU_CORE') = 'true' and num:i(substring($IcuEruChannelNum1,19,1)) != num:i($CGCoreId_Extract)"!][!//
      [!ERROR!][!//
        Error: Wrong Configuration. [!"node:name(../../IcuChannel/*[IcuChannelId = num:i(substring-before(substring-after($IcuEruChannelNum1,'(uint8)'),')'))])"!](using OGU channel 1) and [!"$Channel"!](using OGU channel 5) are not allocated to same core.
      [!ENDERROR!][!//
    [!ENDIF!][!//
  [!ELSEIF "contains($nodeval,'UnitConf_6') = 'true'"!][!//
    [!VAR "IcuEruChannelNum6"= "./IcuChannelId"!][!//
    [!VAR "IcuEruChannelNum6"= "concat('((uint16)','(ICU_CORE',num:i($CGCoreId_Extract),' | ','(uint8)',$IcuEruChannelNum6, '))')"!][!//
    [!IF "contains($IcuEruChannelNum2,'ICU_CORE') = 'true' and num:i(substring($IcuEruChannelNum2,19,1)) != num:i($CGCoreId_Extract)"!][!//
      [!ERROR!][!//
        Error: Wrong Configuration. [!"node:name(../../IcuChannel/*[IcuChannelId = num:i(substring-before(substring-after($IcuEruChannelNum2,'(uint8)'),')'))])"!](using OGU channel 2) and [!"$Channel"!](using OGU channel 6) are not allocated to same core.
      [!ENDERROR!][!//
    [!ENDIF!][!//
  [!ELSEIF "contains($nodeval,'UnitConf_7') = 'true'"!][!//
    [!VAR "IcuEruChannelNum7"= "./IcuChannelId"!][!//  
    [!VAR "IcuEruChannelNum7"= "concat('((uint16)','(ICU_CORE',num:i($CGCoreId_Extract),' | ','(uint8)',$IcuEruChannelNum7, '))')"!][!//
    [!IF "contains($IcuEruChannelNum3,'ICU_CORE') = 'true' and num:i(substring($IcuEruChannelNum3,19,1)) != num:i($CGCoreId_Extract)"!][!//
      [!ERROR!][!//
        Error: Wrong Configuration. [!"node:name(../../IcuChannel/*[IcuChannelId = num:i(substring-before(substring-after($IcuEruChannelNum3,'(uint8)'),')'))])"!](using OGU channel 3) and [!"$Channel"!](using OGU channel 7) are not allocated to same core.
      [!ENDERROR!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDNOCODE!][!//
    (uint16)[!"$MappingValue"!][!IF "$ChannelId != $MaxChannels"!],[!ENDIF!]
    
[!ENDSELECT!][!//
[!ENDFOR!][!//
  },
#endif
  #if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
  {
    [!"$IcuEruChannelNum0"!],
    [!"$IcuEruChannelNum1"!],
    [!"$IcuEruChannelNum2"!],
    [!"$IcuEruChannelNum3"!],
    [!"$IcuEruChannelNum4"!],
    [!"$IcuEruChannelNum5"!],
    [!"$IcuEruChannelNum6"!],
    [!"$IcuEruChannelNum7"!]
  },
  #endif
  #if (ICU_17_TIMERIP_GPT12_USED == STD_ON)
  [!IF "$GPT1Prescalar = 'NONE'"!]
  ICU_GPT12_BPSX_NONE,
  [!ELSE!][!//
  [!"concat('ICU_GPT12_BPS1_',$GPT1Prescalar)"!],
  [!ENDIF!][!//
  [!IF "$GPT2Prescalar = 'NONE'"!]
  ICU_GPT12_BPSX_NONE
  [!ELSE!][!//
  [!"concat('ICU_GPT12_BPS2_',$GPT2Prescalar)"!]
  [!ENDIF!][!//
  #endif
[!ENDSELECT!][!//

};
/*  [/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
   guideline.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"

[!ENDSELECT!][!//
