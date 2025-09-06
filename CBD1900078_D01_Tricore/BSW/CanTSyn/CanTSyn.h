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
/*!        \file  CanTSyn.h
 *        \brief  Vector AUTOSAR CanTSyn header file
 *
 *      \details  This is the main header file of the Vector AUTOSAR module CanTSyn.

 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Stephanie Schaaf              visssf        Vector Informatik GmbH
 *  Martin Nonnenmann             vismno        Vector Informatik GmbH
 *  Thilo Rachlitz                vistra        Vector Informatik GmbH
 *  Charu Pathni                  viscpi        Vector Informatik GmbH 
 *  Bernd Sigle                   vissi         Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2014-09-18  visssf  ESCAN00077542 AR4-664: Provide module CanTSyn for global time synchronization over CAN
 *  01.01.00  2014-12-02  visssf  ESCAN00079947 Time Master or Slave uses wrong Time Domain Id
 *            2014-12-02  visssf  ESCAN00079949 FEAT-971: Complete development of module CanTSyn
 *  01.02.00  2015-07-14  visssf  ESCAN00083404 StbM_TimeStampRawType is not compatible to AR 4.2.1
 *  02.00.00  2015-09-22  visssf  -             Updated Generator Version to 2.0 (Java 8 and R14 CFG5 Breaking Changes)
 *  02.01.00  2016-02-26  visssf  ESCAN00088577 FEAT-1694: Support multiple masters per Time Domain
 *            2016-03-15  visssf  ESCAN00088703 Wrong calculation and validation of Sequence Counter
 *            2016-03-15  visssf  ESCAN00088925 Missing interrupt locks
 *            2016-03-21  visssf  ESCAN00087327 MISRA deviation: MISRA-C:2004 Rules 1.1, 5.6, 14.3, 19.10, 19.7 and HIS Metrics
 *  02.01.01  2017-01-11  visssf  ESCAN00090442 Wrong CRC calculation and validation
 *  03.00.00  2017-04-11  visssf  STORYC-250    Update BSWMD Files to AR 4.3
 *  03.01.00  2017-05-10  visssf  STORYC-128    Tx state machine shall support Multiple Time Domains
 *  03.02.00  2017-06-19  vismno  STORYC-114    Debounce Time introduction
 *                                ESCAN00095191 Wrong validation of Sequence Counter after overflow
 *            2017-06-22  visssf  STORYC-1207   Global Time Precision Measurement Support
 *  03.03.00  2017-07-26  vistra  STORYC-111    Immediate Time Synchronization
 *  03.04.00  2017-09-21  viscpi  STORYC-117    STORY-130: AR4.3 extensions not covered by separate story
 *            2017-10-11  vistra  STORYC-1735   STORY-1727: Support AR4.3 message types and for backward compatibility also AR 4.2 messages types
 *  03.05.00  2017-11-29  viscpi  STORYC-2519   STORY-2567: Usage of ComStackLib for CanTSyn
 *            2018-03-01  visssf  ESCAN00098531 Transmit confirmation not accepted due to wrong master state
 *            2018-03-14  visssf  ESCAN00097094 Improve accuracy of time synchronization
 *            2018-04-05  visssf  ESCAN00098988 StbM API called with disabled interrupts
 *  03.06.00  2018-04-24  vissi   STORYC-5073   STORY-4927: Support Measurement (MC Data)
 *            2018-05-04  visssf  STORYC-5001   STORY-4846: Support time base specific time difference calculation acc. ASR4.3.1
 *            2018-05-15  vissi   STORYC-5069   STORY-4926: Improve accuracy of the global time by rework of exclusive areas around OS API calls
 *  03.06.01  2018-08-27  vistra  ESCAN00100605 Compiler warning: several GCC specific warnings in CanTSyn.c
 *            2018-08-29  visssf  ESCAN00100557 Wrong evaluation of user data by the time slave
 *  03.07.00  2018-09-19  vissi   STORYC-5089   STORY-4943: MISRA-C2012: SysService_AsrTSynCan
 *            2018-12-06  vistra  ESCAN00101476 SGW bit is never set in FUP messages
 *  03.07.01  2019-02-22  vistra  ESCAN00101885 SC Jump Width checking shall be disabled after a timeout
 *            2019-03-11  vistra  ESCAN00101886 SYNC and FUP sequences and OFS and OFNS sequences might not be interrupted
 *********************************************************************************************************************/

#if !defined (CANTSYN_H)
# define CANTSYN_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "CanTSyn_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Vendor and module identification */
# define CANTSYN_VENDOR_ID                       (30u)
# define CANTSYN_MODULE_ID                       (0xA1u)

/* AUTOSAR Software specification version information */
# define CANTSYN_AR_RELEASE_MAJOR_VERSION        (0x04u)
# define CANTSYN_AR_RELEASE_MINOR_VERSION        (0x03u)
# define CANTSYN_AR_RELEASE_REVISION_VERSION     (0x01u)

/* ----- Component version information (decimal version of ALM implementation package) ----- */
# define CANTSYN_SW_MAJOR_VERSION                (3u)
# define CANTSYN_SW_MINOR_VERSION                (7u)
# define CANTSYN_SW_PATCH_VERSION                (1u)

# define CANTSYN_INSTANCE_ID_DET                 (0x00u)

/* ----- API service IDs ----- */
# define CANTSYN_SID_INIT                        (0x01u) /*!< Service ID: CanTSyn_Init() */
# define CANTSYN_SID_GET_VERSION_INFO            (0x02u) /*!< Service ID: CanTSyn_GetVersionInfo() */
# define CANTSYN_SID_SET_TRANSMISSION_MODE       (0x03u) /*!< Service ID: CanTSyn_SetTransmissionMode() */
# define CANTSYN_SID_RX_INDICATION               (0x42u) /*!< Service ID: CanTSyn_RxIndication() */
# define CANTSYN_SID_TX_CONFIRMATION             (0x40u) /*!< Service ID: CanTSyn_TxConfirmation() */
# define CANTSYN_SID_MAIN_FUNCTION               (0x06u) /*!< Service ID: CanTSyn_MainFunction() */

# define CANTSYN_SID_TIMESTAMP_PLUS_TIMESTAMPRAW (0xA1u) /*!< Service ID: CanTSyn_TimestampPlusTimestampRaw() */

/* ----- Error codes ----- */
# define CANTSYN_E_NO_ERROR                      (0x00u) /*!< used to check if no error occurred */
# define CANTSYN_E_INVALID_PDUID                 (0x01u) /*!< Error code: API service called with wrong PDU or SDU  */
# define CANTSYN_E_UNINIT                        (0x02u) /*!< Error code: API service used in un-initialized state */
# define CANTSYN_E_NOT_INITIALIZED               (0x02u) /*!< Error code: API service used in un-initialized state */ /* for compatibility until AR 4.3.0 */ 
# define CANTSYN_E_NULL_POINTER                  (0x03u) /*!< Error code: API service called with NULL_PTR as parameter  */
# define CANTSYN_E_INIT_FAILED                   (0x04u) /*!< Error code: API service called and initialization failed  */
# define CANTSYN_E_PARAM                         (0x05u) /*!< Error code: API service called with invalid parameter  */
# define CANTSYN_E_INV_CTRL_IDX                  (0x06u) /*!< Error code: API service called with invalid controller index  */

/* ----- Modes ----- */
# define CANTSYN_UNINIT                          (0x00u)
# define CANTSYN_INIT                            (0x01u)

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

# define CANTSYN_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  CanTSyn_InitMemory()
 *********************************************************************************************************************/
/*! \brief       Function for *_INIT_*-variable initialization
 *  \details     Service to initialize module global variables at power up. This function can be used to initialize the
 *               variables in *_INIT_* sections in case they are not initialized by the startup code.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE 
 *  \synchronous TRUE
**********************************************************************************************************************/
FUNC(void, CANTSYN_CODE) CanTSyn_InitMemory(void);

/**********************************************************************************************************************
 *  CanTSyn_Init()
 *********************************************************************************************************************/
/*! \brief       Initialization function
 *  \details     This function initializes the module CanTSyn. It initializes all variables and sets the module state to
 *               initialized.
 *  \param[in]   configPtr               Configuration structure for initializing the module.
 *  \pre         Interrupts are disabled and CanTSyn_InitMemory has been called if required.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        Specification of module initialization
 *********************************************************************************************************************/
FUNC(void, CANTSYN_CODE) CanTSyn_Init(P2CONST(CanTSyn_ConfigType, AUTOMATIC, CANTSYN_APPL_DATA) configPtr);

# if (CANTSYN_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  CanTSyn_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief       Returns the version information
 *  \details     CanTSyn_GetVersionInfo() returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]  versioninfo             Pointer to where to store the version information. Parameter must not be NULL.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, CANTSYN_CODE) CanTSyn_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CANTSYN_APPL_VAR) versioninfo);
# endif

/**********************************************************************************************************************
 *  CanTSyn_MainFunction()
 *********************************************************************************************************************/
/*! \brief       Main function
 *  \details     This function processes cyclic tasks of the CanTSyn module.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
/* The CanTSyn_MainFunction definition is localized in CanTSyn.c. The declaration is realized by SchM */

# if (CANTSYN_MASTERCONFIG == STD_ON)
/**********************************************************************************************************************
 *  CanTSyn_SetTransmissionMode()
 *********************************************************************************************************************/
/*! \brief       Set transmission mode
 *  \details     This function turns the TX capabilities of the CanTSyn on and off.
 *  \param[in]   CtrlIdx                 Index of the CAN channel.
 *  \param[in]   Mode                    Transmission on/off.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      CANTSYN_MASTERCONFIG
 *********************************************************************************************************************/
FUNC(void, CANTSYN_CODE) CanTSyn_SetTransmissionMode(uint8 CtrlIdx, CanTSyn_TransmissionModeType Mode);
# endif

# define CANTSYN_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*!
 *
 * \exclusivearea CANTSYN_EXCLUSIVE_AREA_0
 * Ensures consistency of global RAM variables.
 * \protects All affected global RAM variables.
 * \usedin CanTSyn_ProcessReceive, CanTSyn_HandleSync, CanTSyn_HandleFup, CanTSyn_ProcessSend, CanTSyn_TransmitSync,
           CanTSyn_TransmitFup, CanTSyn_PrepareAndSendFUPMsg, CanTSyn_MainFunction, CanTSyn_PrepareAndSendSync,
           CanTSyn_HandleFup, CanTSyn_CheckMessage
 * \exclude All functions provided by CanTSyn.
 * \length SHORT depending on the API and the call graph.
 * \endexclusivearea
 *
 */

#endif  /* CANTSYN_H */

/**********************************************************************************************************************
 *  END OF FILE: CanTSyn.h
 *********************************************************************************************************************/
