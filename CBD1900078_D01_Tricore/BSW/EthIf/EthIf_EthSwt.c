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
/*!        \file  EthIf_EthSwt.c
 *        \brief  EthIf EthSwt public API source file
 *
 *      \details  Implementation of the public API of the sub-module EthSwt of EthIf.
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

#define ETHIF_ETHSWT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on and not to be changed without adaption of \trace  DSGN-EthIfDiag1975
 *********************************************************************************************************/
#include "EthIf_EthSwt.h"
#include "EthIf_EthSwt_Cbk.h"
#include "EthIf_EthSwt_Int.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of Msn header file */
#if (  (ETHIF_SW_MAJOR_VERSION != (10u)) \
    || (ETHIF_SW_MINOR_VERSION != (0u)) \
    || (ETHIF_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of EthIf_EthSwt.c and EthIf.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (ETHIF_CFG_MAJOR_VERSION != (7u)) \
    || (ETHIF_CFG_MINOR_VERSION != (0u)) )
# error "Version numbers of EthIf_EthSwt.c and EthIf_Cfg.h are inconsistent!"
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

#if !defined (ETHIF_ETHSWT_LOCAL)                                                                                       /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_ETHSWT_LOCAL static
#endif

#if !defined (ETHIF_ETHSWT_LOCAL_INLINE)                                                                                /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_ETHSWT_LOCAL_INLINE LOCAL_INLINE
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

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#if ( ETHIF_GET_PORT_MAC_ADDR_API == STD_ON )                                                                           /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 * EthIf_GetPortMacAddr
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
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetPortMacAddr(
  P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA)  MacAddrPtr,
    P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR)   SwitchIdxPtr,
    P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR)   PortIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393875 */
    /* \trace SPEC-2393877 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( MacAddrPtr == NULL_PTR )
  {
    /* \trace SPEC-2393876 */
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else if( SwitchIdxPtr == NULL_PTR )
  {
    /* \trace SPEC-2393876 */
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else if( PortIdxPtr == NULL_PTR )
  {
    /* \trace SPEC-2393876 */
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthSwtDrvApiIterType ethSwtDrvIdx;

    /* #30 For each Ethernet switch driver managed by EthIf */
    for( ethSwtDrvIdx = 0u;
         ethSwtDrvIdx < EthIf_GetSizeOfEthSwtDrvApi();
         ethSwtDrvIdx++ )
    {
      /* #300 Check if driver provides the API */
      if( EthIf_GetGetPortMacAddrOfEthSwtDrvApi(ethSwtDrvIdx) != NULL_PTR )
      {
        /* #3000 Redirect call to the driver */
        /* \trace SPEC-2394044 */
        retVal = EthIf_GetGetPortMacAddrOfEthSwtDrvApi(ethSwtDrvIdx)(MacAddrPtr,
                                                                     SwitchIdxPtr,
                                                                     PortIdxPtr);                                       /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_PUB_PARAM_PTR_CSL03 */

        /* #3010 Check if call to driver was successful -> port information found */
        if( retVal == E_OK )
        {
          EthIf_EthSwtIterType  ethIfSwtIdx;

          retVal = E_NOT_OK;

          /* #30100 Transform the switch index from the driver context to the EthIf context */
          /* search for a matching driver local switch index within the EthIf switch index search range */
          for( ethIfSwtIdx = EthIf_GetEthSwtStartIdxOfEthSwtDrv(ethSwtDrvIdx);
               ethIfSwtIdx < EthIf_GetEthSwtEndIdxOfEthSwtDrv(ethSwtDrvIdx);
               ethIfSwtIdx++ )
          {
            /* check if the driver context switch index matches */
            if( EthIf_GetSnvOfEthSwt(ethIfSwtIdx) == (*SwitchIdxPtr) )
            {
              (*SwitchIdxPtr) = (uint8)ethIfSwtIdx;                                                                     /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
              retVal = E_OK;
            }

            /* leave inner loop if tranformation to EthIf context was done */
            if( retVal == E_OK )
            {
              break;
            }
          }

          /* leave outer loop if transformation to EthIf context was done */
          if( retVal == E_OK )
          {
            break;
          }
        }
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_GET_PORT_MAC_ADDR, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_GetPortMacAddr() */ /* PRQA S 6010,6030,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STMIF */
#endif /* ETHIF_GET_PORT_MAC_ADDR_API */

#if ( ETHIF_GET_ARL_TABLE_API == STD_ON )                                                                               /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 * EthIf_GetArlTable
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
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetArlTable(
        uint8                                            SwitchIdx,
  P2VAR(uint32,              AUTOMATIC, ETHIF_APPL_VAR)  LenPtr,
  P2VAR(EthSwt_MacVlanType,  AUTOMATIC, ETHIF_APPL_VAR)  ArlTablePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393880 */
    /* \trace SPEC-2393882 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( SwitchIdx >= EthIf_GetSizeOfEthSwt()  )
  {
    errorId = ETHIF_E_INV_SWITCH_IDX;
  }
  else if( LenPtr == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else if( ArlTablePtr == NULL_PTR )
  {
    /* \trace SPEC-2393881 */
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthSwtDrvApiIdxOfEthSwtType ethSwtDrvIdx = EthIf_GetEthSwtDrvApiIdxOfEthSwt(SwitchIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetGetArlTableOfEthSwtDrvApi(ethSwtDrvIdx) != NULL_PTR )
    {
      /* #300 Redirect call to the driver */
      /* \trace SPEC-2394046 */
      retVal = EthIf_GetGetArlTableOfEthSwtDrvApi(ethSwtDrvIdx)(EthIf_GetSnvOfEthSwt(SwitchIdx),
                                                                LenPtr,
                                                                ArlTablePtr);                                           /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_PUB_PARAM_PTR_CSL03 */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_QM_FEAT_INNER */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_GET_ARL_TABLE, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_GetArlTable() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ETHIF_GET_ARL_TABLE_API */

#if ( ETHIF_GET_BUFFER_LEVEL_API == STD_ON )                                                                            /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 * EthIf_GetBufferLevel
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
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetBufferLevel(
        uint8                                               SwitchIdx,
  P2VAR(EthSwt_BufferLevelType, AUTOMATIC, ETHIF_APPL_VAR)  SwitchBufferLevelPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393885 */
    /* \trace SPEC-2393887 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( SwitchIdx >= EthIf_GetSizeOfEthSwt()  )
  {
    errorId = ETHIF_E_INV_SWITCH_IDX;
  }
  else if( SwitchBufferLevelPtr == NULL_PTR )
  {
    /* \trace SPEC-2393886 */
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthSwtDrvApiIdxOfEthSwtType ethSwtDrvIdx = EthIf_GetEthSwtDrvApiIdxOfEthSwt(SwitchIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetGetBufferLevelOfEthSwtDrvApi(ethSwtDrvIdx) != NULL_PTR )
    {
      /* #300 Redirect call to the driver */
      /* \trace SPEC-2394048 */
      retVal = EthIf_GetGetBufferLevelOfEthSwtDrvApi(ethSwtDrvIdx)(EthIf_GetSnvOfEthSwt(SwitchIdx),
                                                                   SwitchBufferLevelPtr);                               /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_PUB_PARAM_PTR_CSL03 */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_QM_FEAT_INNER */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_GET_BUFFER_LEVEL, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_GetBufferLevel() */
#endif /* ETHIF_GET_BUFFER_LEVEL_API */

#if ( ETHIF_GET_DROP_COUNT_API == STD_ON )                                                                              /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 * EthIf_GetDropCount
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
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetDropCount(
        uint8                               SwitchIdx,
  P2VAR(uint16, AUTOMATIC, ETHIF_APPL_VAR)  LenPtr,
  P2VAR(uint32, AUTOMATIC, ETHIF_APPL_VAR)  DropCountPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393890 */
    /* \trace SPEC-2393892 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( SwitchIdx >= EthIf_GetSizeOfEthSwt()  )
  {
    errorId = ETHIF_E_INV_SWITCH_IDX;
  }
  else if( LenPtr == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else if( DropCountPtr == NULL_PTR )
  {
    /* \trace SPEC-2393891 */
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthSwtDrvApiIdxOfEthSwtType ethSwtDrvIdx = EthIf_GetEthSwtDrvApiIdxOfEthSwt(SwitchIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetGetDropCountOfEthSwtDrvApi(ethSwtDrvIdx) != NULL_PTR )
    {
      /* #300 Redirect call to the driver */
      /* \trace SPEC-2394050 */
      retVal = EthIf_GetGetDropCountOfEthSwtDrvApi(ethSwtDrvIdx)(EthIf_GetSnvOfEthSwt(SwitchIdx),
                                                                 LenPtr,
                                                                 DropCountPtr);                                         /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_PUB_PARAM_PTR_CSL03 */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_QM_FEAT_INNER */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_GET_DROP_COUNT, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_GetDropCount() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ETHIF_GET_DROP_COUNT_API */

#if ( ETHIF_STORE_CONFIG_API == STD_ON )                                                                                /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 * EthIf_StoreConfiguration
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
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_StoreConfiguration(
  uint8  SwitchIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393895 */
    /* \trace SPEC-2393896 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( SwitchIdx >= EthIf_GetSizeOfEthSwt()  )
  {
    errorId = ETHIF_E_INV_SWITCH_IDX;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthSwtDrvApiIdxOfEthSwtType ethSwtDrvIdx = EthIf_GetEthSwtDrvApiIdxOfEthSwt(SwitchIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetStoreConfigOfEthSwtDrvApi(ethSwtDrvIdx) != NULL_PTR )
    {
      /* #300 Redirect call to the driver */
      retVal = EthIf_GetStoreConfigOfEthSwtDrvApi(ethSwtDrvIdx)(EthIf_GetSnvOfEthSwt(SwitchIdx));                       /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_CSL03 */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_QM_FEAT_INNER */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_STORE_CONFIGURATION, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_StoreConfiguration() */
#endif /* ETHIF_STORE_CONFIG_API */

#if ( ETHIF_RESET_CONFIG_API == STD_ON )                                                                                /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 * EthIf_ResetConfiguration
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
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_ResetConfiguration(
  uint8  SwitchIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393899 */
    /* \trace SPEC-2393900 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( SwitchIdx >= EthIf_GetSizeOfEthSwt() )
  {
    errorId = ETHIF_E_INV_SWITCH_IDX;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthSwtDrvApiIdxOfEthSwtType ethSwtDrvIdx = EthIf_GetEthSwtDrvApiIdxOfEthSwt(SwitchIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetResetConfigOfEthSwtDrvApi(ethSwtDrvIdx) != NULL_PTR )
    {
      /* #300 Redirect call to the driver */
      retVal = EthIf_GetResetConfigOfEthSwtDrvApi(ethSwtDrvIdx)(EthIf_GetSnvOfEthSwt(SwitchIdx));                       /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_CSL03 */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_QM_FEAT_INNER */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_RESET_CONFIGURATION, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_ResetConfiguration() */
#endif /* ETHIF_RESET_CONFIG_API */

#if ( ETHIF_SWITCH_UPDATE_MCAST_PORT_ASSIGN_API == STD_ON )                                                             /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 * EthIf_SwitchUpdateMCastPortAssignment
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
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SwitchUpdateMCastPortAssignment(
          uint8                              SwitchIdx,
          uint8                              PortIdx,
  P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA) MCastAddr,
          EthSwt_MCastPortAssignActionType   Action)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( SwitchIdx >= EthIf_GetSizeOfEthSwt()  )
  {
    errorId = ETHIF_E_INV_SWITCH_IDX;
  }
  else if( MCastAddr == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else if( (Action != ETHSWT_MCAST_PORT_ASSIGN_ACTION_ADD)    &&
           (Action != ETHSWT_MCAST_PORT_ASSIGN_ACTION_REMOVE)    )
  {
    errorId = ETHIF_E_INV_PARAM;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthSwtDrvApiIdxOfEthSwtType ethSwtDrvIdx = EthIf_GetEthSwtDrvApiIdxOfEthSwt(SwitchIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetUpdateMCastPortAssignmentOfEthSwtDrvApi(ethSwtDrvIdx) != NULL_PTR )
    {
      /* #300 Redirect call to the driver */
      retVal = EthIf_GetUpdateMCastPortAssignmentOfEthSwtDrvApi(ethSwtDrvIdx)(EthIf_GetSnvOfEthSwt(SwitchIdx),
                                                                              PortIdx,
                                                                              MCastAddr,
                                                                              Action);                                  /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_PUB_PARAM_PTR_CSL03 */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_QM_FEAT_INNER */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_SWITCH_UPDATE_MCAST_PORT_ASSIGNMENT, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_SwitchUpdateMCastPortAssignment() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

#endif /* ETHIF_SWITCH_UPDATE_MCAST_PORT_ASSIGN_API */

#define ETHIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_EthSwt.c
 *********************************************************************************************************************/

