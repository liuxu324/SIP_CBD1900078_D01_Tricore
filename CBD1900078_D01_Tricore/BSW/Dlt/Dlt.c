/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Dlt.c
 *        \brief  Dlt source file
 *
 *      \details  Source file of the AUTOSAR Diagnostic Log and Trace, according to:
 *                AUTOSAR Diagnostic Log and Trace, AUTOSAR Release 4.0
 *
 *********************************************************************************************************************/

 /*********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 * 
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#define DLT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Dlt.h"
#include "Rte_Dlt.h"


#if (DLT_DEV_ERROR_REPORT == STD_ON)
# include "Det.h" /* Include Development Error Tracer */
#endif /* (DLT_DEV_ERROR_DETECT == STD_ON) */

#if defined (DLT_USE_COMLAYER_XCP) && (DLT_USE_COMLAYER_XCP == STD_ON) /* COV_DLT_FILTER_ASR_XCP */
# include "Xcp.h"
#endif /* (DLT_USE_COMLAYER_XCP) && (DLT_USE_COMLAYER_XCP == STD_ON) */

#if (DLT_USE_VERBOSE_MODE == STD_ON)
# include "VStdLib.h"            /* for VStdMemCpy */
#endif /* (DLT_USE_VERBOSE_MODE == STD_ON) */

/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */
/*lint -e522 */ /* Suppress ID522 because all functions without side-effect have to have no side-effect */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* vendor specific version information is BCD coded */
/* Dlt500 */
#if((DLT_SW_MAJOR_VERSION != (0x01u)) || (DLT_SW_MINOR_VERSION != (0x07u)) || (DLT_SW_PATCH_VERSION != (0x04u)))
# error "Vendor specific version numbers of Dlt.c and Dlt.h are inconsistent"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 1503, 1504, 1505, 1514 EOF */ /* MD_MSR_14.1 */ /* MD_MSR_8.10 */ /* MD_MSR_8.10 */ /* MD_Dlt_1514 */

/* PRQA S 3453 FUNCTIONLIKEMACRO_C */ /*  MD_MSR_19.7 */

#if defined (DLT_USE_COMLAYER_XCP) && (DLT_USE_COMLAYER_XCP == STD_ON) /* COV_DLT_FILTER_ASR_XCP */
# if !defined (Dlt_TransmitData)
#define Dlt_TransmitData(event, data, dataLength)  Xcp_Event(event)
# endif /* !defined (Dlt_TransmitData) */
#endif /* defined (DLT_USE_COMLAYER_XCP) && (DLT_USE_COMLAYER_XCP == STD_ON) */


/* PRQA L:FUNCTIONLIKEMACRO_C */ /* MD_MSR_19.7 */

/*********************************************************************************************************************/
/* General definition of checking macros */
/* PRQA S 0857 17 */ /* MD_MSR_1.1_857 */
/* PRQA S 3458 16 */ /* MD_MSR_19.4 */
# define Dlt_CheckErrorReturnVoid(cond, api, err)        \
{ if(!(cond)){                                           \
    Dlt_CallDetReportError((api), (err));                \
    return;                                              \
}}

# define Dlt_CheckErrorReturnValue(cond, api, err, ret)  \
{ if(!(cond)){                                           \
    Dlt_CallDetReportError((api), (err));                \
    return(ret);                                         \
}}

# define Dlt_CheckErrorContinue(cond, api, err)          \
{ if(!(cond)){                                           \
    Dlt_CallDetReportError((api), (err));                \
}}

/*********************************************************************************************************************/
/* Macros for DET abstraction */

/* Dlt444, Dlt439 */
/* PRQA S 3453 10 */ /*  MD_MSR_19.7 */
#if(DLT_DEV_ERROR_DETECT == STD_ON)
# define Dlt_CheckDetErrorReturnVoid(cond, api, err)       Dlt_CheckErrorReturnVoid((cond), (api), (err))
# define Dlt_CheckDetErrorReturnValue(cond, api, err, ret) Dlt_CheckErrorReturnValue((cond), (api), (err), (ret))
# define Dlt_CheckDetErrorContinue(cond, api, err)         Dlt_CheckErrorContinue((cond), (api), (err))

# if (DLT_DEV_ERROR_REPORT == STD_ON)
# define Dlt_CallDetReportError(api, err)                  (void)Det_ReportError(DLT_MODULE_ID, 0, (api), (err)) /* ESCAN00087203 */
# else /* (DLT_DEV_ERROR_REPORT == STD_ON) */
# define Dlt_CallDetReportError(api, err)
# endif /* (DLT_DEV_ERROR_REPORT == STD_ON) */

#else
# define Dlt_CheckDetErrorReturnVoid(cond, api, err)
# define Dlt_CheckDetErrorReturnValue(cond, api, err, ret) 
# define Dlt_CheckDetErrorContinue(cond, api, err) 
# define Dlt_CallDetReportError(api, err) 
#endif

/* PRQA S 3453 2 */ /* MD_MSR_19.7 */
#  define DLT_BEGIN_CRITICAL_SECTION_0() SchM_Enter_Dlt_DLT_EXCLUSIVE_AREA_0()
#  define DLT_END_CRITICAL_SECTION_0()   SchM_Exit_Dlt_DLT_EXCLUSIVE_AREA_0()


/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/* ====================================================================================================================
 * COMLAYER AUTOSAR
 * ====================================================================================================================
 */

/* ====================================================================================================================
 * COMLAYER XCP
 * ====================================================================================================================
 */

#define DLT_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

DLT_LOCAL VAR(Dlt_GlobalStateType, DLT_VAR_ZERO_INIT) Dlt_GlobalState = DLT_GLOBAL_STATE_UNINIT;
DLT_LOCAL VAR(Dlt_GlobalStateType, DLT_VAR_ZERO_INIT) Dlt_GlobalStateNew = DLT_GLOBAL_STATE_UNINIT;

DLT_LOCAL VAR(boolean, DLT_VAR_ZERO_INIT)             Dlt_EnterDetTransmitContext = FALSE;

#define DLT_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define DLT_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Variable is loaded with the last DET error code */
VAR(uint32, DLT_VAR_NOINIT)                          Dlt_DetErrorCode;

#define DLT_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define DLT_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Variable is loaded with DEM event id and status code. */
VAR(Dlt_DemEventStatusType, DLT_VAR_NOINIT)          Dlt_DemEventStatus; /*lint -e830 */ /* Suppress ID830 */ /*lint -e552 */ /* Suppress ID552 */

/* Variable is loaded with message ID of non-verbose message . */
VAR(Dlt_MessageIDType, DLT_VAR_NOINIT)               Dlt_NonVerboseMessageId;

# if (DLT_USE_VERBOSE_MODE == STD_ON)
/* Buffer is loaded with payload of verbose message. */
VAR(uint8, DLT_VAR_NOINIT)                           Dlt_VerboseMessageData[DLT_MAX_MESSAGE_LENGTH];
# endif /* (DLT_USE_VERBOSE_MODE == STD_ON) */

#define DLT_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */




/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/
#define DLT_START_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


CONST(uint8, DLT_CONST) Dlt_ModuleTable[256] = 
{
/*  0      1      2      3      4      5      6      7      8      9      A      B      C      D      E      F           */
  0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x0Au, 0x0Bu, 0x0Cu, 0x0Du, 0x00u, 0x00u,  /* 0x */ /* 0x0A = ECUM, 0x0B = FIM, 0x0C = COMM, 0x0D = WDGM */
  0x00u, 0x00u, 0x00u, 0x00u, 0x14u, 0x15u, 0x00u, 0x00u, 0x00u, 0x00u, 0x1Au, 0x00u, 0x00u, 0x1Du, 0x00u, 0x1Fu,  /* 1x */ /* 0x14 = NVM, 0x15 = FEE, 0x1A = XCP, 0x1D = NM, 0x1F = CANNM */
  0x20u, 0x00u, 0x00u, 0x23u, 0x24u, 0x25u, 0x00u, 0x00u, 0x28u, 0x00u, 0x2Au, 0x2Bu, 0x00u, 0x00u, 0x00u, 0x00u,  /* 2x */ /* 0x20 = FRNM, 0x23 = CANTP, 0x24 = FRTP, 0x25 = J1939TP, 0x28 = EA, 0x2A = BSWM, 0x2B = WDGIF */
  0x00u, 0x00u, 0x32u, 0x33u, 0x34u, 0x35u, 0x36u, 0x00u, 0x38u, 0x00u, 0x00u, 0x00u, 0x3Cu, 0x3Du, 0x3Eu, 0x00u,  /* 3x */ /* 0x32 = COM, 0x33 = PDUR, 0x34 = IPDUM, 0x35 = DCM, 0x36 = DEM, 0x38 depends on InstanceId (SOAD = 0x00, TCPIP = 0x01, IPV4 = 0x02, IPV6 = 0x04), 0x3C = CANIF, 0x3D = FRIF, 0x3E = LINIF */
  0x00u, 0x41u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x49u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,  /* 4x */ /* 0x41 = ETHIF, 0x49 = ETHTRCV */
  0x50u, 0x51u, 0x52u, 0x53u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x5Cu, 0x00u, 0x00u, 0x00u,  /* 5x */ /* 0x50 = CAN, 0x51 = FR, 0x52 = LIN, 0x53 = SPI, 0x5C = FLS */
  0x00u, 0x00u, 0x00u, 0x00u, 0x64u, 0x65u, 0x66u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,  /* 6x */ /* 0x64 = GPT, 0x65 = MCU, 0x66 = WDG */
  0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x78u, 0x79u, 0x7Au, 0x7Bu, 0x00u, 0x00u, 0x00u, 0x00u,  /* 7x */ /* 0x78 = DIO, 0x79 = PWM, 0x7A = ICU, 0x7B = ADC */
  0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x8Cu, 0x8Du, 0x8Eu, 0x8Fu,  /* 8x */ /* 0x8C = CANSM, 0x8D = LINSM, 0x8E = FRSM , 0x8F = ETHSM */
  0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,  /* 9x */ 
  0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0xAEu, 0x00u,  /* Ax */ /* 0x(1)AE = ETH */
  0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,  /* Bx */
  0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,  /* Cx */
  0x00u, 0x00u, 0x00u, 0xD3u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,  /* Dx */ /* 0xD3 = FRXCP */
  0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,  /* Ex */
  0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0xFFu   /* Fx */ /* 0xFF : depends on InstanceId - 0x00: CANXCP, 0x65: RCS, 0x66: HTTP, 0x67: TLS, 0x68: Crypto, 0x69: DNS, 0x6A: JSON, 0x6B..0x6D: EXI, 0x6E: IPBase, 0x6F: SCC */
};

#define DLT_STOP_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define DLT_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ####################################################################################################################
 *   HH      HH  EEEEEEEEEE  LL          PPPPPPPP    EEEEEEEEEE  RRRRRRRR
 *   HH      HH  EE          LL          PP      PP  EE          RR      RR
 *   HH      HH  EE          LL          PP      PP  EE          RR      RR
 *   HHHHHHHHHH  EEEEEEEE    LL          PPPPPPPP    EEEEEEEE    RRRRRRRR
 *   HH      HH  EE          LL          PP          EE          RR    RR
 *   HH      HH  EE          LL          PP          EE          RR      RR
 *   HH      HH  EEEEEEEEEE  LLLLLLLLLL  PP          EEEEEEEEEE  RR      RR
 * ####################################################################################################################
 */
/**********************************************************************************************************************
  Dlt_Hlp_CopyArrayToLongLittleEndian()
**********************************************************************************************************************/
/*!
 *
 * \brief       Copies data from array to variable.
 * \details     Copies 4 byte from source array to variable with least significant byte first.
 * \param[out]  StartIndex            Start index of source array where the data is copied from.
 * \param[out]  DestData              Data destination.
 * \param[in]   SourceData            Data source.
 * \return      -
 * \pre         The source array must have at least the size of 4.
 * \pre         Only reentrant if destination and source pointer content are not affected by second call while 
 *              interrupted.
 * \context     TASK|ISR
 * \reentrant   TRUE
 * \synchronous TRUE
**********************************************************************************************************************/
DLT_LOCAL_INLINE FUNC(void, DLT_CODE) Dlt_Hlp_CopyArrayToLongLittleEndian(P2VAR(uint16, AUTOMATIC, DLT_APPL_VAR) StartIndex,
                                                                          P2VAR(uint32, AUTOMATIC, DLT_APPL_VAR) DestData,
                                                                          P2CONST(uint8, AUTOMATIC, DLT_CONST) SourceData);




/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/* ####################################################################################################################
 *   HH      HH  EEEEEEEEEE  LL          PPPPPPPP    EEEEEEEEEE  RRRRRRRR
 *   HH      HH  EE          LL          PP      PP  EE          RR      RR
 *   HH      HH  EE          LL          PP      PP  EE          RR      RR
 *   HHHHHHHHHH  EEEEEEEE    LL          PPPPPPPP    EEEEEEEE    RRRRRRRR
 *   HH      HH  EE          LL          PP          EE          RR    RR
 *   HH      HH  EE          LL          PP          EE          RR      RR
 *   HH      HH  EEEEEEEEEE  LLLLLLLLLL  PP          EEEEEEEEEE  RR      RR
 * ####################################################################################################################
 */
/**********************************************************************************************************************
 * Dlt_Hlp_CopyArrayToLongLittleEndian
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 */
DLT_LOCAL_INLINE FUNC(void, DLT_CODE) Dlt_Hlp_CopyArrayToLongLittleEndian(P2VAR(uint16, AUTOMATIC, DLT_APPL_VAR) StartIndex,
                                                                          P2VAR(uint32, AUTOMATIC, DLT_APPL_VAR) DestData,
                                                                          P2CONST(uint8, AUTOMATIC, DLT_CONST) SourceData)
{
  /* ----- Implementation ------------------------------------------------- */
  /* #-- Copy source data from little endian array to destination 32bit variable. */
  (*DestData)  = (uint32)((uint32)(SourceData[StartIndex[0] + 3]) << 24);
  (*DestData) |= (uint32)((uint32)(SourceData[StartIndex[0] + 2]) << 16);
  (*DestData) |= (uint32)((uint32)(SourceData[StartIndex[0] + 1]) << 8);
  (*DestData) |= (uint32)((uint32)(SourceData[StartIndex[0]]));

  /* #-- Set array index to new postion. */
  *StartIndex = StartIndex[0] + 4;
} /* Dlt_Hlp_CopyArrayToLongLittleEndian */



/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/



/**********************************************************************************************************************
 * Dlt_InitMemory
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 */
FUNC(void, DLT_CODE) Dlt_InitMemory(void)
{
  /* #-- If com layer is AUTOSAR, pre-initialize global variables. */

  /* #-- Set the global state to DLT_GLOBAL_STATE_UNINIT, now the logging of DEM and DET messages is active. */
  Dlt_GlobalState = DLT_GLOBAL_STATE_UNINIT;
  Dlt_GlobalStateNew = DLT_GLOBAL_STATE_UNINIT;

#if (DLT_USE_COMLAYER_XCP == STD_ON)
  Dlt_EnterDetTransmitContext = FALSE;
#endif
} /* Dlt_InitMemory */


/**********************************************************************************************************************
 * Dlt_Init
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 */
FUNC(void, DLT_CODE) Dlt_Init( P2CONST(Dlt_ConfigType, AUTOMATIC, DLT_PBCFG) ConfigPtr)
{

  /* ----- Implementation ------------------------------------------------- */
  DLT_DUMMY_STATEMENT(ConfigPtr); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */

  /* #-- Initialize all global variables which have to be available with DLT module initialization. */

#if (DLT_USE_COMLAYER_XCP == STD_ON)
  Dlt_DetErrorCode = 0;
  Dlt_DemEventStatus = 0;
  Dlt_NonVerboseMessageId = 0;
#endif /* (DLT_USE_COMLAYER_XCP == STD_ON) */

  /* #-- Set the global state to DLT_GLOBAL_STATE_OFFLINE, now the logging as well as sending is disabled. */
  Dlt_GlobalState = DLT_GLOBAL_STATE_OFFLINE;
  Dlt_GlobalStateNew = DLT_GLOBAL_STATE_OFFLINE;
  /*lint -e{438} */ /* PC_Dlt_438 */
} /* Dlt_Init */

#if (DLT_VERSION_INFO_API == STD_ON)

/**********************************************************************************************************************
 * Dlt_GetVersionInfo
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 */
FUNC(void, DLT_CODE) Dlt_GetVersionInfo( P2VAR(Std_VersionInfoType, AUTOMATIC, DLT_APPL_VAR) VersionInfo)
{ /* [Dlt271] */
  /* ----- Local Variables ------------------------------------------------ */
  uint8 errorId = DLT_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (DLT_DEV_ERROR_DETECT == STD_ON)
  if (VersionInfo == NULL_PTR)
  {
    errorId = DLT_E_PARAM_POINTER;
  }
  else
#endif /* (DLT_DEV_ERROR_DETECT == STD_ON) */
  /* ----- Implementation ------------------------------------------------- */
  {
    VersionInfo -> vendorID         = DLT_VENDOR_ID;
    VersionInfo -> moduleID         = DLT_MODULE_ID;
    VersionInfo -> sw_major_version = DLT_SW_MAJOR_VERSION;
    VersionInfo -> sw_minor_version = DLT_SW_MINOR_VERSION;
    VersionInfo -> sw_patch_version = DLT_SW_PATCH_VERSION;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (DLT_DEV_ERROR_REPORT == STD_ON)
  if (errorId != DLT_E_NO_ERROR)
  {
    (void)Det_ReportError(DLT_MODULE_ID, 0, DLT_API_ID_GETVERSIONINFO, errorId);
  }
# else /* (DLT_DEV_ERROR_REPORT == STD_ON) */
  DLT_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */ /* PC_Dlt_438 */
# endif /* (DLT_DEV_ERROR_REPORT == STD_ON) */

  /*lint -e{550} */ /* PC_Dlt_550 */
  /* PRQA S 2006 1 */ /* MD_MSR_14.7 */
} /* Dlt_GetVersionInfo */
#endif /* (DLT_VERSION_INFO_API == STD_ON) */


/**********************************************************************************************************************
 * Dlt_DetForwardErrorTrace
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 */
FUNC(void, DLT_CODE) Dlt_DetForwardErrorTrace( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{ 

  /* ----- Implementation ------------------------------------------------- */
  /* #-- Forwarding of DET messages is only allowed before initialization and after DLT activation. */
  if ((Dlt_GlobalState == DLT_GLOBAL_STATE_ONLINE) ||
      (Dlt_GlobalState == DLT_GLOBAL_STATE_UNINIT))
  {
    /* Dlt430, Dlt432 */
    /* #-- Prevent recursion in case DLT throws a DET error itself. */
    if (ModuleId != DLT_MODULE_ID)
    {
      /* #-- Enter Dlt_DLT_EXCLUSIVE_AREA_0. */
      DLT_BEGIN_CRITICAL_SECTION_0(); /* PRQA S 3109 */  /* MD_MSR_14.3 */

      /* #-- If use comlayer xcp enabled, build log message for DET error reporting. */
#if (DLT_USE_COMLAYER_XCP == STD_ON)
      if((uint8)ModuleId == Dlt_ModuleTable[(uint8)ModuleId])
      {  
        Dlt_DetErrorCode = (uint8)InstanceId; /* ESCAN00070451: necessary for components with same module ids */
        Dlt_DetErrorCode <<= 8;
        Dlt_DetErrorCode |= (uint8)ModuleId; /* ESCAN00074824 */
        Dlt_DetErrorCode <<= 8;
        Dlt_DetErrorCode |= (uint8)ApiId;
        Dlt_DetErrorCode <<= 8;
        Dlt_DetErrorCode |= (uint8)ErrorId;
      }
      else
      {
        /* [Dlt439]: detected invalid module ID are not reported to DET to prevent a loop. Instead an invalid module ID is reported to the XCP master via Dlt_DetErrorCode  */
        Dlt_DetErrorCode = (uint32)(0x01000000 | ModuleId);
      }

      /* #-- Protect the transmission context against recursion. */
      if (Dlt_EnterDetTransmitContext == FALSE)
      {
        Dlt_EnterDetTransmitContext = TRUE;
        /* #-- Send DLT-DET-message via XCP. */
        (void)Dlt_TransmitData(DLT_DET_EVENT, &Dlt_DetErrorCode, 4);
        Dlt_EnterDetTransmitContext = FALSE;
      }
#endif /* (DLT_USE_COMLAYER_XCP == STD_ON) */

      /* #-- Leave Dlt_DLT_EXCLUSIVE_AREA_0. */
      DLT_END_CRITICAL_SECTION_0(); /* PRQA S 3109 */  /* MD_MSR_14.3 */
    }
  }
} /* Dlt_DetForwardErrorTrace */


/**********************************************************************************************************************
 * Dlt_DemTriggerOnEventStatus
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 */
FUNC(void, DLT_CODE) Dlt_DemTriggerOnEventStatus(Dem_EventIdType EventId,
                                                 Dem_EventStatusExtendedType EventStatusOld,
                                                 Dem_EventStatusExtendedType EventStatusNew)
{ /* [Dlt474] */
  /* ----- Local Variables ------------------------------------------------ */
  uint8 errorId = DLT_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (DLT_DEV_ERROR_DETECT == STD_ON)
  /* #-- If required, check that event ID is in valid range. */
  /* DEM Event ID = 0 indicates no event or failure. Highest valid event ID is DLT_NUM_DEM_EVENTS. */
  if ((EventId == 0) || (EventId > DLT_NUM_DEM_EVENTS))
  {
    errorId = DLT_E_WRONG_PARAMETERS;
  }
  else
#endif /* (DLT_DEV_ERROR_DETECT == STD_ON) */
  /* ----- Implementation ------------------------------------------------- */
  /* #-- If the initial check is passed or not required: */
  {
    /* #-- DEM events are only allowed to be send before initialization and after DLT activation. */
    if ((Dlt_GlobalState == DLT_GLOBAL_STATE_ONLINE) ||
        (Dlt_GlobalState == DLT_GLOBAL_STATE_UNINIT))
    {
      /* [Dlt475]: the DEM already ensures that EventStatusOld and EventStatusNew are not equal, because Dlt_DemTriggerOnEventStatus is only called if they differ. Hence the log message can always be generated. */
      /* #-- Enter Dlt_DLT_EXCLUSIVE_AREA_0. */
      DLT_BEGIN_CRITICAL_SECTION_0(); /* PRQA S 3109 */  /* MD_MSR_14.3 */

      /* #-- If DEM event filtering is enabled, call callback function to add individual message filter. */
#if (DLT_DEM_EVENT_FILTERING_ENABLED == STD_ON)
      /* UREQ00041311: The implementation shall be able to filter for the following properties: DEM Event ID and DEM Event Status Bits */
      if (Appl_DltDemEventFilterCbk(EventId, EventStatusOld, EventStatusNew) == TRUE)
#else
      DLT_DUMMY_STATEMENT(EventStatusOld); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */ /* PC_Dlt_438 */
#endif
      {
        /* #-- If comlayer XCP is active, send DEM event via XCP. */
#if (DLT_USE_COMLAYER_XCP == STD_ON)
        Dlt_DemEventStatus = (uint16)EventId;
        Dlt_DemEventStatus <<= 16;
        Dlt_DemEventStatus |= (uint8)EventStatusNew;

        /* UREQ00040542: Report DEM Event change */
        (void)Dlt_TransmitData(DLT_DEM_EVENT, &Dlt_DemEventStatus, 4);
#endif /* (DLT_USE_COMLAYER_XCP == STD_ON) */
      }

      /* #-- Leave Dlt_DLT_EXCLUSIVE_AREA_0. */
      DLT_END_CRITICAL_SECTION_0(); /* PRQA S 3109 */  /* MD_MSR_14.3 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (DLT_DEV_ERROR_REPORT == STD_ON)
  if (errorId != DLT_E_NO_ERROR)
  {
    (void)Det_ReportError(DLT_MODULE_ID, 0, DLT_API_ID_DEMTRIGGERONEVENTSTATUS, errorId);
  }
#else /* (DLT_DEV_ERROR_REPORT == STD_ON) */
  DLT_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */ /* PC_Dlt_438 */
#endif /* (DLT_DEV_ERROR_REPORT == STD_ON) */

  /*lint -e{438} */ /* PC_Dlt_438 */
  /*lint -e{550} */ /* PC_Dlt_550 */
  /* PRQA S 2006 1 */ /* MD_MSR_14.7 */
} /* Dlt_DemTriggerOnEventStatus */


/**********************************************************************************************************************
 * Dlt_SendLogMessage
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 */
FUNC(Std_ReturnType, DLT_CODE) Dlt_SendLogMessage(Dlt_SessionIDType parg0, 
                                                  P2CONST(Dlt_MessageLogInfoType, AUTOMATIC, DLT_CONST) LogInfo, 
                                                  P2CONST(uint8, AUTOMATIC, DLT_CONST) LogData, 
                                                  uint16 LogDataLength) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{ /* Dlt241 */
  /* ----- Local Variables ------------------------------------------------ */
  Dlt_ReturnType retVal = DLT_E_ERROR_UNKNOWN;
  uint8 errorId = DLT_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (DLT_DEV_ERROR_DETECT == STD_ON)
  if (Dlt_GlobalState == DLT_GLOBAL_STATE_UNINIT)
  {
    errorId = DLT_E_UNINITIALIZED;
  }
  else if (LogData == NULL_PTR)
  {
    errorId = DLT_E_PARAM_POINTER;
  }
#endif /* (DLT_DEV_ERROR_DETECT == STD_ON) */

  /* #-- If the comlayer ASR is active: */
  /* #-- Otherwise: */
# if (DLT_DEV_ERROR_DETECT == STD_ON)
  else
# endif /* (DLT_DEV_ERROR_DETECT == STD_ON) */
  /* ----- Implementation ------------------------------------------------- */
  {
    DLT_DUMMY_STATEMENT(parg0); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */

    /* #-- If global state is DLT_GLOBAL_STATE_ONLINE: */
    if (Dlt_GlobalState == DLT_GLOBAL_STATE_ONLINE)
    {
      /* SWS_Dlt_00014 */
      /* #-- If message is in verbose mode AND
       *       If implement verbose mode is enabled, build and send the log message with string payload.
       *       Otherwise, invalid request. */
      if ((LogInfo->options & DLT_VERBOSE_MSG) != FALSE)
      {
# if (DLT_USE_VERBOSE_MODE == STD_ON)
        /* verbose message handling */
        if ((LogDataLength < DLT_MAX_MESSAGE_LENGTH))
        {
          /* #-- Enter Dlt_DLT_EXCLUSIVE_AREA_0. */
          DLT_BEGIN_CRITICAL_SECTION_0(); /* PRQA S 3109 */  /* MD_MSR_14.3 */

          VStdMemCpy(&Dlt_VerboseMessageData[0], &LogData[sizeof(Dlt_StandardHeaderType)+sizeof(Dlt_MessageIDType)], LogDataLength);

          /* SREQ00024774: If the string written to the data buffer is shorter than the defined data field it shall be terminated with 0. */
          Dlt_VerboseMessageData[LogDataLength] = '\0';

          /* UREQ00040541: generate verbose log message */
          if ((Dlt_TransmitData(DLT_VERBOSE_MSG_EVENT, (P2CONST(uint8, AUTOMATIC, DLT_CONST))&LogData, (uint16)LogDataLength)) != (XCP_EVENT_NOP))
          {
            retVal = (Dlt_ReturnType)(DLT_E_OK);
          }
          else
          {
            retVal = (Dlt_ReturnType)(DLT_E_ERROR_UNKNOWN);
          }

          /* #-- Leave Dlt_DLT_EXCLUSIVE_AREA_0. */
          DLT_END_CRITICAL_SECTION_0(); /* PRQA S 3109 */  /* MD_MSR_14.3 */
        }
        else
        {
#  if (DLT_DEV_ERROR_DETECT == STD_ON)
          errorId = DLT_E_WRONG_PARAMETERS;
#  endif
          retVal = (Dlt_ReturnType)DLT_E_MSG_TOO_LARGE;
        }
# else /* (DLT_USE_VERBOSE_MODE == STD_ON) */
        DLT_DUMMY_STATEMENT(LogDataLength); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */ /* PC_Dlt_438 */
        /* SWS_Dlt_00090 */
        retVal = (Dlt_ReturnType)DLT_E_ERROR_UNKNOWN;
# endif /* (DLT_USE_VERBOSE_MODE == STD_ON) */
      }
      /* #-- Otherwise, build the log message with message ID and send it via XCP. */
      else
      {
        /* non-verbose message handling */
        uint32 msgId = 0;
        uint16 index = 4;
        Dlt_Hlp_CopyArrayToLongLittleEndian(&index, &msgId, &LogData[0]); /* ESCAN00081868 */
        /* Dlt031: Message IDs used for Dem (0x00000001) and Det (0x00000002) are reserved and not usable for SW-Cs. */
        /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
        /* #-- If message ID in invalid range, reject send request.
         *     Otherwise, send log message via XCP. */
        if ((msgId <= 2) || (msgId >= DLT_NUM_NON_VERBOSE_MESSAGES))
        {
          errorId = DLT_E_WRONG_PARAMETERS;
          retVal = (Dlt_ReturnType)DLT_E_ERROR_UNKNOWN;
        }
        else
        {
          /* #-- Enter Dlt_DLT_EXCLUSIVE_AREA_0 */
          DLT_BEGIN_CRITICAL_SECTION_0(); /* PRQA S 3109 */  /* MD_MSR_14.3 */
          
          Dlt_NonVerboseMessageId = (Dlt_MessageIDType)(msgId);

          if ((Dlt_TransmitData(DLT_NON_VERBOSE_MSG_EVENT, (P2CONST(uint8, AUTOMATIC, DLT_CONST))&LogData, (uint16)LogDataLength)) != (XCP_EVENT_NOP))
          {
            retVal = (Dlt_ReturnType)(DLT_E_OK);
          }
          else
          {
            retVal = (Dlt_ReturnType)(DLT_E_ERROR_UNKNOWN);
          }

          /* #-- Leave Dlt_DLT_EXCLUSIVE_AREA_0 */
          DLT_END_CRITICAL_SECTION_0(); /* PRQA S 3109 */  /* MD_MSR_14.3 */
        }
      }
    }
  }

#if (DLT_DEV_ERROR_REPORT == STD_ON)
  /* ----- Development Error Report --------------------------------------- */
  if (errorId != DLT_E_NO_ERROR)
  {
    (void)Det_ReportError(DLT_MODULE_ID, 0, DLT_API_ID_SENDLOGMESSAGE, errorId);
  }
#else /* (DLT_DEV_ERROR_REPORT == STD_ON) */
  DLT_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */ /* PC_Dlt_438 */
#endif /* (DLT_DEV_ERROR_REPORT == STD_ON) */

  /*lint -e{438} */ /* PC_Dlt_438 */
  return (Std_ReturnType)retVal; /*lint -e{550} */ /* PC_Dlt_550 */

  /* PRQA S 2006 2 */ /* MD_MSR_14.7 */
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* Dlt_SendLogMessage */



/**********************************************************************************************************************
 * Dlt_SetState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 */
FUNC(Std_ReturnType, DLT_CODE) Dlt_SetState(Dlt_GlobalStateType NewState)
{
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = DLT_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
# if (DLT_DEV_ERROR_DETECT == STD_ON)
  if (Dlt_GlobalState == DLT_GLOBAL_STATE_UNINIT)
  {
    errorId = DLT_E_UNINITIALIZED;
  }
  else
# endif /* (DLT_DEV_ERROR_DETECT == STD_ON) */
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #-- Enter Dlt_DLT_EXCLUSIVE_AREA_0. */
    DLT_BEGIN_CRITICAL_SECTION_0(); /* PRQA S 3109 */  /* MD_MSR_14.3 */

    /* #-- If Dlt_GlobalState differs from new state, change the Dlt_GlobalStateNew.
     *     Otherwise, the request is invalid.
     */
    switch(Dlt_GlobalState)
    {
    case(DLT_GLOBAL_STATE_OFFLINE) :
      if (NewState == DLT_GLOBAL_STATE_ONLINE)
      {
        Dlt_GlobalStateNew = DLT_GLOBAL_STATE_ONLINE;
        retVal = E_OK;
      }
      break;

    case(DLT_GLOBAL_STATE_ONLINE) :
      if (NewState == DLT_GLOBAL_STATE_OFFLINE)
      {
        Dlt_GlobalStateNew = DLT_GLOBAL_STATE_OFFLINE;
        retVal = E_OK;
      }
      break;

    default :
      break;
    }

    /* #-- Leave Dlt_DLT_EXCLUSIVE_AREA_0 */
    DLT_END_CRITICAL_SECTION_0(); /* PRQA S 3109 */  /* MD_MSR_14.3 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (DLT_DEV_ERROR_REPORT == STD_ON)
  if (errorId != DLT_E_NO_ERROR)
  {
    (void)Det_ReportError(DLT_MODULE_ID, 0, DLT_API_ID_SETSTATE, errorId);
  }
# else /* (DLT_DEV_ERROR_REPORT == STD_ON) */
  DLT_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */ /* PC_Dlt_438 */
# endif /* (DLT_DEV_ERROR_REPORT == STD_ON) */

  return retVal; /*lint -e{550} */ /* PC_Dlt_550 */
} /* Dlt_SetState */


/**********************************************************************************************************************
 * Dlt_GetState
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 */
FUNC(Std_ReturnType, DLT_CODE) Dlt_GetState(P2VAR(Dlt_GlobalStateType, AUTOMATIC, DLT_APPL_VAR) CurrentStatePtr)
{
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = DLT_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
# if (DLT_DEV_ERROR_DETECT == STD_ON)
  if (Dlt_GlobalState == DLT_GLOBAL_STATE_UNINIT)
  {
    errorId = DLT_E_UNINITIALIZED;
  }
  else
# endif /* (DLT_DEV_ERROR_DETECT == STD_ON) */
  /* ----- Implementation ------------------------------------------------- */
  {
    /* #-- The request of Dlt_GlobalState is only valid in state DLT_GLOBAL_STATE_OFFLINE and 
     *     DLT_GLOBAL_STATE_ONLINE.
     */
    switch(Dlt_GlobalState)
    {
    case(DLT_GLOBAL_STATE_OFFLINE) :
      *CurrentStatePtr = (Dlt_GlobalStateType)DLT_GLOBAL_STATE_OFFLINE;
      retVal = E_OK;
      break;

    case(DLT_GLOBAL_STATE_ONLINE) :
      *CurrentStatePtr = (Dlt_GlobalStateType)DLT_GLOBAL_STATE_ONLINE;
      retVal = E_OK;
      break;

    default :
      break;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (DLT_DEV_ERROR_REPORT == STD_ON)
  if (errorId != DLT_E_NO_ERROR)
  {
    (void)Det_ReportError(DLT_MODULE_ID, 0, DLT_API_ID_GETSTATE, errorId);
  }
# else /* (DLT_DEV_ERROR_REPORT == STD_ON) */
  DLT_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */ /* PC_Dlt_438 */
# endif /* (DLT_DEV_ERROR_REPORT == STD_ON) */

  return retVal; /*lint -e{550} */ /* PC_Dlt_550 */
} /* Dlt_GetState */


/**********************************************************************************************************************
 * Dlt_MainFunction
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 */
FUNC(void, DLT_CODE) Dlt_MainFunction(void)
{

  /* #-- Update global state. */
  if (Dlt_GlobalState != Dlt_GlobalStateNew)
  {
    Dlt_GlobalState = Dlt_GlobalStateNew;
  }

  
  /*lint -e{550} */ /* PC_Dlt_550 */
  /* PRQA S 6030 1 */ /* MD_MSR_STCYC */
} /* Dlt_MainFunction */

#define DLT_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* module specific MISRA deviations:

  MD_Dlt_3218:     MISRA rule 8.7: File scope static, '%s', only accessed in one function.
     Reason:         Constants defined global but are used only once. The function uses reference, thus constants 
                     have to live after leaving the function.
     Risk:           No error.
     Prevention:     Not required.

  MD_Dlt_1514:    MISRA rule 8.7: Objects shall be defined at block scope if they are only accessed from within a 
                                  single function.
     Reason:         Constants defined global but are used only once. The function uses reference, thus constants 
                     have to live after leaving the function.
     Risk:           No error.
     Prevention:     Not required.

  MD_Dlt_0686:     MISRA rule 9.2: Braces shall be used to indicate and match the structure in the non-zero 
                                   initialisation of arrays and structures. 
     Reason:         The structure Dlt_Context cannot be initialized completely global due to variable length depending 
                     on config parameter DLT_MAX_COUNT_APP_IDS.
     Risk:           No error.
     Prevention:     Not required.

  MD_Dlt_3673:     MISRA rule 16.7: A pointer parameter in a function prototype should be declared as pointer to const
                                    if the pointer is not used to modify the addressed object.
     Reason:         The use of these parameters is configuration dependent. In some configurations the pointer is used
                     to modify the addressed object.
     Risk:           No error.
     Prevention:     Not required.
*/

/* module specific PClint deviations:
  
  PC_Dlt_438:      PClint rule 438: Last value assigned to variable 'Symbol' not used.
     Reason:         The variables which are not used in functions are covered by dummy statements, but these statements 
                     can be defined to nothing.
     Risk:           Undetected unused variables.
     Prevention:     Not required.

  PC_Dlt_550:      PClint rule 550: Symbol 'Symbol' (Location) not accessed.
     Reason:         The errorId is always created and initialized, but if development error reporting is disabled, 
                     the variable is never used.
     Risk:           Undetected unused variables.
     Prevention:     Not required.
 */

/* COV_JUSTIFICATION_BEGIN

\ID COV_DLT_FILTER_ASR_XCP
\ACCEPT XF tx xf
\ACCEPT TX tx tx 
\ACCEPT TF tx tf 
\REASON The feature Dlt_Autosar is filtered if according licence is not available

\ID COV_DLT_MSR_COMPATIBILITY
\ACCEPT TX 
\ACCEPT XF 
\REASON [COV_MSR_COMPATIBILITY]

COV_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  END OF FILE: Dlt.c
 *********************************************************************************************************************/
 
