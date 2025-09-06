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
**  FILENAME  : Crc_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE      : 2018-08-07                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Crc.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID]                                           **
**                                                                            **
**  DESCRIPTION  : Code template header file for CRC Library                  **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of CRC Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*************************************************************************/!][!//
[!//
/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2017)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Crc_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 4.1.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                                          **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                                            **
**                                                                            **
**  BSW MODULE DECRIPTION : Crc.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : CRC configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of CRC Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={084339EF-4E3B-40a4-A767-EF7DE0D43436}]
[/cover] */

#ifndef CRC_CFG_H
#define CRC_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

#define CRC_RUNTIME_MODE        (0x01u)
#define CRC_TABLE_MODE          (0x02u)
#define CRC_HARDWARE_MODE       (0x03u)

/*Macro for Initial Values of CRC*/
#define CRC_INITIAL_VALUE8      ((uint8)0xFFU)
#define CRC_INITIAL_VALUE8H2F   ((uint8)0xFFU)
#define CRC_INITIAL_VALUE16     ((uint16)0xFFFFU)
#define CRC_INITIAL_VALUE32     ((uint32)0xFFFFFFFFU)
#define CRC_INITIAL_VALUE32P4   ((uint32)0xFFFFFFFFU)

[!AUTOSPACING!]
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Crc')[1]"!][!//
[!//

/*
         Container : CRCGeneral
*/

[!NOCODE!][!//
[!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
[!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
[!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
[!VAR "NewString" = "text:replaceAll($moduleReleaseVer,"\.",'')"!][!//
[!ENDNOCODE!][!//

/*Autosar specific information*/
/* [cover parentID={C8CF829D-BC18-49ae-9D5F-854A31BF05CB}]
[/cover] */
#define CRC_AR_RELEASE_MAJOR_VERSION  ([!"$MajorVersion"!]U)
/* [cover parentID={3DE22013-294C-4e0c-A14B-8497E12F165A}]
[/cover] */
#define CRC_AR_RELEASE_MINOR_VERSION  ([!"$MinorVersion"!]U)
/* [cover parentID={70B9BE0F-FAF9-488d-8CC5-A6AE13CFD821}]
[/cover] */
#define CRC_AR_RELEASE_REVISION_VERSION  ([!"$RevisionVersion"!]U)

[!VAR "MajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
[!VAR "MinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
[!VAR "RevisionVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
[!VAR "NewString" = "text:replaceAll($moduleSoftwareVer,"\.",'')"!][!//
/*Release specific information*/
/* [cover parentID={A18D550B-8069-42cc-8527-A3628ACF0671}]
[/cover] */
#define CRC_SW_MAJOR_VERSION  ([!"$MajorVersion"!]U)
/* [cover parentID={35FB64B1-4185-4a84-8B5E-4FB388EA4378}]
[/cover] */
#define CRC_SW_MINOR_VERSION  ([!"$MinorVersion"!]U)
/* [cover parentID={05A83C53-F0D3-422d-A45A-1EAC95B9E477}]
[/cover] */
#define CRC_SW_PATCH_VERSION  ([!"$RevisionVersion"!]U)
/*Macro for versioninfoapi*/
/* [cover parentID={6A16D240-906B-4cd7-8CB5-FBFF690F8D6D}]
[/cover] */
#define CRC_VERSION_INFO_API  ([!//
[!IF "CrcGeneral/CrcVersionInfoApi  = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)
 
/*Macro for selection of 16 bit CRC method */
/* [cover parentID={8D50FC69-7BC3-4122-91DD-2E87169CBB82}]
[/cover] */
[!IF "CrcGeneral/Crc16Mode/__1 = 'CRC_16_HARDWARE'"!][!//
#define CRC_16_MODE (CRC_HARDWARE_MODE) [!//
[!ELSEIF "CrcGeneral/Crc16Mode/__1 = 'CRC_16_RUNTIME'"!][!//
#define CRC_16_MODE (CRC_RUNTIME_MODE) [!//
[!ELSEIF "CrcGeneral/Crc16Mode/__1 = 'CRC_16_TABLE'"!][!//
#define CRC_16_MODE (CRC_TABLE_MODE) [!//
[!ELSE!][!//
#define CRC_16_MODE (STD_OFF) [!//
[!ENDIF!][!//


/*Macro for selection of 32 bit CRC method */
/* [cover parentID={098DB2FF-8290-4c2d-8619-317E04E2EE0A}]
[/cover] */
[!IF "CrcGeneral/Crc32Mode/__1 = 'CRC_32_HARDWARE'"!][!//
#define CRC_32_MODE (CRC_HARDWARE_MODE) [!//
[!ELSEIF "CrcGeneral/Crc32Mode/__1 = 'CRC_32_RUNTIME'"!][!//
#define CRC_32_MODE (CRC_RUNTIME_MODE) [!//
[!ELSEIF "CrcGeneral/Crc32Mode/__1 = 'CRC_32_TABLE'"!][!//
#define CRC_32_MODE (CRC_TABLE_MODE) [!//
[!ELSE!][!//
#define CRC_32_MODE (STD_OFF) [!//
[!ENDIF!][!//

/*Macro for selection of 32 bit CRCP4 method */
/* [cover parentID={F9704DEB-1CA1-41a1-BC0D-A5FF70408FBB}]
[/cover] */
[!IF "CrcGeneral/Crc32P4Mode/__1 = 'CRC_32P4_HARDWARE'"!][!//
#define CRC_32P4_MODE (CRC_HARDWARE_MODE) [!//
[!ELSEIF "CrcGeneral/Crc32P4Mode/__1 = 'CRC_32P4_RUNTIME'"!][!//
#define CRC_32P4_MODE (CRC_RUNTIME_MODE) [!//
[!ELSEIF "CrcGeneral/Crc32P4Mode/__1 = 'CRC_32P4_TABLE'"!][!//
#define CRC_32P4_MODE (CRC_TABLE_MODE) [!//
[!ELSE!][!//
#define CRC_32P4_MODE (STD_OFF) [!//
[!ENDIF!][!//

/*Macro for selection of 8 bit CRC method with 0x1D polynomial*/ 
/* [cover parentID={8C3F4ADF-2550-4c70-B539-0AB11F17451E}]
[/cover] */
[!IF "CrcGeneral/Crc8Mode/__1 = 'CRC_8_HARDWARE'"!][!//
#define CRC_8_MODE (CRC_HARDWARE_MODE)[!//
[!ELSEIF "CrcGeneral/Crc8Mode/__1 = 'CRC_8_RUNTIME'"!][!//
#define CRC_8_MODE (CRC_RUNTIME_MODE)[!//
[!ELSEIF "CrcGeneral/Crc8Mode/__1 = 'CRC_8_TABLE'"!][!//
#define CRC_8_MODE (CRC_TABLE_MODE)[!//
[!ELSE!][!//
#define CRC_8_MODE (STD_OFF) [!//
[!ENDIF!][!//  

/*Macro for selection of 8 bit CRC method with 0x2F polynomial*/
/* [cover parentID={8278D7D6-0C00-431b-9CA0-2A2E4A619F7E}]
[/cover] */
[!IF "CrcGeneral/Crc8H2FMode/__1 = 'CRC_8H2F_RUNTIME'"!][!//
#define CRC_8H2F_MODE (CRC_RUNTIME_MODE)[!//
[!ELSEIF "CrcGeneral/Crc8H2FMode/__1 = 'CRC_8H2F_TABLE'"!][!//
#define CRC_8H2F_MODE (CRC_TABLE_MODE)[!//
[!ELSE!][!//
#define CRC_8H2F_MODE (STD_OFF) [!//
[!ENDIF!][!//


/*Macro to enable /disable safety check*/
/* [cover parentID={87869FC4-1164-45e8-8548-E39AA9D48E90}]
[/cover] */
[!IF "CrcGeneral/CrcSafetyEnable = 'true'"!][!//
#define CRC_SAFETYENABLE              (STD_ON)[!//


/*Macro for error return value for each polynomials*/
/* [cover parentID={A60567C6-251A-4660-9460-9766D4EC0276}]
[/cover] */
#define CRC_8_CONFIGERROR_VAL          ([!"CrcGeneral/Crc8ReturnErrorValue"!])[!//

/* [cover parentID={4FEFB7F2-F95F-4c8b-A057-17E7E157EFBA}]
[/cover] */
#define CRC_8H2F_CONFIGERROR_VAL    ([!"CrcGeneral/Crc8H2FReturnErrorValue"!])[!//

/* [cover parentID={22A1CF66-8320-4605-A060-D812133F6700}]
[/cover] */
#define CRC_16_CONFIGERROR_VAL      ([!"CrcGeneral/Crc16ReturnErrorValue"!])[!//

/* [cover parentID={D25344CE-D478-4a48-B2B6-84FF7804BC6B}]
[/cover] */
#define CRC_32_CONFIGERROR_VAL      ([!"CrcGeneral/Crc32ReturnErrorValue"!])[!//

/* [cover parentID={58609002-A43B-4ebc-841B-FA5E65C9AEC9}]
[/cover] */
#define CRC_32P4_CONFIGERROR_VAL      ([!"CrcGeneral/Crc32P4ReturnErrorValue"!])[!//

[!ELSE!][!//
#define CRC_SAFETYENABLE  (STD_OFF)[!//

[!ENDIF!][!//
/*Macro for user/supervisory mode */
/* [cover parentID={33109129-E4F3-42a3-80B6-30DD41F04CAC}]
[/cover] */

#define CRC_RUNTIME_API_MODE    ([!"CrcGeneral/CrcRuntimeApiMode"!])

[!ENDSELECT!][!//

#endif  /* CRC_CFG_H */

