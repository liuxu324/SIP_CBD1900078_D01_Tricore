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
/*!        \file  vMem_30_XXspi01_LL_FlsCmdSeqBuilder.h
 *        \brief  Flash command sequence builder header file
 *
 *      \details  The vMem_30_XXspi01_LL_FlsCmdSeqBuilder implements the generation of the necessary flash command
 *                sequences for the interaction with the flash device.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (VMEM_30_XXSPI01_LL_FLSCMDSEQBUILDER_H)
# define VMEM_30_XXSPI01_LL_FLSCMDSEQBUILDER_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "vMem_30_XXspi01_LL_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define VMEM_30_XXSPI01_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadSequence()
 *********************************************************************************************************************/
/*! \brief       Gets the read command sequence for read access.
 *  \details     vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadSequence() builds the prepared sequence of commands that
 *               is used to read data from the flash device identified by the given instance.
 *  \param[in]   instanceIndex       Index of the related vMem_30_XXspi01 instance.
 *  \param[in]   sourceAddress       NV memory address to read from.
 *  \param[in]   targetAddressPtr    Application pointer to buffer to write to.
 *  \param[in]   length              Length to be read.
 *  \return      Pointer to flash command sequence.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadSequence(
  vMem_30_XXspi01_InstanceIdType instanceIndex,
  vMem_30_XXspi01_AddressType sourceAddress,
  vMem_30_XXspi01_SpiDataPtrType targetAddressPtr,
  vMem_30_XXspi01_SpiLengthType length);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteSequence()
 *********************************************************************************************************************/
/*! \brief       Gets the write command sequence for write access.
 *  \details     vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteSequence() builds the prepared sequence of commands that
 *               is used to write data to the flash device identified by the given instance.
 *  \param[in]   instanceIndex       Index of the related vMem_30_XXspi01 instance.
 *  \param[in]   targetAddress       NV memory address to write to.
 *  \param[in]   sourceAddressPtr    Application pointer to buffer with data to write to nv memory.
 *  \param[in]   length              Length to write.
 *  \return      Pointer to flash command sequence.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteSequence(
  vMem_30_XXspi01_InstanceIdType instanceIndex,
  vMem_30_XXspi01_AddressType targetAddress,
  vMem_30_XXspi01_ConstSpiDataPtrType sourceAddressPtr,
  vMem_30_XXspi01_SpiLengthType length);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetEraseSequence()
 *********************************************************************************************************************/
/*! \brief       Gets the erase command sequence for erase access.
 *  \details     vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetEraseSequence() builds the prepared sequence of commands that
 *               is used to erase memory in the flash devices identified by the given instance.
 *  \param[in]   instanceIndex       Index of the related vMem_30_XXspi01 instance.
 *  \param[in]   targetAddress       Address of the nv sector that shall be erased.
 *  \return      Pointer to flash command sequence.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetEraseSequence(
  vMem_30_XXspi01_InstanceIdType instanceIndex,
  vMem_30_XXspi01_AddressType targetAddress);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetStatusRegisterSequence()
 *********************************************************************************************************************/
/*! \brief       Gets the command sequence for reading the status register of the flash device.
 *  \details     vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetStatusRegisterSequence() builds the prepared sequence of commands that
 *               is used to read the status register of the flash devices identified by the given instance.
 *  \param[in]   instanceIndex       Index of the related vMem_30_XXspi01 instance.
 *  \param[in]   bufferPtr           Pointer to the buffer where the register content is stored.
 *  \param[in]   length              Length of the status register that shall be read.
 *  \return      Pointer to flash command sequence.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetStatusRegisterSequence(
    vMem_30_XXspi01_InstanceIdType instanceIndex,
    vMem_30_XXspi01_SpiDataPtrType bufferPtr,
    vMem_30_XXspi01_SpiLengthType length);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetExtendedProgressCheckRegisterSequence()
 *********************************************************************************************************************/
/*! \brief       Gets the command sequence for reading the extended progress check register of the flash device.
 *  \details     vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetExtendedProgressCheckRegisterSequence() builds the prepared
 *               sequence of commands that is used to read the extended progress check register of the flash devices identified
 *               by the given instance.
 *  \param[in]   instanceIndex       Index of the related vMem_30_XXspi01 instance.
 *  \param[in]   bufferPtr           Pointer to the buffer where the register content is stored.
 *  \param[in]   length              Length of the status register that shall be read.
 *  \return      Pointer to flash command sequence.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetExtendedProgressCheckRegisterSequence(
    vMem_30_XXspi01_InstanceIdType instanceIndex,
    vMem_30_XXspi01_SpiDataPtrType bufferPtr,
    vMem_30_XXspi01_SpiLengthType length);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetResultRegisterSequence()
 *********************************************************************************************************************/
/*! \brief       Gets the command sequence for reading the result register of the flash device.
 *  \details     vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetResultRegisterSequence() builds the prepared sequence of commands that
 *               is used to read the result register of the flash devices identified by the given instance.
 *  \return      Pointer to flash command sequence.
 *  \param[in]   instanceIndex       Index of the related vMem_30_XXspi01 instance.
 *  \param[in]   bufferPtr           Pointer to the buffer where the register content is stored.
 *  \param[in]   length              Length of the result register that shall be read.
 *  \return      Pointer to flash command sequence.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetResultRegisterSequence(
    vMem_30_XXspi01_InstanceIdType instanceIndex,
    vMem_30_XXspi01_SpiDataPtrType bufferPtr,
    vMem_30_XXspi01_SpiLengthType length);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetClearResultRegisterSequence()
 *********************************************************************************************************************/
/*! \brief       Gets the command sequence for clearing the result register of the flash device.
 *  \details     vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetClearResultRegisterSequence() builds the prepared sequence of commands that
 *               is used to clear the result register of the flash devices identified by the given instance.
 *  \param[in]   instanceIndex       Index of the related vMem_30_XXspi01 instance.
 *  \return      Pointer to flash command sequence.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetClearResultRegisterSequence(
    vMem_30_XXspi01_InstanceIdType instanceIndex);

# define VMEM_30_XXSPI01_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VMEM_30_XXSPI01_LL_FLSCMDSEQBUILDER_H */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXspi01_LL_FlsCmdSeqBuilder.h
 *********************************************************************************************************************/
