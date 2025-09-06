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
/*!        \file  vMem_30_XXspi01_LL_FlsCmdSeqExecuter.c
 *        \brief  Flash command sequence executer source file
 *
 *      \details  See vMem_30_XXspi01_LL_FlsCmdSeqExecuter.h
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
#include "vMem_30_XXspi01_LL_FlsCmdSeqExecuter.h"
#include "vMem_30_XXspi01_Cfg.h"

#if (VMEM_30_XXSPI01_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (VMEM_XXSPI01_LOCAL) /* COV_VMEM_30_XXSPI01_COMPATIBILITY */
# define VMEM_XXSPI01_LOCAL static
#endif

#if !defined (VMEM_XXSPI01_LOCAL_INLINE) /* COV_VMEM_30_XXSPI01_COMPATIBILITY */
# define VMEM_XXSPI01_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define VMEM_30_XXSPI01_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VMEM_30_XXSPI01_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define VMEM_30_XXSPI01_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqExecuter_IsSequenceAvailable()
 *********************************************************************************************************************/
/*! \brief       Checks if the given sequence is ready for transmission.
 *  \details     The function checks in the underlying bus driver if the given sequence is ready for a transmission.
 *  \param[in]   sequence   Identifier for the sequence that shall be checked for availability.
 *  \return      TRUE       The sequence is available for transmission.
 *  \return      FALSE   The sequence is busy.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
VMEM_XXSPI01_LOCAL FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqExecuter_IsSequenceAvailable(
    vMem_30_XXspi01_SpiSequenceType sequence);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqExecuter_SetupChannels()
 *********************************************************************************************************************/
/*! \brief       Sets up channels for transmission.
 *  \details     The function sets up the transmission channels at the underlying bus driver based on the given
 *               flash command items.
 *  \param[in]   flsCmdSeq  Pointer to the flash command sequence that contains the flash command items.
 *  \return      E_OK       The channels were initialized successfully.
 *  \return      E_NOT_OK   An error occurred during the setup of the channels.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
VMEM_XXSPI01_LOCAL FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqExecuter_SetupChannels(
    vMem_30_XXspi01_FlsCmdSequencePtrType flsCmdSeq);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqExecuter_IsSequenceAvailable()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VMEM_XXSPI01_LOCAL FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqExecuter_IsSequenceAvailable(
    vMem_30_XXspi01_SpiSequenceType sequence)
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  vMem_30_XXspi01_SpiSeqResultType seqResult;

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  /* #10 Get the sequence result from the underlying bus driver */
  seqResult = vMem_30_XXspi01_LL_SpiGetSequenceResult(sequence);

  /* #20 Remap and return the result. */
  return (seqResult != VMEM_30_XXSPI01_SPI_SEQ_PENDING) ? TRUE : FALSE;
}

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqExecuter_SetupChannels()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VMEM_XXSPI01_LOCAL FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqExecuter_SetupChannels(
    vMem_30_XXspi01_FlsCmdSequencePtrType flsCmdSeq)
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 cmdIndex;

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  /* #10 Setup bus driver channels. */
  for(cmdIndex = 0; cmdIndex < flsCmdSeq->FlsCmdItemCount; cmdIndex++)
  {
    /* #11 Setup channel based on command item. */
    retVal = vMem_30_XXspi01_LL_SpiSetupEB(flsCmdSeq->FlsCmdItems[cmdIndex].SpiChannel,
        flsCmdSeq->FlsCmdItems[cmdIndex].SendDataBufferPtr,
        flsCmdSeq->FlsCmdItems[cmdIndex].ReceiveDataBufferPtr,
        flsCmdSeq->FlsCmdItems[cmdIndex].DataBufferLength); /* SBSW_vMem_30_XXspi01_SetupEB */

    /* #31 Abort the channel setup if the underlying bus driver didn't accept one of the requests. */
    if(retVal == E_NOT_OK)
    {
      break;
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(
    vMem_30_XXspi01_FlsCmdSequencePtrType flsCmdSeq)
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  /* #10 Check if the given sequence is available for transmission */
  if(vMem_30_XXspi01_LL_FlsCmdSeqExecuter_IsSequenceAvailable(flsCmdSeq->SpiSequence) == TRUE)
  {
    /* #20 Setup the transmission channels for the given flash command items. */
    retVal = vMem_30_XXspi01_LL_FlsCmdSeqExecuter_SetupChannels(flsCmdSeq); /* SBSW_vMem_30_XXspi01_SetupChannels */

    /* #30 If no error occurred during the channel setup, start the transmission of the sequence. */
    if(retVal == E_OK)
    {
      retVal = vMem_30_XXspi01_LL_SpiAsyncTransmit(flsCmdSeq->SpiSequence);
    }
  }

  return retVal;
}

#define VMEM_30_XXSPI01_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_vMem_30_XXspi01_SetupChannels
  \DESCRIPTION A function call is made to setup the flash command items as channels at the underlying bus driver using
               a pointer to the flash command sequence that shall be executed.
  \COUNTERMEASURE \N No countermeasure is necessary because the caller of the current function is responsible for
                     providing a valid pointer to a flash command sequence that shall be executed.

\ID SBSW_vMem_30_XXspi01_SetupEB
  \DESCRIPTION A function call is made to the underlying bus driver to set up the transmission channel for the current
               flash command item that is accessed by an indexed array access using the current value of the loop variable.
  \COUNTERMEASURE \N No countermeasure is necessary because the amount of loop iterations is restricted by the flash command
                     item count variable of the sequence itself. The flash command sequences are only created by the FlsCmdSeqBuilder
                     submodule that ensures the validity of sequence pointer itself, as well as the amount and the content of the
                     flash command items. The validity of the SendDataBufferPtr and ReceiveDataBufferPtr, that are contained in
                     each flash command item, is also ensured by the FlsCmdSeqBuilder. In case they point to given user buffers
                     the validity has to be ensured by the caller of the component.

SBSW_JUSTIFICATION_END */

/* START_COVERAGE_JUSTIFICATION

Variant coverage:

\ID COV_VMEM_30_XXSPI01_COMPATIBILITY
 \ACCEPT TX
 \REASON COV_MSR_COMPATIBILITY

END_COVERAGE_JUSTIFICATION
*/

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXspi01_LL_FlsCmdSeqExecuter.h
 *********************************************************************************************************************/
