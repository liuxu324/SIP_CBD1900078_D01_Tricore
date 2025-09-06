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
/*!        \file  EthSwt_30_Sja1105PQRS_Casc.c
 *        \brief  Source file contaning the cascading API
 *
 *      \details  The Ethernet Switch Driver allows to control Ethernet switches in a cascaded setup. This file
 *                implements the APIs related to this functionality.
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

#define ETHSWT_30_SJA1105PQRS_CASC_SOURCE

/* PRQA S 779,777 IDENTIFIER_DIFFER */ /* MD_EthSwt_30_Sja1105PQRS_5.1 */
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "EthSwt_30_Sja1105PQRS.h"
#include "EthSwt_30_Sja1105PQRS_Int.h"
#include "EthSwt_30_Sja1105PQRS_Lcfg.h"
#include "EthSwt_30_Sja1105PQRS_Regs.h"
#include "EthSwt_30_Sja1105PQRS_Casc.h"
#include "EthSwt_30_Sja1105PQRS_Casc_Int.h"

#if ( ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT == STD_ON )
# include "Det.h"
#endif /* ETHSWT_30_SJA1105PQRS_DEV_ERROR_DETECT */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of EthSwt_30_Sja1105PQRS header file */
#if (  (ETHSWT_30_SJA1105PQRS_SW_MAJOR_VERSION != (0x05U)) \
    || (ETHSWT_30_SJA1105PQRS_SW_MINOR_VERSION != (0x00U)) \
    || (ETHSWT_30_SJA1105PQRS_SW_PATCH_VERSION != (0x01U)) )
# error "Vendor specific version numbers of EthSwt_30_Sja1105PQRS_Casc.c and EthSwt_30_Sja1105PQRS.h are inconsistent"
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

/*! Value defining inactive value of a bucket representing a uplink port */
#define ETHSWT_30_SJA1105PQRS_BUCKET_UPLINK_INACTIVE_VAL (0x00u)
/*! Value defining active value of a bucket representing a uplink port */
#define ETHSWT_30_SJA1105PQRS_BUCKET_UPLINK_ACTIVE_VAL (0xFFu)

/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/

#define ETHSWT_30_SJA1105PQRS_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

ETHSWT_LOCAL ETHSWT_VAR_WITH_MEM(boolean, VAR_NOINIT, SJA1105PQRS) EthSwt_30_Sja1105PQRS_UpdateMCastPortAssign_AffectedSwt[ETHSWT_30_SJA1105PQRS_SWITCH_NUM];

#define ETHSWT_30_SJA1105PQRS_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define ETHSWT_30_SJA1105PQRS_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_CalcSwtAffection()
 *********************************************************************************************************************/
/*! \brief          Calculates the affection of a switch according to the passed buckets
 *  \details        -
 *  \param[in]      buckets        Buckets representing ports and holding information about if a port is requested
 *  \param[in,out]  swtAffections  Array to store if a switch is affected with respect to the passed buckets
 *  \pre            -
 *********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_CalcSwtAffection(
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_PortBucketsType, SJA1105PQRS) buckets,
    ETHSWT_P2VAR(boolean,                            SJA1105PQRS) swtAffactions);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_GetUpdateMCastPortAssignSwtAffection()
 *********************************************************************************************************************/
/*! \brief          Retrieve the value of the element addressed by the switch index
 *  \details        -
 *  \param[in]      swtIdx          Switch index to address the array element
 *  \return         FALSE - Switch isn't affected
 *  \return         TRUE - Switch is affected
 *  \pre            -
 *********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetUpdateMCastPortAssignSwtAffection(
  uint8 swtIdx);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_SetSwtAffection()
 *********************************************************************************************************************/
/*! \brief          Checks passed switch index against array boundaries and sets the passed value in the respective
 *                  array element
 *  \details        -
 *  \param[in]      swtIdx          Switch index to address the array element
 *  \param[in,out]  affectionArray  Array the respective element shall be modified in
 *  \param[in]      affection       Value to assigne to the respective array element
 *  \pre            -
 *********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_SetSwtAffection(
               uint8               swtIdx,
  ETHSWT_P2VAR(boolean, SJA1105PQRS)  affectionArray,
               boolean             affection);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_SetUplinkBucketValue()
 *********************************************************************************************************************/
/*! \brief          Sets the respective buckets of the uplink port between the passed switches to the passed value
 *  \details        -
 *  \param[in]      firstSwtIdx   Index of the first switch defining the uplinks
 *  \param[in]      secondSwtIdx  Index of the second switch defining the uplinks
 *  \param[in]      value         Value to be set for the uplink buckets
 *  \param[in,out]  buckets       Buckets representing the ports
 *  \pre            -
 *********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_SetUplinkBucketValue(
               uint8                                         firstSwtIdx,
               uint8                                         secondSwtIdx,
               uint8                                         value,
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_PortBucketsType, SJA1105PQRS) buckets);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_GetCascRelationsNum()
 *********************************************************************************************************************/
/*! \brief          Return the number of cascading relations
 *  \details        -
 *  \return         Number of cascading relations
 *  \pre            -
 *********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(uint8, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetCascRelationsNum(void);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_CalcSwtAffection()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_CalcSwtAffection(
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_PortBucketsType, SJA1105PQRS) buckets,
    ETHSWT_P2VAR(boolean,                            SJA1105PQRS) swtAffactions)
{
  uint8_least swtIdx;

  /* #10 Query for switches that have active non-uplink ports in the buckets and provide the information to the caller */
  for( swtIdx = 0; swtIdx < ETHSWT_30_SJA1105PQRS_SWITCH_NUM; swtIdx++ )
  {
    uint8_least bucketOffset;

    uint8 bucketOffsetStart;
    uint8 bucketOffsetEnd;

    EthSwt_30_Sja1105PQRS_SetSwtAffection((uint8)swtIdx, swtAffactions, FALSE); /* initially the switch isn't affected */

    bucketOffsetStart = EthSwt_30_Sja1105PQRS_CascadingConfig.CascadingMaps[swtIdx].BucketOffset;
    bucketOffsetEnd = bucketOffsetStart + EthSwt_30_Sja1105PQRS_InstanceConfig[swtIdx].PortNum;

    for( bucketOffset = bucketOffsetStart; bucketOffset < bucketOffsetEnd; bucketOffset++ )
    {
      uint8 portIdx = (uint8)(bucketOffset - bucketOffsetStart);

      /* uplink ports aren't relevant for affection of the switch */
      if( EthSwt_30_Sja1105PQRS_IsUplinkPort((uint8)swtIdx, portIdx) == FALSE )
      {
        if( (*buckets)[bucketOffset] > 0 )
        {
          /* at least one affected port is enough for the switch being affected */
          EthSwt_30_Sja1105PQRS_SetSwtAffection((uint8)swtIdx, swtAffactions, TRUE);
          break;
        }
      }
    }
  }
} /* EthSwt_30_Sja1105PQRS_CalcSwtAffection() */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_GetUpdateMCastPortAssignSwtAffection()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetUpdateMCastPortAssignSwtAffection(
  uint8 swtIdx)
{
  /* #10 Retrieve the value */
  return EthSwt_30_Sja1105PQRS_UpdateMCastPortAssign_AffectedSwt[swtIdx];
} /* EthSwt_30_Sja1105PQRS_GetUpdateMCastPortAssignSwtAffection() */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_SetSwtAffection()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_SetSwtAffection(
               uint8               swtIdx,
  ETHSWT_P2VAR(boolean, SJA1105PQRS)  affectionArray,
               boolean             affection)
{
  /* #10 Check index for fulfilling the array bounds and write value */
  if( swtIdx < ETHSWT_30_SJA1105PQRS_SWITCH_NUM )
  {
    affectionArray[swtIdx] = affection;
  }
} /* EthSwt_30_Sja1105PQRS_SetSwtAffection() */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_SetUplinkBucketValue()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_SetUplinkBucketValue(
               uint8                                         firstSwtIdx,
               uint8                                         secondSwtIdx,
               uint8                                         value,
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_PortBucketsType, SJA1105PQRS) buckets)
{
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_CascadingMapType, SJA1105PQRS) cascMap;
  uint8_least uplinkIdx;

  cascMap = &EthSwt_30_Sja1105PQRS_CascadingConfig.CascadingMaps[firstSwtIdx];

  /* #10 Query for uplinks between the passed switches and set the respective buckets to the passed value */
  for( uplinkIdx = 0u; uplinkIdx < cascMap->UplinkNum; uplinkIdx++ )
  {
    if( cascMap->Uplinks[uplinkIdx].RemoteSwitchIdx == secondSwtIdx )
    {
      uint8 bucketOffset = cascMap->BucketOffset + cascMap->Uplinks[uplinkIdx].LocalPortIdx;

      (*buckets)[bucketOffset] = value;
    }
  }
} /* EthSwt_30_Sja1105PQRS_SetUplinkBucketValue() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_GetIndexOfDirectlyConnectedSwitch()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
ETHSWT_FUNC(EthSwt_SwitchIdxType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetIndexOfDirectlyConnectedSwitch( void )
{
  /* ----- Local data declaration --------------------------------------- */
  uint8_least switchIdx;

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Query for the switch instance that is first in the cascading hierarchy
   *     (the one connected to Host-CPU directly) */
  for( switchIdx = 0; switchIdx < ETHSWT_30_SJA1105PQRS_SWITCH_NUM; switchIdx++ )
  {
    if( EthSwt_30_Sja1105PQRS_CascadingConfig.CascadingMaps[switchIdx].CascadingLevel == 0 )
    {
      break;
    }
  }

  return (EthSwt_SwitchIdxType)switchIdx;
} /* EthSwt_30_Sja1105PQRS_GetCascadingLevel0SwitchIdx() */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_IsUplinkPort()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_IsUplinkPort(
  EthSwt_SwitchIdxType swtIdx,
  EthSwt_PortIdxType   portIdx)
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_CascadingMapType, SJA1105PQRS) cascMap;
                 uint8_least                                    uplinkIdx;
                 boolean                                        result;

  /* ----- Local data definition ---------------------------------------- */
  cascMap = &EthSwt_30_Sja1105PQRS_CascadingConfig.CascadingMaps[swtIdx];
  result  = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if port is contained in any uplink of the switch */
  for( uplinkIdx = 0; uplinkIdx < cascMap->UplinkNum; uplinkIdx++ )
  {
    if( portIdx == cascMap->Uplinks[uplinkIdx].LocalPortIdx )
    {
      result = TRUE;
      break;
    }
  }

  return result;
} /* EthSwt_30_Sja1105PQRS_IsUplinkPort() */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_GetLocalUplinkPortForRemoteUplink()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *********************************************************************************************************************/
ETHSWT_FUNC(EthSwt_PortIdxType, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetLocalUplinkPortForRemoteUplink(
               EthSwt_SwitchIdxType           remSwtIdx,
               EthSwt_PortIdxType             locSwtIdx)
{
  /* ----- Local data declaration --------------------------------------- */
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_CascadingMapType, SJA1105PQRS) cascMap;
                 uint8_least                                    uplinkIdx;
                 EthSwt_PortIdxType                             locPortIdx;

  /* ----- Local data definition ---------------------------------------- */
  cascMap    = &EthSwt_30_Sja1105PQRS_CascadingConfig.CascadingMaps[locSwtIdx];
  locPortIdx = ETHSWT_INVALID_PORT_IDX;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Query for the local switch port related to the remote switch (first uplink is used) */
  for( uplinkIdx = 0; uplinkIdx < cascMap->UplinkNum; uplinkIdx++ )
  {
    if( cascMap->Uplinks[uplinkIdx].RemoteSwitchIdx == remSwtIdx )
    {
      locPortIdx = cascMap->Uplinks[uplinkIdx].LocalPortIdx;
    }
  }

  return locPortIdx;
} /* EthSwt_30_Sja1105PQRS_GetLocalUplinkPortForRemoteUplink() */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_IsAnyBucketRequested()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
ETHSWT_FUNC(boolean, SJA1105PQRS) EthSwt_30_Sja1105PQRS_IsAnyBucketRequested(
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_PortBucketsType, SJA1105PQRS) buckets)
{
  /* ----- Local data declaration --------------------------------------- */
  boolean     result;
  uint8_least bucketIdx;

  /* ----- Local data definition ---------------------------------------- */
  result = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if any bucket is requested */
  for( bucketIdx = 0; bucketIdx < ETHSWT_30_SJA1105PQRS_TOTAL_PORTS_NUM; bucketIdx++ )
  {
    if( (*buckets)[bucketIdx] > 0 )
    {
      result = TRUE;
      break;
    }
  }

  return result;
} /* EthSwt_30_Sja1105PQRS_IsAnyBucketRequested() */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_GetCascRelationsNum()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
ETHSWT_LOCAL_INLINE ETHSWT_FUNC(uint8, SJA1105PQRS) EthSwt_30_Sja1105PQRS_GetCascRelationsNum(void)
{
  /* #10 return Number of cascading relations */
  return ETHSWT_30_SJA1105PQRS_CASCADING_RELATIONS;
}
/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_UpdateUplinkPortBuckets()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_UpdateUplinkPortBuckets(
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_PortBucketsType, SJA1105PQRS) buckets)
{
  /* ----- Local data declaration --------------------------------------- */
  uint8_least cascRelationIdx;

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */

  EthSwt_30_Sja1105PQRS_CalcSwtAffection((ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_PortBucketsType, SJA1105PQRS))buckets, EthSwt_30_Sja1105PQRS_UpdateMCastPortAssign_AffectedSwt);

  /* #10 Adapt the uplink port bucket counts dependent on the switches having active ports */
  for( cascRelationIdx = 0; cascRelationIdx < EthSwt_30_Sja1105PQRS_GetCascRelationsNum(); cascRelationIdx++ )
  {
    uint8 localSwtIdx;
    uint8 remoteSwtIdx;
    boolean isLocSwtAffected;
    boolean isRemSwtAffected;
    uint8 bucketCount;

    localSwtIdx  = EthSwt_30_Sja1105PQRS_CascadingConfig.CascadingRelations[cascRelationIdx].FirstSwtIdx;
    remoteSwtIdx = EthSwt_30_Sja1105PQRS_CascadingConfig.CascadingRelations[cascRelationIdx].SecondSwtIdx;

    isLocSwtAffected = EthSwt_30_Sja1105PQRS_GetUpdateMCastPortAssignSwtAffection(localSwtIdx);
    isRemSwtAffected = EthSwt_30_Sja1105PQRS_GetUpdateMCastPortAssignSwtAffection(remoteSwtIdx);

    bucketCount = ETHSWT_30_SJA1105PQRS_BUCKET_UPLINK_INACTIVE_VAL;
    if( (isLocSwtAffected == TRUE) &&
        (isRemSwtAffected == TRUE))
    {
      bucketCount = ETHSWT_30_SJA1105PQRS_BUCKET_UPLINK_ACTIVE_VAL;
    }

    EthSwt_30_Sja1105PQRS_SetUplinkBucketValue(localSwtIdx, remoteSwtIdx, bucketCount, buckets);
  }
} /* EthSwt_30_Sja1105PQRS_UpdateUplinkPortBuckets() */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_CreatePortMasksFromBuckets()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
ETHSWT_FUNC(void, SJA1105PQRS) EthSwt_30_Sja1105PQRS_CreatePortMasksFromBuckets(
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_PortBucketsType, SJA1105PQRS) buckets,
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_PortMaskType,    SJA1105PQRS) portMasks)
{
  /* ----- Local data declaration --------------------------------------- */
  uint8_least swtIdx;

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Create port masks for each switch. */
  for( swtIdx = 0; swtIdx < ETHSWT_30_SJA1105PQRS_SWITCH_NUM; swtIdx++ )
  {
    uint8_least bucketOffset;
    uint8 bucketOffsetStart;
    uint8 bucketOffsetEnd;

    /* #100 Setup bucket index range for the current switch. */
    portMasks[swtIdx] = 0;

    bucketOffsetStart = EthSwt_30_Sja1105PQRS_CascadingConfig.CascadingMaps[swtIdx].BucketOffset;
    bucketOffsetEnd = bucketOffsetStart + EthSwt_30_Sja1105PQRS_InstanceConfig[swtIdx].PortNum;

    /* #110 Enable bit in port mask if bucket counter isn't 0. */
    for( bucketOffset = bucketOffsetStart; bucketOffset < bucketOffsetEnd; bucketOffset++ )
    {
      if( (*buckets)[bucketOffset] > 0 )
      {
        uint8 portIdx = (uint8)(bucketOffset - bucketOffsetStart);
        /* port mask contains hardware representation of the port index */
        portMasks[swtIdx] |= (EthSwt_30_Sja1105PQRS_PortMaskType)(1u << EthSwt_30_Sja1105PQRS_InstanceConfig[swtIdx].TransformPortIdx(portIdx, ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_INTERNAL_VIEW));
      }
    }
  }
} /* EthSwt_30_Sja1105PQRS_CreatePortMasksFromBuckets() */

#define ETHSWT_30_SJA1105PQRS_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* PRQA L: IDENTIFIER_DIFFER */

/* Module specific MISRA deviations:
 *
 */

/**********************************************************************************************************************
 *  END OF FILE: EthSwt_30_Sja1105PQRS_Casc.c
 *********************************************************************************************************************/

