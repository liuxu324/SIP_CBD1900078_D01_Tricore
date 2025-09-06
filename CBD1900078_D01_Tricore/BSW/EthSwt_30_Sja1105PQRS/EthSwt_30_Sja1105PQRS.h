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
/*!        \file  EthSwt_30_Sja1105PQRS.h
 *        \brief  Module Header of Ethernet Switch Driver for NXP SJA1105PQRS
 *
 *      \details  The Ethernet Switch Driver allows to configure and influence the operation of the NXP SJA1105PQRS
 *                switch connected to the SPI interface of the Host MCU this driver runs on.
 *                The Module Header provides the global API and data structure prototypes, which are allowed to be
 *                used and accessed by other modules.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Ingo Schroeck                 visink        Vector Informatik GmbH
 *  David Fessler                 visfer        Vector Informatik GmbH
 *  Mark Harsch                   vismha        Vector Informatik GmbH
 *  Benjamin Groebner             visbgr        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  1.00.00   2017-07-18  visink  -             Initial version
 *  2.00.00   2017-11-23  visink  STORYC-3267   STORY-3206 Release of DrvEthSwitch_Sja1105PQRS with ASR 4.2.1 feature
 *                                              set
 *  3.00.00   2017-12-15  visfer  STORYC-3524   STORY-3206 STORY-3398 Cascading support
 *  3.00.01   2018-02-15  visink  STORYC-4345   STORY-4075 Release of DrvEthSwitch_Sja1105PQRS with bug fixes
 *  4.00.00   2018-07-31  vismha  STORYC-5868   Provide possibility to correct the switch clock by an offset
 *            2018-08-17  vismha  STORYC-5869   Provide possibility to correct the switch clock by a rate
 *            2018-09-11  visink  STORYC-6303   Implement AUTOSAR API with basic ingress and egress mirroring
 *            2018-10-22  visink  STORYC-6306   Implement core part of NvM save and restore of mirror configuration
 *            2018-11-06  visink  STORYC-6840   Change type of RateRatio parameter of EthSwt_SetCorrectionTime to float64
 *            2018-11-13  visink  STORYC-5872   Provide possibility to start/stop the Qbv scheduling
 *  5.00.00   2019-01-11  visbgr  ESCAN00101756 Compiler warning: DiabData - int to unsigned short type conversion
 *                                ESCAN00101567 Static variable in LL_ProvideSpiTransactionBuffer used
 *  5.00.01   2019-03-04  visink  ESCAN00102221 Missing type definitions and wrong compiler abstraction macro usage lead to compilation errors
 *********************************************************************************************************************/

#ifndef ETHSWT_30_SJA1105PQRS_H
#define ETHSWT_30_SJA1105PQRS_H

/* PRQA S 779,777 IDENTIFIER_DIFFER */ /* MD_EthSwt_30_Sja1105PQRS_5.1 */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "EthSwt_30_Sja1105PQRS_Types.h"
#include "EthSwt_30_Sja1105PQRS_Cfg.h"
#include "EthSwt_30_Sja1105PQRS_Mgmt.h"
#include "EthSwt_30_Sja1105PQRS_Time.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Vendor and module identification */
#define ETHSWT_30_SJA1105PQRS_VENDOR_ID                                   (30U)
#define ETHSWT_30_SJA1105PQRS_MODULE_ID                                   (89U)

/* AUTOSAR Software specification version information */
#define ETHSWT_30_SJA1105PQRS_AR_RELEASE_MAJOR_VERSION                    (0x04U)
#define ETHSWT_30_SJA1105PQRS_AR_RELEASE_MINOR_VERSION                    (0x02U)
#define ETHSWT_30_SJA1105PQRS_AR_RELEASE_REVISION_VERSION                 (0x01U)

/* ----- Component version information ----- */
#define ETHSWT_30_SJA1105PQRS_SW_MAJOR_VERSION                            (0x05U)
#define ETHSWT_30_SJA1105PQRS_SW_MINOR_VERSION                            (0x00U)
#define ETHSWT_30_SJA1105PQRS_SW_PATCH_VERSION                            (0x01U)

/* ----- Invalid Instance ID ----- */
/*! Invalid Instance ID: Used on Det call if none or invalid Switch index (representing the instance) is passed
 *  during API call
 */
#define ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID                             (0xFFU)

/* ----- API service IDs ----- */
/*!< Service ID: EthSwt_30_Sja1105PQRS_Init() */
#define ETHSWT_30_SJA1105PQRS_SID_INIT                                    (0x00U)
/*!< Service ID: EthSwt_30_Sja1105PQRS_SwitchInit() */
#define ETHSWT_30_SJA1105PQRS_SID_SWITCH_INIT                             (0x01U)
/*!< Service ID: EthSwt_30_Sja1105PQRS_SetSwitchPortMode() */
#define ETHSWT_30_SJA1105PQRS_SID_SET_SWITCH_PORT_MODE                    (0x02U)
/*!< Service ID: EthSwt_30_Sja1105PQRS_GetSwitchPortMode() */
#define ETHSWT_30_SJA1105PQRS_SID_GET_SWITCH_PORT_MODE                    (0x03U)
/*!< Service ID: EthSwt_30_Sja1105PQRS_StartSwitchPortAutoNegotiation() */
#define ETHSWT_30_SJA1105PQRS_SID_START_SWITCH_PORT_AUTO_NEGOTIATION      (0x04U)
/*!< Service ID: EthSwt_30_Sja1105PQRS_GetLinkState() */
#define ETHSWT_30_SJA1105PQRS_SID_GET_LINK_STATE                          (0x05U)
/*!< Service ID: EthSwt_30_Sja1105PQRS_GetBaudRate() */
#define ETHSWT_30_SJA1105PQRS_SID_GET_BAUD_RATE                           (0x06U)
/*!< Service ID: EthSwt_30_Sja1105PQRS_GetDuplexMode() */
#define ETHSWT_30_SJA1105PQRS_SID_GET_DUPLEX_MODE                         (0x07U)
/*!< Service ID: EthSwt_30_Sja1105PQRS_GetPortMacAddr() */
#define ETHSWT_30_SJA1105PQRS_SID_GET_PORT_MAC_ADDR                       (0x08U)
/*!< Service ID: EthSwt_30_Sja1105PQRS_GetArlTable() */
#define ETHSWT_30_SJA1105PQRS_SID_GET_ARL_TABLE                           (0x09U)
/*!< Service ID: EthSwt_30_Sja1105PQRS_GetBufferLevel() */
#define ETHSWT_30_SJA1105PQRS_SID_GET_BUFFER_LEVEL                        (0x0AU)
/*!< Service ID: EthSwt_30_Sja1105PQRS_GetDropCount() */
#define ETHSWT_30_SJA1105PQRS_SID_GET_DROP_COUNT                          (0x0BU)
/*!< Service ID: EthSwt_30_Sja1105PQRS_EnableVlan() */
#define ETHSWT_30_SJA1105PQRS_SID_ENABLE_VLAN                             (0x0CU)
/*!< Service ID: EthSwt_30_Sja1105PQRS_StoreConfiguration() */
#define ETHSWT_30_SJA1105PQRS_SID_STORE_CONFIGURATION                     (0x0DU)
/*!< Service ID: EthSwt_30_Sja1105PQRS_ResetConfiguration() */
#define ETHSWT_30_SJA1105PQRS_SID_RESET_CONFIGURATION                     (0x0EU)
/*!< Service ID: EthSwt_30_Sja1105PQRS_NvmSingleBlockCallback() */
#define ETHSWT_30_SJA1105PQRS_SID_NVM_SINGLE_BLOCK_CALLBACK               (0x0FU)
/*!< Service ID: EthSwt_30_Sja1105PQRS_MainFunction() */
#define ETHSWT_30_SJA1105PQRS_SID_MAIN_FUNCTION                           (0x10U)
/*!< Service ID: EthSwt_30_Sja1105PQRS_GetVersionInfo() */
#define ETHSWT_30_SJA1105PQRS_SID_GET_VERSION_INFO                        (0x11U)
/*!< Service ID: EthSwt_30_Sja1105PQRS_SetMacLearningMode() */
#define ETHSWT_30_SJA1105PQRS_SID_SET_MAC_LEARNING_MODE                   (0x12U)
/*!< Service ID: EthSwt_30_Sja1105PQRS_GetMacLearningMode() */
#define ETHSWT_30_SJA1105PQRS_SID_GET_MAC_LEARNING_MODE                   (0x13U)
/*!< Service ID: EthSwt_30_Sja1105PQRS_GetEtherStats() */
#define ETHSWT_30_SJA1105PQRS_SID_GET_ETHER_STATS                         (0x14U)
/*!< Service ID EthSwt_30_Sja1105PQRS_SetMirrorFilterMode() */
# define ETHSWT_30_SJA1105PQRS_UPDATE_MCAS_PORT_ASSIGNMENT                (0x23U)
/*!< Service ID: EthSwt_30_Sja1105PQRS_GetSwitchReg() */
#define ETHSWT_30_SJA1105PQRS_SID_GET_SWITCH_REG                          (0x30U)
/*!< Service ID: EthSwt_30_Sja1105PQRS_SetSwitchReg() */
#define ETHSWT_30_SJA1105PQRS_SID_SET_SWITCH_REG                          (0x31U)
/*!< Service ID: EthSwt_30_Sja1105PQRS_ReadTrcvRegister() */
#define ETHSWT_30_SJA1105PQRS_SID_READ_TRCV_REGISTER                      (0x32U)
/*!< Service ID: EthSwt_30_Sja1105PQRS_WriteTrcvRegister() */
#define ETHSWT_30_SJA1105PQRS_SID_WRITE_TRCV_REGISTER                     (0x33U)
/*!< Service ID: EthSwt_30_Sja1105PQRS_VSwitchInit() */
#define ETHSWT_30_SJA1105PQRS_SID_VSWITCH_INIT                            (0x40U)

/* ----- Error codes ----- */
/*! Error code: No error occurred during API processing */
# define ETHSWT_30_SJA1105PQRS_E_NO_ERROR                                 (0x00U)
/*! Error code: API called with invalid switch index  */
#define ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX                            (0x01U)
/*! Error code: API called although EthSwt module was not initialized  */
#define ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED                           (0x02U)
/*! Error code: API called with invalid pointer  */
#define ETHSWT_30_SJA1105PQRS_E_INV_POINTER                               (0x03U)
/*! Error code: API called although module already initialized  */
#define ETHSWT_30_SJA1105PQRS_E_ALREADY_INITIALIZED                       (0x04U)
/*! Error code: Invalid API call by other module  */
#define ETHSWT_30_SJA1105PQRS_E_INV_API                                   (0x05U)
/*! Error code: API called with invalid switch port index  */
#define ETHSWT_30_SJA1105PQRS_E_INV_SWITCHPORT_IDX                        (0x06U)
/*! Error code: *_INIT_* variables not initialized  */
#define ETHSWT_30_SJA1105PQRS_E_MEMORY_NOT_INITIALIZED                    (0x07U)
/*! Error code: API called with invalid parameter value */
#define ETHSWT_30_SJA1105PQRS_E_INV_PARAM                                 (0x08U)
/*! Error code: API operation failed */
#define ETHSWT_30_SJA1105PQRS_E_OP_FAILED                                 (0x09U)
/*! Error code: Internal Error */
# define ETHSWT_30_SJA1105PQRS_E_INTERNAL_ERROR                           (0xF0U)

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

/* Service functions */
/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_InitMemory()
 **********************************************************************************************************************/
/*! \brief         Function for *_INIT_*-variable initialization
 *  \details       Service to initialize module global variables at power up. This function can be used to initialize
 *                 the variables in *_INIT_* sections in case they are not initialized by the startup code.
 *  \pre           Module must not be initialized
 *  \pre           Function shall be called from task level
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_InitMemory(void);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_Init()
 **********************************************************************************************************************/
/*! \brief         Initialization function of the EthSwt.
 *  \details       This function initializes the module EthSwt. It initializes all variables and and sets the module
 *                 state to initialized.
 *  \param[in]     ConfigPtr               Configuration structure for initializing the module
 *  \pre           Interrupts have to be disabled.
 *  \pre           The module has to be uninitialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \note          Specification of module initialization
 **********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_Init(
    ETHSWT_P2CONST(EthSwt_ConfigType, SJA1105PQRS)  ConfigPtr );

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_SwitchInit()
 **********************************************************************************************************************/
/*! \brief         Configuration function of an EthSwt instance.
 *  \details       This function resets and configures the switch instance. Configuration of ingress-, egress-behavior,
 *                 writing of static address resolution table entries and internal ports setup.
 *  \param[in]     SwitchIdx       Index of the switch instance to be initialized
 *  \return        E_NOT_OK        Switch instance initialization not successful.\n
 *                 E_OK            Switch instance initialization successful.
 *  \pre           The module has to be initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \note          AUTOSAR specifies the function EthSwt_SwitchInit() to be called synchronously. However the
 *                 initialization process does take as much time to hurt the timings of task activation.
 *                 Therefore this function shifts the processing of the initialization into an preemtable idle task.
 *  \trace         DSGN-EthSwt22750
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_SwitchInit(
    EthSwt_SwitchIdxType  SwitchIdx);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_VSwitchInit()
 **********************************************************************************************************************/
/*! \brief         Configuration function of an EthSwt instance.
 *  \details       This function resets and configures the switch instance. Configuration of ingress-, egress-behavior,
 *                 writing of static address resolution table entries and internal ports setup.
 *  \param[in]     SwitchIdx       Index of the switch instance to be initialized
 *  \return        E_NOT_OK        Switch instance initialization not successful.\n
 *                 E_OK            Switch instance initialization successful.
 *  \pre           The module has to be initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \note          AUTOSAR specifies the function EthSwt_SwitchInit() to be called synchronously. However the
 *                 initialization process does take as much time to hurt the timings of task activation.
 *                 Therefore this function shifts the processing of the initialization into an preemtable idle task.
 *  \trace         DSGN-EthSwt22750
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_VSwitchInit(
    EthSwt_SwitchIdxType  SwitchIdx);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_SetSwitchPortMode()
 **********************************************************************************************************************/
/*! \brief         Mode change function for a switch port.
 *  \details       This function allows to change the mode of a switch port. It either redirects the call to the
 *                 corresponding Transceiver module (for external configured ports) or applies the change by itself.
 *  \param[in]     SwitchIdx       Index of the switch instance
 *  \param[in]     PortIdx         Index of the port
 *  \param[in]     PortMode        Mode that shall be applied\n
 *                                 ETHTRCV_MODE_DOWN:    Disable communication ability on port\n
 *                                 ETHTRCV_MODE_ACTIVE:  Enable communication ability on port
 *  \return        E_NOT_OK        Mode change not successful\n
 *                 E_OK            Mode change successful
 *  \pre           Switch instance has to be initialized by EthSwt_SwitchInit().
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_SetSwitchPortMode(
    EthSwt_SwitchIdxType  SwitchIdx,
    EthSwt_PortIdxType    PortIdx,
    EthTrcv_ModeType      PortMode);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetSwitchPortMode()
 **********************************************************************************************************************/
/*! \brief         Mode retrieval function for a switch port.
 *  \details       This function allows retrieving the mode of a switch port. It either redirects the call to the
 *                 corresponding Transceiver module (for external configured ports) or retrieves the mode by itself.
 *  \param[in]     SwitchIdx       Index of the switch instance
 *  \param[in]     PortIdx         Index of the port
 *  \param[out]    ModePtr         Retrieved Mode\n
 *                                 ETHTRCV_MODE_DOWN:    Communication ability on port is disabled\n
 *                                 ETHTRCV_MODE_ACTIVE:  Communication ability on port is enabled
 *  \return        E_NOT_OK        Mode retrieval not successful\n
 *                 E_OK            Mode retrieval successful
 *  \pre           Switch instance has to be initialized by EthSwt_SwitchInit().
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_GetSwitchPortMode(
                 EthSwt_SwitchIdxType            SwitchIdx,
                 EthSwt_PortIdxType              PortIdx,
    ETHSWT_P2VAR(EthTrcv_ModeType, SJA1105PQRS)  ModePtr );

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_StartSwitchPortAutoNegotiation()
 **********************************************************************************************************************/
/*! \brief         Trigger Auto Negotiation function for a switch port.
 *  \details       This function allows triggering the Auto Negotiation on a switch port. It either redirects the call
 *                 to the corresponding Transceiver module (for external configured ports) or triggers the Auto
 *                 Negotiation by itself.
 *  \param[in]     SwitchIdx       Index of the switch instance
 *  \param[in]     PortIdx         Index of the port
 *  \return        E_NOT_OK        Auto Negotiation triggering not successful\n
 *                 E_OK            Auto Negotiation triggering successful
 *  \pre           Switch instance has to be initialized by EthSwt_SwitchInit().
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_StartSwitchPortAutoNegotiation(
    EthSwt_SwitchIdxType  SwitchIdx,
    EthSwt_PortIdxType    PortIdx);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetLinkState()
 **********************************************************************************************************************/
/*! \brief         Link State retrieval function for a switch port.
 *  \details       This function allows retrieving the Link State of a switch port. It either redirects the call to
 *                 the corresponding Transceiver module (for external configured ports) or retrieves the Link State by
 *                 itself.
 *  \param[in]     SwitchIdx       Index of the switch instance
 *  \param[in]     PortIdx         Index of the port
 *  \param[out]    LinkStatePtr    Retrieved Link State\n
 *                                 ETHTRCV_LINK_STATE_DOWN:    No link established on port\n
 *                                 ETHTRCV_LINK_STATE_ACTIVE:  Link established on port
 *  \return        E_NOT_OK        Link State retrieval not successful\n
 *                 E_OK            Link State retrieval successful
 *  \pre           Switch instance has to be initialized by EthSwt_SwitchInit().
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_GetLinkState(
                 EthSwt_SwitchIdxType                 SwitchIdx,
                 EthSwt_PortIdxType                   PortIdx,
    ETHSWT_P2VAR(EthTrcv_LinkStateType, SJA1105PQRS)  LinkStatePtr );

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetBaudRate()
 **********************************************************************************************************************/
/*! \brief         Baud Rate retrieval function for a switch port.
 *  \details       This function allows to retrieve the Baud Rate of a switch port. It either redirects the call to
 *                 the corresponding Transceiver module (for external configured ports) or retrieves the Baud Rate by
 *                 itself.
 *  \param[in]     SwitchIdx       Index of the switch instance
 *  \param[in]     PortIdx         Index of the port
 *  \param[out]    BaudRatePtr     Retrieved Baud Rate\n
 *                                 ETHTRCV_BAUD_RATE_10MBIT:   10 MBit Baud Rate\n
 *                                 ETHTRCV_BAUD_RATE_100MBIT:  100 MBit Baud Rate\n
 *                                 ETHTRCV_BAUD_RATE_1000MBIT: 1000 MBit Baud Rate
 *  \return        E_NOT_OK        Baud Rate retrieval not successful\n
 *                 E_OK            Baud Rate retrieval successful
 *  \pre           Switch instance has to be initialized by EthSwt_SwitchInit().
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_GetBaudRate(
                 EthSwt_SwitchIdxType                SwitchIdx,
                 EthSwt_PortIdxType                  PortIdx,
    ETHSWT_P2VAR(EthTrcv_BaudRateType, SJA1105PQRS)  BaudRatePtr );

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetDuplexMode()
 **********************************************************************************************************************/
/*! \brief         Duplex Mode retrieval function for a switch port.
 *  \details       This function allows retrieving the Duplex Mode of a switch port. It either redirects the call to
 *                 the corresponding Transceiver module (for external configured ports) or retrieves the Duplex Mode by
 *                 itself.
 *  \param[in]     SwitchIdx       Index of the switch instance
 *  \param[in]     PortIdx         Index of the port
 *  \param[out]    DuplexModePtr   Retrieved Duplex Mode\n
 *                                 ETHTRCV_DUPLEX_MODE_HALF: Half Duplex Mode\n
 *                                 ETHTRCV_DUPLEX_MODE_FULL: Full Duplex Mode
 *  \return        E_NOT_OK        Duplex Mode retrieval not successful\n
 *                 E_OK            Duplex Mode retrieval successful
 *  \pre           Switch instance has to be initialized by EthSwt_SwitchInit().
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_GetDuplexMode(
                 EthSwt_SwitchIdxType                  SwitchIdx,
                 EthSwt_PortIdxType                    PortIdx,
    ETHSWT_P2VAR(EthTrcv_DuplexModeType, SJA1105PQRS)  DuplexModePtr );


#if ( ETHSWT_30_SJA1105PQRS_GET_PORT_MAC_ADDR_API_ENABLED == STD_ON)
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetPortMacAddr()
 **********************************************************************************************************************/
/*! \brief         Function retrieves the switch instance and port a MAC address is assigned to.
 *  \details       This function allows retrieving the switch instance and port an Ethernet frame with a source MAC
 *                 address matching the given MAC address was received on.
 *  \param[in]     MacAddrPtr      MAC address to be queried
 *  \param[out]    SwitchIdxPtr    Index of the switch instance the corresponding frame was received on
 *  \param[out]    PortIdxPtr      Index of the port the corresponding frame was received on
 *  \return        E_NOT_OK        Retrieval not successful\n
 *                 E_OK            Retrieval successful
 *  \pre           Switch instance has to be initialized by EthSwt_SwitchInit().
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_GetPortMacAddr(
    ETHSWT_P2CONST(uint8,                SJA1105PQRS)  MacAddrPtr,
      ETHSWT_P2VAR(EthSwt_SwitchIdxType, SJA1105PQRS)  SwitchIdxPtr,
      ETHSWT_P2VAR(EthSwt_PortIdxType,   SJA1105PQRS)  PortIdxPtr );
#endif /* ETHSWT_30_SJA1105PQRS_GET_PORT_MAC_ADDR_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_GET_ARL_TABLE_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetArlTable()
 **********************************************************************************************************************/
/*! \brief         Function retrieves the complete address resolution table.
 *  \details       This function allows retrieving the valid entries of the address resolution table of a switch
 *                 instance.
 *  \param[in]     SwitchIdx       Index of the switch instance
 *  \param[in,out] LenPtr          in:  Size of the passed buffer the entries shall be written to\n
 *                                 out: Number of entries written into buffer
 *  \param[out]    ArlTablePtr     Pointer to the buffer the data shall be written to
 *  \return        E_NOT_OK        Retrieval not successful\n
 *                 E_OK            Retrieval successful
 *  \pre           Switch instance has to be initialized by EthSwt_SwitchInit().
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_GetArlTable(
                 EthSwt_SwitchIdxType                SwitchIdx,
    ETHSWT_P2VAR(uint32,               SJA1105PQRS)  LenPtr,
    ETHSWT_P2VAR(EthSwt_MacVlanType,   SJA1105PQRS)  ArlTablePtr );
#endif /* ETHSWT_30_SJA1105PQRS_GET_ARL_TABLE_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_GET_BUFFER_LEVEL_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetBufferLevel()
 **********************************************************************************************************************/
/*! \brief         Function retrieves current buffer occupation.
 *  \details       This function allows retrieving the buffer occupation of a switch instance.
 *  \param[in]     SwitchIdx       Index of the switch instance
 *  \param[out]    BufferLevelPtr  Level of buffer occupation in bytes
 *  \return        E_NOT_OK        Retrieval not successful\n
 *                 E_OK            Retrieval successful
 *  \pre           Switch instance has to be initialized by EthSwt_SwitchInit().
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \note          Not supported by hardware. Will always return E_NOT_OK.
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_GetBufferLevel(
                 EthSwt_SwitchIdxType                  SwitchIdx,
    ETHSWT_P2VAR(EthSwt_BufferLevelType, SJA1105PQRS)  BufferLevelPtr );
#endif /* ETHSWT_30_SJA1105PQRS_GET_BUFFER_LEVEL_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_GET_DROP_COUNT_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetDropCount()
 **********************************************************************************************************************/
/*! \brief         Function retrieves the drop counts according to the AUTOSAR SWS.
 *  \details       This function allows retrieving the drop counts specified by the AUTOSAR SWS. Each count is the sum
 *                 of the drop count of all ports.
 *  \param[in]     SwitchIdx       Index of the switch instance
 *  \param[in,out] LenPtr          in:  Size of the passed buffer the drop counts shall be written to
 *                                 out: Number of drop counts written into buffer
 *  \param[out]    DropCountPtr    Pointer to the buffer the data shall be written to
 *  \return        E_NOT_OK        Retrieval not successful\n
 *                 E_OK            Retrieval successful
 *  \pre           Switch instance has to be initialized by EthSwt_SwitchInit().
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \note          No hardware specific drop counts are written.
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_GetDropCount(
                 EthSwt_SwitchIdxType               SwitchIdx,
    ETHSWT_P2VAR(uint16,              SJA1105PQRS)  LenPtr,
    ETHSWT_P2VAR(uint32,              SJA1105PQRS)  DropCountPtr );
#endif /* ETHSWT_30_SJA1105PQRS_GET_DROP_COUNT_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_GET_ETHER_STATS_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetEtherStats()
 **********************************************************************************************************************/
/*! \brief         Function retrieves the Ethernet statistic counters according to the AUTOSAR SWS.
 *  \details       This function allows retrieving the Ethernet statistic counters specified by the AUTOSAR SWS for one
 *                 Switch Port.
 *  \param[in]     SwitchIdx       Index of the switch instance
 *  \param[in]     SwitchPortIdx   Index of the Port
 *  \param[out]    etherStats      Pointer to the buffer the data shall be written to
 *  \return        E_NOT_OK        Retrieval not successful\n
 *                 E_OK            Retrieval successful
 *  \pre           Switch instance has to be initialized by EthSwt_SwitchInit().
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \note          Statistic counters that are not available contain the max value for the uint32 data type.
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_GetEtherStats(
                 EthSwt_SwitchIdxType               SwitchIdx,
                 EthSwt_PortIdxType                 SwitchPortIdx,
    ETHSWT_P2VAR(uint32,              SJA1105PQRS)  EtherStats );
#endif /* ETHSWT_30_SJA1105PQRS_GET_ETHER_STATS_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_GET_SWITCH_REG_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetSwitchReg()
 **********************************************************************************************************************/
/*! \brief         Function retrieves the value of a switch register.
 *  \details       This function allows retrieving the value of a switch register.
 *  \param[in]     SwitchIdx       Index of the switch instance
 *  \param[in]     page               Addressed memory page (not applicable for SJA1105PQRS)
 *  \param[in]     registerAddr       Addressed register
 *  \param[out]    registerContent    Content of the register read
 *  \return        E_NOT_OK           Retrieval not successful\n
 *                 E_OK               Retrieval successful
 *  \pre           Switch instance has to be initialized by EthSwt_SwitchInit().
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \note          SJA1105PQRS's memory space isn't divided into pages. Therefore the page parameter is unused.
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_GetSwitchReg(
                 EthSwt_SwitchIdxType               SwitchIdx,
                 uint32                             page,
                 uint32                             registerAddr,
    ETHSWT_P2VAR(uint32,              SJA1105PQRS)  registerContent );
#endif /* ETHSWT_30_SJA1105PQRS_GET_SWITCH_REG_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_SET_SWITCH_REG_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_SetSwitchReg()
 **********************************************************************************************************************/
/*! \brief         Function sets the value of a switch register.
 *  \details       This function allows setting the value of a switch register.
 *  \param[in]     SwitchIdx          Index of the switch instance
 *  \param[in]     page               Addressed memory page (not applicable for SJA1105PQRS)
 *  \param[in]     registerAddr       Addressed register
 *  \param[in]     registerContent    Content that shall be written to the register
 *  \return        E_NOT_OK           Retrieval not successful\n
 *                 E_OK               Retrieval successful
 *  \pre           Switch instance has to be initialized by EthSwt_SwitchInit().
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \note          SJA1105PQRS's memory space isn't divided into pages. Therefore the page parameter is unused.
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_SetSwitchReg(
    EthSwt_SwitchIdxType  SwitchIdx,
    uint32                page,
    uint32                registerAddr,
    uint32                registerContent );
#endif /* ETHSWT_30_SJA1105PQRS_SET_SWITCH_REG_API_ENABLED */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_ReadTrcvRegister()
 **********************************************************************************************************************/
/*! \brief         Hardware abstracted read access to transceiver related registers.
 *  \details       This function allows a Ethernet Transceiver module to gain read access to its registers in an hardware
 *                 abstracted manner.
 *  \param[in]     SwitchIdx   Index of switch instance
 *  \param[in]     PortIdx     Index of port
 *  \param[in]     RegIdx      Index of register (MII addressing)
 *  \param[out]    RegValPtr   Value read from register
 *  \pre           -
 *  \return        E_NOT_OK    Register read was successful\n
 *                 E_OK        Register read was not successful
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_ReadTrcvRegister(
    EthSwt_SwitchIdxType  SwitchIdx,
    EthSwt_PortIdxType    PortIdx,
    uint8                 RegIdx,
    uint16               *RegValPtr);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_WriteTrcvRegister()
 **********************************************************************************************************************/
/*! \brief         Hardware abstracted write access to transceiver related registers.
 *  \details       This function allows a Ethernet Transceiver module to gain write access to its registers in an
 *                 hardware abstracted manner.
 *  \param[in]     SwitchIdx   Index of switch instance
 *  \param[in]     PortIdx     Index of port
 *  \param[in]     RegIdx      Index of register
 *  \param[in]     RegVal      Value to be written to register
 *  \return        E_NOT_OK    Register write was successful\n
 *                 E_OK        Register write was not successful
 *  \pre           Switch instance has to be initialized by EthSwt_Init().
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_WriteTrcvRegister(
    EthSwt_SwitchIdxType  SwitchIdx,
    EthSwt_PortIdxType    PortIdx,
    uint8                 RegIdx,
    uint16                RegVal);

#if ( ETHSWT_30_SJA1105PQRS_ENABLE_VLAN_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_EnableVlan()
 **********************************************************************************************************************/
/*! \brief         Function allows changing the VLAN forwarding behavior of a port.
 *  \details       This function allows changing the VLAN forwarding behavior of a port. The VLAN forwarding for the
 *                 corresponding VLAN can either be disable or enabled.
 *  \param[in]     SwitchIdx       Index of the switch instance
 *  \param[in]     PortIdx         Index of the port
 *  \param[in]     VlanId          ID of VLAN the rule shall be applied for
 *  \param[in]     Enable          Behavior that shall be applied\n
 *                                 FALS: VLAN shall not be forwarded\n
 *                                 TRUE: VLAN shall be forwarded
 *  \return        E_NOT_OK        Rule appliance not successful\n
 *                 E_OK            Rule appliance successful
 *  \pre           Switch instance has to be initialized by EthSwt_SwitchInit().
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_EnableVlan(
    EthSwt_SwitchIdxType  SwitchIdx,
    EthSwt_PortIdxType    PortIdx,
    uint16                VlanId,
    boolean               Enable);
#endif /* ETHSWT_30_SJA1105PQRS_ENABLE_VLAN_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_StoreConfiguration()
 **********************************************************************************************************************/
/*! \brief         Function allows storing the current MAC/Port table in NV RAM.
 *  \details       This function allows storing the current MAC/Port table retrieved out of the address resolution table
 *                 of the switch in the NV Ram.
 *  \param[in]     SwitchIdx       Index of the switch instance
 *  \return        E_NOT_OK        Storage not successful\n
 *                 E_OK            Storage successful
 *  \pre           Switch instance has to be initialized by EthSwt_SwitchInit().
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \note          Concurrent calls will lead to returning E_NOT_OK until the async storage process of NvM has finished.
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_StoreConfiguration(
    EthSwt_SwitchIdxType SwitchIdx);
#endif /* ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_ResetConfiguration()
 **********************************************************************************************************************/
/*! \brief         Function resets learned MAC port mapping table in NV RAM.
 *  \details       The function resets the NV RAM used to store the learned MAC to port mapping table.
 *  \param[in]     SwitchIdx       Index of the switch instance
 *  \return        E_NOT_OK        Reset not successful\n
 *                 E_OK            Reset successful
 *  \pre           Switch instance has to be initialized by EthSwt_SwitchInit().
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \note          Concurrent calls will lead to returning E_NOT_OK until the async storage process of NvM has finished.
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_ResetConfiguration(
    EthSwt_SwitchIdxType  SwitchIdx );
#endif /* ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_SET_MAC_LEARNING_MODE_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_SetMacLearningMode()
 **********************************************************************************************************************/
/*! \brief         Function allows influencing the MAC learning behavior of the switch.
 *  \details       This function allows changing the MAC learning mode of the switch.
 *  \param[in]     SwitchIdx       Index of the switch instance
 *  \param[in]     PortIdx         Index of the port
 *  \param[in]     MacLearningMode Learning Mode to be applied\n
 *                                 ETHSWT_MACLEARNING_HWDISABLED:  Disables Hardware MAC learning\n
 *                                 ETHSWT_MACLEARNING_HWENABLED:   Enables Hardware MAC learning\n
 *                                 ETHSWT_MACLEARNING_SWENABLED:   Enables Software MAC learning (disables Hardware MAC
 *                                                                 learning)
 *  \return        E_NOT_OK        MAC learning mode change not successful\n
 *                 E_OK            MAC learning mode change successful
 *  \pre           Switch instance has to be initialized by EthSwt_SwitchInit().
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \note          Enabling Software MAC learning by passing ETHSWT_MACLEARNING_SWENABLED isn't supported!
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_SetMacLearningMode(
    EthSwt_SwitchIdxType    SwitchIdx,
    EthSwt_PortIdxType      PortIdx,
    EthSwt_MacLearningType  MacLearningMode );
#endif /* ETHSWT_30_SJA1105PQRS_SET_MAC_LEARNING_MODE_API_ENABLED */

#if ( ETHSWT_30_SJA1105PQRS_GET_MAC_LEARNING_MODE_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetMacLearningMode()
 **********************************************************************************************************************/
/*! \brief         Function allows retrieving the MAC learning behavior of the switch.
 *  \details       This function allows retrieve the MAC learning mode of the switch.
 *  \param[in]     SwitchIdx          Index of the switch instance
 *  \param[in]     PortIdx            Index of the port
 *  \param[out]    MacLearningModePtr Learning Mode retrieved\n
 *                                    ETHSWT_MACLEARNING_HWDISABLED:  Hardware MAC learning disabled\n
 *                                    ETHSWT_MACLEARNING_HWENABLED:   Hardware MAC learning enabled\n
 *                                    ETHSWT_MACLEARNING_SWENABLED:   Software MAC learning enabled
 *  \return        E_NOT_OK           MAC learning mode retrieval not successful\n
 *                 E_OK               MAC learning mode retrieval successful
 *  \pre           Switch instance has to be initialized by EthSwt_SwitchInit().
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \note          Because setting of ETHSWT_MACLEARNING_SWENABLED isn't supported API will never return this learning
 *                 mode.
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_GetMacLearningMode(
                 EthSwt_SwitchIdxType                  SwitchIdx,
                 EthSwt_PortIdxType                    PortIdx,
    ETHSWT_P2VAR(EthSwt_MacLearningType, SJA1105PQRS)  MacLearningModePtr );
#endif /* ETHSWT_30_SJA1105PQRS_GET_MAC_LEARNING_MODE_API_ENABLED */



#if (    ( ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED == STD_ON )\
      || ( ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED == STD_ON ))
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_NvmSingleBlockCallback()
 **********************************************************************************************************************/
/*! \brief         Callback function to indicate the finish of a NvM job.
 *  \details       This function is called by NvM if a triggered NvM job has finished.
 *  \param[in]     BlockId     ID of the NvM block
 *  \param[in]     JobResult   Result of the NvM job\n
 *                             NVM_REQ_NOT_OK: Job processing finished not successful\n
 *                             NVM_REQ_OK:     Job processing finished successful
 *  \return        E_OK        Always returns E_OK according to SWS_NvM_00368
 *  \pre           Switch instance has to be initialized by EthSwt_SwitchInit().
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_NvmSingleBlockCallback(
    NvM_ServiceIdType      ServiceId,
    NvM_RequestResultType  JobResult);
#endif /* ETHSWT_30_SJA1105PQRS_STORE_CONFIG_API_ENABLED, ETHSWT_30_SJA1105PQRS_RESET_CONFIG_API_ENABLED */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_MainFunction()
 **********************************************************************************************************************/
/*! \brief         Main function of the EthSwt
 *  \details       This function is called periodically and recognizes the events that shall be directed to DEM.
 *  \pre           Switch instance has to be initialized by EthSwt_SwitchInit().
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_MainFunction( void );

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_AsyncProcessingMainFunction()
 **********************************************************************************************************************/
/*! \brief         Main function processing asynchronous tasks
 *  \details       This function is called periodically and processes the asynchronous tasks of the driver.
 *  \pre           Switch instance has to be initialized by EthSwt_SwitchInit().
 *  \context       TASK (Background-/Idle-Task able to preempted by other tasks)
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_AsyncProcessingMainFunction( void );

#if ( ETHSWT_30_SJA1105PQRS_UPDATE_MCAST_PORT_ASSIGN_API_ENABLED == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_UpdateMCastPortAssignment()
 **********************************************************************************************************************/
/*! \brief         This function allows to set the mirror filter mode for ingress/egress traffic on a per switch basis.
 *  \details       -
 *  \param[in]     SwitchIdx         Index of the switch
 *  \param[in]     PortIdx           Index of the switch port
 *  \param[in]     MCastAddr         Pointer to the MAC Multicast Address
 *  \param[in]     Action            Action that shall be applied
 *                                   - ETHSWT_MCAST_PORT_ASSIGN_ACTION_ADD: Request passing of multicast on the port
 *                                   - ETHSWT_MCAST_PORT_ASSIGN_ACTION_REMOVE: Request removal of multicast on the port
 *  \return        E_NOT_OK - Assignment could not be adapted
 *  \return        E_OK - Assignment adapted successfully
 *  \pre           Module is initialized.
 *  \pre           Ethernet switch is initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_UpdateMCastPortAssignment(
                 EthSwt_SwitchIdxType                        SwitchIdx,
                 EthSwt_PortIdxType                          PortIdx,
  ETHSWT_P2CONST(uint8,                           SJA1105PQRS)  MCastAddr,
                 EthSwt_MCastPortAssignActionType            Action);
#endif /* ETHSWT_30_SJA1105PQRS_UPDATE_MCAST_PORT_ASSIGN_API_ENABLED */

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_GetVersionInfo()
 **********************************************************************************************************************/
/*! \brief         Returns the version information
 *  \details       EthSwt_30_Sja1105PQRS_GetVersionInfo() returns version information, vendor ID and AUTOSAR module ID
 *                 of the component. The versions are BCD-coded.
 *  \param[out]    VersionInfoPtr          Pointer to buffer where to store the version information
 *  \pre           Input parameter must not be NULL.
 *  \pre           Function shall be called from task level
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 **********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_GetVersionInfo(
    ETHSWT_P2VAR(Std_VersionInfoType, SJA1105PQRS)  VersionInfoPtr);

/* PRQA L:IDENTIFIER_DIFFER */

#define ETHSWT_30_SJA1105PQRS_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif  /* ETHSWT_30_SJA1105PQRS_H */

/**********************************************************************************************************************
 *  END OF FILE: EthSwt_30_Sja1105PQRS.h
 *********************************************************************************************************************/
