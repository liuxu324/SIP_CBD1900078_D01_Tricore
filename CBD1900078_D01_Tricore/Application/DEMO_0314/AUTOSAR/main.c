/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  SAMPLE CODE ONLY
 *  -------------------------------------------------------------------------------------------------------------------
 *              This implementation is sample code and only intended to illustrate an example of a possible BSW
 *              implementation. The implementation may not be complete and is not provided for use in production
 *              without any modifications. If this sample code is used in any way, the customer shall test
 *              this implementation as well as any of its modifications with diligent care.
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: CBD1800382_D00.c
 *       Description: Provides the implementation of the main function and unimplemented tasks
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Os.h"
#include "EcuM.h"
#include "Rte_Main.h"


# include "ComM_Cfg.h"
# include "ComM.h"
# include "ComM_EcuMBswM.h"
# include "Can.h"

/**********************************************************************************************************************
 *  ADDITIONAL USER INCLUDES
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK User Includes>
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  VERSION CHECK
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  main
 **********************************************************************************************************************/
int main(void)
{
	Os_InitMemory();
	Os_Init();
	EcuM_Init(); /* never returns */
	return 0;
}

/***********************************************************************************************************************
 *  InitTask_OsCore0
 **********************************************************************************************************************/
TASK(OsTask_Init_Core0)
{
	EcuM_StartupTwo();

	ComM_CommunicationAllowed(0, TRUE);

	ComM_RequestComMode(0, COMM_FULL_COMMUNICATION);
	ComM_RequestComMode(1, COMM_FULL_COMMUNICATION);
	(void)TerminateTask();
}

/***********************************************************************************************************************
 *  InitTask_OsCore1
 **********************************************************************************************************************/
TASK(OsTask_Init_Core1)
{
	EcuM_StartupTwo();
	Rte_Start();

	(void)TerminateTask();
}

/***********************************************************************************************************************
 *  InitTask_OsCore2
 **********************************************************************************************************************/
TASK(OsTask_Init_Core2)
{
	EcuM_StartupTwo();
	Rte_Start();

	(void)TerminateTask();
}

/***********************************************************************************************************************
 *  InitTask_OsCore3
 **********************************************************************************************************************/
TASK(OsTask_Init_Core3)
{
	EcuM_StartupTwo();
	Rte_Start();

	(void)TerminateTask();
}

/***********************************************************************************************************************
 *  InitTask_OsCore4
 **********************************************************************************************************************/
TASK(OsTask_Init_Core4)
{
	EcuM_StartupTwo();
	Rte_Start();

	(void)TerminateTask();
}

/***********************************************************************************************************************
 *  InitTask_OsCore5
 **********************************************************************************************************************/
TASK(OsTask_Init_Core5)
{
	EcuM_StartupTwo();
	Rte_Start();

	(void)TerminateTask();
}


/**********************************************************************************************************************
 *  END OF FILE: CBD1800382_D00.c
 *********************************************************************************************************************/
/***********************************************************************************************************************
 * UserDefined ExclusiveArea handling for CAN channels, according to AN-ISC-8-1149_ErrorHook_E_OS_DISABLED_INT.pdf
 **********************************************************************************************************************/
static uint8 BrsAsrApplCanInterruptLockCtr;
void SchM_Enter_Can_CAN_EXCLUSIVE_AREA_0(void)
{
  if (++BrsAsrApplCanInterruptLockCtr == 1u)
  {
    Can_DisableControllerInterrupts(0u);
  }
}

void SchM_Exit_Can_CAN_EXCLUSIVE_AREA_0(void)
{
  if (--BrsAsrApplCanInterruptLockCtr == 0u)
  {
    Can_EnableControllerInterrupts(0u);
  }
}

void SchM_Enter_Can_CAN_EXCLUSIVE_AREA_6(void)
{
  if (++BrsAsrApplCanInterruptLockCtr == 1u)
  {
    Can_DisableControllerInterrupts(0u);
  }
}

void SchM_Exit_Can_CAN_EXCLUSIVE_AREA_6(void)
{
  if (--BrsAsrApplCanInterruptLockCtr == 0u)
  {
    Can_EnableControllerInterrupts(0u);
  }
}

void SchM_Enter_CanIf_CANIF_EXCLUSIVE_AREA_0(void)
{
  if (++BrsAsrApplCanInterruptLockCtr == 1u)
  {
    Can_DisableControllerInterrupts(0u);
  }
}

void SchM_Exit_CanIf_CANIF_EXCLUSIVE_AREA_0(void)
{
  if (--BrsAsrApplCanInterruptLockCtr == 0u)
  {
    Can_EnableControllerInterrupts(0u);
  }
}

void SchM_Enter_CanSM_CANSM_EXCLUSIVE_AREA_4(void)
{
  if (++BrsAsrApplCanInterruptLockCtr == 1u)
  {
    Can_DisableControllerInterrupts(0u);
  }
}

void SchM_Exit_CanSM_CANSM_EXCLUSIVE_AREA_4(void)
{
  if (--BrsAsrApplCanInterruptLockCtr == 0u)
  {
    Can_EnableControllerInterrupts(0u);
  }
}

void SchM_Enter_CanSM_CANSM_EXCLUSIVE_AREA_1(void)
{
  /* Protects against task interruptions -> no locking needed, because all main functions are on same task */
}

void SchM_Exit_CanSM_CANSM_EXCLUSIVE_AREA_1(void)
{
  /* Protects against task interruptions -> no locking needed, because all main functions are on same task */
}

void SchM_Enter_ComM_COMM_EXCLUSIVE_AREA_1(void)
{
  /* Protects against task interruptions -> no locking needed, because all main functions are on same task */
}

void SchM_Exit_ComM_COMM_EXCLUSIVE_AREA_1(void)
{
  /* Protects against task interruptions -> no locking needed, because all main functions are on same task */
}
