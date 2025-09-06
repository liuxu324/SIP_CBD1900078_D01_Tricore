/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2017)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : SchM_Gpt.h                                                 **
**                                                                            **
**  VERSION      : 2.0.0                                                      **
**                                                                            **
**  DATE         : 2018-04-11                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID=]                                          **
**                                                                            **
**  DESCRIPTION  : SchM file for Gpt driver                                   **
**                                                                            **
**  [/cover]                                                                  **
**  SPECIFICATION(S) : Specification of RTE, AUTOSAR Release 4.2.2            **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

#ifndef GPT_SCHM_H
#define GPT_SCHM_H
/* [cover parentID={E355F2BC-7460-4f60-A15F-D215408542D6}]
       tracing to SchM file
   [/cover] */
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
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
**                      Global Function Declarations                          **
*******************************************************************************/
/*******************************************************************************
** Syntax           : void SchM_Enter_Gpt_Get1UsPredefTimerValue(void)        **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
*******************************************************************************/
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
extern void SchM_Enter_Gpt_Get1UsPredefTimerValue(void);

/*******************************************************************************
** Syntax           : void SchM_Exit_Gpt_Get1UsPredefTimerValue(void)         **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Exits Module exclusive area                            **
**                                                                            **
*******************************************************************************/
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
extern void SchM_Exit_Gpt_Get1UsPredefTimerValue(void);

/*******************************************************************************
** Syntax           : void SchM_Enter_Gpt_Get100UsPredefTimerValue(void)      **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
*******************************************************************************/
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
extern void SchM_Enter_Gpt_Get100UsPredefTimerValue(void);

/*******************************************************************************
** Syntax           : void SchM_Exit_Gpt_Get100UsPredefTimerValue(void)       **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Exits Module exclusive area                             **
**                                                                            **
*******************************************************************************/
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
extern void SchM_Exit_Gpt_Get100UsPredefTimerValue(void);

#endif /* End of GPT_SCHM_H */
