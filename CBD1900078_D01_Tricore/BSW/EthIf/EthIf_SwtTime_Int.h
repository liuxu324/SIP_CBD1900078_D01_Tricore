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
/*!        \file  EthIf_SwtTime_Int.h
 *        \brief  EthIf SwtTime internal header file
 *
 *      \details  Provides access to types/functions/data of the sub-module SwtTime of EthIf only to be used internally,
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

#if !defined (ETHIF_SWTTIME_INT_H)
# define ETHIF_SWTTIME_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_SwtTime_Types_Int.h"

# include "EthIf.h"      /* access to DET error IDs */
# include "EthIf_Int.h"  /* access to components/utils shared with all EthIf modules */

/*********************************************************************************************************
 * Predefined file includes based on usage of other components/sub-modules within this sub-module
 * defined in \trace DSGN-EthIfDiag1937
 *********************************************************************************************************/
/* Dependency to <User> resolved through EthIf_Lcfg.h -> no include needed */
/* Dependency to EthSwt resolved through EthIf_Lcfg.h -> no include needed */
# include "EthIf_Utils_Int.h"

/*********************************************************************************************************
 * Predefined file includes based on usage of this sub-module by other components/sub-modules
 * defined in \trace DSGN-EthIfDiag1937
 *********************************************************************************************************/
/* Dependency to <User> resolved through EthIf_Lcfg.h -> no include needed */
/* Dependency to EthSwt resolved through EthIf_Lcfg.h -> no include needed */
# include "EthIf_Rx_Types_Int.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# if !defined (ETHIF_SWTTIME_INT_LOCAL)                                                                                 /* COV_ETHIF_LOCAL_INLINE */
#  define ETHIF_SWTTIME_INT_LOCAL static
# endif

# if !defined (ETHIF_SWTTIME_INT_LOCAL_INLINE)                                                                          /* COV_ETHIF_LOCAL_INLINE */
#  define ETHIF_SWTTIME_INT_LOCAL_INLINE LOCAL_INLINE
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
 *  EthIf_SwtTime_Init
 *********************************************************************************************************************/
/*! \brief          Initializes the EthIf SwtTime sub-module
 *  \details        -
 *  \pre            Configuration pointer must have been initialized
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_SwtTime_Init( void );

# if ( ETHIF_ETHSWT_TIME_STAMP_SUPPORT == STD_ON )                                                                      /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 *  EthIf_InitiateTxSwtTimeStampInfoProc
 *********************************************************************************************************************/
/*! \brief          Initiates the switch time stamp processing for the passed frame buffer
 *  \details        This function sets up the internal data structures for being able to handle switch time stamping
 *                  processing during transmission for the passed frame buffer
 *  \param[in]      ethCtrlIdx    Eth controller the frame buffer is related to
 *                                [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \param[in]      ethIfCtrlIdx  EthIf controller the frame shall be sent on
 *                                [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \param[in]      bufIdx        Frame buffer identifier in context of the Eth/EthIf controller
 *                                [range: bufIdx <= EthIf_GetMaxTxBufForEthIfCtrl(ethIfCtrlIdx)]
 *  \param[in]      bufLen        Frame buffer length
 *  \param[in]      dataPtr       Pointer to the payload portion of the frame buffer
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_InitiateTxSwtTimeStampInfoProc(
        EthIf_EthCtrlIterType              ethCtrlIdx,
        EthIf_EthIfCtrlIterType            ethIfCtrlIdx,
        uint8                              bufIdx,
        uint16                             bufLen,
  P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR)  dataPtr);

/**********************************************************************************************************************
 *  EthIf_ArmTxSwtTimeStampInfoProc
 *********************************************************************************************************************/
/*! \brief          Arm the switch time stamp processing for the passed frame buffer
 *  \details        This function initiazes the switch time stamp processing for the passed frame buffer in context of the
 *                  common transmission procedure (EthIf_ProvideTxBuffer()/EthIf_Transmit()). It retains the information
 *                  related to the frame in case switch time stamping was requested for the frame.
 *  \param[in]      ethCtrlIdx  Eth controller the frame buffer is related to
 *                              [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \param[in]      bufIdx      Frame buffer identifier in context of the Eth/EthIf controller
 *  \param[in]      ownerIdx    Owner the frame is related to
 *                              [range: frameOwnerIdx < EthIf_GetSizeOfUser()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_ArmTxSwtTimeStampInfoProc(
  EthIf_EthCtrlIterType  ethCtrlIdx,
  uint8                  bufIdx,
  EthIf_UserIterType     ownerIdx);

/**********************************************************************************************************************
 *  EthIf_FinishTxSwtTimeStampInfoProc
 *********************************************************************************************************************/
/*! \brief          Completes the switch time stamp processing for the passed frame buffer
 *  \details        This function completes the switch time stamp processing for the passed frame buffer in context of the
 *                  common transmission procedure (EthIf_ProvideTxBuffer()/EthIf_Transmit()). It discards the information
 *                  if no time stamping was requested for the frame.
 *  \param[in]      ethCtrlIdx  Eth controller the frame buffer is related to
 *                              [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \param[in]      bufIdx      Frame buffer identifier in context of the Eth/EthIf controller
 *  \param[in]      len         Length of the frame buffer (0 for release request)
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_FinishTxSwtTimeStampInfoProc(
  EthIf_EthCtrlIterType  ethCtrlIdx,
  uint8                  bufIdx,
  uint16                 len);

/**********************************************************************************************************************
 *  EthIf_InitiateRxSwtTimeStampInfoProc
 *********************************************************************************************************************/
/*! \brief          Initiates the switch time stamp processing for a received frame
 *  \details        This function sets up the internal data structures for being able to handle switch time stamping
 *                  processing during reception for the passed frame
 *  \param[in]      ethCtrlIdx          Eth controller the frame is related to
 *                                      [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \param[in]      ownerIdx            Owner the frame is related to
 *                                      [range: ownerIdx < EthIf_GetSizeOfUser()]
 *  \param[in]      ulRxIndicationData  Rx indication data related to the frame
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_InitiateRxSwtTimeStampInfoProc(
          EthIf_EthCtrlIterType                                      ethCtrlIdx,
          EthIf_UserIterType                                         ownerIdx,
  P2CONST(EthIf_UlRxIndiactionDataType, AUTOMATIC, ETHIF_APPL_DATA)  ulRxIndicationData);
#endif /* ETHIF_ETHSWT_TIME_STAMP_SUPPORT */

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_19.1 */

#endif /* ETHIF_SWTTIME_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_SwtTime_Int.h
 *********************************************************************************************************************/

