[!/****************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2016)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Fls_17_Dmu_Cfg.h                                            **
**                                                                           **
**  VERSION :  3.0.0                                                         **
**                                                                           **
**  DATE       :  2018-09-10                                                 **
**                                                                           **
**  VARIANT   : Variant PB                                                   **
**                                                                           **
**  PLATFORM  : Infineon AURIX2G                                             **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION  : Code template for Fls_17_Dmu_Cfg.h file                   **
**                                                                           **
**  SPECIFICATION(S) : Specification of FLS Driver, AUTOSAR Release 4.2.2    **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: No                                      **
**                                                                           **
******************************************************************************/

************************************************************************/!][!//
[!//
/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2016)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Fls_17_Dmu_Cfg.h                                            **
**                                                                           **
**  VERSION :  3.0.0                                                         **
**                                                                           **
**  DATE, TIME: [!"$date"!], [!"$time"!]                                         **
**                                                                           **
**  GENERATOR : Build [!"$buildnr"!]                                           **
**                                                                           **
**  BSW MODULE DECRIPTION : Fls_17_Dmu.bmd                                   **
**                                                                           **
**  VARIANT   : Variant PB                                                   **
**                                                                           **
**  PLATFORM  : Infineon AURIX2G                                             **
**                                                                           **
**  AUTHOR    : DL-AUTOSAR-Engineering                                       **
**                                                                           **
**  VENDOR    : Infineon Technologies                                        **
**                                                                           **
**  DESCRIPTION  : FLS configuration generated out of ECU configuration      **
**                   file                                                    **
**                                                                           **
**  SPECIFICATION(S) : Specification of FLS Driver, AUTOSAR Release 4.2.2    **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: No                                      **
**                                                                           **
******************************************************************************/
/* [cover parentID={E28116AB-67A4-45c7-9E55-89F2E3382919}][/cover] */
/* [cover parentID={1E72E6C2-4107-4551-BFE4-BC613F96086B}][/cover] */
#ifndef FLS_17_DMU_CFG_H 
#define FLS_17_DMU_CFG_H 

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Typedefs Imported from Mem Interface */ 
#include "MemIf_Types.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!VAR "IfxFeeUsed" = "'OFF'"!][!//
[!VAR "IfxFeeNVMUsed" = "'OFF'"!][!//
[!SELECT "as:modconf('Fls')[1]"!][!//
[!IF "FlsGeneral/FlsIfxFeeUse = 'true'"!][!//
[!VAR "IfxFeeUsed" = "'ON'"!][!//
[!ENDIF!][!//
[!//
/*
  Published parameters
*/

/* FLS Instance ID */
#define FLS_17_DMU_INSTANCE_ID                ((uint8)[!"num:i(FlsGeneral/FlsDriverIndex)"!])

#define Fls_17_DmuConf_FlsGeneral_FlsDriverIndex  (FLS_17_DMU_INSTANCE_ID)

[!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
[!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
[!VAR "PatchVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
/* Autosar specification version */
#define FLS_17_DMU_AR_RELEASE_MAJOR_VERSION           ([!"$MajorVersion"!]U)
#define FLS_17_DMU_AR_RELEASE_MINOR_VERSION           ([!"$MinorVersion"!]U)
#define FLS_17_DMU_AR_RELEASE_REVISION_VERSION        ([!"$PatchVersion"!]U)
[!//
[!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
[!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
[!VAR "SwPatchVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//

/* Vendor specific implementation version information */
#define FLS_17_DMU_SW_MAJOR_VERSION           ([!"$SwMajorVersion"!]U)
#define FLS_17_DMU_SW_MINOR_VERSION           ([!"$SwMinorVersion"!]U)
#define FLS_17_DMU_SW_PATCH_VERSION           ([!"$SwPatchVersion"!]U)

/* Total Number of Config Sets */
#define FLS_17_DMU_CONFIG_COUNT               ([!"num:i(count(FlsConfigSet/*))"!]U)

/*
  The following macros will enable or disable a particular feature in FLS 
  module.Set the macro to STD_ON to enable the feature and STD_OFF to 
  disable the same.  
*/
/* Enable/Disable Development error detection(DET)  */
#define FLS_17_DMU_DEV_ERROR_DETECT         ([!//
[!IF "FlsGeneral/FlsDevErrorDetect = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)
/* [cover parentID={63262F83-0F72-4676-8894-C4C00D13204E}][/cover] */
/* Enable/Disable RunTime error detection */
#define FLS_17_DMU_RUNTIME_ERROR_DETECT         ([!//
[!IF "FlsGeneral/FlsRunTimeErrorDetect = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/* [cover parentID={9F1DDCD5-635A-4826-B961-6EC75D5ACDD2}][/cover] */
/* Enable/Disable Safety error detection */
#define FLS_17_DMU_SAFETY_ENABLE         ([!//
[!IF "FlsGeneral/FlsSafetyEnable = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/*Enable/Disable FLS Init Check API*/
#define FLS_17_DMU_INITCHECK_API         ([!//
[!IF "FlsGeneral/FlsInitCheckApi = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)


/* Flash job interrupt mode or polling mode*/
[!IF "$IfxFeeUsed = 'OFF'"!][!//
#define FLS_17_DMU_USE_INTERRUPTS          ([!//
  [!IF "FlsGeneral/FlsUseInterrupts = 'true'"!][!//
STD_ON[!//
  [!ELSE!][!//
STD_OFF[!//
  [!ENDIF!][!//
[!ELSE!][!//
#define FLS_17_DMU_USE_INTERRUPTS          ([!//
STD_OFF[!//
[!ENDIF!][!//
)

/*Fls_cancel api selection*/
#define FLS_17_DMU_CANCEL_API             ([!//
[!IF "FlsGeneral/FlsCancelApi = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/*Fls_SetMode api selection*/
#define FLS_17_DMU_SET_MODE_API             ([!//
[!IF "FlsGeneral/FlsSetModeApi = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/*Fls_compare api selection*/
#define FLS_17_DMU_COMPARE_API            ([!//
[!IF "FlsGeneral/FlsCompareApi = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/*Fls_BlankCheck api selection*/
#define FLS_17_DMU_BLANK_CHECK_API            ([!//
[!IF "FlsGeneral/FlsBlankCheckApi = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/*Fls_GetJobResult api selection*/
#define FLS_17_DMU_GET_JOB_RESULT_API     ([!//
[!IF "FlsGeneral/FlsGetJobResultApi = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/*Fls_GetStatus api selection*/
#define FLS_17_DMU_GET_STATUS_API         ([!//
[!IF "FlsGeneral/FlsGetStatusApi = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/*Fls_GetVersionInfo api selection*/
#define FLS_17_DMU_VERSION_INFO_API   ([!//
[!IF "FlsGeneral/FlsVersionInfoApi = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/*Erase suspend/resume feature selection*/
#define FLS_17_DMU_USE_ERASESUSPEND   ([!//
[!IF "FlsIfxSpecificConfig/FlsUseEraseSuspend = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)


/* [cover parentID={D0A747BC-456D-4353-91D9-A0376EB61DE3}][/cover] */
[!IF "$IfxFeeUsed = 'ON'"!][!//
/* IFX FEE is being used in configuration */
#define FLS_17_DMU_IFX_FEE_USED        (STD_ON)
[!ELSE!][!//
/* IFX FEE is not in use */
#define FLS_17_DMU_IFX_FEE_USED        (STD_OFF)
[!ENDIF!][!//

/*DFLASH base/start address*/
[!VAR "DF0BaseAddress" = "FlsGeneral/FlsBaseAddress"!][!//
#define FLS_17_DMU_BASE_ADDRESS           ([!"num:inttohex($DF0BaseAddress)"!]U)

/*DFLASH total size*/
[!VAR "DF0Size" = "FlsGeneral/FlsTotalSize"!][!//
#define FLS_17_DMU_TOTAL_SIZE             ([!"num:inttohex($DF0Size)"!]U)

[!VAR "SectorPageSize" = "FlsConfigSet/FlsSectorList/*/*/*/FlsPageSize"!][!//
[!IF "$IfxFeeUsed = 'ON'"!][!//
[!SELECT "FlsConfigSet/FlsSectorList/*[1]"!][!//
[!VAR "TotalSectorSize" = "num:i(0)"!][!//
 [!LOOP "FlsSector/*"!][!//
  [!VAR "NumberofSector" = "FlsNumberOfSectors"!][!//
  [!VAR "SectorAddress" = "FlsSectorStartaddress"!][!//
  [!VAR "SectorSize" = "FlsSectorSize"!][!//
  [!IF "$NumberofSector = 2"!][!//
   [!VAR "IfxFeeNVMUsed" = "'ON'"!][!//
/* Start address of the NVM Sector0 */
#define FLS_17_DMU_NVMSECTOR0_STARTADDRESS ([!"num:inttohex($SectorAddress + $DF0BaseAddress)"!]U)

/* Start address of the NVM Sector1 */
#define FLS_17_DMU_NVMSECTOR1_STARTADDRESS ([!"num:inttohex($SectorAddress + $SectorSize + $DF0BaseAddress)"!]U)

/* Size of the 1 NVM sector of the the double sector in bytes*/
#define FLS_17_DMU_NVMSECTOR_SIZE ([!"num:inttohex($SectorSize)"!]U)
  [!VAR "TotalSectorSize" = "num:i($TotalSectorSize + $SectorSize * 2 + $SectorAddress)"!][!//
 [!ELSE!][!//
/* Start address of the Quasi Static Data */
#define FLS_17_DMU_QSDATA_STARTADDRESS ([!"num:inttohex($SectorAddress + $DF0BaseAddress)"!]U)

/* Size of the Quasi static data in bytes*/
#define FLS_17_DMU_QSDATA_SIZE ([!"num:inttohex($SectorSize)"!]U)
   [!VAR "TotalSectorSize" = "num:i($TotalSectorSize + $SectorSize)"!][!//
   [!VAR "AvailableSize" = "num:i($DF0Size - $SectorAddress)"!][!//
    [!IF "$AvailableSize < $SectorSize"!][!//
     [!ERROR!][!//
      Error: Total sizes of the sectors configured is greater than the Total Flash size!
     [!ENDERROR!][!//
	[!ENDIF!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//
[!IF "($TotalSectorSize + $DF0BaseAddress) > ($DF0Size + $DF0BaseAddress)"!][!//
[!ERROR!][!//
 Error: Total sizes of the sectors configured is greater than the Total Flash size!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ELSE!][!//
[!SELECT "FlsConfigSet/FlsSectorList/*[1]"!][!//
[!VAR "TotalSectorSize" = "num:i(0)"!][!//
[!LOOP "FlsSector/*"!][!//
[!VAR "NumberofSector" = "FlsNumberOfSectors"!][!//
[!VAR "SectorAddress" = "FlsSectorStartaddress"!][!//
[!VAR "SectorSize" = "FlsSectorSize"!][!//
[!VAR "NumberofSector" = "FlsNumberOfSectors"!][!//
#define FlsConf_[!"node:name(.)"!]_STARTADDRESS ([!"num:inttohex($SectorAddress + $DF0BaseAddress)"!]U)
[!VAR "EachSectorSize" = "num:i($SectorSize * $NumberofSector)"!][!//
[!VAR "TotalSectorSize" = "num:i($TotalSectorSize + $EachSectorSize)"!][!//
[!VAR "AvailableSize" = "num:i($DF0Size - $SectorAddress)"!][!//
 [!IF "$AvailableSize < $EachSectorSize"!][!//
  [!ERROR!][!//
    Error: Total sizes of the sectors configured is greater than the Total Flash size!
  [!ENDERROR!][!//
 [!ENDIF!][!//
[!ENDLOOP!]
[!IF "($TotalSectorSize + $DF0BaseAddress) > ($DF0Size + $DF0BaseAddress)"!][!//
[!ERROR!][!//
 Error: Total sizes of the sectors configured is greater than the Total Flash size!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDIF!][!//

[!IF "$IfxFeeNVMUsed = 'ON'"!][!//
[!IF "node:exists(FlsConfigSet/FlsSectorList/*/FlsSector/*[2])"!][!//
[!IF "num:i(FlsConfigSet/FlsSectorList/*/FlsSector/*[2]/FlsNumberOfSectors) > num:i(1)"!][!//
[!ERROR!][!//
Error: Ifx Fee is present and has double data sector mode. Max value of FlsNumberOfsectors is '1' for the second sector.
Suggestion: Please correct the value of FlsNumberOfSectors.
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "node:exists(FlsConfigSet/FlsSectorList/*/FlsSector/*[3])"!][!//
[!ERROR!][!//
Error: Ifx Fee has double data sector mode. Third sector configuration is not allowed.
Suggestion: Please remove one sector.
[!ENDERROR!][!//
[!ENDIF!][!//
/* IFX FEE NVM is present in the configuration */
#define FLS_17_DMU_IFX_NVM_PRESENT        (STD_ON)
[!ELSE!][!//
/* IFX FEE NVM is not present in the configuration */
#define FLS_17_DMU_IFX_NVM_PRESENT        (STD_OFF)
[!ENDIF!][!//

/*
Configuration: FLS_INIT_API_MODE
Specifies the operating modes for Fls initialization - SUPERVISOR/ USER1
*/
[!IF "FlsGeneral/FlsInitApiMode = 'FLS_17_DMU_MCAL_SUPERVISOR'"!][!//
#define FLS_17_DMU_INIT_API_MODE                   (FLS_17_DMU_MCAL_SUPERVISOR)
[!ELSE!][!//
[!IF "FlsGeneral/FlsRuntimeApiMode = 'FLS_17_DMU_MCAL_SUPERVISOR'"!][!//
[!ERROR!][!//
Error: If RuntimeApiMode is supervisor mode then InitApiMode should be Supervisor. 
Suggestion: Please change the InitApiMode to supervisor.
[!ENDERROR!][!//
[!ELSE!][!//
#define FLS_17_DMU_INIT_API_MODE                   (FLS_17_DMU_MCAL_USER1)
[!ENDIF!][!//
[!ENDIF!][!//

/*
Configuration: FLS_RUNTIME_API_MODE
Specifies the operating modes for Fls runtime - SUPERVISOR/ USER1
*/
[!IF "FlsGeneral/FlsRuntimeApiMode = 'FLS_17_DMU_MCAL_SUPERVISOR'"!][!//
#define FLS_17_DMU_RUNTIME_API_MODE                 (FLS_17_DMU_MCAL_SUPERVISOR)
[!ELSE!][!//
#define FLS_17_DMU_RUNTIME_API_MODE                 (FLS_17_DMU_MCAL_USER1)
[!ENDIF!][!//

/* Page size of the Data flash is 8 bytes */
#define FLS_17_DMU_PAGE_SIZE            ([!"$SectorPageSize"!]U)

/* erase and write times are published in us (micro seconds) */
[!VAR "EraseTime" = "FlsPublishedInformation/FlsEraseTime"!][!//
#define FLS_17_DMU_ERASE_TIME            ([!"num:i($EraseTime)"!]U)

[!VAR "WriteTime" = "FlsPublishedInformation/FlsWriteTime"!][!//
#define FLS_17_DMU_WRITE_TIME            ([!"num:i($WriteTime)"!]U)

[!VAR "ErasedValue" = "FlsPublishedInformation/FlsErasedValue"!][!//
#define FLS_17_DMU_DEFAULT_ERASEVALUE            ([!"num:i($ErasedValue)"!]U)

/*Timeout for Erase suspend/resume feature*/
#if (FLS_17_DMU_USE_ERASESUSPEND == STD_ON)
#define FLS_17_DMU_ERASESUSPEND_TIMEOUT        ([!"num:inttohex(FlsIfxSpecificConfig/FlsEraseSuspendTimeout)"!]U)
#endif

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
#endif  /* FLS_17_DMU_CFG_H */
[!ENDSELECT!]
