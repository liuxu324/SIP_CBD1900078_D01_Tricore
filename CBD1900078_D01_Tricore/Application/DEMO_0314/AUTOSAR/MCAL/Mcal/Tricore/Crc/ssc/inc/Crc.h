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
**  FILENAME     : Crc.h                                                      **
**                                                                            **
**  VERSION      : 7.0.0                                                      **
**                                                                            **
**  DATE         : 2018-08-21                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Crc Driver header definition file                          **
**                                                                            **
**  SPECIFICATION(S) : Specification of CRC Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={C3614EB3-C9C9-4b17-8FAF-026924C2E58C}]
[/cover] */
#ifndef CRC_H
#define CRC_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* [cover parentID={586E54A0-2AAC-440d-959C-9E35505AE385}]
[/cover] */
/* Inclusion of Std_Types.h */
#include "Std_Types.h"
#include "Mcal_Compiler.h"

/* Pre-compile/static configuration parameters for CRC                        */
#include "Crc_Cfg.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* [cover parentID={6177EC5E-D0F1-4b2b-96F7-266EA6F8E040}]
[/cover] */
/* CRC VENDOR ID */
#define CRC_VENDOR_ID               (17U)
/* CRC MODULE ID */
#define CRC_MODULE_ID               (201U)


#if (CRC_SAFETYENABLE == STD_ON) 
/* CRC INSTANCE ID */
#define CRC_INSTANCE_ID      (0U)
/* API Service ID's */
#define CRC_SID_GETVERSIONINFO       ((uint8)0x04U)
#define CRC_SID_CALCULATE_CRC8       ((uint8)0x01U)
#define CRC_SID_CALCULATE_CRC8H2F    ((uint8)0x05U)
#define CRC_SID_CALCULATE_CRC16      ((uint8)0x02U)
#define CRC_SID_CALCULATE_CRC32      ((uint8)0x03U)
#define CRC_SID_CALCULATE_CRC32P4    ((uint8)0x06U)

/* Safety Error values  */ 
/* [cover parentID={E2F59094-3191-48c1-99E6-84A0FA74FAFB}]
[/cover] */
#define CRC_E_PARAM_POINTER     ((uint8)0xC8U)
/* [cover parentID={0919B3EB-452A-4ce6-BEB9-92097D6BB555}]
[/cover] */
#define CRC_E_PARAM_LENGTH      ((uint8)0xC9U)
/* [cover parentID={BB052966-0A14-42e3-804B-8BF67CA6537F}]
[/cover] */
#define CRC_E_CHANNEL_TIMEOUT   ((uint8)0xCAU)
#endif
 /* Mode of operation */
#define CRC_MCAL_SUPERVISOR                 (0U)
#define CRC_MCAL_USER1                      (1U)


/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/


/**********************************************************
 * Initial register values
 **********************************************************/



/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/
/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/



/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
/* Memory Map of the CRC Code */
#define CRC_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"

/*******************************************************************************
** Traceability   : [ ]                                                       **
**                                                                            **
** Syntax         : void Crc_GetVersionInfo                                   **
**                                 (Std_VersionInfoType *Versioninfo)         **
**                                                                            **
** Description    : This service returns the version information              **
**                  of this module.The version information includes :         **
**                  - Module Id                                               **
**                  - Vendor Id                                               **
**                  - Vendor specific version numbers                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : 0x04                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : None                                                      **
**                                                                            **
** Parameters(out): versioninfo (Pointer to where to store the version        **
**                               information of this module)                  **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/

#if (CRC_VERSION_INFO_API == STD_ON)
    
extern void Crc_GetVersionInfo(Std_VersionInfoType* const Versioninfo);
#else
    
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used for Error 
   indication when Crc_GetVersionInfo() API is not selected. 
   No functional impact*/
#define Crc_GetVersionInfo(Versioninfo)\
                                 ERROR_Crc_GetVersionInfo_NOT_SELECTED
#endif
/*******************************************************************************
** Traceability   :                                                           **
** Syntax     : extern uint8 Crc_CalculateCRC8                                **
**      (                                                                     **
**       const uint8* const Crc_DataPtr,                                      **
**         const uint32 Crc_Length,                                           **
**       const uint8 Crc_StartValue8,                                         **
**       const boolean Crc_IsFirstCall                                        **
**      )                                                                     **
**                                                                            **
** Service ID     : 0x01                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : conditionally reentrant                                   **
**                                                                            **
** Parameters(in)   :  Crc_DataPtr  - Pointer to the start of the datablock   **
**        Crc_Length - Length of the input data to be fetched                 **
**        Crc_StartValue8 -Start value for CRC Calculation                    **
**        Crc_IsFirstCall -Boolean to decIDe the start value                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value   : uint8                                                     **
**                                                                            **
** Description    : This function:                                            **
** - This function takes the value of input data pointer, start value and     **
**   polynomial, calculates the crc taking the precomputed                    **
**    and reversed xor value  and returns the CRC xored with XOR value        **
*******************************************************************************/

#ifdef CRC_8_MODE

extern uint8 Crc_CalculateCRC8
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint8 Crc_StartValue8,
  const boolean Crc_IsFirstCall
) ;

#endif
/*******************************************************************************
** Traceability   :                                                           **
** Syntax     : extern uint8 Crc_CalculateCRC8H2F                             **
**      (                                                                     **
**       const uint8* const Crc_DataPtr,                                      **
**       const uint32 Crc_Length,                                             **
**       const uint8 Crc_StartValue8H2F,                                      **
**       const boolean Crc_IsFirstCall                                        **
**      )                                                                     **
**                                                                            **
** Service ID     : 0x05                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : reentrant                                                 **
**                                                                            **
** Parameters(in)   :  Crc_DataPtr  - Pointer to the start of the datablock   **
**        Crc_Length - Length of the input data to be fetched                 **
**        Crc_StartValue8H2F -Start value for CRC Calculation                 **
**        Crc_IsFirstCall -Boolean to decIDe the start value                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value   : uint8                                                     **
**                                                                            **
** Description    : This function:                                            **
** - This function takes the value of input data pointer, start value and     **
**   polynomial, calculates the crc taking the precomputed                    **
**    and reversed xor value  and returns the CRC xored with XOR value        **
*******************************************************************************/

#ifdef CRC_8H2F_MODE

extern uint8 Crc_CalculateCRC8H2F
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint8 Crc_StartValue8H2F,
  const boolean Crc_IsFirstCall
);

#endif
/*******************************************************************************
** Traceability                                                               **
** Syntax     : extern uint16 Crc_CalculateCRC16                              **
**      (                                                                     **
**       const uint8* const Crc_DataPtr,                                      **
**       const uint32 Crc_Length,                                             **
**       const uint16 Crc_StartValue16,                                       **
**       const boolean Crc_IsFirstCall                                        **
**      )                                                                     **
**                                                                            **
** Service ID     : 0x02                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : conditionally reentrant                                   **
**                                                                            **
** Parameters(in)   :  Crc_DataPtr  - Pointer to the start of the datablock   **
**        Crc_Length - Length of the input data to be fetched                 **
**        Crc_StartValue16 -Start value for CRC Calculation                   **
**        Crc_IsFirstCall -Boolean to decIDe the start value                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value   : uint16                                                    **
**                                                                            **
** Description    : This function:                                            **
** - This function takes the value of input data pointer, start value and     **
**   polynomial, calculates the crc taking the precomputed                    **
**    and reversed xor value  and returns the CRC xored with XOR value        **
*******************************************************************************/
#ifdef CRC_16_MODE

extern uint16 Crc_CalculateCRC16
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint16 Crc_StartValue16,
  const boolean Crc_IsFirstCall
);

#endif
/*******************************************************************************
** Traceability   :                                                           **
** Syntax     : extern uint32 Crc_CalculateCRC32                              **
**      (                                                                     **
**       const uint8* Crc_DataPtr,                                            **
**       const uint32 Crc_Length,                                             **
**       const uint32 Crc_StartValue32,                                       **
**       const boolean Crc_IsFirstCall                                        **
**      )                                                                     **
**                                                                            **
** Service ID     : 0x03                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : conditionally reentrant                                   **
**                                                                            **
** Parameters(in)   :  Crc_DataPtr  - Pointer to the start of the datablock   **
**        Crc_Length - Length of the input data to be fetched                 **
**        Crc_StartValue32 -Start value for CRC Calculation                   **
**        Crc_IsFirstCall -Boolean to decIDe the start value                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value   : uint32                                                    **
**                                                                            **
** Description    : This function:                                            **
** - This function takes the value of input data pointer, start value and     **
**   polynomial, calculates the crc taking the precomputed                    **
**    and reversed xor value  and returns the CRC xored with XOR value        **
*******************************************************************************/
#ifdef CRC_32_MODE

extern uint32 Crc_CalculateCRC32
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint32 Crc_StartValue32,
  const boolean Crc_IsFirstCall
);

#endif

/*******************************************************************************
** Traceability   :                                                           **
** Syntax     : uint32 Crc_CalculateCRC32P4                                   **
**      (                                                                     **
**       const uint8* const Crc_DataPtr,                                      **
**       const uint32 Crc_Length,                                             **
**       const uint32 Crc_StartValue32,                                       **
**       const boolean Crc_IsFirstCall                                        **
**      )                                                                     **
**                                                                            **
** Service ID     : 0x06                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : reentrant                                                 **
**                                                                            **
** Parameters(in)   :  Crc_DataPtr  - Pointer to the start of the datablock   **
**        Crc_Length - Length of the input data to be fetched                 **
**        Crc_StartValue32 -Start value for CRC Calculation                   **
**        Crc_IsFirstCall -Boolean to decIDe the start value                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value   : uint32                                                    **
**                                                                            **
** Description    : This function:                                            **
** - This function takes the value of input data pointer, start value and     **
**   polynomial, calculates the crc taking the precomputed                    **
**    and reversed xor value  and returns the CRC xored with XOR value        **
*******************************************************************************/
#ifdef CRC_32P4_MODE

extern uint32 Crc_CalculateCRC32P4
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint32 Crc_StartValue32,
  const boolean Crc_IsFirstCall
);

#endif



#define CRC_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
 without safegaurd. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"

/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/

/*******************************************************************************
**                            LOW Level Driver Definitions                    **
*******************************************************************************/

/*******************************************************************************
**                            LOW Level Driver Definitions                    **
*******************************************************************************/

#endif /* End for CRC_H */
