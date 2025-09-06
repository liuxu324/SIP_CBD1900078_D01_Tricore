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
**  FILENAME     : ComStack_Cfg.h                                             **
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
**  DESCRIPTION  : Configuration header file for Com Stack                    **
**                                                                            **
**  SPECIFICATION(S) : AUTOSAR_SWS_CommunicationStackTypes.pdf, AUTOSAR       **
**                     Release 4.2.2                                          **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#ifndef COMSTACK_CFG_H
#define COMSTACK_CFG_H

/*****************************************************************************
**                      Include Section                                     **
*****************************************************************************/

/*****************************************************************************
**                      Global Symbols                                      **
*****************************************************************************/


/*****************************************************************************
**                      Global Data Types (ECU dependent)                   **
*****************************************************************************/

/* [cover parentID={4FFAA8E2-213A-4482-A81D-4A4E70AF1A37}]PduIdType [/cover]*/
typedef uint8        PduIdType;     /* Type of PDU ID.
                                    Allowed ranges: uint8 .. uint16 */

/* [cover parentID={2C4B621E-4460-43f2-89DC-12DE51986F1D}]PduLengthType
[/cover]*/
typedef uint16       PduLengthType; /* Type of PDU Length.
                                    Allowed ranges: uint8 .. uint32 */

#endif
