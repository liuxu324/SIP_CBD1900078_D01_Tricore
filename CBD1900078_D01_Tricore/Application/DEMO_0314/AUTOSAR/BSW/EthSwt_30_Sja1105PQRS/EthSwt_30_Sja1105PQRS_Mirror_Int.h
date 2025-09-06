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
/*!        \file  EthSwt_30_Sja1105PQRS_Mirror_Int.h
 *        \brief  Internal mirror submodule header
 *
 *      \details  Contains macros, types, data and functions of the mirror submodule only to be used by the
 *                driver itself.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

#if !defined (ETHSWT_30_SJA1105PQRS_MIRROR_INT_H)
# define ETHSWT_30_SJA1105PQRS_MIRROR_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "SchM_EthSwt_30_Sja1105PQRS.h"
# include "EthSwt_30_Sja1105PQRS_Types.h"
# include "EthSwt_30_Sja1105PQRS_Int.h"
# include "EthSwt_30_Sja1105PQRS_Regs.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# if !defined (ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE)
#  define ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE static INLINE
# endif

#if !defined(ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC)
/* PRQA S 3453 2 */ /* MD_MSR_19.7 */
# define ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(RetType) \
             ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE FUNC(RetType, ETHSWT_30_SJA1105PQRS_CODE)
#endif

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

# define ETHSWT_30_SJA1105PQRS_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_Mirror_IsConfigValid()
 **********************************************************************************************************************/
/*! \brief       Validates given configuration for specified switch
 *  \details     This function validates the given mirror configuration for the specified switch.
 *  \param[in]   swtIdx           Identifier of the switch
 *  \param[in]   mirrorConfigPtr  Pointer to mirror configuration
 *  \return      FALSE  Mirror configuration is invalid
 *  \return      TRUE   Mirror configuration can be applied to given switch
 *  \pre         -
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
/* PRQA S 3219 1 */ /* MD_EthSwt_30_Sja1105PQRS_3219 */
ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(boolean) EthSwt_30_Sja1105PQRS_Mirror_IsConfigValid(
  uint8 swtIdx,
  P2CONST(EthSwt_PortMirrorCfgType, AUTOMATIC, ETHSWT_30_SJA1105PQRS_CONST) mirrorConfigPtr);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_Mirror_AdaptPortMirrorSelection()
 *********************************************************************************************************************/
/*! \brief          Configures mirroring for the specified port of the specified switch
 *  \details        This function configures the ingress or egress mirroring of frames on the specified port of
 *                  the specified switch. If ingress and egress are both set to FALSE, mirroring is disabled for
 *                  this port. If egress and ingress are both set to TRUE, all frames are mirrored.
 *  \param[in]      swtIdx         Identifier of the switch
 *  \param[in]      hwPortIdx      Hardware identifier of the port
 *  \param[in]      ingressMirror  This flag indicates that ingress frames on this port shall be mirrored
 *  \param[in]      egressMirror   This flag indicates that egress frames on this port shall be mirrored
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
/* PRQA S 3219 1 */ /* MD_EthSwt_30_Sja1105PQRS_3219 */
ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(void) EthSwt_30_Sja1105PQRS_LL_Mirror_AdaptPortMirrorSelection(
  uint8 swtIdx,
  uint8 hwPortIdx,
  boolean ingressMirror,
  boolean egressMirror);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_Mirror_DisableMirroring()
 *********************************************************************************************************************/
/*! \brief          Disables mirroring
 *  \details        This function disables mirroring for the specified switch.
 *  \param[in]      swtIdx         Identifier of the switch
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(void) EthSwt_30_Sja1105PQRS_LL_Mirror_DisableMirroring( /* PRQA S 3219 */ /* MD_EthSwt_30_Sja1105PQRS_3219 */
  uint8 swtIdx);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_Mirror_SetMacFilter()
 *********************************************************************************************************************/
/*! \brief          Configures mirror MAC address filtering.
 *  \details        This function configures which frames should be mirrored. Only frames which match all filter
 *                  are mirrored.
 *  \param[in]      swtIdx            Identifier of the switch
 *  \param[in]      srcMacAddrFilter  Source MAC address filter, don't care value: 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
 *  \param[in]      dstMacAddrFilter  Destination MAC address filter, don't care value: 0xFF, 0xFF, 0xFF, 0xFF,
 *                                    0xFF, 0xFF
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(void) EthSwt_30_Sja1105PQRS_LL_Mirror_SetMacFilter( /* PRQA S 3219 */ /* MD_EthSwt_30_Sja1105PQRS_3219 */ /*lint -e522 */ /* Suppress ID451 because function is yet not implemented. */
  uint8 swtIdx,
  P2CONST(uint8, AUTOMATIC, ETHSWT_30_SJA1105PQRS_CONST) srcMacAddrFilter,
  P2CONST(uint8, AUTOMATIC, ETHSWT_30_SJA1105PQRS_CONST) dstMacAddrFilter);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_Mirror_SetVlanFilter()
 *********************************************************************************************************************/
/*! \brief          Configures mirror VLAN ID filtering.
 *  \details        This function configures which frames should be mirrored. Only frames which match all filters
 *                  are mirrored.
 *  \param[in]      swtIdx            Identifier of the switch
 *  \param[in]      vlanIdFilter      VLAN ID filter, don't care value: 0xFFFF
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(void) EthSwt_30_Sja1105PQRS_LL_Mirror_SetVlanFilter( /* PRQA S 3219 */ /* MD_EthSwt_30_Sja1105PQRS_3219 */
  uint8 swtIdx,
  uint16 vlanIdFilter);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_Mirror_SetPacketDivider()
 *********************************************************************************************************************/
/*! \brief          Configures the packet divider
 *  \details        This function configures the packet divider of the mirror capture port. If it is set to 1, every
 *                  frame is mirrored; if it is set to 2, every second frame is mirrored, etc.
 *  \param[in]      swtIdx            Identifier of the switch
 *  \param[in]      divider           Divider setting, don't care value: 1
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(void) EthSwt_30_Sja1105PQRS_LL_Mirror_SetPacketDivider( /* PRQA S 3219 */ /* MD_EthSwt_30_Sja1105PQRS_3219 */
  uint8 swtIdx,
  uint8 divider);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_Mirror_EnableCapturePort()
 *********************************************************************************************************************/
/*! \brief          Enables the mirror captured port.
 *  \details        This function enables the mirror capture port which sends all mirrored frames. Optionally, these
 *                  frames can be VLAN tagged or double tagged.
 *  \param[in]      swtIdx            Identifier of the switch
 *  \param[in]      hwCapturePortIdx  Hardware identifier of the capture port
 *  \param[in]      mirroringMode     Tagging mode of the captured frames: no tagging, VLAN tagged, double VLAN tagged
 *  \param[in]      vlanOuterTag      VLAN ID used for VLAN retagging or as outer tag for VLAN double retagging
 *  \param[in]      vlanInnerTag      VLAN ID used as inner tag for VLAN double retagging
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(void) EthSwt_30_Sja1105PQRS_LL_Mirror_EnableCapturePort( /* PRQA S 3219 */ /* MD_EthSwt_30_Sja1105PQRS_3219 */
  uint8 swtIdx,
  uint8 hwCapturePortIdx,
  uint8 mirroringMode,
  uint16 vlanOuterTag,
  uint16 vlanInnerTag);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_Mirror_EnableMirroring()
 *********************************************************************************************************************/
/*! \brief          Enable mirroring
 *  \details        This function enables frame mirroring on the specified switch.
 *  \param[in]      swtIdx            Identifier of the switch
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(void) EthSwt_30_Sja1105PQRS_LL_Mirror_EnableMirroring( /* PRQA S 3219 */ /* MD_EthSwt_30_Sja1105PQRS_3219 */
  uint8 swtIdx);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_Mirror_IsConfigValid()
 *********************************************************************************************************************/
/*! \brief          Validates mirror configuration
 *  \details        This function validates the given mirror configuration and will return an error if it will not
 *                  work on the given switch.
 *  \param[in]      swtIdx            Identifier of the switch
 *  \param[in]      mirrorConfigPtr   Mirroring configuration
 *  \return         FALSE - Mirror configuration is not valid
 *  \return         TRUE  - Mirror configuration is valid
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(boolean) EthSwt_30_Sja1105PQRS_LL_Mirror_IsConfigValid( /* PRQA S 3219 */ /* MD_EthSwt_30_Sja1105PQRS_3219 */
  uint8 swtIdx,
  P2CONST(EthSwt_PortMirrorCfgType, AUTOMATIC, ETHSWT_30_SJA1105PQRS_CONST) mirrorConfigPtr);

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_Mirror_SetCapturePort()
 *********************************************************************************************************************/
/*! \brief          Sets capture port
 *  \details        This function sets the capture port port which will output all mirrored frames. If it is set to an
 *                  invalid port, mirroring is disabled.
 *  \param[in]      swtIdx            Identifier of the switch
 *  \param[in]      hwCapturePortIdx  Hardware identifier of the capture port
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *********************************************************************************************************************/
ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(void) EthSwt_30_Sja1105PQRS_LL_Mirror_SetCapturePort( /* PRQA S 3219 */ /* MD_EthSwt_30_Sja1105PQRS_3219 */
  uint8 swtIdx,
  uint8 hwCapturePortIdx);

/**********************************************************************************************************************
 * EthSwt_30_Sja1105PQRS_Mirror_IsConfigValid()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(boolean) EthSwt_30_Sja1105PQRS_Mirror_IsConfigValid( /* PRQA S 3219 */ /* MD_EthSwt_30_Sja1105PQRS_3219 */
  uint8 swtIdx,
  P2CONST(EthSwt_PortMirrorCfgType, AUTOMATIC, ETHSWT_30_SJA1105PQRS_CONST) mirrorConfigPtr)
{
  boolean result;
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  InstanceConfig;
  InstanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[swtIdx];

  /* #10 Check for common mistakes in configuration */
  if( (mirrorConfigPtr->MirroredSwitchEgressPortIdxBitMask == 0) &&
      (mirrorConfigPtr->MirroredSwitchIngressPortIdxBitMask == 0) )
  {
    result = FALSE;
  }
  /* #20 Check that mirror port is available */
  else if( InstanceConfig->TransformPortIdx(mirrorConfigPtr->CapturePortIdx,
                                            ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_INTERNAL_VIEW) >=
      ETHSWT_30_SJA1105PQRS_HARDWARE_PORT_NUM )
  {
    result = FALSE;
  }
  else
  {
    /* #30 Call lower layer function to make derivative specific tests */
    result = EthSwt_30_Sja1105PQRS_LL_Mirror_IsConfigValid(swtIdx, mirrorConfigPtr);
  }
  return result;
} /* EthSwt_30_Sja1105PQRS_Mirror_IsConfigValid() */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_Mirror_AdaptPortMirrorSelection()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(void) EthSwt_30_Sja1105PQRS_LL_Mirror_AdaptPortMirrorSelection( /* PRQA S 3219 */ /* MD_EthSwt_30_Sja1105PQRS_3219 */
  uint8 swtIdx,
  uint8 hwPortIdx,
  boolean ingressMirror,
  boolean egressMirror)
{
  ETHSWT_P2CONST(EthSwt_30_Sja1105PQRS_InstanceConfigType, SJA1105PQRS)  InstanceConfig;
    ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS)  SpiTransaction;
                 EthSwt_PortIdxType                                      PortIdx; /* PRQA S 781 */ /* MD_EthSwt_30_Sja1105PQRS_781 */
                 Std_ReturnType                                          RetVal;
  InstanceConfig = &EthSwt_30_Sja1105PQRS_InstanceConfig[swtIdx];
  PortIdx = InstanceConfig->TransformPortIdx(hwPortIdx, ETHSWT_30_SJA1105PQRS_TRANSFORM_PORT_IDX_TO_SWITCH_EXTERNAL_VIEW);
  RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(swtIdx, &SpiTransaction);
  if( RetVal == (Std_ReturnType)E_OK )
  {
    /* #10 Read current values */
    SpiTransaction->AddrIdx     = (uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG0_ADDR;
    SpiTransaction->DataPtr[0]  = hwPortIdx;
    SpiTransaction->DataPtr[0] |= (uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG0_VALID_MASK;
    RetVal = EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(swtIdx, SpiTransaction);
    (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(swtIdx, SpiTransaction);
  }

  if( RetVal == (Std_ReturnType)E_OK )
  {
    /* register 1 */
    RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(swtIdx, &SpiTransaction);
    if( RetVal == (Std_ReturnType)E_OK )
    {
      /* #20 Activate ingress or egress mirroring if applicable */
      if( ingressMirror == TRUE )
      {
        InstanceConfig->DynMacTableEntries[PortIdx].Register2 |=
            (uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG2_PORTST_ING_MIRROR_EN_MASK;
      }
      else
      {
        InstanceConfig->DynMacTableEntries[PortIdx].Register2 &=
            ~(uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG2_PORTST_ING_MIRROR_EN_MASK;
      }
      if( egressMirror == TRUE )
      {
        InstanceConfig->DynMacTableEntries[PortIdx].Register2 |=
            (uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG2_PORTST_EGR_MIRROR_EN_MASK;
      }
      else
      {
        InstanceConfig->DynMacTableEntries[PortIdx].Register2 &=
            ~(uint32) ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG2_PORTST_EGR_MIRROR_EN_MASK;
      }

      SpiTransaction->AddrIdx    = (uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG2_ADDR;
      SpiTransaction->DataPtr[0] = InstanceConfig->DynMacTableEntries[PortIdx].Register2;
      (void)EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(swtIdx, SpiTransaction);

      /* #30 Write/activate current values */
      SpiTransaction->AddrIdx     = (uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG0_ADDR;
      SpiTransaction->DataPtr[0]  = hwPortIdx;
      SpiTransaction->DataPtr[0] |= (uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG0_VALID_MASK;
      SpiTransaction->DataPtr[0] |= (uint32)ETHSWT_30_SJA1105PQRS_MAC_CONFIG_TABLE_RECONFIG_REG0_RDWRSET_MASK;
      (void)EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(swtIdx, SpiTransaction);

      (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(swtIdx, SpiTransaction);
    }
  }
} /* EthSwt_30_Sja1105PQRS_LL_Mirror_AdaptPortMirrorSelection */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_Mirror_DisableMirroring()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(void) EthSwt_30_Sja1105PQRS_LL_Mirror_DisableMirroring( /* PRQA S 3219 */ /* MD_EthSwt_30_Sja1105PQRS_3219 */
  uint8 swtIdx)
{
  /* #10 Set capture port to invalid port number to disable mirroring */
  EthSwt_30_Sja1105PQRS_LL_Mirror_SetCapturePort(swtIdx, ETHSWT_30_SJA1105PQRS_PORT_INVALID);
} /* EthSwt_30_Sja1105PQRS_LL_Mirror_DisableMirroring */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_Mirror_SetMacFilter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(void) EthSwt_30_Sja1105PQRS_LL_Mirror_SetMacFilter( /* PRQA S 3219 */ /* MD_EthSwt_30_Sja1105PQRS_3219 */
  uint8 swtIdx,
  P2CONST(uint8, AUTOMATIC, ETHSWT_30_SJA1105PQRS_CONST) srcMacAddrFilter,
  P2CONST(uint8, AUTOMATIC, ETHSWT_30_SJA1105PQRS_CONST) dstMacAddrFilter)
{
  /* #10 Not yet implemented */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(swtIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(srcMacAddrFilter); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(dstMacAddrFilter); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* EthSwt_30_Sja1105PQRS_LL_Mirror_SetMacFilter */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_Mirror_SetVlanFilter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(void) EthSwt_30_Sja1105PQRS_LL_Mirror_SetVlanFilter( /* PRQA S 3219 */ /* MD_EthSwt_30_Sja1105PQRS_3219 */
  uint8 swtIdx,
  uint16 vlanIdFilter)
{
  /* #10 Not yet implemented */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(swtIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(vlanIdFilter); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* EthSwt_30_Sja1105PQRS_LL_Mirror_SetVLanFilter */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_Mirror_SetPacketDivider()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(void) EthSwt_30_Sja1105PQRS_LL_Mirror_SetPacketDivider( /* PRQA S 3219 */ /* MD_EthSwt_30_Sja1105PQRS_3219 */
  uint8 swtIdx,
  uint8 divider)
{
  /* #10 Not yet implemented */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(swtIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(divider); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* EthSwt_30_Sja1105PQRS_LL_Mirror_SetPacketDivider */ /* PRQA S 6010, 6030 */ /* MD_MSR_STPTH, MD_MSR_STCYC */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_Mirror_EnableCapturePort()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(void) EthSwt_30_Sja1105PQRS_LL_Mirror_EnableCapturePort( /* PRQA S 3219 */ /* MD_EthSwt_30_Sja1105PQRS_3219 */
  uint8 swtIdx,
  uint8 hwCapturePortIdx,
  uint8 mirroringMode,
  uint16 vlanOuterTag,
  uint16 vlanInnerTag)
{
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(mirroringMode); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(vlanOuterTag); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(vlanInnerTag); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  /* #10 Set capture port to given port */
  EthSwt_30_Sja1105PQRS_LL_Mirror_SetCapturePort(swtIdx, hwCapturePortIdx);
} /* EthSwt_30_Sja1105PQRS_LL_Mirror_EnableCapturePort */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_Mirror_EnableMirroring()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(void) EthSwt_30_Sja1105PQRS_LL_Mirror_EnableMirroring( /* PRQA S 3219 */ /* MD_EthSwt_30_Sja1105PQRS_3219 */
  uint8 swtIdx)
{
  /* #10 Do nothing - not necessary for this hardware */
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(swtIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

} /* EthSwt_30_Sja1105PQRS_LL_Mirror_EnableMirroring */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_Mirror_IsConfigValid()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(boolean) EthSwt_30_Sja1105PQRS_LL_Mirror_IsConfigValid( /* PRQA S 3219 */ /* MD_EthSwt_30_Sja1105PQRS_3219 */
  uint8 swtIdx,
  P2CONST(EthSwt_PortMirrorCfgType, AUTOMATIC, ETHSWT_30_SJA1105PQRS_CONST) mirrorConfigPtr)
{
  boolean isIngressPort = EthSwt_30_Sja1105PQRS_IsPortInBitmask((uint8) mirrorConfigPtr->CapturePortIdx,
                                                            mirrorConfigPtr->MirroredSwitchIngressPortIdxBitMask);
  boolean isEgressPort = EthSwt_30_Sja1105PQRS_IsPortInBitmask((uint8) mirrorConfigPtr->CapturePortIdx,
                                                           mirrorConfigPtr->MirroredSwitchEgressPortIdxBitMask);
  Std_ReturnType retVal = FALSE;
  ETHSWT_30_SJA1105PQRS_DUMMY_STATEMENT(swtIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  /* #10 Mirroring must not be enabled for mirror port */
  if( (isIngressPort == FALSE) && (isEgressPort == FALSE) )
  {
    retVal = TRUE;
  }

  return retVal;
} /* EthSwt_30_Sja1105PQRS_LL_Mirror_IsConfigValid */

/**********************************************************************************************************************
 *  EthSwt_30_Sja1105PQRS_LL_Mirror_SetCapturePort()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHSWT_30_SJA1105PQRS_MIRROR_INT_LOCAL_INLINE_FUNC(void) EthSwt_30_Sja1105PQRS_LL_Mirror_SetCapturePort( /* PRQA S 3219 */ /* MD_EthSwt_30_Sja1105PQRS_3219 */
  uint8 swtIdx,
  uint8 hwCapturePortIdx)
{
  ETHSWT_P2VAR(EthSwt_30_Sja1105PQRS_SpiTransactionType, SJA1105PQRS)  SpiTransaction;
               Std_ReturnType                                          RetVal;

  RetVal = EthSwt_30_Sja1105PQRS_LL_ProvideSpiTransactionBuffer(swtIdx, &SpiTransaction);
  if( RetVal == (Std_ReturnType)E_OK )
  {
    /* #10 Read current values */
    SpiTransaction->AddrIdx    = (uint32)ETHSWT_30_SJA1105PQRS_GENERAL_PARAMS_RECONFIG_REG0_ADDR;
    SpiTransaction->DataPtr[0] = (uint32)ETHSWT_30_SJA1105PQRS_GENERAL_PARAMS_RECONFIG_REG0_VALID_MASK;
    (void)EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(swtIdx, SpiTransaction);
    /* #20 Get current capture port */
    SpiTransaction->AddrIdx    = (uint32)ETHSWT_30_SJA1105PQRS_GENERAL_PARAMS_RECONFIG_REG5_ADDR;
    (void)EthSwt_30_Sja1105PQRS_LL_ReadU32Sync(swtIdx, SpiTransaction);
    /* #30 Set new capture port */
    SpiTransaction->DataPtr[0] &= ~((uint32)ETHSWT_30_SJA1105PQRS_GENERAL_PARAMS_RECONFIG_REG5_MIRR_PORT_MASK <<
                                    (uint32)ETHSWT_30_SJA1105PQRS_GENERAL_PARAMS_RECONFIG_REG5_MIRR_PORT_SHIFT);
    SpiTransaction->DataPtr[0] |= (uint32)hwCapturePortIdx <<
                                  (uint32)ETHSWT_30_SJA1105PQRS_GENERAL_PARAMS_RECONFIG_REG5_MIRR_PORT_SHIFT;
    (void)EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(swtIdx, SpiTransaction);
    /* #40 Activate new capture port */
    SpiTransaction->AddrIdx    = (uint32)ETHSWT_30_SJA1105PQRS_GENERAL_PARAMS_RECONFIG_REG0_ADDR;
    SpiTransaction->DataPtr[0] = (uint32)ETHSWT_30_SJA1105PQRS_GENERAL_PARAMS_RECONFIG_REG0_VALID_MASK |
                                 (uint32)ETHSWT_30_SJA1105PQRS_GENERAL_PARAMS_RECONFIG_REG0_RDWRSET_MASK;
    (void)EthSwt_30_Sja1105PQRS_LL_WriteU32Sync(swtIdx, SpiTransaction);
    (void)EthSwt_30_Sja1105PQRS_LL_ReleaseSpiTransactionBuffer(swtIdx, SpiTransaction);
  }
} /* EthSwt_30_Sja1105PQRS_LL_Mirror_SetCapturePort */

# define ETHSWT_30_SJA1105PQRS_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ETHSWT_30_SJA1105PQRS_MIRROR_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthSwt_30_Sja1105PQRS_Mirror_Int.h
 *********************************************************************************************************************/
