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
**  FILENAME   : Spi_Demo.h                                                  **
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
**  DESCRIPTION : This file exports                                          **                                        
**                - Demo application for SPI driver                          **                                        
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

#ifndef TEST_SPI_H
#define TEST_SPI_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Std_Types.h"
#include "Spi.h"
#include "Spi_Cfg.h"
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
/*******************************************************************************
** Syntax          : void Spi_Demo(void)                                      **
**                                                                            **
** Service ID:     : NA                                                       **
**                                                                            **
** Sync/Async:     : Synchronous                                              **
**                                                                            **
** Reentrancy:     : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : none                                                     **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Timing          :                                                          **
**                                                                            **
** Description : This routine will start the SPI configured for sequence ID 2 **
**               Transmit mode     : Synchronous                              **
**               BUffer used       : IB                                       **
**               Data Width        : 8 bits                                   **
**               Data Bytes        : 4                                        **
**               Jobs used         : 0 (QSPI0),1 (QSPI0)                      **
**               Channel used      : 0,1,2,3                                  **
**               QSPI0 Pins used   : P20.9(CS),P20.14(MTSR),P20.11(CLK)       **
**                                   P20.12(MRTS)                             **
**               Transmision stops once data is transferred                   **
**               Data to be observed on scope                                 **
*******************************************************************************/

extern void Spi_Demo(void);
extern uint8 Spi_Synch_Demo(void);
#endif

 /* TEST_SPI_H */
