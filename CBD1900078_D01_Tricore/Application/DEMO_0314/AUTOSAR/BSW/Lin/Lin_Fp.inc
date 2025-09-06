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
/**        \file  Lin_Fp.inc
 *        \brief  AUTOSAR LIN Driver Frame Processor
 *
 *      \details  Interface implementation for ASCLIN hardware frame processor (Tricore)
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Lutz Pflueger                 vislpr        Vector Informatik GmbH
 *  Andreas Pick                  visap         Vector Informatik GmbH
 *  Jan Gaukel                    visjgl        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  14.00.00  2018-04-03  vislpr  -             Implement new AUTOSAR 4 LIN driver for Tricore
 *                        visap   -             Rework review findings
 *  14.01.00  2018-08-31  visjgl  TASK-89105    MISRA 2012
 *                        visjgl  FIX-4948      No Lin communication possible if F_ASCLINS is selected as Clock Source
 *********************************************************************************************************************/

#if !defined (LIN_FP_INC)
#define LIN_FP_INC

/* Component version information (decimal version of ALM implementation package) */
#define LIN_PLATFORM_MAJOR_VERSION 14
#define LIN_PLATFORM_MINOR_VERSION 1
#define LIN_PLATFORM_PATCH_VERSION 0

/**********************************************************************************************************************
 *  Hardware Software Interface
 *********************************************************************************************************************/
 /*!
 * \internal
 * Hardware interface structures for memory-mapped i/o
 *
 *  Hardware manual:
 *   - tc27x_ts_V3.0_OPEN_MARKET.pdf, chapter 1.19 Asynchronous/Synchronous Interface (ASCLIN)
 *
 *  Errata sheet:
 *   - TC27x_BC_Errata_Sheet_rev1v5_2015_09_16.pdf
 *   - TC26x Step: ES-BC, BC Rel. 1.0, 2016-12-22
 *   - TC22x/TC21x Step: ES-AB, AB, Rel. 1.4, 2017-10-10
 *
 *  Safety manuals:
 *   - AURIX Safety Manual AP32224 V1.5 2017-05
 *
 *  Specifics:
 *   - End-init protection is used as specified in the HW manual and the MSR architecture design.
 *
 *  Used registers and bits are defined below.
 *   - for bit mask definitions refer to Lin.c.
 *
 *  Operating modes:
 *   - refer to the states specified in the CAD
 *   - note: parts of the state machine are implemented in HW
 *
 *  Hardware features related to independence or partitioning:
 *   - none
 *
 *  Access mechanism:
 *   - memory mapped i/o registers
 *
 *  Hardware diagnostics:
 *   - none
 *
 * \endinternal
 */

/*! Hardware register layout */
struct Lin_RegisterStructTag
{
  VAR(uint32, TYPEDEF) CLC;         /*!< Offset Address 0x0000: Clock Control Register */
  VAR(uint32, TYPEDEF) IOCR;        /*!< Offset Address 0x0004: Input Output Control Register */
  VAR(uint32, TYPEDEF) ID;          /*!< Offset Address 0x0008: Module Identification Register */
  VAR(uint32, TYPEDEF) TXFIFOCON;   /*!< Offset Address 0x000C: TX FIFO Configuration Register */
  VAR(uint32, TYPEDEF) RXFIFOCON;   /*!< Offset Address 0x0010: RX FIFO Configuration Register */
  VAR(uint32, TYPEDEF) BITCON;      /*!< Offset Address 0x0014: Bit Timing Configuration Register */
  VAR(uint32, TYPEDEF) FRAMECON;    /*!< Offset Address 0x0018: Frame Configuration Register */
  VAR(uint32, TYPEDEF) DATCON;      /*!< Offset Address 0x001C: Data Configuration Register */
  VAR(uint32, TYPEDEF) BRG;         /*!< Offset Address 0x0020: Baud Rate Generation Register */
  VAR(uint32, TYPEDEF) BRD;         /*!< Offset Address 0x0024: Baud Rate Detection Register */
  VAR(uint32, TYPEDEF) LINCON;      /*!< Offset Address 0x0028: LIN Configuration Register */
  VAR(uint32, TYPEDEF) LINBTIMER;   /*!< Offset Address 0x002C: LIN Break Timer Register */
  VAR(uint32, TYPEDEF) LINHTIMER;   /*!< Offset Address 0x0030: LIN Header Timer Register */
  VAR(uint32, TYPEDEF) FLAGS;       /*!< Offset Address 0x0034: Flags Register */
  VAR(uint32, TYPEDEF) FLAGSSET;    /*!< Offset Address 0x0038: Flags Set Register */
  VAR(uint32, TYPEDEF) FLAGSCLEAR;  /*!< Offset Address 0x003C: Flags Clear Register */
  VAR(uint32, TYPEDEF) FLAGSENABLE; /*!< Offset Address 0x0040: Flags Enable Register */
  VAR(uint32, TYPEDEF) TXDATA;      /*!< Offset Address 0x0044: Transmit Data Register */
  VAR(uint32, TYPEDEF) RXDATA;      /*!< Offset Address 0x0048: Receive Data Register */
  VAR(uint32, TYPEDEF) CSR;         /*!< Offset Address 0x004C: Clock Selection Register */
};


/**********************************************************************************************************************
 *  Used registers and bits (bit mask)
 *********************************************************************************************************************/
/*! Bitmasks for register LIN_CSR */
          /* Clock Select */
#define   LIN_CSR_CLKSEL_MASK       ((uint32)0x0000001FU)

/*! Defines for register LIN_FRAMECON */
          /* ODD=0, PEN=0, CEN=1, MSB=0, MODE=3(LIN), LEAD=2, STOP=1, IDLE=1 */
#define   LIN_FRAMECON_DEFAULT      ((uint32)0x20032240U)

/*! Defines for register LIN_LINCON */
          /* enable master mode, enable hardware checksum logic  0x06000000U */
#define   LIN_LINCON_DEFAULT        ((uint32)0x06000000U)

/*! Defines for register LIN_BITCON */
          /* 3 samples per bit, bits 7,8 and 9, oversampling factor 16 */
#define   LIN_BITCON_DEFAULT        ((uint32)0x890F0000U)

/*! Defines for register LIN_BTIMER */
          /* 14 bit times sync break length */
#define   LIN_LINBTIMER_DEFAULT     ((uint32)0x0000000EU)

/*! Defines for register LIN_DATCON */
          /* response timeout to 256 */
#define   LIN_DATCON_MAXRESP        ((uint32)0x00FF0000U)
          /* response mode set to response part */
#define   LIN_DATCON_RM_RESP        ((uint32)0x00004000U)
          /* classic checksum mode */
#define   LIN_DATCON_CSM_CLASSIC    ((uint32)0x00000000U)
          /* classic checksum mode */
#define   LIN_DATCON_CSM_ENH        ((uint32)0x00008000U)
          /* header only mode */
#define   LIN_DATCON_HO             ((uint32)0x00002000U)

/*! Defines for register LIN_RXFIFOCON */
          /* flush Rx FIFO, disable inlet */
#define   LIN_RXFIFOCON_CLEAR_STOP  ((uint32)0x00000001U)
          /* enable inlet, get 1 byte per read */
#define   LIN_RXFIFOCON_ENABLE      ((uint32)0x00000042U)
          /* FIFO filling level mask */
#define   LIN_RXFIFOCON_FILL_MASK   ((uint32)0x001F0000U)

/*! Defines for register LIN_TXFIFOCON */
          /* flush Tx FIFO, disable outlet, inlet width = 1 */
#define   LIN_TXFIFOCON_CLEAR_STOP  ((uint32)0x00000041U)
          /* enable outlet, inlet width = 1 => take one byte into FIFO per write to TXDATA register */
#define   LIN_TXFIFOCON_ENABLE      ((uint32)0x00000042U)

/*! Defines for register LIN_LINHTIMER */
          /* default header timeout value of 49 bits */
#define   LIN_LINHTIMER_DEFAULT     ((uint32)0x00000031U)

/*! Define for registers FLAGS, FLAGSENABLE, FLAGSCLEAR, FLAGSSET ( interrupt bits / flags ) */
          /* Transmit Header End */
#define   LIN_FLAGS_TH              ((uint32)0x00000001U)
          /* Transmit Response End */
#define   LIN_FLAGS_TR              ((uint32)0x00000002U)
          /* Receive Response End */
#define   LIN_FLAGS_RR              ((uint32)0x00000008U)
          /* Falling Edge 1 -> 0, detecting a wakeup frame is only possible via the FED flag */
#define   LIN_FLAGS_FED             ((uint32)0x00000020U)
          /* Transmit Wake Request */
#define   LIN_FLAGS_TWRQ            ((uint32)0x00002000U)
          /* Transmit Header Request */
#define   LIN_FLAGS_THRQ            ((uint32)0x00004000U)
          /* Transmit Response Request */
#define   LIN_FLAGS_TRRQ            ((uint32)0x00008000U)
          /* Framing Error */
#define   LIN_FLAGS_FE              ((uint32)0x00040000U)
          /* Response Timeout */
#define   LIN_FLAGS_RT              ((uint32)0x00100000U)
          /* LIN Checksum Error */
#define   LIN_FLAGS_LC              ((uint32)0x01000000U)
          /* Collision Detection */
#define   LIN_FLAGS_CE              ((uint32)0x02000000U)

#define   LIN_FLAGSENABLE_DISABLE   ((uint32)( 0U ))

#define   LIN_FLAGS_ERROR           ((uint32)( LIN_FLAGS_FE | \
                                                     LIN_FLAGS_RT | \
                                                     LIN_FLAGS_LC | \
                                                     LIN_FLAGS_CE ))

#define   LIN_FLAGS_ALL             ((uint32)( LIN_FLAGS_ERROR | \
                                                     LIN_FLAGS_TR    | \
                                                     LIN_FLAGS_RR    | \
                                                     LIN_FLAGS_TH ))

#define   LIN_WAKEUP_PATTERN        ((uint8)0x80U)


/**********************************************************************************************************************
 *  Os API
 *********************************************************************************************************************/
#include "Os.h"
#if !defined osWritePeripheral32
# define LIN_PROTECTED_AREA_ENDINIT 0
/* PRQA S 3453 1 */ /* MD_MSR_FctLikeMacro */
# define osWritePeripheral32( a, b, c ) *((uint32*)(b)) = (c)
#endif

/***********************************************************************************************************************
 *  Appl_UnlockEndinit
 **********************************************************************************************************************/
/*! \brief       Unlock Endinit-Protect.
 *  \details     Unlocks registers that are normally protected through Endinit-Protect.
 *  \pre         LIN interrupts for hardware channel of Channel must be locked.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        The user application has provide this function.
 **********************************************************************************************************************/
extern FUNC(void, LIN_APPL_CODE) Appl_UnlockEndinit( void );


/***********************************************************************************************************************
 *  Appl_LockEndinit
 **********************************************************************************************************************/
/*! \brief       Lock Endinit-Protect.
 *  \details     Locks registers that are normally protected through Endinit-Protect.
 *  \pre         LIN interrupts for hardware channel of Channel must be locked.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        The user application has provide this function.
 **********************************************************************************************************************/
extern FUNC(void, LIN_APPL_CODE) Appl_LockEndinit( void );


/***********************************************************************************************************************
 *  Lin_CommonFrameSetup
 **********************************************************************************************************************/
/*! \brief       Set up common part of all frames
 *  \details     Set up header data, checksum and data length
 *  \param[in]   ChannelConfigIdx: Access to all Channel data (register, data, ...)
 *  \param[in]   PduInfoPtr: Pointer to PDU containing the PID, Checksum model, Response type, Dl and SDU data pointer.
 *  \pre         Internal function. Do not call.
 *  \context     TASK/ISR
 *  \reentrant   TRUE for different LIN channels
 *  \synchronous FALSE
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_CommonFrameSetup( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx,
                                                   CONSTP2CONST(Lin_PduType, AUTOMATIC, LIN_APPL_VAR) PduInfoPtr );


/***********************************************************************************************************************
 *  Lin_StartFrameTransmission
 **********************************************************************************************************************/
/*! \brief       Common frame start command
 *  \details     -
 *  \param[in]   ChannelConfigIdx: Access to all Channel data (register, data, ...)
 *  \pre         Internal function. Do not call.
 *  \context     TASK/ISR
 *  \reentrant   TRUE for different LIN channels
 *  \synchronous FALSE
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_StartFrameTransmission( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx );


#define LIN_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  Internal Functions Implementation
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  Lin_CommonFrameSetup
 **********************************************************************************************************************/
 /*!
 * \internal
 * - flush Tx FIFO, disable FIFO outlet
 * - clear all flags
 * - configure common PDU part to be sent
 * \endinternal
 */
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_CommonFrameSetup( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx, /* PRQA S 3206 */ /* MD_LIN_3206 */
                                                   CONSTP2CONST(Lin_PduType, AUTOMATIC, LIN_APPL_VAR) PduInfoPtr )
{
  P2VAR(Lin_RegisterStruct, AUTOMATIC, LIN_VAR_REGS) ChannelRegisterBase = Lin_GetChannelBaseAddressOfChannelConfig( ChannelConfigIdx ); /* PRQA S 0303 */ /* MD_LIN_0303 */
	
  LIN_LOCAL CONST(uint32, LIN_CONST) ResponseTimeoutDurations[8] =
  {  /* response timeout durations for different frame lengths in bit times */
    ((uint32)28U  << 16U),   /* 1 databyte  */
    ((uint32)42U  << 16U),   /* 2 databytes */
    ((uint32)56U  << 16U),   /* 3 databytes */
    ((uint32)70U  << 16U),   /* 4 databytes */
    ((uint32)84U  << 16U),   /* 5 databytes */
    ((uint32)98U  << 16U),   /* 6 databytes */
    ((uint32)112U << 16U),   /* 7 databytes */
    ((uint32)126U << 16U),   /* 8 databytes */
  };

  /* flush Tx FIFO, disable FIFO outlet */
  ChannelRegisterBase->RXFIFOCON  = LIN_RXFIFOCON_CLEAR_STOP; /* SBSW_LIN_PTR_HW */
  ChannelRegisterBase->TXFIFOCON  = LIN_TXFIFOCON_CLEAR_STOP; /* SBSW_LIN_PTR_HW */

  /* clear all flags */
  ChannelRegisterBase->FLAGSCLEAR = ChannelRegisterBase->FLAGS; /* SBSW_LIN_PTR_HW */

  /* configure common PDU part to be sent */
  ChannelRegisterBase->TXDATA = (uint32)PduInfoPtr->Pid; /* SBSW_LIN_PTR_HW */
  ChannelRegisterBase->DATCON = /* SBSW_LIN_PTR_HW */
    (uint32)( (ResponseTimeoutDurations[(PduInfoPtr->Dl-1U)]) |
              ((PduInfoPtr->Cs == (Lin_FrameCsModelType)LIN_ENHANCED_CS) ? LIN_DATCON_CSM_ENH : LIN_DATCON_CSM_CLASSIC) |
              (LIN_DATCON_RM_RESP) |
              ((uint32)(((uint32)PduInfoPtr->Dl)-1U)) );
}

/***********************************************************************************************************************
 *  Lin_StartFrameTransmission
 **********************************************************************************************************************/
 /*!
 * \internal
 * - trigger header transmission and enable Tx Fifo here to allow sending the PID
 * \endinternal
 */
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_StartFrameTransmission( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx ) /* PRQA S 3206 */ /* MD_LIN_3206 */
{
  P2VAR(Lin_RegisterStruct, AUTOMATIC, LIN_VAR_REGS) ChannelRegisterBase = Lin_GetChannelBaseAddressOfChannelConfig( ChannelConfigIdx ); /* PRQA S 0303 */ /* MD_LIN_0303 */
  /* trigger header transmission and enable Tx Fifo here to allow sending the PID */
  ChannelRegisterBase->FLAGSSET  = LIN_FLAGS_THRQ; /* SBSW_LIN_PTR_HW */
  ChannelRegisterBase->TXFIFOCON = LIN_TXFIFOCON_ENABLE; /* SBSW_LIN_PTR_HW */
}

/**********************************************************************************************************************
 *  Frame Processor Implementation
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  Lin_Fp_GlobalInit
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_Fp_GlobalInit( void )
{
  /* no global init demand for this driver */
}

/***********************************************************************************************************************
 *  Lin_Fp_ChannelInit
 **********************************************************************************************************************/
 /*!
 * \internal
 * - Set ASCLIN_CLC register
 * - deactivate clock source during configuration
 * - select LIN operation mode, configure frame parameters
 * - select master mode, enable hardware checksum logic
 * - configure baudrate
 * - configure bit timing and sampling
 * - configure break length
 * - set header timeout, sufficient to set it once. Setting requires CSR_CLKSEL = 0
 * - set used interrupt flag sources
 * - set pin configuration
 * - activate clock source
 * \endinternal
 */
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_Fp_ChannelInit( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx ) /* PRQA S 3206 */ /* MD_LIN_3206 */
{
  P2VAR(Lin_RegisterStruct, AUTOMATIC, LIN_VAR_REGS) ChannelRegisterBase = Lin_GetChannelBaseAddressOfChannelConfig( ChannelConfigIdx ); /* PRQA S 0303 */ /* MD_LIN_0303 */
  /* Set ASCLIN_CLC register */
  Appl_UnlockEndinit();

  osWritePeripheral32( LIN_PROTECTED_AREA_ENDINIT, (uint32)(&(ChannelRegisterBase->CLC)), 0x0008U ); /* PRQA S 0303,0306 */ /* MD_LIN_0303,MD_LIN_HW_0306 */ /* SBSW_LIN_PTR_HW */

  Appl_LockEndinit();

  /* deactivate clock source during configuration */
  ChannelRegisterBase->CSR &= (uint32)~(LIN_CSR_CLKSEL_MASK); /* SBSW_LIN_PTR_HW */

  /* select LIN operation mode, configure frame parameters */
  ChannelRegisterBase->FRAMECON = LIN_FRAMECON_DEFAULT; /* SBSW_LIN_PTR_HW */

  /* select master mode, enable hardware checksum logic */
  ChannelRegisterBase->LINCON = LIN_LINCON_DEFAULT; /* SBSW_LIN_PTR_HW */

  /* configure baudrate */
  ChannelRegisterBase->BRG = Lin_GetBRGOfChannelConfig( ChannelConfigIdx ); /* SBSW_LIN_PTR_HW */

  /* configure bit timing and sampling */
  ChannelRegisterBase->BITCON = LIN_BITCON_DEFAULT | Lin_GetBITCON_PRESCALEROfChannelConfig( ChannelConfigIdx ); /* SBSW_LIN_PTR_HW */

  /* configure break length */
  ChannelRegisterBase->LINBTIMER = LIN_LINBTIMER_DEFAULT; /* SBSW_LIN_PTR_HW */

  /* set header timeout, sufficient to set it once. Setting requires CSR_CLKSEL = 0 */
  ChannelRegisterBase->LINHTIMER = LIN_LINHTIMER_DEFAULT; /* SBSW_LIN_PTR_HW */

  /* set used interrupt flag sources */
  ChannelRegisterBase->FLAGSENABLE = LIN_FLAGSENABLE_DISABLE; /* SBSW_LIN_PTR_HW */

 /* set pin configuration */
  ChannelRegisterBase->IOCR = Lin_GetIOCR_ALTIOfChannelConfig( ChannelConfigIdx ); /* SBSW_LIN_PTR_HW */

  /* activate clock source */
  ChannelRegisterBase->CSR = (Lin_GetCSR_CLKSELOfChannelConfig( ChannelConfigIdx ) & LIN_CSR_CLKSEL_MASK); /* SBSW_LIN_PTR_HW */
}

/***********************************************************************************************************************
 *  Lin_Fp_Interrupt
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE_ISR) Lin_Fp_Interrupt( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx ) /* PRQA S 3206 */ /* MD_LIN_3206 */
{
  /* hardware needs no calculation time */
}

/***********************************************************************************************************************
 *  Lin_Fp_DequeueStatus
 **********************************************************************************************************************/
 /*!
 * \internal
 *   - Dequeue hardware status: read an clear hardware status flags
 *      - mapping hardware status flags to frame processor status
 *        - check if a error flag set
 *            - check if a header error flag is set
 *                - return frame processor status LIN_FP_HEADERERROR
 *            - check time out and received data bytes flags
 *                - return frame processor status LIN_FP_NO_RESPONSE
 *            - error in response or all other errors
 *                - return frame processor status LIN_FP_ERROR
 *        - check if transmission or reception was successful
 *            - return frame processor status LIN_FP_SUCCESSFUL
 *        - no hardware flags set, hardware queue was empty
 *            - return frame processor status LIN_FP_EMPTY
 * \endinternal
 */
LIN_LOCAL_INLINE FUNC(uint8, LIN_CODE) Lin_Fp_DequeueStatus( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx ) /* PRQA S 3206 */ /* MD_LIN_3206 */
{
  VAR(uint8,  AUTOMATIC) ret;
  VAR(uint32, AUTOMATIC) Flags;
  VAR(uint32, AUTOMATIC) RxFifoCon;
  P2VAR(Lin_RegisterStruct, AUTOMATIC, LIN_VAR_REGS) ChannelRegisterBase = Lin_GetChannelBaseAddressOfChannelConfig( ChannelConfigIdx ); /* PRQA S 0303 */ /* MD_LIN_0303 */

  /* Dequeue hardware status: read an clear hardware status flags */
  Flags     = ChannelRegisterBase->FLAGS;
  RxFifoCon = ChannelRegisterBase->RXFIFOCON;
  ChannelRegisterBase->FLAGSCLEAR = Flags & LIN_FLAGS_ALL; /* SBSW_LIN_PTR_HW */

  /* mapping hardware status flags to frame processor status */
  if ( ( Flags & LIN_FLAGS_ERROR) != 0u )
  {/* any error */
    if( ( Flags & LIN_FLAGS_TH ) == 0u )
    { /* header error */
      /* return frame processor status LIN_FP_HEADERERROR */
      ret = LIN_FP_STATUS_HEADERERROR;
    }
    else if ( ( (RxFifoCon & LIN_RXFIFOCON_FILL_MASK ) == (uint32)0x00010000U ) &&   /* only PID received */
              ( (Flags & (LIN_FLAGS_FE | LIN_FLAGS_LC | LIN_FLAGS_CE)) == 0u ) )      /* no error expect timeout */
    { /* no response byte received */
      /* return frame processor status LIN_FP_NO_RESPONSE */
      ret = LIN_FP_STATUS_NO_RESPONSE;
    }
    else /* other error */
    {
      /* return frame processor status LIN_FP_ERROR */
      ret = LIN_FP_STATUS_ERROR;
    }
  }
  else if( ((Flags & (LIN_FLAGS_TR | LIN_FLAGS_RR))!= 0u ) ||  /* RX or TX ok */
           (((ChannelRegisterBase->DATCON & LIN_DATCON_HO) != 0u) && ((Flags & LIN_FLAGS_TH) != 0u ) ) ) /* S2S ok */
  { /* RX, TX, wakeup ok */
    /* return frame processor status LIN_FP_SUCCESSFUL */
    ret = LIN_FP_STATUS_SUCCESSFUL;
  }
  else /* polling or flags handle previous */
  {
    /* return frame processor status LIN_FP_EMPTY */
    ret = LIN_FP_STATUS_EMPTY;
  }

  return ret;
}

/***********************************************************************************************************************
 *  Lin_Fp_StartTxFrame
 **********************************************************************************************************************/
 /*!
 * \internal
 * - Configure common part
 * - write all data bytes to transmit register which are automatically shifted to Tx FIFO
 * - start transmission
 * - start response transmission
 * \endinternal
 */
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_Fp_StartTxFrame( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx,
                                                   CONSTP2CONST(Lin_PduType, AUTOMATIC, LIN_APPL_VAR) PduInfoPtr )
{
  P2VAR(Lin_RegisterStruct, AUTOMATIC, LIN_VAR_REGS) ChannelRegisterBase = Lin_GetChannelBaseAddressOfChannelConfig( ChannelConfigIdx ); /* PRQA S 0303 */ /* MD_LIN_0303 */
  /* Configure common part */
  Lin_CommonFrameSetup( ChannelConfigIdx, PduInfoPtr ); /* SBSW_LIN_CONST_PTR_CONST */

  /* write all data bytes to transmit register which are automatically shifted to Tx FIFO */
  {
    VAR(uint8_least, AUTOMATIC) DataIndex;
    for (DataIndex = 0; DataIndex < (PduInfoPtr->Dl); DataIndex++)
    {
      ChannelRegisterBase->TXDATA = (uint8)PduInfoPtr->SduPtr[DataIndex]; /* SBSW_LIN_PTR_HW */
    }
  }

  /* start transmission */
  Lin_StartFrameTransmission( ChannelConfigIdx );

  /* start response transmission */
  ChannelRegisterBase->FLAGSSET = LIN_FLAGS_TRRQ; /* SBSW_LIN_PTR_HW */
}

/***********************************************************************************************************************
 *  Lin_Fp_StartRxFrame
 **********************************************************************************************************************/
 /*!
 * \internal
 * - Configure common part
 * - Configure RX buffer
 * - start transmission
 * \endinternal
 */
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_Fp_StartRxFrame( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx,
                                                   CONSTP2CONST(Lin_PduType, AUTOMATIC, LIN_APPL_VAR) PduInfoPtr )
{
  P2VAR(Lin_RegisterStruct, AUTOMATIC, LIN_VAR_REGS) ChannelRegisterBase = Lin_GetChannelBaseAddressOfChannelConfig( ChannelConfigIdx ); /* PRQA S 0303 */ /* MD_LIN_0303 */
  /* Configure common part */
  Lin_CommonFrameSetup( ChannelConfigIdx, PduInfoPtr ); /* SBSW_LIN_CONST_PTR_CONST */

  /* Configure RX buffer */
  ChannelRegisterBase->RXFIFOCON = LIN_RXFIFOCON_ENABLE; /* SBSW_LIN_PTR_HW */

  /* start transmission */
  Lin_StartFrameTransmission( ChannelConfigIdx );
}

/***********************************************************************************************************************
 *  Lin_Fp_StartS2sFrame
 **********************************************************************************************************************/
 /*!
 * \internal
 * - Configure common part
 * - overwrite for S2S Frames
 * - start transmission
 * \endinternal
 */
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_Fp_StartS2sFrame( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx,
                                                   CONSTP2CONST(Lin_PduType, AUTOMATIC, LIN_APPL_VAR) PduInfoPtr )
{
  P2VAR(Lin_RegisterStruct, AUTOMATIC, LIN_VAR_REGS) ChannelRegisterBase = Lin_GetChannelBaseAddressOfChannelConfig( ChannelConfigIdx ); /* PRQA S 0303 */ /* MD_LIN_0303 */
  /* Configure common part */
  Lin_CommonFrameSetup( ChannelConfigIdx, PduInfoPtr ); /* SBSW_LIN_CONST_PTR_CONST */

  /* overwrite for S2S Frames */
  ChannelRegisterBase->DATCON = LIN_DATCON_MAXRESP | LIN_DATCON_HO; /* SBSW_LIN_PTR_HW */

  /* start transmission */
  Lin_StartFrameTransmission( ChannelConfigIdx );
}

/***********************************************************************************************************************
 *  Lin_Fp_StartWakeupPulse
 **********************************************************************************************************************/
 /*!
 * \internal
 * - set wakeup byte to transmit
 * - trigger wakeup frame transmission
 * \endinternal
 */
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_Fp_StartWakeupPulse( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx ) /* PRQA S 3206 */ /* MD_LIN_3206 */
{
  P2VAR(Lin_RegisterStruct, AUTOMATIC, LIN_VAR_REGS) ChannelRegisterBase = Lin_GetChannelBaseAddressOfChannelConfig( ChannelConfigIdx ); /* PRQA S 0303 */ /* MD_LIN_0303 */
  /* set wakeup byte to transmit */
  ChannelRegisterBase->TXFIFOCON = LIN_TXFIFOCON_CLEAR_STOP; /* SBSW_LIN_PTR_HW */
  ChannelRegisterBase->TXDATA    = LIN_WAKEUP_PATTERN; /* SBSW_LIN_PTR_HW */
  ChannelRegisterBase->TXFIFOCON = LIN_TXFIFOCON_ENABLE; /* SBSW_LIN_PTR_HW */

  /* trigger wakeup frame transmission */
  ChannelRegisterBase->FLAGSSET  = LIN_FLAGS_TWRQ; /* SBSW_LIN_PTR_HW */
}

/***********************************************************************************************************************
 *  Lin_Fp_SaveRxData
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_Fp_SaveRxData( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx )
{
  P2VAR(Lin_RegisterStruct, AUTOMATIC, LIN_VAR_REGS) ChannelRegisterBase = Lin_GetChannelBaseAddressOfChannelConfig( ChannelConfigIdx ); /* PRQA S 0303 */ /* MD_LIN_0303 */
  /* dummy read of first byte */
  VAR(volatile uint8, AUTOMATIC) dummy = (uint8)ChannelRegisterBase->RXDATA; /*PRQA S 3205*/ /* MD_LIN_HW_3205 */

  /* store RX Data */
  Lin_GetDataBufferOfChannelData( ChannelConfigIdx )[0] = (uint8)ChannelRegisterBase->RXDATA; /* SBSW_LIN_BUFFER_WRITE */
  Lin_GetDataBufferOfChannelData( ChannelConfigIdx )[1] = (uint8)ChannelRegisterBase->RXDATA; /* SBSW_LIN_BUFFER_WRITE */
  Lin_GetDataBufferOfChannelData( ChannelConfigIdx )[2] = (uint8)ChannelRegisterBase->RXDATA; /* SBSW_LIN_BUFFER_WRITE */
  Lin_GetDataBufferOfChannelData( ChannelConfigIdx )[3] = (uint8)ChannelRegisterBase->RXDATA; /* SBSW_LIN_BUFFER_WRITE */
  Lin_GetDataBufferOfChannelData( ChannelConfigIdx )[4] = (uint8)ChannelRegisterBase->RXDATA; /* SBSW_LIN_BUFFER_WRITE */
  Lin_GetDataBufferOfChannelData( ChannelConfigIdx )[5] = (uint8)ChannelRegisterBase->RXDATA; /* SBSW_LIN_BUFFER_WRITE */
  Lin_GetDataBufferOfChannelData( ChannelConfigIdx )[6] = (uint8)ChannelRegisterBase->RXDATA; /* SBSW_LIN_BUFFER_WRITE */
  Lin_GetDataBufferOfChannelData( ChannelConfigIdx )[7] = (uint8)ChannelRegisterBase->RXDATA; /* SBSW_LIN_BUFFER_WRITE */
}

/***********************************************************************************************************************
 *  Lin_Fp_DisableWakupDetection
 **********************************************************************************************************************/
 /*!
 * \internal
 * - disable all interrupts
 * \endinternal
 */
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_Fp_DisableWakupDetection ( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx ) /* PRQA S 3206 */ /* MD_LIN_3206 */
{
  P2VAR(Lin_RegisterStruct, AUTOMATIC, LIN_VAR_REGS) ChannelRegisterBase = Lin_GetChannelBaseAddressOfChannelConfig( ChannelConfigIdx ); /* PRQA S 0303 */ /* MD_LIN_0303 */
  /* disable all interupts */
  ChannelRegisterBase->FLAGSENABLE = LIN_FLAGSENABLE_DISABLE; /* SBSW_LIN_PTR_HW */
}

/***********************************************************************************************************************
 *  Lin_Fp_EnableWakupDetection
 **********************************************************************************************************************/
 /*!
 * \internal
 * - clear all flags
 * - enable interrupt of detection of a falling edge (ext. wakeup)
 * \endinternal
 */
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_Fp_EnableWakupDetection ( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx ) /* PRQA S 3206 */ /* MD_LIN_3206 */
{
  P2VAR(Lin_RegisterStruct, AUTOMATIC, LIN_VAR_REGS) ChannelRegisterBase = Lin_GetChannelBaseAddressOfChannelConfig( ChannelConfigIdx ); /* PRQA S 0303 */ /* MD_LIN_0303 */
  /* clear all flags */
  ChannelRegisterBase->FLAGSCLEAR  = ChannelRegisterBase->FLAGS; /* SBSW_LIN_PTR_HW */

  /* enable interrupt of detection of a falling edge (ext. wakeup) */
  ChannelRegisterBase->FLAGSENABLE = LIN_FLAGS_FED; /* SBSW_LIN_PTR_HW */
}

/***********************************************************************************************************************
 *  Lin_Fp_HasNoResponseBytes
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(boolean, LIN_CODE) Lin_Fp_HasNoResponseBytes( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx ) /* PRQA S 3206 */ /* MD_LIN_3206 */
{
  return FALSE;
}

/***********************************************************************************************************************
 *  Lin_IfRxByteNotStarted
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(boolean, LIN_CODE) Lin_Hw_IfRxByteNotStarted( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx ) /* PRQA S 3206 */ /* MD_LIN_3206 */ /* COV_LIN_HW_TIMEOUT */
{
  return FALSE;
}

/***********************************************************************************************************************
 *  Lin_Fp_GetReceiveBufferPointer
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(uint8*, LIN_CODE) Lin_Fp_GetReceiveBufferPointer( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx )
{
  return Lin_GetDataBufferOfChannelData( ChannelConfigIdx );
}


#define LIN_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* module specific MISRA deviations:

  MD_LIN_HW_3205:
    Reason: The Hardware requires a reed which is otherwise not necessary.
    Risk: Operation appear redundent but is mandtory for correct operation.
    Prevention: Perform testsuite to ensure valid frame reception.

  MD_LIN_HW_0306:
    Reason: If the osWritePeripheral32 function is not declared, then this function is redirected as Macro for direct 
            pointer access.
    Risk: Cast a pointer to an integer type or vice versa may be non-portable.
    Prevention: Perform testsuite with both configurations to ensure valid operation.
*/

/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_LIN_PTR_HW
  \DESCRIPTION The function accesses a hardware register using a pointer access.
  \COUNTERMEASURE \T The code inspection and tests on hardware ensure that the memory location
                     referenced contains the registers with the same structure as specified.
                  \S Verify that the values generated match the address of register of the used hardware. [SMI-962]

SBSW_JUSTIFICATION_END */

#endif /* LIN_FP_INC */

/**********************************************************************************************************************
 *  END OF FILE: Lin_Fp.inc
 *********************************************************************************************************************/
