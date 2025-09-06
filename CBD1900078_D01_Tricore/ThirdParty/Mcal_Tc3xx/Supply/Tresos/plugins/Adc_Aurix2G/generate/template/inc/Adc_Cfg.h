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
**  FILENAME  : Adc_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 6.0.0                                                         **
**                                                                            **
**  DATE      : 2018-08-09                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Adc.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={E0525B6D-A2D0-4db9-AD6B-BEAE5C1D6FCE}]    **
**                                                                            **
**  DESCRIPTION  : Code template header file for Adc Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of ADC Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*************************************************************************/!][!//
[!//
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
**  FILENAME  : Adc_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 6.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                                          **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                                            **
**                                                                            **
**  BSW MODULE DECRIPTION : Adc.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Adc configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of ADC Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef ADC_CFG_H
#define ADC_CFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
[!NOCODE!]
[!INCLUDE "Adc.m"!][!//
[!ENDNOCODE!]
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
[!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
[!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
[!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
[!/* [cover parentID={C4A6CE28-7B86-4965-9161-A33B2D81226C}]ADC_DEINIT_API[/cover] */!][!//
#define ADC_AR_RELEASE_MAJOR_VERSION      ([!"$MajorVersion"!]U)
[!/* [cover parentID={4572085B-8D78-451d-B545-6E2E474B56FD}]ADC_DEINIT_API[/cover] */!][!//
#define ADC_AR_RELEASE_MINOR_VERSION      ([!"$MinorVersion"!]U)
[!/* [cover parentID={C3F4AABD-31AE-4901-A5A8-EB4CB9AF915A}]ADC_DEINIT_API[/cover] */!][!//
#define ADC_AR_RELEASE_REVISION_VERSION   ([!"$RevisionVersion"!]U)

[!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
[!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
[!VAR "SwPatchVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
[!/* [cover parentID={F4049591-276B-4b8c-868E-8738D74E640C}]ADC_DEINIT_API[/cover] */!][!//
#define ADC_SW_MAJOR_VERSION  ([!"$SwMajorVersion"!]U)
[!/* [cover parentID={DE013017-28B5-4e65-B843-7087241CD4FB}]ADC_DEINIT_API[/cover] */!][!//
#define ADC_SW_MINOR_VERSION  ([!"$SwMinorVersion"!]U)
[!/* [cover parentID={26B5D4C5-864A-46c9-B35D-D99AEE8442A0}]ADC_DEINIT_API[/cover] */!][!//
#define ADC_SW_PATCH_VERSION  ([!"$SwPatchVersion"!]U)


/*
  Configuration Options: ADC_PRIORITY_IMPLEMENTATION
  Options for the Priority Mechanism supported in ADC Driver
*/
#define ADC_PRIORITY_NONE  (0U)
#define ADC_PRIORITY_HW  (1U)
#define ADC_PRIORITY_HW_SW  (2U) 

/*
  Configuration Options: ADC_RESULT_HANDLING_IMPLEMENTATION
  Options for the Result Handling Mechanism supported in ADC Driver
*/
#define ADC_INTERRUPT_MODE_RESULT_HANDLING  (0U)
#define ADC_DMA_MODE_RESULT_HANDLING  (1U)
#define ADC_POLLING_MODE_RESULT_HANDLING  (2U) 

/*
  Configuration Options: ADC_SLEEP_MODE_CFG
  Options for the Sleep Mode supported in ADC Driver
*/
#define ADC_SLEEP_MODE_ACCEPT  (0U)
#define ADC_SLEEP_MODE_REJECT  (1U)

/*
  Configuration Options: ADC_RESULT_ALIGNMENT
  Options for the Result Alignment supported in ADC Driver
*/
#define ADC_ALIGN_RIGHT  (0U)
#define ADC_ALIGN_LEFT  (1U)


/*
  Configuration Options: ADC_SUPPLY_VOLTAGE
  Options for the Supply Voltages supported in ADC Driver
*/
#define ADC_VOLTAGE_CONTROLLED_BY_SUPPLY  (0U)
#define ADC_VOLTAGE_5V  (1U)
#define ADC_VOLTAGE_3P3V  (2U)

/*
  Configuration Options for DEM
  Options for the enabling/disabling of DEM in ADC Driver
*/
#define ADC_DISABLE_DEM_REPORT  (0U)
#define ADC_ENABLE_DEM_REPORT  (1U)

/*
  Configuration Options for the setting the privilege mode in ADC Driver
*/
#define ADC_MCAL_SUPERVISOR  (0U)
#define ADC_MCAL_USER1  (1U)


[!SELECT "as:modconf('Adc')[1]"!][!//
/* Configuration: ADC_DEINIT_API
Adc_DeInit API configuration
- if STD_ON, Adc_DeInit API is available
- if STD_OFF, Adc_DeInit API is not available
*/
[!/* [cover parentID={5D453C9E-4448-4758-B881-E270608E8FA6}]ADC_DEINIT_API[/cover] */!][!//
#define ADC_DEINIT_API  [!//
[!CALL "Adc_ConfigPreCompileSwitch","NodeVal" = "AdcGeneral/AdcDeInitApi"!][!//

/* Configuration: ADC_ENABLE_START_STOP_GROUP_API
Start/Stop Group conversion API configuration
- if STD_ON, Adc_StartGroupConversion() and Adc_StopGroupConversion() Group
conversion APIs are available
- if STD_OFF, Adc_StartGroupConversion() and Adc_StopGroupConversion() Group
conversion APIs are not available
*/
[!/* [cover parentID={992D8BBA-BA1F-4fb0-87E2-C716C75A4051}]ADC_ENABLE_START_STOP_GROUP_API[/cover] */!][!//
#define ADC_ENABLE_START_STOP_GROUP_API  [!//
[!CALL "Adc_ConfigPreCompileSwitch","NodeVal" = "AdcGeneral/AdcEnableStartStopGroupApi"!][!//

/* Configuration: ADC_HW_TRIGGER_API
Adc HW Trigger API configuration
- if STD_ON, Adc_EnableHardwareTrigger() and Adc_DisableHardwareTrigger() APIs
are available
- if STD_OFF, Adc_EnableHardwareTrigger() and Adc_DisableHardwareTrigger() APIs
are not available
*/
[!/* [cover parentID={DBF2683A-82BB-47c5-864E-6B7060DB6AB1}]ADC_HW_TRIGGER_API[/cover] */!][!//
#define ADC_HW_TRIGGER_API  [!//
[!CALL "Adc_ConfigPreCompileSwitch","NodeVal" = "AdcGeneral/AdcHwTriggerApi"!][!//

/* Configuration: ADC_READ_GROUP_API
Adc_ReadGroup API switch
- if STD_ON, Adc_ReadGroup() API is available
- if STD_OFF, Adc_ReadGroup() API is not available
*/
[!/* [cover parentID={493286E3-DFA0-451b-9136-DB581245286A}]ADC_READ_GROUP_API[/cover] */!][!//
#define ADC_READ_GROUP_API  [!//
[!CALL "Adc_ConfigPreCompileSwitch","NodeVal" = "AdcGeneral/AdcReadGroupApi"!][!//

/* Configuration: ADC_VERSION_INFO_API
Version Information API configuration
- if STD_ON, Adc_GetVersionInfo API is available
- if STD_OFF, Adc_GetVersionInfo API is not available
*/
[!/* [cover parentID={D392D925-806A-4ea9-9AE9-2D9BACF52549}]ADC_VERSION_INFO_API[/cover] */!][!//
#define ADC_VERSION_INFO_API  [!//
[!CALL "Adc_ConfigPreCompileSwitch","NodeVal" = "AdcGeneral/AdcVersionInfoApi"!][!//

/* Configuration: ADC_STARTUP_CALIB_API
Calibration API configuration
- if STD_ON, Adc_GetStartupCalStatus() and Adc_TriggerStartupCal() API are available
- if STD_OFF, Adc_GetStartupCalStatus() and Adc_TriggerStartupCal() API are not available
*/
[!/* [cover parentID={3D426C1B-4295-48cd-A984-AAD615103DB3}]ADC_STARTUP_CALIB_API[/cover] */!][!//
#define ADC_STARTUP_CALIB_API  [!//
[!CALL "Adc_ConfigPreCompileSwitch","NodeVal" = "AdcGeneral/AdcStartupCalibApi"!][!//

/* Configuration: ADC_TRIGGER_ONE_CONV_ENABLE
Dummy Converison before startup calibration (Refer Errata ADC_TC.083)
- if STD_ON, Execute of one dummy conversion for each configured HW unit, before start-up calibration is triggered in the API Adc_TriggerStartupCal()
- if STD_OFF, Dont Execute of one dummy conversion for each configured HW unit, before start-up calibration is triggered in the API Adc_TriggerStartupCal()
*/
[!/* [cover parentID={2227AE2B-20D0-44f1-995F-FAE53B42C184}]ADC_TRIGGER_ONE_CONV_ENABLE[/cover] */!][!//
#define ADC_TRIGGER_ONE_CONV_ENABLE  [!//
[!CALL "Adc_ConfigPreCompileSwitch","NodeVal" = "AdcGeneral/AdcTriggerOneConversionEnable"!][!//

/*
Configuration: ADC_DEV_ERROR_DETECT
Preprocessor switch for enabling the development error detection and 
reporting. 
- if STD_ON, DET is Enabled 
- if STD_OFF,DET is Disabled 
*/
[!/* [cover parentID={EFE3E83D-5CE8-4ead-B619-38519AE38930}]ADC_DEV_ERROR_DETECT[/cover] */!][!//
#define ADC_DEV_ERROR_DETECT  [!//
[!CALL "Adc_ConfigPreCompileSwitch","NodeVal" = "AdcGeneral/AdcDevErrorDetect"!][!//

/*
Configuration: ADC_ENABLE_LIMIT_CHECK
Preprocessor switch for enabling the limit checking feature of ADC. 
- if STD_ON, Limit checking feature of ADC is Enabled 
- if STD_OFF,Limit checking feature of ADC is Disabled 
*/
[!/* [cover parentID={57D186D9-A81F-4995-84A3-F1293FF1DE41}]ADC_ENABLE_LIMIT_CHECK[/cover] */!][!//
#define ADC_ENABLE_LIMIT_CHECK  [!//
[!CALL "Adc_ConfigPreCompileSwitch","NodeVal" = "AdcGeneral/AdcEnableLimitCheck"!][!//

/* Configuration: ADC_GRP_NOTIF_CAPABILITY
Adc Notification capability configuration 
- if STD_ON, Notification capability is Enabled 
- if STD_OFF, Notification capability is Disabled 
*/
[!/* [cover parentID={CDAB5981-3C11-46b9-A99F-FE30A0FE6196}]ADC_GRP_NOTIF_CAPABILITY[/cover] */!][!//
#define ADC_GRP_NOTIF_CAPABILITY  [!//
[!CALL "Adc_ConfigPreCompileSwitch","NodeVal" = "AdcGeneral/AdcGrpNotifCapability"!][!//

/* Configuration: ADC_ENABLE_QUEUING
Determines, if the queuing mechanism is active in case of priority mechanism 
disabled.
Note: This macro is only applicable in NO_PRIORITY MODE. Queueing is enabled 
only if AdcEnableStartStopGroupApi is set to true, since only SW triggered
groups can be Queued.
- if STD_ON, Queuing mechanism in no priority is Enabled.
- if STD_OFF, Queuing mechanism in no priority is Disabled.
*/
[!IF "AdcGeneral/AdcEnableStartStopGroupApi = 'true' and AdcGeneral/AdcPriorityImplementation = 'ADC_PRIORITY_NONE'"!][!//
[!/* [cover parentID={8C681898-7C67-4ea2-AA6E-6AF78C330D8A}]ADC_ENABLE_QUEUING[/cover] */!][!//
#define ADC_ENABLE_QUEUING  [!//
[!CALL "Adc_ConfigPreCompileSwitch","NodeVal" = "AdcGeneral/AdcEnableQueuing"!][!//
[!ELSE!][!//
[!/* [cover parentID={8C681898-7C67-4ea2-AA6E-6AF78C330D8A}]ADC_ENABLE_QUEUING[/cover] */!][!//
#define ADC_ENABLE_QUEUING  (STD_OFF)
[!ENDIF!][!//

/* Configuration: ADC_PRIORITY_IMPLEMENTATION
Determines the type of prioritization mechanism
*/
[!/* [cover parentID={DAC2F9F8-16C1-4f2c-9603-DC7970D952A2}]ADC_PRIORITY_IMPLEMENTATION[/cover] */!][!//
#define ADC_PRIORITY_IMPLEMENTATION  ([!"AdcGeneral/AdcPriorityImplementation"!])

/* Configuration: ADC_RESULT_HANDLING_IMPLEMENTATION
Determines the result handling mechanism
*/
[!/* [cover parentID={EBDADC2E-C1A2-46d7-8FD8-156CC61DB3D3}]ADC_RESULT_HANDLING_IMPLEMENTATION[/cover] */!][!//
#define ADC_RESULT_HANDLING_IMPLEMENTATION  ([!"AdcGeneral/AdcResultHandlingImplementation"!])

/* Configuration: ADC_SLEEP_MODE_CFG
Determines the status of Sleep mode
*/
[!/* [cover parentID={86201198-147C-4e01-9A1B-CE3889890D45}]ADC_SLEEP_MODE_CFG[/cover] */!][!//
#define ADC_SLEEP_MODE_CFG  ([!"AdcGeneral/AdcSleepMode"!])

/* Configuration: ADC_RESULT_ALIGNMENT
Determines the type of Result Alignment
*/
[!/* [cover parentID={83822865-03ED-4e43-9086-6728C290EB36}]ADC_RESULT_ALIGNMENT[/cover] */!][!//
#define ADC_RESULT_ALIGNMENT  ([!"AdcGeneral/AdcResultAlignment"!])

/* Configuration: ADC_SUPPLY_VOLTAGE
Determines the type of Supply Voltage
*/
[!/* [cover parentID={3B85C35F-B63C-45e4-8641-BE9B9015DD3F}]ADC_SUPPLY_VOLTAGE[/cover] */!][!//
#define ADC_SUPPLY_VOLTAGE  ([!"AdcGeneral/AdcSupplyVoltage"!])
/*
Configuration: ADC_SAFETY_ENABLE
Switch for enabling the Safety Checking feature of ADC. 
- if STD_ON, Safety checking feature of ADC is Enabled 
- if STD_OFF,Safety checking feature of ADC is Disabled 
*/
[!/* [cover parentID={423448F2-19D4-43eb-A0AB-DC2A9B2D25C2}]ADC_SAFETY_ENABLE[/cover] */!][!//
#define ADC_SAFETY_ENABLE  [!//
[!CALL "Adc_ConfigPreCompileSwitch","NodeVal" = "AdcGeneral/AdcSafetyEnable"!][!//

/*
Configuration: ADC_INIT_CHECK_API
Switch for enabling the Init Checking feature of ADC. 
- if STD_ON, Init checking feature of ADC is Enabled 
- if STD_OFF,Init checking feature of ADC is Disabled 
*/
[!/* [cover parentID={82F4EE1F-2483-472c-BCD8-A45E5DEFC311}]ADC_INIT_CHECK_API[/cover] */!][!//
#define ADC_INIT_CHECK_API  [!//
[!CALL "Adc_ConfigPreCompileSwitch","NodeVal" = "AdcGeneral/AdcInitCheckApi"!][!//

/*
Configuration: ADC_MULTICORE_ERROR_DETECT
Switch for enabling the Multicore error detection feature of ADC. 
- if STD_ON, Multicore Error Detection feature of ADC is Enabled 
- if STD_OFF,Multicore Error Detection feature of ADC is Disabled 
*/
[!/* [cover parentID={0DDDB039-48E5-4042-8E60-C1208CE844B4}]ADC_MULTICORE_ERROR_DETECT[/cover] */!][!//
#define ADC_MULTICORE_ERROR_DETECT  [!//
[!CALL "Adc_ConfigPreCompileSwitch","NodeVal" = "AdcGeneral/AdcMultiCoreErrorDetect"!][!//

/*
Configuration: ADC_LOW_POWER_STATE_SUPPORT
Switch for enabling the Low Power States Support features of ADC. 
- if STD_ON, Low Power States Support feature of ADC is Enabled 
- if STD_OFF,Low Power States Support feature of ADC is Disabled 
*/
[!/* [cover parentID={D14E165D-6B7A-4dbf-96FB-2FFC94E812B3}]ADC_LOW_POWER_STATE_SUPPORT[/cover] */!][!//
#define ADC_LOW_POWER_STATE_SUPPORT  [!//
[!IF "(node:exists(AdcGeneral/AdcLowPowerStatesSupport/*[1]))"!][!//
[!CALL "Adc_ConfigPreCompileSwitch","NodeVal" = "AdcGeneral/AdcLowPowerStatesSupport/*[1]"!][!//
[!ELSE!][!//
(STD_OFF)[!//
[!ENDIF!][!//

/* This parameter provides the bit state for Configured Power modes with decreasing
   power consumptions based on the instances of Adc Power State Configurations i.e.
   0th bit position indicates the 1st instances,1st bit position indicates the 2nd instances so on..*/
[!NOCODE!][!//
[!VAR "PowerModeBit" = "num:i(0)"!][!//
[!LOOP "node:order(AdcGeneral/AdcPowerStateConfig/*, './AdcPowerState')"!][!//
  [!VAR "PowerModeVal" = "num:i(AdcPowerState)"!]
  [!VAR "PowerModeBit" = "bit:or($PowerModeBit,bit:shl(1,$PowerModeVal))"!][!//]
[!ENDLOOP!][!//
[!ENDNOCODE!][!//
[!IF "$PowerModeBit != num:i(0)"!][!//
  [!IF "not(bit:getbit($PowerModeBit,0))"!][!//
  [!ERROR!][!//
    ADC Code Generator: Power mode corresponding to full power state is not available
  [!ENDERROR!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!/* [cover parentID={759BF374-9552-4c97-961A-1008EFA622DB}]ADC_POWER_MODES_AVAILABLE[/cover] */!][!//
#define ADC_POWER_MODES_AVAILABLE  ([!"num:inttohex($PowerModeBit,8)"!]U)[!//

/*
Configuration: ADC_SYNC_CONV_ENABLE
Switch for Enabling the synchronous conversions across ADC HW groups. 
- if STD_ON, Synchronous conversions across ADC HW groups is Enabled 
- if STD_OFF,Synchronous conversions across ADC HW groups is Disabled 
*/
[!/* [cover parentID={0F3540AC-D004-4266-B434-D713FF5A976E}]ADC_SYNC_CONV_ENABLE[/cover] */!][!//
#define ADC_SYNC_CONV_ENABLE  [!//
[!CALL "Adc_ConfigPreCompileSwitch","NodeVal" = "AdcGeneral/AdcSyncConvEnable"!][!//

/* Configuration: ADC_RUN_TIME_API_MODE
Determines the privilege mode in which the runtime APIs would operate
*/
[!/* [cover parentID={8699AFA6-421D-4ee0-BA97-AA99A3FB4974}]Precompile Time support for User Mode[/cover] */!][!//
[!/* [cover parentID={AC3426CA-A543-48af-91BC-11149FE5877D}]ADC_RUN_TIME_API_MODE[/cover] */!][!//
#define ADC_RUN_TIME_API_MODE  ([!"AdcGeneral/AdcRuntimeApiMode"!])

/* Configuration: ADC_INIT_DEINIT_API_MODE
Determines the privilege mode in which the Initialization and De-initialization APIs would operate
*/
[!/* [cover parentID={8699AFA6-421D-4ee0-BA97-AA99A3FB4974}]Precompile Time support for User Mode[/cover] */!][!//
[!/* [cover parentID={390AE397-D4A6-4aa8-B300-CDCDF904346E}]ADC_INIT_DEINIT_API_MODE[/cover] */!][!//
#define ADC_INIT_DEINIT_API_MODE  ([!"AdcGeneral/AdcInitDeInitApiMode"!])

/* Configuration: ADC_MAX_CH_CONV_TIME
Determines the maximum channel conversion time in terms of wait loop count
*/
[!/* [cover parentID={DC40340A-06BB-4811-A61F-D0A962EB5CD7}]ADC_MAX_CH_CONV_TIME[/cover] */!][!//
#define ADC_MAX_CH_CONV_TIME  ([!"AdcGeneral/AdcMaxChConvTimeCount"!]U)
[!/* [cover parentID={B30CBE45-EA79-4e26-BA52-F7AEB7335342}]ADC_E_CLC_FAILURE[/cover] */!][!//
/* Configuration: ADC_CLC_FAILURE_DEM_NOTIF and ADC_E_CLC_FAILURE
   Determines whether DEM for CLC failure is enabled or disabled.
*/
[!IF "(node:exists(AdcDemEventParameterRefs/*[1]))"!][!//
[!SELECT "AdcDemEventParameterRefs/*[1]"!][!//
[!IF "(node:exists(./AdcClcFailureNotification/*[1]))"!][!//
[!/* [cover parentID={2D5E0294-32A5-423b-BA80-A82725AF68FC}]ADC_CLC_FAILURE_DEM_NOTIF[/cover] */!][!//
#define ADC_CLC_FAILURE_DEM_NOTIF  (ADC_ENABLE_DEM_REPORT)
[!/* [cover parentID={E206BEE6-B985-493b-925E-0776E02CAE20}]ADC_E_CLC_FAILURE[/cover] */!][!//
[!/* [cover parentID={B30CBE45-EA79-4e26-BA52-F7AEB7335342}]ADC_E_CLC_FAILURE[/cover] */!][!//
#define ADC_E_CLC_FAILURE          (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./AdcClcFailureNotification/*[1])))"!])
[!ELSE!][!//
[!/* [cover parentID={2D5E0294-32A5-423b-BA80-A82725AF68FC}]ADC_CLC_FAILURE_DEM_NOTIF[/cover] */!][!//
#define ADC_CLC_FAILURE_DEM_NOTIF  (ADC_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ELSE!][!//
[!/* [cover parentID={2D5E0294-32A5-423b-BA80-A82725AF68FC}]ADC_CLC_FAILURE_DEM_NOTIF[/cover] */!][!//
#define ADC_CLC_FAILURE_DEM_NOTIF  (ADC_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* Configuration: ADC_CONV_STOP_TIME_DEM_NOTIF and ADC_E_CONV_STOP_TIME_FAILURE
   Determines whether wait counts configured at AdcMaxChConvTimeCount to
   stop the conversion is sufficient or not.
*/
[!IF "(node:exists(AdcDemEventParameterRefs/*[1]))"!][!//
[!SELECT "AdcDemEventParameterRefs/*[1]"!][!//
[!IF "(node:exists(./AdcConvStopTimeNotification/*[1]))"!][!//
[!/* [cover parentID={CEEF3A5F-13F1-4284-A1F4-0AD721784598}]ADC_CONV_STOP_TIME_DEM_NOTIF[/cover] */!][!//
#define ADC_CONV_STOP_TIME_DEM_NOTIF  (ADC_ENABLE_DEM_REPORT)
[!/* [cover parentID={3D49001C-D776-494c-A69B-CED30CDDF83E}]ADC_E_CONV_STOP_TIME_FAILURE[/cover] */!][!//
[!/* [cover parentID={85E678A4-338C-44ee-A550-03E9E88C3425}]ADC_E_CONV_STOP_TIME_FAILURE[/cover] */!][!//
#define ADC_E_CONV_STOP_TIME_FAILURE  (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./AdcConvStopTimeNotification/*[1])))"!])
[!ELSE!][!//
[!/* [cover parentID={CEEF3A5F-13F1-4284-A1F4-0AD721784598}]ADC_CONV_STOP_TIME_DEM_NOTIF[/cover] */!][!//
#define ADC_CONV_STOP_TIME_DEM_NOTIF  (ADC_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ELSE!][!//
[!/* [cover parentID={CEEF3A5F-13F1-4284-A1F4-0AD721784598}]ADC_CONV_STOP_TIME_DEM_NOTIF[/cover] */!][!//
#define ADC_CONV_STOP_TIME_DEM_NOTIF  (ADC_DISABLE_DEM_REPORT)
[!ENDIF!][!//


/* This parameter contains the maximum number of ADC Channel groups 
configured across HW units and configuration sets.
It is required for Queue mechanism in No Priority mode of operation.
For example, if there are 4 HW Units configured with maximum 2, 3, 4 and 5 
groups respectively in each HW Units,then ADC_MAX_GROUPS 
must be configured as 5.*/
[!NOCODE!][!//
[!VAR "AdcMaxGroupCount"= "num:i(0)"!][!//
[!VAR "AdcHwUnitCount" = "num:i(count(AdcConfigSet/AdcHwUnit/*))"!][!//
[!FOR "HwUnitIdx" ="num:i(1)" TO "num:i($AdcHwUnitCount)"!][!//
[!VAR "AdcGroupCount" = "num:i(count(AdcConfigSet/AdcHwUnit/*[num:i($HwUnitIdx)]/AdcGroup/*))"!][!//
[!IF "$AdcGroupCount > $AdcMaxGroupCount"!][!//
  [!VAR "AdcMaxGroupCount" = "num:i($AdcGroupCount)"!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDNOCODE!][!//
[!/* [cover parentID={C31825E7-3498-48a5-88E8-41A315EF3A90}]ADC_MAX_GROUPS[/cover] */!][!//
#define ADC_MAX_GROUPS  ([!"num:i($AdcMaxGroupCount)"!]U)
[!VAR "CGCoreUsed" = "''"!][!//
[!VAR "CGModuleMap" = "''"!][!//
[!VAR "CGAllocatedResources" = "''"!][!//
[!VAR "CGMasterCoreId" = "''"!][!//

[!CALL "Adc_GenerateModuleMap", "Module"="'ADC'"!][!//
[!LOOP "AdcConfigSet/AdcHwUnit/*"!][!//
  [!/* Append the missing resources to master core */!][!//
  [!CALL "Adc_ValidateChAllocation", "Item" = "node:name(node:current())"!][!//
  [!IF "$CGResult = 'FALSE'"!][!//
    [!VAR "CGModuleMap" = "concat($CGModuleMap, 'CORE', $CGMasterCoreId, '_', node:name(node:current()), ',')"!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//
[!FOR "CoreIndex" = "num:i(1)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable'))"!][!//
  [!VAR "corePattern" = "concat( 'CORE', num:i($CoreIndex - 1) )"!][!//
  [!VAR "matchCore" = "concat( '^.*(', $corePattern, ').*$' )"!][!//
  [!VAR "AdcHwUnitUsed"= "num:i(0)"!][!//
  [!IF "text:match($CGCoreUsed, $matchCore)"!][!// Fetch all strings matching the core.
    [!VAR "AdcHwUnitCount" = "num:i(count(AdcConfigSet/AdcHwUnit/*))"!][!//
    [!FOR "HwUnitIdx" ="num:i(1)" TO "num:i($AdcHwUnitCount)"!][!//
      [!SELECT "AdcConfigSet/AdcHwUnit/*[num:i($HwUnitIdx)]"!][!//
        [!VAR "hwUnitPattern" = "node:name(node:current())"!][!//
        [!VAR "matchPattern" = "concat( '^.*(', $corePattern, '_', $hwUnitPattern,',', ').*$' )"!][!//
        [!IF "text:match($CGModuleMap, $matchPattern)"!][!//
          [!VAR "AdcHwId" = "num:i(text:split(AdcHwUnitId,'_ADC')[2])"!][!//
          [!VAR "AdcHwUnitUsed" = "bit:or($AdcHwUnitUsed, bit:shl(1,$AdcHwId))"!][!//
        [!ENDIF!][!//
      [!ENDSELECT!][!//
    [!ENDFOR!][!//
    [!//
  [!ENDIF!][!//
  [!VAR "AdcMaxHwUnitCount"= "num:i(0)"!][!//
  [!FOR "BitIdx" ="num:i(1)" TO "num:i(ecu:get('Adc.MaxHwUnitId'))"!][!//

/*This parameter provides the array index for the Hw Unit [!"num:i($BitIdx - 1)"!] in the Adc_Hw_Unit
Data structure of CPU Core[!"num:i($CoreIndex - 1)"!]. Value of 0xFF is for an unconfigured Hw Unit */
    [!IF "bit:getbit($AdcHwUnitUsed, num:i($BitIdx - 1))"!][!//
      [!AUTOSPACING!][!//
      [!INDENT "0"!][!//
#define ADC[!"num:i($BitIdx - 1)"!]_KERNEL_INDEX_CORE[!"num:i($CoreIndex - 1)"!]  ([!"num:i($AdcMaxHwUnitCount)"!]U)
      [!ENDINDENT!][!//
      [!VAR "AdcMaxHwUnitCount"= "num:i($AdcMaxHwUnitCount+1)"!][!//
    [!ELSE!][!//
      [!AUTOSPACING!][!//
      [!INDENT "0"!][!//
#define ADC[!"num:i($BitIdx - 1)"!]_KERNEL_INDEX_CORE[!"num:i($CoreIndex - 1)"!]  (0xFFU)
      [!ENDINDENT!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  
/*** Group of all the indexes used for all the KERNELs on CPU Core[!"num:i($CoreIndex - 1)"!] ***/
[!/* [cover parentID={F45E6A5F-468C-4c93-9388-AC3787DF5912}]ADCX_KERNEL_INDEX_CORE[X][/cover] */!][!//
[!/* [cover parentID={6F0C1B73-E8DA-4214-801E-7B93884674C6}]ADC[Y]_KERNEL_INDEX_CORE[X][/cover] */!][!//
#define ADCX_KERNEL_INDEX_CORE[!"num:i($CoreIndex - 1)"!]   ADC0_KERNEL_INDEX_CORE[!"num:i($CoreIndex - 1)"!],\
ADC1_KERNEL_INDEX_CORE[!"num:i($CoreIndex - 1)"!],\
ADC2_KERNEL_INDEX_CORE[!"num:i($CoreIndex - 1)"!],\
ADC3_KERNEL_INDEX_CORE[!"num:i($CoreIndex - 1)"!],\
ADC4_KERNEL_INDEX_CORE[!"num:i($CoreIndex - 1)"!],\
ADC5_KERNEL_INDEX_CORE[!"num:i($CoreIndex - 1)"!],\
ADC6_KERNEL_INDEX_CORE[!"num:i($CoreIndex - 1)"!],\
ADC7_KERNEL_INDEX_CORE[!"num:i($CoreIndex - 1)"!],\
ADC8_KERNEL_INDEX_CORE[!"num:i($CoreIndex - 1)"!],\
ADC9_KERNEL_INDEX_CORE[!"num:i($CoreIndex - 1)"!],\
ADC10_KERNEL_INDEX_CORE[!"num:i($CoreIndex - 1)"!],\
ADC11_KERNEL_INDEX_CORE[!"num:i($CoreIndex - 1)"!]
  
/* This parameter stores the maximum number of ADC HW Units configured 
on CPU Core[!"num:i($CoreIndex - 1)"!] across all configuration sets.*/
[!/* [cover parentID={3B1C69DC-F637-4b51-8479-32DB34178C4A}]ADC_KERNEL_USED_COUNT_CORE[/cover] */!][!//
#define ADC_KERNEL_USED_COUNT_CORE[!"num:i($CoreIndex - 1)"!]  ([!"num:i($AdcMaxHwUnitCount)"!]U)

[!ENDFOR!][!//

/* This parameter stores the maximum number of ADC HW Units present in the HW*/
#define ADC_MAX_KERNELS  ([!"ecu:get('Adc.MaxHwUnits')"!]U)

/* This parameter stores the ADC HW Unit ID of the last KERNEL + 1 present in the HW*/
#define ADC_MAX_KERNEL_ID  ([!"ecu:get('Adc.MaxHwUnitId')"!]U)

/* This parameter defines the ADC HW Unit ID for the last primary KERNEL */
#define ADC_LAST_PRIMARY_KERNELID  ([!"num:i(ecu:get('Adc.LastPrimaryHwUnit'))"!]U)

/* This parameter provides the Request Source available per ADC KERNEL */
#define ADC_REQSRC_COUNT ([!"ecu:get('Adc.RSCount')"!]U)

/* This parameter provides the Request Source used per ADC KERNEL */
[!IF "AdcGeneral/AdcPriorityImplementation != 'ADC_PRIORITY_NONE'"!][!//
[!/* [cover parentID={29197480-F387-4a98-953A-3801295CFF5D}]ADC_REQSRC_USED_COUNT[/cover] */!][!//
#define ADC_REQSRC_USED_COUNT ([!"ecu:get('Adc.RSCount')"!]U)
[!ELSE!][!//
[!/* [cover parentID={29197480-F387-4a98-953A-3801295CFF5D}]ADC_REQSRC_USED_COUNT[/cover] */!][!//
#define ADC_REQSRC_USED_COUNT (1U)
[!ENDIF!][!//


/******Symbolic Name for all the AdcGroup with Group ID******/
[!VAR "AdcHwUnitCount" = "num:i(count(AdcConfigSet/AdcHwUnit/*))"!][!//
[!FOR "HwUnitIdx" ="num:i(1)" TO "num:i($AdcHwUnitCount)"!][!//
[!SELECT "AdcConfigSet/AdcHwUnit/*[num:i($HwUnitIdx)]"!][!//
[!VAR "AdcHwId" = "num:i(text:split(AdcHwUnitId,'_ADC')[2])"!][!//
/******Symbolic Name for all the AdcGroup of HW Unit [!"num:i($AdcHwId)"!]******/
[!LOOP "node:order(./AdcGroup/*, './AdcGroupId')"!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   in generated code due to Autosar Naming constraints.*/ 
#ifndef AdcConf_AdcGroup_[!"node:name(.)"!]
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   in generated code due to Autosar Naming constraints.*/
[!/* [cover parentID={6FFAA1D4-A2BF-4a72-B071-88CAC1CDDC50}]AdcConf_AdcGroup_<AdcGroupName>[/cover] */!][!//   
#define AdcConf_AdcGroup_[!"node:name(.)"!]  ([!"./AdcGroupId"!]U)
#endif
[!ENDLOOP!][!//

[!ENDSELECT!][!//
[!ENDFOR!][!//

/******Symbolic Name for all the AdcChannel with Channel ID******/
[!VAR "AdcHwUnitCount" = "num:i(count(AdcConfigSet/AdcHwUnit/*))"!][!//
[!FOR "HwUnitIdx" ="num:i(1)" TO "num:i($AdcHwUnitCount)"!][!//
[!SELECT "AdcConfigSet/AdcHwUnit/*[num:i($HwUnitIdx)]"!][!//
[!VAR "AdcHwId" = "num:i(text:split(AdcHwUnitId,'_ADC')[2])"!][!//
/******Symbolic Name for all the AdcChannel of HW Unit [!"num:i($AdcHwId)"!]******/
[!LOOP "node:order(./AdcChannel/*, './AdcChannelId')"!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   in generated code due to Autosar Naming constraints.*/ 
#ifndef AdcConf_AdcChannel_[!"node:name(.)"!]
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   in generated code due to Autosar Naming constraints.*/
[!/* [cover parentID={1FEC229D-F5E1-4e25-8F6F-D12D3F95530B}]AdcConf_AdcChannel_<AdcChannelName>[/cover] */!][!//  
#define AdcConf_AdcChannel_[!"node:name(.)"!]  ([!"./AdcChannelId"!]U)
#endif
[!ENDLOOP!][!//

[!ENDSELECT!][!//
[!ENDFOR!][!//

/******Symbolic Name for Power State Config******/
[!LOOP "node:order(AdcGeneral/AdcPowerStateConfig/*, './AdcPowerState')"!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   in generated code due to Autosar Naming constraints.*/ 
#ifndef AdcConf_AdcPowerStateConfig_[!"node:name(.)"!]
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   in generated code due to Autosar Naming constraints.*/ 
[!/* [cover parentID={19D5B854-3813-4e0a-AF5F-0CADB861834A}]AdcConf_AdcPowerStateConfig_<AdcPowerState>[/cover] */!][!//  
#define AdcConf_AdcPowerStateConfig_[!"node:name(.)"!]  ([!"./AdcPowerState"!]U)
#endif
[!ENDLOOP!]
[!//
[!ENDSELECT!][!//

#endif


