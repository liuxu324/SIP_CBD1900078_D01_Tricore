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
/*!        \file  EthIf_EthTrcv.h
 *        \brief  EthIf EthTrcv public API header
 *
 *      \details  Provides access to the public API of the sub-module EthTrcv of EthIf.
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

#if !defined (ETHIF_ETHTRCV_H)
# define ETHIF_ETHTRCV_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_EthTrcv_Types.h"

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

# if ( ETHIF_WAKEUP_SUPPORT == STD_ON )
/**********************************************************************************************************************
 * EthIf_SetTransceiverWakeupMode
 **********************************************************************************************************************/
/*! \brief          Changes the wakeup mode of the related hardware driver
 *  \details        Function allows to change the wakeup mode of the related hardware driver by redirecting the call
 *                  depending on the passed EcuM wakeup source.
 *  \param[in]      WakeupSource  EcuM wakeup source
 *  \param[in]      WakeupMode    Wakeup mode to set
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_WAKEUP_SUPPORT
 *  \trace          SPEC-2393948, SPEC-2393863
 *  \trace          DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SetTransceiverWakeupMode(
  EcuM_WakeupSourceType   WakeupSource,
  EthTrcv_WakeupModeType  WakeupMode);

/**********************************************************************************************************************
 * EthIf_GetTransceiverWakeupMode
 **********************************************************************************************************************/
/*! \brief          Retrieves the wakeup mode of the related hardware driver
 *  \details        Function allows to retrieve the wakeup mode of the related hardware driver by redirecting the call
 *                  depending on the passed EcuM wakeup source.
 *  \param[in]      WakeupSource   EcuM wakeup source
 *  \param[out]     WakeupModePtr  Pointer pointing to variable where the wakeup mode is stored to
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_WAKEUP_SUPPORT
 *  \trace          SPEC-2393950, SPEC-2393867
 *  \trace          DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetTransceiverWakeupMode(
        EcuM_WakeupSourceType                               WakeupSource,
  P2VAR(EthTrcv_WakeupModeType, AUTOMATIC, ETHIF_APPL_VAR)  WakeupModePtr);

/**********************************************************************************************************************
 * EthIf_CheckWakeup
 **********************************************************************************************************************/
/*! \brief          Initiates the wakeup check
 *  \details        Function allows to initiate the wakeup check of the related hardware driver by redirecting the call
 *                  depending on the passed EcuM wakeup source.
 *  \param[in]      WakeupSource    EcuM wakeup source
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_WAKEUP_SUPPORT
 *  \trace          SPEC-2393868, SPEC-2393871
 *  \trace          DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_CheckWakeup(
  EcuM_WakeupSourceType  WakeupSource);

/**********************************************************************************************************************
 * EthIf_VSetTransceiverWakeupMode
 **********************************************************************************************************************/
/*! \brief          Changes the wakeup mode of the related hardware drivers
 *  \details        Function allows to change the wakeup mode of the related hardware drivers by redirecting the call
 *                  depending on the passed EcuM wakeup source.
 *  \param[in]      CtrlIdx     EthIf controller index
 *  \param[in]      WakeupMode  Wakeup mode to set
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_WAKEUP_SUPPORT
 *  \trace          DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_VSetTransceiverWakeupMode(
  uint8                   CtrlIdx,
  EthTrcv_WakeupModeType  WakeupMode);

/**********************************************************************************************************************
 * EthIf_VGetTransceiverWakeupMode
 **********************************************************************************************************************/
/*! \brief          Retrieves the wakeup mode of the related hardware driver
 *  \details        Function allows to retrieve the wakeup mode of the related hardware driver by redirecting the call
 *                  depending on the passed EcuM wakeup source.
 *  \param[in]      CtrlIdx        EthIf controller index
 *  \param[out]     WakeupModePtr  Pointer pointing to variable where the wakeup mode is stored to
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_WAKEUP_SUPPORT
 *  \trace          DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_VGetTransceiverWakeupMode(
        uint8                                               CtrlIdx,
  P2VAR(EthTrcv_WakeupModeType, AUTOMATIC, ETHIF_APPL_VAR)  WakeupModePtr);

/**********************************************************************************************************************
 * EthIf_VCheckWakeup
 **********************************************************************************************************************/
/*! \brief          Initiates the wakeup check
 *  \details        Function allows to initiate the wakeup check of the related hardware drivers by redirecting the call
 *                  depending on the passed EthIf controller index.
 *  \param[in]      CtrlIdx  EthIf controller index
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_WAKEUP_SUPPORT
 *  \trace          DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_VCheckWakeup(
  uint8  CtrlIdx);

# endif /* ETHIF_WAKEUP_SUPPORT */

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_19.1 */

#endif /* ETHIF_ETHTRCV_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_EthTrcv.h
 *********************************************************************************************************************/

