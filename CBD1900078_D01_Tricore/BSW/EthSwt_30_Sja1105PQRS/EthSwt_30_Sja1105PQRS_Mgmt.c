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
/*!        \file  EthSwt_30_Sja1105PQRS_Mgmt.c
 *        \brief  Source file containing the frame management API
 *
 *      \details  The Ethernet Switch Driver allows to manage special frames (like PTP frames) received at it's ports.
 *                Additionally frames can be adapted with management information to achieve transmission only on
 *                selected ports.
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

#define ETHSWT_30_SJA1105PQRS_MGMT_SOURCE

/* QAC file deviation */
/* PRQA S 0857 ETHSWT_30_SJA1105PQRS_NO_OF_MACROS */ /* MD_MSR_1.1_857 */
/* PRQA S 779,777 IDENTIFIER_DIFFER */ /* MD_EthSwt_30_Sja1105PQRS_5.1 */
/* PRQA S 0781 EOF */ /* MD_EthSwt_30_Sja1105PQRS_781 */
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "EthSwt_30_Sja1105PQRS_Mgmt.h"
#include "EthSwt_30_Sja1105PQRS.h"
#include "EthSwt_30_Sja1105PQRS_Int.h"
#include "EthSwt_30_Sja1105PQRS_Lcfg.h"
#include "EthSwt_30_Sja1105PQRS_Regs.h"
#include "EthSwt_30_Sja1105PQRS_Time_Int.h"
#include "EthSwt_30_Sja1105PQRS_Casc_Int.h"

#if ( ETHSWT_30_SJA1105PQRS_MANAGEMENT_SUPPORT == STD_ON )
#include "SchM_EthSwt_30_Sja1105PQRS.h"
#include "IpBase.h"
#include "EthIf_Cbk.h"

# if ( ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON )
#include "Det.h"
# endif /* ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of EthSwt_30_Sja1105PQRS header file */
#if (  (ETHSWT_30_SJA1105PQRS_SW_MAJOR_VERSION != (0x05U)) \
    || (ETHSWT_30_SJA1105PQRS_SW_MINOR_VERSION != (0x00U)) \
    || (ETHSWT_30_SJA1105PQRS_SW_PATCH_VERSION != (0x01U)) )
# error "Vendor specific version numbers of EthSwt_30_Sja1105PQRS_Mgmt.c and EthSwt_30_Sja1105PQRS.h are inconsistent"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/
#if !defined (ETHSWT_LOCAL)
# define ETHSWT_LOCAL static
#endif

#if !defined (ETHSWT_LOCAL_INLINE)
# define ETHSWT_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/

#define ETHSWT_30_SJA1105PQRS_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/* PRQA S 3218 2 */ /* MD_EthSwt_30_Sja1105PQRS_3218 */
ETHSWT_LOCAL ETHSWT_VAR(Eth_FrameIdType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_LastManagedRxFrameId;
ETHSWT_LOCAL ETHSWT_P2VAR(uint8, SJA1105PQRS) EthSwt_30_Sja1105PQRS_LastManagedRxDataPtr;
#define ETHSWT_30_SJA1105PQRS_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define ETHSWT_30_SJA1105PQRS_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
ETHSWT_LOCAL ETHSWT_VAR(uint8, SJA1105PQRS) EthSwt_30_Sja1105PQRS_MetaFramePending;
#define ETHSWT_30_SJA1105PQRS_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_GetFreeRxMgmtElement
 **********************************************************************************************************************/
/*! \brief       Retrieves a reception frame management element and pushes it on the element stack
 *  \details     -
 *  \param[in]   swtCfg                     Switch the management element shall be retrieved for
 *  \param[in]   mgmtElem                   Retrieved management element
 *  \return      E_NOT_OK                   No free management element found
 *  \return      E_OK                       Management element found and allocated
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetFreeRxMgmtElement(
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType,                        SJA1105PQRS) swtCfg,
    ETHSWT_P2VAR(ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_RxMgmtDataType, SJA1105PQRS), SJA1105PQRS) mgmtElem);

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_GetRxMgmtElement
 **********************************************************************************************************************/
/*! \brief       Retrieves the latest reception management element on the element stack
 *  \details     -
 *  \param[in]   swtCfg                     Switch the management element is active for
 *  \param[in]   mgmtElem                   Retrieved management element
 *  \return      E_NOT_OK                   Management element couldn't be retrieved
 *  \return      E_OK                       Management element retrieved
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetRxMgmtElement(
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType,                        SJA1105PQRS) swtCfg,
    ETHSWT_P2VAR(ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_RxMgmtDataType, SJA1105PQRS), SJA1105PQRS) mgmtElem);

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_ReleaseRxMgmtElement
 **********************************************************************************************************************/
/*! \brief       Releases the latest reception management element and remove it from element stack
 *  \details     -
 *  \param[in]   swtCfg                     Switch the management element is active for
 *  \param[in]   mgmtElem                   Management element to be released
 *  \return      E_NOT_OK                   Management element couldn't be released
 *  \return      E_OK                       Management element released
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_ReleaseRxMgmtElement(
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS) swtCfg,
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_RxMgmtDataType,       SJA1105PQRS) mgmtElem );

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_AllocateFreeTxMgmtElement
 **********************************************************************************************************************/
/*! \brief       Allocates a transmission management element
 *  \details     -
 *  \param[in]   swtCfg                     Switch the management element is active for
 *  \param[in]   bufIdx                     Frame buffer identifier the element shall be allocated for
 *  \param[in]   frameId                    Management information
 *  \return      E_NOT_OK                   Management element couldn't be allocated
 *  \return      E_OK                       Management element allocated
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_AllocateFreeTxMgmtElement(
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS) swtCfg,
                 uint8                                                  bufIdx,
                 Eth_FrameIdType                                        frameId);

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_GetTxMgmtElement
 **********************************************************************************************************************/
/*! \brief       Retrieves a transmission management element
 *  \details     -
 *  \param[in]   swtCfg                     Switch the management element is active for
 *  \param[in]   bufIdx                     Frame buffer identifier the element is related to
 *  \param[in]   frameId                    Frame ID the element is related to
 *  \param[out]  mgmtElem                   Retrieved management element
 *  \return      E_NOT_OK                   Management element couldn't be retrieved
 *  \return      E_OK                       Management element retrieved
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetTxMgmtElement(
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType,                        SJA1105PQRS) swtCfg,
                 uint8                                                                         bufIdx,
                 Eth_FrameIdType                                                               frameId,
    ETHSWT_P2VAR(ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_TxMgmtDataType, SJA1105PQRS), SJA1105PQRS) mgmtElem);

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_ReleaseTxMgmtElement
 **********************************************************************************************************************/
/*! \brief       Releases the given transmission management element
 *  \details     -
 *  \param[in]   mgmtElem                   Management element to be released
 *  \param[in]   MgmtInfo                   Management information
 *  \return      E_NOT_OK                   Management element couldn't be released
 *  \return      E_OK                       Management element released
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_ReleaseTxMgmtElement(
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_TxMgmtDataType,       SJA1105PQRS) mgmtElem );

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_IsMgmtDestMac
 **********************************************************************************************************************/
/*! \brief       Checks if the given destination MAC address identifies frames to be managed
 *  \details     -
 *  \param[in]   swtCfg                     Switch the management element is active for
 *  \param[in]   destMac                    Destination MAC address to check
 *  \return      FALSE                      MAC address does not belong to management frame
 *  \return      TRUE                       MAC address belongs to management frame
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_IsMgmtDestMac(
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS) swtCfg,
  ETHSWT_P2CONST(uint8,                                    SJA1105PQRS) destMac);

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_IsMetaFrame
 **********************************************************************************************************************/
/*! \brief       Checks if given MAC address is used for META frames
 *  \details     -
 *  \param[in]   swtCfg                     Switch the management element is active for
 *  \param[in]   srcMac                     MAC address of frame
 *  \return      FALSE                      MAC address does not belong to META frame
 *  \return      TRUE                       MAC address is used for META frames
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_IsMetaFrame(
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS) swtCfg,
  ETHSWT_P2CONST(uint8,                                    SJA1105PQRS) srcMac);

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_GetFrameId
 **********************************************************************************************************************/
/*! \brief       Extracts the frame id from the Ethernet frame.
 *  \details     -
 *  \param[in]   DataPtr                    DataPtr to Payload
 *  \param[in]   Len                        Length of the Ethernet frame payload
 *  \return      FrameId                    Frame ID of Ethernet frame
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(Eth_FrameIdType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetFrameId(
    ETHSWT_P2CONST(uint8, SJA1105PQRS) DataPtr,
                   uint16                  Len);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_GetFrameId
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(Eth_FrameIdType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetFrameId(
    ETHSWT_P2CONST(uint8, SJA1105PQRS) DataPtr,
                   uint16                  Len)
{
  /*- #10 Extract the frame id from the Ethernet frame while taking care of misaligned memory access */
  Eth_FrameIdType FrameId;
  Eth_FrameIdType* FrameIdPtr = &FrameId;
  FrameId = 0; /* Only for MISRA... */

  /* PRQA S 0310 2 */ /* MD_EthSwt_30_Sja1105PQRS_0310_FrameId */
  ((uint8*)FrameIdPtr)[0] = DataPtr[Len];
  ((uint8*)FrameIdPtr)[1] = DataPtr[Len + 1];
  return FrameId;
} /* EthSwt_30_Sja1105PQRS_GetFrameId() */

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_GetFreeRxMgmtElement
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetFreeRxMgmtElement(
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType,                        SJA1105PQRS) swtCfg,
    ETHSWT_P2VAR(ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_RxMgmtDataType, SJA1105PQRS), SJA1105PQRS) mgmtElem)
{
  /* ----- Local data declaration --------------------------------------- */
  uint8           stackPos;
  Std_ReturnType  retVal;

  /* ----- Development Error Checks ------------------------------------- */

  /* ----- Local data definition ---------------------------------------- */
  retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Ensure consistency of reception management processing elements and stack) */
  /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_EnterExclusiveArea(Sja1105PQRS, RX_MNGMT_ELEMENT_PROCESSING);

  stackPos = (*swtCfg->FrameManagement->RxMgmtDataStackPos);

  /* #20 Get next free element on stack */
  do
  {
    (*mgmtElem) = &swtCfg->FrameManagement->RxMgmtData[stackPos];
    stackPos++;
  }
  while( ( (*mgmtElem)->IsInUse == TRUE ) &&
         ( stackPos < swtCfg->FrameManagement->RxMgmtDataNum ) );

  /* #30 Ensure that stack hasn't overflowed, if not -> push a new element on the stack and adapt the
   *     stack pointer */
  if( stackPos < swtCfg->FrameManagement->RxMgmtDataNum )
  {
    /* adapt stack position, provide element and lock it */
    stackPos -= (uint8)1u;

    (*swtCfg->FrameManagement->RxMgmtDataStackPos) = stackPos;

    (*mgmtElem)->IsInUse = TRUE;
    retVal               = E_OK;
  }
#if ( ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON )
  else
  {
    EthSwt_CallDetReportError(                              \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,              \
        ETHSWT_30_SJA1105PQRS_SID_INTERNAL_FRAME_MNGMT_API, \
        ETHSWT_30_SJA1105PQRS_E_INTERNAL_ERROR);
  }
#endif /* ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT */

  /* #40 Leave exclusive area */
  /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_ExitExclusiveArea(Sja1105PQRS, RX_MNGMT_ELEMENT_PROCESSING);

  return retVal;
} /* EthSwt_30_Sja1105PQRS_GetFreeRxMgmtElement() */

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_GetRxMgmtElement
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetRxMgmtElement(
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType,                        SJA1105PQRS) swtCfg,
    ETHSWT_P2VAR(ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_RxMgmtDataType, SJA1105PQRS), SJA1105PQRS) mgmtElem)
{
  /* ----- Local data declaration --------------------------------------- */
  uint8           stackPos;
  Std_ReturnType  retVal;

  /* ----- Development Error Checks ------------------------------------- */

  /* ----- Local data definition ---------------------------------------- */
  retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Ensure consistency of reception management processing elements and stack) */
  /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_EnterExclusiveArea(Sja1105PQRS, RX_MNGMT_ELEMENT_PROCESSING);

  /* #20 Get current stack position */
  stackPos = (*swtCfg->FrameManagement->RxMgmtDataStackPos);

  /* #30 Ensure that stack hasn't overflowed and if not get the current element from stack */
  if( stackPos < swtCfg->FrameManagement->RxMgmtDataNum )
  {
    if( swtCfg->FrameManagement->RxMgmtData[stackPos].IsInUse == TRUE )
    {
      /* retrieve element */
      (*mgmtElem) = &swtCfg->FrameManagement->RxMgmtData[stackPos];
      retVal       = E_OK;
    }
  }
#if ( ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON )
  else
  {
    EthSwt_CallDetReportError(                              \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,              \
        ETHSWT_30_SJA1105PQRS_SID_INTERNAL_FRAME_MNGMT_API, \
        ETHSWT_30_SJA1105PQRS_E_INTERNAL_ERROR);
  }
#endif /* ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT */

  /* #40 Leave exclusive area */
  /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_ExitExclusiveArea(Sja1105PQRS, RX_MNGMT_ELEMENT_PROCESSING);

  return retVal;
} /* EthSwt_30_Sja1105PQRS_GetRxMgmtElement() */

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_ReleaseRxMgmtElement
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_ReleaseRxMgmtElement(
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  swtCfg,
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_RxMgmtDataType,       SJA1105PQRS)  mgmtElem )
{
  /* ----- Local data declaration --------------------------------------- */
  Std_ReturnType  retVal;

  /* ----- Development Error Checks ------------------------------------- */

  /* ----- Local data definition ---------------------------------------- */
  retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Ensure consistency of reception management processing elements and stack) */
  /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_EnterExclusiveArea(Sja1105PQRS, RX_MNGMT_ELEMENT_PROCESSING);

  /* #20 Check if element is in use, if so invalidate the element and pop it from stack */
  if( mgmtElem->IsInUse == TRUE )
  {
    /* release element */
    mgmtElem->IsInUse = FALSE;
    mgmtElem->MgmtInfo.PortIdx = ETHSWT_INVALID_PORT_IDX;
    mgmtElem->MgmtInfo.FrameId = ETH_INVALID_FRAME_ID;

    /* decrement stack position if stack bottom isn't reached yet */
    if( (*swtCfg->FrameManagement->RxMgmtDataStackPos) > 0u )
    {
      (*swtCfg->FrameManagement->RxMgmtDataStackPos) -= 1u;
    }
    retVal = E_OK;
  }
#if ( ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON )
  else
  {
    EthSwt_CallDetReportError(                              \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,              \
        ETHSWT_30_SJA1105PQRS_SID_INTERNAL_FRAME_MNGMT_API, \
        ETHSWT_30_SJA1105PQRS_E_INTERNAL_ERROR);
  }
#endif /* ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT */

  /* #30 Leave exclusive area */
  /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_ExitExclusiveArea(Sja1105PQRS, RX_MNGMT_ELEMENT_PROCESSING);

  return retVal;
} /* EthSwt_30_Sja1105PQRS_ReleaseRxMgmtElement() */

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_AllocateFreeTxMgmtElement
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_AllocateFreeTxMgmtElement(
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  swtCfg,
                 uint8                                                   bufIdx,
                 Eth_FrameIdType                                         frameId)
{
  /* ----- Local data declaration --------------------------------------- */
  uint8_least     elemIdx;
  Std_ReturnType  retVal;

  /* ----- Development Error Checks ------------------------------------- */

  /* ----- Local data definition ---------------------------------------- */
  retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Ensure consistency of transmission management processing elements) */
  /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_EnterExclusiveArea(Sja1105PQRS, TX_MNGMT_ELEMENT_PROCESSING);

  /* #20 Query for free tx management element, allocate it if found and report result to the caller */
  for( elemIdx = 0; elemIdx < swtCfg->FrameManagement->TxMgmtDataNum; elemIdx++ )
  {
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_TxMgmtDataType, SJA1105PQRS)  mgmtElem;

    mgmtElem = &swtCfg->FrameManagement->TxMgmtData[elemIdx];

    /* is element available? */
    if( mgmtElem->IsInUse == FALSE )
    {
      /* lock element for usage */
      mgmtElem->IsInUse     = TRUE;
      mgmtElem->ToBeManaged = FALSE;
      mgmtElem->BufferIdx   = bufIdx;
      mgmtElem->MgmtInfo.FrameId = frameId;
      retVal = E_OK;
      break;
    }
  }

#if ( ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON )
  if( retVal == E_NOT_OK )
  {
    EthSwt_CallDetReportError(                              \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,              \
        ETHSWT_30_SJA1105PQRS_SID_INTERNAL_FRAME_MNGMT_API, \
        ETHSWT_30_SJA1105PQRS_E_INTERNAL_ERROR);
  }
#endif /* ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT */

  /* #30 Leave exclusive area */
  /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_ExitExclusiveArea(Sja1105PQRS, TX_MNGMT_ELEMENT_PROCESSING);

  return retVal;
} /* EthSwt_30_Sja1105PQRS_AllocateFreeTxMgmtElement() */

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_GetTxMgmtElement
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetTxMgmtElement(
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType,                        SJA1105PQRS) swtCfg,
                 uint8                                                                         bufIdx,
                 Eth_FrameIdType                                                               frameId,
    ETHSWT_P2VAR(ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_TxMgmtDataType, SJA1105PQRS), SJA1105PQRS) mgmtElem)
{
  /* ----- Local data declaration --------------------------------------- */
  uint8_least     elemIdx;
  Std_ReturnType  retVal;

  /* ----- Development Error Checks ------------------------------------- */

  /* ----- Local data definition ---------------------------------------- */
  retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Ensure consistency of transmission management processing elements) */
  /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_EnterExclusiveArea(Sja1105PQRS, TX_MNGMT_ELEMENT_PROCESSING);

  /* #20 Query for the tx management element identified by the buffer identifier and return result to the caller */
  for( elemIdx = 0; elemIdx < swtCfg->FrameManagement->TxMgmtDataNum; elemIdx++ )
  {
    (*mgmtElem) = &swtCfg->FrameManagement->TxMgmtData[elemIdx];

    /* is searched element? */
    if( ((*mgmtElem)->BufferIdx        == bufIdx)  &&
        ((*mgmtElem)->MgmtInfo.FrameId == frameId)    )
    {
      if( (*mgmtElem)->IsInUse == TRUE )
      {
        retVal = E_OK;
        break;
      }
#if ( ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON )
      else
      {
        EthSwt_CallDetReportError(                           \
            ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,              \
            ETHSWT_30_SJA1105PQRS_SID_INTERNAL_FRAME_MNGMT_API, \
            ETHSWT_30_SJA1105PQRS_E_INTERNAL_ERROR);
      }
#endif /* ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT */
    }
  }

  /* #30 Leave exclusive area */
  /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_ExitExclusiveArea(Sja1105PQRS, TX_MNGMT_ELEMENT_PROCESSING);

  return retVal;
} /* EthSwt_30_Sja1105PQRS_GetTxMgmtElement() */

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_ReleaseTxMgmtElement
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_ReleaseTxMgmtElement(
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_TxMgmtDataType,      SJA1105PQRS)  mgmtElem )
{
  /* ----- Local data declaration --------------------------------------- */
  Std_ReturnType  retVal;

  /* ----- Development Error Checks ------------------------------------- */

  /* ----- Local data definition ---------------------------------------- */
  retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Ensure consistency of transmission management processing elements) */
  /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_EnterExclusiveArea(Sja1105PQRS, TX_MNGMT_ELEMENT_PROCESSING);

  /* #20 Invalidate the element if it is in use and return result to caller */
  if( mgmtElem->IsInUse == TRUE )
  {
    mgmtElem->IsInUse     = FALSE;
    mgmtElem->ToBeManaged = FALSE;
    mgmtElem->MgmtInfo.FrameId = ETH_INVALID_FRAME_ID;

    retVal = E_OK;
  }
#if ( ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON )
  else
  {
    EthSwt_CallDetReportError(                              \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,              \
        ETHSWT_30_SJA1105PQRS_SID_INTERNAL_FRAME_MNGMT_API, \
        ETHSWT_30_SJA1105PQRS_E_INTERNAL_ERROR);
  }
#endif /* ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT */

  /* #30 Leave exclusive area */
  /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_ExitExclusiveArea(Sja1105PQRS, TX_MNGMT_ELEMENT_PROCESSING);

  return retVal;
} /* EthSwt_30_Sja1105PQRS_ReleaseTxMgmtElement() */

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_IsMetaFrame
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_IsMetaFrame(
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS) swtCfg,
  ETHSWT_P2CONST(uint8,                                    SJA1105PQRS) srcMac)
{
  /* #10 Check destination MAC address against MAC address identifying the configured META frame address and provide
   *     result to the caller */

  /* PRQA S 0310 2 */ /* MD_EthSwt_30_Sja1105PQRS_0310_FrameId */
  return EthSwt_30_Sja1105PQRS_IsMacEqual(srcMac,
      (ETHSWT_P2CONST(uint8, SJA1105PQRS))swtCfg->FrameManagement->MetaFrameSrcMac);
} /* EthSwt_30_Sja1105PQRS_IsMgmtDestMac() */

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_IsMgmtDestMac
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_IsMgmtDestMac(
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS) swtCfg,
  ETHSWT_P2CONST(uint8,                                    SJA1105PQRS) destMac)
{
  boolean result;
  uint8_least destMacIdx;

  result = FALSE;

  /* #10 Check destination MAC address against list of MAC addresses identifying management frames and provide result
   *     to the caller */
  for( destMacIdx = 0; destMacIdx < swtCfg->FrameManagement->MgmtDestMacsNum; destMacIdx++ )
  {
    result = EthSwt_30_Sja1105PQRS_IsMacEqual(destMac,
        ((ETHSWT_P2CONST(uint8, SJA1105PQRS))swtCfg->FrameManagement->MgmtDestMacs[destMacIdx]));

    if( result == TRUE )
    {
      break;
    }
  }

  return result;
} /* EthSwt_30_Sja1105PQRS_IsMgmtDestMac() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/
#define ETHSWT_30_SJA1105PQRS_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_MgmtInit
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_MgmtInit( void )
{
  /* ----- Local data declaration --------------------------------------- */
  EthSwt_SwitchIdxType swtIdx;

  /* ----- Development Error Checks ------------------------------------- */

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 For each switch instance controlled by the driver */
  for( swtIdx = 0; swtIdx < (EthSwt_SwitchIdxType)ETHSWT_30_SJA1105PQRS_SWITCH_NUM; swtIdx++ )
  {
    ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  swtCfg;
                   uint8_least                                             elemIdx;

    swtCfg = &EthSwt_30_Sja1105PQRS_InstanceConfig[swtIdx];

    EthSwt_30_Sja1105PQRS_MetaFramePending = FALSE;

    /* #100 Initialize receive management variables */
    (*swtCfg->FrameManagement->RxMgmtDataStackPos) = 0u;

    for( elemIdx = 0; elemIdx < swtCfg->FrameManagement->RxMgmtDataNum; elemIdx++ )
    {
      swtCfg->FrameManagement->RxMgmtData[elemIdx].IsInUse = FALSE;
    }

    /* #110 Initialize transmit managment variables */
    for( elemIdx = 0; elemIdx < swtCfg->FrameManagement->TxMgmtDataNum; elemIdx++ )
    {
      swtCfg->FrameManagement->TxMgmtData[elemIdx].IsInUse  = FALSE;
    }

  }
} /* EthSwt_30_Sja1105PQRS_MgmtInit() */

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_GetSwitchManagementInstance
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetSwitchManagementInstance(
                 uint8                                                                               ethCtrlIdx,
    ETHSWT_P2VAR(ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS), SJA1105PQRS) swtCfg )
{
  /* ----- Local data declaration --------------------------------------- */
  EthSwt_SwitchIdxType swtIdx;
  Std_ReturnType       retVal;

  /* ----- Development Error Checks ------------------------------------- */

  /* ----- Local data definition ---------------------------------------- */
  retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Query for the switch management instance related to the Eth controller and return
   *     result to the caller */
  for( swtIdx = 0; swtIdx < ETHSWT_30_SJA1105PQRS_SWITCH_NUM; swtIdx++ )
  {
    uint8 CurCtrlIdx;

    CurCtrlIdx = EthSwt_30_Sja1105PQRS_InstanceConfig[swtIdx].FrameManagement->EthCtrlIdx;

    if( ethCtrlIdx == CurCtrlIdx )
    {
      (*swtCfg) = &EthSwt_30_Sja1105PQRS_InstanceConfig[swtIdx];
      retVal = E_OK;
      break;
    }
  }

  return retVal;
} /* EthSwt_30_Sja1105PQRS_GetSwitchManagementInstance() */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_EthRxProcessFrame
 *********************************************************************************************************************/
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
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_EthRxProcessFrame(
                 uint8                                           CtrlIdx,
    ETHSWT_P2VAR(ETHSWT_P2VAR(uint8, SJA1105PQRS),  SJA1105PQRS) DataPtr,  /* PRQA S 3673 */ /* MD_EthSwt_30_Sja1105PQRS_3673_AsrApi */
    ETHSWT_P2VAR(uint16,                            SJA1105PQRS) LengthPtr,  /* PRQA S 3673 */ /* MD_EthSwt_30_Sja1105PQRS_3673_AsrApi */
    ETHSWT_P2VAR(boolean,                           SJA1105PQRS) IsMgmtFrameOnlyPtr )
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  swtCfg;
                 Std_ReturnType                                          retVal;

  /* ----- Development Error Checks ------------------------------------- */

  /* ----- Local data definition ---------------------------------------- */
  retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Retrieve the switch instance responsible for managing the frame */
  if( EthSwt_30_Sja1105PQRS_GetSwitchManagementInstance(CtrlIdx, &swtCfg) == E_OK )
  {
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_RxMgmtDataType, SJA1105PQRS)  mgmtElem;

    ETHSWT_P2VAR(uint8, SJA1105PQRS) srcMacPtr;
    ETHSWT_P2VAR(uint8, SJA1105PQRS) destMacPtr;

    srcMacPtr =  &(*DataPtr)[ETHSWT_30_SJA1105PQRS_SRC_MAC_DATA_PTR_OFFSET];
    destMacPtr = &(*DataPtr)[ETHSWT_30_SJA1105PQRS_DEST_MAC_DATA_PTR_OFFSET];

    /* #20 Check if frame contains management information which later must be indicated to EthIf and its upper layers */
    if( EthSwt_30_Sja1105PQRS_IsMgmtDestMac(swtCfg, (ETHSWT_P2CONST(uint8, SJA1105PQRS))destMacPtr) == TRUE )
    {
      /* #200 Save all the information for the managed frame here, that will be needed later: DataPtr, FrameId */
      EthSwt_30_Sja1105PQRS_LastManagedRxFrameId = EthSwt_30_Sja1105PQRS_GetFrameId((*DataPtr), (*LengthPtr)); /* PRQA S 0310, 3305 */ /* MD_EthSwt_30_Sja1105PQRS_0310_FrameId, MD_EthSwt_30_Sja1105PQRS_3305_FrameId */
      EthSwt_30_Sja1105PQRS_LastManagedRxDataPtr = *DataPtr;
      *IsMgmtFrameOnlyPtr = FALSE;
      EthSwt_30_Sja1105PQRS_MetaFramePending = TRUE;
      retVal = E_OK;
    }
    /* #30 Check if frame contains a meta frame, which has to be analyzed and dropped */
    else if( EthSwt_30_Sja1105PQRS_IsMetaFrame(swtCfg, (ETHSWT_P2CONST(uint8, SJA1105PQRS))srcMacPtr) == TRUE )
    {
      if( EthSwt_30_Sja1105PQRS_MetaFramePending == TRUE )
      {
        EthSwt_30_Sja1105PQRS_MetaFramePending = FALSE;

        /* #300 retrieve a free element to store management information */
        if( EthSwt_30_Sja1105PQRS_GetFreeRxMgmtElement(swtCfg, &mgmtElem) == E_OK )
        {
          /* #3000 Save all the information from the META frame here, that will be needed later: PortIdx, SwitchIdx */
          EthSwt_30_Sja1105PQRS_MetaFrame *MetaFramePtr;
          ETHSWT_P2VAR(uint8, SJA1105PQRS) MetaInformationPtr;

          MetaInformationPtr = &(*DataPtr)[ETHSWT_30_SJA1105PQRS_META_DATA_PTR_OFFSET];
          /* PRQA S 0310 1 */ /* MD_EthSwt_30_Sja1105PQRS_0310_FrameId */
          MetaFramePtr = (EthSwt_30_Sja1105PQRS_MetaFrame*)MetaInformationPtr;

          /* #3010 Store needed information */
          mgmtElem->MgmtInfo.PortIdx = swtCfg->TransformPortIdx(MetaFramePtr->SourcePort,
              ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_EXTERNAL_VIEW);
          mgmtElem->MgmtInfo.SwitchIdx  = MetaFramePtr->SwitchId;
          mgmtElem->MgmtInfo.FrameId = EthSwt_30_Sja1105PQRS_LastManagedRxFrameId;
          mgmtElem->ManagedFrameDataPtr = EthSwt_30_Sja1105PQRS_LastManagedRxDataPtr;

#if ( ETHSWT_30_SJA1105PQRS_GLOBAL_TIME_SUPPORT == STD_ON )
          {
            EthSwt_MgmtInfoType mgmtInfo;

            mgmtInfo.PortIdx = mgmtElem->MgmtInfo.PortIdx;
            mgmtInfo.SwitchIdx = mgmtElem->MgmtInfo.SwitchIdx;
            mgmtInfo.FrameId = mgmtElem->MgmtInfo.FrameId;
            /* #3020 Initiate timestamp retrieval */
            EthSwt_30_Sja1105PQRS_InitiateRxTsRetrieval(CtrlIdx, (*DataPtr), &mgmtInfo);
          }
#endif /* ETHSWT_30_SJA1105PQRS_GLOBAL_TIME_SUPPORT */
          retVal = E_OK;
        }
      }
      else
      {
        /* Ignore the META frame without proceeding managed frame */
        retVal = E_NOT_OK;
      }
      *IsMgmtFrameOnlyPtr = TRUE;
    }
    else
    {
      /* Unmanaged frame received */
      *IsMgmtFrameOnlyPtr = FALSE;
      retVal = E_OK;
    }
  }
#if ( ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON )
  else
  {
    EthSwt_CallDetReportError(                              \
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,              \
        ETHSWT_30_SJA1105PQRS_SID_INTERNAL_FRAME_MNGMT_API, \
        ETHSWT_30_SJA1105PQRS_E_INTERNAL_ERROR);
  }
#endif /* ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT */

  return retVal;
} /* EthSwt_30_Sja1105PQRS_EthProcessRxFrame() */  /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_EthRxFinishedIndication
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_EthRxFinishedIndication(
                 uint8                                           CtrlIdx,
    ETHSWT_P2VAR(ETHSWT_P2VAR(uint8, SJA1105PQRS),  SJA1105PQRS) DataPtr) /* PRQA S 3673 */ /* MD_EthSwt_30_Sja1105PQRS_3673_AsrApi */
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  swtCfg;

  /* ----- Development Error Checks ------------------------------------- */

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(DataPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  /* #10 Is there a switch instance doing frame management on the controller? */
  if( EthSwt_30_Sja1105PQRS_GetSwitchManagementInstance(CtrlIdx, &swtCfg) == E_OK )
  {
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_RxMgmtDataType, SJA1105PQRS)  mgmtElem = NULL_PTR;

    /* #100 Check if management information was retrieved before */
    if( EthSwt_30_Sja1105PQRS_GetRxMgmtElement(swtCfg, &mgmtElem) == E_OK )
    {
      if( mgmtElem->MgmtInfo.PortIdx != (EthSwt_PortIdxType)ETHSWT_30_SJA1105PQRS_PORT_DONT_CARE )
      {
        /* #1000 There was management information contained in the frame -> pass the information to EthIf */
        EthSwt_MgmtInfoType  mgmtInfo;

        mgmtInfo.SwitchIdx = mgmtElem->MgmtInfo.SwitchIdx;
        mgmtInfo.PortIdx   = mgmtElem->MgmtInfo.PortIdx;
        mgmtInfo.FrameId   = mgmtElem->MgmtInfo.FrameId;

        /* #1010 Inform EthIf about management information */
        EthIf_SwitchMgmtInfoIndication(CtrlIdx, mgmtElem->ManagedFrameDataPtr,
            (P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, AUTOMATIC))&mgmtInfo);
      }

      /* #1020 Release the management element */
      (void)EthSwt_30_Sja1105PQRS_ReleaseRxMgmtElement(swtCfg, mgmtElem);
    }
  }
} /* EthSwt_30_Sja1105PQRS_EthRxFinishedIndication() */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_EthTxAdaptBufferLength
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_EthTxAdaptBufferLength(
    ETHSWT_P2VAR(uint16, SJA1105PQRS) LengthPtr ) /* PRQA S 3673 */ /* MD_EthSwt_30_Sja1105PQRS_3673_AsrApi */
{
  /* ----- Local data declaration --------------------------------------- */
  /* ----- Development Error Checks ------------------------------------- */
  /* ----- Local data definition ---------------------------------------- */

  /* #10 Nothing to do here */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(LengthPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  return E_OK;

} /* EthSwt_30_Sja1105PQRS_EthTxAdaptBufferLength() */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_EthTxPrepareFrame
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_EthTxPrepareFrame(
                 uint8                                           CtrlIdx,
                 uint8                                           BufIdx,
                 Eth_FrameIdType                                 FrameId,
    ETHSWT_P2VAR(ETHSWT_P2VAR(uint8, SJA1105PQRS),  SJA1105PQRS) DataPtr,  /* PRQA S 3673 */ /* MD_EthSwt_30_Sja1105PQRS_3673_AsrApi */
    ETHSWT_P2VAR(uint16,                            SJA1105PQRS) LengthPtr )  /* PRQA S 3673 */ /* MD_EthSwt_30_Sja1105PQRS_3673_AsrApi */
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  swtCfg;
                 Std_ReturnType                                          retVal;

  /* ----- Development Error Checks ------------------------------------- */

  /* ----- Local data definition ---------------------------------------- */
  retVal       = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(DataPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(LengthPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  /* #10 Is there a switch instance doing frame management on the controller? */
  if( EthSwt_30_Sja1105PQRS_GetSwitchManagementInstance(CtrlIdx, &swtCfg) == E_OK )
  {
    /* #100 Allocate a management element for later usage in transmit processing */
    if( EthSwt_30_Sja1105PQRS_AllocateFreeTxMgmtElement(swtCfg, BufIdx, FrameId) == E_OK )
    {
      retVal = E_OK;
    }
#if ( ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON )
    else
    {
      EthSwt_CallDetReportError(                              \
          ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,              \
          ETHSWT_30_SJA1105PQRS_SID_INTERNAL_FRAME_MNGMT_API, \
          ETHSWT_30_SJA1105PQRS_E_INTERNAL_ERROR);
    }
#endif /* ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT */
  }

  return retVal;
} /* EthSwt_30_Sja1105PQRS_EthTxPrepareFrame() */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_EthTxProcessFrame
 *********************************************************************************************************************/
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
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_EthTxProcessFrame(
                 uint8                                           CtrlIdx,
                 uint8                                           BufIdx,
                 Eth_FrameIdType                                 FrameId,
    ETHSWT_P2VAR(ETHSWT_P2VAR(uint8, SJA1105PQRS),  SJA1105PQRS) DataPtr,  /* PRQA S 3673 */ /* MD_EthSwt_30_Sja1105PQRS_3673_AsrApi */
    ETHSWT_P2VAR(uint16,                            SJA1105PQRS) LengthPtr )  /* PRQA S 3673 */ /* MD_EthSwt_30_Sja1105PQRS_3673_AsrApi */
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS) swtCfg;
                 Std_ReturnType                                         RetVal;
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_TsProcElemType, SJA1105PQRS)     TsProcElemPtr;

  /* ----- Development Error Checks ------------------------------------- */

  /* ----- Local data definition ---------------------------------------- */
  RetVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(LengthPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  /* #10 Is there a switch instance doing frame management on the controller? */
  if( EthSwt_30_Sja1105PQRS_GetSwitchManagementInstance(CtrlIdx, &swtCfg) == E_OK )
  {
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_TxMgmtDataType, SJA1105PQRS) mgmtElem = NULL_PTR;

    /* #100 Allocate a management element for later usage in transmit processing */
    if( EthSwt_30_Sja1105PQRS_GetTxMgmtElement(swtCfg, BufIdx, FrameId, &mgmtElem) == E_OK )
    {
      /* #200 Is management necessary? */
      if( mgmtElem->ToBeManaged == TRUE )
      {
        EthSwt_30_Sja1105PQRS_L2LookupTableWriteResultType L2LookupTableWriteResult;
        uint8* DestMacPtr =  &((*DataPtr)[ETHSWT_30_SJA1105PQRS_DEST_MAC_DATA_PTR_OFFSET]);
        EthSwt_30_Sja1105PQRS_MgmtRouteCfgType MgmtRouteCfg;
        uint8 currentSwitchIdx;
        uint8 HwPortMask;

        /* #2000 Enter exclusive area (Reason: Ensure consistency of timestamp processing) */
        /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
        /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
        EthSwt_EnterExclusiveArea(Sja1105PQRS, TS_QUEUE_PROCESSING);

        MgmtRouteCfg.EnableMgmtRoute = TRUE;
        currentSwitchIdx = EthSwt_30_Sja1105PQRS_GetIndexOfDirectlyConnectedSwitch();

        /* #2010 Current switch != destination switch? Cascading necessary */
        while( (RetVal == E_OK) &&
               (currentSwitchIdx != mgmtElem->MgmtInfo.SwitchIdx) )
        {
          /* #20100 Set management route in all but the last switch */

          /* While processing the management routes for cascading no egress timestamps are necessary */
          MgmtRouteCfg.EnableTimeStamp = FALSE;

          /* Set management route in current switch to cascading port to next switch */
          HwPortMask = (uint8)(1U <<
              EthSwt_30_Sja1105PQRS_CascadingConfig.CascadingMaps[currentSwitchIdx].DerivativeSpecificCasc->PortToCascadedSwitch);

          /* Do Tx Frame Management: Set a new management Route */
          RetVal = EthSwt_30_Sja1105PQRS_WriteL2LookupTableEntry(currentSwitchIdx,
              *(EthSwt_30_Sja1105PQRS_InstanceConfig[currentSwitchIdx].FrameManagement->MgmtRouteIndex),
              DestMacPtr,
              0,
              HwPortMask,
              &MgmtRouteCfg,
              TRUE,
              &L2LookupTableWriteResult);

          /*! Internal comment removed.
 *
 *
 *
 * */
          *(EthSwt_30_Sja1105PQRS_InstanceConfig[currentSwitchIdx].FrameManagement->MgmtRouteIndex) =
              (*swtCfg->FrameManagement->MgmtRouteIndex + 1) % ETHSWT_30_SJA1105PQRS_MGMT_ROUTE_ENTRIES;

          /* Continue with the next switch, which is closer to the target */
          currentSwitchIdx =
              EthSwt_30_Sja1105PQRS_CascadingConfig.CascadingMaps[currentSwitchIdx].DerivativeSpecificCasc->CascadedSwitch;
        }

        if( RetVal == E_OK )
        {
          /* #2020 Retrieve timestamping information for the last switch */
#if (ETHSWT_30_SJA1105PQRS_GLOBAL_TIME_SUPPORT == STD_ON)
          EthSwt_30_Sja1105PQRS_FinalizePrepOfTxTsRetrieval(CtrlIdx,
                                                        BufIdx,
                                                        *DataPtr,
                                                        (P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, AUTOMATIC))&mgmtElem->MgmtInfo,
                                                        &TsProcElemPtr);

          if( TsProcElemPtr != NULL_PTR )
          {
            MgmtRouteCfg.EnableTimeStamp = TRUE;
            MgmtRouteCfg.TsReg           = TsProcElemPtr->TsReg;
          }
          else
#endif /* ETHSWT_30_SJA1105PQRS_GLOBAL_TIME_SUPPORT == STD_ON) */
          {
            MgmtRouteCfg.EnableTimeStamp = FALSE;
          }

          /* Last cascaded switch (final target) */
          HwPortMask = (uint8)(1U <<
              swtCfg->TransformPortIdx(mgmtElem->MgmtInfo.PortIdx,
                  ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_INTERNAL_VIEW));

          /* #2030 Do Tx Frame Management: Set a new management Route in the last switch */
          RetVal = EthSwt_30_Sja1105PQRS_WriteL2LookupTableEntry(currentSwitchIdx,
              *(EthSwt_30_Sja1105PQRS_InstanceConfig[currentSwitchIdx].FrameManagement->MgmtRouteIndex),
              DestMacPtr,
              0,
              HwPortMask,
              &MgmtRouteCfg,
              TRUE,
              &L2LookupTableWriteResult);

          /*! Internal comment removed.
 *
 *
 *
 * */
          *swtCfg->FrameManagement->MgmtRouteIndex =
              (*swtCfg->FrameManagement->MgmtRouteIndex + 1) % ETHSWT_30_SJA1105PQRS_MGMT_ROUTE_ENTRIES;
        }
        /* #2040 Leave exclusive area */
        /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
        /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
        EthSwt_ExitExclusiveArea(Sja1105PQRS, TS_QUEUE_PROCESSING);
      }
      else
      {
        RetVal = E_OK;
      }
    }
#if ( ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON )
    else
    {
      EthSwt_CallDetReportError(                              \
          ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,              \
          ETHSWT_30_SJA1105PQRS_SID_INTERNAL_FRAME_MNGMT_API, \
          ETHSWT_30_SJA1105PQRS_E_INTERNAL_ERROR);
    }
#endif /* ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT */
  }
  return RetVal;
} /* EthSwt_30_Sja1105PQRS_EthTxProcessFrame() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_SetMgmtInfo
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_SetMgmtInfo(
                   uint8                               CtrlIdx,
                   uint8                               BufIdx,
    ETHSWT_P2CONST(EthSwt_MgmtInfoType, SJA1105PQRS)   MgmtInfoPtr)
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  swtCfg;
                 Std_ReturnType                                          retVal;

  /* ----- Development Error Checks ------------------------------------- */

  /* ----- Local data definition ---------------------------------------- */
  retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Is there a switch instance doing frame management on the controller? */
  if( EthSwt_30_Sja1105PQRS_GetSwitchManagementInstance(CtrlIdx, &swtCfg) == E_OK )
  {
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_TxMgmtDataType, SJA1105PQRS) mgmtElem = NULL_PTR;

    /* #100 Allocate a management element for later usage in transmit processing */
    if( EthSwt_30_Sja1105PQRS_GetTxMgmtElement(swtCfg, BufIdx, MgmtInfoPtr->FrameId, &mgmtElem) == E_OK )
    {
      mgmtElem->MgmtInfo.SwitchIdx = MgmtInfoPtr->SwitchIdx;
      mgmtElem->MgmtInfo.PortIdx   = MgmtInfoPtr->PortIdx;
      mgmtElem->MgmtInfo.FrameId   = MgmtInfoPtr->FrameId;

      /* #110 apply frame management */
      mgmtElem->ToBeManaged = TRUE;

      retVal = E_OK;
    }
#if ( ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON )
    else
    {
      EthSwt_CallDetReportError(                              \
          ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID,              \
          ETHSWT_30_SJA1105PQRS_SID_INTERNAL_FRAME_MNGMT_API, \
          ETHSWT_30_SJA1105PQRS_E_INTERNAL_ERROR);
    }
#endif /* ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT */
  }
  return retVal;
} /* EthSwt_30_Sja1105PQRS_SetMgmtInfo() */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_EthTxFinishedIndication
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_EthTxFinishedIndication(
    uint8            CtrlIdx,
    uint8            BufIdx,
    Eth_FrameIdType  FrameId)
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  swtCfg;

  /* ----- Development Error Checks ------------------------------------- */

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Is there a switch instance doing frame management on the controller? */
  if( EthSwt_30_Sja1105PQRS_GetSwitchManagementInstance(CtrlIdx, &swtCfg) == E_OK )
  {
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_TxMgmtDataType, SJA1105PQRS) mgmtElem = NULL_PTR;

    /* #100 Allocate a management element for later usage in transmit processing */
    if( EthSwt_30_Sja1105PQRS_GetTxMgmtElement(swtCfg, BufIdx, FrameId, &mgmtElem) == E_OK )
    {
#if ( ETHSWT_30_SJA1105PQRS_GLOBAL_TIME_SUPPORT == STD_ON )
      /* #110 Initiate timestamp retrieval */
       EthSwt_30_Sja1105PQRS_InitiateTxTsRetrieval(
           CtrlIdx,
           BufIdx,
           (P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, AUTOMATIC))&mgmtElem->MgmtInfo);
#endif /* ETHSWT_30_SJA1105PQRS_GLOBAL_TIME_SUPPORT */
      /* #120 Release the management element */
      (void)EthSwt_30_Sja1105PQRS_ReleaseTxMgmtElement(mgmtElem);
    }
  }
} /* EthSwt_30_Sja1105PQRS_EthTxFinishedIndication() */

#define ETHSWT_30_SJA1105PQRS_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ETHSWT_30_SJA1105PQRS_MANAGEMENT_SUPPORT */

/* PRQA L:IDENTIFIER_DIFFER */
/* PRQA L:ETHSWT_30_SJA1105PQRS_NO_OF_MACROS */

/* Module specific MISRA deviations:
 *
  MD_EthSwt_30_Sja1105PQRS_0310_FrameId:
      Reason:     To access the frame identifier the pointer type must be casted.
      Risk:       Risk of an unaligned memory exception.
      Prevention: Covered by code review.

  MD_EthSwt_30_Sja1105PQRS_3305_FrameId:
      Reason:     To access the frame identifier the pointer type must be casted.
      Risk:       Risk of an unaligned memory exception.
      Prevention: Covered by code review.

  MD_EthSwt_30_Sja1105PQRS_3673_AsrApi:
      Reason:     Api is specified by AUTOSAR and must not be changed.
      Risk:       None.
      Prevention: Covered by code review.

  MD_EthSwt_30_Sja1105PQRS_3218:
      Reason:     No function local static variables should be used. File local variable must be used instead.
      Risk:       None.
      Prevention: Covered by code review.
 */

/**********************************************************************************************************************
 *  END OF FILE: EthSwt_30_Sja1105PQRS_Mgmt.c
 *********************************************************************************************************************/

