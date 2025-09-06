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
/*!        \file  vMem_30_XXspi01.h
 *        \brief  vMem_30_XXspi01 header file
 *
 *      \details  This is the header file of the vMem_30_XXspi01. It declares the interfaces of the vMem_30_XXspi01. 
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Bethina Mausz                 virbmz        Vector Informatik GmbH
 *  Tomas Ondrovic                viroto        Vector Informatik GmbH
 *  Charlotte Ricke               vircre        Vector Informatik GmbH
 *  Andreas Lackner               virlra        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author          Change Id                Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2018-04-23  virlra          STORY-7318               Initial version of vMem_30_XXspi01.
 *********************************************************************************************************************/

#if !defined (VMEM_30_XXSPI01_H)
# define VMEM_30_XXSPI01_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "vMem_30_XXspi01_Cfg.h"
# include "vMem_30_XXspi01_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* ----- Component version information (decimal version of ALM implementation package) ----- */
# define VMEM_30_XXSPI01_SW_MAJOR_VERSION                    (1u)
# define VMEM_30_XXSPI01_SW_MINOR_VERSION                    (0u)
# define VMEM_30_XXSPI01_SW_PATCH_VERSION                    (0u)

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define VMEM_30_XXSPI01_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Global API pointer table */
extern CONST(vMemAccM_vMemApiType, AUTOMATIC) vMem_30_XXspi01_FunctionPointerTable;

#define VMEM_30_XXSPI01_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define VMEM_30_XXSPI01_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_InitMemory()
 *********************************************************************************************************************/
/*! \brief       Function for *_INIT_*-variable initialization
 *  \details     Service to initialize module global variables at power up. This function initializes the
 *               variables in *_INIT_* sections. Used in case they are not initialized by the startup code.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_InitMemory(void);

/**********************************************************************************************************************
 * vMem_30_XXspi01_Init()
 *********************************************************************************************************************/
/*! \brief       Initialization function
 *  \details     This function initializes the module vMem_30_XXspi01. It initializes all variables and sets the module state to
 *               initialized.
 *  \param[in]   ConfigPtr               Pointer to the configuration data.
 *  \pre         Interrupts are disabled.
 *  \pre         vMem_30_XXspi01_InitMemory has been called unless vMem_30_XXspi01_ModuleInitialized is initialized by start-up code.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        Specification of module initialization
 *********************************************************************************************************************/
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_Init(P2CONST(vMem_30_XXspi01_ConfigType, AUTOMATIC, VMEM_30_XXSPI01_PBCFG) ConfigPtr);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_MainFunction()
 *********************************************************************************************************************/
/*! \brief       Monitors and controls the continuous execution of the vMem_30_XXspi01 handling.
 *  \details     -
 *  \param[in]   none.
 *  \param[out]  none.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_MainFunction(void);

# if (VMEM_30_XXSPI01_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  vMem_30_XXspi01_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief       Returns the version information
 *  \details     vMem_30_XXspi01_GetVersionInfo() returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]  versioninfo           Pointer to where to store the version information. Parameter must not be NULL.
 *  \pre         -
 *  \config      GetVersionInfo API is enabled via pre-compile switch.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-150071
 *********************************************************************************************************************/
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, VMEM_30_XXSPI01_APPL_VAR) VersionInfo);
# endif

# define VMEM_30_XXSPI01_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* VMEM_30_XXSPI01_H */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXspi01.h
 *********************************************************************************************************************/

