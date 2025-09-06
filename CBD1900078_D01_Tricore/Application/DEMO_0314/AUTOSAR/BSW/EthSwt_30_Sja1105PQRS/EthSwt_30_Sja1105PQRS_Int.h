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
/*!        \file  EthSwt_30_Sja1105PQRS_Int.h
 *        \brief  Private Module Header of Ethernet Switch Driver for NXP SJA1105PQRS Ethernet switch.
 *
 *      \details  The Private Module Header contains the data types used.
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

#ifndef ETHSWT_30_SJA1105PQRS_INT_H
#define ETHSWT_30_SJA1105PQRS_INT_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "EthSwt_30_Sja1105PQRS_LL.h"
#include "EthSwt_30_Sja1105PQRS_Cfg.h"
#include "IpBase.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#if !defined (ETHSWT_30_SJA1105PQRS_INLINE)
# define ETHSWT_30_SJA1105PQRS_INLINE  static INLINE
#endif

/* -- EthSwt_30_Sja1105PQRS_WriteL2LookupTableEntry() -- */
#if (    (ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED == STD_ON) \
      || (ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED == STD_ON) \
      || (ETHSWT_30_SJA1105PQRS_MANAGEMENT_SUPPORT == STD_ON))
# define ETHSWT_30_SJA1105PQRS_WRITE_L2_LOOKUP_TABLE_ENTRY_API  STD_ON
#else
# define ETHSWT_30_SJA1105PQRS_WRITE_L2_LOOKUP_TABLE_ENTRY_API  STD_OFF
#endif /* Availability of EthSwt_30_Sja1105PQRS_WriteL2LookupTableEntry() API */
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/* Development Error Tracer */
#if ( ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON )
/* PRQA S 3453 5 */ /* MD_MSR_19.7 */
/* PRQA S 3458 4 */ /* MD_MSR_19.4 */
#define EthSwt_CheckDetErrorReturnVoid(  CONDITION, INSTANCE_ID, API_ID, ERROR_CODE )          {if(!(CONDITION)) { (void)Det_ReportError( ETHSWT_30_SJA1105PQRS_MODULE_ID, (INSTANCE_ID), (API_ID), (ERROR_CODE)); return; }}
#define EthSwt_CheckDetErrorReturnValue( CONDITION, INSTANCE_ID, API_ID, ERROR_CODE, RET_VAL ) {if(!(CONDITION)) { (void)Det_ReportError( ETHSWT_30_SJA1105PQRS_MODULE_ID, (INSTANCE_ID), (API_ID), (ERROR_CODE)); return (RET_VAL); }}
#define EthSwt_CheckDetErrorContinue(    CONDITION, INSTANCE_ID, API_ID, ERROR_CODE )          {if(!(CONDITION)) { (void)Det_ReportError( ETHSWT_30_SJA1105PQRS_MODULE_ID, (INSTANCE_ID), (API_ID), (ERROR_CODE)); }}
#define EthSwt_CallDetReportError( INSTANCE_ID, API_ID, ERROR_CODE )                                               (void)Det_ReportError( ETHSWT_30_SJA1105PQRS_MODULE_ID, (INSTANCE_ID), (API_ID), (ERROR_CODE))
#else
/* PRQA S 3453 4 */ /* MD_MSR_19.7 */
#define EthSwt_CheckDetErrorReturnVoid(  CONDITION, INSTANCE_ID, API_ID, ERROR_CODE )
#define EthSwt_CheckDetErrorReturnValue( CONDITION, INSTANCE_ID, API_ID, ERROR_CODE, RET_VAL )
#define EthSwt_CheckDetErrorContinue(    CONDITION, INSTANCE_ID, API_ID, ERROR_CODE )
#define EthSwt_CallDetReportError( INSTANCE_ID, API_ID, ERROR_CODE )
#endif
  /* ETHSWT_DEV_ERROR_DETECT */

/*! SPI Byte order handling */
#define EthSwt_30_Sja1105PQRS_Spi_NToH32(Data32)  IPBASE_SWAP32(Data32) /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Number of entries accessible for one lookup table hash */
#define ETHSWT_30_SJA1105PQRS_LOOKUP_TABLE_HASH_ENTRY_NUM                                                           (4u)
/*! Number of ports the hardware has integrated */
#define ETHSWT_30_SJA1105PQRS_HARDWARE_PORT_NUM                                                                     (5u)
/*! Number of entries of the L2 lookup table */
#define ETHSWT_30_SJA1105PQRS_LOOKUP_TABLE_ENTRY_NUM                                                             (1024u)

/*! Offset for Destination MAC from Ethertype */
#define ETHSWT_30_SJA1105PQRS_DEST_MAC_DATA_PTR_OFFSET                                                             (-12)
/*! Offset for Source MAC from Ethertype */
#define ETHSWT_30_SJA1105PQRS_SRC_MAC_DATA_PTR_OFFSET                                                               (-6)

/*! Offset for META data from Ethertype */
#define ETHSWT_30_SJA1105PQRS_META_DATA_PTR_OFFSET                                                                  (2u)

/*! Number of Management Route entries provided by SJA1105PQRS */
#define ETHSWT_30_SJA1105PQRS_MGMT_ROUTE_ENTRIES                                                                    (4u)

/*! Init value for TsReg status variable - All ten bits are set (5 Ports * 2 TsRegs per Port) */
#define ETHSWT_30_SJA1105PQRS_ALL_TSREGS_AVAILABLE                                                              (0x3FFu)

/*! Factor to calculate TsReg offset from hardware port number */
#define ETHSWT_30_SJA1105PQRS_HW_PORT_TO_TSREG_FACTOR                                                               (2u)

/*! Factor to calculate PTP Egress timestamp register offset3 */
#define ETHSWT_30_SJA1105PQRS_EGRESS_TS_FACTOR                                                                      (2u)

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define ETHSWT_30_SJA1105PQRS_START_SEC_VAR_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
extern ETHSWT_VAR_WITH_MEM(EthSwt_StateType, VAR_INIT, SJA1105PQRS) EthSwt_30_Sja1105PQRS_ModuleInitState;
#define ETHSWT_30_SJA1105PQRS_STOP_SEC_VAR_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


 /**********************************************************************************************************************
  *  GLOBAL FUNCTION PROTOTYPES
  *********************************************************************************************************************/
#if ( ETHSWT_30_SJA1105PQRS_WRITE_L2_LOOKUP_TABLE_ENTRY_API == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_WriteL2LookupTableEntry()
 **********************************************************************************************************************/
/*! \brief         Writes an entry to the L2 lookup table.
 *  \details       This function writes an L2 lookup table entry.
 *  \param[in]     SwitchIdx        Index of switch instance.
 *  \param[in]     TableIndex       Index into the L2 lookup table (allowed values 0 to 1023)
 *  \param[in]     MacAddress       Pointer to the MAC address for L2Lookup table entry.
 *  \param[in]     VlanId           VLAN ID for the L2Lookup table entry.
 *  \param[in]     SwitchPortMask   Port Mask for the L2Lookup table entry.
 *  \param[in]     OverwriteAllowed Specifies whether existing entries may be overwritten.
 *  \param[out]    Result           Result of operation
 *  \pre           -
 **********************************************************************************************************************/
 ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_WriteL2LookupTableEntry(
                  EthSwt_SwitchIdxType                                              SwitchIdx,
                  uint16                                                            TableIndex,
   ETHSWT_P2CONST(uint8,                                              SJA1105PQRS)  MacAddress,
                  uint16                                                            VlanId,
                  uint8                                                             SwitchHwPortMask,
   ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_MgmtRouteCfgType,             SJA1105PQRS)  MgmtRouteCfg,
                  boolean                                                           OverwriteAllowed,
     ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_L2LookupTableWriteResultType, SJA1105PQRS)  Result );
#endif /* ETHSWT_30_SJA1105PQRS_WRITE_L2_LOOKUP_TABLE_ENTRY_API */

 /**********************************************************************************************************************
  *  EthSwt_30_Sja1105PQRS_CopyMacAddr()
  *********************************************************************************************************************/
 /*! \brief         Copies a MAC address.
  *  \details       -
  *  \param[in]     mac0 Pointer to the source MAC address
  *  \param[in]     mac1 Pointer to the destination MAC address
  *  \pre           -
  *********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_CopyMacAddr(
   ETHSWT_CONSTP2CONST(uint8, SJA1105PQRS) CpySrcPtr,
     ETHSWT_CONSTP2VAR(uint8, SJA1105PQRS) CpyDestPtr);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_IsMacEqual()
 *********************************************************************************************************************/
/*! \brief         Compares two MAC-addresses for equality.
 *  \details       -
 *  \param[in]     mac0 Pointer to first MAC to be compared
 *  \param[in]     mac1 Pointer to second MAC to be compared
 *  \return        FALSE - MAC-addresses aren't equal
 *  \return        TRUE - MAC-addresses are equal
 *  \pre           -
 *********************************************************************************************************************/
ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_IsMacEqual(
  ETHSWT_P2CONST(uint8, SJA1105PQRS) mac0,
  ETHSWT_P2CONST(uint8, SJA1105PQRS) mac1);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_IsPortInBitmask()
 **********************************************************************************************************************/
/*! \brief         Tests whether the specified port is defined the bit mask
 *  \details       This function tests whether the specified port can be found in the given bit mask.
 *  \param[in]     portIdx          Identifier of the port
 *  \param[in]     bitMask          Bit mask which shall be tested
 *  \return        FALSE  Port is not represented in bit mask
 *  \return        TRUE   Port has been found in bit mask
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *********************************************************************************************************************/
ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_IsPortInBitmask(
  uint8 portIdx,
  uint32 bitMask);

#endif  /* ETHSWT_30_SJA1105PQRS_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthSwt_30_Sja1105PQRS_Int.h
 *********************************************************************************************************************/
