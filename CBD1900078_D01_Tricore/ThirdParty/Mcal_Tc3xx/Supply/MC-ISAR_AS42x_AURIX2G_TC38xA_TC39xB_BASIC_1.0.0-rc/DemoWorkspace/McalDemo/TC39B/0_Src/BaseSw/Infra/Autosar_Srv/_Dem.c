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
**  FILENAME     : Dem.c                                                      **
**                                                                            **
**  VERSION      : 0.2.0                                                      **
**                                                                            **
**  DATE         : 2017-01-10                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Dem Driver source file                                     **
**                                                                            **
**  SPECIFICATION(S) : Specification of Dem Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Dem.h"
#if (APP_SW == DEMO_APP)
#include "Test_Print.h"
#endif /*#if (APP_SW == DEMO_APP)*/
#if (APP_SW == TEST_APP)
#include "Test_Dem.h"
#endif /*#if (APP_SW == TEST_APP)*/
/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/

/*****************************************************************************
 Dem_ReportErrorStatus

  Function name:  void Dem_ReportErrorStatus(Dem_EventIdType EventId, 
  Dem_EventStatusType EventStatus)

  Description:    This is only a function stub for Eg Application
  Parameter:
  Return value:
  Remarks:
*****************************************************************************/
void Dem_ReportErrorStatus(Dem_EventIdType EventId,
                       Dem_EventStatusType EventStatus)
{
  #if (APP_SW == DEMO_APP)
  if(DEM_EVENT_STATUS_FAILED == EventStatus)
  {
    print_f("\n DEM EVENT FAILED \n");
    print_f("EventId:%d", EventId);
  }
  #endif /*#if (APP_SW == DEMO_APP)*/

  #if (APP_SW == TEST_APP)
  Test_Dem_ReportErrorStatus((uint16)EventId, (uint8)EventStatus);
  #endif /*#if (APP_SW == TEST_APP)*/
}

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
