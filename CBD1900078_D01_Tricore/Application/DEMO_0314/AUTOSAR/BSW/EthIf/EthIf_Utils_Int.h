/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  EthIf_Utils_Int.h
 *        \brief  EthIf Utils internal header file
 *
 *      \details  Provides access to types/functions/data of the sub-module Utils of EthIf only to be used internally,
 *                where functions are intended to be linked by linker.
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

#if !defined (ETHIF_UTILS_INT_H)
# define ETHIF_UTILS_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_Utils_Types_Int.h"

# include "EthIf.h"      /* access to DET error IDs */
# include "EthIf_Int.h"  /* access to components/utils shared with all EthIf modules */

/*********************************************************************************************************
 * Predefined file includes based on usage of other components/sub-modules within this sub-module
 * defined in \trace DSGN-EthIfDiag1937
 *********************************************************************************************************/
/* No dependency to other components/sub-modules */

/*********************************************************************************************************
 * Predefined file includes based on usage of this sub-module by other components/sub-modules
 * defined in \trace DSGN-EthIfDiag1937
 *********************************************************************************************************/
# include "EthIf_Rx_Types_Int.h"
# include "EthIf_Tx_Types_Int.h"
# include "EthIf_ZeroCopy_Types_Int.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# if !defined (ETHIF_UTILS_INT_LOCAL)                                                                                   /* COV_ETHIF_LOCAL_INLINE */
#  define ETHIF_UTILS_INT_LOCAL static
# endif

# if !defined (ETHIF_UTILS_INT_LOCAL_INLINE)                                                                            /* COV_ETHIF_LOCAL_INLINE */
#  define ETHIF_UTILS_INT_LOCAL_INLINE LOCAL_INLINE
# endif

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

# define ETHIF_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  EthIf_QueryForEthIfEthCtrl
 *********************************************************************************************************************/
/*! \brief          Queries for the EthIf  Eth controller
 *  \details        This function queries for the EthIf Eth controller by taking the symbolic name value of the
 *                  respective Ethernet controller.
 *  \param[in]      snvEth  Symbolic name value of the Ethernet controller
 *  \return         EthIf_GetSizeOfEthCtrl() - represents the first invalid EthIf Eth controller index
 *                                             -> no EthIf Eth controller found
 *  \return         other values - EthIf Eth controller index
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(EthIf_EthCtrlIterType, ETHIF_UTILS_INLINE_CODE) EthIf_QueryForEthIfEthCtrl( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  uint8  snvEth);

/**********************************************************************************************************************
 *  EthIf_QueryForEthIfController
 *********************************************************************************************************************/
/*! \brief          Queries for the EthIf controller
 *  \details        This function queries for the EthIf controller by taking the related Ethernet controller, information
 *                  if EthIf controller shall represent a non-tagged or tagged data path and in case of a tagged data path
 *                  by taking the VLAN ID.
 *  \param[in]      ethCtrlIdx  Ethernet controller index
 *  \param[in]      vlanId      VLAN ID that shall be used in case no VLAN is used ETHIF_INV_VLAN_ID
 *  \return         EthIf_GetSizeOfEthIfCtrl() - represents the first invalid EthIf controller index
 *                                               -> no EthIf controller found
 *  \return         other values - EthIf controller index
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(EthIf_EthIfCtrlIterType, ETHIF_UTILS_INLINE_CODE) EthIf_QueryForEthIfController( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthCtrlIterType  ethCtrlIdx,
  uint16                 vlanId);

/**********************************************************************************************************************
 *  EthIf_QueryForFrameOwner
 *********************************************************************************************************************/
/*! \brief          Queries for the owner of the EtherType
 *  \details        This function queries for the owner of the EtherType asked for.
 *  \param[in]      etherType   EtherType the owner shall be found for
 *  \return         EthIf_GetSizeOfUser() - represents the first invalid owner index
 *                                          -> no owner for EtherType found
 *  \return         other values - owner index
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(EthIf_UserIterType, ETHIF_UTILS_INLINE_CODE) EthIf_QueryForFrameOwner( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  Eth_FrameType etherType);

# if (( ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT == STD_ON ) || ( ETHIF_ETHSWT_TIME_STAMP_SUPPORT == STD_ON ))             /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 *  EthIf_GetFrameId
 *********************************************************************************************************************/
/*! \brief          Retrieves the frame identifier contained in the Ethernet frame buffer
 *  \details        -
 *  \param[in]      dataPtr     Pointer to the Ethernet frame TX buffer
 *  \param[in]      payloadLen  Length of the Ethernet frame payload
 *  \return         Frame identifier contained in the Ethernet frame buffer
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(Eth_FrameIdType, ETHIF_UTILS_INLINE_CODE) EthIf_GetFrameId( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA) dataPtr,
          uint16                             payloadLen);
# endif

/**********************************************************************************************************************
 *  EthIf_GetMaxTxBufIdxForEthCtrl
 *********************************************************************************************************************/
/*! \brief          Returns the maximum allowed TX buffer index for a Ethernet controller
 *  \details        -
 *  \param[in]      ethCtrlIdx  Ethernet controller
 *                              [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \return         maximum buffer index
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(uint8, ETHIF_TX_INLINE_CODE) EthIf_GetMaxTxBufIdxForEthCtrl( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthCtrlIterType  ethCtrlIdx);

/**********************************************************************************************************************
 *  EthIf_GetMaxTxBufIdxForEthIfCtrl
 *********************************************************************************************************************/
/*! \brief          Returns the maximum allowed TX buffer index for a EthIf controller
 *  \details        -
 *  \param[in]      ethIfCtrlIdx  Ethernet controller
 *                                [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \return         maximum buffer index
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(uint8, ETHIF_TX_INLINE_CODE) EthIf_GetMaxTxBufIdxForEthIfCtrl( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx);

/**********************************************************************************************************************
 *  EthIf_CalcTxCtxtIdx
 *********************************************************************************************************************/
/*! \brief          Calculates the index to access EthIf_TxContext array using ComStackLib
 *  \details        -
 *  \param[in]      ethCtrlIdx  Ethernet controller
 *                              [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \param[in]      bufIdx      Ethernet TX buffer
 *                              [range: bufIdx <= EthIf_GetMaxTxBufIdxForEthCtrl(ethCtrlIdx)]
 *  \return         index for EthIf_TxContext array [range: 0 < EthIf_GetSizeOfTxContext()]
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(EthIf_TxContextIterType, ETHIF_TX_INLINE_CODE) EthIf_CalcTxCtxtIdx( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthCtrlIterType  ethCtrlIdx,
  uint8                  bufIdx);

# if !defined(ETHIF_UNIT_TEST)                                                                                          /* COV_ETHIF_UNIT_TEST */
/**********************************************************************************************************************
 *  EthIf_QueryForEthIfEthCtrl
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(EthIf_EthCtrlIterType, ETHIF_UTILS_INLINE_CODE) EthIf_QueryForEthIfEthCtrl( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  uint8  snvEth)
{
  EthIf_EthCtrlIterType ethCtrlIdx;
  EthIf_EthCtrlIterType queriedEthCtrlIdx = EthIf_GetSizeOfEthCtrl();

  /* #10 Query over all EthIf Eth controllers and check for a matching symbolic name value. If there is a match return
   *     the EthIf Eth controller index, otherwise return the first invalid index. */
  for( ethCtrlIdx = 0; ethCtrlIdx < EthIf_GetSizeOfEthCtrl(); ethCtrlIdx++ )
  {
    if( snvEth == EthIf_GetSnvOfEthCtrl(ethCtrlIdx) )
    {
      queriedEthCtrlIdx = ethCtrlIdx;
      break;
    }
  }

  return queriedEthCtrlIdx;
} /* EthIf_QueryForEthIfEthCtrl() */

/**********************************************************************************************************************
 *  EthIf_QueryForEthIfController
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
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(EthIf_EthIfCtrlIterType, ETHIF_UTILS_INLINE_CODE) EthIf_QueryForEthIfController( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthCtrlIterType  ethCtrlIdx,
  uint16                 vlanId)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_EthIfCtrlIterType queriedEthIfCtrlIdx;

  /* ----- Implementation ----------------------------------------------- */
  queriedEthIfCtrlIdx = EthIf_GetSizeOfEthIfCtrl();

  /* #10 Check if controller represents un-tagged data path */
  if( vlanId == ETHIF_INV_VLAN_ID )
  {
    EthIf_EthIfCtrlEndIdxOfEthCtrlType ethCtrlEthIfCtrlIdx;

    /* #100 If un-tagged data path EthIf controller exists it is placed at first position of the EthIf controller
     *      group for the Eth controller queried for -> get the element and check if it is the one searched for */
    ethCtrlEthIfCtrlIdx = EthIf_GetEthIfCtrlStartIdxOfEthCtrl(ethCtrlIdx);

    if( EthIf_GetTypeOfEthIfCtrl(ethCtrlEthIfCtrlIdx) == ETHIF_ETHIFCTRL_TYPE_PHYSICAL_TYPEOFETHIFCTRL )
    {
      queriedEthIfCtrlIdx = ethCtrlEthIfCtrlIdx;
    }
  }
  /* #20 Otherwise (tagged data path) */
  else
  {
    EthIf_EthIfCtrlIterType ethIfCtrlIdx;

    /* #200 Query within the EthIf controller group for the Ethernet controller for a matching VLAN ID
     *      which results in retrieving the searched EthIf controller */
    for( ethIfCtrlIdx = EthIf_GetEthIfCtrlStartIdxOfEthCtrl(ethCtrlIdx);
         ethIfCtrlIdx < EthIf_GetEthIfCtrlEndIdxOfEthCtrl(ethCtrlIdx);
         ethIfCtrlIdx++ )
    {
      if( EthIf_GetTypeOfEthIfCtrl(ethIfCtrlIdx) != ETHIF_ETHIFCTRL_TYPE_PHYSICAL_TYPEOFETHIFCTRL )
      {
        if( EthIf_GetVlanIdOfEthIfCtrl(ethIfCtrlIdx) == vlanId )
        {
          /* match */
          queriedEthIfCtrlIdx = ethIfCtrlIdx;
          break;
        }
      }
    }
  }

  return queriedEthIfCtrlIdx;
} /* EthIf_QueryForEthIfController() */

/**********************************************************************************************************************
 *  EthIf_QueryForFrameOwner
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(EthIf_UserIterType, ETHIF_UTILS_INLINE_CODE) EthIf_QueryForFrameOwner( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  uint16 etherType)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_UserIterType queriedOwnerIdx;
  EthIf_UserIterType userIdx;

  /* ----- Implementation ----------------------------------------------- */
  queriedOwnerIdx = EthIf_GetSizeOfUser();

  /* #10 For each owner */
  for( userIdx = 0u;
       userIdx < EthIf_GetSizeOfUser();
       userIdx++ )
  {
    /* #100 Check if EtherType of owner matches the EtherType queried for */
    if ( EthIf_GetEtherTypeOfUser(userIdx) == etherType )
    {
      /* #1000 EtherType matched -> owner found */
      queriedOwnerIdx = userIdx;
      break;
    }
  }

  return queriedOwnerIdx;
} /* EthIf_QueryForFrameOwner() */

#  if (( ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT == STD_ON ) || ( ETHIF_ETHSWT_TIME_STAMP_SUPPORT == STD_ON ))            /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 *  EthIf_GetFrameId
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(Eth_FrameIdType, ETHIF_UTILS_INLINE_CODE) EthIf_GetFrameId( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA) dataPtr,
          uint16                             payloadLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR) frameIdPtr;
        Eth_FrameIdType                   frameId;
        uint8_least                       frameIdByteIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Retrieve the frame identifier from the Ethernet frame buffer */
  frameIdPtr = (P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR))&frameId; /* PRQA S 0310 */ /* Byte access needed to avoid mis-aligned access on specific platforms. */
  for( frameIdByteIdx = 0;
       frameIdByteIdx < sizeof(Eth_FrameIdType);
       frameIdByteIdx++ )
  {
    frameIdPtr[frameIdByteIdx] = dataPtr[payloadLen + frameIdByteIdx];                                                  /* SBSW_ETHIF_FRAME_ID_PTR_WRITE */
  }

  return frameId;
} /* EthIf_GetFrameId() */
#  endif

/**********************************************************************************************************************
 *  EthIf_GetMaxTxBufIdxForEthCtrl
 *********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
*/
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(uint8, ETHIF_TX_INLINE_CODE) EthIf_GetMaxTxBufIdxForEthCtrl( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthCtrlIterType  ethCtrlIdx)
{
  /* #10 Calculate the maximum allowed TX buffer index by the range defined for the TX buffers of the Ethernet controller
   *     by the EthIf_TxContext inderections mapped by ComStackLib. */
  return (uint8)((sint16)EthIf_GetTxContextEndIdxOfEthCtrl(ethCtrlIdx)
                    - (sint16)EthIf_GetTxContextStartIdxOfEthCtrl(ethCtrlIdx));
} /* EthIf_GetMaxTxBufIdxForEthCtrl */

/**********************************************************************************************************************
 *  EthIf_GetMaxTxBufIdxForEthIfCtrl
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(uint8, ETHIF_TX_INLINE_CODE) EthIf_GetMaxTxBufIdxForEthIfCtrl( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthIfCtrlIterType  ethIfCtrlIdx)
{
  /* #10 Retrieve mapped Eth controller and trigger retrieval of maximum TX buffer index for it */
  return EthIf_GetMaxTxBufIdxForEthCtrl(EthIf_GetEthCtrlIdxOfEthIfCtrl(ethIfCtrlIdx));
} /* EthIf_GetMaxTxBufIdxForEthIfCtrl */

/**********************************************************************************************************************
 *  EthIf_CalcTxCtxtIdx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHIF_UTILS_INT_LOCAL_INLINE FUNC(EthIf_TxContextIterType, ETHIF_TX_INLINE_CODE) EthIf_CalcTxCtxtIdx( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  EthIf_EthCtrlIterType  ethCtrlIdx,
  uint8                  bufIdx)
{
  return EthIf_GetTxContextStartIdxOfEthCtrl(ethCtrlIdx) + bufIdx;
} /* EthIf_CalcTxCtxtIdx */
# endif /* ETHIF_UNIT_TEST */

/**********************************************************************************************************************
 *  EthIf_Utils_Init
 *********************************************************************************************************************/
/*! \brief          Initializes the EthIf Utils sub-module
 *  \details        -
 *  \pre            Configuration pointer must have been initialized
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_Utils_Init( void );

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_19.1 */

#endif /* ETHIF_UTILS_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_Utils_Int.h
 *********************************************************************************************************************/

