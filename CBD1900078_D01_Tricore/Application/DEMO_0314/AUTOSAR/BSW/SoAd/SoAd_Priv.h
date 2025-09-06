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
/**        \file  SoAd_Priv.h
 *        \brief  Socket Adaptor private header file
 *
 *      \details  Vector static private header file for AUTOSAR Socket Adaptor module. This header file contains
 *                module internal declarations.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined(SOAD_PRIV_H)
# define SOAD_PRIV_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "SoAd_Types.h"
# include "SoAd_Lcfg.h"
# include "SchM_SoAd.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

# define SOAD_BEGIN_CRITICAL_SECTION()      SchM_Enter_SoAd_SOAD_EXCLUSIVE_AREA_0()
# define SOAD_END_CRITICAL_SECTION()        SchM_Exit_SoAd_SOAD_EXCLUSIVE_AREA_0()

# if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR )
#  if ( SOAD_SOCKET_REPORT_ERROR_ENABLED == STD_ON )
#   define SOAD_REPORT_SOCK_ERROR(API_ID, BSD_API_ID, ERRNO) \
            SoAd_GetSocketReportErrorCbk(0u)((API_ID), (BSD_API_ID), SOAD_SOCK_BSD_PARAM_NONE, \
              SOAD_SOCK_BSD_VALUE_NONE, SOAD_SOCK_BSD_VALUE_NONE, (ERRNO))
#   define SOAD_REPORT_SOCK_ERROR_PARAM(API_ID, BSD_API_ID, PARAM, ERRNO) \
            SoAd_GetSocketReportErrorCbk(0u)((API_ID), (BSD_API_ID), (PARAM), SOAD_SOCK_BSD_VALUE_NONE, \
              SOAD_SOCK_BSD_VALUE_NONE, (ERRNO))
#   define SOAD_REPORT_SOCK_ERROR_PARAM_1(API_ID, BSD_API_ID, PARAM, VAL1, ERRNO) \
            SoAd_GetSocketReportErrorCbk(0u)((API_ID), (BSD_API_ID), (PARAM), (VAL1), SOAD_SOCK_BSD_VALUE_NONE, \
              (ERRNO))
#   define SOAD_REPORT_SOCK_ERROR_PARAM_2(API_ID, BSD_API_ID, PARAM, VAL1, VAL2, ERRNO) \
            SoAd_GetSocketReportErrorCbk(0u)((API_ID), (BSD_API_ID), (PARAM), (VAL1), (VAL2), (ERRNO))
#  else
#   define SOAD_REPORT_SOCK_ERROR(API_ID, BSD_API_ID, ERRNO)
#   define SOAD_REPORT_SOCK_ERROR_PARAM(API_ID, BSD_API_ID, PARAM, ERRNO)
#   define SOAD_REPORT_SOCK_ERROR_PARAM_1(API_ID, BSD_API_ID, PARAM, VAL1, ERRNO)
#   define SOAD_REPORT_SOCK_ERROR_PARAM_2(API_ID, BSD_API_ID, PARAM, VAL1, VAL2, ERRNO)
#  endif /* SOAD_SOCKET_REPORT_ERROR_ENABLED == STD_ON */
# endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */

# define SOAD_DUMMY_STATEMENT_TYPE_VOID  0u
# define SOAD_DUMMY_STATEMENT_TYPE_VAR   1u

# if ( !defined(SOAD_DUMMY_STATEMENT_TYPE) )
#  define SOAD_DUMMY_STATEMENT_VAR(v)         SOAD_DUMMY_STATEMENT(v) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define SOAD_DUMMY_STATEMENT_CONST_VAR(v)   SOAD_DUMMY_STATEMENT_CONST(v) /* PRQA S 3453 */ /* MD_MSR_19.7 */
# else
#  if ( SOAD_DUMMY_STATEMENT_TYPE_VOID == SOAD_DUMMY_STATEMENT_TYPE )
#   define SOAD_DUMMY_STATEMENT_VAR(v)        (void)(v); /* PRQA S 3453 */ /* MD_MSR_19.7 */
#   define SOAD_DUMMY_STATEMENT_CONST_VAR(v)  (void)(v); /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  else
#   define SOAD_DUMMY_STATEMENT_VAR(v)        (v)=(v); /* PRQA S 3453 */ /* MD_MSR_19.7 */
#   define SOAD_DUMMY_STATEMENT_CONST_VAR(v)  SOAD_DUMMY_STATEMENT_CONST(v) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  endif /* SOAD_DUMMY_STATEMENT_TYPE_VOID == SOAD_DUMMY_STATEMENT_TYPE */
# endif /* !defined(SOAD_DUMMY_STATEMENT_VAR) */

/* PRQA S 3453 2 */ /* MD_MSR_19.7 */
# define SOAD_ADDR_IPV6_COPY(Destination, Source)  \
            IpBase_Copy((Destination).addr, (Source).addr, SOAD_IPV6_ADDR_LEN_BYTE)

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

# define SOAD_START_SEC_VAR_NOINIT_32BIT
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */ /*lint !e451 */

# if ( (SOAD_TIMEOUTLISTUDPALIVE == STD_ON) || (SOAD_TIMEOUTLISTNPDUUDPTX == STD_ON) )
/*! Counts the main function cycles (with wrap around) to handle timeouts for the timeout lists. */
extern VAR(uint32, SOAD_VAR_NOINIT) SoAd_GlobalCounter;
# endif /* (SOAD_TIMEOUTLISTUDPALIVE == STD_ON) || (SOAD_TIMEOUTLISTNPDUUDPTX == STD_ON) */

# define SOAD_STOP_SEC_VAR_NOINIT_32BIT
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */ /*lint !e451 */

# define SOAD_START_SEC_VAR_ZERO_INIT_8BIT
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */ /*lint !e451 */

/*! Indicates current state of the module state machine (Valid values: SOAD_STATE_*). */
extern VAR(SoAd_StateType, SOAD_VAR_ZERO_INIT) SoAd_State;

# define SOAD_STOP_SEC_VAR_ZERO_INIT_8BIT
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */ /*lint !e451 */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define SOAD_START_SEC_CODE
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */ /*lint !e451 */

# if ( SOAD_SINGLE_MAIN_FUNCTION == STD_ON )
/**********************************************************************************************************************
 *  SoAd_MainFunctionRx()
 *********************************************************************************************************************/
/*! \brief       Schedules the asynchronous reception handling.
 *  \details     -
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_MainFunctionRx(void);

/**********************************************************************************************************************
 *  SoAd_MainFunctionState()
 *********************************************************************************************************************/
/*! \brief       Schedules state handling.
 *  \details     -
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_MainFunctionState(void);

/**********************************************************************************************************************
 *  SoAd_MainFunctionTx()
 *********************************************************************************************************************/
/*! \brief       Schedules the asynchronous transmission handling.
 *  \details     -
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_MainFunctionTx(void);
# endif /* SOAD_SINGLE_MAIN_FUNCTION == STD_ON */

# define SOAD_STOP_SEC_CODE
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */ /*lint !e451 */

#endif /* !defined(SOAD_PRIV_H) */

/*!
 * \exclusivearea SOAD_EXCLUSIVE_AREA_0
 * Ensures consistency while read, modify and write global variables which are accessed in multiple context (ISR/TASK).
 * \protects SoAd_EventQueueFlag, SoAd_EventQueueDyn, SoAd_BestMatchSoConIdxList, SoAd_SocketDyn, SoAd_SoConDyn,
 * SoAd_RcvRemAddr, SoAd_LocalAddrDyn, SoAd_SocketTxBufferMgt, SoAd_TimeoutListUdpAlive, SoAd_TimeoutListDyn,
 * SoAd_TimeoutListUdpAliveMap, SoAd_TimeoutListUdpAlive, SoAd_TimeoutListNPduUdpTxMap, SoAd_TimeoutListNPduUdpTx,
 * SoAd_TxMgt, SoAd_PduRouteDyn, SoAd_TcpTxQueueData, SoAd_TcpTxQueueMgt, SoAd_NPduUdpTxDyn, SoAd_NPduUdpTxBuffer
 * \usedin SoAd_EventQueue_AddElement, SoAd_EventQueue_GetNextElement, SoAd_SoCon_TcpAcceptedGetSoConIdx, 
 * SoAd_SoCon_EventUdpClose, SoAd_SoCon_SetRemoteAddrCheckAndSet, SoAd_SoCon_ResetCloseMode, SoAd_SoCon_SetRemoteAddr,
 * SoAd_SoCon_SetUniqueRemoteAddr, SoAd_SoCon_RequestOpenSoCon, SoAd_SoCon_RequestCloseSoCon,
 * SoAd_SoCon_OpenSoConOnReception, SoAd_SoCon_HandleUdpAliveTimeout, SoAd_SoCon_CheckAndGetRcvRemoteAddr,
 * SoAd_SoCon_LocalIpAddrAssignmentChg, SoAd_TcpIpBsd_HandleIpAddrStates, SocketTxBufferMgt,
 * SoAd_TcpIpBsd_RequestSocketTxBuffer, SoAd_TcpIpBsd_UpdateSocketTxBuffer, SoAd_TcpIpBsd_HandleSocketTxBuffer,
 * SoAd_TcpIpBsd_HandleSocketTxBuffer, SoAd_TimeoutList_SetElement, SoAd_TimeoutList_GetCurrentTimeout,
 * SoAd_TimeoutList_CheckElements, SoAd_TimeoutList_RemoveElement, SoAd_TxIf_TcpTransmit, SoAd_TxIf_UdpTransmitPdu,
 * SoAd_TxIf_TcpTxConfirmation, SoAd_TxTp_TransmitPdu, SoAd_TxTcpQueue_Clear, SoAd_TxTcpQueue_ReserveNextElement,
 * SoAd_TxTcpQueue_SetElement, SoAd_TxTcpQueue_TxConfirmation, SoAd_TxNPduUdp_QueueAddOrUpdateElement,
 * SoAd_TxNPduUdp_QueuePrepareTransmitSegment, SoAd_TxNPduUdp_QueueTxConfirmation, SoAd_TxNPduUdp_BufferAddElement,
 * SoAd_TxNPduUdp_BufferSend
 * \exclude All other functions provided by SoAd.
 * \length MEDIUM More than a few statements with a constant maximum runtime and a low call-tree.
 * \endexclusivearea
 */

/**********************************************************************************************************************
 *  END OF FILE: SoAd_Priv.h
 *********************************************************************************************************************/
