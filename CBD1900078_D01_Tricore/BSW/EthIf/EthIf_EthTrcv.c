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
/*!        \file  EthIf_EthTrcv.c
 *        \brief  EthIf EthTrcv public API source file
 *
 *      \details  Implementation of the public API of the sub-module EthTrcv of EthIf.
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

#define ETHIF_ETHTRCV_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
#include "EthIf_EthTrcv.h"
#include "EthIf_EthTrcv_Cbk.h"
#include "EthIf_EthTrcv_Int.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of Msn header file */
#if (  (ETHIF_SW_MAJOR_VERSION != (10u)) \
    || (ETHIF_SW_MINOR_VERSION != (0u)) \
    || (ETHIF_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of EthIf_EthTrcv.c and EthIf.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (ETHIF_CFG_MAJOR_VERSION != (7u)) \
    || (ETHIF_CFG_MINOR_VERSION != (0u)) )
# error "Version numbers of EthIf_EthTrcv.c and EthIf_Cfg.h are inconsistent!"
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

#if !defined (ETHIF_ETHTRCV_LOCAL)                                                                                      /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_ETHTRCV_LOCAL static
#endif

#if !defined (ETHIF_ETHTRCV_LOCAL_INLINE)                                                                               /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_ETHTRCV_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define ETHIF_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# if ( ETHIF_WAKEUP_SUPPORT == STD_ON )
/**********************************************************************************************************************
 *  EthIf_QueryForWakeupMap
 *********************************************************************************************************************/
/*! \brief          Queries for a wakeup map
 *  \details        This function queries for the wakeup map by taking the wakeup source passed.
 *  \param[in]      wakeupSource  Wakeup source of EcuM
 *  \return         ETHIF_INVALID_WAKEUP_MAP - no wakeup map found
 *  \return         other values - wakeup map index
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_ETHTRCV_LOCAL_INLINE FUNC(EthIf_WakeupMapIterType, ETHIF_ETHTRCV_INLINE_CODE) EthIf_QueryForWakeupMap(
  EcuM_WakeupSourceType wakeupSource);

/**********************************************************************************************************************
 *  EthIf_QueryForWakeupTransceiver
 *********************************************************************************************************************/
/*! \brief          Queries for the wakeup Ethernet transceiver
 *  \details        This function queries for the wakeup Ethernet transceiver belonging to the EthIf controller.
 *  \param[in]      ethIfCtrlIdx    EthIf controller index
 *  \return         ETHIF_INVALID_WAKEUP_ETHTRCV - no wakeup transceiver found
 *  \return         other values - index of the transceiver within the physical layer elements of the EthIf controller
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_ETHTRCV_LOCAL_INLINE FUNC(EthIf_EthTrcvIterType, ETHIF_ETHTRCV_INLINE_CODE) EthIf_QueryForWakeupTransceiver(
  EthIf_EthIfCtrlIterType ethIfCtrlIdx);

# endif /* ETHIF_WAKEUP_SUPPORT */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

# if ( ETHIF_WAKEUP_SUPPORT == STD_ON )
/**********************************************************************************************************************
 *  EthIf_QueryForWakeupMap
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHIF_ETHTRCV_LOCAL_INLINE FUNC(EthIf_WakeupMapIterType, ETHIF_ETHTRCV_INLINE_CODE) EthIf_QueryForWakeupMap(
  EcuM_WakeupSourceType wakeupSource)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_WakeupMapIterType  queriedWakeupMapIdx;
  EthIf_WakeupMapIterType  wakeupMapIdx;

  /* ----- Implementation ----------------------------------------------- */
  queriedWakeupMapIdx = EthIf_GetSizeOfWakeupMap();

  /* #10 For each wakeup map */
  for( wakeupMapIdx = 0;
       wakeupMapIdx < EthIf_GetSizeOfWakeupMap();
       wakeupMapIdx++ )
  {
    /* #100 Check if wakeup source queried for matches the one of the map */
    if( wakeupSource == EthIf_GetWakeupSourceOfWakeupMap(wakeupMapIdx) )
    {
      /* #1000 Wakeup source matched -> wakeup map found */
      queriedWakeupMapIdx = wakeupMapIdx;
      break;
    }
  }

  return queriedWakeupMapIdx;
} /* EthIf_QueryForWakeupMap() */

/**********************************************************************************************************************
 *  EthIf_QueryForWakeupTransceiver
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHIF_ETHTRCV_LOCAL_INLINE FUNC(EthIf_EthTrcvIterType, ETHIF_ETHTRCV_INLINE_CODE) EthIf_QueryForWakeupTransceiver(
    EthIf_EthIfCtrlIterType ethIfCtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_EthTrcvIterType queriedWakeupEthTrcvIdx;
  EthIf_PhysLayerInitElemsIdxOfEthIfCtrlType physLayerInitElemsIdx;

  /* ----- Implementation ----------------------------------------------- */
  queriedWakeupEthTrcvIdx = ETHIF_INVALID_WAKEUP_ETHTRCV;
  physLayerInitElemsIdx   = EthIf_GetPhysLayerInitElemsIdxOfEthIfCtrl(ethIfCtrlIdx);

  /* #10 Check if EthTrcv is mapped to EthIf controller */
  if( EthIf_IsEthTrcvUsedOfPhysLayerInitElems(physLayerInitElemsIdx) == TRUE )
  {
    queriedWakeupEthTrcvIdx = EthIf_GetEthTrcvIdxOfPhysLayerInitElems(physLayerInitElemsIdx);
  }

  return queriedWakeupEthTrcvIdx;
} /* EthIf_QueryForWakeupTransceiver() */

# endif /* ETHIF_WAKEUP_SUPPORT */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#if ( ETHIF_WAKEUP_SUPPORT == STD_ON )
/**********************************************************************************************************************
 * EthIf_SetTransceiverWakeupMode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SetTransceiverWakeupMode(
  EcuM_WakeupSourceType   WakeupSource,
  EthTrcv_WakeupModeType  WakeupMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType          retVal       = E_NOT_OK;
  uint8                   errorId      = ETHIF_E_NO_ERROR;
  EthIf_WakeupMapIterType wakeupMapIdx = EthIf_QueryForWakeupMap(WakeupSource);

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393861 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( wakeupMapIdx >= EthIf_GetSizeOfWakeupMap() )
  {
    /* \trace SPEC-2393862 */
    errorId = ETHIF_E_INV_PARAM;
  }
  else if( (WakeupMode != ETHTRCV_WUM_DISABLE) &&
           (WakeupMode != ETHTRCV_WUM_ENABLE)  &&
           (WakeupMode != ETHTRCV_WUM_CLEAR)      )
  {
    errorId = ETHIF_E_INV_PARAM;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthTrcvIdxOfWakeupMapType ethTrcvIdx = EthIf_GetEthTrcvIdxOfWakeupMap(wakeupMapIdx);
    EthIf_EthTrcvDrvApiIdxOfEthTrcvType ethTrcvDrvApiIdx = EthIf_GetEthTrcvDrvApiIdxOfEthTrcv(ethTrcvIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetSetTrcvWakeupModeOfEthTrcvDrvApi(ethTrcvDrvApiIdx) != NULL_PTR )
    {
      /* #300 Redirect call to the driver */
      /* \trace SPEC-2393949 */
      retVal = EthIf_GetSetTrcvWakeupModeOfEthTrcvDrvApi(ethTrcvDrvApiIdx)(EthIf_GetSnvOfEthTrcv(ethTrcvIdx),
                                                                           WakeupMode);                                 /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_CSL03 */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_SET_TRANSCEIVER_WAKEUP_MODE, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_SetTransceiverWakeupMode() */

/**********************************************************************************************************************
 * EthIf_GetTransceiverWakeupMode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetTransceiverWakeupMode(
        EcuM_WakeupSourceType                               WakeupSource,
  P2VAR(EthTrcv_WakeupModeType, AUTOMATIC, ETHIF_APPL_VAR)  WakeupModePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType          retVal       = E_NOT_OK;
  uint8                   errorId      = ETHIF_E_NO_ERROR;
  EthIf_WakeupMapIterType wakeupMapIdx = EthIf_QueryForWakeupMap(WakeupSource);

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393864 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( wakeupMapIdx >= EthIf_GetSizeOfWakeupMap() )
  {
    /* \trace SPEC-2393865 */
    errorId = ETHIF_E_INV_PARAM;
  }
  else if( WakeupModePtr == NULL_PTR )
  {
    /* \trace SPEC-2393866 */
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthTrcvIdxOfWakeupMapType ethTrcvIdx = EthIf_GetEthTrcvIdxOfWakeupMap(wakeupMapIdx);
    EthIf_EthTrcvDrvApiIdxOfEthTrcvType ethTrcvDrvApiIdx = EthIf_GetEthTrcvDrvApiIdxOfEthTrcv(ethTrcvIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetGetTrcvWakeupModeOfEthTrcvDrvApi(ethTrcvDrvApiIdx) != NULL_PTR )
    {
      /* #300 Redirect call to the driver */
      /* \trace SPEC-2393951 */
      retVal = EthIf_GetGetTrcvWakeupModeOfEthTrcvDrvApi(ethTrcvDrvApiIdx)(EthIf_GetSnvOfEthTrcv(ethTrcvIdx),
                                                                           WakeupModePtr);                              /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_PUB_PARAM_PTR_CSL03 */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_GET_TRANSCEIVER_WAKEUP_MODE, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_GetTransceiverWakeupMode() */

/**********************************************************************************************************************
 * EthIf_CheckWakeup
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, ETHIF_CODE) EthIf_CheckWakeup(
  EcuM_WakeupSourceType  WakeupSource)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8                   errorId      = ETHIF_E_NO_ERROR;
  EthIf_WakeupMapIterType wakeupMapIdx = EthIf_QueryForWakeupMap(WakeupSource);

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393869 */
    /* \trace SPEC-2393872 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( wakeupMapIdx >= EthIf_GetSizeOfWakeupMap() )
  {
    /* \trace SPEC-2393870 */
    errorId = ETHIF_E_INV_PARAM;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthTrcvIdxOfWakeupMapType ethTrcvIdx = EthIf_GetEthTrcvIdxOfWakeupMap(wakeupMapIdx);
    EthIf_EthTrcvDrvApiIdxOfEthTrcvType ethTrcvDrvApiIdx = EthIf_GetEthTrcvDrvApiIdxOfEthTrcv(ethTrcvIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetCheckWakeupOfEthTrcvDrvApi(ethTrcvDrvApiIdx) != NULL_PTR )
    {
      /* #300 Redirect call to the driver */
      /* \trace SPEC-2393952 */
      (void)EthIf_GetCheckWakeupOfEthTrcvDrvApi(ethTrcvDrvApiIdx)(EthIf_GetSnvOfEthTrcv(ethTrcvIdx));                   /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_CSL03 */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_CHECK_WAKEUP, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

} /* EthIf_CheckWakeup() */

/**********************************************************************************************************************
 * EthIf_VSetTransceiverWakeupMode
 **********************************************************************************************************************/
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
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_VSetTransceiverWakeupMode(
  uint8                   CtrlIdx,
  EthTrcv_WakeupModeType  WakeupMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( CtrlIdx >= EthIf_GetSizeOfEthIfCtrl() )
  {
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else if( (WakeupMode != ETHTRCV_WUM_DISABLE) &&
           (WakeupMode != ETHTRCV_WUM_ENABLE)  &&
           (WakeupMode != ETHTRCV_WUM_CLEAR)      )
  {
    errorId = ETHIF_E_INV_PARAM;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthTrcvIterType ethTrcvIdx = EthIf_QueryForWakeupTransceiver(CtrlIdx);

    /* #30 Check if wakeup transceiver for EthIf controller exists */
    if( ethTrcvIdx != ETHIF_INVALID_WAKEUP_ETHTRCV )
    {
      EthIf_EthTrcvDrvApiIdxOfEthTrcvType ethTrcvDrvApiIdx = EthIf_GetEthTrcvDrvApiIdxOfEthTrcv(ethTrcvIdx);
      /* #300 Check if driver provides the API */
      if( EthIf_GetSetTrcvWakeupModeOfEthTrcvDrvApi(ethTrcvDrvApiIdx) != NULL_PTR )
      {
        /* #3000 Redirect call to the driver */
        retVal = EthIf_GetSetTrcvWakeupModeOfEthTrcvDrvApi(ethTrcvDrvApiIdx)(EthIf_GetSnvOfEthTrcv(ethTrcvIdx),
                                                                             WakeupMode);                               /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_CSL03 */
      }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
      else
      {
        errorId = ETHIF_E_INV_DRIVER_API_CALL;
      }
# endif /* ETHIF_DEV_ERROR_DETECT */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_PARAM;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_SET_TRANSCEIVER_WAKEUP_MODE, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_VSetTransceiverWakeupMode() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 * EthIf_VGetTransceiverWakeupMode
 **********************************************************************************************************************/
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
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_VGetTransceiverWakeupMode(
        uint8                                               CtrlIdx,
  P2VAR(EthTrcv_WakeupModeType, AUTOMATIC, ETHIF_APPL_VAR)  WakeupModePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( CtrlIdx >= EthIf_GetSizeOfEthIfCtrl() )
  {
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else if( WakeupModePtr == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthTrcvIterType ethTrcvIdx =  EthIf_QueryForWakeupTransceiver(CtrlIdx);

    /* #30 Check if wakeup transceiver for EthIf controller exists */
    if( ethTrcvIdx != ETHIF_INVALID_WAKEUP_ETHTRCV )
    {
      EthIf_EthTrcvDrvApiIdxOfEthTrcvType ethTrcvDrvApiIdx = EthIf_GetEthTrcvDrvApiIdxOfEthTrcv(ethTrcvIdx);

      /* #300 Check if driver provides the API */
      if( EthIf_GetGetTrcvWakeupModeOfEthTrcvDrvApi(ethTrcvDrvApiIdx) != NULL_PTR )
      {
        /* #3000 Redirect call to the driver */
        retVal = EthIf_GetGetTrcvWakeupModeOfEthTrcvDrvApi(ethTrcvDrvApiIdx)(EthIf_GetSnvOfEthTrcv(ethTrcvIdx),
                                                                             WakeupModePtr);                            /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_PUB_PARAM_PTR_CSL03 */
      }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
      else
      {
        errorId = ETHIF_E_INV_DRIVER_API_CALL;
      }
# endif /* ETHIF_DEV_ERROR_DETECT */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_PARAM;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_GET_TRANSCEIVER_WAKEUP_MODE, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_VGetTransceiverWakeupMode() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 * EthIf_VCheckWakeup
 **********************************************************************************************************************/
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
FUNC(void, ETHIF_CODE) EthIf_VCheckWakeup(
  uint8  CtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( CtrlIdx >= EthIf_GetSizeOfEthIfCtrl() )
  {
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthTrcvIterType ethTrcvIdx =  EthIf_QueryForWakeupTransceiver(CtrlIdx);

    /* #30 Check if wakeup transceiver for EthIf controller exists */
    if( ethTrcvIdx != ETHIF_INVALID_WAKEUP_ETHTRCV )
    {
      EthIf_EthTrcvDrvApiIdxOfEthTrcvType ethTrcvDrvApiIdx = EthIf_GetEthTrcvDrvApiIdxOfEthTrcv(ethTrcvIdx);

      /* #300 Check if driver provides the API */
      if( EthIf_GetCheckWakeupOfEthTrcvDrvApi(ethTrcvDrvApiIdx) != NULL_PTR )
      {
        /* #3000 Redirect call to the driver */
        (void)EthIf_GetCheckWakeupOfEthTrcvDrvApi(ethTrcvDrvApiIdx)(EthIf_GetSnvOfEthTrcv(ethTrcvIdx));                 /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_CSL03 */
      }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
      else
      {
        errorId = ETHIF_E_INV_DRIVER_API_CALL;
      }
# endif /* ETHIF_DEV_ERROR_DETECT */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_PARAM;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_CHECK_WAKEUP, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

} /* EthIf_VCheckWakeup() */

#endif /* ETHIF_WAKEUP_SUPPORT */

#define ETHIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_EthTrcv.c
 *********************************************************************************************************************/

