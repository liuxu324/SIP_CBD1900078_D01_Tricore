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
/*!        \file  Eth_30_Tc3xx_LL_IrqHandler.c
 *        \brief  Lower layer implementation of interrupt handler
 *
 *      \details  Implementation of lower layer part of the interrupt handler.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the version history in Eth_30_Tc3xx_LL.h
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the newest version in Eth_30_Tc3xx_LL.h
 *********************************************************************************************************************/

/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */

#define ETH_30_TC3XX_LL_IRQ_HANDLER_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Eth_30_Tc3xx.h"
#include "Eth_30_Tc3xx_HwAccess_Int.h"
#include "Eth_30_Tc3xx_LL_IrqHandler.h"
#include "Eth_30_Tc3xx_IrqHandler_Int.h"
#include "Eth_30_Tc3xx_LL_Int.h"
#include "Eth_30_Tc3xx_LL.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define ETH_30_TC3XX_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION DEFINITIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrTx
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_IRQHANDLER_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrTx(
  uint8 ctrlIdx,
  uint8 queueIdx,
  Eth_30_Tc3xx_RegOffsetType regAddr)
{
  /* #10 Clear respective interrupt flags */
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, regAddr, ETH_30_TC3XX_REG_DMA_CHN_STATUS_NIS | ETH_30_TC3XX_REG_DMA_CHN_STATUS_TI);

  /* #20 As long as there is a Tx frame to be confirmed */
  while ((Eth_30_Tc3xx_LL_IsTxQueuePending(ctrlIdx, queueIdx) == TRUE))
  {
    /* #210 Trigger transmission confirmation and reception handling */
    Eth_30_Tc3xx_TxConfirmation(ctrlIdx);
  }
} /* Eth_30_Tc3xx_IrqHdlrTx() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrRx
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_IRQHANDLER_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrRx(
  uint8 ctrlIdx,
  uint8 queueIdx,
  Eth_30_Tc3xx_RegOffsetType regAddr)
{
  Eth_RxStatusType rxStatus = ETH_NOT_RECEIVED;

  /* #10 Clear respective interrupt flags */
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, regAddr, ETH_30_TC3XX_REG_DMA_CHN_STATUS_NIS | ETH_30_TC3XX_REG_DMA_CHN_STATUS_RI);

  /* #20 As long as there is a Rx frame to be received */
  while ((Eth_30_Tc3xx_LL_IsRxQueuePending(ctrlIdx, queueIdx) == TRUE) ||
         (rxStatus == ETH_RECEIVED_MORE_DATA_AVAILABLE))
  {
    /* #210 Trigger transmission confirmation and reception handling */
    Eth_30_Tc3xx_Receive(ctrlIdx, &rxStatus);
  }
} /* Eth_30_Tc3xx_IrqHdlrRx() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrQ0Tx()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrQ0Tx(
  uint8 ctrlIdx)
{
  /* #10 Call the IRQ helper function with related register address and queue index */
  Eth_30_Tc3xx_IrqHdlrTx(ctrlIdx, ETH_30_TC3XX_TXQ0, ETH_30_TC3XX_REG_OFFS_DMA_CH0_STATUS);
} /* Eth_30_Tc3xx_IrqHdlrQ0Tx() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrQ0Rx()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrQ0Rx(
  uint8 ctrlIdx)
{
  /* #10 Call the IRQ helper function */
  Eth_30_Tc3xx_IrqHdlrRx(ctrlIdx, ETH_30_TC3XX_RXQ0, ETH_30_TC3XX_REG_OFFS_DMA_CH0_STATUS);
} /* Eth_30_Tc3xx_IrqHdlrQ0Rx() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrQ1Tx()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrQ1Tx(
  uint8 ctrlIdx)
{
  /* #10 Call the IRQ helper function */
  Eth_30_Tc3xx_IrqHdlrTx(ctrlIdx, ETH_30_TC3XX_TXQ1, ETH_30_TC3XX_REG_OFFS_DMA_CH1_STATUS);
} /* Eth_30_Tc3xx_IrqHdlrQ1Tx() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrQ1Rx()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrQ1Rx(
  uint8 ctrlIdx)
{
  /* #10 Call the IRQ helper function */
  Eth_30_Tc3xx_IrqHdlrRx(ctrlIdx, ETH_30_TC3XX_RXQ1, ETH_30_TC3XX_REG_OFFS_DMA_CH1_STATUS);
} /* Eth_30_Tc3xx_IrqHdlrQ1Rx() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrQ2Tx()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrQ2Tx(
  uint8 ctrlIdx)
{
  /* #10 Call the IRQ helper function */
  Eth_30_Tc3xx_IrqHdlrTx(ctrlIdx, ETH_30_TC3XX_TXQ2, ETH_30_TC3XX_REG_OFFS_DMA_CH2_STATUS);
} /* Eth_30_Tc3xx_IrqHdlrQ2Tx() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrQ2Rx()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrQ2Rx(
  uint8 ctrlIdx)
{
  /* #10 Call the IRQ helper function */
  Eth_30_Tc3xx_IrqHdlrRx(ctrlIdx, ETH_30_TC3XX_RXQ2, ETH_30_TC3XX_REG_OFFS_DMA_CH2_STATUS);
} /* Eth_30_Tc3xx_IrqHdlrQ2Rx() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrQ3Tx()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrQ3Tx(
  uint8 ctrlIdx)
{
  /* #10 Call the IRQ helper function */
  Eth_30_Tc3xx_IrqHdlrTx(ctrlIdx, ETH_30_TC3XX_TXQ3, ETH_30_TC3XX_REG_OFFS_DMA_CH3_STATUS);
} /* Eth_30_Tc3xx_IrqHdlrQ3Tx() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrQ3Rx()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrQ3Rx(
  uint8 ctrlIdx)
{
  /* #10 Call the IRQ helper function */
  Eth_30_Tc3xx_IrqHdlrRx(ctrlIdx, ETH_30_TC3XX_RXQ3, ETH_30_TC3XX_REG_OFFS_DMA_CH3_STATUS);
} /* Eth_30_Tc3xx_IrqHdlrQ3Rx() */

#define ETH_30_TC3XX_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_IrqHandler.c
 *********************************************************************************************************************/

