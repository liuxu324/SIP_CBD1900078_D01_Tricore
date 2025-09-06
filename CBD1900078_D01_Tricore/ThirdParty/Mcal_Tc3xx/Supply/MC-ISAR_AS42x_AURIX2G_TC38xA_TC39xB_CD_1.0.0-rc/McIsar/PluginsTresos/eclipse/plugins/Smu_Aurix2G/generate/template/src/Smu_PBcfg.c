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
**  FILENAME  : Smu_PBCfg.c                                                   **
**                                                                            **
**  VERSION   : 4.0.0                                                         **
**                                                                            **
**  DATE      : 2017-03-29                                                    **
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
**  TRACEABILITY :  [cover parentID={4DFEE3E5-D7D3-4e98-909C-463C78D77D08} ]  **
**                                                                            **
**  DESCRIPTION  : Code template source file for Smu Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!][!//
/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2017)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Smu_PBCfg.c                                                   **
**                                                                            **
**  VERSION   : 1.0.0                                                         **
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
**  DESCRIPTION  : Smu configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#include "Smu.h"
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

[!//
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Smu')"!][!//
[!//
[!/* Include Code Generator Macros */!][!//
[!NOCODE!][!//
[!INCLUDE "Smu.m"!][!//
[!//
[!ENDNOCODE!][!//
[!/*-- [cover parentID={28ED7AED-4D16-4a70-9337-05F1790E592A}]  [/cover] --*/!][!//
[!IF "not(node:exists(as:modconf('ResourceM')[1]))"!]
  [!ERROR!][!//
    SMU Code Generator: ResourceM module is not added to the project.
  [!ENDERROR!][!//
[!ENDIF!]

[!IF "not(node:exists(as:modconf('McalLib')[1]))"!]
  [!ERROR!][!//
    SMU Code Generator: McalLib module is not added to the project.
  [!ENDERROR!][!//
[!ENDIF!]

/*******************************************************************************
**                      Private Macro definition                              **
*******************************************************************************/

/*******************************************************************************
**                      Configuration Options                                 **
*******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/


/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/


/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Funtion Declarations                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
/* Memory Mapping the configuration constant */
#define SMU_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED 
/* MISRA2012_RULE_4_10_JUSTIFICATION: Smu_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of notification functions
 * before include memap.h - Accepted deviation in AUTOSAR */
#include "Smu_MemMap.h"

/* SMU Module Configuration */
/* MISRA2012_RULE_8_7_JUSTIFICATION: Module configuration data structure
   declaration is as per Autosar guidelines. This data structure is needed
   by SW units using Smu Driver APIs hence it should be declared as extern in 
   the SW unit from where it is used */
/* MISRA2012_RULE_8_4_JUSTIFICATION: Module configuration data structure
   declaration is as per Autosar guidelines. This data structure is needed
   by SW units using Smu Driver APIs hence it should be declared as extern in 
   the SW unit from where it is used */

[!/*-- [cover parentID={AB8FF32B-3870-4328-BEE4-53B23FD1C576}]  [/cover] --*/!][!//
[!/*-- [cover parentID={67AAA43D-75D2-4fde-8C6B-199B53953402}]  [/cover] --*/!][!// 
[!/*-- [cover parentID={E578EED1-EE8B-4bcf-BFED-EC5719F85BFE}]  [/cover] --*/!][!// 
[!IF "$VariantsConfigured = num:i(1)"!][!//
const Smu_ConfigType Smu_Config_[!"$PredefinedVarName"!] =
[!ELSE!]
const Smu_ConfigType Smu_Config =
[!ENDIF!][!//
{
[!SELECT "SmuConfigSet/*[num:i(1)]"!][!//
[!VAR "GroupId" = "num:i(0)"!][!//
[!VAR "StdbyGroupId" = "num:i(0)"!][!//
 [!/*-- [cover parentID={7AD99531-804F-4f22-8CF7-52FD222FC0DE}]  [/cover] --*/!][!//    
  /* FSP Cfg for Smu_core*/
[!NOCODE!][!//      
[!VAR "FSP" = "num:i(0)"!][!//
[!CALL "Smu_FSP_Value","MacInputVal" = "SmuCoreConfig/SmuCoreFSPHandling/SmuCoreFSPPrescaler1"!][!//
[!/* PRE1 bit is bit 0,1,2 */!][!//
[!VAR "FSP" = "bit:shl($OutMac_FSP,0)"!][!//
[!CALL "Smu_FSP_Value","MacInputVal" = "SmuCoreConfig/SmuCoreFSPHandling/SmuCoreFSPPrescaler2"!][!//
[!/* PRE2 bit is bit 3,4 */!][!//
[!VAR "FSP" = "bit:shl($OutMac_FSP,3)+ $FSP"!][!//
[!CALL "Smu_FSP_Value","MacInputVal" = "SmuCoreConfig/SmuCoreFSPHandling/SmuCoreFSPSignalingMode"!][!//
[!VAR "FSP" = "bit:shl($OutMac_FSP,5)+ $FSP"!][!//
[!CALL "Smu_FSP_Value","MacInputVal" = "SmuCoreConfig/SmuCoreFSPHandling/SmuCorePESOnFSP"!][!//
[!VAR "FSP" = "bit:shl($OutMac_FSP,7)+ $FSP"!][!//
[!VAR "FSD" = "SmuCoreConfig/SmuCoreFSPHandling/SmuCoreFSPFaultStateDuration"!][!//
[!VAR "FSP" = "bit:shl($FSD,22)+ $FSP"!][!//
[!ENDNOCODE!][!//
  (uint32)[!"num:inttohex($FSP)"!]U,
[!/*-- [cover parentID={EE6EF9D1-ADCC-4053-8406-C07A5606B550}]  [/cover] --*/!][!// 
  /* AGC Cfg for SmuCore*/
[!NOCODE!][!//       
[!VAR "AGC" = "num:i(0)"!][!//
[!CALL "Smu_AGC_Value","MacInputVal" = "SmuCoreConfig/SmuCoreAlarmGlobalConfig/SmuCoreInterruptSet0"!][!//
[!/* IGCS0 bit is bit 0,1,2 */!][!//
[!VAR "AGC" = "bit:shl($OutMac_AGC,0)"!][!//
[!CALL "Smu_AGC_Value","MacInputVal" = "SmuCoreConfig/SmuCoreAlarmGlobalConfig/SmuCoreInterruptSet1"!][!//
[!/* IGCS1 bit is bit 4,5,6  */!][!//
[!VAR "AGC" = "bit:shl($OutMac_AGC,4)+ $AGC"!][!//
[!CALL "Smu_AGC_Value","MacInputVal" = "SmuCoreConfig/SmuCoreAlarmGlobalConfig/SmuCoreInterruptSet2"!][!//
[!/* IGCS2 bit is bit 8,9,10  */!][!//
[!VAR "AGC" = "bit:shl($OutMac_AGC,8)+ $AGC"!][!//
[!CALL "Smu_AGC_Value","MacInputVal" = "SmuCoreConfig/SmuCoreAlarmGlobalConfig/SmuCoreCpu0ResetRequest"!][!//
[!/* RCS-CPU0 bit 16 */!][!//
[!VAR "AGC" = "bit:shl($OutMac_AGC,16)+ $AGC"!][!//
[!CALL "Smu_AGC_Value","MacInputVal" = "SmuCoreConfig/SmuCoreAlarmGlobalConfig/SmuCoreCpu1ResetRequest"!][!//
[!/* RCS-CPU0 bit 17 */!][!//
[!VAR "AGC" = "bit:shl($OutMac_AGC,17)+ $AGC"!][!//
[!CALL "Smu_AGC_Value","MacInputVal" = "SmuCoreConfig/SmuCoreAlarmGlobalConfig/SmuCoreCpu2ResetRequest"!][!//
[!/* RCS-CPU0 bit 18 */!][!//
[!VAR "AGC" = "bit:shl($OutMac_AGC,18)+ $AGC"!][!//
[!CALL "Smu_AGC_Value","MacInputVal" = "SmuCoreConfig/SmuCoreAlarmGlobalConfig/SmuCoreCpu3ResetRequest"!][!//
[!/* RCS-CPU0 bit 19 */!][!//
[!VAR "AGC" = "bit:shl($OutMac_AGC,19)+ $AGC"!][!//
[!CALL "Smu_AGC_Value","MacInputVal" = "SmuCoreConfig/SmuCoreAlarmGlobalConfig/SmuCoreCpu4ResetRequest"!][!//
[!/* RCS-CPU0 bit 20 */!][!//
[!VAR "AGC" = "bit:shl($OutMac_AGC,20)+ $AGC"!][!//
[!CALL "Smu_AGC_Value","MacInputVal" = "SmuCoreConfig/SmuCoreAlarmGlobalConfig/SmuCoreCpu5ResetRequest"!][!//
[!/* RCS-CPU0 bit 21 */!][!//
[!VAR "AGC" = "bit:shl($OutMac_AGC,21)+ $AGC"!][!//
[!CALL "Smu_AGC_Value","MacInputVal" = "SmuCoreConfig/SmuCoreAlarmGlobalConfig/SmuCoreIGCS0ActivatePES"!][!//
[!/* PES bit 24  */!][!//
[!VAR "AGC" = "bit:shl($OutMac_AGC,24)+ $AGC"!][!//
[!CALL "Smu_AGC_Value","MacInputVal" = "SmuCoreConfig/SmuCoreAlarmGlobalConfig/SmuCoreIGCS1ActivatePES"!][!//
[!/* PES bit 25  */!][!//
[!VAR "AGC" = "bit:shl($OutMac_AGC,25)+ $AGC"!][!//
[!CALL "Smu_AGC_Value","MacInputVal" = "SmuCoreConfig/SmuCoreAlarmGlobalConfig/SmuCoreIGCS2ActivatePES"!][!//
[!/* PES bit 26  */!][!//
[!VAR "AGC" = "bit:shl($OutMac_AGC,26)+ $AGC"!][!//
[!CALL "Smu_AGC_Value","MacInputVal" = "SmuCoreConfig/SmuCoreAlarmGlobalConfig/SmuCoreNMIActivatePES"!][!//
[!/* PES bit 27  */!][!//
[!VAR "AGC" = "bit:shl($OutMac_AGC,27)+ $AGC"!][!//
[!CALL "Smu_AGC_Value","MacInputVal" = "SmuCoreConfig/SmuCoreAlarmGlobalConfig/SmuCoreCpuResetActivatePES"!][!//
[!/* PES bit 28  */!][!//
[!VAR "AGC" = "bit:shl($OutMac_AGC,28)+ $AGC"!][!//
[!CALL "Smu_AGC_Value","MacInputVal" = "SmuCoreConfig/SmuCoreAlarmGlobalConfig/SmuCoreEnableFaultToRunState"!][!//
[!/* EFRST bit is bit 29  */!][!//
[!VAR "AGC" = "bit:shl($OutMac_AGC,29)+ $AGC"!][!//
[!ENDNOCODE!][!//
  (uint32)[!"num:inttohex($AGC)"!]U,
[!/*-- [cover parentID={2768A972-3E7B-4eb2-8655-C6C6184069F6}]  [/cover] --*/!][!//      
  /* RTC Cfg for SmuCore*/
[!NOCODE!][!//  
[!//  /* SMU Recovery Timer "!] */
[!VAR "RT0" = "SmuCoreConfig/SmuCoreRecoveryTimer/SmuCoreEnableRT0"!][!//
[!VAR "RT1" = "SmuCoreConfig/SmuCoreRecoveryTimer/SmuCoreEnableRT1"!][!//
[!VAR "RTD" = "num:i(SmuCoreConfig/SmuCoreRecoveryTimer/SmuCoreRTDuration)"!][!//
[!IF "(($RT0 = 'SMU_RT_ENABLE')and($RT1 = 'SMU_RT_DISABLE'))"!][!//
[!VAR "RTD" = "(bit:shl(1,0) + bit:shl($RTD,8))"!][!//
[!ELSEIF "(($RT0 = 'SMU_RT_DISABLE')and($RT1 = 'SMU_RT_ENABLE'))"!]
[!VAR "RTD" = "(bit:shl(1,1) + bit:shl($RTD,8))"!][!//
[!ELSEIF "(($RT0 = 'SMU_RT_ENABLE')and($RT1 = 'SMU_RT_ENABLE'))"!]
[!VAR "RTD" = "(bit:shl(1,0) + bit:shl(1,1) + bit:shl($RTD,8))"!][!//
[!ELSEIF "(($RT0 = 'SMU_RT_DISABLE')and($RT1 = 'SMU_RT_DISABLE'))"!]
[!VAR "RTD" = "bit:shl($RTD,8)"!][!//
[!ELSE!] [!//
[!ENDIF!] [!//  
[!ENDNOCODE!][!//  
  (uint32)[!"num:inttohex($RTD)"!]U,
 [!/*-- [cover parentID={8A1A544F-0290-4477-B35E-1E0CC7960FB1}]  [/cover] --*/!][!// 
  /* RTAC00 Cfg for SmuCore*/
[!NOCODE!][!//      
[!VAR "TotalRTAC0Config" = "num:i(count(SmuCoreConfig/SmuCoreRT0Alarm/*))"!][!// 
[!VAR "RTAC00" = "num:i(0)"!][!//
[!VAR "RTAC01" = "num:i(0)"!][!//
[!FOR "RTAC0Id" ="num:i(1)" TO "(num:i($TotalRTAC0Config))"!][!//
[!SELECT "SmuCoreConfig/SmuCoreRT0Alarm/*[num:i($RTAC0Id)]"!][!//
[!CALL "Smu_RTACfg_Value","MacInputVal" = "SmuCoreRT0AlarmGroupId"!][!//
[!VAR "RTACVar1" = "$OutMac_RTACCfg"!][!//
[!VAR "RTACVar2" = "SmuCoreRT0AlarmId"!][!//
[!IF "($RTAC0Id = num:i(1)) or ($RTAC0Id = num:i(2))"!]
[!VAR "RTAC00" = "bit:or($RTAC00,(bit:shl($RTACVar1,(($RTAC0Id - num:i(1)) * num:i(16)))))"!][!//
[!VAR "RTAC00" = "bit:or($RTAC00,(bit:shl($RTACVar2,(($RTAC0Id - num:i(1)) * num:i(16))+num:i(4))))"!][!//
[!ELSE!]
[!VAR "RTAC01" = "bit:or($RTAC01,(bit:shl($RTACVar1,(($RTAC0Id - num:i(3)) * num:i(16)))))"!][!//
[!VAR "RTAC01" = "bit:or($RTAC01,(bit:shl($RTACVar2,(($RTAC0Id - num:i(3)) * num:i(16))+num:i(4))))"!][!//
[!ENDIF!]
[!ENDSELECT!][!//
[!ENDFOR!][!// 
[!ENDNOCODE!][!//
  (uint32)[!"num:inttohex($RTAC00)"!]U,
[!/*-- [cover parentID={4CD0C998-6D86-4393-A611-E9BBB08A6E25}]  [/cover] --*/!][!//  
  /* RTAC01 Cfg for SmuCore*/
  (uint32)[!"num:inttohex($RTAC01)"!]U,
[!/*-- [cover parentID={FD1591E2-640E-4983-90D0-E7B9CAF9C7F7} ]  [/cover] --*/!][!//  
  /* RTAC10 Cfg for SmuCore*/
[!NOCODE!][!//      
[!VAR "TotalRTAC1Config" = "num:i(count(SmuCoreConfig/SmuCoreRT1Alarm/*))"!][!// 
[!VAR "RTAC10" = "num:i(0)"!][!//
[!VAR "RTAC11" = "num:i(0)"!][!//
[!FOR "RTAC1Id" ="num:i(1)" TO "(num:i($TotalRTAC1Config))"!][!//
[!SELECT "SmuCoreConfig/SmuCoreRT1Alarm/*[num:i($RTAC1Id)]"!][!//
[!CALL "Smu_RTACfg_Value","MacInputVal" = "SmuCoreRT1AlarmGroupId"!][!//
[!VAR "RTACVar1" = "$OutMac_RTACCfg"!][!//
[!VAR "RTACVar2" = "SmuCoreRT1AlarmId"!][!//
[!IF "($RTAC1Id = num:i(1)) or ($RTAC1Id = num:i(2))"!]
[!VAR "RTAC10" = "bit:or($RTAC10,(bit:shl($RTACVar1,(($RTAC1Id - num:i(1)) * num:i(16)))))"!][!//
[!VAR "RTAC10" = "bit:or($RTAC10,(bit:shl($RTACVar2,(($RTAC1Id - num:i(1)) * num:i(16))+num:i(4))))"!][!//
[!ELSE!]
[!VAR "RTAC11" = "bit:or($RTAC11,(bit:shl($RTACVar1,(($RTAC1Id - num:i(3)) * num:i(16)))))"!][!//
[!VAR "RTAC11" = "bit:or($RTAC11,(bit:shl($RTACVar2,(($RTAC1Id - num:i(3)) * num:i(16))+num:i(4))))"!][!//
[!ENDIF!]
[!ENDSELECT!][!//
[!ENDFOR!][!// 
[!ENDNOCODE!][!//
  (uint32)[!"num:inttohex($RTAC10)"!]U,
[!/*-- [cover parentID={0EDD2B94-0EAB-4bde-9365-6F34C406E03F}]  [/cover] --*/!][!//     
  /* RTAC11 Cfg for SmuCore*/
  (uint32)[!"num:inttohex($RTAC11)"!]U,

[!ENDSELECT!][!//
  
  /* CMD_STDBY config for SmuStdby*/
[!NOCODE!][!//       
[!VAR "CMD_STDBY" = "num:i(0)"!][!//
[!SELECT "SmuGeneral"!][!// 
[!CALL "Smu_CMD_STDBY_Value","MacInputVal" = "SmuStdbyEnable"!][!//
[!/* SMUEN is bit 0 */!][!//
[!VAR "CMD_STDBY" = "bit:shl($OutMac_CMD_STDBY,0)"!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!][!//
  (uint32)[!"num:inttohex($CMD_STDBY)"!]U, 
  
  /*AlarmConfig for SmuCore*/
  {
[!SELECT "SmuConfigSet/*[1]/SmuCoreConfig"!][!// 
[!VAR "TotalAlarmGroupConfig" = "num:i(count(SmuCoreAlarmGroup/*))"!][!//
[!FOR "AlmgrpId" ="num:i(1)" TO "(num:i($TotalAlarmGroupConfig))"!][!// 
[!SELECT "SmuCoreAlarmGroup/*[SmuCoreAlmGrpId = num:i($AlmgrpId - num:i(1))]"!][!//    
[!VAR "TotalAlarmConfig" = "num:i(count(SmuCoreAlarmBehavior/*))"!][!// 
[!NOCODE!][!//  
[!VAR "AGCF0" = "num:i(0)"!][!//
[!VAR "AGCF1" = "num:i(0)"!][!//
[!VAR "AGCF2" = "num:i(0)"!][!// 
[!FOR "AlmId" ="num:i(1)" TO "(num:i($TotalAlarmConfig))"!][!//
[!SELECT "SmuCoreAlarmBehavior/*[SmuCoreAlmBehaviourId = num:i($AlmId - 1)]"!][!//
[!CALL "Smu_AlmCfg_Value","MacInputVal" = "SmuCoreAlarmIntBeh"!][!// 
[!VAR "IntAlramBeh" = "$OutMac_AlmCfg"!][!//
[!VAR "Bit0" = "num:i(0)"!][!//
[!VAR "Bit1" = "num:i(0)"!][!//
[!VAR "Bit2" = "num:i(0)"!][!// 
[!VAR "Bit0" = "bit:shr(bit:and($IntAlramBeh,(bit:shl(num:i(1),0))),0)"!][!//
[!VAR "Bit1" = "bit:shr(bit:and($IntAlramBeh,(bit:shl(num:i(1),1))),1)"!][!//
[!VAR "Bit2" = "bit:shr(bit:and($IntAlramBeh,(bit:shl(num:i(1),2))),2)"!][!//
[!IF "$Bit0 = num:i(1)"!][!//
[!VAR "AGCF0" = "bit:or($AGCF0,(bit:shl(num:i(1),($AlmId - num:i(1)))))"!][!//
[!ENDIF!] [!//
[!IF "$Bit1 = num:i(1)"!][!//
[!VAR "AGCF1" = "bit:or($AGCF1,(bit:shl(num:i(1),($AlmId - num:i(1)))))"!][!//
[!ENDIF!][!//
[!IF "$Bit2 = num:i(1)"!][!//
[!VAR "AGCF2" = "bit:or($AGCF2,(bit:shl(num:i(1),($AlmId - num:i(1)))))"!][!//
[!ENDIF!] [!//  
[!ENDSELECT!][!//
[!ENDFOR!][!// 
[!VAR "GroupId" = "$GroupId + num:i(1)"!][!//
[!ENDNOCODE!][!//
    [!"num:inttohex($AGCF0)"!]U,[!"num:inttohex($AGCF1)"!]U,[!"num:inttohex($AGCF2)"!]U[!IF "$GroupId < num:i(12)"!],[!ELSE!][!VAR "GroupId" = "num:i(0)"!][!ENDIF!][!//
[!//    
[!ENDSELECT!][!//
[!ENDFOR!][!// 
[!ENDSELECT!][!//
  },
 [!/*-- [cover parentID={11BBBB3C-4861-4de6-9EA9-519073F51807}]  [/cover] --*/!][!//    
  /*AlarmFspConfig for SmuCore*/
  {
[!SELECT "SmuConfigSet/*[1]/SmuCoreConfig"!][!// 
[!VAR "TotalAlarmGroupConfig" = "num:i(count(SmuCoreAlarmGroup/*))"!][!//
[!FOR "AlmgrpId" ="num:i(1)" TO "(num:i($TotalAlarmGroupConfig))"!][!// 
[!SELECT "SmuCoreAlarmGroup/*[SmuCoreAlmGrpId = num:i($AlmgrpId - 1)]"!][!//       
[!VAR "TotalAlarmConfig" = "num:i(count(SmuCoreAlarmBehavior/*))"!][!// 
[!NOCODE!][!//  
[!VAR "AGFSP" = "num:i(0)"!][!//
[!FOR "AlmId" ="num:i(1)" TO "(num:i($TotalAlarmConfig))"!][!//
[!SELECT "SmuCoreAlarmBehavior/*[SmuCoreAlmBehaviourId = num:i($AlmId - 1)]"!][!//
[!CALL "Smu_AlmCfg_Value","MacInputVal" = "SmuCoreAlarmFSP"!][!//
[!VAR "ExtAlramBeh" = "$OutMac_AlmCfg"!][!//
[!IF "$ExtAlramBeh = num:i(1)"!][!//
[!VAR "AGFSP" = "bit:or($AGFSP,(bit:shl(num:i(1),($AlmId - num:i(1)))))"!][!//
[!ENDIF!] [!//
[!ENDSELECT!][!//
[!ENDFOR!][!// 
[!VAR "GroupId" = "$GroupId + num:i(1)"!][!//
[!ENDNOCODE!][!//
  [!"num:inttohex($AGFSP)"!]U[!IF "$GroupId < num:i(12)"!],[!ELSE!][!VAR "GroupId" = "num:i(0)"!][!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDFOR!][!// 
[!ENDSELECT!][!//
  },
 [!/*-- [cover parentID={C66D900F-1017-45a8-B737-E12A1114C33C}]  [/cover] --*/!][!//  
  /*AlarmFspConfig for SmuStdby*/
 {
[!SELECT "SmuConfigSet/*[1]/SmuStdbyConfig"!][!// 
[!VAR "TotalStdbyAlarmGroupConfig" = "num:i(count(SmuStdbyAlarmGroup/*))"!][!//
[!FOR "StdAlmgrpId" ="num:i(1)" TO "(num:i($TotalStdbyAlarmGroupConfig))"!][!// 
[!SELECT "SmuStdbyAlarmGroup/*[SmuStdbyAlmGrpId = num:i($StdAlmgrpId - 1)]"!][!//       
[!VAR "TotalStdbyAlarmGroupConfig" = "num:i(count(SmuStdbyAlarmBehavior/*))"!][!// 
[!NOCODE!][!//  
[!VAR "AG2FSP" = "num:i(0)"!][!//
[!FOR "StdbyAlmId" ="num:i(1)" TO "(num:i($TotalStdbyAlarmGroupConfig))"!][!//
[!SELECT "SmuStdbyAlarmBehavior/*[SmuStdbyAlmBehaviourId = num:i($StdbyAlmId - 1)]"!][!//
[!CALL "Smu_StdbyAlmCfg_Value","MacInputVal" = "SmuStdbyAlarmFSP"!][!//
[!VAR "StdbyExtAlramBeh" = "$OutMac_StdbyAlmCfg"!][!//
[!IF "($StdbyExtAlramBeh = num:i(1))and(num:i($CMD_STDBY) = num:i(1))"!][!//
[!VAR "AG2FSP" = "bit:or($AG2FSP,(bit:shl(num:i(1),($StdbyAlmId - num:i(1)))))"!][!//
[!ENDIF!] [!//
[!ENDSELECT!][!//
[!ENDFOR!][!// 
[!VAR "StdbyGroupId" = "$StdbyGroupId + num:i(1)"!][!//
[!ENDNOCODE!][!//
   [!"num:inttohex($AG2FSP)"!]U[!IF "$StdbyGroupId < num:i(2)"!],[!ELSE!][!VAR "StdbyGroupId" = "num:i(0)"!][!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDFOR!][!// 
[!ENDSELECT!][!//
 }
};

[!ENDSELECT!][!//
[!AUTOSPACING!]
#define SMU_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED 
/* MISRA2012_RULE_4_10_JUSTIFICATION: Smu_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of notification functions
 * before include memap.h - Accepted deviation in AUTOSAR */
#include "Smu_MemMap.h"
