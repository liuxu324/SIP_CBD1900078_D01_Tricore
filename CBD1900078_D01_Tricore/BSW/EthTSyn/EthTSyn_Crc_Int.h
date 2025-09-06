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
/**        \file  EthTSyn_Crc_Int.h
 *        \brief  EthTSyn internal header file for Crc handling
 *
 *      \details  Contains all macros and function declarations used by the EthTSyn to handle Crc calculation and
 *                validation
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
#if !defined (ETHTSYN_CRC_INT_H)
# define ETHTSYN_CRC_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthTSyn_Cfg.h"

# if (ETHTSYN_CRC_SUPPORT == STD_ON)
#  include "EthTSyn_Types.h"

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
#  define ETHTSYN_START_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  EthTSyn_Crc_ComputeTime0Crc
 *********************************************************************************************************************/
/*! \brief      Computes the uint8 Crc (CRC_TIME_0) for a TimeSecured FollowUp message.
 *  \details    -
 *  \param[in]  DataId          The DataId for the FollowUp
 *  \param[in]  Flags           The Flags determining which fields to use for the Crc calculation
 *  \param[in]  ComMsgPtr       Pointer to the common message header
 *  \return     The computed Crc (with the use Crc_CalculateCRC8H2F).
 *  \pre        For Tx: All Sub-Tlv information except the Crc itself are already copied to the Tx-Buffer
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(uint8, ETHTSYN_CODE) EthTSyn_Crc_ComputeTime0Crc(
                  uint8                      DataId,
                  uint8                      Flags,
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType)  ComMsgPtr);

/**********************************************************************************************************************
 *  EthTSyn_Crc_ComputeTime1Crc
 *********************************************************************************************************************/
/*! \brief      Computes the uint8 Crc (CRC_TIME_1) for a TimeSecured FollowUp message.
 *  \details    -
 *  \param[in]  DataId          The DataId for the FollowUp
 *  \param[in]  Flags           The Flags determining which fields to use for the Crc calculation
 *  \param[in]  ComMsgPtr       Pointer to the common message header
 *  \return     The computed Crc (with the use Crc_CalculateCRC8H2F).
 *  \pre        For Tx: All Sub-Tlv information except the Crc itself are already copied to the Tx-Buffer
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(uint8, ETHTSYN_CODE) EthTSyn_Crc_ComputeTime1Crc(
                  uint8                      DataId,
                  uint8                      Flags,
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType)  ComMsgPtr);

/**********************************************************************************************************************
 *  EthTSyn_Crc_ComputeStatusCrc
 *********************************************************************************************************************/
/*! \brief      Computes the uint8 Crc for a Status Secured FollowUp message.
 *  \details    -
 *  \param[in]  DataId               The DataId for the FollowUp
 *  \param[in]  StatusSecuredTlvPtr  Pointer to the Statues Secured Sub-Tlv of the FollowUp message
 *  \return     The computed Crc (CRC_Status) (with the use Crc_CalculateCRC8H2F).
 *  \pre        For Tx: All Sub-Tlv information except the Crc itself are already copied to the Tx-Buffer
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(uint8, ETHTSYN_CODE) EthTSyn_Crc_ComputeStatusCrc(
                  uint8                        DataId,
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvStatusType)  StatusSecuredTlvPtr);

/**********************************************************************************************************************
 *  EthTSyn_Crc_ComputeUserDataCrc
 *********************************************************************************************************************/
/*! \brief      Computes the uint8 Crc for a UserData Secured FollowUp message.
 *  \details    -
 *  \param[in]  DataId                 The DataId for the FollowUp
 *  \param[in]  UserDataSecuredTlvPtr  Pointer to the UserData Secured Sub-Tlv of the FollowUp message
 *  \return     The computed Crc (CRC_UserData) (with the use Crc_CalculateCRC8H2F).
 *  \pre        For Tx: All Sub-Tlv information except the Crc itself are already copied to the Tx-Buffer
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(uint8, ETHTSYN_CODE) EthTSyn_Crc_ComputeUserDataCrc(
                  uint8                          DataId,
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvUserDataType)  UserDataSecuredTlvPtr);

/**********************************************************************************************************************
 *  EthTSyn_Crc_ComputeOfsCrc
 *********************************************************************************************************************/
/*! \brief      Computes the uint8 Crc for a Ofs Secured FollowUp message.
 *  \details    -
 *  \param[in]  DataId            The DataId for the FollowUp
 *  \param[in]  OfsSecuredTlvPtr  Pointer to the Ofs Secured Sub-Tlv of the FollowUp message
 *  \return     The computed Crc (CRC_OFS) (with the use Crc_CalculateCRC8H2F).
 *  \pre        For Tx: All Sub-Tlv information except the Crc itself are already copied to the Tx-Buffer
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(uint8, ETHTSYN_CODE) EthTSyn_Crc_ComputeOfsCrc(
                  uint8                     DataId,
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvOfsType)  OfsSecuredTlvPtr);

/**********************************************************************************************************************
 *  EthTSyn_Crc_ValidateSubTlvCrc
 *********************************************************************************************************************/
/*! \brief      Validates the Crc for the given Ar Sub-Tlv of the FollowUp.
 *  \details    Computes the expected Crc of the provided Sub-Tlv, if it is a secured Sub-Tlv, and validates the Crc
 *              value carried in the Sub-Tlv itself.
 *  \param[in]  DataId       The DataId for the FollowUp
 *  \param[in]  ComMsgPtr    Pointer to the common message header
 *  \param[in]  ArSubTlvPtr  Pointer to the Ar Sub-Tlv of the FollowUp
 *  \return     TRUE - Crc is valid or Sub-Tlv without Crc was passed
 *  \return     False - Crc is invalid
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(boolean, ETHTSYN_CODE) EthTSyn_Crc_ValidateSubTlvCrc(
                  uint8                               DataId,
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType)           ComMsgPtr,
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvAbstractHeaderType) ArSubTlvPtr);


#  define ETHTSYN_STOP_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_19.1 */

# endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */
#endif /* ETHTSYN_CRC_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Crc_Int.h
 *********************************************************************************************************************/
