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
**  FILENAME  : McalLib_Cfg.h                                                 **
**                                                                            **
**  VERSION   : 6.0.0                                                         **
**                                                                            **
**  DATE      : 2018-08-09                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : McalLib.bmd                                       **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID]                                           **
**                                                                            **
**  DESCRIPTION  : Code template header file for Mcal Library                 **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Mcal Library                          **
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
**  FILENAME  : McalLib_Cfg.h                                                 **
**                                                                            **
**  VERSION   : 6.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                                      **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                                          **
**                                                                            **
**  BSW MODULE DECRIPTION : McalLib.bmd                                       **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : McalLib configuration generated out of ECUC file           **
**                                                                            **
**  SPECIFICATION(S) : Specification of McalLib Driver                        **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
[!/*[cover parentID={F6A194AF-8C7D-4aad-9FB1-E591B813604E}][/cover]*/!][!//
#ifndef MCALLIB_CFG_H
#define MCALLIB_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

[!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
[!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
[!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
#define MCALLIB_AR_RELEASE_MAJOR_VERSION      ([!"$MajorVersion"!]U)
#define MCALLIB_AR_RELEASE_MINOR_VERSION      ([!"$MinorVersion"!]U)
#define MCALLIB_AR_RELEASE_REVISION_VERSION   ([!"$RevisionVersion"!]U)

[!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
[!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
[!VAR "SwPatchVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
#define MCALLIB_SW_MAJOR_VERSION  ([!"$SwMajorVersion"!]U)
#define MCALLIB_SW_MINOR_VERSION  ([!"$SwMinorVersion"!]U)
#define MCALLIB_SW_PATCH_VERSION  ([!"$SwPatchVersion"!]U)

/*Number of cores available*/
[!/*[cover parentID={E6A3B6D0-1D03-43d0-A080-91CC4B3FA5FB}][/cover]*/!][!//
#define MCAL_NO_OF_CORES              ([!"num:inttohex(ecu:get('Mcu.NoOfCoreAvailable'))"!]U)

/* Backup clock frequency in MHz */
[!/*[cover parentID={96A719FE-796E-4832-9318-7C363CF66A1D}][/cover]*/!][!//
#define MCAL_BACKUP_FREQUENCY         ([!"num:inttohex(ecu:get('McalLib.BackupClockFreq'))"!]U)

/* System clock frequency in MHz*/
[!/*[cover parentID={C657D386-B9C9-42c5-A224-3CF461EB6152}][/cover]*/!][!//
#define MCAL_SYSCLK_FREQUENCY         ([!"num:inttohex(ecu:get('McalLib.SysClockFreq'))"!]U)

/* Global PSPR base address */
[!/*[cover parentID={3D07BBDD-A861-49c0-A6EA-A918D645D0A6}][/cover]*/!][!// 
#define MCAL_PSPR0_GLOBAL_BASE_ADDR   ([!"num:inttohex(ecu:get('McalLib.PsprCore0StartAddr'))"!]U)
[!IF "ecu:get('Mcu.fCPU1Exists') = 'true'"!][!//
[!/*[cover parentID={8C7162AA-6630-4ae6-95D4-B09D4DB05A04}][/cover]*/!][!//
#define MCAL_PSPR1_GLOBAL_BASE_ADDR   ([!"num:inttohex(ecu:get('McalLib.PsprCore1StartAddr'))"!]U)
[!ENDIF!][!//
[!IF "ecu:get('Mcu.fCPU2Exists') = 'true'"!][!//
[!/*[cover parentID={C46F068A-442E-4637-B90F-12710417A4CD}][/cover]*/!][!//
#define MCAL_PSPR2_GLOBAL_BASE_ADDR   ([!"num:inttohex(ecu:get('McalLib.PsprCore2StartAddr'))"!]U)
[!ENDIF!][!//
[!IF "ecu:get('Mcu.fCPU3Exists') = 'true'"!][!//
[!/*[cover parentID={ED499666-E048-4ced-BDB3-2E157C2AC0FA}][/cover]*/!][!//
#define MCAL_PSPR3_GLOBAL_BASE_ADDR   ([!"num:inttohex(ecu:get('McalLib.PsprCore3StartAddr'))"!]U)
[!ENDIF!][!//
[!IF "ecu:get('Mcu.fCPU4Exists') = 'true'"!][!//
[!/*[cover parentID={C1EE2273-CE94-41e2-A3BF-162C4D9A833E}][/cover]*/!][!//
#define MCAL_PSPR4_GLOBAL_BASE_ADDR   ([!"num:inttohex(ecu:get('McalLib.PsprCore4StartAddr'))"!]U)
[!ENDIF!][!//
[!IF "ecu:get('Mcu.fCPU5Exists') = 'true'"!][!//
[!/*[cover parentID={D4993593-6B34-4aad-B920-1C6FA5DC9F3F}][/cover]*/!][!//
#define MCAL_PSPR5_GLOBAL_BASE_ADDR   ([!"num:inttohex(ecu:get('McalLib.PsprCore5StartAddr'))"!]U)
[!ENDIF!][!//

/* Global PSPR End address */
[!/*[cover parentID={97C40932-51AF-414f-BC0A-7382AB0BA160}][/cover]*/!][!//
#define MCAL_PSPR0_GLOBAL_END_ADDR   ([!"num:inttohex(ecu:get('McalLib.PsprCore0EndAddr'))"!]U)
[!IF "ecu:get('Mcu.fCPU1Exists') = 'true'"!][!//
[!/*[cover parentID={7095B3C7-87F9-4f1a-84D5-64BA41CB6506}][/cover]*/!][!//
#define MCAL_PSPR1_GLOBAL_END_ADDR   ([!"num:inttohex(ecu:get('McalLib.PsprCore1EndAddr'))"!]U)
[!ENDIF!][!//
[!IF "ecu:get('Mcu.fCPU2Exists') = 'true'"!][!//
[!/*[cover parentID={305886FD-6739-483b-A520-3BC2BAEA1B64}][/cover]*/!][!//
#define MCAL_PSPR2_GLOBAL_END_ADDR   ([!"num:inttohex(ecu:get('McalLib.PsprCore2EndAddr'))"!]U)
[!ENDIF!][!//
[!IF "ecu:get('Mcu.fCPU3Exists') = 'true'"!][!//
[!/*[cover parentID={10B583FB-6854-4d07-AB29-1EFA5F0450F3}][/cover]*/!][!//
#define MCAL_PSPR3_GLOBAL_END_ADDR   ([!"num:inttohex(ecu:get('McalLib.PsprCore3EndAddr'))"!]U)
[!ENDIF!][!//
[!IF "ecu:get('Mcu.fCPU4Exists') = 'true'"!][!//
[!/*[cover parentID={64081E3D-4A32-43cc-A812-C9D7257C9213}][/cover]*/!][!//
#define MCAL_PSPR4_GLOBAL_END_ADDR   ([!"num:inttohex(ecu:get('McalLib.PsprCore4EndAddr'))"!]U)
[!ENDIF!][!//
[!IF "ecu:get('Mcu.fCPU5Exists') = 'true'"!][!//
[!/*[cover parentID={CF8EDF34-2A10-4325-A191-00ADCFA8034F}][/cover]*/!][!//
#define MCAL_PSPR5_GLOBAL_END_ADDR   ([!"num:inttohex(ecu:get('McalLib.PsprCore5EndAddr'))"!]U)
[!ENDIF!][!//

/* Global DSPR base address */
[!/*[cover parentID={283014DF-B436-4233-B9FB-D311BADBD9B0}][/cover]*/!][!//
#define MCAL_DSPR0_GLOBAL_BASE_ADDR    ([!"num:inttohex(ecu:get('McalLib.DsprCore0StartAddr'))"!]U)
[!IF "ecu:get('Mcu.fCPU1Exists') = 'true'"!][!//
[!/*[cover parentID={77C7166A-C4D8-4916-9FD7-0CD3BEFC9116}][/cover]*/!][!//
#define MCAL_DSPR1_GLOBAL_BASE_ADDR    ([!"num:inttohex(ecu:get('McalLib.DsprCore1StartAddr'))"!]U)
[!ENDIF!][!//
[!IF "ecu:get('Mcu.fCPU2Exists') = 'true'"!][!//
[!/*[cover parentID={5BD191A4-4678-4704-AC08-5BC60D6F0CC0}][/cover]*/!][!//
#define MCAL_DSPR2_GLOBAL_BASE_ADDR    ([!"num:inttohex(ecu:get('McalLib.DsprCore2StartAddr'))"!]U)
[!ENDIF!][!//
[!IF "ecu:get('Mcu.fCPU3Exists') = 'true'"!][!//
[!/*[cover parentID={91898296-49FB-4b38-927A-4D8559FA5622}][/cover]*/!][!//
#define MCAL_DSPR3_GLOBAL_BASE_ADDR    ([!"num:inttohex(ecu:get('McalLib.DsprCore3StartAddr'))"!]U)
[!ENDIF!][!//
[!IF "ecu:get('Mcu.fCPU4Exists') = 'true'"!][!//
[!/*[cover parentID={5BD191A4-4678-4704-AC08-5BC60D6F0CC0}][/cover]*/!][!//
#define MCAL_DSPR4_GLOBAL_BASE_ADDR    ([!"num:inttohex(ecu:get('McalLib.DsprCore4StartAddr'))"!]U)
[!ENDIF!][!//
[!IF "ecu:get('Mcu.fCPU5Exists') = 'true'"!][!//
[!/*[cover parentID={14742C4A-0A4C-4305-A3D6-0A91F4EDCE03}][/cover]*/!][!//
#define MCAL_DSPR5_GLOBAL_BASE_ADDR    ([!"num:inttohex(ecu:get('McalLib.DsprCore5StartAddr'))"!]U)
[!ENDIF!][!//

/* Global DSPR End address */
[!/*[cover parentID={AFF6AEC3-1B9A-4d62-ACBC-01B54E78A91B}][/cover]*/!][!//
#define MCAL_DSPR0_GLOBAL_END_ADDR   ([!"num:inttohex(ecu:get('McalLib.DsprCore0EndAddr'))"!]U)
[!IF "ecu:get('Mcu.fCPU1Exists') = 'true'"!][!//
[!/*[cover parentID={053B0237-4617-4dc6-845C-116B25AF40E1}][/cover]*/!][!//
#define MCAL_DSPR1_GLOBAL_END_ADDR   ([!"num:inttohex(ecu:get('McalLib.DsprCore1EndAddr'))"!]U)
[!ENDIF!][!//
[!IF "ecu:get('Mcu.fCPU2Exists') = 'true'"!][!//
[!/*[cover parentID={DA542DF0-E3CA-4e71-8ECB-3E10E58C8A15}][/cover]*/!][!//
#define MCAL_DSPR2_GLOBAL_END_ADDR   ([!"num:inttohex(ecu:get('McalLib.DsprCore2EndAddr'))"!]U)
[!ENDIF!][!//
[!IF "ecu:get('Mcu.fCPU3Exists') = 'true'"!][!//
[!/*[cover parentID={44AB1F62-BA7D-4192-9545-C8C845280C61}][/cover]*/!][!//
#define MCAL_DSPR3_GLOBAL_END_ADDR   ([!"num:inttohex(ecu:get('McalLib.DsprCore3EndAddr'))"!]U)
[!ENDIF!][!//
[!IF "ecu:get('Mcu.fCPU4Exists') = 'true'"!][!//
[!/*[cover parentID={C2303E4F-BBA4-47ac-8DB5-497AB1096C59}][/cover]*/!][!//
#define MCAL_DSPR4_GLOBAL_END_ADDR   ([!"num:inttohex(ecu:get('McalLib.DsprCore4EndAddr'))"!]U)
[!ENDIF!][!//
[!IF "ecu:get('Mcu.fCPU5Exists') = 'true'"!][!//
[!/*[cover parentID={E02DE55D-9BAA-48ff-A546-D23C34D77C88}][/cover]*/!][!//
#define MCAL_DSPR5_GLOBAL_END_ADDR   ([!"num:inttohex(ecu:get('McalLib.DsprCore5EndAddr'))"!]U)
[!ENDIF!][!//

/*
Configuration: MCALLIB_SAFETY_ENABLE:
Compile switch to enable/disable the Safety Enable API
- ON if McalLibSafetyEnable   is true
- OFF if McalLibSafetyEnable   is false
*/
[!/*[cover parentID={C5587013-0247-4b94-8AAD-9472AD0A5A68}][/cover]*/!][!//
[!IF "McalLibGeneral/McalLibSafetyEnable = 'true'"!][!//
#define MCALLIB_SAFETY_ENABLE           (STD_ON)
[!ELSE!][!//
#define  MCALLIB_SAFETY_ENABLE          (STD_OFF)
[!ENDIF!][!//
                                  
/*For retriving the Master Core ID */
[!SELECT "as:modconf('ResourceM')[1]"!][!//
[!/*[cover parentID={D9877FD3-20A0-48a3-9A79-7AFE5287A000}][/cover]*/!][!//
#define MCAL_MASTER_COREID                 ((uint32)[!"substring(node:value(ResourceMMcalConfig/*[1]/ResourceMMasterCore),5,1)"!]U)
[!ENDSELECT!][!//
#endif  /* MCALLIB_CFG_H */

