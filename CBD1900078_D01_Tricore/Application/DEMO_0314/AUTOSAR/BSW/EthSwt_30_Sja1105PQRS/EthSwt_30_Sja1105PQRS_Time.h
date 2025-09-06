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
/*!        \file  EthSwt_30_Sja1105PQRS_Time.h
 *        \brief  Header file for access to the time stamping API
 *
 *      \details  The Ethernet Switch Driver allows to time stamp special frames (like PTP frames) received at it's
 *                ports. The API allows to trigger such time stamping or retrieve the respective time stamp of a frame.
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

#if !defined (ETHSWT_30_SJA1105PQRS_TIME_H)
#define ETHSWT_30_SJA1105PQRS_TIME_H

/* PRQA S 779,777 IDENTIFIER_DIFFER */ /* MD_EthSwt_30_Sja1105PQRS_5.1 */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "EthSwt_30_Sja1105PQRS_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* ----- API service IDs ----- */
/*!< Service ID: EthSwt_30_Sja1105PQRS_EnableEgressTimeStamp() */
#define ETHSWT_30_SJA1105PQRS_SID_ENABLE_EGRESS_TIME_STAMP_API                  (0xF1U)
/*!< Service ID: EthSwt_30_Sja1105PQRS_SetCorrectionTime() */
#define ETHSWT_30_SJA1105PQRS_SID_SET_CORRECTION_TIME_API                       (0xF2U)
/*!< Service ID: EthSwt_30_Sja1105PQRS_StartQbvSchedule() */
#define ETHSWT_30_SJA1105PQRS_SID_START_QBV_SCHEDULE_API                        (0xF3U)
/*!< Service ID: EthSwt_30_Sja1105PQRS_StopQbvSchedule() */
#define ETHSWT_30_SJA1105PQRS_SID_STOP_QBV_SCHEDULE_API                         (0xF4U)


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
#define ETHSWT_30_SJA1105PQRS_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if ( ETHSWT_30_SJA1105PQRS_GLOBAL_TIME_SUPPORT == STD_ON )

/***********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_MainFunctionTime()
 **********************************************************************************************************************/
/*! \brief         Main function for handling cyclic events for global time support
 *  \details       -
 *  \pre           Module is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_MainFunctionTime( void );

/***********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_EnableEgressTimeStamp()
 **********************************************************************************************************************/
/*! \brief         Enables time stamping in Ethernet switch for the frame identified by the passed data
 *  \details       This function enables timestamping for an Ethernet frame on a specific Ethernet switch port.
 *  \param[in]     EthCtrlIdx                 Identifier of the Ethernet controller the Ethernet frame is related to
 *  \param[in]     BufIdx                     Identifier of the transmission buffer within the context of the Ethernet
 *                                            controller
 *  \param[in]     MgmtInfo                   Management information
 *  \return        E_NOT_OK                   Timestamping for the Ethernet frame couldn't be enabled
 *  \return        E_OK                       Timestamping for the Ethernet frame enabled
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_EnableEgressTimeStamp(
                 uint8                              EthCtrlIdx,
                 uint8                              BufIdx,
  ETHSWT_P2CONST(EthSwt_MgmtInfoType, SJA1105PQRS)  MgmtInfo);

/***********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_SetCorrectionTime()
 **********************************************************************************************************************/
/*! \brief         Performs a correction of the switch clock
 *  \details       This function performs offset and rate correction of the switch clock.
 *  \param[in]     SwitchIdx      Index of the switch instance
 *  \param[in]     OffsetTimePtr  Offset the switch clock shall be corrected with
 *  \param[in]     RateRatioPtr   Rate the switch clock shall be corrected with
 *  \return        E_NOT_OK - SPI access failed or requested correction can't be applied
 *  \return        E_OK - Switch clock was corrected
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_SetCorrectionTime(
                 uint8                SwitchIdx,
  ETHSWT_P2CONST(Eth_TimeIntDiffType, SJA1105PQRS)  OffsetTimePtr,
  ETHSWT_P2CONST(float64,             SJA1105PQRS)  RateRatioPtr);

/***********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_StartQbvSchedule()
 **********************************************************************************************************************/
/*! \brief         Starts QBV traffic scheduling
 *  \details       This function starts QBV scheduling on the specified switch. There are two cases:
 *                  1. No switch has QBV traffic scheduling activated:
 *                     The QBV traffic scheduling will be started 1 ms later. This offset gives enough time for
 *                     the necessary SPI operations.
 *                  2. One or more switches have QBV traffic scheduling activated:
 *                     The QBV traffic scheduling will be started the next time the running QBV scheduling will
 *                     itself restart its cycle. If two or more switches are used the length of the QBV traffic
 *                     scheduling cycle should be the same.
 *  \param[in]     SwitchIdx      Index of the switch instance
 *  \return        E_OK - QBV scheduling was started
 *  \return        E_NOT_OK - SPI access failed or QBV already running
 *  \pre           Time must be synchronized on all connected switches.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_StartQbvSchedule(
                 uint8                SwitchIdx);

/***********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_StopQbvSchedule()
 **********************************************************************************************************************/
/*! \brief         Stops QBV traffic scheduling
 *  \details       This function stops QBV traffic scheduling on the specified switch.
 *  \param[in]     SwitchIdx      Index of the switch instance
 *  \return        E_OK - QBV scheduling was stopped
 *  \return        E_NOT_OK - SPI access failed or QBV scheduling already stopped
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_StopQbvSchedule(
                 uint8                SwitchIdx);

#endif /* ETHSWT_30_SJA1105PQRS_GLOBAL_TIME_SUPPORT */

#define ETHSWT_30_SJA1105PQRS_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* PRQA L:IDENTIFIER_DIFFER */


#endif /* ETHSWT_30_SJA1105PQRS_TIME_H */

/**********************************************************************************************************************
 *  END OF FILE: EthSwt_30_Sja1105PQRS_Time.h
 *********************************************************************************************************************/
