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
/*!        \file  vMem_30_XXspi01_LL_FlsCmdSeqExecuter.h
 *        \brief  Flash command sequence executer header file
 *
 *      \details  The vMem_30_XXspi01_LL_FlsCmdSeqExecuter executes a given flash command sequence by setting up the
 *                bus interface and triggering the transmission.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (VMEM_30_XXSPI01_LL_FLSCMDSEQEXECUTER_H)
# define VMEM_30_XXSPI01_LL_FLSCMDSEQEXECUTER_H

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
 *  vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute()
 *********************************************************************************************************************/
/*! \brief       Executes a given flash command sequence.
 *  \details     The function sets up all required transmission channels and triggers the execution in the underlying
 *               bus driver afterwards.
 *  \param[in]   flsCmdSeq    Pointer to the flash command sequence that shall be executed.
 *  \return      E_OK       - The flash command sequence was successfully triggered.
 *  \return      E_NOT_OK   - The underlying bus driver didn't accept the transmission request.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(
    vMem_30_XXspi01_FlsCmdSequencePtrType flsCmdSeq);

# define VMEM_30_XXSPI01_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* VMEM_30_XXSPI01_LL_FLSCMDSEQEXECUTER_H */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXspi01_LL_FlsCmdSeqExecuter.h
 *********************************************************************************************************************/
