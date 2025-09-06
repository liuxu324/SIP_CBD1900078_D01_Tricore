/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2016)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : CanIf_Cbk.c                                                 **
**                                                                           **
**  VERSION    : 1.0.0                                                       **
**                                                                           **
**  DATE       : 2016-10-13                                                  **
**                                                                           **
**  VARIANT    : NA                                                          **
**                                                                           **
**  PLATFORM   : Infineon AURIX2G                                            **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : Implementation of CAN Interface callback functions         **
**                  This file is for Evaluation Purpose Only                 **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/
#include "CanIf_Cbk.h"
#if (APP_SW == DEMO_APP)
#include "Test_Print.h"
#endif

/* Macro to set MSB for Extended messages */
#define CAN_EXTENDED_MSB_SET            (0x80000000U)

#if (CAN_ID_CONFIG_TYPE == CAN_ID_STANDARD)
#define CAN_FD_STANDARD               ((uint16)0x4000U)
#else
#define CAN_FD_STANDARD               ((uint32)0x40000000U)
#endif

extern uint8 Test_RxConfirmCount;
extern uint8 Test_TxConfirmCount;
extern uint8 CanRxDataBuff[20][64];  

/*******************************************************************************
                      CanIf_RxIndication
*******************************************************************************/
#define CAN_17_MCMCAN_START_SEC_CODE_QM_GLOBAL
#include "Can_17_McmCan_MemMap.h"

#if (APP_SW != TEST_APP)

void CanIf_RxIndication(const Can_HwType *Mailbox,const PduInfoType *PduInfoPtr)
{
#if (APP_SW == DEMO_APP)
  uint8 i;
  uint16 MsgdlcCnt;
  uint16 CanDlc;
  Can_HwHandleType Hrh;
  Can_IdType CanId;  
  uint8 *CanSduPtr; 

  Hrh = Mailbox->Hoh;
  CanId = Mailbox->CanId;
  CanSduPtr = PduInfoPtr->SduDataPtr;
  CanDlc = PduInfoPtr->SduLength;
 
#if (CAN_FD_ENABLE  == STD_ON)   
  if (CAN_FD_STANDARD == (CanId & CAN_FD_STANDARD))
  {
    print_f("\n CAN FD Message Received ");
  }
  else
  {
    print_f("\n Classical CAN Message Received ");
  }
#endif    

   MsgdlcCnt =  CanDlc;

#if (CAN_ID_CONFIG_TYPE != CAN_ID_STANDARD) 
  if(CanId & CAN_EXTENDED_MSB_SET)
  {
    print_f("\n Received a Extended Id Message! ");
    print_f("\n Hrh = %d, ID = 0x%x, DLC = %d",Hrh,CanId&0x1FFFFFFF,MsgdlcCnt);
  }
  else
#endif
  {
    print_f("\n Received a Standard Id Message! ");
    print_f("\n Hrh = %d, ID = 0x%x, DLC = %d", Hrh, CanId, MsgdlcCnt );
  } 
  
 print_f(" Msg = ");	
	
	for (i=0; i < MsgdlcCnt ; i++)
	{
		print_f("%x ",CanSduPtr[i]);
		CanRxDataBuff[Test_RxConfirmCount][i] = CanSduPtr[i];
	}
	
	Test_RxConfirmCount++ ;
	  
    print_f("\n");
	
#endif
}

/*******************************************************************************
                      CanIf_TxConfirmation
*******************************************************************************/
void CanIf_TxConfirmation (PduIdType CanTxPduId)
{
#if (APP_SW == DEMO_APP)
  print_f("\n Transmitted a message! CanTxPduId = %d", CanTxPduId);
  Test_TxConfirmCount++ ;
#endif
}

/*******************************************************************************
                      CanIf_ControllerBusOff
*******************************************************************************/
void CanIf_ControllerBusOff(uint8 ControllerId)
{
#if (APP_SW == DEMO_APP)
  print_f("\n Callback function Can_ControllerBusOff is called!");
  print_f("ControllerId = %d", ControllerId);
#endif
}

/*******************************************************************************
                    CanIf_ControllerModeIndication
*******************************************************************************/
void CanIf_ControllerModeIndication( uint8 ControllerId,
                                     CanIf_ControllerModeType ControllerMode )
{
#if (APP_SW == DEMO_APP)
  print_f("\n Callback function CanIf_ControllerModeIndication is called!\n");
  print_f(" ControllerId = %d \n", ControllerId);
  print_f(" ControllerMode = %d \n", ControllerMode);
#endif
}

/*******************************************************************************
                  CAN L-PDU Rx Callout Function Definition
*******************************************************************************/
boolean Appl_LPduRxCalloutFunction(uint8 Hrh,
                                   Can_IdType CanId,
                                   uint8 CanDlc,
                                   const uint8 *CanSduPtr)
{
#ifdef AURIX2G_MCAL_DEMOAPP
  print_f("\n Callback function Appl_LPduRxCalloutFunction is called!");
#endif
  return(TRUE);
}

/*******************************************************************************
                    CanIf_CurrentIcomConfiguration
*******************************************************************************/
void CanIf_CurrentIcomConfiguration(uint8 ControllerId,
                                    IcomConfigIdType ConfigurationId,
                                    IcomSwitch_ErrorType Error)
{
#if (APP_SW == DEMO_APP)
  print_f("\n Callback function CanIf_CurrentIcomConfiguration is called!"); 
  print_f(" Error = %d \n", Error);
#endif
}

/*******************************************************************************
                    CanIf_TriggerTransmit
*******************************************************************************/
Std_ReturnType CanIf_TriggerTransmit(PduIdType TxPduId, 
                                            PduInfoType* PduInfoPtr)
{
#if (APP_SW == DEMO_APP)
  uint8  Data[8] = {0x19,0x29,0x39,0x49,0x59,0x69,0x79,0x89}; 
  if ((TxPduId == 20)||(TxPduId == 21)||(TxPduId == 22)||(TxPduId == 23))
  {
    PduInfoPtr->SduDataPtr = &Data[0];
    PduInfoPtr->SduLength =  8;
	print_f("\n Callback function CanIf_TriggerTransmit is called!\n");
	print_f("\n Data and Dlc is updated!\n");	
  }
#endif
 return(E_OK);
}

#endif /* #if (APP_SW != TEST_APP) */
 
void CanIf_CheckTrcvWakeFlagIndication(uint8 Transceiver)
{
}

void CanIf_TrcvModeIndication(uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode)
{

}

void CanIf_ConfirmPnAvailability(uint8 TransceiverId )
{

}

void CanIf_ClearTrcvWufFlagIndication(uint8 TransceiverId)
{

}

#define CAN_17_MCMCAN_STOP_SEC_CODE_QM_GLOBAL
#include "Can_17_McmCan_MemMap.h"

