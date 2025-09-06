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
/*!        \file  EthSwt_30_Sja1105PQRS_Mirror.h
 *        \brief  Header file for access to the mirroring related API
 *
 *      \details  Contains the public API declaration to access the functionality of the mirror submodule.
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

#if !defined (ETHSWT_30_SJA1105PQRS_MIRROR_H)
# define ETHSWT_30_SJA1105PQRS_MIRROR_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthSwt_30_Sja1105PQRS_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* ----- API service IDs ----- */
/*!< Service ID: EthSwt_30_Sja1105PQRS_WritePortMirrorConfiguration() */
# define ETHSWT_30_SJA1105PQRS_SID_WRITE_PORT_MIRROR_CONFIGURATION   (0x36u)
/*!< Service ID: EthSwt_30_Sja1105PQRS_ReadPortMirrorConfiguration() */
# define ETHSWT_30_SJA1105PQRS_SID_READ_PORT_MIRROR_CONFIGURATION    (0x37u)
/*!< Service ID: EthSwt_30_Sja1105PQRS_GetPortMirrorState() */
# define ETHSWT_30_SJA1105PQRS_SID_GET_PORT_MIRROR_STATE             (0x38u)
/*!< Service ID: EthSwt_30_Sja1105PQRS_SetPortMirrorState() */
# define ETHSWT_30_SJA1105PQRS_SID_SET_PORT_MIRROR_STATE             (0x39u)
/*!< Service ID: EthSwt_30_Sja1105PQRS_DeletePortMirrorConfiguration() */
# define ETHSWT_30_SJA1105PQRS_SID_DELETE_PORT_MIRROR_CONFIGURATION  (0x55u)

/*!< Possible return value for EthSwt_30_Sja1105PQRS_WritePortMirrorConfiguration: Given configuration did not validate */
# define ETHSWT_PORT_MIRRORING_CONFIGURATION_NOT_SUPPORTED (2u)

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

# define ETHSWT_30_SJA1105PQRS_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_MirrorInit()
 *********************************************************************************************************************/
/*! \brief       Initializes mirroring for the specified switch
 *  \details     This function initializes mirroring for the specified switch
 *  \param[in]   switchIdx           Identifier of the switch
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, ETHSWT_30_SJA1105PQRS_CODE) EthSwt_30_Sja1105PQRS_MirrorInit( uint8 switchIdx ); /* PRQA S 3219 */ /* MD_EthSwt_30_Sja1105PQRS_3219 */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_WritePortMirrorConfiguration()
 *********************************************************************************************************************/
/*! \brief         Write port mirroring configuration into internal buffer
 *  \details       This function validates the given port mirroring configuration and writes it into an internal
 *                 buffer in the microcontroller. The stored configuration will be written into the switch later
 *                 when the function EthSwt_30_Sja1105PQRS_SetPortMirrorState() is called to set the mirroring state to
 *                 active.
 *  \param[in]     mirroredSwitchIdx           Identifier of the switch which shall get the new configuration
 *  \param[in]     portMirrorConfigurationPtr  Pointer to the new configuration
 *  \return        ETHSWT_PORT_MIRRORING_CONFIGURATION_NOT_SUPPORTED - Port mirroring configuration is invalid
 *  \return        E_NOT_OK - Error writing configuration
 *  \return        E_OK - Port mirroring configuration is valid and has been saved to buffer
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \trace         CREQ-162957
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHSWT_30_SJA1105PQRS_CODE) EthSwt_30_Sja1105PQRS_WritePortMirrorConfiguration(
          uint8                                                                               mirroredSwitchIdx,
  P2CONST(EthSwt_PortMirrorCfgType, ETHSWT_30_SJA1105PQRS_CONST, ETHSWT_30_SJA1105PQRS_CONST) portMirrorConfigurationPtr);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_ReadPortMirrorConfiguration()
 *********************************************************************************************************************/
/*! \brief         Read port mirroring configuration from internal buffer
 *  \details       This function reads the current mirroring configuration of the specified switch from the internal
 *                 buffer in the microcontroller.
 *  \param[in]     mirroredSwitchIdx           Identifier of switch which configuration shall be read
 *  \param[out]    portMirrorConfigurationPtr  Pointer to buffer where configuration shall be stored
 *  \return        E_NOT_OK - No port mirroring configuration has been found
 *  \return        E_OK - Retrieval of port mirroring configuration has been successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \trace         CREQ-162958
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHSWT_30_SJA1105PQRS_CODE) EthSwt_30_Sja1105PQRS_ReadPortMirrorConfiguration(
        uint8                                                                             mirroredSwitchIdx,
  P2VAR(EthSwt_PortMirrorCfgType, ETHSWT_30_SJA1105PQRS_CONST, ETHSWT_30_SJA1105PQRS_VAR) portMirrorConfigurationPtr);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetPortMirrorState()
 *********************************************************************************************************************/
/*! \brief         Get current port mirroring state
 *  \details       This function returns the current port mirroring state of the specified switch.
 *  \param[in]     mirroredSwitchIdx           Identifier of switch which state shall be read
 *  \param[out]    portMirrorStatePtr          Pointer to variable where state shall be stored
 *  \return        E_NOT_OK - Error getting port mirroring state
 *  \return        E_OK - Retrieval of port mirroring state has been successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \trace         CREQ-162956
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHSWT_30_SJA1105PQRS_CODE) EthSwt_30_Sja1105PQRS_GetPortMirrorState(
        uint8                                                                               mirroredSwitchIdx,
  P2VAR(EthSwt_PortMirrorStateType, ETHSWT_30_SJA1105PQRS_CONST, ETHSWT_30_SJA1105PQRS_VAR) portMirrorStatePtr);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_SetPortMirrorState()
 *********************************************************************************************************************/
/*! \brief         Set new port mirroring state
 *  \details       This function sets the new port mirroring state of the specified switch.
 *  \param[in]     mirroredSwitchIdx           Identifier of switch which state shall be written
 *  \param[in]     portMirrorState             New port mirroring state
 *  \return        E_NOT_OK - Error setting port mirroring state
 *  \return        E_OK - Setting of port mirroring state has been successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \trace         CREQ-162955
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHSWT_30_SJA1105PQRS_CODE) EthSwt_30_Sja1105PQRS_SetPortMirrorState(
        uint8                      mirroredSwitchIdx,
        EthSwt_PortMirrorStateType portMirrorState);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_DeletePortMirrorConfiguration()
 *********************************************************************************************************************/
/*! \brief         Delete stored mirroring configuration
 *  \details       This function deletes the port mirroring configuration of the specified switch. This is only
 *                 only possible if the port mirroring state is PORT_MIRRORING_DISABLED.
 *  \param[in]     mirroredSwitchIdx           Identifier of switch which configuration shall be deleted
 *  \return        E_NOT_OK - Error deleting port mirroring configuration
 *  \return        E_OK - Deleting of port mirroring configuration has been successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \trace         CREQ-162959
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHSWT_30_SJA1105PQRS_CODE) EthSwt_30_Sja1105PQRS_DeletePortMirrorConfiguration(
        uint8                      mirroredSwitchIdx);

# define ETHSWT_30_SJA1105PQRS_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_19.1 */

#endif /* ETHSWT_30_SJA1105PQRS_MIRROR_H */

/**********************************************************************************************************************
 *  END OF FILE: EthSwt_30_Sja1105PQRS_Mirror.h
 *********************************************************************************************************************/
