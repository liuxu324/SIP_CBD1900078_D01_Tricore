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
**  FILENAME  : Icu_17_TimerIp_Cfg.h                                          **
**                                                                            **
**  VERSION   : 9.0.0                                                         **
**                                                                            **
**  DATE      : 2018-06-19                                                    **
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
**  TRACEABILITY : [cover parentID= {8AC26D8F-A810-4529-9571-EE829383AC63}]   **
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
**  FILENAME  : Icu_17_TimerIp_Cfg.h                                          **
**                                                                            **
**  VERSION   : 9.0.0                                                         **
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
/* [cover parentID={8AC26D8F-A810-4529-9571-EE829383AC63}] */
/*  [/cover] */
#ifndef ICU_17_TIMERIP_CFG_H
#define ICU_17_TIMERIP_CFG_H

[!NOCODE!][!//
[!INCLUDE "Icu_17_TimerIp.m"!][!//
[!ENDNOCODE!][!//

[!SELECT "as:modconf('Icu')[1]"!][!// 

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/*Section to Generate Autosar Specific Version Information*/
[!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
[!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
[!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//

[!IF "$MajorVersion = num:i(4)"!][!//
/* [cover parentID={BC4B5EEA-8EF3-4508-A932-9616FD65E7D0}] */
#define ICU_17_TIMERIP_AR_RELEASE_MAJOR_VERSION  ([!"$MajorVersion"!]U)
/*  [/cover] */
/* [cover parentID={8E4163B8-9E3E-424b-AA07-DDAF5DF3842A}] */
#define ICU_17_TIMERIP_AR_RELEASE_MINOR_VERSION  ([!"$MinorVersion"!]U)
/*  [/cover] */
/* [cover parentID={03A382FC-9EED-46f4-A322-7E270B7DDC83}] */
#define ICU_17_TIMERIP_AR_RELEASE_REVISION_VERSION  ([!"$RevisionVersion"!]U)
/*  [/cover] */
[!ENDIF!][!//

/*Section to Generate Vendor Specific Version Information*/
[!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
[!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
[!VAR "SwRevisionVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
/* Vendor specific implementation version information */
/* [cover parentID={9409C226-D472-4a6c-9D71-76B8F4E17A83}] */
#define ICU_17_TIMERIP_SW_MAJOR_VERSION   ([!"$SwMajorVersion"!]U)
/*  [/cover] */
/* [cover parentID={C3F168AC-A903-41cb-8DBE-4F5E3337CC2E}] */
#define ICU_17_TIMERIP_SW_MINOR_VERSION   ([!"$SwMinorVersion"!]U)
/*  [/cover] */
/* [cover parentID={03F840A4-DB19-4c51-B929-2E434B7E60F9}] */
#define ICU_17_TIMERIP_SW_PATCH_VERSION   ([!"$SwRevisionVersion"!]U)
/*  [/cover] */

/*
    Configuration : ICU_17_TIMERIP_SAFETY_ENABLE
    Pre-processor switch to enable/disable the ICU driver safety features.
*/
/* [cover parentID={87E4ECE5-453F-4a5f-B2AF-3B35AABAE31F}] */
#define ICU_17_TIMERIP_SAFETY_ENABLE [!CALL "ICU_CG_ConfigSwitch", "nodeval" = "IcuGeneral/IcuSafetyEnable"!]
/*  [/cover] */
/*
    Configuration : ICU_17_TIMERIP_INITCHECK_API
    Pre-processor switch to enable/disable the ICU init check API.
*/
/* [cover parentID={554F6FC7-4AC4-4608-8A0C-4C4D7BD75DD6}] */
#define ICU_17_TIMERIP_INITCHECK_API [!CALL "ICU_CG_ConfigSwitch", "nodeval" = "IcuOptionalApis/IcuInitCheckApi"!]
/*  [/cover] */

/* ICU026: General Configuration */
/*
Configuration to decide the mode of execution of Run Time API's
*/
/* [cover parentID={7DFA8562-90CA-4283-A7FB-BD59DCE8D2E3}] */
#define ICU_17_TIMERIP_RUNTIME_API_MODE     [!"text:replace(node:value(IcuGeneral/IcuRuntimeApiMode),'ICU_','ICU_17_TIMERIP_')"!]
/*  [/cover] */
/*
Configuration to decide the mode of execution of Init and DeInit API's
*/
/* [cover parentID={17E85140-0787-4702-9291-06C994114161}] */
#define ICU_17_TIMERIP_INIT_DEINIT_API_MODE  [!"text:replace(node:value(IcuGeneral/IcuInitDeInitApiMode),'ICU_','ICU_17_TIMERIP_')"!]
/*  [/cover] */
/*
Configuration: ICU_17_TIMERIP_DEV_ERROR_DETECT
Adds/removes the Development Error Detection 
from the code 
- if STD_ON, Development error detection is enabled
- if STD_OFF, Development error detection is disabled
*/
/* [cover parentID={7304BC44-03B3-4635-A96A-23F8139C0E62}] */
#define ICU_17_TIMERIP_DEV_ERROR_DETECT           [!CALL "ICU_CG_ConfigSwitch", "nodeval" = "IcuGeneral/IcuDevErrorDetect"!]
/*  [/cover] */
/*
Configuration: ICU_17_TIMERIP_MULTICORE_ERROR_DETECT
Adds/removes the Multi-Core Development Error Detection 
from the code 
- if STD_ON, Multi-Core Development error detection is enabled
- if STD_OFF, Multi-Core Development error detection is disabled
*/
/* [cover parentID={ACA78BB7-4768-4cc5-9CAF-2725B3A07A5D}] */
#define ICU_17_TIMERIP_MULTICORE_ERROR_DETECT           [!CALL "ICU_CG_ConfigSwitch", "nodeval" = "IcuGeneral/IcuMultiCoreErrorDetect"!]
/*  [/cover] */
/*
Configuration: ICU_17_TIMERIP_REPORT_WAKEUP_SOURCE
Preprocessor switch to enable/disable the wakeup source reporting
- if STD_ON, Reports wakeup to higher layer
- if STD_OFF, Reporting is switched off
*/
/* [cover parentID={39695C37-0636-4440-A4B2-370FA4F81E34}] */
#define ICU_17_TIMERIP_REPORT_WAKEUP_SOURCE       [!CALL "ICU_CG_ConfigSwitch", "nodeval" = "IcuGeneral/IcuReportWakeupSource"!]
/*  [/cover] */

/*
Configuration: ICU_17_TIMERIP_DE_INIT_API
Adds/removes Icu_DeInit API 
from the code 
- if STD_ON, Icu_DeInit is enabled
- if STD_OFF, Icu_DeInit is disabled
*/
/* [cover parentID={68B0F57E-E7F2-4876-9289-451A30466201}] */
#define ICU_17_TIMERIP_DE_INIT_API                [!CALL "ICU_CG_ConfigSwitch", "nodeval" = "IcuOptionalApis/IcuDeInitApi"!]
/*  [/cover] */
/*
Configuration: ICU_17_TIMERIP_DISABLE_WAKEUP_API
Adds/removes Icu_DisableWakeup API 
from the code 
- if STD_ON, Icu_DisableWakeup is enabled
- if STD_OFF, Icu_DisableWakeup is disabled
*/
/* [cover parentID={42C01C5E-163D-4446-BA59-52007E702B54}] */
#define ICU_17_TIMERIP_DISABLE_WAKEUP_API         [!CALL "ICU_CG_ConfigSwitch", "nodeval" = "IcuOptionalApis/IcuDisableWakeupApi"!]
/*  [/cover] */
/*
Configuration: ICU_17_TIMERIP_ENABLE_WAKEUP_API
Adds/removes Icu_EnableWakeup API 
from the code 
- if STD_ON, Icu_EnableWakeup is enabled
- if STD_OFF, Icu_EnableWakeup is disabled
*/
/* [cover parentID={D785661D-4F83-4767-AA7A-41EC67515059}] */
#define ICU_17_TIMERIP_ENABLE_WAKEUP_API          [!CALL "ICU_CG_ConfigSwitch", "nodeval" = "IcuOptionalApis/IcuEnableWakeupApi"!]
/*  [/cover] */
/*
Configuration: ICU_17_TIMERIP_EDGE_COUNT_API
Adds/removes Edge Count Measurement APIs 
from the code 
- if STD_ON, Icu_EnableEdgeCount, Icu_DisableEdgeCount
         Icu_ResetEdgeCount, Icu_GetEdgeNumbers is enabled
- if STD_OFF, Icu_EnableEdgeCount, Icu_DisableEdgeCount
         Icu_ResetEdgeCount, Icu_GetEdgeNumbers is disabled
*/
/* [cover parentID={71FAFB09-39CB-47aa-8095-6E6237030B32}] */
#define ICU_17_TIMERIP_EDGE_COUNT_API             [!CALL "ICU_CG_ConfigSwitch", "nodeval" = "IcuOptionalApis/IcuEdgeCountApi"!]
/*  [/cover] */
/*
Configuration: ICU_17_TIMERIP_GET_DUTY_CYCLE_VALUES_API
Adds/removes Icu_GetDutyCycleValues API 
from the code 
- if STD_ON, Icu_GetDutyCycleValues is enabled
- if STD_OFF, Icu_GetDutyCycleValues is disabled
*/
/* [cover parentID={325B0634-D9A5-4169-863E-D83ABDF7826A}] */
#define ICU_17_TIMERIP_GET_DUTY_CYCLE_VALUES_API  [!CALL "ICU_CG_ConfigSwitch", "nodeval" = "IcuOptionalApis/IcuGetDutyCycleValuesApi"!]
/*  [/cover] */
/*
Configuration: ICU_17_TIMERIP_GET_INPUT_STATE_API
Adds/removes Icu_GetInputState API 
from the code 
- if STD_ON, Icu_GetInputState is enabled
- if STD_OFF, Icu_GetInputState is disabled
*/
/* [cover parentID={FF37A879-D575-4f41-9B26-E1EE9F89DEC4}] */
#define ICU_17_TIMERIP_GET_INPUT_STATE_API        [!CALL "ICU_CG_ConfigSwitch", "nodeval" = "IcuOptionalApis/IcuGetInputStateApi"!]
/*  [/cover] */
/*
Configuration: ICU_17_TIMERIP_GET_TIME_ELAPSED_API
Adds/removes Icu_GetTimeElapsed API 
from the code 
- if STD_ON, Icu_GetTimeElapsed is enabled
- if STD_OFF, Icu_GetTimeElapsed is disabled
*/
/* [cover parentID={AE1E2451-EFFC-42a0-A65F-C5B3B4E8EC33}] */
#define ICU_17_TIMERIP_GET_TIME_ELAPSED_API       [!CALL "ICU_CG_ConfigSwitch", "nodeval" = "IcuOptionalApis/IcuGetTimeElapsedApi"!]
/*  [/cover] */
/*
Configuration: ICU_17_TIMERIP_GET_VERSION_INFO_API
Adds/removes Icu_GetVersionInfo API 
from the code 
- if STD_ON, Icu_GetVersionInfo is enabled
- if STD_OFF, Icu_GetVersionInfo is disabled
*/
/* [cover parentID={FB2C1251-9A49-4829-8DA1-2F927A1F49B6}] */
#define ICU_17_TIMERIP_GET_VERSION_INFO_API       [!CALL "ICU_CG_ConfigSwitch", "nodeval" = "IcuOptionalApis/IcuGetVersionInfoApi"!]
/*  [/cover] */
/*
Configuration: ICU_17_TIMERIP_SET_MODE_API
Adds/removes Icu_SetMode API 
from the code 
- if STD_ON, Icu_SetMode is enabled
- if STD_OFF, Icu_SetMode is disabled
*/
/* [cover parentID={E02C3468-6A06-49d8-99B4-3A50907586A3}] */
#define ICU_17_TIMERIP_SET_MODE_API               [!CALL "ICU_CG_ConfigSwitch", "nodeval" = "IcuOptionalApis/IcuSetModeApi"!]
/*  [/cover] */
/*
Configuration: ICU_17_TIMERIP_TIMESTAMP_API
Adds/removes Time Stamp APIs 
from the code 
- if STD_ON, Icu_StartTimestamp, Icu_StopTimestamp
         Icu_GetTimestampIndex is enabled
- if STD_OFF, Icu_StartTimestamp, Icu_StopTimestamp
         Icu_GetTimestampIndex is disabled
*/
/* [cover parentID={F4888B17-56BA-4ec7-ADCD-34C5EF6EA3C1}] */
#define ICU_17_TIMERIP_TIMESTAMP_API              [!CALL "ICU_CG_ConfigSwitch", "nodeval" = "IcuOptionalApis/IcuTimestampApi"!]
/*  [/cover] */

/*
Configuration: ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API
Adds/removes Signal Measurement APIs 
from the code 
- if STD_ON, Icu_StartSignalMeasurement, Icu_StopSignalMeasurement
         are enabled
- if STD_OFF, Icu_StartSignalMeasurement, Icu_StopSignalMeasurement
         are disabled
*/
/* [cover parentID={31B250F1-0A62-44f8-BE46-6C3C96ABB17C}] */
#define ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API              [!CALL "ICU_CG_ConfigSwitch", "nodeval" = "IcuOptionalApis/IcuSignalMeasurementApi"!]
/*  [/cover] */

/*
Configuration: ICU_17_TIMERIP_EDGE_DETECT_API
Adds/removes Edge Detect APIs 
from the code 
- if STD_ON, Edge Detection functionality is enabled
- if STD_OFF, Edge Detection functionality is disabled
*/
/* [cover parentID={8E6986B5-F526-441e-B934-5BE5B8795BBF}] */
#define ICU_17_TIMERIP_EDGE_DETECT_API                     [!CALL "ICU_CG_ConfigSwitch", "nodeval" = "IcuOptionalApis/IcuEdgeDetectApi"!]
/*  [/cover] */

/*
Configuration: ICU_17_TIMERIP_WAKEUP_FUNCTIONALITY_API
Adds/removes the service Icu_CheckWakeup() 
from the code 
- if ON, the service Icu_CheckWakeup() is enabled
- if OFF, the service Icu_CheckWakeup() is disabled
*/
/* [cover parentID={CFE5D177-287D-4ef8-9862-8BD06770817C}] */
#define ICU_17_TIMERIP_WAKEUP_FUNCTIONALITY_API        [!CALL "ICU_CG_ConfigSwitch", "nodeval" = "IcuOptionalApis/IcuWakeupFunctionalityApi"!] 
/*  [/cover] */

/*
Configuration: ICU_17_TIMERIP_INSTANCE_ID
InstanceId of ICU module
*/
/* InstanceId of ICU module  */
/* [cover parentID={3864605E-440C-4549-98D0-C416DC1F9DE8}] */
#define ICU_17_TIMERIP_INSTANCE_ID       ((uint8)[!"num:i(node:value(IcuGeneral/IcuIndex))"!])
/*  [/cover] */

[!SELECT "as:modconf('Icu')[1]"!][!//
[!NOCODE!]
[!CALL "ICU_CG_GenerateModuleMap"!][!//
[!ENDNOCODE!]
[!VAR "SingelCore"= "num:i(0)"!][!//
[!VAR "SingelCoreID"= "num:i(0)"!][!//
[!VAR "MaxChannels"= "num:i(count(./IcuConfigSet/IcuChannel/*))"!][!//
[!VAR "GtmChUsed"= "num:i(0)"!][!//
[!VAR "Ccu6ChUsed"= "num:i(0)"!][!//
[!VAR "Gpt12ChUsed"= "num:i(0)"!][!//
[!VAR "EruChUsed"= "num:i(0)"!][!//
[!FOR "CoreId" = "num:i(1)" TO "num:i(6)"!][!//
[!NOCODE!]
[!VAR "GtmCh"= "num:i(0)"!][!//
[!VAR "Ccu6Ch"= "num:i(0)"!][!//
[!VAR "Gpt12Ch"= "num:i(0)"!][!//
[!VAR "EruCh"= "num:i(0)"!][!//
[!ENDNOCODE!][!//
/*
  Core [!"num:i($CoreId - 1)"!] Configurations    
*/
[!FOR "ChannelId" = "num:i(1)" TO "num:i($MaxChannels)"!][!//
[!SELECT "./IcuConfigSet/IcuChannel/*[IcuChannelId = num:i($ChannelId) - num:i(1)]"!][!//
[!NOCODE!]
[!CALL "ICU_CG_GetCore", "Channel" = "node:name(node:current())"!][!//
[!ENDNOCODE!][!//
[!IF "(num:i($CGCoreId_Extract)) = (num:i($CoreId) - num:i(1))"!]
  [!NOCODE!]
   [!IF "./IcuAssignedHwUnit = 'GTM'"!][!//
      [!VAR "GtmCh" = "num:i($GtmCh + 1)"!][!//
    [!ELSEIF "./IcuAssignedHwUnit = 'CCU6'"!][!//
      [!VAR "Ccu6Ch" = "num:i($Ccu6Ch + 1)"!][!//
    [!ELSEIF "./IcuAssignedHwUnit = 'ERU'"!][!//
      [!VAR "EruCh" = "num:i($EruCh + 1)"!][!//
    [!ELSEIF "./IcuAssignedHwUnit = 'GPT12'"!][!//
      [!VAR "Gpt12Ch" = "num:i($Gpt12Ch + 1)"!][!//
    [!ENDIF!][!//
[!ENDNOCODE!][!//
/* [cover parentID={BC525132-BDA7-4065-A7E7-056A9779C95C}] */
/*MISRA2012_RULE_5_1_JUSTIFICATION:
MISRA2012_RULE_5_2_JUSTIFICATION:
MISRA2012_RULE_5_4_JUSTIFICATION:
MISRA2012_RULE_5_5_JUSTIFICATION: decomposition of name is not possible,
Further distinct name can not be given*/
#ifndef IcuConf_IcuChannel_[!"node:name(.)"!]
/*MISRA2012_RULE_5_1_JUSTIFICATION:
MISRA2012_RULE_5_2_JUSTIFICATION:
MISRA2012_RULE_5_4_JUSTIFICATION:
MISRA2012_RULE_5_5_JUSTIFICATION: decomposition of name is not possible,
Further distinct name can not be given*/
#define IcuConf_IcuChannel_[!"node:name(.)"!]       ((Icu_17_TimerIp_ChannelType)[!"./IcuChannelId"!]U)
#endif
/*  [/cover] */
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDFOR!][!//channel
/* Core [!"num:i($CoreId - 1)"!] Configurations summary */
/* [cover parentID={87737856-2F5B-4e98-9266-A5B86EE6176A}] */
/*MISRA2012_RULE_5_1_JUSTIFICATION:
MISRA2012_RULE_5_2_JUSTIFICATION:
MISRA2012_RULE_5_4_JUSTIFICATION:
MISRA2012_RULE_5_5_JUSTIFICATION: decomposition of name is not possible,
Further distinct name can not be given*/
#define ICU_17_TIMERIP_MAX_CHANNELS_CORE[!"num:i($CoreId - 1)"!]                   ([!"num:i($GtmCh + $Ccu6Ch + $Gpt12Ch + $EruCh)"!]U)
/*  [/cover] */
/* [cover parentID={5A803795-0344-4bef-ACBC-D7B3F18CAB5E}] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE[!"num:i($CoreId - 1)"!]         ([!"num:i($GtmCh + $Ccu6Ch + $Gpt12Ch)"!]U)
/*  [/cover] */
[!VAR "Corexchannels"= "num:i($GtmCh + $Ccu6Ch + $Gpt12Ch + $EruCh)"!][!//
[!IF "$Corexchannels = $MaxChannels"!]
[!VAR "SingelCore"= "num:i(1)"!][!//
[!VAR "SingelCoreID"= "num:i($CoreId - 1)"!][!//
[!ENDIF!]
[!VAR "GtmChUsed"= "num:i($GtmCh+$GtmChUsed)"!][!//
[!VAR "Ccu6ChUsed"= "num:i($Ccu6ChUsed+$Ccu6Ch)"!][!//
[!VAR "Gpt12ChUsed"= "num:i($Gpt12ChUsed+$Gpt12Ch)"!][!//
[!VAR "EruChUsed"= "num:i($EruChUsed+$EruCh)"!][!//
[!ENDFOR!][!//Core
[!ENDSELECT!][!//

/***************************************************************************
TOTAL NUMBER OF CONFIGURED CHANNELS 
****************************************************************************/
/* [cover parentID={E99EED83-B152-44d0-9481-A45254ACBE20}] */
#define ICU_17_TIMERIP_MAX_CHANNELS         ([!"num:i($GtmChUsed+$Ccu6ChUsed+$Gpt12ChUsed+$EruChUsed)"!]U)
/*  [/cover] */
/* Macro to idntify single core execution */
#define  ICU_17_TIMERIP_SINGLE_CORE    [!CALL "ICU_CG_ConfigSwitchInt", "nodeval" = "num:i($SingelCore)"!]
#define  ICU_17_TIMERIP_SINGLE_CORE_ID [!"num:i($SingelCoreID)"!]

[!ENDSELECT!][!//
/*
Derived parameters
Vendor specific configuration switches
Format : ICU_<HW>_<MODE>_USED  (Vendor Specific)
HW : TIM, CCU6, ERU, GPT12
STD_ON: <HW> is used for <MODE>.
STD_OFF: <HW> is not used for <MODE>.
*/
/* GTM TIM hardware resource usage */
/* [cover parentID={F5D8F328-055E-436c-9FEA-4B758D081BDE}] */
#define ICU_17_TIMERIP_GTM_TIM_USED         [!CALL "ICU_CG_ConfigSwitchInt", "nodeval" = "num:i($GtmChUsed)"!]
/*  [/cover] */
/* CCU6 hardware resource usage */
/* [cover parentID={BC11C91E-2E8A-44e7-88DA-9C743C30D069}] */
#define ICU_17_TIMERIP_CCU6_USED             [!CALL "ICU_CG_ConfigSwitchInt", "nodeval" = "num:i($Ccu6ChUsed)"!]
/*  [/cover] */
[!NOCODE!]
[!SELECT "as:modconf('Mcu')[1]"!][!//
[!VAR "CCU6Kernel0Allocation" = "'CCU6_MODULE_USED_BY_ICU_DRIVER' = ./McuHardwareResourceAllocationConf/McuHardwareResourceAllocationConf_0/McuCcu6ModuleAllocationConf/McuCcu6ModuleAllocationConf_0/McuCcu6ModuleAllocationConf"!][!//
[!VAR "CCU6Kernel1Allocation" = "'CCU6_MODULE_USED_BY_ICU_DRIVER' = ./McuHardwareResourceAllocationConf/McuHardwareResourceAllocationConf_0/McuCcu6ModuleAllocationConf/McuCcu6ModuleAllocationConf_1/McuCcu6ModuleAllocationConf"!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!]
/* [cover parentID={5FC97717-0B33-43d5-A413-35E2F09F906E}] */
/* CCU6 Kerenl-0 allocation to ICU */
#define ICU_17_TIMERIP_CCU6_KERNEL0_USED    [!CALL "ICU_CG_ConfigSwitch", "nodeval" = "$CCU6Kernel0Allocation"!]
/*  [/cover] */
/* [cover parentID={D83A549C-AF16-4368-9E74-ADE3CBAC1ED5}] */
/* CCU6 Kerenl-1 allocation to ICU */
#define ICU_17_TIMERIP_CCU6_KERNEL1_USED    [!CALL "ICU_CG_ConfigSwitch", "nodeval" = "$CCU6Kernel1Allocation"!]
/*  [/cover] */

/* GPT12 hardware resource usage */
/* [cover parentID={61B3DFBB-A8F7-40f5-B00D-4DB9F37C7289}] */
#define ICU_17_TIMERIP_GPT12_USED           [!CALL "ICU_CG_ConfigSwitchInt", "nodeval" = "num:i($Gpt12ChUsed)"!]
/*  [/cover] */
/* ERU hardware resource usage */
/* [cover parentID={838D586C-6157-4ad3-86B2-D89029110992}] */
#define ICU_17_TIMERIP_ERU_SIGEDGE_USED     [!CALL "ICU_CG_ConfigSwitchInt", "nodeval" = "num:i($EruChUsed)"!]
/*  [/cover] */

#endif  /* ICU_17_TIMERIP_CFG_H */


