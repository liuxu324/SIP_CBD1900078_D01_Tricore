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
/**        \file  Eth_30_Tc3xx_CfgAccess_Int.h
 *        \brief  Configuration access header file
 *
 *      \details  Provides inline functions to access the configuration in an abstracted way.
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
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777 */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */
#if !defined (ETH_30_TC3XX_CFG_ACCESS_INT_H)
# define ETH_30_TC3XX_CFG_ACCESS_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_Lcfg.h"
# include "Eth_30_Tc3xx_HwAccess_Int.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* Bitmasks for supported feature decoding */
# define ETH_30_TC3XX_FEAT_QOS_ENABLED_MASK                                      (0x01U)
# define ETH_30_TC3XX_FEAT_FQTSS_ENABLED_MASK                                    (0x02U)
# define ETH_30_TC3XX_FEAT_TIMESYNC_ENABLED_MASK                                 (0x04U)
# define ETH_30_TC3XX_FEAT_IP_CHECKSUM_OFFLOADING_ENABLED_MASK                   (0x08U)
# define ETH_30_TC3XX_FEAT_PROTOCOL_CHECKSUM_OFFLOADING_ENABLED_MASK             (0x10U)

# if !defined (ETH_30_TC3XX_CFG_ACCESS_INLINE)
#  define ETH_30_TC3XX_CFG_ACCESS_INLINE LOCAL_INLINE
# endif /* ETH_30_TC3XX_CFG_ACCESS_INLINE */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetCtrlCfg
 *********************************************************************************************************************/
/*! \brief       Retrieves the Ethernet controller configuration data structure
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \return      Data structure related to the Ethernet controller
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2CONST(Eth_30_Tc3xx_CtrlCfgType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetCtrlCfg(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTrcvSpeed
 *********************************************************************************************************************/
/*! \brief       Retrieves the statically configured link speed of the related PHY
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \return      Statically configured link speed of the PHY related to the Ethernet controller
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint32, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTrcvSpeed(
  uint8  ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetPreConfiguredMacAddr
 *********************************************************************************************************************/
/*! \brief       Retrieves the statically configured MAC address of the Ethernet controller
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \return      Statically configured MAC address of the Ethernet controller
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2CONST(uint8, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetPreConfiguredMacAddr(
  uint8  ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetActiveMacAddr
 *********************************************************************************************************************/
/*! \brief       Retrieves the currently active MAC address of the Ethernet controller
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \return      Currently active MAC address of the Ethernet controller
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2CONST(uint8, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetActiveMacAddr(
  uint8  ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_InsertActiveMacAddr
 *********************************************************************************************************************/
/*! \brief         Inserts the currently active MAC address of the Ethernet controller into the given buffer
 *  \details       -
 *  \param[in]     ctrlIdx     Identifier of the Ethernet controller
 *  \param[in,out] trgtBuffer  Buffer with at least the length of a MAC address the MAC address shall be inserted in
 *  \context       ANY
 *  \reentrant     TRUE
 *  \pre           -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_InsertActiveMacAddr(
        uint8                        ctrlIdx,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) trgtBuffer);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_SetActiveMacAddr
 *********************************************************************************************************************/
/*! \brief       Sets the active MAC address of the Ethernet controller
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \param[in]   macAddr  MAC address that shall be set
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_SetActiveMacAddr(
          uint8                        ctrlIdx,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) macAddr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetPreConfiguredRegBaseAddr
 *********************************************************************************************************************/
/*! \brief       Retrieves the statically configured register base address of the Ethernet controller
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \return      Register base address of the Ethernet controller
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint32, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetPreConfiguredRegBaseAddr(
  uint8  ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_SetRegBaseAddr
 *********************************************************************************************************************/
/*! \brief       Sets the register base address of the Ethernet controller
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \param[in]   regAddr  Register base address that shall be set
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_SetRegBaseAddr(
  uint8   ctrlIdx,
  uint32  regAddr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetLLCtrlCfgData
 *********************************************************************************************************************/
/*! \brief       Retrieves the Ethernet controller LL configuration data structure
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2CONST(Eth_30_Tc3xx_LL_CtrlCfgDataType, ETH_30_TC3XX_APPL_VAR, ETH_30_TC3XX_APPL_VAR), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetLLCtrlCfgData(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRegNum
 *********************************************************************************************************************/
/*! \brief       Retrieves number of registers to be written during initialization of the Ethernet controller
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \return      Number of registers
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRegNum(
  uint8  ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRegOffset
 *********************************************************************************************************************/
/*! \brief       Retrieves the offset from register base address for the given register
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \param[in]   regIdx   Identifier of the register written during initialization
 *  \return      Offset of the register
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(Eth_30_Tc3xx_RegOffsetType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRegOffset(
  uint8  ctrlIdx,
  uint8  regIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRegValue
 *********************************************************************************************************************/
/*! \brief       Retrieves the value of the register to be written during initialization of the Ethernet controller
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \param[in]   regIdx   Identifier of the register written during initialization
 *  \return      Value of the register
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(Eth_30_Tc3xx_RegWidthType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRegValue(
  uint8  ctrlIdx,
  uint8  regIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRegProtectedAccess
 *********************************************************************************************************************/
/*! \brief       Retrieves if the register to be written during initialization of the Ethernet controller should be
 *               done with protected access
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \param[in]   regIdx   Identifier of the register written during initialization
 *  \return      TRUE - register has to be accessed with protected access
 *               FALSE - register has to be accessed without protected access
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRegProtectedAccess(
  uint8  ctrlIdx,
  uint8  regIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxBufferHandling
 *********************************************************************************************************************/
/*! \brief       Retrieves the reception buffer handling data stucture of the descriptor ring
 *  \details     -
 *  \param[in]   ctrlIdx       Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx  Identifier of the reception descriptor ring
 *  \return      Reception buffer handling data strucutre
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2CONST(Eth_30_Tc3xx_RxBufferHandlingType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxBufferHandling(
  uint8  ctrlIdx,
  uint16 descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxBuffer
 *********************************************************************************************************************/
/*! \brief       Retrieves the reception buffer of the descriptor ring
 *  \details     -
 *  \param[in]   ctrlIdx       Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx  Identifier of the reception descriptor ring
 *  \return      Reception buffer of the descriptor ring
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2VAR(uint8, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxBuffer(
  uint8  ctrlIdx,
  uint16 descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxBufferLen
 *********************************************************************************************************************/
/*! \brief       Retrieves the length of a segment of the reception buffer
 *  \details     -
 *  \param[in]   ctrlIdx       Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx  Identifier of the reception descriptor ring
 *  \return      Length of a segment of the reception buffer
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxBufferLen(
  uint8  ctrlIdx,
  uint16 descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxBufferNum
 *********************************************************************************************************************/
/*! \brief       Retrieves the number of segments of the reception buffer
 *  \details     -
 *  \param[in]   ctrlIdx       Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx  Identifier of the reception descriptor ring
 *  \return      Number of reception buffer segments
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxBufferNum(
  uint8  ctrlIdx,
  uint16 descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxBufferHandling
 *********************************************************************************************************************/
/*! \brief       Retrieves the transmission buffer handling data stucture
 *  \details     -
 *  \param[in]   ctrlIdx       Identifier of the Ethernet controller
 *  \return      Transmission buffer handling data strucutre
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2CONST(Eth_30_Tc3xx_TxBufferHandlingType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxBufferHandling(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxBuffer
 *********************************************************************************************************************/
/*! \brief       Retrieves the transmission buffer
 *  \details     -
 *  \param[in]   ctrlIdx       Identifier of the Ethernet controller
 *  \return      Transmission buffer
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2VAR(uint8, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxBuffer(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetMaxTxBufferLen
 *********************************************************************************************************************/
/*! \brief       Retrieves the length of the greates transmission buffer segment available
 *  \details     -
 *  \param[in]   ctrlIdx       Identifier of the Ethernet controller
 *  \return      Length of the greates transmission buffer segment
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetMaxTxBufferLen(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxBufferStart
 *********************************************************************************************************************/
/*! \brief       Retrieves the start index for a transmission buffer segment
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \param[in]   bufIdx   Identifier of the transmission buffer segment
 *  \return      Start index of the transmission buffer segment
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint32, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxBufferStart(
  uint8 ctrlIdx,
  uint8 bufIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxBufferLen
 *********************************************************************************************************************/
/*! \brief       Retrieves the length of a transmission buffer segment
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \param[in]   bufIdx   Identifier of the transmission buffer segment
 *  \return      Length of the transmission buffer segment
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxBufferLen(
  uint8 ctrlIdx,
  uint8 bufIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxBufferNum
 *********************************************************************************************************************/
/*! \brief       Retrieves the number of transmission buffer segments
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \return      Number of transmission buffer segments
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxBufferNum(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetUlTxConfState
 *********************************************************************************************************************/
/*! \brief       Retrieves the state of the upper layer tx confirmation related to a transmission buffer segment
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \param[in]   bufIdx   Identifier of the transmission buffer segment
 *  \return      State of the upper layer tx confirmation
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetUlTxConfState(
  uint8 ctrlIdx,
  uint8 bufIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_SetUlTxConfState
 *********************************************************************************************************************/
/*! \brief       Sets the upper layer tx confirmation state of the related transmission buffer segment
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \param[in]   bufIdx   Identifier of the transmission buffer segment
 *  \param[in]   value    State that shall be set
 *  \context     ANY
 *  \reentrant   TRUE for different transmission buffer segments
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_SetUlTxConfState(
  uint8 ctrlIdx,
  uint8 bufIdx,
  uint8 value);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxBufferBusyState
 *********************************************************************************************************************/
/*! \brief       Retrieves the busy state of a transmission buffer segment
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \param[in]   bufIdx   Identifier of the transmission buffer segment
 *  \return      Busy state
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxBufferBusyState(
  uint8 ctrlIdx,
  uint8 bufIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_SetTxBufferBusyState
 *********************************************************************************************************************/
/*! \brief       Sets the busy state of the related transmission buffer segment
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \param[in]   bufIdx   Identifier of the transmission buffer segment
 *  \param[in]   value    State that shall be set
 *  \context     ANY
 *  \reentrant   TRUE for different transmission buffer segments
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_SetTxBufferBusyState(
  uint8 ctrlIdx,
  uint8 bufIdx,
  uint8 value);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxDescrRingNum
 *********************************************************************************************************************/
/*! \brief       Retrieves the number of transmission descriptor rings
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \return      Number of transmission descriptor rings
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxDescrRingNum(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxDescrNum
 *********************************************************************************************************************/
/*! \brief       Retrieves the number of descriptors of a transmission descriptor ring
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx   Identifier of the transmission descriptor ring
 *  \return      Number of descriptors
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxDescrNum(
  uint8 ctrlIdx,
  uint8 descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxDescriptorHandling
 *********************************************************************************************************************/
/*! \brief       Retrieves the transmission descriptor handling data structure for a transmission descriptor ring
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx   Identifier of the transmission descriptor ring
 *  \return      Transmission descriptor handling data strucutre
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2CONST(Eth_30_Tc3xx_TxDescriptorHandlingType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxDescriptorHandling(
  uint8 ctrlIdx,
  uint8 descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxDescrRing
 *********************************************************************************************************************/
/*! \brief       Retrieves a transmission descriptor ring
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx   Identifier of the transmission descriptor ring
 *  \return      Transmission descriptor ring
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2VAR(Eth_30_Tc3xx_TxDescriptorType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxDescrRing(
  uint8 ctrlIdx,
  uint8 descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxDescr
 *********************************************************************************************************************/
/*! \brief       Retrieves a descriptor of a transmission descriptor ring
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx   Identifier of the transmission descriptor ring
 *  \param[in]   descrIdx       Identifier of the descriptor
 *  \return      Transmission descriptor
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2VAR(Eth_30_Tc3xx_TxDescriptorType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxDescr(
  uint8 ctrlIdx,
  uint8 descrRingIdx,
  uint8 descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxDescrProcPos
 *********************************************************************************************************************/
/*! \brief       Retrieves the processing position within the transmission descriptor ring
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx   Identifier of the transmission descriptor ring
 *  \return      Processing position
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxDescrRingProcPos(
  uint8 ctrlIdx,
  uint8 descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_SetTxDescrProcPos
 *********************************************************************************************************************/
/*! \brief       Sets the processing position within the transmission descriptor ring
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx   Identifier of the transmission descriptor ring
 *  \param[in]   value          Position to be set
 *  \context     ANY
 *  \reentrant   TRUE for different transmission descriptor rings
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_SetTxDescrRingProcPos(
  uint8 ctrlIdx,
  uint8 descrRingIdx,
  uint8 value);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxDescrRingFreePos
 *********************************************************************************************************************/
/*! \brief       Retrieves the free position within the transmission descriptor ring
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx   Identifier of the transmission descriptor ring
 *  \return      Free position
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxDescrRingFreePos(
  uint8 ctrlIdx,
  uint8 descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_SetTxDescrRingFreePos
 *********************************************************************************************************************/
/*! \brief       Sets the free position within the transmission descriptor ring
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx   Identifier of the transmission descriptor ring
 *  \param[in]   value          Free position to be set
 *  \context     ANY
 *  \reentrant   TRUE for different transmission descriptor rings
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_SetTxDescrRingFreePos(
  uint8 ctrlIdx,
  uint8 descrRingIdx,
  uint8 value);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxDescrToBufferMap
 *********************************************************************************************************************/
/*! \brief       Retrieves the identifier of the transmission buffer segment currently mapped to a descriptor
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx   Identifier of the transmission descriptor ring
 *  \param[in]   descrIdx       Identifier of the transmission descriptor
 *  \return      Identifier of the transmission buffer segment
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxDescrToBufferMap(
  uint8 ctrlIdx,
  uint8 descrRingIdx,
  uint8 descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_SetTxDescrToBufferMap
 *********************************************************************************************************************/
/*! \brief       Sets the transmission buffer segment tied to a transmission descriptor
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx   Identifier of the transmission descriptor ring
 *  \param[in]   descrIdx       Identifier of the transmission descriptor
 *  \param[in]   value          Identifier of the transmission buffer segment to be tied to the descriptor
 *  \context     ANY
 *  \reentrant   TRUE for different descriptors
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_SetTxDescrToBufferMap(
  uint8 ctrlIdx,
  uint8 descrRingIdx,
  uint8 descrIdx,
  uint8 value);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxDescrTxState
 *********************************************************************************************************************/
/*! \brief       Retrieves the transmission state of a transmission descriptor
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx   Identifier of the transmission descriptor ring
 *  \param[in]   descrIdx       Identifier of the transmission descriptor
 *  \return      Transmission state
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxDescrTxState(
  uint8 ctrlIdx,
  uint8 descrRingIdx,
  uint8 descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_SetTxDescrTxState
 *********************************************************************************************************************/
/*! \brief       Sets the transmission state of a transmission descriptor
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx   Identifier of the transmission descriptor ring
 *  \param[in]   descrIdx       Identifier of the transmission descriptor
 *  \param[in]   value          Transmission state to be set
 *  \return      Number of descriptors
 *  \context     ANY
 *  \reentrant   TRUE for different transmission descriptors
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_SetTxDescrTxState(
  uint8 ctrlIdx,
  uint8 descrRingIdx,
  uint8 descrIdx,
  uint8 value);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxDescrRingNum
 *********************************************************************************************************************/
/*! \brief       Retrieves the number of reception descriptor rings
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \return      Number of reception descriptor rings
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxDescrRingNum(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxDescrNum
 *********************************************************************************************************************/
/*! \brief       Retrieves the number of descriptors of a reception descriptor ring
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx   Identifier of the reception descriptor ring
 *  \return      Number of descriptors
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxDescrNum(
  uint8 ctrlIdx,
  uint8 descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxDescriptorHandling
 *********************************************************************************************************************/
/*! \brief       Retrieves the reception descriptor handling data structure
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx   Identifier of the reception descriptor ring
 *  \return      Reception descriptor data structure
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2CONST(Eth_30_Tc3xx_RxDescriptorHandlingType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxDescriptorHandling(
  uint8 ctrlIdx,
  uint8 descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxDescrRing
 *********************************************************************************************************************/
/*! \brief       Retrieves a reception descriptor ring
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx   Identifier of the reception descriptor ring
 *  \return      Reception descriptor ring
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2VAR(Eth_30_Tc3xx_RxDescriptorType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxDescrRing(
  uint8 ctrlIdx,
  uint8 descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxDescr
 *********************************************************************************************************************/
/*! \brief       Retrieves a reception descriptor of a reception descriptor ring
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx   Identifier of the reception descriptor ring
 *  \param[in]   descrIdx       Identifier of the reception descriptor
 *  \return      Reception descriptor
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2VAR(Eth_30_Tc3xx_RxDescriptorType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxDescr(
  uint8  ctrlIdx,
  uint8  descrRingIdx,
  uint16 descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxDescrRingProcPos
 *********************************************************************************************************************/
/*! \brief       Retrieves the processing position within a reception descriptor ring
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx   Identifier of the reception descriptor ring
 *  \return      Processing position
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxDescrRingProcPos(
  uint8 ctrlIdx,
  uint8 descrRingIdx);

#if(ETH_30_TC3XX_ENABLE_MAC_WRITE_ACCESS == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetMacAddressBlockId
 *********************************************************************************************************************/
/*! \brief       Retrieves the Nvm block id of the Mac address block
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \return      Mac address block id
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetMacAddressBlockId(
  uint8 ctrlIdx);
#endif

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_SetRxDescrRingProcPos
 *********************************************************************************************************************/
/*! \brief       Sets the processing position within a reception descriptor ring
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx   Identifier of the reception descriptor ring
 *  \param[in]   value          Processing position to be set
 *  \context     ANY
 *  \reentrant   TRUE for different reception descriptor rings
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_SetRxDescrRingProcPos(
  uint8  ctrlIdx,
  uint8  descrRingIdx,
  uint16 value);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxDescrToBufferMap
 *********************************************************************************************************************/
/*! \brief       Retrieves the identifier of the reception buffer segment currently mapped to a descriptor
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx   Identifier of the reception descriptor ring
 *  \param[in]   descrIdx       Identifier of the reception descriptor
 *  \return      Index of the buffer tied to the descriptor
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxDescrToBufferMap(
  uint8 ctrlIdx,
  uint8 descrRingIdx,
  uint16 descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_SetRxDescrToBufferMap
 *********************************************************************************************************************/
/*! \brief       Sets the reception buffer segment tied to a reception descriptor
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx   Identifier of the reception descriptor ring
 *  \param[in]   descrIdx       Identifier of the reception descriptor
 *  \param[in]   value          Index of the buffer that shall be tied to the descriptor
 *  \context     ANY
 *  \reentrant   TRUE for different reception descriptor rings
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_SetRxDescrToBufferMap(
  uint8  ctrlIdx,
  uint8  descrRingIdx,
  uint16 descrIdx,
  uint16 value);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetIsrInfo
 *********************************************************************************************************************/
/*! \brief       Retrieves interrupt service routine processing information data strucutre
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \param[in]   isrIdx   Identifier of the interrupt service routine
 *  \return      Interrupt service routine processing information
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2CONST(Eth_30_Tc3xx_IsrInfoType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetIsrInfo(
  uint8 ctrlIdx,
  uint8 isrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTsHandling
 *********************************************************************************************************************/
/*! \brief       Retrieves the time stamping handling data structure
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \return      Time stamping handling data structure
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2CONST(Eth_30_Tc3xx_TsHandlingType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTsHandling(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxTsRequest
 *********************************************************************************************************************/
/*! \brief       Retrieves the transmission time stamping request for a transmission buffer segment
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \param[in]   bufIdx   Identifier of the transmission buffer segment
 *  \return      Time stamping request
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxTsRequest(
  uint8 ctrlIdx,
  uint8 bufIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_SetTxTsRequest
 *********************************************************************************************************************/
/*! \brief       Sets the transmission time stamping request for a transmission buffer segment
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \param[in]   bufIdx   Identifier of the transmission buffer segment
 *  \param[in]   value    Time stamping request
 *  \context     ANY
 *  \reentrant   TRUE for different transmission buffer segments
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_SetTxTsRequest(
  uint8 ctrlIdx,
  uint8 bufIdx,
  uint8 value);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxTsContext
 *********************************************************************************************************************/
/*! \brief       Retrieves the transmission time stamping context for a transmission buffer segment
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \param[in]   bufIdx   Identifier of the transmission buffer segment
 *  \return      Transmission context for time stamping related to the transmission buffer segment
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2VAR(Eth_30_Tc3xx_TsContextType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxTsContext(
  uint8 ctrlIdx,
  uint8 bufIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxTsContextStackPos
 *********************************************************************************************************************/
/*! \brief       Retrieves the current depth of the reception time stamping context stack
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \return      Depth of the reception time stmaping context stack
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(sint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxTsContextStackPos(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_SetRxTsContextStackPos
 *********************************************************************************************************************/
/*! \brief       Sets the depth of the recpetion time stamping context stack
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \param[in]   value    Stack depth to be set
 *  \context     ANY
 *  \reentrant   TRUE for different Ethernet controllers
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_SetRxTsContextStackPos(
  uint8 ctrlIdx,
  sint8 value);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxTsContext
 *********************************************************************************************************************/
/*! \brief       Retrieves the currently active reception time stamping context
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \return      Reception time stamping context
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2VAR(Eth_30_Tc3xx_TsContextType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxTsContext(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_PushRxTsContextStack
 *********************************************************************************************************************/
/*! \brief       Pushes a reception time stamping context to the reception time stamping context stack
 *  \details     Function increases the reception time stamping context stack and stores the reception context onto it
 *               for being able to retrieve the context when upper layer wants to retrieve a time stamp for the
 *               respective Ethernet frame.
 *  \param[in]   ctrlIdx      Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx Identifier of the reception descriptor ring to be pushed onto the stack
 *  \param[in]   descrIdx     Identifier of the reception descriptor to be pushed onto the stack
 *  \context     ANY
 *  \reentrant   TRUE for different Ethernet controllers
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_PushRxTsContextStack(
  uint8  ctrlIdx,
  uint8  descrRingIdx,
  uint16 descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_PopRxTsContextStack
 *********************************************************************************************************************/
/*! \brief       Pops the latest reception time stamping context from the reception time stamping context stack
 *  \details     Function removes the latest time stamping context from the recpetion time stamping context stack and
 *               decreases the stack.
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \param[in]   bufIdx   Identifier of the transmission buffer segment
 *  \return      Time stamping request
 *  \context     ANY
 *  \reentrant   TRUE for different Ethernet controllers
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_PopRxTsContextStack(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetQosHandling
 *********************************************************************************************************************/
/*! \brief       Retrieves the quality of service handling data strucuture
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \return      Quality of service handling data structure
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2CONST(Eth_30_Tc3xx_QosHandlingType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetQosHandling(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxDescrRingForVlanPrio
 *********************************************************************************************************************/
/*! \brief       Retrieves the transmission descriptor ring handling a specific VLAN priority
 *  \details     -
 *  \param[in]   ctrlIdx   Identifier of the Ethernet controller
 *  \param[in]   vlanPrio  VLAN priority the ring is handling
 *  \return      Transmission descriptor ring handling the VLAN priority
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxDescrRingForVlanPrio(
  uint8 ctrlIdx,
  uint8 vlanPrio);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_IsShaperAvailable
 *********************************************************************************************************************/
/*! \brief       Checks if a traffic shaper is available on the transmission descriptor ring
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \param[in]   descrRingIdx   Identifier of the transmission descriptor ring
 *  \return      FALSE - no shaper available on the ring
 *  \return      TRUE - shaper available on the ring
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_IsShaperAvailable(
  uint8 ctrlIdx,
  uint8 descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetEthSwtIfc
 *********************************************************************************************************************/
/*! \brief       Retrieves the Ethernet Switch driver interface data structure related to the Ethernet controller
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \return      Ethernet Switch driver interface data strucutre
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2CONST(Eth_30_Tc3xx_EthSwtIfcType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetEthSwtIfc(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_IsEthSwtIfcToBeUsed
 *********************************************************************************************************************/
/*! \brief       Checks if the Ethernet Switch driver has to be called by the Ethernet driver
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *  \return      FALSE - Ethernet Switch driver interface must not be called
 *  \return      TRUE - Ethernet Switch driver interface must be called
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_IsEthSwtIfcToBeUsed(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_IsCtrlFeatEnabled
 *********************************************************************************************************************/
/*! \brief       Checks if the given feature is enabled for the Ethernet controller
 *  \details     -
 *  \param[in]   ctrlIdx       Identifier of the Ethernet controller
 *  \param[in]   featBitMask   Bit maks holding the feature bit to be checked for being enabled
 *  \return      FALSE - feature isn't enabled
 *  \return      TRUE - feature is enabled
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_IsCtrlFeatEnabled(
  uint8 ctrlIdx,
  uint8 featBitMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_IsQosEnabled
 *********************************************************************************************************************/
/*! \brief       Checks if quality of service is enabled for the Ethernet controller
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \return      FALSE - quality of service isn't enabled
 *  \return      TRUE - quality of service is enabled
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_IsQosEnabled(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_IsTimeSyncEnabled
 *********************************************************************************************************************/
/*! \brief       Checks if time synchronization is enabled for the Ethernet controller
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \return      FALSE - time synchronization isn't enabled
 *  \return      TRUE - time synchronization is enabled
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_IsTimeSyncEnabled(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_IsFqtssEnabled
 *********************************************************************************************************************/
/*! \brief       Checks if FQTSS (traffic shaping) is enabled for the Ethernet controller
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \return      FALSE - FQTSS isn't enabled
 *  \return      TRUE - FQTSS is enabled
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_IsFqtssEnabled(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_IsIpChecksumOffloadingEnabled
 *********************************************************************************************************************/
/*! \brief       Checks if IP-Checksum-Offloading (IPv4, IPv6) is enabled for the Ethernet controller
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \return      FALSE - Checksum-Offloading isn't enabled
 *  \return      TRUE - Checksum-Offloading is enabled
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_IsIpChecksumOffloadingEnabled(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_IsProtocolChecksumOffloadingEnabled
 *********************************************************************************************************************/
/*! \brief       Checks if Protocol-Checksum-Offloading (UDP, TCP and so on) is enabled for the Ethernet controller
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \return      FALSE - Checksum-Offloading isn't enabled
 *  \return      TRUE - Checksum-Offloading is enabled
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_IsProtocolChecksumOffloadingEnabled(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_IsRxInterruptModeEnabled
 *********************************************************************************************************************/
/*! \brief       Checks if reception processing with the help of interrupts is enabled for the Ethernet controller
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \return      FALSE - Interrupt processing isn't enabled
 *  \return      TRUE - Interrupt processing is enabled
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_IsRxInterruptModeEnabled(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_IsTxInterruptModeEnabled
 *********************************************************************************************************************/
/*! \brief       Checks if transmisson processing with the help of interrupts is enabled for the Ethernet controller
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \return      FALSE - Interrupt processing isn't enabled
 *  \return      TRUE - Interrupt processing is enabled
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_IsTxInterruptModeEnabled(
  uint8 ctrlIdx);

# if ( ETH_30_TC3XX_DEM_ERROR_DETECT == STD_ON )
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetDemEventId
 *********************************************************************************************************************/
/*! \brief       Retrieves the DEM-Event Id of the Ethernet controller configuration
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \return      Retrieved DEM event Id
 *  \context     ANY
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(Dem_EventIdType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetDemEventId( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx);
# endif /* ETH_30_TC3XX_DEM_ERROR_DETECT */
/**********************************************************************************************************************
 *  GLOBAL FUNCTION DEFINTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetCtrlCfg
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2CONST(Eth_30_Tc3xx_CtrlCfgType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetCtrlCfg( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  return &Eth_30_Tc3xx_CtrlCfg[ctrlIdx];
} /* Eth_30_Tc3xx_Cfg_GetCtrlCfg() */

 /**********************************************************************************************************************
  *  Eth_30_Tc3xx_Cfg_GetTrcvSpeed
  *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint32, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTrcvSpeed( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8  ctrlIdx)
{
  return Eth_30_Tc3xx_Cfg_GetCtrlCfg(ctrlIdx)->TrcvSpeed;
} /* Eth_30_Tc3xx_Cfg_GetTrcvSpeed() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetPreConfiguredMacAddr
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
*/
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2CONST(uint8, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetPreConfiguredMacAddr( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8  ctrlIdx)
{
  return (P2CONST(uint8, AUTOMATIC, AUTOMATIC))&Eth_30_Tc3xx_PhysSrcAddrsRom[ctrlIdx]; /* PRQA S 0310 */ /* MD_Eth_30_Tc3xx_0310 */ /*lint !e545 */
} /* Eth_30_Tc3xx_Cfg_GetPreConfiguredMacAddr() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetActiveMacAddr
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
*/
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2CONST(uint8, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetActiveMacAddr( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8  ctrlIdx)
{
  return (P2CONST(uint8, AUTOMATIC, AUTOMATIC))&Eth_30_Tc3xx_PhysSrcAddrs[ctrlIdx];  /* PRQA S 0310 */ /* MD_Eth_30_Tc3xx_0310 */ /*lint !e545 */
} /* Eth_30_Tc3xx_Cfg_GetActiveMacAddr() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_InsertActiveMacAddr
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
*/
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_InsertActiveMacAddr( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
        uint8                        ctrlIdx,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) trgtBuffer)
{
  trgtBuffer[0] = Eth_30_Tc3xx_PhysSrcAddrs[ctrlIdx][0];
  trgtBuffer[1] = Eth_30_Tc3xx_PhysSrcAddrs[ctrlIdx][1];
  trgtBuffer[2] = Eth_30_Tc3xx_PhysSrcAddrs[ctrlIdx][2];
  trgtBuffer[3] = Eth_30_Tc3xx_PhysSrcAddrs[ctrlIdx][3];
  trgtBuffer[4] = Eth_30_Tc3xx_PhysSrcAddrs[ctrlIdx][4];
  trgtBuffer[5] = Eth_30_Tc3xx_PhysSrcAddrs[ctrlIdx][5];
} /* Eth_30_Tc3xx_Cfg_InsertActiveMacAddr() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_SetActiveMacAddr
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
*/
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_SetActiveMacAddr( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
          uint8                        ctrlIdx,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) macAddr)
{
  Eth_30_Tc3xx_PhysSrcAddrs[ctrlIdx][0] = macAddr[0];
  Eth_30_Tc3xx_PhysSrcAddrs[ctrlIdx][1] = macAddr[1];
  Eth_30_Tc3xx_PhysSrcAddrs[ctrlIdx][2] = macAddr[2];
  Eth_30_Tc3xx_PhysSrcAddrs[ctrlIdx][3] = macAddr[3];
  Eth_30_Tc3xx_PhysSrcAddrs[ctrlIdx][4] = macAddr[4];
  Eth_30_Tc3xx_PhysSrcAddrs[ctrlIdx][5] = macAddr[5];
} /* Eth_30_Tc3xx_Cfg_SetActiveMacAddr() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetPreConfiguredRegBaseAddr
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
*/
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint32, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetPreConfiguredRegBaseAddr( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8  ctrlIdx)
{
  return Eth_30_Tc3xx_RegBaseAddr[ctrlIdx];
} /* Eth_30_Tc3xx_Cfg_GetPreConfiguredRegBaseAddr() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_SetRegBaseAddr
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
*/
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_SetRegBaseAddr( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8  ctrlIdx,
  uint32 regAddr)
{
  Eth_30_Tc3xx_RegBaseAddrRAM[ctrlIdx] = regAddr;
} /* Eth_30_Tc3xx_Cfg_SetRegBaseAddr() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetLLCtrlCfgData
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2CONST(Eth_30_Tc3xx_LL_CtrlCfgDataType, ETH_30_TC3XX_APPL_VAR, ETH_30_TC3XX_APPL_VAR), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetLLCtrlCfgData( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  return Eth_30_Tc3xx_Cfg_GetCtrlCfg(ctrlIdx)->LLCtrCfgData;
} /* Eth_30_Tc3xx_Cfg_GetLLCtrlCfgData() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRegNum
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
*/
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRegNum( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8  ctrlIdx)
{
  return Eth_30_Tc3xx_Cfg_GetCtrlCfg(ctrlIdx)->RegNum;
} /* Eth_30_Tc3xx_Cfg_GetRegNum() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRegOffset
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(Eth_30_Tc3xx_RegOffsetType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRegOffset( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8  ctrlIdx,
  uint8  regIdx)
{
  return Eth_30_Tc3xx_Cfg_GetCtrlCfg(ctrlIdx)->RegVals[regIdx].RegOffset;
} /* Eth_30_Tc3xx_Cfg_GetRegOffset() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRegValue
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(Eth_30_Tc3xx_RegWidthType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRegValue( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8  ctrlIdx,
  uint8  regIdx)
{
  return Eth_30_Tc3xx_Cfg_GetCtrlCfg(ctrlIdx)->RegVals[regIdx].RegValue;
} /* Eth_30_Tc3xx_Cfg_GetRegValue() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRegProtectedAccess
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRegProtectedAccess( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8  ctrlIdx,
  uint8  regIdx)
{
  return Eth_30_Tc3xx_Cfg_GetCtrlCfg(ctrlIdx)->RegVals[regIdx].RegProtectedAccess;
} /* Eth_30_Tc3xx_Cfg_GetRegProtectedAccess() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxBufferHandling
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2CONST(Eth_30_Tc3xx_RxBufferHandlingType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxBufferHandling( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8  ctrlIdx,
  uint16 descrRingIdx)
{
  return &Eth_30_Tc3xx_Cfg_GetCtrlCfg(ctrlIdx)->RxBufferHandling[descrRingIdx];
} /* Eth_30_Tc3xx_Cfg_GetRxBufferHandling() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxBuffer
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2VAR(uint8, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxBuffer( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8  ctrlIdx,
  uint16 descrRingIdx)
{
  return Eth_30_Tc3xx_Cfg_GetRxBufferHandling(ctrlIdx, descrRingIdx)->RxBuffer;
} /* Eth_30_Tc3xx_Cfg_GetRxBuffer() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxBufferLen
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxBufferLen( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8  ctrlIdx,
  uint16 descrRingIdx)
{
  return Eth_30_Tc3xx_Cfg_GetRxBufferHandling(ctrlIdx, descrRingIdx)->AlignedSegmentSize;
} /* Eth_30_Tc3xx_Cfg_GetRxBufferLen() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxBufferNum
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxBufferNum( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8  ctrlIdx,
  uint16 descrRingIdx)
{
  return Eth_30_Tc3xx_Cfg_GetRxBufferHandling(ctrlIdx, descrRingIdx)->SegmentNumber;
} /* Eth_30_Tc3xx_Cfg_GetRxBufferLen() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxBufferHandling
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2CONST(Eth_30_Tc3xx_TxBufferHandlingType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxBufferHandling( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  return Eth_30_Tc3xx_Cfg_GetCtrlCfg(ctrlIdx)->TxBufferHandling;
} /* Eth_30_Tc3xx_Cfg_GetTxBufferHandling() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxBuffer
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2VAR(uint8, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxBuffer( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  return Eth_30_Tc3xx_Cfg_GetTxBufferHandling(ctrlIdx)->TxBuffer;
} /* Eth_30_Tc3xx_Cfg_GetTxBufferStart() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetMaxTxBufferLen
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetMaxTxBufferLen( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  return Eth_30_Tc3xx_TxMaxBufferSize[ctrlIdx];
} /* Eth_30_Tc3xx_Cfg_GetMaxTxBufferLen() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxBufferStart
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint32, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxBufferStart( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 bufIdx)
{
  return Eth_30_Tc3xx_Cfg_GetTxBufferHandling(ctrlIdx)->TxBufferStart[bufIdx];
} /* Eth_30_Tc3xx_Cfg_GetTxBufferStart() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxBufferLen
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxBufferLen( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 bufIdx)
{
  return Eth_30_Tc3xx_Cfg_GetTxBufferHandling(ctrlIdx)->TxBufferLen[bufIdx];
} /* Eth_30_Tc3xx_Cfg_GetTxBufferLen() */


/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxBufferNum
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxBufferNum( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  return Eth_30_Tc3xx_Cfg_GetTxBufferHandling(ctrlIdx)->TxBufferNum;
} /* Eth_30_Tc3xx_Cfg_GetTxBufferNum() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetUlTxConfState
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetUlTxConfState( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 bufIdx)
{
  return Eth_30_Tc3xx_Cfg_GetTxBufferHandling(ctrlIdx)->TxBufferUlTxConfState[bufIdx];
} /* Eth_30_Tc3xx_Cfg_GetUlTxConfState() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_SetUlTxConfState
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_SetUlTxConfState( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 bufIdx,
  uint8 value)
{
  Eth_30_Tc3xx_Cfg_GetTxBufferHandling(ctrlIdx)->TxBufferUlTxConfState[bufIdx] = value;
} /* Eth_30_Tc3xx_Cfg_SetUlTxConfState() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxBufferBusyState
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxBufferBusyState( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 bufIdx)
{
  return Eth_30_Tc3xx_Cfg_GetTxBufferHandling(ctrlIdx)->TxBufferBusyTable[bufIdx];
} /* Eth_30_Tc3xx_Cfg_GetTxBufferBusyState() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_SetTxBufferBusyState
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_SetTxBufferBusyState( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 bufIdx,
  uint8 value)
{
  Eth_30_Tc3xx_Cfg_GetTxBufferHandling(ctrlIdx)->TxBufferBusyTable[bufIdx] = value;
} /* Eth_30_Tc3xx_Cfg_SetTxBufferBusyState() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxDescrRingNum
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxDescrRingNum( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  return Eth_30_Tc3xx_Cfg_GetCtrlCfg(ctrlIdx)->TxDescriptorRingNum;
} /* Eth_30_Tc3xx_Cfg_GetTxDescrRingNum() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxDescrNum
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxDescrNum( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 descrRingIdx)
{
  ETH_30_TC3XX_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  
  return Eth_30_Tc3xx_Cfg_GetTxBufferHandling(ctrlIdx)->TxDescNum;
} /* Eth_30_Tc3xx_Cfg_GetTxDescrNum() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxDescriptorHandling
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2CONST(Eth_30_Tc3xx_TxDescriptorHandlingType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxDescriptorHandling( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 descrRingIdx)
{
  return &Eth_30_Tc3xx_Cfg_GetCtrlCfg(ctrlIdx)->TxDescriptorHandling[descrRingIdx];
} /* Eth_30_Tc3xx_Cfg_GetTxDescriptorHandling() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxDescrRing
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2VAR(Eth_30_Tc3xx_TxDescriptorType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxDescrRing( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 descrRingIdx)
{
  return Eth_30_Tc3xx_Cfg_GetTxDescriptorHandling(ctrlIdx, descrRingIdx)->TxDescriptor;
} /* Eth_30_Tc3xx_Cfg_GetTxDescrRing() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxDescr
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2VAR(Eth_30_Tc3xx_TxDescriptorType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxDescr( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 descrRingIdx,
  uint8 descrIdx)
{
  return &Eth_30_Tc3xx_Cfg_GetTxDescrRing(ctrlIdx, descrRingIdx)[descrIdx];
} /* Eth_30_Tc3xx_Cfg_GetTxDescr() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxDescrProcPos
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxDescrRingProcPos( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 descrRingIdx)
{
  return (*Eth_30_Tc3xx_Cfg_GetTxDescriptorHandling(ctrlIdx, descrRingIdx)->TxDescrRingCurProcPos);
} /* Eth_30_Tc3xx_Cfg_GetTxDescrProcPos() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_SetTxDescrProcPos
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_SetTxDescrRingProcPos( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 descrRingIdx,
  uint8 value)
{
  (*Eth_30_Tc3xx_Cfg_GetTxDescriptorHandling(ctrlIdx, descrRingIdx)->TxDescrRingCurProcPos) = value;
} /* Eth_30_Tc3xx_Cfg_SetTxDescrProcPos() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxDescrRingFreePos
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxDescrRingFreePos( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 descrRingIdx)
{
  return (*Eth_30_Tc3xx_Cfg_GetTxDescriptorHandling(ctrlIdx, descrRingIdx)->TxDescrRingFreePos);
} /* Eth_30_Tc3xx_Cfg_GetTxDescrRingFreePos() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_SetTxDescrRingFreePos
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_SetTxDescrRingFreePos( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 descrRingIdx,
  uint8 value)
{
  (*Eth_30_Tc3xx_Cfg_GetTxDescriptorHandling(ctrlIdx, descrRingIdx)->TxDescrRingFreePos) = value;
} /* Eth_30_Tc3xx_Cfg_SetTxDescrRingFreePos() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxDescrToBufferMap
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxDescrToBufferMap( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 descrRingIdx,
  uint8 descrIdx)
{
  return Eth_30_Tc3xx_Cfg_GetTxDescriptorHandling(ctrlIdx, descrRingIdx)->TxDescrToBufferMap[descrIdx];
} /* Eth_30_Tc3xx_Cfg_GetTxDescrToBufferMap() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_SetTxDescrToBufferMap
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_SetTxDescrToBufferMap( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 descrRingIdx,
  uint8 descrIdx,
  uint8 value)
{
  Eth_30_Tc3xx_Cfg_GetTxDescriptorHandling(ctrlIdx, descrRingIdx)->TxDescrToBufferMap[descrIdx] = value;
} /* Eth_30_Tc3xx_Cfg_SetTxDescrToBufferMap() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxDescrTxState
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxDescrTxState( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 descrRingIdx,
  uint8 descrIdx)
{
  return Eth_30_Tc3xx_Cfg_GetTxDescriptorHandling(ctrlIdx, descrRingIdx)->TxDescrTxReadyTable[descrIdx];
} /* Eth_30_Tc3xx_Cfg_GetTxDescrTxState() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_SetTxDescrTxState
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_SetTxDescrTxState( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 descrRingIdx,
  uint8 descrIdx,
  uint8 value)
{
  Eth_30_Tc3xx_Cfg_GetTxDescriptorHandling(ctrlIdx, descrRingIdx)->TxDescrTxReadyTable[descrIdx] = value;
} /* Eth_30_Tc3xx_Cfg_SetTxDescrTxState() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxDescrRingNum
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxDescrRingNum( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  return Eth_30_Tc3xx_Cfg_GetCtrlCfg(ctrlIdx)->RxDescriptorRingNum;
} /* Eth_30_Tc3xx_Cfg_GetRxDescrRingNum() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxDescrNum
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxDescrNum( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 descrRingIdx)
{
  return Eth_30_Tc3xx_Cfg_GetRxBufferHandling(ctrlIdx, descrRingIdx)->DescNumber;
} /* Eth_30_Tc3xx_Cfg_GetRxDescrRingNum() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxDescriptorHandling
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2CONST(Eth_30_Tc3xx_RxDescriptorHandlingType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxDescriptorHandling( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 descrRingIdx)
{
  return &Eth_30_Tc3xx_Cfg_GetCtrlCfg(ctrlIdx)->RxDescriptorHandling[descrRingIdx];
} /* Eth_30_Tc3xx_Cfg_GetRxDescriptorHandling() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxDescrRing
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2VAR(Eth_30_Tc3xx_RxDescriptorType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxDescrRing( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 descrRingIdx)
{
  return Eth_30_Tc3xx_Cfg_GetRxDescriptorHandling(ctrlIdx, descrRingIdx)->RxDescriptor;
} /* Eth_30_Tc3xx_Cfg_GetRxDescrRing() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxDescr
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2VAR(Eth_30_Tc3xx_RxDescriptorType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxDescr( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8  ctrlIdx,
  uint8  descrRingIdx,
  uint16 descrIdx)
{
  return &Eth_30_Tc3xx_Cfg_GetRxDescrRing(ctrlIdx, descrRingIdx)[descrIdx];
} /* Eth_30_Tc3xx_Cfg_GetRxDescr() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxDescrRingProcPos
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxDescrRingProcPos( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 descrRingIdx)
{
  return (*Eth_30_Tc3xx_Cfg_GetRxDescriptorHandling(ctrlIdx, descrRingIdx)->RxDescrRingCurProcPos);
} /* Eth_30_Tc3xx_Cfg_GetRxDescrProcPos() */

#if (ETH_30_TC3XX_ENABLE_MAC_WRITE_ACCESS == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetMacAddressBlockId
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetMacAddressBlockId( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  return Eth_30_Tc3xx_CtrlMacAddrBlockIds[ctrlIdx].EthNvMBlockDesc;
} /* Eth_30_Tc3xx_Cfg_GetMacAddressBlockId */
#endif

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_SetRxDescrRingProcPos
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_SetRxDescrRingProcPos( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8  ctrlIdx,
  uint8  descrRingIdx,
  uint16 value)
{
  (*Eth_30_Tc3xx_Cfg_GetRxDescriptorHandling(ctrlIdx, descrRingIdx)->RxDescrRingCurProcPos) = value;
} /* Eth_30_Tc3xx_Cfg_SetRxDescrRingProcPos() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxDescrToBufferMap
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxDescrToBufferMap( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8  ctrlIdx,
  uint8  descrRingIdx,
  uint16 descrIdx)
{
  return Eth_30_Tc3xx_Cfg_GetRxDescriptorHandling(ctrlIdx, descrRingIdx)->RxDescrToBufferMap[descrIdx];
} /* Eth_30_Tc3xx_Cfg_GetRxDescrToBufferMap() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_SetRxDescrToBufferMap
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_SetRxDescrToBufferMap( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8  ctrlIdx,
  uint8  descrRingIdx,
  uint16 descrIdx,
  uint16 value)
{
  Eth_30_Tc3xx_Cfg_GetRxDescriptorHandling(ctrlIdx, descrRingIdx)->RxDescrToBufferMap[descrIdx] = value;
} /* Eth_30_Tc3xx_Cfg_SetRxDescrToBufferMap() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetIsrInfo
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2CONST(Eth_30_Tc3xx_IsrInfoType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetIsrInfo( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 isrIdx)
{
  P2CONST(Eth_30_Tc3xx_CtrlCfgType, AUTOMATIC, AUTOMATIC) pCtrlCfg = Eth_30_Tc3xx_Cfg_GetCtrlCfg(ctrlIdx);
  return &pCtrlCfg->Isrs[isrIdx];
} /* Eth_30_Tc3xx_Cfg_GetIsrInfo() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTsHandling
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2CONST(Eth_30_Tc3xx_TsHandlingType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTsHandling( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  return Eth_30_Tc3xx_Cfg_GetCtrlCfg(ctrlIdx)->TsHandling;
} /* Eth_30_Tc3xx_Cfg_GetTsHandling() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxTsRequest
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxTsRequest( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 bufIdx)
{
  return Eth_30_Tc3xx_Cfg_GetTsHandling(ctrlIdx)->TxTsRequests[bufIdx];
} /* Eth_30_Tc3xx_Cfg_GetTxTsRequest() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_SetTxTsRequest
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_SetTxTsRequest( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 bufIdx,
  uint8 value)
{
  Eth_30_Tc3xx_Cfg_GetTsHandling(ctrlIdx)->TxTsRequests[bufIdx] = value;
} /* Eth_30_Tc3xx_Cfg_SetTxTsRequest() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxTsContext
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2VAR(Eth_30_Tc3xx_TsContextType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxTsContext( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 bufIdx)
{
  return &Eth_30_Tc3xx_Cfg_GetTsHandling(ctrlIdx)->TxTsContext[bufIdx];
} /* Eth_30_Tc3xx_Cfg_GetTxTsContext() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxTsContextStackPos
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(sint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxTsContextStackPos( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  return (*Eth_30_Tc3xx_Cfg_GetTsHandling(ctrlIdx)->RxTsContextPos);
} /* Eth_30_Tc3xx_Cfg_GetRxTsContextStackPos() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_SetRxTsContextStackPos
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_SetRxTsContextStackPos( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  sint8 value)
{
  (*Eth_30_Tc3xx_Cfg_GetTsHandling(ctrlIdx)->RxTsContextPos) = value;
} /* Eth_30_Tc3xx_Cfg_SetRxTsContextStackPos() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetRxTsContext
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2VAR(Eth_30_Tc3xx_TsContextType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetRxTsContext( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  return &Eth_30_Tc3xx_Cfg_GetTsHandling(ctrlIdx)->RxTsContextStack[Eth_30_Tc3xx_Cfg_GetRxTsContextStackPos(ctrlIdx)];
} /* Eth_30_Tc3xx_Cfg_GetRxTsContext() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_PushRxTsContextStack
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_PushRxTsContextStack( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8  ctrlIdx,
  uint8  descrRingIdx,
  uint16 descrIdx)
{
  P2VAR(Eth_30_Tc3xx_TsContextType, AUTOMATIC, AUTOMATIC) rxTsContext;
  sint8 curPos;

  /* increase stack position */
  curPos = Eth_30_Tc3xx_Cfg_GetRxTsContextStackPos(ctrlIdx);
  curPos++;
  Eth_30_Tc3xx_Cfg_SetRxTsContextStackPos(ctrlIdx, curPos);

  /* store context on stack */
  rxTsContext = Eth_30_Tc3xx_Cfg_GetRxTsContext(ctrlIdx);
  rxTsContext->RingIdx  = descrRingIdx;
  rxTsContext->DescrIdx = descrIdx;
} /* Eth_30_Tc3xx_Cfg_PushRxTsContextStack() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_PopRxTsContextStack
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_PopRxTsContextStack( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  sint8 curPos;

  /* decreas stack position */
  curPos = Eth_30_Tc3xx_Cfg_GetRxTsContextStackPos(ctrlIdx);
  curPos--;
  Eth_30_Tc3xx_Cfg_SetRxTsContextStackPos(ctrlIdx, curPos);
} /* Eth_30_Tc3xx_Cfg_PopRxTsContextStack() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetQosHandling
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2CONST(Eth_30_Tc3xx_QosHandlingType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetQosHandling( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  return Eth_30_Tc3xx_Cfg_GetCtrlCfg(ctrlIdx)->QosHandling;
} /* Eth_30_Tc3xx_Cfg_GetQosHandling() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetTxDescrRingForVlanPrio
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(uint8, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetTxDescrRingForVlanPrio( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 vlanPrio)
{
  return Eth_30_Tc3xx_Cfg_GetQosHandling(ctrlIdx)->VlanPrioTxDescrRingMap[vlanPrio];
} /* Eth_30_Tc3xx_Cfg_GetTxDescrRingForVlanPrio() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_IsShaperAvailable
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_IsShaperAvailable( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 descrRingIdx)
{
  return Eth_30_Tc3xx_Cfg_GetQosHandling(ctrlIdx)->ShaperAvailablility[descrRingIdx];
} /* Eth_30_Tc3xx_Cfg_IsShaperAvailable() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetEthSwtIfc
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(P2CONST(Eth_30_Tc3xx_EthSwtIfcType, AUTOMATIC, AUTOMATIC), ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetEthSwtIfc( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  return Eth_30_Tc3xx_Cfg_GetCtrlCfg(ctrlIdx)->EthSwtIfc;
} /* Eth_30_Tc3xx_Cfg_GetEthSwtIfc() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_IsEthSwtIfcToBeUsed
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_IsEthSwtIfcToBeUsed( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  boolean result = FALSE;

  if( Eth_30_Tc3xx_Cfg_GetEthSwtIfc(ctrlIdx) != NULL_PTR )
  {
    result = TRUE;
  }

  return result;
} /* Eth_30_Tc3xx_Cfg_IsEthSwtIfcToBeUsed() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_IsCtrlFeatEnabled
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_IsCtrlFeatEnabled( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 featBitMask)
{
  boolean result = FALSE;

  if( (Eth_30_Tc3xx_Cfg_GetCtrlCfg(ctrlIdx)->Features & featBitMask) != 0 )
  {
    result = TRUE;
  }

  return result;
} /* Eth_30_Tc3xx_Cfg_IsCtrlFeatEnabled() */


/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_IsQosEnabled
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_IsQosEnabled( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  return Eth_30_Tc3xx_Cfg_IsCtrlFeatEnabled(ctrlIdx, ETH_30_TC3XX_FEAT_QOS_ENABLED_MASK);
} /* Eth_30_Tc3xx_Cfg_IsQosEnabled() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_IsTimeSyncEnabled
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_IsTimeSyncEnabled( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  return Eth_30_Tc3xx_Cfg_IsCtrlFeatEnabled(ctrlIdx, ETH_30_TC3XX_FEAT_TIMESYNC_ENABLED_MASK);
} /* Eth_30_Tc3xx_Cfg_IsTimeSyncEnabled() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_IsFqtssEnabled
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_IsFqtssEnabled( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  return Eth_30_Tc3xx_Cfg_IsCtrlFeatEnabled(ctrlIdx, ETH_30_TC3XX_FEAT_FQTSS_ENABLED_MASK);
} /* Eth_30_Tc3xx_Cfg_IsTimeSyncEnabled() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_IsIpChecksumOffloadingEnabled
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_IsIpChecksumOffloadingEnabled( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  return Eth_30_Tc3xx_Cfg_IsCtrlFeatEnabled(ctrlIdx, ETH_30_TC3XX_FEAT_IP_CHECKSUM_OFFLOADING_ENABLED_MASK);
} /* Eth_30_Tc3xx_Cfg_IsIpChecksumOffloadingEnabled() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_IsProtocolChecksumOffloadingEnabled
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_IsProtocolChecksumOffloadingEnabled( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  return Eth_30_Tc3xx_Cfg_IsCtrlFeatEnabled(ctrlIdx, ETH_30_TC3XX_FEAT_PROTOCOL_CHECKSUM_OFFLOADING_ENABLED_MASK);
} /* Eth_30_Tc3xx_Cfg_IsProtocolChecksumOffloadingEnabled() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_IsRxInterruptModeEnabled
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_IsRxInterruptModeEnabled( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  /*! Internal comment removed.
 *
 *
 *
   */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  return ETH_30_TC3XX_ENABLE_RX_INTERRUPT;
} /* Eth_30_Tc3xx_Cfg_IsRxInterruptModeEnabled() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_IsTxInterruptModeEnabled
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_IsTxInterruptModeEnabled( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  /*! Internal comment removed.
 *
 *
 *
   */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  return ETH_30_TC3XX_ENABLE_TX_INTERRUPT;
} /* Eth_30_Tc3xx_Cfg_IsTxInterruptModeEnabled() */

# if ( ETH_30_TC3XX_DEM_ERROR_DETECT == STD_ON )
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Cfg_GetDemEventId
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_CFG_ACCESS_INLINE FUNC(Dem_EventIdType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Cfg_GetDemEventId(  /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  return Eth_30_Tc3xx_DemEvents[ctrlIdx];
}
# endif /* ETH_30_TC3XX_DEM_ERROR_DETECT */
# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# endif /* ETH_30_TC3XX_CFG_ACCESS_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_CfgAccess_Int.h
 *********************************************************************************************************************/

