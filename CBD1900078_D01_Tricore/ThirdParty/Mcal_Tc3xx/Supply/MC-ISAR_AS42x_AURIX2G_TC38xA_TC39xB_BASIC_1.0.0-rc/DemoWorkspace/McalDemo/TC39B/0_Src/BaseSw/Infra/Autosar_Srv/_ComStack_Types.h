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
**  FILENAME     : ComStack_Types.h                                           **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2017-10-26                                                 **
**                                                                            **
**  VARIANT      : NA                                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Type Definition for Com Stack                              **
**                                                                            **
**  SPECIFICATION(S) : AUTOSAR_SWS_CommunicationStackTypes.pdf, AUTOSAR       **
**                     Release 4.2.2                                          **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
/* Traceability:
 [cover parentID={6EFE97CB-F5F0-460e-B4C5-1D143599991E}]
 Files inclusion
 [/cover]*/

#ifndef COMSTACK_TYPES_H
#define COMSTACK_TYPES_H

/*****************************************************************************
**                      Include Section                                     **
*****************************************************************************/
/* Traceability:
 [cover parentID={B6DD2FBA-E4D7-4e6f-9065-124B8D8B5F50}]
 [/cover]*/
#include "Std_Types.h"                  /* standard AUTOSAR types           */
#include "ComStack_Cfg.h"
/*****************************************************************************
**                      Global Symbols                                      **
*****************************************************************************/

/*****************************************************************************
**                      Global Data Types (ECU independent)                 **
*****************************************************************************/
/* The Icom configuration ID */
/* [cover parentID={C6CBF19E-19A1-4338-85A1-366B31DBA968}]IcomConfigIdType
[/cover]*/
typedef uint8  IcomConfigIdType;

/* Used to store the identifier of a partial network cluster. */
/* [cover parentID={6FB37B9C-5AC0-484a-9BA5-94B09E359C50}]PNCHandleType
[/cover]*/
typedef uint8  PNCHandleType;

/* Variables of this type shall be used to return the bus status
   evaluated by a transceiver. */
/* [cover parentID={E134E973-F450-4924-9729-DE3A5E2234DC}]BusTrcvErrorType
[/cover]*/
typedef uint8  BusTrcvErrorType;
#define BUSTRCV_OK ((BusTrcvErrorType)0x00u)
#define BUSTRCV_E_ERROR ((BusTrcvErrorType)0x01u)

/* The type for errors which can occur when activating or
deactivating Pretended Networking. */
/* [cover parentID={5ED8F4C5-785C-40fc-B621-A4FC059D2BBB}]IcomSwitch_ErrorType
[/cover]*/
typedef enum
{
  ICOM_SWITCH_E_OK,
  ICOM_SWITCH_E_FAILED
} IcomSwitch_ErrorType;

/* Basic information about a PDU of any type */
/* [cover parentID={A138E53B-1017-4f49-83DD-1D456533BF90}]PduInfoType[/cover]*/
typedef struct
{
  uint8          *SduDataPtr;
  PduLengthType   SduLength;
} PduInfoType;

/* Variables of this type shall be used to store the result of a buffer request. */
typedef enum
{
  BUFREQ_OK,
  BUFREQ_E_NOT_OK,
  BUFREQ_E_BUSY,
  BUFREQ_E_OVFL
} BufReq_ReturnType;

/*****************************************************************************
**                      Global Data                                         **
*****************************************************************************/


/*****************************************************************************
**                      Global Functions                                    **
*****************************************************************************/


#endif /* COMSTACK_TYPES_H */
