/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  SoAd_Tx.h
 *        \brief  Socket Adaptor header file
 *
 *      \details  Vector static code header file for AUTOSAR Socket Adaptor sub-component Tx.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main source file.
 *********************************************************************************************************************/

#if !defined (SOAD_TX_H)
# define SOAD_TX_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "SoAd.h"
# include "SoAd_Priv.h"

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

# define SOAD_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */ /*lint !e451 */

/**********************************************************************************************************************
 *  SoAd_Tx_Init()
**********************************************************************************************************************/
/*! \brief        Initializes Tx structs for PduRoutes and NPdus.
 *  \details      -
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_Tx_Init(void);

/**********************************************************************************************************************
 *  SoAd_Tx_InitSoCon()
**********************************************************************************************************************/
/*! \brief        Initializes Tx structs on a socket connection.
 *  \details      -
 *  \param[in]    SoConIdx      Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_Tx_InitSoCon(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_Tx_IfTransmit()
 *********************************************************************************************************************/
/*! \brief        Transmits a IF-PDU over all related PduRouteDests.
 *  \details      -
 *  \param[in]    PduRouteIdx         PDU route index.
 *                                    [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \param[in]    PduInfoPtr          Pointer to PDU.
 *  \param[out]   ErrorIdPtr          Pointer to error identifier (set if error occurred).
 *  \return       E_OK                SoConId is valid and corresponding PduRouteDest was found.
 *  \return       E_NOT_OK            SoConId is invalid.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_Tx_IfTransmit(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) PduInfoPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_Tx_IfTransmitPduRouteDest()
**********************************************************************************************************************/
/*! \brief        Transmits a IF-PDU on a socket connection.
 *  \details      -
 *  \param[in]    PduRouteDestIdx   PduRouteDest index.
 *                                  [range: PduRouteDestIdx < SoAd_GetSizeOfPduRouteDest()]
 *  \param[in]    PduInfoPtr        Pointer to PDU.
 *  \param[out]   ErrorIdPtr        Pointer to error identifier (set if error occurred).
 *  \return       E_OK              Transmit request was accepted.
 *  \return       E_NOT_OK          Transmit request was not accepted.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different socket connection indexes, FALSE for same socket socket connection index.
 *  \synchronous  TRUE
**********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_Tx_IfTransmitPduRouteDest(
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_Tx_TpTransmit()
**********************************************************************************************************************/
/*! \brief        Transmits a TP-PDU over the related PduRouteDest.
 *  \details      -
 *  \param[in]    PduRouteIdx         PDU route index.
 *                                    [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \param[in]    PduInfoPtr          Pointer to PDU.
 *  \return       E_OK                Transmission request was successful.
 *  \return       E_NOT_OK            Transmission request was not successful.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
**********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_Tx_TpTransmit(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) PduInfoPtr);

/**********************************************************************************************************************
 *  SoAd_Tx_TpCancelTransmit()
 *********************************************************************************************************************/
/*! \brief        Requests transmission cancellation of a specific TP-PDU.
 *  \details      -
 *  \param[in]    PduRouteIdx   PDU route index.
 *                              [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \return       E_OK          Transmit cancellation request was accepted.
 *  \return       E_NOT_OK      Transmit cancellation request was not accepted.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_Tx_TpCancelTransmit(
  SoAd_SizeOfPduRouteType PduRouteIdx);

/**********************************************************************************************************************
 *  SoAd_Tx_CopyTxData()
 *********************************************************************************************************************/
/*! \brief          Copies data to provided transmission buffer.
 *  \details        Uses "BufLengthPtr" to update length if less data is copied to provided buffer.
 *  \param[in]      SockIdx           Module internal socket index.
 *                                    [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \param[in]      BufPtr            Pointer to buffer of provided transmission buffer.
 *  \param[in,out]  BufLengthPtr      Pointer to length of provided transmission buffer.
 *  \return         BUFREQ_OK         Copy request accepted.
 *  \return         BUFREQ_E_NOT_OK   Copy request not accepted.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different socket indexes, FALSE for same socket index.
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_Tx_CopyTxData(
  SoAd_SizeOfSocketType SockIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) BufLengthPtr);

# if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR )
#  if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
  SoAd_Tx_TcpGetUnconfirmedDataLength()
**********************************************************************************************************************/
/*! \brief        Returns length of TCP data which are sent but not yet confirmed on a socket.
 *  \details      -
 *  \param[in]    SockIdx           Module internal socket index.
 *                                  [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \return       Length            Length of unconfirmed transmitted data.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \config       SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR & SOAD_TCP
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(uint32, SOAD_CODE) SoAd_Tx_TcpGetUnconfirmedDataLength(
  SoAd_SizeOfSocketType SockIdx);
#  endif /* SOAD_TCP == STD_ON */
# endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */

/**********************************************************************************************************************
 *  SoAd_Tx_TxConfirmation()
 *********************************************************************************************************************/
/*! \brief        Confirms transmission of data.
 *  \details      -
 *  \param[in]    SockIdx         Module internal socket index.
 *                                [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \param[in]    Length          Length of confirmed data.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different socket indexes, FALSE for same socket index.
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_Tx_TxConfirmation(
  SoAd_SizeOfSocketType SockIdx,
  uint16 Length);

/**********************************************************************************************************************
 *  SoAd_Tx_TerminateTransmit()
**********************************************************************************************************************/
/*! \brief        Terminates active transmission on a socket connection.
 *  \details      -
 *  \param[in]    SoConIdx    Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
**********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_Tx_TerminateTransmit(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_Tx_HandleTransmission()
**********************************************************************************************************************/
/*! \brief        Handles transmission in main function context.
 *  \details      -
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
**********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_Tx_HandleTransmission(void);

/**********************************************************************************************************************
 *  SoAd_Tx_HandleConfirmation()
**********************************************************************************************************************/
/*! \brief        Handles transmission confirmation in main function context.
 *  \details      -
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
**********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_Tx_HandleConfirmation(void);

# define SOAD_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_19.1 */

#endif /* SOAD_TX_H */

/**********************************************************************************************************************
 *  END OF FILE: SoAd_Tx.h
 *********************************************************************************************************************/
