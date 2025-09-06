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
/**        \file  Eth_30_Tc3xx_TrafficHandling.c
 *        \brief  Traffic handling sub-module source file of the Ethernet controller driver
 *
 *      \details  Containes the implementation of the traffic handling related API of the Ethernet controller driver.
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

#define ETH_30_TC3XX_TRAFFIC_HANDLING_SOURCE

/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Eth_30_Tc3xx_TrafficHandling.h"
#include "Eth_30_Tc3xx_TrafficHandling_Int.h"
#include "Eth_30_Tc3xx_LL_TrafficHandling.h"
#include "Eth_30_Tc3xx.h"
#include "Eth_30_Tc3xx_Int.h"
#include "Eth_30_Tc3xx_LL_Cfg.h"
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#if !defined (ETH_30_TC3XX_TRAFFIC_HANDLING_LOCAL)
# define ETH_30_TC3XX_TRAFFIC_HANDLING_LOCAL static
#endif /* ETH_30_TC3XX_TIME_SYNC_LOCAL */

#if !defined (ETH_30_TC3XX_TRAFFIC_HANDLING_LOCAL_INLINE)
# define ETH_30_TC3XX_TRAFFIC_HANDLING_LOCAL_INLINE LOCAL_INLINE
#endif /* ETH_30_TC3XX_TRAFFIC_HANDLING_LOCAL_INLINE */

#if (ETH_30_TC3XX_DYNAMIC_TRAFFIC_SHAPING_SUPPORT == STD_ON)

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS PROTOTYPES
 **********************************************************************************************************************/

# if (ETH_30_TC3XX_IMPLEMENTATION_SET_BANDWIDTH_LIMIT == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_SetBandwidthLimit
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetBandwidthLimit(
    uint8   CtrlIdx,
    uint8   QueuePrio,
    uint32  BandwidthLimit)
{
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETH_30_TC3XX_E_NO_ERROR;

  CtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);

#  if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausability of input parameters and module/controller state */
  if( Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT )
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if( CtrlIdx >= ETH_30_TC3XX_MAX_CTRLS_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if( Eth_30_Tc3xx_CtrlMode[CtrlIdx] == ETH_MODE_DOWN )
  {
    errorId = ETH_30_TC3XX_E_INV_MODE;
  }
  else if( QueuePrio >= Eth_30_Tc3xx_Cfg_GetTxDescrRingNum(CtrlIdx) )
  {
    errorId = ETH_30_TC3XX_E_INV_PARAM;
  }
  else
#  endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    uint32 trcvSpeed = Eth_30_Tc3xx_Cfg_GetTrcvSpeed(CtrlIdx);

    /* #20 Check if new bandwidth limit doesn't exceed transceiver capabilities */
     if( BandwidthLimit <= trcvSpeed )
     {
       uint8_least descrRingIdx;
       uint32 curBandwidth = 0;

       /* #200 Calculate overall bandwidth consumption */
       for(descrRingIdx = 0; descrRingIdx < Eth_30_Tc3xx_Cfg_GetTxDescrRingNum(CtrlIdx); descrRingIdx++)
       {
         if( (Eth_30_Tc3xx_Cfg_IsShaperAvailable(CtrlIdx, (uint8)descrRingIdx) == TRUE) && (descrRingIdx != QueuePrio) )
         {
           curBandwidth += Eth_30_Tc3xx_LL_TrafficHandling_GetCurrentShaperBandwidth(CtrlIdx, (uint8)descrRingIdx); /*lint !e522 */
         }
       }

       /* #210 Check if new bandwidth limit for queue in combination with overall bandwidth consumption doesn't exceed transceiver capabilities */
       if( (BandwidthLimit + curBandwidth) <= trcvSpeed )
       {
         /* #2100 Set new bandwidth */
         Eth_30_Tc3xx_LL_TrafficHandling_SetShaperBandwidth(CtrlIdx, QueuePrio, BandwidthLimit); /*lint !e522 */
         retVal = E_OK;
       }
     }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  /* #30 Report default errors if any occured */
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx), ETH_30_TC3XX_SID_SET_BANDWIDTH_LIMIT, errorId);
  }
#  else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
#  endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* Eth_30_Tc3xx_SetBandwidthLimit() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif /* ETH_30_TC3XX_IMPLEMENTATION_SET_BANDWIDTH_LIMIT */

# if (ETH_30_TC3XX_IMPLEMENTATION_GET_BANDWIDTH_LIMIT == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetBandwidthLimit
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetBandwidthLimit(
          uint8                          CtrlIdx,
          uint8                          QueuePrio,
    P2VAR(uint32, AUTOMATIC, AUTOMATIC)  BandwidthLimitPtr)
{
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETH_30_TC3XX_E_NO_ERROR;

  CtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);

#  if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausability of input parameters and module/controller state */
  if( Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT )
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if( CtrlIdx >= ETH_30_TC3XX_MAX_CTRLS_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if( Eth_30_Tc3xx_CtrlMode[CtrlIdx] == ETH_MODE_DOWN )
  {
    errorId = ETH_30_TC3XX_E_INV_MODE;
  }
  else if( QueuePrio >= Eth_30_Tc3xx_Cfg_GetTxDescrRingNum(CtrlIdx) )
  {
    errorId = ETH_30_TC3XX_E_INV_PARAM;
  }
  else if( BandwidthLimitPtr == NULL_PTR )
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
#  endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* #20 Check if a shaper is available on the queue and if so retrieve and provide it's bandwidth to the caller */
    if( Eth_30_Tc3xx_Cfg_IsShaperAvailable(CtrlIdx, QueuePrio) == TRUE )
    {
      (*BandwidthLimitPtr) = Eth_30_Tc3xx_LL_TrafficHandling_GetCurrentShaperBandwidth(CtrlIdx, QueuePrio); /*lint !e522 */
      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  /* #30 Report default errors if any occured */
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx), ETH_30_TC3XX_SID_GET_BANDWIDTH_LIMIT, errorId);
  }
#  else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
#  endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* Eth_30_Tc3xx_GetBandwidthLimit() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif /* ETH_30_TC3XX_IMPLEMENTATION_GET_BANDWIDTH_LIMIT */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ETH_30_TC3XX_DYNAMIC_TRAFFIC_SHAPING_SUPPORT */

/* module specific MISRA deviations:
 * see file Eth.c
*/

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_TrafficHandling.c
 *********************************************************************************************************************/

