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
/*!        \file  EthIf_Stats.h
 *        \brief  EthIf Stats public API header
 *
 *      \details  Provides access to the public API of the sub-module Stats of EthIf.
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

#if !defined (ETHIF_STATS_H)
# define ETHIF_STATS_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_Stats_Types.h"

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

/**********************************************************************************************************************
 * EthIf_GetTxStats
 **********************************************************************************************************************/
/*! \brief          Retrieves the transmission statistic counters.
 *  \details        Function redirects call to the Eth-driver to retrieve the transmission statistic counters defined
 *                  by AUTOSAR (see Eth-driver for more details). EthIf extends these statistics by additional counters for
 *                  the respective EthIf-controller. The counters provided by EthIf within the EthIf_TxStatsType are cleared
 *                  on read.
 *  \param[in]      CtrlIdx       EthIf controller identifier
 *  \param[out]     EthTxStats    Transmission statistics of the respective Eth-controller
 *  \param[out]     EthIfTxtSats  Transmission statistics of the EthIf-controller
 *  \return         E_OK - Statistics could be retrieved
 *  \return         E_NOT_OK - Wrong parameters or Eth-driver call isn't successful
 *  \pre            Respective EthIf controller is initialized
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \trace          DSGN-EthIf22981
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetTxStats(
        uint8                                         CtrlIdx,
  P2VAR(Eth_TxStatsType,   AUTOMATIC, ETHIF_APPL_VAR) EthTxStats,
  P2VAR(EthIf_TxStatsType, AUTOMATIC, ETHIF_APPL_VAR) EthIfTxStats);

/**********************************************************************************************************************
 * EthIf_GetRxStats
 **********************************************************************************************************************/
/*! \brief          Retrieves the reception statistic counters.
 *  \details        Function redirects call to the Eth-driver to retrieve the reception statistic counters defined
 *                  by AUTOSAR (see Eth-driver for more details). EthIf extends these statistics by additional counters for
 *                  the respective EthIf-controller. The counters provided by EthIf within the EthIf_RxStatsType are cleared
 *                  on read.
 *  \param[in]      CtrlIdx       EthIf controller identifier
 *  \param[out]     EthRxStats    Reception statistics of the respective Eth-controller
 *  \param[out]     EthIfRxtSats  Reception statistics of the EthIf-controller
 *  \return         E_NOT_OK - Wrong parameters or Eth-driver call isn't successful
 *  \return         E_OK - Statistics could be retrieved
 *  \pre            Respective EthIf controller is initialized
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \trace          DSGN-EthIf22980
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetRxStats(
        uint8                                         CtrlIdx,
  P2VAR(Eth_RxStatsType,   AUTOMATIC, ETHIF_APPL_VAR) EthRxStats,
  P2VAR(EthIf_RxStatsType, AUTOMATIC, ETHIF_APPL_VAR) EthIfRxStats);

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_19.1 */

#endif /* ETHIF_STATS_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_Stats.h
 *********************************************************************************************************************/

