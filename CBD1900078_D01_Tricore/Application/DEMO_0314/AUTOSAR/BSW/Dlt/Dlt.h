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
 *         File:  Dlt.h
 *      Project:  Diagnostic Log and Trace
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  Implements partly the functionality of the AUTOSAR 4.x module DLT based on XCP.
 *
 *
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Patrick Markl                  visml        Vector Informatik GmbH
 *  Alexander Zeeb                 viazb        Vector Informatik GmbH
 *  Oliver Reineke                 visore       Vector Informatik GmbH
 *  David Zentner                  viszda       Vector Informatik GmbH
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id       Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2011-05-12  visml   ESCAN00050129   Creation
 *  01.02.00  2013-03-26  visml   ESCAN00065961   Added DLT_APPL_VAR and DLT_PBCFG     
 *                        visml   ESCAN00065958   Added DLT_XCP_DET_EVENT to the template
 *                        visml   ESCAN00066198   Added default XCP event to A2L file
 *  01.02.01  2013-05-21  visazb  ESCAN00067468   Corrected vesion mismatch
 *  01.03.00  2013-07-02  visore  ESCAN00068516   Compiler warning: parameter 'ConfigPtr' unused in function 'Dlt_Init'
 *                        visore  ESCAN00068517   The DET service and error IDs are not compliant to the AUTOSAR4 specification
 *                        visore  ESCAN00068518   The MISRA justifications are not implemented according WI_MISRAC2004_PES.pdf
 *                        visore  ESCAN00068274   AR4-292: Reporting of DET and DEM errors via DLT
 *                        visore  ESCAN00068519   Signature of Dlt_DetForwardErrorTrace() is not compliant to AUTOSAR4
 *                        visore  ESCAN00070450   No changes here
 *                        visore  ESCAN00070451   No changes here
 *  01.03.01  2013-11-20  visore  ESCAN00071890   No changes here
 *  01.03.02  2014-01-20  visore  ESCAN00072716   Improve DLT include structure
 *  01.03.03  2014-05-21  visore  ESCAN00074824   No changes here
 *  01.05.00  2014-02-25  viszda  ESCAN00081343   FEAT-1311: DLT with AUTOSAR functionality and DLT Transport layer
 *            2015-03-17  viszda  ESCAN00081868   No changes here
 *  01.06.00  2015-04-22  viszda  ESCAN00082261   FEAT-1312: Continue DLT development with AUTOSAR functionality and DLT Transport layer (based on FEAT-1311)
 *                        viszda  ESCAN00082468   Compiler error: error C2065: 'xyz' : undeclared identifier
 *                        viszda  ESCAN00082469   Compiler warning: warning C4244, warning C4101, warning C4189, warning C4100
 *                        viszda  ESCAN00082472   Missing filters, compiler abstractions and exclusive areas
 *                        viszda  ESCAN00082473   Reduce code redundancies and code complexity due to FEAT-1311
 *                        viszda  ESCAN00082474   Change erroneous compiler abstractions and use the correct initialization for global variables
 *                        viszda  ESCAN00083946   No changes here
 *  01.06.01  2015-12-17  viszda  ESCAN00087203   No changes here
 *                        viszda  ESCAN00087212   Wrong DLT module ID
 *  01.07.00  2015-02-01  viszda  ESCAN00087978   Correction of version number in DltCom messages
 *            2016-02-26  viszda  ESCAN00088121   Product release of ASR DLT
 *  01.07.01  2016-06-21  viszda  ESCAN00090043   Get the socket connection state via API
 *            2016-07-25  viszda  ESCAN00091129   Valid DEM Event forwarded to DLT triggers DET Error
 *  01.07.02  2016-11-18  viszda  ESCAN00092787   Control messages from Dlt client are rejected and no response is send.
 *                        viszda  ESCAN00081639   Correction of formal issues
 *                        viszda  ESCAN00092560   Compiler error: The include file 'Det.h' cannot be opened
 *            2016-11-22  viszda  ESCAN00092936   Reduce Stack consumption of Dlt
 *  01.07.03  2018-03-13  viszda  ESCAN00098621   Loss of DLT log data after socket reconnect
 *            2018-03-14  viszda  ESCAN00098730   DLT log message loss if a control request message is received by DLT
 *  01.07.04  2018-05-24  viszda  ESCAN00097255   DLT (XCP) forwards DET errors to uninitialized XCP
 *********************************************************************************************************************/

#if !defined(DLT_H)
# define DLT_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "Dlt_Types.h"
# include "SchM_Dlt.h"

# include "Dem.h" /* needed for Dem_EventIdType */


/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* vendor and module identification */
# define DLT_VENDOR_ID                       (30u)
# define DLT_MODULE_ID                       (55u) /* ESCAN00087212 */

/* AUTOSAR Software specification version information */
# define DLT_AR_RELEASE_MAJOR_VERSION        (4u)
# define DLT_AR_RELEASE_MINOR_VERSION        (0u)
# define DLT_AR_RELEASE_REVISION_VERSION     (3u)

/* Component version information (decimal version of ALM implementation package) */
#define DLT_SW_MAJOR_VERSION                 (1u)
#define DLT_SW_MINOR_VERSION                 (7u)
#define DLT_SW_PATCH_VERSION                 (4u)

# define DLT_INSTANCE_ID_DET                 (0x00u)

/* API service IDs */
# define DLT_API_ID_INIT                     ((uint8)0x01u) /*!< ASR4.0 Dlt_Init() service ID [Dlt239]. */
# define DLT_API_ID_GETVERSIONINFO           ((uint8)0x02u) /*!< ASR4.0 Dlt_GetVersionInfo() service ID [Dlt271]. */
# define DLT_API_ID_SENDLOGMESSAGE           ((uint8)0x03u) /*!< ASR4.0 Dlt_SendLogMessage() service ID [Dlt241]. */
# define DLT_API_ID_SENDTRACEMESSAGE         ((uint8)0x04u) /*!< ASR4.0 Dlt_SendTraceMessage() service ID [Dlt243]. */
# define DLT_API_ID_REGISTERCONTEXT          ((uint8)0x05u) /*!< ASR4.0 Dlt_RegisterContext() service ID [Dlt245]. */
# define DLT_API_ID_DETFORWARDERRORTRACE     ((uint8)0x07u) /*!< ASR4.0 Dlt_DetForwardErrorTrace() service ID [Dlt432]. */
# define DLT_API_ID_COMRXINDICATION          ((uint8)0x0Fu) /*!< ASR4.0 Dlt_ComRxIndication() service ID [Dlt272]. */
# define DLT_API_ID_COMTXCONFIRMATION        ((uint8)0x10u) /*!< ASR4.0 Dlt_ComTxConfirmation() service ID [Dlt273]. */
# define DLT_API_ID_SETLOGLEVEL              ((uint8)0x11u) /*!< ASR4.0 Dlt_SetLogLevel() service ID [Dlt252]. */
# define DLT_API_ID_SETTRACESTATUS           ((uint8)0x12u) /*!< ASR4.0 Dlt_SetTraceStatus() service ID [Dlt254]. */
# define DLT_API_ID_SETVERBOSEMODE           ((uint8)0x13u) /*!< ASR4.0 Dlt_SetverboseMode() service ID [Dlt256]. */
# define DLT_API_ID_DEMTRIGGERONEVENTSTATUS  ((uint8)0x15u) /*!< ASR4.0 Dlt_DemTriggerOnEventStatus() service ID [Dlt470]. */
# define DLT_API_ID_MAINFUNCTION             ((uint8)0x50u) /*!< MSR4.0 Dlt_MainFunction() service ID. */
# define DLT_API_ID_SETSTATE                 ((uint8)0x51u) /*!< MSR4.0 Dlt_SetState() service ID. */
# define DLT_API_ID_GETSTATE                 ((uint8)0x52u) /*!< MSR4.0 Dlt_GetState() service ID. */

/* Error codes */
# define DLT_E_NO_ERROR                      ((uint8)0x00u) /*!< Error code: No error. */
# define DLT_E_WRONG_PARAMETERS              ((uint8)0x01u) /*!< Error code: [SWS_Dlt_00447]. */
# define DLT_E_ERROR_IN_PROV_SERVICE         ((uint8)0x02u) /*!< Error code: [SWS_Dlt_00447]. */
# define DLT_E_COM_FAILURE                   ((uint8)0x03u) /*!< Error code: [SWS_Dlt_00447]. */
# define DLT_E_ERROR_TO_MANY_CONTEXT         ((uint8)0x04u) /*!< Error code: [SWS_Dlt_00447]. */
# define DLT_E_MSG_LOOSE                     ((uint8)0x05u) /*!< Error code: [SWS_Dlt_00447]. */
# define DLT_E_PARAM_POINTER                 ((uint8)0x06u) /*!< Error code: [SWS_Dlt_00447]. */
# define DLT_E_INIT_FAILED                   ((uint8)0x07u) /*!< Error code: [SWS_Dlt_00447]. */
# define DLT_E_UNINITIALIZED                 ((uint8)0x08u) /*!< Error code: DLT is not initialized. */
# define DLT_E_INVALID_STATE                 ((uint8)0x09u) /*!< Error code: DLT is in an invalid state. */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

 /* Check the version of Dlt_Types.h */
# if (  (DLT_TYPES_MAJOR_VERSION != (1u)) \
     || (DLT_TYPES_MINOR_VERSION != (7u)) \
     || (DLT_TYPES_PATCH_VERSION != (4u)) )
#  error "Version numbers of Dlt_Types.h are inconsistent"
# endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 FUNCTIONLIKEMACRO */ /* MD_MSR_19.7 */

# if !defined(DLT_DUMMY_STATEMENT)     /* COV_DLT_MSR_COMPATIBILITY */
#  if defined (DLT_USE_DUMMY_STATEMENT)  
# define DLT_DUMMY_STATEMENT(statement) ((void)(statement))
#  else
# define DLT_DUMMY_STATEMENT(statement)
#  endif
# endif

# if !defined(DLT_DUMMY_STATEMENT_CONST)     /* COV_DLT_MSR_COMPATIBILITY */
#  if defined (DLT_USE_DUMMY_STATEMENT_CONST)  
# define DLT_DUMMY_STATEMENT_CONST(statement) ((void)(statement))
#  else
# define DLT_DUMMY_STATEMENT_CONST(statement)
#  endif
# endif

#define DLT_IS_CONNECTION_ONLINE() ((boolean)FALSE)

/* PRQA L:FUNCTIONLIKEMACRO */ /* MD_MSR_19.7 */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define DLT_START_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


extern CONST(uint8, DLT_CONST)                     Dlt_ModuleTable[256];

#define DLT_STOP_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define DLT_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Variable is loaded with the last DET error code */
extern VAR(uint32, DLT_VAR_NOINIT)                 Dlt_DetErrorCode;

#define DLT_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define DLT_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# if defined (DLT_USE_COMLAYER_XCP) && (DLT_USE_COMLAYER_XCP == STD_ON) /* COV_DLT_FILTER_ASR_XCP */
/* Variable is loaded with DEM event status code. */
extern VAR(Dlt_DemEventStatusType, DLT_VAR_NOINIT) Dlt_DemEventStatus;

/* Variable is loaded with message ID of non-verbose message . */
extern VAR(Dlt_MessageIDType, DLT_VAR_NOINIT)      Dlt_NonVerboseMessageId;

#  if (DLT_USE_VERBOSE_MODE == STD_ON)
/* Buffer is loaded with payload of verbose message. */
extern VAR(uint8, DLT_VAR_NOINIT)                  Dlt_VerboseMessageData[DLT_MAX_MESSAGE_LENGTH];
#  endif /* (DLT_USE_VERBOSE_MODE == STD_ON) */
# endif /* defined (DLT_USE_COMLAYER_XCP) && (DLT_USE_COMLAYER_XCP == STD_ON) */

#define DLT_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define DLT_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  Dlt_InitMemory
**********************************************************************************************************************/
/*! \brief       Power-up memory initialization
 *  \details     Initializes component variables in *_INIT_* sections at power up.
 *  \pre         Module is uninitialized.
 *  \return      -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       CREQ-106553
 *  \note        Use this function in case these variables are not initialized by the startup code.
 *********************************************************************************************************************/
FUNC(void, DLT_CODE) Dlt_InitMemory(void);


/**********************************************************************************************************************
 *  Dlt_Init
**********************************************************************************************************************/
/*! \brief       Initializes component
 *  \details     Initializes all component variables and sets the component state to initialized.
 *  \param[in]   ConfigPtr        Component configuration structure
 *  \return      -
 *  \pre         Interrupts are disabled.
 *  \pre         Module is uninitialized.
 *  \pre         Dlt_InitMemory has been called unless Dlt_ModuleInitialized is initialized by start-up code.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       CREQ-106553
 *********************************************************************************************************************/
FUNC(void, DLT_CODE) Dlt_Init(P2CONST(Dlt_ConfigType, AUTOMATIC, DLT_PBCFG) ConfigPtr);

# if(DLT_VERSION_INFO_API == STD_ON)

/**********************************************************************************************************************
 *  Dlt_GetVersionInfo()
**********************************************************************************************************************/
/*! \brief       Returns the version information
 *  \details     Returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]  versioninfo      Pointer to where to store the version information. Parameter must not be NULL.
 *  \return      -
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-106554
 *********************************************************************************************************************/
FUNC(void, DLT_CODE) Dlt_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, DLT_APPL_VAR) VersionInfo);

# endif

/**********************************************************************************************************************
 *  Dlt_DetForwardErrorTrace()
**********************************************************************************************************************/
/*! \brief       Service to forward error reports from Det to Dlt.
 *  \details     Builds and sends a log message containing all passed data.
 *  \param[in]   ModuleId         Module ID of calling module.
 *  \param[in]   InstanceId       The identifier of the index based instance of a module.
 *  \param[in]   ApiId            ID of API service in which error is detected.
 *  \param[in]   ErrorId          ID of detected development error.
 *  \return      -
 *  \pre         -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, DLT_CODE) Dlt_DetForwardErrorTrace(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);


/**********************************************************************************************************************
 *  Dlt_DemTriggerOnEventStatus()
**********************************************************************************************************************/
/*! \brief       This service is provided by the Dem in order to call Dlt upon status changes.
 *  \details     Builds and sends a log message containing the passed data.
 *  \param[in]   EventId          Module ID of calling module.
 *  \param[in]   EventStatusOld   The identifier of the index based instance of a module.
 *  \param[in]   EventStatusNew   ID of API service in which error is detected.
 *  \return      -
 *  \pre         -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, DLT_CODE) Dlt_DemTriggerOnEventStatus(Dem_EventIdType EventId,
                                                 Dem_EventStatusExtendedType EventStatusOld,
                                                 Dem_EventStatusExtendedType EventStatusNew);


# if (DLT_DEM_EVENT_FILTERING_ENABLED == STD_ON)

/**********************************************************************************************************************
 *  Appl_DltDemEventFilterCbk()
**********************************************************************************************************************/
/*! \brief       Checks if DEM event status has changed.
 *  \details     Must be implemented by user and should be used to compare old event status and new event status. The
 *               result should be returned.
 *  \param[in]   EventId          Identification of an Event by assigned event number. The Event number is configured
 *                                in the Dem:
*                                   Min.: 1 (0: Indication of no Event or Failure).
*                                   Max.: Result of configuration of Event Numbers in Dem (Max is either 255 or 65535).
 *  \param[in]   EventStatusOld   Extended event status before change.
 *  \param[in]   EventStatusNew   Detected / reported of event status.
 *  \return      TRUE             The DEM event has passed the filter (log message will be generated by the DLT).
 *  \return      FALSE            The DEM event has not passed the filter (no log message will be generated).
 *  \pre         -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
/* UREQ00041311 */
FUNC(boolean, DLT_CODE) Appl_DltDemEventFilterCbk(Dem_EventIdType EventId,
                                                  Dem_EventStatusExtendedType EventStatusOld,
                                                  Dem_EventStatusExtendedType EventStatusNew);

# endif /* (DLT_DEM_EVENT_FILTERING_ENABLED == STD_ON) */

/**********************************************************************************************************************
 *  Dlt_MainFunction()
**********************************************************************************************************************/
/*! \fn          void Dlt_MainFunction(void)
 *  \brief       Checks periodically the Dlt status.
 *  \details     Handles cyclically the state machine(s).
 *  \param[in]   -
 *  \return      -
 *  \pre         -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       CREQ-106560
 *********************************************************************************************************************/
/* FUNC(void, DLT_CODE) Dlt_MainFunction(void);
*/


#define DLT_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif

/**********************************************************************************************************************
 *  END OF FILE: Dlt.h
 *********************************************************************************************************************/
