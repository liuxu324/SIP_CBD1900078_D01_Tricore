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
**  FILENAME  : Mcu_17_TimerIp_Cfg.c                                          **
**                                                                            **
**  VERSION   : 11.0.0                                                        **
**                                                                            **
**  DATE      : 2018-09-12                                                    **
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
**  TRACEABILITY : [cover parentID]                                           **
**                                                                            **
**  DESCRIPTION  : Timer IP user data code template source file for Mcu Driver**
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*************************************************************************/!][!//
[!//
/*****************************************************************************
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
**  FILENAME  : Mcu_17_TimerIp_Cfg.c                                          **
**                                                                            **
**  VERSION   : 8.0.0                                                         **
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
**  DESCRIPTION :  Timer IP user configuration generated out of ECUC file     **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                            Includes                                        **
*******************************************************************************/
/* Include module header file */
#include "Mcu_17_TimerIp_Cfg.h"
[!NOCODE!]
[!INCLUDE "Mcu_17_TimerIp.m"!][!//

[!/*[cover parentID={7AD9B314-7816-40be-81EC-989A81A763E3}]*/!][!//
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Mcu')[1]"!][!//

  [!SELECT "./McuHardwareResourceAllocationConf/*[1]/*"!][!//
    [!VAR "ModuleConf" = "node:name(.)"!]
    [!/* ERU HW Allocation */!]
    [!IF "$ModuleConf = 'McuEruAllocationConf'"!][!//
      [!VAR "EruUserDataInfo" = "'OGU#0_0,OGU#1_0,OGU#2_0,OGU#3_0,OGU#4_0,OGU#5_0,OGU#6_0,OGU#7_0,'"!]
      [!VAR "EruChannels" = "'McuEruChannelInputLineConf#INP,McuEruChannelOutputUnitConf#OUT'"!][!//
      [!FOR "EruChIndex" = "num:i(0)" TO "num:i(ecu:get('Eru.NoOfEruOutputChannels')) - num:i(1)"!][!//
        [!FOR "index" = "1" TO "count(text:split($EruChannels, ','))"!]
          [!VAR "temp" = "text:split($EruChannels, ',')[position() = $index]"!]
          [!VAR "CurrEruChName" = "substring-before($temp, '#')"!][!//
          [!VAR "CurrEruLiteral" = "substring-after($temp, '#')"!][!//
          [!VAR "NotUsedLiteral" = "concat('ERU_CHANNEL_', $CurrEruLiteral, '_NOT_USED')"!]
          [!VAR "CurrNodeName" = "concat($CurrEruChName,'_',num:i($EruChIndex))"!][!//
          [!IF "(./*[1]/*[@name = $CurrEruChName]/*[@name = $CurrNodeName]/*[@name = $CurrEruChName] != $NotUsedLiteral)"!][!//
            [!/* Verify channel allocation for ADC */!]
            [!VAR "UsedByLiteral"  ="concat('ERU_CHANNEL_', $CurrEruLiteral, '_USED_BY_ADC_DRIVER')"!]
            [!IF "(./*[1]/*[@name = $CurrEruChName]/*[@name = $CurrNodeName]/*[@name = $CurrEruChName] = $UsedByLiteral)"!][!//
              [!CALL "Mcu_17_TimerIp_CG_ConfigEruUserData", "EruChUserInfo"= "'Adc'", "Node" = "$CurrNodeName", "EruChType" = "$CurrEruLiteral", "EruUserData" = "$EruUserDataInfo""!][!//
            [!VAR "EruUserDataInfo" = "$EruUserData"!][!// Update the User data post processing
            [!ENDIF!][!//
            [!/* Verify channel allocation for ICU */!]
            [!VAR "UsedByLiteral"  ="concat('ERU_CHANNEL_', $CurrEruLiteral, '_USED_BY_ICU_DRIVER')"!]
            [!IF "(./*[1]/*[@name = $CurrEruChName]/*[@name = $CurrNodeName]/*[@name = $CurrEruChName] = $UsedByLiteral)"!][!//
              [!CALL "Mcu_17_TimerIp_CG_ConfigEruUserData", "EruChUserInfo"= "'Icu'", "Node" = "$CurrNodeName", "EruChType" = "$CurrEruLiteral", "EruUserData" = "$EruUserDataInfo""!][!//
            [!VAR "EruUserDataInfo" = "$EruUserData"!][!// Update the User data post processing
            [!ENDIF!][!//
          [!ENDIF!][!//
        [!ENDFOR!]
      [!ENDFOR!]
      [!/* Append EIFR Mask to EruData for each OGU */!]
      [!FOR "EruChIndex" = "num:i(1)" TO "(num:i(ecu:get('Eru.NoOfEruOutputChannels')) div 2)"!][!//
        [!VAR "Ogu1" = "text:split($EruUserDataInfo, ',')[num:i($EruChIndex)]"!][!//
        [!VAR "Ogu2" = "text:split($EruUserDataInfo, ',')[num:i($EruChIndex) + num:i(4)]"!][!//
        [!/* RegEx for fetching the Timer Used and Modifying User Data */!]
        [!VAR "fetchOgu1Selected" = "concat( '^', $Ogu1, '.*$' )"!]
        [!VAR "fetchOgu2Selected" = "concat( '^', $Ogu2, '.*$' )"!]
        [!VAR "EruUserDataSelected1" = "translate(text:grep(text:split($EruUserDataInfo, ','), $fetchOgu1Selected), '[]', '')"!]
        [!VAR "EruUserDataSelected2" = "translate(text:grep(text:split($EruUserDataInfo, ','), $fetchOgu2Selected), '[]', '')"!]
        [!VAR "EruData1" = "bit:and(num:i((substring-after($EruUserDataSelected1 ,'_'))), num:i(16711935))"!]
        [!VAR "EruData2" = "bit:and(num:i((substring-after($EruUserDataSelected2 ,'_'))), num:i(16711935))"!]
        [!/* Check if any input channel is used or not */!]
        [!IF "$EruData1 = num:i(0) and $EruData2 = num:i(0)"!]
          [!VAR "EruMask"  = "num:i(0)"!]
        [!ELSE!]
          [!VAR "EruMask"  = "bit:or(bit:shl(num:i(1), bit:and($EruData1, num:i(255))), bit:shl(num:i(1), bit:and($EruData2, num:i(255))))"!]
        [!ENDIF!]
        [!/* Modify the unused Channel as 0xFF */!]
        [!IF "$EruData1 = num:i(0) and $EruMask != num:i(0)"!]
          [!/* Append the mask value to the user data of the OGUs*/!]
          [!VAR "EruData1" = "bit:or(bit:shl($EruMask,num:i(24)), num:i(255))"!]
          [!VAR "EruData1" = "bit:or($EruData1, num:i((substring-after($EruUserDataSelected1 ,'_'))))"!]
        [!ELSE!]
          [!VAR "EruData1" = "bit:or(bit:shl($EruMask,num:i(24)), num:i((substring-after($EruUserDataSelected1 ,'_'))))"!]
        [!ENDIF!]
        [!IF "$EruData2 = num:i(0) and $EruMask != num:i(0)"!]
          [!/* Append the mask value to the user data of the OGUs*/!]
          [!VAR "EruData2" = "bit:or(bit:shl($EruMask,num:i(24)), num:i(255))"!]
          [!VAR "EruData2" = "bit:or($EruData2, num:i((substring-after($EruUserDataSelected2 ,'_'))))"!]
        [!ELSE!]
          [!VAR "EruData2" = "bit:or(bit:shl($EruMask,num:i(24)), num:i((substring-after($EruUserDataSelected2 ,'_'))))"!]
        [!ENDIF!]
        [!VAR "ModifyEruUserData1" = "text:replaceAll($EruUserDataSelected1, substring-after($EruUserDataSelected1 ,'_'), $EruData1)"!]
        [!VAR "ModifyEruUserData2" = "text:replaceAll($EruUserDataSelected2, substring-after($EruUserDataSelected2 ,'_'), $EruData2)"!]
        [!VAR "EruUserDataInfo" = "text:replaceAll($EruUserDataInfo, $EruUserDataSelected1, $ModifyEruUserData1)"!]
        [!VAR "EruUserDataInfo" = "text:replaceAll($EruUserDataInfo, $EruUserDataSelected2, $ModifyEruUserData2)"!]
      [!ENDFOR!][!//
      [!CODE!]
      [!CR!]
      [!AUTOSPACING!]
      [!INDENT "0"!]
      [!/*[/cover]*/!][!//
      [!/* 32 Bit Section */!]
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      #define MCU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
      /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
        without safegaurd. It complies to Autosar guidelines. */
      /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header included as per Autosar
        guidelines. */
      #include "Mcu_MemMap.h"
      [!ENDINDENT!]
      [!CR!]
      [!INDENT "0"!]
      /* MISRA2012_RULE_8_4_JUSTIFICATION: The
      declaration for Mcu_17_Eru_ChUserData is present in Mcu_17_TimerIp.c.
      No side effects foreseen by violating this MISRA rule. */
      /* MISRA2012_RULE_8_9_JUSTIFICATION: This constant is made used in ISRs
      defined in Mcu_17_TimerIp.c for the channel user information. The
      declaration for the same is present in Mcu_17_TimerIp.c. Hence can't
      be made block scope. No side effects foreseen by violating this MISRA rule. */
      [!/*[cover parentID= {2E57EA96-C6D4-4fde-9CDC-FF671A515A7D}][/cover]*/!][!//
      [!/*[cover parentID= {B8255B10-B98F-4ece-8255-AC9DD0388994}][/cover]*/!][!//
      const uint32 Mcu_17_Eru_ChUserData[MCU_17_ERU_NO_OF_OGU] =
      {
        [!INDENT "2"!]
        [!FOR "EruChIndex" = "num:i(1)" TO "num:i(ecu:get('Eru.NoOfEruOutputChannels'))"!][!//
          [!VAR "OguId" = "text:split($EruUserDataInfo, ',')[num:i($EruChIndex)]"!][!//
          [!"num:inttohex(num:i((substring-after($OguId ,'_'))), num:i(8))"!][!IF "$EruChIndex != num:i(ecu:get('Eru.NoOfEruOutputChannels'))"!],[!ENDIF!]
          [!CR!]
        [!ENDFOR!][!//
        [!ENDINDENT!]
      };
      [!ENDINDENT!]
      [!CR!]
      [!INDENT "0"!]
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      #define MCU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
      /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
        without safegaurd. It complies to Autosar guidelines. */
      /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header included as per Autosar
        guidelines. */
      #include "Mcu_MemMap.h"
      [!ENDINDENT!]
      [!ENDCODE!]
    [!ENDIF!]
  [!ENDSELECT!][!//

  [!/* 16 Bit Section */!]
  [!CODE!]
  [!CR!]
  [!AUTOSPACING!]
  [!INDENT "0"!]
  [!/*[/cover]*/!][!//
  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  #define MCU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_16
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
    without safegaurd. It complies to Autosar guidelines. */
  /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header included as per Autosar
    guidelines. */
  #include "Mcu_MemMap.h"
  [!ENDINDENT!]
  [!CR!]
  [!ENDCODE!]
  [!SELECT "./McuHardwareResourceAllocationConf/*[1]/*"!][!//
    [!VAR "ModuleConf" = "node:name(.)"!]
    [!/* GTM HW Allocation */!]
    [!IF "$ModuleConf = 'McuGtmAllocationConf'"!][!//
      [!IF "ecu:get('Gtm.Available')='true'"!][!//
        [!SELECT "./*[1]"!][!//
          [!/* GTM - ATOM  CHANNELS */!]
          [!VAR "AtomUserDataInfo" = "''"!][!//
          [!VAR "TomUserDataInfo" = "''"!][!//
          [!VAR "TimUserDataInfo" = "''"!][!//
          [!IF "node:containsValue(../*/*/*/McuGtmAtomChannelAllocationConf/*/McuGtmAtomChannelAllocationConf, 'GTM_ATOM_CHANNEL_USED_BY_ADC') = 'true'"!][!//
            [!LOOP "node:paths(../*/*/*/McuGtmAtomChannelAllocationConf/*[McuGtmAtomChannelAllocationConf='GTM_ATOM_CHANNEL_USED_BY_ADC'])"!][!//
              [!VAR "ModuleId" = "substring-before(substring-after(., 'McuGtmAtomAllocationConf_'), '/')"!]
              [!VAR "ChannelId" = "substring(substring-after(., 'McuGtmAtomChannelAllocationConf_'), num:i(1))"!]
              [!VAR "AtomUserDataInfo" = "concat($AtomUserDataInfo, 'Adc_Atom',$ModuleId,'#_',$ChannelId,'#,')"!][!//
            [!ENDLOOP!]
          [!ENDIF!][!//
          [!IF "node:containsValue(../*/*/*/McuGtmAtomChannelAllocationConf/*/McuGtmAtomChannelAllocationConf, 'GTM_ATOM_CHANNEL_USED_BY_WDG') = 'true'"!][!//
            [!LOOP "node:paths(../*/*/*/McuGtmAtomChannelAllocationConf/*[McuGtmAtomChannelAllocationConf='GTM_ATOM_CHANNEL_USED_BY_WDG'])"!][!//
              [!VAR "ModuleId" = "substring-before(substring-after(., 'McuGtmAtomAllocationConf_'), '/')"!]
              [!VAR "ChannelId" = "substring(substring-after(., 'McuGtmAtomChannelAllocationConf_'), num:i(1))"!]
              [!VAR "AtomUserDataInfo" = "concat($AtomUserDataInfo, 'Wdg_Atom',$ModuleId,'#_',$ChannelId,'#,')"!][!//
            [!ENDLOOP!]
          [!ENDIF!][!//
          [!IF "node:containsValue(../*/*/*/McuGtmAtomChannelAllocationConf/*/McuGtmAtomChannelAllocationConf, 'GTM_ATOM_CHANNEL_USED_BY_PWM') = 'true'"!][!//
            [!LOOP "node:paths(../*/*/*/McuGtmAtomChannelAllocationConf/*[McuGtmAtomChannelAllocationConf='GTM_ATOM_CHANNEL_USED_BY_PWM'])"!][!//
              [!VAR "ModuleId" = "substring-before(substring-after(., 'McuGtmAtomAllocationConf_'), '/')"!]
              [!VAR "ChannelId" = "substring(substring-after(., 'McuGtmAtomChannelAllocationConf_'), num:i(1))"!]
              [!VAR "AtomUserDataInfo" = "concat($AtomUserDataInfo, 'Pwm_Atom',$ModuleId,'#_',$ChannelId,'#,')"!][!//
            [!ENDLOOP!]
          [!ENDIF!][!//
          [!IF "node:containsValue(../*/*/*/McuGtmAtomChannelAllocationConf/*/McuGtmAtomChannelAllocationConf, 'GTM_ATOM_CHANNEL_USED_BY_GPT') = 'true'"!][!//
            [!LOOP "node:paths(../*/*/*/McuGtmAtomChannelAllocationConf/*[McuGtmAtomChannelAllocationConf='GTM_ATOM_CHANNEL_USED_BY_GPT'])"!][!//
              [!VAR "ModuleId" = "substring-before(substring-after(., 'McuGtmAtomAllocationConf_'), '/')"!]
              [!VAR "ChannelId" = "substring(substring-after(., 'McuGtmAtomChannelAllocationConf_'), num:i(1))"!]
              [!VAR "AtomUserDataInfo" = "concat($AtomUserDataInfo, 'Gpt_Atom',$ModuleId,'#_',$ChannelId,'#,')"!][!//
            [!ENDLOOP!]
          [!ENDIF!][!//
          [!IF "node:containsValue(../*/*/*/McuGtmAtomChannelAllocationConf/*/McuGtmAtomChannelAllocationConf, 'GTM_ATOM_CHANNEL_USED_BY_OCU') = 'true'"!][!//
            [!LOOP "node:paths(../*/*/*/McuGtmAtomChannelAllocationConf/*[McuGtmAtomChannelAllocationConf='GTM_ATOM_CHANNEL_USED_BY_OCU'])"!][!//
              [!VAR "ModuleId" = "substring-before(substring-after(., 'McuGtmAtomAllocationConf_'), '/')"!]
              [!VAR "ChannelId" = "substring(substring-after(., 'McuGtmAtomChannelAllocationConf_'), num:i(1))"!]
              [!VAR "AtomUserDataInfo" = "concat($AtomUserDataInfo, 'Ocu_Atom',$ModuleId,'#_',$ChannelId,'#,')"!][!//
            [!ENDLOOP!]
          [!ENDIF!][!//
          [!IF "node:containsValue(../*/*/*/McuGtmAtomChannelAllocationConf/*/McuGtmAtomChannelAllocationConf, 'GTM_ATOM_CHANNEL_USED_BY_DSADC') = 'true'"!][!//
            [!LOOP "node:paths(../*/*/*/McuGtmAtomChannelAllocationConf/*[McuGtmAtomChannelAllocationConf='GTM_ATOM_CHANNEL_USED_BY_DSADC'])"!][!//
              [!VAR "ModuleId" = "substring-before(substring-after(., 'McuGtmAtomAllocationConf_'), '/')"!]
              [!VAR "ChannelId" = "substring(substring-after(., 'McuGtmAtomChannelAllocationConf_'), num:i(1))"!]
              [!VAR "AtomUserDataInfo" = "concat($AtomUserDataInfo, 'Dsadc_Atom',$ModuleId,'#_',$ChannelId,'#,')"!][!//
            [!ENDLOOP!]
          [!ENDIF!][!//
          [!/* GTM - TOM  CHANNELS */!]
          [!IF "node:containsValue(../*/*/*/McuGtmTomChannelAllocationConf/*/McuGtmTomChannelAllocationConf, 'GTM_TOM_CHANNEL_USED_BY_ADC') = 'true'"!][!//
            [!LOOP "node:paths(../*/*/*/McuGtmTomChannelAllocationConf/*[McuGtmTomChannelAllocationConf='GTM_TOM_CHANNEL_USED_BY_ADC'])"!][!//
              [!VAR "ModuleId" = "substring-before(substring-after(., 'McuGtmTomAllocationConf_'), '/')"!]
              [!VAR "ChannelId" = "substring(substring-after(., 'McuGtmTomChannelAllocationConf_'), num:i(1))"!]
              [!VAR "TomUserDataInfo" = "concat($TomUserDataInfo, 'Adc_Tom',$ModuleId,'#_',$ChannelId,'#,')"!][!//
            [!ENDLOOP!]
          [!ENDIF!][!//
          [!IF "node:containsValue(../*/*/*/McuGtmTomChannelAllocationConf/*/McuGtmTomChannelAllocationConf, 'GTM_TOM_CHANNEL_USED_BY_WDG') = 'true'"!][!//
            [!LOOP "node:paths(../*/*/*/McuGtmTomChannelAllocationConf/*[McuGtmTomChannelAllocationConf='GTM_TOM_CHANNEL_USED_BY_WDG'])"!][!//
              [!VAR "ModuleId" = "substring-before(substring-after(., 'McuGtmTomAllocationConf_'), '/')"!]
              [!VAR "ChannelId" = "substring(substring-after(., 'McuGtmTomChannelAllocationConf_'), num:i(1))"!]
              [!VAR "TomUserDataInfo" = "concat($TomUserDataInfo, 'Wdg_Tom',$ModuleId,'#_',$ChannelId,'#,')"!][!//
            [!ENDLOOP!]
          [!ENDIF!][!//
          [!IF "node:containsValue(../*/*/*/McuGtmTomChannelAllocationConf/*/McuGtmTomChannelAllocationConf, 'GTM_TOM_CHANNEL_USED_BY_PWM') = 'true'"!][!//
            [!LOOP "node:paths(../*/*/*/McuGtmTomChannelAllocationConf/*[McuGtmTomChannelAllocationConf='GTM_TOM_CHANNEL_USED_BY_PWM'])"!][!//
              [!VAR "ModuleId" = "substring-before(substring-after(., 'McuGtmTomAllocationConf_'), '/')"!]
              [!VAR "ChannelId" = "substring(substring-after(., 'McuGtmTomChannelAllocationConf_'), num:i(1))"!]
              [!VAR "TomUserDataInfo" = "concat($TomUserDataInfo, 'Pwm_Tom',$ModuleId,'#_',$ChannelId,'#,')"!][!//
            [!ENDLOOP!]
          [!ENDIF!][!//
          [!IF "node:containsValue(../*/*/*/McuGtmTomChannelAllocationConf/*/McuGtmTomChannelAllocationConf, 'GTM_TOM_CHANNEL_USED_BY_GPT') = 'true'"!][!//
            [!LOOP "node:paths(../*/*/*/McuGtmTomChannelAllocationConf/*[McuGtmTomChannelAllocationConf='GTM_TOM_CHANNEL_USED_BY_GPT'])"!][!//
              [!VAR "ModuleId" = "substring-before(substring-after(., 'McuGtmTomAllocationConf_'), '/')"!]
              [!VAR "ChannelId" = "substring(substring-after(., 'McuGtmTomChannelAllocationConf_'), num:i(1))"!]
              [!VAR "TomUserDataInfo" = "concat($TomUserDataInfo, 'Gpt_Tom',$ModuleId,'#_',$ChannelId,'#,')"!][!//
            [!ENDLOOP!]
          [!ENDIF!][!//
          [!IF "node:containsValue(../*/*/*/McuGtmTomChannelAllocationConf/*/McuGtmTomChannelAllocationConf, 'GTM_TOM_CHANNEL_USED_BY_OCU') = 'true'"!][!//
            [!LOOP "node:paths(../*/*/*/McuGtmTomChannelAllocationConf/*[McuGtmTomChannelAllocationConf='GTM_TOM_CHANNEL_USED_BY_OCU'])"!][!//
              [!VAR "ModuleId" = "substring-before(substring-after(., 'McuGtmTomAllocationConf_'), '/')"!]
              [!VAR "ChannelId" = "substring(substring-after(., 'McuGtmTomChannelAllocationConf_'), num:i(1))"!]
              [!VAR "TomUserDataInfo" = "concat($TomUserDataInfo, 'Ocu_Tom',$ModuleId,'#_',$ChannelId,'#,')"!][!//
            [!ENDLOOP!]
          [!ENDIF!][!//
          [!IF "node:containsValue(../*/*/*/McuGtmTomChannelAllocationConf/*/McuGtmTomChannelAllocationConf, 'GTM_TOM_CHANNEL_USED_BY_DSADC') = 'true'"!][!//
            [!LOOP "node:paths(../*/*/*/McuGtmTomChannelAllocationConf/*[McuGtmTomChannelAllocationConf='GTM_TOM_CHANNEL_USED_BY_DSADC'])"!][!//
              [!VAR "ModuleId" = "substring-before(substring-after(., 'McuGtmTomAllocationConf_'), '/')"!]
              [!VAR "ChannelId" = "substring(substring-after(., 'McuGtmTomChannelAllocationConf_'), num:i(1))"!]
              [!VAR "TomUserDataInfo" = "concat($TomUserDataInfo, 'Dsadc_Tom',$ModuleId,'#_',$ChannelId,'#,')"!][!//
            [!ENDLOOP!]
          [!ENDIF!][!//
          [!/* GTM - TIM  CHANNELS */!]
          [!IF "node:containsValue(../*/*/*/McuGtmTimChannelAllocationConf/*/McuGtmTimChannelAllocationConf, 'GTM_TIM_CHANNEL_USED_BY_ICU') = 'true'"!][!//
            [!LOOP "node:paths(../*/*/*/McuGtmTimChannelAllocationConf/*[McuGtmTimChannelAllocationConf='GTM_TIM_CHANNEL_USED_BY_ICU'])"!][!//
              [!VAR "ModuleId" = "substring-before(substring-after(., 'McuGtmTimAllocationConf_'), '/')"!]
              [!VAR "ChannelId" = "substring(substring-after(., 'McuGtmTimChannelAllocationConf_'), num:i(1))"!]
              [!VAR "TimUserDataInfo" = "concat($TimUserDataInfo, 'Icu_Tim',$ModuleId,'#_',$ChannelId,'#,')"!][!//
            [!ENDLOOP!]
          [!ENDIF!][!//
        [!ENDSELECT!][!//
        [!/* Validate and Generate the User Data (TIM/TOM/ATOM) */!]
        [!CODE!]
        [!AUTOSPACING!]
        [!INDENT "0"!]
        const uint16
        /* MISRA2012_RULE_8_4_JUSTIFICATION: The
        declaration for Mcu_17_Gtm_AtomChUserData is present in Mcu_17_TimerIp.c.
        No side effects foreseen by violating this MISRA rule. */
        /* MISRA2012_RULE_8_9_JUSTIFICATION: This constant is made used in ISRs
        defined in Mcu_17_TimerIp.c for the channel user information. The
        declaration for the same is present in Mcu_17_TimerIp.c. Hence can't
        be made block scope. No side effects foreseen by violating this MISRA rule. */
        [!/*[cover parentID= {9D29279C-9108-47aa-920D-F4F334AB8E16}][/cover]*/!][!//
        Mcu_17_Gtm_AtomChUserData[MCU_17_GTM_NO_OF_ATOM_MODULES][MCU_17_GTM_NO_OF_ATOM_CHANNELS] =
        {
        [!NOCODE!]
        [!VAR "NumOfChs" = "num:i(ecu:get('Gtm.NumberOfAtomChannels') - 1)"!][!//
        [!VAR "NumOfMods" = "num:i(ecu:get('Gtm.NumberOfAtomModules') - 1)"!][!//
        [!CALL "Mcu_17_TimerIp_CG_ConfigGtmUserData","UserDataInfo"= "$AtomUserDataInfo","GtmIp"= "'Atom'"!][!//
        [!FOR "ModuleIndex" = "num:i(0)" TO "$NumOfMods"!][!//
          [!CODE!]
          [!INDENT "2"!]
          /* ATOM Module [!"$ModuleIndex"!] */
          {
          [!ENDINDENT!]
          [!ENDCODE!]
          [!FOR "ChIndex" = "num:i(0)" TO "$NumOfChs"!][!//
            [!VAR "CurrItem" = "concat('_Atom',$ModuleIndex,'#_',$ChIndex,'#@')"!][!//
            [!IF "contains($UserDataInfo, $CurrItem)"!][!//
              [!CODE!]
              [!INDENT "4"!]
              [!"num:inttohex(substring-before(substring-after($UserDataInfo, $CurrItem), '#'),num:i(4))"!][!IF "$ChIndex < $NumOfChs"!],[!ENDIF!][!CR!]
              [!ENDINDENT!]
              [!ENDCODE!]
            [!ELSE!]
              [!CODE!]
              [!INDENT "4"!]
              0x0000[!IF "$ChIndex < $NumOfChs"!],[!ENDIF!][!CR!]
              [!ENDINDENT!]
              [!ENDCODE!]
            [!ENDIF!]
          [!ENDFOR!]
          [!CODE!]
          [!INDENT "2"!]
          }[!IF "$ModuleIndex < $NumOfMods "!],[!ENDIF!][!CR!]
          [!ENDINDENT!]
          [!ENDCODE!]
        [!ENDFOR!]
        [!ENDNOCODE!]
        };
        [!CR!]
        const uint16
        /* MISRA2012_RULE_8_4_JUSTIFICATION: The
        declaration for Mcu_17_Gtm_TimChUserData is present in Mcu_17_TimerIp.c.
        No side effects foreseen by violating this MISRA rule. */
        /* MISRA2012_RULE_8_9_JUSTIFICATION: This constant is made used in ISRs
        defined in Mcu_17_TimerIp.c for the channel user information. The
        declaration for the same is present in Mcu_17_TimerIp.c. Hence can't
        be made block scope. No side effects foreseen by violating this MISRA rule. */
        [!/*[cover parentID= {2237F0FB-5643-473a-B9F7-9426F2D71B77}][/cover]*/!][!//
        Mcu_17_Gtm_TimChUserData[MCU_17_GTM_NO_OF_TIM_MODULES][MCU_17_GTM_NO_OF_TIM_CHANNELS] =
        {
          [!NOCODE!]
          [!VAR "NumOfChs" = "num:i(ecu:get('Gtm.NumberOfTimChannels') - 1)"!][!//
          [!VAR "NumOfMods" = "num:i(ecu:get('Gtm.NumberOfTimModules') - 1)"!][!//
          [!CALL "Mcu_17_TimerIp_CG_ConfigGtmUserData","UserDataInfo"= "$TimUserDataInfo","GtmIp"= "'Tim'"!][!//
          [!FOR "ModuleIndex" = "num:i(0)" TO "$NumOfMods"!][!//
            [!CODE!]
            [!INDENT "2"!]
            /* TIM Module [!"$ModuleIndex"!] */
            {
            [!ENDINDENT!]
            [!ENDCODE!]
            [!FOR "ChIndex" = "num:i(0)" TO "$NumOfChs"!][!//
              [!VAR "CurrItem" = "concat('_Tim',$ModuleIndex,'#_',$ChIndex,'#@')"!][!//
              [!IF "contains($UserDataInfo, $CurrItem)"!][!//
                [!CODE!]
                [!INDENT "4"!]
                [!"num:inttohex(substring-before(substring-after($UserDataInfo, $CurrItem), '#'),num:i(4))"!][!IF "$ChIndex < $NumOfChs"!],[!ENDIF!][!CR!]
                [!ENDINDENT!]
                [!ENDCODE!]
              [!ELSE!]
                [!CODE!]
                [!INDENT "4"!]
                0x0000[!IF "$ChIndex < $NumOfChs"!],[!ENDIF!][!CR!]
                [!ENDINDENT!]
                [!ENDCODE!]
              [!ENDIF!]
            [!ENDFOR!]
            [!CODE!]
            [!INDENT "2"!]
            }[!IF "$ModuleIndex < $NumOfMods "!],[!ENDIF!][!CR!]
            [!ENDINDENT!]
            [!ENDCODE!]
          [!ENDFOR!]
          [!ENDNOCODE!]
        };
        [!CR!]
        const uint16
        /* MISRA2012_RULE_8_4_JUSTIFICATION: The
        declaration for Mcu_17_Gtm_TomChUserData is present in Mcu_17_TimerIp.c.
        No side effects foreseen by violating this MISRA rule. */
        /* MISRA2012_RULE_8_9_JUSTIFICATION: This constant is made used in ISRs
        defined in Mcu_17_TimerIp.c for the channel user information. The
        declaration for the same is present in Mcu_17_TimerIp.c. Hence can't
        be made block scope. No side effects foreseen by violating this MISRA rule. */
        [!/*[cover parentID= {DE498BBD-65D1-4a4f-BE5B-276B5742AEC0}][/cover]*/!][!//
        Mcu_17_Gtm_TomChUserData[MCU_17_GTM_NO_OF_TOM_MODULES][MCU_17_GTM_NO_OF_TOM_CHANNELS] =
        {
          [!NOCODE!]
          [!VAR "NumOfChs" = "num:i(ecu:get('Gtm.NumberOfTomChannels') - 1)"!][!//
          [!VAR "NumOfMods" = "num:i(ecu:get('Gtm.NumberOfTomModules') - 1)"!][!//
          [!CALL "Mcu_17_TimerIp_CG_ConfigGtmUserData","UserDataInfo"= "$TomUserDataInfo","GtmIp"= "'Tom'"!][!//
          [!FOR "ModuleIndex" = "num:i(0)" TO "$NumOfMods"!][!//
            [!CODE!]
            [!INDENT "2"!]
            /* TOM Module [!"$ModuleIndex"!] */
            {
            [!ENDINDENT!]
            [!ENDCODE!]
            [!FOR "ChIndex" = "num:i(0)" TO "$NumOfChs"!][!//
              [!VAR "CurrItem" = "concat('_Tom',$ModuleIndex,'#_',$ChIndex,'#@')"!][!//
              [!IF "contains($UserDataInfo, $CurrItem)"!][!//
                [!CODE!]
                [!INDENT "4"!]
                [!"num:inttohex(substring-before(substring-after($UserDataInfo, $CurrItem), '#'),num:i(4))"!][!IF "$ChIndex < $NumOfChs"!],[!ENDIF!][!CR!]
                [!ENDINDENT!]
                [!ENDCODE!]
              [!ELSE!]
                [!CODE!]
                [!INDENT "4"!]
                0x0000[!IF "$ChIndex < $NumOfChs"!],[!ENDIF!][!CR!]
                [!ENDINDENT!]
                [!ENDCODE!]
              [!ENDIF!]
            [!ENDFOR!]
            [!CODE!]
            [!INDENT "2"!]
            }[!IF "$ModuleIndex < $NumOfMods "!],[!ENDIF!][!CR!]
            [!ENDINDENT!]
            [!ENDCODE!]
          [!ENDFOR!]
          [!ENDNOCODE!]
        };
        [!ENDINDENT!]
        [!ENDCODE!]
      [!ENDIF!][!//
    [!ENDIF!]

    [!/* CCU6 HW Allocation */!]
    [!IF "$ModuleConf = 'McuCcu6ModuleAllocationConf'"!][!//
      [!IF "ecu:get('Ccu6.Available')='true'"!][!//
        [!VAR "Ccu6Kernel0UserInfo"  = "num:i(0)"!][!//
        [!VAR "Ccu6Kernel1UserInfo"  = "num:i(0)"!][!//
        [!VAR "Ccu6MaxKernels" = "num:i(ecu:get('Ccu6.MaxKernals'))"!][!//
        [!FOR "Ccu6KernelIndex" = "num:i(0)" TO "(num:i($Ccu6MaxKernels)- num:i(1))"!][!//
          [!VAR "TempVal" = "num:i(0)"!][!//
            [!IF "(./*[@name = concat('McuCcu6ModuleAllocationConf','_',num:i($Ccu6KernelIndex))]/McuCcu6ModuleAllocationConf != 'CCU6_MODULE_NOT_USED')"!][!//
              [!IF "(./*[@name = concat('McuCcu6ModuleAllocationConf','_',num:i($Ccu6KernelIndex))]/McuCcu6ModuleAllocationConf = 'CCU6_MODULE_USED_BY_PWM_DRIVER')"!][!//
                [!VAR "TempVal"  = "num:i(3)"!][!//
              [!ENDIF!][!//
              [!IF "(./*[@name = concat('McuCcu6ModuleAllocationConf','_',num:i($Ccu6KernelIndex))]/McuCcu6ModuleAllocationConf = 'CCU6_MODULE_USED_BY_ICU_DRIVER')"!][!//
                [!VAR "TempVal"  = "num:i(5)"!][!//
              [!ENDIF!][!//
              [!IF "(./*[@name = concat('McuCcu6ModuleAllocationConf','_',num:i($Ccu6KernelIndex))]/McuCcu6ModuleAllocationConf = 'CCU6_MODULE_USED_BY_ADC_DRIVER')"!][!//
                [!VAR "TempVal"  = "num:i(1)"!][!//
              [!ENDIF!][!//
            [!ENDIF!][!//
          [!IF "$Ccu6KernelIndex = num:i(0)"!][!//
            [!VAR "Ccu6Kernel0UserInfo"  = "$TempVal"!][!//
          [!ENDIF!][!//
          [!IF "$Ccu6KernelIndex = num:i(1)"!][!//
            [!VAR "Ccu6Kernel1UserInfo"  = "$TempVal"!][!//
          [!ENDIF!][!//
        [!ENDFOR!][!//
      [!CODE!]
      [!AUTOSPACING!]
      [!INDENT "0"!]
      const uint16
      /* MISRA2012_RULE_8_4_JUSTIFICATION: The
      declaration for Mcu_17_Ccu6_ChUserData is present in Mcu_17_TimerIp.c.
      No side effects foreseen by violating this MISRA rule. */
      /* MISRA2012_RULE_8_9_JUSTIFICATION: This constant is made used in ISRs
      defined in Mcu_17_TimerIp.c for the channel user information. The
      declaration for the same is present in Mcu_17_TimerIp.c. Hence can't
      be made block scope. No side effects foreseen by violating this MISRA rule. */
      [!/*[cover parentID= {B85A4C46-4703-4d8f-855C-0D4235A0C46B}][/cover]*/!][!//
        Mcu_17_Ccu6_ChUserData[MCU_17_CCU6_NO_OF_KERNELS][MCU_17_CCU6_NO_OF_COMPARATORS] =
      [!VAR "Ccu6MaxKernels" = "num:i(ecu:get('Ccu6.MaxKernals'))"!][!//
      {
      [!VAR "Cc60UserInfo"  = "num:i(0)"!][!//
      [!VAR "Cc61UserInfo"  = "num:i(0)"!][!//
      [!VAR "Cc62UserInfo"  = "num:i(0)"!][!//
      [!VAR "Cc63UserInfo"  = "num:i(0)"!][!//
      [!CALL "Mcu_17_TimerIp_CG_ConfigCcu6UserData","Ccu6KernelUserInfo"= "$Ccu6Kernel0UserInfo","Ccu6KernelNumber"= "num:i(0)","Cc60UserInfo"= "$Cc60UserInfo","Cc61UserInfo"= "$Cc61UserInfo","Cc62UserInfo"= "$Cc62UserInfo","Cc63UserInfo"= "$Cc63UserInfo"!][!//
      [!INDENT "2"!]
        {
          [!"num:inttohex($Cc60UserInfo,num:i(4))"!],
          [!"num:inttohex($Cc61UserInfo,num:i(4))"!],
          [!"num:inttohex($Cc62UserInfo,num:i(4))"!],
          [!"num:inttohex($Cc63UserInfo,num:i(4))"!]
        },
      [!ENDINDENT!]
      [!IF "$Ccu6MaxKernels > 1"!][!//
      [!VAR "Cc60UserInfo"  = "num:i(0)"!][!//
      [!VAR "Cc61UserInfo"  = "num:i(0)"!][!//
      [!VAR "Cc62UserInfo"  = "num:i(0)"!][!//
      [!VAR "Cc63UserInfo"  = "num:i(0)"!][!//
      [!CALL "Mcu_17_TimerIp_CG_ConfigCcu6UserData","Ccu6KernelUserInfo"= "$Ccu6Kernel1UserInfo","Ccu6KernelNumber"= "num:i(1)","Cc60UserInfo"= "$Cc60UserInfo","Cc61UserInfo"= "$Cc61UserInfo","Cc62UserInfo"= "$Cc62UserInfo","Cc63UserInfo"= "$Cc63UserInfo"!][!//
      [!INDENT "2"!]
        {
          [!"num:inttohex($Cc60UserInfo,num:i(4))"!],
          [!"num:inttohex($Cc61UserInfo,num:i(4))"!],
          [!"num:inttohex($Cc62UserInfo,num:i(4))"!],
          [!"num:inttohex($Cc63UserInfo,num:i(4))"!]
        }
      [!ENDINDENT!]
      [!ENDIF!][!//
      };
      [!CR!]
      [!ENDINDENT!]
      [!ENDCODE!]
      [!ENDIF!][!//
    [!ENDIF!]

    [!/* GPT12 HW Allocation */!]
    [!IF "$ModuleConf = 'McuGpt12ModuleAllocationConf'"!][!//
      [!IF "ecu:get('Gpt12.Available')='true'"!][!//
        [!VAR "Gpt12UserDataInfo" = "'T2_0,T3_0,T4_0,T5_0,T6_0'"!][!//
        [!VAR "Gpt12MaxBlocks" = "num:i(ecu:get('Gpt12.MaxBlocks'))"!][!//
        [!FOR "Gpt12BlockIndex" = "num:i(0)" TO "num:i(ecu:get('Gpt12.MaxBlocks')) - num:i(1)"!][!//
            [!VAR "CurrNodeName" = "concat('McuGpt12ModuleAllocationConf','_',num:i($Gpt12BlockIndex))"!][!//
            [!IF "(./*[@name = $CurrNodeName]/McuGpt12ModuleAllocationConf != 'GPT_BLOCK_NOT_USED')"!][!//
              [!IF "(./*[@name = $CurrNodeName]/McuGpt12ModuleAllocationConf = 'GPT_BLOCK_USED_BY_ICU_DRIVER')"!][!//
                [!/* Verify and calculate User Data for ICU */!]
                [!CALL "Mcu_17_TimerIp_CG_ConfigGpt12UserData", "Gpt12BlockUserInfo"= "'Icu'", "Node" = "$CurrNodeName", "Gpt12UserData" = "$Gpt12UserDataInfo""!][!//
              [!ELSEIF "(./*[@name = $CurrNodeName]/McuGpt12ModuleAllocationConf = 'GPT_BLOCK_USED_BY_COMPLEX_DRIVER')"!]
                [!/* Calculate User Data for Complex Driver */!]
                [!CALL "Mcu_17_TimerIp_CG_ConfigGpt12UserData", "Gpt12BlockUserInfo"= "'ComplexDriver'", "Node" = "node:path(./*[@name = $CurrNodeName])", "Gpt12UserData" = "$Gpt12UserDataInfo""!][!//
              [!ENDIF!][!//
              [!VAR "Gpt12UserDataInfo" = "$Gpt12UserData"!][!// Update the User data post processing
            [!ENDIF!][!//
        [!ENDFOR!][!//
        [!VAR "TimerCount" = "count(text:split($Gpt12UserDataInfo, ','))"!]
        [!VAR "counter" = "'0'"!]
        [!CODE!]
        [!AUTOSPACING!]
        [!INDENT "0"!]
        /* MISRA2012_RULE_8_4_JUSTIFICATION: The
        declaration for Mcu_17_Gpt12_ChUserData is present in Mcu_17_TimerIp.c.
        No side effects foreseen by violating this MISRA rule. */
        /* MISRA2012_RULE_8_9_JUSTIFICATION: This constant is made used in ISRs
        defined in Mcu_17_TimerIp.c for the channel user information. The
        declaration for the same is present in Mcu_17_TimerIp.c. Hence can't
        be made block scope. No side effects foreseen by violating this MISRA rule. */
        [!/*[cover parentID= {2E57EA96-C6D4-4fde-9CDC-FF671A515A7D}][/cover]*/!][!//
        const uint16 Mcu_17_Gpt12_ChUserData[MCU_17_GPT12_NO_OF_TIMERS] =
        {
          [!INDENT "2"!]
          [!LOOP "text:split($Gpt12UserDataInfo, ',')"!][!//
              [!VAR "counter" = "num:i($counter) + num:i(1)"!]
              [!"num:inttohex(num:i((substring-after(. ,'_'))), num:i(4))"!][!IF "$counter != $TimerCount"!],[!ENDIF!]
              [!CR!]
          [!ENDLOOP!][!//
          [!ENDINDENT!]
        };
        [!ENDINDENT!]
        [!CR!]
        [!ENDCODE!]
      [!ENDIF!][!//
    [!ENDIF!]

  [!ENDSELECT!][!//
  [!CODE!]
  [!CR!]
  [!AUTOSPACING!]
  [!INDENT "0"!]
  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  #define MCU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_16
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
    without safegaurd. It complies to Autosar guidelines. */
  /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header included as per Autosar
    guidelines. */
  #include "Mcu_MemMap.h"
  [!ENDINDENT!]
  [!CR!]
  [!ENDCODE!]

  [!SELECT "./McuHardwareResourceAllocationConf/*[1]/*"!][!//
    [!VAR "ModuleConf" = "node:name(.)"!]
    [!/* STM HW Allocation */!]
    [!IF "$ModuleConf = 'McuStmAllocationConf'"!][!//
      [!VAR "StmUserDataInfo" = "'STM#0_0,STM#1_0,STM#2_0,STM#3_0,STM#4_0,STM#5_0'"!][!//
      [!VAR "StmCmpInfo" = "num:i(0)"!][!//
      [!VAR "StmComparators" = "'Cmp0,Cmp1'"!][!//
      [!FOR "StmTimerIndex" = "num:i(0)" TO "num:i(ecu:get('Stm.TotalNumberofcores')) - num:i(1)"!][!//
        [!VAR "CurrNodeName" = "concat('McuStmAllocationConf','_',num:i($StmTimerIndex))"!][!//
        [!VAR "CmpCnt" = "num:i(0)"!][!//
        [!/* Check if both comparators belong to STM */!]
        [!SELECT "./*[@name = $CurrNodeName]"!][!//
          [!SELECT "./*"!][!//
            [!IF "text:contains(node:value(.) , 'USED_BY_STM')"!][!//
              [!VAR "CmpCnt" = "num:i($CmpCnt) + num:i(1)"!][!//
            [!ENDIF!]
          [!ENDSELECT!][!//
        [!ENDSELECT!][!//
        [!IF "$CmpCnt = num:i(2)"!][!//
          [!/* Generate User Data for STM */!]
          [!VAR "StmCmpInfo" = "num:i($CmpCnt + num:i(1))"!][!//
          [!CALL "Mcu_17_TimerIp_CG_ConfigStmUserData", "StmUserInfo"= "'Stm'", "Node" = "$CurrNodeName", "StmCmp" = "$StmCmpInfo", "StmUserData" ="$StmUserDataInfo"!][!//
          [!VAR "StmUserDataInfo" = "$StmUserData"!][!// Update the User data post processing
        [!ELSE!]
          [!FOR "index" = "1" TO "count(text:split($StmComparators, ','))"!]
            [!VAR "CurrStmCmp" = "text:split($StmComparators, ',')[position() = $index]"!]
            [!VAR "ParamName" = "concat('McuStm', $CurrStmCmp, 'RegAllocationConf')"!][!//
            [!VAR "NotUsedLiteral" = "concat('STM_', text:toupper($CurrStmCmp), '_NOT_USED')"!][!//
            [!IF "(./*[@name = $CurrNodeName]/*[@name = $ParamName] != $NotUsedLiteral)"!][!//
              [!VAR "UsedByLiteral" = "concat('STM_', text:toupper($CurrStmCmp), '_USED_BY_STM')"!][!//
              [!VAR "UsedByLiteralWdg" = "concat('STM_', text:toupper($CurrStmCmp), '_USED_BY_WDG')"!][!//
              [!IF "(./*[@name = $CurrNodeName]/*[@name = $ParamName] = $UsedByLiteral)"!][!//
                [!/* Verify and calculate User Data for STM */!]
                [!CALL "Mcu_17_TimerIp_CG_ConfigStmUserData", "StmUserInfo"= "'Stm'", "Node" = "$CurrNodeName", "StmCmp" = "$index", "StmUserData" ="$StmUserDataInfo"!][!//
              [!ELSEIF "(./*[@name = $CurrNodeName]/*[@name = $ParamName] = $UsedByLiteralWdg)"!][!//
                [!/* Verify and calculate User Data for WDG */!]
                [!CALL "Mcu_17_TimerIp_CG_ConfigStmUserData", "StmUserInfo"= "'Wdg'", "Node" = "$CurrNodeName", "StmCmp" = "$index", "StmUserData" ="$StmUserDataInfo"!][!//
              [!ENDIF!][!//
              [!VAR "StmUserDataInfo" = "$StmUserData"!][!// Update the User data post processing
            [!ENDIF!][!//
          [!ENDFOR!]
        [!ENDIF!]
      [!ENDFOR!]
      [!CODE!]
      [!CR!]
      [!AUTOSPACING!]
      [!INDENT "0"!]
      [!/*[/cover]*/!][!//
      [!/* 32 Bit Section */!]
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      #define MCU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
      /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
        without safegaurd. It complies to Autosar guidelines. */
      /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header included as per Autosar
        guidelines. */
      #include "Mcu_MemMap.h"
      [!ENDINDENT!]
      [!CR!]
      [!INDENT "0"!]
      /* MISRA2012_RULE_8_4_JUSTIFICATION: The
      declaration for Mcu_17_Eru_ChUserData is present in Mcu_17_TimerIp.c.
      No side effects foreseen by violating this MISRA rule. */
      /* MISRA2012_RULE_8_9_JUSTIFICATION: This constant is made used in ISRs
      defined in Mcu_17_TimerIp.c for the channel user information. The
      declaration for the same is present in Mcu_17_TimerIp.c. Hence can't
      be made block scope. No side effects foreseen by violating this MISRA rule. */
      [!/*[cover parentID= {2E57EA96-C6D4-4fde-9CDC-FF671A515A7D}][/cover]*/!][!//
    [!/*[cover parentID= {F8761123-C0F2-441a-B4C3-E888B863DC71}][/cover]*/!][!//
      const uint32 Mcu_17_Stm_ChUserData[MCU_17_STM_NO_OF_TIMERS] =
      {
        [!INDENT "2"!]
        [!FOR "StmTimerIndex" = "num:i(1)" TO "num:i(ecu:get('Stm.TotalNumberofcores'))"!][!//
          [!VAR "StmId" = "text:split($StmUserDataInfo, ',')[num:i($StmTimerIndex)]"!][!//
          [!"num:inttohex(num:i((substring-after($StmId ,'_'))), num:i(8))"!][!IF "$StmTimerIndex != num:i(ecu:get('Stm.TotalNumberofcores'))"!],[!CR!][!ELSE!][!CR!][!ENDIF!]
        [!ENDFOR!][!//
        [!ENDINDENT!][!//
      };
      [!ENDINDENT!][!//
      [!CR!]
      [!INDENT "0"!]
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      #define MCU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
      /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
        without safegaurd. It complies to Autosar guidelines. */
      /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header included as per Autosar
        guidelines. */
      #include "Mcu_MemMap.h"
      [!ENDINDENT!]
      [!CR!]
      [!ENDCODE!]
    [!ENDIF!]
  [!ENDSELECT!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!]
