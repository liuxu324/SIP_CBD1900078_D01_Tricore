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
**  FILENAME  : Mcu_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 7.0.0                                                         **
**                                                                            **
**  DATE      : 2018-08-28                                                    **
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
**  TRACEABILITY : [cover parentID={92B82DA9-A966-4be2-A5C1-2130696BCB7D}]    **
**                                                                            **
**  DESCRIPTION  : Code template header file for Mcu Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Mcu Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!][!//
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
**  FILENAME  : Mcu_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 7.0.0                                                         **
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
**  DESCRIPTION  : Mcu configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Mcu Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
[!/*[cover parentID={92B82DA9-A966-4be2-A5C1-2130696BCB7D}]*/!][!//
#ifndef MCU_CFG_H
#define MCU_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
[!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
[!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
[!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
[!VAR "NewString" = "text:replaceAll($moduleReleaseVer,"\.",'')"!]
/* Autosar version of the module */
[!/*[cover parentID={478547C9-C0A7-46ab-AFDA-781FA253EDCD}][/cover]*/!][!//
#define MCU_AS_VERSION ([!"$NewString"!])

/* AUTOSAR specification version numbers */
[!/*[cover parentID={52E05C2E-2854-4f29-B3A5-DB36BA472837}][/cover]*/!][!//
[!/*[cover parentID={63C74B1D-48EF-4e77-AD52-067AAA4B8B9C}][/cover]*/!][!//
[!/*[cover parentID={0079783A-976C-4940-B2EE-5DEF3658A0F0}][/cover]*/!][!//
[!/*[cover parentID={D4D58E41-7DEC-4482-9797-D577E463D2BB}][/cover]*/!][!//
[!/*[cover parentID={FF0462EF-EEE0-44a1-A192-372E1BE9E391}][/cover]*/!][!//
[!IF "$MajorVersion = num:i(4)"!][!//
#define MCU_AR_RELEASE_MAJOR_VERSION      ([!"$MajorVersion"!]U)
#define MCU_AR_RELEASE_MINOR_VERSION      ([!"$MinorVersion"!]U)
#define MCU_AR_RELEASE_REVISION_VERSION   ([!"$RevisionVersion"!]U)
[!ENDIF!][!//

[!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
[!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
[!VAR "SwRevisionVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
/* Vendor specific implementation version information */
#define MCU_SW_MAJOR_VERSION   ([!"$SwMajorVersion"!]U)
#define MCU_SW_MINOR_VERSION   ([!"$SwMinorVersion"!]U)
#define MCU_SW_PATCH_VERSION   ([!"$SwRevisionVersion"!]U)

/* MCU_MCAL_SUPERVISOR  */
/* Mcu Operation in Supervisory Mode  */
#define MCU_MCAL_SUPERVISOR             (0U)

/* MCU_MCAL_USER1  */
/* Mcu Operation in User 1 Mode  */
#define MCU_MCAL_USER1                  (1U)

[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Mcu')[1]"!][!//
[!//

/*
  Configuration: MCU_DEV_ERROR_DETECT
  Preprocessor switch for enabling the development error detection and
  reporting.
  ON  : DET is Enabled
  OFF : DET is Disabled
*/
[!/* [cover parentID={CF478994-5338-4c02-B94C-B1C5B2FC7999}] [/cover]*/!][!//
[!IF "McuGeneralConfiguration/McuDevErrorDetect = 'true'"!][!//
#define  MCU_DEV_ERROR_DETECT (STD_ON)
[!ELSE!][!//
#define  MCU_DEV_ERROR_DETECT (STD_OFF)
[!ENDIF!][!//

/*
  Configuration: MCU_MULTICORE_ERROR_DETECT
  Preprocessor switch for enabling the multicore error detection and
  reporting.
  ON  : Multicore error detection and reporting is Enabled
  OFF : Multicore error detection and reporting is Disabled
*/
[!/* [cover parentID={1372F678-85D5-4861-ACC1-A9C5069533DC}] [/cover]*/!][!//
[!IF "McuGeneralConfiguration/McuMultiCoreErrorDetect = 'true'"!][!//
#define  MCU_MULTICORE_ERROR_DETECT (STD_ON)
[!ELSE!][!//
#define  MCU_MULTICORE_ERROR_DETECT (STD_OFF)
[!ENDIF!][!//

/*
  Configuration: MCU_VERSION_INFO_API
  Preprocessor switch to enable / disable the API to read out the modules
  version information.
  ON  : version info API is enabled
  OFF : version info API is disabled
*/
[!IF "McuGeneralConfiguration/McuVersionInfoApi = 'true'"!][!//
[!/*[cover parentID= {0567762F-3A8D-44de-98D9-F79E8F485355}]*/!][!//
#define MCU_VERSION_INFO_API (STD_ON)
[!ELSE!][!//
#define MCU_VERSION_INFO_API (STD_OFF)
[!ENDIF!][!//
[!/*[/cover]*/!][!//
/*
  Configuration : MCU_DISTRIBUTE_PLL_CLOCK_API
  Preprocessor switch to enable / disable the use of the
  API Mcu_DistributePllClock()
  ENABLED  : Mcu_DistributePllClock API is available
  DISABLED : Mcu_DistributePllClock API is not available
*/
[!/*[cover parentID={3A74C11E-5BE1-4633-A902-84C35B01228D}] [/cover]*/!][!//
[!IF "McuGeneralConfiguration/McuNoPll = 'false'"!][!//
#define  MCU_DISTRIBUTE_PLL_CLOCK_API (STD_ON)
[!ELSE!][!//
#define  MCU_DISTRIBUTE_PLL_CLOCK_API (STD_OFF)
[!ENDIF!][!//

/*
  Configuration : MCU_INIT_CLOCK_API
  Preprocessor switch to enable / disable the use of the
  API Mcu_InitClock()
  ENABLED  : Mcu_InitClock API is available
  DISABLED : Mcu_InitClock API is not available
*/
[!/*[cover parentID= {7A725F43-C518-463d-8E82-E99869AAF876}][/cover]*/!][!//
[!IF "McuGeneralConfiguration/McuInitClock = 'true'"!][!//
#define  MCU_INIT_CLOCK_API (STD_ON)
[!ELSE!][!//
#define  MCU_INIT_CLOCK_API (STD_OFF)
[!ENDIF!][!//

/*
  Configuration : MCU_PERFORM_RESET_API
  Preprocessor switch to enable / disable the use of the
  API Mcu_PerformReset()
  ENABLED  : Mcu_PerformReset API is available
  DISABLED : Mcu_PerformReset API is not available
*/
[!/*[cover parentID= {7A832DBF-A8A0-459f-A31B-032FC09BE4D6}]*/!][!//
[!IF "McuGeneralConfiguration/McuPerformResetApi = 'true'"!][!//
#define  MCU_PERFORM_RESET_API (STD_ON)
[!ELSE!][!//
#define  MCU_PERFORM_RESET_API (STD_OFF)
[!ENDIF!][!//
[!/*[/cover]*/!][!//
/*
  Configuration : MCU_GET_RAM_STATE_API (McuGetRamStateApi)
  Pre-processor switch to enable/disable the API Mcu_GetRamState.
  (If the H/W does not support the functionality, this parameter
  can be used to disable the API).
*/
[!IF "McuGeneralConfiguration/McuGetRamStateApi = 'true'"!][!//
[!/*[cover parentID= {0C740769-2EE6-4743-87C5-7B4367284426}]*/!][!//
#define MCU_GET_RAM_STATE_API (STD_ON)
[!ELSE!][!//
#define MCU_GET_RAM_STATE_API (STD_OFF)
[!ENDIF!][!//
[!/*[/cover]*/!][!//
/*
  Configuration : MCU_CLR_COLD_RESET_STAT_API (McuClearColdResetStatusApi)
  Pre-processor switch to enable/disable the API Mcu_ClearColdResetStatus.
*/
[!/*[cover parentID={5754D674-67AD-422c-8724-C4D3124BF3F6}] [/cover]*/!][!//
[!IF "McuGeneralConfiguration/McuClearColdResetStatusApi = 'true'"!][!//
#define MCU_CLR_COLD_RESET_STAT_API (STD_ON)
[!ELSE!][!//
#define MCU_CLR_COLD_RESET_STAT_API (STD_OFF)
[!ENDIF!][!//

/*
  Configuration : MCU_TRAP_API (McuIfxTrapApi)
  Pre-processor switch to Enables/Disables availability of trap related APIs
  defined by IFX namely Mcu_GetTrapCause, Mcu_SetTrapRequest and
  Mcu_ClearTrapRequest.
*/
[!IF "McuGeneralConfiguration/McuIfxTrapApi = 'true'"!][!//
[!/*[cover parentID= {C04157DA-7234-4e26-96FC-B488480EDF75}]*/!][!//
#define MCU_TRAP_API (STD_ON)
[!ELSE!][!//
#define MCU_TRAP_API (STD_OFF)
[!ENDIF!][!//
[!/*[/cover]*/!][!//
/*
  Configuration : MCU_CPU_CCUCON_UPDATE_API (McuIfxCpuCcuconApi)
  This parameter Enables/Disables availability of Cpu Ccucon register
  update API defined by IFX namely Mcu_UpdateCpuCcuconReg
*/
[!/*[cover parentID={C0CB5BFF-E992-48f3-BDAF-F8679AC3699D} ] [/cover]*/!][!//
[!IF "McuGeneralConfiguration/McuIfxCpuCcuconApi = 'true'"!][!//
#define MCU_CPU_CCUCON_UPDATE_API (STD_ON)
[!ELSE!][!//
#define MCU_CPU_CCUCON_UPDATE_API (STD_OFF)
[!ENDIF!][!//

/*
  Configuration : MCU_LOW_POWER_MODE_API (McuIfxLpmApi)
  Pre-processor switch to Enables/Disables availability of low power mode APIs
  defined by IFX namely Mcu_GetCpuIdleModeInitiator, Mcu_GetCpuState,
  Mcu_GetWakeupCause and Mcu_ClearWakeupCause.
*/
[!/*[cover parentID={33EE6E43-986F-4820-AFFD-B6BFC9AD068A}][/cover]*/!][!//
[!IF "McuGeneralConfiguration/McuIfxLpmApi = 'true'"!][!//
#define MCU_LOW_POWER_MODE_API (STD_ON)
[!ELSE!][!//
#define MCU_LOW_POWER_MODE_API (STD_OFF)
[!ENDIF!][!//

[!/*[cover parentID={8A887FB0-81C0-4949-91AB-07D90DF5E396}]*/!][!//
/*
  Configuration : MCU_DEINIT_API (McuIfxDeInitApi)
  Pre-processor switch to Enables/Disables availability of
  Mcu Deinitialization API - Mcu_DeInit.
*/
[!/*[/cover]*/!][!//
[!IF "McuGeneralConfiguration/McuIfxDeInitApi = 'true'"!][!//
#define MCU_DEINIT_API (STD_ON)
[!ELSE!][!//
#define MCU_DEINIT_API (STD_OFF)
[!ENDIF!][!//

/*
  Configuration : MCU_CLK_SRC_FAILURE_NOTIF_API
                                   (McuClockSourceFailureNotification)
  Pre-processor switch for availibility of Clock failure related DEMs
  notification function. ENABLED Clock failure related DEMs are reported
  DISABLED Clock failure related DEMs are not reported.
*/
[!/*[cover parentID= {32933C1E-5084-4199-A8A4-31C241ABFEB8}] [/cover]*/!][!//

[!IF "McuGeneralConfiguration/McuClockSourceFailureNotification = 'true'"!][!//
#define MCU_CLK_SRC_FAILURE_NOTIF_API (STD_ON)
[!ELSE!][!//
#define MCU_CLK_SRC_FAILURE_NOTIF_API (STD_OFF)
[!ENDIF!][!//

/*
    Configuration : MCU_SAFETY_ENABLE
    Pre-processor switch to enable/disable the MCU driver safety features.
*/
[!/*[cover parentID= {97510B77-476C-4499-AB17-C87EC87C263B}] [/cover]*/!][!//
[!IF "McuGeneralConfiguration/McuSafetyEnable = 'true'"!][!//
#define MCU_SAFETY_ENABLE (STD_ON)
[!ELSE!][!//
#define MCU_SAFETY_ENABLE (STD_OFF)
[!ENDIF!][!//
[!/*[/cover]*/!][!//

[!/*[cover parentID= {6CA8839F-9353-4b73-8865-06A296FE7298}] */!][!//
[!IF "McuGeneralConfiguration/McuInitCheckApi = 'true'"!][!//
#define MCU_INITCHECK_API (STD_ON)
[!ELSE!][!//
#define MCU_INITCHECK_API (STD_OFF)
[!ENDIF!][!//
[!/*[/cover]*/!][!//

[!/*[cover parentID= {EF597D8B-BBC1-4ae0-814A-1ECC0FC7F65E}] */!][!//
[!IF "McuGeneralConfiguration/McuInitDeInitApiMode = 'MCU_MCAL_SUPERVISOR'"!][!//
#define MCU_INIT_DEINIT_API_MODE (MCU_MCAL_SUPERVISOR)
[!ELSE!][!//
#define MCU_INIT_DEINIT_API_MODE (MCU_MCAL_USER1)
[!ENDIF!][!//
[!/*[/cover]*/!][!//

[!/*[cover parentID= {F0DF105B-34E6-4b06-811E-E8ADD52D3E60}] */!][!//
[!IF "McuGeneralConfiguration/McuRuntimeApiMode = 'MCU_MCAL_SUPERVISOR'"!][!//
#define MCU_RUNTIME_API_MODE (MCU_MCAL_SUPERVISOR)
[!ELSE!][!//
#define MCU_RUNTIME_API_MODE (MCU_MCAL_USER1)
[!ENDIF!][!//
[!/*[/cover]*/!][!//
/*
    Configuration: MCU_GTM_USED
    This parameter defines if GTM module is used by modules.
*/
[!IF "ecu:get('Gtm.Available')='true'"!][!//
  #define MCU_GTM_USED (STD_ON)

  /*
  Configuration: MCU_GTM_NO_OF_TOM_AVAILABLE
  This parameter defines no of TOM units available [0...6]
*/
#define MCU_GTM_NO_OF_TOM_AVAILABLE  ([!"num:i(ecu:get('Gtm.NumberOfTomModules'))"!]U)

/*
    Configuration: MCU_GTM_NO_OF_ATOM_AVAILABLE
    This parameter defines no of Atom units available [0...12]
*/
#define MCU_GTM_NO_OF_ATOM_AVAILABLE  ([!"num:i(ecu:get('Gtm.NumberOfAtomModules'))"!]U)

/*
    Configuration: MCU_GTM_NO_OF_TIM_AVAILABLE
    This parameter defines no of Tim units available [0...12]
*/
#define MCU_GTM_NO_OF_TIM_AVAILABLE  ([!"num:i(ecu:get('Gtm.NumberOfTimModules'))"!]U)

/*
    Configuration: MCU_GTM_NO_OF_TBU_CH_AVAILABLE
    This parameter defines no of TOM units available [0...3]
*/
#define MCU_GTM_NO_OF_TBU_CH_AVAILABLE  ([!"num:i(ecu:get('Gtm.NumberOfTbuChannels'))"!]U)

/*
    Configuration: MCU_GTM_NO_OF_CCM_AVAILABLE
    This parameter defines no of CCM clusters available [0...12]
*/
#define MCU_GTM_NO_OF_CCM_AVAILABLE  ([!"num:i(ecu:get('Gtm.NumberOfClusters'))"!]U)

[!VAR "ClusterCount" = "num:i(ecu:get('Gtm.NumberOfClusters'))"!][!//
[!VAR "GtmClsClkCfgRstVal" = "num:i(0)"!][!//
[!VAR "GtmClusterRstVal" = "num:i(2)"!][!//
[!FOR "ClusterIndex" = "num:i(0)" TO "(num:i($ClusterCount)- num:i(1))"!][!//
[!VAR "GtmClsClkCfgRstVal" = "bit:or(bit:shl($GtmClsClkCfgRstVal,$GtmClusterRstVal),$GtmClusterRstVal)"!][!//
[!ENDFOR!][!//
#define MCU_GTM_CLS_CLK_CFG_RESET_VAL        ([!"num:inttohex($GtmClsClkCfgRstVal,num:i(8))"!]U)
[!ELSE!][!//
[!/*[cover parentID= {C5D1E04D-C99D-42d9-9BC2-35F20D3A98B1}][/cover]*/!][!//
#define MCU_GTM_USED (STD_OFF)
[!ENDIF!][!//

/*
    Configuration: MCU_MAIN_OSC_FREQ  (MHz)
    This parameter defines main oscillator frequency in MHz
*/
[!/*[cover parentID= {8DC1636C-16F2-4314-B749-9B4FFBCA8715}][/cover]*/!][!//
#define MCU_MAIN_OSC_FREQ  ([!"McuGeneralConfiguration/McuMainOscillatorFrequency"!]U)

/*
    Configuration: MCU_BACKUP_FREQ  (MHz)
    This parameter defines back up frequency in MHz
*/
#define MCU_BACKUP_FREQ    ([!"num:i(ecu:get('Mcu.BackUpFrequency') div num:i(1000000))"!]U)

/* This parameter defines whether CCU6 kernel 0 is used or not*/
[!SELECT "./McuHardwareResourceAllocationConf/*[1]/McuCcu6ModuleAllocationConf"!][!//
[!IF "(./*[@name = concat('McuCcu6ModuleAllocationConf','_',num:i(0))]/McuCcu6ModuleAllocationConf = 'CCU6_MODULE_NOT_USED')"!][!//
#define MCU_CCU60_USED     (STD_OFF)
[!ELSE!]
#define MCU_CCU60_USED     (STD_ON)
[!ENDIF!][!//

/* This parameter defines whether CCU6 kernel 1 is used or not*/
[!IF "(./*[@name = concat('McuCcu6ModuleAllocationConf','_',num:i(1))]/McuCcu6ModuleAllocationConf = 'CCU6_MODULE_NOT_USED')"!][!//
#define MCU_CCU61_USED     (STD_OFF)
[!ELSE!]
#define MCU_CCU61_USED     (STD_ON)
[!ENDIF!][!//
[!ENDSELECT!][!//


/* This parameter defines whether GPT12 is used or not*/
[!SELECT "./McuHardwareResourceAllocationConf/*[1]/McuGpt12ModuleAllocationConf"!][!//
[!VAR "GptUsed" = "num:i(0)"!][!//
[!IF "(./*[@name = concat('McuGpt12ModuleAllocationConf','_',num:i(0))]/McuGpt12ModuleAllocationConf != 'GPT_BLOCK_NOT_USED')"!][!//
[!VAR "GptUsed" = "num:i(1)"!][!//
[!ELSEIF "(./*[@name = concat('McuGpt12ModuleAllocationConf','_',num:i(1))]/McuGpt12ModuleAllocationConf != 'GPT_BLOCK_NOT_USED')"!][!//
[!VAR "GptUsed" = "num:i(1)"!][!//
[!ENDIF!][!//
[!IF "$GptUsed = num:i(0)"!][!//
#define MCU_GPT_USED     (STD_OFF)
[!ELSEIF "$GptUsed = num:i(1)"!][!//
#define MCU_GPT_USED     (STD_ON)
[!ENDIF!][!//
[!ENDSELECT!][!//



/* OSC Frequency Value
    This bit field defines the divider value that generates
    the reference clock that is supervised by the
    oscillator watchdog.
    fOSCREF = OSCCON.OSCVAL - 1 + 16 MHz.
    Equation is OSCVAL = (fOSCREF - 15). */
[!/*[cover parentID= {03884108-8132-470c-A65D-9BF76EEFBBC2}]*/!][!//
[!NOCODE!][!//
[!VAR "McuOscValReg" = "num:inttohex(num:i(0))"!][!//
[!IF "(McuGeneralConfiguration/McuOscillatorMode = 'EXT_CRYSTAL_CERAMIC_RES_MODE_SEL0')"!][!//
[!VAR "McuOscValReg" = "num:i(McuGeneralConfiguration/McuMainOscillatorFrequency) - num:i(15)"!][!//
[!VAR "McuOscValReg" = "num:inttohex(num:i($McuOscValReg))"!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define MCU_OSCVAL_REG_VALUE  ([!"$McuOscValReg"!]U)
[!/*[/cover]*/!][!//
/*
    MACRO : MCU_OSC_MODE
    configured Oscillator mode
    EXT_CRYSTAL_CERAMIC_RES_MODE – 0
    EXT_INPUT_CLOCK_MODE         - 2
    OSC_DISABLED_MODE            – 3
*/
[!/*[cover parentID= {A565F475-3EA7-4fa3-BFD4-C65CB9C9859E}][/cover]*/!][!//
#define MCU_OSC_MODE    ([!"num:i(text:split(./McuGeneralConfiguration/McuOscillatorMode,'SEL')[2])"!]U)

[!NOCODE!][!//
[!VAR "ModulePath" = "'McuModuleConfiguration'"!][!//
[!VAR "ModuleIndex" = "num:i(0)"!][!//
[!VAR "McuStdbyRamEn" = "num:i(0)"!][!//
[!VAR "Count" = "num:i(count(node:ref($ModulePath)/*))"!][!//
[!VAR "McuSystemModeEnable" = "num:i(0)"!][!//
[!VAR "McuIdleModeEnable" = "num:i(0)"!][!//
[!FOR "ModuleIndex" = "num:i(0)" TO "(num:i($Count)- num:i(1))"!][!//
  [!VAR "MaxModeEvrcCtrl" = "num:i(0)"!]
  [!VAR "ModeSettingConfig" = "num:i(count(node:ref($ModulePath)/McuModeSettingConf/*))"!]
  [!FOR "ModeIndex" = "num:i(0)" TO "($ModeSettingConfig - num:i(1))"!][!//
    [!VAR "McuModeConfig" = "num:i(node:ref($ModulePath)/McuModeSettingConf/*[$ModeIndex+1]/McuMode)"!][!//
  [!IF "$McuModeConfig = num:i(0)"!][!//
      [!VAR "McuIdleModeEnable" = "num:i(1)"!][!//
    [!ENDIF!][!//
    [!IF "$McuModeConfig = num:i(1)"!][!//
      [!VAR "McuSystemModeEnable" = "num:i(1)"!][!//
    [!ENDIF!][!//
    [!IF "$McuModeConfig = num:i(2)"!][!//
      [!VAR "McuSystemModeEnable" = "num:i(1)"!][!//
    [!VAR "McuStdbyRamEn" = "num:i(text:split(node:ref($ModulePath)/McuModeSettingConf/*[$ModeIndex+1]/McuStdbyModeSettingConf/McuStdbyModeRamEnable,'SEL')[2])"!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
[!ENDFOR!][!//
[!ENDNOCODE!][!//

[!/* System and Idle mode Core Calculation */!][!//
[!NOCODE!][!//
  [!VAR "McuSysModeCore" = "num:i(0)"!]
  [!VAR "TempVal" = "./McuGeneralConfiguration/McuSystemModeCpuCore"!][!//
  [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
  [!VAR "McuSysModeCore" = "num:i($TempVal+num:i(1))"!][!//
  [!VAR "McuIdleModeCore" = "num:i(0)"!][!//
  [!VAR "TempVal" = "./McuGeneralConfiguration/McuIdleModeCpuCore"!][!//
  [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
  [!VAR "McuIdleModeCore" = "num:i($TempVal)"!][!//
[!ENDNOCODE!][!//

/* Master Core for triggering System Modes for controller
 1 - Core 0
 2 - Core 1
 3 - Core 2
 4 - Core 3
 5 - Core 4
 6 - Core 5
 7 - All Cores Unanimously
*/
#define MCU_SYSTEM_CORE_NOT_DEFINED     (0U)
[!IF "($McuSystemModeEnable > num:i(0))"!][!//
[!/*[cover parentID= {08AA96D1-C854-4cad-B958-A789E6CFB198}][/cover]*/!][!//
#define MCU_SYSTEM_MODE_CORE            ([!"num:i($McuSysModeCore)"!]U)
[!/*McuStandbyEntryMode*/!][!//
[!/*[cover parentID= {E03F632C-ABD0-4bba-A868-4C5C438740BF}][/cover]*/!][!//
#define MCU_STANDBY_MODE_ENTRY          ([!"num:i(text:split(./McuGeneralConfiguration/McuStandbyEntryMode,'SEL')[2])"!]U)
[!ELSE!]
#define MCU_SYSTEM_MODE_CORE            (MCU_SYSTEM_CORE_NOT_DEFINED)
[!ENDIF!][!//
/* Master Core for triggering Idle Mode for controller
 1 - Core 0
 2 - Core 1
 3 - Core 2
 4 - Core 3
 5 - Core 4
 6 - Core 5
 0 - All Cores Individually
*/
[!/*[cover parentID= {94BA7757-989B-4c80-81AD-4D842CE9C577}][/cover]*/!][!//
[!/*[cover parentID= {420B0752-A22F-4993-9462-EB4ADBDD36D4}][/cover]*/!][!//
#define MCU_IDLE_CORE_NOT_DEFINED         (7U)
[!IF "$McuIdleModeEnable > num:i(0)"!][!//
#define MCU_IDLE_MODE_CORE                ([!"num:i($McuIdleModeCore)"!]U)
[!ELSE!]
#define MCU_IDLE_MODE_CORE                (MCU_IDLE_CORE_NOT_DEFINED)
[!ENDIF!][!//


/* Standby Mode Ram enable configuration */
[!/* [cover parentID= {4AE1BF08-D704-4652-A7BF-90DD63B4797E}]*/!][!//
[!IF "($McuStdbyRamEn > num:i(0))"!][!//
  [!IF "($McuStdbyRamEn = num:i(1))"!][!// dLMU0 lower block is selected
#define MCU_NO_OF_STDBY_RAM_BLK       (1U)
  [!ENDIF!][!//
  [!IF "($McuStdbyRamEn = num:i(2))"!][!// dLMU0 is selected
#define MCU_NO_OF_STDBY_RAM_BLK       (2U)
  [!ENDIF!][!//
  [!IF "($McuStdbyRamEn = num:i(4))"!][!// dLMU1 are selected
#define MCU_NO_OF_STDBY_RAM_BLK       (2U)
  [!ENDIF!][!//
  [!IF "($McuStdbyRamEn = num:i(7))"!][!// Both dLMU0 and dLMU1 are selected
#define MCU_NO_OF_STDBY_RAM_BLK       (4U)
  [!ENDIF!][!//
[!ELSE!]
#define MCU_NO_OF_STDBY_RAM_BLK           (0U)
[!ENDIF!][!//
[!/*[/cover]*/!][!//
/*
  Macro to write into Trap disable register
*/
[!VAR "CoreCount" = "num:i(ecu:get('Mcu.NoOfCoreAvailable'))"!][!//
[!IF "($CoreCount = num:i(1))"!][!//
#define MCU_TRAPDIS0_RESET_VAL     (0xF0F0F0FFU)
[!ELSEIF "($CoreCount = num:i(2))"!][!//
#define MCU_TRAPDIS0_RESET_VAL     (0xF0F0FFFFU)
[!ELSEIF "($CoreCount = num:i(3))"!][!//
#define MCU_TRAPDIS0_RESET_VAL     (0xF0FFFFFFU)
[!ELSEIF "($CoreCount = num:i(4))"!][!//
#define MCU_TRAPDIS0_RESET_VAL     (0xFFFFFFFFU)
[!ELSE!][!//
#define MCU_TRAPDIS0_RESET_VAL     (0xFFFFFFFFU)
#define MCU_TRAPDIS1_RESET_VAL     (0x0000FFFFU)
[!ENDIF!][!//

/*
    Container: McuModeSettingConf
    Multiplicity: 1 - *
    Configuration Options:
    For MCU power down modes Mcu_ModeType :
    IDLE Mode: CPU clock is disabled and peripheral clock is running
    as configured
*/
#define MCU_IDLE             (0U)

/*
    Configuration Options:
    For MCU power down modes Mcu_ModeType :
    SLEEP Mode: CPU clock is disabled and Peripherals go to sleep if
    configured for sleep mode
*/
#define MCU_SLEEP            (1U)

/*
    Configuration Options:
    For MCU power down modes Mcu_ModeType :
*/
#define MCU_STANDBY          (2U)

/*
    Maximum number of modes which are configurable is 3
*/
#define MCU_MAX_NO_MODES     (3U)

/*
  Configuration: Mode Id
  This id corresponds to the container name of the McuModeSettingConfiguration
  Use this as the parameter for API: Mcu_SetMode
*/
[!VAR "ModeSettingConfig" = "num:i(count(node:ref($ModulePath)/McuModeSettingConf/*))"!]
[!FOR "ModeIndex" = "num:i(0)" TO "($ModeSettingConfig - num:i(1))"!][!//
  [!VAR "SymbolicName" = "concat('McuConf_McuModeSettingConf_',node:name(node:ref($ModulePath)/McuModeSettingConf/*[$ModeIndex+1]))"!]
[!/*[cover parentID= {E4ED0085-EB4B-4580-A78E-8A6BDF7666E3}]*/!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef [!"$SymbolicName"!]
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define [!"$SymbolicName"!]  ([!"num:i(node:ref($ModulePath)/McuModeSettingConf/*[$ModeIndex+1]/McuMode)"!]U)
#endif
[!ENDFOR!][!//
[!/*[/cover]*/!][!//

/*
  Container: McuClockSettingConfig
  Multiplicity: 1 -*
*/
[!/*[cover parentID= {8DFB209E-AA9F-4c4e-B68C-791ED7856555}]*/!][!//
[!VAR "ClockSettingConfig" = "num:i(count(node:ref($ModulePath)/McuClockSettingConfig/*))"!][!//
[!FOR "ClockIndex" = "num:i(0)" TO "($ClockSettingConfig - num:i(1))"!][!//
  [!VAR "SymbolicName" = "concat('McuConf_McuClockSettingConfig_',node:name(node:ref($ModulePath)/McuClockSettingConfig/*[McuClockSettingId = num:i($ClockIndex)]))"!]
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef [!"$SymbolicName"!]
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define [!"$SymbolicName"!]  ([!"num:i(node:ref($ModulePath)/McuClockSettingConfig/*[McuClockSettingId = num:i($ClockIndex)]/McuClockSettingId)"!]U)
#endif
[!ENDFOR!][!//
[!/*[/cover]*/!][!//
/*
  Container: McuRamSectorSettingConf
  Multiplicity: 0 -*
*/

[!VAR "RamSectorSettingConfig" = "num:i(count(node:ref($ModulePath)/McuRamSectorSettingConf/*))"!][!//
[!/*[cover parentID= {B7661B96-79C4-45f4-8F3B-637646F7DAA3}]*/!][!//
[!IF "$RamSectorSettingConfig > num:i(0)"!][!//
  [!FOR "RAMSectionIndex" = "num:i(0)" TO "($RamSectorSettingConfig - num:i(1))"!][!//
  [!VAR "SymbolicName" = "concat('McuConf_McuRamSectorSettingConf_',node:name(node:ref($ModulePath)/McuRamSectorSettingConf/*[McuRamSectorSettingId = num:i($RAMSectionIndex)]))"!]

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef [!"$SymbolicName"!]
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define [!"$SymbolicName"!]  ([!"num:i(node:ref($ModulePath)/McuRamSectorSettingConf/*[McuRamSectorSettingId = num:i($RAMSectionIndex)]/McuRamSectorSettingId)"!]U)
#endif
  [!ENDFOR!][!//
[!ENDIF!][!//
[!/*[/cover]*/!][!//
/*
  Container: McuResetReasonConf
  Multiplicity: 1-1
*/
[!/*[cover parentID= {C727B85A-0C06-4be6-A7B3-5E0A7AEA5D18}]*/!][!//
[!VAR "LoopCounter" = "'McuPublishedInformation/McuResetReasonConf'"!][!//
[!LOOP "node:ref($LoopCounter)/*"!][!//
  [!NOCODE!][!//
    [!VAR "SymbolicName" = "concat('McuConf_McuResetReasonConf_',node:name(.))"!]
  [!ENDNOCODE!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef [!"$SymbolicName"!]
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define [!"$SymbolicName"!]  ([!"num:i(./McuResetReason)"!]U)
#endif
[!ENDLOOP!][!//
[!/*[/cover]*/!][!//
/* Dem reporting enable/disabled macro */
#define MCU_ENABLE_DEM_REPORT  (1U)
#define MCU_DISABLE_DEM_REPORT (0U)

/* DEM enable/disable for Oscillator Failure */
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1]/MCU_E_OSC_FAILURE/*[1])"!][!//
[!/*[cover parentID= {4E04A93B-FCFC-4b02-8569-1E506F1D83E2}][/cover]*/!][!//
#define MCU_E_OSC_FAILURE_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
[!/*[cover parentID={0D31720A-AEC5-4439-80B0-8DFFA733F18E}][/cover]*/!][!//
#define MCU_E_OSC_FAILURE               \
           (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_OSC_FAILURE/*[1])))"!])[!//
  [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
[!/*[cover parentID={450D47EE-C613-467c-812B-C030C3DDC2F2}][/cover]*/!][!//
#define MCU_E_OSC_FAILURE_DEM_REPORT     (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* DEM enable/disable for system PLL Timeout */
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1]/MCU_E_SYSTEM_PLL_TIMEOUT_ERR/*[1])"!][!//
  [!IF "node:refexists(McuDemEventParameterRefsConf/*[1]/MCU_E_SYSTEM_PLL_TIMEOUT_ERR/*[1]) and (node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_SYSTEM_PLL_TIMEOUT_ERR/*[1]) != ' ' )"!][!//
[!/*[cover parentID= {1D2A5A0F-8C11-4ffa-8BBC-078C773082EF}][/cover]*/!][!//
#define MCU_E_SYSTEM_PLL_TIMEOUT_ERR_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
[!/*[cover parentID= {D9327BAC-0644-44a4-8678-C4AA11010126}][/cover]*/!][!//
#define MCU_E_SYSTEM_PLL_TIMEOUT_ERR                \
           (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_SYSTEM_PLL_TIMEOUT_ERR/*[1])))"!])[!//
    [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
[!/*[cover parentID= {EE8DA45D-147C-4ec9-A845-0335DC6A14A1}][/cover]*/!][!//
#define MCU_E_SYSTEM_PLL_TIMEOUT_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//


/* DEM enable/disable for Peripheral PLL Timeout */
[!/*[cover parentID={4166BC28-387E-4748-AF1A-63D722C1BA2C}] [/cover]*/!][!//
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1]/MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR/*[1])"!][!//
  [!IF "node:refexists(McuDemEventParameterRefsConf/*[1]/MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR/*[1]) and (node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR/*[1]) != ' ' )"!][!//

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
[!/*[cover parentID= {8B624B40-6685-4403-9175-EDF34838BFE9}][/cover]*/!][!//
#define MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR                \
           (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR/*[1])))"!])[!//
    [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* DEM enable/disable for system PLL lock loss */
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1]/MCU_E_SYSTEM_PLL_LOCK_LOSS/*[1])"!][!//
[!/*[cover parentID={8DB3DDCF-216F-4cc5-8FA1-F0C85C6A38E1}][/cover]*/!][!//
#define MCU_E_SYSTEM_PLL_LOCK_LOSS_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
[!/*[cover parentID={C777FE59-0045-4282-9D8A-721F9B834EDB}][/cover]*/!][!//
#define MCU_E_SYSTEM_PLL_LOCK_LOSS                \
           (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_SYSTEM_PLL_LOCK_LOSS/*[1])))"!])[!//
  [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
[!/*[cover parentID={4E04A93B-FCFC-4b02-8569-1E506F1D83E2}][/cover]*/!][!//
#define MCU_E_SYSTEM_PLL_LOCK_LOSS_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* DEM enable/disable for peripheral PLL lock loss */
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1]/MCU_E_PERIPHERAL_PLL_LOCK_LOSS/*[1])"!][!//
[!/*[cover parentID={69218AE2-F7A6-43f3-A834-E5637E6C7C71}][/cover]*/!][!//
#define MCU_E_PERIPHERAL_PLL_LOCK_LOSS_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
[!/*[cover parentID={02307940-EC02-42de-995C-BE563206D792}][/cover]*/!][!//
#define MCU_E_PERIPHERAL_PLL_LOCK_LOSS                \
           (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_PERIPHERAL_PLL_LOCK_LOSS/*[1])))"!])[!//
  [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
#define MCU_E_PERIPHERAL_PLL_LOCK_LOSS_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* DEM enable/disable for GTM module enable failure */
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1])"!][!//
  [!IF "node:refexists(McuDemEventParameterRefsConf/*[1]/MCU_E_GTM_CLC_ENABLE_ERR/*[1]) and (node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_GTM_CLC_ENABLE_ERR/*[1]) != ' ' )"!][!//
[!/* [cover parentID={758F684A-4746-419c-9458-F6BE184F397C}][/cover]*/!][!//
#define MCU_E_GTM_CLC_ENABLE_ERR_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
#define MCU_E_GTM_CLC_ENABLE_ERR                \
           (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_GTM_CLC_ENABLE_ERR/*[1])))"!])[!//
    [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
[!/* [cover parentID= {4E04A93B-FCFC-4b02-8569-1E506F1D83E2}][/cover]*/!][!//
#define MCU_E_GTM_CLC_ENABLE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* DEM enable/disable for GTM module disable failure */
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1])"!][!//
  [!IF "node:refexists(McuDemEventParameterRefsConf/*[1]/MCU_E_GTM_CLC_DISABLE_ERR/*[1]) and (node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_GTM_CLC_DISABLE_ERR/*[1]) != ' ' )"!][!//
[!/* [cover parentID={4DC5407F-C44E-466c-A7A5-530B51244577}][/cover]*/!][!//
#define MCU_E_GTM_CLC_DISABLE_ERR_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
#define MCU_E_GTM_CLC_DISABLE_ERR                \
            (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_GTM_CLC_DISABLE_ERR/*[1])))"!])[!//
    [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
[!/* [cover parentID= {4E04A93B-FCFC-4b02-8569-1E506F1D83E2}][/cover]*/!][!//
#define MCU_E_GTM_CLC_DISABLE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* DEM enable/disable for CONVCTRL module enable failure */
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1])"!][!//
  [!IF "node:refexists(McuDemEventParameterRefsConf/*[1]/MCU_E_CONVCTRL_CLC_ENABLE_ERR/*[1]) and (node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_CONVCTRL_CLC_ENABLE_ERR/*[1]) != ' ' )"!][!//
[!/*[cover parentID={C3DE451C-E699-4b24-90E0-391EB02E2457}][/cover]*/!][!//
#define MCU_E_CONVCTRL_CLC_ENABLE_ERR_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
#define MCU_E_CONVCTRL_CLC_ENABLE_ERR                \
            (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_CONVCTRL_CLC_ENABLE_ERR/*[1])))"!])[!//
    [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
#define MCU_E_CONVCTRL_CLC_ENABLE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* DEM enable/disable for CONVCTRL module disable failure */
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1])"!][!//
  [!IF "node:refexists(McuDemEventParameterRefsConf/*[1]/MCU_E_CONVCTRL_CLC_DISABLE_ERR/*[1]) and (node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_CONVCTRL_CLC_DISABLE_ERR/*[1]) != ' ' )"!][!//
[!/*[cover parentID={BE0114BC-1647-4cfc-BF17-E7E0176FCF5F}][/cover]*/!][!//
#define MCU_E_CONVCTRL_CLC_DISABLE_ERR_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
[!/*[cover parentID={5179398F-3F99-418b-BF58-5F5DF68D643D}][/cover]*/!][!//
#define MCU_E_CONVCTRL_CLC_DISABLE_ERR                \
            (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_CONVCTRL_CLC_DISABLE_ERR/*[1])))"!])[!//
    [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
#define MCU_E_CONVCTRL_CLC_DISABLE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* DEM enable/disable for CCUCON0 update inability (LCK bit set) */
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1])"!][!//
  [!IF "node:refexists(McuDemEventParameterRefsConf/*[1]/MCU_E_CCUCON_UPDATE_ERR/*[1]) and (node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_CCUCON_UPDATE_ERR/*[1]) != ' ' )"!][!//
[!/*[cover parentID={91BDF9B4-8388-4d6f-836B-6C0BBBE0FD12}] [/cover]*/!][!//
#define MCU_E_CCUCON_UPDATE_ERR_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
[!/*[cover parentID={93B276EF-67CD-49e9-9170-166C01FC0C67}] [/cover]*/!][!//
#define MCU_E_CCUCON_UPDATE_ERR                \
            (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_CCUCON_UPDATE_ERR/*[1])))"!])[!//
    [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
#define MCU_E_CCUCON_UPDATE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* DEM enable/disable for CCU6 kernel enable */
[!/*[cover parentID={5271EEF5-C873-4b67-9535-FD1DA452E35E}] [/cover]*/!][!//
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1])"!][!//
  [!IF "node:refexists(McuDemEventParameterRefsConf/*[1]/MCU_E_CCU6_CLC_ENABLE_ERR/*[1]) and (node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_CCU6_CLC_ENABLE_ERR/*[1]) != ' ' )"!][!//

#define MCU_E_CCU6_CLC_ENABLE_ERR_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
#define MCU_E_CCU6_CLC_ENABLE_ERR                \
            (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_CCU6_CLC_ENABLE_ERR/*[1])))"!])[!//
    [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
[!/*[cover parentID= {4E04A93B-FCFC-4b02-8569-1E506F1D83E2}] [/cover]*/!][!//
#define MCU_E_CCU6_CLC_ENABLE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* DEM enable/disable for CCU6 kernel disable */
[!/*[cover parentID={2B7C0E50-0F19-4259-87E9-F0E86D386464}] [/cover]*/!][!//
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1])"!][!//
  [!IF "node:refexists(McuDemEventParameterRefsConf/*[1]/MCU_E_CCU6_CLC_DISABLE_ERR/*[1]) and (node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_CCU6_CLC_DISABLE_ERR/*[1]) != ' ' )"!][!//

#define MCU_E_CCU6_CLC_DISABLE_ERR_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
#define MCU_E_CCU6_CLC_DISABLE_ERR                \
            (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_CCU6_CLC_DISABLE_ERR/*[1])))"!])[!//
    [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
#define MCU_E_CCU6_CLC_DISABLE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* DEM enable/disable for GPT12 module enable */
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1])"!][!//
  [!IF "node:refexists(McuDemEventParameterRefsConf/*[1]/MCU_E_GPT12_CLC_ENABLE_ERR/*[1]) and (node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_GPT12_CLC_ENABLE_ERR/*[1]) != ' ' )"!][!//
[!/*[cover parentID={597E48C0-FC34-461f-B5A5-ACB49A2E3155}][/cover]*/!][!//
#define MCU_E_GPT12_CLC_ENABLE_ERR_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
#define MCU_E_GPT12_CLC_ENABLE_ERR                \
            (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_GPT12_CLC_ENABLE_ERR/*[1])))"!])[!//
    [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
#define MCU_E_GPT12_CLC_ENABLE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* DEM enable/disable for GPT12 module disable */
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1])"!][!//
  [!IF "node:refexists(McuDemEventParameterRefsConf/*[1]/MCU_E_GPT12_CLC_DISABLE_ERR/*[1]) and (node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_GPT12_CLC_DISABLE_ERR/*[1]) != ' ' )"!][!//
[!/*[cover parentID={A6E9068E-7136-45c3-9E0B-043D0C5A7CCD}][/cover]*/!][!//
#define MCU_E_GPT12_CLC_DISABLE_ERR_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
#define MCU_E_GPT12_CLC_DISABLE_ERR                \
            (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_GPT12_CLC_DISABLE_ERR/*[1])))"!])[!//
    [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
#define MCU_E_GPT12_CLC_DISABLE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//


/* DEM enable/disable for PMSWCRx update inability (BUSY bit) */
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1])"!][!//
  [!IF "node:refexists(McuDemEventParameterRefsConf/*[1]/MCU_E_PMSWCR_UPDATE_ERR/*[1]) and (node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_PMSWCR_UPDATE_ERR/*[1]) != ' ' )"!][!//

#define MCU_E_PMSWCR_UPDATE_ERR_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
#define MCU_E_PMSWCR_UPDATE_ERR                \
            (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_PMSWCR_UPDATE_ERR/*[1])))"!])[!//
    [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
#define MCU_E_PMSWCR_UPDATE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

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
[!ENDSELECT!][!//

#endif /* end of MCU_CFG_H */

