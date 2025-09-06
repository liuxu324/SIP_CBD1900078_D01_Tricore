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
/*!        \file  vMem_30_XXspi01_Int.h
 *        \brief  vMem_30_XXspi01 internal header file for declaration of vMem_30_XXspi01 common API
 *
 *      \details  This file contains the declarations of the common vMem_30_XXspi01 API Read, Write, Erase and GetJobResult.
 *                These API can be called via the FunctionPointerTable which is filled in the LowLevel part
 *                of the component.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (VMEM_30_XXSPI01_INT_H)
# define VMEM_30_XXSPI01_INT_H

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define VMEM_30_XXSPI01_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_Read()
 *********************************************************************************************************************/
/*! \brief       Asynchronous service to read data analogous to Fls.
 *  \details     vMem_30_XXspi01_Read() returns the requested data. Parameter checks are done within core part.
 *  \param[in]   InstanceId          ID of the related vMem_30_XXspi01 instance.
 *  \param[in]   SourceAddress       NV memory address to read from.
 *  \param[out]  TargetAddressPtr    application pointer to buffer to write to. Must stay valid until job is completed.
 *  \param[in]   Length              Length in bytes to be read.
 *  \return      E_OK job accepted and queued, E_NOT_OK otherwise.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_Read(
  vMem_30_XXspi01_InstanceIdType InstanceId,
  vMem_30_XXspi01_AddressType SourceAddress,
  vMem_30_XXspi01_DataPtrType TargetAddressPtr,
  vMem_30_XXspi01_LengthType Length
  );

/**********************************************************************************************************************
 *  vMem_30_XXspi01_Write()
 *********************************************************************************************************************/
/*! \brief       Asynchronous service to write data to nv memory.
 *  \details     vMem_30_XXspi01_Write() writes data to nv memory. Parameter checks are done within core part. vMem_30_XXspi01 may use burst
 *               capabilities if supported and configured.
 *  \param[in]   InstanceId          ID of the related vMem_30_XXspi01 instance.
 *  \param[in]   TargetAddress       NV memory address to write to.
 *  \param[in]   SourceAddressPtr    application pointer to buffer with data to write to nv memory.
 *                                   Must stay valid until job is completed.
 *  \param[in]   Length              Length in bytes to write.
 *  \return      E_OK job accepted and queued, E_NOT_OK otherwise.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_Write(
  vMem_30_XXspi01_InstanceIdType InstanceId,
  vMem_30_XXspi01_AddressType TargetAddress,
  vMem_30_XXspi01_ConstDataPtrType SourceAddressPtr,
  vMem_30_XXspi01_LengthType Length
  );

/**********************************************************************************************************************
 *  vMem_30_XXspi01_Erase()
 *********************************************************************************************************************/
/*! \brief       Asynchronous service to erase data from nv memory.
 *  \details     vMem_30_XXspi01_Erase() erases data from nv memory. Parameter checks are done within core part. vMem_30_XXspi01 may use burst
 *               capabilities if supported and configured.
 *  \param[in]   InstanceId          ID of the related vMem_30_XXspi01 instance.
 *  \param[in]   TargetAddress       NV memory address to be erased.
 *  \param[in]   Length              Length in bytes to erase.
 *  \return      E_OK job accepted and queued, E_NOT_OK otherwise.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_Erase(
  vMem_30_XXspi01_InstanceIdType InstanceId,
  vMem_30_XXspi01_AddressType TargetAddress,
  vMem_30_XXspi01_LengthType Length
  );

/**********************************************************************************************************************
 *  vMem_30_XXspi01_GetJobResult()
 *********************************************************************************************************************/
/*! \brief       Returns the result of the last accepted job.
 *  \details     -
 *  \param[in]   InstanceId          ID of the related vMem_30_XXspi01 instance.
 *  \return      Current job result.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(vMem_30_XXspi01_JobResultType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_GetJobResult(vMem_30_XXspi01_InstanceIdType InstanceId);

# define VMEM_30_XXSPI01_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* VMEM_30_XXSPI01_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXspi01_Int.h
 *********************************************************************************************************************/
