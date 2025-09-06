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
**  FILENAME   : Fee_PBCfg.c                                                  **
**                                                                            **
**  VERSION    : 5.0.0                                                        **
**                                                                            **
**  DATE       : 2018-09-25                                                   **
**                                                                            **
**  BSW MODULE DECRIPTION : Fee.bmd                                           **
**                                                                            **
**  VARIANT    : Variant PB                                                   **
**                                                                            **
**  PLATFORM   : Infineon AURIX2G                                             **
**                                                                            **
**  AUTHOR     : DL-AUTOSAR-Engineering                                       **
**                                                                            **
**  VENDOR     : Infineon Technologies                                        **
**                                                                            **
**  TRACEABILITY : [cover parentID]                                           **
**                                                                            **
**  DESCRIPTION  : Code template source file for Fee Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Fee Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
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
**  FILENAME    : Fee_PBCfg.c                                                 **
**                                                                            **
**  VERSION     : 5.0.0                                                       **
**                                                                            **
**  DATE, TIME  : [!"$date"!], [!"$time"!]                                        **
**                                                                            **
**  GENERATOR   : Build [!"$buildnr"!]                                          **
**                                                                            **
**  BSW MODULE DECRIPTION : Fee.bmd                                           **
**                                                                            **
**  VARIANT     : Variant PB                                                  **
**                                                                            **
**  PLATFORM    : Infineon AURIX2G                                            **
**                                                                            **
**  AUTHOR      : DL-AUTOSAR-Engineering                                      **
**                                                                            **
**  VENDOR      : Infineon Technologies                                       **
**                                                                            **
**  DESCRIPTION :  Fee configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Fee Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
[!// [cover parentID={A6EB1EA0-D78E-40c5-AFB1-4153EF897348}]Fee_PBcfg.c [/cover] [!//
[!// [cover parentID={F140A62A-46A0-44c9-91F3-5E75994EC8CF}]Code generator dependency [/cover] [!//
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/* Include Fee Module Header File */
#include "Fee.h"
[!VAR "FeeVariantName" ="'Config'"!][!//
[!SELECT "as:modconf('EcuC')[1]"!][!//
[!IF "node:exists(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!][!//
  [!VAR "PredefinedVarName" = "(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!][!//
  [!VAR "FeeVariantName" = "text:split($PredefinedVarName,'/')[4]"!][!//
  [!VAR "FeeVariantName" = "concat('Config_',$FeeVariantName)"!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Fee')[1]"!][!//
/*******************************************************************************
**                      Imported Compiler Switch Checks                       **
*******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
[!//
[!IF "FeeGeneral/FeeBlockTypeConfigured != 'FEE_QUASI_STATIC_DATA_ONLY'"!][!//
  [!IF "node:exists(FeeGeneral/FeeNvmJobEndNotification/*[1])"!][!//
    [!VAR "jobend" = "FeeGeneral/FeeNvmJobEndNotification/*[1]"!][!//
  [!ELSE!][!//
    [!VAR "jobend" = "'NULL_PTR'"!][!//
  [!ENDIF!][!//
  [!IF "node:exists(FeeGeneral/FeeNvmJobErrorNotification/*[1])"!][!//
    [!VAR "joberror" = "FeeGeneral/FeeNvmJobErrorNotification/*[1]"!][!//
  [!ELSE!][!//
    [!VAR "joberror" = "'NULL_PTR'"!][!//
  [!ENDIF!][!//
[!ELSE!][!//
  [!VAR "jobend" = "'NULL_PTR'"!][!//
  [!VAR "joberror" = "'NULL_PTR'"!][!//
[!ENDIF!][!//
[!IF "FeeGeneral/FeeBlockTypeConfigured != 'FEE_DOUBLE_SECTOR_DATA_ONLY'"!][!//
  [!IF "node:exists(FeeGeneral/FeeQsJobEndNotification/*[1])"!][!//
    [!VAR "qsjobend" = "FeeGeneral/FeeQsJobEndNotification/*[1]"!][!//
  [!ELSE!][!//
    [!VAR "qsjobend" = "'NULL_PTR'"!][!//
  [!ENDIF!][!//
  [!IF "node:exists(FeeGeneral/FeeQsJobErrorNotification/*[1])"!][!//
    [!VAR "qsjoberror" = "FeeGeneral/FeeQsJobErrorNotification/*[1]"!][!//
  [!ELSE!][!//
    [!VAR "qsjoberror" = "'NULL_PTR'"!][!//
  [!ENDIF!][!//
[!ELSE!][!//
  [!VAR "qsjobend" = "'NULL_PTR'"!][!//
  [!VAR "qsjoberror" = "'NULL_PTR'"!][!//
[!ENDIF!][!//

[!//
[!IF "num:isnumber($jobend) != 'true'"!][!//
[!IF "$jobend != 'NvM_JobEndNotification'"!][!//
[!IF "$jobend != 'NULL_PTR'"!][!//
[!IF "$jobend != ''"!][!//
[!IF "$jobend != '""'"!][!//

/* Job End Notification Function */
extern void [!"$jobend"!](void);
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "num:isnumber($joberror) != 'true'"!][!//
[!IF "$joberror != 'NvM_JobErrorNotification'"!][!//
[!IF "$joberror != 'NULL_PTR'"!][!//
[!IF "$joberror != ''"!][!//
[!IF "$joberror != '""'"!][!//
/* Job Error Notification Function */
extern void [!"$joberror"!](void);
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!//
[!IF "num:isnumber($qsjobend) != 'true'"!][!//
[!IF "$qsjobend != 'NULL_PTR'"!][!//
[!IF "$qsjobend != ''"!][!//
[!IF "$qsjobend != '""'"!][!//
/* Job End Notification Function */
extern void [!"$qsjobend"!](void);
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "num:isnumber($qsjoberror) != 'true'"!][!//
[!IF "$qsjoberror != 'NULL_PTR'"!][!//
[!IF "$qsjoberror != ''"!][!//
[!IF "$qsjoberror != '""'"!][!//
/* Job Error Notification Function */
extern void [!"$qsjoberror"!](void);
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//

[!VAR "illegalnvmnotif" = "FeeIfxSpecificConfig/FeeNvmIllegalStateNotification"!][!//
[!IF "$illegalnvmnotif != 'NULL_PTR'"!][!//
[!IF "$illegalnvmnotif != ''"!][!//
[!IF "$illegalnvmnotif != '""'"!][!//
/* Fee NVM Illegal State Notification Function */
extern void [!"$illegalnvmnotif"!](void);
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//

[!VAR "illegalqsnotif" = "FeeIfxSpecificConfig/FeeQsIllegalStateNotification"!][!//
[!IF "$illegalqsnotif != 'NULL_PTR'"!][!//
[!IF "$illegalqsnotif != ''"!][!//
[!IF "$illegalqsnotif != '""'"!][!//
/* Fee QS Illegal State Notification Function */
extern void [!"$illegalqsnotif"!](void);
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//

[!VAR "HardenErrNotif" = "FeeIfxSpecificConfig/FeeQsHardenErrorNotification"!][!//
[!IF "$HardenErrNotif != 'NULL_PTR'"!][!//
[!IF "$HardenErrNotif != ''"!][!//
[!IF "$HardenErrNotif != '""'"!][!//
/* QS Hardeining Error Notification Function */
extern void [!"$HardenErrNotif"!](void);
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
[!//
[!NOCODE!][!//
  [!VAR "CountNvm" = "'0'"!][!//
  [!VAR "CountQs" = "'0'"!][!//
  [!LOOP "FeeBlockConfiguration/*"!][!//
  [!IF "FeeQuasiStaticManager = 'false'"!][!//
  [!VAR "CountNvm" = "$CountNvm + '1'"!][!//
  [!ELSE!][!//
  [!VAR "CountQs" = "$CountQs + '1'"!][!//
  [!ENDIF!][!//
  [!ENDLOOP!][!//   

  [!/*QS Block Address overlap with NVM sector*/!][!//
  [!//
  [!VAR "block_type_configured" = "FeeGeneral/FeeBlockTypeConfigured"!][!//
  [!IF "$block_type_configured = 'FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA'"!][!//
  [!LOOP "FeeBlockConfiguration/*"!][!//
  [!IF "FeeQuasiStaticManager = 'true'"!][!//
  [!IF "num:i(FeeQsBlockAddress) < num:i(num:i(as:modconf('Fls')/FlsConfigSet/FlsSectorList/*/FlsSector/*[1]/FlsSectorSize) * 2)"!][!//
  [!ERROR!][!//
  Error: Fee QsblockAddress overlaps with the NVM sector address
  Suggestion: Please correct the Qs block address
  [!ENDERROR!][!//
  [!ENDIF!][!//
  [!ENDIF!][!//
  [!ENDLOOP!][!//
  [!ENDIF!][!//

  [!//
  [!VAR "CountQsSize" = "'0'"!][!//
  [!VAR "CountQsSizeAddress" = "'0'"!][!//
  [!VAR "block_type_configured" = "FeeGeneral/FeeBlockTypeConfigured"!][!//
  [!IF "$block_type_configured = 'FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA' or $block_type_configured = 'FEE_QUASI_STATIC_DATA_ONLY'"!][!//
  [!LOOP "FeeBlockConfiguration/*"!][!//
  [!IF "FeeQuasiStaticManager = 'true'"!][!//     
  [!VAR "CountQsSizeAddress" = "$CountQsSizeAddress + (num:i(FeeBlockSize) * num:i(FeeQsBlockInstances))"!][!//
  [!ENDIF!][!//
  [!ENDLOOP!][!//
  [!ENDIF!][!//
  [!IF "$block_type_configured = 'FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA'"!][!//
  [!IF "num:i($CountQsSizeAddress) > num:i(as:modconf('Fls')/FlsConfigSet/FlsSectorList/*/FlsSector/*[2]/FlsSectorSize)"!][!//
  [!ERROR!][!//
    Error: Total of Fee QS block size is more than the QS sector size
    Suggestion: Please correct the QS block size or increase the QS sector size
  [!ENDERROR!][!//
  [!ENDIF!][!//
  [!ELSEIF "$block_type_configured = 'FEE_QUASI_STATIC_DATA_ONLY'"!][!//
  [!IF "num:i($CountQsSizeAddress) > num:i(as:modconf('Fls')/FlsConfigSet/FlsSectorList/*/FlsSector/*[1]/FlsSectorSize)"!][!//
  [!ERROR!][!//
    Error: Total of Fee QS block size is more than the QS sector size
    Suggestion: Please correct the QS block size or increase the QS sector size
  [!ENDERROR!][!//
  [!ENDIF!][!//
  [!ENDIF!][!//

  [!/*Check for the QS block address & size overflows the FLS*/!][!//
  [!//
  [!VAR "block_type_configured" = "FeeGeneral/FeeBlockTypeConfigured"!][!//
  [!IF "$block_type_configured = 'FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA' or $block_type_configured = 'FEE_QUASI_STATIC_DATA_ONLY'"!][!//
  [!LOOP "FeeBlockConfiguration/*"!][!//
  [!IF "FeeQuasiStaticManager = 'true'"!][!//     
  [!IF "(num:i(FeeBlockSize) + num:i(FeeQsBlockAddress)) > num:i(as:modconf('Fls')/FlsGeneral/FlsTotalSize)"!][!//
  [!ERROR!][!//
    Error: Total of Fee QS block size or address is configured incorrectly, it overflows the FLS boundary
    Suggestion: Please correct the QS block size or increase the QS sector size
  [!ENDERROR!][!//
  [!ENDIF!][!//
  [!ENDIF!][!//
  [!ENDLOOP!][!//
  [!ENDIF!][!//

  [!//
  [!VAR "temp_count" = "'0'"!][!//
  [!VAR "state_data_struct" = "FeeIfxSpecificConfig/FeeStateVarStructure"!][!//
  [!VAR "block_type_configured" = "FeeGeneral/FeeBlockTypeConfigured"!][!//
  [!IF "$block_type_configured = 'FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA'"!][!//
  [!IF "$CountQs = '0'"!][!//
  [!ERROR!][!//
  Error: FeeBlockTypeConfigured is wrong. FeeBlockTypeConfigured is 
    FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA but no quasi Static data block 
    configured
  suggestion : FeeBlockTypeConfigured to be made as FEE_DOUBLE_SECTOR_DATA_ONLY.
  [!ENDERROR!][!//
  [!ENDIF!][!//
  [!ENDIF!][!//

  [!IF "$block_type_configured = 'FEE_QUASI_STATIC_DATA_ONLY'"!][!//
  [!IF "$CountNvm != '0'"!][!//
  [!ERROR!][!//
  Error: FeeBlockTypeConfigured is wrong. FeeBlockTypeConfigured is 
    FEE_QUASI_STATIC_DATA_ONLY but NVM data block configured
  suggestion : FeeBlockTypeConfigured to be made as 
    FEE_DOUBLE_SECTOR_DATA_AND_QUASI_STATIC_DATA.
  [!ENDERROR!][!//
  [!ENDIF!][!//
  [!ENDIF!][!//

  [!IF "$block_type_configured = 'FEE_DOUBLE_SECTOR_DATA_ONLY'"!][!//
  [!IF "$CountQs != '0'"!][!//
  [!ERROR!][!//
  Error: FeeBlockTypeConfigured is wrong. FeeBlockTypeConfigured is 
    FEE_DOUBLE_SECTOR_DATA_ONLY but quasi Static data block configured
  suggestion : quasi Static data block should be removed..
  [!ENDERROR!][!//
  [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDNOCODE!][!//
/* Allocate space for state data variables in RAM */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap Macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
#define FEE_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"

/* Fee State Variable structure */
/*MISRA2012_RULE_8_7_JUSTIFICATION: Fee_StateVar has not been declared as static
as this structure is being passed to the Fee.c file. It has scope beyond the 
file.*/
/*MISRA2012_RULE_8_4_JUSTIFICATION: MISRA is assuming as a function but it 
branches out as assembly equivalent or compiler routine..*/
Fee_StateDataType [!"$state_data_struct"!];
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap Macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
#define FEE_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"

[!SELECT "as:modconf('Fls')[1]/FlsGeneral"!][!//
[!VAR "FeeFlsSectorSize" = "num:i(FlsTotalSize div 2)"!][!//
[!VAR "FeeAllowedBlockSize" = "num:i((($FeeFlsSectorSize - 1024 - 16) * 7) div 8)"!][!//
[!IF "$FeeAllowedBlockSize > 65535"!][!//
[!VAR "FeeAllowedBlockSize" = "num:i(65535)"!][!//
[!ENDIF!][!//
[!VAR "FeeAllowedThresholdSize" = "num:i($FeeFlsSectorSize - 1024 - 24)"!][!//
[!ENDSELECT!][!//


/* User configured logical block initialization structure */
#define FEE_START_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"
/*[cover parentID={01870B59-CB19-45ea-8F7F-F16AC029FB7A}][/cover]*/ 
[!IF "$CountNvm + $CountQs > 1"!][!//
static const Fee_BlockType Fee_Block[!"$FeeVariantName"!][] =
[!ELSE!][!//
static const Fee_BlockType Fee_Block[!"$FeeVariantName"!][] =
[!ENDIF!][!//
{[!LOOP "FeeBlockConfiguration/*"!][!//
[!IF "$CountNvm > '0'"!][!//    
[!IF "FeeQuasiStaticManager = 'false'"!][!//
  {
[!VAR "imm" = "FeeImmediateData"!][!//
[!VAR "blk_num" = "FeeBlockNumber"!][!//
[!VAR "blk_size" = "FeeBlockSize"!][!//
[!IF "$block_type_configured != 'FEE_DOUBLE_SECTOR_DATA_ONLY'"!][!//
[!VAR "blk_address" = "'0x00'"!][!//
[!VAR "blk_instance" = "'0'"!][!//
[!VAR "blk_user" = "'FEE_NVM_USER'"!][!//
[!ENDIF!][!//
[!IF "$blk_size > $FeeAllowedBlockSize"!][!//
[!ERROR!][!//
Error: Block size should not exceed the allowed limit ([!"$FeeAllowedBlockSize"!]).
Maximum block size that can be configured depends on the configured value of 
FlsTotalSize in FLS driver.
[!ENDERROR!][!//
[!ENDIF!][!//
[!IF "$block_type_configured != 'FEE_QUASI_STATIC_DATA_ONLY'"!][!//
[!VAR "blk_cycle_count" = "FeeNumberOfWriteCycles"!][!//
  [!IF "$imm = 'true'"!][!//
  [!"$blk_cycle_count"!]U, /* Block Cycle Count */
    (uint8)FEE_IMMEDIATE_DATA,  /* Block type is Immediate */
  [!ELSE!][!//
  [!"$blk_cycle_count"!]U, /* Block Cycle Count */
    (uint8)FEE_NORMAL_DATA,     /* Block type is Normal */
  [!ENDIF!][!//
[!ELSE!][!//
  [!VAR "blk_cycle_count" = "'0'"!][!//
    (uint8)FEE_NORMAL_DATA,     /* Block type is Normal */
[!ENDIF!][!//
    [!"$blk_num"!]U, /* Block number */
    [!"$blk_size"!]U, /* Fee Block Size */
[!IF "$block_type_configured != 'FEE_DOUBLE_SECTOR_DATA_ONLY'"!][!//
    [!"$blk_address"!]U, /* Fee Block address */
    [!"$blk_instance"!]U, /* Fee Block instance */
    [!"$blk_user"!] /* Fee quasi/NVM manager */
[!ENDIF!][!//    
[!VAR "temp_count" = "$temp_count + '1'"!][!//
/*MISRA2012_RULE_10_3_JUSTIFICATION: Exception MISRA 10_3 is not applicable 
to the initializer {0} which may be used to initialize an aggregate. 
Here it is defined as enum and first element initialized to 0.
*/
  },
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//

[!IF "$block_type_configured != 'FEE_DOUBLE_SECTOR_DATA_ONLY'"!][!//
[!VAR "temp_count" = "'0'"!][!//
[!IF "$CountQs != '0'"!][!//
[!LOOP "FeeBlockConfiguration/*"!][!//
[!IF "FeeQuasiStaticManager != 'false'"!][!//
  { 
[!VAR "imm" = "FeeImmediateData"!][!//
[!VAR "blk_num" = "FeeBlockNumber"!][!//
[!VAR "blk_size" = "FeeBlockSize"!][!//
[!VAR "blk_address" = "FeeQsBlockAddress"!][!//
[!VAR "blk_instance" = "FeeQsBlockInstances"!][!//
[!VAR "blk_user" = "'FEE_QUASI_STATIC_USER'"!][!//
[!IF "$blk_size > $FeeAllowedBlockSize"!][!//
[!ERROR!][!//
Error: Block size should not exceed the allowed limit ([!"$FeeAllowedBlockSize"!]).
Maximum block size that can be configured depends on the configured value of 
FlsTotalSize in FLS driver.
[!ENDERROR!][!//
[!ENDIF!][!//
[!IF "$block_type_configured != 'FEE_QUASI_STATIC_DATA_ONLY'"!][!//
  [!VAR "blk_cycle_count" = "FeeNumberOfWriteCycles"!][!//
[!ELSE!][!//
  [!VAR "blk_cycle_count" = "'0'"!][!//
[!ENDIF!][!//
    [!"$blk_cycle_count"!]U, /* Block Cycle Count */
    (uint8)FEE_NORMAL_DATA,     /* Block type is Normal */
    [!"$blk_num"!]U, /* Block number */
    [!"$blk_size"!]U, /* Fee Block Size */
    [!"$blk_address"!]U, /* Fee Block address */
    [!"$blk_instance"!]U, /* Fee Block instance */
    [!"$blk_user"!] /* Fee quasi manager */
[!VAR "temp_count" = "$temp_count + '1'"!][!//
/*MISRA2012_RULE_10_3_JUSTIFICATION: Exception MISRA 10_3 is not applicable 
to the initializer {0} which may be used to initialize an aggregate. 
Here it is defined as enum and first element initialized to 0.
*/
  },
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!ENDIF!][!//
};

[!VAR "unconfig" = "FeeIfxSpecificConfig/FeeUnConfigBlock"!][!//
[!VAR "useerasesuspend" = "FeeIfxSpecificConfig/FeeUseEraseSuspend"!][!//
[!SELECT "as:modconf('Fls')[1]/FlsIfxSpecificConfig"!][!//
[!IF "FlsUseEraseSuspend = 'false'"!][!//
[!IF "$useerasesuspend = 'true'"!][!//
[!ERROR!][!//
Error: Flash (FLS driver) should support erase suspend/resume feature!
Check the configuration parameter FlsUseEraseSuspend in FLS module.
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!VAR "eraseallenable" = "FeeIfxSpecificConfig/FeeEraseAllEnable"!][!//
[!VAR "gc_restart" = "FeeIfxSpecificConfig/FeeGcRestart"!][!//
[!VAR "threshold" = "FeeIfxSpecificConfig/FeeThresholdValue"!][!//
[!IF "$threshold > $FeeAllowedThresholdSize"!][!//
[!ERROR!][!//
Error: Configured value of FeeThresholdValue is more than the allowed limit 
  ([!"$FeeAllowedThresholdSize"!]).
Maximum allowed value of FeeThresholdValue depends on the configured value of 
FlsTotalSize in FLS driver.
[!ENDERROR!][!//
[!ENDIF!][!//
/* MISRA2012_RULE_8_7_JUSTIFICATION: External linkage is needed as it is used 
     in more than one translation unit. */
/* MISRA2012_RULE_8_4_JUSTIFICATION: Defined as per AUTOSAR */
/* Fee Global initialization structure. */
const Fee_ConfigType Fee_[!"$FeeVariantName"!] =
{
  
    /* Fee State Data Structure */
    &[!"$state_data_struct"!],
    /* Pointer to logical block configurations */
[!IF "$CountNvm + $CountQs > 1"!][!//
    &Fee_Block[!"$FeeVariantName"!][0],
[!ELSE!][!//
    &Fee_Block[!"$FeeVariantName"!][0],
[!ENDIF!][!//
[!IF "num:isnumber($jobend) != 'true'"!][!//
[!IF "$jobend = '""' or $jobend = '' or $jobend = 'NULL_PTR'"!][!//
/*MISRA2012_RULE_11_3_JUSTIFICATION:  The warning is coming for NULL_PTR defined by 
AUTOSAR. The function pointer is being allocated NULL_PTR as the particular 
function will not be required. The function is correctly getting assigned to NULL VALUE*/
[!VAR "jobend" = "'(Fee_NotifFunctionPtrType)NULL_PTR'"!][!//
[!ELSE!][!//
[!VAR "jobend" = "concat('&',$jobend)"!][!//
[!ENDIF!][!//
[!ELSE!][!//
/*MISRA2012_RULE_11_3_JUSTIFICATION:  The warning is coming for NULL_PTR defined by 
AUTOSAR. The function pointer is being allocated NULL_PTR as the particular 
function will not be required. The function is correctly getting assigned to NULL VALUE*/
[!VAR "jobend" = "concat('(Fee_NotifFunctionPtrType)',$jobend)"!][!//
[!ENDIF!][!//
[!IF "$block_type_configured != 'FEE_QUASI_STATIC_DATA_ONLY'"!][!//
    /* Fee Job end notification API */
    [!"$jobend"!],
[!IF "num:isnumber($joberror) != 'true'"!][!//
[!IF "$joberror = '""' or $joberror = '' or $joberror = 'NULL_PTR'"!][!//
/*MISRA2012_RULE_11_3_JUSTIFICATION:  The warning is coming for NULL_PTR defined by 
AUTOSAR. The function pointer is being allocated NULL_PTR as the particular 
function will not be required. The function is correctly getting assigned to NULL VALUE*/
[!VAR "joberror" = "'(Fee_NotifFunctionPtrType)NULL_PTR'"!][!//
[!ELSE!][!//
[!VAR "joberror" = "concat('&',$joberror)"!][!//
[!ENDIF!][!//
[!ELSE!][!//
/*MISRA2012_RULE_11_3_JUSTIFICATION:  The warning is coming for NULL_PTR defined by 
AUTOSAR. The function pointer is being allocated NULL_PTR as the particular 
function will not be required. The function is correctly getting assigned to NULL VALUE*/
[!VAR "joberror" = "concat('(Fee_NotifFunctionPtrType)',$joberror)"!][!//
[!ENDIF!][!//
    /* Fee Job error notification API */
    [!"$joberror"!],
[!ENDIF!][!//
[!IF "num:isnumber($qsjobend) != 'true'"!][!//
[!IF "$qsjobend = '""' or $qsjobend = '' or $qsjobend = 'NULL_PTR'"!][!//
/*MISRA2012_RULE_11_3_JUSTIFICATION:  The warning is coming for NULL_PTR defined by 
AUTOSAR. The function pointer is being allocated NULL_PTR as the particular 
function will not be required. The function is correctly getting assigned to NULL VALUE*/
[!VAR "qsjobend" = "'(Fee_NotifFunctionPtrType)NULL_PTR'"!][!//
[!ELSE!][!//
[!VAR "qsjobend" = "concat('&',$qsjobend)"!][!//
[!ENDIF!][!//
[!ELSE!][!//
/*MISRA2012_RULE_11_3_JUSTIFICATION:  The warning is coming for NULL_PTR defined by 
AUTOSAR. The function pointer is being allocated NULL_PTR as the particular 
function will not be required. The function is correctly getting assigned to NULL VALUE*/
[!VAR "qsjobend" = "concat('(Fee_NotifFunctionPtrType)',$qsjobend)"!][!//
[!ENDIF!][!//
[!IF "$block_type_configured != 'FEE_DOUBLE_SECTOR_DATA_ONLY'"!][!//
    /* Fee QS Job end notification API */
    [!"$qsjobend"!],
[!ENDIF!][!//
[!IF "num:isnumber($qsjoberror) != 'true'"!][!//
[!IF "$qsjoberror = '""' or $qsjoberror = '' or $qsjoberror = 'NULL_PTR'"!][!//
/*MISRA2012_RULE_11_3_JUSTIFICATION:  The warning is coming for NULL_PTR defined by 
AUTOSAR. The function pointer is being allocated NULL_PTR as the particular 
function will not be required. The function is correctly getting assigned to NULL VALUE*/
[!VAR "qsjoberror" = "'(Fee_NotifFunctionPtrType)NULL_PTR'"!][!//
[!ELSE!][!//
[!VAR "qsjoberror" = "concat('&',$qsjoberror)"!][!//
[!ENDIF!][!//
[!ELSE!][!//
/*MISRA2012_RULE_11_3_JUSTIFICATION:  The warning is coming for NULL_PTR defined by 
AUTOSAR. The function pointer is being allocated NULL_PTR as the particular 
function will not be required. The function is correctly getting assigned to NULL VALUE*/
[!VAR "qsjoberror" = "concat('(Fee_NotifFunctionPtrType)',$qsjoberror)"!][!//
[!ENDIF!][!//
[!IF "$block_type_configured != 'FEE_DOUBLE_SECTOR_DATA_ONLY'"!][!//
    /* Fee QS Job error notification API */
    [!"$qsjoberror"!],
[!ENDIF!][!//
[!IF "$block_type_configured != 'FEE_QUASI_STATIC_DATA_ONLY'"!][!//
    /* Fee threshold value */
    [!"$threshold"!]U,
[!ENDIF!][!//
    /* Number of blocks configured */
    [!"num:i($CountNvm + $CountQs)"!]U,
    {
[!IF "$block_type_configured != 'FEE_QUASI_STATIC_DATA_ONLY'"!][!//
[!IF "$unconfig = 'FEE_UNCONFIG_BLOCK_IGNORE'"!][!//
      /* Ignore the unconfigured blocks */
      FEE_UNCONFIG_BLOCK_IGNORE,
[!ELSE!][!//
      /* Keep the unconfigured blocks */
      FEE_UNCONFIG_BLOCK_KEEP,
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "$gc_restart = 'FEE_GC_RESTART_INIT'"!][!//
      /* Restart Garbage Collection during initialization */
      FEE_GC_RESTART_INIT,
[!ELSE!][!//
      /* Restart Garbage Collection when user job is requested */
      FEE_GC_RESTART_WRITE,
[!ENDIF!][!//

[!IF "$useerasesuspend = 'true'"!][!//
      /* Erase Suspend feature is enabled */
      FEE_ERASE_SUSPEND_ENABLED,
[!ELSE!][!//
      /* Erase Suspend feature is disabled */
      FEE_ERASE_SUSPEND_DISABLED,
[!ENDIF!][!//
      /* Reserved */
      0U
    },
[!//    
[!IF "$illegalnvmnotif = '""' or $illegalnvmnotif = '' or $illegalnvmnotif = 'NULL_PTR'"!][!//
/*MISRA2012_RULE_11_3_JUSTIFICATION: Pointers are accessing the correct memory 
range locations. Out of bounds checks were checked during functional verification. */
[!VAR "illegalnvmnotif" = "'(Fee_NotifFunctionPtrType)NULL_PTR'"!][!//
[!ELSE!][!//
/*MISRA2012_RULE_11_3_JUSTIFICATION:  The warning is coming for NULL_PTR defined by 
AUTOSAR. The function pointer is being allocated NULL_PTR as the particular 
function will not be required. The function is correctly getting assigned to NULL VALUE*/
[!VAR "illegalnvmnotif" = "concat('&',$illegalnvmnotif)"!][!//
[!ENDIF!][!//
/* Fee NVM Illegal State notification */
    [!"$illegalnvmnotif"!],
[!//    
[!IF "$illegalqsnotif = '""' or $illegalqsnotif = '' or $illegalqsnotif = 'NULL_PTR'"!][!//
/*MISRA2012_RULE_11_3_JUSTIFICATION: Pointers are accessing the correct memory 
range locations. Out of bounds checks were checked during functional verification. */
[!VAR "illegalqsnotif" = "'(Fee_NotifFunctionPtrType)NULL_PTR'"!][!//
[!ELSE!][!//
/*MISRA2012_RULE_11_3_JUSTIFICATION:  The warning is coming for NULL_PTR defined by 
AUTOSAR. The function pointer is being allocated NULL_PTR as the particular 
function will not be required. The function is correctly getting assigned to NULL VALUE*/
[!VAR "illegalqsnotif" = "concat('&',$illegalqsnotif)"!][!//
[!ENDIF!][!//
/* Fee NVM Illegal State notification */
    [!"$illegalqsnotif"!],
[!IF "$HardenErrNotif = '""' or $HardenErrNotif = '' or $HardenErrNotif = 'NULL_PTR'"!][!//
/*MISRA2012_RULE_11_3_JUSTIFICATION: Pointers are accessing the correct memory 
range locations. Out of bounds checks were checked during functional verification. */
[!VAR "HardenErrNotif" = "'(Fee_NotifFunctionPtrType)NULL_PTR'"!][!//
[!ELSE!][!//
/*MISRA2012_RULE_11_3_JUSTIFICATION:  The warning is coming for NULL_PTR defined by 
AUTOSAR. The function pointer is being allocated NULL_PTR as the particular 
function will not be required. The function is correctly getting assigned to NULL VALUE*/
[!VAR "HardenErrNotif" = "concat('&',$HardenErrNotif)"!][!//
[!ENDIF!][!//
/* QS Hardening Error notification */
    [!"$HardenErrNotif"!],
    	
[!IF "$block_type_configured != 'FEE_QUASI_STATIC_DATA_ONLY'"!][!//
[!IF "$eraseallenable = 'true'"!][!//
    /* Erase All feature is enabled */
    (boolean)TRUE
[!ELSE!][!//
    /* Erase All feature is disabled */
    (boolean)FALSE
[!ENDIF!][!//
[!ELSE!][!//
    /* Erase All feature is disabled */
    (boolean)FALSE
[!ENDIF!][!//  
};

#define FEE_STOP_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"

[!ENDSELECT!][!//
