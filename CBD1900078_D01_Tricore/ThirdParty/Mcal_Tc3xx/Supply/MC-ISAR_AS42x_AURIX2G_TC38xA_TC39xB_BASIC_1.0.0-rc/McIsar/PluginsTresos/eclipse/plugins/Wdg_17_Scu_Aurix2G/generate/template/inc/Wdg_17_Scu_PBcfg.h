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
**  FILENAME  : Wdg_17_Scu_PBcfg.h                                            **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE      : 2018-07-26                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Wdg_17_Scu.bmd                                    **
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
**  DESCRIPTION  : Code template header file for Wdg_17_Scu Driver            **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) :Specification of WDG_17_SCU Driver,                     **
**                      AUTOSAR Release 4.2.2                                 **
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
**  FILENAME  : Wdg_17_Scu_PBcfg.h                                            **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                                      **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                                          **
**                                                                            **
**  BSW MODULE DECRIPTION : Wdg_17_Scu.bmd                                    **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Wdg_17_Scu configuration generated out of ECUC file        **
**                                                                            **
**  SPECIFICATION(S) : Specification of WDG_17_SCU Driver,                    **
**                       AUTOSAR Release 4.2.2                                **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={3A6CF683-308A-4dce-A169-11EF8902965B}][/cover] */
#ifndef WDG_17_SCU_PBCFG_H
#define WDG_17_SCU_PBCFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/


/*******************************************************************************
**                      Global Const Definitions                              **
*******************************************************************************/
[!AUTOSPACING!] 
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Wdg')[1]"!][!//
[!//
[!VAR "No0fWdgModuleConfig" = "num:i(count(WdgSettingsConfig/*))"!][!//
[!FOR "Index" = "num:i(0)" TO "num:i($No0fWdgModuleConfig - num:i(1))"!][!//
[!VAR "WdgCoreID" = "WdgSettingsConfig/*[@index = $Index]/WdgCoreId"!]
[!VAR "EcucModuleExist" = "num:i(0)"!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* [cover parentID={1ECB14FC-FCA5-456f-A293-EBD310BAA256}][/cover] */
/* [cover parentID={7D8EFFAB-1BCE-4d95-9EAD-78CA0C0D73B9}][/cover] */
/* [cover parentID={215E3BF7-D5CD-4310-9508-58DD1BE281E0}][/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}][/cover] */
#define WDG_17_SCU_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"$WdgCoreID"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
#include "Wdg_17_Scu_MemMap.h"
/* MISRA2012_RULE_8_4_JUSTIFICATION: Prior declaration is not required as it
used same files. scope not limited with static to avoid compiler warning */
/* MISRA2012_RULE_8_7_JUSTIFICATION: Prior declaration is not required as it
used same files. scope not limited with static to avoid compiler warning */
[!SELECT "as:modconf('EcuC')[1]"!][!//
  [!IF "node:exists(EcucPostBuildVariants/*[1]/EcucPostBuildVariantRef/*[1])"!][!//
    [!VAR "EcucModuleExist" = "num:i(1)"!][!//
    [!LOOP "EcucPostBuildVariants/*[1]/EcucPostBuildVariantRef/*"!][!//
      [!VAR "Variantname"="''"!][!//
      [!VAR "Variantname" = "text:split(.,'/')[4]"!]
      [!WS"0"!]
      /* Extern declaration of Wdg_17_Scu Config Root for [!"$Variantname"!] */
      [!WS"0"!]extern const Wdg_17_Scu_ConfigType Wdg_17_Scu_Config_[!"$WdgCoreID"!]_[!"$Variantname"!];
    [!ENDLOOP!][!//
  [!ENDIF!][!//
[!ENDSELECT!][!//
[!IF "$EcucModuleExist = num:i(0)"!][!//
/* Extern declaration of Wdg_17_Scu Config Root */
extern const Wdg_17_Scu_ConfigType Wdg_17_Scu_Config_[!"$WdgCoreID"!];
[!ENDIF!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* [cover parentID={1ECB14FC-FCA5-456f-A293-EBD310BAA256}][/cover] */
/* [cover parentID={7D8EFFAB-1BCE-4d95-9EAD-78CA0C0D73B9}][/cover] */
/* [cover parentID={215E3BF7-D5CD-4310-9508-58DD1BE281E0}][/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}][/cover] */
#define WDG_17_SCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"$WdgCoreID"!]_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
#include "Wdg_17_Scu_MemMap.h"
/* MISRA2012_RULE_8_4_JUSTIFICATION: Prior declaration is not required as it
used same files. scope not limited with static to avoid compiler warning */
/* MISRA2012_RULE_8_7_JUSTIFICATION: Prior declaration is not required as it
used same files. scope not limited with static to avoid compiler warning */
[!ENDFOR!]
[!ENDSELECT!]
#endif  /* WDG_17_SCU_PBCFG_H */

