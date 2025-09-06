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
**  FILENAME     : Crc.c                                                      **
**                                                                            **
**  VERSION      : 9.0.0                                                      **
**                                                                            **
**  DATE         : 2018-09-06                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Crc Driver source file                                     **
**                                                                            **
**  SPECIFICATION(S) : Specification of CRC Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                              **
**                                                                            **
*******************************************************************************/


/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* [cover parentID={B5B329DB-513F-4a82-BB6A-B8A816951405}]
[/cover] */
/* Include microcontroller SFR headers */
#include "IfxFce_reg.h"

/* Include McalLib functions */
#include "McalLib.h"

/* Include Crc.h header */
#include "Crc.h"

/* Include Schm functions */
#include "SchM_Crc.h"

#if (CRC_RUNTIME_API_MODE != CRC_MCAL_SUPERVISOR)
#include "McalLib_OsStub.h"
#endif
/* Import of Safety functionality.*/
#if (CRC_SAFETYENABLE == STD_ON)
#include "Mcal_SafetyError.h"
#endif
/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

/* AUTOSAR Specification File Version Check */
#ifndef CRC_AR_RELEASE_MAJOR_VERSION
#error "CRC_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif
/*#endif for #ifndef CRC_AR_RELEASE_MAJOR_VERSION */

#ifndef CRC_AR_RELEASE_MINOR_VERSION
#error "CRC_AR_RELEASE_MINOR_VERSION is not defined. "
#endif
/*#endif for #ifndef CRC_AR_RELEASE_MINOR_VERSION */

#ifndef CRC_AR_RELEASE_REVISION_VERSION
#error "CRC_AR_RELEASE_REVISION_VERSION is not defined. "
#endif
/*#endif for #ifndef CRC_AR_RELEASE_MINOR_VERSION */

/* [cover parentID={A18D550B-8069-42cc-8527-A3628ACF0671}]
[/cover] */
#ifndef CRC_SW_MAJOR_VERSION
#error "CRC_SW_MAJOR_VERSION is not defined. "
#endif
/*#endif for #ifndef CRC_SW_MAJOR_VERSION */
/* [cover parentID={35FB64B1-4185-4a84-8B5E-4FB388EA4378}]
[/cover] */
#ifndef CRC_SW_MINOR_VERSION
#error "CRC_SW_MINOR_VERSION is not defined. "
#endif
/*#endif for #ifndef CRC_SW_MINOR_VERSION */

#ifndef CRC_SW_PATCH_VERSION
#error "CRC_SW_PATCH_VERSION is not defined. "
#endif
/*#endif for #ifndef CRC_SW_PATCH_VERSION */

/* [cover parentID={B570B431-86E0-4293-8B1F-CD58B339F06B}]
[/cover] */
#if ( CRC_AR_RELEASE_MAJOR_VERSION != 4U)
#error "CRC_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#if ( CRC_AR_RELEASE_MINOR_VERSION != 2U )
#error "CRC_AR_RELEASE_MINOR_VERSION does not match. "
#endif

#if (CRC_SW_MAJOR_VERSION != 4U)
#error "CRC_SW_MAJOR_VERSION does not match. "
#endif
/*#endif for  #if (CRC_SW_MAJOR_VERSION != 4U)*/

#if (CRC_SW_MINOR_VERSION != 1U)
#error "CRC_SW_MINOR_VERSION does not match. "
#endif
/*#endif for  #if (CRC_SW_MINOR_VERSION != 1U)*/



/******************************************************************/

/****************************************************************************
**                      Private Macro Definitions                          **
****************************************************************************/
/* ********** Macros - General ***********    */
#if ((CRC_8_MODE != STD_OFF)||(CRC_8H2F_MODE != STD_OFF) || \
(CRC_16_MODE != STD_OFF)||(CRC_32_MODE != STD_OFF) || \
(CRC_32P4_MODE != STD_OFF))

#define CRC_ZERO_U          (0U)
#endif

#if ((CRC_8_MODE == CRC_RUNTIME_MODE) || (CRC_8_MODE == CRC_HARDWARE_MODE) || \
(CRC_8H2F_MODE == CRC_RUNTIME_MODE)||(CRC_16_MODE == CRC_RUNTIME_MODE) || \
(CRC_16_MODE == CRC_HARDWARE_MODE) ||(CRC_32_MODE != STD_OFF) || \
(CRC_32P4_MODE != STD_OFF))

#define CRC_ONE_U           (1U)
#endif

#if ((CRC_8_MODE == CRC_RUNTIME_MODE) || (CRC_8_MODE == CRC_TABLE_MODE)    ||  \
(CRC_8H2F_MODE == CRC_RUNTIME_MODE)||(CRC_8H2F_MODE == CRC_TABLE_MODE) ||  \
(CRC_16_MODE != STD_OFF) || (CRC_32_MODE != STD_OFF) ||  \
(CRC_32P4_MODE != STD_OFF))

#define CRC_BYTELENGTH_U         (8U)
#endif

#if ((CRC_8_MODE == CRC_TABLE_MODE)||(CRC_8H2F_MODE == CRC_TABLE_MODE) || \
(CRC_16_MODE == CRC_TABLE_MODE)||(CRC_32_MODE == CRC_TABLE_MODE) || \
(CRC_32P4_MODE == CRC_TABLE_MODE))

#define CRC_TABLE_LENGTH            ((uint32)256U)
#endif

#if ((CRC_8_MODE == CRC_HARDWARE_MODE) || (CRC_16_MODE == CRC_HARDWARE_MODE) ||\
(CRC_32_MODE == CRC_HARDWARE_MODE)|| (CRC_32P4_MODE == CRC_HARDWARE_MODE))
#define CRC_MAXCHANNELS_U             (8U)
#define CRC_TIMEOUT_VAL             (10000U)
#define CRC_SPINLOCKTIMEOUT_VAL     (2500U)
#endif

#if (CRC_16_MODE == CRC_HARDWARE_MODE)||(CRC_32_MODE ==  CRC_HARDWARE_MODE)||  \
(CRC_32P4_MODE == CRC_HARDWARE_MODE)
#define CRC_TWO_U                   ((uint32)2U)
#endif

#if (CRC_32_MODE != STD_OFF) || (CRC_32P4_MODE != STD_OFF)
#define CRC_BITCNT_THIRTYTWO            ((uint8)32U)
#endif

#if (CRC_32_MODE == CRC_RUNTIME_MODE) || (CRC_32P4_MODE == CRC_RUNTIME_MODE)
#define CRC_CRC32_SIZE      (32U)
#define CRC_CRC32_MSB       ((uint32)0x80000000U)
#endif

#if (CRC_32_MODE == CRC_HARDWARE_MODE) || (CRC_32P4_MODE == CRC_HARDWARE_MODE)
#define CRC_THREE_U                 ((uint32)3U)
#define CRC_FOUR_U                  ((uint32)4U)
#define CRC_SIXTEEN_U               ((uint32)16U)
#endif

#if ((CRC_32_MODE == CRC_RUNTIME_MODE)||(CRC_32P4_MODE == CRC_RUNTIME_MODE)||  \
(CRC_32_MODE == CRC_TABLE_MODE)   ||(CRC_32P4_MODE == CRC_TABLE_MODE))
#define CRC_BITCNT_EIGHT            ((uint8)8U)
#endif

#if ((CRC_32_MODE == CRC_HARDWARE_MODE)||(CRC_32P4_MODE == CRC_HARDWARE_MODE)||\
(CRC_32_MODE == CRC_TABLE_MODE)   ||(CRC_32P4_MODE == CRC_TABLE_MODE))
#define CRC_SHIFT_TWENTYFOUR        ((uint32)24U)
#endif

#if ((CRC_32_MODE == CRC_TABLE_MODE)  || (CRC_32P4_MODE == CRC_TABLE_MODE))
#define CRC_U32LSB_MASK             ((uint32)0xFFU)
#endif

#if (CRC_16_MODE == CRC_TABLE_MODE)
#define CRC_U16LSB_MASK             ((uint32)0xFFU)
#endif

/* ********** Macros - XOR values ********** */
/* These are the macros which hold the XOR values which are used
 * during the CRC computation. The values used here come from
 * the standard itself. Check the Autosar SWS for details. */
#if (CRC_8_MODE != STD_OFF)
#define CRC_CRC8_XOR_VALUE      ((uint8)0xFFU)
#endif
#if (CRC_8H2F_MODE != STD_OFF)
#define CRC_CRC8H2F_XOR_VALUE   ((uint8)0xFFU)
#endif
#if (CRC_16_MODE != STD_OFF)
#define CRC_CRC16_XOR_VALUE     ((uint16)0x0000U)
#endif
#if (CRC_32_MODE != STD_OFF)
#define CRC_CRC32_XOR_VALUE     ((uint32)0xFFFFFFFFuL)
#endif
#if (CRC_32P4_MODE != STD_OFF)
#define CRC_CRC32P4_XOR_VALUE   ((uint32)0xFFFFFFFFuL)
#endif

/* ********** Macros - for CRC size handling ********** */
#if ((CRC_8_MODE == CRC_RUNTIME_MODE) || (CRC_8H2F_MODE == CRC_RUNTIME_MODE))
#define CRC_CRC8_MSB        ((uint8)0x80)
#endif

#if (CRC_16_MODE == CRC_RUNTIME_MODE)
#define CRC_CRC16_SIZE      (16U)
#define CRC_CRC16_MSB       ((uint16)0x8000U)
#endif

/* ********** Macros - CRC polynomials ********** */
/* These are the different polynomials being used for the CRC computation.
 * The values are just as per the standard. The names which are used
 * are self explanatory. Refer the Autosar SWS for more details. */
#if (CRC_8_MODE == CRC_RUNTIME_MODE)
#define CRC_CRC8_POLYNOMIAL         ((uint8)0x1DU)
#endif

#if (CRC_8H2F_MODE == CRC_RUNTIME_MODE)
#define CRC_CRC8H2F_POLYNOMIAL      ((uint8)0x2FU)
#endif

#if (CRC_16_MODE == CRC_RUNTIME_MODE)
#define CRC_CRC16_POLYNOMIAL        ((uint16)0x1021U)
#endif

#if (CRC_32_MODE == CRC_RUNTIME_MODE)
#define CRC_CRC32_POLYNOMIAL        ((uint32)0x04C11DB7U)
#endif

#if (CRC_32P4_MODE == CRC_RUNTIME_MODE)
#define CRC_CRC32P4_POLYNOMIAL      ((uint32)0xF4ACFB13U)
#endif


/* ********** Macros for the CLC, CRC and CFG registers ********** */
#if (CRC_8_MODE == CRC_HARDWARE_MODE)

#define CRC8_CFGREG_INITVAL         ((uint32)0x00030400U)
#define CRC_FCE_IN_CRC_CRC8_MSK        (0xff)
#endif

#if (CRC_16_MODE == CRC_HARDWARE_MODE)

#define CRC16_CFGREG_INITVAL        ((uint32)0x00020000U)
#define CRC_FCE_IN_CRC_CRC16_MSK    (0xffff)
#endif

#if (CRC_32_MODE == CRC_HARDWARE_MODE)

#define CRC32_CFGREG_INITVAL        ((uint32)0x00000700U)
#endif

#if (CRC_32P4_MODE == CRC_HARDWARE_MODE)

#define CRC32P4_CFGREG_INITVAL        ((uint32)0x00010700U)
#endif

#if ((CRC_8_MODE == CRC_HARDWARE_MODE) || (CRC_16_MODE == CRC_HARDWARE_MODE) ||\
(CRC_32_MODE == CRC_HARDWARE_MODE)|| (CRC_32P4_MODE == CRC_HARDWARE_MODE))

#define CRC_CLC_INITVAL             ((uint32)0U)

/* ********** Macros for endinit protected writes ********** */
#if (CRC_RUNTIME_API_MODE  == CRC_MCAL_SUPERVISOR)
/* MISRA2012_RULE_4_9_JUSTIFICATION: A function shall be used in preference
   to a function-like macro where they are interchangeable. The deviation
   is applicable to the Mcal_WritePeripEndInitProtReg macros. */
#define CRC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(RegAdd,Data)    \
                                    Mcal_WritePeripEndInitProtReg(RegAdd,Data)
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: A function shall be used in preference
to a function-like macro where they are interchangeable. The deviation
is applicable to the Mcal_WritePeripEndInitProtReg macros. */

/* [cover parentID={1A65EADD-AFD0-4845-B2D2-8257E086DD67}]
[/cover] */
#define CRC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(RegAdd,Data)    \
                                  MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)
#endif
#endif
/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/* ---- None ----- */



/*******************************************************************************
**                 Private Function Declarations:                             **
*******************************************************************************/
/* Memory Map of the CRC Code */
#define CRC_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
 [/cover] */
/* [cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
 [/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
 [/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
 [/cover] */
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
 [/cover] */
/* [cover parentID={07DD7AB2-AF63-4d8b-8FB9-0261F77B0ED4}]
 [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
#include "Crc_MemMap.h"


#if  CRC_32_MODE == CRC_HARDWARE_MODE
static uint32 Crc_lCalculateCRC32Hardware
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint32 Crc_StartValue32,
  const boolean Crc_IsFirstCall
);
#endif
/* #if  CRC_32_MODE == CRC_HARDWARE_MODE */

#if  CRC_32_MODE == CRC_TABLE_MODE
static uint32 Crc_lCalculateCRC32Table
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint32 Crc_StartValue32,
  const boolean Crc_IsFirstCall
);
#endif
/* #if  CRC_32_MODE == CRC_TABLE_MODE  */

#if  CRC_32_MODE == CRC_RUNTIME_MODE
static uint32 Crc_lCalculateCRC32Runtime
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint32 Crc_StartValue32,
  const boolean Crc_IsFirstCall
);
#endif
/*#if  CRC_32_MODE == CRC_RUNTIME_MODE */


#if  CRC_32P4_MODE == CRC_TABLE_MODE
static uint32 Crc_lCalculateCRC32P4Table
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint32 Crc_StartValue32,
  const boolean Crc_IsFirstCall
);
#endif
/* #if  CRC_32P4_MODE == CRC_TABLE_MODE */

#if  CRC_32P4_MODE == CRC_RUNTIME_MODE
static uint32 Crc_lCalculateCRC32P4Runtime
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint32 Crc_StartValue32,
  const boolean Crc_IsFirstCall
);
#endif
/* #if  CRC_32P4_MODE == CRC_RUNTIME_MODE */

#if  CRC_32P4_MODE == CRC_HARDWARE_MODE
static uint32 Crc_lCalculateCRC32P4Hardware
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint32 Crc_StartValue32,
  const boolean Crc_IsFirstCall
);
#endif


#if (CRC_32_MODE != STD_OFF) || (CRC_32P4_MODE != STD_OFF)
static uint32 Crc_lReflectCRC32
(
  const uint32 CRCData_32bit,
  const uint8 CRC_BitCount
);
#endif
/* #if defined  (CRC_32_MODE)  || defined (CRC_32P4_MODE) */

#if ((CRC_32_MODE == CRC_RUNTIME_MODE)||(CRC_32P4_MODE == CRC_RUNTIME_MODE))
static uint32 Crc_lCommonCalculateCRC32Runtime
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint32 Crc_StartValue32,
  const uint32 Polynomial_32bit
);
#endif
/* #if defined  (CRC_32_RUNTIME_MODE)  ||
              defined (CRC_32P4_RUNTIME_MODE) */



#if  CRC_16_MODE == CRC_HARDWARE_MODE
static uint16 Crc_lCalculateCRC16Hardware
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint16 Crc_StartValue16,
  const boolean Crc_IsFirstCall
);
#endif
/* #if  CRC_16_MODE == CRC_HARDWARE_MODE */

#if  CRC_16_MODE == CRC_TABLE_MODE
static uint16 Crc_lCalculateCRC16Table
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint16 Crc_StartValue16,
  const boolean Crc_IsFirstCall
);
#endif
/* #if  CRC_16_MODE == CRC_TABLE_MODE */

#if  CRC_16_MODE == CRC_RUNTIME_MODE
static uint16 Crc_lCalculateCRC16Runtime
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint16 Crc_StartValue16,
  const boolean Crc_IsFirstCall
);
#endif
/* #if  CRC_16_MODE == CRC_RUNTIME_MODE  */



#if  CRC_8H2F_MODE == CRC_TABLE_MODE
static uint8 Crc_lCalculateCRC8H2FTable
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint8 Crc_StartValue8H2F,
  const boolean Crc_IsFirstCall
);
#endif
/* #if  CRC_8H2F_MODE == CRC_TABLE_MODE */

#if  CRC_8H2F_MODE == CRC_RUNTIME_MODE
static uint8 Crc_lCalculateCRC8H2FRuntime
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint8 Crc_StartValue8H2F,
  const boolean Crc_IsFirstCall
);
#endif
/* #if  CRC_8H2F_MODE == CRC_RUNTIME_MODE */



#if  CRC_8_MODE == CRC_HARDWARE_MODE
static uint8 Crc_lCalculateCRC8Hardware
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint8 Crc_StartValue8,
  const boolean Crc_IsFirstCall
);
#endif
/* #if  CRC_8_MODE == CRC_HARDWARE_MODE */

#if  CRC_8_MODE == CRC_TABLE_MODE
static uint8 Crc_lCalculateCRC8Table
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint8 Crc_StartValue8,
  const boolean Crc_IsFirstCall
);
#endif
/* #if  CRC_8_MODE == CRC_TABLE_MODE */

#if  CRC_8_MODE == CRC_RUNTIME_MODE
static uint8 Crc_lCalculateCRC8Runtime
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint8 Crc_StartValue8,
  const boolean Crc_IsFirstCall
);
#endif
/* #if  CRC_8_MODE == CRC_RUNTIME_MODE */

#if (CRC_8_MODE == CRC_RUNTIME_MODE)||(CRC_8H2F_MODE == CRC_RUNTIME_MODE)
static uint8 Crc_lCommonCalculateCRC8Runtime
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint8 Crc_StartValue8,
  const uint8 Polynomial_8bit
);
#endif
/* #if defined  (CRC_8_RUNTIME_MODE)  || defined (CRC_8H2F_RUNTIME_MODE) */



#define CRC_STOP_SEC_CODE_ASIL_B_GLOBAL

/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"

/*****************************************************************************
**                      Global Constant Definitions                         **
*****************************************************************************/


/* CRC 32bit polynomial=0x04C11DB7 table initialization */
#if CRC_32_MODE == CRC_TABLE_MODE

#define CRC_START_SEC_CONST_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per
 * Autosar guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly
 * included without safegaurd. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This data structure is quite
 * big is size, therefore link time relocation of table is
 * provided using Autosar Memmap definition guidelines         */
static const uint32 Crc_Table32[CRC_TABLE_LENGTH] =
{
  0x00000000UL,   0x04c11db7UL,   0x09823b6eUL,   0x0d4326d9UL,
  0x130476dcUL,   0x17c56b6bUL,   0x1a864db2UL,   0x1e475005UL,
  0x2608edb8UL,   0x22c9f00fUL,   0x2f8ad6d6UL,   0x2b4bcb61UL,
  0x350c9b64UL,   0x31cd86d3UL,   0x3c8ea00aUL,   0x384fbdbdUL,
  0x4c11db70UL,   0x48d0c6c7UL,   0x4593e01eUL,   0x4152fda9UL,
  0x5f15adacUL,   0x5bd4b01bUL,   0x569796c2UL,   0x52568b75UL,
  0x6a1936c8UL,   0x6ed82b7fUL,   0x639b0da6UL,   0x675a1011UL,
  0x791d4014UL,   0x7ddc5da3UL,   0x709f7b7aUL,   0x745e66cdUL,
  0x9823b6e0UL,   0x9ce2ab57UL,   0x91a18d8eUL,   0x95609039UL,
  0x8b27c03cUL,   0x8fe6dd8bUL,   0x82a5fb52UL,   0x8664e6e5UL,
  0xbe2b5b58UL,   0xbaea46efUL,   0xb7a96036UL,   0xb3687d81UL,
  0xad2f2d84UL,   0xa9ee3033UL,   0xa4ad16eaUL,   0xa06c0b5dUL,
  0xd4326d90UL,   0xd0f37027UL,   0xddb056feUL,   0xd9714b49UL,
  0xc7361b4cUL,   0xc3f706fbUL,   0xceb42022UL,   0xca753d95UL,
  0xf23a8028UL,   0xf6fb9d9fUL,   0xfbb8bb46UL,   0xff79a6f1UL,
  0xe13ef6f4UL,   0xe5ffeb43UL,   0xe8bccd9aUL,   0xec7dd02dUL,
  0x34867077UL,   0x30476dc0UL,   0x3d044b19UL,   0x39c556aeUL,
  0x278206abUL,   0x23431b1cUL,   0x2e003dc5UL,   0x2ac12072UL,
  0x128e9dcfUL,   0x164f8078UL,   0x1b0ca6a1UL,   0x1fcdbb16UL,
  0x018aeb13UL,   0x054bf6a4UL,   0x0808d07dUL,   0x0cc9cdcaUL,
  0x7897ab07UL,   0x7c56b6b0UL,   0x71159069UL,   0x75d48ddeUL,
  0x6b93dddbUL,   0x6f52c06cUL,   0x6211e6b5UL,   0x66d0fb02UL,
  0x5e9f46bfUL,   0x5a5e5b08UL,   0x571d7dd1UL,   0x53dc6066UL,
  0x4d9b3063UL,   0x495a2dd4UL,   0x44190b0dUL,   0x40d816baUL,
  0xaca5c697UL,   0xa864db20UL,   0xa527fdf9UL,   0xa1e6e04eUL,
  0xbfa1b04bUL,   0xbb60adfcUL,   0xb6238b25UL,   0xb2e29692UL,
  0x8aad2b2fUL,   0x8e6c3698UL,   0x832f1041UL,   0x87ee0df6UL,
  0x99a95df3UL,   0x9d684044UL,   0x902b669dUL,   0x94ea7b2aUL,
  0xe0b41de7UL,   0xe4750050UL,   0xe9362689UL,   0xedf73b3eUL,
  0xf3b06b3bUL,   0xf771768cUL,   0xfa325055UL,   0xfef34de2UL,
  0xc6bcf05fUL,   0xc27dede8UL,   0xcf3ecb31UL,   0xcbffd686UL,
  0xd5b88683UL,   0xd1799b34UL,   0xdc3abdedUL,   0xd8fba05aUL,
  0x690ce0eeUL,   0x6dcdfd59UL,   0x608edb80UL,   0x644fc637UL,
  0x7a089632UL,   0x7ec98b85UL,   0x738aad5cUL,   0x774bb0ebUL,
  0x4f040d56UL,   0x4bc510e1UL,   0x46863638UL,   0x42472b8fUL,
  0x5c007b8aUL,   0x58c1663dUL,   0x558240e4UL,   0x51435d53UL,
  0x251d3b9eUL,   0x21dc2629UL,   0x2c9f00f0UL,   0x285e1d47UL,
  0x36194d42UL,   0x32d850f5UL,   0x3f9b762cUL,   0x3b5a6b9bUL,
  0x315d626UL,    0x07d4cb91UL,   0x0a97ed48UL,   0x0e56f0ffUL,
  0x1011a0faUL,   0x14d0bd4dUL,   0x19939b94UL,   0x1d528623UL,
  0xf12f560eUL,   0xf5ee4bb9UL,   0xf8ad6d60UL,   0xfc6c70d7UL,
  0xe22b20d2UL,   0xe6ea3d65UL,   0xeba91bbcUL,   0xef68060bUL,
  0xd727bbb6UL,   0xd3e6a601UL,   0xdea580d8UL,   0xda649d6fUL,
  0xc423cd6aUL,   0xc0e2d0ddUL,   0xcda1f604UL,   0xc960ebb3UL,
  0xbd3e8d7eUL,   0xb9ff90c9UL,   0xb4bcb610UL,   0xb07daba7UL,
  0xae3afba2UL,   0xaafbe615UL,   0xa7b8c0ccUL,   0xa379dd7bUL,
  0x9b3660c6UL,   0x9ff77d71UL,   0x92b45ba8UL,   0x9675461fUL,
  0x8832161aUL,   0x8cf30badUL,   0x81b02d74UL,   0x857130c3UL,
  0x5d8a9099UL,   0x594b8d2eUL,   0x5408abf7UL,   0x50c9b640UL,
  0x4e8ee645UL,   0x4a4ffbf2UL,   0x470cdd2bUL,   0x43cdc09cUL,
  0x7b827d21UL,   0x7f436096UL,   0x7200464fUL,   0x76c15bf8UL,
  0x68860bfdUL,   0x6c47164aUL,   0x61043093UL,   0x65c52d24UL,
  0x119b4be9UL,   0x155a565eUL,   0x18197087UL,   0x1cd86d30UL,
  0x029f3d35UL,   0x065e2082UL,   0x0b1d065bUL,   0x0fdc1becUL,
  0x3793a651UL,   0x3352bbe6UL,   0x3e119d3fUL,   0x3ad08088UL,
  0x2497d08dUL,   0x2056cd3aUL,   0x2d15ebe3UL,   0x29d4f654UL,
  0xc5a92679UL,   0xc1683bceUL,   0xcc2b1d17UL,   0xc8ea00a0UL,
  0xd6ad50a5UL,   0xd26c4d12UL,   0xdf2f6bcbUL,   0xdbee767cUL,
  0xe3a1cbc1UL,   0xe760d676UL,   0xea23f0afUL,   0xeee2ed18UL,
  0xf0a5bd1dUL,   0xf464a0aaUL,   0xf9278673UL,   0xfde69bc4UL,
  0x89b8fd09UL,   0x8d79e0beUL,   0x803ac667UL,   0x84fbdbd0UL,
  0x9abc8bd5UL,   0x9e7d9662UL,   0x933eb0bbUL,   0x97ffad0cUL,
  0xafb010b1UL,   0xab710d06UL,   0xa6322bdfUL,   0xa2f33668UL,
  0xbcb4666dUL,   0xb8757bdaUL,   0xb5365d03UL,   0xb1f740b4UL
};

#define CRC_STOP_SEC_CONST_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per
 * Autosar guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly
 * included without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
#endif
/* #if CRC_32_MODE == CRC_TABLE_MODE*/


/* CRC 32bit polynomial=0xF4ACFB13 table initialization */
#if CRC_32P4_MODE == CRC_TABLE_MODE

#define CRC_START_SEC_CONST_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per
 * Autosar guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly
 * included without safegaurd. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This data structure is quite
 * big is size, therefore link time relocation of table is
 * provided using Autosar Memmap definition guidelines         */
static const uint32 Crc_Table32P4[CRC_TABLE_LENGTH] =
{
  0x00000000UL, 0xF4ACFB13UL, 0x1DF50D35UL, 0xE959F626UL,
  0x3BEA1A6AUL, 0xCF46E179UL, 0x261F175FUL, 0xD2B3EC4CUL,
  0x77D434D4UL, 0x8378CFC7UL, 0x6A2139E1UL, 0x9E8DC2F2UL,
  0x4C3E2EBEUL, 0xB892D5ADUL, 0x51CB238BUL, 0xA567D898UL,
  0xEFA869A8UL, 0x1B0492BBUL, 0xF25D649DUL, 0x06F19F8EUL,
  0xD44273C2UL, 0x20EE88D1UL, 0xC9B77EF7UL, 0x3D1B85E4UL,
  0x987C5D7CUL, 0x6CD0A66FUL, 0x85895049UL, 0x7125AB5AUL,
  0xA3964716UL, 0x573ABC05UL, 0xBE634A23UL, 0x4ACFB130UL,
  0x2BFC2843UL, 0xDF50D350UL, 0x36092576UL, 0xC2A5DE65UL,
  0x10163229UL, 0xE4BAC93AUL, 0x0DE33F1CUL, 0xF94FC40FUL,
  0x5C281C97UL, 0xA884E784UL, 0x41DD11A2UL, 0xB571EAB1UL,
  0x67C206FDUL, 0x936EFDEEUL, 0x7A370BC8UL, 0x8E9BF0DBUL,
  0xC45441EBUL, 0x30F8BAF8UL, 0xD9A14CDEUL, 0x2D0DB7CDUL,
  0xFFBE5B81UL, 0x0B12A092UL, 0xE24B56B4UL, 0x16E7ADA7UL,
  0xB380753FUL, 0x472C8E2CUL, 0xAE75780AUL, 0x5AD98319UL,
  0x886A6F55UL, 0x7CC69446UL, 0x959F6260UL, 0x61339973UL,
  0x57F85086UL, 0xA354AB95UL, 0x4A0D5DB3UL, 0xBEA1A6A0UL,
  0x6C124AECUL, 0x98BEB1FFUL, 0x71E747D9UL, 0x854BBCCAUL,
  0x202C6452UL, 0xD4809F41UL, 0x3DD96967UL, 0xC9759274UL,
  0x1BC67E38UL, 0xEF6A852BUL, 0x0633730DUL, 0xF29F881EUL,
  0xB850392EUL, 0x4CFCC23DUL, 0xA5A5341BUL, 0x5109CF08UL,
  0x83BA2344UL, 0x7716D857UL, 0x9E4F2E71UL, 0x6AE3D562UL,
  0xCF840DFAUL, 0x3B28F6E9UL, 0xD27100CFUL, 0x26DDFBDCUL,
  0xF46E1790UL, 0x00C2EC83UL, 0xE99B1AA5UL, 0x1D37E1B6UL,
  0x7C0478C5UL, 0x88A883D6UL, 0x61F175F0UL, 0x955D8EE3UL,
  0x47EE62AFUL, 0xB34299BCUL, 0x5A1B6F9AUL, 0xAEB79489UL,
  0x0BD04C11UL, 0xFF7CB702UL, 0x16254124UL, 0xE289BA37UL,
  0x303A567BUL, 0xC496AD68UL, 0x2DCF5B4EUL, 0xD963A05DUL,
  0x93AC116DUL, 0x6700EA7EUL, 0x8E591C58UL, 0x7AF5E74BUL,
  0xA8460B07UL, 0x5CEAF014UL, 0xB5B30632UL, 0x411FFD21UL,
  0xE47825B9UL, 0x10D4DEAAUL, 0xF98D288CUL, 0x0D21D39FUL,
  0xDF923FD3UL, 0x2B3EC4C0UL, 0xC26732E6UL, 0x36CBC9F5UL,
  0xAFF0A10CUL, 0x5B5C5A1FUL, 0xB205AC39UL, 0x46A9572AUL,
  0x941ABB66UL, 0x60B64075UL, 0x89EFB653UL, 0x7D434D40UL,
  0xD82495D8UL, 0x2C886ECBUL, 0xC5D198EDUL, 0x317D63FEUL,
  0xE3CE8FB2UL, 0x176274A1UL, 0xFE3B8287UL, 0x0A977994UL,
  0x4058C8A4UL, 0xB4F433B7UL, 0x5DADC591UL, 0xA9013E82UL,
  0x7BB2D2CEUL, 0x8F1E29DDUL, 0x6647DFFBUL, 0x92EB24E8UL,
  0x378CFC70UL, 0xC3200763UL, 0x2A79F145UL, 0xDED50A56UL,
  0x0C66E61AUL, 0xF8CA1D09UL, 0x1193EB2FUL, 0xE53F103CUL,
  0x840C894FUL, 0x70A0725CUL, 0x99F9847AUL, 0x6D557F69UL,
  0xBFE69325UL, 0x4B4A6836UL, 0xA2139E10UL, 0x56BF6503UL,
  0xF3D8BD9BUL, 0x07744688UL, 0xEE2DB0AEUL, 0x1A814BBDUL,
  0xC832A7F1UL, 0x3C9E5CE2UL, 0xD5C7AAC4UL, 0x216B51D7UL,
  0x6BA4E0E7UL, 0x9F081BF4UL, 0x7651EDD2UL, 0x82FD16C1UL,
  0x504EFA8DUL, 0xA4E2019EUL, 0x4DBBF7B8UL, 0xB9170CABUL,
  0x1C70D433UL, 0xE8DC2F20UL, 0x0185D906UL, 0xF5292215UL,
  0x279ACE59UL, 0xD336354AUL, 0x3A6FC36CUL, 0xCEC3387FUL,
  0xF808F18AUL, 0x0CA40A99UL, 0xE5FDFCBFUL, 0x115107ACUL,
  0xC3E2EBE0UL, 0x374E10F3UL, 0xDE17E6D5UL, 0x2ABB1DC6UL,
  0x8FDCC55EUL, 0x7B703E4DUL, 0x9229C86BUL, 0x66853378UL,
  0xB436DF34UL, 0x409A2427UL, 0xA9C3D201UL, 0x5D6F2912UL,
  0x17A09822UL, 0xE30C6331UL, 0x0A559517UL, 0xFEF96E04UL,
  0x2C4A8248UL, 0xD8E6795BUL, 0x31BF8F7DUL, 0xC513746EUL,
  0x6074ACF6UL, 0x94D857E5UL, 0x7D81A1C3UL, 0x892D5AD0UL,
  0x5B9EB69CUL, 0xAF324D8FUL, 0x466BBBA9UL, 0xB2C740BAUL,
  0xD3F4D9C9UL, 0x275822DAUL, 0xCE01D4FCUL, 0x3AAD2FEFUL,
  0xE81EC3A3UL, 0x1CB238B0UL, 0xF5EBCE96UL, 0x01473585UL,
  0xA420ED1DUL, 0x508C160EUL, 0xB9D5E028UL, 0x4D791B3BUL,
  0x9FCAF777UL, 0x6B660C64UL, 0x823FFA42UL, 0x76930151UL,
  0x3C5CB061UL, 0xC8F04B72UL, 0x21A9BD54UL, 0xD5054647UL,
  0x07B6AA0BUL, 0xF31A5118UL, 0x1A43A73EUL, 0xEEEF5C2DUL,
  0x4B8884B5UL, 0xBF247FA6UL, 0x567D8980UL, 0xA2D17293UL,
  0x70629EDFUL, 0x84CE65CCUL, 0x6D9793EAUL, 0x993B68F9UL
};

#define CRC_STOP_SEC_CONST_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per
 * Autosar guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly
 * included without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
#endif
/* #if CRC_32P4_MODE == CRC_TABLE_MODE*/



/* CRC 16bit polynomial=0x1021 table initialization */
#if CRC_16_MODE == CRC_TABLE_MODE
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
#define CRC_START_SEC_CONST_ASIL_B_GLOBAL_16
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per
 * Autosar guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly
 * included without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This data structure is quite
 * big is size, therefore link time relocation of table is
 * provided using Autosar Memmap definition guidelines         */
static const uint16 Crc_Table16[CRC_TABLE_LENGTH] =
{
  0x0000U, 0x1021U, 0x2042U, 0x3063U,
  0x4084U, 0x50A5U, 0x60C6U, 0x70E7U,
  0x8108U, 0x9129U, 0xA14AU, 0xB16BU,
  0xC18CU, 0xD1ADU, 0xE1CEU, 0xF1EFU,
  0x1231U, 0x0210U, 0x3273U, 0x2252U,
  0x52B5U, 0x4294U, 0x72F7U, 0x62D6U,
  0x9339U, 0x8318U, 0xB37BU, 0xA35AU,
  0xD3BDU, 0xC39CU, 0xF3FFU, 0xE3DEU,
  0x2462U, 0x3443U, 0x0420U, 0x1401U,
  0x64E6U, 0x74C7U, 0x44A4U, 0x5485U,
  0xA56AU, 0xB54BU, 0x8528U, 0x9509U,
  0xE5EEU, 0xF5CFU, 0xC5ACU, 0xD58DU,
  0x3653U, 0x2672U, 0x1611U, 0x0630U,
  0x76D7U, 0x66F6U, 0x5695U, 0x46B4U,
  0xB75BU, 0xA77AU, 0x9719U, 0x8738U,
  0xF7DFU, 0xE7FEU, 0xD79DU, 0xC7BCU,
  0x48C4U, 0x58E5U, 0x6886U, 0x78A7U,
  0x0840U, 0x1861U, 0x2802U, 0x3823U,
  0xC9CCU, 0xD9EDU, 0xE98EU, 0xF9AFU,
  0x8948U, 0x9969U, 0xA90AU, 0xB92BU,
  0x5AF5U, 0x4AD4U, 0x7AB7U, 0x6A96U,
  0x1A71U, 0x0A50U, 0x3A33U, 0x2A12U,
  0xDBFDU, 0xCBDCU, 0xFBBFU, 0xEB9EU,
  0x9B79U, 0x8B58U, 0xBB3BU, 0xAB1AU,
  0x6CA6U, 0x7C87U, 0x4CE4U, 0x5CC5U,
  0x2C22U, 0x3C03U, 0x0C60U, 0x1C41U,
  0xEDAEU, 0xFD8FU, 0xCDECU, 0xDDCDU,
  0xAD2AU, 0xBD0BU, 0x8D68U, 0x9D49U,
  0x7E97U, 0x6EB6U, 0x5ED5U, 0x4EF4U,
  0x3E13U, 0x2E32U, 0x1E51U, 0x0E70U,
  0xFF9FU, 0xEFBEU, 0xDFDDU, 0xCFFCU,
  0xBF1BU, 0xAF3AU, 0x9F59U, 0x8F78U,
  0x9188U, 0x81A9U, 0xB1CAU, 0xA1EBU,
  0xD10CU, 0xC12DU, 0xF14EU, 0xE16FU,
  0x1080U, 0x00A1U, 0x30C2U, 0x20E3U,
  0x5004U, 0x4025U, 0x7046U, 0x6067U,
  0x83B9U, 0x9398U, 0xA3FBU, 0xB3DAU,
  0xC33DU, 0xD31CU, 0xE37FU, 0xF35EU,
  0x02B1U, 0x1290U, 0x22F3U, 0x32D2U,
  0x4235U, 0x5214U, 0x6277U, 0x7256U,
  0xB5EAU, 0xA5CBU, 0x95A8U, 0x8589U,
  0xF56EU, 0xE54FU, 0xD52CU, 0xC50DU,
  0x34E2U, 0x24C3U, 0x14A0U, 0x0481U,
  0x7466U, 0x6447U, 0x5424U, 0x4405U,
  0xA7DBU, 0xB7FAU, 0x8799U, 0x97B8U,
  0xE75FU, 0xF77EU, 0xC71DU, 0xD73CU,
  0x26D3U, 0x36F2U, 0x0691U, 0x16B0U,
  0x6657U, 0x7676U, 0x4615U, 0x5634U,
  0xD94CU, 0xC96DU, 0xF90EU, 0xE92FU,
  0x99C8U, 0x89E9U, 0xB98AU, 0xA9ABU,
  0x5844U, 0x4865U, 0x7806U, 0x6827U,
  0x18C0U, 0x08E1U, 0x3882U, 0x28A3U,
  0xCB7DU, 0xDB5CU, 0xEB3FU, 0xFB1EU,
  0x8BF9U, 0x9BD8U, 0xABBBU, 0xBB9AU,
  0x4A75U, 0x5A54U, 0x6A37U, 0x7A16U,
  0x0AF1U, 0x1AD0U, 0x2AB3U, 0x3A92U,
  0xFD2EU, 0xED0FU, 0xDD6CU, 0xCD4DU,
  0xBDAAU, 0xAD8BU, 0x9DE8U, 0x8DC9U,
  0x7C26U, 0x6C07U, 0x5C64U, 0x4C45U,
  0x3CA2U, 0x2C83U, 0x1CE0U, 0x0CC1U,
  0xEF1FU, 0xFF3EU, 0xCF5DU, 0xDF7CU,
  0xAF9BU, 0xBFBAU, 0x8FD9U, 0x9FF8U,
  0x6E17U, 0x7E36U, 0x4E55U, 0x5E74U,
  0x2E93U, 0x3EB2U, 0x0ED1U, 0x1EF0U
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
#define CRC_STOP_SEC_CONST_ASIL_B_GLOBAL_16
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per
 * Autosar guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly
 * included without safegaurd. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
#endif
/* #if CRC_16_MODE == CRC_TABLE_MODE*/




/* CRC 8bit polynomial=0x1D table initialization */
#if CRC_8_MODE == CRC_TABLE_MODE
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
#define CRC_START_SEC_CONST_ASIL_B_GLOBAL_8
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per
 * Autosar guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly
 * included without safegaurd. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This data structure is quite
 * big is size, therefore link time relocation of table is
 * provided using Autosar Memmap definition guidelines         */
static const uint8 Crc_Table8[CRC_TABLE_LENGTH] =
{
  0x00U, 0x1dU, 0x3AU, 0x27U, 0x74U, 0x69U, 0x4eU, 0x53U,
  0xe8U, 0xf5U, 0xd2U, 0xcfU, 0x9cU, 0x81U, 0xa6U, 0xbbU,
  0xCDU, 0xD0U, 0xF7U, 0xEAU, 0xB9U, 0xA4U, 0x83U, 0x9eU,
  0x25U, 0x38U, 0x1FU, 0x02U, 0x51U, 0x4CU, 0x6BU, 0x76U,
  0x87U, 0x9AU, 0xBDU, 0xA0U, 0xF3U, 0xEEU, 0xC9U, 0xD4U,
  0x6FU, 0x72U, 0x55U, 0x48U, 0x1BU, 0x06U, 0x21U, 0x3CU,
  0x4AU, 0x57U, 0x70U, 0x6DU, 0x3EU, 0x23U, 0x04U, 0x19U,
  0xA2U, 0xBFU, 0x98U, 0x85U, 0xD6U, 0xCBU, 0xECU, 0xF1U,
  0x13U, 0x0EU, 0x29U, 0x34U, 0x67U, 0x7AU, 0x5DU, 0x40U,
  0xFBU, 0xE6U, 0xC1U, 0xDCU, 0x8FU, 0x92U, 0xB5U, 0xA8U,
  0xDEU, 0xC3U, 0xE4U, 0xF9U, 0xAAU, 0xB7U, 0x90U, 0x8DU,
  0x36U, 0x2BU, 0x0CU, 0x11U, 0x42U, 0x5FU, 0x78U, 0x65U,
  0x94U, 0x89U, 0xAEU, 0xB3U, 0xE0U, 0xFDU, 0xDAU, 0xC7U,
  0x7CU, 0x61U, 0x46U, 0x5BU, 0x08U, 0x15U, 0x32U, 0x2FU,
  0x59U, 0x44U, 0x63U, 0x7EU, 0x2DU, 0x30U, 0x17U, 0x0AU,
  0xB1U, 0xACU, 0x8BU, 0x96U, 0xC5U, 0xD8U, 0xFFU, 0xE2U,
  0x26U, 0x3BU, 0x1CU, 0x01U, 0x52U, 0x4FU, 0x68U, 0x75U,
  0xCEU, 0xD3U, 0xF4U, 0xE9U, 0xBAU, 0xA7U, 0x80U, 0x9DU,
  0xEBU, 0xF6U, 0xD1U, 0xCCU, 0x9FU, 0x82U, 0xA5U, 0xB8U,
  0x03U, 0x1EU, 0x39U, 0x24U, 0x77U, 0x6AU, 0x4DU, 0x50U,
  0xA1U, 0xBCU, 0x9BU, 0x86U, 0xD5U, 0xC8U, 0xEFU, 0xF2U,
  0x49U, 0x54U, 0x73U, 0x6EU, 0x3DU, 0x20U, 0x07U, 0x1AU,
  0x6CU, 0x71U, 0x56U, 0x4BU, 0x18U, 0x05U, 0x22U, 0x3FU,
  0x84U, 0x99U, 0xBEU, 0xA3U, 0xF0U, 0xEDU, 0xCAU, 0xD7U,
  0x35U, 0x28U, 0x0FU, 0x12U, 0x41U, 0x5CU, 0x7BU, 0x66U,
  0xDDU, 0xC0U, 0xE7U, 0xFAU, 0xA9U, 0xB4U, 0x93U, 0x8EU,
  0xF8U, 0xE5U, 0xC2U, 0xDFU, 0x8CU, 0x91U, 0xB6U, 0xABU,
  0x10U, 0x0DU, 0x2AU, 0x37U, 0x64U, 0x79U, 0x5EU, 0x43U,
  0xB2U, 0xAFU, 0x88U, 0x95U, 0xC6U, 0xDBU, 0xFCU, 0xE1U,
  0x5AU, 0x47U, 0x60U, 0x7DU, 0x2EU, 0x33U, 0x14U, 0x09U,
  0x7FU, 0x62U, 0x45U, 0x58U, 0x0BU, 0x16U, 0x31U, 0x2CU,
  0x97U, 0x8AU, 0xADU, 0xB0U, 0xE3U, 0xFEU, 0xD9U, 0xC4U
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
#define CRC_STOP_SEC_CONST_ASIL_B_GLOBAL_8
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per
 * Autosar guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly
 * included without safegaurd. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"

#endif
/* #if CRC_8_MODE == CRC_TABLE_MODE*/


/* CRC 8bit polynomial=0x1F table initialization */
#if CRC_8H2F_MODE == CRC_TABLE_MODE
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
#define CRC_START_SEC_CONST_ASIL_B_GLOBAL_8
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per
 * Autosar guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly
 * included without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This data structure is quite
 * big is size, therefore link time relocation of table is
 * provided using Autosar Memmap definition guidelines         */
static const uint8 Crc_Table8H2F[CRC_TABLE_LENGTH] =
{
  0x00U, 0x2fU, 0x5eU, 0x71U, 0xbcU, 0x93U, 0xe2U, 0xcdU,
  0x57U, 0x78U, 0x09U, 0x26U, 0xEBU, 0xC4U, 0xB5U, 0x9AU,
  0xAEU, 0x81U, 0xF0U, 0xDFU, 0x12U, 0x3DU, 0x4CU, 0x63U,
  0xF9U, 0xD6U, 0xA7U, 0x88U, 0x45U, 0x6AU, 0x1BU, 0x34U,
  0x73U, 0x5CU, 0x2DU, 0x02U, 0xCFU, 0xE0U, 0x91U, 0xBEU,
  0x24U, 0x0BU, 0x7AU, 0x55U, 0x98U, 0xB7U, 0xC6U, 0xE9U,
  0xDDU, 0xF2U, 0x83U, 0xACU, 0x61U, 0x4EU, 0x3FU, 0x10U,
  0x8AU, 0xA5U, 0xD4U, 0xFBU, 0x36U, 0x19U, 0x68U, 0x47U,
  0xE6U, 0xC9U, 0xB8U, 0x97U, 0x5AU, 0x75U, 0x04U, 0x2BU,
  0xB1U, 0x9EU, 0xEFU, 0xC0U, 0x0DU, 0x22U, 0x53U, 0x7CU,
  0x48U, 0x67U, 0x16U, 0x39U, 0xF4U, 0xDBU, 0xAAU, 0x85U,
  0x1FU, 0x30U, 0x41U, 0x6EU, 0xA3U, 0x8CU, 0xFDU, 0xD2U,
  0x95U, 0xBAU, 0xCBU, 0xE4U, 0x29U, 0x06U, 0x77U, 0x58U,
  0xC2U, 0xEDU, 0x9CU, 0xB3U, 0x7EU, 0x51U, 0x20U, 0x0FU,
  0x3BU, 0x14U, 0x65U, 0x4AU, 0x87U, 0xA8U, 0xD9U, 0xF6U,
  0x6CU, 0x43U, 0x32U, 0x1DU, 0xD0U, 0xFFU, 0x8EU, 0xA1U,
  0xE3U, 0xCCU, 0xBDU, 0x92U, 0x5FU, 0x70U, 0x01U, 0x2EU,
  0xB4U, 0x9BU, 0xEAU, 0xC5U, 0x08U, 0x27U, 0x56U, 0x79U,
  0x4DU, 0x62U, 0x13U, 0x3CU, 0xF1U, 0xDEU, 0xAFU, 0x80U,
  0x1AU, 0x35U, 0x44U, 0x6BU, 0xA6U, 0x89U, 0xF8U, 0xD7U,
  0x90U, 0xBFU, 0xCEU, 0xE1U, 0x2CU, 0x03U, 0x72U, 0x5DU,
  0xC7U, 0xE8U, 0x99U, 0xB6U, 0x7BU, 0x54U, 0x25U, 0x0AU,
  0x3EU, 0x11U, 0x60U, 0x4FU, 0x82U, 0xADU, 0xDCU, 0xF3U,
  0x69U, 0x46U, 0x37U, 0x18U, 0xD5U, 0xFAU, 0x8BU, 0xA4U,
  0x05U, 0x2AU, 0x5BU, 0x74U, 0xB9U, 0x96U, 0xE7U, 0xC8U,
  0x52U, 0x7DU, 0x0CU, 0x23U, 0xEEU, 0xC1U, 0xB0U, 0x9FU,
  0xABU, 0x84U, 0xF5U, 0xDAU, 0x17U, 0x38U, 0x49U, 0x66U,
  0xFCU, 0xD3U, 0xA2U, 0x8DU, 0x40U, 0x6FU, 0x1EU, 0x31U,
  0x76U, 0x59U, 0x28U, 0x07U, 0xCAU, 0xE5U, 0x94U, 0xBBU,
  0x21U, 0x0EU, 0x7FU, 0x50U, 0x9DU, 0xB2U, 0xC3U, 0xECU,
  0xD8U, 0xF7U, 0x86U, 0xA9U, 0x64U, 0x4BU, 0x3AU, 0x15U,
  0x8FU, 0xA0U, 0xD1U, 0xFEU, 0x33U, 0x1CU, 0x6DU, 0x42U
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
#define CRC_STOP_SEC_CONST_ASIL_B_GLOBAL_8
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per
 * Autosar guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly
 * included without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
#endif
/* #if CRC_8H2F_MODE == CRC_TABLE_MODE*/



/*******************************************************************************
**        Global Variable Definitions                                         **
*******************************************************************************/
#if ((CRC_8_MODE == CRC_HARDWARE_MODE) || (CRC_16_MODE == CRC_HARDWARE_MODE) ||\
(CRC_32_MODE == CRC_HARDWARE_MODE) || (CRC_32P4_MODE == CRC_HARDWARE_MODE))

#define CRC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_8
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per
* Autosar guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly
* included without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"

static volatile uint8 Crc_ChannelFlag = CRC_ZERO_U;
#define CRC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_8
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per
 * Autosar guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly
 * included without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
#define CRC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per
* Autosar guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly
* included without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"

static volatile uint32 Crc_SpinLockAddress = CRC_ZERO_U;

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond
* 32 chars because of AS naming convention*/
#define CRC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per
 * Autosar guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly
 * included without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
#endif

/*******************************************************************************
**        Private Constant Definitions                                        **
*******************************************************************************/



/*******************************************************************************
**        Private Variable Definitions                                        **
*******************************************************************************/



/*******************************************************************************
**        Global Function Definitions                                         **
*******************************************************************************/
/* [cover parentID={55C2CC41-ABDB-45df-A1FF-6F9C5FB3435C}]
[/cover] */

/* Memory Map of the CRC Code */
#define CRC_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"

#if (CRC_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={4F55BFEA-0359-49c1-A254-83F3978261BF}]   **
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
** Parameters(out): Versioninfo (Pointer to where to store the version        **
**                               information of this module)                  **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
void Crc_GetVersionInfo(Std_VersionInfoType* const Versioninfo)
{

  /* [cover parentID={CB52FE8D-792A-4d97-B0C0-1F8291105229}]
  If safety check is enabled
  [/cover] */
  /* Check if the passed parameter is a NULL_PTR */
  #if (CRC_SAFETYENABLE == STD_ON)
  /* [cover parentID={614B1344-B4B9-4110-BF6E-BB9B33D2669C}]
  Is the passed pointer valid?
  [/cover] */
  if ((Versioninfo) == NULL_PTR)
  {
    /* [cover parentID={5615A26C-8D6F-4603-937A-324DB2C79246}]
    Report Mcal Safety Error
    [/cover] */
    /* Report Safety error with CRC_E_PARAM_POINTER */
    Mcal_ReportSafetyError(CRC_MODULE_ID, CRC_INSTANCE_ID,
                           CRC_SID_GETVERSIONINFO, CRC_E_PARAM_POINTER);
  }
  else
  #endif
  {

    /* [cover parentID={C957528E-61F3-4926-8C57-C536A7FED827}]
    Update vendor ID, module ID, SW major, SW minor and SW patch version values
    to the passed pointer parameter.
    [/cover] */
    /* Get CRC Vendor ID */
    ((Std_VersionInfoType*)(Versioninfo))->vendorID = CRC_VENDOR_ID;

    /* Get CRC Module ID */
    ((Std_VersionInfoType*)(Versioninfo))->moduleID = CRC_MODULE_ID;

    /* Get CRC module Software major version */
    ((Std_VersionInfoType*)(Versioninfo))->sw_major_version =
      (uint8)CRC_SW_MAJOR_VERSION;

    /* Get CRC module Software minor version */
    ((Std_VersionInfoType*)(Versioninfo))->sw_minor_version =
      (uint8)CRC_SW_MINOR_VERSION;

    /* Get CRC module Software patch version */
    ((Std_VersionInfoType*)(Versioninfo))->sw_patch_version =
      (uint8)CRC_SW_PATCH_VERSION;
  }
} /* End of Crc_GetVersionInfo() */

/******************************************************************************/
#endif
/* End of #if (CRC_VERSION_INFO_API == STD_ON) */

#if (CRC_8_MODE != STD_OFF)
/*******************************************************************************
** Traceability     : [cover parentID={F320531F-FD72-417d-AE1B-620B857DFD21}] **
** Syntax           : uint8 Crc_CalculateCRC8                                 **
**                      (                                                     **
**                          const uint8* const Crc_DataPtr,                   **
**                          const uint32 Crc_Length,                          **
**                          const uint8 Crc_StartValue8,                      **
**                          const boolean Crc_IsFirstCall                     **
**                      )                                                     **
**                                                                            **
** Description      : This function takes the value of input data pointer,    **
**                    start value and polynomial, calculates the crc taking   **
**                    the precomputed  and  xor value  and returns the        **
**                    CRC xored with XOR value                                **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x01                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : Crc_DataPtr  - Pointer to the start of the datablock    **
**                    Crc_Length - Length of the input data to be fetched     **
**                    Crc_StartValue8 -Start value for CRC Calculation        **
**                    Crc_IsFirstCall -Boolean to decIDe the start value      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : uint8                                                   **
**                                                                            **
*******************************************************************************/
uint8 Crc_CalculateCRC8
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint8 Crc_StartValue8,
  const boolean Crc_IsFirstCall
)
{
  uint8 Result;
  /* [cover parentID={A1459FF8-9C4B-4826-9BEA-B12CF8F93E9D}]
  If safety check is enabled
  [/cover] */
  #if (CRC_SAFETYENABLE == STD_ON)

  /* [cover parentID={9CABEDBB-7BF4-4cd4-A074-E24E3ED4BF35}]
  Set CRC result to configured error value
  [/cover] */
  Result = (uint8)CRC_8_CONFIGERROR_VAL;

  /* [cover parentID={746F67D2-89E6-4163-82BD-9633120A2EB0}]
  If the data pointer is not NULL and length is non-zero
  [/cover] */
  if(Crc_DataPtr == NULL_PTR)
  {
    /* [cover parentID={69917B33-5EC0-491c-9BC6-7388B652D37A}]
    Report Mcal Safety Error
    [/cover] */
    Mcal_ReportSafetyError(CRC_MODULE_ID, CRC_INSTANCE_ID,
                           CRC_SID_CALCULATE_CRC8, CRC_E_PARAM_POINTER);
  }
  else if(Crc_Length == 0u)
  {
    /* [cover parentID={69917B33-5EC0-491c-9BC6-7388B652D37A}]
    Report Mcal Safety Error
    [/cover] */
    Mcal_ReportSafetyError(CRC_MODULE_ID, CRC_INSTANCE_ID,
                           CRC_SID_CALCULATE_CRC8, CRC_E_PARAM_LENGTH);
  }
  else
  #endif
  {

    /* Depending on the configuration chosen, the CRC would be calculated
     * using the runtime/table/hardware method. */

    /* [cover parentID={3D2C4ED5-D676-4947-B435-137FEA7D1891}]
    If configured mode is RunTime method
    [/cover] */
    #if  CRC_8_MODE == CRC_RUNTIME_MODE
    /* [cover parentID={A918805B-71F9-4464-8F54-C0F85E48CC63}]
    Calculate CRC using Runtime mode
    [/cover] */
    /* Lets calculate the CRC using the runtime method */
    Result = Crc_lCalculateCRC8Runtime( Crc_DataPtr, Crc_Length,
                                        Crc_StartValue8, Crc_IsFirstCall);

    /* [cover parentID={A98BD269-4732-4ed8-92B6-6DCF6F640DFB}]
    If configured mode is Table method
    [/cover] */
    #elif CRC_8_MODE == CRC_TABLE_MODE
    /* [cover parentID={70D63BB1-DFEF-4c0b-A079-6DD5C2B876CB}]
    Calculate CRC using Table mode
    [/cover] */
    /* Lets calculate the CRC using the table method */
    Result = Crc_lCalculateCRC8Table( Crc_DataPtr, Crc_Length,
                                      Crc_StartValue8, Crc_IsFirstCall);

    /* [cover parentID={6B289E23-DE6F-4476-80C1-7FF7BD54E862}]
    If configured mode is Hardware method
    [/cover] */
    #elif CRC_8_MODE == CRC_HARDWARE_MODE
    /* [cover parentID={AE73D6E0-741A-4194-8371-D80C030EEDAE}]
    Calculate CRC using Hardware method
    [/cover] */
    /* Lets calculate the CRC using the hardware method */
    Result = Crc_lCalculateCRC8Hardware( Crc_DataPtr, Crc_Length,
                                         Crc_StartValue8, Crc_IsFirstCall);

    #endif

  }

  return Result;
}
#endif
/* #ifdef CRC_8_MODE */

#if CRC_8H2F_MODE != STD_OFF

/*******************************************************************************
** Traceability     : [cover parentID={D8F89B96-6BB3-4a12-BB8E-A51666324262}] **
** Syntax           : uint8 Crc_CalculateCRC8H2F                              **
**                      (                                                     **
**                          const uint8* const Crc_DataPtr,                   **
**                          const uint32 Crc_Length,                          **
**                          const uint8 Crc_StartValue8H2F,                   **
**                          const boolean Crc_IsFirstCall                     **
**                      )                                                     **
** Description      : This function takes the value of input data pointer,    **
**                    start value and polynomial, calculates the crc          **
**                    taking the precomputed and  xor value  and returns      **
**                    the CRC xored with XOR value                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x05                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : Crc_DataPtr  - Pointer to the start of the datablock    **
**                    Crc_Length - Length of the input data to be fetched     **
**                    Crc_StartValue8H2F -Start value for CRC Calculation     **
**                    Crc_IsFirstCall -Boolean to decide the start value      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : uint8                                                   **
**                                                                            **
*******************************************************************************/
uint8 Crc_CalculateCRC8H2F
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint8 Crc_StartValue8H2F,
  const boolean Crc_IsFirstCall
)
{
  uint8 Result;
  /* [cover parentID={1680ED3C-2C5E-4694-B97A-BFC6746848A3}]
  If safety check is enabled
  [/cover] */
  #if (CRC_SAFETYENABLE == STD_ON)
  /* [cover parentID={1DB61D07-F46F-4fd3-B91A-D82AA471F1C6}]
  Set CRC result to configured error value
  [/cover] */
  Result = (uint8)CRC_8H2F_CONFIGERROR_VAL;

  /* [cover parentID={6ADD12AA-A9B0-466c-858F-607D556F36A8}]
  If the data pointer is not NULL and length is non-zero
  [/cover] */
  if(Crc_DataPtr == NULL_PTR)
  {
    /* [cover parentID={5518C6A9-2E51-41c9-ADE5-4FFAFAF5E13B}]
    Report Mcal Safety Error
    [/cover] */
    Mcal_ReportSafetyError(CRC_MODULE_ID, CRC_INSTANCE_ID,
                           CRC_SID_CALCULATE_CRC8H2F, CRC_E_PARAM_POINTER);
  }
  else if(Crc_Length == 0u)
  {
    /* [cover parentID={5518C6A9-2E51-41c9-ADE5-4FFAFAF5E13B}]
    Report Mcal Safety Error
    [/cover] */
    Mcal_ReportSafetyError(CRC_MODULE_ID, CRC_INSTANCE_ID,
                           CRC_SID_CALCULATE_CRC8H2F, CRC_E_PARAM_LENGTH);
  }
  else
  #endif
  {


    /* Depending on the configuration chosen, the CRC would be calculated
     * using the runtime/table/hardware method. */
    /* [cover parentID={70D8E6AB-C62C-4096-986D-84D8EB313B33}]
    If configured mode is RunTime method
    [/cover] */
    #if  CRC_8H2F_MODE == CRC_RUNTIME_MODE
    /* [cover parentID={1E5A8A05-9231-45b6-A19C-68B3A0932D88}]
    Calculate CRC using Runtime mode
    [/cover] */
    /* Lets calculate the CRC using the runtime method */
    Result = Crc_lCalculateCRC8H2FRuntime( Crc_DataPtr, Crc_Length,
                                           Crc_StartValue8H2F, Crc_IsFirstCall);

    /* [cover parentID={6CD1B48B-215A-4129-B624-49C7F89C1C87}]
    If configured mode is Table method
    [/cover] */
    #elif CRC_8H2F_MODE == CRC_TABLE_MODE
    /* [cover parentID={BC5A60D6-51C6-4590-94C3-B43821D09345}]
    Calculate CRC using Table mode
    [/cover] */
    /* Lets calculate the CRC using the table method */
    Result = Crc_lCalculateCRC8H2FTable( Crc_DataPtr, Crc_Length,
                                         Crc_StartValue8H2F, Crc_IsFirstCall);

    #endif
  }

  return Result;
}
#endif
/* #ifdef CRC_8H2F_MODE */


#if CRC_16_MODE != STD_OFF

/*******************************************************************************
** Traceability     : [cover parentID={3F6E6BD8-18DD-466d-8CEC-0178A138E548}] **
** Syntax     : uint16 Crc_CalculateCRC16                                     **
**      (                                                                     **
**       const uint8* const Crc_DataPtr,                                      **
**       const uint32 Crc_Length,                                             **
**       const const uint16 Crc_StartValue16,                                 **
**       const boolean Crc_IsFirstCall                                        **
**      )                                                                     **
**                                                                            **
** Description    : This function:                                            **
** - This function takes the value of input data pointer, start value and     **
**   polynomial, calculates the crc taking the precomputed                    **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : 0x05                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy       : Re-entrant                                              **
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
*******************************************************************************/
uint16 Crc_CalculateCRC16
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint16 Crc_StartValue16,
  const boolean Crc_IsFirstCall
)
{
  uint16 Result;

  /* [cover parentID={4ED98803-4132-427e-A4A0-0FA8A3604173}]
  If safety check is enabled
  [/cover] */
  #if (CRC_SAFETYENABLE == STD_ON)

  /* [cover parentID={D4922D8D-40CD-4757-A43F-348750B56B6A}]
  Set CRC result to configured error value
  [/cover] */
  Result = (uint16)CRC_16_CONFIGERROR_VAL;

  /* [cover parentID={4177D422-04EC-4854-BD19-6741EA43DEFC}]
  If the data pointer is not NULL and length is non-zero
  [/cover] */
  if(Crc_DataPtr == NULL_PTR)
  {
    /* [cover parentID={089D44CA-FDFE-400f-957B-4C40553C2EB9}]
    Report Mcal Safety Error
    [/cover] */
    Mcal_ReportSafetyError(CRC_MODULE_ID, CRC_INSTANCE_ID,
                           CRC_SID_CALCULATE_CRC16, CRC_E_PARAM_POINTER);
  }
  else if(Crc_Length == 0u)
  {
    /* [cover parentID={089D44CA-FDFE-400f-957B-4C40553C2EB9}]
    Report Mcal Safety Error
    [/cover] */
    Mcal_ReportSafetyError(CRC_MODULE_ID, CRC_INSTANCE_ID,
                           CRC_SID_CALCULATE_CRC16, CRC_E_PARAM_LENGTH);
  }
  else
  #endif
  {

    /* Depending on the configuration chosen, the CRC would be calculated
     * using the runtime/table/hardware method. */
    /* [cover parentID={377F471C-C3FD-48ed-AB7F-3C8E2B939DB6}]
    If configured mode is RunTime method
    [/cover] */
    #if  CRC_16_MODE == CRC_RUNTIME_MODE
    /* [cover parentID={A53A0EB8-4291-4bda-9B22-CA1035963CA2}]
    Calculate CRC using Runtime mode
    [/cover] */
    /* Lets calculate the CRC using the runtime method */
    Result = Crc_lCalculateCRC16Runtime( Crc_DataPtr, Crc_Length,
                                         Crc_StartValue16, Crc_IsFirstCall);

    /* [cover parentID={DAE659BD-538D-46d9-85A7-7885A0573F2E}]
    If configured mode is Table method
    [/cover] */
    #elif CRC_16_MODE == CRC_TABLE_MODE
    /* [cover parentID={80DEECBE-C00C-45d4-8458-B6EC9061DFA5}]
    Calculate CRC using Table mode
    [/cover] */
    /* Lets calculate the CRC using the table method */
    Result = Crc_lCalculateCRC16Table( Crc_DataPtr, Crc_Length,
                                       Crc_StartValue16, Crc_IsFirstCall);

    /* [cover parentID={EF4562BD-166F-469d-92B1-A9BE8744C23A}]
    If configured mode is Hardware method
    [/cover] */
    #elif CRC_16_MODE == CRC_HARDWARE_MODE
    /* [cover parentID={40469685-9293-49d3-8418-D43A8782CEEF}]
    Calculate CRC using Hardware method
    [/cover] */
    /* Lets calculate the CRC using the hardware method */
    Result = Crc_lCalculateCRC16Hardware( Crc_DataPtr, Crc_Length,
                                          Crc_StartValue16, Crc_IsFirstCall);

    #endif
  }
  return Result;
}
#endif
/* #ifdef CRC_16_MODE */

#if CRC_32_MODE != STD_OFF
/*******************************************************************************
** Traceability     : [cover parentID={468B97AE-C2C7-40f3-80D9-99053101EBBA}] **
** Syntax     : uint32 Crc_CalculateCRC32                                     **
**      (                                                                     **
**       const uint8* const Crc_DataPtr,                                      **
**       const uint32 Crc_Length,                                             **
**       const uint32 Crc_StartValue32,                                       **
**       const boolean Crc_IsFirstCall                                        **
**      )                                                                     **
**                                                                            **
** Description    : This function:                                            **
** - This function takes the value of input data pointer, start value and     **
**   polynomial, calculates the crc taking the precomputed                    **
**    and reversed xor value  and returns the CRC xored with XOR value        **
** [/cover]                                                                   **
**
** Service ID     : 0x01                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy       : Re-entrant                                              **
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
*******************************************************************************/
uint32 Crc_CalculateCRC32
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint32 Crc_StartValue32,
  const boolean Crc_IsFirstCall
)
{
  uint32 Result;

  /* [cover parentID={1FC5CE90-74F1-4a50-849B-BA1A30246F32}]
  If safety check is enabled
  [/cover] */
  #if (CRC_SAFETYENABLE == STD_ON)

  /* [cover parentID={84E27FEF-B84D-4614-AD39-4FF12A2CC560}]
  [/cover] */
  Result = (uint32)CRC_32_CONFIGERROR_VAL;

  /* [cover parentID={6451B3CF-CCD6-4d30-9F13-2C3588167775}]
  [/cover] */
  if(Crc_DataPtr == NULL_PTR)
  {
    /* [cover parentID={0CEE7589-2CAC-49c7-8B24-BC9D15EE7A0B}]
    Report Mcal Safety Error
    [/cover] */
    Mcal_ReportSafetyError(CRC_MODULE_ID, CRC_INSTANCE_ID,
                           CRC_SID_CALCULATE_CRC32, CRC_E_PARAM_POINTER);
  }
  else if(Crc_Length == 0u)
  {
    /* [cover parentID={0CEE7589-2CAC-49c7-8B24-BC9D15EE7A0B}]
    Report Mcal Safety Error
    [/cover] */
    Mcal_ReportSafetyError(CRC_MODULE_ID, CRC_INSTANCE_ID,
                           CRC_SID_CALCULATE_CRC32, CRC_E_PARAM_LENGTH);
  }
  else
  #endif
  {

    /* Depending on the configuration chosen, the CRC would be calculated
     * using the runtime/table/hardware method. */
    /* [cover parentID={A57BFBC9-85F8-4859-A156-B139C0AD630F}]
    If configured mode is RunTime method
    [/cover] */
    #if  CRC_32_MODE == CRC_RUNTIME_MODE
    /* [cover parentID={D06B4159-C3FC-4b88-AF64-2AB87837B45C}]
    Calculate CRC using Runtime mode
    [/cover] */
    /* Lets calculate the CRC using the runtime method */
    Result = Crc_lCalculateCRC32Runtime( Crc_DataPtr, Crc_Length,
                                         Crc_StartValue32, Crc_IsFirstCall);

    /* [cover parentID={04E4E6F3-9E68-45f4-8B3F-0838EC3607F6}]
    If configured mode is Table method
    [/cover] */
    #elif CRC_32_MODE == CRC_TABLE_MODE
    /* [cover parentID={D4675BDB-F036-4bd9-BDBA-F6EAFA81EA75}]
    Calculate CRC using Table mode
    [/cover] */
    /* Lets calculate the CRC using the table method */
    Result = Crc_lCalculateCRC32Table( Crc_DataPtr, Crc_Length,
                                       Crc_StartValue32, Crc_IsFirstCall);

    /* [cover parentID={F51FDDA7-722E-4a32-9AD2-25FBF69A9ED8}]
    If configured mode is Hardware method
    [/cover] */
    #elif CRC_32_MODE == CRC_HARDWARE_MODE
    /* [cover parentID={AC0949A0-6022-46e0-B6B6-5481EBB6D63B}]
    Calculate CRC using Hardware method
    [/cover] */
    /* Lets calculate the CRC using the hardware method */
    Result = Crc_lCalculateCRC32Hardware( Crc_DataPtr, Crc_Length,
                                          Crc_StartValue32, Crc_IsFirstCall);

    #endif
  }
  return Result;
}
#endif
/* #ifdef CRC_32_MODE */


#if CRC_32P4_MODE != STD_OFF
/*******************************************************************************
** Traceability     : [cover parentID={9863DB3E-9C70-4c80-8426-6DA9015F5426}] **
** Syntax     : uint32 Crc_CalculateCRC32P4                                   **
**      (                                                                     **
**       const uint8* const Crc_DataPtr,                                      **
**       const uint32 Crc_Length,                                             **
**       const uint32 Crc_StartValue32,                                       **
**       const boolean Crc_IsFirstCall                                        **
**      )                                                                     **
**                                                                            **
** Description    : This function:                                            **
** - This function takes the value of input data pointer, start value and     **
**   polynomial, calculates the crc taking the precomputed                    **
**    and reversed xor value  and returns the CRC xored with XOR value        **
** [/cover]                                                                   **
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
*******************************************************************************/
uint32 Crc_CalculateCRC32P4
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint32 Crc_StartValue32,
  const boolean Crc_IsFirstCall
)
{
  uint32 Result;

  /* [cover parentID={6DA28B32-2C6C-47a5-AFB0-B3BF841EE438}]
  If safety check is enabled
  [/cover] */
  #if (CRC_SAFETYENABLE == STD_ON)

  /* [cover parentID={67B05D14-F3FF-4af0-A69F-67915E4EB85E}]
  Set CRC result to configured error value
  [/cover] */
  Result = (uint32)CRC_32P4_CONFIGERROR_VAL;

  /* [cover parentID={9000079A-ECAA-4599-BC58-C8EC0C6A7C93}]
  If the data pointer is not NULL and length is non-zero
  [/cover] */
  if(Crc_DataPtr == NULL_PTR)
  {
    /* [cover parentID={455C5413-2156-4b25-BC5B-55DC081CAC3E}]
    Report Mcal Safety Error
    [/cover] */
    Mcal_ReportSafetyError(CRC_MODULE_ID, CRC_INSTANCE_ID,
                           CRC_SID_CALCULATE_CRC32P4, CRC_E_PARAM_POINTER);
  }
  else if(Crc_Length == 0u)
  {
    /* [cover parentID={455C5413-2156-4b25-BC5B-55DC081CAC3E}]
    Report Mcal Safety Error
    [/cover] */
    Mcal_ReportSafetyError(CRC_MODULE_ID, CRC_INSTANCE_ID,
                           CRC_SID_CALCULATE_CRC32P4, CRC_E_PARAM_LENGTH);
  }
  else
  #endif
  {

    /* Depending on the configuration chosen, the CRC would be calculated
     * using the runtime/table/hardware method. */
    /* [cover parentID={7E5C4D83-4B53-4938-AA36-C735F347C03B}]
    If configured mode is RunTime method
    [/cover] */
    #if  CRC_32P4_MODE == CRC_RUNTIME_MODE
    /* [cover parentID={39CE506D-7782-4d42-BBBA-3464B0DBAAB3}]
    Calculate CRC using Runtime mode
    [/cover] */
    /* Lets calculate the CRC using the runtime method */
    Result = Crc_lCalculateCRC32P4Runtime( Crc_DataPtr, Crc_Length,
                                           Crc_StartValue32, Crc_IsFirstCall);

    /* [cover parentID={FE9879B7-A3CF-46d5-9BE2-45F4ADA34D2F}]
    If configured mode is Table method
    [/cover] */
    #elif CRC_32P4_MODE == CRC_TABLE_MODE
    /* [cover parentID={B7D19CE1-3FEA-417e-890C-8D4F5094D4FB}]
    Calculate CRC using Table mode
    [/cover] */
    /* Lets calculate the CRC using the table method */
    Result = Crc_lCalculateCRC32P4Table( Crc_DataPtr, Crc_Length,
                                         Crc_StartValue32, Crc_IsFirstCall);

    /* [cover parentID={D3D8C990-A725-47ee-9E86-C104350C248D}]
    If configured mode is Hardware method
    [/cover] */
    #elif CRC_32P4_MODE == CRC_HARDWARE_MODE
    /* [cover parentID={D2C5A065-14B5-44fe-86DD-C15EC49AADCC}]
    Calculate CRC using Hardware method
    [/cover] */
    /* Lets calculate the CRC using the table method */
    Result = Crc_lCalculateCRC32P4Hardware( Crc_DataPtr, Crc_Length,
                                            Crc_StartValue32, Crc_IsFirstCall);

    #endif
  }
  return Result;
}
#endif
/* #ifdef CRC_32P4_MODE */


#if (CRC_8_MODE == CRC_RUNTIME_MODE) || (CRC_8H2F_MODE == CRC_RUNTIME_MODE)
/*******************************************************************************
** Traceability     : [cover parentID={C1A35029-6D42-45b1-92CA-F3FA8191D39A}] **
**                                                                            **
** Syntax     : static uint8 Crc_lCommonCalculateCRC8Runtime                  **
**      (                                                                     **
**        const uint8* const Crc_DataPtr,                                     **
**        const uint32 Crc_Length,                                            **
**        const uint8 Crc_StartValue8,                                        **
**        const uint8 Polynomial_8bit                                         **
**      )                                                                     **
**                                                                            **
** Description    :                                                           **
** - This function takes the value of input data pointerU, start value and    **
**   polynomialU, calculates the CRC value and returns the CRC                **
** - This function is local to the library module and is not for the user of  **
**   CRC Library                                                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : none                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : reentrant                                                 **
**                                                                            **
** Parameters (in)  : Crc_DataPtr  - Pointer to the start of the datablock    **
**        Crc_Length - Length of the input data to be fetched                 **
**        Crc_StartValue8 -Start value for CRC Calculation                    **
**        Polynomial_8bit - 8bit polynomial to be used                        **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value   : uint8                                                     **
**                                                                            **
*******************************************************************************/
static uint8 Crc_lCommonCalculateCRC8Runtime
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint8 Crc_StartValue8,
  const uint8 Polynomial_8bit
)
{
  uint32 LoopCounter;
  uint8 MessageBit;
  uint8 StartValue8 = Crc_StartValue8;


  /* Well, the fundamental concept is to an XOR division on the binary data
   * to calculate the CRC. We will cycle through each byte and each bit to
   * perform the division. Keep in mind that we are concerned only about the
   * reminder. Quotient is not in the consideration, unlike the traditional
   * math. */

  /* [cover parentID={92C19865-4931-4d65-84CF-945F36EB69A7}]
  Do an XOR division on the binary data to calculate the CRC.
  [/cover] */
  for (LoopCounter = CRC_ZERO_U; LoopCounter < Crc_Length;
       LoopCounter++)
  {

    /* Perform an XOR with the start value or the value which was
     * obtained in the previous cycle. */
    StartValue8 ^= Crc_DataPtr[LoopCounter];

    /* [cover parentID={C1CDBBB2-569A-437f-9B51-D18023FD0345}]
    Do the division bit wise
    [/cover] */
    for(MessageBit = CRC_BYTELENGTH_U; MessageBit > CRC_ZERO_U;
        MessageBit--)
    {

      /* The fundamental idea here is to do the division on the value
       * for which the CRC needs to be computed. This is achieved by
       * shifting the data left continuously, and doing XOR with the
       * result as long as the MSB is 1. Only in this case, the
       * division is meaningful. */

      /* [cover parentID={93E359DB-A026-4189-BEE0-A56147E85A39}]
      Check if the MSB bit is 1.
      [/cover] */
      if(( StartValue8 & CRC_CRC8_MSB ) == CRC_CRC8_MSB)
      {
        /* If MSB is 1 then left shift and X-OR with polynomial*/
        /* [cover parentID={5472E159-775B-41cb-A1B4-25891B8A008F}]
        Left shift Start Value once and XOR with the Polynomial
        [/cover] */
        StartValue8 =
          ((uint8)((uint8)StartValue8 << CRC_ONE_U))
          ^ Polynomial_8bit;
      }
      else
      {
        /* If MSB is 0 then do only left shift */
        /* [cover parentID={D5E4268A-8C72-481e-B4E3-E85669EABFA3}]
        Left shift Start Value once
        [/cover] */
        StartValue8 =
          (uint8)((uint8)StartValue8 << CRC_ONE_U);
      }

    }

  }


  return StartValue8;
}

#endif
/* #if ((CRC_8_MODE == CRC_RUNTIME_MODE) ||
              (CRC_8H2F_MODE == CRC_RUNTIME_MODE)) */



#if  (CRC_8_MODE == CRC_RUNTIME_MODE)
/*******************************************************************************
** Traceability     : [cover parentID={4EFA3C16-C40B-425a-B4CE-F3129F56B490}] **
**                                                                            **
** Syntax     : static uint8 Crc_lCalculateCRC8Runtime                        **
**      (                                                                     **
**        const uint8* const Crc_DataPtr,                                     **
**        const uint32 Crc_Length,                                            **
**        const uint8 Crc_StartValue8,                                        **
**        const boolean Crc_IsFirstCall                                       **
**      )                                                                     **
**                                                                            **
** Description    :                                                           **
** - This function takes the value of input data pointer, start value and     **
**   polynomial, calculates the CRC value and returns the CRC xored with      **
**   XOR value                                                                **
** - This function is local to the library module and is not for the user of  **
**   CRC Library                                                              **
** - The polynomial 0x1D is used for the computation.                         **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : none                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : reentrant                                                 **
**                                                                            **
** Parameters (in)  : Crc_DataPtr  - Pointer to the start of the datablock    **
**        Crc_Length - Length of the input data to be fetched                 **
**        Crc_StartValue8 -Start value for CRC Calculation                    **
**        Crc_IsFirstCall -Boolean to decide the start value                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value   : uint8                                                     **
**                                                                            **
*******************************************************************************/
static uint8 Crc_lCalculateCRC8Runtime
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint8 Crc_StartValue8,
  const boolean Crc_IsFirstCall
)
{
  uint8 StartValue8;

  /* Is this the first call to compute the CRC? */
  /* [cover parentID={572EB332-8188-4a2d-BC86-EBDD5F49C5E6}]
  Is this first call?
  [/cover] */
  if(Crc_IsFirstCall == (boolean)TRUE)
  {
    /* [cover parentID={DE2366E4-FC2E-4cf0-BCBF-C8B872AAC4A6}]
    Set Start Value to Initial value for 8 bit CRC
    [/cover] */
    /* Initial value being assigned for the first call of
     * the CRC computation. */
    StartValue8 = CRC_INITIAL_VALUE8;

  }
  else
  {
    /* [cover parentID={F3ADCCAE-0E6E-4608-A7DA-7ABB274AE6CB}]
     XOR Start Value with XOR Value for the 8 bit CRC
    [/cover] */
    StartValue8 = Crc_StartValue8;
    /* This is not the first call. We will XOR the start value. */
    StartValue8 = StartValue8 ^ CRC_CRC8_XOR_VALUE;

  }


  /* Invoke the common function which would compute the 8 bit CRC */
  /* [cover parentID={130CF239-AD3C-48bc-B984-4564E155262C}]
  Calculate 8 bit CRC
  [/cover] */
  StartValue8 = Crc_lCommonCalculateCRC8Runtime( Crc_DataPtr,
                Crc_Length, StartValue8, CRC_CRC8_POLYNOMIAL);

  /* Perform an XOR, with the XOR value */
  StartValue8 = StartValue8 ^ CRC_CRC8_XOR_VALUE;


  return StartValue8;
}

#elif (CRC_8_MODE == CRC_TABLE_MODE)
/*******************************************************************************
** Traceability     : [cover parentID={0A9AEBC1-2CBB-4a10-8ABC-82B80C76D2A8}] **
**                                                                            **
** Syntax     : static uint8 Crc_lCalculateCRC8Table                          **
**      (                                                                     **
**        const uint8* const Crc_DataPtr,                                     **
**        const uint32 Crc_Length,                                            **
**        const uint8 Crc_StartValue8,                                        **
**        const boolean Crc_IsFirstCall                                       **
**      )                                                                     **
**                                                                            **
** Description    :                                                           **
** - This function takes the value of input data pointer, start value and     **
**   polynomial, calculates the crc taking the precomputed                    **
**   xor value  and returns the CRC xored with XOR value                      **
** - This function is local to the library module and is not for the user of  **
**   CRC Library                                                              **
** [/cover]                                                                   **
**                                                                            **
**                                                                            **
** Service ID     : none                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : reentrant                                                 **
**                                                                            **
** Parameters (in)  : Crc_DataPtr  - Pointer to the start of the datablock    **
**        Crc_Length - Length of the input data to be fetched                 **
**        Crc_StartValue8 -Start value for CRC Calculation                    **
**        Crc_IsFirstCall -Boolean to decide the start value                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value   : uint8                                                     **
**                                                                            **
*******************************************************************************/
static uint8 Crc_lCalculateCRC8Table
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint8 Crc_StartValue8,
  const boolean Crc_IsFirstCall
)
{
  uint32 LoopCounter ;
  uint8 CompareData ;
  uint8 StartValue8 = Crc_StartValue8;


  /* Is this the first call to compute the CRC? */
  /* [cover parentID={C96C53D6-1DA8-490d-84F7-22611F9C46BC}]
  Check if this is first call
  [/cover] */
  if (Crc_IsFirstCall == (boolean)TRUE)
  {
    /* [cover parentID={093D9E2B-D504-4fdc-9876-EB57F523E3DB}]
    Set Start Value to Initial value for 8 bit CRC
    [/cover] */
    /* Assign the initial value for the CRC8 */
    StartValue8 = CRC_INITIAL_VALUE8;

  }
  else
  {
    /* [cover parentID={302963BE-E989-4a47-A6B7-5B2D5BA78A2A}]
    XOR Start Value with XOR Value for the 8 bit CRC
    [/cover] */
    /* This is not the first call. We will XOR the start value. */
    StartValue8 = StartValue8 ^ CRC_CRC8_XOR_VALUE;

  }

  /* ********************************************************************
   * Table method - what's this?
   * Now, the runtime method is a slow and inefficient method to compute
   * the CRC, obviously. Parsing each bit from the message to compute the
   * CRC can be a nightmare when the volume of the data becomes bigger.
   * The lookup table method aims to accelerate the computation by
   * providing lookup values for the possible data combinations. This
   * would eliminate all the bit handling stuff and we can start thinking
   * on the byte level, instead of bits!
   * ******************************************************************** */

  /* [cover parentID={39158678-4B1E-40b4-8A29-EC0B98E9F4E7}]
  Parse each byte from the message
  [/cover] */
  for(LoopCounter = CRC_ZERO_U; LoopCounter < Crc_Length;
      LoopCounter++)
  {

    /* [cover parentID={62B7DA76-40B0-45b2-B66D-99329D5A1AFC}]
    XOR the Byte with Start Value, fetch the value from lookup
    table using the XOR result and store in Start Value
    [/cover] */
    CompareData = Crc_DataPtr[LoopCounter] ^ StartValue8;

    /* Extract each byte from the message, fetch the value from
     * lookup table */
    StartValue8 = Crc_Table8[CompareData] ^
                  (uint8)((uint16)((uint16)StartValue8 << CRC_BYTELENGTH_U));

  }

  StartValue8 = CRC_CRC8_XOR_VALUE ^ StartValue8;


  return StartValue8;
}

#elif (CRC_8_MODE == CRC_HARDWARE_MODE)

/*******************************************************************************
** Traceability     : [cover parentID={AF5A23ED-025E-4705-8F3E-2FB99FBE94CB}] **
**                                                                            **
** Syntax     : static uint8 Crc_lCalculateCRC8Hardware                       **
**      (                                                                     **
**        const uint8* const Crc_DataPtr,                                     **
**        const uint32 Crc_Length,                                            **
**        const uint8 Crc_StartValue8,                                        **
**        const boolean Crc_IsFirstCall                                       **
**      )                                                                     **
**                                                                            **
** Description    :                                                           **
** - This function takes the value of input data pointer, start value and     **
**   polynomial, calculates the crc using the hardware and returns the CRC    **
** - This function is local to the library module and is not for the user of  **
**   CRC Library                                                              **
** [/cover]                                                                   **
**                                                                            **
**                                                                            **
** Service ID     : none                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters (in)  : Crc_DataPtr  - Pointer to the start of the datablock    **
**        Crc_Length - Length of the input data to be fetched                 **
**        Crc_StartValue8 -Start value for CRC Calculation                    **
**        Crc_IsFirstCall -Boolean to decide the start value                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value   : uint8                                                     **
**                                                                            **
*******************************************************************************/
static uint8 Crc_lCalculateCRC8Hardware
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint8 Crc_StartValue8,
  const boolean Crc_IsFirstCall
)
{
  uint32 LoopCounter;
  volatile uint16 TimeOut;
  uint8 Temp;
  uint8 StartValue8 = Crc_StartValue8;
  uint8 ChannelNumber;

  /*assign the base address of FCE*/

  Ifx_FCE *FCERegBaseAddress = &MODULE_FCE;
  TimeOut = CRC_TIMEOUT_VAL;
  /* [cover parentID={8548CF69-4E51-4754-9B6E-AA172CED2EB6}]
  [/cover] */
  /* [cover parentID={05EC355F-BEC9-41ce-92A3-D6AD1FF0DFEE}]
  [/cover] */
  /* [cover parentID={A93C51CD-E48E-40d6-9A52-1BE8F727685D}]
  Critical Section
  [/cover] */
  SchM_Enter_Crc_CriticalSection();
  /* The critical section starts here. The interrupts needs to be disabled */

  Mcal_GetSpinlock(&Crc_SpinLockAddress, CRC_SPINLOCKTIMEOUT_VAL);
  /* MISRA2012_RULE_13_5_JUSTIFICATION: And operator required for timeout and
  channel busy check  */
  /* [cover parentID={8F123D29-5B97-48d6-A12F-75D506BEE924}]
  Wait here untill any one channel is free or timeout expires
  [/cover] */
  while((Crc_ChannelFlag == 0xFFu) && (TimeOut != CRC_ZERO_U))
  {
    TimeOut -- ;        /* Wait for a free channel untill TimeOut expires */
  }
  /* [cover parentID={A11F42CE-0AD4-4eb5-AA2E-AC1C6A06FE47}]
  If timeout expires
  [/cover] */
  if(TimeOut != CRC_ZERO_U)
  {
    /* Loop across all channels to check for a free channel */
    /* [cover parentID={389F2DCF-AABD-4b08-8867-A39291C262B0}]
    Loop across all channels to check for a free channel
    [/cover] */
    for(ChannelNumber = CRC_ZERO_U; ChannelNumber < CRC_MAXCHANNELS_U;
        ChannelNumber++)
    {
      /* [cover parentID={BC613507-85D9-4431-9277-AED90DCC378A}]
      block the free channel
      [/cover] */
      if((Crc_ChannelFlag & (CRC_ONE_U << ChannelNumber)) != \
          (CRC_ONE_U << ChannelNumber))
      {
        /*Set this bit busy if you find it free and exit the for loop*/
        /* [cover parentID={156EE6DE-5B06-4582-8AF0-DF621ABA8BC7}]
        [/cover] */
        Crc_ChannelFlag |= (CRC_ONE_U << ChannelNumber);
        break;
      }

    }
    Mcal_ReleaseSpinlock(&Crc_SpinLockAddress);
    SchM_Exit_Crc_CriticalSection();
    /* The critical section ends here. The interrupts would be enabled
     * henceforth. */

    /* MISRA2012_RULE_11_8_JUSTIFICATION:
       MISRA2012_RULE_11_3_JUSTIFICATION: casting of register address to
       corresponding structure pointer   */
    /* The FCE needs to be enabled       */
    CRC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG \
    ((uint32*)&FCERegBaseAddress->CLC.U, CRC_CLC_INITVAL);

    /* Perform the init for the CFG registers */
    /* MISRA2012_RULE_11_8_JUSTIFICATION:
       MISRA2012_RULE_11_3_JUSTIFICATION: casting of register address to
       corresponding structure pointer   */
    /* MISRA2012_RULE_18_1_JUSTIFICATION: Out-of-bound access of pointer
       is taken care. ChannelNumber will not exceed 7 */
    CRC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG((uint32*) \
        &FCERegBaseAddress->IN[ChannelNumber].CFG.U, CRC8_CFGREG_INITVAL);


    /* Configure CRC register*/
    /* [cover parentID={F48F7CFD-B3C1-4802-8252-04A7BC3E77F9}]
    Is first Call ?
    [/cover] */
    if (Crc_IsFirstCall == (boolean)TRUE)
    {
      /* MISRA2012_RULE_18_1_JUSTIFICATION: Out-of-bound access of pointer
         is taken care. ChannelNumber will not exceed 7 */
      /* [cover parentID={B574B777-EAE3-44cb-B403-98D0B5BFD96A}]
      Load the CRC register with Initial CRC Value
      [/cover] */
      FCERegBaseAddress->IN[ChannelNumber].CRC.U = CRC_INITIAL_VALUE8;


    }
    else
    {
      /* [cover parentID={060D9028-B5C4-42a0-8217-80EDD377D154}]
      XOR the Start Value and Load this value to the  CRC register
      [/cover] */
      Temp = (uint8)(StartValue8 ^ CRC_CRC8_XOR_VALUE);
      /* MISRA2012_RULE_18_1_JUSTIFICATION: Out-of-bound access of pointer
         is taken care. ChannelNumber will not exceed 7 */
      FCERegBaseAddress->IN[ChannelNumber].CRC.U = Temp;


    }

    /* input in INIT register */
    /* [cover parentID={98C0F2C4-5C2B-4172-88FC-E5944CC189FC}]
    Feed data to IR register
    [/cover] */
    for (LoopCounter = CRC_ZERO_U; LoopCounter < Crc_Length;
         LoopCounter++)
    {
      /* MISRA2012_RULE_18_1_JUSTIFICATION: Out-of-bound access of pointer
         is taken care. ChannelNumber will not exceed 7 */
      /* [cover parentID={3F25552D-4BF5-4839-9BEF-48620ED20025}]
      Load the data byte to input register
      [/cover] */
      FCERegBaseAddress->IN[ChannelNumber].IR.U = \
          (uint32)Crc_DataPtr[LoopCounter];


    }

    /* MISRA2012_RULE_18_1_JUSTIFICATION: Out-of-bound access of pointer
       is taken care. ChannelNumber will not exceed 7 */
    /* [cover parentID={EFDAC883-007D-4167-A1A7-868033657D04}]
    Get the LSB 8 bits as result from the result register
    [/cover] */
    StartValue8 = (uint8)((FCERegBaseAddress->IN[ChannelNumber].RES.U) & \
                          ( (uint32)(CRC_FCE_IN_CRC_CRC8_MSK) ) );
    /* [cover parentID={1702FA0B-B9BC-4b01-981F-9C08DC9445EB}]
    Set the blocked channel free
    [/cover] */
    Mcal_SetBitAtomic(&Crc_ChannelFlag, ChannelNumber, 1, CRC_ZERO_U);
  }
  else
  {
    /* [cover parentID={6183150E-99C6-4fc3-B503-237A5D89A64A}]
    Release spin lock
    [/cover] */
    Mcal_ReleaseSpinlock(&Crc_SpinLockAddress);
    SchM_Exit_Crc_CriticalSection();
    /* The critical section ends here. The interrupts would be enabled
     * henceforth. */
    /* [cover parentID={15347D88-C491-49ae-A0C3-E405F74308A7}]
    If safety check is enabled
    [/cover] */ 
    #if (CRC_SAFETYENABLE == STD_ON)
    /* [cover parentID={5241FE23-EAD5-4cc4-91A9-56DDDB6C2382}]
    Report Mcal Safety error
    [/cover] */
    Mcal_ReportSafetyError(CRC_MODULE_ID, CRC_INSTANCE_ID,
                           CRC_SID_CALCULATE_CRC8, CRC_E_CHANNEL_TIMEOUT);
    StartValue8 = (uint8)CRC_8_CONFIGERROR_VAL;
    #endif
  }

  return StartValue8;
}

#endif
/* #if (CRC_8_MODE == CRC_HARDWARE_MODE)*/



#if (CRC_8H2F_MODE == CRC_RUNTIME_MODE)
/*******************************************************************************
** Traceability     : [cover parentID={375D1FD1-0042-4a90-9E69-5C8403715831}] **
**                                                                            **
** Syntax     : static uint8 Crc_lCalculateCRC8H2FRuntime                     **
**      (                                                                     **
**        const uint8* const Crc_DataPtr,                                     **
**        const uint32 Crc_Length,                                            **
**        const uint8 Crc_StartValue8,                                        **
**        const boolean Crc_IsFirstCall                                       **
**      )                                                                     **
**                                                                            **
** Description    :                                                           **
** - This function takes the value of input data pointer, start value and     **
**   polynomial, calculates the CRC value and returns the CRC xored with      **
**   XOR value                                                                **
** - This function is local to the library module and is not for the user of  **
**   CRC Library                                                              **
**                                                                            **
**                                                                            **
** Service ID     : none                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : reentrant                                                 **
**                                                                            **
** Parameters (in)  : Crc_DataPtr  - Pointer to the start of the datablock    **
**        Crc_Length - Length of the input data to be fetched                 **
**        Crc_StartValue8 -Start value for CRC Calculation                    **
**        Crc_IsFirstCall -Boolean to decide the start value                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value   : uint8                                                     **
**                                                                            **
*******************************************************************************/
static uint8 Crc_lCalculateCRC8H2FRuntime
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint8 Crc_StartValue8H2F,
  const boolean Crc_IsFirstCall
)
{
  uint8 StartValue8H2F = Crc_StartValue8H2F;

  /* [cover parentID={9D11CED8-FA0E-4416-BFF4-B0FF16E5EE5A}]
  Is this first call?
  [/cover] */
  /* Is this the first call? */
  if(Crc_IsFirstCall == (boolean)TRUE)
  {
    /* [cover parentID={751E1247-617B-4665-9932-6A9F69A5D3FC}]
    Set Start Value to Initial value for 8 bit 0x2F CRC
    [/cover] */
    /* Assign the initial value as set by the standard */
    StartValue8H2F = CRC_INITIAL_VALUE8H2F;

  }
  else
  {
    /* [cover parentID={AFC3DF97-E7C7-4848-9F8C-7638F80DF2DE}]
    XOR Start Value with XOR Value for the 8 bit 0x2F CRC
    [/cover] */
    /* This is not the first call. We will XOR the start value. */
    StartValue8H2F = StartValue8H2F ^ CRC_CRC8H2F_XOR_VALUE;

  }
  /* [cover parentID={49258B29-B330-418e-B844-DC5664235DEF}]
  Calculate 8 bit CRC
  [/cover] */
  /* Invoke the common function which would compute the 8 bit CRC */
  StartValue8H2F = Crc_lCommonCalculateCRC8Runtime( Crc_DataPtr,
                   Crc_Length,    StartValue8H2F, CRC_CRC8H2F_POLYNOMIAL);

  /* Perform an XOR, with the XOR value */
  StartValue8H2F = CRC_CRC8H2F_XOR_VALUE ^ StartValue8H2F;


  return StartValue8H2F;
}

#elif (CRC_8H2F_MODE == CRC_TABLE_MODE)
/*******************************************************************************
** Traceability     : [cover parentID={9DE83B09-7B9D-409d-92E4-AA2D37FFCD55}] **
**                                                                            **
** Syntax     : static uint8 Crc_lCalculateCRC8H2FTable                       **
**      (                                                                     **
**        const uint8* const Crc_DataPtr,                                     **
**        const uint32 Crc_Length,                                            **
**        const uint8 Crc_StartValue8H2F,                                     **
**        const boolean Crc_IsFirstCall                                       **
**      )                                                                     **
**                                                                            **
** Description    :                                                           **
** - This function takes the value of input data pointer, start value and     **
**   polynomial, calculates the crc taking the precomputed                    **
**   xor value  and returns the CRC xored with XOR value                      **
** - This function is local to the library module and is not for the user of  **
**   CRC Library                                                              **
**                                                                            **
**                                                                            **
** Service ID     : none                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : reentrant                                                 **
**                                                                            **
** Parameters (in)  : Crc_DataPtr  - Pointer to the start of the datablock    **
**        Crc_Length - Length of the input data to be fetched                 **
**        Crc_StartValue8H2F -Start value for CRC Calculation                 **
**        Crc_IsFirstCall -Boolean to decide the start value                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value   : uint8                                                     **
**                                                                            **
*******************************************************************************/
static uint8 Crc_lCalculateCRC8H2FTable( const uint8* const Crc_DataPtr,
    const uint32 Crc_Length, const uint8 Crc_StartValue8H2F,
    const boolean Crc_IsFirstCall)
{
  uint32 LoopCounter;
  uint8 CompareData ;
  uint8 StartValue8H2F = Crc_StartValue8H2F;

  /* [cover parentID={4240F2BE-3035-474c-A603-7766C15BBFFF}]
  Check if this is first call
  [/cover] */
  if (Crc_IsFirstCall == (boolean)TRUE)
  {
    /* [cover parentID={4CFD5918-78DF-4074-98E4-6F3FFE8D16B5}]
    Set Start Value to Initial value for 8 bit 0x2F CRC
    [/cover] */
    /* Get the start value needed for the CRC8H2F */
    StartValue8H2F = CRC_INITIAL_VALUE8H2F;

  }
  else
  {
    /* [cover parentID={55E3089F-307B-4d9a-AFED-539106DEE9B6}]
    XOR Start Value with XOR Value for the 8 bit 0x2F CRC
    [/cover] */
    /* This is not the first call. We will XOR the start value. */
    StartValue8H2F = StartValue8H2F ^ CRC_CRC8H2F_XOR_VALUE;

  }

  /* ********************************************************************
   * Table method - what's this?
   * Now, the runtime method is a slow and inefficient method to compute
   * the CRC, obviously. Parsing each bit from the message to compute the
   * CRC can be a nightmare when the volume of the data becomes bigger.
   * The lookup table method aims to accelerate the computation by
   * providing lookup values for the possible data combinations. This
   * would eliminate all the bit handling stuff and we can start thinking
   * on the byte level, instead of bits!
   * ******************************************************************** */

  /* [cover parentID={4879B690-4339-4c86-96DC-69E50D8AE499}]
   Parse each byte from the message
  [/cover] */
  /* Extract each byte from the message, fetch the value from
   * lookup table and XOR with the CRC value*/
  for(LoopCounter = CRC_ZERO_U; LoopCounter < Crc_Length;
      LoopCounter++)
  {

    /* [cover parentID={AAA1B3C0-87D6-49a5-AC47-CBF770818402}]
    XOR the Byte with Start Value, fetch the value from lookup table
    using the XOR result and store in Start Value
    [/cover] */
    CompareData = Crc_DataPtr[LoopCounter] ^ StartValue8H2F ;

    /* Get the look up value from the CRC table */
    StartValue8H2F = Crc_Table8H2F[CompareData] ^
                  (uint8)((uint16)((uint16)StartValue8H2F << CRC_BYTELENGTH_U));
  }

  StartValue8H2F = CRC_CRC8H2F_XOR_VALUE ^ StartValue8H2F;


  return StartValue8H2F;
}

#endif
/* #if (CRC_8H2F_MODE == CRC_TABLE_MODE)*/



#if (CRC_16_MODE == CRC_RUNTIME_MODE)

/*******************************************************************************
** Traceability     : [cover parentID={F2ABF50E-BC3F-4455-9F04-2F34C3AA425E}] **
**                                                                            **
** Syntax     : static uint16 Crc_lCalculateCRC16Runtime                      **
**      (                                                                     **
**        const uint8* const Crc_DataPtr,                                     **
**        const uint32 Crc_Length,                                            **
**        const uint16 Crc_StartValue16,                                      **
**        const boolean Crc_IsFirstCall                                       **
**      )                                                                     **
**                                                                            **
** Description    :                                                           **
** - This function takes the value of input data pointer, start value and     **
**   polynomial, calculates the CRC value and returns the CRC xored with      **
**   XOR value                                                                **
** - This function is local to the library module and is not for the user of  **
**   CRC Library                                                              **
**                                                                            **
** Service ID     : none                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : reentrant                                                 **
**                                                                            **
** Parameters (in)  : Crc_DataPtr  - Pointer to the start of the datablock    **
**        Crc_Length - Length of the input data to be fetched                 **
**        Crc_StartValue16 -Start value for CRC Calculation                   **
**        Crc_IsFirstCall -Boolean to decide the start value                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value   : uint16                                                    **
**                                                                            **
**                                                                            **
*******************************************************************************/
static uint16 Crc_lCalculateCRC16Runtime( const uint8* const Crc_DataPtr,
    const uint32 Crc_Length, const uint16 Crc_StartValue16,
    const boolean Crc_IsFirstCall)
{
  uint32 LoopCounter;
  uint32 MessageBit;
  uint16 StartValue16 = Crc_StartValue16;

  /* [cover parentID={361BB8E6-99FA-4b83-B15C-6F5D066060F3}]
  Is this first call?
  [/cover] */
  /* Is this the first call? */
  if(Crc_IsFirstCall == (boolean)TRUE)
  {
    /* Assign the standard start value */
    /* [cover parentID={14550BA8-2907-4004-BA02-3EE15620EE4C}]
    Set Start Value to Initial value for 16 bit CRC
    [/cover] */
    StartValue16 = CRC_INITIAL_VALUE16;
  }
  else
  {
    /* This is not the first call. We will XOR the start value. */
    /* [cover parentID={3CD28638-AD99-40a3-9B69-CA8EB0168CDB}]
    XOR Start Value with XOR Value for the 16 bit CRC
    [/cover] */
    StartValue16 = StartValue16 ^ CRC_CRC16_XOR_VALUE;
  }

  /* Well, the fundamental concept is to an XOR division on the binary data
   * to calculate the CRC. We will cycle through each byte and each bit to
   * perform the division. Keep in mind that we are concerned only about the
   * reminder. Quotient is not in the consideration, unlike the traditional
   * math. ;-) */
  /* [cover parentID={F4FE119D-5309-48dd-ABB1-68C256127910}]
  Do an XOR division on the binary data to calculate the CRC.
  [/cover] */
  for(LoopCounter = CRC_ZERO_U; LoopCounter < Crc_Length;
      LoopCounter++)
  {
    /* [cover parentID={23C3F5B4-D7BD-4dbc-A8C7-19FA74534A08}]
    Perform an XOR between Start Value and the Byte and store in Start Value
    [/cover] */
    StartValue16 ^= (uint16)((uint16)Crc_DataPtr[LoopCounter] <<
                             (CRC_CRC16_SIZE - CRC_BYTELENGTH_U));

    /* [cover parentID={39F24CC2-7B29-44e6-9D51-411FC2608BFF}]
    Do the division bit wise
    [/cover] */
    for(MessageBit = CRC_BYTELENGTH_U; MessageBit > CRC_ZERO_U;
        MessageBit--)
    {

      /* [cover parentID={3EFF86C4-BBB3-43c9-A3C2-EA4BBEE8300D}]
      Is the MSB one ?
      [/cover] */
      if((StartValue16 & CRC_CRC16_MSB) == CRC_CRC16_MSB)
      {
        /* If MSB is 1 then left shift and X-OR with polynomial*/
        /* [cover parentID={4D3173AC-2DDA-45ac-B67E-3F2728536254}]
        Left shift Start Value once and XOR with the Polynomial
        [/cover] */
        StartValue16 =
          (uint16)((uint16)StartValue16 << CRC_ONE_U)
          ^ CRC_CRC16_POLYNOMIAL;

      }
      else
      {
        /* If MSB is 0 then left shift and X-OR with polynomial*/
        /* [cover parentID={3D6E8CB4-19B0-4caf-8618-CAE78FB788A1}]
        Left shift Start Value once
        [/cover] */
        StartValue16 =
          (uint16)((uint16)StartValue16 << CRC_ONE_U);
      }

    }

  }

  StartValue16 = CRC_CRC16_XOR_VALUE ^ StartValue16;


  return StartValue16;
}

#elif (CRC_16_MODE == CRC_TABLE_MODE)
/*******************************************************************************
** Traceability     : [cover parentID={FE2FFCD0-E244-4332-972C-D842C19E914C}] **
**                                                                            **
** Syntax     : static uint16 Crc_lCalculateCRC16Table                        **
**      (                                                                     **
**        const uint8* const Crc_DataPtr,                                     **
**        const uint32 Crc_Length,                                            **
**        const uint16 Crc_StartValue16,                                      **
**        const boolean Crc_IsFirstCall                                       **
**      )                                                                     **
**                                                                            **
** Description    :                                                           **
** - This function takes the value of input data pointer, start value and     **
**   polynomial, calculates the crc taking the precomputed                    **
**   xor value  and returns the CRC xored with XOR value                      **
** - This function is local to the library module and is not for the user of  **
**   CRC Library                                                              **
**                                                                            **
** Service ID     : none                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : reentrant                                                 **
**                                                                            **
** Parameters (in)  : Crc_DataPtr  - Pointer to the start of the datablock    **
**        Crc_Length - Length of the input data to be fetched                 **
**        Crc_StartValue16 -Start value for CRC Calculation                   **
**        Crc_IsFirstCall -Boolean to decide the start value                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value   : uint16                                                    **
**                                                                            **
**                                                                            **
*******************************************************************************/
static uint16 Crc_lCalculateCRC16Table( const uint8* const Crc_DataPtr,
                                        const uint32 Crc_Length, 
                                        const uint16 Crc_StartValue16,
                                        const boolean Crc_IsFirstCall)
{
  /* code for crc 16 Table based calculaion with 0x1021 polynomial*/
  uint32 LoopCounter;
  uint16 TempLocal;
  uint16 DataVal;
  uint16 StartValue16 = Crc_StartValue16;

  /* [cover parentID={DEEE439B-3C3D-43a4-B35B-484EECB13FC8}]
  Check if this is first call
  [/cover] */
  /*Initialization of Table array*/
  if(Crc_IsFirstCall == (boolean)TRUE)
  {
    /* [cover parentID={33482AC4-90A6-406c-BD24-43D06434F1E9}]
    Set Start Value to Initial value for 16bit CRC
    [/cover] */
    StartValue16 = CRC_INITIAL_VALUE16;
  }
  else
  {
    /* [cover parentID={F52AA5AD-1C66-4d75-B0CD-FC1244B18E42}]
    XOR Start Value with XOR Value for the 16 bit CRC
    [/cover] */
    StartValue16 = StartValue16 ^ CRC_CRC16_XOR_VALUE;
  }

  /* ********************************************************************
   * Table method - what's this?
   * Now, the runtime method is a slow and inefficient method to compute
   * the CRC, obviously. Parsing each bit from the message to compute the
   * CRC can be a nightmare when the volume of the data becomes bigger.
   * The lookup table method aims to accelerate the computation by
   * providing lookup values for the possible data combinations. This
   * would eliminate all the bit handling stuff and we can start thinking
   * on the byte level, instead of bits!
   * ******************************************************************** */
  /* [cover parentID={3271593E-BE10-4b8c-89C6-455622CB4A4D}]
  Parse each byte from the message
  [/cover] */
  for(LoopCounter = CRC_ZERO_U; LoopCounter < Crc_Length;
      LoopCounter++)
  {
    /* [cover parentID={BD197EF4-EC4D-403b-9619-BFD0E5616759}]
    XOR the Byte with Start Value, fetch the value from lookup table using
    the XOR result, XOR the fetched value with Start Value shifted 8 times
    right and store in Start Value
    [/cover] */

    DataVal = (uint16)(Crc_DataPtr[LoopCounter]);
    TempLocal = (uint16)(( (uint16)(StartValue16 >> (uint16)CRC_BYTELENGTH_U)
                           ^ DataVal) & (uint16)CRC_U16LSB_MASK);

    StartValue16 = (uint16)((uint16)(StartValue16 &
                   (uint16)CRC_U16LSB_MASK) << (uint16)CRC_BYTELENGTH_U)
                   ^ Crc_Table16[TempLocal];


  }

  StartValue16 = CRC_CRC16_XOR_VALUE ^ StartValue16;


  return StartValue16;
}

#elif (CRC_16_MODE == CRC_HARDWARE_MODE)
/*******************************************************************************
** Traceability     : [cover parentID={E4902B7F-02E7-408d-B282-CECBACC7336E}] **
**                                                                            **
** Syntax     : static uint16 Crc_lCalculateCRC16Hardware                     **
**      (                                                                     **
**        const uint8* const Crc_DataPtr,                                     **
**        const uint32 Crc_Length,                                            **
**        const uint16 Crc_StartValue16,                                      **
**        const boolean Crc_IsFirstCall                                       **
**      )                                                                     **
**                                                                            **
** Description    :                                                           **
** - This function takes the value of input data pointer, start value and     **
**   polynomial, calculates the crc using the hardware and returns the CRC    **
**   xored with the XOR_VALUE                                                 **
** - This function is local to the library module and is not for the user of  **
**   CRC Library                                                              **
**                                                                            **
** Service ID     : none                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters (in)  : Crc_DataPtr  - Pointer to the start of the datablock    **
**        Crc_Length - Length of the input data to be fetched                 **
**        Crc_StartValue16 -Start value for CRC Calculation                   **
**        Crc_IsFirstCall -Boolean to decide the start value                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value   : uint16                                                    **
**                                                                            **
**                                                                            **
*******************************************************************************/
static uint16 Crc_lCalculateCRC16Hardware( const uint8* const Crc_DataPtr,
    const uint32 Crc_Length,  const uint16 Crc_StartValue16,
    const boolean Crc_IsFirstCall)
{
  uint32 LoopCounter;
  volatile uint16 TimeOut;
  uint16 tempVal;
  uint16 temp;
  uint16 StartValue16 = Crc_StartValue16;
  uint8 ChannelNumber;


  Ifx_FCE *FCERegBaseAddress = &MODULE_FCE;
  TimeOut = CRC_TIMEOUT_VAL;
  /* [cover parentID={8548CF69-4E51-4754-9B6E-AA172CED2EB6}]
  [/cover] */
  /* [cover parentID={05EC355F-BEC9-41ce-92A3-D6AD1FF0DFEE}]
  [/cover] */
  /* [cover parentID={5B3DB737-790E-4d47-AED5-C72D00D167DA}]
  Critical Section
  [/cover] */
  SchM_Enter_Crc_CriticalSection();
  /* The critical section starts here. The interrupts needs to be disabled */

  Mcal_GetSpinlock(&Crc_SpinLockAddress, CRC_SPINLOCKTIMEOUT_VAL);
  /* MISRA2012_RULE_13_5_JUSTIFICATION: And operator required for timeout and
  channel busy check  */
  /* [cover parentID={DB9BD7EC-60D0-41be-B5A0-6091927B5335}]
  Wait here untill any one channel is free or timeout expires
  [/cover] */
  while((Crc_ChannelFlag == 0xFFu) && (TimeOut != CRC_ZERO_U))
  {
    /* [cover parentID={DB9BD7EC-60D0-41be-B5A0-6091927B5335}]
    [/cover] */
    TimeOut -- ;        /* Wait for a free channel untill TimeOut expires */
  }
  /* [cover parentID={D960A00E-43C9-435d-92E7-C3356E3779AD}]
  If timeout expires
  [/cover] */
  if(TimeOut != CRC_ZERO_U)
  {
    /* [cover parentID={D7BE522F-F330-4278-A846-647198D1AF59}]
     Loop across all channels to check for a free channel
    [/cover] */
    /* Loop across all channels to check for a free channel */
    for(ChannelNumber = CRC_ZERO_U; ChannelNumber < CRC_MAXCHANNELS_U;
        ChannelNumber++)
    {
      /* [cover parentID={82690CEB-8CA4-4d02-9EA7-243266EE6EAA}]
      block the free channel
      [/cover] */
      if((Crc_ChannelFlag & (CRC_ONE_U << ChannelNumber)) != \
          (CRC_ONE_U << ChannelNumber))
      {
        /* [cover parentID={44505D3E-00F3-4c09-A2A6-D063CFA3E0BC}]
        block the channel
        [/cover] */
        /* Set this bit busy if you find it free and exit the for loop*/
        Crc_ChannelFlag |= (CRC_ONE_U << ChannelNumber);
        break;
      }

    }
    Mcal_ReleaseSpinlock(&Crc_SpinLockAddress);
    SchM_Exit_Crc_CriticalSection();
    /* The critical section ends here. The interrupts would be enabled
     * henceforth. */

    /* The FCE needs to be enabled */
    /* MISRA2012_RULE_11_8_JUSTIFICATION:
       MISRA2012_RULE_11_3_JUSTIFICATION: casting of register address to
       corresponding structure pointer   */
    CRC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG \
    ((uint32*)&FCERegBaseAddress->CLC.U, CRC_CLC_INITVAL);

    /* Perform the init for the CFG registers */
    /* MISRA2012_RULE_11_8_JUSTIFICATION:
       MISRA2012_RULE_11_3_JUSTIFICATION: casting of register address to
       corresponding structure pointer   */
    /* MISRA2012_RULE_18_1_JUSTIFICATION: Out-of-bound access of pointer
       is taken care. ChannelNumber will not exceed 7  */
    CRC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG((uint32*) \
        &FCERegBaseAddress->IN[ChannelNumber].CFG.U, CRC16_CFGREG_INITVAL);


    /* code for crc 16 hardware calculation with 0x1021 polynomial*/
    /* reset end init protection to enable FCE using CLC register*/
    /* [cover parentID={0D2590F9-F7B4-4e17-9D3D-256EBD860620}]
    Is first Call ?
    [/cover] */
    /*Configure CRC register*/
    if (Crc_IsFirstCall == (boolean)TRUE)
    {
      /* [cover parentID={45138D92-1821-4c00-8604-F59D1C03919B}]
      Load the CRC register with Initial CRC Value
      [/cover] */
      /* MISRA2012_RULE_18_1_JUSTIFICATION: Out-of-bound access of pointer
         is taken care. ChannelNumber will not exceed 7 */
      FCERegBaseAddress->IN[ChannelNumber].CRC.U = CRC_INITIAL_VALUE16;

    }
    else
    {
      /* [cover parentID={2ADB5F11-41DA-44b3-BE84-85672EA73688}]
      XOR the Start Value and Load this value to the  CRC register
      [/cover] */
      temp = StartValue16 ^ CRC_CRC16_XOR_VALUE;
      /* MISRA2012_RULE_18_1_JUSTIFICATION: Out-of-bound access of pointer
         is taken care. ChannelNumber will not exceed 7 */
      FCERegBaseAddress->IN[ChannelNumber].CRC.U = temp;

    }

    /* [cover parentID={758793E7-894F-4f06-9AAA-3D15231B4417}]
    Feed data to IR register
    [/cover] */
    /* input in INIT register */
    for (LoopCounter = CRC_ZERO_U; LoopCounter < Crc_Length; LoopCounter +=
           CRC_TWO_U)
    {
      /* [cover parentID={CAB4D9D0-8C22-4de8-A86A-813EAF702415}]
      Convert the 2 invidual bytes into a 16 bit word and load into
      input register. If data length is odd then shift last byte to MSB
      of the 16 bit word.
      [/cover] */
      if( (LoopCounter / CRC_TWO_U) == (Crc_Length / CRC_TWO_U) )
      {
        /* [cover parentID={CAB4D9D0-8C22-4de8-A86A-813EAF702415}]
        [/cover] */
        tempVal = (uint16)((uint16)Crc_DataPtr[LoopCounter] <<
                           CRC_BYTELENGTH_U);
      }
      else
      {
        /* [cover parentID={CAB4D9D0-8C22-4de8-A86A-813EAF702415}]
        [/cover] */
        tempVal = Crc_DataPtr[LoopCounter];

        tempVal = tempVal << CRC_BYTELENGTH_U;

        tempVal = tempVal ^ Crc_DataPtr[LoopCounter + CRC_ONE_U];
      }

      /* MISRA2012_RULE_18_1_JUSTIFICATION: Out-of-bound access of pointer
         is taken care. ChannelNumber will not exceed 7 */
      FCERegBaseAddress->IN[ChannelNumber].IR.U = (uint32)tempVal;

    }

    /* MISRA2012_RULE_18_1_JUSTIFICATION: Out-of-bound access of pointer
       is taken care. ChannelNumber will not exceed 7 */
    /* [cover parentID={7FC33588-C4F1-40cd-9697-F8E226C78CEB}]
    Get the LSB 16 bits as result from the result register
    [/cover] */
    StartValue16 = (uint16)((FCERegBaseAddress->IN[ChannelNumber].RES.U) & \
                            ((uint32)(CRC_FCE_IN_CRC_CRC16_MSK)));
    /* [cover parentID={ACA3AFE8-A82F-44f3-B2E2-1BB4B446990E}]
    Set the blocked channel free
    [/cover] */
    Mcal_SetBitAtomic(&Crc_ChannelFlag, ChannelNumber, 1, CRC_ZERO_U);
  }
  else
  {
    /* [cover parentID={C15F8D26-5FEE-4dfd-9131-7F7998F7FADD}]
    Release spin lock
    [/cover] */
    Mcal_ReleaseSpinlock(&Crc_SpinLockAddress);
    SchM_Exit_Crc_CriticalSection();
    /* The critical section ends here. The interrupts would be enabled
     * henceforth. */

    /* [cover parentID={C5C29192-4395-43e0-981B-7AE4B137C2D5}]
    If safety check is enabled
    [/cover] */
    #if (CRC_SAFETYENABLE == STD_ON)
    /* [cover parentID={4E44288C-2A33-48e7-95D8-2A27C5DD3CC4}]
    Report Mcal Safety error in case of timeout
    [/cover] */
    Mcal_ReportSafetyError(CRC_MODULE_ID, CRC_INSTANCE_ID,
                           CRC_SID_CALCULATE_CRC16, CRC_E_CHANNEL_TIMEOUT);
    StartValue16 = (uint16)CRC_16_CONFIGERROR_VAL;
    #endif
  }


  return StartValue16;
}

#endif
/* #endif (CRC_16_MODE == CRC_HARDWARE_MODE)*/


#if (CRC_32_MODE != STD_OFF) || (CRC_32P4_MODE != STD_OFF)
/*******************************************************************************
** Traceability     : [cover parentID={6A5349E1-7B09-42f0-9E13-CA182ED2219A}] **
**                                                                            **
** Syntax     : static uint32 Crc_lReflectCRC32                               **
**      (                                                                     **
**        const uint32 CRCData_32bit,                                         **
**        const uint8 CRC_BitCount                                            **
**      )                                                                     **
**                                                                            **
** Description    :                                                           **
** - This function takes the 32bit crc data and length of the data, calculates**
**   reverses it and return back.                                             **
** - This function is local to the library module and is not for the user of  **
**   CRC Library                                                              **
**                                                                            **
** Service ID     : none                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : reentrant                                                 **
**                                                                            **
** Parameters (in)  : CRCData_32bit -Start value for CRC Calculation          **
**        CRC_BitCount -Boolean to decide the start value                     **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value   : uint32                                                    **
**                                                                            **
**                                                                            **
*******************************************************************************/
static uint32 Crc_lReflectCRC32(const uint32 CRCData_32bit,
                                const uint8 CRC_BitCount)
{
  uint32 ReversedData = CRC_ZERO_U;
  uint8  MsgBit;
  uint32 Data_32bit = CRCData_32bit;


  /* Cycle through each of the bit in the parameter passed to the
   * function and reverse the bits. i.e. after the processing done by
   * this function, the data bits in the result would be in
   * the reverse order. */
  /* [cover parentID={EA7FE783-53D3-4d6b-A61A-D58681796E32}]
   Reverse the bits and store in a 32bit variable
  [/cover] */
  for (MsgBit = CRC_ZERO_U; MsgBit < CRC_BitCount; MsgBit++)
  {
    /* [cover parentID={0A91EF0F-AAE2-4675-9BC7-8E099F67B449}]
    Store the bits in reverse order
    [/cover] */
    /* Start cycling through each bit of the data */
    if( (Data_32bit & CRC_ONE_U) == CRC_ONE_U )
    {
      /* [cover parentID={2E3A984E-A9E4-4865-B4BF-44A2279F5596}]
      Write 1 to the corresponding bit so that the bit is stored in
      reverse order in the variable which will hold the reverse value
      [/cover] */
      /* If a bit '1' is detected, set the bit at the opposite
       * end of the data so that we can reverse the information. */
      ReversedData |= (uint32)((uint32)CRC_ONE_U <<
                               ((CRC_BitCount - CRC_ONE_U) - MsgBit));
    }


    /* Shift the data to the right by one bit */
    Data_32bit = (uint32)((uint32)Data_32bit >> (uint32)CRC_ONE_U);

  }


  return ReversedData;
}

#endif
/* #if defined (CRC_32_MODE)) || defined (CRC_32P4_MODE) */


#if (CRC_32_MODE == CRC_RUNTIME_MODE) || (CRC_32P4_MODE == CRC_RUNTIME_MODE)

/*******************************************************************************
** Traceability     : [cover parentID={054774B5-6232-4ea8-9D92-20316A83975B}] **
**                                                                            **
** Syntax     : static uint32 Crc_lCommonCalculateCRC32Runtime                **
**      (                                                                     **
**        const uint8* const Crc_DataPtr,                                     **
**        const uint32 Crc_Length,                                            **
**        const uint32 Crc_StartValue32,                                      **
**        const uint32 Polynomial_32bit                                       **
**      )                                                                     **
**                                                                            **
** Description    :                                                           **
** - This function takes the value of input data pointerU, start value and    **
**   polynomialU, calculates the CRC value and returns the CRC                **
** - This function is local to the library module and is not for the user of  **
**   CRC Library                                                              **
**                                                                            **
** Service ID     : none                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : reentrant                                                 **
**                                                                            **
** Parameters (in)  : Crc_DataPtr  - Pointer to the start of the data block   **
**        Crc_Length - Length of the input data to be fetched                 **
**        Crc_StartValue32 -Start value for CRC Calculation                   **
**        Polynomial_32bit - 8bit polynomial to be used                       **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value   : uint32                                                    **
**                                                                            **
*******************************************************************************/
static uint32 Crc_lCommonCalculateCRC32Runtime(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint32 Crc_StartValue32,
  const uint32 Polynomial_32bit)
{
  uint32 LoopCounter;
  uint32 TempVal;
  uint32 StartValue32 = Crc_StartValue32;
  uint8 MessageBit;


  /* Cycle through each byte of the data provided. This loop would
   * run till the complete CRC is computed. Yes, this is a blocking call,
   * but that's the best way possible with the interfaces
   * defined by AUTOSAR. */
  /* [cover parentID={DF9DB996-BB3A-4e96-AE40-E99B3CB2626E}]
  Do an XOR division on the binary data to calculate the CRC.
  [/cover] */
  for (LoopCounter = CRC_ZERO_U;
       LoopCounter < Crc_Length; LoopCounter++)
  {
    /* [cover parentID={74959112-FD49-4162-9522-2D40833D2893}]
    Get the reflection of input data
    [/cover] */
    /* The input data needs to be 'reflected'. */
    TempVal = Crc_lReflectCRC32((uint32)Crc_DataPtr[LoopCounter],
                                CRC_BITCNT_EIGHT);

    /* Shift the 8 bit data to the MSB of the 32 bit variable */
    StartValue32 ^=  TempVal << (CRC_CRC32_SIZE - CRC_BYTELENGTH_U);

    /* [cover parentID={55332D17-801D-41e6-A211-5ADE0259A1CC}]
    Do the division bit wise
    [/cover] */
    /* Cycle through each bit of the data */
    for( MessageBit = CRC_BYTELENGTH_U;
         MessageBit > CRC_ZERO_U; MessageBit--)
    {
      /* [cover parentID={B14AB436-B240-4fcf-BCA8-E508A3AAA5C8}]
      Is the MSB bit 1 ?
      [/cover] */
      /* Check if the MSB is set */
      if((StartValue32 & CRC_CRC32_MSB) == CRC_CRC32_MSB)
      {
        /* [cover parentID={09C06B03-288E-4583-BE94-6EC9BDF3BCAA}]
        Left shift Start Value once and XOR with the Polynomial
        [/cover] */
        /* If MSB is 1 then left shift and X-OR with polynomial*/
        StartValue32 =
          (StartValue32 << CRC_ONE_U) ^ Polynomial_32bit;
      }
      else
      { /* [cover parentID={026614BC-6CD7-4373-844C-4187B4582C5A}]
        Left shift Start Value once
        [/cover] */
        /* If MSB is 0 then left shift and skip the XOR operation */
        StartValue32 = (StartValue32 << CRC_ONE_U);
      }

    }

  }
  /* [cover parentID={69B4C9BE-CCAA-4729-BEFA-31C45525ADC0}]
  Reflect the output
  [/cover] */
  /* The output data also should be reflected */
  StartValue32 =
    Crc_lReflectCRC32(StartValue32, CRC_BITCNT_THIRTYTWO);


  return StartValue32;
}

#endif
/* ##if (CRC_32_MODE == CRC_RUNTIME_MODE) ||
                 (CRC_32P4_MODE == CRC_RUNTIME_MODE) */


#if  CRC_32_MODE == CRC_RUNTIME_MODE
/******************************************************************************
** Traceability     : [cover parentID={BA60DB95-AD93-42f8-9E67-D700A277C087}]**
**                                                                           **
** Syntax     : static uint32 Crc_lCalculateCRC32Runtime                     **
**      (                                                                    **
**        const uint8* const Crc_DataPtr,                                    **
**        const uint32 Crc_Length,                                           **
**        const uint32 Crc_StartValue32,                                     **
**        const boolean Crc_IsFirstCall                                      **
**      )                                                                    **
**                                                                           **
**                                                                           **
** Description    :                                                          **
** - This function takes the value of input data pointer, start value and    **
**   polynomial, calculates the CRC value and returns the CRC xored with     **
**   XOR value                                                               **
** - This function is local to the library module and is not for the user of **
**   CRC Library                                                             **
**                                                                           **
** Service ID     : none                                                     **
**                                                                           **
** Sync/Async     : Synchronous                                              **
**                                                                           **
** Reentrancy     : reentrant                                                **
**                                                                           **
** Parameters (in)  : Crc_DataPtr  - Pointer to the start of the datablock   **
**        Crc_Length - Length of the input data to be fetched                **
**        Crc_StartValue32 -Start value for CRC Calculation                  **
**        Crc_IsFirstCall -Boolean to decide the start value                 **
**          *                                                                **
** Parameters (out) : none                                                   **
**                                                                           **
** Return value   : uint32                                                   **
**                                                                           **
******************************************************************************/
static uint32 Crc_lCalculateCRC32Runtime( const uint8* const Crc_DataPtr,
    const uint32 Crc_Length, const uint32 Crc_StartValue32,
    const boolean Crc_IsFirstCall)
{
  /* code for crc 32 runtime calculaion with 0x04C11DB7 polynomial*/
  uint32 StartValue32 = Crc_StartValue32;

  /* [cover parentID={0507DFC3-C67C-4d01-A559-6F1087AA0BDF}]
  Is this first call?
  [/cover] */
  /* if it is first call assign initial value to the start value */
  if(Crc_IsFirstCall == (boolean)TRUE)
  {
    /* [cover parentID={E763EBDC-DA69-4659-92A8-A16CD840A06A}]
    Set Start Value to Initial value for 32 bit CRC
    [/cover] */
    /* First call, assign the initial value needed. */
    StartValue32 = CRC_INITIAL_VALUE32;

  }
  else
  {
    /* [cover parentID={CF5DE952-4449-43d5-AFED-F2580E1E614D}]
    XOR Start Value with XOR Value for the 32 bit CRC
    [/cover] */
    /* Not a first call. So, take the start value, xor with the needed
     * value and proceed. */
    StartValue32 = StartValue32 ^ CRC_CRC32_XOR_VALUE;

    /* Reverse the data bits in the start value. This is as per the
    * specification of the CRC */
    /* [cover parentID={8D8A9D99-22AB-40b4-B0CC-65E04C810579}]
    Reflect the Start Value
    [/cover] */
    StartValue32 =
      Crc_lReflectCRC32(StartValue32, CRC_BITCNT_THIRTYTWO);

  }
  /* [cover parentID={421BF97D-5899-4468-B910-52B566855203}]
  Calculate 32  bit CRC
  [/cover] */
  StartValue32 = Crc_lCommonCalculateCRC32Runtime( Crc_DataPtr,
                 Crc_Length, StartValue32, CRC_CRC32_POLYNOMIAL );

  /* The output data should be XORed with the needed value */
  StartValue32 = CRC_CRC32_XOR_VALUE ^ StartValue32;


  return StartValue32;
}

#elif  (CRC_32_MODE == CRC_TABLE_MODE)
/*******************************************************************************
** Traceability     : [cover parentID={5B35DDC5-C351-402c-871D-D4897F3931B4}] **
**                                                                            **
** Syntax     : static uint32 Crc_lCalculateCRC32Table                        **
**      (                                                                     **
**        const uint8* const Crc_DataPtr,                                     **
**        const uint32 Crc_Length,                                            **
**        const uint32 Crc_StartValue32,                                      **
**        const boolean Crc_IsFirstCall                                       **
**      )                                                                     **
**                                                                            **
**                                                                            **
** Description    :                                                           **
** - This function takes the value of input data pointer, start value and     **
**   polynomial, calculates the crc taking the precomputed                    **
**    and reversed xor value  and returns the CRC xored with XOR value        **
** - This function is local to the library module and is not for the user of  **
**   CRC Library                                                              **
**                                                                            **
** Service ID     : none                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : reentrant                                                 **
**                                                                            **
** Parameters (in)  : Crc_DataPtr  - Pointer to the start of the datablock    **
**        Crc_Length - Length of the input data to be fetched                 **
**        Crc_StartValue32 -Start value for CRC Calculation                   **
**        Crc_IsFirstCall -Boolean to decide the start value                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value   : uint32                                                    **
**                                                                            **
**                                                                            **
*******************************************************************************/
static uint32 Crc_lCalculateCRC32Table( const uint8* const Crc_DataPtr,
                                        const uint32 Crc_Length, 
                                        const uint32 Crc_StartValue32,
                                        const boolean Crc_IsFirstCall)
{
  /* code for crc 32 table based calculaion with 0x04C11DB7 polynomial*/
  uint32 LoopCounter ;
  uint32 Temp32;
  uint32 StartValue32 = Crc_StartValue32;

  /* [cover parentID={4605ABE7-F96A-435b-8A83-87652D2DFEBE}]
  Check if this is first call
  [/cover] */
  if(Crc_IsFirstCall == (boolean)TRUE)
  {
    /* [cover parentID={F663866E-F494-4d8b-9B58-83203D348672}]
    XOR Start Value with XOR Value for the 32 bit CRC
    [/cover] */
    StartValue32 = CRC_INITIAL_VALUE32;
  }
  else
  {
    /* [cover parentID={83A2F306-5599-4392-AC3A-80C8A15E93D4}]
    Set Start Value to Initial value for 32 bit CRC
    [/cover] */
    StartValue32 = StartValue32 ^ CRC_CRC32_XOR_VALUE;
    /* [cover parentID={6E231011-9390-41fe-9FB0-43B5F29217EB}]
    Reflect the Start Value
    [/cover] */
    StartValue32 = Crc_lReflectCRC32(StartValue32,
                                     CRC_BITCNT_THIRTYTWO);
  }

  /* ********************************************************************
   * Table method - what's this?
   * Now, the runtime method is a slow and inefficient method to compute
   * the CRC, obviously. Parsing each bit from the message to compute the
   * CRC can be a nightmare when the volume of the data becomes bigger.
   * The lookup table method aims to accelerate the computation by
   * providing lookup values for the possible data combinations. This
   * would eliminate all the bit handling stuff and we can start thinking
   * on the byte level, instead of bits!
   * ******************************************************************** */

  /*Extract each byte from the message, fetch the value from lookup
  table and XOR with the crc value*/
  /* [cover parentID={9EDB6753-3911-44f2-8137-C3F3CE308A84}]
  Parse each byte from the message
  [/cover] */
  for(LoopCounter = CRC_ZERO_U; LoopCounter < Crc_Length;
      LoopCounter++)
  {

    /* [cover parentID={BD1043EC-28D0-4e58-A67E-167716A411A2}]
    XOR the Byte with Start Value, fetch the value from lookup table using
    the XOR result, XOR the fetched value with Start Value shifted 8 times
    right and store in Start Value
    [/cover] */
    Temp32 = Crc_lReflectCRC32((uint32)Crc_DataPtr[LoopCounter],
                               CRC_BITCNT_EIGHT);

    Temp32 = ((uint32) ((uint32)StartValue32 >> CRC_SHIFT_TWENTYFOUR) ^
              Temp32) & CRC_U32LSB_MASK;

    StartValue32 =
      (uint32)((uint32)StartValue32 << CRC_BYTELENGTH_U) ^
      Crc_Table32[Temp32];

  }
  /* [cover parentID={1B3C86DA-501D-4c1a-A05F-57726AA1BF43}]
  Reflect the output
  [/cover] */
  StartValue32 = Crc_lReflectCRC32(StartValue32,
                                   CRC_BITCNT_THIRTYTWO);

  StartValue32 = CRC_CRC32_XOR_VALUE ^ StartValue32;


  return StartValue32;
}

#elif  (CRC_32_MODE == CRC_HARDWARE_MODE)
/*******************************************************************************
** Traceability     : [cover parentID={564FEFDC-DC12-4a2e-AAB8-8C0BCADFF866}] **
**                                                                            **
** Syntax     : static uint32 Crc_lCalculateCRC32Hardware                     **
**      (                                                                     **
**        const uint8* const Crc_DataPtr,                                     **
**        const uint32 Crc_Length,                                            **
**        const uint32 Crc_StartValue32,                                      **
**        const boolean Crc_IsFirstCall                                       **
**      )                                                                     **
**                                                                            **
**                                                                            **
** Description    :                                                           **
** - This function takes the value of input data pointer, start value and     **
**   polynomial, calculates the crc using the hardware and returns the CRC    **
**   reversed and xored with the XOR_VALUE                                    **
** - This function is local to the library module and is not for the user of  **
**   CRC Library                                                              **
**                                                                            **
** Service ID     : none                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters (in)  : Crc_DataPtr  - Pointer to the start of the datablock    **
**        Crc_Length - Length of the input data to be fetched                 **
**        Crc_StartValue32 -Start value for CRC Calculation                   **
**        Crc_IsFirstCall -Boolean to decide the start value                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value   : uint32                                                    **
**                                                                            **
**                                                                            **
*******************************************************************************/
static uint32 Crc_lCalculateCRC32Hardware( const uint8* const Crc_DataPtr,
    const uint32 Crc_Length, const uint32 Crc_StartValue32,
    const boolean Crc_IsFirstCall)
{
  uint32 LoopCounter;
  volatile uint16 TimeOut;
  volatile uint32 tempVal;
  uint32 Reflectedword;
  uint32 StartValue32 = Crc_StartValue32;
  uint8 ChannelNumber;

  Ifx_FCE *FCERegBaseAddress = &MODULE_FCE;
  TimeOut = CRC_TIMEOUT_VAL;
  /* [cover parentID={8548CF69-4E51-4754-9B6E-AA172CED2EB6}]
  [/cover] */
  /* [cover parentID={05EC355F-BEC9-41ce-92A3-D6AD1FF0DFEE}]
  [/cover] */
  /* [cover parentID={08124EE7-94CD-45f5-AE10-C9BFD9C1D931}]
  Critical Section
  [/cover] */
  SchM_Enter_Crc_CriticalSection();
  /* The critical section starts here. The interrupts needs to be disabled */

  Mcal_GetSpinlock(&Crc_SpinLockAddress, CRC_SPINLOCKTIMEOUT_VAL);
  /* MISRA2012_RULE_13_5_JUSTIFICATION: And operator required for timeout and
  channel busy check  */
  /* [cover parentID={B9BF57EA-7DAE-4eff-8E49-2A399FAD4962}]
  Wait here untill any one channel is free or timeout expires
  [/cover] */
  while((Crc_ChannelFlag == 0xFFu) && (TimeOut != CRC_ZERO_U))
  {
    /* [cover parentID={B9BF57EA-7DAE-4eff-8E49-2A399FAD4962}]
    Wait here untill any one channel is free or timeout expires
    [/cover] */
    TimeOut -- ;        /* Wait for a free channel untill TimeOut expires */
  }
  /* [cover parentID={2747D165-C347-47e4-ACD0-42552BBBA868}]
  If timeout expires
  [/cover] */
  if(TimeOut != CRC_ZERO_U)
  {
    /* [cover parentID={79197AAC-9F50-4bc6-ADA5-8AA4AA849945}]
     Loop across all channels to check for a free channel
    [/cover] */
    /* Loop across all channels to check for a free channel */
    for(ChannelNumber = CRC_ZERO_U; ChannelNumber < CRC_MAXCHANNELS_U;
        ChannelNumber++)
    {
      /* [cover parentID={5E55F015-74A6-48a6-B636-BFB3BF17862B}]
      block the free channel
      [/cover] */
      if((Crc_ChannelFlag & (CRC_ONE_U << ChannelNumber)) != \
          (CRC_ONE_U << ChannelNumber))
      {
        /*Set this bit busy if you find it free and exit the for loop */
        /* [cover parentID={6555AC91-7A7C-422d-8535-0557079AEF66}]
        block the channel
        [/cover] */
        Crc_ChannelFlag |= (CRC_ONE_U << ChannelNumber);
        break;
      }

    }
    Mcal_ReleaseSpinlock(&Crc_SpinLockAddress);
    SchM_Exit_Crc_CriticalSection();
    /* The critical section ends here. The interrupts would be enabled
     * henceforth. */

    /* The FCE needs to be enabled */
    /* MISRA2012_RULE_11_8_JUSTIFICATION:
       MISRA2012_RULE_11_3_JUSTIFICATION: casting of register address to
       corresponding structure pointer   */
    CRC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG \
    ((uint32*)&FCERegBaseAddress->CLC.U, CRC_CLC_INITVAL);

    /* Perform the init for the CFG registers */
    /* MISRA2012_RULE_11_8_JUSTIFICATION:
       MISRA2012_RULE_11_3_JUSTIFICATION: casting of register address to
       corresponding structure pointer   */
    /* MISRA2012_RULE_18_1_JUSTIFICATION: Out-of-bound access of pointer
           is taken care. ChannelNumber will not exceed 7   */
    CRC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG((uint32*) \
        &FCERegBaseAddress->IN[ChannelNumber].CFG.U, CRC32_CFGREG_INITVAL);


    /* Configure CRC register*/
    /* [cover parentID={63C88ABF-5B39-4fbd-BD07-26E67C27FDB3}]
    Is first Call ?
    [/cover] */
    if (Crc_IsFirstCall == (boolean)TRUE)
    {

      /* [cover parentID={0498E9E7-43C3-41ca-8EB2-AB839A34517E}]
      Load the CRC register with Initial CRC Value
      [/cover] */
      /* MISRA2012_RULE_18_1_JUSTIFICATION: Out-of-bound access of pointer
         is taken care. ChannelNumber will not exceed 7 */
      FCERegBaseAddress->IN[ChannelNumber].CRC.U = CRC_INITIAL_VALUE32;

    }
    else
    {

      /* [cover parentID={91288659-B28B-41a7-9629-570F440739E4}]
      XOR the Start Value and Load this value to the  CRC register
      [/cover] */
      StartValue32 = StartValue32 ^ CRC_CRC32_XOR_VALUE;
      /* [cover parentID={B417C472-6997-4504-A534-2898193FB4AE}]
      Do a 32 bit reflection of the XORed value
      [/cover] */
      Reflectedword = (uint32)(Crc_lReflectCRC32(StartValue32,
                               CRC_BITCNT_THIRTYTWO));

      /* MISRA2012_RULE_18_1_JUSTIFICATION: Out-of-bound access of pointer
         is taken care. ChannelNumber will not exceed 7 */
      FCERegBaseAddress->IN[ChannelNumber].CRC.U = Reflectedword;

    }

    /* [cover parentID={8EE58336-1299-478c-ABC9-897843699972}]
    Feed data to IR register
    [/cover] */
    /* input in IR register */
    for (LoopCounter = CRC_ZERO_U; LoopCounter < Crc_Length;
         LoopCounter += CRC_FOUR_U)
    {
      /* [cover parentID={B0245A10-185F-428d-AC01-AA244A4527E6}]
      If 1,2 or 3 bytes are remaining
      [/cover] */
      if((LoopCounter / CRC_FOUR_U) == (Crc_Length / CRC_FOUR_U))
      {
        /* [cover parentID={8E5FC2BF-D8DB-47b8-B01E-2E48D96902D8}]
        Conditional node
        [/cover] */
        tempVal = CRC_ZERO_U;
        /* [cover parentID={9A2B14D8-5FAB-41c2-A74A-04CBBD0A1A91}]
        If only 1 byte remains
        [/cover] */
        if((Crc_Length % CRC_FOUR_U) == CRC_ONE_U)
        {
          /*[cover parentID={A0489BF3-61DB-4f63-A93F-313811D42A17}]
          Shift the byte to MSB of the 32 bit word
          [/cover] */
          tempVal = (uint32)((uint32)Crc_DataPtr[LoopCounter] <<
                             CRC_SHIFT_TWENTYFOUR);
        }
        /* [cover parentID={753E6281-A092-4292-A1F8-E3B57A0C1F9F}]
        If 2 bytes remain
        [/cover] */
        else if((Crc_Length % CRC_FOUR_U) == CRC_TWO_U)
        {
          /* [cover parentID={CB340B93-3F55-42d4-82F6-F318B09C822F}]
          Shift the bytes left 24 and 16 times respectively in to
          the 32 bit word
          [/cover] */
          tempVal = (uint32)((uint32)Crc_DataPtr[LoopCounter] <<
                             CRC_SHIFT_TWENTYFOUR);

          tempVal = (uint32)(tempVal |
                    (uint32)((uint32)Crc_DataPtr[LoopCounter + CRC_ONE_U] <<
                    CRC_SIXTEEN_U));
        }
        /* [cover parentID={FB4B0843-2E91-414d-9A7F-04366EB0DB58}]
        If 3 bytes remain
        [/cover] */
        else
        {
          /* [cover parentID={029501DA-48AA-4fe0-BED8-5D83D9D3F587}]
          Shift the bytes one after the other 24 16 and 8 times in
          to the 32 bit word
          [/cover] */
          tempVal = (uint32)((uint32)Crc_DataPtr[LoopCounter] <<
                             CRC_SHIFT_TWENTYFOUR);

          tempVal = (uint32)(tempVal |
                    (uint32)((uint32)Crc_DataPtr[LoopCounter + CRC_ONE_U] <<
                    CRC_SIXTEEN_U));

          tempVal = (uint32)(tempVal |
                    (uint32)((uint32)Crc_DataPtr[LoopCounter + CRC_TWO_U] <<
                    CRC_BYTELENGTH_U));
        }

      }
      else
      {
        /* [cover parentID={F80AB54B-FB32-4b99-B7FF-E3E8CFED3899}]
        Store the 4 bytes in to one 32 bit word
        [/cover] */
        tempVal = (uint32)((uint32)Crc_DataPtr[LoopCounter + CRC_ZERO_U]
                           << CRC_SHIFT_TWENTYFOUR) |
                  (uint32)((uint32)Crc_DataPtr[LoopCounter + CRC_ONE_U]
                           << CRC_SIXTEEN_U) |
                  (uint32)((uint32)Crc_DataPtr[LoopCounter + CRC_TWO_U]
                           << CRC_BYTELENGTH_U) |
                  (Crc_DataPtr[LoopCounter + CRC_THREE_U]);

      }

      /* MISRA2012_RULE_18_1_JUSTIFICATION: Out-of-bound access of pointer
         is taken care. ChannelNumber will not exceed 7 */
      FCERegBaseAddress->IN[ChannelNumber].IR.U = tempVal;

    }

    /* MISRA2012_RULE_18_1_JUSTIFICATION: Out-of-bound access of pointer
       is taken care. ChannelNumber will not exceed 7 */
    StartValue32 = FCERegBaseAddress->IN[ChannelNumber].RES.U;
    /* [cover parentID={2863AC01-F36B-484d-A393-703CFA6712C8}]
    Set the blocked channel free
    [/cover] */
    Mcal_SetBitAtomic(&Crc_ChannelFlag, ChannelNumber, 1, CRC_ZERO_U);
  }
  else
  {
    /* [cover parentID={1407AEE8-D3EB-42e6-8F4F-6594F332E7BC}]
    Release spin lock
    [/cover] */
    Mcal_ReleaseSpinlock(&Crc_SpinLockAddress);
    SchM_Exit_Crc_CriticalSection();
    /* The critical section ends here. The interrupts would be enabled
     * henceforth. */

    /* [cover parentID={CEF240BB-371B-49e9-9BB9-9649079795BB}]
    If safety check is enabled
    [/cover] */
    #if (CRC_SAFETYENABLE == STD_ON)
    /* [cover parentID={EB23D52B-065D-4f7a-A091-6AF2DE862296}]
    Report Mcal Safety error in case of timeout
    [/cover] */
    Mcal_ReportSafetyError(CRC_MODULE_ID, CRC_INSTANCE_ID,
                           CRC_SID_CALCULATE_CRC32, CRC_E_CHANNEL_TIMEOUT);
    StartValue32 = (uint32)CRC_32_CONFIGERROR_VAL;
    #endif
  }

  /* set end init protection once FCE is disabled */
  return StartValue32;
}


#endif
/* #if  CRC_32_MODE == CRC_HARDWARE_MODE */



#if  CRC_32P4_MODE == CRC_RUNTIME_MODE
/*******************************************************************************
** Traceability     : [cover parentID={4DB33E44-4AF4-4329-BB36-823122E64D58}] **
**                                                                            **
** Syntax     : static uint32 Crc_lCalculateCRC32P4Runtime                    **
**      (                                                                     **
**        const uint8* const Crc_DataPtr,                                     **
**        const uint32 Crc_Length,                                            **
**        const uint32 Crc_StartValue32,                                      **
**        const boolean Crc_IsFirstCall                                       **
**      )                                                                     **
**                                                                            **
** Description    :                                                           **
** - This function takes the value of input data pointer, start value and     **
**   polynomial, calculates the CRC value and returns the CRC xored with      **
**   XOR value                                                                **
** - This function is local to the library module and is not for the user of  **
**   CRC Library                                                              **
**                                                                            **
**                                                                            **
** Service ID     : none                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : reentrant                                                 **
**                                                                            **
** Parameters (in)  : Crc_DataPtr  - Pointer to the start of the datablock    **
**        Crc_Length - Length of the input data to be fetched                 **
**        Crc_StartValue32 -Start value for CRC Calculation                   **
**        Crc_IsFirstCall -Boolean to decide the start value                  **
**          *                                                                 **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value   : uint32                                                    **
**                                                                            **
*******************************************************************************/
static uint32 Crc_lCalculateCRC32P4Runtime( const uint8* const Crc_DataPtr,
    const uint32 Crc_Length, const uint32 Crc_StartValue32,
    const boolean Crc_IsFirstCall)
{
  /* code for CRC 32P4 runtime calculation with 0xF4ACFB13 polynomial*/
  uint32 StartValue32P4 = Crc_StartValue32;
  /* [cover parentID={2481D997-81D8-48ff-8DD4-1A68B4A24EEC}]
  Is this first call?
  [/cover] */
  /* if it is first call assign initial value to the start value */
  if(Crc_IsFirstCall == (boolean)TRUE)
  {
    /* [cover parentID={CD2B992E-EBE6-40cc-AABD-D43B6170BDAF}]
    Set Start Value to Initial value for 32 bit P4 CRC
    [/cover] */
    /* First call, assign the initial value needed. */
    StartValue32P4 = CRC_INITIAL_VALUE32P4;

  }
  else
  {
    /* [cover parentID={4A11219C-2EE2-4f67-B680-7A4830DAE9BD}]
    XOR Start Value with XOR Value for the 32 bit P4 CRC
    [/cover] */
    /* Not a first call. So, take the start value, XOR with the needed
     * value and proceed. */
    StartValue32P4 = StartValue32P4 ^ CRC_CRC32P4_XOR_VALUE;

    /* Reverse the data bits in the start value. This is as per the
    * specification of the CRC32P4 */
    /* [cover parentID={0E79849A-5827-477d-A225-2071C0D71847}]
    Reflect the Start Value
    [/cover] */
    StartValue32P4 = Crc_lReflectCRC32(StartValue32P4,
                                       CRC_BITCNT_THIRTYTWO);

  }

  /* [cover parentID={C26BF489-19AA-4a42-AF13-BBAAC82F28EC}]
  Calculate 32  bit P4 CRC
  [/cover] */
  StartValue32P4 = Crc_lCommonCalculateCRC32Runtime( Crc_DataPtr,
                   Crc_Length, StartValue32P4, CRC_CRC32P4_POLYNOMIAL );

  /* The output data should be XORed with the needed value */
  StartValue32P4 = CRC_CRC32P4_XOR_VALUE ^ StartValue32P4;


  return StartValue32P4;
}
#elif  (CRC_32P4_MODE == CRC_TABLE_MODE)
/*******************************************************************************
** Traceability     : [cover parentID={279A74DC-64A6-4225-AF8E-1BB24519E0A3}] **
**                                                                            **
** Syntax     : static uint32 Crc_lCalculateCRC32P4Table                      **
**      (                                                                     **
**        const uint8* const Crc_DataPtr,                                     **
**        const uint32 Crc_Length,                                            **
**        const uint32 Crc_StartValue32,                                      **
**        const boolean Crc_IsFirstCall                                       **
**      )                                                                     **
**                                                                            **
** Description    :                                                           **
** - This function takes the value of input data pointer, start value and     **
**   polynomial, calculates the crc taking the precomputed                    **
**    and reversed xor value  and returns the CRC xored with XOR value        **
** - This function is local to the library module and is not for the user of  **
**   CRC Library                                                              **
**                                                                            **
**                                                                            **
** Service ID     : none                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : reentrant                                                 **
**                                                                            **
** Parameters (in)  : Crc_DataPtr  - Pointer to the start of the datablock    **
**        Crc_Length - Length of the input data to be fetched                 **
**        Crc_StartValue32 -Start value for CRC Calculation                   **
**        Crc_IsFirstCall -Boolean to decide the start value                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value   : uint32                                                    **
**                                                                            **
*******************************************************************************/
static uint32 Crc_lCalculateCRC32P4Table( const uint8* const Crc_DataPtr,
    const uint32 Crc_Length, const uint32 Crc_StartValue32,
    const boolean Crc_IsFirstCall)
{
  /* code for crc 32 table based calculation with 0x04C11DB7 polynomial*/
  uint32 LoopCounter ;
  uint32 Temp32;
  uint32 StartValue32P4 = Crc_StartValue32;

  /* [cover parentID={D58DA465-D27F-4111-9D6F-EBED5D2AE53D}]
  Check if this is first call
  [/cover] */
  if(Crc_IsFirstCall == (boolean)TRUE)
  {
    /* [cover parentID={41B50AF3-A853-48c7-A002-CF5C2DF20AB2}]
    Set Start Value to Initial value for 32 bit P4 CRC
    [/cover] */
    StartValue32P4 = CRC_INITIAL_VALUE32P4;
  }
  else
  {
    /* [cover parentID={254DD0C6-FCAE-4469-89C5-307DFEC62A38}]
    XOR Start Value with XOR Value for the 32 bit P4 CRC
    [/cover] */
    StartValue32P4 = StartValue32P4 ^ CRC_CRC32P4_XOR_VALUE;
    /* [cover parentID={3EF8C922-AB92-4729-A61B-547C1233BE73}]
    Reflect the Start Value
    [/cover] */
    StartValue32P4 = Crc_lReflectCRC32(StartValue32P4,
                                       CRC_BITCNT_THIRTYTWO);
  }

  /* ********************************************************************
   * Table method - what's this?
   * Now, the runtime method is a slow and inefficient method to compute
   * the CRC, obviously. Parsing each bit from the message to compute the
   * CRC can be a nightmare when the volume of the data becomes bigger.
   * The lookup table method aims to accelerate the computation by
   * providing lookup values for the possible data combinations. This
   * would eliminate all the bit handling stuff and we can start thinking
   * on the byte level, instead of bits!
   * ******************************************************************** */

  /*Extract each byte from the message, fetch the value from lookup
  table and XOR with the crc value*/
  /* [cover parentID={B884C8A2-41A9-4a10-880A-E49B17133217}]
  Parse each byte from the message
  [/cover] */
  for(LoopCounter = CRC_ZERO_U; LoopCounter < Crc_Length;
      LoopCounter++)
  {
    /* [cover parentID={F20E2DA5-3817-46cd-99E4-AAB10D34BB80}]
    XOR the Byte with Start Value, fetch the value from lookup table using
    the XOR result, XOR the fetched value with Start Value shifted 8 times
    right and store in Start Value
    [/cover] */
    Temp32 = Crc_lReflectCRC32((uint32)Crc_DataPtr[LoopCounter],
                               CRC_BITCNT_EIGHT);

    Temp32 =
      ((uint32) ((uint32)StartValue32P4 >> CRC_SHIFT_TWENTYFOUR) ^
       Temp32) & CRC_U32LSB_MASK;

    StartValue32P4 =
      (uint32)((uint32)StartValue32P4 << CRC_BYTELENGTH_U) ^
      Crc_Table32P4[Temp32];

  }
  /* [cover parentID={19832151-E3D2-45d6-AC90-1DC450F47DDB}]
  Reflect the output
  [/cover] */
  StartValue32P4 = Crc_lReflectCRC32(StartValue32P4,
                                     CRC_BITCNT_THIRTYTWO);

  StartValue32P4 = CRC_CRC32P4_XOR_VALUE ^ StartValue32P4;


  return StartValue32P4;
}

#elif  (CRC_32P4_MODE == CRC_HARDWARE_MODE)
/*******************************************************************************
** Traceability     : [cover parentID={8C110756-9047-4d19-B38B-A959B792C377}] **
**                                                                            **
** Syntax     : static uint32 Crc_lCalculateCRC32P4Hardware                   **
**      (                                                                     **
**        const uint8* const Crc_DataPtr,                                     **
**        const uint32 Crc_Length,                                            **
**        const uint32 Crc_StartValue32,                                      **
**        const boolean Crc_IsFirstCall                                       **
**      )                                                                     **
**                                                                            **
**                                                                            **
** Description    :                                                           **
** - This function takes the value of input data pointer, start value and     **
**   polynomial, calculates the crc using the hardware and returns the CRC    **
**   reversed and xored with the XOR_VALUE                                    **
** - This function is local to the library module and is not for the user of  **
**   CRC Library                                                              **
**                                                                            **
** Service ID     : none                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters (in)  : Crc_DataPtr  - Pointer to the start of the datablock    **
**        Crc_Length - Length of the input data to be fetched                 **
**        Crc_StartValue32 -Start value for CRC Calculation                   **
**        Crc_IsFirstCall -Boolean to decide the start value                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value   : uint32                                                    **
**                                                                            **
**                                                                            **
*******************************************************************************/
static uint32 Crc_lCalculateCRC32P4Hardware( const uint8* const Crc_DataPtr,
    const uint32 Crc_Length, const uint32 Crc_StartValue32,
    const boolean Crc_IsFirstCall)
{
  uint32 LoopCounter;
  volatile uint16 TimeOut;
  volatile uint32 tempVal;
  uint32 Reflectedword;
  uint32 StartValue32P4 = Crc_StartValue32;
  uint8 ChannelNumber;

  Ifx_FCE *FCERegBaseAddress = &MODULE_FCE;
  TimeOut = CRC_TIMEOUT_VAL;
  /* [cover parentID={8548CF69-4E51-4754-9B6E-AA172CED2EB6}]
  [/cover] */
  /* [cover parentID={05EC355F-BEC9-41ce-92A3-D6AD1FF0DFEE}]
  [/cover] */
  /* [cover parentID={F0E95E81-5251-4e2a-BF7A-4EF01AD83E1A}]
  Critical Section
  [/cover] */
  SchM_Enter_Crc_CriticalSection();
  /* The critical section starts here. The interrupts needs to be disabled */

  Mcal_GetSpinlock(&Crc_SpinLockAddress, CRC_SPINLOCKTIMEOUT_VAL);
  /* MISRA2012_RULE_13_5_JUSTIFICATION: And operator required for timeout and
  channel busy check  */
  /* [cover parentID={13FE1329-7D74-4c96-85B2-528EDD7C9987}]
  Wait here untill any one channel is free or timeout expires
  [/cover] */
  while((Crc_ChannelFlag == 0xFFu) && (TimeOut != CRC_ZERO_U))
  {
    /* [cover parentID={13FE1329-7D74-4c96-85B2-528EDD7C9987}]
    [/cover] */
    TimeOut -- ;        /* Wait for a free channel untill TimeOut expires */
  }
  /* [cover parentID={445FB1D7-29AE-4a6b-98DD-99D625985674}]
  If timeout expires
  [/cover] */
  if(TimeOut != CRC_ZERO_U)
  {
    /* [cover parentID={0D2B5646-7105-4544-B6A8-405C699B3001}]
     Loop across all channels to check for a free channel
    [/cover] */
    /* Loop across all channels to check for a free channel */
    for(ChannelNumber = CRC_ZERO_U; ChannelNumber < CRC_MAXCHANNELS_U;
        ChannelNumber++)
    {
      /* [cover parentID={7BCF3E2E-4633-4cb4-B261-D13C04A9AAF6}]
      block the free channel
      [/cover] */
      if((Crc_ChannelFlag & (CRC_ONE_U << ChannelNumber)) != \
          (CRC_ONE_U << ChannelNumber))
      {
        /* [cover parentID={CEA73B0C-E344-4819-B158-4C10121C18BE}]
        block the channel
        [/cover] */
        /*Set this bit busy if you find it free and exit the for loop */
        Crc_ChannelFlag |= (CRC_ONE_U << ChannelNumber);
        break;
      }
    }
    Mcal_ReleaseSpinlock(&Crc_SpinLockAddress);
    SchM_Exit_Crc_CriticalSection();
    /* The critical section ends here. The interrupts would be enabled
     * henceforth. */

    /* The FCE needs to be enabled */
    /* MISRA2012_RULE_11_8_JUSTIFICATION:
       MISRA2012_RULE_11_3_JUSTIFICATION: casting of register address to
       corresponding structure pointer   */
    CRC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG \
    ((uint32*)&FCERegBaseAddress->CLC.U, CRC_CLC_INITVAL);

    /* Perform the init for the CFG registers */
    /* MISRA2012_RULE_11_8_JUSTIFICATION:
       MISRA2012_RULE_11_3_JUSTIFICATION: casting of register address to
       corresponding structure pointer   */
    /* MISRA2012_RULE_18_1_JUSTIFICATION: Out-of-bound access of pointer
       is taken care. ChannelNumber will not exceed 7 */
    CRC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG((uint32*) \
        &FCERegBaseAddress->IN[ChannelNumber].CFG.U, CRC32P4_CFGREG_INITVAL);

    /* [cover parentID={905BFC56-11FD-4bd5-9C0D-3B2C93751BE3}]
    Is first Call ?
    [/cover] */
    /* Configure CRC register*/
    if (Crc_IsFirstCall == (boolean)TRUE)
    {
      /* [cover parentID={07371EB4-21E3-41b1-9893-20AADAAB507A}]
      Load the CRC register with Initial CRC Value
      [/cover] */
      /* MISRA2012_RULE_18_1_JUSTIFICATION: Out-of-bound access of pointer
         is taken care. ChannelNumber will not exceed 7 */
      FCERegBaseAddress->IN[ChannelNumber].CRC.U = CRC_INITIAL_VALUE32;

    }
    else
    {
      /* [cover parentID={4FD5D711-D709-4cb6-86EB-2EDD2AD50125}]
      XOR the Start Value and Load this value to the  CRC register
      [/cover] */
      StartValue32P4 = StartValue32P4 ^ CRC_CRC32P4_XOR_VALUE;
      /* [cover parentID={8C1AFDBF-3390-445e-BDD0-9E9A6B07D9BE}]
      Do a 32 bit reflection of the XORed value
      [/cover] */
      Reflectedword = (uint32)(Crc_lReflectCRC32(StartValue32P4,
                               CRC_BITCNT_THIRTYTWO));

      /* MISRA2012_RULE_18_1_JUSTIFICATION: Out-of-bound access of pointer
         is taken care. ChannelNumber will not exceed 7 */
      FCERegBaseAddress->IN[ChannelNumber].CRC.U = Reflectedword;

    }
    /* [cover parentID={62007533-9EAB-4de6-83DA-F2792C06377D}]
    Feed data to IR register
    [/cover] */
    /* input in IR register */
    for (LoopCounter = CRC_ZERO_U; LoopCounter < Crc_Length;
         LoopCounter += CRC_FOUR_U)
    {
      /* [cover parentID={612E2157-080D-4e96-BBB3-9AAA9B7C073C}]
      Conditional node
      [/cover] */
      if((LoopCounter / CRC_FOUR_U) == (Crc_Length / CRC_FOUR_U))
      {
        /* [cover parentID={9D751501-B0CD-4ca1-9944-A58239C9097A}]
        If 1,2 or 3 bytes are remaining
        [/cover] */
        tempVal = CRC_ZERO_U;

        if((Crc_Length % CRC_FOUR_U) == CRC_ONE_U)
        {
          /*[cover parentID={73B2B3CA-639D-4f08-966A-D3A227C04140}]
          Shift the byte to MSB of the 32 bit word
          [/cover] */
          tempVal = (uint32)((uint32)Crc_DataPtr[LoopCounter] <<
                             CRC_SHIFT_TWENTYFOUR);
        }

        else if((Crc_Length % CRC_FOUR_U) == CRC_TWO_U)
        {
          /*[cover parentID={8B7166C5-309E-4b04-9C2D-F5AA680D83FD}]
          Shift the bytes left 24 and 16 times respectively in to
          the 32 bit word
          [/cover] */
          tempVal = (uint32)((uint32)Crc_DataPtr[LoopCounter] <<
                             CRC_SHIFT_TWENTYFOUR);

          tempVal = (uint32)(tempVal |
                    (uint32)((uint32)Crc_DataPtr[LoopCounter + CRC_ONE_U] <<
                    CRC_SIXTEEN_U));
        }

        else
        {
          /* [cover parentID={6247B923-4A91-4f09-90D5-8E60A0098D91}]
          Shift the bytes one after the other 24 16 and 8 times in to
          the 32 bit word
          [/cover] */
          tempVal = (uint32)((uint32)Crc_DataPtr[LoopCounter] <<
                             CRC_SHIFT_TWENTYFOUR);

          tempVal = (uint32)(tempVal |
                    (uint32)((uint32)Crc_DataPtr[LoopCounter + CRC_ONE_U] <<
                    CRC_SIXTEEN_U));

          tempVal = (uint32)(tempVal |
                    (uint32)((uint32)Crc_DataPtr[LoopCounter + CRC_TWO_U] <<
                    CRC_BYTELENGTH_U));
        }

      }
      else
      {
        /* [cover parentID={0260A417-2105-4e86-97C2-6FD041A3F685}]
        Store the 4 bytes in to one 32 bit word
        [/cover] */
        tempVal = (uint32)((uint32)Crc_DataPtr[LoopCounter + CRC_ZERO_U]
                           << CRC_SHIFT_TWENTYFOUR) |
                  (uint32)((uint32)Crc_DataPtr[LoopCounter + CRC_ONE_U] <<
                           CRC_SIXTEEN_U) |
                  (uint32)((uint32)Crc_DataPtr[LoopCounter + CRC_TWO_U] <<
                           CRC_BYTELENGTH_U) |
                  (Crc_DataPtr[LoopCounter + CRC_THREE_U]);

      }

      /* MISRA2012_RULE_18_1_JUSTIFICATION: Out-of-bound access of pointer
         is taken care. ChannelNumber will not exceed 7 */
      FCERegBaseAddress->IN[ChannelNumber].IR.U = tempVal;

    }

    /* MISRA2012_RULE_18_1_JUSTIFICATION: Out-of-bound access of pointer
       is taken care. ChannelNumber will not exceed 7 */
    StartValue32P4 = FCERegBaseAddress->IN[ChannelNumber].RES.U;
    /* [cover parentID={3D963071-1F13-461b-AF22-44A910426B6E}]
    Set the blocked channel free
    [/cover] */
    Mcal_SetBitAtomic(&Crc_ChannelFlag, ChannelNumber, 1, CRC_ZERO_U);
  }
  else
  {
    /* [cover parentID={655F6158-8BFD-4434-9AD4-47F584EACB89}]
    Release spin lock
    [/cover] */
    Mcal_ReleaseSpinlock(&Crc_SpinLockAddress);
    SchM_Exit_Crc_CriticalSection();
    /* The critical section ends here. The interrupts would be enabled
     * henceforth. */

    /* [cover parentID={8C1AFDBF-3390-445e-BDD0-9E9A6B07D9BE}]
    [/cover] */
    #if (CRC_SAFETYENABLE == STD_ON)
    /* [cover parentID={F5504E03-495F-482c-8700-1D5C4BA8DB75}]
    Report Mcal Safety error in case of timeout
    [/cover] */
    Mcal_ReportSafetyError(CRC_MODULE_ID, CRC_INSTANCE_ID,
                           CRC_SID_CALCULATE_CRC32P4, CRC_E_CHANNEL_TIMEOUT);
    StartValue32P4 = (uint32)CRC_32P4_CONFIGERROR_VAL;
    #endif
  }

  return StartValue32P4;
}

#endif
/* #if  CRC_32P4_MODE == ** */


#define CRC_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"

