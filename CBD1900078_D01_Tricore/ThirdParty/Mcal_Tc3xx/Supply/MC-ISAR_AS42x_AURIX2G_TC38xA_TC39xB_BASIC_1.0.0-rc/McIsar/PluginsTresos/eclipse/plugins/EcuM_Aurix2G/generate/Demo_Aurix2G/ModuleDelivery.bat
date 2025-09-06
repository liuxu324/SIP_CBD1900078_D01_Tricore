[!/*****************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2016)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : ModuleDelivery.bat                                            **
**                                                                            **
**  VERSION   : 0.0.1                                                         **
**                                                                            **
**  DATE      : 2016-09-02                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : NA                                                **
**                                                                            **
**  VARIANT   : Post-Build                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Code template for ModuleDelivery.bat file                  **
**                                                                            **
**  SPECIFICATION(S) :  NA                                                    **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: No                                       **
**                                                                            **
*******************************************************************************/

*************************************************************************/!][!//
@ECHO OFF
REM ****************************************************************************
REM *                                                                         **
REM * Copyright (C) Infineon Technologies (2016)                              **
REM *                                                                         **
REM * All rights reserved.                                                    **
REM *                                                                         **
REM * This document contains proprietary information belonging to Infineon    **
REM * Technologies. Passing on and copying of this document, and communication**
REM * of its contents is not permitted without prior written authorization.   **
REM *                                                                         **
REM ****************************************************************************
REM *                                                                         **
REM *  FILENAME  : ModuleDelivery.bat                                         **
REM *                                                                         **
REM *  VERSION   : 0.0.1                                                      **
REM *                                                                         **
REM *  DATE,TIME : [!"$date"!], [!"$time"!]                                   **
REM *                                                                         **
REM *  VARIANT   : Post-Build                                                 **
REM *                                                                         **
REM *  PLATFORM  : Infineon AURIX2G                                           **
REM *                                                                         **
REM *  AUTHOR    : DL-AUTOSAR-Engineering                                     **
REM *                                                                         **
REM *  VENDOR    : Infineon Technologies                                      **
REM *                                                                         **
REM *  DESCRIPTION  : This file creates the Demo Modules that are delivered.  **
REM *                                                                         **
REM *  MAY BE CHANGED BY USER [yes/no]: YES                                   **
REM *                                                                         **
REM ***************************************************************************/
[!NOCODE!]
[!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//

[!VAR "McuModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('Mcu')[1]"!][!//
[!VAR "McuModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//

[!VAR "PortModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('Port')[1]"!][!//
[!VAR "PortModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//

[!VAR "DioModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('Dio')[1]"!][!//
[!VAR "DioModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//

[!VAR "GptModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('Gpt')[1]"!][!//
[!VAR "GptModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//

[!VAR "SpiModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('Spi')[1]"!][!//
[!VAR "SpiModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//

[!VAR "PwmModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('Pwm')[1]"!][!//
[!VAR "PwmModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//

[!VAR "AdcModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('Adc')[1]"!][!//
[!VAR "AdcModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//

[!VAR "DsadcModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('Dsadc')[1]"!][!//
[!VAR "DsadcModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//
[!VAR "DmaModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('Dma')[1]"!][!//
[!VAR "DmaModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//

[!VAR "FeeModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('Fee')[1]"!][!//
[!VAR "FeeModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//

[!VAR "FlsModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('Fls')[1]"!][!//
[!VAR "FlsModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//

[!VAR "IcuModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('Icu')[1]"!][!//
[!VAR "IcuModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//

[!VAR "CanModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('Can')[1]"!][!//
[!VAR "CanModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//

[!VAR "FrModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('Fr')[1]"!][!//
[!VAR "FrModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//

[!VAR "EthModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('Eth')[1]"!][!//
[!VAR "EthModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//

[!VAR "WdgModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('Wdg')[1]"!][!//
[!VAR "WdgModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//

[!VAR "MscModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('Msc')[1]"!][!//
[!VAR "MscModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//

[!VAR "CrcModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('Crc')[1]"!][!//
[!VAR "CrcModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//

[!VAR "LinModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('Lin')[1]"!][!//
[!VAR "LinModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//

[!VAR "HsslModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('Hssl')[1]"!][!//
[!VAR "HsslModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//

[!VAR "SentModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('Sent')[1]"!][!//
[!VAR "SentModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//

[!VAR "FlsLdrModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('FlsLoader')[1]"!][!//
[!VAR "FlsLdrModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//

[!VAR "I2cModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('I2c')[1]"!][!//
[!VAR "I2cModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//

[!VAR "UartModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('Uart')[1]"!][!//
[!VAR "UartModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//

[!VAR "SmuModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('Smu')[1]"!][!//
[!VAR "SmuModuleUsed" = "'STD_ON'"!][!//
[!ENDSELECT!][!//

[!ENDNOCODE!]
SET MCU_DEMO_EN=[!"$McuModuleUsed"!]
SET PORT_DEMO_EN=[!"$PortModuleUsed"!]
SET DIO_DEMO_EN=[!"$DioModuleUsed"!]
SET GPT_DEMO_EN=[!"$GptModuleUsed"!]
SET SPI_DEMO_EN=[!"$SpiModuleUsed"!]
SET PWM_DEMO_EN=[!"$PwmModuleUsed"!]
SET ADC_DEMO_EN=[!"$AdcModuleUsed"!]
SET DSADC_DEMO_EN=[!"$DsadcModuleUsed"!]
SET DMA_DEMO_EN=[!"$DmaModuleUsed"!]
SET FEE_DEMO_EN=[!"$FeeModuleUsed"!]
SET FLS_DEMO_EN=[!"$FlsModuleUsed"!]
SET ICU_DEMO_EN=[!"$IcuModuleUsed"!]
SET CAN_DEMO_EN=[!"$CanModuleUsed"!]
SET FR_DEMO_EN=[!"$FrModuleUsed"!]
SET ETH_DEMO_EN=[!"$EthModuleUsed"!]
SET WDG_DEMO_EN=[!"$WdgModuleUsed"!]
SET MSC_DEMO_EN=[!"$MscModuleUsed"!]
SET CRC_DEMO_EN=[!"$CrcModuleUsed"!]
SET LIN_DEMO_EN=[!"$LinModuleUsed"!]
SET HSSL_DEMO_EN=[!"$HsslModuleUsed"!]
SET SENT_DEMO_EN=[!"$SentModuleUsed"!]
SET FLSLDR_DEMO_EN=[!"$FlsLdrModuleUsed"!]
SET SMU_DEMO_EN=[!"$SmuModuleUsed"!]
SET I2C_DEMO_EN=[!"$I2cModuleUsed"!]
SET UART_DEMO_EN=[!"$UartModuleUsed"!]