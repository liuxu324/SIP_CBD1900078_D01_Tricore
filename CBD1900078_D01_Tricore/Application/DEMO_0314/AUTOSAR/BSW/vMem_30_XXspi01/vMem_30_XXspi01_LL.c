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
/*!        \file  vMem_30_XXspi01_LL.c
 *        \brief  vMem_30_XXspi01 LowLevel source file
 *
 *      \details  See vMem_30_XXspi01_LL.h
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
#include "vMem_30_XXspi01_LL_FlsCmdSeqExecuter.h"
#include "vMem_30_XXspi01_LL.h"
#include "vMem_30_XXspi01_Cfg.h"

#if (VMEM_30_XXSPI01_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  HARDWARE SOFTWARE INTERFACE (HSI)
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
 *
 *
 *
 *
 *
 *
*/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
#if !defined (VMEM_30_XXSPI01_LOCAL) /* COV_VMEM_30_XXSPI01_COMPATIBILITY */
# define VMEM_30_XXSPI01_LOCAL static
#endif

#if !defined (VMEM_30_XXSPI01_LOCAL_INLINE) /* COV_VMEM_30_XXSPI01_COMPATIBILITY */
# define VMEM_30_XXSPI01_LOCAL_INLINE LOCAL_INLINE
#endif

/*! Internal state machine type to indicate the instance-specific job progress. */
typedef enum
{
  VMEM_30_XXSPI01_IDLE = 0,
  VMEM_30_XXSPI01_EXECUTE_READ,
  VMEM_30_XXSPI01_EXECUTE_WRITE,
  VMEM_30_XXSPI01_CHECK_WRITE_PROGRESS,
  VMEM_30_XXSPI01_EXTENDED_WRITE_PROGRESS_CHECK,
  VMEM_30_XXSPI01_CHECK_WRITE_RESULT,
  VMEM_30_XXSPI01_EXECUTE_ERASE,
  VMEM_30_XXSPI01_CHECK_ERASE_PROGRESS,
  VMEM_30_XXSPI01_EXTENDED_ERASE_PROGRESS_CHECK,
  VMEM_30_XXSPI01_CHECK_ERASE_RESULT,
  VMEM_30_XXSPI01_CLEAR_RESULT_REGISTER
} vMem_30_XXspi01_JobProgressType;

/*! Instance job type to group an instance's job result and job progress. */
typedef struct
{
  vMem_30_XXspi01_JobResultType JobResult;
  vMem_30_XXspi01_JobProgressType JobProgress;
  boolean ProcessFlag;
} vMem_30_XXspi01_InstanceJobType;

typedef P2VAR(vMem_30_XXspi01_InstanceJobType, AUTOMATIC, VMEM_30_XXSPI01_VAR) vMem_30_XXspi01_InstanceJobPtrType;

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define VMEM_30_XXSPI01_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Defines a buffer for each configured flash device to store the content of read device registers. */
VMEM_30_XXSPI01_LOCAL VAR(vMem_30_XXspi01_SpiDataType, VMEM_30_XXSPI01_VAR)
  vMem_30_XXspi01_RegisterDataBuffers[vMem_30_XXspi01_GetSizeOfvMemInstance()][vMem_30_XXspi01_LL_MaximumStatusRegisterSize];

#define VMEM_30_XXSPI01_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VMEM_30_XXSPI01_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Contains instance specific status parameters like the JobResult, the JobProgress and the ProcessFlag. */
VMEM_30_XXSPI01_LOCAL VAR(vMem_30_XXspi01_InstanceJobType, VMEM_30_XXSPI01_VAR)
  vMem_30_XXspi01_InstanceStateMachine[vMem_30_XXspi01_GetSizeOfvMemInstance()];

#define VMEM_30_XXSPI01_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL INLINE FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define VMEM_30_XXSPI01_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLGetInstanceIndex()
 *********************************************************************************************************************/
/*! \brief        Returns the index of the requested instance ID.
 *  \details      -
 *  \param[in]    instanceId          ID of the related vMem_30_XXspi01 instance.
 *  \return       instance index
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(vMem_30_XXspi01_InstanceIdType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLGetInstanceIndex(
    vMem_30_XXspi01_InstanceIdType instanceId);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLIsDeviceReady()
 *********************************************************************************************************************/
/*! \brief        Checks if the memory device is ready to accept further requests.
 *  \details      -
 *  \param[in]    instanceIndex       Index of the related vMem_30_XXspi01 instance.
 *  \return       TRUE              - The device is ready.
 *  \return       FALSE             - The device is busy.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLIsDeviceReady(
    vMem_30_XXspi01_InstanceIdType instanceIndex);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLIsExtendedProgressCheckSucceeded()
 *********************************************************************************************************************/
/*! \brief        Checks if the extended progress check indicates that the external device is ready
 *                to accept further requests.
 *  \details      This extended progress check is an optionally configurable feature. There are devices
 *                with two BUSY flags. The extended progress check checks the additional BUSY flag.
 *  \param[in]    instanceIndex       Index of the related vMem_30_XXspi01 instance.
 *  \return       TRUE              - The device is ready.
 *  \return       FALSE             - The device is busy.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLIsExtendedProgressCheckSucceeded(
    vMem_30_XXspi01_InstanceIdType instanceIndex);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLIsEraseSucceeded()
 *********************************************************************************************************************/
/*! \brief        Checks if the previously executed erase operation was successful.
 *  \details      -
 *  \param[in]    instanceIndex       Index of the related vMem_30_XXspi01 instance.
 *  \return       TRUE              - The erase operation was successful.
 *  \return       FALSE             - The erase operation failed.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLIsEraseSucceeded(
    vMem_30_XXspi01_InstanceIdType instanceIndex);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLIsProgramSucceeded()
 *********************************************************************************************************************/
/*! \brief        Checks if the previously executed program operation was successful.
 *  \details      -
 *  \param[in]    instanceIndex       Index of the related vMem_30_XXspi01 instance.
 *  \return       TRUE              - The program operation was successful.
 *  \return       FALSE             - The program operation failed.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLIsProgramSucceeded(
    vMem_30_XXspi01_InstanceIdType instanceIndex);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLReadStatusRegister()
 *********************************************************************************************************************/
/*! \brief        Initiates the "read status register"-sequence and triggers its execution.
 *  \details      -
 *  \param[in]    instanceIndex       Index of the related vMem_30_XXspi01 instance.
 *  \return       E_OK              - The sequence has been successfully triggered.
 *  \return       E_NOT_OK          - The sequence execution failed.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLReadStatusRegister(
    vMem_30_XXspi01_InstanceIdType instanceIndex);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLReadResultRegister()
 *********************************************************************************************************************/
/*! \brief        Initiates the "read result register"-sequence and triggers its execution.
 *  \details      -
 *  \param[in]    instanceIndex       Index of the related vMem_30_XXspi01 instance.
 *  \return       E_OK              - The sequence has been successfully triggered.
 *  \return       E_NOT_OK          - The sequence execution failed.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLReadResultRegister(
    vMem_30_XXspi01_InstanceIdType instanceIndex);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLReadExtendedProgressCheckRegister()
 *********************************************************************************************************************/
/*! \brief        Initiates the "read extended progress check register"-sequence and triggers its execution.
 *  \details      -
 *  \param[in]    instanceIndex       Index of the related vMem_30_XXspi01 instance.
 *  \return       E_OK              - The sequence has been successfully triggered.
 *  \return       E_NOT_OK          - The sequence execution failed.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLReadExtendedProgressCheckRegister(
    vMem_30_XXspi01_InstanceIdType instanceIndex);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLClearResultRegister()
 *********************************************************************************************************************/
/*! \brief        Initiates the "clear result register"-sequence and triggers its execution.
 *  \details      -
 *  \param[in]    instanceIndex       Index of the related vMem_30_XXspi01 instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLClearResultRegister(
    vMem_30_XXspi01_InstanceIdType instanceIndex);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLExecuteState()
 *********************************************************************************************************************/
/*! \brief        Performs the "Execute" state machine action for the passed instance.
 *  \details      -
 *  \param[in]    instanceIndex       Index of the related vMem_30_XXspi01 instance.
 *  \param[in]    nextState           The instance's potentially next state.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLExecuteState(
    vMem_30_XXspi01_InstanceIdType instanceIndex,  vMem_30_XXspi01_JobProgressType nextState);

/*********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLCheckProgressState()
 *********************************************************************************************************************/
/*! \brief        Performs the "Check Progress" state machine action for the passed instance.
 *  \details      -
 *  \param[in]    instanceIndex       Index of the related vMem_30_XXspi01 instance.
 *  \param[in]    extendedCheckState  The instance's potentially next extended check state.
 *  \param[in]    resultCheckState    The instance's potentially next result check state.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLCheckProgressState(
    vMem_30_XXspi01_InstanceIdType instanceIndex,
    vMem_30_XXspi01_JobProgressType extendedProgressCheckState,
    vMem_30_XXspi01_JobProgressType resultCheckState);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLExtendedProgressCheckState()
 *********************************************************************************************************************/
/*! \brief        Performs the "Extended Progress Check" state machine action for the passed instance.
 *  \details      -
 *  \param[in]    instanceIndex       Index of the related vMem_30_XXspi01 instance.
 *  \param[in]    nextState           The instance's potentially next state.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLExtendedProgressCheckState(
    vMem_30_XXspi01_InstanceIdType instanceIndex, vMem_30_XXspi01_JobProgressType nextState);

/*********************************************************************************************************************
 *  LOCAL INLINE FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLGetInstanceIndex()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(vMem_30_XXspi01_InstanceIdType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLGetInstanceIndex(
    vMem_30_XXspi01_InstanceIdType instanceId)
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  /* #10 The default return value is the number of configured instances. */
  vMem_30_XXspi01_InstanceIdType retVal = vMem_30_XXspi01_GetSizeOfvMemInstance();
  vMem_30_XXspi01_InstanceIdType i;

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  /* #20 Iterate over all configured instances. */
  for(i = 0; i < vMem_30_XXspi01_GetSizeOfvMemInstance(); i++)
  {
    /* #30 If the requested instance ID is found, it will be returned. */
    if(vMem_30_XXspi01_GetIdOfvMemInstance(i) == instanceId)
    {
      retVal = i;
      break;
    }
  }

  return retVal;
} /* vMem_30_XXspi01_LLGetInstanceIndex */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLIsDeviceReady()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLIsDeviceReady(vMem_30_XXspi01_InstanceIdType instanceIndex)
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  boolean retVal = FALSE;

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  if((vMem_30_XXspi01_RegisterDataBuffers[instanceIndex][0] & vMem30_XXspi01_LL_Cfg_GetStatusRegBusyFlagBitMask(instanceIndex))
      == 0x00u)
  {
    retVal = TRUE;
  }

  return retVal;
} /* vMem_30_XXspi01_LLIsDeviceReady */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLIsExtendedProgressCheckSucceeded()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLIsExtendedProgressCheckSucceeded(
    vMem_30_XXspi01_InstanceIdType instanceIndex)
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  boolean retVal = FALSE;

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  if((vMem_30_XXspi01_RegisterDataBuffers[instanceIndex][0] & vMem30_XXspi01_LL_Cfg_GetExtendedProgressCheckRegBusyFlagBitMask(instanceIndex))
      == vMem30_XXspi01_LL_Cfg_GetExtendedProgressCheckRegBusyFlagBitMask(instanceIndex))
  {
    retVal = TRUE;
  }

  return retVal;
} /* vMem_30_XXspi01_LLIsExtendedProgressCheckSucceeded */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLIsEraseSucceeded()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLIsEraseSucceeded(vMem_30_XXspi01_InstanceIdType instanceIndex)
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  boolean retVal = FALSE;

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  if((vMem_30_XXspi01_RegisterDataBuffers[instanceIndex][0] & vMem30_XXspi01_LL_Cfg_GetResultRegEraseErrorBitMask(instanceIndex))
      == 0x00u)
  {
    retVal = TRUE;
  }

  return retVal;
} /* vMem_30_XXspi01_LLIsEraseSucceeded */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLIsProgramSucceeded()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLIsProgramSucceeded(vMem_30_XXspi01_InstanceIdType instanceIndex)
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  boolean retVal = FALSE;

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  if((vMem_30_XXspi01_RegisterDataBuffers[instanceIndex][0] & vMem30_XXspi01_LL_Cfg_GetResultRegProgramErrorBitMask(instanceIndex))
      == 0x00u)
  {
    retVal = TRUE;
  }

  return retVal;
} /* vMem_30_XXspi01_LLIsProgramSucceeded */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLReadStatusRegister()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLReadStatusRegister(
    vMem_30_XXspi01_InstanceIdType instanceIndex)
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  vMem_30_XXspi01_FlsCmdSequencePtrType sequencePtr;

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  /* #10 Receive the status register sequence from the FlsCmdSeqBuilder. */
  sequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetStatusRegisterSequence(instanceIndex,
      vMem_30_XXspi01_RegisterDataBuffers[instanceIndex], vMem_30_XXspi01_LL_MaximumStatusRegisterSize); /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */

  /* #20 Call the FlsCmdSeqExecuter to execute the passed sequence and return the executer's return value. */
  return vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(sequencePtr); /* SBSW_vMem_30_XXspi01_ExecuteSequence */
} /* vMem_30_XXspi01_LLReadStatusRegister */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLReadResultRegister()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLReadResultRegister( /* PRQA S 3219 */ /* MD_vMem_30_XXspi01_FunctionNotUsed */
    vMem_30_XXspi01_InstanceIdType instanceIndex)
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  vMem_30_XXspi01_FlsCmdSequencePtrType sequencePtr;

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  /* #10 Receive the result register sequence from the FlsCmdSeqBuilder. */
  sequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetResultRegisterSequence(instanceIndex,
      vMem_30_XXspi01_RegisterDataBuffers[instanceIndex],
      vMem_30_XXspi01_LL_MaximumStatusRegisterSize); /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */

  /* #20 Call the FlsCmdSeqExecuter to execute the passed sequence and return the executer's return value. */
  return vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(sequencePtr); /* SBSW_vMem_30_XXspi01_ExecuteSequence */
} /* vMem_30_XXspi01_LLReadResultRegister */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLReadExtendedProgressCheckRegister()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLReadExtendedProgressCheckRegister(
    vMem_30_XXspi01_InstanceIdType instanceIndex)
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  vMem_30_XXspi01_FlsCmdSequencePtrType sequencePtr;

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  /* #10 Receive the extended progress check register sequence from the FlsCmdSeqBuilder. */
  sequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetExtendedProgressCheckRegisterSequence(instanceIndex,
      vMem_30_XXspi01_RegisterDataBuffers[instanceIndex],
      vMem_30_XXspi01_LL_MaximumStatusRegisterSize); /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */

  /* #20 Call the FlsCmdSeqExecuter to execute the passed sequence and return the executer's return value. */
  return vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(sequencePtr); /* SBSW_vMem_30_XXspi01_ExecuteSequence */
} /* vMem_30_XXspi01_LLReadExtendedProgressCheckRegister */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLClearResultRegister()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLClearResultRegister(
    vMem_30_XXspi01_InstanceIdType instanceIndex)
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  vMem_30_XXspi01_FlsCmdSequencePtrType sequencePtr;
  vMem_30_XXspi01_InstanceJobPtrType processedInstance;

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  /* #10 Call the FlsCmdSeqBuilder to receive the "clear result register" - sequence. */
  sequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetClearResultRegisterSequence(instanceIndex);
  processedInstance = &vMem_30_XXspi01_InstanceStateMachine[instanceIndex];

  /* #20 If the attempt to execute the passed sequence succeeds, set the job progress to CLEAR_RESULT_REGISTER. */
  if(vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(sequencePtr) == E_OK) /* SBSW_vMem_30_XXspi01_ExecuteSequence */
  {
    processedInstance->JobProgress = VMEM_30_XXSPI01_CLEAR_RESULT_REGISTER; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
  }
  /* #30 Otherwise the job failed. */
  else
  {
    processedInstance->JobResult = VMEM_JOB_FAILED; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedInstance->JobProgress = VMEM_30_XXSPI01_IDLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
  }
} /* vMem_30_XXspi01_LLClearResultRegister */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLExecuteState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL_INLINE FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLExecuteState(
    vMem_30_XXspi01_InstanceIdType instanceIndex,  vMem_30_XXspi01_JobProgressType nextState)
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  vMem_30_XXspi01_InstanceJobPtrType processedInstance = &vMem_30_XXspi01_InstanceStateMachine[instanceIndex];

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  /*
   * #10 If triggering the "read status register"-sequence succeeded, set the passed nextState value as the
   * instance's job progress value.
   */
  if(vMem_30_XXspi01_LLReadStatusRegister(instanceIndex) == E_OK)
  {
    processedInstance->JobProgress = nextState; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
  }
  /* #20 Otherwise the job failed. */
  else
  {
    processedInstance->JobResult = VMEM_JOB_FAILED; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedInstance->JobProgress = VMEM_30_XXSPI01_IDLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
  }
} /* vMem_30_XXspi01_LLExecuteState */

/*********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLCheckProgressState()
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
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLCheckProgressState(
    vMem_30_XXspi01_InstanceIdType instanceIndex,
    vMem_30_XXspi01_JobProgressType extendedProgressCheckState,
    vMem_30_XXspi01_JobProgressType resultCheckState) /* PRQA S 3206 */ /* MD_vMem_30_XXspi01_ParameterNotUsed */
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  vMem_30_XXspi01_InstanceJobPtrType processedInstance = &vMem_30_XXspi01_InstanceStateMachine[instanceIndex];
  boolean jobFailed = TRUE;

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  /* #10 If the external device is ready. */
  if(vMem_30_XXspi01_LLIsDeviceReady(instanceIndex) == TRUE)
  {
    /* #20 If the instance's "extended progress check" is enabled. */
    if(vMem_30_XXspi01_LL_Cfg_IsExtendedProgressCheckEnabled(instanceIndex))
    {
      /*
       * #30 If triggering the "read extended progress check register"-sequence successfully, set the instance's
       * job progress to the given extended progress check state.
       */
      if(vMem_30_XXspi01_LLReadExtendedProgressCheckRegister(instanceIndex) == E_OK)
      {
        processedInstance->JobProgress = extendedProgressCheckState; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
        jobFailed = FALSE;
      }
    }
#if (VMEM_30_XXSPI01_DEV_ERROR_DETECT == STD_ON)
    /* #40 If the instance's result check is enabled. */
    else if(vMem_30_XXspi01_LL_Cfg_IsResultCheckEnabled(instanceIndex))
    {
      /* #50 Trigger the "read result register"-sequence
       *     and set the job progress to the given result check state if the transmission was successful. */
      if(vMem_30_XXspi01_LLReadResultRegister(instanceIndex) == E_OK)
      {
        processedInstance->JobProgress = resultCheckState; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
        jobFailed = FALSE;
      }
    }
#endif /* VMEM_30_XXSPI01_DEV_ERROR_DETECT */
    /* #60 If neither the extended check nor the result check is enabled, the job is successfully finished. */
    else
    {
      processedInstance->JobResult = VMEM_JOB_OK; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
      processedInstance->JobProgress = VMEM_30_XXSPI01_IDLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
      jobFailed = FALSE;
    }
  }
  /* #70 If the device is not ready yet the status register must be read again. */
  else
  {
    /* #80 If triggering the "read status register"-sequence was successful, the job doesn't fail succeeds. */
    if(vMem_30_XXspi01_LLReadStatusRegister(instanceIndex) == E_OK)
    {
      jobFailed = FALSE;
    }
  }

  /* #90 If the job failed, set an appropriate instance's job progress state. */
  if(jobFailed == TRUE)
  {
    processedInstance->JobResult = VMEM_JOB_FAILED; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    processedInstance->JobProgress = VMEM_30_XXSPI01_IDLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
  }
} /* vMem_30_XXspi01_LLCheckProgressState */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLExtendedProgressCheckState()
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
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLExtendedProgressCheckState(
    vMem_30_XXspi01_InstanceIdType instanceIndex, vMem_30_XXspi01_JobProgressType nextState) /* PRQA S 3206 */ /* MD_vMem_30_XXspi01_ParameterNotUsed */
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  vMem_30_XXspi01_InstanceJobPtrType processedInstance = &vMem_30_XXspi01_InstanceStateMachine[instanceIndex];

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  /* #10 If the value of the external device's status register indicates that the device is ready. */
  if(vMem_30_XXspi01_LLIsExtendedProgressCheckSucceeded(instanceIndex) == TRUE)
  {
#if (VMEM_30_XXSPI01_DEV_ERROR_DETECT == STD_ON)
    /* #20 If the instance's result check is enabled. */
    if(vMem_30_XXspi01_LL_Cfg_IsResultCheckEnabled(instanceIndex))
    {
      /*
       * #30 If triggering the "read result register"-sequence successfully, set the instance's job progress
       * to the given result check state.
       */
      if(vMem_30_XXspi01_LLReadResultRegister(instanceIndex) == E_OK)
      {
        processedInstance->JobProgress = nextState; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
      }
      /* #40 Otherwise the job fails. */
      else
      {
        processedInstance->JobResult = VMEM_JOB_FAILED; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
        processedInstance->JobProgress = VMEM_30_XXSPI01_IDLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
      }
    }
    /* #50 Otherwise the job is successfully finished. */
    else
#endif /* VMEM_30_XXSPI01_DEV_ERROR_DETECT */
    {
      processedInstance->JobResult = VMEM_JOB_OK; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
      processedInstance->JobProgress = VMEM_30_XXSPI01_IDLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    }
  }
  /* #60 If the device is not ready, the status register must be read again. */
  else
  {
    /* #70 If triggering the "read extended progress check register"-sequence failed, the whole job failed. */
    if(vMem_30_XXspi01_LLReadExtendedProgressCheckRegister(instanceIndex) == E_NOT_OK)
    {
      processedInstance->JobResult = VMEM_JOB_FAILED; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
      processedInstance->JobProgress = VMEM_30_XXSPI01_IDLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    }
  }
} /* vMem_30_XXspi01_LLExtendedProgressCheckState */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLSeqEndNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLSeqEndNotification(vMem_30_XXspi01_InstanceIdType instanceIndex)
{
  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  vMem_30_XXspi01_InstanceStateMachine[instanceIndex].ProcessFlag = TRUE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayParameter */
} /* vMem_30_XXspi01_LLSeqEndNotification */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLRead()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLRead(vMem_30_XXspi01_InstanceIdType InstanceId,
    vMem_30_XXspi01_AddressType SourceAddress, vMem_30_XXspi01_DataPtrType TargetAddressPtr,
    vMem_30_XXspi01_LengthType Length)
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  Std_ReturnType retVal;
  vMem_30_XXspi01_FlsCmdSequencePtrType readSequencePtr;
  vMem_30_XXspi01_InstanceIdType instanceIndex = vMem_30_XXspi01_LLGetInstanceIndex(InstanceId);

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  /* #10 Set the job parameters for the requested instance according to the requested operation. */
  vMem_30_XXspi01_InstanceStateMachine[instanceIndex].JobProgress = VMEM_30_XXSPI01_EXECUTE_READ; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayParameter */
  vMem_30_XXspi01_InstanceStateMachine[instanceIndex].JobResult = VMEM_JOB_PENDING; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayParameter */

  /* #20 Call the SeqBuilder service to retrieve the "read" - sequence. */
  readSequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadSequence(instanceIndex, SourceAddress,
      (vMem_30_XXspi01_SpiDataPtrType)TargetAddressPtr, (vMem_30_XXspi01_SpiLengthType)Length); /* PRQA S 0316 */ /* MD_vMem_30_XXspi01_VoidPtrTypedPtr */ /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */

  /* #30 Trigger the FlsCmdSeqExecuter to transmit the "read"-sequence and set the job result to E_OK if the transmission was successful. */
  if (vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(readSequencePtr) == E_OK) /* SBSW_vMem_30_XXspi01_ExecuteSequence */
  {
    retVal = E_OK;
  }
  /* #40 Otherwise the job failed. */
  else
  {
    vMem_30_XXspi01_InstanceStateMachine[instanceIndex].JobProgress = VMEM_30_XXSPI01_IDLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayParameter */
    vMem_30_XXspi01_InstanceStateMachine[instanceIndex].JobResult = VMEM_JOB_FAILED; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayParameter */

    retVal = E_NOT_OK;
  }

  return retVal;
} /* vMem_30_XXspi01_LLRead */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLWrite()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLWrite(vMem_30_XXspi01_InstanceIdType InstanceId,
    vMem_30_XXspi01_AddressType TargetAddress, vMem_30_XXspi01_ConstDataPtrType SourceAddressPtr,
    vMem_30_XXspi01_LengthType Length)
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  Std_ReturnType retVal;
  vMem_30_XXspi01_FlsCmdSequencePtrType writeSequencePtr;
  vMem_30_XXspi01_InstanceIdType instanceIndex = vMem_30_XXspi01_LLGetInstanceIndex(InstanceId);

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  /* #10 Set the job parameters for the requested instance according to the requested operation. */
  vMem_30_XXspi01_InstanceStateMachine[instanceIndex].JobProgress = VMEM_30_XXSPI01_EXECUTE_WRITE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayParameter */
  vMem_30_XXspi01_InstanceStateMachine[instanceIndex].JobResult = VMEM_JOB_PENDING; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayParameter */

  /* #20 Call the SeqBuilder service to retrieve the "write"-sequence. */
  writeSequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteSequence(instanceIndex, TargetAddress,
      (vMem_30_XXspi01_SpiDataPtrType)SourceAddressPtr, (vMem_30_XXspi01_SpiLengthType)Length); /* PRQA S 0316, 0311 */ /* MD_vMem_30_XXspi01_VoidPtrTypedPtr, MD_vMem_30_XXspi01_PtrCastLossOfConst */ /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */

  /* #30 Trigger the FlsCmdSeqExecuter to transmit the "write"-sequence and set the job result to E_OK if the transmission was successful. */
  if (vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(writeSequencePtr) == E_OK) /* SBSW_vMem_30_XXspi01_ExecuteSequence */
  {
    retVal = E_OK;
  }
  /* #40 Otherwise the job failed. */
  else
  {
    vMem_30_XXspi01_InstanceStateMachine[instanceIndex].JobProgress = VMEM_30_XXSPI01_IDLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayParameter */
    vMem_30_XXspi01_InstanceStateMachine[instanceIndex].JobResult = VMEM_JOB_FAILED; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayParameter */

    retVal = E_NOT_OK;
  }

  return retVal;
} /* vMem_30_XXspi01_LLWrite */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLErase()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLErase(vMem_30_XXspi01_InstanceIdType InstanceId,
    vMem_30_XXspi01_AddressType TargetAddress, vMem_30_XXspi01_LengthType Length)
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  Std_ReturnType retVal;
  vMem_30_XXspi01_FlsCmdSequencePtrType eraseSequencePtr;
  vMem_30_XXspi01_InstanceIdType instanceIndex = vMem_30_XXspi01_LLGetInstanceIndex(InstanceId);

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  /* #10 Set the job parameters for the requested instance according to the requested operation. */
  vMem_30_XXspi01_InstanceStateMachine[instanceIndex].JobProgress = VMEM_30_XXSPI01_EXECUTE_ERASE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayParameter */
  vMem_30_XXspi01_InstanceStateMachine[instanceIndex].JobResult = VMEM_JOB_PENDING; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayParameter */

  /* #20 Call the SeqBuilder service to retrieve the "erase"-sequence. */
  eraseSequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetEraseSequence(instanceIndex, TargetAddress);

  /* #30 Trigger the FlsCmdSeqExecuter to transmit the "erase"-sequence and set the job result to E_OK if the transmission was successful. */
  if (vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(eraseSequencePtr) == E_OK) /* SBSW_vMem_30_XXspi01_ExecuteSequence */
  {
    retVal = E_OK;
  }
  /* #50 Otherwise the job failed. */
  else
  {
    vMem_30_XXspi01_InstanceStateMachine[instanceIndex].JobProgress = VMEM_30_XXSPI01_IDLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayParameter */
    vMem_30_XXspi01_InstanceStateMachine[instanceIndex].JobResult = VMEM_JOB_FAILED; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayParameter */

    retVal = E_NOT_OK;
  }

  /* The passed Length parameter is currently not necessary due to only single physical sectors can be erased at once. */
  VMEM_30_XXSPI01_DUMMY_STATEMENT(Length);

  return retVal;
} /* vMem_30_XXspi01_LLErase */

/**********************************************************************************************************************
 * vMem_30_XXspi01_LLGetJobResult()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vMem_30_XXspi01_JobResultType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLGetJobResult(
    vMem_30_XXspi01_InstanceIdType InstanceId)
{
  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  return vMem_30_XXspi01_InstanceStateMachine[InstanceId].JobResult;
} /* vMem_30_XXspi01_LLGetJobResult */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLProcessing()
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
 *
 *
 *
 *
 *
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
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLProcessing(void)
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  vMem_30_XXspi01_InstanceIdType instanceIndex;
  vMem_30_XXspi01_InstanceJobPtrType processedInstance;

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  /* #10 Iterate over all configured instances. */
  for (instanceIndex = 0; instanceIndex < vMem_30_XXspi01_GetSizeOfvMemInstance(); instanceIndex++)
  {
    processedInstance = &vMem_30_XXspi01_InstanceStateMachine[instanceIndex];

    /* #20 If the instance's process flag is set. */
    if (processedInstance->ProcessFlag == TRUE)
    {
      /* #30 Reset the process flag. */
      processedInstance->ProcessFlag = FALSE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrLoop */

      /* #40 Check the job progress and perform the corresponding operation. */
      switch (processedInstance->JobProgress)
      {
  /* ------ VMEM_30_XXSPI01_EXECUTE_READ --------------------------------------------------------------------------- */
      case VMEM_30_XXSPI01_EXECUTE_READ:
        /* #50 Perform the "execute read" - state. */
        processedInstance->JobResult = VMEM_JOB_OK; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrLoop */
        processedInstance->JobProgress = VMEM_30_XXSPI01_IDLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrLoop */
        break;
  /* ------ VMEM_30_XXSPI01_EXECUTE_WRITE -------------------------------------------------------------------------- */
      case VMEM_30_XXSPI01_EXECUTE_WRITE:
        /* #60 Perform the "execute write" - state. */
        vMem_30_XXspi01_LLExecuteState(instanceIndex, VMEM_30_XXSPI01_CHECK_WRITE_PROGRESS);
        break;
  /* ------ VMEM_30_XXSPI01_CHECK_WRITE_PROGRESS ------------------------------------------------------------------- */
      case VMEM_30_XXSPI01_CHECK_WRITE_PROGRESS:
        /* #70 Perform the "check write progress" - state. */
          vMem_30_XXspi01_LLCheckProgressState(instanceIndex, VMEM_30_XXSPI01_EXTENDED_WRITE_PROGRESS_CHECK, VMEM_30_XXSPI01_CHECK_WRITE_RESULT);
        break;
  /* ------ VMEM_30_XXSPI01_EXTENDED_CHECK_WRITE_PROGRESS ---------------------------------------------------------- */
      case VMEM_30_XXSPI01_EXTENDED_WRITE_PROGRESS_CHECK:
        /* #80 Perform the "extended write progress check" - state. */
        vMem_30_XXspi01_LLExtendedProgressCheckState(instanceIndex, VMEM_30_XXSPI01_CHECK_WRITE_RESULT);
        break;
  /* ------ VMEM_30_XXSPI01_CHECK_WRITE_RESULT --------------------------------------------------------------------- */
      case VMEM_30_XXSPI01_CHECK_WRITE_RESULT:
        /* #90 Perform the "check write result" - state. */
        /*
         * #100 If the value of the external device's result register indicates that the write operation was successful,
         * the job is successfully finished.
         */
        if(vMem_30_XXspi01_LLIsProgramSucceeded(instanceIndex) == TRUE)
        {
          processedInstance->JobResult = VMEM_JOB_OK; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrLoop */
          processedInstance->JobProgress = VMEM_30_XXSPI01_IDLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrLoop */
        }
        /* #110 Otherwise the result register must be cleared. */
        else
        {
          vMem_30_XXspi01_LLClearResultRegister(instanceIndex);
        }
        break;
  /* ------ VMEM_30_XXSPI01_EXECUTE_ERASE -------------------------------------------------------------------------- */
      case VMEM_30_XXSPI01_EXECUTE_ERASE:
        /* #120 Perform the "execute erase" - state. */
        vMem_30_XXspi01_LLExecuteState(instanceIndex, VMEM_30_XXSPI01_CHECK_ERASE_PROGRESS);
        break;
  /* ------ VMEM_30_XXSPI01_CHECK_ERASE_PROGRESS ------------------------------------------------------------------- */
      case VMEM_30_XXSPI01_CHECK_ERASE_PROGRESS:
        /* #130 Perform the "check erase progress" - state. */
        vMem_30_XXspi01_LLCheckProgressState(instanceIndex, VMEM_30_XXSPI01_EXTENDED_ERASE_PROGRESS_CHECK, VMEM_30_XXSPI01_CHECK_ERASE_RESULT);
        break;
  /* ------ VMEM_30_XXSPI01_EXTENDED_CHECK_ERASE_PROGRESS ---------------------------------------------------------- */
      case VMEM_30_XXSPI01_EXTENDED_ERASE_PROGRESS_CHECK:
        /* #140 Perform the "extended erase progress check" - state. */
        vMem_30_XXspi01_LLExtendedProgressCheckState(instanceIndex, VMEM_30_XXSPI01_CHECK_ERASE_RESULT);
        break;
  /* ------ VMEM_30_XXSPI01_CHECK_ERASE_RESULT --------------------------------------------------------------------- */
      case VMEM_30_XXSPI01_CHECK_ERASE_RESULT:
        /* #150 Perform the "check erase result" - state. */
        /*
         * #160 If the value of the external device's result register indicates that the erase operation was successful,
         * the job is successfully finished.
         */
        if(vMem_30_XXspi01_LLIsEraseSucceeded(instanceIndex) == TRUE)
        {
          processedInstance->JobResult = VMEM_JOB_OK; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrLoop */
          processedInstance->JobProgress = VMEM_30_XXSPI01_IDLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrLoop */
        }
        /* #170 Otherwise the result register must be cleared. */
        else
        {
          vMem_30_XXspi01_LLClearResultRegister(instanceIndex);
        }
        break;
  /* ------ VMEM_30_XXSPI01_CLEAR_STATUS --------------------------------------------------------------------------- */
      case VMEM_30_XXSPI01_CLEAR_RESULT_REGISTER:
        /* #180 Perform the "clear result register" - state. */
        processedInstance->JobResult = VMEM_JOB_FAILED; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrLoop */
        processedInstance->JobProgress = VMEM_30_XXSPI01_IDLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrLoop */
        break;
  /* ------ VMEM_30_XXSPI01_IDLE ----------------------------------------------------------------------------------- */
      case VMEM_30_XXSPI01_IDLE:
      default:
        /* #190 "Idle" - state: Nothing to do. */
        break;
      }
    }
  }
} /* vMem_30_XXspi01_LLProcessing */ /* PRQA S 6030 */ /* MD_MSR_STCYC */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LLInit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LLInit(void)
{
  /* ------ Local variables ---------------------------------------------------------------------------------------- */
  vMem_30_XXspi01_InstanceIdType sequenceIdIterator;

  /* ------ Implementation ----------------------------------------------------------------------------------------- */
  for (sequenceIdIterator = 0; sequenceIdIterator < vMem_30_XXspi01_GetSizeOfvMemInstance(); sequenceIdIterator++)
  {
    vMem_30_XXspi01_InstanceStateMachine[sequenceIdIterator].JobProgress = VMEM_30_XXSPI01_IDLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayLoop */
    vMem_30_XXspi01_InstanceStateMachine[sequenceIdIterator].JobResult = VMEM_JOB_OK; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayLoop */
    vMem_30_XXspi01_InstanceStateMachine[sequenceIdIterator].ProcessFlag = FALSE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayLoop */
  }

  return E_OK;
} /* vMem_30_XXspi01_LLInit */

#define VMEM_30_XXSPI01_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Justification for module-specific MISRA deviations:
  MD_vMem_30_XXspi01_VoidPtrTypedPtr: rule 11.5
  Reason:     vMem accepts untyped void pointers in its hardware specific functionality, to provide a compatible
              interface for different hardware specific function implementations: one may get a structure of type A,
              the other of type B etc. With a void pointer interface the signature of all the functions keeps the same
              as can be used in one typed function pointer array.
              In the hardware specific functionality GetActiveAddressRegion the vMem performs a cast of the void pointer
              to a pointer to vMem_30_Tc3xxInf01_AddressRegionType, so it can write the currently active address region
              to the referenced object.
              The user of this functionality has to make sure, that the referenced object is of type
              vMem_30_Tc3xxInf01_AddressRegionType. During initialization the components calls its own service to get
              the active address region and for this performs a cast from a pointer to object type to a pointer to void.
              vMem also accepts void pointers for user buffers. During a write job vMem has to split the passed
              buffer into words. Therefore, the buffer is cast to a pointer of type uint32.
  Risk:       Possible mismatch of pointer type and given length parameter after cast of untyped void pointer.
  Prevention: Component tests ensures that the vMem accesses the referenced object correctly.

  MD_vMem_30_XXspi01_PtrCastLossOfConst: rule 11.5
  Reason:     Dangerous pointer cast results in loss of const qualification.
  Risk:       An element the pointer is pointing to can be manipulated without a const qualifier.
  Prevention: vMem ensures that the element the pointer is pointing to is never manipulated.

  MD_vMem_30_XXspi01_FunctionNotUsed: rule 2.1
  Reason:     The function is not used in this translation unit because a feature is disabled for this variant.
  Risk:       No risk. It's just a function that is not called in this configuration.
  Prevention: No prevention possible, because the function is required for other configurations.

  MD_vMem_30_XXspi01_ParameterNotUsed: rule 2.7
  Reason:     The parameter is not used in this function because a feature is disabled for this variant.
  Risk:       No risk. It's just an unused function parameter.
  Prevention: No prevention possible, because the parameter is required for other configurations.
*/

/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer
  \DESCRIPTION A function is called with a pointer to the buffer where the the content of a flash device register is
               stored. The instance index parameter is used to retrieve the pointer to the device specific buffer.
  \COUNTERMEASURE \N No countermeasure is necessary because the caller of the function is responsible for providing
                     a valid instance index value. The indexed register buffer array is preallocated with sufficient
                     memory for each configured flash device.

\ID SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers
  \DESCRIPTION A function is called with a pointer that was passed down to the current function.
  \COUNTERMEASURE \N No countermeasure is necessary because the caller of the current function is responsible for providing
                     a valid pointer that could be passed further down.

\ID SBSW_vMem_30_XXspi01_ExecuteSequence
  \DESCRIPTION The flash command sequence executor submodule is called with a pointer to the sequence that shall be
               executed.
  \COUNTERMEASURE \T The validity of the used pointer to the flash command sequence that is build by the flash command
                     sequence builder is verified by the test cases TCASE-963427, TCASE-963429, TCASE-963432,
                     TCASE-963433, TCASE-976015, TCASE-963434 and TCASE-963435.

\ID SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter
  \DESCRIPTION A write access is made using a pointer to the flash device job management structure.
  \COUNTERMEASURE \N No countermeasure is necessary because the pointer is retrieved by using the given instance index.
                     The referenced structure array is preallocated with one entry for each configured flash device.
                     The caller of the function is therefore responsible for providing a valid instance index value.
                     In case the given parameter is the instance id instead of the index, the id is mapped the index
                     and checked against the max value in advance.

\ID SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrLoop
  \DESCRIPTION A write access is made using a pointer to the flash device job management structure.
  \COUNTERMEASURE \N No countermeasure is necessary because the pointer is retrieved by using the loop variable as
                     index. The referenced structure array is preallocated with one entry for each configured flash
                     device. The loop iterates over every configured device and therefore only provides valid indices.

\ID SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayParameter
  \DESCRIPTION A write access is made to the flash device job management structure array using the instance index.
  \COUNTERMEASURE \N No countermeasure is necessary because the array is accessed using the index of the flash device
                     identified by the given instance id. Because the instance id is validated by the calling module,
                     every given instance id could successfully be mapped to a valid index. The referenced structure
                     array is preinitialized with one entry for each configured flash device.

\ID SBSW_vMem_30_XXspi01_WriteToInstanceStateMachineArrayLoop
  \DESCRIPTION A write access is made to the flash device job management structure array using the instance index.
  \COUNTERMEASURE \N No countermeasure is necessary because the array is accessed using a loop variable as index. The
                     referenced structure array is preallocated with one entry for each configured flash device. The
                     loop iterates over every configured device and therefore only provides valid indices.

SBSW_JUSTIFICATION_END */

/* START_COVERAGE_JUSTIFICATION

Variant coverage:

\ID COV_VMEM_30_XXSPI01_COMPATIBILITY
 \ACCEPT TX
 \REASON COV_MSR_COMPATIBILITY

END_COVERAGE_JUSTIFICATION
*/
/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXspi01_LL.c
 *********************************************************************************************************************/

