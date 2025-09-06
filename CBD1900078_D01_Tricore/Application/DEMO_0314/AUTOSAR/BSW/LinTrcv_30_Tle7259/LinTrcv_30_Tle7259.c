/**********************************************************************************************************************
 * COPYRIGHT
 * -------------------------------------------------------------------------------------------------------------------
 * \verbatim
 * Copyright (c) 2018 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *               This software is copyright protected and proprietary to Vector Informatik GmbH.
 *               Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *               All other rights remain with Vector Informatik GmbH.
 * \endverbatim
 * -------------------------------------------------------------------------------------------------------------------
 * FILE DESCRIPTION
 * -------------------------------------------------------------------------------------------------------------------
 *         File:  LinTrcv_30_Tle7259.c
 *      Project:  MICROSAR
 *       Module:  LIN Transceiver Driver
 *  Description:  Implementation of the MICROSAR LIN Transceiver Driver
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * */

#define LINTRCV_30_TLE7259_SOURCE

/**********************************************************************************************************************
 * MISRA
 *********************************************************************************************************************/
/* Disable the following MISRA warnings because they would appear too often for individual suppression.
 * See justification at the end of file */

/* PRQA  S 1881 EOF */ /* MD_MSR_AutosarBoolean */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#define LINTRCV_30_TLE7259_INCLUDE_INTERNAL
#include "LinIf.h"
#include "LinTrcv_30_Tle7259.h"
#include "Schm_LinTrcv_30_Tle7259.h"

#if (LINTRCV_30_TLE7259_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

#if (LINTRCV_30_TLE7259_ECUMWAKEUPSOURCEIDOFCHANNEL == STD_ON)
# include "EcuM_Cbk.h"
#endif

#if (LINTRCV_30_TLE7259_ICUCHANNELIDOFCHANNEL == STD_ON)
# include "Icu.h"
#endif

#if (LINTRCV_30_TLE7259_ECUMWAKEUPSOURCEIDOFCHANNEL == STD_ON)
# include "LinIf_Cbk.h"
#endif


/***********************************************************************************************************************
 * VERSION CHECK
 **********************************************************************************************************************/
#if ( DRVTRANS_TLE7259LINDIOASR_VERSION != 0x0603u )  /* COV_LINTRCV_CONFIG XF */
# error "Module LinTrcv_30_Tle7259: Source and Header files are inconsistent!"
#endif
#if ( DRVTRANS_TLE7259LINDIOASR_RELEASE_VERSION != 0x00u )  /* COV_LINTRCV_CONFIG XF */
# error "Module LinTrcv_30_Tle7259: Source and Header files are inconsistent!"
#endif
#if (DRVTRANS_LIN_30_TLE7259_GENTOOL_CFG5_MAJOR_VERSION != 0x06U) /* COV_LINTRCV_CONFIG XF */
# error "Module LinTrcv_30_Tle7259: Static and Generated files are inconsistent!"
#endif
#if (DRVTRANS_LIN_30_TLE7259_GENTOOL_CFG5_MINOR_VERSION != 0x02U) /* COV_LINTRCV_CONFIG XF */
# error "Module LinTrcv_30_Tle7259: Static and Generated files are inconsistent!"
#endif

/***********************************************************************************************************************
 * CONFIGURATION CHECK
 **********************************************************************************************************************/
#if (LINTRCV_30_TLE7259_ECUMWAKEUPSOURCEIDOFCHANNEL == STD_ON)
# if (LINTRCV_30_TLE7259_WAKEUPBYBUSUSEDOFCHANNEL == STD_ON) /* COV_LINTRCV_CONFIG XF */
# elif (LINTRCV_30_TLE7259_WAKEUPBYPINUSEDOFCHANNEL == STD_ON) /* COV_LINTRCV_CONFIG XX */ /* COV_LINTRCV_CONFIG XF */
# else
#  error "The EcuM wakeup source of the LinTrcv channel should be enabled only if wakeup by bus or/and pin is enabled for same the channel"
# endif
#endif

#if (LINTRCV_30_TLE7259_ECUMWAKEUPSOURCEIDOFCHANNEL == STD_ON)
# if (LINTRCV_30_TLE7259_WAKEUPSUPPORT == STD_ON) /* COV_LINTRCV_CONFIG XF */
# else
#  error "LinTrcvWakeUpSupport in LinTrcvGeneral must be enabled if wakeup by busor/and pin is enabled for any channel"
# endif
#endif

#if ! defined (LINTRCV_30_TLE7259_DUMMY_STATEMENT)
# error "The define LINTRCV_30_TLE7259_DUMMY_STATEMENT shall be defined either in Compiler_Cfg.h or as parameter for the Compiler!"
#endif

#if ! defined (LINTRCV_30_TLE7259_LOCAL) /* COV_LINTRCV_COMPATIBILITY */
# define LINTRCV_30_TLE7259_LOCAL                         static
#endif

#if ! defined (LINTRCV_30_TLE7259_LOCAL_INLINE) /* COV_LINTRCV_COMPATIBILITY */
# define LINTRCV_30_TLE7259_LOCAL_INLINE                  LOCAL_INLINE
#endif

#if ! defined (LINTRCV_30_TLE7259_INSTANCE_ID_DET) /* COV_LINTRCV_COMPATIBILITY */
# define LINTRCV_30_TLE7259_INSTANCE_ID_DET               LINTRCV_30_TLE7259_INSTANCE_ID
#endif


/**********************************************************************************************************************
 * LOCAL DEFINES
 **********************************************************************************************************************/
#if (LINTRCV_30_TLE7259_DEV_ERROR_DETECT == STD_ON)
# define LinTrcv_30_Tle7259_Dev_InitValue                 ((uint8)0x00u)
# define LinTrcv_30_Tle7259_Dev_CheckValue                ((uint8)0xA5u)
#endif

/**********************************************************************************************************************
 * LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/
#if (LINTRCV_30_TLE7259_DEV_ERROR_DETECT == STD_ON)
# define LINTRCV_30_TLE7259_START_SEC_VAR_ZERO_INIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/* Variable LinTrcv_30_Tle7259_Dev_InitDetect must be initialized after reset for working Debug check */
LINTRCV_30_TLE7259_LOCAL VAR(uint8, LINTRCV_30_TLE7259_VAR_ZERO_INIT) LinTrcv_30_Tle7259_Dev_InitDetect = LinTrcv_30_Tle7259_Dev_InitValue;
# define LINTRCV_30_TLE7259_STOP_SEC_VAR_ZERO_INIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif

#if (LINTRCV_30_TLE7259_USE_INIT_POINTER == STD_ON)
# define LINTRCV_30_TLE7259_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/* Pointer to Global Configuration */
LINTRCV_30_TLE7259_LOCAL P2CONST(LinTrcv_30_Tle7259_ConfigType, LINTRCV_30_TLE7259_VAR_ZERO_INIT, LINTRCV_30_TLE7259_INIT_DATA) LinTrcv_30_Tle7259_ConfigDataPtr = NULL_PTR;
# define LINTRCV_30_TLE7259_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif


/**********************************************************************************************************************
 * GLOBAL DATA
 **********************************************************************************************************************/
#define LINTRCV_30_TLE7259_START_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
CONST(uint8, LINTRCV_30_TLE7259_CONST) LinTrcv_30_Tle7259_MainVersion = (uint8)(LINTRCV_30_TLE7259_SW_MAJOR_VERSION);
CONST(uint8, LINTRCV_30_TLE7259_CONST) LinTrcv_30_Tle7259_SubVersion = (uint8)(LINTRCV_30_TLE7259_SW_MINOR_VERSION);
CONST(uint8, LINTRCV_30_TLE7259_CONST) LinTrcv_30_Tle7259_ReleaseVersion = (uint8)(LINTRCV_30_TLE7259_SW_PATCH_VERSION);
#define LINTRCV_30_TLE7259_STOP_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define LINTRCV_30_TLE7259_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * LOCAL FUNCTIONS
 **********************************************************************************************************************/


/**********************************************************************************************************************
 * GLOBAL FUNCTIONS
 **********************************************************************************************************************/


/***********************************************************************************************************************
 * LinTrcv_30_Tle7259_InitMemory()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, LINTRCV_30_TLE7259_CODE) LinTrcv_30_Tle7259_InitMemory
(
  void
)
{

  /* #10 Set state to uninitialized */
#if (LINTRCV_30_TLE7259_DEV_ERROR_DETECT == STD_ON)
  LinTrcv_30_Tle7259_Dev_InitDetect = LinTrcv_30_Tle7259_Dev_InitValue;
#endif

  /* #20 Uninitialize the local init pointer */
#if (LINTRCV_30_TLE7259_USE_INIT_POINTER == STD_ON)
  LinTrcv_30_Tle7259_ConfigDataPtr = NULL_PTR;
#endif
}

/***********************************************************************************************************************
 * LinTrcv_30_Tle7259_Init()
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
 *
 *
 *
 *
 */
FUNC(void, LINTRCV_30_TLE7259_CODE) LinTrcv_30_Tle7259_Init
(
  P2CONST(LinTrcv_30_Tle7259_ConfigType, AUTOMATIC, LINTRCV_30_TLE7259_INIT_DATA) ConfigPtr /* PRQA S 3206 */ /* MD_LINTRCV_3206 */
)
{
  VAR(uint8, AUTOMATIC) LinTrcvIndex;
  VAR(Std_ReturnType, AUTOMATIC) LinTrcv_ReturnValTmp = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  VAR(uint8, AUTOMATIC) LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_NO_ERROR; /* PRQA S 3205, 2981 */ /* MD_LINTRCV_3205, MD_MSR_RetVal */

#if (LINTRCV_30_TLE7259_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if the component is already initialized */
  if (LinTrcv_30_Tle7259_Dev_InitDetect != LinTrcv_30_Tle7259_Dev_InitValue)
  {
    LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_UNINIT; /* PRQA S 2983 */ /* MD_LINTRCV_2983 */
  }
# if (LINTRCV_30_TLE7259_USE_INIT_POINTER == STD_ON)
  /* #20 Check the validity of the pointer ConfigPtr */
  else if (ConfigPtr == NULL_PTR)
  {
    LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_PARAM_POINTER; /* PRQA S 2983 */ /* MD_LINTRCV_2983 */
  }
# endif
  else
#endif
  {
#if (LINTRCV_30_TLE7259_USE_INIT_POINTER == STD_ON)
    LinTrcv_30_Tle7259_ConfigDataPtr = ConfigPtr;
#endif

    /* #25 Loop over all configured channels */
    for (LinTrcvIndex = 0x00u; LinTrcvIndex < LinTrcv_30_Tle7259_NrOfChannels; LinTrcvIndex++)
    {
      /* #30 If the channel is used */
      if (LinTrcv_30_Tle7259_IsChannelUsedOfChannel(LinTrcvIndex))
      {
#if (LINTRCV_30_TLE7259_WAKEUPSUPPORT == STD_ON)
        /* #40 Enable Wakeup reporting for the channel, initialise WakeupReason value */
        LinTrcv_30_Tle7259_ChannelData[LinTrcvIndex].LinTrcv_30_Tle7259_WakeupMode = LINTRCV_WUMODE_ENABLE; /* SBSW_LINTRCV_CHANNEL_DATA */
        LinTrcv_30_Tle7259_ChannelData[LinTrcvIndex].LinTrcv_30_Tle7259_WakeupReason = LINTRCV_WU_ERROR; /* SBSW_LINTRCV_CHANNEL_DATA */
#endif
        /* #50 Set the hardware OpMode according to the parameter LinTrcvInitState (normal or sleep) */
        switch(LinTrcv_30_Tle7259_GetInitStateOfChannel(LinTrcvIndex))
        {
          case LINTRCV_30_TLE7259_OP_MODE_NORMAL:
            Dio_WriteChannel(LinTrcv_30_Tle7259_GetDioPinEnOfDioChannel(LinTrcvIndex), STD_HIGH);
            LinTrcv_ReturnValTmp = E_OK;

#if (LINTRCV_30_TLE7259_ICUCHANNELIDOFCHANNEL == STD_ON) || (LINTRCV_30_TLE7259_WAKEUPSUPPORT == STD_ON)
            {
# if (LINTRCV_30_TLE7259_ICUCHANNELIDOFCHANNEL == STD_ON)
              /* #60 Normal mode successfully set: If Icu is used, disable Icu notification */
              if (LinTrcv_30_Tle7259_IsIcuChannelIdUsedOfChannel(LinTrcvIndex))
              {
                Icu_DisableNotification(LinTrcv_30_Tle7259_GetIcuChannelIdOfChannel(LinTrcvIndex));
              }
# endif
# if (LINTRCV_30_TLE7259_WAKEUPSUPPORT == STD_ON)
              /* #70 Set the WakeupReason to RESET */
              LinTrcv_30_Tle7259_ChannelData[LinTrcvIndex].LinTrcv_30_Tle7259_WakeupReason = LINTRCV_WU_RESET; /* SBSW_LINTRCV_CHANNEL_DATA */
# endif
            }
#endif
            break;

          case LINTRCV_30_TLE7259_OP_MODE_SLEEP:
#if (LINTRCV_30_TLE7259_SLEEPINITWORKAROUNDOFTLE7259CHANNEL == STD_ON)
            if (LinTrcv_30_Tle7259_IsSleepInitWorkaroundOfTle7259Channel(LinTrcvIndex))
            {
              /* Switch into normal operation mode first */
              Dio_WriteChannel(LinTrcv_30_Tle7259_GetDioPinEnOfDioChannel(LinTrcvIndex), STD_HIGH);

              /* Invoke the call-out function Appl_LinTrcv_30_Tle7259_Wait() */
              Appl_LinTrcv_30_Tle7259_Wait(LINTRCV_30_TLE7259_WAIT_COUNT);
            }
#endif
            /* Switch into sleep operation mode */
            Dio_WriteChannel(LinTrcv_30_Tle7259_GetDioPinEnOfDioChannel(LinTrcvIndex), STD_LOW);
            LinTrcv_ReturnValTmp = E_OK;

#if (LINTRCV_30_TLE7259_ICUCHANNELIDOFCHANNEL == STD_ON)
            /* #80 Sleep mode successfully set: If Icu is used, enable Icu notification */
            {
              if (LinTrcv_30_Tle7259_IsIcuChannelIdUsedOfChannel(LinTrcvIndex))
              {
                Icu_EnableNotification(LinTrcv_30_Tle7259_GetIcuChannelIdOfChannel(LinTrcvIndex));
              }
            }
#endif
            break;

          default: /* COV_LINTRCV_MISRA */
            LinTrcv_ReturnValTmp = E_NOT_OK;
            break;
        }

        if (LinTrcv_ReturnValTmp == E_OK) /* COV_LINTRCV_CONFIG TX */
        {
#if (LINTRCV_30_TLE7259_WAIT_COUNT_USED == STD_ON)
          /* #90 Invoke the call-out function Appl_LinTrcv_30_Tle7259_Wait() */
          Appl_LinTrcv_30_Tle7259_Wait(LINTRCV_30_TLE7259_WAIT_COUNT);
#endif

          /* #100 Change the internal state to the initial operation mode */
          LinTrcv_30_Tle7259_ChannelData[LinTrcvIndex].LinTrcv_30_Tle7259_State = LinTrcv_30_Tle7259_GetInitStateOfChannel(LinTrcvIndex); /* SBSW_LINTRCV_CHANNEL_DATA */
        }
        else
        {
          /* Break the init loop in case of any E_NOT_OK return */
          break;
        }
      }
    }
  }

#if (LINTRCV_30_TLE7259_DEV_ERROR_REPORT == STD_ON)
  if (LinTrcv_ErrorId != LINTRCV_30_TLE7259_E_NO_ERROR)
  {
    (void)Det_ReportError(LINTRCV_30_TLE7259_MODULE_ID, LINTRCV_30_TLE7259_INSTANCE_ID_DET, LINTRCV_30_TLE7259_SID_INIT, LinTrcv_ErrorId);
  }
#else
  LINTRCV_30_TLE7259_DUMMY_STATEMENT(LinTrcv_ErrorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#endif

#if (LINTRCV_30_TLE7259_DEV_ERROR_DETECT == STD_ON)
  if(LinTrcv_ReturnValTmp == E_OK)
  {
    /* Initialization went through, set flag */
    LinTrcv_30_Tle7259_Dev_InitDetect = LinTrcv_30_Tle7259_Dev_CheckValue;
  }
#endif

#if (LINTRCV_30_TLE7259_USE_INIT_POINTER == STD_OFF)
  LINTRCV_30_TLE7259_DUMMY_STATEMENT(ConfigPtr); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif
} /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */

/***********************************************************************************************************************
 * LinTrcv_30_Tle7259_SetOpMode()
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
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, LINTRCV_30_TLE7259_CODE) LinTrcv_30_Tle7259_SetOpMode
(
  VAR(uint8, AUTOMATIC) LinTrcvIndex,
  VAR(LinTrcv_TrcvModeType, AUTOMATIC) OpMode
)
{
  VAR(Std_ReturnType, AUTOMATIC) LinTrcv_ReturnValTmp = E_NOT_OK;
  VAR(uint8, AUTOMATIC) LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_NO_ERROR; /* PRQA S 3205, 2981 */ /* MD_LINTRCV_3205, MD_MSR_RetVal */


#if (LINTRCV_30_TLE7259_DEV_ERROR_DETECT == STD_ON)
  if (LinTrcv_30_Tle7259_Dev_InitDetect != LinTrcv_30_Tle7259_Dev_CheckValue)
  {
    LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_UNINIT; /* PRQA S 2983 */ /* MD_LINTRCV_2983 */
  }
  /* #10 Check the validity of the parameter LinTrcvIndex */
  else if (LinTrcvIndex >= LinTrcv_30_Tle7259_NrOfChannels)
  {
    LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_INVALID_LIN_NETWORK; /* PRQA S 2983 */ /* MD_LINTRCV_2983 */
  }
  else if (LinTrcv_30_Tle7259_IsChannelUsedOfChannel(LinTrcvIndex) != TRUE)
  {
    LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_INVALID_LIN_NETWORK; /* PRQA S 2983 */ /* MD_LINTRCV_2983 */
  }
  else
#endif
  {

    /* #20 Enter critical area */
    SchM_Enter_LinTrcv_30_Tle7259_LINTRCV_30_TLE7259_EXCLUSIVE_AREA_0();

    /* #30 Set OpMode according to the parameter OpMode (normal or sleep) */
    switch(OpMode)
    {

      case LINTRCV_30_TLE7259_OP_MODE_NORMAL:
        Dio_WriteChannel(LinTrcv_30_Tle7259_GetDioPinEnOfDioChannel(LinTrcvIndex), STD_HIGH);
        LinTrcv_ReturnValTmp = E_OK;

#if (LINTRCV_30_TLE7259_ICUCHANNELIDOFCHANNEL == STD_ON) || (LINTRCV_30_TLE7259_WAKEUPSUPPORT == STD_ON)
        {
# if (LINTRCV_30_TLE7259_ICUCHANNELIDOFCHANNEL == STD_ON)
          /* #40 Normal mode sucessfully set: If Icu is used, disable Icu notification */
          if (LinTrcv_30_Tle7259_IsIcuChannelIdUsedOfChannel(LinTrcvIndex))
          {
            Icu_DisableNotification(LinTrcv_30_Tle7259_GetIcuChannelIdOfChannel(LinTrcvIndex));
          }
# endif
# if (LINTRCV_30_TLE7259_WAKEUPSUPPORT == STD_ON)
          /* #50 If Sleep->Normal transition */
          if (LinTrcv_30_Tle7259_ChannelData[LinTrcvIndex].LinTrcv_30_Tle7259_State == LINTRCV_30_TLE7259_OP_MODE_SLEEP)
          {
            /* #60 If no WakeupReason is stored: Set WakeupReason to internal */
#  if (LINTRCV_30_TLE7259_ECUMWAKEUPSOURCEIDOFCHANNEL == STD_ON)
            /* This if statement is needed only when external wakeups are possible:
             * Unless external wakeups are possible, the LinTrcv channel was in sleep mode (WakeupReason == LINTRCV_WU_ERROR)
             * Making this if statement always true and useless. */
            if (LinTrcv_30_Tle7259_ChannelData[LinTrcvIndex].LinTrcv_30_Tle7259_WakeupReason == LINTRCV_WU_ERROR)
#  endif
            {
              LinTrcv_30_Tle7259_ChannelData[LinTrcvIndex].LinTrcv_30_Tle7259_WakeupReason = LINTRCV_WU_INTERNALLY; /* SBSW_LINTRCV_CHANNEL_DATA */
            }
          }
# endif
        }
#endif
        break;

      case LINTRCV_30_TLE7259_OP_MODE_SLEEP:
        Dio_WriteChannel(LinTrcv_30_Tle7259_GetDioPinEnOfDioChannel(LinTrcvIndex), STD_LOW);
        LinTrcv_ReturnValTmp = E_OK;

#if (LINTRCV_30_TLE7259_ICUCHANNELIDOFCHANNEL == STD_ON) || (LINTRCV_30_TLE7259_WAKEUPSUPPORT == STD_ON)
        {
# if (LINTRCV_30_TLE7259_ICUCHANNELIDOFCHANNEL == STD_ON)
          /* #70 Sleep mode sucessfully set: If Icu is used, enable Icu notification */
          if (LinTrcv_30_Tle7259_IsIcuChannelIdUsedOfChannel(LinTrcvIndex))
          {
            Icu_EnableNotification(LinTrcv_30_Tle7259_GetIcuChannelIdOfChannel(LinTrcvIndex));
          }
# endif
# if (LINTRCV_30_TLE7259_WAKEUPSUPPORT == STD_ON)
          /* #80 Clear WakeupReason */
          LinTrcv_30_Tle7259_ChannelData[LinTrcvIndex].LinTrcv_30_Tle7259_WakeupReason = LINTRCV_WU_ERROR; /* SBSW_LINTRCV_CHANNEL_DATA */
# endif
        }
#endif
        break;

      default: /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
#if (LINTRCV_30_TLE7259_DEV_ERROR_DETECT == STD_ON)
        LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_PARAM_TRCV_OPMODE; /* PRQA S 2983 */ /* MD_LINTRCV_2983 */
#endif
        break;
    }

    if(LinTrcv_ReturnValTmp == E_OK)
    {
      /* #90 Change the internal state to the requested operation mode */
      LinTrcv_30_Tle7259_ChannelData[LinTrcvIndex].LinTrcv_30_Tle7259_State = OpMode; /* SBSW_LINTRCV_CHANNEL_DATA */
    }

    /* #100 Exit critical area */
    SchM_Exit_LinTrcv_30_Tle7259_LINTRCV_30_TLE7259_EXCLUSIVE_AREA_0();

#if (LINTRCV_30_TLE7259_WAIT_COUNT_USED == STD_ON)
    /* #110 Invoke the call-out function Appl_LinTrcv_30_Tle7259_Wait() */
    if(LinTrcv_ReturnValTmp == E_OK)
    {
      Appl_LinTrcv_30_Tle7259_Wait(LINTRCV_30_TLE7259_WAIT_COUNT);
    }
#endif

  }

#if (LINTRCV_30_TLE7259_DEV_ERROR_REPORT == STD_ON)
  if (LinTrcv_ErrorId != LINTRCV_30_TLE7259_E_NO_ERROR)
  {
    (void)Det_ReportError(LINTRCV_30_TLE7259_MODULE_ID, LINTRCV_30_TLE7259_INSTANCE_ID_DET, LINTRCV_30_TLE7259_SID_SETOPMODE, LinTrcv_ErrorId);
  }
#else
  LINTRCV_30_TLE7259_DUMMY_STATEMENT(LinTrcv_ErrorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#endif

  return LinTrcv_ReturnValTmp;
} /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */

/***********************************************************************************************************************
 * LinTrcv_30_Tle7259_GetOpMode()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, LINTRCV_30_TLE7259_CODE) LinTrcv_30_Tle7259_GetOpMode
(
  VAR(uint8, AUTOMATIC) LinTrcvIndex,
  P2VAR(LinTrcv_TrcvModeType, AUTOMATIC, LINTRCV_30_TLE7259_APPL_VAR) OpMode
)
{
  VAR(Std_ReturnType, AUTOMATIC) LinTrcv_ReturnValTmp = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  VAR(uint8, AUTOMATIC) LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_NO_ERROR; /* PRQA S 3205, 2981 */ /* MD_LINTRCV_3205, MD_MSR_RetVal */

#if (LINTRCV_30_TLE7259_DEV_ERROR_DETECT == STD_ON)
  if (LinTrcv_30_Tle7259_Dev_InitDetect != LinTrcv_30_Tle7259_Dev_CheckValue)
  {
    LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_UNINIT; /* PRQA S 2983 */ /* MD_LINTRCV_2983 */
  }
  /* #10 Check the validity of the parameter LinTrcvIndex */
  else if (LinTrcvIndex >= LinTrcv_30_Tle7259_NrOfChannels)
  {
    LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_INVALID_LIN_NETWORK; /* PRQA S 2983 */ /* MD_LINTRCV_2983 */
  }
  else if (LinTrcv_30_Tle7259_IsChannelUsedOfChannel(LinTrcvIndex) != TRUE)
  {
    LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_INVALID_LIN_NETWORK; /* PRQA S 2983 */ /* MD_LINTRCV_2983 */
  }
  /* #20 Check the validity of the pointer OpMode */
  else if (OpMode == NULL_PTR)
  {
    LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_PARAM_POINTER; /* PRQA S 2983 */ /* MD_LINTRCV_2983 */
  }
  else
#endif
  {
    /* #30 Return the current OpMode */
    *OpMode = LinTrcv_30_Tle7259_ChannelData[LinTrcvIndex].LinTrcv_30_Tle7259_State; /* SBSW_LINTRCV_PTR */
    LinTrcv_ReturnValTmp = E_OK;
  }

#if (LINTRCV_30_TLE7259_DEV_ERROR_REPORT == STD_ON)
  if (LinTrcv_ErrorId != LINTRCV_30_TLE7259_E_NO_ERROR)
  {
    (void)Det_ReportError(LINTRCV_30_TLE7259_MODULE_ID, LINTRCV_30_TLE7259_INSTANCE_ID_DET, LINTRCV_30_TLE7259_SID_GETOPMODE, LinTrcv_ErrorId);
  }
#else
  LINTRCV_30_TLE7259_DUMMY_STATEMENT(LinTrcv_ErrorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#endif

  return LinTrcv_ReturnValTmp;
}

/***********************************************************************************************************************
 * LinTrcv_30_Tle7259_GetBusWuReason()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, LINTRCV_30_TLE7259_CODE) LinTrcv_30_Tle7259_GetBusWuReason
(
  VAR(uint8, AUTOMATIC) LinTrcvIndex,
  P2VAR(LinTrcv_TrcvWakeupReasonType, AUTOMATIC, LINTRCV_30_TLE7259_APPL_VAR) Reason
)
{
  VAR(Std_ReturnType, AUTOMATIC) LinTrcv_ReturnValTmp = E_NOT_OK;
  VAR(uint8, AUTOMATIC) LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_NO_ERROR; /* PRQA S 3205, 2981 */ /* MD_LINTRCV_3205, MD_MSR_RetVal */

#if (LINTRCV_30_TLE7259_DEV_ERROR_DETECT == STD_ON)
  if (LinTrcv_30_Tle7259_Dev_InitDetect != LinTrcv_30_Tle7259_Dev_CheckValue)
  {
    LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_UNINIT; /* PRQA S 2983 */ /* MD_LINTRCV_2983 */
  }
  /* #10 Check the validity of the parameter LinTrcvIndex */
  else if (LinTrcvIndex >= LinTrcv_30_Tle7259_NrOfChannels)
  {
    LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_INVALID_LIN_NETWORK; /* PRQA S 2983 */ /* MD_LINTRCV_2983 */
  }
  else if (LinTrcv_30_Tle7259_IsChannelUsedOfChannel(LinTrcvIndex) != TRUE)
  {
    LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_INVALID_LIN_NETWORK; /* PRQA S 2983 */ /* MD_LINTRCV_2983 */
  }
  /* #20 Check the validity of the pointer Reason */
  else if (Reason == NULL_PTR)
  {
    LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_PARAM_POINTER; /* PRQA S 2983 */ /* MD_LINTRCV_2983 */
  }
  else
#endif
  {
#if (LINTRCV_30_TLE7259_WAKEUPSUPPORT == STD_ON)
    /* #30 Return the current WakeupReason */
    *Reason = LinTrcv_30_Tle7259_ChannelData[LinTrcvIndex].LinTrcv_30_Tle7259_WakeupReason; /* SBSW_LINTRCV_PTR */

    /* #40 If the stored WakeupReason is valid: Return E_OK */
    if (LinTrcv_30_Tle7259_ChannelData[LinTrcvIndex].LinTrcv_30_Tle7259_WakeupReason != LINTRCV_WU_ERROR)
    {
      LinTrcv_ReturnValTmp = E_OK;
    }
#else
    *Reason = LINTRCV_WU_NOT_SUPPORTED; /* SBSW_LINTRCV_PTR */
    LINTRCV_30_TLE7259_DUMMY_STATEMENT (LinTrcvIndex); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif
  }

#if (LINTRCV_30_TLE7259_DEV_ERROR_REPORT == STD_ON)
  if (LinTrcv_ErrorId != LINTRCV_30_TLE7259_E_NO_ERROR)
  {
    (void)Det_ReportError(LINTRCV_30_TLE7259_MODULE_ID, LINTRCV_30_TLE7259_INSTANCE_ID_DET, LINTRCV_30_TLE7259_SID_GETBUSWUREASON, LinTrcv_ErrorId);
  }
#else
  LINTRCV_30_TLE7259_DUMMY_STATEMENT(LinTrcv_ErrorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#endif

  return LinTrcv_ReturnValTmp;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/***********************************************************************************************************************
 * LinTrcv_30_Tle7259_SetWakeupMode()
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
FUNC(Std_ReturnType, LINTRCV_30_TLE7259_CODE) LinTrcv_30_Tle7259_SetWakeupMode
(
  VAR(uint8, AUTOMATIC) LinTrcvIndex,
  VAR(LinTrcv_TrcvWakeupModeType, AUTOMATIC) TrcvWakeupMode /* PRQA S 3206 */ /* MD_LINTRCV_3206 */
)
{
  VAR(Std_ReturnType, AUTOMATIC) LinTrcv_ReturnValTmp = E_NOT_OK;
  VAR(uint8, AUTOMATIC) LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_NO_ERROR; /* PRQA S 3205, 2981 */ /* MD_LINTRCV_3205, MD_MSR_RetVal */

#if (LINTRCV_30_TLE7259_DEV_ERROR_DETECT == STD_ON)
  if (LinTrcv_30_Tle7259_Dev_InitDetect != LinTrcv_30_Tle7259_Dev_CheckValue)
  {
    LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_UNINIT; /* PRQA S 2983 */ /* MD_LINTRCV_2983 */
  }
  /* #10 Check the validity of the parameter LinTrcvIndex */
  else if (LinTrcvIndex >= LinTrcv_30_Tle7259_NrOfChannels)
  {
    LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_INVALID_LIN_NETWORK; /* PRQA S 2983 */ /* MD_LINTRCV_2983 */
  }
  else if (LinTrcv_30_Tle7259_IsChannelUsedOfChannel(LinTrcvIndex) != TRUE)
  {
    LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_INVALID_LIN_NETWORK; /* PRQA S 2983 */ /* MD_LINTRCV_2983 */
  }
  else
#endif
  {
#if (LINTRCV_30_TLE7259_WAKEUPSUPPORT == STD_ON)
      /* #20 Enter critical area */
      SchM_Enter_LinTrcv_30_Tle7259_LINTRCV_30_TLE7259_EXCLUSIVE_AREA_0();

      /* #30 Set WakeupMode according to the parameter TrcvWakeupMode */
      switch(TrcvWakeupMode)
      {
        case LINTRCV_WUMODE_ENABLE:
          /* #40 For enable mode: enable WakeupReport and notify any stored Wakeup events */
          LinTrcv_30_Tle7259_ChannelData[LinTrcvIndex].LinTrcv_30_Tle7259_WakeupMode = LINTRCV_WUMODE_ENABLE; /* SBSW_LINTRCV_CHANNEL_DATA */
# if (LINTRCV_30_TLE7259_ECUMWAKEUPSOURCEIDOFCHANNEL == STD_ON)
          switch (LinTrcv_30_Tle7259_ChannelData[LinTrcvIndex].LinTrcv_30_Tle7259_WakeupReason)
          {
#  if (LINTRCV_30_TLE7259_WAKEUPBYBUSUSEDOFCHANNEL == STD_ON) /* COV_LINTRCV_WU_BY_BUS */
            case LINTRCV_WU_BY_BUS:
#  endif
#  if (LINTRCV_30_TLE7259_WAKEUPBYPINUSEDOFCHANNEL == STD_ON) /* COV_LINTRCV_WU_BY_PIN */
            case LINTRCV_WU_BY_PIN:
#  endif
              EcuM_SetWakeupEvent(LinTrcv_30_Tle7259_GetEcuMWakeupSourceIdOfChannel(LinTrcvIndex));
              LinIf_WakeupConfirmation(LinTrcv_30_Tle7259_GetEcuMWakeupSourceIdOfChannel(LinTrcvIndex));
              break;

            default: /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
              break;
          }
# endif

          LinTrcv_ReturnValTmp = E_OK;
          break;

        case LINTRCV_WUMODE_DISABLE:
          /* #50 For disable mode: disable WakeupReport */
          LinTrcv_30_Tle7259_ChannelData[LinTrcvIndex].LinTrcv_30_Tle7259_WakeupMode = LINTRCV_WUMODE_DISABLE; /* SBSW_LINTRCV_CHANNEL_DATA */
          LinTrcv_ReturnValTmp = E_OK;
          break;

        case LINTRCV_WUMODE_CLEAR:
          /* #60 For clear mode: set the WakeupReason to WU_ERROR only if WakeupReport is disabled */
          if (LinTrcv_30_Tle7259_ChannelData[LinTrcvIndex].LinTrcv_30_Tle7259_WakeupMode == LINTRCV_WUMODE_DISABLE)
          {
            LinTrcv_30_Tle7259_ChannelData[LinTrcvIndex].LinTrcv_30_Tle7259_WakeupReason = LINTRCV_WU_ERROR; /* SBSW_LINTRCV_CHANNEL_DATA */
            LinTrcv_ReturnValTmp = E_OK;
          }
          break;

        default: /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
# if (LINTRCV_30_TLE7259_DEV_ERROR_DETECT == STD_ON)
          LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_PARAM_TRCV_WAKEUP_MODE;
# endif
          break;
      }

      /* #70 Exit critical area */
      SchM_Exit_LinTrcv_30_Tle7259_LINTRCV_30_TLE7259_EXCLUSIVE_AREA_0();
#else
    LINTRCV_30_TLE7259_DUMMY_STATEMENT (TrcvWakeupMode); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
    LINTRCV_30_TLE7259_DUMMY_STATEMENT (LinTrcvIndex); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif
  }

#if (LINTRCV_30_TLE7259_DEV_ERROR_REPORT == STD_ON)
  if (LinTrcv_ErrorId != LINTRCV_30_TLE7259_E_NO_ERROR)
  {
    (void)Det_ReportError(LINTRCV_30_TLE7259_MODULE_ID, LINTRCV_30_TLE7259_INSTANCE_ID_DET, LINTRCV_30_TLE7259_SID_SETWAKEUPMODE, LinTrcv_ErrorId);
  }
#else
  LINTRCV_30_TLE7259_DUMMY_STATEMENT(LinTrcv_ErrorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#endif

  return LinTrcv_ReturnValTmp;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/***********************************************************************************************************************
 * LinTrcv_30_Tle7259_CheckWakeup()
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
FUNC(Std_ReturnType, LINTRCV_30_TLE7259_CODE) LinTrcv_30_Tle7259_CheckWakeup
(
  VAR(uint8, AUTOMATIC) LinTrcvIndex
)
{
  VAR(Std_ReturnType, AUTOMATIC) LinTrcv_ReturnValTmp = E_NOT_OK;
  VAR(uint8, AUTOMATIC) LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_NO_ERROR; /* PRQA S 3205, 2981 */ /* MD_LINTRCV_3205, MD_MSR_RetVal */

#if (LINTRCV_30_TLE7259_ECUMWAKEUPSOURCEIDOFCHANNEL == STD_ON)
  VAR(uint8, AUTOMATIC) LinTrcv_WakeupDetected = 0;
#endif

#if (LINTRCV_30_TLE7259_DEV_ERROR_DETECT == STD_ON)
  if (LinTrcv_30_Tle7259_Dev_InitDetect != LinTrcv_30_Tle7259_Dev_CheckValue)
  {
    LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_UNINIT; /* PRQA S 2983 */ /* MD_LINTRCV_2983 */
  }
  /* #10 Check the validity of the parameter LinTrcvIndex */
  else if (LinTrcvIndex >= LinTrcv_30_Tle7259_NrOfChannels)
  {
    LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_INVALID_LIN_NETWORK; /* PRQA S 2983 */ /* MD_LINTRCV_2983 */
  }
  else if (LinTrcv_30_Tle7259_IsChannelUsedOfChannel(LinTrcvIndex) != TRUE)
  {
    LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_INVALID_LIN_NETWORK; /* PRQA S 2983 */ /* MD_LINTRCV_2983 */
  }
  else
#endif
  {
#if (LINTRCV_30_TLE7259_ECUMWAKEUPSOURCEIDOFCHANNEL == STD_ON)
    /* #20 If the channel is in sleep mode */
    if (LinTrcv_30_Tle7259_ChannelData[LinTrcvIndex].LinTrcv_30_Tle7259_State == LINTRCV_30_TLE7259_OP_MODE_SLEEP)
    {

      /* #30 Enter critical area */
      SchM_Enter_LinTrcv_30_Tle7259_LINTRCV_30_TLE7259_EXCLUSIVE_AREA_0();

      /* #40 Check for wakeups */
# if (LINTRCV_30_TLE7259_WAKEUPBYBUSUSEDOFCHANNEL == STD_ON)
      if (LinTrcv_30_Tle7259_IsWakeupByBusUsedOfChannel(LinTrcvIndex))
      {
        if ((Dio_ReadChannel(LinTrcv_30_Tle7259_GetDioPinRxOfDioChannel(LinTrcvIndex)) == STD_LOW) &&
            (Dio_ReadChannel(LinTrcv_30_Tle7259_GetDioPinTxOfDioChannel(LinTrcvIndex)) == STD_HIGH)) /* PRQA S 3415 */ /* MD_LINTRCV_3415 */
        {
          /* Rx low / Tx high: Wakeup by pin */
          LinTrcv_30_Tle7259_ChannelData[LinTrcvIndex].LinTrcv_30_Tle7259_WakeupReason = LINTRCV_WU_BY_BUS; /* SBSW_LINTRCV_CHANNEL_DATA */
          LinTrcv_WakeupDetected = 1;
        }
      }
# endif

# if (LINTRCV_30_TLE7259_WAKEUPBYPINUSEDOFCHANNEL == STD_ON)
      if (LinTrcv_30_Tle7259_IsWakeupByPinUsedOfChannel(LinTrcvIndex))
      {
        if ((Dio_ReadChannel(LinTrcv_30_Tle7259_GetDioPinRxOfDioChannel(LinTrcvIndex)) == STD_LOW) &&
            (Dio_ReadChannel(LinTrcv_30_Tle7259_GetDioPinTxOfDioChannel(LinTrcvIndex)) == STD_LOW)) /* PRQA S 3415 */ /* MD_LINTRCV_3415 */
        {
          /* Rx/Tx low: Wakeup by pin */
          LinTrcv_30_Tle7259_ChannelData[LinTrcvIndex].LinTrcv_30_Tle7259_WakeupReason = LINTRCV_WU_BY_PIN; /* SBSW_LINTRCV_CHANNEL_DATA */
          LinTrcv_WakeupDetected = 1;
        }
      }
# endif

      /* #50 If the WakeupMode is enabled: Notify EcuM/LinIf about detected wakeups (LL part) */
      if ((LinTrcv_WakeupDetected == 1u) && (LinTrcv_30_Tle7259_ChannelData[LinTrcvIndex].LinTrcv_30_Tle7259_WakeupMode == LINTRCV_WUMODE_ENABLE))
      {
        LinTrcv_ReturnValTmp = E_OK;
        EcuM_SetWakeupEvent(LinTrcv_30_Tle7259_GetEcuMWakeupSourceIdOfChannel(LinTrcvIndex));
        LinIf_WakeupConfirmation(LinTrcv_30_Tle7259_GetEcuMWakeupSourceIdOfChannel(LinTrcvIndex));
      }

      /* #60 Exit critical area */
      SchM_Exit_LinTrcv_30_Tle7259_LINTRCV_30_TLE7259_EXCLUSIVE_AREA_0();

    }
# if (LINTRCV_30_TLE7259_DEV_ERROR_DETECT == STD_ON)
    else
    {
      /* Channel is not in sleep mode */
      LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_TRCV_NOT_SLEEP;
    }
# endif
#else
  LINTRCV_30_TLE7259_DUMMY_STATEMENT (LinTrcvIndex); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
#endif
  }

#if (LINTRCV_30_TLE7259_DEV_ERROR_REPORT == STD_ON)
  if (LinTrcv_ErrorId != LINTRCV_30_TLE7259_E_NO_ERROR)
  {
    (void)Det_ReportError(LINTRCV_30_TLE7259_MODULE_ID, LINTRCV_30_TLE7259_INSTANCE_ID_DET, LINTRCV_30_TLE7259_SID_CHECKWAKEUP, LinTrcv_ErrorId);
  }
#else
  LINTRCV_30_TLE7259_DUMMY_STATEMENT(LinTrcv_ErrorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#endif

  return LinTrcv_ReturnValTmp;
} /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */

#if (LINTRCV_30_TLE7259_GET_VERSION_INFO == STD_ON)
/***********************************************************************************************************************
 * LinTrcv_30_Tle7259_GetVersionInfo()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, LINTRCV_30_TLE7259_CODE) LinTrcv_30_Tle7259_GetVersionInfo
(
  P2VAR(Std_VersionInfoType, AUTOMATIC, LINTRCV_30_TLE7259_APPL_VAR) VersionInfo
)
{
  VAR(uint8, AUTOMATIC) LinTrcv_ErrorId;
  LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_NO_ERROR; /* PRQA S 2982 */ /* MD_LINTRCV_2982 */

# if (LINTRCV_30_TLE7259_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check the validity of the pointer VersionInfo. Note: no uninit check is performed */
  if (VersionInfo == NULL_PTR)
  {
    LinTrcv_ErrorId = LINTRCV_30_TLE7259_E_PARAM_POINTER; /* PRQA S 2983 */ /* MD_LINTRCV_2983 */
  }
  else
# endif
  {
    /* #20 Set VersionInfo with the component information */
    VersionInfo->vendorID = LINTRCV_30_TLE7259_VENDOR_ID; /* SBSW_LINTRCV_PTR */
    VersionInfo->moduleID = LINTRCV_30_TLE7259_MODULE_ID; /* SBSW_LINTRCV_PTR */
    VersionInfo->sw_major_version = LINTRCV_30_TLE7259_SW_MAJOR_VERSION; /* SBSW_LINTRCV_PTR */
    VersionInfo->sw_minor_version = LINTRCV_30_TLE7259_SW_MINOR_VERSION; /* SBSW_LINTRCV_PTR */
    VersionInfo->sw_patch_version = LINTRCV_30_TLE7259_SW_PATCH_VERSION; /* SBSW_LINTRCV_PTR */
  }

# if (LINTRCV_30_TLE7259_DEV_ERROR_REPORT == STD_ON)
  if (LinTrcv_ErrorId != LINTRCV_30_TLE7259_E_NO_ERROR)
  {
    (void)Det_ReportError(LINTRCV_30_TLE7259_MODULE_ID, LINTRCV_30_TLE7259_INSTANCE_ID_DET, LINTRCV_30_TLE7259_SID_GETVERSIONINFO, LinTrcv_ErrorId);
  }
# else
  LINTRCV_30_TLE7259_DUMMY_STATEMENT(LinTrcv_ErrorId); /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
# endif
}
#endif

#define LINTRCV_30_TLE7259_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Justification for module-specific MISRA deviations:

   MD_LINTRCV_0883: rule 1.2
        Reason:     The Compiler_Cfg.inc and the MemMap.inc do not have an include protection.
        Risk:       They could be included to often.
        Prevention: The Compiler_Cfg.inc and the MemMap.inc are implemented according to template

   MD_LINTRCV_2982: rule 2.2
        Reason:     Assigned value of LinTrcv_ErrorId is not used before modification when dummy statement is not used.
        Risk:       Redundancy could exist.
        Prevention: N/A

   MD_LINTRCV_3205: rule 2.3
        Reason:     It is not used when error detection is disabled.
        Risk:       Unused type declarations could exist.
        Prevention: N/A

   MD_LINTRCV_3206: rule 2.7
        Reason:     Function parameter may not be used.
        Risk:       Unused parameter could exist.
        Prevention: N/A

   MD_LINTRCV_2983: rule 2.2
        Reason:     The assigned value is not used when Error reporting is disabled.
        Risk:       Redundant assignment statement could exist.
        Prevention: N/A

   MD_LINTRCV_3415: rule 13.5
        Reason:     If statement checks for two conditions simutaniously. This is necessary to detect the wakeup event.
        Risk:       Right hand condition is not always checked.
        Prevention: Program flow has been verified by component tests and review.

*/


/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_LINTRCV_CHANNEL_DATA
    \DESCRIPTION Array write access to LinTcv_ChannelData using index variable LinTrcvIndex.
    \COUNTERMEASURE \N The variable LinTrcvIndex is checked before to be less than LINTRCV_30_TLE7259_NROFCHANNELS.
                       The size of this array is always equal to number of channels configured. No out of bounds array access can occur
                       since LinTcv_ChannelData was created with the size equal to LINTRCV_30_TLE7259_NROFCHANNELS.

  \ID SBSW_LINTRCV_PTR
    \DESCRIPTION The function writes to the object referenced by parameter.
    \COUNTERMEASURE \N The caller ensures that the pointers passed to the parameter is valid.


  SBSW_JUSTIFICATION_END */

/* START_COVERAGE_JUSTIFICATION

  \ID COV_LINTRCV_COMPATIBILITY
    \ACCEPT TX
    \REASON [COV_MSR_COMPATIBILITY]

  \ID COV_LINTRCV_MISRA
     \ACCEPT X
     \ACCEPT TX
     \REASON [MSR_COV_MISRA]

  \ID COV_LINTRCV_CONFIG
    \REASON [COV_MSR_CONFIG]

  \ID COV_LINTRCV_WU_BY_BUS
    \REASON N/A

  \ID COV_LINTRCV_WU_BY_PIN
    \REASON N/A

  \ID COV_LINTRCV_SLEEPINITWORKAROUND
    \ACCEPT XF tf tf
    \REASON only external declaration of function, in code are all paths coverd.

  END_COVERAGE_JUSTIFICATION */

/**********************************************************************************************************************
 * END OF FILE: LinTrcv_30_Tle7259.c
 *********************************************************************************************************************/
