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
/*!        \file  EthIf_SwtTime_Cbk.h
 *        \brief  EthIf SwtTime public callback API header
 *
 *      \details  Provides access to the public callback API of the sub-module SwtTime of EthIf.
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

#if !defined (ETHIF_SWTTIME_CBK_H)
# define ETHIF_SWTTIME_CBK_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_SwtTime_Types.h"

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

# if ( ETHIF_ETHSWT_TIME_STAMP_SUPPORT == STD_ON )                                                                      /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 *  EthIf_SwitchEgressTimeStampIndication
 *********************************************************************************************************************/
/*! \brief          Notifies the EthIf about time stamping information related to an Ethernet frame transmitted
 *  \details        Function allows to provide time stamping information for an Ethernet frame transmitted at a
 *                  switch port to the EthIf.
 *  \param[in]      CtrlIdx    Index of the EthIf controller
 *  \param[in]      DataPtr    Pointer to identify the frame context
 *  \param[in]      MgmtInfo   Switch management information
 *  \param[in]      timeStamp  Port Egress Time stamp
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_SwitchEgressTimeStampIndication(
          uint8                                             CtrlIdx,
    P2VAR(uint8,               AUTOMATIC, ETHIF_APPL_VAR)   DataPtr,
  P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, ETHIF_APPL_DATA)  MgmtInfo,
  P2CONST(Eth_TimeStampType,   AUTOMATIC, ETHIF_APPL_DATA)  timeStamp);

/**********************************************************************************************************************
 *  EthIf_SwitchIngressTimeStampIndication
 *********************************************************************************************************************/
/*! \brief         Notifies the EthIf about time stamping information related to an Ethernet frame received
 *  \details       Function allows to provide time stamping information for an Ethernet frame received at a switch
 *                 port to the EthIf.
 *  \param[in]      CtrlIdx    Index of the EthIf controller
 *  \param[in]      DataPtr    Pointer to identify the frame context
 *  \param[in]      MgmtInfo   Switch management information
 *  \param[in]      timeStamp  Port Ingress Time stamp
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_SwitchIngressTimeStampIndication(
          uint8                                             CtrlIdx,
    P2VAR(uint8,               AUTOMATIC, ETHIF_APPL_VAR)   DataPtr,
  P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, ETHIF_APPL_DATA)  MgmtInfo,
  P2CONST(Eth_TimeStampType,   AUTOMATIC, ETHIF_APPL_DATA)  timeStamp);

# endif /* ETHIF_ETHSWT_TIME_STAMP_SUPPORT */

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_19.1 */

#endif /* ETHIF_SWTTIME_CBK_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_SwtTime_Cbk.h
 *********************************************************************************************************************/

