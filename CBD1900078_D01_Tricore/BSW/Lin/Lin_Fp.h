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
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Lin_Fp.h
 *        \brief  AUTOSAR LIN Driver Frame Processor Interface
 *
 *      \details  Internal frame processor interface which is common for LIN controller and byte based peripheral units.
 *
 *********************************************************************************************************************/

#if !defined (LIN_FP_H)
#define LIN_FP_H

 /* Frame processor status returns */
#define LIN_FP_STATUS_EMPTY        0 /*!< If the queue empty (i.e. no relevant bit are set) */
#define LIN_FP_STATUS_SUCCESSFUL   1 /*!< If the frame without any error done */
#define LIN_FP_STATUS_HEADERERROR  2 /*!< A error in the header (header not successful sent) */
#define LIN_FP_STATUS_ERROR        3 /*!< A error in the response (header successful sent, response not successful sent or received) */
#define LIN_FP_STATUS_NO_RESPONSE  4 /*!< Frame time out and no bytes are received */

#define LIN_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/***********************************************************************************************************************
 *  Lin_Fp_GlobalInit
 **********************************************************************************************************************/
/*! \brief       Initializes the frame processor.
 *  \details     Channel independent initializing of the frame processor.
 *  \pre         Lin interrupts must be locked.
 *  \context     TASK
 *  \reentrant   FALSE
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_Fp_GlobalInit( void );

/***********************************************************************************************************************
 *  Lin_Fp_ChannelInit
 **********************************************************************************************************************/
/*! \brief       Initializes the frame processor channel.
 *  \details     Channel dependent initializing of the frame processor. After initializing the channel must be wake
 *               (disable wakeup detection, disable transmission and reception).
 *  \param[in]   ChannelConfigIdx: The valid index of the 1:1 relation pointing to Lin_ChannelConfig or Lin_ChannelData
 *  \pre         Lin interrupts must be locked.
 *  \context     TASK
 *  \reentrant   TRUE for different handles (LIN channels)
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_Fp_ChannelInit( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx );

/***********************************************************************************************************************
 *  Lin_Fp_Interrupt
 **********************************************************************************************************************/
/*! \brief       Provide calculate time for hardware.
 *  \details     - In case of SOFTWARE frame processor: Forward interrupt to provide calculate time for the software
 *                 frame processor.
 *               - In case of HARDWARE frame processor: No implementation needed because the hardware needs no
 *                 calculation time. If hardware frame processor needs the interrupt this function could implement.
 *  \param[in]   ChannelConfigIdx: The valid index of the 1:1 relation pointing to Lin_ChannelConfig or Lin_ChannelData
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE for different handles (LIN channels)
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE_ISR) Lin_Fp_Interrupt( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx );

/***********************************************************************************************************************
 *  Lin_Fp_DequeueStatus
 **********************************************************************************************************************/
/*! \brief       Dequeue and return the status of the frame processor.
 *  \details     A real hardware has typical a queue with the length of one.
 *  \param[in]   ChannelConfigIdx: The valid index of the 1:1 relation pointing to Lin_ChannelConfig or Lin_ChannelData
 *  \return      LIN_FP_EMPTY:       If the queue empty (i.e. no relevant bit are set)
 *  \return      LIN_FP_SUCCESSFUL:  If the frame without any error done
 *  \return      LIN_FP_HEADERERROR: A error in the header (header not successful sent)
 *  \return      LIN_FP_ERROR:       A error in the response (header successful sent, response not successful sent)
 *  \return      LIN_FP_NO_RESPONSE: Frame time out and no bytes are received. If time out not supported implement
 *                                   Lin_Fp_HasNoResponseBytes() and Lin_Hw_IfRxByteNotStarted()
 *  \pre         Lin interrupts must be locked.
 *  \context     TASK/ISR
 *  \reentrant   TRUE for different handles (LIN channels)
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(uint8, LIN_CODE) Lin_Fp_DequeueStatus( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx );

/***********************************************************************************************************************
 *  Lin_Fp_StartTxFrame
 **********************************************************************************************************************/
/*! \brief       Stop any communication and start a new TX frame.
 *  \details     Ongoing communication must stop (if possible).
 *  \param[in]   ChannelConfigIdx: The valid index of the 1:1 relation pointing to Lin_ChannelConfig or Lin_ChannelData
 *  \param[in]   PduInfoPtr: Pointer to PDU containing the PID, Checksum model, Response type, Dl and SDU data pointer.
 *  \pre         Lin interrupts must be locked.
 *  \context     TASK/ISR
 *  \reentrant   TRUE for different handles (LIN channels)
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_Fp_StartTxFrame( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx,
                                                  CONSTP2CONST(Lin_PduType, AUTOMATIC, LIN_APPL_VAR) PduInfoPtr );

/***********************************************************************************************************************
 *  Lin_Fp_StartRxFrame
 **********************************************************************************************************************/
/*! \brief       Stop any communication and start a new RX frame.
 *  \details     Ongoing communication must stop.
 *  \param[in]   ChannelConfigIdx: The valid index of the 1:1 relation pointing to Lin_ChannelConfig or Lin_ChannelData
 *  \param[in]   PduInfoPtr: Pointer to PDU containing the PID, Checksum model, Response type, Dl and SDU data pointer.
 *  \pre         Lin interrupts must be locked.
 *  \context     TASK/ISR
 *  \reentrant   TRUE for different handles (LIN channels)
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_Fp_StartRxFrame( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx,
                                                  CONSTP2CONST(Lin_PduType, AUTOMATIC, LIN_APPL_VAR) PduInfoPtr );

/***********************************************************************************************************************
 *  Lin_Fp_StartS2sFrame
 **********************************************************************************************************************/
/*! \brief       Stop any communication and start a new S2S frame.
 *  \details     Ongoing communication must stop.
 *  \param[in]   ChannelConfigIdx: The valid index of the 1:1 relation pointing to Lin_ChannelConfig or Lin_ChannelData
 *  \param[in]   PduInfoPtr: Pointer to PDU containing the PID, Checksum model, Response type, Dl and SDU data pointer.
 *  \pre         Lin interrupts must be locked.
 *  \context     TASK/ISR
 *  \reentrant   TRUE for different handles (LIN channels)
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_Fp_StartS2sFrame( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx,
                                                  CONSTP2CONST(Lin_PduType, AUTOMATIC, LIN_APPL_VAR) PduInfoPtr );

/***********************************************************************************************************************
 *  Lin_Fp_StartWakeupPulse
 **********************************************************************************************************************/
/*! \brief       Stop any communication and start a wakeup pulse
 *  \details     Ongoing communication must stop.
 *  \param[in]   ChannelConfigIdx: The valid index of the 1:1 relation pointing to Lin_ChannelConfig or Lin_ChannelData
 *  \pre         Lin interrupts must be locked.
 *  \context     TASK/ISR
 *  \reentrant   TRUE for different handles (LIN channels)
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_Fp_StartWakeupPulse( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx );

/***********************************************************************************************************************
 *  Lin_Fp_SaveRxData
 **********************************************************************************************************************/
/*! \brief       Save the received data (from hardware) to channel data buffer Lin_DataBuffer (RAM).
 *  \details     In case of a hardware buffer with uint8 array layout, no data must copied.
 *  \param[in]   ChannelConfigIdx: The valid index of the 1:1 relation pointing to Lin_ChannelConfig or Lin_ChannelData
 *  \pre         Lin interrupts must be locked.
 *  \context     TASK/ISR
 *  \reentrant   TRUE for different handles (LIN channels)
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_Fp_SaveRxData( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx );

/***********************************************************************************************************************
 *  Lin_Fp_DisableWakupDetection
 **********************************************************************************************************************/
/*! \brief       Disable wakeup detection, disable transmission and reception
 *  \details     -
 *  \param[in]   ChannelConfigIdx: The valid index of the 1:1 relation pointing to Lin_ChannelConfig or Lin_ChannelData
 *  \pre         Lin interrupts must be locked.
 *  \context     TASK/ISR
 *  \reentrant   TRUE for different handles (LIN channels)
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_Fp_DisableWakupDetection( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx );

/***********************************************************************************************************************
 *  Lin_Fp_EnableWakupDetection
 **********************************************************************************************************************/
/*! \brief       Enable wakeup detection, disable transmission and reception
 *  \details     -
 *  \param[in]   ChannelConfigIdx: The valid index of the 1:1 relation pointing to Lin_ChannelConfig or Lin_ChannelData
 *  \pre         Lin interrupts must be locked.
 *  \context     TASK/ISR
 *  \reentrant   TRUE for different handles (LIN channels)
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_Fp_EnableWakupDetection ( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx );

/***********************************************************************************************************************
 *  Lin_Fp_HasNoResponseBytes
 **********************************************************************************************************************/
/*! \brief       Check how much bytes are received
 *  \details     This function does not change any data.
 *  \param[in]   ChannelConfigIdx: The valid index of the 1:1 relation pointing to Lin_ChannelConfig or Lin_ChannelData
 *  \return      TRUE: If no bytes received
 *  \return      FALSE: If more the 0 bytes received or if the frame processor has a working frame time out
 *  \pre         Lin interrupts must be locked.
 *  \context     TASK/ISR
 *  \reentrant   TRUE for different handles (LIN channels)
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(boolean, LIN_CODE) Lin_Fp_HasNoResponseBytes( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx );

/***********************************************************************************************************************
 *  Lin_Hw_IfRxByteNotStarted
 **********************************************************************************************************************/
/*! \brief       Check if a start bit received
 *  \details     Optional if hardware support this function and hardware has no working frame time out. This function
 *               does not change any data.
 *  \param[in]   ChannelConfigIdx: The valid index of the 1:1 relation pointing to Lin_ChannelConfig or Lin_ChannelData
 *  \return      TRUE: If a start bit received
 *  \return      FALSE: If no start bit received, or if not supported/implemented
 *  \pre         Lin interrupts must be locked.
 *  \context     TASK/ISR
 *  \reentrant   TRUE for different handles (LIN channels)
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(boolean, LIN_CODE) Lin_Hw_IfRxByteNotStarted( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx );

/***********************************************************************************************************************
 *  Lin_Fp_GetReceiveBufferPointer
 **********************************************************************************************************************/
/*! \brief       Return the receive buffer pointer of frame processor.
 *  \details     For the LIN response reception the bytes of the SDU buffer shall be allocated in increasingly
 *               consecutive address order. The LIN frame data length information defines the minimum SDU buffer length.
 *               This function does not change any data.
 *  \param[in]   ChannelConfigIdx: The valid index of the 1:1 relation pointing to Lin_ChannelConfig or Lin_ChannelData
 *  \return      The pointer to the buffer
 *  \pre         Lin interrupts must be locked.
 *  \context     TASK/ISR
 *  \reentrant   TRUE for different handles (LIN channels)
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(uint8*, LIN_CODE) Lin_Fp_GetReceiveBufferPointer( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx );


#define LIN_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* LIN_FP_H */

/**********************************************************************************************************************
 *  END OF FILE: Lin_Fp.h
 *********************************************************************************************************************/
