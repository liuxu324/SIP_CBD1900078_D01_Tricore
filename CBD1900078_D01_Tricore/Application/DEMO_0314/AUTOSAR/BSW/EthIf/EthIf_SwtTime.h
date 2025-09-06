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
/*!        \file  EthIf_SwtTime.h
 *        \brief  EthIf SwtTime public API header
 *
 *      \details  Provides access to the public API of the sub-module SwtTime of EthIf.
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

#if !defined (ETHIF_SWTTIME_H)
# define ETHIF_SWTTIME_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_SwtTime_Types.h"

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

# define ETHIF_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# if ( ETHIF_ETHSWT_TIME_STAMP_SUPPORT == STD_ON )                                                                      /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 * EthIf_SwitchEnableEgressTimeStamp
 **********************************************************************************************************************/
/*! \brief          Enables time stamping within the Ethernet switch for an Ethernet frame.
 *  \details        Function enables time stamping for an Ethernet frame identified by the buffer index on the
 *                  port described by the management information.
 *  \param[in]      EthIfCtrlIdx  Index of the EthIf controller
 *  \param[in]      BufIdx        Index of the Ethernet Tx buffer retrieved during EthIf_ProvideTxBuffer()
 *  \param[in]      MgmtInfo      Switch Management information
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters
 *  \pre            Buffer has to be acquired with EthIf_ProvideTxBuffer()
 *  \context        ANY
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \note           Further context restriction:
 *                  Call only allowed between EthIf_ProvideTxBuffer()/EthIf_ProvideExtTxBuffer() and EthIf_Transmit()
 *                  for a specific frame
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SwitchEnableEgressTimeStamp(
          uint8                                             EthIfCtrlIdx,
          uint8                                             BufIdx,
  P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, ETHIF_APPL_DATA)  MgmtInfo);
# endif /* ETHIF_ETHSWT_TIME_STAMP_SUPPORT */

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_19.1 */

#endif /* ETHIF_SWTTIME_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_SwtTime.h
 *********************************************************************************************************************/

