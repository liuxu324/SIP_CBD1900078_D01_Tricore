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
**  FILENAME   : Fls_17_Dmu_PBCfg.c                                          **
**                                                                           **
**  VERSION :  3.0.0                                                         **
**                                                                           **
**  DATE       :  2018-03-27                                                 **
**                                                                           **
**  VARIANT   : Variant PB                                                   **
**                                                                           **
**  PLATFORM  : Infineon AURIX2G                                             **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION  : Code template for Fls_17_Dmu_PBCfg.c file                 **
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
**  FILENAME   : Fls_17_Dmu_PBCfg.c                                          **
**                                                                           **
**  VERSION :  3.0.0                                                         **
**                                                                           **
**  DATE, TIME: [!"$date"!], [!"$time"!]                                         **
**                                                                           **
**  GENERATOR : Build [!"$buildnr"!]                                            **
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

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* [cover parentID={4CE0ACDB-3D6F-4ba5-AB79-8AAB7154D070}][/cover] */
/* Include Flash Module File */
#include "Fls_17_Dmu.h"
#include "Fls_17_Dmu_ac.h"


[!//
[!VAR "VariantsConfigured" = "num:i(0)"!]
[!SELECT "as:modconf('EcuC')[1]"!][!//
[!IF "node:exists(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!][!//
[!VAR "PredefinedVarName1" = "(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!]
[!VAR "PredefinedVarName2" = "substring-after($PredefinedVarName1, "/")"!][!//
[!VAR "PredefinedVarName3" = "substring-after($PredefinedVarName2, "/")"!][!//
[!VAR "PredefinedVarName" = "substring-after($PredefinedVarName3, "/")"!][!//
[!VAR "VariantsConfigured" = "num:i(1)"!]
[!ENDIF!][!//
[!ENDSELECT!]

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

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

[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Fls')[1]"!][!//
[!SELECT "as:modconf('Fls')[1]/FlsConfigSet"!][!//
[!IF "node:exists(./FlsJobEndNotification/*[1]) = 'true'"!][!//
[!VAR "Notification1" = "./FlsJobEndNotification/*[1]"!][!//
[!ELSE!][!//
[!VAR "Notification1" = "''"!][!//
[!ENDIF!][!//
[!IF "string-length($Notification1) = 0"!][!//
[!VAR "Notification1" = "'(Fls_17_Dmu_NotifFunctionPtrType)0'"!][!//
[!ENDIF!][!//
[!IF "$Notification1 = '"NULL"' or $Notification1 = 'NULL'or $Notification1 = 'NULL_PTR' or $Notification1 = ''"!][!//
[!VAR "Notification1" = "'(Fls_17_Dmu_NotifFunctionPtrType)0'"!][!//
[!ENDIF!][!//
[!IF "$Notification1 != '(Fls_17_Dmu_NotifFunctionPtrType)0'"!][!//
/* Function declaration of Fls Job End Notification */
extern void [!"$Notification1"!](void);
[!ELSE!][!//
/* Job End Notification Function is not configured */
[!ENDIF!][!//

[!IF "node:exists(./FlsJobErrorNotification /*[1]) = 'true'"!][!//
[!VAR "Notification2" = "./FlsJobErrorNotification/*[1]"!][!//
[!ELSE!][!//
[!VAR "Notification2" = "''"!][!//
[!ENDIF!][!//
[!IF "string-length($Notification2) = 0"!][!//
[!VAR "Notification2" = "'(Fls_17_Dmu_NotifFunctionPtrType)0'"!][!//
[!ENDIF!][!//
[!IF "$Notification2 = '"NULL"' or $Notification2 = 'NULL' or $Notification2 = 'NULL_PTR' or $Notification2 = ''"!][!//
[!VAR "Notification2" = "'(Fls_17_Dmu_NotifFunctionPtrType)0'"!][!//
[!ENDIF!][!//
[!IF "$Notification2 != '(Fls_17_Dmu_NotifFunctionPtrType)0'"!][!//
/* Function declaration of Fls Job Error Notifications */
extern void [!"$Notification2"!](void);
[!ELSE!][!//
/* Job Error Notification Function is not configured */
[!ENDIF!][!//

[!IF "node:exists(./FlsEraseVerifyErrNotif /*[1]) = 'true'"!][!//
[!VAR "Notification3" = "./FlsEraseVerifyErrNotif/*[1]"!][!//
[!ELSE!][!//
[!VAR "Notification3" = "''"!][!//
[!ENDIF!][!//
[!IF "string-length($Notification3) = 0"!][!//
[!VAR "Notification3" = "'(Fls_17_Dmu_NotifFunctionPtrType)0'"!][!//
[!ENDIF!][!//
[!IF "$Notification3 = '"NULL"' or $Notification3 = 'NULL' or $Notification3 = 'NULL_PTR' or $Notification3 = ''"!][!//
[!VAR "Notification3" = "'(Fls_17_Dmu_NotifFunctionPtrType)0'"!][!//
[!ENDIF!][!//
[!IF "$Notification3 != '(Fls_17_Dmu_NotifFunctionPtrType)0'"!][!//
/* Function declaration of Fls EVER Error Notifications */
extern void [!"$Notification3"!](void);
[!ELSE!][!//
/* EVER Notification Function is not configured */
[!ENDIF!][!//

[!IF "node:exists(./FlsProgVerifyErrNotif/*[1]) = 'true'"!][!//
[!VAR "Notification4" = "./FlsProgVerifyErrNotif/*[1]"!][!//
[!ELSE!][!//
[!VAR "Notification4" = "''"!][!//
[!ENDIF!][!//
[!IF "string-length($Notification4) = 0"!][!//
[!VAR "Notification4" = "'(Fls_17_Dmu_NotifFunctionPtrType)0'"!][!//
[!ENDIF!][!//
[!IF "$Notification4 = '"NULL"' or $Notification4 = 'NULL' or $Notification4 = 'NULL_PTR' or $Notification4 = ''"!][!//
[!VAR "Notification4" = "'(Fls_17_Dmu_NotifFunctionPtrType)0'"!][!//
[!ENDIF!][!//
[!IF "$Notification4 != '(Fls_17_Dmu_NotifFunctionPtrType)0'"!][!//
/* Function declaration of Fls PVER Error Notifications */
extern void [!"$Notification4"!](void);
[!ELSE!][!//
/* PVER Notification Function is not configured */
[!ENDIF!][!//
[!ENDSELECT!][!//

[!VAR "NotifIllegalState" = "FlsIfxSpecificConfig/FlsIllegalStateNotification"!][!//
[!IF "string-length($NotifIllegalState) != 0 and $NotifIllegalState != '"NULL"' and $NotifIllegalState != 'NULL' and $NotifIllegalState != 'NULL_PTR' and $NotifIllegalState != ''"!][!//
/* Function declaration of Illegal State Notification */
extern void [!"$NotifIllegalState"!](void);
[!ELSE!][!//
/* Illegal State Notification function is not configured */
[!ENDIF!][!//
[!ENDSELECT!][!//

/*******************************************************************************
**                      Global Constant Definitions                          **
*******************************************************************************/
[!SELECT "as:modconf('Fls')[1]"!][!//
[!NOCODE!][!//
    [!VAR "NotifIllegalState" = "FlsIfxSpecificConfig/FlsIllegalStateNotification"!][!//
    [!IF "string-length($NotifIllegalState) = 0 or $NotifIllegalState = '"NULL"' or $NotifIllegalState = 'NULL' or $NotifIllegalState = 'NULL_PTR'"!][!//
    [!VAR "NotifIllegalState" = "'(Fls_17_Dmu_NotifFunctionPtrType)0'"!][!//
    [!ENDIF!][!//
[!ENDNOCODE!][!//
[!VAR "state_data_struct" = "FlsIfxSpecificConfig/FlsStateVarStruct"!][!//
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline.*/
#include "Fls_17_Dmu_MemMap.h"

/* Fls State Variable structure */
static Fls_17_Dmu_StateType  [!"$state_data_struct"!];

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline.*/
#include "Fls_17_Dmu_MemMap.h"
[!ENDSELECT!][!//

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_START_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED

/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline.*/
   #include "Fls_17_Dmu_MemMap.h"

/* MISRA2012_RULE_8_7_JUSTIFICATION: External linkage is needed as it is used 
     in more than one translation unit. */
/* MISRA2012_RULE_8_4_JUSTIFICATION: Defined as per AUTOSAR */
[!IF "$VariantsConfigured = num:i(1)"!][!//
const Fls_17_Dmu_ConfigType Fls_17_Dmu_Config_[!"$PredefinedVarName"!] =
[!ELSE!]
const Fls_17_Dmu_ConfigType Fls_17_Dmu_Config =
[!ENDIF!] 
{
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Fls')[1]"!][!//
[!VAR "FlsAcLoadOnJobStart" =  "FlsGeneral/FlsAcLoadOnJobStart"!][!//
[!VAR "FlsDevErrorDetect" =  "FlsGeneral/FlsDevErrorDetect"!][!//
[!VAR "FlsSafetyEnable" =  "FlsGeneral/FlsSafetyEnable"!][!//

[!SELECT "FlsConfigSet"!][!//
    /* Fls state variable structure */
    &[!"$state_data_struct"!],

    /* Maximum number of bytes to Read in one cycle */
    /* Fast Mode */
    [!"FlsMaxReadFastMode"!]U,
    
    /* Normal Mode */
    [!"FlsMaxReadNormalMode"!]U,
[!NOCODE!][!//
/* [cover parentID={0DC82B98-99E0-43ea-BA46-A7A740CD26FB}][/cover] */
    [!/* FlsJobEndNotification*/!][!//
    [!IF "node:exists(./FlsJobEndNotification/*[1]) = 'true'"!][!//
    [!VAR "Notification1" = "./FlsJobEndNotification/*[1]"!][!//
    [!ELSE!][!//
    [!VAR "Notification1" = "''"!][!//
    [!ENDIF!][!//
    [!IF "string-length($Notification1) = 0 or $Notification1 = '"NULL"' or $Notification1 = 'NULL' or $Notification1 = 'NULL_PTR'"!][!//
    [!VAR "Notification1" = "'(Fls_17_Dmu_NotifFunctionPtrType)0'"!][!//
    [!ENDIF!][!//
    [!/* FlsJobErrorNotification */!][!//
    [!IF "node:exists(./FlsJobErrorNotification /*[1]) = 'true'"!][!//
    [!VAR "Notification2" = "./FlsJobErrorNotification/*[1]"!][!//
    [!ELSE!][!//
    [!VAR "Notification2" = "''"!][!//
    [!ENDIF!][!//
    [!IF "string-length($Notification2) = 0 or $Notification2 = '"NULL"' or $Notification2 = 'NULL' or $Notification2 = 'NULL_PTR'"!][!//
    [!VAR "Notification2" = "'(Fls_17_Dmu_NotifFunctionPtrType)0'"!][!//
    [!ENDIF!][!//
    [!/* Fls EVER Notification */!][!//
    [!IF "node:exists(./FlsEraseVerifyErrNotif /*[1]) = 'true'"!][!//
    [!VAR "Notification3" = "./FlsEraseVerifyErrNotif/*[1]"!][!//
    [!ELSE!][!//
    [!VAR "Notification3" = "''"!][!//
    [!ENDIF!][!//
    [!IF "string-length($Notification3) = 0 or $Notification3 = '"NULL"' or $Notification3 = 'NULL' or $Notification3 = 'NULL_PTR'"!][!//
    [!VAR "Notification3" = "'(Fls_17_Dmu_NotifFunctionPtrType)0'"!][!//
    [!ENDIF!][!//
    [!/* Fls PVER Notification */!][!//
    [!IF "node:exists(./FlsProgVerifyErrNotif /*[1]) = 'true'"!][!//
    [!VAR "Notification4" = "./FlsProgVerifyErrNotif/*[1]"!][!//
    [!ELSE!][!//
    [!VAR "Notification4" = "''"!][!//
    [!ENDIF!][!//
    [!IF "string-length($Notification4) = 0 or $Notification4 = '"NULL"' or $Notification4 = 'NULL' or $Notification4 = 'NULL_PTR'"!][!//
    [!VAR "Notification4" = "'(Fls_17_Dmu_NotifFunctionPtrType)0'"!][!//
    [!ENDIF!][!//
[!ENDNOCODE!][!//

    /* Job End Notification */
[!IF "$Notification1 = '(Fls_17_Dmu_NotifFunctionPtrType)0'"!][!//
    NULL_PTR,
[!ELSE!][!//
    &[!"$Notification1"!],
[!ENDIF!][!//

    /* Job Error Notification */
[!IF "$Notification2 = '(Fls_17_Dmu_NotifFunctionPtrType)0'"!][!//
    NULL_PTR,
[!ELSE!][!//
    &[!"$Notification2"!],
[!ENDIF!][!//

 /* EVER Notification */
[!IF "$Notification3 = '(Fls_17_Dmu_NotifFunctionPtrType)0'"!][!//
    NULL_PTR,
[!ELSE!][!//
    &[!"$Notification3"!],
[!ENDIF!][!//

/* PVER Notification */
[!IF "$Notification4 = '(Fls_17_Dmu_NotifFunctionPtrType)0'"!][!//
    NULL_PTR,
[!ELSE!][!//
    &[!"$Notification4"!],
[!ENDIF!][!//

    /* Illegal State Notification */
[!IF "$NotifIllegalState = '(Fls_17_Dmu_NotifFunctionPtrType)0'"!][!//
    NULL_PTR,
[!ELSE!][!//
    &[!"$NotifIllegalState"!],
[!ENDIF!][!//

    /*Wait state configuration for Read access and error correction */
    (((uint32)[!"FlsWaitStateRead"!]) |
     ((uint32)[!"FlsWaitStateErrorCorrection"!] << 16U)) ,

[!IF "$FlsDevErrorDetect = 'true' or $FlsSafetyEnable = 'true'"!][!//
    /* FlsCallCycle for timeout monitoring, convert to us by multiplying by 
       1000 * 1000 */
[!VAR "CallCycle" = "FlsCallCycle"!][!//
[!VAR "CallCycle" = "$CallCycle * 1000 * 1000"!][!//
    [!"num:i($CallCycle)"!]U,
[!ENDIF!][!// 
    /* Default mode of FLS driver */
    [!"FlsDefaultMode"!]
[!ENDSELECT!][!//
[!ENDSELECT!][!//
};

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_STOP_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED

/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline.*/
 #include "Fls_17_Dmu_MemMap.h"

