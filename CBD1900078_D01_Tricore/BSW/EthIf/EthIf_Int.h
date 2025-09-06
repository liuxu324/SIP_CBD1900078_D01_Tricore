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
/*!        \file  EthIf_Int.h
 *        \brief  Ethernet Interface internal header file
 *
 *      \details  Component to abstract the underlying Ethernet hardware for the upper layers to provide a generic
 *                interface to be used for controlling and communicate with the help of the Ethernet hardware
 *                provided by an ECU (Ethernet controller, Ethernet transceiver, Ethernet switch).
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

#if !defined(ETHIF_INT_H)
# define ETHIF_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1977
 *********************************************************************************************************/
# include "EthIf_Types.h"
# include "EthIf_Lcfg.h"

/* includes of foreign modules shared for all EthIf modules */
# include "SchM_EthIf.h"
# include "IpBase.h"
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
#  include "Det.h"
# endif

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# if !defined (ETHIF_INT_INLINE)                                                                                        /* COV_ETHIF_LOCAL_INLINE */
#  define ETHIF_INT_INLINE  LOCAL_INLINE
# endif

# define ETHIF_UINT16_UPPER_BYTE_MASK (0xFF00u)
# define ETHIF_UINT16_LOWER_BYTE_MASK (0x00FFu)
# define ETHIF_BYTE_SHIFT_VAL              (8u)

/* ----- Ethernet Frame structure ----- */
/*! Length of the Ethernet header without VLAN tag consideration */
# define ETHIF_HDR_LEN_BYTE            (14U)
/*! Offset into the Ethernet frame to EtherType location */
# define ETHIF_FRAME_TYPE_OFFSET       (12U)
/*! Minimum Ethernet Frame lenght */
# define ETHIF_MIN_ETH_FRAME_LEN_BYTE  (60U)

/* ----- VLAN Tag structure ----- */
/* TCI structure according to IEEE802.1Q */
# define ETHIF_VLAN_TCI_VID_SHIFT               (0U)
# define ETHIF_VLAN_TCI_DEI_SHIFT               (12U)
# define ETHIF_VLAN_TCI_PCP_SHIFT               (13U)
# define ETHIF_VLAN_TCI_VID_MASK                (0x0FFFU)
# define ETHIF_VLAN_TCI_DEI_MASK                (0x1000U)
# define ETHIF_VLAN_TCI_PCP_MASK                (0xE000U)
/* VLAN TPID according to IEEE802.1Q */
# define ETHIF_VLAN_TPID_UB                     (0x81U)
# define ETHIF_VLAN_TPID_LB                     (0x00U)
# define ETHIF_VLAN_TPID                        (0x8100U)
/* VLAN Tag offsets into Ethernet frame */
# define ETHIF_VLAN_TCI_OFFSET                  (0U)
# define ETHIF_VLAN_FRAME_TYPE_OFFSET           (2U)
/* Length of the VLAN-Tag */
# define ETHIF_VLAN_TAG_LEN_BYTE                (4U)
/* PCP according to IEEE802.1Q */
# define ETHIF_VLAN_PCP_MAX_VAL                 (7U)
/* VLAN ID according to IEEE802.1Q */
# define ETHIF_VLAN_VLANID_PRIO_VLANID          (0U)
# define ETHIF_VLAN_VLANID_INV_VLANID           (ETHIF_INV_VLAN_ID)

/*! Value that defines the special value for the length parameter used in the EthIf_Transmit()/EthIf_VTransmit()
 *  API to trigger a buffer release instead of transmission. */
#define ETHIF_TX_BUFFER_RELEASE_LEN            (0u)

/* Extended Traffic handling */
# define ETHIF_NO_EXTENDED_TRAFFIC_HANDLING    (0U)
# define ETHIF_TRAFFIC_MIRRORING               (1U)
# define ETHIF_TRAFFIC_GATEWAY                 (2U)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453,3458 FCT_LIKE_MACROS */ /* MISRA 19.4,19.7: Macros improve code readability */

# define EthIf_EnterExclusiveArea(ExclusiveArea)  SchM_Enter_EthIf_ETHIF_EXCLUSIVE_AREA_##ExclusiveArea() /* PRQA S 0342 */ /* MD_MSR_19.13_0342 */
# define EthIf_ExitExclusiveArea(ExclusiveArea)   SchM_Exit_EthIf_ETHIF_EXCLUSIVE_AREA_##ExclusiveArea()  /* PRQA S 0342 */ /* MD_MSR_19.13_0342 */

/* PRQA L:FCT_LIKE_MACROS */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/* \trace SPEC-2393573 */
typedef uint8 EthIf_StateType;
typedef uint8 EthIf_TrcvStateType;

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
# define ETHIF_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern VAR(EthIf_StateType, ETHIF_VAR_INIT)  EthIf_ModuleInitialized;

# define ETHIF_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# define ETHIF_START_SEC_CONST_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern CONST(uint8, ETHIF_CONST) EthIf_BroadcastMac[ETH_PHYS_ADDR_LEN_BYTE];

# define ETHIF_STOP_SEC_CONST_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# define ETHIF_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
# if !defined(ETHIF_UNIT_TEST)                                                                                          /* COV_ETHIF_UNIT_TEST */

# endif /* ETHIF_UNIT_TEST */

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ETHIF_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_Int.h
 *********************************************************************************************************************/

