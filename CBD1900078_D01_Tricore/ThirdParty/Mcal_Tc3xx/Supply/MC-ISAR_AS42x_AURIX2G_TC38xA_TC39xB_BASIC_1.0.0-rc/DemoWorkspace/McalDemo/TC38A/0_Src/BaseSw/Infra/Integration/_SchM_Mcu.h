/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2018)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : SchM_Mcu.h                                                 **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2018-02-12                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : SchM file for Mcu                                          **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
/*[cover parentID={A1BC5DF7-EB0E-4ac0-8284-9E803CF88735}][/cover]*/
#ifndef MCU_SCHM_H
#define MCU_SCHM_H

extern void SchM_Enter_Mcu_TomTgcReg(void);

extern void SchM_Exit_Mcu_TomTgcReg(void);

extern void SchM_Enter_Mcu_AtomAgcReg(void);

extern void SchM_Exit_Mcu_AtomAgcReg(void);

#endif /* MCU_SCHM_H */
