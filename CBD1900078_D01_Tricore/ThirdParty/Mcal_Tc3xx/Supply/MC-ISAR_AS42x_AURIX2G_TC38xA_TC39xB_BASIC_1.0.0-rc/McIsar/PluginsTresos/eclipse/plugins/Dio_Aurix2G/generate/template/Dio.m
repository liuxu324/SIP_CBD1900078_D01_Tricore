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
**  FILENAME  : Dio.m                                                         **
**                                                                            **
**  VERSION   : 4.0.0                                                         **
**                                                                            **
**  DATE      : 2018-08-07                                                    **
**                                                                            **
**  BSW MODULE DESCRIPTION : Dio.bmd                                          **
**                                                                            **
**  VARIANT   : Variant LT                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY :[cover parentID={0DEC4F46-E925-4a8d-A9D8-C6725332C45C}]     **
**                [/cover]                                                    **
**  DESCRIPTION  : Code template macro file for Dio Driver                    **
**                                                                            **
**                                                                            **
**                                                                            **
**  SPECIFICATION(S) : Specification of Dio Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
*/!]


[!/*****************************************************************************
  Macro: Dio_ConfigSwitch

  Macro to generate configuration switch Values STD_ON/STD_OFF based on
  configuration true/false

  Input Parameters:
  - nodeval: true/false
*****************************************************************************/!]
[!MACRO "Dio_ConfigSwitch", "nodeval" = ""!][!//
[!//
[!IF "$nodeval = 'true'"!][!//
(STD_ON)[!//
[!ELSE!][!//
(STD_OFF)[!//
[!ENDIF!]
[!ENDMACRO!]


[!/*****************************************************************************
  Macro: Dio_GetDioChannelSymbolicNames

  Macro to print the symbolic names of each of the Dio channels

  Input Parameters:
  PortNum
*****************************************************************************/!]
[!MACRO "Dio_GetDioChannelSymbolicNames", "PortNum" = ""!][!//
[!//
[!FOR "PortPinNo" = "num:i(0)" TO "ecu:get(concat('Dio.Port',$PortNum,'_MSPin'))"!][!//
[!VAR "PinId" = "num:i($PortNum) * num:i(16)"!][!//
[!VAR "PinId" = "num:i($PinId) + num:i($PortPinNo)"!][!//
[!//
[!IF "contains(ecu:get(concat('Dio.DioChannels_Port',$PortNum)),concat('_',$PortPinNo,'_'))"!][!//
#define DIO_CHANNEL_[!"num:i($PortNum)"!]_[!"num:i($PortPinNo)"!]                    ((Dio_ChannelType)[!"num:inttohex($PinId, 3)"!])
[!ENDIF!][!//
[!//
[!ENDFOR!][!//
[!ENDMACRO!]
[!/*****************************************************************************
  Macro: Dio_GetDioPortSymbolicNames

  Macro to print the symbolic names of each of the Dio Ports

  Input Parameters:
  None
*****************************************************************************/!]
[!MACRO "Dio_GetDioPortSymbolicNames"!][!//
[!//
[!FOR "PortNumber" = "num:i(0)" TO "ecu:get('Dio.MaxAvailablePort')"!][!//
[!IF "contains(ecu:get('Dio.AvailablePorts'),concat('_',$PortNumber,'_'))"!][!//
#define DIO_PORT_[!"$PortNumber"!]                          ((Dio_PortType)[!"$PortNumber"!])
[!ENDIF!][!//
[!ENDFOR!][!//
[!//
[!ENDMACRO!]


[!/*****************************************************************************
  Macro: Dio_GetDioConfiguredChannelInfo

 Macro to identify and print the configured status of Dio Port and its Channels.

  Input Parameters:
  PortNum
*****************************************************************************/!]
[!/* [cover parentID={38E90E81-83B3-442e-9C9E-FA273E2F1E9D}] [/cover]*/!]
[!MACRO "Dio_GetDioConfiguredChannelInfo", "PortNum" = ""!][!//
[!//
[!VAR "PortConfigured" = "num:i(0)"!][!//
[!/* Loop for all DioPort containers to generate configured Port,
     Channels under this port  */!][!//
[!IF "node:exists(DioConfig/DioPort/*[DioPortId = num:i($PortNum)])"!][!//
[!SELECT "DioConfig/DioPort/*[DioPortId = num:i($PortNum)]"!][!//
     DIO_PORT_CONFIGURED,
[!FOR "PortPinNo" = "num:i(0)" TO "num:i(15)"!][!//
[!IF "node:exists(DioChannel/*[DioChannelId = num:i($PortPinNo)])"!][!//
[!VAR "PortConfigured" = "bit:or($PortConfigured,(bit:shl(1,num:i($PortPinNo))))"!][!//
[!ELSE!][!//
[!VAR "PortConfigured" = "bit:or($PortConfigured,(bit:shl(0,num:i($PortPinNo))))"!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
     ([!"num:inttohex($PortConfigured, 4)"!]U)
[!ENDSELECT!][!//
[!ELSE!][!//
     DIO_PORT_NOT_CONFIGURED,
     (0x0000U)
[!ENDIF!][!//
[!//
[!ENDMACRO!]
[!/*****************************************************************************
  Macro: Dio_GetUserDefinedSymbolicNames

  Macro to print the user defined symbolic names of each Dio Port/Channel/Group

  Input Parameters:
  None
*****************************************************************************/!]
[!/* [cover parentID={1194A06F-A403-4d29-83B1-5090FAA15A35}] [/cover]*/!]
[!MACRO "Dio_GetUserDefinedSymbolicNames"!][!//
[!//
[!/* Variable used as index to refer to the channel groups */!][!//
[!VAR "j" = "num:i(0)"!][!//
[!//
[!/* Loop for all DioPort containers to generate symbolic names for the Port,
     Channels under this port & Channel groups under this port */!][!//
[!LOOP "DioConfig/DioPort/*"!][!//
[!//
[!/* Check if the Port Id. is valid. */!][!//
[!CALL "Dio_CheckPortIdValidity", "PortId" = "num:i(./DioPortId)"!][!//
[!//
[!VAR "PortId" = "num:i(./DioPortId)"!][!//
[!VAR "PortName" = "concat('DIO_PORT_', num:i(./DioPortId))"!][!//
[!VAR "ChannelPrefix" = "concat('DIO_CHANNEL_', num:i(./DioPortId))"!][!//
[!VAR "ChannelGroupPrefix" = "'Dio_kChannelGroupConfig'"!][!//
[!VAR "PortSymbolicName" = "concat('DioConf_DioPort_', node:name(.))"!][!//

/*
  DIO PORT : ([!"node:name(.)"!])
*/
[!VAR "PortSymbolicName" = "normalize-space($PortSymbolicName)"!][!//
[!IF "num:i(string-length($PortSymbolicName)) != 0"!][!//

#ifndef [!"$PortSymbolicName"!]
#define [!"$PortSymbolicName"!] ([!"$PortName"!])
#endif
[!ELSE!][!//
/* The Port does not have a User defined symbolic name. Use directly the
   internal Symbolic Name ([!"$PortName"!]) */
[!ENDIF!][!//
[!//
[!/* Generate Symbolic names for Dio channels under this port */!][!//
[!LOOP "./DioChannel/*"!][!//
[!//
[!/* Check for validity of the configured channel id*/!][!//
[!CALL "Dio_CheckChannelIdValidity", "PortId" = "num:i($PortId)", "ChannelId" = "num:i(./DioChannelId)"!][!//
[!//
[!VAR "ChannelName" = "concat($ChannelPrefix,'_', num:i(./DioChannelId))"!][!//
[!VAR "ChannelSymbolicName" = "concat('DioConf_DioChannel_', node:name(.))"!][!//
[!VAR "ChannelSymbolicName" = "normalize-space($ChannelSymbolicName)"!][!//

/* DIO Channel : ([!"node:name(.)"!]) */
[!IF "num:i(string-length($ChannelSymbolicName)) != 0"!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers are defined
 according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers are defined
 according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers are defined
 according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers are defined
 according to requirement ecuc_sws_2108*/
#ifndef [!"$ChannelSymbolicName"!]
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers are defined
 according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers are defined
 according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers are defined
 according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers are defined
 according to requirement ecuc_sws_2108*/
#define [!"$ChannelSymbolicName"!] ([!"$ChannelName"!])
#endif
[!ELSE!][!//
/* The Dio Channel does not have a User defined symbolic name. Use directly the
   internal Symbolic Name ([!"$ChannelName"!]) */
[!ENDIF!][!//
[!ENDLOOP!][!//
[!//
[!/* Generate Symbolic names for Dio channel groups under this port */!][!//
[!LOOP "./DioChannelGroup/*"!][!//
[!//
[!/* Check for validity of Mask */!][!//
[!CALL "Dio_CheckChannelGroupMaskValidity", "GroupName" = "DioChannelGroupIdentification", "PortId" = "../../DioPortId", "MaskValue" = "num:i(DioPortMask)"!][!//
[!//

[!VAR "ChannelGroupSymbolicName" = "concat('DioConf_DioChannelGroup_', node:name(.))"!][!//
[!VAR "ChannelGroupSymbolicName" = "normalize-space($ChannelGroupSymbolicName)"!][!//

/*DIO Channel Group : [!"DioChannelGroupIdentification"!]*/
[!IF "num:i(string-length($ChannelGroupSymbolicName)) != num:i(0)"!][!//

/* To prevent double declaration */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers are defined
 according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers are defined
 according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers are defined
 according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers are defined
 according to requirement ecuc_sws_2108*/
#ifndef [!"$ChannelGroupSymbolicName"!]
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers are defined
 according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers are defined
 according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers are defined
 according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers are defined
 according to requirement ecuc_sws_2108*/
#define [!"$ChannelGroupSymbolicName"!] (&Dio_Config.Dio_ChannelGroupConfigPtr[[!"num:i($j)"!]])
#endif
[!ELSE!][!//
/* The Dio Port Pin Group does not have a User defined symbolic name.*/
[!ENDIF!][!//
[!VAR "j" = "$j + 1"!][!//
[!ENDLOOP!][!/* LOOP "./DioChannelGroup/*" */!][!//
[!//
[!ENDLOOP!][!/*LOOP "DioPort/*"*/!][!//

[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: Dio_GetNumOfDioChannelGroupsConfigured

  Macro to get the number of channel groups configured
  Port.

  Input Parameters:
  None
*****************************************************************************/!]
[!MACRO "Dio_GetNumOfDioChannelGroupsConfigured"!][!//
[!//
[!/* If there are DIO channel groups configured */!][!//
[!VAR "NumOfGroups" = "num:i(count(DioConfig/DioPort/*/DioChannelGroup/*))"!][!//
[!//
[!ENDMACRO!][!//
[!/*****************************************************************************
  Macro: Dio_GetDioChannelGroupDefinition

  Macro to set the definition of the channel group under each
  Port.

  Input Parameters:
  None
*****************************************************************************/!]
[!/* [cover parentID={C14746A4-EB54-4c09-8C16-CCC3BD6FC8E2}] [/cover]*/!]
[!MACRO "Dio_GetDioChannelGroupDefinition"!][!//
[!//
[!/* If there are DIO channel groups configured */!][!//
[!IF "num:i(count(DioConfig/DioPort/*/DioChannelGroup/*)) > 0"!][!//
[!VAR "PortChannelGroupStructName" = "'Dio_kChannelGroupConfig'"!][!//
static const Dio_ChannelGroupType Dio_kChannelGroupConfig[DIO_CHANNELGROUPCOUNT]=
{[!//
[!/* Variables used in this configuration structure */!][!//
[!VAR "PortName" = "num:i(0)"!][!//
[!VAR "PortId" = "num:i(0)"!][!//
[!VAR "PortOffset" = "num:i(0)"!][!//
[!VAR "BitPosition" = "num:i(0)"!][!//
[!VAR "counter" = "num:i(0)"!][!//
[!//
[!/* Loop for all DioPort containers */!][!//
[!LOOP "DioConfig/DioPort/*"!][!//
[!VAR "PortName" = "node:name(.)"!][!//
[!VAR "PortId" = "num:i(./DioPortId)"!][!//
[!LOOP "./DioChannelGroup/*"!][!//
[!/* To skip the first comma in the generated file */!][!//
[!IF "$counter = num:i(1)"!][!//
,[!//
[!ENDIF!]
[!VAR "counter" = "1"!][!//
[!NOCODE!][!//
  [!/* Calculate the offset depending on the value of the DioPortMask */!][!//
  [!VAR "PortOffset" = "num:i(0)"!][!//
  [!FOR "BitPosition" = "num:i(0)" TO "num:i(15)"!]
    [!IF "bit:getbit( num:i(DioPortMask), num:i($BitPosition) ) = 'true'"!]
      [!VAR "PortOffset" = "num:i($BitPosition)"!][!//
      [!BREAK!]
    [!ENDIF!]
  [!ENDFOR!]

  [!VAR "MaskValuecorrect" = "num:i(0)"!][!//
  [!VAR "MaskValuewrong" = "num:i(0)"!][!//
  [!VAR "Mask" = "DioPortMask"!][!//
  [!VAR "Mask" = "num:i(bit:shr($Mask,$PortOffset))"!][!//
  [!FOR "Index" = "num:i(0)" TO "num:i(15 - $PortOffset)"!][!//
  [!VAR "MaskValuecorrect" = "num:i(bit:and(num:i(1),num:i($Mask)))"!][!//
  [!IF "$MaskValuecorrect = num:i(1)"!][!//
  [!IF "$MaskValuewrong = num:i(1)"!][!//
  [!ERROR!][!//
   Config Error: Set the mask value which have only adjoining one's in the Group [!"DioChannelGroupIdentification"!]
  [!ENDERROR!][!//
  [!ENDIF!][!//
  [!ELSE!][!//
  [!VAR "MaskValuewrong" = "num:i(1)"!][!//
  [!ENDIF!][!//
  [!VAR "Mask" = "num:i(bit:shr($Mask,1))"!][!//
  [!ENDFOR!][!//

[!ENDNOCODE!][!//
  {
    /* [!"$PortName"!], [!"DioChannelGroupIdentification"!] */
    (Dio_PortLevelType)[!"num:inttohex(num:i(DioPortMask))"!], /* Mask    */
    (uint8)[!"num:i($PortOffset)"!],              /* Offset  */
    (Dio_PortType)[!"num:i($PortId)"!]          /* Port Id */
  }[!//
[!ENDLOOP!][!/*LOOP "./DioChannelGroup/*"*/!][!//
[!ENDLOOP!][!/*LOOP "DioPort/*"*/!][!//

};
[!//
[!/* If there are no DIO channel groups configured */!][!//
[!ELSE!][!//
/* No Groups are configured */
[!ENDIF!][!//
[!//
[!ENDMACRO!][!//


[!/*****************************************************************************
  Macro: Dio_CheckPortIdValidity

  Macro to check  Port id is valid or not

  Input Parameters:
  - PortId:
*****************************************************************************/!]
[!MACRO "Dio_CheckPortIdValidity", "PortId" = ""!][!//
[!NOCODE!][!//
[!//
[!IF "(not(ecu:has(concat('Dio.DioChannels_Port',$PortId))))"!][!//
[!ERROR!][!//
Config Error: The PortId [!"$PortId"!] is invalid. The available Ports are [!"ecu:get('Dio.AvailablePorts')"!].[!//
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!//
[!ENDMACRO!]

[!/*****************************************************************************
  Macro: Dio_CheckChannelIdValidity

  Macro to check the validity of the channel id. for the specified port

  Input Parameters:
  - PortId:
  - ChannelId:
*****************************************************************************/!]
[!MACRO "Dio_CheckChannelIdValidity", "PortId" = "", "ChannelId" = ""!][!//
[!NOCODE!][!//
[!//
[!IF "(ecu:has(concat('Dio.DioChannels_Port',$PortId)))"!][!//
[!IF "(not(contains(ecu:get(concat('Dio.DioChannels_Port',$PortId)),concat('_',$ChannelId,'_'))))"!][!//
[!ERROR!][!//
Config Error: The ChannelID [!"$ChannelId"!] is invalid. The available PortPins for PORT[!"$PortId"!] are [!"ecu:get(concat('Dio.DioChannels_Port',$PortId))"!].[!//
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!//
[!ENDMACRO!]

[!/*****************************************************************************
  Macro: Dio_CheckChannelGroupIdValidity

  Macro to check the validity of the channel group Id

  Input Parameters:
  - GroupCtrName:
*****************************************************************************/!]
[!/* [cover parentID={5EA03B63-F622-4faa-BBBD-1ED45FF53B29}] [/cover]*/!]
[!MACRO "Dio_CheckChannelGroupIdValidity", "GroupCtrName" = ""!][!//
[!NOCODE!][!//
  [!IF "( num:i(string-length(DioChannelGroupIdentification)) = num:i(0) )"!][!//
   [!ERROR!][!//
   Config Error: The parameter DioChannelGroupIdentification for the ChannelGroup [!//
   with container name [!"$GroupCtrName"!] is not configured[!//
   [!ENDERROR!][!//
  [!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//


[!/*****************************************************************************
  Macro: Dio_CheckChannelGroupMaskValidity

  Macro to check the validity of the mask value of the channel group

  Input Parameters:
  - GroupName:
  - PortId:
  - MaskValue:
*****************************************************************************/!]
[!MACRO "Dio_CheckChannelGroupMaskValidity", "GroupName" = "", "PortId" = "", "MaskValue" = ""!][!//
[!NOCODE!][!//

[!/* Check if MaskValue is 0 */!][!//
[!IF " ( num:i($MaskValue) = num:i(0) )"!][!//
[!ERROR!][!//
Config Error: The ChannelGroup [!"$GroupName"!] is configured with no channels [!//
because the parameter DioPortMask is configured 0. Configure a valid mask value[!//
[!ENDERROR!][!//
[!ENDIF!][!//

[!/* Check for the validity of the mask value for the channel group */!][!//
[!VAR "InvalidMaskValue" = "'False'"!][!//

[!IF "boolean( bit:and( ($MaskValue) , (bit:not(num:hextoint(ecu:get(concat('Dio.DioPortMask_Port',$PortId)))))))"!][!//
  [!VAR "InvalidMaskValue" = "'True'"!][!//
[!ENDIF!]

[!/* Generate error message */!][!//

[!IF "( $InvalidMaskValue = 'True')"!][!//
[!ERROR!][!//
Config Error: The ChannelGroup [!"$GroupName"!] is configured with a mask value [!//
that specifies more no. of port pins in the group than available on that port. [!//
Configure a valid mask value[!//
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: Dio_VerifyDioConfig

  Macro to verify the validity of the Dio configuration

  Input Parameters:
  None
*****************************************************************************/!]
[!/* [cover parentID={C1B94883-9131-4ad0-8AB6-F0924C2B57F2}] [/cover]*/!]
[!MACRO "Dio_VerifyDioConfig"!][!//
[!NOCODE!][!//

  [!//
  [!/* Loop for all DioPort containers to verify the configuration for the Port,
       Channels under this port & Channel groups under this port */!][!//
  [!LOOP "DioConfig/DioPort/*"!][!//
    [!//
    [!VAR "PortId" = "num:i(./DioPortId)"!][!//
    [!VAR "PortName" = "concat('DIO_PORT_', num:i(./DioPortId))"!][!//
    [!VAR "ChannelPrefix" = "concat('DIO_CHANNEL_', num:i(./DioPortId))"!][!//
    [!VAR "ChannelGroupPrefix" = "'Dio_ChannelGroupConfig'"!][!//
    [!VAR "PortSymbolicName" = "node:name(.)"!][!//
    [!//
    [!/* Check if the Port Id. is valid. */!][!//
    [!CALL "Dio_CheckPortIdValidity", "PortId" = "$PortId"!][!//
    [!//
    [!IF "($PortSymbolicName = $PortName)"!][!//
     [!ERROR!][!//
     Config Error: The User Defined Symbolic Name is same as Internal Symbolic Name for [!//
     [!"$PortName"!]. Define another unique name![!//
     [!ENDERROR!][!//
    [!ENDIF!][!//

    [!//

    [!//
    [!/* Loop for all channels under this port */!][!//
    [!LOOP "./DioChannel/*"!][!//
      [!//
      [!VAR "ChannelName" = "concat($ChannelPrefix,'_', num:i(./DioChannelId))"!][!//
      [!VAR "ChannelSymbolicName" = "node:name(.)"!][!//
      [!//
      [!/* Check for validity of the configured channel id*/!][!//
      [!CALL "Dio_CheckChannelIdValidity", "PortId" = "num:i($PortId)", "ChannelId" = "num:i(./DioChannelId)"!][!//
      [!//
    [!IF "($ChannelSymbolicName = $ChannelName)"!]
    [!ERROR!][!//
Config Error:The User Defined Symbolic Name is same as Internal Symbolic Name for [!//
[!"$ChannelName"!]. Define another unique name![!//
[!ENDERROR!][!//
[!ENDIF!][!//

      [!//
    [!ENDLOOP!][!/*LOOP "./DioChannel/*"*/!][!//
    [!//

    [!//
    [!/* Loop for all the Dio channel groups under this port */!][!//
    [!LOOP "./DioChannelGroup/*"!][!//
      [!//
      [!/* Check for validity of the DioChannelGroupIdentification */!][!//
      [!CALL "Dio_CheckChannelGroupIdValidity", "GroupCtrName" = "node:name(.)"!][!//
      [!//
      [!/* Check for validity of Mask */!][!//
      [!CALL "Dio_CheckChannelGroupMaskValidity", "GroupName" = "DioChannelGroupIdentification", "PortId" = "../../DioPortId", "MaskValue" = "num:i(DioPortMask)"!][!//
      [!//
    [!ENDLOOP!][!/* LOOP "./DioChannelGroup/*" */!][!//
    [!//

  [!//
  [!ENDLOOP!][!/*LOOP "DioPort/*"*/!][!//
  [!//

[!ENDNOCODE!][!//
[!ENDMACRO!][!//


[!/*****************************************************************************
  Macro: Dio_GetMaskForPortPins

  Macro to generate the values to mask the undefined port pins

  Input Parameters:
  None
*****************************************************************************/!]
[!MACRO "Dio_GetMaskForPortPins"!][!//
[!//
/* Values to mask the undefined port pins within a port */
[!FOR "PortNumber" = "0" TO "ecu:get('Dio.MaxAvailablePort')"!][!//
[!VAR "MaskPort_Temp" = "num:inttohex(0,4)"!][!//
[!IF "contains(ecu:get('Dio.AvailablePorts'),concat('_',$PortNumber,'_'))"!][!//
[!VAR "MaskPort_Temp" = "num:inttohex(num:hextoint(ecu:get(concat('Dio.DioPortMask_Port',$PortNumber))),4)"!][!//
[!ENDIF!][!//
#define DIO_MASK_ALL_PINS_PORT[!"$PortNumber"!]             ([!"$MaskPort_Temp"!]U)
[!ENDFOR!][!//
[!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: Dio_GetPortMSPin

  Macro to generate the most significant pin for each port

  Input Parameters:
  None
*****************************************************************************/!]
[!MACRO "Dio_GetPortMSPin"!][!//
[!FOR "PortNumber" = "0" TO "ecu:get('Dio.MaxAvailablePort')"!][!//
[!VAR "MsPort_Temp" = "num:i(0)"!][!//
[!IF "contains(ecu:get('Dio.AvailablePorts'),concat('_',$PortNumber,'_'))"!][!//
[!VAR "MsPort_Temp" = "num:i(ecu:get(concat('Dio.Port',$PortNumber,'_MSPin')))"!][!//
[!ENDIF!][!//
#define DIO_PORT_[!"$PortNumber"!]_MSPIN                     ([!"$MsPort_Temp"!]U)
[!ENDFOR!][!//
[!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: Dio_GetReadOnlyPorts00to31

  Macro to generate definition to indicate the read only ports of the uC

  Input Parameters:
  None
*****************************************************************************/!]
[!MACRO "Dio_GetReadOnlyPorts00to31"!][!//
[!NOCODE!][!//

[!VAR "ReadOnlyPorts" = "num:i(0)"!][!//

[!FOR "PortNumber" = "0" TO "31"!][!//
[!IF "contains(ecu:get('Dio.AvailableReadOnlyPorts'),concat('_',$PortNumber,'_'))"!][!//
  [!VAR "ReadOnlyPorts" = "bit:bitset($ReadOnlyPorts, $PortNumber)"!][!//
[!ENDIF!]
[!ENDFOR!]

[!ENDNOCODE!][!//
[!//
#define DIO_PORTS_READONLY_00_31             ([!"num:inttohex($ReadOnlyPorts, 8)"!]U)
[!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: Dio_GetMaxAvailablePort

  Macro to generate the value for Maximum available port on the uC

  Input Parameters:
  None
*****************************************************************************/!]
[!MACRO "Dio_GetMaxAvailablePort"!][!//
[!//
#define MAX_AVAILABLE_PORT                  ([!"num:i(ecu:get('Dio.MaxAvailablePort'))"!]U)
[!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: Dio_GetReadOnlyPorts32to63

  Macro to generate definition to indicate the read only ports of the uC

  Input Parameters:
  None
*****************************************************************************/!]
[!MACRO "Dio_GetReadOnlyPorts32to63"!][!//
[!NOCODE!][!//

[!VAR "ReadOnlyPorts" = "num:i(0)"!][!//

[!FOR "PortNumber" = "32" TO "ecu:get('Dio.MaxAvailablePort')"!][!//
[!IF "contains(ecu:get('Dio.AvailableReadOnlyPorts'),concat('_',$PortNumber,'_'))"!][!//
  [!VAR "ReadOnlyPorts" = "bit:bitset($ReadOnlyPorts, (num:i($PortNumber)-num:i(32)))"!][!//
[!ENDIF!]
[!ENDFOR!]

[!ENDNOCODE!][!//
[!//
#define DIO_PORTS_READONLY_32_63             ([!"num:inttohex($ReadOnlyPorts, 8)"!]U)
[!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: Dio_GetPortsAvailable00to31

  Macro to generate definition to indicate the ports available on the uC

  Input Parameters:
  None
*****************************************************************************/!]
[!MACRO "Dio_GetPortsAvailable00to31"!][!//
[!NOCODE!][!//

[!VAR "AvailablePorts" = "num:i(0)"!][!//

[!FOR "PortNumber" = "0" TO "31"!][!//
[!IF "contains(ecu:get('Dio.AvailablePorts'),concat('_',$PortNumber,'_'))"!][!//
  [!VAR "AvailablePorts" = "bit:bitset($AvailablePorts, $PortNumber)"!][!//
[!ENDIF!]
[!ENDFOR!]

[!ENDNOCODE!][!//
[!//
#define DIO_PORTS_AVAILABLE_00_31           ([!"num:inttohex($AvailablePorts, 8)"!]U)
[!//
[!ENDMACRO!][!//
[!/*****************************************************************************
  Macro: Dio_GetPortsAvailable32to63

  Macro to generate definition to indicate the ports available on the uC

  Input Parameters:
  None
*****************************************************************************/!]
[!MACRO "Dio_GetPortsAvailable32to63"!][!//
[!NOCODE!][!//

[!VAR "AvailablePorts" = "num:i(0)"!][!//

[!FOR "PortNumber" = "32" TO "ecu:get('Dio.MaxAvailablePort')"!][!//
[!IF "contains(ecu:get('Dio.AvailablePorts'),concat('_',$PortNumber,'_'))"!][!//
  [!VAR "AvailablePorts" = "bit:bitset($AvailablePorts, (num:i($PortNumber)-num:i(32)))"!][!//
[!ENDIF!]
[!ENDFOR!]

[!ENDNOCODE!][!//
[!//
#define DIO_PORTS_AVAILABLE_32_63           ([!"num:inttohex($AvailablePorts, 8)"!]U)
[!//
[!ENDMACRO!][!//


[!/*****************************************************************************
  Macro: Dio_check_duplicate_DioPortId

  Macro to check containers with duplicate id

  Input Parameters:
  none
*****************************************************************************/!]
[!/* [cover parentID={6936A2C0-3C20-4add-B44E-3EA076DA841A}] [/cover]*/!]
[!MACRO "Dio_check_duplicate_DioPortId"!][!//
[!//
[!FOR "portno" = "num:i(0)" TO "ecu:get('Dio.MaxAvailablePort')"!][!//
[!VAR "COUNT" = "num:i(0)"!][!//
[!LOOP "as:modconf('Dio')[1]/DioConfig/DioPort/*"!][!//
[!IF "./DioPortId = num:i($portno)"!][!//
[!VAR "COUNT" = "$COUNT + 1"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!IF "$COUNT > num:i(1)"!][!//
[!ERROR!][!//
  DioPortId = [!"$portno"!], is repeated [!"num:i($COUNT)"!] times DioConfig/DioPort/DioPortId
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDMACRO!][!//


[!/*****************************************************************************
  Macro: Dio_check_duplicate_DioPortChannelId

  Macro to check containers with duplicate id

  Input Parameters:
  PortNum
*****************************************************************************/!]
[!/* [cover parentID={DD71ABAD-69BF-42a5-8F44-6697F30B9F53}] [/cover]*/!]
[!MACRO "Dio_check_duplicate_DioPortChannelId", "PortNum" = ""!][!//
[!//
[!FOR "PortListIndex" = "num:i(0)" TO "ecu:get('Dio.DioPortMax')"!][!//
[!FOR "index" = "num:i(0)" TO "num:i(16)"!][!//
[!VAR "COUNT" = "num:i(0)"!][!//
[!LOOP "as:modconf('Dio')[1]/DioConfig/DioPort/*[num:i($PortListIndex)]/DioChannel/*"!][!//
[!IF "./DioChannelId = num:i($index)"!][!//
[!VAR "COUNT" = "$COUNT + 1"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!IF "$COUNT > num:i(1)"!][!//
[!ERROR!][!//
[!VAR "PortListIndex" = "$PortListIndex - 1"!][!//
  DioChannelId = [!"$index"!], is repeated [!"num:i($COUNT)"!] times in DioConfig/DioPort[[!"num:i($PortListIndex)"!]]/DioChannel
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDFOR!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: Dio_GVerify_Unique_Channel_Name

  Macro to check containers with duplicate Channel name

  Input Parameters:
  none
*****************************************************************************/!]
[!MACRO "Dio_GVerify_Unique_Channel_Name"!][!//
[!//
[!NOCODE!][!//
[!SELECT "as:modconf('Dio')[1]"!][!//
[!LOOP "./DioConfig/DioPort/*"!]
[!VAR "Dio_chnl_list" = "''"!]
[!LOOP "./DioChannel/*"!]
[!IF "contains(text:split($Dio_chnl_list,','),concat('(',node:name(.),')')) = 'true'"!]
[!ERROR!][!//
Symbolic Name of a channel shall not be assigned to more than one PortPin.
The Channel name '[!"node:name(.)"!]' is used for channels more than once.
Location: Dio/DioConfig/DioPort/[!"node:name(./../..)"!]/DioChannel/[!"node:name(.)"!]
[!ENDERROR!][!//
[!ENDIF!]
[!VAR "Dio_chnl_list" = "concat($Dio_chnl_list,',','(',node:name(.),')')"!]
[!ENDLOOP!]
[!ENDLOOP!]
[!ENDSELECT!]
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: Dio_GVerify_Unique_Channel_Grp_Name

  Macro to check containers with duplicate Channel name

  Input Parameters:
  none
*****************************************************************************/!]
[!/* [cover parentID={32E02A67-2C0E-4760-8378-0098256592DD}] [/cover]*/!]
[!MACRO "Dio_GVerify_Unique_Channel_Grp_Name"!][!//
[!//
[!NOCODE!][!//
[!SELECT "as:modconf('Dio')[1]"!][!//
[!LOOP "./DioConfig/DioPort/*"!]
[!VAR "Dio_chnl_grp_list" = "''"!]
[!LOOP "./DioChannelGroup/*"!]
[!IF "contains(text:split($Dio_chnl_grp_list,','),concat('(',node:value(./DioChannelGroupIdentification),')')) = 'true'"!]
[!ERROR!][!//
Symbolic Name of a Channel Group shall not be assigned to more than one PortPin.
The Channel Group name "[!"./DioChannelGroupIdentification"!]" is used for channels more than once.
Location: Dio/DioPort/[!"node:name(./../..)"!]/DioChannel/[!"node:name(.)"!]
[!ENDERROR!][!//
[!ENDIF!]
[!VAR "Dio_chnl_grp_list" = "concat($Dio_chnl_grp_list,',','(',node:value(./DioChannelGroupIdentification),')')"!]
[!ENDLOOP!]
[!ENDLOOP!]
[!ENDSELECT!]
[!ENDNOCODE!][!//
[!ENDMACRO!][!//