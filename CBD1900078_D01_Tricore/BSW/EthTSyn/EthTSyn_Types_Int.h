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
 *  -------------------------------------------------------------------------------------------------------------------
 *         \file  EthTSyn_Types_Int.h
 *        \brief  EthTSyn internal Types header
 *
 *      \details  Contains all internal type definitions used by different sub-modules of the EthTSyn
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

#if !defined(ETHTSYN_TYPES_INT_H)
# define ETHTSYN_TYPES_INT_H
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "EthTSyn_GeneratedComplexTypes.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! Internally used Port role enum */
typedef enum EthTSyn_InternalPortRoleEnum
{
  ETHTSYN_PORT_ROlE_INVALID,
  ETHTSYN_PORT_ROLE_SLAVE,
  ETHTSYN_PORT_ROLE_MASTER,
  ETHTSYN_PORT_ROLE_PASSIVE,
  ETHTSYN_PORT_ROLE_DISABLED
} EthTSyn_InternalPortRoleEnumType;

/*! Internally used port identification struct definition*/
typedef struct EthTSyn_PortIdentificationStruct
{
  EthTSyn_InternalPortRoleEnumType PortRole;        /*<! Master or Slave Port */
  EthTSyn_MasterPortIdxOfPortType  MasterPortIndex; /*<! Index of the Master Port (valid for PortRole == MASTER_PORT) */
  EthTSyn_SlavePortIdxOfPortType   SlavePortIndex;  /*<! Index of the Slave Port (valid for PortRole == SLAVE_PORT) */
} EthTSyn_PortIdentificationStructType;

typedef enum EthTSyn_InternalMsgTypeEnum
{
  ETHTSYN_INT_MSG_TYPE_INVALID,
  ETHTSYN_INT_MSG_TYPE_SYNC,
  ETHTSYN_INT_MSG_TYPE_FOLLOW_UP,
  ETHTSYN_INT_MSG_TYPE_ANNOUNCE,
  ETHTSYN_INT_MSG_TYPE_PDELAY_REQ,
  ETHTSYN_INT_MSG_TYPE_PDELAY_RESP,
  ETHTSYN_INT_MSG_TYPE_PDELAY_RESP_FUP
} EthTSyn_InternalMsgEnumType;

/*! Internally used tuple of message type and port index */
typedef struct EthTSyn_MsgTypePortIdxTupleStruct
{
  boolean                      IsValid; /*<! Marking if the tuple is valid. When set to TRUE both PortIdx and MsgType
                                             are valid. In addition it is already ensured that the port is capable of
                                             transmitting/receiving the specified msg. */
  EthTSyn_SizeOfPortType       PortIdx; /*<! Index of the Port the message was transmitted/received */
  EthTSyn_InternalMsgEnumType  MsgType; /*<! Type of the transmitted/received message */
} EthTSyn_MsgTypePortIdxTupleType;

/*! Internally used information to set up common message header */
typedef struct
{
  uint16                  MsgLength;
  uint16                  SequenceId;
  EthTSyn_SizeOfPortType  PortIdx;
  uint8                   MsgType;
  uint8                   ComHdrControl;
  sint8                   LogMsgInterval;
} EthTSyn_ComMsgHdrInfoStructType;

/*! Internally used Ethernet tx buffer struct definition */
typedef struct
{
  ETHTSYN_P2VAR(uint8) BufferPtr; /*<! Pointer to the payload portion of the Ethernet Tx buffer.
                                       Valid when BufferIdx is valid. */
  uint16               Length;    /*<! The requested Ethernet Tx buffer length. */
  EthTSyn_FrameIdType  FrameId;   /*<! The FrameId. */
  uint8                BufferIdx; /*<! Index of the Ethernet Tx buffer */
} EthTSyn_EthTxBufferStructType;

typedef uint8 EthTSyn_EnableTimestampFlagsType;
/* Flags */
# define ETHTSYN_ENABLE_TS_HW_TS_MASK          (0x01u)
# define ETHTSYN_ENABLE_TS_SWT_TS_MASK         (0x02u)
# define ETHTSYN_ENABLE_TS_HW_XOR_SWT_TS_MASK  (0x04u)
/* Values */
# define ETHTSYN_ENABLE_TS_NONE                (0x00u)
# define ETHTSYN_ENABLE_TS_HW_TS               (0x01u)
# define ETHTSYN_ENABLE_TS_SWT_TS              (0x02u)
# define ETHTSYN_ENABLE_TS_HW_AND_SWT_TS       (0x03u)
# define ETHTSYN_ENABLE_TS_HW_XOR_SWT_TS       (0x07u)

#endif /* ETHTSYN_TYPES_INT_H */
/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Types_Int.h
 *********************************************************************************************************************/
