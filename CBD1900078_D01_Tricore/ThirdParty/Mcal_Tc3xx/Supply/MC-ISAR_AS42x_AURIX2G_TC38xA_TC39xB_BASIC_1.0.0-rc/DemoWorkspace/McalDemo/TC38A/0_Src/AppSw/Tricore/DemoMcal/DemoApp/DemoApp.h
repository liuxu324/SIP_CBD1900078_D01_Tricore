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
**  FILENAME  : DemoApp.h                                                     **
**                                                                            **
**  VERSION    : 0.0.2                                                        **
**                                                                            **
**  DATE       : 2017-03-07                                                   **
**                                                                            **
**  VARIANT    : NA                                                           **
**                                                                            **
**  PLATFORM   : Infineon AURIX2G                                             **
**                                                                            **
**  AUTHOR      : DL-AUTOSAR-Engineering                                      **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION : This file exports                                           **
**                - DemoApp Framework for MCAL driver Demo Applications       **
**                                                                            **
**  SPECIFICATION(S) :  NA                                                    **
**                                                                            **
**  MAY BE CHANGED BY USER [Yes/No]: Yes                                      **
*******************************************************************************/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#ifndef  DEMOAPP_H
#define  DEMOAPP_H

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
extern uint8 DemoApp_FlsInitDone; /* Flag to check FLS init is already called */

typedef void (*demo_fct_type) (void);

/* Definition of menu type */
typedef  struct DemoApp_FctListType
{
  const char    *fct_name;
  demo_fct_type fct_p;
  const char    *fct_desc;
} DemoApp_FctListType;

typedef  struct DemoApp_MenuType
{
  uint32    size;
  DemoApp_FctListType const *list;
} DemoApp_MenuType;

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
extern void DemoApp(void);
extern void DemoApp_Init(void);
 
#endif /* DEMOAPP_H */

