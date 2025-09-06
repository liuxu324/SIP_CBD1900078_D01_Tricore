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
/*!        \file  vMem_30_XXspi01_LL.h
 *        \brief  vMem_30_XXspi01 LowLevel header file
 *
 *      \details  The vMem_30_XXspi01 LowLevel subcomponent implements all the hardware specific functionality of the
 *                vMem_30_XXspi01. It performs the actual access of the NV device. It also implements a state machine
 *                for the processing of the asynchronous jobs.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (VMEM_30_XXSPI01_LL_H)
# define VMEM_30_XXSPI01_LL_H

/*********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "vMemAccM_vMemApi.h"
# include "vMem_30_XXspi01_LL_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*!< Number of extended hardware specific functionality. This equals the size of the array of hardware specific functions. */
# define VMEM_30_XXSPI01_EXTENDED_FUNCTION_COUNT    0u
/*!< Define for the table of hardware specific functionality. */
# define VMEM_30_XXSPI01_EXTENDED_FUNCTION_TABLE    NULL_PTR

/* This is not simply commented code but an example how to publish hardware specific jobs (an array of size zero
 * leads to compiler warnings):
 */
/*
 * # define VMEM_30_XXSPI01_EXTENDED_FUNCTION_TABLE vMem_30_XXspi01_HwSpecificFunctions
 */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
# define VMEM_30_XXSPI01_START_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*
 * extern CONST(vMem_30_XXspi01AccM_vMem_30_XXspi01HwSpecificFuncPtr, AUTOMATIC) vMem_30_XXspi01_HwSpecificFunctions[VMEM_30_XXSPI01_EXTENDED_FUNCTION_COUNT];
 */

# define VMEM_30_XXSPI01_STOP_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define VMEM_30_XXSPI01_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLSeqEndNotification()
 *********************************************************************************************************************/
/*! \brief        Callback service to notify the vMem module about a finished sequence.
 *  \details      -
 *  \param[in]    instanceIndex      Index of the related vMem_30_XXspi01 instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLSeqEndNotification(vMem_30_XXspi01_InstanceIdType instanceIndex);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLRead()
 *********************************************************************************************************************/
/*! \brief       Synchronous service to read data using memcpy.
 *  \details     vMem_30_XXspi01_LLRead() returns the requested data. Parameter checks are done within core part.
 *  \param[in]   InstanceId          ID of the related vMem_30_XXspi01 instance, must be valid.
 *  \param[in]   SourceAddress       NV memory address to read from, must be valid.
 *  \param[out]  TargetAddressPtr    application pointer to buffer to write to. Must stay valid until job is completed.
 *  \param[in]   Length              Length in bytes to be read, must be valid.
 *  \return      E_OK job accepted, E_NOT_OK otherwise.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLRead(
  vMem_30_XXspi01_InstanceIdType InstanceId,
  vMem_30_XXspi01_AddressType SourceAddress,
  vMem_30_XXspi01_DataPtrType TargetAddressPtr,
  vMem_30_XXspi01_LengthType Length);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLWrite()
 *********************************************************************************************************************/
/*! \brief       Asynchronous service to write data to nv memory.
 *  \details     vMem_30_XXspi01_LLWrite() Write data to nv memory. Parameter checks are done within core part.
 *  \param[in]   InstanceId          ID of the related vMem_30_XXspi01 instance, must be valid.
 *  \param[in]   TargetAddress       NV memory address to write to, must be valid.
 *  \param[in]   SourceAddressPtr    application pointer to buffer with data to write to nv memory.
 *                                   Must stay valid until job is completed.
 *  \param[in]   Length              Length in bytes to write, must be valid.
 *  \return      E_OK job accepted, E_NOT_OK otherwise.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLWrite(
  vMem_30_XXspi01_InstanceIdType InstanceId,
  vMem_30_XXspi01_AddressType TargetAddress,
  vMem_30_XXspi01_ConstDataPtrType SourceAddressPtr,
  vMem_30_XXspi01_LengthType Length
  );

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLErase()
 *********************************************************************************************************************/
/*! \brief       Asynchronous service to erase data from nv memory.
 *  \details     vMem_30_XXspi01_LLErase() erases data from nv memory. Parameter checks are done within core part.
 *  \param[in]   InstanceId          ID of the related vMem_30_XXspi01 instance, must be valid.
 *  \param[in]   TargetAddress       NV memory address to be erased, must be valid.
 *  \param[in]   Length              Length in bytes to erase, must be valid.
 *  \return      E_OK job accepted, E_NOT_OK otherwise.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLErase(
  vMem_30_XXspi01_InstanceIdType InstanceId,
  vMem_30_XXspi01_AddressType TargetAddress,
  vMem_30_XXspi01_LengthType Length
  );

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLGetJobResult()
 *********************************************************************************************************************/
/*! \brief       Returns the result of the last accepted job, as long as no new job is accepted.
 *  \details     -
 *  \param[in]   InstanceId          ID of the related vMem_30_XXspi01 instance, must be valid.
 *  \return      Current job result.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(vMem_30_XXspi01_JobResultType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLGetJobResult(vMem_30_XXspi01_InstanceIdType InstanceId);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLProcessing()
 *********************************************************************************************************************/
/*! \brief       Processes the vMem_30_XXspi01 LowLevel state machine, returns when done.
 *  \details     -
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLProcessing(void);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLInit()
 *********************************************************************************************************************/
/*! \brief       Initializes LowLevel part of component.
 *  \details     -
 *  \return      E_OK initialization successful, E_NOT_OK initialization failed.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLInit(void);

# define VMEM_30_XXSPI01_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* VMEM_30_XXSPI01_LL_H */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXspi01_LL.h
 *********************************************************************************************************************/
