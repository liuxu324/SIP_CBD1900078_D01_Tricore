/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  EthSwt_30_Sja1105PQRS_LL.c
 *        \brief  Internal low-level implementation for SPI handling
 *
 *      \details  Source File contains the implementation of the low-level APIs that handle the SPI and MII interfaces.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

/* QAC file deviation */
/* PRQA S 0857 ETHSWT_30_SJA1105PQRS_LL_NO_OF_MACROS */ /* MD_MSR_1.1_857 */
/* PRQA S 0810 ETHSWT_30_SJA1105PQRS_LL_INC_NESTING_LEVEL */ /* MD_MSR_1.1_810 */
/* PRQA S 0828 ETHSWT_30_SJA1105PQRS_LL_IF_NESTING_LEVEL */ /* MD_MSR_1.1_828 */
/* PRQA S 779,777 IDENTIFIER_DIFFER */ /* MD_EthSwt_30_Sja1105PQRS_5.1 */

#define ETHSWT_30_SJA1105PQRS_LL_SOURCE

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "EthSwt_30_Sja1105PQRS_LL.h"
#include "EthSwt_30_Sja1105PQRS.h"
#include "EthSwt_30_Sja1105PQRS_Regs.h"
#include "EthSwt_30_Sja1105PQRS_Lcfg.h"
#include "SchM_EthSwt_30_Sja1105PQRS.h"
#include "IpBase.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* Check the version of EthSwt_30_Sja1105PQRS header file */
#if (  (ETHSWT_30_SJA1105PQRS_SW_MAJOR_VERSION != (0x05u)) \
    || (ETHSWT_30_SJA1105PQRS_SW_MINOR_VERSION != (0x00u)) \
    || (ETHSWT_30_SJA1105PQRS_SW_PATCH_VERSION != (0x01u)) )
 #error "Vendor specific version numbers of EthSwt_30_Sja1105PQRS_LL.c and EthSwt_30_Sja1105PQRS.h are inconsistent"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/
#ifndef   STATIC
#  define STATIC static
#endif /* STATIC */

/*! Transaction stack size defining the maximum parallel SPI transactions */
#define ETHSWT_30_SJA1105PQRS_LL_TRANSACTION_STACK_SIZE  (5u)

/* -- Swap Commands --------------------------------------------------------- */

/* -- Spi DataType encapsulation -------------------------------------------- */
#if (((defined SPI_AR_RELEASE_MAJOR_VERSION) && (4 == SPI_AR_RELEASE_MAJOR_VERSION)) && \
     ((defined SPI_AR_RELEASE_MINOR_VERSION) && (0 == SPI_AR_RELEASE_MINOR_VERSION)))
 /* Is ASR 4.0 */

typedef Spi_DataType EthSwt_30_Sja1105PQRS_LLSpiDataType;
#elif (((defined SPI_AR_RELEASE_MAJOR_VERSION) && (4 == SPI_AR_RELEASE_MAJOR_VERSION)) && \
     ((defined SPI_AR_RELEASE_MINOR_VERSION) && (1 <= SPI_AR_RELEASE_MINOR_VERSION)))
 /* Is ASR 4.1 or higher */

typedef Spi_DataBufferType EthSwt_30_Sja1105PQRS_LLSpiDataType;
#else
#  error "Only Autosar 4.x supported!"
#endif

/*! Field positions of SPI header. */
#define ETHSWT_30_SJA1105PQRS_LL_SPI_READ_ADDR_SHIFT                  (4U)
#define ETHSWT_30_SJA1105PQRS_LL_SPI_WRITE_ADDR_SHIFT                 (4U)
#define ETHSWT_30_SJA1105PQRS_LL_SPI_READ_WORDNUM_SHIFT              (25U)
#define ETHSWT_30_SJA1105PQRS_LL_SPI_WRITE_CMD_SHIFT                 (31U)

/*! Masks of SPI header */
#define ETHSWT_30_SJA1105PQRS_LL_SPI_WRITE_CMD_MASK          (0x80000000U)

/*! SPI word to byte calculation factor */
#define ETHSWT_30_SJA1105PQRS_LL_WORDS_TO_BYTE                        (4U)

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/
#define ETHSWT_30_SJA1105PQRS_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

STATIC ETHSWT_VAR_WITH_MEM(uint8, VAR_NOINIT, SJA1105PQRS) EthSwt_30_Sja1105PQRS_CurrentStackIdx[ETHSWT_30_SJA1105PQRS_SWITCH_NUM];

#define ETHSWT_30_SJA1105PQRS_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define ETHSWT_30_SJA1105PQRS_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* PRQA S 0779 2 */ /* MD_EthSwt_30_Sja1105PQRS_0779 */ /* PRQA S 3218 1 */ /* MD_EthSwt_30_Sja1105PQRS_3218 */
STATIC ETHSWT_VAR_WITH_MEM(EthSwt_30_Sja1105PQRS_SpiTransactionType, VAR_NOINIT, SJA1105PQRS) EthSwt_30_Sja1105PQRS_SpiTransactionStack[ETHSWT_30_SJA1105PQRS_SWITCH_NUM][ETHSWT_30_SJA1105PQRS_LL_TRANSACTION_STACK_SIZE];
STATIC ETHSWT_VAR_WITH_MEM(EthSwt_30_Sja1105PQRS_SpiBufferType, VAR_NOINIT, SJA1105PQRS) EthSwt_30_Sja1105PQRS_SpiTransactionBuffer[ETHSWT_30_SJA1105PQRS_SWITCH_NUM][ETHSWT_30_SJA1105PQRS_LL_TRANSACTION_STACK_SIZE];


#define ETHSWT_30_SJA1105PQRS_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define ETHSWT_30_SJA1105PQRS_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_SwapBytesSpi
 *********************************************************************************************************************/
/*! \brief      Swaps bytes within a data buffer depending on endianess.
 *  \details    -
 *  \param[in]  DataPtr                       The data that must be swapped
 *  \param[in]  DataLen                       Data length of data to be swapped
 *  \pre        Switch index must be valid
 *  \context    ANY
 *  \note       Compare with equally named activity in code design document
 *********************************************************************************************************************/
STATIC ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_LL_SwapBytesSpi(
    ETHSWT_P2VAR(uint32, SJA1105PQRS)  DataPtr,
                 uint16                DataLen);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_SwapBytesSpi
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
STATIC ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_LL_SwapBytesSpi(
    ETHSWT_P2VAR(uint32, SJA1105PQRS)  DataPtr,
                 uint16                DataLen)
{
  uint16_least Index;

  /* #10 Swap all bytes in buffer */
  for( Index = 0; Index < DataLen; Index++ )
  {
      DataPtr[Index] = IPBASE_HTON32(DataPtr[Index]);
  }
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_LL_Init( void )
{
  uint8_least LoopSwitchIdx;

  /* #10 Reset SPI transfer stack for all switches */
  for( LoopSwitchIdx = 0u; LoopSwitchIdx < ETHSWT_30_SJA1105PQRS_SWITCH_NUM; LoopSwitchIdx++ )
  {
    EthSwt_30_Sja1105PQRS_CurrentStackIdx[LoopSwitchIdx] = (uint8)0u;
  }
}

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_ReadBytesSync
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_LL_ReadBytesSync(
                   uint8                                                   SwitchIdx,
    ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS)  TransactionPtr)
{
  Std_ReturnType RetVal= (Std_ReturnType)E_NOT_OK;

  /* #10 Check for allowed number of words which shall be transfered */
  if (TransactionPtr->WordNum < (ETHSWT_30_SJA1105PQRS_LL_MAX_TRANSACTION_WORDS - 1))
  {
    /* #20 Enter exclusive area (Reason: Ensure consistency of SPI transfers) */
    /* PRQA S 0872 2 */ /* MD_EthSwt_30_Sja1105PQRS_0872 */
    /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
    EthSwt_EnterExclusiveArea(Sja1105PQRS, SPI_SEQUENCE);

    /* #30 Set read command and register address */
    EthSwt_30_Sja1105PQRS_SpiTransactionBuffer[SwitchIdx][TransactionPtr->TransactionId].SpiDataTx[0] = 0u;
    EthSwt_30_Sja1105PQRS_SpiTransactionBuffer[SwitchIdx][TransactionPtr->TransactionId].SpiDataTx[0] |=
        (uint32)((uint32)TransactionPtr->AddrIdx << (uint32)ETHSWT_30_SJA1105PQRS_LL_SPI_READ_ADDR_SHIFT);
    EthSwt_30_Sja1105PQRS_SpiTransactionBuffer[SwitchIdx][TransactionPtr->TransactionId].SpiDataTx[0] |=
        (uint32)((uint32)TransactionPtr->WordNum << (uint32)ETHSWT_30_SJA1105PQRS_LL_SPI_READ_WORDNUM_SHIFT);

    /* #40 Take care of endianess */
    EthSwt_30_Sja1105PQRS_LL_SwapBytesSpi(
        &EthSwt_30_Sja1105PQRS_SpiTransactionBuffer[SwitchIdx][TransactionPtr->TransactionId].SpiDataTx[0],
        1);

    /* #50 Setup SPI Data Channel for reception of SPI Data */
    RetVal = Spi_SetupEB(
        EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].LowerLayerData->SpiChannel,
        /* PRQA S 0310 4 */ /* MD_EthSwt_30_Sja1105PQRS_0310_SpiApi */
        (P2CONST(EthSwt_30_Sja1105PQRS_LLSpiDataType, AUTOMATIC, SPI_APPL_DATA))
            &EthSwt_30_Sja1105PQRS_SpiTransactionBuffer[SwitchIdx][TransactionPtr->TransactionId].SpiDataTx[0],
        /* PRQA S 0310 4 */ /* MD_EthSwt_30_Sja1105PQRS_0310_SpiApi */
        (P2VAR(EthSwt_30_Sja1105PQRS_LLSpiDataType, AUTOMATIC, SPI_APPL_DATA))
            &EthSwt_30_Sja1105PQRS_SpiTransactionBuffer[SwitchIdx][TransactionPtr->TransactionId].SpiDataRx[0],
        (VAR(Spi_NumberOfDataType, SPI_APPL_DATA))
            ((TransactionPtr->WordNum + 1) * ETHSWT_30_SJA1105PQRS_LL_WORDS_TO_BYTE));

    if( RetVal == (Std_ReturnType)E_OK )
    {
      /* #60 Start SPI transfer */
      RetVal = Spi_SyncTransmit(EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].LowerLayerData->SpiSequence);

      /* #70 Take care of endianess */
      EthSwt_30_Sja1105PQRS_LL_SwapBytesSpi(
          &EthSwt_30_Sja1105PQRS_SpiTransactionBuffer[SwitchIdx][TransactionPtr->TransactionId].SpiDataRx[1],
          TransactionPtr->WordNum);

      /* #80 Retrieve data */
      IpBase_Copy(TransactionPtr->DataPtr,
          &EthSwt_30_Sja1105PQRS_SpiTransactionBuffer[SwitchIdx][TransactionPtr->TransactionId].SpiDataRx[1],
          (TransactionPtr->WordNum * ETHSWT_30_SJA1105PQRS_LL_WORDS_TO_BYTE));
    }
    /* #90 Leave exclusive area */
    /* PRQA S 0872 2 */ /* MD_EthSwt_30_Sja1105PQRS_0872 */
    /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
    EthSwt_ExitExclusiveArea(Sja1105PQRS, SPI_SEQUENCE);
  }

  return RetVal;
}

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_WriteBytesSync
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_LL_WriteBytesSync(
                 uint8                                                   SwitchIdx,
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS)  TransactionPtr)
{
  Std_ReturnType RetVal = (Std_ReturnType)E_NOT_OK;

  /* #10 Check for allowed number of words which shall be transfered */
  if (TransactionPtr->WordNum < (ETHSWT_30_SJA1105PQRS_LL_MAX_TRANSACTION_WORDS - 1))
  {
    /* #20 Enter exclusive area (Reason: Ensure consistency of SPI transfers) */
    /* PRQA S 0872 2 */ /* MD_EthSwt_30_Sja1105PQRS_0872 */
    /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
    EthSwt_EnterExclusiveArea(Sja1105PQRS, SPI_SEQUENCE);

    /* #30 Set write command and register address */
    EthSwt_30_Sja1105PQRS_SpiTransactionBuffer[SwitchIdx][TransactionPtr->TransactionId].SpiDataTx[0] = 0;
    EthSwt_30_Sja1105PQRS_SpiTransactionBuffer[SwitchIdx][TransactionPtr->TransactionId].SpiDataTx[0] |=
        (uint32)ETHSWT_30_SJA1105PQRS_LL_SPI_WRITE_CMD_MASK;
    EthSwt_30_Sja1105PQRS_SpiTransactionBuffer[SwitchIdx][TransactionPtr->TransactionId].SpiDataTx[0] |=
        (uint32)(TransactionPtr->AddrIdx << (uint32)ETHSWT_30_SJA1105PQRS_LL_SPI_WRITE_ADDR_SHIFT);

    /* #40 Take care of endianess */
    EthSwt_30_Sja1105PQRS_LL_SwapBytesSpi(
        &EthSwt_30_Sja1105PQRS_SpiTransactionBuffer[SwitchIdx][TransactionPtr->TransactionId].SpiDataTx[0],
        (TransactionPtr->WordNum + 1u));

    /* #50 Setup SPI Data Channel for reception of SPI Data */
    /* PRQA S 0310 3 */ /* MD_EthSwt_30_Sja1105PQRS_0310_SpiApi */
    RetVal = Spi_SetupEB(
        EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].LowerLayerData->SpiChannel,
        (P2CONST(EthSwt_30_Sja1105PQRS_LLSpiDataType, AUTOMATIC, SPI_APPL_DATA))
            &EthSwt_30_Sja1105PQRS_SpiTransactionBuffer[SwitchIdx][TransactionPtr->TransactionId].SpiDataTx[0],
        (P2VAR(EthSwt_30_Sja1105PQRS_LLSpiDataType, AUTOMATIC, SPI_APPL_DATA))
            NULL_PTR,
        (VAR(Spi_NumberOfDataType, SPI_APPL_DATA))
            ((TransactionPtr->WordNum + 1u ) * ETHSWT_30_SJA1105PQRS_LL_WORDS_TO_BYTE));

    if( RetVal == (Std_ReturnType)E_OK )
    {
      /* #60 Start SPI transfer */
      RetVal = Spi_SyncTransmit(EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].LowerLayerData->SpiSequence);
    }

    /* #70 Leave exclusive area */
    /* PRQA S 0872 2 */ /* MD_EthSwt_30_Sja1105PQRS_0872 */
    /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
    EthSwt_ExitExclusiveArea(Sja1105PQRS, SPI_SEQUENCE);
  }

  return RetVal;
}

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_ReadU32Sync
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(
               uint8                                                   SwitchIdx,
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS)  TransactionPtr)
{
  TransactionPtr->WordNum = 1;
  return EthSwt_30_Sja1105PQRS_LL_ReadBytesSync(SwitchIdx, TransactionPtr);
}

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_WriteU32Sync
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(
               uint8                                                   SwitchIdx,
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS)  TransactionPtr)
{
  /* #10 Prepare transaction of one word and call internal SPI write function */
  TransactionPtr->WordNum = 1;
  return EthSwt_30_Sja1105PQRS_LL_WriteBytesSync(SwitchIdx, TransactionPtr);
}

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(
               uint8                                                   SwitchIdx,
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS) *TransactionPtr)
{
  Std_ReturnType RetVal;

  RetVal = (Std_ReturnType)E_NOT_OK;

  /* #10 Enter exclusive area (Reason: Ensure consistency of SPI transfers) */
  /* PRQA S 0872 2 */ /* MD_EthSwt_30_Sja1105PQRS_0872 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_EnterExclusiveArea(Sja1105PQRS, SPI_SEQUENCE);

  /* #20 Handle additional provide if possible */
  if( EthSwt_30_Sja1105PQRS_CurrentStackIdx[SwitchIdx] < (uint8)(ETHSWT_30_SJA1105PQRS_LL_TRANSACTION_STACK_SIZE - 1u) )
  {
    EthSwt_30_Sja1105PQRS_SpiTransactionStack[SwitchIdx][EthSwt_30_Sja1105PQRS_CurrentStackIdx[SwitchIdx]].TransactionId =
        EthSwt_30_Sja1105PQRS_CurrentStackIdx[SwitchIdx];
    EthSwt_30_Sja1105PQRS_SpiTransactionStack[SwitchIdx][EthSwt_30_Sja1105PQRS_CurrentStackIdx[SwitchIdx]].DataPtr =
        &EthSwt_30_Sja1105PQRS_SpiTransactionBuffer[SwitchIdx][EthSwt_30_Sja1105PQRS_CurrentStackIdx[SwitchIdx]].SpiDataTx[1];
    *TransactionPtr = &EthSwt_30_Sja1105PQRS_SpiTransactionStack[SwitchIdx][EthSwt_30_Sja1105PQRS_CurrentStackIdx[SwitchIdx]];
    EthSwt_30_Sja1105PQRS_CurrentStackIdx[SwitchIdx]++;

    RetVal = (Std_ReturnType)E_OK;
  }

  /* #30 Leave exclusive area */
  /* PRQA S 0872 2 */ /* MD_EthSwt_30_Sja1105PQRS_0872 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_ExitExclusiveArea(Sja1105PQRS, SPI_SEQUENCE);

  return RetVal;
}

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(
               uint8                                                   SwitchIdx,
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS)  TransactionPtr)
{
  uint16_least WordIdx;
  Std_ReturnType RetVal;

  RetVal = (Std_ReturnType)E_NOT_OK;

  /* #10 Enter exclusive area (Reason: Ensure consistency of SPI transfers) */
  /* PRQA S 0872 2 */ /* MD_EthSwt_30_Sja1105PQRS_0872 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_EnterExclusiveArea(Sja1105PQRS, SPI_SEQUENCE);

  /* #20 check if call can be processed */
  if( EthSwt_30_Sja1105PQRS_CurrentStackIdx[SwitchIdx] > 0U )
  {
    EthSwt_30_Sja1105PQRS_CurrentStackIdx[SwitchIdx]--;

    /* #30 Clear data */
    for( WordIdx = 0; WordIdx < TransactionPtr->WordNum; WordIdx++ )
    {
      TransactionPtr->DataPtr[WordIdx] = 0;
    }

    TransactionPtr->WordNum = 0;
    RetVal = (Std_ReturnType)E_OK;
  }

  /* #40 Leave exclusive area */
  /* PRQA S 0872 2 */ /* MD_EthSwt_30_Sja1105PQRS_0872 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_ExitExclusiveArea(Sja1105PQRS, SPI_SEQUENCE);

  return RetVal;
}

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_WriteRaw
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_LL_WriteRaw(
                 uint8            SwitchIdx,
  ETHSWT_P2CONST(uint32, SJA1105PQRS) DataPtr,
    ETHSWT_CONST(uint16, SJA1105PQRS) WordNum)
{
  Std_ReturnType RetVal;

  /* #10 Enter exclusive area (Reason: Ensure consistency of SPI transfers) */
  /* PRQA S 0872 2 */ /* MD_EthSwt_30_Sja1105PQRS_0872 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_EnterExclusiveArea(Sja1105PQRS, SPI_SEQUENCE);

  /* #20 Setup SPI Data Channel for reception of SPI Data */
  /* PRQA S 0310 3 */ /* MD_EthSwt_30_Sja1105PQRS_0310_SpiApi */
  RetVal = Spi_SetupEB(
        EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].LowerLayerData->SpiChannel,
        (P2CONST(EthSwt_30_Sja1105PQRS_LLSpiDataType, AUTOMATIC, SPI_APPL_DATA))DataPtr,
        (P2VAR(EthSwt_30_Sja1105PQRS_LLSpiDataType, AUTOMATIC, SPI_APPL_DATA))NULL_PTR,
        (VAR(Spi_NumberOfDataType, SPI_APPL_DATA))(WordNum * ETHSWT_30_SJA1105PQRS_LL_WORDS_TO_BYTE));

  if( RetVal == (Std_ReturnType)E_OK )
  {
    /* #30 Start SPI transfer */
    RetVal = Spi_SyncTransmit(EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].LowerLayerData->SpiSequence);
  }
  /* #40 Leave exclusive area */
  /* PRQA S 0872 2 */ /* MD_EthSwt_30_Sja1105PQRS_0872 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_ExitExclusiveArea(Sja1105PQRS, SPI_SEQUENCE);

  return RetVal;
}

#define ETHSWT_30_SJA1105PQRS_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* PRQA L:ETHSWT_30_SJA1105PQRS_LL_IF_NESTING_LEVEL */
/* PRQA L:ETHSWT_30_SJA1105PQRS_LL_INC_NESTING_LEVEL */
/* PRQA L:ETHSWT_30_SJA1105PQRS_LL_NO_OF_MACROS */
/* PRQA L:IDENTIFIER_DIFFER */

/* Module specific MISRA deviations:

    MD_EthSwt_30_Sja1105PQRS_0779:
      Reason:     Generated data structures can easily identified by their name and have a direct relation with the
                  configuration elements used in DaVinci Configurator Pro. However API infix increases the identifier
                  by a amount where is hardly possible to declare different identifiers.
      Risk:       No risk
      Prevention: Compile/link error if compiler doesn't support long identifiers.

    MD_EthSwt_30_Sja1105PQRS_0872:
      Reason:     Usage leads to a far better readability of the code.
      Risk:       No risk
      Prevention: Covered by review and compile/link tests.

    MD_EthSwt_30_Sja1105PQRS_0310_SpiApi:
      Reason:     API of Spi driver uses Spi driver specific data types to pass pointers to the TX and RX data.
                  Therefore the cast is needed to pass the data location.
      Risk:       There is no risk due to cast to a lesser strict alignment.
      Prevention: Covered by code review, compile/link and runtime tests.
 */

/**********************************************************************************************************************
 *  END OF FILE: EthSwt_30_Sja1105PQRS_LL.c
 *********************************************************************************************************************/
