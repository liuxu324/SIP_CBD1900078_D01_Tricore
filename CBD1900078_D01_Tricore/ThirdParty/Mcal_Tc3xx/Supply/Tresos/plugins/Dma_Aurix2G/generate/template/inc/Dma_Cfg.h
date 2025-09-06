[!/*****************************************************************************
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
**  FILENAME  : Dma_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 3.0.0                                                         **
**                                                                            **
**  DATE      : 2018-08-08                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : NA                                                **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID= {2E029066-ABA2-42ec-8228-7DAF01A03B0F}]   **
**                                                                            **
**  DESCRIPTION  : Code template header file for Dma Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!][!//
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
**  FILENAME  : Dma_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 3.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                                      **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                                          **
**                                                                            **
**  BSW MODULE DECRIPTION : NA                                                **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Dma configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

[!NOCODE!][!//
    [!INCLUDE "Dma.m"!][!//
[!ENDNOCODE!][!//
#ifndef DMA_CFG_H
#define DMA_CFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/* Include the McalLib header */
#include "McalLib_Cfg.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Dma')[1]"!][!//
[!//
[!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
[!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
[!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//

/* AUTOSAR specification version numbers */
/* [cover parentID={40CCE8CD-73D5-44c6-8370-F659C1A56ABD}]
DMA_AR_RELEASE_MAJOR_VERSION
[/cover] */
/* [cover parentID={CF5151EF-73C2-40af-BC84-20167F6C2EDB}]
DMA_AR_RELEASE_MINOR_VERSION
[/cover] */
/* [cover parentID={2BBA264E-605D-4a4f-9477-4C4F87931E68}]
DMA_AR_RELEASE_REVISION_VERSION
[/cover] */
[!IF "$MajorVersion = num:i(4)"!][!//
#define DMA_AR_RELEASE_MAJOR_VERSION        ([!"$MajorVersion"!]U)
#define DMA_AR_RELEASE_MINOR_VERSION        ([!"$MinorVersion"!]U)
#define DMA_AR_RELEASE_REVISION_VERSION     ([!"$RevisionVersion"!]U)
[!ENDIF!][!//
[!//
[!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
[!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
[!VAR "SwRevisionVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//

/*SW Version Information*/
/* [cover parentID={60DF11D7-94B0-4b23-B422-7FE28D556787}]
DMA_SW_MAJOR_VERSION
[/cover] */
/* [cover parentID={72B5A76B-8621-42f1-AC66-D18D21F086AF}]
DMA_SW_MINOR_VERSION
[/cover] */
/* [cover parentID={8737518F-C058-4265-B186-EF33C18D403C}]
DMA_SW_PATCH_VERSION
[/cover] */
#define DMA_SW_MAJOR_VERSION                ([!"$SwMajorVersion"!]U)
#define DMA_SW_MINOR_VERSION                ([!"$SwMinorVersion"!]U)
#define DMA_SW_PATCH_VERSION                ([!"$SwRevisionVersion"!]U)

/*Number of DMA channels present in the controller*/
/* [cover pparentID={A02B4E43-1406-49a7-8E03-D631ED6393E1}]
DMA_MAX_NUM_OF_CHANNELS
[/cover] */
#define DMA_MAX_NUM_OF_CHANNELS             ([!"ecu:get('Dma.MaxDmaChannel')"!]U)


/* Derived Configuration for DmaDevErrorDetect */
/*
Configuration: DMA_DEV_ERROR_DETECT
Preprocessor switch for enabling the development error detection and
reporting.
- if STD_ON, DET is Enabled
- if STD_OFF,DET is Disabled
*/
/* [cover parentID={7AB95133-DBBB-49fd-913E-CE67BDD9B492}]
DMA_DEV_ERROR_DETECT
[/cover] */
#define DMA_DEV_ERROR_DETECT                ([!//
[!IF "DmaGeneral/DmaDevErrorDetect = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)


/* Configuration: DMA_CHDEINIT_API
Deinit API configuration
- if STD_ON, Dma_ChDeInit API is available
- if STD_OFF, Dma_ChDeInit API is not available
*/
/* [cover parentID={B4288CCC-24CC-483e-AEB4-6E0F74DB4B19}]
DMA_CHDEINIT_API
[/cover] */
#define DMA_CHDEINIT_API                    ([!//
[!IF "DmaGeneral/DmaDeinitApiConfiguration = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/* Configuration: DMA_SUSPEND_API
Suspend and freeze API configuration
- if STD_ON, Dma_ChTransferFreeze and Dma_ChTransferResume APIs are available
- if STD_OFF, Dma_ChTransferFreeze and Dma_ChTransferResume APIs are not
              available
*/
/* [cover parentID={74E1D4AB-F716-4619-826F-31B9A0C41D80}]
DMA_SUSPEND_API
[/cover] */
#define DMA_SUSPEND_API                     ([!//
[!IF "DmaGeneral/DmaSuspendApiConfiguration = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/* Configuration: DMA_TRIGGER_API
Channel hardware trigger API configuration
- if STD_ON, Dma_ChEnableHardwareTrigger and Dma_ChDisableHardwareTrigger APIs
             are available
- if STD_OFF, Dma_ChEnableHardwareTrigger and Dma_ChDisableHardwareTrigger APIs
             are not available
*/
/* [cover parentID={E7799D5F-670D-43df-B25E-06FF48229C23}]
DMA_TRIGGER_API
[/cover] */
#define DMA_TRIGGER_API                     ([!//
[!IF "DmaGeneral/DmaTriggerApiConfiguration = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/* Configuration: DMA_DATA_PENDING_API
Get remaining data API configuration
- if STD_ON, Dma_ChGetRemainingData API is available
- if STD_OFF, Dma_ChGetRemainingData API is not available
*/
/* [cover parentID={E296EFD7-A8D9-4b8e-82DB-86F106D97ABB}]
DMA_DATA_PENDING_API
[/cover] */
#define DMA_DATA_PENDING_API                ([!//
[!IF "DmaGeneral/DmaDataPendingApiConfiguration = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/* Configuration: DMA_BUFFER_SWITCH_API
Buffer Switch API configuration
- if STD_ON, Dma_ChSwitchBuffer API is available
- if STD_OFF, Dma_ChSwitchBuffer API is not available
*/
/* [cover parentID={FA7482A2-4409-4e56-80AE-B45E388D4F9F}]
DMA_BUFFER_SWITCH_API
[/cover] */
#define DMA_BUFFER_SWITCH_API               ([!//
[!IF "DmaGeneral/DmaBufferSwitchApiConfiguration = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/* Configuration: DMA_GETVERSIONINFO_API
Version Information API configuration
- if STD_ON, Dma_GetVersionInfo API is available
- if STD_OFF, Dma_GetVersionInfo API is not available
*/
/* [cover parentID={19352A23-55BC-4b78-90F5-47815F96C79A}]
DMA_GETVERSIONINFO_API
[/cover] */
#define DMA_GETVERSIONINFO_API               ([!//
[!IF "DmaGeneral/DmaVersionInfoApi = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)


/* Maximum number of transaction set allowed on a DMA channel in case
   of linked list
*/
/* [cover parentID={2187C834-E665-4db0-99A6-8AA5DB9AA087}]
DMA_MAX_TRANSACTION_SET_PER_CHANNEL
[/cover] */
#define DMA_MAX_TRANSACTION_SET_PER_CHANNEL ([!//
[!"node:value(DmaGeneral/DmaMaxTransactionSetPerChannel)"!]U)[!//

[!NOCODE!][!//
[!VAR "Dma_DoubleBufferControl" = "'STD_OFF'"!]
[!VAR "LinkListEnable" = "'STD_OFF'"!][!//
[!VAR "NoOfDmaChannels" = "num:i(count(DmaChannelConfig/*))"!][!//
[!VAR "ChannelIndex" = "num:i(0)"!][!//
[!FOR "ChannelIndex" = "0" TO "num:i($NoOfDmaChannels) -1"!][!//
    [!SELECT "DmaChannelConfig/*[@index=$ChannelIndex]"!][!//
        [!VAR "NoOfTCS" = "num:i(count(DmaChannelTransactionSet/*))"!][!//
        [!VAR "ChannelTcsIndex" = "num:i(0)"!][!//
        [!FOR "ChannelTcsIndex" = "0" TO "num:i($NoOfTCS) -1"!][!//
            [!SELECT "DmaChannelTransactionSet/*[@index=$ChannelTcsIndex]"!][!//
                [!CALL "Dma_DoubleBufferConfig", "ShadowMode"="DmaTcsShadowRegisterConfiguration","Dma_DoubleBufferControl" ="$Dma_DoubleBufferControl"!][!//
                [!IF "text:contains(node:value(DmaTcsShadowRegisterConfiguration),'LINK') = 'true'"!][!//
                    [!VAR "LinkListEnable" = "'STD_ON'"!][!//
                [!ENDIF!][!//
            [!ENDSELECT!][!//
        [!ENDFOR!][!//
    [!ENDSELECT!][!//
[!ENDFOR!][!//
[!ENDNOCODE!][!//


/* configuration for DMA_LINKED_LIST_ENABLE
- if STD_ON, Any channel has more than one TCS
- if STD_OFF, None of the DMA channel has more than one TCS
*/

#define DMA_LINKED_LIST_ENABLE              ([!"$LinkListEnable"!])

/* configuration for DMA_DOUBLE_BUFFER_ENABLE
- if STD_ON, Any DMA channel has Double buffer configuration
- if STD_OFF, None of the DMA channel has Double buffer configuration
*/
/* [cover parentID={18C5B46C-0D0E-48b2-B9E6-1225E057A522}]
DMA_DOUBLE_BUFFER_ENABLE
[/cover] */
#define DMA_DOUBLE_BUFFER_ENABLE            ([!"$Dma_DoubleBufferControl"!])

/* No of DMA channels used in the configuration */
/* [cover parentID={0D41BBBC-A58F-4caf-B254-6241838765EA}]
DMA_NUM_OF_CHANNELS
[/cover] */
#define DMA_NUM_OF_CHANNELS                 ([!"$NoOfDmaChannels"!]U)


/* ******************** USER/SUPERVISOR MODE CONFIGURATIONS ***************** */

#define DMA_MCAL_SUPERVISORMODE (0U)
#define DMA_MCAL_USER1MODE      (1U)

/* Configuration: DMA_INIT_API_MODE
Mode selection for the Init and Deinit APIs
- if DMA_MCAL_SUPERVISORMODE, the init and deinit functions should be
  running in the supervisor mode
- if DMA_MCAL_USER1MODE, the init and deinit functions should be running in the
  user1 mode
*/
/* [cover parentID={109A2A0C-FAD5-46d6-8640-09FB91EE6147}]
DMA_INIT_API_MODE
[/cover] */
#define DMA_INIT_API_MODE       ([!"node:value(DmaGeneral/DmaInitApiMode)"!])

/* Configuration: DMA_RUNTIME_API_MODE
Mode selection for the Runtime APIs
- if DMA_MCAL_SUPERVISORMODE, the Runtime functions should be running in the
  supervisor mode
- if DMA_MCAL_USER1MODE, the Runtime functions should be running in the
  user1 mode
*/
/* [cover parentID={6E3C8B08-0002-434f-B6E8-F4F6F61A496F}]
DMA_RUNTIME_API_MODE
[/cover] */
#define DMA_RUNTIME_API_MODE    ([!"node:value(DmaGeneral/DmaRuntimeApiMode)"!])
/* ************************************************************************** */


/* ************************ MULTICORE CONFIGURATIONS ************************ */

/* Derived Configuration for DmaMultiCoreErrorDetect */
/*
Configuration: DMA_MULTICORE_ERROR_DETECT
Preprocessor switch for enabling the multicore error checks and error reporting.
- if STD_ON, multicore error checks are Enabled
- if STD_OFF, multicore error checks are Disabled
*/
/* [cover parentID={6A6168FB-F0C0-4a19-8AC6-7BBD2FEA1914}]
DMA_MULTICORE_ERROR_DETECT
[/cover] */

#define DMA_MULTICORE_ERROR_DETECT          ([!//
[!IF "DmaGeneral/DmaMultiCoreErrorDetect = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

[!INDENT "0"!][!//
    [!NOCODE!][!//
        [!/* Get all the core and channel mappings from the Resource Manager */!][!//
        [!CALL "Dma_CG_GenerateModuleMap", "Module"="'DMA'"!][!//
        /* Configuration for the number of channels allocated per core */
        [!VAR "MasterCoreNumber" = "num:i(0)"!][!//
        [!/* Get the number of the core configured as the master core */!][!//
        [!CALL "Dma_CG_GetMasterCoreNumber", "MasterCoreNumber" = "num:i(0)"!][!//
        [!VAR "NoOfUnassignedChannels" = "num:i(0)"!][!//
        [!/* Get the number of unallocated channels, which eventually goes to the master core */!][!//
        [!CALL "Dma_CG_GetNoOfUnallocatedChannels", "NoOfUnassignedChannels" = "num:i(0)"!][!//
        [!FOR "ChannelCoreIndex" = "num:i(0)" TO "num:i(ecu:get('McalLib.NoOfCoreAvailable')) - num:i(1)"!][!//
            [!VAR "AllocationTotalCount" = "num:i(0)"!][!//
            [!CALL "Dma_CG_GetResourceNumbers", "LocalCoreId"="$ChannelCoreIndex", "AllocationTotalCount" = "''"!][!//
            [!CODE!][!//
                /* Total number of DMA channels in core [!"$ChannelCoreIndex"!] */
                [!/* Assigned channels = [!"num:i($AllocationTotalCount)"!], Unassigned channels = [!"num:i($NoOfUnassignedChannels)"!] */!][!//
                #define DMA_ALLOCATED_CHANNELS_CORE[!"$ChannelCoreIndex"!] [!//
                [!IF "$ChannelCoreIndex = $MasterCoreNumber"!][!//
                    ([!"num:i(num:i($AllocationTotalCount) + num:i($NoOfUnassignedChannels))"!]U)
                [!ELSE!][!//
                    ([!"num:i($AllocationTotalCount)"!]U)
                [!ENDIF!][!//
            [!ENDCODE!][!//
        [!ENDFOR!][!//
    [!ENDNOCODE!][!//
[!ENDINDENT!][!//

/* ************************************************************************** */


/* *************************** SAFETY CONFIGURATIONS ************************ */

/* Derived Configuration for DmaSafetyEnable */
/*
Configuration: DMA_SAFETY_ENABLE
Preprocessor switch for enabling the safety checks and error reporting.
- if STD_ON, Safety checks are Enabled
- if STD_OFF,Safety checks are Disabled
*/
/* [cover parentID={513EAA68-EE91-45a0-9556-76A5DDF1CD8E}]
DMA_SAFETY_ENABLE
[/cover] */
#define DMA_SAFETY_ENABLE                   ([!//
[!IF "DmaGeneral/DmaSafetyEnable = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/* Configuration: DMA_INITCHECK_API
Init check API configuration
- if STD_ON,  Dma_InitCheck API is available
- if STD_OFF, Dma_InitCheck API is not available
*/
/* [cover parentID={CFB33CEC-75DF-451b-AD5F-3B89E2032BF7}]
DMA_INITCHECK_API
[/cover] */
#define DMA_INITCHECK_API                   ([!//
[!IF "DmaGeneral/DmaInitCheckApi  = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)
/* ************************************************************************** */

[!ENDSELECT!][!//
#endif  /* DMA_CFG_H */


