[!/*
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
**  FILENAME  : Gpt.m                                                         **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE      : 2018-04-09                                                    **
**                                                                            **
**  BSW MODULE DESCRIPTION : Gpt.bmd                                          **
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
**  DESCRIPTION  : Code template macro file for Gpt Driver                    **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Gpt Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
*/!]
/* [cover parentID={BD2B7307-D05B-4f74-971D-609CB156A1D9}]
[/cover] */

[!//
[!/* *** multiple inclusion protection*** */!][!//
[!IF "not(var:defined('GPT_M'))"!][!//
[!VAR "GPT_M"="'true'"!][!//
[!AUTOSPACING!]
[!INDENT "0"!]

/*******************************************************************************
** Name           : GPT_CG_ConfigSwitch                                       **
**                                                                            **
** Description    : This macro generates configuration switch Values          **
**                  STD_ON/STD_OFF based on configuration true/false          **
**                                                                            **
*******************************************************************************/
[!MACRO "GPT_CG_ConfigSwitch", "nodeval" = ""!][!//
[!//
[!IF "$nodeval = 'true'"!][!//
(STD_ON)[!//
[!ELSE!][!//
(STD_OFF)[!//
[!ENDIF!]
[!ENDMACRO!]

/*******************************************************************************
** Name           : GPT_CG_GetGTMChannelParam                                 **
**                                                                            **
** Description    : This macro accepts the string configured for              **
**                  the parameter GtmTimerUsed and reutrns                    **
**                  the Timer type (ATOM / TOM),                              **
**                  Timer module number and Timer Channel Number.             **
**                                                                            **
*******************************************************************************/
[!MACRO "GPT_CG_GetGTMChannelParam","GtmTimerString" = ""!][!//
[!NOCODE!]

[!VAR "GtmTimerString" = "text:split($GtmTimerString,'McuGtmAllocationConf')[2]"!][!//
[!VAR "GtmTimerType" = "text:split($GtmTimerString,'AllocationConf')[1]"!][!//
[!VAR "GtmTimerType" = "text:toupper(text:split($GtmTimerType,'McuGtm')[2])"!][!//

[!VAR "GtmTimerModNo" = "text:split($GtmTimerString,'/')[2]"!][!//
[!VAR "GtmTimerModNo" = "text:split($GtmTimerModNo,'_')[2]"!][!//

[!VAR "GtmTimerChNo" = "text:split($GtmTimerString,'/')[3]"!][!//
[!VAR "GtmTimerChNo" = "text:split($GtmTimerChNo,'_')[2]"!][!//

[!VAR "GlobalChannelNumber" = "concat('GTM_',text:toupper($GtmTimerType),$GtmTimerModNo,'_CHANNEL',$GtmTimerChNo,'')"!][!//

[!ENDNOCODE!]
[!ENDMACRO!]

/*******************************************************************************
** Name           : GPT_CG_GetPredefTimerInfo                                 **
**                                                                            **
** Description    : This macro iterates over                                  **
**                  GtmTimerOutputModuleConfigurations and identifies the     **
**                  Nth channel among (N-1), N and (N+1)                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={50DF2451-BCE1-4b83-87C5-B5A8B9F466F0} ]   **
**                                                                            **
*******************************************************************************/
[!MACRO "GPT_CG_GetPredefTimerInfo", "Channel" = ""!][!//
[!NOCODE!]
[!VAR "PreviousPredefTimer" = "''"!]
[!VAR "ActualPredefTimer" = "''"!]
[!VAR "NextPredefTimer" = "''"!]
[!VAR "TimerModNoList" = "''"!]
[!VAR "GtmTimerChList" = "''"!]
[!VAR "GtmFactorTimerChList" = "''"!]
[!VAR "GtmTimerChSum" = "num:i(0)"!]
[!SELECT "as:modconf('Gpt')[1]/GptDriverConfiguration/GptClockReferencePoint/*[1]"!][!//
  [!VAR "ClockRef" = "GptClockReference"!][!//
[!ENDSELECT!][!//
[!SELECT "as:modconf('Gpt')[1]/GptChannelConfigSet/GptChannelConfiguration"!][!//
  [!SELECT "./*[GptChannelId = num:i($Channel) - num:i(1)]"!][!//
    [!VAR "GptPredefTimerType" = "node:value(GptTimerChannelUsage)"!]
    [!VAR "GptPredefTimerUs" = "text:split($GptPredefTimerType,'TIMERCH_')[2]"!][!//
    [!VAR "GptPredefTimerUs" = "text:split($GptPredefTimerUs,'US_')[1]"!][!//
    [!SELECT "./GtmTimerOutputModuleConfiguration/*"!][!//
      [!CALL "GPT_CG_GetGTMChannelParam","GtmTimerString" = "GtmTimerUsed"!][!//
      [!IF "($GtmTimerType != 'TOM')"!][!//
        [!ERROR!][!//
          Config Error: GPT Predef Timers shall use GTM TOM Channels only. Change selection under : [!"node:path(./GtmTimerUsed)"!].
        [!ENDERROR!][!//
      [!ENDIF!][!//
      [!IF "not(contains(text:split($TimerModNoList),$GtmTimerModNo))"!]
        [!VAR "TimerModNoList" = "concat($TimerModNoList, $GtmTimerModNo, ',')"!]
      [!ENDIF!]
      [!VAR "factor" = "num:i(($GtmTimerModNo + 1) * 16)"!]
      [!VAR "GtmTimerChList" = "concat($GtmTimerChList, num:i($GtmTimerChNo + $factor), ',')"!]
      [!VAR "GtmFactorTimerChList" = "concat($GtmFactorTimerChList, 'CHANNEL', num:i($GtmTimerChNo + $factor), '#_', $factor,',')"!]
    [!ENDSELECT!]
    [!/* Validate the configured Gtm Timers */!]
    [!VAR "GtmConfigCount" = "num:i(count(./GtmTimerOutputModuleConfiguration/*))"!]
    [!VAR "MinChNo" = "num:min(text:split($GtmTimerChList, ','))"!]
    [!VAR "MaxChNo" = "num:max(text:split($GtmTimerChList, ','))"!]
    [!VAR "MaxChPattern" = "concat( 'CHANNEL', num:i($MaxChNo) )"!]
    [!VAR "MinChPattern" = "concat( 'CHANNEL', num:i($MinChNo) )"!]
    [!VAR "fetchMinCh" = "concat( '^', $MinChPattern, '#.*$' )"!]
    [!VAR "fetchMaxCh" = "concat( '^', $MaxChPattern, '#.*$' )"!]
    [!VAR "MinChFactor" = "translate(text:grep(text:split($GtmFactorTimerChList, ','), $fetchMinCh), '[]', '')"!]
    [!VAR "MinChFactor" = "text:split($MinChFactor, '_')[2]"!]
    [!VAR "MinChModNo"  = "num:i(($MinChFactor div 16) - 1)"!]
    [!VAR "MaxChFactor" = "translate(text:grep(text:split($GtmFactorTimerChList, ','), $fetchMaxCh), '[]', '')"!]
    [!VAR "MaxChFactor" = "text:split($MaxChFactor, '_')[2]"!]
    [!VAR "MaxChModNo"  = "num:i(($MaxChFactor div 16) - 1)"!]
    [!IF "$GtmConfigCount = num:i(2) and num:i($MaxChNo - $MinChNo) != num:i(1)"!]
      [!ERROR!][!//
        ERROR: The GTM Timer channels must be continuous number.
      [!ENDERROR!][!//
    [!ELSEIF "$GtmConfigCount = num:i(3) and num:i($MaxChNo - $MinChNo) != num:i(2)"!]
      [!ERROR!][!//
        ERROR: The GTM Timer channels must be continuous number.
      [!ENDERROR!][!//
    [!ELSE!]
        [!IF "$GtmConfigCount = num:i(1)"!]
          [!VAR "BasePredefChannel" = "$MinChNo - $MinChFactor"!]
          [!VAR "BasePredefChannelModNo" = "$MinChModNo"!]
          [!IF "$BasePredefChannel = 0"!]
            [!CALL "GPT_CG_GetGptPredefFreq","GtmClockRef" = "$ClockRef", "TimerModNo" = "$BasePredefChannelModNo", "TickDurationUs" = "num:i($GptPredefTimerUs)", "OpnMode" = "num:i(1)"!]
            [!IF "num:i($Extra_Channel) = num:i(1) and ($BasePredefChannelModNo - 1) < 0 "!]
                [!ERROR!][!//
                  ERROR : The channel referenced by 'GtmTimerUsed' under configuration [!"node:name(.)"!]
                  cannot support a predef timer, as its the first channel in this TOM slice which requires an extra channel (immediate previous) to make the required predef timer frequency. Change the channel selection.
                [!ENDERROR!][!//
            [!ELSE!]
                [!VAR "PreviousPredefTimer" = "concat('GTM_TOM', ($BasePredefChannelModNo - 1) , '_CHANNEL',num:i(15),'')"!]
            [!ENDIF!]
          [!ELSE!]
            [!VAR "PreviousPredefTimer" = "concat('GTM_TOM', $BasePredefChannelModNo , '_CHANNEL',num:i($BasePredefChannel - 1),'')"!]
          [!ENDIF!]
          [!VAR "ActualPredefTimer" = "concat('GTM_TOM',$BasePredefChannelModNo,'_CHANNEL',num:i($BasePredefChannel),'')"!]
          [!VAR "NextPredefTimer"   = "''"!]
        [!ELSEIF "$GtmConfigCount = num:i(2)"!]
          [!VAR "BasePredefChannel" = "$MinChNo - $MinChFactor"!]
          [!VAR "BasePredefChannelModNo" = "$MinChModNo"!]
          [!VAR "CascadingPredefChannel" = "$MaxChNo - $MaxChFactor"!]
          [!VAR "CascadingPredefChannelModNo" = "$MaxChModNo"!]
          [!CALL "GPT_CG_GetGptPredefFreq","GtmClockRef" = "$ClockRef", "TimerModNo" = "$BasePredefChannelModNo", "TickDurationUs" = "num:i($GptPredefTimerUs)", "OpnMode" = "num:i(1)"!]
          [!IF "num:i($Extra_Channel) = num:i(1)"!]
            [!IF "contains(GptTimerChannelUsage, '32') or contains(GptTimerChannelUsage, '24')"!]
              [!IF "$BasePredefChannel = 0 and ($BasePredefChannelModNo - 1) < 0"!]
                [!ERROR!][!//
                  ERROR : The channel referenced by 'GtmTimerUsed' under configuration [!"node:name(.)"!]
                  cannot support a predef timer, as its the first channel in this TOM slice which requires an extra channel (immediate previous) to make the required predef timer frequency. Change the channel selection.
                [!ENDERROR!][!//
              [!ELSE!]
                [!IF "$BasePredefChannel = 0"!]
                  [!VAR "PreviousPredefTimer" = "concat('GTM_TOM', $BasePredefChannelModNo - 1 , '_CHANNEL',num:i(15),'')"!][!//
                [!ELSE!]
                  [!VAR "PreviousPredefTimer" = "concat('GTM_TOM', $BasePredefChannelModNo, '_CHANNEL',num:i($BasePredefChannel - 1),'')"!][!//
                [!ENDIF!]
                [!VAR "ActualPredefTimer"   = "concat('GTM_TOM', $BasePredefChannelModNo,'_CHANNEL',num:i($BasePredefChannel),'')"!][!//
                [!VAR "NextPredefTimer"     = "concat('GTM_TOM', $CascadingPredefChannelModNo,'_CHANNEL',num:i($CascadingPredefChannel),'')"!]
              [!ENDIF!]
            [!ELSE!]
              [!VAR "PreviousPredefTimer" = "concat('GTM_TOM', $BasePredefChannelModNo , '_CHANNEL',num:i($BasePredefChannel),'')"!][!//
              [!VAR "ActualPredefTimer"   = "concat('GTM_TOM', $CascadingPredefChannelModNo,'_CHANNEL',num:i($CascadingPredefChannel),'')"!][!//
            [!ENDIF!]
          [!ELSE!]
            [!IF "contains(GptTimerChannelUsage, '32') or contains(GptTimerChannelUsage, '24')"!]
              [!VAR "PreviousPredefTimer" = "''"!][!//
              [!VAR "ActualPredefTimer" = "concat('GTM_TOM', $BasePredefChannelModNo,'_CHANNEL',num:i($BasePredefChannel),'')"!][!//
              [!VAR "NextPredefTimer" = "concat('GTM_TOM', $CascadingPredefChannelModNo , '_CHANNEL',num:i($CascadingPredefChannel),'')"!][!//
            [!ELSE!]
              [!VAR "PreviousPredefTimer" = "''"!][!//
              [!VAR "ActualPredefTimer" = "concat('GTM_TOM', $BasePredefChannelModNo,'_CHANNEL',num:i($BasePredefChannel),'')"!][!//
            [!ENDIF!]
          [!ENDIF!]
        [!ELSEIF "$GtmConfigCount = num:i(3)"!]
          [!VAR "BasePredefChannel" = "$MinChNo - $MinChFactor"!]
          [!VAR "BasePredefChannelModNo" = "$MinChModNo"!]
          [!VAR "CascadingPredefChannel" = "$MaxChNo - $MaxChFactor"!]
          [!VAR "CascadingPredefChannelModNo" = "$MaxChModNo"!]
          [!VAR "GtmTimerChList" = "num:order(text:split($GtmTimerChList, ','))"!]
          [!VAR "MiddleChNo" = "num:i(text:split($GtmTimerChList, ',')[2])"!]
          [!VAR "MiddleChPattern" = "concat( 'CHANNEL', num:i($MiddleChNo) )"!]
          [!VAR "fetchMiddleCh" = "concat( '^', $MiddleChPattern, '#.*$' )"!]
          [!VAR "MiddleChFactor" = "translate(text:grep(text:split($GtmFactorTimerChList, ','), $fetchMiddleCh), '[]', '')"!]
          [!VAR "MiddleChFactor" = "text:split($MiddleChFactor, '_')[2]"!]
          [!VAR "MiddleChModNo"  = "num:i(($MiddleChFactor div 16) - 1)"!]
          [!VAR "PreviousPredefTimer" = "concat('GTM_TOM', $BasePredefChannelModNo , '_CHANNEL',num:i($BasePredefChannel),'')"!]
          [!VAR "ActualPredefTimer"   = "concat('GTM_TOM', $MiddleChModNo, '_CHANNEL',num:i($MiddleChNo - $MiddleChFactor),'')"!]
          [!VAR "NextPredefTimer"     = "concat('GTM_TOM', $CascadingPredefChannelModNo, '_CHANNEL',num:i($CascadingPredefChannel),'')"!]
        [!ENDIF!]
    [!ENDIF!]

    [!/* Validate GPT Predef Timer Extra_Channel Requirements. */!]
    [!CALL "GPT_CG_GetGptPredefFreq","GtmClockRef" = "$ClockRef", "TimerModNo" = "$BasePredefChannelModNo", "TickDurationUs" = "num:i($GptPredefTimerUs)", "OpnMode" = "num:i(1)"!]
    [!IF "num:i($Extra_Channel) = num:i(1)"!]
      [!IF "contains(GptTimerChannelUsage, '1US_16BIT_ENABLED')"!][!//
        [!IF "$GtmConfigCount = num:i(1)"!]
          [!ERROR!][!//
            ERROR: To make a 1Us predef timer of 16bit, the channel "[!"$ActualPredefTimer"!]", under configuration [!"node:name(.)"!],
             need it's immediate previous Channel "[!"$PreviousPredefTimer"!]" also to work as a clock divider for frequency tuning.
             Add the GTM Timer channel "[!"$PreviousPredefTimer"!]" to implement 1us predef timer.
          [!ENDERROR!][!//
        [!ENDIF!]
      [!ELSE!]
        [!IF "$GtmConfigCount = num:i(2)"!]
          [!ERROR!][!//
            ERROR: To make a predef timer of 24bit/32bit, the Channel "[!"$ActualPredefTimer"!]" under configuration [!"node:name(.)"!]
            need it's immediate previous Channel "[!"$PreviousPredefTimer"!]" also to work as a clock divider for frequency tuning.
            Add the GTM Timer channel "[!"$PreviousPredefTimer"!]" to implement 1us predef timer.
          [!ENDERROR!][!//
        [!ENDIF!]
      [!ENDIF!]
    [!ELSE!]
      [!IF "contains(GptTimerChannelUsage, '1US_16BIT_ENABLED')"!][!//
        [!IF "$GtmConfigCount = num:i(2)"!]
          [!WARNING!][!//
            WARNING: Predef timer Channel "[!"$ActualPredefTimer"!]" under configuration [!"node:name(.)"!]
            does not need it's immediate previous Channel "[!"$PreviousPredefTimer"!]".
            The GTM Timer channel "[!"$PreviousPredefTimer"!]" can be removed.
          [!ENDWARNING!][!//
        [!ENDIF!]
      [!ELSE!]
        [!IF "$GtmConfigCount = num:i(3)"!]
          [!WARNING!][!//
            WARNING: Predef timer Channel "[!"$ActualPredefTimer"!]" under configuration [!"node:name(.)"!]
            does not need it's immediate previous Channel "[!"$PreviousPredefTimer"!]".
            The GTM Timer channel "[!"$PreviousPredefTimer"!]" can be removed.
          [!ENDWARNING!][!//
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDSELECT!]
[!ENDSELECT!]
[!ENDNOCODE!]
[!ENDMACRO!]

/***********************************************************************************
** Name           : GPT_CG_GetGptPredefExtraChConf                                **
**                                                                                **
** Description    : This macro calculates the required timer configuration        **
**                  properties of the extra TOM channel which can be              **
**                  used to tick the actual predef timer channel.                 **
**                                                                                **
***********************************************************************************/
[!MACRO "GPT_CG_GetGptPredefExtraChConf","TickDurationUs" = ""!][!//
[!NOCODE!]
[!VAR "Invalid" = "num:i(1)"!][!//
[!VAR "PredefClkId0" = "num:i(0)"!][!//
[!VAR "Frequency_Final" = "num:i(1)"!][!//
[!VAR "CM0_Calculated" = "num:i(65535)"!]
[!IF "num:i($TickDurationUs) = num:i(100)"!][!// 100us Predef timer
  [!VAR "Exp_Freq" = "num:i(10000)"!]
  [!VAR "Difference1" = "num:i($Exp_Freq)"!]
[!ELSE!] [!// 1us Predef timer
  [!VAR "Exp_Freq" = "num:i(1000000)"!]
  [!VAR "Difference1" = "num:i($Exp_Freq)"!]
[!ENDIF!][!//
[!FOR "ClkId1" = "num:i(0)" TO "num:i(4)"!][!// Different Fxclk divider selections
  [!CALL "GPT_CG_PowerCalc","number" = "num:i(2)","exponent" = "num:i(($ClkId1*4))"!][!// Calculate the Fixed clock divider
  [!VAR "Fxclk1"="$Val"!] [!//Fixed clock divider
  [!VAR "CompareValue" = "num:f(num:f($Fgtm) div num:f($Fxclk1 * num:i($Exp_Freq)))"!][!// Possible values of Compare register, CM0
  [!IF "num:f($CompareValue) > num:f(1.8) and num:f($CompareValue) < num:f(65535)"!][!//
    [!VAR "Invalid" = "num:i(0)"!][!//
    [!VAR "Frequency" = "($Fgtm div ($Fxclk1 * round($CompareValue)))"!][!//
    [!IF "num:f($Exp_Freq) < num:f($Frequency)"!][!//
      [!VAR "Difference" = "num:f($Frequency) - num:f($Exp_Freq)"!][!//
    [!ELSE!][!//
      [!VAR "Difference" = "num:f($Exp_Freq) - num:f($Frequency)"!][!//
    [!ENDIF!][!//
    [!IF "num:f($Difference) < num:f($Difference1)"!][!//
      [!VAR "Difference1" = "num:f($Difference)"!][!//
      [!VAR "CM0_Calculated" = "round($CompareValue)"!][!// Actual CM0 value
      [!VAR "Frequency_Final" = "($Fgtm div ($Fxclk1 * round($CompareValue)))"!][!//
     [!VAR "FXCLK00" = "num:f($Fxclk1)"!][!//
      [!VAR "PredefClkId0" = "num:i($ClkId1)"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDFOR!][!//

[!IF "num:i($Invalid) = num:i(1)"!][!// Invalid compare register values
  [!ERROR!][!//
    ERROR: Frequency error. [!"$TickDurationUs"!]US Predef timer cannot be implemented with the current clock configuration.
           Recheck the settings under MCU plugin.
  [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDNOCODE!]
[!ENDMACRO!]

/***********************************************************************************
** Name           : GPT_CG_GetGptPredefFreq                                       **
**                                                                                **
** Description    : This macro calculates the timer channel frequency             **
**                  based on the dividers configured                              **
**                  for GTM CMU and GTM CCM.                                      **
**                  This macro also tells whether an extra channel                **
**                  is required for frequency tuning of a predef timer channel.   **
**                                                                                **
**  TRACEABILITY : [cover parentID={E7EE6EB5-77B1-4017-9B38-2E71110B02EC}]        **
**                                                                                **
***********************************************************************************/
[!MACRO "GPT_CG_GetGptPredefFreq","GtmClockRef" = "","TimerModNo" = "","TickDurationUs" = "","OpnMode" = ""!][!//
[!NOCODE!]
[!VAR "Fscugtm" = "node:value(node:ref($GtmClockRef)/McuPllDistributionSettingConfig/McuGTMFrequency)"!][!//Clock frequecy from MCU
[!SELECT "as:modconf('Mcu')[1]/McuModuleConfiguration/GtmGlobalConfiguration/*[1]/McuGtmClockManagementConf"!][!//
  [!VAR "GtmDenominator" = "GtmCmuGlobalClockDenominator"!][!//
  [!VAR "GtmNumerator" = "GtmCmuGlobalClockNumerator"!][!//
  [!VAR "Fgtm" = "$Fscugtm div($GtmNumerator div $GtmDenominator)"!] [!//Clock frequecy GTM Global - CMU_GCLK
  [!VAR "Cluster0ClkDivider" = "../GtmClusterConf/*[1]/GtmCmuClusterInputClockDividerEnable"!][!//
  [!VAR "GtmClusterNodeName" = "concat('GtmClusterConf_',num:i($TimerModNo))"!]
  [!VAR "GtmClusterXDivider" = "../GtmClusterConf/*[@name=$GtmClusterNodeName]/GtmCmuClusterInputClockDividerEnable"!]
  [!VAR "GtmCluster0Divider" = "../GtmClusterConf/*[@name='GtmClusterConf_0']/GtmCmuClusterInputClockDividerEnable"!]
  [!IF "$GtmCluster0Divider = 'CLS_CLK_CFG_DISABLED_SEL0' or $GtmClusterXDivider = 'CLS_CLK_CFG_DISABLED_SEL0'"!]
    [!ERROR!]
      GPT Code Generator: GTM cluster level divider (GtmCmuClusterInputClockDividerEnable) is swiched off for Cluster0 or Cluster[!"$GtmTimerModNo"!].
    [!ENDERROR!]
  [!ENDIF!]
  [!IF "num:i($TimerModNo) < num:i(5)"!][!//
    [!IF "$GtmCluster0Divider= 'CLS_CLK_CFG_ENABLED_WITH_DIV_SEL2'"!]
      [!VAR "GtmClusterDivVal" = "num:f(2.0)"!]
    [!ELSEIF "$GtmCluster0Divider= 'CLS_CLK_CFG_ENABLED_WITHOUT_DIV_SEL1'"!]
      [!IF "$GtmClusterXDivider= 'CLS_CLK_CFG_ENABLED_WITH_DIV_SEL2'"!]
        [!VAR "GtmClusterDivVal" = "num:f(2.0)"!]
      [!ELSE!]
        [!VAR "GtmClusterDivVal" = "num:f(1.0)"!]
      [!ENDIF!]
    [!ENDIF!]
  [!ELSE!][!//
    [!IF "$GtmClusterXDivider = 'CLS_CLK_CFG_ENABLED_WITH_DIV_SEL2'"!]
      [!VAR "GtmClusterDivVal" = "num:f(2.0)"!]
    [!ENDIF!]
  [!ENDIF!]
  [!VAR "Fgtm"="num:f(num:f($Fgtm) div num:f($GtmClusterDivVal))"!]
[!ENDSELECT!][!//
[!SELECT "as:modconf('Mcu')[1]/McuModuleConfiguration/GtmGlobalConfiguration/*[1]/GtmClusterConf/*[@name=$GtmClusterNodeName]"!]"!][!//
  [!SELECT "./GtmClusterFixedClockSetting"!]
    [!VAR "TempNodeValue" = "GtmClusterFixedClockSrc"!]
  [!ENDSELECT!]
  [!IF "contains($TempNodeValue,'CLOCK8')"!]
      [!VAR "ClockType" = "'CONF_CLOCK'"!]
  [!ELSE!]
      [!VAR "ClockType" = "'FIXED_CLOCK'"!]
  [!ENDIF!]    [!//[!IF "contains($TempNodeValue,'CLOCK8')"!][!//
  [!SELECT "as:modconf('Mcu')[1]/McuModuleConfiguration/GtmGlobalConfiguration/*[1]/McuGtmClockManagementConf/*"!]
    [!IF "(./GtmFixedClockSetting/GtmCmuFixedClockEnable = 'false')"!]
      [!ERROR!]
        ERROR : McuGtmClockManagementConf/GtmFixedClockSetting/GtmCmuFixedClockEnable cannot be false when fixed clock is used.
      [!ENDERROR!]
    [!ENDIF!]    [!//[!IF "(GtmFixedClockSetting/GtmCmuFixedClockEnable = 'false')"!]
  [!ENDSELECT!]
[!ENDSELECT!]
[!SELECT "as:modconf('Mcu')[1]/McuModuleConfiguration/GtmGlobalConfiguration/*[1]/McuGtmClockManagementConf/GtmConfigClockSetting"!]
  [!IF "$ClockType = 'FIXED_CLOCK'"!][!//
    [!VAR "TempNodeValue" = "../GtmFixedClockSetting/GtmCmuFixedClockSel"!]
    [!IF "$TempNodeValue != 'CMU_GLOBAL_CLOCK_SEL0'"!] [!// Configurable clock is the source of fixed clock
      [!VAR "CmuClkID" = "num:i(substring-after($TempNodeValue,'SEL'))"!][!//Extract CMU clock ID from TempNodeValue
      [!VAR "CmuConfigClockEn" =  "concat('GtmCmuConfigClock',string($CmuClkID),'Enable')"!]
      [!IF "node:value($CmuConfigClockEn) != 'true'"!]
        [!ERROR!]
          ERROR : CMU configurable Clock[!"$CmuClkID"!] is not enabled in the configuration.
        [!ENDERROR!]
      [!ENDIF!][!//    [!IF "node:value($CmuConfigClockEn) != 'true'"!]
      [!VAR "CmuConfigClockDiv" =  "concat('GtmCmuConfigClock',string($CmuClkID),'Div')"!]
      [!VAR "ClockDivider" = "num:i(node:value($CmuConfigClockDiv))+1"!][!// NodeValue of (GtmConfigClockSetting/GtmCmuConfigClock[CmuClkID]Div) +1 [!//
      [!VAR "Fgtm" = "num:f(num:f($Fgtm) div num:f($ClockDivider))"!][!//
    [!ENDIF!][!//
  [!ELSEIF "($ClockType = 'CONF_CLOCK')"!][!//
    [!VAR "Fgtm" = "$Fscugtm"!] [!// Fgtm = CMU_CLK8
  [!ELSE!]
    [!ERROR!]
      ERROR : Unable to calculate the clock frequency for the GTM timer cell.
    [!ENDERROR!]
  [!ENDIF!]    [!//[!IF "$ClockType = 'FIXED_CLOCK'"!]
[!ENDSELECT!]
[!IF "$OpnMode = num:i(1)"!][!// Check whether an extra channel is required for predef timer implementation
  [!VAR "Extra_Channel" = "num:i(1)"!]
  [!IF "num:i($TickDurationUs) = num:i(100)"!][!// 100us Predef timer
    [!VAR "Exp_Freq" = "num:i(10000)"!]
  [!ELSEIF "num:i($TickDurationUs) = num:i(1)"!][!// 1us Predef timer
    [!VAR "Exp_Freq" = "num:i(1000000)"!]
  [!ELSE!]
    [!ERROR!]
      ERROR : Undefined parameter 'TickDurationUs' passed to the macro. Cannot support [!"$TickDurationUs"!]US predef timer.
    [!ENDERROR!]
  [!ENDIF!][!//
  [!FOR "ClkId0" = "num:i(0)" TO "num:i(4)"!][!// Different Fxclk divider selections
    [!CALL "GPT_CG_PowerCalc","number" = "num:i(2)","exponent" = "num:i(($ClkId0*4))"!][!// Calculate the Fixed clock divider
    [!VAR "Fxclk0"="$Val"!] [!//Fixed clock divider
    [!IF "(round($Fgtm) = round($Exp_Freq * $Fxclk0))"!][!//Check whether the predef channel frequency can be derived directly from the GTM clock
      [!VAR "PredefClkId1" = "num:i($ClkId0)"!]
      [!VAR "Extra_Channel" = "num:i(0)"!]
    [!ENDIF!]
  [!ENDFOR!]
[!ENDIF!]
[!ENDNOCODE!]
[!ENDMACRO!]

/*******************************************************************************
** Name           : GPT_CG_PowerCalc                                          **
**                                                                            **
** Description    : Macro to calculate power                                  **
**                                                                            **
*******************************************************************************/
[!MACRO "GPT_CG_PowerCalc", "number" = "","exponent" = ""!]
[!NOCODE!]
[!VAR "Val" = "num:i(1)"!]
[!IF "$exponent != num:i(0)"!]
  [!VAR "Val" = "num:i(bit:shl($number, $exponent - num:i(1)))"!]
[!ENDIF!]
[!ENDNOCODE!]
[!ENDMACRO!]

/*******************************************************************************
** Name           : GPT_CG_GptCoreChannelInfo                                 **
**                                                                            **
** Description    : Macro to calculate the number of Normal and Predef        **
**                  channels in a core                                        **
**                                                                            **
** Pre-requisite  : GPT_CG_GenerateModuleMap macro should be called before    **
**                  calling this macro                                        **
**                                                                            **
**  TRACEABILITY : [cover parentID={11D72E80-957E-4428-87FB-5101A32F40C3} ]   **
**                                                                            **
*******************************************************************************/
[!MACRO "GPT_CG_GptCoreChannelInfo", "GptCoreId" = ""!][!//
[!NOCODE!][!//
[!VAR "MaxChannelMappedToCore"  = "num:i(0)"!][!//
[!VAR "MaxPredefChannelMappedToCore"  = "num:i(0)"!][!//
[!VAR "corePattern" = "concat( 'CORE', $GptCoreId )"!]
[!VAR "matchCore" = "concat( '^.*(', $corePattern, ').*$' )"!]
[!VAR "fetchItem" = "concat( '^', $corePattern, '.*$' )"!]
[!/*Count all channels mapped to the current core*/!]
[!IF "text:match($CGModuleMap, $matchCore)"!] [!// Fetch all strings matching the core.
  [!VAR "grepData" = "translate(text:grep(text:split($CGModuleMap, ','), $fetchItem), '[]', '')"!][!//Fetch all channels mapped to the current core
  [!VAR "MaxChannelMappedToCore" = "count(text:split($grepData, ','))"!]
[!ENDIF!]
[!/*Count all predef channels mapped to the current core*/!]
[!SELECT "as:modconf('Gpt')[1]/GptChannelConfigSet/GptChannelConfiguration/*"!][!//
  [!IF "(contains(text:split($grepData, ','), concat($corePattern, '_', node:name(node:current()), '#')))"!][!//
    [!IF "not (contains(GptTimerChannelUsage, '_NORMAL'))"!][!//
      [!VAR "MaxPredefChannelMappedToCore" = "num:i($MaxPredefChannelMappedToCore + 1)"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : GPT_CG_GenerateModuleMap                                **
**                                                                            **
** Description      : Macro to generate core-channel mappings for a module    **
**                                                                            **
*******************************************************************************/
[!MACRO "GPT_CG_GenerateModuleMap", "Module" = ""!][!//
[!NOCODE!][!//
[!VAR "CGCoreUsed" = "''"!][!//
[!VAR "CGModuleMap" = "''"!][!//
[!VAR "CGAllocatedResources" = "''"!][!//
[!/* [cover parentID={40A68E73-EC73-41a7-A60C-FD43AD05F294}] */!]
[!/*  [/cover] */!]
[!SELECT "as:modconf('ResourceM')[1]"!][!//
    [!VAR "CGMasterCoreId" = "substring(node:value(ResourceMMcalConfig/*[1]/ResourceMMasterCore),5,1)"!][!//
    [!LOOP "ResourceMMcalConfig/*[1]/ResourceMMcalCore/*"!][!//
      [!VAR "CGCoreID" = "./ResourceMCoreID"!][!//
      [!LOOP "ResourceMAllocation/*"!][!//
        [!IF "$Module = ./ResourceMModuleName"!][!//
          [!IF "node:refvalid(./ResourceMResourceRef)"!]
            [!VAR "index" = "num:i(count(text:split(./ResourceMResourceRef, '/')))"!][!//
            [!VAR "ResourceName" = "text:split(./ResourceMResourceRef, '/')[num:i($index)]"!][!//
            [!VAR "CGModuleMap" = "concat($CGModuleMap, $CGCoreID, '_', $ResourceName, '#,')"!][!//
            [!VAR "CGAllocatedResources" = "concat($CGAllocatedResources, $ResourceName, '#,')"!][!//
            [!IF "not(contains(text:split($CGCoreUsed), $CGCoreID))"!]
              [!VAR "CGCoreUsed" = "concat($CGCoreUsed, $CGCoreID, ',')"!][!//
            [!ENDIF!]
          [!ELSE!]
            [!WARNING!][!//
            Warning: The resource [!"node:value(./ResourceMResourceRef)"!] does not exists.
            [!ENDWARNING!][!//
          [!ENDIF!]
        [!ENDIF!][!//
      [!ENDLOOP!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : GPT_CG_ValidateChAllocation                             **
**                                                                            **
** Description      : Macro to validate if a channel is allocated to the core **
**                                                                            **
** Pre-requisite    : GPT_CG_GenerateModuleMap macro should be called before  **
**                    calling this macro                                      **
*******************************************************************************/
[!MACRO "GPT_CG_ValidateChAllocation", "Item" = ""!][!//
[!NOCODE!][!//
[!VAR "CGResult" = "'FALSE'"!][!//
[!VAR "pattern" = "concat($Item, '#')"!]
[!IF "text:contains(text:split($CGAllocatedResources,','), $pattern)"!][!//
  [!VAR "CGResult" = "'TRUE'"!][!//
[!ELSE!]
  [!VAR "CGResult" = "'FALSE'"!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!ENDINDENT!]
[!ENDIF!][!// IF "not(var:defined('GPT_M'))