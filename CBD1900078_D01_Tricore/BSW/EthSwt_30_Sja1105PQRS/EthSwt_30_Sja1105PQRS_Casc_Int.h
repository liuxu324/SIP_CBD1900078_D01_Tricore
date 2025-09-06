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
/*!        \file  EthSwt_30_Sja1105PQRS_Casc_Int.h
 *        \brief  Header file for access to the internal cascaded related API
 *
 *      \details  The Ethernet Switch Driver allows to control Ethernet switches in a cascaded setup. This file
 *                contains the declartions of APIs related to this functionality.
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

#if !defined (ETHSWT_30_SJA1105PQRS_CASC_INT_H)
#define ETHSWT_30_SJA1105PQRS_CASC_INT_H

/* PRQA S 779,777 IDENTIFIER_DIFFER */ /* MD_EthSwt_30_Sja1105PQRS_5.1 */
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "EthSwt_30_Sja1105PQRS_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*! Maximum counter value for the buckets */
#define ETHSWT_30_SJA1105PQRS_MAX_BUCKET_CNT           (0xFEu)

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

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_GetIndexOfDirectlyConnectedSwitch()
 *********************************************************************************************************************/
/*! \brief       Queries for the switch instance that is first in the cascading hierarchy (directly connected to
 *               Host-CPU)
 *  \details     -
 *  \return      Index of the switch instance
 *  \pre         -
 *********************************************************************************************************************/
ETHSWT_FUNC(EthSwt_SwitchIdxType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetIndexOfDirectlyConnectedSwitch( void );

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_IsUplinkPort()
 **********************************************************************************************************************/
/*! \brief Checks if the passed port is a uplink to another switch
 *  \details     -
 *  \param[in]   swtIdx  Index of the switch the port is related to
 *  \param[in]   portIdx Index of the port
 *  \return      FALSE - Port isn't an uplink to another switch
 *  \return      TRUE - Port is an uplink to another switch
 *  \pre         -
 **********************************************************************************************************************/
ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_IsUplinkPort(
  EthSwt_SwitchIdxType swtIdx,
  EthSwt_PortIdxType   portIdx);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_GetLocalUplinkPortForRemoteUplink()
 *********************************************************************************************************************/
/*! \brief Retrieves the port of a switch related to the uplink of another switch
 *  \details     -
 *  \param[in]   remSwtIdx   Index of the other switch
 *  \param[in]   locSwtIdx   Index of the switch the port shall be retrieved for
 *  \return      ETHSWT_30_SJA1105PQRS_INVALID_PORT_IDX - if no related port was found
 *  \return      Index of the port - if port was found
 *  \pre         -
 *********************************************************************************************************************/
ETHSWT_FUNC(EthSwt_PortIdxType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetLocalUplinkPortForRemoteUplink(
               EthSwt_SwitchIdxType           remSwtIdx,
               EthSwt_PortIdxType             locSwtIdx);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_IsAnyBucketRequested()
 **********************************************************************************************************************/
/*! \brief Checks if any bucket of the passed buckets is active
 *  \details     -
 *  \param[in]   buckets  Buckets that shall be checked
 *  \return      FALSE - no bucket active
 *  \return      TRUE - at least one bucket active
 *  \pre         -
 **********************************************************************************************************************/
ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_IsAnyBucketRequested(
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_PortBucketsType, SJA1105PQRS) buckets);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_UpdateUplinkPortBuckets()
 **********************************************************************************************************************/
/*! \brief Checks if buckets of different switches are active and dependent on that updates the activation of the
 *         uplink ports connecting them
 *  \details     -
 *  \param[in]   buckets  Buckets that shall be checked
 *  \pre         -
 **********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_UpdateUplinkPortBuckets(
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_PortBucketsType, SJA1105PQRS) buckets);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_CreatePortMasksFromBuckets()
 **********************************************************************************************************************/
/*! \brief  Creates a port mask for each switch having the ports active that are active in the buckets
 *  \details     -
 *  \param[in]   buckets    Buckets containing the port activation states
 *  \param[out]  portMasks  Pointer to the location where the port masks that are created shall be stored
 *  \pre         -
 **********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_CreatePortMasksFromBuckets(
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_PortBucketsType, SJA1105PQRS) buckets,
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_PortMaskType, SJA1105PQRS)      portMasks);

#define ETHSWT_30_SJA1105PQRS_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* PRQA L:IDENTIFIER_DIFFER */


#endif /* ETHSWT_30_SJA1105PQRS_CASC_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthSwt_30_Sja1105PQRS_Casc_Int.h
 *********************************************************************************************************************/
