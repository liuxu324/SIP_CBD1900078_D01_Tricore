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
/**        \file  Eth_30_Tc3xx.c
 *        \brief  Ethernet controller driver implementation
 *
 *      \details  Core part of the Ethernet controller driver implementation.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define ETH_30_TC3XX_SOURCE

/*lint -e438 */ /* Suppress ID438 because Config pointer only used in Post-Build Variant */
/*lint -e506 */ /* Suppress ID506 due to MD_MSR_14.1 */
/*lint -e537 */ /* Suppress ID537 due to MD_MSR_19.1 */
/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */

/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Eth_30_Tc3xx.h"
#include "Eth_30_Tc3xx_Int.h"
#include "Eth_30_Tc3xx_LL_Cfg.h"
#include "Eth_30_Tc3xx_Cfg.h"
#include "Eth_30_Tc3xx_Lcfg.h"
#include "Eth_30_Tc3xx_LL.h"
#include "Eth_30_Tc3xx_HwAccess_Int.h"
#include "Eth_30_Tc3xx_IrqHandler_Int.h"
#include "EthIf_Cbk.h"
#if (ETH_30_TC3XX_ENABLE_MAC_WRITE_ACCESS == STD_ON)
# include "NvM.h"
#endif /* ETH_30_TC3XX_ENABLE_MAC_WRITE_ACCESS */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */
#if (ETH_30_TC3XX_DEM_ERROR_DETECT == STD_ON)
# include "Dem.h"
#endif /* ETH_30_TC3XX_DEM_ERROR_DETECT */

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#ifndef ETH_30_TC3XX_LOCAL
# define ETH_30_TC3XX_LOCAL static
#endif
 
#ifndef ETH_30_TC3XX_LOCAL_INLINE
# define ETH_30_TC3XX_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
VAR(Eth_StateType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_ModuleInitialized;
VAR(Eth_ModeType, ETH_30_TC3XX_VAR_ZERO_INIT) Eth_30_Tc3xx_CtrlMode[ETH_30_TC3XX_MAX_CTRLS_TOTAL];
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

ETH_30_TC3XX_LOCAL VAR(Eth_FrameIdType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_CurrentFrameId[ETH_30_TC3XX_MAX_CTRLS_TOTAL];

#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/
#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define ETH_30_TC3XX_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsBroadcast
 **********************************************************************************************************************/
/*! \brief      Checks wheather the MAC address is the broadcast address
 *  \details    -
 *  \param[in]  macAddr  MAC address that shall be checked
 *  \return     FALSE - MAC address isn't broadcast address
 *  \return     TRUE - MAC address is broadcast address
 *  \context    ANY
 *  \reentrant  TRUE
 *  \pre        -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsBroadcast(
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) macAddr);

#if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsZeroAddress
 **********************************************************************************************************************/
/*! \brief      Checks wheather the MAC address is all-zero
 *  \details    -
 *  \param[in]  macAddr  MAC address that shall be checked
 *  \return     FALSE - MAC address isn't all zero
 *  \return     TRUE - MAC address is all zero
 *  \context    ANY
 *  \reentrant  TRUE
 *  \pre        -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsZeroAddress(
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) macAddr);
#endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */

#if (ETH_30_TC3XX_IMPLEMENTATION_SET_CONTROLLER_MODE == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_InitBuffersAndDescriptors
 **********************************************************************************************************************/
/*! \brief      Initializes the transmission and reception buffers, descriptors and structures
 *  \details    -
 *  \param[in]  ctrlIdx  Identifier of the Ethernet controller
 *  \context    TASK
 *  \reentrant  TRUE for different Ethernet controllers
 *  \pre        -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_InitBuffersAndDescriptors(
  uint8 ctrlIdx);
#endif /* ETH_30_TC3XX_IMPLEMENTATION_SET_CONTROLLER_MODE */

#if (ETH_30_TC3XX_IMPLEMENTATION_RECEIVE == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IncRxDescrRingProcPos
 **********************************************************************************************************************/
/*! \brief      Increments the processing position in a reception descriptor ring
 *  \details    -
 *  \param[in]  ctrlIdx       Identifier of the Ethernet controller
 *  \param[in]  descrRingIdx  Identifier of the reception descriptor ring
 *  \context    TASK|ISR1|ISR2
 *  \reentrant  TRUE for different reception descriptor rings
 *  \pre        -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncRxDescrRingProcPos(
  uint8 ctrlIdx,
  uint8 descrRingIdx);
#endif /* ETH_30_TC3XX_IMPLEMENTATION_RECEIVE == STD_ON */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IncTxDescRingProcPos
 **********************************************************************************************************************/
/*! \brief      Increments the processing position in a transmission descriptor ring
 *  \details    -
 *  \param[in]  ctrlIdx       Identifier of the Ethernet controller
 *  \param[in]  descrRingIdx  Identifier of the transmission descriptor ring
 *  \context    TASK|ISR1|ISR2
 *  \reentrant  TRUE for different transmission descriptor rings
 *  \pre        -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncTxDescRingProcPos(
  uint8 ctrlIdx,
  uint8 descrRingIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IncTxDescRingFreePos
 **********************************************************************************************************************/
/*! \brief      Increments the free position in a transmission descriptor ring
 *  \details    -
 *  \param[in]  ctrlIdx       Identifier of the Ethernet controller
 *  \param[in]  descrRingIdx  Identifier of the transmission descriptor ring
 *  \context    TASK|ISR1|ISR2
 *  \reentrant  TRUE for different transmission descriptor rings
 *  \pre        -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncTxDescRingFreePos(
  uint8 ctrlIdx,
  uint8 descrRingIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_SetFrameId
 **********************************************************************************************************************/
/*! \brief          Increments the frame ID and sets the new value at the end of the passed buffer
 *  \details        -
 *  \param[in]      ctrlIdx     Identifier of the Ethernet controller
 *  \param[in,out]  payloadPtr  Buffer at whichs end the new frame ID shall be stored
 *  \param[in]      payloadLen  Length of the data within the buffer after that the frame ID shall be inserted
 *  \context        TASK|ISR1|ISR2
 *  \reentrant      FALSE
 *  \pre            -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetFrameId(
        uint8                        ctrlIdx,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) payloadPtr,
        uint16                       payloadLen);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetFrameId
 **********************************************************************************************************************/
/*! \brief      Retrieves a frame ID stored at the end of the passed buffer
 *  \details    -
 *  \param[in]  payloadPtr  Buffer at whichs end the frame ID is stored
 *  \param[in]  payloadLen  Length of the data within the buffer after that the frame ID is stored
 *  \context    TASK|ISR1|ISR2
 *  \reentrant  TRUE
 *  \pre        -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_FrameIdType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetFrameId(
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) payloadPtr,
          uint16                       payloadLen);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsTxBufProvisonPossible
 **********************************************************************************************************************/
/*! \brief          Checks if transmission buffer provision can be processed
 *  \details        Function performs a pre-check if tx buffer provision is possible.
 *  \param[in]      ctrlIdx  Identifier of the Ethernet controller
 *  \param[in,out]  lenPtr   Buffer to determin the requested length and the actual needed length of the buffer:
 *                           [in]  Length of the buffer as requested by the upper layer
 *                           [out] Length of the buffer needed due to other constraints like insertion of switch
 *                                 management data by the EthSwt driver
 *  \context        TASK|ISR1|ISR2
 *  \reentrant      TRUE for different Ethernet controllers
 *  \pre            -s
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsTxBufProvisonPossible(
        uint8                         ctrlIdx,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) lenPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_PrePrepareTxFrame
 **********************************************************************************************************************/
/*! \brief          Performs a pre-prepartion of the buffer that shall be provided to the upper layer
 *  \details        -
 *  \param[in]      ctrlIdx  Identifier of the Ethernet controller
 *  \param[in]      bufIdx   Identifier of the transmission buffer segment
 *  \param[in]      frameId  Identifier of the Ethernet frame related to the buffer segment
 *  \param[in,out]  dataPtr  Buffer provided to the upper layer later on:
 *                           [in]  Pointer pointing to the Ether Type position of a IEEE conform Ethernet frame
 *                           [out] Pointer pointing to the Ether Type postion of the resulting Ethernet frame
 *                                 (adaption of position could be needed due to insertion of an additional header
 *                                  between MAC addresses and Ether Type like in a EthSwt management use case)
 *  \param[in,out]  dataLen  Length of the buffer provided to the upper layer later on:
 *                           [in]  Actual length of the buffer segment
 *                           [out] Available length of the buffer segment
 *                                 (adaption of the actual length could be needed due to instertion of an additional
 *                                  header between MAC addresses an Ether Type like in a EthSwt management use case)
 *  \context        TASK|ISR1|ISR2
 *  \reentrant      TRUE for different transmission buffer segments
 *  \pre            -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_PrePrepareTxFrame(
        uint8                         ctrlIdx,
        uint8                         bufIdx,
        Eth_FrameIdType               frameId,
  P2VAR(uint8*, AUTOMATIC, AUTOMATIC) dataPtr,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) dataLen);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsFrameTxAllowed
 **********************************************************************************************************************/
/*! \brief          Checks if triggering of transmission of a Ethernet frame is possible
 *  \details        -
 *  \param[in]      ctrlIdx  Identifier of the Ethernet controller
 *  \param[in]      bufIdx   Identifier of the transmission buffer segment
 *  \param[in]      frameId  Identifier of the Ethernet frame related to the buffer segment
 *  \param[in,out]  dataPtr  Buffer provided to the upper layer later on:
 *                           [in]  Pointer pointing to the Ether Type postion of the resulting Ethernet frame
 *                                 (position could be shifted due to insertion of an additional header
 *                                  between MAC addresses and Ether Type like in a EthSwt management use case)
 *                           [out] Pointer pointing to the Ether Type position of a IEEE conform Ethernet frame
 *  \param[in,out]  dataLen  Length of the buffer provided to the upper layer later on:
 *                           [in]  Available length of the buffer segment
 *                                 (actual length could be decreased due to instertion of an additional
 *                                  header between MAC addresses an Ether Type like in a EthSwt management use case)
 *                           [out] Actual length of the buffer segment
 *  \context        TASK|ISR1|ISR2
 *  \reentrant      TRUE for different transmission buffer segments
 *  \pre            -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsFrameTxAllowed(
        uint8                         ctrlIdx,
        uint8                         bufIdx,
        Eth_FrameIdType               frameId,
  P2VAR(uint8*, AUTOMATIC, AUTOMATIC) dataPtr,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) dataLen);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_FinishFrameTx
 **********************************************************************************************************************/
/*! \brief      Finishes the transmission triggering of a Ethernet frame
 *  \details    -
 *  \param[in]  ctrlIdx  Identifier of the Ethernet controller
 *  \param[in]  bufIdx   Identifier of the transmission buffer segment
 *  \param[in]  frameId  Identifier of the Ethernet frame related to the buffer segment
 *  \context    TASK|ISR1|ISR2
 *  \reentrant  TRUE for different transmission buffer segments
 *  \pre        -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_FinishFrameTx(
  uint8           ctrlIdx,
  uint8           bufIdx,
  Eth_FrameIdType frameId);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsFrameRxAllowed
 **********************************************************************************************************************/
/*! \brief          Checks if reception of an Ethernet frame is allowed
 *  \details        -
 *  \param[in]      ctrlIdx  Identifier of the Ethernet controller
 *  \param[in,out]  dataPtr  Buffer provided to the upper layer later on:
 *                           [in]  Pointer pointing to the Ether Type position of a IEEE conform Ethernet frame
 *                           [out] Pointer pointing to the Ether Type postion of the resulting Ethernet frame
 *                                 (adaption of position could be needed due to insertion of an additional header
 *                                  between MAC addresses and Ether Type like in a EthSwt management use case)
 *  \param[in,out]  dataLen  Length of the buffer provided to the upper layer later on:
 *                           [in]  Actual length of the Ethernet frame contained in the buffer
 *                           [out] Available length of the Ethernet frame contained in the buffer
 *                                 (adaption of the actual length of the Ethernet frame could be needed due to instertion
 *                                  of an additional header between MAC addresses an Ether Type like in a EthSwt
 *                                  management use case)
 *  \context        TASK|ISR1|ISR2
 *  \reentrant      TRUE for different reception buffer segments
 *  \pre            -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsFrameRxAllowed(
        uint8                         ctrlIdx,
  P2VAR(uint8*, AUTOMATIC, AUTOMATIC) dataPtr,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) dataLen);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_FinishFrameRx
 **********************************************************************************************************************/
/*! \brief      Finishes the reception of a Ethernet frame
 *  \details    -
 *  \param[in]  ctrlIdx  Identifier of the Ethernet controller
 *  \param[in]  bufIdx   Identifier of the transmission buffer segment
 *  \param[in]  frameId  Identifier of the Ethernet frame related to the buffer segment
 *  \context    TASK|ISR1|ISR2
 *  \reentrant  TRUE for different transmission buffer segments
 *  \pre        -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_FinishFrameRx(
        uint8                         ctrlIdx,
  P2VAR(uint8*, AUTOMATIC, AUTOMATIC) dataPtr);

#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsValidDescAndBuffAlignment
 **********************************************************************************************************************/
/*! \brief      Check if all Rx \ Tx Descriptors and Buffers fulfill minimum alignment requirements
 *  \details    -
 *  \param[out] ctrlIdx  Identifier of the Ethernet controller in case alignment is not fulfilled and return value is FALSE
 *  \context    ANY
 *  \reentrant  TRUE
 *  \pre        -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsValidDescAndBuffAlignment(
    P2VAR(uint8, ETH_30_TC3XX_APPL_VAR, ETH_30_TC3XX_APPL_VAR) ctrlIdx);
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsBroadcast
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsBroadcast(
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) macAddr)
{
  uint8_least addrIdx;
  boolean     isBroadcast = TRUE;

  /* #10 Iterate over all six bytes of a MAC address */
  for( addrIdx = 0; addrIdx < ETH_PHYS_ADDR_LEN_BYTE; addrIdx++ )
  {
    /* #100 Check whether byte is 0xFF (Broadcast) */
    if( macAddr[(uint8)addrIdx] != 0xFF )
    {
      isBroadcast = FALSE;
      break;
    }
  }
  return isBroadcast;
} /* Eth_30_Tc3xx_IsBroadcast() */

#if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsZeroAddress
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsZeroAddress(
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) macAddr)
{
  uint8_least addrIdx;
  boolean     isZeroAddress = TRUE;

  /* #10 Iterate over all six bytes of a MAC address */
  for( addrIdx = 0; addrIdx < ETH_PHYS_ADDR_LEN_BYTE; addrIdx++ )
  {
    /* #100 Check whether byte is zero */
    if( macAddr[(uint8)addrIdx] != 0x00 )
    {
      isZeroAddress = FALSE;
      break;
    }
  }
  return isZeroAddress;
} /* Eth_30_Tc3xx_IsZeroAddress() */
#endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON */

#if (ETH_30_TC3XX_IMPLEMENTATION_SET_CONTROLLER_MODE == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_InitBuffersAndDescriptors
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
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_InitBuffersAndDescriptors(
  uint8 ctrlIdx)
{
  uint8_least bufIdx;
  uint8_least descIdx;
  uint8_least descrRingIdx;

  /* #10 Loop over all Tx descriptor rings */
  for( descrRingIdx = 0U; descrRingIdx < Eth_30_Tc3xx_Cfg_GetTxDescrRingNum(ctrlIdx); descrRingIdx++ )
  {
    /* #100 Loop over all Tx descriptors in that ring */
    for( descIdx = 0U; descIdx < Eth_30_Tc3xx_Cfg_GetTxDescrNum(ctrlIdx, (uint8)descrRingIdx); descIdx++ )
    {
      /* #110 Initialize Tx descriptor */
      /*lint -e{522} */
      Eth_30_Tc3xx_LL_InitializeTxDescriptor(ctrlIdx, (uint8)descrRingIdx, (uint8)descIdx);
      Eth_30_Tc3xx_Cfg_SetTxDescrTxState(ctrlIdx, (uint8)descrRingIdx, (uint8)descIdx, ETH_30_TC3XX_DESCRIPTOR_NOT_READY);
    }

    /* #20 Set state variables for ring positions to start values */
    Eth_30_Tc3xx_Cfg_SetTxDescrRingFreePos(ctrlIdx, (uint8)descrRingIdx, 0);
    Eth_30_Tc3xx_Cfg_SetTxDescrRingProcPos(ctrlIdx, (uint8)descrRingIdx, 0);
  }

  /* #30 Loop over all Rx descriptor rings */
  for( descrRingIdx = 0U; descrRingIdx < Eth_30_Tc3xx_Cfg_GetRxDescrRingNum(ctrlIdx); descrRingIdx++ )
  {
    /* #300 Loop over all Rx descriptors in that ring */
    for( descIdx = 0; descIdx < Eth_30_Tc3xx_Cfg_GetRxDescrNum(ctrlIdx, (uint8)descrRingIdx); descIdx++ )
    {
       /* #310 Initialize Rx descriptor */
       /*lint -e{522} */
       Eth_30_Tc3xx_LL_InitializeRxDescriptor(ctrlIdx, (uint8)descrRingIdx, (uint8)descIdx);

       if (descIdx < Eth_30_Tc3xx_Cfg_GetRxBufferNum(ctrlIdx, (uint8)descrRingIdx))
       {
         Eth_30_Tc3xx_Cfg_SetRxDescrToBufferMap(ctrlIdx, (uint8)descrRingIdx, (uint8)descIdx, (uint16)descIdx);
       }
       else
       {
         Eth_30_Tc3xx_Cfg_SetRxDescrToBufferMap(ctrlIdx, (uint8)descrRingIdx, (uint8)descIdx,
                                                (uint16)ETH_30_TC3XX_RX_DESCRIPTOR_TO_BUFFER_NOT_MAPPED);
       }
    }
    Eth_30_Tc3xx_Cfg_SetRxDescrRingProcPos(ctrlIdx, (uint8)descrRingIdx, 0);
  }

  for( bufIdx = 0; bufIdx < Eth_30_Tc3xx_Cfg_GetTxBufferNum(ctrlIdx); bufIdx++ )
  {
    Eth_30_Tc3xx_Cfg_SetTxBufferBusyState(ctrlIdx, (uint8)bufIdx, ETH_30_TC3XX_BUFFER_NOT_BUSY);
    Eth_30_Tc3xx_Cfg_SetUlTxConfState(ctrlIdx, (uint8)bufIdx, ETH_30_TC3XX_TX_STATE_CONFIRMATION_NOT_PENDING);
    if( Eth_30_Tc3xx_Cfg_IsTimeSyncEnabled(ctrlIdx) == TRUE )
    {
      Eth_30_Tc3xx_Cfg_SetTxTsRequest(ctrlIdx, (uint8)bufIdx, ETH_30_TC3XX_TIMESYNC_TS_NOT_REQUESTED);
    }
  }

  /* #40 Initialize HW specific global Descriptor state variables */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_InitDescriptorStateVariables(ctrlIdx);

  /* #50 Announce descriptor lists to hardware */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_SetDescriptorBaseAddresses(ctrlIdx);
} /* Eth_30_Tc3xx_InitBuffersAndDescriptors() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_SET_CONTROLLER_MODE */

#if (ETH_30_TC3XX_IMPLEMENTATION_RECEIVE == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IncRxDescrRingProcPos
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncRxDescrRingProcPos(
  uint8 ctrlIdx,
  uint8 descrRingIdx)
{
  uint16 procPos = Eth_30_Tc3xx_Cfg_GetRxDescrRingProcPos(ctrlIdx, descrRingIdx);
  /* #10 Increment current read position in Rx descriptor ring */
  procPos++;

  /* #20 Check for wraparound */
  if(procPos >= Eth_30_Tc3xx_Cfg_GetRxDescrNum(ctrlIdx, descrRingIdx))
  {
    procPos = 0u;
  }

  Eth_30_Tc3xx_Cfg_SetRxDescrRingProcPos(ctrlIdx, descrRingIdx, procPos);
} /* Eth_30_Tc3xx_IncRxDescrRingProcPos() */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_RECEIVE == STD_ON */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IncTxDescRingProcPos
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncTxDescRingProcPos(
  uint8 ctrlIdx,
  uint8 descrRingIdx)
{
  uint8 procPos = Eth_30_Tc3xx_Cfg_GetTxDescrRingProcPos(ctrlIdx, descrRingIdx);
  /* #10 Increment current transmission position in Tx descriptor ring */
  procPos++;

  /* #20 Check for wraparound */
  if(procPos >= (Eth_30_Tc3xx_Cfg_GetTxDescrNum(ctrlIdx, descrRingIdx)))
  {
    procPos = 0u;
  }

  Eth_30_Tc3xx_Cfg_SetTxDescrRingProcPos(ctrlIdx, descrRingIdx, procPos);
} /* Eth_30_Tc3xx_IncTxDescRingProcPos() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IncTxDescRingFreePos
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncTxDescRingFreePos(
  uint8 ctrlIdx,
  uint8 descrRingIdx)
{
  uint8 freePos = Eth_30_Tc3xx_Cfg_GetTxDescrRingFreePos(ctrlIdx, descrRingIdx);
  /* #10 Increment free position in Tx descriptor ring */
  freePos++;

  /* #20 Check for wraparound */
  if(freePos >= (Eth_30_Tc3xx_Cfg_GetTxDescrNum(ctrlIdx, descrRingIdx)))
  {
    freePos = 0u;
  }

  Eth_30_Tc3xx_Cfg_SetTxDescrRingFreePos(ctrlIdx, descrRingIdx, freePos);
} /* Eth_30_Tc3xx_IncTxDescRingFreePos() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_SetFrameId
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetFrameId(
        uint8                        ctrlIdx,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) payloadPtr,
        uint16                       payloadLen)
{
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) frameIdPtr;

  Eth_30_Tc3xx_EnterExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  Eth_30_Tc3xx_CurrentFrameId[ctrlIdx]++;

  if( Eth_30_Tc3xx_CurrentFrameId[ctrlIdx] == ETH_INVALID_FRAME_ID )
  {
    Eth_30_Tc3xx_CurrentFrameId[ctrlIdx]++;
  }

  frameIdPtr = (P2VAR(uint8, AUTOMATIC, AUTOMATIC))&Eth_30_Tc3xx_CurrentFrameId[ctrlIdx]; /* PRQA S 0310 */ /* Byte access needed to avoid mis-aligned access on specific platforms. */
  payloadPtr[payloadLen + 0] = frameIdPtr[0];
  payloadPtr[payloadLen + 1] = frameIdPtr[1];

  Eth_30_Tc3xx_ExitExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */
} /* Eth_30_Tc3xx_SetFrameId() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetFrameId
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_FrameIdType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetFrameId(
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) payloadPtr,
          uint16                       payloadLen)
{
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) frameIdPtr;
        Eth_FrameIdType              frameId;

  frameIdPtr = (P2VAR(uint8, AUTOMATIC, AUTOMATIC))&frameId; /* PRQA S 0310 */ /* Byte access needed to avoid mis-aligned access on specific platforms. */
  frameIdPtr[0] = payloadPtr[payloadLen + 0];
  frameIdPtr[1] = payloadPtr[payloadLen + 1];

  return frameId;
} /* Eth_30_Tc3xx_GetFrameId() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsTxBufProvisonPossible
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsTxBufProvisonPossible(
        uint8                         ctrlIdx,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) lenPtr)
{
  boolean result = TRUE;

  if( Eth_30_Tc3xx_Cfg_IsEthSwtIfcToBeUsed(ctrlIdx) == TRUE )
  {
    if( Eth_30_Tc3xx_Cfg_GetEthSwtIfc(ctrlIdx)->EthAdaptBufferLength(lenPtr) == E_NOT_OK )
    {
      result = FALSE;
    }
  }

  return result;
} /* Eth_30_Tc3xx_IsTxBufProvisonPossible() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_PrePrepareTxFrame
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_PrePrepareTxFrame(
        uint8                         ctrlIdx,
        uint8                         bufIdx,
        Eth_FrameIdType               frameId,
  P2VAR(uint8*, AUTOMATIC, AUTOMATIC) dataPtr,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) dataLen)
{
  boolean result = TRUE;

  if( Eth_30_Tc3xx_Cfg_IsEthSwtIfcToBeUsed(ctrlIdx) == TRUE )
  {
    if( Eth_30_Tc3xx_Cfg_GetEthSwtIfc(ctrlIdx)->EthPrepareTxFrame(ctrlIdx,
                                                                 bufIdx,
                                                                 frameId,
                                                                 dataPtr,
                                                                 dataLen) == E_NOT_OK )
    {
      result = FALSE;
    }
  }

  return result;
} /* Eth_30_Tc3xx_PrePrepareTxFrame() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsFrameTxAllowed
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsFrameTxAllowed(
        uint8                         ctrlIdx,
        uint8                         bufIdx,
        Eth_FrameIdType               frameId,
  P2VAR(uint8*, AUTOMATIC, AUTOMATIC) dataPtr,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) dataLen)
{
  boolean result = TRUE;

  if( Eth_30_Tc3xx_Cfg_IsEthSwtIfcToBeUsed(ctrlIdx) == TRUE )
  {
    if( Eth_30_Tc3xx_Cfg_GetEthSwtIfc(ctrlIdx)->EthProcessTxFrame(ctrlIdx,
                                                                 bufIdx,
                                                                 frameId,
                                                                 dataPtr,
                                                                 dataLen) == E_NOT_OK )
    {
      result = FALSE;
    }
  }

  return result;
} /* Eth_30_Tc3xx_IsFrameTxAllowed() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_FinishFrameTx
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_FinishFrameTx(
  uint8           ctrlIdx,
  uint8           bufIdx,
  Eth_FrameIdType frameId)
{
  if( Eth_30_Tc3xx_Cfg_IsEthSwtIfcToBeUsed(ctrlIdx) == TRUE )
  {
    Eth_30_Tc3xx_Cfg_GetEthSwtIfc(ctrlIdx)->EthTxFinishedIndication(ctrlIdx,
                                                                   bufIdx,
                                                                   frameId);
  }
} /* Eth_30_Tc3xx_FinishFrameTx() */

#if (ETH_30_TC3XX_IMPLEMENTATION_RECEIVE == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsFrameRxAllowed
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsFrameRxAllowed(
        uint8                         ctrlIdx,
  P2VAR(uint8*, AUTOMATIC, AUTOMATIC) dataPtr,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) dataLen)
{
  boolean result = TRUE;

  if( Eth_30_Tc3xx_Cfg_IsEthSwtIfcToBeUsed(ctrlIdx) == TRUE )
  {
    boolean isMgmtFrameOnly;

    if( Eth_30_Tc3xx_Cfg_GetEthSwtIfc(ctrlIdx)->EthProcessRxFrame(ctrlIdx,
                                                                 dataPtr,
                                                                 dataLen,
                                                                 &isMgmtFrameOnly) == E_NOT_OK )
    {
      result = FALSE;
    }
    else
    {
      if( isMgmtFrameOnly == TRUE )
      {
        result = FALSE;
      }
    }

  }

  return result;
} /* Eth_30_Tc3xx_IsFrameRxAllowed() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_FinishFrameRx
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_FinishFrameRx(
        uint8                         ctrlIdx,
  P2VAR(uint8*, AUTOMATIC, AUTOMATIC) dataPtr)
{
  if( Eth_30_Tc3xx_Cfg_IsEthSwtIfcToBeUsed(ctrlIdx) == TRUE )
  {
    Eth_30_Tc3xx_Cfg_GetEthSwtIfc(ctrlIdx)->EthRxFinishedIndication(ctrlIdx,
                                                                   dataPtr);
  }
} /* Eth_30_Tc3xx_FinishFrameRx() */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_RECEIVE */

#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsValidDescAndBuffAlignment
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsValidDescAndBuffAlignment(
  P2VAR(uint8, ETH_30_TC3XX_APPL_VAR, ETH_30_TC3XX_APPL_VAR) ctrlIdx)
{
  uint8_least cIdx;
  boolean result = TRUE;

  /* Loop over all controllers */
  for(cIdx = 0; cIdx < ETH_30_TC3XX_MAX_CTRLS_TOTAL; cIdx++)
  {
    uint8_least ringIdx;

    for(ringIdx = 0; ringIdx < (uint8_least)Eth_30_Tc3xx_Cfg_GetRxDescrRingNum((uint8)cIdx); ringIdx++)
    {
      /* PRQA S 0303 1 */ /* MD_Eth_30_Tc3xx_0303 */
      uint32 rxDescAlignProve = ((uint32)Eth_30_Tc3xx_Cfg_GetRxDescr((uint8)cIdx, (uint8)ringIdx, 0) %
                                 (uint32)ETH_30_TC3XX_LL_DESC_ALIGN_BYTE);
      /* PRQA S 0306 1 */ /* MD_Eth_30_Tc3xx_0306 */
      uint32 rxBufAlignProve  = ((uint32)Eth_30_Tc3xx_Cfg_GetRxBuffer((uint8)cIdx, (uint8)ringIdx) %
                                 (uint32)ETH_30_TC3XX_LL_BUFF_ALIGN_BYTE);

      if( (rxDescAlignProve != 0u) ||
          (rxBufAlignProve  != 0u) )
      {
        result = FALSE;
        break;
      }
    }

    for(ringIdx = 0; ringIdx < Eth_30_Tc3xx_Cfg_GetTxDescrRingNum((uint8)cIdx); ringIdx++)
    {
      /* PRQA S 0303 1 */ /* MD_Eth_30_Tc3xx_0303 */
      uint32 txDescAlignProve = (((uint32)Eth_30_Tc3xx_Cfg_GetTxDescr((uint8)cIdx, (uint8)ringIdx, 0)) %
                                  (uint32)ETH_30_TC3XX_LL_DESC_ALIGN_BYTE);
      /* PRQA S 0306 1 */ /* MD_Eth_30_Tc3xx_0306 */
      uint32 txBufAlignProve  = ((uint32)Eth_30_Tc3xx_Cfg_GetTxBuffer((uint8)cIdx) %
                                 (uint32)ETH_30_TC3XX_LL_BUFF_ALIGN_BYTE);

      if( (txDescAlignProve != 0u) ||
          (txBufAlignProve  != 0u) )
      {
        result = FALSE;
        break;
      }
    }
  }

  if (result == FALSE)
  {
    *ctrlIdx = (uint8)cIdx;
  }

  return result;
} /* Eth_30_Tc3xx_IsValidDescAndBuffAlignment() */
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/
#if (ETH_30_TC3XX_IMPLEMENTATION_INIT_MEMORY == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_InitMemory
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_InitMemory( void )
{
# if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
  {
    /* #10 Initialize state variables for DET checks */
    Eth_30_Tc3xx_ModuleInitialized = ETH_STATE_UNINIT;
  }
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
} /* Eth_30_Tc3xx_InitMemory() */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_INIT_MEMORY == STD_ON */

#if (ETH_30_TC3XX_IMPLEMENTATION_INIT == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Init
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
/* PRQA S 3206 3 */ /* MD_Eth_30_Tc3xx_3206 */
FUNC(void, ETH_30_TC3XX_CODE)Eth_30_Tc3xx_Init(
  P2CONST(Eth_ConfigType, ETH_30_TC3XX_CONST, ETH_30_TC3XX_CONST) CfgPtr)
{
  uint8_least ctrlIdx;
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  uint8 ctrlIdxNoValidAlignment = ETH_30_TC3XX_MAX_CTRLS_TOTAL;
  /* Check validity of descriptor and buffer alignment */
  if(Eth_30_Tc3xx_IsValidDescAndBuffAlignment(&ctrlIdxNoValidAlignment) == FALSE)
  {
    errorId = ETH_30_TC3XX_E_INV_ALIGNMENT;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON */
  {
    /* #Loop over all available controllers */
    for(ctrlIdx = 0; ctrlIdx < ETH_30_TC3XX_MAX_CTRLS_TOTAL; ctrlIdx++)
    {
# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
      /* #100 Initialize state variables for DET checks */
      Eth_30_Tc3xx_ModuleInitialized = ETH_STATE_INIT;
      Eth_30_Tc3xx_CtrlMode[ctrlIdx] = ETH_MODE_DOWN;
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

      /* #110 Copy physical address from ROM to RAM variable */
      Eth_30_Tc3xx_Cfg_SetActiveMacAddr((uint8)ctrlIdx, Eth_30_Tc3xx_Cfg_GetPreConfiguredMacAddr((uint8)ctrlIdx));

      /* #120 Copy register base address from ROM to RAM variable */
      Eth_30_Tc3xx_Cfg_SetRegBaseAddr((uint8)ctrlIdx, Eth_30_Tc3xx_Cfg_GetPreConfiguredRegBaseAddr((uint8)ctrlIdx));

      /* #20 Enable Mii Access so that Transceiver can be initialized during VSwitchInit */
      /*lint -e{522} */
      Eth_30_Tc3xx_LL_EnableMiiAccess((uint8)ctrlIdx);
    }
  }

  ETH_30_TC3XX_DUMMY_STATEMENT_CONST(CfgPtr); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e!438 */

  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    if (ctrlIdxNoValidAlignment < ETH_30_TC3XX_MAX_CTRLS_TOTAL)
    {
      ctrlIdxNoValidAlignment = Eth_30_Tc3xx_TransformToGlobalCtrlIdx(ctrlIdxNoValidAlignment);
    }
    (void)Det_ReportError(ETH_MODULE_ID, ctrlIdxNoValidAlignment, ETH_30_TC3XX_SID_CONTROLLER_INIT, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e!438 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON */
} /* Eth_30_Tc3xx_Init() */
#endif /* ETH_30_TC3XX_CORE_IMPLEMENTATION_INIT == STD_ON */

#if (ETH_30_TC3XX_IMPLEMENTATION_CONTROLLER_INIT == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_ControllerInit
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
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ControllerInit(
  uint8 CtrlIdx,
  uint8 CfgIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 u8Idx;
  /* PRQA S 3197 1 */ /* MD_Eth_30_Tc3xx_3197 */
  Std_ReturnType retVal = E_OK;
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;

  ETH_30_TC3XX_DUMMY_STATEMENT(CfgIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* ----- Development Error Checks ------------------------------------- */
  CtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);

# if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of input parameters */
  if(CtrlIdx >= ETH_30_TC3XX_MAX_CTRLS_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if(Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if(CfgIdx > ETH_30_TC3XX_MAX_CFGS_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_CONFIG;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON */
  {
    uint16 hwLoopTimeout = 0;

    /* ----- Implementation ----------------------------------------------- */
    /* trigger start of runtime measurement */
    Eth_30_Tc3xx_Rtm_Start(ControllerInit);

# if (ETH_30_TC3XX_ENABLE_PRE_CTRLINIT_CALL == STD_ON)
    Eth_30_Tc3xx_PreControllerInitCallout(CtrlIdx);
# endif /* ETH_30_TC3XX_ENABLE_PRE_CTRLINIT_CALL */

    /* #20 Hardware configuration which needs to be done before MAC reset */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_PreResetMac(CtrlIdx);

    /* #30 do a soft reset if necessary */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_ResetMac(CtrlIdx);

    /* #40 wait for the reset to be finished */
    /*lint -e{522} */
    while( Eth_30_Tc3xx_LL_IsResetMacFinished(CtrlIdx) == FALSE )
    {
      /* still busy */
      if( hwLoopTimeout >  Eth_30_Tc3xx_ResetLoopCycles[CtrlIdx] )
      {
        ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(CtrlIdx);
        retVal = E_NOT_OK;
        break;
      }
      hwLoopTimeout++;
    }

    if( retVal == E_OK )
    {
# if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
      Eth_30_Tc3xx_CtrlMode[CtrlIdx] = ETH_MODE_DOWN;
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

      /* #400 configure registers */
      for( u8Idx = 0; u8Idx < Eth_30_Tc3xx_Cfg_GetRegNum(CtrlIdx); u8Idx++ )
      {
        if (Eth_30_Tc3xx_Cfg_GetRegProtectedAccess(CtrlIdx, u8Idx) == TRUE)
        {
          Eth_30_Tc3xx_Reg_Write_Protected(CtrlIdx, Eth_30_Tc3xx_Cfg_GetRegOffset(CtrlIdx, u8Idx),
                                                    Eth_30_Tc3xx_Cfg_GetRegValue(CtrlIdx, u8Idx));
        }
        else
        {
          Eth_30_Tc3xx_Reg_Write(CtrlIdx, Eth_30_Tc3xx_Cfg_GetRegOffset(CtrlIdx, u8Idx),
                                          Eth_30_Tc3xx_Cfg_GetRegValue(CtrlIdx, u8Idx));
        }
      }

      Eth_30_Tc3xx_CurrentFrameId[CtrlIdx] = 1u;

      /* #410 Reset Pending Interrupt events */
      Eth_30_Tc3xx_PendingTxEvents[CtrlIdx] = 0;
      Eth_30_Tc3xx_PendingRxEvents[CtrlIdx] = 0;

      /* #420 Initialize all buffers and descriptors */
      Eth_30_Tc3xx_InitBuffersAndDescriptors(CtrlIdx);

      /* #430 Write mac address to MAC registers */
      /*lint -e{522} */
      Eth_30_Tc3xx_LL_WriteMacAddressToRegister(CtrlIdx, Eth_30_Tc3xx_Cfg_GetActiveMacAddr(CtrlIdx));

      /* #440 Reset frame counters */
      /*lint -e{522} */
      Eth_30_Tc3xx_LL_ResetCounters(CtrlIdx);

      /* #450 Initialize TimeSync support */
#if (ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON )
      if( Eth_30_Tc3xx_Cfg_IsTimeSyncEnabled(CtrlIdx) == TRUE )
      {
        Eth_30_Tc3xx_Cfg_SetRxTsContextStackPos(CtrlIdx, ETH_30_TC3XX_RX_TS_CONTEXT_STACK_EMPTY_POS);
        retVal |= Eth_30_Tc3xx_TimeSync_Init(CtrlIdx);
      }
#endif /* ETH_30_TC3XX_ENABLE_TIMESYNC */

# if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
      /* #460 reset data all structures for mac address filtering */
      for( u8Idx = 0; u8Idx < ETH_30_TC3XX_MULTICAST_BUCKET_COUNTERS; u8Idx++ )
      {
        Eth_30_Tc3xx_MulticastBucketCounters[CtrlIdx][u8Idx] = 0;
      }
      Eth_30_Tc3xx_PromiscuousModeCounter[CtrlIdx] = 0;
# endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */
    }

# if (ETH_30_TC3XX_ENABLE_POST_CTRLINIT_CALL == STD_ON)
    Eth_30_Tc3xx_PostControllerInitCallout(CtrlIdx);
# endif /* ETH_30_TC3XX_ENABLE_PRE_CTRLINIT_CALL */

    /* trigger stop of runtime measurement */
    Eth_30_Tc3xx_Rtm_Stop(ControllerInit);
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx), ETH_30_TC3XX_SID_CONTROLLER_INIT, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e!438 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_CONTROLLER_INIT == STD_ON */

#if (ETH_30_TC3XX_IMPLEMENTATION_SET_CONTROLLER_MODE == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_SetControllerMode
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
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetControllerMode(
  uint8        CtrlIdx,
  Eth_ModeType CtrlMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  CtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);
  
# if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
  retVal = E_NOT_OK;

  /* #10 Check plausibility of input parameters */
  if(CtrlIdx >= ETH_30_TC3XX_MAX_CTRLS_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if(Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #100 Decide whether the controller has to be switched to Active or Down */

    /* #200 Controller should be activated */
    if( CtrlMode == ETH_MODE_ACTIVE )
    {
      /* #2000 enable MAC */
      /*lint -e{522} */
      Eth_30_Tc3xx_LL_EnableMac(CtrlIdx);

      /*lint -e{522} */
      if( Eth_30_Tc3xx_LL_IsMacEnabled(CtrlIdx) == FALSE)
      {
        /* #2010 error handling in case enabling the MAC failed */
        ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(CtrlIdx);
        retVal = E_NOT_OK;
      }
      else
      {
        retVal = E_OK;
      }

      if( Eth_30_Tc3xx_Cfg_IsTimeSyncEnabled(CtrlIdx) == TRUE )
      {
        /* #2100 Start the time synchronization clock */
        /*lint -e{522} */
        Eth_30_Tc3xx_LL_StartTimesyncClock(CtrlIdx);
      }
    }
    /* #300 Controller should be shut down */
    else
    {
      /* #3000 disable MAC */
      /*lint -e{522} */
      Eth_30_Tc3xx_LL_DisableMac(CtrlIdx);
      
      /*lint -e{522} */
      if( Eth_30_Tc3xx_LL_IsMacEnabled(CtrlIdx) == TRUE )
      {
        /* #3010 error handling in case disabling the MAC failed */
        ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(CtrlIdx);
        retVal = E_NOT_OK;
      }
      else
      {
        retVal = E_OK;
      }
    }
# if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
    if( retVal == E_OK )
    {
      Eth_30_Tc3xx_CtrlMode[CtrlIdx] = CtrlMode;
    }
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx), ETH_30_TC3XX_SID_SET_CONTROLLER_MODE, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e!438 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON */
  return retVal;
} /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_SET_CONTROLLER_MODE == STD_ON */

#if (ETH_30_TC3XX_IMPLEMENTATION_GET_CONTROLLER_MODE == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetControllerMode
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetControllerMode(
        uint8                               CtrlIdx,
  P2VAR(Eth_ModeType, AUTOMATIC, AUTOMATIC) CtrlModePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  CtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);
  
# if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
  retVal = E_NOT_OK;

  /* #10 Check plausibility of input parameters */
  if(CtrlIdx >= ETH_30_TC3XX_MAX_CTRLS_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if(Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if(CtrlModePtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON */
  /* ----- Implementation ----------------------------------------------- */
  {
    /* #100 read controller mode from HW register */
    /*lint -e{522} */
    if (Eth_30_Tc3xx_LL_IsMacEnabled(CtrlIdx) == TRUE)
    {
      /* #1000 Report mode as active */
      (*CtrlModePtr) = ETH_MODE_ACTIVE;
    }
    else
    {
      /* #1010 Report mode as down */
      (*CtrlModePtr) = ETH_MODE_DOWN;
    }
    retVal = E_OK;
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx), ETH_30_TC3XX_SID_GET_CONTROLLER_MODE, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e!438 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON */
  return retVal;
}
#endif /* ETH_30_TC3XX_IMPLEMENTATION_GET_CONTROLLER_MODE == STD_ON */

#if (ETH_30_TC3XX_IMPLEMENTATION_GET_PHYS_ADDR == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetPhysAddr
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetPhysAddr(
        uint8                        CtrlIdx,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) PhysAddrPtr)

{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;

   /* ----- Development Error Checks ------------------------------------- */
  CtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);

# if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of input parameters */
  if(CtrlIdx >= ETH_30_TC3XX_MAX_CTRLS_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if(Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if(PhysAddrPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON */
  /* ----- Implementation ----------------------------------------------- */
  {
    /* #100 MAC address read from configuration */
    Eth_30_Tc3xx_Cfg_InsertActiveMacAddr(CtrlIdx, PhysAddrPtr);
  }
/* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx), ETH_30_TC3XX_SID_GET_PHYS_ADDR, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e!438 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON */
} /* Eth_30_Tc3xx_GetPhysAddr() */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_GET_PHYS_ADDR == STD_ON */

#if (ETH_30_TC3XX_IMPLEMENTATION_SET_PHYS_ADDR == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_SetPhysAddr
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC (void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetPhysAddr(
          uint8                        CtrlIdx,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) PhysAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  CtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);
  
# if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of input parameters */
  if(CtrlIdx >= ETH_30_TC3XX_MAX_CTRLS_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if(Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if(PhysAddrPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #100 Set Physical Address RAM variables */
    Eth_30_Tc3xx_Cfg_SetActiveMacAddr(CtrlIdx, PhysAddrPtr);

    /* #110 Write mac address to registers */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_WriteMacAddressToRegister(CtrlIdx, PhysAddrPtr);

# if (ETH_30_TC3XX_ENABLE_MAC_WRITE_ACCESS == STD_ON)
    {
      /* #1110 Write to NVM if configured */
      uint8 status = NVM_REQ_PENDING;

      (void)NvM_GetErrorStatus(Eth_30_Tc3xx_Cfg_GetMacAddressBlockId(CtrlIdx), &status);

      if(status != NVM_REQ_PENDING)
      {
        /* set block Status to true */
        (void)NvM_SetRamBlockStatus(Eth_30_Tc3xx_Cfg_GetMacAddressBlockId(CtrlIdx), TRUE);
      }
    }
# endif /* ETH_30_TC3XX_ENABLE_MAC_WRITE_ACCESS */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx), ETH_30_TC3XX_SID_SET_PHYS_ADDR, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e!438 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON */
} /* Eth_30_Tc3xx_SetPhysAddr() */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_SET_PHYS_ADDR == STD_ON */

#if (ETH_30_TC3XX_IMPLEMENTATION_UPDATE_PHYS_ADDR_FILTER == STD_ON)
# if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_UpdatePhysAddrFilter
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC (Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_UpdatePhysAddrFilter(
          uint8                        CtrlIdx,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) PhysAddrPtr,
          Eth_FilterActionType         Action)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  CtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);
  
# if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of input parameters */
  if(CtrlIdx >= ETH_30_TC3XX_MAX_CTRLS_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if(Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if(PhysAddrPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* Do HW specific filter mode settings for hash filtering */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_SetMulticastFilteringMode(CtrlIdx);

    Eth_30_Tc3xx_EnterExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #100 Check whether a special address defined by AUTOSAR is passed as parameter */
    if(Eth_30_Tc3xx_IsBroadcast(PhysAddrPtr) == TRUE)
    {
      /* #1000 Broadcast address is passed: Promiscuous mode should be influenced */
      if(Action == ETH_ADD_TO_FILTER)
      {
        if(Eth_30_Tc3xx_PromiscuousModeCounter[CtrlIdx] < ETH_30_TC3XX_UINT8_MAX)
        {
          Eth_30_Tc3xx_PromiscuousModeCounter[CtrlIdx]++;
          retVal = E_OK;

          if(Eth_30_Tc3xx_PromiscuousModeCounter[CtrlIdx] == 1)
          {
            /* Set promiscuous mode */
            /*lint -e{522} */
            Eth_30_Tc3xx_LL_EnablePromiscuousMode(CtrlIdx);
          }
        }
        else
        {
          /* Too much activations of promiscuous mode */
        }
      }
      else /* ETH_30_TC3XX_REMOVE_FROM_FILTER */
      {
        if(Eth_30_Tc3xx_PromiscuousModeCounter[CtrlIdx] > 0)
        {
          Eth_30_Tc3xx_PromiscuousModeCounter[CtrlIdx]--;
          retVal = E_OK;

          if(Eth_30_Tc3xx_PromiscuousModeCounter[CtrlIdx] == 0)
          {
            /* Unset promiscuous mode */
            /*lint -e{522} */
            Eth_30_Tc3xx_LL_DisablePromiscuousMode(CtrlIdx);
          }
        }
        else
        {
          /* Tried to stop promiscuous mode, although it was not activated */
        }
      }
    }
    else if (Eth_30_Tc3xx_IsZeroAddress(PhysAddrPtr) == TRUE)
    {
      /* #1100 All zero address is passed: All adapted filters will be closed */
      uint8_least bucketPos;
      /* Unset promiscuous mode */
      /*lint -e{522} */
      Eth_30_Tc3xx_LL_DisablePromiscuousMode(CtrlIdx);

      /* Close all multicast filters */
      /*lint -e{522} */
      Eth_30_Tc3xx_LL_CloseAllMulticastFilters(CtrlIdx);

      /* set all filter buckets to zero */
      for(bucketPos = 0; bucketPos < ETH_30_TC3XX_MULTICAST_BUCKET_COUNTERS; bucketPos++)
      {
        Eth_30_Tc3xx_MulticastBucketCounters[CtrlIdx][bucketPos] = 0;
      }

      /* set no promiscuous mode requested */
      Eth_30_Tc3xx_PromiscuousModeCounter[CtrlIdx] = 0;

      retVal = E_OK;
    }
    else
    {
      /* #1200 a mac address without special function defined by AUTOSAR should be manipulated */
      uint32 bucketMask;
      boolean isUpperReg;
      uint8 hash;

      /*lint -e{522} */
      Eth_30_Tc3xx_LL_CalculateMulticastFilterRegisterHash(CtrlIdx, PhysAddrPtr, &hash, &isUpperReg, &bucketMask);

      if(ETH_ADD_TO_FILTER == Action)
      {
        if (Eth_30_Tc3xx_MulticastBucketCounters[CtrlIdx][hash] < ETH_30_TC3XX_BUCKET_MAX_CNT)
        {
          Eth_30_Tc3xx_MulticastBucketCounters[CtrlIdx][hash]++;
          retVal = E_OK;
        }

        if(Eth_30_Tc3xx_MulticastBucketCounters[CtrlIdx][hash] == 1)
        {
          if(isUpperReg == TRUE)
          {
            /*lint -e{522} */
            Eth_30_Tc3xx_LL_SetUpperMulticastFilterBucketRegister(CtrlIdx, bucketMask);
          }
          else
          {
            /*lint -e{522} */
            Eth_30_Tc3xx_LL_SetLowerMulticastFilterBucketRegister(CtrlIdx, bucketMask);
          }
          retVal = E_OK;
        }
      }
      else /* ETH_30_TC3XX_REMOVE_FROM_FILTER */
      {
        if(Eth_30_Tc3xx_MulticastBucketCounters[CtrlIdx][hash] > 0)
        {
          Eth_30_Tc3xx_MulticastBucketCounters[CtrlIdx][hash]--;

          /* #1300 Set calculated filter bit in ctrl register */
          if(Eth_30_Tc3xx_MulticastBucketCounters[CtrlIdx][hash] == 0)
          {
            if(TRUE == isUpperReg)
            {
              /*lint -e{522} */
              Eth_30_Tc3xx_LL_ResetUpperMulticastFilterBucketRegister(CtrlIdx, bucketMask);
            }
            else
            {
              /*lint -e{522} */
              Eth_30_Tc3xx_LL_ResetLowerMulticastFilterBucketRegister(CtrlIdx, bucketMask);
            }
          }
          retVal = E_OK;
        }
      }
    }
    Eth_30_Tc3xx_ExitExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx), ETH_30_TC3XX_SID_UPDATE_PHYS_ADDR_FILTER, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e!438 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON */
  return retVal;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
# endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_UPDATE_PHYS_ADDR_FILTER == STD_ON */

#if (ETH_30_TC3XX_IMPLEMENTATION_WRITE_MII == STD_ON)
# if ( ETH_30_TC3XX_MII_INTERFACE == STD_ON )
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_WriteMii
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Eth_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_WriteMii(
  uint8  CtrlIdx,
  uint8  TrcvIdx,
  uint8  RegIdx,
  uint16 RegVal)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  Eth_ReturnType retVal = ETH_E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
  CtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);
  
#  if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of input parameters */
  if(CtrlIdx >= ETH_30_TC3XX_MAX_CTRLS_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if(Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if(RegIdx >= ETH_30_TC3XX_MAX_MII_REG_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_PARAM;
  }
  else
#  endif /* ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON */
  {
    uint16 hwLoopTimeout = 0;

    /* ----- Implementation ----------------------------------------------- */
    Eth_30_Tc3xx_EnterExclusiveArea(MII); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #110 Write register value to MII */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_WriteMiiTrigger(CtrlIdx, TrcvIdx, RegIdx, RegVal);

    /* #120 wait for MII operation to finish */
    /*lint -e{522} */
    while ( Eth_30_Tc3xx_LL_IsMiiOperationPending(CtrlIdx) == TRUE )
    {
      /* still busy */
      if (hwLoopTimeout > Eth_30_Tc3xx_MiiLoopCycles[CtrlIdx])
      {
        ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(CtrlIdx);
        retVal = ETH_E_NO_ACCESS;
        break;
      }
      hwLoopTimeout++;
    }

    if( hwLoopTimeout <= Eth_30_Tc3xx_MiiLoopCycles[CtrlIdx] )
    {
      retVal = ETH_OK;
    }

    Eth_30_Tc3xx_ExitExclusiveArea(MII); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
  /* ----- Development Error Report --------------------------------------- */
#  if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
   (void)Det_ReportError(ETH_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx), ETH_30_TC3XX_SID_WRITE_MII, errorId);
  }
#  else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e!438 */
#  endif /* ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON */

  return retVal;
}/* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif /* ( ETH_30_TC3XX_MII_INTERFACE == STD_ON ) */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_WRITE_MII == STD_ON */

#if (ETH_30_TC3XX_IMPLEMENTATION_READ_MII == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_ReadMii
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
# if ( ETH_30_TC3XX_MII_INTERFACE == STD_ON )
FUNC(Eth_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ReadMii(
        uint8                         CtrlIdx,
        uint8                         TrcvIdx,
        uint8                         RegIdx,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) RegValPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  Eth_ReturnType retVal = ETH_E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
  CtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);
  
#  if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of input parameters */
  if(CtrlIdx >= ETH_30_TC3XX_MAX_CTRLS_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if(Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if(RegIdx > ETH_30_TC3XX_MAX_MII_REG_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_PARAM;
  }
  else if(RegValPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
#  endif /* ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON */
  {
    uint16 hwLoopTimeout = 0;

    /* ----- Implementation ----------------------------------------------- */
    Eth_30_Tc3xx_EnterExclusiveArea(MII); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #100 read MII */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_ReadMiiTrigger(CtrlIdx, TrcvIdx, RegIdx);

    /* #110 wait for MII operation to finish */
    /*lint -e{522} */
    while ( Eth_30_Tc3xx_LL_IsMiiOperationPending(CtrlIdx) == TRUE )
    {
      if (hwLoopTimeout > Eth_30_Tc3xx_MiiLoopCycles[CtrlIdx])
      {
        ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(CtrlIdx);
        retVal = ETH_E_NO_ACCESS;
        break;
      }
      hwLoopTimeout++;
    }

    if( hwLoopTimeout <= Eth_30_Tc3xx_MiiLoopCycles[CtrlIdx] )
    {
      /*lint -e{522} */
      Eth_30_Tc3xx_LL_GetReadMiiResult(CtrlIdx, RegValPtr);
      retVal = ETH_OK;
    }

    Eth_30_Tc3xx_ExitExclusiveArea(MII); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
  /* ----- Development Error Report --------------------------------------- */
#  if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
   (void)Det_ReportError(ETH_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx), ETH_30_TC3XX_SID_READ_MII, errorId);
  }
#  else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e!438 */
#  endif /* ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON */

  return retVal;
}/* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
# endif /* ( ETH_30_TC3XX_MII_INTERFACE == STD_ON ) */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_READ_MII == STD_ON */

#if (ETH_30_TC3XX_IMPLEMENTATION_GET_COUNTER_STATE == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetCounterState
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetCounterState(
        uint8                         CtrlIdx,
        uint16                        CtrOffs,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) CtrValPtr)
{

  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
  CtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);
  
# if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of input parameters */
  if(CtrlIdx >= ETH_30_TC3XX_MAX_CTRLS_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if(Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if(CtrValPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #100 Check number of counter to read for validity */
    /*lint -e{522} */
    if( Eth_30_Tc3xx_LL_GetMaxCounterOffset(CtrlIdx) >= CtrOffs )
    {
      /* #1000 Read counter */
      /*lint -e{522} */
      retVal = Eth_30_Tc3xx_LL_GetCounterValue(CtrlIdx, CtrOffs, CtrValPtr);
    }
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
   (void)Det_ReportError(ETH_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx), ETH_30_TC3XX_SID_GET_COUNTER_STATE, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e!438 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON */

  return retVal;
}
#endif /* ETH_30_TC3XX_IMPLEMENTATION_GET_COUNTER_STATE == STD_ON */

#if (ETH_30_TC3XX_IMPLEMENTATION_PROVIDE_TX_BUFFER == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_ProvideTxBuffer
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
FUNC(BufReq_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ProvideTxBuffer(
        uint8                                CtrlIdx,
  P2VAR(uint8,        AUTOMATIC, AUTOMATIC)  BufIdxPtr,
  P2VAR(Eth_DataType, AUTOMATIC, AUTOMATIC) *BufPtr,
  P2VAR(uint16,       AUTOMATIC, AUTOMATIC)  LenBytePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
  CtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);
  
# if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of input parameters */
  if(CtrlIdx >= ETH_30_TC3XX_MAX_CTRLS_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if(Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if(Eth_30_Tc3xx_CtrlMode[CtrlIdx] == ETH_MODE_DOWN)
  {
    errorId = ETH_30_TC3XX_E_INV_MODE;
  }
  else if(BufIdxPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else if(BufPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else if(LenBytePtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON */
  {
    if( Eth_30_Tc3xx_IsTxBufProvisonPossible(CtrlIdx, LenBytePtr) == TRUE )
    {
      Eth_30_Tc3xx_EnterExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

      /* #100 Check requested buffer for valid size */
      if(Eth_30_Tc3xx_Cfg_GetMaxTxBufferLen(CtrlIdx) < ((*LenBytePtr) + ETH_30_TC3XX_HDR_LEN_BYTE + ETH_30_TC3XX_USED_FCS_LEN_BYTE))
      {
        retVal = BUFREQ_E_OVFL;
      }
      else
      {
        uint8_least txBufferBusyIdx;

        /* #1000 Find find first buffer which is big enough, if available, by iterating over all transmission buffers */
        for( txBufferBusyIdx = 0; txBufferBusyIdx < Eth_30_Tc3xx_Cfg_GetTxBufferNum(CtrlIdx); txBufferBusyIdx++ )
        {
          /* PRQA S 3415 2 */ /* MD_Eth_30_Tc3xx_3415 */
          if( (Eth_30_Tc3xx_Cfg_GetTxBufferBusyState(CtrlIdx, (uint8)txBufferBusyIdx) == ETH_30_TC3XX_BUFFER_NOT_BUSY)                &&
              (Eth_30_Tc3xx_Cfg_GetTxBufferLen(CtrlIdx, (uint8)txBufferBusyIdx)       >= ((*LenBytePtr) + ETH_30_TC3XX_HDR_LEN_BYTE + ETH_30_TC3XX_USED_FCS_LEN_BYTE))    )
          {
            break;
          }
        }

        /* #2000 Check whether a matching buffer could be found */
        if(txBufferBusyIdx < Eth_30_Tc3xx_Cfg_GetTxBufferNum(CtrlIdx))
        {
          uint32 bufOffset = Eth_30_Tc3xx_Cfg_GetTxBufferStart(CtrlIdx, (uint8)txBufferBusyIdx) + ETH_30_TC3XX_DEST_SRC_MACS_LEN_BYTE;

          (*BufPtr)     = (P2VAR(Eth_DataType, AUTOMATIC, AUTOMATIC))&Eth_30_Tc3xx_Cfg_GetTxBuffer(CtrlIdx)[bufOffset]; /* PRQA S 3305, 0310 */ /* MD_Eth_30_Tc3xx_3305, MD_Eth_30_Tc3xx_0310 */
          (*BufIdxPtr)  = (uint8)txBufferBusyIdx;
          (*LenBytePtr) = (uint16)(Eth_30_Tc3xx_Cfg_GetTxBufferLen(CtrlIdx, (uint8)txBufferBusyIdx) - (ETH_30_TC3XX_DEST_SRC_MACS_LEN_BYTE + ETH_30_TC3XX_USED_FCS_LEN_BYTE));
          Eth_30_Tc3xx_SetFrameId(CtrlIdx, &((P2VAR(uint8, AUTOMATIC, AUTOMATIC))(*BufPtr))[ETH_30_TC3XX_FRAME_TYPE_LEN_BYTE], (uint16)((*LenBytePtr) - ETH_30_TC3XX_FRAME_TYPE_LEN_BYTE)); /* PRQA S 0310 */ /* MD_Eth_30_Tc3xx_0310 */

          if( Eth_30_Tc3xx_PrePrepareTxFrame(CtrlIdx,
                                            (uint8)txBufferBusyIdx,
                                            Eth_30_Tc3xx_GetFrameId(&((P2VAR(uint8, AUTOMATIC, AUTOMATIC))(*BufPtr))[ETH_30_TC3XX_FRAME_TYPE_LEN_BYTE], (uint16)((*LenBytePtr) - ETH_30_TC3XX_FRAME_TYPE_LEN_BYTE)), /* PRQA S 0310 */ /* MD_Eth_30_Tc3xx_0310 */
                                            (P2VAR(uint8*, AUTOMATIC, AUTOMATIC))BufPtr, /* PRQA S 0310 */ /* MD_Eth_30_Tc3xx_0310 */
                                            LenBytePtr) == TRUE )
          {
            /* #2010 Lock buffer and return BufferIdx, payload and length pointer in case of success */
            Eth_30_Tc3xx_Cfg_SetTxBufferBusyState(CtrlIdx, (uint8)txBufferBusyIdx, ETH_30_TC3XX_BUFFER_BUSY);

            if( Eth_30_Tc3xx_Cfg_IsTimeSyncEnabled(CtrlIdx) == TRUE ) /* PRQA S 0715 */ /* MD_MSR_1.1_715 */
            {
              Eth_30_Tc3xx_Cfg_SetTxTsRequest(CtrlIdx, (uint8)txBufferBusyIdx, ETH_30_TC3XX_TIMESYNC_TS_NOT_REQUESTED);
            }
            (*LenBytePtr) -= ETH_30_TC3XX_FRAME_TYPE_LEN_BYTE;
            (*BufPtr) = (P2VAR(Eth_DataType, AUTOMATIC, AUTOMATIC)) &((P2VAR(uint8, AUTOMATIC, AUTOMATIC))(*BufPtr))[ETH_30_TC3XX_FRAME_TYPE_LEN_BYTE]; /* PRQA S 3305, 0310 */ /* MD_Eth_30_Tc3xx_3305, MD_Eth_30_Tc3xx_0310 */
            retVal    = BUFREQ_OK;
          }
        }
        else
        {
          /* #2020 Return BUFREQ_E_BUSY for the case, that no matching buffer could be found */
          retVal = BUFREQ_E_BUSY;
        }
      }

      Eth_30_Tc3xx_ExitExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    }
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx), ETH_30_TC3XX_SID_PROVIDE_TX_BUFFER, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e!438 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON */

  return retVal;
}/* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_PROVIDE_TX_BUFFER == STD_ON */

#if (ETH_30_TC3XX_IMPLEMENTATION_TRANSMIT == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Transmit
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Transmit(
          uint8                        CtrlIdx,
          uint8                        BufIdx,
          Eth_FrameType                FrameType,
          boolean                      TxConfirmation,
          uint16                       LenByte,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) PhysAddrPtr)
{
  /* #10 Call Eth_30_Tc3xx_VTransmit() function with the ECUs own source MAC address as PhysAddrPtrSrc parameter */
  /* no transformation between local and global controller index necessary */
  return Eth_30_Tc3xx_VTransmit(CtrlIdx,
                       BufIdx,
                       FrameType,
                       TxConfirmation,
                       LenByte,
                       PhysAddrPtr,
                       Eth_30_Tc3xx_Cfg_GetActiveMacAddr(CtrlIdx));
} /* PRQA S 6060 */ /* MD_MSR_STPAR */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_TRANSMIT == STD_ON */

#if (ETH_30_TC3XX_IMPLEMENTATION_VTRANSMIT == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_VTransmit
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
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_VTransmit(
          uint8                        CtrlIdx,
          uint8                        BufIdx,
          Eth_FrameType                FrameType,
          boolean                      TxConfirmation,
          uint16                       LenByte,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) PhysAddrPtrDst,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) PhysAddrPtrSrc)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
  CtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);
  
# if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check parameters for plausibility */
  if(CtrlIdx >= ETH_30_TC3XX_MAX_CTRLS_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if(Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if(Eth_30_Tc3xx_CtrlMode[CtrlIdx] == ETH_MODE_DOWN)
  {
    errorId = ETH_30_TC3XX_E_INV_MODE;
  }
  else if(BufIdx >= Eth_30_Tc3xx_Cfg_GetTxBufferNum(CtrlIdx))
  {
    errorId = ETH_30_TC3XX_E_INV_PARAM;
  }
  else if(LenByte > (Eth_30_Tc3xx_Cfg_GetTxBufferLen(CtrlIdx, BufIdx) - (ETH_30_TC3XX_HDR_LEN_BYTE + ETH_30_TC3XX_USED_FCS_LEN_BYTE)))
  {
    errorId = ETH_30_TC3XX_E_INV_PARAM;
  }
  else if(PhysAddrPtrDst == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else if(PhysAddrPtrSrc == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    Eth_30_Tc3xx_EnterExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #100 Check whether buffer is locked for transmission */
    if( Eth_30_Tc3xx_Cfg_GetTxBufferBusyState(CtrlIdx, BufIdx) == ETH_30_TC3XX_BUFFER_BUSY )
    {
      P2VAR(uint8, AUTOMATIC, AUTOMATIC) bufPtr;
      P2VAR(uint8, AUTOMATIC, AUTOMATIC) bufStartPtr;
      uint32 bufOffset;
      Eth_FrameIdType frameId;

      /* set buffer index and pointer */
      bufOffset = Eth_30_Tc3xx_Cfg_GetTxBufferStart(CtrlIdx, BufIdx);
      bufStartPtr = &Eth_30_Tc3xx_Cfg_GetTxBuffer(CtrlIdx)[bufOffset];
      bufPtr = bufStartPtr;

      frameId = Eth_30_Tc3xx_GetFrameId(&bufPtr[ETH_30_TC3XX_HDR_LEN_BYTE],
                                       (uint16)(Eth_30_Tc3xx_Cfg_GetTxBufferLen(CtrlIdx, BufIdx) - ETH_30_TC3XX_HDR_LEN_BYTE));

      /* #1000 Check whether transmission length is zero (buffer release)*/
      if ( LenByte == 0U )
      {
        /* #1010 length zero: release transmit buffer only */
        Eth_30_Tc3xx_Cfg_SetTxBufferBusyState(CtrlIdx, BufIdx, ETH_30_TC3XX_BUFFER_NOT_BUSY);
        retVal = E_OK;
      }
      else
      {
        uint8 curPos;
        uint8 descrRingIdx = 0;

        /* #1020 length greater than zero: perpare buffer for transmission */
        /* Assemble Ethernet Header */
        /* Physical destination address */
        bufPtr[ETH_30_TC3XX_TX_DST_OFFSET_U8 + 0U] = PhysAddrPtrDst[0];
        bufPtr[ETH_30_TC3XX_TX_DST_OFFSET_U8 + 1U] = PhysAddrPtrDst[1];
        bufPtr[ETH_30_TC3XX_TX_DST_OFFSET_U8 + 2U] = PhysAddrPtrDst[2];
        bufPtr[ETH_30_TC3XX_TX_DST_OFFSET_U8 + 3U] = PhysAddrPtrDst[3];
        bufPtr[ETH_30_TC3XX_TX_DST_OFFSET_U8 + 4U] = PhysAddrPtrDst[4];
        bufPtr[ETH_30_TC3XX_TX_DST_OFFSET_U8 + 5U] = PhysAddrPtrDst[5];

        /* Physical source address */
        bufPtr[ETH_30_TC3XX_TX_SRC_OFFSET_U8 + 0U] = PhysAddrPtrSrc[0];
        bufPtr[ETH_30_TC3XX_TX_SRC_OFFSET_U8 + 1U] = PhysAddrPtrSrc[1];
        bufPtr[ETH_30_TC3XX_TX_SRC_OFFSET_U8 + 2U] = PhysAddrPtrSrc[2];
        bufPtr[ETH_30_TC3XX_TX_SRC_OFFSET_U8 + 3U] = PhysAddrPtrSrc[3];
        bufPtr[ETH_30_TC3XX_TX_SRC_OFFSET_U8 + 4U] = PhysAddrPtrSrc[4];
        bufPtr[ETH_30_TC3XX_TX_SRC_OFFSET_U8 + 5U] = PhysAddrPtrSrc[5];

        bufPtr = &bufPtr[ETH_30_TC3XX_TX_TYPE_OFFSET_U8];

        if( Eth_30_Tc3xx_IsFrameTxAllowed(CtrlIdx,
                                         BufIdx,
                                         frameId,
                                         &bufPtr,
                                         &LenByte) == TRUE )
        {
          /* Frame type */
          bufPtr[0] = (uint8)(FrameType >> 8u);
          bufPtr[1] = (uint8)FrameType;

          /* increase the passed length by the Ethernet frame header length */
          LenByte += ETH_30_TC3XX_HDR_LEN_BYTE;

          /* #1030 Find the configured ring for transmission */
          if( Eth_30_Tc3xx_Cfg_IsQosEnabled(CtrlIdx) == TRUE )
          {/* PRQA S 0715 */ /* MD_MSR_1.1_715 */
            /* if frame is VLAN tagged schedule transmission with descriptor ring selected for the VLAN priority */
            if(FrameType == ETH_30_TC3XX_VLAN_ETHER_TYPE)
            {
              uint8 vlanPrio;

              vlanPrio = (uint8)((bufPtr[ETH_30_TC3XX_VLAN_TCI_UPPER_BYTE_OFFSET] & ETH_30_TC3XX_VLAN_PCP_BYTE_MASK) >> ETH_30_TC3XX_VLAN_PCP_BYTE_SHIFT);
              descrRingIdx = Eth_30_Tc3xx_Cfg_GetTxDescrRingForVlanPrio(CtrlIdx, vlanPrio);
            }
          }

          curPos = Eth_30_Tc3xx_Cfg_GetTxDescrRingFreePos(CtrlIdx, descrRingIdx);

          if ( TRUE == TxConfirmation )
          {/* PRQA S 0715 */ /* MD_MSR_1.1_715 */
            Eth_30_Tc3xx_Cfg_SetUlTxConfState(CtrlIdx, BufIdx, ETH_30_TC3XX_TX_STATE_CONFIRMATION_PENDING);
          }

          /* #1040 Prepare descriptor for Transmission */
          /*lint -e{522} */
          Eth_30_Tc3xx_LL_PrepareTxDescriptorForTransmission(CtrlIdx, descrRingIdx, curPos, BufIdx, LenByte, bufStartPtr);

          /* 1050: Remember the buffer connected to this descriptor and mark descriptor state as ready for transmission */
          Eth_30_Tc3xx_Cfg_SetTxDescrToBufferMap(CtrlIdx, descrRingIdx, curPos, BufIdx);
          Eth_30_Tc3xx_Cfg_SetTxDescrTxState(CtrlIdx, descrRingIdx, curPos, ETH_30_TC3XX_DESCRIPTOR_READY);

          if( Eth_30_Tc3xx_Cfg_IsTimeSyncEnabled(CtrlIdx) == TRUE )
          {/* PRQA S 0715 */ /* MD_MSR_1.1_715 */
            /* Reset PTP status */
            if( Eth_30_Tc3xx_Cfg_GetTxTsRequest(CtrlIdx, BufIdx) == ETH_30_TC3XX_TIMESYNC_TS_REQUESTED )
            {
              P2VAR(Eth_30_Tc3xx_TsContextType, AUTOMATIC, AUTOMATIC) txTsContext = Eth_30_Tc3xx_Cfg_GetTxTsContext(CtrlIdx, BufIdx);

              txTsContext->RingIdx  = descrRingIdx;
              txTsContext->DescrIdx = curPos;

              /*lint -e{522} */
              Eth_30_Tc3xx_LL_PrepareTxDescriptorForTimestamping(CtrlIdx, descrRingIdx, curPos, BufIdx);
            }
          }

          /* #1060 Prepare Tx descriptor for checksum offloading */
          if( Eth_30_Tc3xx_Cfg_IsIpChecksumOffloadingEnabled(CtrlIdx) == TRUE )
          {/* PRQA S 0715 */ /* MD_MSR_1.1_715 */
            Eth_30_Tc3xx_LL_PrepareTxDescriptorForIpChecksumOffloading(CtrlIdx, descrRingIdx, curPos); /*lint !e522 */
          }
          if( Eth_30_Tc3xx_Cfg_IsProtocolChecksumOffloadingEnabled(CtrlIdx) == TRUE )
          {/* PRQA S 0715 */ /* MD_MSR_1.1_715 */
            Eth_30_Tc3xx_LL_PrepareTxDescriptorForProtocolChecksumOffloading(CtrlIdx, descrRingIdx, curPos); /*lint !e522 */
          }

          /* #1070 Mark as owned by DMA */
          /*lint -e{522} */
          Eth_30_Tc3xx_LL_TriggerTransmission(CtrlIdx, descrRingIdx, curPos);

          /* #1080 Move next descriptor in the transmission ring */
          Eth_30_Tc3xx_IncTxDescRingFreePos(CtrlIdx, descrRingIdx);


          retVal = E_OK;
        }
      }

      Eth_30_Tc3xx_FinishFrameTx(CtrlIdx, BufIdx, frameId);
    }

    Eth_30_Tc3xx_ExitExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx), ETH_30_TC3XX_SID_TRANSMIT, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e!438 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* PRQA S 6010, 6030, 6050, 6060, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STPAR, MD_MSR_STMIF */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_VTRANSMIT == STD_ON */

#if (ETH_30_TC3XX_IMPLEMENTATION_RECEIVE == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Receive
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
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Receive(
        uint8                                   CtrlIdx,
  P2VAR(Eth_RxStatusType, AUTOMATIC, AUTOMATIC) RxStatusPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  CtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);
  
# if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check parameters for plausibility */
  if(CtrlIdx >= ETH_30_TC3XX_MAX_CTRLS_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if(Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if(Eth_30_Tc3xx_CtrlMode[CtrlIdx] == ETH_MODE_DOWN)
  {
    errorId = ETH_30_TC3XX_E_INV_MODE;
  }
  else if( RxStatusPtr == NULL_PTR )
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON */
  {
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) bufPtr;
    uint16 lenByte;
    boolean isBroadcast;
    uint16 frameType;
    uint8 descrRingIdx;

    /* ----- Implementation ----------------------------------------------- */
    Eth_30_Tc3xx_EnterExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    (*RxStatusPtr) = ETH_NOT_RECEIVED;

    /* #100 Retrieve the DescrRing where a frame has been received */
    if( Eth_30_Tc3xx_Cfg_IsRxInterruptModeEnabled(CtrlIdx) == FALSE )
    {
      /*lint -e{522} */
      Eth_30_Tc3xx_LL_SetRxEvents(CtrlIdx);
    }

    descrRingIdx = Eth_30_Tc3xx_GetHighestPrioPendingRxEventDescrRing(CtrlIdx);

    if(descrRingIdx != ETH_30_TC3XX_UNDEFINED_DESCRIPTOR_RING)
    {
      uint16 rxDescProcPos = Eth_30_Tc3xx_Cfg_GetRxDescrRingProcPos(CtrlIdx, descrRingIdx);
      uint16 bufIdx = Eth_30_Tc3xx_Cfg_GetRxDescrToBufferMap(CtrlIdx, descrRingIdx, rxDescProcPos);

      /* Check if bufIdx is valid */
      if (bufIdx < Eth_30_Tc3xx_Cfg_GetRxBufferNum(CtrlIdx, descrRingIdx))
      {
        /* #110 Check whether descriptor is owned by Host or DMA */
        /*lint -e{522} */
        if(Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver(CtrlIdx, descrRingIdx, rxDescProcPos) == TRUE)
        {
          /* #1000 Is an error flag set in the descriptor? */
          /*lint -e{522} */
          if(Eth_30_Tc3xx_LL_IsErrorinRxDescriptor(CtrlIdx, descrRingIdx, rxDescProcPos) == FALSE)
          {
            P2VAR(uint8, AUTOMATIC, AUTOMATIC) srcMacPtr;
            uint32 bufferOffset = bufIdx * Eth_30_Tc3xx_Cfg_GetRxBufferLen(CtrlIdx, descrRingIdx);

            /* #1010 Extract frame length from RX descriptor */
            /*lint -e{522} */
            lenByte = Eth_30_Tc3xx_LL_GetFrameLengthFromRxDescriptor(CtrlIdx, descrRingIdx, rxDescProcPos);

            /* #1020 Access associated buffer */
            bufPtr = &Eth_30_Tc3xx_Cfg_GetRxBuffer(CtrlIdx, descrRingIdx)[bufferOffset];

            /* #1030 Check whether received frame is a broadcast */
            isBroadcast = Eth_30_Tc3xx_IsBroadcast(&bufPtr[ETH_30_TC3XX_RX_DST_OFFSET_U8]);

            srcMacPtr = &bufPtr[ETH_30_TC3XX_RX_SRC_OFFSET_U8];

            bufPtr   = &bufPtr[ETH_30_TC3XX_RX_TYPE_OFFSET_U8];
            lenByte -= ETH_30_TC3XX_DEST_SRC_MACS_LEN_BYTE;

            Eth_30_Tc3xx_SetFrameId(CtrlIdx, bufPtr, lenByte);

            if( Eth_30_Tc3xx_IsFrameRxAllowed(CtrlIdx,
                                             &bufPtr,
                                             &lenByte) == TRUE )
            {
              /* #1040 Extract frame type */
              frameType  = (uint16)((uint16)bufPtr[0] << 8u);
              frameType |=          (uint16)bufPtr[1];

              if( Eth_30_Tc3xx_Cfg_IsTimeSyncEnabled(CtrlIdx) == TRUE ) /* PRQA S 0715 1 */ /* MD_MSR_1.1_715 */
              {
                Eth_30_Tc3xx_Cfg_PushRxTsContextStack(CtrlIdx, descrRingIdx, rxDescProcPos);
              }


              Eth_30_Tc3xx_ExitExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

              /* #1050 Call RxIndication of Ethernet Interface */
              EthIf_RxIndication(
                  Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx),
                  frameType,
                  isBroadcast,
                  srcMacPtr,
                  (P2VAR(Eth_DataType, AUTOMATIC, AUTOMATIC))&bufPtr[ETH_30_TC3XX_FRAME_TYPE_LEN_BYTE], /* PRQA S 3305, 0310 */ /* MD_Eth_30_Tc3xx_3305, MD_Eth_30_Tc3xx_0310 */
                  (uint16)(lenByte - ETH_30_TC3XX_FRAME_TYPE_LEN_BYTE));

              Eth_30_Tc3xx_EnterExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */ /* PRQA S 0715 1 */ /* MD_MSR_1.1_715 */

              if( Eth_30_Tc3xx_Cfg_IsTimeSyncEnabled(CtrlIdx) == TRUE ) /* PRQA S 0715 1 */ /* MD_MSR_1.1_715 */
              {
                Eth_30_Tc3xx_Cfg_PopRxTsContextStack(CtrlIdx);
              }
            }

            Eth_30_Tc3xx_FinishFrameRx(CtrlIdx, &bufPtr);
          }
          else
          {
            /* payload not valid - discard package */
          }

          /* #120 Recharge descriptor so that the next frame can be received in this descriptor */
          /*lint -e{522} */
          Eth_30_Tc3xx_LL_RechargeRxDescriptor(CtrlIdx, descrRingIdx, rxDescProcPos);

          /* #130 Do adaptions in the descriptor ring after decriptor processing has been finished,
           * e. g. setting of tail pointer registers, reordering of descriptors or buffers, ... */
          /*lint -e{522} */
          Eth_30_Tc3xx_LL_AdaptRxDescriptorRingAfterReception(CtrlIdx, descrRingIdx, rxDescProcPos);

          /* #150 Next Descriptor will be processed now */
          Eth_30_Tc3xx_IncRxDescrRingProcPos(CtrlIdx, descrRingIdx);
          rxDescProcPos = Eth_30_Tc3xx_Cfg_GetRxDescrRingProcPos(CtrlIdx, descrRingIdx);

          /* #160 Rearm reception for the given RX descriptor ring on register level */
          /*lint -e{522} */
          Eth_30_Tc3xx_LL_RearmMacForReception(CtrlIdx, descrRingIdx);

          /* Frames may have been lost because of a buffer overflow or unavailable buffers. Nevertheless no error is returned to the EthIf.
          Otherwise congestion could happen in polling mode because ETH_RECEIVED_MORE_DATA_AVAILABLE can not be returned to the EthIf anymore
          and a maximum of one frame per mainfunction can be processed. */
          /*lint -e{522} */
          if(Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver(CtrlIdx,  descrRingIdx, rxDescProcPos) == TRUE)
          {
            /* more data available ... */
            Eth_30_Tc3xx_SetRxEvent(CtrlIdx, descrRingIdx);
            (*RxStatusPtr) = ETH_RECEIVED_MORE_DATA_AVAILABLE;
          }
          else
          {
            /* Set status to received */
            (*RxStatusPtr) = ETH_RECEIVED;
          }
        }
        else
        {
          (*RxStatusPtr) = ETH_NOT_RECEIVED;
        }
      }
    }
    Eth_30_Tc3xx_ExitExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx), ETH_30_TC3XX_SID_RECEIVE, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e!438 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON */
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL , MD_MSR_STMIF */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_RECEIVE == STD_ON */

#if (ETH_30_TC3XX_IMPLEMENTATION_TX_CONFIRMATION == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_TxConfirmation
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
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_TxConfirmation(
  uint8 CtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  CtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);
  
# if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check parameters for plausibility */
  if(CtrlIdx >= ETH_30_TC3XX_MAX_CTRLS_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if(Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if(Eth_30_Tc3xx_CtrlMode[CtrlIdx] == ETH_MODE_DOWN)
  {
    errorId = ETH_30_TC3XX_E_INV_MODE;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON */
  {
    uint8 descrRingIdx;

    /* #100 Retrieve the DescrRing where a frame has been transmitted */
    if( Eth_30_Tc3xx_Cfg_IsTxInterruptModeEnabled(CtrlIdx) == FALSE )
    {
      /*lint -e{522} */
      Eth_30_Tc3xx_LL_SetTxEvents(CtrlIdx);
    }

    descrRingIdx = Eth_30_Tc3xx_GetHighestPrioPendingTxEventDescrRing(CtrlIdx);

    if(descrRingIdx != ETH_30_TC3XX_UNDEFINED_DESCRIPTOR_RING)
    {
      /* #200 Find last processed descriptor */
      uint8 curDescrPos   = Eth_30_Tc3xx_Cfg_GetTxDescrRingProcPos(CtrlIdx, descrRingIdx);

      Eth_30_Tc3xx_EnterExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

      /* #300 Iterate over all Tx descriptors, which have been transmitted */
      /* PRQA S 3415 2 */ /* MD_Eth_30_Tc3xx_3415 */
      /*lint -e{522} */
      while( (Eth_30_Tc3xx_LL_IsTxDescriptorOwnedByDriver(CtrlIdx, descrRingIdx, curDescrPos) == TRUE)                        &&
             (Eth_30_Tc3xx_Cfg_GetTxDescrTxState(CtrlIdx, descrRingIdx, curDescrPos)     == ETH_30_TC3XX_DESCRIPTOR_READY)    )
      {
        uint8 relatedBufIdx = Eth_30_Tc3xx_Cfg_GetTxDescrToBufferMap(CtrlIdx, descrRingIdx, curDescrPos);

        Eth_30_Tc3xx_Cfg_SetTxDescrTxState(CtrlIdx, descrRingIdx, curDescrPos, ETH_30_TC3XX_DESCRIPTOR_TRANSMITTED);

        /* #3000 Check if upper layer requested to be notified about the finished transmission */
        if(Eth_30_Tc3xx_Cfg_GetUlTxConfState(CtrlIdx, relatedBufIdx) == ETH_30_TC3XX_TX_STATE_CONFIRMATION_PENDING)
        {
          Eth_30_Tc3xx_ExitExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

          /* #30000 Call Ethernet Interface TxConfirmation */
          EthIf_TxConfirmation(Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx), relatedBufIdx);

          Eth_30_Tc3xx_EnterExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

          Eth_30_Tc3xx_Cfg_SetUlTxConfState(CtrlIdx, relatedBufIdx, ETH_30_TC3XX_TX_STATE_CONFIRMATION_NOT_PENDING);
        }

        if( Eth_30_Tc3xx_Cfg_IsTimeSyncEnabled(CtrlIdx) == TRUE )
        {
          Eth_30_Tc3xx_Cfg_SetTxTsRequest(CtrlIdx, relatedBufIdx, ETH_30_TC3XX_TIMESYNC_TS_NOT_REQUESTED);
          /*lint -e{522} */
          Eth_30_Tc3xx_LL_ResetTimestampingInTxDescriptor(CtrlIdx, descrRingIdx, curDescrPos);
        }

        /* #3100 release descriptor and buffer */
        Eth_30_Tc3xx_Cfg_SetTxDescrTxState(CtrlIdx, descrRingIdx, curDescrPos, ETH_30_TC3XX_DESCRIPTOR_NOT_READY);
        Eth_30_Tc3xx_Cfg_SetTxBufferBusyState(CtrlIdx, relatedBufIdx, ETH_30_TC3XX_BUFFER_NOT_BUSY);

        Eth_30_Tc3xx_LL_RechargeTxDescriptor(CtrlIdx, descrRingIdx, curDescrPos);

        /* #3200 switch to next descriptor */
        Eth_30_Tc3xx_IncTxDescRingProcPos(CtrlIdx, descrRingIdx);
        curDescrPos = Eth_30_Tc3xx_Cfg_GetTxDescrRingProcPos(CtrlIdx, descrRingIdx);
      }

      Eth_30_Tc3xx_ExitExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    }
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx), ETH_30_TC3XX_SID_TX_CONFIRMATION, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e!438 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON */
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_TX_CONFIRMATION == STD_ON */

#if (ETH_30_TC3XX_IMPLEMENTATION_MAINFUNCTION == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_MainFunction
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_MainFunction( void )
{
  /* #10 Call MainFunction of lower layer */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_MainFunction();
}
#endif /* ETH_30_TC3XX_IMPLEMENTATION_MAINFUNCTION == STD_ON */

#if (ETH_30_TC3XX_IMPLEMENTATION_GET_VERSION_INFO == STD_ON)
# if (ETH_30_TC3XX_VERSION_INFO_API == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetVersionInfo
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVersionInfo(
  P2VAR(Std_VersionInfoType, ETH_30_TC3XX_APPL_DATA, ETH_30_TC3XX_APPL_DATA) VersionInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
   uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#  if ( ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check parameters for plausibility */
  if(VersionInfoPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
#  endif /* ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON */
  {
    /*#100 Return Vendor Id, Module Id and SW version number */
    VersionInfoPtr->vendorID = ETH_VENDOR_ID;
    VersionInfoPtr->moduleID = ETH_MODULE_ID;
    VersionInfoPtr->sw_major_version = ETH_30_TC3XX_SW_MAJOR_VERSION;
    VersionInfoPtr->sw_minor_version = ETH_30_TC3XX_SW_MINOR_VERSION;
    VersionInfoPtr->sw_patch_version = ETH_30_TC3XX_SW_PATCH_VERSION;
  }
  /* ----- Development Error Report --------------------------------------- */
#  if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_MODULE_ID, 0, ETH_30_TC3XX_SID_GET_VERSION_INFO, errorId);
  }
#  else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e!438 */
#  endif /* ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON */
} /* Eth_30_Tc3xx_GetVersionInfo() */
# endif /* ETH_VERSION_INFO_API */
#endif /* ETH_30_TC3XX_IMPLEMENTATION_GET_VERSION_INFO == STD_ON */

#if (ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetRxStats()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxStats(
        uint8                                                          CtrlIdx,
  P2VAR(Eth_RxStatsType, ETH_30_TC3XX_APPL_VAR, ETH_30_TC3XX_APPL_VAR) RxStatsPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  CtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);
  
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;
  /* #10 Check plausibility of input parameters */
  /* Check initialization state of the component */
  if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  /* Check parameter 'CtrlIdx' */
  else if (CtrlIdx >= ETH_30_TC3XX_MAX_CTRLS_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  /* Check parameter 'RxStats' */
  else if (RxStatsPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
#endif
  {
    /* #20 Enter exclusive area (Reason: Retrieval of RX statistic counters in a consistent manner)*/
    Eth_30_Tc3xx_EnterExclusiveArea(RXTX_STATS); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #30 Read the Rx statistics counter registers and return the memory address where the results are stored */
    retVal = Eth_30_Tc3xx_LL_GetRxStats(CtrlIdx, RxStatsPtr);

    /* #40 Leave exclusive area */
    Eth_30_Tc3xx_ExitExclusiveArea(RXTX_STATS); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx), ETH_30_TC3XX_SID_GET_RX_STATS, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
#endif

  return retVal;
}

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetTxStats()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxStats(
        uint8                                                          CtrlIdx,
  P2VAR(Eth_TxStatsType, ETH_30_TC3XX_APPL_VAR, ETH_30_TC3XX_APPL_VAR) TxStatsPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;
  /* #10 Check plausibility of input parameters */
  /* Check initialization state of the component */
  if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  /* Check parameter 'CtrlIdx' */
  else if (CtrlIdx >= ETH_30_TC3XX_MAX_CTRLS_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  /* Check parameter 'TxStats' */
  else if (TxStatsPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
#endif
  {
    /* #20 Enter exclusive area (Reason: Retrieval of TX statistic counters in a consistent manner)*/
    Eth_30_Tc3xx_EnterExclusiveArea(RXTX_STATS); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #30 Read the Tx statistics counter registers and return the memory address where the results are stored */
    retVal = Eth_30_Tc3xx_LL_GetTxStats(CtrlIdx, TxStatsPtr);

    /* #40 Leave exclusive area */
    Eth_30_Tc3xx_ExitExclusiveArea(RXTX_STATS); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx), ETH_30_TC3XX_SID_GET_TX_STATS, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
#endif

  return retVal;
}
#endif /* ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API */

#define ETH_30_TC3XX_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* module specific MISRA deviations:
  MD_Eth_30_Tc3xx_0303:
    Reason:     Hardware accesses need a cast from integral type to a pointer to object.
    Risk:       There is no risk as the register is mapped to the respective memory address.
    Prevention: Covered by code review.

  MD_Eth_30_Tc3xx_0310:
    Reason:     The pointer where the cast led to has a less stricter alignment. The cast
                is necessary since the array represents a continuous data buffer.
    Risk:       There is no risk since the array is a continuous data buffer.
    Prevention: Covered by code review.

  MD_Eth_30_Tc3xx_3305:
    Reason:     The cast is necessary since the array represents a continuous data buffer and the Ethernet header
                has a length of 14 bytes
    Risk:       There is no risk since the array is a continuous data buffer. which is not divisable by 4.
    Prevention: Covered by code review.

  MD_Eth_30_Tc3xx_3305_1:
    Reason:     Fast access to Ethernet MAC address.
    Risk:       When the physical address buffer starts on an uneven memory address this may lead to
                a unaligned access exception on some hardware platforms. The buffer must
                start on an even memory address.
    Prevention: Covered by code review.

  MD_Eth_30_Tc3xx_3206:
    Reason:     The configuration pointer is only used when configuration variant 3 is chosen.
    Risk:       There is no risk.
    Prevention: Covered by code review.

  MD_Eth_30_Tc3xx_3199:
    Reason:     Dummy statement to avoid compiler warnings.
    Risk:       There is no risk as such statements have no effect on the code.
    Prevention: Covered by code review.

  MD_Eth_30_Tc3xx_0488:
    Reason:     Pointer arithmetic necessary to quickly access the reception buffer start address.
    Risk:       Wrong arithmetic could lead to a memory corruption.
    Prevention: Covered by code review. Wrong arithmetic is avoided.

  MD_Eth_30_Tc3xx_3371:
    Reason:     Intended behaviour of crc checksum.
    Risk:       There is no risk.
    Prevention: Covered by code review.

  MD_Eth_30_Tc3xx_3197:
    Reason:     First read/write access is variant depending. Possible initialization before possible write access does not harm but
                improves code readability.
    Risk:       There is no risk.
    Prevention: Covered by code review.

  MD_Eth_30_Tc3xx_3218:
    Reason:     No function local static variables should be used. File local variable must be used instead.
    Risk:       There is no risk.
    Prevention: Covered by code review.

  MD_Eth_30_Tc3xx_3219:
    Reason:     This function is inlined and therefore it has to be implemented here. The function is not used
                by all implementation files which include this header file.
    Risk:       None.
    Prevention: None.

  MD_Eth_30_Tc3xx_3415:
   Reason:      Avoid nesting of control structures.
   Risk:        There is no risk because the functions called only retrieve data and don't manipulate them.
   Prevention:  Convered by component tests.
*/

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx.c
 *********************************************************************************************************************/

