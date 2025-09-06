[!/*****************************************************************************
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
**  FILENAME  : Can_17_McmCan_Cfg.h                                           **
**                                                                            **
**  VERSION   : 4.0.0                                                         **
**                                                                            **
**  DATE      : 2018-08-08                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Can_17_McmCan.bmd                                 **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={A7B6579C-0625-4f54-9CC9-6C4981949D65}]    **
**                                                                            **
**  DESCRIPTION  : Code template header file for Can Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Can Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!]
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
**  FILENAME  : Can_17_McmCan_Cfg.h                                           **
**                                                                            **
**  VERSION   : 4.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                                          **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                                            **
**                                                                            **
**  BSW MODULE DECRIPTION : Can_17_McmCan.bmd                                 **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Can configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Can Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef CAN_17_MCMCAN_CFG_H
#define CAN_17_MCMCAN_CFG_H
[!/* Include Code Generator Macros */!][!//
[!INCLUDE "Can_17_McmCan.m"!][!//
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Can')[1]/CanConfigSet"!][!//
[!//
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/*******************************************************************************
**                      Common Published Information                          **
*******************************************************************************/
[!NOCODE!][!//
  /* Autosar specification version */
  [!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
  [!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
  [!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
[!ENDNOCODE!][!//
/* [cover parentID={7BE20AAE-30B8-46f5-ABBC-F2E65FBCEEE8}]
[/cover] */
#define CAN_17_MCMCAN_AR_RELEASE_MAJOR_VERSION          ([!"$MajorVersion"!]U)
/* [cover parentID={B0D7A378-F23B-4f83-86A7-50682CB089E5}]
[/cover] */
#define CAN_17_MCMCAN_AR_RELEASE_MINOR_VERSION          ([!"$MinorVersion"!]U)
/* [cover parentID={F34E3ADE-341D-4e08-9A3B-B454B00382E4}]
[/cover] */
#define CAN_17_MCMCAN_AR_RELEASE_REVISION_VERSION       ([!"$RevisionVersion"!]U)
[!NOCODE!][!//
  /* Vendor specific implementation version information */
  [!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
  [!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
  [!VAR "SwPatchVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
[!ENDNOCODE!]
/* [cover parentID={98E1F5ED-AA8E-49af-8DBB-E84CD1B0960B}]
[/cover] */
#define CAN_17_MCMCAN_SW_MAJOR_VERSION                  ([!"$SwMajorVersion"!]U)
/* [cover parentID={EAB7012E-044A-4fb7-84E1-245B81493A73}]
[/cover] */
#define CAN_17_MCMCAN_SW_MINOR_VERSION                  ([!"$SwMinorVersion"!]U)
/* [cover parentID={4763C7E9-3BE5-4b3b-96DA-1E92B11A9191}]
[/cover] */
#define CAN_17_MCMCAN_SW_PATCH_VERSION                  ([!"$SwPatchVersion"!]U)
[!VAR "MaxKernel" = "num:i(ecu:get('Can.MaxKernels'))"!][!//
[!VAR "MaxController" = "num:i(ecu:get('Can.MaxCtrlKer'))"!][!//
[!VAR "MaxConfigCont"= "num:i(ecu:get('Can.MaxControllers'))"!][!//
[!VAR "MaxCore" = "num:i(ecu:get('Mcu.NoOfCoreAvailable'))"!][!//
[!/* Can Activated controller identification and allocation */!][!//
[!CALL "CAN_CG_ControllerAllocation"!][!//
[!/* Bring in core specific configuration of the CAN controllers */!][!//
[!CALL "CAN_CG_GenerateModuleMap","Module" = "'CAN'"!][!//
[!VAR "BusOffInterruptStatus" = "num:i(0)"!][!//
[!VAR "RxInterruptStatus" = "num:i(0)"!][!//
[!VAR "TxInterruptStatus" = "num:i(0)"!][!//
[!VAR "BusOffPollingStatus" = "num:i(0)"!][!//
[!VAR "RxPollingStatus" = "num:i(0)"!][!//
[!VAR "TxPollingStatus" = "num:i(0)"!][!//
[!VAR "WUPollingStatus" = "num:i(0)"!][!//
[!LOOP "./CanController/*"!][!//
[!IF "CanControllerActivation = 'true'"!][!//
[!IF "CanBusoffProcessing = 'INTERRUPT'"!][!//
[!VAR "BusOffInterruptStatus" = "num:i(1)"!][!//
[!ELSE!][!//
[!VAR "BusOffPollingStatus" = "num:i(1)"!][!//
[!ENDIF!][!//
[!IF "CanRxProcessing = 'INTERRUPT'"!][!//
[!VAR "RxInterruptStatus" = "num:i(1)"!][!//
[!ELSE!][!//
[!VAR "RxPollingStatus" = "num:i(1)"!][!//
[!ENDIF!][!//
[!IF "CanTxProcessing = 'INTERRUPT'"!][!//
[!VAR "TxInterruptStatus" = "num:i(1)"!][!//
[!ELSE!][!//
[!VAR "TxPollingStatus" = "num:i(1)"!][!//
[!ENDIF!][!//
[!IF "CanWakeupProcessing   = 'POLLING'"!][!//
[!VAR "WUPollingStatus" = "num:i(1)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
/*******************************************************************************
**          Global Macro Definitions                                          **
*******************************************************************************/

/* Master core is allocated with CAN controllers */
[!IF "$CGMasterAlloc = 1"!][!//
#define CAN_17_MCMCAN_MASTER_CORE_ALLOCATION                       (STD_ON)
[!ELSE!][!//
#define CAN_17_MCMCAN_MASTER_CORE_ALLOCATION                       (STD_OFF)
[!ENDIF!][!//

/* [cover parentID={211F892D-CBE4-4d08-A1AF-EA8D2E16463B}]
[/cover] */
/* Multicore Enabled or not */
#define CAN_17_MCMCAN_MULTICORE_ERROR_DETECT                       [!//
[!CALL "CAN_CG_ConfigSwitch","nodeval" = "../CanGeneral/CanMultiCoreErrorDetect"!]

[!/* [cover parentID={1D964BF4-8B27-46da-A999-9B5888FF124A}]
[/cover] */!][!//
/* Maximum number of CAN Controllers configured in a ConfigSet */
#define CAN_17_MCMCAN_NOOF_CONTROLLER                       (uint8)([!"num:i(count(./CanController/*))"!]U)
[!FOR "CoreIndx" = "0" TO "$MaxCore - '1'"!][!//
[!VAR "CheckText" = "text:toupper(concat('CORE',$CoreIndx))"!][!//
[!/* Bring in core specific CAN controller count */!][!//
[!CALL "CAN_CG_GetContInCore","CoreName" = "$CheckText"!][!//
[!IF "text:contains( text:split($CGAllocCore,','), $CheckText )"!][!//

/* Maximum number of CAN Controllers configured in a ConfigSet for [!"$CheckText"!] */
#define CAN_17_MCMCAN_[!"$CheckText"!]_NOOF_CONTROLLER      (uint8)([!"$NoOfCont"!]U)
[!ENDIF!][!//
[!ENDFOR!][!//

/* The number of hardware objects (includes Tx and Rx) configured in a
ConfigSet */
#define CAN_17_MCMCAN_NOOF_HARDWARE_OBJECTS          (Can_HwHandleType) ([!"num:i(count(./CanHardwareObject/*))"!]U)

[!/* Loop for calculate Total number of Icom-Message and Icom-signal with in the configuration  */!][!//
[!VAR "TrigTransmit" = "num:i(0)"!][!//
[!VAR "CanHwObjectCount" = "num:i(count(./CanHardwareObject/*))"!][!//
[!FOR "HwObjIndx" = "1" TO "num:i($CanHwObjectCount)"!][!//
[!IF "node:exists(./CanHardwareObject/*[position()=$HwObjIndx]/CanTriggerTransmitEnable/*[1]) = 'true'"!][!//
[!IF "node:value(./CanHardwareObject/*[position()=$HwObjIndx]/CanTriggerTransmitEnable/*[1]) = 'true'"!][!//
[!VAR "TrigTransmit" = "num:i(1)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
/* [cover parentID={22BF2529-8DA1-4094-9A12-F0EEFE184EF5}]
[/cover] */
/* Trigger transmit Enabled or not */
#define CAN_17_MCMCAN_TRIG_TRANSMIT                                 ([!IF "$TrigTransmit = num:i(1)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

[!VAR "MultiTxPeriod" = "num:i(0)"!][!//
[!VAR "MultiRxPeriod" = "num:i(0)"!][!//
/* Maximum number of main function RW periods configured in a ConfigSet */
[!VAR "MultiperiodsVal" = "num:i(count(../CanGeneral/CanMainFunctionRWPeriods/*))"!][!//
[!IF "$MultiperiodsVal > 1"!][!//
[!IF "$RxPollingStatus = num:i(1)"!][!//
[!VAR "MultiRxPeriod" = "num:i(1)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!VAR "MultiperiodsVal" = "num:i(count(../CanGeneral/CanMainFunctionRWPeriods/*))"!][!//
[!IF "$MultiperiodsVal > 1"!][!//
[!IF "$TxPollingStatus = num:i(1)"!][!//
[!VAR "MultiTxPeriod" = "num:i(1)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
#define CAN_17_MCMCAN_NOOF_RX_TX_PERIODS_CONFIG              ([!"$MultiperiodsVal"!]U)

/* Multiple cycle period for Recieve is configured in a ConfigSet */
#define CAN_17_MCMCAN_RX_MULTI_PERIODS_SUPPORT               ([!IF "$MultiRxPeriod = num:i(1)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/* Multiple cycle period for Transmit is configured in a ConfigSet */
#define CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT               ([!IF "$MultiTxPeriod = num:i(1)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

[!VAR "IcomRxMsgCount" = "num:i(0)"!][!//
[!VAR "IcomRxMsgSignalCount" = "num:i(0)"!][!//
[!VAR "IcomConfigCount" = "num:i(count(./CanIcom/./*[1]/CanIcomConfig/*))"!][!//
[!IF "../CanGeneral/CanPublicIcomSupport = 'true'"!][!//
[!/* Loop for calculate Total number of Icom-Message and Icom-signal with in the configuration  */!][!//
[!LOOP "./CanIcom/./*[1]/CanIcomConfig/*"!][!//
[!VAR "IcomRxMsgCount" = "num:i(count(./CanIcomWakeupCauses/CanIcomRxMessage/*) + $IcomRxMsgCount )"!][!//
[!FOR "Rxindx" = "1" TO "num:i($IcomRxMsgCount)"!][!//
[!IF "node:exists(./CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomRxMessageSignalConfig/*) = 'true'"!][!//
[!VAR "IcomRxMsgSignalCount" = "num:i(count(./CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomRxMessageSignalConfig/*) + $IcomRxMsgSignalCount)"!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDLOOP!][!//
[!/* [cover parentID={6B735756-7B1C-4ca3-85E4-B389A7F41960}]
[/cover] */!][!//
/* Maximum number of Icom configurations with in the ConfigSet */
#define CAN_17_MCMCAN_NOOF_ICOM_CONFIGURATIONS        (IcomConfigIdType) ([!"$IcomConfigCount"!]U)

[!/* [cover parentID={4395F5EB-4259-4798-9FA0-48F585BDB108}]
[/cover] */!][!//
/* Maximum number of Icom Message configurations with in the ConfigSet */
#define CAN_17_MCMCAN_NOOF_ICOM_MSGCONFIGURATIONS     ([!"$IcomRxMsgCount"!]U)

[!/* [cover parentID={CFF33692-9DAF-4876-B8A6-C210DDB76E72}]
[/cover] */!][!//
/* Maximum number of Icom Signal configurations with in the ConfigSet */
#define CAN_17_MCMCAN_NOOF_ICOM_SIGNALCONFIGURATIONS  ([!"$IcomRxMsgSignalCount"!]U)
[!ENDIF!][!//

/* Initialization and De-Initilaization user mode configuration */
#define CAN_17_MCMCAN_INIT_DEINIT_API_MODE   ([!"../CanGeneral/CanInitDeInitApiMode"!])

/*******************************************************************************
**                      CAN General Information                               **
*******************************************************************************/
/* Configuration: CAN_17_MCMCAN_INSTANCE_ID
 - Specifies the InstanceId of this module instance
*/
[!/* [cover parentID={E82F8AA2-1043-440c-85D6-2C804A008B52}]
[/cover] */!][!//
#define CAN_17_MCMCAN_INSTANCE_ID                     ([!"../CanGeneral/CanIndex"!]U)

/* Configuration: CAN_17_MCMCAN_DEV_ERROR_DETECT
 - STD_ON  - DET is enabled
 - STD_OFF - DET is disabled
*/
[!/* [cover parentID={A8611F59-B315-4dab-AE47-64C8D534CC84}]
[/cover] */!][!//
#define CAN_17_MCMCAN_DEV_ERROR_DETECT                            [!//
[!CALL "CAN_CG_ConfigSwitch","nodeval" = "../CanGeneral/CanDevErrorDetection"!]

/* Configuration: CAN_17_MCMCAN_VERSION_INFO_API
 - STD_ON  - Can_17_McmCan_GetVersionInfo API is enabled
 - STD_OFF - Can_17_McmCan_GetVersionInfo API is disabled
*/
[!/* [cover parentID={BFA2B975-6875-4b44-9279-CE09AF0D31A1}]
[/cover] */!][!//
#define CAN_17_MCMCAN_VERSION_INFO_API                            [!//
[!CALL "CAN_CG_ConfigSwitch","nodeval" = "../CanGeneral/CanVersionInfoApi"!]

/* Configuration: CAN_17_MCMCAN_MULTIPLEXED_TRANSMISSION
 - STD_ON  - Multiplexed transmission feature is enabled
 - STD_OFF - Multiplexed transmission feature is disabled
*/
[!/* [cover parentID={50E6705F-C8BB-46fa-9C9F-A7908348E200}]
[/cover] */!][!//
#define CAN_17_MCMCAN_MULTIPLEXED_TRANSMISSION                    [!//
[!CALL "CAN_CG_ConfigSwitch","nodeval" = "../CanGeneral/CanMultiplexedTransmission"!]

/* Configuration: CAN_17_MCMCAN_TIMEOUT_DURATION
 - Specifies the maximum amount of time for a blocking function until
   a time-out is raised in short term wait loops
*/
[!/* [cover parentID={F045BC45-613C-42a0-9436-C72F69722508}]
[/cover] */!][!//
[!VAR "CanTimeoutDuration" = "../CanGeneral/CanTimeoutDuration"!][!//
#define CAN_17_MCMCAN_TIMEOUT_DURATION                            ([!"num:i($CanTimeoutDuration * 10000000)"!]U)

/* Configuration: CAN_17_MCMCAN_SET_BAUDRATE_API
 - STD_ON  - Can_17_McmCan_SetBaudrate API is enabled
 - STD_OFF - Can_17_McmCan_SetBaudrate API is Disabled
*/
[!/* [cover parentID={B3714324-EEA9-44ee-8BC0-0695D8DE4EDC}]
[/cover] */!][!//
[!IF "node:exists(../CanGeneral/CanSetBaudrateApi/*[1]) = 'true'"!][!//
#define CAN_17_MCMCAN_SET_BAUDRATE_API                            [!//
[!CALL "CAN_CG_ConfigSwitch","nodeval" = "../CanGeneral/CanSetBaudrateApi/*[1]"!]
[!ELSE!][!//
#define CAN_17_MCMCAN_SET_BAUDRATE_API                           (STD_OFF)
[!ENDIF!][!//

/* Configuration: CanControllerFdBaudrateConfig
 - STD_ON  - FD Operation is Enabled
 - STD_OFF - FD Operation is Disabled
*/
[!/* [cover parentID={B5240496-84D2-4b7c-8F70-A9B7C12273B1}]
[/cover] */!][!//
[!/* Loop set for controller specific information read */!][!//
[!VAR "FDNodesPresentVal" = "num:i(0)"!][!//
[!LOOP "./CanController/*"!][!//
[!VAR "BaudrateCfgCount" = "num:i(count(./CanControllerBaudrateConfig/*))"!][!//
[!FOR "BaudrateIndx" = "1" TO "$BaudrateCfgCount"!][!//
[!IF "(node:exists(CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]))"!][!//
[!/* Set Global switch for FD support */!][!//
[!VAR "FDNodesPresentVal" = "num:i(1)"!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDLOOP!][!//
[!IF "$FDNodesPresentVal = 0"!][!//
#define CAN_17_MCMCAN_FD_ENABLE                                   (STD_OFF)
[!ELSE!][!//
#define CAN_17_MCMCAN_FD_ENABLE                                   (STD_ON)
[!ENDIF!][!//

/* Configuration: CAN_17_MCMCAN_DEINIT_API
 - STD_ON  - CAN De-initialization API is enabled
 - STD_OFF - CAN De-initialization API is not enabled
*/
[!/* [cover parentID={D6062C72-4A90-433c-9B34-44D01B2A096E}]
[/cover] */!][!//
#define CAN_17_MCMCAN_DEINIT_API                                  [!//
[!CALL "CAN_CG_ConfigSwitch","nodeval" = "../CanGeneral/CanDeInitApi"!]

/* Configuration: CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT
 - STD_ON  - CAN Pretended networking is enabled
 - STD_OFF - CAN Pretended networking is not enabled
*/
[!/* [cover parentID={5C4ADE3F-9408-4970-821C-BF1F0402FBA9}]
[/cover] */!][!//
#define CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT                         [!//
[!CALL "CAN_CG_ConfigSwitch","nodeval" = "../CanGeneral/CanPublicIcomSupport"!]

/******************************************************************************/
                    /* CAN Controller Configurations */
/******************************************************************************/
/* CAN Activation on CORE0
 - STD_ON  - A CAN Kernel is activated on Core 0
 - STD_OFF - No CAN Kernel is activated on Core 0
*/
[!IF "not(text:contains( text:split($CGAllocCore,','), "CORE0" ))"!][!//
#define CAN_17_MCMCAN_CORE0_ACTIVATION                     (STD_OFF)
[!ELSE!][!//
#define CAN_17_MCMCAN_CORE0_ACTIVATION                     (STD_ON)
[!ENDIF!][!//
/* CAN Activation on CORE1
 - STD_ON  - A CAN Kernel is activated on Core 1
 - STD_OFF - No CAN Kernel is activated on Core 1
*/
[!IF "not(text:contains( text:split($CGAllocCore,','), "CORE1" ))"!][!//
#define CAN_17_MCMCAN_CORE1_ACTIVATION                     (STD_OFF)
[!ELSE!][!//
#define CAN_17_MCMCAN_CORE1_ACTIVATION                     (STD_ON)
[!ENDIF!][!//
/* CAN Activation on CORE2
 - STD_ON  - A CAN Kernel is activated on Core 2
 - STD_OFF - No CAN Kernel is activated on Core 2
*/
[!IF "not(text:contains( text:split($CGAllocCore,','), "CORE2" ))"!][!//
#define CAN_17_MCMCAN_CORE2_ACTIVATION                     (STD_OFF)
[!ELSE!][!//
#define CAN_17_MCMCAN_CORE2_ACTIVATION                     (STD_ON)
[!ENDIF!][!//
/* CAN Activation on CORE3
 - STD_ON  - A CAN Kernel is activated on Core 3
 - STD_OFF - No CAN Kernel is activated on Core 3
*/
[!IF "not(text:contains( text:split($CGAllocCore,','), "CORE3" ))"!][!//
#define CAN_17_MCMCAN_CORE3_ACTIVATION                     (STD_OFF)
[!ELSE!][!//
#define CAN_17_MCMCAN_CORE3_ACTIVATION                     (STD_ON)
[!ENDIF!][!//
/* CAN Activation on CORE4
 - STD_ON  - A CAN Kernel is activated on Core 4
 - STD_OFF - No CAN Kernel is activated on Core 4
*/
[!IF "not(text:contains( text:split($CGAllocCore,','), "CORE4" ))"!][!//
#define CAN_17_MCMCAN_CORE4_ACTIVATION                     (STD_OFF)
[!ELSE!][!//
#define CAN_17_MCMCAN_CORE4_ACTIVATION                     (STD_ON)
[!ENDIF!][!//
/* CAN Activation on CORE5
 - STD_ON  - A CAN Kernel is activated on Core 5
 - STD_OFF - No CAN Kernel is activated on Core 5
*/
[!IF "not(text:contains( text:split($CGAllocCore,','), "CORE5" ))"!][!//
#define CAN_17_MCMCAN_CORE5_ACTIVATION                     (STD_OFF)
[!ELSE!][!//
#define CAN_17_MCMCAN_CORE5_ACTIVATION                     (STD_ON)
[!ENDIF!][!//

/*BusOff Processing Event used as Interrupt
 - STD_ON - BusOff event is notified through Interrupt mechanism by the
            configured controller
 - STD_OFF - BusOff event is notified through Interrupt mechanism by the
            configured controller
*/
[!/* [cover parentID={770D12EC-4677-4f63-9D68-818459709219}]
[/cover] */!][!//
[!IF "$BusOffInterruptStatus = 0"!][!//
#define CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING                     (STD_OFF)
[!ELSE!][!//
#define CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING                     (STD_ON)
[!ENDIF!][!//

/* Transmission Processing Event used as Interrupt
 - STD_ON - Transmission event is notified through Interrupt mechanism by the
            configured controller
 - STD_OFF - Transmission event is notified through Interrupt mechanism by the
            configured controller
*/
[!/* [cover parentID={81AAE1E7-9BD4-4c1c-8CFF-FF767097AD58}]
[/cover] */!][!//
[!IF "$TxInterruptStatus = 0"!][!//
#define CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING                     (STD_OFF)
[!ELSE!][!//
#define CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING                     (STD_ON)
[!ENDIF!][!//

/* Reception Processing Event used as Interrupt
 - STD_ON - Reception event is notified through Interrupt mechanism by the
            configured controller
 - STD_OFF - Reception event is notified through Interrupt mechanism by the
            configured controller
*/
[!/* [cover parentID={51A4C1BD-C68D-4d15-AAAA-7F18A4D9D2C8}]
[/cover] */!][!//
[!IF "$RxInterruptStatus = 0"!][!//
#define CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING                     (STD_OFF)
[!ELSE!][!//
#define CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING                     (STD_ON)
[!ENDIF!][!//

/*BusOff Processing Event used as POLLING
 - STD_ON - BusOff event is notified through Polling mechanism by the
            configured controller
 - STD_OFF - BusOff event is notified through Polling mechanism by the
            configured controller
*/
[!/* [cover parentID={8893D9B6-249D-44f6-8A18-C81B908D3230}]
[/cover] */!][!//
[!IF "$BusOffPollingStatus = 0"!][!//
#define CAN_17_MCMCAN_BO_POLLING_PROCESSING                       (STD_OFF)
[!ELSE!][!//
#define CAN_17_MCMCAN_BO_POLLING_PROCESSING                       (STD_ON)
[!ENDIF!][!//

/* Transmission Processing Event used as POLLING
 - STD_ON - Transmission event is notified through Polling mechanism by the
            configured controller
 - STD_OFF - Transmission event is notified through Polling mechanism by the
            configured controller
*/
[!/* [cover parentID={3887D8F4-930A-4211-B1BA-D6F52B6E6169}]
[/cover] */!][!//
[!IF "$TxPollingStatus = 0"!][!//
#define CAN_17_MCMCAN_TX_POLLING_PROCESSING                       (STD_OFF)
[!ELSE!][!//
#define CAN_17_MCMCAN_TX_POLLING_PROCESSING                       (STD_ON)
[!ENDIF!][!//

/* Reception Processing Event used as POLLING
 - STD_ON - Reception event is notified through Polling mechanism by the
            configured controller
 - STD_OFF - Reception event is notified through Polling mechanism by the
            configured controller
*/
[!/* [cover parentID={2D792F9D-44FA-4ceb-B70E-DE7158C44480}]
[/cover] */!][!//
[!IF "$RxPollingStatus = 0"!][!//
#define CAN_17_MCMCAN_RX_POLLING_PROCESSING                       (STD_OFF)
[!ELSE!][!//
#define CAN_17_MCMCAN_RX_POLLING_PROCESSING                       (STD_ON)
[!ENDIF!][!//

/* WakeUp Processing Event used as POLLING
 - STD_ON - WakeUp event is notified through Polling mechanism by the
            configured controller
 - STD_OFF - WakeUp event is notified through Polling mechanism by the
            configured controller
*/
[!/* [cover parentID={5D842C6F-4C56-44fe-A623-7C6FE0032C1A}]
[/cover] */!][!//
[!IF "$WUPollingStatus = 0"!][!//
#define CAN_17_MCMCAN_WU_POLLING_PROCESSING                       (STD_OFF)
[!ELSE!][!//
#define CAN_17_MCMCAN_WU_POLLING_PROCESSING                       (STD_ON)
[!ENDIF!][!//

/* Controller Handle Id */
[!NOCODE!][!//
[!VAR "ActualCntrlIndex" = "'0'"!][!//
[!VAR "ControllerConfigMaxTemp" = "num:i(count(./CanController/*))"!][!//
[!FOR "Cntrlindx" = "0" TO "$ControllerConfigMaxTemp - 1"!][!//
[!LOOP "./CanController/*"!][!//
[!IF "CanControllerId = $Cntrlindx"!][!//
[!IF "CanControllerActivation = 'true'"!][!//
[!VAR "Text" = "node:name(.)"!][!//
[!CODE!][!//

[!/* [cover parentID={7BB086C8-4A6D-488b-9D5B-737BCF061C39}]
[/cover] */!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define Can_17_McmCanConf_CanController_[!"$Text"!]             [!"$ActualCntrlIndex"!]
[!ENDCODE!][!//
[!VAR "ActualCntrlIndex" = "num:i($ActualCntrlIndex+1)"!][!//
[!ENDIF!]
[!ENDIF!]
[!ENDLOOP!]
[!ENDFOR!]
[!ENDNOCODE!][!//

/* Hardware object Handle Id */
[!NOCODE!][!//
[!VAR "ActualHwIndex" = "'0'"!][!//
[!VAR "HwObjConfigMaxTemp" = "num:i(count(./CanHardwareObject/*))"!][!//
[!FOR "HwObjindx" = "0" TO "$HwObjConfigMaxTemp - 1"!][!//
[!LOOP "./CanHardwareObject/*"!][!//
[!IF "CanObjectId  = $HwObjindx"!][!//
[!IF "(node:ref(CanControllerRef)/CanControllerActivation = 'true')"!][!//
[!VAR "Text" = "node:name(.)"!][!//
[!CODE!][!//

[!/* [cover parentID={872AF529-27F3-43ce-AC9F-7F80AAE00986}]
[/cover] */!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define Can_17_McmCanConf_CanHardwareObject_[!"$Text"!]         [!"$ActualHwIndex"!]
[!ENDCODE!][!//
[!VAR "ActualHwIndex" = "num:i($ActualHwIndex+1)"!][!//
[!ENDIF!]
[!ENDIF!]
[!ENDLOOP!]
[!ENDFOR!]
[!ENDNOCODE!][!//

[!IF "../CanGeneral/CanPublicIcomSupport = 'true'"!][!//
/* ICOM Configuration Id */
#define Can_17_McmCanConf_CanIcomConfigIndex_Deactivate            0
[!VAR "IcomMax" = "num:i(count(./CanIcom/./*[1]/CanIcomConfig/*))"!][!//
[!FOR "Icomindx" = "1" TO "$IcomMax"!][!//
[!LOOP "./CanIcom/./*[1]/CanIcomConfig/*"!][!//
[!IF "CanIcomConfigId  = $Icomindx"!][!//
[!VAR "Text" = "node:name(.)"!][!//

[!/* [cover parentID={872AF529-27F3-43ce-AC9F-7F80AAE00986}]
[/cover] */!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define Can_17_McmCanConf_CanIcomConfigIndex_[!"$Text"!]         [!"$Icomindx"!]
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDFOR!][!//
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
[!VAR "HwObjMaxIndx" = "num:i(count(../CanGeneral/CanMainFunctionRWPeriods/*))"!][!//
[!IF "$HwObjMaxIndx>1"!][!//
[!IF "$MultiTxPeriod = num:i(1)"!]
/*******************************************************************************
**  Can_MainFunction_Write Function Declarations with multipleperiod support  **
*******************************************************************************/
[!FOR "HwObjindx" = "0" TO "$HwObjMaxIndx - 1"!][!//

[!/* [cover parentID={6C243DDF-2B43-4af4-81C0-D104AE3634B6}]
[/cover] */!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
extern void Can_17_McmCan_MainFunction_Write_[!"$HwObjindx"!](void);
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDIF!][!//

[!VAR "HwObjMaxIndx" = "num:i(count(../CanGeneral/CanMainFunctionRWPeriods/*))"!][!//
[!IF "$HwObjMaxIndx>1"!][!//
[!IF "$MultiRxPeriod = num:i(1)"!]
/*******************************************************************************
**  Can_MainFunction_Read Function Declarations with multipleperiod support  **
*******************************************************************************/
[!FOR "HwObjindx" = "0" TO "$HwObjMaxIndx - 1"!][!//

[!/* [cover parentID={D6383A7F-FBB5-4550-B179-C83DF72F254D}]
[/cover] */!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
extern void Can_17_McmCan_MainFunction_Read_[!"$HwObjindx"!](void);
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/
[!ENDSELECT!]
#endif  /* CAN_17_MCMCAN_CFG_H */