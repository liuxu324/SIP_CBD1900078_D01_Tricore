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
/**        \file EthTSyn_Crc_Int.c
*        \brief  EthTSyn Crc source file - Internal Functions
*
*      \details  EthTSyn Crc source file containing the EthTSyn Crc implementation of the EthTSyn module.
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

#define ETHTSYN_CRC_INT_SOURCE

/**********************************************************************************************************************
*  INCLUDES
*********************************************************************************************************************/
#include "EthTSyn_Crc_Int.h" /* PRQA S 0857 */ /* MD_MSR_1.1_857 */

#if (ETHTSYN_CRC_SUPPORT == STD_ON)
# include "EthTSyn_Int.h" /* PRQA S 3219, 0883 */ /* MD_EthTSyn_3219, MD_EthTSyn_0883 */
# include "Crc.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of EthTSyn header file */
# if (  (ETHTSYN_SW_MAJOR_VERSION != (7u)) \
     || (ETHTSYN_SW_MINOR_VERSION != (0u)) \
     || (ETHTSYN_SW_PATCH_VERSION != (0u)) )
#  error "Vendor specific version numbers of EthTSyn_Crc_Int.c and EthTSyn.h are inconsistent"
# endif

/* Check the version of the configuration header file */
# if (  (ETHTSYN_CFG_MAJOR_VERSION != (7u)) \
     || (ETHTSYN_CFG_MINOR_VERSION != (0u)) )
#  error "Version numbers of EthTSyn_Crc_Int.c and EthTSyn_Cfg.h are inconsistent!"
# endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
# define ETHTSYN_CRC_FLAGS_MSG_LENGTH_MASK          (0x01u)

# define ETHTSYN_CRC_FLAGS_DOMAIN_NUMBER_MASK       (0x02u)

# define ETHTSYN_CRC_FLAGS_CORRECTION_FIELD_MASK    (0x04u)

# define ETHTSYN_CRC_FLAGS_SRC_PORT_IDENTITY_MASK   (0x08u)

# define ETHTSYN_CRC_FLAGS_SEQUENCE_ID_MASK         (0x10u)

# define ETHTSYN_CRC_FLAGS_PRECISE_ORIGIN_TS_MASK   (0x20u)

# define ETHTSYN_CRC_STATUS_CRC_DATA_SIZE           (2u)
# define ETHTSYN_CRC_USER_DATA_CRC_DATA_SIZE        (5u)
# define ETHTSYN_CRC_OFS_CRC_DATA_SIZE              (17u)

 /* CRC_TIME_0 Max Size: TimeFlages (1) + DomainNumber (1) + SrcPortIdentity (10) + PreciseOriginTimestamp (10) +
 *                      DataId (1) = 22 */
# define ETHTSYN_CRC_TIME_0_MAX_DATA_SIZE    (23u)
 /* CRC_TIME_1 Max Size: TimeFlages (1) + MsgLength (2) + CorrectionField (8) + SequenceId (2) + DataId (1) = 13 */
# define ETHTSYN_CRC_TIME_1_MAX_DATA_SIZE    (14u)

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
# if !defined (ETHTSYN_LOCAL) /* COV_MSR_COMPATIBILITY */
#  define ETHTSYN_LOCAL static
# endif

# if !defined (ETHTSYN_LOCAL_INLINE) /* COV_MSR_COMPATIBILITY */
#  define ETHTSYN_LOCAL_INLINE LOCAL_INLINE
# endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define ETHTSYN_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  EthTSyn_Crc_ValidateTimeCrc
 *********************************************************************************************************************/
 /*! \brief      Validates the Crc (CRC_TIME_0 + CRC_TIME_1) for a TimeSecured FollowUp.
  *  \details    Computes the expected CrcTime0 and CrcTime1 of the provided TimeSecured Sub-Tlv and validates the Crc
  *              values carried in the Sub-Tlv itself.
 *   \param[in]  DataId             The DataId for the FollowUp
 *   \param[in]  ComMsgPtr          Pointer to the common message header
 *   \param[in]  TimeSecuredTlvPtr  Pointer to the Time Secured Sub-Tlv of the FollowUp
 *   \return     TRUE - Crc is valid
 *   \return     False - Crc is invalid
 *   \pre        -
 *   \context    TASK|ISR2
 *   \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Crc_ValidateTimeCrc(
                  uint8                            DataId,
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType)        ComMsgPtr,
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvTimeSecuredType) TimeSecuredTlvPtr);

/**********************************************************************************************************************
 *  EthTSyn_Crc_ValidateStatusCrc
 *********************************************************************************************************************/
/*! \brief      Validates the Crc (CRC_Status) for a Status Secured FollowUp message.
 *  \details    Computes the expected Crc of the provided StatusSecured Sub-Tlv and validates the Crc value carried in
 *              the Sub-Tlv itself.
 *  \param[in]  DataId               The DataId for the FollowUp
 *  \param[in]  StatusSecuredTlvPtr  Pointer to the Statues Secured Sub-Tlv of the FollowUp message
 *  \pre        -
 *  \return     TRUE - Crc is valid
 *  \return     False - Crc is invalid
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Crc_ValidateStatusCrc(
                  uint8                        DataId,
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvStatusType)  StatusSecuredTlvPtr);

/**********************************************************************************************************************
 *  EthTSyn_Crc_ValidateUserDataCrc
 *********************************************************************************************************************/
/*! \brief      Validates the Crc (CRC_UserData) for a UserData Secured FollowUp message.
 *  \details    Computes the expected Crc of the provided UserDataSecured Sub-Tlv and validates the Crc value carried in
 *              the Sub-Tlv itself.
 *  \param[in]  DataId                 The DataId for the FollowUp
 *  \param[in]  UserDataSecuredTlvPtr  Pointer to the UserData Secured Sub-Tlv of the FollowUp message
 *  \pre        -
 *  \return     TRUE - Crc is valid
 *  \return     False - Crc is invalid
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Crc_ValidateUserDataCrc(
                  uint8                          DataId,
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvUserDataType)  UserDataSecuredTlvPtr);

/**********************************************************************************************************************
 *  EthTSyn_Crc_ValidateOfsCrc
 *********************************************************************************************************************/
/*! \brief      Validates the Crc (CRC_OFS) for a Ofs Secured FollowUp message.
 *  \details    Computes the expected Crc of the provided OfsSecured Sub-Tlv and validates the Crc value carried in
 *              the Sub-Tlv itself.
 *  \param[in]  DataId            The DataId for the FollowUp
 *  \param[in]  OfsSecuredTlvPtr  Pointer to the Ofs Secured Sub-Tlv of the FollowUp message
 *  \return     TRUE - Crc is valid
 *  \return     False - Crc is invalid
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Crc_ValidateOfsCrc(
                  uint8                     DataId,
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvOfsType)  OfsSecuredTlvPtr);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Crc_ValidateTimeCrc
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Crc_ValidateTimeCrc(
                  uint8                            DataId,
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType)        ComMsgPtr,
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvTimeSecuredType) TimeSecuredTlvPtr)
{
  /* #10 Compute and validate the Crc Time0 and Time1 of the Time secured sub Tlv. */
  /* PRQA S 3415 5 */ /* MD_EthTSyn_3415_ReadOnly */
  return (boolean)(
    (TimeSecuredTlvPtr->CrcTime0 == EthTSyn_Crc_ComputeTime0Crc(DataId, TimeSecuredTlvPtr->CrcTimeFlags, ComMsgPtr))   /* SBSW_ETHTSYN_PASSING_API_POINTER */
    &&
    (TimeSecuredTlvPtr->CrcTime1 == EthTSyn_Crc_ComputeTime1Crc(DataId, TimeSecuredTlvPtr->CrcTimeFlags, ComMsgPtr))   /* SBSW_ETHTSYN_PASSING_API_POINTER */
    );
} /* EthTSyn_Crc_ValidateTimeCrc() */

/**********************************************************************************************************************
 *  EthTSyn_Crc_ValidateStatusCrc
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Crc_ValidateStatusCrc(
                  uint8                       DataId,
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvStatusType) StatusSecuredTlvPtr)
{
  /* #10 Compute and validate the Crc of the status secured sub Tlv. */
  return (boolean)(StatusSecuredTlvPtr->CrcStatus == EthTSyn_Crc_ComputeStatusCrc(DataId, StatusSecuredTlvPtr));       /* SBSW_ETHTSYN_PASSING_API_POINTER */
} /* EthTSyn_Crc_ValidateStatusCrc() */

/**********************************************************************************************************************
 *  EthTSyn_Crc_ValidateUserDataCrc
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Crc_ValidateUserDataCrc(
                  uint8                         DataId,
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvUserDataType) UserDataSecuredTlvPtr)
{
  /* #10 Compute and validate the Crc of the user data secured sub Tlv. */
  return (boolean)
    (UserDataSecuredTlvPtr->CrcUserData == EthTSyn_Crc_ComputeUserDataCrc(DataId, UserDataSecuredTlvPtr));             /* SBSW_ETHTSYN_PASSING_API_POINTER */
} /* EthTSyn_Crc_ValidateUserDataCrc() */

/**********************************************************************************************************************
 *  EthTSyn_Crc_ValidateOfsCrc
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTSYN_LOCAL_INLINE FUNC(boolean, ETHTSYN_CODE) EthTSyn_Crc_ValidateOfsCrc(
                  uint8                    DataId,
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvOfsType) OfsSecuredTlvPtr)
{
  /* #10 Compute and validate the Crc of the offset time domain (ofs) secured sub Tlv. */
  return (boolean)(OfsSecuredTlvPtr->CrcOfs == EthTSyn_Crc_ComputeOfsCrc(DataId, OfsSecuredTlvPtr));                   /* SBSW_ETHTSYN_PASSING_API_POINTER */
} /* EthTSyn_Crc_ValidateOfsCrc() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Crc_ComputeTime0Crc
 *********************************************************************************************************************/
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
FUNC(uint8, ETHTSYN_CODE) EthTSyn_Crc_ComputeTime0Crc(
                  uint8                     DataId,
                  uint8                     Flags,
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) ComMsgPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 crcData[ETHTSYN_CRC_TIME_0_MAX_DATA_SIZE];
  uint32 crcDataLength = 0;
  ETHTSYN_CONSTP2CONST(EthTSyn_FollowUpMsgType) followUpMsgPtr =
    (ETHTSYN_P2CONST(EthTSyn_FollowUpMsgType))&((ETHTSYN_P2CONST(uint8))ComMsgPtr)[ETHTSYN_HDR_COM_LENGTH]; /* PRQA S 0310 */ /* MD_EthTSyn_0310_SubType */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Add the Value of Flags to Crc data. */
  crcData[crcDataLength] = Flags;                                                                                      /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcDataLength += 1u;

  /* #20 Add Domain Number to Crc data if applicable. */
  if ((Flags & ETHTSYN_CRC_FLAGS_DOMAIN_NUMBER_MASK) != 0u)
  {
    crcData[crcDataLength] = ComMsgPtr->DomainNumber;                                                                  /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcDataLength += 1u;
  }


  /* #30 Add Source Port Identity to Crc data if applicable. */
  if ((Flags & ETHTSYN_CRC_FLAGS_SRC_PORT_IDENTITY_MASK) != 0u)
  {
    const uint16 srcPortNumber = (uint16)EthTSyn_Ntohs(ComMsgPtr->SourcePortNumber);

    crcData[crcDataLength + 0u] = ComMsgPtr->SourceClockIdentity[0u];                                                  /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcData[crcDataLength + 1u] = ComMsgPtr->SourceClockIdentity[1u];                                                  /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcData[crcDataLength + 2u] = ComMsgPtr->SourceClockIdentity[2u];                                                  /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcData[crcDataLength + 3u] = ComMsgPtr->SourceClockIdentity[3u];                                                  /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcData[crcDataLength + 4u] = ComMsgPtr->SourceClockIdentity[4u];                                                  /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcData[crcDataLength + 5u] = ComMsgPtr->SourceClockIdentity[5u];                                                  /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcData[crcDataLength + 6u] = ComMsgPtr->SourceClockIdentity[6u];                                                  /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcData[crcDataLength + 7u] = ComMsgPtr->SourceClockIdentity[7u];                                                  /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcDataLength += 8u;

    ETHTSYN_PUT_UINT16(crcData, crcDataLength, srcPortNumber);
    crcDataLength += 2u;
  }

  /* #40 Add Precise Origin Timestamp to Crc data if applicable. */
  if ((Flags & ETHTSYN_CRC_FLAGS_PRECISE_ORIGIN_TS_MASK) != 0u)
  {
    crcData[crcDataLength + 0u] = followUpMsgPtr->PreciseOriginTimestampSeconds[0u];                                   /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcData[crcDataLength + 1u] = followUpMsgPtr->PreciseOriginTimestampSeconds[1u];                                   /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcData[crcDataLength + 2u] = followUpMsgPtr->PreciseOriginTimestampSeconds[2u];                                   /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcData[crcDataLength + 3u] = followUpMsgPtr->PreciseOriginTimestampSeconds[3u];                                   /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcData[crcDataLength + 4u] = followUpMsgPtr->PreciseOriginTimestampSeconds[4u];                                   /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcData[crcDataLength + 5u] = followUpMsgPtr->PreciseOriginTimestampSeconds[5u];                                   /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcDataLength += 6u;

    crcData[crcDataLength + 0u] = followUpMsgPtr->PreciseOriginTimestampNanoSeconds[0u];                               /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcData[crcDataLength + 1u] = followUpMsgPtr->PreciseOriginTimestampNanoSeconds[1u];                               /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcData[crcDataLength + 2u] = followUpMsgPtr->PreciseOriginTimestampNanoSeconds[2u];                               /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcData[crcDataLength + 3u] = followUpMsgPtr->PreciseOriginTimestampNanoSeconds[3u];                               /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcDataLength += 4u;
  }

  /* #50 Add DataId to Crc data. */
  crcData[crcDataLength] = DataId;                                                                                     /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcDataLength += 1u;

  /* #60 Calculate and return the Crc value. */
  return Crc_CalculateCRC8H2F(crcData, crcDataLength, 0u, TRUE);                                                       /* SBSW_ETHTSYN_VARIABLE_ARRAY_AS_POINTER */
} /* EthTSyn_Crc_ComputeTime0Crc() */

/**********************************************************************************************************************
 *  EthTSyn_Crc_ComputeTime1Crc
 *********************************************************************************************************************/
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
FUNC(uint8, ETHTSYN_CODE) EthTSyn_Crc_ComputeTime1Crc(
                  uint8                     DataId,
                  uint8                     Flags,
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType) ComMsgPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 crcData[ETHTSYN_CRC_TIME_1_MAX_DATA_SIZE];
  uint32 crcDataLength = 0;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Add the Value of Flags to Crc data. */
  crcData[crcDataLength] = Flags;                                                                                      /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcDataLength += 1u;

  /* #20 Add Message Length to Crc data if applicable. */
  if ((Flags & ETHTSYN_CRC_FLAGS_MSG_LENGTH_MASK) != 0u)
  {
    const uint16 msgLength = (uint16)EthTSyn_Ntohs(ComMsgPtr->MessageLength);

    ETHTSYN_PUT_UINT16(crcData, crcDataLength, msgLength);
    crcDataLength += 2u;
  }

  /* #30 Add Correction field to Crc data if applicable. */
  if ((Flags & ETHTSYN_CRC_FLAGS_CORRECTION_FIELD_MASK) != 0u)
  {
    crcData[crcDataLength + 0u] = ComMsgPtr->CorrectionField[0u];                                                      /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcData[crcDataLength + 1u] = ComMsgPtr->CorrectionField[1u];                                                      /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcData[crcDataLength + 2u] = ComMsgPtr->CorrectionField[2u];                                                      /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcData[crcDataLength + 3u] = ComMsgPtr->CorrectionField[3u];                                                      /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcData[crcDataLength + 4u] = ComMsgPtr->CorrectionField[4u];                                                      /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcData[crcDataLength + 5u] = ComMsgPtr->CorrectionField[5u];                                                      /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcData[crcDataLength + 6u] = ComMsgPtr->CorrectionField[6u];                                                      /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcData[crcDataLength + 7u] = ComMsgPtr->CorrectionField[7u];                                                      /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
    crcDataLength += 8u;
  }

  /* #40 Add Sequence Id to Crc data if applicable. */
  if ((Flags & ETHTSYN_CRC_FLAGS_SEQUENCE_ID_MASK) != 0u)
  {
    const uint16 sequenceId = (uint16)EthTSyn_Ntohs(ComMsgPtr->SequenceId);

    ETHTSYN_PUT_UINT16(crcData, crcDataLength, sequenceId);
    crcDataLength += 2u;
  }

  /* #50 Add DataId to Crc data. */
  crcData[crcDataLength] = DataId;                                                                                     /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcDataLength += 1u;

  /* #60 Calculate and return the Crc value. */
  return Crc_CalculateCRC8H2F(crcData, crcDataLength, 0, TRUE);                                                        /* SBSW_ETHTSYN_VARIABLE_ARRAY_AS_POINTER */
} /* EthTSyn_Crc_ComputeTime1Crc() */

/**********************************************************************************************************************
 *  EthTSyn_Crc_ComputeStatusCrc
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(uint8, ETHTSYN_CODE) EthTSyn_Crc_ComputeStatusCrc(
                  uint8                       DataId,
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvStatusType) StatusSecuredTlvPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 crcData[ETHTSYN_CRC_STATUS_CRC_DATA_SIZE];
  uint8 crcDataLength = 0;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Add Status to Crc data. */
  crcData[crcDataLength] = StatusSecuredTlvPtr->Status;                                                                /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcDataLength += 1u;

  /* #20 Add DataId to Crc data. */
  crcData[crcDataLength] = DataId;                                                                                     /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcDataLength += 1u;

  /* #30 Calculate and return the Crc value. */
  return Crc_CalculateCRC8H2F(crcData, crcDataLength, 0, TRUE);                                                        /* SBSW_ETHTSYN_VARIABLE_ARRAY_AS_POINTER */
} /* EthTSyn_Crc_ComputeStatusCrc() */

/**********************************************************************************************************************
 *  EthTSyn_Crc_ComputeUserDataCrc
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(uint8, ETHTSYN_CODE) EthTSyn_Crc_ComputeUserDataCrc(
                  uint8                         DataId,
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvUserDataType) UserDataSecuredTlvPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 crcData[ETHTSYN_CRC_USER_DATA_CRC_DATA_SIZE];
  uint8 crcDataLength = 0;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Add UserData Length to Crc data. */
  crcData[crcDataLength] = UserDataSecuredTlvPtr->UserDataLength;                                                      /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcDataLength += 1u;

  /* #20 Add UserData Bytes 0 - 2 to Crc data. */
  crcData[crcDataLength + 0u] = UserDataSecuredTlvPtr->UserByte0;                                                      /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcData[crcDataLength + 1u] = UserDataSecuredTlvPtr->UserByte1;                                                      /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcData[crcDataLength + 2u] = UserDataSecuredTlvPtr->UserByte2;                                                      /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcDataLength += 3u;

  /* #30 Add DataId to Crc data. */
  crcData[crcDataLength] = DataId;                                                                                     /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcDataLength += 1u;

  /* #40 Calculate and return the Crc value. */
  return Crc_CalculateCRC8H2F(crcData, crcDataLength, 0, TRUE);                                                        /* SBSW_ETHTSYN_VARIABLE_ARRAY_AS_POINTER */
} /* EthTSyn_Crc_ComputeUserDataCrc() */

/**********************************************************************************************************************
 *  EthTSyn_Crc_ComputeOfsCrc
 *********************************************************************************************************************/
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
 *
 */
FUNC(uint8, ETHTSYN_CODE) EthTSyn_Crc_ComputeOfsCrc(
                  uint8                    DataId,
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvOfsType) OfsSecuredTlvPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 crcData[ETHTSYN_CRC_OFS_CRC_DATA_SIZE];
  uint8 crcDataLength = 0;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Add Ofs Time Domain to Crc data. */
  crcData[crcDataLength] = OfsSecuredTlvPtr->OfsTimeDomain;                                                            /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcDataLength += 1u;

  /* #20 Add Ofs Time Sec to Crc data. */
  crcData[crcDataLength + 0u] = OfsSecuredTlvPtr->OfsTimeSec[0u];                                                      /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcData[crcDataLength + 1u] = OfsSecuredTlvPtr->OfsTimeSec[1u];                                                      /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcData[crcDataLength + 2u] = OfsSecuredTlvPtr->OfsTimeSec[2u];                                                      /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcData[crcDataLength + 3u] = OfsSecuredTlvPtr->OfsTimeSec[3u];                                                      /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcData[crcDataLength + 4u] = OfsSecuredTlvPtr->OfsTimeSec[4u];                                                      /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcData[crcDataLength + 5u] = OfsSecuredTlvPtr->OfsTimeSec[5u];                                                      /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcDataLength += 6u;

  /* #30 Add Ofs Time NSec to Crc dat. */
  crcData[crcDataLength + 0u] = OfsSecuredTlvPtr->OfsTimeNSec[0u];                                                     /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcData[crcDataLength + 1u] = OfsSecuredTlvPtr->OfsTimeNSec[1u];                                                     /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcData[crcDataLength + 2u] = OfsSecuredTlvPtr->OfsTimeNSec[2u];                                                     /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcData[crcDataLength + 3u] = OfsSecuredTlvPtr->OfsTimeNSec[3u];                                                     /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcDataLength += 4u;

  /* #40 Add Status to Crc data. */
  crcData[crcDataLength] = OfsSecuredTlvPtr->Status;                                                                   /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcDataLength += 1u;

  /* #50 Add UserData Length to Crc data. */
  crcData[crcDataLength] = OfsSecuredTlvPtr->UserDataLength;                                                           /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcDataLength += 1u;

  /* #60 Add UserData bytes 0 - 2 to Crc data. */
  crcData[crcDataLength + 0u] = OfsSecuredTlvPtr->UserByte0;                                                           /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcData[crcDataLength + 1u] = OfsSecuredTlvPtr->UserByte1;                                                           /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcData[crcDataLength + 2u] = OfsSecuredTlvPtr->UserByte2;                                                           /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcDataLength += 3u;

  /* #70 Add DataId to Crc data. */
  crcData[crcDataLength] = DataId;                                                                                     /* SBSW_ETHTSYN_CRC_DATA_ARRAY_SIZE */
  crcDataLength += 1u;

  /* #80 Calculate and return the Crc value. */
  return Crc_CalculateCRC8H2F(crcData, crcDataLength, 0, TRUE);                                                        /* SBSW_ETHTSYN_VARIABLE_ARRAY_AS_POINTER */
} /* EthTSyn_Crc_ComputeOfsCrc() */

/**********************************************************************************************************************
 *  EthTSyn_Crc_ValidateSubTlvCrc
 *********************************************************************************************************************/
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
FUNC(boolean, ETHTSYN_CODE) EthTSyn_Crc_ValidateSubTlvCrc(
                  uint8                               DataId,
  ETHTSYN_P2CONST(EthTSyn_CommonMsgHdrType)           ComMsgPtr,
  ETHTSYN_P2CONST(EthTSyn_ArSubTlvAbstractHeaderType) ArSubTlvPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean crcIsValid;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check Ar Sub Tlv type */
  switch (ArSubTlvPtr->Type)
  {
  case ETHTSYN_AR_SUB_TLV_TYPE_TIME_SECURED:
      {
        /* #100 Ar Sub Tlv type: Time Secured -> Validate Crc */
        crcIsValid = EthTSyn_Crc_ValidateTimeCrc(DataId, ComMsgPtr,                                                      /* SBSW_ETHTSYN_PASSING_API_POINTER */
          (ETHTSYN_P2CONST(EthTSyn_ArSubTlvTimeSecuredType))ArSubTlvPtr); /* PRQA S 0310 */ /* MD_EthTSyn_0310_SubType */
        break;
      }

  case ETHTSYN_AR_SUB_TLV_TYPE_OFS_SECURED:
    {
      /* #101 Ar Sub Tlv type: Ofs Secured -> Validate Crc */
      crcIsValid = EthTSyn_Crc_ValidateOfsCrc(DataId, (ETHTSYN_P2CONST(EthTSyn_ArSubTlvOfsType))ArSubTlvPtr); /* PRQA S 0310 */ /* MD_EthTSyn_0310_SubType */ /* SBSW_ETHTSYN_PASSING_API_POINTER */
      break;
    }

  case ETHTSYN_AR_SUB_TLV_TYPE_STATUS_SECURED:
    {
      /* #102 Ar Sub Tlv type: Status Secured -> Validate Crc */
      crcIsValid = EthTSyn_Crc_ValidateStatusCrc(DataId, (ETHTSYN_P2CONST(EthTSyn_ArSubTlvStatusType))ArSubTlvPtr); /* PRQA S 0310 */ /* MD_EthTSyn_0310_SubType */ /* SBSW_ETHTSYN_PASSING_API_POINTER */
      break;
    }

  case ETHTSYN_AR_SUB_TLV_TYPE_USER_DATA_SECURED:
    {
      /* #103 Ar Sub Tlv type: UserData Secured -> Validate Crc */
      crcIsValid = EthTSyn_Crc_ValidateUserDataCrc(DataId, (ETHTSYN_P2CONST(EthTSyn_ArSubTlvUserDataType))ArSubTlvPtr); /* PRQA S 0310 */ /* MD_EthTSyn_0310_SubType */ /* SBSW_ETHTSYN_PASSING_API_POINTER */
      break;
    }

  default:
    {
      /* #104 Not secured or unknown Ar Sub Tlv type -> return with positive value */
      crcIsValid = TRUE;
      break;
    }

  }

  return crcIsValid;
} /* EthTSyn_Crc_ValidateSubTlvCrc() */

# define ETHTSYN_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* (ETHTSYN_CRC_SUPPORT == STD_ON) */

/* Justification for module-specific MISRA deviations:
* see file EthTSyn.c
*/

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Crc_Int.c
 *********************************************************************************************************************/
