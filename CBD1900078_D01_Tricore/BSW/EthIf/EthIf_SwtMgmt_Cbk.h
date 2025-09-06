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
/*!        \file  EthIf_SwtMgmt_Cbk.h
 *        \brief  EthIf SwtMgmt public callback API header
 *
 *      \details  Provides access to the public callback API of the sub-module SwtMgmt of EthIf.
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

#if !defined (ETHIF_SWTMGMT_CBK_H)
# define ETHIF_SWTMGMT_CBK_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_SwtMgmt_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

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


# if ( ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT == STD_ON )                                                               /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 *  EthIf_SwitchMgmtInfoIndication
 *********************************************************************************************************************/
/*! \brief          Notifies the EthIf about switch management information related to a received Ethernet frame
 *  \details        Function allows to provide switch management information for an received Ethernet frame to
 *                  the EthIf.
 *  \param[in]      CtrlIdx   Index of the EthIf controller
 *  \param[in]      DataPtr   Pointer to identify the frame context
 *  \param[in]      MgmtInfo  Switch management information
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT
 *  \trace          DSGN-EthIf22904
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_SwitchMgmtInfoIndication(
          uint8                                             CtrlIdx,
    P2VAR(uint8,               AUTOMATIC, ETHIF_APPL_VAR)   DataPtr,
  P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, ETHIF_APPL_DATA)  MgmtInfo);
# endif /* ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT */

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_19.1 */

#endif /* ETHIF_SWTMGMT_CBK_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_SwtMgmt_Cbk.h
 *********************************************************************************************************************/

