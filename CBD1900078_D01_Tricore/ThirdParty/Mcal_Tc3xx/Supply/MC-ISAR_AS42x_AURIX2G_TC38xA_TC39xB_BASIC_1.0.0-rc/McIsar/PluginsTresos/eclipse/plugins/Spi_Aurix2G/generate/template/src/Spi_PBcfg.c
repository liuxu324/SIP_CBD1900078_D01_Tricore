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
**  FILENAME  : Spi_PBCfg.c                                                   **
**                                                                            **
**  VERSION   : 8.0.0                                                         **
**                                                                            **
**  DATE      : 2018-09-03                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Spi.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={A21E0696-390A-464f-BBA4-63B0BA6AD221}]    **
**                                                                            **
**  DESCRIPTION  : Code template source file for Spi Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Spi Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!]
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
**  FILENAME  : Spi_PBCfg.c                                                   **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                                      **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                                          **
**                                                                            **
**  BSW MODULE DECRIPTION : Spi.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Spi configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Spi Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
[!AUTOSPACING!]
[!NOCODE!]
[!INCLUDE "..\Spi_checks.m"!]
[!ENDNOCODE!]

[!//[cover parentID={F2776BA9-87CC-4a88-897C-B7A8CEFC60CE}] Dependent module check[/cover][!//

[!IF "not(node:exists(as:modconf('ResourceM')[1]))"!]
  [!ERROR!][!//
    SPI Code Generator: ResourceM module is not added to the project.
  [!ENDERROR!][!//
[!ENDIF!]

[!IF "not(node:exists(as:modconf('Mcu')[1]))"!]
  [!ERROR!][!//
    SPI Code Generator: Mcu module is not added to the project.
  [!ENDERROR!][!//
[!ENDIF!]

[!IF "(SpiGeneral/SpiLevelDelivered = num:i(1)) or (SpiGeneral/SpiLevelDelivered = num:i(2))"!]
[!IF "not(node:exists(as:modconf('Dma')[1]))"!]
  [!ERROR!][!//
    SPI Code Generator: Dma module is not added to the project.
  [!ENDERROR!][!//
[!ENDIF!]
[!ENDIF!]

[!//
[!VAR "VariantsConfigured" = "num:i(0)"!]
[!SELECT "as:modconf('EcuC')[1]"!][!//
[!IF "node:exists(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!][!//
[!VAR "PredefinedVarName1" = "(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!]
[!VAR "PredefinedVarName2" = "substring-after($PredefinedVarName1, "/")"!][!//
[!VAR "PredefinedVarName3" = "substring-after($PredefinedVarName2, "/")"!][!//
[!VAR "PredefinedVarName" = "substring-after($PredefinedVarName3, "/")"!][!//
[!VAR "VariantsConfigured" = "num:i(1)"!]
[!ENDIF!][!//
[!ENDSELECT!]
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Spi')[1]"!][!//

/* Module header file */
#include "Spi.h"

/*******************************************************************************
**                      Private Macro definition                              **
*******************************************************************************/
/* MISRA2012_RULE_4_9_JUSTIFICATION: More readble as macros. Code coplexity
reduces as well. */
#define Spi_BaudRateAndClockParam(TQ,LB,Q,A,B,C,CPH,CPOL,PAREN)                \
            (                                                                  \
             (uint32)(                                                         \
                      ((uint32)TQ << 16U)|((uint32)LB << 30U)|((uint32)Q)|\
                      ((uint32)A << 6U)|((uint32)B << 8U)|         \
                      ((uint32)C << 10U)|((uint32)CPH << 12U)|        \
                      ((uint32)CPOL << 13U)|((uint32)PAREN << 14U)     \
                     )                                                         \
            )

/* MISRA2012_RULE_4_9_JUSTIFICATION: More readble as macros. Code coplexity
reduces as well. */
#define Spi_IdleLeadTrailParam(IPRE,IDLE,LPRE,LEAD,TPRE,TRAIL,PARTYP)          \
            (                                                                  \
             (uint32)(                                                         \
                       ((uint32)IPRE << 1U)|((uint32)IDLE << 4U)|    \
                       ((uint32)LPRE << 7U)|((uint32)LEAD << 10U)|   \
                       ((uint32)TPRE << 13U)|((uint32)TRAIL << 16U)| \
                       ((uint32)PARTYP << 19U)            \
                     )                                                         \
            )

/*******************************************************************************
**                      Extern Declaration                                    **
*******************************************************************************/
[!VAR "Spi_MaxCore" = "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!]
[!VAR "Spi_MasterCallBackSeqLstNum" = "''"!]
[!IF "(SpiGeneral/SpiLevelDelivered = num:i(1)) or (SpiGeneral/SpiLevelDelivered = num:i(2))"!]
   [!LOOP "SpiDriver/SpiSequence/*"!]
     [!IF "node:exists(./SpiSeqEndNotification/*[1])"!]
       [!IF "not(num:isnumber(./SpiSeqEndNotification/*[1])) and (./SpiSeqEndNotification/*[1] != 'NULL_PTR')"!]
        [!IF "not(text:contains(text:split($Spi_MasterCallBackSeqLstNum,','),node:value(./SpiSeqEndNotification/*[1])))"!]
/* Notification function for Sequence: [!"node:name(.)"!] */
extern void [!"./SpiSeqEndNotification/*[1]"!](void);
[!VAR "Spi_MasterCallBackSeqLstNum" = "concat($Spi_MasterCallBackSeqLstNum,node:value(./SpiSeqEndNotification/*[1]),',')"!]
         [!ENDIF!]
       [!ENDIF!]
     [!ENDIF!]
   [!ENDLOOP!]
[!ENDIF!]

[!VAR "Spi_MasterCallBackJobLstNum" = "''"!][!//
[!IF "(SpiGeneral/SpiLevelDelivered = num:i(1)) or (SpiGeneral/SpiLevelDelivered = num:i(2))"!]
   [!LOOP "SpiDriver/SpiJob/*"!]
     [!IF "node:exists(./SpiJobEndNotification/*[1])"!]
       [!IF "not(num:isnumber(./SpiJobEndNotification/*[1])) and (./SpiJobEndNotification/*[1] != 'NULL_PTR')"!]
          [!IF "not(text:contains(text:split($Spi_MasterCallBackJobLstNum,','),node:value(./SpiJobEndNotification/*[1])))"!]
/* Notification function for Job: [!"node:name(.)"!] */
extern void [!"./SpiJobEndNotification/*[1]"!](void);
[!VAR "Spi_MasterCallBackJobLstNum" = "concat($Spi_MasterCallBackJobLstNum,node:value(./SpiJobEndNotification/*[1]),',')"!]
         [!ENDIF!]
       [!ENDIF!]
     [!ENDIF!]
   [!ENDLOOP!]
[!ENDIF!]


/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/******************* GLOBAL CONFIGURATION MEMMAP SECTION *********************/

[!//[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}][/cover][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
[!// [cover parentID={6BEDAB1C-42FE-45bd-9F5A-F8B6F8C123B7}]Sequence config[/cover][!//
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"
[!//
[!//getting core id
[!CALL "Spi_CGGenerateModuleMap", "Module" = "'SPI'"!][!//
[!CALL "Spi_CGGetCore"!][!//
[!//
[!//
[!/* Store Symbolic names for Sequences in variables */!][!//
[!CALL "Spi_CGStoreSequence_ID"!][!//
[!//
[!// Spi_CGCoreConfig macro generates a List {,1,1,1,0,0,0} where position 1 to 6 represents Core0 to Core5 and if it is configured to use any QSPI then it is 1 else 0
[!CALL "Spi_CGStoreCoreConfig"!][!//
[!//
[!/* Store Symbolic names for Jobs in variables */!][!//
[!CALL "Spi_CGStoreJob_ID"!][!//
[!//
[!/* Store Symbolic names for Jobs in variables */!][!//
[!CALL "Spi_CGStoreChannel_ID"!][!//
[!//
/*Sequence Index Lookup*/
[!CALL "Spi_CGGenerateSequenceIndexMapping"!][!//

/*Job Index Lookup*/
[!CALL "Spi_CGGenerateJobIndexMapping"!]

/*Channel Index Lookup*/
[!CALL "Spi_CGGenerateChannelIndexMapping"!]

/* Linked list for the Job[s] assigned to the sequence[s] Physical*/
[!LOOP "SpiDriver/SpiSequence/*"!]
[!//[cover parentID={C925CB51-AC28-4aed-BF87-A12053A0E032}][/cover][!//
static const Spi_JobType [!"node:name(.)"!]_JobLinkPtr_Physical[] =
{
  [!LOOP "./SpiJobAssignment/*"!]
  [!VAR "Spi_seqJobIndex" = "num:i(node:value(node:ref(.)/SpiJobId))"!][!//
  [!"text:split($Spi_JobPhysicalIndex,',')[position() = $Spi_seqJobIndex + 2]"!]U,        /* Physical index value for Job [!"node:name(node:ref(.))"!] Job ID [!"num:i(node:value(node:ref(.)/SpiJobId))"!] */
[!// Generating macro name as per all job assigned for each sequence
  [!ENDLOOP!]
  SPI_JOB_DELIMITER
};
[!ENDLOOP!]

/* Linked list for the channel[s] assigned to the job[s] Physical */
[!LOOP "SpiDriver/SpiJob/*"!]
[!//[cover parentID={61F7392A-2970-45ea-8DB6-B9C6E719DF9B}][/cover][!//
static const Spi_ChannelType [!"node:name(.)"!]_ChannelLinkPtr_Physical[] =
{
  [!LOOP "node:order(./SpiChannelList/*,'node:value(./SpiChannelIndex)')"!]
  [!VAR "Spi_jobChannelIndex" = "num:i((node:ref(./SpiChannelAssignment)/SpiChannelId))"!][!//
  [!"text:split($Spi_ChannelPhysicalIndex,',')[position() = $Spi_jobChannelIndex + 2]"!]U,        /* Physical index value for Channel [!"node:name(node:ref(./SpiChannelAssignment))"!] Channel ID [!"num:i(node:value(node:ref(./SpiChannelAssignment)/SpiChannelId))"!] */
  [!// Generating macro name as per all channel assigned for each job
  [!ENDLOOP!]
  SPI_CHANNEL_DELIMITER
};
[!ENDLOOP!][!//

[!IF "SpiGeneral/SpiLevelDelivered != num:i(0)"!][!//
/* Linked list of sequence[s] with Job[s] shared  */
[!LOOP "SpiDriver/SpiSequence/*"!]
static const Spi_SequenceType [!"node:name(.)"!]_SeqSharePtr[] =
{
[!CALL "Spi_CGGetSharedSequence","Spi_OutSequence" = "node:name(.)"!][!//
  SPI_SEQUENCE_DELIMITER
};
[!ENDLOOP!]
[!ENDIF!][!//

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"

/******************* GLOBAL CONFIGURATION MEMMAP SECTION *********************/

[!// For each core
[!FOR "CPU_ID" = "0" TO "num:i($Spi_MaxCore)"!][!//
[!// checking if core is enabled only then generate configuration for that core
[!IF "text:split($Core_config,',')[position() = $CPU_ID + num:i(1)] = num:i(1)"!] [!//
/******************* CORE[!"num:i($CPU_ID)"!] SEQUENCE CONFIGURATION MEMMAP SECTION *************/

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($CPU_ID)"!]_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"

[!//[cover parentID={CF32DE49-EF29-41a1-AC72-29A95B503000}][/cover][!//
static const Spi_SequenceConfigType Spi_kSequenceConfig_Core[!"num:i($CPU_ID)"!][] =
{
[!/* Generate Sequence configuration */!][!//
[!CALL "Spi_CGGenerateSequenceConfig", "CPUID" = "$CPU_ID"!]
};

[!//[cover parentID={F8C3E17E-D343-488d-9C9D-75899C97A304}][/cover][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($CPU_ID)"!]_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"

/***************** CORE[!"num:i($CPU_ID)"!] SEQUENCE CONFIGURATION MEMMAP SECTION END *************/
[!ENDIF!][!//
[!ENDFOR!][!//
[!FOR "CPU_ID" = "0" TO "num:i($Spi_MaxCore)"!][!//
[!// checking if core is enabled only then generate configuration for that core
[!IF "text:split($Core_config,',')[position() = $CPU_ID + num:i(1)] = num:i(1)"!][!//
/******************* CORE[!"num:i($CPU_ID)"!] JOB CONFIGURATION MEMMAP SECTION *************/

[!//[cover parentID={5EEF6E44-E1AE-4667-AF88-365ADB178C4E}][/cover][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($CPU_ID)"!]_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"

static const Spi_JobConfigType Spi_kJobConfig_Core[!"num:i($CPU_ID)"!][] =
{
[!/* Generate Job configuration */!][!//
[!CALL "Spi_CGGenerateJobConfig","CPUID" = "$CPU_ID"!]

};

[!//[cover parentID={9D294F20-6464-4121-BF5D-B79867B7D473}][/cover][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($CPU_ID)"!]_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"

/***************** CORE[!"num:i($CPU_ID)"!] JOB CONFIGURATION MemMap SECTION END *************/
[!ENDIF!][!//
[!ENDFOR!][!//
[!FOR "CPU_ID" = "0" TO "num:i($Spi_MaxCore)"!][!//
[!// checking if core is enabled only then generate configuration for that core
[!IF "text:split($Core_config,',')[position() = $CPU_ID + num:i(1)] = num:i(1)"!]
/******************* CORE[!"num:i($CPU_ID)"!] CHANNEL CONFIGURATION MEMMAP SECTION *************/

[!//[cover parentID={0E2EEC03-AD55-4c36-ADC5-59029C66101A}][/cover][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($CPU_ID)"!]_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"

[!//[cover parentID={3060237C-37EE-4045-9D4C-9CAA1EAFCD59}][/cover][!//
static const Spi_ChannelConfigType Spi_kChannelConfig_Core[!"num:i($CPU_ID)"!][] =
{
[!/* Generate Channel configuration */!][!//
[!CALL "Spi_CGGenerateChnlConfig","CPUID" = "$CPU_ID"!][!//

};

[!//[cover parentID={CDDCBC8A-96ED-46b0-B87A-B026097A60F2}][/cover][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($CPU_ID)"!]_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"

/***************** CORE[!"num:i($CPU_ID)"!] JOB CONFIGURATION MemMap SECTION END *************/
[!ENDIF!][!//
[!ENDFOR!][!//
[!// Spi_CGKernelCoreConfig macro will generate a list {,1,0,2,2,255,255} where position 1 to 6 represents each QSPI instance and numbers on that postion represents CpuId for respective QSPI
[!CALL "Spi_CGStoreKernelCoreConfig"!]
[!CALL "Spi_CGIsQSPIzUsed"!][!//
[!FOR "QSPICPU_ID1" = "0" TO "num:i($Spi_MaxCore)"!][!//
[!//
[!IF "$Spi_MacQspi0Used = num:i(1)"!][!//
[!/* QSPI0 */!][!//
[!IF "text:split($QSPICore_config,',')[position() = num:i(1)] = $QSPICPU_ID1"!]

/******************* CORE[!"num:i($QSPICPU_ID1)"!] QSPI0 CONFIGURATION MEMMAP SECTION *************/

[!//[cover parentID={9FF6E853-3CF5-439b-B15F-E8B4BBBBAED1}][/cover][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($QSPICPU_ID1)"!]_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"

[!CALL "Spi_CGGenerateQspix","Spi_OutQSPIx" = "'QSPI0'"!][!//

[!//[cover parentID={CC2E83A7-738C-4ef1-B051-4DC1E6C6AC23}][/cover][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($QSPICPU_ID1)"!]_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"

/***************** CORE[!"num:i($QSPICPU_ID1)"!] QSPI0 CONFIGURATION MemMap SECTION END *************/
[!ENDIF!]
[!ENDIF!][!//

[!IF "$Spi_MacQspi1Used = num:i(1)"!][!//
[!/* QSPI1 */!][!//
[!IF "text:split($QSPICore_config,',')[position() = num:i(2)] = $QSPICPU_ID1"!]
/******************* CORE[!"num:i($QSPICPU_ID1)"!] QSPI1 CONFIGURATION MEMMAP SECTION *************/

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($QSPICPU_ID1)"!]_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"

[!CALL "Spi_CGGenerateQspix","Spi_OutQSPIx" = "'QSPI1'"!][!//

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($QSPICPU_ID1)"!]_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"

/***************** CORE[!"num:i($QSPICPU_ID1)"!] QSPI1 CONFIGURATION MemMap SECTION END *************/
[!ENDIF!]
[!ENDIF!][!//

[!IF "$Spi_MacQspi2Used = num:i(1)"!][!//
[!/* QSPI2 */!][!//
[!IF "text:split($QSPICore_config,',')[position() = num:i(3)] = $QSPICPU_ID1"!]
/******************* CORE[!"num:i($QSPICPU_ID1)"!] QSPI2 CONFIGURATION MEMMAP SECTION *************/

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($QSPICPU_ID1)"!]_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"

[!CALL "Spi_CGGenerateQspix","Spi_OutQSPIx" = "'QSPI2'"!][!//

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($QSPICPU_ID1)"!]_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"

/***************** CORE[!"num:i($QSPICPU_ID1)"!] QSPI2 CONFIGURATION MemMap SECTION END *************/
[!ENDIF!]
[!ENDIF!][!//

[!IF "$Spi_MacQspi3Used = num:i(1)"!][!//
[!/* QSPI3 */!][!//
[!IF "text:split($QSPICore_config,',')[position() = num:i(4)] = $QSPICPU_ID1"!]
/******************* CORE[!"num:i($QSPICPU_ID1)"!] QSPI3 CONFIGURATION MEMMAP SECTION *************/

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($QSPICPU_ID1)"!]_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"

[!CALL "Spi_CGGenerateQspix","Spi_OutQSPIx" = "'QSPI3'"!][!//

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($QSPICPU_ID1)"!]_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"

/***************** CORE[!"num:i($QSPICPU_ID1)"!] QSPI3 CONFIGURATION MemMap SECTION END *************/
[!ENDIF!]
[!ENDIF!][!//

[!IF "$Spi_MacQspi4Used = num:i(1)"!][!//
[!/* QSPI4 */!][!//
[!IF "text:split($QSPICore_config,',')[position() = num:i(5)] = $QSPICPU_ID1"!]
/******************* CORE[!"num:i($QSPICPU_ID1)"!] QSPI4 CONFIGURATION MEMMAP SECTION *************/

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($QSPICPU_ID1)"!]_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"

[!CALL "Spi_CGGenerateQspix","Spi_OutQSPIx" = "'QSPI4'"!][!//

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($QSPICPU_ID1)"!]_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"

/***************** CORE[!"num:i($QSPICPU_ID1)"!] QSPI4 CONFIGURATION MemMap SECTION END *************/
[!ENDIF!]
[!ENDIF!][!//

[!IF "$Spi_MacQspi5Used = num:i(1)"!][!//
[!/* QSPI5 */!][!//
[!IF "text:split($QSPICore_config,',')[position() = num:i(6)] = $QSPICPU_ID1"!]
/******************* CORE[!"num:i($QSPICPU_ID1)"!] QSPI5 CONFIGURATION MEMMAP SECTION *************/

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($QSPICPU_ID1)"!]_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"


[!CALL "Spi_CGGenerateQspix","Spi_OutQSPIx" = "'QSPI5'"!][!//


/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($QSPICPU_ID1)"!]_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"

/***************** CORE[!"num:i($QSPICPU_ID1)"!] QSPI5 CONFIGURATION MemMap SECTION END *************/
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//

[!FOR "CPU_ID" = "0" TO "num:i($Spi_MaxCore)"!][!//
[!IF "text:split($Core_config,',')[position() = $CPU_ID + num:i(1)] = num:i(1)"!][!//
/********************CORE[!"num:i($CPU_ID)"!] RX/TX BUFFERS MEMMAP SECTION***********************/

[!//[cover parentID={540AA5A3-0D26-4d64-8455-1CEDEE02099E}][/cover][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($CPU_ID)"!]_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"
/* Lookup table to hold the offset in buffer and total elements to be transferred for all IB channels.
Index - Represents channel number, 1st element - Offset in buffer, 2nd element - Total elements to be transmitted */

[!//[cover parentID={894976AB-984A-435a-B31F-A23D4828D556}][/cover][!//
static const Spi_CoreChannelOffsetType Spi_ChannelOffsets_Core[!"num:i($CPU_ID)"!][SPI_NUM_IB_CHANNELS_CORE[!"num:i($CPU_ID)"!] +  SPI_NUM_EB_CHANNELS_CORE[!"num:i($CPU_ID)"!] + 1U] =
{
[!VAR "Spi_offSet" = "num:i(0)"!]
[!IF "text:split($QSPICore_config,',')[position() = 1] = $CPU_ID"!][!//
[!//
[!//
[!IF "$Spi_ChnlSyncQSPI0Count != 0"!][!//
[!FOR "Spi_LoopCntr" = "$Spi_ChnlSyncQSPI0Count" TO "num:i(1)" STEP "-1"!][!//
[!VAR "Spi_ChannlNamePointer" = "text:split($Spi_ChnlSyncQSPI0,',')[position() = $Spi_LoopCntr]"!][!//
  {[!"num:i($Spi_offSet)"!], [!"node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiIbNBuffers'))"!]},  /* for IB channels [!"$Spi_ChannlNamePointer"!]  */
/* Get the Channel Width */
[!VAR "Spi_Width" = "node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiDataWidth'))"!][!//
[!IF "$Spi_Width >= num:i(2) and $Spi_Width <= num:i(8)"!][!//
[!VAR "Spi_Width" = "num:i(8)"!][!//
[!ELSEIF "$Spi_Width >= num:i(9) and $Spi_Width <= num:i(16)"!][!//
[!VAR "Spi_Width" = "num:i(16)"!][!//
[!ELSE!][!//
[!VAR "Spi_Width" = "num:i(32)"!][!//
[!ENDIF!][!//
[!VAR "Spi_offSet0" = "$Spi_Width div num:i(8)"!][!//

[!VAR "Spi_offSet0" = "$Spi_offSet0 * node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiIbNBuffers'))"!][!//
[!IF "$Spi_offSet0 mod num:i(4) != num:i(0)"!][!//
[!VAR "Spi_offSet0" = "$Spi_offSet0 + (num:i(4) - ($Spi_offSet0 mod num:i(4)))"!][!//
[!ENDIF!][!//
[!VAR "Spi_offSet" = "$Spi_offSet + $Spi_offSet0"!]
[!ENDFOR!][!//
[!ELSE!][!//
[!FOR "Spi_LoopCntr" = "$Spi_ChnlAsyncQSPI0Count" TO "num:i(1)" STEP "-1"!][!//
[!VAR "Spi_ChannlNamePointer" = "text:split($Spi_ChnlAsyncQSPI0,',')[position() = $Spi_LoopCntr]"!][!//
  {[!"num:i($Spi_offSet)"!], [!"node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiIbNBuffers'))"!]},  /* for IB channels [!"$Spi_ChannlNamePointer"!] */
[!VAR "Spi_Width" = "node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiDataWidth'))"!][!//
[!IF "$Spi_Width >= num:i(2) and $Spi_Width <= num:i(8)"!][!//
[!VAR "Spi_Width" = "num:i(8)"!][!//
[!ELSEIF "$Spi_Width >= num:i(9) and $Spi_Width <= num:i(16)"!][!//
[!VAR "Spi_Width" = "num:i(16)"!][!//
[!ELSE!][!//
[!VAR "Spi_Width" = "num:i(32)"!][!//
[!ENDIF!][!//
[!VAR "Spi_offSet0" = "$Spi_Width div num:i(8)"!][!//
[!VAR "Spi_offSet0" = "$Spi_offSet0 * node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiIbNBuffers'))"!][!//
[!IF "$Spi_offSet0 mod num:i(4) != num:i(0)"!][!//
[!VAR "Spi_offSet0" = "$Spi_offSet0 + (num:i(4) - ($Spi_offSet0 mod num:i(4)))"!][!//
[!ENDIF!][!//
[!VAR "Spi_offSet" = "$Spi_offSet + $Spi_offSet0"!]
[!ENDFOR!][!//
[!ENDIF!][!//
[!//
[!ENDIF!][!//
[!//
[!IF "text:split($QSPICore_config,',')[position() = 2] = $CPU_ID"!][!//
[!//
[!//
[!IF "$Spi_ChnlSyncQSPI1Count != 0"!][!//
[!FOR "Spi_LoopCntr" = "$Spi_ChnlSyncQSPI1Count" TO "num:i(1)" STEP "-1"!][!//
[!VAR "Spi_ChannlNamePointer" = "text:split($Spi_ChnlSyncQSPI1,',')[position() = $Spi_LoopCntr]"!][!//
  {[!"num:i($Spi_offSet)"!], [!"node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiIbNBuffers'))"!]},  /* for IB channels [!"$Spi_ChannlNamePointer"!] */
/* Get the Channel Width */
[!VAR "Spi_Width" = "node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiDataWidth'))"!][!//
[!IF "$Spi_Width >= num:i(2) and $Spi_Width <= num:i(8)"!][!//
[!VAR "Spi_Width" = "num:i(8)"!][!//
[!ELSEIF "$Spi_Width >= num:i(9) and $Spi_Width <= num:i(16)"!][!//
[!VAR "Spi_Width" = "num:i(16)"!][!//
[!ELSE!][!//
[!VAR "Spi_Width" = "num:i(32)"!][!//
[!ENDIF!][!//
[!VAR "Spi_offSet1" = "$Spi_Width div num:i(8)"!][!//

[!VAR "Spi_offSet1" = "$Spi_offSet1 * node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiIbNBuffers'))"!][!//
[!IF "$Spi_offSet1 mod num:i(4) != num:i(0)"!][!//
[!VAR "Spi_offSet1" = "$Spi_offSet1 + (num:i(4) - ($Spi_offSet1 mod num:i(4)))"!][!//
[!ENDIF!][!//
[!VAR "Spi_offSet" = "$Spi_offSet + $Spi_offSet1"!]
[!ENDFOR!][!//
[!ELSE!][!//
[!FOR "Spi_LoopCntr" = "$Spi_ChnlAsyncQSPI1Count" TO "num:i(1)" STEP "-1"!][!//
[!VAR "Spi_ChannlNamePointer" = "text:split($Spi_ChnlAsyncQSPI1,',')[position() = $Spi_LoopCntr]"!][!//
  {[!"num:i($Spi_offSet)"!], [!"node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiIbNBuffers'))"!]},  /* for IB channels [!"$Spi_ChannlNamePointer"!] */
/* Get the Channel Width */
[!VAR "Spi_Width" = "node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiDataWidth'))"!][!//
[!IF "$Spi_Width >= num:i(2) and $Spi_Width <= num:i(8)"!][!//
[!VAR "Spi_Width" = "num:i(8)"!][!//
[!ELSEIF "$Spi_Width >= num:i(9) and $Spi_Width <= num:i(16)"!][!//
[!VAR "Spi_Width" = "num:i(16)"!][!//
[!ELSE!][!//
[!VAR "Spi_Width" = "num:i(32)"!][!//
[!ENDIF!][!//
[!VAR "Spi_offSet1" = "$Spi_Width div num:i(8)"!][!//
[!VAR "Spi_offSet1" = "$Spi_offSet1 * node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiIbNBuffers'))"!][!//
[!IF "$Spi_offSet1 mod num:i(4) != num:i(0)"!][!//
[!VAR "Spi_offSet1" = "$Spi_offSet1 + (num:i(4) - ($Spi_offSet1 mod num:i(4)))"!][!//
[!ENDIF!][!//
[!VAR "Spi_offSet" = "$Spi_offSet + $Spi_offSet1"!]
[!ENDFOR!][!//
[!ENDIF!][!//[!//
[!ENDIF!][!//
[!//
[!IF "text:split($QSPICore_config,',')[position() = 3] = $CPU_ID"!][!//
[!//
[!//
[!IF "$Spi_ChnlSyncQSPI2Count != 0"!][!//
[!FOR "Spi_LoopCntr" = "$Spi_ChnlSyncQSPI2Count" TO "num:i(1)" STEP "-1"!][!//
[!VAR "Spi_ChannlNamePointer" = "text:split($Spi_ChnlSyncQSPI2,',')[position() = $Spi_LoopCntr]"!][!//
  {[!"num:i($Spi_offSet)"!], [!"node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiIbNBuffers'))"!]},  /* for IB channels [!"$Spi_ChannlNamePointer"!] */
/* Get the Channel Width */
[!VAR "Spi_Width" = "node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiDataWidth'))"!][!//
[!IF "$Spi_Width >= num:i(2) and $Spi_Width <= num:i(8)"!][!//
[!VAR "Spi_Width" = "num:i(8)"!][!//
[!ELSEIF "$Spi_Width >= num:i(9) and $Spi_Width <= num:i(16)"!][!//
[!VAR "Spi_Width" = "num:i(16)"!][!//
[!ELSE!][!//
[!VAR "Spi_Width" = "num:i(32)"!][!//
[!ENDIF!][!//
[!VAR "Spi_offSet2" = "$Spi_Width div num:i(8)"!][!//
[!VAR "Spi_offSet2" = "$Spi_offSet2 * node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiIbNBuffers'))"!][!//
[!IF "$Spi_offSet2 mod num:i(4) != num:i(0)"!][!//
[!VAR "Spi_offSet2" = "$Spi_offSet2 + (num:i(4) - ($Spi_offSet2 mod num:i(4)))"!][!//
[!ENDIF!][!//
[!VAR "Spi_offSet" = "$Spi_offSet + $Spi_offSet2"!]
[!ENDFOR!][!//
[!ELSE!][!//
[!FOR "Spi_LoopCntr" = "$Spi_ChnlAsyncQSPI2Count" TO "num:i(1)" STEP "-1"!][!//
[!VAR "Spi_ChannlNamePointer" = "text:split($Spi_ChnlAsyncQSPI2,',')[position() = $Spi_LoopCntr]"!][!//
  {[!"num:i($Spi_offSet)"!], [!"node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiIbNBuffers'))"!]},  /* for IB channels [!"$Spi_ChannlNamePointer"!] */
/* Get the Channel Width */
[!VAR "Spi_Width" = "node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiDataWidth'))"!][!//
[!IF "$Spi_Width >= num:i(2) and $Spi_Width <= num:i(8)"!][!//
[!VAR "Spi_Width" = "num:i(8)"!][!//
[!ELSEIF "$Spi_Width >= num:i(9) and $Spi_Width <= num:i(16)"!][!//
[!VAR "Spi_Width" = "num:i(16)"!][!//
[!ELSE!][!//
[!VAR "Spi_Width" = "num:i(32)"!][!//
[!ENDIF!][!//
[!VAR "Spi_offSet2" = "$Spi_Width div num:i(8)"!][!//
[!VAR "Spi_offSet2" = "$Spi_offSet2 * node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiIbNBuffers'))"!][!//
[!IF "$Spi_offSet2 mod num:i(4) != num:i(0)"!][!//
[!VAR "Spi_offSet2" = "$Spi_offSet2 + (num:i(4) - ($Spi_offSet2 mod num:i(4)))"!][!//
[!ENDIF!][!//
[!VAR "Spi_offSet" = "$Spi_offSet + $Spi_offSet2"!]
[!ENDFOR!][!//
[!ENDIF!][!//
[!//
[!ENDIF!][!//
[!//
[!IF "text:split($QSPICore_config,',')[position() = 4] = $CPU_ID"!][!//
[!//
[!//
[!IF "$Spi_ChnlSyncQSPI3Count != 0"!][!//
[!FOR "Spi_LoopCntr" = "$Spi_ChnlSyncQSPI3Count" TO "num:i(1)" STEP "-1"!][!//
[!VAR "Spi_ChannlNamePointer" = "text:split($Spi_ChnlSyncQSPI3,',')[position() = $Spi_LoopCntr]"!][!//
  {[!"num:i($Spi_offSet)"!], [!"node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiIbNBuffers'))"!]},  /* for IB channels [!"$Spi_ChannlNamePointer"!] */
/* Get the Channel Width */
[!VAR "Spi_Width" = "node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiDataWidth'))"!][!//
[!IF "$Spi_Width >= num:i(2) and $Spi_Width <= num:i(8)"!][!//
[!VAR "Spi_Width" = "num:i(8)"!][!//
[!ELSEIF "$Spi_Width >= num:i(9) and $Spi_Width <= num:i(16)"!][!//
[!VAR "Spi_Width" = "num:i(16)"!][!//
[!ELSE!][!//
[!VAR "Spi_Width" = "num:i(32)"!][!//
[!ENDIF!][!//
[!VAR "Spi_offSet3" = "$Spi_Width div num:i(8)"!][!//
[!VAR "Spi_offSet3" = "$Spi_offSet3 * node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiIbNBuffers'))"!][!//
[!IF "$Spi_offSet3 mod num:i(4) != num:i(0)"!][!//
[!VAR "Spi_offSet3" = "$Spi_offSet3 + (num:i(4) - ($Spi_offSet3 mod num:i(4)))"!][!//
[!ENDIF!][!//
[!VAR "Spi_offSet" = "$Spi_offSet + $Spi_offSet3"!]
[!ENDFOR!][!//
[!ELSE!][!//
[!FOR "Spi_LoopCntr" = "$Spi_ChnlAsyncQSPI3Count" TO "num:i(1)" STEP "-1"!][!//
[!VAR "Spi_ChannlNamePointer" = "text:split($Spi_ChnlAsyncQSPI3,',')[position() = $Spi_LoopCntr]"!][!//
  {[!"num:i($Spi_offSet)"!], [!"node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiIbNBuffers'))"!]},  /* for IB channels [!"$Spi_ChannlNamePointer"!] */
/* Get the Channel Width */
[!VAR "Spi_Width" = "node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiDataWidth'))"!][!//
[!IF "$Spi_Width >= num:i(2) and $Spi_Width <= num:i(8)"!][!//
[!VAR "Spi_Width" = "num:i(8)"!][!//
[!ELSEIF "$Spi_Width >= num:i(9) and $Spi_Width <= num:i(16)"!][!//
[!VAR "Spi_Width" = "num:i(16)"!][!//
[!ELSE!][!//
[!VAR "Spi_Width" = "num:i(32)"!][!//
[!ENDIF!][!//
[!VAR "Spi_offSet3" = "$Spi_Width div num:i(8)"!][!//
[!VAR "Spi_offSet3" = "$Spi_offSet3 * node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiIbNBuffers'))"!][!//
[!IF "$Spi_offSet3 mod num:i(4) != num:i(0)"!][!//
[!VAR "Spi_offSet3" = "$Spi_offSet3 + (num:i(4) - ($Spi_offSet3 mod num:i(4)))"!][!//
[!ENDIF!][!//
[!VAR "Spi_offSet" = "$Spi_offSet + $Spi_offSet3"!]
[!ENDFOR!][!//
[!ENDIF!][!//
[!//
[!ENDIF!][!//
[!//
[!IF "text:split($QSPICore_config,',')[position() = 5] = $CPU_ID"!][!//
[!//
[!//
[!IF "$Spi_ChnlSyncQSPI4Count != 0"!][!//
[!FOR "Spi_LoopCntr" = "$Spi_ChnlSyncQSPI4Count" TO "num:i(1)" STEP "-1"!][!//
[!VAR "Spi_ChannlNamePointer" = "text:split($Spi_ChnlSyncQSPI4,',')[position() = $Spi_LoopCntr]"!][!//
  {[!"num:i($Spi_offSet)"!], [!"node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiIbNBuffers'))"!]},  /* for IB channels [!"$Spi_ChannlNamePointer"!] */
/* Get the Channel Width */
[!VAR "Spi_Width" = "node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiDataWidth'))"!][!//
[!IF "$Spi_Width >= num:i(2) and $Spi_Width <= num:i(8)"!][!//
[!VAR "Spi_Width" = "num:i(8)"!][!//
[!ELSEIF "$Spi_Width >= num:i(9) and $Spi_Width <= num:i(16)"!][!//
[!VAR "Spi_Width" = "num:i(16)"!][!//
[!ELSE!][!//
[!VAR "Spi_Width" = "num:i(32)"!][!//
[!ENDIF!][!//
[!VAR "Spi_offSet4" = "$Spi_Width div num:i(8)"!][!//
[!VAR "Spi_offSet4" = "$Spi_offSet4 * node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiIbNBuffers'))"!][!//
[!IF "$Spi_offSet4 mod num:i(4) != num:i(0)"!][!//
[!VAR "Spi_offSet4" = "$Spi_offSet4 + (num:i(4) - ($Spi_offSet4 mod num:i(4)))"!][!//
[!ENDIF!]
[!VAR "Spi_offSet" = "$Spi_offSet + $Spi_offSet4"!]
[!ENDFOR!][!//
[!ELSE!][!//
[!FOR "Spi_LoopCntr" = "$Spi_ChnlAsyncQSPI4Count" TO "num:i(1)" STEP "-1"!][!//
[!VAR "Spi_ChannlNamePointer" = "text:split($Spi_ChnlAsyncQSPI4,',')[position() = $Spi_LoopCntr]"!]
  {[!"num:i($Spi_offSet)"!], [!"node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiIbNBuffers'))"!]},  /* for IB channels [!"$Spi_ChannlNamePointer"!] */
/* Get the Channel Width */
[!VAR "Spi_Width" = "node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiDataWidth'))"!][!//
[!IF "$Spi_Width >= num:i(2) and $Spi_Width <= num:i(8)"!][!//
[!VAR "Spi_Width" = "num:i(8)"!][!//
[!ELSEIF "$Spi_Width >= num:i(9) and $Spi_Width <= num:i(16)"!][!//
[!VAR "Spi_Width" = "num:i(16)"!][!//
[!ELSE!][!//
[!VAR "Spi_Width" = "num:i(32)"!][!//
[!ENDIF!][!//
[!VAR "Spi_offSet4" = "$Spi_Width div num:i(8)"!][!//
[!VAR "Spi_offSet4" = "$Spi_offSet4 * node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiIbNBuffers'))"!]
[!IF "$Spi_offSet4 mod num:i(4) != num:i(0)"!]
[!VAR "Spi_offSet4" = "$Spi_offSet4 + (num:i(4) - ($Spi_offSet4 mod num:i(4)))"!]
[!ENDIF!][!//
[!VAR "Spi_offSet" = "$Spi_offSet + $Spi_offSet4"!]
[!ENDFOR!][!//
[!ENDIF!][!//
[!//
[!ENDIF!][!//
[!//
[!IF "text:split($QSPICore_config,',')[position() = 6] = $CPU_ID"!][!//
[!//
[!//
[!IF "$Spi_ChnlSyncQSPI5Count != 0"!][!//
[!FOR "Spi_LoopCntr" = "$Spi_ChnlSyncQSPI5Count" TO "num:i(1)" STEP "-1"!][!//
[!VAR "Spi_ChannlNamePointer" = "text:split($Spi_ChnlSyncQSPI5,',')[position() = $Spi_LoopCntr]"!][!//
  {[!"num:i($Spi_offSet)"!], [!"node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiIbNBuffers'))"!]},  /* for IB channels [!"$Spi_ChannlNamePointer"!] */
/* Get the Channel Width */
[!VAR "Spi_Width" = "node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiDataWidth'))"!][!//
[!IF "$Spi_Width >= num:i(2) and $Spi_Width <= num:i(8)"!][!//
[!VAR "Spi_Width" = "num:i(8)"!][!//
[!ELSEIF "$Spi_Width >= num:i(9) and $Spi_Width <= num:i(16)"!][!//
[!VAR "Spi_Width" = "num:i(16)"!][!//
[!ELSE!][!//
[!VAR "Spi_Width" = "num:i(32)"!][!//
[!ENDIF!][!//
[!VAR "Spi_offSet5" = "$Spi_Width div num:i(8)"!][!//
[!VAR "Spi_offSet5" = "$Spi_offSet5 * node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiIbNBuffers'))"!][!//
[!IF "$Spi_offSet5 mod num:i(4) != num:i(0)"!][!//
[!VAR "Spi_offSet5" = "$Spi_offSet5 + (num:i(4) - ($Spi_offSet5 mod num:i(4)))"!][!//
[!ENDIF!][!//
[!VAR "Spi_offSet" = "$Spi_offSet + $Spi_offSet5"!]
[!ENDFOR!][!//
[!ELSE!][!//
[!FOR "Spi_LoopCntr" = "$Spi_ChnlAsyncQSPI5Count" TO "num:i(1)" STEP "-1"!][!//
[!VAR "Spi_ChannlNamePointer" = "text:split($Spi_ChnlAsyncQSPI5,',')[position() = $Spi_LoopCntr]"!][!//
  {[!"num:i($Spi_offSet)"!], [!"node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiIbNBuffers'))"!]},  /* for IB channels [!"$Spi_ChannlNamePointer"!] */
/* Get the Channel Width */
[!VAR "Spi_Width" = "node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiDataWidth'))"!][!//
[!IF "$Spi_Width >= num:i(2) and $Spi_Width <= num:i(8)"!][!//
[!VAR "Spi_Width" = "num:i(8)"!][!//
[!ELSEIF "$Spi_Width >= num:i(9) and $Spi_Width <= num:i(16)"!][!//
[!VAR "Spi_Width" = "num:i(16)"!][!//
[!ELSE!][!//
[!VAR "Spi_Width" = "num:i(32)"!][!//
[!ENDIF!][!//
[!VAR "Spi_offSet5" = "$Spi_Width div num:i(8)"!][!//
[!VAR "Spi_offSet5" = "$Spi_offSet5 * node:value(concat('SpiDriver/SpiChannel/',$Spi_ChannlNamePointer,'/SpiIbNBuffers'))"!][!//
[!IF "$Spi_offSet5 mod num:i(4) != num:i(0)"!][!//
[!VAR "Spi_offSet5" = "$Spi_offSet5 + (num:i(4) - ($Spi_offSet5 mod num:i(4)))"!][!//
[!ENDIF!][!//
[!VAR "Spi_offSet" = "$Spi_offSet + $Spi_offSet5"!]
[!ENDFOR!][!//
[!ENDIF!][!//
[!//
[!ENDIF!][!//
[!//
[!//
[!//
[!IF "text:split($QSPICore_config,',')[position() = 1] = $CPU_ID"!][!//
[!//
[!//
[!IF "$Spi_EBChnlCount0Sync != 0"!][!//
[!FOR "Spi_LoopCntr" = "$Spi_EBChnlCount0Sync" TO "num:i(1)" STEP "-1"!][!//
  {0, 0},    /*[!"text:split($Spi_EBChnl0Sync,',')[position() = $Spi_LoopCntr]"!]*/
[!ENDFOR!][!//
[!ELSE!][!//
[!FOR "Spi_LoopCntr" = "$Spi_EBChnlCount0Async" TO "num:i(1)" STEP "-1"!][!//
  {0, 0},    /*[!"text:split($Spi_EBChnl0Async,',')[position() = $Spi_LoopCntr]"!]*/
[!ENDFOR!][!//
[!ENDIF!][!//
[!//
[!ENDIF!][!//
[!//
[!//
[!IF "text:split($QSPICore_config,',')[position() = 2] = $CPU_ID"!][!//
[!//
[!//
[!IF "$Spi_EBChnlCount1Sync != 0"!][!//
[!FOR "Spi_LoopCntr" = "$Spi_EBChnlCount1Sync" TO "num:i(1)" STEP "-1"!][!//
  {0, 0},    /*[!"text:split($Spi_EBChnl1Sync,',')[position() = $Spi_LoopCntr]"!]*/
[!ENDFOR!][!//
[!ELSE!][!//
[!FOR "Spi_LoopCntr" = "$Spi_EBChnlCount1Async" TO "num:i(1)" STEP "-1"!][!//
  {0, 0},    /*[!"text:split($Spi_EBChnl1Async,',')[position() = $Spi_LoopCntr]"!]*/
[!ENDFOR!][!//
[!ENDIF!][!//
[!//
[!ENDIF!][!//
[!//
[!//
[!IF "text:split($QSPICore_config,',')[position() = 3] = $CPU_ID"!][!//
[!//
[!//
[!IF "$Spi_EBChnlCount2Sync != 0"!][!//
[!FOR "Spi_LoopCntr" = "$Spi_EBChnlCount2Sync" TO "num:i(1)" STEP "-1"!][!//
  {0, 0},    /*[!"text:split($Spi_EBChnl2Sync,',')[position() = $Spi_LoopCntr]"!]*/
[!ENDFOR!][!//
[!ELSE!][!//
[!FOR "Spi_LoopCntr" = "$Spi_EBChnlCount2Async" TO "num:i(1)" STEP "-1"!][!//
  {0, 0},    /*[!"text:split($Spi_EBChnl2Async,',')[position() = $Spi_LoopCntr]"!]*/
[!ENDFOR!][!//
[!ENDIF!][!//
[!//
[!ENDIF!][!//
[!//
[!//
[!IF "text:split($QSPICore_config,',')[position() = 4] = $CPU_ID"!][!//
[!//
[!//
[!IF "$Spi_EBChnlCount3Sync != 0"!][!//
[!FOR "Spi_LoopCntr" = "$Spi_EBChnlCount3Sync" TO "num:i(1)" STEP "-1"!][!//
  {0, 0},    /*[!"text:split($Spi_EBChnl3Sync,',')[position() = $Spi_LoopCntr]"!]*/
[!ENDFOR!][!//
[!ELSE!][!//
[!FOR "Spi_LoopCntr" = "$Spi_EBChnlCount3Async" TO "num:i(1)" STEP "-1"!][!//
  {0, 0},    /*[!"text:split($Spi_EBChnl3Async,',')[position() = $Spi_LoopCntr]"!]*/
[!ENDFOR!][!//
[!ENDIF!][!//
[!//
[!ENDIF!][!//
[!//
[!//
[!IF "text:split($QSPICore_config,',')[position() = 5] = $CPU_ID"!][!//
[!//
[!//
[!IF "$Spi_EBChnlCount4Sync != 0"!][!//
[!FOR "Spi_LoopCntr" = "$Spi_EBChnlCount4Sync" TO "num:i(1)" STEP "-1"!][!//
  {0, 0},    /*[!"text:split($Spi_EBChnl4Sync,',')[position() = $Spi_LoopCntr]"!]*/
[!ENDFOR!][!//
[!ELSE!][!//
[!FOR "Spi_LoopCntr" = "$Spi_EBChnlCount4Async" TO "num:i(1)" STEP "-1"!][!//
  {0, 0},    /*[!"text:split($Spi_EBChnl4Async,',')[position() = $Spi_LoopCntr]"!]*/
[!ENDFOR!][!//
[!ENDIF!][!//
[!//
[!ENDIF!][!//
[!IF "text:split($QSPICore_config,',')[position() = 6] = $CPU_ID"!][!//
[!//
[!//
[!IF "$Spi_EBChnlCount5Sync != 0"!][!//
[!FOR "Spi_LoopCntr" = "$Spi_EBChnlCount5Sync" TO "num:i(1)" STEP "-1"!][!//
  {0, 0},    /*[!"text:split($Spi_EBChnl5Sync,',')[position() = $Spi_LoopCntr]"!]*/
[!ENDFOR!][!//
[!ELSE!][!//
[!FOR "Spi_LoopCntr" = "$Spi_EBChnlCount5Async" TO "num:i(1)" STEP "-1"!][!//
    {0, 0},    /*[!"text:split($Spi_EBChnl5Async,',')[position() = $Spi_LoopCntr]"!]*/
[!ENDFOR!][!//
[!ENDIF!][!//
[!//
[!ENDIF!][!//
  {0xFFFF, 0xFFFF}
};

[!//[cover parentID={D9126AE6-F9D1-4d56-946F-29F4A505841D}][/cover][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($CPU_ID)"!]_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"
/********************CORE[!"num:i($CPU_ID)"!] RX/TX BUFFERS MEMMAP SECTION***********************/
[!ENDIF!][!//
[!//
[!ENDFOR!][!//

[!FOR "CPU_ID" = "0" TO "num:i($Spi_MaxCore)"!][!//
[!// checking if core is enabled only then generate configuration for that core
[!IF "text:split($Core_config,',')[position() = $CPU_ID + num:i(1)] = num:i(1)"!][!//
/******************* CORE[!"num:i($CPU_ID)"!] Spi_Config_Core CONFIGURATION MEMMAP SECTION *************/

[!// [cover parentID={05AD43C2-FF50-4d26-B68E-279693B32B8F}][/cover][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($CPU_ID)"!]_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"

/* MISRA2012_RULE_8_7_JUSTIFICATION: Spi_Config_Core[!"num:i($CPU_ID)"!] is being used globally
 * cannot be static */
 /* MISRA2012_RULE_8_4_JUSTIFICATION: Agreed violation */
[!// [cover parentID={6D2265AA-8B10-40c9-B50A-44F80FCA55D7}][/cover][!//
[!IF "$VariantsConfigured = num:i(1)"!][!//
const Spi_CoreConfigType Spi_Config_Core[!"num:i($CPU_ID)"!]_[!"$PredefinedVarName"!] =
[!ELSE!]
const Spi_CoreConfigType Spi_Config_Core[!"num:i($CPU_ID)"!] =
[!ENDIF!]
{
  /* Sequence Configuration */
  Spi_kSequenceConfig_Core[!"num:i($CPU_ID)"!],

  /* Job configuration */
  Spi_kJobConfig_Core[!"num:i($CPU_ID)"!],

  /* Channel Configuration */
  Spi_kChannelConfig_Core[!"num:i($CPU_ID)"!],

  Spi_ChannelOffsets_Core[!"num:i($CPU_ID)"!],
  /* QSPI Hw configuration */
  {
[!// checking if the QSPI0 is assigned to the core for which configuration is being generated
[!IF "text:split($QSPICore_config,',')[position() = num:i(1)] = $CPU_ID"!]
[!IF "$Spi_MacQspi0Used = num:i(1)"!][!//
[!/* QSPI0 */!][!//
    &Spi_kQspiHwConfigQSPI0,
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!]
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!][!//
[!// checking if the QSPI1 is assigned to the core for which configuration is being generated
[!IF "text:split($QSPICore_config,',')[position() = num:i(2)] = $CPU_ID"!]
[!IF "$Spi_MacQspi1Used = num:i(1)"!][!//
[!/* QSPI1 */!][!//
    &Spi_kQspiHwConfigQSPI1,
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!]
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!][!//
[!// checking if the QSPI2 is assigned to the core for which configuration is being generated
[!IF "text:split($QSPICore_config,',')[position() = num:i(3)] = $CPU_ID"!]
[!IF "$Spi_MacQspi2Used = num:i(1)"!][!//
[!/* QSPI2 */!][!//
    &Spi_kQspiHwConfigQSPI2,
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!]
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!][!//
[!// checking if the QSPI3 is assigned to the core for which configuration is being generated
[!IF "text:split($QSPICore_config,',')[position() = num:i(4)] = $CPU_ID"!]
[!IF "$Spi_MacQspi3Used = num:i(1)"!][!//
[!/* QSPI3 */!][!//
    &Spi_kQspiHwConfigQSPI3,
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!]
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!][!//
[!// checking if the QSPI4 is assigned to the core for which configuration is being generated
[!IF "text:split($QSPICore_config,',')[position() = num:i(5)] = $CPU_ID"!]
[!IF "$Spi_MacQspi4Used = num:i(1)"!][!//
[!/* QSPI4 */!][!//
    &Spi_kQspiHwConfigQSPI4,
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!]
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!][!//
[!// checking if the QSPI5 is assigned to the core for which configuration is being generated
[!IF "SpiPublishedInformation/SpiMaxHwUnit = num:i(6)"!]
    [!IF "text:split($QSPICore_config,',')[position() = num:i(6)] = $CPU_ID"!]
    [!IF "$Spi_MacQspi5Used = num:i(1)"!][!//
    [!/* QSPI5 */!][!//
    &Spi_kQspiHwConfigQSPI5,
[!ELSE!][!//
    NULL_PTR,
    [!ENDIF!]
    [!ELSE!][!//
     NULL_PTR,
    [!ENDIF!][!//
[!ENDIF!]
  },

  /* Hw Map Index */
[!// Hw map value will be genrated using Spi_CGGenerateQspiMapConfigVal
  [!CALL "Spi_CGGenerateQspiMapConfigVal","CPU_ID" = "$CPU_ID"!],

  /* No. of Sequences configured */
[!VAR "Spi_SeqCountConfig" = "num:i(0)"!][!//
[!LOOP "SpiDriver/SpiSequence/*"!][!//
  [!VAR "Spi_SeqKernelHW" = "node:value(node:ref(node:ref(./SpiJobAssignment/*[1])/SpiDeviceAssignment)/SpiHwUnit)"!][!//
  [!VAR "Spi_SeqKernelID" = "substring-after($Spi_SeqKernelHW, 'I')"!][!//
  [!IF "text:split($QSPICore_config,',')[position() = $Spi_SeqKernelID + 1] = $CPU_ID"!][!//
    [!VAR "Spi_SeqCountConfig" = "$Spi_SeqCountConfig + num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//
  [!"num:i($Spi_SeqCountConfig)"!]U,

  /* No. of Jobs configured */
[!VAR "Spi_JobCountConfig" = "num:i(0)"!][!//
[!LOOP "SpiDriver/SpiJob/*"!][!//
  [!VAR "Spi_JobKernelHW" = "node:value(node:ref(./SpiDeviceAssignment)/SpiHwUnit)"!][!//
  [!VAR "Spi_JobKernelID" = "substring-after($Spi_JobKernelHW, 'I')"!][!//
  [!IF "text:split($QSPICore_config,',')[position() = $Spi_JobKernelID + 1] = $CPU_ID"!][!//
    [!VAR "Spi_JobCountConfig" = "$Spi_JobCountConfig + num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//
  [!"num:i($Spi_JobCountConfig)"!]U,

  /* No. of Channels configured */
[!VAR "Spi_ChnlCountConfig" = "num:i(0)"!][!//
[!VAR "Spi_ListOfChannelperCore" = "''"!][!//
[!LOOP "SpiDriver/SpiJob/*"!][!//
  [!VAR "Spi_JobKernelHW" = "node:value(node:ref(./SpiDeviceAssignment)/SpiHwUnit)"!][!//
  [!VAR "Spi_JobKernelID" = "substring-after($Spi_JobKernelHW, 'I')"!][!//
  [!IF "text:split($QSPICore_config,',')[position() = $Spi_JobKernelID + 1] = $CPU_ID"!][!//
    [!LOOP "./SpiChannelList/*"!][!//
      [!IF "not(text:contains(text:split($Spi_ListOfChannelperCore,','), node:name(node:ref(./SpiChannelAssignment))))"!][!//
        [!VAR "Spi_ListOfChannelperCore" = "concat($Spi_ListOfChannelperCore, node:name(node:ref(./SpiChannelAssignment)),',')"!][!//
        [!VAR "Spi_ChnlCountConfig" = "$Spi_ChnlCountConfig + num:i(1)"!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//
  [!"num:i($Spi_ChnlCountConfig)"!]U
};

[!// [cover parentID={6A08AC0D-B613-4ad1-94D1-A9B43C5A353D}][/cover][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"num:i($CPU_ID)"!]_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"

/***************** CORE[!"num:i($CPU_ID)"!] Spi_Config_Core CONFIGURATION MemMap SECTION END *************/
[!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDSELECT!][!/* as:modconf('Spi')[1] */!][!//

[!// [cover parentID={7F7AD6A8-754B-4c69-88E1-5946A35A9B5E}][/cover][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"


[!// [cover parentID={3D665480-5F82-4a49-A1EB-86EAEDFBB00D}][/cover][!//
[!IF "$VariantsConfigured = num:i(1)"!][!//
const Spi_ConfigType Spi_Config_[!"$PredefinedVarName"!] =
[!ELSE!][!//
const Spi_ConfigType Spi_Config =
[!ENDIF!][!//
{
  {
[!CALL "Spi_CGGenerateRootConfig"!]


  },
  [!IF "$VariantsConfigured = num:i(1)"!][!//
  SequenceLookupIndex_[!"$PredefinedVarName"!],
  JobLookupIndex_[!"$PredefinedVarName"!],
  ChannelLookupIndex_[!"$PredefinedVarName"!],
  [!ELSE!][!//
  SequenceLookupIndex,
  JobLookupIndex,
  ChannelLookupIndex,
  [!ENDIF!][!//

  /*Total number of Sequence*/
  [!"num:i(count(SpiDriver/SpiSequence/*))"!]U,
  /*Total number of Jobs*/
  [!"num:i(count(SpiDriver/SpiJob/*))"!]U,
  /*Total number of Channels*/
  [!"num:i(count(SpiDriver/SpiChannel/*))"!]U,
  /*Sync Delay*/
  [!"num:i(SpiGeneral/SpiSyncTransmitTimeoutDuration)"!]U
};

[!// [cover parentID={8A1794E7-AAEE-4cda-A743-62C52DC953CD}][/cover][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers shall be distinct
 * because of AS naming convention*/
 /* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers declared in the same scope
 shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 names
 * because of AS naming convention*/
#define SPI_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"[!//


/* End Of File */
[!//
