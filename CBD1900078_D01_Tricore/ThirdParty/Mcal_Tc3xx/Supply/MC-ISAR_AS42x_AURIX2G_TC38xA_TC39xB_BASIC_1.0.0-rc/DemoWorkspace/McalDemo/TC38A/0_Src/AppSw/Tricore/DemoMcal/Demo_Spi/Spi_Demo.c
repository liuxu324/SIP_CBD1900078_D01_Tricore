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
**  FILENAME   : Spi_Demo.c                                                  **
**                                                                           **
**  VERSION    : 0.0.1                                                       **
**                                                                           **
**  DATE       : 2016-09-14                                                  **
**                                                                           **
**  VARIANT    : NA                                                          **
**                                                                           **
**  PLATFORM   : Infineon AURIX2G                                            **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : This file contains                                         **                                        
**                - Demo application for SPI driver                          **                                        
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
*******************************************************************************/
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Spi_Demo.h"
#include "Test_Print.h"

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

extern const Spi_ConfigType Spi_Config;


/* IB Buffer used to load & Read data bytes for Write */
volatile Spi_DataBufferType  SpiWrite_Data_Buffer[20u];
volatile Spi_DataBufferType  SpiRead_Data_Buffer[20u];
static volatile uint8 QSPI_Transfer_Status = TRUE;

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/*******************************************************************************/
/******************************SPI-TestCases***********************************/
/*******************************************************************************/
/*******************************************************************************                                       
** Syntax : void Spi_Demo (void)                                              **                                       
**                                                                            **                                       
** Service ID   : NA                                                          **                                       
**                                                                            **                                       
** Sync/Async   : Synchronous                                                 **                                       
**                                                                            **                                       
** Reentrancy   : Non Reentrant                                               **                                       
**                                                                            **                                       
** Parameters (in): none                                                      **                                       
**                                                                            **                                       
** Parameters (out): none                                                     **                                       
**                                                                            **                                       
** Return value: none                                                         **                                       
**                                                                            **                                       
** Description : DemoApp for SPI driver                                       **                                       
**                                                                            **                                       
*******************************************************************************/                                       
void Spi_Demo(void)                                                                                           
{                                                                                                                      
  char szString[80];                                                                                                   
  volatile uint8 TempUSage = 0;  
  
  uint8 QSPI_Transfer_Result = 0U;
  Spi_Init(&Spi_Config);

  while (!TempUSage)                                                                                                   
  {                                                                                                                    
    print_f("\n\n\n");                                                                                                 
    print_f("\n/*********************************************************/\n");                                        
    print_f("\n                SPI DRIVER DEMOAPP MENU                   \n ");                                        
    print_f("\n                                                          \n ");                                        
    print_f("     1.  Transfer 8-bit data from QSPI0 using sequence 0    \n ");                                                                            
    print_f("     x.  Back To Main Menu                                  \n ");                                        
    print_f("                                                            \n ");                                        
    print_f("\n/*********************************************************/\n");                                        
    print_f("  Enter Your Option :: ");                                                                                
                                                                                                                       
    getline(szString, sizeof szString - 1);                                                                            
                                                                                                                       
    switch (*szString)                                                                                                 
    {                                                                                                                  
       case '1':                                                                                                       
       {                  
           QSPI_Transfer_Result = Spi_Synch_Demo();  
           if(QSPI_Transfer_Result == FALSE){
           print_f("\n QSPI Synch Mode Communication Failure \n");
        
			StartResult();
			print_f("Result = FAIL;");
			EndResult();
           }
           else
           {
              print_f("\n QSPI Synch Mode Communication Success \n");
			StartResult();
			print_f("Result = PASS;");
			EndResult();
           }		   
           break;                                                                                                      
       }                                                                                                                                                                                                                            
       case 'x':                                                                                                       
       case 'X':                                                                                                       
         TempUSage = 1;                                                                                                
         break;                                                                                                        
       default :                                                                                                       
         print_f(" \n\n Invalid option \n ");
		StartResult();
        print_f("Result = Fail;");
        EndResult();
       break;                                                                                                          
    }    	
  }                                                                                                                    
}/* SPI_Demo() */
/*******************************************************************************
** Syntax       : uint8 Spi_Synch_Demo(void)                                        **
**                                                                            **
** Service ID   : NA                                                          **
**                                                                            **
** Sync/Async   : Synchronous                                                 **
**                                                                            **
** Reentrancy   : Non Reentrant                                               **
**                                                                            **
** Parameters (in) : none                                                     **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Timing          :                                                          **
**                                                                            **
** Description : This routine will start the SPI configured for sequence ID 0 **
**               Transmit mode     : Synchronous                              **
**               LevelDelivered    : 00                                       **
**               External Devices  : QSPI0                                    **
**               CS Selection      : CS_VIA_PERIPHERAL_ENGINE                 **
**               QSPI0 Pins used   : P20.08(CS-0),P20.13(SCLK),P20.14(MTSR)    **
**                                   P20.12(MRTS)                             **
*******************************************************************************/
uint8 Spi_Synch_Demo(void)
{
  /* volatile uint8 TestResult = 1U;*/
   volatile uint8 Transmit_Data_incr;
   volatile uint8 Receive_Data_incr;
   QSPI_Transfer_Status = TRUE;
   print_f ("\n Internal data buffer transmitted on QSPI0 : \n");
   for(Transmit_Data_incr = 0; Transmit_Data_incr < 20; Transmit_Data_incr++){
      SpiWrite_Data_Buffer[Transmit_Data_incr] = Transmit_Data_incr;
      print_f ("\n Write IB[%d] : %d \n ",Transmit_Data_incr,SpiWrite_Data_Buffer[Transmit_Data_incr]);
   }

   Spi_WriteIB(SpiConf_SpiChannel_SpiChannel_0,(uint8 *) &SpiWrite_Data_Buffer[0u]);
   Spi_WriteIB(SpiConf_SpiChannel_SpiChannel_1,(uint8 *) &SpiWrite_Data_Buffer[10u]);

   Spi_SyncTransmit(SpiConf_SpiSequence_SpiSequence_0);
   while(Spi_GetSequenceResult(SpiConf_SpiSequence_SpiSequence_0) != SPI_SEQ_OK)
   {
         /* Wait till write is finished */
   }
   Spi_ReadIB(SpiConf_SpiChannel_SpiChannel_0,(uint8 *)&SpiRead_Data_Buffer[0u]);
   Spi_ReadIB(SpiConf_SpiChannel_SpiChannel_1,(uint8 *)&SpiRead_Data_Buffer[10u]);
   
   print_f ("\n Internal data buffer Received on QSPI0 : \n");
   /* Evaluate the Recieved Buffer data */   
   for(Receive_Data_incr = 0; Receive_Data_incr < 20; Receive_Data_incr++){
      print_f ("\n ReadIB[%d] : %d \n ",Receive_Data_incr,SpiRead_Data_Buffer[Receive_Data_incr]);
     if(SpiRead_Data_Buffer[Receive_Data_incr] != SpiWrite_Data_Buffer[Receive_Data_incr])
     {
       QSPI_Transfer_Status = FALSE;
        break;
     }
   }
   //Spi_DeInit();
   return QSPI_Transfer_Status;

}




