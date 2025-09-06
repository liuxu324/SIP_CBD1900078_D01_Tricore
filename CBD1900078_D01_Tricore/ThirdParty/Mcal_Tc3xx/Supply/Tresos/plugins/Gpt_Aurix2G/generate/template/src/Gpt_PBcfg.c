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
**  FILENAME  : Gpt_PBcfg.c                                                   **
**                                                                            **
**  VERSION   : 7.0.0                                                         **
**                                                                            **
**  DATE      : 2018-08-30                                                    **
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
**  TRACEABILITY : [cover parentID={3A38785D-88CE-48fe-841D-A1BCB81DDCF7} ]   **
**                                                                            **
**  DESCRIPTION  : Code template source file for GPT Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of GPT Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!]
[!CODE!][!// Template
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
**  FILENAME  : Gpt_PBcfg.c                                                   **
**                                                                            **
**  VERSION   : 7.0.0                                                         **
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
[!ENDCODE!][!// End of Template

[!INCLUDE "Gpt.m"!]

[!CODE!][!// Template
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Include module header File */
#include "Gpt.h"
[!CR!]
[!ENDCODE!][!// End of Template

[!/* Variation Point */!]
[!VAR "PredefinedVarName" = "''"!]
[!SELECT "as:modconf('EcuC')[1]"!]
  [!IF "node:exists(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!]
    [!VAR "index" = "num:i(count(text:split(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef, '/')))"!]
    [!VAR "PredefinedVarName" = "concat('_', text:split(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef, '/')[num:i($index)])"!]
  [!ENDIF!]
[!ENDSELECT!]

[!CODE!][!// Template
/*******************************************************************************
**                      Inclusion File Check                                  **
*******************************************************************************/


/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/


/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/


/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/


/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
[!ENDCODE!][!// End of Template

[!/* Generate Gpt Notifications */!]
[!VAR "PredefTimerStatus" = "'GPT_TIMER_CHANNEL_NORMAL'"!][!//
[!VAR "PredefTimerChannels" = "num:i(0)"!][!//
[!VAR "GptNotificationList" = "''"!][!//
[!VAR "GptNotifChannelMapping" = "''"!][!//
[!SELECT "as:modconf('Gpt')[1]"!][!//
  [!LOOP "./GptChannelConfigSet/GptChannelConfiguration/*"!][!//
    [!IF "node:exists(GptNotification/*[1])"!][!//
      [!IF "not(num:isnumber(GptNotification/*[1]))"!][!//
        [!VAR "Notification" = "GptNotification/*[1]"!][!//
        [!IF "($Notification = 'NULL') or ($Notification = 'NULL_PTR') or ($Notification = '')"!][!//
          [!ERROR!][!//
            [!AUTOSPACING!]
            [!INDENT "0"!]
            ERROR: If Notification is not desired, then remove the Notification container. Notification of "NULL" , "NULL_PTR" or empty field is not allowed
            [!ENDINDENT!]
          [!ENDERROR!][!//
        [!ELSE!]
          [!IF "not(contains(text:split($GptNotificationList), $Notification))"!]
            [!VAR "GptNotificationList" = "concat($GptNotificationList , $Notification, '#,')"!][!//
          [!ENDIF!]
          [!VAR "GptNotifChannelMapping" = "concat($GptNotifChannelMapping , $Notification, '#', node:name(.), ',')"!][!//
        [!ENDIF!][!//
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!CODE!][!//
[!AUTOSPACING!]
[!INDENT "0"!]
/*
  Channel Notification Function Declarations
 */
[!ENDINDENT!]
[!ENDCODE!][!//
[!LOOP "text:split($GptNotificationList, ',')"!][!//
  [!VAR "matchItem" = "concat( '^.*(', (.), ').*$' )"!]
  [!VAR "fetchItem" = "concat( '^', (.), '.*$' )"!]
  [!IF "text:match($GptNotifChannelMapping, $matchItem)"!] [!// Fetch all strings matching.
    [!VAR "grepData" = "translate(text:grep(text:split($GptNotifChannelMapping, ','), $fetchItem), '[]', '')"!]
  [!ENDIF!]
  [!CODE!][!//
    [!AUTOSPACING!]
    [!INDENT "0"!]
    /* 
    [cover parentID={153D3242-9699-47b7-8EB6-CC8041BD659F}]
    [!"text:replaceAll( $grepData, (.), '')"!]
     channel notification function(s) declaration 
	[/cover]
	*/
    extern void [!"text:replace( (.), '#', '' )"!](void);
    [!CR!]
    [!ENDINDENT!][!//
  [!ENDCODE!][!//
[!ENDLOOP!][!//

[!CODE!][!// Template
/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
[!CR!]
[!ENDCODE!][!// End of template

[!SELECT "as:modconf('Gpt')[1]"!][!//
  [!VAR "GptPredefTimer1us" = "GptDriverConfiguration/GptPredefTimer1usEnablingGrade"!][!//
  [!IF "contains($GptPredefTimer1us, 'ENABLED')"!][!//
    [!VAR "GptPredefTimer1usStat" = "'true'"!][!//
  [!ELSE!][!//
    [!VAR "GptPredefTimer1usStat" = "'false'"!][!//
  [!ENDIF!][!//
  [!VAR "GptPredefTimer100us" = "GptDriverConfiguration/GptPredefTimer100us32bitEnable"!][!//
  [!IF "$GptPredefTimer100us = 'true'"!][!//
    [!VAR "GptPredefTimer100usStat" = "'true'"!][!//
  [!ELSE!][!//
    [!VAR "GptPredefTimer100usStat" = "'false'"!][!//
  [!ENDIF!][!//
  [!VAR "ReportWakeupSource" = "GptDriverConfiguration/GptReportWakeupSource"!][!//
  [!IF "$ReportWakeupSource = 'true'"!][!//
    [!SELECT "./GptChannelConfigSet"!][!//
      [!VAR "WakeupFlag" = "'false'"!][!//
      [!LOOP "GptChannelConfiguration/*"!][!//
        [!IF "./GptEnableWakeup ='true'"!][!//
          [!VAR "WakeupFlag" = "'true'"!][!//
        [!ENDIF!][!//
      [!ENDLOOP!][!//
      [!IF "$WakeupFlag = 'false'"!][!//
        [!ERROR!][!//
          [!AUTOSPACING!]
          [!INDENT "0"!]
          ERROR: Wrong Configuration. You have not configured any channel for wakeup capability  in Configuration [!"node:name(.)"!]
          but GptReportWakeupSource is set to true.In Post Build configuration, if GptReportWakeupSource is set then
          the configurations should have atleast one wakeup capable channel.
          [!ENDINDENT!]
        [!ENDERROR!][!//
      [!ENDIF!][!//
    [!ENDSELECT!][!//
  [!ENDIF!][!//
[!ENDSELECT!][!//

[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Gpt')[1]"!][!//
  [!/*
  If any of the channel needs to be wakeup capable then Gtm Clock should have
  the capability to disable GTM Clock Sleep mode when sleep mode is requested.
  */!][!//
  [!/* [cover parentID={40A68E73-EC73-41a7-A60C-FD43AD05F294}] */!]
  [!/*  [/cover] */!]
  [!SELECT "as:modconf('Mcu')[1]"!][!//
    [!/* Access Gtm Clock Sleep Mode */!][!//
    [!VAR "GtmSleepMode" = "./McuGeneralConfiguration/McuGtmSleepModeEnabled"!][!//
  [!ENDSELECT!][!//
  [!VAR "GptChannelCount" = "num:i(0)"!][!//
  [!VAR "GptChannelCountConfigured" = "num:i(count(./GptChannelConfigSet/GptChannelConfiguration/*))"!][!//
[!ENDSELECT!][!//

[!/* Validate Gpt configuration */!]
[!SELECT "as:modconf('Gpt')[1]/GptChannelConfigSet/GptChannelConfiguration"!][!//
  [!VAR "MaxChannels"= "num:i(count(./*))"!][!//
  [!/* Check whether ChannelId is continuous. */!]
  [!FOR "ChannelId" = "num:i(1)" TO "num:i($MaxChannels)"!][!//
    [!IF "not(node:exists(./*[GptChannelId = num:i($ChannelId) - num:i(1)]))"!]
    [!ERROR!][!//
      [!AUTOSPACING!]
      [!INDENT "0"!]
      ERROR: GptChannelId must be continuous number. ChannelId "[!"num:i(num:i($ChannelId) - num:i(1))"!]" is missing.
      [!ENDINDENT!]
    [!ENDERROR!][!//
    [!ENDIF!]
  [!ENDFOR!]

  [!/* Check duplicate Channel instances and Proper Channel allocation. */!]
  [!FOR "ChannelId" = "num:i(1)" TO "num:i($MaxChannels)"!][!//
    [!SELECT "./*[GptChannelId = num:i($ChannelId) - num:i(1)]"!][!//
    [!VAR "Conf" = "node:name(.)"!]
    [!SELECT "./GtmTimerOutputModuleConfiguration/*"!]
    [!CALL "GPT_CG_GetGTMChannelParam","GtmTimerString" = "GtmTimerUsed"!][!//
    [!VAR "GlobalChannelNumber1" = "$GlobalChannelNumber"!][!//
      [!FOR "ChannelId1" = "num:i(num:i($ChannelId)+num:i(1))" TO "num:i($MaxChannels)"!][!//
        [!SELECT "../../../*[GptChannelId = num:i($ChannelId1) - num:i(1)]"!][!//
        [!SELECT "./GtmTimerOutputModuleConfiguration/*"!]
        [!CALL "GPT_CG_GetGTMChannelParam","GtmTimerString" = "GtmTimerUsed"!][!//
        [!IF "$GlobalChannelNumber1 = $GlobalChannelNumber"!]
          [!ERROR!][!//
            [!AUTOSPACING!]
            [!INDENT "0"!]
            ERROR: Duplicate Channel Reference! [!"$Conf"!] and [!"node:name(.)"!] using the same channel reference.
            [!ENDINDENT!]
          [!ENDERROR!][!//
        [!ENDIF!]
        [!ENDSELECT!]
        [!ENDSELECT!]
      [!ENDFOR!]
    [!VAR "ChannelAlloc" = "node:value(node:ref(GtmTimerUsed)/*[1])"!]
    [!IF "not(contains($ChannelAlloc,'USED_BY_GPT'))"!][!//
      [!ERROR!][!//
        [!AUTOSPACING!]
        [!INDENT "0"!]
        ERROR: Wrong configuration. The Channel [!"GtmTimerUsed"!] in the configuration [!"node:name(../..)"!] is not meant for GPT driver. Check the ChannelAllocation in GtmTimerUsed under [!"node:name(.)"!]
        [!ENDINDENT!]
      [!ENDERROR!][!//
    [!ENDIF!][!//
    [!ENDSELECT!]
    [!ENDSELECT!]
  [!ENDFOR!]

  [!/* Check at-least one normal GPT channel in configured. */!]
  [!IF "($GptPredefTimer1usStat = 'true') or ($GptPredefTimer100usStat = 'true')"!][!//
    [!SELECT ".."!][!//
      [!VAR "TotalChCount" = "num:i(count(GptChannelConfiguration/*))"!][!//
      [!VAR "TotalPredefCh" = "num:i(0)"!][!//
    [!ENDSELECT!][!//
    [!FOR "ChannelId" = "num:i(1)" TO "num:i($TotalChCount)"!][!//
      [!SELECT "./*[GptChannelId = num:i($ChannelId) - num:i(1)]"!][!//
        [!IF "contains(node:value(GptTimerChannelUsage),'_1US_') or contains(node:value(GptTimerChannelUsage),'_100US_')"!][!//
          [!VAR "TotalPredefCh" = "num:i(num:i($TotalPredefCh)+num:i(1))"!][!//
        [!ENDIF!][!//
      [!ENDSELECT!][!//
    [!ENDFOR!][!//
    [!VAR "NormalChannels" = "num:i(num:i($TotalChCount)-num:i($TotalPredefCh))"!][!//
    [!IF "(num:i($NormalChannels) = num:i(0))"!][!//
      [!ERROR!][!//
        ERROR : Configure atleast one normal channel for GPT.
      [!ENDERROR!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//

  [!/*
      Check if any conflict between driver configuration and channel
      configurations in case of Gpt Predef timers
  */!]
  [!IF "($GptPredefTimer1usStat = 'true') or ($GptPredefTimer100usStat = 'true')"!][!//
    [!/* 1us Predef Timer */!]
    [!IF "($GptPredefTimer1usStat = 'true')"!][!//
      [!VAR "Status1Us" = "num:i(0)"!][!//
      [!FOR "ChannelId" = "num:i(1)" TO "num:i($MaxChannels)"!][!//
        [!SELECT "./*[GptChannelId = num:i(num:i($ChannelId) - num:i(1))]"!][!//
          [!IF "contains(node:value(GptTimerChannelUsage), '_1US_')"!][!//
            [!VAR "Status1Us" = "num:i(1)"!][!//
          [!ENDIF!][!//
        [!ENDSELECT!][!//
      [!ENDFOR!][!//
      [!IF "num:i($Status1Us) = num:i(0)"!][!//
        [!ERROR!][!//
          [!AUTOSPACING!]
          [!INDENT "0"!]
          ERROR: No Channel is configured to support a 1US predef timer.
          If 1US predef timer facility is not desired, disable it in the driver configuration.
          [!ENDINDENT!]
        [!ENDERROR!][!//
      [!ENDIF!][!//
    [!ENDIF!]

    [!/* 100us Predef Timer */!]
    [!IF "($GptPredefTimer100usStat = 'true')"!][!//
      [!VAR "Status100Us" = "num:i(0)"!][!//
      [!FOR "ChannelId" = "num:i(1)" TO "num:i($MaxChannels)"!][!//
        [!SELECT "./*[GptChannelId = num:i($ChannelId) - num:i(1)]"!][!//
          [!IF "contains(node:value(GptTimerChannelUsage), '_100US_')"!][!//
            [!VAR "Status100Us" = "num:i(1)"!][!//
          [!ENDIF!][!//
        [!ENDSELECT!][!//
      [!ENDFOR!][!//
      [!IF "num:i($Status100Us) = num:i(0)"!][!//
        [!ERROR!][!//
          [!AUTOSPACING!]
          [!INDENT "0"!]
          ERROR: No Channel is configured to support a 100US predef timer.
          If 100US predef timer facility is not desired, disable it in the driver configuration.
          [!ENDINDENT!]
        [!ENDERROR!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//

  [!/* Validate GPT Predef Timer Requirements. */!]
  [!IF "($GptPredefTimer1usStat = 'true') or ($GptPredefTimer100usStat = 'true')"!][!//
    [!FOR "ChannelId" = "num:i(1)" TO "num:i($MaxChannels)"!][!//
      [!SELECT "./*[GptChannelId = num:i($ChannelId) - num:i(1)]"!][!//
      [!SELECT "./GtmTimerOutputModuleConfiguration/*[1]"!][!//
      [!CALL "GPT_CG_GetGTMChannelParam","GtmTimerString" = "GtmTimerUsed"!][!//
      [!ENDSELECT!][!//
      [!VAR "GptPredefTimerType" = "node:value(GptTimerChannelUsage)"!]
      [!IF "contains($GptPredefTimerType,'ENABLED')"!][!//
        [!VAR "PredefTimerChannels" = "num:i(num:i($PredefTimerChannels)+num:i(1))"!][!//
        [!VAR "PredefTimerStatus" = "'GPT_PREDEF_TIMER_ENABLED'"!][!//
        [!IF "contains($GptPredefTimerType, '100US_32BIT')"!]
            [!VAR "TempNode" = "node:name(.)"!]
            [!FOR "ChannelId1" = "num:i(num:i($ChannelId)+num:i(1))" TO "num:i($MaxChannels)"!][!//
              [!SELECT "../*[GptChannelId = num:i($ChannelId1) - num:i(1)]"!][!//
              [!IF "node:value(GptTimerChannelUsage) = $GptPredefTimerType"!]
                [!ERROR!]
                  [!AUTOSPACING!]
                  [!INDENT "0"!]
                  ERROR : GPT_PREDEF_TIMER_100US_32BIT is already enabled in [!"$TempNode"!].
                  Disable "GptTimerChannelUsage" in [!"$TempNode"!] or [!"node:name(.)"!]
                  [!ENDINDENT!]
                [!ENDERROR!]
              [!ENDIF!]
              [!ENDSELECT!]
            [!ENDFOR!]
        [!ENDIF!]
        [!IF "contains($GptPredefTimerType, '_1US_')"!]
          [!IF "(substring-before(substring-after(($GptPredefTimer1us),'TIMER_'),'_ENABLED')) != (substring-before(substring-after(($GptPredefTimerType),'TIMERCH_'),'_ENABLED'))"!]
            [!ERROR!][!//
              [!AUTOSPACING!]
              [!INDENT "0"!]
              Config Error : This GPT driver is configured to support a predef timer of type [!"substring-before($GptPredefTimer1us, '_ENABLED')"!].
              But channel under [!"node:name(.)"!] is configured to support an invalid predef timer type.
              Change the selection accordingly in GptTimerChannelUsage under [!"node:name(.)"!].
              [!ENDINDENT!]
            [!ENDERROR!][!//
          [!ENDIF!]
          [!VAR "TempNode" = "node:name(.)"!]
          [!FOR "ChannelId1" = "num:i(num:i($ChannelId)+num:i(1))" TO "num:i($MaxChannels)"!][!//
            [!SELECT "../*[GptChannelId = num:i($ChannelId1) - num:i(1)]"!][!//
            [!IF "contains(node:value(GptTimerChannelUsage), '_1US_')"!]
              [!ERROR!]
                [!AUTOSPACING!]
                [!INDENT "0"!]
                ERROR :  GPT_PREDEF_TIMER_1US is already enabled in [!"$TempNode"!].
                Disable "GptTimerChannelUsage" in [!"$TempNode"!] or [!"node:name(.)"!].
                Change the grade to 32bit to get the maximum time span.
                [!ENDINDENT!]
              [!ENDERROR!]
            [!ENDIF!]
            [!ENDSELECT!]
          [!ENDFOR!]
        [!ENDIF!]
      [!ENDIF!][!//
      [!ENDSELECT!]
    [!ENDFOR!][!//
  [!ENDIF!]

  [!/* Gpt predef timers must have maximum Channel ID number */!]
  [!IF "($GptPredefTimer1usStat = 'true') and ($GptPredefTimer100usStat = 'true')"!][!//
    [!FOR "ChannelId" = "num:i(1)" TO "num:i($MaxChannels)"!][!//
      [!SELECT "./*[GptChannelId = num:i($ChannelId) - num:i(1)]"!][!//
        [!IF "contains(node:value(GptTimerChannelUsage), 'ENABLED')"!][!//
          [!IF "num:i(node:value(GptChannelId)) != num:i(num:i($MaxChannels) - num:i(1)) and num:i(node:value(GptChannelId)) != num:i(num:i($MaxChannels) - num:i(2))"!][!//
            [!ERROR!][!//
              [!AUTOSPACING!]
              [!INDENT "0"!]
              ERROR: Give maximum GptchannelId numbers to the predef timers.
              GptchannelId of predef timer channel must be "[!"num:i(num:i($MaxChannels) - num:i(1))"!]" or "[!"num:i(num:i($MaxChannels) - num:i(2))"!]"
              [!ENDINDENT!]
            [!ENDERROR!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDSELECT!][!//
    [!ENDFOR!][!//
  [!ELSEIF "($GptPredefTimer1usStat = 'true') or ($GptPredefTimer100usStat = 'true')"!][!//
    [!FOR "ChannelId" = "num:i(1)" TO "num:i($MaxChannels)"!][!//
      [!SELECT "./*[GptChannelId = num:i($ChannelId) - num:i(1)]"!][!//
        [!IF "contains(node:value(GptTimerChannelUsage), 'ENABLED')"!][!//
          [!IF "num:i(node:value(GptChannelId)) != num:i(num:i($MaxChannels) - num:i(1))"!][!//
            [!ERROR!][!//
              [!AUTOSPACING!]
              [!INDENT "0"!]
              ERROR: Give maximum GptchannelId number to the predef timer.
              GptchannelId of predef timer channel must be "[!"num:i(num:i($MaxChannels) - num:i(1))"!]"
              [!ENDINDENT!]
            [!ENDERROR!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDSELECT!][!//
    [!ENDFOR!][!//
  [!ENDIF!][!//

  [!/* Validate the configured Gtm Timers under Predef Timers */!]
  [!IF "($GptPredefTimer1usStat = 'true') or ($GptPredefTimer100usStat = 'true')"!]
    [!FOR "ChannelId" = "num:i(1)" TO "num:i($MaxChannels)"!][!//
      [!SELECT "./*[GptChannelId = num:i($ChannelId) - num:i(1)]"!][!//
        [!VAR "GptPredefTimerType" = "node:value(GptTimerChannelUsage)"!]
        [!IF "contains($GptPredefTimerType,'ENABLED')"!][!//
          [!/* Get the Gtm Configuration which acts as the actual Predef Timer */!]
          [!CALL "GPT_CG_GetPredefTimerInfo", "Channel" = "$ChannelId"!]
        [!ENDIF!]
      [!ENDSELECT!]
    [!ENDFOR!]
  [!ENDIF!]
[!ENDSELECT!]

[!/* Collect core-channel mappings from Resource Manager. */!]
[!CALL "GPT_CG_GenerateModuleMap", "Module"="'GPT'"!][!//

[!/* Append the missing resources to master core and fetch Predef Timers information */!]
[!VAR "Is1usPredefChannelAvailable"   = "'false'"!][!//
[!VAR "Is100usPredefChannelAvailable" = "'false'"!][!//
[!VAR "Gpt1usPredefTimerChannelId"       =  "''"!]
[!VAR "Gpt100usPredefTimerChannelId"     =  "''"!]
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
  [!/* Sort Predef Timers */!]
  [!IF "contains(GptTimerChannelUsage,'_1US_')"!][!//
    [!VAR "Is1usPredefChannelAvailable" = "'true'"!][!//
    [!VAR "Gpt1usPredefTimerChannelId" = "num:i(GptChannelId)"!][!//
  [!ELSEIF "contains(GptTimerChannelUsage,'_100US_')"!][!//
    [!VAR "Is100usPredefChannelAvailable" = "'true'"!][!//
    [!VAR "Gpt100usPredefTimerChannelId" = "num:i(GptChannelId)"!][!//
  [!ENDIF!][!//
[!ENDSELECT!]

[!/* If no resource is allocated to master core, add master core to CGCoreUsed as dummy core */!]
[!VAR "pattern" = "concat('CORE', $CGMasterCoreId)"!]
[!IF "not(contains(text:split($CGCoreUsed),$pattern))"!]
  [!VAR "CGCoreUsed" = "concat($CGCoreUsed, $pattern, ',')"!][!//
[!ENDIF!]

[!/* Get the max channel count */!]
[!SELECT "GptChannelConfigSet"!][!//
  [!VAR "ChannelMax" = "num:i(count(GptChannelConfiguration/*))"!][!//
[!ENDSELECT!][!//

[!/* Generate Channel Configuration */!]
[!CODE!]
[!AUTOSPACING!]
[!INDENT "0"!]
/*
[!WS!]Channel Configuration Instance
*/
[!ENDINDENT!]
[!ENDCODE!]
[!VAR "GptChStructGenerated" = "''"!]
[!VAR "MaxCoreConfigured" = "num:i(count(text:split($CGCoreUsed, ',')))"!]
[!/* Iterate for each cores used by Gpt Driver */!]
[!FOR "ConfigCoreIndex" = "num:i(1)" TO "$MaxCoreConfigured"!]
  [!VAR "GptCurrentCoreId" = "substring-after(text:split($CGCoreUsed, ',')[num:i($ConfigCoreIndex)], 'CORE')"!]
  [!VAR "GptChannelCounter" = "num:i(0)"!][!// Channel counter
  [!VAR "GptChannelOffsetMap" = "''"!]
  [!/* Fetch Normal and Predef Channel count */!]
  [!CALL "GPT_CG_GptCoreChannelInfo", "GptCoreId" = "$GptCurrentCoreId"!]
  [!/* Iterate over all channels */!]
  [!SELECT "as:modconf('Gpt')[1]"!]
    [!SELECT "node:order(./GptChannelConfigSet/GptChannelConfiguration/*, 'node:value(./GptChannelId)')"!]
      [!VAR "pattern" = "concat(text:split($CGCoreUsed, ',')[num:i($ConfigCoreIndex)], '_', node:name(node:current()), '#')"!]
      [!IF "contains($CGModuleMap, $pattern)"!]
        [!IF "contains(GptTimerChannelUsage, '_NORMAL')"!]
          [!VAR "GptChannelOffsetMap" = "concat($GptChannelOffsetMap, "CH", num:i(./GptChannelId), '#_', $GptChannelCounter, ',')"!][!//
          [!SELECT "./GtmTimerOutputModuleConfiguration/*[1]"!]
            [!CALL "GPT_CG_GetGTMChannelParam","GtmTimerString" = "GtmTimerUsed"!]
              [!IF "$GtmTimerType = 'ATOM'"!]
                [!VAR "TimerType" = "'MCU_GTM_TIMER_ATOM'"!]
              [!ELSE!]
                [!VAR "TimerType" = "'MCU_GTM_TIMER_TOM'"!]
              [!ENDIF!]
          [!ENDSELECT!]
          [!/*
          Set period, duty match timer interrupt and interrupt mode
          By default interrupts are disabled and Pulse-Notify mode is selected
          */!]
          [!VAR "IntEnMode" = "num:i(128)"!][!//
          [!VAR "EnableWakeup" = "GptEnableWakeup"!][!//
          [!IF "($EnableWakeup = 'true' and $GtmSleepMode = 'true')"!][!//
            [!ERROR!]
              [!AUTOSPACING!]
              [!INDENT "0"!]
              Configuration ERROR: Gtm Clock is not configured with Sleep Disable request.
              But GPT is having a wakeup capable channel. Change the gtm clock configuration.
              [!ENDINDENT!]
            [!ENDERROR!]
          [!ENDIF!]
          [!IF "node:exists(GptNotification/*[1])"!]
            [!VAR "Notification" = "GptNotification/*[1]"!]
          [!ENDIF!]
          [!IF "node:empty(GptNotification/*[1])"!]
            [!VAR "Notification" = "'NULL_PTR'"!]
          [!ELSE!]
            [!IF "num:isnumber($Notification) = 'true'"!]
              [!VAR "Notification" = "concat('(Gpt_NotificationPtrType)',$Notification)"!]
            [!ELSE!]
              [!VAR "Notification" = "concat('&',$Notification)"!]
            [!ENDIF!]
          [!ENDIF!]
          [!VAR "WakeupInfo" = "num:i(0)"!][!//select
          [!IF "node:value(../../../GptDriverConfiguration/GptReportWakeupSource) = 'true' and node:value(./GptEnableWakeup) = 'true'"!][!//
            [!IF "node:exists(./GptWakeupConfiguration/*[1]/GptWakeupSourceRef) and string-length(./GptWakeupConfiguration/*[1]/GptWakeupSourceRef) > 0"!][!//
              [!VAR "NodePath" = "node:path(node:ref(./GptWakeupConfiguration/*[1]/GptWakeupSourceRef))"!][!//
              [!SELECT "node:ref($NodePath)"!][!//
                [!VAR "WakeupInfo" = "(EcuMWakeupSourceId)"!]
              [!ENDSELECT!]
            [!ELSE!][!//
              [!ERROR!][!//
                [!AUTOSPACING!]
                [!INDENT "0"!]
                Config Error: GptWakeupSourceRef is not configured for wakeup capable channel [!"node:path(node:current())"!].If wakeup functionality is needed,Provide reference to EcuM Wakeup source otherwise disable wakeup feature for the channel by unchecking GptEnableWakeup.
                [!ENDINDENT!]
              [!ENDERROR!][!//
            [!ENDIF!][!//
          [!ENDIF!][!//
          [!VAR "EnableWakeup" = "GptEnableWakeup"!][!//
          [!IF "$EnableWakeup = 'true'"!][!//
            [!VAR "EnableWakeup" = "'(boolean)TRUE'"!][!//
          [!ELSE!][!//
            [!VAR "EnableWakeup" = "'(boolean)FALSE'"!][!//
          [!ENDIF!][!//
          [!VAR "ChannelMode" = "GptChannelMode"!][!//
          [!IF "$ChannelMode = 'GPT_CH_MODE_CONTINUOUS'"!][!//
            [!VAR "ChannelMode" = "'GPT_MODE_CONTINUOUS'"!][!//
          [!ENDIF!][!//
          [!IF "$ChannelMode = 'GPT_CH_MODE_ONESHOT'"!][!//
            [!VAR "ChannelMode" = "'GPT_MODE_ONESHOT'"!][!//
          [!ENDIF!][!//
          [!SELECT "./GtmTimerOutputModuleConfiguration/*[1]"!][!//
            [!VAR "GptChannelClock_freq" ="node:value(GtmTimerClockSelect)"!][!//
            [!VAR "CtrlReg" = "num:hextoint('0x00000800')"!][!//(Default Value)
            [!/* Set Clock Source for Timer Channel*/!][!//
            [!VAR "CtrlReg" = "bit:or($CtrlReg,bit:shl(substring-after(($GptChannelClock_freq),'CLOCK_'),12))"!][!//
            [!IF "$GtmTimerType = 'ATOM'"!][!//
              [!/* Set ATOM mode as SOMP (10B ATOM Signal Output Mode PWM (SOMP)), then only OSM bit is applicable */!][!//
              [!VAR "CtrlReg" = "bit:or($CtrlReg, num:i(2))"!][!//
            [!ENDIF!][!//
            [!IF "$ChannelMode = 'GPT_MODE_ONESHOT'"!][!//
              [!/* Enable the channel in One Shot Mode. OSM = 1 */!][!//
              [!VAR "CtrlReg" = "bit:or($CtrlReg,bit:shl(1,26))"!][!//
              [!/* Enable the CCU0 Interrupt */!][!//
              [!VAR "IntEnMode" = "num:i(128)"!][!//
            [!ENDIF!][!//
          [!ENDSELECT!][!//
          [!IF "not(text:contains(text:split($GptChStructGenerated, ','), $GptCurrentCoreId))"!]
            [!VAR "GptChStructGenerated" = "text:toupper(text:concat($GptChStructGenerated, concat($GptCurrentCoreId, ',')))"!]
            [!VAR "OpenBraces" = "num:i(1)"!]
            [!CODE!]
            [!AUTOSPACING!]
            [!INDENT "0"!]
            [!CR!]
            [!/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}] */!][!//
            [!/*  [/cover] */!][!//
            /* Memory mapping for configuration data */
            /* [/cover] */
            /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            #define GPT_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"$GptCurrentCoreId"!]_UNSPECIFIED
            /*MISRA2012_RULE_20_1_JUSTIFICATION: File inclusion after pre-processor
            directives is allowed only for MemMap.h*/
            /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
              without safegaurd. It complies to Autosar guidelines. */
            #include "Gpt_MemMap.h"
            [!CR!]
            static const Gpt_ChannelConfigType Gpt_kChannelConfig_Core[!"$GptCurrentCoreId"!][ ] =
            {
            [!ENDINDENT!]
            [!ENDCODE!]
          [!ENDIF!]
          [!CODE!]
          [!AUTOSPACING!]
          [!INDENT "2"!]
          /*
          [!WS!] Channel Symbolic Name(ChannelId) : [!"node:name(.)"!]
          [!WS!] GTM TOM/ATOM Channel : [!"$GlobalChannelNumber"!] in [!"$ChannelMode"!]
          */
          {
          [!INDENT "4"!]
            #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
            [!"$Notification"!], /* Notification Function */
            #endif

            #if ( (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) \
                && (GPT_REPORT_WAKEUP_SOURCE == STD_ON) )
            [!"$WakeupInfo"!]U, /* Wakeup Info */
            #endif

            #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
            [!"$EnableWakeup"!], /* Wakeup Capability */
            #endif

            [!"$ChannelMode"!], /* Channel Mode */
          [!ENDINDENT!]
          [!ENDINDENT!]
          [!ENDCODE!]
          [!SELECT "./GtmTimerOutputModuleConfiguration/*[1]"!][!//
            [!VAR "GtmCpuId" = "text:toupper(text:concat('CPU_CORE_', $GptChCoreID))"!][!//
            [!CODE!][!//
            [!AUTOSPACING!]
            [!INDENT "4"!]
              {
                [!INDENT "6"!]
                [!"$TimerType"!], /* Timer Type (TOM/ATOM)*/
                [!"num:inttohex(bit:or(bit:shl($GtmTimerModNo, num:i(8)), $GtmTimerChNo))"!], /* Timer Number Module No | Timer Channel No */
                [!"num:inttohex($CtrlReg)"!]U, /* Channel Control Register */
                [!"num:inttohex(num:i(0))"!]U, /* CN0 in ticks */
                [!"num:inttohex(num:i(0))"!]U, /* CM0 in ticks */
                [!"num:inttohex(num:i(0))"!]U, /* CM1 in ticks */
                [!"num:inttohex(num:i(0))"!]U, /* SR0 in ticks */
                [!"num:inttohex(num:i(0))"!]U, /* SR1 in ticks */
                [!"num:inttohex(num:i(0))"!]U, /* Port Out     */
                [!"num:inttohex($IntEnMode)"!]U  /* Interrupt status and mode*/
                [!ENDINDENT!]
              }
            [!ENDINDENT!]
            [!ENDCODE!]
          [!ENDSELECT!]
          [!VAR "GptChannelCounter" = "num:i($GptChannelCounter + 1)"!][!//
          [!IF "num:i($GptChannelCounter) != num:i(num:i($MaxChannelMappedToCore)-num:i($MaxPredefChannelMappedToCore))"!]
            [!CODE!]
            [!AUTOSPACING!]
            [!INDENT "2"!]
              },
              [!CR!][!//
            [!ENDINDENT!]
            [!ENDCODE!]
          [!ELSE!]
            [!VAR "OpenBraces" = "num:i(0)"!]
            [!CODE!]
            [!AUTOSPACING!]
            [!INDENT "2"!]
              }
            [!ENDINDENT!]
            [!ENDCODE!]
          [!ENDIF!]
          [!IF "$OpenBraces = num:i(0)"!]
            [!CODE!]
            [!AUTOSPACING!]
            [!INDENT "0"!]
            };
            [!CR!]
            /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            #define GPT_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"$GptCurrentCoreId"!]_UNSPECIFIED
            /* MISRA2012_RULE_20_1_JUSTIFICATION: File inclusion after pre-processor
              directives is allowed only for MemMap.h*/
            /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
              without safegaurd. It complies to Autosar guidelines. */
            #include "Gpt_MemMap.h"
            [!CR!]
            [!ENDINDENT!]
            [!ENDCODE!]
            [!NOCODE!]
            [!IF "$MaxCoreConfigured > num:i(1)"!]
              [!CODE!]
              [!AUTOSPACING!]
              [!INDENT "0"!]
              [!CR!]
              [!/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}] */!][!//
              [!/*  [/cover] */!][!//
              /* Memory mapping for constants */
              /* [/cover] */
              /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
              #define GPT_START_SEC_CONST_ASIL_B_CORE[!"$GptCurrentCoreId"!]_8
              /*MISRA2012_RULE_20_1_JUSTIFICATION: File inclusion after pre-processor
              directives is allowed only for MemMap.h*/
              /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
                without safegaurd. It complies to Autosar guidelines. */
              #include "Gpt_MemMap.h"
              [!CR!]
              /* Indexes of channels allocated to Core [!"$GptCurrentCoreId"!] */
              static const uint8 Gpt_ChannelIndex_Core[!"$GptCurrentCoreId"!][] =
              {
              [!ENDINDENT!]
              [!ENDCODE!]
              [!FOR "ChIndex" = "num:i(1)" TO "num:i(num:i($ChannelMax)-num:i($PredefTimerChannels))"!]
                [!VAR "chPattern" = "concat( 'CH', num:i($ChIndex - 1) )"!]
                [!VAR "matchCh" = "concat( '^.*(', $chPattern, '#).*$' )"!]
                [!VAR "fetchItem" = "concat( '^', $chPattern, '#.*$' )"!]
                [!IF "text:match($GptChannelOffsetMap, $matchCh)"!] [!// Fetch all strings matching the channel.
                  [!VAR "grepData" = "translate(text:grep(text:split($GptChannelOffsetMap, ','), $fetchItem), '[]', '')"!]
                  [!VAR "offset" = "num:inttohex(num:i(text:split($grepData,'_')[2]), 2)"!]
                [!ELSE!]
                  [!VAR "offset" = "'0xFF'"!]
                [!ENDIF!]
                [!CODE!]
                [!AUTOSPACING!]
                [!INDENT "2"!]
                [!"$offset"!]U,    /* Channel Id [!"num:i($ChIndex - 1)"!] */
                [!ENDINDENT!]
                [!ENDCODE!]
              [!ENDFOR!]
              [!CODE!]
              [!AUTOSPACING!]
              [!INDENT "0"!]
              };
              [!CR!]
              /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
              #define GPT_STOP_SEC_CONST_ASIL_B_CORE[!"$GptCurrentCoreId"!]_8
              /* MISRA2012_RULE_20_1_JUSTIFICATION: File inclusion after pre-processor
                directives is allowed only for MemMap.h*/
              /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
                without safegaurd. It complies to Autosar guidelines. */
              #include "Gpt_MemMap.h"
              [!ENDINDENT!]
              [!CR!]
              [!ENDCODE!]
            [!ENDIF!]
            [!ENDNOCODE!]
          [!ENDIF!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDSELECT!]
  [!ENDSELECT!]
[!ENDFOR!]

[!/* Predef Timer */!]
[!IF "num:i($PredefTimerChannels) != num:i(0)"!][!//
    [!/* 1us Predef Timer */!]
    [!CODE!]
    [!AUTOSPACING!]
    [!INDENT "0"!]
    #if ((GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON) || \
    [!WS!] (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON) || \
    [!WS!] (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
    [!ENDINDENT!]
    [!ENDCODE!][!//
    [!/* [cover parentID={270F6572-58A2-4e82-BF3A-EB4DCA271922}] */!]
    [!/*  [/cover] */!]
    [!FOR "ConfigCoreIndex" = "num:i(1)" TO "num:i($MaxCoreConfigured)"!]
      [!VAR "GptCurrentCoreId" = "substring-after(text:split($CGCoreUsed, ',')[num:i($ConfigCoreIndex)], 'CORE')"!]
      [!CODE!]
      [!AUTOSPACING!]
      [!INDENT "0"!]
      [!CR!]
      /* Memory Mapping the configuration constant */
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
         in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
         in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
         in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
         in generated code due to Autosar Naming constraints.*/
      #define GPT_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"$GptCurrentCoreId"!]_UNSPECIFIED
      /* MISRA2012_RULE_20_1_JUSTIFICATION: File inclusion after pre-processor
         directives is allowed only for MemMap.h*/
      /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
         without safegaurd. It complies to Autosar guidelines. */
      #include "Gpt_MemMap.h"
      [!CR!]
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
         in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
         in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
         in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
         in generated code due to Autosar Naming constraints.*/[!//
      [!/* [cover parentID={F0167C1F-3C98-408d-9DF7-CAD47B717B92}] */!][!//
      [!/*  [/cover] */!]
      static const Gpt_1UsPredefTimerChannelConfigType \
                                      Gpt_k1UsPredefTimerChannelConfig_Core[!"$GptCurrentCoreId"!] =
      {
      [!ENDINDENT!]
      [!ENDCODE!][!//
      [!IF "$Is1usPredefChannelAvailable = 'true'"!]
        [!/*
          Set period, duty match timer interrupt and interrupt mode
          By default interrupts are disabled and Level mode is selected
        */!]
        [!VAR "IntEnMode" = "num:i(0)"!][!//
        [!VAR "ChannelId" = "$Gpt1usPredefTimerChannelId + num:i(1)"!]
        [!SELECT "as:modconf('Gpt')[1]/GptChannelConfigSet/GptChannelConfiguration"!]
          [!SELECT "./*[GptChannelId = num:i($ChannelId) - num:i(1)]"!][!//
            [!VAR "GptPredefTimerType" = "node:value(GptTimerChannelUsage)"!][!//
              [!SELECT "as:modconf('Gpt')[1]/GptDriverConfiguration/GptClockReferencePoint/*[1]"!][!//
                [!VAR "ClockRef" = "GptClockReference"!][!//
              [!ENDSELECT!][!//
              [!VAR "GptPredefTimerUs" = "text:split($GptPredefTimerType,'TIMERCH_')[2]"!][!//
              [!VAR "GptPredefTimerUs" = "text:split($GptPredefTimerUs,'US_')[1]"!][!//
              [!VAR "CtrlReg2" = "num:i(0)"!]
              [!VAR "CN0_Value0" = "num:i(0)"!]
              [!VAR "CN0_Value2" = "num:i(0)"!]
              [!VAR "CM0_Value0" = "num:i(0)"!]
              [!VAR "CM0_Value2" = "num:i(0)"!]
              [!VAR "SR0_Value0" = "num:i(0)"!]
              [!VAR "SR0_Value2" = "num:i(0)"!]
              [!VAR "CtrlReg0" = "num:i(0)"!]
              [!/* Get the Gtm Configuration which acts as the actual Predef Timer */!]
              [!CALL "GPT_CG_GetPredefTimerInfo", "Channel" = "$ChannelId"!]
              [!VAR "ActualPredefTimerModNo"= "text:split( text:split($ActualPredefTimer, '_CHANNEL')[1], 'GTM_TOM')[1]"!]
              [!VAR "ActualPredefTimerChNo"= "text:split($ActualPredefTimer, '_CHANNEL')[2]"!]
              [!CALL "GPT_CG_GetGptPredefFreq","GtmClockRef" = "$ClockRef", "TimerModNo" = "$ActualPredefTimerModNo", "TickDurationUs" = "num:i($GptPredefTimerUs)", "OpnMode" = "num:i(1)"!][!//To check if an extra channel is needed for predef timer implementation
              [!VAR "PrevPredefTimerModNo"= "num:i(0)"!]
              [!VAR "PrevPredefTimerChNo"= "num:i(0)"!]
              [!IF "num:i($Extra_Channel) = num:i(1)"!][!// Need extra channel for frequency tuning
                [!VAR "PrevPredefTimerModNo"= "text:split( text:split($PreviousPredefTimer, '_CHANNEL')[1], 'GTM_TOM')[1]"!]
                [!VAR "PrevPredefTimerChNo"= "text:split($PreviousPredefTimer, '_CHANNEL')[2]"!]
                [!CALL "GPT_CG_GetGptPredefFreq","GtmClockRef" = "$ClockRef", "TimerModNo" = "$PrevPredefTimerModNo", "TickDurationUs" = "num:i($GptPredefTimerUs)", "OpnMode" = "num:i(0)"!][!//To calculate GTM frequency Fgtm
                [!CALL "GPT_CG_GetGptPredefExtraChConf","TickDurationUs" = "num:i($GptPredefTimerUs)"!][!//
                [!VAR "CtrlReg0" = "num:hextoint('0x00000800')"!][!//(Default value, where OSM=0 for continuous mode operation)
                [!/* Set Clock Source for the Timer Channel */!][!//
                [!VAR "CtrlReg0" = "bit:or($CtrlReg0,bit:shl($PredefClkId0,12))"!][!//
                [!/* Enable the channel trigger output. So that this channel trigger is used as the clock for the next channel*/!][!//
                [!VAR "CtrlReg0" = "bit:or($CtrlReg0,bit:shl(1,24))"!][!//
                [!VAR "CN0_Value0" = "num:i(0)"!][!//Clear CN0 register
                [!VAR "CM0_Value0" = "num:i($CM0_Calculated)"!][!// Load CM0 register with the value calculated from the macro GPT_CG_GetGtmGptPredefFreq
                [!VAR "SR0_Value0" = "num:i($CM0_Calculated)"!][!//
              [!ENDIF!]
              [!VAR "CtrlReg1" = "num:hextoint('0x00000800')"!][!//(Default value, where OSM=0 for continuous mode operation)
              [!IF "num:i($Extra_Channel) = num:i(1)"!][!// Need extra channel for frequency tuning
                [!/* Set Clock Source for Timer Channel -- select TRIG[x-1] as channel clock */!][!//
                [!VAR "CtrlReg1" = "bit:or($CtrlReg1,bit:shl(5,12))"!][!//
                [!/* Make ECLK_SRC=1 -- To enable Set2 selection in CLK_SRC_SR bit ( TRIG[x-1] as a clock source )*/!][!//
                [!VAR "CtrlReg1" = "bit:or($CtrlReg1,bit:shl(1,15))"!][!//
              [!ELSE!][!//Predef timer can directly get required clock from global clock Fgtm
                [!/* Set Clock Source for Timer Channel */!][!//
                [!VAR "CtrlReg1" = "bit:or($CtrlReg1,bit:shl($PredefClkId1,12))"!][!//
              [!ENDIF!][!//
              [!IF "(contains($GptPredefTimerType, '32')) or (contains($GptPredefTimerType, '24'))"!][!//
                [!/* Enable the channel trigger output. So that this channel trigger is used as the clock for the next channel to make 24 or 32 bit timer*/!][!//
                [!VAR "CtrlReg1" = "bit:or($CtrlReg1,bit:shl(1,24))"!][!//
              [!ENDIF!][!//
              [!VAR "CN0_Value1" = "num:i(0)"!][!// Clear CN0 register
              [!VAR "CM0_Value1" = "num:i(65535)"!][!// Set CM0 with the Maximum timer count value
              [!VAR "SR0_Value1" = "num:i(65535)"!][!//Set Shadow register also with the same CM0 Value, this is a safety measure to avoid unintended update from shadow registers
              [!VAR "NextPredefTimerModNo"= "num:i(0)"!]
              [!VAR "NextPredefTimerChNo"= "num:i(0)"!]
              [!IF "(contains($GptPredefTimerType, '32')) or (contains($GptPredefTimerType, '24'))"!][!// Reserving the extra channel for Concatenation
                [!VAR "NextPredefTimerModNo"= "text:split( text:split($NextPredefTimer, '_CHANNEL')[1], 'GTM_TOM')[1]"!]
                [!VAR "NextPredefTimerChNo"= "text:split($NextPredefTimer, '_CHANNEL')[2]"!]
                [!VAR "CtrlReg2" = "num:hextoint('0x00000800')"!][!//(Default value, where OSM=0 for continuous mode operation)
                [!/* Set Clock Source for Timer Channel -- select TRIG[x-1] as channel clock */!][!//
                [!VAR "CtrlReg2" = "bit:or($CtrlReg2,bit:shl(5,12))"!][!//
                [!/* Make ECLK_SRC=1 -- To enable Set2 selection in CLK_SRC_SR bit ( TRIG[x-1] as a clock source )*/!][!//
                [!VAR "CtrlReg2" = "bit:or($CtrlReg2,bit:shl(1,15))"!][!//
                [!VAR "CN0_Value2" = "num:i(0)"!][!// Clear CN0 register
                [!IF "(contains($GptPredefTimerType, '32'))"!][!//
                  [!VAR "CM0_Value2" = "num:i(65535)"!][!// Set CM0 with the Maximum timer count value
                  [!VAR "SR0_Value2" = "num:i(65535)"!][!//Set Shadow register also with the same CM0 Value, this is a safety measure to avoid unintended update from shadow registers
                [!ELSE!][!// 24 bit predef timer
                  [!VAR "CM0_Value2" = "num:i(255)"!][!// Set CM0 to its half, for cascade purpose to make 24 bit timer
                  [!VAR "SR0_Value2" = "num:i(255)"!][!//Set Shadow register also with the same CM0 Value, this is a safety measure to avoid unintended update from shadow registers
                [!ENDIF!][!//
              [!ENDIF!][!//
              [!/* [cover parentID={493E4AAC-698C-427e-8894-3D13EA16612C}] */!]
              [!/*  [/cover] */!]
              [!IF "contains(GptTimerChannelUsage, '1US_16BIT_ENABLED')"!][!//
                [!VAR "PredefTimer1" = "'GPT_PREDEF_TIMER_1US_16BIT'"!]
                [!VAR "PredefTimer2" = "'GPT_PREDEF_TIMER_1US_16BIT'"!]
                [!VAR "PredefTimer3" = "'GPT_PREDEF_TIMER_1US_16BIT'"!]
              [!ELSEIF "contains(GptTimerChannelUsage, '1US_16_24BIT_ENABLED')"!][!//
                [!VAR "PredefTimer1" = "'GPT_PREDEF_TIMER_1US_24BIT'"!]
                [!VAR "PredefTimer2" = "'GPT_PREDEF_TIMER_1US_16BIT'"!]
                [!VAR "PredefTimer3" = "'GPT_PREDEF_TIMER_1US_24BIT'"!]
              [!ELSEIF "contains(GptTimerChannelUsage, '1US_16_24_32BIT_ENABLED')"!][!//
                [!VAR "PredefTimer1" = "'GPT_PREDEF_TIMER_1US_32BIT'"!]
                [!VAR "PredefTimer2" = "'GPT_PREDEF_TIMER_1US_24BIT'"!]
                [!VAR "PredefTimer3" = "'GPT_PREDEF_TIMER_1US_16BIT'"!]
              [!ENDIF!][!//
              [!CODE!][!//
                [!AUTOSPACING!]
                [!INDENT "2"!]
                #if (GPT_PREDEF_EXTRA_CH_1US == STD_ON)
                {
                  [!INDENT "4"!]
                  MCU_GTM_TIMER_TOM, /* Timer Type (TOM/ATOM) */
                  [!"num:inttohex(bit:or(bit:shl($PrevPredefTimerModNo, num:i(8)),$PrevPredefTimerChNo))"!], /* Timer Number Module No | Timer Channel No */
                  [!"num:inttohex($CtrlReg0)"!]U, /* Channel Control Register */
                  [!"num:inttohex($CN0_Value0)"!]U, /* CN0 in ticks */
                  [!"num:inttohex($CM0_Value0)"!]U, /* CM0 in ticks */
                  [!"num:inttohex(num:i(0))"!]U, /* CM1 in ticks */
                  [!"num:inttohex($SR0_Value0)"!]U, /* SR0 in ticks */
                  [!"num:inttohex(num:i(0))"!]U, /* SR1 in ticks */
                  [!"num:inttohex(num:i(0))"!]U, /* Port Out     */
                  [!"num:inttohex($IntEnMode)"!]U /* Interrupt status and mode*/
                  [!ENDINDENT!]
                },
                #endif
                [!INDENT "2"!]
                {
                  [!INDENT "4"!]
                  MCU_GTM_TIMER_TOM, /* Timer Type (TOM/ATOM) */
                  [!"num:inttohex(bit:or(bit:shl($ActualPredefTimerModNo, num:i(8)),$ActualPredefTimerChNo))"!], /* Timer Number Module No | Timer Channel No */
                  [!"num:inttohex($CtrlReg1)"!]U, /* Channel Control Register */
                  [!"num:inttohex($CN0_Value1)"!]U, /* CN0 in ticks */
                  [!"num:inttohex($CM0_Value1)"!]U, /* CM0 in ticks */
                  [!"num:inttohex(num:i(0))"!]U, /* CM1 in ticks */
                  [!"num:inttohex($SR0_Value1)"!]U, /* SR0 in ticks */
                  [!"num:inttohex(num:i(0))"!]U, /* SR1 in ticks */
                  [!"num:inttohex(num:i(0))"!]U, /* Port Out     */
                  [!"num:inttohex($IntEnMode)"!]U /* Interrupt status and mode*/
                  [!ENDINDENT!]
                },
                [!ENDINDENT!]
                #if ((GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON) || \
                    (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
                {
                  [!INDENT "4"!]
                  MCU_GTM_TIMER_TOM, /* Timer Type (TOM/ATOM) */
                  [!"num:inttohex(bit:or(bit:shl($NextPredefTimerModNo, num:i(8)),$NextPredefTimerChNo))"!], /* Timer Number Module No | Timer Channel No */
                  [!"num:inttohex($CtrlReg2)"!]U, /* Channel Control Register */
                  [!"num:inttohex($CN0_Value2)"!]U, /* CN0 in ticks */
                  [!"num:inttohex($CM0_Value2)"!]U, /* CM0 in ticks */
                  [!"num:inttohex(num:i(0))"!]U, /* CM1 in ticks */
                  [!"num:inttohex($SR0_Value2)"!]U, /* SR0 in ticks */
                  [!"num:inttohex(num:i(0))"!]U, /* SR1 in ticks */
                  [!"num:inttohex(num:i(0))"!]U, /* Port Out     */
                  [!"num:inttohex($IntEnMode)"!]U /* Interrupt status and mode*/
                  [!ENDINDENT!]
                },
                #endif
                [!"$Extra_Channel"!], /* Is extra Channel for frequency tuning required */
                /* Types of Predef timers enabled : */
                [!"$PredefTimer1"!],
                [!"$PredefTimer2"!],
                [!"$PredefTimer3"!]
                [!ENDINDENT!]
              [!ENDCODE!][!//
          [!ENDSELECT!][!//
        [!ENDSELECT!][!//
      [!ENDIF!][!//
      [!CODE!]
        [!AUTOSPACING!]
        [!INDENT "0"!]
        };
        [!CR!]
        /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
           in generated code due to Autosar Naming constraints.*/
        /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
           in generated code due to Autosar Naming constraints.*/
        /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
           in generated code due to Autosar Naming constraints.*/
        /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
           in generated code due to Autosar Naming constraints.*/
        #define GPT_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"$GptCurrentCoreId"!]_UNSPECIFIED
        /* MISRA2012_RULE_20_1_JUSTIFICATION: File inclusion after pre-processor
           directives is allowed only for MemMap.h*/
        /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
           without safegaurd. It complies to Autosar guidelines. */
        #include "Gpt_MemMap.h"
        [!CR!][!//
        [!ENDINDENT!]
      [!ENDCODE!][!//
    [!ENDFOR!]
    [!CODE!]
      [!AUTOSPACING!]
      [!INDENT "0"!]
      #endif
      [!ENDINDENT!]
    [!ENDCODE!][!//

    [!/* 100us Predef Timer */!]
    [!CODE!]
      [!AUTOSPACING!]
      [!INDENT "0"!]
      [!CR!]
      #if (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON)
      [!ENDINDENT!]
    [!ENDCODE!][!//
    [!FOR "ConfigCoreIndex" = "num:i(1)" TO "num:i($MaxCoreConfigured)"!]
      [!VAR "GptCurrentCoreId" = "substring-after(text:split($CGCoreUsed, ',')[num:i($ConfigCoreIndex)], 'CORE')"!]
      [!CODE!]
      [!AUTOSPACING!]
      [!INDENT "0"!]
      [!CR!]
      /* Memory Mapping the configuration constant */
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
         in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
         in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
         in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
         in generated code due to Autosar Naming constraints.*/
      #define GPT_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"$GptCurrentCoreId"!]_UNSPECIFIED
      /* MISRA2012_RULE_20_1_JUSTIFICATION: File inclusion after pre-processor
         directives is allowed only for MemMap.h*/
      /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
         without safegaurd. It complies to Autosar guidelines. */
      #include "Gpt_MemMap.h"
      [!CR!]
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
         in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
         in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
         in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
         in generated code due to Autosar Naming constraints.*/[!//
      [!/* [cover parentID={F78A1026-E30F-4281-B98B-A5C4BC2A6AF5}] */!][!//
      [!/*  [/cover] */!]
      static const Gpt_100UsPredefTimerChannelConfigType \
                                      Gpt_k100UsPredefTimerChannelConfig_Core[!"$GptCurrentCoreId"!] =
      {
      [!ENDINDENT!]
      [!ENDCODE!][!//
      [!IF "$Is100usPredefChannelAvailable = 'true'"!]
        [!/*
          Set period, duty match timer interrupt and interrupt mode
          By default interrupts are disabled  and Level mode is selected
        */!][!//
        [!VAR "IntEnMode" = "num:i(0)"!][!//
        [!VAR "ChannelId" = "$Gpt100usPredefTimerChannelId + num:i(1)"!]
        [!SELECT "as:modconf('Gpt')[1]/GptChannelConfigSet/GptChannelConfiguration"!]
          [!SELECT "./*[GptChannelId = num:i($ChannelId) - num:i(1)]"!][!//
          [!VAR "GptPredefTimerType" = "node:value(GptTimerChannelUsage)"!]
          [!IF "contains(GptTimerChannelUsage,'_100US_')"!][!//
            [!SELECT "as:modconf('Gpt')[1]/GptDriverConfiguration/GptClockReferencePoint/*[1]"!][!//
              [!VAR "ClockRef" = "GptClockReference"!][!//
            [!ENDSELECT!][!//
            [!VAR "GptPredefTimerUs" = "text:split($GptPredefTimerType,'TIMERCH_')[2]"!][!//
            [!VAR "GptPredefTimerUs" = "text:split($GptPredefTimerUs,'US_')[1]"!][!//
            [!VAR "CtrlReg2" = "num:i(0)"!]
            [!VAR "CN0_Value0" = "num:i(0)"!]
            [!VAR "CN0_Value2" = "num:i(0)"!]
            [!VAR "CM0_Value0" = "num:i(0)"!]
            [!VAR "CM0_Value2" = "num:i(0)"!]
            [!VAR "SR0_Value0" = "num:i(0)"!]
            [!VAR "SR0_Value2" = "num:i(0)"!]
            [!VAR "CtrlReg0" = "num:i(0)"!]
            [!/* Get the Gtm Configuration which acts as the actual Predef Timer */!]
            [!CALL "GPT_CG_GetPredefTimerInfo", "Channel" = "$ChannelId"!]
            [!VAR "ActualPredefTimerModNo"= "text:split( text:split($ActualPredefTimer, '_CHANNEL')[1], 'GTM_TOM')[1]"!]
            [!VAR "ActualPredefTimerChNo"= "text:split($ActualPredefTimer, '_CHANNEL')[2]"!]
            [!CALL "GPT_CG_GetGptPredefFreq","GtmClockRef" = "$ClockRef", "TimerModNo" = "$ActualPredefTimerModNo", "TickDurationUs" = "num:i($GptPredefTimerUs)", "OpnMode" = "num:i(1)"!][!//To check if an extra channel is needed for predef timer implementation
            [!VAR "PrevPredefTimerModNo"= "num:i(0)"!]
            [!VAR "PrevPredefTimerChNo"= "num:i(0)"!]
            [!IF "num:i($Extra_Channel) = num:i(1)"!][!// Need an extra channel for frequency tuning
              [!VAR "PrevPredefTimerModNo"= "text:split( text:split($PreviousPredefTimer, '_CHANNEL')[1], 'GTM_TOM')[1]"!]
              [!VAR "PrevPredefTimerChNo"= "text:split($PreviousPredefTimer, '_CHANNEL')[2]"!]
              [!CALL "GPT_CG_GetGptPredefFreq","GtmClockRef" = "$ClockRef", "TimerModNo" = "$PrevPredefTimerModNo", "TickDurationUs" = "num:i($GptPredefTimerUs)", "OpnMode" = "num:i(0)"!][!//To calculate GTM frequency Fgtm
              [!CALL "GPT_CG_GetGptPredefExtraChConf","TickDurationUs" = "num:i($GptPredefTimerUs)"!][!//
              [!VAR "CtrlReg0" = "num:hextoint('0x00000800')"!][!//(Default value, where OSM=0 for continuous mode operation)
              [!/* Set Clock Source for the Timer Channel */!][!//
              [!VAR "CtrlReg0" = "bit:or($CtrlReg0,bit:shl($PredefClkId0,12))"!][!//
              [!/* Enable the channel trigger output. So that this channel trigger is used as the clock for the next channel*/!][!//
              [!VAR "CtrlReg0" = "bit:or($CtrlReg0,bit:shl(1,24))"!][!//
              [!VAR "CN0_Value0" = "num:i(0)"!][!//Clear CN0 register
              [!VAR "CM0_Value0" = "num:i($CM0_Calculated)"!][!// Load CM0 register with the value calculated from the macro GPT_CG_GetGtmGptPredefFreq
              [!VAR "SR0_Value0" = "num:i($CM0_Calculated)"!][!//
            [!ENDIF!]
            [!VAR "CtrlReg1" = "num:hextoint('0x00000800')"!][!//(Default value, where OSM=0 for continuous mode operation)
            [!IF "num:i($Extra_Channel) = num:i(1)"!][!// Need extra channel for frequency tuning
              [!/* Set Clock Source for Timer Channel -- select TRIG[x-1] as channel clock */!][!//
              [!VAR "CtrlReg1" = "bit:or($CtrlReg1,bit:shl(5,12))"!][!//
              [!/* Make ECLK_SRC=1 -- To enable Set2 selection in CLK_SRC_SR bit ( TRIG[x-1] as a clock source )*/!][!//
              [!VAR "CtrlReg1" = "bit:or($CtrlReg1,bit:shl(1,15))"!][!//
            [!ELSE!][!//Predef timer can directly get required clock from global clock Fgtm
              [!/* Set Clock Source for Timer Channel */!][!//
              [!VAR "CtrlReg1" = "bit:or($CtrlReg1,bit:shl($PredefClkId1,12))"!][!//
            [!ENDIF!]
            [!/* Enable the channel trigger output. So that this channel trigger is used as the clock for the next channel to make a 32 bit timer*/!][!//
            [!VAR "CtrlReg1" = "bit:or($CtrlReg1,bit:shl(1,24))"!][!//
            [!VAR "CN0_Value1" = "num:i(0)"!][!// Clear CN0 register
            [!VAR "CM0_Value1" = "num:i(65535)"!][!// Set CM0 with the Maximum timer count value
            [!VAR "SR0_Value1" = "num:i(65535)"!][!//Set Shadow register also with the same CM0 Value, this is a safety measure to avoid unintended update from shadow registers
            [!VAR "NextPredefTimerModNo"= "text:split( text:split($NextPredefTimer, '_CHANNEL')[1], 'GTM_TOM')[1]"!]
            [!VAR "NextPredefTimerChNo"= "text:split($NextPredefTimer, '_CHANNEL')[2]"!]
            [!VAR "CtrlReg2" = "num:hextoint('0x00000800')"!][!//(Default value, where OSM=0 for continuous mode operation)
            [!/* Set Clock Source for Timer Channel -- select TRIG[x-1] as channel clock */!][!//
            [!VAR "CtrlReg2" = "bit:or($CtrlReg2,bit:shl(5,12))"!][!//
            [!/* Make ECLK_SRC=1 -- To enable Set2 selection in CLK_SRC_SR bit ( TRIG[x-1] as a clock source )*/!][!//
            [!VAR "CtrlReg2" = "bit:or($CtrlReg2,bit:shl(1,15))"!][!//
            [!VAR "CN0_Value2" = "num:i(0)"!][!// Clear CN0 register
            [!VAR "CM0_Value2" = "num:i(65535)"!][!// Set CM0 with the Maximum timer count value
            [!VAR "SR0_Value2" = "num:i(65535)"!][!//Set Shadow register also with the same CM0 Value, this is a safety measure to avoid unintended update from shadow registers
            [!CODE!][!//
              [!AUTOSPACING!]
              [!INDENT "2"!]
              #if (GPT_PREDEF_EXTRA_CH_100US == STD_ON)
              {
                [!INDENT "4"!]
                MCU_GTM_TIMER_TOM, /* Timer Type (TOM/ATOM) */
                [!"num:inttohex(bit:or(bit:shl($PrevPredefTimerModNo, num:i(8)),$PrevPredefTimerChNo))"!], /* Timer Number Module No | Timer Channel No */
                [!"num:inttohex($CtrlReg0)"!]U, /* Channel Control Register */
                [!"num:inttohex($CN0_Value0)"!]U, /* CN0 in ticks */
                [!"num:inttohex($CM0_Value0)"!]U, /* CM0 in ticks */
                [!"num:inttohex(num:i(0))"!]U, /* CM1 in ticks */
                [!"num:inttohex($SR0_Value0)"!]U, /* SR0 in ticks */
                [!"num:inttohex(num:i(0))"!]U, /* SR1 in ticks */
                [!"num:inttohex(num:i(0))"!]U, /* Port Out     */
                [!"num:inttohex($IntEnMode)"!]U /* Interrupt status and mode*/
                [!ENDINDENT!]
              },
              #endif
              {
                [!INDENT "4"!]
                MCU_GTM_TIMER_TOM, /* Timer Type (TOM/ATOM) */
                [!"num:inttohex(bit:or(bit:shl($ActualPredefTimerModNo, num:i(8)),$ActualPredefTimerChNo))"!], /* Timer Number Module No | Timer Channel No */
                [!"num:inttohex($CtrlReg1)"!]U, /* Channel Control Register */
                [!"num:inttohex($CN0_Value1)"!]U, /* CN0 in ticks */
                [!"num:inttohex($CM0_Value1)"!]U, /* CM0 in ticks */
                [!"num:inttohex(num:i(0))"!]U, /* CM1 in ticks */
                [!"num:inttohex($SR0_Value1)"!]U, /* SR0 in ticks */
                [!"num:inttohex(num:i(0))"!]U, /* SR1 in ticks */
                [!"num:inttohex(num:i(0))"!]U, /* Port Out     */
                [!"num:inttohex($IntEnMode)"!]U /* Interrupt status and mode*/
                [!ENDINDENT!]
              },
              {
                [!INDENT "4"!]
                MCU_GTM_TIMER_TOM, /* Timer Type (TOM/ATOM) */
                [!"num:inttohex(bit:or(bit:shl($NextPredefTimerModNo, num:i(8)),$NextPredefTimerChNo))"!], /* Timer Number Module No | Timer Channel No */
                [!"num:inttohex($CtrlReg2)"!]U,   /* Channel Control Register */
                [!"num:inttohex($CN0_Value2)"!]U, /* CN0 in ticks */
                [!"num:inttohex($CM0_Value2)"!]U, /* CM0 in ticks */
                [!"num:inttohex(num:i(0))"!]U, /* CM1 in ticks */
                [!"num:inttohex($SR0_Value2)"!]U, /* SR0 in ticks */
                [!"num:inttohex(num:i(0))"!]U, /* SR1 in ticks */
                [!"num:inttohex(num:i(0))"!]U, /* Port Out     */
                [!"num:inttohex($IntEnMode)"!]U /* Interrupt status and mode*/
                [!ENDINDENT!]
              },
              [!"$Extra_Channel"!], /* Is extra Channel for frequency tuning required */
              /* Type of the Predef timer enabled : */
              GPT_PREDEF_TIMER_100US_32BIT
              [!ENDINDENT!]
            [!ENDCODE!][!//
          [!ENDIF!][!//
      [!ENDSELECT!][!//
        [!ENDSELECT!][!//
      [!ENDIF!]
      [!CODE!][!//
      [!AUTOSPACING!]
      [!INDENT "0"!]
      };
      [!CR!][!//
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
         in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
         in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
         in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
         in generated code due to Autosar Naming constraints.*/
      #define GPT_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"$GptCurrentCoreId"!]_UNSPECIFIED
      /* MISRA2012_RULE_20_1_JUSTIFICATION: File inclusion after pre-processor
         directives is allowed only for MemMap.h*/
      /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
         without safegaurd. It complies to Autosar guidelines. */
      #include "Gpt_MemMap.h"
      [!CR!]
      [!ENDINDENT!]
      [!ENDCODE!][!//
    [!ENDFOR!]
    [!CODE!]
      [!AUTOSPACING!]
      [!INDENT "0"!]
      #endif
      [!CR!][!//
      [!ENDINDENT!]
    [!ENDCODE!][!//
  [!ENDIF!]

[!/* GPT_CR_016: GptEnableDisableNotificationApi is Significant only if
     GptNotification for any one of the channels is not NULL
*/!][!//
[!SELECT "as:modconf('Gpt')[1]"!]
  [!VAR "NotifApi" = "GptConfigurationOfOptApiServices/GptEnableDisableNotificationApi"!][!//
  [!VAR "InitialVal" = "num:i(0)"!][!//
  [!SELECT "./GptChannelConfigSet"!][!//
    [!VAR "TotalGptChannel" = "num:i(count(GptChannelConfiguration/*))"!][!//
    [!LOOP "./GptChannelConfiguration/*"!][!//
      [!IF "node:empty(GptNotification/*[1])"!][!//
        [!VAR "Notification" = "'NULL_PTR'"!][!//
        [!VAR "InitialVal" = "$InitialVal + 1"!][!//
        [!VAR "InitialVal" = "num:i($InitialVal)"!][!//
      [!ELSE!][!//
        [!VAR "Notification" = "./GptNotification/*[1]"!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//[!LOOP "./GptChannelConfiguration/*"!][!//
  [!ENDSELECT!][!//
[!ENDSELECT!][!//
[!VAR "TotalGptChannel" = "num:i($TotalGptChannel)"!][!//
[!IF "$InitialVal = $TotalGptChannel and $NotifApi = 'true' "!][!//
  [!IF "not($InitialVal != $TotalGptChannel and $NotifApi = 'false')"!][!//
    [!ERROR!][!//
      [!AUTOSPACING!]
      [!INDENT "0"!]
      ERROR: Wrong configuration. None of the channel contain valid Notification function name then GptEnableDisableNotificationApi should be false.
      [!ENDINDENT!]
    [!ENDERROR!][!//
  [!ENDIF!][!//
[!ELSEIF "$InitialVal != $TotalGptChannel and $NotifApi = 'false'"!][!//
  [!IF "$NotifApi != 'true'"!][!//
    [!ERROR!][!//
      [!AUTOSPACING!]
      [!INDENT "0"!]
      ERROR: Wrong configuration. if Any one channel has valid Notification function name, then GptEnableDisableNotificationApi should be true.
      [!ENDINDENT!]
    [!ENDERROR!][!//
  [!ENDIF!][!//
[!ENDIF!][!//

[!/* Driver Configuration for each Core */!]
[!CODE!][!//
/*
  Configuration: Gpt Driver Configuration for each Core
*/
[!ENDCODE!][!//
[!FOR "ConfigCoreIndex" = "num:i(1)" TO "num:i($MaxCoreConfigured)"!][!//
  [!VAR "GptCurrentCoreId" = "substring-after(text:split($CGCoreUsed, ',')[num:i($ConfigCoreIndex)], 'CORE')"!]
  [!CODE!][!//
  [!AUTOSPACING!]
  [!INDENT "0"!]
  [!CR!]
  /* Memory Mapping the configuration constant */
  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
     in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
     in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
     in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
     in generated code due to Autosar Naming constraints.*/
  #define GPT_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"$GptCurrentCoreId"!]_UNSPECIFIED
  /*MISRA2012_RULE_20_1_JUSTIFICATION: File inclusion after pre-processor
    directives is allowed only for MemMap.h*/
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
     without safegaurd. It complies to Autosar guidelines. */
  #include "Gpt_MemMap.h"
  [!CR!]
  [!/* [cover parentID={36A31DAA-8C57-44d5-8065-7AD59285D1C3}] */!][!//
  [!/*  [/cover] */!][!//
  static const Gpt_CoreConfigType Gpt_kConfig_Core[!"$GptCurrentCoreId"!] =
  {
  [!ENDINDENT!]
  [!ENDCODE!][!//

  [!/* Fetch Normal and Predef Channel count */!]
  [!CALL "GPT_CG_GptCoreChannelInfo", "GptCoreId" = "$GptCurrentCoreId"!]
  [!VAR "MaxNormalChannles" = "num:i(0)"!]
  [!IF "$MaxChannelMappedToCore - $MaxPredefChannelMappedToCore > 0"!][!//
      [!VAR "MaxNormalChannles" = "num:i($MaxChannelMappedToCore - $MaxPredefChannelMappedToCore)"!]
      [!IF "$MaxCoreConfigured > num:i(1)"!]
        [!CODE!][!//
        [!AUTOSPACING!]
        [!INDENT "2"!]
        /* Pointer to Channels allocated to Core [!"$GptCurrentCoreId"!] */
        Gpt_ChannelIndex_Core[!"$GptCurrentCoreId"!],
        [!ENDINDENT!]
        [!ENDCODE!][!//
        [!CR!]
      [!ENDIF!]
      [!CODE!][!//
      [!AUTOSPACING!]
      [!INDENT "2"!]
      [!/* [cover parentID={36ABE364-B6CE-44b8-832A-CF244B7E87FE}] */!][!//
      [!/*  [/cover] */!][!//
      /* Pointer to channel configuration of Core[!"$GptCurrentCoreId"!] */
      Gpt_kChannelConfig_Core[!"$GptCurrentCoreId"!],
      [!ENDINDENT!]
      [!ENDCODE!][!//
  [!ELSE!][!//
      [!IF "$MaxCoreConfigured > num:i(1)"!]
        [!CODE!][!//
        [!AUTOSPACING!]
        [!INDENT "2"!]
        /* Pointer to Channels allocated to Core [!"$GptCurrentCoreId"!] */
        NULL_PTR,
        [!ENDINDENT!]
        [!ENDCODE!][!//
        [!CR!]
      [!ENDIF!]
      [!CODE!][!//
      [!AUTOSPACING!]
      [!INDENT "2"!]
      /* Pointer to channel configuration of Core[!"$GptCurrentCoreId"!] */
      NULL_PTR,
      [!ENDINDENT!]
      [!ENDCODE!][!//
  [!ENDIF!][!//
  [!CODE!]
  [!CR!]
  [!AUTOSPACING!]
  [!INDENT "2"!]
  /* Channel configerd for 1us Predef Timer in Core [!"$GptCurrentCoreId"!] */
  #if ((GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON)    || \
      (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)    || \
      (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
  &Gpt_k1UsPredefTimerChannelConfig_Core[!"$GptCurrentCoreId"!],
  #endif

  /* Channel configerd for 100us Predef Timer in Core [!"$GptCurrentCoreId"!] */
  #if (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON)
  &Gpt_k100UsPredefTimerChannelConfig_Core[!"$GptCurrentCoreId"!],
  #endif

  /* Maximum Normal Channels allocated to core [!"$GptCurrentCoreId"!] */
  GPT_MAX_CHANNELS_CORE[!"num:i($GptCurrentCoreId)"!]
  [!ENDINDENT!]
  [!INDENT "0"!]
  };
  [!CR!][!//
  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
     in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
     in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
     in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
     in generated code due to Autosar Naming constraints.*/
  #define GPT_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"$GptCurrentCoreId"!]_UNSPECIFIED
  /* MISRA2012_RULE_20_1_JUSTIFICATION: File inclusion after pre-processor
     directives is allowed only for MemMap.h*/
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
     without safegaurd. It complies to Autosar guidelines. */
  #include "Gpt_MemMap.h"
  [!CR!]
  [!ENDINDENT!]
  [!ENDCODE!][!//
[!ENDFOR!][!//

[!/* Gpt_ConfigType structure */!]
[!VAR "MaxCoreCount" = "num:i(ecu:get('Mcu.NoOfCoreAvailable'))"!]
[!CODE!][!//
/* Memory Mapping the configuration constant */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
#define GPT_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: File inclusion after pre-processor
   directives is allowed only for MemMap.h*/
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"
[!CR!]
/*
  Configuration: Configuration
  Definition of Gpt_ConfigType structure
*/
/* MISRA2012_RULE_8_7_JUSTIFICATION: Module configuration data structure
   declaration as per Autosar guidelines. This data structure may be needed
   by SW units using Gpt Driver APIs */
/* MISRA2012_RULE_8_4_JUSTIFICATION: Definition is as per Autosar guidelines */[!//
[!/* [cover parentID={6972F238-1F46-4fd3-AFFD-26C55C647316}] */!][!//
[!/*  [/cover] */!]
const Gpt_ConfigType Gpt_Config[!"$PredefinedVarName"!] =
{
  /* Pointer to Gpt Core Specific Config Set */
  [!AUTOSPACING!]
  [!INDENT "2"!]
  {
  [!ENDINDENT!]
[!ENDCODE!][!//
[!FOR "ConfigCoreIndex" = "num:i(0)" TO "num:i($MaxCoreCount - 1)"!][!//
  [!VAR "currCore" = "concat('CORE', $ConfigCoreIndex)"!]
  [!IF "(text:contains(text:split($CGCoreUsed, ','), $currCore))"!]
    [!CODE!][!//
      [!AUTOSPACING!]
      [!INDENT "4"!]
      &Gpt_kConfig_Core[!"$ConfigCoreIndex"!], /* CORE [!"$ConfigCoreIndex"!] */
      [!ENDINDENT!]
    [!ENDCODE!][!//
  [!ELSE!]
    [!CODE!][!//
      [!AUTOSPACING!]
      [!INDENT "4"!]
      NULL_PTR,           /* CORE [!"$ConfigCoreIndex"!] */
      [!ENDINDENT!]
    [!ENDCODE!][!//
  [!ENDIF!]
[!ENDFOR!][!//
[!CODE!][!//
  [!AUTOSPACING!]
  [!INDENT "2"!]
  }
  [!ENDINDENT!]
};
[!CR!]
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
#define GPT_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: File inclusion after pre-processor
directives is allowed only for MemMap.h*/
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"
[!CR!]
[!ENDCODE!][!//

[!CODE!][!// Template
[!CR!][!//
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
**                      Global Function Definitions                           **
*******************************************************************************/


/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
/* End Of File */
[!ENDCODE!][!//
[!ENDNOCODE!][!//
