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
/*!        \file  vMem_30_XXspi01_LL_FlsCmdSeqBuilder.c
 *        \brief  Flash command sequence builder source file
 *
 *      \details  See vMem_30_XXspi01_LL_FlsCmdSeqBuilder.h
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define VMEM_30_XXSPI01_LL_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vMem_30_XXspi01_LL_FlsCmdSeqBuilder.h"
#include "vMem_30_XXspi01_Cfg.h"

#if (VMEM_30_XXSPI01_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! One byte bitmask. */
#define VMEM_30_XXSPI01_BYTE_MASK (uint8)(0xFF)

/*! Size of the address buffer for each instance */
#define VMEM_30_XXSPI01_ADDRESS_BUFFER_SIZE (0x04u)

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (VMEM_XXSPI01_LOCAL) /* COV_VMEM_30_XXSPI01_COMPATIBILITY */
# define VMEM_30_XXSPI01_LOCAL static
#endif

#if !defined (VMEM_XXSPI01_LOCAL_INLINE) /* COV_VMEM_30_XXSPI01_COMPATIBILITY */
# define VMEM_30_XXSPI01_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define VMEM_30_XXSPI01_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

VMEM_30_XXSPI01_LOCAL vMem_30_XXspi01_FlsCmdSequenceType FlashSequenceBuffer[vMem_30_XXspi01_GetSizeOfvMemInstance()];

VMEM_30_XXSPI01_LOCAL vMem_30_XXspi01_SpiDataType AddressBuffer[vMem_30_XXspi01_GetSizeOfvMemInstance()][VMEM_30_XXSPI01_ADDRESS_BUFFER_SIZE]; /* PRQA S 3218 */ /* MD_vMem_XXspi01_3218 */

#define VMEM_30_XXSPI01_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define VMEM_30_XXSPI01_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_GetAddressBuffer()
 *********************************************************************************************************************/
/*! \brief       Fills the address buffer for the given instance.
 *  \details     The function fills the address buffer of the given instance with the value of the given instance.
 *               The length of the address buffer depends on the configured address mode.
 *  \param[in]   instanceIndex       Index of the instance the address buffer shall be filled for.
 *  \param[in]   address             The address that shall be written into the address buffer.
 *  \param[out]  addressBuffer       Pointer to the filled address buffer.
 *  \param[out]  addressBufferLength Length of the filled address buffer.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_GetAddressBuffer(
  vMem_30_XXspi01_InstanceIdType instanceIndex,
  vMem_30_XXspi01_AddressType address,
  vMem_30_XXspi01_SpiDataPtrPtrType addressBuffer,
  vMem_30_XXspi01_SpiLengthPtrType addressBufferLength);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_GetAddressBuffer()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_GetAddressBuffer(
  vMem_30_XXspi01_InstanceIdType instanceIndex,
  vMem_30_XXspi01_AddressType address,
  vMem_30_XXspi01_SpiDataPtrPtrType addressBuffer,
  vMem_30_XXspi01_SpiLengthPtrType addressBufferLength)
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  /* #10 Get the address buffer of the given instance. */
  vMem_30_XXspi01_SpiDataPtrType buffer = &AddressBuffer[instanceIndex][0];

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  *addressBuffer = buffer; /* SBSW_vMem_30_XXspi01_AddressBufferAssignment */

  /* #20 If extended addressing is enables, fill the address buffer with all four bytes of the address. */
  if(vMem_30_XXspi01_LL_Cfg_IsExtendedAddressingEnabled(instanceIndex))
  {
    buffer[0] = (vMem_30_XXspi01_SpiDataType)(address >> 24); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
    buffer[1] = (vMem_30_XXspi01_SpiDataType)((address >> 16) & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
    buffer[2] = (vMem_30_XXspi01_SpiDataType)((address >> 8) & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
    buffer[3] = (vMem_30_XXspi01_SpiDataType)(address & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */

    *addressBufferLength = VMEM_30_XXSPI01_ADDRESS_BUFFER_SIZE; /* SBSW_vMem_30_XXspi01_AddressBufferLengthWriteAccess */
  }
  /* #30 Otherwise use only the lower three bytes of the address. */
  else
  {
    buffer[0] = (vMem_30_XXspi01_SpiDataType)((address >> 16) & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
    buffer[1] = (vMem_30_XXspi01_SpiDataType)((address >> 8) & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */
    buffer[2] = (vMem_30_XXspi01_SpiDataType)(address & VMEM_30_XXSPI01_BYTE_MASK); /* SBSW_vMem_30_XXspi01_AddressBufferWriteAccess */

    *addressBufferLength = VMEM_30_XXSPI01_ADDRESS_BUFFER_SIZE-1; /* SBSW_vMem_30_XXspi01_AddressBufferLengthWriteAccess */
  }
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadSequence()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadSequence(
  vMem_30_XXspi01_InstanceIdType instanceIndex,
  vMem_30_XXspi01_AddressType sourceAddress,
  vMem_30_XXspi01_SpiDataPtrType targetAddressPtr,
  vMem_30_XXspi01_SpiLengthType length)
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  vMem_30_XXspi01_SpiDataPtrType addressBufferPtr = NULL_PTR;
  vMem_30_XXspi01_SpiLengthType addressBufferLength = 0u;
  vMem_30_XXspi01_FlsCmdSequencePtrType instSeqBuffer = &(FlashSequenceBuffer[instanceIndex]);

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  instSeqBuffer->SpiSequence = vMem_30_XXspi01_LL_Cfg_GetSpiReadSeq(instanceIndex); /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */
  instSeqBuffer->FlsCmdItemCount = 3; /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */

  /* #10 Setup read command channel. */
  instSeqBuffer->FlsCmdItems[0].SpiChannel = vMem_30_XXspi01_LL_Cfg_GetSpiReadChls(instanceIndex, 0u); /* PRQA S 2985 */ /* MD_vMem_XXspi01_2985 */ /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].SendDataBufferPtr = &(vMem_30_XXspi01_LL_Cfg_GetFlsDeviceReadCommand(instanceIndex)); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

  /* #20 Setup read address channel. */
  vMem_30_XXspi01_LL_GetAddressBuffer(instanceIndex,
      sourceAddress,
      &addressBufferPtr,
      &addressBufferLength); /* SBSW_vMem_30_XXspi01_GetAddressBuffer */

  instSeqBuffer->FlsCmdItems[1].SpiChannel = vMem_30_XXspi01_LL_Cfg_GetSpiReadChls(instanceIndex, 1u); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[1].SendDataBufferPtr = addressBufferPtr; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[1].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[1].DataBufferLength = addressBufferLength; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

  /* #30 Setup read data channel. */
  instSeqBuffer->FlsCmdItems[2].SpiChannel = vMem_30_XXspi01_LL_Cfg_GetSpiReadChls(instanceIndex, 2u); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[2].SendDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[2].ReceiveDataBufferPtr = targetAddressPtr; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[2].DataBufferLength = length; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

  return instSeqBuffer;
}

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteSequence()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteSequence(
  vMem_30_XXspi01_InstanceIdType instanceIndex,
  vMem_30_XXspi01_AddressType targetAddress,
  vMem_30_XXspi01_ConstSpiDataPtrType sourceAddressPtr,
  vMem_30_XXspi01_SpiLengthType length)
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  vMem_30_XXspi01_SpiDataPtrType addressBufferPtr = NULL_PTR;
  vMem_30_XXspi01_SpiLengthType addressBufferLength = 0u;
  vMem_30_XXspi01_FlsCmdSequencePtrType instSeqBuffer = &(FlashSequenceBuffer[instanceIndex]);

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  instSeqBuffer->SpiSequence = vMem_30_XXspi01_LL_Cfg_GetSpiWriteSeq(instanceIndex); /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */
  instSeqBuffer->FlsCmdItemCount = 4; /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */

  /* #10 Setup write enable channel. */
  instSeqBuffer->FlsCmdItems[0].SpiChannel = vMem_30_XXspi01_LL_Cfg_GetSpiWriteChls(instanceIndex, 0u); /* PRQA S 2985 */ /* MD_vMem_XXspi01_2985 */ /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].SendDataBufferPtr = &(vMem_30_XXspi01_LL_Cfg_GetFlsDeviceWriteEnableCommand(instanceIndex)); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

  /* #20 Setup write command channel. */
  instSeqBuffer->FlsCmdItems[1].SpiChannel = vMem_30_XXspi01_LL_Cfg_GetSpiWriteChls(instanceIndex, 1u); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[1].SendDataBufferPtr = &(vMem_30_XXspi01_LL_Cfg_GetFlsDeviceWriteCommand(instanceIndex)); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[1].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[1].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

  /* #30 Setup write address channel. */
  vMem_30_XXspi01_LL_GetAddressBuffer(instanceIndex,
      targetAddress,
      &addressBufferPtr,
      &addressBufferLength); /* SBSW_vMem_30_XXspi01_GetAddressBuffer */

  instSeqBuffer->FlsCmdItems[2].SpiChannel = vMem_30_XXspi01_LL_Cfg_GetSpiWriteChls(instanceIndex, 2u); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[2].SendDataBufferPtr = addressBufferPtr; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[2].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[2].DataBufferLength = addressBufferLength; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

  /* #40 Setup write data channel. */
  instSeqBuffer->FlsCmdItems[3].SpiChannel = vMem_30_XXspi01_LL_Cfg_GetSpiWriteChls(instanceIndex, 3u); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[3].SendDataBufferPtr = sourceAddressPtr; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[3].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[3].DataBufferLength = length; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

  return instSeqBuffer;
}

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetEraseSequence()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetEraseSequence(
  vMem_30_XXspi01_InstanceIdType instanceIndex,
  vMem_30_XXspi01_AddressType targetAddress
  )
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  vMem_30_XXspi01_SpiDataPtrType addressBufferPtr = NULL_PTR;
  vMem_30_XXspi01_SpiLengthType addressBufferLength = 0u;
  vMem_30_XXspi01_FlsCmdSequencePtrType instSeqBuffer = &(FlashSequenceBuffer[instanceIndex]);

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  instSeqBuffer->SpiSequence = vMem_30_XXspi01_LL_Cfg_GetSpiEraseSeq(instanceIndex); /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */
  instSeqBuffer->FlsCmdItemCount = 3; /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */

  /* #10 Setup write enable channel. */
  instSeqBuffer->FlsCmdItems[0].SpiChannel = vMem_30_XXspi01_LL_Cfg_GetSpiEraseChls(instanceIndex, 0u); /* PRQA S 2985 */ /* MD_vMem_XXspi01_2985 */ /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].SendDataBufferPtr = &(vMem_30_XXspi01_LL_Cfg_GetFlsDeviceWriteEnableCommand(instanceIndex)); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

  /* #20 Setup erase command channel. */
  instSeqBuffer->FlsCmdItems[1].SpiChannel = vMem_30_XXspi01_LL_Cfg_GetSpiEraseChls(instanceIndex, 1u); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[1].SendDataBufferPtr = &(vMem_30_XXspi01_LL_Cfg_GetFlsDeviceEraseCommand(instanceIndex)); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[1].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[1].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

  /* #30 Setup erase address channel. */
  vMem_30_XXspi01_LL_GetAddressBuffer(instanceIndex,
      targetAddress,
      &addressBufferPtr,
      &addressBufferLength); /* SBSW_vMem_30_XXspi01_GetAddressBuffer */

  instSeqBuffer->FlsCmdItems[2].SpiChannel = vMem_30_XXspi01_LL_Cfg_GetSpiEraseChls(instanceIndex, 2u); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[2].SendDataBufferPtr = addressBufferPtr; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[2].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[2].DataBufferLength = addressBufferLength; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

  return instSeqBuffer;
}

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetStatusRegisterSequence()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetStatusRegisterSequence(
    vMem_30_XXspi01_InstanceIdType instanceIndex,
    vMem_30_XXspi01_SpiDataPtrType bufferPtr,
    vMem_30_XXspi01_SpiLengthType length)
{
   /* ------ Local variables ---------------------------------------------------------------------------------------- */
   vMem_30_XXspi01_FlsCmdSequencePtrType instSeqBuffer = &(FlashSequenceBuffer[instanceIndex]);

   /* ------ Implementation ----------------------------------------------------------------------------------------- */
   instSeqBuffer->SpiSequence = vMem_30_XXspi01_LL_Cfg_GetSpiReadStatusRegSeq(instanceIndex); /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */
   instSeqBuffer->FlsCmdItemCount = 2; /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */

   /* #10 Setup read status register command channel. */
   instSeqBuffer->FlsCmdItems[0].SpiChannel = vMem_30_XXspi01_LL_Cfg_GetSpiReadStatusRegisterChls(instanceIndex, 0u); /* PRQA S 2985 */ /* MD_vMem_XXspi01_2985 */ /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
   instSeqBuffer->FlsCmdItems[0].SendDataBufferPtr = &(vMem_30_XXspi01_LL_Cfg_GetFlsDeviceReadStatusRegisterCommand(instanceIndex)); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
   instSeqBuffer->FlsCmdItems[0].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
   instSeqBuffer->FlsCmdItems[0].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

   /* #20 Setup register content buffer channel. */
   instSeqBuffer->FlsCmdItems[1].SpiChannel = vMem_30_XXspi01_LL_Cfg_GetSpiReadStatusRegisterChls(instanceIndex, 1u); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
   instSeqBuffer->FlsCmdItems[1].SendDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
   instSeqBuffer->FlsCmdItems[1].ReceiveDataBufferPtr = bufferPtr; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
   instSeqBuffer->FlsCmdItems[1].DataBufferLength = length; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

   return instSeqBuffer;
}

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetExtendedProgressCheckRegisterSequence()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetExtendedProgressCheckRegisterSequence(
    vMem_30_XXspi01_InstanceIdType instanceIndex,
    vMem_30_XXspi01_SpiDataPtrType bufferPtr,
    vMem_30_XXspi01_SpiLengthType length)
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  vMem_30_XXspi01_FlsCmdSequencePtrType instSeqBuffer = &(FlashSequenceBuffer[instanceIndex]);

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  instSeqBuffer->SpiSequence = vMem_30_XXspi01_LL_Cfg_GetSpiReadExtendedProgressCheckRegSeq(instanceIndex); /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */
  instSeqBuffer->FlsCmdItemCount = 2; /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */

  /* #10 Setup read extended progress check register command channel. */
  instSeqBuffer->FlsCmdItems[0].SpiChannel = vMem_30_XXspi01_LL_Cfg_GetSpiExtendedProgressCheckChls(instanceIndex, 0u); /* PRQA S 2985 */ /* MD_vMem_XXspi01_2985 */ /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].SendDataBufferPtr = &(vMem_30_XXspi01_LL_Cfg_GetFlsDeviceReadExtendedProgressCheckRegisterCommand(instanceIndex)); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

  /* #20 Setup register content buffer channel. */
  instSeqBuffer->FlsCmdItems[1].SpiChannel = vMem_30_XXspi01_LL_Cfg_GetSpiExtendedProgressCheckChls(instanceIndex, 1u); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[1].SendDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[1].ReceiveDataBufferPtr = bufferPtr; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[1].DataBufferLength = length; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

  return instSeqBuffer;
}

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetResultRegisterSequence()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetResultRegisterSequence(
    vMem_30_XXspi01_InstanceIdType instanceIndex,
    vMem_30_XXspi01_SpiDataPtrType bufferPtr,
    vMem_30_XXspi01_SpiLengthType length)
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  vMem_30_XXspi01_FlsCmdSequencePtrType instSeqBuffer = &(FlashSequenceBuffer[instanceIndex]);

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  instSeqBuffer->SpiSequence = vMem_30_XXspi01_LL_Cfg_GetSpiReadResultRegSeq(instanceIndex); /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */
  instSeqBuffer->FlsCmdItemCount = 2; /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */

  /* #10 Setup read result register command channel. */
  instSeqBuffer->FlsCmdItems[0].SpiChannel = vMem_30_XXspi01_LL_Cfg_GetSpiReadResultRegisterChls(instanceIndex, 0u); /* PRQA S 2985 */ /* MD_vMem_XXspi01_2985 */ /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].SendDataBufferPtr = &(vMem_30_XXspi01_LL_Cfg_GetFlsDeviceReadResultRegisterCommand(instanceIndex)); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

  /* #20 Setup register content buffer channel. */
  instSeqBuffer->FlsCmdItems[1].SpiChannel = vMem_30_XXspi01_LL_Cfg_GetSpiReadResultRegisterChls(instanceIndex, 1u); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[1].SendDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[1].ReceiveDataBufferPtr = bufferPtr; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[1].DataBufferLength = length; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

  return instSeqBuffer;
}

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetClearResultRegisterSequence()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vMem_30_XXspi01_FlsCmdSequencePtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetClearResultRegisterSequence(
    vMem_30_XXspi01_InstanceIdType instanceIndex)
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  vMem_30_XXspi01_FlsCmdSequencePtrType instSeqBuffer = &(FlashSequenceBuffer[instanceIndex]);

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  instSeqBuffer->SpiSequence = vMem_30_XXspi01_LL_Cfg_GetSpiClearResultRegSeq(instanceIndex); /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */
  instSeqBuffer->FlsCmdItemCount = 1; /* SBSW_vMem_30_XXspi01_SequenceBufferPointer */

  /* #10 Setup clear result register command channel. */
  instSeqBuffer->FlsCmdItems[0].SpiChannel = vMem_30_XXspi01_LL_Cfg_GetSpiClearResultRegisterChls(instanceIndex, 0u); /* PRQA S 2985 */ /* MD_vMem_XXspi01_2985 */ /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].SendDataBufferPtr = &(vMem_30_XXspi01_LL_Cfg_GetFlsDeviceClearResultRegisterCommand(instanceIndex)); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].ReceiveDataBufferPtr = NULL_PTR; /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */
  instSeqBuffer->FlsCmdItems[0].DataBufferLength = sizeof(vMem_30_XXspi01_SpiDataType); /* SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess */

  return instSeqBuffer;
}

#define VMEM_30_XXSPI01_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Justification for module-specific MISRA deviations:
 MD_vMem_XXspi01_3218: rule 8.9
      Reason:     File scope static, 'AddressBuffer', is only accessed in one function.
      Risk:       No risk.
      Prevention: No prevention.

  MD_vMem_XXspi01_2985: rule 2.2
      Reason:     The getter macro for the SPI channel reference requires a channel index.
                  The first channel index for a sequence inevitable is zero, what causes the rule deviation.
      Risk:       No risk.
      Prevention: No prevention.
*/

/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_vMem_30_XXspi01_AddressBufferAssignment
  \DESCRIPTION A pointer to the address buffer for a specific instance is assigned to the dereferenced given address buffer
               pointer pointer.
  \COUNTERMEASURE \N No countermeasure is necessary because the caller of the function is responsible for providing a correct
                     pointer pointer where the pointer to the address buffer could be stored.

\ID SBSW_vMem_30_XXspi01_AddressBufferWriteAccess
  \DESCRIPTION A write access on the address buffer through the buffer pointer is performed.
  \COUNTERMEASURE \N No countermeasure is necessary because the buffer pointer is valid as long as the caller of the function
                     provides a valid instance index. For each configured flash device an address buffer is preallocated.

\ID SBSW_vMem_30_XXspi01_AddressBufferLengthWriteAccess
  \DESCRIPTION A write access on the address buffer length pointer parameter is performed.
  \COUNTERMEASURE \N No countermeasure is necessary because the caller of the function is responsible for providing a valid
                     pointer to store the address buffer length.

\ID SBSW_vMem_30_XXspi01_SequenceBufferPointer
  \DESCRIPTION A write access on the sequence buffer for a specific instance is performed.
  \COUNTERMEASURE \N No countermeasure is necessary because the pointer on the instances sequence buffer is retrieved
                     by using the given instance index. No out of bounds access occurs as long as a valid instance index is provided
                     by the caller. The validity of the instance index is ensured by the DET checks in the components public interface.
                     For every configured device a sequence buffer is preallocated using the generated vMem_30_XXspi01_GetSizeOfvMemInstance()
                     macro, that delivers the amount of configured devices.

\ID SBSW_vMem_30_XXspi01_FlsCmdItemArrayWriteAccess
  \DESCRIPTION A write access on the flash command item array is performed.
  \COUNTERMEASURE \N No countermeasure is necessary because the array is statically preallocated and only accessed with a static
                     index. It has to be checked that the set value for the flash command item count reflects the amount of initialized
                     flash command items. The total amount of preallocated flash command items is defined by the
                     vMem_30_XXspi01_LL_MaximumChannels. It is obvious that the longest sequence of flash command items required
                     for a sequence is lower or equal to this value. The validity of the instSeqBuffer pointer is justified by the
                     SBSW_vMem_30_XXspi01_SequenceBufferPointer justification.

\ID SBSW_vMem_30_XXspi01_GetAddressBuffer
  \DESCRIPTION Function call to retrieve the pointer to the filled address buffer and the length of the buffer for the given instance.
  \COUNTERMEASURE \N No countermeasure is necessary because the passed pointers for the address buffer pointer and the address buffer
                     length are defined locally in the function and are therefore valid.

SBSW_JUSTIFICATION_END */

/* START_COVERAGE_JUSTIFICATION

Variant coverage:

\ID COV_VMEM_30_XXSPI01_COMPATIBILITY
 \ACCEPT TX
 \REASON COV_MSR_COMPATIBILITY

END_COVERAGE_JUSTIFICATION
*/

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXspi01_LL_FlsCmdSeqBuilder.c
 *********************************************************************************************************************/
