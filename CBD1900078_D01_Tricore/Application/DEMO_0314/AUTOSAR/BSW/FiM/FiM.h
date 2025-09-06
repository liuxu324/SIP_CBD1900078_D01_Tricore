/***********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2017 by Vector Informatik GmbH. All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  --------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/*!     \file      FiM.h
 *      \brief     Header for Autosar 4 module FiM
 *
 *      \details   Static header file for FiM. May not be changed by customer / generator
 *
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  --------------------------------------------------------------------------------------------------------------------
 *  Joachim Kalmbach              visjk         Vector Informatik GmbH
 *  Katrin  Thurow                visktw        Vector Informatik GmbH
 *  Thomas  Necker                vistne        Vector Informatik GmbH
 *  --------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  --------------------------------------------------------------------------------------------------------------------
 *            2012-08-22  visjk   ---           3.01.00: AR 3 FiM version that this module was originally based on
 *                        visktw  ---           ditto
 *  1.00.00   2012-10-11  vistne  ESCAN00061742 AR4-148: FiM AR4 Support
 *                        vistne  ESCAN00061816 AR4-220: Remove STATIC
 *  1.01.00   2013-03-15  vistne  ESCAN00063875 Add Offline Calibration Support
 *                        vistne  ESCAN00063883 FiM include hierarchy does not conform to AR standard
 *                        vistne  ESCAN00064191 Support Cyclic Event Evaluation
 *                        vistne  ESCAN00064193 Support of FiM_GetFunctionPendingStatus
 *  1.02.00   2013-06-28  vistne  ESCAN00067461 Include of Dem.h was moved to different file
 *                        vistne  ESCAN00067956 Support absence of RTE generated files
 *  2.00.00   2013-11-01  vistne  ESCAN00070055 Compiler error: FiM.c(XXX) : 'FiM_FidPendingCounter' : undeclared identifier
 *                        vistne  ESCAN00070532 Possible out of bounds access to EventIdTable
 *                        vistne  ESCAN00070624 New Binary Search Algorithm for EventIds
 *                        vistne  ESCAN00070687 New Direct Table Access for EventIds
 *  2.01.00   2014-03-07  vistne  ESCAN00071946 Harmonize usage of boolean and Boolean
 *                        vistne  ESCAN00072079 Pending status of FID is influenced by event even if corresponding
 *                                              event/FID link has invalid inhibition configuration
 *                        vistne  ESCAN00072092 AR4-580: FiM Inhibition Config Optimizations
 *                        vistne  ESCAN00072428 AR4-580: FiM Postbuild Loadable
 *  3.00.00   2014-10-31  vistne  ESCAN00078673 Introduce DET code FIM_E_INITIALIZATION_NOT_COMPLETED
 *                        vistne  ESCAN00078676 FiM_GetFunctionPermission and FiMGetFunctionPendingStatus return
 *                                              E_NOT_OK in all error cases
 *  3.01.00   2015-03-20  vistne  ESCAN00080166 Return value for FiM_DemTriggerOnEventStatus does not comply to
 *                                              AUTOSAR-Standard
 *                        vistne  ESCAN00080369 FiM_GetFunctionPermission and FiMGetFunctionPendingStatus do
 *                                              plausibility checks only if FIM_DEV_ERROR_DETECT is enabled
 *                        vistne  ESCAN00080605 Ignore events when Dem_GetEventStatus does not return E_OK
 *                        vistne  ESCAN00080284 FEAT-427: SafeBSW Step I
 *  4.00.00   2016-01-08  vistne  ESCAN00083200 Remove inclusion of v_ver.h
 *                        vistne  ESCAN00083639 Compiler warning: narrowing or signed-to-unsigned type conversion found
 *                        vistne  ESCAN00085144 FEAT-1527: SafeBSW Step 3
 *                        vistne  ESCAN00086406 Reduce number of entries into critical sections
 *  4.01.00   2016-07-27  vistne  ESCAN00089387 FEAT-1734: SafeBSW Step 5
 *  4.02.00   2016-11-18  vistne  FEATC-12      FEAT-1920: FiM - SafeBSW Step6
 *                        vistne  ESCAN00091090 Incorrect initialization status detection
 *                        vistne  ESCAN00091787 Removed Critical Sections in FiM_GetFunctionPermission and
 *                                              FiM_GetFunctionPendingStatus
 *  5.00.00   2017-10-27  vistne  STORY-12      Rework for AR 4.3 OnDemand Calculation - Beta, Component Only
 *                                STORY-2524    Rework for AR 4.3 OnDemand Calculation - Beta, DemIntegrated
 *  5.01.00   2017-12-22  vistne  STORY-2522    Rework for AR 4.3 OnDemand Calculation (incl. OBD) - Release
***********************************************************************************************************************/
#if !defined(FIM_H)
#define FIM_H


/***********************************************************************************************************************
 * INCLUDES
 **********************************************************************************************************************/

#include "FiM_Cfg.h"
#include "FiM_Types.h"
#include "FiM_Lcfg.h"
#include "FiM_PBcfg.h"


/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/

/* Vendor and module identification */
#define FIM_VENDOR_ID                               (30u) /* Vector Informatik GmbH */
#define FIM_MODULE_ID                               (11u) /* FIM */
/* AUTOSAR Software Specification Version Information - decimal encoding */
#define FIM_AR_RELEASE_MAJOR_VERSION                (4u)
#define FIM_AR_RELEASE_MINOR_VERSION                (0u)
#define FIM_AR_RELEASE_REVISION_VERSION             (3u)

/* ----- Component version information (decimal version of ALM implementation package) ----- */
#define FIM_SW_MAJOR_VERSION                        (0x05)/* decimal coded version number         */
#define FIM_SW_MINOR_VERSION                        (0x01)
#define FIM_SW_PATCH_VERSION                        (0x00)/* decimal coded release version number */

#define FIM_INSTANCE_ID_DET                         (0x00u)

/*! * \defgroup  FimDetSids API Service IDs for reporting errors to the DET
 * API Service IDs for reporting errors to the DET with Det_ReportError(FIM_MODULE_ID, FIM_INSTANCE_ID, ServiceId,
 * ErrorId)
 * \{ */
#define FIM_SID_FIM_INIT                            (0x00u) /*!< Service ID: FiM_Init() */
#define FIM_SID_FIM_GETFUNCTIONPERMISSION           (0x01u) /*!< Service ID: FiM_GetFunctionPermission() */
#define FIM_SID_FIM_DEMTRIGGERONMONITORSTATUS       (0x02u) /*!< Service ID: FiM_DemTriggerOnMonitorStatus() */
#define FIM_SID_FIM_DEMINIT                         (0x03u) /*!< Service ID: FiM_DemInit() */
#define FIM_SID_FIM_GETVERSIONINFO                  (0x04u) /*!< Service ID: FiM_GetVersionInfo() */
#define FIM_SID_FIM_MAINFUNCTION                    (0x05u) /*!< Service ID: FiM_MainFunction() */
/* Additional API Service IDs for reporting errors to the DET */
# if (FIM_FEATURE_OBD == STD_ON)
#  define FIM_SID_FIM_GETFUNCTIONPENDINGSTATUS      (0x80u) /*!< Service ID: FiM_GetFunctionPendingStatus() */
#  define FIM_SID_FIM_DEMTRIGGERONEVENTSTATUS       (0x82u) /*!< Service ID: FiM_DemTriggerOnEventStatus() */
#endif
/*! \} */

/*! * \defgroup  FimDetErrId ErrorIds for reporting errors to the DET
 * ErrorIds for reporting errors to the DET
 * \{ */
#define FIM_E_NO_ERROR                              (0x00u) /*!< used to check if no error occurred */
#define FIM_E_UNINIT                                (0x01u) /*!< API function called before the FiM module has been fully initialized (AR4.3) */
#define FIM_E_FID_OUT_OF_RANGE                      (0x02u) /*!< FiM_GetFunctionPermission/FiM_GetFunctionPendingStatus called with wrong FID (AR4.3) */
#define FIM_E_EVENTID_OUT_OF_RANGE                  (0x03u) /*!< Dem calls FiM with invalid EventId (AR4.3) */
#define FIM_E_PARAM_POINTER                         (0x04u) /*!< API is invoked with NULL pointer (AR4.3) */
#define FIM_E_INIT_FAILED                           (0x05u) /*!< Invalid configuration set selection (e.g.) (AR4.3) */
/* Additional ErrorIds for reporting errors to the DET */
/* none */
/*! \} */

/*! * \defgroup  IdxInhModTable Indexes for inhibition configuration.
 * Indexes for inhibition configuration.
 * \{ */
#define FIM_INHCODE_INVALID                         (0u)
#define FIM_INHCODE_LAST_FAILED                     (1u)
#define FIM_INHCODE_NOT_TESTED                      (2u)
#define FIM_INHCODE_TESTED                          (3u)
#define FIM_INHCODE_TESTED_AND_FAILED               (4u)
#define FIM_INHCODE_NOT_TESTED_OR_FAILED            (5u)
#define FIM_INHCODE_PENDING                         (6u)
#define FIM_INHCODE_NUMBER                          (7u)
/*! \} */

/*! Invalid DEM event id. */
#define FIM_DEM_EVENT_INVALID                       (0u)

/*! Minimum list length necessary to apply binary search algorithm. */
#if !defined FIM_BINSEARCH_MINLISTLENGTH                                                  /* COV_MSR_COMPATIBILITY TX */
# define FIM_BINSEARCH_MINLISTLENGTH                (5u)
#endif

#if (FIM_DATA_FIXED == STD_ON)
#  error "Invalid configuration: Calibration not supported anymore"
#endif

#if (FIM_CYCLIC_EVENT_EVALUATION == STD_ON)
#  error "Invalid configuration: FIM_CYCLIC_EVENT_EVALUATION not supported"
#endif


/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/
#define FIM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (FIM_CFG_VARIANT_POSTBUILD_LOADABLE == STD_ON)
extern P2CONST(FiM_ConfigType, FIM_VAR_NOINIT, FIM_INIT_DATA)  FiM_ConfigDataPtr;
#endif

#define FIM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */                                                          


/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

#define FIM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/***********************************************************************************************************************
 *  FiM_InitMemory()
 **********************************************************************************************************************/
/*! \brief                    Use this function to initialize static RAM variables.
 *                            - Extension to Autosar -  
 *  \details                  Use when the start-up code is not used to initialize RAM.
 *  \pre                      Module is uninitialized.
 *  \context                  TASK|ISR2
 *  \reentrant                TRUE
 *  \synchronous              TRUE
 *  \trace                    CREQ-103737
 **********************************************************************************************************************/
FUNC(void, FIM_CODE)            FiM_InitMemory(void);

/***********************************************************************************************************************
 *  FiM_Init()
 **********************************************************************************************************************/
/*! \brief                    Initializes FiM
 *
 *  \details                  This function shall be used during the startup phase of the ECU before
 *                            the DEM is initialized to setup the FIM's internal variables for operation.
 *                            The component state is set to pre-initialized if no error occurred.
 *                            The FiM is not yet ready for operation afterwards.
 *
 *  \param[in]  FiMConfigPtr  Root pointer to FiM's configuration.
 *
 *  \pre                      FiM_InitMemory has been called unless FiM_InitializationStatus is initialized by
 *                            start-up code.
 *  \context                  TASK
 *  \reentrant                FALSE
 *  \synchronous              TRUE
 *  \trace                    DSGN-FiM22910
 **********************************************************************************************************************/
FUNC(void, FIM_CODE)            FiM_Init
                                  (P2CONST(FiM_ConfigType,
                                   AUTOMATIC, FIM_INIT_DATA) FiMConfigPtr);

/***********************************************************************************************************************
 *  FiM_DemInit()
 **********************************************************************************************************************/
/*! \brief                    This service (re-)initializes the FiM with current status of DEM.
 *
 *  \details                  Function shall be called by DEM to (re-)initialize the FIM when
 *                            - the DEM has been initialized and FIM can query monitor and event status for initial FID
 *                              calculation or
 *                            - the DEM detects a status change of a certain number of events.
 *                            CAUTION: During the complete runtime of FiM_DemInit, FiM_DemTriggerOnEventStatus
 *                            must not be called!
 *                            NOTE: Interruption by FiM_DemTriggerOnMonitorStatus is ok.
 *                            CAUTION: The FiM loops through all configured events or FIDs and calls 
 *                            Dem_GetEventUdsStatus and Dem_GetMonitorStatus for each of them.
 *                            Depending on the configuration, FiM_DemInit can take a considerable time.
 *  \pre                      FiM needs to be at least pre-initialized.
 *  \context                  TASK
 *  \reentrant                FALSE
 *  \synchronous              TRUE
 *  \trace                    DSGN-FiM22936, DSGN-FiM22867
 **********************************************************************************************************************/
FUNC(void, FIM_CODE)            FiM_DemInit(void);

/***********************************************************************************************************************
 *  FiM_GetFunctionPermission()
 **********************************************************************************************************************/
/*! \brief      This function shall be used to query the permission of the FID.
 *
 *  \details    - This function  reports the permission state of the functionality assigned to the FID.
 *              - If development error detection is enabled:
 *                - Permission will be set to FALSE, if the FIM is not initialized or if the FID is not valid.
 *                - If development error reporting is enabled, an error will additionally be reported to the DET.
 *
 *  \param[in]  FID           Function ID that the query is for (identifies a functionality).
 *                            Min.:   0
 *                            Max.:   Result of configuration of FIDs in FIM (Max is either 255 or 65535)
 *  \param[out] Permission    Must point to a variable of type boolean.
 *                            TRUE:   FID has permission to run 
 *                            FALSE:  FID has no permission to run, i.e. shall not be executed 
 *  \return                   E_OK:     The request is accepted, Permission could be obtained and is valid
 *                            E_NOT_OK: The request is not accepted, e.g. initialization of FIM not completed 
 *                                      Permission could not be obtained.
 *  \pre                      -
 *  \context                  TASK|ISR2
 *  \reentrant                TRUE
 *  \synchronous              TRUE
 *  \trace                    DSGN-FiM22861
 **********************************************************************************************************************/
FUNC(Std_ReturnType, FIM_CODE)  FiM_GetFunctionPermission
                                  (FiM_FunctionIdType FID,
                                   P2VAR(boolean, AUTOMATIC, FIM_APPL_DATA) Permission
                                  );

#if (FIM_FEATURE_OBD == STD_ON)
/***********************************************************************************************************************
 *  FiM_GetFunctionPendingStatus()
 **********************************************************************************************************************/
/*! \brief      This function shall be used to query the pending status of the events connected to the FID.
 *
 *  \details    - This function is used in context of IUMPR calculation for OBD.
 *              - It reports the pending status of the event assigned to the FID.
 *              - If development error detection is enabled:
 *                - pending status will be set to FALSE, if the FIM is not initialized or if the FID is not valid,
 *                - if development error reporting is enabled, an error will additionally be reported to the DET.
 *
 *  \param[in]  FID           Function ID that the query is for (identifies a functionality).
 *                            Min.:   0
 *                            Max.:   Result of configuration of FIDs in FIM (Max is either 255 or 65535)
 *  \param[out] pendingStatus Must point to a variable of type boolean.
 *                            TRUE:   any event connected to FID has status bit DEM_UDS_STATUS_PDTC set
 *                            FALSE:  no event connected to FID has status bit DEM_UDS_STATUS_PDTC set
 *  \return                   E_OK:     The request is accepted, pending status could be obtained and is valid
 *                            E_NOT_OK: The request is not accepted, e.g. initialization of FIM not completed 
 *                                      Pending status could not be obtained.
 *  \pre                      -
 *  \context                  TASK|ISR2
 *  \reentrant                TRUE
 *  \synchronous              TRUE
 *  \config                   FIM_FEATURE_OBD == STD_ON (OBD license available and OBD enabled at compile time)
 *  \trace                    DSGN-FiM23008
 **********************************************************************************************************************/
FUNC(Std_ReturnType, FIM_CODE)  FiM_GetFunctionPendingStatus
                                  (FiM_FunctionIdType FID, 
                                   P2VAR(boolean, AUTOMATIC, FIM_APPL_DATA) pendingStatus
                                  );
#endif


#if (FIM_FEATURE_OBD == STD_ON)
/***********************************************************************************************************************
 *  FiM_DemTriggerOnEventStatus()
 **********************************************************************************************************************/
/*! \brief      Function is provided to DEM in order to call FIM upon status changes.
 *
 *  \details                    This function is provided to DEM in order to call FIM upon status changes.
 *                              CAUTION: This function may not be interrupted by a function call of the same kind
 *                              with the same event id! Interruption of FiM_DemTriggerOnEventStatus by
 *                              FiM_DemTriggerOnEventStatus is only allowed if the event ids of both calls differ.
 *  \param[in]  EventId         Identification of an Event by assigned event number.
 *                              The Event Number is configured in the DEM. 
 *                              Min.: 1 (0: Indication of no Event or Failure) 
 *                              Max.: depending on configuration of Event Numbers in DEM (Max is either 255 or 65535) 
 *  \param[in]  EventStatusOld  extended event status before change
 *  \param[in]  EventStatusNew  extended event status after change
 *  \pre                        -
 *  \context                    TASK|ISR2
 *  \reentrant                  TRUE (but not for the same event id!)
 *  \synchronous                TRUE
 *  \trace                      DSGN-FiM22911
 **********************************************************************************************************************/
FUNC(void, FIM_CODE)            FiM_DemTriggerOnEventStatus
                                  (Dem_EventIdType EventId,
                                   Dem_UdsStatusByteType EventStatusOld,
                                   Dem_UdsStatusByteType EventStatusNew
                                  );
#endif

/***********************************************************************************************************************
 *  FiM_DemTriggerOnMonitorStatus()
 **********************************************************************************************************************/
/*! \brief      Function is provided to DEM in order to call FIM upon monitor status changes.
 *
 *  \details                    This function is provided to DEM in order to call FIM upon monitor status changes.
 *  \param[in]  EventId         Identification of an Event by assigned event number.
 *                              The Event Number is configured in the DEM. 
 *                              Min.: 1 (0: Indication of no Event or Failure) 
 *                              Max.: depending on configuration of Event Numbers in DEM (Max is either 255 or 65535) 
 *  \pre                        -
 *  \context                    TASK|ISR2
 *  \reentrant                  TRUE
 *  \synchronous                TRUE
 *  \trace                      DSGN-FiM22960
 **********************************************************************************************************************/
FUNC(void, FIM_CODE)            FiM_DemTriggerOnMonitorStatus
                                  (Dem_EventIdType EventId
                                  );

#if (FIM_VERSION_INFO_API == STD_ON)
/***********************************************************************************************************************
 *  FiM_GetVersionInfo()
 **********************************************************************************************************************/
/*! \brief                      This function returns the version information of the FiM.
 *
 *  \details                    The version information contains vendor ID, moduleID, major/minor/patch version number. 
 *                              The version numbers are decimal coded.
 *  \param[out] versioninfo     Pointer to where to store the version information of this module. Must point to a
 *                              variable of type Std_VersionInfoType.
 *  \pre                        -
 *  \context                    TASK|ISR2
 *  \reentrant                  TRUE
 *  \synchronous                TRUE
 *  \config                     FIM_VERSION_INFO_API == STD_ON
 *  \trace                      CREQ-103738
 **********************************************************************************************************************/
FUNC(void, FIM_CODE)            FiM_GetVersionInfo
                                  (P2VAR(Std_VersionInfoType, AUTOMATIC, FIM_APPL_DATA) versioninfo
                                  );   
#endif

/***********************************************************************************************************************
 *  FiM_MainFunction()
 **********************************************************************************************************************/
/*! \brief                      Main function without functionality. Needs not be cyclically scheduled. 
 *
 *  \details                    This function does nothing, as cyclic event evaluation is not supported.
 *
 *  \pre                        -
 *  \context                    TASK
 *  \reentrant                  FALSE
 *  \synchronous                TRUE
 **********************************************************************************************************************/
FUNC(void, FIM_CODE)            FiM_MainFunction(void);

#define FIM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/*!
 * \exclusivearea FIM_EXCLUSIVE_AREA_0
 *                Ensures consistency of the FID Pending counters and inhibition status array.
 * \protects      FiM_InhStatus, FiM_FidPendingCounter
 * \usedin        FiM_Init, FiM_DemInit, FiM_DemTriggerOnMonitorStatus, FiM_DemTriggerOnEventStatus
 * \exclude       -
 * \length        SHORT during runtime          protects a short code section for inc/decrementing up a counter or (re-)setting a bit
 * \length        MEDIUM during initialization  protects resetting all counters and inhibition states
 * \endexclusivearea
 */


#endif /* FIM_H */

/***********************************************************************************************************************
 *  END OF FILE: FiM.h
 **********************************************************************************************************************/
