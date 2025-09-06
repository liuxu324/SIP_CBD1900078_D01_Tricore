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
/*!        \file  EthSwt_30_Sja1105PQRS_Regs.h
 *        \brief  Register Definition Header of Ethernet Switch Driver for NXP SJA1105PQRS Ethernet switch.
 *
 *      \details  The Header contains the defines and macros used for register access and manipulation.
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
/*!
 *  Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
#if !defined (ETHSWT_30_SJA1105PQRS_REGS_H)
#define ETHSWT_30_SJA1105PQRS_REGS_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* - STATUS AREA --------------------------------------------------------------------------------------------------- */
/* -- Device ID register - address 0x00 -- */
#define ETHSWT_30_SJA1105PQRS_DEVICE_ID_REG_ADDR                                                                 (0x00u)
#define ETHSWT_30_SJA1105PQRS_DEVICE_ID_REG_WIDTH                                                                   (1u)

/* -- Ethernet MAC-level diagnostic counters - base address 0x200 -- */
#define ETHSWT_30_SJA1105PQRS_ETH_MAC_DIAG_COUNTERS_REG_BASE_ADDR                                               (0x200u)
#define ETHSWT_30_SJA1105PQRS_ETH_MAC_DIAG_COUNTERS_REG_OFFSET                                                   (0x02u)
/* ---- N_RUNT ---- */
#define ETHSWT_30_SJA1105PQRS_ETH_MAC_DIAG_COUNTERS_REG_N_RUNT_MASK                                       (0xFF000000ul)
#define ETHSWT_30_SJA1105PQRS_ETH_MAC_DIAG_COUNTERS_REG_N_RUNT_SHIFT                                               (24u)
/* ---- N_ALIGNERR ---- */
#define ETHSWT_30_SJA1105PQRS_ETH_MAC_DIAG_COUNTERS_REG_N_ALIGNERR_MASK                                   (0x0000FF00ul)
#define ETHSWT_30_SJA1105PQRS_ETH_MAC_DIAG_COUNTERS_REG_N_ALIGNERR_SHIFT                                            (8u)

/* -- Ethernet High-level port Status Part 1 - base address 0x400 -- */
#define ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_1_REG_BASE_ADDR                                              (0x400u)
#define ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_1_REG_OFFSET                                                  (0x10u)
/* --- N_CRCERR --- */
#define ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_1_N_CRCERR_REG_OFFSET                                         (0x0Bu)
/* --- N_RXFRM --- */
#define ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_1_N_RXFRM_REG_OFFSET                                          (0x06u)
/* --- N_RXBYTE --- */
#define ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_1_N_RXBYTE_REG_OFFSET                                         (0x04u)
/* --- N_TXFRM --- */
#define ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_1_N_TXFRM_REG_OFFSET                                          (0x02u)
/* --- N_TXBYTE --- */
#define ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_1_N_TXBYTE_REG_OFFSET                                         (0x00u)

/* -- Ethernet High-level port Status Part 2 - base address 0x600 -- */
#define ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_2_REG_BASE_ADDR                                              (0x600u)
#define ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_2_REG_OFFSET                                                  (0x10u)
/* --- QFULL --- */
#define ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_2_QFULL_REG_OFFSET                                            (0x03u)
/* --- PART_DROP --- */
#define ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_2_PART_DROP_REG_OFFSET                                        (0x02u)

/* -- Ethernet statistics counters base addresses - base address 0x1400 -- */
#define ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_REG_BASE_ADDR                                                 (0x1400u)
#define ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_REG_OFFSET                                                      (0x18u)
/* --- TX_BYTES_1024_1518 --- */
#define ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_TX_BYTES_1024_1518_REG_OFFSET                                   (0x0Fu)
/* --- TX_BYTES_512_1023 --- */
#define ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_TX_BYTES_512_1023_REG_OFFSET                                    (0x0Eu)
/* --- TX_BYTES_256_511 --- */
#define ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_TX_BYTES_256_511_REG_OFFSET                                     (0x0Du)
/* --- TX_BYTES_128_255 --- */
#define ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_TX_BYTES_128_255_REG_OFFSET                                     (0x0Cu)
/* --- TX_BYTES_65_127 --- */
#define ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_TX_BYTES_65_127_REG_OFFSET                                      (0x0Bu)
/* --- TX_BYTES_64 --- */
#define ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_TX_BYTES_64_REG_OFFSET                                          (0x0Au)
/* --- TX_MCAST --- */
#define ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_TX_MCAST_REG_OFFSET                                             (0x09u)
/* --- TX_BCAST --- */
#define ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_TX_BCAST_REG_OFFSET                                             (0x08u)
/* --- RX_BYTES_1024_1518 --- */
#define ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_RX_BYTES_1024_1518_REG_OFFSET                                   (0x07u)
/* --- RX_BYTES_512_1023 --- */
#define ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_RX_BYTES_512_1023_REG_OFFSET                                    (0x06u)
/* --- RX_BYTES_256_511 --- */
#define ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_RX_BYTES_256_511_REG_OFFSET                                     (0x05u)
/* --- RX_BYTES_128_255 --- */
#define ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_RX_BYTES_128_255_REG_OFFSET                                     (0x04u)
/* --- RX_BYTES_65_127 --- */
#define ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_RX_BYTES_65_127_REG_OFFSET                                      (0x03u)
/* --- RX_BYTES_64 --- */
#define ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_RX_BYTES_64_REG_OFFSET                                          (0x02u)
/* --- RX_MCAST --- */
#define ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_RX_MCAST_REG_OFFSET                                             (0x01u)
/* --- RX_BCAST --- */
#define ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_RX_BCAST_REG_OFFSET                                             (0x00u)

/* -- General status registers 11 - 20 (Egress Timestamps) -- */
#define ETHSWT_30_SJA1105PQRS_EGRESS_TS_REG_BASE_ADDR                                                            (0xC0u)
#define ETHSWT_30_SJA1105PQRS_EGRESS_TS_REG_UPDATE_MASK                                                   (0x00000001ul)

/* - CONTROL AREA -------------------------------------------------------------------------------------------------- */
/* -- Initial device configuration flag register - address 0x01 --*/
#define ETHSWT_30_SJA1105PQRS_INIT_DEV_CONFIG_FLAG_REG_ADDR                                                      (0x01u)
#define ETHSWT_30_SJA1105PQRS_INIT_DEV_CONFIG_FLAG_REG_WIRDTH                                                       (1u)
/* ---- CONFIGS ---- */
#define ETHSWT_30_SJA1105PQRS_INIT_DEV_CONFIG_FLAG_REG_CONFIGS_MASK                                       (0x80000000ul)
#define ETHSWT_30_SJA1105PQRS_INIT_DEV_CONFIG_FLAG_REG_CONFIGS_SHIFT                                               (31u)
/* ---- CRCCHKL ---- */
#define ETHSWT_30_SJA1105PQRS_INIT_DEV_CONFIG_FLAG_REG_CRCCHKL_MASK                                       (0x40000000ul)
#define ETHSWT_30_SJA1105PQRS_INIT_DEV_CONFIG_FLAG_REG_CRCCHKL_SHIFT                                               (30u)
/* ---- IDS     ---- */
#define ETHSWT_30_SJA1105PQRS_INIT_DEV_CONFIG_FLAG_REG_IDS_MASK                                           (0x20000000ul)
#define ETHSWT_30_SJA1105PQRS_INIT_DEV_CONFIG_FLAG_REG_IDS_SHIFT                                                   (29u)
/* ---- CRCCHKG ---- */
#define ETHSWT_30_SJA1105PQRS_INIT_DEV_CONFIG_FLAG_REG_CRCCHKG_MASK                                       (0x10000000ul)
#define ETHSWT_30_SJA1105PQRS_INIT_DEV_CONFIG_FLAG_REG_CRCCHKG_SHIFT                                               (28u)

/* -- PTP control register 2: PTPCTRL2 - address 0x13 -- */
#define ETHSWT_30_SJA1105PQRS_PTPCTRL2_REG_ADDR                                                                  (0x13u)

/* -- PTP control register 0: PTPCTRL1 - address 0x18 -- */
#define ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_ADDR                                                                  (0x18u)
#define ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_VALID_MASK                                                     (0x80000000ul)
#define ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_PTPSTRTSCH_MASK                                                (0x40000000ul)
#define ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_PTPSTOPSCH_MASK                                                (0x20000000ul)
#define ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_CASSYNC_MASK                                                   (0x04000000ul)
#define ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_CORRCLK4TS_MASK                                                (0x00000004ul)
#define ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_PTPCLKSUB_MASK                                                 (0x00000002ul)
#define ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_PTPCLKADD_MASK                                                 (0x00000001ul)
/* -- PTP control register 7: PTPCTRL7 - address 0x19 -- */
#define ETHSWT_30_SJA1105PQRS_PTPCTRL7_REG_ADDR                                                                  (0x19u)

/* -- PTP control register 8: PTPCTRL8 - address 0x1A -- */
#define ETHSWT_30_SJA1105PQRS_PTPCTRL8_REG_ADDR                                                                  (0x1Au)

/* -- PTP control register 9: PTPCTRL9 - address 0x1B -- */
#define ETHSWT_30_SJA1105PQRS_PTPCTRL9_REG_ADDR                                                                  (0x1Bu)
#define ETHSWT_30_SJA1105PQRS_PTPCTRL9_REG_INT_PART_MASK                                                  (0x80000000ul)
#define ETHSWT_30_SJA1105PQRS_PTPCTRL9_REG_INT_PART_SHIFT                                                          (31u)
#define ETHSWT_30_SJA1105PQRS_PTPCTRL9_REG_FRACT_PART_MASK                                                (0x7FFFFFFFul)
#define ETHSWT_30_SJA1105PQRS_PTPCTRL9_REG_DEFAULT_RATE                 ETHSWT_30_SJA1105PQRS_PTPCTRL9_REG_INT_PART_MASK

/* -- PTP control register 13: PTPCTRL13 - address 0x1F -- */
#define ETHSWT_30_SJA1105PQRS_PTPCTRL13_REG_ADDR                                                                 (0x1Fu)

/* -- PTP control register 14: PTPCTRL14 - address 0x20 -- */
#define ETHSWT_30_SJA1105PQRS_PTPCTRL14_REG_ADDR                                                                 (0x20u)

/* -- Lower part of PTPTSCLK register: PTPTSCLKL - address 0x1C -- */
#define ETHSWT_30_SJA1105PQRS_PTPTSCLK_LOW_REG_ADDR                                                              (0x1Cu)

/* -- Credit-based shaping block register 0 - address 0x37 -- */
#define ETHSWT_30_SJA1105PQRS_CBS_SHAPING_BLOCK_REG0_ADDR                                                        (0x37u)
#define ETHSWT_30_SJA1105PQRS_CBS_SHAPING_BLOCK_REG0_WIDTH                                                          (1u)

/* -- Credit-based shaping block register 1 - address 0x36 -- */
#define ETHSWT_30_SJA1105PQRS_CBS_SHAPING_BLOCK_REG1_ADDR                                                        (0x36u)
#define ETHSWT_30_SJA1105PQRS_CBS_SHAPING_BLOCK_REG1_WIDTH                                                          (1u)

/* -- Credit-based shaping block register 2 - address 0x35 -- */
#define ETHSWT_30_SJA1105PQRS_CBS_SHAPING_BLOCK_REG2_ADDR                                                        (0x35u)
#define ETHSWT_30_SJA1105PQRS_CBS_SHAPING_BLOCK_REG2_WIDTH                                                          (1u)

/* -- Credit-based shaping block register 3 - address 0x34 -- */
#define ETHSWT_30_SJA1105PQRS_CBS_SHAPING_BLOCK_REG3_ADDR                                                        (0x34u)
#define ETHSWT_30_SJA1105PQRS_CBS_SHAPING_BLOCK_REG3_WIDTH                                                          (1u)

/* -- Credit-based shaping block register 4 - address 0x33 -- */
#define ETHSWT_30_SJA1105PQRS_CBS_SHAPING_BLOCK_REG4_ADDR                                                        (0x33u)
#define ETHSWT_30_SJA1105PQRS_CBS_SHAPING_BLOCK_REG4_WIDTH                                                          (1u)

/* -- Credit-based shaping block register 5 - address 0x32 -- */
#define ETHSWT_30_SJA1105PQRS_CBS_SHAPING_BLOCK_REG5_ADDR                                                        (0x32u)
#define ETHSWT_30_SJA1105PQRS_CBS_SHAPING_BLOCK_REG5_WIDTH                                                          (1u)

/* -- L2 Address Lookup table reconfiguration register 0 - address 0x29 -- */
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_ADDR                                                 (0x29u)
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_WIDTH                                                   (1u)
/* ---- VALID */
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_VALID_MASK                                    (0x80000000ul)
/* ---- RDWRSET */
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_RDWRSET_VAL_WR_MASK                           (0x40000000ul)
/* ---- ERRORS */
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_ERRORS_MASK                                   (0x20000000ul)
/* ---- LOCKEDS */
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_LOCKEDS_MASK                                  (0x10000000ul)
/* ---- VALIDENT */
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_VALIDENT_MASK                                 (0x08000000ul)
/* ---- MGMTROUTE */
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_MGMTROUTE_MASK                                (0x04000000ul)
/* ---- HOSTCMD */
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_HOSTCMD_SHIFT                                          (23u)
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_HOSTCMD_SEARCH                                        (0x1u)
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_HOSTCMD_READ                                          (0x2u)
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_HOSTCMD_WRITE                                         (0x3u)

/* -- L2 Address Lookup table reconfiguration -- */
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_MACADDR_MASK                                       (0x000000FFul)
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_MACADDR_UPPER_MASK                                 (0x000000FCul)
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_MACADDR_LOWER_MASK                                 (0x00000003ul)

/* -- L2 Address Lookup table reconfiguration register 1 - address 0x28 -- */
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG1_TSREG_MASK                                   (0x000000001ul)
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG1_EGR_TS_SHIFT                                            (6u)
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG1_TSREG_SHIFT                                             (7u)
/* MASK_MACADDR */
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG1_MACADDR_MASK                                  (0x00000007ul)

/* -- L2 Address Lookup table reconfiguration register 2 - address 0x27 -- */
/* MASK_MACADDR */
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG2_MACADDR_MASK                                  (0xFFFFFFFFul)

/* -- L2 Address Lookup table reconfiguration register 3 - address 0x26 -- */
/* MACADDR[0] */
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG3_MACADDR0_SHIFT                                          (2u)
/* MASK_MACADDR */
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG3_MACADDR_MASK                                  (0xFFF80000ul)

/* -- L2 Address Lookup table reconfiguration register 4 - address 0x25 -- */
/* MACADDR[4], MACADDR[3], MACADDR[2], MACADDR[1] and MACADDR[0] */
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG4_MACADDR0_SHIFT                                         (30u)
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG4_MACADDR1_SHIFT                                         (22u)
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG4_MACADDR2_SHIFT                                         (14u)
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG4_MACADDR3_SHIFT                                          (6u)
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG4_MACADDR4_SHIFT                                          (2u)

/* -- L2 Address Lookup table reconfiguration register 5 - address 0x24 -- */
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_ADDR                                                 (0x24u)
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_WIDTH                                                   (1u)
/* ---- DESTPORTS */
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_DESTPORTS_MASK                                (0x003E0000ul)
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_DESTPORTS_ALIGN_SHIFT                                  (17u)

/* ---- INDEX */
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_INDEX_MASK                                    (0x0000FFC0ul)
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_INDEX_SHIFT                                             (6u)
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_ENFPORT_SHIFT                                          (16u)
/* MACADDR[5] and MACADDR[4] */
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_MACADDR4_SHIFT                                         (30u)
#define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_MACADDR5_SHIFT                                         (22u)

/* -- VLAN Lookup table reconfiguration register 0 - address 0x30 -- */
#define ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG0_ADDR                                               (0x30u)
#define ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG0_WIDTH                                                 (1u)
/* ---- VALID */
#define ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG0_VALID_MASK                                  (0x80000000ul)
/* ---- RDWRSET */
#define ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG0_RDWRSET_MASK                                (0x40000000ul)
/* ---- VALIDENT */
#define ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG0_VALIDENT_MASK                               (0x08000000ul)

/* -- VLAN Lookup table reconfiguration register 1 - address 0x2D -- */
#define ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG1_ADDR                                               (0x2Du)
#define ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG1_WIDTH                                                 (1u)
/* ---- VMEMB_PORT */
#define ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG1_VMEMB_PORT_MASK                             (0x003E0000ul)
#define ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG1_VMEMB_PORT_SHIFT                                     (17u)
/* ---- VLAN_BC */
#define ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG1_VLAN_BC_MASK                                (0x0001F000ul)
#define ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG1_VLAN_BC_SHIFT                                        (12u)
/* ---- TAG_PORT */
#define ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG1_TAG_PORT_MASK                               (0x00000F80ul)
/* ---- VLANID Upper Part */
#define ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG1_VLANID_UPPER_MASK                           (0x0000007Ful)
#define ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG1_VLANID_UPPER_SHIFT                                    (5u)

/* -- VLAN Lookup table reconfiguration register 2 - address 0x2E -- */
#define ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG2_ADDR                                               (0x2Eu)
#define ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG2_WIDTH                                                 (1u)
/* ---- VLANID Lower Part */
#define ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG3_VLANID_LOWER_MASK                           (0xF8000000ul)
#define ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG3_VLANID_LOWER_SHIFT                                   (27u)

/* -- General parameters reconfiguration register 0 - address 0x46 -- */
#define ETHSWT_30_SJA1105PQRS_GENERAL_PARAMS_RECONFIG_REG0_ADDR                                                  (0x46u)
#define ETHSWT_30_SJA1105PQRS_GENERAL_PARAMS_RECONFIG_REG0_WIDTH                                                    (1u)
/* VALID */
#define ETHSWT_30_SJA1105PQRS_GENERAL_PARAMS_RECONFIG_REG0_VALID_MASK                                     (0x80000000ul)
/* RDWRSET */
#define ETHSWT_30_SJA1105PQRS_GENERAL_PARAMS_RECONFIG_REG0_RDWRSET_MASK                                   (0x10000000ul)

/* -- General parameters reconfiguration register 5 - address 0x3F -- */
#define ETHSWT_30_SJA1105PQRS_GENERAL_PARAMS_RECONFIG_REG5_ADDR                                                  (0x3Fu)
#define ETHSWT_30_SJA1105PQRS_GENERAL_PARAMS_RECONFIG_REG5_WIDTH                                                    (1u)
/* MIRR_PORT */
#define ETHSWT_30_SJA1105PQRS_GENERAL_PARAMS_RECONFIG_REG5_MIRR_PORT_MASK                                        (0x07u)
#define ETHSWT_30_SJA1105PQRS_GENERAL_PARAMS_RECONFIG_REG5_MIRR_PORT_SHIFT                                         (11u)

/* -- MAC configuration table reconfiguration register 0 - address 0x53 -- */
#define ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG0_ADDR                                                (0x53u)
#define ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG0_WIDTH                                                  (1u)
/* VALID */
#define ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG0_VALID_MASK                                   (0x80000000ul)
#define ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG0_VALID_SHIFT                                           (31u)
/* RDWRSET */
#define ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG0_RDWRSET_MASK                                 (0x20000000ul)
#define ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG0_RDWRSET_SHIFT                                         (29u)

/* -- MAC configuration table reconfiguration register 1 - address 0x4B -- */
#define ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG1_ADDR                                                (0x4Bu)
#define ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG1_WIDTH                                                  (1u)
/* ---- PORTST */
#define ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG1_PORTST_RX_EN_MASK                            (0x80000000ul)

/* -- MAC configuration table reconfiguration register 2 - address 0x4C -- */
#define ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG2_ADDR                                                (0x4Cu)
#define ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG2_WIDTH                                                  (1u)
/* ---- PORTST */
#define ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG2_PORTST_TX_EN_MASK                            (0x00000001ul)
#define ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG2_PORTST_MAC_LEARN_EN_MASK                     (0x00000002ul)
#define ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG2_PORTST_EGR_MIRROR_EN_MASK                    (0x00000100ul)
#define ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG2_PORTST_ING_MIRROR_EN_MASK                    (0x00000200ul)

/* -- MAC configuration table reconfiguration register 3 - address 0x4D -- */
#define ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG3_ADDR                                                (0x4Du)
#define ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG3_WIDTH                                                  (1u)

/* -- MAC configuration table reconfiguration register 4 - address 0x4E -- */
#define ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG4_ADDR                                                (0x4Eu)
#define ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG4_WIDTH                                                  (1u)

/* ---- PORTST */
/* - CLOCK GENERATION UNIT (CGU) ----------------------------------------------------------------------------------- */
/* -- PLL_0_S clock status register - address 0x100007 -- */

/* -- PLL_1_S clock status register - address 0x100009 -- */
#define ETHSWT_30_SJA1105PQRS_PLL1_S_STATUS_REG_ADDR                                                      (0x00100009ul)
#define ETHSWT_30_SJA1105PQRS_PLL1_S_STATUS_REG_WIDTH                                                               (1u)
#define ETHSWT_30_SJA1105PQRS_PLL1_S_STATUS_REG_PLL_LOCKED_MASK                                           (0x00000001ul)

/* -- PLL_1_C control register - address 0x10000A -- */
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_ADDR                                                        (0x0010000Aul)
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_WIDTH                                                                 (1u)
/* ---- PLLCLKSRC ---- */
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_PLLCLKSSRC_VAL_DEFAULT_MASK                                 (0x0A000000ul)
/* ---- MSEL      ---- */
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_MSEL_MASK                                                   (0x00FF0000ul)
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_MSEL_SHIFT                                                           (16u)
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_MSEL_VAL_50MHZ_CLKGEN_MASK                                  (0x00010000ul)
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_MSEL_VAL_50MHZ_CLKGEN                                                 (1u)
/* ---- AUTOBLOCK ---- */
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_AUTOBLOCK_MASK                                              (0x00000800ul)
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_AUTOBLOCK_SHIFT                                                      (11u)
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_AUTOBLOCK_VAL_ENABLED_MASK                                  (0x00000800ul)
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_AUTOBLOCK_VAL_ENABLED                                                 (1u)
/* ---- PSEL      ---- */
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_PSEL_MASK                                                   (0x00000300ul)
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_PSEL_SHIFT                                                            (8u)
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_PSEL_VAL_50MHZ_CLKGEN_MASK                                  (0x00000100ul)
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_PSEL_VAL_50MHZ_CLKGEN                                                 (1u)
/* ---- DIRECT    ---- */
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_DIRECT_MASK                                                 (0x00000080ul)
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_DIRECT_SHIFT                                                          (7u)
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_DIRECT_VAL_ENABLE                                                     (0u)
/* ---- FBSEL     ---- */
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_FBSEL_MASK                                                  (0x00000040ul)
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_FBSEL_SHIFT                                                           (6u)
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_FBSEL_VAL_RGMII_CLKGEN_MASK                                 (0x00000040ul)
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_FBSEL_VAL_RGMII_CLKGEN                                                (1u)
/* ---- PLLBYPASS ---- */
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_PLLBYPASS_MASK                                              (0x00000002ul)
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_PLLBYPASS_SHIFT                                                       (1u)
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_PLLBYPASS_VAL_NO_BYBASS                                               (0u)
/* ---- PLL1PD    ---- */
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_PLL1PD_MASK                                                 (0x00000001ul)
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_PLL1PD_SHIFT                                                          (0u)
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_PLL1PD_VAL_DISABLE_MASK                                     (0x00000001ul)
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_PLL1PD_VAL_DISABLE                                                    (1u)
#define ETHSWT_30_SJA1105PQRS_PLL1_C_CTRL_REG_PLL1PD_VAL_ENABLE                                                     (0u)

/* -- IDIV_0_C control register - address 0x10000B -- */
#define ETHSWT_30_SJA1105PQRS_IDIV_0_CTRL_REG_ADDR                                                        (0x0010000Bul)
/* -- IDIV_1_C control register - address 0x10000C -- */
#define ETHSWT_30_SJA1105PQRS_IDIV_1_CTRL_REG_ADDR                                                        (0x0010000Cul)
/* -- IDIV_2_C control register - address 0x10000D -- */
#define ETHSWT_30_SJA1105PQRS_IDIV_2_CTRL_REG_ADDR                                                        (0x0010000Dul)
/* -- IDIV_3_C control register - address 0x10000E -- */
#define ETHSWT_30_SJA1105PQRS_IDIV_3_CTRL_REG_ADDR                                                        (0x0010000Eul)
/* -- IDIV_4_C control register - address 0x10000F -- */
#define ETHSWT_30_SJA1105PQRS_IDIV_4_CTRL_REG_ADDR                                                        (0x0010000Ful)

/* -- IDIV_X_C control register -- */
/* ---- DIVCLKSRC ---- */
#define ETHSWT_30_SJA1105PQRS_IDIV_X_CTRL_REG_VAL_DIVCLKSRC_DEFAULT_MASK                                  (0x0A000000ul)
#define ETHSWT_30_SJA1105PQRS_IDIV_X_CTRL_REG_VAL_IDIV_DISABLE_MASK                                       (0x0A000001ul)
/* ---- AUTOBLOCK ---- */
#define ETHSWT_30_SJA1105PQRS_IDIV_X_CTRL_REG_VAL_AUTOBLOCK_MASK                                          (0x00000800ul)
/* ---- IDIV ---- */
#define ETHSWT_30_SJA1105PQRS_IDIV_X_CTRL_REG_VAL_IDIV1_MASK                                              (0x00000000ul)
#define ETHSWT_30_SJA1105PQRS_IDIV_X_CTRL_REG_VAL_IDIV10_MASK                                             (0x00000028ul)

/* -- MII0_MII_TX_CLK control register - address 0x100013 -- */
#define ETHSWT_30_SJA1105PQRS_MII0_MII_TX_CLK_REG_ADDR                                                    (0x00100013ul)
/* -- MII0_MII_RX_CLK control register - address 0x100014 -- */
#define ETHSWT_30_SJA1105PQRS_MII0_MII_RX_CLK_REG_ADDR                                                    (0x00100014ul)
/* -- MII0_RMII_REF_CLK control register - address 0x100015 -- */
#define ETHSWT_30_SJA1105PQRS_MII0_RMII_REF_CLK_REG_ADDR                                                  (0x00100015ul)
/* -- MII0_RGMII_TX_CLK control register - address 0x100016 -- */
#define ETHSWT_30_SJA1105PQRS_MII0_RGMII_TX_CLK_REG_ADDR                                                  (0x00100016ul)
/* -- MII0_EXT_TX_CLK control register - address 0x100017 -- */
#define ETHSWT_30_SJA1105PQRS_MII0_EXT_TX_CLK_REG_ADDR                                                    (0x00100017ul)
/* -- MII0_EXT_RX_CLK control register - address 0x100018 -- */
#define ETHSWT_30_SJA1105PQRS_MII0_EXT_RX_CLK_REG_ADDR                                                    (0x00100018ul)

/* -- MII1_MII_TX_CLK control register - address 0x100019 -- */
#define ETHSWT_30_SJA1105PQRS_MII1_MII_TX_CLK_REG_ADDR                                                    (0x00100019ul)
/* -- MII1_MII_RX_CLK control register - address 0x10001A -- */
#define ETHSWT_30_SJA1105PQRS_MII1_MII_RX_CLK_REG_ADDR                                                    (0x0010001Aul)
/* -- MII1_RMII_REF_CLK control register - address 0x10001B -- */
#define ETHSWT_30_SJA1105PQRS_MII1_RMII_REF_CLK_REG_ADDR                                                  (0x0010001Bul)
/* -- MII1_RGMII_TX_CLK control register - address 0x10001C -- */
#define ETHSWT_30_SJA1105PQRS_MII1_RGMII_TX_CLK_REG_ADDR                                                  (0x0010001Cul)
/* -- MII1_EXT_TX_CLK control register - address 0x10001D -- */
#define ETHSWT_30_SJA1105PQRS_MII1_EXT_TX_CLK_REG_ADDR                                                    (0x0010001Dul)
/* -- MII1_EXT_RX_CLK control register - address 0x10001E -- */
#define ETHSWT_30_SJA1105PQRS_MII1_EXT_RX_CLK_REG_ADDR                                                    (0x0010001Eul)

/* -- MII2_MII_TX_CLK control register - address 0x10001F -- */
#define ETHSWT_30_SJA1105PQRS_MII2_MII_TX_CLK_REG_ADDR                                                    (0x0010001Ful)
/* -- MII2_MII_RX_CLK control register - address 0x100020 -- */
#define ETHSWT_30_SJA1105PQRS_MII2_MII_RX_CLK_REG_ADDR                                                    (0x00100020ul)
/* -- MII2_RMII_REF_CLK control register - address 0x100021 -- */
#define ETHSWT_30_SJA1105PQRS_MII2_RMII_REF_CLK_REG_ADDR                                                  (0x00100021ul)
/* -- MII2_RGMII_TX_CLK control register - address 0x100022 -- */
#define ETHSWT_30_SJA1105PQRS_MII2_RGMII_TX_CLK_REG_ADDR                                                  (0x00100022ul)
/* -- MII2_EXT_TX_CLK control register - address 0x100023 -- */
#define ETHSWT_30_SJA1105PQRS_MII2_EXT_TX_CLK_REG_ADDR                                                    (0x00100023ul)
/* -- MII2_EXT_RX_CLK control register - address 0x100024 -- */
#define ETHSWT_30_SJA1105PQRS_MII2_EXT_RX_CLK_REG_ADDR                                                    (0x00100024ul)

/* -- MII3_MII_TX_CLK control register - address 0x100025 -- */
#define ETHSWT_30_SJA1105PQRS_MII3_MII_TX_CLK_REG_ADDR                                                    (0x00100025ul)
/* -- MII3_MII_RX_CLK control register - address 0x100026 -- */
#define ETHSWT_30_SJA1105PQRS_MII3_MII_RX_CLK_REG_ADDR                                                    (0x00100026ul)
/* -- MII3_RMII_REF_CLK control register - address 0x100027 -- */
#define ETHSWT_30_SJA1105PQRS_MII3_RMII_REF_CLK_REG_ADDR                                                  (0x00100027ul)
/* -- MII3_RGMII_TX_CLK control register - address 0x100028 -- */
#define ETHSWT_30_SJA1105PQRS_MII3_RGMII_TX_CLK_REG_ADDR                                                  (0x00100028ul)
/* -- MII3_EXT_TX_CLK control register - address 0x100029 -- */
#define ETHSWT_30_SJA1105PQRS_MII3_EXT_TX_CLK_REG_ADDR                                                    (0x00100029ul)
/* -- MII3_EXT_RX_CLK control register - address 0x10002A -- */
#define ETHSWT_30_SJA1105PQRS_MII3_EXT_RX_CLK_REG_ADDR                                                    (0x0010002Aul)

/* -- MII4_MII_TX_CLK control register - address 0x10002B -- */
#define ETHSWT_30_SJA1105PQRS_MII4_MII_TX_CLK_REG_ADDR                                                    (0x0010002Bul)
/* -- MII4_MII_RX_CLK control register - address 0x10002C -- */
#define ETHSWT_30_SJA1105PQRS_MII4_MII_RX_CLK_REG_ADDR                                                    (0x0010002Cul)
/* -- MII4_RMII_REF_CLK control register - address 0x10002D -- */
#define ETHSWT_30_SJA1105PQRS_MII4_RMII_REF_CLK_REG_ADDR                                                  (0x0010002Dul)
/* -- MII4_RGMII_TX_CLK control register - address 0x10002E -- */
#define ETHSWT_30_SJA1105PQRS_MII4_RGMII_TX_CLK_REG_ADDR                                                  (0x0010002Eul)
/* -- MII4_EXT_TX_CLK control register - address 0x10002F -- */
#define ETHSWT_30_SJA1105PQRS_MII4_EXT_TX_CLK_REG_ADDR                                                    (0x0010002Ful)
/* -- MII4_EXT_RX_CLK control register - address 0x100030 -- */
#define ETHSWT_30_SJA1105PQRS_MII4_EXT_RX_CLK_REG_ADDR                                                    (0x00100030ul)

/* -- MIIx_CLK_CTRL clock control register -- */
/* ---- CLKSRC ---- */
#define ETHSWT_30_SJA1105PQRS_MIIX_CLK_CTRL_REG_CLKSRC_VAL_MII0_TX_CLK_MASK                               (0x00000000ul)
#define ETHSWT_30_SJA1105PQRS_MIIX_CLK_CTRL_REG_CLKSRC_VAL_MII0_RX_CLK_MASK                               (0x01000000ul)
#define ETHSWT_30_SJA1105PQRS_MIIX_CLK_CTRL_REG_CLKSRC_VAL_MII1_TX_CLK_MASK                               (0x02000000ul)
#define ETHSWT_30_SJA1105PQRS_MIIX_CLK_CTRL_REG_CLKSRC_VAL_MII1_RX_CLK_MASK                               (0x03000000ul)
#define ETHSWT_30_SJA1105PQRS_MIIX_CLK_CTRL_REG_CLKSRC_VAL_MII2_TX_CLK_MASK                               (0x04000000ul)
#define ETHSWT_30_SJA1105PQRS_MIIX_CLK_CTRL_REG_CLKSRC_VAL_MII2_RX_CLK_MASK                               (0x05000000ul)
#define ETHSWT_30_SJA1105PQRS_MIIX_CLK_CTRL_REG_CLKSRC_VAL_MII3_TX_CLK_MASK                               (0x06000000ul)
#define ETHSWT_30_SJA1105PQRS_MIIX_CLK_CTRL_REG_CLKSRC_VAL_MII3_RX_CLK_MASK                               (0x07000000ul)
#define ETHSWT_30_SJA1105PQRS_MIIX_CLK_CTRL_REG_CLKSRC_VAL_MII4_TX_CLK_MASK                               (0x08000000ul)
#define ETHSWT_30_SJA1105PQRS_MIIX_CLK_CTRL_REG_CLKSRC_VAL_MII4_RX_CLK_MASK                               (0x09000000ul)
#define ETHSWT_30_SJA1105PQRS_MIIX_CLK_CTRL_REG_CLKSRC_VAL_MII4_XO66M0_MASK                               (0x0A000000ul)
#define ETHSWT_30_SJA1105PQRS_MIIX_CLK_CTRL_REG_CLKSRC_VAL_PLL0_MASK                                      (0x0B000000ul)
#define ETHSWT_30_SJA1105PQRS_MIIX_CLK_CTRL_REG_CLKSRC_VAL_PLL1_MASK                                      (0x0E000000ul)
#define ETHSWT_30_SJA1105PQRS_MIIX_CLK_CTRL_REG_CLKSRC_VAL_IDIV0_MASK                                     (0x11000000ul)
#define ETHSWT_30_SJA1105PQRS_MIIX_CLK_CTRL_REG_CLKSRC_VAL_IDIV1_MASK                                     (0x12000000ul)
#define ETHSWT_30_SJA1105PQRS_MIIX_CLK_CTRL_REG_CLKSRC_VAL_IDIV2_MASK                                     (0x13000000ul)
#define ETHSWT_30_SJA1105PQRS_MIIX_CLK_CTRL_REG_CLKSRC_VAL_IDIV3_MASK                                     (0x14000000ul)
#define ETHSWT_30_SJA1105PQRS_MIIX_CLK_CTRL_REG_CLKSRC_VAL_IDIV4_MASK                                     (0x15000000ul)
/* ---- AUTOBLOCK ---- */
#define ETHSWT_30_SJA1105PQRS_MIIX_CLK_CTRL_REG_VAL_AUTOBLOCK_MASK                                        (0x00000800ul)

/* - RESET GENERATION UNIT (RGU) ----------------------------------------------------------------------------------- */
/* -- RESET_CTRL register - address 0x100440 -- */
#define ETHSWT_30_SJA1105PQRS_RESET_CTRL_REG_ADDR                                                         (0x00100440ul)
#define ETHSWT_30_SJA1105PQRS_RESET_CTRL_REG_WIDTH                                                                  (1u)
/* ---- RST_CTRL ---- */
#define ETHSWT_30_SJA1105PQRS_RESET_CTRL_REG_RST_CTRL_MASK                                                (0x0000001Ful)
#define ETHSWT_30_SJA1105PQRS_RESET_CTRL_REG_RST_CTRL_SHIFT                                                         (0u)
#define ETHSWT_30_SJA1105PQRS_RESET_CTRL_REG_RST_CTRL_WARM_RST_VAL                                               (0x08u)
#define ETHSWT_30_SJA1105PQRS_RESET_CTRL_REG_RST_CTRL_COLD_RST_VAL                                               (0x04u)

/* - I/O AND DEBUG ------------------------------------------------------------------------------------------------- */
/* -- CFG_PAD_MII0_TX register - address 0x100800 -- */
#define ETHSWT_30_SJA1105PQRS_CFG_PAD_MII0_TX_REG_ADDR                                                    (0x00100800ul)

/* -- CFG_PAD_MIIx_TX register -- */
/* Output stage speed masks */
#define ETHSWT_30_SJA1105PQRS_CFG_PAD_MIIx_TX_REG_LOW_SPEED_MASK                                          (0x02020202ul)
#define ETHSWT_30_SJA1105PQRS_CFG_PAD_MIIx_TX_REG_MEDIUM_SPEED_MASK                                       (0x0A0A0A0Aul)
#define ETHSWT_30_SJA1105PQRS_CFG_PAD_MIIx_TX_REG_FAST_SPEED_MASK                                         (0x12121212ul)
#define ETHSWT_30_SJA1105PQRS_CFG_PAD_MIIx_TX_REG_HIGH_SPEED_MASK                                         (0x1A1A1A1Aul)

/* -- CFG_PAD_MIIx_ID register -- */
#define ETHSWT_30_SJA1105PQRS_CFG_PAD_MII0_ID_REG_ADDR                                                    (0x00100810ul)

#define ETHSWT_30_SJA1105PQRS_CFG_PAD_MII_ID_RXC_BYPASS_MASK                                              (0x00000200ul)
#define ETHSWT_30_SJA1105PQRS_CFG_PAD_MII_ID_TXC_BYPASS_MASK                                              (0x00000002ul)
#define ETHSWT_30_SJA1105PQRS_CFG_PAD_MII_ID_RXC_PD_MASK                                                  (0x00000100ul)
#define ETHSWT_30_SJA1105PQRS_CFG_PAD_MII_ID_TXC_PD_MASK                                                  (0x00000001ul)

/* -- SGMII register -- */
#define ETHSWT_30_SJA1105PQRS_SGMII_BASIC_CONTROL_REG_ADDR                                                (0x001F0000ul)
#define ETHSWT_30_SJA1105PQRS_SGMII_BASIC_CONTROL_REG_VAL_1GBIT                                           (0x00000040ul)
#define ETHSWT_30_SJA1105PQRS_SGMII_BASIC_CONTROL_REG_VAL_100MBIT                                         (0x00002000ul)
#define ETHSWT_30_SJA1105PQRS_SGMII_BASIC_CONTROL_REG_VAL_10MBIT                                          (0x00000000ul)
#define ETHSWT_30_SJA1105PQRS_SGMII_BASIC_CONTROL_REG_AUTONEG_ENABLE_MASK                                 (0x00001000ul)
#define ETHSWT_30_SJA1105PQRS_SGMII_BASIC_CONTROL_REG_DUPLEX_MODE_MASK                                    (0x00000100ul)

#define ETHSWT_30_SJA1105PQRS_SGMII_AUTONEG_CONTROL_REG_ADDR                                              (0x001F8001ul)
#define ETHSWT_30_SJA1105PQRS_SGMII_AUTONEG_CONTROL_REG_SGMII_LINK_MASK                                   (0x00000010ul)

#define ETHSWT_30_SJA1105PQRS_SGMII_TX_BOOST_CONTROL_REG_ADDR                                             (0x001F8030ul)

#define ETHSWT_30_SJA1105PQRS_SGMII_RX_EQ_CONTROL_REG_ADDR                                                (0x001F8051ul)

#define ETHSWT_30_SJA1105PQRS_SGMII_DIGITAL_CONTROL_REG_ADDR                                              (0x001F80E1ul)
#define ETHSWT_30_SJA1105PQRS_SGMII_DIGITAL_CONTROL_REG_TX_POL_INV_MASK                                   (0x00000010ul)
#define ETHSWT_30_SJA1105PQRS_SGMII_DIGITAL_CONTROL_REG_RX_POL_INV_MASK                                   (0x00000001ul)

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

#endif  /* ETHSWT_30_SJA1105PQRS_REGS_H */

/**********************************************************************************************************************
 *  END OF FILE: EthSwt_30_Sja1105PQRS_Regs.h
 *********************************************************************************************************************/

