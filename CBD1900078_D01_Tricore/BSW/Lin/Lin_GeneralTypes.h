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
/**        \file  Lin_GeneralTypes.h
 *        \brief  AUTOSAR LIN Driver
 *
 *      \details  AUTOSAR LIN Driver for all target systems
 *
 *********************************************************************************************************************/

#if !defined (LIN_GENERALTYPES_H)
#define LIN_GENERALTYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

/*! LIN operation states for a LIN channel or frame, as returned by the API service Lin_GetStatus(). */
typedef enum Lin_StatusTypeTag
{
  /*! LIN frame operation return value.
      Development or production error occurred. */
  LIN_NOT_OK,

  /*! LIN frame operation return value.
      Successful transmission.    */
  LIN_TX_OK,

  /*! LIN frame operation return value.
      Ongoing transmission (Header or Response). */
  LIN_TX_BUSY,

  /*! LIN frame operation return value.
      Erroneous header transmission such as:
       - Mismatch between sent and read back data
       - Identifier parity error or
       - Physical bus error */
  LIN_TX_HEADER_ERROR,

  /*! LIN frame operation return value.
      Erroneous response transmission such as:
       - Mismatch between sent and read back data
       - Physical bus error */
  LIN_TX_ERROR,

  /*! LIN frame operation return value.
      Ongoing reception: at least one response byte has been received, but the checksum byte has not been received. */
  LIN_RX_BUSY,

  /*! LIN frame operation return value.
      Reception of correct response. */
  LIN_RX_OK,

  /*! LIN frame operation return value.
      Erroneous response reception such as:
       - Framing error
       - Overrun error
       - Checksum error or
       - Short response */
  LIN_RX_ERROR,

  /*! LIN frame operation return value.
      No response byte has been received so far. */
  LIN_RX_NO_RESPONSE,

  /*! LIN channel state return value.
      Normal operation; the related LIN channel is ready to transmit next header. No data from previous frame available
      (e.g. after initialization). */
  LIN_OPERATIONAL,

  /*! LIN channel state return value.
      Sleep state operation; in this state wake-up detection from slave nodes is enabled. */
  LIN_CH_SLEEP
}Lin_StatusType;


/*! Pointer to pointer to a shadow buffer or memory mapped LIN Hardware receive buffer where the current SDU is
    stored. */
typedef P2VAR(uint8, TYPEDEF, LIN_APPL_VAR) Lin_u8PtrType;


/*! Represents all valid protected identifier used by Lin_SendFrame(). */
typedef uint8 Lin_FramePidType;


/*! This type is used to specify the Checksum model to be used for the LIN Frame. */
typedef enum Lin_FrameCsModelTypeTag
{
  LIN_ENHANCED_CS, /*<! Enhanced checksum model */
  LIN_CLASSIC_CS   /*<! Classic checksum model */
}Lin_FrameCsModelType;


/*! This type is used to specify whether the frame processor is required to transmit the
    response part of the LIN frame. */
typedef enum Lin_FrameResponseTypeTag
{
  LIN_MASTER_RESPONSE, /*<! Response is generated from this (master) node */
  LIN_SLAVE_RESPONSE,  /*<! Response is generated from a remote slave node */
  LIN_SLAVE_TO_SLAVE   /*<! Response is generated from one slave to another slave */
}Lin_FrameResponseType;


/*! This type is used to specify the number of SDU data bytes to copy.
    Range: 1 - 8, data length of a LIN frame. */
typedef uint8 Lin_FrameDlType;


/*! This Type is used to provide PID, checksum model, data length and SDU pointer of a LIN frame
    from the LIN Interface to the LIN driver.  */
typedef struct Lin_PduTypeTag
{
  VAR(Lin_FramePidType, TYPEDEF)      Pid;    /*<! Valid protected identifier */
  VAR(Lin_FrameCsModelType, TYPEDEF)  Cs;     /*<! Specified Checksum model */
  VAR(Lin_FrameResponseType, TYPEDEF) Drc;    /*<! Type of response part */
  VAR(Lin_FrameDlType, TYPEDEF)       Dl;     /*<! Number of SDU data bytes to copy */
  P2VAR(uint8, TYPEDEF, LIN_APPL_VAR) SduPtr; /*<! Pointer to SDU data bytes */
}Lin_PduType;


/* Include General Types of LinIf */
#include "LinIf_GeneralTypes.h"


#endif /* LIN_GENERALTYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Lin_GeneralTypes.h
 *********************************************************************************************************************/

