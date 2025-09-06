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
/*!        \file     FiM.C
 *         \brief    Source for Autosar 4 module FiM
 *
 *         \details  Static source file for FiM. May not be changed by customer / generator
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
 *  2.00.00   2013-11-01  vistne  ESCAN00070055 Compiler error: FiM.c(XXX):'FiM_FidPendingCounter':undeclared identifier
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

#define FIM_SOURCE

/* *********************************************************************************************************************
 *  GLOBAL MISRA Justifications
 **********************************************************************************************************************/

/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */


/***********************************************************************************************************************
*  INCLUDES
***********************************************************************************************************************/

#include "Dem.h"
#include "FiM.h"

#include "SchM_FiM.h"

#if (FIM_DEV_ERROR_REPORT == STD_ON)
  /* Include Development Error Tracer */
# include "Det.h"                        
#endif

#if (FIM_CFG_USE_RTE == STD_ON)
# include "Rte_FiM.h"
#endif

/* EcuM for ErrorHook */
#if (FIM_CFG_VARIANT_POSTBUILD_LOADABLE == STD_ON)
# include "EcuM_Error.h"
#endif


/*! Enter critical section of FiM */
#define FiM_EnterCritical()   SchM_Enter_FiM_FIM_EXCLUSIVE_AREA_0()
/*! Leave critical section of FiM */
#define FiM_LeaveCritical()   SchM_Exit_FiM_FIM_EXCLUSIVE_AREA_0()


/***********************************************************************************************************************
*  VERSION CHECK
***********************************************************************************************************************/
/* vendor specific version information is decimal coded */
#if (  (FIM_SW_MAJOR_VERSION != (0x05)) \
    || (FIM_SW_MINOR_VERSION != (0x01)) \
    || (FIM_SW_PATCH_VERSION != (0x00)) )      
# error "Vendor specific version numbers of FiM.c and FiM.h are inconsistent"
#endif

/* check whether whether configuration files were generated with compatible generator version */
#if (  (FIM_CFG_GEN_MAJOR_VERSION != (0x05)) \
    || (FIM_CFG_GEN_MINOR_VERSION != (0x01)) )
# error "Incompatible configuration file (generator) version used!"
#endif


/***********************************************************************************************************************
*  LOCAL CONSTANT MACROS
***********************************************************************************************************************/
#if !defined (FIM_LOCAL)                                                                  /* COV_MSR_COMPATIBILITY XF */
/*! Default compiler abstraction for local functions */
# define FIM_LOCAL                 static
#endif

#if !defined (FIM_LOCAL_INLINE)                                                           /* COV_MSR_COMPATIBILITY XF */
/*! Default compiler abstraction for local inline functions */
# define FIM_LOCAL_INLINE          LOCAL_INLINE
#endif


/*! FiM is in uninitialized state */
#define FIM_UNINITIALIZED           0
/*! FiM is in initialized state */
#define FIM_INITIALIZED             1
/*! FiM is in pre-initialized state (FiM_Init was executed but not FiM_DemInit) */
#define FIM_PREINITIALIZED          2

/*! \defgroup  FiM_ErrorCodes  Error codes used by FIM
 * Error codes used by FIM
 * \{ */
#define FIM_E_OK                    E_OK /*!< No error */
#define FIM_E_NOT_OK                1u   /*!< Error    */
#if (FIM_E_OK == FIM_E_NOT_OK)
# error "Something's wrong with definition of E_OK!"
#endif
/*! \} */


/*! \defgroup  FiM_IncDecCodes  Internal codes for FID increment / decrement
 * Internal codes for FID increment / decrement
 * \{ */
#define FIM_FID_NOCHANGE            (0x00u) /*!< No change */
#define FIM_FID_INC                 (0x01u) /*!< Increment */
#define FIM_FID_DEC                 (0x02u) /*!< Decrement */
/*! \} */


/*! \defgroup  FiM_EventIdTableType  Internal codes which eventId table to use
 * Internal codes which eventId table to use
 * \{ */
#define FIM_EVENTID_TABLE           (0x00u) /*!< Main table for inhibition */
#define FIM_EVENTIDPENDING_TABLE    (0x01u) /*!< Table for pending locks   */
/*! \} */


/* status bits defined by DEM
DEM_MONITOR_STATUS_TF     0x01  bit 0: TestFailed 
DEM_MONITOR_STATUS_TNCTOC 0x02  bit 1: TestNotCompletedThisOperationCycle
DEM_UDS_STATUS_TF         0x01  bit 0: TestFailed 
DEM_UDS_STATUS_TFTOC      0x02  bit 1: TestFailedThisOperationCycle 
DEM_UDS_STATUS_PDTC       0x04  bit 2: PendingDTC 
DEM_UDS_STATUS_CDTC       0x08  bit 3: ConfirmedDTC 
DEM_UDS_STATUS_TNCSLC     0x10  bit 4: TestNotCompletedSinceLastClear 
DEM_UDS_STATUS_TFSLC      0x20  bit 5: TestFailedSinceLastClear 
DEM_UDS_STATUS_TNCTOC     0x40  bit 6: TestNotCompletedThisOperationCycle 
DEM_UDS_STATUS_WIR        0x80  bit 7: WarningIndicatorRequested          */

/*! * \defgroup  DefInhModTable Defines for Inhibition Mode Table
 * Defines for masks, patterns and whether result needs to be inverted that are used in calculation of effects of
 * monitor status changes.
 * \{ */
/*! \defgroup  InhCfgCodeLF Inhibition Config Code "Last Failed"
 * Inhibition configuration inhibits if test failed status bit is set. \n
 * Inhibits if: TF
 * \{ */
#define FIM_LAST_FAILED_MASK                  (Dem_MonitorStatusType)0x01u  /*!<DEM_MONITOR_STATUS_TF */
#define FIM_LAST_FAILED_PATTERN               (Dem_MonitorStatusType)0x01u  /*!<DEM_MONITOR_STATUS_TF set */
#define FIM_LAST_FAILED_INVERTRESULT          (boolean)FALSE                /*!<do not invert result */
/*! \} */
/*! \defgroup  InhCfgCodeTst Inhibition Config Code "Tested"
 * Inhibition configuration inhibits if TestNotCompletedThisOperationCycle status bit is NOT set. \n
 * Inhibits if: /TNCTOC
 * \{ */
#define FIM_TESTED_MASK                       (Dem_MonitorStatusType)0x02u  /*!<DEM_MONITOR_STATUS_TNCTOC */
#define FIM_TESTED_PATTERN                    (Dem_MonitorStatusType)0x00u  /*!<DEM_MONITOR_STATUS_TNCTOC not set */
#define FIM_TESTED_INVERTRESULT               (boolean)FALSE                /*!<do not invert result */
/*! \} */
/*! \defgroup  InhCfgCodeNTst Inhibition Config Code "Not Tested"
 * Inhibition configuration inhibits if TestNotCompletedThisOperationCycle status bit is set. \n
 * Inhibits if: TNCTOC
 * \{ */
#define FIM_NOT_TESTED_MASK                   (Dem_MonitorStatusType)0x02u  /*!<DEM_MONITOR_STATUS_TNCTOC */
#define FIM_NOT_TESTED_PATTERN                (Dem_MonitorStatusType)0x02u  /*!<DEM_MONITOR_STATUS_TNCTOC set */
#define FIM_NOT_TESTED_INVERTRESULT           (boolean)FALSE                /*!<do not invert result */
/*! \} */
/*! \defgroup  InhCfgCodeTstLF Inhibition Config Code "Tested AND Failed"
 * Inhibition configuration inhibits if TestNotCompletedThisOperationCycle status bit is NOT set AND LastFailed status
 * bit is set. \n
 * Inhibits if: /TNCTOC && TF
 * \{ */
#define FIM_TESTED_AND_FAILED_MASK            (Dem_MonitorStatusType)0x03u  /*!<DEM_MONITOR_STATUS_TNCTOC | DEM_MONITOR_STATUS_TF */
#define FIM_TESTED_AND_FAILED_PATTERN         (Dem_MonitorStatusType)0x01u  /*!<DEM_MONITOR_STATUS_TNCTOC not set, DEM_MONITOR_STATUS_TF set */
#define FIM_TESTED_AND_FAILED_INVERTRESULT    (boolean)FALSE                /*!<do not invert result */
/*! \} */
/*! \defgroup  InhCfgCodeNTstOrLF Inhibition Config Code "Not Tested OR Failed" (Autosar extension)
 * Inhibition configuration inhibits if TestNotCompletedThisOperationCycle status bit is set OR LastFailed status
 * bit is NOT set. \n
 * Inhibits if: TNCTOC || TF -> /(/TNCTOC && /TF)
 * \{ */
#define FIM_NOT_TESTED_OR_FAILED_MASK         (Dem_MonitorStatusType)0x03u  /*!<DEM_MONITOR_STATUS_TNCTOC | DEM_MONITOR_STATUS_TF */
#define FIM_NOT_TESTED_OR_FAILED_PATTERN      (Dem_MonitorStatusType)0x00u  /*!<DEM_MONITOR_STATUS_TNCTOC not set, DEM_MONITOR_STATUS_TF not set */
#define FIM_NOT_TESTED_OR_FAILED_INVERTRESULT (boolean)TRUE                 /*!<invert result */
/*! \} */
/*! \} */


/***********************************************************************************************************************
*  LOCAL FUNCTION MACROS
***********************************************************************************************************************/

/*! Return number of configured FIDs. One less than size of FID table (last element is dummy element).          */
#define FiM_GetNrOfFids()                                       (FiM_GetSizeOfFidTable() - 1)
/*! Return event id at particular position in event id list (macro is easier to read).                          */
#define FiM_GetEventId_EventIdTable                             FiM_GetEventIdOfEventIdTable
/*! Return index into inhibition code table at particular position in event id list (macro is easier to read).  */
#define FiM_GetEventToInhCodeTableIndex_EventIdTable            FiM_GetEventToInhCodeTableIndexOfEventIdTable

/***********************************************************************************************************************
*  LOCAL DATA TYPES AND STRUCTURES
***********************************************************************************************************************/

#if (FIM_CFG_VARIANT_POSTBUILD_LOADABLE == STD_ON)
/*! Pointer to configuration data in case of PB loadable. */
P2CONST(FiM_ConfigType, FIM_VAR_NOINIT, FIM_INIT_DATA)              FiM_ConfigDataPtr;
#endif


/***********************************************************************************************************************
*  LOCAL DATA PROTOTYPES
***********************************************************************************************************************/


/*! Struct that holds info for the calculation of a FID depending on the inhibition configuration. */
typedef struct FiM_InhibitionModeT
{
  Dem_MonitorStatusType Mask;
  Dem_MonitorStatusType Pattern;
  boolean                     InvertResult;
} FiM_InhibitionModeType;

/*! Typedef for access to event id table. */
typedef uint16 FiM_EventIdTableIndexType;


#define FIM_START_SEC_VAR_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Initialization status of FiM. */
FIM_LOCAL VAR(uint8, FIM_VAR_INIT)                        FiM_InitializationStatus    = FIM_UNINITIALIZED;

#define FIM_STOP_SEC_VAR_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define FIM_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*!Offset into event id table. Used if direct table acces is used, i.e. event ids are in continuously ascending order.*/
FIM_LOCAL VAR(FiM_EventIdTableIndexType, FIM_VAR_NOINIT)  FiM_SearchEventIdTableDirectOffset;

#define FIM_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define FIM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Pointer that holds the used function for searching an event id in EventIdTable. */
FIM_LOCAL FUNC(boolean, FIM_CODE) (*FiM_SearchEventIdTableFct)
                                   (Dem_EventIdType eventId                                            /* in  */,
                                    P2VAR(FiM_EventIdTableIndexType, AUTOMATIC, AUTOMATIC) evTableIdx  /* out */,
                                    uint8 eventIdTableType                                             /* in  */);

#define FIM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/***********************************************************************************************************************
*  GLOBAL DATA
***********************************************************************************************************************/

#define FIM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Inhibition Mode Table: used in calculation of effects of event status changes. */
FIM_LOCAL CONST(FiM_InhibitionModeType, FIM_CONST)
  FiM_InhibitionModeTable[FIM_INHCODE_NUMBER] =                                       /* PRQA S 3218 */ /* MD_FiM_8.7 */
{
  { /* invalid: pattern can never match "anded" mask */
    /* FIM_INHCODE_INVALID */
    (Dem_MonitorStatusType)0x00u,    
    (Dem_MonitorStatusType)0x01u,
    (boolean) FALSE
  },
  { /* FIM_LAST_FAILED */
    FIM_LAST_FAILED_MASK,
    FIM_LAST_FAILED_PATTERN,
    FIM_LAST_FAILED_INVERTRESULT
  },
  { /* FIM_NOT_TESTED */
    FIM_NOT_TESTED_MASK,                    
    FIM_NOT_TESTED_PATTERN,
    FIM_NOT_TESTED_INVERTRESULT
  },
  { /* FIM_TESTED */
    FIM_TESTED_MASK,                    
    FIM_TESTED_PATTERN,
    FIM_TESTED_INVERTRESULT
  },
  { /* FIM_TESTED_AND_FAILED */
    FIM_TESTED_AND_FAILED_MASK,            
    FIM_TESTED_AND_FAILED_PATTERN,
    FIM_TESTED_AND_FAILED_INVERTRESULT
  },
  { /* FIM_NOT_TESTED_OR_FAILED */
    FIM_NOT_TESTED_OR_FAILED_MASK,            
    FIM_NOT_TESTED_OR_FAILED_PATTERN,
    FIM_NOT_TESTED_OR_FAILED_INVERTRESULT
  },
  { /* invalid code for inhibition (only pending): pattern can never match "anded" mask */
    /* FIM_INHCODE_PENDING */
    (Dem_MonitorStatusType)0x00u,    
    (Dem_MonitorStatusType)0x01u,
    (boolean) FALSE
  }
};                   


#define FIM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/***********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define FIM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/***********************************************************************************************************************
 *  FiM_CompareAndSwap
 **********************************************************************************************************************/
/*! \brief                    Internal default version of an atomic compare and swap operation.
 *
 *  \details                  Compares the contents of a memory location (identified by addressPtr) to a given
 *                            value (cmpValue) and, only if they are the same, modifies the contents of that memory
 *                            location to a given new value (newValue).
 *                            This is done as a single atomic operation.
 *                              - Implemented here with a critical section.
 *                              - Can be replaced by more efficient version for multicore systems as soon as FiM
 *                                becomes multicore capable.
 *  \param[in,out] addressPtr Memory location to be compared and swapped. Must point to a valid memory location.
 *  \param[in]     cmpValue   Value to be compared with.
 *  \param[in]     newValue   Value to be written.
 *  \return                   TRUE  swap has been performed
 *                            FALSE otherwise
 *  \pre                      -
 *  \context                  TASK|ISR2
 *  \reentrant                TRUE
 **********************************************************************************************************************/
FIM_LOCAL_INLINE FUNC(boolean, FIM_CODE) FiM_CompareAndSwap
                                          (volatile CONSTP2VAR(uint32, AUTOMATIC, AUTOMATIC) addressPtr /* in/out */,
                                           CONST(FiM_ProcessorWordType, AUTOMATIC) cmpValue             /* in     */,
                                           CONST(FiM_ProcessorWordType, AUTOMATIC) newValue             /* in     */);


/***********************************************************************************************************************
 * FiM_GetBitfieldWordIndex
 **********************************************************************************************************************/
/*! \brief                    Calculate and return the word index in a bitfield array.
 *
 *  \details                  A bitfield array is composed of a word array.
 *                            Function calculates the index of the word array where a specified bit position is located.
 *  \param[in]  bitPosition   Specified bit position.
 *  \return                   Index in word array.
 *  \pre                      -
 *  \context                  TASK|ISR2
 *  \reentrant                TRUE
 **********************************************************************************************************************/
FIM_LOCAL_INLINE FUNC(uint32, FIM_CODE) FiM_GetBitfieldWordIndex
                                         (CONST(uint32, AUTOMATIC) bitPosition /* in  */);


/***********************************************************************************************************************
 * FiM_GetBitfieldBitInWordIndex
 **********************************************************************************************************************/
/*! \brief                    Calculate and return the index of a bit within the corresponding word in a bitfield array.
 *
 *  \details                  A bitfield array is composed of a word array.
 *                            Function calculates the index of the bit within the word where a specified bit position
 *                            is located.
 *  \param[in]  bitPosition   Specified bit position.
 *  \return                   Bit position within word.
 *  \pre                      -
 *  \context                  TASK|ISR2
 *  \reentrant                TRUE
 **********************************************************************************************************************/
FIM_LOCAL_INLINE FUNC(uint8, FIM_CODE)  FiM_GetBitfieldBitInWordIndex
                                         (CONST(uint32, AUTOMATIC) bitPosition /* in  */);


/***********************************************************************************************************************
 * FiM_TestBitInBitfield
 **********************************************************************************************************************/
/*! \brief                      Test if the bit at a given position is set in a bitfield.
 *
 *  \details                    see brief
 *  \param[in]  bitfieldWordPtr Pointer to bitfield array (actually word array containing bitfield).
 *                              Internally only used for read access.
 *  \param[in]  bitPosition     Specified bit position.
 *  \return                     TRUE if bit is set.
 *                              FALSE if bit is not set.
 *  \pre                        -
 *  \context                    TASK|ISR2
 *  \reentrant                  TRUE
 **********************************************************************************************************************/
FIM_LOCAL_INLINE
  FUNC(boolean,FIM_CODE)  FiM_TestBitInBitfield
                                      (volatile CONSTP2CONST(FiM_ProcessorWordType,AUTOMATIC,AUTOMATIC)bitfieldWordPtr,
                                       CONST(uint32, AUTOMATIC) bitPosition);


/***********************************************************************************************************************
 * FiM_SetBitInBitfield
 **********************************************************************************************************************/
/*! \brief                          Set the bit at a given position in a bitfield.
 *
 *  \details                        see brief
 *  \param[in]  bitfieldPtr         Pointer to bitfield array (actually word array containing bitfield).
 *  \param[in]  bitfieldWordArrSize Total size of word array containing bitfield.
 *                                  Must not exceed length of word array allocated in valid memory.
 *  \param[in]  bitPosition         Specified bit position.
 *  \pre                            -
 *  \context                        TASK|ISR2
 *  \reentrant                      TRUE
 **********************************************************************************************************************/
FIM_LOCAL_INLINE FUNC(void, FIM_CODE) FiM_SetBitInBitfield
                                       (volatile CONSTP2VAR(FiM_ProcessorWordType,AUTOMATIC,AUTOMATIC) bitfieldWordPtr,
                                        CONST(uint32, AUTOMATIC) bitfieldWordArrSize,
                                        CONST(uint32, AUTOMATIC) bitPosition);


/***********************************************************************************************************************
 * FiM_ResetBitInBitfield
 **********************************************************************************************************************/
/*! \brief                          Reset the bit at a given position in a bitfield.
 *
 *  \details                        see brief
 *  \param[in]  bitfieldWordPtr     Pointer to bitfield array (actually word array containing bitfield).
 *  \param[in]  bitfieldWordArrSize Total size of word array contianing bitfield.
 *                                  Must not exceed length of word array allocated in valid memory.
 *  \param[in]  bitPosition         Specified bit position.
 *  \pre                            -
 *  \context                        TASK|ISR2
 *  \reentrant                      TRUE
 **********************************************************************************************************************/
FIM_LOCAL_INLINE FUNC(void, FIM_CODE) FiM_ResetBitInBitfield
                                       (volatile CONSTP2VAR(FiM_ProcessorWordType,AUTOMATIC,AUTOMATIC) bitfieldWordPtr,
                                        CONST(uint32, AUTOMATIC) bitfieldWordArrSize,
                                        CONST(uint32, AUTOMATIC) bitPosition);


/***********************************************************************************************************************
 * FiM_GetCountOfEvents_ByTableType
 **********************************************************************************************************************/
/*! \brief                        Return the number of events (except dummy ones) depending on type of eventId
 *                                table.
 *
 *  \details                      There may be several eventId tables. This function accesses FiM_GetCountOfEvents of
 *                                the table that is specified in the parameter.
 *  \param[in]  eventIdTableType  Which eventId table to use.
 *                                Must be one of FiM_EventIdTableType.
 *  \return                       Count of events in the specified table.
 *  \pre                          -
 *  \context                      TASK|ISR2
 *  \reentrant                    TRUE
 **********************************************************************************************************************/
FIM_LOCAL_INLINE FUNC(FiM_EventIdTableIndexType, FIM_CODE) FiM_GetCountOfEvents_ByTableType(uint8 eventIdTableType);


/***********************************************************************************************************************
 * FiM_GetEventId_EventIdTable_ByTableType
 **********************************************************************************************************************/
/*! \brief                        Return event id at index position depending on type of eventId table.
 *
 *  \details                      There may be several eventId tables. This function accesses
 *                                FiM_GetEventId_EventIdTable of the table that is specified in the parameter.
 *  \param[in]  index             Index in table to obtain eventId from.
 *  \param[in]  eventIdTableType  Which eventId table to use.
 *                                Must be one of FiM_EventIdTableType.
 *  \return                       EvenmtId in the specified table.
 *  \pre                          -
 *  \context                      TASK|ISR2
 *  \reentrant                    TRUE
 **********************************************************************************************************************/
FIM_LOCAL_INLINE FUNC(Dem_EventIdType,FIM_CODE) FiM_GetEventId_EventIdTable_ByTableType(FiM_EventIdTableIndexType index,
                                                                                        uint8 eventIdTableType);


/***********************************************************************************************************************
 *  FiM_SearchEventIdTableDirect
 **********************************************************************************************************************/
/*! \brief                        Internal helper function to find a given event id in FiM_EventIdTable
 *                                using direct index access.
 *
 *  \details                      There is a direct relation between the event id and it's position in FiM_EventIdTable
 *                                of the kind: event id = position + offset
 *                                Algorithm is determined by FiM_SetSearchEventIdTableFct.
 *                                Offset is stored in FiM_SearchEventIdTableDirectOffset and was determined in
 *                                FiM_SetSearchEventIdTableFct.
 *  \param[in]  eventId           Event id to be searched in event id table.
 *                                May be any value from 0 to max value of Dem_EventIdType.
 *  \param[out] evTableIdx        Pointer to variable where index of found event is stored.
 *                                Must point to a variable of type FiM_EventIdTableIndexType.
 *  \param[in]  eventIdTableType  Which eventId table to use.
 *                                Must be one of FiM_EventIdTableType.
 *  \return                       TRUE  event id was found
 *                                FALSE event id was not found
 *  \pre                          Event Ids in FiM_EventIdTable must be in continuously ascending order without gaps.
 *  \context                      TASK|ISR2
 *  \reentrant                    TRUE
 **********************************************************************************************************************/
FIM_LOCAL FUNC(boolean, FIM_CODE) FiM_SearchEventIdTableDirect
                                   (Dem_EventIdType eventId                                            /* in  */,
                                    P2VAR(FiM_EventIdTableIndexType, AUTOMATIC, AUTOMATIC) evTableIdx  /* out */,
                                    uint8 eventIdTableType                                             /* in  */);

/***********************************************************************************************************************
 *  FiM_SearchEventIdTableLinear
 **********************************************************************************************************************/
/*! \brief                        Internal helper function to find a given event id in FiM_EventIdTable using linear 
 *                                search.
 *
 *  \details                      Just a dumb linear search starting at the beginning of FiM_EventIdTable until either
 *                                end is reached or event id is found.
 *                                Algorithm is determined by FiM_SetSearchEventIdTableFct.
 *  \param[in]  eventId           Event id to be searched in event id table.
 *                                May be any value from 0 to max value of Dem_EventIdType.
 *  \param[out] evTableIdx        Pointer to variable where index of found event is stored.
 *                                Must point to a variable of type FiM_EventIdTableIndexType.
 *  \param[in]  eventIdTableType  Which eventId table to use.
 *                                Must be one of FiM_EventIdTableType.
 *  \return                       TRUE  event id was found
 *                                FALSE event id was not found
 *  \pre                          -
 *  \context                      TASK|ISR2
 *  \reentrant                    TRUE
 **********************************************************************************************************************/
FIM_LOCAL FUNC(boolean, FIM_CODE) FiM_SearchEventIdTableLinear
                                   (Dem_EventIdType eventId                                            /* in  */,
                                    P2VAR(FiM_EventIdTableIndexType, AUTOMATIC, AUTOMATIC) evTableIdx  /* out */,
                                    uint8 eventIdTableType                                             /* in  */);

/***********************************************************************************************************************
 *  FiM_SearchEventIdTableBinary
 **********************************************************************************************************************/
/*! \brief                        Internal helper function to find a given event id in FiM_EventIdTable using binary 
 *                                search.
 *
 *  \details                      Just a standard half-interval search.
 *                                Algorithm is determined by FiM_SetSearchEventIdTableFct.
 *  \param[in]  eventId           Event id to be searched in event id table.
 *                                May be any value from 0 to max value of Dem_EventIdType.
 *  \param[out] evTableIdx        Pointer to variable where index of found event is stored.
 *                                Must point to a variable of type FiM_EventIdTableIndexType.
 *  \param[in]  eventIdTableType  Which eventId table to use.
 *                                Must be one of FiM_EventIdTableType.
 *  \return                       TRUE  event id was found
 *                                FALSE event id was not found
 *  \pre                          Event Ids in FiM_EventIdTable must be in ascending order.
 *  \context                      TASK|ISR2
 *  \reentrant                    TRUE
 **********************************************************************************************************************/
FIM_LOCAL FUNC(boolean, FIM_CODE) FiM_SearchEventIdTableBinary
                                   (Dem_EventIdType eventId                                            /* in  */,
                                    P2VAR(FiM_EventIdTableIndexType, AUTOMATIC, AUTOMATIC) evTableIdx  /* out */,
                                    uint8 eventIdTableType                                             /* in  */);

/***********************************************************************************************************************
 *  FiM_SetSearchEventIdTableFct
 **********************************************************************************************************************/
/*! \brief                        Internal helper function to determine the search algorithm in FiM_EventIdTable.
 *
 *  \details                      This function is used at startup of FIM. It's result depends on the sequence of event.
 *                                ids. This is not done at generation time since FiM_EventIdTable can be calibratable.
 *                                Possible search algorithms: Linear or binary search or direct table access.
 *  \param[in]  eventIdTableType  Which eventId table to use.
 *                                Must be one of FiM_EventIdTableType.
 *  \pre                          -
 *  \context                      TASK
 *  \reentrant                    FALSE
 **********************************************************************************************************************/
FIM_LOCAL FUNC(void, FIM_CODE)    FiM_SetSearchEventIdTableFct(uint8 eventIdTableType);

#if (FIM_FEATURE_OBD == STD_ON)
/***********************************************************************************************************************
 *  FiM_IncFidPendingCounter_Checked()
 **********************************************************************************************************************/
/*! \brief                    Internal helper function to increment FID pending counter.
 *                        
 *  \details                  This function increments the pending counter for the passed FID.
 *                            If runtime checks are enabled:
 *                              It is ensured that FID is smaller than number of elements in FiM_FidPendingCounter
 *                              before write access is done.
 *  \param[in]  fid           Function Id that pending counter should be incremented for.
 *  \pre                      -
 *  \context                  TASK|ISR2
 *  \reentrant                TRUE
 *  \config                   FIM_FEATURE_OBD == STD_ON
 **********************************************************************************************************************/
FIM_LOCAL_INLINE FUNC(void, FIM_CODE) FiM_IncFidPendingCounter_Checked(FiM_FunctionIdType fid);

/***********************************************************************************************************************
 *  FiM_DecFidPendingCounter_Checked()
 **********************************************************************************************************************/
/*! \brief                    Internal helper function to decrement FID pending counter if counter is not already 0.
 *                        
 *  \details                  This function decrements the pending counter for the passed FID. It includes a prior
 *                            check for 0.
 *                            If runtime checks are enabled:
 *                              It is ensured that FID is smaller than number of elements in FiM_FidPendingCounter
 *                              before write access is done.
 *  \param[in]  fid           Function Id that pending counter should be decremented for.
 *  \pre                      -
 *  \context                  TASK|ISR2
 *  \reentrant                TRUE
 *  \config                   FIM_FEATURE_OBD == STD_ON
 **********************************************************************************************************************/
FIM_LOCAL_INLINE FUNC(void, FIM_CODE) FiM_DecFidPendingCounter_Checked(FiM_FunctionIdType fid);
#endif


/***********************************************************************************************************************
 *  FiM_IsFidInhibited()
 **********************************************************************************************************************/
/*! \brief                    Internal helper function to calculate whether a specific FID is inhibited.
 *                        
 *  \details                  Checks all inhibitions states connected to FID.
 *  \pre                      -
 *  \context                  TASK|ISR2
 *  \reentrant                TRUE
 **********************************************************************************************************************/
FIM_LOCAL_INLINE FUNC(boolean, FIM_CODE)  FiM_IsFidInhibited(FiM_FunctionIdType FID);


#if (FIM_FEATURE_OBD == STD_ON)
/***********************************************************************************************************************
 *  FiM_IsFidPendingLocked()
 **********************************************************************************************************************/
/*! \brief                    Internal helper function to calculate whether a specific FID is pending locked.
 *                        
 *  \details                  Checks all pending states connected to FID.
 *  \pre                      -
 *  \context                  TASK|ISR2
 *  \reentrant                TRUE
 **********************************************************************************************************************/
FIM_LOCAL_INLINE FUNC(boolean, FIM_CODE)  FiM_IsFidPendingLocked(FiM_FunctionIdType FID);
#endif


/***********************************************************************************************************************
 *  FiM_CalcInhAndPendingStates()
 **********************************************************************************************************************/
/*! \brief                    Internal helper function to calculate the state of all Inhibition Configurations as well
 *                            as the pending states of the FIDs.
 *  \details                  Complete re-calculation. Request Monitor and Event status from DEM.
 *  \pre                      -
 *  \context                  TASK
 *  \reentrant                TRUE
 **********************************************************************************************************************/
FIM_LOCAL FUNC(void, FIM_CODE) FiM_CalcInhAndPendingStates(void);


/***********************************************************************************************************************
 *  FiM_GetInhibitionStatusFromMonitor()
 **********************************************************************************************************************/
/*! \brief                    Internal helper function to obtain the inhibition status
 *                            for one monitor status / inhibition code.
 *
 *  \details                  Obtain the inhibition status for
 *                            - one monitor status
 *                            - one inhibition code
 *  \param[in]  monStatus     monitor status byte of event
 *  \param[in]  inhCode       code of inhibition configuration, i.e. index into FiM_InhibitionModeTable;
 *  \return                   TRUE:  combination inhibits FID.
 *                            FALSE: combination does not inhibit FID.
 *  \pre                      -
 *  \context                  TASK|ISR2
 *  \reentrant                TRUE
 **********************************************************************************************************************/
FIM_LOCAL_INLINE FUNC(boolean, FIM_CODE) FiM_GetInhibitionStatusFromMonitor(Dem_MonitorStatusType monStatus,
                                                                            uint8 inhCode);


#if (FIM_FEATURE_OBD == STD_ON)
/***********************************************************************************************************************
 *  FiM_ModFidCounters()
 **********************************************************************************************************************/
/*!
 *  \brief                      Internal helper function to modify FID pending counters.
 *  \details                    Increment, decrement or leave the counters unchanged depending on passed modification
 *                              codes.
 *  \param[in]  fid             FID for which pending counters are modified
 *  \param[in]  modCodePending  code how to modify FID Pending counter
 *                              possible codes:
 *                              FIM_FID_NOCHANGE: FID Pending shall not be changed due to status change
 *                              FIM_FID_INC:      FID Pending shall be incremented due to status change
 *                              FIM_FID_DEC:      FID Pending shall be decremented due to status change
 *  \pre                      -
 *  \context                    TASK|ISR2
 *  \reentrant                  TRUE
*******************************************************************************/
FIM_LOCAL_INLINE FUNC(void, FIM_CODE) FiM_ModFidCounters(FiM_FunctionIdType fid, uint8 modCodePending);
#endif


/***********************************************************************************************************************
 *  FiM_CalcInhibStatusOfEvent()
 **********************************************************************************************************************/
/*!
 *  \brief                      Internal helper function to calcuate the inhibition states connected to an event.
 *  \details                    Request Monitor Status from DEM. Set or reset corresponding inhibition status bit.
 *  \param[in]  evTableIdx      Index into event id table for event of which inhibition states are to be calculated.
 *  \pre                        -
 *  \context                    TASK|ISR2
 *  \reentrant                  TRUE
*******************************************************************************/
FIM_LOCAL_INLINE FUNC(void, FIM_CODE) FiM_CalcInhibStatusOfEvent(FiM_EventIdTableIndexType evTableIdx);


#if (FIM_FEATURE_OBD == STD_ON)
/***********************************************************************************************************************
 *  FiM_CalcPendingStatusOfEvent()
 **********************************************************************************************************************/
/*!
 *  \brief                      Internal helper function to calcuate the FID pending states connected to an event.
 *  \details                    Increment, decrement or leave the counters unchanged depending on passed modification
 *                              codes. Changes all FID pending counters of an event.
 *  \param[in]  evTableIdx      Index into event id table for event of which inhibition states are to be calculated.
 *  \param[in]  modCodePending  Code whether to increment, decrement or leave the counter unchanged.
 *  \pre                        -
 *  \context                    TASK|ISR2
 *  \reentrant                  TRUE
*******************************************************************************/
FIM_LOCAL_INLINE FUNC(void, FIM_CODE) FiM_CalcPendingStatusOfEvent(FiM_EventIdTableIndexType evTableIdx,
                                                                   uint8 modCodePending);
#endif


#define FIM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/
#define FIM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/***********************************************************************************************************************
 * FiM_CompareAndSwap
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FIM_LOCAL_INLINE FUNC(boolean, FIM_CODE) FiM_CompareAndSwap
                                          (volatile CONSTP2VAR(uint32, AUTOMATIC, AUTOMATIC) addressPtr,
                                           CONST(FiM_ProcessorWordType, AUTOMATIC) cmpValue,
                                           CONST(FiM_ProcessorWordType, AUTOMATIC) newValue)
{
  boolean retVal;

  /* #10 Enter critical section. */
  FiM_EnterCritical();

  /* #20 Assert that the currently stored value is the same as the passed compare value. */
  if (*addressPtr == cmpValue)
  {
    /* #30 if so: write new value. */
    *addressPtr = newValue;                                                      /* SBSW_FIM_COMPSWAPFUNC_ADDRESS_PTR */
    retVal = TRUE;
  }
  else
  {
    /* #40 otherwise: return FALSE. */
    retVal = FALSE;
  }

  /* #50 Leave critical section. */
  FiM_LeaveCritical();

  return retVal;
}


/***********************************************************************************************************************
 * FiM_GetBitfieldWordIndex
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FIM_LOCAL_INLINE FUNC(uint32, FIM_CODE) FiM_GetBitfieldWordIndex
                                         (CONST(uint32, AUTOMATIC) bitPosition)
{
  uint32  retVal;

  retVal = (uint32)(bitPosition / FIM_BITS_PER_WORD);

  return retVal;
}


/***********************************************************************************************************************
 * FiM_GetBitfieldBitInWordIndex
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FIM_LOCAL_INLINE FUNC(uint8, FIM_CODE)  FiM_GetBitfieldBitInWordIndex
                                         (CONST(uint32, AUTOMATIC) bitPosition)
{
  uint8 retVal;

  retVal = (uint8)(bitPosition % FIM_BITS_PER_WORD);

  return retVal;
}


/***********************************************************************************************************************
 * FiM_TestBitInBitfield
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FIM_LOCAL_INLINE
  FUNC(boolean, FIM_CODE) FiM_TestBitInBitfield
                            (volatile CONSTP2CONST(FiM_ProcessorWordType, AUTOMATIC, AUTOMATIC) bitfieldWordPtr,
                             CONST(uint32, AUTOMATIC) bitPosition)
{
  /* ! bitfieldWordPtr may only be used for read access ! */

  boolean               retVal;
  FiM_ProcessorWordType bitMask;
  uint32                bitfieldWordArrIndex = FiM_GetBitfieldWordIndex(bitPosition);
  
  /* #10 Set up bitmask for the word depending on passed bitPosition. */
  bitMask = (0x01U << (FiM_GetBitfieldBitInWordIndex(bitPosition)));
  /* #20 Mask out all other bits and test whether AND yields something different than 0. */
  if ((bitfieldWordPtr[bitfieldWordArrIndex] & bitMask) != 0)
  {
    /* #30 Return TRUE if yes (bit is set). */
    retVal = TRUE;
  }
  else
  {
    /* #40 Return FALSE if no (bit is not set). */
    retVal = FALSE;
  }

  return retVal;
}


/***********************************************************************************************************************
 * FiM_SetBitInBitfield
 **********************************************************************************************************************/
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
FIM_LOCAL_INLINE FUNC(void, FIM_CODE) FiM_SetBitInBitfield
                                       (volatile CONSTP2VAR(FiM_ProcessorWordType,AUTOMATIC,AUTOMATIC) bitfieldWordPtr,
                                        CONST(uint32, AUTOMATIC) bitfieldWordArrSize,
                                        CONST(uint32, AUTOMATIC) bitPosition)
{
  volatile P2VAR(FiM_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) wordPtr;

  FiM_ProcessorWordType oldValue;
  FiM_ProcessorWordType newValue;
  FiM_ProcessorWordType bitMask;
  uint32                bitfieldWordArrIndex;

  FIM_DUMMY_STATEMENT_CONST(bitfieldWordArrSize);            /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */

  /* #10 Identify the index into the word array where the bit is located. */
  bitfieldWordArrIndex = FiM_GetBitfieldWordIndex(bitPosition);

  /* #20 If runtime checks are enabled: Check that write access is not done beyond array bounds. */
#if (FIM_DEV_RUNTIME_CHECKS == STD_ON)                                                      /* COV_FIM_RUNTIME_CHECKS */
  if (bitfieldWordArrIndex < bitfieldWordArrSize)
#endif
  {
    /* #30 Identify the word and the bitmask for the word. */
    wordPtr = &bitfieldWordPtr[bitfieldWordArrIndex];
    bitMask = (0x01U << (FiM_GetBitfieldBitInWordIndex(bitPosition)));
    /* #40 Repeat until CompareAndSwap succeeds. */
    do
    {
      /* #50 Set the correct bit in the bitfield word in a current stack copy. */
      oldValue = *wordPtr;
      newValue = (oldValue | bitMask);
      /* #60 Try to update (compare & swap) the RAM contents. */
    } while (FiM_CompareAndSwap(wordPtr, oldValue, newValue) == FALSE);        /* SBSW_FIM_BITMANIP_COMPSWAPFUNC_CALL */
  }
  return;
}


/***********************************************************************************************************************
 * FiM_ResetBitInBitfield
 **********************************************************************************************************************/
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
FIM_LOCAL_INLINE FUNC(void, FIM_CODE) FiM_ResetBitInBitfield
                                       (volatile CONSTP2VAR(FiM_ProcessorWordType,AUTOMATIC,AUTOMATIC) bitfieldWordPtr,
                                        CONST(uint32, AUTOMATIC) bitfieldWordArrSize,
                                        CONST(uint32, AUTOMATIC) bitPosition)
{
  volatile P2VAR(FiM_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) wordPtr;

  FiM_ProcessorWordType oldValue;
  FiM_ProcessorWordType newValue;
  FiM_ProcessorWordType bitMask;

  uint32                bitfieldWordArrIndex;

  FIM_DUMMY_STATEMENT_CONST(bitfieldWordArrSize);            /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */

  /* #10 Identify the index into the word array where the bit is located. */
  bitfieldWordArrIndex = FiM_GetBitfieldWordIndex(bitPosition);

  /* #20 If runtime checks are enabled: Check that write access is not done beyond array bounds. */
#if (FIM_DEV_RUNTIME_CHECKS == STD_ON)                                                      /* COV_FIM_RUNTIME_CHECKS */
  if (bitfieldWordArrIndex < bitfieldWordArrSize)
#endif
  {
    /* #30 Identify the word and the bitmask for the word. */
    wordPtr = &bitfieldWordPtr[bitfieldWordArrIndex];
    bitMask = ~(0x01U << (FiM_GetBitfieldBitInWordIndex(bitPosition)));
    /* #40 Repeat until CompareAndSwap succeeds. */
    do
    {
      /* #50 Reset the correct bit in the bitfield word in a current stack copy. */
      oldValue = *wordPtr;
      newValue = (oldValue & bitMask);
      /* #60 Try to update (compare & swap) the RAM contents. */
    } while (FiM_CompareAndSwap(wordPtr, oldValue, newValue) == FALSE);        /* SBSW_FIM_BITMANIP_COMPSWAPFUNC_CALL */
  }
  return;
}


/***********************************************************************************************************************
 * FiM_GetCountOfEvents_ByTableType
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FIM_LOCAL_INLINE FUNC(FiM_EventIdTableIndexType, FIM_CODE) FiM_GetCountOfEvents_ByTableType(uint8 eventIdTableType)
{
  FiM_SizeOfEventIdTableType retVal;
# if (FIM_FEATURE_OBD == STD_OFF)
  FIM_DUMMY_STATEMENT(eventIdTableType);                                             /* PRQA S 3112 */ /* MD_MSR_14.2 */
#else
  if (eventIdTableType == FIM_EVENTIDPENDING_TABLE)
  {
    retVal = (FiM_EventIdTableIndexType)(FiM_GetSizeOfEventIdTable() - 1);
    /* at the moment there is no separate event id table for pending locks  */
    /* otherwise one would use something like FiM_GetCountOfEventsPending   */
  }
  else
#endif
  {
    retVal = (FiM_EventIdTableIndexType)(FiM_GetSizeOfEventIdTable() - 1);
  }
  return retVal;
}


/***********************************************************************************************************************
 * FiM_GetEventId_EventIdTable_ByTableType
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FIM_LOCAL_INLINE FUNC(Dem_EventIdType,FIM_CODE) FiM_GetEventId_EventIdTable_ByTableType(FiM_EventIdTableIndexType index,
                                                                                        uint8 eventIdTableType)
{
  Dem_EventIdType eventId;
# if (FIM_FEATURE_OBD == STD_OFF)
  FIM_DUMMY_STATEMENT(eventIdTableType);                                             /* PRQA S 3112 */ /* MD_MSR_14.2 */
#else
  if (eventIdTableType == FIM_EVENTIDPENDING_TABLE)
  {
    eventId = FiM_GetEventId_EventIdTable(index);
    /* at the moment there is no separate event id table for pending locks        */
    /* otherwise one would use something like FiM_GetEventId_EventIdPendingTable  */
  }
  else
#endif
  {
    eventId = FiM_GetEventId_EventIdTable(index);
  }
  return eventId;
}


/***********************************************************************************************************************
 *  FiM_SearchEventIdTableDirect
 **********************************************************************************************************************/
/*!
 *  Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FIM_LOCAL FUNC(boolean, FIM_CODE) FiM_SearchEventIdTableDirect
                                   (Dem_EventIdType eventId /* in */,
                                    P2VAR(FiM_EventIdTableIndexType, AUTOMATIC, AUTOMATIC) evTableIdx  /* out */,
                                    uint8 eventIdTableType                                             /* in  */)
{
  boolean retVal;
  FiM_EventIdTableIndexType  countOfEvents = FiM_GetCountOfEvents_ByTableType(eventIdTableType);
  FiM_EventIdTableIndexType  searchEventIdTableDirectOffset;
# if (FIM_FEATURE_OBD == STD_OFF)
  FIM_DUMMY_STATEMENT(eventIdTableType);                                             /* PRQA S 3112 */ /* MD_MSR_14.2 */
#else
  if (eventIdTableType == FIM_EVENTIDPENDING_TABLE)
  {
    searchEventIdTableDirectOffset = FiM_SearchEventIdTableDirectOffset;
    /* at the moment there is no separate event id table for pending locks                    */
    /* otherwise one would set it to something like FiM_SearchEventIdTablePendingDirectOffset */
  }
  else
#endif
  {
    searchEventIdTableDirectOffset = FiM_SearchEventIdTableDirectOffset;
  }
  /* #10 if event id is within range limits */
  if ((eventId >= searchEventIdTableDirectOffset)                             &&
      (eventId <  (countOfEvents + searchEventIdTableDirectOffset)))
  {
    /* #20 event id found: subtract offset from event id, return this as index into FiM_EventIdTable */
    (*evTableIdx) =                                                           /* SBSW_FIM_SEARCHIDFUNC_EVTABLEIDX_PTR */
      (FiM_EventIdTableIndexType)eventId - searchEventIdTableDirectOffset;
    /* #30 set return value to TRUE */
    retVal = TRUE;
  }
  /* #40 otherwise */
  else
  {
    /* #50 event id not found: set return value to FALSE */
    retVal = FALSE;
  }
  return retVal;
}


/***********************************************************************************************************************
 *  FiM_SearchEventIdTableLinear
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FIM_LOCAL FUNC(boolean, FIM_CODE) FiM_SearchEventIdTableLinear
                                   (Dem_EventIdType eventId                                            /* in  */,
                                    P2VAR(FiM_EventIdTableIndexType, AUTOMATIC, AUTOMATIC) evTableIdx  /* out */,
                                    uint8 eventIdTableType                                             /* in  */)
{
  /* #10 set return value to FALSE */
  boolean                   retVal        = FALSE;
  FiM_EventIdTableIndexType countOfEvents = FiM_GetCountOfEvents_ByTableType(eventIdTableType);
  /* #30 loop through all indexes in FiM_EventIdTable until end is reached or event id was found */
  for(*evTableIdx = 0;                                                        /* SBSW_FIM_SEARCHIDFUNC_EVTABLEIDX_PTR */
      *evTableIdx < countOfEvents;
      (*evTableIdx)++)                                                        /* SBSW_FIM_SEARCHIDFUNC_EVTABLEIDX_PTR */
  {
    /* #40 check whether event id at current probe index matches */
    Dem_EventIdType  currEventId  = FiM_GetEventId_EventIdTable_ByTableType(*evTableIdx, eventIdTableType);
    if (currEventId == eventId)
    {
      /* #50 it matches -> event id found; return this as index into FiM_EventIdTable and set return value to TRUE */
      retVal = TRUE;
      break;
    }
  }
  return retVal;
}


/***********************************************************************************************************************
 *  FiM_SearchEventIdTableBinary
 **********************************************************************************************************************/
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
 *
 *
 *
 *
 */
FIM_LOCAL FUNC(boolean, FIM_CODE) FiM_SearchEventIdTableBinary
                                   (Dem_EventIdType eventId                                           /* in  */,
                                    P2VAR(FiM_EventIdTableIndexType, AUTOMATIC, AUTOMATIC) evTableIdx /* out */,
                                    uint8 eventIdTableType                                            /* in  */)
{
  /* #05 set return value to FALSE */
  boolean                   retVal        = FALSE;
  FiM_EventIdTableIndexType countOfEvents = FiM_GetCountOfEvents_ByTableType(eventIdTableType);

  /* #10 init BOTTOM (loIdx) and TOP (hiIdx) boundaries to first and last element in FiM_EventIdTable */
  FiM_EventIdTableIndexType loIdx = 0;
  FiM_EventIdTableIndexType hiIdx = FiM_GetCountOfEvents_ByTableType(eventIdTableType);

  /* #20 loop while bottom index smaller than top index, element not found and search index is still within bounds */
  while (loIdx <= hiIdx)
  {
    boolean         notAvail = FALSE;
    Dem_EventIdType probeEventId;

    /* #30 calculate the probe reference (in the middle of loIdx and hiIdx) */
    (*evTableIdx) = (FiM_EventIdTableIndexType)((hiIdx + loIdx) >> 1);        /* SBSW_FIM_SEARCHIDFUNC_EVTABLEIDX_PTR */

    /* #40 if event id found */
    probeEventId  = FiM_GetEventId_EventIdTable_ByTableType(*evTableIdx, eventIdTableType);
    if (probeEventId == eventId)
    {
      /* found a matching element */
      /* #50 set return value to TRUE (found) */
      retVal = TRUE;
    }
    /* #60 otherwise */
    else
    {
      /* not found a matching element */
      /* #70 determine whether lower or higher half shall be taken as interval for next try */
      /* #80 if event id found is higher than the id we're looking for */
      if (probeEventId > eventId)
      {
        /* id we're looking for is lower than the current reference */
        /* #90 Use lower half of interval for next loop, i.e. set new top index to current probe index  */
        /* #100 Make sure new index stays within array bounds, remember if it wants to get beyond       */
        if((*evTableIdx) > 0)
        {
          hiIdx = (FiM_EventIdTableIndexType)((*evTableIdx) - 1);                    /* PRQA S 0291 */ /* MD_FiM_0291 */
        }
        else
        { /* not available */
          notAvail = TRUE; /* found no matching element */
        }
      }
      /* #110 otherwise */
      else
      {
        /* id we're looking for is greater than the current reference */
        /* #120 Use upper half of interval for next loop, i.e. set new bottom index to current probe index */
        /* #130 Make sure new index stays within array bounds, remember if it wants to get beyond          */
        if((*evTableIdx) < (countOfEvents - 1))
        {
          loIdx = (FiM_EventIdTableIndexType)((*evTableIdx) + 1); 
        }
        else
        { /* not available */
          notAvail = TRUE; /* found no matching element */
        }
      }
    }
    /* #140 break loop if element was found or index went beyond array bounds */
    /* #150 check whether bottom index is still lower than top index is done in loop condition */
    if ((retVal == TRUE) || (notAvail == TRUE))
    {
      break;
    }
  }

  return retVal;
}


/***********************************************************************************************************************
 *  FiM_SetSearchEventIdTableFct
 **********************************************************************************************************************/
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
 *
 */
FIM_LOCAL FUNC(void, FIM_CODE) FiM_SetSearchEventIdTableFct(uint8 eventIdTableType)
{
  FiM_EventIdTableIndexType evTableIdx;
  Dem_EventIdType           prevEventId;  /* previous event id */
  Dem_EventIdType           currEventId;  /* current event id  */
  FIM_LOCAL FUNC(boolean, FIM_CODE) (*searchEventIdTableFct)
                                      (Dem_EventIdType eventId                                            /* in  */,
                                       P2VAR(FiM_EventIdTableIndexType, AUTOMATIC, AUTOMATIC) evTableIdx  /* out */,
                                       uint8 eventIdTableType                                             /* in  */);
  FiM_EventIdTableIndexType searchEventIdTableDirectOffset;
  FiM_EventIdTableIndexType countOfEvents = FiM_GetCountOfEvents_ByTableType(eventIdTableType);

  searchEventIdTableFct               = FiM_SearchEventIdTableDirect;
  prevEventId                         = FiM_GetEventId_EventIdTable_ByTableType(0, eventIdTableType);
  searchEventIdTableDirectOffset      = prevEventId;

  for (evTableIdx = 1; evTableIdx < countOfEvents; evTableIdx++)
  {
    currEventId = FiM_GetEventId_EventIdTable_ByTableType(evTableIdx, eventIdTableType);
    /* are we still hoping for direct access? if so, check whether next id is still continuous */
    if ((searchEventIdTableFct == FiM_SearchEventIdTableDirect) &&
        (currEventId != (prevEventId + 1)))
    {
      /* not continuous anymore -> switch to binary search if list is not too small */
      /*lint -save -e506 */
      if (countOfEvents >= FIM_BINSEARCH_MINLISTLENGTH)
      /*lint -restore */
      {
        searchEventIdTableFct = FiM_SearchEventIdTableBinary;
      }
      else
      {
        /* use linear algorithm for small lists (if direct access cannot be used) */
        searchEventIdTableFct = FiM_SearchEventIdTableLinear;
      }
    }
    /* are we hoping for binary algorithm, i.e. at least ordered event ids?                       */
    /* no check if (FiM_SearchEventIdTableFct == FiM_SearchEventIdTableBinary) necessary because: */
    /* - if we're still in direct access mode (current event id <= previous event id)             */
    /*   always returns FALSE                                                                     */
    /* - if we're already in linear search mode it won't do any harm; we may or may not enter the */
    /*   block but afterwards it will still be linear mode and we will stop                       */
    /* Note: the next two decisions should only be true if event ids were re-assigned after       */
    /*       FIM generation                                                                       */
    if (currEventId <= prevEventId)
    {
      /* not ordered anymore -> switch to linear search and stop */
      searchEventIdTableFct = FiM_SearchEventIdTableLinear;
    }
    prevEventId = currEventId;
    /* are we down to linear search? */
    if (searchEventIdTableFct == FiM_SearchEventIdTableLinear)
    {
      /* we're down to linear search -> stop the search for the optimal algorithm - it won't get any better */
      break;
    }
  }
# if (FIM_FEATURE_OBD == STD_ON)
  if (eventIdTableType == FIM_EVENTIDPENDING_TABLE)
  {
    FiM_SearchEventIdTableFct = searchEventIdTableFct;
    FiM_SearchEventIdTableDirectOffset = searchEventIdTableDirectOffset;
    /* at the moment there is no separate event id table for pending locks                        */
    /* otherwise one would use something like FiM_SearchEventIdPendingTableFct and                */
    /* FiM_SearchEventIdTablePendingDirectOffset                                                  */
  }
  else
#endif
  {
    FiM_SearchEventIdTableFct = searchEventIdTableFct;
    FiM_SearchEventIdTableDirectOffset = searchEventIdTableDirectOffset;
  }
}


# if (FIM_FEATURE_OBD == STD_ON)
/***********************************************************************************************************************
 *  FiM_IncFidPendingCounter_Checked()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FIM_LOCAL_INLINE FUNC(void, FIM_CODE) FiM_IncFidPendingCounter_Checked(FiM_FunctionIdType fid)
{
#if (FIM_DEV_RUNTIME_CHECKS == STD_ON)                                                      /* COV_FIM_RUNTIME_CHECKS */
  if (fid < FiM_GetSizeOfFidPendingCounter())
#endif
  {
    FiM_IncFidPendingCounter(fid);                                       /* SBSW_FIM_ACCESS_FIDPENDINGCOUNTER_CHECKED */
  }
}


/***********************************************************************************************************************
 *  FiM_DecFidPendingCounter_Checked()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FIM_LOCAL_INLINE FUNC(void, FIM_CODE) FiM_DecFidPendingCounter_Checked(FiM_FunctionIdType fid)
{
#if (FIM_DEV_RUNTIME_CHECKS == STD_ON)                                                      /* COV_FIM_RUNTIME_CHECKS */
  if (fid < FiM_GetSizeOfFidPendingCounter())
#endif
  {
    if (FiM_GetFidPendingCounter(fid) > 0)
    {
      FiM_DecFidPendingCounter(fid);                                     /* SBSW_FIM_ACCESS_FIDPENDINGCOUNTER_CHECKED */
    }
  }
}
# endif


/***********************************************************************************************************************
 *  FiM_GetInhibitionStatusFromMonitor()
 **********************************************************************************************************************/
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
FIM_LOCAL_INLINE FUNC(boolean, FIM_CODE) FiM_GetInhibitionStatusFromMonitor(Dem_MonitorStatusType monStatus,
                                                                            uint8 inhCode)
{
  boolean result;
  /* #10 if runtime checks are enabled                                                              */
#if (FIM_DEV_RUNTIME_CHECKS == STD_ON)                                                      /* COV_FIM_RUNTIME_CHECKS */
  /* #20 if inhibition code is not valid                                                            */
  /*     Invalid inhibition codes are ignored                                                       */
  /*     only relevant if there is a problem with the generator                                     */
  /*     would result otherwise in an out of bounds read access and an undefined inhibition status  */
  /*       -> avoid out of bound access and define status to permitted (i.e. ignore code)           */
  if (inhCode >= FIM_INHCODE_NUMBER)
  {
    /* #30 define status to permitted (i.e. ignore code)           */
    result = FALSE;
  }
  /* #40 otherwise */
  else
#endif
  {
    /* #100 mask the passed monStatus with the mask that's relevant for the passed inhibition code                    */
    /* #110 this yields the bits that are relevant for the passed inhibition code                                     */
    /* #120 if these bits match the bit pattern relevant for the passed inhibition code then combination inhibits FID */
    result = (boolean)((monStatus & FiM_InhibitionModeTable[inhCode].Mask) == FiM_InhibitionModeTable[inhCode].Pattern);
    /* #130 check whether inhibition code requests an inversion of the result                                         */
    if (FiM_InhibitionModeTable[inhCode].InvertResult == TRUE)
    {
      result = (boolean)(!result);
    }
  }

  return result;
}


#if (FIM_FEATURE_OBD == STD_ON)
/***********************************************************************************************************************
 *  FiM_ModFidCounters()
 **********************************************************************************************************************/
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
FIM_LOCAL_INLINE FUNC(void, FIM_CODE) FiM_ModFidCounters(FiM_FunctionIdType fid, uint8 modCodePending)
{
  {
    /* enter critical section to protect each increment/decrement against interruption; */
    /* only one enter/leave over the whole if/else to reduce number of enter/leaves     */
    FiM_EnterCritical();                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */
    if (modCodePending == FIM_FID_DEC)
    {
      /* decrement FID Pending counter is necessary                              */
      FiM_DecFidPendingCounter_Checked(fid);
    }
    if (modCodePending == FIM_FID_INC)
    {
      /* increment FID Pending counter is necessary                              */
      FiM_IncFidPendingCounter_Checked(fid);
    }
    /* leave critical section */
    FiM_LeaveCritical();                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
  return;
}
#endif


/**********************************************************************************************************************
 *  FiM_CalcInhibStatusOfEvent()
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
FIM_LOCAL_INLINE FUNC(void, FIM_CODE) FiM_CalcInhibStatusOfEvent(FiM_EventIdTableIndexType evTableIdx)
{
  uint16                        inhCodeIdx, inhCodeTableIdx_Start, inhCodeTableIdx_Stop;

  Dem_MonitorStatusType monitorStatusAtBegin, monitorStatusAtEnd;
  Std_ReturnType        retCodeAtBegin, retCodeAtEnd;

  /* #10 identify the parts of the complete inhibition config tables that are relevant for this event         */
  /*     do so by identifying start index and stop index (last relevant element plus 1) in the complete array */
  inhCodeTableIdx_Start = FiM_GetEventToInhCodeTableIndex_EventIdTable(evTableIdx);
  inhCodeTableIdx_Stop  = FiM_GetEventToInhCodeTableIndex_EventIdTable(evTableIdx+1);
  
  /* #20 get monitor status for event from DEM                                                                */
  retCodeAtEnd = Dem_GetMonitorStatus(FiM_GetEventId_EventIdTable(evTableIdx), &monitorStatusAtEnd); /* SBSW_FIM_DEMGETMONITORSTATUS_CALL */

  /* #30 repeat the following until both return code and monitor status didn't change during calculation      */
  /*     (in which case we were interrupted and the basis for our calculation changed -> we have to redo it   */
  do
  {
    retCodeAtBegin        = retCodeAtEnd;
    monitorStatusAtBegin  = monitorStatusAtEnd;
    /* #100 loop through all inhibition configurations that are connected to the event */
    for(inhCodeIdx = inhCodeTableIdx_Start; inhCodeIdx < inhCodeTableIdx_Stop; inhCodeIdx++)
    {
      /* inhibition configuration table is always generated, no manual calibration here                           */
      /* -> it does not contain invalid inhibition configurations                                                 */
      /* even if it contained an invalid event id, first element of FiM_InhibitionModeTable would neutralise it   */

      boolean inhibStat = FALSE;

      /* #110 if monitor status could be obtained */
      if (retCodeAtBegin == E_OK)
      {
        /* #120 determine the inhibition status of this particular inhibition cfg                                     */
        inhibStat = FiM_GetInhibitionStatusFromMonitor(monitorStatusAtBegin, FiM_GetInhCodeTable(inhCodeIdx));
      }
      /* #130 otherwise */
      else
      {
        /* #140 event is not available in DEM -> it cannot inhibit the function                           */
        /*      (it may not be available, e.g. because SetEventAvailable was called with parameter FALSE) */
        /* SPEC-63513 */
      }
          
      /* #160 set bit in bitfield to inhibition status */
      if (inhibStat == TRUE)
      {
        /* set bit in bitfield FiM_InhStatus[inhCodeIdx] to inhibition status */
        FiM_SetBitInBitfield(&FiM_GetInhStatus(0), FiM_GetSizeOfInhStatus(), inhCodeIdx);   /* SBSW_FIM_BITMANIP_CALL */
      }
      else
      {
        FiM_ResetBitInBitfield(&FiM_GetInhStatus(0), FiM_GetSizeOfInhStatus(), inhCodeIdx); /* SBSW_FIM_BITMANIP_CALL */
      }
    } /* for(inhCfgIdx = 0; inhCfgIdx < nrInhCfgs; inhCfgIdx++) */

    retCodeAtEnd = Dem_GetMonitorStatus(FiM_GetEventId_EventIdTable(evTableIdx), &monitorStatusAtEnd); /* SBSW_FIM_DEMGETMONITORSTATUS_CALL */
  } while ((monitorStatusAtEnd != monitorStatusAtBegin) || (retCodeAtEnd != retCodeAtBegin));

  return;
}



#if (FIM_FEATURE_OBD == STD_ON)
/**********************************************************************************************************************
 *  FiM_CalcPendingStatusOfEvent()
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
FIM_LOCAL_INLINE FUNC(void, FIM_CODE) FiM_CalcPendingStatusOfEvent(FiM_EventIdTableIndexType evTableIdx,
                                                                   uint8  modCodePending)
{
  /* #10 check if a manipulation of FID Pending counters is necessary */
  if (modCodePending != FIM_FID_NOCHANGE)
  {
    /* #20 if yes */
    uint16  evToFidTableIter;
    /* #30 identify the part of the complete FID Pending table that is relevant for this event and inhibition cfg   */
    /*     do so by identifying start index and stop index (last relevant element + 1) in the complete array        */
    /* #40 loop through relevant FIDs and manipulate their Pending counters */
    uint16  evToFidTableIdx_Start = FiM_GetEventToFidPendingTableIndexOfEventIdTable(evTableIdx);
    uint16  evToFidTableIdx_Stop  = FiM_GetEventToFidPendingTableIndexOfEventIdTable(evTableIdx+1);
    for (evToFidTableIter = evToFidTableIdx_Start; evToFidTableIter < evToFidTableIdx_Stop; evToFidTableIter++)
    {
      /* #50 modify FID Pending counters according to given modification code */
      FiM_ModFidCounters(FiM_GetEventToFidPendingTable(evToFidTableIter), modCodePending);
    }
  }
}
#endif


 /**********************************************************************************************************************
  *  FiM_IsFidInhibited()
  *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
 *
  */
FIM_LOCAL_INLINE FUNC(boolean, FIM_CODE)  FiM_IsFidInhibited(FiM_FunctionIdType FID)
{
  uint16  fidToInhTableIdx, fidToInhTableIdx_Start, fidToInhTableIdx_Stop;
  boolean inhibStat = FALSE;

  /* #10 identify the parts of the complete "Fid-to-inhibition-code" table that are relevant for this FID             */
  /* #20 do so by identifying start index and stop index (last relevant element plus 1) in the complete array         */
  fidToInhTableIdx_Start = (uint16)FiM_GetFidTable(FID);
  fidToInhTableIdx_Stop  = (uint16)FiM_GetFidTable(FID + 1);

  /* #30 loop through all inhibition configurations that are connected to the FID                                     */
  for(fidToInhTableIdx = fidToInhTableIdx_Start; fidToInhTableIdx < fidToInhTableIdx_Stop; fidToInhTableIdx++)
  {
    /* inhibition configuration table is always generated, no manual calibration here                                 */
    /* -> it does not contain invalid inhibition configurations                                                       */
    /* even if it contained an invalid event id, first element of FiM_InhibitionModeTable would neutralise it         */

    /* #40 check if inhibition cfg inhibits FID, break if yes (FID is inhibited if at least one cfg inhibits          */
    uint32  inhCodeTableIdx = FiM_GetInhCodeTableIdxOfFidToInhTable(fidToInhTableIdx);
    inhibStat = FiM_TestBitInBitfield(&FiM_GetInhStatus(0), inhCodeTableIdx);                /* SBSW_FIM_BITTEST_CALL */
    if (inhibStat == TRUE)
    {
      break;
    }
}
  return inhibStat;
}
    

 #if (FIM_FEATURE_OBD == STD_ON)
/**********************************************************************************************************************
  *  FiM_IsFidPendingLocked()
  *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
  */
FIM_LOCAL_INLINE FUNC(boolean, FIM_CODE)  FiM_IsFidPendingLocked(FiM_FunctionIdType FID)
{
  boolean pendingStat;
  /* add FiM_EnterCritical() if FiM_FidCounterType cannot be accessed in an atomic way,  */
  /* e.g., FiM_FidCounterType becomes 32 bits while 16 bit platforms are still supported */
  if(FiM_GetFidPendingCounter(FID) != 0)
  {
    pendingStat = TRUE;
  }
  else
  {
    pendingStat = FALSE;
  }
  /* FiM_LeaveCritical() see above comment for FiM_EnterCritical() */
  return pendingStat;
}
#endif

 /**********************************************************************************************************************
  *  FiM_CalcInhAndPendingStates()
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
  */
FIM_LOCAL FUNC(void, FIM_CODE)  FiM_CalcInhAndPendingStates(void)
{
  FiM_ProcessorWordType         inhStatIter;
  FiM_EventIdTableIndexType     evTableIdx;
  /* #10 reset all permission states (and pending counters) to 0 */
  FiM_EnterCritical();                                                               /* PRQA S 3109 */ /* MD_MSR_14.3 */
  for(inhStatIter = 0; inhStatIter < FiM_GetSizeOfInhStatus(); inhStatIter++)
  {
    FiM_SetInhStatus(inhStatIter, 0);                                  /* SBSW_FIM_ACCESS_INHSTATUS_CALCINHPENDSTATES */
  }
  FiM_LeaveCritical();                                                               /* PRQA S 3109 */ /* MD_MSR_14.3 */
#if (FIM_FEATURE_OBD == STD_ON)
  {
    FiM_FunctionIdType            fidIter;
    /* #20 reset all pending counters to 0 */
    FiM_EnterCritical();                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */
    for(fidIter = 0; fidIter < FiM_GetSizeOfFidPendingCounter(); fidIter++)
    {
      FiM_SetFidPendingCounter(fidIter, 0);                    /* SBSW_FIM_ACCESS_FIDPENDINGCOUNTER_CALCINHPENDSTATES */
    }
    FiM_LeaveCritical();                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
#endif

  /* #30 loop through all events in FiM_EventIdTable starting at the first one until the end of the table is reached */
  for(evTableIdx = 0; evTableIdx < FiM_GetCountOfEvents_ByTableType(FIM_EVENTID_TABLE); evTableIdx++)
  {
    /* event id table is always generated, no manual calibration here -> it does not contain invalid event ids */

    /* #40 calculate the inhibition states of this event */
    FiM_CalcInhibStatusOfEvent(evTableIdx);

#if (FIM_FEATURE_OBD == STD_ON)
    {
      Dem_UdsStatusByteType       eventStatus;
      Std_ReturnType              retValue;
      /* #45 in case of OBD */
      /* #50 get event status from DEM for current event id */
      retValue = Dem_GetEventUdsStatus(FiM_GetEventId_EventIdTable(evTableIdx), &eventStatus);   /* SBSW_FIM_DEMGETEVENTUDSSTATUS_CALL */
      /* #60 if event status could be obtained (Dem_GetEventUdsStatus returned E_OK) */
      if(retValue == E_OK)
      {
        uint8   modCode = FIM_FID_NOCHANGE;
        /* #70 determine whether FID pending counter has to be incremented */
        if((eventStatus & DEM_UDS_STATUS_PDTC) == DEM_UDS_STATUS_PDTC)
        {
           modCode = FIM_FID_INC;
        }
        /* #80 calculate the pending status FIDs for this event */
        FiM_CalcPendingStatusOfEvent(evTableIdx, modCode);
      } /* if(retValue == E_OK) */
      /* #210 otherwise (Dem_GetEventUdsStatus did not return E_OK) */
      else
      {
        /* #220 Dem_GetEventUdsStatus returned an error: ignore event for calculation */
      } /* else if(returnValue == E_OK) */
    }
#endif
  } /* for(...; evTableIdx < FiM_GetCountOfEvents_ByTableType(); ...) */
  return;
}



/***********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  FiM_InitMemory
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FIM_CODE) FiM_InitMemory(void)
{ 
  FiM_InitializationStatus = FIM_UNINITIALIZED;
}


/***********************************************************************************************************************
 *  FiM_Init
 **********************************************************************************************************************/
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
 *
*/
FUNC(void, FIM_CODE) FiM_Init(P2CONST(FiM_ConfigType, AUTOMATIC, FIM_INIT_DATA) FiMConfigPtr) /*lint -e{438} */ /*lint -e{550} */
{
  /* ----- Local Variables ---------------------------------------------- */
  
  /* #10 if PB is enabled: do some checks on passed PB config */
#if (FIM_CFG_VARIANT_POSTBUILD_LOADABLE == STD_ON)
  uint8 errorId = FIM_E_INIT_FAILED;
  /* #20 if FiMConfigPtr is NULL_PTR */
  if (FiMConfigPtr == NULL_PTR)
  {
    /* #25 call EcuM_BswErrorHook */
    EcuM_BswErrorHook((uint16) FIM_MODULE_ID,
                      (uint8) ECUM_BSWERROR_NULLPTR);
  }
  /* #40 otherwise if there is a mismatch in the magic numbers of the PB config and the code */
  else if (FiMConfigPtr->FinalMagicNumberOfPBConfig != FIM_FINAL_MAGIC_NUMBER)
  {
    /* #45 call EcuM_BswErrorHook */
    EcuM_BswErrorHook((uint16) FIM_MODULE_ID,
                      (uint8) ECUM_BSWERROR_MAGICNUMBER);
  }
  /* #50 otherwise if there is a mismatch in compatibility versions of the generators used for PB config and code */
  else if (FiMConfigPtr->GeneratorCompatibilityVersionOfPBConfig != FIM_CFG_GEN_COMPATIBILITY_VERSION)
  {
    /* #55 call EcuM_BswErrorHook */
    EcuM_BswErrorHook((uint16) FIM_MODULE_ID,
                      (uint8) ECUM_BSWERROR_COMPATIBILITYVERSION);
  }
  /* #60 otherwise PB config is fine */
  else
  {
    /* #70 use PB config pointer */
    FiM_ConfigDataPtr = FiMConfigPtr;
    errorId           = FIM_E_NO_ERROR;
#else
  {
    FIM_DUMMY_STATEMENT(FiMConfigPtr);                                               /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif

    /* #100 determine search algorithm for event id list */
    FiM_SetSearchEventIdTableFct(FIM_EVENTID_TABLE);
    /* at the moment there is no separate event id table for pending locks  */
# if (FIM_FEATURE_OBD == STD_ON)
    FiM_SetSearchEventIdTableFct(FIM_EVENTIDPENDING_TABLE);
#endif

    /* #250 set component state to "pre-initialized" */
    FiM_InitializationStatus  = FIM_PREINITIALIZED;
  }

#if (FIM_CFG_VARIANT_POSTBUILD_LOADABLE == STD_ON)
# if (FIM_DEV_ERROR_REPORT == STD_ON)
  /* #300 if error was detected report DET */
  if (errorId != FIM_E_NO_ERROR)
  {
    (void)Det_ReportError(FIM_MODULE_ID, FIM_INSTANCE_ID_DET, FIM_SID_FIM_INIT, errorId);
  }
# else
  FIM_DUMMY_STATEMENT(errorId);                              /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
# endif
#endif
}


/***********************************************************************************************************************
 *  FiM_DemInit
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
*/
FUNC(void, FIM_CODE) FiM_DemInit(void)  /*lint -e{529} */
{
  uint8           errorId = FIM_E_NO_ERROR;

#if (FIM_DEV_ERROR_DETECT == STD_ON)                                                         /* COV_FIM_DET_DETECT TX */
  /* #10 check whether FIM is at least pre-initialized */
  if ((FiM_InitializationStatus != FIM_INITIALIZED) &&
      (FiM_InitializationStatus != FIM_PREINITIALIZED))
  {
    errorId = FIM_E_INIT_FAILED;
  }
  else
#endif
  {
    /* #20 re-calculate inhibition states and pending lock states of FIDs if it is initialized */
    FiM_CalcInhAndPendingStates();
    /* #30 set component state to "initialized" */
    FiM_InitializationStatus  = FIM_INITIALIZED;
  }
#if (FIM_DEV_ERROR_REPORT == STD_ON)
  /* #40 otherwise if error was detected report DET */
  if (errorId != FIM_E_NO_ERROR)
  {
    (void)Det_ReportError(FIM_MODULE_ID, FIM_INSTANCE_ID_DET, FIM_SID_FIM_DEMINIT, errorId);
  }
#else
  FIM_DUMMY_STATEMENT(errorId);                              /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
}


#if (FIM_VERSION_INFO_API == STD_ON)
/***********************************************************************************************************************
 *  FiM_GetVersionInfo()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, FIM_CODE)  FiM_GetVersionInfo
                       (P2VAR(Std_VersionInfoType, AUTOMATIC, FIM_APPL_DATA) versioninfo)

{
  uint8 errorId = FIM_E_NO_ERROR;
  
#if (FIM_DEV_ERROR_DETECT == STD_ON)                                                         /* COV_FIM_DET_DETECT TX */
  if (versioninfo == NULL_PTR)
  {
    errorId = FIM_E_PARAM_POINTER;
  }
  else
#endif
  {
    versioninfo->vendorID         = FIM_VENDOR_ID;                                        /* SBSW_FIM_VERSIONINFO_PTR */
    versioninfo->moduleID         = FIM_MODULE_ID;                                        /* SBSW_FIM_VERSIONINFO_PTR */
    versioninfo->sw_major_version = FIM_SW_MAJOR_VERSION;                                 /* SBSW_FIM_VERSIONINFO_PTR */
    versioninfo->sw_minor_version = FIM_SW_MINOR_VERSION;                                 /* SBSW_FIM_VERSIONINFO_PTR */
    versioninfo->sw_patch_version = FIM_SW_PATCH_VERSION;                                 /* SBSW_FIM_VERSIONINFO_PTR */
  }
#if (FIM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != FIM_E_NO_ERROR)
  {
    (void)Det_ReportError(FIM_MODULE_ID, FIM_INSTANCE_ID_DET, FIM_SID_FIM_GETVERSIONINFO, errorId);
  }
#else
  FIM_DUMMY_STATEMENT(errorId);                              /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif
}
#endif /* (FIM_VERSION_INFO_API == STD_ON) */


/***********************************************************************************************************************
 *  FiM_GetFunctionPermission
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
*/
FUNC(Std_ReturnType, FIM_CODE)  FiM_GetFunctionPermission
                                 (FiM_FunctionIdType FID,                            /* PRQA S 1330 */ /* MD_FiM_16.4 */
                                  P2VAR(boolean, AUTOMATIC, FIM_APPL_DATA) Permission
                                 )                                                                     /*lint -e{529} */
{
  uint8             errorId = FIM_E_NO_ERROR;
  Std_ReturnType    retCode = E_NOT_OK;

#if (FIM_DEV_ERROR_DETECT == STD_ON)                                                         /* COV_FIM_DET_DETECT TX */
  /* #010 if out parameter Permission is NULL_PTR set corresponding DET code */
  if (Permission == NULL_PTR)
  {
    errorId = FIM_E_PARAM_POINTER;
  }
  /* #020 otherwise if FIM is not initialized set corresponding DET code (SPEC-31915) */
  else if(FiM_InitializationStatus != FIM_INITIALIZED)
  {
    errorId = FIM_E_UNINIT;
    *Permission = FALSE;                                                                   /* SBSW_FIM_PERMISSION_PTR */
  }
  /* #030 otherwise if FID is out of range set corresponding DET code (SPEC-31912) */
  else if(FID >= FiM_GetNrOfFids())
  {
    errorId = FIM_E_FID_OUT_OF_RANGE;
    *Permission = FALSE;                                                                   /* SBSW_FIM_PERMISSION_PTR */
  }
  else
#endif
  /* #040 otherwise return permission status of FID (SPEC-31914) */
  {
    boolean inhibStat = FiM_IsFidInhibited(FID);
    
    *Permission = !inhibStat;                                                              /* SBSW_FIM_PERMISSION_PTR */
    retCode     = E_OK;
  }

#if (FIM_DEV_ERROR_REPORT == STD_ON)
  /* #050 if error reporting is enabled, report DET code if one was set */
  if (errorId != FIM_E_NO_ERROR)
  {
    (void)Det_ReportError(FIM_MODULE_ID, FIM_INSTANCE_ID_DET, FIM_SID_FIM_GETFUNCTIONPERMISSION, errorId);
  }
#else
  FIM_DUMMY_STATEMENT(errorId);                              /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif

  return retCode;
}


#if (FIM_FEATURE_OBD == STD_ON)
/******************************************************************************
    FiM_GetFunctionPendingStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
*/
FUNC(Std_ReturnType, FIM_CODE)  FiM_GetFunctionPendingStatus
                                 (FiM_FunctionIdType FID, 
                                  P2VAR(boolean, AUTOMATIC, FIM_APPL_DATA) pendingStatus
                                 )                                                                     /*lint -e{529} */
{
  uint8             errorId = FIM_E_NO_ERROR;
  Std_ReturnType    retCode = E_NOT_OK;

#if (FIM_DEV_ERROR_DETECT == STD_ON)                                                         /* COV_FIM_DET_DETECT TX */
  /* #10 if out parameter pendingStatus is NULL_PTR set corresponding DET code */
  if (pendingStatus == NULL_PTR)
  {
    errorId = FIM_E_PARAM_POINTER;
  }
  /* #20 otherwise if FIM is not initialized set corresponding DET code */
  else if(FiM_InitializationStatus != FIM_INITIALIZED)
  {
    errorId = FIM_E_UNINIT;
  }
  /* #30 otherwise if FID is out of range set corresponding DET code */
  else if(FID >= FiM_GetSizeOfFidPendingCounter())
  {
    errorId = FIM_E_FID_OUT_OF_RANGE;
  }
  else
#endif
  /* #40 otherwise return pending status of FID */
  {
    *pendingStatus = FiM_IsFidPendingLocked(FID);                                       /* SBSW_FIM_PENDINGSTATUS_PTR */
    retCode = E_OK;
  }

#if (FIM_DEV_ERROR_REPORT == STD_ON)
  /* #50 if error reporting is enabled, report DET code if one was set */
  if (errorId != FIM_E_NO_ERROR)
  {
    (void)Det_ReportError(FIM_MODULE_ID, FIM_INSTANCE_ID_DET,
                          FIM_SID_FIM_GETFUNCTIONPENDINGSTATUS, errorId);
  }
#else
  FIM_DUMMY_STATEMENT(errorId);                              /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif

  return retCode;
}
#endif

#if (FIM_FEATURE_OBD == STD_ON)
/***********************************************************************************************************************
 *  FiM_DemTriggerOnEventStatus
 **********************************************************************************************************************/
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
*/
FUNC(void, FIM_CODE)  FiM_DemTriggerOnEventStatus
                       (Dem_EventIdType EventId,
                        Dem_UdsStatusByteType EventStatusOld,
                        Dem_UdsStatusByteType EventStatusNew
                       )                                                                               /*lint -e{529} */
{
  uint8 errorId = FIM_E_NO_ERROR;
  
#if (FIM_DEV_ERROR_DETECT == STD_ON)                                                         /* COV_FIM_DET_DETECT TX */
  /* #10 if FIM is not initialized skip rest of function */
  /* SlientBSW: check is silence relevant */
  if (FiM_InitializationStatus != FIM_INITIALIZED)
  {
    errorId = FIM_E_UNINIT;
  }
  /* #20 otherwise */
  else
#endif
  {
    /* #30 if passed event id is not FIM_DEM_EVENT_INVALID */
    if (EventId != FIM_DEM_EVENT_INVALID)
    {
      FiM_EventIdTableIndexType evTableIdx;
      boolean                   pendingStatusNew = FALSE;
      boolean                   pendingStatusOld = FALSE;
      uint8                     modCode          = FIM_FID_DEC;
      if((EventStatusNew & DEM_UDS_STATUS_PDTC) == DEM_UDS_STATUS_PDTC)
      {
        pendingStatusNew = TRUE;
        modCode          = FIM_FID_INC;
      }
      if((EventStatusOld & DEM_UDS_STATUS_PDTC) == DEM_UDS_STATUS_PDTC)
      {
        pendingStatusOld = TRUE;
      }

      /* #40 if the pending status bit changed (we're only interested in changes of this status bit) */
      if (pendingStatusNew != pendingStatusOld)
      {
        /* #50 search for event (i.e. is event known/configured in FIM?) */
        /* Silent:
            SBSW_FIM_SEARCHIDFUNC_EVTABLEIDX_PTR:
                      - pointer to local stack variale of type FiM_EventIdTableIndexType
            SBSW_FIM_SEARCHIDFUNC_PTR:
                      - initialization status is checked above
                      - in FiM_Init function pointer is always set */
        boolean evFound = (*FiM_SearchEventIdTableFct)                                   /* SBSW_FIM_SEARCHIDFUNC_PTR */
                           (EventId, &evTableIdx, FIM_EVENTIDPENDING_TABLE);
        /* #60 if event was found */
        if (evFound == TRUE)
        {
          /* #70 calculate the pending status FIDs for this event */
          /*     (does not depend on inhibition cfg, just linked to dummy inhibition cfg) */
          FiM_CalcPendingStatusOfEvent(evTableIdx, modCode);
        } /* if (evFound == TRUE) */
      } /* if (pendingStatusNew != pendingStatusOld) */
    } /* if (EventId != FIM_DEM_EVENT_INVALID) */
  }

#if (FIM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != FIM_E_NO_ERROR)
  {
    (void)Det_ReportError(FIM_MODULE_ID, FIM_INSTANCE_ID_DET,
                          FIM_SID_FIM_DEMTRIGGERONEVENTSTATUS, errorId);
  }
#else
  FIM_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif

  return;
}
#endif


/***********************************************************************************************************************
 *  FiM_DemTriggerOnMonitorStatus
 **********************************************************************************************************************/
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
FUNC(void, FIM_CODE)  FiM_DemTriggerOnMonitorStatus
                       (Dem_EventIdType EventId
                       )                                                                               /*lint -e{529} */
{
  uint8           errorId = FIM_E_NO_ERROR;

#if (FIM_DEV_ERROR_DETECT == STD_ON)                                                         /* COV_FIM_DET_DETECT TX */
  /* #10 if FIM is not initialized skip rest of function (SPEC-31918) */
  /* SilentBSW: check is silence relevant */
  if (FiM_InitializationStatus != FIM_INITIALIZED)
  {
    errorId = FIM_E_UNINIT;
  }
  /* #20 otherwise */
  else
#endif
  {
    /* #30 if passed event id is not FIM_DEM_EVENT_INVALID */
    if (EventId != FIM_DEM_EVENT_INVALID)
    {
      FiM_EventIdTableIndexType     evTableIdx;

      /* #40 search for event (i.e. is event known/configured in FIM?) */
      /* Silent:
          SBSW_FIM_SEARCHIDFUNC_EVTABLEIDX_PTR:
                    - pointer to local stack variale of type FiM_EventIdTableIndexType
          SBSW_FIM_SEARCHIDFUNC_PTR:
                    - initialization status is checked above
                    - in FiM_Init function pointer is always set */
      boolean evFound = (*FiM_SearchEventIdTableFct)                                     /* SBSW_FIM_SEARCHIDFUNC_PTR */
                         (EventId, &evTableIdx, FIM_EVENTID_TABLE);
      /* #50 if event was found */
      if (evFound == TRUE)
      {
        /* #60 calculate the inhibition states of this event */
        FiM_CalcInhibStatusOfEvent(evTableIdx);
      } /* if (evFound == TRUE) */
    } /* if (EventId != FIM_DEM_EVENT_INVALID) */
  }

#if (FIM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != FIM_E_NO_ERROR)
  {
    (void)Det_ReportError(FIM_MODULE_ID, FIM_INSTANCE_ID_DET,
                          FIM_SID_FIM_DEMTRIGGERONMONITORSTATUS, errorId);
  }
#else
  FIM_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif

  return;
}


/***********************************************************************************************************************
 *  FiM_MainFunction()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FIM_CODE) FiM_MainFunction(void)
{
}


#define FIM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/* module specific MISRA deviations:
   MD_FiM_8.7:
     Description: Rule 8.7
                  Objects shall be defined at block scope if they are only accessed from within a single function.
     Reason:      Vector style guide prevents usage of static variables in function scope
     Risk:        None.
     Prevention:  None.

   MD_FiM_16.4:
     Description: Rule 16.4
                  The identifiers used in the declaration and definition of a function shall be identical.
     Reason:      Conflicting prototype is generated by RTE. Currently there is no way to tell RTE the parameter name.
     Risk:        None.
     Prevention:  None.

   MD_FiM_0291:
     Description: Rule 0291
                  An integer expression with a value that is apparently negative is being converted to an unsigned type.
     Reason:      Previous check (scanIdx > loLimit) together with the fact that loLimit is unsigned guarantees that
                  scanIdx is at least 1.
     Risk:        None.
     Prevention:  None.
*/


/* COV_JUSTIFICATION_BEGIN
\ID COV_FIM_DET_DETECT
  \REASON For SafeBSW Error Detection is always switched on.

\ID COV_FIM_RUNTIME_CHECKS
  \ACCEPT TX
  \REASON For SafeBSW Runtime Checks are always switched on.

COV_JUSTIFICATION_END */ 


/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_FIM_COMPSWAPFUNC_ADDRESS_PTR
    \DESCRIPTION    Pointer write access to parameter addressPtr.
    \COUNTERMEASURE \N Compare and Swap function is internal and caller makes sure that a
                       valid pointer 'addressPtr' is passed.

\ID SBSW_FIM_BITMANIP_COMPSWAPFUNC_CALL
    \DESCRIPTION    Call of CompareAndSwap with pointer parameter.
    \COUNTERMEASURE \R A Runtime check ensures that the passed pointer is within array bounds.
                       Bit manipulation functions are internal and caller makes sure that a
                       valid pointer to word array is passed and that 'bitfieldWordArrSize'
                       does not exceed length of this word array.

\ID SBSW_FIM_BITMANIP_CALL
    \DESCRIPTION    Call of bit manipulation function with pointer to array and length of array as parameters.
    \COUNTERMEASURE \N Qualified use case CSL01 of ComStackLib.

\ID SBSW_FIM_BITTEST_CALL
    \DESCRIPTION    Call of bit test function with pointer to array.
    \COUNTERMEASURE \N Bit test function is internal and pointer is only used for read access.

\ID SBSW_FIM_SEARCHIDFUNC_EVTABLEIDX_PTR
    \DESCRIPTION    Pointer write access to out parameter evTableIdx.
    \COUNTERMEASURE \N Search functions are internal and pointer passed by caller always points to a local (stack)
                       variable. See also SBSW_FIM_SEARCHIDFUNC_PTR.

\ID SBSW_FIM_SEARCHIDFUNC_PTR
    \DESCRIPTION Call of function via function pointer.
    \COUNTERMEASURE \M Verify that FIM_DEV_ERROR_DETECT == STD_ON.
                       Then function checks whether initialization has been performed.
                       FiM_Init ensures that function pointer is always set to a valid function if initialization
                       has been performed.

\ID SBSW_FIM_DEMGETMONITORSTATUS_CALL
    \DESCRIPTION Call of Dem_GetMonitorStatus with pointer parameter.
    \COUNTERMEASURE \N Pointer to local variable of type Dem_MonitorStatusType is passed.

\ID SBSW_FIM_DEMGETEVENTUDSSTATUS_CALL
    \DESCRIPTION Call of Dem_GetEventUdsStatus with pointer parameter.
    \COUNTERMEASURE \N Pointer to local variable of type Dem_UdsStatusByteType is passed.

\ID SBSW_FIM_ACCESS_FIDPENDINGCOUNTER_CHECKED
    \DESCRIPTION    Access of FimFidPendingCounter using ComStackLib.
    \COUNTERMEASURE \M [CM_FIM_CSL01_ENABLE_RUNTIME_CHECKS]

\ID SBSW_FIM_ACCESS_INHSTATUS_CALCINHPENDSTATES
    \DESCRIPTION    Access of FimFidCounter using ComStackLib.
    \COUNTERMEASURE \N Qualified use case CSL01 of ComStackLib.

\ID SBSW_FIM_ACCESS_FIDPENDINGCOUNTER_CALCINHPENDSTATES
    \DESCRIPTION    Access of FimFidPendingCounter using ComStackLib.
    \COUNTERMEASURE \N Qualified use case CSL01 of ComStackLib.

\ID SBSW_FIM_VERSIONINFO_PTR
    \DESCRIPTION Pointer write access to versioninfo pointer variable in FiM_GetVersionInfo().
    \COUNTERMEASURE \N The application which uses this API has to make sure that a valid pointer to the parameter
                       versioninfo is passed.

\ID SBSW_FIM_PERMISSION_PTR
    \DESCRIPTION Pointer write access to permission pointer variable in FiM_GetFunctionPermission().
    \COUNTERMEASURE \N The application which uses this API has to make sure that a valid pointer to a variable
                       that can hold a boolean type is passed.

\ID SBSW_FIM_PENDINGSTATUS_PTR
    \DESCRIPTION Pointer write access to pending status pointer variable in FiM_GetFunctionPendingStatus().
    \COUNTERMEASURE \N The application which uses this API has to make sure that a valid pointer to a variable
                       that can hold a boolean type is passed.

SBSW_JUSTIFICATION_END */

/*

\CM CM_FIM_CSL01_ENABLE_RUNTIME_CHECKS
       Verify that FIM_DEV_RUNTIME_CHECKS == STD_ON.
       Then it's Qualified use case CSL01 of ComStackLib.

*/

/***********************************************************************************************************************
*  END OF FILE: FiM.c
***********************************************************************************************************************/
