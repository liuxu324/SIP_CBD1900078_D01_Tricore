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
**  FILENAME   : DemoApp_Cfg.h                                                **
**                                                                            **
**  DATE       : 2016-09-02                                                   **
**                                                                            **
**  VARIANT   : Post-Build                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Code template for DemoApp_Cfg.h file                       **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: No                                       **
**                                                                            **
*************************************************************************/!][!//
[!// 
/*******************************************************************************
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
**   FILENAME   : DemoApp_Cfg.h                                               **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                                          **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                                            **
**                                                                            **
**  VARIANT   : Post-Build                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : DemoApp configuration generated out of Tresos configuration**
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                      **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#ifndef  DEMOAPP_CFG_H
#define  DEMOAPP_CFG_H

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/************************* Demo Application Configuration *********************/

[!NOCODE!]
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

[!VAR "IrqModuleUsed" = "'STD_OFF'"!][!//
[!SELECT "as:modconf('Irq')[1]"!][!//
[!VAR "IrqModuleUsed" = "'STD_ON'"!][!//
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

#define MCU_DEMO_EN                   ([!"$McuModuleUsed"!])
#define PORT_DEMO_EN                  ([!"$PortModuleUsed"!])
#define DIO_DEMO_EN                   ([!"$DioModuleUsed"!])
#define GPT_DEMO_EN                   ([!"$GptModuleUsed"!])
#define SPI_DEMO_EN                   ([!"$SpiModuleUsed"!])
#define PWM_DEMO_EN                   ([!"$PwmModuleUsed"!])
#define ADC_DEMO_EN                   ([!"$AdcModuleUsed"!])
#define DSADC_DEMO_EN                 ([!"$DsadcModuleUsed"!])
#define DMA_DEMO_EN                   ([!"$DmaModuleUsed"!])
/* Note that the FLS Delivery must be ON if FEE is ON */
#define FEE_DEMO_EN                   ([!"$FeeModuleUsed"!])
#define FLS_DEMO_EN                   ([!"$FlsModuleUsed"!])
#define ICU_DEMO_EN                   ([!"$IcuModuleUsed"!])
#define CAN_DEMO_EN                   ([!"$CanModuleUsed"!])
#define FR_DEMO_EN                    ([!"$FrModuleUsed"!])
#define ETH_DEMO_EN                   ([!"$EthModuleUsed"!])
#define WDG_DEMO_EN                   ([!"$WdgModuleUsed"!])
#define MSC_DEMO_EN                   ([!"$MscModuleUsed"!])
#define CRC_DEMO_EN                   ([!"$CrcModuleUsed"!])
#define LIN_DEMO_EN                   ([!"$LinModuleUsed"!])
#define HSSL_DEMO_EN                  ([!"$HsslModuleUsed"!])
#define SENT_DEMO_EN                  ([!"$SentModuleUsed"!])
#define FLSLDR_DEMO_EN                ([!"$FlsLdrModuleUsed"!])
#define IRQ_DEMO_EN                   ([!"$IrqModuleUsed"!])
#define I2C_DEMO_EN                   ([!"$I2cModuleUsed"!])
#define UART_DEMO_EN                   ([!"$UartModuleUsed"!])
#define SMU_DEMO_EN                  ([!"$SmuModuleUsed"!])

#endif /* DEMOAPP_CFG_H */
