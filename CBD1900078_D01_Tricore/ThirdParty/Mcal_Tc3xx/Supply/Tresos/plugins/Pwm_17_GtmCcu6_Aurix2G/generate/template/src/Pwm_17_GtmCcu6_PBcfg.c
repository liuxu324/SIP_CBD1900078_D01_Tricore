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
**  FILENAME  : Pwm_17_GtmCcu6_PBcfg.c                                        **
**                                                                            **
**  VERSION   : 9.0.0                                                         **
**                                                                            **
**  DATE      : 2018-09-22                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Pwm.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY :                                                            **
**                                                                            **
**  DESCRIPTION  : Code template source file for Pwm Driver                   **
**                                                                            **
**                                                                            **
**                                                                            **
**  SPECIFICATION(S) : Specification of Pwm Driver, AUTOSAR Release 4.2.2     **
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
**  FILENAME  : Pwm_17_GtmCcu6_PBcfg.c                                        **
**                                                                            **
**  VERSION   : 8.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                                      **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                                          **
**                                                                            **
**  BSW MODULE DECRIPTION : Pwm.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Pwm configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Pwm Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
[!NOCODE!]
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

[!INCLUDE "Pwm_17_GtmCcu6.m"!][!//
[!ENDNOCODE!]

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/* Include module header File */
#include "Pwm_17_GtmCcu6.h"
#include "Mcu_17_TimerIp.h"
/* [cover parentID={E86E979E-8B2D-4605-BF57-7FFD88121727}]
  Generated File containing objects to data structures
[/cover] */
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
/*
Pre Compile time parameters are placed in Pwm_Cfg.h
*/
/* Precompile macros for Alternate port pin selection  */
/* [cover parentID={773C76D6-1285-4e38-9D78-FB3A595E2C45}]
 GtmTimerPortPinSelect [/cover]*/
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Usage of this macro depends upon configuration done in tresos*/
#define PWM_ALT_SELA ((uint16)0x00)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Usage of this macro depends upon configuration done in tresos*/
#define PWM_ALT_SELB ((uint16)0x01)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Usage of this macro depends upon configuration done in tresos*/
#define PWM_ALT_SELC ((uint16)0x02)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Usage of this macro depends upon configuration done in tresos*/
#define PWM_ALT_SELD ((uint16)0x03)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Usage of this macro depends upon configuration done in tresos*/
#define PWM_ALT_SELE ((uint16)0x04)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Usage of this macro depends upon configuration done in tresos*/
#define PWM_ALT_SELF ((uint16)0x05)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Usage of this macro depends upon configuration done in tresos*/
#define PWM_ALT_SELG ((uint16)0x06)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Usage of this macro depends upon configuration done in tresos*/
#define PWM_ALT_SELH ((uint16)0x07)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Usage of this macro depends upon configuration done in tresos*/
#define PWM_ALT_SELI ((uint16)0x08)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Usage of this macro depends upon configuration done in tresos*/
#define PWM_ALT_SELJ ((uint16)0x09)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Usage of this macro depends upon configuration done in tresos*/
#define PWM_ALT_SELK ((uint16)0x0A)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
  Usage of this macro depends upon configuration done in tresos*/
#define PWM_ALT_SELL ((uint16)0x0B)
/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/
/*
Configuration:
PWM Channel Configuration:
Elements / Attributes
1. Notification function pointer (if required)
2. Shift Value, only for PWM_FIXED_PERIOD_SHIFTED Class
   Input a value between 0 and 0x8000.
3. Default Duty Cycle ( duty cycle value between
   0 and 0x8000)
4. Pwm_Period:
   Enter in ticks
   PWM070: All time units should be in ticks.
5. Pwm_ConfigChannel:
   Go in the following parameter order
   a) Reference to Channel Number, for a Shifted, Center Aligned and
   Zero Shifted channel, a reference must be given. For a variable
   and Fixed Period channel class, reference should not be given.
   Reference should be given in the form of channel number index.
   b) Channel Class
      Possible Options: PWM_FIXED_PERIOD, PWM_FIXED_PERIOD_SHIFTED,
      PWM_FIXED_PERIOD_CENTER_ALIGNED, PWM_VARIABLE_PERIOD
   c) Channel Idle State:
      Possible Options: PWM_LOW, PWM_HIGH
      Output line goes into Idle state either after Pwm_SetOutputtoIdle
      or Pwm_DeInit.
   d) Channel Polarity:
      Possible Options: PWM_LOW, PWM_HIGH
      Initial Polarity state of the channel.
   e) GTM timer Configuration:
      Select timer reference :TOM/ATOM.
      Clockselect and port pin.
 */
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
/*
Function Like Macro:Pwm_lConfigChannel
Macro that packs the PWM Channel Information.
Input Parameters:
ShiftReset: Shifted channel is reset by itself or by other channel
ChannelClass : Channel Class
ChannelCoherency : Channel Coherency
IdleState : Idle State
Polarity : Channel Polarity
AssignedHwUnit : Hardware Unit Used
*/
/*MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is used to reduce the
  memory usage */
#define Pwm_lConfigChannel(ShiftReset,                   \
                           ChannelClass,                 \
                           ChannelCoherency,             \
                           IdleState,                    \
                           Polarity)                     \
              ((uint16)( ((ShiftReset) << 5U)          |   \
                         ((ChannelClass) << 3U)        |   \
                         ((ChannelCoherency) << 2U)    |   \
                         ((IdleState) << 1U)           |   \
                         ((Polarity))                       \
                       ))
/******************************************************************************/
/******************************************************************************/
[!SELECT "as:modconf('Pwm')[1]"!][!//
[!NOCODE!]
[!VAR "MaxChannels"= "num:i(count(PwmChannelConfigSet/PwmChannel/*))"!][!//

[!VAR "PwmHandleShiftOffset" = "'false'"!][!//
[!IF "node:exists(PwmGeneral/PwmHandleShiftByOffset)"!][!//
[!IF "PwmGeneral/PwmHandleShiftByOffset  = 'true'"!]
[!VAR "PwmHandleShiftOffset" = "'true'"!][!//
[!ENDIF!][!//
[!ENDIF!][!//

[!VAR "Notification" = "'STD_OFF'"!]
[!IF "PwmGeneral/PwmNotificationSupported = 'true'"!]
[!VAR "Notification" = "'STD_ON'"!]
[!ENDIF!]

[!VAR "DutyShiftInTicks" = "'false'"!][!//
[!IF "node:exists(PwmGeneral/PwmDutyShiftInTicks)"!][!//
[!VAR "DutyShiftInTicks" = "PwmGeneral/PwmDutyShiftInTicks"!][!//
[!ENDIF!][!//

[!VAR "DutyCycleEndPeriodNeeded" = "'false'"!][!//
[!VAR "PeriodEndPeriodNeeded" = "'false'"!][!//

[!IF "node:exists(PwmGeneral/PwmDutycycleUpdatedEndperiod)"!][!//
[!VAR "DutyCycleEndPeriodNeeded" = "node:value(PwmGeneral/PwmDutycycleUpdatedEndperiod)"!][!//
[!ENDIF!][!//

[!IF "node:exists(PwmGeneral/PwmPeriodUpdatedEndperiod)"!][!//
[!VAR "PeriodEndPeriodNeeded" = "node:value(PwmGeneral/PwmPeriodUpdatedEndperiod)"!][!//
[!ENDIF!][!//

/* [cover parentID={DBB4E018-E652-497f-8440-E0A1C7BE293A}]
 extern definition for notification function [/cover]*/
/* 1 Generate_Notification functions*/
[!ENDNOCODE!][!//
[!LOOP "PwmChannelConfigSet/PwmChannel/*"!][!//
[!IF "$Notification = 'STD_ON'"!][!//
[!IF "node:exists(./PwmNotification/*[1])"!][!//
[!VAR "Notify" = "./PwmNotification/*[1]"!][!//
[!ELSE!][!//
[!VAR "Notify" = "'(Pwm_17_GtmCcu6_NotifiPtrType)0'"!][!//
[!ENDIF!][!//
[!IF "string-length($Notify) = 0"!][!//
[!VAR "Notify" = "'(Pwm_17_GtmCcu6_NotifiPtrType)0'"!][!//
[!ENDIF!][!//
[!IF "$Notify = '"NULL_PTR"' or $Notify = 'NULL_PTR'"!][!//
[!VAR "Notify" = "'(Pwm_17_GtmCcu6_NotifiPtrType)0'"!][!//
[!ENDIF!][!//
[!IF "$Notify != '(Pwm_17_GtmCcu6_NotifiPtrType)0'"!][!//       
[!IF "num:isnumber($Notify) != 'true'"!][!//
extern void [!"$Notify"!] (void); /*[!"node:name(.)"!]*/
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//

[!NOCODE!]
[!VAR "CCU6resourceMap" = "''"!][!//
[!VAR "CCU6resourceMapChId" = "''"!][!//
[!LOOP "PwmChannelConfigSet/PwmChannel/*"!][!//
[!VAR "ChannelID" = "./PwmChannelId"!][!//
[!VAR "TempTimerUsed" = "./PwmAssignedHwUnit"!][!//
[!IF "$TempTimerUsed = 'CCU6'"!][!//
[!VAR "CCU6TimerUsed" = "CCU6CC6Configuration/*[1]/CCU6TimerUsed"!][!//
[!VAR "Kernel" = "num:i(substring-after(CCU6CC6Configuration/*[1]/CCU6KernelUsed,'McuCcu6ModuleAllocationConf_'))"!][!//
[!VAR "CCU6CompUsed" = "'Cc63'"!][!//
[!IF "$CCU6TimerUsed = 'T12'"!][!//
[!VAR "CCU6CompUsed" = "CCU6CC6Configuration/*[1]/Cc6xChannel"!][!//
[!ENDIF!][!//
[!VAR "CCU6resourceMap" = "concat($CCU6resourceMap,'_',$Kernel,'_',$CCU6TimerUsed,'_',$CCU6CompUsed,',')"!][!//
[!VAR "CCU6resourceMapChId" = "concat($CCU6resourceMapChId,'_',$Kernel,'_',$CCU6TimerUsed,'_',$CCU6CompUsed,'_ID',$ChannelID,',')"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!][!//

[!VAR "kernel" = "num:i(0)"!][!//
[!VAR "Timer" = "num:i(0)"!][!//
[!VAR "Channel" = "num:i(0)"!][!//
[!VAR "comp" = "num:i(0)"!][!//
[!VAR "Channel" = "num:i(0)"!][!//
[!VAR "TempId" = "num:i(0)"!][!//
[!VAR "ErrorFound" = "num:i(0)"!][!//
[!LOOP "text:split($CCU6resourceMap,',')"!][!//
[!VAR "TempId" = "node:current()"!][!//
[!IF "text:uniq(text:split($CCU6resourceMap,','),$TempId)"!][!//
[!ELSE!][!//
[!VAR "kernel" = "text:split($TempId,'_')[1]"!][!//
[!VAR "Timer" = "text:split($TempId,'_')[2]"!][!//
[!VAR "comp" = "text:split($TempId,'_')[3]"!][!//
[!VAR "comp" = "text:split($TempId,'_')[3]"!][!//
[!VAR "ErrorFound" = "num:i(1)"!][!//
[!BREAK!]
[!ENDIF!][!//
[!ENDLOOP!][!//

[!VAR "CCU6Kernel0" = "num:i(4294967295)"!][!//
[!VAR "CCU6Kernel1" = "num:i(4294967295)"!][!//
[!VAR "MaxCompCCU6Kernel0" = "num:i(0)"!][!//
[!VAR "MaxCompCCU6Kernel1" = "num:i(0)"!][!//
[!IF "$ErrorFound = num:i(1)"!][!//
[!LOOP "text:split($CCU6resourceMapChId,',')"!][!//
[!VAR "TempIdCh" = "node:current()"!][!//
[!IF "contains($TempIdCh,$TempId)"!][!//
[!VAR "Channel" = "substring-after($TempIdCh,'_ID')"!][!//
[!ERROR!]
  ERROR: CCU6 kernel : [!"$kernel"!], Timer : [!"$Timer"!], Comparator : [!"$comp"!] is assigned to more than one PWM channel. ChannelId-[!"$Channel"!].
[!ENDERROR!]
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//

[!LOOP "text:split($CCU6resourceMapChId,',')"!][!//
[!VAR "CurrentNode" = "node:current()"!][!//
[!VAR "kernel" ="text:split($CurrentNode,'_')[1]"!][!//* kernel*/
[!VAR "timer" ="text:split($CurrentNode,'_')[2]"!][!//* timer*/
[!VAR "Comp" ="substring-after(text:split($CurrentNode,'_')[3],'Cc6')"!][!//* comp*/      
[!VAR "ChId" ="substring-after(text:split($CurrentNode,'_')[4],'ID')"!][!//* ChId*/
[!IF "$timer = 'T12'"!][!//
[!VAR "Temp" = "bit:shl($ChId,$Comp * num:i(8))"!][!//
[!VAR "Mask" = "num:i(0)"!][!//
[!VAR "Mask" = "bit:shl(num:i(255),$Comp * num:i(8))"!][!//
[!VAR "Mask" = "bit:not($Mask)"!][!//
[!VAR "Temp" = "bit:xor($Temp,$Mask)"!][!//
[!IF "$kernel = num:i(0)"!][!//
[!VAR "CCU6Kernel0" = "bit:and($CCU6Kernel0,$Temp)"!][!//
[!IF "$Comp >= $MaxCompCCU6Kernel0"!][!//
[!VAR "MaxCompCCU6Kernel0" = "$Comp"!][!//
[!ENDIF!][!//
[!ELSE!][!//
[!VAR "CCU6Kernel1" = "bit:and($CCU6Kernel1,$Temp)"!][!//
[!IF "$Comp >= $MaxCompCCU6Kernel1"!][!//
[!VAR "MaxCompCCU6Kernel1" = "$Comp"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//

[!VAR "Ccu6KernelFound" = "num:i(0)"!][!//
[!VAR "PWMCHID" = "num:i(0)"!][!//
[!LOOP "PwmChannelConfigSet/PwmChannel/*"!][!//
  [!VAR "PwmTimerUsed" = "./PwmAssignedHwUnit"!][!//
  [!VAR "PwmChannelClass" = "./PwmChannelClass/*[1]"!][!//
  [!VAR "PWMCHID" = "./PwmChannelId"!][!//
  [!IF "node:exists(./PwmChannelClass/*[1])"!][!//
    [!VAR "classvalue" = "./PwmChannelClass/*[1]"!][!//
  [!ELSE!][!//
    [!ERROR!]
      ERROR: Pwm Channel class is not provided in [!"node:name(.)"!][!//
    [!ENDERROR!]
  [!ENDIF!][!//
  [!IF "$PwmTimerUsed = 'CCU6'"!][!//
    [!VAR "TempPeriod" = "./PwmPeriodDefault"!][!//
    [!SELECT "CCU6CC6Configuration/*[1]"!][!//
      [!VAR "CCU6TimerUsed" = "./CCU6TimerUsed"!][!//
      [!VAR "Ccu6KernelUsed" = "./CCU6KernelUsed"!][!//
      [!VAR "Ccu6TimerClockSel" = "./CCU6TimerClockSelect"!][!//
      [!VAR "Ccu6TimerPreScalar" = "./CCU6TimerPrescalarEnabled"!][!//
      [!IF "$CCU6TimerUsed = 'T12'"!][!//
        [!VAR "Ccu6KernelFound" = "num:i(1)"!][!//
        [!FOR "counter1" = "num:i(0)" TO "num:i($MaxChannels) - num:i(1)"!][!//
        [!SELECT "../../../../PwmChannel/*[PwmChannelId = num:i($counter1)]"!][!//
        [!VAR "PWMCHID1" = "./PwmChannelId"!][!//
        [!VAR "PwmChannelClassTemp" = "./PwmChannelClass/*[1]"!][!//
          [!VAR "PwmTimerUsed1" = "./PwmAssignedHwUnit"!][!//
          [!IF "$PwmTimerUsed1 = 'CCU6'"!][!//
            [!VAR "TempPeriod1" = "./PwmPeriodDefault"!][!//
            [!SELECT "CCU6CC6Configuration/*[1]"!][!//
              [!VAR "CCU6TimerUsed1" = "./CCU6TimerUsed"!][!// 
              [!VAR "Ccu6KernelUsed1" = "./CCU6KernelUsed"!][!//
              [!VAR "Ccu6TimerClockSel1" = "./CCU6TimerClockSelect"!][!//
              [!VAR "Ccu6TimerPreScalar1" = "./CCU6TimerPrescalarEnabled"!][!//
              [!IF "$CCU6TimerUsed1 = 'T12' and $Ccu6KernelUsed1 = $Ccu6KernelUsed"!][!//
                [!IF "$TempPeriod != $TempPeriod1"!][!//
                  [!ERROR!]
                    ERROR: Period value of Cc60/Cc61/Cc62 comparators in a kernel should be same for channels [!"$PWMCHID1"!] and [!"$PWMCHID"!]
                  [!ENDERROR!]
                [!ENDIF!][!//
                [!IF "$PwmChannelClassTemp = 'PWM_VARIABLE_PERIOD' and $PwmChannelClass = 'PWM_FIXED_PERIOD'"!][!//
                  [!ERROR!]
                    ERROR: If one of the comparators Cc60/Cc61/Cc62 is configured as PWM_VARIABLE_PERIOD remaining comparators cannot be used for other PWM channels [!"$PWMCHID1"!] and [!"$PWMCHID"!].
                  [!ENDERROR!]
                [!ENDIF!][!//
                [!IF "$Ccu6TimerClockSel != $Ccu6TimerClockSel1 or $Ccu6TimerPreScalar != $Ccu6TimerPreScalar1"!][!//
                   [!ERROR!]
                   ERROR: CCU6TimerClockSelect and CCU6TimerPrescalarEnabled values of Cc60/Cc61/Cc62 comparators in a kernel should be same for channels [!"$PWMCHID1"!] and [!"$PWMCHID"!]
                  [!ENDERROR!]
                [!ENDIF!][!//
              [!ENDIF!][!//
            [!ENDSELECT!][!//
          [!ENDIF!][!//
         [!ENDSELECT!][!//
         [!ENDFOR!][!//
      [!ENDIF!][!//
    [!ENDSELECT!][!//
    [!IF "$CCU6TimerUsed = 'T13'"!][!//
      [!IF "$classvalue = 'PWM_FIXED_PERIOD_SHIFTED'"!][!//
        [!VAR "RefShiftChn" = "node:path(node:ref(./PwmReferenceChannel))"!][!//
        [!VAR "RefTimerKernelUsed"= "node:ref($RefShiftChn)/CCU6CC6Configuration/*[1]/CCU6KernelUsed"!][!//
        [!IF "$RefTimerKernelUsed != $Ccu6KernelUsed"!][!//
          [!ERROR!]
            ERROR: Shifted channels should refer to fixed period channel of the same CCU6 kernel ChannelId [!"$PWMCHID"!].
          [!ENDERROR!]
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//

    
[!VAR "Module" = "'PWM'"!][!//
[!CALL "PWM_GenerateModuleMap", "Module" = "'PWM'"!][!//
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
Memory Mapping config data
[/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function 
  before MemMap inclusion It complies to Autosar guidelines. */
#include "Pwm_17_GtmCcu6_MemMap.h"
/* [cover parentID={933763AC-75AA-40a0-9A52-62A3E13015EE}]
 Data Structure to hold index map
[/cover] */
[!VAR "MaxChannelsCore" = "num:i(0)"!][!//
[!VAR "GtmChannelIndex" = "num:i(0)"!][!//
[!VAR "Ccu6ChannelIndex" = "num:i(0)"!][!//
[!VAR "PwmCoreIdMap" = "num:i(0)"!][!//
[!VAR "TempIdx" = "num:i(0)"!][!//
[!VAR "CurrentIdx" = "num:i(0)"!][!//
[!VAR "PwmCore0Idx" = "num:i(0)"!][!//
[!VAR "PwmCore1Idx" = "num:i(0)"!][!//
[!VAR "PwmCore2Idx" = "num:i(0)"!][!//
[!VAR "PwmCore3Idx" = "num:i(0)"!][!//
[!VAR "PwmCore4Idx" = "num:i(0)"!][!//
[!VAR "PwmCore5Idx" = "num:i(0)"!][!//
[!IF "$VariantsConfigured = num:i(1)"!][!//
static const uint8 Pwm_ChannelIndexMap_[!"$PredefinedVarName"!] [[!"num:i($MaxChannels)"!]] =
[!ELSE!][!//
static const uint8 Pwm_ChannelIndexMap [[!"num:i($MaxChannels)"!]] =
[!ENDIF!][!//
{
[!FOR "ChannelId" = "num:i(0)" TO "num:i($MaxChannels) - num:i(1)"!][!//
[!SELECT "PwmChannelConfigSet/PwmChannel/*[PwmChannelId = num:i($ChannelId)]"!][!//
[!VAR "NodeName" = "node:name(.)"!][!//
[!FOR "CoreId" = "num:i(0)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
[!CALL "PWM_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
[!IF "$CGAllocationResult = 'TRUE'"!][!//
[!IF "$CoreId = num:i(0)"!][!//
[!VAR "CurrentIdx" = "$PwmCore0Idx"!][!//
[!VAR "PwmCore0Idx" = "$PwmCore0Idx+num:i(1)"!][!//
[!ELSEIF "$CoreId = num:i(1)"!][!//
[!VAR "CurrentIdx" = "$PwmCore1Idx"!][!//
[!VAR "PwmCore1Idx" = "$PwmCore1Idx+num:i(1)"!][!//
[!ELSEIF "$CoreId = num:i(2)"!][!//
[!VAR "CurrentIdx" = "$PwmCore2Idx"!][!//
[!VAR "PwmCore2Idx" = "$PwmCore2Idx+num:i(1)"!][!//
[!ELSEIF "$CoreId = num:i(3)"!][!//
[!VAR "CurrentIdx" = "$PwmCore3Idx"!][!//
[!VAR "PwmCore3Idx" = "$PwmCore3Idx+num:i(1)"!][!//
[!ELSEIF "$CoreId = num:i(4)"!][!//
[!VAR "CurrentIdx" = "$PwmCore4Idx"!][!//
[!VAR "PwmCore4Idx" = "$PwmCore4Idx+num:i(1)"!][!//
[!ELSEIF "$CoreId = num:i(5)"!][!//
[!VAR "CurrentIdx" = "$PwmCore5Idx"!][!//
[!VAR "PwmCore5Idx" = "$PwmCore5Idx+num:i(1)"!][!//
[!ELSE!]
[!ENDIF!][!//
  [!"num:inttohex(number($CurrentIdx))"!]U,
[!VAR "CurrentIdx" = "num:i(0)"!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDSELECT!][!//
[!ENDFOR!][!//
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function 
  before MemMap inclusion It complies to Autosar guidelines. */
#include "Pwm_17_GtmCcu6_MemMap.h"

/* Loop for all the cores */
[!FOR "CoreId" = "num:i(0)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
[!VAR "MaxChannelsCore" = "num:i(0)"!][!//
[!VAR "GtmChannelIndex" = "num:i(0)"!][!//
[!VAR "Ccu6ChannelIndex" = "num:i(0)"!][!//
[!VAR "TempCoreId" = "concat('CORE',$CoreId)"!][!//
[!CALL "PWM_GetMasterCoreID"!][!//
[!IF "(text:contains( text:split($CGAllocatedCores,','), $TempCoreId)) or ($CGMasterCoreId = $TempCoreId)"!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"$CoreId"!]_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function 
  before MemMap inclusion It complies to Autosar guidelines. */
#include "Pwm_17_GtmCcu6_MemMap.h"
[!FOR "ChannelId" = "num:i(0)" TO "num:i($MaxChannels) - num:i(1)"!][!//
[!SELECT "PwmChannelConfigSet/PwmChannel/*[PwmChannelId = num:i($ChannelId)]"!][!//
[!VAR "NodeName" = "node:name(.)"!][!//
[!VAR "PwmLogicalChId" = "./PwmChannelId"!][!//
[!CALL "PWM_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
[!IF "$CGAllocationResult = 'TRUE'"!][!//
[!NOCODE!][!//
  [!VAR "MaxChannelsCore" = "$MaxChannelsCore + num:i(1)"!][!//
  [!VAR "PwmTimerUsed" = "./PwmAssignedHwUnit"!][!//
  [!IF "$PwmTimerUsed = 'GTM'"!][!//
    [!VAR "GtmChannelIndex" = "$GtmChannelIndex + num:i(1)"!][!//
  [!ELSE!][!//
    [!VAR "Ccu6ChannelIndex" = "$Ccu6ChannelIndex + num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDFOR!][!//

[!IF "$GtmChannelIndex > num:i(0)"!][!//
/* [cover parentID={B70285DD-C6A1-4806-B583-9A5D242FFA6C}]
  Gtm Channel Structure for selected Core
[/cover] */
[!IF "$VariantsConfigured = num:i(1)"!][!//
static const Mcu_17_Gtm_TomAtomChConfigType Pwm_kChannelConfigGtm_Core[!"$CoreId"!]_[!"$PredefinedVarName"!][[!"num:i($GtmChannelIndex)"!]] = 
[!ELSE!][!//
static const Mcu_17_Gtm_TomAtomChConfigType Pwm_kChannelConfigGtm_Core[!"$CoreId"!][[!"num:i($GtmChannelIndex)"!]] = 
[!ENDIF!][!//
{
[!VAR "GtmChannelIndex" = "num:i(0)"!][!//
[!FOR "ChannelId" = "num:i(0)" TO "num:i($MaxChannels) - num:i(1)"!][!//
[!SELECT "PwmChannelConfigSet/PwmChannel/*[PwmChannelId = num:i($ChannelId)]"!][!//
[!VAR "PwmTimerUsed" = "./PwmAssignedHwUnit"!][!//
[!IF "$PwmTimerUsed = 'GTM'"!][!//
[!VAR "NodeName" = "node:name(.)"!][!//
[!VAR "PwmLogicalChId" = "./PwmChannelId"!][!//
[!CALL "PWM_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
[!IF "$CGAllocationResult = 'TRUE'"!][!//
[!NOCODE!]
    [!VAR "GtmChannelIndex" = "$GtmChannelIndex + num:i(1)"!][!//
    [!VAR "polarity" = "./PwmPolarity"!][!//
    [!VAR "classvalue" = "./PwmChannelClass/*[1]"!][!//
    [!SELECT "GtmTimerOutputModuleConfiguration/*[1]"!][!//
      /* GTM Timer Configuration Information*/
      /* GtmTimerMode: PWM channels always runs in continous mode value = 0 (bit 26) */
      [!VAR "CtrlReg" = "num:i(0)"!][!//
              
      /* Set Clock Source for Timer Channel*/
      [!VAR "CtrlReg" = "bit:or($CtrlReg,bit:shl(substring-after((./GtmTimerClockSelect),'CLOCK_'),12))"!][!//
      /* Set Timer Type*/
      [!VAR "TimerType" = "substring-before(substring-after((./GtmTimerUsed),'McuGtmAllocationConf_0/McuGtm'),'All')"!][!//
      [!IF "$TimerType  = 'Atom'"!]
        [!VAR "TimerType" = "'MCU_GTM_TIMER_ATOM'"!][!//
        [!VAR "MaxTimerval" = "num:i(16777215)"!][!//
        /* Set ATOM mode as SOPM (10B ATOM Signal Output Mode PWM (SOMP))*/
        [!VAR "CtrlReg" = "bit:or($CtrlReg,2)"!][!//
      [!ELSE!][!//
        [!VAR "TimerType" = "'MCU_GTM_TIMER_TOM'"!][!//
        [!VAR "MaxTimerval" = "num:i(65535)"!][!//
      [!ENDIF!]
      /* Set Timer Module and Channel Number*/
      [!VAR "ModuleNumber" = "substring-before(substring-after((./GtmTimerUsed),'omAllocationConf_'),'/')"!][!//
      [!VAR "ChannelNumber" = "substring-after((./GtmTimerUsed),'ChannelAllocationConf_')"!][!//
      [!VAR "TimerChIdentifier" = "bit:or(num:i($ChannelNumber),num:i(bit:shl($ModuleNumber,8)))"!][!//
      
      [!IF "./GtmTimerPortPinSelect = 'NONE'"!][!//
        [!ERROR!]
          ERROR: Selected GtmTimer is not mapped to any Port pin for PwmChannelId [!"$ChannelId"!], choose different port pin or different Gtm timer.
        [!ENDERROR!]
      [!ELSE!][!//
        /* Set Port Select Parameters*/
        [!VAR "ToutSel" = "number(substring-before(substring-after((./GtmTimerPortPinSelect),'TOUT'),'_SEL'))"!][!//
        [!VAR "ALT_SEL" = "concat('PWM_ALT_SEL',substring-before(substring-after((./GtmTimerPortPinSelect),'_SEL'),'_PORT'),' << 15U')"!][!//
      [!ENDIF!][!//    
      [!ENDSELECT!][!//
    
      [!VAR "classvalue" = "./PwmChannelClass/*[1]"!][!//
    
      /*Update IsReference*/
      [!VAR "IsReference" = "num:i(0)"!][!//
      [!IF "$classvalue = 'PWM_FIXED_PERIOD'"!][!//
      [!VAR "currentnode" = "@name"!][!//
        [!FOR "counter1" = "num:i(0)" TO "num:i($MaxChannels) - num:i(1)"!][!//
          [!SELECT "../../PwmChannel/*[PwmChannelId = num:i($counter1)]"!][!//
          [!VAR "classvalue1" = "./PwmChannelClass/*[1]"!][!//
          [!IF "$classvalue1 = 'PWM_FIXED_PERIOD_SHIFTED' or $classvalue1 = 'PWM_FIXED_PERIOD_CENTER_ALIGNED'"!][!//
            [!IF "node:refvalid(./PwmReferenceChannel)"!][!//
            [!VAR "refchannelid" = "(node:ref(./PwmReferenceChannel)/PwmChannelId)"!][!//
              [!IF "num:i($ChannelId) = num:i($refchannelid)"!][!//
                [!VAR "PwmTimerUsedTemp" = "./PwmAssignedHwUnit"!][!//
                [!IF "$PwmTimerUsedTemp = $PwmTimerUsed"!][!//
                  [!VAR "IsReference" = "num:i(1)"!][!//
                  [!BREAK!]
                [!ELSE!][!//
                  [!ERROR!]
                    ERROR: Referred channel should be of same HW type (GTM/CCU6) [!"node:name(.)"!].
                  [!ENDERROR!]
                [!ENDIF!][!//
              [!ENDIF!][!//
            [!ELSE!][!//
              [!ERROR!]
              ERROR: Invalid reference [!"node:name(.)"!][!//
              [!ENDERROR!]
            [!ENDIF!][!//
          [!ENDIF!][!//
          [!ENDSELECT!][!//
        [!ENDFOR!][!//
      [!ENDIF!][!//
    
      /* Update Duty and Period*/
      [!VAR "DutyCycle" = "./PwmDutycycleDefault"!][!//
      [!VAR "PeriodValue" = "num:i(0)"!][!//
      [!IF "$classvalue = 'PWM_FIXED_PERIOD_SHIFTED' or $classvalue = 'PWM_FIXED_PERIOD_CENTER_ALIGNED'"!][!//
        [!VAR "Refchannel" = "node:path(node:ref(./PwmReferenceChannel))"!][!//
        [!VAR "PeriodValue" = "node:ref($Refchannel)/PwmPeriodDefault"!][!//
      [!ELSE!][!//
        [!VAR "PeriodValue" = "./PwmPeriodDefault"!][!//
      [!ENDIF!][!//
      
      [!VAR "polarity" = "./PwmPolarity"!][!//
       /* [cover parentID={2A2DF2BC-CBA8-4461-ABAC-F28CE9FCA8C6}]
         Fixed period center aligned PWM channel class shall always 
         synchronize with reference channel at the end of each period RST_CCU0 
         is enabled with Shiftreset variable
       [/cover] */
      [!VAR "ShiftReset" = "num:i(0)"!][!//
      [!IF "$PwmHandleShiftOffset  = 'true'"!]
        [!IF "$classvalue = 'PWM_FIXED_PERIOD_CENTER_ALIGNED'"!][!//
          [!VAR "ShiftReset" = "num:i(1)"!][!//
        [!ELSE!][!//
          [!VAR "ShiftReset" = "num:i(0)"!][!//
        [!ENDIF!][!//
      [!ELSE!][!//
        [!IF "$classvalue = 'PWM_FIXED_PERIOD_SHIFTED' or $classvalue = 'PWM_FIXED_PERIOD_CENTER_ALIGNED'"!][!//
          [!VAR "ShiftReset" = "num:i(1)"!][!//
        [!ELSE!][!//
          [!VAR "ShiftReset" = "num:i(0)"!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
  
      /* Get Scaled Values of Duty w.r.t to period */
      /* Pwm_lGetAbsvalEdge  duty*/
      [!IF "($DutyShiftInTicks = 'true')"!][!//
      /* Absolute */
      [!VAR "ScaledDuty" = "num:i($DutyCycle)"!][!//
      [!ELSE!]
      /* Relative */
      [!VAR "ScaledDuty" = "bit:shr((num:i($DutyCycle) * num:i($PeriodValue)),15)"!][!//
      [!ENDIF!][!//
      
      [!IF "num:i($ScaledDuty) >= num:i($PeriodValue)"!][!//
      [!VAR "ScaledDuty" = "num:i($PeriodValue)"!][!//
      [!ENDIF!][!//
      
      [!IF "$PeriodValue = num:i(0)"!][!//
      [!VAR "ScaledDuty" = "num:i(0)"!][!//
      [!ENDIF!][!//
          /* Get Abolute Shift value */
      [!IF "$classvalue = 'PWM_FIXED_PERIOD' or $classvalue = 'PWM_VARIABLE_PERIOD'"!][!//
      [!VAR "ShiftValue" = "num:i(0)"!][!//
      [!ELSE!]
        [!IF "$classvalue = 'PWM_FIXED_PERIOD_SHIFTED'"!][!//
          /* GetShiftLead */
          [!VAR "ShiftValue" = "num:i(./PwmShiftValue)"!][!//
          [!IF "($DutyShiftInTicks = 'false')"!][!//
            /* Relative */
            [!VAR "ShiftValue" = "bit:shr((num:i($ShiftValue) * num:i($PeriodValue)),15)"!][!//
          [!ENDIF!][!//
          [!IF "$PeriodValue = num:i(0) or $ShiftValue >= $PeriodValue"!][!//
            [!VAR "ShiftValue" = "num:i(0)"!][!//
          [!ENDIF!][!//
        [!ELSE!]
          /* GetCenterLead */
          [!IF "$ScaledDuty < $PeriodValue"!][!//
            [!VAR "ShiftValue" = "(num:i($PeriodValue)-num:i($ScaledDuty)) div 2"!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
              /* Get_CounterValues Update Counter values(CM0,CM1,CN0,SR1, and SR0) w.r.t period,duty and shift*/
      [!IF "$classvalue = 'PWM_FIXED_PERIOD' or $classvalue = 'PWM_VARIABLE_PERIOD'"!][!//
      [!VAR "TimerCM0Value" = "num:i($PeriodValue)"!][!//
      [!VAR "TimerCM1Value" = "num:i($ScaledDuty)"!][!//
      [!VAR "TimerCN0Value" = "num:i($PeriodValue)"!][!//
      [!VAR "TimerSR1Value" = "num:i($ScaledDuty)"!][!//
      [!VAR "TimerSR0Value" = "num:i($PeriodValue)"!][!//
      [!ELSE!]
        /* PWM_FIXED_PERIOD_SHIFTED' or PWM_FIXED_PERIOD_CENTER_ALIGNED*/
        [!IF "$ShiftReset = num:i(1)"!][!//
        /* FIXED_PERIOD_SHIFTED when OFFSET = OFF CENTER_ALIGNED when OFFSET = (ON/OFF)*/
          [!IF "num:i($ScaledDuty) = num:i(0)"!][!//
            [!VAR "TimerCM0Value" = "$MaxTimerval"!][!//
            [!VAR "TimerCM1Value" = "num:i(0)"!][!//
            [!VAR "TimerCN0Value" = "num:i(0)"!][!//
            [!VAR "TimerSR1Value" = "num:i(0)"!][!//
            [!VAR "TimerSR0Value" = "$MaxTimerval"!][!//
          [!ELSEIF "num:i($ScaledDuty) = num:i($PeriodValue)"!][!//
            [!VAR "TimerCM0Value" = "num:i(0)"!][!//
            [!VAR "TimerCM1Value" = "$MaxTimerval"!][!//g
            [!VAR "TimerCN0Value" = "num:i(0)"!][!//
            [!VAR "TimerSR1Value" = "$MaxTimerval"!][!//
            [!VAR "TimerSR0Value" = "num:i(0)"!][!//
          [!ELSE!]
            [!VAR "TimerCM0Value" = "num:i($ShiftValue)"!][!//
            [!VAR "TimerCM1Value" = "num:i(num:mod((num:i($ShiftValue)+num:i($ScaledDuty)),num:i($PeriodValue)))"!][!//
            [!VAR "TimerCN0Value" = "num:i(0)"!][!//
            [!VAR "TimerSR1Value" = "num:i(num:mod((num:i($ShiftValue)+num:i($ScaledDuty)),num:i($PeriodValue)))"!][!//
            [!VAR "TimerSR0Value" = "num:i($ShiftValue)"!][!//
          [!ENDIF!][!//
        [!ELSE!]
        /* FIXED_PERIOD_SHIFTED when OFFSET  =  ON.*/
          [!IF "num:i($PeriodValue) = num:i(0)"!][!//
            [!VAR "TimerCN0Value" = "num:i(0)"!][!//
          [!ELSE!]
            [!VAR "TimerCN0Value" = "num:i($PeriodValue) - num:i($ShiftValue)"!][!//
          [!ENDIF!][!//
            [!VAR "TimerCM0Value" = "num:i($PeriodValue)"!][!//
            [!VAR "TimerCM1Value" = "num:i($ScaledDuty)"!][!//
            [!VAR "TimerSR1Value" = "num:i($ScaledDuty)"!][!//
            [!VAR "TimerSR0Value" = "num:i($PeriodValue)"!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
  
      [!VAR "NodeName" = "node:name(.)"!][!//
      /* Set for control register */
      
      /* Set initial signal level of the GTM Timer channel */
      [!IF "$polarity = 'PWM_HIGH'"!]
        [!VAR "CtrlReg" = "bit:bitset($CtrlReg,11)"!][!//
      [!ENDIF!]
      /* Set Trigger Output  and RST_CCU0 for this Channel */
      [!IF "$ShiftReset = num:i(1)"!]
        [!VAR "CtrlReg" = "bit:bitset($CtrlReg,20)"!][!//
      [!ENDIF!]
      
      [!IF "$IsReference = num:i(1)"!]
        [!VAR "CtrlReg" = "bit:bitset($CtrlReg,24)"!][!//
      [!ENDIF!]
      
      /* Set period, duty match timer interrupt and interrupt mode*/
      /* By default interrupts are disabled and level mode is selected (00) */
      [!VAR "IntEnMode" = "num:i(128)"!][!//
[!ENDNOCODE!][!//
  {
    [!"$TimerType"!], /* Timer Type (TOM/ATOM)*/
    /* Bit[15:8] - Module number Bit[7:0] - Channel number*/
    [!"num:inttohex(number($TimerChIdentifier))"!]U,
    [!"num:inttohex($CtrlReg)"!]U, /* Channel Control Register*/
    [!"num:inttohex($TimerCN0Value)"!]U, /* CN0 in ticks */
    [!"num:inttohex($TimerCM0Value)"!]U, /* CM0 in ticks */
    [!"num:inttohex($TimerCM1Value)"!]U, /* CM1 in ticks */
    [!"num:inttohex($TimerSR0Value)"!]U, /* SR0 in ticks */
    [!"num:inttohex($TimerSR1Value)"!]U, /* SR1 in ticks */
    (uint32)((uint32)[!"num:i($ToutSel)"!]U | (uint32)([!"$ALT_SEL"!])),/* portpinout*/
    [!"num:inttohex($IntEnMode)"!]U /* Period,Duty Interrupt and mode*/
  },
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDFOR!][!//
};
[!ENDIF!][!//
[!IF "$Ccu6ChannelIndex > num:i(0)"!][!//
[!IF "$VariantsConfigured = num:i(1)"!][!//
/* [cover parentID={19BE0B53-A1C4-4665-AD2F-6DF0B77F9A2A}]
  Ccu6 Channel Structure for selected Core
[/cover] */
static const Mcu_17_Ccu6_TimerConfigType Pwm_kChannelConfigCcu6_Core[!"$CoreId"!]_[!"$PredefinedVarName"!][[!"num:i($Ccu6ChannelIndex)"!]] = 
[!ELSE!][!//
static const Mcu_17_Ccu6_TimerConfigType Pwm_kChannelConfigCcu6_Core[!"$CoreId"!][[!"num:i($Ccu6ChannelIndex)"!]] = 
[!ENDIF!][!//
{
[!VAR "CCU6ChannelIndex" = "num:i(0)"!][!//
[!FOR "ChannelId" = "num:i(0)" TO "num:i($MaxChannels) - num:i(1)"!][!//
[!SELECT "PwmChannelConfigSet/PwmChannel/*[PwmChannelId = num:i($ChannelId)]"!][!//
[!VAR "Ccu6TimerId" = "num:i(0)"!][!//
[!VAR "PwmTimerUsed" = "./PwmAssignedHwUnit"!][!//
[!IF "$PwmTimerUsed = 'CCU6'"!][!//
[!VAR "NodeName" = "node:name(.)"!][!//
[!VAR "PwmLogicalChId" = "./PwmChannelId"!][!//
[!CALL "PWM_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
[!IF "$CGAllocationResult = 'TRUE'"!][!//
[!NOCODE!]
  [!SELECT "CCU6CC6Configuration/*[1]"!][!//
  [!VAR "Ccu6KernelUsed" = "./CCU6KernelUsed"!][!//
  [!IF "contains($Ccu6KernelUsed,'McuCcu6ModuleAllocationConf_0')"!][!//
    [!VAR "Ccu6KernelUsed" = "num:i(0)"!][!//
    [!VAR "MaxCompCCU6Kernelx" = "$MaxCompCCU6Kernel0"!][!//
  [!ELSE!]
    [!VAR "Ccu6KernelUsed" = "num:i(1)"!][!//
    [!VAR "MaxCompCCU6Kernelx" = "$MaxCompCCU6Kernel1"!][!//
  [!ENDIF!][!//
  
  [!VAR "CCU6TimerUsed" = "./CCU6TimerUsed"!][!//
  [!VAR "CCU6CompUsed" = "num:i(substring-after(./Cc6xChannel,'Cc6'))"!][!//
  
  [!IF "$CCU6TimerUsed = 'T12'"!][!//
    [!VAR "CCU6TimerUsed" = "num:i(0)"!][!//
  [!ELSE!]
    [!VAR "CCU6TimerUsed" = "num:i(1)"!][!//
    [!VAR "CCU6CompUsed" = "num:i(3)"!][!//
  [!ENDIF!][!//
  
  
  [!VAR "CCU6TimerClock" = "num:i(substring-after(./CCU6TimerClockSelect,'CCU6_CONFIGURABLE_CLOCK_'))"!][!//
  [!VAR "Ccu6PreScalar" = "./CCU6TimerPrescalarEnabled"!][!//
  [!IF "$Ccu6PreScalar = 'true'"!][!//
    [!VAR "Ccu6PreScalar" = "num:i(1)"!][!//
  [!ELSE!]
    [!VAR "Ccu6PreScalar" = "num:i(0)"!][!//
  [!ENDIF!][!//
  [!ENDSELECT!][!//

  [!VAR "Ccu6TimerId" = "$Ccu6KernelUsed"!][!//
  [!VAR "Ccu6TimerId" = "bit:or($Ccu6TimerId,bit:shl($CCU6TimerUsed,8))"!][!//
  [!VAR "Ccu6TimerId" = "bit:or($Ccu6TimerId,bit:shl($CCU6CompUsed,16))"!][!//
  [!VAR "PasStateLvlReg" = "./PwmPolarity"!][!//
  [!IF "$PasStateLvlReg = 'PWM_LOW'"!][!//
    [!VAR "PasStateLvlReg" = "num:i(0)"!][!//
  [!ELSE!]
    [!VAR "PasStateLvlReg" = "num:i(1)"!][!//
  [!ENDIF!][!//
  
  [!VAR "TimerCtrlReg0" = "$CCU6TimerClock"!][!//
  [!IF "$CCU6TimerUsed = num:i(0)"!][!//
  [!VAR "TimerCtrlReg0" = "bit:or($TimerCtrlReg0,bit:shl($Ccu6PreScalar,3))"!][!//
  [!VAR "ModCtrlReg" = "num:i(1)"!][!//
    [!IF "$PasStateLvlReg = num:i(1)"!][!//
      [!VAR "PasStateLvlReg" = "num:i(1)"!][!//
    [!ELSE!]
      [!VAR "PasStateLvlReg" = "num:i(0)"!][!//
    [!ENDIF!][!//
  [!ELSE!]
  [!VAR "TimerCtrlReg0" = "bit:or($TimerCtrlReg0,bit:shl($CCU6TimerClock,8))"!][!//
  [!VAR "TimerCtrlReg0" = "bit:or($TimerCtrlReg0,bit:shl($Ccu6PreScalar,11))"!][!//
  [!VAR "ModCtrlReg" = "bit:shl(num:i(1),2)"!][!//
    [!IF "$PasStateLvlReg = num:i(1)"!][!//
      [!VAR "PasStateLvlReg" = "bit:shl(num:i(1),2)"!][!//
    [!ELSE!]
      [!VAR "PasStateLvlReg" = "num:i(0)"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
  
  /* Start with count 0 */
  [!VAR "TimerCntReg" = "num:i(0)"!][!//
  [!VAR "classvalue" = "./PwmChannelClass/*[1]"!][!//
  [!VAR "TimerPeriodReg" = "num:i(0)"!][!//
  [!IF "$classvalue = 'PWM_FIXED_PERIOD_SHIFTED'"!][!//
    [!VAR "Refchannel" = "node:path(node:ref(./PwmReferenceChannel))"!][!//
    [!VAR "TimerPeriodReg" = "node:ref($Refchannel)/PwmPeriodDefault"!][!//
    [!VAR "ShiftValue" = "num:i(./PwmShiftValue)"!][!//
    [!IF "($DutyShiftInTicks = 'false')"!][!//
      /* Relative */
      [!VAR "ShiftValue" = "bit:shr((num:i($ShiftValue) * num:i($TimerPeriodReg)),15)"!][!//
    [!ENDIF!][!//
    [!IF "$TimerPeriodReg = num:i(0) or $ShiftValue >= $TimerPeriodReg"!][!//
      [!VAR "ShiftValue" = "num:i(0)"!][!//
    [!ENDIF!][!//
  [!ELSE!][!//
    [!VAR "TimerPeriodReg" = "./PwmPeriodDefault"!][!//
    [!VAR "ShiftValue" = "num:i(0)"!][!//
  [!ENDIF!][!//
      
  [!VAR "DutyCycle" = "./PwmDutycycleDefault"!][!//
  /* Get Scaled Values of Duty w.r.t to period */
  /* Pwm_lGetAbsvalEdge  duty*/
  [!IF "($DutyShiftInTicks = 'true')"!][!//
    /* Absolute */
    [!VAR "Ccu6ShadowReg" = "num:i($DutyCycle)"!][!//
  [!ELSE!]
    /* Relative */
    [!VAR "Ccu6ShadowReg" = "bit:shr((num:i($DutyCycle) * num:i($TimerPeriodReg)),15)"!][!//
  [!ENDIF!][!//
  
  [!IF "num:i($Ccu6ShadowReg) >= num:i($TimerPeriodReg)"!][!//
    [!VAR "Ccu6ShadowReg" = "num:i($TimerPeriodReg)"!][!//
  [!ENDIF!][!//
  
  [!IF "$TimerPeriodReg = num:i(0)"!][!//
    [!VAR "Ccu6ShadowReg" = "num:i(0)"!][!//
  [!ENDIF!][!//
  
  [!IF "$classvalue = 'PWM_FIXED_PERIOD_SHIFTED'"!][!//
    [!VAR "TimerCntReg" = "num:i($TimerPeriodReg) - num:i($ShiftValue)"!][!//
  [!ENDIF!][!//
  [!IF "$CCU6TimerUsed = num:i(0)"!][!//
  [!VAR "T12NodeMask" = "bit:shl($MaxCompCCU6Kernelx,num:i(2))"!][!//
  [!VAR "IntNodePointerReg" = "bit:or($CCU6CompUsed,$T12NodeMask)"!][!//
  [!ELSE!][!//
  [!VAR "IntNodePointerReg" = "num:i(12)"!][!//
  [!ENDIF!][!//
[!ENDNOCODE!][!//
  {
    [!"num:inttohex(number($Ccu6TimerId))"!]U, /* Ccu6 Timer ID */
    /* T12 - [2-0] - Timer T12 Input Clock Select
             [3]   - Timer T12 Prescaler Bit
             [7]   - T12 Operating Mode
       T13 - [10-8] - Timer T13 Input Clock Select
             [11]   - Timer T13 Prescaler Bit */
    [!"num:inttohex(number($TimerCtrlReg0))"!]U,
    /* T12 - [1-0]  - Timer T12 modulation enable
       T13 - [2]   - Enable Compare Timer T13 Output CC63*/
    [!"num:inttohex(number($ModCtrlReg))"!]U,
    /* T12 - [1-0] - Compare Outputs Passive State Level
       T13 - [2]   - Passive State Level of Output COUT63*/
    [!"num:inttohex(number($PasStateLvlReg))"!]U,
    [!"num:inttohex(number($TimerCntReg))"!]U, /* T12/T13 counter value */
    [!"num:inttohex(number($TimerPeriodReg))"!]U, /* Period */
    [!"num:inttohex(number($Ccu6ShadowReg))"!]U, /* Duty */
    0x1U, /* Compare Mode */
    0x0U, /* port in select */
    0x0U, /* Interrupt enable */
    [!"num:inttohex(number($IntNodePointerReg))"!]U /* Interrupt node Select */
  },
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDFOR!][!//
};
[!ENDIF!][!//
/* [cover parentID={590D92B5-1B71-4d3f-BAEC-819D90AF138E}]
  Channel Structure for selected Core
[/cover] */
[!VAR "GtmChannelIndex" = "num:i(0)"!][!//
[!VAR "Ccu6ChannelIndex" = "num:i(0)"!][!//
[!IF "$MaxChannelsCore > num:i(0)"!][!//
[!IF "$VariantsConfigured = num:i(1)"!][!//
static const Pwm_17_GtmCcu6_ChannelConfigType Pwm_kChannelConfigurationCore[!"$CoreId"!]_[!"$PredefinedVarName"!][] =
[!ELSE!][!//
static const Pwm_17_GtmCcu6_ChannelConfigType Pwm_kChannelConfigurationCore[!"$CoreId"!][] =
[!ENDIF!][!//
{
[!FOR "ChannelId" = "num:i(0)" TO "num:i($MaxChannels) - num:i(1)"!][!//
[!SELECT "PwmChannelConfigSet/PwmChannel/*[PwmChannelId = num:i($ChannelId)]"!][!//
[!VAR "NodeName" = "node:name(.)"!][!//
[!VAR "PwmLogicalChId" = "./PwmChannelId"!][!//
[!CALL "PWM_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
[!IF "$CGAllocationResult = 'TRUE'"!][!//
[!NOCODE!][!//
  [!VAR "PwmTimerUsed" = "./PwmAssignedHwUnit"!][!//
  [!IF "$PwmTimerUsed = 'GTM'"!][!//
    [!VAR "PwmTimerUsed" = "num:i(0)"!][!//
    [!VAR "GtmChannelIndex" = "$GtmChannelIndex + num:i(1)"!][!//
    [!SELECT "GtmTimerOutputModuleConfiguration/*[1]"!][!//
      [!NOCODE!]
        /* GTM Timer Information*/
        /* Set Timer Type*/
        [!VAR "TimerType" = "substring-before(substring-after((./GtmTimerUsed),'McuGtmAllocationConf_0/McuGtm'),'All')"!][!//
        [!IF "$TimerType  = 'Atom'"!]
          [!VAR "TimerType" = "'MCAL_GTM_TIMER_ATOM'"!][!//
        [!ELSE!][!//
          [!VAR "TimerType" = "'MCAL_GTM_TIMER_TOM'"!][!//
        [!ENDIF!]
        /* Set Timer Module and Channel Number*/
        [!VAR "ModuleNumber" = "substring-before(substring-after((./GtmTimerUsed),'omAllocationConf_'),'/')"!][!//
        [!VAR "ChannelNumber" = "substring-after((./GtmTimerUsed),'ChannelAllocationConf_')"!][!//
      [!ENDNOCODE!][!//
    [!ENDSELECT!][!//
  [!ELSE!][!//
    /* CCU6 Timer Information*/
    [!VAR "PwmTimerUsed" = "num:i(1)"!][!//
    [!VAR "TimerType" = "'MCAL_CCU6_TIMER'"!][!//
    [!VAR "Ccu6ChannelIndex" = "$Ccu6ChannelIndex + num:i(1)"!][!//
  [!ENDIF!][!//
  
  /* Notification information */
  [!VAR "Notify" = "'(Pwm_17_GtmCcu6_NotifiPtrType)0'"!][!//
  [!IF "$Notification = 'STD_ON'"!][!//
    [!IF "node:exists(./PwmNotification/*[1])"!][!//
      [!VAR "Notify" = "./PwmNotification/*[1]"!][!//
    [!ELSE!][!//
      [!VAR "Notify" = "'NULL_PTR'"!][!//
    [!ENDIF!][!//
    [!IF "string-length($Notify) = 0 or $Notify = '"NULL_PTR"' or $Notify = 'NULL_PTR'"!]
      [!VAR "Notify" = "'NULL_PTR'"!]
    [!ELSE!][!//
      [!IF "num:isnumber($Notify) = 'true'"!][!//
        [!VAR "Notify" = "concat('(Pwm_17_GtmCcu6_NotifiPtrType)',$Notify,'U')"!]
      [!ELSE!][!//
        [!VAR "Notify" = "concat('&',$Notify)"!]
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
   
  /*Update Choerency */
  [!IF "node:exists(./PwmChannelClass/*[1])"!][!//
    [!VAR "classvalue" = "./PwmChannelClass/*[1]"!][!//
  [!ELSE!][!//
    [!ERROR!]
      ERROR: Pwm Channel class is not provided in [!"node:name(.)"!][!//
    [!ENDERROR!]
  [!ENDIF!][!//
  
  [!IF "$classvalue = 'PWM_FIXED_PERIOD_SHIFTED' or $classvalue = 'PWM_FIXED_PERIOD_CENTER_ALIGNED'"!][!//
    [!VAR "refnode" = "./PwmReferenceChannel"!][!//
    [!IF "string-length($refnode) = 0"!][!//
      [!ERROR!]
        ERROR: Reference channel must be provided for shifted or centre aligned [!"@name"!]
      [!ENDERROR!]
    [!ENDIF!][!//
  [!ENDIF!][!//

  [!// Read the local coherent update value for this channel(true/false)
  [!VAR "ChannelCoherency" = "'PWM_17_GTMCCU6_NON_COHERENT'"!][!//
  [!IF "$DutyCycleEndPeriodNeeded = 'true'"!][!//
    [!IF "$classvalue != 'PWM_VARIABLE_PERIOD'"!][!//
      [!VAR "ChannelCoherency" = "'PWM_17_GTMCCU6_COHERENT'"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//

  [!IF "$PeriodEndPeriodNeeded = 'true'"!][!//
    [!IF "$classvalue = 'PWM_VARIABLE_PERIOD'"!][!//
      [!VAR "ChannelCoherency" = "'PWM_17_GTMCCU6_COHERENT'"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//

  [!IF "node:exists(PwmCoherentUpdate)"!][!//
    [!IF "PwmCoherentUpdate = 'true'"!][!//
      [!VAR "ChannelCoherency" = "'PWM_17_GTMCCU6_COHERENT'"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//

 [!IF "$classvalue = 'PWM_FIXED_PERIOD_SHIFTED' or $classvalue = 'PWM_FIXED_PERIOD_CENTER_ALIGNED'"!][!//
 [!VAR "RefShiftChn" = "node:path(node:ref(./PwmReferenceChannel))"!][!//
 [!ENDIF!][!//

 [!IF "$PwmTimerUsed = num:i(1)"!][!//
 [!VAR "ChannelCoherency" = "'PWM_17_GTMCCU6_COHERENT'"!][!//
 [!ENDIF!][!//
  /*Update IsReference*/
  [!VAR "IsReference" = "num:i(0)"!][!//
  [!IF "$classvalue = 'PWM_FIXED_PERIOD'"!][!//
    [!VAR "PeriodValue" = "./PwmPeriodDefault"!][!//
    [!VAR "currentnode" = "@name"!][!//
    [!FOR "counter1" = "num:i(0)" TO "num:i($MaxChannels) - num:i(1)"!][!//
      [!SELECT "../../PwmChannel/*[PwmChannelId = num:i($counter1)]"!][!//
      [!VAR "classvalue1" = "./PwmChannelClass/*[1]"!][!//
        [!IF "$classvalue1 = 'PWM_FIXED_PERIOD_SHIFTED' or $classvalue1 = 'PWM_FIXED_PERIOD_CENTER_ALIGNED'"!][!//
          [!VAR "refnode1" = "./PwmReferenceChannel"!][!//
          [!IF "string-length($refnode1) = 0"!][!//
            [!ERROR!]
              ERROR: Reference channel must be provided for shifted or centre aligned [!"@name"!]
            [!ENDERROR!]
          [!ENDIF!][!//
          [!VAR "refchannelid" = "(node:ref(./PwmReferenceChannel)/PwmChannelId)"!][!//
          [!IF "num:i($ChannelId) = num:i($refchannelid)"!][!//
            [!IF "num:i($ChannelId) > num:i($counter1)"!][!//
              [!ERROR!]
                ERROR: PwmChannelId of  [!"$currentnode"!] should be less than the PwmChannelId of [!"@name"!]
              [!ENDERROR!]
            [!ENDIF!][!//
            [!VAR "IsReference" = "num:i(1)"!][!//
            [!IF "$TimerType = 'MCAL_GTM_TIMER_TOM'"!][!//
              [!IF "$PeriodValue = num:i(65535)"!][!//
                [!ERROR!]
                  ERROR: Enter TOM period value less than maximum allowed value 0xFFFF for PWM Channel [!"$currentnode"!]
                [!ENDERROR!]
              [!ENDIF!][!//
            [!ELSEIF "$TimerType = 'MCAL_GTM_TIMER_ATOM'"!][!//
              [!IF "$PeriodValue = num:i(16777215)"!][!//
                [!ERROR!]
                  ERROR: Enter ATOM period value less than maximum allowed value 0xFFFFFF for PWM Channel [!"$currentnode"!]
                [!ENDERROR!]
              [!ENDIF!][!//
            [!ENDIF!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDSELECT!][!//
    [!ENDFOR!][!//
  [!ENDIF!][!//

  /* Update Reference_Channel*/
  [!IF "$classvalue = 'PWM_FIXED_PERIOD_SHIFTED' or $classvalue = 'PWM_FIXED_PERIOD_CENTER_ALIGNED'"!][!//
    [!VAR "currentnode" = "@name"!][!//
    [!VAR "refnode" = "node:name(node:ref(./PwmReferenceChannel))"!][!//
    [!VAR "TempHWuint" = "./PwmAssignedHwUnit"!][!//
    [!IF "$refnode = $currentnode"!][!//
      [!ERROR!]
        ERROR: Reference Channel cannot be the same channel [!"@name"!]
      [!ENDERROR!]
    [!ENDIF!][!//
    [!FOR "counter" = "num:i(0)" TO "num:i($MaxChannels) - num:i(1)"!][!//
      [!IF "$refnode = node:name(as:modconf('Pwm')[1]/PwmChannelConfigSet/PwmChannel/*[@index = $counter])"!][!//
        [!IF "as:modconf('Pwm')[1]/PwmChannelConfigSet/PwmChannel/*[@index = $counter]/PwmChannelClass/*[1] != 'PWM_FIXED_PERIOD'"!][!//
          [!ERROR!]
            ERROR:PWM Channel[!"PwmChannelId"!] A referred channel can only be of Fixed Period Class
          [!ENDERROR!]
        [!ENDIF!][!//
        
        [!IF "as:modconf('Pwm')[1]/PwmChannelConfigSet/PwmChannel/*[@index = $counter]/PwmAssignedHwUnit != $TempHWuint"!][!//
          [!ERROR!]
            ERROR:PWM Channel[!"PwmChannelId"!] PwmAssignedHwUnit of referencing and referred channel should be same. (GTM/CCU6)
          [!ENDERROR!]
        [!ENDIF!][!//
        
        [!IF "$PwmTimerUsed = num:i(0)"!][!//
          [!VAR "RefTimerUsed"= "num:i(0)"!][!//
          [!VAR "RefTimerType" = "num:i(0)"!][!//
          [!VAR "RefModuleNumber" = "num:i(0)"!][!//
          [!VAR "RefChannelNumber" = "num:i(0)"!][!//
          [!VAR "RefGroupNo" = "num:i(0)"!][!//
          [!VAR "GroupNo" = "num:i(number($ChannelNumber) div 8)"!][!//
          [!VAR "RefShiftChn" = "num:i(0)"!][!//
          [!VAR "RefShiftChn" = "node:path(node:ref(./PwmReferenceChannel))"!][!//
          [!VAR "RefTimerUsed"= "node:ref($RefShiftChn)/GtmTimerOutputModuleConfiguration/*[1]/GtmTimerUsed"!][!//
          [!VAR "RefTimerType" = "substring-before(substring-after($RefTimerUsed,'McuGtmAllocationConf_0/McuGtm'),'All')"!][!//
          [!VAR "RefModuleNumber" = "substring-before(substring-after($RefTimerUsed,'omAllocationConf_'),'/')"!][!//
          [!VAR "RefChannelNumber" = "substring-after($RefTimerUsed,'ChannelAllocationConf_')"!][!//
          [!IF "$RefTimerType  = 'Atom'"!]
            [!VAR "RefTimerType" = "'MCAL_GTM_TIMER_ATOM'"!][!//
            [!VAR "RefGroupNo" = "num:i(0)"!][!//
          [!ELSE!][!//
            [!VAR "RefTimerType" = "'MCAL_GTM_TIMER_TOM'"!][!//
            [!VAR "RefGroupNo" = "num:i($RefChannelNumber div 8)"!][!//
          [!ENDIF!]
          [!IF "($RefTimerType != $TimerType) or (num:i($RefModuleNumber) != num:i($ModuleNumber)) or (num:i($RefGroupNo) != num:i($GroupNo)) or (num:i($RefChannelNumber) > num:i($ChannelNumber))"!][!//
            [!ERROR!]
              ERROR: PWM Channel[!"PwmChannelId"!] Shifted\Center Aligned channels should be present in the same
              TGC/AGC of the same TOM/ATOM module number where the referenced Fixed Period channel is present.
              Note: Fixed Period channel number should be less then Shifted\Center Aligned channel number
            [!ENDERROR!]
          [!ENDIF!][!//
        [!ENDIF!]
        [!VAR "RefPeriod" = "num:i(0)"!][!//
        [!VAR "ShiftValue" = "num:i(0)"!][!//
        [!IF "$classvalue = 'PWM_FIXED_PERIOD_SHIFTED'"!][!//
          [!VAR "ShiftValue" = "./PwmShiftValue"!][!//
          [!IF "($DutyShiftInTicks = 'true')"!][!//
            [!VAR "RefPeriod"= "node:ref($RefShiftChn)/PwmPeriodDefault"!][!//
            [!IF "$ShiftValue > $RefPeriod"!][!//
              [!ERROR!]
                ERROR: PWM Channel[!"PwmChannelId"!] ShiftValue is greater than Reference Period. Enter number less than or equal to Reference Period
              [!ENDERROR!]
            [!ENDIF!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDFOR!][!//
  [!ENDIF!][!//

  /* Update Duty and Period*/
  [!VAR "DutyCycle" = "./PwmDutycycleDefault"!][!//
  [!VAR "PeriodValue" = "num:i(0)"!][!//
  [!IF "$classvalue = 'PWM_FIXED_PERIOD_SHIFTED' or $classvalue = 'PWM_FIXED_PERIOD_CENTER_ALIGNED'"!][!//
    [!VAR "Refchannel" = "node:path(node:ref(./PwmReferenceChannel))"!][!//
    [!VAR "PeriodValue" = "node:ref($Refchannel)/PwmPeriodDefault"!][!//
  [!ELSE!][!//
    [!VAR "PeriodValue" = "./PwmPeriodDefault"!][!//
  [!ENDIF!][!//
  
  [!IF "$PwmTimerUsed = num:i(0)"!][!//
    [!IF "$TimerType = 'MCAL_GTM_TIMER_TOM'"!][!//
      [!IF "($DutyShiftInTicks = 'true')"!][!//
        [!IF "$DutyCycle > num:i(65535)"!][!//
          [!ERROR!]
            ERROR: In TOM Duty cycle value is greater than maximum allowed value 0xFFFF for PWM Channel [!"PwmChannelId"!]
          [!ENDERROR!]
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!IF "$PeriodValue > num:i(65535)"!][!//
        [!ERROR!]
          ERROR: In TOM period value is greater than maximum allowed value 0xFFFF for PWM Channel [!"PwmChannelId"!]
        [!ENDERROR!]
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
 
  [!IF "$PwmTimerUsed = num:i(1)"!][!//
    [!IF "($DutyShiftInTicks = 'true')"!][!//
      [!IF "$DutyCycle > num:i(65535)"!][!//
        [!ERROR!]
          ERROR: In CCU6 Duty cycle value is greater than maximum allowed value 0xFFFF for PWM Channel [!"PwmChannelId"!]
        [!ENDERROR!]
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!IF "$PeriodValue > num:i(65535)"!][!//
        [!ERROR!]
          ERROR: In CCU6 period value is greater than maximum allowed value 0xFFFF for PWM Channel [!"PwmChannelId"!]
        [!ENDERROR!]
    [!ENDIF!][!//
  [!ENDIF!][!//
 
  [!VAR "idlestate" = "./PwmIdleState"!][!//
  [!VAR "polarity" = "./PwmPolarity"!][!//

  [!VAR "ShiftReset" = "num:i(0)"!][!//
  [!IF "$PwmHandleShiftOffset  = 'true'"!]
    [!IF "$classvalue = 'PWM_FIXED_PERIOD_CENTER_ALIGNED'"!][!//
      [!VAR "ShiftReset" = "num:i(1)"!][!//
    [!ELSE!][!//
      [!VAR "ShiftReset" = "num:i(0)"!][!//
    [!ENDIF!][!//
  [!ELSE!][!//
    [!IF "$classvalue = 'PWM_FIXED_PERIOD_SHIFTED' or $classvalue = 'PWM_FIXED_PERIOD_CENTER_ALIGNED'"!][!//
      [!VAR "ShiftReset" = "num:i(1)"!][!//
    [!ELSE!][!//
      [!VAR "ShiftReset" = "num:i(0)"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//

  /* Get Scaled Values of Duty w.r.t to period */
  /* Pwm_lGetAbsvalEdge  duty*/
  [!IF "($DutyShiftInTicks = 'true')"!][!//
    /* Absolute */
    [!VAR "ScaledDuty" = "num:i($DutyCycle)"!][!//
  [!ELSE!]
    /* Relative */
    [!VAR "ScaledDuty" = "bit:shr((num:i($DutyCycle) * num:i($PeriodValue)),15)"!][!//
  [!ENDIF!][!//
 
  [!IF "num:i($ScaledDuty) >= num:i($PeriodValue)"!][!//
    [!VAR "ScaledDuty" = "num:i($PeriodValue)"!][!//
  [!ENDIF!][!//
 
  [!IF "$PeriodValue = num:i(0)"!][!//
    [!VAR "ScaledDuty" = "num:i(0)"!][!//
  [!ENDIF!][!//
 
  /* Get Abolute Shift value */
  [!IF "$classvalue = 'PWM_FIXED_PERIOD' or $classvalue = 'PWM_VARIABLE_PERIOD' or $PwmTimerUsed = num:i(1)"!][!//
    [!VAR "ShiftValue" = "num:i(0)"!][!//
  [!ELSE!]
    [!IF "$classvalue = 'PWM_FIXED_PERIOD_SHIFTED'"!][!//
      /* GetShiftLead */
      [!VAR "ShiftValue" = "num:i(./PwmShiftValue)"!][!//
      [!IF "($DutyShiftInTicks = 'false')"!][!//
        /* Relative */
        [!VAR "ShiftValue" = "bit:shr((num:i($ShiftValue) * num:i($PeriodValue)),15)"!][!//
      [!ENDIF!][!//
      [!IF "$PeriodValue = num:i(0) or $ShiftValue >= $PeriodValue"!][!//
        [!VAR "ShiftValue" = "num:i(0)"!][!//
      [!ENDIF!][!//
    [!ELSE!]
      /* GetCenterLead */
      [!IF "$ScaledDuty < $PeriodValue"!][!//
        [!VAR "ShiftValue" = "(num:i($PeriodValue)-num:i($ScaledDuty)) div 2"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDNOCODE!][!//
/*******************************************************************************
 *  Channel Number        : [!"$PwmLogicalChId"!]
 *  Channel Symbolic Name : Pwm_17_GtmCcu6Conf_PwmChannel_[!"$NodeName"!]
 *  Channel Class         : [!"$classvalue"!]
*******************************************************************************/
  {
    [!"$PwmLogicalChId"!], /* Pwm logical channel ID */
    [!"$PwmTimerUsed"!], /* Timer used GTM:0/CCU6:1 */
[!IF "$Notification = 'STD_ON'"!][!//
    #if (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
    [!"$Notify"!], /* Notification function */
    #endif
[!ENDIF!][!//
    Pwm_lConfigChannel(
                    [!"$ShiftReset"!]U,/* Channel reset from other channel or not*/
                    [!"text:replace($classvalue,'PWM','PWM_17_GTMCCU6')"!],/* Channel Class */
                    [!"$ChannelCoherency"!],/* Coherency */
                    [!"text:replace($idlestate,'PWM','PWM_17_GTMCCU6')"!], /* channel Idle state */
                    [!"text:replace($polarity,'PWM','PWM_17_GTMCCU6')"!]  /* channel polarity */
                  ),
    (Pwm_17_GtmCcu6_PeriodType)[!"num:inttohex($PeriodValue)"!], /* Default Period */
    (uint32)[!"num:inttohex($ScaledDuty)"!], /* Default Duty Cycle */
    (uint32)[!"num:inttohex($ShiftValue)"!], /* Shift Value */
[!IF "$PwmTimerUsed = num:i(0)"!][!//
[!IF "$VariantsConfigured = num:i(1)"!][!//
    (const void*)&Pwm_kChannelConfigGtm_Core[!"$CoreId"!]_[!"$PredefinedVarName"!][[!"num:i(num:i($GtmChannelIndex) - num:i(1))"!]]
[!ELSE!][!//
    (const void*)&Pwm_kChannelConfigGtm_Core[!"$CoreId"!][[!"num:i(num:i($GtmChannelIndex) - num:i(1))"!]]
[!ENDIF!][!//
[!ELSE!][!//
[!IF "$VariantsConfigured = num:i(1)"!][!//
    (const void*)&Pwm_kChannelConfigCcu6_Core[!"$CoreId"!]_[!"$PredefinedVarName"!][[!"num:i(num:i($Ccu6ChannelIndex) - num:i(1))"!]]
[!ELSE!][!//
    (const void*)&Pwm_kChannelConfigCcu6_Core[!"$CoreId"!][[!"num:i(num:i($Ccu6ChannelIndex) - num:i(1))"!]]
[!ENDIF!][!//
[!ENDIF!][!//
 /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
  * by violating this MISRA rule. */
  },
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDFOR!][!//
};
[!ENDIF!][!//
/* [cover parentID={4792FFBE-31C3-4655-841B-ABD19E034213}]
  Code data Structure for selected Core
[/cover] */
[!IF "$VariantsConfigured = num:i(1)"!][!//
static const Pwm_17_GtmCcu6_CoreConfigType Pwm_CoreConfigCore[!"$CoreId"!]_[!"$PredefinedVarName"!] =
[!ELSE!][!//
static const Pwm_17_GtmCcu6_CoreConfigType Pwm_CoreConfigCore[!"$CoreId"!] =
[!ENDIF!][!//
{
  (Pwm_17_GtmCcu6_ChannelType)[!"num:i($MaxChannelsCore)"!]U,
  [!IF "$MaxChannelsCore = num:i(0)"!][!//
   NULL_PTR
  [!ELSE!][!//
[!IF "$VariantsConfigured = num:i(1)"!][!//
  (const Pwm_17_GtmCcu6_ChannelConfigType*)&Pwm_kChannelConfigurationCore[!"$CoreId"!]_[!"$PredefinedVarName"!]
[!ELSE!][!//
  (const Pwm_17_GtmCcu6_ChannelConfigType*)&Pwm_kChannelConfigurationCore[!"$CoreId"!]
[!ENDIF!][!//
  [!ENDIF!][!//
  /* MISRA2012_RULE_1_3_JUSTIFICATION: Var Pwm_kChannelConfigurationCore<x> is 
  of type Pwm_17_GtmCcu6_ChannelConfigType. No side effects foreseen
  by violating this MISRA rule. */
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"$CoreId"!]_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function 
  before MemMap inclusion It complies to Autosar guidelines. */
#include "Pwm_17_GtmCcu6_MemMap.h"

[!ENDIF!][!//
[!ENDFOR!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function 
  before MemMap inclusion It complies to Autosar guidelines. */
#include "Pwm_17_GtmCcu6_MemMap.h"
/* MISRA2012_RULE_8_7_JUSTIFICATION: Module configuration data structure
   declaration as per Autosar guidelines. This data structure is needed
   by SW units using Pwm Driver APIs */
/* MISRA2012_RULE_8_4_JUSTIFICATION: Definition is as per Autosar guidelines */
/* [cover parentID={64A5C335-632A-4007-B2CD-2FAC1B118DDB}]
   Pwm config structure
[/cover] */
[!IF "$VariantsConfigured = num:i(1)"!][!//
const Pwm_17_GtmCcu6_ConfigType Pwm_17_GtmCcu6_Config_[!"$PredefinedVarName"!] =
[!ELSE!][!//
const Pwm_17_GtmCcu6_ConfigType Pwm_17_GtmCcu6_Config =
[!ENDIF!][!//
{
  {
[!FOR "CoreId" = "num:i(0)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
[!VAR "TempCoreId" = "concat('CORE',$CoreId)"!][!//
[!IF "(text:contains( text:split($CGAllocatedCores,','), $TempCoreId)) or ($CGMasterCoreId = $TempCoreId)"!][!//
    /* MISRA2012_RULE_11_8_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule */
[!IF "$VariantsConfigured = num:i(1)"!][!//
    (Pwm_17_GtmCcu6_CoreConfigType*)&Pwm_CoreConfigCore[!"$CoreId"!]_[!"$PredefinedVarName"!][!IF "$CoreId < num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!],[!ENDIF!]
[!ELSE!][!//
    (Pwm_17_GtmCcu6_CoreConfigType*)&Pwm_CoreConfigCore[!"$CoreId"!][!IF "$CoreId < num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!],[!ENDIF!]
[!ENDIF!][!//
   /* MISRA2012_RULE_11_8_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule */
[!ELSE!][!//
    NULL_PTR[!IF "$CoreId < num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!],[!ENDIF!]
[!ENDIF!][!//
[!ENDFOR!][!//
  },
  /* MISRA2012_RULE_11_8_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule */
[!IF "$VariantsConfigured = num:i(1)"!][!//
  (uint8*)&Pwm_ChannelIndexMap_[!"$PredefinedVarName"!],
[!ELSE!][!//
  (uint8*)&Pwm_ChannelIndexMap,
[!ENDIF!][!//
  { 
    [!"num:inttohex($CCU6Kernel0)"!]U,[!// /* CCU6Kernel0*/
    [!"num:inttohex($CCU6Kernel1)"!]U[!// /* CCU6Kernel1*/
  }
   
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function 
  before MemMap inclusion It complies to Autosar guidelines. */
#include "Pwm_17_GtmCcu6_MemMap.h"
[!ENDSELECT!][!//
