/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Rte_CtCddIoHwAb.h
 *        Config:  E:/1.MCU_Prj/1.AURIX_TC3X7/TC397_Vector_Prj/DEMO_0314/AUTOSAR/TC397START.dpa
 *     SW-C Type:  CtCddIoHwAb
 *  Generated at:  Tue Nov  5 20:09:34 2024
 *
 *     Generator:  MICROSAR RTE Generator Version 4.19.0
 *                 RTE Core Version 1.19.0
 *       License:  CBD1900078
 *
 *   Description:  Application header file for SW-C <CtCddIoHwAb> (Contract Phase)
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_CTCDDIOHWAB_H
# define _RTE_CTCDDIOHWAB_H

# ifdef RTE_APPLICATION_HEADER_FILE
#  error Multiple application header files included.
# endif
# define RTE_APPLICATION_HEADER_FILE
# ifndef RTE_PTR2ARRAYBASETYPE_PASSING
#  define RTE_PTR2ARRAYBASETYPE_PASSING
# endif

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

/* include files */

# include "Rte_CtCddIoHwAb_Type.h"
# include "Rte_DataHandleType.h"


/**********************************************************************************************************************
 * Component Data Structures and Port Data Structures
 *********************************************************************************************************************/

struct Rte_CDS_CtCddIoHwAb
{
  /* dummy entry */
  uint8 _dummy;
};

# define RTE_START_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern CONSTP2CONST(struct Rte_CDS_CtCddIoHwAb, RTE_CONST, RTE_CONST) Rte_Inst_CtCddIoHwAb; /* PRQA S 0850 */ /* MD_MSR_19.8 */

# define RTE_STOP_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

typedef P2CONST(struct Rte_CDS_CtCddIoHwAb, TYPEDEF, RTE_CONST) Rte_Instance;


# define CtCddIoHwAb_START_SEC_CODE
# include "CtCddIoHwAb_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *
 * Runnable Entity Name: PiIoHwRead_ReadChannel
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadChannel> of PortPrototype <PiIoHwRead>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType PiIoHwRead_ReadChannel(IdtDioValueType *Value)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_PiIoHwRead_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_PiIoHwRead_ReadChannel PiIoHwRead_ReadChannel
FUNC(Std_ReturnType, CtCddIoHwAb_CODE) PiIoHwRead_ReadChannel(P2VAR(IdtDioValueType, AUTOMATIC, RTE_CTCDDIOHWAB_APPL_VAR) Value); /* PRQA S 0850 */ /* MD_MSR_19.8 */

# define CtCddIoHwAb_STOP_SEC_CODE
# include "CtCddIoHwAb_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

# define RTE_E_PiIoHwRead_E_NOT_OK (1U)

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* _RTE_CTCDDIOHWAB_H */
