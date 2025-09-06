/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  CanTSyn_Types.h
 *        \brief  Vector AUTOSAR CanTSyn Types header file
 *
 *      \details  This header file contains the type definitions of the Vector AUTOSAR module CanTSyn.

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

#if !defined (CANTSYN_TYPES_H)
# define CANTSYN_TYPES_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "Std_Types.h"
# include "ComStack_Types.h"
# include "StbM_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# define CANTSYN_NO_SLAVE_IDX                    (255u)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef uint8 CanTSyn_CanMsgType[8];

typedef uint8 CanTSyn_DataIDListType[16];

/* CANTSYN State-Machine State Definitions */
typedef uint8 CanTSyn_StateMachineStateType;
# define CANTSYN_STATE_RECEIVE_WAITING_FOR_SYNC                    (0u)
# define CANTSYN_STATE_RECEIVE_WAITING_FOR_FOLLOW_UP               (1u)

# define CANTSYN_STATE_SEND_WAITING_FOR_SYNC_SEND                  (0u)
# define CANTSYN_STATE_SEND_WAITING_FOR_SYNC_TX_CONFIRMATION       (1u)
# define CANTSYN_STATE_SEND_WAITING_FOR_FOLLOW_UP_SEND             (2u)
# define CANTSYN_STATE_SEND_WAITING_FOR_FOLLOW_UP_TX_CONFIRMATION  (3u)

# define CANTSYN_STATE_SEND_WAITING_FOR_SEND                       (4u)
# define CANTSYN_STATE_SEND_WAITING_FOR_TX_CONFIRMATION            (5u)

/* CANTSYN Transmission State Definitions */
typedef uint8 CanTSyn_TransmissionModeType;
# define CANTSYN_TX_OFF                                            (0u)
# define CANTSYN_TX_ON                                             (1u)

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#endif  /* CANTSYN_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: CanTSyn_Types.h
 *********************************************************************************************************************/
