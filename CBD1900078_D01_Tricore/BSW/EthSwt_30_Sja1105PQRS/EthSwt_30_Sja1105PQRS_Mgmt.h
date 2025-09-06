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
/*!        \file  EthSwt_30_Sja1105PQRS_Mgmt.h
 *        \brief  Header file for access to the frame management API
 *
 *      \details  The Ethernet Switch Driver allows to manage special frames (like PTP frames) received at it's ports.
 *                Additionally frames can be adapted with management information to achieve transmission only on
 *                selected ports.
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

#if !defined (ETHSWT_30_SJA1105PQRS_MGMT_H)
#define ETHSWT_30_SJA1105PQRS_MGMT_H

/* PRQA S 779,777 IDENTIFIER_DIFFER */ /* MD_EthSwt_30_Sja1105PQRS_5.1 */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "EthSwt_30_Sja1105PQRS_Types.h"
#include "EthSwt_30_Sja1105PQRS_Cfg.h"
#include "EthSwt_30_Sja1105PQRS_Lcfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* ----- API service IDs ----- */
/*! Service ID: Service ID for internal frame management APIs */
#define ETHSWT_30_SJA1105PQRS_SID_INTERNAL_FRAME_MNGMT_API                  (0xF0U)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct
{
    uint8 reserved;
    uint8 Timestamp0;
    uint8 Timestamp1;
    uint8 Timestamp2;
    uint8 MacDestination1;
    uint8 MacDestination2;
    uint8 SourcePort;
    uint8 SwitchId;
} EthSwt_30_Sja1105PQRS_MetaFrame;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define ETHSWT_30_SJA1105PQRS_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if ( ETHSWT_30_SJA1105PQRS_MANAGEMENT_SUPPORT == STD_ON )

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_MgmtInit
 *********************************************************************************************************************/
/*! \brief          Initializes the frame management related data structures.
 *  \details        -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *  \synchronous    TRUE
 *********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_MgmtInit( void );

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_GetSwitchManagementInstance
 **********************************************************************************************************************/
/*! \brief          Retrieves the switch that uses the given Eth controller as management interface
 *  \details        -
 *  \param[in]      ethCtrlIdx         Eth controller the switch shall be retrieved for
 *  \param[out]     swtCfg             Pointer where the switch configuration of the switch using the Eth controller
 *                                     as management interface shall be stored
 *  \return         E_NOT_OK           no switch using the Eth controller as management interface found
 *  \return         E_OK               switch using the Eth controller as management interface found
 *  \context        ANY
 *  \reentrant      TRUE
 *  \pre            -
 *  \synchronous    TRUE
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetSwitchManagementInstance(
                 uint8                                                                               ethCtrlIdx,
    ETHSWT_P2VAR(ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS), SJA1105PQRS) swtCfg );

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_EthProcessRxFrame
 *********************************************************************************************************************/
/*! \brief          Function inspects the Ethernet frame passed by the data pointer for management information and
 *                  stores it for later use in EthSwt_30_Sja1105PQRS_EthRxFinishedIndication().
 *  \details        -
 *  \param[in]      CtrlIdx            Ethernet Controller index
 *  \param[in,out]  DataPtr            [in]:  Pointer to the position of the EtherType of a common Ethernet frame
 *                                     [out]: Pointer to the position of the EtherType in the management frame
 *  \param[in,out]  LengthPtr          [in]:  Pointer to the length of the frame received
 *                                     [out]: Pointer to the length decreased by the management information length
 *  \param[out]     IsMgmtFrameOnlyPtr Information about the kind of frame
 *                                     FALSE: Frame is not only for management purpose but also for normal
 *                                            communication.
 *                                     TRUE:  Frame is only for management purpose and MUST not be processed in
 *                                            common receive process.
 *  \return         E_OK               Frame successfully processed.
 *  \return         E_NOT_OK           Frame processing failed.
 *  \context        ANY
 *  \reentrant      TRUE
 *  \pre            -
 *  \synchronous    TRUE
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_EthRxProcessFrame(
                 uint8                                          CtrlIdx,
    ETHSWT_P2VAR(ETHSWT_P2VAR(uint8, SJA1105PQRS), SJA1105PQRS) DataPtr,
    ETHSWT_P2VAR(uint16,                           SJA1105PQRS) LengthPtr,
    ETHSWT_P2VAR(boolean,                          SJA1105PQRS) IsMgmtFrameOnlyPtr);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_EthRxFinishedIndication
 *********************************************************************************************************************/
/*! \brief          Indication for a finished receive process for a specific Ethernet frame, which results in providing
 *                  the management information retrieved during EthSwt_30_Sja1105PQRS_EthProcessRxFrame() to the EthIf
 *                  if frame received needs special treatment.
 *  \details        -
 *  \param[in]      CtrlIdx            Ethernet Controller index
 *  \context        ANY
 *  \reentrant      TRUE
 *  \pre            -
 *  \synchronous    TRUE
 *********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_EthRxFinishedIndication(
                 uint8                                          CtrlIdx,
    ETHSWT_P2VAR(ETHSWT_P2VAR(uint8, SJA1105PQRS), SJA1105PQRS) DataPtr);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_EthTxAdaptBufferLength
 *********************************************************************************************************************/
/*! \brief          Modifies the buffer length to be able to insert management information (No modification done for
 *                  Sja1105PQRS).
 *  \details        -
 *  \param[in,out]  LengthPtr          [in]:  Pointer to the length of the buffer without management information.
 *                                     [out]: Pointer to the modified length needed for buffer and management
 *                                            information.
 *  \return         E_OK               Buffer length adaption successful.
 *  \return         E_NOT_OK           Buffer length adaption failed.
 *  \context        ANY
 *  \reentrant      TRUE
 *  \pre            -
 *  \synchronous    TRUE
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_EthTxAdaptBufferLength(
    ETHSWT_P2VAR(uint16, SJA1105PQRS) LengthPtr );

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_EthTxPrepareFrame
 *********************************************************************************************************************/
/*! \brief          Prepares a the Ethernet frame for common Ethernet communication (frame shall be handled by switch
 *                  according to the common address resolution behavior) and stores the information for processing of
 *                  EthSwt_30_Sja1105PQRS_EthTxFinishedIndication().
 *  \details        -
 *  \param[in]      CtrlIdx            Ethernet Controller index
 *  \param[in]      BufIdx             Ethernet Tx Buffer index
 *  \param[in,out]  DataPtr            [in]:  Pointer to the position of the EtherType of a common Ethernet frame
 *                                     [out]: Pointer to the position of the EtherType in the management frame
 *  \param[in,out]  LengthPtr          [in]:  Pointer to the length of the buffer without management information.
 *                                     [out]: Pointer to the modified length needed for buffer and management
 *                                            information.
 *  \return         E_OK               Preparation successful.
 *  \return         E_NOT_OK           Preparation failed.
 *  \context        ANY
 *  \reentrant      TRUE
 *  \pre            -
 *  \synchronous    TRUE
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_EthTxPrepareFrame(
                 uint8                                          CtrlIdx,
                 uint8                                          BufIdx,
                 Eth_FrameIdType                                FrameId,
    ETHSWT_P2VAR(ETHSWT_P2VAR(uint8, SJA1105PQRS), SJA1105PQRS) DataPtr,
    ETHSWT_P2VAR(uint16,                           SJA1105PQRS) LengthPtr );

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_EthTxProcessFrame
 *********************************************************************************************************************/
/*! \brief          Function sets management information for the Ethernet frame.
 *  \details        -
 *  \param[in]      CtrlIdx            Ethernet Controller index
 *  \param[in]      BufIdx             Ethernet Rx Buffer index
 *  \param[in,out]  DataPtr            [in]:  Pointer to the position of the EtherType of a common Ethernet frame
 *                                     [out]: Pointer to the position of the EtherType in the management frame
 *  \param[in,out]  LengthPtr          [in]:  Pointer to the length of the frame received
 *                                     [out]: Pointer to the length decreased by the management information length
 *  \return         E_OK               Frame successfully processed.
 *  \return         E_NOT_OK           Frame processing failed.
 *  \context        ANY
 *  \reentrant      TRUE
 *  \pre            -
 *  \synchronous    TRUE
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_EthTxProcessFrame(
                 uint8                                          CtrlIdx,
                 uint8                                          BufIdx,
                 Eth_FrameIdType                                FrameId,
    ETHSWT_P2VAR(ETHSWT_P2VAR(uint8, SJA1105PQRS), SJA1105PQRS) DataPtr,
    ETHSWT_P2VAR(uint16,                           SJA1105PQRS) LengthPtr );

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_SetMgmtInfo
 *********************************************************************************************************************/
/*! \brief          Sets the management information for the provided frame to achieve transmission only on specific
 *                  ports.
 *  \details        -
 *  \param[in]      CtrlIdx            Ethernet Controller index
 *  \param[in]      BufIdx             Ethernet Tx Buffer index
 *  \param[in]      MgmtInfoPtr        Pointer to the management information
 *  \return         E_OK               Insertion of management information successful.
 *  \return         E_NOT_OK           Insertion of management information failed.
 *  \context        ANY
 *  \reentrant      TRUE
 *  \pre            -
 *  \synchronous    TRUE
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_SetMgmtInfo(
                 uint8                              CtrlIdx,
                 uint8                              BufIdx,
  ETHSWT_P2CONST(EthSwt_MgmtInfoType, SJA1105PQRS)  MgmtInfoPtr);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_EthTxFinishedIndication
 *********************************************************************************************************************/
/*! \brief          Indication for a finished transmit process for a specific Ethernet frame.
 *  \details        -
 *  \param[in]      CtrlIdx            Ethernet Controller index
 *  \param[in]      BufIdx             Ethernet Tx Buffer index
 *  \context        ANY
 *  \reentrant      TRUE
 *  \pre            -
 *  \synchronous    TRUE
 *********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_EthTxFinishedIndication(
    uint8            CtrlIdx,
    uint8            BufIdx,
    Eth_FrameIdType  FrameId);

#endif /* ETHSWT_30_SJA1105PQRS_MANAGEMENT_SUPPORT */

#define ETHSWT_30_SJA1105PQRS_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* PRQA L:IDENTIFIER_DIFFER */


#endif /* ETHSWT_30_SJA1105PQRS_MGMT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthSwt_30_Sja1105PQRS_Mgmt.h
 *********************************************************************************************************************/
