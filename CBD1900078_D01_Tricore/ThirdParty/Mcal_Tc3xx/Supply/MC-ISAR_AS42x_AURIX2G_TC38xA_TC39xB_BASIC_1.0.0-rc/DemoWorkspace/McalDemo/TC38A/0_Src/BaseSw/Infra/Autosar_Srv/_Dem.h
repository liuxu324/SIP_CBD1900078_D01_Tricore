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
**  FILENAME     : Dem.h                                                      **
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
**  DESCRIPTION  : DEM Driver header definition file                          **
**                                                                            **
**  SPECIFICATION(S) : Specification of DEM Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

#ifndef _DEM_H
#define _DEM_H

/*******************************************************************************
**                      Includes
*******************************************************************************/
#include "Std_Types.h"
#include "Dem_cfg.h"
#if (APP_SW == TEST_APP)
#include "Test_Dem.h"
#endif /* #if (APP_SW == TEST_APP) */
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
#define DEM_AR_RELEASE_MAJOR_VERSION 4U
#define DEM_AR_RELEASE_MINOR_VERSION 2U

#define DEM_EVENT_STATUS_PASSED    ((Dem_EventStatusType)0x00)
#define DEM_EVENT_STATUS_FAILED    ((Dem_EventStatusType)0x01)
#define DEM_EVENT_STATUS_PREPASSED ((Dem_EventStatusType)0x02)
#define DEM_EVENT_STATUS_PREFAILED ((Dem_EventStatusType)0x03)

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
typedef uint16 Dem_EventIdType;
typedef uint8 Dem_EventStatusType;

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
extern void Dem_ReportErrorStatus ( Dem_EventIdType EventId,\
                                      Dem_EventStatusType EventStatus);
#endif /* end of _DEM_H */
