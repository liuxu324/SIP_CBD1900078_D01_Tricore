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
**  FILENAME  : Dio_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 3.0.0                                                         **
**                                                                            **
**  DATE      : 2018-08-07                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Dio.bmd                                           **
**                                                                            **
**  VARIANT   : Variant LT                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={E904F353-1698-4047-B0E7-3F3F73EB6811}]    **
**                                                                            **
**  DESCRIPTION  : Code template header file for Dio Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Dio Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!]
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
**  FILENAME  : Dio_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 1.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                                      **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                                          ** 
**                                                                            **
**  BSW MODULE DECRIPTION : Dio.bmd                                           **
**                                                                            **
**  VARIANT   : Variant LT                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Dio configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Dio Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef DIO_CFG_H
#define DIO_CFG_H
[!//
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Dio')"!][!//
[!//
[!/* Include Code Generator Macros */!][!//
[!NOCODE!][!//
[!INCLUDE "..\Dio.m"!][!//
[!ENDNOCODE!][!//
[!//
[!/* Verify the validity of DIO configuration */!][!//
[!CALL "Dio_VerifyDioConfig"!][!//
[!//
/*
 Notes:
 - The runtime configuration is handled by the Port Driver Module.
 - The configuration and usage of the DIO Driver Module is adapted to
   the microcontroller and ECU.

*/

/*Version check macros */
[!NOCODE!][!//
[!VAR "AsMajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
[!VAR "AsMinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
[!VAR "AsRevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
[!ENDNOCODE!][!//
#define DIO_AR_RELEASE_MAJOR_VERSION     ([!"$AsMajorVersion"!]U)
#define DIO_AR_RELEASE_MINOR_VERSION     ([!"$AsMinorVersion"!]U)
#define DIO_AR_RELEASE_REVISION_VERSION  ([!"$AsRevisionVersion"!]U)

[!NOCODE!][!//
[!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
[!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
[!VAR "SwRevisionVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
[!ENDNOCODE!][!//

#define DIO_SW_MAJOR_VERSION  ([!"$SwMajorVersion"!]U)
#define DIO_SW_MINOR_VERSION  ([!"$SwMinorVersion"!]U)
#define DIO_SW_PATCH_VERSION  ([!"$SwRevisionVersion"!]U)

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/*                          Container: DioGeneral                            */
/*

  Pre-processor switch to enable/disable detection of Development errors.
  - if defined ON, Development error detection is enabled
  - if defined OFF, Development error detection is disabled
*/
 /* [cover parentID={77FB036C-3267-4076-BF13-2B2A1E6213E3}] [/cover]*/
#define DIO_DEV_ERROR_DETECT                [!//
[!CALL "Dio_ConfigSwitch","nodeval" = "DioGeneral/DioDevErrorDetect"!][!//

/*
  Pre-Compiler switch to include the API Dio_GetVersionInfo()
  - if defined ON, Dio_GetVersionInfo API available
  - if defined OFF, Dio_GetVersionInfo API not available
*/
#define DIO_VERSION_INFO_API                [!//
[!CALL "Dio_ConfigSwitch","nodeval" = "DioGeneral/DioVersionInfoApi"!][!//

/*
  Pre-Compiler switch to include the API Dio_FlipChannel()
  - if defined ON, Dio_FlipChannel API available
  - if defined OFF, Dio_FlipChannel API not available
*/
#define DIO_FLIP_CHANNEL_API                [!//
[!CALL "Dio_ConfigSwitch","nodeval" = "DioGeneral/DioFlipChannelApi"!][!//

/*
  Pre-Compiler switch to include the Safety Check
*/  
#define DIO_SAFETY_ENABLE                [!//
[!CALL "Dio_ConfigSwitch","nodeval" = "DioGeneral/DioSafetyEnable"!][!//

/* The following macros are available only if development error detection
    is enabled */
[!IF "(DioGeneral/DioDevErrorDetect = 'true')or(DioGeneral/DioSafetyEnable = 'true')"!][!//
/* Definition to specify the ports available on the microcontroller
   Bit value = 0 implies the port is not available
   Bit value = 1 implies the port is available
   Bit 0 is for Port 0, Bit 1 is for Port 1, ... , Bit 31 is for Port 31 */
[!CALL "Dio_GetPortsAvailable00to31"!][!//

/* Definition to specify the ports available on the microcontroller
   Bit value = 0 implies the port is not available
   Bit value = 1 implies the port is available
   Bit 0 is for Port 32, Bit 1 is for Port 33, ... , Bit 31 is for Port 63 */
[!CALL "Dio_GetPortsAvailable32to63"!][!//

/* Definition to specify the ports that are read only ports on the
   microcontroller
   Bit value = 0 implies the port readable/writable
   Bit value = 1 implies the port is read only port
   Bit 0 is for Port 0, Bit 1 is for Port 1, ... , Bit 31 is for Port 31 */
[!CALL "Dio_GetReadOnlyPorts00to31"!][!//

/* Definition to specify the ports that are read only ports on the
   microcontroller
   Bit value = 0 implies the port readable/writable
   Bit value = 1 implies the port is read only port
   Bit 0 is for Port 32, Bit 1 is for Port 33, ... , Bit 31 is for Port 63 */
[!CALL "Dio_GetReadOnlyPorts32to63"!][!//

/* Value of the most significant pin on the port
   Note: In case of no pins on a port, the value is kept 0 */
[!CALL "Dio_GetPortMSPin"!][!//
[!ENDIF!][!//  DioDecerrorDetect

/* Macro to define the maximum port available */
[!CALL "Dio_GetMaxAvailablePort"!][!//

[!/* Macro to define the values to mask for the port pins */!][!//
[!CALL "Dio_GetMaskForPortPins"!][!//

/* Macro to define the No of channel groups configured */
[!CALL "Dio_GetNumOfDioChannelGroupsConfigured"!][!//
#define DIO_CHANNELGROUPCOUNT               ([!"$NumOfGroups"!]U)


/*******************************************************************************
**                           Global Symbols                                   **
*******************************************************************************/

/*
 Symbolic names for DIO Channels, Port & Channel groups
*/

/*
                       Symbolic names for Channels
*/
[!FOR "PortNumber" = "num:i(0)" TO "ecu:get('Dio.MaxAvailablePort')"!][!//
[!//
[!IF "contains(ecu:get('Dio.AvailablePorts'),concat('_',$PortNumber,'_'))"!][!//
[!CALL "Dio_GetDioChannelSymbolicNames","PortNum" = "$PortNumber"!][!//
[!ENDIF!][!//
[!//
[!ENDFOR!]

/*
                      Symbolic names for DIO ports
*/
[!CALL "Dio_GetDioPortSymbolicNames"!][!//

/*
     User Defined Symbolic Names for the DIO Ports, Channels & Channel Groups
*/
[!CALL "Dio_GetUserDefinedSymbolicNames"!][!//



/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/
[!VAR "configstruct" = "as:name(as:modconf('Dio')[1]/DioConfig)"!][!//
#define DIO_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
#include "Dio_MemMap.h"

extern const struct Dio_ConfigType Dio_Config; 
#define DIO_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines 
Dio_Memmap.h header is included without safegaurd.*/
#include "Dio_MemMap.h"
/*******************************************************************************
**                      Global Data Type                                      **
*******************************************************************************/
[!ENDSELECT!]
/* End of DIO_CFG_H */
#endif
