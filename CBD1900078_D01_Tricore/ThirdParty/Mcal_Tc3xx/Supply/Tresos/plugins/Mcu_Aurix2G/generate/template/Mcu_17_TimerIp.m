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
**  FILENAME  : Mcu_17_TimerIp.m                                              **
**                                                                            **
**  VERSION   : 8.0.0                                                         **
**                                                                            **
**  DATE      : 2018.09.12                                                    **
**                                                                            **
**  VARIANT   : Post-Build                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION :  This file contains the macros used by the code template    **
**                                                                            **
**  SPECIFICATION(S) : Specification of MCU Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : No                                               **
**                                                                            **
*******************************************************************************/
*/!]
/******************************************************************************/
[!AUTOSPACING!]
[!/* *** multiple inclusion protection*** */!][!//
[!IF "not(var:defined('MCU_17_TIMERIP_M'))"!][!//
[!VAR "MCU_17_TIMERIP_M"="'true'"!][!//

/*******************************************************************************
** Name             : Mcu_17_TimerIp_CG_ConfigGtmUserData                     **
**                                                                            **
** Description      : Macro to generate the user data for the ATOM/TOM/TIM    **
**                    channels                                                **
*******************************************************************************/
[!MACRO "Mcu_17_TimerIp_CG_ConfigGtmUserData","UserDataInfo"= "","GtmIp"= ""!][!//
[!NOCODE!][!//
[!/* Tom/Atom Verification and UserInfo Construction */!]
[!IF "'Atom' = $GtmIp or 'Tom' = $GtmIp"!]
  [!FOR "Index" = "num:i(1)" TO "count(text:split($UserDataInfo, ','))"!][!// Iterate for all items in HashMap
    [!VAR "CurrNode" = "text:split($UserDataInfo, ',')[num:i($Index)]"!]
    [!VAR "ModuleId" = "substring-before(substring-after($CurrNode, concat('_', $GtmIp)), '#')"!]
    [!VAR "ChannelId" = "substring-before(substring-after($CurrNode, '#_'), '#')"!]
    [!VAR "McuNodeRefered" = "concat('McuGtm', $GtmIp, 'AllocationConf_', $ModuleId, '/McuGtm', $GtmIp, 'ChannelAllocationConf_', $ChannelId)"!][!//
    [!VAR "UserModule" = "substring-before($CurrNode, '_')"!][!//
    [!IF "$UserModule = 'Gpt'"!][!// User is GPT
      [!IF "node:exists(as:modconf('Gpt')[1])"!][!//
        [!VAR "Flag" = "num:i(0)"!][!//
        [!SELECT "as:modconf('Gpt')[1]/GptChannelConfigSet/*/*"!][!//
          [!SELECT "(./GtmTimerOutputModuleConfiguration/*)"!][!//
            [!VAR "NodeRefered" = "substring-after(./GtmTimerUsed,'McuGtmAllocationConf_0/')"!][!//
            [!IF "$NodeRefered = $McuNodeRefered"!][!//
              [!VAR "Flag" = "num:i(1)"!][!//
              [!VAR "LogicalChannelId" = "../../GptChannelId"!][!//
              [!VAR "GtmIpData" = "bit:or(num:i(4),bit:shl($LogicalChannelId,num:i(8)))"!][!// UserID of GPT | Gpt LogicalChannelId
              [!/* RegEx for fetching the Channel Used and Modifying User Data */!]
              [!VAR "ModifyGtmUserData" = "concat($CurrNode, '@', $GtmIpData, '#')"!][!//
              [!VAR "UserDataInfo" = "text:replaceAll($UserDataInfo, $CurrNode, $ModifyGtmUserData)"!][!//
              [!BREAK!][!//
            [!ENDIF!][!//
          [!ENDSELECT!][!//
        [!ENDSELECT!][!//
        [!IF "$Flag = num:i(0)"!]
          [!ERROR!][!//
          ERROR: GTM timer [!"text:toupper($GtmIp)"!] Module [!"$ModuleId"!], Channel [!"$ChannelId"!], allocated for GPT in Mcu Hardware Resource Allocation is not configured in GPT module. Unreserve the [!"text:toupper($GtmIp)"!] channel in MCU.
          [!ENDERROR!][!//
        [!ENDIF!]
      [!ELSE!][!//
        [!ERROR!][!//
        ERROR: GTM timer [!"text:toupper($GtmIp)"!] Module [!"$ModuleId"!], Channel [!"$ChannelId"!], is allocated for GPT in Mcu Hardware Resource Allocation, but GPT module is not part of Configuration generation project. Unreserve the [!"text:toupper($GtmIp)"!] channel in MCU.
        [!ENDERROR!][!//
      [!ENDIF!]
    [!ELSEIF "$UserModule = 'Pwm'"!][!// User is PWM
      [!IF "node:exists(as:modconf('Pwm')[1])"!][!//
        [!VAR "Flag" = "num:i(0)"!][!//
        [!SELECT "as:modconf('Pwm')[1]/PwmChannelConfigSet/*/*"!][!//
          [!SELECT "(./GtmTimerOutputModuleConfiguration/*)"!][!//
            [!VAR "NodeRefered" = "substring-after(./GtmTimerUsed,'McuGtmAllocationConf_0/')"!][!//
            [!IF "$NodeRefered = $McuNodeRefered"!][!//
              [!VAR "Flag" = "num:i(1)"!][!//
              [!VAR "LogicalChannelId" = "../../PwmChannelId"!][!//
              [!VAR "GtmIpData" = "bit:or(num:i(3),bit:shl($LogicalChannelId,num:i(8)))"!][!// UserID of PWM | PWM LogicalChannelId
              [!/* RegEx for fetching the Channel Used and Modifying User Data */!]
              [!VAR "ModifyGtmUserData" = "concat($CurrNode, '@', $GtmIpData, '#')"!][!//
              [!VAR "UserDataInfo" = "text:replaceAll($UserDataInfo, $CurrNode, $ModifyGtmUserData)"!][!//
              [!BREAK!][!//
            [!ENDIF!][!//
          [!ENDSELECT!][!//
        [!ENDSELECT!][!//
        [!IF "$Flag = num:i(0)"!]
          [!ERROR!][!//
          ERROR: GTM timer [!"text:toupper($GtmIp)"!] Module [!"$ModuleId"!], Channel [!"$ChannelId"!], allocated for PWM in Mcu Hardware Resource Allocation is not configured in PWM module. Unreserve the [!"text:toupper($GtmIp)"!] channel in MCU.
          [!ENDERROR!][!//
        [!ENDIF!]
      [!ELSE!][!//
        [!ERROR!][!//
        ERROR: GTM timer [!"text:toupper($GtmIp)"!] Module [!"$ModuleId"!], Channel [!"$ChannelId"!], is allocated for PWM in Mcu Hardware Resource Allocation, but PWM module is not part of Configuration generation project. Unreserve the [!"text:toupper($GtmIp)"!] channel in MCU.
        [!ENDERROR!][!//
      [!ENDIF!]
    [!ELSEIF "$UserModule = 'Adc'"!][!// User is ADC
      [!IF "node:exists(as:modconf('Adc')[1])"!][!//
        [!VAR "Flag" = "num:i(0)"!][!//
        [!SELECT "as:modconf('Adc')[1]/AdcConfigSet/AdcHwUnit/*/AdcGroup/*"!][!//
          [!SELECT "(./GtmTriggerTimerConfig/*)"!][!//
            [!VAR "NodeRefered" = "substring-after(./GtmTimerUsed,'McuGtmAllocationConf_0/')"!][!//
            [!IF "$NodeRefered = $McuNodeRefered"!][!//
              [!VAR "Flag" = "num:i(1)"!][!//
              [!VAR "LogicalChannelId" = "num:i(0)"!][!// Dummy
              [!VAR "GtmIpData" = "bit:or(num:i(1),bit:shl($LogicalChannelId,num:i(8)))"!][!// UserID of ADC
              [!/* RegEx for fetching the Channel Used and Modifying User Data */!]
              [!VAR "ModifyGtmUserData" = "concat($CurrNode, '@', $GtmIpData, '#')"!][!//
              [!VAR "UserDataInfo" = "text:replaceAll($UserDataInfo, $CurrNode, $ModifyGtmUserData)"!][!//
              [!BREAK!][!//
            [!ENDIF!][!//
          [!ENDSELECT!][!//
          [!SELECT "(./GtmGatingTimerConfig/*)"!][!//
            [!VAR "NodeRefered" = "substring-after(./GtmTimerUsed,'McuGtmAllocationConf_0/')"!][!//
            [!IF "$NodeRefered = $McuNodeRefered"!][!//
              [!VAR "Flag" = "num:i(1)"!][!//
              [!VAR "LogicalChannelId" = "num:i(0)"!][!// Dummy
              [!VAR "GtmIpData" = "bit:or(num:i(1),bit:shl($LogicalChannelId,num:i(8)))"!][!// UserID of ADC
              [!/* RegEx for fetching the Channel Used and Modifying User Data */!]
              [!VAR "ModifyGtmUserData" = "concat($CurrNode, '@', $GtmIpData, '#')"!][!//
              [!VAR "UserDataInfo" = "text:replaceAll($UserDataInfo, $CurrNode, $ModifyGtmUserData)"!][!//
              [!BREAK!][!//
            [!ENDIF!][!//
          [!ENDSELECT!][!//
        [!ENDSELECT!][!//
        [!IF "$Flag = num:i(0)"!]
          [!ERROR!][!//
          ERROR: GTM timer [!"text:toupper($GtmIp)"!] Module [!"$ModuleId"!], Channel [!"$ChannelId"!], allocated for ADC in Mcu Hardware Resource Allocation is not configured in ADC module. Unreserve the [!"text:toupper($GtmIp)"!] channel in MCU.
          [!ENDERROR!][!//
        [!ENDIF!]
      [!ELSE!][!//
        [!ERROR!][!//
        ERROR: GTM timer [!"text:toupper($GtmIp)"!] Module [!"$ModuleId"!], Channel [!"$ChannelId"!], is allocated for ADC in Mcu Hardware Resource Allocation, but ADC module is not part of Configuration generation project. Unreserve the [!"text:toupper($GtmIp)"!] channel in MCU.
        [!ENDERROR!][!//
      [!ENDIF!]
    [!ELSEIF "$UserModule = 'Wdg'"!][!// User is WDG
      [!IF "node:exists(as:modconf('Wdg')[1])"!][!//
        [!VAR "Flag" = "num:i(0)"!][!//
        [!SELECT "as:modconf('Wdg')[1]/WdgSettingsConfig/*/*/*/*"!][!//
          [!SELECT "(./GtmTimerOutputModuleConfiguration)"!][!//
            [!VAR "NodeRefered" = "substring-after(./GtmTimerUsed,'McuGtmAllocationConf_0/')"!][!//
            [!IF "$NodeRefered = $McuNodeRefered"!][!//
              [!VAR "Flag" = "num:i(1)"!][!//
              [!VAR "LogicalChannelId" = "num:i(0)"!][!// Dummy
              [!VAR "GtmIpData" = "bit:or(num:i(2),bit:shl($LogicalChannelId,num:i(8)))"!][!// UserID of WDG
              [!/* RegEx for fetching the Channel Used and Modifying User Data */!]
              [!VAR "ModifyGtmUserData" = "concat($CurrNode, '@', $GtmIpData, '#')"!][!//
              [!VAR "UserDataInfo" = "text:replaceAll($UserDataInfo, $CurrNode, $ModifyGtmUserData)"!][!//
              [!BREAK!][!//
            [!ENDIF!][!//
          [!ENDSELECT!][!//
        [!ENDSELECT!][!//
        [!IF "$Flag = num:i(0)"!]
          [!ERROR!][!//
          ERROR: GTM timer [!"text:toupper($GtmIp)"!] Module [!"$ModuleId"!], Channel [!"$ChannelId"!], allocated for WDG in Mcu Hardware Resource Allocation is not configured in WDG module. Unreserve the [!"text:toupper($GtmIp)"!] channel in MCU.
          [!ENDERROR!][!//
        [!ENDIF!]
      [!ELSE!][!//
        [!ERROR!][!//
        ERROR: GTM timer [!"text:toupper($GtmIp)"!] Module [!"$ModuleId"!], Channel [!"$ChannelId"!], is allocated for WDG in Mcu Hardware Resource Allocation, but WDG module is not part of Configuration generation project. Unreserve the [!"text:toupper($GtmIp)"!] channel in MCU.
        [!ENDERROR!][!//
      [!ENDIF!]
    [!ELSEIF "$UserModule = 'Dsadc'"!][!// User is DSADC
      [!IF "node:exists(as:modconf('Dsadc')[1])"!]
        [!VAR "LogicalChannelId" = "num:i(0)"!][!// Dummy
        [!VAR "GtmIpData" = "bit:or(num:i(7),bit:shl($LogicalChannelId,num:i(8)))"!][!// UserID of DSADC
        [!/* RegEx for fetching the Channel Used and Modifying User Data */!]
        [!VAR "ModifyGtmUserData" = "concat($CurrNode, '@', $GtmIpData, '#')"!][!//
        [!VAR "UserDataInfo" = "text:replaceAll($UserDataInfo, $CurrNode, $ModifyGtmUserData)"!][!//
      [!ELSE!][!//
        [!ERROR!][!//
        ERROR: GTM timer [!"text:toupper($GtmIp)"!] Module [!"$ModuleId"!], Channel [!"$ChannelId"!], is allocated for DSADC in Mcu Hardware Resource Allocation, but DSADC module is not part of Configuration generation project. Unreserve the [!"text:toupper($GtmIp)"!] channel in MCU.
        [!ENDERROR!][!//
      [!ENDIF!]
    [!ELSEIF "$UserModule = 'Ocu'"!][!// User is OCU
      [!IF "node:exists(as:modconf('Ocu')[1])"!]
        [!VAR "LogicalChannelId" = "num:i(0)"!][!// Dummy
        [!VAR "GtmIpData" = "bit:or(num:i(6),bit:shl($LogicalChannelId,num:i(8)))"!][!// UserID of OCU
        [!/* RegEx for fetching the Channel Used and Modifying User Data */!]
        [!VAR "ModifyGtmUserData" = "concat($CurrNode, '@', $GtmIpData, '#')"!]
        [!VAR "UserDataInfo" = "text:replaceAll($UserDataInfo, $CurrNode, $ModifyGtmUserData)"!]
      [!ELSE!][!//
        [!ERROR!][!//
        ERROR: GTM timer [!"text:toupper($GtmIp)"!] Module [!"$ModuleId"!], Channel [!"$ChannelId"!], is allocated for OCU in Mcu Hardware Resource Allocation, but OCU module is not part of Configuration generation project. Unreserve the [!"text:toupper($GtmIp)"!] channel in MCU.
        [!ENDERROR!][!//
      [!ENDIF!]
    [!ENDIF!]
  [!ENDFOR!][!//
[!/* TIM Verification and UserInfo Construction */!]
[!ELSEIF "'Tim' = $GtmIp"!]
  [!FOR "Index" = "num:i(1)" TO "count(text:split($UserDataInfo, ','))"!][!// Iterate for all items in HashMap
    [!VAR "CurrNode" = "text:split($UserDataInfo, ',')[num:i($Index)]"!]
    [!VAR "ModuleId" = "substring-before(substring-after($CurrNode, concat('_', $GtmIp)), '#')"!]
    [!VAR "ChannelId" = "substring-before(substring-after($CurrNode, '#_'), '#')"!]
    [!VAR "McuNodeRefered" = "concat('McuGtm', $GtmIp, 'AllocationConf_', $ModuleId, '/McuGtm', $GtmIp, 'ChannelAllocationConf_', $ChannelId)"!][!//
    [!VAR "UserModule" = "substring-before($CurrNode, '_')"!][!//
    [!IF "$UserModule = 'Icu'"!][!// User is ICU
      [!IF "node:exists(as:modconf('Icu')[1])"!][!//
        [!VAR "Flag" = "num:i(0)"!][!//
        [!SELECT "as:modconf('Icu')[1]/IcuConfigSet/*/*"!][!//
          [!SELECT "(./GtmTimerInputConfiguration/*)"!][!//
            [!VAR "NodeRefered" = "substring-after(./GtmTimerUsed,'McuGtmAllocationConf_0/')"!][!//
            [!IF "$NodeRefered = $McuNodeRefered"!][!//
              [!VAR "Flag" = "num:i(1)"!][!//
              [!VAR "LogicalChannelId" = "../../IcuChannelId"!][!//
              [!VAR "GtmIpData" = "bit:or(num:i(5),bit:shl($LogicalChannelId,num:i(8)))"!][!// UserID of ICU | ICU LogicalChannelId
              [!/* RegEx for fetching the Channel Used and Modifying User Data */!]
              [!VAR "ModifyGtmUserData" = "concat($CurrNode, '@', $GtmIpData, '#')"!][!//
              [!VAR "UserDataInfo" = "text:replaceAll($UserDataInfo, $CurrNode, $ModifyGtmUserData)"!][!//
              [!BREAK!][!//
            [!ENDIF!][!//
          [!ENDSELECT!][!//
        [!ENDSELECT!][!//
        [!IF "$Flag = num:i(0)"!]
          [!ERROR!][!//
          ERROR: GTM timer [!"text:toupper($GtmIp)"!] Module [!"$ModuleId"!], Channel [!"$ChannelId"!], allocated for ICU in Mcu Hardware Resource Allocation is not configured in ICU module. Unreserve the [!"text:toupper($GtmIp)"!] channel in MCU.
          [!ENDERROR!][!//
        [!ENDIF!]
      [!ELSE!][!//
        [!ERROR!][!//
        ERROR: GTM timer [!"text:toupper($GtmIp)"!] Module [!"$ModuleId"!], Channel [!"$ChannelId"!], is allocated for ICU in Mcu Hardware Resource Allocation, but ICU module is not part of Configuration generation project. Unreserve the [!"text:toupper($GtmIp)"!] channel in MCU.
        [!ENDERROR!][!//
      [!ENDIF!]
    [!ENDIF!]
  [!ENDFOR!]
[!ENDIF!]
[!ENDNOCODE!]
[!ENDMACRO!]


/*******************************************************************************
** Name             : Mcu_17_TimerIp_CG_ConfigCcu6UserData                    **
**                                                                            **
** Description      : Macro to calculate the user data for CCU6 Comparators   **
*******************************************************************************/
[!MACRO "Mcu_17_TimerIp_CG_ConfigCcu6UserData","Ccu6KernelUserInfo"= "","Ccu6KernelNumber"= "","Cc60UserInfo"= "","Cc61UserInfo"= "","Cc62UserInfo"= "","Cc63UserInfo"= ""!][!//
[!NOCODE!][!//
[!VAR "Ccu6KernelUser" = "num:i(0)"!][!//
  [!IF "$Ccu6KernelUserInfo = num:i(5)"!][!// User is ICU
    [!IF "node:exists(as:modconf('Icu')[1])"!]
      [!VAR "Ccu6CompConfigInIcu" = "num:i(0)"!][!//
      [!SELECT "as:modconf('Icu')[1]"!][!//
        [!LOOP "IcuConfigSet/IcuChannel/*"!][!//
          [!VAR "Ccu6KernelUser" = "$Ccu6KernelUserInfo"!][!//
          [!IF "node:exists(./CCU6CC6Configuration/*[1])"!][!//
            [!VAR "Ccu6KernelRef"= "./CCU6CC6Configuration/*[1]/CCU6KernelUsed"!][!//
            [!VAR "Ccu6KernelNo" = "substring-after($Ccu6KernelRef,'McuCcu6ModuleAllocationConf_')"!][!//
            [!IF "$Ccu6KernelNo = $Ccu6KernelNumber"!][!//
              [!VAR "LogicalChannelId" = "./IcuChannelId"!][!//
              [!VAR "Ccu6CompConfigInIcu" = "num:i(1)"!][!//
              [!VAR "Ccu6KernelUser" = "bit:or($Ccu6KernelUser,bit:shl($LogicalChannelId,num:i(8)))"!][!//
              [!VAR "Ccu6Comparator"= "./CCU6CC6Configuration/*[1]/Cc6xChannel"!][!//
              [!IF "$Ccu6Comparator = 'Cc60'"!][!//
                [!VAR "Cc60UserInfo" = "$Ccu6KernelUser"!][!//
              [!ELSEIF "$Ccu6Comparator = 'Cc61'"!][!//
                [!VAR "Cc61UserInfo" = "$Ccu6KernelUser"!][!//
              [!ELSEIF "$Ccu6Comparator = 'Cc62'"!][!//
                [!VAR "Cc62UserInfo" = "$Ccu6KernelUser"!][!//
              [!ELSE!][!//
                [!VAR "Cc63UserInfo" = "$Ccu6KernelUser"!][!//
              [!ENDIF!][!//
            [!ENDIF!][!//
          [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "$Ccu6CompConfigInIcu = num:i(0)"!][!//
          [!ERROR!][!//
          ERROR: CCU6 Kernel[!"$Ccu6KernelNumber"!] allocated for ICU in Mcu Hardware Resource Allocation is not configured in ICU module. Unreserve the CCU6 kernel in MCU.
          [!ENDERROR!][!//
        [!ENDIF!][!//
      [!ENDSELECT!][!//
    [!ELSE!][!//
    [!ERROR!][!//
    ERROR: CCU6 Kernel[!"$Ccu6KernelNumber"!] is allocated for ICU in Mcu Hardware Resource Allocation, but ICU module is not part of Configuration generation project.Unreserve the CCU6 kernel in MCU.
    [!ENDERROR!][!//
    [!ENDIF!][!//
  [!ELSEIF "$Ccu6KernelUserInfo = num:i(3)"!][!// User is PWM
    [!IF "node:exists(as:modconf('Pwm')[1])"!]
      [!VAR "Ccu6CompConfigInPwm" = "num:i(0)"!][!//
      [!SELECT "as:modconf('Pwm')[1]"!][!//
        [!LOOP "PwmChannelConfigSet/PwmChannel/*"!][!//
          [!VAR "Ccu6KernelUser" = "$Ccu6KernelUserInfo"!][!//
          [!IF "node:exists(./CCU6CC6Configuration/*[1])"!][!//
            [!VAR "Ccu6KernelRef"= "./CCU6CC6Configuration/*[1]/CCU6KernelUsed"!][!//
            [!VAR "Ccu6KernelNo" = "substring-after($Ccu6KernelRef,'McuCcu6ModuleAllocationConf_')"!][!//
            [!IF "$Ccu6KernelNo = $Ccu6KernelNumber"!][!//
              [!VAR "LogicalChannelId" = "./PwmChannelId"!][!//
              [!VAR "Ccu6CompConfigInPwm" = "num:i(1)"!][!//
              [!VAR "Ccu6KernelUser" = "bit:or($Ccu6KernelUser,bit:shl($LogicalChannelId,num:i(8)))"!][!//
              [!VAR "Ccu6Comparator"= "./CCU6CC6Configuration/*[1]/Cc6xChannel"!][!//
              [!VAR "Ccu6TimerTypeUsed"= "./CCU6CC6Configuration/*[1]/CCU6TimerUsed"!][!//
              [!IF "$Ccu6TimerTypeUsed = 'T12'"!][!//
                [!IF "$Ccu6Comparator = 'Cc60'"!][!//
                  [!VAR "Cc60UserInfo" = "$Ccu6KernelUser"!][!//
                [!ELSEIF "$Ccu6Comparator = 'Cc61'"!][!//
                  [!VAR "Cc61UserInfo" = "$Ccu6KernelUser"!][!//
                [!ELSE!][!//
                  [!VAR "Cc62UserInfo" = "$Ccu6KernelUser"!][!//
                [!ENDIF!][!//
              [!ENDIF!][!//
              [!IF "$Ccu6TimerTypeUsed = 'T13'"!][!//
                  [!VAR "Cc63UserInfo" = "$Ccu6KernelUser"!][!//
              [!ENDIF!][!//
            [!ENDIF!][!//
          [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "$Ccu6CompConfigInPwm = num:i(0)"!][!//
          [!ERROR!][!//
          ERROR: CCU6 Kernel[!"$Ccu6KernelNumber"!] allocated for PWM in Mcu Hardware Resource Allocation is not configured in PWM module. Unreserve the CCU6 kernel in MCU.
          [!ENDERROR!][!//
        [!ENDIF!][!//
      [!ENDSELECT!][!//
    [!ELSE!][!//
      [!ERROR!][!//
      ERROR: CCU6 Kernel[!"$Ccu6KernelNumber"!] is allocated for PWM in Mcu Hardware Resource Allocation, but PWM module is not part of Configuration generation project.Unreserve the CCU6 kernel in MCU.
      [!ENDERROR!][!//
    [!ENDIF!][!//
  [!ELSEIF "$Ccu6KernelUserInfo = num:i(1)"!][!// User is ADC
    [!IF "node:exists(as:modconf('Adc')[1])"!]
      [!VAR "Cc60UserInfo" = "num:i(1)"!][!//
      [!VAR "Cc61UserInfo" = "num:i(1)"!][!//
      [!VAR "Cc62UserInfo" = "num:i(1)"!][!//
      [!VAR "Cc63UserInfo" = "num:i(1)"!][!//
    [!ELSE!][!//
      [!ERROR!][!//
      ERROR: CCU6 Kernel[!"$Ccu6KernelNumber"!] is allocated for ADC in Mcu Hardware Resource Allocation, but ADC module is not part of Configuration generation project.Unreserve the CCU6 kernel in MCU.
      [!ENDERROR!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//


/*******************************************************************************
** Name             : Mcu_17_TimerIp_CG_ConfigGpt12UserData                   **
**                                                                            **
** Description      : Macro to calculate the user data for GPT12 timers       **
*******************************************************************************/
[!MACRO "Mcu_17_TimerIp_CG_ConfigGpt12UserData", "Gpt12BlockUserInfo"= "", "Node" = "", "Gpt12UserData" = ""!][!//
[!NOCODE!][!//
[!VAR "Gpt12UserID" = "num:i(0)"!]
[!VAR "IcuFlag" = "num:i(0)"!]
  [!/* Verify and Calculate User Data for ICU */!]
  [!IF "$Gpt12BlockUserInfo = 'Icu'"!]
    [!IF "node:exists(as:modconf('Icu')[1])"!]
      [!SELECT "as:modconf('Icu')[1]"!]
        [!LOOP "IcuConfigSet/IcuChannel/*"!]
          [!IF "node:exists(./GPT12Configuration/*[1])"!]
            [!VAR "Gpt12UserID" = "num:i(5)"!][!// Set ICU User ID as '5'
            [!VAR "GptChannelRef"= "./GPT12Configuration/*[1]/GPT12BlockReference"!][!//
            [!VAR "Gpt12Used" = "substring-after($GptChannelRef,'McuHardwareResourceAllocationConf_0/')"!][!//
            [!IF "$Gpt12Used = $Node"!][!// Match found
              [!VAR "IcuFlag" = "num:i(1)"!]
              [!VAR "LogicalChannelId" = "./IcuChannelId"!]
              [!VAR "Gpt12UserID" = "bit:or($Gpt12UserID,bit:shl($LogicalChannelId,num:i(8)))"!]
              [!VAR "GptTimerSelected"= "./GPT12Configuration/*[1]/GPT12TimerSelection"!]
              [!/* RegEx for fetching the Timer Used and Modifying User Data */!]
              [!VAR "fetchGptTimerSelected" = "concat( '^', $GptTimerSelected, '.*$' )"!]
              [!VAR "Gpt12UserDataSelected" = "translate(text:grep(text:split($Gpt12UserData, ','), $fetchGptTimerSelected), '[]', '')"!]
              [!VAR "ModifyGpt12UserDataMod" = "text:replaceAll($Gpt12UserDataSelected, '0', $Gpt12UserID)"!]
              [!VAR "Gpt12UserData" = "text:replaceAll($Gpt12UserData, $Gpt12UserDataSelected, $ModifyGpt12UserDataMod)"!]
            [!ENDIF!]
          [!ENDIF!]
        [!ENDLOOP!]
        [!IF "$IcuFlag  = num:i(0)"!][!//
          [!ERROR!][!//
          ERROR: GPT Block [!"substring-after($Node,'McuGpt12ModuleAllocationConf_')"!] allocated for [!"$Gpt12BlockUserInfo"!] in Mcu Hardware Resource Allocation is not configured in [!"$Gpt12BlockUserInfo"!] module. Unreserve the GPT block in MCU.
          [!ENDERROR!][!//
        [!ENDIF!]
      [!ENDSELECT!][!//
    [!ELSE!][!//
      [!ERROR!][!//
      ERROR: GPT Block [!"substring-after($Node,'McuGpt12ModuleAllocationConf_')"!] is allocated for [!"$Gpt12BlockUserInfo"!] in Mcu Hardware Resource Allocation, but [!"$Gpt12BlockUserInfo"!] module is not part of Configuration generation project. Unreserve the GPT block in MCU.
      [!ENDERROR!][!//
    [!ENDIF!][!//
  [!/* Notify User that Complex Driver cannot be verified */!]
  [!/* Calculate User Data for Complex Driver */!]
  [!ELSE!][!//
    [!WARNING!]
      WARNING: Complex Driver cannot be verified, User needs to take care
    [!ENDWARNING!]
    [!VAR "Gpt12UserID" = "num:i(6)"!][!// Set Complex Driver User ID as '6'
    [!VAR "LogChIDNode" = "concat($Node, '/McuGpt12ComplexDriverLogicalChannelId')"!][!//
    [!VAR "TimerSelectedNode" = "concat($Node, '/McuGpt12ComplexDriverTimerSelection')"!][!//
    [!VAR "LogicalChannelId" = "node:value($LogChIDNode)"!][!//
    [!VAR "GptTimerSelected" = "node:value($TimerSelectedNode)"!][!//
    [!VAR "Gpt12UserID" = "bit:or($Gpt12UserID,bit:shl($LogicalChannelId,num:i(8)))"!][!//
    [!/* RegEx for fetching the Timer Used and Modifying User Data */!]
    [!VAR "fetchGptTimerSelected" = "concat( '^', $GptTimerSelected, '.*$' )"!]
    [!VAR "Gpt12UserDataSelected" = "translate(text:grep(text:split($Gpt12UserData, ','), $fetchGptTimerSelected), '[]', '')"!]
    [!VAR "ModifyGpt12UserDataMod" = "text:replaceAll($Gpt12UserDataSelected, '0', $Gpt12UserID)"!]
    [!VAR "Gpt12UserData" = "text:replaceAll($Gpt12UserData, $Gpt12UserDataSelected, $ModifyGpt12UserDataMod)"!]
  [!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//


/*******************************************************************************
** Name             : Mcu_17_TimerIp_CG_ConfigStmUserData                     **
**                                                                            **
** Description      : Macro to calculate the user data for STM timers         **
*******************************************************************************/
[!MACRO "Mcu_17_TimerIp_CG_ConfigStmUserData", "StmUserInfo"= "", "Node" = "", "StmCmp" = "", "StmUserData" = ""!][!//
[!NOCODE!]
[!VAR "StmUserID" = "num:i(0)"!]
[!VAR "StmFlag" = "num:i(0)"!]
[!VAR "Stmdata" = "num:i(0)"!]
[!/* Verify STM allocation for WDG */!]
[!IF "$StmUserInfo = 'Wdg'"!]
  [!VAR "StmUserID" = "num:i(2)"!][!// Set WDG User ID as '2'
  [!IF "node:exists(as:modconf('ResourceM')[1])"!]
    [!SELECT "as:modconf('ResourceM')[1]"!]
      [!SELECT "ResourceMMcalConfig/*[1]/ResourceMMcalCore/*"!][!//
        [!VAR "RMCoreID" = "substring-after(./ResourceMCoreID, 'CORE')"!][!//
        [!SELECT "ResourceMAllocation/*"!][!//
          [!IF "'STM' = ./ResourceMModuleName"!][!//
            [!VAR "StmFlag" = "num:i(1)"!]
            [!IF "node:refvalid(./ResourceMResourceRef)"!]
              [!VAR "index" = "num:i(count(text:split(./ResourceMResourceRef, '/')))"!][!//
              [!VAR "ResourceName" = "text:split(./ResourceMResourceRef, '/')[num:i($index)]"!][!//
              [!IF "$ResourceName = $Node"!]
                [!/* Search the core in WDG */!]
                [!IF "node:exists(as:modconf('Wdg')[1])"!][!//
                  [!SELECT "as:modconf('Wdg')[1]"!][!//
                    [!IF "((node:exists(./WdgSettingsConfig/*[WdgCoreId = num:i($RMCoreID)])) and (./WdgGeneral/WdgTriggerTimerSelection = 'STM_TIMER'))"!]
                      [!SELECT "as:modconf($StmUserInfo)[1]"!]
                        [!VAR "StmId"= "concat('STM#', substring-after($ResourceName, 'McuStmAllocationConf_'))"!]
                        [!/* RegEx for fetching the Timer Used and Modifying User Data */!]
                        [!VAR "fetchStmSelected" = "concat( '^', $StmId, '.*$' )"!]
                        [!VAR "StmUserDataSelected" = "translate(text:grep(text:split($StmUserData, ','), $fetchStmSelected), '[]', '')"!]
                        [!IF "num:i($StmCmp) = num:i(1)"!]
                          [!VAR "Stmdata" = "bit:or(bit:shl($StmUserID, num:i(8)), $StmCmp)"!]
                        [!ELSEIF "num:i($StmCmp) = num:i(2)"!]
                          [!VAR "Stmdata" = "bit:or(bit:shl($StmUserID, num:i(24)), bit:shl($StmCmp, num:i(16)))"!]
                        [!ENDIF!]
                        [!VAR "Stmdata" = "bit:or(substring-after($StmUserDataSelected, '_'), $Stmdata)"!]
                        [!VAR "ModifyStmUserData" = "text:concat(substring-before($StmUserDataSelected, '_'), concat('_', $Stmdata))"!]
                        [!VAR "ModifyStmUserData" = "translate($ModifyStmUserData, '[]', '')"!]
                        [!VAR "StmUserData" = "text:replaceAll($StmUserData, $StmUserDataSelected, $ModifyStmUserData)"!]
                      [!ENDSELECT!]
                    [!ELSE!]
                      [!ERROR!][!//
                      ERROR: STM Timer [!"substring-after($Node,'McuStmAllocationConf_')"!] allocated for [!"$StmUserInfo"!] in Mcu Hardware Resource Allocation is not configured in [!"$StmUserInfo"!] module. Unreserve the STM Timer in MCU.
                      [!ENDERROR!][!//
                    [!ENDIF!]
                  [!ENDSELECT!]
                [!ELSE!]
                  [!ERROR!][!//
                    ERROR: STM Timer [!"substring-after($Node,'McuStmAllocationConf_')"!] allocated for [!"$StmUserInfo"!] in Mcu Hardware Resource Allocation, but [!"$StmUserInfo"!] module is not part of Configuration generation project. Unreserve the STM Timer [!"substring-after($Node,'McuStmAllocationConf_')"!] in MCU.
                  [!ENDERROR!][!//
                [!ENDIF!]
              [!ENDIF!]
            [!ENDIF!]
          [!ENDIF!]
        [!ENDSELECT!]
      [!ENDSELECT!]
    [!ENDSELECT!][!//
  [!ENDIF!]
[!ELSEIF "$StmUserInfo = 'Stm'"!]
  [!VAR "StmUserID" = "num:i(8)"!][!// Set STM User ID as '8'
  [!IF "node:exists(as:modconf('ResourceM')[1])"!]
    [!SELECT "as:modconf('ResourceM')[1]"!]
      [!SELECT "ResourceMMcalConfig/*[1]/ResourceMMcalCore/*"!][!//
        [!SELECT "ResourceMAllocation/*"!][!//
          [!IF "'STM' = ./ResourceMModuleName"!][!//
            [!IF "node:refvalid(./ResourceMResourceRef)"!]
              [!VAR "index" = "num:i(count(text:split(./ResourceMResourceRef, '/')))"!][!//
              [!VAR "ResourceName" = "text:split(./ResourceMResourceRef, '/')[num:i($index)]"!][!//
              [!IF "$ResourceName = $Node"!]
                [!VAR "StmFlag" = "num:i(1)"!]
                [!VAR "StmId"= "concat('STM#', substring-after($ResourceName, 'McuStmAllocationConf_'))"!]
                [!/* RegEx for fetching the Timer Used and Modifying User Data */!]
                [!VAR "fetchStmSelected" = "concat( '^', $StmId, '.*$' )"!]
                [!VAR "StmUserDataSelected" = "translate(text:grep(text:split($StmUserData, ','), $fetchStmSelected), '[]', '')"!]
                [!IF "num:i($StmCmp) = num:i(1)"!]
                  [!VAR "Stmdata" = "bit:or(bit:shl($StmUserID, num:i(8)), $StmCmp)"!]
                [!ELSEIF "num:i($StmCmp) = num:i(2)"!]
                  [!VAR "Stmdata" = "bit:or(bit:shl($StmUserID, num:i(24)), bit:shl($StmCmp, num:i(16)))"!]
                [!ELSE!]
                  [!VAR "Stmdata1" = "bit:or(bit:shl($StmUserID, num:i(24)), bit:shl($StmCmp, num:i(16)))"!]
                  [!VAR "Stmdata2" = "bit:or(bit:shl($StmUserID, num:i(8)), $StmCmp)"!]
                  [!VAR "Stmdata"  = "bit:or($Stmdata1, $Stmdata2)"!]
                [!ENDIF!]
                [!VAR "Stmdata" = "bit:or(substring-after($StmUserDataSelected, '_'), $Stmdata)"!]
                [!VAR "ModifyStmUserData" = "text:concat(substring-before($StmUserDataSelected, '_'), concat('_', $Stmdata))"!]
                [!VAR "ModifyStmUserData" = "translate($ModifyStmUserData, '[]', '')"!]
                [!VAR "StmUserData" = "text:replaceAll($StmUserData, $StmUserDataSelected, $ModifyStmUserData)"!]
              [!ENDIF!]
            [!ENDIF!]
          [!ENDIF!]
        [!ENDSELECT!]
      [!ENDSELECT!]
    [!ENDSELECT!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$StmFlag  = num:i(0)"!][!//
  [!ERROR!][!//
  ERROR: STM Timer [!"substring-after($Node,'McuStmAllocationConf_')"!] allocated for [!"$StmUserInfo"!] in Mcu Hardware Resource Allocation is not configured in Resource Manager. Unreserve the STM Timer in MCU.
  [!ENDERROR!][!//
[!ENDIF!]
[!ENDNOCODE!]
[!ENDMACRO!]


/*******************************************************************************
** Name             : Mcu_17_TimerIp_CG_ConfigERUUserData                     **
**                                                                            **
** Description      : Macro to calculate the user data for ERU Channels       **
*******************************************************************************/
[!MACRO "Mcu_17_TimerIp_CG_ConfigEruUserData", "EruChUserInfo"= "", "Node" = "", "EruChType" = "", "EruUserData" =""!][!//
[!NOCODE!]
[!VAR "EruUserID" = "num:i(0)"!]
[!VAR "IcuFlag" = "num:i(0)"!]
[!VAR "AdcFlag" = "num:i(0)"!]
[!/* Verify Channel allocation for ICU */!]
[!IF "$EruChUserInfo = 'Icu'"!]
  [!VAR "EruUserID" = "num:i(5)"!][!// Set ICU User ID as '5'
  [!IF "node:exists(as:modconf('Icu')[1])"!]
    [!SELECT "as:modconf('Icu')[1]"!]
      [!LOOP "IcuConfigSet/IcuChannel/*"!]
        [!IF "node:exists(./ERUInputConfiguration/*[1])"!]
          [!IF "$EruChType = 'OUT'"!]
            [!VAR "EruChannelRef"= "./ERUInputConfiguration/*[1]/EruOguReference"!][!//
          [!ELSE!]
            [!VAR "EruChannelRef"= "./ERUInputConfiguration/*[1]/EruErsReference"!][!//
          [!ENDIF!]
          [!VAR "EruUsed" = "substring-after($EruChannelRef,'McuHardwareResourceAllocationConf_0/')"!][!//
          [!VAR "EruUsed" = "substring-after($EruUsed,'/')"!][!//
          [!IF "$EruUsed = $Node"!][!// Match found
            [!VAR "IcuFlag" = "num:i(1)"!]
            [!IF "$EruChType = 'OUT'"!]
              [!VAR "LogicalChannelId" = "./IcuChannelId"!]
              [!VAR "EruInpTimerSelected"= "substring-after(./ERUInputConfiguration/*[1]/EruErsReference, 'McuEruChannelInputLineConf_')"!]
              [!VAR "OguId"= "concat('OGU#', substring-after($EruUsed,'_'))"!]
              [!VAR "EruData" = "bit:or(bit:shl($EruUserID, num:i(16)), bit:shl($LogicalChannelId,num:i(8)))"!]
              [!VAR "EruData" = "bit:or($EruData, num:i($EruInpTimerSelected))"!]
              [!/* RegEx for fetching the Timer Used and Modifying User Data */!]
              [!VAR "fetchOguSelected" = "concat( '^', $OguId, '.*$' )"!]
              [!VAR "EruUserDataSelected" = "translate(text:grep(text:split($EruUserData, ','), $fetchOguSelected), '[]', '')"!]
              [!VAR "ModifyEruUserData" = "text:replaceAll($EruUserDataSelected, '_0', concat('_', $EruData))"!]
              [!VAR "EruUserData" = "text:replaceAll($EruUserData, $EruUserDataSelected, $ModifyEruUserData)"!]
            [!ENDIF!]
          [!ENDIF!]
        [!ENDIF!]
      [!ENDLOOP!]
      [!IF "$IcuFlag  = num:i(0)"!][!//
        [!IF "$EruChType = 'OUT'"!]
          [!ERROR!][!//
          ERROR: ERU Output Channel [!"substring-after($Node,'McuEruChannelOutputUnitConf_')"!] allocated for [!"$EruChUserInfo"!] in Mcu Hardware Resource Allocation is not configured in [!"$EruChUserInfo"!] module. Unreserve the ERU Output Channel [!"substring-after($Node,'McuEruChannelOutputUnitConf_')"!] in MCU.
          [!ENDERROR!][!//
        [!ELSE!]
          [!ERROR!][!//
          ERROR: ERU Input Channel [!"substring-after($Node,'McuEruChannelInputLineConf_')"!] allocated for [!"$EruChUserInfo"!] in Mcu Hardware Resource Allocation is not configured in [!"$EruChUserInfo"!] module. Unreserve the ERU Input Channel [!"substring-after($Node,'McuEruChannelInputLineConf_')"!] in MCU.
          [!ENDERROR!][!//
        [!ENDIF!]
      [!ENDIF!]
    [!ENDSELECT!][!//
  [!ELSE!][!//
    [!IF "$EruChType = 'OUT'"!]
      [!ERROR!][!//
      ERROR: ERU Output Channel [!"substring-after($Node,'McuEruChannelOutputUnitConf_')"!] is allocated for [!"$EruChUserInfo"!] in Mcu Hardware Resource Allocation, but [!"$EruChUserInfo"!] module is not part of Configuration generation project. Unreserve the ERU Output Channel [!"substring-after($Node,'McuEruChannelOutputUnitConf_')"!] in MCU.
      [!ENDERROR!][!//
    [!ELSE!]
      [!ERROR!][!//
      ERROR: ERU Input Channel [!"substring-after($Node,'McuEruChannelInputLineConf_')"!] is allocated for [!"$EruChUserInfo"!] in Mcu Hardware Resource Allocation, but [!"$EruChUserInfo"!] module is not part of Configuration generation project. Unreserve the ERU Input Channel [!"substring-after($Node,'McuEruChannelInputLineConf_')"!] in MCU.
      [!ENDERROR!][!//
    [!ENDIF!]
  [!ENDIF!][!//
[!ELSEIF "$EruChUserInfo = 'Adc'"!][!// User is ADC
    [!IF "node:exists(as:modconf('Adc')[1])"!][!//
      [!SELECT "as:modconf('Adc')[1]/AdcConfigSet/AdcHwUnit/*/AdcGroup/*"!][!//
          [!IF "node:exists(./EruTriggerConfig/*[1])"!]
            [!IF "$EruChType = 'OUT'"!]
              [!VAR "EruChannelRef"= "./EruTriggerConfig/*[1]/AdcEruOguRef"!][!//
            [!ELSE!]
              [!VAR "EruChannelRef"= "./EruTriggerConfig/*[1]/AdcEruErsRef"!][!//
            [!ENDIF!]
            [!VAR "EruUsed" = "substring-after($EruChannelRef,'McuHardwareResourceAllocationConf_0/')"!][!//
            [!VAR "EruUsed" = "substring-after($EruUsed,'/')"!][!//
            [!IF "$EruUsed = $Node"!][!// Match found
              [!VAR "AdcFlag" = "num:i(1)"!]
            [!ENDIF!]
          [!ENDIF!]
         [!IF "node:exists(./EruGatingConfig/*[1])"!]
            [!IF "$EruChType = 'OUT'"!]
              [!VAR "EruChannelRef"= "./EruGatingConfig/*[1]/AdcEruOguRef"!][!//
            [!ELSE!]
              [!VAR "EruChannelRef"= "./EruGatingConfig/*[1]/AdcEruErsRef"!][!//
            [!ENDIF!]
            [!VAR "EruUsed" = "substring-after($EruChannelRef,'McuHardwareResourceAllocationConf_0/')"!][!//
            [!VAR "EruUsed" = "substring-after($EruUsed,'/')"!][!//
            [!IF "$EruUsed = $Node"!][!// Match found
              [!VAR "AdcFlag" = "num:i(1)"!]
            [!ENDIF!]
         [!ENDIF!]
      [!ENDSELECT!][!//
      [!IF "$AdcFlag = num:i(0)"!]
        [!IF "$EruChType = 'OUT'"!]
          [!ERROR!][!//
          ERROR: ERU Output Channel [!"substring-after($Node,'McuEruChannelOutputUnitConf_')"!] allocated for [!"$EruChUserInfo"!] in Mcu Hardware Resource Allocation is not configured in [!"$EruChUserInfo"!] module. Unreserve the ERU Output Channel [!"substring-after($Node,'McuEruChannelOutputUnitConf_')"!] in MCU.
          [!ENDERROR!][!//
        [!ELSE!]
          [!ERROR!][!//
          ERROR: ERU Input Channel [!"substring-after($Node,'McuEruChannelInputLineConf_')"!] allocated for [!"$EruChUserInfo"!] in Mcu Hardware Resource Allocation is not configured in [!"$EruChUserInfo"!] module. Unreserve the ERU Input Channel [!"substring-after($Node,'McuEruChannelInputLineConf_')"!] in MCU.
          [!ENDERROR!][!//
        [!ENDIF!]
      [!ENDIF!]
      [!ELSE!][!//
    [!IF "$EruChType = 'OUT'"!]
      [!ERROR!][!//
      ERROR: ERU Output Channel [!"substring-after($Node,'McuEruChannelOutputUnitConf_')"!] is allocated for [!"$EruChUserInfo"!] in Mcu Hardware Resource Allocation, but [!"$EruChUserInfo"!] module is not part of Configuration generation project. Unreserve the ERU Output Channel [!"substring-after($Node,'McuEruChannelOutputUnitConf_')"!] in MCU.
      [!ENDERROR!][!//
    [!ELSE!]
      [!ERROR!][!//
      ERROR: ERU Input Channel [!"substring-after($Node,'McuEruChannelInputLineConf_')"!] is allocated for [!"$EruChUserInfo"!] in Mcu Hardware Resource Allocation, but [!"$EruChUserInfo"!] module is not part of Configuration generation project. Unreserve the ERU Input Channel [!"substring-after($Node,'McuEruChannelInputLineConf_')"!] in MCU.
      [!ENDERROR!][!//
    [!ENDIF!]
    [!ENDIF!]
[!ENDIF!][!//
[!ENDNOCODE!]
[!ENDMACRO!]

[!ENDIF!][!// IF "not(var:defined('MCU_17_TIMERIP_M'))
