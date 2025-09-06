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
/*!        \file  EthIf_Rx.c
 *        \brief  EthIf Rx public API source file
 *
 *      \details  Implementation of the public API of the sub-module Rx of EthIf.
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

#define ETHIF_RX_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
#include "EthIf_Rx.h"
#include "EthIf_Rx_Cbk.h"
#include "EthIf_Rx_Int.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of Msn header file */
#if (  (ETHIF_SW_MAJOR_VERSION != (10u)) \
    || (ETHIF_SW_MINOR_VERSION != (0u)) \
    || (ETHIF_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of EthIf_Rx.c and EthIf.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (ETHIF_CFG_MAJOR_VERSION != (7u)) \
    || (ETHIF_CFG_MINOR_VERSION != (0u)) )
# error "Version numbers of EthIf_Rx.c and EthIf_Cfg.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (ETHIF_RX_LOCAL)                                                                                           /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_RX_LOCAL static
#endif

#if !defined (ETHIF_RX_LOCAL_INLINE)                                                                                    /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_RX_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
/*! Data needed during reception processing */
typedef struct EthIf_RxFrameHandlingStruct
{
        EthIf_FrameHdrType              FrameHdr;
  P2VAR(uint8, TYPEDEF, ETHIF_APPL_VAR) EthLayerPayloadPtr;
  P2VAR(uint8, TYPEDEF, ETHIF_APPL_VAR) EthIfLayerPayloadPtr;
        Eth_FrameType                   EthLayerFrameType;
        Eth_FrameType                   EthIfLayerFrameType;
        uint16                          EthLayerPayloadLen;
        uint16                          EthIfLayerPayloadLen;
} EthIf_RxFrameHandlingType;

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define ETHIF_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthIf_ExtractRxEthHeader
 *********************************************************************************************************************/
/*! \brief          Extracts and creates rx processing data
 *  \details        -
 *  \param[in]      frameType        Ether Type of the Ethernet frame as passed by the driver
 *  \param[in]      payloadLen       Length of the Ethernet frames payload as passed by the driver
 *  \param[in]      srcMacPtr        Pointer to the source MAC address of the frame
 *  \param[in]      payloadPtr       Pointer to the Ethernet frames payload as passed by the driver
 *  \param[out]     rxFrameHandling  Reception handling data extracted
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_RX_LOCAL_INLINE FUNC(void, ETHIF_RX_INLINE_CODE) EthIf_ExtractRxEthHeader(
          Eth_FrameType                                          frameType,
          uint16                                                 payloadLen,
  P2CONST(uint8,                     AUTOMATIC, ETHIF_APPL_DATA) srcMacPtr,
    P2VAR(uint8,                     AUTOMATIC, ETHIF_APPL_VAR)  payloadPtr,
    P2VAR(EthIf_RxFrameHandlingType, AUTOMATIC, ETHIF_APPL_VAR)  rxFrameHandling);

/**********************************************************************************************************************
 *  EthIf_IsRxAllowed
 *********************************************************************************************************************/
/*! \brief          Checks if the frame represented by the passed information is allowed to be received
 *  \details        -
 *  \param[in]      ethCtrlIdx    Eth controller index the frame was received on
 *                                [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \param[out]     ethIfCtrlIdx  EthIf controller index representing a valid data path for the frame (only valid if TRUE
 *                                is returned)
 *  \param[in]      frameHdr      Ethernet frame header information
 *  \param[in]      payloadPtr    Pointer to the frames payload
 *  \param[in]      payloadLen    Length of the frames payload
 *  \return         TRUE - Frame is allowed to be received
 *  \return         FALSE - Frame is not allowed to be received
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_RX_LOCAL_INLINE FUNC(boolean, ETHIF_RX_INLINE_CODE) EthIf_IsRxAllowed(
          EthIf_EthCtrlIterType                                ethCtrlIdx,
    P2VAR(EthIf_EthIfCtrlIterType, AUTOMATIC, ETHIF_APPL_VAR)  ethIfCtrlIdx,
  P2CONST(EthIf_FrameHdrType,      AUTOMATIC, ETHIF_APPL_DATA) frameHdr,
  P2CONST(uint8,                   AUTOMATIC, ETHIF_APPL_DATA) payloadPtr,
          uint16                                               payloadLen);

#if ( ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE != ETHIF_NO_EXTENDED_TRAFFIC_HANDLING )                                      /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 *  EthIf_InvokeRxTrafficHandling
 *********************************************************************************************************************/
/*! \brief          Invokes the reception traffic handling sub-modules
 *  \details        -
 *  \param[in]      ethIfCtrlIdx      EthIf controller reception is processed for
 *                                    [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \param[in]      rxFrameHandling   Reception handling data
 *  \return         TRUE - frame is allowed to be forwarded to upper layers
 *  \return         FALSE - frame must not be forwarded to upper layers
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_RX_LOCAL_INLINE FUNC(boolean, ETHIF_RX_INLINE_CODE) EthIf_InvokeRxTrafficHandling(
          EthIf_EthIfCtrlIterType                                ethIfCtrlIdx,
  P2CONST(EthIf_RxFrameHandlingType, AUTOMATIC, ETHIF_APPL_DATA) rxFrameHandling);
#endif /* ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE */

/**********************************************************************************************************************
 *  EthIf_HandleUlRxIndication
 *********************************************************************************************************************/
/*! \brief          Handles the Rx indication of the upper layers
 *  \details        This function informs the upper layers about the reception of a frame they have registered for.
 *  \param[in]      ownerIdx             Frame owner index
 *  \param[in]      ulRxIndicationData   Data to retrieve the upper layers to inform and information about the frame.
 *  \return         TRUE - frame passed to upper layer -> frame received
 *  \return         FALSE - no upper layer registered for reception -> frame not received
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_RX_LOCAL_INLINE FUNC(boolean, ETHIF_RX_INLINE_CODE) EthIf_HandleUlRxIndication(
          EthIf_UserIterType                                         ownerIdx,
  P2CONST(EthIf_UlRxIndiactionDataType, AUTOMATIC, ETHIF_APPL_DATA)  ulRxIndicationData);

/**********************************************************************************************************************
 *  EthIf_InvokeRxSwtHandling
 *********************************************************************************************************************/
/*! \brief          Invokes the switch handling sub-modules
 *  \details        -
 *  \param[in]      ethCtrlIdx           Eth controller the frame was received on
 *                                       [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \param[in]      ownerIdx             Frame owner the frame belongs to
 *                                       [range: ownerIdx < EthIf_GetSizeOfUser()]
 *  \param[in]      ulRxIndicationData   Data to retrieve the upper layers to inform and information about the frame.
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_RX_LOCAL_INLINE FUNC(void, ETHIF_RX_INLINE_CODE) EthIf_InvokeRxSwtHandling(
          EthIf_EthIfCtrlIterType                                   ethCtrlIdx,
          EthIf_UserIterType                                        ownerIdx,
  P2CONST(EthIf_UlRxIndiactionDataType, AUTOMATIC, ETHIF_APPL_DATA) rxIndData);

/**********************************************************************************************************************
 *  EthIf_InvokeZeroCopyHandling
 *********************************************************************************************************************/
/*! \brief          Invokes the zero copy handling sub-modules
 *  \details        -
 *  \param[in]      isReceivedByUser  Indicates if frame was passed to upper layer
 *  \param[in]      ethIfCtrlIdx      EthIf controller the frame was received on (if non was found value must be
 *                                    set to EthIf_GetSizeOfEthIfCtrl())
 *                                    [range: ethIfCtrlIdx <= EthIf_GetSizeOfEthIfCtrl()]
 *  \param[in]      ethCtrlIdx        Eth controller the frame was received on
 *                                    [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \param[in]      rxFrameHandling   Reception handling data
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_RX_LOCAL_INLINE FUNC(void, ETHIF_RX_INLINE_CODE) EthIf_InvokeZeroCopyHandling(
          boolean                                                isReceivedByUser,
          EthIf_EthIfCtrlIterType                                ethIfCtrlIdx,
          EthIf_EthCtrlIterType                                  ethCtrlIdx,
  P2CONST(EthIf_RxFrameHandlingType, AUTOMATIC, ETHIF_APPL_DATA) rxFrameHandling);

/**********************************************************************************************************************
 *  EthIf_Internal_RxIndication
 *********************************************************************************************************************/
/*! \brief          Notifies the EthIf about a received Ethernet frame
 *  \details        See EthIf_RxIndication() for details.
 *  \param[in]      ethCtrlIdx   Ethernet controller index
 *                               [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \param[in]      frameType    EtherType the Ethernet frame is related to
 *  \param[in]      isBroadcast  Broadcast indication:
 *                               FALSE - frame isn't a broadcast frame
 *                               TRUE - frame is a broadcast frame
 *  \param[in]      physAddrPtr  Source MAC address of the Ethernet frame
 *  \param[out]     dataPtr      Location of the Ethernet frame payload (no VLAN tag considered)
 *  \param[in]      lenByte      Length of the Ethernet frame payload (no VLAN tag considered)
 *  \pre            -
 *  \context        TASK|ISR1|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
ETHIF_RX_LOCAL_INLINE FUNC(void, ETHIF_RX_INLINE_CODE) EthIf_Internal_RxIndication(
        uint8                                     ethCtrlIdx,
        Eth_FrameType                             frameType,
        boolean                                   isBroadcast,
  P2VAR(uint8,        AUTOMATIC, ETHIF_APPL_VAR)  physAddrPtr,
  P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR)  dataPtr,
        uint16                                    lenByte);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthIf_ExtractRxEthHeader
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHIF_RX_LOCAL_INLINE FUNC(void, ETHIF_RX_INLINE_CODE) EthIf_ExtractRxEthHeader(
          Eth_FrameType                                          frameType,
          uint16                                                 payloadLen,
  P2CONST(uint8,                     AUTOMATIC, ETHIF_APPL_DATA) srcMacPtr,
    P2VAR(uint8,                     AUTOMATIC, ETHIF_APPL_VAR)  payloadPtr,
    P2VAR(EthIf_RxFrameHandlingType, AUTOMATIC, ETHIF_APPL_VAR)  rxFrameHandling)
{
  /* #10 Setup position and length information for Eth layer and EthIf layer */
  rxFrameHandling->EthLayerPayloadPtr    = payloadPtr;                                                                  /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
  rxFrameHandling->EthIfLayerPayloadPtr  = payloadPtr;                                                                  /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
  rxFrameHandling->EthLayerFrameType     = frameType;                                                                   /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
  rxFrameHandling->EthLayerPayloadLen    = payloadLen;                                                                  /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
  rxFrameHandling->EthIfLayerFrameType   = frameType;                                                                   /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
  rxFrameHandling->EthIfLayerPayloadLen  = payloadLen;                                                                  /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */

  /* #20 Extract Source-/Destination-MAC information and set EtherType and VLAN ID */
  rxFrameHandling->FrameHdr.SrcMacAddrPtr = srcMacPtr;                                                                  /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
#if ( ETHIF_FIREWALL_SUPPORT == STD_ON )                                                                                /* COV_ETHIF_QM_FEAT_CHECK_ON */
  /* PRQA S 3382 1 */ /* MD_EthIf_3382 */
  rxFrameHandling->FrameHdr.DstMacAddrPtr = &srcMacPtr[-(sint16)ETH_PHYS_ADDR_LEN_BYTE];                                /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
#endif /* ETHIF_FIREWALL_SUPPORT */
  rxFrameHandling->FrameHdr.EtherType     = frameType;                                                                  /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
  rxFrameHandling->FrameHdr.VlanId        = ETHIF_INV_VLAN_ID;                                                          /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */

  /* #30 Check if frame is a tagged frame */
  if( rxFrameHandling->FrameHdr.EtherType == ETHIF_VLAN_TPID )
  {
    /* #300 Extract tag information out of frame and update EthIf layer position and length information */
    rxFrameHandling->FrameHdr.VlanId  = (uint16)(((uint16)payloadPtr[ETHIF_VLAN_TCI_OFFSET]) << 8U);                    /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
    rxFrameHandling->FrameHdr.VlanId |= (uint16)payloadPtr[ETHIF_VLAN_TCI_OFFSET + 1U];                                 /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
    rxFrameHandling->FrameHdr.VlanId &= (uint16)ETHIF_VLAN_TCI_VID_MASK;                                                /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */

    rxFrameHandling->FrameHdr.Priority = (uint8)(payloadPtr[ETHIF_VLAN_TCI_OFFSET]
                                                            >> ((sint8)ETHIF_VLAN_TCI_PCP_SHIFT - (sint8)8));           /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */

    rxFrameHandling->FrameHdr.EtherType  = (uint16)((uint16)payloadPtr[ETHIF_VLAN_FRAME_TYPE_OFFSET] << 8U);            /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
    rxFrameHandling->FrameHdr.EtherType |= (uint16)payloadPtr[ETHIF_VLAN_FRAME_TYPE_OFFSET + 1U];                       /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */

    rxFrameHandling->EthIfLayerPayloadPtr = &payloadPtr[ETHIF_VLAN_TAG_LEN_BYTE];                                       /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
    rxFrameHandling->EthIfLayerFrameType  = rxFrameHandling->FrameHdr.EtherType;                                        /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
    rxFrameHandling->EthIfLayerPayloadLen = (uint16)((sint32)payloadLen - (sint32)ETHIF_VLAN_TAG_LEN_BYTE);             /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
  }
} /* EthIf_ExtractRxEthHeader() */

/**********************************************************************************************************************
 *  EthIf_IsRxAllowed
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHIF_RX_LOCAL_INLINE FUNC(boolean, ETHIF_RX_INLINE_CODE) EthIf_IsRxAllowed(
          EthIf_EthCtrlIterType                                ethCtrlIdx,
    P2VAR(EthIf_EthIfCtrlIterType, AUTOMATIC, ETHIF_APPL_VAR)  ethIfCtrlIdx,
  P2CONST(EthIf_FrameHdrType,      AUTOMATIC, ETHIF_APPL_DATA) frameHdr,
  P2CONST(uint8,                   AUTOMATIC, ETHIF_APPL_DATA) payloadPtr,
          uint16                                               payloadLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean result = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Trigger query for a EthIf controller that represents the data path (tuple Eth-Controller and VLAN configuration) */
  (*ethIfCtrlIdx) = EthIf_QueryForEthIfController(ethCtrlIdx, frameHdr->VlanId);                                        /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */

  /* #20 Check if a valid data path is configured and the data path is active */
  if( (*ethIfCtrlIdx) < EthIf_GetSizeOfEthIfCtrl() )
  {
    /* \trace SPEC-2393656 */
    if( EthIf_GetEthIfCtrlMode((*ethIfCtrlIdx)) == ETH_MODE_ACTIVE )
    {
#if ( ETHIF_FIREWALL_SUPPORT == STD_ON )                                                                                /* COV_ETHIF_QM_FEAT_CHECK_ON */
      /* #200 If firewall support is enabled also let firewall check if reception is allowed */
      if( EthFw_IsFrameRxAllowed(EthIf_GetSnvOfEthIfCtrl((*ethIfCtrlIdx)), frameHdr, payloadPtr, payloadLen) == TRUE )  /* SBSW_ETHIF_INT_FCT_PARAM_PTR_PASS */
#else
      ETHIF_DUMMY_STATEMENT_CONST(payloadPtr);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
      ETHIF_DUMMY_STATEMENT(payloadLen);        /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
#endif /* ETHIF_FIREWALL_SUPPORT */
      {
        result = TRUE;
      }
    }
  }

  return result;
} /* EthIf_IsRxAllowed() */

#if ( ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE != ETHIF_NO_EXTENDED_TRAFFIC_HANDLING )                                      /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 *  EthIf_InvokeRxTrafficHandling
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHIF_RX_LOCAL_INLINE FUNC(boolean, ETHIF_RX_INLINE_CODE) EthIf_InvokeRxTrafficHandling(
          EthIf_EthIfCtrlIterType                                ethIfCtrlIdx,
  P2CONST(EthIf_RxFrameHandlingType, AUTOMATIC, ETHIF_APPL_DATA) rxFrameHandling)
{
  boolean isFrameForUl = TRUE;

# if ( ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE == ETHIF_TRAFFIC_MIRRORING )                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #10 Trigger mirroring sub-module for received frame */
  /* PRQA S 0310, 3305 4 */ /* MD_EthIf_310_Buffer, MD_EthIf_3305_Buffer */
  EthIf_MirrorRxTraffic(ethIfCtrlIdx,
                        rxFrameHandling->EthLayerFrameType,
                        rxFrameHandling->EthLayerPayloadLen,
                        (P2CONST(Eth_DataType, AUTOMATIC, ETHIF_APPL_DATA))rxFrameHandling->EthLayerPayloadPtr);        /* SBSW_ETHIF_INT_FCT_PARAM_PTR_PASS */
# endif /* ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE */

# if ( ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE == ETHIF_TRAFFIC_GATEWAY )                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #20 Trigger gateway sub-module for received frame and check if EthIf is allowed to pass the frame to upper layers */
  /* PRQA S 0310, 3305 4 */ /* MD_EthIf_310_Buffer, MD_EthIf_3305_Buffer */
  if( EthIf_GatewayTraffic(ethIfCtrlIdx,
                           rxFrameHandling->EthIfLayerFrameType,
                           rxFrameHandling->EthIfLayerPayloadLen,
                           (P2CONST(Eth_DataType, AUTOMATIC, ETHIF_APPL_DATA))rxFrameHandling->EthLayerPayloadPtr)      /* SBSW_ETHIF_INT_FCT_PARAM_PTR_PASS */
       == TRUE )
  {
    isFrameForUl = FALSE;
  }
# endif /* ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE */

  return isFrameForUl;
} /* EthIf_InvokeRxTrafficHandling() */
#endif /* ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE */

/**********************************************************************************************************************
 *  EthIf_HandleUlRxIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHIF_RX_LOCAL_INLINE FUNC(boolean, ETHIF_RX_INLINE_CODE) EthIf_HandleUlRxIndication(
          EthIf_UserIterType                                         ownerIdx,
  P2CONST(EthIf_UlRxIndiactionDataType, AUTOMATIC, ETHIF_APPL_DATA)  ulRxIndicationData)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean result;

  /* ----- Implementation ----------------------------------------------- */
  result = FALSE;

  /* #10 If there is an owner for the frame */
  if( ownerIdx < EthIf_GetSizeOfUser() )
  {
    EthIf_RxIndicationsIndIterType indIdx;

    /* #100 Pass frame to upper layers */
    for( indIdx = EthIf_GetRxIndicationsIndStartIdxOfUser(ownerIdx);
         indIdx < EthIf_GetRxIndicationsIndEndIdxOfUser(ownerIdx);
         indIdx++ )
    {
      EthIf_RxIndicationsIndType rxIndicationIdx = EthIf_GetRxIndicationsInd(indIdx);

      EthIf_GetRxIndications(rxIndicationIdx)(EthIf_GetSnvOfEthIfCtrl(ulRxIndicationData->EthIfCtrlIdx),
                                              ulRxIndicationData->EtherType,
                                              ulRxIndicationData->IsBroadcast,
                                              ulRxIndicationData->SrcMacPtr,
                                              ulRxIndicationData->PayloadPtr,
                                              ulRxIndicationData->PayloadLen);                                          /* SBSW_ETHIF_USERAPI_FCT_PTR_WITH_INT_PARAM_PTR_CSL03 */
      result = TRUE;
    }
  }

  return result;
} /* EthIf_HandleUlRxIndication() */

/**********************************************************************************************************************
 *  EthIf_InvokeRxSwtHandling
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHIF_RX_LOCAL_INLINE FUNC(void, ETHIF_RX_INLINE_CODE) EthIf_InvokeRxSwtHandling(
          EthIf_EthCtrlIterType                                     ethCtrlIdx,
          EthIf_UserIterType                                        ownerIdx,
  P2CONST(EthIf_UlRxIndiactionDataType, AUTOMATIC, ETHIF_APPL_DATA) rxIndData)
{
#if ( ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT == STD_ON )                                                                 /* COV_ETHIF_QM_FEAT_CHECK_ON */
  /* #10 If the upper layer registered for switch management information, initiate the management
   *     information provision process */
  if( EthIf_IsMgmtInfoIndsIndUsedOfUser(ownerIdx) &&
      EthIf_IsSwtMgmtRxCtxtPoolUsedOfEthCtrl(ethCtrlIdx) )
  {
    EthIf_InitiateRxSwtMgmtInfoProc(ethCtrlIdx,
                                    ownerIdx,
                                    rxIndData);                                                                         /* SBSW_ETHIF_INT_FCT_PARAM_PTR_PASS */
  }
#endif /* ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT */

#if ( ETHIF_ETHSWT_TIME_STAMP_SUPPORT == STD_ON )                                                                       /* COV_ETHIF_QM_FEAT_CHECK_ON */
  /* #20 If the upper layer registered for switch timestamp information, initiate the timestamp
   *     information provision process */
  if( EthIf_IsIngressTsIndsIndUsedOfUser(ownerIdx) &&
      EthIf_IsSwtTsRxCtxtPoolUsedOfEthCtrl(ethCtrlIdx) )
  {
    EthIf_InitiateRxSwtTimeStampInfoProc(ethCtrlIdx,
                                         ownerIdx,
                                         rxIndData);                                                                    /* SBSW_ETHIF_INT_FCT_PARAM_PTR_PASS */
  }
#endif /* ETHIF_ETHSWT_TIME_STAMP_SUPPORT */

#if ( ( ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT == STD_OFF ) && ( ETHIF_ETHSWT_TIME_STAMP_SUPPORT == STD_OFF ) )          /* COV_ETHIF_QM_FEAT_CHECK_OFF */
  ETHIF_DUMMY_STATEMENT(ethCtrlIdx);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  ETHIF_DUMMY_STATEMENT(ownerIdx);         /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  ETHIF_DUMMY_STATEMENT_CONST(rxIndData);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
#endif
} /* EthIf_InvokeRxSwtHandling() */

/**********************************************************************************************************************
 *  EthIf_InvokeZeroCopyHandling
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHIF_RX_LOCAL_INLINE FUNC(void, ETHIF_RX_INLINE_CODE) EthIf_InvokeZeroCopyHandling(
          boolean                                                isReceivedByUser,
          EthIf_EthIfCtrlIterType                                ethIfCtrlIdx,
          EthIf_EthCtrlIterType                                  ethCtrlIdx,
  P2CONST(EthIf_RxFrameHandlingType, AUTOMATIC, ETHIF_APPL_DATA) rxFrameHandling)
{
#if ( ETHIF_ENABLE_ZERO_COPY_EXTENSIONS == STD_ON )                                                                     /* COV_ETHIF_QM_FEAT_CHECK_ON */
    /* #10 Check if implicit buffer release must be triggered */
    /* PRQA S 3415 2 */ /* MD_EthIf_3415 */
    if( (isReceivedByUser == FALSE) ||
        (EthIf_IsImplicitBufferReleaseNeeded(ethIfCtrlIdx, rxFrameHandling->EthIfLayerFrameType) == TRUE) )
    {
      /* #100 Release the RX buffer implicitly if Ethernet driver supports the feature too */
      EthIf_EthDrvApiIdxOfEthCtrlType ethDrvApiIdx = EthIf_GetEthDrvApiIdxOfEthCtrl(ethCtrlIdx);

      /* Check if driver supports the API */
      if( EthIf_GetReleaseRxBufferOfEthDrvApi(ethDrvApiIdx) != NULL_PTR )
      {
        /* PRQA S 0310, 3305 2 */ /* MD_EthIf_310_Buffer, MD_EthIf_3305_Buffer */
        (void)EthIf_GetReleaseRxBufferOfEthDrvApi(ethDrvApiIdx)(EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                                (P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR))rxFrameHandling->EthLayerPayloadPtr); /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_INT_PARAM_PTR_CSL03 */
      }
    }
#else
    ETHIF_DUMMY_STATEMENT(isReceivedByUser);       /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
    ETHIF_DUMMY_STATEMENT(ethIfCtrlIdx);           /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
    ETHIF_DUMMY_STATEMENT(ethCtrlIdx);             /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
    ETHIF_DUMMY_STATEMENT_CONST(rxFrameHandling);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
#endif /* ETHIF_ENABLE_ZERO_COPY_EXTENSIONS */
} /* EthIf_InvokeZeroCopyHandling() */

/**********************************************************************************************************************
 *  EthIf_Internal_RxIndication
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
ETHIF_RX_LOCAL_INLINE FUNC(void, ETHIF_RX_INLINE_CODE) EthIf_Internal_RxIndication(
        uint8                                     ethCtrlIdx,
        Eth_FrameType                             frameType,
        boolean                                   isBroadcast,
  P2VAR(uint8,        AUTOMATIC, ETHIF_APPL_VAR)  physAddrPtr,
  P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR)  dataPtr,
        uint16                                    lenByte)
{
  P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR)  u8DataPtr;
        EthIf_EthIfCtrlIterType            ethIfCtrlIdx;
        EthIf_UserIterType                 ownerIdx;
        boolean                            isReceivedByUser;
        EthIf_RxFrameHandlingType          rxFrameHandling;

  /* PRQA S 0310 1 */ /* MD_EthIf_310_Buffer */
  u8DataPtr        = (P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR))dataPtr;
  isReceivedByUser = FALSE;

  /* #10 Trigger header extraction */
  EthIf_ExtractRxEthHeader(frameType, lenByte, physAddrPtr, u8DataPtr, &rxFrameHandling);                               /* SBSW_ETHIF_INT_FCT_PARAM_PTR_PASS_AND_REF_OF_STACK_VAR */

  /* #20 Trigger check if frame is allowed to be received */
  if( EthIf_IsRxAllowed(ethCtrlIdx,
                        &ethIfCtrlIdx,
                        (P2CONST(EthIf_FrameHdrType, AUTOMATIC, ETHIF_APPL_DATA))&rxFrameHandling.FrameHdr,
                        rxFrameHandling.EthIfLayerPayloadPtr,
                        rxFrameHandling.EthIfLayerPayloadLen) == TRUE )                                                 /* SBSW_ETHIF_INT_FCT_PARAM_PTR_PASS_AND_REF_OF_STACK_VAR */
  {
#if ( ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE != ETHIF_NO_EXTENDED_TRAFFIC_HANDLING )                                      /* COV_ETHIF_QM_FEAT_CHECK_ON */
    /* #200 Invoke mirroring/gatway sub modules to check if frame is allowed to be passed to the upper layers */
    boolean passFrameToUl = EthIf_InvokeRxTrafficHandling(ethIfCtrlIdx, &rxFrameHandling);                              /* SBSW_ETHIF_REF_OF_STACK_VAR */

    if( passFrameToUl == TRUE )
    {
#endif /* ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE */
      /* #2000 Try to pass the frame to a upper layer */
      EthIf_UlRxIndiactionDataType rxIndData;

      rxIndData.EthIfCtrlIdx = ethIfCtrlIdx;
      rxIndData.EtherType    = rxFrameHandling.EthIfLayerFrameType;
      rxIndData.IsBroadcast  = isBroadcast;
      rxIndData.SrcMacPtr    = physAddrPtr;
      rxIndData.PayloadPtr   = rxFrameHandling.EthIfLayerPayloadPtr;
      rxIndData.PayloadLen   = rxFrameHandling.EthIfLayerPayloadLen;

      ownerIdx = EthIf_QueryForFrameOwner(rxIndData.EtherType);

      isReceivedByUser = EthIf_HandleUlRxIndication(ownerIdx, &rxIndData);                                              /* SBSW_ETHIF_REF_OF_STACK_VAR */

      /* #2010 Check if there was at least one upper layer the frame could be passed to */
      if( isReceivedByUser == TRUE )
      {
        /* #20100 Update reception statistics */
        EthIf_UpdateRxStats(ethIfCtrlIdx, rxIndData.PayloadLen);
        /* #20110 Invoke the switch handling sub-modules to be able to process switch information indications
         *        later on if user is registered for */
        EthIf_InvokeRxSwtHandling(ethCtrlIdx, ownerIdx, &rxIndData); /*lint !e522 */                                    /* SBSW_ETHIF_REF_OF_STACK_VAR */
      }
#if ( ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE != ETHIF_NO_EXTENDED_TRAFFIC_HANDLING )                                      /* COV_ETHIF_QM_FEAT_CHECK_ON */
    }
#endif /* ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE */
  }
  /* #30 Invoke the ZeroCopy sub-module to be able to handle buffer release correctly */
  EthIf_InvokeZeroCopyHandling(isReceivedByUser, ethIfCtrlIdx, ethCtrlIdx, &rxFrameHandling); /*lint !e522 */           /* SBSW_ETHIF_REF_OF_STACK_VAR */

} /* EthIf_Internal_RxIndication() */ /* PRQA S 6050, 6060 */ /* MD_MSR_STCAL, MD_MSR_STPAR */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthIf_RxIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, ETHIF_CODE) EthIf_RxIndication(
        uint8                                     CtrlIdx,
        Eth_FrameType                             FrameType,
        boolean                                   IsBroadcast,
  P2VAR(uint8,        AUTOMATIC, ETHIF_APPL_VAR)  PhysAddrPtr,
  P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR)  DataPtr,
        uint16                                    LenByte)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHIF_E_NO_ERROR;
  EthIf_EthCtrlIterType ethCtrlIdx = EthIf_QueryForEthIfEthCtrl(CtrlIdx);

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393652 */
    /* \trace SPEC-2393657 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( ethCtrlIdx >= EthIf_GetSizeOfEthCtrl() )
  {
    /* \trace SPEC-2393653 */
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else if( (IsBroadcast != FALSE) &&
           (IsBroadcast != TRUE)     )
  {
    errorId = ETHIF_E_INV_PARAM;
  }
  else if( PhysAddrPtr == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else if( DataPtr == NULL_PTR )
  {
    /* \trace SPEC-2393654 */
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
#endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Trigger frame reception */
    EthIf_Internal_RxIndication((uint8)ethCtrlIdx, FrameType, IsBroadcast, PhysAddrPtr, DataPtr, LenByte);                        /* SBSW_ETHIF_INT_FCT_PUB_PARAM_PTR_PASS */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_RX_INDICATION, errorId);
  }
#else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
#endif

} /* EthIf_RxIndication() */ /* PRQA S 6060, 6080 */ /* MD_MSR_STPAR, MD_MSR_STMIF */

/**********************************************************************************************************************
*  EthIf_MainFunctionRx
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
FUNC(void, ETHIF_CODE) EthIf_MainFunctionRx( void )
{
  /* #10 If feature receive polling is enabled */
  /* \trace SPEC-2393667 */
#if ( ETHIF_ENABLE_RX_INTERRUPT == STD_OFF )
  /* #20 Check if module is initialized */
  if ( EthIf_ModuleInitialized == ETHIF_STATE_INIT )
  {
    EthIf_EthCtrlIterType ethCtrlIdx;
    boolean               moreFramesPresent;

    for( ethCtrlIdx = 0;
         ethCtrlIdx < EthIf_GetSizeOfEthCtrl();
         ethCtrlIdx++ )
    {
      EthIf_SetEthCtrlRxFrameCnt(ethCtrlIdx, EthIf_GetMaxFrameRxPerEthCtrl());                                          /* SBSW_ETHIF_COMMON_CSL03 */
    }

    /* #30 Poll for frames to be received until no more frames are available
     *     or the maximum count of frames per Ethernet controller is reached */
    do
    {
      moreFramesPresent = FALSE;

      /* #300 Receive polling for each Eth controller used */
      /* (this is done for each run of the outer loop to serve the controllers equally and
       *  prevent one controller from stressing the reception so the others wouldn't be served) */
      for( ethCtrlIdx = 0;
           ethCtrlIdx < EthIf_GetSizeOfEthCtrl();
           ethCtrlIdx++ )
      {
        /* #3000 Check if controller is active and frame limit isn't reached yet */
        if( (EthIf_GetEthCtrlModeCnt(ethCtrlIdx) > 0u) && (EthIf_GetEthCtrlRxFrameCnt(ethCtrlIdx) > 0u) )
        {
          EthIf_EthDrvApiIdxOfEthCtrlType ethDrvApiIdx = EthIf_GetEthDrvApiIdxOfEthCtrl(ethCtrlIdx);
          Eth_RxStatusType rxStatus = ETH_NOT_RECEIVED;

          /* #30000 Trigger frame reception */
          EthIf_GetReceiveOfEthDrvApi(ethDrvApiIdx)(EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                    &rxStatus);                                                         /* SBSW_ETHIF_DRVAPI_FCT_PTR_MAN_WITH_REF_OF_STACK_VAR_PARAM_PTR_CSL03 */

          EthIf_DecEthCtrlRxFrameCnt(ethCtrlIdx);                                                                       /* SBSW_ETHIF_COMMON_CSL03 */

          /* #30010 Check if an additional run must be performed and trigger run if necessary */
          if( (rxStatus == ETH_RECEIVED_MORE_DATA_AVAILABLE) && (EthIf_GetEthCtrlRxFrameCnt(ethCtrlIdx) != 0u) )
          {
              /* there are more frames present */
              moreFramesPresent = TRUE;
          }
        }
      }
    }
    while ( moreFramesPresent == TRUE ); /* more frames available for reception? */
    /* \trace SPEC-2393668 */
  }
#endif /* ETHIF_ENABLE_RX_INTERRUPT */
} /* EthIf_MainFunctionRx() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

#define ETHIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_Rx.c
 *********************************************************************************************************************/

