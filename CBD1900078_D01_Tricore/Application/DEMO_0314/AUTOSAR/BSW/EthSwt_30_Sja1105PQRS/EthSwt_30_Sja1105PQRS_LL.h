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
/*!        \file  EthSwt_30_Sja1105PQRS_LL.h
 *        \brief  Private header for internal low-level SPI and MII handling
 *
 *      \details  The Ethernet Switch Driver allows to configure and influence the operation of the NXP Sja1105PQRS
 *                switch connected to the SPI or MII interface of the Host MCU this driver runs on.
 *                The Module Header provides the global API and data structure prototypes, which are allowed to be
 *                used and accessed by other modules.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#ifndef ETHSWT_30_SJA1105PQRS_LL_H
#define ETHSWT_30_SJA1105PQRS_LL_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "EthSwt_30_Sja1105PQRS_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! Maximum number of words used by the upper layer */
#define ETHSWT_30_SJA1105PQRS_LL_MAX_TRANSACTION_WORDS  (8u)


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! Type holds data used between higher layer and lower layer to access the switch via SPI. */
typedef struct
{
  uint32* DataPtr;
  uint32  AddrIdx;
  uint16  WordNum;
  uint8  TransactionId;
} EthSwt_30_Sja1105PQRS_SpiTransactionType;

/*! Type holds data buffers passed to SPI driver to exchange data with switch. */
typedef struct
{
  uint32 SpiDataRx[ETHSWT_30_SJA1105PQRS_LL_MAX_TRANSACTION_WORDS];
  uint32 SpiDataTx[ETHSWT_30_SJA1105PQRS_LL_MAX_TRANSACTION_WORDS];
} EthSwt_30_Sja1105PQRS_SpiBufferType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define ETHSWT_30_SJA1105PQRS_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_Init
 *********************************************************************************************************************/
/*! \brief         Initializes the low level part of the Switch driver.
 *  \details       -
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_LL_Init( void );

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_ReadBytesSync
 *********************************************************************************************************************/
/*! \brief         Reads a bunch of data bytes of a given register.
 *  \details       -
 *  \param[in]     SwitchIdx                 Switch index
 *  \param[in,out] TransactionPtr            Spi Transaction data
 *  \return        E_OK                          The data was successfully read
 *  \return        E_NOT_OK                      SPI transmission error
 *  \pre           Switch index must be valid
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_LL_ReadBytesSync(
                 uint8                                                   SwitchIdx,
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS)  TransactionPtr);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_WriteBytesSync
 *********************************************************************************************************************/
/*! \brief         Writes a bunch of data bytes into a given register.
 *  \details       -
 *  \param[in]     SwitchIdx                 Switch index
 *  \param[in,out] TransactionPtr            Spi Transaction data
 *  \return        E_OK                      The data was successfully read
 *  \return        E_NOT_OK                  SPI transmission error
 *  \pre           Switch index must be valid
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_LL_WriteBytesSync(
                 uint8                                                   SwitchIdx,
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS)  TransactionPtr);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_ReadU32Sync
 *********************************************************************************************************************/
/*! \brief         Reads a 32-Bit register.
 *  \details       -
 *  \param[in]     SwitchIdx                 Switch index
 *  \param[in,out] TransactionPtr            Spi Transaction data
 *  \return        E_OK                      The data was successfully read
 *  \return        E_NOT_OK                  SPI transmission error
 *  \pre           Switch index must be valid
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(
               uint8                                                   SwitchIdx,
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS)  TransactionPtr);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_WriteU32Sync
 *********************************************************************************************************************/
/*! \brief         Writes a 32-Bit register.
 *  \details       -
 *  \param[in]     SwitchIdx                 Switch index
 *  \param[in,out] TransactionPtr            Spi Transaction data
 *  \return        E_OK                      The data was successfully read
 *  \return        E_NOT_OK                  SPI transmission error
 *  \pre           Switch index must be valid
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(
               uint8                                                   SwitchIdx,
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS)  TransactionPtr);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer
 *********************************************************************************************************************/
/*! \brief         Provide a SpiTransactionBuffer for SPI data transmission
 *                 MII. The API ensures that the register data is returned in the proper host byte order.
 *  \details       -
 *  \param[in]     SwitchIdx                     Switch index
 *  \param[out]    TransactionPtr                Pointer to the SpiTransactionBuffer which is provided when function
 *                                               succeeds
 *  \return        E_OK                          SpiTransactionBuffer was provided
 *  \return        E_NOT_OK                      SpiTransactionBuffer could not be provided
 *  \pre           Switch index must be valid
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(
               uint8                                                   SwitchIdx,
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS) *TransactionPtr);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer
 *********************************************************************************************************************/
/*! \brief         Releases a SpiTransactionBuffer
 *                 MII. The API ensures that the register data is returned in the proper host byte order.
 *  \details       -
 *  \param[in]     SwitchIdx                     Switch index
 *  \param[out]    TransactionPtr                Pointer to the SpiTransactionBuffer which is released when function
 *                                               succeeds
 *  \return        E_OK                          SpiTransactionBuffer was released
 *  \return        E_NOT_OK                      SpiTransactionBuffer could not be released
 *  \pre           Switch index must be valid
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(
               uint8                                                   SwitchIdx,
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS)  TransactionPtr);


/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_WriteRaw
 *********************************************************************************************************************/
/*! \brief         Configuration Block is written to the Sja1105PQRS configuration area via SPI
 *  \details       -
 *  \param[in]     SwitchIdx                     Switch index
 *  \param[in]     DataPtr                       Pointer to the configuration block to be transmitted
 *  \param[in]     WordNum                       Number of words (32 Bit) to be transmitted
 *  \return        E_OK                          Transmission of the configuration block was successful
 *  \return        E_NOT_OK                      Transmission of the failed
 *  \pre           Switch index must be valid, Sja1105PQRS switch must be in configuration mode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_LL_WriteRaw(
                 uint8                 SwitchIdx,
  ETHSWT_P2CONST(uint32, SJA1105PQRS)  DataPtr,
    ETHSWT_CONST(uint16, SJA1105PQRS)  WordNum);

#define ETHSWT_30_SJA1105PQRS_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  END OF FILE: EthSwt_30_Sja1105PQRS_LL.h
 *********************************************************************************************************************/
#endif /* ETHSWT_30_SJA1105PQRS_LL_H */
