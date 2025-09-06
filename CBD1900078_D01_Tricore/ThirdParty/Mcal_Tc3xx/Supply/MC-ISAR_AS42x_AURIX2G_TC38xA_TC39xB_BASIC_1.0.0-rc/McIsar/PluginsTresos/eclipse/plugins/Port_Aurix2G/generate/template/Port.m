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
**  FILENAME  : Port.m                                                        **
**                                                                            **
**  VERSION   : 4.0.0                                                         **
**                                                                            **
**  DATE      : 2018-09-17                                                    **
**                                                                            **
**  BSW MODULE DESCRIPTION : Port.bmd                                         **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={4BF71B29-3A9E-4f5c-A82F-273AC9579A51}]    **
**                                                                            **
**  DESCRIPTION  : Code template macro file for Port Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Port Driver, AUTOSAR Release 4.2.2    **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
*/!]

[!/*****************************************************************************
MACRO: Port_ConfigSwitch
Macro to generate configuration switch Values ON/OFF based on configuration
true/false
******************************************************************************/!]
[!MACRO "Port_ConfigSwitch", "node" =""!][!//
[!//
[!IF "$node = 'true'"!][!//
(STD_ON)[!//
[!ELSE!][!//
(STD_OFF)[!//
[!ENDIF!]
[!ENDMACRO!]

[!/*****************************************************************************
  Macro: Port_GetAvailablePorts00to31

  Macro to generate definition to indicate the ports that are available in the
  microcontroller

  Notes:
  The macro checks for the string Port_AvailablePorts for the ports that are
  available and the corresponding bits within the printed definition are set
  for all existing ports

  Input Parameters:
  None
*****************************************************************************/!]

[!MACRO "Port_GetAvailablePorts00to31"!][!//
[!NOCODE!][!//

  [!VAR "AvailablePorts" = "num:i(0)"!][!//

  [!FOR "PortNumber" = "0" TO "31"!]
    [!IF "($PortNumber = text:split(ecu:get('Port.AvailablePorts'), ' ' ))"!][!//
      [!VAR "AvailablePorts" = "bit:bitset($AvailablePorts, $PortNumber)"!][!//
    [!ENDIF!]`
  [!ENDFOR!]

[!ENDNOCODE!][!//
[!//
#define PORTS_AVAILABLE_00_31       ([!"num:inttohex($AvailablePorts, 8)"!]U)
[!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: Port_GetAvailablePorts32to63

  Macro to generate definition to indicate the ports that are available in the
  microcontroller

  Notes:
  The macro checks for the string Port_AvailablePorts for the ports that are
  available and the corresponding bits within the printed definition are set
  for all existing ports

  Input Parameters:
  None
*****************************************************************************/!]
[!MACRO "Port_GetAvailablePorts32to63"!][!//
[!NOCODE!][!//

  [!VAR "AvailablePorts" = "num:i(0)"!][!//

  [!FOR "PortNumber" = "32" TO "63"!]
    [!IF "($PortNumber = text:split(ecu:get('Port.AvailablePorts'), ' ' ))"!][!//
      [!VAR "AvailablePorts" = "bit:bitset($AvailablePorts, ($PortNumber -32))"!][!//
    [!ENDIF!]
  [!ENDFOR!]

[!ENDNOCODE!][!//
[!//
#define PORTS_AVAILABLE_32_63       ([!"num:inttohex($AvailablePorts, 8)"!]U)
[!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: Port_ReadOnlyPorts00to31

  Macro to generate definition to indicate the ports that are readonly in the
  microcontroller

  Notes:
  The macro checks for the string Port_AvailablePorts for the ports that are
  available and the corresponding bits within the printed definition are set
  for all existing ports

  Input Parameters:
  None
*****************************************************************************/!]
[!MACRO "Port_ReadOnlyPorts00to31"!][!//
[!NOCODE!][!//

  [!VAR "ReadOnlyPorts" = "num:i(0)"!][!//

  [!FOR "PortNumber" = "0" TO "31"!]
    [!IF "($PortNumber = text:split(ecu:get('Port.AvailableReadOnlyPorts'), ' ' ))"!][!//
      [!VAR "ReadOnlyPorts" = "bit:bitset($ReadOnlyPorts, $PortNumber)"!][!//
    [!ENDIF!]
  [!ENDFOR!]

[!ENDNOCODE!][!//
[!//
#define PORTS_READONLY_00_31       ([!"num:inttohex($ReadOnlyPorts, 8)"!]U)
[!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: Port_ReadOnlyPorts32to63

  Macro to generate definition to indicate the ports that are readonly in the
  microcontroller

  Notes:
  The macro checks for the string Port_ReadOnlyPorts for the ports that are
  available and the corresponding bits within the printed definition are set
  for all existing ports

  Input Parameters:
  None
*****************************************************************************/!]
[!MACRO "Port_ReadOnlyPorts32to63"!][!//
[!NOCODE!][!//

  [!VAR "ReadOnlyPorts" = "num:i(0)"!][!//

  [!FOR "PortNumber" = "32" TO "63"!]
    [!IF "($PortNumber = text:split(ecu:get('Port.AvailableReadOnlyPorts'), ' ' ))"!][!//
      [!VAR "ReadOnlyPorts" = "bit:bitset($ReadOnlyPorts, ($PortNumber -32))"!][!//
    [!ENDIF!]
  [!ENDFOR!]

[!ENDNOCODE!][!//
[!//
#define PORTS_READONLY_32_63       ([!"num:inttohex($ReadOnlyPorts, 8)"!]U)
[!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: Port_GetAvailablePortPins

  Macro to generate definition to indicate the port pins that are available
  in the microcontroller


  Input Parameters:
  None
*****************************************************************************/!]
[!MACRO "Port_GetAvailablePortPins"!][!//
[!FOR "PortNumber" = "0" TO "41"!][!//
[!VAR "AvailablePins" = "num:i(0)"!][!//
[!IF "($PortNumber = text:split(ecu:get('Port.AvailablePorts'), ' ' ))"!][!//
[!FOR "PinNum" = "0" TO "15"!][!//
[!IF "($PinNum = text:split(ecu:get(concat('Port.Port',$PortNumber,'_AvailablePins')), ' ' ))"!][!//
[!VAR "AvailablePins" = "bit:bitset($AvailablePins, ($PinNum))"!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
#define PORT_AVAILABLE_PINS_PORT[!"$PortNumber"!]        ([!"num:inttohex($AvailablePins, 4)"!]U)
[!ENDFOR!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: Port_GetLVDSPorts00to31

  Macro to generate definition to indicate ports which support LVDS of the uC

  Input Parameters:
  None
*****************************************************************************/!]
[!MACRO "Port_GetLVDSPorts00to31"!][!//
[!NOCODE!][!//

  [!VAR "LVDSPorts" = "num:i(0)"!][!//

  [!FOR "PortNumber" = "0" TO "31"!]
    [!IF "($PortNumber = text:split(ecu:get('Port.AvailableLVDSPorts'), ' ' ))"!][!//
      [!VAR "LVDSPorts" = "bit:bitset($LVDSPorts, $PortNumber)"!][!//
    [!ENDIF!]
  [!ENDFOR!]

[!ENDNOCODE!][!//
[!//
#define PORTS_LVDS_00_31       ([!"num:inttohex($LVDSPorts, 8)"!]U)
[!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: Port_GetLVDSPorts32to63

 Macro to generate definition to indicate ports which support LVDS of the uC

  Input Parameters:
  None
*****************************************************************************/!]
[!MACRO "Port_GetLVDSPorts32to63"!][!//
[!NOCODE!][!//

  [!VAR "LVDSPorts" = "num:i(0)"!][!//

  [!FOR "PortNumber" = "32" TO "63"!]
    [!IF "($PortNumber = text:split(ecu:get('Port.AvailableLVDSPorts'), ' ' ))"!][!//
      [!VAR "LVDSPorts" = "bit:bitset($LVDSPorts, ($PortNumber -32))"!][!//
    [!ENDIF!]
  [!ENDFOR!]

[!ENDNOCODE!][!//
[!//
#define PORTS_LVDS_32_63       ([!"num:inttohex($LVDSPorts, 8)"!]U)
[!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: Port_GetPCSRPorts00to31

Macro to generate definition to indicate ports which support PCSR of the uC



  Input Parameters:
  None
*****************************************************************************/!]
[!MACRO "Port_GetPCSRPorts00to31"!][!//
[!NOCODE!][!//

  [!VAR "PCSRPorts" = "num:i(0)"!][!//

  [!FOR "PortNumber" = "0" TO "31"!]
    [!IF "($PortNumber = text:split(ecu:get('Port.AvailablePCSRPorts'), ' ' ))"!][!//
      [!VAR "PCSRPorts" = "bit:bitset($PCSRPorts, $PortNumber)"!][!//
    [!ENDIF!]
  [!ENDFOR!]

[!ENDNOCODE!][!//
[!//
#define PORTS_PCSR_00_31       ([!"num:inttohex($PCSRPorts, 8)"!]U)
[!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: Port_GetPCSRPorts32to63

Macro to generate definition to indicate ports which support PCSR of the uC




  Input Parameters:
  None
*****************************************************************************/!]
[!MACRO "Port_GetPCSRPorts32to63"!][!//
[!NOCODE!][!//

  [!VAR "PCSRPorts" = "num:i(0)"!][!//

  [!FOR "PortNumber" = "32" TO "63"!]
    [!IF "($PortNumber = text:split(ecu:get('Port.AvailablePCSRPorts'), ' ' ))"!][!//
      [!VAR "PCSRPorts" = "bit:bitset($PCSRPorts, ($PortNumber -32))"!][!//
    [!ENDIF!]
  [!ENDFOR!]

[!ENDNOCODE!][!//
[!//
#define PORTS_PCSR_32_63       ([!"num:inttohex($PCSRPorts, 8)"!]U)
[!//
[!ENDMACRO!][!//


[!/*****************************************************************************
  Macro: Port_GetPortPinSymbolicName

 Gets the Port Pin attributes : Direction, Characteristic and pin mode.
Input Prameters:
port: The Port Id
pinstart: The Starting Pin id of the Port
pinend: The ending Pin id of the Port
*****************************************************************************/!]
[!/*[cover parentID={E418C221-8B1C-44f6-907E-790B38AE995E}][/cover]*/!][!//
[!MACRO "Port_GetPortPinSymbolicName", "port"=""!][!//
                   
/*   
   Port[!"$PortNumber"!]   
*/ 
  
[!//
[!FOR "PortPinNo" = "0" TO "15"!][!//
[!VAR "PinId" = "num:i($port) * num:i(16)"!][!//
[!VAR "PinId" = "num:i($PinId) + num:i($PortPinNo)"!][!//
[!VAR "PinId" = "num:i($PinId)"!][!//
[!/*
  Select the container for the calculated PinId to extract the configuration
*/!][!//
[!SELECT "PortConfigSet/PortContainer/*/PortPin/*[PortPinId = num:i($PinId)]"!][!//
[!//
/* Symbolic Name: [!"PortPinSymbolicName"!] */
/*MISRA2012_RULE_5_1_JUSTIFICATION:
MISRA2012_RULE_5_2_JUSTIFICATION:
MISRA2012_RULE_5_4_JUSTIFICATION:
MISRA2012_RULE_5_5_JUSTIFICATION: decomposition of name is not possible,
Further distinct name can not be given*/
#ifndef PortConf_[!"node:name(../../.)"!]_[!"PortPinSymbolicName"!] 
/*MISRA2012_RULE_5_1_JUSTIFICATION:
MISRA2012_RULE_5_2_JUSTIFICATION:
MISRA2012_RULE_5_4_JUSTIFICATION:
MISRA2012_RULE_5_5_JUSTIFICATION: decomposition of name is not possible,
Further distinct name can not be given*/
#define PortConf_[!"node:name(../../.)"!]_[!"PortPinSymbolicName"!]  (Port_PinType )([!"num:inttohex($PinId,4)"!]U)
#endif
[!ENDSELECT!][!//
[!ENDFOR!][!//
[!ENDMACRO!][!//


[!/*****************************************************************************
  Macro: Port_GetPortPinDirectionAndModeAttributes

 Gets the Port Pin attributes : Direction, Characteristic and pin mode.
Input Prameters:
port: The Port Id
pinstart: The Starting Pin id of the Port
pinend: The ending Pin id of the Port
*****************************************************************************/!]
[!/*[cover parentID={DEE24C2F-1A2D-4f68-9DA4-79665488E6E1}][/cover]*/!][!//
[!MACRO "Port_GetPortPinDirectionAndModeAttributes", "port"=""!][!//
[!//
[!NOCODE!]
[!FOR "PortPinNo" = "0" TO "15"!][!//
[!VAR "PinId" = "num:i($port) * num:i(16)"!][!//
[!VAR "PinId" = "num:i($PinId) + num:i($PortPinNo)"!][!//
[!IF "node:exists(PortConfigSet/PortContainer/*/PortPin/*[PortPinId = num:i($PinId)])"!][!//
[!/*
  Select the container for the calculated PinId to extract the configuration
*/!][!//
[!SELECT "PortConfigSet/PortContainer/*/PortPin/*[PortPinId = num:i($PinId)]"!][!//
[!//
[!//
[!//
[!CODE!][!//
/* MISRA2012_RULE_10_3_JUSTIFICATION: Union is needed to access data 
per port pin and as a 32 Bit Value*/
  ((uint8)[!"PortPinDirection"!] | [!//
[!ENDCODE!][!//
[!IF "PortPinDirection = 'PORT_PIN_IN'"!][!//
[!CODE!][!//
[!"PortPinInputPullResistor"!] | [!//
[!ENDCODE!][!//
[!ELSE!][!//
[!CODE!][!//
[!"PortPinOutputPinDriveMode"!] | [!//
[!ENDCODE!][!//
[!ENDIF!][!//
[!VAR "PinMode" = "PortPinInitialMode"!][!//
[!CODE!][!//
PORT_PIN_MODE_[!"$PinMode"!])[!//
[!ENDCODE!][!//
[!ENDSELECT!][!//
[!ELSE!][!//
[!CODE!][!//
  (PORT_PIN_DEFAULT)[!//
[!ENDCODE!][!//
[!ENDIF!][!//
[!IF "num:i($PortPinNo) != num:i(15)"!][!//
[!CODE!][!//
,/*Pin [!"num:i($PortPinNo)"!]*/
[!ENDCODE!][!//
[!ELSE!][!//
[!CODE!][!//
/*Pin [!"num:i($PortPinNo)"!]*/[!//
[!ENDCODE!][!//
[!ENDIF!]
[!ENDFOR!][!//
[!ENDNOCODE!]
[!ENDMACRO!][!//

[!/******************************************************************************
MACRO: Port_GetPortPinLevelAttributes
Gets the Port Pin level attributes 
Input Prameters:
port: The Port Id
pinstart: The Starting Pin id of the Port
pinend: The ending Pin id of the Port
******************************************************************************/!]
[!/*[cover parentID={B8949F21-5848-4209-93B3-294A4594235A}][/cover]*/!][!//
[!MACRO "Port_GetPortPinLevelAttributes", "port"=""!][!//
[!//
[!FOR "PortPinNo" = "0" TO "15"!][!//
[!VAR "PinId" = "num:i($port) * num:i(16)"!][!//
[!VAR "PinId" = "num:i($PinId) + num:i($PortPinNo)"!][!//
[!IF "node:exists(PortConfigSet/PortContainer/*/PortPin/*[PortPinId = num:i($PinId)])"!][!//
[!/*
  Select the container for the calculated PinId to extract the configuration
*/!][!//
[!SELECT "PortConfigSet/PortContainer/*/PortPin/*[PortPinId = num:i($PinId)]"!][!//
[!IF "PortPinLevelValue = 'PORT_PIN_LEVEL_LOW'"!][!//
         PORT_PIN_LEVEL_LOW[!//
[!ELSE!][!//
         PORT_PIN_LEVEL_HIGH[!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ELSE!][!//
         0U[!//
[!ENDIF!][!//
[!IF "num:i($PortPinNo) < num:i(15)"!][!//
,/* Pin [!"num:i($PortPinNo)"!] */ [!//
[!ELSE!][!//
 /* Pin [!"num:i($PortPinNo)"!] */ [!//
[!ENDIF!]
[!ENDFOR!][!//
[!ENDMACRO!][!//

[!/******************************************************************************
MACRO: Port_GetPortPinDirectionChangeable
Gets the Port Pin DirectionChangeable attributes
Input Prameters:
port: The Port Id
pinstart: The Starting Pin id of the Port
pinend: The ending Pin id of the Port
******************************************************************************/!]
[!/*[cover parentID={C77D6AA0-471F-4658-8925-24844A8A19FA}][/cover]*/!][!//
[!MACRO "Port_GetPortPinDirectionChangeable", "port"=""!][!//
[!//
[!FOR "PortPinNo" = "0" TO "15"!][!//
[!VAR "PinId" = "num:i($port) * num:i(16)"!][!//
[!VAR "PinId" = "num:i($PinId) + num:i($PortPinNo)"!][!//
[!IF "node:exists(PortConfigSet/PortContainer/*/PortPin/*[PortPinId = num:i($PinId)])"!][!//
[!/*
  Select the container for the calculated PinId to extract the configuration
*/!][!//
[!SELECT "PortConfigSet/PortContainer/*/PortPin/*[PortPinId = num:i($PinId)]"!][!//
[!IF "PortPinDirectionChangeable = 'true'"!][!//
         PORT_PIN_DIRECTION_CHANGEABLE [!//
[!ELSE!][!//
         PORT_PIN_DIRECTION_NOT_CHANGEABLE [!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ELSE!][!//
         PORT_PIN_DIRECTION_NOT_CHANGEABLE [!//
[!ENDIF!][!//
[!IF "num:i($PortPinNo) != num:i(15)"!][!//
,/* Pin [!"num:i($PortPinNo)"!] */ [!//
[!ELSE!][!//
 /* Pin [!"num:i($PortPinNo)"!] */ [!//
[!ENDIF!]
[!ENDFOR!][!//
[!ENDMACRO!][!//

[!/******************************************************************************
MACRO: Port_GetPortPinModeChangeable
Gets the Port Pin ModeChangeabl attributes.
Input Prameters:
port: The Port Id
pinstart: The Starting Pin id of the Port
pinend: The ending Pin id of the Port
******************************************************************************/!]
[!/*[cover parentID={0B3C7BCE-6E6A-4d30-B386-4F056BFB4721}][/cover]*/!][!//
[!MACRO "Port_GetPortPinModeChangeable", "port"=""!][!//
[!//
[!FOR "PortPinNo" = "0" TO "15"!][!//
[!VAR "PinId" = "num:i($port) * num:i(16)"!][!//
[!VAR "PinId" = "num:i($PinId) + num:i($PortPinNo)"!][!//
[!IF "node:exists(PortConfigSet/PortContainer/*/PortPin/*[PortPinId = num:i($PinId)])"!][!//
[!/*
  Select the container for the calculated PinId to extract the configuration
*/!][!//
[!SELECT "PortConfigSet/PortContainer/*/PortPin/*[PortPinId = num:i($PinId)]"!][!//
[!IF "PortPinModeChangeable = 'true'"!][!//
         PORT_PIN_MODE_CHANGEABLE [!//
[!ELSE!][!//
         PORT_PIN_MODE_NOT_CHANGEABLE [!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ELSE!][!//
         PORT_PIN_MODE_NOT_CHANGEABLE [!//
[!ENDIF!][!//
[!IF "num:i($PortPinNo) != num:i(15)"!][!//
,/* Pin [!"num:i($PortPinNo)"!] */ [!//
[!ELSE!][!//
 /* Pin [!"num:i($PortPinNo)"!] */ [!//
[!ENDIF!]
[!ENDFOR!][!//
[!ENDMACRO!][!//

[!/******************************************************************************
MACRO: Port_GetPortPinDirectionChangeableAttributes
Gets the Port Pin attributes : Direction, Characteristic and pin mode if DirectionChangeable is true for pin
Input Prameters:
port: The Port Id
pinstart: The Starting Pin id of the Port
pinend: The ending Pin id of the Port
******************************************************************************/!]
[!/*[cover parentID={D735FAF8-BC32-48d9-B147-2CA1AA260B58}][/cover]*/!][!//
[!MACRO "Port_GetPortPinDirectionChangeableAttributes", "port"=""!][!//
[!//
[!FOR "PortPinNo" = "0" TO "15"!][!//
[!VAR "PinId" = "num:i($port) * num:i(16)"!][!//
[!VAR "PinId" = "num:i($PinId) + num:i($PortPinNo)"!][!//
[!IF "node:exists(PortConfigSet/PortContainer/*/PortPin/*[PortPinId = num:i($PinId)])"!][!//
[!/*
  Select the container for the calculated PinId to extract the configuration
*/!][!//
/* MISRA2012_RULE_10_3_JUSTIFICATION: Union is needed to access data 
per port pin and as a 32 Bit Value*/
[!SELECT "PortConfigSet/PortContainer/*/PortPin/*[PortPinId = num:i($PinId)]"!][!//
[!//
[!IF "PortPinDirectionChangeable = 'false'"!][!//
[!IF "PortPinDirection = 'PORT_PIN_IN'"!][!//
  ((uint8)PORT_PIN_IN | [!//
[!"PortPinInputPullResistor"!] | [!//
[!ELSE!][!//
  ((uint8)PORT_PIN_OUT | [!//
[!"PortPinOutputPinDriveMode"!] | [!//
[!ENDIF!][!//
[!VAR "PinMode" = "PortPinInitialMode"!][!//
PORT_PIN_MODE_[!"$PinMode"!])[!//
[!ELSE!][!//
[!IF "PortPinDirection = 'PORT_PIN_IN'"!][!//
  ((uint8)PORT_PIN_OUT | [!//
[!"PortPinOutputPinDriveMode "!] | [!//
[!ELSE!][!//
  ((uint8)PORT_PIN_IN | [!//
[!"PortPinInputPullResistor"!] | [!//
[!ENDIF!][!//
PORT_PIN_MODE_GPIO)[!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ELSE!][!//
  (PORT_PIN_DEFAULT)[!//
[!ENDIF!][!//
[!IF "num:i($PortPinNo) != num:i(15)"!][!//
,/*Pin[!"num:i($PortPinNo)"!]*/[!//
[!ELSE!][!//
/*Pin[!"num:i($PortPinNo)"!]*/[!//
[!ENDIF!]
[!ENDFOR!][!//
[!ENDMACRO!][!//

[!/******************************************************************************
MACRO: Port_GetPortPinDriverStrength1
Gets the Port Pin attributes : Level and Strength.
Input Prameters:
port: The Port Id
pinstart: The Starting Pin id of the Port
pinend: The ending Pin id of the Port
******************************************************************************/!]
[!/*[cover parentID={2BECFF43-D972-4a0e-BB0E-618DE44A6D10}][/cover]*/!][!//
[!MACRO "Port_GetPortPinDriverStrength1", "port"=""!][!//
[!//
[!NOCODE!]
[!FOR "PortPinNo" = "0" TO "7"!][!//
[!VAR "PinId" = "num:i($port) * num:i(16)"!][!//
[!VAR "PinId" = "num:i($PinId) + num:i($PortPinNo)"!][!//
[!IF "node:exists(PortConfigSet/PortContainer/*/PortPin/*[PortPinId = num:i($PinId)])"!][!//
[!/*
  Select the container for the calculated PinId to extract the configuration
*/!][!//
[!SELECT "PortConfigSet/PortContainer/*/PortPin/*[PortPinId = num:i($PinId)]"!][!//

[!IF "(PortPinDirection = 'PORT_PIN_OUT') or ($port = num:i(11))"!][!//
  [!IF "(concat('_',($PinId)mod 16,'_') = text:split(ecu:get(concat('Port_',($port),'_SLOW')), ' ' ))"!][!//
    [!VAR "PadStrength" = "PortPinOutputPadDriveStrength"!][!//
    [!CODE!][!//
      (PORT_PIN_PAD_LEVEL_DEFAULT|SLOW_[!"$PadStrength"!])[!//
    [!ENDCODE!][!//
  [!ENDIF!]
  [!IF "(concat('_',($PinId)mod 16,'_') = text:split(ecu:get(concat('Port_',($port),'_FAST')), ' ' ))"!][!//
    [!VAR "PadStrength" = "PortPinOutputPadDriveStrength"!][!//
    [!CODE!][!//
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_[!"$PadStrength"!])[!//
    [!ENDCODE!][!//
  [!ENDIF!]
  [!IF "(concat('_',($PinId)mod 16,'_') = text:split(ecu:get(concat('Port_',($port),'_RFAST')), ' ' ))"!][!//
    [!VAR "PadStrength" = "PortPinOutputPadDriveStrength"!][!//
    [!CODE!][!//
      (PORT_PIN_PAD_LEVEL_DEFAULT|RFAST_[!"$PadStrength"!])[!//
    [!ENDCODE!][!//
  [!ENDIF!]
[!ELSE!][!//

 [!VAR "PadLevel" = "PortPinInputPadLevel"!][!//
  [!CODE!][!//
    ([!"$PadLevel"!]|PORT_PIN_PAD_STRENGTH_DEFAULT)[!//
  [!ENDCODE!][!//

[!ENDIF!][!//
[!ENDSELECT!] 
[!ELSE!][!//
[!CODE!][!//
  (PORT_PIN_PAD_DEFAULT)[!//
[!ENDCODE!][!//
[!ENDIF!][!//

[!IF "num:i($PortPinNo) != num:i(7)"!][!//
[!CODE!][!//
,/*Pin[!"num:i($PortPinNo)"!]*/[!// 
[!ENDCODE!][!//
[!ELSE!][!//
[!CODE!][!//
/*Pin[!"num:i($PortPinNo)"!]*/
[!ENDCODE!][!//
[!ENDIF!]
[!ENDFOR!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!/******************************************************************************
MACRO: Port_GetPortPinDriverStrength2
Gets the Port Pin attributes : Port pin Level and strength.
Input Prameters:
port: The Port Id
pinstart: The Starting Pin id of the Port
pinend: The ending Pin id of the Port
******************************************************************************/!]
[!/*[cover parentID={E0701679-1C22-4b0d-B433-6162BAD7573F}][/cover]*/!][!//
[!MACRO "Port_GetPortPinDriverStrength2", "port"=""!][!//
[!//
[!NOCODE!]
[!FOR "PortPinNo" = "8" TO "15"!][!//
[!VAR "PinId" = "num:i($port) * num:i(16)"!][!//
[!VAR "PinId" = "num:i($PinId) + num:i($PortPinNo)"!][!//
[!IF "node:exists(PortConfigSet/PortContainer/*/PortPin/*[PortPinId = num:i($PinId)])"!][!//
[!/*
  Select the container for the calculated PinId to extract the configuration
*/!][!//
[!SELECT "PortConfigSet/PortContainer/*/PortPin/*[PortPinId = num:i($PinId)]"!][!//
[!IF "(PortPinDirection = 'PORT_PIN_OUT') or ($port = num:i(11))"!][!//
  [!IF "(concat('_',($PinId)mod 16,'_') = text:split(ecu:get(concat('Port_',($port),'_SLOW')), ' ' ))"!][!//
    [!VAR "PadStrength" = "PortPinOutputPadDriveStrength"!][!//
    [!CODE!][!//
      (PORT_PIN_PAD_LEVEL_DEFAULT|SLOW_[!"$PadStrength"!])[!//
    [!ENDCODE!][!//
  [!ENDIF!]
  [!IF "(concat('_',($PinId)mod 16,'_') = text:split(ecu:get(concat('Port_',($port),'_FAST')), ' ' ))"!][!//
    [!VAR "PadStrength" = "PortPinOutputPadDriveStrength"!][!//
    [!CODE!][!//
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_[!"$PadStrength"!])[!//
    [!ENDCODE!][!//
  [!ENDIF!]
  [!IF "(concat('_',($PinId)mod 16,'_') = text:split(ecu:get(concat('Port_',($port),'_RFAST')), ' ' ))"!][!//
    [!VAR "PadStrength" = "PortPinOutputPadDriveStrength"!][!//
    [!CODE!][!//
      (PORT_PIN_PAD_LEVEL_DEFAULT|RFAST_[!"$PadStrength"!])[!//
    [!ENDCODE!][!//
  [!ENDIF!]
[!ELSE!][!//

 [!VAR "PadLevel" = "PortPinInputPadLevel"!][!//
  [!CODE!][!//
    ([!"$PadLevel"!]|PORT_PIN_PAD_STRENGTH_DEFAULT)[!//
  [!ENDCODE!][!//

[!ENDIF!][!//
[!ENDSELECT!] 
[!ELSE!][!//
[!CODE!][!//
  (PORT_PIN_PAD_DEFAULT)[!//
[!ENDCODE!][!//
[!ENDIF!][!//

[!IF "num:i($PortPinNo) != num:i(15)"!][!//
[!CODE!][!//
,/*Pin[!"num:i($PortPinNo)"!]*/[!// 
 [!ENDCODE!][!//
[!ELSE!][!//
[!CODE!][!//
/*Pin[!"num:i($PortPinNo)"!]*/
[!ENDCODE!][!//
[!ENDIF!]
[!ENDFOR!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/******************************************************************************
MACRO: Port_GetPortPinAnalogInputSelection
Gets the Port Pin attributes : Analog input Enabled or not
Input Prameters:
port: The Port Id
pinstart: The Starting Pin id of the Port
pinend: The ending Pin id of the Port
******************************************************************************/!]
[!/*[cover parentID={9EF26D41-160F-4f7c-B4BD-3B5625B90CCD}][/cover]*/!][!//
[!MACRO "Port_GetPortPinAnalogInputSelection", "port"=""!][!//
[!//
[!FOR "PortPinNo" = "0" TO "15"!][!//
[!VAR "PinId" = "num:i($port) * num:i(16)"!][!//
[!VAR "PinId" = "num:i($PinId) + num:i($PortPinNo)"!][!//
[!IF "node:exists(PortConfigSet/PortContainer/*/PortPin/*[PortPinId = num:i($PinId)])"!][!//
[!/*
  Select the container for the calculated PinId to extract the configuration
*/!][!//
[!SELECT "PortConfigSet/PortContainer/*/PortPin/*[PortPinId = num:i($PinId)]"!][!//
[!IF "PortPinEnableAnalogInputOnly  = 'PORT_PIN_ANALOG_INPUT_ENABLE'"!][!//
                PORT_PIN_ANALOG_INPUT_ENABLE[!//
[!ELSE!][!//
                PORT_PIN_ANALOG_INPUT_DISABLE[!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ELSE!][!//
                PORT_PIN_ANALOG_INPUT_DISABLE[!//
[!ENDIF!][!//
[!IF "num:i($PortPinNo) != num:i(15)"!][!//
,/* Pin [!"num:i($PortPinNo)"!] */ [!//
[!ELSE!][!//
 /* Pin [!"num:i($PortPinNo)"!] */ [!//
[!ENDIF!]
[!ENDFOR!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
MACRO: Port_GetPortPinMode
Sets the array for the modes supported by the port pin
Input Prameters:
port: The Port Id
*****************************************************************************/!]
[!/*[cover parentID={255B7AE8-0E2A-43d1-947D-DE7AA20D5821} ][/cover]*/!][!//
[!MACRO "Port_GetPortPinMode", "port" = ""!][!//
[!NOCODE!][!//
[!FOR "PortPinNo" = "0" TO "15"!][!//
  [!VAR "PinId" = "num:i($port) * num:i(16)"!][!//
  [!VAR "PinId" = "num:i($PinId) + num:i($PortPinNo)"!][!//

    [!IF "node:exists(PortConfigSet/PortContainer/*/PortPin/*[PortPinId = num:i($PinId)])"!][!//
                [!VAR "PortPinHwSupportModes" = "num:i(0)"!][!//

                [!LOOP "PortConfigSet/PortContainer/*/PortPin/*[PortPinId = num:i($PinId)]/PortPinMode/*"!][!//

                  [!IF ". = 'PORT_PIN_MODE_GPIO'"!][!//
                    [!VAR "PortPinHwSupportModes"= "bit:or($PortPinHwSupportModes,num:i(1))"!][!//
                  [!ELSEIF ". = 'PORT_PIN_MODE_ALT1'"!][!//
                    [!VAR "PortPinHwSupportModes"= "bit:or($PortPinHwSupportModes,num:i(2))"!][!//
                  [!ELSEIF ". = 'PORT_PIN_MODE_ALT2'"!][!//
                    [!VAR "PortPinHwSupportModes"= "bit:or($PortPinHwSupportModes,num:i(4))"!][!//
                  [!ELSEIF ". = 'PORT_PIN_MODE_ALT3'"!][!//
                    [!VAR "PortPinHwSupportModes"= "bit:or($PortPinHwSupportModes,num:i(8))"!][!//
                  [!ELSEIF ". = 'PORT_PIN_MODE_ALT4'"!][!//
                    [!VAR "PortPinHwSupportModes"= "bit:or($PortPinHwSupportModes,num:i(16))"!][!//
                  [!ELSEIF ". = 'PORT_PIN_MODE_ALT5'"!][!//
                    [!VAR "PortPinHwSupportModes"= "bit:or($PortPinHwSupportModes,num:i(32))"!][!//
                  [!ELSEIF ". = 'PORT_PIN_MODE_ALT6'"!][!//
                    [!VAR "PortPinHwSupportModes"= "bit:or($PortPinHwSupportModes,num:i(64))"!][!//
                  [!ELSEIF ". = 'PORT_PIN_MODE_ALT7'"!][!//
                    [!VAR "PortPinHwSupportModes"= "bit:or($PortPinHwSupportModes,num:i(128))"!][!//
                  [!ELSEIF ". = 'PORT_PIN_MODE_ALL'"!][!//
                    [!VAR "CurPortPinHwSupportModes"= "num:i(1)"!][!//
                    [!VAR "PortPinHwSupportModes"= "$CurPortPinHwSupportModes"!][!//
                      [!FOR "PortPinModeIndex" = "1" TO "7"!][!//
                      [!VAR "CurPortPinHwSupportModes"= "bit:shl($CurPortPinHwSupportModes,num:i(1))"!][!//
                        [!IF "
                          not((contains(ecu:get(concat('Port.InitialModes',(../../../../PortNumber),'_',((../../PortPinId) mod 16))),
                            concat('ALT',$PortPinModeIndex,'_Reserved'))
                             ) or (contains(ecu:get(concat('Port.InitialModes',(../../../../PortNumber),'_',((../../PortPinId) mod 16))),
                            concat('ALT',$PortPinModeIndex,'_RESERVED'))
                             ))
                        "!][!//
                        [!VAR "PortPinHwSupportModes"= "bit:or($PortPinHwSupportModes,$CurPortPinHwSupportModes)"!][!//
                        [!ENDIF!]
                      [!ENDFOR!]
                  [!ENDIF!]
                [!ENDLOOP!][!//
[!CODE!][!//
      (uint8)([!"num:inttohex($PortPinHwSupportModes, 2)"!]U)[!//
[!ENDCODE!][!//
                [!IF "num:i($PortPinNo) != num:i(15)"!][!//
[!CODE!][!//
,/*Pin[!"num:i($PortPinNo)"!]*/
[!ENDCODE!][!//
                [!ELSE!][!//
[!CODE!][!//
 /*Pin[!"num:i($PortPinNo)"!]*/[!//
[!ENDCODE!][!//
                [!ENDIF!][!//
    [!ELSE!][!//
[!CODE!][!//
      (uint8)(0x00U)[!//
[!ENDCODE!][!//
        [!IF "num:i($PortPinNo) != num:i(15)"!][!//
[!CODE!][!//
,/*Pin[!"num:i($PortPinNo)"!]*/
[!ENDCODE!][!//
        [!ELSE!][!//
[!CODE!][!//
 /*Pin[!"num:i($PortPinNo)"!]*/[!//
[!ENDCODE!][!//
        [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDFOR!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: Port_GetPCSRPads
  Macro to generate Port_PCSRConfigType for all the Ports
  Input Parameters: Configset instance.
  None
*****************************************************************************/!]
[!/*[cover parentID={85A84934-FD7E-4460-8FEC-958221529BE2}][/cover]*/!][!//
[!MACRO "Port_GetPCSRPads"!][!//
[!NOCODE!][!//
[!VAR "counter" = "count(text:split(ecu:get('Port.AvailablePCSRPorts'),' '))"!]
[!SELECT "as:modconf('Port')[1]"!][!//
  [!LOOP "node:order(PortConfigSet/PortContainer/*,'node:value(./PortNumber)')"!][!//
[!IF "(./PortNumber = text:split(ecu:get('Port.AvailablePCSRPorts'), ' ' ))"!][!//
      [!VAR "counter" = "num:i(num:sub($counter,1))"!]
[!CODE!][!//

               /*           Port[!"./PortNumber"!]            */
   Port_lPcsr(
[!ENDCODE!][!//
      [!FOR "PortPinNo" = "0" TO "15"!][!//
          [!IF "text:contains(text:split(ecu:get(concat('Port.Port',./PortNumber,'_AvailablePinPCSR')),' '),$PortPinNo)"!]
            [!VAR "PortHolder" = "num:i(./PortNumber)"!]
            [!SELECT "as:modconf('Port')[1]/PortConfigSet/PortContainer/*/PortPin/*[PortPinId = num:add(num:mul($PortHolder,16),$PortPinNo)]"!][!//
              [!IF "./PortPinControllerSelect  = 'DISABLE'"!]
                [!IF "$PortPinNo = num:i(15)"!]
[!CODE!][!//
               PORT_PCSR_DISABLE   /*Pin[!"$PortPinNo"!]*/
[!ENDCODE!][!//
                [!ELSE!]
[!CODE!][!//
               PORT_PCSR_DISABLE,  /*Pin[!"$PortPinNo"!]*/
[!ENDCODE!][!//
                [!ENDIF!]
              [!ELSE!]
                [!IF "$PortPinNo = num:i(15)"!]
[!CODE!][!//
               PORT_PCSR_ENABLE    /*Pin[!"$PortPinNo"!]*/
[!ENDCODE!][!//
                [!ELSE!]
[!CODE!][!//
               PORT_PCSR_ENABLE,   /*Pin[!"$PortPinNo"!]*/
[!ENDCODE!][!//
                [!ENDIF!]
              [!ENDIF!]
            [!ENDSELECT!]
          [!ELSE!]
            [!IF "$PortPinNo = num:i(15)"!]
[!CODE!][!//
               PORT_PCSR_DEFAULT   /*Pin[!"$PortPinNo"!]*/
[!ENDCODE!][!//
            [!ELSE!]
[!CODE!][!//
               PORT_PCSR_DEFAULT,  /*Pin[!"$PortPinNo"!]*/
[!ENDCODE!][!//
            [!ENDIF!]
          [!ENDIF!]
      [!ENDFOR!]
          [!IF "$counter = num:i(0)"!]
[!CODE!][!//
              )
[!ENDCODE!][!//
          [!ELSE!]
[!CODE!][!//
              ),
[!ENDCODE!][!//
          [!ENDIF!]
    [!ENDIF!]
 [!ENDLOOP!]
[!ENDSELECT!]
[!ENDNOCODE!][!//
[!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: Port_GetLVDSPads
  Macro to generate Port_LVDSConfigType for all the Ports
  Input Parameters: Configset instance.
  None
*****************************************************************************/!]
[!/*[cover parentID={94D3810A-6487-4d29-897A-41B728D37B58}][/cover]*/!][!//
[[!MACRO "Port_GetLVDSPads"!][!//
[!//
[!NOCODE!][!//
[!VAR "MaxLPCR" = "num:i(ecu:get('Port.MaxLPCRReg'))"!]
[!VAR "NoOfLvdsReg" = "num:i(num:mul(count(text:split(ecu:get('Port.AvailableLVDSPorts'),' ')),ecu:get('Port.MaxLPCRReg')))"!]
[!SELECT "as:modconf('Port')[1]"!][!//
  [!LOOP "node:order(PortConfigSet/PortContainer/*,'node:value(./PortNumber)')"!][!//
  [!IF "(./PortNumber = text:split(ecu:get('Port.AvailableLVDSPorts'), ' ' ))"!][!//
[!CODE!][!//
  { /*             Port[!"./PortNumber"!]            */
[!ENDCODE!][!//
[!FOR "LPCRReg" ="num:i(0)" TO "num:sub(num:i(ecu:get('Port.MaxLPCRReg')),1)"!]
[!CODE!][!//
/*             LPCR[!"$LPCRReg"!]            */


[!ENDCODE!][!//
[!IF "text:contains(text:split(ecu:get(concat('Port.Port',./PortNumber,'AvailablePinPairLVDS')),'_'),num:i(num:mul(num:i($LPCRReg),2)))"!][!//
[!CODE!][!//
    Port_lLvds(
[!ENDCODE!][!//
       [!VAR "Holder" = "@name"!]
       [!LOOP "as:modconf('Port')[1]/PortConfigSet/PortContainer/*[@name = $Holder]/PortLVDS/*[PortLVDSPinPair] "!][!//[!//
[!VAR "PinPair" = "num:i(num:mul(num:i($LPCRReg),2))"!]
[!IF "$PinPair = text:split(./PortLVDSPinPair,'_')"!]
[!IF "./PortLVDSPinPair = text:split(ecu:get(concat('Port.Port_',node:current()/../../PortNumber,'_AvailablePinPairLVDSRx')),' ')"!]
         [!IF "./PortLVDSRxEnController = 'PORT_CONTROLLED' "!]
[!CODE!][!//
                  PORT_LVDS_PORT_CONTROLLED,
[!ENDCODE!][!//
             [!ELSE!]
[!CODE!][!//
                  PORT_LVDS_HSCT_CONTROLLED,
[!ENDCODE!][!//
             [!ENDIF!]
             [!IF "./PortLVDSRxPathEnable = 'false' "!]
[!CODE!][!//
                  PORT_LVDS_DISABLE,
[!ENDCODE!][!//
             [!ELSE!]
[!CODE!][!//
                  PORT_LVDS_ENABLE,
[!ENDCODE!][!//
             [!ENDIF!]
             [!IF "./PortLVDSRxTerminationMode = 'INTERNAL_TERMINATION' "!]
[!CODE!][!//
                  PORT_LVDS_INTERNAL_TERMINATION,
[!ENDCODE!][!//
             [!ELSE!]
[!CODE!][!//
                  PORT_LVDS_EXTERNAL_TERMINATION,
[!ENDCODE!][!//
             [!ENDIF!]
[!CODE!][!//
                  PORT_LVDS_POLY_RESISTOR_TERM,
[!ENDCODE!][!//
[!IF "./PortLVDSMode = 'LVDSH' "!]
[!CODE!][!//
                  PORT_LVDS_LVDSH,
[!ENDCODE!][!//
             [!ELSE!]
[!CODE!][!//
                  PORT_LVDS_LVDSM,
[!ENDCODE!][!//
             [!ENDIF!]
             [!IF "./PortLVDSPadSupply = 'V3_3' "!]
[!CODE!][!//
                  PAD_SUPPLY_3_3V,
[!ENDCODE!][!//
             [!ELSE!]
[!CODE!][!//
                  PAD_SUPPLY_5_0V,
[!ENDCODE!][!//
             [!ENDIF!]
[!CODE!][!//
                  PORT_LVDS_DEFAULT,
                  PORT_LVDS_DEFAULT,
                  PORT_LVDS_DEFAULT,
                  PORT_LVDS_DEFAULT,
                  PORT_LVDS_DEFAULT,
                  PORT_LVDS_DEFAULT,
                  PORT_LVDS_DEFAULT
[!ENDCODE!][!//
[!ENDIF!]
[!IF "./PortLVDSPinPair = text:split(ecu:get(concat('Port.Port',node:current()/../../PortNumber,'_AvailablePinPairLVDSTx')),' ')"!]

[!CODE!][!//
                  PORT_LVDS_DEFAULT,
                  PORT_LVDS_DEFAULT,
                  PORT_LVDS_DEFAULT,
                  PORT_LVDS_DEFAULT,
                  PORT_LVDS_DEFAULT,
[!ENDCODE!][!//
             [!IF "./PortLVDSPadSupply = 'V3_3' "!][!//
[!CODE!][!//
                  PAD_SUPPLY_3_3V,
[!ENDCODE!][!//
             [!ELSE!]
[!CODE!][!//
                  PAD_SUPPLY_5_0V,
[!ENDCODE!][!//
             [!ENDIF!]

         [!IF "./PortLVDSTxEnController = 'PORT_CONTROLLED' "!][!//
[!CODE!][!//
                  PORT_LVDS_PORT_CONTROLLED,
[!ENDCODE!][!//
             [!ELSE!]
[!CODE!][!//
                  PORT_LVDS_HSCT_CONTROLLED,
[!ENDCODE!][!//
             [!ENDIF!]
             [!IF "./PortLVDSTxPathEnable = 'false' "!][!//
[!CODE!][!//
                  PORT_LVDS_DISABLE,
[!ENDCODE!][!//
             [!ELSE!]
[!CODE!][!//
                  PORT_LVDS_ENABLE,
[!ENDCODE!][!//
             [!ENDIF!]
[!CODE!][!//
                  PORT_LVDS_LVDS_VDIFF_ADJ,
                  PORT_LVDS_VOSDYN,
                  PORT_LVDS_VOSEXT,
                  PORT_LVDS_POWER_DOWN,
[!ENDCODE!][!//
[!IF "./PortLVDSTxPowerDownPullDown = 'DISABLE' "!][!//
[!CODE!][!//
                  PORT_LVDS_TX_PWDPD_DISABLE
[!ENDCODE!][!//
             [!ELSE!]
[!CODE!][!//
                  PORT_LVDS_TX_PWDPD_ENABLE
[!ENDCODE!][!//
             [!ENDIF!]
[!ENDIF!]
[!ENDIF!]
       [!ENDLOOP!]
       [!IF "$LPCRReg < num:i(num:sub($MaxLPCR,1))"!][!//
[!CODE!][!//
                ),
[!ENDCODE!][!//
       [!ELSE!]
[!CODE!][!//
                )
[!ENDCODE!][!//
       [!ENDIF!]     
     [!ELSE!][!//
       [!IF "$LPCRReg < num:i(num:sub($MaxLPCR,1))"!][!//
[!CODE!][!//
                  PORT_LPCR_DEFAULT,
[!ENDCODE!][!//
       [!ELSE!]
[!CODE!][!//
                  PORT_LPCR_DEFAULT
[!ENDCODE!][!//
       [!ENDIF!]
     [!ENDIF!]
     [!VAR "NoOfLvdsReg" = "num:i($NoOfLvdsReg) - num:i(1)"!][!//
   [!ENDFOR!]
   [!IF "$NoOfLvdsReg > num:i(1)"!][!//
[!CODE!][!//
  },[!//
[!ENDCODE!][!//
   [!ELSE!]
[!CODE!][!//
  }[!//
[!ENDCODE!][!//
   [!ENDIF!]
   [!ENDIF!]  
 [!ENDLOOP!]
[!ENDSELECT!]
[!ENDNOCODE!][!//
[!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: Port_ConfigurationCheck

  Macro to determine if the configuration for Port module is correct or not.
*****************************************************************************/!]
[!/*[cover parentID={1CAF831F-3416-4db9-A533-DBA612CC84D2}][/cover]*/!][!//
[!MACRO "Port_ConfigurationCheck"!][!//
[!NOCODE!][!//
[!//
[!/* Determine if there is any Port pin whose direction is changeable,*/!]
[!/* when the general setting doesn't allow for direction changeable pins */!]
[!IF "PortGeneral/PortSetPinDirectionApi = 'true'"!][!//
  [!//
  [!/* ConfigOk = 0 indicates all pins are direction not changeable */!][!//
  [!VAR "ConfigOk" = "num:i(0)"!][!//
  
    [!//
    [!/* Scan through the Port Pins other than the read only ports */!][!//
    [!LOOP "PortConfigSet/PortContainer/*/PortPin/*"!][!//
      [!//
     
        [!IF "PortPinDirectionChangeable = 'true'"!][!//
          [!VAR "ConfigOk" = "num:i(1)"!][!/* One of the pins is direction changeable*/!][!//
          [!BREAK!][!//
        [!ENDIF!][!//
     
      [!//
    [!ENDLOOP!][!//
    [!//
 
    [!//
  
    [!IF "not(num:i($ConfigOk) = num:i(1))"!][!//
      [!ERROR!][!//
 Config Error: PortGeneral/PortSetPinDirectionApi is set as true, but PortPinDirectionChangeable of none of the I/O port pins of is set to true!
      [!ENDERROR!][!//
    [!ENDIF!]
  
  [!//
[!ENDIF!][!/* IF "PortGeneral/PortSetPinDirectionApi = 'true'" */!][!//
[!//
[!/* Determine if there is any Port pin whose mode is changeable,*/!]
[!/* when the general setting doesn't allow for mode changeable pins */!]
[!IF "PortGeneral/PortSetPinModeApi = 'true'"!][!//
  [!//
  [!/* ConfigOk = 0 indicates all pins are mode not changeable */!][!//
  [!VAR "ConfigOk" = "num:i(0)"!][!//
  
    [!/* Scan through the Port Pins other than the read only ports */!][!//
    [!LOOP "PortConfigSet/PortContainer/*/PortPin/*"!][!//
      [!//
      
        [!IF "PortPinModeChangeable = 'true'"!][!//
          [!VAR "ConfigOk" = "num:i(1)"!][!/* One of the pins is mode changeable*/!][!//
          [!BREAK!][!//
        [!ENDIF!][!//
     
      [!//
    [!ENDLOOP!][!//
    [!//

  

 [!IF "not(num:i($ConfigOk) = num:i(1))"!][!//
      [!ERROR!][!//
 Config Error: PortGeneral/PortSetPinModeApi is set as true, but PortPinModeChangeable of none of the I/O port pins of is set to true!
      [!ENDERROR!][!//
    [!ENDIF!]
  [!//
[!ENDIF!][!/* IF "PortGeneral/PortSetPinModeApi = 'true'" */!][!//


[/*To check if the Port has Correct Port Number*/]


[/*To check if No of PortPins configured are valid*/]
   [!IF "num:i(count(PortConfigSet/PortContainer/*)) != ecu:get('Port.TotalNumOfPort')"!][!//
      [!ERROR!][!//
   At [!"name(PortConfigSet)"!],
  Number of Ports configured is not proper, there should be [!"ecu:get('Port.TotalNumOfPort')"!] Ports configured
      [!ENDERROR!][!//
    [!ENDIF!]


[/*To check if the Port has Correct PortNumberOfPortPins*/]

  [!/* Scan through the Port Pins other than the read only ports */!][!//
  [!LOOP "PortConfigSet/PortContainer/*"!][!//
    [!IF "num:i(count(text:split(ecu:get(concat('Port.Port',./PortNumber,'_AvailablePins')),' '))) != num:i(./PortNumberOfPortPins)"!][!//
      [!ERROR!][!//
   At "PortConfigSet/PortContainer/[!"@name"!]",
  Port_[!"./PortNumber"!] should have [!"num:i(count(text:split(ecu:get(concat('Port.Port',./PortNumber,'_AvailablePins')),' ')))"!]pins
      [!ENDERROR!][!//
    [!ENDIF!]
  [!ENDLOOP!][!//


[!/*To check if the PortPinMode is defined more than one for a portpin*/!]


  [!/* Scan through the Port Pins other than the read only ports */!][!//
  [!LOOP "PortConfigSet/PortContainer/*/PortPin/*/PortPinMode/*"!][!//
    [!IF "
     contains(substring-before(concat(text:join(../*, ','), ','), concat(., ',')), concat(., ',')) = 'true'
     or
     contains(substring-after(concat(text:join(../*, ','), ','), concat(., ',')), concat(., ',')) = 'true'
     "!][!//
      [!ERROR!][!//
At "PortConfigSet/PortContainer/PortPin/[!"../../@name"!]/PortPinMode/",
[!"node:value(.)"!] should be defined only once for [!"../../PortPinSymbolicName"!]
      [!ENDERROR!][!//
    [!ENDIF!]
  [!ENDLOOP!][!//

[!/* To check there should be only one mode available if PORT_PIN_MODE_ALL is selected */!]

[!/* Scan through the Port Pins other than the read only ports */!][!//
  [!LOOP "PortConfigSet/PortContainer/*/PortPin/*/PortPinMode/*"!][!//
    [!IF "
      (contains(substring-before(concat(text:join(../*, ','), ','), concat(., ',')), 'PORT_PIN_MODE_ALL')
      or
      contains(substring-after(concat(text:join(../*, ','), ','), concat(., ',')), 'PORT_PIN_MODE_ALL'))
      and
      (count(../*) > 1)
      "!][!//
      [!ERROR!][!//
At "PortConfigSet/PortContainer/[!"../../../../@name"!]/PortPin/[!"../../@name"!]/PortPinMode/",
PORT_PIN_MODE_ALL selects all the modes available for [!"../../PortPinSymbolicName"!], no need to add any other modes
      [!ENDERROR!][!//
    [!ENDIF!]
  [!ENDLOOP!][!//

[!/*To Check if the Mode is available for the PortPin*/!]

[!/* Scan through the Port Pins other than the read only ports */!][!//
  [!LOOP "PortConfigSet/PortContainer/PortPin/*/PortPinMode/*"!][!//
    [!IF "
        contains(ecu:get(concat('Port.InitialModes',(../../../../PortNumber),'_',((../../PortPinId) mod 16))),
        concat(substring-after(.,'PORT_PIN_MODE_'),'_Reserved'))
         "!][!//
      [!ERROR!][!//
At "PortConfigSet/PortContainer/[!"../../../../@name"!]/PortPin/[!"../../@name"!]/PortPinMode/",
[!"node:value(.)"!] is not available for [!"../../PortPinSymbolicName"!]
      [!ENDERROR!][!//
    [!ENDIF!]
  [!ENDLOOP!][!//

[!/* To Check he direction of Port is Output for LVDS */!]
[!LOOP "PortConfigSet/PortContainer/*"!][!//
 [!IF "./PortNumber = text:split(ecu:get('Port.AvailableLVDSPorts'),' ')"!]
   [!LOOP "./PortLVDS/*"!]
   [!IF "not(contains(ecu:get(concat('Port.Port_',../../PortNumber,'_AvailablePinPairLVDSRx')),./PortLVDSPinPair)) and not(contains(ecu:get(concat('Port.Port',../../PortNumber,'_AvailablePinPairLVDSTx')),./PortLVDSPinPair))"!]
        [!ERROR!][!//
[!"./PortLVDSPinPair"!] is not a valid name,expected name for PortLVDSPinPair of Port[!"../../PortNumber"!] is [!"ecu:get(concat('Port.Port',../../PortNumber,'_AvailablePinPairLVDSRx'))"!], [!"ecu:get(concat('Port.Port',../../PortNumber,'_AvailablePinPairLVDSTx'))"!]
        [!ENDERROR!][!//
   [!ENDIF!]
     [!IF "contains(ecu:get(concat('Port.Port_',../../PortNumber,'_AvailablePinPairLVDSRx')),./PortLVDSPinPair)"!]
       [!IF "contains(./PortLVDSRxPathEnable,'true')"!]
       [!VAR "PortPin1" = "text:split(text:replaceAll(text:replaceAll(./PortLVDSPinPair,'Pin_',' '),'_',' '),' ')[position()-1 = 0]"!]
       [!VAR "PortPin2" = "text:split(text:replaceAll(text:replaceAll(./PortLVDSPinPair,'Pin_',' '),'_',' '),' ')[position()-1 = 1]"!]
         [!LOOP "../../PortPin/*"!]
           [!IF "./PortPinId = num:add(num:mul(../../PortNumber,16),$PortPin1)"!]
             [!IF "./PortPinDirection = 'PORT_PIN_IN'"!]
               [!ERROR!][!//
               If LVDS Enable is selected for PortPinPair Pin_[!"$PortPin1"!]_Pin_[!"$PortPin2"!] the PortPinDirection
               should be PORT_PIN_OUT for the Pin with symbolic name : [!"./PortPinSymbolicName"!] of Port[!"../../PortNumber"!]
               [!ENDERROR!][!//
             [!ENDIF!]
           [!ENDIF!]
           [!IF "./PortPinId = num:add(num:mul(../../PortNumber,16),$PortPin2)"!]
             [!IF "./PortPinDirection = 'PORT_PIN_IN'"!]
               [!ERROR!][!//
               If LVDS Enable is selected for PortPinPair Pin_[!"$PortPin1"!]_Pin_[!"$PortPin2"!] the PortPinDirection
               should be PORT_PIN_OUT for the Pin with symbolic name : [!"./PortPinSymbolicName"!] of Port[!"../../PortNumber"!]
               [!ENDERROR!][!//
             [!ENDIF!]
           [!ENDIF!]
         [!ENDLOOP!]
       [!ENDIF!]
     [!ENDIF!]

     [!IF "contains(ecu:get(concat('Port.Port',../../PortNumber,'_AvailablePinPairLVDSTx')),./PortLVDSPinPair)"!]
       [!IF "contains(./PortLVDSTxPathEnable,'true')"!]
       [!VAR "PortPin1" = "text:split(text:replaceAll(text:replaceAll(./PortLVDSPinPair,'Pin_',' '),'_',' '),' ')[position()-1 = 0]"!]
       [!VAR "PortPin2" = "text:split(text:replaceAll(text:replaceAll(./PortLVDSPinPair,'Pin_',' '),'_',' '),' ')[position()-1 = 1]"!]
         [!LOOP "../../PortPin/*"!]
           [!IF "./PortPinId = num:add(num:mul(../../PortNumber,16),$PortPin1)"!]
             [!IF "./PortPinDirection = 'PORT_PIN_IN'"!]
               [!ERROR!][!//
               If LVDS Enable is selected for PortPinPair Pin_[!"$PortPin1"!]_Pin_[!"$PortPin2"!] the PortPinDirection
               should be PORT_PIN_OUT for the Pin with symbolic name : [!"./PortPinSymbolicName"!] of Port[!"../../PortNumber"!]
               [!ENDERROR!][!//
             [!ENDIF!]
           [!ENDIF!]
           [!IF "./PortPinId = num:add(num:mul(../../PortNumber,16),$PortPin2)"!]
             [!IF "./PortPinDirection = 'PORT_PIN_IN'"!]
               [!ERROR!][!//
               If LVDS Enable is selected for PortPinPair Pin_[!"$PortPin1"!]_Pin_[!"$PortPin2"!] the PortPinDirection
               should be PORT_PIN_OUT for the Pin with symbolic name : [!"./PortPinSymbolicName"!] of Port[!"../../PortNumber"!]
               [!ENDERROR!][!//
             [!ENDIF!]
           [!ENDIF!]
         [!ENDLOOP!]
       [!ENDIF!]
     [!ENDIF!]
   [!ENDLOOP!]
 [!ENDIF!]
[!ENDLOOP!]

[!ENDNOCODE!][!//
[!ENDMACRO!][!/* End of macro Port_ConfigurationCheck */!][!//

[!/******************************************************************************
MACRO: Port_GetPortPinEmergencyStopEnable
Gets the Port Pin ModeChangeabl attributes.
Input Prameters:
port: The Port Id
pinstart: The Starting Pin id of the Port
pinend: The ending Pin id of the Port
******************************************************************************/!]
[!/*[cover parentID={9C37A638-CE18-46f5-93EC-37A00B3A83A2}][/cover]*/!][!//
[!MACRO "Port_GetPortPinEmergencyStopEnable", "port"=""!][!//
[!//
[!FOR "PortPinNo" = "0" TO "15"!][!//
[!VAR "PinId" = "num:i($port) * num:i(16)"!][!//
[!VAR "PinId" = "num:i($PinId) + num:i($PortPinNo)"!][!//
[!IF "node:exists(PortConfigSet/PortContainer/*/PortPin/*[PortPinId = num:i($PinId)])"!][!//
[!/*
  Select the container for the calculated PinId to extract the configuration
*/!][!//
[!SELECT "PortConfigSet/PortContainer/*/PortPin/*[PortPinId = num:i($PinId)]"!][!//
[!IF "PortPinEmergencyStop = 'true'"!][!//
          PORT_PIN_EMERGENCY_STOP_ENABLE[!//
[!ELSE!][!//
         PORT_PIN_EMERGENCY_STOP_DISABLE[!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ELSE!][!//
         PORT_PIN_EMERGENCY_STOP_DISABLE[!//
[!ENDIF!][!//
[!IF "num:i($PortPinNo) != num:i(15)"!][!//
,/* Pin [!"num:i($PortPinNo)"!] */ [!//
[!ELSE!][!//
 /* Pin [!"num:i($PortPinNo)"!] */
[!ENDIF!]
[!ENDFOR!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: Port_GetPDISCPorts00to31

Macro to generate definition to indicate ports which support PCSR of the uC

Input Parameters:
  None
*****************************************************************************/!]
[!MACRO "Port_GetPDISCPorts00to31"!][!//
[!NOCODE!][!//

  [!VAR "PDISCPorts" = "num:i(0)"!][!//

  [!FOR "PortNumber" = "0" TO "31"!]
    [!IF "($PortNumber = text:split(ecu:get('Port.AvailableAnalogDigitalPorts'), ' ' ))"!][!//
      [!VAR "PDISCPorts" = "bit:bitset($PDISCPorts, $PortNumber)"!][!//
    [!ENDIF!]
  [!ENDFOR!]

[!ENDNOCODE!][!//
[!//
#define PORTS_PDISC_00_31       ([!"num:inttohex($PDISCPorts, 8)"!]U)
[!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: Port_GetPDISCPorts32to63

Macro to generate definition to indicate ports which support PCSR of the uC




  Input Parameters:
  None
*****************************************************************************/!]
[!MACRO "Port_GetPDISCPorts32to63"!][!//
[!NOCODE!][!//

  [!VAR "PDISCPorts" = "num:i(0)"!][!//

  [!FOR "PortNumber" = "32" TO "63"!]
    [!IF "($PortNumber = text:split(ecu:get('Port.AvailableAnalogDigitalPorts'), ' ' ))"!][!//
      [!VAR "PDISCPorts" = "bit:bitset($PDISCPorts, ($PortNumber -32))"!][!//
    [!ENDIF!]
  [!ENDFOR!]

[!ENDNOCODE!][!//
[!//
#define PORTS_PDISC_32_63       ([!"num:inttohex($PDISCPorts, 8)"!]U)
[!//
[!ENDMACRO!][!//


