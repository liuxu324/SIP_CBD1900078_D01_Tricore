/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  EthSwt_30_Sja1105PQRS_Time.c
 *        \brief  Source file containing the timestamping API
 *
 *      \details  The Ethernet Switch Driver allows to retrieve the timestamps of PTP frames received or transmitted
 *                at its ports. This module implements this functionality.
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

#define ETHSWT_30_SJA1105PQRS_TIME_SOURCE

/* QAC file deviation */
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */
/* PRQA S 779,777 IDENTIFIER_DIFFER */ /* MD_EthSwt_30_Sja1105PQRS_5.1 */
/* PRQA S 0781 EOF */ /* MD_EthSwt_30_Sja1105PQRS_781 */
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "EthSwt_30_Sja1105PQRS_Time.h"
#include "EthSwt_30_Sja1105PQRS_Mgmt.h"
#include "EthSwt_30_Sja1105PQRS.h"
#include "EthSwt_30_Sja1105PQRS_Int.h"
#include "EthSwt_30_Sja1105PQRS_Lcfg.h"
#include "EthSwt_30_Sja1105PQRS_Regs.h"
#include "EthSwt_30_Sja1105PQRS_Time_Int.h"
#include "EthSwt_30_Sja1105PQRS_Casc_Int.h"

#if ( ETHSWT_30_SJA1105PQRS_GLOBAL_TIME_SUPPORT == STD_ON )
# include "SchM_EthSwt_30_Sja1105PQRS.h"
# include "IpBase.h"
# include "EthIf_Cbk.h"
# if ( ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON )
#  include "Det.h"
# endif /* ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of EthSwt_30_Sja1105PQRS header file */
#if (  (ETHSWT_30_SJA1105PQRS_SW_MAJOR_VERSION != (0x05U)) \
    || (ETHSWT_30_SJA1105PQRS_SW_MINOR_VERSION != (0x00U)) \
    || (ETHSWT_30_SJA1105PQRS_SW_PATCH_VERSION != (0x01U)) )
# error "Vendor specific version numbers of EthSwt_30_Sja1105PQRS_Time.c and EthSwt_30_Sja1105PQRS.h are inconsistent"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

#if !defined (ETHSWT_LOCAL)
# define ETHSWT_LOCAL static
#endif

#if !defined (ETHSWT_LOCAL_INLINE)
# define ETHSWT_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/
#define ETHSWT_30_SJA1105PQRS_TIMESTAMP_TYPE_SECONDS_LOW_MAX         (0xFFFFFFFFul)
#define ETHSWT_30_SJA1105PQRS_NSEC_PER_SEC                           (1000000000ul)
#define ETHSWT_30_SJA1105PQRS_NSEC_PER_MILLISEC                      (1000000ul)
#define ETHSWT_30_SJA1105PQRS_PORT_TIME_STAMP_MAX                    (0x0000FFFFFFFFFFFFull)
#define ETHSWT_30_SJA1105PQRS_TS_LOWER_3_BYTES_MASK                  (0x0000000000FFFFFFull)
#define ETHSWT_30_SJA1105PQRS_TS_UPPER_5_BYTES_MASK                  (0xFFFFFFFFFF000000ull)
#define ETHSWT_30_SJA1105PQRS_SECONDS_MASK                           (0x00000000FFFFFFFFull)
#define ETHSWT_30_SJA1105PQRS_SECONDS_HIGH_MASK                      (0x0000FFFF00000000ull)
#define ETHSWT_30_SJA1105PQRS_PTPTSCLK_TO_NS_FACTOR                  (0x08u)
#define ETHSWT_30_SJA1105PQRS_PARTIAL_TS_EXISTS                      (0xFF000000u)
#define ETHSWT_30_SJA1105PQRS_PARTIAL_TS_EXISTANCE_MASK              (0xFF000000u)
#define ETHSWT_30_SJA1105PQRS_TS_ELEM_TIMEOUT_STOP                   (0xFFFFu)
#define ETHSWT_30_SJA1105PQRS_TS_ELEM_INV_BUF_IDX                    (0xFFu)
#define ETHSWT_30_SJA1105PQRS_MAX_OFFSET_SECONDS                     (((uint64) 0xFFFFFFFFFFFFFFFFull) / \
          (ETHSWT_30_SJA1105PQRS_NSEC_PER_SEC / ETHSWT_30_SJA1105PQRS_PTPTSCLK_TO_NS_FACTOR))
/*! Maximum rate that should be used for the PTPCTRL9 registers PTPCLKRATE field (as described in UM11040 for field
 *  CORRCLK4TS of register PTPCTRL1). */
#define ETHSWT_30_SJA1105PQRS_MAX_CLOCK_RATE                         (1.2)
/*! Minimum rate that should be used for PTPCTRL9 registers PTPCLKRATE field (no specific value given in UM11040 but
 *  analogous to ETHSWT_30_SJA1105PQRS_MAX_CLOCK_RATE the range is lowered by 0.2 beneath 1.0). */
#define ETHSWT_30_SJA1105PQRS_MIN_CLOCK_RATE                         (0.8)

typedef struct
{
  uint32   FixedPointValue;        /*!< Calculated fixed point value */
  float64  FixedAsFloatPointValue; /*!< Fixed point value represented as float (including resolution
                                        based errors) */
} EthSwt_30_Sja1105PQRS_Float2FixedTransType;

#define ETHSWT_30_SJA1105PQRS_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_IncProcElemIdx
 **********************************************************************************************************************/
/*! \brief          Increases the passed index according to the layout of the timestamp retrieval working queue layout
 *  \details        -
 *  \param[in,out]  elemIdx    Index to be increased (either current element index or free element index)
 *  \context        ANY
 *  \reentrant      TRUE
 *  \pre            -
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_IncProcElemIdx(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) elemIdx);

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_IsHostPort
 **********************************************************************************************************************/
/*! \brief          Checks if the port given in the management information is the port connected to the host CPU
 *  \details        -
 *  \param[in]      mgmtInfo    Management information containing the port information that shall be checked
 *  \return         FALSE - Port isn't the one connected to the host CPU
 *  \return         TRUE  - Port is the one connected to the host CPU
 *  \context        ANY
 *  \reentrant      TRUE
 *  \pre            -
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_IsHostPort(
  P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, AUTOMATIC) mgmtInfo);

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_InvalidateTsElem
 **********************************************************************************************************************/
/*! \brief          Invalidate the given timestamp processing element
 *  \details        -
 *  \param[in]      tsProcElem    Timestamp processing element to be invalidated
 *  \context        ANY
 *  \reentrant      TRUE
 *  \pre            -
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_InvalidateTsElem(
    P2VAR(EthSwt_30_Sja1105PQRS_TsProcElemType, AUTOMATIC, AUTOMATIC) tsProcElem);

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_QueueTsElem
 **********************************************************************************************************************/
/*! \brief          Queue the timestamp processing element into the working queue
 *  \details        -
 *  \param[in]      tsProcElem    Timestamp processing element to be queued
 *  \context        ANY
 *  \reentrant      TRUE
 *  \pre            -
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_QueueTsElem(
  P2VAR(EthSwt_30_Sja1105PQRS_TsProcElemType, AUTOMATIC, AUTOMATIC) tsProcElem);

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_DequeueTsElem
 **********************************************************************************************************************/
/*! \brief          Dequeue the timestamp processing element from the working queue
 *  \details        -
 *  \param[in]      tsProcElem    Timestamp processing element to be queued
 *  \context        ANY
 *  \reentrant      TRUE
 *  \pre            -
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_DequeueTsElem(
  P2VAR(EthSwt_30_Sja1105PQRS_TsProcElemType, AUTOMATIC, AUTOMATIC) tsProcElem);

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_FetchIngressTs
 **********************************************************************************************************************/
/*! \brief          Fetches the timestamp available on an integrated PHY port (ports 0-4)
 *  \details        -
 *  \param[in]      mgmtInfo     Management information containing the port the timestamp shall be retrieved from
 *  \param[out]     timestamp    Timestamp that was retrieved
 *  \context        ANY
 *  \reentrant      TRUE
 *  \pre            -
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_FetchIngressTs(
    P2VAR(EthSwt_30_Sja1105PQRS_TsProcElemType, AUTOMATIC, AUTOMATIC) tsProcElem);

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_FetchEgressTs
 **********************************************************************************************************************/
/*! \brief          Fetches the timestamp available on an integrated PHY port (ports 0-4)
 *  \details        -
 *  \param[in]      mgmtInfo     Management information containing the port the timestamp shall be retrieved from
 *  \param[out]     timestamp    Timestamp that was retrieved
 *  \context        ANY
 *  \reentrant      TRUE
 *  \pre            -
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_FetchEgressTs(
    P2VAR(EthSwt_30_Sja1105PQRS_TsProcElemType, AUTOMATIC, AUTOMATIC) tsProcElem);

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_ProcessTsElem
 **********************************************************************************************************************/
/*! \brief          Processes a timestamp processing element to retrieve the timestamps related to an frame
 *  \details        -
 *  \param[in]      tsProcElem    Management information containing the port the timestamp shall be retrieved from
 *  \return         FALSE - Processing isn't finished yet
 *  \return         TRUE  - Processing has finished
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_ProcessTsElem(
  P2VAR(EthSwt_30_Sja1105PQRS_TsProcElemType, AUTOMATIC, AUTOMATIC) tsProcElem);

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_StartPrepOfTxTsRetrieval
 **********************************************************************************************************************/
/*! \brief          Start the preparation of a timestamp processing element used to retrieve the timestamps of a frame
 *                  intended to be transmitted
 *  \details        -
 *  \param[in]      ethCtrlIdx    Identifier of the Ethernet controller the frame shall be transmitted on
 *  \param[in]      bufIdx        Identifier of the Frame buffer in context of the Ethernet controller used to transmit
 *                                the frame
 *  \param[in]      mgmtInfo      Management information containing on which port the frame shall be egressed
 *  \return         FALSE - no free elements in the timestamp processing pool
 *  \return         TRUE - element in timestamp processing pool could be allocated
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_StartPrepOfTxTsRetrieval(
          uint8                                      ethCtrlIdx,
          uint8                                      bufIdx,
  P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, AUTOMATIC) mgmtInfo,
          uint8                                      TsReg);

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_CombineTs
 **********************************************************************************************************************/
/*! \brief          Start the preparation of a timestamp processing element used to retrieve the timestamps of a frame
 *                  intended to be transmitted
 *  \details        -
 *  \param[in]      MgmtInfo               Management information containing on which port the frame shall be egressed
 *  \param[in,out]  CompleteTimestampPtr   Pointer to a timestamp, which shall be combined with the LowerTsPartPtr
 *  \param[in]      LowerTsPartPtr         Pointer to a partial timestamp, which shall be combined with the
 *                                         CompleteTimestampPtr to a complete timestamp
 *  \return         return whether combining the different timestamps was successful
 *  \context        ANY
 *  \reentrant      TRUE
 *  \pre            -
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_CombineTs(
    P2CONST(EthSwt_MgmtInfoType,   AUTOMATIC, AUTOMATIC) MgmtInfo,
    P2VAR(Eth_TimeStampType,       AUTOMATIC, AUTOMATIC) CompleteTimestampPtr,
    P2CONST(Eth_TimeStampType,     AUTOMATIC, AUTOMATIC) LowerTsPartPtr);

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_IsTsRegAvailable
 **********************************************************************************************************************/
/*! \brief          Check if timestamp register is available
 *  \details        -
 *  \param[in]      swtIdx         Identifier of the switch with the register which shall be checked
 *  \param[in]      portIdx        Index of the port whose timestamp register shall be checked
 *  \param[in]      tsReg          Number of timestamp register (0 or 1)
 *  \return         return whether whether the register is available
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_IsTsRegAvailable(
    uint8 swtIdx,
    uint8 portIdx,
    uint8 tsReg);

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_OccupyTsReg
 **********************************************************************************************************************/
/*! \brief          Occupy timestamp register
 *  \details        -
 *  \param[in]      swtIdx         Identifier of the switch with the register which shall be occupied
 *  \param[in]      portIdx        Index of the port whose timestamp register shall be occupied
 *  \param[in]      tsReg          Number of timestamp register (0 or 1)
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_OccupyTsReg(
    uint8 swtIdx,
    uint8 portIdx,
    uint8 tsReg);

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_FreeTsReg
 **********************************************************************************************************************/
/*! \brief          Free timestamp register
 *  \details        -
 *  \param[in]      swtIdx         Identifier of the switch with the register which shall be freed
 *  \param[in]      portIdx        Index of the port whose timestamp register shall be freed
 *  \param[in]      tsReg          Number of timestamp register (0 or 1)
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_FreeTsReg(
    uint8 swtIdx,
    uint8 portIdx,
    uint8 tsReg);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_PerformOffsetCorrection
 *********************************************************************************************************************/
/*! \brief          Performs a offset correction for a switch
 *  \details        -
 *  \param[in]      swtIdx         Identifier of the switch the offset shall be corrected for
 *  \param[in]      offsetTimePtr  Offset that the switch  shall be corrected with
 *  \return         E_OK - Offset correction was performed
 *  \return         E_NOT_OK - SPI access failed or offset has a value that can't be corrected (absolute correction to
 *                             big)
 *  \context        ANY
 *  \reentrant      TRUE
 *  \pre            -
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_PerformOffsetCorrection(
                 uint8                               swtIdx,
  ETHSWT_P2CONST(Eth_TimeIntDiffType,  SJA1105PQRS)  offsetTimePtr);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105_IsRateRatioInRange
 *********************************************************************************************************************/
/*! \brief          Checks if the given rate ratio is in a range the hardware can handle
 *  \details        -
 *  \param[in]      corrRateRatio  Floating point rate ratio value
 *  \return         FALSE - value is not in range and shall not be applied to register
 *  \return         TRUE - value is in range and can be used
 *  \context        ANY
 *  \reentrant      TRUE
 *  \pre            -
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105_IsRateRatioInRange(
  float64 corrRateRatio);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105_Float2Fixed
 *********************************************************************************************************************/
/*! \brief          Calculates the fixed point value for the registers based on a floating point value
 *  \details        -
 *  \param[in]      floatPointValue  Floating point rate ratio value
 *                                   [range: ETHSWT_30_SJA1105PQRS_MIN_CLOCK_RATE <
 *                                           floatPointValue <
 *                                           ETHSWT_30_SJA1105PQRS_MAX_CLOCK_RATE]
 *  \return         Result containing the fixed point value and its floating point representation (including errors
 *                  inducted due to resolution of fixed point value)
 *  \context        ANY
 *  \reentrant      TRUE
 *  \pre            -
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(EthSwt_30_Sja1105PQRS_Float2FixedTransType, SJA1105PQRS) EthSwt_30_Sja1105_Float2Fixed(
    float64 floatPointValue);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_PerformRateCorrection
 *********************************************************************************************************************/
/*! \brief          Performs a rate correction for a switch
 *  \details        -
 *  \param[in]      swtIdx        Identifier of the switch the offset shall be corrected for
 *  \param[in]      rateRatioPtr  Rate that the switch  shall be corrected with
 *  \return         E_OK - Rate correction was performed
 *  \return         E_NOT_OK - Spi access failed or rate ratio has a value that can't be corrected (is in a range the
 *                             hardware can't handle)
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_PerformRateCorrection(
                 uint8                   swtIdx,
  ETHSWT_P2CONST(float64,  SJA1105PQRS)  rateRatioPtr);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_IsTsRegAvailable
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_IsTsRegAvailable(
    uint8 swtIdx,
    uint8 portIdx,
    uint8 tsReg)
{
  /* #10 Return whether the TsReg passed as parameter is available */
  return (boolean)(((*EthSwt_30_Sja1105PQRS_InstanceConfig[swtIdx].TsProc->TsRegFlags) &
      (uint16)(1U << ((uint32)((uint32)ETHSWT_30_SJA1105PQRS_HW_PORT_TO_TSREG_FACTOR * portIdx) + tsReg))) != 0);
}

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_OccupyTsReg
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_OccupyTsReg(
    uint8 swtIdx,
    uint8 portIdx,
    uint8 tsReg)
{
  /* #10 Occupy the TsReg passed as parameter */
  *EthSwt_30_Sja1105PQRS_InstanceConfig[swtIdx].TsProc->TsRegFlags &=
      (uint16)~(uint32)(1U << ((uint32)((uint32)ETHSWT_30_SJA1105PQRS_HW_PORT_TO_TSREG_FACTOR * portIdx) + tsReg));
}

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_FreeTsReg
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_FreeTsReg(
    uint8 swtIdx,
    uint8 portIdx,
    uint8 tsReg)
{
  /* #10 Free the TsReg passed as parameter */
  *EthSwt_30_Sja1105PQRS_InstanceConfig[swtIdx].TsProc->TsRegFlags |=
      (uint16)(1U << ((uint32)((uint32)ETHSWT_30_SJA1105PQRS_HW_PORT_TO_TSREG_FACTOR * portIdx) + tsReg));
}

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_IncProcElemIdx
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_IncProcElemIdx(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) elemIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Ensure that passed processing index is increased in an atomar way) */
  /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_EnterExclusiveArea(Sja1105PQRS, TS_QUEUE_PROCESSING);

  /* #20 Increase index and handle an possible index overflow */
  (*elemIdx)++;

  if( (*elemIdx) == ETHSWT_30_SJA1105PQRS_MAX_PARALLEL_TS_EVENTS )
  {
    (*elemIdx) = 0;
  }

  /* #30 Leave exclusive area */
  /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_ExitExclusiveArea(Sja1105PQRS, TS_QUEUE_PROCESSING);
} /* EthSwt_30_Sja1105PQRS_IncProcElemIdx() */

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_IsHostPort
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_IsHostPort(
  P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, AUTOMATIC) mgmtInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean result;
  EthSwt_SwitchIdxType cascLvl0SwtIdx;
  EthSwt_PortIdxType cascLvl0MgmtPortIdx;

  /* ----- Implementation ----------------------------------------------- */
  result = FALSE;
  cascLvl0SwtIdx = EthSwt_30_Sja1105PQRS_GetIndexOfDirectlyConnectedSwitch();
  cascLvl0MgmtPortIdx = EthSwt_30_Sja1105PQRS_InstanceConfig[cascLvl0SwtIdx].FrameManagement->MgmtPortIdx;

  /* #10 Check if the passed management information represents the port to Host-CPU and if so
   *     indicate this to the caller */
  if( ( mgmtInfo->SwitchIdx == cascLvl0SwtIdx ) &&
      ( mgmtInfo->PortIdx == cascLvl0MgmtPortIdx ) )
  {
    result = TRUE;
  }

  return result;
} /* EthSwt_30_Sja1105PQRS_IsHostPort() */

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_InvalidateTsElem
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_InvalidateTsElem(
  P2VAR(EthSwt_30_Sja1105PQRS_TsProcElemType, AUTOMATIC, AUTOMATIC) tsProcElem)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Ensure consistency of timestamp processing queue and elements) */
  /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_EnterExclusiveArea(Sja1105PQRS, TS_QUEUE_PROCESSING);

  /* #20 Invalidate the element by setting respective invalid data */
  tsProcElem->State = ETHSWT_30_SJA1105PQRS_TS_ELEM_STATE_FREE;
  tsProcElem->ProcFlags = ETHSWT_30_SJA1105PQRS_TS_PROC_FLAG_CLEAR;
  tsProcElem->BufIdx = ETHSWT_30_SJA1105PQRS_TS_ELEM_INV_BUF_IDX;
  tsProcElem->DataPtr = NULL_PTR;
  tsProcElem->Timeout = ETHSWT_30_SJA1105PQRS_TS_ELEM_TIMEOUT_STOP;
  tsProcElem->EgrMgmtInfo.FrameId = ETH_INVALID_FRAME_ID;
  tsProcElem->IgrMgmtInfo.FrameId = ETH_INVALID_FRAME_ID;

  /* #30 Leave exclusive area */
  /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_ExitExclusiveArea(Sja1105PQRS, TS_QUEUE_PROCESSING);
} /* EthSwt_30_Sja1105PQRS_InvalidateTsElem() */

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_QueueTsElem
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_QueueTsElem(
  P2VAR(EthSwt_30_Sja1105PQRS_TsProcElemType, AUTOMATIC, AUTOMATIC) tsProcElem)
{
  /* ----- Local Variables ---------------------------------------------- */

  P2CONST(EthSwt_30_Sja1105PQRS_TsProcType, AUTOMATIC, AUTOMATIC) tsProcIgrSwt;
  P2CONST(EthSwt_30_Sja1105PQRS_TsProcType, AUTOMATIC, AUTOMATIC) tsProcEgrSwt;
  uint16 timeout;

  /* ----- Implementation ----------------------------------------------- */
  tsProcIgrSwt = EthSwt_30_Sja1105PQRS_InstanceConfig[tsProcElem->IgrMgmtInfo.SwitchIdx].TsProc;
  tsProcEgrSwt = EthSwt_30_Sja1105PQRS_InstanceConfig[tsProcElem->EgrMgmtInfo.SwitchIdx].TsProc;

  /* #10 Select the smaller timeout as timeout for the whole element */
  if( tsProcIgrSwt->TsTimeout < tsProcEgrSwt->TsTimeout )
  {
    timeout = tsProcIgrSwt->TsTimeout;
  }
  else
  {
    timeout = tsProcEgrSwt->TsTimeout;
  }

  /* #20 Enter exclusive area (Reason: Ensure consistency of timestamp processing queue and elements) */
  /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_EnterExclusiveArea(Sja1105PQRS, TS_QUEUE_PROCESSING);

  /* #30 Set processing state, timeout and processing flags and queue the element in processing queue */
  EthSwt_30_Sja1105PQRS_TsProcQueue[EthSwt_30_Sja1105PQRS_TsQueue_FreeProcElemIdx] = tsProcElem;
  tsProcElem->State = ETHSWT_30_SJA1105PQRS_TS_ELEM_STATE_QUEUED;
  tsProcElem->ProcFlags = ETHSWT_30_SJA1105PQRS_TS_PROC_FLAG_EGR_PENDING | ETHSWT_30_SJA1105PQRS_TS_PROC_FLAG_IGR_PENDING;
  tsProcElem->Timeout = timeout;
  EthSwt_30_Sja1105PQRS_IncProcElemIdx(&EthSwt_30_Sja1105PQRS_TsQueue_FreeProcElemIdx);

  /* #40 Leave exclusive area */
  /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_ExitExclusiveArea(Sja1105PQRS, TS_QUEUE_PROCESSING);
} /* EthSwt_30_Sja1105PQRS_QueueTsElem() */

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_DequeueTsElem
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_DequeueTsElem(
  P2VAR(EthSwt_30_Sja1105PQRS_TsProcElemType, AUTOMATIC, AUTOMATIC) tsProcElem)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  swtCfg;
  uint8 hwPortIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* retrieve the switch instance responsible for managing the frame */
  if( EthSwt_30_Sja1105PQRS_GetSwitchManagementInstance(tsProcElem->EthCtrlIdx, &swtCfg) == E_OK )
  {
    /* #10 Enter exclusive area (Reason: Ensure consistency of timestamp processing queue and elements) */
    /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
    /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
    EthSwt_EnterExclusiveArea(Sja1105PQRS, TS_QUEUE_PROCESSING);

    hwPortIdx = swtCfg->TransformPortIdx(tsProcElem->EgrMgmtInfo.PortIdx,
                                         ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_INTERNAL_VIEW);

    /* Free element in pool of TsRegs - may be used again */
    EthSwt_30_Sja1105PQRS_FreeTsReg(tsProcElem->EgrMgmtInfo.SwitchIdx, hwPortIdx, tsProcElem->TsReg);

    /* #20 Invalidate the element and remove dequeue it from processing queue */
    EthSwt_30_Sja1105PQRS_InvalidateTsElem(tsProcElem);

    EthSwt_30_Sja1105PQRS_TsProcQueue[EthSwt_30_Sja1105PQRS_TsQueue_CurProcElemIdx] = NULL_PTR;
    EthSwt_30_Sja1105PQRS_IncProcElemIdx(&EthSwt_30_Sja1105PQRS_TsQueue_CurProcElemIdx);

    /* #30 Leave exclusive area */
    /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
    /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
    EthSwt_ExitExclusiveArea(Sja1105PQRS, TS_QUEUE_PROCESSING);
  }
} /* EthSwt_30_Sja1105PQRS_DequeueTsElem() */

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_CombineTs
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_CombineTs(
    P2CONST(EthSwt_MgmtInfoType,   AUTOMATIC, AUTOMATIC) MgmtInfo,
    P2VAR(Eth_TimeStampType,       AUTOMATIC, AUTOMATIC) CompleteTimestampPtr,
    P2CONST(Eth_TimeStampType,     AUTOMATIC, AUTOMATIC) LowerTsPartPtr)
{

  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS) SpiTransaction;
  Std_ReturnType RetVal;

  RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(MgmtInfo->SwitchIdx, &SpiTransaction);

  if( RetVal == (Std_ReturnType)E_OK )
  {
    uint64 timerRegister;
    uint64 secondsTimer;
    uint32 lowerTsPart = LowerTsPartPtr->nanoseconds & (uint32)ETHSWT_30_SJA1105PQRS_TS_LOWER_3_BYTES_MASK;
    /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
    /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
    EthSwt_EnterExclusiveArea(Sja1105PQRS, TS_QUEUE_PROCESSING);

    /* #10 Read Lower and Upper Part of Switch Time (2 words) */
    SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_PTPCTRL7_REG_ADDR;
    SpiTransaction->WordNum = (uint16)2u;

    RetVal = EthSwt_30_Sja1105PQRS_LL_ReadBytesSync(MgmtInfo->SwitchIdx, SpiTransaction);

    timerRegister = (SpiTransaction->DataPtr[0] | ((uint64)(SpiTransaction->DataPtr[1]) << 32));

    (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(MgmtInfo->SwitchIdx, SpiTransaction);

    /* #20 decide whether a wraparound occurred */
    if( (timerRegister & ETHSWT_30_SJA1105PQRS_TS_LOWER_3_BYTES_MASK) >= lowerTsPart )
    {
      /* #200 No wraparound: Combine 3 bytes from META Frame / Egress TS register with upper 5 bytes from corrected global time register */
      timerRegister &= ETHSWT_30_SJA1105PQRS_TS_UPPER_5_BYTES_MASK;
      timerRegister |= lowerTsPart;
    }
    else
    {
      /* #210 Wraparound happened: subtract 1 from the upper 5 bytes of the TS */
      timerRegister = (timerRegister & ETHSWT_30_SJA1105PQRS_TS_UPPER_5_BYTES_MASK) >> 24;
      timerRegister--;
      timerRegister <<= 24;
      /* #220 Combine 3 bytes from META Frame / Egress TS register with upper 5 bytes from corrected global time register */
      timerRegister |= lowerTsPart;
    }

    secondsTimer = timerRegister / (uint64)(ETHSWT_30_SJA1105PQRS_NSEC_PER_SEC / ETHSWT_30_SJA1105PQRS_PTPTSCLK_TO_NS_FACTOR);

    CompleteTimestampPtr->nanoseconds = (uint32)((timerRegister % ((uint64)ETHSWT_30_SJA1105PQRS_NSEC_PER_SEC / (uint64)ETHSWT_30_SJA1105PQRS_PTPTSCLK_TO_NS_FACTOR))
                                          * ETHSWT_30_SJA1105PQRS_PTPTSCLK_TO_NS_FACTOR);
    CompleteTimestampPtr->seconds =   (uint32)(secondsTimer & ETHSWT_30_SJA1105PQRS_SECONDS_MASK);
    CompleteTimestampPtr->secondsHi = (uint16)((secondsTimer & ETHSWT_30_SJA1105PQRS_SECONDS_HIGH_MASK) >> 32);

    /*! Internal comment removed.
 *
 *
 *
 * */

    /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
    /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
    EthSwt_ExitExclusiveArea(Sja1105PQRS, TS_QUEUE_PROCESSING);

  }

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_CombineTs */

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_FetchIngressTs
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_FetchIngressTs(
    P2VAR(EthSwt_30_Sja1105PQRS_TsProcElemType, AUTOMATIC, AUTOMATIC) tsProcElem)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType RetVal = E_NOT_OK;
  P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, AUTOMATIC) mgmtInfo;
  P2VAR(Eth_TimeStampType, AUTOMATIC, AUTOMATIC) timestamp;

  /* ----- Implementation ----------------------------------------------- */
  /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_EnterExclusiveArea(Sja1105PQRS, TS_QUEUE_PROCESSING);
  mgmtInfo = &tsProcElem->IgrMgmtInfo;
  timestamp = &tsProcElem->IgrTs;

/* Is a timestamp available? Lowest 3 bytes of ns contain the partial timestamp register value,
 * highest byte contains information whether ts is valid */
  if( (timestamp->nanoseconds & ETHSWT_30_SJA1105PQRS_PARTIAL_TS_EXISTANCE_MASK) == ETHSWT_30_SJA1105PQRS_PARTIAL_TS_EXISTS )
  {
    /* Lower 3 bytes of the timestamp is already available - just add the upper 5 bytes and check for overflow */
      RetVal = EthSwt_30_Sja1105PQRS_CombineTs(mgmtInfo, timestamp, timestamp);
  }
  /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_ExitExclusiveArea(Sja1105PQRS, TS_QUEUE_PROCESSING);

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_FetchIngressTs() */

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_FetchEgressTs
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_FetchEgressTs(
    P2VAR(EthSwt_30_Sja1105PQRS_TsProcElemType, AUTOMATIC, AUTOMATIC) tsProcElem)
{
  /* ----- Local Variables ---------------------------------------------- */

  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS) SpiTransaction;
  Std_ReturnType RetVal = E_NOT_OK;
  Eth_TimeStampType LowerTsPart;
  uint8 TsReg;
  P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, AUTOMATIC) mgmtInfo;
  P2VAR(Eth_TimeStampType, AUTOMATIC, AUTOMATIC) timestamp;
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  swtCfg;
  uint8 hwPortIdx;

  /* ----- Implementation ----------------------------------------------- */

  /* retrieve the switch instance responsible for managing the frame */
  if( EthSwt_30_Sja1105PQRS_GetSwitchManagementInstance(tsProcElem->EthCtrlIdx, &swtCfg) == E_OK )
  {
    /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
    /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
    EthSwt_EnterExclusiveArea(Sja1105PQRS, TS_QUEUE_PROCESSING);

    mgmtInfo = &tsProcElem->EgrMgmtInfo;
    timestamp = &tsProcElem->EgrTs;
    TsReg = tsProcElem->TsReg;

    RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(mgmtInfo->SwitchIdx, &SpiTransaction);

    if( RetVal == (Std_ReturnType)E_OK )
    {
      /* convert to hw port idx */
      hwPortIdx = swtCfg->TransformPortIdx(mgmtInfo->PortIdx,
                                           ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_INTERNAL_VIEW);

      /* Calculate register address for port related egress timestamp register */
      SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_EGRESS_TS_REG_BASE_ADDR +
          (((ETHSWT_30_SJA1105PQRS_HW_PORT_TO_TSREG_FACTOR * hwPortIdx) + TsReg) *
              ETHSWT_30_SJA1105PQRS_EGRESS_TS_FACTOR);

      RetVal = EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(mgmtInfo->SwitchIdx, SpiTransaction);

      if( (RetVal == E_OK) && ((SpiTransaction->DataPtr[0] & ETHSWT_30_SJA1105PQRS_EGRESS_TS_REG_UPDATE_MASK) != 0) )
      {
        SpiTransaction->AddrIdx++;
        RetVal = EthSwt_30_Sja1105PQRS_LL_ReadBytesSync(mgmtInfo->SwitchIdx, SpiTransaction);

        if( RetVal == E_OK )
        {
          LowerTsPart.nanoseconds = SpiTransaction->DataPtr[0];

          /* Lower 3 bytes of the timestamp are already available - just add the upper 5 bytes and check for overflow */
          RetVal = EthSwt_30_Sja1105PQRS_CombineTs(mgmtInfo, timestamp, &LowerTsPart);
        }
      }

      (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(mgmtInfo->SwitchIdx, SpiTransaction);
    }
    /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
    /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
    EthSwt_ExitExclusiveArea(Sja1105PQRS, TS_QUEUE_PROCESSING);
  }

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_FetchEgressTs() */

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_ProcessTsElem
 **********************************************************************************************************************/
/*! Internal comment removed.
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
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_ProcessTsElem(
  P2VAR(EthSwt_30_Sja1105PQRS_TsProcElemType, AUTOMATIC, AUTOMATIC) tsProcElem)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean result;

  /* ----- Implementation ----------------------------------------------- */
  result = FALSE;

  /*! Internal comment removed.
 *
 *
 *
 *
   */

  /* #10 Check if ingress timestamp retrieval is pending */
  if( ((uint32)tsProcElem->ProcFlags & (uint32)ETHSWT_30_SJA1105PQRS_TS_PROC_FLAG_IGR_PENDING) != 0 )
  {
    /* #100 If timestamp must be retrieved for Host-Port */
    if( EthSwt_30_Sja1105PQRS_IsHostPort((P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, AUTOMATIC))&tsProcElem->IgrMgmtInfo) == TRUE )
    {
      /* #1000 Indicate missing time stamp with NULL_PTR (currently available hardware revision doesn't support
       *       timestamping on the Host-Port) and end ingress timestamp retrieval processing */
      EthIf_SwitchIngressTimeStampIndication(tsProcElem->EthCtrlIdx, tsProcElem->DataPtr, &tsProcElem->IgrMgmtInfo, NULL_PTR);
      tsProcElem->ProcFlags &= (EthSwt_30_Sja1105PQRS_TsProcFlagsType)(~(uint32)ETHSWT_30_SJA1105PQRS_TS_PROC_FLAG_IGR_PENDING);
    }
    /* #110 Otherwise the timestamp must be retrieved for an external port */
    else
    {
      /* #1100 Check if the timestamp is already available */
      if( EthSwt_30_Sja1105PQRS_FetchIngressTs(tsProcElem) == E_OK )
      {
        /* #11000 Get the timestamp, indicate the availability to EthIf and end ingress timestamp retrieval processing */
        EthIf_SwitchIngressTimeStampIndication(tsProcElem->EthCtrlIdx, tsProcElem->DataPtr, &tsProcElem->IgrMgmtInfo, &tsProcElem->IgrTs);
        tsProcElem->ProcFlags &= (EthSwt_30_Sja1105PQRS_TsProcFlagsType)(~(uint32)ETHSWT_30_SJA1105PQRS_TS_PROC_FLAG_IGR_PENDING);
      }
    }
  }

  /* #20 Check if egress timestamp retrieval is pending */
  if( ((uint32)tsProcElem->ProcFlags & (uint32)ETHSWT_30_SJA1105PQRS_TS_PROC_FLAG_EGR_PENDING) != 0 )
  {
    /* #200 If timestamp must be retrieved for Host-Port */ /* PRQA S 0310 1 */ /* MD_EthSwt_30_Sja1105PQRS_0310_FrameId */
    if( EthSwt_30_Sja1105PQRS_IsHostPort((P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, AUTOMATIC))&tsProcElem->EgrMgmtInfo) == TRUE )
    {
      /* #2000 Indicate missing time stamp with NULL_PTR (currently available hardware revision doesn't support
       *       timestamping on the Host-Port) and end egress timestamp retrieval processing */
      EthIf_SwitchEgressTimeStampIndication(tsProcElem->EthCtrlIdx, tsProcElem->DataPtr, &tsProcElem->EgrMgmtInfo, NULL_PTR);
      tsProcElem->ProcFlags &= (EthSwt_30_Sja1105PQRS_TsProcFlagsType)(~(uint32)ETHSWT_30_SJA1105PQRS_TS_PROC_FLAG_EGR_PENDING);
    }
    /* #210 Otherwise the timestamp must be retrieved for an external port */
    else
    {
      /* #2100 Check if the timestamp is already available */
      if( EthSwt_30_Sja1105PQRS_FetchEgressTs(tsProcElem) == E_OK )
      {
        /* #21000 Get the timestamp, indicate the availability to EthIf and end egress timestamp retrieval processing */
        EthIf_SwitchEgressTimeStampIndication(tsProcElem->EthCtrlIdx, tsProcElem->DataPtr, &tsProcElem->EgrMgmtInfo, &tsProcElem->EgrTs);
        tsProcElem->ProcFlags &= (EthSwt_30_Sja1105PQRS_TsProcFlagsType)(~(uint32)ETHSWT_30_SJA1105PQRS_TS_PROC_FLAG_EGR_PENDING);
      }
    }
  }

  /* #30 Check if processing of element has finished and if so indicate it to the caller */
  if( tsProcElem->ProcFlags == ETHSWT_30_SJA1105PQRS_TS_PROC_FLAG_CLEAR )
  {
    result = TRUE;
  }

  return result;
} /* EthSwt_30_Sja1105PQRS_ProcessTsElem() */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_PerformOffsetCorrection
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_PerformOffsetCorrection(
                 uint8                               swtIdx,
  ETHSWT_P2CONST(Eth_TimeIntDiffType,  SJA1105PQRS)  offsetTimePtr)
{
  Std_ReturnType retVal;
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS) SpiTransaction;

  retVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(swtIdx, &SpiTransaction);

  if( retVal == E_OK )
  {
    uint64 OffsetSwtValue;
    uint64 SecondsOffset;
    ETHSWT_P2VAR(uint32, SJA1105PQRS) ptpCtrl1RegRamMirror = EthSwt_30_Sja1105PQRS_InstanceConfig[swtIdx].QbvHandling->PtpCtrl1RegRamMirror;

    /* #10 Enter exclusive area (Reason: Consistency of date retrieved and set in consecutive SPI transactions that must
     *                                   not be interrupted) */
    /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
    EthSwt_EnterExclusiveArea(Sja1105PQRS, SET_CORRECTION_TIME);

    /* #20 Prepare register for time offset correction */
    if( offsetTimePtr->sign == FALSE )
    {
      (*ptpCtrl1RegRamMirror) |= ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_PTPCLKSUB_MASK;
    }
    else
    {
      (*ptpCtrl1RegRamMirror) |= ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_PTPCLKADD_MASK;
    }
    SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_ADDR;
    SpiTransaction->DataPtr[0] = (*ptpCtrl1RegRamMirror);
    retVal |= EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(swtIdx, SpiTransaction);

    /* #30 Prepare offset correction time parameters */
    SecondsOffset = ((offsetTimePtr->diff.seconds) | ((uint64)offsetTimePtr->diff.secondsHi << 32));

    /* #40 Check for overflow */
    if( SecondsOffset <= ETHSWT_30_SJA1105PQRS_MAX_OFFSET_SECONDS )
    {
      OffsetSwtValue  = (uint64)(offsetTimePtr->diff.nanoseconds / (uint64)ETHSWT_30_SJA1105PQRS_PTPTSCLK_TO_NS_FACTOR);
      OffsetSwtValue += (SecondsOffset * ((uint64) ETHSWT_30_SJA1105PQRS_NSEC_PER_SEC / (uint64)ETHSWT_30_SJA1105PQRS_PTPTSCLK_TO_NS_FACTOR));

      /* #400 Write offset correction to switch */
      SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_PTPCTRL7_REG_ADDR;
      SpiTransaction->WordNum = 2u;
      SpiTransaction->DataPtr[0] = (uint32)OffsetSwtValue;
      SpiTransaction->DataPtr[1] = (uint32)(OffsetSwtValue >> 32u);
      retVal |= EthSwt_30_Sja1105PQRS_LL_WriteBytesSync(swtIdx, SpiTransaction);
    }
    else
    {
      retVal = E_NOT_OK;
    }

    /* #50 Clear offset correction action again */
    (*ptpCtrl1RegRamMirror) &= ~(ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_PTPCLKSUB_MASK | ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_PTPCLKADD_MASK);
    SpiTransaction->DataPtr[0] = (*ptpCtrl1RegRamMirror);
    SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_ADDR;
    retVal |= EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(swtIdx, SpiTransaction);

    (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(swtIdx, SpiTransaction);

    /* #60 Leave exclusive area */
    /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
    EthSwt_ExitExclusiveArea(Sja1105PQRS, SET_CORRECTION_TIME);
  }

  return retVal;
} /* EthSwt_30_Sja1105PQRS_PerformOffsetCorrection() */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105_IsRateRatioInRange
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105_IsRateRatioInRange(
    float64 corrRateRatio)
{
  boolean result = FALSE;

  /* #10 Check if value is expected range */
  if( (corrRateRatio > ETHSWT_30_SJA1105PQRS_MIN_CLOCK_RATE) &&
      (corrRateRatio < ETHSWT_30_SJA1105PQRS_MAX_CLOCK_RATE)    )
  {
    result = TRUE;
  }

  return result;
} /* EthSwt_30_Sja1105_IsRateRatioInRange() */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105_Float2Fixed
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(EthSwt_30_Sja1105PQRS_Float2FixedTransType, SJA1105PQRS) EthSwt_30_Sja1105_Float2Fixed(
    float64 floatPointValue)
{
  EthSwt_30_Sja1105PQRS_Float2FixedTransType calcResult;
  uint32_least fracPartPos;

  /* #10 Calculate integer part of fixed point value (only first bit) by transforming the floating point value to
   *     an integer value and shifting the result to the correct position. */
  calcResult.FixedPointValue = ((uint32)floatPointValue) << ETHSWT_30_SJA1105PQRS_PTPCTRL9_REG_INT_PART_SHIFT;
  calcResult.FixedAsFloatPointValue = (float64)((uint32)floatPointValue);

  /* #20 Take the remaining fraction part of the floating point value and transform it to the fixed point value
   *     remaining part by calculating each bits significance and if it is needed to display the floating point value
   *     till all bits are taken into account. */
  floatPointValue -= (float64)((uint32)floatPointValue);
  for( fracPartPos = 0u; fracPartPos < ETHSWT_30_SJA1105PQRS_PTPCTRL9_REG_INT_PART_SHIFT; fracPartPos++ )
  {
    /* Although the index runs from 0 -> 30 we are calculating the bit significances of the fraction part from 2^-1 to 2^-31 */
    float64 bitSignificance = ((float64)1 / (float64)((uint32)2 << fracPartPos));

    if( (floatPointValue - bitSignificance) >= 0)
    {
      calcResult.FixedPointValue |= 1u << (uint32)(((sint32)ETHSWT_30_SJA1105PQRS_PTPCTRL9_REG_INT_PART_SHIFT - 1) - (sint32)fracPartPos);
      calcResult.FixedAsFloatPointValue += bitSignificance;

      floatPointValue -= bitSignificance;
    }
  }

  return calcResult;
} /* EthSwt_30_Sja1105_Float2Fixed() */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_PerformRateCorrection
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_PerformRateCorrection(
                 uint8                   swtIdx,
  ETHSWT_P2CONST(float64,  SJA1105PQRS)  rateRatioPtr)
{
  Std_ReturnType retVal = E_NOT_OK;
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType,  SJA1105PQRS) swtCfg = &EthSwt_30_Sja1105PQRS_InstanceConfig[swtIdx];
  float64 corrRateRatio = (*swtCfg->QbvHandling->CurRateRatio);

  /* #10 Calculate the resulting rate ratio when relative correction is applied */
  corrRateRatio *= (*rateRatioPtr);

  /* #20 Trigger check if resulting rate ratio can be applied to register */
  if( EthSwt_30_Sja1105_IsRateRatioInRange(corrRateRatio) == TRUE )
  {
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS) spiTract;

    retVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(swtIdx, &spiTract);

    if( retVal == E_OK )
    {
      /* #200 Trigger transformation of floating point value to fixed point value that must be written to the register */
      EthSwt_30_Sja1105PQRS_Float2FixedTransType calcResult;
      calcResult = EthSwt_30_Sja1105_Float2Fixed(corrRateRatio);

      spiTract->AddrIdx    = (uint32)ETHSWT_30_SJA1105PQRS_PTPCTRL9_REG_ADDR;
      spiTract->DataPtr[0] = calcResult.FixedPointValue;

      /* #210 Update register */
      retVal |= EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(swtIdx, spiTract);

      if( retVal == E_OK )
      {
        /* #220 Store the floating point representation of the fixed point value for next correction cycle
         *      (this will prevent errors inducted due to resolution errors when transforming from floating to fixed point
         *       value but calculating with the floating point value all the time) */
        (*swtCfg->QbvHandling->CurRateRatio) = calcResult.FixedAsFloatPointValue;
      }
      (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(swtIdx, spiTract);
    }
  }

  return retVal;
} /* EthSwt_30_Sja1105PQRS_PerformRateCorrection() */

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_StartPrepOfTxTsRetrieval
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_StartPrepOfTxTsRetrieval(
          uint8                                      ethCtrlIdx,
          uint8                                      bufIdx,
  P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, AUTOMATIC) mgmtInfo,
          uint8                                      TsReg)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least elemIdx;
  boolean     result;

  /* ----- Implementation ----------------------------------------------- */
  result = FALSE;

  /* #10 Enter exclusive area (Reason: Ensure consistency of timestamp processing queue and elements) */
  /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_EnterExclusiveArea(Sja1105PQRS, TS_QUEUE_PROCESSING);

  /* #20 Query for a free timestamp processing element */
  for( elemIdx = 0; elemIdx < ETHSWT_30_SJA1105PQRS_MAX_PARALLEL_TS_EVENTS; elemIdx++ )
  {
    if( EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].State == ETHSWT_30_SJA1105PQRS_TS_ELEM_STATE_FREE )
    {
      /* #200 Free element found -> Set it up for later usage */
      EthSwt_SwitchIdxType cascLvl0SwtIdx = EthSwt_30_Sja1105PQRS_GetIndexOfDirectlyConnectedSwitch();
      EthSwt_PortIdxType   cascLvl0MgmtPortIdx = EthSwt_30_Sja1105PQRS_InstanceConfig[cascLvl0SwtIdx].FrameManagement->MgmtPortIdx;

      EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].State = ETHSWT_30_SJA1105PQRS_TS_ELEM_STATE_ALLOC;
      EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].EthCtrlIdx = ethCtrlIdx;
      EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].BufIdx                = bufIdx;

      EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].IgrMgmtInfo.SwitchIdx = cascLvl0SwtIdx;
      EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].IgrMgmtInfo.PortIdx   = cascLvl0MgmtPortIdx;
      EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].IgrMgmtInfo.FrameId   = mgmtInfo->FrameId;
      EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].EgrMgmtInfo.SwitchIdx = mgmtInfo->SwitchIdx;
      EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].EgrMgmtInfo.PortIdx   = mgmtInfo->PortIdx;
      EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].EgrMgmtInfo.FrameId   = mgmtInfo->FrameId;

      EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].TsReg                 = TsReg;
      result = TRUE;
      break;
    }
  }
  /* #30 Leave exclusive area */
  /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_ExitExclusiveArea(Sja1105PQRS, TS_QUEUE_PROCESSING);

  return result;
} /* EthSwt_30_Sja1105PQRS_StartPrepOfTxTsRetrieval() */

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_FinalizePrepOfTxTsRetrieval
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_FinalizePrepOfTxTsRetrieval(
        uint8                                                     ethCtrlIdx,
        uint8                                                     bufIdx,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC)                              dataPtr,
  P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, AUTOMATIC)              mgmtInfo,
  P2CONST(EthSwt_30_Sja1105PQRS_TsProcElemType, AUTOMATIC, AUTOMATIC) *TsProcElemPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least elemIdx;

  /* ----- Implementation ----------------------------------------------- */
  *TsProcElemPtr = NULL_PTR;

  /* #10 Query for the respective timestamp processing element */
  for( elemIdx = 0; elemIdx < ETHSWT_30_SJA1105PQRS_MAX_PARALLEL_TS_EVENTS; elemIdx++ )
  {
    if( (EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].EthCtrlIdx          == ethCtrlIdx)        &&
        (EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].BufIdx              == bufIdx)            &&
        (EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].EgrMgmtInfo.FrameId == mgmtInfo->FrameId)    )
    {
      /* #100 Element found -> Check if buffer release is requested or normal transmit is triggered.
       *                      Dependent on that either release the element or store the passed data. */

      EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].DataPtr = dataPtr;
      *TsProcElemPtr = &EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx];

      break;
    }
  }
} /* EthSwt_30_Sja1105PQRS_FinalizePrepOfTxTsRetrieval() */

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_InitiateTxTsRetrieval
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_InitiateTxTsRetrieval(
  uint8 ethCtrlIdx,
  uint8 bufIdx,
  P2CONST(EthSwt_MgmtInfoType, AUTOMATIC, AUTOMATIC)  mgmtInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  swtCfg;
  uint8_least elemIdx;
  uint8 hwPortIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Query for the respective timestamp processing element */
  for( elemIdx = 0; elemIdx < ETHSWT_30_SJA1105PQRS_MAX_PARALLEL_TS_EVENTS; elemIdx++ )
  {
    if( (EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].EthCtrlIdx == ethCtrlIdx) &&
        (EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].BufIdx == bufIdx)         &&
        (EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].EgrMgmtInfo.FrameId == mgmtInfo->FrameId)    )
    {
      if( EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].DataPtr == NULL_PTR )
      {
        /* retrieve the switch instance responsible for managing the frame */
        if( EthSwt_30_Sja1105PQRS_GetSwitchManagementInstance(EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].EthCtrlIdx, &swtCfg) == E_OK )
        {
          hwPortIdx = swtCfg->TransformPortIdx(EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].EgrMgmtInfo.PortIdx,
                                               ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_INTERNAL_VIEW);

          /* Free element in pool of TsRegs - may be used again */
          EthSwt_30_Sja1105PQRS_FreeTsReg(EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].EgrMgmtInfo.SwitchIdx,
                                          hwPortIdx,
                                          EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].TsReg);
        }

        EthSwt_30_Sja1105PQRS_InvalidateTsElem(&EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx]);
      }
      else
      {
        /* #100 Element found -> Queue it into the processing queue */
        EthSwt_30_Sja1105PQRS_QueueTsElem(&EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx]);
      }
      break;
    }
  }
} /* EthSwt_30_Sja1105PQRS_InitiateTxTsRetrieval() */

/***********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_InitiateRxTsRetrieval
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_InitiateRxTsRetrieval(
          uint8                                                     ethCtrlIdx,
    P2VAR(uint8,                              AUTOMATIC, AUTOMATIC) dataPtr,
  P2CONST(EthSwt_MgmtInfoType,                AUTOMATIC, AUTOMATIC) mgmtInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least elemIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Ensure consistency of timestamp processing queue and elements) */
  /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_EnterExclusiveArea(Sja1105PQRS, TS_QUEUE_PROCESSING);

  /* #20 Query for a free timestamp processing element */
  for( elemIdx = 0; elemIdx < ETHSWT_30_SJA1105PQRS_MAX_PARALLEL_TS_EVENTS; elemIdx++ )
  {
    if( EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].State == ETHSWT_30_SJA1105PQRS_TS_ELEM_STATE_FREE )
    {
      EthSwt_30_Sja1105PQRS_MetaFrame *MetaFramePtr;
      ETHSWT_P2VAR(uint8, SJA1105PQRS) MetaInformationPtr;

      /* #200 Free element found -> Set it up for usage */
      EthSwt_SwitchIdxType cascLvl0SwtIdx = EthSwt_30_Sja1105PQRS_GetIndexOfDirectlyConnectedSwitch();
      EthSwt_PortIdxType   cascLvl0MgmtPortIdx = EthSwt_30_Sja1105PQRS_InstanceConfig[cascLvl0SwtIdx].FrameManagement->MgmtPortIdx;

      EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].State = ETHSWT_30_SJA1105PQRS_TS_ELEM_STATE_ALLOC;
      EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].EthCtrlIdx = ethCtrlIdx;
      EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].DataPtr = dataPtr;
      EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].BufIdx  = ETHSWT_30_SJA1105PQRS_TS_ELEM_INV_BUF_IDX;

      EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].IgrMgmtInfo.SwitchIdx = mgmtInfo->SwitchIdx;
      EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].IgrMgmtInfo.PortIdx = mgmtInfo->PortIdx;
      EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].IgrMgmtInfo.FrameId = mgmtInfo->FrameId;
      EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].EgrMgmtInfo.SwitchIdx = cascLvl0SwtIdx;
      EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].EgrMgmtInfo.PortIdx = cascLvl0MgmtPortIdx;
      EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].EgrMgmtInfo.FrameId = mgmtInfo->FrameId;

      MetaInformationPtr = &(EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].DataPtr)[ETHSWT_30_SJA1105PQRS_META_DATA_PTR_OFFSET];
      MetaFramePtr = (EthSwt_30_Sja1105PQRS_MetaFrame*)MetaInformationPtr;  /* PRQA S 0310 */ /* MD_EthSwt_30_Sja1105PQRS_0310_FrameId */

      /* Save the lower 3 bytes of the timestamp register - Upper 5 Byte will be added later */
      EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].IgrTs.nanoseconds = \
          ((uint32)MetaFramePtr->Timestamp0 << 16) | ((uint32)MetaFramePtr->Timestamp1 << 8) | MetaFramePtr->Timestamp2;

      /* Write pattern to highest byte of timestamp field to mark it as correctly prepared */
      EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx].IgrTs.nanoseconds |= ETHSWT_30_SJA1105PQRS_PARTIAL_TS_EXISTS;

      /* #210 Queue element into processing queue */
      EthSwt_30_Sja1105PQRS_QueueTsElem(&EthSwt_30_Sja1105PQRS_TsProcPool[elemIdx]);
      break;
    }
  }

  /* #30 Leave exclusive area */
  /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  EthSwt_ExitExclusiveArea(Sja1105PQRS, TS_QUEUE_PROCESSING);
} /* EthSwt_30_Sja1105PQRS_InitiateRxTsRetrieval() */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_SynchronizeSwitchToCasMaster
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_SynchronizeSwitchToCasMaster(
  uint8 syncSwtIdx)
{
  Std_ReturnType retVal;
  uint8 casMasterSwtIdx;
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS) spiTransCasMasterSwt;
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS) spiTransSyncSwt;

  casMasterSwtIdx = EthSwt_30_Sja1105PQRS_GetIndexOfDirectlyConnectedSwitch();

  retVal  = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(casMasterSwtIdx, &spiTransCasMasterSwt);
  retVal |= EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(syncSwtIdx, &spiTransSyncSwt);

  if( retVal == E_OK )
  {
    ETHSWT_P2VAR(uint32, SJA1105PQRS) casMasterPtpCtrl1RegRamMirror = EthSwt_30_Sja1105PQRS_InstanceConfig[casMasterSwtIdx].QbvHandling->PtpCtrl1RegRamMirror;

    /* #10 Trigger sampling of timestamps for both switches by utilizing the sync line */
    spiTransCasMasterSwt->AddrIdx     = (uint32)ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_ADDR;
    (*casMasterPtpCtrl1RegRamMirror) |= ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_CASSYNC_MASK;
    spiTransCasMasterSwt->DataPtr[0]  = (*casMasterPtpCtrl1RegRamMirror);
    retVal |= EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(casMasterSwtIdx, spiTransCasMasterSwt);

    retVal |= EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(casMasterSwtIdx, spiTransCasMasterSwt);

    /* #20 Check if sampling was done */
    if( (spiTransCasMasterSwt->DataPtr[0] & ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_VALID_MASK) == 0 )
    {
      Eth_TimeIntDiffType timeDiff;
      sint64 offsetNs;
      uint64 tsCasMasterSwt;
      uint64 tsSyncSwt;
      uint64 unsignedOffsetNs;

      /* #210 Read sampled timestamps of master switch and switch to synchronize */
      spiTransCasMasterSwt->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_PTPCTRL13_REG_ADDR;
      spiTransCasMasterSwt->WordNum = (uint16)2u;
      retVal |= EthSwt_30_Sja1105PQRS_LL_ReadBytesSync(casMasterSwtIdx, spiTransCasMasterSwt);
      tsCasMasterSwt = ((((uint64)spiTransCasMasterSwt->DataPtr[1]) << 32) |
                          (uint64)spiTransCasMasterSwt->DataPtr[0]);

      spiTransSyncSwt->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_PTPCTRL13_REG_ADDR;
      spiTransSyncSwt->WordNum = (uint16)2u;
      retVal |= EthSwt_30_Sja1105PQRS_LL_ReadBytesSync(syncSwtIdx, spiTransSyncSwt);
      tsSyncSwt = ((((uint64)spiTransSyncSwt->DataPtr[1]) << 32) |
                     (uint64)spiTransSyncSwt->DataPtr[0]);

      /* #220 Calculate time offset between the switches */
      offsetNs = (sint64)((tsCasMasterSwt - tsSyncSwt) * ETHSWT_30_SJA1105PQRS_PTPTSCLK_TO_NS_FACTOR);
      if( offsetNs >= 0 )
      {
        timeDiff.sign = TRUE;
        unsignedOffsetNs = (uint64) offsetNs;
      }
      else
      {
        timeDiff.sign = FALSE;
        unsignedOffsetNs = (uint64) (-offsetNs);
      }


      timeDiff.diff.nanoseconds = (uint32)(unsignedOffsetNs % ETHSWT_30_SJA1105PQRS_NSEC_PER_SEC);
      timeDiff.diff.seconds     = (uint32)(unsignedOffsetNs / ETHSWT_30_SJA1105PQRS_NSEC_PER_SEC) &
                                           ETHSWT_30_SJA1105PQRS_TIMESTAMP_TYPE_SECONDS_LOW_MAX;
      timeDiff.diff.secondsHi   = (uint16)((unsignedOffsetNs / ETHSWT_30_SJA1105PQRS_NSEC_PER_SEC) >> 32);

      /* #230 Perform offset correction in switch to synchronize to align it to the master switch */
      retVal |= EthSwt_30_Sja1105PQRS_SetCorrectionTime(syncSwtIdx, &timeDiff, NULL_PTR);
    }

    /* #30 Deassert sync line again */
    spiTransCasMasterSwt->AddrIdx     = (uint32)ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_ADDR;
    (*casMasterPtpCtrl1RegRamMirror) &= ~ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_CASSYNC_MASK;
    spiTransCasMasterSwt->DataPtr[0]  = (*casMasterPtpCtrl1RegRamMirror);
    retVal |= EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(casMasterSwtIdx, spiTransCasMasterSwt);

    (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(casMasterSwtIdx, spiTransCasMasterSwt);
    (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(syncSwtIdx, spiTransSyncSwt);
  }

  return retVal;
} /* EthSwt_30_Sja1105PQRS_SynchronizeSwitchToCasMaster() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_TimeInit
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_TimeInit( void )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least SwitchIdx;
  uint8_least ElemIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize processing queue indices */
  EthSwt_30_Sja1105PQRS_TsQueue_FreeProcElemIdx = 0;
  EthSwt_30_Sja1105PQRS_TsQueue_CurProcElemIdx = 0;

  /* #20 Initialize timestamp processing elements */
  for( SwitchIdx = 0; SwitchIdx < ETHSWT_30_SJA1105PQRS_SWITCH_NUM; SwitchIdx++ )
  {
    uint8_least portIdx;

    for( portIdx = 0; portIdx < EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].PortNum; portIdx++ )
    {
      EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].TsProc->PortTs[portIdx].LastTimeStamp = 0;
      EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].TsProc->PortTs[portIdx].SwTime.nanoseconds = 0;
      EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].TsProc->PortTs[portIdx].SwTime.seconds = 0;
      EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].TsProc->PortTs[portIdx].SwTime.secondsHi = 0;
    }

    /* Mark all ten TsRegs as available (5 ports, 2 Egress Timestamp register per port */
    (*(EthSwt_30_Sja1105PQRS_InstanceConfig[SwitchIdx].TsProc->TsRegFlags)) = ETHSWT_30_SJA1105PQRS_ALL_TSREGS_AVAILABLE;
   }

  /* #30 Initialize processing queue */
  for( ElemIdx = 0; ElemIdx < ETHSWT_30_SJA1105PQRS_MAX_PARALLEL_TS_EVENTS; ElemIdx++ )
  {
    EthSwt_30_Sja1105PQRS_TsProcQueue[ElemIdx] = NULL_PTR;
    EthSwt_30_Sja1105PQRS_InvalidateTsElem(&EthSwt_30_Sja1105PQRS_TsProcPool[ElemIdx]);
  }

} /* EthSwt_30_Sja1105PQRS_TimeInit() */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_ConfigureQbv
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_ConfigureQbv(
  uint8 swtIdx)
{
  Std_ReturnType retVal;
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS) SpiTransaction;

  retVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(swtIdx, &SpiTransaction);

  if( retVal == E_OK )
  {
    ETHSWT_P2VAR(uint32,  SJA1105PQRS) ptpCtrl1RegRamMirror = EthSwt_30_Sja1105PQRS_InstanceConfig[swtIdx].QbvHandling->PtpCtrl1RegRamMirror;
    ETHSWT_P2VAR(float64, SJA1105PQRS) curRateRatio = EthSwt_30_Sja1105PQRS_InstanceConfig[swtIdx].QbvHandling->CurRateRatio;

    /* #10 Initialize PTP control 1 register so timestamps on ports are based on corrected global time */
    (*ptpCtrl1RegRamMirror) = ( ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_VALID_MASK      |
                                ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_CORRCLK4TS_MASK   );

    SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_ADDR;
    SpiTransaction->DataPtr[0] = (*ptpCtrl1RegRamMirror);
    retVal |= EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(swtIdx, SpiTransaction);

    /* #20 Initialize PTP control 9 register to the default rate of 1.0 */
    (*curRateRatio) = 1.0;
    SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_PTPCTRL9_REG_ADDR;
    SpiTransaction->DataPtr[0] = ETHSWT_30_SJA1105PQRS_PTPCTRL9_REG_DEFAULT_RATE;
    retVal |= EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(swtIdx, SpiTransaction);

    (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(swtIdx, SpiTransaction);
  }

  return retVal;
}

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_EnableEgressTimeStamp
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS)  EthSwt_30_Sja1105PQRS_EnableEgressTimeStamp(
                 uint8                              EthCtrlIdx,
                 uint8                              BufIdx,
  ETHSWT_P2CONST(EthSwt_MgmtInfoType, SJA1105PQRS)  MgmtInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  RetVal  = E_NOT_OK;
  uint8           errorId = ETHSWT_30_SJA1105PQRS_E_NO_ERROR;
  uint8           TsReg = 0; /* PRQA S 781 */ /* MD_EthSwt_30_Sja1105PQRS_781 */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  swtCfg;
  uint8           hwPortIdx;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check initialization state of the component. */
  if( (EthSwt_30_Sja1105PQRS_ModuleInitState == ETHSWT_STATE_UNINIT) ||
      (EthSwt_30_Sja1105PQRS_ModuleInitState == ETHSWT_STATE_INIT)      )
  {
    errorId = ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( MgmtInfo == NULL_PTR )
  {
    errorId = ETHSWT_30_SJA1105PQRS_E_INV_POINTER;
  }
  else
#endif /* ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* retrieve the switch instance responsible for managing the frame */
    if( EthSwt_30_Sja1105PQRS_GetSwitchManagementInstance(EthCtrlIdx, &swtCfg) == E_OK )
    {
      /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
      /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
      EthSwt_EnterExclusiveArea(Sja1105PQRS, TS_QUEUE_PROCESSING);

      /* #30 Convert PortIdx to HW PortIdx */
      hwPortIdx = swtCfg->TransformPortIdx(MgmtInfo->PortIdx,
                                           ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_INTERNAL_VIEW);

      /* #40 Initiate the processing of a transmission timestamp retrieval process */
      if( EthSwt_30_Sja1105PQRS_IsTsRegAvailable(MgmtInfo->SwitchIdx, hwPortIdx, 0) == TRUE )
      {
        TsReg = 0;
        RetVal = E_OK;
      }
      else if( EthSwt_30_Sja1105PQRS_IsTsRegAvailable(MgmtInfo->SwitchIdx, hwPortIdx, 1) == TRUE )
      {
        TsReg = 1;
        RetVal = E_OK;
      }
      else
      {
        /* No TsReg available at the moment - retVal stays E_NOT_OK */
      }

      if( RetVal == E_OK )
      {
        /* A free TsReg was found for this port - continue by setting up a TsProc element */
        if( EthSwt_30_Sja1105PQRS_StartPrepOfTxTsRetrieval(EthCtrlIdx, BufIdx, MgmtInfo, TsReg) == FALSE )
        {
          RetVal = E_NOT_OK;
        }
      }
      if( RetVal == E_OK )
      {
        /* reserve the TsReg if everything was successful */
        EthSwt_30_Sja1105PQRS_OccupyTsReg(MgmtInfo->SwitchIdx, hwPortIdx, TsReg);
      }

      /* PRQA S 872 2 */ /* MD_EthSwt_30_Sja1105PQRS_1.2 */
      /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
      EthSwt_ExitExclusiveArea(Sja1105PQRS, TS_QUEUE_PROCESSING);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (ETHSWT_30_SJA1105PQRS_DEV_ERROR_REPORT == STD_ON)
  /* #50 Report default errors if any occurred */
  if (errorId != ETHSWT_30_SJA1105PQRS_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHSWT_30_SJA1105PQRS_MODULE_ID, ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID, ETHSWT_30_SJA1105PQRS_SID_ENABLE_EGRESS_TIME_STAMP_API, errorId);
  }
#else
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif

  return RetVal;
} /* EthSwt_30_Sja1105PQRS_EnableEgressTimeStamp() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_SetCorrectionTime
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_SetCorrectionTime(
                 uint8                              SwitchIdx,
  ETHSWT_P2CONST(Eth_TimeIntDiffType, SJA1105PQRS)  OffsetTimePtr,
  ETHSWT_P2CONST(float64,             SJA1105PQRS)  RateRatioPtr)
{
  Std_ReturnType retVal;
  uint8          errorId = ETHSWT_30_SJA1105PQRS_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON)
  retVal  = E_NOT_OK;
  /* #10 Check initialization state of the component */
  if( (EthSwt_30_Sja1105PQRS_ModuleInitState == ETHSWT_STATE_UNINIT) ||
      (EthSwt_30_Sja1105PQRS_ModuleInitState == ETHSWT_STATE_INIT)      )
  {
    errorId = ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( SwitchIdx >= ETHSWT_30_SJA1105PQRS_SWITCH_NUM )
  {
    errorId = ETHSWT_30_SJA1105PQRS_E_INV_PARAM;
  }
  else
#endif /* ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT */
  {
    retVal = E_OK;

    /* #30 Check if offset time correction has been requested and if so trigger it */
    if( OffsetTimePtr != NULL_PTR )
    {
      retVal |= EthSwt_30_Sja1105PQRS_PerformOffsetCorrection(SwitchIdx, OffsetTimePtr);
    }

    /* #40 Check if rate ratio correction has been requested and if so trigger it */
    if( RateRatioPtr != NULL_PTR )
    {
      retVal |= EthSwt_30_Sja1105PQRS_PerformRateCorrection(SwitchIdx, RateRatioPtr);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (ETHSWT_30_SJA1105PQRS_DEV_ERROR_REPORT == STD_ON)
  /* #50 Report default errors if any occurred */
  if (errorId != ETHSWT_30_SJA1105PQRS_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHSWT_30_SJA1105PQRS_MODULE_ID, ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID, ETHSWT_30_SJA1105PQRS_SID_SET_CORRECTION_TIME_API, errorId);
  }
#else
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif

  return retVal;
} /* EthSwt_30_Sja1105PQRS_SetCorrectionTime() */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_StartQbvSchedule
 *********************************************************************************************************************/
/*! Internal comment removed.
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
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_StartQbvSchedule(
    uint8                              SwitchIdx)
{
  Std_ReturnType                                                         retVal;
  uint8                                                                  errorId = ETHSWT_30_SJA1105PQRS_E_NO_ERROR;
  uint8_least                                                            LoopIdx;
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType,   SJA1105PQRS)  SpiTransaction;
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_InstanceDataType,     SJA1105PQRS)  InstanceRuntime;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON)
  retVal  = E_NOT_OK;
  /* #10 Check initialization state of the component */
  if( (EthSwt_30_Sja1105PQRS_ModuleInitState == ETHSWT_STATE_UNINIT) ||
      (EthSwt_30_Sja1105PQRS_ModuleInitState == ETHSWT_STATE_INIT)      )
  {
    errorId = ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( SwitchIdx >= ETHSWT_30_SJA1105PQRS_SWITCH_NUM )
  {
    errorId = ETHSWT_30_SJA1105PQRS_E_INV_PARAM;
  }
  else
#endif /* ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT */
  {
    InstanceRuntime = &EthSwt_30_Sja1105PQRS_InstanceData[SwitchIdx];

    /* #30 Enter exclusive area (Reason: Consistency of date retrieved and set in consecutive SPI transactions that must
     *                                   not be interrupted) */
    /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
    EthSwt_EnterExclusiveArea(Sja1105PQRS, QBV_START_STOP_SCHEDULE);

    retVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(SwitchIdx, &SpiTransaction);

    if( retVal == (Std_ReturnType)E_OK )
    {
      /* #40 Get current state of QBV traffic scheduling */
      SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_ADDR;
      SpiTransaction->WordNum = (uint16)1u;
      retVal = EthSwt_30_Sja1105PQRS_LL_ReadBytesSync(SwitchIdx, SpiTransaction);
    }

    /* #50 Check if QBV is already started */
    if ( (retVal == (Std_ReturnType)E_OK) &&
         ((SpiTransaction->DataPtr[0] & ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_PTPSTRTSCH_MASK) != 0) )
    {
      retVal = E_NOT_OK;
    }

    /* #60 Start QBV traffic scheduling */
    if( retVal == (Std_ReturnType)E_OK )
    {
      uint64 startedTimer = 0;
      uint64 schedulerLength = 0;
      uint64 timerRegister;

      /* #600 Check if a scheduler is already running */
      for( LoopIdx = 0; LoopIdx < ETHSWT_30_SJA1105PQRS_SWITCH_NUM; LoopIdx++ )
      {
        if (startedTimer < EthSwt_30_Sja1105PQRS_InstanceData[LoopIdx].QbvSchedulingStart)
        {
          startedTimer = EthSwt_30_Sja1105PQRS_InstanceData[LoopIdx].QbvSchedulingStart;
          schedulerLength = EthSwt_30_Sja1105PQRS_InstanceConfig[LoopIdx].QbvScheduleLength;
        }
      }

      /* #610 Read Lower and Upper Part of Switch Time (2 words) */
      SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_PTPCTRL7_REG_ADDR;
      SpiTransaction->WordNum = (uint16)2u;

      retVal = EthSwt_30_Sja1105PQRS_LL_ReadBytesSync(SwitchIdx, SpiTransaction);

      /* #620 Calculate scheduler start */
      timerRegister = (SpiTransaction->DataPtr[0] | ((uint64)(SpiTransaction->DataPtr[1]) << 32));
      timerRegister += (uint64) (ETHSWT_30_SJA1105PQRS_NSEC_PER_MILLISEC / ETHSWT_30_SJA1105PQRS_PTPTSCLK_TO_NS_FACTOR);

      /* #630 Optionally synchronize to already running scheduler */
      if ((startedTimer > 0) && (schedulerLength != 0))
      {
        uint64 runSchedulers = (timerRegister - startedTimer) / schedulerLength;
        timerRegister = startedTimer + (schedulerLength * (runSchedulers + 1));
      }

      /* #640 Prepare scheduler start */
      SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_PTPCTRL2_REG_ADDR;
      SpiTransaction->DataPtr[0] = (uint32)(timerRegister & 0xFFFFFFFFull);
      SpiTransaction->DataPtr[1] = (uint32)(timerRegister >> 32u);
      SpiTransaction->WordNum = (uint16)2u;
      retVal |= EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(SwitchIdx, SpiTransaction);

      SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_ADDR;
      SpiTransaction->DataPtr[0] = ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_VALID_MASK |
                                   ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_PTPSTRTSCH_MASK;
      SpiTransaction->WordNum = (uint16)1u;
      retVal |= EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(SwitchIdx, SpiTransaction);
      InstanceRuntime->QbvSchedulingStart = timerRegister;
    }
    /* #70 Leave exclusive area */
    /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
    EthSwt_ExitExclusiveArea(Sja1105PQRS, QBV_START_STOP_SCHEDULE);
  }

  /* ----- Development Error Report --------------------------------------- */
#if (ETHSWT_30_SJA1105PQRS_DEV_ERROR_REPORT == STD_ON)
  /* #80 Report default errors if any occurred */
  if (errorId != ETHSWT_30_SJA1105PQRS_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHSWT_30_SJA1105PQRS_MODULE_ID,
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID, ETHSWT_30_SJA1105PQRS_SID_START_QBV_SCHEDULE_API, errorId);
  }
#else
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif

  return retVal;
} /* EthSwt_30_Sja1105PQRS_StartQbvSchedule() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_StopQbvSchedule
 *********************************************************************************************************************/
/*! Internal comment removed.
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
 *********************************************************************************************************************/
ETHSWT_FUNC(Std_ReturnType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_StopQbvSchedule(
    uint8                              SwitchIdx)
{
  Std_ReturnType                                                      retVal;
  uint8                                                               errorId = ETHSWT_30_SJA1105PQRS_E_NO_ERROR;
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS) SpiTransaction;
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_InstanceDataType,   SJA1105PQRS) InstanceRuntime;


  /* ----- Development Error Checks ------------------------------------- */
#if (ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON)
  retVal  = E_NOT_OK;
  /* #10 Check initialization state of the component */
  if( (EthSwt_30_Sja1105PQRS_ModuleInitState == ETHSWT_STATE_UNINIT) ||
      (EthSwt_30_Sja1105PQRS_ModuleInitState == ETHSWT_STATE_INIT)      )
  {
    errorId = ETHSWT_30_SJA1105PQRS_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( SwitchIdx >= ETHSWT_30_SJA1105PQRS_SWITCH_NUM )
  {
    errorId = ETHSWT_30_SJA1105PQRS_E_INV_PARAM;
  }
  else
#endif /* ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT */
  {
    InstanceRuntime = &EthSwt_30_Sja1105PQRS_InstanceData[SwitchIdx];
    /* #30 Enter exclusive area (Reason: Consistency of date retrieved and set in consecutive SPI transactions that must
     *                                   not be interrupted) */
    /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
    EthSwt_EnterExclusiveArea(Sja1105PQRS, QBV_START_STOP_SCHEDULE);

    retVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(SwitchIdx, &SpiTransaction);

    if( retVal == (Std_ReturnType)E_OK )
    {
      /* #40 Get current state of QBV traffic scheduling */
      SpiTransaction->AddrIdx = (uint32)ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_ADDR;
      SpiTransaction->WordNum = (uint16)1u;
      retVal = EthSwt_30_Sja1105PQRS_LL_ReadBytesSync(SwitchIdx, SpiTransaction);
    }

    /* #50 Check if QBV is already stopped */
    if ( (retVal == (Std_ReturnType)E_OK) &&
         ((SpiTransaction->DataPtr[0] & ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_PTPSTRTSCH_MASK) == 0) )
    {
      retVal = E_NOT_OK;
    }

    /* #60 Stop QBV traffic scheduling */
    if( retVal == (Std_ReturnType)E_OK )
    {
      SpiTransaction->DataPtr[0] = ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_VALID_MASK |
                                   ETHSWT_30_SJA1105PQRS_PTPCTRL1_REG_PTPSTOPSCH_MASK;
      retVal |= EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(SwitchIdx, SpiTransaction);
      InstanceRuntime->QbvSchedulingStart = 0;
    }
    /* #70 Leave exclusive area */
    /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
    EthSwt_ExitExclusiveArea(Sja1105PQRS, QBV_START_STOP_SCHEDULE);
  }
  /* ----- Development Error Report --------------------------------------- */
#if (ETHSWT_30_SJA1105PQRS_DEV_ERROR_REPORT == STD_ON)
  /* #80 Report default errors if any occurred */
  if (errorId != ETHSWT_30_SJA1105PQRS_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHSWT_30_SJA1105PQRS_MODULE_ID,
        ETHSWT_30_SJA1105PQRS_INV_INSTANCE_ID, ETHSWT_30_SJA1105PQRS_SID_STOP_QBV_SCHEDULE_API, errorId);
  }
#else
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint -e{438} */
#endif

  return retVal;
} /* EthSwt_30_Sja1105PQRS_StopQbvSchedule() */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_MainFunctionTime
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_MainFunctionTime( void )
{
  uint8 elemIdx;

  /* #10 If current active processing queue element has something to process */
  while( EthSwt_30_Sja1105PQRS_TsProcQueue[EthSwt_30_Sja1105PQRS_TsQueue_CurProcElemIdx] != NULL_PTR )
  {
    boolean isCompleted;

    /* #100 Process the queue element */
    isCompleted = EthSwt_30_Sja1105PQRS_ProcessTsElem(EthSwt_30_Sja1105PQRS_TsProcQueue[EthSwt_30_Sja1105PQRS_TsQueue_CurProcElemIdx]);

    /* #110 If processing of the element has finished */
    if( isCompleted == TRUE )
    {
      /* #1100 Dequeue element from processing queue and advance the processing queue to next element */
      EthSwt_30_Sja1105PQRS_DequeueTsElem(EthSwt_30_Sja1105PQRS_TsProcQueue[EthSwt_30_Sja1105PQRS_TsQueue_CurProcElemIdx]);
    }
    /* #120 Otherwise */
    else
    {
      /* #1200 If timeout for the processing of the element is reached */
      if( EthSwt_30_Sja1105PQRS_TsProcQueue[EthSwt_30_Sja1105PQRS_TsQueue_CurProcElemIdx]->Timeout == 0u )
      {
        /* #12000 Inform EthIf about the missing timestamps, dequeue the element and advance the processing queue to next element */
        if( (EthSwt_30_Sja1105PQRS_TsProcQueue[EthSwt_30_Sja1105PQRS_TsQueue_CurProcElemIdx]->ProcFlags & ETHSWT_30_SJA1105PQRS_TS_PROC_FLAG_IGR_PENDING) != 0U )
        {
          EthIf_SwitchIngressTimeStampIndication(EthSwt_30_Sja1105PQRS_TsProcQueue[EthSwt_30_Sja1105PQRS_TsQueue_CurProcElemIdx]->EthCtrlIdx,
                                                 EthSwt_30_Sja1105PQRS_TsProcQueue[EthSwt_30_Sja1105PQRS_TsQueue_CurProcElemIdx]->DataPtr,
                                                 &EthSwt_30_Sja1105PQRS_TsProcQueue[EthSwt_30_Sja1105PQRS_TsQueue_CurProcElemIdx]->IgrMgmtInfo,
                                                 NULL_PTR);
        }
        if( (EthSwt_30_Sja1105PQRS_TsProcQueue[EthSwt_30_Sja1105PQRS_TsQueue_CurProcElemIdx]->ProcFlags & ETHSWT_30_SJA1105PQRS_TS_PROC_FLAG_EGR_PENDING) != 0U )
        {
          EthIf_SwitchEgressTimeStampIndication(EthSwt_30_Sja1105PQRS_TsProcQueue[EthSwt_30_Sja1105PQRS_TsQueue_CurProcElemIdx]->EthCtrlIdx,
                                                EthSwt_30_Sja1105PQRS_TsProcQueue[EthSwt_30_Sja1105PQRS_TsQueue_CurProcElemIdx]->DataPtr,
                                                &EthSwt_30_Sja1105PQRS_TsProcQueue[EthSwt_30_Sja1105PQRS_TsQueue_CurProcElemIdx]->EgrMgmtInfo,
                                                NULL_PTR);

        }
        /* invalidate entry and proceed with next queue element */
        EthSwt_30_Sja1105PQRS_DequeueTsElem(EthSwt_30_Sja1105PQRS_TsProcQueue[EthSwt_30_Sja1105PQRS_TsQueue_CurProcElemIdx]);
      }
      break;
    }
  }

  /* #20 Calculate the timeouts of the elements in the processing queue */
  for( elemIdx = 0; elemIdx < ETHSWT_30_SJA1105PQRS_MAX_PARALLEL_TS_EVENTS; elemIdx++ )
  {
    if( EthSwt_30_Sja1105PQRS_TsProcQueue[elemIdx] != NULL_PTR )
    {
      if( EthSwt_30_Sja1105PQRS_TsProcQueue[elemIdx]->Timeout > 0 )
      {
        EthSwt_30_Sja1105PQRS_TsProcQueue[elemIdx]->Timeout--;
      }
    }
  }

} /* EthSwt_30_Sja1105PQRS_MainFunctionTime() */

#define ETHSWT_30_SJA1105PQRS_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ETHSWT_30_SJA1105PQRS_GLOBAL_TIME_SUPPORT */

/* PRQA L: IDENTIFIER_DIFFER */

/* Module specific MISRA deviations:
 *
  MD_EthSwt_30_Sja1105PQRS_0310_FrameId:
      Reason:     To access the frame identifier the pointer type must be casted.
      Risk:       Risk of an unaligned memory exception.
      Prevention: Covered by code review.
 */

/**********************************************************************************************************************
 *  END OF FILE: EthSwt_30_Sja1105PQRS_Time.c
 *********************************************************************************************************************/

