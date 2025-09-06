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
/*!        \file  Eth_30_Tc3xx_LL_TimeSync.h
 *        \brief  Header of lower layer part of the Ethernet controller driver timer sub-module
 *
 *      \details  Provides access to the hardware timer related API of the Ethernet controller driver.
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

#if !defined (ETH_30_TC3XX_LL_TIME_SYNC_H)
# define      ETH_30_TC3XX_LL_TIME_SYNC_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_TimeSync_Int.h"
# include "Eth_30_Tc3xx_HwAccess_Int.h"
# include "Eth_30_Tc3xx_CfgAccess_Int.h"
# include "SchM_Eth_30_Tc3xx.h"
# include "Eth_30_Tc3xx_Int.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# if !defined (ETH_30_TC3XX_LL_TIME_SYNC_LOCAL)
#  define ETH_30_TC3XX_LL_TIME_SYNC_LOCAL static
# endif /* ETH_30_TC3XX_LL_TIME_SYNC_LOCAL */

# if !defined (ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE)
#  define ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE LOCAL_INLINE
# endif /* ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE */

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TimeSync_Init
 **********************************************************************************************************************/
/*! \brief       Initializes the time synchronization hardware
 *  \details     -
 *  \param[in]   ctrlIdx              Identifier of the Eth controller
 *  \return      E_OK - Initialization finished successfully
 *  \return      E_NOT_OK - Initialization failed
 *  \context     ANY
 *  \reentrant   TRUE for different Eth controllers
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TimeSync_Init(
    uint8 ctrlIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_TimeSync_LL_CaptureHwTime
 **********************************************************************************************************************/
/*! \brief       Captures the hardware timer of the Eth controller and returns the time stamp
 *  \details     -
 *  \param[in]   ctrlIdx      Identifier of Eth controller
 *  \param[out]  timeStampPtr Time stamp captured
 *  \context     ANY
 *  \reentrant   TRUE for different Eth controllers
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_TimeSync_LL_CaptureHwTime(
        uint8                                    ctrlIdx,
  P2VAR(Eth_TimeStampType, AUTOMATIC, AUTOMATIC) timeStampPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_TimeSync_LL_SetHwTime
 **********************************************************************************************************************/
/*! \brief       Sets the hardware and software part of the timer to the given time
 *  \details     -
 *  \param[in]   ctrlIdx      Identifier of Eth controller
 *  \param[in]   timeStampPtr Time to set
 *  \context     ANY
 *  \reentrant   TRUE for different Eth controllers
 *  \synchronous TRUE
 *  \pre         Exclusive area for hardware timer (EXCLUSIVE_AREA_TIME) entered
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_TimeSync_LL_SetHwTime(
          uint8                                    ctrlIdx,
  P2CONST(Eth_TimeStampType, AUTOMATIC, AUTOMATIC) timeStampPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_TimeSync_LL_GetTxTimeStamp
 **********************************************************************************************************************/
/*! \brief       Retrieves the tx time stamp from the given descriptor
 *  \details     -
 *  \param[in]   ctrlIdx      Identifier of Eth controller
 *  \param[in]   ringIdx      Identifier of the tx descriptor ring
 *  \param[in]   descrIdx     Identifier of the tx descriptor within the ring
 *  \param[out]  timeStampPtr Transmission time stamp
 *  \context     TASK|ISR <Eth_UL>_TxConfirmation()
 *  \reentrant   TRUE for different tx descriptor
 *  \synchronous TRUE
 *  \pre         -
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_TimeSync_LL_GetTxTimeStamp(
        uint8                                    ctrlIdx,
        uint8                                    ringIdx,
        uint8                                    descrIdx,
  P2VAR(Eth_TimeStampType, AUTOMATIC, AUTOMATIC) timeStampPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_TimeSync_LL_GetRxTimeStamp
 **********************************************************************************************************************/
/*! \brief       Retrieves the rx time stamp from the given descriptor
 *  \details     -
 *  \param[in]   ctrlIdx       Identifier of Eth controller
 *  \param[in]   ringIdx       Identifier of the rx descriptor ring
 *  \param[in]   descrIdx      Identifier of the rx descriptor within the ring
 *  \param[out]  timeStampPtr  Reception time stamp
 *  \context     TASK|ISR <Eth_UL>_RxIndication()
 *  \reentrant   TRUE for different rx descriptor
 *  \synchronous TRUE
 *  \pre        -
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_TimeSync_LL_GetRxTimeStamp(
        uint8                                    ctrlIdx,
        uint8                                    ringIdx,
        uint8                                    descrIdx,
  P2VAR(Eth_TimeStampType, AUTOMATIC, AUTOMATIC) timeStampPtr);
  
/**********************************************************************************************************************
 *  GLOBAL FUNCTION DEFINITONS
 *********************************************************************************************************************/
 
 /***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TimeSync_Init
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TimeSync_Init( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  return E_OK;
} /* Eth_30_Tc3xx_LL_TimeSync_Init() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_TimeSync_LL_CaptureHwTime
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_TimeSync_LL_CaptureHwTime( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
        uint8                                    ctrlIdx,
  P2VAR(Eth_TimeStampType, AUTOMATIC, AUTOMATIC) timeStampPtr)
{
  uint32 sec;
  uint16 secHi;
  uint16 hwLoopCycles = 0u;
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 Loop if cycle count limit is not reached yet */
  while (hwLoopCycles < Eth_30_Tc3xx_LoopCycles[ctrlIdx])
  {
    hwLoopCycles++;

    /* #100 Get hardware time stamp from hardware timer register parts */
    timeStampPtr->secondsHi   =  (uint16) /* PRQA S 0306 1 */ /* MD_Eth_0306 */
        Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS,
                                           ETH_30_TC3XX_REG_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_TSHWR_MASK);
    timeStampPtr->seconds     = /* PRQA S 0306 1 */ /* MD_Eth_0306 */
        Eth_30_Tc3xx_Reg_Read    (ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_SECONDS);
    timeStampPtr->nanoseconds = /* PRQA S 0306 1 */ /* MD_Eth_0306 */
        Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_NANOSECONDS,
                                           ETH_30_TC3XX_REG_MAC_SYSTEM_TIME_NANOSECONDS_TSSS_MASK);

    /* #110 Check if there was any time stamp part overflow during retrieval of separate time stamp parts */
    secHi = (uint16) /* PRQA S 0306 1 */ /* MD_Eth_0306 */
        Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS,
                                           ETH_30_TC3XX_REG_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_TSHWR_MASK);
    sec   = /* PRQA S 0306 1 */ /* MD_Eth_0306 */
        Eth_30_Tc3xx_Reg_Read    (ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_SECONDS);

    if ((timeStampPtr->secondsHi == secHi) && (timeStampPtr->seconds == sec))
    {
      /* #1100 Consistent and valid time stamp retrieved therefore break the loop */
      retVal = E_OK;
      break;
    }

    /* #120 In case there was an overflow do another loop execution to try again to read consistent time stamp parts
     * (no further overflow for the duration of approximately one second expected) */
  }

  /* #20 Check if a valid time stamp is available */
  if (retVal != E_OK)
  {
    /* #210 No valid time stamp is available so reset time stamp return values to 0 and do error reporting */
    ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(ctrlIdx);
    timeStampPtr->secondsHi   = 0u;
    timeStampPtr->seconds     = 0ul;
    timeStampPtr->nanoseconds = 0ul;
  }

  return retVal;
} /* Eth_30_Tc3xx_TimeSync_LL_CaptureHwTime() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_TimeSync_LL_SetHwTime
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_TimeSync_LL_SetHwTime( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
          uint8                                    ctrlIdx,
  P2CONST(Eth_TimeStampType, AUTOMATIC, AUTOMATIC) timeStampPtr)
{
  /* #10 Set time in hardware timer registers */
  /* PRQA S 0306 5 */ /* MD_Eth_0306 */
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE,  timeStampPtr->nanoseconds);
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_SECONDS_UPDATE,      timeStampPtr->seconds);
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS, timeStampPtr->secondsHi);

  Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_TIMESTAMP_CONTROL,
                                       ETH_30_TC3XX_REG_MAC_TIMESTAMP_CONTROL_TSINIT_MASK);

  return E_OK;
} /* Eth_30_Tc3xx_TimeSync_LL_SetHwTime() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_TimeSync_LL_GetTxTimeStamp
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_TimeSync_LL_GetTxTimeStamp( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
        uint8                                    ctrlIdx,
        uint8                                    ringIdx,
        uint8                                    descrIdx,
  P2VAR(Eth_TimeStampType, AUTOMATIC, AUTOMATIC) timeStampPtr)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 Check descriptor index */
  if (Eth_30_Tc3xx_Cfg_GetTxDescrNum(ctrlIdx, ringIdx) > descrIdx)
  {
    P2VAR(Eth_30_Tc3xx_TxDescriptorType, AUTOMATIC, AUTOMATIC) txDescPtr =
        Eth_30_Tc3xx_Cfg_GetTxDescr(ctrlIdx, ringIdx, descrIdx);

    /* #110 Check if last descriptor bit and TX timestamp status flags are available */
    if (((txDescPtr->TxDescrWord[ETH_30_TC3XX_DES3_IDX] & ETH_30_TC3XX_TX3_DESC_STATUS_LD)   != 0ul) &&
        ((txDescPtr->TxDescrWord[ETH_30_TC3XX_DES3_IDX] & ETH_30_TC3XX_TX3_DESC_STATUS_TTSS) != 0ul))
    {
      /* #1010 Retrieve TX time stamp */
      timeStampPtr->nanoseconds = txDescPtr->TxDescrWord[ETH_30_TC3XX_DES0_IDX];
      timeStampPtr->seconds     = txDescPtr->TxDescrWord[ETH_30_TC3XX_DES1_IDX];
      /* The seconds portion, stored in the descriptor only contains the lower 32 bits. The upper bits must be read
       * from Higher Word Seconds Register.
       * There is a potential risk that the Higher Word Seconds Register was increased between the actual reception of
       * the frame and the time the descriptor is processed here. However this risk is extremely unlikely and cannot be
       * avoided
       */
      /* PRQA S 0306 1 */ /* MD_Eth_0306 */
      timeStampPtr->secondsHi = (uint16)
          (Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS) & 0x0000FFFFul);

      /* #1020 Check if time stamp is valid, if an all ones pattern is set, the timestamp is not valid */
      if ((timeStampPtr->seconds != 0xFFFFFFFFul) && (timeStampPtr->nanoseconds != 0xFFFFFFFFul))
      {
        retVal = E_OK;
      }
    }
  }
  return retVal;
} /* Eth_30_Tc3xx_TimeSync_LL_GetTxTimeStamp() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_TimeSync_LL_GetRxTimeStamp
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TIME_SYNC_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_TimeSync_LL_GetRxTimeStamp( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
        uint8                                    ctrlIdx,
        uint8                                    ringIdx,
        uint8                                    descrIdx,
  P2VAR(Eth_TimeStampType, AUTOMATIC, AUTOMATIC) timeStampPtr)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 Check descriptor index */
  if (Eth_30_Tc3xx_Cfg_GetRxDescrNum(ctrlIdx, ringIdx) > descrIdx)
  {
    P2VAR(Eth_30_Tc3xx_RxDescriptorType, AUTOMATIC, AUTOMATIC) rxDescPtr =
        Eth_30_Tc3xx_Cfg_GetRxDescr(ctrlIdx, ringIdx, descrIdx);

    /* #110 Check for last descriptor, timestamp valid and timestamp not dropped flags */
    if (((rxDescPtr->RxDescrWord[ETH_30_TC3XX_DES3_IDX] & ETH_30_TC3XX_RX3_DESC_LD)  != 0ul) &&
        ((rxDescPtr->RxDescrWord[ETH_30_TC3XX_DES1_IDX] & ETH_30_TC3XX_RX1_DESC_TSA) != 0ul) &&
        ((rxDescPtr->RxDescrWord[ETH_30_TC3XX_DES1_IDX] & ETH_30_TC3XX_RX1_DESC_TD)  == 0ul))
    {
      /* #1010 Retrieve RX time stamp */
      timeStampPtr->nanoseconds = rxDescPtr->RxDescrWord[ETH_30_TC3XX_CNTXT_DES0_IDX];
      timeStampPtr->seconds     = rxDescPtr->RxDescrWord[ETH_30_TC3XX_CNTXT_DES1_IDX];
      /* The seconds portion, stored in the descriptor only contains the lower 32 bits. The upper bits must be read
       * from Higher Word Seconds Register.
       * There is a potential risk that the Higher Word Seconds Register was increased between the actual reception of
       * the frame and the time the descriptor is processed here. However this risk is extremely unlikely and cannot be
       * avoided
       */
      /* PRQA S 0306 1 */ /* MD_Eth_0306 */
      timeStampPtr->secondsHi = (uint16)
          (Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS) & (0x0000FFFFul));

      /* #1020 Check if time stamp is valid, if an all ones pattern is set, the timestamp is not valid */
      if ((timeStampPtr->seconds != 0xFFFFFFFFul) && (timeStampPtr->nanoseconds != 0xFFFFFFFFul))
      {
        retVal = E_OK;
      }
    }
  }
  return retVal;
} /* Eth_30_Tc3xx_TimeSync_LL_GetRxTimeStamp() */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

#endif /* ETH_30_TC3XX_LL_TIME_SYNC_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_TimeSync.h
 *********************************************************************************************************************/

