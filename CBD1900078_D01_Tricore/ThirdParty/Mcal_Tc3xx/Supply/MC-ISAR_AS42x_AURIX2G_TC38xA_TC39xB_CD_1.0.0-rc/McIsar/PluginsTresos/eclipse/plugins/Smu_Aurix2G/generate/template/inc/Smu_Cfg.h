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
**  FILENAME  : Smu_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE      : 2017-08-27                                                    **
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
**  TRACEABILITY :  [cover parentID={FC35270B-C4B3-415c-8138-E8526306E2F5} ]  **
**                                                                            **
**  DESCRIPTION  : Code template header file for Smu Driver                   **
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
**  FILENAME  : Smu_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                                          **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                                            **
**                                                                            **
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
#ifndef SMU_CFG_H
#define SMU_CFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

[!NOCODE!]
[!INCLUDE "Smu.m"!][!//
[!ENDNOCODE!]
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
[!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
[!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
[!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
[!/*-- [cover parentID={BD286E93-F0ED-456c-A489-F389D744DD68}]  [/cover] --*/!][!//
#define SMU_AR_RELEASE_MAJOR_VERSION      ([!"$MajorVersion"!]U)
[!/*-- [cover parentID={9E03F945-EF95-40c6-A319-933E67F77BAD}]  [/cover] --*/!][!//
#define SMU_AR_RELEASE_MINOR_VERSION      ([!"$MinorVersion"!]U)
[!/*-- [cover parentID={2A91BB3F-5475-4621-AAED-5AB88B8A96A8}]  [/cover] --*/!][!//
#define SMU_AR_RELEASE_REVISION_VERSION   ([!"$RevisionVersion"!]U)
[!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
[!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
[!VAR "SwPatchVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
[!/*-- [cover parentID={2BEB2799-E273-4baa-AFC7-FFB9283EA291}]  [/cover] --*/!][!//
#define SMU_SW_MAJOR_VERSION  ([!"$SwMajorVersion"!]U)
[!/*-- [cover parentID={5431BCE8-BF47-4f6a-AC5F-A306E54B234F}]  [/cover] --*/!][!//
#define SMU_SW_MINOR_VERSION  ([!"$SwMinorVersion"!]U)
[!/*-- [cover parentID={4F4EDA96-DADD-479b-8D02-7108711FE980}]  [/cover] --*/!][!//
#define SMU_SW_PATCH_VERSION  ([!"$SwPatchVersion"!]U)

/*
  Configuration Options for DEM
  Options for the enabling/disabling of DEM in SMU Driver
*/
#define SMU_DISABLE_DEM_REPORT  (0U)
#define SMU_ENABLE_DEM_REPORT  (1U)

[!SELECT "as:modconf('Smu')[1]"!][!//
[!VAR "TotalConfig" = "num:i(count(SmuConfigSet/*))"!][!//
[!FOR "SmuId" ="num:i(1)" TO "(num:i($TotalConfig))"!][!//
[!SELECT "SmuConfigSet/*[num:i($SmuId)]"!][!//
#define [!"node:name(.)"!]         ((uint8)[!"@index"!])
[!ENDSELECT!][!//
[!ENDFOR!][!//



/* Timeout value for AG status readback */ 
[!/*-- [cover parentID={57FA5075-8216-4ec6-961F-998BB6D4B455}]  [/cover] --*/!][!//
#define SMU_AGSTATUS_TIMEOUT    ((uint32)([!"num:i(SmuGeneral/SmuAGStatusTimeout)"!]U))

/* Configuration: SMU_VERSION_INFO_API
Version Information API configuration
- if STD_ON, Smu_GetVersionInfo API is available
- if STD_OFF, Smu_GetVersionInfo API is not available
*/
[!/*-- [cover parentID={8E1A360C-FA93-4a4d-AFC7-D7FE500F3AC0}]  [/cover] --*/!][!//
#define SMU_VERSION_INFO_API  [!//
[!CALL "Smu_ConfigPreCompileSwitch","NodeVal" = "SmuGeneral/SmuVersionInfoApi"!][!//
[!/*-- [cover parentID={A78BF8E5-BA40-4e03-BF1E-CCC85D07819D}] [/cover] --*/!]
#define SMU_INIT_CHECK_API  [!//
[!CALL "Smu_ConfigPreCompileSwitch","NodeVal" = "SmuGeneral/SmuInitCheckApi"!][!//
 
/*
Configuration: SMU_DEV_ERROR_DETECT
Preprocessor switch for enabling the development error detection and 
reporting. 
- if STD_ON, DET is Enabled 
- if STD_OFF,DET is Disabled 
*/
[!/*-- [cover parentID={8D4B222C-9BE0-4b59-88F1-105E88F863AC}]  [/cover] --*/!][!//
[!/*-- [cover parentID={0E474C12-99A5-4896-87D6-128770E88FE0}]  [/cover] --*/!]
#define SMU_DEV_ERROR_DETECT  [!//
[!CALL "Smu_ConfigPreCompileSwitch","NodeVal" = "SmuGeneral/SmuDevErrorDetect"!][!//

/*Safety enable switch*/
#define SMU_SAFETY_ENABLE  [!//
[!CALL "Smu_ConfigPreCompileSwitch","NodeVal" = "SmuGeneral/SmuSafetyEnable"!][!//

/*Smu_stdby enable switch*/
[!/*-- [cover parentID={6370E1C2-9FF2-4b97-BAE1-B7CE8D0C5F04}]  [/cover] --*/!][!//
#define SMU_STANDBY_SWITCH  [!//
[!CALL "Smu_ConfigPreCompileSwitch","NodeVal" = "SmuGeneral/SmuStdbyEnable"!][!//

/*User and Supervisor mode moacros*/
#define SMU_MCAL_SUPERVISOR  0U

#define SMU_MCAL_USER1       1U

/*Smu_core FSP[0] HW Port Direction*/
[!/*-- [cover parentID={1A5E77FF-10F4-48c9-AAB4-7BE9A6FD9DE0}]  [/cover] --*/!][!// 
#define SMU_CORE_FSP0_HWDIR  [!//
[!CALL "Smu_FSPConfigSwitch","NodeVal" = "SmuGeneral/SmuCoreFSP0OutputEnable"!][!//

/*Smu_core FSP[1] HW Port Direction*/
[!/*-- [cover parentID={638A1736-B752-435c-B3EC-89B210EDE8FF}]  [/cover] --*/!][!// 
#define SMU_CORE_FSP1_HWDIR  [!//
[!CALL "Smu_FSPConfigSwitch","NodeVal" = "SmuGeneral/SmuCoreFSP1OutputEnable"!][!//

/*Smu_core FSP[0] HW Port Enable*/
[!/*-- [cover parentID={EC9A104D-48F3-41cb-93F6-3EF447FF0359}]  [/cover] --*/!][!// 
#define SMU_CORE_FSP0_PORT_ENABLE  [!//
[!CALL "Smu_FSPConfigSwitch","NodeVal" = "SmuGeneral/SmuCoreFSP0PortEnable"!][!//

/*Smu_core FSP[1] HW Port Direction*/
[!/*-- [cover parentID={FA729925-74A9-4768-802F-E9D0985E7F0A}]  [/cover] --*/!][!//
#define SMU_CORE_FSP1_PORT_ENABLE  [!//
[!CALL "Smu_FSPConfigSwitch","NodeVal" = "SmuGeneral/SmuCoreFSP1PortEnable"!][!//

/*Smu_core glitch filter through SCU enabled*/
[!/*-- [cover parentID={EA507610-961C-4524-9F2E-85F591DE3991}]  [/cover] --*/!][!//
#define SMU_GLITCHFILTER_SCU  [!//
[!CALL "Smu_FSPConfigSwitch","NodeVal" = "SmuGeneral/SmuCoreGlitchFilterSCU"!][!//

/*Smu_core glitch filter through SMU_STS enabled*/
[!/*-- [cover parentID={8B7889C3-01B3-4b9d-91AA-5FF7A63A323F}]  [/cover] --*/!][!//
#define SMU_GLITCHFILTER_SMU_STS  [!//
[!CALL "Smu_FSPConfigSwitch","NodeVal" = "SmuGeneral/SmuCoreGlitchFilterSTS"!][!//

/*Runtime API mode*/
[!/*-- [cover parentID={B1DB9768-3E31-4d4e-A237-AFEA35ED1115}]  [/cover] --*/!][!//
#define SMU_RUNTIME_API_MODE   ([!"SmuGeneral/SmuRuntimeApiMode"!])

/*Init Deinit API mode*/
[!/*-- [cover parentID={A11AB7CB-6AB2-49d7-AF4B-A643038B444E}]  [/cover] --*/!][!//
#define SMU_INIT_DEINIT_API_MODE    ([!"SmuGeneral/SmuInitDeInitApiMode"!])

/*Total number of alarm groups for Smu_core*/
#define SMU_CORE_TOTAL_ALARM_GROUPS     ((uint32)([!"(ecu:get('Smu.SmuCoreTotalAlarmGroups'))"!]U))

/*Total number of alarm groups for Smu_stdby*/
#define SMU_STDBY_TOTAL_ALARM_GROUPS     ((uint32)([!"(ecu:get('Smu.SmuStdbyTotalAlarmGroups'))"!]U))

/*Total number of alarm configuration registers for Smu_core*/
#define SMU_CORE_TOTAL_ALARM_CONFIG_REG  ((uint32)([!"(ecu:get('Smu.SmuCoreTotalCfgRegs'))"!]U))

/*Start group number for Smu_stdby*/
#define SMU_STDBY_START_ALARM_GROUP      ((uint32)([!"(ecu:get('Smu.SmuStdbyStartAlarmGroup'))"!]U))

/*End group number for Smu_stdby*/
#define SMU_STDBY_END_ALARM_GROUP        ((uint32)([!"(ecu:get('Smu.SmuStdbyEndAlarmGroup'))"!]U))

/*Smu_stdby FSP[0] as output*/
[!/*-- [cover parentID={00DBBE9A-0D84-4e27-B591-97745915EEF0}]  [/cover] --*/!][!//
#define SMU_STDBY_FSP0_OUTPUT  [!//
[!CALL "Smu_FSPConfigSwitch","NodeVal" = "SmuConfigSet/*[1]/SmuStdbyConfig/SmuStdbyAlarmGlobalConfig/SmuStdbyEnableFSP0"!][!// 

/*Smu_stdby FSP[1] as output*/
[!/*-- [cover parentID={FC3B7F13-7B76-4574-AA71-8C9BDB1880E4}]  [/cover] --*/!][!//
#define SMU_STDBY_FSP1_OUTPUT  [!//
[!CALL "Smu_FSPConfigSwitch","NodeVal" = "SmuConfigSet/*[1]/SmuStdbyConfig/SmuStdbyAlarmGlobalConfig/SmuStdbyEnableFSP1"!][!//

/*Macros to deine the valid alarm positions wrt the alarm groups*/
[!/*-- [cover parentID={969B8DD6-932A-479d-9841-248121C9C341}]  [/cover] --*/!][!//
#define SMU_MAX_ALARM_POS             ([!"(ecu:get('Smu.SmuMaxAlarmPos'))"!]U)
[!/*-- [cover parentID={F9EB78DD-9A97-4aa4-81EA-7944787FAEB1}]  [/cover] --*/!][!//
#define SMU_GROUP0_POS                ([!"num:inttohex((ecu:get('Smu.SmuAlarmGroup0')))"!]U)
#define SMU_GROUP1_POS                ([!"num:inttohex((ecu:get('Smu.SmuAlarmGroup1')))"!]U)
#define SMU_GROUP2_POS                ([!"num:inttohex((ecu:get('Smu.SmuAlarmGroup2')))"!]U)
#define SMU_GROUP3_POS                ([!"num:inttohex((ecu:get('Smu.SmuAlarmGroup3')))"!]U)
#define SMU_GROUP4_POS                ([!"num:inttohex((ecu:get('Smu.SmuAlarmGroup4')))"!]U)
#define SMU_GROUP5_POS                ([!"num:inttohex((ecu:get('Smu.SmuAlarmGroup5')))"!]U)
#define SMU_GROUP6_POS                ([!"num:inttohex((ecu:get('Smu.SmuAlarmGroup6')))"!]U)
#define SMU_GROUP7_POS                ([!"num:inttohex((ecu:get('Smu.SmuAlarmGroup7')))"!]U)
#define SMU_GROUP8_POS                ([!"num:inttohex((ecu:get('Smu.SmuAlarmGroup8')))"!]U)
#define SMU_GROUP9_POS                ([!"num:inttohex((ecu:get('Smu.SmuAlarmGroup9')))"!]U)
#define SMU_GROUP10_POS                ([!"num:inttohex((ecu:get('Smu.SmuAlarmGroup10')))"!]U)
#define SMU_GROUP11_POS                ([!"num:inttohex((ecu:get('Smu.SmuAlarmGroup11')))"!]U)
#define SMU_GROUP20_POS                ([!"num:inttohex((ecu:get('Smu.SmuAlarmGroup20')))"!]U)
#define SMU_GROUP21_POS                ([!"num:inttohex((ecu:get('Smu.SmuAlarmGroup21')))"!]U)


/* Configuration: SMU_ACTIVATE_RUN_STATE_FAILURE_DEM_NOTIF and SMU_E_ACTIVATE_RUN_STATE_FAILURE 
   Determines whether DEM for Activate RUN state failure is enabled or disabled.
*/
[!/*-- [cover parentID={7C7D9FB0-324E-47a1-BAB8-5364282586DA}]  [/cover] --*/!][!// 
[!/*-- [cover parentID={5A624FBD-729E-4e51-9631-F53FEDBA6338}]  [/cover] --*/!][!// 
[!/*-- [cover parentID={416568DB-7AB8-41d5-8FDB-54011F3C862A}]  [/cover] --*/!][!// 
[!IF "(node:exists(SmuDemEventParameterRefsConf/*[1]))"!][!//
[!SELECT "SmuDemEventParameterRefsConf/*[1]"!][!//
[!IF "(node:exists(./SmuActivateRunStateFailureNotification/*[1]))"!][!//
#define SMU_ACTIVATE_RUN_STATE_FAILURE_DEM_NOTIF   (SMU_ENABLE_DEM_REPORT)
#define SMU_E_ACTIVATE_RUN_STATE_FAILURE           (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./SmuActivateRunStateFailureNotification/*[1])))"!])
[!ELSE!][!//
#define SMU_ACTIVATE_RUN_STATE_FAILURE_DEM_NOTIF   (SMU_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ELSE!][!//
#define SMU_ACTIVATE_RUN_STATE_FAILURE_DEM_NOTIF   (SMU_DISABLE_DEM_REPORT)
[!ENDIF!][!//



/* Configuration: SMU_CLEAR_ALARM_STATUS_DEM_NOTIF   and SMU_E_CLEAR_ALARM_STATUS_FAILURE
   Determines whether DEM for clearing alarm status failure is enabled or disabled.
*/
[!/*-- [cover parentID={A3726E04-BEEB-4a80-BFB8-F23F3F129018}]  [/cover] --*/!][!// 
[!/*-- [cover parentID={340F588A-491E-48c0-8636-CB11E441A4FF}]  [/cover] --*/!][!// 
[!/*-- [cover parentID={76A8743D-47CE-41e0-B2F2-A8AC3A3D1B38}]  [/cover] --*/!][!//
[!IF "(node:exists(SmuDemEventParameterRefsConf/*[1]))"!][!//
[!SELECT "SmuDemEventParameterRefsConf/*[1]"!][!//
[!IF "(node:exists(./SmuClearAlarmStatusFailureNotification/*[1]))"!][!//
#define SMU_CLEAR_ALARM_STATUS_DEM_NOTIF     (SMU_ENABLE_DEM_REPORT)
#define SMU_E_CLEAR_ALARM_STATUS_FAILURE     (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./SmuClearAlarmStatusFailureNotification/*[1])))"!])
[!ELSE!][!//
#define SMU_CLEAR_ALARM_STATUS_DEM_NOTIF     (SMU_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ELSE!][!//
#define SMU_CLEAR_ALARM_STATUS_DEM_NOTIF     (SMU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* Configuration: SMU_RELEASE_FSP_DEM_NOTIF and SMU_E_RELEASE_FSP_FAILURE
   Determines whether DEM for releasing FSP failure is enabled or disabled.
*/
[!/*-- [cover parentID={C3594A1B-4114-487b-9B02-A2252C8EAC0E}]  [/cover] --*/!][!// 
[!/*-- [cover parentID={570CE945-7B1D-47d8-ADF2-A6541E0AB156}]  [/cover] --*/!][!// 
[!/*-- [cover parentID={FDEAC965-1246-4a26-90B0-D5EE90E84F35}]  [/cover] --*/!][!//  
[!IF "(node:exists(SmuDemEventParameterRefsConf/*[1]))"!][!//
[!SELECT "SmuDemEventParameterRefsConf/*[1]"!][!//
[!IF "(node:exists(./SmuReleaseFSPFailureNotification/*[1]))"!][!//
#define SMU_RELEASE_FSP_DEM_NOTIF     (SMU_ENABLE_DEM_REPORT)
#define SMU_E_RELEASE_FSP_FAILURE      (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./SmuReleaseFSPFailureNotification/*[1])))"!])
[!ELSE!][!//
#define SMU_RELEASE_FSP_DEM_NOTIF      (SMU_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ELSE!][!//
#define SMU_RELEASE_FSP_DEM_NOTIF      (SMU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* Configuration: SMU_CORE_ALIVE_FAILURE_DEM_NOTIF and SMU_E_CORE_ALIVE_FAILURE
   Determines whether DEM for Smu_core_alive test failure is enabled or disabled.
*/
[!/*-- [cover parentID={D45F495C-2A08-4c3f-B559-E94FE75FC253}]  [/cover] --*/!][!// 
[!/*-- [cover parentID={EF9026EE-4868-45b1-8DB1-15A993C2C51A}]  [/cover] --*/!][!// 
[!/*-- [cover parentID={A3964A90-C599-49d5-B4BC-48724018DF07}]  [/cover] --*/!][!//
[!IF "(node:exists(SmuDemEventParameterRefsConf/*[1]))"!][!//
[!SELECT "SmuDemEventParameterRefsConf/*[1]"!][!//
[!IF "(node:exists(./SmuCoreAliveFailureNotification/*[1]))"!][!//
#define SMU_CORE_ALIVE_FAILURE_DEM_NOTIF      (SMU_ENABLE_DEM_REPORT)
#define SMU_E_CORE_ALIVE_FAILURE              (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./SmuCoreAliveFailureNotification/*[1])))"!])
[!ELSE!][!//
#define SMU_CORE_ALIVE_FAILURE_DEM_NOTIF       (SMU_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ELSE!][!//
#define SMU_CORE_ALIVE_FAILURE_DEM_NOTIF       (SMU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* Configuration: SMU_RT_STOP_FAILURE_DEM_NOTIF  and SMU_E_RT_STOP_FAILURE
   Determines whether DEM for RT stop failure is enabled or disabled.
*/
[!/*-- [cover parentID={DE92C383-9B13-438d-9F49-705840A70A13}] [/cover] --*/!][!// 
[!/*-- [cover parentID={AF0FE326-F653-42d2-BC95-3C1ADFE9F789}] [/cover] --*/!][!// 
[!/*-- [cover parentID={4CCE1A5C-F28D-4b93-9F0F-AAFAC418CD6C}] [/cover] --*/!][!// 
[!IF "(node:exists(SmuDemEventParameterRefsConf/*[1]))"!][!//
[!SELECT "SmuDemEventParameterRefsConf/*[1]"!][!//
[!IF "(node:exists(./SmuRTStopFailureNotification/*[1]))"!][!//
#define SMU_RT_STOP_FAILURE_DEM_NOTIF       (SMU_ENABLE_DEM_REPORT)
#define SMU_E_RT_STOP_FAILURE             (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./SmuRTStopFailureNotification/*[1])))"!])
[!ELSE!][!//
#define SMU_RT_STOP_FAILURE_DEM_NOTIF        (SMU_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ELSE!][!//
#define SMU_RT_STOP_FAILURE_DEM_NOTIF        (SMU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* Configuration: SMU_ACTIVATE_PES_FAILURE_DEM_NOTIF   and SMU_E_ACTIVATE_PES_FAILURE
   Determines whether DEM for Activate PES failure is enabled or disabled.
*/
[!/*-- [cover parentID={FA87874F-481A-46e0-9A7A-D5DE58F723D2}] [/cover] --*/!][!// 
[!/*-- [cover parentID={0F059DC8-3DD5-4883-91C4-FB18E9FD1F28}] [/cover] --*/!][!//
[!/*-- [cover parentID={72F5F7F0-4ED6-43b7-8231-8B6421A329FA}] [/cover] --*/!][!//
[!IF "(node:exists(SmuDemEventParameterRefsConf/*[1]))"!][!//
[!SELECT "SmuDemEventParameterRefsConf/*[1]"!][!//
[!IF "(node:exists(./SmuActivatePESFailureNotification/*[1]))"!][!//
#define SMU_ACTIVATE_PES_FAILURE_DEM_NOTIF        (SMU_ENABLE_DEM_REPORT)
#define SMU_E_ACTIVATE_PES_FAILURE             (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./SmuActivatePESFailureNotification/*[1])))"!])
[!ELSE!][!//
#define SMU_ACTIVATE_PES_FAILURE_DEM_NOTIF         (SMU_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ELSE!][!//
#define SMU_ACTIVATE_PES_FAILURE_DEM_NOTIF         (SMU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* Configuration: SMU_ACTIVATE_FSP_FAILURE_DEM_NOTIF  and SMU_E_ACTIVATE_FSP_FAILURE 
   Determines whether DEM for Activate FSP failure is enabled or disabled.
*/
[!/*-- [cover parentID={F091A99D-C4ED-4ff3-B63E-FAF5F913B8B1}]  [/cover] --*/!][!// 
[!/*-- [cover parentID={BFC90927-5A79-476d-A4E3-8843BB309195}]  [/cover] --*/!][!// 
[!/*-- [cover parentID={379E5B4F-0E87-477c-B4F7-B5A455F55918}]  [/cover] --*/!][!//
[!IF "(node:exists(SmuDemEventParameterRefsConf/*[1]))"!][!//
[!SELECT "SmuDemEventParameterRefsConf/*[1]"!][!//
[!IF "(node:exists(./SmuActivateFSPFailureNotification/*[1]))"!][!//
#define SMU_ACTIVATE_FSP_FAILURE_DEM_NOTIF  (SMU_ENABLE_DEM_REPORT)
#define SMU_E_ACTIVATE_FSP_FAILURE          (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./SmuActivateFSPFailureNotification/*[1])))"!])
[!ELSE!][!//
#define SMU_ACTIVATE_FSP_FAILURE_DEM_NOTIF  (SMU_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ELSE!][!//
#define SMU_ACTIVATE_FSP_FAILURE_DEM_NOTIF  (SMU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* Configuration: SMU_SET_ALARM_STATUS_DEM_NOTIF and SMU_E_SET_ALARM_STATUS_FAILURE
   Determines whether DEM for set alarm status failure is enabled or disabled.
*/
[!/*-- [cover parentID={F0F5F7E7-1A92-422e-AE9E-E4C760893E9E}]  [/cover] --*/!][!// 
[!/*-- [cover parentID={1CC16216-C67C-443c-810B-80090A4CDDAC}]  [/cover] --*/!][!// 
[!/*-- [cover parentID={3B029C48-F55D-49dd-B96E-2062AA6D7513}]  [/cover] --*/!][!//
[!IF "(node:exists(SmuDemEventParameterRefsConf/*[1]))"!][!//
[!SELECT "SmuDemEventParameterRefsConf/*[1]"!][!//
[!IF "(node:exists(./SmuSetAlarmStatusFailureNotification/*[1]))"!][!//
#define SMU_SET_ALARM_STATUS_DEM_NOTIF         (SMU_ENABLE_DEM_REPORT)
#define SMU_E_SET_ALARM_STATUS_FAILURE             (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./SmuSetAlarmStatusFailureNotification/*[1])))"!])
[!ELSE!][!//
#define SMU_SET_ALARM_STATUS_DEM_NOTIF          (SMU_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ELSE!][!//
#define SMU_SET_ALARM_STATUS_DEM_NOTIF         (SMU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* Configuration: SMU_SFF_TEST_FAILURE_DEM_NOTIF   and SMU_E_SFF_TEST_FAILURE
   Determines whether DEM for SFF test failure is enabled or disabled.
*/
[!/*-- [cover parentID={A2BA5D27-D210-4780-A67D-72D01CF8138F}]  [/cover] --*/!][!// 
[!/*-- [cover parentID={DE2CC1AD-CF3A-4216-8781-C47AEBA9A887}]  [/cover] --*/!][!// 
[!/*-- [cover parentID={28B85B9B-52DA-40c2-9E65-460A21A25D95}]  [/cover] --*/!][!//
[!IF "(node:exists(SmuDemEventParameterRefsConf/*[1]))"!][!//
[!SELECT "SmuDemEventParameterRefsConf/*[1]"!][!//
[!IF "(node:exists(./SmuSffFailureNotification/*[1]))"!][!//
#define SMU_SFF_TEST_FAILURE_DEM_NOTIF           (SMU_ENABLE_DEM_REPORT)
#define SMU_E_SFF_TEST_FAILURE                   (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./SmuSffFailureNotification/*[1])))"!])
[!ELSE!][!//
#define SMU_SFF_TEST_FAILURE_DEM_NOTIF           (SMU_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ELSE!][!//
#define SMU_SFF_TEST_FAILURE_DEM_NOTIF          (SMU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

[!ENDSELECT!][!//

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/

#endif  /* SMU_CFG_H */
[!AUTOSPACING!]
