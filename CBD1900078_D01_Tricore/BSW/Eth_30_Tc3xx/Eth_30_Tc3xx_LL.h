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
/*!        \file  Eth_30_Tc3xx_LL.h
 *        \brief  Lower layer header file
 *
 *      \details  Declaration and definition of lower layer part of Ethernet driver.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Benjamin Groebner             visbgr        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  00.01.00  2017-08-01  visbgr  -             Initial creation
 *  00.02.00  2018-01-03  visbgr  STORY-3570    TASK-60515 Provide DrvETh_Tc3xx Beta version using TriBoard TC3X9 V2.0
 *  01.00.00  2018-02-19  visbgr  STORY-4098    TASK-65966 Review Integration and Core Update
 *  02.00.00  2018-05-14  visbgr  STORYC-5156   TASK-73499 Implement prototype QoS support in implementation
 *                                STORYC-5967   TASK-82306 Testing and bugfixing of QoS RX prototype implementation
 *                                STORYC-5968   TASK-82307 Testing and bugfixing of FQTSS prototype implementation
 *                                STORYC-5155   TASK-73501 Finalize QoS support implementation
 *  02.01.00  2019-02-18  visbgr  STORY-10652   Update Core DrvEth_Tc3xxEthAsr
 *  03.00.00  2019-03-18  visbgr  ESCAN00101437 Possible memory violation in case of multi Eth driver configuration
 *                                ESCAN00101808 Compiler warning: Calling function without prototype
 *                                              Appl_UnlockEndinit / Appl_LockEndinit
 *                                ESCAN00101709 Missing overflow handling during global time retrieval
 *  03.00.01  2019-04-02  visbgr  STORYC-8019   Review Integration of DMA Review for TC3xx
 *                                ESCAN00101663 Memory corruption possible if RX buffers are configured smaller than
 *                                              1522 bytes
 *                                ESCAN00102625 Possible loss of interrupt could lead to stuck communication on
 *                                              Ethernet
 *********************************************************************************************************************/

#if !defined (ETH_30_TC3XX_LL_H)
# define ETH_30_TC3XX_LL_H

/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_LL_Regs.h"
# include "Eth_30_Tc3xx_LL_Types.h"
# include "Eth_30_Tc3xx_LL_Int.h"
# include "Eth_30_Tc3xx_IrqHandler_Int.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# ifndef ETH_30_TC3XX_LOCAL
#  define ETH_30_TC3XX_LL_LOCAL static
# endif
 
# ifndef ETH_30_TC3XX_LL_LOCAL_INLINE
#  define ETH_30_TC3XX_LL_LOCAL_INLINE LOCAL_INLINE
# endif


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/* ETH software version */
# define ETH_30_TC3XX_SW_MAJOR_VERSION                     (3u)
# define ETH_30_TC3XX_SW_MINOR_VERSION                     (0u)
# define ETH_30_TC3XX_SW_PATCH_VERSION                     (1u)

# define ETH_30_TC3XX_FRAME_TYPE_LEN_BYTE                  (2u)
# define ETH_30_TC3XX_DEST_SRC_MACS_LEN_BYTE               (12u)
# define ETH_30_TC3XX_HDR_LEN_BYTE                         (14u)
# define ETH_30_TC3XX_USED_FCS_LEN_BYTE                    (0u)
# define ETH_30_TC3XX_FCS_LEN_BYTE                         (4u)

# define ETH_30_TC3XX_ALIGN_PADDING                        (2u)

# define ETH_30_TC3XX_TX_DST_OFFSET_U8                     (0u)
# define ETH_30_TC3XX_TX_SRC_OFFSET_U8                     (6u)
# define ETH_30_TC3XX_TX_TYPE_OFFSET_U8                    (12u)

# define ETH_30_TC3XX_RX_DST_OFFSET_U8                     (2u)
# define ETH_30_TC3XX_RX_SRC_OFFSET_U8                     (8u)
# define ETH_30_TC3XX_RX_TYPE_OFFSET_U8                    (14u)

# define ETH_30_TC3XX_MMC_COUNTER_MAX_OFFSET               (0x0170u)
# define ETH_30_TC3XX_MMC_COUNTER_BASE_OFFSET              (0x0714u)

/*! Shaper/Descriptor ring identifier */
# define ETH_30_TC3XX_LL_LOW_PRIO_QUEUE_IDX                (0u)
# define ETH_30_TC3XX_LL_MID_0_PRIO_QUEUE_IDX              (1u)
# define ETH_30_TC3XX_LL_MID_1_PRIO_QUEUE_IDX              (2u)
# define ETH_30_TC3XX_LL_HIGH_PRIO_QUEUE_IDX               (3u)

# define ETH_30_TC3XX_LL_QOS_QUEUES_NUM                    (3u)

/*! Descriptor and Buffer Alignment restrictions */
# define ETH_30_TC3XX_LL_DESC_ALIGN_BYTE                   (16u)
# define ETH_30_TC3XX_LL_BUFF_ALIGN_BYTE                   (16u)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsTxPending
 **********************************************************************************************************************/
/*! \brief       Checks for pending Tx events
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller.
 *  \return      FALSE - There is no Tx event pending that must be confirmed
 *  \return      TRUE - There is at least one Tx event pending that must be confirmed
 *  \context     TASK|ISR1|ISR2
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTxPending(
    uint8 ctrlIdx);

 /**********************************************************************************************************************
  *  Eth_30_Tc3xx_LL_IsTxQueuePending
 **********************************************************************************************************************/
 /*! \brief       Checks for pending Tx Queue events
  *  \details     The function checks for pending Tx Queue events and sets respective Tx event flags
  *  \param[in]   ctrlIdx       Identifier of the Ethernet controller.
  *  \param[in]   descrRingIdx  Index of descriptor ring.
  *  \return      FALSE - There is no Tx event pending that must be confirmed
  *  \return      TRUE - There is at least one Tx Queue event pending that must be confirmed
  *  \context     TASK|ISR1|ISR2
  *  \synchronous TRUE
  *  \reentrant   FALSE
  *  \pre         -
  */
 ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTxQueuePending(
     uint8 ctrlIdx,
     uint8 descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsRxPending
 **********************************************************************************************************************/
/*! \brief       Checks for pending Rx events
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller.
 *  \return      FALSE - There is no Rx event pending that must be notified
 *  \return      TRUE - There is at least one Rx event pending that must be notified
 *  \context     TASK|ISR1|ISR2
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxPending(
    uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsRxQueuePending
 **********************************************************************************************************************/
/*! \brief       Checks for pending Rx Queue events
 *  \details     The function checks for pending Rx Queue events and sets respective Rx event flags
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller.
 *  \param[in]   descrRingIdx  Index of descriptor ring.
 *  \return      FALSE - There is no Rx event pending that must be notified
 *  \return      TRUE - There is at least one Rx event pending that must be notified
 *  \context     TASK|ISR1|ISR2
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxQueuePending(
    uint8 ctrlIdx,
    uint8 descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_InitializeRxDescriptor()
 *********************************************************************************************************************/
/*! \brief       Function for initializing an Rx descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be initialized
 *  \param[in]   descrRingIdx     Index of descriptor ring to be initialized
 *  \param[in]   descrIdx         Index of descriptor to be initialized
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_InitializeRxDescriptor(
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint16 descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_InitializeTxDescriptor()
 *********************************************************************************************************************/
/*! \brief       Function for initializing a Tx descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be initialized
 *  \param[in]   descrRingIdx     Index of descriptor ring to be initialized
 *  \param[in]   descrIdx         Index of descriptor to be initialized
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_InitializeTxDescriptor(
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint8 descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_SetDescriptorBaseAddresses()
 *********************************************************************************************************************/
/*! \brief       Function for announcing the descriptor base addresses to hardware
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which descriptors shall be announced
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetDescriptorBaseAddresses(
    uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_InitDescriptorStateVariables()
 *********************************************************************************************************************/
/*! \brief       Function for initializing descriptor state variables, if needed by the lower layer
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be initialized
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_InitDescriptorStateVariables(
    uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_EnableMiiAccess()
 *********************************************************************************************************************/
/*! \brief       Function for enabling the MII management access (SMI)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller where the MII access shall be enabled
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_EnableMiiAccess(
    uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_ResetCounters()
 *********************************************************************************************************************/
/*! \brief       Function for resetting statistic counters of the MAC
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which statistic counters should be reset
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetCounters(
    uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_StartTimesyncClock()
 *********************************************************************************************************************/
/*! \brief       Function for starting the timesync clock of the MAC
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the timesync clock shall be started
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_StartTimesyncClock(
    uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_PrepareTxDescriptorForIpChecksumOffloading()
 *********************************************************************************************************************/
/*! \brief       Function for enabling the IP checksum offload option in a Tx descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which checksum offloading shall be enabled
 *  \param[in]   descrRingIdx     Index of descriptor ring for which checksum offloading shall be enabled
 *  \param[in]   descrIdx         Index of descriptor for which checksum offloading shall be enabled
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PrepareTxDescriptorForIpChecksumOffloading(
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint8 descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_PrepareTxDescriptorForProtocolChecksumOffloading()
 *********************************************************************************************************************/
/*! \brief       Function for enabling the Protocol checksum offload option in a Tx descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which checksum offloading shall be enabled
 *  \param[in]   descrRingIdx     Index of descriptor ring for which checksum offloading shall be enabled
 *  \param[in]   descrIdx         Index of descriptor for which checksum offloading shall be enabled
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PrepareTxDescriptorForProtocolChecksumOffloading(
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint8 descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TriggerTransmission()
 *********************************************************************************************************************/
/*! \brief       Function for starting the transmission of a already prepared buffer an descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the transmission shall be triggered
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the transmission shall be triggered
 *  \param[in]   descrIdx         Index of descriptor for which the transmission shall be triggered
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TriggerTransmission(
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint8 descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_PrepareTxDescriptorForTimestamping()
 *********************************************************************************************************************/
/*! \brief       Function for enabling the timestamping option for a Tx descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which timestamping shall be prepared
 *  \param[in]   descrRingIdx     Index of descriptor ring for which timestamping shall be prepared
 *  \param[in]   descrIdx         Index of descriptor for which timestamping shall be prepared
 *  \param[in]   bufIdx           Index of buffer for which timestamping shall be prepared
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PrepareTxDescriptorForTimestamping(
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint8 descrIdx,
    uint8 bufIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_PrepareTxDescriptorForTransmission()
 *********************************************************************************************************************/
/*! \brief       Function for doing all necessary settings to prepare a Tx descriptor for transmission
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be used for transmission
 *  \param[in]   descrRingIdx     Index of descriptor ring to be used for transmission
 *  \param[in]   descrIdx         Index of descriptor to be transmitted
 *  \param[in]   bufIdx           Index of buffer to be transmitted
 *  \param[in]   lenByte          Length of frame to be transmitted
 *  \param[in]   bufPtr           Pointer to buffer to be transmitted
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PrepareTxDescriptorForTransmission(
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint8 descrIdx,
    uint8 bufIdx,
    uint16 lenByte,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) bufPtr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_RechargeTxDescriptor()
 *********************************************************************************************************************/
/*! \brief       Function for recharging a Tx descriptor, after the transmission of a frame was finished
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the descriptor shall be recharged
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the descriptor shall be recharged
 *  \param[in]   descrIdx         Index of descriptor which shall be recharged
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_RechargeTxDescriptor(
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint8 descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_ResetTimestampingInTxDescriptor
 *********************************************************************************************************************/
/*! \brief       Resets the timestamping request for the given tx descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the timestamping request shall be reset
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the timestamping request shall be reset
 *  \param[in]   descrIdx         Index of descriptor for which the timestamping request shall be reset
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetTimestampingInTxDescriptor(
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint8 descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_EnableMac()
 *********************************************************************************************************************/
/*! \brief       Function for enabling the MAC
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be enabled
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_EnableMac(
    uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_DisableMac()
 *********************************************************************************************************************/
/*! \brief       Function for disabling the MAC
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be disabled
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_DisableMac(
    uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsMacEnabled()
 *********************************************************************************************************************/
/*! \brief       Function for checking the mode of the MAC (enabled, disabled)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be checked for mode
 *  \return      TRUE - MAC is enabled
 *  \return      FALSE - MAC is disabled
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsMacEnabled(
    uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_WriteMacAddressToRegister()
 *********************************************************************************************************************/
/*! \brief       Function for writing the configured MAC address to the hardware register
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the MAC address shall be set
 *  \param[in]   macAddrPtr       Pointer to physical address to be set
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_WriteMacAddressToRegister(
    uint8 ctrlIdx,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) macAddrPtr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_PreResetMac()
 *********************************************************************************************************************/
/*! \brief       Function for hardware specific operations which need to be executed before MAC reset
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller which shall be reset
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PreResetMac(
    uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_ResetMac()
 *********************************************************************************************************************/
/*! \brief       Function for resetting the MAC (if needed by hardware)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller which shall be reset
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetMac(
    uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsResetMacFinished()
 *********************************************************************************************************************/
/*! \brief       Function for checking for the completion of the reset
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller which shall be checked for completion of reset
 *  \return      TRUE - MAC reset is finished
 *  \return      FALSE - MAC reset is not finished yet
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsResetMacFinished(
    uint8 ctrlIdx);

# if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_EnablePromiscuousMode()
 *********************************************************************************************************************/
/*! \brief       Function for enabling the promiscuous mode
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which promiscuous mode shall be enabled
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_EnablePromiscuousMode(
    uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_DisablePromiscuousMode()
 *********************************************************************************************************************/
/*! \brief       Function for disabling the promiscuous mode
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which promiscuous mode shall be disabled
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_DisablePromiscuousMode(
    uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_CloseAllMulticastFilters()
 *********************************************************************************************************************/
/*! \brief       Function for closing all multicast filters
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which all multicast filters shall be closed
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_CloseAllMulticastFilters(
    uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_SetMulticastFilteringMode()
 *********************************************************************************************************************/
/*! \brief       Function for enabling a certain multicast filter mode
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the multicast filter mode shall be set
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetMulticastFilteringMode(
    uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_SetUpperMulticastFilterBucketRegister()
 *********************************************************************************************************************/
/*! \brief       Function for writing the upper multicast filter bucket register
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the multicast bucket register shall be set
 *  \param[in]   bucketMask       Mask which shall be set
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetUpperMulticastFilterBucketRegister(
    uint8 ctrlIdx,
    uint32 bucketMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_SetLowerMulticastFilterBucketRegister()
 *********************************************************************************************************************/
/*! \brief       Function for writing the lower multicast filter bucket register
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the multicast bucket register shall be set
 *  \param[in]   bucketMask       Mask which shall be set
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetLowerMulticastFilterBucketRegister(
    uint8 ctrlIdx,
    uint32 bucketMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_ResetUpperMulticastFilterBucketRegister()
 *********************************************************************************************************************/
/*! \brief       Function writing resetting bits in the upper multicast filter bucket register
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the multicast bucket register shall be set
 *  \param[in]   bucketMask       Mask which shall be reset
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetUpperMulticastFilterBucketRegister(
    uint8 ctrlIdx,
    uint32 bucketMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_ResetLowerMulticastFilterBucketRegister()
 *********************************************************************************************************************/
/*! \brief       Function writing resetting bits in the lower multicast filter bucket register
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the multicast bucket register shall be set
 *  \param[in]   bucketMask       Mask which shall be reset
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetLowerMulticastFilterBucketRegister(
    uint8 ctrlIdx,
    uint32 bucketMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_CalculateMulticastFilterRegisterHash()
 *********************************************************************************************************************/
/*! \brief       Function for calculating a multicast filter has value
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the multicast bucket register shall be set
 *  \param[in]   macAddrPtr       Pointer to the physical address for which a hash shall be calculated
 *  \param[out]  hashPtr          Pointer to the variable which contains the calculated hash
 *  \param[out]  isUpperRegPtr    Pointer to the variable which contains the decision which filter register shall be
 *                                used
 *  \param[out]  bucketMaskPtr    Pointer to the variable which contains the mask for the filter register
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_CalculateMulticastFilterRegisterHash(
    uint8 ctrlIdx,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) macAddrPtr,
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) hashPtr,
    P2VAR(boolean, AUTOMATIC, AUTOMATIC) isUpperRegPtr,
    P2VAR(uint32, AUTOMATIC, AUTOMATIC) bucketMaskPtr);
# endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_WriteMiiTrigger()
 *********************************************************************************************************************/
/*! \brief       Function for triggering a write operation on the MII management access (SMI)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller  for which the MII write operation shall be triggered
 *  \param[in]   trcvIdx          Index of transceiver for which the MII write operation shall be triggered
 *  \param[in]   regIdx           Index of register for which the MII write operation shall be triggered
 *  \param[in]   regVal           Register value that shall be written
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_WriteMiiTrigger(
    uint8 ctrlIdx,
    uint8 trcvIdx,
    uint8 regIdx,
    uint16 regVal);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_ReadMiiTrigger()
 *********************************************************************************************************************/
/*! \brief       Function for triggering a read operation on the MII management access (SMI)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the MII read operation shall be triggered
 *  \param[in]   trcvIdx          Index of transceiver for which the MII read operation shall be triggered
 *  \param[in]   regIdx           Index of register for which the MII read operation shall be triggered
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ReadMiiTrigger(
    uint8 ctrlIdx,
    uint8 trcvIdx,
    uint8 regIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetReadMiiResult()
 *********************************************************************************************************************/
/*! \brief       Function for retrieving the result of a read operation on the MII management access (SMI)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the MII read operation result shall be retrieved
 *  \param[out]  regValPtr        Pointer to buffer where register value shall be stored
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetReadMiiResult(
    uint8 ctrlIdx,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) regValPtr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsMiiOperationPending()
 *********************************************************************************************************************/
/*! \brief       Function for checking the completion of an operation on the MII management access (SMI)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the MII operation completion shall be checked
 *  \return      TRUE - MII operation still pending
 *  \return      FALSE - MII operation not pending
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsMiiOperationPending(
    uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_SetTxEvents()
 *********************************************************************************************************************/
/*! \brief       Sets the Tx events for the respective descriptor rings
 *  \details     Function sets Tx events by calling Eth_30_Tc3xx_SetTxEvent() for each Tx descriptor ring having a
 *               pending Tx event (respective interrupt flag set).
 *  \param[in]   ctrlIdx          Index of controller pending tx events shall be queried for
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetTxEvents(
    uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver()
 *********************************************************************************************************************/
/*! \brief       Function for retrieving the information, if a Rx descriptor is owned by DMA or driver
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the owner of a descriptor shall be checked
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the owner of a descriptor shall be checked
 *  \param[in]   descrIdx         Index of descriptor for which the owner shall be checked
 *  \return      TRUE - descriptor is owned by driver
 *  \return      FALSE - descriptor is owned by DMA
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver(
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint16 descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsTxDescriptorOwnedByDriver()
 *********************************************************************************************************************/
/*! \brief       Function for retrieving the information, if a Tx descriptor is owned by DMA or driver
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the owner of a descriptor shall be checked
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the owner of a descriptor shall be checked
 *  \param[in]   descrIdx         Index of descriptor for which the owner shall be checked
 *  \return      TRUE - descriptor is owned by driver
 *  \return      FALSE - descriptor is owned by DMA
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTxDescriptorOwnedByDriver(
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint8 descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsErrorinRxDescriptor()
 *********************************************************************************************************************/
/*! \brief       Function for retrieving the information, if a error flag was set in a Rx descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the owner of a descriptor shall be checked
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the owner of a descriptor shall be checked
 *  \param[in]   descrIdx         Index of descriptor for which the owner shall be checked
 *  \return      TRUE - error flag is set in descriptor
 *  \return      FALSE - no error flags is set in descriptor
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsErrorinRxDescriptor(
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint16 descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_SetRxEvents()
 *********************************************************************************************************************/
/*! \brief       Sets the Rx events for the respective descriptor rings
 *  \details     Functions sets Rx event by calling Eth_30_Tc3xx_SetRxEvent() for each Rx descriptor ring having a
 *               pending Rx event (respective interrupt flag set).
 *  \param[in]   ctrlIdx          Index of controller pending rx events shall be queried for
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetRxEvents(
    uint8 ctrlIdx);

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_RearmMacForReception
 **********************************************************************************************************************/
/*! \brief       Rearms the MAC for being able to receive frames on the respective descriptor ring again
 *  \details     Function sets registers that rearm the RX DMA to receive frames on the respective RX descriptor
 *               ring again.
 *  \param[in]   ctrlIdx          Index of controller that shall be rearmed for reception
 *  \param[in]   descrRingIdx     Index of descriptor ring that shall be rearmed for reception
 *  \context     ANY
 *  \reentrant   TRUE - for different Eth controllers
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_RearmMacForReception(
    uint8 ctrlIdx,
    uint8 descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_RechargeRxDescriptor()
 *********************************************************************************************************************/
/*! \brief       Function for recharging a Rx descriptor, after the reception of a frame was finished
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the descriptor shall be recharged
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the descriptor shall be recharged
 *  \param[in]   descrIdx         Index of descriptor which shall be recharged
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_RechargeRxDescriptor(
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint16 descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_AdaptRxDescriptorRingAfterReception
 *********************************************************************************************************************/
/*! \brief       Function for hw specific Rx descriptor operations which are necessary after a frame has been received
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the descriptor shall be adapted
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the descriptor shall be adapted
 *  \param[in]   descrrIdx        Index of descriptor which shall be adapted
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_AdaptRxDescriptorRingAfterReception(
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint16 descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetFrameLengthFromRxDescriptor
 *********************************************************************************************************************/
/*! \brief       Function for retrieving the frame length of a received frame from a Rx descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the frame length shall be retrieved
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the frame length shall be retrieved
 *  \param[in]   descrIdx         Index of descriptor for which the frame length shall be retrieved
 *  \return      Length extracted from a Rx descriptor
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetFrameLengthFromRxDescriptor(
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint16 descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetMaxCounterOffset
 *********************************************************************************************************************/
/*! \brief       Returns the maximum counter offset within the statistic counter register block
 *  \details     Function returns the maximum counter offset of the Ethernet controllers statistic counters register
 *               block.
 *               during retrieval of the counter value.
 *  \param[in]   ctrlIdx          Index of controller
 *  \return      Amount of statistic counters
 *  \context     TASK
 *  \reentrant   TRUE - for different Eth controllers
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetMaxCounterOffset(
    uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetCounterValue
 *********************************************************************************************************************/
/*! \brief       Retrieves the value of the given statistics counter
 *  \details     Function checks if a valid statistics counter is addressed within the counter register block and if
 *               so returns its value.
 *  \param[in]   ctrlIdx          Index of controller
 *  \param[in]   counterOffset    Offset into the statistic counter register block
 *  \param[out]  counterValue     Value of the statistics counter
 *  \return      E_NOT_OK - Index results in addressing a non existing counter
 *  \return      E_OK - Counter value successfully retrieved
 *  \context     TASK
 *  \reentrant   TRUE - for different Eth controllers and counters
 *  \synchronous TRUE
 *  \pre         counterIdx must have been checked for being inside of the statistics counter register block
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetCounterValue(
    uint8 ctrlIdx,
    uint16 counterOffset,
    P2VAR(uint32, AUTOMATIC, AUTOMATIC) counterVal);

# if (ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetRxStats
 *********************************************************************************************************************/
/*! \brief       Retrieves the values of Rx statistics counters
 *  \details     Function reads a set of reception statistics counters and returns their values.
 *  \param[in]   ctrlIdx    Index of controller
 *  \param[out]  rxStatsPtr Pointer to the address where the Rx statistics counter values are stored
 *  \return      E_NOT_OK - Rx statistics counters not retrieved
 *  \return      E_OK - Rx statistics counters successfully retrieved
 *  \context     TASK
 *  \reentrant   TRUE - for different Eth controllers
 *  \synchronous TRUE
 *  \pre         ETH_30_TC3XX_EXCLUSIVE_AREA_DATA must be entered.
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetRxStats(
    uint8 ctrlIdx,
    P2VAR(Eth_RxStatsType, AUTOMATIC, AUTOMATIC) rxStatsPtr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetTxStats
 *********************************************************************************************************************/
/*! \brief       Retrieves the values of Tx statistics counters
 *  \details     Function reads a set of transmission statistics counters and returns their values.
 *  \param[in]   ctrlIdx    Index of controller
 *  \param[out]  rxStatsPtr Pointer to the address where the Tx statistics counter values are stored
 *  \return      E_NOT_OK - Rx statistics counters not retrieved
 *  \return      E_OK - Rx statistics counters successfully retrieved
 *  \context     TASK
 *  \reentrant   TRUE - for different Eth controllers
 *  \synchronous TRUE
 *  \pre         ETH_30_TC3XX_EXCLUSIVE_AREA_DATA must be entered.
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetTxStats(
    uint8 ctrlIdx,
    P2VAR(Eth_TxStatsType, AUTOMATIC, AUTOMATIC) txStatsPtr);
# endif /* ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_MainFunction()
 *********************************************************************************************************************/
/*! \brief       MainFunction for hardware specific cyclic operations
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_MainFunction( void );

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsTxPending
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTxPending(
  uint8 ctrlIdx)
{
  uint8_least queueCount;
  boolean isTxPend = FALSE;

  /* #10 Iterate over all used queues */
  for (queueCount = (uint8)Eth_30_Tc3xx_Cfg_GetTxDescrRingNum(ctrlIdx); queueCount > 0u; queueCount--)
  {
    uint8 queueIdx = (uint8)(queueCount - 1u);

    /* #110 If any checked TX queue has pending TX frames */
    if (Eth_30_Tc3xx_LL_IsTxQueuePending(ctrlIdx, queueIdx) == TRUE)
    {
      /* #1110 Return that a TX event is pending */
      isTxPend = TRUE;
    }
  }

  return isTxPend;
} /* Eth_30_Tc3xx_LL_IsTxPending() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsTxQueuePending
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTxQueuePending(
  uint8 ctrlIdx,
  uint8 descrRingIdx)
{
  boolean isTxPend = FALSE;
  uint8 curTxDescrIdx = Eth_30_Tc3xx_Cfg_GetTxDescrRingProcPos(ctrlIdx, descrRingIdx);

  /* PRQA S 3415 3 */ /* MD_Eth_30_Tc3xx_3415 */
  /* #10 Check if next descriptor to process is passed to driver already */
  if ((Eth_30_Tc3xx_LL_IsTxDescriptorOwnedByDriver(ctrlIdx, descrRingIdx, curTxDescrIdx) == TRUE) &&
      (Eth_30_Tc3xx_Cfg_GetTxDescrTxState(ctrlIdx, descrRingIdx, curTxDescrIdx) == ETH_30_TC3XX_DESCRIPTOR_READY))
  {
    /* #110 Is passed, set respective events for the core and signal the caller that he should trigger a re-check
     *      after processing of the checked descriptor */
    Eth_30_Tc3xx_SetTxEvent(ctrlIdx, descrRingIdx);
    isTxPend = TRUE;
  }

  return isTxPend;
} /* Eth_30_Tc3xx_LL_IsTxQueuePending() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsRxPending
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxPending(
  uint8 ctrlIdx)
{
  uint8_least queueCount;
  boolean isRxPend = FALSE;

  /* #10 Iterate over all used queues */
  for (queueCount = (uint8)Eth_30_Tc3xx_Cfg_GetRxDescrRingNum(ctrlIdx); queueCount > 0u; queueCount--)
  {
    uint8 queueIdx = (uint8)(queueCount - 1u);

    /* #110 If any checked RX queue has pending RX frames */
    if (Eth_30_Tc3xx_LL_IsRxQueuePending(ctrlIdx, queueIdx) == TRUE)
    {
      /* #1110 Return that a RX event is pending */
      isRxPend = TRUE;
    }
  }

  return isRxPend;
} /* Eth_30_Tc3xx_LL_IsRxPending() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsRxQueuePending
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxQueuePending(
    uint8 ctrlIdx,
    uint8 descrRingIdx)
{
  boolean isRxPend = FALSE;
  uint16 curRxDescrIdx = Eth_30_Tc3xx_Cfg_GetRxDescrRingProcPos(ctrlIdx, descrRingIdx);

  /* #10 Check if next descriptor to process is passed to driver already */
  if (Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver(ctrlIdx, descrRingIdx, curRxDescrIdx) == TRUE)
  {
    /* #110 Is passed, set respective events for the core and signal the caller that he should trigger a re-check
     *      after processing of the checked descriptor */
    Eth_30_Tc3xx_SetRxEvent(ctrlIdx, descrRingIdx);
    isRxPend = TRUE;
  }

  return isRxPend;
} /* Eth_30_Tc3xx_LL_IsRxQueuePending() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_InitializeRxDescriptor
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_InitializeRxDescriptor( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 descrRingIdx,
  uint16 descrIdx)
{
  /* #10 Write buffer address to descriptor */
  P2VAR(Eth_30_Tc3xx_RxDescriptorType, AUTOMATIC, AUTOMATIC) rxDescr =
      Eth_30_Tc3xx_Cfg_GetRxDescr(ctrlIdx, descrRingIdx, descrIdx);
  uint32 bufferOffset = descrIdx * Eth_30_Tc3xx_Cfg_GetRxBufferHandling(ctrlIdx, descrRingIdx)->AlignedSegmentSize +
      ETH_30_TC3XX_ALIGN_PADDING;

  /* PRQA S 0306 2 */ /* MD_Eth_0306 */
  rxDescr->RxDescrWord[ETH_30_TC3XX_DES0_IDX] =
    (uint32)(&Eth_30_Tc3xx_Cfg_GetRxBufferHandling(ctrlIdx, descrRingIdx)->RxBuffer[bufferOffset]);
  rxDescr->RxDescrWord[ETH_30_TC3XX_DES1_IDX] = 0ul;
  rxDescr->RxDescrWord[ETH_30_TC3XX_DES2_IDX] = 0ul;

/* #20 Set descriptor as owned by DMA, enable interrupt on completion */
  rxDescr->RxDescrWord[ETH_30_TC3XX_DES3_IDX] = (uint32)(ETH_30_TC3XX_RX3_DESC_OWN |
                                                         ETH_30_TC3XX_RX3_DESC_IOC |
                                                         ETH_30_TC3XX_RX3_DESC_BUF1V);

  /* #30 Initialize context descriptor to be able to capture timestamps */
  rxDescr->RxDescrWord[ETH_30_TC3XX_CNTXT_DES0_IDX] = 0ul;
  rxDescr->RxDescrWord[ETH_30_TC3XX_CNTXT_DES1_IDX] = 0ul;
  rxDescr->RxDescrWord[ETH_30_TC3XX_CNTXT_DES2_IDX] = 0ul;
  rxDescr->RxDescrWord[ETH_30_TC3XX_CNTXT_DES3_IDX] = (uint32)ETH_30_TC3XX_RX3_DESC_OWN;
} /* Eth_30_Tc3xx_LL_InitializeRxDescriptor() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_InitializeTxDescriptor
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Etnb_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_InitializeTxDescriptor(
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint8 descrIdx)
{
  P2VAR(Eth_30_Tc3xx_TxDescriptorType, AUTOMATIC, AUTOMATIC) txDescr =
      Eth_30_Tc3xx_Cfg_GetTxDescr(ctrlIdx, descrRingIdx, descrIdx);

  /* #10 Reset TX descriptor, set as owned by driver. No context descriptor needed for TX */
  txDescr->TxDescrWord[ETH_30_TC3XX_DES0_IDX] = 0ul;
  txDescr->TxDescrWord[ETH_30_TC3XX_DES1_IDX] = 0ul;
  txDescr->TxDescrWord[ETH_30_TC3XX_DES2_IDX] = 0ul;
  txDescr->TxDescrWord[ETH_30_TC3XX_DES3_IDX] = 0ul;
} /* Eth_30_Tc3xx_LL_InitializeTxDescriptor() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_SetDescriptorBaseAddresses
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
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetDescriptorBaseAddresses( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  uint8_least queueIdx;
  /* #10 Use queue count according to configuration - TX\RX descriptor number is always equal to each other */
  uint8_least queueCount = (uint8)Eth_30_Tc3xx_Cfg_GetTxDescrRingNum(ctrlIdx);

  /* #20 Iterate over used queues */
  for (queueIdx = 0u; queueIdx < queueCount; queueIdx++)
  {
    Eth_30_Tc3xx_RegOffsetType regOffsetRxDescRingLen;
    Eth_30_Tc3xx_RegOffsetType regOffsetTxDescRingLen;
    Eth_30_Tc3xx_RegOffsetType regOffsetRxDescStartAddr;
    Eth_30_Tc3xx_RegOffsetType regOffsetTxDescStartAddr;
    Eth_30_Tc3xx_RegOffsetType regOffsetRxDescTailAddr;
    Eth_30_Tc3xx_RegOffsetType regOffsetTxDescTailAddr;

    /* #30 Get TX/RX descriptor counts and addresses */
    uint16 rxDescCount = Eth_30_Tc3xx_Cfg_GetRxBufferHandling(ctrlIdx, (uint8)queueIdx)->DescNumber;
    uint16 txDescCount = Eth_30_Tc3xx_Cfg_GetTxBufferHandling(ctrlIdx)->TxDescNum;

    /* PRQA S 0303 6 */ /* MD_Eth_0303 */
    uint32 rxDescAddr = (uint32)
        (&Eth_30_Tc3xx_Cfg_GetRxDescr(ctrlIdx, (uint8)queueIdx, 0u)->RxDescrWord[ETH_30_TC3XX_DES0_IDX]);
    uint32 txDescAddr = (uint32)
        (&Eth_30_Tc3xx_Cfg_GetTxDescr(ctrlIdx, (uint8)queueIdx, 0u)->TxDescrWord[ETH_30_TC3XX_DES0_IDX]);
    uint32 rxDescLastAddr = (uint32)
        (&Eth_30_Tc3xx_Cfg_GetRxDescr(ctrlIdx, (uint8)queueIdx, (uint16)(rxDescCount - 1u))
                                                                   ->RxDescrWord[ETH_30_TC3XX_DES0_IDX]);

    switch ((uint8)queueIdx)
    {
    case ETH_30_TC3XX_LL_MID_0_PRIO_QUEUE_IDX:
      regOffsetRxDescRingLen   = ETH_30_TC3XX_REG_OFFS_DMA_CH1_RX_DESC_RING_LEN;
      regOffsetTxDescRingLen   = ETH_30_TC3XX_REG_OFFS_DMA_CH1_TX_DESC_RING_LEN;
      regOffsetRxDescStartAddr = ETH_30_TC3XX_REG_OFFS_DMA_CH1_RX_DESC_LIST_ADDR;
      regOffsetTxDescStartAddr = ETH_30_TC3XX_REG_OFFS_DMA_CH1_TX_DESC_LIST_ADDR;
      regOffsetRxDescTailAddr  = ETH_30_TC3XX_REG_OFFS_DMA_CH1_RX_DESC_TAIL_PTR;
      regOffsetTxDescTailAddr  = ETH_30_TC3XX_REG_OFFS_DMA_CH1_TX_DESC_TAIL_PTR;
      break;
    case ETH_30_TC3XX_LL_MID_1_PRIO_QUEUE_IDX:
      regOffsetRxDescRingLen   = ETH_30_TC3XX_REG_OFFS_DMA_CH2_RX_DESC_RING_LEN;
      regOffsetTxDescRingLen   = ETH_30_TC3XX_REG_OFFS_DMA_CH2_TX_DESC_RING_LEN;
      regOffsetRxDescStartAddr = ETH_30_TC3XX_REG_OFFS_DMA_CH2_RX_DESC_LIST_ADDR;
      regOffsetTxDescStartAddr = ETH_30_TC3XX_REG_OFFS_DMA_CH2_TX_DESC_LIST_ADDR;
      regOffsetRxDescTailAddr  = ETH_30_TC3XX_REG_OFFS_DMA_CH2_RX_DESC_TAIL_PTR;
      regOffsetTxDescTailAddr  = ETH_30_TC3XX_REG_OFFS_DMA_CH2_TX_DESC_TAIL_PTR;
      break;
    case ETH_30_TC3XX_LL_HIGH_PRIO_QUEUE_IDX:
      regOffsetRxDescRingLen   = ETH_30_TC3XX_REG_OFFS_DMA_CH3_RX_DESC_RING_LEN;
      regOffsetTxDescRingLen   = ETH_30_TC3XX_REG_OFFS_DMA_CH3_TX_DESC_RING_LEN;
      regOffsetRxDescStartAddr = ETH_30_TC3XX_REG_OFFS_DMA_CH3_RX_DESC_LIST_ADDR;
      regOffsetTxDescStartAddr = ETH_30_TC3XX_REG_OFFS_DMA_CH3_TX_DESC_LIST_ADDR;
      regOffsetRxDescTailAddr  = ETH_30_TC3XX_REG_OFFS_DMA_CH3_RX_DESC_TAIL_PTR;
      regOffsetTxDescTailAddr  = ETH_30_TC3XX_REG_OFFS_DMA_CH3_TX_DESC_TAIL_PTR;
      break;
    default:
      regOffsetRxDescRingLen   = ETH_30_TC3XX_REG_OFFS_DMA_CH0_RX_DESC_RING_LEN;
      regOffsetTxDescRingLen   = ETH_30_TC3XX_REG_OFFS_DMA_CH0_TX_DESC_RING_LEN;
      regOffsetRxDescStartAddr = ETH_30_TC3XX_REG_OFFS_DMA_CH0_RX_DESC_LIST_ADDR;
      regOffsetTxDescStartAddr = ETH_30_TC3XX_REG_OFFS_DMA_CH0_TX_DESC_LIST_ADDR;
      regOffsetRxDescTailAddr  = ETH_30_TC3XX_REG_OFFS_DMA_CH0_RX_DESC_TAIL_PTR;
      regOffsetTxDescTailAddr  = ETH_30_TC3XX_REG_OFFS_DMA_CH0_TX_DESC_TAIL_PTR;
    }

    /* #40 Announce ring length to hardware */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffsetRxDescRingLen, ETH_30_TC3XX_REG_DMA_CHN_RX_DESC_RING_LEN &
                            (Eth_30_Tc3xx_RegWidthType)((2u * rxDescCount) - 1u)); /* -1 described in manual */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffsetTxDescRingLen, ETH_30_TC3XX_REG_DMA_CHN_TX_DESC_RING_LEN &
                            (Eth_30_Tc3xx_RegWidthType)(txDescCount - 1u)); /* -1 described in manual */

    /* #50 Announce descriptor ring to the hardware */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffsetRxDescStartAddr, rxDescAddr);
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffsetTxDescStartAddr, txDescAddr);

    /* #60 RX Tail Pointer points to the last descriptor */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffsetRxDescTailAddr, rxDescLastAddr);

    /* #70 TX Tail Pointer points to the first descriptor */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffsetTxDescTailAddr, txDescAddr);
  }
} /* Eth_30_Tc3xx_LL_SetDescriptorBaseAddresses() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_InitDescriptorStateVariables
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_InitDescriptorStateVariables( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
} /* Eth_30_Tc3xx_LL_InitDescriptorStateVariables() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_EnableMiiAccess
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Etnb_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_EnableMiiAccess(
  uint8 ctrlIdx)
{
  /* Register is writable in supervisor mode only and is ENDINIT protected */
  Appl_UnlockEndinit();

  /* #10 Delete Disable Request Bit in ETH_CLC register - otherwise module is not active */
  Eth_30_Tc3xx_Reg_Write_Protected(ctrlIdx, ETH_30_TC3XX_REG_OFFS_CLC, 0ul);

  /* #20 configure MII mode and pin muxing configuration */
  Eth_30_Tc3xx_Reg_Write_Protected(ctrlIdx, ETH_30_TC3XX_REG_OFFS_ETH_GPCTL,
                                            Eth_30_Tc3xx_Cfg_GetLLCtrlCfgData(ctrlIdx)->GPCTL_Reg);

  Appl_LockEndinit();
} /* Eth_30_Tc3xx_LL_EnableMiiAccess() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_ResetCounters
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetCounters( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  /* #10 Reset statistic counters */
  Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_CNTRL, ETH_30_TC3XX_REG_MMC_CNTRL_RST);
} /* Eth_30_Tc3xx_LL_ResetCounters() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_StartTimesyncClock
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_StartTimesyncClock( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  /* #10 Start time synchronization clock */
  Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_TIMESTAMP_CONTROL,
                                       ETH_30_TC3XX_REG_MAC_TIMESTAMP_CONTROL_TSADDREG);
} /* Eth_30_Tc3xx_LL_StartTimesyncClock() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_PrepareTxDescriptorForTransmission
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PrepareTxDescriptorForTransmission( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint8 descrIdx,
    uint8 bufIdx,
    uint16 lenByte,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) bufPtr)
{
  P2VAR(Eth_30_Tc3xx_TxDescriptorType, AUTOMATIC, AUTOMATIC) txDescr =
      Eth_30_Tc3xx_Cfg_GetTxDescr(ctrlIdx, descrRingIdx, descrIdx);

  /* #10 Set buffer address, interrupt on completion, first + last descriptor */
  /* PRQA S 0306 1 */ /* MD_Eth_0306 */
  txDescr->TxDescrWord[ETH_30_TC3XX_DES0_IDX] = (uint32)(bufPtr);

  txDescr->TxDescrWord[ETH_30_TC3XX_DES2_IDX] = (uint32)(ETH_30_TC3XX_TX2_DESC_IOC |
                                                        (ETH_30_TC3XX_TX2_DESC_BUF1_LEN_MASK & lenByte));

  txDescr->TxDescrWord[ETH_30_TC3XX_DES3_IDX] = (uint32)(ETH_30_TC3XX_TX3_DESC_FD |
                                                         ETH_30_TC3XX_TX3_DESC_LD |
                                                        (ETH_30_TC3XX_TX3_DESC_FL_MASK & (lenByte +
                                                                                          ETH_30_TC3XX_HDR_LEN_BYTE)));

  ETH_30_TC3XX_DUMMY_STATEMENT(bufIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
} /* Eth_30_Tc3xx_LL_PrepareTxDescriptorForTransmission() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_RechargeTxDescriptor
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_RechargeTxDescriptor( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 descrRingIdx,
  uint8 descrIdx)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  ETH_30_TC3XX_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  ETH_30_TC3XX_DUMMY_STATEMENT(descrIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
} /* Eth_30_Tc3xx_LL_RechargeTxDescriptor() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_ResetTimestampingInTxDescriptor
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetTimestampingInTxDescriptor( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint8 descrIdx)
{
  /* #10 Reset PTP descriptor flag */
  if (Eth_30_Tc3xx_Cfg_IsTimeSyncEnabled(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_Cfg_GetTxDescr(ctrlIdx, descrRingIdx, descrIdx)->TxDescrWord[ETH_30_TC3XX_DES2_IDX] &=
        (uint32)~ETH_30_TC3XX_TX2_DESC_TTSE;
  }
} /* Eth_30_Tc3xx_LL_ResetTimestampingInTxDescriptor() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_PrepareTxDescriptorForIpChecksumOffloading
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PrepareTxDescriptorForIpChecksumOffloading( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint8 descrIdx)
{
  /* #10 Enable checksum offloading for IPv4-Header */
  if (Eth_30_Tc3xx_Cfg_IsIpChecksumOffloadingEnabled(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_Cfg_GetTxDescr(ctrlIdx, descrRingIdx, descrIdx)->TxDescrWord[ETH_30_TC3XX_DES3_IDX] |=
        (ETH_30_TC3XX_TX3_DESC_IP_OFFLOAD << ETH_30_TC3XX_TX3_DESC_CIC_SHIFT);
  }
} /* Eth_30_Tc3xx_LL_PrepareTxDescriptorForIpChecksumOffloading() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_PrepareTxDescriptorForProtocolChecksumOffloading
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PrepareTxDescriptorForProtocolChecksumOffloading( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint8 descrIdx)
{
  /* #10 Enable transport protocol offloading for this descriptor */
  if (Eth_30_Tc3xx_Cfg_IsProtocolChecksumOffloadingEnabled(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_Cfg_GetTxDescr(ctrlIdx, descrRingIdx, descrIdx)->TxDescrWord[ETH_30_TC3XX_DES3_IDX] |=
        (ETH_30_TC3XX_TX3_DESC_TRANSPORT_OFFLOAD << ETH_30_TC3XX_TX3_DESC_CIC_SHIFT);
  }
} /* Eth_30_Tc3xx_LL_PrepareTxDescriptorForProtocolChecksumOffloading() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_TriggerTransmission
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TriggerTransmission( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint8 descrIdx)
{
  Eth_30_Tc3xx_RegOffsetType regOffset;
  P2VAR(Eth_30_Tc3xx_TxDescriptorType, AUTOMATIC, AUTOMATIC) txDescr =
      Eth_30_Tc3xx_Cfg_GetTxDescr(ctrlIdx, descrRingIdx, descrIdx);

  /* #10 Set descriptor as owned by DMA */
  txDescr->TxDescrWord[ETH_30_TC3XX_DES3_IDX] |= ETH_30_TC3XX_TX3_DESC_OWN;

  /* #20 Calculate next tail pointer address with regard to wraparound */
  if(descrIdx < (Eth_30_Tc3xx_Cfg_GetTxBufferNum(ctrlIdx) - 1u))
  {
    descrIdx++;
  }
  else
  {
    descrIdx = 0u;
  }
  txDescr = Eth_30_Tc3xx_Cfg_GetTxDescr(ctrlIdx, descrRingIdx, descrIdx);

  /* #30 Set tail pointer to start transmission */
  if (descrRingIdx == ETH_30_TC3XX_LL_HIGH_PRIO_QUEUE_IDX)
  {
    regOffset = ETH_30_TC3XX_REG_OFFS_DMA_CH3_TX_DESC_TAIL_PTR;
  }
  else if (descrRingIdx == ETH_30_TC3XX_LL_MID_1_PRIO_QUEUE_IDX)
  {
    regOffset = ETH_30_TC3XX_REG_OFFS_DMA_CH2_TX_DESC_TAIL_PTR;
  }
  else if (descrRingIdx == ETH_30_TC3XX_LL_MID_0_PRIO_QUEUE_IDX)
  {
    regOffset = ETH_30_TC3XX_REG_OFFS_DMA_CH1_TX_DESC_TAIL_PTR;
  }
  else
  {
    regOffset = ETH_30_TC3XX_REG_OFFS_DMA_CH0_TX_DESC_TAIL_PTR;
  }
  /* PRQA S 0303 1 */ /* MD_Eth_0303 */
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffset, (uint32)(&(txDescr->TxDescrWord[ETH_30_TC3XX_DES0_IDX])));
} /* Eth_30_Tc3xx_LL_TriggerTransmission() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_PrepareTxDescriptorForTimestamping
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PrepareTxDescriptorForTimestamping( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint8 descrIdx,
    uint8 bufIdx)
{
  /* - #10 Enable timestamping for this descriptor */
  if (Eth_30_Tc3xx_Cfg_IsTimeSyncEnabled(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_Cfg_GetTxDescr(ctrlIdx, descrRingIdx, descrIdx)->TxDescrWord[ETH_30_TC3XX_DES2_IDX] |=
                                                                              ETH_30_TC3XX_TX2_DESC_TTSE;
  }

  ETH_30_TC3XX_DUMMY_STATEMENT(bufIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
} /* Eth_30_Tc3xx_LL_PrepareTxDescriptorForTimestamping() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_EnableMac
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_EnableMac( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx)
{

  /* #10 Enable MAC */
   Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_PMT_CTRL, ETH_30_TC3XX_REG_PMT_CTRL_PWR_DOWN);

  /* #20 Enable frame transmission and reception in DMA module */
  Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH0_RX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR);
  Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH0_TX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST);

  if(Eth_30_Tc3xx_Cfg_IsQosEnabled(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH1_RX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR);
    Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH1_TX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST);
    Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH2_RX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR);
    Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH2_TX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST);
    Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH3_RX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR);
    Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH3_TX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST);
  }

  /* #30 Enable frame transmission and reception in MAC */
  Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_CFG, ETH_30_TC3XX_REG_CFG_RE_TE);
} /* Eth_30_Tc3xx_LL_EnableMac() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_DisableMac
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_DisableMac( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx)
{

  /* #10 Disable frame transmission and reception in DMA module */
  Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH0_RX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR);
  Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH0_TX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST);

  if(Eth_30_Tc3xx_Cfg_IsQosEnabled(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH1_RX_CNTRL,
                                           ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR);
    Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH1_TX_CNTRL,
                                           ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST);
    Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH2_RX_CNTRL,
                                           ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR);
    Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH2_TX_CNTRL,
                                           ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST);
    Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH3_RX_CNTRL,
                                           ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR);
    Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH3_TX_CNTRL,
                                           ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST);
  }

  /* #20 Disable frame transmission and reception in MAC */
  Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_CFG, ETH_30_TC3XX_REG_CFG_RE_TE);
} /* Eth_30_Tc3xx_LL_DisableMac() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsMacEnabled
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE)  Eth_30_Tc3xx_LL_IsMacEnabled( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx)
{
  /* #10 Return status of MAC transmission / reception enabled bits */
  return Eth_30_Tc3xx_Reg_IsBitMaskSet(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_CFG, ETH_30_TC3XX_REG_CFG_RE_TE);
} /* Eth_30_Tc3xx_LL_IsMacEnabled() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_WriteMacAddressToRegister
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_WriteMacAddressToRegister( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) macAddrPtr)
{
  /* #10 Write Mac address to registers */
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_ADDR0_HIGH,
    (uint32)((uint32)macAddrPtr[5] <<  8u) |
            ((uint32)macAddrPtr[4] <<  0u) );
  Eth_30_Tc3xx_Reg_Write(ctrlIdx,  ETH_30_TC3XX_REG_OFFS_ADDR0_LOW,
    (uint32)((uint32)macAddrPtr[3] << 24u) |
            ((uint32)macAddrPtr[2] << 16u) |
            ((uint32)macAddrPtr[1] <<  8u) |
            ((uint32)macAddrPtr[0] <<  0u) );
} /* Eth_30_Tc3xx_LL_WriteMacAddressToRegister() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_PreResetMac
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PreResetMac( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx)
{
  /* #10 Disable Interrupts which should not be active during controller initialization */
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_INT_EN, 0ul);

  Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH0_INT_EN, 0ul);

  if (Eth_30_Tc3xx_Cfg_IsQosEnabled(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH1_INT_EN, 0ul);
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH2_INT_EN, 0ul);
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH3_INT_EN, 0ul);
  }
} /* Eth_30_Tc3xx_LL_PreResetMac() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_ResetMac
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetMac( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx)
{
  /* #10 Reset MAC */
  Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_MODE, ETH_30_TC3XX_REG_DMA_MODE_SWR);
} /* Eth_30_Tc3xx_LL_ResetMac() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsResetMacFinished
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsResetMacFinished( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx)
{
  /* #10 Return status of MAC reset bit */
  return (boolean)((Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_MODE) &
                                                   ETH_30_TC3XX_REG_DMA_MODE_SWR) == 0ul);
} /* Eth_30_Tc3xx_LL_IsResetMacFinished() */

# if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_EnablePromiscuousMode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_EnablePromiscuousMode( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx)
{
  /* #10 Enable promiscuous mode */
  Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_PACKET_FILTER, ETH_30_TC3XX_REG_PACKET_FILTER_PR);
} /* Eth_30_Tc3xx_LL_EnablePromiscuousMode() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_DisablePromiscuousMode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_DisablePromiscuousMode( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx)
{
  /* #10 Disable promiscuous mode */
  Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_PACKET_FILTER, ETH_30_TC3XX_REG_PACKET_FILTER_PR);
} /* Eth_30_Tc3xx_LL_DisablePromiscuousMode() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_CloseAllMulticastFilters
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_CloseAllMulticastFilters( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
} /* Eth_30_Tc3xx_LL_CloseAllMulticastFilters() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_SetMulticastFilteringMode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetMulticastFilteringMode( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
} /* Eth_30_Tc3xx_LL_SetMulticastFilteringMode() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_SetUpperMulticastFilterBucketRegister
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetUpperMulticastFilterBucketRegister( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx,
    uint32 bucketMask)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  ETH_30_TC3XX_DUMMY_STATEMENT(bucketMask); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
} /* Eth_30_Tc3xx_LL_SetUpperMulticastFilterBucketRegister() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_SetLowerMulticastFilterBucketRegister
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetLowerMulticastFilterBucketRegister( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx,
    uint32 bucketMask)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  ETH_30_TC3XX_DUMMY_STATEMENT(bucketMask); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
} /* Eth_30_Tc3xx_LL_SetLowerMulticastFilterBucketRegister() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_ResetUpperMulticastFilterBucketRegister
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetUpperMulticastFilterBucketRegister( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx,
    uint32 bucketMask)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  ETH_30_TC3XX_DUMMY_STATEMENT(bucketMask); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
} /* Eth_30_Tc3xx_LL_ResetUpperMulticastFilterBucketRegister() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_ResetLowerMulticastFilterBucketRegister
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetLowerMulticastFilterBucketRegister( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx,
    uint32 bucketMask)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  ETH_30_TC3XX_DUMMY_STATEMENT(bucketMask); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
} /* Eth_30_Tc3xx_LL_ResetLowerMulticastFilterBucketRegister() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_CalculateMulticastFilterRegisterHash
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_CalculateMulticastFilterRegisterHash( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
            uint8                          ctrlIdx,
    P2CONST(uint8,   AUTOMATIC, AUTOMATIC) macAddrPtr,
      P2VAR(uint8,   AUTOMATIC, AUTOMATIC) hashPtr,
      P2VAR(boolean, AUTOMATIC, AUTOMATIC) isUpperRegPtr,
      P2VAR(uint32,  AUTOMATIC, AUTOMATIC) bucketMaskPtr)
{
  /* #10 Return dummy values */
  *hashPtr = 0u;
  *bucketMaskPtr = 0ul;
  *isUpperRegPtr = FALSE;

  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  ETH_30_TC3XX_DUMMY_STATEMENT(macAddrPtr); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
} /* Eth_30_Tc3xx_LL_CalculateMulticastFilterRegisterHash() */
# endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_WriteMiiTrigger
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_WriteMiiTrigger( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx,
    uint8 trcvIdx,
    uint8 regIdx,
    uint16 regVal)
{
  /* #10 Prepare MII register value */
  uint32 ctrlRegVal = ETH_30_TC3XX_REG_MDIO_ADDR_GB | ETH_30_TC3XX_REG_MDIO_ADDR_WRITE |
  ((((uint32)regIdx) << ETH_30_TC3XX_REG_MDIO_ADDR_RDA_SHIFT) & ETH_30_TC3XX_REG_MDIO_ADDR_RDA_MASK) |
  ((((uint32)trcvIdx) << ETH_30_TC3XX_REG_MDIO_ADDR_PA_SHIFT) & ETH_30_TC3XX_REG_MDIO_ADDR_PA_MASK) |
  (Eth_30_Tc3xx_Cfg_GetLLCtrlCfgData(ctrlIdx)->MdcCsrRegValue & ETH_30_TC3XX_REG_MDIO_ADDR_CR_MASK);

  /* #20 Trigger a write command with the prepared values */
  /* PRQA S 0306 2 */ /* MD_Eth_0306 */
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MDIO_DATA, ((uint32)regVal) & ETH_30_TC3XX_REG_MDIO_DATA_MASK);
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MDIO_ADDR, ctrlRegVal);
} /* Eth_30_Tc3xx_LL_WriteMiiTrigger() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_ReadMiiTrigger
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ReadMiiTrigger( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx,
    uint8 trcvIdx,
    uint8 regIdx)
{
  /* #10 Prepare MII register value */
  uint32 ctrlRegVal = ETH_30_TC3XX_REG_MDIO_ADDR_GB | ETH_30_TC3XX_REG_MDIO_ADDR_READ |
  ((((uint32)regIdx) << ETH_30_TC3XX_REG_MDIO_ADDR_RDA_SHIFT) & ETH_30_TC3XX_REG_MDIO_ADDR_RDA_MASK) |
  ((((uint32)trcvIdx) << ETH_30_TC3XX_REG_MDIO_ADDR_PA_SHIFT) & ETH_30_TC3XX_REG_MDIO_ADDR_PA_MASK) |
  (Eth_30_Tc3xx_Cfg_GetLLCtrlCfgData(ctrlIdx)->MdcCsrRegValue & ETH_30_TC3XX_REG_MDIO_ADDR_CR_MASK);

  /* #20 Trigger a read operation */
  /* PRQA S 0306 1 */ /* MD_Eth_0306 */
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MDIO_ADDR, ctrlRegVal);
} /* Eth_30_Tc3xx_LL_ReadMiiTrigger() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_GetReadMiiResult
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetReadMiiResult( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) regValPtr) /* PRQA S 3673 */ /* MD_Eth_30_Tc3xx_3673 */
{
  /* #10 Read back the result of a Mii read operation */
  *regValPtr = (uint16)(Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MDIO_DATA) &
                                                       ETH_30_TC3XX_REG_MDIO_DATA_MASK);
} /* Eth_30_Tc3xx_LL_GetReadMiiResult() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsMiiOperationPending
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsMiiOperationPending( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx)
{
  /* #10 Return status of MII interface busy bit */
  return Eth_30_Tc3xx_Reg_IsBitMaskSet(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MDIO_ADDR, ETH_30_TC3XX_REG_MDIO_ADDR_GB);
} /* Eth_30_Tc3xx_LL_IsMiiOperationPending() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_SetTxEvents
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetTxEvents( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx)
{
  /* #10 Trigger Tx event evaluation */
  (void)Eth_30_Tc3xx_LL_IsTxPending(ctrlIdx);
} /* Eth_30_Tc3xx_LL_SetTxEvents() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint16 descrIdx)
{
  /* #10 Return status of OWN bit in Rx descriptor */
  return (boolean)((ETH_30_TC3XX_RX3_DESC_OWN &
           Eth_30_Tc3xx_Cfg_GetRxDescr(ctrlIdx, descrRingIdx, descrIdx)->RxDescrWord[ETH_30_TC3XX_DES3_IDX]) == 0ul);
} /* Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsTxDescriptorOwnedByDriver
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTxDescriptorOwnedByDriver( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint8 descrIdx)
{
  /* #10 Return status of OWN bit in Tx descriptor */
  return (boolean)(((uint32)(ETH_30_TC3XX_TX3_DESC_OWN &
          Eth_30_Tc3xx_Cfg_GetTxDescr(ctrlIdx, descrRingIdx, descrIdx)->TxDescrWord[ETH_30_TC3XX_DES3_IDX])) == 0ul);
} /* Eth_30_Tc3xx_LL_IsTxDescriptorOwnedByDriver() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsErrorinRxDescriptor
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
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsErrorinRxDescriptor( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint16 descrIdx)
{
  boolean errorInDescriptor;
  uint16 FrameLen = Eth_30_Tc3xx_LL_GetFrameLengthFromRxDescriptor(ctrlIdx, descrRingIdx, descrIdx);
  Eth_30_Tc3xx_RxDescriptorType* rxDescPtr = Eth_30_Tc3xx_Cfg_GetRxDescr(ctrlIdx, descrRingIdx, descrIdx);

  /* #10 Check whether descriptor was split into more than one descriptor (FD+LD not set, e.g. because frame is larger
   *     than the default HW limit of 1518/1522(VLAN tagged) bytes for normal frames or a configured lower limit in
   *     the DMA_CHi_RX_CONTROL register) or error flags are set */
  if(((rxDescPtr->RxDescrWord[ETH_30_TC3XX_DES3_IDX] & ETH_30_TC3XX_RX3_DESC_FD)   == 0ul) ||
     ((rxDescPtr->RxDescrWord[ETH_30_TC3XX_DES3_IDX] & ETH_30_TC3XX_RX3_DESC_LD)   == 0ul) ||
     ((rxDescPtr->RxDescrWord[ETH_30_TC3XX_DES3_IDX] & ETH_30_TC3XX_RX3_DESC_ES)   != 0ul) ||
     ((rxDescPtr->RxDescrWord[ETH_30_TC3XX_DES3_IDX] & ETH_30_TC3XX_RX3_DESC_CTXT) != 0ul))
  {
    errorInDescriptor = TRUE;
  }
  /* #20 Check whether received frame size exceeds configured frame size (because of buffer alignment and size
   *     requirements (e.g. DMA_CHi_RX_CONTROL register with fields RBSZ_13_y and RBSZ_x_0 the actual buffer size in
   *     the memory can be larger so these frames have to blocked by software!)*/
  else if((FrameLen + ETH_30_TC3XX_FCS_LEN_BYTE)
  /* FCS not copied to memory / included in FrameLen therefore adding constant FCS length value here! */
                   > (Eth_30_Tc3xx_Cfg_GetRxBufferHandling(ctrlIdx, descrRingIdx)->MaximumFrameSize))
  {
    errorInDescriptor = TRUE;
  }
  else
  {
    errorInDescriptor = FALSE;
  }

  return errorInDescriptor;
} /* Eth_30_Tc3xx_LL_IsErrorinRxDescriptor() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_SetRxEvents
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetRxEvents( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx)
{
  /* #10 Trigger Rx event evaluation */
  (void)Eth_30_Tc3xx_LL_IsRxPending(ctrlIdx);
} /* Eth_30_Tc3xx_LL_SetRxEvents() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_RearmMacForReception
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_RearmMacForReception( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx,
    uint8 descrRingIdx)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  ETH_30_TC3XX_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
} /* Eth_30_Tc3xx_LL_RearmMacForReception() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_RechargeRxDescriptor
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_RechargeRxDescriptor( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint16 descrIdx)
{
  /* #10 Call Eth_30_Tc3xx_LL_InitializeRxDescriptor which will reinitialize the descriptor */
  Eth_30_Tc3xx_LL_InitializeRxDescriptor(ctrlIdx, descrRingIdx, descrIdx);
} /* Eth_30_Tc3xx_LL_RechargeRxDescriptor() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_AdaptRxDescriptorRingAfterReception
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_AdaptRxDescriptorRingAfterReception( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint16 descrIdx)
{
  Eth_30_Tc3xx_RegOffsetType regOffset;

  if(descrRingIdx == ETH_30_TC3XX_LL_HIGH_PRIO_QUEUE_IDX)
  {
    regOffset = ETH_30_TC3XX_REG_OFFS_DMA_CH3_RX_DESC_TAIL_PTR;
  }
  else if(descrRingIdx == ETH_30_TC3XX_LL_MID_1_PRIO_QUEUE_IDX)
  {
    regOffset = ETH_30_TC3XX_REG_OFFS_DMA_CH2_RX_DESC_TAIL_PTR;
  }
  else if(descrRingIdx == ETH_30_TC3XX_LL_MID_0_PRIO_QUEUE_IDX)
  {
    regOffset = ETH_30_TC3XX_REG_OFFS_DMA_CH1_RX_DESC_TAIL_PTR;
  }
  else
  {
    regOffset = ETH_30_TC3XX_REG_OFFS_DMA_CH0_RX_DESC_TAIL_PTR;
  }

  /* #10 set tail pointer to next descriptor */
  /* PRQA S 0303 1 */ /* MD_Eth_0303 */
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffset, (uint32)
      (&Eth_30_Tc3xx_Cfg_GetRxDescr(ctrlIdx, descrRingIdx, descrIdx)->RxDescrWord[ETH_30_TC3XX_DES0_IDX]));
} /* Eth_30_Tc3xx_LL_AdaptRxDescriptorRingAfterReception() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_GetFrameLengthFromRxDescriptor
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetFrameLengthFromRxDescriptor( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx,
    uint8 descrRingIdx,
    uint16 descrIdx)
{
  /* #10 Extract length of a received frame from a descriptor */
  return (uint16)(Eth_30_Tc3xx_Cfg_GetRxDescr(ctrlIdx, descrRingIdx, descrIdx)->RxDescrWord[ETH_30_TC3XX_DES3_IDX] &
                    ETH_30_TC3XX_RX3_DESC_FL_MASK);
} /* Eth_30_Tc3xx_LL_GetFrameLengthFromRxDescriptor() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetMaxCounterOffset
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetMaxCounterOffset( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx)
{
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 Return max counter offset */
  return ETH_30_TC3XX_MMC_COUNTER_MAX_OFFSET;
} /* Eth_30_Tc3xx_LL_GetMaxCounterOffset() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetCounterValue
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetCounterValue( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx,
    uint16 counterOffset,
    P2VAR(uint32, AUTOMATIC, AUTOMATIC) counterVal)
{
  Std_ReturnType retVal = E_OK;

  /* #10 Get statistics register with related offset */
  Eth_30_Tc3xx_RegOffsetType regOffset = ETH_30_TC3XX_MMC_COUNTER_BASE_OFFSET + counterOffset;
  (*counterVal) = Eth_30_Tc3xx_Reg_Read(ctrlIdx, regOffset);

  return retVal;
} /* Eth_30_Tc3xx_LL_GetCounterValue() */

# if (ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetRxStats
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetRxStats( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx,
    P2VAR(Eth_RxStatsType, AUTOMATIC, AUTOMATIC) rxStatsPtr)
{
  /* #10 Read the reception statistics counter values */
  rxStatsPtr->RxStatsDropEvents =
      (Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FIFO_OVFL)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_CRC_ERROR)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_ALIGN)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_RUNT)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_JABBER)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_UNDERSIZE_G)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_OVERSIZE_G));
  rxStatsPtr->RxStatsOctets =
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_OCTETS_GB);
  rxStatsPtr->RxStatsPkts =
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES);
  rxStatsPtr->RxStatsBroadcastPkts =
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_BROADCAST_FRAMES);
  rxStatsPtr->RxStatsMulticastPkts =
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_MULTICAST_FRAMES);
  rxStatsPtr->RxStatsCrcAlignErrors =
      (Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_CRC_ERROR)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_ALIGN));
  rxStatsPtr->RxStatsUndersizePkts =
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_UNDERSIZE_G);
  rxStatsPtr->RxStatsOversizePkts =
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_OVERSIZE_G);
  rxStatsPtr->RxStatsFragments =
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_RUNT);
  rxStatsPtr->RxStatsJabbers =
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_JABBER);
  rxStatsPtr->RxStatsPkts64Octets =
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES_64);
  rxStatsPtr->RxStatsPkts65to127Octets =
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES_64_TO_127);
  rxStatsPtr->RxStatsPkts128to255Octets =
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES_128_TO_255);
  rxStatsPtr->RxStatsPkts256to511Octets =
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES_256_TO_511);
  rxStatsPtr->RxStatsPkts512to1023Octets =
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES_512_TO_1023);
  rxStatsPtr->RxStatsPkts1024to1518Octets =
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES_1024_TO_MAX);
  rxStatsPtr->RxUnicastFrames =
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_UNICAST_G_FRAMES);
  rxStatsPtr->RxStatsCollisions =
      (Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_TX_SINGLE_COL)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_TX_MULTI_COL)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_TX_LATE_COL)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_TX_EXC_COL));

  return E_OK;
} /* Eth_30_Tc3xx_LL_GetRxStats() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetTxStats
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetTxStats( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
        uint8                                  ctrlIdx,
  P2VAR(Eth_TxStatsType, AUTOMATIC, AUTOMATIC) txStatsPtr)
{
  /* #10 Read the transmission statistics counter values */
  txStatsPtr->TxNumberOfOctets = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_TX_OCTETS_GB);
  txStatsPtr->TxNUcastPkts    = (Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_TX_BROADCASTS_GB)
                               + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_TX_MULTICASTS_GB));
  txStatsPtr->TxUniCastPkts    = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_TX_UNICASTS_GB);

  return E_OK;
} /* Eth_30_Tc3xx_LL_GetTxStats() */
# endif /* ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_MainFunction
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_MainFunction( void ) /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
{
  /* #10 Nothing to do here */
} /* Eth_30_Tc3xx_LL_MainFunction() */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ETH_30_TC3XX_LL_H */

/* module specific MISRA deviations:

 */
/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL.h
 *********************************************************************************************************************/

