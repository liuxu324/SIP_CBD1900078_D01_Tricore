[!/*
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
**  FILENAME  : Smu.m                                                         **
**                                                                            **
**  VERSION   : 7.0.0                                                         **
**                                                                            **
**  DATE      : 2018-08-01                                                    **
**                                                                            **
**  BSW MODULE DESCRIPTION : NA                                               **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**                                                                            **
**  DESCRIPTION  : Code template macro file for Smu Driver                    **
**                                                                            **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
*/!]
/******************************************************************************/
[!//
[!/* *** multiple inclusion protection*** */!][!//
[!IF "not(var:defined('Smu_M'))"!][!//
[!VAR "Smu_M"="'true'"!][!//

[!/*-- [cover parentID={7953DBEC-4296-4f33-96FC-0074E14CB869}]  [/cover] --*/!][!//
/*******************************************************************************
** Name             : Smu_FSP_Value                                           **
**                                                                            **
** Description      : Macro to retrieve the value in OutMac_FSP variable      **
**                    based on the MacInputVal value                          **
**                                                                            **
*******************************************************************************/
[!MACRO "Smu_FSP_Value", "MacInputVal" = ""!][!//
[!//
[!IF "$MacInputVal = 'SMU_REF_CLK_FRQ_DIV_2'"!][!//
[!VAR "OutMac_FSP" = "num:i(0)"!]
[!ELSEIF "$MacInputVal = 'SMU_REF_CLK_FRQ_DIV_4'"!][!//
[!VAR "OutMac_FSP" = "num:i(1)"!]
[!ELSEIF "$MacInputVal = 'SMU_REF_CLK_FRQ_DIV_8'"!][!//
[!VAR "OutMac_FSP" = "num:i(2)"!]
[!ELSEIF "$MacInputVal = 'SMU_REF_CLK_FRQ_DIV_16'"!][!//
[!VAR "OutMac_FSP" = "num:i(3)"!]
[!ELSEIF "$MacInputVal = 'SMU_REF_CLK_FRQ_DIV_32'"!][!//
[!VAR "OutMac_FSP" = "num:i(4)"!]
[!ELSEIF "$MacInputVal = 'SMU_REF_CLK_FRQ_DIV_64'"!][!//
[!VAR "OutMac_FSP" = "num:i(5)"!]
[!ELSEIF "$MacInputVal = 'SMU_REF_CLK_FRQ_DIV_128'"!][!//
[!VAR "OutMac_FSP" = "num:i(6)"!]
[!ELSEIF "$MacInputVal = 'SMU_REF_CLK_FRQ_DIV_256'"!][!//
[!VAR "OutMac_FSP" = "num:i(7)"!]
[!ELSEIF "$MacInputVal = 'SMU_REF_CLK_FRQ_DIV_512'"!][!//
[!VAR "OutMac_FSP" = "num:i(0)"!]
[!ELSEIF "$MacInputVal = 'SMU_REF_CLK_FRQ_DIV_1024'"!][!//
[!VAR "OutMac_FSP" = "num:i(1)"!]
[!ELSEIF "$MacInputVal = 'SMU_REF_CLK_FRQ_DIV_2048'"!][!//
[!VAR "OutMac_FSP" = "num:i(2)"!]
[!ELSEIF "$MacInputVal = 'SMU_REF_CLK_FRQ_DIV_4096'"!][!//
[!VAR "OutMac_FSP" = "num:i(3)"!]
[!ELSEIF "$MacInputVal = 'SMU_FSP_BISTABLE_PROTOCOL'"!][!//
[!VAR "OutMac_FSP" = "num:i(0)"!]
[!ELSEIF "$MacInputVal = 'SMU_FSP_TIME_SWITCHING_PROTOCOL'"!][!//
[!VAR "OutMac_FSP" = "num:i(2)"!]
[!ELSEIF "$MacInputVal = 'SMU_FSP_DUAL_RAIL_PROTOCOL'"!][!//
[!VAR "OutMac_FSP" = "num:i(1)"!]
[!ELSEIF "$MacInputVal = 'SMU_FSP_PES_DISABLE'"!][!//
[!VAR "OutMac_FSP" = "num:i(0)"!]
[!ELSEIF "$MacInputVal = 'SMU_FSP_PES_ENABLE'"!][!//
[!VAR "OutMac_FSP" = "num:i(1)"!]
[!ELSE!][!//
[!ERROR"Config Error: Wrong SMU_FSP."!]
[!ENDIF!]
[!ENDMACRO!]

[!/*-- [cover parentID={E4C0259C-2428-4e65-A3D7-7A53EB3C4E47}]  [/cover] --*/!][!//
/*******************************************************************************
** Name             : Smu_AGC_Value                                           **
**                                                                            **
** Description      : Macro to retrieve the value in OutMac_AG variable       **
**                    based on the MacInputVal value                          **
**                                                                            **
*******************************************************************************/
[!MACRO "Smu_AGC_Value", "MacInputVal" = ""!][!//
[!//
[!IF "$MacInputVal = 'SMU_SELECT_INT_NONE'"!][!//
[!VAR "OutMac_AGC" = "num:i(0)"!]
[!ELSEIF "$MacInputVal = 'SMU_SELECT_INT0'"!][!//
[!VAR "OutMac_AGC" = "num:i(1)"!]
[!ELSEIF "$MacInputVal = 'SMU_SELECT_INT1'"!][!//
[!VAR "OutMac_AGC" = "num:i(2)"!]
[!ELSEIF "$MacInputVal = 'SMU_SELECT_INT2'"!][!//
[!VAR "OutMac_AGC" = "num:i(4)"!]
[!ELSEIF "$MacInputVal = 'SMU_SELECT_INT0_INT1'"!][!//
[!VAR "OutMac_AGC" = "num:i(3)"!]
[!ELSEIF "$MacInputVal = 'SMU_SELECT_INT0_INT2'"!][!//
[!VAR "OutMac_AGC" = "num:i(5)"!]
[!ELSEIF "$MacInputVal = 'SMU_SELECT_INT1_INT2'"!][!//
[!VAR "OutMac_AGC" = "num:i(6)"!]
[!ELSEIF "$MacInputVal = 'SMU_SELECT_INT0_INT1_INT2'"!][!//
[!VAR "OutMac_AGC" = "num:i(7)"!]
[!ELSEIF "$MacInputVal = 'true'"!][!//
[!VAR "OutMac_AGC" = "num:i(1)"!]
[!ELSEIF "$MacInputVal = 'false'"!][!//
[!VAR "OutMac_AGC" = "num:i(0)"!]
[!ELSEIF "$MacInputVal = 'SMU_EFRST_DISABLE'"!][!//
[!VAR "OutMac_AGC" = "num:i(0)"!]
[!ELSEIF "$MacInputVal = 'SMU_EFRST_ENABLE'"!][!//
[!VAR "OutMac_AGC" = "num:i(1)"!]
[!ELSE!][!//
[!ERROR"Config Error: Wrong SMU_AGC Select."!]
[!ENDIF!]
[!ENDMACRO!]

[!/*-- [cover parentID={A5DC7017-38E0-4cb7-9F21-F8CB97F9263E}]  [/cover] --*/!][!//
/*******************************************************************************
** Name             : Smu_AlmCfg_Value                                        **
**                                                                            **
** Description      : Macro to retrieve the value in OutMac_AlmCfg variable   **
**                    based on the MacInputVal value                          **
**                                                                            **
*******************************************************************************/
[!MACRO "Smu_AlmCfg_Value", "MacInputVal" = ""!][!//
[!//
[!IF "$MacInputVal = 'SMU_NA_INT_ACTION'"!][!//
[!VAR "OutMac_AlmCfg" = "num:i(0)"!]
[!ELSEIF "$MacInputVal = 'SMU_IGCS0_INT_ACTION'"!][!//
[!VAR "OutMac_AlmCfg" = "num:i(2)"!]
[!ELSEIF "$MacInputVal = 'SMU_IGCS1_INT_ACTION'"!][!//
[!VAR "OutMac_AlmCfg" = "num:i(3)"!]
[!ELSEIF "$MacInputVal = 'SMU_IGCS2_INT_ACTION'"!][!//
[!VAR "OutMac_AlmCfg" = "num:i(4)"!]
[!ELSEIF "$MacInputVal = 'SMU_NMI_INT_ACTION'"!][!//
[!VAR "OutMac_AlmCfg" = "num:i(5)"!]
[!ELSEIF "$MacInputVal = 'SMU_RESET_INT_ACTION'"!][!//
[!VAR "OutMac_AlmCfg" = "num:i(6)"!]
[!ELSEIF "$MacInputVal = 'SMU_CPU_RESET_INT_ACTION'"!][!//
[!VAR "OutMac_AlmCfg" = "num:i(7)"!]
[!ELSEIF "$MacInputVal = 'SMU_ALARM_FSP_DISABLED'"!][!//
[!VAR "OutMac_AlmCfg" = "num:i(0)"!]
[!ELSEIF "$MacInputVal = 'SMU_ALARM_FSP_ENABLED'"!][!//
[!VAR "OutMac_AlmCfg" = "num:i(1)"!]
[!ELSE!][!//
[!ERROR"Config Error: Wrong SMU_AlmCfg Select."!][!//
[!ENDIF!]
[!ENDMACRO!]

[!/*-- [cover parentID={245D1393-1503-42ec-A413-09A3305FC212}]  [/cover] --*/!][!//
/*******************************************************************************
** Name             : Smu_RTACfg_Value                                        **
**                                                                            **
** Description      : Macro to retrieve the value in OutMac_RTACCfg variable  **
**                    based on the MacInputVal value                          **
**                                                                            **
*******************************************************************************/
[!MACRO "Smu_RTACfg_Value", "MacInputVal" = ""!][!//
[!//
[!IF "$MacInputVal = 'SMU_ALARM_GROUP0'"!][!//
[!VAR "OutMac_RTACCfg" = "num:i(0)"!]
[!ELSEIF "$MacInputVal = 'SMU_ALARM_GROUP1'"!][!//
[!VAR "OutMac_RTACCfg" = "num:i(1)"!]
[!ELSEIF "$MacInputVal = 'SMU_ALARM_GROUP2'"!][!//
[!VAR "OutMac_RTACCfg" = "num:i(2)"!]
[!ELSEIF "$MacInputVal = 'SMU_ALARM_GROUP3'"!][!//
[!VAR "OutMac_RTACCfg" = "num:i(3)"!]
[!ELSEIF "$MacInputVal = 'SMU_ALARM_GROUP4'"!][!//
[!VAR "OutMac_RTACCfg" = "num:i(4)"!]
[!ELSEIF "$MacInputVal = 'SMU_ALARM_GROUP5'"!][!//
[!VAR "OutMac_RTACCfg" = "num:i(5)"!]
[!ELSEIF "$MacInputVal = 'SMU_ALARM_GROUP6'"!][!//
[!VAR "OutMac_RTACCfg" = "num:i(6)"!]
[!ELSEIF "$MacInputVal = 'SMU_ALARM_GROUP7'"!][!//
[!VAR "OutMac_RTACCfg" = "num:i(7)"!]
[!ELSEIF "$MacInputVal = 'SMU_ALARM_GROUP8'"!][!//
[!VAR "OutMac_RTACCfg" = "num:i(8)"!]
[!ELSEIF "$MacInputVal = 'SMU_ALARM_GROUP9'"!][!//
[!VAR "OutMac_RTACCfg" = "num:i(9)"!]
[!ELSEIF "$MacInputVal = 'SMU_ALARM_GROUP10'"!][!//
[!VAR "OutMac_RTACCfg" = "num:i(10)"!]
[!ELSEIF "$MacInputVal = 'SMU_ALARM_GROUP11'"!][!//
[!VAR "OutMac_RTACCfg" = "num:i(11)"!]
[!ELSE!][!//
[!ERROR"Config Error: Wrong SMU_RTACCfg Select."!]
[!ENDIF!]
[!ENDMACRO!]


[!/*-- [cover parentID={8A1E3827-B1AE-47fd-A18C-C22B756EFA38}]  [/cover] --*/!][!//
/*******************************************************************************
** Name             : Smu_CMD_STDBY_Value                                     **
**                                                                            **
** Description      : Macro to retrieve the value in OutMac_CMD_STDBY variable**
**                    based on the MacInputVal value                          **
**                                                                            **
*******************************************************************************/
[!MACRO "Smu_CMD_STDBY_Value", "MacInputVal" = ""!][!//
[!//
[!IF "$MacInputVal = 'true'"!][!//
[!VAR "OutMac_CMD_STDBY" = "num:i(1)"!]
[!ELSEIF "$MacInputVal = 'false'"!][!//
[!VAR "OutMac_CMD_STDBY" = "num:i(0)"!]
[!ELSE!][!//
[!ERROR"Config Error: Wrong CMD_STDBY Select."!]
[!ENDIF!]
[!ENDMACRO!]

[!/*-- [cover parentID={11C651D0-26AC-4a84-A573-D2324D2D367F}]  [/cover] --*/!][!//
*******************************************************************************
** Name             : Smu_StdbyAlmCfg_Value                                   **
**                                                                            **
** Description      : Macro to retrieve the value in OutMac_StdbyAlmCfg       **
**                    variable based on the MacInputVal value                 **
**                                                                            **
*******************************************************************************/
[!MACRO "Smu_StdbyAlmCfg_Value", "MacInputVal" = ""!][!//
[!//
[!IF "$MacInputVal = 'SMU_ALARM_FSP_DISABLED'"!][!//
[!VAR "OutMac_StdbyAlmCfg" = "num:i(0)"!]
[!ELSEIF "$MacInputVal = 'SMU_ALARM_FSP_ENABLED'"!][!//
[!VAR "OutMac_StdbyAlmCfg" = "num:i(1)"!]
[!ELSE!][!//
[!ERROR"Config Error: Wrong StdbyAlmCfg Select."!]
[!ENDIF!]
[!ENDMACRO!]

[!/*-- [cover parentID={C3EDCC98-3DE9-4dc6-8AC3-BB3D001ED315}]  [/cover] --*/!][!//
/*******************************************************************************
** Name             : Smu_ConfigPreCompileSwitch                              **
**                                                                            **
** Description      : Macro to generate configuration Values ON/OFF           **
**                    based on configuration true/false                       **
**                                                                            **
*******************************************************************************/
[!MACRO "Smu_ConfigPreCompileSwitch", "NodeVal" = ""!][!//
[!//
[!IF "$NodeVal = 'true'"!][!//
(STD_ON)[!//
[!ELSE!][!//
(STD_OFF)[!//
[!ENDIF!]
[!ENDMACRO!]

[!/*-- [cover parentID={E5101D7C-BF52-47bf-AC25-CA02F8FE9ECB}]  [/cover] --*/!][!//


/*******************************************************************************
** Name             : Smu_FSPConfigSwitch                                     **
**                                                                            **
** Description      : Macro to generate configuration Values true/false       **
**                    based on configuration true/false                       **
**                                                                            **
*******************************************************************************/
[!MACRO "Smu_FSPConfigSwitch", "NodeVal" = ""!][!//
[!//
[!IF "$NodeVal = 'true'"!][!//
(0x1U)[!//
[!ELSE!][!//
(0x0U)[!//
[!ENDIF!]
[!ENDMACRO!]


[!ENDIF!][!// IF "not(var:defined('Smu_M'))


