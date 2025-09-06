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
/*!        \file  EthSwt_30_Sja1105PQRS_Types.h
 *        \brief  Private Type Header of Ethernet Switch Driver for NXP SJA1105PQRS Ethernet switch.
 *
 *      \details  The Private Type Header contains the data types used.
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

#ifndef ETHSWT_30_SJA1105PQRS_TYPES_H
#define ETHSWT_30_SJA1105PQRS_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "EthSwt_GeneralTypes.h"
#include "EthSwt_30_Sja1105PQRS_Cfg.h"
#include "EthTrcv_GeneralTypes.h"

#if(    (STD_ON == ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED) \
     || (STD_ON == ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED) )
#include "NvM.h"
#endif /* ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED, ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED */
#include "Spi.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! Transceiver index don't care value
 *
 *  Value must not be used within static code! 0xFFU is a valid transceiver index. The define is only
 *  used in GenData instead of a magic number.
 */
#define ETHSWT_30_SJA1105PQRS_TRCV_IDX_DONT_CARE                                                                 (0xFFu)

/*! VLAN ID don't care value */
#define ETHSWT_30_SJA1105PQRS_VLAN_ID_DONT_CARE                                                                (0xFFFFu)

/*! Number of counters passed by EthSwt_30_Sja1105PQRS_GetDropCount() */
#define ETHSWT_30_SJA1105PQRS_DROP_COUNT_COUNTERS_NUM                                                              (14u)

/*! Mask for Multicast-Address checking
 *
 *  Mask is used to check if first byte of MAC address defines address as a multicast address.
 */
#define ETHSWT_30_SJA1105PQRS_MULTICAST_CHECK_MASK_8BIT                                                          (0x01u)

/*! Port Index don't care value */
#define ETHSWT_30_SJA1105PQRS_PORT_DONT_CARE                                                                     (0xFFu)

/*! Invalid port number */
#define ETHSWT_30_SJA1105PQRS_PORT_INVALID                                                                       (0x07u)

/*! Number of possible PCP values of VLAN tag */
#define ETHSWT_30_SJA1105PQRS_PCP_NUM                                                                               (8u)

/*! xMII PHY type */
#define ETHSWT_30_SJA1105PQRS_XMII_PHY_MANAGED_BY_MCU                                                            (0x00u)
#define ETHSWT_30_SJA1105PQRS_XMII_PHY_MANAGED_BY_SWITCH                                                         (0x01u)
#define ETHSWT_30_SJA1105PQRS_XMII_NO_PHY                                                                        (0x02u)
#define ETHSWT_30_SJA1105PQRS_XMII_PHY_DONT_CARE                                                                 (0xFFu)

/*! Transformation direction values for EthSwt_30_Sja1105PQRS_TransformPortIdx() API. */
#define ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_INTERNAL_VIEW                                            (0u)
#define ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_EXTERNAL_VIEW                                            (1u)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 3 */ /* MD_MSR_19.7 */
/*! Macro for Multicast-Address check for most significant byte of MAC address */
#define EthSwt_30_Sja1105PQRS_IsMulticastAddress(MostSigMacAddrByte) \
    (boolean)((MostSigMacAddrByte) & ETHSWT_30_SJA1105PQRS_MULTICAST_CHECK_MASK_8BIT)

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! EthSwt_30_Sja1105PQRS_TrcvCalloutFctsType holds all necessary API function for an Ethernet Transceiver
 *  connected to a switch port.
 *
 *  The Ethernet Transceivers connected to switch ports (internal or external) are implemented in
 *  independent modules. This modules are implemented according to the AUTOSAR SWS for the Ethernet Transceiver
 *  Driver and provide an API to control the transceivers behavior.
 */
typedef struct
{
  Std_ReturnType (* const SetTrcvMode)(uint8 TrcvIdx, EthTrcv_ModeType TrcvMode);               /**< EthTrcv_xyz_SetTransceiverMode() */
  Std_ReturnType (* const GetTrcvMode)(uint8 TrcvIdx, EthTrcv_ModeType *TrcvModePtr);           /**< EthTrcv_xyz_GetTransceiverMode() */
  Std_ReturnType (* const StartAutoNegotiation)(uint8 TrcvIdx);                                 /**< EthTrcv_xyz_StartAutoNegotiation() */
  Std_ReturnType (* const GetLinkState)(uint8 TrcvIdx, EthTrcv_LinkStateType *LinkStatePtr);    /**< EthTrcv_xyz_GetLinkState() */
  Std_ReturnType (* const GetBaudRate)(uint8 TrcvIdx, EthTrcv_BaudRateType *BaudRatePtr);       /**< EthTrcv_xyz_GetBaudRate() */
  Std_ReturnType (* const GetDuplexMode)(uint8 TrcvIdx, EthTrcv_DuplexModeType *DuplexModePtr); /**< EthTrcv_xyz_GetDuplexMode() */
  Std_ReturnType (* const TrcvInit)(uint8 TrcvIdx, uint8 ConfigIdx);                            /**< EthTrcv_xyz_TransceiverInit() */
} EthSwt_30_Sja1105PQRS_TrcvCalloutFctsType;

typedef struct {
  boolean EnableMgmtRoute;
  boolean EnableTimeStamp;
  uint8   TsReg;
} EthSwt_30_Sja1105PQRS_MgmtRouteCfgType;

typedef struct EthSwt_30_Sja1105PQRS_MirrorEntityStruct
{
  EthSwt_PortMirrorStateType MirrorStatus;
  EthSwt_PortMirrorCfgType   MirrorConfig;
} EthSwt_30_Sja1105PQRS_MirrorEntityType;

typedef struct EthSwt_30_Sja1105PQRS_MirrorInfoStruct
{
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_MirrorEntityType, SJA1105PQRS)  MirrorEntity;
  uint8 NvmBlockId;
} EthSwt_30_Sja1105PQRS_MirrorInfoType;

/* PRQA S 0779 2 */ /* MD_EthSwt_30_Sja1105PQRS_0779 */
/*! Result of a write access to lookup table. */
typedef uint8 EthSwt_30_Sja1105PQRS_L2LookupTableWriteResultType;
# define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_WRITE_OK                                                             (0u)
# define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_WRITE_OCCUPIED                                                       (1u)

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/



#endif  /* ETHSWT_30_SJA1105PQRS_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: EthSwt_30_Sja1105PQRS_Types.h
 *********************************************************************************************************************/

