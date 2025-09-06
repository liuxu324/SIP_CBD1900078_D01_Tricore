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
/**        \file  Eth_30_Tc3xx_IrqHandler_Int.h
 *        \brief  Component private header file of IRQ sub-module.
 *
 *      \details  Private header file of IRQ sub-module.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777 */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */
#if !defined (ETH_30_TC3XX_IRQ_HANDLER_INT_H)
# define ETH_30_TC3XX_IRQ_HANDLER_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_Types.h"
# include "Eth_30_Tc3xx_Int.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# if !defined(ETH_30_TC3XX_IRQ_HANDLER_LOCAL)
#  define ETH_30_TC3XX_IRQ_HANDLER_LOCAL LOCAL_INLINE
# endif /* ETH_30_TC3XX_IRQ_HANDLER_LOCAL */

/**********************************************************************************************************************
 *  GLOBAL TYPES
 *********************************************************************************************************************/
/*! Represents a bit mask holding tx/rx events where MSB represents the highest and LSB represents the lowest prio event */
typedef uint16 Eth_30_Tc3xx_PendingEventsType;

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
# define ETH_30_TC3XX_START_SEC_VAR_NOINIT_16BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern VAR(Eth_30_Tc3xx_PendingEventsType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_PendingRxEvents[ETH_30_TC3XX_MAX_CTRLS_TOTAL];
extern VAR(Eth_30_Tc3xx_PendingEventsType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_PendingTxEvents[ETH_30_TC3XX_MAX_CTRLS_TOTAL];

# define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_16BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetHighestPrioPendingRxEventDescrRing
 **********************************************************************************************************************/
/*! \brief        Retrieve the descriptor ring related to the highest prio event pending
 *  \details      -
 *  \param[in]    events  Bit maks having bits set representing an event
 *  \return       Descriptor ring with the highest prio event, if no event is pending -> invalid descriptor ring value
 *  \context      ANY
 *  \reentrant    TRUE for different events
 *  \pre          -
 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetHighestPrioPendingEventDescrRing(
  P2VAR(Eth_30_Tc3xx_PendingEventsType, AUTOMATIC, AUTOMATIC) events);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_SetRxEvent
 **********************************************************************************************************************/
/*! \brief        Sets an rx event for the given reception descriptor ring
 *  \details      -
 *  \param[in]    ctrlIdx       Identifier of the Ethernet controller
 *  \param[in]    descrRingIdx  Identifier of the reception descriptor ring
 *  \context      ANY
 *  \reentrant    TRUE
 *  \pre          -
 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetRxEvent(
  uint8 ctrlIdx,
  uint8 descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetHighestPrioPendingRxEventDescrRing
 **********************************************************************************************************************/
/*! \brief        Retrieves the recpetion descriptor ring related to the highest prio rx event pending
 *  \details      -
 *  \param[in]    ctrlIdx       Identifier of the Ethernet controller
 *  \return       Descriptor ring with the highest prio event, if no event is pending -> invalid descriptor ring value
 *  \context      ANY
 *  \reentrant    TRUE for different Ethernet controllers
 *  \pre          -
 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetHighestPrioPendingRxEventDescrRing(
  uint8 ctrlIdx); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_SetTxEvent
 **********************************************************************************************************************/
/*! \brief        Sets an tx event for the given transmission descriptor ring
 *  \details      -
 *  \param[in]    ctrlIdx       Identifier of the Ethernet controller
 *  \param[in]    descrRingIdx  Identifier of the transmission descriptor ring
 *  \context      ANY
 *  \reentrant    TRUE
 *  \pre          -
 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetTxEvent(
  uint8 ctrlIdx,
  uint8 descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetHighestPrioPendingTxEventDescrRing
 **********************************************************************************************************************/
/*! \brief        Retrieves the transmission descriptor ring related to the highest prio tx event pending
 *  \details      -
 *  \param[in]    ctrlIdx       Identifier of the Ethernet controller
 *  \return       Descriptor ring with the highest prio event, if no event is pending -> invalid descriptor ring value
 *  \context      ANY
 *  \reentrant    TRUE for different Ethernet controllers
 *  \pre          -
 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetHighestPrioPendingTxEventDescrRing(
  uint8 ctrlIdx); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetHighestPrioPendingEventDescrRing
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetHighestPrioPendingEventDescrRing( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  P2VAR(Eth_30_Tc3xx_PendingEventsType, AUTOMATIC, AUTOMATIC) events)
{
  sint8_least flagIdx;
  uint8       descrRingIdx = ETH_30_TC3XX_UNDEFINED_DESCRIPTOR_RING;

  /* Search downwards because highest prio event will be found first */
  for( flagIdx = (sizeof(Eth_30_Tc3xx_PendingEventsType) * 8) - 1; flagIdx >= 0; flagIdx-- )
  {
    Eth_30_Tc3xx_PendingEventsType bitMask = (Eth_30_Tc3xx_PendingEventsType)((uint32)1u << (uint32)(sint32)flagIdx);

    if( ((*events) & bitMask) != 0u )
    {
      descrRingIdx = (uint8)flagIdx;
      (*events) = (Eth_30_Tc3xx_PendingEventsType)((uint32)(*events) & (uint32)(~(uint32)bitMask));
      break;
    }
  }

  return descrRingIdx;
} /* Eth_30_Tc3xx_GetHighestPrioPendingEventDescrRing() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_SetRxEvent
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetRxEvent( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 descrRingIdx)
{
  Eth_30_Tc3xx_PendingRxEvents[ctrlIdx] |= 1u << descrRingIdx;
} /* Eth_30_Tc3xx_SetRxEvent() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetHighestPrioPendingRxEventDescrRing
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetHighestPrioPendingRxEventDescrRing( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  return Eth_30_Tc3xx_GetHighestPrioPendingEventDescrRing(&Eth_30_Tc3xx_PendingRxEvents[ctrlIdx]);
} /* Eth_30_Tc3xx_GetHighestPrioPendingRxEventDescrRing() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_SetTxEvent
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetTxEvent( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 descrRingIdx)
{
  Eth_30_Tc3xx_PendingTxEvents[ctrlIdx] |= 1u << descrRingIdx;
} /* Eth_30_Tc3xx_SetTxEvent() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetHighestPrioPendingTxEventDescrRing
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_IRQ_HANDLER_LOCAL FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetHighestPrioPendingTxEventDescrRing( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  return Eth_30_Tc3xx_GetHighestPrioPendingEventDescrRing(&Eth_30_Tc3xx_PendingTxEvents[ctrlIdx]);
} /* Eth_30_Tc3xx_GetHighestPrioPendingTxEventDescrRing() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_ProcessIsr
 **********************************************************************************************************************/
/*! \brief        Processes the interrupt events of a specific interrupt service routine
 *  \details      Function processes the interrupt event handler functions of a specific interrupt service routine.
 *                Additionally - if enabled during configuration - pre- and post-ISR-User-Functions are proccessed too.
 *  \param[in]    ctrlIdx    Module local identifier of the controller
 *  \param[in]    isrIdx     Interrupt service routine identifier
 *  \context      ISR1|ISR2
 *  \reentrant    TRUE for different interrupt service routines
 *  \pre          -
 **********************************************************************************************************************/
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ProcessIsr(
  uint8 ctrlIdx,
  uint8 isrIdx);

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ETH_30_TC3XX_IRQ_HANDLER_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_IrqHandler_Int.h
 *********************************************************************************************************************/

