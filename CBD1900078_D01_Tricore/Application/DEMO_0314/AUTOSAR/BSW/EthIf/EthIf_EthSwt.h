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
/*!        \file  EthIf_EthSwt.h
 *        \brief  EthIf EthSwt public API header
 *
 *      \details  Provides access to the public API of the sub-module EthSwt of EthIf.
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

#if !defined (ETHIF_ETHSWT_H)
# define ETHIF_ETHSWT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_EthSwt_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

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

# define ETHIF_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# if ( ETHIF_GET_PORT_MAC_ADDR_API == STD_ON )                                                                          /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 * EthIf_GetPortMacAddr
 **********************************************************************************************************************/
/*! \brief          Retrieves the switch port a MAC address is assigned to.
 *  \details        Function allows to retrieve the switch port a Ethernet node with the given MAC address is connected
 *                  to.
 *  \param[in]      MacAddrPtr    MAC address to be queried for
 *  \param[out]     SwitchIdxPtr  Pointer to store the switch the port belongs to
 *  \param[out]     PortIdxPtr    Pointer to store the port
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters or no port information found
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         ETHIF_GET_PORT_MAC_ADDR_API
 *  \trace          SPEC-2393873, SPEC-2393874
 *  \trace          DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetPortMacAddr(
  P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA)  MacAddrPtr,
    P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR)   SwitchIdxPtr,
    P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR)   PortIdxPtr);
# endif /* ETHIF_GET_PORT_MAC_ADDR_API */

# if ( ETHIF_GET_ARL_TABLE_API == STD_ON )                                                                              /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 * EthIf_GetArlTable
 **********************************************************************************************************************/
/*! \brief         Retrieves the complete address resolution table.
 *  \details       Function allows to retrieve the valid entries of the address resolution table of a switch
 *                 instance.
 *  \param[in]     SwitchIdx    Switch the ARL table shall be retrieved for
 *  \param[in,out] LenPtr       Pointer to length of the buffer passed:
 *                              [in] - Size of the passed buffer the entries shall be written to
 *                              [out] - Number of entries written into buffer
 *  \param[out]    ArlTablePtr  Pointer to the buffer the data shall be written to
 *  \return        E_OK - success
 *  \return        E_NOT_OK - function has been called with invalid parameters
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        ETHIF_GET_ARL_TABLE_API
 *  \trace         SPEC-2394045, SPEC-2393879
 *  \trace         DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetArlTable(
        uint8                                            SwitchIdx,
  P2VAR(uint32,              AUTOMATIC, ETHIF_APPL_VAR)  LenPtr,
  P2VAR(EthSwt_MacVlanType,  AUTOMATIC, ETHIF_APPL_VAR)  ArlTablePtr);
# endif /* ETHIF_GET_ARL_TABLE_API */

# if ( ETHIF_GET_BUFFER_LEVEL_API == STD_ON )                                                                           /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 * EthIf_GetBufferLevel
 **********************************************************************************************************************/
/*! \brief         Reads the buffer level of the currently used buffer of the switch
 *  \details       Function reads the buffer level of the currently used buffer of the switch.
 *  \param[in]     SwitchIdx             Switch the buffer level shall be retrieved for
 *  \param[out]    SwitchBufferLevelPtr  The interpretation of this value is switch dependent
 *  \return        E_OK - success
 *  \return        E_NOT_OK - function has been called with invalid parameters
 *  \pre           Module and drivers have been initialized
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        ETHIF_GET_BUFFER_LEVEL_API
 *  \trace         SPEC-2394047, SPEC-2393884
 *  \trace         DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetBufferLevel(
        uint8                                               SwitchIdx,
  P2VAR(EthSwt_BufferLevelType, AUTOMATIC, ETHIF_APPL_VAR)  SwitchBufferLevelPtr);
# endif /* ETHIF_GET_BUFFER_LEVEL_API */

# if ( ETHIF_GET_DROP_COUNT_API == STD_ON )                                                                             /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 * EthIf_GetDropCount
 **********************************************************************************************************************/
/*! \brief         Retrieves the drop counts according to the AUTOSAR SWS.
 *  \details       Function allows to retrieve the drop counts specified by the AUTOSAR SWS. Each count is the sum
 *                 of the drop count of all ports.
 *  \param[in]     SwitchIdx       Switch the drop counts shall be retrieved for
 *  \param[in,out] LenPtr          Pointer to the length of the buffer passed:
 *                                 [in] - Size of the passed buffer the drop counts shall be written to
 *                                 [out] - Number of drop counts written into buffer
 *  \param[out]    DropCountPtr    Pointer to the buffer the data shall be written to
 *  \return        E_OK - success
 *  \return        E_NOT_OK - function has been called with invalid parameters
 *  \pre           Module and drivers have been initialized
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        ETHIF_GET_DROP_COUNT_API
 *  \trace         SPEC-2394049, SPEC-2393889
 *  \trace         DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetDropCount(
        uint8                               SwitchIdx,
  P2VAR(uint16, AUTOMATIC, ETHIF_APPL_VAR)  LenPtr,
  P2VAR(uint32, AUTOMATIC, ETHIF_APPL_VAR)  DropCountPtr);
# endif /* ETHIF_GET_DROP_COUNT_API */

# if ( ETHIF_STORE_CONFIG_API == STD_ON )                                                                               /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 * EthIf_StoreConfiguration
 **********************************************************************************************************************/
/*! \brief         Calls EthSwt_StoreConfiguration() API of the related EthSwt-driver.
 *  \details       Function calls the EthSwt_StoreConfiguration() API of the related EthSwt-driver. Behavior
 *                 depends on the implementation of the driver. Commonly the latest MAC/Port table retrieved out of
 *                 the address resolution table of the switch is stored in NV RAM.
 *  \param[in]     SwitchIdx  Switch the configuration shall be stored for
 *  \return        E_OK - success
 *  \return        E_NOT_OK - function has been called with invalid parameters
 *  \pre           Module and drivers have been initialized
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        ETHIF_STORE_CONFIG_API
 *  \trace         SPEC-2394051, SPEC-2393894
 *  \trace         DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_StoreConfiguration(
  uint8  SwitchIdx);
# endif /* ETHIF_STORE_CONFIG_API */

# if ( ETHIF_RESET_CONFIG_API == STD_ON )                                                                               /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 * EthIf_ResetConfiguration
 **********************************************************************************************************************/
/*! \brief         Calls EthSwt_ResetConfiguration() API of the related EthSwt-driver.
 *  \details       Function calls the EthSwt_ResetConfiguration() API of the related EthSwt-driver. Behavior
 *                 depends on the implementation of the driver. Commonly the MAC/Port table previously stored in NV RAM
 *                 triggered by EthIf_StoreConfiguration() is invalidated and switching behavior with regard to MACs
 *                 and VLANs is reset to initial (as defined by static configuration) behavior.
 *  \param[in]     SwitchIdx  Switch the configuration shall be invalidated for
 *  \return        E_OK - success
 *  \return        E_NOT_OK - function has been called with invalid parameters
 *  \pre           Module and drivers have been initialized
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        ETHIF_RESET_CONFIG_API
 *  \trace         SPEC-2394053, SPEC-2393898
 *  \trace         DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_ResetConfiguration(
  uint8  SwitchIdx);
# endif /* ETHIF_RESET_CONFIG_API */

# if ( ETHIF_SWITCH_UPDATE_MCAST_PORT_ASSIGN_API == STD_ON )                                                            /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 * EthIf_SwitchUpdateMCastPortAssignment
 **********************************************************************************************************************/
/*! \brief         Updates the multicast assignment for a specific port.
 *  \details       Function updates the multicast assignment for a specific Ethernet switch port.
 *  \param[in]     SwitchIdx  Index of the EthIf switch
 *  \param[in]     PortIdx    Index of the Ethernet Switch Port
 *  \param[in]     MCastAddr  Pointer to the multicast address
 *  \param[in]     Action     Action that shall be applied:
 *                            ETHSWT_MCAST_PORT_ASSIGN_ACTION_ADD - Request passing of multicast on the port
 *                            ETHSWT_MCAST_PORT_ASSIGN_ACTION_REMOVE - Request removal of multicast on the port
 *  \return        E_OK - success
 *  \return        E_NOT_OK - function has been called with invalid parameters
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        ETHIF_SWITCH_UPDATE_MCAST_PORT_ASSIGN_API
 *  \trace         DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SwitchUpdateMCastPortAssignment(
          uint8                              SwitchIdx,
          uint8                              PortIdx,
  P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA) MCastAddr,
          EthSwt_MCastPortAssignActionType   Action);
# endif /* ETHIF_SWITCH_UPDATE_MCAST_PORT_ASSIGN_API */


# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_19.1 */

#endif /* ETHIF_ETHSWT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_EthSwt.h
 *********************************************************************************************************************/

