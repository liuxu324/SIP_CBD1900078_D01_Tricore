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
/**        \file  SoAd_Tx.c
 *        \brief  Socket Adaptor source file
 *
 *      \details  Vector static code implementation for AUTOSAR Socket Adaptor sub-component Tx.
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

/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */

#define SOAD_TX_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "SoAd_EventQueue.h"
#include "SoAd_TimeoutList.h"
#include "SoAd_TcpIp.h"
#include "SoAd_SoCon.h"
#include "SoAd_RouteGrp.h"
#include "SoAd_Util.h"
#include "SoAd_Tx.h"

#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
# include "Det.h"
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
#include "IpBase.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! Length if meta data. */
#define SOAD_TX_META_DATA_LEN                       2u
/*! Number of retries to send a nPdu if nPdu becomes larger (caused by larger PDUs in trigger transmit calls). */
#define SOAD_N_PDU_UDP_TX_QUEUE_RETRY_CNT_DIRECT    2u

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (SOAD_LOCAL)
# define SOAD_LOCAL static
#endif

#if !defined (SOAD_LOCAL_INLINE)
# define SOAD_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define SOAD_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */ /*lint !e451 */

/**********************************************************************************************************************
 *  SoAd_Tx_CopyTxDataCheckParameter()
 *********************************************************************************************************************/
/*! \brief      Checks transmission parameters on call to SoAd_CopyTxData.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  BufLength       Length of provided transmission buffer.
 *  \return     E_OK            Parameters are valid for transmission.
 *  \return     E_NOT_OK        Parameters are not valid for transmission.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket connection index.
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_Tx_CopyTxDataCheckParameter(
  SoAd_SizeOfSoConType SoConIdx,
  uint16 BufLength);

/**********************************************************************************************************************
 *  SoAd_Tx_CopyTxDataPduHeader()
 *********************************************************************************************************************/
/*! \brief          Copies PDU header to provided transmission buffer.
 *  \details        Uses "BufLengthPtr" to decrement length of available provided transmission buffer. Sets "BufPtr" to
 *                  the position after PDU header.
 *  \param[in]      SoConIdx        Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]      PduRouteIdx     PDU route index.
 *                                  [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \param[in,out]  BufPtr          Pointer to buffer of provided transmission buffer.
 *  \param[in,out]  BufLengthPtr    Pointer to length of provided transmission buffer.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different socket connection indexes, FALSE for same socket connection index.
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_Tx_CopyTxDataPduHeader(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfPduRouteType PduRouteIdx,
  P2VAR(uint8*, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) BufLengthPtr);

/**********************************************************************************************************************
 *  SoAd_Tx_CheckSoConStates()
 *********************************************************************************************************************/
/*! \brief      Checks if socket connection and corresponding socket is ready to transmit data.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \return     E_OK            Transmision possible.
 *  \return     E_NOT_OK        No tansmision possible.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_Tx_CheckSoConStates(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_Tx_UdpImmediateIfTxConfirmation()
 *********************************************************************************************************************/
/*! \brief      Confirms transmission of data for a UDP socket connection with immediate IF TxConfirmation.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre        -
 *  \context    ISR2
 *  \reentrant  TRUE for different socket connections, FALSE for same socket connection.
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_Tx_UdpImmediateIfTxConfirmation(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_TxIf_CheckParameter()
**********************************************************************************************************************/
/*! \brief      Checks transmission parameter for a IF-PDU.
 *  \details    -
 *  \param[in]  PduRouteIdx     PDU route index.
 *                              [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \param[in]  PduLength       PDU length.
 *  \return     E_OK            Parameters are valid for transmission.
 *  \return     E_NOT_OK        Parameters are not valid for transmission.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_CheckParameter(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  PduLengthType PduLength);

/**********************************************************************************************************************
 *  SoAd_TxIf_CheckTxPduLength()
**********************************************************************************************************************/
/*! \brief        Cheks the PDU length of a IF-PDU requested for transmission.
 *  \details      -
 *  \param[in]    PduRouteIdx     PDU route index.
 *                                [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \param[in]    PduLength       PDU length.
 *  \return       E_OK            PDU length is valid.
 *  \return       E_NOT_OK        PDU length is invalid.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_CheckTxPduLength(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  PduLengthType PduLength);

/**********************************************************************************************************************
 *  SoAd_TxIf_CheckTxState()
**********************************************************************************************************************/
/*! \brief        Checks the transmission state for a IF-PDU if transmission is allowed or not.
 *  \details      -
 *  \param[in]    PduRouteIdx     PDU route index.
 *                                [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \return       E_OK            Transmission is allowed.
 *  \return       E_NOT_OK        Transmission is prohibited.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_CheckTxState(
  SoAd_SizeOfPduRouteType PduRouteIdx);

/**********************************************************************************************************************
 *  SoAd_TxIf_TransmitPdu()
**********************************************************************************************************************/
/*! \brief        Transmits a valid IF-PDU over all related PduRouteDests.
 *  \details      -
 *  \param[in]    PduRouteIdx     PDU route index.
 *                                [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \param[in]    PduInfoPtr      Pointer to PDU.
 *  \param[out]   ErrorIdPtr      Pointer to error identifier (set if error occurred).
 *  \return       E_OK            SoConId is valid and corresponding PduRouteDest was found.
 *  \return       E_NOT_OK        SoConId is invalid.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_TransmitPdu(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) PduInfoPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_TxIf_GetPduRouteDestIdxByMetaData()
**********************************************************************************************************************/
/*! \brief        Returns the PduRouteDest of a PduRoute which matches the SoConId in the meta data if configured.
 *  \details      -
 *  \param[in]    PduRouteIdx         PDU route index.
 *                                    [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \param[in]    PduInfoPtr          Pointer to PDU.
 *  \param[out]   PduRouteDestIdxPtr  Pointer to index of PduRouteDest.
 *  \return       E_OK                SoConId is valid and corresponding PduRouteDest was found.
 *  \return       E_NOT_OK            SoConId is invalid.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_GetPduRouteDestIdxByMetaData(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) PduInfoPtr,
  P2VAR(SoAd_SizeOfPduRouteDestType, AUTOMATIC, SOAD_APPL_DATA) PduRouteDestIdxPtr);

/**********************************************************************************************************************
 *  SoAd_TxIf_TransmitPduRouteDest()
**********************************************************************************************************************/
/*! \brief        Transmits a IF-PDU on a socket connection.
 *  \details      -
 *  \param[in]    PduRouteDestIdx PduRouteDest index.
 *                                [range: PduRouteDestIdx < SoAd_GetSizeOfPduRouteDest()]
 *  \param[in]    PduInfoPtr      Pointer to PDU.
 *  \param[out]   ErrorIdPtr      Pointer to error identifier (set if error occurred).
 *  \return       E_OK            Transmit request was accepted.
 *  \return       E_NOT_OK        Transmit request was not accepted.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different socket connection indexes, FALSE for same socket socket connection index.
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_TransmitPduRouteDest(
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_TxIf_TcpTransmit()
**********************************************************************************************************************/
/*! \brief      Transmits a IF-PDU on a TCP socket connection.
 *  \details    -
 *  \param[in]  PduRouteDestIdx PduRouteDest index.
 *                              [range: PduRouteDestIdx < SoAd_GetSizeOfPduRouteDest()]
 *  \param[in]  PduInfoPtr      Pointer to PDU.
 *  \return     E_OK            Transmit processed successfully.
 *  \return     E_NOT_OK        Transmit failed.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_TCP
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_TcpTransmit(
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr);

/**********************************************************************************************************************
 *  SoAd_TxIf_TcpPrepareTransmit()
**********************************************************************************************************************/
/*! \brief      Prepares transmission of a IF-PDU on a TCP socket connection.
 *  \details    -
 *  \param[in]  PduRouteDestIdx PduRouteDest index.
 *                              [range: PduRouteDestIdx < SoAd_GetSizeOfPduRouteDest()]
 *  \param[in]  PduInfoPtr      Pointer to PDU.
 *  \return     E_OK            Transmit prepared successfully.
 *  \return     E_NOT_OK        Transmit preparation failed.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_TCP
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_TcpPrepareTransmit(
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr);

/**********************************************************************************************************************
 *  SoAd_TxIf_TcpCallTransmit()
**********************************************************************************************************************/
/*! \brief      Calls transmission service of lower layer to transmit a IF-PDU on a TCP socket connection.
 *  \details    -
 *  \param[in]  PduRouteDestIdx PduRouteDest index.
 *                              [range: PduRouteDestIdx < SoAd_GetSizeOfPduRouteDest()]
 *  \return     E_OK            Transmit processed successfully.
 *  \return     E_NOT_OK        Transmit failed.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_TCP
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_TcpCallTransmit(
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx);

/**********************************************************************************************************************
 *  SoAd_TxIf_TcpCopyTxData()
**********************************************************************************************************************/
/*! \brief      Copies data to provided transmission buffer of a IF-PDU on a TCP socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  BufPtr          Pointer to buffer of provided transmission buffer.
 *  \param[in]  BufLength       Length of provided transmission buffer.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket connection index.
 *  \config     SOAD_TCP
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxIf_TcpCopyTxData(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 BufLength);
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TxIf_UdpTransmit()
**********************************************************************************************************************/
/*! \brief        Transmits a IF-PDU on a UDP socket connection.
 *  \details      -
 *  \param[in]    PduRouteDestIdx PduRouteDest index.
 *                                [range: PduRouteDestIdx < SoAd_GetSizeOfPduRouteDest()]
 *  \param[in]    PduInfoPtr      Pointer to PDU.
 *  \param[out]   ErrorIdPtr      Pointer to error identifier (set if error occurred).
 *  \return       E_OK            Transmit processed successfully.
 *  \return       E_NOT_OK        Transmit failed.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_UdpTransmit(
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_TxIf_UdpTransmitNPdu()
**********************************************************************************************************************/
/*! \brief        Transmits a IF-PDU as a nPdu on a UDP socket connection.
 *  \details      -
 *  \param[in]    PduRouteDestIdx PduRouteDest index.
 *                                [range: PduRouteDestIdx < SoAd_GetSizeOfPduRouteDest()]
 *  \param[in]    PduInfoPtr      Pointer to PDU.
 *  \param[out]   ErrorIdPtr      Pointer to error identifier (set if error occurred).
 *  \return       E_OK            Transmit processed successfully.
 *  \return       E_NOT_OK        Transmit failed.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_UdpTransmitNPdu(
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_TxIf_UdpTransmitNPduQueue()
**********************************************************************************************************************/
/*! \brief        Transmits a IF-PDU as a nPdu stored in a queue on a UDP socket connection.
 *  \details      -
 *  \param[in]    PduRouteDestIdx PduRouteDest index.
 *                                [range: PduRouteDestIdx < SoAd_GetSizeOfPduRouteDest()]
 *  \param[in]    PduInfoPtr      Pointer to PDU.
 *  \return       E_OK            Transmit processed successfully.
 *  \return       E_NOT_OK        Transmit failed.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_UdpTransmitNPduQueue(
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr);

/**********************************************************************************************************************
 *  SoAd_TxIf_UdpTransmitNPduBuffer()
**********************************************************************************************************************/
/*! \brief        Transmits a IF-PDU as a nPdu stored in a buffer on a UDP socket connection.
 *  \details      -
 *  \param[in]    PduRouteDestIdx PduRouteDest index.
 *                                [range: PduRouteDestIdx < SoAd_GetSizeOfPduRouteDest()]
 *  \param[in]    PduInfoPtr      Pointer to PDU.
 *  \return       E_OK            Transmit processed successfully.
 *  \return       E_NOT_OK        Transmit failed.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_UdpTransmitNPduBuffer(
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr);

/**********************************************************************************************************************
 *  SoAd_TxIf_UdpTransmitPdu()
**********************************************************************************************************************/
/*! \brief        Transmits a IF-PDU as a single PDU on a UDP socket connection.
 *  \details      -
 *  \param[in]    PduRouteDestIdx PduRouteDest index.
 *                                [range: PduRouteDestIdx < SoAd_GetSizeOfPduRouteDest()]
 *  \param[in]    PduInfoPtr      Pointer to PDU.
 *  \return       E_OK            Transmit processed successfully.
 *  \return       E_NOT_OK        Transmit failed.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_UdpTransmitPdu(
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr);

/**********************************************************************************************************************
 *  SoAd_TxIf_UdpCopyTxData()
**********************************************************************************************************************/
/*! \brief          Copies data to provided transmission buffer of a IF-PDU on a UDP socket connection.
 *  \details        Uses "BufLengthPtr" to update length if less data is copied to provided buffer.
 *  \param[in]      SoConIdx            Socket connection index.
 *                                      [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]      BufPtr              Pointer to buffer of provided transmission buffer.
 *  \param[in,out]  BufLengthPtr        Pointer to length of provided transmission buffer.
 *  \return         BUFREQ_OK           Copy request accepted.
 *  \return         BUFREQ_E_NOT_OK     Copy request not accepted.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different socket connection indexes, FALSE for same socket connection index.
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_TxIf_UdpCopyTxData(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) BufLengthPtr);

/**********************************************************************************************************************
 *  SoAd_TxIf_UdpCopyTxDataTrigger()
**********************************************************************************************************************/
/*! \brief          Copies data to provided transmission buffer of a IF-PDU on a UDP socket connection retrieved via
 *                  trigger transmit call.
 *  \details        Uses "BufLengthPtr" to update length if less data is copied to provided buffer.
 *  \param[in]      SoConIdx            Socket connection index.
 *                                      [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]      PduRouteIdx         PDU route index.
 *                                      [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \param[in]      BufPtr              Pointer to buffer of provided transmission buffer.
 *  \param[in,out]  BufLengthPtr        Pointer to length of provided transmission buffer.
 *  \return         BUFREQ_OK           Copy request accepted.
 *  \return         BUFREQ_E_NOT_OK     Copy request not accepted.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different socket connection indexes, FALSE for same socket connection index.
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_TxIf_UdpCopyTxDataTrigger(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfPduRouteType PduRouteIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) BufLengthPtr);

/**********************************************************************************************************************
 *  SoAd_TxIf_UdpCopyTxDataTriggerCheckParameter()
**********************************************************************************************************************/
/*! \brief      Checks parameter after call to trigger transmit for a IF-PDU on a UDP socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  BufLength       Length of provided transmission buffer.
 *  \param[in]  PduInfoPtr      Pointer to PDU copied in trigger transmit call.
 *  \return     E_OK            Trigger transmit call returned valid parameter.
 *  \return     E_NOT_OK        Trigger transmit call returned invalid parameter.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket connection index.
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_UdpCopyTxDataTriggerCheckParameter(
  SoAd_SizeOfSoConType SoConIdx,
  uint16 BufLength,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr);

/**********************************************************************************************************************
 *  SoAd_TxIf_UdpCopyTxDataTriggerFinish()
**********************************************************************************************************************/
/*! \brief          Finishes transmission of a IF-PDU on a UDP socket connection retrieved via trigger transmit.
 *  \details        Uses "BufLengthPtr" to update length if less data is copied to provided buffer.
 *  \param[in]      SoConIdx        Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]      BufPtr          Pointer to buffer of provided transmission buffer.
 *  \param[in,out]  BufLengthPtr    Pointer to length of provided transmission buffer.
 *  \param[in]      PduInfoPtr      Pointer to PDU copied in trigger transmit call.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different socket connection indexes, FALSE for same socket connection index.
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxIf_UdpCopyTxDataTriggerFinish(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) BufLengthPtr,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr);

/**********************************************************************************************************************
 *  SoAd_TxIf_UdpCopyTxDataDirect()
**********************************************************************************************************************/
/*! \brief          Copies data to provided transmission buffer of a IF-PDU on a UDP socket connection sent directly
 *                  without trigger transmit.
 *  \details        -
 *  \param[in]      SoConIdx        Socket connection index.
 *                                  [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]      BufPtr          Pointer to buffer of provided transmission buffer.
 *  \param[in]      BufLength       Length of provided transmission buffer.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different socket connection indexes, FALSE for same socket connection index.
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxIf_UdpCopyTxDataDirect(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 BufLength);

/**********************************************************************************************************************
 *  SoAd_TxIf_AddPendingConf()
**********************************************************************************************************************/
/*! \brief      Adds a pending TxConfirmation for IF-API to a specific socket connection.
 *  \details    Handles TxConfirmations generated by SoAd itself and called in context of SoAd_TxConfirmation.
 *  \param[in]  PduRouteIdx     PDU route index.
 *                              [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxIf_AddPendingConf(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_TxIf_AddPendingConfUdp()
**********************************************************************************************************************/
/*! \brief      Adds a pending TxConfirmation for IF-API to a specific UDP socket connection.
 *  \details    Handles TxConfirmations generated by SoAd itself and called in context of SoAd_TxConfirmation.
 *  \param[in]  PduRouteIdx     PDU route index.
 *                              [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxIf_AddPendingConfUdp(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_TxIf_UdpHandleTxConfirmation()
**********************************************************************************************************************/
/*! \brief      Handles TxConfirmation in main function context for IF-API on UDP socket connections.
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxIf_UdpHandleTxConfirmation(void);

/**********************************************************************************************************************
 *  SoAd_TxIf_UdpTxConfirmation()
**********************************************************************************************************************/
/*! \brief      Calls TxConfirmation in main function context for a PduRoute with IF-API on UDP socket connections.
 *  \param[in]  PduRouteIdx     PDU route index.
 *                              [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxIf_UdpTxConfirmation(
  SoAd_SizeOfPduRouteType PduRouteIdx);

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_TxIf_TcpTxConfirmation()
**********************************************************************************************************************/
/*! \brief        Confirms IF transmission on a TCP socket connection.
 *  \details      -
 *  \param[in]    SoConIdx      Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    PduRouteIdx   PDU route index.
 *                              [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \param[in]    ByResetSoCon  Indicates if confirmation is requested by resetting socket connection on close.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \config       SOAD_TCP
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxIf_TcpTxConfirmation(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfPduRouteType PduRouteIdx,
  boolean ByResetSoCon);
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TxTp_CheckParameter()
**********************************************************************************************************************/
/*! \brief        Checks transmission parameter for a TP-PDU.
 *  \details      -
 *  \param[in]    PduRouteIdx     PDU route index.
 *                                [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \param[in]    PduLength       PDU length.
 *  \return       E_OK            Parameters are valid for transmission.
 *  \return       E_NOT_OK        Parameters are not valid for transmission.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxTp_CheckParameter(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  PduLengthType PduLength);

/**********************************************************************************************************************
 *  SoAd_TxTp_TransmitPdu()
**********************************************************************************************************************/
/*! \brief        Transmits a TP-PDU over the related PduRouteDest.
 *  \details      -
 *  \param[in]    PduRouteIdx     PDU route index.
 *                                [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \param[in]    PduInfoPtr      Pointer to PDU.
 *  \return       E_OK            Transmission request was successful.
 *  \return       E_NOT_OK        Transmission request was not successful.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxTp_TransmitPdu(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) PduInfoPtr);

/**********************************************************************************************************************
 *  SoAd_TxTp_CheckAndSetProtocolParameter()
**********************************************************************************************************************/
/*! \brief        Checks and sets protocol specific parameters for a transmission of a TP-PDU.
 *  \details      -
 *  \param[in]    PduRouteIdx     PDU route index.
 *                                [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \param[in]    PduLength       PDU length.
 *  \return       E_OK            Parameters are valid and set for transmission.
 *  \return       E_NOT_OK        Parameters are not valid and therefore not set for transmission.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxTp_CheckAndSetProtocolParameter(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  PduLengthType PduLength);

/**********************************************************************************************************************
 *  SoAd_TxTp_PrepareTransmitPdu()
**********************************************************************************************************************/
/*! \brief        Prepares socket connection to perform a transmission of a TP-PDU.
 *  \details      -
 *  \param[in]    PduRouteIdx     PDU route index.
 *                                [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \param[in]    PduLength       PDU length.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTp_PrepareTransmitPdu(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  PduLengthType PduLength);

/**********************************************************************************************************************
 *  SoAd_TxTp_CallCopyTxData()
**********************************************************************************************************************/
/*! \brief        Calls CopyTxData function of upper layer.
 *  \details      -
 *  \param[in]    PduRouteIdx       PDU route index.
 *                                  [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \param[in]    PduInfoPtr        Pointer to PDU.
 *  \param[out]   BufferSizePtr     Pointer to available data length.
 *  \return       BUFREQ_OK         Copy request accepted.
 *  \return       BUFREQ_E_BUSY     Required amount of data is not available.
 *  \return       BUFREQ_E_NOT_OK   Copy request not accepted.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_TxTp_CallCopyTxData(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  CONSTP2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) PduInfoPtr,
  CONSTP2VAR(PduLengthType, AUTOMATIC, SOAD_APPL_DATA) BufferSizePtr);

/**********************************************************************************************************************
 *  SoAd_TxTp_TerminateTransmit()
**********************************************************************************************************************/
/*! \brief        Terminates active Tx TP session on a socket connection.
 *  \details      -
 *  \param[in]    SoConIdx    Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTp_TerminateTransmit(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_TxTp_CancelTransmit()
**********************************************************************************************************************/
/*! \brief      Requests PDU transmission cancellation which is handled later in main function context.
 *  \details    -
 *  \param[in]  PduRouteIdx   PDU route index.
 *                            [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \return     E_OK          Cancellation request succeeded.
 *  \return     E_NOT_OK      Cancellation request failed.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxTp_CancelTransmit(
  SoAd_SizeOfPduRouteType PduRouteIdx);

/**********************************************************************************************************************
 *  SoAd_TxTp_HandleTransmission()
**********************************************************************************************************************/
/*! \brief      Handles TP transmission in main function context.
 *  \details    -
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTp_HandleTransmission(void);

/**********************************************************************************************************************
 *  SoAd_TxTp_TransmitPduRouteDest()
**********************************************************************************************************************/
/*! \brief      Transmits a TP-PDU on a socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  CalledByMain    Indicates if transmission is in context of main function instead of transmit service.
 *  \return     E_OK            Transmit processed successfully.
 *  \return     E_NOT_OK        Transmit failed.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket socket connection index.
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxTp_TransmitPduRouteDest(
  SoAd_SizeOfSoConType SoConIdx,
  boolean CalledByMain);

/**********************************************************************************************************************
 *  SoAd_TxTp_HandleCancellation()
**********************************************************************************************************************/
/*! \brief      Handles TP reception cancellation in main function context.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre        -
 *  \context    TASK
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket socket connection index.
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTp_HandleCancellation(
  SoAd_SizeOfSoConType SoConIdx);

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_TxTp_TcpTransmit()
**********************************************************************************************************************/
/*! \brief      Transmits a TP-PDU on a TCP socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  CalledByMain    Indicates if transmission is in context of main function instead of transmit service.
 *  \return     E_OK            Transmit processed successfully.
 *  \return     E_NOT_OK        Transmit failed.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket socket connection index.
 *  \config     SOAD_TCP
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxTp_TcpTransmit(
  SoAd_SizeOfSoConType SoConIdx,
  boolean CalledByMain);

/**********************************************************************************************************************
 *  SoAd_TxTp_TcpCalculateLength()
**********************************************************************************************************************/
/*! \brief        Calculates length of available data to be transmitted.
 *  \details      -
 *  \param[in]    SoConIdx            Socket connection index.
 *                                    [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[out]   AvailableBufLenPtr  Pointer to available upper layer TP transmission buffer.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different socket connection indexes, FALSE for same socket socket connection index.
 *  \config       SOAD_TCP
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTp_TcpCalculateLength(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(PduLengthType, AUTOMATIC, SOAD_APPL_VAR) AvailableBufLenPtr);

/**********************************************************************************************************************
 *  SoAd_TxTp_TcpTransmitHandleSuccess()
**********************************************************************************************************************/
/*! \brief      Handles TP session in TCP socket connection if transmission to TcpIp was successful.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket socket connection index.
 *  \config     SOAD_TCP
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTp_TcpTransmitHandleSuccess(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_TxTp_TcpTransmitHandleFail()
**********************************************************************************************************************/
/*! \brief      Handles TP session in TCP socket connection if transmission to TcpIp has failed.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  CalledByMain    Indicates if transmission is in context of main function instead of transmit service.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket socket connection index.
 *  \config     SOAD_TCP
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTp_TcpTransmitHandleFail(
  SoAd_SizeOfSoConType SoConIdx,
  boolean CalledByMain);

/**********************************************************************************************************************
 *  SoAd_TxTp_TcpCopyTxData()
**********************************************************************************************************************/
/*! \brief      Copies data to provided transmission buffer of a TP-PDU on a TCP socket connection.
 *  \details    -
 *  \param[in]  SoConIdx          Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PduRouteIdx       PDU route index.
 *                                [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \param[in]  BufPtr            Pointer to buffer of provided transmission buffer.
 *  \param[in]  BufLength         Length of provided transmission buffer.
 *  \return     BUFREQ_OK         Copy request accepted.
 *  \return     BUFREQ_E_NOT_OK   Copy request not accepted.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket connection index.
 *  \config     SOAD_TCP
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_TxTp_TcpCopyTxData(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfPduRouteType PduRouteIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 BufLength);

/**********************************************************************************************************************
 *  SoAd_TxTp_TcpTxConfirmation()
**********************************************************************************************************************/
/*! \brief        Confirms successful TP transmission on a TCP socket connection.
 *  \details      -
 *  \param[in]    SoConIdx      Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    PduRouteIdx   PDU route index.
 *                              [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \config       SOAD_TCP
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTp_TcpTxConfirmation(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfPduRouteType PduRouteIdx);
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TxTp_UdpTransmit()
**********************************************************************************************************************/
/*! \brief      Transmits a TP-PDU on a UDP socket connection.
 *  \details    Copies PDU to TP transmission buffer first and triggers transmission when copied completely.
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  CalledByMain    Indicates if transmission is in context of main function instead of transmit service.
 *  \return     E_OK            Transmit processed successfully.
 *  \return     E_NOT_OK        Transmit failed.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket socket connection index.
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxTp_UdpTransmit(
  SoAd_SizeOfSoConType SoConIdx,
  boolean CalledByMain);

/**********************************************************************************************************************
 *  SoAd_TxTp_UdpCopyPduHdr()
**********************************************************************************************************************/
/*! \brief      Copies PDU header to TP transmission buffer.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket socket connection index.
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTp_UdpCopyPduHdr(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_TxTp_UdpCopyPdu()
**********************************************************************************************************************/
/*! \brief      Copies PDU to TP transmission buffer.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  CalledByMain    Indicates if transmission is in context of main function instead of transmit service.
 *  \return     E_OK            PDU copied successfully.
 *  \return     E_NOT_OK        PDU copy failed.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket socket connection index.
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxTp_UdpCopyPdu(
  SoAd_SizeOfSoConType SoConIdx,
  boolean CalledByMain);

/**********************************************************************************************************************
 *  SoAd_TxTp_UdpTransmitOnSocket()
**********************************************************************************************************************/
/*! \brief      Transmits data from TP transmission buffer over a UDP socket conenction.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  CalledByMain    Indicates if transmission is in context of main function instead of transmit service.
 *  \return     E_OK            Transmisssion succeeded.
 *  \return     E_NOT_OK        Transmission failed.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket socket connection index.
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxTp_UdpTransmitOnSocket(
  SoAd_SizeOfSoConType SoConIdx,
  boolean CalledByMain);

/**********************************************************************************************************************
 *  SoAd_TxTp_UdpTerminateTransmit()
**********************************************************************************************************************/
/*! \brief      Terminates a TP session for transmission on a UDP socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  CalledByMain    Indicates if transmission is in context of main function instead of transmit service.
 *  \param[in]  Result          Indicates result of transmission. Range: E_OK, E_NOT_OK.
 *  \return     E_OK            Transmisssion succeeded.
 *  \return     E_NOT_OK        Transmission failed.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket socket connection index.
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTp_UdpTerminateTransmit(
  SoAd_SizeOfSoConType SoConIdx,
  boolean CalledByMain,
  Std_ReturnType Result);

/**********************************************************************************************************************
 *  SoAd_TxTp_UdpCopyTxData()
**********************************************************************************************************************/
/*! \brief      Copies data to provided transmission buffer of a TP-PDU on a UDP socket connection.
 *  \details    -
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  BufPtr          Pointer to buffer of provided transmission buffer.
 *  \param[in]  BufLength       Length of provided transmission buffer.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different socket connection indexes, FALSE for same socket connection index.
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTp_UdpCopyTxData(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 BufLength);

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_TxTcpQueue_Init()
**********************************************************************************************************************/
/*! \brief      Initializes Tx TCP queue on a specific socket connection if configured.
 *  \details    -
 *  \param[in]  SoConIdx    Socket connection index.
 *                          [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_TCP
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTcpQueue_Init(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_TxTcpQueue_Clear()
**********************************************************************************************************************/
/*! \brief      Clears Tx TCP queue on a specific socket connection if configured.
 *  \details    Calls additionally IF TxConfirmation if pending.
 *  \param[in]  SoConIdx    Socket connection index.
 *                          [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_TCP
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTcpQueue_Clear(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_TxTcpQueue_ReserveNextElement()
**********************************************************************************************************************/
/*! \brief      Reserves next free Tx TCP queue entry to store a transmission.
 *  \details    -
 *  \param[in]  SoConIdx      Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PduRouteIdx   PDU route index.
 *                            [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \return     E_OK          Element reserved.
 *  \return     E_NOT_OK      No elements left or an element is already reserved.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_TCP
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxTcpQueue_ReserveNextElement(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfPduRouteType PduRouteIdx);

/**********************************************************************************************************************
 *  SoAd_TxTcpQueue_GetNextElement()
**********************************************************************************************************************/
/*! \brief      Gets next free Tx TCP queue entry to store a transmission if not already reserved.
 *  \details    -
 *  \param[in]  SoConIdx    Socket connection index.
 *                          [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[out] WriteIdx    Pointer to next write index.
 *  \return     E_OK        Next element available.
 *  \return     E_NOT_OK    Last element is already reserved.
 *  \pre        Has to be called in critical section.
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_TCP
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxTcpQueue_GetNextElement(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(SoAd_SizeOfTcpTxQueueDataType, AUTOMATIC, SOAD_APPL_DATA) WriteIdx);

/**********************************************************************************************************************
 *  SoAd_TxTcpQueue_SetElement()
**********************************************************************************************************************/
/*! \brief      Sets a previously reserved element in Tx TCP queue.
 *  \details    -
 *  \param[in]  SoConIdx      Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PduRouteIdx   PDU route index.
 *                            [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \param[in]  Len           Length of transmission data.
 *  \param[in]  Release       Release or set the reserved element.
 *  \pre        An element has to be reserved with SoAd_TxTcpQueue_ReserveNextElement().
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_TCP
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTcpQueue_SetElement(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfPduRouteType PduRouteIdx,
  PduLengthType Len,
  boolean Release);

/**********************************************************************************************************************
 *  SoAd_TxTcpQueue_GetTotalLength()
**********************************************************************************************************************/
/*! \brief      Returns the total length of all set queue elements.
 *  \details    -
 *  \param[in]  SoConIdx    Socket connection index.
 *                          [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \return     TotalLen    Total length of all set queue elements.
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_TCP
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(uint32, SOAD_CODE) SoAd_TxTcpQueue_GetTotalLength(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_TxTcpQueue_TxConfirmation
**********************************************************************************************************************/
/*! \brief        Removes elements from queue which have been sent and calls the corresponding notification of user.
 *  \details      -
 *  \param[in]    SoConIdx    Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    Len         Length of confirmed transmission data.
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \config       SOAD_TCP
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTcpQueue_TxConfirmation(
  SoAd_SizeOfSoConType SoConIdx,
  PduLengthType Len);
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_HandleTransmission()
**********************************************************************************************************************/
/*! \brief      Handles nPdu transmission in main function context.
 *  \details    -
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxNPduUdp_HandleTransmission(void);

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_Transmit()
**********************************************************************************************************************/
/*! \brief      Transmits a nPdu.
 *  \details    -
 *  \param[in]  NPduIdx           NPdu index.
 *                                [range: NPduIdx < SoAd_GetSizeOfNPduUdpTx()]
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxNPduUdp_Transmit(
  SoAd_SizeOfNPduUdpTxType NPduIdx);

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_SetTriggerTimeout()
**********************************************************************************************************************/
/*! \brief      Sets timeout for nPdu if configured.
 *  \details    -
 *  \param[in]  NPduIdx           NPdu index.
 *                                [range: NPduIdx < SoAd_GetSizeOfNPduUdpTx()]
 *  \param[in]  PduRouteDestIdx   PduRouteDest index.
 *                                [range: PduRouteDestIdx < SoAd_GetSizeOfPduRouteDest()]
 *  \return     E_OK              Timeout set successfully.
 *  \return     E_NOT_OK          Timeout list cannot store timeout.
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxNPduUdp_SetTriggerTimeout(
  SoAd_SizeOfNPduUdpTxType NPduIdx,
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx);

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_Clear()
**********************************************************************************************************************/
/*! \brief      Clears a nPdu and calls the corresponding TxConfirmations if required.
 *  \details    -
 *  \param[in]  NPduIdx           NPdu index.
 *                                [range: NPduIdx < SoAd_GetSizeOfNPduUdpTx()]
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxNPduUdp_Clear(
  SoAd_SizeOfNPduUdpTxType NPduIdx);

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueAddOrUpdateElement()
**********************************************************************************************************************/
/*! \brief      Adds or updates a PDU as element to a nPdu queue.
 *  \details    -
 *  \param[in]  PduRouteIdx             PDU route index.
 *                                      [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \param[in]  PduRouteDestIdx         PduRouteDest index.
 *                                      [range: PduRouteDestIdx < SoAd_GetSizeOfPduRouteDest()]
 *  \param[in]  PduInfoPtr              Pointer to PDU.
 *  \return     SOAD_NPDU_OK            Added or updated element to nPdu successfully.
 *  \return     SOAD_NPDU_OVFL_NEW      New PDU exceeds nPdu size or queue size.
 *  \return     SOAD_NPDU_OVFL_UPDATE   Update of PDU in nPdu exceeds nPdu size.
 *  \return     SOAD_NPDU_NOT_OK        Cannot create nPdu since timeout list size is not sufficient to store nPdu.
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(SoAd_NPduReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueueAddOrUpdateElement(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr);

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueUpdateElement()
**********************************************************************************************************************/
/*! \brief      Updates a PDU as element to a nPdu queue.
 *  \details    -
 *  \param[in]  NPduIdx                 NPdu index.
 *                                      [range: NPduIdx < SoAd_GetSizeOfNPduUdpTx()]
 *  \param[in]  PduRouteIdx             PDU route index.
 *                                      [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \param[in]  DataLen                 Length of PDU considering PDU header.
 *  \param[out] ElementUpdated          Indicates if element is updated.
 *  \return     SOAD_NPDU_OK            Updated element in nPdu successfully or no element for PDU exists.
 *  \return     SOAD_NPDU_OVFL_UPDATE   Update of PDU in nPdu exceeds nPdu size.
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(SoAd_NPduReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueueUpdateElement(
  SoAd_SizeOfNPduUdpTxType NPduIdx,
  SoAd_SizeOfPduRouteType PduRouteIdx,
  PduLengthType DataLen,
  P2VAR(boolean, AUTOMATIC, SOAD_APPL_VAR) ElementUpdated);

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueAddElement()
**********************************************************************************************************************/
/*! \brief      Adds a PDU as element to a nPdu queue.
 *  \details    -
 *  \param[in]  NPduIdx                 NPdu index.
 *                                      [range: NPduIdx < SoAd_GetSizeOfNPduUdpTx()]
 *  \param[in]  PduRouteIdx             PDU route index.
 *                                      [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \param[in]  PduRouteDestIdx         PduRouteDest index.
 *                                      [range: PduRouteDestIdx < SoAd_GetSizeOfPduRouteDest()]
 *  \param[in]  DataLen                 Length of PDU considering PDU header.
 *  \param[in]  PduInfoPtr              Pointer to PDU.
 *  \return     SOAD_NPDU_OK            Added element to nPdu successfully.
 *  \return     SOAD_NPDU_OVFL_NEW      New PDU exceeds nPdu size or queue size.
 *  \return     SOAD_NPDU_NOT_OK        Cannot create nPdu since timeout list size is not sufficient to store nPdu.
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(SoAd_NPduReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueueAddElement(
  SoAd_SizeOfNPduUdpTxType NPduIdx,
  SoAd_SizeOfPduRouteType PduRouteIdx,
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  PduLengthType DataLen,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr);

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueCheckSize()
**********************************************************************************************************************/
/*! \brief      Checks if a new PDU exceeds the nPdu size or the queue size.
 *  \details    -
 *  \param[in]  NPduIdx                 NPdu index.
 *                                      [range: NPduIdx < SoAd_GetSizeOfNPduUdpTx()]
 *  \param[in]  DataLen                 Length of PDU considering PDU header.
 *  \return     SOAD_NPDU_OK            Added element to nPdu successfully.
 *  \return     SOAD_NPDU_OVFL_NEW      New PDU exceeds nPdu size or queue size.
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(SoAd_NPduReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueueCheckSize(
  SoAd_SizeOfNPduUdpTxType NPduIdx,
  PduLengthType DataLen);

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueTransmit()
**********************************************************************************************************************/
/*! \brief      Transmits a nPdu stored in a queue.
 *  \details    -
 *  \param[in]  NPduIdx                 NPdu index.
 *                                      [range: NPduIdx < SoAd_GetSizeOfNPduUdpTx()]
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
**********************************************************************************************************************/
SOAD_LOCAL FUNC(void, SOAD_CODE) SoAd_TxNPduUdp_QueueTransmit(
  SoAd_SizeOfNPduUdpTxType NPduIdx);

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueuePrepareTransmitSegment()
**********************************************************************************************************************/
/*! \brief      Prepares a transmission of a nPdu segment stored in a queue.
 *  \details    -
 *  \param[in]  NPduIdx                 NPdu index.
 *                                      [range: NPduIdx < SoAd_GetSizeOfNPduUdpTx()]
 *  \return     E_OK                    Transmission prepared successfully.
 *  \return     E_NOT_OK                Transmission not possible and nPdu is flushed if no retry is left.
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
**********************************************************************************************************************/
SOAD_LOCAL FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueuePrepareTransmitSegment(
  SoAd_SizeOfNPduUdpTxType NPduIdx);

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueCheckAndSetTransmitState()
**********************************************************************************************************************/
/*! \brief      Checks if a transmission is possible and set transmission to active if so.
 *  \details    -
 *  \param[in]  NPduIdx                 NPdu index.
 *                                      [range: NPduIdx < SoAd_GetSizeOfNPduUdpTx()]
 *  \return     E_OK                    Transmission possible and set to active.
 *  \return     E_NOT_OK                Transmission not possible and nPdu is flushed if no retry is left.
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueueCheckAndSetTransmitState(
  SoAd_SizeOfNPduUdpTxType NPduIdx);

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueCheckRetry()
**********************************************************************************************************************/
/*! \brief      Checks if a retry is left so that transmission of nPdu segment is allowed.
 *  \details    -
 *  \param[in]  NPduIdx                 NPdu index.
 *                                      [range: NPduIdx < SoAd_GetSizeOfNPduUdpTx()]
 *  \return     E_OK                    Transmission allowed.
 *  \return     E_NOT_OK                Transmission not allowed.
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueueCheckRetry(
  SoAd_SizeOfNPduUdpTxType NPduIdx);

#if ( SOAD_TX_DYN_LEN == STD_OFF )
/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueGetNPduLengthUpToOverflow()
 *********************************************************************************************************************/
/*! \brief      Sums up all PDUs in queue until nPdu overflow occurs.
 *  \details    -
 *  \param[in]  NPduIdx                 NPdu index.
 *                                      [range: NPduIdx < SoAd_GetSizeOfNPduUdpTx(),
 *                                      SoAd_IsNPduUdpTxQueueUsedOfNPduUdpTx()]
 *  \return     NPduLengthUpToOverflow  Length of all PDUs in nPdu until nPdu overflow occurs.
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
 *  \config     SOAD_TX_DYN_LEN == STD_OFF
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(uint16, SOAD_CODE) SoAd_TxNPduUdp_QueueGetNPduLengthUpToOverflow(
  SoAd_SizeOfNPduUdpTxType NPduIdx);
#endif /* SOAD_TX_DYN_LEN == STD_OFF */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueTransmitSegment()
**********************************************************************************************************************/
/*! \brief      Transmits a nPdu segment stored in a queue.
 *  \details    -
 *  \param[in]  NPduIdx                 NPdu index.
 *                                      [range: NPduIdx < SoAd_GetSizeOfNPduUdpTx()]
 *  \return     E_OK                    Transmission allowed.
 *  \return     E_NOT_OK                Transmission not allowed.
 *  \context    TASK|ISR2
 *  \pre        Transmission has to be prepared via SoAd_TxNPduUdp_QueuePrepareTransmitSegment().
 *  \reentrant  FALSE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueueTransmitSegment(
  SoAd_SizeOfNPduUdpTxType NPduIdx);

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueFinishTransmitSegment()
**********************************************************************************************************************/
/*! \brief      Finishes nPdu segment transmission by calling TxConfirmation for all transmitted PDU elements in queue.
 *  \details    -
 *  \param[in]  NPduIdx                 NPdu index.
 *                                      [range: NPduIdx < SoAd_GetSizeOfNPduUdpTx()]
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxNPduUdp_QueueFinishTransmitSegment(
  SoAd_SizeOfNPduUdpTxType NPduIdx);

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueTxConfirmation()
**********************************************************************************************************************/
/*! \brief      Handles TxConfirmation for a PDU located in a nPdu queue.
 *  \details    -
 *  \param[in]  SoConIdx                Socket connection index.
 *                                      [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  PduRouteIdx             PDU route index.
 *                                      [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \param[in]  AllowReconnect          Indicates if socket connection reconnection is allowed if required.
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxNPduUdp_QueueTxConfirmation(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfPduRouteType PduRouteIdx,
  boolean AllowReconnect);

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_BufferAddElement()
**********************************************************************************************************************/
/*! \brief      Adds a PDU as element to a nPdu buffer.
 *  \details    -
 *  \param[in]  PduRouteIdx             PDU route index.
 *                                      [range: PduRouteIdx < SoAd_GetSizeOfPduRoute()]
 *  \param[in]  PduRouteDestIdx         PduRouteDest index.
 *                                      [range: PduRouteDestIdx < SoAd_GetSizeOfPduRouteDest()]
 *  \param[in]  PduInfoPtr              Pointer to PDU.
 *  \return     SOAD_NPDU_OK            Added element to nPdu successfully.
 *  \return     SOAD_NPDU_OVFL_NEW      New PDU exceeds nPdu size.
 *  \return     SOAD_NPDU_NOT_OK        Cannot create nPdu since timeout list size is not sufficient to store nPdu.
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(SoAd_NPduReturnType, SOAD_CODE) SoAd_TxNPduUdp_BufferAddElement(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr);

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_BufferSend()
**********************************************************************************************************************/
/*! \brief      Sends a nPdu stored in a buffer.
 *  \details    -
 *  \param[in]  NPduIdx                 NPdu index.
 *                                      [range: NPduIdx < SoAd_GetSizeOfNPduUdpTx()]
 *  \context    TASK|ISR2
 *  \reentrant  FALSE
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxNPduUdp_BufferSend(
  SoAd_SizeOfNPduUdpTxType NPduIdx);

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_CopyTxData()
**********************************************************************************************************************/
/*! \brief          Copies data to provided transmission buffer of a nPdu.
 *  \details        Uses "BufLengthPtr" to update length if less data is copied to provided buffer.
 *  \param[in]      SoConIdx            Socket connection index.
 *                                      [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]      BufPtr              Pointer to buffer of provided transmission buffer.
 *  \param[in,out]  BufLengthPtr        Pointer to length of provided transmission buffer.
 *  \return         BUFREQ_OK           Copy request accepted.
 *  \return         BUFREQ_E_NOT_OK     Copy request not accepted.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different socket connection indexes, FALSE for same socket connection index.
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_TxNPduUdp_CopyTxData(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) BufLengthPtr);

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueCopyTxData()
**********************************************************************************************************************/
/*! \brief          Copies data to provided transmission buffer of a nPdu queue.
 *  \details        Uses "BufLengthPtr" to update length if less data is copied to provided buffer.
 *  \param[in]      NPduIdx             NPdu index.
 *                                      [range: NPduIdx < SoAd_GetSizeOfNPduUdpTx()]
 *  \param[in]      BufPtr              Pointer to buffer of provided transmission buffer.
 *  \param[in,out]  BufLengthPtr        Pointer to length of provided transmission buffer.
 *  \return         BUFREQ_OK           Copy request accepted.
 *  \return         BUFREQ_E_NOT_OK     Copy request not accepted.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different nPdu indexes, FALSE for same nPdu index.
**********************************************************************************************************************/
/* PRQA S 779 4 */ /* MD_MSR_5.1_779 */
SOAD_LOCAL_INLINE FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueueCopyTxData(
  SoAd_SizeOfNPduUdpTxType NPduIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) BufLengthPtr);

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueCopyTxDataBuffer()
**********************************************************************************************************************/
/*! \brief          Copies data to provided transmission buffer of a nPdu queue element stored in nPdu buffer.
 *  \details        Uses "BufLengthPtr" to decrement length of available provided transmission buffer.
 *  \param[in]      NPduQueueIdx        NPdu queue index.
 *                                      [range: NPduQueueIdx < SoAd_GetSizeOfNPduUdpTxQueue()]
 *  \param[in]      BufPtr              Pointer to buffer of provided transmission buffer.
 *  \param[in,out]  BufLengthPtr        Pointer to length of provided transmission buffer.
 *  \return         BUFREQ_OK           Copy request accepted.
 *  \return         BUFREQ_E_OVFL       Provided buffer is not sufficient.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different nPdu indexes, FALSE for same nPdu index.
**********************************************************************************************************************/
/* PRQA S 779 5 */ /* MD_MSR_5.1_779 */
SOAD_LOCAL_INLINE FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueueCopyTxDataBuffer(
  SoAd_SizeOfNPduUdpTxQueueType NPduQueueIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) BufLengthPtr);

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueCopyTxDataTrigger()
**********************************************************************************************************************/
/*! \brief          Copies data to provided transmission buffer of a nPdu queue element to be retrieved via trigger
 *                  transmit.
 *  \details        Uses "BufLengthPtr" to decrement length of available provided transmission buffer.
 *  \param[in]      NPduIdx             NPdu index.
 *                                      [range: NPduIdx < SoAd_GetSizeOfNPduUdpTx()]
 *  \param[in]      NPduQueueIdx        NPdu queue index.
 *                                      [range: NPduQueueIdx < SoAd_GetSizeOfNPduUdpTxQueue()]
 *  \param[in]      BufPtr              Pointer to buffer of provided transmission buffer.
 *  \param[in,out]  BufLengthPtr        Pointer to length of provided transmission buffer.
 *  \return         BUFREQ_OK           Copy request accepted.
 *  \return         BUFREQ_E_NOT_OK     Copy request not accepted.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE for different nPdu indexes, FALSE for same nPdu index.
**********************************************************************************************************************/
/* PRQA S 779 5 */ /* MD_MSR_5.1_779 */
SOAD_LOCAL_INLINE FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueueCopyTxDataTrigger(
  SoAd_SizeOfNPduUdpTxType NPduIdx,
  SoAd_SizeOfNPduUdpTxQueueType NPduQueueIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) BufLengthPtr);

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueCopyTxDataTriggerPrepare()
**********************************************************************************************************************/
/*! \brief          Prepares to copy data to provided transmission buffer of a nPdu queue element to be retrieved via
 *                  trigger transmit.
 *  \details        -
 *  \param[in]      NPduIdx             NPdu index.
 *                                      [range: NPduIdx < SoAd_GetSizeOfNPduUdpTx()]
 *  \param[in]      BufPtr              Pointer to buffer of provided transmission buffer.
 *  \param[in,out]  BufLength           Length of provided transmission buffer.
 *  \param[in,out]  PduInfoPtr          Pointer to provided transmission buffer used in trigger transmit call.
 *  \return         BUFREQ_OK           Preparation succeeded.
 *  \return         BUFREQ_E_OVFL       Preparation failed because provided buffer size is not sufficient.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
**********************************************************************************************************************/
/* PRQA S 779 5 */ /* MD_MSR_5.1_779 */
SOAD_LOCAL_INLINE FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueueCopyTxDataTriggerPrepare(
  SoAd_SizeOfNPduUdpTxType NPduIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 BufLength,
  P2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr);

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueCopyTxDataTriggerCall()
**********************************************************************************************************************/
/*! \brief          Calls trigger transmit to copy data to provided transmission buffer of a nPdu queue element to be
 *                  retrieved via trigger transmit.
 *  \details        Uses "BufLengthPtr" to decrement length of available provided transmission buffer.
 *  \param[in]      NPduIdx             NPdu index.
 *                                      [range: NPduIdx < SoAd_GetSizeOfNPduUdpTx()]
 *  \param[in]      NPduQueueIdx        NPdu queue index.
 *                                      [range: NPduQueueIdx < SoAd_GetSizeOfNPduUdpTxQueue()]
 *  \param[in,out]  BufLengthPtr        Pointer to length of provided transmission buffer.
 *  \param[in,out]  PduInfoPtr          Pointer to provided transmission buffer used in trigger transmit call.
 *  \return         BUFREQ_OK           Trigger transmit call succeeded.
 *  \return         BUFREQ_E_OVFL       Trigger transmit call failed.
 *  \return         BUFREQ_E_NOT_OK     Trigger transmit call returned invalid parameter.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
**********************************************************************************************************************/
/* PRQA S 779 5 */ /* MD_MSR_5.1_779 */
SOAD_LOCAL_INLINE FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueueCopyTxDataTriggerCall(
  SoAd_SizeOfNPduUdpTxType NPduIdx,
  SoAd_SizeOfNPduUdpTxQueueType NPduQueueIdx,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) BufLengthPtr,
  P2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr);

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueCopyTxDataTriggerAddPduHeader()
**********************************************************************************************************************/
/*! \brief          Adds PDU header to provided transmission buffer of a nPdu queue element to be retrieved via trigger
 *                  transmit.
 *  \details        Uses "BufLengthPtr" to decrement length of available provided transmission buffer.
 *  \param[in]      NPduIdx             NPdu index.
 *                                      [range: NPduIdx < SoAd_GetSizeOfNPduUdpTx()]
 *  \param[in]      NPduQueueIdx        NPdu queue index.
 *                                      [range: NPduQueueIdx < SoAd_GetSizeOfNPduUdpTxQueue()]
 *  \param[in]      BufPtr              Pointer to buffer of provided transmission buffer.
 *  \param[in,out]  BufLengthPtr        Pointer to length of provided transmission buffer.
 *  \param[in]      PduInfoPtr          Pointer to PDU copied in trigger transmit call.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
**********************************************************************************************************************/
/* PRQA S 779 6 */ /* MD_MSR_5.1_779 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxNPduUdp_QueueCopyTxDataTriggerAddPduHeader(
  SoAd_SizeOfNPduUdpTxType NPduIdx,
  SoAd_SizeOfNPduUdpTxQueueType NPduQueueIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) BufLengthPtr,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr);

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_BufferCopyTxData()
**********************************************************************************************************************/
/*! \brief      Copies data to provided transmission buffer of a nPdu buffer.
 *  \details    -
 *  \param[in]  NPduIdx         NPdu index.
 *                              [range: NPduIdx < SoAd_GetSizeOfNPduUdpTx()]
 *  \param[in]  BufPtr          Pointer to buffer of provided transmission buffer.
 *  \param[in]  BufLength       Length of provided transmission buffer.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different nPdu indexes, FALSE for same nPdu index.
**********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxNPduUdp_BufferCopyTxData(
  SoAd_SizeOfNPduUdpTxType NPduIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 BufLength);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

 /*********************************************************************************************************************
 *  SoAd_Tx_CopyTxDataCheckParameter()
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_Tx_CopyTxDataCheckParameter(
  SoAd_SizeOfSoConType SoConIdx,
  uint16 BufLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if no socket connection is active on requested socket. */
  if ( SoConIdx == SoAd_GetSizeOfSoCon() )
  {
    retVal = E_NOT_OK;
  }
  /* #11 Check socket connection states otherwise. */
  else if ( (SoAd_GetModeOfSoConDyn(SoConIdx) != SOAD_SOCON_ONLINE) ||
    (SoAd_GetCloseModeOfSoConDyn(SoConIdx) != SOAD_CLOSE_NONE) )
  {
    retVal = E_NOT_OK;
  }
  /* #12 Check for PDU route otherwise. */
  else if ( SoAd_IsTxMgtUsedOfSoCon(SoConIdx) == FALSE )
  {
    retVal = E_NOT_OK;
  }
  /* #13 Check buffer length otherwise. */
  else if ( BufLength > SoAd_GetTxBytesPendingOfTxMgt(SoAd_GetTxMgtIdxOfSoCon(SoConIdx)) )
  {
    retVal = E_NOT_OK;
  }
  /* #14 Indicate that parameters are correct. */
  else
  {
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_Tx_CopyTxDataCheckParameter() */

/**********************************************************************************************************************
 *  SoAd_Tx_CopyTxDataPduHeader()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_Tx_CopyTxDataPduHeader(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfPduRouteType PduRouteIdx,
  P2VAR(uint8*, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) BufLengthPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_PduRouteDestIterType pduRouteDestIter;
  SoAd_SizeOfTxMgtType      txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(SoConIdx);
  PduLengthType             bytesCopied;
  PduLengthType             bytesToCopy;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate data length which is already copied to lower layer. */
  bytesCopied = (PduLengthType)(SoAd_GetTxBytesLenOfTxMgt(txMgtIdx) - SoAd_GetTxBytesPendingOfTxMgt(txMgtIdx));

  /* #20 Check if PDU header is not yet copied. */
  if ( bytesCopied < SOAD_PDU_HDR_SIZE )
  {
    /* #30 Iterate over all PduRouteDests of PduRoute to find the corresponding PduRouteDest. */
    for ( pduRouteDestIter = SoAd_GetPduRouteDestStartIdxOfPduRoute(PduRouteIdx);
      pduRouteDestIter < SoAd_GetPduRouteDestEndIdxOfPduRoute(PduRouteIdx);
      pduRouteDestIter++ )
    {
      /* #40 Check if current PduRouteDest is the corresponding PduRouteDest. */
      if ( SoAd_GetSoConIdxOfPduRouteDest(pduRouteDestIter) == SoConIdx )
      {
        /* #50 Calculate PDU header snippet length which can be copied in this context. */
        bytesToCopy = SOAD_PDU_HDR_SIZE - bytesCopied;
        if ( bytesToCopy > *BufLengthPtr )
        {
          bytesToCopy = *BufLengthPtr;
        }

        /* #60 Copy PDU header snippet of PduRouteDest to provided buffer. */
        SoAd_Util_CopyPduHdr2Buf(SoAd_GetTxPduHdrIdOfPduRouteDest(pduRouteDestIter),                                   /* SBSW_SOAD_POINTER_FORWARD */
          (SoAd_GetTxBytesLenOfTxMgt(txMgtIdx) - SOAD_PDU_HDR_SIZE),
          *BufPtr,
          bytesCopied,
          bytesToCopy);

        /* #70 Decrement pending data of PDU. */
        SoAd_SetTxBytesPendingOfTxMgt(txMgtIdx, SoAd_GetTxBytesPendingOfTxMgt(txMgtIdx) - bytesToCopy);                /* SBSW_SOAD_OPTIONAL_CSL03 */

        /* #80 Decrement provided buffer length. */
        *BufLengthPtr -= bytesToCopy;                                                                                  /* SBSW_SOAD_POINTER_WRITE */

        /* #90 Update buffer pointer to position after PDU header. */
        *BufPtr = &(*BufPtr)[bytesToCopy];                                                                             /* SBSW_SOAD_POINTER_WRITE */

        break;
      }
    }
  }
} /* SoAd_Tx_CopyTxDataPduHeader() */

/**********************************************************************************************************************
 *  SoAd_Tx_CheckSoConStates()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_Tx_CheckSoConStates(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType sockIdx = SoAd_GetSocketIdxOfSoCon(SoConIdx);
  Std_ReturnType        retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if socket is open. */
  if ( SoAd_GetStateOfSocketDyn(sockIdx) == SOAD_SOCK_STATE_ESTABLISHED )
  {
    /* #20 Check if socket connection is online. */
    if ( SoAd_GetModeOfSoConDyn(SoConIdx) == SOAD_SOCON_ONLINE )
    {
      /* #30 Check if socket connection is not requested to be closed. */
      if ( SoAd_GetCloseModeOfSoConDyn(SoConIdx) == SOAD_CLOSE_NONE )
      {
        retVal = E_OK;
      }
    }
  }

  return retVal;
} /* SoAd_Tx_CheckSoConStates() */

/**********************************************************************************************************************
 *  SoAd_Tx_UdpImmediateIfTxConfirmation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_Tx_UdpImmediateIfTxConfirmation(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfPduRouteDestBySoConIndType pduRouteDestBySoConIndStartIdx;
  SoAd_SizeOfPduRouteType               pduRouteIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if immediate IF TxConfirmation is configured. */
  if ( SoAd_IsImmedIfTxConfOfSocketUdp(SoAd_GetSocketUdpIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx))) == TRUE )
  {
    /* #20 Get first and only PduRoute. */
    pduRouteDestBySoConIndStartIdx = SoAd_GetPduRouteDestBySoConIndStartIdxOfSoCon(SoConIdx);
    pduRouteIdx = SoAd_GetPduRouteIdxOfPduRouteDest(SoAd_GetPduRouteDestBySoConInd(pduRouteDestBySoConIndStartIdx));

    /* #30 Reconnect socket connection if socket connection has auto setup enabled and wildcards configured. */
    SoAd_SoCon_Reconnect(SoConIdx);

    /* #40 Call TxConfirmation if configured. */
    if ( SoAd_IsTxConfEnabledOfPduRoute(pduRouteIdx) == TRUE )
    {
      SoAd_GetIfTxConfirmationCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfPduRoute(pduRouteIdx))(                           /* SBSW_SOAD_FUNCTION_PTR */
        SoAd_GetTxConfPduIdOfPduRoute(pduRouteIdx));
    }
  }
} /* SoAd_Tx_UdpImmediateIfTxConfirmation() */

/**********************************************************************************************************************
 *  SoAd_TxIf_CheckParameter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_CheckParameter(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  PduLengthType PduLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check module state. */
  if ( SoAd_State == SOAD_STATE_INIT )
  {
    /* #20 Check PDU length. */
    if ( SoAd_TxIf_CheckTxPduLength(PduRouteIdx, PduLength) == E_OK )
    {
      /* #30 Check transmission state. */
      if ( SoAd_TxIf_CheckTxState(PduRouteIdx) == E_OK )
      {
        retVal = E_OK;
      }
    }
  }

  return retVal;
} /* SoAd_TxIf_CheckParameter() */

/**********************************************************************************************************************
 *  SoAd_TxIf_CheckTxPduLength()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 3206 2 */ /* MD_SoAd_3206 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_CheckTxPduLength(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  PduLengthType PduLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8           minLength;
  Std_ReturnType  retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate minimum length in case PDU Header option is used. */
  if ( SoAd_IsAllPduRouteDestWithPduHdrOfPduRoute(PduRouteIdx) == TRUE )
  {
    if ( SoAd_IsMetaDataTxEnabledOfPduRoute(PduRouteIdx) == TRUE )
    {
      minLength = 2u;
    }
    else
    {
      minLength = 0u;
    }
  }
  /* #11 Calculate minimum length in case PDU Header option is not used otherwise. */
  else
  {
    if ( SoAd_IsMetaDataTxEnabledOfPduRoute(PduRouteIdx) == TRUE )
    {
      minLength = 3u;
    }
    else
    {
      minLength = 1u;
    }
  }

  /* #20 Validate minimum length. */
  if ( PduLength >= minLength )
  {
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_TxIf_CheckTxPduLength() */

/**********************************************************************************************************************
 *  SoAd_TxIf_CheckTxState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_CheckTxState(
  SoAd_SizeOfPduRouteType PduRouteIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfPduRouteDestType pduRouteDestIdx = SoAd_GetPduRouteDestStartIdxOfPduRoute(PduRouteIdx);
  SoAd_SizeOfSoConType        soConIdx = SoAd_GetSoConIdxOfPduRouteDest(pduRouteDestIdx);
  Std_ReturnType              retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if a TxConfirmation is pending on the requested PDU */
  if ( (SoAd_IsNPduUdpTxUsedOfSoCon(soConIdx) == FALSE) ||
    (SoAd_IsIfTriggerTransmitEnabledOfPduRoute(PduRouteIdx) == FALSE) )
  {
    if ( (SoAd_GetPendingTxConfNumOfPduRouteDyn(PduRouteIdx) != 0u) ||
      (SoAd_IsPendingTxConfMainOfPduRouteDyn(PduRouteIdx) == TRUE) )
    {
      retVal = E_NOT_OK;

      /* switch off TxConfirmation if faster transmission is required */
    }
  }

  return retVal;
} /* SoAd_TxIf_CheckTxState() */

/**********************************************************************************************************************
 *  SoAd_TxIf_TransmitPdu()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_TransmitPdu(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) PduInfoPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_PduRouteDestIterType   pduRouteDestIter;
  uint16                      pduRouteDestsDisabled = 0u;
  SoAd_SizeOfPduRouteDestType pduRouteDestIdx = SoAd_GetSizeOfPduRouteDest();
  Std_ReturnType              retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if meta data are used to send over a specific PduRouteDest. */
  if ( SoAd_IsMetaDataTxEnabledOfPduRoute(PduRouteIdx) == TRUE )
  {
    /* #100 Get PduRouteDest by extracting SoConId from meta data. */
    if ( SoAd_TxIf_GetPduRouteDestIdxByMetaData(PduRouteIdx, PduInfoPtr, &pduRouteDestIdx) == E_OK )                   /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
    {
      /* #1000 Check if any routing group is enabled on the PduRouteDest. */
      if ( SoAd_RouteGrp_CheckAnyRoutGrpOnPduRouteDestEnabled(pduRouteDestIdx) == TRUE )
      {
        /* #10000 If enabled transmit PDU over PduRouteDest. */
        PduInfoType pduInfo;

        pduInfo.SduDataPtr = PduInfoPtr->SduDataPtr;
        pduInfo.SduLength = (PduLengthType)(PduInfoPtr->SduLength - SOAD_TX_META_DATA_LEN);

        retVal = SoAd_TxIf_TransmitPduRouteDest(pduRouteDestIdx, &pduInfo, ErrorIdPtr);                                /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
      }
      else
      {
        /* #10001 If disabled reject transmit request. */
        retVal = E_NOT_OK;
      }
    }
    else
    {
      retVal = E_NOT_OK;
    }
  }
  /* #11 Send over all PduRouteDests otherwise. */
  else
  {
    /* #110 Iterate over all PduRouteDests. */
    for ( pduRouteDestIter = SoAd_GetPduRouteDestStartIdxOfPduRoute(PduRouteIdx);
      pduRouteDestIter < SoAd_GetPduRouteDestEndIdxOfPduRoute(PduRouteIdx);
      pduRouteDestIter++ )
    {
      /* #1100 Check if any routing group is enabled on the PduRouteDest. */
      if ( FALSE == SoAd_RouteGrp_CheckAnyRoutGrpOnPduRouteDestEnabled((SoAd_SizeOfPduRouteDestType)pduRouteDestIter) )
      { /* all routing groups for this PduRouteDest are disabled */
        /* discard PDU for this PduRouteDest but consider that transmission is successful */
        /* count all disabled PduRouteDests */
        pduRouteDestsDisabled++;
      }
      else
      {
        /* #11000 If enabled transmit PDU over PduRouteDest. */
        retVal |= SoAd_TxIf_TransmitPduRouteDest((SoAd_SizeOfPduRouteDestType)pduRouteDestIter,                        /* SBSW_SOAD_POINTER_FORWARD */
          PduInfoPtr, ErrorIdPtr);
      }
    }

    /* #111 If no routing group is enabled for any PduRouteDest reject transmit request. */
    if ( pduRouteDestsDisabled ==
      (SoAd_GetPduRouteDestEndIdxOfPduRoute(PduRouteIdx) - SoAd_GetPduRouteDestStartIdxOfPduRoute(PduRouteIdx)) )
    { /* all PduRouteDests are disabled */
      /* return E_NOT_OK */
      retVal = E_NOT_OK;
    }
  }

  return retVal;
} /* SoAd_TxIf_TransmitPdu() */

/**********************************************************************************************************************
 *  SoAd_TxIf_GetPduRouteDestIdxByMetaData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_GetPduRouteDestIdxByMetaData(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) PduInfoPtr,
  P2VAR(SoAd_SizeOfPduRouteDestType, AUTOMATIC, SOAD_APPL_DATA) PduRouteDestIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_PduRouteDestIterType pduRouteDestIter;
  SoAd_SoConIdType          soConId;
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Extract SoConId from meta data. */
  IPBASE_GET_UINT16(PduInfoPtr->SduDataPtr, (PduInfoPtr->SduLength - SOAD_TX_META_DATA_LEN), soConId);                 /* SBSW_SOAD_POINTER_FORWARD */

  /* #11 Check if extracted SoConId is valid. */
  if ( (soConId < SoAd_GetSizeOfSoConMap())
#if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    && (SoAd_IsInvalidHndOfSoConMap(soConId) == FALSE)
#endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    /* #110 Iterate over all PduRouteDests to find the PduRouteDest with extracted SoConId. */
    for ( pduRouteDestIter = SoAd_GetPduRouteDestStartIdxOfPduRoute(PduRouteIdx);
      pduRouteDestIter < SoAd_GetPduRouteDestEndIdxOfPduRoute(PduRouteIdx);
      pduRouteDestIter++ )
    {
      if ( (SoAd_SoConIdType)soConId == SoAd_GetSoConIdOfSoCon(SoAd_GetSoConIdxOfPduRouteDest(pduRouteDestIter)) )
      {
        *PduRouteDestIdxPtr = (SoAd_SizeOfPduRouteDestType)pduRouteDestIter;                                           /* SBSW_SOAD_POINTER_WRITE */
        retVal = E_OK;
        break;
      }
    }
  }

  return retVal;
} /* SoAd_TxIf_GetPduRouteDestIdxByMetaData() */

/**********************************************************************************************************************
 *  SoAd_TxIf_TransmitPduRouteDest()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_TransmitPduRouteDest(
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx = SoAd_GetSoConIdxOfPduRouteDest(PduRouteDestIdx);
  Std_ReturnType        retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check socket connection specific parameter. */
  if ( SoAd_Tx_CheckSoConStates(soConIdx) == E_OK )
  {
#if ( SOAD_TCP == STD_ON )
    /* #20 Handle transmission for TCP socket connection. */
    if ( SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx)) == TRUE )
    {
      retVal = SoAd_TxIf_TcpTransmit(PduRouteDestIdx, PduInfoPtr);                                                     /* SBSW_SOAD_POINTER_FORWARD */
    }
    else
#endif /* SOAD_TCP == STD_ON */
    /* #21 Handle transmission for UDP socket connection otherwise. */
    {
      retVal = SoAd_TxIf_UdpTransmit(PduRouteDestIdx, PduInfoPtr, ErrorIdPtr);                                         /* SBSW_SOAD_POINTER_FORWARD */
    }
  }

  return retVal;
} /* SoAd_TxIf_TransmitPduRouteDest() */

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_TxIf_TcpTransmit()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_TcpTransmit(
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx = SoAd_GetSoConIdxOfPduRouteDest(PduRouteDestIdx);
  SoAd_SizeOfSocketType sockIdx = SoAd_GetSocketIdxOfSoCon(soConIdx);
  Std_ReturnType        retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent read/write issues for active transmission on socket. */
  SOAD_BEGIN_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Check if no transmission is active on socket. */
  if ( SoAd_GetSoConTxActiveIdxOfSocketDyn(sockIdx) == SoAd_GetSizeOfSoCon() )
  {
    /* #30 Set transmission active on socket. */
    SoAd_SetSoConTxActiveIdxOfSocketDyn(sockIdx, soConIdx);                                                            /* SBSW_SOAD_CSL03 */

    /* #40 Leave critical section. */
    SOAD_END_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #50 Prepare transmission. */
    if ( SoAd_TxIf_TcpPrepareTransmit(PduRouteDestIdx, PduInfoPtr) == E_OK )                                           /* SBSW_SOAD_POINTER_FORWARD */
    {
      /* #60 Transmit IF-PDU on TCP socket connection. */
      retVal = SoAd_TxIf_TcpCallTransmit(PduRouteDestIdx);
    }

    /* #70 Deactivate transmission on socket. */
    SoAd_SetSoConTxActiveIdxOfSocketDyn(sockIdx, SoAd_GetSizeOfSoCon());                                               /* SBSW_SOAD_CSL03 */
  }
  /* #21 Leave critical section otherwise. */
  else
  {
    SOAD_END_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }

  return retVal;
} /* SoAd_TxIf_TcpTransmit() */

/**********************************************************************************************************************
 *  SoAd_TxIf_TcpPrepareTransmit()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_TcpPrepareTransmit(
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfPduRouteType pduRouteIdx = SoAd_GetPduRouteIdxOfPduRouteDest(PduRouteDestIdx);
  SoAd_SizeOfSoConType    soConIdx = SoAd_GetSoConIdxOfPduRouteDest(PduRouteDestIdx);
  SoAd_SizeOfTxMgtType    txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(soConIdx);
  Std_ReturnType          retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if transmission via trigger transmit is configured. */
  if ( SoAd_IsIfTriggerTransmitEnabledOfPduRoute(pduRouteIdx) == TRUE )
  {
    PduInfoType                       pduInfo;
    PduLengthType                     dataLen;
    SoAd_SizeOfTriggerTxBufConfigType triggerTxBufConfigIdx = SoAd_GetTriggerTxBufConfigIdxOfSoCon(soConIdx);
    SoAd_SizeOfTriggerTxBufType       triggerTxBufStartIdx;
    SoAd_SizeOfTriggerTxBufType       triggerTxBufSize;
    uint8                             minExpectedLen;

    /* #20 Prepare local trigger transmit buffer. */
    triggerTxBufStartIdx = SoAd_GetTriggerTxBufStartIdxOfTriggerTxBufConfig(triggerTxBufConfigIdx);
    triggerTxBufSize = SoAd_GetTriggerTxBufEndIdxOfTriggerTxBufConfig(triggerTxBufConfigIdx) - triggerTxBufStartIdx;

    pduInfo.SduDataPtr = SoAd_GetAddrTriggerTxBuf(triggerTxBufStartIdx);
    pduInfo.SduLength = (PduLengthType)triggerTxBufSize;

    /* #30 Call trigger transmit and check if call succeeds. */
    if ( SoAd_GetIfTriggerTransmitCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfPduRoute(pduRouteIdx))(                       /* SBSW_SOAD_FUNCTION_PTR */
      SoAd_GetTxConfPduIdOfPduRoute(pduRouteIdx), &pduInfo) == E_OK )
    {
      /* #40 Calculate minimum exptected copied length considering PDU header. */
      if ( SoAd_IsPduHdrEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx)) == TRUE )
      {
        minExpectedLen = 0u;
        dataLen = SOAD_PDU_HDR_SIZE;
      }
      else
      {
        minExpectedLen = 1u;
        dataLen = 0u;
      }

      /* #50 Check if data copied by upper layer via trigger transmit is valid. */
      if ( (pduInfo.SduDataPtr != NULL_PTR) && (pduInfo.SduLength >= minExpectedLen) &&
        (pduInfo.SduLength <= triggerTxBufSize) )
      {
        /* #60 Prepare for call to CopyTxData. */
        dataLen += pduInfo.SduLength;
        SoAd_SetPduRouteIdxOfTxMgt(txMgtIdx, pduRouteIdx);                                                             /* SBSW_SOAD_OPTIONAL_CSL03 */
        SoAd_SetTxBytesLenOfTxMgt(txMgtIdx, dataLen);                                                                  /* SBSW_SOAD_OPTIONAL_CSL03 */
        SoAd_SetTxBytesPendingOfTxMgt(txMgtIdx, dataLen);                                                              /* SBSW_SOAD_OPTIONAL_CSL03 */
        SoAd_SetTxBufPtrOfTxMgt(txMgtIdx, SoAd_GetAddrTriggerTxBuf(triggerTxBufStartIdx));                             /* SBSW_SOAD_OPTIONAL_CSL03 */
      }
      /* #51 Return negative transmission result otherwise. */
      else
      {
        retVal = E_NOT_OK;
      }
    }
    /* #31 Return negative transmission result otherwise. */
    else
    {
      retVal = E_NOT_OK;
    }
  }
  else
  /* #11 Prepare for call to CopyTxData for direct transmission otherwise. */
  {
    SoAd_SetPduRouteIdxOfTxMgt(txMgtIdx, pduRouteIdx);                                                                 /* SBSW_SOAD_OPTIONAL_CSL03 */
    SoAd_SetTxBufPtrOfTxMgt(txMgtIdx, PduInfoPtr->SduDataPtr);                                                         /* SBSW_SOAD_OPTIONAL_CSL03 */

    if ( SoAd_IsPduHdrEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx)) == TRUE )
    {
      SoAd_SetTxBytesLenOfTxMgt(txMgtIdx, PduInfoPtr->SduLength + SOAD_PDU_HDR_SIZE);                                  /* SBSW_SOAD_OPTIONAL_CSL03 */
      SoAd_SetTxBytesPendingOfTxMgt(txMgtIdx, PduInfoPtr->SduLength + SOAD_PDU_HDR_SIZE);                              /* SBSW_SOAD_OPTIONAL_CSL03 */
    }
    else
    {
      SoAd_SetTxBytesLenOfTxMgt(txMgtIdx, PduInfoPtr->SduLength);                                                      /* SBSW_SOAD_OPTIONAL_CSL03 */
      SoAd_SetTxBytesPendingOfTxMgt(txMgtIdx, PduInfoPtr->SduLength);                                                  /* SBSW_SOAD_OPTIONAL_CSL03 */
    }
  }

  return retVal;
} /* SoAd_TxIf_TcpPrepareTransmit() */

/**********************************************************************************************************************
 *  SoAd_TxIf_TcpCallTransmit()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_TcpCallTransmit(
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfPduRouteType pduRouteIdx = SoAd_GetPduRouteIdxOfPduRouteDest(PduRouteDestIdx);
  SoAd_SizeOfSoConType    soConIdx = SoAd_GetSoConIdxOfPduRouteDest(PduRouteDestIdx);
  SoAd_SizeOfTxMgtType    txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(soConIdx);
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Try to reserve a element in the Tx TCP queue. */
  if ( SoAd_TxTcpQueue_ReserveNextElement(soConIdx, pduRouteIdx) == E_OK )
  {
    /* #20 Try to transmit data and check if transmission succeeds. */
    if ( SoAd_TcpIp_TcpTransmit(soConIdx, SoAd_GetTxBytesLenOfTxMgt(txMgtIdx), TRUE) == E_OK )
    {
      /* #30 Set the reserved element in the Tx TCP queue. */
      SoAd_TxTcpQueue_SetElement(soConIdx, pduRouteIdx, SoAd_GetTxBytesLenOfTxMgt(txMgtIdx), FALSE);

      /* #40 Add a pending TxConfirmation for the transmitted PDU. */
      SoAd_TxIf_AddPendingConf(pduRouteIdx, soConIdx);

      retVal = E_OK;
    }
    /* #21 Remove reserved element from Tx TCP queue otherwise. */
    else
    {
      SoAd_TxTcpQueue_SetElement(soConIdx, pduRouteIdx, 0, TRUE);
    }
  }

  /* #50 Finish transmission on socket connection. */
  SoAd_SetPduRouteIdxOfTxMgt(txMgtIdx, SoAd_GetSizeOfPduRoute());                                                      /* SBSW_SOAD_OPTIONAL_CSL03 */
  SoAd_SetTxBufPtrOfTxMgt(txMgtIdx, NULL_PTR);                                                                         /* SBSW_SOAD_OPTIONAL_CSL03 */

  return retVal;
} /* SoAd_TxIf_TcpCallTransmit() */

/**********************************************************************************************************************
 *  SoAd_TxIf_TcpCopyTxData()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxIf_TcpCopyTxData(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 BufLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  PduLengthType           bytesCopied;
  SoAd_SizeOfTxMgtType    txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfPduRouteType pduRouteIdx = SoAd_GetPduRouteIdxOfTxMgt(txMgtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if PDU header is used. */
  if ( SoAd_IsPduHdrEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) == TRUE )
  {
    /* #100 Copy PDU header to provided buffer. */
    SoAd_Tx_CopyTxDataPduHeader(SoConIdx, pduRouteIdx, &BufPtr, &BufLength);                                           /* SBSW_SOAD_POINTER_FORWARD */

    /* #101 Calculcate number of copied bytes considering PDU header and check if PDU header is copied completely. */
    bytesCopied = (PduLengthType)(SoAd_GetTxBytesLenOfTxMgt(txMgtIdx) - SoAd_GetTxBytesPendingOfTxMgt(txMgtIdx));
    if ( bytesCopied >= SOAD_PDU_HDR_SIZE )
    {
      bytesCopied -= SOAD_PDU_HDR_SIZE;

      /* #102 Copy PDU data from local transmission buffer if provided buffer is sufficient to copy data. */
      if ( BufLength > 0u )
      {
        SOAD_P2VAR(uint8) txBufPtr = SoAd_GetTxBufPtrOfTxMgt(txMgtIdx);

        IpBase_Copy(SOAD_A_P2VAR(IpBase_CopyDataType)BufPtr,                                                           /* SBSW_SOAD_POINTER_AND_TX_BUFFER_POINTER_FORWARD */
          SOAD_A_P2CONST(IpBase_CopyDataType)&txBufPtr[bytesCopied],
          BufLength);
      }
    }
  }
  else
  /* #11 Copy PDU data otherwise. */
  {
    SOAD_P2VAR(uint8) txBufPtr = SoAd_GetTxBufPtrOfTxMgt(txMgtIdx);

    /* #110 Calculate number of copied bytes. */
    bytesCopied = (PduLengthType)(SoAd_GetTxBytesLenOfTxMgt(txMgtIdx) - SoAd_GetTxBytesPendingOfTxMgt(txMgtIdx));

    /* #111 Copy PDU data from local transmission buffer. */
    IpBase_Copy(SOAD_A_P2VAR(IpBase_CopyDataType)BufPtr,                                                               /* SBSW_SOAD_POINTER_AND_TX_BUFFER_POINTER_FORWARD */
      SOAD_A_P2CONST(IpBase_CopyDataType)&txBufPtr[bytesCopied],
      BufLength);
  }

  /* #20 Decrement pending data to be transmitted. */
  SoAd_SetTxBytesPendingOfTxMgt(txMgtIdx, (PduLengthType)(SoAd_GetTxBytesPendingOfTxMgt(txMgtIdx) - BufLength));       /* SBSW_SOAD_OPTIONAL_CSL03 */
} /* SoAd_TxIf_TcpCopyTxData() */
#endif /* SOAD_TCP == STD_ON */


/**********************************************************************************************************************
 *  SoAd_TxIf_UdpTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_UdpTransmit(
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx = SoAd_GetSoConIdxOfPduRouteDest(PduRouteDestIdx);
  Std_ReturnType        retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Update alive timeout. */
  SoAd_SoCon_UpdateUdpAliveTimeout(soConIdx);

  /* #20 Handle transmission if nPdu is configured. */
  if ( SoAd_IsNPduUdpTxUsedOfSoCon(soConIdx) == TRUE )
  {
    retVal = SoAd_TxIf_UdpTransmitNPdu(PduRouteDestIdx, PduInfoPtr, ErrorIdPtr);                                       /* SBSW_SOAD_POINTER_FORWARD */
  }
  else
  /* #21 Handle transmission of single PDU otherwise. */
  {
    retVal = SoAd_TxIf_UdpTransmitPdu(PduRouteDestIdx, PduInfoPtr);                                                    /* SBSW_SOAD_POINTER_FORWARD */
  }

  return retVal;
} /* SoAd_TxIf_UdpTransmit() */

/**********************************************************************************************************************
 *  SoAd_TxIf_UdpTransmitNPdu()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_UdpTransmitNPdu(
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType    soConIdx = SoAd_GetSoConIdxOfPduRouteDest(PduRouteDestIdx);
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConIdx);
  PduLengthType           dataLen;
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate PDU length considering PDU header. */
  dataLen = PduInfoPtr->SduLength;
  if ( SoAd_IsPduHdrEnabledOfSoConGrp(soConGrpIdx) == TRUE )
  {
    dataLen += SOAD_PDU_HDR_SIZE;
  }

  /* #20 Check if PDU size is valid for nPdu. */
  if ( dataLen <= SoAd_GetNPduUdpTxBufferMinOfSocketUdp(SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx)) )
  {
    /* #30 Transmit via nPdu queue. */
    if ( SoAd_IsNPduUdpTxQueueUsedOfNPduUdpTx(SoAd_GetNPduUdpTxIdxOfSoCon(soConIdx)) == TRUE )
    {
      retVal = SoAd_TxIf_UdpTransmitNPduQueue(PduRouteDestIdx, PduInfoPtr);                                            /* SBSW_SOAD_POINTER_FORWARD */
    }
    /* #31 Transmit via nPdu buffer. */
    else
    {
      retVal = SoAd_TxIf_UdpTransmitNPduBuffer(PduRouteDestIdx, PduInfoPtr);                                           /* SBSW_SOAD_POINTER_FORWARD */
    }
  }
  /* #21 Set DET error since too much TCP transmissions are active or too much PduRouteDests are configured. */
  else
  {
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
    *ErrorIdPtr = SOAD_E_NOBUFS;                                                                                       /* SBSW_SOAD_POINTER_WRITE */
#else
    SOAD_DUMMY_STATEMENT_VAR(ErrorIdPtr); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  }

  return retVal;
} /* SoAd_TxIf_UdpTransmitNPdu() */

/**********************************************************************************************************************
 *  SoAd_TxIf_UdpTransmitNPduQueue()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_UdpTransmitNPduQueue(
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfPduRouteType   pduRouteIdx = SoAd_GetPduRouteIdxOfPduRouteDest(PduRouteDestIdx);
  SoAd_SizeOfSoConType      soConIdx = SoAd_GetSoConIdxOfPduRouteDest(PduRouteDestIdx);
  SoAd_SizeOfNPduUdpTxType  nPduIdx = SoAd_GetNPduUdpTxIdxOfSoCon(soConIdx);
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Try to add or update an element for his PDU. */
  switch ( SoAd_TxNPduUdp_QueueAddOrUpdateElement(pduRouteIdx, PduRouteDestIdx, PduInfoPtr) )                          /* SBSW_SOAD_POINTER_FORWARD */
  {
    /* #100 Handle nPdu in case adding new PDU leads to an overflow. */
    case SOAD_NPDU_OVFL_NEW:
    {
      /* #1000 Transmit nPdu. */
      SoAd_TxNPduUdp_QueueTransmit(nPduIdx);

      /* #1001 Try to add new PDU to nPdu again. */
      if ( SoAd_TxNPduUdp_QueueAddOrUpdateElement(pduRouteIdx, PduRouteDestIdx, PduInfoPtr) == SOAD_NPDU_OK )          /* SBSW_SOAD_POINTER_FORWARD */
      {
        /* #1002 Transmit nPdu now if trigger mode is set to always. */
        if ( SoAd_GetTxUdpTriggerModeOfPduRouteDest(PduRouteDestIdx) == SOAD_TX_UDP_TRIGGER_ALWAYS )
        {
          SoAd_TxNPduUdp_QueueTransmit(nPduIdx);
        }
        retVal = E_OK;
      }
      break;
    }
    /* #101 Handle nPdu in case update of a PDU leads to an overflow. */
    case SOAD_NPDU_OVFL_UPDATE:
    {
      /* #1010 Transmit nPdu. */
      SoAd_TxNPduUdp_QueueTransmit(nPduIdx);
      retVal = E_OK;
      break;
    }
    /* #102 Handle nPdu in case new PDU is added to nPdu successfully. */
    case SOAD_NPDU_OK:
    {
      /* #1020 Transmit nPdu now if trigger mode is set to always. */
      if ( SoAd_GetTxUdpTriggerModeOfPduRouteDest(PduRouteDestIdx) == SOAD_TX_UDP_TRIGGER_ALWAYS )
      {
        SoAd_TxNPduUdp_QueueTransmit(nPduIdx);
      }
      retVal = E_OK;
      break;
    }
    /* #103 Reject transmission if PDU could not be added to nPdu. */
    default: /* SOAD_NPDU_NOT_OK */
    {
      /* Nothing to do. */
    }
  }

  return retVal;
} /* SoAd_TxIf_UdpTransmitNPduQueue() */

/**********************************************************************************************************************
 *  SoAd_TxIf_UdpTransmitNPduBuffer()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_UdpTransmitNPduBuffer(
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfPduRouteType   pduRouteIdx = SoAd_GetPduRouteIdxOfPduRouteDest(PduRouteDestIdx);
  SoAd_SizeOfSoConType      soConIdx = SoAd_GetSoConIdxOfPduRouteDest(PduRouteDestIdx);
  SoAd_SizeOfNPduUdpTxType  nPduIdx = SoAd_GetNPduUdpTxIdxOfSoCon(soConIdx);
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Try to add PDU to nPdu buffer. */
  switch ( SoAd_TxNPduUdp_BufferAddElement(pduRouteIdx, PduRouteDestIdx, PduInfoPtr) )                                 /* SBSW_SOAD_POINTER_FORWARD */
  {
    /* #100 Handle nPdu in case adding new PDU leads to an overflow. */
    case SOAD_NPDU_OVFL_NEW:
    {
      /* #1000 Transmit nPdu. */
      SoAd_TxNPduUdp_BufferSend(nPduIdx);

      /* #1001 Try to add new PDU to nPdu again. */
      if ( SoAd_TxNPduUdp_BufferAddElement(pduRouteIdx, PduRouteDestIdx, PduInfoPtr) == SOAD_NPDU_OK )                 /* SBSW_SOAD_POINTER_FORWARD */
      {
        /* #1002 Transmit nPdu now if trigger mode is set to always. */
        if ( SoAd_GetTxUdpTriggerModeOfPduRouteDest(PduRouteDestIdx) == SOAD_TX_UDP_TRIGGER_ALWAYS )
        {
          SoAd_TxNPduUdp_BufferSend(nPduIdx);
        }
        retVal = E_OK;
      }
      break;
    }
    /* #101 Handle nPdu in case new PDU is added to nPdu successfully. */
    case SOAD_NPDU_OK:
    {
      /* #1010 Transmit nPdu now if trigger mode is set to always. */
      if ( SoAd_GetTxUdpTriggerModeOfPduRouteDest(PduRouteDestIdx) == SOAD_TX_UDP_TRIGGER_ALWAYS )
      {
        SoAd_TxNPduUdp_BufferSend(nPduIdx);
      }
      retVal = E_OK;
      break;
    }
    /* #102 Reject transmission if PDU could not be added to nPdu. */
    default: /* SOAD_NPDU_NOT_OK */
    {
      /* Nothing to do. */
    }
  }

  return retVal;
} /* SoAd_TxIf_UdpTransmitNPduBuffer() */

/**********************************************************************************************************************
 *  SoAd_TxIf_UdpTransmitPdu()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_UdpTransmitPdu(
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfPduRouteType pduRouteIdx = SoAd_GetPduRouteIdxOfPduRouteDest(PduRouteDestIdx);
  SoAd_SizeOfSoConType    soConIdx = SoAd_GetSoConIdxOfPduRouteDest(PduRouteDestIdx);
  SoAd_SizeOfTxMgtType    txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(soConIdx);
  SoAd_SizeOfSocketType   sockIdx = SoAd_GetSocketIdxOfSoCon(soConIdx);
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent read/write issues for active transmission on socket. */
  SOAD_BEGIN_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Check if no transmission is active on socket. */
  if ( SoAd_GetSoConTxActiveIdxOfSocketDyn(sockIdx) == SoAd_GetSizeOfSoCon() )
  {
    /* #30 Set transmission active on socket. */
    SoAd_SetSoConTxActiveIdxOfSocketDyn(sockIdx, soConIdx);                                                            /* SBSW_SOAD_CSL03 */

    /* #40 Leave critical section. */
    SOAD_END_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #50 Prepare transmission via CopyTxData. */
    SoAd_SetPduRouteIdxOfTxMgt(txMgtIdx, pduRouteIdx);                                                                 /* SBSW_SOAD_OPTIONAL_CSL03 */
    SoAd_SetTxBufPtrOfTxMgt(txMgtIdx, PduInfoPtr->SduDataPtr);                                                         /* SBSW_SOAD_OPTIONAL_CSL03 */

    if ( SoAd_IsPduHdrEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx)) == TRUE )
    {
      SoAd_SetTxBytesLenOfTxMgt(txMgtIdx, PduInfoPtr->SduLength + SOAD_PDU_HDR_SIZE);                                  /* SBSW_SOAD_OPTIONAL_CSL03 */
      SoAd_SetTxBytesPendingOfTxMgt(txMgtIdx, PduInfoPtr->SduLength + SOAD_PDU_HDR_SIZE);                              /* SBSW_SOAD_OPTIONAL_CSL03 */
    }
    else
    {
      SoAd_SetTxBytesLenOfTxMgt(txMgtIdx, PduInfoPtr->SduLength);                                                      /* SBSW_SOAD_OPTIONAL_CSL03 */
      SoAd_SetTxBytesPendingOfTxMgt(txMgtIdx, PduInfoPtr->SduLength);                                                  /* SBSW_SOAD_OPTIONAL_CSL03 */
    }

    /* #60 Try to transmit PDU over UDP and check if transmission succeeds. */
    /* PRQA S 310 2 */ /* MD_SoAd_11.4_struct */
    if ( SoAd_TcpIp_UdpTransmit(sockIdx, SoAd_GetSocketIdOfSocketDyn(sockIdx),                                         /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
        SOAD_A_P2VAR(SoAd_SockAddrType)SoAd_GetAddrRemAddrDynOfSoConDyn(soConIdx),
        (uint16)SoAd_GetTxBytesLenOfTxMgt(txMgtIdx)) == E_OK )
    {
      /* #70 Add a pending TxConfirmation for the transmitted PDU. */
      SoAd_TxIf_AddPendingConf(pduRouteIdx, soConIdx);

      retVal = E_OK;
    }

    /* #80 Finish transmission on socket connection. */
    SoAd_SetPduRouteIdxOfTxMgt(txMgtIdx, SoAd_GetSizeOfPduRoute());                                                    /* SBSW_SOAD_OPTIONAL_CSL03 */
    SoAd_SetTxBufPtrOfTxMgt(txMgtIdx, NULL_PTR);                                                                       /* SBSW_SOAD_OPTIONAL_CSL03 */

    /* #90 Deactivate transmission on socket. */
    SoAd_SetSoConTxActiveIdxOfSocketDyn(sockIdx, SoAd_GetSizeOfSoCon());                                               /* SBSW_SOAD_CSL03 */
  }
  /* #21 Leave critical section otherwise. */
  else
  {
    SOAD_END_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }

  return retVal;
} /* SoAd_TxIf_UdpTransmitPdu() */

/**********************************************************************************************************************
 *  SoAd_TxIf_UdpCopyTxData()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_TxIf_UdpCopyTxData(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) BufLengthPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SOAD_P2VAR(uint8)       bufPtrTmp = BufPtr;
  uint16                  bufLengthTmp = *BufLengthPtr;
  SoAd_SizeOfTxMgtType    txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfPduRouteType pduRouteIdx = SoAd_GetPduRouteIdxOfTxMgt(txMgtIdx);
  BufReq_ReturnType       retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle transmission if transmission is handled from nPdu (if eanbled). */
  if ( SoAd_IsNPduUdpTxUsedOfSoCon(SoConIdx) == TRUE )
  {
    retVal = SoAd_TxNPduUdp_CopyTxData(SoConIdx, BufPtr, BufLengthPtr);                                                /* SBSW_SOAD_POINTER_FORWARD */
  }
  /* #11 Handle transmission of single PDU otherwise. */
  else
  {
    /* #110 Copy PDU header to provided buffer if used. */
    if ( SoAd_IsPduHdrEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) == TRUE )
    {
      SoAd_Tx_CopyTxDataPduHeader(SoConIdx, pduRouteIdx, &bufPtrTmp, &bufLengthTmp);                                   /* SBSW_SOAD_POINTER_FORWARD */
    }

    /* #111 Copy PDU data to provided buffer. */
    if ( SoAd_IsIfTriggerTransmitEnabledOfPduRoute(pduRouteIdx) == TRUE )
    {
      /* #1110 Copy data in case of UDP and trigger transmit is used. */
      retVal = SoAd_TxIf_UdpCopyTxDataTrigger(SoConIdx, pduRouteIdx, BufPtr, BufLengthPtr);                            /* SBSW_SOAD_POINTER_FORWARD */
    }
    else
    {
      /* #1111 Copy data provided in transmit context directly otherwise. */
      SoAd_TxIf_UdpCopyTxDataDirect(SoConIdx, bufPtrTmp, bufLengthTmp);                                                /* SBSW_SOAD_POINTER_FORWARD */
      retVal = BUFREQ_OK;
    }
  }

  return retVal;
} /* SoAd_TxIf_UdpCopyTxData() */

/**********************************************************************************************************************
 *  SoAd_TxIf_UdpCopyTxDataTrigger()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_TxIf_UdpCopyTxDataTrigger(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfPduRouteType PduRouteIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) BufLengthPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  PduInfoType       pduInfo;
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare provided buffer for trigger transmit call. */
  if ( SoAd_IsPduHdrEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) == TRUE )
  {
    pduInfo.SduDataPtr = &BufPtr[SOAD_PDU_HDR_SIZE];
    pduInfo.SduLength = (PduLengthType)(*BufLengthPtr - SOAD_PDU_HDR_SIZE);
  }
  else
  {
    pduInfo.SduDataPtr = BufPtr;
    pduInfo.SduLength = (PduLengthType)*BufLengthPtr;
  }

  /* #20 Call trigger transmit and check if call succeeds. */
  if ( SoAd_GetIfTriggerTransmitCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfPduRoute(PduRouteIdx))(                         /* SBSW_SOAD_FUNCTION_PTR */
    SoAd_GetTxConfPduIdOfPduRoute(PduRouteIdx), &pduInfo) == E_OK )
  {
    /* #200 Check if upper layer returned valid parameter. */
    if ( SoAd_TxIf_UdpCopyTxDataTriggerCheckParameter(SoConIdx, *BufLengthPtr, &pduInfo) == E_OK )                     /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
    {
      /* #2000 Finish copy and update copied length if required. */
      SoAd_TxIf_UdpCopyTxDataTriggerFinish(SoConIdx, BufPtr, BufLengthPtr, &pduInfo);                                  /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */

      retVal = BUFREQ_OK;
    }
  }

  return retVal;
} /* SoAd_TxIf_UdpCopyTxDataTrigger() */

/**********************************************************************************************************************
 *  SoAd_TxIf_UdpCopyTxDataTriggerCheckParameter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxIf_UdpCopyTxDataTriggerCheckParameter(
  SoAd_SizeOfSoConType SoConIdx,
  uint16 BufLength,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16          maxLen;
#if ( SOAD_TX_DYN_LEN == STD_ON )
  uint16          minLen;
#endif /* SOAD_TX_DYN_LEN == STD_ON */
  Std_ReturnType  retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate maximum and minimum expected length if PDU header is used. */
  if ( SoAd_IsPduHdrEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) == TRUE )
  {
    maxLen = (uint16)(BufLength - SOAD_PDU_HDR_SIZE);
#if ( SOAD_TX_DYN_LEN == STD_ON )
    minLen = 0u;
#endif /* SOAD_TX_DYN_LEN == STD_ON */
  }
  /* #11 Calculate maximum and minimum expected length without considering PDU header otherwise. */
  else
  {
    maxLen = BufLength;
#if ( SOAD_TX_DYN_LEN == STD_ON )
    minLen = 1u;
#endif /* SOAD_TX_DYN_LEN == STD_ON */
  }

  /* #20 Check if buffer pointer is invalid. */
  if ( PduInfoPtr->SduDataPtr == NULL_PTR )
  {
    retVal = E_NOT_OK;
  }
  /* #21 Check if buffer length is invalid otherwise. */
#if ( SOAD_TX_DYN_LEN == STD_ON )
  else if ( (PduInfoPtr->SduLength < minLen) || (PduInfoPtr->SduLength > maxLen) )
#else
  else if ( PduInfoPtr->SduLength != maxLen )
#endif /* SOAD_TX_DYN_LEN == STD_ON */
  {
    retVal = E_NOT_OK;
  }
  /* #22 Return success otherwise. */
  else
  {
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_TxIf_UdpCopyTxDataTriggerCheckParameter() */

/**********************************************************************************************************************
 *  SoAd_TxIf_UdpCopyTxDataTriggerFinish()
 *********************************************************************************************************************/
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
/* PRQA S 3206 5 */ /* MD_SoAd_3206 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxIf_UdpCopyTxDataTriggerFinish(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) BufLengthPtr,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfTxMgtType  txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(SoConIdx);
#if ( SOAD_TX_DYN_LEN == STD_ON )
  PduLengthType         oldPduLength = SoAd_GetTxBytesLenOfTxMgt(txMgtIdx);
#endif /* SOAD_TX_DYN_LEN == STD_ON */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Indicate that no further data is pending for this transmission. */
  SoAd_SetTxBytesPendingOfTxMgt(txMgtIdx, 0u);                                                                         /* SBSW_SOAD_OPTIONAL_CSL03 */

#if ( SOAD_TX_DYN_LEN == STD_ON )
  /* #20 Update length of whole PDU (if CopyTxData with dynamic length is enabled). */
  SoAd_SetTxBytesLenOfTxMgt(txMgtIdx, PduInfoPtr->SduLength);                                                          /* SBSW_SOAD_OPTIONAL_CSL03 */

  /* #30 Check if PDU header is used. */
  if ( SoAd_IsPduHdrEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) == TRUE )
  {
    /* #300 Consider PDU header length when updating length if whole PDU. */
    SoAd_SetTxBytesLenOfTxMgt(txMgtIdx, SoAd_GetTxBytesLenOfTxMgt(txMgtIdx) + SOAD_PDU_HDR_SIZE);                      /* SBSW_SOAD_OPTIONAL_CSL03 */

    /* #301 Update PDU header if length has changed during trigger transmit call. */
    if ( PduInfoPtr->SduLength != (oldPduLength - SOAD_PDU_HDR_SIZE) )
    {
      SoAd_Util_UpdatePduHdrLen(PduInfoPtr->SduLength, BufPtr);                                                        /* SBSW_SOAD_POINTER_FORWARD */
    }
  }

  /* #40 Return updated length (if CopyTxData with dynamic length is enabled). */
  *BufLengthPtr = (uint16)SoAd_GetTxBytesLenOfTxMgt(txMgtIdx);                                                         /* SBSW_SOAD_POINTER_WRITE */
#else
  SOAD_DUMMY_STATEMENT_VAR(BufPtr); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */
  SOAD_DUMMY_STATEMENT_VAR(BufLengthPtr); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */
  SOAD_DUMMY_STATEMENT_VAR(PduInfoPtr); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */
#endif /* SOAD_TX_DYN_LEN == STD_ON */
} /* SoAd_TxIf_UdpCopyTxDataTriggerFinish() */

/**********************************************************************************************************************
 *  SoAd_TxIf_UdpCopyTxDataDirect()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxIf_UdpCopyTxDataDirect(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 BufLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  SOAD_P2VAR(uint8)     txBufPtr;
  SoAd_SizeOfTxMgtType  txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(SoConIdx);
  PduLengthType         bytesCopied;
  uint16                bytesToCopy;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate buffer index and length to prepare for copying. */
  bytesCopied = (PduLengthType)(SoAd_GetTxBytesLenOfTxMgt(txMgtIdx) - SoAd_GetTxBytesPendingOfTxMgt(txMgtIdx));
  if ( SoAd_IsPduHdrEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) == TRUE )
  {
    if ( bytesCopied < SOAD_PDU_HDR_SIZE )
    {
      bytesToCopy = 0u;
      bytesCopied = 0u;
    }
    else
    {
      bytesToCopy = BufLength;
      bytesCopied -= SOAD_PDU_HDR_SIZE;
    }
  }
  else
  {
    bytesToCopy = BufLength;
  }

  /* #20 Copy PDU data. */
  txBufPtr = SoAd_GetTxBufPtrOfTxMgt(txMgtIdx);
  IpBase_Copy(SOAD_A_P2VAR(IpBase_CopyDataType)&BufPtr[0u],                                                            /* SBSW_SOAD_POINTER_AND_TX_BUFFER_POINTER_FORWARD */
    SOAD_A_P2CONST(IpBase_CopyDataType)&txBufPtr[bytesCopied],
    bytesToCopy);

  /* #30 Decrement pending data length. */
  SoAd_SetTxBytesPendingOfTxMgt(txMgtIdx, (PduLengthType)(SoAd_GetTxBytesPendingOfTxMgt(txMgtIdx) - bytesToCopy));     /* SBSW_SOAD_OPTIONAL_CSL03 */
} /* SoAd_TxIf_UdpCopyTxDataDirect() */

/**********************************************************************************************************************
 *  SoAd_TxIf_AddPendingConf()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxIf_AddPendingConf(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if TxConfirmation is enabled. */
  if ( SoAd_IsTxConfEnabledOfPduRoute(PduRouteIdx) == TRUE )
  {
    /* #20 Check if API type is IF. */
    if ( SoAd_GetUpperLayerApiOfPduRoute(PduRouteIdx) == SOAD_UL_API_IF )
    {
#if ( SOAD_TCP == STD_ON )
      /* #30 Check if socket type is UDP. */
      if ( SoAd_IsSocketUdpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) == TRUE )
#endif /* SOAD_TCP == STD_ON */
      {
        /* #300 Add pending TxConfirmation on UDP socket connection. */
        SoAd_TxIf_AddPendingConfUdp(PduRouteIdx, SoConIdx);
      }
#if ( SOAD_TCP == STD_ON )
      else
      /* #40 Assume socket type is TCP otherwise (if enabled). */
      {
        /* #400 Increment pending TxConfirmation counter to confirm in SoAd_TxConfirmation. */
        SoAd_IncPendingTxConfNumOfPduRouteDyn(PduRouteIdx);                                                            /* SBSW_SOAD_PARAMETER_IDX */
      }
#endif /* SOAD_TCP == STD_ON */
    }
  }
} /* SoAd_TxIf_AddPendingConf() */

/**********************************************************************************************************************
 *  SoAd_TxIf_AddPendingConfUdp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxIf_AddPendingConfUdp(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if nPdu queue is used. */
  if ( (SoAd_IsNPduUdpTxUsedOfSoCon(SoConIdx) == TRUE) &&
    (SoAd_IsIfTriggerTransmitEnabledOfPduRoute(PduRouteIdx) == TRUE) )
  {
    /* #100 Increment pending TxConfirmation counter to confirm after TriggerTransmit call. */
    SoAd_IncPendingTxConfNumOfPduRouteDyn(PduRouteIdx);                                                                /* SBSW_SOAD_PARAMETER_IDX */
  }
  /* #11 Check if UdpImmediateIfTxConfirmation is disabled otherwise (if feature is enabled at all). */
  else if ( SoAd_IsImmedIfTxConfOfSocketUdp(
    SoAd_GetSocketUdpIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx))) == FALSE )
  {
    /* #110 Set flag to call TxConfirmation in next main function. */
    /* May be set multiple times if multiple PduRoutesDests are configured with this confirmation strategy. */
    SoAd_SetPendingTxConfMainOfPduRouteDyn(PduRouteIdx, TRUE);                                                         /* SBSW_SOAD_PARAMETER_IDX */
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_IF_UDP_PDU_ROUTE, PduRouteIdx);
  }
  else
  {
    /* nothing to do */
  }
} /* SoAd_TxIf_AddPendingConfUdp() */

/**********************************************************************************************************************
 *  SoAd_TxIf_UdpHandleTxConfirmation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxIf_UdpHandleTxConfirmation(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_EventQueueIfUdpPduRouteIterType  eventQueueIfUdpPduRouteIter;
  uint32                                handleIdx = 0u;
  uint32                                elementNumToHandle = SoAd_EventQueue_GetElementNumToHandle(
    SOAD_EVENT_QUEUE_IF_UDP_PDU_ROUTE);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all queue elements which have to be handled in this context considering configured limit. */
  for ( eventQueueIfUdpPduRouteIter = 0u;
    eventQueueIfUdpPduRouteIter < elementNumToHandle;
    eventQueueIfUdpPduRouteIter++ )
  {
    /* #20 Get next element. */
    if ( SoAd_EventQueue_GetNextElement(SOAD_EVENT_QUEUE_IF_UDP_PDU_ROUTE, &handleIdx) == E_OK )                       /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    {
      SoAd_SizeOfPduRouteType pduRouteIdx = (SoAd_SizeOfPduRouteType)handleIdx;

      /* #30 Check if a TxConfirmation is pending to be handled in main function context. */
      if ( SoAd_IsPendingTxConfMainOfPduRouteDyn(pduRouteIdx) == TRUE )
      {
        /* #40 Call TxConfirmation. */
        SoAd_TxIf_UdpTxConfirmation(pduRouteIdx);
      }
    }
    /* #21 Stop iteration if no element is left. */
    else
    {
      break;
    }
  }
} /* SoAd_TxIf_HandleTxConfirmation() */

/**********************************************************************************************************************
 *  SoAd_TxIf_UdpTxConfirmation()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxIf_UdpTxConfirmation(
  SoAd_SizeOfPduRouteType PduRouteIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_PduRouteDestIterType pduRouteDestIter;
  SoAd_SizeOfSoConType      soConIdx;
  SoAd_SizeOfSoConGrpType   soConGrpIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all PduRouteDests. */
  for ( pduRouteDestIter = SoAd_GetPduRouteDestStartIdxOfPduRoute(PduRouteIdx);
    pduRouteDestIter < SoAd_GetPduRouteDestEndIdxOfPduRoute(PduRouteIdx);
    pduRouteDestIter++ )
  {
    soConIdx = SoAd_GetSoConIdxOfPduRouteDest(pduRouteDestIter);
    soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConIdx);

    /* #20 Check if PduRouteDest is configured for UDP and immediate TxConfirmation is disabled. */
    if (
#if ( SOAD_TCP == STD_ON )
     (SoAd_IsSocketUdpUsedOfSoConGrp(soConGrpIdx) == TRUE) &&
#endif /* SOAD_TCP == STD_ON */
     (SoAd_IsImmedIfTxConfOfSocketUdp(SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx)) == FALSE) )
    {
      /* #30 Indicate that no TxConfirmation is pending in main function for this PduRoute. */
      SoAd_SetPendingTxConfMainOfPduRouteDyn(PduRouteIdx, FALSE);                                                      /* SBSW_SOAD_PARAMETER_IDX */

      /* #40 Check if now no TxConfirmation is pending at all for this PduRoute. */
      if ( SoAd_GetPendingTxConfNumOfPduRouteDyn(PduRouteIdx) == 0u )
      {
        /* #50 Reconnect socket connection if socket connection has auto setup enabled and wildcards configured. */
        SoAd_SoCon_Reconnect(soConIdx);

        /* #60 Call TxConfirmation if configured. */
        if ( SoAd_IsTxConfEnabledOfPduRoute(PduRouteIdx) == TRUE )
        {
          SoAd_GetIfTxConfirmationCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfPduRoute(PduRouteIdx))(                       /* SBSW_SOAD_FUNCTION_PTR */
            SoAd_GetTxConfPduIdOfPduRoute(PduRouteIdx));
        }

        break;
      }
    }
  }
} /* SoAd_TxIf_UdpTxConfirmation() */

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_TxIf_TcpTxConfirmation()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxIf_TcpTxConfirmation(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfPduRouteType PduRouteIdx,
  boolean ByResetSoCon)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if TxConfirmation is enabled for this PDU. */
  if ( SoAd_IsTxConfEnabledOfPduRoute(PduRouteIdx) == TRUE )
  {
    /* #20 Enter critical section to prevent that other confirmation interrupts and TxConfirmation is called twice. */
    SOAD_BEGIN_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #30 Check if a pending TxConfirmation is left. */
    if ( SoAd_GetPendingTxConfNumOfPduRouteDyn(PduRouteIdx) > 0u )
    {
      /* #40 Decrement pending confirmation counter. */
      SoAd_DecPendingTxConfNumOfPduRouteDyn(PduRouteIdx);                                                              /* SBSW_SOAD_PARAMETER_IDX */

      /* #50 Check if no confirmation is pending (i.e. transmission confirmed on all PduRouteDests). */
      if ( (SoAd_GetPendingTxConfNumOfPduRouteDyn(PduRouteIdx) == 0u) &&
        (SoAd_IsPendingTxConfMainOfPduRouteDyn(PduRouteIdx) == FALSE) )
      {
        /* #60 Check if confirmation is not requested by resetting socket connection on close. */
        if ( ByResetSoCon == FALSE )
        {
          /* #600 Reconnect socket connection if socket connection has auto setup enabled and wildcards configured. */
          SoAd_SoCon_RequestReconnect(SoConIdx);
        }

        /* #70 Leave critical section to be able to call TxConfirmation of upper layer. */
        SOAD_END_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

        /* #80 Call TxConfirmation of upper layer. */
        SoAd_GetIfTxConfirmationCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfPduRoute(PduRouteIdx))(                         /* SBSW_SOAD_FUNCTION_PTR */
          SoAd_GetTxConfPduIdOfPduRoute(PduRouteIdx));
      }
      /* #51 Leave critical section otherwise. */
      else
      {
        SOAD_END_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
      }
    }
    /* #31 Leave critical section otherwise. */
    else
    {
      SOAD_END_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    }
  }
} /* SoAd_TxIf_TcpTxConfirmation() */
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TxTp_CheckParameter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxTp_CheckParameter(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  PduLengthType PduLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfPduRouteDestType pduRouteDestIdx = SoAd_GetPduRouteDestStartIdxOfPduRoute(PduRouteIdx);
  SoAd_SizeOfSoConType        soConIdx = SoAd_GetSoConIdxOfPduRouteDest(pduRouteDestIdx);
  Std_ReturnType              retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check module state. */
  if ( SoAd_State == SOAD_STATE_INIT )
  {
    /* #20 Check PDU length. */
    if ( PduLength > 0u )
    {
      /* #30 Check socket connection state. */
      if ( (SoAd_GetCloseModeOfSoConDyn(soConIdx) == SOAD_CLOSE_NONE) &&
        (SoAd_GetModeOfSoConDyn(soConIdx) == SOAD_SOCON_ONLINE) )
      {
        retVal = E_OK;
      }
    }
  }

  return retVal;
} /* SoAd_TxTp_CheckParameter() */

/**********************************************************************************************************************
 *  SoAd_TxTp_TransmitPdu()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxTp_TransmitPdu(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfPduRouteDestType pduRouteDestIdx = SoAd_GetPduRouteDestStartIdxOfPduRoute(PduRouteIdx);
  SoAd_SizeOfSoConType        soConIdx = SoAd_GetSoConIdxOfPduRouteDest(pduRouteDestIdx);
  Std_ReturnType              retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if any routing group is enabled for this PduRouteDest. */
  if ( SoAd_RouteGrp_CheckAnyRoutGrpOnPduRouteDestEnabled(pduRouteDestIdx) == TRUE )
  {
    /* #20 Enter critical section to prevent interruption by another transmission request. */
    SOAD_BEGIN_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #30 Check if corresponding socket connection is not used for another transmission. */
    if ( SoAd_GetSoConTxActiveIdxOfSocketDyn(SoAd_GetSocketIdxOfSoCon(soConIdx)) == SoAd_GetSizeOfSoCon() )
    {
      /* #40 Check and set protocol (TCP/UDP) specific parameter. */
      if ( SoAd_TxTp_CheckAndSetProtocolParameter(PduRouteIdx, PduInfoPtr->SduLength) == E_OK )
      {
        /* #50 Prepare transmission on socket connection. */
        SoAd_TxTp_PrepareTransmitPdu(PduRouteIdx, PduInfoPtr->SduLength);

        retVal = E_OK;
      }
    }

    /* #60 Leave critical section. */
    SOAD_END_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }

  /* #70 Check if transmission is prepared. */
  if ( retVal == E_OK )
  {
    /* #80 Handle transmission in this context if TpOptimized is enabled for this PDU. */
    if ( SoAd_IsTpOptimizedOfPduRoute(PduRouteIdx) == TRUE )
    {
      retVal = SoAd_TxTp_TransmitPduRouteDest(soConIdx, FALSE);
    }
    /* #81 Add event to corresponding event queue to handle transmission in main function context otherwise. */
    else
    {
      SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_TP_TX_SO_CON, soConIdx);
    }
  }

  return retVal;
} /* SoAd_TxTp_TransmitPdu() */

/**********************************************************************************************************************
 *  SoAd_TxTp_CheckAndSetProtocolParameter()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxTp_CheckAndSetProtocolParameter(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  PduLengthType PduLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfPduRouteDestType pduRouteDestIdx = SoAd_GetPduRouteDestStartIdxOfPduRoute(PduRouteIdx);
  SoAd_SizeOfSoConType        soConIdx = SoAd_GetSoConIdxOfPduRouteDest(pduRouteDestIdx);
  Std_ReturnType              retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */

#if ( SOAD_TCP == STD_ON )
  /* #10 Handle transmission over TCP. */
  if ( SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx)) == TRUE )
  {
    /* #100 Check if TxQueue can handle new request. */
    if ( SoAd_TxTcpQueue_ReserveNextElement(soConIdx, PduRouteIdx) == E_OK )
    {
      /* #1000 Set element considering PDU header length if PDU header is eanbled. */
      if ( SoAd_IsPduHdrEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx)) == TRUE )
      {
        SoAd_TxTcpQueue_SetElement(soConIdx, PduRouteIdx, (PduLength + SOAD_PDU_HDR_SIZE), FALSE);
      }
      else
      /* #1001 Set element considering PDU length only if PDU header is disabled. */
      {
        SoAd_TxTcpQueue_SetElement(soConIdx, PduRouteIdx, PduLength, FALSE);
      }

      retVal = E_OK;
    }
  }
  else
#endif /* SOAD_TCP == STD_ON */
  /* #20 Handle transmission over UDP. */
  {
    SoAd_SizeOfTpTxBufferConfigType tpTxBufferConfigIdx = SoAd_GetTpTxBufferConfigIdxOfSoCon(soConIdx);

    /* #200 Check if TP Tx buffer size is sufficient. */
    if ( PduLength <=
      (SoAd_GetTpTxBufferEndIdxOfTpTxBufferConfig(tpTxBufferConfigIdx) -
        SoAd_GetTpTxBufferStartIdxOfTpTxBufferConfig(tpTxBufferConfigIdx)) )
    {
      /* #2000 Update Alive Supervision Timeout. */
      SoAd_SoCon_UpdateUdpAliveTimeout(soConIdx);

      retVal = E_OK;
    }
  }

  return retVal;
} /* SoAd_TxTp_CheckAndSetProtocolParameter() */

/**********************************************************************************************************************
 *  SoAd_TxTp_PrepareTransmitPdu()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTp_PrepareTransmitPdu(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  PduLengthType PduLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfPduRouteDestType pduRouteDestIdx = SoAd_GetPduRouteDestStartIdxOfPduRoute(PduRouteIdx);
  SoAd_SizeOfSoConType        soConIdx = SoAd_GetSoConIdxOfPduRouteDest(pduRouteDestIdx);
  SoAd_SizeOfTxMgtType        txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(soConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set transmission management structure. */
  SoAd_SetPduRouteIdxOfTxMgt(txMgtIdx, PduRouteIdx);                                                                   /* SBSW_SOAD_OPTIONAL_CSL03 */
  SoAd_SetTxBytesLenOfTxMgt(txMgtIdx, PduLength);                                                                      /* SBSW_SOAD_OPTIONAL_CSL03 */
  SoAd_SetTxBytesPendingOfTxMgt(txMgtIdx, PduLength);                                                                  /* SBSW_SOAD_OPTIONAL_CSL03 */

  if ( SoAd_IsPduHdrEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx)) == TRUE )
  {
    /* #100 Consider length of PDU header. */
    SoAd_SetTxBytesLenOfTxMgt(txMgtIdx, SoAd_GetTxBytesLenOfTxMgt(txMgtIdx) + SOAD_PDU_HDR_SIZE);                      /* SBSW_SOAD_OPTIONAL_CSL03 */
    SoAd_SetTxBytesPendingOfTxMgt(txMgtIdx, SoAd_GetTxBytesPendingOfTxMgt(txMgtIdx) + SOAD_PDU_HDR_SIZE);              /* SBSW_SOAD_OPTIONAL_CSL03 */
  }

  /* #20 Lock socket connection for this transmission. */
  SoAd_SetSoConTxActiveIdxOfSocketDyn(SoAd_GetSocketIdxOfSoCon(soConIdx), soConIdx);                                   /* SBSW_SOAD_CSL03 */
} /* SoAd_TxTp_PrepareTransmitPdu() */

/**********************************************************************************************************************
 *  SoAd_TxTp_CallCopyTxData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_TxTp_CallCopyTxData(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  CONSTP2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) PduInfoPtr,
  CONSTP2VAR(PduLengthType, AUTOMATIC, SOAD_APPL_DATA) BufferSizePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfUpperLayerType upperLayerIdx = SoAd_GetUpperLayerIdxOfPduRoute(PduRouteIdx);
  BufReq_ReturnType         retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call CopyTxData function with non-constant pointer if configured. */
  if ( SoAd_GetTpCopyTxDataCbkOfUpperLayer(upperLayerIdx) != NULL_PTR )
  {
    retVal = SoAd_GetTpCopyTxDataCbkOfUpperLayer(upperLayerIdx)(                                                       /* SBSW_SOAD_FUNCTION_PTR */
      SoAd_GetTxConfPduIdOfPduRoute(PduRouteIdx), PduInfoPtr, NULL_PTR, BufferSizePtr);
  }
  /* #20 Call CopyTxData function with constant pointer otherwise. */
  else
  {
    retVal = SoAd_GetTpCopyTxDataConstCbkOfUpperLayer(upperLayerIdx)(
      SoAd_GetTxConfPduIdOfPduRoute(PduRouteIdx), PduInfoPtr, NULL_PTR, BufferSizePtr);                                /* SBSW_SOAD_FUNCTION_PTR */
  }

  return retVal;
} /* SoAd_TxTp_CallCopyTxData() */

/**********************************************************************************************************************
 *  SoAd_TxTp_TerminateTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTp_TerminateTransmit(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfTxMgtType    txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfPduRouteType pduRouteIdx = SoAd_GetPduRouteIdxOfTxMgt(txMgtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if transmission is active on socket connection. */
  if ( pduRouteIdx != SoAd_GetSizeOfPduRoute() )
  {
    /* #20 Check if transmission is of type TP. */
    if ( SoAd_GetUpperLayerApiOfPduRoute(pduRouteIdx) == SOAD_UL_API_TP )
    {
      /* #30 Call confirmation callback with positive result if all data are sent. */
      if ( SoAd_GetTxBytesPendingOfTxMgt(txMgtIdx) == 0u )
      {
        SoAd_GetTpTxConfirmationCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfPduRoute(pduRouteIdx))(                         /* SBSW_SOAD_FUNCTION_PTR */
          SoAd_GetTxConfPduIdOfPduRoute(pduRouteIdx), E_OK);
      }
      /* #31 Call confirmation callback with negative result if not all data are sent. */
      else
      {
        SoAd_GetTpTxConfirmationCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfPduRoute(pduRouteIdx))(                         /* SBSW_SOAD_FUNCTION_PTR */
          SoAd_GetTxConfPduIdOfPduRoute(pduRouteIdx), E_NOT_OK);
      }

      /* #40 Reset transmission struct on socket connection. */
      SoAd_SetTxBytesLenOfTxMgt(txMgtIdx, 0u);                                                                         /* SBSW_SOAD_OPTIONAL_CSL03 */
      SoAd_SetTxBytesPendingOfTxMgt(txMgtIdx, 0u);                                                                     /* SBSW_SOAD_OPTIONAL_CSL03 */
      SoAd_SetPduRouteIdxOfTxMgt(txMgtIdx, SoAd_GetSizeOfPduRoute());                                                  /* SBSW_SOAD_OPTIONAL_CSL03 */
      SoAd_SetCancelRequestedOfTxMgt(txMgtIdx, FALSE);                                                                 /* SBSW_SOAD_OPTIONAL_CSL03 */
    }
  }
} /* SoAd_TxTp_TerminateTransmit() */

/**********************************************************************************************************************
 *  SoAd_TxTp_CancelTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxTp_CancelTransmit(
  SoAd_SizeOfPduRouteType PduRouteIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfPduRouteDestType pduRouteDestIdx = SoAd_GetPduRouteDestStartIdxOfPduRoute(PduRouteIdx);
  SoAd_SizeOfSoConType        soConIdx = SoAd_GetSoConIdxOfPduRouteDest(pduRouteDestIdx);
  SoAd_SizeOfTxMgtType        txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(soConIdx);
  Std_ReturnType              retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if PDU transmission is active on socket connection. */
  if ( PduRouteIdx == SoAd_GetPduRouteIdxOfTxMgt(txMgtIdx) )
  {
    /* #20 Set flag to perform cancellation. */
    SoAd_SetCancelRequestedOfTxMgt(txMgtIdx, TRUE);                                                                    /* SBSW_SOAD_OPTIONAL_CSL03 */

    /* #30 Set event to handle PDU (i.e. cancellation) in main function. */
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_TP_TX_SO_CON, soConIdx);

    retVal = E_OK;
  }

  return retVal;
} /* SoAd_TxTp_CancelTransmit() */

/**********************************************************************************************************************
 *  SoAd_TxTp_HandleTransmission()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTp_HandleTransmission(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_EventQueueTpTxSoConIterType  eventQueueTpTxSoConIter;
  uint32                            handleIdx = 0u;
  uint32                            elementNumToHandle = SoAd_EventQueue_GetElementNumToHandle(
    SOAD_EVENT_QUEUE_TP_TX_SO_CON);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all queue elements which have to be handled in this context considering configured limit. */
  for ( eventQueueTpTxSoConIter = 0u;
    eventQueueTpTxSoConIter < elementNumToHandle;
    eventQueueTpTxSoConIter++ )
  {
    /* #20 Get next element. */
    if ( SoAd_EventQueue_GetNextElement(SOAD_EVENT_QUEUE_TP_TX_SO_CON, &handleIdx) == E_OK )                           /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    {
      SoAd_SizeOfSoConType soConIdx = (SoAd_SizeOfSoConType)handleIdx;

      /* #30 Handle TP transmission on socket connection. */
      (void)SoAd_TxTp_TransmitPduRouteDest(soConIdx, TRUE);
    }
    /* #21 Stop iteration if no element is left. */
    else
    {
      break;
    }
  }
} /* SoAd_TxTp_HandleTransmission() */

/**********************************************************************************************************************
 *  SoAd_TxTp_TransmitPduRouteDest()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxTp_TransmitPduRouteDest(
  SoAd_SizeOfSoConType SoConIdx,
  boolean CalledByMain)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfTxMgtType    txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfPduRouteType pduRouteIdx = SoAd_GetPduRouteIdxOfTxMgt(txMgtIdx);
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if TP PDU transmission is active. */
  if ( pduRouteIdx != SoAd_GetSizeOfPduRoute() )
  {
    /* #20 Check if socket connection is not requested to be closed. */
    if ( SoAd_GetCloseModeOfSoConDyn(SoConIdx) == SOAD_CLOSE_NONE )
    {
      /* #30 Handle transmit cancellation if requested. */
      if ( SoAd_IsCancelRequestedOfTxMgt(txMgtIdx) == TRUE )
      {
        SoAd_TxTp_HandleCancellation(SoConIdx);
      }
      /* #31 Continue transmission otherwise. */
      else
      {
#if ( SOAD_TCP == STD_ON )
        /* #310 Continue transmission for TCP (if enabled). */
        if ( SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) == TRUE )
        {
          retVal = SoAd_TxTp_TcpTransmit(SoConIdx, CalledByMain);
        }
        else
#endif /* SOAD_TCP == STD_ON */
        /* #311 Continue transmission for UDP otherwise. */
        {
          retVal = SoAd_TxTp_UdpTransmit(SoConIdx, CalledByMain);
        }
      }
    }
  }

  return retVal;
} /* SoAd_TxTp_TransmitPduRouteDest() */

/**********************************************************************************************************************
 *  SoAd_TxTp_HandleCancellation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTp_HandleCancellation(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfTxMgtType    txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfPduRouteType pduRouteIdx = SoAd_GetPduRouteIdxOfTxMgt(txMgtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Release local TP transmission buffer. */
  if ( SoAd_IsTpTxBufferConfigUsedOfSoCon(SoConIdx) == TRUE )
  {
    SoAd_SetTpTxBufferIdxOfTpTxBufferConfigDyn(SoAd_GetTpTxBufferConfigIdxOfSoCon(SoConIdx),                           /* SBSW_SOAD_CSL03 */
      SoAd_GetTpTxBufferStartIdxOfTpTxBufferConfig(SoAd_GetTpTxBufferConfigIdxOfSoCon(SoConIdx)));
  }

#if ( SOAD_TCP == STD_ON )
  /* #20 Release Tx TCP queue element (if enabled). */
  if ( SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) == TRUE )
  {
    SoAd_TxTcpQueue_SetElement(SoConIdx, pduRouteIdx, 0u, TRUE);
  }
#endif /* SOAD_TCP == STD_ON */

  /* #30 Reset TP session. */
  SoAd_SetPduRouteIdxOfTxMgt(txMgtIdx, SoAd_GetSizeOfPduRoute());                                                      /* SBSW_SOAD_OPTIONAL_CSL03 */
  SoAd_SetTxBytesLenOfTxMgt(txMgtIdx, 0u);                                                                             /* SBSW_SOAD_OPTIONAL_CSL03 */
  SoAd_SetTxBytesPendingOfTxMgt(txMgtIdx, 0u);                                                                         /* SBSW_SOAD_OPTIONAL_CSL03 */
  SoAd_SetCancelRequestedOfTxMgt(txMgtIdx, FALSE);                                                                     /* SBSW_SOAD_OPTIONAL_CSL03 */

  /* #40 Indicate to close socket connection in main function. */
  SoAd_SetCloseModeOfSoConDyn(SoConIdx, SOAD_CLOSE_OFFLINE_RESET);                                                     /* SBSW_SOAD_PARAMETER_IDX */
  SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx);

  /* #50 Call upper layer TpTxConfirmation with negative result. */
  SoAd_GetTpTxConfirmationCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfPduRoute(pduRouteIdx))(                               /* SBSW_SOAD_FUNCTION_PTR */
    SoAd_GetTxConfPduIdOfPduRoute(pduRouteIdx), E_NOT_OK);
} /* SoAd_TxTp_HandleCancellation() */

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_TxTp_TcpTransmit()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxTp_TcpTransmit(
  SoAd_SizeOfSoConType SoConIdx,
  boolean CalledByMain)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfTxMgtType    txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfPduRouteType pduRouteIdx = SoAd_GetPduRouteIdxOfTxMgt(txMgtIdx);
  PduInfoType             pduInfo = { NULL_PTR, 0u };
  PduLengthType           availableBufLen = 0u;
  boolean                 continueTransmission = TRUE;
  Std_ReturnType          retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate until PDU is completely transmitted. */
  while ( SoAd_GetTxBytesPendingOfTxMgt(txMgtIdx) > 0u )
  {
    /* #20 Call CopyTxData and check if call succeeds. */
    if ( SoAd_TxTp_CallCopyTxData(pduRouteIdx, &pduInfo, &availableBufLen) == BUFREQ_OK )                              /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    {
      /* #200 Calculate length of data that can be transmitted now. */
      SoAd_TxTp_TcpCalculateLength(SoConIdx, &availableBufLen);                                                        /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */

      /* #201 Handle transmission to TcpIp if upper layer has data for transmission available. */
      if ( availableBufLen > 0u )
      {
        /* #2010 Try to transmit data and handle TP session if transmission succeeded. */
        if ( SoAd_TcpIp_TcpTransmit(SoConIdx, availableBufLen, FALSE) == E_OK )
        {
          SoAd_TxTp_TcpTransmitHandleSuccess(SoConIdx);
        }
        /* #2011 Return that transmission has failed and handle TP session otherwise. */
        else
        {
          SoAd_TxTp_TcpTransmitHandleFail(SoConIdx, CalledByMain);
          retVal = E_NOT_OK;
        }
      }
      /* #202 Indicate to continue transmission in main function otherwise. */
      else
      {
        SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_TP_TX_SO_CON, SoConIdx);

        continueTransmission = FALSE;
      }
    }
    /* #21 Handle case if call to CopyTxData failed otherwise. */
    else
    {
      /* #210 Indicate to close socket connection in main function. */
      SoAd_SetCloseModeOfSoConDyn(SoConIdx, SOAD_CLOSE_OFFLINE_RESET);                                                 /* SBSW_SOAD_PARAMETER_IDX */
      SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx);

      /* #211 Return that transmission has failed. */
      continueTransmission = FALSE;
      retVal = E_NOT_OK;
    }

    /* #30 Stop transmission in this context if transmission failed or no data for transmission is available. */
    if ( continueTransmission == FALSE )
    {
      break;
    }
  }

  return retVal;
} /* SoAd_TxTp_TcpTransmit() */

/**********************************************************************************************************************
 *  SoAd_TxTp_TcpCalculateLength()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTp_TcpCalculateLength(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(PduLengthType, AUTOMATIC, SOAD_APPL_VAR) AvailableBufLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfTxMgtType  txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(SoConIdx);
  PduLengthType         maxExpectedBufLen;
  PduLengthType         pduHdrRestLen;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if upper layer has available buffer. */
  if ( *AvailableBufLenPtr > 0u )
  {
    /* #20 Set maximum expected available buffer size to pending data size. */
    maxExpectedBufLen = SoAd_GetTxBytesPendingOfTxMgt(txMgtIdx);

    /* #30 Check if PDU header is enabled. */
    if ( SoAd_IsPduHdrEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) == TRUE )
    {
      /* #40 Get pending PDU header length. */
      pduHdrRestLen = SoAd_GetTxBytesLenOfTxMgt(txMgtIdx) - SoAd_GetTxBytesPendingOfTxMgt(txMgtIdx);
      if ( pduHdrRestLen > SOAD_PDU_HDR_SIZE )
      {
        pduHdrRestLen = 0u;
      }
      else
      {
        pduHdrRestLen = SOAD_PDU_HDR_SIZE - pduHdrRestLen;
      }

      /* #50 Add pending PDU header length to available buffer size. */
      *AvailableBufLenPtr += pduHdrRestLen;                                                                            /* SBSW_SOAD_POINTER_WRITE */
    }

    /* #60 Overwrite available upper layer buffer size if it exceeds the maximum expected available buffer size. */
    if ( *AvailableBufLenPtr > maxExpectedBufLen )
    {
      *AvailableBufLenPtr = maxExpectedBufLen;                                                                         /* SBSW_SOAD_POINTER_WRITE */
    }
  }
} /* SoAd_TxTp_TcpCalculateLength() */

/**********************************************************************************************************************
 *  SoAd_TxTp_TcpTransmitHandleSuccess()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTp_TcpTransmitHandleSuccess(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfTxMgtType    txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfPduRouteType pduRouteIdx = SoAd_GetPduRouteIdxOfTxMgt(txMgtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if transmission is finsihed. */
  if ( SoAd_GetTxBytesPendingOfTxMgt(txMgtIdx) == 0u )
  {
    /* #20 Check if immediate TP TxConfirmation is enabled. */
    if ( SoAd_IsImmedTpTxConfOfSocketTcp(SoAd_GetSocketTcpIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx))) ==
      TRUE )
    {
      /* #30 Reset TP session. */
      SoAd_SetPduRouteIdxOfTxMgt(txMgtIdx, SoAd_GetSizeOfPduRoute());                                                  /* SBSW_SOAD_OPTIONAL_CSL03 */
      SoAd_SetTxBytesLenOfTxMgt(txMgtIdx, 0u);                                                                         /* SBSW_SOAD_OPTIONAL_CSL03 */

      SoAd_SetSoConTxActiveIdxOfSocketDyn(SoAd_GetSocketIdxOfSoCon(SoConIdx), SoAd_GetSizeOfSoCon());                  /* SBSW_SOAD_CSL03 */

      /* #40 Reconnect socket connection if socket connection has auto setup enabled and wildcards configured. */
      SoAd_SoCon_RequestReconnect(SoConIdx);

      /* #50 Call TpTxConfirmation of upper layer with positive result. */
      SoAd_GetTpTxConfirmationCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfPduRoute(pduRouteIdx))(                           /* SBSW_SOAD_FUNCTION_PTR */
        SoAd_GetTxConfPduIdOfPduRoute(pduRouteIdx), E_OK);
    }
  }
} /* SoAd_TxTp_TcpTransmitHandleSuccess() */

/**********************************************************************************************************************
 *  SoAd_TxTp_TcpTransmitHandleFail()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTp_TcpTransmitHandleFail(
  SoAd_SizeOfSoConType SoConIdx,
  boolean CalledByMain)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfTxMgtType    txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfPduRouteType pduRouteIdx = SoAd_GetPduRouteIdxOfTxMgt(txMgtIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset TP session. */
  SoAd_SetPduRouteIdxOfTxMgt(txMgtIdx, SoAd_GetSizeOfPduRoute());                                                      /* SBSW_SOAD_OPTIONAL_CSL03 */
  SoAd_SetTxBytesLenOfTxMgt(txMgtIdx, 0u);                                                                             /* SBSW_SOAD_OPTIONAL_CSL03 */
  SoAd_SetTxBytesPendingOfTxMgt(txMgtIdx, 0u);                                                                         /* SBSW_SOAD_OPTIONAL_CSL03 */

  SoAd_SetSoConTxActiveIdxOfSocketDyn(SoAd_GetSocketIdxOfSoCon(SoConIdx), SoAd_GetSizeOfSoCon());                      /* SBSW_SOAD_CSL03 */

  /* #20 Indicate to close socket connection in main function if transmission has already started. */
  if ( SoAd_GetTxBytesLenOfTxMgt(txMgtIdx) != SoAd_GetTxBytesPendingOfTxMgt(txMgtIdx) )
  {
    SoAd_SetCloseModeOfSoConDyn(SoConIdx, SOAD_CLOSE_OFFLINE_RESET);                                                   /* SBSW_SOAD_PARAMETER_IDX */
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_SO_CON_STATE, SoConIdx);
  }
  /* #21 Stop transmission of this PDU otherwise. */
  else
  {
    SoAd_TxTcpQueue_SetElement(SoConIdx, pduRouteIdx, 0u, TRUE);
  }

  /* #30 Call TpTxConfirmation of upper layer with negative result if transmission is continued in main function. */
  if ( CalledByMain == TRUE )
  {
    SoAd_GetTpTxConfirmationCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfPduRoute(pduRouteIdx))(                             /* SBSW_SOAD_FUNCTION_PTR */
      SoAd_GetTxConfPduIdOfPduRoute(pduRouteIdx), E_NOT_OK);
  }
} /* SoAd_TxTp_TcpTransmitHandleFail() */

/**********************************************************************************************************************
 *  SoAd_TxTp_TcpCopyTxData()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_TxTp_TcpCopyTxData(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfPduRouteType PduRouteIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 BufLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  PduInfoType           pduInfo;
  SoAd_SizeOfTxMgtType  txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(SoConIdx);
  PduLengthType         availableBufLength = 0u;
  BufReq_ReturnType     retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Copy PDU header to provided buffer if used. */
  if ( SoAd_IsPduHdrEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) == TRUE )
  {
    SoAd_Tx_CopyTxDataPduHeader(SoConIdx, PduRouteIdx, &BufPtr, &BufLength);                                           /* SBSW_SOAD_POINTER_FORWARD */
  }

  /* #20 Check if provided buffer is not sufficient to copy PDU data in this CopyTxData call. */
  if ( BufLength == 0u )
  {
    retVal = BUFREQ_OK;
  }
  else
  /* #21 Copy PDU data otherwise. */
  {
    /* #30 Prepare buffer for TpCopyTxData call. */
    pduInfo.SduDataPtr = BufPtr;
    pduInfo.SduLength = (PduLengthType)BufLength;

    /* #40 Call TpCopyTxData of upper layer and check if calls succeeds. */
    if ( SoAd_TxTp_CallCopyTxData(PduRouteIdx, &pduInfo, &availableBufLength) == BUFREQ_OK )                           /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    {
      /* #50 Decrement pending data to be transmitted. */
      SoAd_SetTxBytesPendingOfTxMgt(txMgtIdx, (PduLengthType)(SoAd_GetTxBytesPendingOfTxMgt(txMgtIdx) - BufLength));   /* SBSW_SOAD_OPTIONAL_CSL03 */
      retVal = BUFREQ_OK;
    }
    /* #41 Indicate that transmission failed otherwise. */
    else
    {
      retVal = BUFREQ_E_NOT_OK;
    }
  }

  return retVal;
} /* SoAd_TxTp_TcpCopyTxData() */

/**********************************************************************************************************************
 *  SoAd_TxTp_TcpTxConfirmation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTp_TcpTxConfirmation(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfPduRouteType PduRouteIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfTxMgtType txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(SoConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if immediate TxConfirmation for TP-API is disabled. */
  if ( SoAd_IsImmedTpTxConfOfSocketTcp(SoAd_GetSocketTcpIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx))) == FALSE )
  {
    /* #20 Check if cancellation is not requested. */
    if ( SoAd_IsCancelRequestedOfTxMgt(txMgtIdx) == FALSE )
    {
      /* #30 Reconnect socket connection if socket connection was opened on reception. */
      SoAd_SoCon_RequestReconnect(SoConIdx);

      /* #40 Finish TP transmission. */
      SoAd_SetPduRouteIdxOfTxMgt(txMgtIdx, SoAd_GetSizeOfPduRoute());                                                  /* SBSW_SOAD_OPTIONAL_CSL03 */
      SoAd_SetTxBytesLenOfTxMgt(txMgtIdx, 0u);                                                                         /* SBSW_SOAD_OPTIONAL_CSL03 */

      SoAd_SetSoConTxActiveIdxOfSocketDyn(SoAd_GetSocketIdxOfSoCon(SoConIdx), SoAd_GetSizeOfSoCon());                  /* SBSW_SOAD_CSL03 */

      /* #50 Call TxConfirmation of user. */
      SoAd_GetTpTxConfirmationCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfPduRoute(PduRouteIdx))(                           /* SBSW_SOAD_FUNCTION_PTR */
        SoAd_GetTxConfPduIdOfPduRoute(PduRouteIdx), E_OK);
    }
  }
} /* SoAd_TxTp_TcpTxConfirmation() */
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TxTp_UdpTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxTp_UdpTransmit(
  SoAd_SizeOfSoConType SoConIdx,
  boolean CalledByMain)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfTxMgtType            txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfTpTxBufferConfigType tpTxBufferConfigIdx = SoAd_GetTpTxBufferConfigIdxOfSoCon(SoConIdx);
  Std_ReturnType                  retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Update UDP alive supervision timeout. */
  SoAd_SoCon_UpdateUdpAliveTimeout(SoConIdx);

  /* #20 Copy PDU header to TP transmission buffer. */
  SoAd_TxTp_UdpCopyPduHdr(SoConIdx);

  /* #30 Copy PDU to TP transmission buffer. */
  if ( SoAd_TxTp_UdpCopyPdu(SoConIdx, CalledByMain) == E_OK )
  {
    /* #40 Transmit PDU over UDP socket if PDU is copied completely to TP transmission buffer. */
    if ( SoAd_GetTxBytesLenOfTxMgt(txMgtIdx) ==
      (SoAd_GetTpTxBufferIdxOfTpTxBufferConfigDyn(tpTxBufferConfigIdx) -
        SoAd_GetTpTxBufferStartIdxOfTpTxBufferConfig(tpTxBufferConfigIdx)) )
    {
      retVal = SoAd_TxTp_UdpTransmitOnSocket(SoConIdx, CalledByMain);
    }
    else
    {
      retVal = E_OK;
    }
  }

  return retVal;
} /* SoAd_TxTp_UdpTransmit() */

/**********************************************************************************************************************
 *  SoAd_TxTp_UdpCopyPduHdr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTp_UdpCopyPduHdr(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfTxMgtType            txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfPduRouteType         pduRouteIdx = SoAd_GetPduRouteIdxOfTxMgt(txMgtIdx);
  SoAd_SizeOfTpTxBufferConfigType tpTxBufferConfigIdx = SoAd_GetTpTxBufferConfigIdxOfSoCon(SoConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if PDU header is enabled. */
  if ( SoAd_IsPduHdrEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoConIdx)) == TRUE )
  {
    /* #20 Check if PDU header is not copied yet. */
    if ( SoAd_GetTpTxBufferIdxOfTpTxBufferConfigDyn(tpTxBufferConfigIdx) ==
      SoAd_GetTpTxBufferStartIdxOfTpTxBufferConfig(tpTxBufferConfigIdx) )
    {
      /* #30 Copy PDU header to TP transmission buffer. */
      SoAd_Util_CopyPduHdr2Buf(SoAd_GetTxPduHdrIdOfPduRouteDest(SoAd_GetPduRouteDestStartIdxOfPduRoute(pduRouteIdx)),  /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
        (SoAd_PduHdrLenType)(SoAd_GetTxBytesLenOfTxMgt(txMgtIdx) - SOAD_PDU_HDR_SIZE),
        SoAd_GetAddrTpTxBuffer(SoAd_GetTpTxBufferStartIdxOfTpTxBufferConfig(tpTxBufferConfigIdx)),
        0u, SOAD_PDU_HDR_SIZE);

      SoAd_SetTpTxBufferIdxOfTpTxBufferConfigDyn(tpTxBufferConfigIdx,                                                  /* SBSW_SOAD_OPTIONAL_CSL03 */
        (SoAd_TpTxBufferIdxOfTpTxBufferConfigDynType)
          (SoAd_GetTpTxBufferStartIdxOfTpTxBufferConfig(tpTxBufferConfigIdx) + SOAD_PDU_HDR_SIZE));
    }
  }
} /* SoAd_TxTp_UdpCopyPduHdr() */

/**********************************************************************************************************************
 *  SoAd_TxTp_UdpCopyPdu()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxTp_UdpCopyPdu(
  SoAd_SizeOfSoConType SoConIdx,
  boolean CalledByMain)
{
  /* ----- Local Variables ---------------------------------------------- */
  PduInfoType                     pduInfo = { NULL_PTR, 0u };
  PduLengthType                   availableBufLen = 0u;
  PduLengthType                   maxExpectedBufLen;
  SoAd_SizeOfTxMgtType            txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfPduRouteType         pduRouteIdx = SoAd_GetPduRouteIdxOfTxMgt(txMgtIdx);
  SoAd_SizeOfTpTxBufferConfigType tpTxBufferConfigIdx = SoAd_GetTpTxBufferConfigIdxOfSoCon(SoConIdx);
  boolean                         continueTransmission = TRUE;
  Std_ReturnType                  retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate until PDU is copied completely to TP transmission buffer. */
  while ( SoAd_GetTxBytesLenOfTxMgt(txMgtIdx) >
    (SoAd_GetTpTxBufferIdxOfTpTxBufferConfigDyn(tpTxBufferConfigIdx) -
      SoAd_GetTpTxBufferStartIdxOfTpTxBufferConfig(tpTxBufferConfigIdx)) )
  {
    /* #20 Call CopyTxData and check if call succeeds. */
    if ( SoAd_TxTp_CallCopyTxData(pduRouteIdx, &pduInfo, &availableBufLen) == BUFREQ_OK )                              /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    {
      /* #30 Increment offset of buffer by copied data length. */
      SoAd_SetTpTxBufferIdxOfTpTxBufferConfigDyn(tpTxBufferConfigIdx,                                                  /* SBSW_SOAD_CSL03 */
        (SoAd_TpTxBufferIdxOfTpTxBufferConfigDynType)(SoAd_GetTpTxBufferIdxOfTpTxBufferConfigDyn(tpTxBufferConfigIdx) +
          pduInfo.SduLength));

      /* #40 Check if data is still pending. */
      if ( SoAd_GetTxBytesLenOfTxMgt(txMgtIdx) >
        (SoAd_GetTpTxBufferIdxOfTpTxBufferConfigDyn(tpTxBufferConfigIdx) -
          SoAd_GetTpTxBufferStartIdxOfTpTxBufferConfig(tpTxBufferConfigIdx)) )
      {
        /* #50 Set maximum expected available upper layer buffer size to pending PDU data. */
        maxExpectedBufLen = (PduLengthType)(SoAd_GetTxBytesLenOfTxMgt(txMgtIdx) -
          (SoAd_GetTpTxBufferIdxOfTpTxBufferConfigDyn(tpTxBufferConfigIdx) -
            SoAd_GetTpTxBufferStartIdxOfTpTxBufferConfig(tpTxBufferConfigIdx)));

        /* #60 Overwrite available upper layer buffer size if it exceeds the maximum expected available buffe size. */
        if ( availableBufLen > maxExpectedBufLen )
        {
          availableBufLen = maxExpectedBufLen;
        }

        /* #70 Set pointer to TP transmission buffer and length for next CopyTxData call if buffer is available. */
        if ( availableBufLen > 0u )
        {
          pduInfo.SduDataPtr = SoAd_GetAddrTpTxBuffer(SoAd_GetTpTxBufferIdxOfTpTxBufferConfigDyn(tpTxBufferConfigIdx));
          pduInfo.SduLength = availableBufLen;
        }
        /* #71 Indicate to stop transmission in this context and continue transmission in main function otherwise. */
        else
        {
          SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_TP_TX_SO_CON, SoConIdx);

          continueTransmission = FALSE;
        }
      }

      retVal = E_OK;
    }
    /* #21 Handle case if call to CopyTxData failed otherwise. */
    else
    {
      /* #80 Terminate TP session. */
      SoAd_TxTp_UdpTerminateTransmit(SoConIdx, CalledByMain, E_NOT_OK);

      /* #90 Return that transmission has failed. */
      continueTransmission = FALSE;
    }

    /* #100 Stop transmission in this context if CopyTxData failed or no data for transmission is available. */
    if ( continueTransmission == FALSE )
    {
      break;
    }
  }

  return retVal;
} /* SoAd_TxTp_UdpCopyPdu() */

/**********************************************************************************************************************
 *  SoAd_TxTp_UdpTransmitOnSocket()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxTp_UdpTransmitOnSocket(
  SoAd_SizeOfSoConType SoConIdx,
  boolean CalledByMain)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfTxMgtType            txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfTpTxBufferConfigType tpTxBufferConfigIdx = SoAd_GetTpTxBufferConfigIdxOfSoCon(SoConIdx);
  Std_ReturnType                  retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare transmission of TP-PDU over UDP. */
  SoAd_SetTxBufPtrOfTxMgt(txMgtIdx,                                                                                    /* SBSW_SOAD_CSL03 */
    SoAd_GetAddrTpTxBuffer(SoAd_GetTpTxBufferStartIdxOfTpTxBufferConfig(tpTxBufferConfigIdx)));

  /* #20 Try to transmit PDU. */
  /* PRQA S 310 3 */ /* MD_SoAd_11.4_struct */
  if ( SoAd_TcpIp_UdpTransmit(SoAd_GetSocketIdxOfSoCon(SoConIdx),                                                      /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
      SoAd_GetSocketIdOfSocketDyn(SoAd_GetSocketIdxOfSoCon(SoConIdx)),
      SOAD_A_P2VAR(SoAd_SockAddrType)SoAd_GetAddrRemAddrDynOfSoConDyn(SoConIdx),
      (uint16)SoAd_GetTxBytesLenOfTxMgt(txMgtIdx)) == E_OK )
  {
    /* #201 Terminate TP session positively. */
    SoAd_TxTp_UdpTerminateTransmit(SoConIdx, CalledByMain, E_OK);

    retVal = E_OK;
  }
  else
  {
    /* #202 Terminate TP session negatively otherwise. */
    SoAd_TxTp_UdpTerminateTransmit(SoConIdx, CalledByMain, E_NOT_OK);

    retVal = E_NOT_OK;
  }

  return retVal;
} /* SoAd_TxTp_UdpTransmitOnSocket() */

/**********************************************************************************************************************
 *  SoAd_TxTp_UdpTerminateTransmit()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTp_UdpTerminateTransmit(
  SoAd_SizeOfSoConType SoConIdx,
  boolean CalledByMain,
  Std_ReturnType Result)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfTxMgtType            txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(SoConIdx);
  SoAd_SizeOfPduRouteType         pduRouteIdx = SoAd_GetPduRouteIdxOfTxMgt(txMgtIdx);
  SoAd_SizeOfTpTxBufferConfigType tpTxBufferConfigIdx = SoAd_GetTpTxBufferConfigIdxOfSoCon(SoConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Release TP transmission buffer. */
  SoAd_SetTpTxBufferIdxOfTpTxBufferConfigDyn(tpTxBufferConfigIdx,                                                      /* SBSW_SOAD_OPTIONAL_CSL03 */
    SoAd_GetTpTxBufferStartIdxOfTpTxBufferConfig(tpTxBufferConfigIdx));

  /* #20 Reset TP session. */
  SoAd_SetPduRouteIdxOfTxMgt(txMgtIdx, SoAd_GetSizeOfPduRoute());                                                      /* SBSW_SOAD_OPTIONAL_CSL03 */
  SoAd_SetTxBytesLenOfTxMgt(txMgtIdx, 0u);                                                                             /* SBSW_SOAD_OPTIONAL_CSL03 */
  SoAd_SetTxBytesPendingOfTxMgt(txMgtIdx, 0u);                                                                         /* SBSW_SOAD_OPTIONAL_CSL03 */

  SoAd_SetSoConTxActiveIdxOfSocketDyn(SoAd_GetSocketIdxOfSoCon(SoConIdx), SoAd_GetSizeOfSoCon());                      /* SBSW_SOAD_CSL03 */

  /* #30 Check if transmission succeeded. */
  if ( Result == E_OK )
  {
    /* #300 Call TpTxConfirmation of upper layer with positive result. */
    SoAd_GetTpTxConfirmationCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfPduRoute(pduRouteIdx))(                             /* SBSW_SOAD_FUNCTION_PTR */
      SoAd_GetTxConfPduIdOfPduRoute(pduRouteIdx), E_OK);

    /* #301 Reconnect socket connection if socket connection has auto setup enabled and wildcards configured. */
    SoAd_SoCon_Reconnect(SoConIdx);
  }
  /* #31 Check if transmission context is main function otherwise. */
  else if ( CalledByMain == TRUE )
  {
    /* #310 Call TpTxConfirmation of upper layer with negative result if transmission context is main function. */
    SoAd_GetTpTxConfirmationCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfPduRoute(pduRouteIdx))(                             /* SBSW_SOAD_FUNCTION_PTR */
      SoAd_GetTxConfPduIdOfPduRoute(pduRouteIdx), E_NOT_OK);
  }
  /* #32 No further action required otherwise. */
  else
  {
    /* Nothing to do. */
  }
} /* SoAd_TxTp_UdpTerminateTransmit() */

/**********************************************************************************************************************
 *  SoAd_TxTp_UdpCopyTxData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTp_UdpCopyTxData(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 BufLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  SOAD_P2VAR(uint8)     txBufPtr;
  SoAd_SizeOfTxMgtType  txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(SoConIdx);
  PduLengthType         bytesCopied;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate pending data to be copied. */
  bytesCopied = SoAd_GetTxBytesLenOfTxMgt(txMgtIdx) - SoAd_GetTxBytesPendingOfTxMgt(txMgtIdx);

  /* #20 Copy data from TP transmission buffer to provided buffer. */
  txBufPtr = SoAd_GetTxBufPtrOfTxMgt(txMgtIdx);
  IpBase_Copy(                                                                                                         /* SBSW_SOAD_POINTER_AND_TX_BUFFER_POINTER_FORWARD */
    SOAD_A_P2VAR(IpBase_CopyDataType)&BufPtr[0],
    SOAD_A_P2CONST(IpBase_CopyDataType)&txBufPtr[bytesCopied],
    BufLength);

  /* #30 Decrement pending length. */
  SoAd_SetTxBytesPendingOfTxMgt(txMgtIdx, SoAd_GetTxBytesPendingOfTxMgt(txMgtIdx) - BufLength);                        /* SBSW_SOAD_OPTIONAL_CSL03 */
} /* SoAd_TxTp_UdpCopyTxData() */

#if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
 *  SoAd_TxTcpQueue_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTcpQueue_Init(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_TcpTxQueueDataIterType tcpTxQueueDataIter;
  SoAd_SizeOfTcpTxQueueType   tcpTxQueueIdx = SoAd_GetTcpTxQueueIdxOfSoCon(SoConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Tx TCP queue is configured. */
  if ( SoAd_IsTcpTxQueueUsedOfSoCon(SoConIdx) == TRUE )
  {
    /* #20 Initialize all queue elements. */
    for ( tcpTxQueueDataIter = SoAd_GetTcpTxQueueDataStartIdxOfTcpTxQueue(tcpTxQueueIdx);
      tcpTxQueueDataIter < SoAd_GetTcpTxQueueDataEndIdxOfTcpTxQueue(tcpTxQueueIdx);
      tcpTxQueueDataIter++ )
    {
      SoAd_SetPduRouteIdxOfTcpTxQueueData(tcpTxQueueDataIter, SoAd_GetSizeOfPduRoute());                               /* SBSW_SOAD_CSL03 */
      SoAd_SetLenOfTcpTxQueueData(tcpTxQueueDataIter, 0u);                                                             /* SBSW_SOAD_CSL03 */
    }

    /* #30 Initialize management struct. */
    SoAd_SetTcpTxQueueDataIdxOfTcpTxQueueMgt(tcpTxQueueIdx, SoAd_GetTcpTxQueueDataStartIdxOfTcpTxQueue(tcpTxQueueIdx));/* SBSW_SOAD_OPTIONAL_CSL03 */
    SoAd_SetLvlOfTcpTxQueueMgt(tcpTxQueueIdx, 0u);                                                                     /* SBSW_SOAD_OPTIONAL_CSL03 */
    SoAd_SetTotLenOfTcpTxQueueMgt(tcpTxQueueIdx, 0u);                                                                  /* SBSW_SOAD_OPTIONAL_CSL03 */
  }
} /* SoAd_TxTcpQueue_Init() */

/**********************************************************************************************************************
 *  SoAd_TxTcpQueue_Clear()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTcpQueue_Clear(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_TcpTxQueueDataIterType tcpTxQueueDataIter;
  SoAd_SizeOfTcpTxQueueType   tcpTxQueueIdx = SoAd_GetTcpTxQueueIdxOfSoCon(SoConIdx);
  SoAd_SizeOfPduRouteType     pduRouteIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that call is interrupted and Tx TCP Queue becomes inconsistent. */
  SOAD_BEGIN_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Check if Tx TCP queue is configured. */
  if ( SoAd_IsTcpTxQueueUsedOfSoCon(SoConIdx) == TRUE )
  {
    /* #30 Initialize all queue elements. */
    for ( tcpTxQueueDataIter = SoAd_GetTcpTxQueueDataStartIdxOfTcpTxQueue(tcpTxQueueIdx);
      tcpTxQueueDataIter < SoAd_GetTcpTxQueueDataEndIdxOfTcpTxQueue(tcpTxQueueIdx);
      tcpTxQueueDataIter++ )
    {
      pduRouteIdx = SoAd_GetPduRouteIdxOfTcpTxQueueData(tcpTxQueueDataIter);

      /* #300 Call IF TxConfirmation if pending. */
      if ( (pduRouteIdx != SoAd_GetSizeOfPduRoute()) &&
        (SoAd_GetUpperLayerApiOfPduRoute(pduRouteIdx) == SOAD_UL_API_IF) )
      {
        SoAd_TxIf_TcpTxConfirmation(SoConIdx, pduRouteIdx, TRUE);
      }

      SoAd_SetPduRouteIdxOfTcpTxQueueData(tcpTxQueueDataIter, SoAd_GetSizeOfPduRoute());                               /* SBSW_SOAD_CSL03 */
      SoAd_SetLenOfTcpTxQueueData(tcpTxQueueDataIter, 0u);                                                             /* SBSW_SOAD_CSL03 */
    }

    /* #40 Initialize management struct. */
    SoAd_SetTcpTxQueueDataIdxOfTcpTxQueueMgt(tcpTxQueueIdx, SoAd_GetTcpTxQueueDataStartIdxOfTcpTxQueue(tcpTxQueueIdx));/* SBSW_SOAD_OPTIONAL_CSL03 */
    SoAd_SetLvlOfTcpTxQueueMgt(tcpTxQueueIdx, 0u);                                                                     /* SBSW_SOAD_OPTIONAL_CSL03 */
    SoAd_SetTotLenOfTcpTxQueueMgt(tcpTxQueueIdx, 0u);                                                                  /* SBSW_SOAD_OPTIONAL_CSL03 */
  }

  /* #50 Leave critical section. */
  SOAD_END_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
} /* SoAd_TxTcpQueue_Clear() */

/**********************************************************************************************************************
 *  SoAd_TxTcpQueue_ReserveNextElement()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxTcpQueue_ReserveNextElement(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfPduRouteType PduRouteIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfTcpTxQueueType     tcpTxQueueIdx = SoAd_GetTcpTxQueueIdxOfSoCon(SoConIdx);
  SoAd_SizeOfTcpTxQueueDataType writeIdx = SoAd_GetTcpTxQueueDataIdxOfTcpTxQueueMgt(tcpTxQueueIdx);
  Std_ReturnType                retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that call is interrupted and Tx TCP Queue becomes inconsistent. */
  SOAD_BEGIN_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Check if TCP Tx queue has elements left. */
  if ( SoAd_GetLvlOfTcpTxQueueMgt(tcpTxQueueIdx) <
    (SoAd_GetTcpTxQueueDataEndIdxOfTcpTxQueue(tcpTxQueueIdx) -
      SoAd_GetTcpTxQueueDataStartIdxOfTcpTxQueue(tcpTxQueueIdx)) )
  {
    /* #30 Get next element index if queue is filled. */
    if ( SoAd_GetLvlOfTcpTxQueueMgt(tcpTxQueueIdx) > 0u )
    {
      retVal = SoAd_TxTcpQueue_GetNextElement(SoConIdx, &writeIdx);                                                    /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    }
    /* #31 Use current element index if queue is empty. */
    else
    {
      retVal = E_OK;
    }
  }

  /* #40 Reserve element if free element index was found. */
  if ( retVal == E_OK )
  {
    SoAd_IncLvlOfTcpTxQueueMgt(tcpTxQueueIdx);                                                                         /* SBSW_SOAD_OPTIONAL_CSL03 */
    SoAd_SetPduRouteIdxOfTcpTxQueueData(writeIdx, PduRouteIdx);                                                        /* SBSW_SOAD_INDEX_BY_FUNCTION_OR_CALCULATED_CSL03 */
    SoAd_SetLenOfTcpTxQueueData(writeIdx, 0u);                                                                         /* SBSW_SOAD_INDEX_BY_FUNCTION_OR_CALCULATED_CSL03 */
  }

  /* #50 Leave critical section. */
  SOAD_END_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return retVal;
} /* SoAd_TxTcpQueue_ReserveNextElement() */

/**********************************************************************************************************************
 *  SoAd_TxTcpQueue_GetNextElement()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxTcpQueue_GetNextElement(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(SoAd_SizeOfTcpTxQueueDataType, AUTOMATIC, SOAD_APPL_DATA) WriteIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfTcpTxQueueType     tcpTxQueueIdx = SoAd_GetTcpTxQueueIdxOfSoCon(SoConIdx);
  SoAd_SizeOfTcpTxQueueDataType lastLvl;
  SoAd_SizeOfTcpTxQueueDataType lastWriteIdx;
  Std_ReturnType                retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get last write index. */
  lastLvl = (SoAd_SizeOfTcpTxQueueDataType)(SoAd_GetLvlOfTcpTxQueueMgt(tcpTxQueueIdx) - 1u);
  if ( (SoAd_GetTcpTxQueueDataIdxOfTcpTxQueueMgt(tcpTxQueueIdx) + lastLvl) >=
    SoAd_GetTcpTxQueueDataEndIdxOfTcpTxQueue(tcpTxQueueIdx) )
  {
    /* #100 Get last write index in case of queue wrap around. */
    lastWriteIdx = (SoAd_SizeOfTcpTxQueueDataType)(SoAd_GetTcpTxQueueDataStartIdxOfTcpTxQueue(tcpTxQueueIdx) +
      (lastLvl - (SoAd_GetTcpTxQueueDataEndIdxOfTcpTxQueue(tcpTxQueueIdx) -
        SoAd_GetTcpTxQueueDataIdxOfTcpTxQueueMgt(tcpTxQueueIdx))));
  }
  else
  {
    /* #101 Get last write index in case of no queue wrap around. */
    lastWriteIdx = (SoAd_SizeOfTcpTxQueueDataType)(SoAd_GetTcpTxQueueDataIdxOfTcpTxQueueMgt(tcpTxQueueIdx) + lastLvl);
  }

  /* #20 Check if last index is completely written and new entry is possible. */
  if ( SoAd_GetLenOfTcpTxQueueData(lastWriteIdx) != 0u )
  {
    /* #200 Get new write index. */
    if ( (lastWriteIdx + 1u) == SoAd_GetTcpTxQueueDataEndIdxOfTcpTxQueue(tcpTxQueueIdx) )
    {
      /* #2000 Get new write index in case of queue wrap around. */
      *WriteIdx = SoAd_GetTcpTxQueueDataStartIdxOfTcpTxQueue(tcpTxQueueIdx);                                           /* SBSW_SOAD_POINTER_WRITE */
    }
    else
    {
      /* #2001 Get new write index in case of no queue wrap around. */
      *WriteIdx = (SoAd_SizeOfTcpTxQueueDataType)(lastWriteIdx + 1u);                                                  /* SBSW_SOAD_POINTER_WRITE */
    }
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_TxTcpQueue_GetNextElement() */

/**********************************************************************************************************************
 *  SoAd_TxTcpQueue_SetElement()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTcpQueue_SetElement(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfPduRouteType PduRouteIdx,
  PduLengthType Len,
  boolean Release)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfTcpTxQueueType     tcpTxQueueIdx = SoAd_GetTcpTxQueueIdxOfSoCon(SoConIdx);
  SoAd_SizeOfTcpTxQueueDataType writeIdx;
  uint16                        lvl = SoAd_GetLvlOfTcpTxQueueMgt(tcpTxQueueIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that call is interrupted and Tx TCP queue becomes inconsistent. */
  SOAD_BEGIN_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Check if queue is filled by at least one reserved element. */
  if ( lvl > 0u )
  {
    /* #30 Get last element index in case of queue wrap around. */
    lvl--;
    if ( (SoAd_GetTcpTxQueueDataIdxOfTcpTxQueueMgt(tcpTxQueueIdx) + lvl) >=
      SoAd_GetTcpTxQueueDataEndIdxOfTcpTxQueue(tcpTxQueueIdx) )
    {
      writeIdx = (SoAd_SizeOfTcpTxQueueDataType)(SoAd_GetTcpTxQueueDataStartIdxOfTcpTxQueue(tcpTxQueueIdx) +
        (lvl - (SoAd_GetTcpTxQueueDataEndIdxOfTcpTxQueue(tcpTxQueueIdx) -
          SoAd_GetTcpTxQueueDataIdxOfTcpTxQueueMgt(tcpTxQueueIdx))));
    }
    /* #31 Get last element index in case of no queue wrap around. */
    else
    {
      writeIdx = (SoAd_SizeOfTcpTxQueueDataType)(SoAd_GetTcpTxQueueDataIdxOfTcpTxQueueMgt(tcpTxQueueIdx) + lvl);
    }

    /* #40 Check if element is reserved. */
    if ( PduRouteIdx == SoAd_GetPduRouteIdxOfTcpTxQueueData(writeIdx) )
    {
      /* #400 Release element if required. */
      if ( Release == TRUE )
      {
        SoAd_SetPduRouteIdxOfTcpTxQueueData(writeIdx, SoAd_GetSizeOfPduRoute());                                       /* SBSW_SOAD_CALCULATED_CSL03 */
        SoAd_DecLvlOfTcpTxQueueMgt(tcpTxQueueIdx);                                                                     /* SBSW_SOAD_OPTIONAL_CSL03 */
      }
      /* #401 Set element if required. */
      else
      {
        SoAd_SetLenOfTcpTxQueueData(writeIdx, Len);                                                                    /* SBSW_SOAD_CALCULATED_CSL03 */
        SoAd_SetTotLenOfTcpTxQueueMgt(tcpTxQueueIdx, SoAd_GetTotLenOfTcpTxQueueMgt(tcpTxQueueIdx) + Len);              /* SBSW_SOAD_OPTIONAL_CSL03 */
      }
    }
  }

  /* #50 Leave critical section. */
  SOAD_END_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
} /* SoAd_TxTcpQueue_SetElement() */

/**********************************************************************************************************************
 *  SoAd_TxTcpQueue_GetTotalLength()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(uint32, SOAD_CODE) SoAd_TxTcpQueue_GetTotalLength(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 totalLen;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Return total length of Tx TCP queue. */
  totalLen = SoAd_GetTotLenOfTcpTxQueueMgt(SoAd_GetTcpTxQueueIdxOfSoCon(SoConIdx));

  return totalLen;
} /* SoAd_TxTcpQueue_GetTotalLength() */

/**********************************************************************************************************************
 *  SoAd_TxTcpQueue_TxConfirmation()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxTcpQueue_TxConfirmation(
  SoAd_SizeOfSoConType SoConIdx,
  PduLengthType Len)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfTcpTxQueueType     tcpTxQueueIdx = SoAd_GetTcpTxQueueIdxOfSoCon(SoConIdx);
  SoAd_SizeOfTcpTxQueueDataType tcpTxQueueDataIdx;
  SoAd_SizeOfPduRouteType       pduRouteIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that call is interrupted and Tx TCP queue becomes inconsistent. */
  SOAD_BEGIN_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Iterate over queue until all elements are released or length to be released is 0. */
  while ( Len > 0u )
  {
    /* #30 Check if queue is filled. */
    if ( SoAd_TxTcpQueue_GetTotalLength(SoConIdx) > 0u )
    {
      tcpTxQueueDataIdx = SoAd_GetTcpTxQueueDataIdxOfTcpTxQueueMgt(tcpTxQueueIdx);

      /* #40 Check if PDU is confirmed completely. */
      if ( SoAd_GetLenOfTcpTxQueueData(tcpTxQueueDataIdx) <= Len )
      {
        pduRouteIdx = SoAd_GetPduRouteIdxOfTcpTxQueueData(tcpTxQueueDataIdx);

        /* #400 Remove element from queue. */
        Len -= SoAd_GetLenOfTcpTxQueueData(tcpTxQueueDataIdx);

        SoAd_SetTotLenOfTcpTxQueueMgt(tcpTxQueueIdx,                                                                   /* SBSW_SOAD_OPTIONAL_CSL03 */
          SoAd_GetTotLenOfTcpTxQueueMgt(tcpTxQueueIdx) - SoAd_GetLenOfTcpTxQueueData(tcpTxQueueDataIdx));

        SoAd_SetLenOfTcpTxQueueData(tcpTxQueueDataIdx, 0u);                                                            /* SBSW_SOAD_CALCULATED_CSL03 */
        SoAd_SetPduRouteIdxOfTcpTxQueueData(tcpTxQueueDataIdx, SoAd_GetSizeOfPduRoute());                              /* SBSW_SOAD_CALCULATED_CSL03 */

        SoAd_DecLvlOfTcpTxQueueMgt(tcpTxQueueIdx);                                                                     /* SBSW_SOAD_OPTIONAL_CSL03 */

        if ( (tcpTxQueueDataIdx + 1u) == SoAd_GetTcpTxQueueDataEndIdxOfTcpTxQueue(tcpTxQueueIdx) )
        { /* wrap around */
          SoAd_SetTcpTxQueueDataIdxOfTcpTxQueueMgt(tcpTxQueueIdx,                                                      /* SBSW_SOAD_OPTIONAL_CSL03 */
            SoAd_GetTcpTxQueueDataStartIdxOfTcpTxQueue(tcpTxQueueIdx));
        }
        else
        { /* no wrap around */
          SoAd_SetTcpTxQueueDataIdxOfTcpTxQueueMgt(tcpTxQueueIdx, (SoAd_TcpTxQueueDataIdxOfTcpTxQueueMgtType)          /* SBSW_SOAD_OPTIONAL_CSL03 */
            (SoAd_GetTcpTxQueueDataIdxOfTcpTxQueueMgt(tcpTxQueueIdx) + 1u));
        }

        /* #401 Leave critical section. */
        SOAD_END_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

        /* #402 Confirm PDU transmission for TP-PDU. */
        if ( SoAd_GetUpperLayerApiOfPduRoute(pduRouteIdx) == SOAD_UL_API_TP )
        {
          SoAd_TxTp_TcpTxConfirmation(SoConIdx, pduRouteIdx);
        }
        /* #403 Confirm PDU transmission for IF-PDU otherwise. */
        else
        {
          SoAd_TxIf_TcpTxConfirmation(SoConIdx, pduRouteIdx, FALSE);
        }

        /* #404 Enter critical section again. */
        SOAD_BEGIN_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
      }
      /* #41 Confirm PDU partly otherwise. */
      else
      {
        SoAd_SetTotLenOfTcpTxQueueMgt(tcpTxQueueIdx, SoAd_GetTotLenOfTcpTxQueueMgt(tcpTxQueueIdx) - Len);              /* SBSW_SOAD_OPTIONAL_CSL03 */
        SoAd_SetLenOfTcpTxQueueData(tcpTxQueueDataIdx, SoAd_GetLenOfTcpTxQueueData(tcpTxQueueDataIdx) - Len);          /* SBSW_SOAD_CALCULATED_CSL03 */

        Len = 0u;
      }
    }
    /* #31 Abort confirmation otherwise. */
    else
    {
      break;
    }
  }

  /* #50 Leave critical section. */
  SOAD_END_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
} /* SoAd_TxTcpQueue_TxConfirmation() */
#endif /* SOAD_TCP == STD_ON */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_HandleTransmission()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxNPduUdp_HandleTransmission(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32                    elementIdx = 0u;
  uint32                    handleIdx = 0u;
  SoAd_SizeOfNPduUdpTxType  nPduIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all timeouts in this main function cycle. */
  while ( SoAd_TimeoutList_CheckElements(SOAD_TIMEOUT_LIST_N_PDU,                                                      /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    &elementIdx, &handleIdx, SoAd_GlobalCounter) == E_OK )
  {
    nPduIdx = (SoAd_SizeOfNPduUdpTxType)handleIdx;

    /* #20 Try to transmit nPdu. */
    SoAd_TxNPduUdp_Transmit(nPduIdx);
  }
} /* SoAd_TxNPduUdp_HandleTransmission() */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_Transmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxNPduUdp_Transmit(
  SoAd_SizeOfNPduUdpTxType NPduIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Start transmission if not started before. */
  if ( SoAd_IsTransmissionActiveOfNPduUdpTxDyn(NPduIdx) == FALSE )
  {
    SoAd_SetTransmissionActiveOfNPduUdpTxDyn(NPduIdx, TRUE);                                                           /* SBSW_SOAD_PARAMETER_IDX */

    /* #100 Set retry counter for nPdu queue. */
    if ( SoAd_IsNPduUdpTxQueueUsedOfNPduUdpTx(NPduIdx) == TRUE )
    {
      SoAd_SetRetryCntOfNPduUdpTxDyn(NPduIdx, SOAD_N_PDU_UDP_TX_QUEUE_RETRY_CNT_MAIN);                                 /* SBSW_SOAD_PARAMETER_IDX */
    }
  }

  /* #20 Handle transmission of nPdu. */
  if ( SoAd_IsNPduUdpTxQueueUsedOfNPduUdpTx(NPduIdx) == TRUE )
  {
    /* #200 Handle transmission of nPdu queue. */
    SoAd_TxNPduUdp_QueueTransmit(NPduIdx);
  }
  else
  {
    /* #201 Handle transmission of nPdu buffer otherwise. */
    SoAd_TxNPduUdp_BufferSend(NPduIdx);
  }
} /* SoAd_TxNPduUdp_Transmit() */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_SetTriggerTimeout()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxNPduUdp_SetTriggerTimeout(
  SoAd_SizeOfNPduUdpTxType NPduIdx,
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32                    currentTimeoutCnt = 0u;
  SoAd_SizeOfSoConType      soConIdx = SoAd_GetSoConIdxOfNPduUdpTx(NPduIdx);
  SoAd_SizeOfSocketUdpType  socketUdpIdx = SoAd_GetSocketUdpIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx));
  Std_ReturnType            retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if PduRouteDest specific timeout is configured. */
  if ( SoAd_GetUdpTriggerTimeoutOfPduRouteDest(PduRouteDestIdx) > 0u  )
  {
    /* #20 Get timeout value if already running. */
    if ( SoAd_TimeoutList_GetCurrentTimeout(SOAD_TIMEOUT_LIST_N_PDU, NPduIdx, &currentTimeoutCnt,                      /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
      SoAd_GlobalCounter) == E_OK )
    {
      /* #30 Update timeout if configured timeout is smaller than current timeout value. */
      if ( SoAd_GetUdpTriggerTimeoutOfPduRouteDest(PduRouteDestIdx) < currentTimeoutCnt )
      {
        (void)SoAd_TimeoutList_SetElement(SOAD_TIMEOUT_LIST_N_PDU, NPduIdx,
          SoAd_GetUdpTriggerTimeoutOfPduRouteDest(PduRouteDestIdx), SoAd_GlobalCounter);
      }
    }
    /* #21 Set timeout otherwise. */
    else
    {
      retVal = SoAd_TimeoutList_SetElement(SOAD_TIMEOUT_LIST_N_PDU, NPduIdx,
        SoAd_GetUdpTriggerTimeoutOfPduRouteDest(PduRouteDestIdx), SoAd_GlobalCounter);
    }
  }
  /* #11 Check if socket connection specific timeout is configured. */
  else if ( SoAd_GetUdpTriggerTimeoutOfSocketUdp(socketUdpIdx) > 0u )
  {
    /* #40 Get timeout value if already running. */
    if ( SoAd_TimeoutList_GetCurrentTimeout(SOAD_TIMEOUT_LIST_N_PDU, NPduIdx, &currentTimeoutCnt,                      /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
      SoAd_GlobalCounter) == E_OK )
    {
      /* #50 Update timeout if configured timeout is smaller than current timeout value. */
      if ( SoAd_GetUdpTriggerTimeoutOfSocketUdp(socketUdpIdx) < currentTimeoutCnt )
      {
        (void)SoAd_TimeoutList_SetElement(SOAD_TIMEOUT_LIST_N_PDU, NPduIdx,
          SoAd_GetUdpTriggerTimeoutOfSocketUdp(socketUdpIdx), SoAd_GlobalCounter);
      }
    }
    /* #41 Set timeout otherwise. */
    else
    {
      retVal = SoAd_TimeoutList_SetElement(SOAD_TIMEOUT_LIST_N_PDU, NPduIdx,
        SoAd_GetUdpTriggerTimeoutOfSocketUdp(socketUdpIdx), SoAd_GlobalCounter);
    }
  }
  /* #12 Assume that no timeout has to be set otherwise. */
  else
  {
    /* Nothing to do. */
  }

  return retVal;
} /* SoAd_TxNPduUdp_SetTriggerTimeout() */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_Clear()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxNPduUdp_Clear(
  SoAd_SizeOfNPduUdpTxType NPduIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType soConIdx = SoAd_GetSoConIdxOfNPduUdpTx(NPduIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset management structs. */
  SoAd_SetTotalLenOfNPduUdpTxDyn(NPduIdx, 0u);                                                                         /* SBSW_SOAD_PARAMETER_IDX */
  SoAd_SetTransmissionActiveOfNPduUdpTxDyn(NPduIdx, FALSE);                                                            /* SBSW_SOAD_PARAMETER_IDX */

  /* #20 Remove timeout from list. */
  SoAd_TimeoutList_RemoveElement(SOAD_TIMEOUT_LIST_N_PDU, NPduIdx);

  /* #30 Clear nPdu queue. */
  if ( SoAd_IsNPduUdpTxQueueUsedOfNPduUdpTx(NPduIdx) == TRUE )
  {
    SoAd_NPduUdpTxQueueIterType nPduUdpTxQueueIter;

    /* #300 Clear nPdu queue elements. */
    for ( nPduUdpTxQueueIter = SoAd_GetNPduUdpTxQueueStartIdxOfNPduUdpTx(NPduIdx);
      nPduUdpTxQueueIter < SoAd_GetNPduUdpTxQueueEndIdxOfNPduUdpTx(NPduIdx);
      nPduUdpTxQueueIter++ )
    {
      SoAd_SizeOfPduRouteType pduRouteIdx = SoAd_GetPduRouteIdxOfNPduUdpTxQueue(nPduUdpTxQueueIter);

      /* #3000 Call TxConfirmation if element is set. */
      if ( pduRouteIdx != SoAd_GetSizeOfPduRoute() )
      {
        SoAd_TxNPduUdp_QueueTxConfirmation(soConIdx, pduRouteIdx, FALSE);
      }

      /* #3001 Reset element struct. */
      SoAd_SetNPduUdpTxBufferIdxOfNPduUdpTxQueue(nPduUdpTxQueueIter, 0u);                                              /* SBSW_SOAD_CSL03 */
      SoAd_SetCopiedOfNPduUdpTxQueue(nPduUdpTxQueueIter, FALSE);                                                       /* SBSW_SOAD_CSL03 */
      SoAd_SetLenOfNPduUdpTxQueue(nPduUdpTxQueueIter, 0u);                                                             /* SBSW_SOAD_CSL03 */
      SoAd_SetPduRouteIdxOfNPduUdpTxQueue(nPduUdpTxQueueIter, SoAd_GetSizeOfPduRoute());                               /* SBSW_SOAD_CSL03 */
    }

    /* #301 Clear nPdu fill level. */
    SoAd_SetLvlOfNPduUdpTxDyn(NPduIdx, 0u);                                                                            /* SBSW_SOAD_PARAMETER_IDX */
  }

  /* #40 Clear nPdu buffer. */
  if ( SoAd_IsNPduUdpTxBufferUsedOfNPduUdpTx(NPduIdx) == TRUE )
  {
    SoAd_SetBufLenOfNPduUdpTxDyn(NPduIdx, 0u);                                                                         /* SBSW_SOAD_PARAMETER_IDX */
  }
} /* SoAd_TxNPduUdp_Clear() */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueAddOrUpdateElement()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(SoAd_NPduReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueueAddOrUpdateElement(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType      soConIdx = SoAd_GetSoConIdxOfPduRouteDest(PduRouteDestIdx);
  PduLengthType             dataLen = PduInfoPtr->SduLength;
  SoAd_SizeOfNPduUdpTxType  nPduIdx = SoAd_GetNPduUdpTxIdxOfSoCon(soConIdx);
  boolean                   elementUpdated = FALSE;
  SoAd_NPduReturnType       nPduRetVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to write nPdu atomic. */
  SOAD_BEGIN_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Calculate PDU length considering PDU header. */
  if ( SoAd_IsPduHdrEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx)) == TRUE )
  {
    dataLen += SOAD_PDU_HDR_SIZE;
  }

  /* #30 Check and update if PDU is already in queue. */
  nPduRetVal = SoAd_TxNPduUdp_QueueUpdateElement(nPduIdx, PduRouteIdx, dataLen, &elementUpdated);                      /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */

  /* #40 Try to add element if PDU is not updated. */
  if ( elementUpdated == FALSE )
  {
    /* #50 Try to add element if nPdu transmission is not active. */
    if ( SoAd_IsTransmissionActiveOfNPduUdpTxDyn(nPduIdx) == FALSE )
    {
      nPduRetVal = SoAd_TxNPduUdp_QueueAddElement(nPduIdx, PduRouteIdx, PduRouteDestIdx, dataLen, PduInfoPtr);         /* SBSW_SOAD_POINTER_FORWARD */
    }
    /* #51 Indicate overflow of nPdu otherwise. */
    else
    {
      nPduRetVal = SOAD_NPDU_OVFL_NEW;
    }
  }

  /* #60 Leave critical section. */
  SOAD_END_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return nPduRetVal;
} /* SoAd_TxNPduUdp_QueueAddOrUpdateElement() */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueUpdateElement()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(SoAd_NPduReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueueUpdateElement(
  SoAd_SizeOfNPduUdpTxType NPduIdx,
  SoAd_SizeOfPduRouteType PduRouteIdx,
  PduLengthType DataLen,
  P2VAR(boolean, AUTOMATIC, SOAD_APPL_VAR) ElementUpdated)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx = SoAd_GetSoConIdxOfNPduUdpTx(NPduIdx);
  SoAd_NPduReturnType   nPduRetVal = SOAD_NPDU_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if trigger transmit is enabled so that element update is possible. */
  if ( SoAd_IsIfTriggerTransmitEnabledOfPduRoute(PduRouteIdx) == TRUE )
  {
    SoAd_NPduUdpTxQueueIterType nPduUdpTxQueueIter;

    /* #20 Iterate over all elements. */
    for ( nPduUdpTxQueueIter = SoAd_GetNPduUdpTxQueueStartIdxOfNPduUdpTx(NPduIdx);
      nPduUdpTxQueueIter <
        (SoAd_NPduUdpTxQueueIterType)
          (SoAd_GetNPduUdpTxQueueStartIdxOfNPduUdpTx(NPduIdx) + SoAd_GetLvlOfNPduUdpTxDyn(NPduIdx));
      nPduUdpTxQueueIter++ )
    {
      /* #30 Check if element contains the requested PDU. */
      if ( SoAd_GetPduRouteIdxOfNPduUdpTxQueue(nPduUdpTxQueueIter) == PduRouteIdx )
      {
        /* #40 Update element. */
        SoAd_SetTotalLenOfNPduUdpTxDyn(NPduIdx,                                                                        /* SBSW_SOAD_PARAMETER_IDX */
          SoAd_GetTotalLenOfNPduUdpTxDyn(NPduIdx) - SoAd_GetLenOfNPduUdpTxQueue(nPduUdpTxQueueIter));
        SoAd_SetLenOfNPduUdpTxQueue(nPduUdpTxQueueIter, DataLen);                                                      /* SBSW_SOAD_CSL03 */
        SoAd_SetTotalLenOfNPduUdpTxDyn(NPduIdx, SoAd_GetTotalLenOfNPduUdpTxDyn(NPduIdx) + DataLen);                    /* SBSW_SOAD_PARAMETER_IDX */
        *ElementUpdated = TRUE;                                                                                        /* SBSW_SOAD_POINTER_WRITE */

        /* #50 Check and indicate if update causes nPdu size overflow. */
        if ( SoAd_GetTotalLenOfNPduUdpTxDyn(NPduIdx) >
          SoAd_GetNPduUdpTxBufferMinOfSocketUdp(
            SoAd_GetSocketUdpIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx))) )
        {
          nPduRetVal = SOAD_NPDU_OVFL_UPDATE;
        }

        break;
      }
    }
  }

  return nPduRetVal;
} /* SoAd_TxNPduUdp_QueueUpdateElement() */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueAddElement()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(SoAd_NPduReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueueAddElement(
  SoAd_SizeOfNPduUdpTxType NPduIdx,
  SoAd_SizeOfPduRouteType PduRouteIdx,
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  PduLengthType DataLen,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx = SoAd_GetSoConIdxOfNPduUdpTx(NPduIdx);
  SoAd_NPduReturnType   nPduRetVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if queue size is sufficient. */
  if ( SoAd_TxNPduUdp_QueueCheckSize(NPduIdx, DataLen) == SOAD_NPDU_OK )
  {
    /* #20 Check if timeout can be set if configured. */
    if ( SoAd_TxNPduUdp_SetTriggerTimeout(NPduIdx, PduRouteDestIdx) == E_OK )
    {
      SoAd_SizeOfNPduUdpTxQueueType currentIdx = (SoAd_SizeOfNPduUdpTxQueueType)
        (SoAd_GetNPduUdpTxQueueStartIdxOfNPduUdpTx(NPduIdx) + SoAd_GetLvlOfNPduUdpTxDyn(NPduIdx));

      /* #30 Store element in queue. */
      SoAd_SetCopiedOfNPduUdpTxQueue(currentIdx, FALSE);                                                               /* SBSW_SOAD_CALCULATED_CSL03 */
      SoAd_SetLenOfNPduUdpTxQueue(currentIdx, DataLen);                                                                /* SBSW_SOAD_CALCULATED_CSL03 */
      SoAd_SetPduRouteIdxOfNPduUdpTxQueue(currentIdx, PduRouteIdx);                                                    /* SBSW_SOAD_CALCULATED_CSL03 */
      SoAd_IncLvlOfNPduUdpTxDyn(NPduIdx);                                                                              /* SBSW_SOAD_PARAMETER_IDX */

      /* #40 Store PDU in buffer if trigger transmit is not used. */
      if ( SoAd_IsIfTriggerTransmitEnabledOfPduRoute(PduRouteIdx) == FALSE )
      {
        SoAd_SetNPduUdpTxBufferIdxOfNPduUdpTxQueue(currentIdx,                                                         /* SBSW_SOAD_CALCULATED_CSL03 */
          (SoAd_NPduUdpTxBufferIdxOfNPduUdpTxQueueType)(SoAd_GetNPduUdpTxBufferStartIdxOfNPduUdpTx(NPduIdx) +
            SoAd_GetBufLenOfNPduUdpTxDyn(NPduIdx)));

        (void)SoAd_TxNPduUdp_BufferAddElement(PduRouteIdx, PduRouteDestIdx, PduInfoPtr);                               /* SBSW_SOAD_POINTER_FORWARD */
      }
      /* #41 Store PDU length only and indicate to call TxConfirmation in main function otherwise. */
      else
      {
        SoAd_SetTotalLenOfNPduUdpTxDyn(NPduIdx, SoAd_GetTotalLenOfNPduUdpTxDyn(NPduIdx) + DataLen);                    /* SBSW_SOAD_PARAMETER_IDX */

        SoAd_TxIf_AddPendingConf(PduRouteIdx, soConIdx);
      }

      nPduRetVal = SOAD_NPDU_OK;
    }
    /* #21 Indicate an error otherwise. */
    else
    {
      nPduRetVal = SOAD_NPDU_NOT_OK;
    }
  }
  /* #11 Indicate overflow otherwise. */
  else
  {
    nPduRetVal = SOAD_NPDU_OVFL_NEW;
  }

  return nPduRetVal;
} /* SoAd_TxNPduUdp_QueueAddElement() */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueCheckSize()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(SoAd_NPduReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueueCheckSize(
  SoAd_SizeOfNPduUdpTxType NPduIdx,
  PduLengthType DataLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType      soConIdx = SoAd_GetSoConIdxOfNPduUdpTx(NPduIdx);
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConIdx);
  SoAd_SizeOfSocketUdpType  socketUdpIdx = SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx);
  SoAd_NPduReturnType       nPduRetVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if new element exceeds the configured queue size. */
  if ( SoAd_GetLvlOfNPduUdpTxDyn(NPduIdx) == SoAd_GetNPduUdpTxQueueSizeOfSocketUdp(socketUdpIdx) )
  {
    nPduRetVal = SOAD_NPDU_OVFL_NEW;
  }
  /* #20 Check if new element exceeds nPdu size otherwise. */
  else if ( (SoAd_GetTotalLenOfNPduUdpTxDyn(NPduIdx) + DataLen) >
    (SoAd_GetNPduUdpTxBufferMinOfSocketUdp(socketUdpIdx)) )
  {
    nPduRetVal = SOAD_NPDU_OVFL_NEW;
  }
  /* #30 Indicate that nPdu size is sufficient to store new PDU otherwise. */
  else
  {
    nPduRetVal = SOAD_NPDU_OK;
  }

  return nPduRetVal;
} /* SoAd_TxNPduUdp_QueueCheckSize() */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueTransmit()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxNPduUdp_QueueTransmit(
  SoAd_SizeOfNPduUdpTxType NPduIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least retryCnt;
  boolean     stopRetry = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Retry transmission if nPdu becomes larger on trigger transmit. */
  for ( retryCnt = 0u; retryCnt < SOAD_N_PDU_UDP_TX_QUEUE_RETRY_CNT_DIRECT; retryCnt++ )
  {
    /* #20 Prepare transmission of nPdu. */
    if ( SoAd_TxNPduUdp_QueuePrepareTransmitSegment(NPduIdx) == E_NOT_OK )
    {
      stopRetry = TRUE;
    }
    /* #21 Transmit nPdu. */
    else if ( SoAd_TxNPduUdp_QueueTransmitSegment(NPduIdx) == E_NOT_OK )
    {
      stopRetry = TRUE;
    }
    /* #22 Check if transmission of nPdu is finished. */
    else if ( SoAd_IsTransmissionActiveOfNPduUdpTxDyn(NPduIdx) == FALSE )
    {
      stopRetry = TRUE;
    }
    /* #23 Retry otherwise. */
    else
    {
      /* Nothing to do. */
    }

    /* #30 Stop retry if required. */
    if ( stopRetry == TRUE )
    {
      break;
    }
  }
} /* SoAd_TxNPduUdp_QueueTransmit() */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueuePrepareTransmitSegment()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueuePrepareTransmitSegment(
  SoAd_SizeOfNPduUdpTxType NPduIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType      soConIdx = SoAd_GetSoConIdxOfNPduUdpTx(NPduIdx);
  SoAd_SizeOfSocketType     sockIdx = SoAd_GetSocketIdxOfSoCon(soConIdx);
  SoAd_SizeOfTxMgtType      txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(soConIdx);
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConIdx);
  SoAd_SizeOfSocketUdpType  socketUdpIdx = SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx);
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that another transmit interrupts this transmission. */
  SOAD_BEGIN_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Check if no transmission is active on socket. */
  if ( SoAd_GetSoConTxActiveIdxOfSocketDyn(sockIdx) == SoAd_GetSizeOfSoCon() )
  {
    /* #30 Check and set transmission state for this nPdu. */
    if ( SoAd_TxNPduUdp_QueueCheckAndSetTransmitState(NPduIdx) == E_OK )
    {
      /* #40 Set transmission active on socket. */
      SoAd_SetSoConTxActiveIdxOfSocketDyn(sockIdx, soConIdx);                                                          /* SBSW_SOAD_CSL03 */

      /* #50 Prepare transmission management struct for call to CopyTxData. */
      SoAd_SetPduRouteIdxOfTxMgt(txMgtIdx, 0u);                                                                        /* SBSW_SOAD_OPTIONAL_CSL03 */
      if ( SoAd_GetTotalLenOfNPduUdpTxDyn(NPduIdx) > SoAd_GetNPduUdpTxBufferMinOfSocketUdp(socketUdpIdx) )
      {
#if ( SOAD_TX_DYN_LEN == STD_ON )
        SoAd_SetTxBytesPendingOfTxMgt(txMgtIdx, SoAd_GetNPduUdpTxBufferMinOfSocketUdp(socketUdpIdx));                  /* SBSW_SOAD_OPTIONAL_CSL03 */
        SoAd_SetTxBytesLenOfTxMgt(txMgtIdx, SoAd_GetNPduUdpTxBufferMinOfSocketUdp(socketUdpIdx));                      /* SBSW_SOAD_OPTIONAL_CSL03 */
#else
        uint16 overflowNPduLength = SoAd_TxNPduUdp_QueueGetNPduLengthUpToOverflow(NPduIdx);

        SoAd_SetTxBytesPendingOfTxMgt(txMgtIdx, overflowNPduLength);                                                   /* SBSW_SOAD_OPTIONAL_CSL03 */
        SoAd_SetTxBytesLenOfTxMgt(txMgtIdx, overflowNPduLength);                                                       /* SBSW_SOAD_OPTIONAL_CSL03 */
#endif /* SOAD_TX_DYN_LEN == STD_ON */
      }
      else
      {
        SoAd_SetTxBytesPendingOfTxMgt(txMgtIdx, (PduLengthType)SoAd_GetTotalLenOfNPduUdpTxDyn(NPduIdx));               /* SBSW_SOAD_OPTIONAL_CSL03 */
        SoAd_SetTxBytesLenOfTxMgt(txMgtIdx, (PduLengthType)SoAd_GetTotalLenOfNPduUdpTxDyn(NPduIdx));                   /* SBSW_SOAD_OPTIONAL_CSL03 */
      }
      SoAd_SetTxBufPtrOfTxMgt(txMgtIdx, NULL_PTR);                                                                     /* SBSW_SOAD_OPTIONAL_CSL03 */

      retVal = E_OK;
    }
    /* #31 Flush nPdu if chek fails otherwise. */
    else
    {
      SoAd_TxNPduUdp_Clear(NPduIdx);
    }
  }
  /* #21 Set timeout to retry in main function otherwise. */
  else
  {
    (void)SoAd_TimeoutList_SetElement(SOAD_TIMEOUT_LIST_N_PDU, NPduIdx, 1u, SoAd_GlobalCounter);
  }

  /* #60 Leave critical section. */
  SOAD_END_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return retVal;
} /* SoAd_TxNPduUdp_QueuePrepareTransmitSegment() */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueCheckAndSetTransmitState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueueCheckAndSetTransmitState(
  SoAd_SizeOfNPduUdpTxType NPduIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if transmission of nPdu is set to active. */
  if ( SoAd_IsTransmissionActiveOfNPduUdpTxDyn(NPduIdx) == TRUE )
  {
    /* #20 Check if retry has failed. */
    if ( SoAd_TxNPduUdp_QueueCheckRetry(NPduIdx) == E_NOT_OK )
    {
      retVal = E_NOT_OK;
    }
  }
  /* #11 Set transmission to active otherwise. */
  else
  {
    SoAd_SetTransmissionActiveOfNPduUdpTxDyn(NPduIdx, TRUE);                                                           /* SBSW_SOAD_PARAMETER_IDX */
    SoAd_SetRetryCntOfNPduUdpTxDyn(NPduIdx, SOAD_N_PDU_UDP_TX_QUEUE_RETRY_CNT_MAIN);                                   /* SBSW_SOAD_PARAMETER_IDX */
  }

  return retVal;
} /* SoAd_TxNPduUdp_QueueCheckAndSetTransmitState() */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueCheckRetry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueueCheckRetry(
  SoAd_SizeOfNPduUdpTxType NPduIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if retry is running. */
  if ( SoAd_GetRetryCntOfNPduUdpTxDyn(NPduIdx) > 0u )
  {
    /* #20 Decrement retry counter. */
    SoAd_DecRetryCntOfNPduUdpTxDyn(NPduIdx);                                                                           /* SBSW_SOAD_PARAMETER_IDX */

    /* #30 Return that retry failed if retry counter is zero. */
    if ( SoAd_GetRetryCntOfNPduUdpTxDyn(NPduIdx) == 0u )
    {
      retVal = E_NOT_OK;
    }
  }

  return retVal;
} /* SoAd_TxNPduUdp_QueueCheckRetry() */

#if ( SOAD_TX_DYN_LEN == STD_OFF )
/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueGetNPduLengthUpToOverflow()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(uint16, SOAD_CODE) SoAd_TxNPduUdp_QueueGetNPduLengthUpToOverflow(
  SoAd_SizeOfNPduUdpTxType NPduIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_NPduUdpTxQueueIterType nPduUdpTxQueueIter;
  SoAd_SizeOfSoConType        soConIdx = SoAd_GetSoConIdxOfNPduUdpTx(NPduIdx);
  SoAd_SizeOfSoConGrpType     soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConIdx);
  SoAd_SizeOfSocketUdpType    socketUdpIdx = SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx);
  uint16                      nPduLengthUpToOverflow = 0U;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all queue elements to sum up all PDUs until overflow occurs. */
  for ( nPduUdpTxQueueIter = SoAd_GetNPduUdpTxQueueStartIdxOfNPduUdpTx(NPduIdx);
    nPduUdpTxQueueIter <
      (SoAd_NPduUdpTxQueueIterType) /* PRQA S 4391 */ /* MD_SoAd_GenericWiderTypeCast */
        (SoAd_GetNPduUdpTxQueueStartIdxOfNPduUdpTx(NPduIdx) + SoAd_GetLvlOfNPduUdpTxDyn(NPduIdx));
    nPduUdpTxQueueIter++ )
  {
    /* #20 Check if queue element exceeds the nPdu size. */
    if ( (nPduLengthUpToOverflow + SoAd_GetLenOfNPduUdpTxQueue(nPduUdpTxQueueIter)) >
      SoAd_GetNPduUdpTxBufferMinOfSocketUdp(socketUdpIdx) )
    {
      /* #30 Stop iterating to return the length up to this queue element. */
      break;
    }
    else
    {
      /* #40 Add queue element length to the total length of queue elements until overflow occurs. */
      nPduLengthUpToOverflow += SoAd_GetLenOfNPduUdpTxQueue(nPduUdpTxQueueIter);
    }
  }

  return nPduLengthUpToOverflow;
} /* SoAd_TxNPduUdp_QueueGetNPduLengthUpToOverflow() */
#endif /* SOAD_TX_DYN_LEN == STD_OFF */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueTransmitSegment()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueueTransmitSegment(
  SoAd_SizeOfNPduUdpTxType NPduIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx = SoAd_GetSoConIdxOfNPduUdpTx(NPduIdx);
  SoAd_SizeOfSocketType sockIdx = SoAd_GetSocketIdxOfSoCon(soConIdx);
  SoAd_SizeOfTxMgtType  txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(soConIdx);
  Std_ReturnType        retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Transmit nPdu and check if transmission succeeds. */
  /* PRQA S 310 5 */ /* MD_SoAd_11.4_struct */
  if ( SoAd_TcpIp_UdpTransmit(
    sockIdx,
    SoAd_GetSocketIdOfSocketDyn(sockIdx),
    SOAD_A_P2VAR(SoAd_SockAddrType)SoAd_GetAddrRemAddrDynOfSoConDyn(soConIdx),                                         /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    (uint16)SoAd_GetTxBytesPendingOfTxMgt(txMgtIdx)) == E_OK )
  {
    /* #20 Finish transmission of nPdu elements. */
    SoAd_TxNPduUdp_QueueFinishTransmitSegment(NPduIdx);

    /* #30 Reset transmission management struct. */
    SoAd_SetPduRouteIdxOfTxMgt(txMgtIdx, SoAd_GetSizeOfPduRoute());                                                    /* SBSW_SOAD_OPTIONAL_CSL03 */

    /* #40 Deactivate transmission on socket. */
    SoAd_SetSoConTxActiveIdxOfSocketDyn(sockIdx, SoAd_GetSizeOfSoCon());                                               /* SBSW_SOAD_CSL03 */

    /* #50 Finish transmission of nPdu if sent completely. */
    if ( SoAd_GetTotalLenOfNPduUdpTxDyn(NPduIdx) == 0u )
    {
      /* #500 Release queue. */
      SoAd_SetLvlOfNPduUdpTxDyn(NPduIdx, 0u);                                                                          /* SBSW_SOAD_PARAMETER_IDX */

      /* #501 Release buffer. */
      if ( SoAd_IsNPduUdpTxBufferUsedOfNPduUdpTx(NPduIdx) == TRUE )
      {
        SoAd_SetBufLenOfNPduUdpTxDyn(NPduIdx, 0u);                                                                     /* SBSW_SOAD_PARAMETER_IDX */
      }

      /* #502 Remove timeout from list. */
      SoAd_TimeoutList_RemoveElement(SOAD_TIMEOUT_LIST_N_PDU, NPduIdx);

      /* #503 Reset transmission state of nPdu. */
      SoAd_SetTransmissionActiveOfNPduUdpTxDyn(NPduIdx, FALSE);                                                        /* SBSW_SOAD_PARAMETER_IDX */
    }

    retVal = E_OK;
  }
  /* #11 Handle nPdu transmission if transmission failed. */
  else
  {
    /* #60 Reset transmission management struct. */
    SoAd_SetPduRouteIdxOfTxMgt(txMgtIdx, SoAd_GetSizeOfPduRoute());                                                    /* SBSW_SOAD_OPTIONAL_CSL03 */

    /* #70 Deactivate transmission on socket. */
    SoAd_SetSoConTxActiveIdxOfSocketDyn(sockIdx, SoAd_GetSizeOfSoCon());                                               /* SBSW_SOAD_CSL03 */

    /* #80 Set timeout to retry in main function. */
    (void)SoAd_TimeoutList_SetElement(SOAD_TIMEOUT_LIST_N_PDU, NPduIdx, 1u, SoAd_GlobalCounter);

    retVal = E_NOT_OK;
  }

  return retVal;
} /* SoAd_TxNPduUdp_QueueTransmitSegment() */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueFinishTransmitSegment()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxNPduUdp_QueueFinishTransmitSegment(
  SoAd_SizeOfNPduUdpTxType NPduIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_NPduUdpTxQueueIterType nPduUdpTxQueueIter;
  SoAd_SizeOfSoConType        soConIdx = SoAd_GetSoConIdxOfNPduUdpTx(NPduIdx);
  SoAd_SizeOfPduRouteType     pduRouteIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all queue elements. */
  for ( nPduUdpTxQueueIter = SoAd_GetNPduUdpTxQueueStartIdxOfNPduUdpTx(NPduIdx);
    nPduUdpTxQueueIter <
      (SoAd_NPduUdpTxQueueIterType)
        (SoAd_GetNPduUdpTxQueueStartIdxOfNPduUdpTx(NPduIdx) + SoAd_GetLvlOfNPduUdpTxDyn(NPduIdx));
    nPduUdpTxQueueIter++ )
  {
    pduRouteIdx = SoAd_GetPduRouteIdxOfNPduUdpTxQueue(nPduUdpTxQueueIter);

    /* #20 Check if element is not yet released. */
    if ( pduRouteIdx != SoAd_GetSizeOfPduRoute() )
    {
      /* #30 Check if element is copied and sent. */
      if ( SoAd_IsCopiedOfNPduUdpTxQueue(nPduUdpTxQueueIter) == TRUE )
      {
        /* #40 Call TxConfirmation if PDU is retrieved via trigger transmit. */
        if ( SoAd_IsIfTriggerTransmitEnabledOfPduRoute(pduRouteIdx) == TRUE )
        {
          SoAd_TxNPduUdp_QueueTxConfirmation(soConIdx, pduRouteIdx, TRUE);
        }

        /* #50 Release queue element. */
        SoAd_SetTotalLenOfNPduUdpTxDyn(NPduIdx,                                                                        /* SBSW_SOAD_PARAMETER_IDX */
          SoAd_GetTotalLenOfNPduUdpTxDyn(NPduIdx) - SoAd_GetLenOfNPduUdpTxQueue(nPduUdpTxQueueIter));
        SoAd_SetPduRouteIdxOfNPduUdpTxQueue(nPduUdpTxQueueIter, SoAd_GetSizeOfPduRoute());                             /* SBSW_SOAD_CALCULATED_CSL03 */
      }
      /* #31 Stop releasing elements otherwise. */
      else
      {
        break;
      }
    }
  }
} /* SoAd_TxNPduUdp_QueueFinishTransmitSegment() */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueTxConfirmation()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxNPduUdp_QueueTxConfirmation(
  SoAd_SizeOfSoConType SoConIdx,
  SoAd_SizeOfPduRouteType PduRouteIdx,
  boolean AllowReconnect)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if TxConfirmation is enabled for this PDU. */
  if ( SoAd_IsTxConfEnabledOfPduRoute(PduRouteIdx) == TRUE )
  {
    /* #20 Enter critical section to prevent that other confirmation interrupts and TxConfirmation is called twice. */
    SOAD_BEGIN_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #30 Check if a pending TxConfirmation is left. */
    if ( SoAd_GetPendingTxConfNumOfPduRouteDyn(PduRouteIdx) > 0u )
    {
      /* #40 Decrement pending confirmation counter. */
      SoAd_DecPendingTxConfNumOfPduRouteDyn(PduRouteIdx);                                                              /* SBSW_SOAD_PARAMETER_IDX */

      /* #50 Check if no confirmation is pending (i.e. transmission confirmed on all PduRouteDests). */
      if ( (SoAd_GetPendingTxConfNumOfPduRouteDyn(PduRouteIdx) == 0u) &&
        (SoAd_IsPendingTxConfMainOfPduRouteDyn(PduRouteIdx) == FALSE) )
      {
        /* #60 Check if socket connection reconnect is allowed. */
        if ( AllowReconnect == TRUE )
        {
          /* #600 Reconnect socket connection if socket connection has auto setup enabled and wildcards configured. */
          SoAd_SoCon_RequestReconnect(SoConIdx);
        }

        /* #70 Leave critical section to be able to call TxConfirmation of upper layer. */
        SOAD_END_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

        /* #80 Call TxConfirmation of upper layer. */
        SoAd_GetIfTxConfirmationCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfPduRoute(PduRouteIdx))(                         /* SBSW_SOAD_FUNCTION_PTR */
          SoAd_GetTxConfPduIdOfPduRoute(PduRouteIdx));
      }
      /* #51 Leave critical section otherwise. */
      else
      {
        SOAD_END_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
      }
    }
    /* #31 Leave critical section otherwise. */
    else
    {
      SOAD_END_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    }
  }
} /* SoAd_TxNPduUdp_QueueTxConfirmation() */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_BufferAddElement()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(SoAd_NPduReturnType, SOAD_CODE) SoAd_TxNPduUdp_BufferAddElement(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  PduLengthType             dataLen = PduInfoPtr->SduLength;
  SoAd_SizeOfSoConType      soConIdx = SoAd_GetSoConIdxOfPduRouteDest(PduRouteDestIdx);
  SoAd_SizeOfNPduUdpTxType  nPduIdx = SoAd_GetNPduUdpTxIdxOfSoCon(soConIdx);
  SoAd_SizeOfSoConGrpType   soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConIdx);
  SoAd_SizeOfSocketUdpType  socketUdpIdx = SoAd_GetSocketUdpIdxOfSoConGrp(soConGrpIdx);
  SoAd_NPduReturnType       nPduRetVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that another transmit interrupts this transmission. */
  SOAD_BEGIN_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Check if nPdu transmission is not active. */
  if ( SoAd_IsTransmissionActiveOfNPduUdpTxDyn(nPduIdx) == FALSE )
  {
    /* #30 Calculate PDU length considering PDU header. */
    if ( SoAd_IsPduHdrEnabledOfSoConGrp(soConGrpIdx) == TRUE )
    {
      dataLen += SOAD_PDU_HDR_SIZE;
    }

    /* #40 Check if nPdu size is not sufficient for new request. */
    if ( (SoAd_GetTotalLenOfNPduUdpTxDyn(nPduIdx) + dataLen) > SoAd_GetNPduUdpTxBufferMinOfSocketUdp(socketUdpIdx) )
    {
      nPduRetVal = SOAD_NPDU_OVFL_NEW;
    }
    /* #41 Check if timeout cannot be set if configured otherwise. */
    else if ( SoAd_TxNPduUdp_SetTriggerTimeout(nPduIdx, PduRouteDestIdx) == E_NOT_OK )
    {
      nPduRetVal = SOAD_NPDU_NOT_OK;
    }
    /* #42 Store PDU in nPdu buffer otherwise. */
    else
    {
      /* #420 Copy PDU header to nPdu buffer. */
      if ( SoAd_IsPduHdrEnabledOfSoConGrp(soConGrpIdx) == TRUE )
      {
        SoAd_Util_CopyPduHdr2Buf(                                                                                      /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
          SoAd_GetTxPduHdrIdOfPduRouteDest(PduRouteDestIdx),
          PduInfoPtr->SduLength,
          SoAd_GetAddrNPduUdpTxBuffer(
            SoAd_GetNPduUdpTxBufferStartIdxOfNPduUdpTx(nPduIdx) + SoAd_GetBufLenOfNPduUdpTxDyn(nPduIdx)),
          0u,
          SOAD_PDU_HDR_SIZE);
        SoAd_SetBufLenOfNPduUdpTxDyn(nPduIdx, SoAd_GetBufLenOfNPduUdpTxDyn(nPduIdx) + SOAD_PDU_HDR_SIZE);              /* SBSW_SOAD_OPTIONAL_CSL03 */
        SoAd_SetTotalLenOfNPduUdpTxDyn(nPduIdx, SoAd_GetTotalLenOfNPduUdpTxDyn(nPduIdx) + SOAD_PDU_HDR_SIZE);          /* SBSW_SOAD_OPTIONAL_CSL03 */
      }

      /* #421 Copy PDU data to nPdu buffer. */
      IpBase_Copy(                                                                                                     /* SBSW_SOAD_OPTIONAL_CSL03_POINTER_FORWARD */
        SOAD_A_P2VAR(IpBase_CopyDataType)SoAd_GetAddrNPduUdpTxBuffer(
          SoAd_GetNPduUdpTxBufferStartIdxOfNPduUdpTx(nPduIdx) + SoAd_GetBufLenOfNPduUdpTxDyn(nPduIdx)),
        SOAD_A_P2VAR(IpBase_CopyDataType)&PduInfoPtr->SduDataPtr[0],
        PduInfoPtr->SduLength);
      SoAd_SetBufLenOfNPduUdpTxDyn(nPduIdx, SoAd_GetBufLenOfNPduUdpTxDyn(nPduIdx) + PduInfoPtr->SduLength);            /* SBSW_SOAD_OPTIONAL_CSL03 */
      SoAd_SetTotalLenOfNPduUdpTxDyn(nPduIdx, SoAd_GetTotalLenOfNPduUdpTxDyn(nPduIdx) + PduInfoPtr->SduLength);        /* SBSW_SOAD_OPTIONAL_CSL03 */

      /* #422 Indicate that a TxConfirmation is pending for the copied PDU. */
      SoAd_TxIf_AddPendingConf(PduRouteIdx, soConIdx);

      nPduRetVal = SOAD_NPDU_OK;
    }
  }
  else
  {
    nPduRetVal = SOAD_NPDU_NOT_OK;
  }

  /* #70 Leave critical section. */
  SOAD_END_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return nPduRetVal;
} /* SoAd_TxNPduUdp_BufferAddElement() */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_BufferSend()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxNPduUdp_BufferSend(
  SoAd_SizeOfNPduUdpTxType NPduIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfPduRouteDestBySoConIndType pduRouteDestBySoConIndStartIdx;
  SoAd_SizeOfPduRouteType               pduRouteIdx;
  SoAd_SizeOfSoConType                  soConIdx = SoAd_GetSoConIdxOfNPduUdpTx(NPduIdx);
  SoAd_SizeOfSocketType                 sockIdx = SoAd_GetSocketIdxOfSoCon(soConIdx);
  SoAd_SizeOfTxMgtType                  txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(soConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that another transmit interrupts this transmission. */
  SOAD_BEGIN_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Check if no transmission is active on socket. */
  if ( SoAd_GetSoConTxActiveIdxOfSocketDyn(sockIdx) == SoAd_GetSizeOfSoCon() )
  {
    /* Use first PDU route of socket connection as dummy identifier (used to identify API type in CopyTxData). */
    pduRouteDestBySoConIndStartIdx = SoAd_GetPduRouteDestBySoConIndStartIdxOfSoCon(soConIdx);
    pduRouteIdx = SoAd_GetPduRouteIdxOfPduRouteDest(SoAd_GetPduRouteDestBySoConInd(pduRouteDestBySoConIndStartIdx));

    /* #30 Set transmission active of nPdu. */
    SoAd_SetTransmissionActiveOfNPduUdpTxDyn(NPduIdx, TRUE);                                                           /* SBSW_SOAD_PARAMETER_IDX */

    /* #40 Set transmission active on socket. */
    SoAd_SetSoConTxActiveIdxOfSocketDyn(sockIdx, soConIdx);                                                            /* SBSW_SOAD_CSL03 */

    /* #50 Prepare transmission. */
    SoAd_SetPduRouteIdxOfTxMgt(txMgtIdx, pduRouteIdx);                                                                 /* SBSW_SOAD_OPTIONAL_CSL03 */
    SoAd_SetTxBytesPendingOfTxMgt(txMgtIdx, (PduLengthType)SoAd_GetTotalLenOfNPduUdpTxDyn(NPduIdx) );                  /* SBSW_SOAD_OPTIONAL_CSL03 */
    SoAd_SetTxBytesLenOfTxMgt(txMgtIdx, (PduLengthType)SoAd_GetTotalLenOfNPduUdpTxDyn(NPduIdx));                       /* SBSW_SOAD_OPTIONAL_CSL03 */
    SoAd_SetTxBufPtrOfTxMgt(txMgtIdx, NULL_PTR);                                                                       /* SBSW_SOAD_OPTIONAL_CSL03 */

    /* #60 Leave critical section. */
    SOAD_END_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #70 Try to send nPdu. */
    /* PRQA S 310 5 */ /* MD_SoAd_11.4_struct */
    (void)SoAd_TcpIp_UdpTransmit(                                                                                      /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
      sockIdx,
      SoAd_GetSocketIdOfSocketDyn(sockIdx),
      SOAD_A_P2VAR(SoAd_SockAddrType)SoAd_GetAddrRemAddrDynOfSoConDyn(soConIdx),
      (uint16)SoAd_GetTotalLenOfNPduUdpTxDyn(NPduIdx));

    /* #80 Remove timeout from list. */
    SoAd_TimeoutList_RemoveElement(SOAD_TIMEOUT_LIST_N_PDU, NPduIdx);

    /* #90 Finish nPdu transmission independent of transmission result since there is no retransmission specified. */
    SoAd_SetBufLenOfNPduUdpTxDyn(NPduIdx, 0u);                                                                         /* SBSW_SOAD_PARAMETER_IDX */
    SoAd_SetTotalLenOfNPduUdpTxDyn(NPduIdx, 0u);                                                                       /* SBSW_SOAD_PARAMETER_IDX */
    SoAd_SetTransmissionActiveOfNPduUdpTxDyn(NPduIdx, FALSE);                                                          /* SBSW_SOAD_PARAMETER_IDX */

    /* #100 Reset transmission management struct. */
    SoAd_SetPduRouteIdxOfTxMgt(txMgtIdx, SoAd_GetSizeOfPduRoute());                                                    /* SBSW_SOAD_OPTIONAL_CSL03 */

    /* #110 Deactivate transmission on socket. */
    SoAd_SetSoConTxActiveIdxOfSocketDyn(sockIdx, SoAd_GetSizeOfSoCon());                                               /* SBSW_SOAD_CSL03 */
  }
  /* #21 Skip transmission in this context. */
  else
  {
    /* #210 Leave critical section. */
    SOAD_END_CRITICAL_SECTION(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
} /* SoAd_TxNPduUdp_BufferSend() */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_CopyTxData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_TxNPduUdp_CopyTxData(
  SoAd_SizeOfSoConType SoConIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) BufLengthPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfNPduUdpTxType  nPduIdx = SoAd_GetNPduUdpTxIdxOfSoCon(SoConIdx);
  BufReq_ReturnType         retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle CopyTxData in case nPdu queue is used. */
  if ( SoAd_IsNPduUdpTxQueueUsedOfNPduUdpTx(nPduIdx) == TRUE )
  {
    retVal = SoAd_TxNPduUdp_QueueCopyTxData(nPduIdx, BufPtr, BufLengthPtr);                                            /* SBSW_SOAD_POINTER_FORWARD */
  }
  /* #11 Handle CopyTxData for nPdu buffer otherwise. */
  else
  {
    SoAd_TxNPduUdp_BufferCopyTxData(nPduIdx, BufPtr, *BufLengthPtr);                                                   /* SBSW_SOAD_POINTER_FORWARD */

    retVal = BUFREQ_OK;
  }

  return retVal;
} /* SoAd_TxNPduUdp_CopyTxData() */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueCopyTxData()
 *********************************************************************************************************************/
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
SOAD_LOCAL_INLINE FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueueCopyTxData(
  SoAd_SizeOfNPduUdpTxType NPduIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) BufLengthPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_NPduUdpTxQueueIterType nPduUdpTxQueueIter;
  SoAd_SizeOfPduRouteType     pduRouteIdx;
  SoAd_SizeOfSoConType        soConIdx = SoAd_GetSoConIdxOfNPduUdpTx(NPduIdx);
  SoAd_SizeOfTxMgtType        txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(soConIdx);
  uint16                      bufLength = *BufLengthPtr;
  uint16                      bufIdx = 0u;
  BufReq_ReturnType           retVal = BUFREQ_E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all elements in nPdu queue. */
  for ( nPduUdpTxQueueIter = SoAd_GetNPduUdpTxQueueStartIdxOfNPduUdpTx(NPduIdx);
    nPduUdpTxQueueIter <
      (SoAd_NPduUdpTxQueueIterType)
        (SoAd_GetNPduUdpTxQueueStartIdxOfNPduUdpTx(NPduIdx) + SoAd_GetLvlOfNPduUdpTxDyn(NPduIdx));
    nPduUdpTxQueueIter++ )
  {
    pduRouteIdx = SoAd_GetPduRouteIdxOfNPduUdpTxQueue(nPduUdpTxQueueIter);

    /* #20 Check if nPdu element is pending. */
    if ( pduRouteIdx != SoAd_GetSizeOfPduRoute() )
    {
      /* #30 Copy element if PDU is located in buffer. */
      if ( SoAd_IsIfTriggerTransmitEnabledOfPduRoute(pduRouteIdx) == FALSE )
      {
        retVal = SoAd_TxNPduUdp_QueueCopyTxDataBuffer((SoAd_SizeOfNPduUdpTxQueueType)nPduUdpTxQueueIter,               /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
          &BufPtr[bufIdx], &bufLength);
      }
      else
      /* #31 Copy element via trigger transmit otherwise. */
      {
        retVal = SoAd_TxNPduUdp_QueueCopyTxDataTrigger(NPduIdx, (SoAd_SizeOfNPduUdpTxQueueType)nPduUdpTxQueueIter,     /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
          &BufPtr[bufIdx], &bufLength);
      }

      /* #40 Indicate that element is finished if it is successfully copied to provided buffer. */
      if ( retVal == BUFREQ_OK )
      {
        bufIdx = *BufLengthPtr - bufLength;
        SoAd_SetCopiedOfNPduUdpTxQueue(nPduUdpTxQueueIter, TRUE);                                                      /* SBSW_SOAD_CALCULATED_CSL03 */
      }
      /* #41 Stop iteration otherwise. */
      else
      {
        /* #410 Return without error if buffer size of provided buffer is not sufficient and an element is copied. */
        if ( (retVal == BUFREQ_E_OVFL) && (bufLength < *BufLengthPtr) )
        {
          retVal = BUFREQ_OK;
        }
        break;
      }
    }
  }

  /* #50 Return length of data copied effectively. */
  *BufLengthPtr = bufIdx;                                                                                              /* SBSW_SOAD_POINTER_WRITE */
  SoAd_SetTxBytesLenOfTxMgt(txMgtIdx, SoAd_GetTxBytesLenOfTxMgt(txMgtIdx) - bufIdx);                                   /* SBSW_SOAD_OPTIONAL_CSL03 */

  return retVal;
} /* SoAd_TxNPduUdp_QueueCopyTxData() */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueCopyTxDataBuffer()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueueCopyTxDataBuffer(
  SoAd_SizeOfNPduUdpTxQueueType NPduQueueIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) BufLengthPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType retVal = BUFREQ_E_OVFL;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if provided buffer is sufficient to copy PDU. */
  if ( *BufLengthPtr >= SoAd_GetLenOfNPduUdpTxQueue(NPduQueueIdx) )
  {
    /* #20 Copy PDU to provided buffer. */
    IpBase_Copy(                                                                                                       /* SBSW_SOAD_POINTER_AND_OPTIONAL_CSL03_POINTER_FORWARD */
      SOAD_V_P2VAR(IpBase_CopyDataType)&BufPtr[0],
      SOAD_V_P2CONST(IpBase_CopyDataType)SoAd_GetAddrNPduUdpTxBuffer(
        SoAd_GetNPduUdpTxBufferIdxOfNPduUdpTxQueue(NPduQueueIdx)),
      SoAd_GetLenOfNPduUdpTxQueue(NPduQueueIdx));

    /* #30 Indicate that PDU is copied completely. */
    *BufLengthPtr -= (uint16)SoAd_GetLenOfNPduUdpTxQueue(NPduQueueIdx);                                                /* SBSW_SOAD_POINTER_WRITE */

    retVal = BUFREQ_OK;
  }

  return retVal;
} /* SoAd_TxNPduUdp_QueueCopyTxDataBuffer() */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueCopyTxDataTrigger()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueueCopyTxDataTrigger(
  SoAd_SizeOfNPduUdpTxType NPduIdx,
  SoAd_SizeOfNPduUdpTxQueueType NPduQueueIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) BufLengthPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  PduInfoType             pduInfo;
  SoAd_SizeOfSoConType    soConIdx = SoAd_GetSoConIdxOfNPduUdpTx(NPduIdx);
  SoAd_SizeOfSoConGrpType soConGrpIdx = SoAd_GetSoConGrpIdxOfSoCon(soConIdx);
  BufReq_ReturnType       retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare buffer to copy data via trigger transmit. */
  retVal = SoAd_TxNPduUdp_QueueCopyTxDataTriggerPrepare(NPduIdx, BufPtr, *BufLengthPtr, &pduInfo);                     /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */

  /* #20 Check if buffer is prepared. */
  if ( retVal == BUFREQ_OK )
  {
    /* #30 Check if PDU contains data in case PDU header is used. */
    if ( (SoAd_IsPduHdrEnabledOfSoConGrp(soConGrpIdx) == FALSE) ||
      ((SoAd_GetLenOfNPduUdpTxQueue(NPduQueueIdx) - SOAD_PDU_HDR_SIZE) != 0u) )
    {
      /* #40 Call trigger transmit to copy data to provided buffer. */
      retVal = SoAd_TxNPduUdp_QueueCopyTxDataTriggerCall(NPduIdx, NPduQueueIdx, BufLengthPtr, &pduInfo);               /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
    }

    /* #50 Add PDU header considering length returned by trigger transmit call. */
    if ( (retVal == BUFREQ_OK) && (SoAd_IsPduHdrEnabledOfSoConGrp(soConGrpIdx) == TRUE) )
    {
      SoAd_TxNPduUdp_QueueCopyTxDataTriggerAddPduHeader(NPduIdx, NPduQueueIdx, BufPtr, BufLengthPtr, &pduInfo);        /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
    }
  }

  return retVal;
} /* SoAd_TxNPduUdp_QueueCopyTxDataTrigger() */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueCopyTxDataTriggerPrepare()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueueCopyTxDataTriggerPrepare(
  SoAd_SizeOfNPduUdpTxType NPduIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 BufLength,
  P2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx = SoAd_GetSoConIdxOfNPduUdpTx(NPduIdx);
  BufReq_ReturnType     retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Prepare buffer considering PDU header offset. */
  if ( SoAd_IsPduHdrEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx)) == TRUE )
  {
    /* #100 Prepare buffer if provided buffer size is sufficient to store the PDU. */
    if ( BufLength >= SOAD_PDU_HDR_SIZE )
    {
      PduInfoPtr->SduDataPtr = &BufPtr[SOAD_PDU_HDR_SIZE];                                                             /* SBSW_SOAD_POINTER_WRITE */
      PduInfoPtr->SduLength = (PduLengthType)(BufLength - SOAD_PDU_HDR_SIZE);                                          /* SBSW_SOAD_POINTER_WRITE */

      retVal = BUFREQ_OK;
    }
    /* #101 Indicate an overflow otherwise. */
    else
    {
      retVal = BUFREQ_E_OVFL;
    }
  }
  /* #11 Prepare buffer to copy data without offset otherwise. */
  else
  {
    PduInfoPtr->SduDataPtr = BufPtr;                                                                                   /* SBSW_SOAD_POINTER_WRITE */
    PduInfoPtr->SduLength = (PduLengthType)BufLength;                                                                  /* SBSW_SOAD_POINTER_WRITE */

    retVal = BUFREQ_OK;
  }

  return retVal;
} /* SoAd_TxNPduUdp_QueueCopyTxDataTriggerPrepare() */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueCopyTxDataTriggerCall()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_TxNPduUdp_QueueCopyTxDataTriggerCall(
  SoAd_SizeOfNPduUdpTxType NPduIdx,
  SoAd_SizeOfNPduUdpTxQueueType NPduQueueIdx,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) BufLengthPtr,
  P2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfPduRouteType pduRouteIdx = SoAd_GetPduRouteIdxOfNPduUdpTxQueue(NPduQueueIdx);
  SoAd_SizeOfSoConType    soConIdx = SoAd_GetSoConIdxOfNPduUdpTx(NPduIdx);
  PduLengthType           expectedLen;
  BufReq_ReturnType       retVal = BUFREQ_E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call trigger transmit to copy PDU to provided buffer. */
  if ( SoAd_GetIfTriggerTransmitCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfPduRoute(pduRouteIdx))(                         /* SBSW_SOAD_FUNCTION_PTR */
    SoAd_GetTxConfPduIdOfPduRoute(pduRouteIdx), PduInfoPtr) == E_OK )
  {
#if ( SOAD_TX_DYN_LEN == STD_ON )
    /* #20 Check if copied length is valid (if CopyTxData with dynamic length is enabled). */
    if ( SoAd_IsPduHdrEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx)) == TRUE )
    {
      expectedLen = (PduLengthType)(*BufLengthPtr - SOAD_PDU_HDR_SIZE);
    }
    else
    {
      expectedLen = (PduLengthType)(*BufLengthPtr);
    }

    if ( PduInfoPtr->SduLength <= expectedLen )
    {
      retVal = BUFREQ_OK;
    }
#else
    /* #21 Check if copied length is valid (if CopyTxData with dynamic length is disabled). */
    if ( SoAd_IsPduHdrEnabledOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx)) == TRUE )
    {
      expectedLen = (PduLengthType)(SoAd_GetLenOfNPduUdpTxQueue(NPduQueueIdx) - SOAD_PDU_HDR_SIZE);
    }
    else
    {
      expectedLen = (PduLengthType)(SoAd_GetLenOfNPduUdpTxQueue(NPduQueueIdx));
    }

    if ( PduInfoPtr->SduLength == expectedLen )
    {
      retVal = BUFREQ_OK;
    }
#endif /* SOAD_TX_DYN_LEN == STD_OFF */

    /* #30 Decrement available buffer length of provided buffer by copied length if valid. */
    if ( retVal == BUFREQ_OK )
    {
      *BufLengthPtr -= (uint16)PduInfoPtr->SduLength;                                                                  /* SBSW_SOAD_POINTER_WRITE */
    }
  }
  else
  {
    retVal = BUFREQ_E_OVFL;
  }

  return retVal;
} /* SoAd_TxNPduUdp_QueueCopyTxDataTriggerCall() */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_QueueCopyTxDataTriggerAddPduHeader()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxNPduUdp_QueueCopyTxDataTriggerAddPduHeader(
  SoAd_SizeOfNPduUdpTxType NPduIdx,
  SoAd_SizeOfNPduUdpTxQueueType NPduQueueIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) BufLengthPtr,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_PduRouteDestIterType pduRouteDestIter;
  SoAd_SizeOfPduRouteType   pduRouteIdx = SoAd_GetPduRouteIdxOfNPduUdpTxQueue(NPduQueueIdx);
  SoAd_SizeOfSoConType      soConIdx = SoAd_GetSoConIdxOfNPduUdpTx(NPduIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all PduRouteDests of PduRoute to find the corresponding PduRouteDest. */
  for ( pduRouteDestIter = SoAd_GetPduRouteDestStartIdxOfPduRoute(pduRouteIdx);
    pduRouteDestIter < SoAd_GetPduRouteDestEndIdxOfPduRoute(pduRouteIdx);
    pduRouteDestIter++ )
  {
    /* #20 Check if current PduRouteDest is the corresponding PduRouteDest. */
    if ( SoAd_GetSoConIdxOfPduRouteDest(pduRouteDestIter) == soConIdx )
    {
      /* #30 Copy PDU header of PduRouteDest to provided buffer. */
      SoAd_Util_CopyPduHdr2Buf(                                                                                        /* SBSW_SOAD_POINTER_FORWARD */
        SoAd_GetTxPduHdrIdOfPduRouteDest(pduRouteDestIter),
        PduInfoPtr->SduLength,
        BufPtr,
        0u,
        SOAD_PDU_HDR_SIZE);

      /* #40 Decrement available buffer length of provided buffer by length of PDU header. */
      *BufLengthPtr -= SOAD_PDU_HDR_SIZE;                                                                              /* SBSW_SOAD_POINTER_WRITE */

      break;
    }
  }
} /* SoAd_TxNPduUdp_QueueCopyTxDataTriggerAddPduHeader() */

/**********************************************************************************************************************
 *  SoAd_TxNPduUdp_BufferCopyTxData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_TxNPduUdp_BufferCopyTxData(
  SoAd_SizeOfNPduUdpTxType NPduIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 BufLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  SOAD_P2VAR(uint8)     txBufPtr = SoAd_GetAddrNPduUdpTxBuffer(SoAd_GetNPduUdpTxBufferStartIdxOfNPduUdpTx(NPduIdx));
  PduLengthType         bytesCopied;
  SoAd_SizeOfTxMgtType  txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(SoAd_GetSoConIdxOfNPduUdpTx(NPduIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate data length which is already copied to lower layer. */
  bytesCopied = (PduLengthType)(SoAd_GetTxBytesLenOfTxMgt(txMgtIdx) - SoAd_GetTxBytesPendingOfTxMgt(txMgtIdx));

  /* #20 Copy nPdu buffer to provided buffer. */
  IpBase_Copy(                                                                                                         /* SBSW_SOAD_POINTER_AND_OPTIONAL_CSL03_POINTER_FORWARD */
    SOAD_V_P2VAR(IpBase_CopyDataType)&BufPtr[0u],
    SOAD_V_P2CONST(IpBase_CopyDataType)&txBufPtr[bytesCopied],
    BufLength);

  /* #30 Decrement pending data length. */
  SoAd_SetTxBytesPendingOfTxMgt(txMgtIdx, (PduLengthType)(SoAd_GetTxBytesPendingOfTxMgt(txMgtIdx) - BufLength));       /* SBSW_SOAD_OPTIONAL_CSL03 */
} /* SoAd_TxNPduUdp_BufferCopyTxData() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

 /*********************************************************************************************************************
 *  SoAd_Tx_Init()
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_Tx_Init(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_PduRouteIterType   pduRouteIter;
  SoAd_NPduUdpTxIterType  nPduUdpTxIter;

  /* ----- Implementation ----------------------------------------------- */
  /*  #10 Iterate over all PduRoutes. */
  for ( pduRouteIter = 0u; pduRouteIter < SoAd_GetSizeOfPduRoute(); pduRouteIter++ )
  {
    /* #100 Initialize PduRoute structs. */
    SoAd_SetPendingTxConfMainOfPduRouteDyn(pduRouteIter, 0u);                                                          /* SBSW_SOAD_CSL02 */
    SoAd_SetPendingTxConfNumOfPduRouteDyn(pduRouteIter, FALSE);                                                        /* SBSW_SOAD_CSL02 */
  }

  /* #20 Iterate over all nPdus. */
  for ( nPduUdpTxIter = 0u; nPduUdpTxIter < SoAd_GetSizeOfNPduUdpTx(); nPduUdpTxIter++ )
  {
    /* #200 Initialize nPdu structs. */
    SoAd_TxNPduUdp_Clear((SoAd_SizeOfNPduUdpTxType)nPduUdpTxIter);
  }
} /* SoAd_Tx_Init() */

 /*********************************************************************************************************************
 *  SoAd_Tx_InitSoCon()
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_Tx_InitSoCon(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfTxMgtType  txMgtIdx = SoAd_GetTxMgtIdxOfSoCon(SoConIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize tx struct elements. */
  if ( SoAd_IsTxMgtUsedOfSoCon(SoConIdx) == TRUE )
  {
    SoAd_SetPduRouteIdxOfTxMgt(txMgtIdx, SoAd_GetSizeOfPduRoute());                                                    /* SBSW_SOAD_OPTIONAL_CSL03 */
    SoAd_SetTxBytesPendingOfTxMgt(txMgtIdx, 0u);                                                                       /* SBSW_SOAD_OPTIONAL_CSL03 */
    SoAd_SetTxBytesLenOfTxMgt(txMgtIdx, 0u);                                                                           /* SBSW_SOAD_OPTIONAL_CSL03 */
    SoAd_SetTxBufPtrOfTxMgt(txMgtIdx, NULL_PTR);                                                                       /* SBSW_SOAD_OPTIONAL_CSL03 */
    SoAd_SetCancelRequestedOfTxMgt(txMgtIdx, FALSE);                                                                   /* SBSW_SOAD_OPTIONAL_CSL03 */
  }

  /* #20 Initialize tx buffer. */
  if ( SoAd_IsTpTxBufferConfigUsedOfSoCon(SoConIdx) == TRUE )
  {
    SoAd_SizeOfTpTxBufferConfigType tpTxBufferConfigIdx = SoAd_GetTpTxBufferConfigIdxOfSoCon(SoConIdx);

    SoAd_SetTpTxBufferIdxOfTpTxBufferConfigDyn(tpTxBufferConfigIdx,                                                    /* SBSW_SOAD_OPTIONAL_CSL03 */
      SoAd_GetTpTxBufferStartIdxOfTpTxBufferConfig(tpTxBufferConfigIdx));
  }

#if ( SOAD_TCP == STD_ON )
  /* #30 Initialize Tx TCP queue (if enabled). */
  SoAd_TxTcpQueue_Init(SoConIdx);
#endif /* SOAD_TCP == STD_ON */
} /* SoAd_Tx_InitSoCon() */

/**********************************************************************************************************************
 *  SoAd_Tx_IfTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_Tx_IfTransmit(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) PduInfoPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check parameters for transmission. */
  if ( SoAd_TxIf_CheckParameter(PduRouteIdx, PduInfoPtr->SduLength) == E_OK )
  {
    /* #20 Trigger transmission of PDU. */
    retVal = SoAd_TxIf_TransmitPdu(PduRouteIdx, PduInfoPtr, ErrorIdPtr);                                               /* SBSW_SOAD_POINTER_FORWARD */
  }

  return retVal;
} /* SoAd_Tx_IfTransmit() */

/**********************************************************************************************************************
 *  SoAd_Tx_IfTransmitPduRouteDest()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_Tx_IfTransmitPduRouteDest(
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Forward transmission request to sub-component. */
  return SoAd_TxIf_TransmitPduRouteDest(PduRouteDestIdx, PduInfoPtr, ErrorIdPtr);                                      /* SBSW_SOAD_POINTER_FORWARD */
} /* SoAd_Tx_IfTransmitPduRouteDest() */

/**********************************************************************************************************************
 *  SoAd_Tx_TpTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_Tx_TpTransmit(
  SoAd_SizeOfPduRouteType PduRouteIdx,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check parameters for transmission. */
  if ( SoAd_TxTp_CheckParameter(PduRouteIdx, PduInfoPtr->SduLength) == E_OK )
  {
    /* #20 Try to store transmission request. */
    if ( SoAd_TxTp_TransmitPdu(PduRouteIdx, PduInfoPtr) == E_OK )                                                      /* SBSW_SOAD_POINTER_FORWARD */
    {
      retVal = E_OK;
    }
  }

  return retVal;
} /* SoAd_Tx_TpTransmit() */

/**********************************************************************************************************************
 *  SoAd_Tx_TpCancelTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_Tx_TpCancelTransmit(
  SoAd_SizeOfPduRouteType PduRouteIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Forward transmission cancellation request to sub-component.*/
  return SoAd_TxTp_CancelTransmit(PduRouteIdx);
} /* SoAd_Tx_TpCancelTransmit() */

/**********************************************************************************************************************
 *  SoAd_Tx_CopyTxData()
 *********************************************************************************************************************/
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
FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_Tx_CopyTxData(
  SoAd_SizeOfSocketType SockIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) BufLengthPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType    soConIdx = SoAd_GetSoConTxActiveIdxOfSocketDyn(SockIdx);
  SoAd_SizeOfPduRouteType pduRouteIdx;
  BufReq_ReturnType       retVal = BUFREQ_E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if parameters are valid. */
  if ( SoAd_Tx_CopyTxDataCheckParameter(soConIdx, *BufLengthPtr) == E_OK )
  {
    pduRouteIdx = SoAd_GetPduRouteIdxOfTxMgt(SoAd_GetTxMgtIdxOfSoCon(soConIdx));

    /* #20 Handle transmission for IF-API. */
    if ( SoAd_GetUpperLayerApiOfPduRoute(pduRouteIdx) == SOAD_UL_API_IF )
    {
#if ( SOAD_TCP == STD_ON )
      /* #200 Handle transmission for IF-API on TCP socket (if enabled). */
      if ( SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx)) == TRUE )
      {
        SoAd_TxIf_TcpCopyTxData(soConIdx, BufPtr, *BufLengthPtr);                                                      /* SBSW_SOAD_POINTER_FORWARD */
        retVal = BUFREQ_OK;
      }
      else
#endif /* SOAD_TCP == STD_ON */
      /* #201 Handle transmission for IF-API on UDP socket. */
      {
        retVal = SoAd_TxIf_UdpCopyTxData(soConIdx, BufPtr, BufLengthPtr);                                              /* SBSW_SOAD_POINTER_FORWARD */
      }
    }
    /* #21 Handle transmission for TP-API otherwise. */
    else
    {
#if ( SOAD_TCP == STD_ON )
      /* #210 Handle transmission for TP-API on TCP socket (if enabled). */
      if ( SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx)) == TRUE )
      {
        retVal = SoAd_TxTp_TcpCopyTxData(soConIdx, pduRouteIdx, BufPtr, *BufLengthPtr);                                /* SBSW_SOAD_POINTER_FORWARD */
      }
      else
#endif /* SOAD_TCP == STD_ON */
      /* #211 Handle transmission for TP-API on UDP socket. */
      {
        SoAd_TxTp_UdpCopyTxData(soConIdx, BufPtr, *BufLengthPtr);                                                      /* SBSW_SOAD_POINTER_FORWARD */
        retVal = BUFREQ_OK;
      }
    }
  }

  return retVal;
} /* SoAd_Tx_CopyTxData() */

#if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR )
# if ( SOAD_TCP == STD_ON )
/**********************************************************************************************************************
  SoAd_Tx_TcpGetUnconfirmedDataLength()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(uint32, SOAD_CODE) SoAd_Tx_TcpGetUnconfirmedDataLength(
  SoAd_SizeOfSocketType SockIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Return total length of TcpQueue to return length of data not yet confirmed. */
  return SoAd_TxTcpQueue_GetTotalLength(SoAd_GetSoConStartIdxOfSocket(SockIdx));
}
# endif /* SOAD_TCP == STD_ON */
#endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */

/**********************************************************************************************************************
 *  SoAd_Tx_TxConfirmation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* PRQA S 3206 3 */ /* MD_SoAd_3206 */
FUNC(void, SOAD_CODE) SoAd_Tx_TxConfirmation(
  SoAd_SizeOfSocketType SockIdx,
  uint16 Length)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType soConIdx = SoAd_GetSoConStartIdxOfSocket(SockIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check socket connection specific parameter. */
  if ( SoAd_Tx_CheckSoConStates(soConIdx) == E_OK )
  {
#if ( SOAD_TCP == STD_ON )
    /* #20 Handle TxConfirmation for TCP socket connection (if eanbled). */
    if ( SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(soConIdx)) == TRUE )
    {
      SoAd_TxTcpQueue_TxConfirmation(soConIdx, (PduLengthType)Length);
    }
    else
#else
  SOAD_DUMMY_STATEMENT_VAR(Length); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */
#endif /* SOAD_TCP == STD_ON */
    /* #21 Handle TxConfirmation for UDP socket connection with immediate TxConfirmation otherwise. */
    {
      SoAd_Tx_UdpImmediateIfTxConfirmation(soConIdx);
    }
  }
} /* SoAd_Tx_TxConfirmation() */

/**********************************************************************************************************************
 *  SoAd_Tx_TerminateTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_Tx_TerminateTransmit(
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Terminate active TP session. */
  SoAd_TxTp_TerminateTransmit(SoConIdx);

#if ( SOAD_TCP == STD_ON )
  /* #20 Reinitialize Tx Tcp queue (if enabled). */
  SoAd_TxTcpQueue_Clear(SoConIdx);
#endif /* SOAD_VTCP_USED == STD_ON */

  /* #30 Clear nPdu. */
  if ( SoAd_IsNPduUdpTxUsedOfSoCon(SoConIdx) == TRUE )
  {
    SoAd_TxNPduUdp_Clear(SoAd_GetNPduUdpTxIdxOfSoCon(SoConIdx));
  }
} /* SoAd_Tx_TerminateTransmit() */

/**********************************************************************************************************************
 *  SoAd_Tx_HandleTransmission()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_Tx_HandleTransmission(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle TP transmission. */
  SoAd_TxTp_HandleTransmission();

  /* #20 Handle nPdu transmission. */
  if ( SoAd_HasNPduUdpTx() )
  {
    SoAd_TxNPduUdp_HandleTransmission();
  }
} /* SoAd_Tx_HandleTransmission() */

/**********************************************************************************************************************
 *  SoAd_Tx_HandleConfirmation()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_Tx_HandleConfirmation(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle pending UDP IfTxConfirmations. */
  SoAd_TxIf_UdpHandleTxConfirmation();
} /* SoAd_Tx_HandleConfirmation() */

#define SOAD_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */ /*lint !e451 */

/* Justification for module-specific MISRA deviations:
 * see file SoAd.c
 */

/**********************************************************************************************************************
 *  END OF FILE: SoAd_Tx.c
 *********************************************************************************************************************/
