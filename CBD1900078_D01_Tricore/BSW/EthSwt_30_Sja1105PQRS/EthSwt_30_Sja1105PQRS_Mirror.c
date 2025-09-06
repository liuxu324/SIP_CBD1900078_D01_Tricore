/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  EthSwt_30_Sja1105PQRS_Mirror.c
 *        \brief  Header file for access to the mirroring related API
 *
 *      \details  Contains the implementation of the mirror submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file EthSwt_30_Sja1105PQRS.h.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

#define ETHSWT_30_SJA1105PQRS_MIRROR_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EthSwt_30_Sja1105PQRS.h"
#include "EthSwt_30_Sja1105PQRS_Int.h"
#include "EthSwt_30_Sja1105PQRS_Mirror.h"
#include "EthSwt_30_Sja1105PQRS_Mirror_Int.h"

#if ( ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON )
# include "Det.h"
#endif /* ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of EthSwt_30_Sja1105PQRS header file */
#if (  (ETHSWT_30_SJA1105PQRS_SW_MAJOR_VERSION != (5u)) \
    || (ETHSWT_30_SJA1105PQRS_SW_MINOR_VERSION != (0u)) \
    || (ETHSWT_30_SJA1105PQRS_SW_PATCH_VERSION != (1u)) )
# error "Vendor specific version numbers of EthSwt_30_Sja1105PQRS_Mirror.c and EthSwt_30_Sja1105PQRS.h are inconsistent"
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

#if !defined (ETHSWT_30_SJA1105PQRS_MIRROR_LOCAL)
# define ETHSWT_30_SJA1105PQRS_MIRROR_LOCAL static
#endif

#if !defined (ETHSWT_30_SJA1105PQRS_MIRROR_LOCAL_INLINE)
# define ETHSWT_30_SJA1105PQRS_MIRROR_LOCAL_INLINE LOCAL_INLINE
#endif

#if !defined (ETHSWT_30_SJA1105PQRS_MIRROR_LOCAL_INLINE_FUNC)
/* PRQA S 3453 2 */ /* MD_MSR_19.7 */
# define ETHSWT_30_SJA1105PQRS_MIRROR_LOCAL_INLINE_FUNC(RetType) \
             ETHSWT_30_SJA1105PQRS_MIRROR_LOCAL_INLINE FUNC(RetType, ETHSWT_30_SJA1105PQRS_CODE)
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define ETHSWT_30_SJA1105PQRS_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# if( ETHSWT_30_SJA1105PQRS_NVM_USAGE == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_Mirror_RestoreConfigurationFromNvmData()
 **********************************************************************************************************************/
/*! \brief       Restores mirroring configuration
 *  \details     This function restores the mirroring configuration from NVM
 *  \param[in]   swtIdx           Identifier of the switch
 *  \return      FALSE  There has been no mirroring configuration stored or there has been an error reading it
 *  \return      TRUE   The stored mirroring configuration has been loaded successfully
 *  \pre         -
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(boolean) EthSwt_30_Sja1105PQRS_Mirror_RestoreConfigurationFromNvmData(
  uint8 swtIdx);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_Mirror_StoreConfiguration()
 **********************************************************************************************************************/
/*! \brief       Stores mirroring configuration
 *  \details     This function stores the current mirroring configuration in NVM if the configuration is valid.
 *  \param[in]   swtIdx           Identifier of the switch
 *  \pre         -
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
 ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(boolean) EthSwt_30_Sja1105PQRS_Mirror_StoreConfiguration(
  uint8 swtIdx);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_Mirror_InvalidateConfiguration()
 **********************************************************************************************************************/
/*! \brief       Invalidates mirror configuration
 *  \details     This function invalidates the stored mirroring configuration in NVM.
 *  \param[in]   swtIdx           Identifier of the switch
 *  \pre         -
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
 ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(void) EthSwt_30_Sja1105PQRS_Mirror_InvalidateConfiguration (
  uint8 swtIdx);
# endif /* ETHSWT_30_SJA1105PQRS_NVM_USAGE */

# if (ETHSWT_30_SJA1105PQRS_MIRROR_API == STD_ON)
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_Internal_SetPortMirrorState()
 *********************************************************************************************************************/
/*! \brief         Set new port mirroring state
 *  \details       This internal function sets the new port mirroring state of the specified switch.
 *  \param[in]     mirroredSwitchIdx           Identifier of switch which state shall be written
 *  \param[in]     portMirrorState             New port mirroring state
 *  \return        E_NOT_OK - Error setting port mirroring state
 *  \return        E_OK - Setting of port mirroring state has been successful
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \trace         CREQ-162955
 *********************************************************************************************************************/
 ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(Std_ReturnType) EthSwt_30_Sja1105PQRS_Internal_SetPortMirrorState(
  uint8                      mirroredSwitchIdx,
  EthSwt_PortMirrorStateType portMirrorState);
# endif /* ETHSWT_30_SJA1105PQRS_MIRROR_API */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

# if( ETHSWT_30_SJA1105PQRS_NVM_USAGE == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_Mirror_RestoreConfigurationFromNvmData()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
 ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(boolean) EthSwt_30_Sja1105PQRS_Mirror_RestoreConfigurationFromNvmData(
  uint8 swtIdx)
{
  boolean result = FALSE;
  uint8 nvmBlockId;
  NvM_RequestResultType nvmReqRes;
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS) instanceConfig;

  instanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[swtIdx];
  nvmBlockId = instanceConfig->MirrorNvmBlockId;

  /* #10 Check status of mirroring NVM block */
  if( NvM_GetErrorStatus(nvmBlockId, &nvmReqRes) == E_OK )
  {
    if( (nvmReqRes == NVM_REQ_OK) ||
        (nvmReqRes == NVM_REQ_BLOCK_SKIPPED) )
    {
      /* #20 Trigger reading of the configuration from NVM and wait till reading has been finished */
      if (NvM_ReadBlock(nvmBlockId, (void *) instanceConfig->MirrorEntity) == E_OK)
      {

        Std_ReturnType retVal;
        do
        {
          retVal = NvM_GetErrorStatus(nvmBlockId, &nvmReqRes);
        }
        while( (nvmReqRes == NVM_REQ_PENDING) &&
               (retVal == E_OK)                  );

        /* #30 Return TRUE if reading was successful, else invalidate configuration in RAM */
        if( nvmReqRes == NVM_REQ_OK )
        {
          result = TRUE;
        }
        else
        {
          instanceConfig->MirrorEntity->MirrorStatus = ETHSWT_PORT_MIRROR_INVALID;
        }
      }
    }
  }
  return result;
} /* EthSwt_30_Sja1105PQRS_Mirror_RestoreConfigurationFromNvmData() */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_Mirror_StoreConfiguration()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
 ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(Std_ReturnType) EthSwt_30_Sja1105PQRS_Mirror_StoreConfiguration(
  uint8 swtIdx)
{
  Std_ReturnType retVal;
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS) instanceConfig;
  instanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[swtIdx];

  /* #10 Write current mirroring configuration to NVM */
  retVal = NvM_WriteBlock(instanceConfig->MirrorNvmBlockId, (void *) instanceConfig->MirrorEntity);

  return retVal;
} /* EthSwt_30_Sja1105PQRS_Mirror_StoreConfiguration() */
# endif /* ETHSWT_30_SJA1105PQRS_NVM_USAGE */

# if( ETHSWT_30_SJA1105PQRS_NVM_USAGE == STD_ON )
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_Mirror_InvalidateConfiguration()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
 ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(void) EthSwt_30_Sja1105PQRS_Mirror_InvalidateConfiguration (
  uint8 swtIdx)
{
   ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS) instanceConfig;
   instanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[swtIdx];

   /* #10 Invalidate NV-RAM block */
   (void)NvM_InvalidateNvBlock(instanceConfig->MirrorNvmBlockId);
} /* EthSwt_30_Sja1105PQRS_Mirror_InvalidateConfiguration() */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_Internal_SetPortMirrorState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
 ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(Std_ReturnType) EthSwt_30_Sja1105PQRS_Internal_SetPortMirrorState(
  uint8                      mirroredSwitchIdx,
  EthSwt_PortMirrorStateType portMirrorState)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS) instanceConfig;
  instanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[mirroredSwitchIdx];

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check internal status */
  if( instanceConfig->MirrorEntity->MirrorStatus != ETHSWT_PORT_MIRROR_INVALID )
  {
    uint8_least portIdx;
    /* #20 Disable mirroring for all ports if applicable */
    if( portMirrorState == ETHSWT_PORT_MIRROR_DISABLED )
    {
      for( portIdx = 0; portIdx < instanceConfig->PortNum; portIdx++ )
      {
        uint8 hwPortIdx;
        hwPortIdx = instanceConfig->TransformPortIdx((EthSwt_PortIdxType)portIdx,
            ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_INTERNAL_VIEW);

        EthSwt_30_Sja1105PQRS_LL_Mirror_AdaptPortMirrorSelection(
            mirroredSwitchIdx,
            hwPortIdx,
            FALSE,
            FALSE);
      }
      EthSwt_30_Sja1105PQRS_LL_Mirror_DisableMirroring(mirroredSwitchIdx);
    }
    /* #30 Configure mirroring and enable all ports if applicable */
    else
    {
      EthSwt_30_Sja1105PQRS_LL_Mirror_SetMacFilter(mirroredSwitchIdx,
          instanceConfig->MirrorEntity->MirrorConfig.srcMacAddrFilter,
          instanceConfig->MirrorEntity->MirrorConfig.dstMacAddrFilter);
      EthSwt_30_Sja1105PQRS_LL_Mirror_SetVlanFilter(mirroredSwitchIdx,
          instanceConfig->MirrorEntity->MirrorConfig.VlanIdFilter);
      EthSwt_30_Sja1105PQRS_LL_Mirror_SetPacketDivider(mirroredSwitchIdx,
          instanceConfig->MirrorEntity->MirrorConfig.MirroringPacketDivider);

      for( portIdx = 0; portIdx < instanceConfig->PortNum; portIdx++ )
      {
        boolean isIngressPort = EthSwt_30_Sja1105PQRS_IsPortInBitmask((uint8) portIdx,
            instanceConfig->MirrorEntity->MirrorConfig.MirroredSwitchIngressPortIdxBitMask);
        boolean isEgressPort = EthSwt_30_Sja1105PQRS_IsPortInBitmask((uint8) portIdx,
            instanceConfig->MirrorEntity->MirrorConfig.MirroredSwitchEgressPortIdxBitMask);
        uint8 hwPortIdx;
        hwPortIdx = instanceConfig->TransformPortIdx((EthSwt_PortIdxType)portIdx,
            ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_INTERNAL_VIEW);

        EthSwt_30_Sja1105PQRS_LL_Mirror_AdaptPortMirrorSelection(
            mirroredSwitchIdx,
            hwPortIdx,
            isIngressPort,
            isEgressPort);
      }

      EthSwt_30_Sja1105PQRS_LL_Mirror_EnableCapturePort(mirroredSwitchIdx,
          instanceConfig->TransformPortIdx((EthSwt_PortIdxType)instanceConfig->MirrorEntity->MirrorConfig.CapturePortIdx,
              ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_INTERNAL_VIEW),
              instanceConfig->MirrorEntity->MirrorConfig.MirroringMode,
              instanceConfig->MirrorEntity->MirrorConfig.VlanOuterTag,
              instanceConfig->MirrorEntity->MirrorConfig.VlanInnerTag);
      EthSwt_30_Sja1105PQRS_LL_Mirror_EnableMirroring(mirroredSwitchIdx);
    }
    instanceConfig->MirrorEntity->MirrorStatus = portMirrorState;
    /* #40 Write new status to NVM */
# if( ETHSWT_30_SJA1105PQRS_NVM_USAGE == STD_ON )
    retVal = EthSwt_30_Sja1105PQRS_Mirror_StoreConfiguration(mirroredSwitchIdx);
#else
    retVal = E_OK;
# endif /* ETHSWT_30_SJA1105PQRS_NVM_USAGE */
  }

  return retVal;
} /* EthSwt_30_Sja1105PQRS_Internal_SetPortMirrorState() */ /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
# endif /* ETHSWT_30_SJA1105PQRS_MIRROR_API */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

 #if (ETHSWT_30_SJA1105PQRS_MIRROR_API == STD_ON)
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_MirrorInit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETHSWT_30_SJA1105PQRS_CODE) EthSwt_30_Sja1105PQRS_MirrorInit( uint8 switchIdx ) /* PRQA S 3219 */ /* MD_EthSwt_30_Sja1105PQRS_3219 */
{
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS) instanceConfig;
  instanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[switchIdx];

  /* #10 Set port mirroring status to default */
  instanceConfig->MirrorEntity->MirrorStatus = ETHSWT_PORT_MIRROR_INVALID;
# if( ETHSWT_30_SJA1105PQRS_NVM_USAGE == STD_ON )
  /* #20 Configure switch mirroring if reading configuration from NVM was successful */
  if( EthSwt_30_Sja1105PQRS_Mirror_RestoreConfigurationFromNvmData(switchIdx) == TRUE )
  {
    (void) EthSwt_30_Sja1105PQRS_Internal_SetPortMirrorState(switchIdx, instanceConfig->MirrorEntity->MirrorStatus);
  }
# endif /* ETHSWT_30_SJA1105PQRS_NVM_USAGE */

} /* EthSwt_30_Sja1105PQRS_MirrorInit() */
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_WritePortMirrorConfiguration()
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
FUNC(Std_ReturnType, ETHSWT_30_SJA1105PQRS_CODE) EthSwt_30_Sja1105PQRS_WritePortMirrorConfiguration(
          uint8                                                                               mirroredSwitchIdx,
  P2CONST(EthSwt_PortMirrorCfgType, ETHSWT_30_SJA1105PQRS_CONST, ETHSWT_30_SJA1105PQRS_CONST) portMirrorConfigurationPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHSWT_30_SJA1105PQRS_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check module states */
  if( EthSwt_30_Sja1105PQRS_ModuleInitState == ETHSWT_STATE_UNINIT )
  {
    mirroredSwitchIdx = ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID;
    errorId = ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( mirroredSwitchIdx >= ETHSWT_30_SJA1105PQRS_SWITCH_NUM )
  {
    mirroredSwitchIdx = ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID;
    errorId = ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX;
  }
  else if( portMirrorConfigurationPtr == NULL_PTR )
  {
    errorId = ETHSWT_30_SJA1105PQRS_E_INV_POINTER;
  }
  else
# endif
  {
    ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS) instanceConfig;
    instanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[mirroredSwitchIdx];

    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check preconditions */
    if( instanceConfig->MirrorEntity->MirrorStatus != ETHSWT_PORT_MIRROR_ENABLED )
    {
      if( EthSwt_30_Sja1105PQRS_Mirror_IsConfigValid(mirroredSwitchIdx, portMirrorConfigurationPtr) == TRUE )
      {
        /* #40 Write Configuration to internal buffer */
        instanceConfig->MirrorEntity->MirrorConfig = *portMirrorConfigurationPtr;
        instanceConfig->MirrorEntity->MirrorStatus = ETHSWT_PORT_MIRROR_DISABLED;
        /* #50 Write Configuration to NVM */
# if( ETHSWT_30_SJA1105PQRS_NVM_USAGE == STD_ON )
        retVal = EthSwt_30_Sja1105PQRS_Mirror_StoreConfiguration(mirroredSwitchIdx);
#else
        retVal = E_OK;
# endif /* ETHSWT_30_SJA1105PQRS_NVM_USAGE */
      }
      else
      {
        retVal = ETHSWT_PORT_MIRRORING_CONFIGURATION_NOT_SUPPORTED;
      }
    }
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETHSWT_30_SJA1105PQRS_DEV_ERROR_REPORT == STD_ON)
  /* #60 Report default errors if any occurred */
  if( errorId != ETHSWT_30_SJA1105PQRS_E_NO_ERROR )
  {
    (void)Det_ReportError(ETHSWT_30_SJA1105PQRS_MODULE_ID, mirroredSwitchIdx,
        ETHSWT_30_SJA1105PQRS_SID_WRITE_PORT_MIRROR_CONFIGURATION, errorId);
  }
# else
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthSwt_30_Sja1105PQRS_WritePortMirrorConfiguration() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_ReadPortMirrorConfiguration()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHSWT_30_SJA1105PQRS_CODE) EthSwt_30_Sja1105PQRS_ReadPortMirrorConfiguration(
        uint8                                                                             mirroredSwitchIdx,
  P2VAR(EthSwt_PortMirrorCfgType, ETHSWT_30_SJA1105PQRS_CONST, ETHSWT_30_SJA1105PQRS_VAR) portMirrorConfigurationPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHSWT_30_SJA1105PQRS_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check module states */
  if( EthSwt_30_Sja1105PQRS_ModuleInitState == ETHSWT_STATE_UNINIT )
  {
    mirroredSwitchIdx = ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID;
    errorId = ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( mirroredSwitchIdx >= ETHSWT_30_SJA1105PQRS_SWITCH_NUM )
  {
    mirroredSwitchIdx = ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID;
    errorId = ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX;
  }
  else if( portMirrorConfigurationPtr == NULL_PTR )
  {
    errorId = ETHSWT_30_SJA1105PQRS_E_INV_POINTER;
  }
  else
# endif
  {
    ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS) instanceConfig;
    instanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[mirroredSwitchIdx];
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check if mirroring has already been configured */
    if( instanceConfig->MirrorEntity->MirrorStatus != ETHSWT_PORT_MIRROR_INVALID )
    {
      /* #40 Get current configuration */
      (*portMirrorConfigurationPtr) = instanceConfig->MirrorEntity->MirrorConfig;
      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHSWT_30_SJA1105PQRS_DEV_ERROR_REPORT == STD_ON)
  /* #50 Report default errors if any occurred */
  if( errorId != ETHSWT_30_SJA1105PQRS_E_NO_ERROR )
  {
    (void)Det_ReportError(ETHSWT_30_SJA1105PQRS_MODULE_ID, mirroredSwitchIdx,
        ETHSWT_30_SJA1105PQRS_SID_READ_PORT_MIRROR_CONFIGURATION, errorId);
  }
# else
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthSwt_30_Sja1105PQRS_ReadPortMirrorConfiguration() */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetPortMirrorState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHSWT_30_SJA1105PQRS_CODE) EthSwt_30_Sja1105PQRS_GetPortMirrorState(
        uint8                                                                               mirroredSwitchIdx,
  P2VAR(EthSwt_PortMirrorStateType, ETHSWT_30_SJA1105PQRS_CONST, ETHSWT_30_SJA1105PQRS_VAR) portMirrorStatePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHSWT_30_SJA1105PQRS_E_NO_ERROR;
  Std_ReturnType retVal;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;

  /* #10 Check module states */
  if( EthSwt_30_Sja1105PQRS_ModuleInitState == ETHSWT_STATE_UNINIT )
  {
    mirroredSwitchIdx = ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID;
    errorId = ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( mirroredSwitchIdx >= ETHSWT_30_SJA1105PQRS_SWITCH_NUM )
  {
    mirroredSwitchIdx = ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID;
    errorId = ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX;
  }
  else if( portMirrorStatePtr == NULL_PTR )
  {
    errorId = ETHSWT_30_SJA1105PQRS_E_INV_POINTER;
  }
  else
# endif
  {
    ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS) instanceConfig;
    instanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[mirroredSwitchIdx];
    /* ----- Implementation ----------------------------------------------- */
    if (instanceConfig->MirrorEntity->MirrorStatus == ETHSWT_PORT_MIRROR_INVALID)
    {
      /* #30 Convert internal used INVALID status to AUTOSAR status if applicable */
      (*portMirrorStatePtr) = ETHSWT_PORT_MIRROR_DISABLED;
    }
    else
    {
      /* #40 Get current status if it is not invalid */
      (*portMirrorStatePtr) = instanceConfig->MirrorEntity->MirrorStatus;
    }
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHSWT_30_SJA1105PQRS_DEV_ERROR_REPORT == STD_ON)
  /* #50 Report default errors if any occurred */
  if( errorId != ETHSWT_30_SJA1105PQRS_E_NO_ERROR )
  {
    (void)Det_ReportError(ETHSWT_30_SJA1105PQRS_MODULE_ID, mirroredSwitchIdx,
        ETHSWT_30_SJA1105PQRS_SID_GET_PORT_MIRROR_STATE, errorId);
  }
# else
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthSwt_30_Sja1105PQRS_GetPortMirrorState() */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_SetPortMirrorState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHSWT_30_SJA1105PQRS_CODE) EthSwt_30_Sja1105PQRS_SetPortMirrorState(
        uint8                      mirroredSwitchIdx,
        EthSwt_PortMirrorStateType portMirrorState)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHSWT_30_SJA1105PQRS_E_NO_ERROR;
  Std_ReturnType retVal;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;

  /* #10 Check module states */
  if( EthSwt_30_Sja1105PQRS_ModuleInitState == ETHSWT_STATE_UNINIT )
  {
    mirroredSwitchIdx = ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID;
    errorId = ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED;
  }
  else if( EthSwt_30_Sja1105PQRS_InstanceData[mirroredSwitchIdx].InitState != (EthSwt_StateType)ETHSWT_STATE_ACTIVE )
  {
    errorId = ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( mirroredSwitchIdx >= ETHSWT_30_SJA1105PQRS_SWITCH_NUM )
  {
    mirroredSwitchIdx = ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID;
    errorId = ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX;
  }
  else if( (portMirrorState != ETHSWT_PORT_MIRROR_DISABLED) &&
           (portMirrorState != ETHSWT_PORT_MIRROR_ENABLED) )
  {
    errorId = ETHSWT_30_SJA1105PQRS_E_INV_PARAM;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Set new mirror state */
    retVal = EthSwt_30_Sja1105PQRS_Internal_SetPortMirrorState(mirroredSwitchIdx, portMirrorState);
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHSWT_30_SJA1105PQRS_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if( errorId != ETHSWT_30_SJA1105PQRS_E_NO_ERROR )
  {
    (void)Det_ReportError(ETHSWT_30_SJA1105PQRS_MODULE_ID, mirroredSwitchIdx,
        ETHSWT_30_SJA1105PQRS_SID_SET_PORT_MIRROR_STATE, errorId);
  }
# else
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthSwt_30_Sja1105PQRS_SetPortMirrorState() */ /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_DeletePortMirrorConfiguration()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHSWT_30_SJA1105PQRS_CODE) EthSwt_30_Sja1105PQRS_DeletePortMirrorConfiguration(
        uint8                      mirroredSwitchIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHSWT_30_SJA1105PQRS_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check module states */
  if( EthSwt_30_Sja1105PQRS_ModuleInitState == ETHSWT_STATE_UNINIT )
  {
    mirroredSwitchIdx = ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID;
    errorId = ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( mirroredSwitchIdx >= ETHSWT_30_SJA1105PQRS_SWITCH_NUM )
  {
    mirroredSwitchIdx = ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID;
    errorId = ETHSWT_30_SJA1105PQRS_E_INV_SWITCH_IDX;
  }
  else
# endif
  {
    ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS) instanceConfig;
    instanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[mirroredSwitchIdx];
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Set new status if mirroring is not enabled */
    if( instanceConfig->MirrorEntity->MirrorStatus != ETHSWT_PORT_MIRROR_ENABLED )
    {
      instanceConfig->MirrorEntity->MirrorStatus = ETHSWT_PORT_MIRROR_INVALID;
# if( ETHSWT_30_SJA1105PQRS_NVM_USAGE == STD_ON )
      /* #40 Invalidate data in NVM */
      EthSwt_30_Sja1105PQRS_Mirror_InvalidateConfiguration(mirroredSwitchIdx);
# endif /* ETHSWT_30_SJA1105PQRS_NVM_USAGE */
      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHSWT_30_SJA1105PQRS_DEV_ERROR_REPORT == STD_ON)
  /* #50 Report default errors if any occurred */
  if( errorId != ETHSWT_30_SJA1105PQRS_E_NO_ERROR )
  {
    (void)Det_ReportError(ETHSWT_30_SJA1105PQRS_MODULE_ID, mirroredSwitchIdx,
        ETHSWT_30_SJA1105PQRS_SID_DELETE_PORT_MIRROR_CONFIGURATION, errorId);
  }
# else
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthSwt_30_Sja1105PQRS_DeletePortMirrorConfiguration() */

#endif /* ETHSWT_30_SJA1105PQRS_MIRROR_API */

#define ETHSWT_30_SJA1105PQRS_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  END OF FILE: EthSwt_30_Sja1105PQRS_Mirror.c
 *********************************************************************************************************************/
