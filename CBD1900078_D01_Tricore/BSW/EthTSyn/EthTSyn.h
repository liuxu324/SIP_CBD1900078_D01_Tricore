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
 *  -------------------------------------------------------------------------------------------------------------------
 *         \file  EthTSyn.h
 *        \brief  EthTSyn module header file
 *
 *      \details  Contains all public function declarations and global definitions with respect to the EthTSyn module
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Jeroen Laverman               vislje        Vector Informatik
 *  Michael Seidenspinner         vissem        Vector Informatik
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2014-08-28  vislje  ESCAN00077557 created
 *            2014-09-23  vislje  -             Support for Software-Timestamping added
 *                                              Added Bugfixes / Features from SysService_Gptp802As[1.01.01]
 *            2014-09-24  vislje  -             Changed SyncSend[].TxConfirmationPending to sint8 
 *            2014-10-23  vislje  -             Organization of types
 *  01.00.01  2014-11-11  vislje  ESCAN00079492 Module causes DET in Eth-Module at initialization
 *                        vissem  ESCAN00079841 Added missing DET to MainFunction
 *                                -             Changed Module ID from 676 to 164
 *                                -             Added EthTSyn_SetTransmissionMode API
 *  01.00.02  2014-11-21  vissem  ESCAN00079837 Pdelay calculation is not valid if Pdelay responder response very fast
 *                                ESCAN00079849 Unexpected behavior of API EthTSyn_SetTransmissionMode
 *                                ESCAN00079853 Wrong RequestingPortNumber of PdelayRespFollowUp message undetected
 *            2015-01-07  vissem  ESCAN00080431 Compiler error: Wrong DET in EthTSyn_SetTransmissionMode 
 *  01.01.00  2015-02-17  vissem  ESCAN00081290 Timestamp is not sent correctly
 *            2015-02-18  vissem  ESCAN00080071 FEAT-1268: Add timestamp support (STBM) in software for EthTSyn
 *            2015-02-27  vissem  ESCAN00081498 Wrong Transceiver Link State/Enabled Flag after Re-Initialization of
 *                                              EthTSyn
 *            2015-03-03  vissem  ESCAN00081543 Negative Pdelay leads to AsCapable = false
 *            2015-03-24  vissem  ESCAN00081965 Incorrect TimestampType in EthTSyn_SetGlobalTime 
 *  01.01.01  2015-04-22  vissem  ESCAN00082125 Code Clean-Up and correction of issues found by review
 *  01.01.02  2015-07-07  vissem  ESCAN00083506 Compiler warning: Unused variable IngressTimestampRaw
 *                                ESCAN00083505 Compiler warning: Unused variable TimestampQuality
 *                                ESCAN00083508 Compiler warning: Declared but unused function
 *                                              EthTSyn_RawTimeToTimestamp
 *                                ESCAN00083507 Compiler warning: Declared but unused function:
 *                                              EthTSyn_ProcessSmSiteSyncSync
 *                                ESCAN00083497 Os Error Hook: Disabled Interrupts
 *                                ESCAN00083503 Synchronized time in Time Slave lags behind
 *            2015-07-08  vissem  ESCAN00083501 Time calculated by EthTsyn lags behind real time
 *                                ESCAN00083638 Compiler warning: EthTSyn - Possible loss of data due to implicit type
 *                                              conversion
 *                                ESCAN00084291 Compiler error: C2440: 'function' : cannot convert from
 *                                              'EthTSyn_GlobalTimestampType' to 'Eth_TimeStampType'
 *  01.02.00  2015-07-09  vissem  ESCAN00083859 Adopt Type of DataPtr in EthTSyn_RxIndication
 *                                ESCAN00083403 StbM_TimeStampRawType is not compatible to AR 4.2.1
 *            2015-07-22  vissem  ESCAN00084123 Removed AUTOSAR Version filter
 *  01.02.01  2015-08-14  vissem  ESCAN00084533 Calculation of RateRatio is incorrect
 *  02.00.00  2015-09-01  vissem  ESCAN00085374 FEAT-1529: Support Ethernet Switches for Ethernet Time Sync
 *                                ESCAN00085671 FEAT-1555: Ethernet Stack Bugfixing
 *            2015-10-01  vissem  ESCAN00085562 Invalid Pointer passed to EthIf_GetIngressTimestamp
 *            2015-10-12  vissem  ESCAN00085796 Valid PDelay_Resp_FollowUp is discarded
 *            2015-10-14  vissem  ESCAN00085769 EthTSyn issues a DET error if a gPTP frame is received on a network/VLAN
 *                                              on which EthTSyn itself is not active
 *                        vissem  ESCAN00084129 Allow the use of always AsCapable
 *                        vissem  ESCAN00085186 AUTOSAR 4.2.2 API adoptions
 *                        vissem  ESCAN00085629 Incompatible Timestamp types
 *  02.00.01  2016-01-26  vissem  ESCAN00087452 FollowUp-CorrectionField is not taken into account at the
 *                                              synchronization of a Time-Slave
 *  02.00.02  2016-02-19  vissem  ESCAN00088420 Review Integration
 *  02.01.00  2016-04-01  vissem  ESCAN00087687 FEAT-1691: EthTSyn shall support RateCorrection as OffsetCorrection
 *                                              and/or FrequencyRateCorrection below and above SynchronizationThreshold
 *                                ESCAN00084951 Added support of RateRatio for SW-Timestamping
 *                                ESCAN00087691 FEAT-1689: Each Time Communication Port shall be able to support
 *                                              Time Master & Time Slave functionality in parallel
 *                                ESCAN00088535 Time slave does not synchronize to the time master without former
 *                                              Announce message
 *                                ESCAN00086975 EthTSyn does not release TxBuffers if the transmission failed
 *                                ESCAN00088539 In a Time-Aware-Bridge the modification of the SourcePortIdenty is now
 *                                              optional
 *                                ESCAN00088655 EthTSyn_Cbk_TrcvLinkStateChg renamed to EthTSyn_TrcvLinkStateChg 
 *                                              (according to AUTOSAR 4.2.2)
 *                                ESCAN00088877 StbM_SetGlobalTime() is called instead of StbM_BusSetGlobalTime()
 *                                ESCAN00088493 FEAT-1694: Time Gateway shall be supported and EthTSyn shall support
 *                                              Boundary Clock on each Time Master Port
 *                                ESCAN00088660 Added SourcePortIdentity check for Sync/FollowUp messages received
 *                                              by a slave port
 *                                ESCAN00087695 FEAT-1201: Release of FEAT-971 ETH only
 *                                              (Time Sync over Ethernet module development) [AR4-954]
 *  02.02.00  2016-05-13  vissem  ESCAN00089687 FEAT-1987: Support of flexible Pdelay configuration
 *  02.02.01  2016-06-24  vissem  ESCAN00090251 Synchronization might be erroneous if corrective action RATE_RATIO is
 *                                              used
 *  03.00.00  2016-11-25  vissem  ESCAN00091272 Compiler error: #154: expression must have struct or union type
 *                                FEATC-248     FEAT-1998: Support of HW Time Stamping for Switch for EthTSyn
 *                                              (SysService_AsrTSynEth)
 *                                ESCAN00091957 Inconsistent use of the configuration parameter
 *                                              EthTSynGlobalTimeFollowUpTimeout
 *                                ESCAN00092113 Added support of the configuration parameter
 *                                              EthTSynTimeHardwareCorrectionThreshold
 *                                ESCAN00091972 Missing comparison of the source port identity for
 *                                              received Sync/FollowUp
 *  03.00.01  2016-11-29  vissem  ESCAN00093066 Used EthTSyn_TimediffType is too small when HW-Timestamping is active
 *                                ESCAN00093137 Using RateRatio correction in conjunction if HW-Timestamping can cause
 *                                              an Os TickTime error
 *                                ESCAN00093131 EthIf_GetIngressTimestamp is called in invalid context
 *                                ESCAN00093296 DET may occur on transmission of FollowUp message or buffer data is
 *                                              overwritten
 *                                ESCAN00093361 DET may occur on transmission of Announce message or buffer data is
 *                                              overwritten
 *                                ESCAN00093326 Message buffers with invalid Switch Mgmt info are not released
 *                                ESCAN00093325 Received message with invalid switch information might not be dropped
 *                                ESCAN00093248 DET ETHTSYN_SWT_MGMT_E_NO_MSG_AVAILABLE is issued when
 *                                              EthTSyn_SwitchMgmtInfoIndication is called after a message was
 *                                              discarded by the EthTSyn
 *                                ESCAN00091834 Call of the OS-API GetCounterValue() during disabled interrupts
 *                                ESCAN00093366 Compiler error: Syntax error
 *                                ESCAN00093411 ResponseOriginTimestamp is always 0 after first Pdelay message flow
 *                                ESCAN00093384 Compiler error: EthIf_SwitchEnableEgressTimestamp declared implicitly
 *                                ESCAN00093247 Reception of Announce leads to DET ETHTSYN_E_MSG_LENGTH
 *                                ESCAN00093327 Sync receive Timeout is supervised although Grandmaster Capable is
 *                                              disabled
 *  03.00.02  2017-01-24  vissem  ESCAN00093708 Precision of the RateRatio is insufficient when HW-Timestamping is used
 *  04.00.00  2017-03-31  vissem  ESCAN00093838 Misalignment exception during reception of a frame with odd length on
 *                                              RH850/V850 platform
 *                                ESCAN00093937 Message handling with enabled Switch Timestamping not working properly
 *                                FEATC-383     FEAT-2279: Time Synchronization acc. AR 4.3 for EthTSyn
 *  04.00.01  2017-04-18  vissem  ESCAN00094545 CrcTime1 value of the Time Secured SubTlv is invalid when SequenceId is
 *                                              included
 *                                ESCAN00094780 FollowUp IEEE Information Tlv invalid organization Id
 *  04.00.02  2017-05-03  vissem  ESCAN00094784 Compiler error: Multiple errors (e.g. undeclared identifier) with
 *                                              Switch Mgmt and Rx Announce support
 *                                ESCAN00094847 StbM APIs called with disabled interrupts
 *                                ESCAN00094973 Missing observation of EthTSynPdelayRespAndRespFollowUpTimeout
 *  05.00.00  2017-07-07  vissem  STORYC-1213   Global Time Precision Measurement Support
 *                                STORYC-113    Immediate Time Synchronization (event based SYNC in parallel to the
 *                                              regular cycle based SYNC)
 *  05.01.00  2017-07-26  vissem  ESCAN00095964 Time Base Sync for slave ports: Follow up timeout always exceeds if
 *                                              follow up timeout is disabled
 *                                ESCAN00095802 Compiler warning: Multiple warnings
 *  06.00.00  2017-10-27  vissem  STORYC-411    FEAT-2463,S-445 [SAFE] SafeBSW for EthTSyn (ASIL B), S1ComStackLib
 *                                ESCAN00096626 EthTSyn expects uint8* as return value of
 *                                              StbM_GetTimeBaseUpdateCounter()
 *                                ESCAN00096710 Message handling with enabled Switch Timestamping not working properly
 *                                ESCAN00096825 Linker error: Unresolved external symbol (EthTSyn_ProcessSmPdelayResp)
 *                                ESCAN00096818 Possible index out of bounds access
 *                                STORYC-119    AR4.3 extensions not covered by separate story
 *  06.01.00  2017-11-17  vissem  STORYC-410    FEAT-2463,S-444 [SAFE] SafeBSW for EthTSyn (ASIL B), S1 RevHlp
 *                                STORYC-3211   SysService_AsrTSynEth: Additional code and generator refactoring
 *                                ESCAN00097557 Compiler error: Redeclared types
 *            2017-12-08  vissem  ESCAN00097679 On message transmission, the byte order of the 'Flags' field does not
 *                                              match IEEE802.1As
 *            2017-12-12  vissem  ESCAN00097716 Possible memory access violation (read) because of not checking length
 *                                              of AUTOSAR TLV
 *            2018-01-11  vissem  ESCAN00097931 PdelayRequestReceivedTimestamp/PdelayResponseOriginTimestamp might
 *                                              contain a nanoseconds value greater than 999999999ns
 *                                ESCAN00097934 Possible wraparound of StbM raw timestamp remains undetected
 *            2018-01-29  vissem  STORYC-414    FEAT-2463,S-448 [SAFE] SafeBSW for EthTSyn (ASIL B), S1Test100
 *            2018-02-27  vissem  ESCAN00098324 EthTSyn transmits messages (Pdelay_Req) although TxMode is set to
 *                                              ETHTSYN_TX_OFF
 *            2018-03-08  vissem  ESCAN00098608 TwoStepFlag is set to TRUE in all message types and not just in Sync
 *                                              and Pdelay_Resp message
 *  06.02.00  2018-04-11  vissem  STORYC-4963   SysService_AsrTSynEth: Rework of CDD
 *            2018-04-19  vissem  STORYC-5002   Support time base specific time difference calculation acc. ASR4.3.1
 *  06.02.01  2018-05-02  vissem  ESCAN00099268 Invalid Timestamp might be used for calculation of SyncRefTime
 *            2018-08-16  vissem  ESCAN00099722 BETA version - the BSW module is in BETA state
 *  07.00.00  2018-09-18  vissem  ESCAN00098852 LogMessageInterval of transmitted Sync/FollowUp/Announce message is
 *                                              always 0.
 *            2018-09-19  vissem  ESCAN00098444 EthTSyn Master transmits Sync/FollowUp messages although the
 *                                              Global_Time_Base bit is not set
 *            2018-11-16  vissem  STORYC-6413   [AVB] Implementation of 802.1Qbv extensions for EthTSyn
 *                                ESCAN00101348 Time Master might transmit a too new PreciseOriginTimestamp
 *********************************************************************************************************************/


#if !defined(ETHTSYN_H)
# define ETHTSYN_H


/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
/* PRQA S 0857 MACRO_LIMIT */ /* MD_MSR_1.1_857 */
# include "EthTSyn_Cbk.h"
# include "EthTSyn_Lcfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* vendor and module identification */
# define ETHTSYN_VENDOR_ID                             (30u)
# define ETHTSYN_MODULE_ID                             (164u)
# define ETHTSYN_INSTANCE_ID                           (0U)

/* AUTOSAR Software specification version information */
# define ETHTSYN_AR_RELEASE_MAJOR_VERSION              (0x04u)
# define ETHTSYN_AR_RELEASE_MINOR_VERSION              (0x03u)
# define ETHTSYN_AR_RELEASE_REVISION_VERSION           (0x00u)

/* ----- Component version information (decimal version of ALM implementation package) ----- */
# define ETHTSYN_SW_MAJOR_VERSION                      (7u)
# define ETHTSYN_SW_MINOR_VERSION                      (0u)
# define ETHTSYN_SW_PATCH_VERSION                      (0u)

/* ----- API service IDs ----- */
/* AR */
/*!< Service ID: EthTSyn_Init() */
# define ETHTSYN_SID_INIT                                          (0x01u)
/*!< Service ID: EthTSyn_GetVersionInfo() */
# define ETHTSYN_SID_GET_VERSION_INFO                              (0x02u)
/*!< Service ID: EthTSyn_SetTransmissionMode() */
# define ETHTSYN_SID_SET_TRANSMISSION_MODE                         (0x05u)
/*!< Service ID: EthTSyn_RxIndication() */
# define ETHTSYN_SID_RX_INDICATION                                 (0x06u)
/*!< Service ID: EthTSyn_TxConfirmation() */
# define ETHTSYN_SID_TX_CONFIRMATION                               (0x07u)
/*!< Service ID: EthTSyn_TrcvLinkStateChg() */
# define ETHTSYN_SID_TRCV_LINK_STATE_CHG                           (0x08u)
/*!< Service ID: EthTSyn_MainFunction() */
# define ETHTSYN_SID_MAIN_FUNCTION                                 (0x09u)
/*!< Service ID: EthTSyn_SwitchMgmtInfoIndication() */
# define ETHTSYN_SWT_MGMT_SID_SWITCH_MGMT_INFO_INDICATION          (0x0Au)
/*!< Service ID: EthTSyn_SwitchIngressTimeStampIndication() */
# define ETHTSYN_SWT_MGMT_SID_SWITCH_INGRESS_TIMESTAMP_INDICATION  (0x0Bu)
/*!< Service ID: EthTSyn_SwitchEgressTimeStampIndication() */
# define ETHTSYN_SWT_MGMT_SID_SWITCH_EGRESS_TIMESTAMP_INDICATION   (0x0Cu)

/* Non-AR */
/*!< Service ID: EthTSyn_UtilRx_SyncPortRoleCheckWithMasterSlaveConflictDetection() */
# define ETHTSYN_SID_SYNC_PORT_ROLE_CHECK_WITH_MS_CONFLICT_DETECT  (0x50u)


/* ----- Error codes ----- */
/* AR runtime errors */
/*!< Error code: Time Master Conflict */
# define ETHTSYN_E_TMCONFLICT                                      (0x01u)
/*!< Error code: Time Slave Conflict */
# define ETHTSYN_E_TSCONFLICT                                      (0x02u)

/* AR development errors */
/*!< Error code: API service used in un-initialized state */
# define ETHTSYN_E_NOT_INITIALIZED                                 (0x20u)
/*!< Error code: EthTSyn initialization failed */
# define ETHTSYN_E_INIT_FAILED                                     (0x21u)
/*!< Error code: API called with invalid controller index */
# define ETHTSYN_E_CTRL_IDX                                        (0x22u)
/*!< Error code: API called with invalid Pointer */
# define ETHTSYN_E_PARAM_POINTER                                   (0x23u)
/*!< Error code: API called with invalid parameter */
# define ETHTSYN_E_PARAM                                           (0x24u)

/* Non-AR */
/*!< no error occurred */
# define ETHTSYN_E_NO_ERROR                                        (0x00u)
/*!< Error code: Received message with an invalid Message length */
# define ETHTSYN_E_MSG_LENGTH                                      (0x30u)
/*!< Error code: Received message with an invalid Protocol Version */
# define ETHTSYN_E_PROTOCOL_VERSION                                (0x31u)
/*!< Error code: Received message with an invalid Message Type */
# define ETHTSYN_E_MSG_TYPE                                        (0x32u)
/*!< Error code: Received message with an invalid Frame Type */
# define ETHTSYN_E_FRAME_TYPE                                      (0x33u)
/*!< Error code: Received message with an invalid Domain Number */
# define ETHTSYN_E_DOMAIN_NUMBER                                   (0x34u)
/*!< Error code: RxIndication called for inactive controller */
# define ETHTSYN_E_TRCV_DOWN                                       (0x35u)
/*!< Error code: No matching EthTSyn port found */
# define ETHTSYN_E_NO_PORT_FOUND                                   (0x36u)
/*!< Error code: Invalid Ethernet buffer alignment */
# define ETHTSYN_E_ETH_BUFFER_ALIGNMENT                            (0x37u)
/*!< Error Code: No free message buffer available */
# define ETHTSYN_SWT_MGMT_E_MSG_BUFFER_OVERFLOW                    (0x50u)
/*!< Error Code: Payload to big for the message buffer */
# define ETHTSYN_SWT_MGMT_E_MSG_BUFFER_PAYLOAD_OVERFLOW            (0x51u)
/*!< Error Code: EthTSyn_SwitchInfoIndication called with no buffered message available */
# define ETHTSYN_SWT_MGMT_E_NO_MSG_AVAILABLE                       (0x52u)
/*!< Error code: Internal error occurred */
# define ETHTSYN_E_INTERNAL_ERROR                                  (0xFFu)

/* PRQA L:MACRO_LIMIT */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define ETHTSYN_START_SEC_CODE
# include "MemMap.h"

# if (ETHTSYN_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_GetVersionInfo
 *********************************************************************************************************************/
/*! \brief       Returns the version information.
 *  \details     EthTSyn_GetVersionInfo() returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]  VersionInfoPtr  Pointer to where to store the version information. Parameter must not be NULL.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace CREQ-107318
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_GetVersionInfo(
  ETHTSYN_P2VAR(Std_VersionInfoType) VersionInfoPtr);
# endif /* (ETHTSYN_VERSION_INFO_API == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_Init
 *********************************************************************************************************************/
/*! \brief        Initialization of the EthTSyn module.
 *  \details      Function initializes the module EthTSyn. It initializes all variables and sets the module state to
 *                initialized.
 *  \param[in]    CfgPtr   Pointer to configuration
 *  \pre          The function EthTSyn_InitMemory() must be called first
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \trace CREQ-107316
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Init(
  P2CONST(EthTSyn_ConfigType, AUTOMATIC, ETHTSYN_INIT_DATA) CfgPtr);

/**********************************************************************************************************************
 *  EthTSyn_InitMemory
 *********************************************************************************************************************/
/*! \brief       Memory initialization of the EthTSyn module.
 *  \details     Service to initialize module global variables at power up. This function initializes the variables
 *               in *_INIT_* sections. Used in case they are not initialized by the startup code.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace CREQ-107316
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_InitMemory(void);

/**********************************************************************************************************************
 *  EthTSyn_SetTransmissionMode
 *********************************************************************************************************************/
/*! \brief       Set the EthTSyn transmission mode.
 *  \details     This API is used to turn on and off the TX capabilities of the EthTSyn.
 *  \param[in]   CtrlIdx      EthIf controller index
 *  \param[in]   Mode         Mode that shall be applied:
 *                            ETHTSYN_TX_OFF - turn of EthTSyn Tx capability
 *                            ETHTSYN_TX_ON - turn on EthTSyn Tx capability
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace CREQ-126709
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_SetTransmissionMode(
    uint8                        CtrlIdx,
    EthTSyn_TransmissionModeType Mode);

/**********************************************************************************************************************
 *  EthTSyn_MainFunction
 *********************************************************************************************************************/
/*! \brief       EthTSyn Main Function.
 *  \details     Main Function to handle cyclic tasks of the EthTSyn module.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
/* Function declaration is provided by SchM */

# define ETHTSYN_STOP_SEC_CODE
# include "MemMap.h"

/*!
 * \exclusivearea ETHTSYN_EXCLUSIVE_AREA_0
 * Ensures consistency of global RAM variables.
 * \protects All affected global RAM variables.
 * \usedin EthTSyn_MasterTx_TxSyncMsg, EthTSyn_MasterTx_TxFollowUpMsg, EthTSyn_MasterTx_IsFollowUpTxReady,
 *         EthTSyn_Master_TxAnnounceMsg, EthTSyn_Master_HandleCyclicTasks, EthTSyn_Master_SyncSendSm_SendSync,
 *         EthTSyn_Master_SyncSendSm_SendFup,
 *         EthTSyn_Pdelay_TxPdelayReqMsg, EthTSyn_Pdelay_TxPdelayRespMsg, EthTSyn_Pdelay_TxPdelayRespFupMsg,
 *         EthTSyn_Pdelay_CheckForPdelayRespTimeout, EthTSyn_Pdelay_ProcSmPdResp,
 *         EthTSyn_Pdelay_HandleCyclicTasks, EthTSyn_Pdelay_ProcRcvdReqMsg,
 *         EthTSyn_Pdelay_ProcRcvdRespMsg, EthTSyn_Pdelay_ProcRcvdRespFupMsg,
 *         EthTSyn_Slave_ProcessSmSyncReceive, EthTSyn_Slave_HandleCyclicTasks, EthTSyn_SlaveRx_ProcRcvdSyncMsg,
 *         EthTSyn_Slave_ProcRcvdAnnounceMsg, EthTSyn_EndStation_Slave_ProcRcvdSyncMsg,
 *         EthTSyn_SwtMgmt_ProcRcvdPdReqMsg, EthTSyn_SwtMgmt_ProcRcvdPdRespMsg,
 *         EthTSyn_SwtMgmt_ProcRcvdPdRespFupMsg, EthTSyn_SwtMgmt_ReleaseMsgBuffer,
 *         EthTSyn_SwtMgmt_ProvideMsgBuffer
 * \exclude All functions provided by EthTSyn.
 * \length LONG depending on the API and the call graph.
 * \endexclusivearea
 */

#endif /* ETHTSYN_H */
/**********************************************************************************************************************
 *  END OF FILE: EthTSyn.h
 *********************************************************************************************************************/
