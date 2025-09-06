[!NOCODE!]
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
**  FILENAME  : Gpt_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE      : 2018-04-09                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Gpt.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={CCDFE54F-3034-432b-A84C-E6942751DF0A} ]   **
**                                                                            **
**  DESCRIPTION  : Code template header file for Gpt Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Gpt Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!]
[!ENDNOCODE!][!//
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
**  FILENAME  : Gpt_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 4.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                                      **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                                          **
**                                                                            **
**  BSW MODULE DECRIPTION : Gpt.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : GPT configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of GPT Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
[!CR!][!//
#ifndef  GPT_CFG_H
#define  GPT_CFG_H
[!CR!][!//
[!NOCODE!][!//
[!INCLUDE "Gpt.m"!][!//
[!ENDNOCODE!][!//
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
[!CR!][!CR!][!//
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
[!CR!][!//
/* Section to Generate Autosar Specific Version Information */
[!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
[!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
[!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
[!IF "$MajorVersion = num:i(4)"!][!CR!][!//
#define GPT_AR_RELEASE_MAJOR_VERSION                      ([!"$MajorVersion"!]U)
#define GPT_AR_RELEASE_MINOR_VERSION                      ([!"$MinorVersion"!]U)
#define GPT_AR_RELEASE_REVISION_VERSION                   ([!"$RevisionVersion"!]U)
[!ENDIF!][!//
[!CR!][!//
/* Section to Generate Vendor Specific Version Information */
[!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
[!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
[!VAR "SwRevisionVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
/* Vendor specific implementation version information */
#define GPT_SW_MAJOR_VERSION                              ([!"$SwMajorVersion"!]U)
#define GPT_SW_MINOR_VERSION                              ([!"$SwMinorVersion"!]U)
#define GPT_SW_PATCH_VERSION                              ([!"$SwRevisionVersion"!]U)

[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Gpt')[1]"!][!//
[!/* Select GptDriverConfiguration as context-node */!][!//
/*
Container : GptDriverConfiguration
This container contains the channel-wide configuration (parameters) of
the GPT Driver.
*/
[!SELECT "GptDriverConfiguration"!][!//
[!CR!][!//
/*
Configuration: GPT_SAFETY_ENABLE
Preprocessor switch to enable/disable the safety check and reporting.
- if STD_ON, Enable safety check
- if STD_OFF, Disable safety check
*/
[!/* [cover parentID={3C3B8BE4-B4B7-4dc0-85AC-BD1385991849}] */!][!//
#define GPT_SAFETY_ENABLE                                 [!//
[!CALL "GPT_CG_ConfigSwitch", "nodeval" = "GptSafetyEnable"!][!//
[!/*  [/cover] */!][!//
[!CR!][!//
/*
Configuration: GPT_INITCHECK_API
Adds/removes the service Gpt_InitCheck() from the code
- if STD_ON, Gpt_InitCheck() can be used
- if STD_OFF, Gpt_InitCheck() can not be used
*/
[!/* [cover parentID={8285B7E6-36F5-4040-8CB7-D1BB67C67F78}] */!][!//
#define GPT_INITCHECK_API                                 [!//
[!IF "node:exists(GptInitCheckApi)"!]
  [!CALL "GPT_CG_ConfigSwitch", "nodeval" = "GptInitCheckApi"!][!//
[!ELSE!][!//
   [!INDENT "0"!]
  (STD_OFF)
  [!ENDINDENT!]
[!ENDIF!][!//
[!/*  [/cover] */!][!//
[!CR!][!//
/*
Configuration: GPT_MULTICORE_ERROR_DETECT
Preprocessor switch to enable/disable the
multicore development error detection and reporting.
- if STD_ON, Enable multicore development error detection
- if STD_OFF, Disable multicore development error detection
*/
[!/* [cover parentID={EF80663E-1ED8-4e1d-B61E-3D7E93503DF2}] */!][!//

#define GPT_MULTICORE_ERROR_DETECT                                  [!//
[!CALL "GPT_CG_ConfigSwitch", "nodeval" = "GptMultiCoreErrorDetect"!][!//
[!/*  [/cover] */!][!//
[!CR!][!//
/*
Configuration: GPT_DEV_ERROR_DETECT
Preprocessor switch to enable/disable the development error detection and
reporting.
- if STD_ON, Enable development error detection
- if STD_OFF, Disable development error detection
*/
[!/* [cover parentID={0EE4C03A-84D0-4e00-B24F-F46F0D35EB62}] */!][!//
#define GPT_DEV_ERROR_DETECT                              [!//
[!CALL "GPT_CG_ConfigSwitch", "nodeval" = "GptDevErrorDetect"!][!//
[!/*  [/cover] */!][!//
[!CR!][!//
/*
Configuration: GPT_REPORT_WAKEUP_SOURCE
Preprocessor switch to enable/disable the wakeup source reporting
- if STD_ON, Report wakeup source
- if STD_OFF, Dont report wakeup source
*/
[!/* [cover parentID={299B4A94-1B05-4342-9F50-56AAA5DD61E1}] */!][!//
#define GPT_REPORT_WAKEUP_SOURCE                          [!//
[!CALL "GPT_CG_ConfigSwitch", "nodeval" = "GptReportWakeupSource"!][!//
[!/*  [/cover] */!][!//
[!CR!][!//
/*
Configuration: GPT_PREDEF_TIMER_100US_32BIT_EN
Preprocessor switch to enable/disable the GPT Predef Timer 100us 32bit.
- if STD_ON, Enable 100us 32bit predef timer
- if STD_OFF, Disable 100us 32bit predef timer
*/
[!VAR "GptPredefTimer100us" = "GptPredefTimer100us32bitEnable"!][!//
[!/* [cover parentID={4C2E4D94-B664-429f-AD16-F24BCA4E1D20}] */!][!//
#define GPT_PREDEF_TIMER_100US_32BIT_EN                   [!//
[!CALL "GPT_CG_ConfigSwitch", "nodeval" = "$GptPredefTimer100us"!][!//
[!/*  [/cover] */!][!//
[!CR!][!//
/*
Configuration: GPT_PREDEF_TIMER_1US_xBIT_EN
Specifies the grade of enabling the GPT Predef Timers with 1µs tick duration.
- if STD_ON, Enable 1us xBit predef timer
- if STD_OFF, Disable 1us xBit predef timer
*/
[!/* [cover parentID={7164BE38-13C1-4fda-8FA2-175489A30F53}]
[/cover] */!][!//
[!VAR "GptPredefTimer1us" = "GptPredefTimer1usEnablingGrade"!][!//
[!IF "$GptPredefTimer1us = 'GPT_PREDEF_TIMER_1US_DISABLED'"!][!//
#define GPT_PREDEF_TIMER_1US_16BIT_EN                     (STD_OFF)
#define GPT_PREDEF_TIMER_1US_24BIT_EN                     (STD_OFF)
#define GPT_PREDEF_TIMER_1US_32BIT_EN                     (STD_OFF)
[!//
[!ELSEIF "$GptPredefTimer1us = 'GPT_PREDEF_TIMER_1US_16BIT_ENABLED'"!][!//
#define GPT_PREDEF_TIMER_1US_16BIT_EN                     (STD_ON)
#define GPT_PREDEF_TIMER_1US_24BIT_EN                     (STD_OFF)
#define GPT_PREDEF_TIMER_1US_32BIT_EN                     (STD_OFF)
[!//
[!ELSEIF "$GptPredefTimer1us = 'GPT_PREDEF_TIMER_1US_16_24BIT_ENABLED'"!][!//
#define GPT_PREDEF_TIMER_1US_16BIT_EN                     (STD_ON)
#define GPT_PREDEF_TIMER_1US_24BIT_EN                     (STD_ON)
#define GPT_PREDEF_TIMER_1US_32BIT_EN                     (STD_OFF)
[!//
[!ELSEIF "$GptPredefTimer1us = 'GPT_PREDEF_TIMER_1US_16_24_32BIT_ENABLED'"!][!//
#define GPT_PREDEF_TIMER_1US_16BIT_EN                     (STD_ON)
#define GPT_PREDEF_TIMER_1US_24BIT_EN                     (STD_ON)
#define GPT_PREDEF_TIMER_1US_32BIT_EN                     (STD_ON)
[!ENDIF!][!//
[!NOCODE!][!//
[!IF "contains($GptPredefTimer1us, 'ENABLED')"!][!//
  [!VAR "GptPredefTimer1usStat" = "'true'"!][!//
[!ELSE!][!//
  [!VAR "GptPredefTimer1usStat" = "'false'"!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDSELECT!][!// ENDSLECT of Gpt Driver Configuration
[!CR!][!//
/*
Configuration: GPT_PREDEF_EXTRA_CH_1US and GPT_PREDEF_EXTRA_CH_100US
Preprocessor switch to enable/disable the extra channel to use with predefined
timer.
- if STD_ON, extra channel required
- if STD_OFF, no extra channel required
*/
[!NOCODE!][!//
[!SELECT "GptChannelConfigSet"!][!//
  [!VAR "ChannelMax" = "num:i(count(GptChannelConfiguration/*))"!][!//
[!ENDSELECT!][!//
[!SELECT "as:modconf('Gpt')[1]/GptChannelConfigSet/GptChannelConfiguration"!][!//
 [!VAR "PredefTimerChannels" = "num:i(0)"!][!//
 [!VAR "ExtraPredefCh1Us" = "num:i(0)"!][!//
 [!VAR "ExtraPredefCh100Us" = "num:i(0)"!][!//
 [!IF "($GptPredefTimer1usStat = 'true') or ($GptPredefTimer100us = 'true')"!][!//
   [!FOR "ChannelId" = "num:i(1)" TO "num:i($ChannelMax)"!][!//
    [!SELECT "./*[GptChannelId = num:i($ChannelId) - num:i(1)]"!][!//
    [!VAR "GptPredefTimerType" = "node:value(GptTimerChannelUsage)"!]
    [!IF "contains(node:value(GptTimerChannelUsage),'_1US_')"!][!//
      [!VAR "PredefTimerChannels" = "num:i(num:i($PredefTimerChannels)+num:i(1))"!][!//
      [!SELECT "./GtmTimerOutputModuleConfiguration/*[1]"!][!//
      [!CALL "GPT_CG_GetGTMChannelParam","GtmTimerString" = "GtmTimerUsed"!][!//
      [!ENDSELECT!][!//
      [!VAR "GptPredefTimerUs" = "num:i(1)"!][!//
      [!SELECT "as:modconf('Gpt')[1]/GptDriverConfiguration/GptClockReferencePoint/*[1]"!][!//
      [!VAR "ClockRef" = "GptClockReference"!][!//
      [!ENDSELECT!][!//
      [!/* Call GPT_CG_GetGptPredefFreq to check if the predef enabled channel require an extra channel for its frequency tuning*/!]
      [!CALL "GPT_CG_GetGptPredefFreq","GtmClockRef" = "$ClockRef", "TimerModNo" = "$GtmTimerModNo", "TickDurationUs" = "num:i($GptPredefTimerUs)", "OpnMode" = "num:i(1)"!][!//
      [!IF "num:i($Extra_Channel) = num:i(1)"!][!// Need extra chanel for frequency tuning
        [!VAR "ExtraPredefCh1Us" = "num:i(1)"!][!// Predef timer needs an extra channel for frequency tuning
      [!ENDIF!]
    [!ELSEIF "contains(node:value(GptTimerChannelUsage),'_100US_')"!][!//
      [!VAR "PredefTimerChannels" = "num:i(num:i($PredefTimerChannels)+num:i(1))"!][!//
      [!SELECT "./GtmTimerOutputModuleConfiguration/*[1]"!][!//
      [!CALL "GPT_CG_GetGTMChannelParam","GtmTimerString" = "GtmTimerUsed"!][!//
      [!ENDSELECT!][!//
      [!VAR "GptPredefTimerUs" = "num:i(100)"!][!//
      [!SELECT "as:modconf('Gpt')[1]/GptDriverConfiguration/GptClockReferencePoint/*[1]"!][!//
      [!VAR "ClockRef" = "GptClockReference"!][!//
      [!ENDSELECT!][!//
      [!// Call GPT_CG_GetGptPredefFreq to check if the  predef enabled channel require an extra channel for its frequency tuning
      [!CALL "GPT_CG_GetGptPredefFreq","GtmClockRef" = "$ClockRef", "TimerModNo" = "$GtmTimerModNo", "TickDurationUs" = "num:i($GptPredefTimerUs)", "OpnMode" = "num:i(1)"!][!//
      [!IF "num:i($Extra_Channel) = num:i(1)"!][!// Need extra chanel for frequency tuning
        [!VAR "ExtraPredefCh100Us" = "num:i(1)"!][!// Predef timer needs an extra channel for frequency tuning
      [!ENDIF!]
    [!ENDIF!][!//
    [!ENDSELECT!][!//
   [!ENDFOR!][!//
 [!ENDIF!][!//
[!CODE!][!//
[!CR!][!//
/*
This macro determines whether the GPT driver needs an extra channel for
1us predefined timer implementation that can be used for frequency tuning.
*/
[!/* [cover parentID={BFE0FFAF-51DC-4548-B08F-9DCDF936FDF5}] */!][!//
#define GPT_PREDEF_EXTRA_CH_1US                           ([!//
[!IF "num:i($ExtraPredefCh1Us) = num:i(1)"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)
[!/*  [/cover] */!][!//
[!CR!][!//
/*
This macro determines whether the GPT driver needs an extra channel for
100us predefined timer implementation, that can be used for frequency tuning.
*/
[!/* [cover parentID={A67B2C62-669D-4def-89EF-6D1A536E3038}] */!][!//
#define GPT_PREDEF_EXTRA_CH_100US                         ([!//
[!IF "num:i($ExtraPredefCh100Us) = num:i(1)"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)
[!/*  [/cover] */!][!//
[!ENDCODE!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!][!//
[!ENDSELECT!][!//
[!CR!][!//
[!/* Select GptConfigurationOfOptApiServices as context-node*/!][!//
/*
Container : Configuration of optional API services
This container contains all configuration switches for configuring
optional API services of the GPT driver.
*/
[!SELECT "as:modconf('Gpt')[1]/GptConfigurationOfOptApiServices"!][!//
[!CR!][!//
/*
Configuration: GPT_DEINIT_API
Adds/removes the service Gpt_DeInit() from the code
- if STD_ON, Gpt_DeInit() can be used
- if STD_OFF, Gpt_DeInit() can not be used
*/
[!/* [cover parentID={42FC815E-32E2-4a9e-805C-D064D0E1E81E}] */!][!//
#define GPT_DEINIT_API                                    [!//
[!CALL "GPT_CG_ConfigSwitch", "nodeval" = "GptDeinitApi"!][!//
[!/*  [/cover] */!][!//
[!CR!][!//
/*
Configuration: GPT_TIME_ELAPSED_API
Adds/removes the service Gpt_GetTimeElapsed() from the code
- if STD_ON, Gpt_GetTimeElapsed() can be used
- if STD_OFF, Gpt_GetTimeElapsed() can not be used
*/
[!/* [cover parentID={C4B27141-E460-4d1e-BA67-EDF30E523CFF}] */!][!//
#define GPT_TIME_ELAPSED_API                              [!//
[!CALL "GPT_CG_ConfigSwitch", "nodeval" = "GptTimeElapsedApi"!][!//
[!/*  [/cover] */!][!//
[!CR!][!//
/*
Configuration: GPT_VERSION_INFO_API
Adds/removes the service Gpt_GetVersionInfo() from the code
- if STD_ON, Gpt_GetVersionInfo() can be used
- if STD_OFF, Gpt_GetVersionInfo() can not be used
*/
[!/* [cover parentID={CF143F6C-DFD6-4542-9EC9-AB70D7643E5C}] */!][!//
#define GPT_VERSION_INFO_API                              [!//
[!CALL "GPT_CG_ConfigSwitch", "nodeval" = "GptVersionInfoApi"!][!//
[!/*  [/cover] */!][!//
[!CR!][!//
/*
Configuration: GPT_ENABLE_DISABLE_NOTIFICATION_API
Adds/removes the service Gpt_EnableNotification() and Gpt_DisableNotification
from the code
- if STD_ON, Gpt_EnableNotification() and Gpt_DisableNotification  can be used
- if STD_OFF, Gpt_EnableNotification() and Gpt_DisableNotification  can not be
  used
*/
[!/* [cover parentID={C5242219-C9DE-45e2-9639-5D2B02B28CEC}] */!][!//
#define GPT_ENABLE_DISABLE_NOTIFICATION_API               [!//
[!CALL "GPT_CG_ConfigSwitch", "nodeval" = "GptEnableDisableNotificationApi"!][!//
[!/*  [/cover] */!][!//
[!CR!][!//
/*
Configuration: GPT_TIME_REMAINING_API
Adds/removes the service Gpt_GetTimeRemaining() from the code
- if STD_ON, Gpt_GetTimeRemaining() can be used
- if STD_OFF, Gpt_GetTimeRemaining() can not be used
*/
[!/* [cover parentID={53FBB67D-C11B-4e1e-9FB0-C023B91EEE96}] */!][!//
#define GPT_TIME_REMAINING_API                            [!//
[!CALL "GPT_CG_ConfigSwitch", "nodeval" = "GptTimeRemainingApi"!][!//
[!/*  [/cover] */!][!//
[!CR!][!//
/*
Configuration: GPT_WAKEUP_FUNCTIONALITY_API
Adds/removes the service Gpt_SetMode(), Gpt_EnableWakeup(),
Gpt_DisableWakeup() and Gpt_CheckWakeup() from the code
- if STD_ON, Gpt_SetMode(), Gpt_EnableWakeup(), Gpt_DisableWakeup() and
  Gpt_CheckWakeup() can be used
- if STD_OFF, Gpt_SetMode(), Gpt_EnableWakeup(), Gpt_DisableWakeup() and
  Gpt_CheckWakeup() can not be used
*/
[!/* [cover parentID={0D9FA647-1227-494c-A320-5F008577BC2F}] */!][!//
#define GPT_WAKEUP_FUNCTIONALITY_API                      [!//
[!CALL "GPT_CG_ConfigSwitch", "nodeval" = "GptWakeupFunctionalityApi"!][!//
[!/*  [/cover] */!][!//
[!CR!][!//
[!ENDSELECT!][!//
/*
Configuration: GPT_ONESHOT_USED
The configuration contains oneshot mode channels
*/
[!NOCODE!]
[!VAR "OsmUsed" = "num:i(0)"!][!//
[!SELECT "as:modconf('Gpt')[1]/GptChannelConfigSet/GptChannelConfiguration"!][!//
[!LOOP "./*"!][!//
[!VAR "Mode" = "GptChannelMode"!][!//
[!IF "$Mode = 'GPT_CH_MODE_ONESHOT'"!][!//
[!VAR "OsmUsed" = "num:i(1)"!][!//
[!BREAK!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!IF "$OsmUsed = num:i(1)"!][!//
[!BREAK!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!][!//
[!/* [cover parentID={A8736581-BFB5-46f1-846A-C6413D1BFD38}] */!][!//
[!IF "$OsmUsed = num:i(1)"!][!//
#define GPT_ONESHOT_USED                                  (STD_ON)
[!ELSE!][!//
#define GPT_ONESHOT_USED                                  (STD_OFF)
[!ENDIF!][!//
[!/*  [/cover] */!][!//
[!CR!]
/*******************************************************************************
**                                Gpt Driver Usage                            **
*******************************************************************************/
[!NOCODE!][!//
[!/* Collect core-channel mappings from Resource Manager. */!]
[!CALL "GPT_CG_GenerateModuleMap", "Module"="'GPT'"!][!//
[!SELECT "as:modconf('Gpt')[1]/GptChannelConfigSet/GptChannelConfiguration/*"!]
  [!/* Append the missing resources to master core */!]
  [!CALL "GPT_CG_ValidateChAllocation", "Item" = "node:name(node:current())"!][!//
  [!IF "$CGResult = 'FALSE'"!]
    [!VAR "CGModuleMap" = "concat($CGModuleMap, 'CORE', $CGMasterCoreId, '_', node:name(node:current()), '#,')"!][!//
    [!VAR "pattern" = "concat('CORE', $CGMasterCoreId)"!]
    [!IF "not(contains(text:split($CGCoreUsed),$pattern))"!]
      [!VAR "CGCoreUsed" = "concat($CGCoreUsed, $pattern, ',')"!][!//
    [!ENDIF!]
  [!ENDIF!]
[!ENDSELECT!]
[!/* If no resource is allocated to master core, add master core to CGCoreUsed as dummy core */!]
[!VAR "pattern" = "concat('CORE', $CGMasterCoreId)"!]
[!IF "not(contains(text:split($CGCoreUsed),$pattern))"!]
  [!VAR "CGCoreUsed" = "concat($CGCoreUsed, $pattern, ',')"!][!//
[!ENDIF!]
[!VAR "MaxCoreConfigured" = "num:i(count(text:split($CGCoreUsed, ',')))"!]
[!ENDNOCODE!][!//
[!CR!]
/* Configuration: ResourceM
The configuration contains allocation of Gpt channels across cores.
- if STD_ON, atleast one Gpt channel is configured in the core.
- if STD_OFF, no Gpt channels are configured in the core. */
[!NOCODE!][!//
[!FOR "CoreIndex" = "num:i(1)" TO "num:i(6)"!][!//
  [!VAR "corePattern" = "concat( 'CORE', num:i($CoreIndex - 1) )"!]
  [!VAR "matchCore" = "concat( '^.*(', $corePattern, ').*$' )"!]
  [!IF "text:match($CGCoreUsed, $matchCore)"!] [!// Fetch all strings matching the core.
    [!CODE!]
    [!AUTOSPACING!]
    [!INDENT "0"!]
    #define GPT_CONFIGURED_CORE[!"num:i($CoreIndex - 1)"!]                              (STD_ON)
    [!ENDINDENT!]
    [!ENDCODE!]
  [!ELSE!]
    [!CODE!]
    [!AUTOSPACING!]
    [!INDENT "0"!]
    #define GPT_CONFIGURED_CORE[!"num:i($CoreIndex - 1)"!]                              (STD_OFF)
    [!ENDINDENT!]
    [!ENDCODE!]
  [!ENDIF!]
[!ENDFOR!]
[!ENDNOCODE!]
[!CR!]
/* Number of Cores confgiured for Gpt */
#define GPT_MAX_CORE_USED                                 ([!"$MaxCoreConfigured"!]U)
[!CR!]
/* Number of channels configured as regular timers across all cores. */
[!/* [cover parentID={4AA5BFE1-A606-4cfa-B1AC-BE069F7E9FD5}] */!][!//
#define GPT_MAX_CHANNELS                                  ([!"num:i(num:i($ChannelMax)-num:i($PredefTimerChannels))"!]U)
[!/*  [/cover] */!][!//
[!CR!]
/* Number of channels configured as regular timers per core */
[!NOCODE!][!//
[!FOR "CoreIndex" = "num:i(1)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable'))"!][!//
  [!/* Fetch Normal and Predef Channel count */!]
  [!CALL "GPT_CG_GptCoreChannelInfo", "GptCoreId" = "num:i($CoreIndex - 1)"!]
  [!CODE!]
  [!AUTOSPACING!]
  [!INDENT "0"!]
  [!/* [cover parentID={5D79D60F-A3D4-43ad-9292-8BC5BBCADD0A}] */!][!//
  #define GPT_MAX_CHANNELS_CORE[!"num:i($CoreIndex - 1)"!]                            ([!"num:i($MaxChannelMappedToCore - $MaxPredefChannelMappedToCore)"!]U)
  [!/*  [/cover] */!][!//
  [!ENDINDENT!]
  [!ENDCODE!]
[!ENDFOR!]
[!ENDNOCODE!]
[!NOCODE!][!//
[!VAR "TomNo" = "num:i(0)"!][!//
[!VAR "AtomNo" = "num:i(0)"!][!//
[!SELECT "as:modconf('Gpt')[1]/GptChannelConfigSet/GptChannelConfiguration"!][!//
[!FOR "ChannelId" = "num:i(1)" TO "num:i($ChannelMax)"!][!//
  [!SELECT "./*[GptChannelId = num:i($ChannelId) - num:i(1)]"!][!//
  [!SELECT "./GtmTimerOutputModuleConfiguration/*[1]"!][!//
  [!CALL "GPT_CG_GetGTMChannelParam","GtmTimerString" = "GtmTimerUsed""!][!//
  [!ENDSELECT!][!//
  [!IF "$GtmTimerType = 'TOM'"!][!//
    [!VAR "TomNo" = "num:i($TomNo) + num:i(1)"!][!//
  [!ELSEIF "$GtmTimerType = 'ATOM'"!][!//
    [!VAR "AtomNo" = "num:i($AtomNo) + num:i(1)"!][!//
  [!ENDIF!][!//
  [!ENDSELECT!][!//
[!ENDFOR!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!][!//
[!CR!]
/* Adds/removes the code related to ‘TOM channels’
- if STD_ON, atleast one of the channel is using TOM channel
- if STD_OFF, none of the channels are using TOM channel */
[!/* [cover parentID={96F6B743-CD32-4746-B6D7-FDE693C57B30}] */!][!//
#define GPT_TOM_USED                                      ([!//
[!IF "$TomNo > num:i(0)"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)
[!/*  [/cover] */!][!//
[!CR!][!//
/* Adds/removes the code related to ‘ATOM channels’
- if STD_ON, atleast one of the channel is using ATOM channel
- if STD_OFF, none of the channels are using ATOM channel */
[!/* [cover parentID={FCFCE90A-4FA2-4f75-8C73-D1FC7919D752}] */!][!//
#define GPT_ATOM_USED                                     ([!//
[!IF "$AtomNo > num:i(0)"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)
[!/*  [/cover] */!][!//
[!CR!][!//
/*******************************************************************************
**                          Gpt Channel Symbolic Names                        **
*******************************************************************************/
[!SELECT "as:modconf('Gpt')[1]/GptChannelConfigSet/GptChannelConfiguration/*"!][!//
/* Gpt Channel ID Enumerations for Channel Configuration. */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef GptConf_GptChannelConfiguration_[!"node:name(.)"!]
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GptConf_GptChannelConfiguration_[!"node:name(.)"!]  \
                                                           ((Gpt_ChannelType)[!"GptChannelId"!]U)
#endif
[!ENDSELECT!][!//
[!CR!]
/*******************************************************************************
**                          Resource Availability                             **
*******************************************************************************/
[!CR!][!//
#define GPT_GTM_TOM_MODULE                                ([!"ecu:get('Gtm.NumberOfTomModules')"!]U)
#define GPT_GTM_TOM_CHANNELS_PER_TGC                      ([!"ecu:get('Gtm.NumberOfChannelsPerTgc')"!]U)
[!CR!][!//
#define GPT_GTM_ATOM_MODULE                               ([!"ecu:get('Gtm.NumberOfAtomModules')"!]U)
#define GPT_GTM_ATOM_CHANNELS_PER_AGC                     ([!"ecu:get('Gtm.NumberOfChannelsPerAgc')"!]U)
[!CR!][!//
#endif /* GPT_CFG_H */
/* End Of File */