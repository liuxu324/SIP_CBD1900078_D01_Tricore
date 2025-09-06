/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  EthTSyn_Pdelay_Int.c
 *        \brief  EthTSyn Path Delay source file - Internal Functions
 *
 *      \details  EthTSyn Path Delay source file containing the EthTSyn Path Delay implementation of the EthTSyn
 *                module.
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

#define ETHTSYN_PDELAY_INT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EthTSyn_Pdelay_Int.h" /* PRQA S 0883, 3219, 0810 */ /* MD_EthTSyn_0883, MD_EthTSyn_3219, MD_MSR_1.1_810 */
#include "EthTSyn_Int.h" /* PRQA S 3219 */ /* MD_EthTSyn_3219 */
#include "EthTSyn_Util_Int.h" /* PRQA S 3219 */ /* MD_EthTSyn_3219 */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of EthTSyn header file */
#if (  (ETHTSYN_SW_MAJOR_VERSION != (7u)) \
    || (ETHTSYN_SW_MINOR_VERSION != (0u)) \
    || (ETHTSYN_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of EthTSyn_Pdelay_Int.c and EthTSyn.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (ETHTSYN_CFG_MAJOR_VERSION != (7u)) \
    || (ETHTSYN_CFG_MINOR_VERSION != (0u)) )
# error "Version numbers of EthTSyn_Pdelay_Int.c and EthTSyn_Cfg.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (ETHTSYN_LOCAL) /* COV_MSR_COMPATIBILITY */
# define ETHTSYN_LOCAL static
#endif

#if !defined (ETHTSYN_LOCAL_INLINE) /* COV_MSR_COMPATIBILITY */
# define ETHTSYN_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define ETHTSYN_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_InitPdelayInternal
 *********************************************************************************************************************/
/*! \brief      Initializes the passed Pdelay.
 *  \details    Initializes all component variables directly related to the passed Pdelay.
 *  \param[in]  PdelayIdx  Index of the Pdelay
 *                         [range: PdelayIdx < EthTSyn_GetSizeOfPdelayConfig()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_InitPdelayInternal(
  EthTSyn_PdelayConfigIterType PdelayIdx);

#if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  PDELAY INITIATOR
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_InitPdelayInitiator
 *********************************************************************************************************************/
/*! \brief      Initializes the passed Pdelay initiator.
 *  \details    Initializes all component variables directly related to the passed Pdelay initiator.
 *  \param[in]  PdelayInitiatorIdx  Index of the Pdelay initiator
 *                                  [range: PdelayInitiatorIdx < EthTSyn_GetSizeOfPdelayInitiator()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_InitPdelayInitiator(
  EthTSyn_PdelayInitiatorIterType PdelayInitiatorIdx);


/**********************************************************************************************************************
 *  EthTSyn_Pdelay_TxPdelayReqMsg
 *********************************************************************************************************************/
/*! \brief      Transmits a Pdelay Request message.
 *  \details    Transmits a Pdelay Request message on the passed Port. This includes getting a TxBuffer.
 *  \param[in]  PortIdx         Index of the port that should transmit the message
 *                              [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     E_OK - Message transmission was successful
 *  \return     E_NOT_OK - Message transmission was not successful
 *  \pre        Constraints for PortIdx: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                       EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                       EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *  \note       In case of any error, the possibly locked TxBuffer is released by this function
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Pdelay_TxPdelayReqMsg(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_PdelayTx_CopyPdelayReqToTxBuffer
 *********************************************************************************************************************/
/*! \brief      Copies a PdelayReq message to the given Tx buffer in Network-Byte-Order.
 *  \details    -
 *  \param[in]  PortIdx         Index of the port that should transmit the message
 *                              [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[out] TxBufPtr        The assembled PdelayReq message in Network-Byte-Order
 *              the PdelayReq message.
 *  \pre        Constraints for PortIdx: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                       EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                       EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TxBuffers
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_PdelayTx_CopyPdelayReqToTxBuffer(
  EthTSyn_IntPortIdxType PortIdx, ETHTSYN_P2VAR(uint8) TxBufPtr);


/**********************************************************************************************************************
 *  EthTSyn_Pdelay_CheckForPdelayRespTimeout
 *********************************************************************************************************************/
/*! \brief      Checks if a PdelayResp or PdelayRespFollowUp timeout occurred and handles the timeout.
 *  \details    -
 *  \param[in]  PortIdx         Index of the used port
 *                              [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - Transmission of new PdelayReq should be triggered
 *  \return     FALSE - No transmission of new PdelayReq required
 *  \pre        Constraint for PortIdx: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                      EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                      EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Pdelay_CheckForPdelayRespTimeout(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_TriggerPdelayCalculation
 *********************************************************************************************************************/
/*! \brief      Triggers the calculation of a new Pdelay.
 *  \details    Checks if a new Pdelay value can be computed. If so triggers the calculation of the new Pdelay.
 *  \param[in]  PortIdx         Index of the port
 *                              [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre        Constraint for PortIdx: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                      EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                      EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_TriggerPdelayCalculation(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_ComputePdelay
 *********************************************************************************************************************/
/*! \brief      Calculates the path delay for the passed Port.
 *  \details    -
 *  \param[in]  PortIdx         Index of the used port
 *                              [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     E_OK - Calculation was successful
 *  \return     E_NOT_OK - Calculation was not successful
 *  \pre        Constraint for PortIdx: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                      EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                      EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Pdelay_ComputePdelay(
  EthTSyn_IntPortIdxType PortIdx);

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_PdelayRx_IsReadyToReceivePdelayResp
 *********************************************************************************************************************/
/*! \brief      Checks if a Pdelay response message reception is possible.
 *  \details    Checks if a Pdelay response message can currently be received on the passed Port without respect to the
 *              Pdelay request state machine state, i.e. if the passed Port is an active Pdelay initiator.
 *  \param[in]  PortIdx   Index of the port
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - Ready to receive Pdelay response message
 *  \return     FALSE - Not ready to receive Pdelay response message
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_PdelayRx_IsReadyToReceivePdelayResp(
  EthTSyn_IntPortIdxType PortIdx);
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_PdelayRx_ReceivePdelayResp
 *********************************************************************************************************************/
/*! \brief      Receives a Pdelay response message.
 *  \details    Checks the state of the Pdelay request state machine and performs required action for the reception
 *              of the Pdelay response message.
 *  \param[in]  PortIdx     Index of the Port the Pdelay request was received on
 *                          [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]  ComMsgPtr   Pointer to the received Pdelay response message
 *  \pre        Constraint for PortIdx: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                      EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                      EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *  \note       The preconditions for PortIdx can be ensured by EthTSyn_PdelayRx_IsReadyToReceivePdelayResp(PortIdx)
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_PdelayRx_ReceivePdelayResp(
                  EthTSyn_IntPortIdxType     PortIdx,
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType)  ComMsgPtr);
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_PdelayRx_IsReadyToReceivePdelayRespFup
 *********************************************************************************************************************/
/*! \brief      Checks if a Pdelay response follow up message reception is possible.
 *  \details    Checks if a Pdelay response follow up message can currently be received on the passed Port including
 *              state check of the Pdelay request state machine.
 *  \param[in]  PortIdx   Index of the port
 *                        [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     TRUE - Ready to receive Pdelay response follow up message
 *  \return     FALSE - Not ready to receive Pdelay response follow up message
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_PdelayRx_IsReadyToReceivePdelayRespFup(
  EthTSyn_IntPortIdxType PortIdx); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

/**********************************************************************************************************************
 *  END: PDELAY INITIATOR
 *********************************************************************************************************************/
#endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

#if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  PDELAY RESPONDER
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_InitPdelayResponder
 *********************************************************************************************************************/
/*! \brief      Initializes the passed Pdelay responder.
 *  \details    Initializes all component variables directly related to the passed Pdelay responder.
 *  \param[in]  PdelayResponderIdx  Index of the Pdelay responder
 *                                  [range: PdelayResponderIdx < EthTSyn_GetSizeOfPdelayResponder()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_InitPdelayResponder(
  EthTSyn_PdelayResponderIterType PdelayResponderIdx);

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_TxPdelayRespMsg
 *********************************************************************************************************************/
/*! \brief      Transmits a PdelayResp message.
 *  \details    Transmits a PdelayResp message on the passed port. This includes getting a TxBuffer.
 *  \param[in]  PortIdx         Index of the port that should transmit the message
 *                              [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     E_OK - Message transmission was successful
 *  \return     E_NOT_OK - Message transmission was not successful
 *  \pre        Constraint for PortIdx: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                      EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                      EthTSyn_IsPdelayResponderUsedOfPdelayConfig() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *  \note       In case of any error, the possibly locked TxBuffer is released by this function
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Pdelay_TxPdelayRespMsg(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_PdelayTx_CopyPdelayRespToTxBuffer
 *********************************************************************************************************************/
/*! \brief      Copies a PdelayResp message to the provided TxBuffer in Network-Byte-Order.
 *  \details    -
 *  \param[in]  PortIdx         Index of the port that should transmit the message
 *                              [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[out] TxBufPtr        The assembled PdelayResp message in Network-Byte-Order
 *  \pre        Constraint for PortIdx: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                      EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                      EthTSyn_IsPdelayResponderUsedOfPdelayConfig() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_PdelayTx_CopyPdelayRespToTxBuffer(
                EthTSyn_IntPortIdxType PortIdx,
  ETHTSYN_P2VAR(uint8)                 TxBufPtr);

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_TxPdelayRespFupMsg
 *********************************************************************************************************************/
/*! \brief      Transmits a PdelayResp FollowUp message.
 *  \details    Transmits a PdelayResp FollowUp message on the passed port. This includes getting a TxBuffer.
 *  \param[in]  PortIdx         Index of the port that should transmit the message
 *                              [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     E_OK - Message transmission was successful
 *  \return     E_NOT_OK - Message transmission was not successful
 *  \pre        Constraint for PortIdx: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                      EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                      EthTSyn_IsPdelayResponderUsedOfPdelayConfig() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *  \note       In case of any error, the possibly locked TxBuffer is released by this function
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Pdelay_TxPdelayRespFupMsg(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_PdelayTx_CopyPdelayRespFupToTxBuffer
 *********************************************************************************************************************/
/*! \brief      Copies a PdelayResp FollowUp message to the provided TxBuffer in Network-Byte-Order.
 *  \details    -
 *  \param[in]  PortIdx         Index of the port that should transmit the message
 *  \param[out] TxBufPtr        The assembled PdelayResp FollowUp message in Network-Byte-Order
 *  \pre        Constraint for PortIdx: EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *                                      EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *                                      EthTSyn_IsPdelayResponderUsedOfPdelayConfig() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_PdelayTx_CopyPdelayRespFupToTxBuffer(
                EthTSyn_IntPortIdxType PortIdx,
  ETHTSYN_P2VAR(uint8)                 TxBufPtr); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/**********************************************************************************************************************
 *  END PDELAY RESPONDER
 *********************************************************************************************************************/
#endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_InitPdelayInternal
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_InitPdelayInternal(
  EthTSyn_PdelayConfigIterType PdelayIdx)
{
  /* #10 Set default pdelay values. */
  EthTSyn_SetAsCapableOfPdelayInfo(PdelayIdx, (boolean)EthTSyn_IsAlwaysAsCapableOfPdelayConfig(PdelayIdx));            /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
  EthTSyn_SetPdelayValueNsOfPdelayInfo(PdelayIdx, EthTSyn_GetInitialPdelayNsOfPdelayConfig(PdelayIdx));                /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
  EthTSyn_SetUseAverageOfPdelayInfo(PdelayIdx, FALSE);                                                                 /* SBSW_ETHTSYN_API_ARGUMENT_IDX */

  /* #20 Initialize Pdelay initiator. */
#if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
  if(EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig(PdelayIdx) == TRUE)
  {
    EthTSyn_Pdelay_InitPdelayInitiator(EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(PdelayIdx));
  }
#endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

  /* #30 Initialize Pdelay responder. */
#if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
  if(EthTSyn_IsPdelayResponderUsedOfPdelayConfig(PdelayIdx) == TRUE)
  {
    EthTSyn_Pdelay_InitPdelayResponder(EthTSyn_GetPdelayResponderIdxOfPdelayConfig(PdelayIdx));
  }
#endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */
} /* EthTSyn_Pdelay_InitPdelayInternal() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

#if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  PDELAY INITIATOR
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_InitPdelayInitiator
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_InitPdelayInitiator(
  EthTSyn_PdelayInitiatorIterType PdelayInitiatorIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_P2VAR(EthTSyn_PdelayReqSmType) pDelayReqSmPtr =
      EthTSyn_GetAddrPdelayReqSm(EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(PdelayInitiatorIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set Pdelay request state machine state to NOT_ENABLED. */
  pDelayReqSmPtr->State = ETHTSYN_S_PD_REQ_SM_DISABLED;                                                                /* SBSW_ETHTSYN_API_ARGUMENT_IDX */

  /* #20 Set default values of Pdelay request state machine. */
  pDelayReqSmPtr->PdelayReq.TxIntervalCnt = EthTSyn_GetTxIntervalMfOfPdelayInitiator(PdelayInitiatorIdx);              /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
  pDelayReqSmPtr->TxBuf.Index = ETHTSYN_INV_BUF_IDX;                                                                   /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
  pDelayReqSmPtr->TxBuf.Address = NULL_PTR;                                                                            /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
  pDelayReqSmPtr->PdelayReq.SequenceId = 0;                                                                            /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
  pDelayReqSmPtr->TxConfirmationPending = 0u;                                                                          /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
  pDelayReqSmPtr->LostResponses = 0u;                                                                                  /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
  pDelayReqSmPtr->FrameId = ETHTSYN_INVALID_FRAME_ID;                                                                  /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
} /* EthTSyn_Pdelay_InitPdelayInitiator() */

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_TxPdelayReqMsg
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
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Pdelay_TxPdelayReqMsg(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  const EthTSyn_CtrlIdxOfPortType ctrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);
  const EthTSyn_EthIfCtrlIdxOfCtrlType ethIfCtrlIdx = EthTSyn_GetEthIfCtrlIdxOfCtrl(ctrlIdx);
  EthTSyn_EthTxBufferStructType txBuffer;


  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Port is ready for transmission and get an Ethernet TxBuffer. */
  txBuffer.Length = ETHTSYN_MSG_P_DELAY_REQ_LENGTH;
  if(EthTSyn_UtilTx_ProvideTxBuffer(ethIfCtrlIdx, EthTSyn_GetFramePrioOfPort(PortIdx), &txBuffer) == E_OK)             /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
  {
    const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
      EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
    const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
      EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
    EthTSyn_PdelayReqSmPtrType pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);
    ETHTSYN_P2CONST(EthTSyn_SwtMgmtInfoType) mgmtInfoPtr = NULL_PTR;
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
    EthTSyn_SwtMgmtInfoType mgmtInfo;
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

    ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #20 Reload timeout interval and increment SequenceId. */
    pDelayReqSmPtr->PdelayReq.TxIntervalCnt = EthTSyn_GetTxIntervalMfOfPdelayInitiator(pDelayInitiatorIdx);            /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
    pDelayReqSmPtr->PdelayReq.SequenceId++;                                                                            /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */

    /* #30 Copy PdelayReq to Ethernet TxBuffer. */
    EthTSyn_PdelayTx_CopyPdelayReqToTxBuffer(PortIdx, txBuffer.BufferPtr);                                             /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
    /* #40 Get switch management info and frame id if applicable. */
    if(EthTSyn_UtilTx_GetSwtMgmtInfo(PortIdx, &mgmtInfo) == E_OK)                                                      /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
    {
      mgmtInfo.FrameId = txBuffer.FrameId;
      pDelayReqSmPtr->FrameId = mgmtInfo.FrameId;                                                                      /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
      mgmtInfoPtr = &mgmtInfo;
    }
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
    pDelayReqSmPtr->PdelayReq.EgressTimestampMgmt.State =
      ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_WAITING_FOR_TIMESTAMP;                                                /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */

    ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #50 Try to enable egress timestamp. */
    retVal = EthTSyn_UtilTx_PrepareTransmission(ethIfCtrlIdx, txBuffer.BufferIdx, ETHTSYN_ENABLE_TS_HW_XOR_SWT_TS,
      mgmtInfoPtr);                                                                                                    /* SBSW_ETHTSYN_POINTER_VARIABLE */
    if(retVal == E_OK)
    {
      /* #500 Successfully enabled egress timestamp -> trigger transmission. */
      retVal = EthTSyn_UtilTx_Transmit(ethIfCtrlIdx, txBuffer.BufferIdx, ETHTSYN_MSG_P_DELAY_REQ_LENGTH);
    }

    /* #60 Check if transmission was successful. */
    if(retVal == E_OK)
    {
      /* #600 Transmission successful. Increment pending TxConfirmation count of pDelay request state machine and store
              Tx buffer information. */
      pDelayReqSmPtr->TxConfirmationPending++;                                                                         /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
      pDelayReqSmPtr->TxBuf.Index = txBuffer.BufferIdx;                                                                /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
      pDelayReqSmPtr->TxBuf.Address = txBuffer.BufferPtr;                                                              /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
    }
    else
    {
      /* #601 Transmission failed. Release Ethernet transmission buffer. */
      EthTSyn_UtilTx_ReleaseTxBuffer(ethIfCtrlIdx, txBuffer.BufferIdx);
    }
  }

  return retVal;
} /* EthTSyn_Pdelay_TxPdelayReqMsg() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  EthTSyn_PdelayTx_CopyPdelayReqToTxBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_PdelayTx_CopyPdelayReqToTxBuffer(
                EthTSyn_IntPortIdxType PortIdx,
  ETHTSYN_P2VAR(uint8)                 TxBufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_P2VAR(EthTSyn_CommonMsgHdrType) comMsgPtr;

  /* ----- Implementation ----------------------------------------------- */
  comMsgPtr = (ETHTSYN_P2VAR(EthTSyn_CommonMsgHdrType))TxBufPtr; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */

  /* #10 Set common header message attributes. */
  EthTSyn_UtilTx_PrepareCommonMsgHdr(comMsgPtr, ETHTSYN_MSG_TYPE_PDELAY_REQ, PortIdx);                                 /* SBSW_ETHTSYN_PASSING_API_POINTER */

  /* Pdelay request message only included reserved fields as message specific field. The hole Ethernet transmission
   * buffer is initialized with '0' by the EthTSyn therefore no action is required here. */

} /* EthTSyn_PdelayTx_CopyPdelayReqToTxBuffer() */

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_CheckForPdelayRespTimeout
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
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Pdelay_CheckForPdelayRespTimeout(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean txPdelayReq = FALSE;
  boolean lostResponse = FALSE;
  const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
  const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
    EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
  const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
    EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
  ETHTSYN_CONSTP2VAR(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Pdelay request transmission interval elapsed. */
  ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  if (pDelayReqSmPtr->PdelayReq.TxIntervalCnt == 0u)
  {
    /* #100 Interval elapsed -> mark lost response and transmission. */
    txPdelayReq = TRUE;
    lostResponse = TRUE;
  }
  else
  {
    /* #101 Interval not elapsed -> Check for Pdelay response timeout. */
    if(EthTSyn_GetRespRespFollowUpTimeoutOfPdelayInitiator(pDelayInitiatorIdx) > 0)
    {
      if(pDelayReqSmPtr->PdelayRespRespFollowUpTimeout == 0u)
      {
        lostResponse = TRUE;
      }
    }
  }

  /* #20 Check for lost response. */
  if(lostResponse == TRUE)
  {
    /* #200 Lost response -> reset PdelayReqSm state to WAITING_FOR_PDELAY_INTERVAL_COUNTER */
    pDelayReqSmPtr->State = ETHTSYN_S_PD_REQ_SM_WAIT_TX_COUNTER;                                                       /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */

    /* #201 Check for lost response limit. */
    if(pDelayReqSmPtr->LostResponses < EthTSyn_GetAllowedLostResponsesOfPdelayInitiator(pDelayInitiatorIdx))
    {
      /* #2010 Lost response limit not exceeded -> Increment lost response counter. */
      pDelayReqSmPtr->LostResponses++;                                                                                 /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
    }
    else
    {
      /* #2011 Lost response limit exceeded -> Set AsCapable to FALSE if AlwaysAsCapable is FALSE for the Port. */
      EthTSyn_Util_SetAsCapable(PortIdx, FALSE);
    }
  }

  ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */


  return txPdelayReq;
} /* EthTSyn_Pdelay_CheckForPdelayRespTimeout() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_TriggerPdelayCalculation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_TriggerPdelayCalculation(EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_PdelayConfigIdxOfPortType pDelayIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
  const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
    EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayIdx);
  const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
    EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
  ETHTSYN_CONSTP2VAR(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);
  boolean newAsCapable = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Verify that TxConfirmation for sent Pdelay request occurred. */
  if(pDelayReqSmPtr->TxConfirmationPending == 0)
  {
    /* #20 Verify that Pdelay request egress timestamp is ready for processing. */
    if(EthTSyn_IsTimestampReadyToProcess(pDelayReqSmPtr->PdelayReq.EgressTimestampMgmt.State) == TRUE)
    {
# if ( (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) && (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF) )
      /* SW-Timestamping */
      /* #30 For SW-Timestamping: Check for and handle overflow of raw timestamp for PdelayRespIngress timestamp. */
      pDelayReqSmPtr->PdelayResp.IngressTimestampMgmt.Timestamp = EthTSyn_Util_CheckAndHandleRawTimestampOverflow(     /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */ /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
          &pDelayReqSmPtr->PdelayReq.EgressTimestampMgmt.Timestamp,
          pDelayReqSmPtr->PdelayResp.IngressTimestampRaw);
# endif /* ( (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) && (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF) ) */
      /* #40 All values of Pdelay request sequence are available --> Compute new Pdelay, set AsCapable and
       * change the state of the PdelayReqSm to WAITING_FOR_PDELAY_INTERVAL_COUNTER. */
      if (EthTSyn_IsUseStaticPdelayOfPdelayConfig(pDelayIdx) == FALSE)
      {
        newAsCapable = (boolean)(EthTSyn_Pdelay_ComputePdelay(PortIdx) == E_OK);
      }

      EthTSyn_Util_SetAsCapable(PortIdx, newAsCapable);
      pDelayReqSmPtr->State = ETHTSYN_S_PD_REQ_SM_WAIT_TX_COUNTER;                                                     /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
    }
  }
} /* EthTSyn_Pdelay_TriggerPdelayCalculation() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_ComputePdelay
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Pdelay_ComputePdelay(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  EthTSyn_TimediffType localResidenceTime = 0;
  EthTSyn_TimediffType remoteResidenceTime = 0;
  EthTSyn_TimediffType currentPdelay;
  const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
  const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
    EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
  const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
    EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
  ETHTSYN_CONSTP2VAR(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* computes the mean propagation delay on the link (see also IEEE802.1AS-2011 Figure 11-1) */
  /* t1: Pdelay_Req egress timestamp (initiator), t2: Pdelay_Req ingress timestamp (responder) */
  /* t3: Pdelay_Resp egress timestamp (responder), t4: Pdelay_Resp ingress timestamp (initiator) */
  /*      (t4 - t1) - (t3 - t2)                      */
  /* D = ___________________________                 */
  /*              2                                  */

  /* #10 Compute local residence time. */
  if(EthTSyn_Util_TimestampMinusTimestamp(&pDelayReqSmPtr->PdelayResp.IngressTimestampMgmt.Timestamp,
      &pDelayReqSmPtr->PdelayReq.EgressTimestampMgmt.Timestamp, &localResidenceTime) == E_OK)                          /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
  {
    /* #20 Successfully computed local residence time -> compute remote residence time. */
    if(EthTSyn_Util_TimestampMinusTimestamp(&pDelayReqSmPtr->PdelayRespFollowUp.ResponseOriginTimestampMgmt.Timestamp,
        &pDelayReqSmPtr->PdelayResp.RequestReceiptTimestamp, &remoteResidenceTime) == E_OK)                            /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
    {
      /* #30 Successfully computed remote residence time --> calculate current path delay. */
      currentPdelay = (localResidenceTime - remoteResidenceTime) / 2u;
      /* #40 Perform sanity and threshold check of path delay. */
      /* PRQA S 3415 6 */ /* MD_EthTSyn_3415_CslReadOnly */
      if(
        (remoteResidenceTime >= 0) &&
        (localResidenceTime >= 0) &&
        (currentPdelay >= 0u) &&
        (currentPdelay < (EthTSyn_TimediffType)EthTSyn_GetPdelayThresholdOfPdelayInitiator(pDelayInitiatorIdx))
        )
      {
        /* #50 Valid Pdelay -> apply weighted averaging. */
        const EthTSyn_PdelayConfigIdxOfPortType pDelayIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
        EthTSyn_PdelayType tmpPdelay;

        if (EthTSyn_IsUseAverageOfPdelayInfo(pDelayIdx) == TRUE)
        {
          tmpPdelay = EthTSyn_GetPdelayValueNsOfPdelayInfo(pDelayIdx);
          tmpPdelay = (EthTSyn_PdelayType)(
            (((EthTSyn_GetAverageWeightOfPdelayInitiator(pDelayInitiatorIdx) - 1) * tmpPdelay) +
            (EthTSyn_PdelayType)currentPdelay) / EthTSyn_GetAverageWeightOfPdelayInitiator(pDelayInitiatorIdx));
        }
        else
        {
          tmpPdelay = (EthTSyn_PdelayType)currentPdelay;
          EthTSyn_SetUseAverageOfPdelayInfo(pDelayIdx, TRUE);                                                          /* SBSW_ETHTSYN_CSL03 */
        }

        EthTSyn_SetPdelayValueNsOfPdelayInfo(pDelayIdx, tmpPdelay);                                                    /* SBSW_ETHTSYN_CSL03 */

        retVal = E_OK;
      }
    }
  }

  return retVal;
}/* EthTSyn_Pdelay_ComputePdelay() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_PdelayRx_IsReadyToReceivePdelayResp
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */

ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_PdelayRx_IsReadyToReceivePdelayResp(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* #10 Return TRUE if port is active pdelay port and pdelay initiator is enabled. Otherwise return FALSE. */
  return EthTSyn_Util_IsPdelayInitiator(PortIdx);
} /* EthTSyn_PdelayRx_IsReadyToReceivePdelayResp() */
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_PdelayRx_ReceivePdelayResp
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
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_PdelayRx_ReceivePdelayResp(
                  EthTSyn_IntPortIdxType    PortIdx,
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) ComMsgPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
  const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
    EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
  const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
    EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
  ETHTSYN_CONSTP2VAR(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);
  boolean lostResponse = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check Pdelay request state machine state. */
  if(pDelayReqSmPtr->State == ETHTSYN_S_PD_REQ_SM_WAIT_RESP)
  {
    /* #100 Waiting for Pdelay response -> continue message processing. */
    ETHTSYN_CONSTP2CONST(EthTSyn_PdelayRespMsgType) pDelayRespMsgPtr =
      (ETHTSYN_P2CONST(EthTSyn_PdelayRespMsgType))&((ETHTSYN_P2CONST(uint8))ComMsgPtr)[ETHTSYN_HDR_COM_LENGTH]; /* PRQA S 0310 */ /* MD_EthTSyn_0310_SubType */

    /* #101 Check for matching Sequence Id and requesting source port identity. */
    /* PRQA S 0310, 3415 3 */ /* MD_EthTSyn_0310_PortIdent, MD_EthTSyn_3415_ReadOnly */
    if((EthTSyn_PortIdentityIsEqualLocalPort(PortIdx,
        (ETHTSYN_P2CONST(EthTSyn_PortIdentityType))pDelayRespMsgPtr->RequestingClockIdentity) == TRUE) &&              /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */
        ((uint16)EthTSyn_Ntohs(ComMsgPtr->SequenceId) == pDelayReqSmPtr->PdelayReq.SequenceId))
    {
      /* #1010 Store message attributes. */
      pDelayReqSmPtr->PdelayResp.SequenceId = (uint16)EthTSyn_Ntohs(ComMsgPtr->SequenceId);                            /* SBSW_ETHTSYN_CSL02_03 */
      EthTSyn_SetClockIdentity(pDelayReqSmPtr->PdelayResp.SourcePortIdentity.ClockIdentity,
        ComMsgPtr->SourceClockIdentity);                                                                               /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */ /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
      pDelayReqSmPtr->PdelayResp.SourcePortIdentity.PortNumber =
        (EthTSyn_PortNumberType)EthTSyn_Ntohs(ComMsgPtr->SourcePortNumber);                                            /* SBSW_ETHTSYN_CSL02_03 */
      /* PRQA S 0310 2 */ /* MD_EthTSyn_0310_Timestamp */
      EthTSyn_NtohTimestamp(&pDelayReqSmPtr->PdelayResp.RequestReceiptTimestamp,
        (ETHTSYN_P2VAR(EthTSyn_TimestampType))pDelayRespMsgPtr->RequestReceiptTimestampSeconds);                       /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */

      /* #1011 Change state of the pdelay request state machine. */
      pDelayReqSmPtr->State = ETHTSYN_S_PD_REQ_SM_WAIT_RESP_FUP;                                                       /* SBSW_ETHTSYN_CSL02_03 */
    }
    else
    {
      lostResponse = TRUE;
    }
  }
  /* #20 Check for double Pdelay response */
  else if(pDelayReqSmPtr->State == ETHTSYN_S_PD_REQ_SM_WAIT_RESP_FUP)
  {
    if(pDelayReqSmPtr->PdelayReq.SequenceId == (uint16)EthTSyn_Ntohs(ComMsgPtr->SequenceId))
    {
      /* #200 Received Pdelay response with same sequence id twice -> lost response. */
      lostResponse = TRUE;
    }
  }
  else
  {
    /* Nothing to do here. */
  }

  /* #30 Check for lost response. */
  if(lostResponse == TRUE)
  {
    /* #300 Invalid message attributes -> treat as lost response. */
    if(pDelayReqSmPtr->LostResponses < EthTSyn_GetAllowedLostResponsesOfPdelayInitiator(pDelayInitiatorIdx))
    {
      pDelayReqSmPtr->LostResponses++;                                                                                 /* SBSW_ETHTSYN_CSL02_03 */
    }
    else
    {
      /* Lost response limit exceeded -> Mark as not AsCapable if port is not set to 'AlwaysAsCapable'. */
      EthTSyn_Util_SetAsCapable(PortIdx, FALSE);
    }

    /* #301 Trigger re-transmission of the pdelay request */
    pDelayReqSmPtr->State = ETHTSYN_S_PD_REQ_SM_TX_REQ;                                                                /* SBSW_ETHTSYN_CSL02_03 */
  }
} /* EthTSyn_PdelayRx_ReceivePdelayResp() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_PdelayRx_IsReadyToReceivePdelayRespFup
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_PdelayRx_IsReadyToReceivePdelayRespFup(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isReady = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Port is an active Pdelay initiator. */
  if(EthTSyn_Util_IsPdelayInitiator(PortIdx) == TRUE)
  {
    /* #20 Pdelay initiator is enabled -> check State of Pdelay Request state machine. */
    const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
      EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
    const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
      EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
    ETHTSYN_CONSTP2CONST(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);

    if(pDelayReqSmPtr->State == ETHTSYN_S_PD_REQ_SM_WAIT_RESP_FUP)
    {
      isReady = TRUE;
    }
  }

  return isReady;
} /* EthTSyn_PdelayRx_IsReadyToReceivePdelayRespFup() */
# endif /* #if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

/**********************************************************************************************************************
 *  END: PDELAY INITIATOR
 *********************************************************************************************************************/
#endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

#if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  PDELAY RESPONDER
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_InitPdelayResponder
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_InitPdelayResponder(
  EthTSyn_PdelayResponderIterType PdelayResponderIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pDelayRespSmIdx =
    EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(PdelayResponderIdx);
  ETHTSYN_CONSTP2VAR(EthTSyn_PdelayRespSmType) pDelayRespSmPtr =
    EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set Pdelay response state machine state to NOT_ENABLED. */
  pDelayRespSmPtr->State = ETHTSYN_S_PD_RESP_SM_DISABLED;                                                              /* SBSW_ETHTSYN_API_ARGUMENT_IDX */

  /* #20 Set default values of Pdelay response state machine. */
  pDelayRespSmPtr->TxBuf.Index = ETHTSYN_INV_BUF_IDX;                                                                  /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
  pDelayRespSmPtr->TxBuf.Address = NULL_PTR;                                                                           /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
  pDelayRespSmPtr->TxConfirmationPending = 0u;                                                                         /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
  pDelayRespSmPtr->InProgress = FALSE;                                                                                 /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
  pDelayRespSmPtr->FrameId = ETHTSYN_INVALID_FRAME_ID;                                                                 /* SBSW_ETHTSYN_API_ARGUMENT_IDX */
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
} /* EthTSyn_Pdelay_InitPdelayResponder() */

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_TxPdelayRespMsg
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
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Pdelay_TxPdelayRespMsg(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  EthTSyn_EthTxBufferStructType txBuffer;

  const EthTSyn_CtrlIdxOfPortType ctrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);
  const EthTSyn_EthIfCtrlIdxOfCtrlType ethIfCtrlIdx = EthTSyn_GetEthIfCtrlIdxOfCtrl(ctrlIdx);
  const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
  const EthTSyn_PdelayResponderIdxOfPdelayConfigType pDelayResponderIdx =
    EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pDelayCfgIdx);
  const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pDelayRespSmIdx =
    EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pDelayResponderIdx);
  ETHTSYN_CONSTP2VAR(EthTSyn_PdelayRespSmType) pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get Ethernet transmission buffer. */
  txBuffer.Length = ETHTSYN_MSG_P_DELAY_RESP_LENGTH;
  if(EthTSyn_UtilTx_ProvideTxBuffer(ethIfCtrlIdx, EthTSyn_GetFramePrioOfPort(PortIdx), &txBuffer) == E_OK)             /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
  {
    ETHTSYN_P2CONST(EthTSyn_SwtMgmtInfoType) mgmtInfoPtr = NULL_PTR;
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
    EthTSyn_SwtMgmtInfoType mgmtInfo;
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

    ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #20 Copy the Pdelay response to the Ethernet TxBuffer. */
    EthTSyn_PdelayTx_CopyPdelayRespToTxBuffer(PortIdx, txBuffer.BufferPtr);                                            /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */

    /* #40 Get switch management info and frame id if applicable. */
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
    if(EthTSyn_UtilTx_GetSwtMgmtInfo(PortIdx, &mgmtInfo) == E_OK)                                                      /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */

    {
      /* #400 Store frame id if applicable. */
      mgmtInfo.FrameId = txBuffer.FrameId;
      pDelayRespSmPtr->FrameId = mgmtInfo.FrameId;                                                                     /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
      mgmtInfoPtr = &mgmtInfo;
    }
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

    pDelayRespSmPtr->PdelayResp.EgressTimestampMgmt.State =
        ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_WAITING_FOR_TIMESTAMP;                                              /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
    pDelayRespSmPtr->State = ETHTSYN_S_PD_RESP_SM_WAIT_RESP_TS;                                                        /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */

    ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #50 Prepare message transmission (i.e. enable egress timestamping and set up switch mgmt info). */
    retVal = EthTSyn_UtilTx_PrepareTransmission(ethIfCtrlIdx, txBuffer.BufferIdx, ETHTSYN_ENABLE_TS_HW_XOR_SWT_TS,
      mgmtInfoPtr);                                                                                                    /* SBSW_ETHTSYN_POINTER_VARIABLE */
    if(retVal == E_OK)
    {
      /* #500 Prepared message transmission. Trigger transmission. */
      retVal = EthTSyn_UtilTx_Transmit(ethIfCtrlIdx, txBuffer.BufferIdx, ETHTSYN_MSG_P_DELAY_RESP_LENGTH);
    }

    /* #60 Store buffer index and pointer for TxConfirmation in case of successful transmission and release Ethernet
           transmission buffer otherwise. */
    if(retVal == E_OK)
    {
      pDelayRespSmPtr->TxBuf.Index = txBuffer.BufferIdx;                                                               /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
      pDelayRespSmPtr->TxBuf.Address = txBuffer.BufferPtr;                                                             /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
    }
    else
    {
      EthTSyn_UtilTx_ReleaseTxBuffer(ethIfCtrlIdx, txBuffer.BufferIdx);
    }
  }

  return retVal;
} /* EthTSyn_Pdelay_TxPdelayRespMsg() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  EthTSyn_PdelayTx_CopyPdelayRespToTxBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_PdelayTx_CopyPdelayRespToTxBuffer(
                EthTSyn_IntPortIdxType PortIdx,
  ETHTSYN_P2VAR(uint8)                 TxBufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_P2VAR(EthTSyn_PdelayRespMsgType) pDelayRespMsgPtr;
  ETHTSYN_P2VAR(EthTSyn_CommonMsgHdrType) comMsgPtr;
  const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
  const EthTSyn_PdelayResponderIdxOfPdelayConfigType pDelayResponderIdx =
    EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pDelayCfgIdx);
  const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pDelayRespSmIdx =
    EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pDelayResponderIdx);
  ETHTSYN_CONSTP2VAR(EthTSyn_PdelayRespSmType) pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* Set message pointers */
  comMsgPtr = (ETHTSYN_P2VAR(EthTSyn_CommonMsgHdrType))TxBufPtr; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */
  pDelayRespMsgPtr = (ETHTSYN_P2VAR(EthTSyn_PdelayRespMsgType))&TxBufPtr[ETHTSYN_HDR_COM_LENGTH]; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */

  /* #10 Initialize common message header. */
  EthTSyn_UtilTx_PrepareCommonMsgHdr(comMsgPtr, ETHTSYN_MSG_TYPE_PDELAY_RESP, PortIdx);                                /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */

  /* #20 Set message specific attributes. */
  EthTSyn_SetClockIdentity(pDelayRespMsgPtr->RequestingClockIdentity,
      pDelayRespSmPtr->PdelayReq.SourcePortIdentity.ClockIdentity);                                                    /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */

  pDelayRespMsgPtr->RequestingPortNumber =
      (uint16)EthTSyn_Htons(pDelayRespSmPtr->PdelayReq.SourcePortIdentity.PortNumber);                                 /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */

  /* #30 Set request received timestamp. */
  /* PRQA S 0310 2 */ /* MD_EthTSyn_0310_Timestamp */
  EthTSyn_UtilTx_HtonTimestamp(
    (ETHTSYN_P2VAR(EthTSyn_TimestampType))pDelayRespMsgPtr->RequestReceiptTimestampSeconds,
    &pDelayRespSmPtr->PdelayReq.IngressTimestampMgmt.Timestamp);                                                       /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */
} /* EthTSyn_PdelayTx_CopyPdelayRespToTxBuffer() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_TxPdelayRespFupMsg
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
 */
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Pdelay_TxPdelayRespFupMsg(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_CtrlIdxOfPortType ctrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);
  const EthTSyn_EthIfCtrlIdxOfCtrlType ethIfCtrlIdx = EthTSyn_GetEthIfCtrlIdxOfCtrl(ctrlIdx);
  Std_ReturnType retVal = E_NOT_OK;
  EthTSyn_EthTxBufferStructType txBuffer;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get Ethernet transmission buffer. */
  txBuffer.Length = ETHTSYN_MSG_P_DELAY_RESP_FOLLOW_UP_LENGTH;
  if(EthTSyn_UtilTx_ProvideTxBuffer(ethIfCtrlIdx, EthTSyn_GetFramePrioOfPort(PortIdx), &txBuffer) == E_OK)             /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
  {
    ETHTSYN_P2CONST(EthTSyn_SwtMgmtInfoType) mgmtInfoPtr = NULL_PTR;
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
    EthTSyn_SwtMgmtInfoType mgmtInfo;
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

    ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #20 Copy PdelayResp FollowUp message to TxBuffer. */
    EthTSyn_PdelayTx_CopyPdelayRespFupToTxBuffer(PortIdx, txBuffer.BufferPtr);                                         /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
    /* #30 Get Switch management info if required. */
    if(EthTSyn_UtilTx_GetSwtMgmtInfo(PortIdx, &mgmtInfo) == E_OK)                                                      /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
    {
      /* #300 Get frame id if required. */
      mgmtInfo.FrameId = txBuffer.FrameId;
      mgmtInfoPtr = &mgmtInfo;
    }
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */

    ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #40 Prepare transmission (i.e. set switch mgmt info). */
    retVal = EthTSyn_UtilTx_PrepareTransmission(ethIfCtrlIdx, txBuffer.BufferIdx, ETHTSYN_ENABLE_TS_NONE, mgmtInfoPtr);/* SBSW_ETHTSYN_POINTER_VARIABLE */
    if(retVal == E_OK)
    {
      /* #50 Successfully prepared transmission. Trigger transmission. */
      retVal = EthTSyn_UtilTx_Transmit(ethIfCtrlIdx, txBuffer.BufferIdx, ETHTSYN_MSG_P_DELAY_RESP_FOLLOW_UP_LENGTH);
    }

    if(retVal != E_OK)
    {
      /* #60 Transmission failed. Release Ethernet transmission buffer. */
      EthTSyn_UtilTx_ReleaseTxBuffer(ethIfCtrlIdx, txBuffer.BufferIdx);
    }
  }

  return retVal;
} /* EthTSyn_Pdelay_TxPdelayRespFupMsg() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  EthTSyn_PdelayTx_CopyPdelayRespFupToTxBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(void, ETHTSYN_CODE) EthTSyn_PdelayTx_CopyPdelayRespFupToTxBuffer(
                EthTSyn_IntPortIdxType PortIdx,
  ETHTSYN_P2VAR(uint8)                 TxBufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHTSYN_P2VAR(EthTSyn_PDelayResFollowUpMsgType) pDelayRespFollowUpPtr;
  ETHTSYN_P2VAR(EthTSyn_CommonMsgHdrType) comMsgPtr;
  const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
  const EthTSyn_PdelayResponderIdxOfPdelayConfigType pDelayResponderIdx =
    EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pDelayCfgIdx);
  const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pDelayRespSmIdx =
    EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pDelayResponderIdx);
  ETHTSYN_CONSTP2VAR(EthTSyn_PdelayRespSmType) pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* Set message pointers. */
  comMsgPtr = (ETHTSYN_P2VAR(EthTSyn_CommonMsgHdrType))TxBufPtr; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */
  pDelayRespFollowUpPtr = (ETHTSYN_P2VAR(EthTSyn_PDelayResFollowUpMsgType))&TxBufPtr[ETHTSYN_HDR_COM_LENGTH]; /* PRQA S 0310 */ /* MD_EthTSyn_0310_MsgStruct */

  /* #10 Set common header message attributes. */
  EthTSyn_UtilTx_PrepareCommonMsgHdr(comMsgPtr, ETHTSYN_MSG_TYPE_PDELAY_RES_FOLLOW_UP, PortIdx);                       /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */

  /* #20 Set specific message type attributes. */
  EthTSyn_SetClockIdentity(pDelayRespFollowUpPtr->RequestingClockIdentity,
      pDelayRespSmPtr->PdelayReq.SourcePortIdentity.ClockIdentity);                                                    /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */

  pDelayRespFollowUpPtr->RequestingPortNumber =
      (uint16)EthTSyn_Htons(pDelayRespSmPtr->PdelayReq.SourcePortIdentity.PortNumber);                                 /* SBSW_ETHTSYN_WRITE_TO_TX_BUFFER */

  /* PRQA S 0310 3 */ /* MD_EthTSyn_0310_Timestamp */
  EthTSyn_UtilTx_HtonTimestamp(
      (ETHTSYN_P2VAR(EthTSyn_TimestampType))pDelayRespFollowUpPtr->ResponseOriginTimestampSeconds,
      &pDelayRespSmPtr->PdelayResp.EgressTimestampMgmt.Timestamp);                                                     /* SBSW_ETHTSYN_TX_BUFFER_POINTER_VARIABLE */ /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */

} /* EthTSyn_PdelayTx_CopyPdelayRespFupToTxBuffer() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  END PDELAY RESPONDER
 *********************************************************************************************************************/
#endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_Init(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_PdelayConfigIterType pdelayCfgIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate all pdelay configurations and trigger initialization. */
  for(pdelayCfgIter = 0; pdelayCfgIter < EthTSyn_GetSizeOfPdelayConfig(); pdelayCfgIter++)
  {
    EthTSyn_Pdelay_InitPdelayInternal(pdelayCfgIter);
  }
}

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_InitPdelayOfPort
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_InitPdelayOfPort(
  EthTSyn_PortIterType PortIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the given port is an active pdelay port, trigger initialization of the Pdelay. */
  if(EthTSyn_Util_IsActivePdelayPort((EthTSyn_IntPortIdxType)PortIdx) == TRUE)
  {
    EthTSyn_Pdelay_InitPdelayInternal(EthTSyn_GetPdelayConfigIdxOfPort(PortIdx));
  }
} /* EthTSyn_Pdelay_InitPdelayOfPort() */

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_GetCurrentPdelay
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(EthTSyn_PdelayType, ETHTSYN_CODE) EthTSyn_Pdelay_GetCurrentPdelay(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_PdelayType pDelay = 0;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check for valid Pdelay index. */
  if(EthTSyn_IsPdelayConfigUsedOfPort(PortIdx) == TRUE)
  {
    const EthTSyn_PdelayConfigIdxOfPortType pdelayIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    /* #20 Get the current Pdelay value. */
    pDelay = EthTSyn_GetPdelayValueNsOfPdelayInfo(pdelayIdx);
  }

  return pDelay;
} /* EthTSyn_Pdelay_GetCurrentPdelay() */

#if ( (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) || (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) )
/**********************************************************************************************************************
 *  EthTSyn_Pdelay_HandleCyclicTasks
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
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_HandleCyclicTasks(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_PdelayConfigIterType pDelayIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all Pdelay configurations */
  for(pDelayIter = 0; pDelayIter < EthTSyn_GetSizeOfPdelayConfig(); pDelayIter++)
  {
    const EthTSyn_IntPortIdxType activePdelayPortIdx = EthTSyn_GetPortIdxOfPdelayConfig(pDelayIter);
# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
    /* #20 Check if Pdelay initiator is activated for the current Pdelay configuration. */
    if(EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig(pDelayIter) == TRUE)
    {
      const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
          EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayIter);
      const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
          EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
      ETHTSYN_P2VAR(EthTSyn_PdelayReqSmType) pdelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);

      /* #200 Handle timers and timeouts of Pdelay request state machine. */
      ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
      if (pdelayReqSmPtr->PdelayReq.TxIntervalCnt > 0u)
      {
        pdelayReqSmPtr->PdelayReq.TxIntervalCnt--;                                                                     /* SBSW_ETHTSYN_CSL03 */
      }
      if (pdelayReqSmPtr->PdelayRespRespFollowUpTimeout > 0u)
      {
        pdelayReqSmPtr->PdelayRespRespFollowUpTimeout--;                                                               /* SBSW_ETHTSYN_CSL03 */
      }
      ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

      /* #201 Process Pdelay request state machine. */
      EthTSyn_Pdelay_ProcSmPdReq(activePdelayPortIdx);
    }
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
    /* #30 Check of Pdelay responder is activated for the current Pdelay configuration. */
    if(EthTSyn_IsPdelayResponderUsedOfPdelayConfig(pDelayIter) == TRUE)
    {
      /* #300 Process Pdelay response state machine. */
      EthTSyn_Pdelay_ProcSmPdResp(activePdelayPortIdx);
    }
# endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

  } /* END: Iteration Pdelay Config */
} /* EthTSyn_Pdelay_HandleCyclicTasks() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
#endif /* ( (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) || (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) ) */

#if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  PDELAY INITIATOR
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_ProcSmPdReq
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
FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_ProcSmPdReq(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
  const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
    EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
  const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
    EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
  ETHTSYN_CONSTP2VAR(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);
  boolean txPdelayReq = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check Pdelay request state machine state. */
  switch(pDelayReqSmPtr->State)
  {
  case ETHTSYN_S_PD_REQ_SM_DISABLED:
    {
      /* #100 State: Not enabled -> Enable state machine if port is tx ready. */
      if(EthTSyn_IsTxReady(PortIdx) == TRUE)
      {
        pDelayReqSmPtr->State = ETHTSYN_S_PD_REQ_SM_TX_REQ;                                                            /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX_PTR_BY_INDIRECTION */
      }
      break;
    }

  case ETHTSYN_S_PD_REQ_SM_TX_REQ:
    {
      /* #101 State: Send Pdelay request -> mark transmission of Pdelay request. */
      txPdelayReq = TRUE;
      break;
    }

  case ETHTSYN_S_PD_REQ_SM_WAIT_RESP:
  case ETHTSYN_S_PD_REQ_SM_WAIT_RESP_FUP:
    {
      /* #102 State: Waiting for Pdelay response/response follow up -> Check and handle PdelayResp or
       *      PdelayRespFollowUp timeout. */
      txPdelayReq = EthTSyn_Pdelay_CheckForPdelayRespTimeout(PortIdx);
      break;
    }

  case ETHTSYN_S_PD_REQ_SM_COMPUTE_PDELAY:
    {
      /* #103 State: Received Pdelay response and response follow up -> trigger Pdelay calculation. */
      EthTSyn_Pdelay_TriggerPdelayCalculation(PortIdx);
      break;
    }

  case ETHTSYN_S_PD_REQ_SM_WAIT_TX_COUNTER:
    {
      /* #104 State: Waiting for Pdelay interval counter -> Handle Pdelay interval counter. */
      if(pDelayReqSmPtr->PdelayReq.TxIntervalCnt == 0u)
      {
        txPdelayReq = TRUE;
      }
      break;
    }

  default:
    {
      /* Nothing to do here. */
      break;
    }

  } /* END: switch(pDelayReqSmPtr->State) */

  /* #20 Check if Pdelay request should be transmitted. */
  if(txPdelayReq == TRUE)
  {
    /* #200 Tx Pdelay request required -> verify that port is ready for transmission. */
    if (EthTSyn_IsTxReady(PortIdx) == TRUE)
    {
      /* #2000 Port is tx ready -> transmit Pdelay request. */
      if (EthTSyn_Pdelay_TxPdelayReqMsg(PortIdx) == E_OK)
      {
        /* #20000 Transmission successful. Change state to WAIT_RESP and charge RespRespgFupTimeout. */
        pDelayReqSmPtr->State = ETHTSYN_S_PD_REQ_SM_WAIT_RESP;                                                         /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX_PTR_BY_INDIRECTION */
        pDelayReqSmPtr->PdelayRespRespFollowUpTimeout =
          EthTSyn_GetRespRespFollowUpTimeoutOfPdelayInitiator(pDelayInitiatorIdx);                                     /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX_PTR_BY_INDIRECTION */
      }
      else
      {
        /* #20001 Transmission failed. Change state to TX_REQ. */
        pDelayReqSmPtr->State = ETHTSYN_S_PD_REQ_SM_TX_REQ;                                                            /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX_PTR_BY_INDIRECTION */
      }
    }
    else
    {
      /* #2001 Port is not tx ready -> disable Pdelay request state machine. */
      pDelayReqSmPtr->State = ETHTSYN_S_PD_REQ_SM_DISABLED;                                                            /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX_PTR_BY_INDIRECTION */
    }
  }

} /* EthTSyn_Pdelay_ProcSmPdReq() */ /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_EthTSyn_6050_CslAccess */

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_Pdelay_ProcRcvdRespMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_ProcRcvdRespMsg(
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) ComMsgPtr,
                  EthTSyn_IntPortIdxType    PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
#  if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  Eth_TimestampQualityType timestampQual = ETH_INVALID;
#  else
  const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
  const StbM_SynchronizedTimeBaseType timeBaseId = EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(timeDomainIdx);
#  endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if port is ready to received Pdelay response. */
  if(EthTSyn_PdelayRx_IsReadyToReceivePdelayResp(PortIdx) == TRUE)
  {
    /* #20 Pdelay initiator is enabled -> continue message processing. */
    const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
      EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
    const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
      EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
    ETHTSYN_CONSTP2VAR(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);

    /* #30 Get Ingress timestamp. */
    pDelayReqSmPtr->PdelayResp.IngressTimestampMgmt.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_NOT_AVAILABLE;  /* SBSW_ETHTSYN_CSL02_03 */
#  if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
    /* HW-Timestamping */
    /* PRQA S 0310, 0311 2 */ /* MD_EthTSyn_0310_MsgStructRev, MD_EthTSyn_0311 */
    if(EthIf_GetIngressTimestamp(
      EthTSyn_Util_GetEthIfCtrlIdxOfPort(PortIdx), (ETHTSYN_P2VAR(Eth_DataType))ComMsgPtr,
      &pDelayReqSmPtr->PdelayResp.IngressTimestampMgmt.Timestamp, &timestampQual) == E_OK)                             /* SBSW_ETHTSYN_PASSING_API_POINTER */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */  /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */
    {
      if(timestampQual == ETH_VALID)
      {
        pDelayReqSmPtr->PdelayResp.IngressTimestampMgmt.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_AVAILABLE;  /* SBSW_ETHTSYN_CSL02_03 */
      }
    }
#  else
    /* SW-Timestamping */
    if(StbM_GetCurrentTimeRaw(timeBaseId, &pDelayReqSmPtr->PdelayResp.IngressTimestampRaw) == E_OK)                    /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
    {
      /* For SW-Timestamping an overflow check has to be performed for the pDelayRespIngressTimestamp.
       * This check is done in EthTSyn_Pdelay_TriggerPdelayCalculation() where it is ensured that the
       * PdelayReqEgressTimestamp is available which is required for the overflow check. */
      pDelayReqSmPtr->PdelayResp.IngressTimestampMgmt.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_AVAILABLE;    /* SBSW_ETHTSYN_CSL02_03 */
    }
#  endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

    /* #40 Check if ingress timestamp is available. */
    if(pDelayReqSmPtr->PdelayResp.IngressTimestampMgmt.State == ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_AVAILABLE)
    {
      /* #400 Timestamp available -> receive Pdelay response. */
      EthTSyn_PdelayRx_ReceivePdelayResp(PortIdx, ComMsgPtr);                                                          /* SBSW_ETHTSYN_PASSING_API_POINTER */
    }

  }
} /* EthTSyn_Pdelay_ProcRcvdRespMsg() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_Pdelay_ProcRcvdRespFupMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_ProcRcvdRespFupMsg(
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) ComMsgPtr,
                  EthTSyn_IntPortIdxType    PortIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if port is ready to receive a Pdelay response follow up message. */
  if(EthTSyn_PdelayRx_IsReadyToReceivePdelayRespFup(PortIdx) == TRUE)
  {
    const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
      EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
    const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
      EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
    ETHTSYN_CONSTP2VAR(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);
    ETHTSYN_P2CONST(EthTSyn_PDelayResFollowUpMsgType) pDelayRespFollowUpMsgPtr =
      (ETHTSYN_P2CONST(EthTSyn_PDelayResFollowUpMsgType))&((ETHTSYN_P2CONST(uint8))ComMsgPtr)[ETHTSYN_HDR_COM_LENGTH]; /* PRQA S 0310 */ /* MD_EthTSyn_0310_SubType */

    ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    /* #20 Check message attributes (Sequence Id, Matching Port Identity for PdelayResp and PdelayRespFollowUp,
     * Matching Requesting Port Identity) */
    /* Check Sequnce Id */
    if((uint16)EthTSyn_Ntohs(ComMsgPtr->SequenceId) == pDelayReqSmPtr->PdelayReq.SequenceId)
    {
      /* Check Source Port Identity */
      /* PRQA S 0310 3 */ /* MD_EthTSyn_0310_PortIdent */
      if(EthTSyn_PortIdentityIsEqual(
          (ETHTSYN_P2CONST(EthTSyn_PortIdentityType))&pDelayReqSmPtr->PdelayResp.SourcePortIdentity,
          (ETHTSYN_P2CONST(EthTSyn_PortIdentityType))ComMsgPtr->SourceClockIdentity) == TRUE)                          /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */ /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
      {
        /* Check Requesting Port Identity */
        /* PRQA S 0310 2 */ /* MD_EthTSyn_0310_PortIdent */
        if(EthTSyn_PortIdentityIsEqualLocalPort(PortIdx,
            (ETHTSYN_P2CONST(EthTSyn_PortIdentityType))pDelayRespFollowUpMsgPtr->RequestingClockIdentity) == TRUE)     /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */
        {
          /* #30 Store message attributes, reset lost responses and transit Pdelay request state machine. */
          /* PRQA S 0310 2 */ /* MD_EthTSyn_0310_Timestamp */
          EthTSyn_NtohTimestamp(&pDelayReqSmPtr->PdelayRespFollowUp.ResponseOriginTimestampMgmt.Timestamp,
              (ETHTSYN_P2VAR(EthTSyn_TimestampType))pDelayRespFollowUpMsgPtr->ResponseOriginTimestampSeconds);         /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */

          /* Reset lost responses. */
          pDelayReqSmPtr->LostResponses = 0u;                                                                          /* SBSW_ETHTSYN_CSL02_03 */

          /* valid PdelayResp and PdelayRespFollowUp were received -> path delay calculation in MainFunction
           * context is possible, after PdelayReq message was transmitted successfully (indicated by
           * TxConfirmationPending flag)*/

          pDelayReqSmPtr->State = ETHTSYN_S_PD_REQ_SM_COMPUTE_PDELAY;                                                  /* SBSW_ETHTSYN_CSL02_03 */
        }
      }
    }
    ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }

} /* EthTSyn_Pdelay_ProcRcvdRespFupMsg() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

/**********************************************************************************************************************
 *  END: PDELAY INITIATOR
 *********************************************************************************************************************/
#endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

#if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  PDELAY RESPONDER
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_ProcSmPdResp
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
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_ProcSmPdResp(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
  const EthTSyn_PdelayResponderIdxOfPdelayConfigType pDelayResponderIdx =
    EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pDelayCfgIdx);
  const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pDelayRespSmIdx =
    EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pDelayResponderIdx);
  ETHTSYN_CONSTP2VAR(EthTSyn_PdelayRespSmType) pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check Pdelay response state machine state. */
  switch(pDelayRespSmPtr->State)
  {
  case ETHTSYN_S_PD_RESP_SM_DISABLED:
    {
      /* #100 State: Not enabled -> enable Pdelay response state machine. */
      if((EthTSyn_GetAddrCtrlState(EthTSyn_GetCtrlIdxOfPort(PortIdx)))->TrcvLinkState == ETHTRCV_LINK_STATE_ACTIVE)
      {
        pDelayRespSmPtr->State = ETHTSYN_S_PD_RESP_SM_WAIT_REQ;                                                        /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
      }
      break;
    }

  case ETHTSYN_S_PD_RESP_SM_TX_RESP:
    {
      /* #101 State: Send Pdelay response -> Verify that port is ready to transmit Pdelay response. */
      /* PRQA S 3415 2 */ /* MD_EthTSyn_3415_ReadOnly */
      if((EthTSyn_IsTxReady(PortIdx) == TRUE) &&
        (EthTSyn_IsTimestampReadyToProcess(pDelayRespSmPtr->PdelayReq.IngressTimestampMgmt.State) == TRUE))
      {
        ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
        pDelayRespSmPtr->TxConfirmationPending++;                                                                      /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
        ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
        /* #1010 Ready for transmission -> transmit Pdelay response message. */
        if(EthTSyn_Pdelay_TxPdelayRespMsg(PortIdx) != E_OK)
        {
          ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
          pDelayRespSmPtr->TxConfirmationPending--;                                                                    /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
          pDelayRespSmPtr->State = ETHTSYN_S_PD_RESP_SM_TX_RESP;                                                       /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
          ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
        }
      }
      break;
    }

  case ETHTSYN_S_PD_RESP_SM_WAIT_RESP_TS:
    {
      /* #102 State: Waiting for Pdelay response egress timestamp -> Check if TxConfirmation for send Pdelay response
       * occurred */
      if((EthTSyn_IsTimestampReadyToProcess(pDelayRespSmPtr->PdelayResp.EgressTimestampMgmt.State) == TRUE) &&
        (pDelayRespSmPtr->TxConfirmationPending == 0))
      {
        /* #1020 TxConfirmation occurred -> Transmit Pdelay response follow up. */
        pDelayRespSmPtr->State = ETHTSYN_S_PD_RESP_SM_TX_RESP_FUP;                                                     /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
      }
      break;
    }

  case ETHTSYN_S_PD_RESP_SM_TX_RESP_FUP:
    {
      /* #103 State: Send Pdelay response follow up -> Verify that port is ready to transmit Pdelay response follow up. */
      if(EthTSyn_IsTxReady(PortIdx) == TRUE)
      {
        /* #1030 Ready for transmission -> transmit Pdelay response follow up message. */
        if(EthTSyn_Pdelay_TxPdelayRespFupMsg(PortIdx) == E_OK)
        {
          pDelayRespSmPtr->State = ETHTSYN_S_PD_RESP_SM_WAIT_REQ;                                                      /* SBSW_ETHTSYN_API_ARGUMENT_PORT_IDX */
        }
      }
      break;
    }

  default:
    {
      /* Nothing to do here. */
      break;
    }
  }

} /* EthTSyn_Pdelay_ProcSmPdResp() */ /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_EthTSyn_6050_CslAccess */

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
/**********************************************************************************************************************
 *  EthTSyn_Pdelay_ProcRcvdReqMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_ProcRcvdReqMsg(
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) ComMsgPtr,
                  EthTSyn_IntPortIdxType    PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
#  if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  Eth_TimestampQualityType    timestampQual;
#  else
  StbM_TimeStampRawType pDelayRequestReceivedTimestamp = 0;
  const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
  const StbM_SynchronizedTimeBaseType timeBaseId = EthTSyn_GetSynchronizedTimeBaseIdOfTimeDomain(timeDomainIdx);
#  endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Verify that Pdelay request was received on an active Pdelay responder port. */
  if (EthTSyn_Util_IsPdelayResponder(PortIdx) == TRUE)
  {
    /* #20 Pdelay responder is enabled -> continue message processing. */
    const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
    const EthTSyn_PdelayResponderIdxOfPdelayConfigType pDelayResponderIdx =
      EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pDelayCfgIdx);
    const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pDelayRespSmIdx =
      EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pDelayResponderIdx);
    ETHTSYN_CONSTP2VAR(EthTSyn_PdelayRespSmType) pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);

    /* #30 Get the ingress timestamp. */
    pDelayRespSmPtr->PdelayReq.IngressTimestampMgmt.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_NOT_AVAILABLE;  /* SBSW_ETHTSYN_CSL02_03 */
#  if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
      /* PRQA S 0310, 0311 2 */ /* MD_EthTSyn_0310_MsgStructRev, MD_EthTSyn_0311 */
    if (EthIf_GetIngressTimestamp(
      EthTSyn_Util_GetEthIfCtrlIdxOfPort(PortIdx), (ETHTSYN_P2VAR(Eth_DataType))ComMsgPtr,
      &pDelayRespSmPtr->PdelayReq.IngressTimestampMgmt.Timestamp, &timestampQual) == E_OK)                             /* SBSW_ETHTSYN_PASSING_API_POINTER */ /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */ /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */
    {
      if (timestampQual == ETH_VALID)
      {
        pDelayRespSmPtr->PdelayReq.IngressTimestampMgmt.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_AVAILABLE;  /* SBSW_ETHTSYN_CSL02_03 */
      }
    }
#  else
    if (StbM_GetCurrentTimeRaw(timeBaseId, &pDelayRequestReceivedTimestamp) == E_OK)                                   /* SBSW_ETHTSYN_REFERENCE_OF_VARIABLE */
    {
      pDelayRespSmPtr->PdelayReq.IngressTimestampMgmt.Timestamp =
        EthTSyn_Util_RawTimeToTimestamp(pDelayRequestReceivedTimestamp);                                               /* SBSW_ETHTSYN_CSL02_03 */
      pDelayRespSmPtr->PdelayReq.IngressTimestampMgmt.State = ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_AVAILABLE;    /* SBSW_ETHTSYN_CSL02_03 */
    }
#  endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

    ETHTSYN_ENTER_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    /* #40 Only proceed if ingress timestamp is available. */
    if (pDelayRespSmPtr->PdelayReq.IngressTimestampMgmt.State == ETHTSYN_TIMESTAMP_STATE_TIMESTAMP_REQUIRED_AVAILABLE)
    {
      /* #50 Store message attributes */

      /* Store Requesting source port identity */
      EthTSyn_SetClockIdentity(pDelayRespSmPtr->PdelayReq.SourcePortIdentity.ClockIdentity,
        ComMsgPtr->SourceClockIdentity);                                                                               /* SBSW_ETHTSYN_REFERENCE_OF_STRUCT_ELEMENT */ /* SBSW_ETHTSYN_REFERENCE_OF_POINTER_ELEMENT */
      pDelayRespSmPtr->PdelayReq.SourcePortIdentity.PortNumber = (EthTSyn_PortNumberType)
        EthTSyn_Ntohs(ComMsgPtr->SourcePortNumber);                                                                    /* SBSW_ETHTSYN_CSL02_03 */

      /* Store sequence id */
      pDelayRespSmPtr->PdelayReq.SequenceId = (uint16)EthTSyn_Ntohs(ComMsgPtr->SequenceId);                            /* SBSW_ETHTSYN_CSL02_03 */

      /* Change Pdelay response state machine state */
      pDelayRespSmPtr->State = ETHTSYN_S_PD_RESP_SM_TX_RESP;                                                           /* SBSW_ETHTSYN_CSL02_03 */
    }
    ETHTSYN_LEAVE_CRITICAL_SECTION_0(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }

} /* EthTSyn_Pdelay_ProcRcvdReqMsg() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */

/**********************************************************************************************************************
 *  END: PDELAY RESPONDER
 *********************************************************************************************************************/
#endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

#define ETHTSYN_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Justification for module-specific MISRA deviations:
 * see file EthTSyn.c
*/

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Pdelay_Int.c
 *********************************************************************************************************************/
