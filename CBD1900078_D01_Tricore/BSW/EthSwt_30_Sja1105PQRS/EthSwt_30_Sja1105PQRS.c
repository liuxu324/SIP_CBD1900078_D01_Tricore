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
/*!        \file  EthSwt_30_Sja1105PQRS.c
 *        \brief  Implementation of Ethernet Switch Driver for NXP SJA1105PQRS
 *
 *      \details  Source File contains the implementation of the global API, local functions and local data structures.
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

/* PClint warning suppression */
/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */

/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

#define ETHSWT_30_SJA1105PQRS_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "EthSwt_30_Sja1105PQRS.h"
#include "EthSwt_30_Sja1105PQRS_Int.h"
#include "EthSwt_30_Sja1105PQRS_Regs.h"
#include "EthSwt_30_Sja1105PQRS_Lcfg.h"
#include "EthSwt_30_Sja1105PQRS_Casc_Int.h"
#include "EthSwt_30_Sja1105PQRS_Time_Int.h"
#include "EthSwt_30_Sja1105PQRS_Mirror.h"
#include "EthSwt_30_Sja1105PQRS_LL.h"
#include "EthTrcv_GeneralTypes.h"
#include "SchM_EthSwt_30_Sja1105PQRS.h" /* Include scheduler module for critical sections */
#if ( ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON )
# include "Det.h"
#endif /* ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT */
#if( ETHSWT_30_SJA1105PQRS_PROD_ERROR_REPORTING == STD_ON )
# include "Dem.h"
#endif /* ETHSWT_30_SJA1105PQRS_PROD_ERROR_REPORTING */
#if(    ( ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED == STD_ON) \
     || ( ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED == STD_ON) )
# include "NvM.h"
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of EthSwt_30_Sja1105PQRS header file */
#if(    (ETHSWT_30_SJA1105PQRS_SW_MAJOR_VERSION != (0x05U)) \
     || (ETHSWT_30_SJA1105PQRS_SW_MINOR_VERSION != (0x00U)) \
     || (ETHSWT_30_SJA1105PQRS_SW_PATCH_VERSION != (0x01U)) )
 #error "Vendor specific version numbers of EthSwt_30_Sja1105PQRS.c and EthSwt_30_Sja1105PQRS.h are inconsistent"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

/*! Definition of STATIC macro to be able to declare local data and functions. */
#ifndef   STATIC
#  define STATIC static
#endif /* STATIC */

/*! Count of bytes of a MAC address */
#define ETHSWT_30_SJA1105PQRS_MAC_ADDR_LENGTH_BYTE (6u)

/* ---- configuration section for availability of internal functions ---- */
/* -- EthSwt_30_Sja1105PQRS_ReadL2LookupTableEntry() -- */
#if (    (ETHSWT_30_SJA1105PQRS_GET_ARL_TABLE_API_ENABLED     == STD_ON) \
      || (ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED      == STD_ON) \
      || (ETHSWT_30_SJA1105PQRS_GET_PORT_MAC_ADDR_API_ENABLED == STD_ON)   )
# define ETHSWT_30_SJA1105PQRS_READ_L2_LOOKUP_TABLE_ENTRY_API  STD_ON
#else
# define ETHSWT_30_SJA1105PQRS_READ_L2_LOOKUP_TABLE_ENTRY_API  STD_OFF
#endif /* Availability of EthSwt_30_Sja1105PQRS_ReadL2LookupTableEntry() */

/* -- EthSwt_30_Sja1105PQRS_RestoreConfiguration() -- */
#if (    (ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED == STD_ON) \
      || (ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED == STD_ON)   )
# define ETHSWT_30_SJA1105PQRS_RESTORE_CONFIGURATION_API  STD_ON
#else
# define ETHSWT_30_SJA1105PQRS_RESTORE_CONFIGURATION_API  STD_OFF
#endif /* Availability of EthSwt_30_Sja1105PQRS_RestoreConfiguration() API */

/* -- EthSwt_30_Sja1105PQRS_GetHwPortIndexFromPortMask() -- */
#if( ETHSWT_30_SJA1105PQRS_READ_L2_LOOKUP_TABLE_ENTRY_API == STD_ON )
# define ETHSWT_30_SJA1005_GET_HW_PORT_INDEX_FROM_PORT_MASK_API  STD_ON
#else
# define ETHSWT_30_SJA1005_GET_HW_PORT_INDEX_FROM_PORT_MASK_API  STD_OFF
#endif /* Availability of EthSwt_30_Sja1105PQRS_GetHwPortIndexFromPortMask() API */

/* -- EthSwt_30_Sja1105PQRS_GetPortMaskFromHwPortIndex() -- */
#if (    (ETHSWT_30_SJA1105PQRS_READ_L2_LOOKUP_TABLE_ENTRY_API == STD_ON) \
      || (ETHSWT_30_SJA1105PQRS_ENABLE_VLAN_API_ENABLED        == STD_ON)   )
# define ETHSWT_30_SJA1105PQRS_GET_PORT_MASK_FROM_HW_PORT_INDEX_API  STD_ON
#else
# define ETHSWT_30_SJA1105PQRS_GET_PORT_MASK_FROM_HW_PORT_INDEX_API  STD_OFF
#endif /* Availability of EthSwt_30_Sja1105PQRS_GetPortMaskFromHwPortIndex() API */

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/
#if    ( ETHSWT_30_SJA1105PQRS_API_CALL_TYPE == ETHSWT_30_SJA1105PQRS_API_CALL_TYPE_ASYNC_CALL ) \
    || ( ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED == STD_ON )                              \
    || ( ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED == STD_ON )

/*! State of a asynchronous processing task */
typedef uint8 EthSwt_30_Sja1105PQRS_AsyncProccessingStateType;
#define ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_IDLE       (0U)
#define ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_WAITING    (1U)
#define ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_PROCESSING (2U)

#endif /* ETHSWT_30_SJA1105PQRS_API_CALL_TYPE, ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED, ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_API_CALL_TYPE == ETHSWT_30_SJA1105PQRS_API_CALL_TYPE_ASYNC_CALL )

# if ( ETHSWT_30_SJA1105PQRS_GET_ARL_TABLE_API_ENABLED == STD_ON )
/*! Type for asynchronous processing of GetArlTable() request. */
typedef struct
{
  ETHSWT_P2VAR(EthSwt_MacVlanType, SJA1105PQRS)    ArlTablePtr;
  ETHSWT_P2VAR(uint32,             SJA1105PQRS)    LenPtr;
  EthSwt_30_Sja1105PQRS_AsyncProccessingStateType  ProcState;
} EthSwt_30_Sja1105PQRS_GetArlTableProcessingType;
# endif /* ETHSWT_30_SJA1105PQRS_GET_ARL_TABLE_API_ENABLED */

# if ( ETHSWT_30_SJA1105PQRS_GET_DROP_COUNT_API_ENABLED == STD_ON )
/*! Type for asynchronous processing of GetDropCount() request. */
typedef struct
{
  ETHSWT_P2VAR(uint16,              SJA1105PQRS)   LenPtr;
  ETHSWT_P2VAR(uint32,              SJA1105PQRS)   DropCountPtr;
  EthSwt_30_Sja1105PQRS_AsyncProccessingStateType  ProcState;
} EthSwt_30_Sja1105PQRS_GetDropCountProcessingType;
# endif /* ETHSWT_30_SJA1105PQRS_GET_DROP_COUNT_API_ENABLED */

# if ( ETHSWT_30_SJA1105PQRS_GET_ETHER_STATS_API_ENABLED == STD_ON )
/*! Type for asynchronous processing of GetEtherStats() request. */
typedef struct
{
  ETHSWT_P2VAR(uint32,              SJA1105PQRS)   EtherStatsPtr;
               EthSwt_PortIdxType              PortIdx;
  EthSwt_30_Sja1105PQRS_AsyncProccessingStateType  ProcState;
} EthSwt_30_Sja1105PQRS_GetEtherStatsProcessingType;
# endif /* ETHSWT_30_SJA1105PQRS_GET_ETHER_STATS_API_ENABLED */

#endif /* ETHSWT_30_SJA1105PQRS_API_CALL_TYPE */

#if ( ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED == STD_ON)
/*! Type for asynchronous processing of StoreConfiguration() request. */
typedef struct
{
  EthSwt_SwitchIdxType                         SwitchIdx;
  EthSwt_30_Sja1105PQRS_AsyncProccessingStateType  ProcState;
} EthSwt_30_Sja1105PQRS_StoreConfigProcessingType;
#endif /* ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED == STD_ON )
/*! Type for asynchronous processing of ResetConfiguration() request. */
typedef struct
{
  EthSwt_SwitchIdxType                         SwitchIdx;
  EthSwt_30_Sja1105PQRS_AsyncProccessingStateType  ProcState;
} EthSwt_30_Sja1105PQRS_ResetConfigProcessingType;
#endif /* ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_READ_L2_LOOKUP_TABLE_ENTRY_API == STD_ON )
/*! Type of entry that shall be valid for retrieval of L2 Lookup Table entry with
 *  EthSwt_30_Sja1105PQRS_ReadL2LookupTableEntry() */

typedef uint8 EthSwt_30_Sja1105PQRS_L2LookupTableEntryTypeType;
# define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_ENTRY_TYPE_DONT_CARE (0u)
# define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_ENTRY_DYNAMIC_TYPE   (1u)
# define ETHSWT_30_SJA1105PQRS_L2_LOOKUP_ENTRY_STATIC_TYPE    (2u)
#endif /* ETHSWT_30_SJA1105PQRS_READ_L2_LOOKUP_TABLE_ENTRY_API */

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

#define ETHSWT_30_SJA1105PQRS_START_SEC_VAR_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Variable to indicate if the initialization function of the EthSwt was called. */
ETHSWT_VAR_WITH_MEM(EthSwt_StateType, VAR_INIT, SJA1105PQRS) EthSwt_30_Sja1105PQRS_ModuleInitState = (EthSwt_StateType)ETHSWT_STATE_UNINIT;

#define ETHSWT_30_SJA1105PQRS_STOP_SEC_VAR_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define ETHSWT_30_SJA1105PQRS_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if ( ETHSWT_30_SJA1105PQRS_API_CALL_TYPE == ETHSWT_30_SJA1105PQRS_API_CALL_TYPE_ASYNC_CALL )

# if ( ETHSWT_30_SJA1105PQRS_GET_ARL_TABLE_API_ENABLED == STD_ON )
STATIC ETHSWT_VAR_WITH_MEM(EthSwt_30_Sja1105PQRS_GetArlTableProcessingType, VAR_NOINIT, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetArlTableProcessing[ETHSWT_30_SJA1105PQRS_SWITCH_NUM];
# endif /* ETHSWT_30_SJA1105PQRS_GET_ARL_TABLE_API_ENABLED */

# if ( ETHSWT_30_SJA1105PQRS_GET_ARL_TABLE_API_ENABLED == STD_ON )
STATIC ETHSWT_VAR_WITH_MEM(EthSwt_30_Sja1105PQRS_GetDropCountProcessingType, VAR_NOINIT, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetDropCountProcessing[ETHSWT_30_SJA1105PQRS_SWITCH_NUM];
# endif /* ETHSWT_30_SJA1105PQRS_GET_ARL_TABLE_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_GET_ETHER_STATS_API_ENABLED == STD_ON )
STATIC ETHSWT_VAR_WITH_MEM(EthSwt_30_Sja1105PQRS_GetEtherStatsProcessingType, VAR_NOINIT, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetEtherStatsProcessing[ETHSWT_30_SJA1105PQRS_SWITCH_NUM];
#endif /* ETHSWT_30_SJA1105PQRS_GET_ETHER_STATS_API_ENABLED */

#endif /* ETHSWT_30_SJA1105PQRS_API_CALL_TYPE */

#if ( ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED == STD_ON )
STATIC ETHSWT_VAR_WITH_MEM(EthSwt_30_Sja1105PQRS_StoreConfigProcessingType, VAR_NOINIT, SJA1105PQRS) EthSwt_30_Sja1105PQRS_StoreConfigProcessing;
#endif /* ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED == STD_ON )
STATIC ETHSWT_VAR_WITH_MEM(EthSwt_30_Sja1105PQRS_ResetConfigProcessingType, VAR_NOINIT, SJA1105PQRS) EthSwt_30_Sja1105PQRS_ResetConfigProcessing;
#endif /* ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED */

#define ETHSWT_30_SJA1105PQRS_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define ETHSWT_30_SJA1105PQRS_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if ( ETHSWT_30_SJA1105PQRS_PROD_ERROR_REPORTING == STD_ON )
STATIC ETHSWT_VAR_WITH_MEM(uint32, VAR_NOINIT, SJA1105PQRS) EthSwt_30_Sja1105PQRS_ProdErrorDetect_DropCounts[ETHSWT_30_SJA1105PQRS_SWITCH_NUM][ETHSWT_30_SJA1105PQRS_DROP_COUNT_COUNTERS_NUM];
#endif /* ETHSWT_30_SJA1105PQRS_PROD_ERROR_REPORTING */

#define ETHSWT_30_SJA1105PQRS_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define ETHSWT_30_SJA1105PQRS_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if ( (ETHSWT_30_SJA1105PQRS_PROD_ERROR_REPORTING == STD_ON)                                     && \
      (ETHSWT_30_SJA1105PQRS_API_CALL_TYPE        == ETHSWT_30_SJA1105PQRS_API_CALL_TYPE_ASYNC_CALL)     )
STATIC ETHSWT_VAR_WITH_MEM(uint16, VAR_NOINIT, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_ProdErrorDetect_IsPending[ETHSWT_30_SJA1105PQRS_SWITCH_NUM];
#endif /* ETHSWT_30_SJA1105PQRS_PROD_ERROR_REPORTING, ETHSWT_30_SJA1105PQRS_API_CALL_TYPE */

#define ETHSWT_30_SJA1105PQRS_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

#define ETHSWT_30_SJA1105PQRS_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if ( ETHSWT_30_SJA1005_GET_HW_PORT_INDEX_FROM_PORT_MASK_API == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetHwPortIndexFromPortMask()
 **********************************************************************************************************************/
/*! \brief         Retrieves the hardware port index from a port mask.
 *  \details       This function retrieves the hardware port index from a port mask.
 *  \param[in]     PortMask      Port mask the hardware port index shall be retrieved for.
 *  \return        Hardware Port Index
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(uint8, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetHwPortIndexFromPortMask(
  uint8  PortMask);
#endif /* ETHSWT_30_SJA1005_GET_HW_PORT_INDEX_FROM_PORT_MASK_API */

#if ( ETHSWT_30_SJA1105PQRS_GET_PORT_MASK_FROM_HW_PORT_INDEX_API == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetPortMaskFromHwPortIndex()
 **********************************************************************************************************************/
/*! \brief         Retrieves the port mask from a hardware port index.
 *  \details       This function retrieves the port mask from a hardware port index.
 *  \param[in]     HwPortIdx     Port mask the hardware port index shall be retrieved for.
 *  \return        Port Mask
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(uint8, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetPortMaskFromHwPortIndex(
  uint8  HwPortIdx);
#endif /* ETHSWT_30_SJA1105PQRS_GET_PORT_MASK_FROM_HW_PORT_INDEX_API */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_CheckDeviceAccess()
 **********************************************************************************************************************/
/*! \brief         Checks if SPI communication with SJA1105PQRS switch is possible.
 *  \details       This function reads the Device ID of the SJA1105PQRS switch over SPI to check if access is possible.
 *  \param[in]     SwitchIdx        Index of the switch instance whose device ID shall be checked.
 *  \return        E_NOT_OK -  Device ID does not match / SPI problems
 *  \return        E_OK - Device ID matches configuration
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_CheckDeviceAccess(
  EthSwt_SwitchIdxType  SwitchIdx);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_ResetDevice()
 **********************************************************************************************************************/
/*! \brief         Resets the SJA1105PQRS switch.
 *  \details       This function resets the SJA1105PQRS switch and polls its status until it has left the reset.
 *  \param[in]     SwitchIdx        Index of the switch instance which shall be reset.
 *  \return        E_NOT_OK - Device does not leave reset state / SPI problems
 *  \return        E_OK - Reset successful
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_ResetDevice(
  EthSwt_SwitchIdxType  SwitchIdx);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_DownloadConfig()
 **********************************************************************************************************************/
/*! \brief         Downloads the initial configuration for a SJA1105PQRS switch.
 *  \details       This function downloads the configuration blocks needed to get the SJA1105PQRS switch operational.
 *  \param[in]     SwitchIdx        Index of the switch instance the configuration download shall be processed for.
 *  \return        E_NOT_OK - Configuration not successful / SPI problems
 *  \return        E_OK - Configuration successful
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_DownloadConfig(
  EthSwt_SwitchIdxType  SwitchIdx);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_VerifyConfigDownload()
 **********************************************************************************************************************/
/*! \brief         Verifies if the configuration download was successful.
 *  \details       This function verifies if the configuration was downloaded successfully by checking specific registers.
 *  \param[in]     SwitchIdx        Index of the switch instance the download shall be verified for.
 *  \return        E_NOT_OK - Configuration not successful / SPI problems
 *  \return        E_OK - Configuration successful
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_VerifyConfigDownload(
  EthSwt_SwitchIdxType  SwitchIdx);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_ConfigureShapers()
 **********************************************************************************************************************/
/*! \brief         Configures the shapers.
 *  \details       This function configures the shapers during runtime because this can't be done by configuration
 *                 download.
 *  \param[in]     SwitchIdx        Index of the switch instance whose shapers shall be configured.
 *  \return        E_NOT_OK - Configuration not successful / SPI problems
 *  \return        E_OK - Configuration successful
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_ConfigureShapers(
  EthSwt_SwitchIdxType  SwitchIdx);

#if ( ETHSWT_30_SJA1105PQRS_READ_L2_LOOKUP_TABLE_ENTRY_API == STD_ON)
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_ReadL2LookupTableEntry()
 **********************************************************************************************************************/
/*! \brief         Retrieves an entry of the L2 lookup table.
 *  \details       This function retrieves an L2 lookup table entry.
 *
 *  \param[in]     SwitchIdx      Index of switch instance.
 *  \param[in]     TableIndex     Index into the L2 lookup table (allowed values 0 to 1023)
 *  \param[out]    TableInfo      Pointer to the memory where the information of the read is stored if call was
 *                                successfully.
 *  \param[in]     EntryType      ETHSWT_30_SJA1105PQRS_L2_LOOKUP_ENTRY_STATIC_TYPE:
 *                                - information only valid if entry is static
 *                                ETHSWT_30_SJA1105PQRS_L2_LOOKUP_ENTRY_DYNAMIC_TYPE:
 *                                - information only valid if entry is dynamic
 *                                ETHSWT_30_SJA1105PQRS_L2_LOOKUP_ENTRY_TYPE_DONT_CARE:
 *                                - entry type isn't considered
 *  \return        E_NOT_OK - Retrieval not successful / SPI problems
 *  \return        E_OK - Retrieval successful
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_ReadL2LookupTableEntry(
               EthSwt_SwitchIdxType                                       SwitchIdx,
               uint16                                                     TableIndex,
  ETHSWT_P2VAR(EthSwt_MacVlanType,                          SJA1105PQRS)  TableInfo,
               EthSwt_30_Sja1105PQRS_L2LookupTableEntryTypeType           EntryType);
#endif /* ETHSWT_30_SJA1105PQRS_READ_L2_LOOKUP_TABLE_ENTRY_API */

#if ( ETHSWT_30_SJA1105PQRS_GET_PORT_MAC_ADDR_API_ENABLED == STD_ON)
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_SearchL2LookupTableEntry()
 **********************************************************************************************************************/
/*! \brief         Searches an entry of the L2 lookup table.
 *  \details       This function searches an L2 lookup table entry.
 *
 *  \param[in]     SwitchIdx           Index of switch instance.
 *  \param[in]     MacAddr             MAC Address which shall be searched
 *  \param[out]    SwitchPort          Pointer to switch port where MAC address has been found
 *  \param[out]    L2LookupTableIndex  Index of the found L2LookupTable entry
 *  \return        E_NOT_OK - Retrieval not successful / SPI problems
 *  \return        E_OK - Retrieval successful
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_SearchL2LookupTableEntry(
                 EthSwt_SwitchIdxType                SwitchIdx,
  ETHSWT_P2CONST(uint8,                SJA1105PQRS)  MacAddr,
    ETHSWT_P2VAR(uint8,                SJA1105PQRS)  SwitchPort,
    ETHSWT_P2VAR(uint16,               SJA1105PQRS)  L2LookupTableIndex);
#endif /* ETHSWT_30_SJA1105PQRS_GET_PORT_MAC_ADDR_API_ENABLED */

#if ( (ETHSWT_30_SJA1105PQRS_WRITE_L2_LOOKUP_TABLE_ENTRY_API == STD_ON) || (ETHSWT_30_SJA1105PQRS_UPDATE_MCAST_PORT_ASSIGN_API_ENABLED == STD_ON))
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_CheckL2LookupTableAvailability()
 **********************************************************************************************************************/
/*! \brief         Checks whether the the specified TableIndex is available (unused) in the L2LookupTable
 *  \details       Checks whether the the specified TableIndex is available (unused) in the L2LookupTable
 *  \param[in]     SwitchIdx      Index of switch instance.
 *  \param[in]     TableIndex     Index into the L2 lookup table (allowed values 0 to 1023)
 *  \param[out]    Result         Pointer to the memory where the result of the check is stored
 *                                - ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_WRITE_OK
 *                                - ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_WRITE_OCCUPIED
 *  \return        E_NOT_OK - Retrieval not successful / SPI problems
 *  \return        E_OK - Retrieval successful
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC INLINE Std_ReturnType EthSwt_30_Sja1105PQRS_CheckL2LookupTableAvailability(
    EthSwt_SwitchIdxType                                                       SwitchIdx,
    uint16                                                                     TableIndex,
ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_L2LookupTableWriteResultType, SJA1105PQRS)  Result);
#endif /* ETHSWT_30_SJA1105PQRS_WRITE_L2_LOOKUP_TABLE_ENTRY_API */

#if ( ETHSWT_30_SJA1105PQRS_GET_ARL_TABLE_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_VGetArlTable()
 **********************************************************************************************************************/
/*! \brief         Internal function retrieves the complete address resolution table.
 *  \details       This internal function allows retrieving the valid entries of the address resolution table of a switch
 *                 instance.
 *  \param[in]     SwitchIdx       Index of the switch instance
 *  \param[in,out] LenPtr          in:  Size of the passed buffer the entries shall be written to
 *                                 out: Number of entries written into buffer
 *  \param[out]    ArlTablePtr     Pointer to the buffer the data shall be written to
 *  \return        E_NOT_OK - Retrieval not successful
 *  \return        E_OK - Retrieval successful
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_VGetArlTable(
               EthSwt_SwitchIdxType               SwitchIdx,
  ETHSWT_P2VAR(uint32,              SJA1105PQRS)  LenPtr,
  ETHSWT_P2VAR(EthSwt_MacVlanType,  SJA1105PQRS)  ArlTablePtr );
#endif /* ETHSWT_30_SJA1105PQRS_GET_ARL_TABLE_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_GET_DROP_COUNT_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_VGetDropCount()
 **********************************************************************************************************************/
/*! \brief         Internal function retrieves the drop counts according to the AUTOSAR SWS.
 *  \details       This internal function allows retrieving the drop counts specified by the AUTOSAR SWS. Each count is
 *                 the sum of the drop count of all ports.
 *  \param[in]     SwitchIdx       Index of the switch instance
 *  \param[in,out] LenPtr          in:  Size of the passed buffer the drop counts shall be written to
 *                                 out: Number of drop counts written into buffer
 *  \param[out]    DropCountPtr    Pointer to the buffer the data shall be written to
 *  \return        E_NOT_OK - Retrieval not successful
 *  \return        E_OK - Retrieval successful
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_VGetDropCount(
                 EthSwt_SwitchIdxType               SwitchIdx,
    ETHSWT_P2VAR(uint16,              SJA1105PQRS)  LenPtr,
    ETHSWT_P2VAR(uint32,              SJA1105PQRS)  DropCountPtr );
#endif /* ETHSWT_30_SJA1105PQRS_GET_DROP_COUNT_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_GET_ETHER_STATS_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_VGetEtherStats()
 **********************************************************************************************************************/
/*! \brief         Internal function retrieves the Ethernet statistic counters according to the AUTOSAR SWS.
 *  \details       This internal function allows retrieving the Ethernet statistic counters specified by the AUTOSAR SWS
 *                 for one Switch Port.
 *  \param[in]     SwitchIdx       Index of the switch instance
 *  \param[in]     SwitchPortIdx   Index of the Port
 *  \param[out]    EtherStats      Pointer to the buffer the data shall be written to
 *  \return        E_NOT_OK - Retrieval not successful
 *  \return        E_OK - Retrieval successful
 *  \pre           Switch instance has to be initialized by EthSwt_SwitchInit().
 *  \note          Statistic counters that are not available contain the max value for the uint32 data type.
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_VGetEtherStats(
                 EthSwt_SwitchIdxType               SwitchIdx,
                 EthSwt_PortIdxType                 SwitchPortIdx,
    ETHSWT_P2VAR(uint32,              SJA1105PQRS)  EtherStats );
#endif /* ETHSWT_30_SJA1105PQRS_GET_ETHER_STATS_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_VStoreConfiguration()
 **********************************************************************************************************************/
/*! \brief         Internal function allows storing the current MAC/Port table in NV RAM.
 *  \details       This internal function allows storing the current MAC/Port table retrieved out of the address
 *                 resolution table of the switch in the NV Ram.
 *  \param[in]     SwitchIdx       Index of the switch instance
 *  \return        E_NOT_OK - Storage not successful
 *  \return        E_OK - Storage successful
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \note          Concurrent calls will lead to returning E_NOT_OK until the async storage process of NvM has finished.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_VStoreConfiguration(
    EthSwt_SwitchIdxType  SwitchIdx );
#endif /* ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_VResetConfiguration()
 **********************************************************************************************************************/
/*! \brief         Internal function resets learned MAC port mapping table in NV RAM.
 *  \details       The internal function resets the NV RAM used to store the learned MAC to port mapping table.
 *  \param[in]     SwitchIdx       Index of the switch instance
 *  \return        E_NOT_OK - Reset not successful
 *  \return        E_OK - Reset successful
 *  \pre           Switch instance has to be initialized by EthSwt_SwitchInit().
 *  \note          Concurrent calls will lead to returning E_NOT_OK until the async storage process of NvM has finished.
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_VResetConfiguration(
    EthSwt_SwitchIdxType  SwitchIdx );
#endif /* ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_RESTORE_CONFIGURATION_API == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_RestoreConfiguration()
 **********************************************************************************************************************/
/*! \brief         Downloads the configuration stored in NV-Memory.
 *  \details       This function checks if NV-Memory data is available and downloads the configuration to the switch.
 *  \param[in]     SwitchIdx     Index of the switch instance
 *  \return        E_NOT_OK - Call was not processed successfully
 *  \return        E_OK - Call was processed successfully
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_RestoreConfiguration(
  EthSwt_SwitchIdxType  SwitchIdx );
#endif /* ETHSWT_30_SJA1105PQRS_RESTORE_CONFIGURATION_API */

#if ( ETHSWT_30_SJA1105PQRS_PROD_ERROR_REPORTING == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_ReportProdErrors()
 **********************************************************************************************************************/
/*! \brief         Reports production errors.
 *  \details       This function reports production errors to DEM.
 *  \param[in]     SwitchIdx     Index of the switch instance
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_ReportProdErrors(
  EthSwt_SwitchIdxType  SwitchIdx );
#endif /* ETHSWT_30_SJA1105PQRS_PROD_ERROR_REPORTING */

#if ( ETHSWT_30_SJA1105PQRS_PROD_ERROR_REPORTING == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_DetectProdErrors()
 **********************************************************************************************************************/
/*! \brief         Triggers detection of production errors.
 *  \details       This function triggers the detection of production errors.
 *  \param[in]     SwitchIdx     Index of the switch instance
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_DetectProdErrors(
  EthSwt_SwitchIdxType  SwitchIdx );
#endif /* ETHSWT_30_SJA1105PQRS_PROD_ERROR_REPORTING */

#if (ETHSWT_30_SJA1105PQRS_UPDATE_MCAST_PORT_ASSIGN_API_ENABLED == STD_ON)
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_PrepareAddressOfMCastEntry()
 **********************************************************************************************************************/
/*! \brief         Adapts the address of the entry used for multicast to port assignment
 *  \details       This function modifies the address stored in the entry used for multicast to port assignment. This
 *                 modification either leads to marking the entry as valid (multicast address inserted) or as invalid
 *                 (no multicast address inserted).
 *  \param[in]     mCastAddr   Pointer to the multicast address that shall be inserted
 *  \param[in,out] mCastEntry  Entry that shall be adapted
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_PrepareAddressOfMCastEntry(
  ETHSWT_P2CONST(uint8,                                                 SJA1105PQRS)  mCastAddr,
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_UpdateMCastPortAssignBucketType, SJA1105PQRS)  mCastEntry);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetMCastPortAssignBucketsForActionAdd()
 **********************************************************************************************************************/
/*! \brief         Retrieves the buckets from the multicast bucket entry list that either matches the multicast address
 *                 or is empty (where the matching one is preferred)
 *  \details       -
 *  \param[in]     mCastAddr   Pointer to the multicast address a entry shall be queried for
 *  \param[out]    mCastEntry  Pointer to the entry found
 *  \return        FALSE - not matching entry found and no free entry left to acquire
 *  \return        TRUE - matching or empty entry found and returned
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetMCastPortAssignBucketsForActionAdd(
  ETHSWT_P2CONST(uint8,                                                                            SJA1105PQRS) mCastAddr,
    ETHSWT_P2VAR(ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_UpdateMCastPortAssignBucketType, SJA1105PQRS), SJA1105PQRS) mCastEntry);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetMCastPortAssignBucketsForActionRemove()
 **********************************************************************************************************************/
/*! \brief         Retrieves the buckets from the multicast bucket entry list that matches the multicast address
 *  \details       -
 *  \param[in]     mCastAddr   Pointer to the multicast address a entry shall be queried for
 *  \param[out]    mCastEntry  Pointer to the entry found
 *  \return        FALSE - no entry with matching multicast address found
 *  \return        TRUE - matching entry found and returned
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetMCastPortAssignBucketsForActionRemove(
  ETHSWT_P2CONST(uint8,                                                                            SJA1105PQRS) mCastAddr,
    ETHSWT_P2VAR(ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_UpdateMCastPortAssignBucketType, SJA1105PQRS), SJA1105PQRS) mCastEntry);
#endif /* ETHSWT_30_SJA1105PQRS_UPDATE_MCAST_PORT_ASSIGN_API_ENABLED */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_InitPinCharacteristics()
 **********************************************************************************************************************/
/*! \brief         Initialize Pin characteristics (Slew Rates)
 *  \details       -
 *  \param[in]     SwitchIdx   Index of the switch to be configured
 *  \return        E_NOT_OK - configuration was not successful
 *  \return        E_OK - configuration was successful
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_InitPinCharacteristics(
    EthSwt_SwitchIdxType  SwitchIdx);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_EnableRgmiiTdl()
 **********************************************************************************************************************/
/*! \brief         Enable internal delay lines for RXC / TXC according to configuration
 *  \details       -
 *  \param[in]     SwitchIdx   Index of the switch to be configured
 *  \param[in]     PortIdx     Index of the port to be configured
 *  \return        E_NOT_OK - configuration was not successful
 *  \return        E_OK - configuration was successful
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_EnableRgmiiTdl(
    uint8 SwitchIdx,
    uint8 PortIdx);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_DisableRgmiiTdl()
 **********************************************************************************************************************/
/*! \brief         Disable internal delay lines for RXC / TXC according to configuration
 *  \details       -
 *  \param[in]     SwitchIdx   Index of the switch to be configured
 *  \param[in]     PortIdx     Index of the port to be configured
 *  \return        E_NOT_OK - configuration was not successful
 *  \return        E_OK - configuration was successful
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_DisableRgmiiTdl(
    uint8 SwitchIdx,
    uint8 PortIdx);

#if ( ETHSWT_30_SJA1105PQRS_UPDATE_MCAST_PORT_ASSIGN_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105_FindEmptyL2LookupTablePosition()
 **********************************************************************************************************************/
/*! \brief         Find an empty position in the L2LookupTable
 *  \details       -
 *  \param[in]     SwitchIdx            Index of the switch to be browsed
 *  \param[out]    l2LookupTableIndex   Free position in the static area of the L2LookupTable
 *  \return        E_NOT_OK - No free position was found
 *  \return        E_OK - Free position found
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105_FindEmptyL2LookupTablePosition(
    uint8   SwitchIdx,
    uint16 *l2LookupTableIndex);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105_InvalidateL2LookupTableEntry()
 **********************************************************************************************************************/
/*! \brief         Invalidate a position in the L2LookupTable
 *  \details       -
 *  \param[in]     SwitchIdx            Index of the switch to be configured
 *  \param[out]    l2LookupTableIndex   Position in the L2LookupTable to be invalidated
 *  \return        E_NOT_OK - No free position was found
 *  \return        E_OK - Free position found
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
STATIC ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105_InvalidateL2LookupTableEntry(
    EthSwt_SwitchIdxType                        SwitchIdx,
    uint16                                      L2LookupTableIndex);
#endif /* ETHSWT_30_SJA1105PQRS_UPDATE_MCAST_PORT_ASSIGN_API_ENABLED */
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_CopyMacAddr()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_CopyMacAddr(
  ETHSWT_CONSTP2CONST(uint8, SJA1105PQRS) CpySrcPtr,
    ETHSWT_CONSTP2VAR(uint8, SJA1105PQRS) CpyDestPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least index;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Copy each byte of the MAC address */
  for(index = 0; index < ETH_PHYS_ADDR_LEN_BYTE; index++)
  {
    CpyDestPtr[index] = CpySrcPtr[index];
  }
} /* EthSwt_30_Sja1105PQRS_CopyPhyAddr() */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_IsMacEqual()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *********************************************************************************************************************/
ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_IsMacEqual(
  ETHSWT_P2CONST(uint8, SJA1105PQRS) mac0,
  ETHSWT_P2CONST(uint8, SJA1105PQRS) mac1)
{
  /* ----- Local data declaration --------------------------------------- */
  boolean result;
  uint8_least macPartIdx;

  /* ----- Local data definition ---------------------------------------- */
  result = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Compare the bytes of the MAC addresses for being equal. Stop processing on first mismatch. */
  for( macPartIdx = 0; macPartIdx < ETH_PHYS_ADDR_LEN_BYTE; macPartIdx++ )
  {
    if( mac0[macPartIdx] != mac1[macPartIdx] )
    {
      result = FALSE;
      break;
    }
  }

  return result;
} /* EthSwt_30_Sja1105PQRS_IsMacEqual() */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_IsPortInBitmask()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_IsPortInBitmask(
  uint8 portIdx,
  uint32 bitMask)
{
  uint32 portMask;
  boolean result = TRUE;
  /* #10 Calculate bit mask which represents specified port */
  portMask = (uint32)1u << portIdx;
  /* #20 Test if port bit mask is part of specified bit mask */
  if( (bitMask & portMask) == 0 )
  {
    result = FALSE;
  }
  return result;
} /* EthSwt_30_Sja1105PQRS_IsPortInBitmask() */

#if ( ETHSWT_30_SJA1005_GET_HW_PORT_INDEX_FROM_PORT_MASK_API == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetHwPortIndexFromPortMask()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC INLINE ETHSWT_FUNC(uint8, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetHwPortIndexFromPortMask(
  uint8  PortMask)
{
  /* ----- Local data declaration --------------------------------------- */
  uint8_least HwPortIdx;
  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Query for matching mask to retrieve the hardware port index */
  for( HwPortIdx = 0u; HwPortIdx < ETHSWT_30_SJA1105PQRS_HARDWARE_PORT_NUM; HwPortIdx++ )
  {
    if( PortMask == (uint8)(0x01 << HwPortIdx) )
    {
      break;
    }
  }

  return (uint8)HwPortIdx;
} /* EthSwt_30_Sja1105PQRS_GetHwPortIndexFromPortMask() */
#endif /* ETHSWT_30_SJA1005_GET_HW_PORT_INDEX_FROM_PORT_MASK_API */

#if ( ETHSWT_30_SJA1105PQRS_GET_PORT_MASK_FROM_HW_PORT_INDEX_API == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetPortMaskFromHwPortIndex()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC INLINE ETHSWT_FUNC(uint8, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetPortMaskFromHwPortIndex(
  uint8  HwPortIdx)
{
  /* ----- Local data declaration --------------------------------------- */

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Retrieve the port mask by hardware port index */
  return (uint8)(0x01 << HwPortIdx);
} /* EthSwt_30_Sja1105PQRS_GetPortMaskFromHwPortIndex() */
#endif /* ETHSWT_30_SJA1105PQRS_GET_PORT_MASK_FROM_HW_PORT_INDEX_API */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_CheckDeviceAccess()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_CheckDeviceAccess(
  EthSwt_SwitchIdxType  SwitchIdx)
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType,  SJA1105PQRS)  InstanceConfig;
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType,  SJA1105PQRS)  SpiTransaction;
                 Std_ReturnType                                           RetVal;

  /* ----- Local data definition ---------------------------------------- */
  InstanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx];

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Retrieve the device ID */
  /* read the device ID to check access to the device */
  RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(SwitchIdx, &SpiTransaction);

  if( RetVal == (Std_ReturnType)E_OK )
  {
    SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_DEVICE_ID_REG_ADDR;
    RetVal = EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);

    if( RetVal == (Std_ReturnType)E_OK )
    {
      /* #20 If device ID retrieved isn't the one expected */
      if( SpiTransaction->DataPtr[0] != EthSwt_30_Sja1105PQRS_Spi_NToH32(InstanceConfig->DeviceId[0]) )
      {
        /* #200 Set the return value to E_NOT_OK to indicate a fail */
        /* Device ID differs -> either SPI access not possible or device not supported */
        RetVal = (Std_ReturnType)E_NOT_OK;
        /* #210 If feature Production error reporting is enabled */
#if ( ETHSWT_30_SJA1105PQRS_PROD_ERROR_REPORTING == STD_ON )
        /* #2100 Report production error */
        Dem_ReportErrorStatus(InstanceConfig->DemEvent_E_ACCESS, DEM_EVENT_STATUS_FAILED);
#endif /* ETHSWT_30_SJA1105PQRS_PROD_ERROR_REPORTING */
      }
    }

    (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(SwitchIdx, SpiTransaction);
  }

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_CheckDeviceAccess() */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_ResetDevice()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_ResetDevice(
  EthSwt_SwitchIdxType  SwitchIdx)
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType,  SJA1105PQRS)  InstanceConfig;
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType,  SJA1105PQRS)  SpiTransaction;
                 Std_ReturnType                                           RetVal;

  /* ----- Local data definition ---------------------------------------- */
  InstanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx];

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Trigger reset */
  RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(SwitchIdx, &SpiTransaction);
  if( RetVal == (Std_ReturnType)E_OK )
  {
    SpiTransaction->AddrIdx    = (uint32)ETHSWT_30_SJA1105PQRS_RESET_CTRL_REG_ADDR;
    SpiTransaction->DataPtr[0] = (uint32)ETHSWT_30_SJA1105PQRS_RESET_CTRL_REG_RST_CTRL_COLD_RST_VAL;
    RetVal = EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(SwitchIdx, SpiTransaction);
    (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(SwitchIdx, SpiTransaction);
  }

  if( RetVal == (Std_ReturnType)E_OK )
  {
    /* #20 Wait for the device to leave reset by checking the device ID */
    RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(SwitchIdx, &SpiTransaction);

    if( RetVal == (Std_ReturnType)E_OK )
    {
      uint16 ResetTries;

      ResetTries              = (uint16)ETHSWT_30_SJA1105PQRS_DEVICE_RESET_TRIES;
      SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_DEVICE_ID_REG_ADDR;

      do
      {
        RetVal = EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);

        if( RetVal == (Std_ReturnType)E_NOT_OK ) { break; }

        ResetTries--;
      } while( (SpiTransaction->DataPtr[0] != EthSwt_30_Sja1105PQRS_Spi_NToH32(InstanceConfig->DeviceId[0])) &&
               (ResetTries > (uint16)0U)                                                                         );

      /* #30 If device hasn't left reset or timeout is hit */
      if( (SpiTransaction->DataPtr[0] != EthSwt_30_Sja1105PQRS_Spi_NToH32(InstanceConfig->DeviceId[0])) &&
          (ResetTries == (uint16)0U)                                                                         )
      {
        /* #300 Set return value to E_NOT_OK to indicate a fail */
         RetVal = (Std_ReturnType)E_NOT_OK;
      }

      (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(SwitchIdx, SpiTransaction);
    }
  }

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_ResetDevice() */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_DownloadConfig()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_DownloadConfig(
  EthSwt_SwitchIdxType  SwitchIdx)
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType,  SJA1105PQRS)  InstanceConfig;
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_ConfigBlockDataType, SJA1105PQRS)  ConfigBlocksDataPtr;
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType,  SJA1105PQRS)  SpiTransaction;
                 Std_ReturnType                                           RetVal;
                 uint16_least                                             LoopIdx;

  /* ----- Local data definition ---------------------------------------- */
  InstanceConfig      = &EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx];
  ConfigBlocksDataPtr = InstanceConfig->ConfigBlocksData;
  RetVal              = (Std_ReturnType)E_OK;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Iterate over all available configuration blocks */
  /* Trigger download of configuration blocks */
  for( LoopIdx = 0u; LoopIdx < InstanceConfig->ConfigBlockNum; LoopIdx++ )
  {
    /* check if previous steps were successful -> otherwise stop processing */
    if( RetVal == (Std_ReturnType)E_NOT_OK ) { break; }

    /* #100 Download the configuration block */
    /* trigger download of configuration block */
    RetVal = EthSwt_30_Sja1105PQRS_LL_WriteRaw(
                                        SwitchIdx,
                                        &InstanceConfig->ConfigBlocks[ConfigBlocksDataPtr[LoopIdx].BlockOffset],
                                        ConfigBlocksDataPtr[LoopIdx].BlockLength);

    if( RetVal == (Std_ReturnType)E_OK )
    {
      /* check if no CRC check fail for this block occurred */
      RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(SwitchIdx, &SpiTransaction);
      if( RetVal == (Std_ReturnType)E_OK )
      {
        /* #110 Retrieve CRC check result for the downloaded configuration block */
        SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_INIT_DEV_CONFIG_FLAG_REG_ADDR;
        RetVal = EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);

        if( RetVal == (Std_ReturnType)E_OK )
        {
          /* #1100 If CRC check failed */
          if( (SpiTransaction->DataPtr[0] & (uint32)ETHSWT_30_SJA1105PQRS_INIT_DEV_CONFIG_FLAG_REG_CRCCHKL_MASK) != (uint32)0u )
          {
            /* #11000 Set return value to E_NOT_OK to indicate fail */
            /* CRC check failed -> abort download */
            RetVal = (Std_ReturnType)E_NOT_OK;
          }
        }

        (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(SwitchIdx, SpiTransaction);
      }
    }
  }

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_DownloadConfig() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_VerifyConfigDownload()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_VerifyConfigDownload(
  EthSwt_SwitchIdxType  SwitchIdx)
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS)  SpiTransaction;
               Std_ReturnType                                          RetVal;

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* Retrieve download status register */
  RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(SwitchIdx, &SpiTransaction);

  if( RetVal == (Std_ReturnType)E_OK )
  {
    /* #10 Retrieve the configuration download status */
    SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_INIT_DEV_CONFIG_FLAG_REG_ADDR;

    RetVal = EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);

    if( RetVal == (Std_ReturnType)E_OK )
    {
      /* #20 If configuration isn't valid */
      /* Is configuration valid? */
      if( (SpiTransaction->DataPtr[0] & (uint32)ETHSWT_30_SJA1105PQRS_INIT_DEV_CONFIG_FLAG_REG_CONFIGS_MASK) == (uint32)0u )
      {
        /* #200 Set return value to E_NOT_OK to indicate fail */
        RetVal = (Std_ReturnType)E_NOT_OK;
      }
      /* #30 Else-If device ID isn't correct */
      /* Is Device ID correct? */
      else if( (SpiTransaction->DataPtr[0] & (uint32)ETHSWT_30_SJA1105PQRS_INIT_DEV_CONFIG_FLAG_REG_IDS_MASK) != (uint32)0u )
      {
        /* #300 Set return value to E_NOT_OK to indicate fail */
        RetVal = (Std_ReturnType)E_NOT_OK;
      }
      /* #40 Else-If global CRC isn't correct */
      /* Is global CRC correct? */
      else if( (SpiTransaction->DataPtr[0] & (uint32)ETHSWT_30_SJA1105PQRS_INIT_DEV_CONFIG_FLAG_REG_CRCCHKG_MASK) != (uint32)0u )
      {
        /* #400 Set return value to E_NOT_OK to indicate fail */
        RetVal = (Std_ReturnType)E_NOT_OK;
      }
      else
      {
        /* no error occurred -> proceed */
      }
    }

    (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(SwitchIdx, SpiTransaction);
  }

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_VerifyConfigDownload() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_ConfigureShapers()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_ConfigureShapers(
  EthSwt_SwitchIdxType  SwitchIdx)
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType,  SJA1105PQRS)  InstanceConfig;
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType,  SJA1105PQRS)  SpiTransaction;
                 uint8_least                                              ShaperIdx;
                 Std_ReturnType                                           RetVal;

  /* ----- Local data definition ---------------------------------------- */
  InstanceConfig  = &EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx];
  RetVal          = (Std_ReturnType)E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 For each shaper configured */
  for( ShaperIdx = (uint8_least)0u; ShaperIdx < InstanceConfig->ShaperNum; ShaperIdx++ )
  {
    if( RetVal == (Std_ReturnType)E_NOT_OK ) { break; }

    /* #100 Download shaper configuration */
    RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(SwitchIdx, &SpiTransaction);
    if( RetVal == (Std_ReturnType)E_OK )
    {
      SpiTransaction->WordNum = (uint16)6U;
      SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_CBS_SHAPING_BLOCK_REG5_ADDR;
      /* write register 5 (containing IDLE_SLOPE) */

      SpiTransaction->DataPtr[0] = InstanceConfig->ShaperConfigs[ShaperIdx].Register5;
      /* write register 4 (containing SEND_SLOPE, IDLE_SLOPE) */
      SpiTransaction->DataPtr[1] = InstanceConfig->ShaperConfigs[ShaperIdx].Register4;
      /* write register 3 (containing CREDIT_HI, SEND_SLOPE) */
      SpiTransaction->DataPtr[2] = InstanceConfig->ShaperConfigs[ShaperIdx].Register3;
      /* write register 2 (containing CREDIT_LO, CREDIT_HI) */
      SpiTransaction->DataPtr[3] = InstanceConfig->ShaperConfigs[ShaperIdx].Register2;
      /* write register 1 (containing CBS_PORT, CBS_PRIO, CREDIT_LO) */
      SpiTransaction->DataPtr[4] = InstanceConfig->ShaperConfigs[ShaperIdx].Register1;
      /* write register 0 (containing VALID, RDWRSET, ERRORS, CBSIDX) */
      SpiTransaction->DataPtr[5] = InstanceConfig->ShaperConfigs[ShaperIdx].Register0;
      RetVal |= EthSwt_30_Sja1105PQRS_LL_WriteBytesSync(SwitchIdx, SpiTransaction);

      (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(SwitchIdx, SpiTransaction);
    }
  }

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_ConfigureShapers() */



/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_InitPinCharacteristics()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_InitPinCharacteristics(
  EthSwt_SwitchIdxType  SwitchIdx)
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType,  SJA1105PQRS)  InstanceConfig;
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType,  SJA1105PQRS)  SpiTransaction;
                 Std_ReturnType                                           RetVal;
                 uint8                                                    PortIdx; /* PRQA S 781 */ /* MD_EthSwt_30_Sja1105PQRS_781 */

  /* ----- Local data definition ---------------------------------------- */
  InstanceConfig  = &EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx];
  RetVal          = (Std_ReturnType)E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 For each port configured */
  for( PortIdx = 0u; PortIdx < InstanceConfig->PortNum; PortIdx++ )
  {
    uint8 HwPortIdx;

    if( RetVal == (Std_ReturnType)E_NOT_OK ) { break; }

    HwPortIdx = InstanceConfig->TransformPortIdx((EthSwt_PortIdxType)PortIdx,
        ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_INTERNAL_VIEW);

    if( InstanceConfig->PortSlewRate[HwPortIdx] != ETHSWT_30_SJA1105PQRS_PORT_SLEWRATE_INVALID_SPEED )
    {
      /* #100 Configure port slew rates */
      RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(SwitchIdx, &SpiTransaction);
      if( RetVal == (Std_ReturnType)E_OK )
      {
        SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_CFG_PAD_MII0_TX_REG_ADDR + (2 * HwPortIdx);

        switch( InstanceConfig->PortSlewRate[HwPortIdx] )
        {
        case ETHSWT_30_SJA1105PQRS_PORT_SLEWRATE_LOW_SPEED:
          SpiTransaction->DataPtr[0] = ETHSWT_30_SJA1105PQRS_CFG_PAD_MIIx_TX_REG_LOW_SPEED_MASK;
          break;
        case ETHSWT_30_SJA1105PQRS_PORT_SLEWRATE_MEDIUM_SPEED:
          SpiTransaction->DataPtr[0] = ETHSWT_30_SJA1105PQRS_CFG_PAD_MIIx_TX_REG_MEDIUM_SPEED_MASK;
          break;
        case ETHSWT_30_SJA1105PQRS_PORT_SLEWRATE_FAST_SPEED:
          SpiTransaction->DataPtr[0] = ETHSWT_30_SJA1105PQRS_CFG_PAD_MIIx_TX_REG_FAST_SPEED_MASK;
          break;
        case ETHSWT_30_SJA1105PQRS_PORT_SLEWRATE_HIGH_SPEED:
          SpiTransaction->DataPtr[0] = ETHSWT_30_SJA1105PQRS_CFG_PAD_MIIx_TX_REG_HIGH_SPEED_MASK;
          break;
        default:
          /* Should never happen */
          RetVal = E_NOT_OK;
          break;
        }

        RetVal |= EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(SwitchIdx, SpiTransaction);

        (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(SwitchIdx, SpiTransaction);
      }
    }
  }

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_ConfigureShapers() */


#if ( ETHSWT_30_SJA1105PQRS_READ_L2_LOOKUP_TABLE_ENTRY_API == STD_ON)
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_ReadL2LookupTableEntry()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_ReadL2LookupTableEntry(
               EthSwt_SwitchIdxType                                       SwitchIdx,
               uint16                                                     TableIndex,
  ETHSWT_P2VAR(EthSwt_MacVlanType,                          SJA1105PQRS)  TableInfo,
               EthSwt_30_Sja1105PQRS_L2LookupTableEntryTypeType           EntryType)
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS)  SpiTransaction;
               Std_ReturnType                                          RetVal;

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  EthSwt_EnterExclusiveArea(Sja1105PQRS, ARL_TABLE_ACCESS); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(SwitchIdx, &SpiTransaction);

  if( RetVal == (Std_ReturnType)E_OK )
  {
    /* #10 Retrieve the status of the lookup table entry addressed */
    /* trigger a table read for the current index */
    /* setup L2 address lookup table reconfiguration register 5 */
    SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_ADDR;
    /* setup index for the entry to be read */
    SpiTransaction->DataPtr[0] = (uint32)((uint32)TableIndex << (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_INDEX_SHIFT);
    RetVal |= EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(SwitchIdx, SpiTransaction);

    /* Setup L2 address lookup table reconfiguration register 0 */
    /* setup read access */
    SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_ADDR;
    SpiTransaction->DataPtr[0]  = (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_VALID_MASK;
    SpiTransaction->DataPtr[0] |= (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_LOCKEDS_MASK;
    SpiTransaction->DataPtr[0] |= (uint32)(ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_HOSTCMD_READ <<
                                           ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_HOSTCMD_SHIFT);
    /* trigger read */
    RetVal |= EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(SwitchIdx, SpiTransaction);

    /* read back the result of the read */
    SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_ADDR;
    /* read result */
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);

    /* #20 If addressed entry is valid */
    /* process table entry */
    /* check if entry is valid */
    if( ((SpiTransaction->DataPtr[0] & (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_VALIDENT_MASK) != (uint32)0u) &&
        ((SpiTransaction->DataPtr[0] & (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_VALID_MASK)    == (uint32)0u) &&
        ((SpiTransaction->DataPtr[0] & (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_ERRORS_MASK)   == (uint32)0u) &&
        (RetVal == (Std_ReturnType)E_OK) )
    {
      /* #200 If addressed entry is of type queried for */
      /* check if entry is of type queried for */
      switch( EntryType )
      {
        case ETHSWT_30_SJA1105PQRS_L2_LOOKUP_ENTRY_STATIC_TYPE:
          if( (SpiTransaction->DataPtr[0] & (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_LOCKEDS_MASK) != (uint32)0u )
          {
            RetVal = (Std_ReturnType)E_OK;
          }
          break;
        case ETHSWT_30_SJA1105PQRS_L2_LOOKUP_ENTRY_DYNAMIC_TYPE:
          if( (SpiTransaction->DataPtr[0] & (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_LOCKEDS_MASK) == (uint32)0u )
          {
            RetVal = (Std_ReturnType)E_OK;
          }
          break;
        case ETHSWT_30_SJA1105PQRS_L2_LOOKUP_ENTRY_TYPE_DONT_CARE:
          RetVal = (Std_ReturnType)E_OK;
          break;
        default:
          RetVal = (Std_ReturnType)E_NOT_OK;
          break;
      }

      if( RetVal == (Std_ReturnType)E_OK )
      {
        SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_ADDR;
        SpiTransaction->WordNum = (uint16)3u;
        RetVal = EthSwt_30_Sja1105PQRS_LL_ReadBytesSync(SwitchIdx, SpiTransaction);

        if( RetVal == (Std_ReturnType)E_OK )
        {
          uint8 PortMask;

          /* #2000 Retrieve Port information of entry */
          /* get port ID */
          PortMask = (uint8)((SpiTransaction->DataPtr[0] &
              (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_DESTPORTS_MASK)
              >> (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_DESTPORTS_ALIGN_SHIFT);
          TableInfo->SwitchPort = EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].TransformPortIdx(
              EthSwt_30_Sja1105PQRS_GetHwPortIndexFromPortMask(PortMask),
              ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_EXTERNAL_VIEW);

          /* #2010 Retrieve MAC-address information of entry */
          TableInfo->MacAddr[5]  = (uint8)((SpiTransaction->DataPtr[0] >>
              (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_MACADDR5_SHIFT) &
              (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_MACADDR_MASK);
          TableInfo->MacAddr[4]  = (uint8)((SpiTransaction->DataPtr[0] >>
              (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_MACADDR4_SHIFT) &
              (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_MACADDR_LOWER_MASK);
          TableInfo->MacAddr[4] |= (uint8)((SpiTransaction->DataPtr[1] <<
              (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG4_MACADDR4_SHIFT) &
              (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_MACADDR_UPPER_MASK);
          TableInfo->MacAddr[3]  = (uint8)((SpiTransaction->DataPtr[1] >>
              (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG4_MACADDR3_SHIFT) &
              (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_MACADDR_MASK);
          TableInfo->MacAddr[2]  = (uint8)((SpiTransaction->DataPtr[1] >>
              (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG4_MACADDR2_SHIFT) &
              (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_MACADDR_MASK);
          TableInfo->MacAddr[1]  = (uint8)((SpiTransaction->DataPtr[1] >>
              (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG4_MACADDR1_SHIFT) &
              (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_MACADDR_MASK);
          TableInfo->MacAddr[0]  = (uint8)((SpiTransaction->DataPtr[1] >>
              (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG4_MACADDR0_SHIFT) &
              (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_MACADDR_LOWER_MASK);
          TableInfo->MacAddr[0] |= (uint8)((SpiTransaction->DataPtr[2] <<
              (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG3_MACADDR0_SHIFT) &
              (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_MACADDR_UPPER_MASK);

          /* #2020 Retrieve VLAN information of entry */
          /* VLAN for address table hashing is turned off due to EthSwt_GetPortMacAddr() API -> no VLAN information */
          TableInfo->VlanId = (uint16)0u;
        }
      }
    }
    else
    {
      RetVal = (Std_ReturnType)E_NOT_OK;
    }

    (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(SwitchIdx, SpiTransaction);
  }

  EthSwt_ExitExclusiveArea(Sja1105PQRS, ARL_TABLE_ACCESS); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_ReadL2LookupTableEntry() */
#endif /* ETHSWT_30_SJA1105PQRS_READ_L2_LOOKUP_TABLE_ENTRY_API */

#if ( (ETHSWT_30_SJA1105PQRS_WRITE_L2_LOOKUP_TABLE_ENTRY_API == STD_ON) || (ETHSWT_30_SJA1105PQRS_UPDATE_MCAST_PORT_ASSIGN_API_ENABLED == STD_ON))
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_CheckL2LookupTableAvailability()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_CheckL2LookupTableAvailability(
    EthSwt_SwitchIdxType                                               SwitchIdx,
    uint16                                                             TableIndex,
ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_L2LookupTableWriteResultType, SJA1105PQRS)  Result)
{
  Std_ReturnType                                                       RetVal;
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS)  SpiTransaction;

  EthSwt_EnterExclusiveArea(Sja1105PQRS, ARL_TABLE_ACCESS); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(SwitchIdx, &SpiTransaction);

  if( RetVal == (Std_ReturnType)E_OK )
  {
    /* #10 Retrieve the status of the lookup table entry addressed */
    /*-- trigger a table read for the current index */
    /* - setup L2 address lookup table reconfiguration register 5 */
    SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_ADDR;
    SpiTransaction->WordNum = (uint16)5u;
    /* setup index for the entry to be read */
    SpiTransaction->DataPtr[0] =  (uint32)((uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_INDEX_MASK
                                       & ((uint32)TableIndex
                                           << (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_INDEX_SHIFT));
    SpiTransaction->DataPtr[1] = 0;
    SpiTransaction->DataPtr[2] = 0;
    SpiTransaction->DataPtr[3] = 0;
    SpiTransaction->DataPtr[4] = 0;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_WriteBytesSync(SwitchIdx, SpiTransaction);

    /* - setup L2 address lookup table reconfiguration register 0 */
    /* setup read access */
    SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_ADDR;
    SpiTransaction->DataPtr[0]  = (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_VALID_MASK;
    SpiTransaction->DataPtr[0] |= (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_LOCKEDS_MASK;
    SpiTransaction->DataPtr[0] |= (uint32)(ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_HOSTCMD_READ <<
                                           ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_HOSTCMD_SHIFT);
    /* - trigger read */
    RetVal |= EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(SwitchIdx, SpiTransaction);

    /* -- read back the result of the read */
    SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_ADDR;
    /* - read result */
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);

    /* analyze result */
    /* #20 If error has occurred during access */
    if( (SpiTransaction->DataPtr[0] & (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_ERRORS_MASK) != (uint32)0u )
    {
      /* #200 Set return value to E_NOT_OK to indicate fail */
      /* error occurred during read */
      RetVal = (Std_ReturnType)E_NOT_OK;
    }
    /* #30 Else-If entry is already in use */
    else if(    ((SpiTransaction->DataPtr[0] & ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_LOCKEDS_MASK)  != (uint32)0u)
            || ((SpiTransaction->DataPtr[0] & ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_VALIDENT_MASK) != (uint32)0u) )
    {
      /* #300 Set access result to "entry occupied" */
      /* entry is already in use -> no write possible */
      Result[0] = (EthSwt_30_Sja1105PQRS_L2LookupTableWriteResultType)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_WRITE_OCCUPIED;
    }
    else
    {
      /* #310 Set access result to "entry written" */
      /* no error occurred and entry isn't use -> allow a write */
      Result[0] = (EthSwt_30_Sja1105PQRS_L2LookupTableWriteResultType)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_WRITE_OK;
    }

    (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(SwitchIdx, SpiTransaction);
  }

  EthSwt_ExitExclusiveArea(Sja1105PQRS, ARL_TABLE_ACCESS); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return RetVal;
}

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_WriteL2LookupTableEntry()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
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
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_WriteL2LookupTableEntry(
                 EthSwt_SwitchIdxType                                              SwitchIdx,
                 uint16                                                            TableIndex,
  ETHSWT_P2CONST(uint8,                                              SJA1105PQRS)  MacAddress,
                 uint16                                                            VlanId,
                 uint8                                                             SwitchHwPortMask,
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_MgmtRouteCfgType,             SJA1105PQRS)  MgmtRouteCfg,
                 boolean                                                           OverwriteAllowed,
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_L2LookupTableWriteResultType, SJA1105PQRS)  Result )
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS)  SpiTransaction;
               Std_ReturnType                                          RetVal;

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(VlanId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  EthSwt_EnterExclusiveArea(Sja1105PQRS, ARL_TABLE_ACCESS); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(SwitchIdx, &SpiTransaction);

  if( RetVal == (Std_ReturnType)E_OK )
  {
    /* Allow overwriting for Mgmt Routes and if the parameter is set. Mgmt Routes are only valid during Eth_Transmit -
     * no interruptions are expected during that time */
    if((MgmtRouteCfg->EnableMgmtRoute == TRUE) || (OverwriteAllowed == TRUE) )
    {
      *Result = (EthSwt_30_Sja1105PQRS_L2LookupTableWriteResultType)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_WRITE_OK;
    }
    else
    {
      /* Check is L2LookupTable Entry is available or blocked by a learned or loaded entry */
      RetVal |= EthSwt_30_Sja1105PQRS_CheckL2LookupTableAvailability(SwitchIdx, TableIndex, Result);
    }


    /* #50 If no error has occurred and entry is available */
    if(    (RetVal == (Std_ReturnType)E_OK)
        && (*Result == (EthSwt_30_Sja1105PQRS_L2LookupTableWriteResultType)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_WRITE_OK) )
    {
      /* #500 Setup entry information (port, MAC-address, VLAN) */
      /* Setup transfer data */
      SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_ADDR;
      SpiTransaction->WordNum = (uint16)5u;

      /* setup register 5 */
      SpiTransaction->DataPtr[0]  = (uint32)0u;
      /* INDEX */
      SpiTransaction->DataPtr[0] |= (uint32)((uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_INDEX_MASK
                                           & ((uint32)TableIndex << (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_INDEX_SHIFT));
      if( MgmtRouteCfg->EnableMgmtRoute == TRUE )
      {
        /* ENFPORT is only set for a management route */
        SpiTransaction->DataPtr[0] |= (uint32)((uint32)1U << ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_ENFPORT_SHIFT);
      }

      /* DESTPORTS */
      SpiTransaction->DataPtr[0] |= (uint32)((uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_DESTPORTS_MASK
                                           & ((uint32)SwitchHwPortMask << (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_DESTPORTS_ALIGN_SHIFT));

      /* lower part of MACADDR */
      SpiTransaction->DataPtr[0] |= (uint32)(((uint32)MacAddress[5] &
          (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_MACADDR_MASK)
          << (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_MACADDR5_SHIFT);
      SpiTransaction->DataPtr[0] |= (uint32)(((uint32)MacAddress[4] &
          (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_MACADDR_MASK)
          << (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_MACADDR4_SHIFT);

      /* setup register 4 */
      SpiTransaction->DataPtr[1]  = (uint32)0u;
      SpiTransaction->DataPtr[1] |= (uint32)(((uint32)MacAddress[4] &
          (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_MACADDR_MASK)
          >> (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG4_MACADDR4_SHIFT);
      SpiTransaction->DataPtr[1] |= (uint32)(((uint32)MacAddress[3] &
          (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_MACADDR_MASK)
          << (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG4_MACADDR3_SHIFT);
      SpiTransaction->DataPtr[1] |= (uint32)(((uint32)MacAddress[2] &
          (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_MACADDR_MASK)
          << (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG4_MACADDR2_SHIFT);
      SpiTransaction->DataPtr[1] |= (uint32)(((uint32)MacAddress[1] &
          (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_MACADDR_MASK)
          << (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG4_MACADDR1_SHIFT);
      SpiTransaction->DataPtr[1] |= (uint32)(((uint32)MacAddress[0] &
          (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_MACADDR_MASK)
          << (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG4_MACADDR0_SHIFT);

      /* setup register 3 */
      SpiTransaction->DataPtr[2]  = (uint32)0u;
      SpiTransaction->DataPtr[2] |= (uint32)(((uint32)MacAddress[0] &
          (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_MACADDR_MASK)
          >> (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG3_MACADDR0_SHIFT);

      /* VLANID */
      /* is already set to 0 because VLAN isn't taken into account for MAC address learning */

      SpiTransaction->DataPtr[2] |= ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG3_MACADDR_MASK;
      SpiTransaction->DataPtr[3]  = ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG2_MACADDR_MASK;
      SpiTransaction->DataPtr[4]  = ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG1_MACADDR_MASK;

      if( MgmtRouteCfg->EnableMgmtRoute == TRUE )
      {
        if( MgmtRouteCfg->EnableTimeStamp == TRUE )
        {
          /* EGR_TS Enable timestamps (LSB in VLANID, see MGMTROUTE) */
          SpiTransaction->DataPtr[2] |= ((uint32)1U
              <<ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG1_EGR_TS_SHIFT);

          /* TS_REGID Select TS Register 0 (Bit 1 in VLANID, see MGMTROUTE) */
          SpiTransaction->DataPtr[2] |=
              ((uint32)((uint32)MgmtRouteCfg->TsReg & ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG1_TSREG_MASK)
                  << ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG1_TSREG_SHIFT);
        }
      }

      RetVal = EthSwt_30_Sja1105PQRS_LL_WriteBytesSync(SwitchIdx, SpiTransaction);

      if(RetVal == (Std_ReturnType)E_OK)
      {
        SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_ADDR;

        /* #510 Download entry to lookup table */
        /* setup register 0 - command register */
        SpiTransaction->DataPtr[0] = (uint32)((uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_VALID_MASK
                                            | (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_RDWRSET_VAL_WR_MASK
                                            | (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_VALIDENT_MASK
                                            | (uint32)(ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_HOSTCMD_WRITE <<
                                                ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_HOSTCMD_SHIFT));

        if( MgmtRouteCfg->EnableMgmtRoute == TRUE )
        {
          SpiTransaction->DataPtr[0] |= (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_MGMTROUTE_MASK;
        }
        else
        {
          SpiTransaction->DataPtr[0] |= (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_LOCKEDS_MASK;
        }

        RetVal = EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(SwitchIdx, SpiTransaction);
      }
    }

    (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(SwitchIdx, SpiTransaction);
  }

  EthSwt_ExitExclusiveArea(Sja1105PQRS, ARL_TABLE_ACCESS); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_WriteL2LookupTableEntry() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */
#endif /* ETHSWT_30_SJA1105PQRS_READ_L2_LOOKUP_TABLE_ENTRY_API */

#if ( ETHSWT_30_SJA1105PQRS_GET_ARL_TABLE_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_VGetArlTable()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
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
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_VGetArlTable(
               EthSwt_SwitchIdxType               SwitchIdx,
  ETHSWT_P2VAR(uint32,              SJA1105PQRS)  LenPtr,
  ETHSWT_P2VAR(EthSwt_MacVlanType,  SJA1105PQRS)  ArlTablePtr )
{
  /* ----- Local data declaration --------------------------------------- */
  Std_ReturnType  RetVal;
  uint16_least    TableEntryIdx;
  uint32          ReadEntriesCnt;

  /* ----- Local data definition ---------------------------------------- */
  ReadEntriesCnt = (uint32)0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all available entries of lookup table */
  /* SJA1105PQRS only supports iterating over whole L2 lookup table to retrieve the valid entries of the table */
  for( TableEntryIdx = 0u; TableEntryIdx < ETHSWT_30_SJA1105PQRS_LOOKUP_TABLE_ENTRY_NUM; TableEntryIdx++ )
  {
    /* #100 If no space left in destination buffer */
    /* check if there is enough space left in the passed array */
    if( ReadEntriesCnt == LenPtr[0] )
    {
      /* #1000 Stop processing */
      /* not enough space */
      break;
    }

    /* #110 Read a lookup table entry */
    RetVal = EthSwt_30_Sja1105PQRS_ReadL2LookupTableEntry(
                                  SwitchIdx,
                                  (uint16)TableEntryIdx,
                                  &ArlTablePtr[ReadEntriesCnt],
                                  (EthSwt_30_Sja1105PQRS_L2LookupTableEntryTypeType)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_ENTRY_TYPE_DONT_CARE);

    /* #120 If entry is valid */
    if( RetVal == (Std_ReturnType)E_OK )
    {
      /* #1200 Increase the count of read entries */
      /* increase the read entries count if read was successful */
      ReadEntriesCnt++;
    }
  }

  /* #20 If at least one entry is read and destination buffer was large enough */
  if( (ReadEntriesCnt > 0u)         &&
      (ReadEntriesCnt != LenPtr[0])    )
  {
    /* #200 Set return value to E_OK to indicate success */
    RetVal = (Std_ReturnType)E_OK;
  }
  else
  {
    /* #300 Set return value to E_NOT_OK to indicate fail */
    RetVal = (Std_ReturnType)E_NOT_OK;
  }

  /* #40 Pass count of read entries */
  LenPtr[0] = ReadEntriesCnt;

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_VGetArlTable() */
#endif /* ETHSWT_30_SJA1105PQRS_GET_ARL_TABLE_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_GET_DROP_COUNT_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_VGetDropCount()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_VGetDropCount(
                 EthSwt_SwitchIdxType               SwitchIdx,
    ETHSWT_P2VAR(uint16,              SJA1105PQRS)  LenPtr,        /* PRQA S 3673 */ /* MD_EthSwt_30_Sja1105PQRS_3673 */
    ETHSWT_P2VAR(uint32,              SJA1105PQRS)  DropCountPtr )
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  InstanceConfig;
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS)  SpiTransaction;
                 Std_ReturnType                                          RetVal;
                 uint8_least                                             LoopPortIdx;
                 boolean                                                 IsSpiTransactionProvided;

  /* ----- Local data definition ---------------------------------------- */
  InstanceConfig           = &EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx];
  IsSpiTransactionProvided = (boolean)FALSE;

  /* ----- Implementation ----------------------------------------------- */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(LenPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(SwitchIdx, &SpiTransaction);

  /* #10 Set unsupported counters to max value */
  /* initialize counters to default value */
  if( RetVal == (Std_ReturnType)E_OK )
  {
    IsSpiTransactionProvided = (boolean)TRUE;

    /* -- dropped ingress packets due to buffer overrun -- */
    DropCountPtr[0] = (uint32)0u;
    /* -- dropped ingress packets due to CRC errors -- */
    DropCountPtr[1] = (uint32)0u;
    /* -- number of undersized ingress packets less than 64 bytes (IETF RFC1757) -- */
    DropCountPtr[2] = (uint32)0u;
    /* -- number of oversized ingress packets longer than 1518 bytes (IETF RFC1757) -- */
    DropCountPtr[3] = (uint32)0xFFFFFFFFu;
    /* -- number of ingress packets with alignment errors -- */
    DropCountPtr[4] = (uint32)0u;
    /* -- number of ingress packets with SQE test error according to IETF RFC1643 -- */
    DropCountPtr[5] = (uint32)0xFFFFFFFFu;
    /* -- number of ingress frames discarded due to need for buffer space (IETF RFC2233) -- */
    DropCountPtr[6] = (uint32)0xFFFFFFFFu;
    /* -- total number of erroneous ingress packets -- */
    DropCountPtr[7] = (uint32)0u;
    /* -- number of egress packets discarded due to need for buffer space (IETF RFC2233) -- */
    DropCountPtr[8] = (uint32)0xFFFFFFFFu;
    /* -- total number of erroneous egress packets -- */
    DropCountPtr[9] = (uint32)0xFFFFFFFFu;
    /* -- number of single collision egress packets -- */
    DropCountPtr[10] = (uint32)0xFFFFFFFFu;
    /* -- number of multiple collision egress packets -- */
    DropCountPtr[11] = (uint32)0xFFFFFFFFu;
    /* -- number of deferred egress packets due to busy medium -- */
    DropCountPtr[12] = (uint32)0xFFFFFFFFu;
    /* -- number of late collision egress packets -- */
    DropCountPtr[13] = (uint32)0xFFFFFFFFu;
  }

  /* #20 Iterate over ports */
  /* retrieve supported counters */
  for( LoopPortIdx = 0u; LoopPortIdx < InstanceConfig->PortNum; LoopPortIdx++ )
  {
    uint32 Address;
    uint8 HwPortIdx;

    if( RetVal == (Std_ReturnType)E_NOT_OK ) { break; }

    HwPortIdx = InstanceConfig->TransformPortIdx((EthSwt_PortIdxType)LoopPortIdx, ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_INTERNAL_VIEW);

    /* #200 Retrieve supported counters */
    /* -- dropped ingress packets due to buffer overrun -- */
    Address = (uint32)((uint32)ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_2_REG_BASE_ADDR
                                    + ((uint32)HwPortIdx * (uint32)ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_2_REG_OFFSET));
    /* sum of PART_DROP and QFULL */
    /* PART_DROP */
    SpiTransaction->AddrIdx = Address + (uint32)ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_2_PART_DROP_REG_OFFSET;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    DropCountPtr[0] += SpiTransaction->DataPtr[0];
    /* QFULL */
    SpiTransaction->AddrIdx = Address + (uint32)ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_2_QFULL_REG_OFFSET;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    DropCountPtr[0] += SpiTransaction->DataPtr[0];

    /* -- dropped ingress packets due to CRC errors -- */
    Address = (uint32)((uint32)ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_1_REG_BASE_ADDR
                                        + ((uint32)HwPortIdx * (uint32)ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_1_REG_OFFSET));
    /* N_CRCERR */
    SpiTransaction->AddrIdx = Address + (uint32)ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_1_N_CRCERR_REG_OFFSET;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    DropCountPtr[1] += SpiTransaction->DataPtr[0];

    /* -- number of undersized ingress packets less than 64 bytes (IETF RFC1757) -- */
    Address = (uint32)((uint32)ETHSWT_30_SJA1105PQRS_ETH_MAC_DIAG_COUNTERS_REG_BASE_ADDR
                                            + ((uint32)HwPortIdx * (uint32)ETHSWT_30_SJA1105PQRS_ETH_MAC_DIAG_COUNTERS_REG_OFFSET));
    SpiTransaction->AddrIdx = Address;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    /* N_RUNT */
    DropCountPtr[2] += (uint32)((SpiTransaction->DataPtr[0] & (uint32)ETHSWT_30_SJA1105PQRS_ETH_MAC_DIAG_COUNTERS_REG_N_RUNT_MASK)
                                  >> (uint32)ETHSWT_30_SJA1105PQRS_ETH_MAC_DIAG_COUNTERS_REG_N_RUNT_SHIFT);

    /* -- number of ingress packets with alignment errors -- */
    /* N_ALIGNERR */
    DropCountPtr[4] += (uint32)((SpiTransaction->DataPtr[0] & (uint32)ETHSWT_30_SJA1105PQRS_ETH_MAC_DIAG_COUNTERS_REG_N_ALIGNERR_MASK)
                                  >> (uint32)ETHSWT_30_SJA1105PQRS_ETH_MAC_DIAG_COUNTERS_REG_N_ALIGNERR_SHIFT);
  }

  /* #210 Aggregate supported counters to summary counter */
  if( RetVal == (Std_ReturnType)E_OK )
  {
    /* -- total number of erroneous ingress packets -- */
    DropCountPtr[7] = DropCountPtr[0] +
                      DropCountPtr[1] +
                      DropCountPtr[2] +
                      DropCountPtr[4];
  }

  if( IsSpiTransactionProvided == (boolean)TRUE )
  {
    /* release SPI transaction */
    (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(SwitchIdx, SpiTransaction);
  }

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_VGetDropCount() */
#endif /* ETHSWT_30_SJA1105PQRS_GET_DROP_COUNT_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_GET_ETHER_STATS_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_VGetEtherStats()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_VGetEtherStats(
                 EthSwt_SwitchIdxType               SwitchIdx,
                 EthSwt_PortIdxType                 SwitchPortIdx,
    ETHSWT_P2VAR(uint32,              SJA1105PQRS)  EtherStats )
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  InstanceConfig;
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS)  SpiTransaction;
                 Std_ReturnType                                          RetVal;

  /* ----- Local data definition ---------------------------------------- */
  InstanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx];

  /* ----- Implementation ----------------------------------------------- */

  RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(SwitchIdx, &SpiTransaction);

  if( RetVal == (Std_ReturnType)E_OK )
  {
    uint32 Address;
    uint8  HwPortIdx;

    HwPortIdx = InstanceConfig->TransformPortIdx(SwitchPortIdx,
                                                 ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_INTERNAL_VIEW);

    /* #10 Set unsupported counters to max value */
    /* initialize unsupported counters to default value */
    /* EtherStatsDropEvents */
    EtherStats[0] = (uint32)0xFFFFFFFFUL;
    /* etherStatsOversizePkts */
    EtherStats[7] = (uint32)0xFFFFFFFFUL;
    /* etherStatsFragments */
    EtherStats[8] = (uint32)0xFFFFFFFFUL;
    /* etherStatsJabbers */
    EtherStats[9] = (uint32)0xFFFFFFFFUL;
    /* etherStatsCollisions */
    EtherStats[10] = (uint32)0xFFFFFFFFUL;


    /* #20 Retrieve supported counters */
    /* retrieve supported counters */
    /* etherStatsOctets */
    Address = (uint32)((uint32)ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_1_REG_BASE_ADDR
                                        + ((uint32)HwPortIdx * (uint32)ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_1_REG_OFFSET));
    /* sum of N_RXBYTE and N_TXBYTE */
    /* N_RXBYTE (only lower part of 64 bit counter taken because target buffer is only able to hold 32 bit) */
    SpiTransaction->AddrIdx = Address + (uint32)ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_1_N_RXBYTE_REG_OFFSET;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    EtherStats[1] = SpiTransaction->DataPtr[0];
    /* N_TXBYTE (only lower part of 64 bit counter taken because target buffer is only able to hold 32 bit) */
    SpiTransaction->AddrIdx = Address + (uint32)ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_1_N_TXBYTE_REG_OFFSET;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    EtherStats[1] += SpiTransaction->DataPtr[0];

    /* etherStatsPkts */
    /* sum of N_RXFRM and N_TXFRM */
    /* N_RXFRM (only lower part of 64 bit counter taken because target buffer is only able to hold 32 bit) */
    SpiTransaction->AddrIdx = Address + (uint32)ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_1_N_RXFRM_REG_OFFSET;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    EtherStats[2] = SpiTransaction->DataPtr[0];
    /* N_TXFRM (only lower part of 64 bit counter taken because target buffer is only able to hold 32 bit) */
    SpiTransaction->AddrIdx = Address + (uint32)ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_1_N_TXFRM_REG_OFFSET;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    EtherStats[2] += SpiTransaction->DataPtr[0];

    /* EtherStatsCrcAlignErrors */
    /* sum of N_CRC_ERROR and N_ALIGNERR */
    /* N_CRC_ERROR */
    SpiTransaction->AddrIdx = Address + (uint32)ETHSWT_30_SJA1105PQRS_ETH_HIGH_PORT_STATUS_1_N_CRCERR_REG_OFFSET;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    EtherStats[5] = SpiTransaction->DataPtr[0];
    /* N_ALIGNERR */
    Address = (uint32)((uint32)ETHSWT_30_SJA1105PQRS_ETH_MAC_DIAG_COUNTERS_REG_BASE_ADDR
                                                + ((uint32)HwPortIdx * (uint32)ETHSWT_30_SJA1105PQRS_ETH_MAC_DIAG_COUNTERS_REG_OFFSET));
    SpiTransaction->AddrIdx = Address;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    EtherStats[5] += (uint32)((SpiTransaction->DataPtr[0] & (uint32)ETHSWT_30_SJA1105PQRS_ETH_MAC_DIAG_COUNTERS_REG_N_ALIGNERR_MASK)
                                >> (uint32)ETHSWT_30_SJA1105PQRS_ETH_MAC_DIAG_COUNTERS_REG_N_ALIGNERR_SHIFT);

    /* EtherStatsUndersizePkts */
    /* N_RUNT */
    EtherStats[6] = (uint32)((SpiTransaction->DataPtr[0] & (uint32)ETHSWT_30_SJA1105PQRS_ETH_MAC_DIAG_COUNTERS_REG_N_RUNT_MASK)
                                >> (uint32)ETHSWT_30_SJA1105PQRS_ETH_MAC_DIAG_COUNTERS_REG_N_RUNT_SHIFT);


    /* base address of Ethernet statistics counter registers */
    Address = (uint32)((uint32)ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_REG_BASE_ADDR
                                            + ((uint32)HwPortIdx * (uint32)ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_REG_OFFSET));

    /* EtherStatsBroadcastPkts */
    /* sum of RX_BCAST and TX_BCAST */
    /* RX_BCAST */
    SpiTransaction->AddrIdx = Address + (uint32)ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_RX_BCAST_REG_OFFSET;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    EtherStats[3] = SpiTransaction->DataPtr[0];
    /* TX_BCAST */
    SpiTransaction->AddrIdx = Address + (uint32)ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_TX_BCAST_REG_OFFSET;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    EtherStats[3] += SpiTransaction->DataPtr[0];

    /* EtherStatsMulticastPkts */
    /* sum of RX_MCAST and TX_MCAST */
    /* RX_MCAST */
    SpiTransaction->AddrIdx = Address + (uint32)ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_RX_MCAST_REG_OFFSET;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    EtherStats[4] = SpiTransaction->DataPtr[0];
    /* TX_MCAST */
    SpiTransaction->AddrIdx = Address + (uint32)ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_TX_MCAST_REG_OFFSET;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    EtherStats[4] += SpiTransaction->DataPtr[0];

    /* EtherStatsPkts64Octets */
    /* sum of RX_BYTES_64 and TX_BYTES_64 */
    /* RX_BYTES_64 */
    SpiTransaction->AddrIdx = Address + (uint32)ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_RX_BYTES_64_REG_OFFSET;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    EtherStats[11] = SpiTransaction->DataPtr[0];
    /* TX_BYTES_64 */
    SpiTransaction->AddrIdx = Address + (uint32)ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_TX_BYTES_64_REG_OFFSET;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    EtherStats[11] += SpiTransaction->DataPtr[0];

    /* EtherStatsPkts65to127Octets */
    /* sum of RX_BYTES_65_127  and TX_BYTES_65_127  */
    /* RX_BYTES_65_127 */
    SpiTransaction->AddrIdx = Address + (uint32)ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_RX_BYTES_65_127_REG_OFFSET;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    EtherStats[12] = SpiTransaction->DataPtr[0];
    /* TX_BYTES_65_127 */
    SpiTransaction->AddrIdx = Address + (uint32)ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_TX_BYTES_65_127_REG_OFFSET;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    EtherStats[12] += SpiTransaction->DataPtr[0];

    /* EtherStatsPkts128to255Octets */
    /* sum of RX_BYTES_128_255  and TX_BYTES_128_255 */
    /* RX_BYTES_128_255 */
    SpiTransaction->AddrIdx = Address + (uint32)ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_RX_BYTES_128_255_REG_OFFSET;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    EtherStats[13] = SpiTransaction->DataPtr[0];
    /* TX_BYTES_128_255 */
    SpiTransaction->AddrIdx = Address + (uint32)ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_TX_BYTES_128_255_REG_OFFSET;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    EtherStats[13] += SpiTransaction->DataPtr[0];

    /* EtherStatsPkts256to511Octets */
    /* sum of RX_BYTES_256_511 and TX_BYTES_256_511  */
    /* RX_BYTES_256_511 */
    SpiTransaction->AddrIdx = Address + (uint32)ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_RX_BYTES_256_511_REG_OFFSET;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    EtherStats[14] = SpiTransaction->DataPtr[0];
    /* TX_BYTES_256_511 */
    SpiTransaction->AddrIdx = Address + (uint32)ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_TX_BYTES_256_511_REG_OFFSET;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    EtherStats[14] += SpiTransaction->DataPtr[0];

    /* EtherStatsPkts512to1023Octets */
    /* sum of RX_BYTES_512_1023 and TX_BYTES_512_1023 */
    /* RX_BYTES_512_1023 */
    SpiTransaction->AddrIdx = Address + (uint32)ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_RX_BYTES_512_1023_REG_OFFSET;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    EtherStats[15] = SpiTransaction->DataPtr[0];
    /* TX_BYTES_512_1023 */
    SpiTransaction->AddrIdx = Address + (uint32)ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_TX_BYTES_512_1023_REG_OFFSET;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    EtherStats[15] += SpiTransaction->DataPtr[0];

    /* EtherStatsPkts1024to1518Octets */
    /* sum of RX_BYTES_1024_1518 and TX_BYTES_1024_1518 */
    /* RX_BYTES_1024_1518 */
    SpiTransaction->AddrIdx = Address + (uint32)ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_RX_BYTES_1024_1518_REG_OFFSET;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    EtherStats[16] = SpiTransaction->DataPtr[0];
    /* TX_BYTES_1024_1518 */
    SpiTransaction->AddrIdx = Address + (uint32)ETHSWT_30_SJA1105PQRS_ETH_STATS_COUNTERS_TX_BYTES_1024_1518_REG_OFFSET;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);
    EtherStats[16] += SpiTransaction->DataPtr[0];

    (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(SwitchIdx, SpiTransaction);
  }

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_VGetEtherStats() */
#endif /* ETHSWT_30_SJA1105PQRS_GET_ETHER_STATS_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_VStoreConfiguration()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
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
 *
 *
 */
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_VStoreConfiguration(
    EthSwt_SwitchIdxType  SwitchIdx )
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_NvmBufferType, SJA1105PQRS)  NvmBufferPtr;
               Std_ReturnType                                     RetVal;
               uint16_least                                       TableEntryIdx;
               uint16                                             ReadEntriesCnt;

  /* ----- Local data definition ---------------------------------------- */
  NvmBufferPtr   = EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].NvmBuffer;
  ReadEntriesCnt = (uint32)0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all available entries of lookup table */
  /* SJA1105PQRS only supports iterating over whole L2 lookup table to retrieve the valid entries of the table */
  for( TableEntryIdx = 0u; TableEntryIdx < ETHSWT_30_SJA1105PQRS_LOOKUP_TABLE_ENTRY_NUM; TableEntryIdx++ )
  {
    /* #100 If no space left in destination buffer */
    /* check if there is enough space left in the passed array */
    if( ReadEntriesCnt == ETHSWT_30_SJA1105PQRS_MAX_ARL_TABLE_ENTRIES )
    {
      /* #1000 Stop processing */
      /* not enough space */
      break;
    }

    /* #110 Read a lookup table entry */
    RetVal = EthSwt_30_Sja1105PQRS_ReadL2LookupTableEntry(SwitchIdx,
                                                          (uint16)TableEntryIdx,
                                                          &NvmBufferPtr->BufferData[ReadEntriesCnt],
                                                          (EthSwt_30_Sja1105PQRS_L2LookupTableEntryTypeType)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_ENTRY_DYNAMIC_TYPE);

    /* #120 If entry is valid */
    if( RetVal == (Std_ReturnType)E_OK )
    {
      /* #1200 Increase the count of read entries */
      /* increase the read entries count if read was successful */
      ReadEntriesCnt++;
    }
  }

  /* #20 If at least one entry is read and destination buffer was large enough */
  if( (ReadEntriesCnt > 0u)                                       &&
      (ReadEntriesCnt != ETHSWT_30_SJA1105PQRS_MAX_ARL_TABLE_ENTRIES)    )
  {
    /* #200 Set return value to E_OK to indicate success */
    RetVal = (Std_ReturnType)E_OK;
  }
  /* #30 Else */
  else
  {
    /* #300 Set return value to E_NOT_OK to indicate fail */
    RetVal = (Std_ReturnType)E_NOT_OK;
  }

  /* #40 Pass count of read entries */
  NvmBufferPtr->Entries = ReadEntriesCnt;

  /* #50 If processing was successful */
  if( RetVal == (Std_ReturnType)E_OK )
  {
    /* #500 Trigger NvM to store the configuration in NV-RAM */
    /* trigger NvM write */
    RetVal = NvM_WriteBlock(
                    EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].NvmBlockId,
                    (void *)NvmBufferPtr);
  }

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_VStoreConfiguration() */
#endif /* ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_VResetConfiguration()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_VResetConfiguration(
    EthSwt_SwitchIdxType  SwitchIdx )
{
  /* ----- Local data declaration --------------------------------------- */
  Std_ReturnType  RetVal;

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Invalidate RAM buffer of NV-RAM */
  /* set entry count to 0 to reset configuration */
  EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].NvmBuffer->Entries = (uint16)0u;

  /* #20 Trigger NV-RAM invalidation */
  RetVal = NvM_InvalidateNvBlock(EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].NvmBlockId);

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_VResetConfiguration() */
#endif /* ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_RESTORE_CONFIGURATION_API == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_RestoreConfiguration()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
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
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_RestoreConfiguration(
  EthSwt_SwitchIdxType  SwitchIdx )
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS) InstanceConfig;
                 Std_ReturnType                                         RetVal;
                 NvM_RequestResultType                                  NvmReqResult;

  /* ----- Local data definition ---------------------------------------- */
  InstanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx];

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Retrieve information about NV-RAM */
  RetVal = NvM_GetErrorStatus(InstanceConfig->NvmBlockId, &NvmReqResult);

  if( RetVal == (Std_ReturnType)E_OK )
  {
    /* #20 If NV-RAM is valid */
    if(    (NvmReqResult == (NvM_RequestResultType)NVM_REQ_OK)
        || (NvmReqResult == (NvM_RequestResultType)NVM_REQ_BLOCK_SKIPPED) )
    {
      /* #200 Trigger read of NV-RAM */
      RetVal = NvM_ReadBlock(InstanceConfig->NvmBlockId, InstanceConfig->NvmBuffer);

      if( RetVal == (Std_ReturnType)E_OK )
      {
        /* #210 Wait till NV-RAM read has finished */
        do
        {
          RetVal = NvM_GetErrorStatus(InstanceConfig->NvmBlockId, &NvmReqResult);
        }
        while(    (RetVal == (Std_ReturnType)E_OK)
               && (NvmReqResult == (NvM_RequestResultType)NVM_REQ_PENDING) );

        /* #220 If read was successful */
        if( NvmReqResult == (NvM_RequestResultType)NVM_REQ_OK )
        {
          uint16_least EntryIdx;
          EthSwt_30_Sja1105PQRS_MgmtRouteCfgType MgmtRouteCfg;
          MgmtRouteCfg.EnableMgmtRoute = FALSE;
          MgmtRouteCfg.EnableTimeStamp = FALSE;

          /* #2200 For each lookup table entry retrieved out of NV-RAM */
          for( EntryIdx = 0u; EntryIdx < InstanceConfig->NvmBuffer->Entries; EntryIdx++ )
          {
            uint8                                               SubEntryIdx;
            EthSwt_30_Sja1105PQRS_L2LookupTableWriteResultType  L2LookupTableWriteResult;

            SubEntryIdx = 0;

            if( RetVal == (Std_ReturnType)E_NOT_OK ) { break; }

            /* #22000 For each available sub-entry in lookup table */
            do
            {
              ETHSWT_P2CONST(EthSwt_MacVlanType, SJA1105PQRS) MacVlanPtr = &InstanceConfig->NvmBuffer->BufferData[EntryIdx];
              uint8 SwitchHwPortMask = (uint8)(1 << InstanceConfig->TransformPortIdx(MacVlanPtr->SwitchPort,
                  ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_INTERNAL_VIEW));

              /* #220000 Trigger download of entry */
              RetVal = EthSwt_30_Sja1105PQRS_WriteL2LookupTableEntry(
                                          SwitchIdx,
                                          (uint16) EntryIdx,
                                          MacVlanPtr->MacAddr,
                                          MacVlanPtr->VlanId,
                                          SwitchHwPortMask,
                                          &MgmtRouteCfg,
                                          FALSE,
                                          &L2LookupTableWriteResult);

              SubEntryIdx++;
            }
            /* - #220010 Repeat until each sub-entry is loaded down */
            while(    (RetVal == (Std_ReturnType)E_OK)
                   && (L2LookupTableWriteResult == (EthSwt_30_Sja1105PQRS_L2LookupTableWriteResultType)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_WRITE_OCCUPIED)
                   && (SubEntryIdx < (uint8)ETHSWT_30_SJA1105PQRS_LOOKUP_TABLE_HASH_ENTRY_NUM));
          }
        }
      }
    }
  }

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_RestoreConfiguration() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ETHSWT_30_SJA1105PQRS_RESTORE_CONFIGURATION_API */

#if ( ETHSWT_30_SJA1105PQRS_PROD_ERROR_REPORTING == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_ReportProdErrors()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
STATIC INLINE ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_ReportProdErrors(
  EthSwt_SwitchIdxType  SwitchIdx )
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  InstanceConfig;
  ETHSWT_P2CONST(uint32,                                   SJA1105PQRS)  DropCounts;

  /* ----- Local data definition ---------------------------------------- */
  InstanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx];
  DropCounts     = &EthSwt_30_Sja1105PQRS_ProdErrorDetect_DropCounts[SwitchIdx][0];

  /* ----- Implementation ----------------------------------------------- */
  /* -- dropped packets due to overrun --------------------------- */
  if(    ( 0 < DropCounts[0] )
      && ( DEM_EVENT_INVALID != InstanceConfig->DemDropCountEvents->E_BUFFEROVERRUN ))
  {
    Dem_ReportErrorStatus(InstanceConfig->DemDropCountEvents->E_BUFFEROVERRUN, DEM_EVENT_STATUS_FAILED);
    InstanceConfig->DemEventReports->E_BUFFEROVERRUN_Reported = TRUE;
  }
  else
  {
    if( TRUE == InstanceConfig->DemEventReports->E_BUFFEROVERRUN_Reported )
    {
      Dem_ReportErrorStatus(InstanceConfig->DemDropCountEvents->E_BUFFEROVERRUN, DEM_EVENT_STATUS_PASSED);
      InstanceConfig->DemEventReports->E_BUFFEROVERRUN_Reported = FALSE;
    }
  }

  /* -- dropped packets due to CRC error --------------------------- */
  if(    ( 0 < DropCounts[1] )
      && ( DEM_EVENT_INVALID != InstanceConfig->DemDropCountEvents->E_CRC ))
  {
    Dem_ReportErrorStatus(InstanceConfig->DemDropCountEvents->E_CRC, DEM_EVENT_STATUS_FAILED);
    InstanceConfig->DemEventReports->E_CRC_Reported = TRUE;
  }
  else
  {
    if( TRUE == InstanceConfig->DemEventReports->E_CRC_Reported )
    {
      Dem_ReportErrorStatus(InstanceConfig->DemDropCountEvents->E_CRC, DEM_EVENT_STATUS_PASSED);
      InstanceConfig->DemEventReports->E_CRC_Reported = FALSE;
    }
  }

  /* -- number of undersize packets -------------- */
  if(    ( 0 < DropCounts[2] )
      && ( DEM_EVENT_INVALID != InstanceConfig->DemDropCountEvents->E_UNDERSIZEPCKT ))
  {
    Dem_ReportErrorStatus(InstanceConfig->DemDropCountEvents->E_UNDERSIZEPCKT, DEM_EVENT_STATUS_FAILED);
    InstanceConfig->DemEventReports->E_UNDERSIZEPCKT_Reported = TRUE;
  }
  else
  {
    if( TRUE == InstanceConfig->DemEventReports->E_UNDERSIZEPCKT_Reported )
    {
      Dem_ReportErrorStatus(InstanceConfig->DemDropCountEvents->E_UNDERSIZEPCKT, DEM_EVENT_STATUS_PASSED);
      InstanceConfig->DemEventReports->E_UNDERSIZEPCKT_Reported = FALSE;
    }
  }

  /* -- number of oversize packets ------------- */
  /* hardware doesn't support this counter */

  /* -- number of alignment errors ------------------- */
  if(    ( 0 < DropCounts[4] )
      && ( DEM_EVENT_INVALID != InstanceConfig->DemDropCountEvents->E_ALIGNMENT ))
  {
    Dem_ReportErrorStatus(InstanceConfig->DemDropCountEvents->E_ALIGNMENT, DEM_EVENT_STATUS_FAILED);
    InstanceConfig->DemEventReports->E_ALIGNMENT_Reported = TRUE;
  }
  else
  {
    if( TRUE == InstanceConfig->DemEventReports->E_ALIGNMENT_Reported )
    {
      Dem_ReportErrorStatus(InstanceConfig->DemDropCountEvents->E_ALIGNMENT, DEM_EVENT_STATUS_PASSED);
      InstanceConfig->DemEventReports->E_ALIGNMENT_Reported = FALSE;
    }
  }

  /* -- SQE test errors ----------------------------- */
  /* hardware doesn't support this counter */

  /* -- ifInDiscards --------------------------------- */
  /* hardware doesn't support this counter */

  /* -- total number of erroneous inbound packets ------ */
  if(    ( 0 < DropCounts[7] )
      && ( DEM_EVENT_INVALID != InstanceConfig->DemDropCountEvents->E_INERROR ))
  {
    Dem_ReportErrorStatus(InstanceConfig->DemDropCountEvents->E_INERROR, DEM_EVENT_STATUS_FAILED);
    InstanceConfig->DemEventReports->E_INERROR_Reported = TRUE;
  }
  else
  {
    if( TRUE == InstanceConfig->DemEventReports->E_INERROR_Reported )
    {
      Dem_ReportErrorStatus(InstanceConfig->DemDropCountEvents->E_INERROR, DEM_EVENT_STATUS_PASSED);
      InstanceConfig->DemEventReports->E_INERROR_Reported = FALSE;
    }
  }
  /* -- ifOutDiscards -------------------------- */
  /* hardware doesn't support this counter */

  /* -- total number of erroneous outbound packets ---- */
  /* hardware doesn't support this counter */

  /* -- single collision frames on transmit ---- */
  /* hardware doesn't support this counter */

  /* -- multiple collision frames on transmit ---- */
  /* hardware doesn't support this counter */

  /* -- number of deferred transmission ---- */
  /* hardware doesn't support this counter */

  /* -- number of late collisions on transmit ---- */
  /* hardware doesn't support this counter */

} /* EthSwt_30_Sja1105PQRS_ReportProdErrors() */ /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */
#endif /* ETHSWT_30_SJA1105PQRS_PROD_ERROR_REPORTING */

#if ( ETHSWT_30_SJA1105PQRS_PROD_ERROR_REPORTING == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_DetectProdErrors()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC INLINE ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_DetectProdErrors(
  EthSwt_SwitchIdxType  SwitchIdx )
{
  /* ----- Local data declaration --------------------------------------- */
  Std_ReturnType  RetVal;
  static ETHSWT_VAR_WITH_MEM(uint16, VAR_NOINIT, SJA1105PQRS) EthSwt_30_Sja1105PQRS_ProdErrorDetect_DropCountNum[ETHSWT_30_SJA1105PQRS_SWITCH_NUM];

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
# if   ( ETHSWT_30_SJA1105PQRS_API_CALL_TYPE == ETHSWT_30_SJA1105PQRS_API_CALL_TYPE_ASYNC_CALL )
  if( EthSwt_30_Sja1105PQRS_ProdErrorDetect_IsPending[SwitchIdx] == (boolean)FALSE )
  {
    EthSwt_30_Sja1105PQRS_ProdErrorDetect_IsPending[SwitchIdx] = (boolean)TRUE;
# endif /* ETHSWT_30_SJA1105PQRS_API_CALL_TYPE */

    /* #10 Retrieve drop counters */
    EthSwt_30_Sja1105PQRS_ProdErrorDetect_DropCountNum[SwitchIdx] = ETHSWT_30_SJA1105PQRS_DROP_COUNT_COUNTERS_NUM;
    RetVal = EthSwt_30_Sja1105PQRS_GetDropCount(SwitchIdx,
                                                &EthSwt_30_Sja1105PQRS_ProdErrorDetect_DropCountNum[SwitchIdx],
                                                &EthSwt_30_Sja1105PQRS_ProdErrorDetect_DropCounts[SwitchIdx][0]);

# if   ( ETHSWT_30_SJA1105PQRS_API_CALL_TYPE == ETHSWT_30_SJA1105PQRS_API_CALL_TYPE_ASYNC_CALL )
    if( RetVal == (Std_ReturnType)E_NOT_OK )
    {
      EthSwt_30_Sja1105PQRS_ProdErrorDetect_IsPending[SwitchIdx] = (boolean)FALSE;
    }
  }
# elif ( ETHSWT_30_SJA1105PQRS_API_CALL_TYPE == ETHSWT_30_SJA1105PQRS_API_CALL_TYPE_SYNC_CALL )
  /* check if call was successful */
  if( RetVal == (Std_ReturnType)E_OK )
  {
    /* Analyze drop counters */
    EthSwt_30_Sja1105PQRS_ReportProdErrors(SwitchIdx);
  }
# endif /* ETHSWT_30_SJA1105PQRS_API_CALL_TYPE */

} /* EthSwt_30_Sja1105PQRS_DetectProdErrors() */
#endif /* ETHSWT_30_SJA1105PQRS_PROD_ERROR_REPORTING */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_EnableRgmiiTdl()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_EnableRgmiiTdl(
    uint8 SwitchIdx,
    uint8 PortIdx)
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS) InstanceConfig;
  Std_ReturnType RetVal;
  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  InstanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx];
  /* #10 Check if RGMII is configured for the requested switch port */
  if( InstanceConfig->PortMiiIfcs[PortIdx] == ETHSWT_30_SJA1105PQRS_PORT_MII_IFC_RGMII )
  {
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS) SpiTransaction;
    /* #100 Get hardware port number */
    uint8 HwPortIdx = InstanceConfig->TransformPortIdx(PortIdx,
        ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_INTERNAL_VIEW);

    /* #110 Enable Rx and Tx delay depending on configuration */
    RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(SwitchIdx, &SpiTransaction);
    if( RetVal == (Std_ReturnType)E_OK )
    {
      uint32 data = 0;
      if( InstanceConfig->RgmiiIfc[PortIdx].RxDelayEnabled == STD_OFF )
      {
        data |= (ETHSWT_30_SJA1105PQRS_CFG_PAD_MII_ID_RXC_BYPASS_MASK |
                 ETHSWT_30_SJA1105PQRS_CFG_PAD_MII_ID_RXC_PD_MASK);
      }
      if( InstanceConfig->RgmiiIfc[PortIdx].TxDelayEnabled == STD_OFF )
      {
        data |= (ETHSWT_30_SJA1105PQRS_CFG_PAD_MII_ID_TXC_BYPASS_MASK |
                                       ETHSWT_30_SJA1105PQRS_CFG_PAD_MII_ID_TXC_PD_MASK);
      }
      data |= InstanceConfig->RgmiiIfc[PortIdx].Cfg_pad_miix_id;
      SpiTransaction->DataPtr[0]  = data;
      SpiTransaction->AddrIdx     = (uint32)(ETHSWT_30_SJA1105PQRS_CFG_PAD_MII0_ID_REG_ADDR + HwPortIdx);
      RetVal = EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(SwitchIdx, SpiTransaction);
      (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(SwitchIdx, SpiTransaction);
    }
  }
  /* #20 Otherwise */
  else
  {
    /* #200 Nothing to do, no RGMII configured */
    RetVal = E_OK;
  }
  return RetVal;
} /* EthSwt_30_Sja1105PQRS_EnableRgmiiTdl() */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_DisableRgmiiTdl()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_DisableRgmiiTdl(
    uint8 SwitchIdx,
    uint8 PortIdx)
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  InstanceConfig;
  Std_ReturnType RetVal;

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  InstanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx];
  /* #10 Check if RGMII is configured for the requested switch port */
  if( InstanceConfig->PortMiiIfcs[PortIdx] == ETHSWT_30_SJA1105PQRS_PORT_MII_IFC_RGMII )
  {
    /* #100 Disable RGMII specific settings */
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS) SpiTransaction;
    RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(SwitchIdx, &SpiTransaction);
    if( RetVal == (Std_ReturnType)E_OK )
    {
      uint8 HwPortIdx = InstanceConfig->TransformPortIdx(PortIdx,
          ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_INTERNAL_VIEW);
      SpiTransaction->AddrIdx     = (uint32)(ETHSWT_30_SJA1105PQRS_CFG_PAD_MII0_ID_REG_ADDR + HwPortIdx);
      SpiTransaction->DataPtr[0]  = (ETHSWT_30_SJA1105PQRS_CFG_PAD_MII_ID_RXC_BYPASS_MASK  |
                                     ETHSWT_30_SJA1105PQRS_CFG_PAD_MII_ID_TXC_BYPASS_MASK  |
                                     ETHSWT_30_SJA1105PQRS_CFG_PAD_MII_ID_RXC_PD_MASK      |
                                     ETHSWT_30_SJA1105PQRS_CFG_PAD_MII_ID_TXC_PD_MASK);
      RetVal = EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(SwitchIdx, SpiTransaction);
      (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(SwitchIdx, SpiTransaction);
    }
  }
  /* #20 Otherwise */
  else
  {
    /* #200 Nothing to do, no RGMII configured */
    RetVal = E_OK;
  }
  return RetVal;
} /* EthSwt_30_Sja1105PQRS_DisableRgmiiTdl() */

#if (ETHSWT_30_SJA1105PQRS_UPDATE_MCAST_PORT_ASSIGN_API_ENABLED == STD_ON)
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_PrepareAddressOfMCastEntry()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_PrepareAddressOfMCastEntry(
  ETHSWT_P2CONST(uint8,                                               SJA1105PQRS) mCastAddr,
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_UpdateMCastPortAssignBucketType, SJA1105PQRS)  mCastEntry)
{
  /* ----- Local data declaration --------------------------------------- */

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if any port request is pending */
  if( EthSwt_30_Sja1105PQRS_IsAnyBucketRequested((ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_PortBucketsType, SJA1105PQRS))&mCastEntry->PortRequests) == TRUE ) /*lint !e545 */
  {
    /* #100 At least one port request is pending -> Set multicast address in entry (entry is now valid) */
    EthSwt_30_Sja1105PQRS_CopyMacAddr(mCastAddr, mCastEntry->Multicast);
  }
  /* #20 Otherwise */
  else
  {
    /* #200 No port request is pending anymore -> Clear first byte of address in entry (entry is now invalid) */
    mCastEntry->Multicast[0] = 0x00u;
  }

} /* EthSwt_30_Sja1105PQRS_PrepareAddressOfMCastEntry() */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetMCastPortAssignBucketsForActionAdd()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetMCastPortAssignBucketsForActionAdd(
  ETHSWT_P2CONST(uint8,                                                                            SJA1105PQRS) mCastAddr,
    ETHSWT_P2VAR(ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_UpdateMCastPortAssignBucketType, SJA1105PQRS), SJA1105PQRS) mCastEntry)
{
  /* ----- Local data declaration --------------------------------------- */
  boolean     result;
  uint8_least mCastEntyIdx;

  /* ----- Local data definition ---------------------------------------- */
  result        = FALSE;
  (*mCastEntry) = (ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_UpdateMCastPortAssignBucketType, SJA1105PQRS))NULL_PTR;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Query for a multicast bucket entry for the given multicast address */
  for( mCastEntyIdx = 0; mCastEntyIdx < ETHSWT_30_SJA1105PQRS_MAX_PARALLEL_MCAST_PORT_ASSIGNMENTS; mCastEntyIdx++ )
  {
    /* #100 Check if the multicast address matches the one of the entry and if this is the case stop query and return the
     *      found entry */
    if( EthSwt_30_Sja1105PQRS_IsMacEqual(mCastAddr, EthSwt_30_Sja1105PQRS_UpdateMCastPortAssignBuckets[mCastEntyIdx].Multicast) == TRUE )
    {
      (*mCastEntry) = &EthSwt_30_Sja1105PQRS_UpdateMCastPortAssignBuckets[mCastEntyIdx];
      break;
    }

    /* #110 Check if the entry is empty and if this is the case store it for returning but continue query for a
     *      entry representing the multicast address */
    if( (*mCastEntry) == (ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_UpdateMCastPortAssignBucketType, SJA1105PQRS))NULL_PTR )
    {
      /* no bucket assigned yet -> use this bucket if it is free */
      if( EthSwt_30_Sja1105PQRS_UpdateMCastPortAssignBuckets[mCastEntyIdx].Multicast[0] == 0x00u )
      {
        (*mCastEntry) = &EthSwt_30_Sja1105PQRS_UpdateMCastPortAssignBuckets[mCastEntyIdx];
      }
    }
  }

  /* #20 Check if either a matching or an empty entry could be found and prepare result for the caller */
  if( (*mCastEntry) != (ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_UpdateMCastPortAssignBucketType, SJA1105PQRS))NULL_PTR )
  {
    result = TRUE;
  }

  return result;
} /* EthSwt_30_Sja1105PQRS_GetMCastPortAssignBucketForActionAdd() */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetMCastPortAssignBucketsForActionRemove()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
STATIC INLINE ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetMCastPortAssignBucketsForActionRemove(
  ETHSWT_P2CONST(uint8,                                                                            SJA1105PQRS) mCastAddr,
    ETHSWT_P2VAR(ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_UpdateMCastPortAssignBucketType, SJA1105PQRS), SJA1105PQRS) mCastEntry)
{
  /* ----- Local data declaration --------------------------------------- */
  boolean      result;
  uint8_least  mCastEntryIdx;

  /* ----- Local data definition ---------------------------------------- */
  result = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Query for the multicast bucket entry representing the given multicast address and return it to the caller
   *     if found */
  for( mCastEntryIdx = 0; mCastEntryIdx < ETHSWT_30_SJA1105PQRS_MAX_PARALLEL_MCAST_PORT_ASSIGNMENTS; mCastEntryIdx++ )
  {
    /* Check if multicast address already is representet by a bucket */
    if( EthSwt_30_Sja1105PQRS_IsMacEqual(mCastAddr, EthSwt_30_Sja1105PQRS_UpdateMCastPortAssignBuckets[mCastEntryIdx].Multicast) == TRUE )
    {
      (*mCastEntry) = &EthSwt_30_Sja1105PQRS_UpdateMCastPortAssignBuckets[mCastEntryIdx];
      result = TRUE;
      break;
    }
  }

  return result;
} /* EthSwt_30_Sja1105PQRS_GetMCastPortAssignBucketForActionRemove() */
#endif /* ETHSWT_30_SJA1105PQRS_UPDATE_MCAST_PORT_ASSIGN_API_ENABLED */
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_InitMemory()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHSWT_FUNC(void, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_InitMemory( void )
{
  /* ----- Local data declaration --------------------------------------- */
    uint8_least  LoopIdx;

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize module state to UNINIT */
  /* set global initialization state */
  EthSwt_30_Sja1105PQRS_ModuleInitState = (EthSwt_StateType)ETHSWT_STATE_UNINIT;

  /* #20 For each switch instance */
  /* initialize the configuration variables of each instance */
  for( LoopIdx = 0; LoopIdx < ETHSWT_30_SJA1105PQRS_SWITCH_NUM; LoopIdx++ )
  {
    /* #200 Trigger memory initialization */
    EthSwt_30_Sja1105PQRS_InstanceConfig[LoopIdx].InitConfigMemory();
  }

} /* EthSwt_30_Sja1105PQRS_InitMemory() */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_Init()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
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
ETHSWT_FUNC(void, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_Init(
    ETHSWT_P2CONST(EthSwt_ConfigType, SJA1105PQRS)  ConfigPtr )
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType,  SJA1105PQRS)  InstanceConfig;
  uint8_least  LoopIdx;
  uint8 PortIdx; /* PRQA S 781 */ /* MD_EthSwt_30_Sja1105PQRS_781 */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check module initialization state */
  EthSwt_CheckDetErrorReturnVoid(                                                       \
    (EthSwt_30_Sja1105PQRS_ModuleInitState == (EthSwt_StateType)ETHSWT_STATE_UNINIT),   \
    ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                              \
    ETHSWT_30_SJA1105PQRS_SID_INIT,                                                     \
    ETHSWT_30_SJA1105PQRS_E_ALREADY_INITIALIZED); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* ----- Implementation ----------------------------------------------- */
  /* Configuration pointer is unused due to Pre-Compile only support */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(ConfigPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  /* #20 Set module initialization state to INIT */
  /* set global initialization state */
  EthSwt_30_Sja1105PQRS_ModuleInitState = (EthSwt_StateType)ETHSWT_STATE_INIT;

  /* #30 For each switch instance */
  /* set initialization state of each instance */
  for( LoopIdx = 0; LoopIdx < ETHSWT_30_SJA1105PQRS_SWITCH_NUM; LoopIdx++ )
  {
    /* #300 Check for correct memory initialization */
    /* Check if *_INIT_* variables are either initialized by startup code or by explicit call to
     * EthSwt_30_Sja1105PQRS_InitMemory() by verifying a random pattern created during generation. */
    EthSwt_CheckDetErrorReturnVoid(                                       \
        (EthSwt_30_Sja1105PQRS_InstanceData[LoopIdx].InitVerifyPattern    \
             == (uint32)ETHSWT_30_SJA1105PQRS_INIT_VERIFICATION_PATTERN), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                            \
        ETHSWT_30_SJA1105PQRS_SID_INIT,                                   \
        ETHSWT_30_SJA1105PQRS_E_MEMORY_NOT_INITIALIZED); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #310 Set switch instance initialization state to INIT */
    /* set instance variables */
    EthSwt_30_Sja1105PQRS_InstanceData[LoopIdx].InitState = (EthSwt_StateType)ETHSWT_STATE_INIT;

    InstanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[LoopIdx];
#if ( ETHSWT_30_SJA1105PQRS_MANAGEMENT_SUPPORT == STD_ON )
    *(InstanceConfig->FrameManagement->MgmtRouteIndex) = 0;
#endif /* ETHSWT_30_SJA1105PQRS_MANAGEMENT_SUPPORT */

    /* #320 If feature async API processing is enabled */
#if ( ETHSWT_30_SJA1105PQRS_API_CALL_TYPE == ETHSWT_30_SJA1105PQRS_API_CALL_TYPE_ASYNC_CALL )
    /* #3200 Set state variables */
    /* set states for asynchronous processing */
# if ( ETHSWT_30_SJA1105PQRS_GET_ARL_TABLE_API_ENABLED == STD_ON )
    EthSwt_30_Sja1105PQRS_GetArlTableProcessing[LoopIdx].ProcState = ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_IDLE;
# endif /* ETHSWT_30_SJA1105PQRS_GET_ARL_TABLE_API_ENABLED */

# if ( ETHSWT_30_SJA1105PQRS_GET_DROP_COUNT_API_ENABLED == STD_ON )
    EthSwt_30_Sja1105PQRS_GetDropCountProcessing[LoopIdx].ProcState = ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_IDLE;
# endif /* ETHSWT_30_SJA1105PQRS_GET_DROP_COUNT_API_ENABLED */

# if ( ETHSWT_30_SJA1105PQRS_PROD_ERROR_REPORTING == STD_ON )
    EthSwt_30_Sja1105PQRS_ProdErrorDetect_IsPending[LoopIdx] = (boolean)FALSE;
# endif /* ETHSWT_30_SJA1105PQRS_PROD_ERROR_REPORTING */

#endif /* ETHSWT_30_SJA1105PQRS_API_CALL_TYPE */

    for(PortIdx = 0; PortIdx < InstanceConfig->PortNum; PortIdx++)
    {
      InstanceConfig->CurrentLinkStates[PortIdx] = ETHTRCV_LINK_STATE_DOWN;
    }
#if ( ETHSWT_30_SJA1105PQRS_UPDATE_MCAST_PORT_ASSIGN_API_ENABLED == STD_ON )
  {
    uint8_least mCastEntryIdx;

    for( mCastEntryIdx = 0; mCastEntryIdx < ETHSWT_30_SJA1105PQRS_MAX_PARALLEL_MCAST_PORT_ASSIGNMENTS; mCastEntryIdx++ )
    {
      uint8 bucketIdx;

      for( bucketIdx = 0; bucketIdx < ETHSWT_30_SJA1105PQRS_TOTAL_PORTS_NUM; bucketIdx++ )
      {
        EthSwt_30_Sja1105PQRS_UpdateMCastPortAssignBuckets[mCastEntryIdx].Multicast[0] = 0x00u;
        EthSwt_30_Sja1105PQRS_UpdateMCastPortAssignBuckets[mCastEntryIdx].PortRequests[bucketIdx] = 0u;
      }
    }
  }
#endif /* ETHSWT_30_SJA1105PQRS_UPDATE_MCAST_PORT_ASSIGN_API_ENABLED */
  }
#if ( ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED == STD_ON )
  EthSwt_30_Sja1105PQRS_StoreConfigProcessing.ProcState = ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_IDLE;
#endif /* ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED == STD_ON )
  EthSwt_30_Sja1105PQRS_ResetConfigProcessing.ProcState = ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_IDLE;
#endif /* ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED */

  /* #40 Trigger lower level initialization */
  /* low level module initialization */
  EthSwt_30_Sja1105PQRS_LL_Init();

#if ( ETHSWT_30_SJA1105PQRS_MANAGEMENT_SUPPORT == STD_ON )
  /* frame management initialization */
  EthSwt_30_Sja1105PQRS_MgmtInit();
#endif /* ETHSWT_30_SJA1105PQRS_MANAGEMENT_SUPPORT */
#if ( ETHSWT_30_SJA1105PQRS_GLOBAL_TIME_SUPPORT == STD_ON )
  EthSwt_30_Sja1105PQRS_TimeInit();
#endif /* ETHSWT_30_SJA1105PQRS_GLOBAL_TIME_SUPPORT */

} /* EthSwt_30_Sja1105PQRS_Init() */ /* PRQA S 2006 */ /* MD_MSR_14.7 */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_SwitchInit()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_SwitchInit(
    EthSwt_SwitchIdxType  SwitchIdx )
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_InstanceDataType, SJA1105PQRS)  InstanceRuntime;
               Std_ReturnType                                        RetVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check initialization state of the component. */
  EthSwt_CheckDetErrorReturnValue(                                                        \
        (EthSwt_30_Sja1105PQRS_ModuleInitState >= (EthSwt_StateType)ETHSWT_STATE_INIT),   \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                            \
        ETHSWT_30_SJA1105PQRS_SID_SWITCH_INIT,                                            \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                          \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #20 Check switch index for validity. */
  EthSwt_CheckDetErrorReturnValue(                                            \
        ((EthSwt_SwitchIdxType)ETHSWT_30_SJA1105PQRS_SWITCH_NUM > SwitchIdx), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                \
        ETHSWT_30_SJA1105PQRS_SID_SWITCH_INIT,                                \
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX,                               \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #30 Check initialization state of the instance. */
  EthSwt_CheckDetErrorReturnValue(                                                                          \
        (EthSwt_30_Sja1105PQRS_InstanceData[SwitchIdx].InitState >= (EthSwt_StateType)ETHSWT_STATE_INIT),   \
        SwitchIdx,                                                                                          \
        ETHSWT_30_SJA1105PQRS_SID_SWITCH_INIT,                                                              \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                                            \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* ----- Local data definition ---------------------------------------- */
  InstanceRuntime = &EthSwt_30_Sja1105PQRS_InstanceData[SwitchIdx];

  /* ----- Implementation ----------------------------------------------- */
  /* #40 If switch instance is in state ACTIVE */
  if( InstanceRuntime->InitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE )
  {
    RetVal = E_OK;

    /* #400 Set module state to ACTIVE and set return value to E_OK to signal proper initialization of switch to caller. */
    EthSwt_30_Sja1105PQRS_ModuleInitState = (EthSwt_StateType)ETHSWT_STATE_ACTIVE;
  }

#if ( ETHSWT_30_SJA1105PQRS_GLOBAL_TIME_SUPPORT == STD_ON )
  if((RetVal == E_OK) &&
     (EthSwt_30_Sja1105PQRS_CascadingConfig.CascadingMaps[SwitchIdx].CascadingLevel != 0))
  {
    /* A cascaded switch was initialized - perform one initial offset correction to CAS_MASTER switch */
    RetVal = EthSwt_30_Sja1105PQRS_SynchronizeSwitchToCasMaster(SwitchIdx);
  }
#endif /* ETHSWT_30_SJA1105PQRS_GLOBAL_TIME_SUPPORT */

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_SwitchInit() */ /* PRQA S 2006 */ /* MD_MSR_14.7 */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_VSwitchInit()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
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
 *
 *
 *
 *
 *
 *
 */
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_VSwitchInit(
    EthSwt_SwitchIdxType  SwitchIdx )
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType,  SJA1105PQRS)  InstanceConfig;
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_InstanceDataType,    SJA1105PQRS)  InstanceRuntime;
                 uint8_least                                              LoopIdx;
                 Std_ReturnType                                           RetVal;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check initialization state of the component. */
  EthSwt_CheckDetErrorReturnValue(                                                         \
        (EthSwt_30_Sja1105PQRS_ModuleInitState >= (EthSwt_StateType)ETHSWT_STATE_INIT),    \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                             \
        ETHSWT_30_SJA1105PQRS_SID_VSWITCH_INIT,                                            \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                           \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #20 Check switch index for validity. */
  EthSwt_CheckDetErrorReturnValue(                                             \
        ((EthSwt_SwitchIdxType)ETHSWT_30_SJA1105PQRS_SWITCH_NUM > SwitchIdx),  \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                 \
        ETHSWT_30_SJA1105PQRS_SID_VSWITCH_INIT,                                \
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX,                                \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #30 Check initialization state of the instance. */
  EthSwt_CheckDetErrorReturnValue(                                                                           \
        (EthSwt_30_Sja1105PQRS_InstanceData[SwitchIdx].InitState >= (EthSwt_StateType)ETHSWT_STATE_INIT),    \
        SwitchIdx,                                                                                           \
        ETHSWT_30_SJA1105PQRS_SID_VSWITCH_INIT,                                                              \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                                             \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* ----- Local data definition ---------------------------------------- */
  InstanceConfig  = &EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx];
  InstanceRuntime = &EthSwt_30_Sja1105PQRS_InstanceData[SwitchIdx];

  /* ----- Implementation ----------------------------------------------- */
  /* #40 Set instance state to INIT. */
  InstanceRuntime->InitState = (EthSwt_StateType)ETHSWT_STATE_INIT;

  /* #50 Initialize configuration related data. (function call(s)) */
  InstanceConfig->InitConfig();

  /* #60 Check for device access. (function call(s)) */
  RetVal = EthSwt_30_Sja1105PQRS_CheckDeviceAccess(SwitchIdx);

  if( RetVal == (Std_ReturnType)E_OK )
  {
    /* #70 Reset device. (function call(s)) */
    RetVal = EthSwt_30_Sja1105PQRS_ResetDevice(SwitchIdx);

    /* #80 Initialize hardware (i.e. clocks, pin characteristics). (function call(s)) */
    /* ---- Initialize clocks ---- */
    if( RetVal == (Std_ReturnType)E_OK )
    {
      RetVal = InstanceConfig->InitClock();
    }
    /* ---- Initialize pin characteristics ---- */
    if( RetVal == (Std_ReturnType)E_OK )
    {
      RetVal = EthSwt_30_Sja1105PQRS_InitPinCharacteristics(SwitchIdx);
    }

    /* #90 Download configuration. (function call(s)) */
    /* ---- Download the Configuration ---- */
    if( RetVal == (Std_ReturnType)E_OK )
    {
      RetVal = EthSwt_30_Sja1105PQRS_DownloadConfig(SwitchIdx);
    }
    /* ---- Download verification ---- */
    if( RetVal == (Std_ReturnType)E_OK )
    {
      RetVal = EthSwt_30_Sja1105PQRS_VerifyConfigDownload(SwitchIdx);
    }
    /* ---- Shaper Configuration ---- */
    if( RetVal == (Std_ReturnType)E_OK )
    {
      RetVal = EthSwt_30_Sja1105PQRS_ConfigureShapers(SwitchIdx);
    }
#if ( ETHSWT_30_SJA1105PQRS_GLOBAL_TIME_SUPPORT == STD_ON )
    /* ----- IEEE802.1Qbv Configuration ---- */
    if( RetVal == (Std_ReturnType)E_OK )
    {
      RetVal = EthSwt_30_Sja1105PQRS_ConfigureQbv(SwitchIdx);
    }
#endif /* ETHSWT_30_SJA1105PQRS_GLOBAL_TIME_SUPPORT */

    /* #100 If preconfig feature EthSwtStoreConfigurationApi or EthSwtResetConfigurationApi is enabled. */
#if ( (ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED == STD_ON) || \
      (ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED == STD_ON)    )
    /* #1000 Restore switch configuration out of NV-RAM. (function call(s)) */
    if( RetVal == (Std_ReturnType)E_OK )
    {
      RetVal = EthSwt_30_Sja1105PQRS_RestoreConfiguration(SwitchIdx);
    }
#endif /* ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED, ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED */
    /* #110 Restore a possibly persisted mirroring configuration. */
#if( ETHSWT_30_SJA1105PQRS_MIRROR_API == STD_ON )
    EthSwt_30_Sja1105PQRS_MirrorInit(SwitchIdx);
#endif /* ETHSWT_30_SJA1105PQRS_MIRROR_API */

    /* #200 Iterate over all ports */
    for( LoopIdx = 0; LoopIdx < InstanceConfig->PortNum; LoopIdx++ )
    {
      /* check if previous steps were successful -> otherwise stop processing */
      if( RetVal == (Std_ReturnType)E_NOT_OK ) { break; }

      /* #2000 Set port state to DOWN. */
      InstanceConfig->PortModes[LoopIdx] = (EthTrcv_ModeType)ETHTRCV_MODE_DOWN;

      /* #2010 Call transceiver initialization of EthTrcv. */
      /* MAC <-> MAC or MAC <-> PHY interface? */
      if( InstanceConfig->TrcvCalloutFcts[LoopIdx] != NULL_PTR )
      {
        /* MAC <-> PHY interface */
        RetVal = InstanceConfig->TrcvCalloutFcts[LoopIdx]->TrcvInit(
                                                              InstanceConfig->PortTrcvIdxMap[LoopIdx],
                                                              (uint8)0U);
      }
      else
      {
        /* MAC <-> MAC interface -> nothing to do */
      }
    }
  }

  /* #300 If all initialization steps were successful */
  if( RetVal == (Std_ReturnType)E_OK )
  {
    /* #3000 Set switch instance to state ACTIVE. */
    InstanceRuntime->InitState = (EthSwt_StateType)ETHSWT_STATE_ACTIVE;
  }
  return RetVal;
} /* EthSwt_30_Sja1105PQRS_VSwitchInit() */ /* PRQA S 2006, 6010, 6030, 6050, 6060 */ /* MD_MSR_14.7, MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STPAR */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_SetSwitchPortMode()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
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
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_SetSwitchPortMode(
    EthSwt_SwitchIdxType  SwitchIdx,
    EthSwt_PortIdxType    PortIdx,
    EthTrcv_ModeType      PortMode )
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  InstanceConfig;
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS)  SpiTransaction;
                 uint8                                                   HwPortIdx;
                 Std_ReturnType                                          RetVal;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check initialization state of the component */
  EthSwt_CheckDetErrorReturnValue(                                                          \
        (EthSwt_30_Sja1105PQRS_ModuleInitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE),   \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                              \
        ETHSWT_30_SJA1105PQRS_SID_SET_SWITCH_PORT_MODE,                                     \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                            \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #20 Check switch index for validity */
  EthSwt_CheckDetErrorReturnValue(                                            \
        ((EthSwt_SwitchIdxType)ETHSWT_30_SJA1105PQRS_SWITCH_NUM > SwitchIdx), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                \
        ETHSWT_30_SJA1105PQRS_SID_SET_SWITCH_PORT_MODE,                       \
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX,                               \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  EthSwt_CheckDetErrorReturnValue(                                           \
        (EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].PortNum > PortIdx), \
        SwitchIdx,                                                           \
        ETHSWT_30_SJA1105PQRS_SID_SET_SWITCH_PORT_MODE,                      \
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCHPORT_IDX,                          \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #30 Check initialization state of the instance */
  EthSwt_CheckDetErrorReturnValue(                                                                            \
        (EthSwt_30_Sja1105PQRS_InstanceData[SwitchIdx].InitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE),   \
        SwitchIdx,                                                                                            \
        ETHSWT_30_SJA1105PQRS_SID_SET_SWITCH_PORT_MODE,                                                       \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                                              \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* ----- Local data definition ---------------------------------------- */
  InstanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx];
  HwPortIdx = InstanceConfig->TransformPortIdx(PortIdx, ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_INTERNAL_VIEW);

  /* ----- Implementation ----------------------------------------------- */
  /* #40 Enable Tx and Rx for the port */
  RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(SwitchIdx, &SpiTransaction);

  if( RetVal == (Std_ReturnType)E_OK )
  {
    /* Read current values */
    SpiTransaction->AddrIdx     = (uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG0_ADDR;
    SpiTransaction->DataPtr[0]  = HwPortIdx;
    SpiTransaction->DataPtr[0] |= (uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG0_VALID_MASK;
    RetVal = EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(SwitchIdx, SpiTransaction);
    (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(SwitchIdx, SpiTransaction);
  }

  if( RetVal == (Std_ReturnType)E_OK )
  {
    /* register 1 */
    RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(SwitchIdx, &SpiTransaction);
    if( RetVal == (Std_ReturnType)E_OK )
    {
      if (InstanceConfig->PortMiiIfcs[PortIdx] == ETHSWT_30_SJA1105PQRS_PORT_MII_IFC_SGMII)
      {
        SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_SGMII_AUTONEG_CONTROL_REG_ADDR;
        if (PortMode == ETHTRCV_MODE_ACTIVE)
        {
          SpiTransaction->DataPtr[0] = ETHSWT_30_SJA1105PQRS_SGMII_AUTONEG_CONTROL_REG_SGMII_LINK_MASK;
        }
        else
        {
          SpiTransaction->DataPtr[0] = 0;
        }
        RetVal |= EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(SwitchIdx, SpiTransaction);
      }

      /* adapt local mirror of entry in table (table doesn't allow to read entries) */
      switch( PortMode )
      {
        case ETHTRCV_MODE_DOWN:
          /* clear receive and transmit flags in table entry */
          InstanceConfig->DynMacTableEntries[PortIdx].Register1 &= ~(uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG1_PORTST_RX_EN_MASK;
          InstanceConfig->DynMacTableEntries[PortIdx].Register2 &= ~(uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG2_PORTST_TX_EN_MASK;
          break;
        case ETHTRCV_MODE_ACTIVE:
          /* set receive and transmit flags in table entry */
          InstanceConfig->DynMacTableEntries[PortIdx].Register1 |= (uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG1_PORTST_RX_EN_MASK;
          InstanceConfig->DynMacTableEntries[PortIdx].Register2 |= (uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG2_PORTST_TX_EN_MASK;
          break;
        default:
          break;
      }

      SpiTransaction->AddrIdx    = (uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG2_ADDR;
      SpiTransaction->DataPtr[0] = InstanceConfig->DynMacTableEntries[PortIdx].Register2;
      RetVal |= EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(SwitchIdx, SpiTransaction);

      SpiTransaction->AddrIdx    = (uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG1_ADDR;
      SpiTransaction->DataPtr[0] = InstanceConfig->DynMacTableEntries[PortIdx].Register1;
      RetVal |= EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(SwitchIdx, SpiTransaction);

      /* Write/activate current values */
      SpiTransaction->AddrIdx     = (uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG0_ADDR;
      SpiTransaction->DataPtr[0]  = HwPortIdx;
      SpiTransaction->DataPtr[0] |= (uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG0_VALID_MASK;
      SpiTransaction->DataPtr[0] |= (uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG0_RDWRSET_MASK;
      RetVal |= EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(SwitchIdx, SpiTransaction);

      (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(SwitchIdx, SpiTransaction);
    }
  }

  if( RetVal == (Std_ReturnType)E_OK )
  {
    /* #50 If port interface is MAC <-> PHY */
    /* MAC <-> MAC or MAC <-> PHY interface ? */
    if( InstanceConfig->TrcvCalloutFcts[PortIdx] != NULL_PTR )
    {
      /* MAC <-> PHY interface */

      /* #500 If EthTrcv API is available */
      /* -- Utilize EthTrcv driver API if available -- */
      if( InstanceConfig->TrcvCalloutFcts[PortIdx]->SetTrcvMode != NULL_PTR )
      {
        /* #5000 Call EthTrcv API */
        /* call EthTrcv_xyz_SetTransceiverMode() of Ethernet Transceiver instance related to port */
        RetVal = InstanceConfig->TrcvCalloutFcts[PortIdx]->SetTrcvMode(
                                                                InstanceConfig->PortTrcvIdxMap[PortIdx],
                                                                PortMode);
      }
      /* #510 Else */
      else
      {
        /* #5100 Report development error */
        /* API not provided by transceiver module -> call is forbidden */
        EthSwt_CallDetReportError(
            SwitchIdx,
            ETHSWT_30_SJA1105PQRS_SID_SET_SWITCH_PORT_MODE,
            ETHSWT_30_SJA1105PQRS_E_INV_API);
      }
    }
    else
    {
      /* MAC <-> MAC interface -> nothing to do here */
    }
  }

  /* #60 Store port mode in state variable */
  if( RetVal == (Std_ReturnType)E_OK )
  {
    InstanceConfig->PortModes[PortIdx] = PortMode;
  }

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_SetSwitchPortMode() */ /* PRQA S 2006,6010,6030 */ /* MD_MSR_14.7,MD_MSR_STPTH,MD_MSR_STCYC */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetSwitchPortMode()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
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
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_GetSwitchPortMode(
                 EthSwt_SwitchIdxType               SwitchIdx,
                 EthSwt_PortIdxType                 PortIdx,
    ETHSWT_P2VAR(EthTrcv_ModeType,    SJA1105PQRS)  ModePtr )
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  InstanceConfig;
                 Std_ReturnType                                          RetVal;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check initialization state of the component */
  EthSwt_CheckDetErrorReturnValue(                                                          \
        (EthSwt_30_Sja1105PQRS_ModuleInitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE),   \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                              \
        ETHSWT_30_SJA1105PQRS_SID_GET_SWITCH_PORT_MODE,                                     \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                            \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #20 Check switch index for validity */
  EthSwt_CheckDetErrorReturnValue(                                            \
        ((EthSwt_SwitchIdxType)ETHSWT_30_SJA1105PQRS_SWITCH_NUM > SwitchIdx), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                \
        ETHSWT_30_SJA1105PQRS_SID_GET_SWITCH_PORT_MODE,                       \
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX,                               \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    EthSwt_CheckDetErrorReturnValue(                                            \
          (EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].PortNum > PortIdx),  \
          SwitchIdx,                                                            \
          ETHSWT_30_SJA1105PQRS_SID_GET_SWITCH_PORT_MODE,                       \
          ETHSWT_30_SJA1105PQRS_E_INV_SWITCHPORT_IDX,                           \
          E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #30 Check initialization state of the instance */
  EthSwt_CheckDetErrorReturnValue(                                                                            \
        (EthSwt_30_Sja1105PQRS_InstanceData[SwitchIdx].InitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE),   \
        SwitchIdx,                                                                                            \
        ETHSWT_30_SJA1105PQRS_SID_GET_SWITCH_PORT_MODE,                                                       \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                                              \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* ----- Local data definition ---------------------------------------- */
  InstanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx];
  RetVal         = (Std_ReturnType)E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #40 If port interface is MAC <-> PHY */
  /* MAC <-> MAC or MAC <-> PHY interface ? */
  if( InstanceConfig->TrcvCalloutFcts[PortIdx] != NULL_PTR )
  {
    /* MAC <-> PHY interface */

    /* #400 If EthTrcv API is available */
    /* -- Utilize EthTrcv driver API if available -- */
    if( InstanceConfig->TrcvCalloutFcts[PortIdx]->GetTrcvMode != NULL_PTR )
    {
      /* #4000 Call EthTrcv API */
      /* call EthTrcv_xyz_GetTransceiverMode() of Ethernet Transceiver instance related to port */
      RetVal = InstanceConfig->TrcvCalloutFcts[PortIdx]->GetTrcvMode(
                                                              InstanceConfig->PortTrcvIdxMap[PortIdx],
                                                              ModePtr);
    }
    /* #410 Else */
    else
    {
      /* #4100 Report development error */
      /* API not provided by transceiver module -> call is forbidden */
      EthSwt_CallDetReportError(
          SwitchIdx,
          ETHSWT_30_SJA1105PQRS_SID_GET_SWITCH_PORT_MODE,
          ETHSWT_30_SJA1105PQRS_E_INV_API);
    }
  }
  /* #50 Else */
  else
  {
    /* MAC <-> MAC interface */
    /* #500 Retrieve port mode from state variable */
    ModePtr[0] = InstanceConfig->PortModes[PortIdx];
  }

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_GetSwitchPortMode() */ /* PRQA S 2006,6010,6030 */ /* MD_MSR_14.7,MD_MSR_STPTH,MD_MSR_STCYC */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_StartSwitchPortAutoNegotiation()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
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
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_StartSwitchPortAutoNegotiation(
    EthSwt_SwitchIdxType SwitchIdx,
    EthSwt_PortIdxType   PortIdx )
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  InstanceConfig;
                 Std_ReturnType                                          RetVal;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check initialization state of the component */
  EthSwt_CheckDetErrorReturnValue(                                                          \
        (EthSwt_30_Sja1105PQRS_ModuleInitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE),   \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                              \
        ETHSWT_30_SJA1105PQRS_SID_START_SWITCH_PORT_AUTO_NEGOTIATION,                       \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                            \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #20 Check switch index for validity */
  EthSwt_CheckDetErrorReturnValue(                                            \
        ((EthSwt_SwitchIdxType)ETHSWT_30_SJA1105PQRS_SWITCH_NUM > SwitchIdx), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                \
        ETHSWT_30_SJA1105PQRS_SID_START_SWITCH_PORT_AUTO_NEGOTIATION,         \
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX,                               \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  EthSwt_CheckDetErrorReturnValue(                                            \
        (EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].PortNum > PortIdx),  \
        SwitchIdx,                                                            \
        ETHSWT_30_SJA1105PQRS_SID_START_SWITCH_PORT_AUTO_NEGOTIATION,         \
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCHPORT_IDX,                           \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #30 Check initialization state of the instance */
  EthSwt_CheckDetErrorReturnValue(                                                                            \
        (EthSwt_30_Sja1105PQRS_InstanceData[SwitchIdx].InitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE),   \
        SwitchIdx,                                                                                            \
        ETHSWT_30_SJA1105PQRS_SID_START_SWITCH_PORT_AUTO_NEGOTIATION,                                         \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                                              \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* ----- Local data definition ---------------------------------------- */
  InstanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx];
  RetVal         = (Std_ReturnType)E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #40 If port interface is MAC <-> PHY */
  /* MAC <-> MAC or MAC <-> PHY interface ? */
  if( InstanceConfig->TrcvCalloutFcts[PortIdx] != NULL_PTR )
  {
    /* MAC <-> PHY interface */

    /* #400 If EthTrcv API is available */
    if( InstanceConfig->TrcvCalloutFcts[PortIdx]->StartAutoNegotiation != NULL_PTR )
    {
      /* #4000 Call EthTrcv API */
      /* call EthTrcv_xyz_StartAutoNegotiation() of Ethernet Transceiver instance related to port */
      RetVal = InstanceConfig->TrcvCalloutFcts[PortIdx]->StartAutoNegotiation(
                                                              InstanceConfig->PortTrcvIdxMap[PortIdx]);
    }
    /* #410 Else */
    else
    {
      /* #4100 Report development error */
      /* API not provided by transceiver module -> call is forbidden */
      EthSwt_CallDetReportError(
          SwitchIdx,
          ETHSWT_30_SJA1105PQRS_SID_START_SWITCH_PORT_AUTO_NEGOTIATION,
          ETHSWT_30_SJA1105PQRS_E_INV_API);
    }
  }
  else
  {
    /* MAC <-> MAC interface -> nothing to do here */
    EthSwt_CallDetReportError(
        SwitchIdx,
        ETHSWT_30_SJA1105PQRS_SID_START_SWITCH_PORT_AUTO_NEGOTIATION,
        ETHSWT_30_SJA1105PQRS_E_INV_API);
  }

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_StartSwitchPortAutoNegotiation() */ /* PRQA S 2006,6010,6030 */ /* MD_MSR_14.7,MD_MSR_STPTH,MD_MSR_STCYC */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetLinkState()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
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
 *
 */
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_GetLinkState(
                 EthSwt_SwitchIdxType                 SwitchIdx,
                 EthSwt_PortIdxType                   PortIdx,
    ETHSWT_P2VAR(EthTrcv_LinkStateType, SJA1105PQRS)  LinkStatePtr )
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  InstanceConfig;
                 Std_ReturnType                                          RetVal;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check initialization state of the component */
  EthSwt_CheckDetErrorReturnValue(                                                          \
        (EthSwt_30_Sja1105PQRS_ModuleInitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE),   \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                              \
        ETHSWT_30_SJA1105PQRS_SID_GET_LINK_STATE,                                           \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                            \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #20 Check switch index for validity */
  EthSwt_CheckDetErrorReturnValue(                                            \
        ((EthSwt_SwitchIdxType)ETHSWT_30_SJA1105PQRS_SWITCH_NUM > SwitchIdx), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                \
        ETHSWT_30_SJA1105PQRS_SID_GET_LINK_STATE,                             \
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX,                               \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  EthSwt_CheckDetErrorReturnValue(                                           \
        (EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].PortNum > PortIdx), \
        SwitchIdx,                                                           \
        ETHSWT_30_SJA1105PQRS_SID_GET_LINK_STATE,                            \
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCHPORT_IDX,                          \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #30 Check initialization state of the instance */
  EthSwt_CheckDetErrorReturnValue(                                                                            \
        (EthSwt_30_Sja1105PQRS_InstanceData[SwitchIdx].InitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE),   \
        SwitchIdx,                                                                                            \
        ETHSWT_30_SJA1105PQRS_SID_GET_LINK_STATE,                                                             \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                                              \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* ----- Local data definition ---------------------------------------- */
  InstanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx];
  RetVal         = (Std_ReturnType)E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #40 If port interface is MAC <-> PHY */
  /* MAC <-> MAC or MAC <-> PHY interface ? */
  if( InstanceConfig->TrcvCalloutFcts[PortIdx] != NULL_PTR )
  {
    /* MAC <-> PHY interface */

    /* #400 If EthTrcv API is available */
    if( InstanceConfig->TrcvCalloutFcts[PortIdx]->GetLinkState != NULL_PTR )
    {
      /* #4000 Call EthTrcv API */

      /* call EthTrcv_xyz_GetLinkState() of Ethernet Transceiver instance related to port */
      RetVal = InstanceConfig->TrcvCalloutFcts[PortIdx]->GetLinkState(
                                                              InstanceConfig->PortTrcvIdxMap[PortIdx],
                                                              LinkStatePtr);
    }
    /* #410 Else */
    else
    {
      /* #4100 API not provided by transceiver module -> provide link state active */
      *LinkStatePtr = (EthTrcv_LinkStateType)ETHTRCV_LINK_STATE_ACTIVE;
      RetVal = E_OK;
    }
  }
  /* #50 Else */
  else
  {
    /* MAC <-> MAC interface */
    /* #500 Retrieve link state from state variable */
    /* issue a link as soon as the port is ACTIVE */
    switch( InstanceConfig->PortModes[PortIdx] )
    {
      case ETHTRCV_MODE_DOWN:
        *LinkStatePtr = (EthTrcv_LinkStateType)ETHTRCV_LINK_STATE_DOWN;
        RetVal          = (Std_ReturnType)E_OK;
        break;
      case ETHTRCV_MODE_ACTIVE:
        *LinkStatePtr = (EthTrcv_LinkStateType)ETHTRCV_LINK_STATE_ACTIVE;
        RetVal          = (Std_ReturnType)E_OK;
        break;
      default:
        break;
    }
  }

  /* #600 Inform user about link state change */
  /* call user link up/down callbacks if needed */
  if( RetVal == E_OK )
  {
    if( InstanceConfig->CurrentLinkStates[PortIdx] != *LinkStatePtr )
    {
      if( *LinkStatePtr == ETHTRCV_LINK_STATE_ACTIVE )
      {
        RetVal = EthSwt_30_Sja1105PQRS_EnableRgmiiTdl(SwitchIdx, PortIdx);
        /* #60 If feature user link state change notification is enabled */
#if ( ETHSWT_30_SJA1105PQRS_LINK_USER_CALLBACK_ENABLED == STD_ON )
        EthSwt_30_Sja1105PQRS_PortLinkUpUserCallback(&SwitchIdx, &PortIdx);
#endif /* ETHSWT_30_SJA1105PQRS_LINK_USER_CALLBACK_ENABLED */
      }
      else if ( *LinkStatePtr == ETHTRCV_LINK_STATE_DOWN )
      {
        RetVal = EthSwt_30_Sja1105PQRS_DisableRgmiiTdl(SwitchIdx, PortIdx);
#if ( ETHSWT_30_SJA1105PQRS_LINK_USER_CALLBACK_ENABLED == STD_ON )
        EthSwt_30_Sja1105PQRS_PortLinkDownUserCallback(&SwitchIdx, &PortIdx);
#endif /* ETHSWT_30_SJA1105PQRS_LINK_USER_CALLBACK_ENABLED */
      }
      else
      {
        /* No other Linkstate is possible */
      }

      /* Remember link state change only in case all operations were successful */
      if(RetVal == E_OK)
      {
        InstanceConfig->CurrentLinkStates[PortIdx] = *LinkStatePtr;
      }
    }
  }

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_GetLinkState() */ /* PRQA S 2006,6010,6030 */ /* MD_MSR_14.7,MD_MSR_STPTH,MD_MSR_STCYC */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetBaudRate()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
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
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_GetBaudRate(
                 EthSwt_SwitchIdxType                SwitchIdx,
                 EthSwt_PortIdxType                  PortIdx,
    ETHSWT_P2VAR(EthTrcv_BaudRateType, SJA1105PQRS)  BaudRatePtr )
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  InstanceConfig;
                 Std_ReturnType                                          RetVal;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check initialization state of the component */
  EthSwt_CheckDetErrorReturnValue(                                                          \
        (EthSwt_30_Sja1105PQRS_ModuleInitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE),   \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                              \
        ETHSWT_30_SJA1105PQRS_SID_GET_BAUD_RATE,                                            \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                            \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #20 Check switch index for validity */
  EthSwt_CheckDetErrorReturnValue(                                            \
        ((EthSwt_SwitchIdxType)ETHSWT_30_SJA1105PQRS_SWITCH_NUM > SwitchIdx), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                \
        ETHSWT_30_SJA1105PQRS_SID_GET_BAUD_RATE,                              \
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX,                               \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  EthSwt_CheckDetErrorReturnValue(                                           \
        (EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].PortNum > PortIdx), \
        SwitchIdx,                                                           \
        ETHSWT_30_SJA1105PQRS_SID_GET_BAUD_RATE,                             \
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCHPORT_IDX,                          \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #30 Check initialization state of the instance */
  EthSwt_CheckDetErrorReturnValue(                                                                            \
        (EthSwt_30_Sja1105PQRS_InstanceData[SwitchIdx].InitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE),   \
        SwitchIdx,                                                                                            \
        ETHSWT_30_SJA1105PQRS_SID_GET_BAUD_RATE,                                                              \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                                              \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* ----- Local data definition ---------------------------------------- */
  InstanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx];
  RetVal         = (Std_ReturnType)E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #40 If port interface is MAC <-> PHY */
  /* MAC <-> MAC or MAC <-> PHY interface ? */
  if( InstanceConfig->TrcvCalloutFcts[PortIdx] != NULL_PTR )
  {
    /* MAC <-> PHY interface */

    /* #400 If EthTrcv API is available */
    if( InstanceConfig->TrcvCalloutFcts[PortIdx]->GetBaudRate != NULL_PTR )
    {
      /* #4000 Call EthTrcv API */
      /* call EthTrcv_xyz_GetBaudRate() of Ethernet Transceiver instance related to port */
      RetVal = InstanceConfig->TrcvCalloutFcts[PortIdx]->GetBaudRate(
                                                              InstanceConfig->PortTrcvIdxMap[PortIdx],
                                                              BaudRatePtr);
    }
    /* #410 Else */
    else
    {
      /* #4100 Report development error */
      /* API not provided by transceiver module -> call is forbidden */
      EthSwt_CallDetReportError(
          SwitchIdx,
          ETHSWT_30_SJA1105PQRS_SID_GET_BAUD_RATE,
          ETHSWT_30_SJA1105PQRS_E_INV_API);
    }
  }
  /* #50 Else */
  else
  {
    /* MAC <-> MAC interface */

    /* #500 Retrieve speed from state variable */
    BaudRatePtr[0] = InstanceConfig->PortSpeed[PortIdx];
    RetVal         = (Std_ReturnType)E_OK;
  }

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_GetBaudRate() */ /* PRQA S 2006,6010,6030 */ /* MD_MSR_14.7,MD_MSR_STPTH,MD_MSR_STCYC */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetDuplexMode()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
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
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_GetDuplexMode(
                 EthSwt_SwitchIdxType                  SwitchIdx,
                 EthSwt_PortIdxType                    PortIdx,
    ETHSWT_P2VAR(EthTrcv_DuplexModeType, SJA1105PQRS)  DuplexModePtr )
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  InstanceConfig;
                 Std_ReturnType                                          RetVal;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check initialization state of the component */
  EthSwt_CheckDetErrorReturnValue(                                                          \
        (EthSwt_30_Sja1105PQRS_ModuleInitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE),   \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                              \
        ETHSWT_30_SJA1105PQRS_SID_GET_DUPLEX_MODE,                                          \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                            \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #20 Check switch index for validity */
  EthSwt_CheckDetErrorReturnValue(                                            \
        ((EthSwt_SwitchIdxType)ETHSWT_30_SJA1105PQRS_SWITCH_NUM > SwitchIdx), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                \
        ETHSWT_30_SJA1105PQRS_SID_GET_DUPLEX_MODE,                            \
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX,                               \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  EthSwt_CheckDetErrorReturnValue(                                           \
        (EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].PortNum > PortIdx), \
        SwitchIdx,                                                           \
        ETHSWT_30_SJA1105PQRS_SID_GET_DUPLEX_MODE,                           \
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCHPORT_IDX,                          \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #30 Check initialization state of the instance */
  EthSwt_CheckDetErrorReturnValue(                                                                            \
        (EthSwt_30_Sja1105PQRS_InstanceData[SwitchIdx].InitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE),   \
        SwitchIdx,                                                                                            \
        ETHSWT_30_SJA1105PQRS_SID_GET_DUPLEX_MODE,                                                            \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                                              \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* ----- Local data definition ---------------------------------------- */
  InstanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx];
  RetVal         = (Std_ReturnType)E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #40 If port interface is MAC <-> PHY */
  /* MAC <-> MAC or MAC <-> PHY interface ? */
  if( InstanceConfig->TrcvCalloutFcts[PortIdx] != NULL_PTR )
  {
    /* MAC <-> PHY interface */

    /* #400 If EthTrcv API is available */
    if( InstanceConfig->TrcvCalloutFcts[PortIdx]->GetDuplexMode != NULL_PTR )
    {
      /* #4000 Call EthTrcv API */
      /* call EthTrcv_xyz_GetDuplexMode() of Ethernet Transceiver instance related to port */
      RetVal = InstanceConfig->TrcvCalloutFcts[PortIdx]->GetDuplexMode(
                                                              InstanceConfig->PortTrcvIdxMap[PortIdx],
                                                              DuplexModePtr);
    }
    /* #410 Else */
    else
    {
      /* #4100 Report development error */
      /* API not provided by transceiver module -> call is forbidden */
      EthSwt_CallDetReportError(
          SwitchIdx,
          ETHSWT_30_SJA1105PQRS_SID_GET_DUPLEX_MODE,
          ETHSWT_30_SJA1105PQRS_E_INV_API);
    }
  }
  else
  {
    /* MAC <-> MAC interface */

    /* #500 Return FULL_DUPLEX */
    /* xMII is always full duplex */
    DuplexModePtr[0] = (EthTrcv_DuplexModeType)ETHTRCV_DUPLEX_MODE_FULL;
    RetVal           = (Std_ReturnType)E_OK;
  }

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_GetDuplexMode() */ /* PRQA S 2006,6010,6030 */ /* MD_MSR_14.7,MD_MSR_STPTH,MD_MSR_STCYC */

#if ( ETHSWT_30_SJA1105PQRS_GET_PORT_MAC_ADDR_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_SearchL2LookupTableEntry()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
STATIC INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_SearchL2LookupTableEntry(
                   EthSwt_SwitchIdxType                SwitchIdx,
    ETHSWT_P2CONST(uint8,                SJA1105PQRS)  MacAddr,
      ETHSWT_P2VAR(uint8,                SJA1105PQRS)  SwitchPort,
      ETHSWT_P2VAR(uint16,               SJA1105PQRS)  L2LookupTableIndex)
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS)  SpiTransaction;
               Std_ReturnType                                          RetVal;

  /* ----- Implementation ----------------------------------------------- */
  EthSwt_EnterExclusiveArea(Sja1105PQRS, ARL_TABLE_ACCESS); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(SwitchIdx, &SpiTransaction);

  if( RetVal == (Std_ReturnType)E_OK )
  {
    SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_ADDR;
    SpiTransaction->WordNum = (uint16)6u;
    /* #10 Setup L2 address lookup table reconfiguration registers 5-0 */
    SpiTransaction->DataPtr[0]  = (uint32)((uint32)MacAddr[5] <<
                                  ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_MACADDR5_SHIFT);
    SpiTransaction->DataPtr[0] |= (uint32)((uint32)MacAddr[4] <<
                                  ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_MACADDR4_SHIFT);
    SpiTransaction->DataPtr[1]  = (uint32)((uint32)MacAddr[4] >>
                                  ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG4_MACADDR4_SHIFT);
    SpiTransaction->DataPtr[1] |= (uint32)((uint32)MacAddr[3] <<
                                  ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG4_MACADDR3_SHIFT);
    SpiTransaction->DataPtr[1] |= (uint32)((uint32)MacAddr[2] <<
                                  ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG4_MACADDR2_SHIFT);
    SpiTransaction->DataPtr[1] |= (uint32)((uint32)MacAddr[1] <<
                                  ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG4_MACADDR1_SHIFT);
    SpiTransaction->DataPtr[1] |= (uint32)((uint32)MacAddr[0] <<
                                  ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG4_MACADDR0_SHIFT);
    SpiTransaction->DataPtr[2]  = (uint32)((uint32)MacAddr[0] >>
                                  ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG3_MACADDR0_SHIFT);
    SpiTransaction->DataPtr[2] |= ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG3_MACADDR_MASK;
    SpiTransaction->DataPtr[3]  = ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG2_MACADDR_MASK;
    SpiTransaction->DataPtr[4]  = ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG1_MACADDR_MASK;
    SpiTransaction->DataPtr[5]  = (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_VALID_MASK;
    SpiTransaction->DataPtr[5] |= (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_LOCKEDS_MASK;
    SpiTransaction->DataPtr[5] |= (uint32)(ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_HOSTCMD_SEARCH <<
                                           ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_HOSTCMD_SHIFT);
    RetVal |= EthSwt_30_Sja1105PQRS_LL_WriteBytesSync(SwitchIdx, SpiTransaction);

    /* #20 Read back the result of the read */
    SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_ADDR;
    RetVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);

    if( RetVal == (Std_ReturnType)E_OK )
    {
      /* #30 If MAC address has been found */
      if( ((SpiTransaction->DataPtr[0] & (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_VALIDENT_MASK)
          != (uint32)0u))
      {
        /* #300 Read port index */
        SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_ADDR;
        RetVal = EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);

        /* #310 If SPI transfer worked */
        if( RetVal == (Std_ReturnType)E_OK )
        {
          uint8 PortMask;

          /* #3110 Convert port index to external representation and return it */
          PortMask   = (uint8)((SpiTransaction->DataPtr[0] &
              (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_DESTPORTS_MASK)
              >> (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_DESTPORTS_ALIGN_SHIFT);

          *SwitchPort = EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].TransformPortIdx(
              EthSwt_30_Sja1105PQRS_GetHwPortIndexFromPortMask(PortMask),
              ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_EXTERNAL_VIEW);

          *L2LookupTableIndex = (uint16)((SpiTransaction->DataPtr[0] &
              (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_INDEX_MASK)
                >> (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_INDEX_SHIFT);
        }
      }
      else
      {
        /* No matching entry could be found */
        RetVal = E_NOT_OK;
      }
    }

    (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(SwitchIdx, SpiTransaction);
  }

  EthSwt_ExitExclusiveArea(Sja1105PQRS, ARL_TABLE_ACCESS); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_SearchL2LookupTableEntry() */
#endif /* ETHSWT_30_SJA1105PQRS_GET_PORT_MAC_ADDR_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_GET_PORT_MAC_ADDR_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetPortMacAddr()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_GetPortMacAddr(
  ETHSWT_P2CONST(uint8,                SJA1105PQRS)  MacAddrPtr,
    ETHSWT_P2VAR(EthSwt_SwitchIdxType, SJA1105PQRS)  SwitchIdxPtr,
    ETHSWT_P2VAR(EthSwt_PortIdxType,   SJA1105PQRS)  PortIdxPtr )
{
  /* ----- Local data declaration --------------------------------------- */
  uint8_least     LoopSwitchIdx;
  Std_ReturnType  RetVal;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check initialization state of the component */
  EthSwt_CheckDetErrorReturnValue(                                                          \
        (EthSwt_30_Sja1105PQRS_ModuleInitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE),   \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                              \
        ETHSWT_30_SJA1105PQRS_SID_GET_PORT_MAC_ADDR,                                        \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                            \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  EthSwt_CheckDetErrorReturnValue(                                                          \
        (NULL_PTR != MacAddrPtr),                                                           \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                              \
        ETHSWT_30_SJA1105PQRS_SID_GET_PORT_MAC_ADDR,                                        \
        ETHSWT_30_SJA1105PQRS_E_INV_POINTER,                                                \
        E_NOT_OK);

  /* ----- Local data definition ---------------------------------------- */
  RetVal            = (Std_ReturnType)E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #20 For each switch instance */
  for( LoopSwitchIdx = 0u; LoopSwitchIdx < ETHSWT_30_SJA1105PQRS_SWITCH_NUM; LoopSwitchIdx++ )
  {
    uint8  SwitchPort = 0; /* PRQA S 781 */ /* MD_EthSwt_30_Sja1105PQRS_781 */
    uint16 L2LookupTableLineIndex;

    /* #200 Try to retrieve the entry for the MAC-address */
    if( EthSwt_30_Sja1105PQRS_SearchL2LookupTableEntry((EthSwt_SwitchIdxType)LoopSwitchIdx,
            MacAddrPtr, &SwitchPort, &L2LookupTableLineIndex) == (Std_ReturnType)E_OK )
    {
      /* #2000 If entry is no uplink port, port has been found */
      if( EthSwt_30_Sja1105PQRS_IsUplinkPort((EthSwt_SwitchIdxType) LoopSwitchIdx, SwitchPort) == FALSE )
      {
        SwitchIdxPtr[0] = (EthSwt_SwitchIdxType)LoopSwitchIdx;
        PortIdxPtr[0]   = SwitchPort;
        RetVal          = (Std_ReturnType)E_OK;
        break;
      }
    }
  }

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_GetPortMacAddr() */ /* PRQA S 2006,6080 */ /* MD_MSR_14.7,MD_MSR_STMIF */
#endif /* ETHSWT_30_SJA1105PQRS_GET_PORT_MAC_ADDR_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_GET_ARL_TABLE_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetArlTable()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_GetArlTable(
               EthSwt_SwitchIdxType               SwitchIdx,
  ETHSWT_P2VAR(uint32,              SJA1105PQRS)  LenPtr,
  ETHSWT_P2VAR(EthSwt_MacVlanType,  SJA1105PQRS)  ArlTablePtr )
{
  /* ----- Local data declaration --------------------------------------- */
  Std_ReturnType  RetVal;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check initialization state of the component */
  EthSwt_CheckDetErrorReturnValue(                                                        \
        (EthSwt_30_Sja1105PQRS_ModuleInitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                            \
        ETHSWT_30_SJA1105PQRS_SID_GET_ARL_TABLE,                                          \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                          \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #20 Check switch index for validity */
  EthSwt_CheckDetErrorReturnValue(                                            \
        ((EthSwt_SwitchIdxType)ETHSWT_30_SJA1105PQRS_SWITCH_NUM > SwitchIdx), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                \
        ETHSWT_30_SJA1105PQRS_SID_GET_ARL_TABLE,                              \
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX,                               \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #30 Check initialization state of the instance */
  EthSwt_CheckDetErrorReturnValue(                                                                          \
        (EthSwt_30_Sja1105PQRS_InstanceData[SwitchIdx].InitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE), \
        SwitchIdx,                                                                                          \
        ETHSWT_30_SJA1105PQRS_SID_GET_ARL_TABLE,                                                            \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                                            \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #40 Trigger address resolution table retrieval */
# if   ( ETHSWT_30_SJA1105PQRS_API_CALL_TYPE == ETHSWT_30_SJA1105PQRS_API_CALL_TYPE_SYNC_CALL )
  /* process synchronous within this call */
  RetVal = EthSwt_30_Sja1105PQRS_VGetArlTable(SwitchIdx, LenPtr, ArlTablePtr);
# elif ( ETHSWT_30_SJA1105PQRS_API_CALL_TYPE == ETHSWT_30_SJA1105PQRS_API_CALL_TYPE_ASYNC_CALL )
  /* trigger the processing in async main function */

  /* check if processing isn't running yet */
  if( EthSwt_30_Sja1105PQRS_GetArlTableProcessing[SwitchIdx].ProcState != ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_PROCESSING )
  {
    /* no processing -> trigger processing */
    EthSwt_30_Sja1105PQRS_GetArlTableProcessing[SwitchIdx].ProcState   = ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_WAITING;
    EthSwt_30_Sja1105PQRS_GetArlTableProcessing[SwitchIdx].ArlTablePtr = ArlTablePtr;
    EthSwt_30_Sja1105PQRS_GetArlTableProcessing[SwitchIdx].LenPtr      = LenPtr;
    RetVal = (Std_ReturnType)E_OK;
  }
  else
  {
    /* processing -> discard call */
    RetVal = (Std_ReturnType)E_NOT_OK;
  }
# endif /* ETHSWT_30_SJA1105PQRS_API_CALL_TYPE */

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_GetArlTable() */ /* PRQA S 2006 */ /* MD_MSR_14.7 */
#endif /* ETHSWT_30_SJA1105PQRS_GET_ARL_TABLE_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_GET_BUFFER_LEVEL_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetBufferLevel()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_GetBufferLevel(
                 EthSwt_SwitchIdxType                  SwitchIdx,
    ETHSWT_P2VAR(EthSwt_BufferLevelType, SJA1105PQRS)  BufferLevelPtr ) /* PRQA S 3673 */ /* MD_EthSwt_30_Sja1105PQRS_3673 */
{
  /* ----- Local data declaration --------------------------------------- */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check initialization state of the component */
  EthSwt_CheckDetErrorReturnValue(                                                          \
        (EthSwt_30_Sja1105PQRS_ModuleInitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE),   \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                              \
        ETHSWT_30_SJA1105PQRS_SID_GET_BUFFER_LEVEL,                                         \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                            \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #20 Check switch index for validity */
  EthSwt_CheckDetErrorReturnValue(                                            \
        ((EthSwt_SwitchIdxType)ETHSWT_30_SJA1105PQRS_SWITCH_NUM > SwitchIdx), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                \
        ETHSWT_30_SJA1105PQRS_SID_GET_BUFFER_LEVEL,                           \
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX,                               \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #30 Check initialization state of the instance */
  EthSwt_CheckDetErrorReturnValue(                                                                            \
        (EthSwt_30_Sja1105PQRS_InstanceData[SwitchIdx].InitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE),   \
        SwitchIdx,                                                                                            \
        ETHSWT_30_SJA1105PQRS_SID_GET_BUFFER_LEVEL,                                                           \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                                              \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(SwitchIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(BufferLevelPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  /* #40 Return E_NOT_OK due to no hardware support */
  return (Std_ReturnType)E_NOT_OK;
} /* EthSwt_30_Sja1105PQRS_GetBufferLevel() */ /* PRQA S 2006 */ /* MD_MSR_14.7 */
#endif /* ETHSWT_30_SJA1105PQRS_GET_BUFFER_LEVEL_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_GET_DROP_COUNT_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetDropCount()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_GetDropCount(
                 EthSwt_SwitchIdxType               SwitchIdx,
    ETHSWT_P2VAR(uint16,              SJA1105PQRS)  LenPtr,
    ETHSWT_P2VAR(uint32,              SJA1105PQRS)  DropCountPtr )
{
  /* ----- Local data declaration --------------------------------------- */
  Std_ReturnType  RetVal;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check initialization state of the component */
  EthSwt_CheckDetErrorReturnValue(                                                        \
        (EthSwt_30_Sja1105PQRS_ModuleInitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                            \
        ETHSWT_30_SJA1105PQRS_SID_GET_DROP_COUNT,                                         \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                          \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #20 Check switch index for validity */
  EthSwt_CheckDetErrorReturnValue(                                            \
        ((EthSwt_SwitchIdxType)ETHSWT_30_SJA1105PQRS_SWITCH_NUM > SwitchIdx), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                \
        ETHSWT_30_SJA1105PQRS_SID_GET_DROP_COUNT,                             \
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX,                               \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #30 Check initialization state of the instance */
  EthSwt_CheckDetErrorReturnValue(                                                                          \
        (EthSwt_30_Sja1105PQRS_InstanceData[SwitchIdx].InitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE), \
        SwitchIdx,                                                                                          \
        ETHSWT_30_SJA1105PQRS_SID_GET_DROP_COUNT,                                                           \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                                            \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #40 Check buffer length */
  EthSwt_CheckDetErrorReturnValue(                                  \
        (ETHSWT_30_SJA1105PQRS_DROP_COUNT_COUNTERS_NUM <= *LenPtr), \
        SwitchIdx,                                                  \
        ETHSWT_30_SJA1105PQRS_SID_GET_DROP_COUNT,                   \
        ETHSWT_30_SJA1105PQRS_E_INV_PARAM,                          \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #50 Trigger drop count retrieval */
# if   ( ETHSWT_30_SJA1105PQRS_API_CALL_TYPE == ETHSWT_30_SJA1105PQRS_API_CALL_TYPE_SYNC_CALL )
  /* process synchronous within this call */
  RetVal = EthSwt_30_Sja1105PQRS_VGetDropCount(SwitchIdx, LenPtr, DropCountPtr);
# elif ( ETHSWT_30_SJA1105PQRS_API_CALL_TYPE == ETHSWT_30_SJA1105PQRS_API_CALL_TYPE_ASYNC_CALL )
  /* trigger the processing in async main function */

  /* check if processing isn't running yet */
  if( EthSwt_30_Sja1105PQRS_GetDropCountProcessing[SwitchIdx].ProcState != ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_PROCESSING )
  {
    /* no processing -> trigger processing */
    EthSwt_30_Sja1105PQRS_GetDropCountProcessing[SwitchIdx].ProcState    = ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_WAITING;
    EthSwt_30_Sja1105PQRS_GetDropCountProcessing[SwitchIdx].DropCountPtr = DropCountPtr;
    EthSwt_30_Sja1105PQRS_GetDropCountProcessing[SwitchIdx].LenPtr       = LenPtr;
    RetVal = (Std_ReturnType)E_OK;
  }
  else
  {
    /* processing -> discard call */
    RetVal = (Std_ReturnType)E_NOT_OK;
  }
# endif /* ETHSWT_30_SJA1105PQRS_API_CALL_TYPE */

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_GetDropCount() */ /* PRQA S 2006,6010 */ /* MD_MSR_14.7,MD_MSR_STPTH */
#endif /* ETHSWT_30_SJA1105PQRS_GET_DROP_COUNT_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_GET_ETHER_STATS_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetEtherStats()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_GetEtherStats(
                 EthSwt_SwitchIdxType               SwitchIdx,
                 EthSwt_PortIdxType                 SwitchPortIdx,
    ETHSWT_P2VAR(uint32,              SJA1105PQRS)  EtherStats )
{
  /* ----- Local data declaration --------------------------------------- */
  Std_ReturnType RetVal;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check initialization state of the component */
  EthSwt_CheckDetErrorReturnValue(                                                         \
        (EthSwt_30_Sja1105PQRS_ModuleInitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE),  \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                             \
        ETHSWT_30_SJA1105PQRS_SID_GET_ETHER_STATS,                                         \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                           \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #20 Check switch index for validity */
  EthSwt_CheckDetErrorReturnValue(                                            \
        ((EthSwt_SwitchIdxType)ETHSWT_30_SJA1105PQRS_SWITCH_NUM > SwitchIdx), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                \
        ETHSWT_30_SJA1105PQRS_SID_GET_ETHER_STATS,                            \
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX,                               \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #30 Check initialization state of the instance */
  EthSwt_CheckDetErrorReturnValue(                                                                           \
        (EthSwt_30_Sja1105PQRS_InstanceData[SwitchIdx].InitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE),  \
        SwitchIdx,                                                                                           \
        ETHSWT_30_SJA1105PQRS_SID_GET_ETHER_STATS,                                                           \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                                             \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #40 Trigger Ethernet statistics retrieval */
# if   ( ETHSWT_30_SJA1105PQRS_API_CALL_TYPE == ETHSWT_30_SJA1105PQRS_API_CALL_TYPE_SYNC_CALL )
  /* process synchronous within this call */
  RetVal = EthSwt_30_Sja1105PQRS_VGetEtherStats(SwitchIdx, SwitchPortIdx, EtherStats);
# elif ( ETHSWT_30_SJA1105PQRS_API_CALL_TYPE == ETHSWT_30_SJA1105PQRS_API_CALL_TYPE_ASYNC_CALL )
  /* trigger the processing in async main function */

  /* check if processing isn't running yet */
  if( EthSwt_30_Sja1105PQRS_GetEtherStatsProcessing[SwitchIdx].ProcState != ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_PROCESSING )
  {
    /* no processing -> trigger processing */
    EthSwt_30_Sja1105PQRS_GetEtherStatsProcessing[SwitchIdx].ProcState     = ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_WAITING;
    EthSwt_30_Sja1105PQRS_GetEtherStatsProcessing[SwitchIdx].PortIdx       = SwitchPortIdx;
    EthSwt_30_Sja1105PQRS_GetEtherStatsProcessing[SwitchIdx].EtherStatsPtr = EtherStats;
    RetVal = (Std_ReturnType)E_OK;
  }
  else
  {
    /* processing -> discard call */
    RetVal = (Std_ReturnType)E_NOT_OK;
  }
# endif /* ETHSWT_30_SJA1105PQRS_API_CALL_TYPE */

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_GetEtherStats() */ /* PRQA S 2006 */ /* MD_MSR_14.7 */
#endif /* ETHSWT_30_SJA1105PQRS_GET_ETHER_STATS_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_GET_SWITCH_REG_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetSwitchReg()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_GetSwitchReg(
                 EthSwt_SwitchIdxType               SwitchIdx,
                 uint32                             page,
                 uint32                             registerAddr,
    ETHSWT_P2VAR(uint32,              SJA1105PQRS)  registerContent )
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS)  SpiTransaction;
               Std_ReturnType                                          RetVal;

   /* ----- Development Error Checks ------------------------------------- */
   EthSwt_CheckDetErrorReturnValue(                                                        \
         (EthSwt_30_Sja1105PQRS_ModuleInitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE), \
         ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                            \
         ETHSWT_30_SJA1105PQRS_SID_GET_SWITCH_REG,                                         \
         ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                          \
         E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
   EthSwt_CheckDetErrorReturnValue(                                            \
         ((EthSwt_SwitchIdxType)ETHSWT_30_SJA1105PQRS_SWITCH_NUM > SwitchIdx), \
         ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                \
         ETHSWT_30_SJA1105PQRS_SID_GET_SWITCH_REG,                             \
         ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX,                               \
         E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(page); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  /* #10 Retrieve switch register */
  RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(SwitchIdx, &SpiTransaction);

  if( RetVal == (Std_ReturnType)E_OK )
  {
    SpiTransaction->AddrIdx = registerAddr;
    RetVal = EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(SwitchIdx, SpiTransaction);

    if( RetVal == (Std_ReturnType)E_OK )
    {
      registerContent[0] = SpiTransaction->DataPtr[0];
    }
    (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(SwitchIdx, SpiTransaction);
  }

  return RetVal;
}  /* PRQA S 2006 */ /* MD_MSR_14.7 */
#endif /* ETHSWT_30_SJA1105PQRS_GET_SWITCH_REG_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_SET_SWITCH_REG_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_SetSwitchReg()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_SetSwitchReg(
    EthSwt_SwitchIdxType  SwitchIdx,
    uint32                page,
    uint32                registerAddr,
    uint32                registerContent )
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS)  SpiTransaction;
               Std_ReturnType                                          RetVal;

   /* ----- Development Error Checks ------------------------------------- */
   EthSwt_CheckDetErrorReturnValue(                                                        \
         (EthSwt_30_Sja1105PQRS_ModuleInitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE), \
         ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                            \
         ETHSWT_30_SJA1105PQRS_SID_SET_SWITCH_REG,                                         \
         ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                          \
         E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
   EthSwt_CheckDetErrorReturnValue(                                            \
         ((EthSwt_SwitchIdxType)ETHSWT_30_SJA1105PQRS_SWITCH_NUM > SwitchIdx), \
         ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                \
         ETHSWT_30_SJA1105PQRS_SID_SET_SWITCH_REG,                             \
         ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX,                               \
         E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(page); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  /* #10 Set switch register */
  RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(SwitchIdx, &SpiTransaction);

  if( RetVal == (Std_ReturnType)E_OK )
  {
    SpiTransaction->AddrIdx    = registerAddr;
    SpiTransaction->DataPtr[0] = registerContent;
    RetVal = EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(SwitchIdx, SpiTransaction);
    (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(SwitchIdx, SpiTransaction);
  }

  return RetVal;
} /* PRQA S 2006 */ /* MD_MSR_14.7 */
#endif /* ETHSWT_30_SJA1105PQRS_SET_SWITCH_REG_API_ENABLED */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_ReadTrcvRegister()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_ReadTrcvRegister(EthSwt_SwitchIdxType SwitchIdx,
                                                                        EthSwt_PortIdxType PortIdx,
                                                                        uint8 RegIdx,
                                                                        ETHSWT_P2VAR(uint16, SJA1105PQRS)  RegValPtr) /* PRQA S 3673 */ /* MD_EthSwt_30_Sja1105PQRS_3673 */
{
  /* ----- Development Error Checks ------------------------------------- */
  EthSwt_CheckDetErrorReturnValue(
        (EthSwt_30_Sja1105PQRS_ModuleInitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE),
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,
        ETHSWT_30_SJA1105PQRS_SID_READ_TRCV_REGISTER,
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  EthSwt_CheckDetErrorReturnValue(
        ((EthSwt_SwitchIdxType)ETHSWT_30_SJA1105PQRS_SWITCH_NUM > SwitchIdx),
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,
        ETHSWT_30_SJA1105PQRS_SID_READ_TRCV_REGISTER,
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX,
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(SwitchIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(PortIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(RegIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(RegValPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  /* - #10 Return E_NOT_OK since Sja1105PQRS has no internal Trcvs */
  return E_NOT_OK;
} /* EthSwt_30_Sja1105PQRS_ReadTrcvRegister() */ /* PRQA S 2006 */ /* MD_MSR_14.7 */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_WriteTrcvRegister()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_WriteTrcvRegister(EthSwt_SwitchIdxType SwitchIdx,
                                                                                 EthSwt_PortIdxType PortIdx,
                                                                                 uint8 RegIdx,
                                                                                 uint16 RegVal)
{
  /* ----- Development Error Checks ------------------------------------- */
  EthSwt_CheckDetErrorReturnValue(
        (EthSwt_30_Sja1105PQRS_ModuleInitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE),
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,
        ETHSWT_30_SJA1105PQRS_SID_WRITE_TRCV_REGISTER,
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  EthSwt_CheckDetErrorReturnValue(
        ((EthSwt_SwitchIdxType)ETHSWT_30_SJA1105PQRS_SWITCH_NUM > SwitchIdx),
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,
        ETHSWT_30_SJA1105PQRS_SID_WRITE_TRCV_REGISTER,
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX,
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(SwitchIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(PortIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(RegIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(RegVal); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  /* - #10 Return E_NOT_OK since Sja1105PQRS has no internal Trcvs */
  return E_NOT_OK;
} /* EthSwt_30_Sja1105PQRS_WriteTrcvRegister() */ /* PRQA S 2006 */ /* MD_MSR_14.7 */

#if ( ETHSWT_30_SJA1105PQRS_ENABLE_VLAN_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_EnableVlan()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
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
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_EnableVlan(
    EthSwt_SwitchIdxType  SwitchIdx,
    EthSwt_PortIdxType    PortIdx,
    uint16                VlanId,
    boolean               Enable )
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_DynVlanTableProcType, SJA1105PQRS) VlanTableProcPtr;
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_DynVlanTableType,     SJA1105PQRS) DynTableEntryPtr;
                 Std_ReturnType                                           RetVal;
                 uint16_least                                             VlanProcTableIdx;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check initialization state of the component */
  EthSwt_CheckDetErrorReturnValue(                                                        \
        (EthSwt_30_Sja1105PQRS_ModuleInitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                            \
        ETHSWT_30_SJA1105PQRS_SID_ENABLE_VLAN,                                            \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                          \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #20 Check switch index for validity */
  EthSwt_CheckDetErrorReturnValue(                                            \
        ((EthSwt_SwitchIdxType)ETHSWT_30_SJA1105PQRS_SWITCH_NUM > SwitchIdx), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                \
        ETHSWT_30_SJA1105PQRS_SID_ENABLE_VLAN,                                \
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX,                               \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  EthSwt_CheckDetErrorReturnValue(                                           \
        (EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].PortNum > PortIdx), \
        SwitchIdx,                                                           \
        ETHSWT_30_SJA1105PQRS_SID_ENABLE_VLAN,                               \
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCHPORT_IDX,                          \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #30 Check initialization state of the instance */
  EthSwt_CheckDetErrorReturnValue(                                                                          \
        (EthSwt_30_Sja1105PQRS_InstanceData[SwitchIdx].InitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE), \
        SwitchIdx,                                                                                          \
        ETHSWT_30_SJA1105PQRS_SID_ENABLE_VLAN,                                                              \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                                            \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* ----- Local data definition ---------------------------------------- */
  RetVal           = (Std_ReturnType)E_NOT_OK;
  VlanTableProcPtr = EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].VlanTableProc;
  DynTableEntryPtr = (ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_DynVlanTableType, SJA1105PQRS))NULL_PTR;

  /* ----- Implementation ----------------------------------------------- */
  /* #40 Query for existing entry for VLAN  */
  /* -- Query for an available entry -- */
  /* check if already a a entry for the VLAN was provided */
  for( VlanProcTableIdx = 0u; VlanProcTableIdx < VlanTableProcPtr->DynEntryUpperBound; VlanProcTableIdx++ )
  {
    uint32 VlanTableId;
    VlanTableId  = VlanTableProcPtr->DynVlanTable[VlanProcTableIdx].Register3 >> ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG3_VLANID_LOWER_SHIFT;
    VlanTableId |= (VlanTableProcPtr->DynVlanTable[VlanProcTableIdx].Register2 & ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG1_VLANID_UPPER_MASK)
                   << ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG1_VLANID_UPPER_SHIFT;

    if( VlanTableId == VlanId )
    {
      DynTableEntryPtr = &VlanTableProcPtr->DynVlanTable[VlanProcTableIdx];
      break;
    }
  }

  /* #50 If no existing entry for VLAN was found */
  /* if no entry for VLAN is provided check if there is space in VLAN table left to handle the request */
  if( DynTableEntryPtr == (ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_DynVlanTableType, SJA1105PQRS))NULL_PTR )
  {
    /* #500 Check if an additional entry can be handled */
    for( VlanProcTableIdx = VlanTableProcPtr->DynEntryLowerBound; VlanProcTableIdx < VlanTableProcPtr->DynEntryUpperBound; VlanProcTableIdx++ )
    {
      if( (VlanTableProcPtr->DynVlanTable[VlanProcTableIdx].Register1 & (uint32)ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG0_VALIDENT_MASK) == (uint32) 0u )
      {
        /* entry is unused */
        DynTableEntryPtr = &VlanTableProcPtr->DynVlanTable[VlanProcTableIdx];
        break;
      }
    }
  }

  /* #60 If any entry was found */
  /* is any entry available to process the request? */
  if( DynTableEntryPtr != (ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_DynVlanTableType, SJA1105PQRS))NULL_PTR )
  {
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS) SpiTransaction;

    RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(SwitchIdx, &SpiTransaction);

    if( RetVal == (Std_ReturnType)E_OK )
    {
      uint8 PortMask;
      uint8 IngressPortMask;
      uint8 EgressPortMask;

      /* #600 Retrieve port mask of entry */
      PortMask = EthSwt_30_Sja1105PQRS_GetPortMaskFromHwPortIndex(
                                    EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].TransformPortIdx(
                                                                                    PortIdx,
                                                                                    ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_INTERNAL_VIEW));

      /* retrieve current port masks for ingress and egress */
      IngressPortMask = (uint8)((DynTableEntryPtr->Register2 & (uint32)ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG1_VMEMB_PORT_MASK)
                                   >> (uint32)ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG1_VMEMB_PORT_SHIFT);
      EgressPortMask  = (uint8)((DynTableEntryPtr->Register2 & (uint32)ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG1_VLAN_BC_MASK)
                                   >> (uint32)ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG1_VLAN_BC_SHIFT);

      /* #610 Change forwarding state */
      if( Enable == (boolean)TRUE )
      {
        /* allow VLAN on ingress and egress */
        IngressPortMask |= PortMask;
        EgressPortMask  |= PortMask;
      }
      else
      {
        /* disallow VLAN on ingress and egress */
        IngressPortMask &= (uint8)(~(uint32)PortMask);
        EgressPortMask  &= (uint8)(~(uint32)PortMask);
      }

      /* #620 Prepare entry and download to switch */
      /* adapt RAM mirrors of registers */
      /* prepare command register */
      DynTableEntryPtr->Register1 = (uint32)((uint32) ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG0_VALID_MASK
                                           | (uint32) ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG0_RDWRSET_MASK);

      /* if port masks have set any bits -> mark entry as valid */
      if( (IngressPortMask != (uint8)0u) && (EgressPortMask != (uint8)0u) )
      {
        DynTableEntryPtr->Register1 |= (uint32)ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG0_VALIDENT_MASK;
      }

      /* prepare lower word of entry */
      DynTableEntryPtr->Register3 = (uint32)((uint32)ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG3_VLANID_LOWER_MASK
                                       & ((uint32)VlanId << (uint32)ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG3_VLANID_LOWER_SHIFT));
      /* prepare higher word of entry */
      /* clear everything except the untag map */
      DynTableEntryPtr->Register2 &= (uint32)ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG1_TAG_PORT_MASK;
      /* setup new register data */
      DynTableEntryPtr->Register2 |= (uint32)(((uint32)ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG1_VMEMB_PORT_MASK
                                             & ((uint32)IngressPortMask << (uint32)ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG1_VMEMB_PORT_SHIFT))
                                         | ((uint32)ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG1_VLAN_BC_MASK
                                             & ((uint32)EgressPortMask << (uint32)ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG1_VLAN_BC_SHIFT))
                                         | ((uint32)ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG1_VLANID_UPPER_MASK
                                             & ((uint32)VlanId >> (uint32)ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG1_VLANID_UPPER_SHIFT)));

      /* provide table entry data */
      SpiTransaction->AddrIdx    = (uint32)ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG1_ADDR;
      SpiTransaction->WordNum    = (uint16)2u;
      SpiTransaction->DataPtr[0] = DynTableEntryPtr->Register3;
      SpiTransaction->DataPtr[1] = DynTableEntryPtr->Register2;

      RetVal |= EthSwt_30_Sja1105PQRS_LL_WriteBytesSync(SwitchIdx, SpiTransaction);

      /* commit table entry data to VLAN lookup table */
      SpiTransaction->AddrIdx    = (uint32)ETHSWT_30_SJA1105PQRS_VLAN_LOOKUP_TABLE_RECONFIG_REG0_ADDR;
      SpiTransaction->DataPtr[0] = DynTableEntryPtr->Register1;

      RetVal |= EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(SwitchIdx, SpiTransaction);

      (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(SwitchIdx, SpiTransaction);
    }
  }

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_EnableVlan() */ /* PRQA S 2006,6010,6030 */ /* MD_MSR_14.7,MD_MSR_STPTH,MD_MSR_STCYC */
#endif /* ETHSWT_30_SJA1105PQRS_ENABLE_VLAN_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_StoreConfiguration()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_StoreConfiguration(
    EthSwt_SwitchIdxType  SwitchIdx )
{
  /* ----- Local data declaration --------------------------------------- */
  Std_ReturnType  RetVal;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check initialization state of the component */
  EthSwt_CheckDetErrorReturnValue(                                                        \
        (EthSwt_30_Sja1105PQRS_ModuleInitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                            \
        ETHSWT_30_SJA1105PQRS_SID_STORE_CONFIGURATION,                                    \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                          \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #20 Check switch index for validity */
  EthSwt_CheckDetErrorReturnValue(                                            \
        ((EthSwt_SwitchIdxType)ETHSWT_30_SJA1105PQRS_SWITCH_NUM > SwitchIdx), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                \
        ETHSWT_30_SJA1105PQRS_SID_STORE_CONFIGURATION,                        \
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX,                               \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #30 Check initialization state of the instance */
  EthSwt_CheckDetErrorReturnValue(                                                                          \
        (EthSwt_30_Sja1105PQRS_InstanceData[SwitchIdx].InitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE), \
        SwitchIdx,                                                                                          \
        ETHSWT_30_SJA1105PQRS_SID_STORE_CONFIGURATION,                                                      \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                                            \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* ----- Local data definition ---------------------------------------- */
  RetVal = (Std_ReturnType)E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #40 Trigger configuration storage */
  /* trigger the processing in async main function */

  /* check if processing isn't running yet */
  if( EthSwt_30_Sja1105PQRS_StoreConfigProcessing.ProcState != ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_PROCESSING )
  {
    /* no processing -> trigger processing */
    EthSwt_30_Sja1105PQRS_StoreConfigProcessing.ProcState = ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_WAITING;
    EthSwt_30_Sja1105PQRS_StoreConfigProcessing.SwitchIdx = SwitchIdx;
    RetVal = (Std_ReturnType)E_OK;
  }

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_StoreConfiguration() */ /* PRQA S 2006 */ /* MD_MSR_14.7 */
#endif /* ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_ResetConfiguration()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_ResetConfiguration(
    EthSwt_SwitchIdxType  SwitchIdx )
{
  /* ----- Local data declaration --------------------------------------- */
  Std_ReturnType  RetVal;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check initialization state of the component */
  EthSwt_CheckDetErrorReturnValue(                                                        \
        (EthSwt_30_Sja1105PQRS_ModuleInitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                            \
        ETHSWT_30_SJA1105PQRS_SID_RESET_CONFIGURATION,                                    \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                          \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #20 Check switch index for validity */
  EthSwt_CheckDetErrorReturnValue(                                            \
        ((EthSwt_SwitchIdxType)ETHSWT_30_SJA1105PQRS_SWITCH_NUM > SwitchIdx), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                \
        ETHSWT_30_SJA1105PQRS_SID_RESET_CONFIGURATION,                        \
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX,                               \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #30 Check initialization state of the instance */
  EthSwt_CheckDetErrorReturnValue(                                                                          \
        (EthSwt_30_Sja1105PQRS_InstanceData[SwitchIdx].InitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE), \
        SwitchIdx,                                                                                          \
        ETHSWT_30_SJA1105PQRS_SID_RESET_CONFIGURATION,                                                      \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                                            \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* ----- Local data definition ---------------------------------------- */
  RetVal = (Std_ReturnType)E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #40 Trigger configuration reset */
  /* trigger the processing in async main function */

  /* check if processing isn't running yet */
  if( EthSwt_30_Sja1105PQRS_ResetConfigProcessing.ProcState != ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_PROCESSING )
  {
    /* no processing -> trigger processing */
    EthSwt_30_Sja1105PQRS_ResetConfigProcessing.ProcState = ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_WAITING;
    EthSwt_30_Sja1105PQRS_ResetConfigProcessing.SwitchIdx = SwitchIdx;
    RetVal = (Std_ReturnType)E_OK;
  }

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_ResetConfiguration() */ /* PRQA S 2006 */ /* MD_MSR_14.7 */
#endif /* ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_SET_MAC_LEARNING_MODE_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_SetMacLearningMode()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_SetMacLearningMode(
    EthSwt_SwitchIdxType    SwitchIdx,
    EthSwt_PortIdxType      PortIdx,
    EthSwt_MacLearningType  MacLearningMode )
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  InstanceConfig;
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS)  SpiTransaction;
                 uint8                                                   HwPortIdx;
                 Std_ReturnType                                          RetVal;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check initialization state of the component */
  EthSwt_CheckDetErrorReturnValue(                                                        \
        (EthSwt_30_Sja1105PQRS_ModuleInitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                            \
        ETHSWT_30_SJA1105PQRS_SID_SET_MAC_LEARNING_MODE,                                  \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                          \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #20 Check switch index for validity */
  EthSwt_CheckDetErrorReturnValue(                                            \
        ((EthSwt_SwitchIdxType)ETHSWT_30_SJA1105PQRS_SWITCH_NUM > SwitchIdx), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                \
        ETHSWT_30_SJA1105PQRS_SID_SET_MAC_LEARNING_MODE,                      \
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX,                               \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #30 Check initialization state of the instance */
  EthSwt_CheckDetErrorReturnValue(                                                                          \
        (EthSwt_30_Sja1105PQRS_InstanceData[SwitchIdx].InitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE), \
        SwitchIdx,                                                                                          \
        ETHSWT_30_SJA1105PQRS_SID_SET_MAC_LEARNING_MODE,                                                    \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                                            \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* ----- Local data definition ---------------------------------------- */
  InstanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx];
  HwPortIdx = InstanceConfig->TransformPortIdx(PortIdx, ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_INTERNAL_VIEW);

  /* ----- Implementation ----------------------------------------------- */
  /* #40 Adapt learning mode of port */
  switch( MacLearningMode )
  {
    case ETHSWT_MACLEARNING_HWDISABLED:
      /* disable learning */
      InstanceConfig->DynMacTableEntries[PortIdx].Register2 &= (uint32)~((uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG2_PORTST_MAC_LEARN_EN_MASK);
      RetVal = (Std_ReturnType)E_OK;
      break;
    case ETHSWT_MACLEARNING_HWENABLED:
      /* enable learning */
      InstanceConfig->DynMacTableEntries[PortIdx].Register2 |= (uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG2_PORTST_MAC_LEARN_EN_MASK;
      RetVal = (Std_ReturnType)E_OK;
      break;
    default: /* and ETHSWT_MACLEARNING_SWENABLED */
      RetVal = (Std_ReturnType)E_NOT_OK;
      break;
  }

  /* #50 Process the reconfiguration */
  if( RetVal == (Std_ReturnType)E_OK )
  {
    RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(SwitchIdx, &SpiTransaction);

    if( RetVal == (Std_ReturnType)E_OK )
    {
      /* Read current values */
      SpiTransaction->AddrIdx    = (uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG2_ADDR;
      SpiTransaction->DataPtr[0] = InstanceConfig->DynMacTableEntries[PortIdx].Register2;
      RetVal |= EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(SwitchIdx, SpiTransaction);

      /* Write/activate current values */
      SpiTransaction->AddrIdx     = (uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG0_ADDR;
      SpiTransaction->DataPtr[0]  = HwPortIdx;
      SpiTransaction->DataPtr[0] |= (uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG0_VALID_MASK;
      SpiTransaction->DataPtr[0] |= (uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG0_RDWRSET_MASK;
      RetVal |= EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(SwitchIdx, SpiTransaction);

      (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(SwitchIdx, SpiTransaction);
    }
  }

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_SetMacLearningMode() */ /* PRQA S 2006,6010,6030 */ /* MD_MSR_14.7,MD_MSR_STPTH,MD_MSR_STCYC */
#endif /* ETHSWT_30_SJA1105PQRS_SET_MAC_LEARNING_MODE_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_GET_MAC_LEARNING_MODE_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetMacLearningMode()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_GetMacLearningMode(
                 EthSwt_SwitchIdxType                  SwitchIdx,
                 EthSwt_PortIdxType                    PortIdx,
    ETHSWT_P2VAR(EthSwt_MacLearningType, SJA1105PQRS)  MacLearningModePtr )
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  InstanceConfig;
                 Std_ReturnType                                          RetVal;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check initialization state of the component */
  EthSwt_CheckDetErrorReturnValue(                                                        \
        (EthSwt_30_Sja1105PQRS_ModuleInitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                            \
        ETHSWT_30_SJA1105PQRS_SID_GET_MAC_LEARNING_MODE,                                  \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                          \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #20 Check switch index for validity */
  EthSwt_CheckDetErrorReturnValue(                                            \
        ((EthSwt_SwitchIdxType)ETHSWT_30_SJA1105PQRS_SWITCH_NUM > SwitchIdx), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                \
        ETHSWT_30_SJA1105PQRS_SID_GET_MAC_LEARNING_MODE,                      \
        ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX,                               \
        E_NOT_OK);
  /* #30 Check initialization state of the instance */
  EthSwt_CheckDetErrorReturnValue(                                                                          \
        (EthSwt_30_Sja1105PQRS_InstanceData[SwitchIdx].InitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE), \
        SwitchIdx,                                                                                          \
        ETHSWT_30_SJA1105PQRS_SID_GET_MAC_LEARNING_MODE,                                                    \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                                            \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* ----- Local data definition ---------------------------------------- */
  InstanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx];
  RetVal = (Std_ReturnType)E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #40 Retrieve MAC learning mode */
  if( (InstanceConfig->DynMacTableEntries[PortIdx].Register2
        & (uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG2_PORTST_MAC_LEARN_EN_MASK) != (uint32)0u )
  {
      MacLearningModePtr[0] = (EthSwt_MacLearningType)ETHSWT_MACLEARNING_HWENABLED;
  }
  else
  {
      MacLearningModePtr[0] = (EthSwt_MacLearningType)ETHSWT_MACLEARNING_HWDISABLED;
  }

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_GetMacLearningMode() */ /* PRQA S 2006 */ /* MD_MSR_14.7 */
#endif /* ETHSWT_30_SJA1105PQRS_GET_MAC_LEARNING_MODE_API_ENABLED */

#if (    ( ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED == STD_ON )\
      || ( ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED == STD_ON ))
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_NvmSingleBlockCallback()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_NvmSingleBlockCallback(
  NvM_ServiceIdType      ServiceId,
  NvM_RequestResultType  JobResult )
{
  /* ----- Local data declaration --------------------------------------- */

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check initialization state of the component */
  EthSwt_CheckDetErrorReturnValue(                                                        \
        (EthSwt_30_Sja1105PQRS_ModuleInitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE), \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                            \
        ETHSWT_30_SJA1105PQRS_SID_NVM_SINGLE_BLOCK_CALLBACK,                              \
        ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED,                                          \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  EthSwt_CheckDetErrorReturnValue(                                                        \
        (JobResult != NVM_REQ_NOT_OK),                                                    \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,                                            \
        ETHSWT_30_SJA1105PQRS_SID_NVM_SINGLE_BLOCK_CALLBACK,                              \
        ETHSWT_30_SJA1105PQRS_E_OP_FAILED,                                                \
        E_NOT_OK); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* ServiceId is never used */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(ServiceId); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  /* #20 If feature user notification for NV-RAM operation is enabled */
# if ( ETHSWT_30_SJA1105PQRS_NVM_SINGLE_BLOCK_USER_CALLBACK_ENABLED == STD_ON )
  /* #200 Call user notification */
  EthSwt_30_Sja1105PQRS_NvmSingleBlockUserCallback(JobResult);
# else
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(JobResult); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* ETHSWT_30_SJA1105PQRS_NVM_SINGLE_BLOCK_USER_CALLBACK_ENABLED */

  /* According to requirement SWS_EthSwt_00127 which relates to
   * SWS_NvM_00368 the function shall always return E_OK.
   */
  return E_OK;
} /* EthSwt_30_Sja1105PQRS_NvmSingleBlockCallback() */ /* PRQA S 2006 */ /* MD_MSR_14.7 */
#endif /* ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED, ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_MainFunction()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETHSWT_FUNC(void, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_MainFunction( void )
{
  /* ----- Local data declaration ----------------------------------- */
  uint8_least  LoopIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If module is initialized */
  if( EthSwt_30_Sja1105PQRS_ModuleInitState >= (EthSwt_StateType)ETHSWT_STATE_INIT )
  {
    /* #100 For each switch instance */
    for( LoopIdx = 0; LoopIdx < ETHSWT_30_SJA1105PQRS_SWITCH_NUM; LoopIdx++ )
    {
      /* #1000 If switch instance is ACTIVE */
      if( EthSwt_30_Sja1105PQRS_InstanceData[LoopIdx].InitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE )
      {
        /* #10000 If feature production error detection is enabled */
#if ( ETHSWT_30_SJA1105PQRS_PROD_ERROR_REPORTING == STD_ON )
        /* #100000 Trigger production error detection */
        EthSwt_30_Sja1105PQRS_DetectProdErrors((EthSwt_SwitchIdxType)LoopIdx);
#endif /* ETHSWT_30_SJA1105PQRS_PROD_ERROR_REPORTING */
      }
    }
  }
} /* EthSwt_30_Sja1105PQRS_MainFunction() */ /* PRQA S 2006 */ /* MD_MSR_14.7 */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_AsyncProcessingMainFunction()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
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
ETHSWT_FUNC(void, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_AsyncProcessingMainFunction( void )
{
  /* ----- Local data declaration --------------------------------------- */
  uint8_least LoopSwitchIdx;
  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 For each switch instance */
  for( LoopSwitchIdx = 0u; LoopSwitchIdx < ETHSWT_30_SJA1105PQRS_SWITCH_NUM; LoopSwitchIdx++ )
  {

    /* #100 If instance is ACTIVE */
    if( EthSwt_30_Sja1105PQRS_InstanceData[LoopSwitchIdx].InitState == (EthSwt_StateType)ETHSWT_STATE_ACTIVE )
    {
      /* #1000 If feature async API processing is enabled */
#if ( ETHSWT_30_SJA1105PQRS_API_CALL_TYPE == ETHSWT_30_SJA1105PQRS_API_CALL_TYPE_ASYNC_CALL )

# if ( ETHSWT_30_SJA1105PQRS_GET_ARL_TABLE_API_ENABLED == STD_ON )
      /* #10000 Process address resolution table retrieval */
      /* check if async processing was triggered */
      if( EthSwt_30_Sja1105PQRS_GetArlTableProcessing[LoopSwitchIdx].ProcState == ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_WAITING )
      {
        Std_ReturnType RetVal;

        /* activate processing */
        EthSwt_30_Sja1105PQRS_GetArlTableProcessing[LoopSwitchIdx].ProcState = ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_PROCESSING;

        /* process request */
        RetVal = EthSwt_30_Sja1105PQRS_VGetArlTable(
                                    LoopSwitchIdx,
                                    EthSwt_30_Sja1105PQRS_GetArlTableProcessing[LoopSwitchIdx].LenPtr,
                                    EthSwt_30_Sja1105PQRS_GetArlTableProcessing[LoopSwitchIdx].ArlTablePtr);

        /* inform caller about finished processing */
        if( RetVal == (Std_ReturnType)E_OK )
        {
          EthSwt_30_Sja1105PQRS_AsyncCallFinishedNotification(LoopSwitchIdx, ETHSWT_30_SJA1105PQRS_SID_GET_ARL_TABLE, TRUE);
        }
        else
        {
          EthSwt_30_Sja1105PQRS_AsyncCallFinishedNotification(LoopSwitchIdx, ETHSWT_30_SJA1105PQRS_SID_GET_ARL_TABLE, FALSE);
        }

        /* allow new processing request */
        EthSwt_30_Sja1105PQRS_GetArlTableProcessing[LoopSwitchIdx].ProcState = ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_IDLE;
      }
# endif /* ETHSWT_30_SJA1105PQRS_GET_ARL_TABLE_API_ENABLED */

# if ( ETHSWT_30_SJA1105PQRS_GET_DROP_COUNT_API_ENABLED == STD_ON )
      /* #10010 Process drop count retrieval */
      /* check if async processing was triggered */
      if( EthSwt_30_Sja1105PQRS_GetDropCountProcessing[LoopSwitchIdx].ProcState == ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_WAITING )
      {
        Std_ReturnType RetVal;
        boolean        Result;

        /* activate processing */
        EthSwt_30_Sja1105PQRS_GetDropCountProcessing[LoopSwitchIdx].ProcState = ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_PROCESSING;

        /* process request */
        RetVal = EthSwt_30_Sja1105PQRS_VGetDropCount(
                                    LoopSwitchIdx,
                                    EthSwt_30_Sja1105PQRS_GetDropCountProcessing[LoopSwitchIdx].LenPtr,
                                    EthSwt_30_Sja1105PQRS_GetDropCountProcessing[LoopSwitchIdx].DropCountPtr);

        /* inform caller about finished processing */
        if( RetVal == (Std_ReturnType)E_OK )
        {
          Result = (boolean)TRUE;
        }
        else
        {
          Result = (boolean)FALSE;
        }

#  if ( ETHSWT_30_SJA1105PQRS_PROD_ERROR_REPORTING == STD_ON )
        if( EthSwt_30_Sja1105PQRS_ProdErrorDetect_IsPending[LoopSwitchIdx] == (boolean)FALSE )
        {
#  endif /* ETHSWT_30_SJA1105PQRS_PROD_ERROR_REPORTING */
          EthSwt_30_Sja1105PQRS_AsyncCallFinishedNotification(LoopSwitchIdx, ETHSWT_30_SJA1105PQRS_SID_GET_DROP_COUNT, Result);
#  if ( ETHSWT_30_SJA1105PQRS_PROD_ERROR_REPORTING == STD_ON )
        }
        else
        {
          EthSwt_30_Sja1105PQRS_ReportProdErrors(LoopSwitchIdx);
        }
#  endif /* ETHSWT_30_SJA1105PQRS_PROD_ERROR_REPORTING */

        /* allow new processing request */
        EthSwt_30_Sja1105PQRS_GetDropCountProcessing[LoopSwitchIdx].ProcState = ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_IDLE;
      }
# endif /* ETHSWT_30_SJA1105PQRS_GET_DROP_COUNT_API_ENABLED */

# if ( ETHSWT_30_SJA1105PQRS_GET_ETHER_STATS_API_ENABLED == STD_ON )
      /* #10020 Process Ethernet statistics retrieval */
      /* check if async processing was triggered */
      if( EthSwt_30_Sja1105PQRS_GetEtherStatsProcessing[LoopSwitchIdx].ProcState == ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_WAITING )
      {
        Std_ReturnType RetVal;

        /* activate processing */
        EthSwt_30_Sja1105PQRS_GetEtherStatsProcessing[LoopSwitchIdx].ProcState = ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_PROCESSING;

        /* process request */
        RetVal = EthSwt_30_Sja1105PQRS_VGetEtherStats(
                                    LoopSwitchIdx,
                                    EthSwt_30_Sja1105PQRS_GetEtherStatsProcessing[LoopSwitchIdx].PortIdx,
                                    EthSwt_30_Sja1105PQRS_GetEtherStatsProcessing[LoopSwitchIdx].EtherStatsPtr);

        /* inform caller about finished processing */
        if( RetVal == (Std_ReturnType)E_OK )
        {
          EthSwt_30_Sja1105PQRS_AsyncCallFinishedNotification(LoopSwitchIdx, ETHSWT_30_SJA1105PQRS_SID_GET_ETHER_STATS, TRUE);
        }
        else
        {
          EthSwt_30_Sja1105PQRS_AsyncCallFinishedNotification(LoopSwitchIdx, ETHSWT_30_SJA1105PQRS_SID_GET_ETHER_STATS, FALSE);
        }

        /* allow new processing request */
        EthSwt_30_Sja1105PQRS_GetEtherStatsProcessing[LoopSwitchIdx].ProcState = ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_IDLE;
      }
# endif /* ETHSWT_30_SJA1105PQRS_GET_ETHER_STATS_API_ENABLED */

#endif /* ETHSWT_30_SJA1105PQRS_API_CALL_TYPE */

#if ( ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED == STD_ON )
      /* #2000 Process configuration storage */
      /* check if async processing was triggered */
      if( EthSwt_30_Sja1105PQRS_StoreConfigProcessing.ProcState == ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_WAITING )
      {
        /* activate processing */
        EthSwt_30_Sja1105PQRS_StoreConfigProcessing.ProcState = ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_PROCESSING;

        /* process request */
        (void)EthSwt_30_Sja1105PQRS_VStoreConfiguration(EthSwt_30_Sja1105PQRS_StoreConfigProcessing.SwitchIdx);

        /* allow new processing request */
        EthSwt_30_Sja1105PQRS_StoreConfigProcessing.ProcState = ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_IDLE;
      }
#endif /* ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED == STD_ON )
      /* #3000 Process configuration reset */
      /* check if async processing was triggered */
      if( EthSwt_30_Sja1105PQRS_ResetConfigProcessing.ProcState == ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_WAITING )
      {
                /* activate processing */
        EthSwt_30_Sja1105PQRS_ResetConfigProcessing.ProcState = ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_PROCESSING;

        /* process request */
        (void)EthSwt_30_Sja1105PQRS_VResetConfiguration(EthSwt_30_Sja1105PQRS_StoreConfigProcessing.SwitchIdx);

        /* allow new processing request */
        EthSwt_30_Sja1105PQRS_ResetConfigProcessing.ProcState = ETHSWT_30_SJA1105PQRS_ASYNC_PROC_STATE_IDLE;
      }
#endif /* ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED */
    }
  }
} /* EthSwt_30_Sja1105PQRS_AsyncProcessingMainFunction() */

#if ( ETHSWT_30_SJA1105PQRS_UPDATE_MCAST_PORT_ASSIGN_API_ENABLED == STD_ON )

/**********************************************************************************************************************
 * EthSwt_30_Sja1105_FindEmptyL2LookupTablePosition()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105_FindEmptyL2LookupTablePosition(
    uint8   SwitchIdx,
    uint16 *l2LookupTableIndex)
{

  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType,  SJA1105PQRS)  InstanceConfig;
                 Std_ReturnType                                           RetVal = E_NOT_OK;
                 EthSwt_30_Sja1105PQRS_L2LookupTableWriteResultType       searchResult = 0;

  InstanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx];
  /* #10 Iterate through L2Lookup Table for finding an empty entry */
  for(*l2LookupTableIndex = 0; *l2LookupTableIndex < InstanceConfig->StaticL2LookupTableEntries; (*l2LookupTableIndex)++)
  {
    /* #100 Check for empty entries at the current position */
    RetVal = EthSwt_30_Sja1105PQRS_CheckL2LookupTableAvailability(SwitchIdx, *l2LookupTableIndex, &searchResult);
    if((RetVal == E_OK) &&
       (searchResult == ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_WRITE_OK))
    {
      /* #200 Remember and return found empty position */
      RetVal = E_OK;
      break;
    }
  }

  if(*l2LookupTableIndex == InstanceConfig->StaticL2LookupTableEntries)
  {
    /* No empty entry found in static area of L2LookupTable, return E_NOT_OK */
    RetVal = E_NOT_OK;
  }
  return RetVal;
}

/**********************************************************************************************************************
 * EthSwt_30_Sja1105_InvalidateL2LookupTableEntry()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105_InvalidateL2LookupTableEntry(
    EthSwt_SwitchIdxType                        SwitchIdx,
    uint16                                      L2LookupTableIndex)
{
  Std_ReturnType RetVal;
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS)  SpiTransaction;

  EthSwt_EnterExclusiveArea(Sja1105PQRS, ARL_TABLE_ACCESS); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(SwitchIdx, &SpiTransaction);

  if(RetVal == E_OK)
  {
    SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_ADDR;

    /* #10 setup INDEX in register 5 */
    SpiTransaction->DataPtr[0]  = (uint32)0u;
    SpiTransaction->DataPtr[0] |= (uint32)((uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_INDEX_MASK
        & ((uint32)L2LookupTableIndex << (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG5_INDEX_SHIFT));

    RetVal = EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(SwitchIdx, SpiTransaction);

    /* #20 setup register 0 (command register) without VALIDENT flag set */
    SpiTransaction->DataPtr[0] = (uint32)((uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_VALID_MASK
        | (uint32)ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_RDWRSET_VAL_WR_MASK
        | (uint32)(ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_HOSTCMD_WRITE <<
            ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_RECONFIG_REG0_HOSTCMD_SHIFT));

    RetVal |= EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(SwitchIdx, SpiTransaction);

    (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(SwitchIdx, SpiTransaction);
  }

  EthSwt_ExitExclusiveArea(Sja1105PQRS, ARL_TABLE_ACCESS); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return RetVal;
}

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_UpdateMCastPortAssignment()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_UpdateMCastPortAssignment(
                 EthSwt_SwitchIdxType                        SwitchIdx,
                 EthSwt_PortIdxType                          PortIdx,
  ETHSWT_P2CONST(uint8,                           SJA1105PQRS)  MCastAddr,
                 EthSwt_MCastPortAssignActionType            Action)
{
  /* ----- Local data declaration --------------------------------------- */
  Std_ReturnType RetVal  = E_NOT_OK;
  uint8          errorId = ETHSWT_30_SJA1105PQRS_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of input parameters and module state */
  if( EthSwt_30_Sja1105PQRS_ModuleInitState != ETHSWT_STATE_ACTIVE )
  {
    errorId = ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED;
  }
  else if( SwitchIdx >= ETHSWT_30_SJA1105PQRS_SWITCH_NUM )
  {
    errorId = ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX;
  }
  else if( PortIdx >= EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].PortNum )
  {
    errorId = ETHSWT_30_SJA1105PQRS_E_INV_SWITCHPORT_IDX;
  }
  else if( MCastAddr == NULL_PTR)
  {
    errorId = ETHSWT_30_SJA1105PQRS_E_INV_POINTER;
  }
  else if( EthSwt_30_Sja1105PQRS_IsMulticastAddress(MCastAddr[0]) == FALSE )
  {
    errorId = ETHSWT_30_SJA1105PQRS_E_INV_PARAM;
  }
  else if( EthSwt_30_Sja1105PQRS_IsUplinkPort(SwitchIdx, PortIdx) == TRUE )
  {
    errorId = ETHSWT_30_SJA1105PQRS_E_INV_PARAM;
  }
  else if( (Action != ETHSWT_MCAST_PORT_ASSIGN_ACTION_ADD)    &&
           (Action != ETHSWT_MCAST_PORT_ASSIGN_ACTION_REMOVE)    )
  {
    errorId = ETHSWT_30_SJA1105PQRS_E_INV_PARAM;
  }
  else
#endif /* ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT */
  {
    /* ----- Local data declaration --------------------------------------- */
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_UpdateMCastPortAssignBucketType, SJA1105PQRS) mCastEntry = NULL_PTR;
                 uint8                                         bucketOffset;

    /* ----- Local data definition ---------------------------------------- */

    /* ----- Implementation ----------------------------------------------- */
    /* #20 Calculate bucket offset */
    bucketOffset = EthSwt_30_Sja1105PQRS_CascadingConfig.CascadingMaps[SwitchIdx].BucketOffset + PortIdx;

    /* #30 Adapt the bucket counters dependent on the action applied for the multicast address */
    if( Action == ETHSWT_MCAST_PORT_ASSIGN_ACTION_ADD )
    {
      if( EthSwt_30_Sja1105PQRS_GetMCastPortAssignBucketsForActionAdd(MCastAddr, &mCastEntry) == TRUE )
      {
        if( mCastEntry->PortRequests[bucketOffset] < ETHSWT_30_SJA1105PQRS_MAX_BUCKET_CNT )
        {
          mCastEntry->PortRequests[bucketOffset]++;
          RetVal = E_OK;
        }
      }
    }
    else
    {
      if( EthSwt_30_Sja1105PQRS_GetMCastPortAssignBucketsForActionRemove(MCastAddr, &mCastEntry) == TRUE )
      {
        if( mCastEntry->PortRequests[bucketOffset] > 0u )
        {
          mCastEntry->PortRequests[bucketOffset]--;
          RetVal = E_OK;
        }
      }
    }

    if( RetVal == E_OK )
    {
      uint8_least                                             switchLoopIdx;
      EthSwt_30_Sja1105PQRS_PortMaskType                      portMasks[ETHSWT_30_SJA1105PQRS_SWITCH_NUM];
      uint16                                                  l2LookupTableIndex;
      uint8                                                   switchPortIdx;

      /* #40 Update the buckets of the uplink ports if needed and create the port masks that must be written to the ARL table */
      EthSwt_30_Sja1105PQRS_UpdateUplinkPortBuckets((ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_PortBucketsType, SJA1105PQRS))&mCastEntry->PortRequests); /*lint !e545 */
      EthSwt_30_Sja1105PQRS_CreatePortMasksFromBuckets((ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_PortBucketsType, SJA1105PQRS))&mCastEntry->PortRequests, portMasks); /*lint !e545 */

      EthSwt_EnterExclusiveArea(Sja1105PQRS, ARL_TABLE_ACCESS); /* PRQA S 3109 */ /* MD_MSR_14.3 */

      /* #50 Update the ARL table of each switch with the updated port masks */
      for( switchLoopIdx = 0u; switchLoopIdx < ETHSWT_30_SJA1105PQRS_SWITCH_NUM; switchLoopIdx++ )
      {
        /* Find index of multicast, if existent */
        if(EthSwt_30_Sja1105PQRS_SearchL2LookupTableEntry((uint8)switchLoopIdx, MCastAddr, &switchPortIdx, &l2LookupTableIndex) == E_OK)
        {
          /* Nothing to do, we have already a valid l2LookupTableIndex */
        }
        else
        {
          /* No matching entry found - take a free entry */
          RetVal = EthSwt_30_Sja1105_FindEmptyL2LookupTablePosition((uint8)switchLoopIdx, &l2LookupTableIndex);
        }

        if(RetVal != E_OK) {break; }

        /* Is valid PortMask existent? */
        if(portMasks[switchLoopIdx] != 0)
        {
          EthSwt_30_Sja1105PQRS_MgmtRouteCfgType MgmtRouteCfg;
          EthSwt_30_Sja1105PQRS_L2LookupTableWriteResultType WriteResult;

          MgmtRouteCfg.EnableMgmtRoute = FALSE;
          MgmtRouteCfg.EnableTimeStamp = FALSE;

          RetVal = EthSwt_30_Sja1105PQRS_WriteL2LookupTableEntry((uint8)switchLoopIdx,
                                                                 l2LookupTableIndex,
                                                                 MCastAddr,
                                                                 0,
                                                                 (uint8)portMasks[switchLoopIdx],
                                                                 &MgmtRouteCfg,
                                                                 TRUE,
                                                                 &WriteResult);

          /* PRQA S 0715 4 */ /* MD_MSR_1.1_715 */
          if(WriteResult == ETHSWT_30_SJA1105PQRS_L2_LOOKUP_TABLE_WRITE_OCCUPIED)
          {
            RetVal = E_NOT_OK;
          }
        }
        else
        {
          /*  The L2LookupTableLine needs to be invalidated */
          RetVal = EthSwt_30_Sja1105_InvalidateL2LookupTableEntry((uint8)switchLoopIdx, l2LookupTableIndex);
        }
        EthSwt_30_Sja1105PQRS_PrepareAddressOfMCastEntry(MCastAddr, mCastEntry);
      }

      EthSwt_ExitExclusiveArea(Sja1105PQRS, ARL_TABLE_ACCESS); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    }
  }

#if ( ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON )
  /* #60 If any development error occurred */
  if( errorId != ETHSWT_30_SJA1105PQRS_E_NO_ERROR )
  {
    /* #600 Report development error to DET */
    (void)Det_ReportError(ETHSWT_30_SJA1105PQRS_MODULE_ID, SwitchIdx,
        ETHSWT_30_SJA1105PQRS_UPDATE_MCAS_PORT_ASSIGNMENT, errorId);
  }
#else
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
#endif /* ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT */

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_UpdateMCastPortAssignment() */ /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* ETHSWT_30_SJA1105PQRS_UPDATE_MCAST_PORT_ASSIGN_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_VERSION_INFO_API_ENABLED == STD_ON )
/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_GetVersionInfo()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetVersionInfo(
    ETHSWT_P2VAR(Std_VersionInfoType, SJA1105PQRS)  VersionInfoPtr)
{
  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if pointer is valid */
  EthSwt_CheckDetErrorReturnVoid(                     \
    (NULL_PTR != VersionInfoPtr),                     \
    ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,            \
    ETHSWT_30_SJA1105PQRS_SID_GET_VERSION_INFO,       \
    ETHSWT_30_SJA1105PQRS_E_INV_POINTER); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* ----- Implementation ----------------------------------------------- */
  /* #20 Retrieve version information */
  VersionInfoPtr->vendorID         = (uint16)( ETHSWT_30_SJA1105PQRS_VENDOR_ID );
  VersionInfoPtr->moduleID         = (uint16)( ETHSWT_30_SJA1105PQRS_MODULE_ID );
  VersionInfoPtr->sw_major_version =  (uint8)( ETHSWT_30_SJA1105PQRS_SW_MAJOR_VERSION );
  VersionInfoPtr->sw_minor_version =  (uint8)( ETHSWT_30_SJA1105PQRS_SW_MINOR_VERSION );
  VersionInfoPtr->sw_patch_version =  (uint8)( ETHSWT_30_SJA1105PQRS_SW_PATCH_VERSION );

} /* EthSwt_30_Sja1105PQRS_GetVersionInfo() */  /* PRQA S 2006 */ /* MD_MSR_14.7 */
#endif /* ETHSWT_30_SJA1105PQRS_VERSION_INFO_API_ENABLED */

#define ETHSWT_30_SJA1105PQRS_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Module specific MISRA deviations:

    MD_EthSwt_30_Sja1105PQRS_3673:
      Reason:     API is specified by AUTOSAR and isn't allowed to be changed due to compatibility reasons.
      Risk:       No risk.
      Prevention: Covered by code review.
 */

/**********************************************************************************************************************
 *  END OF FILE: EthSwt_30_Sja1105PQRS.c
 *********************************************************************************************************************/

