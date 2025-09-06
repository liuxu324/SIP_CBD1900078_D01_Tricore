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
**  FILENAME   : Fee_Cfg.h                                                    **
**                                                                            **
**  VERSION    : 5.0.0                                                        **
**                                                                            **
**  DATE       : 2018-04-25                                                   **
**                                                                            **
**  BSW MODULE DECRIPTION : Fee.bmd                                           **
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
**  DESCRIPTION  : Code template header file for Fee Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Fee Driver, AUTOSAR Release 4.2.2     **
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
**  FILENAME  : Fee_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                                          **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                                            **
**                                                                            **
**  BSW MODULE DECRIPTION : Fee.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Fee configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Fee Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
[!// [cover parentID={1BC43321-A51F-4ae0-B743-77B62934CF51}] [/cover] [!//
#ifndef  FEE_CFG_H
#define  FEE_CFG_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/* Typedefs Imported from Memory Abstract Interface */ 
#include "MemIf_Types.h"

/* Callback functions imported from NvM Module */
#include "NvM_Cbk.h"

[!SELECT "as:modconf('Fee')[1]"!][!//
[!IF "FeeGeneral/FeeBlockTypeConfigured != 'FEE_DOUBLE_SECTOR_DATA_ONLY'"!][!//
/* Callback functions imported from QsM Module */
#include "QsM_Cbk.h"
[!ENDIF!][!//
[!ENDSELECT!][!//

/* Functions imported from Fls Module */
#include "Fls_17_Dmu.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
[!//
[!IF "not(node:exists(as:modconf('Fls')[1]))"!][!//
	[!ERROR!][!//
		error: Fls module not included.
		suggestion: Please include Fls module
	[!ENDERROR!][!//	
[!ENDIF!][!//


[!SELECT "as:modconf('Fee')[1]"!][!//
/* FEE AS version information */
[!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
[!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
[!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
[!VAR "NewString" = "text:replaceAll($moduleReleaseVer,"\.",'')"!][!//
#define FEE_AS_VERSION ([!"$NewString"!])
[!IF "$MajorVersion = num:i(4)"!][!//
#define FEE_AR_RELEASE_MAJOR_VERSION  ([!"$MajorVersion"!]U)
#define FEE_AR_RELEASE_MINOR_VERSION  ([!"$MinorVersion"!]U)
#define FEE_AR_RELEASE_REVISION_VERSION  ([!"$RevisionVersion"!]U)
[!ENDIF!][!//

/* Vendor specific implementation version information */
[!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
[!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
[!VAR "SwPatchVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
#define FEE_SW_MAJOR_VERSION  ([!"$SwMajorVersion"!]U)
#define FEE_SW_MINOR_VERSION  ([!"$SwMinorVersion"!]U)
#define FEE_SW_PATCH_VERSION  ([!"$SwPatchVersion"!]U)

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
                        
/*******************************************************************************
**                    Static configuration parameters                         **
*******************************************************************************/
[!VAR "block_type_configured" = "FeeGeneral/FeeBlockTypeConfigured"!][!//
[!IF "$block_type_configured != 'FEE_QUASI_STATIC_DATA_ONLY'"!][!//
[!// [cover parentID={904C9A47-0D5B-4e14-BE12-797835F83D1E}] [/cover] [!//
/* Development error detection enabled/disabled */
[!IF "FeeGeneral/FeeDevErrorDetect = 'true'"!][!//
#define FEE_DEV_ERROR_DETECT       (STD_ON)
[!ELSE!][!//
#define FEE_DEV_ERROR_DETECT       (STD_OFF)
[!ENDIF!][!//
[!ELSE!][!//
#define FEE_DEV_ERROR_DETECT       (STD_OFF)
[!ENDIF!][!//

/* Enable/Disable Safety error detection and reporting*/
#define FEE_SAFETY_ENABLE         ([!//
[!IF "FeeGeneral/FeeSafetyEnable = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/* Enable/Disable FEE Init Check API*/
#define FEE_INITCHECK_API         ([!//
[!IF "FeeGeneral/FeeInitCheckApi = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/* Fee_GetVersionInfo API enabled/disabled */
[!IF "FeeGeneral/FeeVersionInfoApi = 'true'"!][!//
#define FEE_VERSION_INFO_API       (STD_ON)
[!ELSE!][!//
#define FEE_VERSION_INFO_API       (STD_OFF)
[!ENDIF!][!//

[!// [cover parentID={D7966CED-E453-48cf-9C19-135DCAC2B4CA}] [/cover] [!//
/* Fee_GetCycleCount API enabled/disabled */
[!IF "$block_type_configured != 'FEE_QUASI_STATIC_DATA_ONLY'"!][!//
[!IF "FeeIfxSpecificConfig/FeeGetCycleCountApi = 'true'"!][!//
#define FEE_GET_CYCLE_COUNT_API    (STD_ON)
[!ELSE!][!//
#define FEE_GET_CYCLE_COUNT_API    (STD_OFF)
[!ENDIF!][!//
[!ELSE!][!//
#define FEE_GET_CYCLE_COUNT_API    (STD_OFF)
[!ENDIF!][!//


[!VAR "block_type_configured" = "FeeGeneral/FeeBlockTypeConfigured"!][!//
/* Fee_SetMode API enabled/disabled */
[!IF "FeeGeneral/FeeSetModeSupported = 'true'"!][!//
	[!IF "$block_type_configured != 'FEE_QUASI_STATIC_DATA_ONLY'"!][!//
		[!IF "as:modconf('Fls')/FlsGeneral/FlsSetModeApi = 'true'"!][!//
[!// [cover parentID={15745F43-07FD-474a-8AC4-A630C6C47C17}] [/cover] [!//		
#define FEE_SET_MODE_SUPPORTED     (STD_ON)
		[!ELSE!][!//
			[!ERROR!][!//
				Error: FlsSetModeApi is not enabled in Fls. FeeSetModeSupported setting
					 is dependent on FleSetModeApi.
				suggestion: To enable FeeSetModeSupported, FlsSetModeApi needs to be 
					enabled.
			[!ENDERROR!][!//
		[!ENDIF!][!//
	[!ELSE!][!//
		[!ERROR!][!//
			Error: FeeSetModeSupported is unavailable in FEE_QUASI_STATIC_DATA_ONLY.
			suggestion: FeeBlockTypeConfigured should be FEE_DOUBLE_SECTOR_DATA_ONLY
				OR FEE_DOUBLE_SECTOR_DATA_AND_QUASI_STATIC_DATA 
			if the FeeSetModeSupported needs to be enabled.
		[!ENDERROR!][!//
	[!ENDIF!][!//
[!ELSE!][!//
#define FEE_SET_MODE_SUPPORTED     (STD_OFF)
[!ENDIF!][!//


[!//
[!VAR "CountNvm" = "'0'"!][!//
[!VAR "CountQs" = "'0'"!][!//
[!LOOP "FeeBlockConfiguration/*"!][!//
[!IF "FeeQuasiStaticManager = 'false'"!][!//
[!VAR "CountNvm" = "$CountNvm + '1'"!][!//
[!ELSE!][!//
[!VAR "CountQs" = "$CountQs + '1'"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//

[!IF "$CountQs != '0'"!][!//
#define FEE_QSBLOCK_BEGIN_INDEX ([!"num:i($CountNvm)"!]U)
[!ENDIF!][!//

/* Block type configured */
[!// [cover parentID={7D5AD08D-5A21-4f86-9095-96FF8D19604B}] [/cover] [!//
[!IF "FeeGeneral/FeeBlockTypeConfigured = 'FEE_DOUBLE_SECTOR_DATA_ONLY'"!][!//
[!IF "as:modconf('Fls')/FlsConfigSet/FlsSectorList/*/FlsSector/*[1]/FlsNumberOfSectors = '2' and not(node:exists(as:modconf('Fls')/FlsConfigSet/FlsSectorList/*/FlsSector/*[2]))"!][!//
#define FEE_DATA_BLOCK_SUPPORTED FEE_DOUBLE_SECTOR_DATA_ONLY
[!ELSE!][!//
[!ERROR!][!//
error: Only Double sector is configured in Fee.
suggestion: Check the Fls configuration to change the sectors or change the FeeBlockTypeConfigured.
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "FeeGeneral/FeeBlockTypeConfigured = 'FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA'"!][!//
[!IF "as:modconf('Fls')/FlsConfigSet/FlsSectorList/*/FlsSector/*[1]/FlsNumberOfSectors = '2' and as:modconf('Fls')/FlsConfigSet/FlsSectorList/*/FlsSector/*[2]/FlsNumberOfSectors = '1'"!][!//
#define FEE_DATA_BLOCK_SUPPORTED FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA
[!ELSEIF "as:modconf('Fls')/FlsConfigSet/FlsSectorList/*/FlsSector/*[1]/FlsNumberOfSectors = '1' and as:modconf('Fls')/FlsConfigSet/FlsSectorList/*/FlsSector/*[2]/FlsNumberOfSectors= '2'"!][!//
[!ERROR!][!//
error: In Fls,Sector 0 is to be configured for use as Normal Double Data sector. The number of sectors should be 2 and the second sector should be QS with number of sectors as 1. 
suggestion: Please check the Fls configuration and change the sector details.
[!ENDERROR!][!//
[!ELSE!][!//
[!ERROR!][!//
error: Both QS and Double sector are configured in Fee.
suggestion: Check the Fls configuration or change the FeeBlockTypeConfigured.
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "FeeGeneral/FeeBlockTypeConfigured = 'FEE_QUASI_STATIC_DATA_ONLY'"!][!//
[!IF "as:modconf('Fls')/FlsConfigSet/FlsSectorList/*/FlsSector/*[1]/FlsNumberOfSectors = '1' and not(node:exists(as:modconf('Fls')/FlsConfigSet/FlsSectorList/*/FlsSector/*[2]))"!][!//
#define FEE_DATA_BLOCK_SUPPORTED FEE_QUASI_STATIC_DATA_ONLY
[!ELSE!][!//
[!ERROR!][!//
error: Only QS sector is configured in Fee. 
suggestion: Please check the Fls configuration or change the FeeBlockTypeConfigured.
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//

[!IF "FeeGeneral/FeeBlockTypeConfigured != 'FEE_DOUBLE_SECTOR_DATA_ONLY'"!][!//
[!VAR "Count" = "'0'"!][!//
[!LOOP "FeeBlockConfiguration/*"!][!//
[!IF "FeeQuasiStaticManager != 'false'"!][!//
[!VAR "Count" = "$Count + '1'"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
#define FEE_NUM_QUASI_BLOCKS                ([!"num:i($Count)"!]U)
[!ENDIF!][!//
	
[!// [cover parentID={BB1E9ABC-CE17-46ec-8ED0-3EBBA73CF1EB}] [/cover] [!//
/* Fee_17_GetPrevData API enabled/disabled */
[!IF "FeeGeneral/FeeBlockTypeConfigured != 'FEE_QUASI_STATIC_DATA_ONLY'"!][!//
	[!IF "FeeIfxSpecificConfig/FeeGetPrevDataApi = 'true'"!][!//
#define FEE_GET_PREV_DATA_API      (STD_ON)
	[!ELSE!][!//
#define FEE_GET_PREV_DATA_API      (STD_OFF)
	[!ENDIF!][!//
[!ELSE!][!//
#define FEE_GET_PREV_DATA_API      (STD_OFF)
[!ENDIF!][!//

[!IF "FeeGeneral/FeeBlockTypeConfigured != 'FEE_DOUBLE_SECTOR_DATA_ONLY'"!][!//
[!// [cover parentID={49506EF8-B02F-41a4-8329-808E151834D7}] [/cover] [!//
/* Fee_17_CancelAll  API enabled/disabled */
[!IF "FeeIfxSpecificConfig/FeeCancelAllApi = 'true'"!][!//
[!IF "as:modconf('Fls')/FlsGeneral/FlsCancelApi = 'true'"!][!//
#define FEE_CANCELL_ALL_API      (STD_ON)
[!ELSE!][!//
[!ERROR!][!//
Error: FlsCancelApi is not enabled in Fls. FlsCancelApi should be enabled for 
	Fee_17_CancelAll  API to work.
[!ENDERROR!][!//
[!ENDIF!][!//
[!ELSE!][!//
#define FEE_CANCELL_ALL_API      (STD_OFF)
[!ENDIF!][!//
[!ELSE!][!//
#define FEE_CANCELL_ALL_API      (STD_OFF)
[!ENDIF!][!//

[!IF "FeeIfxSpecificConfig/FeeMaxBytesPerCycle = 'FEE_MAX_BYTES_64'"!][!//
#define FEE_MAX_BYTES_PER_CYCLE      (64U)
[!ELSEIF "FeeIfxSpecificConfig/FeeMaxBytesPerCycle = 'FEE_MAX_BYTES_128'"!][!//
#define FEE_MAX_BYTES_PER_CYCLE      (128U)
[!ELSEIF "FeeIfxSpecificConfig/FeeMaxBytesPerCycle = 'FEE_MAX_BYTES_256'"!][!//
#define FEE_MAX_BYTES_PER_CYCLE      (256U)
[!ELSE!][!//
#define FEE_MAX_BYTES_PER_CYCLE      (512U)
[!ENDIF!][!//
[!IF "FeeIfxSpecificConfig/FeeVirginFlashIllegalState = 'true'"!][!//
[!// [cover parentID={0564563A-23FC-4356-BE23-A878AC5A3361}] [/cover] [!//
/* FEE reaches illegal state upon detection virgin flash */
#define FEE_VIRGIN_FLASH_ILLEGAL_STATE      (STD_ON)
[!ELSE!][!//
/* FEE programs state pages upon detection of virgin flash */
#define FEE_VIRGIN_FLASH_ILLEGAL_STATE      (STD_OFF)
[!ENDIF!][!//

/* Enable/Disable Debug support  */
[!IF "FeeGeneral/FeeDebugSupport = 'true'"!][!//
#define FEE_DEBUG_SUPPORT     (STD_ON)
/* define the state variable for extern declaration in Fee_Dbg.h*/
[!VAR "state_data_struct" = "FeeIfxSpecificConfig/FeeStateVarStructure"!][!//
#define FEE_STATE_VAR       [!"$state_data_struct"!]
[!ELSE!][!//
#define FEE_DEBUG_SUPPORT     (STD_OFF)
[!ENDIF!][!//

/*FeeMainFunctionPeriod value in micro seconds(us)*/
[!VAR "MainFunctionPeriod" = "FeeGeneral/FeeMainFunctionPeriod"!][!//
[!VAR "MainFunctionPeriod" = "$MainFunctionPeriod * 1000 * 1000"!][!//
#define FEE_MAIN_FUNCTION_PERIOD       [!"num:i($MainFunctionPeriod)"!]

[!// [cover parentID={381FA897-186C-427f-8415-C4B09D96D1B1}] [/cover] [!//
[!VAR "useerasesuspend" = "FeeIfxSpecificConfig/FeeUseEraseSuspend"!][!//
/* Erase suspend/resume feature supported in FLS */
[!SELECT "as:modconf('Fls')[1]/FlsIfxSpecificConfig"!][!//
#define FEE_FLS_SUPPORTS_ERASE_SUSPEND  ([!//
[!IF "FlsUseEraseSuspend = 'true' and $useerasesuspend = 'true' "!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)
[!ENDSELECT!][!//

/* DFlash WordLine size */
#define FEE_DFLASH_WORDLINE_SIZE     ([!"num:i(ecu:get('Fee.FlsWordLineSize'))"!]U)

#define FEE_CONTINUE          (0U)
#define FEE_STOP_AT_GC        (1U)

[!// [cover parentID={2380BEA0-E8F6-4864-BCBB-4E325CBF114A}] [/cover] [!//
[!IF "$block_type_configured != 'FEE_QUASI_STATIC_DATA_ONLY'"!][!//
#define FEE_UNCFG_BLK_OVERFLOW_HANDLE    ([!"FeeIfxSpecificConfig/FeeUnConfigBlkOverflowHandle"!])
[!ENDIF!][!//
[!// [cover parentID={D1DF0BB5-52F8-41d6-BCBB-30EDB8FB698A}] [/cover] [!//
/* Virtual page size, i.e., DF_EEPROM page size */
#define FEE_VIRTUAL_PAGE_SIZE      ([!"num:i(FeeGeneral/FeeVirtualPageSize)"!]U)

[!// [cover parentID={5FAA0333-4BBB-4a21-9FF8-812C22A63F12}] [/cover] [!//
/* Logical block's overhead in bytes */
#define FEE_BLOCK_OVERHEAD         ([!"num:i(FeePublishedInformation/FeeBlockOverhead)"!]U)

[!// [cover parentID={EB0AA39C-CD77-4eed-9E64-216866EE3EBD}] [/cover] [!//
/* Logical block's data page overhead in bytes */
#define FEE_PAGE_OVERHEAD          ([!"num:i(FeePublishedInformation/FeePageOverhead)"!]U)

/* Maximum number of configured blocks to be handled */
[!VAR "feemaxblkcnt" = "FeeIfxSpecificConfig/FeeMaxBlockCount"!][!//
[!IF "num:i(count(FeeBlockConfiguration/*)) > $feemaxblkcnt"!][!//
[!WARNING!][!//
More number of blocks are configured than the value specified for FeeMaxBlockCount!
Number of configured blocks: [!"num:i(count(FeeBlockConfiguration/*))"!]
Configured value of FeeMaxBlockCount: [!"$feemaxblkcnt"!]
It is recommended to configure the value of FeeMaxBlockCount appropriately!
[!ENDWARNING!][!//
[!VAR "feemaxblkcnt" = "num:i(count(FeeBlockConfiguration/*))"!][!//
[!ENDIF!][!//
[!SELECT "as:modconf('Fls')[1]/FlsGeneral"!][!//
[!VAR "FeeFlsSectorSize" = "num:i(FlsTotalSize div 2)"!][!//
[!VAR "FeeAllowedNumberOfBlocks" = "num:i((($FeeFlsSectorSize - 1024) div 24) - 10)"!][!//
[!ENDSELECT!][!//
[!IF "$feemaxblkcnt > $FeeAllowedNumberOfBlocks"!][!//
[!ERROR!][!//
Error: Number of Blocks configured is more than the allowed limit ([!"$FeeAllowedNumberOfBlocks"!]).
Maximum number of blocks that can be configured depends on the configured value of FlsTotalSize in FLS driver.
[!ENDERROR!][!//
[!ENDIF!][!//
[!// [cover parentID={08D2BC6F-77BF-4a51-ACBC-A9984DA0670D}] [/cover] [!//
#define FEE_MAX_BLOCK_COUNT        ([!"num:i($feemaxblkcnt)"!]U)

/* Symbolic names of logical blocks */
[!LOOP "FeeBlockConfiguration/*"!][!//
[!VAR "SymbolicName" = "node:name(.)"!][!//
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap Macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
#ifdef FeeConf_FeeBlockConfiguration_[!"$SymbolicName"!] 
/* to prevent double declaration */
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap Macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
#error FeeConf_FeeBlockConfiguration_[!"$SymbolicName"!] already defined
#else 
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap Macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
#define FeeConf_FeeBlockConfiguration_[!"$SymbolicName"!] ((uint16)[!"(num:i(./FeeBlockNumber))"!])
#endif /* #ifdef FeeConf_FeeBlockConfiguration_[!"$SymbolicName"!] */

[!ENDLOOP!][!//

#define FEE_DISABLE_DEM_REPORT   (0U)
#define FEE_ENABLE_DEM_REPORT    (1U)

[!VAR "FeeDemEnabled" = "num:i(0)"!][!//
/* DEM Configurations */
[!IF "node:exists(FeeDemEventParameterRefs/*[1])"!][!//
[!SELECT "FeeDemEventParameterRefs/*[1]"!][!//
[!IF "(node:refexists(./FEE_E_GC_INIT/*[1]) = 'true') and (node:value(./FEE_E_GC_INIT/*[1]) != ' ' )"!][!//
[!VAR "FeeDemEnabled" = "num:i(1)"!][!//
[!// [cover parentID={FA8C6115-BD2C-4775-A427-2D75F0CCAF6B}] [/cover] [!//
#define FEE_GC_INIT_DEM_REPORT       (FEE_ENABLE_DEM_REPORT)
#define FEE_E_GC_INIT                (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./FEE_E_GC_INIT/*[1])))"!])
[!ELSE!][!//
#define FEE_GC_INIT_DEM_REPORT       (FEE_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!IF "(node:refexists(./FEE_E_WRITE/*[1]) = 'true') and (node:value(./FEE_E_WRITE/*[1]) != ' ' )"!][!//
[!VAR "FeeDemEnabled" = "num:i(1)"!][!//
[!// [cover parentID={530FC327-EC9D-4133-8D57-EB5D77B2F64E}] [/cover] [!//
#define FEE_WRITE_DEM_REPORT         (FEE_ENABLE_DEM_REPORT)
#define FEE_E_WRITE                  (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./FEE_E_WRITE/*[1])))"!])
[!ELSE!][!//
#define FEE_WRITE_DEM_REPORT         (FEE_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!IF "(node:refexists(./FEE_E_READ/*[1]) = 'true') and (node:value(./FEE_E_READ/*[1]) != ' ' )"!][!//
[!VAR "FeeDemEnabled" = "num:i(1)"!][!//
[!// [cover parentID={420907A9-2FEB-42de-AF28-5F649B9F942F}] [/cover] [!//
#define FEE_READ_DEM_REPORT          (FEE_ENABLE_DEM_REPORT)
#define FEE_E_READ                   (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./FEE_E_READ/*[1])))"!])
[!ELSE!][!//
#define FEE_READ_DEM_REPORT          (FEE_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!IF "(node:refexists(./FEE_E_GC_WRITE/*[1]) = 'true') and (node:value(./FEE_E_GC_WRITE/*[1]) != ' ' )"!][!//
[!VAR "FeeDemEnabled" = "num:i(1)"!][!//
[!// [cover parentID={7E6E9628-E970-4482-8567-D85D184362E6}] [/cover] [!//
#define FEE_GC_WRITE_DEM_REPORT      (FEE_ENABLE_DEM_REPORT)
#define FEE_E_GC_WRITE               (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./FEE_E_GC_WRITE/*[1])))"!])
[!ELSE!][!//
#define FEE_GC_WRITE_DEM_REPORT      (FEE_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!IF "(node:refexists(./FEE_E_GC_READ/*[1]) = 'true') and (node:value(./FEE_E_GC_READ/*[1]) != ' ' )"!][!//
[!VAR "FeeDemEnabled" = "num:i(1)"!][!//
[!// [cover parentID={B2214E59-C990-4898-A784-219B538B5F18}] [/cover] [!//
#define FEE_GC_READ_DEM_REPORT       (FEE_ENABLE_DEM_REPORT)
#define FEE_E_GC_READ                (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./FEE_E_GC_READ/*[1])))"!])
[!ELSE!][!//
#define FEE_GC_READ_DEM_REPORT       (FEE_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!IF "(node:refexists(./FEE_E_GC_ERASE/*[1]) = 'true') and (node:value(./FEE_E_GC_ERASE/*[1]) != ' ' )"!][!//
[!VAR "FeeDemEnabled" = "num:i(1)"!][!//
[!// [cover parentID={794CB95F-1592-4bc0-B74C-FE92B0998372}] [/cover] [!//
#define FEE_GC_ERASE_DEM_REPORT      (FEE_ENABLE_DEM_REPORT)
#define FEE_E_GC_ERASE               (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./FEE_E_GC_ERASE/*[1])))"!])
[!ELSE!][!//
#define FEE_GC_ERASE_DEM_REPORT      (FEE_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!IF "(node:refexists(./FEE_E_INVALIDATE/*[1]) = 'true') and (node:value(./FEE_E_INVALIDATE/*[1]) != ' ' )"!][!//
[!VAR "FeeDemEnabled" = "num:i(1)"!][!//
[!// [cover parentID={72E8A9AA-0B0D-4bdf-9C4D-EA5289C8B2C8}] [/cover] [!//
#define FEE_INVALIDATE_DEM_REPORT    (FEE_ENABLE_DEM_REPORT)
#define FEE_E_INVALIDATE             (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./FEE_E_INVALIDATE/*[1])))"!])
[!ELSE!][!//
#define FEE_INVALIDATE_DEM_REPORT    (FEE_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!IF "(node:refexists(./FEE_E_WRITE_CYCLES_EXHAUSTED/*[1]) = 'true') and (node:value(./FEE_E_WRITE_CYCLES_EXHAUSTED/*[1]) != ' ' )"!][!//
[!VAR "FeeDemEnabled" = "num:i(1)"!][!//
[!// [cover parentID={64920942-30E1-4cd4-B51E-B67952E4ED6C}] [/cover] [!//
#define FEE_WRITE_CYCLES_DEM_REPORT  (FEE_ENABLE_DEM_REPORT)
#define FEE_E_WRITE_CYCLES_EXHAUSTED (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./FEE_E_WRITE_CYCLES_EXHAUSTED/*[1])))"!])
[!ELSE!][!//
#define FEE_WRITE_CYCLES_DEM_REPORT  (FEE_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!IF "(node:refexists(./FEE_E_GC_TRIG/*[1]) = 'true') and (node:value(./FEE_E_GC_TRIG/*[1]) != ' ' )"!][!//
[!VAR "FeeDemEnabled" = "num:i(1)"!][!//
[!// [cover parentID={0DD5F17B-3844-4d7c-ABEB-340AAA161BCA}] [/cover] [!//
#define FEE_GC_TRIG_DEM_REPORT       (FEE_ENABLE_DEM_REPORT)
#define FEE_E_GC_TRIG                (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./FEE_E_GC_TRIG/*[1])))"!])
[!ELSE!][!//
#define FEE_GC_TRIG_DEM_REPORT       (FEE_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!IF "(node:refexists(./FEE_E_UNCONFIG_BLK_EXCEEDED/*[1]) = 'true') and (node:value(./FEE_E_UNCONFIG_BLK_EXCEEDED/*[1]) != ' ' )"!][!//
[!VAR "FeeDemEnabled" = "num:i(1)"!][!//
#define FEE_UNCFG_BLK_DEM_REPORT     (FEE_ENABLE_DEM_REPORT)
#define FEE_E_UNCONFIG_BLK_EXCEEDED  (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./FEE_E_UNCONFIG_BLK_EXCEEDED/*[1])))"!])
[!ELSE!][!//
#define FEE_UNCFG_BLK_DEM_REPORT     (FEE_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ELSE!][!//
#define FEE_GC_INIT_DEM_REPORT       (FEE_DISABLE_DEM_REPORT)
#define FEE_WRITE_DEM_REPORT         (FEE_DISABLE_DEM_REPORT)
#define FEE_READ_DEM_REPORT          (FEE_DISABLE_DEM_REPORT)
#define FEE_GC_WRITE_DEM_REPORT      (FEE_DISABLE_DEM_REPORT)
#define FEE_GC_READ_DEM_REPORT       (FEE_DISABLE_DEM_REPORT)
#define FEE_GC_ERASE_DEM_REPORT      (FEE_DISABLE_DEM_REPORT)
#define FEE_INVALIDATE_DEM_REPORT    (FEE_DISABLE_DEM_REPORT)
#define FEE_WRITE_CYCLES_DEM_REPORT  (FEE_DISABLE_DEM_REPORT)
#define FEE_GC_TRIG_DEM_REPORT       (FEE_DISABLE_DEM_REPORT)
[!// [cover parentID={4565B6A8-6CBA-47ea-B22E-1D1E7F1AA06E}] [/cover] [!//
#define FEE_UNCFG_BLK_DEM_REPORT     (FEE_DISABLE_DEM_REPORT)
[!ENDIF!][!//

[!IF "$block_type_configured != 'FEE_QUASI_STATIC_DATA_ONLY'"!][!//
[!IF "$FeeDemEnabled = num:i(1)"!][!//
#define FEE_DEM_ENABLED              (STD_ON)
[!ELSE!][!//
#define FEE_DEM_ENABLED              (STD_OFF)
[!ENDIF!][!//
[!ELSE!][!//
#define FEE_DEM_ENABLED              (STD_OFF)
[!ENDIF!][!//
[!ENDSELECT!][!//

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/


/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

#endif /* #ifndef FEE_CFG_H */
