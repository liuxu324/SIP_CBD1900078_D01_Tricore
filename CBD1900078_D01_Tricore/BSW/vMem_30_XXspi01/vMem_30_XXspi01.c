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
/*!        \file  vMem_30_XXspi01.c
 *        \brief  vMem_30_XXspi01 source file
 *
 *      \details  See vMem_30_XXspi01.h
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

#define VMEM_30_XXSPI01_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "vMem_30_XXspi01.h"
#include "vMem_30_XXspi01_Int.h"
#include "vMem_30_XXspi01_LL.h"

#if (VMEM_30_XXSPI01_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of vMem_30_XXspi01 header file */
#if (  (VMEM_30_XXSPI01_SW_MAJOR_VERSION != (1u)) \
    || (VMEM_30_XXSPI01_SW_MINOR_VERSION != (0u)) \
    || (VMEM_30_XXSPI01_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of vMem_30_XXspi01.c and vMem_30_XXspi01.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (VMEM_30_XXSPI01_CFG_COMP_MAJOR_VERSION != (1u)) \
    || (VMEM_30_XXSPI01_CFG_COMP_MINOR_VERSION != (0u)) )
# error "Version numbers of vMem_30_XXspi01.c and vMem_30_XXspi01_Cfg.h are inconsistent!"
#endif


/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (VMEM_30_XXSPI01_LOCAL) /* COV_VMEM_30_XXSPI01_COMPATIBILITY */
# define VMEM_30_XXSPI01_LOCAL static
#endif

#if !defined (VMEM_30_XXSPI01_LOCAL_INLINE) /* COV_VMEM_30_XXSPI01_COMPATIBILITY */
# define VMEM_30_XXSPI01_LOCAL_INLINE LOCAL_INLINE
#endif


/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define VMEM_30_XXSPI01_START_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (VMEM_30_XXSPI01_DEV_ERROR_DETECT == STD_ON)
/*! Initialization state of the module */
# define VMEM_30_XXSPI01_UNINIT                              (0x00u)
# define VMEM_30_XXSPI01_INIT                                (0x01u)

VMEM_30_XXSPI01_LOCAL VAR(uint8, VMEM_30_XXSPI01_VAR_ZERO_INIT) vMem_30_XXspi01_ModuleInitialized = VMEM_30_XXSPI01_UNINIT;
#endif /* (VMEM_30_XXSPI01_DEV_ERROR_DETECT == STD_ON) */

#define VMEM_30_XXSPI01_STOP_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define VMEM_30_XXSPI01_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Global API pointer table definition.
 * The vMem_30_XXspi01 hardware specific extended functionality is defined within LowLevel. */
CONST(vMemAccM_vMemApiType, AUTOMATIC) vMem_30_XXspi01_FunctionPointerTable = {
  {
    VMEM_30_XXSPI01_EXTENDED_FUNCTION_COUNT,
    VMEM_30_XXSPI01_EXTENDED_FUNCTION_TABLE
  },
  &vMem_30_XXspi01_Read,
  &vMem_30_XXspi01_Write,
  &vMem_30_XXspi01_Erase,
  &vMem_30_XXspi01_GetJobResult
};

#define VMEM_30_XXSPI01_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define VMEM_30_XXSPI01_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#if (VMEM_30_XXSPI01_DEV_ERROR_DETECT == STD_ON)

/**********************************************************************************************************************
 *  vMem_30_XXspi01_InstancePendingCheck()
 *********************************************************************************************************************/
/*!
 * \brief       Check whether the requested instance is in a pending state.
 * \details     Calls LowLevel GetJobResult service, to retrieve current state of vMem_30_XXspi01 instance.
 * \param[in]   InstanceId        Id of vMem_30_XXspi01 instance is passed on to LowLevel, must be valid.
 * \return      TRUE, if the instance is pending; FALSE otherwise
 * \pre         VMEM_30_XXSPI01_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_InstancePendingCheck(vMem_30_XXspi01_InstanceIdType InstanceId);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_ReadAddressCheck()
 *********************************************************************************************************************/
/*!
 * \brief       Check whether the passed address points to any configured sector.
 * \details     -
 * \param[in]   InstanceId        ID of the related vMem_30_XXspi01 instance, must be valid.
 * \param[in]   Address           NV memory address to read from.
 * \return      TRUE, if the address is valid; FALSE otherwise
 * \pre         VMEM_30_XXSPI01_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_ReadAddressCheck(
  vMem_30_XXspi01_InstanceIdType InstanceId, vMem_30_XXspi01_AddressType Address);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_WriteAddressCheck()
 *********************************************************************************************************************/
/*!
 * \brief       Checks whether the passed address is aligned to page size of the referenced sector.
 * \details     -
 * \param[in]   InstanceId        ID of the related vMem_30_XXspi01 instance, must be valid.
 * \param[in]   Address           NV memory address to write to.
 * \return      TRUE, if the address is aligned; FALSE otherwise
 * \pre         VMEM_30_XXSPI01_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_WriteAddressCheck(
  vMem_30_XXspi01_InstanceIdType InstanceId, vMem_30_XXspi01_AddressType Address);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_EraseAddressCheck()
 *********************************************************************************************************************/
/*!
 * \brief       Checks whether the passed address is aligned to sector size.
 * \details     -
 * \param[in]   InstanceId        ID of the related vMem_30_XXspi01 instance, must be valid.
 * \param[in]   Address           NV memory address of memory which shall be erased.
 * \return      TRUE, if the address is aligned; FALSE otherwise
 * \pre         VMEM_30_XXSPI01_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_EraseAddressCheck(
  vMem_30_XXspi01_InstanceIdType InstanceId, vMem_30_XXspi01_AddressType Address);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_ReadLengthCheck()
 *********************************************************************************************************************/
/*!
 * \brief       Checks whether the passed Length is valid, that is if it is contained in the same sector batch as the
 *              passed Address.
 * \details     -
 * \param[in]   InstanceId        ID of the related vMem_30_XXspi01 instance, must be valid.
 * \param[in]   Address           NV memory address to read from, must be valid.
 * \param[in]   Length            Length in bytes to read.
 * \return      E_OK, if the Length is valid; E_NOT_OK otherwise
 * \pre         VMEM_30_XXSPI01_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_ReadLengthCheck(
  vMem_30_XXspi01_InstanceIdType InstanceId, vMem_30_XXspi01_AddressType Address, vMem_30_XXspi01_LengthType Length);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_WriteLengthCheck()
 *********************************************************************************************************************/
/*!
 * \brief       Checks whether the passed Length matches the page size or the write burst size of the sector
 *              referenced by passed address.
 * \details     -
 * \param[in]   InstanceId        ID of the related vMem_30_XXspi01 instance, must be valid.
 * \param[in]   Address           NV memory address to write to, must be valid.
 * \param[in]   Length            Length in bytes to write.
 * \return      TRUE, if the Length matches the page size or write burst size; FALSE otherwise.
 * \pre         VMEM_30_XXSPI01_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_WriteLengthCheck(
  vMem_30_XXspi01_InstanceIdType InstanceId, vMem_30_XXspi01_AddressType Address, vMem_30_XXspi01_LengthType Length);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_EraseLengthCheck()
 *********************************************************************************************************************/
/*!
 * \brief       Checks whether the passed Length matches the sector size or the erase burst size of the sector
 *              referenced by passed address.
 * \details     -
 * \param[in]   InstanceId        ID of the related vMem_30_XXspi01 instance, must be valid.
 * \param[in]   Address           NV memory address to erase, must be valid.
 * \param[in]   Length            Length in bytes to erase.
 * \return      TRUE, if the Length matches the sector size or erase burst size; FALSE otherwise.
 * \pre         VMEM_30_XXSPI01_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_EraseLengthCheck(
  vMem_30_XXspi01_InstanceIdType InstanceId, vMem_30_XXspi01_AddressType Address, vMem_30_XXspi01_LengthType Length);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_InitPendingCheck()
 *********************************************************************************************************************/
/*!
 * \brief       In case of re-initialization check that no instance is pending.
 * \details     -
 * \return      TRUE, if every vMem_30_XXspi01 instance is idle; FALSE otherwise.
 * \pre         VMEM_30_XXSPI01_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_InitPendingCheck(void);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_IsAligned()
 *********************************************************************************************************************/
/*!
 * \brief       Checks the passed value to be aligned to passed alignment.
 * \details     -
 * \param[in]   Value           Value that shall be verified, e.g. NV memory address.
 * \param[in]   Alignment       Specified alignment, e.g. sector size.
 * \return      TRUE, if the value is aligned; FALSE otherwise.
 * \pre         VMEM_30_XXSPI01_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_IsAligned(
  uint32 Value, uint32 Alignment);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_IsSectorIndexValid()
 *********************************************************************************************************************/
/*!
 * \brief       Checks whether the passed sector index is lower than the number of configured sectors for the
 *              referenced instance.
 * \details     Does not check whether the passed index bigger than the lower sector index threshold of the referenced
 *              instance. Therefore, this local function shall only be used, when sector index is computed with local
 *              function vMem_30_XXspi01_GetSectorIndex.
 * \param[in]   InstanceId        ID of the related vMem_30_XXspi01 instance, must be valid.
 * \param[in]   SectorIndex       Index of the sector (batch) which shall be validated.
 * \return      TRUE; if the sector index is valid; FALSE otherwise.
 * \pre         VMEM_30_XXSPI01_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_IsSectorIndexValid(
  vMem_30_XXspi01_InstanceIdType InstanceId, uint32 SectorIndex);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_GetInstanceIndex()
 *********************************************************************************************************************/
/*!
 * \brief       Converts the passed InstanceId to the index in configuration structure.
 * \details     If the passed InstanceId is invalid, the function will return an out of range index!
 * \param[in]   InstanceId        ID of the related vMem_30_XXspi01 instance.
 * \return      Index of the instance in configuration structure, or out of range value, if InstanceId is invalid.
 * \pre         VMEM_30_XXSPI01_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(uint32, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_GetInstanceIndex(
  vMem_30_XXspi01_InstanceIdType InstanceId);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_IsInstanceIndexValid()
 *********************************************************************************************************************/
/*!
 * \brief       Checks the passed instance index to exist (not to be out of range).
 * \details     The passed instance index shall always be computed from the InstanceId using the local function
 *              vMem_30_XXspi01_GetInstanceIndex.
 * \param[in]   InstanceIndex       Index of the related vMem_30_XXspi01 instance in configuration structure.
 * \return      TRUE; if the instance index is valid; FALSE otherwise.
 * \pre         VMEM_30_XXSPI01_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_IsInstanceIndexValid(
  vMem_30_XXspi01_InstanceIdType InstanceIndex);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_GetSectorIndex()
 *********************************************************************************************************************/
/*!
 * \brief       Searches for the passed address within the configuration and determined index of sector (batch) in
 *              configuration structure.
 * \details     -
 * \param[in]   InstanceId        ID of the related vMem_30_XXspi01 instance, must be valid.
 * \param[in]   Address           NV memory address which shall be found within configured sector structure.
 * \return      Index to the sector batch, or an out of range value.
 * \pre         VMEM_30_XXSPI01_DEV_ERROR_DETECT enabled
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(uint32, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_GetSectorIndex(
  vMem_30_XXspi01_InstanceIdType InstanceId, vMem_30_XXspi01_AddressType Address);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vMem_30_XXspi01_InstancePendingCheck
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_InstancePendingCheck(
  vMem_30_XXspi01_InstanceIdType InstanceId)
{
  return (boolean)(vMem_30_XXspi01_LLGetJobResult(InstanceId) == VMEM_JOB_PENDING); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
}

/**********************************************************************************************************************
 *  vMem_30_XXspi01_ReadAddressCheck()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_ReadAddressCheck(
  vMem_30_XXspi01_InstanceIdType InstanceId, vMem_30_XXspi01_AddressType Address)
{
  return (boolean)(vMem_30_XXspi01_IsSectorIndexValid(InstanceId, vMem_30_XXspi01_GetSectorIndex(InstanceId, Address)));
}

/**********************************************************************************************************************
 *  vMem_30_XXspi01_WriteAddressCheck()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_WriteAddressCheck(vMem_30_XXspi01_InstanceIdType InstanceId, vMem_30_XXspi01_AddressType Address)
{
  boolean retVal = FALSE;
  uint32 sectorIndex = vMem_30_XXspi01_GetSectorIndex(InstanceId, Address);
  if(vMem_30_XXspi01_IsSectorIndexValid(InstanceId, sectorIndex) == TRUE)
  {
    /* StartAddress of SectorBatch is not always aligned to PageSize. Take offset into account for alignment check. */
    retVal = vMem_30_XXspi01_IsAligned(Address - vMem_30_XXspi01_GetStartAddressOfMemSector(sectorIndex), vMem_30_XXspi01_GetPageSizeOfMemSector(sectorIndex));
  }

  return retVal;
}

/**********************************************************************************************************************
 *  vMem_30_XXspi01_EraseAddressCheck()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_EraseAddressCheck(vMem_30_XXspi01_InstanceIdType InstanceId, vMem_30_XXspi01_AddressType Address)
{
  boolean retVal = FALSE;
  uint32 sectorIndex = vMem_30_XXspi01_GetSectorIndex(InstanceId, Address);
  if(vMem_30_XXspi01_IsSectorIndexValid(InstanceId, sectorIndex) == TRUE)
  {
    /* StartAddress of SectorBatch is not always aligned to SectorSize. Take offset into account for alignment check. */
    retVal = vMem_30_XXspi01_IsAligned(Address - vMem_30_XXspi01_GetStartAddressOfMemSector(sectorIndex), vMem_30_XXspi01_GetSectorSizeOfMemSector(sectorIndex));
  }

  return retVal;
}

/**********************************************************************************************************************
 *  vMem_30_XXspi01_ReadLengthCheck()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_ReadLengthCheck(
  vMem_30_XXspi01_InstanceIdType InstanceId, vMem_30_XXspi01_AddressType Address, vMem_30_XXspi01_LengthType Length)
{
  /* We already know that the passed address is valid. */
  uint32 sectorIndex = vMem_30_XXspi01_GetSectorIndex(InstanceId, Address);
  uint32 remainingSectorBatchLength = ((vMem_30_XXspi01_AddressType)vMem_30_XXspi01_GetSectorSizeOfMemSector(sectorIndex) * (vMem_30_XXspi01_AddressType)vMem_30_XXspi01_GetNrOfSectorsOfMemSector(sectorIndex))
    - (Address - vMem_30_XXspi01_GetStartAddressOfMemSector(sectorIndex));
  /* The passed Length has to point to the same sector batch as the address itself. */
  return (boolean)(Length <= remainingSectorBatchLength); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

}

/**********************************************************************************************************************
 *  vMem_30_XXspi01_WriteLengthCheck()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_WriteLengthCheck(
  vMem_30_XXspi01_InstanceIdType InstanceId, vMem_30_XXspi01_AddressType Address, vMem_30_XXspi01_LengthType Length)
{
  /* Note: We already know that the passed address is valid.
   * If burst is not enabled, generated write burst size equals page size. */
  uint32 sectorIndex = vMem_30_XXspi01_GetSectorIndex(InstanceId, Address);
  return (boolean)((Length == vMem_30_XXspi01_GetPageSizeOfMemSector(sectorIndex)) || /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
    (Length == vMem_30_XXspi01_GetWriteBurstSizeOfMemSector(sectorIndex))); 
}

/**********************************************************************************************************************
 *  vMem_30_XXspi01_EraseLengthCheck()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_EraseLengthCheck(
  vMem_30_XXspi01_InstanceIdType InstanceId, vMem_30_XXspi01_AddressType Address, vMem_30_XXspi01_LengthType Length)
{
  /* Note: We already know that the passed address is valid.
   * If burst is not enabled, generated erase burst size equals sector size. */
  uint32 sectorIndex = vMem_30_XXspi01_GetSectorIndex(InstanceId, Address);
  return (boolean)((Length == vMem_30_XXspi01_GetSectorSizeOfMemSector(sectorIndex)) || /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
    (Length == vMem_30_XXspi01_GetEraseBurstSizeOfMemSector(sectorIndex))); 
}

/**********************************************************************************************************************
 *  vMem_30_XXspi01_InitPendingCheck()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_InitPendingCheck(void)
{
  boolean retVal = TRUE;
  uint32 instanceIndex;
  if(vMem_30_XXspi01_ModuleInitialized == VMEM_30_XXSPI01_INIT)
  {
    for(instanceIndex = 0; instanceIndex < vMem_30_XXspi01_GetSizeOfvMemInstanceOfPCConfig(); instanceIndex++)
    {
      if(vMem_30_XXspi01_InstancePendingCheck(instanceIndex) == TRUE)
      {
        retVal = FALSE;
        break;
      }
    }
  }
  return retVal;
}

/**********************************************************************************************************************
 *  vMem_30_XXspi01_IsAligned()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_IsAligned(uint32 Value, uint32 Alignment)
{
  return (boolean)((Value % Alignment) == 0u); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
}

/**********************************************************************************************************************
 *  vMem_30_XXspi01_IsSectorIndexValid()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_IsSectorIndexValid(vMem_30_XXspi01_InstanceIdType InstanceId, uint32 SectorIndex)
{
  /* By now it has already been checked, that InstanceId is valid. No need, to check instanceIndex again. */
  uint32 instanceIndex = vMem_30_XXspi01_GetInstanceIndex(InstanceId);
  return (boolean)(SectorIndex < vMem_30_XXspi01_GetMemSectorEndIdxOfvMemInstance(instanceIndex)); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
}

/**********************************************************************************************************************
 *  vMem_30_XXspi01_GetInstanceIndex()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(uint32, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_GetInstanceIndex(
  vMem_30_XXspi01_InstanceIdType InstanceId)
{
  /* Default: set out of range value. */
  uint32 retVal = vMem_30_XXspi01_GetSizeOfvMemInstance();
  uint32 i;
  for(i = 0; i < vMem_30_XXspi01_GetSizeOfvMemInstance(); i++)
  {
    if(vMem_30_XXspi01_GetIdOfvMemInstance(i) == InstanceId)
    {
      retVal = i;
      break;
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 *  vMem_30_XXspi01_IsInstanceIndexValid()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_IsInstanceIndexValid(vMem_30_XXspi01_InstanceIdType InstanceIndex)
{
  return (boolean)(InstanceIndex < vMem_30_XXspi01_GetSizeOfvMemInstance()); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
}

/**********************************************************************************************************************
 *  vMem_30_XXspi01_GetSectorIndex()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(uint32, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_GetSectorIndex(
  vMem_30_XXspi01_InstanceIdType InstanceId, vMem_30_XXspi01_AddressType Address)
{
  uint32 sectorIndex = vMem_30_XXspi01_GetSizeOfMemSector();
  /* We already know that InstanceId, and thus InstanceIndex is valid */
  uint32 instanceIndex = vMem_30_XXspi01_GetInstanceIndex(InstanceId);
  uint32 i;
  for (i = vMem_30_XXspi01_GetMemSectorStartIdxOfvMemInstance(instanceIndex); i < vMem_30_XXspi01_GetMemSectorEndIdxOfvMemInstance(instanceIndex); i++)
  {
    /* The address may be equal to the start address or even higher. It shall also be lower than the
     * end of the sector (batch). -1 takes care about overflows - the sector batch may be located
     * at the end of the address range. */
    if((Address >= vMem_30_XXspi01_GetStartAddressOfMemSector(i)) &&
      (Address <= (vMem_30_XXspi01_GetStartAddressOfMemSector(i) +
          (((vMem_30_XXspi01_AddressType)(vMem_30_XXspi01_GetNrOfSectorsOfMemSector(i)) * vMem_30_XXspi01_GetSectorSizeOfMemSector(i)) - 1u))))
    {
      sectorIndex = i;
      break;
    }
  }
  return sectorIndex;
}
#endif /* (VMEM_30_XXSPI01_DEV_ERROR_DETECT == STD_ON) */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vMem_30_XXspi01_Read()
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
 */
FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_Read(
  vMem_30_XXspi01_InstanceIdType InstanceId,
  vMem_30_XXspi01_AddressType SourceAddress,
  vMem_30_XXspi01_DataPtrType TargetAddressPtr,
  vMem_30_XXspi01_LengthType Length
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = VMEM_30_XXSPI01_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
#if (VMEM_30_XXSPI01_DEV_ERROR_DETECT == STD_ON)
  /* Check initialization state of the component */
  if (vMem_30_XXspi01_ModuleInitialized == VMEM_30_XXSPI01_UNINIT)
  {
    errorId = VMEM_30_XXSPI01_E_UNINIT;
  }
  else if (vMem_30_XXspi01_IsInstanceIndexValid(vMem_30_XXspi01_GetInstanceIndex(InstanceId)) == FALSE)
  {
    errorId = VMEM_30_XXSPI01_E_PARAM_INSTANCE_ID;
  }
  else if (vMem_30_XXspi01_InstancePendingCheck(InstanceId) == TRUE)
  {
    errorId = VMEM_30_XXSPI01_E_PENDING;
  }
  else if (TargetAddressPtr == NULL_PTR)
  {
    errorId = VMEM_30_XXSPI01_E_PARAM_POINTER;
  }
  else if(vMem_30_XXspi01_ReadAddressCheck(InstanceId, SourceAddress) == FALSE)
  {
      errorId = VMEM_30_XXSPI01_E_PARAM_ADDRESS;
  }
  else if (vMem_30_XXspi01_ReadLengthCheck(InstanceId, SourceAddress, Length) == FALSE)
  {
      errorId = VMEM_30_XXSPI01_E_PARAM_LENGTH;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    retVal = vMem_30_XXspi01_LLRead(InstanceId, SourceAddress, TargetAddressPtr, Length); /* SBSW_vMem_30_XXspi01_UserPointer */
  }
  
  /* ----- Development Error Report --------------------------------------- */
#if (VMEM_30_XXSPI01_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VMEM_30_XXSPI01_E_NO_ERROR)
  {
    (void)Det_ReportError(VMEM_30_XXSPI01_MODULE_ID, VMEM_30_XXSPI01_INSTANCE_ID_DET, VMEM_30_XXSPI01_SID_READ, errorId);
  }
#else
  VMEM_30_XXSPI01_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif

  return retVal;
} /* vMem_30_XXspi01_Read() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_Write()
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
 */
FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_Write(
  vMem_30_XXspi01_InstanceIdType InstanceId,
  vMem_30_XXspi01_AddressType TargetAddress,
  vMem_30_XXspi01_ConstDataPtrType SourceAddressPtr,
  vMem_30_XXspi01_LengthType Length
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = VMEM_30_XXSPI01_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
#if (VMEM_30_XXSPI01_DEV_ERROR_DETECT == STD_ON)
  /* Check initialization state of the component */
  if (vMem_30_XXspi01_ModuleInitialized == VMEM_30_XXSPI01_UNINIT)
  {
    errorId = VMEM_30_XXSPI01_E_UNINIT;
  }
  else if (vMem_30_XXspi01_IsInstanceIndexValid(vMem_30_XXspi01_GetInstanceIndex(InstanceId)) == FALSE)
  {
    errorId = VMEM_30_XXSPI01_E_PARAM_INSTANCE_ID;
  }
  else if (vMem_30_XXspi01_InstancePendingCheck(InstanceId) == TRUE)
  {
    errorId = VMEM_30_XXSPI01_E_PENDING;
  }
  else if (SourceAddressPtr == NULL_PTR)
  {
    errorId = VMEM_30_XXSPI01_E_PARAM_POINTER;
  }
  else if(vMem_30_XXspi01_WriteAddressCheck(InstanceId, TargetAddress) == FALSE)
  {
      errorId = VMEM_30_XXSPI01_E_PARAM_ADDRESS;
  }
  else if (vMem_30_XXspi01_WriteLengthCheck(InstanceId, TargetAddress, Length) == FALSE)
  {
      errorId = VMEM_30_XXSPI01_E_PARAM_LENGTH;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    retVal = vMem_30_XXspi01_LLWrite(InstanceId, TargetAddress, SourceAddressPtr, Length); /* SBSW_vMem_30_XXspi01_UserPointer */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VMEM_30_XXSPI01_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VMEM_30_XXSPI01_E_NO_ERROR)
  {
    (void)Det_ReportError(VMEM_30_XXSPI01_MODULE_ID, VMEM_30_XXSPI01_INSTANCE_ID_DET, VMEM_30_XXSPI01_SID_WRITE, errorId);
  }
#else
  VMEM_30_XXSPI01_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif

  return retVal;
} /* vMem_30_XXspi01_Write() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */


/**********************************************************************************************************************
 *  vMem_30_XXspi01_Erase()
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
FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_Erase(
  vMem_30_XXspi01_InstanceIdType InstanceId,
  vMem_30_XXspi01_AddressType TargetAddress,
  vMem_30_XXspi01_LengthType Length
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = VMEM_30_XXSPI01_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
#if (VMEM_30_XXSPI01_DEV_ERROR_DETECT == STD_ON)
  /* Check initialization state of the component */
  if (vMem_30_XXspi01_ModuleInitialized == VMEM_30_XXSPI01_UNINIT)
  {
    errorId = VMEM_30_XXSPI01_E_UNINIT;
  }
  else if (vMem_30_XXspi01_IsInstanceIndexValid(vMem_30_XXspi01_GetInstanceIndex(InstanceId)) == FALSE)
  {
    errorId = VMEM_30_XXSPI01_E_PARAM_INSTANCE_ID;
  }
  else if (vMem_30_XXspi01_InstancePendingCheck(InstanceId) == TRUE)
  {
    errorId = VMEM_30_XXSPI01_E_PENDING;
  }
  else if(vMem_30_XXspi01_EraseAddressCheck(InstanceId, TargetAddress) == FALSE)
  {
      errorId = VMEM_30_XXSPI01_E_PARAM_ADDRESS;
  }
  else if (vMem_30_XXspi01_EraseLengthCheck(InstanceId, TargetAddress, Length) == FALSE)
  {
      errorId = VMEM_30_XXSPI01_E_PARAM_LENGTH;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    retVal = vMem_30_XXspi01_LLErase(InstanceId, TargetAddress, Length);
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VMEM_30_XXSPI01_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VMEM_30_XXSPI01_E_NO_ERROR)
  {
    (void)Det_ReportError(VMEM_30_XXSPI01_MODULE_ID, VMEM_30_XXSPI01_INSTANCE_ID_DET, VMEM_30_XXSPI01_SID_ERASE, errorId);
  }
#else
  VMEM_30_XXSPI01_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif

  return retVal;
} /* vMem_30_XXspi01_Erase() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */


/**********************************************************************************************************************
 *  vMem_30_XXspi01_GetJobResult()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(vMem_30_XXspi01_JobResultType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_GetJobResult(
  vMem_30_XXspi01_InstanceIdType InstanceId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = VMEM_30_XXSPI01_E_NO_ERROR;
  vMem_30_XXspi01_JobResultType jobResult = VMEM_JOB_FAILED; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
#if (VMEM_30_XXSPI01_DEV_ERROR_DETECT == STD_ON)
  /* Check initialization state of the component */
  if (vMem_30_XXspi01_ModuleInitialized == VMEM_30_XXSPI01_UNINIT)
  {
    errorId = VMEM_30_XXSPI01_E_UNINIT;
  }
  else if (vMem_30_XXspi01_IsInstanceIndexValid(vMem_30_XXspi01_GetInstanceIndex(InstanceId)) == FALSE)
  {
    errorId = VMEM_30_XXSPI01_E_PARAM_INSTANCE_ID;
  }
  else
#endif
  {
  /* ----- Implementation ----------------------------------------------- */
    jobResult = vMem_30_XXspi01_LLGetJobResult(InstanceId);
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VMEM_30_XXSPI01_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VMEM_30_XXSPI01_E_NO_ERROR)
  {
    (void)Det_ReportError(VMEM_30_XXSPI01_MODULE_ID, VMEM_30_XXSPI01_INSTANCE_ID_DET, VMEM_30_XXSPI01_SID_GET_JOB_RESULT, errorId);
  }
#else
  VMEM_30_XXSPI01_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif

  return jobResult;
} /* vMem_30_XXspi01_GetJobResult() */



/**********************************************************************************************************************
 *  vMem_30_XXspi01_InitMemory()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_InitMemory(void)
{
  /* ----- Implementation ----------------------------------------------- */
#if (VMEM_30_XXSPI01_DEV_ERROR_DETECT == STD_ON)
  vMem_30_XXspi01_ModuleInitialized = VMEM_30_XXSPI01_UNINIT;
#endif
}  /* vMem_30_XXspi01_InitMemory() */


/**********************************************************************************************************************
 *  vMem_30_XXspi01_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_Init(P2CONST(vMem_30_XXspi01_ConfigType, AUTOMATIC, VMEM_30_XXSPI01_PBCFG) ConfigPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = VMEM_30_XXSPI01_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (VMEM_30_XXSPI01_DEV_ERROR_DETECT == STD_ON)
  if (vMem_30_XXspi01_InitPendingCheck() == FALSE)
  {
    errorId = VMEM_30_XXSPI01_E_PENDING;
  }
  else
#endif
  {
  /* ----- Implementation ----------------------------------------------- */
  /* Do not use the ConfigPtr, simply ignore the parameter (vMem_30_XXspi01 is not post build capable yet). */
    if (vMem_30_XXspi01_LLInit() == E_NOT_OK)
    {
      errorId = VMEM_30_XXSPI01_E_INITIALIZATION_FAILED;
    }
  }
#if (VMEM_30_XXSPI01_DEV_ERROR_DETECT == STD_ON)
  if (errorId == VMEM_30_XXSPI01_E_NO_ERROR)
  {
    vMem_30_XXspi01_ModuleInitialized = VMEM_30_XXSPI01_INIT;
  }
#endif
#if (VMEM_30_XXSPI01_DEV_ERROR_REPORT == STD_ON)
  else
  {
    (void)Det_ReportError(VMEM_30_XXSPI01_MODULE_ID, VMEM_30_XXSPI01_INSTANCE_ID_DET, VMEM_30_XXSPI01_SID_INIT, errorId);
  }
#else
  VMEM_30_XXSPI01_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif
  VMEM_30_XXSPI01_DUMMY_STATEMENT(ConfigPtr); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
} /* vMem_30_XXspi01_Init() */


/***********************************************************************************************************************
 *  vMem_30_XXspi01_MainFunction
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_MainFunction(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = VMEM_30_XXSPI01_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (VMEM_30_XXSPI01_DEV_ERROR_DETECT == STD_ON)
  /* Check initialization state of the component */
  if (vMem_30_XXspi01_ModuleInitialized == VMEM_30_XXSPI01_UNINIT)
  {
    errorId = VMEM_30_XXSPI01_E_UNINIT;
  }
  else
#endif
  {
    vMem_30_XXspi01_LLProcessing();
  }
  /* ----- Development Error Report --------------------------------------- */
#if (VMEM_30_XXSPI01_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VMEM_30_XXSPI01_E_NO_ERROR)
  {
    (void)Det_ReportError(VMEM_30_XXSPI01_MODULE_ID, VMEM_30_XXSPI01_INSTANCE_ID_DET, VMEM_30_XXSPI01_SID_MAIN_FUNCTION, errorId);
  }
#else
  VMEM_30_XXSPI01_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif
} /* vMem_30_XXspi01_MainFunction */


#if (VMEM_30_XXSPI01_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  vMem_30_XXspi01_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, VMEM_30_XXSPI01_APPL_VAR) VersionInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = VMEM_30_XXSPI01_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (VMEM_30_XXSPI01_DEV_ERROR_DETECT == STD_ON)
  if (VersionInfo == NULL_PTR)
  {
    errorId = VMEM_30_XXSPI01_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    VersionInfo->vendorID = (VMEM_30_XXSPI01_VENDOR_ID); /* SBSW_vMem_30_XXspi01_UserPointer */
    VersionInfo->moduleID = (VMEM_30_XXSPI01_MODULE_ID); /* SBSW_vMem_30_XXspi01_UserPointer */
    VersionInfo->sw_major_version = (VMEM_30_XXSPI01_SW_MAJOR_VERSION); /* SBSW_vMem_30_XXspi01_UserPointer */
    VersionInfo->sw_minor_version = (VMEM_30_XXSPI01_SW_MINOR_VERSION); /* SBSW_vMem_30_XXspi01_UserPointer */
    VersionInfo->sw_patch_version = (VMEM_30_XXSPI01_SW_PATCH_VERSION); /* SBSW_vMem_30_XXspi01_UserPointer */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VMEM_30_XXSPI01_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VMEM_30_XXSPI01_E_NO_ERROR)
  {
    (void)Det_ReportError(VMEM_30_XXSPI01_MODULE_ID, VMEM_30_XXSPI01_INSTANCE_ID_DET, VMEM_30_XXSPI01_SID_GET_VERSION_INFO, errorId);
  }
# else
  VMEM_30_XXSPI01_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
# endif
}
#endif


#define VMEM_30_XXSPI01_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_vMem_30_XXspi01_UserPointer
 \DESCRIPTION Pointer write access or function call: vMem_30_XXspi01 gets a pointer to write information to. vMem_30_XXspi01 expects the pointer to be typed
              correctly and will use it, if it is != NULL_PTR. vMem_30_XXspi01 writes to the pointer or forwards it to another component internal function.
 \COUNTERMEASURE \R vMem_30_XXspi01 checks the passed pointer to be != NULL_PTR. User is responsible for pointer correctness.

SBSW_JUSTIFICATION_END */

/* START_COVERAGE_JUSTIFICATION

Variant coverage:

\ID COV_VMEM_30_XXSPI01_COMPATIBILITY
 \ACCEPT TX
 \REASON COV_MSR_COMPATIBILITY

END_COVERAGE_JUSTIFICATION
*/

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXspi01.c
 *********************************************************************************************************************/
