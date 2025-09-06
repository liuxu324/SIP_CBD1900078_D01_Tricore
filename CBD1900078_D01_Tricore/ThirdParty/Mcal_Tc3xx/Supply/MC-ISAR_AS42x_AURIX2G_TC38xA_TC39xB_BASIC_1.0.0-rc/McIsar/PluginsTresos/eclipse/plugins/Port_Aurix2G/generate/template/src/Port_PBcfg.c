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
**  FILENAME  : Port_PBCfg.c                                                  **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE      :2018-09-28                                                     **
**                                                                            **
**  BSW MODULE DECRIPTION : Port.bmd                                          **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={1ED8D59E-F9E3-45e0-8D9C-FA71E7957773},
   {07243163-3598-4e76-B231-2BF54658DEC4}]                                    **
**                                                                            **
**  DESCRIPTION  : Code template source file for Port Driver                  **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Port Driver, AUTOSAR Release 4.2.2    **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!][!//
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
**  FILENAME  : Port_PBCfg.c                                                  **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                                      **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                                          **
**                                                                            **
**  BSW MODULE DECRIPTION : Port.bmd                                          **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Port configuration generated out of ECUC file              **
**                                                                            **
**  SPECIFICATION(S) : Specification of Port Driver, AUTOSAR Release 4.2.2    **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/


[!//
[!NOCODE!]
[!INCLUDE "Port.m"!][!//
[!ENDNOCODE!] 
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Inclusion of Port Header file */
#include "Port.h"
[!//
[!VAR "VariantsConfigured" = "num:i(0)"!]
[!SELECT "as:modconf('EcuC')"!][!//
[!IF "node:exists(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!][!//
[!VAR "PredefinedVarName1" = "(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!]
[!VAR "PredefinedVarName2" = "substring-after($PredefinedVarName1, "/")"!][!//
[!VAR "PredefinedVarName3" = "substring-after($PredefinedVarName2, "/")"!][!//
[!VAR "PredefinedVarName" = "substring-after($PredefinedVarName3, "/")"!][!//
[!VAR "VariantsConfigured" = "num:i(1)"!]
[!ENDIF!][!//
[!ENDSELECT!]

[!//
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Port')"!][!//
[!//
[!/* Include Code Generator Macros */!][!//
[!NOCODE!][!//
[!INCLUDE "Port.m"!][!//
[!//
[!ENDNOCODE!][!//

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/


/* Macro definition for PORT pad drive control register Pn_PDR0 */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macros are used to calculate 
register values */
#define  Portx_lPdrConfig1(Pd0,Pd1,Pd2,Pd3,Pd4,Pd5,Pd6,Pd7)                    \
         ( ((uint32)(Pd7) << (uint32)28) | ((uint32)(Pd6) << (uint32)24) |     \
           ((uint32)(Pd5) << (uint32)20) | ((uint32)(Pd4) << (uint32)16) |     \
           ((uint32)(Pd3) << (uint32)12) |  ((uint32)(Pd2) << (uint32)8)  |    \
           ((uint32)(Pd1) << (uint32)4)  | (uint32)(Pd0)                       \
         )

/* Macro definition for PORT pad drive control register Pn_PDR1 */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macros are used to calculate 
register values */
#define  Portx_lPdrConfig2(Pd8,Pd9,Pd10,Pd11,Pd12,Pd13,Pd14,Pd15)              \
         ( ((uint32)(Pd15) << (uint32)28) | ((uint32)(Pd14) << (uint32)24) |   \
           ((uint32)(Pd13) << (uint32)20) | ((uint32)(Pd12) << (uint32)16) |   \
           ((uint32)(Pd11) << (uint32)12)|  ((uint32)(Pd10) << (uint32)8)  |   \
           ((uint32)(Pd9) << (uint32)4) | (uint32)(Pd8)                        \
         )                  
       
/* Macro definition for PORT Pad Disable Control Register */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macros are used to calculate 
register values */
#define Port_lDiscSet(b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15)   \
  ((uint16)(                                                                   \
            (uint32)(b0) | ((uint32)(b1) << (uint32)1) |                       \
            ((uint32)(b2) << (uint32)2) | ((uint32)(b3) << (uint32)3) |        \
            ((uint32)(b4) << (uint32)4) | ((uint32)(b5) << (uint32)5) |        \
            ((uint32)(b6) << (uint32)6) | ((uint32)(b7) << (uint32)7) |        \
            ((uint32)(b8) << (uint32)8) | ((uint32)(b9) << (uint32)9) |        \
            ((uint32)(b10) << (uint32)10) | ((uint32)(b11) << (uint32)11) |    \
            ((uint32)(b12) << (uint32)12) | ((uint32)(b13)<< (uint32)13) |     \
            ((uint32)(b14) << (uint32)14) | ((uint32)(b15) << (uint32)15)      \
           ))

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macros are used to calculate 
register values */
#define Port_lPcsr(b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15)      \
  ((uint32)(                                                                   \
            ((uint32)(b0)) | ((uint32)(b1) << (uint32)1) |                     \
            ((uint32)(b2) << (uint32)2) | ((uint32)(b3) << (uint32)3) |        \
            ((uint32)(b4) << (uint32)4) | ((uint32)(b5) << (uint32)5) |        \
            ((uint32)(b6) << (uint32)6) | ((uint32)(b7) << (uint32)7) |        \
            ((uint32)(b8) << (uint32)8) | ((uint32)(b9) << (uint32)9) |        \
            ((uint32)(b10) << (uint32)10) | ((uint32)(b11) << (uint32)11) |    \
            ((uint32)(b12) << (uint32)12) | ((uint32)(b13) << (uint32)13) |    \
            ((uint32)(b14) << (uint32)14) | ((uint32)(b15) << (uint32)15)      \
           ))
       
/* Macro definition for PORT LPCR register for LVDS */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macros are used to calculate 
register values */
#define Port_lLvds(REN_CTRL,RX_EN,TERM,LRTXERM,LVDSM,PS,TEN_CTRL,TX_EN,\
                   VIDFFADJ,VOSDYN,VOSEXT,TX_PD,TX_PWDPD) \
  ((uint32)(                                                                   \
           ((uint32)(REN_CTRL)) | ((uint32)(RX_EN) << (uint32)1) |             \
           ((uint32)(TERM) << (uint32)2) | ((uint32)(LRTXERM) << (uint32)3) |  \
           ((uint32)(LVDSM) << (uint32)6) |((uint32)(PS) << (uint32)7) |       \
           ((uint32)(TEN_CTRL) << (uint32)8) |                                 \
           ((uint32)(TX_EN) << (uint32)9) |((uint32)(VIDFFADJ) << (uint32)10) |\
           ((uint32)(VOSDYN) << (uint32)12) | ((uint32)(VOSEXT) << (uint32)13)|\
           ((uint32)(TX_PD) << (uint32)14) | ((uint32)(TX_PWDPD) << (uint32)15)\
           ))
/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}] [/cover] */
#define PORT_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines 
Port_Memmap.h header is included without safegaurd.*/
#include "Port_MemMap.h"

/*******************************************************************************
**                      Configuration Options                                 **
*******************************************************************************/
/*
                     Container : PortPinConfiguration
*/
/* Macros to define pin Default Input Output control value */
#define  PORT_PIN_DEFAULT                   (0x10U)

/* 
Configuration Options: Physical pin level
-LOW  (Low Volatage Level)
-HIGH (High Voltage Level) 
*/
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_PIN_LEVEL_LOW    (0x00U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_PIN_LEVEL_HIGH   (0x01U)

/* 
Configuration Options: Pin input pull resistor 
-NO PULL
-PULL DOWN
-PULL UP
*/
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_PIN_IN_PULL_UP     (0x10U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_PIN_IN_PULL_DOWN   (0x08U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_PIN_IN_NO_PULL     (0x00U)

/*
Configuration Options: Pin driver strength
*/
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define RFAST_PORT_PIN_STRONG_DRIVER_SHARP_EDGE  (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define RFAST_PORT_PIN_STRONG_DRIVER_MEDIUM_EDGE (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define RFAST_PORT_PIN_MEDIUM_DRIVER             (0x2U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define RFAST_PORT_PIN_RGMII_DRIVER              (0x3U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define RFAST_PORT_PIN_DEFAULT_DRIVER            (0x0U)

/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define FAST_PORT_PIN_STRONG_DRIVER_SHARP_EDGE  (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define FAST_PORT_PIN_STRONG_DRIVER_MEDIUM_EDGE (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define FAST_PORT_PIN_MEDIUM_DRIVER             (0x2U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define FAST_PORT_PIN_DEFAULT_DRIVER            (0x0U)


/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define SLOW_PORT_PIN_MEDIUM_DRIVER_SHARP_EDGE  (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define SLOW_PORT_PIN_MEDIUM_DRIVER             (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define SLOW_PORT_PIN_DEFAULT_DRIVER            (0x0U)

/* Pin driver strength value for the non available pins*/
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define  PORT_PIN_PAD_STRENGTH_DEFAULT      (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define  PORT_PIN_PAD_LEVEL_DEFAULT         (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define  PORT_PIN_PAD_DEFAULT               (0x0U)

/* 
Configuration Options: Pin output characteristics 
-PUSHPULL
-OPENDRAIN
*/

/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_PIN_OUT_PUSHPULL     (0x00U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_PIN_OUT_OPENDRAIN    (0x40U)

/*
Configuration Options: Pin Pad Level  
*/
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE  (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_INPUT_LEVEL_TTL_3_3V       (0xCU)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_INPUT_LEVEL_TTL_5_0V       (0x8U)


/* For the Px_DISC register value set */
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_PIN_ANALOG_INPUT_ENABLE  (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_PIN_ANALOG_INPUT_DISABLE (0x0U)

/* For PCSR register */
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_PCSR_ENABLE  (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_PCSR_DISABLE (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_PCSR_DEFAULT   (0x0U)

/* For Pn_LPCR registers wrt LVDSH pads */
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_PORT_CONTROLLED           (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_HSCT_CONTROLLED           (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_ENABLE                    (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_DISABLE                   (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_INTERNAL_TERMINATION      (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_EXTERNAL_TERMINATION      (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_POLY_RESISTOR_TERM        (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_LVDSM                     (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_LVDSH                     (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PAD_SUPPLY_3_3V                     (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PAD_SUPPLY_5_0V                    (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_LVDS_VDIFF_ADJ            (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_VOSDYN                    (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_VOSEXT                    (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_POWER_DOWN                (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_TX_PWDPD_ENABLE           (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_TX_PWDPD_DISABLE          (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration 
structures for generation values for structure members. The use of the macros 
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_DEFAULT                   (0x0U)



/******************************************************************************/
[!SELECT "as:modconf('Port')[1]"!][!//. 
[!VAR "PortPinDirectionChangeControl" = "PortGeneral/PortSetPinDirectionApi"!][!//
[!VAR "PortPinModeChangeControl" = "PortGeneral/PortSetPinModeApi"!][!//
[!// Determine if the configuration done for the port module is valid
[!CALL "Port_ConfigurationCheck"!][!//

[!/*[cover parentID={9F2D7FCF-E1E9-4619-8480-FC43F26BE49E}][/cover]*/!][!//
static const Port_n_ConfigType Port_kConfiguration[] = 
{
[!FOR "PortNumber" = "num:i(0)" TO "num:i(ecu:get('Port.MaxAvailablePort'))"!][!//
[!//
[!IF "($PortNumber = text:split(ecu:get('Port.AvailablePorts'), ' ' ))"!][!//
/*                              Port[!"$PortNumber"!]                       */
  {
    {
      /* Port pins direction, characteristics and mode configuration */
      
[!CALL "Port_GetPortPinDirectionAndModeAttributes","port" = "$PortNumber"!][!//
      
    },
  
    {
      /* Port pins initial level configuration */
      
[!CALL "Port_GetPortPinLevelAttributes","port" = "$PortNumber"!][!//
      
    },
  /* Port pins drive strength1 configuration */
    Portx_lPdrConfig1(
[!CALL "Port_GetPortPinDriverStrength1","port" = "$PortNumber"!][!//
                     ),
    /* Port pins drive strength2 configuration */
    Portx_lPdrConfig2(
[!CALL "Port_GetPortPinDriverStrength2","port" = "$PortNumber"!][!//
                     ),
[!IF "$PortPinModeChangeControl = 'true'"!][!//
    {/* Port pin run time mode changeable or not configuration */
      
[!CALL "Port_GetPortPinModeChangeable","port" = "$PortNumber"!][!//
      
    },
[!ENDIF!][!//
[!IF "$PortPinDirectionChangeControl = 'true'"!][!//
    {/* Port pin run time direction changeable or not configuration */
      
[!CALL "Port_GetPortPinDirectionChangeable","port" = "$PortNumber"!][!//
      
    },
    {
      /* Port pins direction, characteristics and mode configuration if 
         direction is changeable */   
      
[!CALL "Port_GetPortPinDirectionChangeableAttributes","port" = "$PortNumber"!][!//
      
    },
[!ENDIF!][!//

    {/* Port pin run time mode changeable or not configuration */
      
[!CALL "Port_GetPortPinEmergencyStopEnable","port" = "$PortNumber"!][!//
      
    }

   }[!IF "not(contains(ecu:get('Port.AvailableLastAnalogPort'), concat('_', $PortNumber, '_')))"!],[!ENDIF!]
[!ENDIF!][!//
[!//
[!ENDFOR!][!//
};

[!/*[cover parentID={C5935BEA-956A-4830-B242-2EF63FF78E52}][/cover]*/!][!//
static const uint32 Port_DiscSet[] = 
{     
[!FOR "PortNumber" = "num:i(0)" TO "num:i(ecu:get('Port.MaxAvailablePort'))"!][!//
[!IF "($PortNumber = text:split(ecu:get('Port.AvailableAnalogDigitalPorts'), ' ' ))"!][!//
 /*                              Port[!"$PortNumber"!]                       */
  
  Port_lDiscSet(
[!CALL "Port_GetPortPinAnalogInputSelection","port" = "$PortNumber"!][!//
                )[!IF "not(contains(ecu:get('Port.AvailableLastAnalogPort'), concat('_', $PortNumber, '_')))"!],[!ENDIF!]
[!ENDIF!][!//
[!//
[!ENDFOR!][!//
};

/* LVDS configuration */
static const Port_n_LVDSConfigType Port_kLVDSConfig[] = 
{
[!CALL "Port_GetLVDSPads"!][!//
};

/* PCSR configuration */
static const Port_n_PCSRConfigType Port_kPCSRConfig[] = 
{
[!CALL "Port_GetPCSRPads"!][!//
};

[!VAR "PortDevErrorDetect" = "PortGeneral/PortDevErrorDetect"!][!//
[!VAR "PortSafetyEnable" = "PortGeneral/PortSafetyEnable"!][!//

[!//
[!IF "$PortPinModeChangeControl = 'true'"!][!//
[!IF " $PortDevErrorDetect = 'true' or  $PortSafetyEnable = 'true' "!][!//

/*
   Array contains information on the modes supported by each port pin
*/
[!/*[cover parentID={BD08FB01-D07E-4cbf-B048-A684071046E5}][/cover]*/!][!//
static const Port_n_ModeType Port_kPinSupportedModes[] = 
{
[!FOR "PortNumber" = "num:i(0)" TO "num:i(ecu:get('Port.MaxAvailablePort'))"!][!//
[!//
[!IF "($PortNumber = text:split(ecu:get('Port.AvailablePorts'), ' ' ))"!][!//
/*     Port[!"$PortNumber"!]      */
  {
    {     
[!CALL "Port_GetPortPinMode","port" = "$PortNumber"!]
    }
  }[!IF "($PortNumber != text:split(ecu:get('Port.AvailableLastAnalogPort') ))"!],[!ENDIF!] 
[!ENDIF!][!//
[!//
[!ENDFOR!][!//
/* MISRA2012_RULE_19_2_JUSTIFICATION: Union is needed to access data per port pin 
and as a 32 Bit Value*/
};
[!ENDIF!][!// $PortPinModeChangeControl = 'true'
[!ENDIF!][!// $PortSafetyEnable = 'true' && $PortDevErrorDetect = 'true'
[!//
[!ENDSELECT!][!//

/* MISRA2012_RULE_8_7_JUSTIFICATION: Module configuration data structure
   declaration as per Autosar guidelines. This data structure may be needed
   by SW units using Port Driver APIs */
/* MISRA2012_RULE_8_4_JUSTIFICATION: Definition is as per Autosar guidelines */

[!IF "$VariantsConfigured = num:i(1)"!][!//
const Port_ConfigType Port_Config_[!"$PredefinedVarName"!] =
[!ELSE!]
const Port_ConfigType Port_Config = 
[!ENDIF!][!//
{
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!/*[cover parentID={A33149A5-C94D-4056-A074-CF27E7A250D4}][/cover]*/!][!//

[!SELECT "as:modconf('Port')[1]/PortConfigSet/*[1]"!][!//
[!//      
    /* Port Configuration set  */
    &Port_kConfiguration[0],
    /* Port 40-th Disc configuration set  */
    &Port_DiscSet[0],
[!IF "$PortPinModeChangeControl = 'true' "!][!//
[!IF "$PortDevErrorDetect = 'true' or  $PortSafetyEnable = 'true' "!][!//
    &Port_kPinSupportedModes[0],[!//
[!ENDIF!][!// $PortPinModeChangeControl = 'true' && $PortDevErrorDetect = 'true'
[!ENDIF!]
    /* LVDS configuration */
    &Port_kLVDSConfig[0],
    /* PCSR Configuration */
    &Port_kPCSRConfig[0]
  [!//
[!ENDSELECT!]
};


#define PORT_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines 
Port_Memmap.h header is included without safegaurd.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Port_Memmap.h header included as per Autosar 
   guidelines. */
#include "Port_MemMap.h"
[!ENDSELECT!]

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/


