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
**  FILENAME  : FlsLoader_Cfg.h $                                             **
**                                                                            **
**  VERSION   : 4.0.0                                                         **
**                                                                            **
**  DATE      : 2018-08-08                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : FlsLoader.bmd                                     **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2                                               **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY: [cover parentID={7AD39586-ED27-4604-83B1-D6834257029A}]     **
**                                                                            **
**  DESCRIPTION  : Code template for FlsLoader_Cfg.h file                     **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*************************************************************************/!][!//
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
**  FILENAME  : FlsLoader_Cfg.h                                               **
**                                                                            **
**  VERSION   : 1.1.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                                          **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                                            **
**                                                                            **
**  BSW MODULE DECRIPTION : FlsLoader.bmd                                     **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : FlashLoader configuration generated out of ECUC file       **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*[cover parentID={FA729015-A442-4cc3-8D5B-D6ED57FDD5E3}] added for code-gen 
dependencies. Dependency to resourceM is present by default[/cover]*/

#ifndef FLSLOADER_CFG_H
#define FLSLOADER_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* Pflash sector size */
#define FLSLOADER_PF_SECTOR_SIZE          (0X004000U)  /* 16KB */
#define FLSLOADER_PF_SECTOR_NUMBER_OFFSET (14U)        /* 16KB = 2^14 */
#define FLSLOADER_PF_SECTOR_MASK          (0xFF)
#define FLSLOADER_TC39x   (1U)

#define NO_PROTECTION     (0U)
#define READ_PROTECTION   (1U)
#define WRITE_PROTECTION  (2U)
#define WOP_PROTECTION    (3U)
#define OTP_PROTECTION    (4U)

[!NOCODE!][!//
[!/*
MACRO: CG_ConfigSwitch
Macro to generate configuration switch Values ON/OFF based on configuration
true/false
*/!]
[!MACRO "CG_ConfigSwitch", "nodeval" = ""!][!//
[!IF "$nodeval = 'true'"!][!//
(STD_ON)[!//
[!ELSE!][!//
(STD_OFF)[!//
[!ENDIF!][!//
[!ENDMACRO!][!//
[!//
[!ENDNOCODE!][!//
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('FlsLoader')[1]"!][!//

[!IF "ecu:get('FlsLoader.Pf0Sectors') = num:i(192)"!][!//
#define FLSLOADER_DERIVATIVE             (FLSLOADER_[!"ecu:get('Rel.SubDerivate')"!])
[!ENDIF!][!//
/* FLASH LOADER module instance ID */
#define FLSLOADER_INSTANCE_ID            ((uint8)1U)

[!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
[!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
[!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
#define FLSLOADER_AR_RELEASE_MAJOR_VERSION      ([!"$MajorVersion"!]U)
#define FLSLOADER_AR_RELEASE_MINOR_VERSION      ([!"$MinorVersion"!]U)
#define FLSLOADER_AR_RELEASE_REVISION_VERSION   ([!"$RevisionVersion"!]U)

[!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
[!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
[!VAR "SwPatchVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
#define FLSLOADER_SW_MAJOR_VERSION       ([!"$SwMajorVersion"!]U)
#define FLSLOADER_SW_MINOR_VERSION       ([!"$SwMinorVersion"!]U)
#define FLSLOADER_SW_PATCH_VERSION       ([!"$SwPatchVersion"!]U)

#define FLSLOADER_NUM_OF_PFLASH_BANK     ((uint8)[!"(ecu:get('FlsLoader.PfBank'))"!]U)
#define FLSLOADER_NUM_OF_DFLASH_BANK     ((uint8)[!"(ecu:get('FlsLoader.DfBank'))"!]U)
 
#define FLSLOADER_PFLASH0_START_ADDRESS  ((uint32)([!"num:inttohex(ecu:get('FlsLoader.Pf0StartAddress'))"!]U))
#define FLSLOADER_PFLASH0_END            ((FlsLoader_AddressType)([!"num:inttohex(ecu:get('FlsLoader.Pf0EndAddress'))"!]U))
#define FLSLOADER_PFLASH0_SIZE           ([!"num:inttohex(ecu:get('FlsLoader.Pf0Size'))"!]U)
#define FLSLOADER_NUM_OF_PF0_SECTORS     ([!"(ecu:get('FlsLoader.Pf0Sectors'))"!]U)
[!IF "ecu:get('FlsLoader.Pf1Sectors') > num:i(0)"!][!//

#define FLSLOADER_PFLASH1_START_ADDRESS  ((uint32)([!"num:inttohex(ecu:get('FlsLoader.Pf1StartAddress'))"!]U))
#define FLSLOADER_PFLASH1_END            ((FlsLoader_AddressType)([!"num:inttohex(ecu:get('FlsLoader.Pf1EndAddress'))"!]U))
#define FLSLOADER_PFLASH1_SIZE           ([!"num:inttohex(ecu:get('FlsLoader.Pf1Size'))"!]U)
#define FLSLOADER_NUM_OF_PF1_SECTORS     ([!"(ecu:get('FlsLoader.Pf1Sectors'))"!]U)
[!ENDIF!][!//
[!IF "ecu:get('FlsLoader.Pf2Sectors') > num:i(0)"!][!//

#define FLSLOADER_PFLASH2_START_ADDRESS  ((uint32)([!"num:inttohex(ecu:get('FlsLoader.Pf2StartAddress'))"!]U))
#define FLSLOADER_PFLASH2_END            ((FlsLoader_AddressType)([!"num:inttohex(ecu:get('FlsLoader.Pf2EndAddress'))"!]U))
#define FLSLOADER_PFLASH2_SIZE           ([!"num:inttohex(ecu:get('FlsLoader.Pf2Size'))"!]U)
#define FLSLOADER_NUM_OF_PF2_SECTORS     ([!"(ecu:get('FlsLoader.Pf2Sectors'))"!]U)
[!ENDIF!][!//
[!IF "ecu:get('FlsLoader.Pf3Sectors') > num:i(0)"!][!//

#define FLSLOADER_PFLASH3_START_ADDRESS  ((uint32)([!"num:inttohex(ecu:get('FlsLoader.Pf3StartAddress'))"!]U))
#define FLSLOADER_PFLASH3_END            ((FlsLoader_AddressType)([!"num:inttohex(ecu:get('FlsLoader.Pf3EndAddress'))"!]U))
#define FLSLOADER_PFLASH3_SIZE           ([!"num:inttohex(ecu:get('FlsLoader.Pf3Size'))"!]U)
#define FLSLOADER_NUM_OF_PF3_SECTORS     ([!"(ecu:get('FlsLoader.Pf3Sectors'))"!]U)
[!ENDIF!][!//
[!IF "ecu:get('FlsLoader.Pf4Sectors') > num:i(0)"!][!//

#define FLSLOADER_PFLASH4_START_ADDRESS  ((uint32)([!"num:inttohex(ecu:get('FlsLoader.Pf4StartAddress'))"!]U))
#define FLSLOADER_PFLASH4_END            ((FlsLoader_AddressType)([!"num:inttohex(ecu:get('FlsLoader.Pf4EndAddress'))"!]U))
#define FLSLOADER_PFLASH4_SIZE           ([!"num:inttohex(ecu:get('FlsLoader.Pf4Size'))"!]U)
#define FLSLOADER_NUM_OF_PF4_SECTORS     ([!"(ecu:get('FlsLoader.Pf4Sectors'))"!]U)
[!ENDIF!][!//
[!IF "ecu:get('FlsLoader.Pf5Sectors') > num:i(0)"!][!//

#define FLSLOADER_PFLASH5_START_ADDRESS  ((uint32)([!"num:inttohex(ecu:get('FlsLoader.Pf5StartAddress'))"!]U))
#define FLSLOADER_PFLASH5_END            ((FlsLoader_AddressType)([!"num:inttohex(ecu:get('FlsLoader.Pf5EndAddress'))"!]U))
#define FLSLOADER_PFLASH5_SIZE           ([!"num:inttohex(ecu:get('FlsLoader.Pf5Size'))"!]U)
#define FLSLOADER_NUM_OF_PF5_SECTORS     ([!"(ecu:get('FlsLoader.Pf5Sectors'))"!]U)
[!ENDIF!][!//

#define FLSLOADER_DFLASH0_START_ADDRESS  ((FlsLoader_AddressType)([!"num:inttohex(ecu:get('FlsLoader.Df0StartAddress'))"!]U))
#define FLSLOADER_DFLASH0_END            ((FlsLoader_AddressType)([!"num:inttohex(ecu:get('FlsLoader.Df0EndAddress'))"!]U))
#define FLSLOADER_DFLASH0_BANK_SIZE      ([!"num:inttohex(ecu:get('FlsLoader.Df0BankSize'))"!]U)
#define FLSLOADER_NUM_OF_DF0_SECTORS     ([!"(ecu:get('FlsLoader.Df0Sectors'))"!]U)

#define FLSLOADER_DFLASH1_START_ADDRESS  ((FlsLoader_AddressType)([!"num:inttohex(ecu:get('FlsLoader.Df1StartAddress'))"!]U))
#define FLSLOADER_DFLASH1_END            ((FlsLoader_AddressType)([!"num:inttohex(ecu:get('FlsLoader.Df1EndAddress'))"!]U))
#define FLSLOADER_DFLASH1_BANK_SIZE      ([!"num:inttohex(ecu:get('FlsLoader.Df1BankSize'))"!]U)
#define FLSLOADER_NUM_OF_DF1_SECTORS     ([!"(ecu:get('FlsLoader.Df1Sectors'))"!]U) 

/* UCB PFLASH Original address */
#define FLSLOADER_UCB_PFLASH_ORGINAL_START  ((FlsLoader_AddressType)([!"num:inttohex(ecu:get('FlsLoader.UcbPfOrgStart'))"!]U))
#define FLSLOADER_UCB_PFLASH_ORGINAL_END    ((FlsLoader_AddressType)([!"num:inttohex(ecu:get('FlsLoader.UcbPfOrgEnd'))"!]U))
#define FLSLOADER_UCB_PFLASH_ORGINAL_SIZE   ([!"num:inttohex(ecu:get('FlsLoader.UcbPfOrgSize') div num:i(4))"!]U)

/* UCB PFLASH Copy address */
#define FLSLOADER_UCB_PFLASH_COPY_START   ((FlsLoader_AddressType)([!"num:inttohex(ecu:get('FlsLoader.UcbPfCopyStart'))"!]U))
#define FLSLOADER_UCB_PFLASH_COPY_END     ((FlsLoader_AddressType)([!"num:inttohex(ecu:get('FlsLoader.UcbPfCopyEnd'))"!]U))
#define FLSLOADER_UCB_PFLASH_COPY_SIZE    ([!"num:inttohex(ecu:get('FlsLoader.UcbPfCopySize'))"!]U)

/* UCB DFLASH Original address */
#define FLSLOADER_UCB_DFLASH_ORIGINAL_START ((FlsLoader_AddressType)([!"num:inttohex(ecu:get('FlsLoader.UcbDfOrgStart'))"!]U))
#define FLSLOADER_UCB_DFLASH_ORGINAL_END    ((FlsLoader_AddressType)([!"num:inttohex(ecu:get('FlsLoader.UcbDfOrgEnd'))"!]U))
#define FLSLOADER_UCB_DFLASH_ORGINAL_SIZE   ([!"num:inttohex(ecu:get('FlsLoader.UcbDfOrgSize') div num:i(4))"!]U)

/* UCB DFLASH Copy address */
#define FLSLOADER_UCB_DFLASH_COPY_START   ((FlsLoader_AddressType)([!"num:inttohex(ecu:get('FlsLoader.UcbDfCopyStart'))"!]U))
#define FLSLOADER_UCB_DFLASH_COPY_END     ((FlsLoader_AddressType)([!"num:inttohex(ecu:get('FlsLoader.UcbDfCopyEnd'))"!]U))
#define FLSLOADER_UCB_DFLASH_COPY_SIZE    ([!"num:inttohex(ecu:get('FlsLoader.UcbDfCopySize'))"!]U)

/* UCB OTP0 address */
#define FLSLOADER_UCB_OTP0_START  ((FlsLoader_AddressType)([!"num:inttohex(ecu:get('FlsLoader.UcbOtp0Start'))"!]U))
#define FLSLOADER_UCB_OTP0_END    ((FlsLoader_AddressType)([!"num:inttohex(ecu:get('FlsLoader.UcbOtp0End'))"!]U))
#define FLSLOADER_UCB_OTP0_SIZE   ([!"num:inttohex(ecu:get('FlsLoader.UcbOtp0Size') div num:i(4))"!]U)

/* UCB OTP7 Copy address */
#define FLSLOADER_UCB_START   ((FlsLoader_AddressType)([!"num:inttohex(ecu:get('FlsLoader.UcbStart'))"!]U))
#define FLSLOADER_UCB_END     ((FlsLoader_AddressType)([!"num:inttohex(ecu:get('FlsLoader.UcbEnd'))"!]U))
#define FLSLOADER_UCB_SIZE    ([!"num:inttohex(ecu:get('FlsLoader.UcbSize'))"!]U)

[!IF "(ecu:get('FlsLoader.PfBank') = num:i(6))"!][!//
#define FLSLOADER_PF_BANKS                (6U)
#define FLSLOADER_FLASH_BUSY_MASK         (0x000000FDU)
#define FLSLOADER_PFLASH_END              (FLSLOADER_PFLASH5_END)
[!ELSEIF "(ecu:get('FlsLoader.PfBank') = num:i(5))"!][!//
#define FLSLOADER_PF_BANKS                (5U)
#define FLSLOADER_FLASH_BUSY_MASK         (0x0000007DU)
#define FLSLOADER_PFLASH_END              (FLSLOADER_PFLASH4_END)
[!ELSEIF "(ecu:get('FlsLoader.PfBank') = num:i(4))"!][!//
#define FLSLOADER_PF_BANKS                (4U)
#define FLSLOADER_FLASH_BUSY_MASK         (0x0000003DU)
#define FLSLOADER_PFLASH_END              (FLSLOADER_PFLASH3_END)
[!ELSEIF "ecu:get('FlsLoader.PfBank') = num:i(3)"!][!//
#define FLSLOADER_PF_BANKS                (3U)
#define FLSLOADER_FLASH_BUSY_MASK         (0x0000001DU)
#define FLSLOADER_PFLASH_END              (FLSLOADER_PFLASH2_END)
[!ELSEIF "ecu:get('FlsLoader.PfBank') = num:i(2)"!][!//
#define FLSLOADER_PF_BANKS                (2U)
#define FLSLOADER_FLASH_BUSY_MASK         (0x0000000DU)
#define FLSLOADER_PFLASH_END              (FLSLOADER_PFLASH1_END)
[!ELSE!][!//
#define FLSLOADER_PF_BANKS                (1U)
#define FLSLOADER_FLASH_BUSY_MASK         (0x00000005U)
#define FLSLOADER_PFLASH_END              (FLSLOADER_PFLASH0_END)
[!ENDIF!][!//

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

#define FLSLOADER_START_SEC_CONST_QM_LOCAL_8
#include "Flsloader_MemMap.h"

/* MISRA2012_RULE_8_9_JUSTIFICATION:FlsLoader_PFlashSectorCount is exported 
from FlsLoader_Cfg.c*/
extern const uint8 FlsLoader_PFlashSectorCount[FLSLOADER_NUM_OF_PFLASH_BANK];

#define FLSLOADER_STOP_SEC_CONST_QM_LOCAL_8
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Flsloader_MemMap.h"

/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the FLSLOADER module*/
#define FLSLOADER_START_SEC_CONST_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Flsloader_MemMap.h"

extern const uint32 FlsLoader_PFlashOffset[FLSLOADER_NUM_OF_PFLASH_BANK];

/* MISRA2012_RULE_5_1_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_2_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_4_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the FLSLOADER module*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Compiler supports macro names going beyond 
   32 chars and this macro is used only inside the FLSLOADER module*/
#define FLSLOADER_STOP_SEC_CONST_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Flsloader_MemMap.h"

/*******************************************************************************
**                      Derived Macros                                        **
*******************************************************************************/
/*
[cover parentID={F26CAAD6-9ABF-4fc2-91D9-6DA9C8309ED8}][/cover]
Configuration: FLSLOADER_DEV_ERROR_DETECT
Preprocessor switch to enable/disable the development error detection and
reporting.
-If ON, Enable development error detecion
-If OFF,Disable development error detecion
*/
#define FLSLOADER_DEV_ERROR_DETECT       [!CALL "CG_ConfigSwitch","nodeval" = "FlsLoaderGeneral/FlsLoaderDevErrorDetect"!][!//

/*
[cover parentID={17C6F5DC-4EC9-46e3-882B-8B9DB2068F72}][/cover]
Configuration: FLSLOADER_ENABLE_LOCKCHECK
Preprocessor switch to enable/disable the Lockcheck
The erase and write API's has Lock Check functionality, substantially
this is a big section, user could remove the same, if locking is not
used.
-If ON, Enable the FlsLoader Lockcheck in Write / Erase API's
-If OFF,Disable the FlsLoader Lockcheck in Write / Erase API's
*/
#define FLSLOADER_ENABLE_LOCKCHECK       [!CALL "CG_ConfigSwitch", "nodeval" = "FlsLoaderGeneral/FlsLoaderEnableLockCheck"!][!//

/*
[cover parentID={FE37F9D8-948F-4eec-A0E9-B1137A50224E}][/cover]
Configuration: FLSLOADER_DEINIT_API
Preprocessor switch to enable/disable the deinitilize FlsLoader API
-If ON, Enable FlsLoader Deinitilization API
-If OFF,Disable FlsLoader Deinitilization API
*/
#define FLSLOADER_DEINIT_API             [!CALL "CG_ConfigSwitch", "nodeval" = "FlsLoaderOptionalApi/FlsLoaderDeInitApi"!]

/*
[cover parentID={12B15DED-B5B8-40d9-97D3-0A271B57994D}][/cover]
Configuration: FLSLOADER_LOCK_UNLOCK_API
Preprocessor switch to enable/disable the Lock/UnLock API
-If ON, Enable the FlsLoader Lock/UnLock API
-If OFF,Disable FlsLoader Lock/UnLock API
*/
#define FLSLOADER_LOCK_UNLOCK_API        [!CALL "CG_ConfigSwitch", "nodeval" = "FlsLoaderOptionalApi/FlsLoaderLockUnlockApi"!][!//


/*
[cover parentID={59891D9C-E29C-4a81-A6A5-09D085E0A712}][/cover]
Configuration: FLSLOADER_CALLOUT_FUNC
Preprocessor switch to enable/disable the Loop CallOut function 
-If ON, Enable the FFlsLoader_lCallout Function 
-If OFF,Disable the FFlsLoader_lCallout Function 
*/
[!VAR "CallOutEnable" = "FlsLoaderGeneral/FlsLoaderCallOutFunction"!][!//
[!IF "$CallOutEnable != 'NULL_PTR'"!][!//
#define FLSLOADER_CALLOUT_FUNC           (STD_ON)
[!ELSE!][!//
#define FLSLOADER_CALLOUT_FUNC           (STD_OFF)
[!ENDIF!][!//

/*
[cover parentID={8251C609-6FAF-4016-A1CD-B96EE7809C88}][/cover]
Configuration: FLSLOADER_CALLOUT_TIME
The maximum time in nanoseconds to wait before invoking call-out function to application
*/
[!VAR "CalloutDuration" = "FlsLoaderGeneral/FlsLoaderCallOutTime"!][!//
#define FLSLOADER_CALLOUT_TIME           ([!"$CalloutDuration"!]U)

/*
[cover parentID={B7EF1C55-1DEB-4af6-AF10-098209CF0EC5}][/cover]
Configuration: FLSLOADER_VERSION_INFO_API
Preprocessor switch to enable/disable the versioninfo API
-If ON, Include the FlsLoader GetVersionInfo API
-If OFF,Disable FlsLoader GetVersionInfo API
*/
#define FLSLOADER_VERSION_INFO_API       [!CALL "CG_ConfigSwitch", "nodeval" = "FlsLoaderOptionalApi/FlsLoaderVersionInfoApi"!]

/*[cover parentID={0F20D5C4-179A-42b2-AB93-92D455F58A6B}][/cover]*/
/* Configuration: FlsLoader PFlash0 Protection configuration */
#define FLSLOADER_PF0_PROT         ([!"FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash0ProtConfig/FlsLoaderPFLash0WriteProt"!])

/*[cover parentID={E29D3CD4-C8E1-4402-80CB-A9AB468D3B10}][/cover]*/
[!IF "ecu:get('FlsLoader.Pf1Sectors') > num:i(0)"!][!//
/* Configuration: FlsLoader PFlash1 Protection configuration */
#define FLSLOADER_PF1_PROT        ([!"FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash1ProtConfig/FlsLoaderPFLash1WriteProt"!])
[!ELSE!][!//
/* Configuration:this device variant does not have Pf1Sectors so FLSLOADER_PF1_PROT 
  generated with default value NO_PROTECTION  */
#define FLSLOADER_PF1_PROT        (NO_PROTECTION)
[!ENDIF!][!//

/*[cover parentID={A61E62D5-694E-4405-AC29-686D9E1F8AF2}][/cover]*/
[!IF "ecu:get('FlsLoader.Pf2Sectors') > num:i(0)"!][!//
/* Configuration: FlsLoader PFlash2 Protection configuration */
#define FLSLOADER_PF2_PROT         ([!"FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash2ProtConfig/FlsLoaderPFLash2WriteProt"!])
[!ELSE!][!//
/* Configuration:this device variant does not have Pf2Sectors so FLSLOADER_PF2_PROT 
  generated with default value NO_PROTECTION  */
#define FLSLOADER_PF2_PROT         (NO_PROTECTION)
[!ENDIF!][!//

/*[cover parentID={65E85D45-5273-4c38-9D7F-897AE5037623}][/cover]*/
[!IF "ecu:get('FlsLoader.Pf3Sectors') > num:i(0)"!][!//
/* Configuration: FlsLoader PFlash3 Protection configuration */
#define FLSLOADER_PF3_PROT        ([!"FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash3ProtConfig/FlsLoaderPFLash3WriteProt"!])
[!ELSE!][!//
/* Configuration:this device variant does not have Pf3Sectors so FLSLOADER_PF3_PROT 
  generated with default value NO_PROTECTION   */
#define FLSLOADER_PF3_PROT         (NO_PROTECTION)
[!ENDIF!][!//

/*[cover parentID={E3428B02-7AF5-4e60-9187-75C888BA883A}][/cover]*/
[!IF "ecu:get('FlsLoader.Pf4Sectors') > num:i(0)"!][!//
/* Configuration: FlsLoader PFlash4 Protection configuration */
#define FLSLOADER_PF4_PROT        ([!"FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash4ProtConfig/FlsLoaderPFLash4WriteProt"!])
[!ELSE!][!//
/* Configuration:this device variant does not have Pf4Sectors so FLSLOADER_PF4_PROT 
  generated with default value NO_PROTECTION   */
#define FLSLOADER_PF4_PROT         (NO_PROTECTION)
[!ENDIF!][!//

/*[cover parentID={14FD328E-0F3F-4fbb-9E3A-C3348F37C14F}][/cover]*/
[!IF "ecu:get('FlsLoader.Pf5Sectors') > num:i(0)"!][!//
/* Configuration: FlsLoader PFlash5 Protection configuration */
#define FLSLOADER_PF5_PROT        ([!"FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash5ProtConfig/FlsLoaderPFLash5WriteProt"!])
[!ELSE!][!//
/* Configuration:this device variant does not have Pf5Sectors so FLSLOADER_PF5_PROT 
  generated with default value NO_PROTECTION   */
#define FLSLOADER_PF5_PROT         (NO_PROTECTION)
[!ENDIF!][!//

/*[cover parentID={45FEA2EA-58A1-4b63-AB3A-C312F849B9AB}][/cover]*/
/*
Configuration: FlsLoader DFLASH0 Read/Write Protection configuration */
#define FLSLOADER_DF0_PROT        ([!"FlsLoaderDFLASHConfig/FlsLoaderDFLASHConfig_0/FlsLoaderDFlash0ProtConfig/FlsLoaderDF0Prot"!])

/*******************************************************************************
**                      Extern function declarations                          **
*******************************************************************************/
[!NOCODE!]
[!VAR "CallOutFunc" = "FlsLoaderGeneral/FlsLoaderCallOutFunction"!]
[!IF "not(num:isnumber($CallOutFunc)) and $CallOutFunc != 'NULL_PTR'"!]
[!CODE!][!//
/*user defined call out function*/
extern void [!"$CallOutFunc"!](void);
[!ENDCODE!]
[!ENDIF!]
[!ENDNOCODE!][!//

#if ((FLSLOADER_PF0_PROT == READ_PROTECTION )|| \
  (FLSLOADER_PF0_PROT == WRITE_PROTECTION)|| \
  (FLSLOADER_PF0_PROT == OTP_PROTECTION )|| \
  (FLSLOADER_PF0_PROT == WOP_PROTECTION)\
[!IF "(ecu:get('FlsLoader.Pf1Sectors') > num:i(0))"!][!//
||(FLSLOADER_PF1_PROT == READ_PROTECTION )||\
  (FLSLOADER_PF1_PROT == WRITE_PROTECTION)\
||(FLSLOADER_PF1_PROT == OTP_PROTECTION )|| \
  (FLSLOADER_PF1_PROT == WOP_PROTECTION)\
[!ENDIF!][!//
[!IF "(ecu:get('FlsLoader.Pf2Sectors') > num:i(0))"!][!//
||(FLSLOADER_PF2_PROT == READ_PROTECTION )|| \
  (FLSLOADER_PF2_PROT == WRITE_PROTECTION)\
||(FLSLOADER_PF2_PROT == OTP_PROTECTION )|| \
  (FLSLOADER_PF2_PROT == WOP_PROTECTION)\
[!ENDIF!][!//
[!IF "(ecu:get('FlsLoader.Pf3Sectors') > num:i(0))"!][!//
||(FLSLOADER_PF3_PROT == READ_PROTECTION )|| \
  (FLSLOADER_PF3_PROT == WRITE_PROTECTION)\
||(FLSLOADER_PF3_PROT == OTP_PROTECTION )|| \
  (FLSLOADER_PF3_PROT == WOP_PROTECTION)\
[!ENDIF!][!//
[!IF "(ecu:get('FlsLoader.Pf4Sectors') > num:i(0))"!][!//
||(FLSLOADER_PF4_PROT == READ_PROTECTION )|| \
  (FLSLOADER_PF4_PROT == WRITE_PROTECTION)\
||(FLSLOADER_PF4_PROT == OTP_PROTECTION )|| \
  (FLSLOADER_PF4_PROT == WOP_PROTECTION)\
[!ENDIF!][!//
[!IF "(ecu:get('FlsLoader.Pf5Sectors') > num:i(0))"!][!//
||(FLSLOADER_PF5_PROT == READ_PROTECTION )|| \
  (FLSLOADER_PF5_PROT == WRITE_PROTECTION)\
||(FLSLOADER_PF5_PROT == OTP_PROTECTION )|| \
  (FLSLOADER_PF5_PROT == WOP_PROTECTION)\
[!ENDIF!][!//
)
/* PFLASH0 UCB 4 double word password*/
/* [cover parentID={EAA76066-D045-494d-A022-C888FDE3D5EC}][/cover] */
#define FLSLOADER_PF0_PW00   ((uint32)[!"num:inttohex(num:i(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash0ProtConfig/FlsLoaderPFUcbPW0_0),8)"!]U)
/* [cover parentID={A805D4D2-1A95-4511-9695-8C8E0DDAFAD6}][/cover] */
#define FLSLOADER_PF0_PW01   ((uint32)[!"num:inttohex(num:i(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash0ProtConfig/FlsLoaderPFUcbPW0_1),8)"!]U)
/* [cover parentID={208987E0-62B8-4140-BE7B-E1182B0B6C6B}][/cover] */
#define FLSLOADER_PF0_PW10   ((uint32)[!"num:inttohex(num:i(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash0ProtConfig/FlsLoaderPFUcbPW1_0),8)"!]U)
/* [cover parentID={D7E4E155-316D-498e-8862-69E075E653FA}][/cover] */
#define FLSLOADER_PF0_PW11   ((uint32)[!"num:inttohex(num:i(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash0ProtConfig/FlsLoaderPFUcbPW1_1),8)"!]U)
/* [cover parentID={A39A3040-F64C-4df8-BACE-34C5F40B0793}][/cover] */
#define FLSLOADER_PF0_PW20   ((uint32)[!"num:inttohex(num:i(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash0ProtConfig/FlsLoaderPFUcbPW2_0),8)"!]U)
/* [cover parentID={810CECD7-C60F-4619-88C6-6BBF4F891C48}][/cover] */
#define FLSLOADER_PF0_PW21   ((uint32)[!"num:inttohex(num:i(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash0ProtConfig/FlsLoaderPFUcbPW2_1),8)"!]U)
/* [cover parentID={A27300DD-1B2F-4618-B3B4-A8E2C4BC67E3}][/cover] */
#define FLSLOADER_PF0_PW30   ((uint32)[!"num:inttohex(num:i(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash0ProtConfig/FlsLoaderPFUcbPW3_0),8)"!]U)
/* [cover parentID={8D079434-8599-44b6-A12D-CF69B2D17D5F}][/cover] */
#define FLSLOADER_PF0_PW31   ((uint32)[!"num:inttohex(num:i(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash0ProtConfig/FlsLoaderPFUcbPW3_1),8)"!]U)

[!VAR "Proconp00" = "num:i(0)"!][!//
[!VAR "Proconp01" = "num:i(0)"!][!//
[!VAR "Proconp02" = "num:i(0)"!][!//
[!VAR "Proconp03" = "num:i(0)"!][!//
[!VAR "Proconp04" = "num:i(0)"!][!//
[!VAR "Proconp05" = "num:i(0)"!][!//
[!//
[!VAR "ProconOtp00" = "num:i(0)"!][!//
[!VAR "ProconOtp01" = "num:i(0)"!][!//
[!VAR "ProconOtp02" = "num:i(0)"!][!//
[!VAR "ProconOtp03" = "num:i(0)"!][!//
[!VAR "ProconOtp04" = "num:i(0)"!][!//
[!VAR "ProconOtp05" = "num:i(0)"!][!//
[!//
[!VAR "ProconWop00" = "num:i(0)"!][!//
[!VAR "ProconWop01" = "num:i(0)"!][!//
[!VAR "ProconWop02" = "num:i(0)"!][!//
[!VAR "ProconWop03" = "num:i(0)"!][!//
[!VAR "ProconWop04" = "num:i(0)"!][!//
[!VAR "ProconWop05" = "num:i(0)"!][!//
[!VAR "BitOffset" = "num:i(0)"!][!//
[!//
[!IF "(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash0ProtConfig/FlsLoaderPFLash0WriteProt = 'WRITE_PROTECTION')"!][!//
[!VAR "SectorPath1" ="'FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash0ProtConfig/FlsLoaderPF0Sector/FlsLoaderPF0Sector'"!][!//
[!//
[!FOR "i" = "0" TO "ecu:get('FlsLoader.Pf0Sectors') - num:i(1)"!][!//
[!VAR "SectorPath2" = "concat($SectorPath1,$i)"!][!//
[!VAR "SectorPath" = "concat($SectorPath2,'/FlsLoaderPFSectorWriteProtection')"!][!//
[!IF "node:value($SectorPath) = 'WRITE_PROTECTION'"!][!//
[!IF "$i < num:i(32)"!][!//
[!VAR "Proconp00" = "bit:bitset($Proconp00, $i)"!][!//
[!ELSEIF "$i < 64"!][!//
[!VAR "BitOffset" = "$i - num:i(32)"!][!//
[!VAR "Proconp01" = "bit:bitset($Proconp01, $BitOffset)"!][!//
[!ELSEIF "$i < 96"!][!//
[!VAR "BitOffset" = "$i -num:i(64)"!][!//
[!VAR "Proconp02" = "bit:bitset($Proconp02, $BitOffset)"!][!//
[!ELSEIF "$i < 128"!][!//
[!VAR "BitOffset" = "$i -num:i(96)"!][!//
[!VAR "Proconp03" = "bit:bitset($Proconp03, $BitOffset)"!][!//
[!ELSEIF "$i < 160"!][!//
[!VAR "BitOffset" = "$i -num:i(128)"!][!//
[!VAR "Proconp04" = "bit:bitset($Proconp04, $BitOffset)"!][!//
[!ELSEIF "$i < 192"!][!//
[!VAR "BitOffset" = "$i -num:i(160)"!][!//
[!VAR "Proconp05" = "bit:bitset($Proconp05, $BitOffset)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//

[!ELSEIF "(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash0ProtConfig/FlsLoaderPFLash0WriteProt = 'OTP_PROTECTION')"!][!//
[!VAR "SectorPath1" ="'FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash0ProtConfig/FlsLoaderPF0Sector/FlsLoaderPF0Sector'"!][!//

[!FOR "i" = "0" TO "ecu:get('FlsLoader.Pf0Sectors') - num:i(1)"!][!//
[!VAR "SectorPath2" = "concat($SectorPath1,$i)"!][!//
[!VAR "SectorPath" = "concat($SectorPath2,'/FlsLoaderPFSectorWriteProtection')"!][!//
[!IF "node:value($SectorPath) = 'OTP_PROTECTION'"!][!//
[!IF "$i < 32"!][!//
[!VAR "ProconOtp00" = "bit:bitset($ProconOtp00, $i)"!][!//
[!ELSEIF "$i < 64"!][!//
[!VAR "BitOffset" = "$i - num:i(32)"!][!//
[!VAR "ProconOtp01" = "bit:bitset($ProconOtp01, $BitOffset)"!][!//
[!ELSEIF "$i < 96"!][!//
[!VAR "BitOffset" = "$i - num:i(64)"!][!//
[!VAR "ProconOtp02" = "bit:bitset($ProconOtp02, $BitOffset)"!][!//
[!ELSEIF "$i < 128"!][!//
[!VAR "BitOffset" = "$i - num:i(96)"!][!//
[!VAR "ProconOtp03" = "bit:bitset($ProconOtp03, $BitOffset)"!][!//
[!ELSEIF "$i < 160"!][!//
[!VAR "BitOffset" = "$i - num:i(128)"!][!//
[!VAR "ProconOtp04" = "bit:bitset($ProconOtp04, $BitOffset)"!][!//
[!ELSEIF "$i < 192"!][!//
[!VAR "BitOffset" = "$i - num:i(160)"!][!//
[!VAR "ProconOtp05" = "bit:bitset($ProconOtp05, $BitOffset)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//

[!ELSEIF "(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash0ProtConfig/FlsLoaderPFLash0WriteProt = 'WOP_PROTECTION')"!][!//
[!VAR "SectorPath1" ="'FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash0ProtConfig/FlsLoaderPF0Sector/FlsLoaderPF0Sector'"!][!//
[!FOR "i" = "0" TO "ecu:get('FlsLoader.Pf0Sectors') - num:i(1)"!][!//
[!VAR "SectorPath2" = "concat($SectorPath1,$i)"!][!//
[!VAR "SectorPath" = "concat($SectorPath2,'/FlsLoaderPFSectorWriteProtection')"!][!//
[!IF "node:value($SectorPath) = 'WOP_PROTECTION'"!][!//
[!IF "$i < 32"!][!//
[!VAR "ProconWop00" = "bit:bitset($ProconWop00, $i)"!][!//
[!ELSEIF "$i < 64"!][!//
[!VAR "BitOffset" = "$i - num:i(32)"!][!//
[!VAR "ProconWop01" = "bit:bitset($ProconWop01, $BitOffset)"!][!//
[!ELSEIF "$i < 96"!][!//
[!VAR "BitOffset" = "$i - num:i(64)"!][!//
[!VAR "ProconWop02" = "bit:bitset($ProconWop02, $BitOffset)"!][!//
[!ELSEIF "$i < 128"!][!//
[!VAR "BitOffset" = "$i - num:i(96)"!][!//
[!VAR "ProconWop03" = "bit:bitset($ProconWop03, $BitOffset)"!][!//
[!ELSEIF "$i < 160"!][!//
[!VAR "BitOffset" = "$i - num:i(128)"!][!//
[!VAR "ProconWop04" = "bit:bitset($ProconWop04, $BitOffset)"!][!//
[!ELSEIF "$i < 192"!][!//
[!VAR "BitOffset" = "$i - num:i(160)"!][!//
[!VAR "ProconWop05" = "bit:bitset($ProconWop05, $BitOffset)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
/* PFLASH0 protection configuration for Sector x*/
/* [cover parentID={F29A2916-E9AD-480e-BD2D-57BA572D679E}][/cover] */
#define FLSLOADER_PROCONP00       ((uint32)[!"num:inttohex($Proconp00,8)"!]U)
/* [cover parentID={08B1953B-64F2-4713-8049-699E88747FE1}][/cover] */
#define FLSLOADER_PROCONP01       ((uint32)[!"num:inttohex($Proconp01,8)"!]U)
/* [cover parentID={54C97723-F466-42b4-9BBD-486484CB3942}][/cover] */
#define FLSLOADER_PROCONP02       ((uint32)[!"num:inttohex($Proconp02,8)"!]U)
/* [cover parentID={6C224434-C2AE-4d81-986A-9FEF701739B8}][/cover] */
#define FLSLOADER_PROCONP03       ((uint32)[!"num:inttohex($Proconp03,8)"!]U)
/* [cover parentID={51734116-FBC6-4ced-8797-624CCF651E2F}][/cover] */
#define FLSLOADER_PROCONP04       ((uint32)[!"num:inttohex($Proconp04,8)"!]U)
/* [cover parentID={E9952947-4873-4d79-9FE4-7EEEB60D54A7}][/cover] */
#define FLSLOADER_PROCONP05       ((uint32)[!"num:inttohex($Proconp05,8)"!]U)

/* [cover parentID={EAF3935C-8C46-499a-9AE9-8D9A7A000B33}][/cover] */
#define FLSLOADER_PROCONOTP00     ((uint32)[!"num:inttohex($ProconOtp00,8)"!]U)
/* [cover parentID={ACED8FD2-FF95-4d3c-A5B9-A9B791543166}][/cover] */
#define FLSLOADER_PROCONOTP01     ((uint32)[!"num:inttohex($ProconOtp01,8)"!]U)
/* [cover parentID={FE272641-D936-42e6-958C-6A98C801367C}][/cover] */
#define FLSLOADER_PROCONOTP02     ((uint32)[!"num:inttohex($ProconOtp02,8)"!]U)
/* [cover parentID={9D6466C9-126F-4c2d-83C4-D41860CA595D}][/cover] */
#define FLSLOADER_PROCONOTP03     ((uint32)[!"num:inttohex($ProconOtp03,8)"!]U)
/* [cover parentID={2787FBB2-3FB0-47eb-9774-53287C652695}][/cover] */
#define FLSLOADER_PROCONOTP04     ((uint32)[!"num:inttohex($ProconOtp04,8)"!]U)
/* [cover parentID={9616494C-D807-4ba9-99B1-858C2A9CD945}][/cover] */
#define FLSLOADER_PROCONOTP05     ((uint32)[!"num:inttohex($ProconOtp05,8)"!]U)

/* [cover parentID={3F4BFA28-0CF8-4f3c-B5F1-A187837CD872}][/cover] */
#define FLSLOADER_PROCONWOP00     ((uint32)[!"num:inttohex($ProconWop00,8)"!]U)
/* [cover parentID={CED18925-CABF-478f-921A-CFA0B4145959}][/cover] */
#define FLSLOADER_PROCONWOP01     ((uint32)[!"num:inttohex($ProconWop01,8)"!]U)
/* [cover parentID={490E1E06-E3E5-47fe-B493-EE3E375299B5}][/cover] */
#define FLSLOADER_PROCONWOP02     ((uint32)[!"num:inttohex($ProconWop02,8)"!]U)
/* [cover parentID={1EADFB9D-09BD-4350-9387-C56BD40C0346}][/cover] */
#define FLSLOADER_PROCONWOP03     ((uint32)[!"num:inttohex($ProconWop03,8)"!]U)
/* [cover parentID={685A76A1-0DBF-4e25-B7CA-07CD23602268}][/cover] */
#define FLSLOADER_PROCONWOP04     ((uint32)[!"num:inttohex($ProconWop04,8)"!]U)
/* [cover parentID={65103CD0-7718-40f2-97C1-F3C259BC80D8}][/cover] */
#define FLSLOADER_PROCONWOP05     ((uint32)[!"num:inttohex($ProconWop05,8)"!]U)

[!VAR "Proconp10" = "num:i(0)"!][!//
[!VAR "Proconp11" = "num:i(0)"!][!//
[!VAR "Proconp12" = "num:i(0)"!][!//
[!VAR "Proconp13" = "num:i(0)"!][!//
[!VAR "Proconp14" = "num:i(0)"!][!//
[!VAR "Proconp15" = "num:i(0)"!][!//
[!//
[!VAR "ProconOtp10" = "num:i(0)"!][!//
[!VAR "ProconOtp11" = "num:i(0)"!][!//
[!VAR "ProconOtp12" = "num:i(0)"!][!//
[!VAR "ProconOtp13" = "num:i(0)"!][!//
[!VAR "ProconOtp14" = "num:i(0)"!][!//
[!VAR "ProconOtp15" = "num:i(0)"!][!//
[!//
[!VAR "ProconWop10" = "num:i(0)"!][!//
[!VAR "ProconWop11" = "num:i(0)"!][!//
[!VAR "ProconWop12" = "num:i(0)"!][!//
[!VAR "ProconWop13" = "num:i(0)"!][!//
[!VAR "ProconWop14" = "num:i(0)"!][!//
[!VAR "ProconWop15" = "num:i(0)"!][!//
[!//
[!VAR "BitOffset" = "num:i(0)"!][!//
[!//
[!IF "ecu:get('FlsLoader.Pf1Sectors') > num:i(0)"!][!//
[!IF "(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash1ProtConfig/FlsLoaderPFLash1WriteProt = 'WRITE_PROTECTION')"!][!//
[!VAR "SectorPath1" ="'FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash1ProtConfig/FlsLoaderPF1Sector/FlsLoaderPF1Sector'"!][!//

[!FOR "i" = "0" TO "ecu:get('FlsLoader.Pf1Sectors') - num:i(1)"!][!//
[!VAR "SectorPath2" = "concat($SectorPath1,$i)"!][!//
[!VAR "SectorPath" = "concat($SectorPath2,'/FlsLoaderPFSectorWriteProtection')"!][!//
[!IF "node:value($SectorPath) = 'WRITE_PROTECTION'"!][!//
[!IF "$i < num:i(32)"!][!//
[!VAR "Proconp10" = "bit:bitset($Proconp10, $i)"!][!//
[!ELSEIF "$i < 64"!][!//
[!VAR "BitOffset" = "$i - num:i(32)"!][!//
[!VAR "Proconp11" = "bit:bitset($Proconp11, $BitOffset)"!][!//
[!ELSEIF "$i < 96"!][!//
[!VAR "BitOffset" = "$i - num:i(64)"!][!//
[!VAR "Proconp12" = "bit:bitset($Proconp12, $BitOffset)"!][!//
[!ELSEIF "$i < 128"!][!//
[!VAR "BitOffset" = "$i - num:i(96)"!][!//
[!VAR "Proconp13" = "bit:bitset($Proconp13, $BitOffset)"!][!//
[!ELSEIF "$i < 160"!][!//
[!VAR "BitOffset" = "$i - num:i(128)"!][!//
[!VAR "Proconp14" = "bit:bitset($Proconp14, $BitOffset)"!][!//
[!ELSEIF "$i < 192"!][!//
[!VAR "BitOffset" = "$i - num:i(160)"!][!//
[!VAR "Proconp15" = "bit:bitset($Proconp15, $BitOffset)"!][!//
[!ENDIF!][!//

[!ENDIF!][!//
[!ENDFOR!][!//

[!ELSEIF "(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash1ProtConfig/FlsLoaderPFLash1WriteProt = 'OTP_PROTECTION')"!][!//
[!VAR "SectorPath1" ="'FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash1ProtConfig/FlsLoaderPF1Sector/FlsLoaderPF1Sector'"!][!//

[!FOR "i" = "0" TO "ecu:get('FlsLoader.Pf1Sectors') - num:i(1)"!][!//
[!VAR "SectorPath2" = "concat($SectorPath1,$i)"!][!//
[!VAR "SectorPath" = "concat($SectorPath2,'/FlsLoaderPFSectorWriteProtection')"!][!//
[!IF "node:value($SectorPath) = 'OTP_PROTECTION'"!][!//
[!IF "$i < num:i(32)"!][!//
[!VAR "ProconOtp10" = "bit:bitset($ProconOtp10, $i)"!][!//
[!ELSEIF "$i < 64"!][!//
[!VAR "BitOffset" = "$i - num:i(32)"!][!//
[!VAR "ProconOtp11" = "bit:bitset($ProconOtp11, $BitOffset)"!][!//
[!ELSEIF "$i < 96"!][!//
[!VAR "BitOffset" = "$i - num:i(64)"!][!//
[!VAR "ProconOtp12" = "bit:bitset($ProconOtp12, $BitOffset)"!][!//
[!ELSEIF "$i < 128"!][!//
[!VAR "BitOffset" = "$i - num:i(96)"!][!//
[!VAR "ProconOtp13" = "bit:bitset($ProconOtp13, $BitOffset)"!][!//
[!ELSEIF "$i < 160"!][!//
[!VAR "BitOffset" = "$i - num:i(128)"!][!//
[!VAR "ProconOtp14" = "bit:bitset($ProconOtp14, $BitOffset)"!][!//
[!ELSEIF "$i < 192"!][!//
[!VAR "BitOffset" = "$i - num:i(160)"!][!//
[!VAR "ProconOtp15" = "bit:bitset($ProconOtp15, $BitOffset)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//

[!ELSEIF "(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash1ProtConfig/FlsLoaderPFLash1WriteProt = 'WOP_PROTECTION')"!][!//
[!VAR "SectorPath1" ="'FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash1ProtConfig/FlsLoaderPF1Sector/FlsLoaderPF1Sector'"!][!//

[!FOR "i" = "0" TO "ecu:get('FlsLoader.Pf1Sectors') - num:i(1)"!][!//
[!VAR "SectorPath2" = "concat($SectorPath1,$i)"!][!//
[!VAR "SectorPath" = "concat($SectorPath2,'/FlsLoaderPFSectorWriteProtection')"!][!//
[!IF "node:value($SectorPath) = 'WOP_PROTECTION'"!][!//
[!IF "$i < num:i(32)"!][!//
[!VAR "ProconWop10" = "bit:bitset($ProconWop10, $i)"!][!//
[!ELSEIF "$i < 64"!][!//
[!VAR "BitOffset" = "$i - num:i(32)"!][!//
[!VAR "ProconWop11" = "bit:bitset($ProconWop11, $BitOffset)"!][!//
[!ELSEIF "$i < 96"!][!//
[!VAR "BitOffset" = "$i - num:i(64)"!][!//
[!VAR "ProconWop12" = "bit:bitset($ProconWop12, $BitOffset)"!][!//
[!ELSEIF "$i < 128"!][!//
[!VAR "BitOffset" = "$i - num:i(96)"!][!//
[!VAR "ProconWop13" = "bit:bitset($ProconWop13, $BitOffset)"!][!//
[!ELSEIF "$i < 160"!][!//
[!VAR "BitOffset" = "$i - num:i(128)"!][!//
[!VAR "ProconWop14" = "bit:bitset($ProconWop14, $BitOffset)"!][!//
[!ELSEIF "$i < 192"!][!//
[!VAR "BitOffset" = "$i - num:i(160)"!][!//
[!VAR "ProconWop15" = "bit:bitset($ProconWop15, $BitOffset)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
/* PFLASH1 protection configuration for Sector x*/
/* [cover parentID={A1457E13-47FB-4c8a-B39B-4E693BBE5FB1}][/cover] */
#define FLSLOADER_PROCONP10       ((uint32)[!"num:inttohex($Proconp10,8)"!]U)
/* [cover parentID={BD18E84C-F4EF-416b-93FC-0A6C47A595A8}][/cover] */
#define FLSLOADER_PROCONP11       ((uint32)[!"num:inttohex($Proconp11,8)"!]U)
/* [cover parentID={DDF03E4B-9924-439b-9EC2-59398D6A60B6}][/cover] */
#define FLSLOADER_PROCONP12       ((uint32)[!"num:inttohex($Proconp12,8)"!]U)
/* [cover parentID={37976FA8-1518-4ee3-AE22-1A292632E63F}][/cover] */
#define FLSLOADER_PROCONP13       ((uint32)[!"num:inttohex($Proconp13,8)"!]U)
/* [cover parentID={7183555D-E8B7-4688-AB4F-21F738E615EA}][/cover] */
#define FLSLOADER_PROCONP14       ((uint32)[!"num:inttohex($Proconp14,8)"!]U)
/* [cover parentID={BB36E121-4308-48ba-8734-D6378C8B68C4}][/cover] */
#define FLSLOADER_PROCONP15       ((uint32)[!"num:inttohex($Proconp15,8)"!]U)

/* [cover parentID={DB6CDCCB-A0C5-488c-9145-416AE01130B9}][/cover] */
#define FLSLOADER_PROCONOTP10     ((uint32)[!"num:inttohex($ProconOtp10,8)"!]U)
/* [cover parentID={0C0F825B-47E5-427e-903C-0475CBD84960}][/cover] */
#define FLSLOADER_PROCONOTP11     ((uint32)[!"num:inttohex($ProconOtp11,8)"!]U)
/* [cover parentID={5E5CC155-858B-4abc-BEED-3ACF1F8F87B9}][/cover] */
#define FLSLOADER_PROCONOTP12     ((uint32)[!"num:inttohex($ProconOtp12,8)"!]U)
/* [cover parentID={2DE3405B-7CEA-488f-992A-CBC9506C7BF7}][/cover] */
#define FLSLOADER_PROCONOTP13     ((uint32)[!"num:inttohex($ProconOtp13,8)"!]U)
/* [cover parentID={FB580C38-83FC-4c6d-946F-17024C552A14}][/cover] */
#define FLSLOADER_PROCONOTP14     ((uint32)[!"num:inttohex($ProconOtp14,8)"!]U)
/* [cover parentID={5D99BA2A-4CD0-4cb5-98D3-E87695B9C603}][/cover] */
#define FLSLOADER_PROCONOTP15     ((uint32)[!"num:inttohex($ProconOtp15,8)"!]U)

/* [cover parentID={2D76BC0E-A57F-447d-BE94-FC0738C12635}][/cover] */
#define FLSLOADER_PROCONWOP10     ((uint32)[!"num:inttohex($ProconWop10,8)"!]U)
/* [cover parentID={FBDE6BEF-EB5F-4b76-8C62-8DF4FFEC1570}][/cover] */
#define FLSLOADER_PROCONWOP11     ((uint32)[!"num:inttohex($ProconWop11,8)"!]U)
/* [cover parentID={2CCEB389-6CE0-43a5-994C-5FA77449561C}][/cover] */
#define FLSLOADER_PROCONWOP12     ((uint32)[!"num:inttohex($ProconWop12,8)"!]U)
/* [cover parentID={36071A7E-9463-453b-98CD-1288CAEF117D}][/cover] */
#define FLSLOADER_PROCONWOP13     ((uint32)[!"num:inttohex($ProconWop13,8)"!]U)
/* [cover parentID={AAF9A345-CC57-49a1-BF5E-EC44D17B34EC}][/cover] */
#define FLSLOADER_PROCONWOP14     ((uint32)[!"num:inttohex($ProconWop14,8)"!]U)
/* [cover parentID={C5D1D2A3-AA27-4134-95FD-3FB5F85DD14A}][/cover] */
#define FLSLOADER_PROCONWOP15     ((uint32)[!"num:inttohex($ProconWop15,8)"!]U)

[!VAR "Proconp20" = "num:i(0)"!][!//
[!VAR "Proconp21" = "num:i(0)"!][!//
[!VAR "Proconp22" = "num:i(0)"!][!//
[!VAR "Proconp23" = "num:i(0)"!][!//
[!VAR "Proconp24" = "num:i(0)"!][!//
[!VAR "Proconp25" = "num:i(0)"!][!//
[!//
[!VAR "ProconOtp20" = "num:i(0)"!][!//
[!VAR "ProconOtp21" = "num:i(0)"!][!//
[!VAR "ProconOtp22" = "num:i(0)"!][!//
[!VAR "ProconOtp23" = "num:i(0)"!][!//
[!VAR "ProconOtp24" = "num:i(0)"!][!//
[!VAR "ProconOtp25" = "num:i(0)"!][!//
[!//
[!VAR "ProconWop20" = "num:i(0)"!][!//
[!VAR "ProconWop21" = "num:i(0)"!][!//
[!VAR "ProconWop22" = "num:i(0)"!][!//
[!VAR "ProconWop23" = "num:i(0)"!][!//
[!VAR "ProconWop24" = "num:i(0)"!][!//
[!VAR "ProconWop25" = "num:i(0)"!][!//
[!//
[!VAR "BitOffset" = "num:i(0)"!][!//
[!//
[!IF "ecu:get('FlsLoader.Pf2Sectors') > num:i(0)"!][!//
[!IF "(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash2ProtConfig/FlsLoaderPFLash2WriteProt = 'WRITE_PROTECTION')"!][!//
[!VAR "SectorPath1" ="'FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash2ProtConfig/FlsLoaderPF2Sector/FlsLoaderPF2Sector'"!][!//
[!FOR "i" = "0" TO "ecu:get('FlsLoader.Pf2Sectors') - num:i(1)"!][!//
[!VAR "SectorPath2" = "concat($SectorPath1,$i)"!][!//
[!VAR "SectorPath" = "concat($SectorPath2,'/FlsLoaderPFSectorWriteProtection')"!][!//
[!IF "node:value($SectorPath) = 'WRITE_PROTECTION'"!][!//
[!IF "$i < num:i(32)"!][!//
[!VAR "Proconp20" = "bit:bitset($Proconp20, $i)"!][!//
[!ELSEIF "$i < 64"!][!//
[!VAR "BitOffset" = "$i - num:i(32)"!][!//
[!VAR "Proconp21" = "bit:bitset($Proconp21, $BitOffset)"!][!//
[!ELSEIF "$i < 96"!][!//
[!VAR "BitOffset" = "$i - num:i(64)"!][!//
[!VAR "Proconp22" = "bit:bitset($Proconp22, $BitOffset)"!][!//
[!ELSEIF "$i < 128"!][!//
[!VAR "BitOffset" = "$i - num:i(96)"!][!//
[!VAR "Proconp23" = "bit:bitset($Proconp23, $BitOffset)"!][!//
[!ELSEIF "$i < 160"!][!//
[!VAR "BitOffset" = "$i - num:i(128)"!][!//
[!VAR "Proconp24" = "bit:bitset($Proconp24, $BitOffset)"!][!//
[!ELSEIF "$i < 192"!][!//
[!VAR "BitOffset" = "$i - num:i(160)"!][!//
[!VAR "Proconp25" = "bit:bitset($Proconp25, $BitOffset)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//

[!ELSEIF "(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash2ProtConfig/FlsLoaderPFLash2WriteProt = 'OTP_PROTECTION')"!][!//
[!VAR "SectorPath1" ="'FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash2ProtConfig/FlsLoaderPF2Sector/FlsLoaderPF2Sector'"!][!//
[!FOR "i" = "0" TO "ecu:get('FlsLoader.Pf2Sectors') - num:i(1)"!][!//
[!VAR "SectorPath2" = "concat($SectorPath1,$i)"!][!//
[!VAR "SectorPath" = "concat($SectorPath2,'/FlsLoaderPFSectorWriteProtection')"!][!//
[!IF "node:value($SectorPath) = 'OTP_PROTECTION'"!][!//
[!IF "$i < num:i(32)"!][!//
[!VAR "ProconOtp20" = "bit:bitset($ProconOtp20, $i)"!][!//
[!ELSEIF "$i < 64"!][!//
[!VAR "BitOffset" = "$i - num:i(32)"!][!//
[!VAR "ProconOtp21" = "bit:bitset($ProconOtp21, $BitOffset)"!][!//
[!ELSEIF "$i < 96"!][!//
[!VAR "BitOffset" = "$i - num:i(64)"!][!//
[!VAR "ProconOtp22" = "bit:bitset($ProconOtp22, $BitOffset)"!][!//
[!ELSEIF "$i < 128"!][!//
[!VAR "BitOffset" = "$i - num:i(96)"!][!//
[!VAR "ProconOtp23" = "bit:bitset($ProconOtp23, $BitOffset)"!][!//
[!ELSEIF "$i < 160"!][!//
[!VAR "BitOffset" = "$i - num:i(128)"!][!//
[!VAR "ProconOtp24" = "bit:bitset($ProconOtp24, $BitOffset)"!][!//
[!ELSEIF "$i < 192"!][!//
[!VAR "BitOffset" = "$i - num:i(160)"!][!//
[!VAR "ProconOtp25" = "bit:bitset($ProconOtp25, $BitOffset)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//

[!ELSEIF "(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash2ProtConfig/FlsLoaderPFLash2WriteProt = 'WOP_PROTECTION')"!][!//
[!VAR "SectorPath1" ="'FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash2ProtConfig/FlsLoaderPF2Sector/FlsLoaderPF2Sector'"!][!//
[!FOR "i" = "0" TO "ecu:get('FlsLoader.Pf2Sectors') - num:i(1)"!][!//
[!VAR "SectorPath2" = "concat($SectorPath1,$i)"!][!//
[!VAR "SectorPath" = "concat($SectorPath2,'/FlsLoaderPFSectorWriteProtection')"!][!//
[!IF "node:value($SectorPath) = 'WOP_PROTECTION'"!][!//
[!IF "$i < num:i(32)"!][!//
[!VAR "ProconWop20" = "bit:bitset($ProconWop20, $i)"!][!//
[!ELSEIF "$i < 64"!][!//
[!VAR "BitOffset" = "$i - num:i(32)"!][!//
[!VAR "ProconWop21" = "bit:bitset($ProconWop21, $BitOffset)"!][!//
[!ELSEIF "$i < 96"!][!//
[!VAR "BitOffset" = "$i - num:i(64)"!][!//
[!VAR "ProconWop22" = "bit:bitset($ProconWop22, $BitOffset)"!][!//
[!ELSEIF "$i < 128"!][!//
[!VAR "BitOffset" = "$i - num:i(96)"!][!//
[!VAR "ProconWop23" = "bit:bitset($ProconWop23, $BitOffset)"!][!//
[!ELSEIF "$i < 160"!][!//
[!VAR "BitOffset" = "$i - num:i(128)"!][!//
[!VAR "ProconWop24" = "bit:bitset($ProconWop24, $BitOffset)"!][!//
[!ELSEIF "$i < 192"!][!//
[!VAR "BitOffset" = "$i - num:i(160)"!][!//
[!VAR "ProconWop25" = "bit:bitset($ProconWop25, $BitOffset)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
/* PFLASH2 protection configuration for Sector x*/
/* [cover parentID={FEB8BB70-7529-48f4-A3F1-6A5F5037051E}][/cover] */
#define FLSLOADER_PROCONP20       ((uint32)[!"num:inttohex($Proconp20,8)"!]U)
/* [cover parentID={B914C116-CC1D-476d-B877-AC9629A7A0A3}][/cover] */
#define FLSLOADER_PROCONP21       ((uint32)[!"num:inttohex($Proconp21,8)"!]U)
/* [cover parentID={EEDD1C56-6409-45e6-AE60-E4966060A77F}][/cover] */
#define FLSLOADER_PROCONP22       ((uint32)[!"num:inttohex($Proconp22,8)"!]U)
/* [cover parentID={C730779F-60EF-45b0-9C80-5276565F1B9C}][/cover] */
#define FLSLOADER_PROCONP23       ((uint32)[!"num:inttohex($Proconp23,8)"!]U)
/* [cover parentID={44EF932B-44A2-47fc-9263-E83AEF941FD1}][/cover] */
#define FLSLOADER_PROCONP24       ((uint32)[!"num:inttohex($Proconp24,8)"!]U)
/* [cover parentID={D2081FAD-8E78-4be9-BE14-2EBFECDDC723}][/cover] */
#define FLSLOADER_PROCONP25       ((uint32)[!"num:inttohex($Proconp25,8)"!]U)

/* [cover parentID={29292CF5-0D4B-4b77-BB30-1D2C6AA891C7}][/cover] */
#define FLSLOADER_PROCONOTP20     ((uint32)[!"num:inttohex($ProconOtp20,8)"!]U)
/* [cover parentID={BCD7A783-7EE4-4585-B78A-1475D69BD9EF}][/cover] */
#define FLSLOADER_PROCONOTP21     ((uint32)[!"num:inttohex($ProconOtp21,8)"!]U)
/* [cover parentID={FDA611C8-93C8-43b3-9296-71BE2A17864A}][/cover] */
#define FLSLOADER_PROCONOTP22     ((uint32)[!"num:inttohex($ProconOtp22,8)"!]U)
/* [cover parentID={0EDC22CD-7A17-4315-8FE1-3D7792671D9C}][/cover] */
#define FLSLOADER_PROCONOTP23     ((uint32)[!"num:inttohex($ProconOtp23,8)"!]U)
/* [cover parentID={D71423A4-CF88-4b56-9E6A-927BEBFD7F0E}][/cover] */
#define FLSLOADER_PROCONOTP24     ((uint32)[!"num:inttohex($ProconOtp24,8)"!]U)
/* [cover parentID={5C7336EC-5A51-4844-9A5A-42B5E8B932F9}][/cover] */
#define FLSLOADER_PROCONOTP25     ((uint32)[!"num:inttohex($ProconOtp25,8)"!]U)

/* [cover parentID={92185DC6-AFB6-4017-AC54-1757EFE45850}][/cover] */
#define FLSLOADER_PROCONWOP20     ((uint32)[!"num:inttohex($ProconWop20,8)"!]U)
/* [cover parentID={8B66FD2D-D12C-4981-95A5-328063FB75B2}][/cover] */
#define FLSLOADER_PROCONWOP21     ((uint32)[!"num:inttohex($ProconWop21,8)"!]U)
/* [cover parentID={67CE9138-AB57-4f5f-A2C9-9CB630EFE725}][/cover] */
#define FLSLOADER_PROCONWOP22     ((uint32)[!"num:inttohex($ProconWop22,8)"!]U)
/* [cover parentID={3CC29CA3-6B83-465e-907B-096ACEB85A1D}][/cover] */
#define FLSLOADER_PROCONWOP23     ((uint32)[!"num:inttohex($ProconWop23,8)"!]U)
/* [cover parentID={54C1F7F3-04F2-490a-8799-FCF9BDE0B451}][/cover] */
#define FLSLOADER_PROCONWOP24     ((uint32)[!"num:inttohex($ProconWop24,8)"!]U)
/* [cover parentID={2DFCD2A6-1DD9-42bf-91D8-1B65DA1B6EFC}][/cover] */
#define FLSLOADER_PROCONWOP25     ((uint32)[!"num:inttohex($ProconWop25,8)"!]U)

[!VAR "Proconp30" = "num:i(0)"!][!//
[!VAR "Proconp31" = "num:i(0)"!][!//
[!VAR "Proconp32" = "num:i(0)"!][!//
[!VAR "Proconp33" = "num:i(0)"!][!//
[!VAR "Proconp34" = "num:i(0)"!][!//
[!VAR "Proconp35" = "num:i(0)"!][!//
[!//
[!VAR "ProconOtp30" = "num:i(0)"!][!//
[!VAR "ProconOtp31" = "num:i(0)"!][!//
[!VAR "ProconOtp32" = "num:i(0)"!][!//
[!VAR "ProconOtp33" = "num:i(0)"!][!//
[!VAR "ProconOtp34" = "num:i(0)"!][!//
[!VAR "ProconOtp35" = "num:i(0)"!][!//
[!//
[!VAR "ProconWop30" = "num:i(0)"!][!//
[!VAR "ProconWop31" = "num:i(0)"!][!//
[!VAR "ProconWop32" = "num:i(0)"!][!//
[!VAR "ProconWop33" = "num:i(0)"!][!//
[!VAR "ProconWop34" = "num:i(0)"!][!//
[!VAR "ProconWop35" = "num:i(0)"!][!//
[!//
[!VAR "BitOffset" = "num:i(0)"!][!//
[!//
[!IF "ecu:get('FlsLoader.Pf3Sectors') > num:i(0)"!][!//
[!IF "(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash3ProtConfig/FlsLoaderPFLash3WriteProt = 'WRITE_PROTECTION')"!][!//
[!VAR "SectorPath1" ="'FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash3ProtConfig/FlsLoaderPF3Sector/FlsLoaderPF3Sector'"!][!//
[!FOR "i" = "0" TO "ecu:get('FlsLoader.Pf3Sectors') - num:i(1)"!][!//
[!VAR "SectorPath2" = "concat($SectorPath1,$i)"!][!//
[!VAR "SectorPath" = "concat($SectorPath2,'/FlsLoaderPFSectorWriteProtection')"!][!//
[!IF "node:value($SectorPath) = 'WRITE_PROTECTION'"!][!//
[!IF "$i < num:i(32)"!][!//
[!VAR "Proconp30" = "bit:bitset($Proconp30, $i)"!][!//
[!ELSEIF "$i < 64"!][!//
[!VAR "BitOffset" = "$i - num:i(32)"!][!//
[!VAR "Proconp31" = "bit:bitset($Proconp31, $BitOffset)"!][!//
[!ELSEIF "$i < 96"!][!//
[!VAR "BitOffset" = "$i - num:i(64)"!][!//
[!VAR "Proconp32" = "bit:bitset($Proconp32, $BitOffset)"!][!//
[!ELSEIF "$i < 128"!][!//
[!VAR "BitOffset" = "$i - num:i(96)"!][!//
[!VAR "Proconp33" = "bit:bitset($Proconp33, $BitOffset)"!][!//
[!ELSEIF "$i < 160"!][!//
[!VAR "BitOffset" = "$i - num:i(128)"!][!//
[!VAR "Proconp34" = "bit:bitset($Proconp34, $BitOffset)"!][!//
[!ELSEIF "$i < 192"!][!//
[!VAR "BitOffset" = "$i - num:i(160)"!][!//
[!VAR "Proconp35" = "bit:bitset($Proconp35, $BitOffset)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//

[!ELSEIF "(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash3ProtConfig/FlsLoaderPFLash3WriteProt = 'OTP_PROTECTION')"!][!//
[!VAR "SectorPath1" ="'FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash3ProtConfig/FlsLoaderPF3Sector/FlsLoaderPF3Sector'"!][!//
[!FOR "i" = "0" TO "ecu:get('FlsLoader.Pf3Sectors') - num:i(1)"!][!//
[!VAR "SectorPath2" = "concat($SectorPath1,$i)"!][!//
[!VAR "SectorPath" = "concat($SectorPath2,'/FlsLoaderPFSectorWriteProtection')"!][!//
[!IF "node:value($SectorPath) = 'OTP_PROTECTION'"!][!//
[!IF "$i < num:i(32)"!][!//
[!VAR "ProconOtp30" = "bit:bitset($ProconOtp30, $i)"!][!//
[!ELSEIF "$i < 64"!][!//
[!VAR "BitOffset" = "$i - num:i(32)"!][!//
[!VAR "ProconOtp31" = "bit:bitset($ProconOtp31, $BitOffset)"!][!//
[!ELSEIF "$i < 96"!][!//
[!VAR "BitOffset" = "$i - num:i(64)"!][!//
[!VAR "ProconOtp32" = "bit:bitset($ProconOtp32, $BitOffset)"!][!//
[!ELSEIF "$i < 128"!][!//
[!VAR "BitOffset" = "$i - num:i(96)"!][!//
[!VAR "ProconOtp33" = "bit:bitset($ProconOtp33, $BitOffset)"!][!//
[!ELSEIF "$i < 160"!][!//
[!VAR "BitOffset" = "$i - num:i(128)"!][!//
[!VAR "ProconOtp34" = "bit:bitset($ProconOtp34, $BitOffset)"!][!//
[!ELSEIF "$i < 192"!][!//
[!VAR "BitOffset" = "$i - num:i(160)"!][!//
[!VAR "ProconOtp35" = "bit:bitset($ProconOtp35, $BitOffset)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//

[!ELSEIF "(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash3ProtConfig/FlsLoaderPFLash3WriteProt = 'WOP_PROTECTION')"!][!//
[!VAR "SectorPath1" ="'FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash3ProtConfig/FlsLoaderPF3Sector/FlsLoaderPF3Sector'"!][!//
[!FOR "i" = "0" TO "ecu:get('FlsLoader.Pf3Sectors') - num:i(1)"!][!//
[!VAR "SectorPath2" = "concat($SectorPath1,$i)"!][!//
[!VAR "SectorPath" = "concat($SectorPath2,'/FlsLoaderPFSectorWriteProtection')"!][!//
[!IF "node:value($SectorPath) = 'WOP_PROTECTION'"!][!//
[!IF "$i < num:i(32)"!][!//
[!VAR "ProconWop30" = "bit:bitset($ProconWop30, $i)"!][!//
[!ELSEIF "$i < 64"!][!//
[!VAR "BitOffset" = "$i - num:i(32)"!][!//
[!VAR "ProconWop31" = "bit:bitset($ProconWop31, $BitOffset)"!][!//
[!ELSEIF "$i < 96"!][!//
[!VAR "BitOffset" = "$i - num:i(64)"!][!//
[!VAR "ProconWop32" = "bit:bitset($ProconWop32, $BitOffset)"!][!//
[!ELSEIF "$i < 128"!][!//
[!VAR "BitOffset" = "$i - num:i(96)"!][!//
[!VAR "ProconWop33" = "bit:bitset($ProconWop33, $BitOffset)"!][!//
[!ELSEIF "$i < 160"!][!//
[!VAR "BitOffset" = "$i - num:i(128)"!][!//
[!VAR "ProconWop34" = "bit:bitset($ProconWop34, $BitOffset)"!][!//
[!ELSEIF "$i < 192"!][!//
[!VAR "BitOffset" = "$i - num:i(160)"!][!//
[!VAR "ProconWop35" = "bit:bitset($ProconWop35, $BitOffset)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
/* PFLASH3 protection configuration for Sector x*/
/* [cover parentID={58CBE0BF-D2B3-4f09-AD96-2B530BD62115}][/cover] */
#define FLSLOADER_PROCONP30       ((uint32)[!"num:inttohex($Proconp30,8)"!]U)
/* [cover parentID={AB0D7E94-A380-46e2-B003-368A18911D43}][/cover] */
#define FLSLOADER_PROCONP31       ((uint32)[!"num:inttohex($Proconp31,8)"!]U)
/* [cover parentID={DE7E35FC-25F6-4147-A967-808098CB3395}][/cover] */
#define FLSLOADER_PROCONP32         ((uint32)[!"num:inttohex($Proconp32,8)"!]U)
/* [cover parentID={B6EE2D9C-691B-49c6-9C99-31B1949F1D06}][/cover] */
#define FLSLOADER_PROCONP33         ((uint32)[!"num:inttohex($Proconp33,8)"!]U)
/* [cover parentID={E349E613-BA29-443a-A512-C4615E892C1E}][/cover] */
#define FLSLOADER_PROCONP34         ((uint32)[!"num:inttohex($Proconp34,8)"!]U)
/* [cover parentID={118FBA53-C5DA-481a-9E90-4D1E7DF4C72A}][/cover] */
#define FLSLOADER_PROCONP35         ((uint32)[!"num:inttohex($Proconp35,8)"!]U)

/* [cover parentID={1F3E8DD0-DAFC-4052-BDFC-3729B10CD2F4}][/cover] */
#define FLSLOADER_PROCONOTP30       ((uint32)[!"num:inttohex($ProconOtp30,8)"!]U)
/* [cover parentID={FC42602B-9ECD-4c24-A98F-0942ED504E83}][/cover] */
#define FLSLOADER_PROCONOTP31       ((uint32)[!"num:inttohex($ProconOtp31,8)"!]U)
/* [cover parentID={499A0D1F-51EE-4cd2-8B68-A7C6E266E2BF}][/cover] */
#define FLSLOADER_PROCONOTP32       ((uint32)[!"num:inttohex($ProconOtp32,8)"!]U)
/* [cover parentID={C5E1ECE9-98B2-454a-9493-90388B0DA47E}][/cover] */
#define FLSLOADER_PROCONOTP33       ((uint32)[!"num:inttohex($ProconOtp33,8)"!]U)
/* [cover parentID={1BF9AFB6-6DE1-4aa0-BE0C-2E0A909D24EB}][/cover] */
#define FLSLOADER_PROCONOTP34       ((uint32)[!"num:inttohex($ProconOtp34,8)"!]U)
/* [cover parentID={EA9A75FD-7C23-4b6b-952D-FBC3B3B57961}][/cover] */
#define FLSLOADER_PROCONOTP35       ((uint32)[!"num:inttohex($ProconOtp35,8)"!]U)

/* [cover parentID={CE7162FB-1481-4250-B777-A09FFC4CCDA4}][/cover] */
#define FLSLOADER_PROCONWOP30       ((uint32)[!"num:inttohex($ProconWop30,8)"!]U)
/* [cover parentID={47CC4003-545E-4bcc-B86C-37DC5E885202}][/cover] */
#define FLSLOADER_PROCONWOP31       ((uint32)[!"num:inttohex($ProconWop31,8)"!]U)
/* [cover parentID={B341961C-3773-4a4c-B9DD-841CFFC72614}][/cover] */
#define FLSLOADER_PROCONWOP32       ((uint32)[!"num:inttohex($ProconWop32,8)"!]U)
/* [cover parentID={F613874B-BFD7-4e60-97AF-10B6AC17B210}][/cover] */
#define FLSLOADER_PROCONWOP33       ((uint32)[!"num:inttohex($ProconWop33,8)"!]U)
/* [cover parentID={D50D391F-AD06-4635-B587-63DA35FBF7BE}][/cover] */
#define FLSLOADER_PROCONWOP34       ((uint32)[!"num:inttohex($ProconWop34,8)"!]U)
/* [cover parentID={91012028-26D1-46ba-AE05-D62E7BBDB72E}][/cover] */
#define FLSLOADER_PROCONWOP35       ((uint32)[!"num:inttohex($ProconWop35,8)"!]U)

[!VAR "Proconp40" = "num:i(0)"!][!//
[!VAR "Proconp41" = "num:i(0)"!][!//
[!VAR "Proconp42" = "num:i(0)"!][!//
[!VAR "Proconp43" = "num:i(0)"!][!//
[!VAR "Proconp44" = "num:i(0)"!][!//
[!VAR "Proconp45" = "num:i(0)"!][!//
[!//
[!VAR "ProconOtp40" = "num:i(0)"!][!//
[!VAR "ProconOtp41" = "num:i(0)"!][!//
[!VAR "ProconOtp42" = "num:i(0)"!][!//
[!VAR "ProconOtp43" = "num:i(0)"!][!//
[!VAR "ProconOtp44" = "num:i(0)"!][!//
[!VAR "ProconOtp45" = "num:i(0)"!][!//
[!//
[!VAR "ProconWop40" = "num:i(0)"!][!//
[!VAR "ProconWop41" = "num:i(0)"!][!//
[!VAR "ProconWop42" = "num:i(0)"!][!//
[!VAR "ProconWop43" = "num:i(0)"!][!//
[!VAR "ProconWop44" = "num:i(0)"!][!//
[!VAR "ProconWop45" = "num:i(0)"!][!//
[!//
[!VAR "BitOffset" = "num:i(0)"!][!//
[!//
[!IF "ecu:get('FlsLoader.Pf4Sectors') > num:i(0)"!][!//
[!IF "(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash4ProtConfig/FlsLoaderPFLash4WriteProt = 'WRITE_PROTECTION')"!][!//
[!VAR "SectorPath1" ="'FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash4ProtConfig/FlsLoaderPF4Sector/FlsLoaderPF4Sector'"!][!//
[!FOR "i" = "0" TO "ecu:get('FlsLoader.Pf4Sectors') - num:i(1)"!][!//
[!VAR "SectorPath2" = "concat($SectorPath1,$i)"!][!//
[!VAR "SectorPath" = "concat($SectorPath2,'/FlsLoaderPFSectorWriteProtection')"!][!//
[!IF "node:value($SectorPath) = 'WRITE_PROTECTION'"!][!//
[!IF "$i < num:i(32)"!][!//
[!VAR "Proconp40" = "bit:bitset($Proconp40, $i)"!][!//
[!ELSEIF "$i < 64"!][!//
[!VAR "BitOffset" = "$i - num:i(32)"!][!//
[!VAR "Proconp41" = "bit:bitset($Proconp41, $BitOffset)"!][!//
[!ELSEIF "$i < 96"!][!//
[!VAR "BitOffset" = "$i - num:i(64)"!][!//
[!VAR "Proconp42" = "bit:bitset($Proconp42, $BitOffset)"!][!//
[!ELSEIF "$i < 128"!][!//
[!VAR "BitOffset" = "$i - num:i(96)"!][!//
[!VAR "Proconp43" = "bit:bitset($Proconp43, $BitOffset)"!][!//
[!ELSEIF "$i < 160"!][!//
[!VAR "BitOffset" = "$i - num:i(128)"!][!//
[!VAR "Proconp44" = "bit:bitset($Proconp44, $BitOffset)"!][!//
[!ELSEIF "$i < 192"!][!//
[!VAR "BitOffset" = "$i - num:i(160)"!][!//
[!VAR "Proconp45" = "bit:bitset($Proconp45, $BitOffset)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//

[!ELSEIF "(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash4ProtConfig/FlsLoaderPFLash4WriteProt = 'OTP_PROTECTION')"!][!//
[!VAR "SectorPath1" ="'FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash4ProtConfig/FlsLoaderPF4Sector/FlsLoaderPF4Sector'"!][!//
[!FOR "i" = "0" TO "ecu:get('FlsLoader.Pf4Sectors') - num:i(1)"!][!//
[!VAR "SectorPath2" = "concat($SectorPath1,$i)"!][!//
[!VAR "SectorPath" = "concat($SectorPath2,'/FlsLoaderPFSectorWriteProtection')"!][!//
[!IF "node:value($SectorPath) = 'OTP_PROTECTION'"!][!//
[!IF "$i < num:i(32)"!][!//
[!VAR "ProconOtp40" = "bit:bitset($ProconOtp40, $i)"!][!//
[!ELSEIF "$i < 64"!][!//
[!VAR "BitOffset" = "$i - num:i(32)"!][!//
[!VAR "ProconOtp41" = "bit:bitset($ProconOtp41, $BitOffset)"!][!//
[!ELSEIF "$i < 96"!][!//
[!VAR "BitOffset" = "$i - num:i(64)"!][!//
[!VAR "ProconOtp42" = "bit:bitset($ProconOtp42, $BitOffset)"!][!//
[!ELSEIF "$i < 128"!][!//
[!VAR "BitOffset" = "$i - num:i(96)"!][!//
[!VAR "ProconOtp43" = "bit:bitset($ProconOtp43, $BitOffset)"!][!//
[!ELSEIF "$i < 160"!][!//
[!VAR "BitOffset" = "$i - num:i(128)"!][!//
[!VAR "ProconOtp44" = "bit:bitset($ProconOtp44, $BitOffset)"!][!//
[!ELSEIF "$i < 192"!][!//
[!VAR "BitOffset" = "$i - num:i(160)"!][!//
[!VAR "ProconOtp45" = "bit:bitset($ProconOtp45, $BitOffset)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//

[!ELSEIF "(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash4ProtConfig/FlsLoaderPFLash4WriteProt = 'WOP_PROTECTION')"!][!//
[!VAR "SectorPath1" ="'FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash4ProtConfig/FlsLoaderPF4Sector/FlsLoaderPF4Sector'"!][!//
[!FOR "i" = "0" TO "ecu:get('FlsLoader.Pf4Sectors') - num:i(1)"!][!//
[!VAR "SectorPath2" = "concat($SectorPath1,$i)"!][!//
[!VAR "SectorPath" = "concat($SectorPath2,'/FlsLoaderPFSectorWriteProtection')"!][!//
[!IF "node:value($SectorPath) = 'WOP_PROTECTION'"!][!//
[!IF "$i < num:i(32)"!][!//
[!VAR "ProconWop40" = "bit:bitset($ProconWop40, $i)"!][!//
[!ELSEIF "$i < 64"!][!//
[!VAR "BitOffset" = "$i - num:i(32)"!][!//
[!VAR "ProconWop41" = "bit:bitset($ProconWop41, $BitOffset)"!][!//
[!ELSEIF "$i < 96"!][!//
[!VAR "BitOffset" = "$i - num:i(64)"!][!//
[!VAR "ProconWop42" = "bit:bitset($ProconWop42, $BitOffset)"!][!//
[!ELSEIF "$i < 128"!][!//
[!VAR "BitOffset" = "$i - num:i(96)"!][!//
[!VAR "ProconWop43" = "bit:bitset($ProconWop43, $BitOffset)"!][!//
[!ELSEIF "$i < 160"!][!//
[!VAR "BitOffset" = "$i - num:i(128)"!][!//
[!VAR "ProconWop44" = "bit:bitset($ProconWop44, $BitOffset)"!][!//
[!ELSEIF "$i < 192"!][!//
[!VAR "BitOffset" = "$i - num:i(160)"!][!//
[!VAR "ProconWop45" = "bit:bitset($ProconWop45, $BitOffset)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
/* PFLASH4 protection configuration for Sector x*/
/* [cover parentID={566DAAE1-262C-4801-BA65-55BBA9D06A43}][/cover] */
#define FLSLOADER_PROCONP40       ((uint32)[!"num:inttohex($Proconp40,8)"!]U)
/* [cover parentID={07DDAA27-E8A5-4743-BDBA-AA527D5F46A6}][/cover] */
#define FLSLOADER_PROCONP41       ((uint32)[!"num:inttohex($Proconp41,8)"!]U)
/* [cover parentID={7F577772-08AB-484c-9391-6177FF72099A}][/cover] */
#define FLSLOADER_PROCONP42       ((uint32)[!"num:inttohex($Proconp42,8)"!]U)
/* [cover parentID={78BDB5DA-A845-444d-AF31-2EBB4EDA210F}][/cover] */
#define FLSLOADER_PROCONP43       ((uint32)[!"num:inttohex($Proconp43,8)"!]U)
/* [cover parentID={02C3194A-69E6-4529-A526-CE6BE3D65D4C}][/cover] */
#define FLSLOADER_PROCONP44       ((uint32)[!"num:inttohex($Proconp44,8)"!]U)
/* [cover parentID={A73B5B05-B67D-408e-81E4-B0A018C590A4}][/cover] */
#define FLSLOADER_PROCONP45       ((uint32)[!"num:inttohex($Proconp45,8)"!]U)

/* [cover parentID={6831E004-FC68-4b7d-97B7-455544C0B6CA}][/cover] */
#define FLSLOADER_PROCONOTP40       ((uint32)[!"num:inttohex($ProconOtp40,8)"!]U)
/* [cover parentID={C6FF62F0-9E36-4286-822D-A656108B7C9D}][/cover] */
#define FLSLOADER_PROCONOTP41       ((uint32)[!"num:inttohex($ProconOtp41,8)"!]U)
/* [cover parentID={A90DC5A4-46B9-4c59-BF8B-9EFFED038DC3}][/cover] */
#define FLSLOADER_PROCONOTP42       ((uint32)[!"num:inttohex($ProconOtp42,8)"!]U)
/* [cover parentID={54A9818B-8F1B-42da-B2A5-CB5FB65E075B}][/cover] */
#define FLSLOADER_PROCONOTP43       ((uint32)[!"num:inttohex($ProconOtp43,8)"!]U)
/* [cover parentID={4F83C0CD-F4F6-49f5-B601-BC169B974AF1}][/cover] */
#define FLSLOADER_PROCONOTP44       ((uint32)[!"num:inttohex($ProconOtp44,8)"!]U)
/* [cover parentID={BA2B96FF-C242-492a-B413-9B58C708051F}][/cover] */
#define FLSLOADER_PROCONOTP45       ((uint32)[!"num:inttohex($ProconOtp45,8)"!]U)

/* [cover parentID={1DC30615-68F6-4981-872C-885EDB35EC4F}][/cover] */
#define FLSLOADER_PROCONWOP40       ((uint32)[!"num:inttohex($ProconWop40,8)"!]U)
/* [cover parentID={A8C866F6-BF4E-472a-9C59-864024C8D854}][/cover] */
#define FLSLOADER_PROCONWOP41       ((uint32)[!"num:inttohex($ProconWop41,8)"!]U)
/* [cover parentID={14B1BACA-5FA8-4583-8FE1-A4EC3EEFA599}][/cover] */
#define FLSLOADER_PROCONWOP42       ((uint32)[!"num:inttohex($ProconWop42,8)"!]U)
/* [cover parentID={4DE754F4-63E6-4ba1-ACD3-ECE8C873249D}][/cover] */
#define FLSLOADER_PROCONWOP43       ((uint32)[!"num:inttohex($ProconWop43,8)"!]U)
/* [cover parentID={B403F508-1C39-45ba-9083-514F3151284E}][/cover] */
#define FLSLOADER_PROCONWOP44       ((uint32)[!"num:inttohex($ProconWop44,8)"!]U)
/* [cover parentID={3461C8D6-D524-44de-960A-B32EDA3A39E9}][/cover] */
#define FLSLOADER_PROCONWOP45       ((uint32)[!"num:inttohex($ProconWop45,8)"!]U)

[!VAR "Proconp50" = "num:i(0)"!][!//
[!VAR "Proconp51" = "num:i(0)"!][!//
[!//
[!VAR "ProconOtp50" = "num:i(0)"!][!//
[!VAR "ProconOtp51" = "num:i(0)"!][!//
[!//
[!VAR "ProconWop50" = "num:i(0)"!][!//
[!VAR "ProconWop51" = "num:i(0)"!][!//
[!//
[!VAR "BitOffset" = "num:i(0)"!][!//
[!//
[!IF "ecu:get('FlsLoader.Pf5Sectors') > num:i(0)"!][!//
[!IF "(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash5ProtConfig/FlsLoaderPFLash5WriteProt = 'WRITE_PROTECTION')"!][!//
[!VAR "SectorPath1" ="'FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash5ProtConfig/FlsLoaderPF5Sector/FlsLoaderPF5Sector'"!][!//
[!FOR "i" = "0" TO "ecu:get('FlsLoader.Pf5Sectors') - num:i(1)"!][!//
[!VAR "SectorPath2" = "concat($SectorPath1,$i)"!][!//
[!VAR "SectorPath" = "concat($SectorPath2,'/FlsLoaderPFSectorWriteProtection')"!][!//
[!IF "node:value($SectorPath) = 'WRITE_PROTECTION'"!][!//
[!IF "$i < num:i(32)"!][!//
[!VAR "Proconp50" = "bit:bitset($Proconp50, $i)"!][!//
[!ELSEIF "$i < 64"!][!//
[!VAR "BitOffset" = "$i - num:i(32)"!][!//
[!VAR "Proconp51" = "bit:bitset($Proconp51, $BitOffset)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//

[!ELSEIF "(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash5ProtConfig/FlsLoaderPFLash5WriteProt = 'OTP_PROTECTION')"!][!//
[!VAR "SectorPath1" ="'FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash5ProtConfig/FlsLoaderPF5Sector/FlsLoaderPF5Sector'"!][!//
[!FOR "i" = "0" TO "ecu:get('FlsLoader.Pf5Sectors') - num:i(1)"!][!//
[!VAR "SectorPath2" = "concat($SectorPath1,$i)"!][!//
[!VAR "SectorPath" = "concat($SectorPath2,'/FlsLoaderPFSectorWriteProtection')"!][!//
[!IF "node:value($SectorPath) = 'OTP_PROTECTION'"!][!//
[!IF "$i < num:i(32)"!][!//
[!VAR "ProconOtp50" = "bit:bitset($ProconOtp50, $i)"!][!//
[!ELSEIF "$i < 64"!][!//
[!VAR "BitOffset" = "$i - num:i(32)"!][!//
[!VAR "ProconOtp51" = "bit:bitset($ProconOtp51, $BitOffset)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//

[!ELSEIF "(FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash5ProtConfig/FlsLoaderPFLash5WriteProt = 'WOP_PROTECTION')"!][!//
[!VAR "SectorPath1" ="'FlsLoaderPFLASHConfig/FlsLoaderPFLASHConfig_0/FlsLoaderPFlash5ProtConfig/FlsLoaderPF5Sector/FlsLoaderPF5Sector'"!][!//
[!FOR "i" = "0" TO "ecu:get('FlsLoader.Pf5Sectors') - num:i(1)"!][!//
[!VAR "SectorPath2" = "concat($SectorPath1,$i)"!][!//
[!VAR "SectorPath" = "concat($SectorPath2,'/FlsLoaderPFSectorWriteProtection')"!][!//
[!IF "node:value($SectorPath) = 'WOP_PROTECTION'"!][!//
[!IF "$i < num:i(32)"!][!//
[!VAR "ProconWop50" = "bit:bitset($ProconWop50, $i)"!][!//
[!ELSEIF "$i < 64"!][!//
[!VAR "BitOffset" = "$i - num:i(32)"!][!//
[!VAR "ProconWop51" = "bit:bitset($ProconWop51, $BitOffset)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
/* PFLASH5 protection configuration for Sector x*/
/* [cover parentID={6BC75B4F-607D-4fae-B843-8F5EEDDCE753}][/cover] */
#define FLSLOADER_PROCONP50       ((uint32)[!"num:inttohex($Proconp50,8)"!]U)
/* [cover parentID={97C30AA9-2C0C-45bc-B2D8-377EFDFAE923}][/cover] */
#define FLSLOADER_PROCONP51       ((uint32)[!"num:inttohex($Proconp51,8)"!]U)
/* [cover parentID={AFC1074B-8F6C-4112-9F81-77697FF510A0}][/cover] */
#define FLSLOADER_PROCONOTP50       ((uint32)[!"num:inttohex($ProconOtp50,8)"!]U)
/* [cover parentID={C9CFEC62-5FBF-46cb-8396-5E9B22537EC8}][/cover] */
#define FLSLOADER_PROCONOTP51       ((uint32)[!"num:inttohex($ProconOtp51,8)"!]U)
/* [cover parentID={4592F684-7150-4ac7-AFFA-555CAE764DB2}][/cover] */
#define FLSLOADER_PROCONWOP50       ((uint32)[!"num:inttohex($ProconWop50,8)"!]U)
/* [cover parentID={D12B71DB-C931-4376-A385-E1CE85FA2165}][/cover] */
#define FLSLOADER_PROCONWOP51       ((uint32)[!"num:inttohex($ProconWop51,8)"!]U)

#endif

#if (FLSLOADER_DF0_PROT == READ_PROTECTION)
#define FLSLOADER_PROCOND0 ((uint32)(0x80000001U))
#elif (FLSLOADER_DF0_PROT == WRITE_PROTECTION)
#define FLSLOADER_PROCOND0 ((uint32)(0x00000001U))
#else
#define FLSLOADER_PROCOND0 ((uint32)(0x00000000U))
#endif

[!IF "FlsLoaderConfig/FlsLoaderConfig_0/FlsLoaderDFlash0ProtConfig/FlsLoaderDF0Prot != 'NO_PROTECTION'"!][!//
#if (FLSLOADER_DF0_PROT != NO_PROTECTION)
/* DFLASH UCB 4 double word password*/
/* [cover parentID={9F4A3344-902C-44fb-9BE7-DBCE14A4AF94}][/cover] */
#define FLSLOADER_DF0_PW00    ((uint32)[!"num:inttohex(num:i(FlsLoaderDFLASHConfig/FlsLoaderDFLASHConfig_0/FlsLoaderDFlash0ProtConfig/FlsLoaderDF0UcbPW0_0),8)"!]U)

/* [cover parentID={F150C16D-0260-47ec-BD26-3C5C250D5A8D}][/cover] */
#define FLSLOADER_DF0_PW01    ((uint32)[!"num:inttohex(num:i(FlsLoaderDFLASHConfig/FlsLoaderDFLASHConfig_0/FlsLoaderDFlash0ProtConfig/FlsLoaderDF0UcbPW0_1),8)"!]U)

/* [cover parentID={45E8499B-66FF-4e03-BBB6-19D58B17848A}][/cover] */
#define FLSLOADER_DF0_PW10    ((uint32)[!"num:inttohex(num:i(FlsLoaderDFLASHConfig/FlsLoaderDFLASHConfig_0/FlsLoaderDFlash0ProtConfig/FlsLoaderDF0UcbPW1_0),8)"!]U)

/* [cover parentID={596B12EE-A019-4448-8915-48503ECCFB6D}][/cover] */
#define FLSLOADER_DF0_PW11    ((uint32)[!"num:inttohex(num:i(FlsLoaderDFLASHConfig/FlsLoaderDFLASHConfig_0/FlsLoaderDFlash0ProtConfig/FlsLoaderDF0UcbPW1_1),8)"!]U)

/* [cover parentID={461D2E26-54F2-4b39-AC66-3ED155A26DF0}][/cover] */
#define FLSLOADER_DF0_PW20    ((uint32)[!"num:inttohex(num:i(FlsLoaderDFLASHConfig/FlsLoaderDFLASHConfig_0/FlsLoaderDFlash0ProtConfig/FlsLoaderDF0UcbPW2_0),8)"!]U)

/* [cover parentID={A1C102C3-2E87-4480-92D4-9B303479556E}][/cover] */
#define FLSLOADER_DF0_PW21    ((uint32)[!"num:inttohex(num:i(FlsLoaderDFLASHConfig/FlsLoaderDFLASHConfig_0/FlsLoaderDFlash0ProtConfig/FlsLoaderDF0UcbPW2_1),8)"!]U)

/* [cover parentID={2B0BB7B3-7A52-44cc-A31C-4430F3E768D7}][/cover] */
#define FLSLOADER_DF0_PW30    ((uint32)[!"num:inttohex(num:i(FlsLoaderDFLASHConfig/FlsLoaderDFLASHConfig_0/FlsLoaderDFlash0ProtConfig/FlsLoaderDF0UcbPW3_0),8)"!]U)

/* [cover parentID={1388FDEA-A734-4186-97D0-D7E45059DBEC}][/cover] */
#define FLSLOADER_DF0_PW31    ((uint32)[!"num:inttohex(num:i(FlsLoaderDFLASHConfig/FlsLoaderDFLASHConfig_0/FlsLoaderDFlash0ProtConfig/FlsLoaderDF0UcbPW3_1),8)"!]U)
#else
/* Passords in the form of Bytes used in array to fill in UCB_PFLASH  */
#define FLSLOADER_DF0_PW00    ((uint32)(0U))
#define FLSLOADER_DF0_PW01    ((uint32)(0U))
#define FLSLOADER_DF0_PW10    ((uint32)(0U))
#define FLSLOADER_DF0_PW11    ((uint32)(0U))
#define FLSLOADER_DF0_PW20    ((uint32)(0U))
#define FLSLOADER_DF0_PW21    ((uint32)(0U))
#define FLSLOADER_DF0_PW30    ((uint32)(0U))
#define FLSLOADER_DF0_PW31    ((uint32)(0U))
#endif
[!ENDIF!][!//

#define FLSLOADER_DF0_USERMODE    ((uint32)(0U))

[!ENDSELECT!][!//

#endif /*FLSLOADER_CFG_H*/
