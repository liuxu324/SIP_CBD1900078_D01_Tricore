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
/**        \file  Eth_30_Tc3xx_Int.h
 *        \brief  Component private header file
 *
 *      \details  Private header file of component.
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

#ifndef ETH_30_TC3XX_INT_H
# define ETH_30_TC3XX_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_Cfg.h"
# include "Eth_30_Tc3xx_CfgAccess_Int.h"
# include "Eth_30_Tc3xx_HwAccess_Int.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# define ETH_30_TC3XX_UNDEFINED_DESCRIPTOR_RING                                  (0xFFU)

# define ETH_30_TC3XX_UINT8_MAX                                                  (0xFFU)
# define ETH_30_TC3XX_UINT16_MAX                                                 (0xFFFFU)
# define ETH_30_TC3XX_UINT32_MAX                                                 (0xFFFFFFFFU)

# define ETH_30_TC3XX_ISR_NO_OS_SUPPORT                                          (0U)
# define ETH_30_TC3XX_ISR_CATEGORY_1                                             (1U)
# define ETH_30_TC3XX_ISR_CATEGORY_2                                             (2U)

/* Buffer status */
# define ETH_30_TC3XX_BUFFER_NOT_BUSY                                            (0U)
# define ETH_30_TC3XX_BUFFER_BUSY                                                (1U)

/* Tx Confirmation */
# define ETH_30_TC3XX_TX_STATE_CONFIRMATION_NOT_PENDING                          (0U)
# define ETH_30_TC3XX_TX_STATE_CONFIRMATION_PENDING                              (1U)

/* Descriptor status */
#define ETH_30_TC3XX_DESCRIPTOR_NOT_READY                                        (0U)
#define ETH_30_TC3XX_DESCRIPTOR_READY                                            (1U)
#define ETH_30_TC3XX_DESCRIPTOR_TRANSMITTED                                      (2U)

#define ETH_30_TC3XX_RX_DESCRIPTOR_TO_BUFFER_NOT_MAPPED                          (ETH_30_TC3XX_UINT16_MAX)

# define ETH_30_TC3XX_TIMESYNC_TS_NOT_REQUESTED                                  (0U)
# define ETH_30_TC3XX_TIMESYNC_TS_REQUESTED                                      (1U)


# define ETH_30_TC3XX_MAX_CFGS_TOTAL                                             (1U)

# define ETH_30_TC3XX_MAX_MII_REG_TOTAL                                          (32U)

# define ETH_30_TC3XX_MULTICAST_BUCKET_COUNTERS                                  (64U)
# define ETH_30_TC3XX_BUCKET_MAX_CNT                                             (0xFFU)

# define ETH_30_TC3XX_RX_TS_CONTEXT_STACK_EMPTY_POS                              (-1)

# define ETH_30_TC3XX_VLAN_ETHER_TYPE                                            (0x8100U)
# define ETH_30_TC3XX_VLAN_TCI_UPPER_BYTE_OFFSET                                 (2U)
# define ETH_30_TC3XX_VLAN_PCP_BYTE_MASK                                         (0xE0U)
# define ETH_30_TC3XX_VLAN_PCP_BYTE_SHIFT                                        (5U)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 2 */ /* MD_MSR_19.7 */
# define Eth_30_Tc3xx_EnterExclusiveArea(Area) SchM_Enter_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_##Area() /* PRQA S 0342 */ /* MD_MSR_19.13_0342 */
# define Eth_30_Tc3xx_ExitExclusiveArea(Area) SchM_Exit_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_##Area() /* PRQA S 0342 */ /* MD_MSR_19.13_0342 */

/* Diagnostic Event Manager */
# if ( ETH_30_TC3XX_DEM_ERROR_DETECT == STD_ON )
/* PRQA S 3453 2 */ /* MD_MSR_19.7 */
#  define ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(CtrlIdx) \
  (Dem_ReportErrorStatus(Eth_30_Tc3xx_Cfg_GetDemEventId(CtrlIdx), DEM_EVENT_STATUS_FAILED))
# else
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#  define ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(CtrlIdx)
# endif /* ETH_30_TC3XX_DEM_ERROR_DETECT */

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
# define ETH_30_TC3XX_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
extern VAR(Eth_StateType, ETH_30_TC3XX_VAR_ZERO_INIT) Eth_30_Tc3xx_ModuleInitialized;
extern VAR(Eth_ModeType, ETH_30_TC3XX_VAR_ZERO_INIT) Eth_30_Tc3xx_CtrlMode[ETH_30_TC3XX_MAX_CTRLS_TOTAL];
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

# define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# endif /* ETH_30_TC3XX_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_Int.h
 *********************************************************************************************************************/

