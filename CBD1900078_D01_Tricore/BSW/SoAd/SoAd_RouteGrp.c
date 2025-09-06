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
/**        \file  SoAd_RouteGrp.c
 *        \brief  Socket Adaptor source file
 *
 *      \details  Vector static code implementation for AUTOSAR Socket Adaptor sub-component RouteGrp.
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

#define SOAD_ROUTE_GRP_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "SoAd_EventQueue.h"
#include "SoAd_RouteGrp.h"
#include "SoAd_Tx.h"

#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
# include "Det.h"
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

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
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  SoAd_RouteGrp_SetRoutingGroupStateOnSpecificPduRouteDest()
 *********************************************************************************************************************/
/*! \brief      Sets routing group state on all routing group and specific socket connection related PduRouteDests.
 *  \details    -
 *  \param[in]  RouteGrpIdx     Routing group index.
 *                              [range: RouteGrpIdx < SoAd_GetSizeOfRouteGrp()]
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  State           State of routing group.
 *  \return     E_OK            Routing enabled for at least one related PduRouteDest.
 *  \return     E_NOT_OK        No routing enabled.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
/* PRQA S 779 4 */ /* MD_MSR_5.1_779 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RouteGrp_SetRoutingGroupStateOnSpecificPduRouteDest(
  SoAd_SizeOfRouteGrpType RouteGrpIdx,
  SoAd_SizeOfSoConType SoConIdx,
  boolean State);

/**********************************************************************************************************************
 *  SoAd_RouteGrp_SetRoutingGroupStateOnSpecificSockRoute()
 *********************************************************************************************************************/
/*! \brief      Sets routing group state on all routing group and specific socket connection related SocketRoutes.
 *  \details    -
 *  \param[in]  RouteGrpIdx     Routing group index.
 *                              [range: RouteGrpIdx < SoAd_GetSizeOfRouteGrp()]
 *  \param[in]  SoConIdx        Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]  State           State of routing group.
 *  \return     E_OK            Routing enabled for at least one related SocketRoute.
 *  \return     E_NOT_OK        No routing enabled.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
/* PRQA S 779 4 */ /* MD_MSR_5.1_779 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RouteGrp_SetRoutingGroupStateOnSpecificSockRoute(
  SoAd_SizeOfRouteGrpType RouteGrpIdx,
  SoAd_SizeOfSoConType SoConIdx,
  boolean State);

/**********************************************************************************************************************
 *  SoAd_RouteGrp_IfTransmit()
 *********************************************************************************************************************/
/*! \brief        Transmits a routing group on all related PduRouteDests.
 *  \details      -
 *  \param[in]    RouteGrpIdx     Routing group index.
 *                                [range: RouteGrpIdx < SoAd_GetSizeOfRouteGrp()]
 *  \param[out]   ErrorIdPtr      Pointer to error identifier (set if error occurred).
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RouteGrp_IfTransmit(
  SoAd_SizeOfRouteGrpType RouteGrpIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_RouteGrp_IfTransmitPduRouteDest()
 *********************************************************************************************************************/
/*! \brief          Transmits a routing group on a PduRouteDest.
 *  \details        Uses parameter "LastPduRouteIdxPtr" and "PduInfoPtr" to handle multiple tranmissions on different
 *                  socket connections of same PduRoute.
 *  \param[in]      PduRouteDestIdx     PDU route destination index on routing group.
 *                                      [range: PduRouteDestIdx < SoAd_GetSizeOfPduRouteDest()]
 *  \param[in,out]  LastPduRouteIdxPtr  Pointer to last handled PDU route index (updated on call).
 *  \param[in,out]  PduInfoPtr          Pointer to PDU retrieved before (overwritten on call).
 *  \param[out]     ErrorIdPtr          Pointer to error identifier (set if error occurred).
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RouteGrp_IfTransmitPduRouteDest(
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  P2VAR(SoAd_SizeOfPduRouteType, AUTOMATIC, SOAD_APPL_VAR) LastPduRouteIdxPtr,
  P2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  SoAd_RouteGrp_SetRoutingGroupStateOnSpecificPduRouteDest()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RouteGrp_SetRoutingGroupStateOnSpecificPduRouteDest(
  SoAd_SizeOfRouteGrpType RouteGrpIdx,
  SoAd_SizeOfSoConType SoConIdx,
  boolean State)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_PduRouteDestByRouteGrpIndIterType  pduRouteDestByRouteGrpIndIter;
  Std_ReturnType                          retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over routing group related PduRouteDests. */
  for ( pduRouteDestByRouteGrpIndIter = SoAd_GetPduRouteDestByRouteGrpIndStartIdxOfRouteGrp(RouteGrpIdx);
    pduRouteDestByRouteGrpIndIter < SoAd_GetPduRouteDestByRouteGrpIndEndIdxOfRouteGrp(RouteGrpIdx);
    pduRouteDestByRouteGrpIndIter++ )
  {
    SoAd_SizeOfPduRouteDestType pduRouteDestIdx = SoAd_GetPduRouteDestByRouteGrpInd(pduRouteDestByRouteGrpIndIter);

    /* #20 Check if PduRouteDest is related to specified socket connection. */
    if ( SoAd_GetSoConIdxOfPduRouteDest(pduRouteDestIdx) == SoConIdx )
    {
      /* #30 Set routing group state. */
      SoAd_SetEnabledOfRouteGrpPduRouteDest(pduRouteDestByRouteGrpIndIter, State);                                     /* SBSW_SOAD_CSL03 */

      retVal = E_OK;
    }
  }

  return retVal;
} /* SoAd_RouteGrp_SetRoutingGroupStateOnSpecificPduRouteDest() */

/**********************************************************************************************************************
 *  SoAd_RouteGrp_SetRoutingGroupStateOnSpecificSockRoute()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_RouteGrp_SetRoutingGroupStateOnSpecificSockRoute(
  SoAd_SizeOfRouteGrpType RouteGrpIdx,
  SoAd_SizeOfSoConType SoConIdx,
  boolean State)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SocketRouteByRouteGrpIndIterType sockRouteByRouteGrpIndIter;
  Std_ReturnType                        retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over routing group related SocketRoutes. */
  for ( sockRouteByRouteGrpIndIter = SoAd_GetSocketRouteByRouteGrpIndStartIdxOfRouteGrp(RouteGrpIdx);
    sockRouteByRouteGrpIndIter < SoAd_GetSocketRouteByRouteGrpIndEndIdxOfRouteGrp(RouteGrpIdx);
    sockRouteByRouteGrpIndIter++ )
  {
    SoAd_SizeOfSocketRouteType socketRouteIdx = SoAd_GetSocketRouteByRouteGrpInd(sockRouteByRouteGrpIndIter);

    /* #20 Check if SocketRoute is related to specified socket connection. */
    if ( SoAd_GetSoConIdxOfSocketRoute(socketRouteIdx) == SoConIdx )
    {
      /* #30 Set routing group state. */
      SoAd_SetEnabledOfRouteGrpSocketRoute(sockRouteByRouteGrpIndIter, State);                                         /* SBSW_SOAD_CSL03 */

      retVal = E_OK;
    }
  }

  return retVal;
} /* SoAd_RouteGrp_SetRoutingGroupStateOnSpecificSockRoute() */

/**********************************************************************************************************************
 *  SoAd_RouteGrp_IfTransmit()
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
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RouteGrp_IfTransmit(
  SoAd_SizeOfRouteGrpType RouteGrpIdx,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  PduInfoType                             pduInfo = { NULL_PTR, 0u };
  SoAd_SizeOfPduRouteType                 lastPduRouteIdx = SoAd_GetSizeOfPduRoute();
  SoAd_PduRouteDestByRouteGrpIndIterType  pduRouteDestByRouteGrpIndIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all PduRouteDests related to the routing group. */
  for ( pduRouteDestByRouteGrpIndIter = SoAd_GetPduRouteDestByRouteGrpIndStartIdxOfRouteGrp(RouteGrpIdx);
    pduRouteDestByRouteGrpIndIter < SoAd_GetPduRouteDestByRouteGrpIndEndIdxOfRouteGrp(RouteGrpIdx);
    pduRouteDestByRouteGrpIndIter++ )
  {
    SoAd_SizeOfPduRouteDestType pduRouteDestIdx = SoAd_GetPduRouteDestByRouteGrpInd(pduRouteDestByRouteGrpIndIter);

    /* #100 Check if routing group transmit trigger is set for this PduRouteDest. */
    if ( SoAd_IsTriggerOfRouteGrpPduRouteDest(pduRouteDestByRouteGrpIndIter) == TRUE )
    {
      /* #1000 Trigger transmission of PduRouteDest. */
      SoAd_RouteGrp_IfTransmitPduRouteDest(pduRouteDestIdx, &lastPduRouteIdx, &pduInfo, ErrorIdPtr);                   /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */

      /* Reset transmit trigger flag later since multiple PduRouteDests of this RoutingGroup may reference the
       * same socket connection. */
    }
  }

  /* #20 Iterate over all PduRouteDests again to reset trigger flags. */
  for ( pduRouteDestByRouteGrpIndIter = SoAd_GetPduRouteDestByRouteGrpIndStartIdxOfRouteGrp(RouteGrpIdx);
    pduRouteDestByRouteGrpIndIter < SoAd_GetPduRouteDestByRouteGrpIndEndIdxOfRouteGrp(RouteGrpIdx);
    pduRouteDestByRouteGrpIndIter++ )
  {
    /* #200 Reset transmit trigger flags. */
    SoAd_SetTriggerOfRouteGrpPduRouteDest(pduRouteDestByRouteGrpIndIter, FALSE);                                       /* SBSW_SOAD_CSL03 */
  }
} /* SoAd_RouteGrp_IfTransmit() */

/**********************************************************************************************************************
 *  SoAd_RouteGrp_IfTransmitPduRouteDest()
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
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_RouteGrp_IfTransmitPduRouteDest(
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx,
  P2VAR(SoAd_SizeOfPduRouteType, AUTOMATIC, SOAD_APPL_VAR) LastPduRouteIdxPtr,
  P2VAR(PduInfoType, AUTOMATIC, SOAD_APPL_VAR) PduInfoPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfPduRouteType pduRouteIdx;

  /* ----- Implementation ----------------------------------------------- */
  pduRouteIdx = SoAd_GetPduRouteIdxOfPduRouteDest(PduRouteDestIdx);

#if ( SOAD_TX_DYN_LEN == STD_ON )
  /* #10 Check if transmission with trigger transmit is configured for this PDU. */
  if ( SoAd_IsIfTriggerTransmitEnabledOfPduRoute(pduRouteIdx) == TRUE )
  {
    /* #20 Prepare transmit with size of maximum configured PDU size and copy less data in CopyTxData if necessary. */
    PduInfoPtr->SduDataPtr = NULL_PTR;                                                                                 /* SBSW_SOAD_POINTER_WRITE */
    PduInfoPtr->SduLength = SoAd_GetMaxIfRouteGrpTransmitPduSize();                                                    /* SBSW_SOAD_POINTER_WRITE */

    /* #30 Transmit PDU. */
    (void)SoAd_Tx_IfTransmitPduRouteDest(PduRouteDestIdx, PduInfoPtr, ErrorIdPtr);                                     /* SBSW_SOAD_POINTER_FORWARD */
  }
  else
#endif /* SOAD_TX_DYN_LEN == STD_ON) */
  /* #11 Handle transmission for PDUs with direct transmit otherwise. */
  {
    /* #40 Check if trigger transmit has already been called for the corresponding PduRoute. */
    if ( pduRouteIdx == *LastPduRouteIdxPtr )
    {
      /* #50 Check if trigger transmit call succeeded. */
      if ( PduInfoPtr->SduDataPtr != NULL_PTR )
      {
        /* #60 Transmit PDU. */
        (void)SoAd_Tx_IfTransmitPduRouteDest(PduRouteDestIdx, PduInfoPtr, ErrorIdPtr);                                 /* SBSW_SOAD_POINTER_FORWARD */
      }
    }
    /* #41 Retrieve PDU data via trigger transmit otherwise. */
    else
    {
      /* #70 Prepare transmit with pointer to local trigger transmit buffer and corresponding size. */
      PduInfoPtr->SduDataPtr = SoAd_GetAddrIfRouteGrpTransmitBuf(0u);                                                  /* SBSW_SOAD_POINTER_WRITE */
      PduInfoPtr->SduLength  = SoAd_GetIfRouteGrpTransmitBufSize();                                                    /* SBSW_SOAD_POINTER_WRITE */

      /* #80 Store index of PduRoute to prevent that trigger transmit is called multiple times for same PduRoute. */
      *LastPduRouteIdxPtr = pduRouteIdx;                                                                               /* SBSW_SOAD_POINTER_WRITE */

      /* #90 Call IfTriggerTransmit of upper layer and check if call succeeds. */
      if ( SoAd_GetIfTriggerTransmitCbkOfUpperLayer(SoAd_GetUpperLayerIdxOfPduRoute(pduRouteIdx))(                     /* SBSW_SOAD_FUNCTION_PTR */
        SoAd_GetTxConfPduIdOfPduRoute(pduRouteIdx), PduInfoPtr) == E_OK )
      {
        /* #100 Check if returned parameters are valid. */
        if ( (PduInfoPtr->SduDataPtr != NULL_PTR) && (PduInfoPtr->SduLength != 0u) &&
          (PduInfoPtr->SduLength <= SoAd_GetIfRouteGrpTransmitBufSize()) )
        {
          /* #110 Transmit PDU. */
          (void)SoAd_Tx_IfTransmitPduRouteDest(PduRouteDestIdx, PduInfoPtr, ErrorIdPtr);                               /* SBSW_SOAD_POINTER_FORWARD */
        }
        /* #101 Indicate that call failed otherwise. */
        else
        {
          PduInfoPtr->SduDataPtr = NULL_PTR;                                                                           /* SBSW_SOAD_POINTER_WRITE */
        }
      }
      /* #91 Indicate that call failed otherwise. */
      else
      {
        PduInfoPtr->SduDataPtr = NULL_PTR;                                                                             /* SBSW_SOAD_POINTER_WRITE */
      }
    }
  }
} /* SoAd_RouteGrp_IfTransmitPduRouteDest() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  SoAd_RouteGrp_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_RouteGrp_Init(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_RouteGrpIterType routeGrpIter;
  boolean               routeGrpEnabled;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all routing groups. */
  for ( routeGrpIter = 0u; routeGrpIter < SoAd_GetSizeOfRouteGrp(); routeGrpIter++ )
  {
    SoAd_PduRouteDestByRouteGrpIndIterType  pduRouteDestByRouteGrpIndIter;
    SoAd_SocketRouteByRouteGrpIndIterType   socketRouteByRouteGrpIndIter;

    /* #20 Get routing group state at initialization. */
    routeGrpEnabled = (boolean)SoAd_IsEnabledAtInitOfRouteGrp(routeGrpIter);

    /* #30 Initialize routing group states on PduRouteDests. */
    for ( pduRouteDestByRouteGrpIndIter = SoAd_GetPduRouteDestByRouteGrpIndStartIdxOfRouteGrp(routeGrpIter);
      pduRouteDestByRouteGrpIndIter < SoAd_GetPduRouteDestByRouteGrpIndEndIdxOfRouteGrp(routeGrpIter);
      pduRouteDestByRouteGrpIndIter++ )
    {
      SoAd_SetEnabledOfRouteGrpPduRouteDest(pduRouteDestByRouteGrpIndIter, routeGrpEnabled);                           /* SBSW_SOAD_CSL03 */
      SoAd_SetTriggerOfRouteGrpPduRouteDest(pduRouteDestByRouteGrpIndIter, FALSE);                                     /* SBSW_SOAD_CSL03 */
    }

    /* #40 Initialize routing group states on SocketRoutes. */
    for ( socketRouteByRouteGrpIndIter = SoAd_GetSocketRouteByRouteGrpIndStartIdxOfRouteGrp(routeGrpIter);
      socketRouteByRouteGrpIndIter < SoAd_GetSocketRouteByRouteGrpIndEndIdxOfRouteGrp(routeGrpIter);
      socketRouteByRouteGrpIndIter++ )
    {
      SoAd_SetEnabledOfRouteGrpSocketRoute(socketRouteByRouteGrpIndIter, routeGrpEnabled);                             /* SBSW_SOAD_CSL03 */
    }
  }
} /* SoAd_RouteGrp_Init() */

/**********************************************************************************************************************
 *  SoAd_RouteGrp_SetRoutingGroupStateOnPduRouteDest()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_RouteGrp_SetRoutingGroupStateOnPduRouteDest(
  SoAd_SizeOfRouteGrpType RouteGrpIdx,
  boolean State)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_PduRouteDestByRouteGrpIndIterType pduRouteDestByRouteGrpIndIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over routing group related PduRouteDests. */
  for ( pduRouteDestByRouteGrpIndIter = SoAd_GetPduRouteDestByRouteGrpIndStartIdxOfRouteGrp(RouteGrpIdx);
    pduRouteDestByRouteGrpIndIter < SoAd_GetPduRouteDestByRouteGrpIndEndIdxOfRouteGrp(RouteGrpIdx);
    pduRouteDestByRouteGrpIndIter++ )
  {
    /* #20 Set routing group state. */
    SoAd_SetEnabledOfRouteGrpPduRouteDest(pduRouteDestByRouteGrpIndIter, State);                                       /* SBSW_SOAD_CSL03 */
  }
} /* SoAd_RouteGrp_SetRoutingGroupStateOnPduRouteDest() */

/**********************************************************************************************************************
 *  SoAd_RouteGrp_SetRoutingGroupStateOnSockRoute()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_RouteGrp_SetRoutingGroupStateOnSockRoute(
  SoAd_SizeOfRouteGrpType RouteGrpIdx,
  boolean State)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SocketRouteByRouteGrpIndIterType socketRouteByRouteGrpIndIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over routing group related SocketRoutes. */
  for ( socketRouteByRouteGrpIndIter = SoAd_GetSocketRouteByRouteGrpIndStartIdxOfRouteGrp(RouteGrpIdx);
    socketRouteByRouteGrpIndIter < SoAd_GetSocketRouteByRouteGrpIndEndIdxOfRouteGrp(RouteGrpIdx);
    socketRouteByRouteGrpIndIter++ )
  {
    /* #20 Set routing group state. */
    SoAd_SetEnabledOfRouteGrpSocketRoute(socketRouteByRouteGrpIndIter, State);                                         /* SBSW_SOAD_CSL03 */
  }
} /* SoAd_RouteGrp_SetRoutingGroupStateOnSockRoute() */

/**********************************************************************************************************************
 *  SoAd_RouteGrp_SetSpecificRoutingGroupState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_RouteGrp_SetSpecificRoutingGroupState(
  SoAd_SizeOfRouteGrpType RouteGrpIdx,
  SoAd_SizeOfSoConType SoConIdx,
  boolean State)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set routing group state for routing group related PduRouteDests on the specified socket connection. */
  if ( SoAd_RouteGrp_SetRoutingGroupStateOnSpecificPduRouteDest(RouteGrpIdx, SoConIdx, State) == E_OK )
  {
    retVal = E_OK;
  }

  /* #20 Set routing group state for routing group related SocketRoutes on the specified socket connection. */
  if ( SoAd_RouteGrp_SetRoutingGroupStateOnSpecificSockRoute(RouteGrpIdx, SoConIdx, State) == E_OK )
  {
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_RouteGrp_SetSpecificRoutingGroupState() */

/**********************************************************************************************************************
 *  SoAd_RouteGrp_SetIfTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_RouteGrp_SetIfTransmit(
  SoAd_SizeOfRouteGrpType RouteGrpIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_PduRouteDestByRouteGrpIndIterType pduRouteDestByRouteGrpIndIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Store transmission request for all related PduRouteDests. */
  for ( pduRouteDestByRouteGrpIndIter = SoAd_GetPduRouteDestByRouteGrpIndStartIdxOfRouteGrp(RouteGrpIdx);
    pduRouteDestByRouteGrpIndIter < SoAd_GetPduRouteDestByRouteGrpIndEndIdxOfRouteGrp(RouteGrpIdx);
    pduRouteDestByRouteGrpIndIter++ )
  {
    SoAd_SetTriggerOfRouteGrpPduRouteDest(pduRouteDestByRouteGrpIndIter, TRUE);                                        /* SBSW_SOAD_CSL03 */
  }

  /* #20 Set event to handle routing group transmit request in main function. */
  SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_IF_TX_ROUTE_GRP, RouteGrpIdx);
} /* SoAd_RouteGrp_SetIfTransmit() */

/**********************************************************************************************************************
 *  SoAd_RouteGrp_SetIfSpecificTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_RouteGrp_SetIfSpecificTransmit(
  SoAd_SizeOfRouteGrpType RouteGrpIdx,
  SoAd_SizeOfSoConType SoConIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_PduRouteDestByRouteGrpIndIterType  pduRouteDestByRouteGrpIndIter;
  Std_ReturnType                          retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Store transmission request for the related PduRouteDest. */
  for ( pduRouteDestByRouteGrpIndIter = SoAd_GetPduRouteDestByRouteGrpIndStartIdxOfRouteGrp(RouteGrpIdx);
    pduRouteDestByRouteGrpIndIter < SoAd_GetPduRouteDestByRouteGrpIndEndIdxOfRouteGrp(RouteGrpIdx);
    pduRouteDestByRouteGrpIndIter++ )
  {
    SoAd_SizeOfPduRouteDestType pduRouteDestIdx = SoAd_GetPduRouteDestByRouteGrpInd(pduRouteDestByRouteGrpIndIter);

    if ( SoAd_GetSoConIdxOfPduRouteDest(pduRouteDestIdx) == SoConIdx )
    {
      SoAd_SetTriggerOfRouteGrpPduRouteDest(pduRouteDestByRouteGrpIndIter, TRUE);                                      /* SBSW_SOAD_CSL03 */

      retVal = E_OK;
    }
  }

  /* #20 Set event to handle routing group transmit request in main function. */
  if ( retVal == E_OK )
  {
    SoAd_EventQueue_AddElement(SOAD_EVENT_QUEUE_IF_TX_ROUTE_GRP, RouteGrpIdx);
  }

  return retVal;
} /* SoAd_RouteGrp_SetIfSpecificTransmit() */

/**********************************************************************************************************************
 *  SoAd_RouteGrp_HandleIfTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_RouteGrp_HandleIfTransmit(
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_EventQueueIfTxRouteGrpIterType eventQueueIfTxRouteGrpIter;
  uint32                              handleIdx = 0u;
  uint32                              elementNumToHandle = SoAd_EventQueue_GetElementNumToHandle(
    SOAD_EVENT_QUEUE_IF_TX_ROUTE_GRP);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all queue elements which have to be handled in this context considering configured limit. */
  for ( eventQueueIfTxRouteGrpIter = 0u;
    eventQueueIfTxRouteGrpIter < elementNumToHandle;
    eventQueueIfTxRouteGrpIter++ )
  {
    /* #20 Get next element. */
    if ( SoAd_EventQueue_GetNextElement(SOAD_EVENT_QUEUE_IF_TX_ROUTE_GRP, &handleIdx) == E_OK )                        /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    {
      /* #30 Transmit routing group. */
      SoAd_RouteGrp_IfTransmit((SoAd_SizeOfRouteGrpType)handleIdx, ErrorIdPtr);                                        /* SBSW_SOAD_POINTER_FORWARD */
    }
    /* #21 Stop iteration if no element is left. */
    else
    {
      break;
    }
  }
} /* SoAd_RouteGrp_HandleIfTransmit() */

/**********************************************************************************************************************
 *  SoAd_RouteGrp_CheckAnyRoutGrpOnPduRouteDestEnabled()
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
FUNC(boolean, SOAD_CODE) SoAd_RouteGrp_CheckAnyRoutGrpOnPduRouteDestEnabled(
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_RouteGrpByPduRouteDestIndIterType  routeGrpByPduRouteDestIndIter;
  SoAd_SizeOfRouteGrpPduRouteDestType     routeGrpPduRouteDestIdx;
  boolean                                 retVal = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if any routing group is configured. */
  if ( SoAd_GetRouteGrpByPduRouteDestIndStartIdxOfPduRouteDest(PduRouteDestIdx) !=
    SoAd_GetRouteGrpByPduRouteDestIndEndIdxOfPduRouteDest(PduRouteDestIdx) )
  {
    /* #20 Iterate over all related routing groups. */
    for ( routeGrpByPduRouteDestIndIter = SoAd_GetRouteGrpByPduRouteDestIndStartIdxOfPduRouteDest(PduRouteDestIdx);
      routeGrpByPduRouteDestIndIter < SoAd_GetRouteGrpByPduRouteDestIndEndIdxOfPduRouteDest(PduRouteDestIdx);
      routeGrpByPduRouteDestIndIter++ )
    {
      routeGrpPduRouteDestIdx = SoAd_GetRouteGrpPduRouteDestByPduRouteDestInd(routeGrpByPduRouteDestIndIter);

      /* #30 Check if routing group is enabled. */
      if ( SoAd_IsEnabledOfRouteGrpPduRouteDest(routeGrpPduRouteDestIdx) == TRUE )
      {
        /* #40 Indicate to forward PDU. */
        retVal = TRUE;
        break;
      }
    }
  }
  /* #11 Indicate to forward PDU otherwise. */
  else
  {
    retVal = TRUE;
  }

  return retVal;
} /* SoAd_RouteGrp_CheckAnyRoutGrpOnPduRouteDestEnabled() */

/**********************************************************************************************************************
 *  SoAd_RouteGrp_CheckAnyRoutGrpOnSockRouteDestEnabled()
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
FUNC(boolean, SOAD_CODE) SoAd_RouteGrp_CheckAnyRoutGrpOnSockRouteDestEnabled(
  SoAd_SizeOfSocketRouteType SockRouteIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_RouteGrpSocketRouteBySocketRouteIndIterType  routeGrpSocketRouteBySocketRouteIndIter;
  SoAd_SizeOfRouteGrpSocketRouteType                routeGrpSocketRouteIdx;
  boolean                                           retVal = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if any routing group is configured. */
  if ( SoAd_GetRouteGrpSocketRouteBySocketRouteIndStartIdxOfSocketRoute(SockRouteIdx) !=
    SoAd_GetRouteGrpSocketRouteBySocketRouteIndEndIdxOfSocketRoute(SockRouteIdx))
  {
    /* #20 Iterate over all related routing groups. */
    for ( routeGrpSocketRouteBySocketRouteIndIter =
        SoAd_GetRouteGrpSocketRouteBySocketRouteIndStartIdxOfSocketRoute(SockRouteIdx);
      routeGrpSocketRouteBySocketRouteIndIter <
        SoAd_GetRouteGrpSocketRouteBySocketRouteIndEndIdxOfSocketRoute(SockRouteIdx);
      routeGrpSocketRouteBySocketRouteIndIter++ )
    {
      routeGrpSocketRouteIdx = SoAd_GetRouteGrpSocketRouteBySocketRouteInd(routeGrpSocketRouteBySocketRouteIndIter);

      /* #30 Check if routing group is enabled. */
      if ( SoAd_IsEnabledOfRouteGrpSocketRoute(routeGrpSocketRouteIdx) == TRUE )
      {
        /* #40 Indicate to forward PDU. */
        retVal = TRUE;
        break;
      }
    }
  }
  /* #11 Indicate to forward PDU otherwise. */
  else
  {
    retVal = TRUE;
  }

  return retVal;
} /* SoAd_RouteGrp_CheckAnyRoutGrpOnSockRouteDestEnabled() */

#define SOAD_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Justification for module-specific MISRA deviations:
 * see file SoAd.c
 */

/**********************************************************************************************************************
 *  END OF FILE: SoAd_RouteGrp.c
 *********************************************************************************************************************/
