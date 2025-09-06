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
/**        \file  SoAd_RouteGrp.h
 *        \brief  Socket Adaptor header file
 *
 *      \details  Vector static code header file for AUTOSAR Socket Adaptor sub-component RouteGrp.
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

#if !defined (SOAD_ROUTE_GRP_H)
# define SOAD_ROUTE_GRP_H

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
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  SoAd_RouteGrp_Init()
**********************************************************************************************************************/
/*! \brief        Initializes routing group structs.
 *  \details      -
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_RouteGrp_Init(void);

/**********************************************************************************************************************
 *  SoAd_RouteGrp_SetRoutingGroupStateOnPduRouteDest()
 *********************************************************************************************************************/
/*! \brief        Sets routing group state on all routing group related PduRouteDests.
 *  \details      -
 *  \param[in]    RouteGrpIdx     Routing group index.
 *                                [range: RouteGrpIdx < SoAd_GetSizeOfRouteGrp()]
 *  \param[in]    State           Indicates if routing group state shall be enabled or disabled otherwise.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
/* PRQA S 777 3 */ /* MD_MSR_5.1_777 */
FUNC(void, SOAD_CODE) SoAd_RouteGrp_SetRoutingGroupStateOnPduRouteDest(
  SoAd_SizeOfRouteGrpType RouteGrpIdx,
  boolean State);

/**********************************************************************************************************************
 *  SoAd_RouteGrp_SetRoutingGroupStateOnSockRoute()
 *********************************************************************************************************************/
/*! \brief        Sets routing group state on all routing group related SocketRoutes.
 *  \details      -
 *  \param[in]    RouteGrpIdx     Routing group index.
 *                                [range: RouteGrpIdx < SoAd_GetSizeOfRouteGrp()]
 *  \param[in]    State           Indicates if routing group state shall be enabled or disabled otherwise.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
/* PRQA S 777 3 */ /* MD_MSR_5.1_777 */
FUNC(void, SOAD_CODE) SoAd_RouteGrp_SetRoutingGroupStateOnSockRoute(
  SoAd_SizeOfRouteGrpType RouteGrpIdx,
  boolean State);

/**********************************************************************************************************************
 *  SoAd_RouteGrp_SetSpecificRoutingGroupState()
 *********************************************************************************************************************/
/*! \brief        Sets routing group state on all routing group related PduRouteDest/SocketRoutes.
 *  \details      -
 *  \param[in]    RouteGrpIdx     Routing group index.
 *                                [range: RouteGrpIdx < SoAd_GetSizeOfRouteGrp()]
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    State           Indicates if routing group state shall be enabled or disabled otherwise.
 *  \return       E_OK            Routing state set for at least one related PduRouteDest or SocketRoute.
 *  \return       E_NOT_OK        No routing state set.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_RouteGrp_SetSpecificRoutingGroupState(
  SoAd_SizeOfRouteGrpType RouteGrpIdx,
  SoAd_SizeOfSoConType SoConIdx,
  boolean State);

/**********************************************************************************************************************
 *  SoAd_RouteGrp_SetIfTransmit()
 *********************************************************************************************************************/
/*! \brief        Sets a routing group to be transmitted in main function context.
 *  \details      -
 *  \param[in]    RouteGrpIdx     Routing group index.
 *                                [range: RouteGrpIdx < SoAd_GetSizeOfRouteGrp()]
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_RouteGrp_SetIfTransmit(
  SoAd_SizeOfRouteGrpType RouteGrpIdx);

/**********************************************************************************************************************
 *  SoAd_RouteGrp_SetIfSpecificTransmit()
 *********************************************************************************************************************/
/*! \brief        Sets a routing group to be transmitted on a specific socket connection in main function context.
 *  \details      -
 *  \param[in]    RouteGrpIdx     Routing group index.
 *                                [range: RouteGrpIdx < SoAd_GetSizeOfRouteGrp()]
 *  \param[in]    SoConIdx        Socket connection index.
 *                                [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \return       E_OK            Transmission requested sucessfully.
 *  \return       E_NOT_OK        Routing group is not related to the socket connection.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_RouteGrp_SetIfSpecificTransmit(
  SoAd_SizeOfRouteGrpType RouteGrpIdx,
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_RouteGrp_HandleIfTransmit()
**********************************************************************************************************************/
/*! \brief        Handles routing group transmission.
 *  \details      -
 *  \param[out]   ErrorIdPtr      Pointer to error identifier (set if error occurred).
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_RouteGrp_HandleIfTransmit(
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_RouteGrp_CheckAnyRoutGrpOnPduRouteDestEnabled()
 *********************************************************************************************************************/
/*! \brief        Checks if any routing group is enabled on a PduRouteDest.
 *  \details      -
 *  \param[in]    PduRouteDestIdx     Pdu route destination index.
 *                                    [range: PduRouteDestIdx < SoAd_GetSizeOfPduRouteDest()]
 *  \return       IsEnabled           Indicates if any routing group is enabled.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(boolean, SOAD_CODE) SoAd_RouteGrp_CheckAnyRoutGrpOnPduRouteDestEnabled(
  SoAd_SizeOfPduRouteDestType PduRouteDestIdx);

/**********************************************************************************************************************
 *  SoAd_RouteGrp_CheckAnyRoutGrpOnSockRouteDestEnabled()
 *********************************************************************************************************************/
/*! \brief        Checks if any routing group is enabled on a SocketRoute(Dest).
 *  \details      -
 *  \param[in]    SockRouteIdx      Socket route index.
 *                                  [range: SockRouteIdx < SoAd_GetSizeOfSocketRoute()]
 *  \return       IsEnabled         Indicates if any routing group is enabled.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
/* PRQA S 777 2 */ /* MD_MSR_5.1_777 */
FUNC(boolean, SOAD_CODE) SoAd_RouteGrp_CheckAnyRoutGrpOnSockRouteDestEnabled(
  SoAd_SizeOfSocketRouteType SockRouteIdx);

# define SOAD_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_19.1 */

#endif /* !defined(SOAD_ROUTE_GRP_H) */

/**********************************************************************************************************************
 *  END OF FILE: SoAd_RouteGrp.h
 *********************************************************************************************************************/
