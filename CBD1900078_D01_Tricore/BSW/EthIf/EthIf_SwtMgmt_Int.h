/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  EthIf_SwtMgmt_Int.h
 *        \brief  EthIf SwtMgmt internal header file
 *
 *      \details  Provides access to types/functions/data of the sub-module SwtMgmt of EthIf only to be used internally,
 *                where functions are intended to be linked by linker.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#if !defined (ETHIF_SWTMGMT_INT_H)
# define ETHIF_SWTMGMT_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_SwtMgmt_Types_Int.h"

# include "EthIf.h"      /* access to DET error IDs */
# include "EthIf_Int.h"  /* access to components/utils shared with all EthIf modules */

/*********************************************************************************************************
 * Predefined file includes based on usage of other components/sub-modules within this sub-module
 * defined in \trace DSGN-EthIfDiag1937
 *********************************************************************************************************/
/* Dependency to <User> resolved through EthIf_Lcfg.h -> no include needed */
/* Dependency to EthSwt resolved through EthIf_Lcfg.h -> no include needed */
# include "EthIf_Utils_Int.h"
# include "EthIf_Tx_Int.h"

/*********************************************************************************************************
 * Predefined file includes based on usage of this sub-module by other components/sub-modules
 * defined in \trace DSGN-EthIfDiag1937
*********************************************************************************************************/
/* Dependency to <User> resolved through EthIf_Lcfg.h -> no include needed */
/* Dependency to EthSwt resolved through EthIf_Lcfg.h -> no include needed */
# include "EthIf_Rx_Types_Int.h"
# include "EthIf_Tx_Types_Int.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# if !defined (ETHIF_SWTMGMT_INT_LOCAL)                                                                                 /* COV_ETHIF_LOCAL_INLINE */
#  define ETHIF_SWTMGMT_INT_LOCAL static
# endif

# if !defined (ETHIF_SWTMGMT_INT_LOCAL_INLINE)                                                                          /* COV_ETHIF_LOCAL_INLINE */
#  define ETHIF_SWTMGMT_INT_LOCAL_INLINE LOCAL_INLINE
# endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETHIF_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  EthIf_SwtMgmt_Init
 *********************************************************************************************************************/
/*! \brief          Initializes the EthIf SwtMgmt sub-module
 *  \details        -
 *  \pre            Configuration pointer must have been initialized
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_SwtMgmt_Init( void );

# if ( ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT == STD_ON )                                                                /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 *  EthIf_InitiateRxSwtMgmtInfoProc
 *********************************************************************************************************************/
/*! \brief          Initiates the switch frame management information processing for a received frame
 *  \details        This function sets up the internal data structures for being able to handle switch frame management
 *                  information processing during reception for the passed frame
 *  \param[in]      ethCtrlIdx          Eth controller the frame is related to
 *                                      [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \param[in]      ownerIdx            Owner the frame is related to
 *                                      [range: ownerIdx < EthIf_GetSizeOfUser()]
 *  \param[in]      ulRxIndicationData  Rx indication data related to the frame
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_InitiateRxSwtMgmtInfoProc(
          EthIf_EthCtrlIterType                                      ethCtrlIdx,
          EthIf_UserIterType                                         ownerIdx,
  P2CONST(EthIf_UlRxIndiactionDataType, AUTOMATIC, ETHIF_APPL_DATA)  ulRxIndicationData);
# endif /* ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT */

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_19.1 */

#endif /* ETHIF_SWTMGMT_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_SwtMgmt_Int.h
 *********************************************************************************************************************/

