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
/*!        \file  EthSwt_30_Sja1105PQRS_Time_Int.h
 *        \brief  Internal header of the timestamping module of Ethernet Switch Driver for NXP Sja1105PQRS
 *
 *      \details  The internal sub module header contains the data types and functions used to access and interact with
 *                the timestamping module of the driver.
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

#if !defined (ETHSWT_30_SJA1105PQRS_TIME_INT_H)
# define ETHSWT_30_SJA1105PQRS_TIME_INT_H

#if (ETHSWT_30_SJA1105PQRS_GLOBAL_TIME_SUPPORT == STD_ON)
/* PRQA S 779,777 IDENTIFIER_DIFFER */ /* MD_EthSwt_30_Sja1105PQRS_5.1 */
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#  include "EthSwt_30_Sja1105PQRS_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_TimeInit
 *********************************************************************************************************************/
/*! \brief         Initializes the timestamping sub module of the driver
 *  \details       -
 *  \pre           -
 *********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_TimeInit( void );

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_ConfigureQbv
 *********************************************************************************************************************/
/*! \brief         Initializes some IEEE802.1Qbv related registers
 *  \details       -
 *  \pre           -
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_ConfigureQbv(
  uint8 swtIdx);

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_FinalizePrepOfTxTsRetrieval
 **********************************************************************************************************************/
/*! \brief         Finalizes the preparation of a timestamp processing element of a frame intended to be transmitted
 *  \details       -
 *  \param[in]     ethCtrlIdx    Identifier of the Ethernet controller the frame shall be transmitted on
 *  \param[in]     bufIdx        Identifier of the Frame buffer in context of the Ethernet controller used to transmit
 *                               the frame
 *  \param[in]     lenByte       Length used by the frame transmission initiator to transmit the frame
 *  \param[in]     dataPtr       Memory location of the transmission buffer used to transmit the frame
 *  \pre           -
 **********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_FinalizePrepOfTxTsRetrieval(
        uint8                                                          ethCtrlIdx,
        uint8                                                          bufIdx,
  P2VAR(uint8,                 AUTOMATIC, AUTOMATIC)                   dataPtr,
  P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, AUTOMATIC)                   mgmtInfo,
  P2CONST(EthSwt_30_Sja1105PQRS_TsProcElemType, AUTOMATIC, AUTOMATIC) *TsProcElemPtr);

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_InitiateTxTsRetrieval
 **********************************************************************************************************************/
/*! \brief         Initiates the timestamp retrieval a frame intended to be transmitted
 *  \details       -
 *  \param[in]     ethCtrlIdx    Identifier of the Ethernet controller the frame was received on
 *  \param[in]     bufIdx        Identifier of the Frame buffer in context of the Ethernet controller used to transmit
 *                               the frame
 *  \pre           -
 **********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_InitiateTxTsRetrieval(
  uint8                                               ethCtrlIdx,
  uint8                                               bufIdx,
  P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, AUTOMATIC)  mgmtInfo);

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_InitiateRxTsRetrieval
 **********************************************************************************************************************/
/*! \brief         Initiates the timestamp retrieval a frame received
 *  \details       -
 *  \param[in]     ethCtrlIdx    Identifier of the Ethernet controller the frame was received on
 *  \param[in]     dataPtr       Memory location of the reception buffer used for the received frame
 *  \param[in]     mgmtInfo      Management information containing information about the port the frame was received on
 *  \pre           -
 **********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_InitiateRxTsRetrieval(
          uint8                                                     ethCtrlIdx,
    P2VAR(uint8,                              AUTOMATIC, AUTOMATIC) dataPtr,
  P2CONST(EthSwt_MgmtInfoType,                AUTOMATIC, AUTOMATIC) mgmtInfo);

/***********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_SynchronizeSwitchToCasMaster()
 **********************************************************************************************************************/
/*! \brief         Synchronizes the clock of a switch to the master switch using offset correction
 *  \details       Functions synchronizes a switch to the master switch with respect to the offset between the switch
 *                 clocks by utilizing the sync line the switches are connected with and the respective mechanism to
 *                 get the offset between the switches.
 *  \param[in]     syncSwtIdx  Index of switch to be synchronized to master switch
 *  \return        E_NOT_OK    There is no master switch or there are SPI transaction problems
 *  \return        E_OK        Switch was synchronized to master with respect to its offset
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_SynchronizeSwitchToCasMaster(
  uint8  syncSwtIdx);

/* PRQA L:IDENTIFIER_DIFFER */

# endif /* ETHSWT_30_SJA1105PQRS_GLOBAL_TIME_SUPPORT == STD_ON */
#endif  /* ETHSWT_30_SJA1105PQRS_TIME_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthSwt_30_Sja1105PQRS_Time_Int.h
 *********************************************************************************************************************/

