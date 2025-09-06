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
**  FILENAME  : Wdg_17_Scu_Cfg.h                                              **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE      : 2018-07-26                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Wdg.bmd                                           **
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
**  DESCRIPTION  : Code template header file for Wdg Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Wdg Driver, AUTOSAR Release 4.2.2     **
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
**  FILENAME  : Wdg_17_Scu_Cfg.h                                              **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                                      **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                                          **
**                                                                            **
**  BSW MODULE DECRIPTION : Wdg.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Wdg configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Wdg Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={B6D99DA4-A9E6-466a-BD12-8DE8ACD6BB76}][/cover] */

#ifndef WDG_17_SCU_CFG_H
#define WDG_17_SCU_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
[!NOCODE!]
[!INCLUDE "Wdg_17_Scu.m"!][!//
[!ENDNOCODE!]
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
[!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
[!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
[!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//

/* AUTOSAR specification version numbers */

#define WDG_17_SCU_AR_RELEASE_MAJOR_VERSION     ([!"$MajorVersion"!]U)
#define WDG_17_SCU_AR_RELEASE_MINOR_VERSION     ([!"$MinorVersion"!]U)
#define WDG_17_SCU_AR_RELEASE_REVISION_VERSION  ([!"$RevisionVersion"!]U)


[!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
[!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
[!VAR "SwPatchVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
/* Vendor specific implementation version information */
#define WDG_17_SCU_SW_MAJOR_VERSION   ([!"$SwMajorVersion"!]U)
#define WDG_17_SCU_SW_MINOR_VERSION   ([!"$SwMinorVersion"!]U)
#define WDG_17_SCU_SW_PATCH_VERSION   ([!"$SwPatchVersion"!]U)

/*
Configuration: WDG_DEV_ERROR_DETECT  :
- if ON, DET is Enabled
- if OFF,DET is Disabled
ECUC_Wdg_00115: Compile switch to enable/disable development error detection
for this module.
- STD_ON if WdgDevErrorDetect is true
- STD_OFF if WdgDevErrorDetect is true
*/
[!SELECT "as:modconf('Wdg')[1]"!][!//
/* [cover parentID={196ED3F2-E379-48e0-9906-5F634181ED62}][/cover] */
#define WDG_17_SCU_DEV_ERROR_DETECT                                 [!//
[!CALL "WDG_CG_ConfigSwitch", "nodeval" = "WdgGeneral/WdgDevErrorDetect"!][!//
[!CR!][!//

/*
Configuration: WDG_VERSION_INFO_API:
ECUC_Wdg_00119:Compile switch to enable/disable the version information API
- STD_ON if WdgVersionInfoApi is true
- STD_OFF if WdgVersionInfoApi is false
*/
/* [cover parentID={2FF354C6-15C2-422a-9AED-B51CF6DA5ED8}][/cover] */
#define WDG_17_SCU_VERSION_INFO_API                                 [!//
[!CALL "WDG_CG_ConfigSwitch", "nodeval" = "WdgGeneral/WdgVersionInfoApi"!][!//
[!CR!][!//

/*
Configuration: WDG_17_SCU_SAFETY_ENABLE:
ECUC_Wdg_00119:Compile switch to enable/disable the Safety Enable API
- ON if WdgSafetyEnable is true
- OFF if WdgSafetyEnable is false
*/
/* [cover parentID={4D369CBC-7442-47a3-B620-FBCEBCDAEEF6}][/cover] */
#define WDG_17_SCU_SAFETY_ENABLE                                    [!//
[!CALL "WDG_CG_ConfigSwitch", "nodeval" = "WdgGeneral/WdgSafetyEnable"!][!//
[!CR!][!//

/*
Configuration: WDG_17_SCU_INIT_CHECK_API:
ECUC_Wdg_00119:Compile switch to enable/disable the Init Check API
- STD_ON if WdgInitCheckApi is true
- STD_OFF if WdgInitCheckApi is false
*/
/* [cover parentID={FD823AD4-F66D-478b-886E-8783A07F1564}][/cover] */
#define WDG_17_SCU_INIT_CHECK_API                                   [!//
[!CALL "WDG_CG_ConfigSwitch", "nodeval" = "WdgGeneral/WdgInitCheckApi"!][!//
[!CR!][!//

/*
Configuration: WDG_17_SCU_INIT_API_MODE:
-User Mode Macro for Init API
*/
/* [cover parentID={8CF14F53-5342-4dec-9F35-96A4F4E3F2A5}][/cover] */
[!IF "WdgGeneral/WdgInitApiMode='WDG_MCAL_SUPERVISOR'"!][!//
#define WDG_17_SCU_INIT_API_MODE                           (WDG_17_SCU_MCAL_SUPERVISOR)
[!ELSE!][!//
#define WDG_17_SCU_INIT_API_MODE                           (WDG_17_SCU_MCAL_USER1)
[!ENDIF!][!//

/*
Configuration: WDG_17_SCU_RUNTIME_API_MODE:
-User Mode Macro for Runtime APIs
*/
/* [cover parentID={B5A8398D-97D4-42f8-99CF-919CFAAED467}][/cover] */
[!IF "WdgGeneral/WdgRuntimeApiMode = 'WDG_MCAL_SUPERVISOR'"!][!//
#define WDG_17_SCU_RUNTIME_API_MODE                        (WDG_17_SCU_MCAL_SUPERVISOR)
[!ELSE!][!//
#define WDG_17_SCU_RUNTIME_API_MODE                        (WDG_17_SCU_MCAL_USER1)
[!ENDIF!][!//

/*Wdg Core Configured*/
[!SELECT "as:modconf('Wdg')[1]"!]
[!VAR "No0fWdgModuleConfig" = "num:i(count(WdgSettingsConfig/*))"!]
/* [cover parentID={5CA58BDD-0BE1-4869-BE44-333AD4E77E2F}][/cover] */
[!FOR "CoreIndex" = "num:i(0)" TO "num:i(num:i(ecu:get('Mcu.NoOfCoreAvailable'))-num:i(1))"!]
[!VAR "CoreConfigured" = "num:i(0)"!]
[!FOR "Index" = "num:i(0)" TO "num:i($No0fWdgModuleConfig - num:i(1))"!]
[!IF "node:value(WdgSettingsConfig/*[@index = $Index]/WdgCoreId) = $CoreIndex"!]
[!AUTOSPACING!]
[!INDENT "0"!]
#define WDG_17_SCU_CONFIGURED_CORE[!"node:value(WdgSettingsConfig/*[@index = $Index]/WdgCoreId)"!]                                 (STD_ON)
[!ENDINDENT!]
[!VAR "CoreConfigured" = "num:i(1)"!]
[!ENDIF!]
[!ENDFOR!]
[!IF "$CoreConfigured != num:i(1)"!]
[!AUTOSPACING!]
[!INDENT "0"!]
#define WDG_17_SCU_CONFIGURED_CORE[!"$CoreIndex"!]                                 (STD_OFF)

[!ENDINDENT!]
[!ENDIF!]
[!ENDFOR!]
[!ENDSELECT!]

/* WDG_MAX_TIMERS: holds maximum number of WDG timers configured */
#define WDG_17_SCU_MAX_TIMERS ([!"num:i(ecu:get('Mcu.NoOfCoreAvailable'))"!]U) 

/* [cover parentID={30F21997-90E4-48a3-9CB7-90366F306B02}][/cover] */
/* WDG_TRIG_SELECT: Select the timer for service WDG during STC window period */
#define WDG_17_SCU_TRIG_SELECT (WDG_17_SCU_[!"WdgGeneral/WdgTriggerTimerSelection"!])

/* Dem related pre-compile switches */
/* Dem reporting enable/disabled macro */
#define WDG_17_SCU_ENABLE_DEM_REPORT  (1U)
#define WDG_17_SCU_DISABLE_DEM_REPORT (0U)
[!IF "(node:exists(WdgDemEventParameterRefs/*[1]) = 'true')"!][!//
[!SELECT "WdgDemEventParameterRefs/*[1]"!][!//
[!IF "((node:exists(./WDG_E_DISABLE_REJECTED/*[1])) = 'true')"!][!//
/* [cover parentID={E9F1346D-101C-46b6-9717-0E36F056C853}][/cover] */
#define WDG_17_SCU_E_DISABLE_REJECTED          (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./WDG_E_DISABLE_REJECTED/*[1])))"!]) 
#define WDG_17_SCU_DISABLE_REJECT_DEM_REPORT   (WDG_17_SCU_ENABLE_DEM_REPORT)
[!ELSE!][!//
/* [cover parentID={E72AA0BE-A201-46d0-8A2C-0C543C1CD70C}][/cover] */
#define WDG_17_SCU_DISABLE_REJECT_DEM_REPORT   (WDG_17_SCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!IF "((node:exists(./WDG_E_MODE_FAILED/*[1])) = 'true')"!][!//
/* [cover parentID={7C09BFD0-7967-4507-A7A6-38DC84E5F9F5}][/cover] */
/* [cover parentID={40596155-897D-4767-B0C9-7133662B58BC}][/cover] */
/* [cover parentID={72A9C41A-0522-4239-B575-0FBA4A00D4B2}][/cover] */
#define WDG_17_SCU_E_MODE_FAILED         (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./WDG_E_MODE_FAILED/*[1])))"!]) 
/* [cover parentID={52039A3A-3079-49d3-80F9-BD83A8C710C3}][/cover] */
#define WDG_17_SCU_MODE_FAIL_DEM_REPORT    (WDG_17_SCU_ENABLE_DEM_REPORT)
[!ELSE!][!//
/* [cover parentID={52039A3A-3079-49d3-80F9-BD83A8C710C3}][/cover] */
#define WDG_17_SCU_MODE_FAIL_DEM_REPORT  (WDG_17_SCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ELSE!][!//
/* [cover parentID={E72AA0BE-A201-46d0-8A2C-0C543C1CD70C}][/cover] */
#define WDG_17_SCU_DISABLE_REJECT_DEM_REPORT   (WDG_17_SCU_DISABLE_DEM_REPORT)
/* [cover parentID={52039A3A-3079-49d3-80F9-BD83A8C710C3}][/cover] */
#define WDG_17_SCU_MODE_FAIL_DEM_REPORT        (WDG_17_SCU_DISABLE_DEM_REPORT)
[!ENDIF!]
[!//
[!//
/* Instance ID for WDG module */
/* [cover parentID={8651DF64-7267-47f4-85C9-F3BB40C0ACC5}][/cover] */
#define WDG_17_SCU_INSTANCE_ID   ((uint8)[!"num:i(WdgGeneral/WdgIndex)"!]U)
#define Wdg_17_ScuConf_WdgGeneral_WdgIndex (WDG_17_SCU_INSTANCE_ID)


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
#endif  /* WDG_17_CFG_H */

