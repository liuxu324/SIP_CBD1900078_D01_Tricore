/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2018)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Fls_17_Dmu.c                                                **
**                                                                           **
**  VERSION :  16.0.0                                                        **
**                                                                           **
**  DATE     :  2018-09-28                                                   **
**                                                                           **
**  VARIANT   : Variant PB                                                   **
**                                                                           **
**  PLATFORM  : Infineon AURIX2G                                             **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION  : This file contains                                        **
**                 - functionality of Flash driver                           **
**                                                                           **
**  SPECIFICATION(S) : Specification of FLS Driver, AUTOSAR Release 4.2.2    **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: No                                      **
**                                                                           **
******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* [cover parentID={CE0E1013-F855-45f6-A341-3134FAB115C5}][/cover] */
/* [cover parentID={325361F6-5AA1-4027-A491-D8A970E7FE8C}][/cover] */
/* [cover parentID={93231028-6942-4390-A06D-5ACF5EB86F2F}][/cover] */
/* [cover parentID={34C9BD42-7196-4ba0-B305-4C5EE582F134}][/cover] */

#include "IfxDmu_reg.h"
#include "IfxDmu_bf.h"
#include "IfxFsi_reg.h"

/* Inclusion of Flash header file */
/* [cover parentID={93E8BC5E-CDEC-4da2-9273-77E9147D1B32}][/cover] */
#include "Fls_17_Dmu.h"

/* Inclusion of Flash command cycles file */
#include "Fls_17_Dmu_ac.h"

#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
#include "Mcal_SafetyError.h"
#endif

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

#ifndef FLS_17_DMU_AR_RELEASE_MAJOR_VERSION
#error "FLS_17_DMU_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#ifndef FLS_17_DMU_AR_RELEASE_MINOR_VERSION
#error "FLS_17_DMU_AR_RELEASE_MINOR_VERSION is not defined. "
#endif

#ifndef FLS_17_DMU_AR_RELEASE_REVISION_VERSION
#error "FLS_17_DMU_AR_RELEASE_REVISION_VERSION is not defined. "
#endif

#if ( FLS_17_DMU_AR_RELEASE_MAJOR_VERSION != 4U )
#error "FLS_17_DMU_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#if ( FLS_17_DMU_AR_RELEASE_MINOR_VERSION != 2U )
#error "FLS_17_DMU_AR_RELEASE_MINOR_VERSION does not match. "
#endif

/*
    DRIVER VERSION CHECK FOR FLS MODULE INCLUSION
*/

#ifndef FLS_17_DMU_SW_MAJOR_VERSION
#error "FLS_17_DMU_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef FLS_17_DMU_SW_MINOR_VERSION
#error "FLS_17_DMU_SW_MINOR_VERSION is not defined. "
#endif

#ifndef FLS_17_DMU_SW_PATCH_VERSION
#error "FLS_17_DMU_SW_PATCH_VERSION is not defined. "
#endif

#if (FLS_17_DMU_SW_MAJOR_VERSION != 3U)
#error "FLS_17_DMU_SW_MAJOR_VERSION does not match."
#endif

#if (FLS_17_DMU_SW_MINOR_VERSION != 0U)
#error "FLS_17_DMU_SW_MINOR_VERSION does not match."
#endif


/* [cover parentID={703AAC5B-F330-40d2-98BC-02D1C0CE7C27}]
[/cover]
*/
/*
    VERSION CHECK FOR DET MODULE INCLUSION
*/
#if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
                                 (FLS_17_DMU_SAFETY_ENABLE == STD_ON)

#ifndef DET_AR_RELEASE_MAJOR_VERSION
#error "DET_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#if ( DET_AR_RELEASE_MAJOR_VERSION != 4U )
#error "DET_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#endif /* (FLS_DEV_ERROR_DETECT == STD_ON) */


/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

#define FLS_ONE_VALUE                (1U)
#define FLS_THREE_VALUE              (3U)

/* Page size mask used for checking if address is page aligned*/
/* MISRA2012_RULE_2_5_JUSTIFICATION: Macro has been used so it is a false
warning*/
#define FLS_PAGE_SIZE_MASK        (FLS_17_DMU_PAGE_SIZE-1U)

#if(FLS_17_DMU_IFX_FEE_USED == STD_ON)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Macro has been used so it is a false
warning*/
#define FLS_WL_SIZE_MASK          (512U-1U)
#endif

/* Protection and sequence errors */
#define FLS_PROER_SQER_ERROR        (0x00000006U)

/* Operational error */
#define FLS_OPER_ERROR              (0x00000001U)
/* Uncorrectable bit error */
#define FLS_BIT_ERROR               (0x00080000U)
/* Dflash busy status */
#define FLS_D0BUSY                  (0x00000001U)
/* Dflash Waitstate mask */
#define FLS_DMU_WAITSTATES_MASK     (0xFFF8FF00U)
/*SELD0 for Margin Select*/
#define FLS_DMU_SELD0_MASK          (0xFFFFFFFCU)

/*Timeout value for margin switch*/
/* MISRA2012_RULE_2_5_JUSTIFICATION: Macro has been used so it is a false
warning*/
#define FLS_DMU_MARGIN_TIMEOUT      (2000U)
/*End of Busy Interrupt Bit*/

#if( FLS_17_DMU_USE_INTERRUPTS == STD_ON)
#define FLS_DMU_EER_EOBM_MASK       (0x80000000U)
#endif
/*Trap Disable*/
#define FLS_DMU_ECCC_TRAPDIS_MASK   (0xC0000000U)

/*Enable CLR the AERM bit*/
#define FLS_DMU_ECCC_CLR        (0x00000003U)

#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
#define FLS_DMU_MODE_CHK            (0x00000003U)
#endif

#define FLS_DMU_ECCW_CLR            (0x3FFFFFFFU)

#if (FLS_17_DMU_INITCHECK_API == STD_ON)
/*Init Check registers*/
#define FLS_REG_CLR_CHK               (0xFFFFFFFFU)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Macro has been used so it is a false
warning*/
#define FLS_REG_COMM_CLRCHK           (uint8)(0xFF)
#define FLS_ERRSRREG_CLRCHK           (0x0000001FU)
#endif

/* MISRA2012_RULE_2_5_JUSTIFICATION: Macro has been used so it is a false
warning*/
#define FLS_DMU_ECCW_CLR_CHK          (0xC0000000U)
#define FLS_DMU_ECCC_CLR_CHK          (0xC0000000U)
#define FLS_DMU_ERR_CLR               (0x0000003EU)

/* MISRA2012_RULE_2_5_JUSTIFICATION: Macro has been used so it is a false
warning*/
#define FLS_DMU_WAITSTATES_MASK_CHK   (0x000000FFU)

/* MISRA2012_RULE_2_5_JUSTIFICATION: Macro has been used so it is a false
warning*/
#define FLS_DMU_SELD0_MASK_CHK        (0x00000003U)

/*
#define IFX_DMU_HF_ERRSR_OPER_MSK (0x1u)
#define IFX_DMU_HF_ERRSR_PVER_OFF (3u)
#define IFX_DMU_HF_ERRSR_PVER_MSK (0x1u)
#define IFX_DMU_HF_ECCC_TRAPDIS_MSK (0x3u)
*/

/*Init status for the API*/
#define FLS_INITIALIZED            ((uint32)1)

/* Word size - 4 bytes */
/* MISRA2012_RULE_2_5_JUSTIFICATION: Macro has been used so it is a false
warning*/
#define FLS_WORD_SIZE              (4U)

/* MISRA2012_RULE_2_5_JUSTIFICATION: Macro has been used so it is a false
warning*/
#define FLS_WORD_SIZE_MASK        (FLS_WORD_SIZE - 1U)

#if (FLS_17_DMU_USE_ERASESUSPEND == STD_ON)
#define SUSPEND_CLR_OFF            (0x2U)
#endif

/* Mask to check the Mod4K result */
#define FLS_MOD4K_MASK          (0x0FFFU)
/* Number of shifts to do division or multiplication by 4K -> 2^12 */
#define FLS_4KSHIFT_VAL          (12U)
/* Mask to check the Mod64 result */
/* MISRA2012_RULE_2_5_JUSTIFICATION: Macro has been used so it is a false
warning*/
#define FLS_MOD64_MASK          (0x3FU)
/* Number of shifts to do division or multiplication by 64 -> 2^6 */
/* MISRA2012_RULE_2_5_JUSTIFICATION: Macro has been used so it is a false
warning*/
#define FLS_64SHIFT_VAL          (6U)

/* Recommended maximum number of sectors to be erased in 1 erase command cycle
*/
#define FLS_MAXERASE_SEC          (64U)

/* MISRA2012_RULE_2_5_JUSTIFICATION: Macro has been used so it is a false
warning*/
#define FLS_VERIFYSECTOR_CHK_VAL   (0xDEADBEEFU)

/*Read with hard margin selection value */
/* MISRA2012_RULE_2_5_JUSTIFICATION: Macro has been used so it is a false
warning*/
#define FLS_READHARDMARGIN_VAL      (3U)
/*Tight0- Tight margin for 0 (low) level */

/* MISRA2012_RULE_2_5_JUSTIFICATION: Macro has been used so it is a false
warning*/
#define FLS_TIGHT0MARGIN_VAL       (0xfffffeffU)

/*Hardening*/
#if(FLS_17_DMU_IFX_FEE_USED == STD_ON)
/*Mask to extract the TBE (3 bit error) status in FSI_COMM_2 */
#define FLS_COMM2TBE_MASK (0xE0U)

/* Register setting value for control gate voltage of 4.1V */
#define FLS_CTRLGATEVOLTAGE_VAL (0x20)

/* Mask to extract the result stored (5bits) in FSI_COMM_2.COMM2[4:0] */
#define FLS_FSICOMM2RES_MASK          ((uint8)(0x1FU))

#define FLS_DMU_HARDEN_PAGE_ALIGN      (0x8U)
#define FLS_DMU_HARDEN_WORD_ALIGN      (0xFFFFFFF7U)

/*Timeout for User Content Count*/
#define FLS_USRCONTENT_PAGE_TIMEOUT         (21000U)
#define FLS_USRCONTENT_WL_TIMEOUT         (100000U)
/* 8 bits shift value */
#define FLS_SHIFT8BITS_VAL          ((uint8)(8U))

#endif /*Hardening*/

/* MISRA2012_RULE_2_5_JUSTIFICATION: Macro has been used so it is a false
warning*/
#define FLS_COMM_RESET_VAL         ((uint8)0x00)
/* Wordline fail count to be suported */

/* MISRA2012_RULE_2_5_JUSTIFICATION: Macro has been used so it is a false
warning*/
#define FLS_WL_FAIL_COUNT (2U)

#define FLS_EVER_CHK ((uint8)(0x1))

#if (FLS_17_DMU_INIT_API_MODE == FLS_17_DMU_MCAL_SUPERVISOR)

/* Library APIs  */

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro defined for User mode
support in code. No side effects foreseen by violating this MISRA rule. */
#define FLS_17_DMU_LIB_INIT_DEINIT_WRITECPUENDINITPROTREG(RegAdd,Data) \
                                     Mcal_WriteCpuEndInitProtReg(RegAdd,Data)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro defined for User mode
support in code. No side effects foreseen by violating this MISRA rule. */
#define FLS_17_DMU_SFR_INIT_DEINIT_WRITE32(reg, value)  \
                                              ((*(reg)) = (uint32)(value))

#else
#include "McalLib_OsStub.h"
/* [cover parentID={1A65EADD-AFD0-4845-B2D2-8257E086DD67} ][/cover] */

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro defined for User mode
support in code. No side effects foreseen by violating this MISRA rule. */
#define FLS_17_DMU_LIB_INIT_DEINIT_WRITECPUENDINITPROTREG(RegAdd,Data) \
                                 MCAL_LIB_WRITECPUENDINITPROTREG(RegAdd,Data)


/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro defined for User mode
support in code. No side effects foreseen by violating this MISRA rule. */
#define FLS_17_DMU_SFR_INIT_DEINIT_WRITE32(RegAdd, Data)\
                        MCAL_SFR_OS_WRITE32(FLS_17_DMU_MODULE_ID,RegAdd,Data)

#endif /*(FLS_17_DMU_INIT_API_MODE == MCAL_SUPERVISOR)*/

#if (FLS_17_DMU_RUNTIME_API_MODE == FLS_17_DMU_MCAL_SUPERVISOR)
/* Library APIs  */

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro defined for User mode
support in code. No side effects foreseen by violating this MISRA rule. */
#define FLS_17_DMU_LIB_RUNTIME_WRITECPUENDINITPROTREG(RegAdd,Data) \
                                     Mcal_WriteCpuEndInitProtReg(RegAdd,Data)
#else
#include "McalLib_OsStub.h"

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro defined for User mode
support in code. No side effects foreseen by violating this MISRA rule. */
#define FLS_17_DMU_LIB_RUNTIME_WRITECPUENDINITPROTREG(RegAdd,Data) \
                                 MCAL_LIB_WRITECPUENDINITPROTREG(RegAdd,Data)
#endif /*(FLS_17_DMU_RUNTIME_API_MODE == MCAL_SUPERVISOR)*/

/******************************************************************************
**                      Private Function Declarations                        **
******************************************************************************/

#define FLS_17_DMU_START_SEC_CODE_ASIL_B_LOCAL

/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}][/cover] */
/* [cover parentID= {566ED99C-0D96-46ac-97BF-E97B04E2C700}][/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}][/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}][/cover] */
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}][/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}][/cover] */

/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Fls_17_Dmu_MemMap.h"

static void Fls_lMainErase(void);

static void Fls_lMainWrite(void);

static void Fls_lMainRead(void);

static void Fls_lMainCompare(void);

static void Fls_lMainBlankCheck(void);

static void Fls_lErrorHandler(const uint8 JobType);

#if (FLS_17_DMU_IFX_FEE_USED == STD_ON)
static Std_ReturnType Fls_lLocalVerifyErase(
  const Fls_17_Dmu_AddressType TargetAddress,
  uint32 *const UnerasedWordlineAddressPtr,
  uint8 *const UnerasedWordlineCountPtr,
  const uint8 Sector, uint32 value);
#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
LOCAL_INLINE uint8 Fls_lHardenSafetyChk(
  const Fls_17_Dmu_AddressType TargetAddress,
  const uint8 AlignChk);
#endif
#endif

#if (FLS_17_DMU_IFX_FEE_USED == STD_ON)
static void Fls_lEverFlagChkFail(void);
#endif

#if (FLS_17_DMU_USE_ERASESUSPEND == STD_ON)
LOCAL_INLINE boolean Fls_lSpndTimeout(const uint32 TimeOutCount);
#endif

static void Fls_lMainWriteJobStart(const uint32 PhysicalAddress);

static void Fls_lMainEraseJobStart(const uint32 PhysicalAddress);

LOCAL_INLINE boolean Fls_lPverChk(void);

#if (FLS_17_DMU_INITCHECK_API == STD_ON)
static Std_ReturnType Fls_lInitCheck(void);
#endif

#if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON)|| \
                             (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
LOCAL_INLINE uint8 Fls_lBusyDET_Read(
  const Fls_17_Dmu_StateType *const StatePtr);

LOCAL_INLINE uint8 Fls_lBusyDET_Write(const Fls_17_Dmu_StateType *const
                                      StatePtr);

LOCAL_INLINE uint8 Fls_lBusyDET_Erase(const Fls_17_Dmu_StateType *const
                                      StatePtr);

#if (FLS_17_DMU_COMPARE_API == STD_ON)
LOCAL_INLINE uint8 Fls_lBusyDET_Compare(
  const Fls_17_Dmu_StateType*const
  StatePtr);
#endif

static uint8 Fls_lUninitDET(const uint8 ServiceID);

static uint8 Fls_lTimeOutDET(const uint8 ServiceID);

LOCAL_INLINE void Fls_lCalculateWriteTimeoutCount(void);

#if (FLS_17_DMU_IFX_FEE_USED == STD_OFF)
LOCAL_INLINE Std_ReturnType Fls_lPageEraseCheck(
  uint32 *const AddrCheckPtr,
  const uint32 Length,
  const uint8 ServiceID);
#endif

LOCAL_INLINE Std_ReturnType Fls_lCheckEraseDet(
  const Fls_17_Dmu_AddressType TargetAddress,
  const Fls_17_Dmu_LengthType Length);

LOCAL_INLINE Std_ReturnType Fls_lCheckWriteDet(
  const Fls_17_Dmu_AddressType TargetAddress,
  uint8 *const SourceAddressPtr,
  const Fls_17_Dmu_LengthType Length);

#if (FLS_17_DMU_IFX_FEE_USED == STD_OFF)
LOCAL_INLINE boolean Fls_lCheckWrittenPage(const uint32 PageLength);
#endif


/* API to check DET errors in Fls_Init API. */
static void Fls_lReportError(const uint8 Fls_Sid, const uint8 ErrorId);

#endif /* End of FLS_DEV_ERROR_DETECT, FLS_17_DMU_SAFETY_ENABLE */

/*Check for command sequence error and protection error*/
LOCAL_INLINE uint32 Fls_lChkSeqProtErrors(void);

/*Check for operational error */
LOCAL_INLINE uint32 Fls_lChkOperError(void);

/*Check for double bit errors (DBER) */
LOCAL_INLINE uint32 Fls_lChkBitErrors(void);

/* Return the Busy status of the Data Flash Bank */
/* FLASH0_FSR.U & (1U<< (1U + (Bank) ) */
LOCAL_INLINE uint32 Fls_lHWBusyCheck(void);

/* get the write mode , page mode or burst mode */
LOCAL_INLINE uint8 Fls_lGetWriteMode(void);

/* Get max read length according to the FLS mode */
LOCAL_INLINE Fls_17_Dmu_LengthType Fls_lGetReadModeLength(void);

LOCAL_INLINE MemIf_ModeType Fls_lSetDefaultMode(void);


#define FLS_17_DMU_STOP_SEC_CODE_ASIL_B_LOCAL
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}][/cover] */

/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Fls_17_Dmu_MemMap.h"

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}][/cover] */

/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Fls_17_Dmu_MemMap.h"

/* MISRA2012_RULE_8_4_JUSTIFICATION: The variable declaration and
definition is correct and compatible.*/
const Fls_17_Dmu_ConfigType *Fls_ConfigPtr;
/* Initialize status. */

static uint32 Fls_17_Dmu_InitStatus;

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
/* [cover parentID={8A00BEA5-55E8-4faa-8270-04E4059138F6}]
[/cover]
*/
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover]
*/

/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Fls_17_Dmu_MemMap.h"



/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define FLS_17_DMU_START_SEC_CODE_ASIL_B_LOCAL

/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Fls_17_Dmu_MemMap.h"
/*******************************************************************************
** Traceability     : [cover parentID={E35FF093-4D81-429d-87D5-8A59FAFBBEFE}] **
**                                                                            **
** Syntax : void Fls_17_Dmu_Init(const Fls_17_Dmu_ConfigType* ConfigPtr)      **
**                                                                            **
** Service ID: 0x00                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  ConfigPtr - Pointer to configuration set                **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : Driver Module Initialization function                        **
** Service for FLASH initialization. The Initialization function shall        **
** initialize all Flash relevant registers with the values of the structure   **
** referenced by the parameter ConfigPtr.                                     **
**                                                                            **
*******************************************************************************/
void Fls_17_Dmu_Init(const Fls_17_Dmu_ConfigType *const ConfigPtr)
/* [cover parentID={E35FF093-4D81-429d-87D5-8A59FAFBBEFE}][/cover] */
{
  Fls_17_Dmu_StateType  *StatePtr;
  uint32 DFlash0WaitState;
  uint32 BitChange;
  volatile uint32 DummyRetVal;

  /* [cover parentID={847791BC-14C3-4fea-86A4-6F564E93786E}]
  Is the Configuration point NULL ?
  [/cover] */
  if (ConfigPtr == NULL_PTR)

  {
    /* [cover parentID={052A4F15-6F3C-4888-A3F0-5E10718631CC}]
    Report DET error
    [/cover] */
    /* [cover parentID={528501A2-FD21-41b9-A29E-9ACF0FF637F9}][/cover]
     */
    /* Report to DET */
#if( FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
                              (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
    Fls_lReportError(FLS_17_DMU_SID_INIT,FLS_17_DMU_E_PARAM_CONFIG);
#endif
  }

  /* [cover parentID={C740BB47-7648-4040-BD5F-CC72896D6A3D}]
  DET Enabled
  [/cover] */
  /* [cover parentID={EF535A4A-1D07-46d6-9728-2EA0599D6F59}]
  DET Enabled
  [/cover] */
#if( FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
                                      (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  /* Check if the driver is BUSY */

  else if(ConfigPtr->FlsStateVarPtr->FlsJobType != FLS_17_DMU_NONE )
  { /* [cover parentID={1F90F1CB-746A-40cf-8D42-4A3384B08521}][/cover] */
    Fls_lReportError(FLS_17_DMU_SID_INIT,
                     FLS_17_DMU_E_BUSY);/* Report to DET */
  }
#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  /*Safety Error if HWbusy */
  else if(Fls_lHWBusyCheck() != 0U)
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID,FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_INIT,FLS_17_DMU_E_HW_BUSY);
  }
  /* [cover parentID={B2067ECE-C152-439b-93CD-73560BB1D9E4}]
  Is erase already suspended?
  [/cover] */
  else if(DMU_HF_SUSPEND.B.SPND == 1U)
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID,FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_INIT,FLS_17_DMU_E_INIT_FAILED);
  }
  /*If the mode is not set to Single Mode*/
  else if((DMU_HF_PROCONUSR.U & FLS_DMU_MODE_CHK) != 0U)
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID,FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_INIT,FLS_17_DMU_E_INIT_FAILED);
  }
#endif
#endif
  else
  {
    /*  ------------------------------------------------------------------ **
    **                 Flash Module Initialization                         **
    **  ------------------------------------------------------------------ */
    /*
    Initialization of flash driver and its relevant registers
    */

    /* [cover parentID={0A96AA98-47DC-407b-AC21-B5DD959EC624}]
    Store the configuration pointer
    Clears error flags of FSR register
    Set DFlash (DF0) Wait states according to configuration
    [/cover] */
    /* Store the configuration pointer */
    Fls_ConfigPtr = ConfigPtr;

    /* Clears error flags of FSR register */
    Fls_ResetReadCmdCycle();

    /*clear the previous errors*/
    Fls_ClearStatusCmdCycle();

    /* Set DFlash (DF0) Wait states according to configuration */
    /*MISRA2012_RULE_11_4_JUSTIFICATION: Conversion between pointer to
      object and integer type is permitted for special function registers*/
    DFlash0WaitState = DMU_HF_DWAIT.U;
    DFlash0WaitState &= FLS_DMU_WAITSTATES_MASK;
    DFlash0WaitState |= ConfigPtr->FlsWaitStates;


    /* Reset EndInit protection to access EndInit protected registers */

    /* Clear the following Error Interrupt masks */
    /* OPERM, SQERM, PROERM, PVERM, EVERM, EOBM */
    /*MISRA2012_RULE_11_4_JUSTIFICATION: Conversion between pointer to
      object and integer type is permitted for special function registers*/
    /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
    the object types as the address of the register is being passed.
    MISRA2012_RULE_11_1_JUSTIFICATION: Pointer cast is required to match
    the object types.*/
    /*MISRA2012_RULE_11_8_JUSTIFICATION: Attempt to cast away const from a
    pointer. Solvable, but gives compiler warning. The address of the register
    is being passed.*/
    FLS_17_DMU_SFR_INIT_DEINIT_WRITE32(\
                                       (volatile uint32 *)&DMU_HF_EER.U, 0U);

    /* Margin Read Selection is set as standard margin */
    /*MISRA2012_RULE_11_4_JUSTIFICATION: Conversion between pointer to
      object and integer type is permitted for special function registers*/
    BitChange = DMU_HF_MARGIN.U & FLS_DMU_SELD0_MASK;

    /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
    the object types as the address of the register is being passed.
    MISRA2012_RULE_11_1_JUSTIFICATION: Pointer cast is required to match
    the object types.*/
    /*MISRA2012_RULE_11_8_JUSTIFICATION: Attempt to cast away const from a
    pointer. Solvable, but gives compiler warning. The address of the register
    is being passed.*/
    FLS_17_DMU_SFR_INIT_DEINIT_WRITE32(\
                                       (volatile uint32 *)&DMU_HF_MARGIN.U, \
                                       BitChange);
    /* Please note RFLASH1 field is for DF0 */
    /* RFLASH2 is for DF1 which shall be programmed by HSM */
    /* RFLASH2 value shall be greater than or equal to RFLASH1 */
    /*MISRA2012_RULE_11_4_JUSTIFICATION: Conversion between pointer to
      object and integer type is permitted for special function registers*/

    /* [cover parentID={6D6E729F-9EC7-4b69-B622-7F4ED402D8AA}]
    Initialise the DWAIT register
    [/cover] */
    /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
    the object types as the address of the register is being passed.*/
    /*MISRA2012_RULE_11_1_JUSTIFICATION: Pointer cast is required to match
    the object types.*/
    /*MISRA2012_RULE_11_8_JUSTIFICATION: Attempt to cast away const from a
    pointer. The address of the register
    is being passed.*/
    FLS_17_DMU_LIB_INIT_DEINIT_WRITECPUENDINITPROTREG(\
        (volatile uint32 *)&DMU_HF_DWAIT.U, \
        DFlash0WaitState);
    /*[cover parentID={88F8A5C9-CCDB-40bd-A8A2-5DB65E9BA807}][/cover]*/
#if( FLS_17_DMU_USE_INTERRUPTS == STD_ON)
    /* Enable End of Busy Interrupt Mask */
    /*MISRA2012_RULE_11_4_JUSTIFICATION: Conversion between pointer to
      object and integer type is permitted for special function registers*/
    BitChange = (DMU_HF_EER.U | FLS_DMU_EER_EOBM_MASK);

    /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
       the object types as the address of the register is being passed.
       MISRA2012_RULE_11_1_JUSTIFICATION: Pointer cast is required to match
       the object types.*/
    FLS_17_DMU_SFR_INIT_DEINIT_WRITE32(&DMU_HF_EER.U, \
                                       BitChange);
#endif

    /* The uncorrectable ECC error trap is disabled and ECC status register
     is cleared to clear the errors. */
    /*MISRA2012_RULE_11_4_JUSTIFICATION: Conversion between pointer to
      object and integer type is permitted for special function registers*/
    BitChange= (DMU_HF_ECCC.U & FLS_DMU_ECCC_CLR_CHK);
    BitChange|=(FLS_DMU_ECCC_TRAPDIS_MASK | FLS_DMU_ECCC_CLR);


    /* [cover parentID={03DCC2CD-1DD2-4f54-A0DC-AAFA42F0740D}]

       [/cover] */
    /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
    the object types as the address of the register is being passed.*/
    /*MISRA2012_RULE_11_1_JUSTIFICATION: Pointer cast is required to match
    the object types.*/
    /*MISRA2012_RULE_11_8_JUSTIFICATION: Attempt to cast away const from a
    pointer. Solvable, but gives compiler warning. The address of the register
    is being passed.*/
    FLS_17_DMU_LIB_INIT_DEINIT_WRITECPUENDINITPROTREG(\
        (volatile uint32 *)&DMU_HF_ECCC.U, \
        BitChange);

    /*Enable the ECC correction*/
    BitChange = (DMU_HF_ECCW.U & FLS_DMU_ECCW_CLR);

    /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
     the object types as the address of the register is being passed.*/
    /*MISRA2012_RULE_11_8_JUSTIFICATION: Attempt to cast away const from a
     pointer. Solvable, but gives compiler warning. The address of the register
     is being passed.*/
    FLS_17_DMU_LIB_INIT_DEINIT_WRITECPUENDINITPROTREG(\
        (volatile uint32 *)&DMU_HF_ECCW.U,BitChange);

    /*Clear the suspend registers*/
    /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
    the object types as the address of the register is being passed.*/
    FLS_17_DMU_SFR_INIT_DEINIT_WRITE32(\
                                       (volatile uint32 *)&DMU_HF_SUSPEND, 0U);

    /*Reset the COMM1 and COMM2 values to system reset values*/
    /* [cover parentID={E1BD7A7A-7C40-4b22-8C1D-2A02D4D2B180}]
    Reset the value of FSI_COMM1 and FSI_COMM2 registers
    [/cover] */
    FSI_COMM_1.U = FLS_COMM_RESET_VAL;
    FSI_COMM_2.U = FLS_COMM_RESET_VAL;

    /*  ------------------------------------------------------------------ **
    **                 Global Variable Initialization                      **
    **  ------------------------------------------------------------------ */
    /*
    After having finished the module initialization,
    the Flash Driver state shall be set to FLS_17_DMU_IDLE and and the jobs
    result shall be set to FLS_17_DMU_JOB_OK.
    */

    /* [cover parentID={D3BE77D2-199E-463b-BDC0-2E35609756A1}]
       Initialise the Global variables
       Set the Job result to OK, Job type to NONE
       Assign the default operating mode of FLS as per configuration,
       Initialize the OPER status, Check for OPER error
       [/cover] */
    StatePtr = ConfigPtr->FlsStateVarPtr;

    /*Set JobResult to ok */
    StatePtr->FlsJobResult = MEMIF_JOB_OK;

    /* Setting the Jobtype to none */
    StatePtr->FlsJobType = FLS_17_DMU_NONE;

    StatePtr->NotifCaller = FLS_17_DMU_NO_JOB;

    /* Initialize Job Status */
    StatePtr->JobStarted.Write = 0U;
    StatePtr->JobStarted.Erase = 0U;

    /* Assign default mode */
    StatePtr->FlsMode = Fls_lSetDefaultMode();

#if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
                        (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
    /* Enable timeout handling */
    StatePtr->FlsTimeoutControl = 1U;
#endif

    /* [cover parentID={5F594EBC-55CE-4483-99D3-50FF79B13AC6}]
     [/cover] */
    /* Check for OPER */
    DummyRetVal = Fls_lChkOperError();

    /* FlsOper will be updated by Fls_lChkOperError() */
    UNUSED_PARAMETER(DummyRetVal);

    Fls_17_Dmu_InitStatus = FLS_INITIALIZED;
    /* [cover parentID={53A71103-0C6E-48c6-B3C8-6A48D0158B7A}]
    Return
    [/cover] */
  }
}/* End of Function: Fls_Init */


#if (FLS_17_DMU_INITCHECK_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={FABE1515-678B-4067-9C75-7DBE5B2AB39C}]   **
**                                                                            **
** Syntax         : Std_ReturnType Fls_17_Dmu_InitCheck                       **
**                              (                                             **
**                              const Fls_17_Dmu_ConfigType *const ConfigPtr  **
**                              )                                             **
**                                                                            **
** Description    : This function verifies the initialization the FLS driver  **
**                  in context to the core from where the API is invoked.     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : 0x2B                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : None                                                      **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : E_OK - Initialization comparison is success               **
**                  E_NOT_OK - Initialization comparison failed               **
**                                                                            **
*******************************************************************************/
Std_ReturnType Fls_17_Dmu_InitCheck(const Fls_17_Dmu_ConfigType
                                    *const ConfigPtr)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint32 MarginCheck, EccEnableCheck,ErrStatusCheck,
         EccStatusCheck, DwaitRegCheck,DwaitCheck, EerStatusCheck,
         PverEverErrChk, ErrorChkStatus;
  uint8 HardenChkComm;

  if(ConfigPtr != NULL_PTR)
  {
    MarginCheck=((uint32)DMU_HF_MARGIN.U & FLS_DMU_SELD0_MASK_CHK);
    EccEnableCheck=((uint32)DMU_HF_ECCW.U & FLS_DMU_ECCW_CLR_CHK);
    /*MISRA2012_RULE_13_5_JUSTIFICATION: These are device registers and are
     declared with Volatile qualifier due to which the tool is giving
    MISRA 13.5.*/
    /*MISRA2012_RULE_1_3_JUSTIFICATION: These are device registers and are
     declared with Volatile qualifier due to which the tool is giving
      MISRA 1.3.*/
    /*MISRA2012_RULE_13_2_JUSTIFICATION: These are device registers and are
     declared with Volatile qualifier due to which the tool is giving
      MISRA 13.2.*/
    ErrStatusCheck=(((uint32)DMU_HF_ECCS.U & FLS_REG_CLR_CHK) | \
                    ((uint32)DMU_HF_SUSPEND.U & FLS_REG_CLR_CHK));
    DwaitRegCheck=((uint32)DMU_HF_DWAIT.U & FLS_REG_CLR_CHK);
    DwaitCheck=(((uint32)DMU_HF_DWAIT.U & FLS_DMU_WAITSTATES_MASK) |
                ConfigPtr->FlsWaitStates);
    EerStatusCheck=((uint32)DMU_HF_EER.U & FLS_REG_CLR_CHK);
    EccStatusCheck=((uint32)DMU_HF_ECCC.U & FLS_REG_CLR_CHK);
    /*MISRA2012_RULE_13_5_JUSTIFICATION: These are device registers and are
     declared with Volatile qualifier due to which the tool is giving
     MISRA 13.5.*/
    /*MISRA2012_RULE_1_3_JUSTIFICATION: These are device registers and are
     declared with Volatile qualifier due to which the tool is giving
     MISRA 1.3.*/
    /*MISRA2012_RULE_13_2_JUSTIFICATION: These are device registers and are
     declared with Volatile qualifier due to which the tool is giving
     MISRA 13.2.*/
    HardenChkComm = (((uint8)FSI_COMM_1.U & FLS_REG_COMM_CLRCHK) |  \
                     ((uint8)FSI_COMM_2.U & FLS_REG_COMM_CLRCHK));

    PverEverErrChk = ((uint32)DMU_HF_ERRSR.U & FLS_ERRSRREG_CLRCHK);
    ErrorChkStatus = (ErrStatusCheck | PverEverErrChk | EccEnableCheck |
                      MarginCheck | HardenChkComm);

    if((Fls_ConfigPtr !=NULL_PTR) && (Fls_ConfigPtr == ConfigPtr))
    {
      RetVal = Fls_lInitCheck();

      if(RetVal == E_OK)
      {
#if( FLS_17_DMU_USE_INTERRUPTS == STD_ON)
        if (FLS_DMU_EER_EOBM_MASK != EerStatusCheck)
#else
        if (0U != EerStatusCheck)
#endif
        {
          RetVal = E_NOT_OK;
        }
        else if (ErrorChkStatus != 0U)
        {
          RetVal = E_NOT_OK;
        }
        else if ((DwaitCheck != DwaitRegCheck) ||
                 (FLS_DMU_ECCC_TRAPDIS_MASK !=EccStatusCheck))
        {
          RetVal = E_NOT_OK;
        }
        else
        {
          /* Dummy else */
        }
      }
    }
    else
    {
      RetVal = E_NOT_OK;
    }
  }
  return(RetVal);
}



/*******************************************************************************
** Traceability   : [cover parentID=]                                         **
**                                                                            **
** Syntax         : Std_ReturnType Fls_lInitCheck                             **
**                              (                                             **
**                                                                            **
**                              )                                             **
**                                                                            **
** Description    : This function verifies the initialization the FLS driver  **
**                  in context to the core from where the API is invoked.     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : None                                                      **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : E_OK - Initialization comparison is success               **
**                  E_NOT_OK - Initialization comparison failed               **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Fls_lInitCheck(void)
{
  Std_ReturnType ReturnVal;
  const Fls_17_Dmu_StateType  *StatePtr;

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;

  if((StatePtr->FlsJobResult != MEMIF_JOB_OK)
      || (StatePtr->FlsJobType != FLS_17_DMU_NONE))
  {
    ReturnVal=E_NOT_OK;
  }

  else if((StatePtr->JobStarted.Write != 0U)
          || (StatePtr->JobStarted.Erase != 0U)
          || (Fls_ConfigPtr->FlsDefaultMode != StatePtr->FlsMode) ||
          (Fls_17_Dmu_InitStatus != FLS_INITIALIZED))
  {
    ReturnVal=E_NOT_OK;
  }
  else
  {
    ReturnVal=E_OK;
  }


  return(ReturnVal);

}
/* End of Fls_InitCheck */
/******************************************************************************/
#endif
/* End of #if (FLS_INITCHECK_API == STD_ON) */

/*******************************************************************************
** Traceability :[cover parentID={6959CDE2-07AD-4e69-807A-7C5952D7A7BD}]      **
**                                                                            **
** Syntax : void Fls_17_Dmu_GetVersionInfo(
                                 Std_VersionInfoType * const VersioninfoPtr ) **
**                                                                            **
** Service ID:     0x10                                                       **
**                                                                            **
** Sync/Async:      Synchronous                                               **
**                                                                            **
** Reentrancy:      reentrant                                                 **
**                                                                            **
** Parameters (in): VersioninfoPtr : Pointer to where to store the version    **
**                                   information of this module.              **
**                                                                            **
** Parameters (out):VersioninfoPtr : Pointer to where to store the version    **
**                               information of this module.                  **
** Return value:    none                                                      **
**                                                                            **
** Description :    This service returns the version information of           **
**                  this module.                                              **
**                  The version information includes:                         **
**                  Module Id,Vendor Id , Vendor specific version numbers     **
**                                                                            **
*******************************************************************************/
#if (FLS_17_DMU_VERSION_INFO_API == STD_ON)
/* [cover parentID={24B4E86B-4759-4bfa-871A-2E56DACB3C30}]
FLS VERSION INFO API is enabled
[/cover] */

/* [cover parentID={D746F9C2-0E84-4b70-B3C7-602D35911049}][/cover] */

/* [cover parentID={BE398CB8-00EC-49f1-B412-B4DA0A38FA75}][/cover] */
void Fls_17_Dmu_GetVersionInfo(Std_VersionInfoType* const VersionInfoPtr)
{ /* [cover parentID={0D6C04B3-0806-4803-B44F-FC92D762B0D9}][/cover] */
#if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
                                          (FLS_17_DMU_SAFETY_ENABLE == STD_ON)

  /* [cover parentID={B02230C6-1C60-41e8-944D-21D6C1BF3BBE}]
  Is version information pointer Null? [/cover] */
  if ((VersionInfoPtr) == NULL_PTR)
  {
    /* [cover parentID={E6FFC26B-96BE-4fce-88E1-5FD86A03B53B}]
    Report DET error
    [/cover] */
    /* [cover parentID={0BE84EAA-2B61-44b2-A4E4-C34C5DC5E090}][/cover] */
    Fls_lReportError(
      FLS_17_DMU_SID_GETVERSIONINFO,
      FLS_17_DMU_E_PARAM_POINTER
    );/* Report to  DET */

  }
  else
#endif
  {
    /* Note that version info pointer is not checked for NULL as the user
     is supposed to send the memory allocated pointer */
    /* FLS Module ID */
    /* [cover parentID={C6691AD5-6557-4533-BF53-2F0D04D79DF2}][/cover] */
    ((Std_VersionInfoType*)(VersionInfoPtr))->moduleID = FLS_17_DMU_MODULE_ID;
    /* FLS vendor ID */
    ((Std_VersionInfoType*)(VersionInfoPtr))->vendorID = FLS_17_DMU_VENDOR_ID;
    /* major version of FLS */
    ((Std_VersionInfoType*)(VersionInfoPtr))->sw_major_version =
      (uint8)FLS_17_DMU_SW_MAJOR_VERSION;
    /* minor version of FLS */
    ((Std_VersionInfoType*)(VersionInfoPtr))->sw_minor_version =
      (uint8)FLS_17_DMU_SW_MINOR_VERSION;
    /* patch version of FLS */
    ((Std_VersionInfoType*)(VersionInfoPtr))->sw_patch_version =
      (uint8)FLS_17_DMU_SW_PATCH_VERSION;
  }
  /* [cover parentID={856AA060-4F1B-4abe-9C42-B33FE3DE01E1}][/cover] */
}
#endif

/*******************************************************************************
** Traceability :[cover parentID={65778937-91C1-4192-98F4-8E9595BAC650}]      **
**                                                                            **
** Syntax : Std_ReturnType Fls_17_Dmu_Erase(                                  **
**                             const Fls_17_Dmu_AddressType TargetAddress,    **
**                             const Fls_17_Dmu_LengthType Length             **
**                                  )                                         **
**                                                                            **
** Service ID: 0x01                                                           **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  TargetAddress - Target address in Flash memory.         **
** This address offset will be added to the flash memory base address         **
**                    Length - Number of bytes to erase                       **
**                                                                            **
** Parameters (out): E_OK: command has been accepted                          **
**                   E_NOT_OK: command has not been accepted                  **
**                                                                            **
** Return value    : Std_ReturnType                                           **
**                                                                            **
** Description : This API Erases Flash. It copies the given parameters to     **
** driver internal variables, initiates the erase job, sets the driver status **
** to MEMIF_BUSY and job result to MEMIF_JOB_PENDING.                         **
*******************************************************************************/
Std_ReturnType Fls_17_Dmu_Erase( const Fls_17_Dmu_AddressType TargetAddress,
                                 const Fls_17_Dmu_LengthType Length)
/*[cover parentID={6C63C328-5CB0-4efe-A474-EB350526D552}][/cover]*/
{
  Fls_17_Dmu_StateType*   StatePtr;
  volatile uint32  PhysicalAddress;
  uint8            JobType;
  Std_ReturnType   ReturnValue;
#if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
                                (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  uint8            TimeoutCal;
#endif

  /* check for development error */

  /* [cover parentID={1D966A04-93A0-4e32-876A-B8B27A1965B9}]
  Rasie DET
  [/cover] */
#if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
                                     (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  if(Fls_lCheckEraseDet(TargetAddress, Length) != E_OK)
  {
    /* [cover parentID={00049BFD-5949-475a-8781-B4DF8F70D60E}]
    Set the Return Value as NOT OK
    [/cover] */
    /* [cover parentID={C3FABF96-64B7-4b52-8ECE-333E338D0535}]
    Set the Return Value as NOT OK
    [/cover] */
    ReturnValue = E_NOT_OK;
  }
  /* [cover parentID={AB5C643C-1FF9-42c9-9A9C-067A7C8F93B5}]
  Is erase already suspended?
  [/cover] */
#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  else if(DMU_HF_SUSPEND.B.SPND == 1U)
  {

    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID,FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_ERASE,FLS_17_DMU_E_ILLGL_OPERTN);

    ReturnValue = E_NOT_OK;
  }
#endif
  else
    /* FLS_DEV_ERROR_DETECT */
#endif

  {
    /* Check for OPER error */
    if(Fls_lChkOperError() == 0U)
    {
      /* [cover parentID={3E636493-8F52-42f3-AC35-DCCF57556815}]
      Set the Return Value as OK
      [/cover] */
      ReturnValue = E_OK;

      /* Initialise Local variables */
      StatePtr = Fls_ConfigPtr->FlsStateVarPtr;

      /* [cover parentID={785A057F-E5AC-44e8-9F02-86BA61F4851F}]
      Make a copy of parameters
      Calculate the physical address from TargetAddress
      Set the physical address to be erase
      Calculate the length in terms of number of 4K sectors
      [/cover] */
      /* Calculate the physical address from TargetAddress */
      PhysicalAddress = (uint32) (FLS_17_DMU_BASE_ADDRESS + TargetAddress);
      /* Set the physical address to be erased */
      StatePtr->FlsEraseAddress = PhysicalAddress;
      if((Length & FLS_MOD4K_MASK) == 0U)
      {
        /* Calculate the length in terms of number of 4K sectors*/
        StatePtr->FlsEraseNumSectors = (uint16) (Length >> FLS_4KSHIFT_VAL);
      }
      else
      {
        /* [cover parentID={B86B3591-795B-4503-925F-19C1080BDD26}]
        Update the number of 4K sectors to be erased
        [/cover] */
        /* Calculate the length in terms of number of 4K sectors*/
        StatePtr->FlsEraseNumSectors =
          (uint16)((Length >> FLS_4KSHIFT_VAL)+ FLS_ONE_VALUE);
      }
      /* Check if number of sectors to be erased can be accommodated in 1 erase
        command cycle; If not seal the number of sectors to be erased to
        recommended value 64 */
      if (StatePtr->FlsEraseNumSectors > FLS_MAXERASE_SEC)
      {
        StatePtr->FlsEraseNumSecPerCmd = (uint8)FLS_MAXERASE_SEC;
      }
      else
      {
        StatePtr->FlsEraseNumSecPerCmd = (uint8)StatePtr->FlsEraseNumSectors;
      }
      /* [cover parentID={3D29230A-4B5D-4c61-9502-D0C497A89D6E}]
      DET Enabled
      [/cover] */
#if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
                                       (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
      if((StatePtr->FlsEraseNumSectors & FLS_MOD64_MASK) == 0U)
      {
        /* Calculate the number of erase command cycles required*/
        TimeoutCal = (uint8) (StatePtr->FlsEraseNumSectors >> FLS_64SHIFT_VAL);
      }
      else
      {
        /* Calculate the number of erase command cycles required*/
        TimeoutCal = (uint8)
                     ((StatePtr->FlsEraseNumSectors >> FLS_64SHIFT_VAL)+
                      FLS_ONE_VALUE);
      }
#endif

      /* [cover parentID={4A618C5D-BF1A-4985-8C1D-9E0006CFC5EE}]
      DET Enabled
      [/cover] */
#if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
                                     (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
      if (StatePtr->FlsTimeoutControl != 0U)
      {
        /* Update Timeout count for erase */
        StatePtr->FlsEraseTimeoutCycleCount =
          (uint32)(FLS_17_DMU_ERASE_TIME / Fls_ConfigPtr->FlsCallCycle);
        /* Increment by one as a safety precaution to avoid boundary errors */
        StatePtr->FlsEraseTimeoutCycleCount++;
        /* Update the time out count in propotion to the
              number of erase command cycles */
        StatePtr->FlsEraseTimeoutCycleCount =
          StatePtr->FlsEraseTimeoutCycleCount * TimeoutCal;
      }
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */

      /* Check for hardware status */
      if(Fls_lHWBusyCheck() == 0U)
      {

        StatePtr->FlsEver = ((uint8)0x00);

        /*Set the Job Type*/
        /* [cover parentID={E640D575-9E03-47cc-AF2B-FFAFD266B784}]
        Update the Job Type as FLS_ERASE(erase job)
        [/cover] */
        JobType = FLS_17_DMU_ERASE;

        /* [cover parentID={7A7C7BAD-908D-48c8-9A86-4F9016C6986F}]
         Update driver status to pending by setting the FLS job result to Job
         pending
          [/cover] */
        /* Set the flash job result to job pending */
        StatePtr->FlsJobResult = MEMIF_JOB_PENDING;

        /* Update the new job */
        StatePtr->FlsJobType = JobType ;
        /*Job type settings done*/

        /* Indicate that the ERASE Job has been started */
        StatePtr->JobStarted.Erase = 1U;

        Fls_ClearStatusCmdCycle();
        /* Execute the ERASE COMMAND CYCLES */

        /* [cover parentID={B4D4B886-2A89-4e47-9FDC-5B2627F92309}]
        Execute Erase Command Cycles
        [/cover] */
        Fls_CallEraseCommand(StatePtr->FlsEraseAddress);

        /* Check for Sequence error,Protection error  */
        /* [cover parentID={A5E5A351-0321-4aa0-B226-F88C67A3A3D7}]
        Is sequence/protection error detected?
        [/cover] */
        if(Fls_lChkSeqProtErrors() != 0U)
        {
          /*[cover parentID={F83E03A0-A123-44fb-B48A-59E61F1278DE}][/cover] */
          ReturnValue = E_NOT_OK;
          /* Report Runtime error code to DET */
#if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
          /* [cover parentID={F83E03A0-A123-44fb-B48A-59E61F1278DE}][/cover] */
          Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                                  FLS_17_DMU_INSTANCE_ID,
                                  FLS_17_DMU_SID_ERASE,
                                  FLS_17_DMU_E_ERASE_FAILED);
#endif
          Fls_lErrorHandler(FLS_17_DMU_ERASE);
        }
        /* Check for command sequence Timeout */
        /* [cover parentID={71CA1BA3-109A-46c9-B0B6-AA6D22B3773F}]
        Is there command sequence timeout?
        [/cover] */
        else if (StatePtr->FlsTimeoutErr == FLS_17_DMU_ERASE)
        {
          ReturnValue = E_NOT_OK;
          /* [cover parentID={B653E4F4-BD09-4d86-B3AB-A7AD1A495BE9}]
          Call ErrorHandler function
          [/cover] */
          Fls_lErrorHandler(FLS_17_DMU_ERASE);
        }
        else
        {
          /* dummy else */
        }
      }
      else
      {
        ReturnValue = E_NOT_OK;
      }
    }
    else
    {

#if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
      /*[cover parentID={F83E03A0-A123-44fb-B48A-59E61F1278DE}][/cover] */
      Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                              FLS_17_DMU_INSTANCE_ID,
                              FLS_17_DMU_SID_ERASE,
                              FLS_17_DMU_E_ERASE_FAILED);
#endif
      Fls_lErrorHandler(FLS_17_DMU_ERASE);
      /* Job cannot be started because of OPER error */
      ReturnValue = E_NOT_OK;
    }
  }
  /* [cover parentID={CE2708C6-69C0-4bdd-8A7B-B23AB208CEBD}]
  Return
  [/cover] */
  return(ReturnValue);
}

/*******************************************************************************
** Traceability :[cover parentID={32E75AE9-D154-41ac-AC8E-FDA0064F594A}]      **
**                                                                            **
** Syntax : Std_ReturnType Fls_17_Dmu_Write( Fls_AddressType TargetAddress,   **
**                                    const uint8 *SourceAddressPtr,          **
**                                    Fls_LengthType Length                   **
**                                  )                                         **
**                                                                            **
** Service ID: 0x02                                                           **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :TargetAddress,SourceAddressPtr and Length                 **
**                                                                            **
** Parameters (out): E_OK: command has been accepted                          **
**                   E_NOT_OK: command has not been accepted                  **
**                                                                            **
** Return value    : Std_ReturnType                                           **
**                                                                            **
** Description : Writing to given flash address.                              **
** Service for writing one or more flash pages. This service copies the given **
** parameters to driver internal variables, initiate a Write job, set driver  **
** status to MEMIF_BUSY and job result to MEMIF_JOB_PENDING.                  **
*******************************************************************************/
Std_ReturnType Fls_17_Dmu_Write( const Fls_17_Dmu_AddressType TargetAddress,
                                 const uint8 *const SourceAddressPtr,
                                 const Fls_17_Dmu_LengthType Length
                               )
/* [cover parentID={56425B2B-6F8E-4a81-AAEF-6B0A60CA6988}][/cover] */
{
  Fls_17_Dmu_StateType   *StatePtr;
  uint32 PhysicalAddress;
  uint32          *PageStartAddressPtr;
  Std_ReturnType  RetVal;
  uint8           WriteMode;
  uint8           JobType;
  /* Initialise Local variables */
  RetVal = E_OK;
  /* [cover parentID={92FC4D7A-3D54-43df-91CB-547CF3BD8FD2}]
  Return value is OK
  [/cover] */

  /* [cover parentID={F6619BCF-D161-445b-9702-29D168BFDFA3}]
  DET Enabled
  [/cover] */
#if  ( FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
                              (FLS_17_DMU_SAFETY_ENABLE == STD_ON)

  /*[cover parentID={F46FD0D2-B0BE-4061-94D2-3E28023E7359}]
  Is development error detected ?
  [/cover] */
  /*MISRA2012_RULE_11_8_JUSTIFICATION: Attempt to cast away const from a
     pointer. Solvable, but gives compiler warning. the buffer address is
     used where the read data will be kept so non-const*/
  if(Fls_lCheckWriteDet(TargetAddress,(uint8 *)SourceAddressPtr,
                        Length) != E_OK)
  {
    /* [cover parentID={81B43DCD-E3FA-4dd1-B543-B9FED6088033}]
    Return value is NOT OK
    [/cover] */
    RetVal = E_NOT_OK;
  }
  /* [cover parentID={ABF80738-88B1-4700-919A-E145959FB823}]
  Check if  the driver is busy
  [/cover] */
  /* [cover parentID={61BF2015-B801-439d-BCF2-DA8A1A87FB49}]
  Is the driver busy?
  [/cover] */
  else if(Fls_lBusyDET_Write(Fls_ConfigPtr->FlsStateVarPtr) == 1U)
  {
    RetVal = E_NOT_OK;
  }
  else
#endif
  {
    StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
    /* PVER check for IFX FEE, clear FlsPver */
#if(FLS_17_DMU_VER_ERROR_CHECK == STD_ON)
#if(FLS_17_DMU_IFX_FEE_USED == STD_ON)
    StatePtr->FlsPver = 0U;
#endif
#endif

    /* Check OPER error status */
    if(Fls_lChkOperError() == 0U)
    {
      /*Check HW Busy*/
      if(Fls_lHWBusyCheck() == 0U)
      {

        /*Assign jobtype of Data Bank0 to write */
        /* [cover parentID={47820183-3840-4278-99EC-CAD7E0D144E4}]
        Update the state variable with FLS Jobtype with the new job(Write)
        [/cover] */
        /* [cover parentID={0DC68D4D-11BF-4832-8CD4-95849C0FAC74}]
          Update the state variable with FLS Jobtype with the new job(Write)
          [/cover] */
        JobType = FLS_17_DMU_WRITE;

        /* Determine the page start address */

        /* [cover parentID={A9B96D9C-0240-40c2-9114-77CA94921D22}]
     Update the Fls Write Physical Address to the address where the write has
          to begin
        [/cover] */
   /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
         type is required to access the FLASH address/target address which
               is defined as unsigned long. */
     /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
       is required to access the FLASH address/target address which is defined
             as unsigned long by AUTOSAR. */
   /* MISRA2012_RULE_10_8_JUSTIFICATION: conversion between pointer and integer
                            type is required to access the FLASH address/target
                             address which is defined as unsigned long. */
    PageStartAddressPtr = (uint32*)(FLS_17_DMU_BASE_ADDRESS + TargetAddress);
        /* Setting the PhysicalAddress to DF0 start address for Command cycle
                 execution */
        PhysicalAddress = FLS_17_DMU_BASE_ADDRESS;

        /*Job status setting done*/

        /*Set Job result*/
        /* 1. Set the flash job result to job pending */
        /* [cover parentID={0DC68D4D-11BF-4832-8CD4-95849C0FAC74}]
        Update job result as job pending
        [/cover] */
        StatePtr->FlsJobResult = MEMIF_JOB_PENDING;

        /*By Default Setting the PageStartAddress to DataBank0 PageAddress */

        /* [cover parentID={71640E10-5599-462f-8BE2-1382951C25BD}]
        Update the write buffer address(source)
        [/cover] */
        /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and
        integer type is required to access the FLASH address/target address
        which is defined as unsigned long. */
    /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
       is required to access the FLASH address/target address which is
             defined as unsigned long by AUTOSAR. */
        StatePtr->FlsWriteAddress = (uint32)PageStartAddressPtr;

        /* Assigning Length to global variable FlsWriteLength*/
        StatePtr->FlsWriteLength = Length;

        /* Assigning SourceAddressPtr to Global variable FlsWriteBufferPtr */
        StatePtr->FlsWriteBufferPtr = SourceAddressPtr;

        /* Update the new job  */
        StatePtr->FlsJobType = JobType;
        /* [cover parentID={43077E25-F854-4aed-908F-B259D832DA7D}]
            DET enabled
            [/cover] */
#if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
                                (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
        if (StatePtr->FlsTimeoutControl != 0U)
        {
          Fls_lCalculateWriteTimeoutCount();
        }
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
        /*End of StateVar variable setting*/

        /* [cover parentID={165C446B-0AFB-4c49-BF1D-5C91564E5673}]
        FLS_DEV_ERROR_DETECT is enabled
        FLS_17_DMU_IFX_FEE_USED is disabled
        [/cover] */
#if  ( FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
                                (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
#if (FLS_17_DMU_IFX_FEE_USED == STD_OFF)
        /* [cover parentID={EC5445C8-F6A1-4fe9-AFEA-9831C0882664}]
        Comparing the contents of the addressed memory area against the value
        of an erased flash cell to that the block has not been completely
        erased
        [/cover] */
 if(Fls_lPageEraseCheck(PageStartAddressPtr,Length,FLS_17_DMU_SID_WRITE) !=
            E_OK)
        {
          Fls_lErrorHandler(FLS_17_DMU_WRITE);
          RetVal = E_NOT_OK;
        }
        else
#endif /*FLS_17_DMU_IFX_FEE_USED*/
#endif /* FLS_DEV_ERROR_DETECT */
        {
          /* Indicate that the WRITE Job has started */
          StatePtr->JobStarted.Write = 1U;
          /*Obtain the Mode (Page or Burst) */
          WriteMode = Fls_lGetWriteMode();
          /* [cover parentID={898C45F2-EF1A-465f-86A9-B446C0525083}]
          Clear the HW error status registers
          [/cover] */
          Fls_ClearStatusCmdCycle();
          /* [cover parentID={601ECCF4-1583-4fd3-8FF0-627484D546B0}]
          Call write command sequence
          [/cover] */
          /* Execute the Write command sequence */
          Fls_CallWriteCommand(PhysicalAddress,StatePtr,WriteMode);

          /* [cover parentID={AF5A0B0E-17B4-476d-9038-2E4DCC90BA91}]
          Is production/sequence error detected?
          [/cover] */
          /* Check for Sequence error,Protection error */
          if(Fls_lChkSeqProtErrors() != 0U)
          {
            /* [cover parentID={9764FBD6-16E6-49b1-924B-AFC37936ECA2}]
            Runtime error detection enabled
            [/cover] */
            /* Report Runtime error code to DET */
#if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
            /* [cover parentID={E589FD7F-86DA-4aa9-8F8F-FA675DFD6438}]
            Report runtime DET error
            [/cover] */
   /* [cover parentID={90B6ED4E-82EC-4caf-8347-06E7DFB7D392}][/cover]
            */
            Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                                    FLS_17_DMU_INSTANCE_ID,
                                    FLS_17_DMU_SID_WRITE,
                                    FLS_17_DMU_E_WRITE_FAILED);
#endif
            /* Call to Fls_lErrorHandler local function */
            Fls_lErrorHandler(FLS_17_DMU_WRITE);
            RetVal = E_NOT_OK;
            /* [cover parentID={81B43DCD-E3FA-4dd1-B543-B9FED6088033}]
            Return value is NOT OK
            [/cover] */
          }
          /* Check for command cycle Timeout */
          /* [cover parentID={1A5C2B23-1B6A-446e-B706-B39EA4EFA77A}]
          Is timeout error detected?
          [/cover] */
          else if (StatePtr->FlsTimeoutErr == FLS_17_DMU_WRITE)
          {
            /* Call to Fls_lErrorHandler local function */
            /* [cover parentID={E048A1F4-352F-4a9d-A51F-808F5DBC0D51}]
            Indicate the error by calling
            [/cover] */
            Fls_lErrorHandler(FLS_17_DMU_WRITE);
            RetVal = E_NOT_OK;
            /* [cover parentID={81B43DCD-E3FA-4dd1-B543-B9FED6088033}]
            Return value is NOT OK
            [/cover] */
          }
          else
          {
            /* dummy else */
          }
        }
      }
      else
      {
        RetVal = E_NOT_OK;
      }
    }
    else
    {
      /* Report Runtime error code to DET */
#if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
      /* [cover parentID={E589FD7F-86DA-4aa9-8F8F-FA675DFD6438}]
        Report runtime DET error
        [/cover] */
      Det_ReportRuntimeError((uint16)FLS_17_DMU_MODULE_ID,
                             FLS_17_DMU_INSTANCE_ID,
                             FLS_17_DMU_SID_WRITE,
                             FLS_17_DMU_E_WRITE_FAILED);
#endif
      /* Call to Fls_lErrorHandler local function */
      Fls_lErrorHandler(FLS_17_DMU_WRITE);
      RetVal = E_NOT_OK;
    }
  }
  /* [cover parentID={109B909A-7693-4d33-8FCC-6914CD8A9E33}]
  Return
  [/cover] */
  return(RetVal);
}

#if (FLS_17_DMU_COMPARE_API == STD_ON)
/* [cover parentID={A971BDB0-9F06-428a-A954-D114299067FB}]
FLS COMPARE API is enabled
[/cover] */
/*******************************************************************************
** Traceability :[cover parentID={09A2E0A1-079D-41b3-B3A2-DBEDA142ABC2}]      **
**                                                                            **
** Syntax : Std_ReturnType Fls_17_Dmu_Compare(
**                                      Fls_17_Dmu_AddressType SourceAddress, **
**                                      const uint8 *TargetAddressPtr,        **
**                                     const Fls_17_Dmu_LengthType Length     **
**                                    );                                      **
**                                                                            **
** Service ID:  0x08                                                          **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :SourceAddress -  Source address in Flash memory.          **
** This address offset will be added to the flash memory base address.        **
**                  TargetAddressPtr - Pointer to target data buffer          **
**                  Length - Number of bytes to compare                       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: command has been accepted                         **
**                    E_NOT_OK: command has not been accepted                 **
**                                                                            **
** Description : Service for comparing the contents of an area of flash memory**
** with that of an application data buffer. This service shall copy the given **
** parameters to driver internal variables, initiate a compare job, set the   **
** driver status to MEMIF_BUSY, set the job result to MEMIF_JOB_PENDING       **
** and return with E_OK.                                                      **
*******************************************************************************/
Std_ReturnType Fls_17_Dmu_Compare( const Fls_17_Dmu_AddressType SourceAddress,
                                   const uint8 *const TargetAddressPtr,
                                   const Fls_17_Dmu_LengthType Length
                                 )
/*[cover parentID={48F60B5E-23BE-42c9-856D-E572D4367401}][/cover]*/
{
  Fls_17_Dmu_StateType   *StatePtr;
  volatile uint32 PhysicalAddress;
  uint8           JobType;
  Std_ReturnType  ReturnValue;
  /* Initialise Local variables */
  /* [cover parentID={32B578EC-FAAA-4a7e-86B6-A16FF31220D9}]
  Set the Return Value as OK
  [/cover] */
  ReturnValue = E_OK;

  /****************************** DET *****************************************/
  /* [cover parentID={141BC9A4-04FB-4dd9-A4EF-D29B75655BAE}]
  DET Enabled
  [/cover] */
#if( FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
                                   (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={F9010C56-EC3D-4407-87A1-DEC3A216E9DA}]
  Report DET error
  [/cover] */
  /* [cover parentID={874569B4-586A-4fb7-A0D3-4C7E705ECB34}]
  Is UNINIT Det error detected?
  [/cover] */
  if(Fls_lUninitDET(FLS_17_DMU_SID_COMPARE) == 1U)
  {
    /* [cover parentID={B281440C-ED41-47d8-B4CB-3590176399EC}]
    Set the Return Value as NOT OK
    [/cover] */
    ReturnValue = E_NOT_OK;
  }

  /*
   Checking whether given SourceAddress is valid or not
  */
  /* [cover parentID={F036BFD7-87BC-429e-93BC-5A0CCA67ABFF}]
  Is the given SourceAddress valid ?
  [/cover] */
  /*[cover parentID={2B120B27-3973-4088-A840-8637F0D4AB2C}][/cover]*/
  else if( SourceAddress >= FLS_17_DMU_TOTAL_SIZE )
  {
    /* [cover parentID={9F2FECA4-FAE5-4480-829F-77E92FDC809A}][/cover] */
    Fls_lReportError(
      FLS_17_DMU_SID_COMPARE,
      FLS_17_DMU_E_PARAM_ADDRESS
    );/* Report to DET */

    /* [cover parentID={B281440C-ED41-47d8-B4CB-3590176399EC}]
    Set the Return Value as NOT OK
    [/cover] */
    ReturnValue = E_NOT_OK;
  }

  /*
  Check for Pointer to an application buffer
  */
  /* [cover parentID={5523FD97-7681-47a9-8C5F-7A673E442E2B}]
  Is there any Pointer to an application buffer?
  [/cover] */
  else if(TargetAddressPtr == NULL_PTR)
  {
    /* [cover parentID={4A144583-41B1-4f65-A9D5-795C172A5387}][/cover] */
    Fls_lReportError(
      FLS_17_DMU_SID_COMPARE,
      FLS_17_DMU_E_PARAM_DATA
    );/* Report to DET */
    /* [cover parentID={B281440C-ED41-47d8-B4CB-3590176399EC}]
    Set the Return Value as NOT OK
    [/cover] */
    ReturnValue = E_NOT_OK;
  }
  /*
   Checking whether given Length is valid or not
  */
  /* [cover parentID={A57944B9-9512-4a2d-9154-03C2711F57B2}]
  Is the given Length valid ?
  [/cover] */
  /*[cover parentID={2B120B27-3973-4088-A840-8637F0D4AB2C}][/cover]*/
  else if((Length == 0U) || (Length > (FLS_17_DMU_TOTAL_SIZE - SourceAddress)))
  {
    /* [cover parentID={39483FE9-5476-47fe-9734-A56F8E6DAC0D}][/cover] */
    Fls_lReportError(
      FLS_17_DMU_SID_COMPARE,
      FLS_17_DMU_E_PARAM_LENGTH
    );/* Report to DET */
    /* [cover parentID={B281440C-ED41-47d8-B4CB-3590176399EC}]
    Set the Return Value as NOT OK
    [/cover] */
    ReturnValue = E_NOT_OK;
  }
  /* [cover parentID={B58F9527-A75E-427e-9375-0F5EB221B662}]
  Is the Flash driver busy?
  [/cover] */
  else if(Fls_lBusyDET_Compare(Fls_ConfigPtr->FlsStateVarPtr) == 1U)
  {
    ReturnValue = E_NOT_OK;
  }

  /* [cover parentID={8AB01410-36EA-4aa1-BED4-03BFD185EC90}]
  Is the FLS HW IDLE ?
  [/cover] */
  /*Check HW Busy*/
#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  else if(Fls_lHWBusyCheck() != 0U)
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID,FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_COMPARE, FLS_17_DMU_E_HW_BUSY);

    ReturnValue = E_NOT_OK;
  }
#endif
  else
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
    /**************************************************************************/
  {
    /* [cover parentID={73EF1706-206B-48f7-AA72-278D4E1850BB}]
    Update Job type to compare and Job result to job pending
    [/cover] */
    JobType = FLS_17_DMU_COMPARE;
    /*MISRA2012_RULE_11_8_JUSTIFICATION: Attempt to cast away const from a
    pointer. Solvable, but gives compiler warning. The address of the register
        is being passed.*/
    PhysicalAddress = (uint32)(FLS_17_DMU_BASE_ADDRESS + SourceAddress);
    StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
    /* 1. Set the flash job result to job pending */
    StatePtr->FlsJobResult = MEMIF_JOB_PENDING;

    /* [cover parentID={C70C4FD1-6C10-485d-97FD-B99498390558}]
    Store job parameters : Length/ target address pointer/ source address
    [/cover] */
    /*MISRA2012_RULE_11_8_JUSTIFICATION: Attempt to cast away const from a
       pointer. The const pointer is allocated to non-const pointer as
      buffer is to put the read data from FDFLASH0. */
    StatePtr->FlsReadBufferPtr = (uint8 *) TargetAddressPtr;
    /* Assigning Length to Global variable FlsReadLength*/
    StatePtr->FlsReadLength = Length;
    StatePtr->FlsReadAddress = PhysicalAddress;

    /*3. Update the new job on affected banks */
    StatePtr->FlsJobType = JobType;
  }
  /* [cover parentID={8452DB20-BF96-4947-8028-65EF39FD122D}]
  Return
  [/cover] */
  return(ReturnValue);
}
/* FLS_COMPARE_API == STD_ON */
#endif

#if (FLS_17_DMU_BLANK_CHECK_API == STD_ON)
/* [cover parentID={0BDE695E-8B9B-4be2-B844-BFB76B0C697D}]
FLS BLANK CHECK API is enabled
[/cover] */
/*******************************************************************************
** Traceability :  [cover parentID={A3F66C87-9D89-4f07-902F-2009EA91E6AB}]    **
**                                                                            **
** Syntax : Std_ReturnType Fls_17_Dmu_BlankCheck(                             **
**                                Fls_17_Dmu_AddressType TargetAddress        **
**                                const Fls_17_Dmu_LengthType Length          **
**                                    );                                      **
**                                                                            **
** Service ID:  0x0A                                                          **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :TargetAddress - Address in Flash memory from which the    **
**                   blank check should be started.                           **
**                  Length - Number of bytes to be checked for erase pattern  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: command has been accepted                         **
**                    E_NOT_OK: command has not been accepted                 **
**                                                                            **
** Description : This API is a Service is to verify, whether a given memory   **
** area has been erased but not (yet) programmed.                             **
*******************************************************************************/
Std_ReturnType Fls_17_Dmu_BlankCheck(
  const Fls_17_Dmu_AddressType TargetAddress,
  const Fls_17_Dmu_LengthType Length
)
/*[cover parentID={5C9703DD-3DEB-47d3-B1F2-AA6C8748DCCA}][/cover]*/
/* [cover parentID={DF1893ED-5581-422c-A14F-1F4A3E1213C1}][/cover] */
{
  Fls_17_Dmu_StateType   *StatePtr;
  volatile uint32 PhysicalAddress;
  uint8           JobType;
  Std_ReturnType  ReturnValue;

  /* Initialise Local variables */
  /* [cover parentID={7BAA6745-2325-4954-9414-4EE94D08E6DE}]
                Return value is OK
                [/cover] */
  ReturnValue = E_OK;

  /****************************** DET ***************************************/
  /* [cover parentID={890EBA3B-503E-4b1f-B193-8459AA2A92DF}]
  DET Enabled
  [/cover] */
#if( FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
                                       (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={9523B544-B5EA-4de1-B748-D0B82B11B04C}]
  Is Uninit DET error detected?
  [/cover] */
  /* [cover parentID={52A84A6A-F5E2-43ea-A49F-9B1F4BC39F7B}]
  Checking for Uninit DET
  [/cover] */
  if(Fls_lUninitDET(FLS_17_DMU_SID_BLANKCHECK) == 1U)
  {
    /* [cover parentID={C1A4EA1F-207C-452b-8573-FE785F6034F2}]
                Return value is NOT OK
                [/cover] */
    ReturnValue = E_NOT_OK;
  }
  /*[cover parentID={37693A7B-92C4-45bc-8D98-1155CBDAB4A8}]
  Does the start address lie beyond the specified lower and upper flash address
  boundaries?
  [/cover] */
  /*[cover parentID={2B120B27-3973-4088-A840-8637F0D4AB2C}][/cover]*/
  else if(TargetAddress >= FLS_17_DMU_TOTAL_SIZE)
  { /* [cover parentID={7FE697D6-9B33-440a-B417-D94DA4F8D19E}]
                 Report DET error
                 [/cover] */
    /* [cover parentID={9F2FECA4-FAE5-4480-829F-77E92FDC809A}][/cover] */
    /* [cover parentID={D307AF36-FA3A-45e1-834F-A2BA84BA6196}][/cover] */
    Fls_lReportError(
      FLS_17_DMU_SID_BLANKCHECK,
      FLS_17_DMU_E_PARAM_ADDRESS
    );/* Report to DET */

    ReturnValue = E_NOT_OK;
  }
  /* [cover parentID={FAF31B75-4A1F-4524-8B30-DFD9DEB5B66D}]
  Is the given length valid?
  [/cover] */
  /*   Checking whether given Length is valid or not  */
  /*[cover parentID={2B120B27-3973-4088-A840-8637F0D4AB2C}][/cover]*/
  else if(!(( Length >= FLS_ONE_VALUE) &&
            ( Length <= (FLS_17_DMU_TOTAL_SIZE - TargetAddress ))))
  {
    /* [cover parentID={F7106420-BFD6-411f-8D95-6761D5A96C44}]
                Report DET error
                [/cover] */
    /* [cover parentID={39483FE9-5476-47fe-9734-A56F8E6DAC0D}][/cover]
    */
    Fls_lReportError(
      FLS_17_DMU_SID_BLANKCHECK,
      FLS_17_DMU_E_PARAM_LENGTH
    );/* Report to DET */

    /* [cover parentID={C1A4EA1F-207C-452b-8573-FE785F6034F2}]
                    Return value is NOT OK
                    [/cover] */
    ReturnValue = E_NOT_OK;
  }
  /* [cover parentID={365469BA-536A-4c30-A73F-27F264936494}]
  Is the job type none?
  [/cover] */
  /* [cover parentID={52BC18CE-8E84-4d6d-99BE-8A7FB405EB37}]
  Is the HW IDLE ?
  [/cover] */
  else if (Fls_ConfigPtr->FlsStateVarPtr->FlsJobType != FLS_17_DMU_NONE)
  { /* [cover parentID={1F90F1CB-746A-40cf-8D42-4A3384B08521}][/cover] */
    Fls_lReportError(
      FLS_17_DMU_SID_BLANKCHECK,
      FLS_17_DMU_E_BUSY);/* Report to DET */
    /* [cover parentID={C1A4EA1F-207C-452b-8573-FE785F6034F2}]
    Return value is NOT OK
    [/cover] */
    ReturnValue = E_NOT_OK;
  }
#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  else if(Fls_lHWBusyCheck() != 0U)
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID,FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_BLANKCHECK, FLS_17_DMU_E_HW_BUSY);
    ReturnValue = E_NOT_OK;
  }
#endif
  else
#endif /* FLS_17_DMU_DEV_ERROR_DETECT == STD_ON */
    /*************************************************************************/
  {
    /* [cover parentID={01410584-CA77-4095-A9DC-D0FF7819B8A1}]
                Update job type to blankcheck and job result to pending
                [/cover] */
    JobType = FLS_17_DMU_BLANKCHECK;
    PhysicalAddress = (uint32)(FLS_17_DMU_BASE_ADDRESS + TargetAddress);
    StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
    /* 1. Set the flash job result to job pending */
    StatePtr->FlsJobResult = MEMIF_JOB_PENDING;

    /* Assigning Length to Global variable FlsReadLength*/
    /* [cover parentID={EB07BD14-21A1-4ef9-9615-DD3C11B544D5}]
    Store job parameters : Length/target address pointer/ source address
    [/cover] */
    StatePtr->FlsReadLength = Length;

    StatePtr->FlsReadAddress = PhysicalAddress;

    /*3. Update the new job  */
    StatePtr->FlsJobType = JobType;

  }
  return(ReturnValue);
}
/* FLS_BLANK_CHECK_API == STD_ON */
#endif


#if  (FLS_17_DMU_CANCEL_API  ==  STD_ON)
/* [cover parentID={CE9A0F7F-5EC5-488d-B9A5-1CE393C30D51}]
FLS cancel API is enabled
[/cover] */
/* [cover parentID={0A7233D3-B287-4cb8-8657-9D281BAC4F44}]
FLS cancel API is enabled
[/cover] */
/*******************************************************************************
** Traceability :  [cover parentID={818E8AB7-EAE0-4743-8C20-7BB75D96CBA5}]    **
**                                                                            **
** Syntax : void Fls_17_Dmu_Cancel(Void)                                      **
**                                                                            **
** Service ID:  0x03                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description :                                                              **
** Service for Canceling an ongoing flash job.                                **
** Read and Compare jobs will be cancelled immediately. Write and Erase jobs  **
** will be cancelled in driver immediately but hardware might still be busy   **
** until the ongoing operation is completed for the already issued commands   **
*******************************************************************************/
void Fls_17_Dmu_Cancel(void)
/*[cover parentID={3F2C37E5-7D99-4666-9665-28F9BF259443}][/cover]*/
{
  Fls_17_Dmu_StateType  *StatePtr;
  uint8 JobType;
  boolean JobCanceled;

  /* [cover parentID={94491FDE-D479-45ae-98A2-07217CF697DE}]
  DET enabled
  [/cover] */
#if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
                                         (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  /* API called before initialization */
  /* [cover parentID={29F6DEEF-E175-4eca-821A-CAD42FD988CA}]
  Check for Uninit DET error
  [/cover] */

  /* [cover parentID={F0B67590-5532-4535-92CA-EBB2C0626D4B}]
  [/cover] */
  if (Fls_lUninitDET(FLS_17_DMU_SID_CANCEL) == 0U)
#endif
  {
    StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
    JobType = StatePtr->FlsJobType;
    JobCanceled = (boolean)FALSE;

    /* [cover parentID={6F11E35F-B5E3-42a0-AEE1-724CB0135125}]
    Check for Uninit DET error
    [/cover] */
    /* Cancel WRITE Job */
    if(FLS_17_DMU_WRITE == JobType)
    {
      /* Set the JobType to NONE;
         This shall be done before calling Fls_lUnLoadAccessCode() */

      /* [cover parentID={5CCBA7C5-7031-4747-83F2-78643B4D5755}]
      From write to None
      [/cover] */
      StatePtr->FlsJobType = FLS_17_DMU_NONE;
      /*Exit critical section*/

      StatePtr->FlsJobResult = MEMIF_JOB_CANCELED;
      JobCanceled = (boolean)TRUE;

      /* Resetting the internal variables */
      /*[cover parentID={2B120B27-3973-4088-A840-8637F0D4AB2C}][/cover]*/
      StatePtr->FlsWriteAddress = (uint32)FLS_17_DMU_TOTAL_SIZE;
      StatePtr->FlsWriteLength = 0U;
      StatePtr->FlsWriteBufferPtr = NULL_PTR;
    }

    /*[cover parentID={E9DB0B1F-0429-4658-A05B-5178D548AC3E}][/cover]*/
    /* Cancel ERASE Job */
    else if(FLS_17_DMU_ERASE == JobType)
    {
      /*Enter critical section to prevent erase interrupt*/
      /* Set the JobType to NONE;
         This shall be done before calling Fls_lUnLoadAccessCode() */

      /*[cover parentID={8DD2D23A-49E2-4f6c-A46A-CB99D0DE1F33}]
       Job Type to None
       Set the job result to Canceled
       [/cover]*/
      StatePtr->FlsJobType = FLS_17_DMU_NONE;

      /*[cover parentID={D42B9C38-D63D-491d-B398-139CC145653A}]
      Set the job result to cancelled
      [/cover]*/
      StatePtr->FlsJobResult = MEMIF_JOB_CANCELED;
      JobCanceled = (boolean)TRUE;
    }

    /* [cover parentID= {5E7E6BE2-5808-4d6b-B1B5-9766259E5BED}]
    Cancel the ongoing job by making jobtype as none
    [/cover] */
    else if((FLS_17_DMU_READ == JobType) || (FLS_17_DMU_COMPARE == JobType))
    {
      /* Cancel READ / COMPARE Job */
      /* Set the JobType to NONE */

      StatePtr->FlsJobType = FLS_17_DMU_NONE;

      StatePtr->FlsJobResult = MEMIF_JOB_CANCELED;
      JobCanceled = (boolean)TRUE;

      /* [cover parentID={87473FA6-8270-4820-9B9C-5C3B473847C8}]
      Update job result as cancelled ( when the job result is PENDING,
      otherwise leave it unchanged)
      Resetting the internal variables
      (length, address and Buffer pointer)
      [/cover] */

      /*Reset internal variables after cancellation*/
      StatePtr->FlsReadBufferPtr = NULL_PTR;
      StatePtr->FlsReadLength = 0U;
      StatePtr->FlsReadAddress = (uint32)FLS_17_DMU_TOTAL_SIZE;
    }

    /* [cover parentID=  {84F0AAFB-59A4-4999-85D5-68774E3FF775}]
    [/cover] */
    else if(FLS_17_DMU_BLANKCHECK == JobType)
    {
      /* Set the JobType to NONE; */

      StatePtr->FlsJobType = FLS_17_DMU_NONE;

      StatePtr->FlsJobResult = MEMIF_JOB_CANCELED;
      JobCanceled = (boolean)TRUE;
    }

    /* [cover parentID={E82ABB8D-5F51-475c-8E55-3E42FCEC986D}]
    Make Jobtype as NONE
    [/cover] */
    else
    {
      /* Set the JobType to NONE */

      /* [cover parentID={9A9D41DB-2F11-4447-96D9-31DAE9CD084F}]
      Make Jobtype as NONE
      [/cover] */
      StatePtr->FlsJobType = FLS_17_DMU_NONE;
    }

    /* [cover parentID={86E9AD85-FE3A-4534-B8DD-423DB0620E33}]
    1. Rest the write and erase started status to not started.
    [/cover] */
    /* Reset JobStartStatus */
    StatePtr->JobStarted.Write = 0U;
    StatePtr->JobStarted.Erase = 0U;



    if((JobCanceled == (boolean)TRUE) &&
        (Fls_ConfigPtr->FlsJobErrorNotificationPtr != NULL_PTR)
      )
    {
      /* [cover parentID={9DDC4A9D-123A-4ac7-8539-ECE5F8B1F2AB}]
       Notification flag for FEE is set to Cancel Job
      [/cover] */
      StatePtr->NotifCaller = FLS_17_DMU_CANCEL_JOB;
      /* [cover parentID={DD52340F-C6D5-416b-B3A1-39B499069192}]
      Call FLS job error notification
      [/cover] */
      /* [cover parentID={F3DF12FB-EC06-455a-B0A2-2DAAAE766369}]
      Call FLS job error notification
      [/cover] */
      /* FlsJobErrorNotificationPtr should be called */
      (Fls_ConfigPtr->FlsJobErrorNotificationPtr)();
      /* [cover parentID={0265A23C-D907-426e-A17E-358B707B470E}]
      Set the FEE notification flag to No Job
      [/cover] */
      StatePtr->NotifCaller = FLS_17_DMU_NO_JOB;
    }

  }

}

#endif /* #if (FLS_CANCEL_API == STD_ON) */

/*******************************************************************************
** Traceability : [cover parentID={2286DD54-0A69-45e6-ADFD-CC09F66B2688}]     **
**                                                                            **
** Syntax : void Fls_17_Dmu_CancelNonEraseJobs(void)                          **
**                                                                            **
** Service ID: 0x28                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description :                                                              **
** Service for Canceling an ongoing flash jobs except the erase job.          **
** Read and Compare jobs will be cancelled immediately. Write job             **
** will be cancelled in driver immediately but hardware might still be busy   **
** until the ongoing operation is completed for the already issued commands   **
*******************************************************************************/
void Fls_17_Dmu_CancelNonEraseJobs(void)
/*[cover parentID={2EFCDB48-187B-4d13-A230-B0C7BE5BFAEA}][/cover]*/
{
  Fls_17_Dmu_StateType  *StatePtr;
  uint8 JobType;
  boolean JobCanceled;

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  JobType = StatePtr->FlsJobType;
  JobCanceled = (boolean)FALSE;

  /* [cover parentID={18974E21-105B-4812-AFBF-EC3EE210D1D3}]
  Is there any ongoing Job ?
  [/cover] */
  /* Cancel WRITE Job */
  if(FLS_17_DMU_WRITE == JobType)
  {
    /* [cover parentID={302F4467-5E2A-42db-8C9E-981AEB4BD72C}]
    Set the Job Type to FLS_NONE.
    [/cover] */
    StatePtr->FlsJobType = FLS_17_DMU_NONE;

    /*
    Set the result of job as cancelled if it was marked as pending
    */
    StatePtr->FlsJobResult = MEMIF_JOB_CANCELED;

    JobCanceled = (boolean)TRUE;

    /* Reset JobStart Status */
    StatePtr->JobStarted.Write = 0U;

  }
  /* Cancel READ / COMPARE / BlankCheck Job */
  else if((FLS_17_DMU_READ == JobType) || (FLS_17_DMU_COMPARE == JobType) || \
          (FLS_17_DMU_BLANKCHECK == JobType))
  {
    /* [cover parentID={1A9B312D-8DEB-4a5d-A2E5-8D10CF13FF6D}]
    1. Set the result of job as cancelled if it was marked as pending.
    2. Cancel the ongoing job by making jobtype as none.
    3. Set Job Cancel flag to True.
    [/cover] */
    StatePtr->FlsJobType = FLS_17_DMU_NONE;

    StatePtr->FlsJobResult = MEMIF_JOB_CANCELED;

    JobCanceled = (boolean)TRUE;
  }

  else
  {
    /* Reset JobType of Non-Erase Job */

    StatePtr->FlsJobType = ((JobType == FLS_17_DMU_ERASE) ?
                            FLS_17_DMU_ERASE : FLS_17_DMU_NONE);

  }

  /* Set the NotifCaller to Cancel Job */


  if((JobCanceled == (boolean)TRUE) &&
      (Fls_ConfigPtr->FlsJobErrorNotificationPtr != NULL_PTR)
    )
  {
    /* [cover parentID={44BCC7FD-9B85-4b8b-A8C1-6586C4BF8476}]
    Set the Notification flag to CANCEL_JOB
    [/cover] */
    Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_CANCEL_JOB;
    /* FlsJobErrorNotificationPtr should be called */
    /* [cover parentID={D448B972-5866-4b69-B9B7-57AAD957B0F4}]
    Call FlsJobErrorNotificationPtr
    [/cover] */
    (Fls_ConfigPtr->FlsJobErrorNotificationPtr)();
    /* [cover parentID={92FB03DC-A95C-4cec-BBD8-3009629BF38D}]
    Set the notification pointer to FLS_NO_JOB
    [/cover] */
    Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_NO_JOB;
  }

}

/*******************************************************************************
** Traceability : [cover parentID={CB676030-CE4D-4b2d-B0FB-14DB3947C53D}]     **
**                                                                            **
** Syntax : void Fls_17_Dmu_SetMode(const MemIf_ModeType Mode)                **
**                                                                            **
** Service ID:  0x09                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : Mode MEMIF_MODE_SLOW:                                    **
**                        Slow read access                                    **
**                                                                            **
**                        MEMIF_MODE_FAST:                                    **
**                        Fast read access                                    **
**                                                                            **
** Parameters (out): : None                                                   **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This API sets the Flash driver's operation mode.             **
**               FAST or SLOW mode impacts only Read/Compare operations.      **
**               Based on the currently active mode, the number of bytes to be**
**               read from Flash in each call of Fls_17_Dmu_MainFunction is   **
**               taken from the configuration                                 **
*******************************************************************************/
#if  (FLS_17_DMU_SET_MODE_API  ==  STD_ON)
/* [cover parentID={009D9D83-81EA-4acc-81B2-9064BFD98A2D}]
FLS SET MODE API  is enabled
[/cover] */
/* [cover parentID={887E1F26-1DC2-4b3d-967A-49E35D53B742}][/cover] */
void Fls_17_Dmu_SetMode(const MemIf_ModeType Mode)
{
  /* [cover parentID={750FE6BF-FE76-4ad6-AE35-13ABFF0A450E}]
  DET Enabled
  [/cover] */
#if  ( FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
                                        (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  uint8 JobType;
  if (Fls_lUninitDET(FLS_17_DMU_SID_SETMODE) == 0U)
  {
    JobType = Fls_ConfigPtr->FlsStateVarPtr->FlsJobType;
    /* Check if the driver is BUSY */
    /* [cover parentID={6CAF01FF-2D18-4e15-8852-65E33436C658}]
    Is the driver busy?
    [/cover] */
    if( JobType != FLS_17_DMU_NONE )
    {
      /* [cover parentID={01F518B7-444B-4946-8602-F01AA7A4489C}]
      Report DET error
      [/cover] */
      /* [cover parentID={1F90F1CB-746A-40cf-8D42-4A3384B08521}][/cover] */
      Fls_lReportError(FLS_17_DMU_SID_SETMODE,
                       FLS_17_DMU_E_BUSY);/* Report to DET */
    }
#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
    else if ((MEMIF_MODE_SLOW != Mode) && (MEMIF_MODE_FAST != Mode))
    {
      Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID,FLS_17_DMU_INSTANCE_ID,
                             FLS_17_DMU_SID_SETMODE,
                             FLS_17_DMU_E_PARAM_INVLD);
    }
#endif
    else
#endif
    { /* [cover parentID={C93A086D-8E9B-43d1-B373-57F389935F09}]
      Set flash driver's operation mode
      [/cover] */
      Fls_ConfigPtr->FlsStateVarPtr->FlsMode = Mode;
    }
    /* [cover parentID={A019C01B-F6EC-4a90-A07E-5970D6A6BA4C}][/cover] */
#if  ( FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
                                 (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  }
#endif
}
#endif


/*******************************************************************************
** Traceability : [cover parentID={18730333-536B-494d-8FB0-10F16F44A4A0}]     **
**                                                                            **
** Syntax : void Fls_17_Dmu_MainFunction(void)                                **
**                                                                            **
** Service ID:  0x06                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out): : None                                                   **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description :                                                              **
** This service shall perform the processing of the flash read,write          **
**         and erase jobs                                                     **
*******************************************************************************/
void Fls_17_Dmu_MainFunction(void)
/* [cover parentID={D100ACCD-70B7-4226-B004-79439A1FC37F}]
Fls_17_Dmu_MainFunction [/cover] */
/* [cover parentID={BF6D9ACD-AC47-4231-A2B6-917D4FF7432D}][/cover] */
{
  const Fls_17_Dmu_StateType  *StatePtr;
  uint8 JobType;
  uint8 ErrorUninitFlag=0U;
  /* [cover parentID={68813369-F249-48f9-B216-C4313DCB2E4F}]
  DET Enabled
  [/cover] */
#if  ( FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
                                       (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  uint8 ErrorTimeoutFlag;
  /* API  called before initialization */
  /* [cover parentID={6752ADFF-BE6E-4e06-913D-865E8A0603A7}]
  Report DET error
  [/cover] */
  ErrorUninitFlag = Fls_lUninitDET(FLS_17_DMU_SID_MAIN);
  if (ErrorUninitFlag == 0U)
    /* [cover parentID={7B21429D-9466-458d-9427-024A5BAAA05E}]
    Check for Uninit DET error
    [/cover] */
  {
    /* [cover parentID={2AB8D16D-C1D1-4da7-8F50-942FC3C04B64}]
    Check for Timeout Det error
    [/cover] */
    /* [cover parentID={6752ADFF-BE6E-4e06-913D-865E8A0603A7}]
    Report DET error
    [/cover] */
    ErrorTimeoutFlag = Fls_lTimeOutDET(FLS_17_DMU_SID_MAIN);
    if (ErrorTimeoutFlag == 0U)
      /* [cover parentID={B6F16F30-2B1D-4b3f-B72C-EDA57875D761}]
      Is Timeout DET error detected?
      [/cover] */
#else
  if((Fls_ConfigPtr == NULL_PTR) || (FLS_INITIALIZED != Fls_17_Dmu_InitStatus))
  {
    ErrorUninitFlag = 1;
  }

  if (ErrorUninitFlag == 0U)
#endif
    {
      StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
      JobType = StatePtr->FlsJobType;

      if( JobType != FLS_17_DMU_NONE)
      {
        /* Check for any Flash operation is ongoing? */
        if( Fls_lHWBusyCheck() == 0U)
        {
          switch(JobType)
            /* [cover parentID={0FA15697-671E-43a0-AAA1-1899866E810E}]
            Get the type of the pending job
            [/cover] */

          {
              /*[cover parentID={88F8A5C9-CCDB-40bd-A8A2-5DB65E9BA807}][/cover]
              */
#if(FLS_17_DMU_USE_INTERRUPTS == STD_OFF)
            /* [cover parentID={B03F208B-EDD7-42bd-A1B1-EEA16BC402B4}]
            Interrupt Disabled
            [/cover] */
/******************************** ERASE **********************************/
            case FLS_17_DMU_ERASE:
              {
                /* Fls_Main_Erase operation should be called  */
                /* [cover parentID={0366A308-A442-4d97-95CA-70DE34BBC2D2}]
                Call Local Main Erase Function
                [/cover] */
                Fls_lMainErase();
              }
              break;
/******************************** WRITE ************************************/
            case FLS_17_DMU_WRITE:
              {
                /* Fls_Main_Write operation should be called  */
                /* [cover parentID={EC5806CB-46DD-43d9-A0FE-B6F5C20050DB}]
                Call Local Main Write Function
                [/cover] */
                Fls_lMainWrite();
              }
              break;
              /* FLS_USE_INTERRUPTS == STD_OFF */
#endif
/******************************** READ **************************************/
            case FLS_17_DMU_READ:
              {
                /* Fls_Main_Read operation should be called  */
                /* [cover parentID={2C284258-AFB5-422a-9652-A64A65D4217D}]
                Call Local Main Read Function
                [/cover] */
                Fls_lMainRead();
              }
              break;
/****************************** COMPARE ************************************/
            case FLS_17_DMU_COMPARE:
              {
                /* Fls_Main_Compare operation should be called  */
                /* [cover parentID={533B372F-9552-4912-B8EB-6B4F880AD80D}]
                Call Local Main Comapre Function
                [/cover] */
                Fls_lMainCompare();
              }
              break;
/****************************** BLANK CHECK ***********************************/
            case FLS_17_DMU_BLANKCHECK:
              {
                /* Fls_Main_BlankCheck operation should be called  */
                /* [cover parentID={218A069E-51B9-441e-A2EE-6A32EDDBE2E2}]
                Call Local Main Blank Check Function
                [/cover] */
                Fls_lMainBlankCheck();
              }
              break;
            default:
              {
                /* Do nothing - To avoid MISRA warning */
              }
              break;
          }
        }
      }
#if  ( FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
                                     (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
    }
#endif
  }
  /* [cover parentID={DE6A282F-9FFE-43a0-A515-0A3EF92B213E}][/cover] */
}


/*******************************************************************************
** Traceability : [cover parentID={2A9A31FE-C2D1-47ca-9A22-3F281024F0A2}]     **
**                                                                            **
** Syntax : Std_ReturnType Fls_17_Dmu_Read(
**                                   Fls_17_Dmu_AddressType SourceAddress,    **
**                                   uint8 *TargetAddressPtr,                 **
**                              const Fls_17_Dmu_LengthType Length            **
**                                 );                                         **
**                                                                            **
** Service ID:  0x07                                                          **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : SourceAddress,TargetAddressPtr and Length                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: command has been accepted                         **
**                    E_NOT_OK: command has not been accepted                 **
**                                                                            **
** Description : Service for reading from flash memory. This service copies   **
** the given parameters to driver internal variables, set driver status to    **
** MEMIF_BUSY and job result to MEMIF_JOB_PENDING.                            **
*******************************************************************************/
Std_ReturnType Fls_17_Dmu_Read(const Fls_17_Dmu_AddressType SourceAddress,
                               uint8 *const TargetAddressPtr,
                               const Fls_17_Dmu_LengthType Length)
/* [cover parentID={F945E4D5-BEB5-4055-B6F7-33D2A6F0B2A4}][/cover] */
{
  Fls_17_Dmu_StateType  *StatePtr;
  volatile uint32 PhysicalAddress;
  Std_ReturnType ReturnValue;
  uint8 JobType;

  /* Initialise Local variables */
  /* [cover parentID={6E4AF82B-7708-4645-8CA5-FE72D28D3474}]
  Set the Return Value as OK
  [/cover] */
  ReturnValue = (Std_ReturnType)E_OK;

  /**************************** DET ******************************************/

  /* [cover parentID={9FDC9E89-EF19-47c1-B186-5BC98FC13F5B}]
  DET Enabled
  [/cover] */
#if  ( FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
                                     (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  /*  API  called before initialization */
  /* [cover parentID={EF160363-0D89-4fb2-8950-26584F81C13A}]
  Is Uninit Det error detected?
  [/cover] */
  if(Fls_lUninitDET(FLS_17_DMU_SID_READ) == 1U)
  {
    /* [cover parentID={1281120B-29EA-4864-8DC0-A4CDAF6C217E}]
    Set the Return Value as NOT OK
    [/cover] */

    ReturnValue = E_NOT_OK;
  }
  /*  Checking whether given SourceAddress is valid or not */
  /* [cover parentID={D0FB4705-8153-40cd-A224-9DEDFAF46501}]
  Is the given Source Address valid?
  [/cover] */
  /*[cover parentID={2B120B27-3973-4088-A840-8637F0D4AB2C}][/cover]*/
  else if(SourceAddress >= (FLS_17_DMU_TOTAL_SIZE))
  {
    /* [cover parentID={DEF6F07D-0960-4930-9AD3-EA6589D169BA}]
    Report DET error
    [/cover] */
    /* [cover parentID={9F2FECA4-FAE5-4480-829F-77E92FDC809A}][/cover] */
    Fls_lReportError(FLS_17_DMU_SID_READ,
                     FLS_17_DMU_E_PARAM_ADDRESS);/* Report to DET */

    ReturnValue = E_NOT_OK;
    /* [cover parentID={1281120B-29EA-4864-8DC0-A4CDAF6C217E}]
    Set the Return Value as NOT OK
    [/cover] */

  }
  /*Check for Pointer to an application buffer*/
  /* [cover parentID={671138DB-C22D-4e38-8F87-676B02CA6475}]
  Is there a Pointer to an application buffer?
  [/cover] */
  else if(TargetAddressPtr == NULL_PTR)
  {
    /* [cover parentID={DEF6F07D-0960-4930-9AD3-EA6589D169BA}]
    Report DET error
    [/cover] */
    /* [cover parentID={4A144583-41B1-4f65-A9D5-795C172A5387}][/cover] */
    Fls_lReportError(FLS_17_DMU_SID_READ,
                     FLS_17_DMU_E_PARAM_DATA);/* Report to DET */

    ReturnValue = E_NOT_OK;
    /* [cover parentID={1281120B-29EA-4864-8DC0-A4CDAF6C217E}]
    Set the Return Value as NOT OK
    [/cover] */

  }
  /* Checking whether given Length is valid or not */
  /* [cover parentID={4CCB86DF-F9A8-4690-9AC6-EA988D47BC05}]
  Is the given Length valid?
  [/cover] */
  /*[cover parentID={2B120B27-3973-4088-A840-8637F0D4AB2C}][/cover]*/
  else if((Length < FLS_ONE_VALUE) ||
          (Length > (FLS_17_DMU_TOTAL_SIZE - SourceAddress)))
  {
    /* [cover parentID={DEF6F07D-0960-4930-9AD3-EA6589D169BA}]
     Report DET error
     [/cover] */
    /* [cover parentID={39483FE9-5476-47fe-9734-A56F8E6DAC0D}][/cover]*/
    Fls_lReportError(FLS_17_DMU_SID_READ,
                     FLS_17_DMU_E_PARAM_LENGTH);/* Report to DET */

    ReturnValue = E_NOT_OK;
    /* [cover parentID={1281120B-29EA-4864-8DC0-A4CDAF6C217E}]
     Set the Return Value as NOT OK
     [/cover] */

  }

  /* [cover parentID={8DE1B39A-A277-4108-98C2-BCF4BC933AFB}]
  If the new Read job can be accepted? ( busy check)
  [/cover] */
  else if(Fls_lBusyDET_Read(Fls_ConfigPtr->FlsStateVarPtr) == 1U)
  {
    ReturnValue = E_NOT_OK;
  }
  else
#endif
    /*************************************************************************/
  {
    if(Fls_lHWBusyCheck() == 0U)
    {
      /*Assign jobtype to read */
      /* [cover parentID={735FD7FA-90EA-45ab-B927-643A6BC0CC6D}]
      Update the physical address to the base address plus the given source address
      Update job result to pending/ Store job parameters/ Update the job type to
      Read
      [/cover] */
      JobType = FLS_17_DMU_READ;
      PhysicalAddress = (uint32)(FLS_17_DMU_BASE_ADDRESS + SourceAddress);
      StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
      /* 2. Set the flash job result to job pending */
      StatePtr->FlsJobResult = MEMIF_JOB_PENDING;

      /* Assigning TargetAddressPtr to Global variable FlsReadBufferPtr */
      StatePtr->FlsReadBufferPtr = TargetAddressPtr;
      /* [cover parentID={E0319812-0D46-4ee8-A535-A8E760315388}]
      Assigning TargetAddressPtr to Global variable Read Buffer Pointer
      Assigning Length to Global variable FlsReadLength
      [/cover] */

      /* Assigning Length to Global variable FlsReadLength*/
      StatePtr->FlsReadLength = Length;

      StatePtr->FlsReadAddress = PhysicalAddress;

      /*3. Update the new job on affected banks */
      StatePtr->FlsJobType = JobType;
    }
    else
    {
#if(FLS_17_DMU_SAFETY_ENABLE == STD_ON)
      Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID,FLS_17_DMU_INSTANCE_ID,
                             FLS_17_DMU_SID_READ, FLS_17_DMU_E_HW_BUSY);
#endif
      ReturnValue = E_NOT_OK; /*HW is busy*/
    }
  }
  /* [cover parentID={F93086E6-451A-482b-BEDE-9F1E1DDA6E73}]
  Return
  [/cover] */
  return(ReturnValue);
}

#if (FLS_17_DMU_GET_STATUS_API == STD_ON)
/* [cover parentID={6DB028BA-3A97-4152-ABD0-2D5BD566D3B3}]
FLS get status API  is enabled
[/cover] */
/*******************************************************************************
** Traceability : [cover parentID={5C6365D7-79D7-459f-BEB7-A89C359F9399}]     **
**                                                                            **
** Syntax : MemIf_StatusType Fls_17_Dmu_GetStatus(void)                       **
**                                                                            **
** Service ID:  0x04                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Re-entrant                                                    **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out): : None                                                   **
**                                                                            **
** Return value    :  MemIf_StatusType - The state of the driver              **
**                                                                            **
** Description :                                                              **
** This service shall return the driver state synchronously                   **
*******************************************************************************/
MemIf_StatusType Fls_17_Dmu_GetStatus(void)
/*[cover parentID={59FF2D8F-716D-43e2-B59E-7D3D1A27A5DA}][/cover]*/
{
  MemIf_StatusType ReturnValue;
  uint8 JobType;

  if((Fls_ConfigPtr == NULL_PTR) || (FLS_INITIALIZED != Fls_17_Dmu_InitStatus))
  {
    /* [cover parentID={B08669D6-885F-42d8-806C-2ECED4ED1F9A}]
    Is the driver initialised?
    [/cover] */
    /* [cover parentID={FEF1E417-BE22-440b-87E3-C2FD830ABA70}]
    Return - Driver is not initialized
    MEMIF_UNINIT
    [/cover] */
    ReturnValue = MEMIF_UNINIT;
  }
  else
  {
    JobType = Fls_ConfigPtr->FlsStateVarPtr->FlsJobType;

    if((JobType != FLS_17_DMU_NONE))
    {
      /* [cover parentID={8C1B9220-1A20-49c0-A932-74F4A21C8D59}]
      Return flash status as busy
      MEMIF_BUSY
      [/cover] */
      ReturnValue = MEMIF_BUSY;
    }
    else
    {
      /* [cover parentID={CB7B8DE8-3A82-4564-A0F4-C0BC212E4F6A}]
      Return flash status as idle
      MEMIF_IDLE
      [/cover] */
      ReturnValue = MEMIF_IDLE;
    }
  }
  /*  Service shall return driver state synchronously. */
  return(ReturnValue);
} /* End of Function: Fls_GetStatus */


#endif

#if  (FLS_17_DMU_GET_JOB_RESULT_API  ==  STD_ON)
/* [cover parentID={B3673CCA-93F4-4262-B34E-4DCDBA625906}]
Get job result API is enabled
[/cover] */
/*******************************************************************************
** Traceability : [cover parentID={FBF001A4-D07E-4b03-8FA8-5C020552B5D6}]     **
**                                                                            **
** Syntax : MemIf_JobResultType Fls_17_Dmu_GetJobResult(void)                 **
**                                                                            **
** Service ID:  0x05                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Re-entrant                                                    **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out): : None                                                   **
**                                                                            **
** Return value    :  MemIf_JobResultType  - The result of the last job       **
**                                                                            **
** Description :                                                              **
**         This service shall return the result of the last job synchronously **
*******************************************************************************/
MemIf_JobResultType Fls_17_Dmu_GetJobResult(void)
/* [cover parentID={BDC1DA1D-8384-4ca0-9EA1-AD0E33D37102}][/cover] */
{

  MemIf_JobResultType RetVal;
  /* [cover parentID={A5F084DF-5708-4ac2-933E-B241D4E0A3E2}]
  Update the local state pointer by the global configuration values
  Return the FLS Job Result (for the last job) stored by the Flash Driver
  [/cover] */


  /* [cover parentID={F08DCF6B-684A-474e-89FE-F32D9B941CF5}]
  DET Enabled
  [/cover] */
#if  ( FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
                               (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  /*  API  called before initialization */
  /* [cover parentID={624E029E-8CC6-418f-B8C6-17BB642D8A61}]
  Check for Uninit DET error
  [/cover] */

  /* [cover parentID={E9039619-FDF4-438b-A228-DB8EF06B29D7}]
  Check for Uninit DET error
  [/cover] */
  if (Fls_lUninitDET(FLS_17_DMU_SID_GETJOBRESULT) != 0U)
  {
    /* [cover parentID={B8DBD4BB-DA12-46f6-896B-51F7D7DCF1DC}]
    Return : Job failed
    [/cover] */
    RetVal = MEMIF_JOB_FAILED;
  }
  else
#endif
  {
    RetVal = Fls_ConfigPtr->FlsStateVarPtr->FlsJobResult;
  }

  return(RetVal);
}
#endif
/*FLS_GET_JOB_RESULT_API == STD_ON */

#if (FLS_17_DMU_IFX_FEE_USED == STD_ON)
/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax : Std_ReturnType Fls_17_Dmu_ReadWordsSync(                          **
**                                const Fls_17_Dmu_AddressType SourceAddress, **
**                                           const uint32 *TargetAddressPtr,  **
**                                           uint32 Length                    **
**                                         );                                 **
**                                                                            **
** Service ID:  0x21                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : SourceAddress, TargetAddressPtr and Length               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Read successful                                    **
**                   E_NOT_OK: HW busy or read failed with ECC error          **
**                                                                            **
** Description : Service for reading word data from flash bank synchronously  **
*******************************************************************************/
Std_ReturnType Fls_17_Dmu_ReadWordsSync(
  const Fls_17_Dmu_AddressType SourceAddress,
  uint32 *const TargetAddressPtr,
  const uint32 Length)
/*[cover parentID={0E143A6B-82CC-4526-89DC-A33334872FB0}][/cover]*/
{
  Fls_17_Dmu_StateType  *StatePtr;
  uint8 JobType;
  volatile uint32 PhysicalAddress;
  Std_ReturnType RetVal;
  const uint32 *SrcPtr;
  uint32 *DestPtr;
  uint32 LengthChk;
  uint32 BitChange;

  /* [cover parentID={AC6F2839-EEDA-4960-9BE9-D7B6B8B47544}]
  Set the return value as E_OK
  [/cover] */
  RetVal = E_OK;

#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)

  /*  Checking whether given SourceAddress is valid or not */
  if((SourceAddress >= (FLS_17_DMU_TOTAL_SIZE)) ||
      (((Fls_17_Dmu_AddressType)SourceAddress & FLS_WORD_SIZE_MASK)!=0U))
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_READSYNC, FLS_17_DMU_E_PARAM_ADDRESS);

    RetVal = E_NOT_OK;
  }
  /*Check for Pointer to an application buffer*/
  else if(TargetAddressPtr == NULL_PTR)
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_READSYNC, FLS_17_DMU_E_PARAM_DATA);

    RetVal = E_NOT_OK;
  }
  /* Checking whether given Length is valid or not */
  else if((Length < FLS_ONE_VALUE) ||
          (Length > (FLS_17_DMU_TOTAL_SIZE - SourceAddress)))
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID,FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_READSYNC, FLS_17_DMU_E_PARAM_LENGTH);

    RetVal = E_NOT_OK;
  }
  /* [cover parentID={65D72724-2220-4887-A71C-D858DFD9F778}]
  Is the flash HW busy?
  [/cover] */
  else if(Fls_lHWBusyCheck() != 0U)
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID,FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_READSYNC, FLS_17_DMU_E_HW_BUSY);
    RetVal = E_NOT_OK;
  }
  else
#endif
  {
    StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
    JobType = StatePtr->FlsJobType;


    PhysicalAddress = (uint32)( FLS_17_DMU_BASE_ADDRESS + SourceAddress );

    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
    type is required to access the FLASH address/target address which
    is defined as unsigned long. */
    /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
      is required to check the value of the address of data buffer alignment. */
    SrcPtr = (uint32*)PhysicalAddress;

    DestPtr = (uint32*)TargetAddressPtr;

    LengthChk=(uint32)Length;

    /* [cover parentID={37D0FA7F-BE27-46ff-9A46-9BB3CDD69FDF}]
    Is there any ongoing job?
    [/cover] */
    /* Check if no operation ongoing */
    if(JobType == FLS_17_DMU_NONE)
    {
      /* Modify the GlobalVar JobType so that no new requests can be accepted on
      *the Bank till ReadSync is finished */
      StatePtr->FlsJobType = FLS_17_DMU_READSYNC;

      /*Clear the ECC status bits by writing DMU_HF_ECCC.CLR with 11b to clear
           AERM bit*/

      BitChange= DMU_HF_ECCC.U | FLS_DMU_ECCC_CLR;

      /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
       the object types as the address of the register is being passed.*/
      FLS_17_DMU_LIB_RUNTIME_WRITECPUENDINITPROTREG(\
          (volatile uint32 *)&DMU_HF_ECCC.U, \
          BitChange);

      /*There is a delay of 2-3 cycles in the clearing of AERM bit*/
      NOP();
      NOP();
      NOP();

      /* [cover parentID={92085615-E122-4214-8582-814D822E9A61}]
      1. Read word from flash
      2. Decrease length
      3. Increase physical address
      [/cover] */

      /* Read the data */
      do
      {
        *DestPtr = *SrcPtr;
        /* Point to the next word */
        DestPtr++;
        /* Increment by one word */
        SrcPtr++;
        LengthChk--;
      } while(LengthChk > 0U);

      /* Restore the JobType with previous tasks */
      StatePtr->FlsJobType = FLS_17_DMU_NONE;

      /* Check for uncorrectable bit error */
      /* [cover parentID={3E0984C3-E497-489e-9384-BCB4A6069132}]
      Check for uncorrectable ECC errors
      [/cover] */
      /* [cover parentID={C15185C5-63ED-4af3-9B33-BD3F59CD0B67}]
      Is uncorrectable ECC error detected?
      [/cover] */
      if(Fls_lChkBitErrors() != 0U)
      {
        /* FLS106: Read Job fails due to hardware error */
        /* Report Runtime error code to DET */

        /* [cover parentID={08D70AA1-BCC2-406c-86F6-130AE6134FEE}]
        RUNTIME ERROR detection enabled
        [/cover] */

#if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
        /* [cover parentID={79096AEA-511E-40bb-AD3D-345B7E5A75CF}]
        Report Runtime error code to DET
        [/cover] */
        /*[cover parentID={6F22C8E9-7345-4936-9BD1-F7D343DB53B5}][/cover] */
        Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                                FLS_17_DMU_INSTANCE_ID,
                                FLS_17_DMU_SID_READSYNC,
                                FLS_17_DMU_E_READ_FAILED);
#endif
        /* [cover parentID={AEA1E1B5-AFE7-411a-9ADD-B03DA1485261}]
        SynchA
        [/cover] */
        /* Return E_NOT_OK */
        RetVal = E_NOT_OK;
      }
    }
    else
    {
#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
      Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                             FLS_17_DMU_SID_READSYNC, FLS_17_DMU_E_BUSY);
#endif
      RetVal = E_NOT_OK;
    }
  }
  return(RetVal);
}


/*******************************************************************************
** Traceability : [cover parentID={071F2EBB-AF4C-4744-89F8-D802E4DDB976}]     **
**                                                                            **
** Syntax : Std_ReturnType Fls_17_Dmu_CompareWordsSync(                       **
**                              const Fls_17_Dmu_AddressType SourceAddress,   **
**                                     const uint32 *const TargetAddressPtr,  **
**                                     const uint32 Length);                  **
**                                                                            **
** Service ID: 0x22                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : SourceAddress - Source address in Flash memory.          **
**          This address offset is added to the flash memory base address     **
**                   TargetAddressPtr - Pointer to target data buffer         **
**                   Length - Number of words to be compared. It takes the    **
**                   value from 1 to Flash Size                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Compare successful                                 **
**                   E_NOT_OK: HW busy or compare failed or ECC error         **
**                                                                            **
** Description : Service for comparing data from flash bank synchronously     **
*******************************************************************************/
Std_ReturnType Fls_17_Dmu_CompareWordsSync(
  const Fls_17_Dmu_AddressType SourceAddress,
  const uint32 *const TargetAddressPtr,
  const uint32 Length)
/* [cover parentID={EA54EE68-6A30-4a38-A981-DD82346FC1A1}][/cover] */
{
  Fls_17_Dmu_StateType  *StatePtr;
  uint8 JobType;

  volatile uint32 PhysicalAddress;
  Std_ReturnType RetVal;
  const uint32 *SrcPtr;
  uint32 CompLen;
  uint32 BitChange;
  uint32 IndexTargetAddressPtr;


  RetVal = E_OK;

  IndexTargetAddressPtr=0;

#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  /*  Checking whether given SourceAddress is valid or not */
  if((SourceAddress >= (FLS_17_DMU_TOTAL_SIZE)) ||
      (((uint32)SourceAddress & FLS_WORD_SIZE_MASK)!=0U))
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_COMPARESYNC, FLS_17_DMU_E_PARAM_ADDRESS);

    RetVal = E_NOT_OK;
  }
  /*Check for Pointer to an application buffer*/
  else if(TargetAddressPtr == NULL_PTR)
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_COMPARESYNC, FLS_17_DMU_E_PARAM_DATA);

    RetVal = E_NOT_OK;
  }
  /* Checking whether given Length is valid or not */
  else if((Length < FLS_ONE_VALUE) ||
          (Length > (FLS_17_DMU_TOTAL_SIZE - SourceAddress)))
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_COMPARESYNC, FLS_17_DMU_E_PARAM_LENGTH);

    RetVal = E_NOT_OK;
  }/*Range Check Over*/

  /* [cover parentID={77BFA20F-CA11-46b5-9298-458699DBD7FF}]
  Is flash HW busy?
  [/cover] */
  else if(Fls_lHWBusyCheck() != 0U)/*HW Busy check*/
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_COMPARESYNC, FLS_17_DMU_E_HW_BUSY);
    RetVal = E_NOT_OK;
  }
  else
#endif
  {

    StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
    JobType = StatePtr->FlsJobType;
    CompLen = Length;

    PhysicalAddress = (uint32)( FLS_17_DMU_BASE_ADDRESS + SourceAddress);

    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
           type is required to access the FLASH address/target address which
           is defined as unsigned long. */
    /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
      is required to check the value of the address of data buffer alignment. */
    SrcPtr = (uint32*)PhysicalAddress;
    /* Check if no operation ongoing */
    if(JobType == FLS_17_DMU_NONE)
    {
      /* Modify the GlobalVar JobType so that no new requests can be accepted on
      the Bank till CompareSync is finished */
      /* [cover parentID={59CE9E38-7367-44ac-8B70-73D939397B9B}]
      Update the job type to comparesync
      [/cover] */
      StatePtr->FlsJobType = FLS_17_DMU_COMPARESYNC;

      /*Clear the ECC status bits by writing DMU_HF_ECCC.CLR with 11b to clear
              AERM bit*/

      /* [cover parentID={128AD975-478F-4c58-A290-C3609D63DCF1}]
      Clear the ECC error bit(AERM)
      [/cover] */
      BitChange= DMU_HF_ECCC.U | FLS_DMU_ECCC_CLR;

      /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
       the object types as the address of the register is being passed.*/
      FLS_17_DMU_LIB_RUNTIME_WRITECPUENDINITPROTREG(\
          (volatile uint32 *)&DMU_HF_ECCC.U, \
          BitChange);

      /*There is a delay of 2-3 cycles in the clearing of AERM bit*/
      NOP();
      NOP();
      NOP();

      /* [cover parentID= {42801EB9-2F03-487e-BE5D-80E59089B575}]
      loop tp compare
      [/cover] */
      do
      {
        /* COMPARE THE FLASH DATA WITH THE BUFFER DATA (word Compare)*/
        /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
        array indexing used for FLASH address calculation and for subsequent
        traversal.The access range is within the flash address range.*/
        if( *(TargetAddressPtr+IndexTargetAddressPtr) != *SrcPtr )
        {
          /* [cover parentID={0D693A05-EFD6-47ce-995D-D58C0200836A}]
          Set the Return value as NOT OK
          [/cover] */
          /* [cover parentID={D271F1A4-BCAA-4111-B71B-C65816C69E14}]
          Set the Return value as NOT OK
          [/cover] */
          RetVal = E_NOT_OK;
          /* [cover parentID={7C65ED2C-4B14-4ace-B916-B1EC41AA9838}]
          Update length as zero
          [/cover] */
          CompLen = 0U;
        }
        else
        {
          IndexTargetAddressPtr++;
          SrcPtr++;
          CompLen--;
        }
      } while(CompLen > 0U);
      /* [cover parentID={051A1A45-688C-4aee-A8A1-8F455E1C8BA2}]
      Is compare successful?
      [/cover] */

      /* Restore the JobType with previous tasks */
      StatePtr->FlsJobType = FLS_17_DMU_NONE;

      /* Check for uncorrectable bit error */
      if(Fls_lChkBitErrors() != 0U)
      {
#if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)

        Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                                FLS_17_DMU_INSTANCE_ID,
                                FLS_17_DMU_SID_COMPARESYNC,
                                FLS_17_DMU_E_COMPARE_FAILED);
#endif
        /* Return E_NOT_OK */
        RetVal = E_NOT_OK;

      }
    }
    else
    {
#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
      Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                             FLS_17_DMU_SID_COMPARESYNC, FLS_17_DMU_E_BUSY);
#endif
      /* [cover parentID={0D693A05-EFD6-47ce-995D-D58C0200836A}]
      Set the Return value as NOT OK
      [/cover] */
      RetVal = E_NOT_OK;

    }
  }
  return(RetVal);

}


#if (FLS_17_DMU_IFX_NVM_PRESENT == STD_ON)
/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax : Std_ReturnType Fls_17_Dmu_VerifyErase(                            **
**                         const Fls_17_Dmu_AddressType TargetAddress         **
**                               ,uint32 * UnerasedWordlineAddressPtr         **
**                               uint8 * const UnerasedWordlineCountPtr       **
**                               );                                           **
**                                                                            **
** Service ID: 0x23                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : TargetAddress                                            **
**                                                                            **
** Parameters (out): UnerasedWordlineAddressPtr,UnerasedWordlineCountPtr      **
**                                                                            **
** Return value    :  E_OK: Erase verification successful                     **
**                    E_NOT_OK: HW busy or erase verification failed          **
**                                                                            **
** Description : Service for verifying erase of a sector                      **
*******************************************************************************/
Std_ReturnType Fls_17_Dmu_VerifyErase(
  const Fls_17_Dmu_AddressType TargetAddress,
  uint32 *const UnerasedWordlineAddressPtr,
  uint8 * const UnerasedWordlineCountPtr )
/* [cover parentID={5E18E6DD-2144-49f5-8745-3EED2D934CE0}]
Fls_17_Dmu_VerifyErase
[/cover] */
/*[cover parentID={3C77357E-5460-46ff-A479-A216C527E574}][/cover]*/
{

  Std_ReturnType RetVal;


#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  const Fls_17_Dmu_StateType  *StatePtr;
  uint8 JobType;
  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  JobType = StatePtr->FlsJobType;
  /* Checking whether given TargetAddress is valid or not */
  if(((uint32)TargetAddress >= FLS_17_DMU_TOTAL_SIZE) ||
      ((TargetAddress & FLS_MOD4K_MASK )!=0U))
  {
    /* Report to DET */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_VERIFYERASE, FLS_17_DMU_E_PARAM_ADDRESS);

    RetVal = E_NOT_OK;
  }
  else if((UnerasedWordlineAddressPtr == NULL_PTR) ||
          (UnerasedWordlineCountPtr == NULL_PTR))
  {
    /* Report to DET */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_VERIFYERASE, FLS_17_DMU_E_PARAM_DATA);

    RetVal = E_NOT_OK;
  }
  /* [cover parentID={EFC67AE6-E063-42b3-9474-32E7F663F3FC}]
  Is driver IDLE?
  [/cover] */
  else  if(JobType != FLS_17_DMU_NONE)/*Driver Busy*/
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_VERIFYERASE, FLS_17_DMU_E_BUSY);
    RetVal = E_NOT_OK;
  }
  /* [cover parentID={F939BB22-8474-4f86-8782-5A7BCCE24B2D}]
  Is the FLS HW IDLE ?
  [/cover] */
  else if(Fls_lHWBusyCheck() != 0U)/*HW Busy check*/
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_VERIFYERASE, FLS_17_DMU_E_HW_BUSY);
    RetVal = E_NOT_OK;
  }
  else
  {
#endif
    RetVal = Fls_lLocalVerifyErase(TargetAddress, UnerasedWordlineAddressPtr,
                                   UnerasedWordlineCountPtr, 0U, 0U);
#if(FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  }
#endif
  return(RetVal);

}
#endif


/*******************************************************************************
** Traceability :  [cover parentID={73A7CFF7-D3A9-49ba-A186-E9AA3F27FC09}]    **
**                                                                            **
** Syntax : Std_ReturnType Fls_17_Dmu_VerifySectorErase                       **
**                                (Fls_17_Dmu_AddressType TargetAddress,      **
**                                 uint32 * const UnerasedWordlineAddressPtr  **
**                                 uint8 * const UnerasedWordlineCountPtr     **
**                               uint8 Sector);                               **
**                                                                            **
** Service ID: 0x24                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : TargetAddress,Sector                                     **
**                                                                            **
** Parameters (out): UnerasedWordlineAddressPtr,UnerasedWordlineCountPtr      **
**                                                                            **
** Return value    :  E_OK: Erase verification successful                     **
**                    E_NOT_OK: HW busy or erase verification failed          **
**                                                                            **
** Description : Service for verifying erase of a sector                      **
*******************************************************************************/
Std_ReturnType Fls_17_Dmu_VerifySectorErase(
  const Fls_17_Dmu_AddressType TargetAddress,
  uint32 *const UnerasedWordlineAddressPtr,
  uint8 *const UnerasedWordlineCountPtr,
  const uint8 Sector)
/* [cover parentID={2643CE1D-3341-479a-A7C9-4AB37E7FAD8D}]
Fls_17_Dmu_VerifySectorErase[/cover] */
/* [cover parentID={E4899288-DB87-4ef0-94EB-11BD01754497}][/cover] */
{
  Std_ReturnType RetVal;

#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  const Fls_17_Dmu_StateType  *StatePtr;
  uint8 JobType;
  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  JobType = StatePtr->FlsJobType;
  /* Checking whether given TargetAddress is valid or not */
  if(((uint32)TargetAddress >= FLS_17_DMU_TOTAL_SIZE) ||
      ((TargetAddress & FLS_MOD4K_MASK )!=0U))
  {
    /* Report Safety Error*/
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_VERIFYSECTORERASE, FLS_17_DMU_E_PARAM_ADDRESS);

    RetVal = E_NOT_OK;
  }
  else if((UnerasedWordlineAddressPtr == NULL_PTR) ||
          (UnerasedWordlineCountPtr == NULL_PTR))
  {
    /* Report Safety Error */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_VERIFYSECTORERASE, FLS_17_DMU_E_PARAM_DATA);

    RetVal = E_NOT_OK;
  }
  /*FLS_17_DMU_NVMSECTOR_SIZE will always be a multiple of 4K as this info
   is conveyed to the user in the UM*/
  else if(Sector >= (FLS_17_DMU_NVMSECTOR_SIZE/FLS_17_DMU_SUBSECTOR_SIZE))
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_VERIFYSECTORERASE,FLS_17_DMU_E_PARAM_INVLD);
    RetVal = E_NOT_OK;
  }
  else  if(JobType != FLS_17_DMU_NONE)/*Driver Busy*/
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_VERIFYSECTORERASE, FLS_17_DMU_E_BUSY);
    RetVal = E_NOT_OK;
  }
  /* [cover parentID={66433ED3-1964-4c98-9E98-D445C29EC469}]
  Is FLS hardware IDLE?
  [/cover] */
  else if(Fls_lHWBusyCheck() != 0U)/*HW Busy check*/
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_VERIFYSECTORERASE, FLS_17_DMU_E_HW_BUSY);
    RetVal = E_NOT_OK;
  }
  else
  {
#endif

    RetVal = Fls_lLocalVerifyErase(TargetAddress, UnerasedWordlineAddressPtr,
                                   UnerasedWordlineCountPtr, Sector,
                                   FLS_VERIFYSECTOR_CHK_VAL);
#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  }
#endif
  return(RetVal);
}


/*******************************************************************************
** Traceability :  [cover parentID={73A7CFF7-D3A9-49ba-A186-E9AA3F27FC09}]    **
**                                                                            **
** Syntax : Std_ReturnType Fls_lLocalVerifyErase                              **
**                                (Fls_17_Dmu_AddressType TargetAddress,      **
**                                 uint32 * const UnerasedWordlineAddressPtr  **
**                                 uint8 * const UnerasedWordlineCountPtr     **
**                               uint8 *Sector);                              **
**                                                                            **
** Service ID: 0x24                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : TargetAddress,Sector                                     **
**                                                                            **
** Parameters (out): UnerasedWordlineAddressPtr,UnerasedWordlineCountPtr,     **
**                                                                            **
**                                                                            **
** Return value    :  E_OK: Erase verification successful                     **
**                    E_NOT_OK: HW busy or erase verification failed          **
**                                                                            **
** Description : Service for verifying erase of a sector                      **
*******************************************************************************/
static Std_ReturnType Fls_lLocalVerifyErase(
  const Fls_17_Dmu_AddressType TargetAddress,
  uint32 *const UnerasedWordlineAddressPtr,
  uint8 *const UnerasedWordlineCountPtr,
  const uint8 Sector, uint32 value)
{
  Fls_17_Dmu_StateType  *StatePtr;
  volatile uint32 PhysicalAddress;
  uint32 *SrcPtr;
  uint32 Length;
  uint32 UnerasableWLAddr;
  uint32 HFMarginBackUpVal;
  uint32 BitChange;
  uint32 TimeOutCountInitial;
  uint32 TimeOutResolution;
  uint32 TimeOutCount;
  uint32 MeasuredTicks;
  uint8 FailCount;
  uint8 FailIndex;
  uint8 CompareFail;
  uint8 JobType;
  Std_ReturnType RetVal;


  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  JobType = StatePtr->FlsJobType;

  RetVal = E_OK;
  FailIndex = 0U;

  /* Store the DMU_HF_MARGIN value so that it can be restored later */

  HFMarginBackUpVal = DMU_HF_MARGIN.U;

  if(value == FLS_VERIFYSECTOR_CHK_VAL)
  {
    FailCount = *UnerasedWordlineCountPtr;
  }
#if (FLS_17_DMU_IFX_NVM_PRESENT == STD_ON)
  else
  {
    FailCount = 0U;
  }
#endif

  /*Clear the ECC status bits by writing DMU_HF_ECCC.CLR with 11b to clear
                   AERM bit*/
  BitChange= DMU_HF_ECCC.U | FLS_DMU_ECCC_CLR;

  /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
   the object types as the address of the register is being passed.*/
  FLS_17_DMU_LIB_RUNTIME_WRITECPUENDINITPROTREG(\
      (volatile uint32 *)&DMU_HF_ECCC.U, \
      BitChange);
  /* [cover parentID={966DC9FE-7326-45d3-9B21-2F0433E75CAA}]
  [/cover] */
  /* If EVER bit is 1, then read has to be performed with tight margin for
  0-level. Switch to hard margin is done here instead of doing it just before
     read, because it takes 2us (tFL_MarginDel) for the switch over to happen.
     */

  BitChange = (DMU_HF_MARGIN.U | FLS_READHARDMARGIN_VAL)& \
              FLS_TIGHT0MARGIN_VAL;
  DMU_HF_MARGIN.U = BitChange;
  NOP();
  NOP();

  /* [cover parentID={371B2DD6-ADBF-4530-A11F-E92A512AD2C5}]
  Wait for 2us for margin set up
  [/cover] */
  /*2us delay for margin switchover*/
  TimeOutResolution = Mcal_DelayTickResolution();
  TimeOutCount = (uint32)FLS_DMU_MARGIN_TIMEOUT / TimeOutResolution;
  TimeOutCountInitial = Mcal_DelayGetTick();

  do
  {
    MeasuredTicks = Mcal_DelayGetTick() -  TimeOutCountInitial;

  } while (TimeOutCount > MeasuredTicks);

  PhysicalAddress = FLS_17_DMU_BASE_ADDRESS + TargetAddress;

  if(value == FLS_VERIFYSECTOR_CHK_VAL)
  {

    SrcPtr =
      /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
               type is required to access the FLASH address/target address which
                        is defined as unsigned long. */
      /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
          is required to check the value of the address of data buffer alignment.
           */
      /* MISRA2012_RULE_10_8_JUSTIFICATION: conversion between pointer and integer
            type is required to access the FLASH address/target address which
              is defined as unsigned long. */
      (uint32 *)(PhysicalAddress + (uint32)(FLS_17_DMU_SUBSECTOR_SIZE * \
                                            Sector));

  }
#if (FLS_17_DMU_IFX_NVM_PRESENT == STD_ON)
  else
  {

    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
         type is required to access the FLASH address/target address which
              is defined as unsigned long. */
    /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
      is required to check the value of the address of data buffer alignment.
      */
    SrcPtr = (uint32*)PhysicalAddress;
  }
#endif

  /* Check if no operation ongoing */
  if(JobType == FLS_17_DMU_NONE)
  {

    /* Modify the GlobalVar JobType so that no new requests can be accepted on
                   the Bank till VerifyErase is finished */
    StatePtr->FlsJobType = FLS_17_DMU_VERIFYERASE;


    if(value == FLS_VERIFYSECTOR_CHK_VAL )
    {
      /* Data Flash Bank0 : Logical sector size-> 4K bytes*/
      Length = FLS_17_DMU_SUBSECTOR_SIZE;
    }
#if (FLS_17_DMU_IFX_NVM_PRESENT == STD_ON)
    else
    {
      /*[cover parentID={3C2F5740-7DBD-49dc-8E69-1FFDBEB93300}][/cover]*/
      Length = FLS_17_DMU_NVMSECTOR_SIZE;
    }
#endif

    /* Check if there is verify error during Erase operation */
    do
    {
      CompareFail = 0U;

      /*[cover parentID= {38A0FD1D-35DD-4cc5-9D96-FB60CC608644}][/cover]*/
      /* COMPARE THE FLASH DATA WITH zero (first 16 Bytes of the Wordline)*/

      /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
       array indexing used for FLASH address calculation and for subsequent
       traversal.The access range is within the flash address range.*/
      if((*SrcPtr != 0U) || (*(SrcPtr + 1U) !=0U) || \
          (*(SrcPtr + 2U) !=0U) || (*(SrcPtr + 3U) !=0U) )
      {
        CompareFail = 1U;
      }
      /* [cover parentID=   {488838E2-C699-42f0-85F3-1239E5A8A321}]
         Is there ECC error ?
          [/cover] */
      if(Fls_lChkBitErrors() != 0U)
      {
        /* [cover parentID=  {3185CC99-BFFE-4db7-97DB-CBD69A56C455}]
            Set the compare flag set and clear the errors
               [/cover] */
        CompareFail = 1U;

        /* Clear the errors status flags */
        BitChange = FLS_DMU_ERR_CLR;
        /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
         the object types as the address of the register is being passed.*/
        FLS_17_DMU_LIB_RUNTIME_WRITECPUENDINITPROTREG( \
            (volatile uint32 *)&DMU_HF_CLRE.U, \
            BitChange);
      }

      /*[cover parentID= {26FFF6BE-EAF5-469f-9362-7CDF71CA1C6C}][/cover]*/
      /* [cover parentID=  {6784AF29-9A31-472f-A1D3-455624C447B9}]
           Is the compare flag set ?
            [/cover] */
      if(CompareFail == 1U)
      {
        /* [cover parentID= {93B835A2-2C25-4f73-87F6-96C43BB521A3}]
            Is the compare flag set ?
          [/cover] */
        FailCount++;
        /* [cover parentID={5E89075C-A634-4971-B817-9AA54D8B2B61}]
         Is the fail count > 2 Wordline fail count?
         [/cover] */

        /* [cover parentID={4B8F014E-139E-41ac-B815-3EDF6B012473}]
         Is the fail count > 2 Wordline fail count?
         [/cover] */
        /* [cover parentID=  {4562081B-C702-459c-A16D-276D013841C2}]
           Is the unerasable wordline count > 2
        [/cover] */
        if(FailCount > FLS_WL_FAIL_COUNT)
        {
          /* [cover parentID={5E89075C-A634-4971-B817-9AA54D8B2B61}]
             Return Value as NOT OK
          [/cover] */
          /* [cover parentID={8A7C1862-BBDA-4763-B843-9B03307DE225}]
             Set the Return value as NOT OK
              [/cover] */
          RetVal = E_NOT_OK;

        }
        else
        {
          /* Update the Unerasable WL address */


          /* [cover parentID={2347D209-ED61-40e6-89A9-B4AFE06077E5}]

             [/cover] */
          /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
            type is required to access the FLASH address/target address which
           is defined as unsigned long. */
          /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
          is required to access the FLASH address/target address which is defined
            as unsigned long by AUTOSAR. */
          UnerasableWLAddr = (uint32)SrcPtr - FLS_17_DMU_BASE_ADDRESS;


          /* [cover parentID={1AF7D403-E461-47fb-95CA-89B36814F09D}]
          Update the Unerasable wordline address to FEE and move to the next word
          for comparison, decrement the length
          [/cover] */
          /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
          array indexing used for FLASH address calculation and for subsequent
          traversal.The access range is within the flash address range.*/
          *(UnerasedWordlineAddressPtr+FailIndex) = UnerasableWLAddr;

          /* increment SrcPtr to next wordline, divide by 4 for SrcPtr is
             uint32 ptr*/

          /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
          array indexing used for FLASH address calculation and for subsequent
          traversal.The access range is within the flash address range.*/
          SrcPtr += (FLS_17_DMU_WORDLINE_SIZE/FLS_WORD_SIZE);
          Length -= FLS_17_DMU_WORDLINE_SIZE;
          FailIndex++;
        }
      }
      else
      {
        /* increment SrcPtr to next wordline, divide by 4 for SrcPtr is
           uint32 ptr*/

        /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
        array indexing used for FLASH address calculation and for subsequent
        traversal.The access range is within the flash address range.*/
        SrcPtr += (FLS_17_DMU_WORDLINE_SIZE/FLS_WORD_SIZE);
        Length -= FLS_17_DMU_WORDLINE_SIZE;
      }

    } while((Length != 0U) && (FailCount <= FLS_WL_FAIL_COUNT));
    /* [cover parentID={F1FA3210-4EAE-4f97-9368-801096BA4CB7}]
    Check if fail count is greater than 2
    [/cover] */
    /* [cover parentID={48568C58-FD18-4449-B984-F48343ECCD52}]
     Update teh fail count to FEE
      [/cover] */
    *UnerasedWordlineCountPtr = FailCount;

    /* Restore the JobType with previous tasks */
    StatePtr->FlsJobType = FLS_17_DMU_NONE;
  }
  else
  {
    RetVal = E_NOT_OK;

    /*Restore the DMU_HF_MARGIN value that was backed-up earlier */

    DMU_HF_MARGIN.U = HFMarginBackUpVal;

  }

  return(RetVal);
}



/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax : Fls_17_Dmu_Job_Type Fls_17_Dmu_GetNotifCaller(void)               **
**                                                                            **
** Service ID: 0x29                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  FLS Job that raised the notification                    **
**                                                                            **
** Description :                                                              **
** Ths function returns the FLS Job that raised the notification              **
*******************************************************************************/
Fls_17_Dmu_Job_Type Fls_17_Dmu_GetNotifCaller(void)
/* [cover parentID={519B41BB-BF62-462e-ABC6-1F035388EE0F}][/cover] */
{
  /* [cover parentID={1A32FA81-F43C-4ea1-8475-A19BB0177DD1}]
  Notify the caller with the present running job
  [/cover] */
  return(Fls_ConfigPtr->FlsStateVarPtr->NotifCaller);
  /* [cover parentID={0C41A653-5FBA-4588-B5C5-E6E215A3616F}]
  Return
  [/cover] */

}

#endif /* FLS_17_DMU_IFX_FEE_USED == STD_ON */


/*[cover parentID={2CDC5CFF-A02A-4fb1-8FED-A46CBA2351DA}][/cover]*/
#if (FLS_17_DMU_USE_ERASESUSPEND == STD_ON)
/*******************************************************************************
** Traceability :  [cover parentID={169CB9F4-AF3D-48a8-89DA-B7E27440AA98}]    **
**                                                                            **
** Syntax : Std_ReturnType Fls_17_Dmu_SuspendErase(void)                      **
**                                                                            **
** Service ID: 0x25                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK - Erase suspend successful                         **
**                    E_NOT_OK - Erase suspend failed                         **
**                                                                            **
** Description :                                                              **
** Ths function suspends an ongoing erase of a sector.                        **
*******************************************************************************/
Std_ReturnType Fls_17_Dmu_SuspendErase(void)
/* [cover parentID={E62F23D2-A43A-4d8f-B76C-6DDA9D9A79F2}][/cover] */
{
  Std_ReturnType RetVal;
  Fls_17_Dmu_StateType  *StatePtr;
  volatile uint32 TimeOutCount;

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  uint32 BitChange;


  /* [cover parentID={298F7C2D-0034-46da-884F-6DCAA541C2E6}]
  Is the FLS HW busy ?
  [/cover] */
  if(DMU_HF_STATUS.B.D0BUSY != 1U)
  {
    RetVal = E_NOT_OK;
  }
  else if(DMU_HF_SUSPEND.B.SPND == 1U)
  {
    RetVal = E_OK;
  }
  else
  {

    /* [cover parentID={1DD2F5F8-0B13-4559-B297-9B42DDE73CFF}]
    Check whether operation is suspended successfully or timeout occured?
    [/cover] */

    BitChange = DMU_HF_SUSPEND.U | IFX_DMU_HF_SUSPEND_REQ_MSK;
    DMU_HF_SUSPEND.U = BitChange;

    /*[cover parentID={03DA6395-E09B-4114-AC16-C8D3FBF3278B}][/cover]*/
    TimeOutCount = FLS_17_DMU_ERASESUSPEND_TIMEOUT;
    do
    {
      TimeOutCount-- ;

      /*MISRA2012_RULE_13_5_JUSTIFICATION: These are device registers and are
      declared with Volatile qualifier due to which the tool is giving MISRA 13.5.
      */
    } while((TimeOutCount > 0U) && (DMU_HF_SUSPEND.B.REQ == 1U));

    if (TRUE == Fls_lSpndTimeout(TimeOutCount))
    {
      /* [cover parentID={C6D2B841-80B2-483c-ADD8-EBBE6C3E40F7}]
      Set the Return Value as NOT OK
      [/cover] */
      RetVal = E_NOT_OK;
    }

    else if(DMU_HF_SUSPEND.B.SPND != 1U)
    {
      /* Clear Suspend Error status */

      BitChange = DMU_HF_SUSPEND.U | SUSPEND_CLR_OFF;
      DMU_HF_SUSPEND.U=BitChange;
      /* [cover parentID={C6D2B841-80B2-483c-ADD8-EBBE6C3E40F7}]
      Set the Return Value as NOT OK
      [/cover] */
      RetVal = E_NOT_OK;
    }
    else
    {

      /*EVER check*/
      /* [cover parentID={F87AB3A8-6261-4c49-A496-EC6FCD5C3AFD}]
      Is the EVER bit set ?
      [/cover] */
      if((DMU_HF_ERRSR.B.EVER != 0U)
          && (StatePtr->FlsEver == (uint8)0))
      {
        StatePtr->FlsEver = FLS_EVER_CHK;
      }

      RetVal = E_OK;
      /* Set job status for the bank to None */
      StatePtr->FlsJobType = FLS_17_DMU_NONE;
      /* Reset JobStartStatus */
      StatePtr->JobStarted.Erase = 0U;
      /* Set the flash job result to job ok */
      StatePtr->FlsJobResult = MEMIF_JOB_OK;
    }
  }

  return RetVal;
}

/*******************************************************************************
** Traceability :  [cover parentID={0F3EBC6B-A3E5-452f-87AD-3D740F53F2C2}]    **
**                                                                            **
** Syntax : Std_ReturnType Fls_17_Dmu_ResumeErase (uint32 BankNum )           **
**                                                                            **
** Service ID: 0x26                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK - Resume Erase successful                          **
**                    E_NOT_OK - Resume Erase failed                          **
**                                                                            **
** Description :                                                              **
** This function suspends an ongoing erase of a sector.                       **
*******************************************************************************/
Std_ReturnType Fls_17_Dmu_ResumeErase (void)
/*[cover parentID={478A22CE-6897-4722-81AB-41264DBC1353}][/cover]*/
{
  Std_ReturnType RetVal;
  Fls_17_Dmu_StateType  *StatePtr;
  volatile uint32 PhysicalAddress;
  uint32 TimeOutCount;
  uint32 BitChange;


  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  RetVal = E_OK;

  /* [cover parentID={1A1D6B47-4982-474b-A13D-44321A53C4FD}]
  Is suspend bit set?
  [/cover] */
  if(DMU_HF_SUSPEND.B.SPND == 1U)
  {

    /*[cover parentID={0EF026E3-7E78-4210-BA00-21FDED676D2F}][/cover]*/
    PhysicalAddress = Fls_ConfigPtr->FlsStateVarPtr->FlsEraseAddress;

    Fls_ClearStatusCmdCycle();

    /* Execute the Resume ERASE COMMAND CYCLES */

    Fls_ResumeEraseCmdCycle(PhysicalAddress);

    /*Timeout for the resume command to complete*/
    /*[cover parentID={03DA6395-E09B-4114-AC16-C8D3FBF3278B}][/cover]*/
    TimeOutCount = FLS_17_DMU_ERASESUSPEND_TIMEOUT;
    do
    {
      TimeOutCount-- ;
    } while((DMU_HF_SUSPEND.B.SPND == 1U) && (TimeOutCount > 0U) );


    if(Fls_lChkSeqProtErrors() != 0U)/*SQER check*/
    {

      /* [cover parentID={61A69F77-F379-4ffe-981C-DE61535E9E0C}]
      Send command cycles for resuming the erase for the particular sector
      [/cover] */
      /* Clear the error status flags */
      BitChange = FLS_DMU_ERR_CLR;
      /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
       the object types as the address of the register is being passed.*/
      FLS_17_DMU_LIB_RUNTIME_WRITECPUENDINITPROTREG( \
          (volatile uint32 *)&DMU_HF_CLRE.U, \
          BitChange);

      /* [cover parentID={1901C645-1546-472b-9EB4-E9FB9C442D7C}]
      Return Value is NOT OK
      [/cover] */
      RetVal = E_NOT_OK;
    }
    else
    {

      /*OPER check*/
      if(0U != Fls_lChkOperError())
      {
        /* OPER error occured */
        /* [cover parentID={1901C645-1546-472b-9EB4-E9FB9C442D7C}]
        Return Value is NOT OK
        [/cover] */
        RetVal = E_NOT_OK;
      }
      /* [cover parentID={968637F5-4D30-40de-B554-0911CC1AA17E}]
        Is erase resumed?
      [/cover] */
      else if((DMU_HF_SUSPEND.B.SPND == 1U) && (TimeOutCount == 0U))
      {
#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
        Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                               FLS_17_DMU_SID_RESUMEERASE, FLS_17_DMU_E_HW_TIMEOUT);
#endif
        /* If timeout happens and Suspend bit is not cleared return E_NOT_OK*/
        /* [cover parentID={1901C645-1546-472b-9EB4-E9FB9C442D7C}]
        Return Value is NOT OK
        [/cover] */
        RetVal = E_NOT_OK;
      }
      else if(0U == DMU_HF_STATUS.B.D0BUSY)
      {
        /* If hardware is still not busy i.e., if erase did not resume,
        then return E_NOT_OK */
        RetVal = E_NOT_OK;
      }

      else
      {

        /* Restore the JobType with previous erase */
        StatePtr->FlsJobType = FLS_17_DMU_ERASE;
        /* 1. Set the flash job result to job pending */
        StatePtr->FlsJobResult = MEMIF_JOB_PENDING;
        /*Indicate that the ERASE Job has been started */
        StatePtr->JobStarted.Erase = 1U;
      }
    }
  }

  return RetVal;
}

#endif /* FLS_USE_ERASESUSPEND == STD_ON */

/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax : Std_ReturnType Fls_17_Dmu_GetOperStatus(void)                     **
**                                                                            **
** Service ID: 0x2A                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK - No OPER error                                    **
**                    E_NOT_OK - OPER error has occurred                      **
**                                                                            **
** Description : This function provides the OPER error status                 **
*******************************************************************************/
Std_ReturnType Fls_17_Dmu_GetOperStatus(void)
/* [cover parentID={284116EC-B6F7-4276-96FE-3AA60587BC9C}][/cover] */
{
  uint32 OPER_Status;
  Std_ReturnType RetVal;

  RetVal = E_OK;

  OPER_Status = ((uint32)DMU_HF_ERRSR.U & IFX_DMU_HF_ERRSR_OPER_MSK);
  /* [cover parentID={08A2FB3E-A953-4d56-9FF2-3290BBF7C42B}]
  Is the oper bit set or operational error detected?
  [/cover] */
  if(0U != OPER_Status)
  {
    RetVal = E_NOT_OK;
  }

  return (RetVal);
}


/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax : void Fls_17_Dmu_ControlTimeoutDet(uint8 Param)                    **
**                                                                            **
** Service ID: 0x2B                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  Param  - Value for timeout                              **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This is the function to disable and re-enable detection /    **
**               reporting of time-out DET                                    **
*******************************************************************************/
void Fls_17_Dmu_ControlTimeoutDet(const uint8 Param)
/* [cover parentID={E21C9DB9-FFE7-4807-9088-185BCAEBE945}][/cover] */
{
  /* [cover parentID={B113BC20-94AA-4c60-9E27-EB03BB7275AF}]
  DET Enable
  [/cover] */
#if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
                                       (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  if(Param > ((uint8)0x01))
  {
#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID,FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_CONTROLTIMEOUTDET,FLS_17_DMU_E_PARAM_INVLD);
#endif
  }
  else
  {
    /* [cover parentID={1233DCB8-4181-4e01-BCFB-3895466F08C8}]
     Set the local state pointer to the value in configuration pointer
     Assign the value of param to FlsTimeoutControl
    [/cover] */
    Fls_ConfigPtr->FlsStateVarPtr->FlsTimeoutControl = Param;
  }

#else
  UNUSED_PARAMETER(Param);
#endif
}

#if(FLS_17_DMU_IFX_FEE_USED == STD_ON)
/*******************************************************************************
** Traceability :  [cover parentID={685AB4B7-A883-439e-9AAD-040235A9CF46}]    **
**                                                                            **
** Syntax : Fls_17_Dmu_HardenType Fls_17_Dmu_IsHardeningRequired(             **
**                    const Fls_17_Dmu_AddressType TargetAddress,             **
**                    const uint8 AlignChk )                                  **
**                                                                            **
** Service ID: 0x2C                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  TargetAddress, AlignChk                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Fls_17_Dmu_HardenType                                   **
**                                                                            **
** Description : The function checks whether the contents of memory at        **
                 requested wordline address needs hardening or not            **
*******************************************************************************/
Fls_17_Dmu_HardenType Fls_17_Dmu_IsHardeningRequired(
  const Fls_17_Dmu_AddressType TargetAddress,
  const uint8 AlignChk)
/* [cover parentID={03D233C8-248E-4bef-9AFC-1AED269BAB08}]
 Service to harden - Fls_17_Dmu_IsHardeningRequired
  [/cover] */
/* [cover parentID={ABEE16D0-CB28-422d-B3CE-FFA63C0990BB}]
Service to harden - Fls_17_Dmu_IsHardeningRequired
[/cover] */
{
  uint8 RetVal;
  uint8 ECCErrorStat;
  volatile uint32     PhysicalAddress;
  uint32 CountDiff, BitChange=0U, BitRestore;
  uint32 TimeOutType;
  uint32 TimeOutCount;
  uint32 TimeOutCountInitial;
  uint32 TimeOutResolution;
  uint32 MeasuredTicks;

#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  if((Fls_lHardenSafetyChk(TargetAddress, AlignChk))
      == FLS_17_DMU_HARDENCHK_ERROR)
  {
    RetVal = FLS_17_DMU_HARDENCHK_ERROR;
  }
  else
#endif
  {

    PhysicalAddress = FLS_17_DMU_BASE_ADDRESS + TargetAddress;

    /* Set the control gate voltage to 4.1V before executing the command */

    FSI_COMM_1.B.COMM1 = FLS_CTRLGATEVOLTAGE_VAL;

    BitRestore = DMU_HF_CONTROL.U;
    /* [cover parentID={4D174B2B-4FA5-45da-8586-E587142F0972}]
    Set the FLS alignment to pagewise and clear status error bits
    [/cover] */
    if(FLS_17_DMU_PAGE_HARDEN == AlignChk)
    {
      BitChange=((uint32)DMU_HF_CONTROL.U | FLS_DMU_HARDEN_PAGE_ALIGN);
      TimeOutType = (uint32)FLS_USRCONTENT_PAGE_TIMEOUT;
    }
    else
    {
      BitChange=((uint32)DMU_HF_CONTROL.U & FLS_DMU_HARDEN_WORD_ALIGN);
      TimeOutType = (uint32)FLS_USRCONTENT_WL_TIMEOUT;
    }

    FLS_17_DMU_LIB_RUNTIME_WRITECPUENDINITPROTREG(&DMU_HF_CONTROL.U,
        BitChange);

    Fls_ClearStatusCmdCycle();

    /* Execute the user content count command sequence */

    Fls_UserContentCountCmdCycle(PhysicalAddress);



    /*Wait for 20us*/
    TimeOutResolution = Mcal_DelayTickResolution();
    TimeOutCount =  TimeOutType/TimeOutResolution;
    TimeOutCountInitial = Mcal_DelayGetTick();

    do
    {
      MeasuredTicks = Mcal_DelayGetTick() -  TimeOutCountInitial;

    } while ((Fls_lHWBusyCheck() != 0U) && (TimeOutCount > MeasuredTicks));

    if(TimeOutCount <= MeasuredTicks)
    {
#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
      Mcal_ReportSafetyError((uint16)FLS_17_DMU_MODULE_ID,
                             FLS_17_DMU_INSTANCE_ID,
                             FLS_17_DMU_SID_ISHARDENINGREQ,
                             FLS_17_DMU_E_HW_TIMEOUT);
#endif
      RetVal = FLS_17_DMU_HARDENCHK_ERROR;
    }
    else if (Fls_lChkSeqProtErrors() != 0U)
    {
      RetVal = FLS_17_DMU_HARDENCHK_ERROR;
      /*Clear the SQER/PVER/EVER error*/
      BitChange = FLS_DMU_ERR_CLR;
      /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
       the object types as the address of the register is being passed.*/
      FLS_17_DMU_LIB_RUNTIME_WRITECPUENDINITPROTREG( \
          (volatile uint32 *)&DMU_HF_CLRE.U, \
          BitChange);

#if(FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
      Det_ReportRuntimeError((uint16)FLS_17_DMU_MODULE_ID,
                             FLS_17_DMU_INSTANCE_ID,
                             FLS_17_DMU_SID_ISHARDENINGREQ,
                             FLS_17_DMU_E_HARDENCHK_FAIL);
#endif
    }
    else if(Fls_lChkOperError() != 0U) /*Check for OPER*/
    {
      /*Harden fail due to OPER error*/
      RetVal = FLS_17_DMU_HARDENCHK_ERROR;

#if(FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
      Det_ReportRuntimeError((uint16)FLS_17_DMU_MODULE_ID,
                             FLS_17_DMU_INSTANCE_ID,
                             FLS_17_DMU_SID_ISHARDENINGREQ,
                             FLS_17_DMU_E_HARDENCHK_FAIL);
#endif
    }
    else
    {
      /* [cover parentID={425BF8CF-FBBA-46cc-A02D-773F6908768C}]
      [/cover] */
      /* Result (Difference in count of '1' bits) is returned as 13-bit unsigned
          integer with bits [7:0] in FSI_COMM_1.COMM1[7:0] and bits [12:8] in
          FSI_COMM_2.COMM2[4:0]. Ordering of the information is done and
          stored in CountDiff*/

      CountDiff = FSI_COMM_2.B.COMM2;

      CountDiff = (CountDiff & FLS_FSICOMM2RES_MASK)<< FLS_SHIFT8BITS_VAL;


      CountDiff |= FSI_COMM_1.B.COMM1;

      /* Obtain the TBE (3 bit error) status after the command execution */

      ECCErrorStat = FSI_COMM_2.B.COMM2 & FLS_COMM2TBE_MASK;

      /* Hardening is required either if there is a difference in number of
         '1'-bits with tight margin for 0-level and the number of '1'-bits with
         tight margin for 1-level or with 3-bit ECC errors */

      if ((CountDiff > 1U) && (FLS_17_DMU_PAGE_HARDEN == AlignChk))
      {
        RetVal = FLS_17_DMU_HARDENCHK_REQRD;
      }
      else if((CountDiff > 2U) && (FLS_17_DMU_WORDSIZE_HARDEN == AlignChk))
      {
        RetVal = FLS_17_DMU_HARDENCHK_REQRD;
      }
      else if(ECCErrorStat != 0U)
      {
        RetVal = FLS_17_DMU_HARDENCHK_REQRD;
      }
      else
      {
        RetVal = FLS_17_DMU_HARDENCHK_NOTREQD;
      }

      /*Clear the page alignment to restore the previosu status so that other
       operations are not affected*/
      FLS_17_DMU_LIB_RUNTIME_WRITECPUENDINITPROTREG(&DMU_HF_CONTROL.U,
          BitRestore);

      /*Reset the COMM1 and COMM2 values to system reset values*/
      FSI_COMM_1.U = FLS_COMM_RESET_VAL;
      FSI_COMM_2.U = FLS_COMM_RESET_VAL;

    } /*timeout, SQER, PROER*/

  } /*Range Check is OK*/

  return (RetVal);
}


#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability :  [cover parentID={685AB4B7-A883-439e-9AAD-040235A9CF46}]    **
**                                                                            **
** Syntax : LOCAL_INLINE uint8 Fls_lHardenSafetyChk(const                     **
**              Fls_17_Dmu_AddressType TargetAddress, const uint8 AlignChk)   **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  TargetAddress, AlignChk                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Fls_17_Dmu_HardenType                                   **
**                                                                            **
** Description : This function which will do the safety  and                  **
                 range check for the Fls_17_Dmu_IsHardeningRequired()         **
*******************************************************************************/
LOCAL_INLINE uint8 Fls_lHardenSafetyChk(
  const Fls_17_Dmu_AddressType TargetAddress, const uint8 AlignChk)
{
  uint8 RetVal;
  const Fls_17_Dmu_StateType  *StatePtr;
  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  RetVal = FLS_17_DMU_HARDENCHK_NOTREQD;
  /*Check the Target Address*/
  if(((uint32)TargetAddress) >= FLS_17_DMU_TOTAL_SIZE)
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID,FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_ISHARDENINGREQ, FLS_17_DMU_E_PARAM_ADDRESS);

    RetVal = FLS_17_DMU_HARDENCHK_ERROR;
  }
  else if(((FLS_17_DMU_WORDSIZE_HARDEN == AlignChk) &&
           ((TargetAddress & FLS_WL_SIZE_MASK) != 0U)) ||
          ((FLS_17_DMU_PAGE_HARDEN == AlignChk) &&
           ((TargetAddress & FLS_PAGE_SIZE_MASK) != 0U)))
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_ISHARDENINGREQ, FLS_17_DMU_E_PARAM_ADDRESS);
    RetVal = FLS_17_DMU_HARDENCHK_ERROR;
  }
  else if((FLS_17_DMU_WORDSIZE_HARDEN != AlignChk) &&
          (FLS_17_DMU_PAGE_HARDEN != AlignChk))
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_ISHARDENINGREQ, FLS_17_DMU_E_PARAM_INVLD);
    RetVal = FLS_17_DMU_HARDENCHK_ERROR;
  }
  /* [cover parentID={87BA5140-9EC1-443d-B45E-5BC7E32DCD18}]
  Is the FLS HW busy ?
  [/cover] */
  else if(Fls_lHWBusyCheck() != 0U)/*HW Busy check*/
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_ISHARDENINGREQ, FLS_17_DMU_E_HW_BUSY);
    RetVal = FLS_17_DMU_HARDENCHK_ERROR;
  }
  /* [cover parentID={F0068116-161F-426c-8622-A8AAE08A64D6}]
  Is the FLS driver busy ?
  [/cover] */
  else  if(StatePtr->FlsJobType != FLS_17_DMU_NONE)/*Driver Busy*/
  {
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_ISHARDENINGREQ, FLS_17_DMU_E_BUSY);
    RetVal = FLS_17_DMU_HARDENCHK_ERROR;
  }
  else
  {
    /*MISRA*/
  }

  return(RetVal);
}
#endif
#endif


/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax : static void Fls_lMainErase(void)                                  **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non-reentrant                                                 **
**                                                                            **
** Parameters (in) : void                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Performs the erase operation during Interrupt/Cyclic         **
**               Job handling                                                 **
*******************************************************************************/
/* CYCLOMATIC_Fls_lMainErase_JUSTIFICATION: The complexity of this function is
 16 as it has to check for many conditions which include checking for FLS
 operation with both IFX FEE as well as FLS stand-alone mode. Breaking it into
another local function will break the continuity of the checks*/
static void Fls_lMainErase(void)
{
  Fls_17_Dmu_StateType       *StatePtr;
  MemIf_JobResultType LastJobResult;
  volatile uint32     PhysicalAddress;
  volatile uint32     EraseSizeBytesPerCmd;
  Std_ReturnType      RetVal;
  uint32 BitChange;


  /******************* Initialise the local variables ***************/
  RetVal = E_OK;
  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;

  /* [cover parentID={88310907-6D29-4060-8B88-CA83C591ACC9}]
  Obtain the physical address for the erase operation
  [/cover] */
  /* Obtain the physical address for the erase operation */
  PhysicalAddress = StatePtr->FlsEraseAddress;

  /* Sector erase size in bytes per Erase command ; 1 logical sector = 4K*/
  /* MISRA2012_RULE_10_8_JUSTIFICATION: conversion between pointer and integer
      type is required to access the FLASH address/target
      address which is defined as unsigned long. */
  EraseSizeBytesPerCmd = (uint32)((uint16)(StatePtr->FlsEraseNumSecPerCmd) << \
                                  (uint8)FLS_4KSHIFT_VAL);

  /* Erase job has already been started */
  /* [cover parentID={7FD2CA56-A3EA-448a-8D38-03EE5884BF39}]
  Is operational error present?
  [/cover] */
  if(Fls_lChkOperError() != 0U) /* Check for operational error */
  {
    /* Erase Job fails due to hardware error */
    /* Report Runtime error code to DET */
    /* [cover parentID={CC8A11C9-5532-4838-B32E-6BD826F786F4}]
    RUNTIME ERROR DETECT is enabled
    [/cover] */
    /*
    RUNTIME ERROR DETECT is enabled
    */
#if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
    /* [cover parentID={E5568FF3-C810-43e8-934E-7B39B1C5A1ED}]
    Report det
    [/cover] */
    /* [cover parentID={F83E03A0-A123-44fb-B48A-59E61F1278DE}][/cover] */


    Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                            FLS_17_DMU_INSTANCE_ID,
                            FLS_17_DMU_SID_MAIN,
                            FLS_17_DMU_E_ERASE_FAILED);
#endif
    /* Call Fls_lErrorHandler local function */
    Fls_lErrorHandler(FLS_17_DMU_ERASE);
    /* [cover parentID={234A9B4E-AAB9-4095-A13A-01049F15F821}]
    Set return value as NOT OK
    [/cover] */

    RetVal = E_NOT_OK;
  }

  /******************************** DET *************************************/
#if ( FLS_17_DMU_IFX_FEE_USED ==  STD_OFF )
#if ( FLS_17_DMU_DEV_ERROR_DETECT == STD_ON )|| \
        (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  else if(StatePtr->FlsEver != FLS_EVER_CHK)
  {
    if (DMU_HF_ERRSR.B.EVER != 0U)
    {
      Fls_lReportError(FLS_17_DMU_SID_MAIN,
                       FLS_17_DMU_E_VERIFY_ERASE_FAILED);
      Fls_lErrorHandler(FLS_17_DMU_ERASE);
      RetVal = E_NOT_OK; /*return from function*/
    }
    else
    {
      /*MISRA*/
    }
  }
 else
 {
      /*MISRA*/
 }
#endif
#endif

  /* Check if there is verify error during Erase operation */
  if(DMU_HF_ERRSR.B.EVER == 0U)
  {
    /* The sector is correctly erased.
     All erased bits have full expected quality */

    /* [cover parentID={39124837-DB2C-40e8-9338-9C82EFE2884F}]
    Is the EVER Flag set ?
    [/cover] */
    /* [cover parentID={DC6E6DBA-DB98-43b3-840F-3A20DB0FE5D8}]
    Is the Ever Flag set ?
    [/cover] */
    if(StatePtr->FlsEver == FLS_EVER_CHK)
    {
#if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
      Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                              FLS_17_DMU_INSTANCE_ID,
                              FLS_17_DMU_SID_MAIN,
                              FLS_17_DMU_E_ERASE_FAILED);
#endif
#if (FLS_17_DMU_IFX_FEE_USED ==  STD_ON )
      /*Fls_lEverFlagChkFail*/
      Fls_lEverFlagChkFail();
#else   /*FLS Standalone*/
      Fls_lErrorHandler(FLS_17_DMU_ERASE);
      StatePtr->FlsEver = (uint8)0x00;
#endif
      RetVal = E_NOT_OK; /*return from function*/
    }

  }
  else /*EVER error*/
  {
#if ( FLS_17_DMU_IFX_FEE_USED ==  STD_ON )
    /* [cover parentID={F068704D-64CE-47a8-BA5C-A2F2C62DC0C4}]
    Is the FLS EVER Flag already set ?
    [/cover] */
    if(StatePtr->FlsEver == ((uint8)0x00))
    {
      StatePtr->FlsEver = FLS_EVER_CHK;
      /*Clear the OPER, SQER error*/
      BitChange = FLS_DMU_ERR_CLR;
      /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
       the object types as the address of the register is being passed.*/
      FLS_17_DMU_LIB_RUNTIME_WRITECPUENDINITPROTREG( \
          (volatile uint32 *)&DMU_HF_CLRE.U, \
          BitChange);
    }
    else
    {
      /*
      Check if there is verify error during Erase operation
      */
#if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
      Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                              FLS_17_DMU_INSTANCE_ID,
                              FLS_17_DMU_SID_MAIN,
                              FLS_17_DMU_E_ERASE_FAILED);
#endif

      Fls_lEverFlagChkFail();
      RetVal = E_NOT_OK; /*return from function*/

#else /*FLS_17_DMU_IFX_FEE_USED == STD_OFF*/
    if(StatePtr->FlsEver == ((uint8)0x00))
    {
      StatePtr->FlsEver = FLS_EVER_CHK;
    }
    if(StatePtr->FlsEver == FLS_EVER_CHK)
    {
#if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
      /* [cover parentID={E5568FF3-C810-43e8-934E-7B39B1C5A1ED}]
      Report det
      [/cover] */
      /* [cover parentID={F83E03A0-A123-44fb-B48A-59E61F1278DE}][/cover]*/
      Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                              FLS_17_DMU_INSTANCE_ID,
                              FLS_17_DMU_SID_MAIN,
                              FLS_17_DMU_E_ERASE_FAILED);
#endif
      Fls_lErrorHandler(FLS_17_DMU_ERASE);
      StatePtr->FlsEver = (uint8)0x00;
      /*Clear the EVER error*/
      BitChange = FLS_DMU_ERR_CLR;
      /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
       the object types as the address of the register is being passed.*/
      FLS_17_DMU_LIB_RUNTIME_WRITECPUENDINITPROTREG( \
          (volatile uint32 *)&DMU_HF_CLRE.U, \
          BitChange);
      RetVal = E_NOT_OK; /*return from function*/

    }
#endif
#if ( FLS_17_DMU_IFX_FEE_USED ==  STD_ON )
    }
#endif
  } /*EVER error*/

  if(RetVal == E_OK)
  {
    /* [cover parentID={3C653B10-4DC8-4ee3-9472-6660DD525CB1}]
    1) Goto the next erase address
    2) Decrement the number of sectors to be erased
    [/cover] */
    /* Calculate the latest address to be erased */
    StatePtr->FlsEraseAddress += EraseSizeBytesPerCmd;
    /* Calcualte the remaining sectors to be erased*/
    StatePtr->FlsEraseNumSectors -= StatePtr->FlsEraseNumSecPerCmd ;
    /* Check if number of sectors to be erased can be accomodated in 1 erase
      command cycle; If not seal the number of sectors to be erased to
      recommended value 64 */

    if (StatePtr->FlsEraseNumSectors > FLS_MAXERASE_SEC)
    {
      StatePtr->FlsEraseNumSecPerCmd = (uint8)FLS_MAXERASE_SEC;
    }
    else
    {
      StatePtr->FlsEraseNumSecPerCmd = (uint8)StatePtr->FlsEraseNumSectors;
    }
    if(StatePtr->FlsEraseNumSectors != 0U)
    {
      PhysicalAddress = StatePtr->FlsEraseAddress;
      /* Start Erase operation */
      Fls_lMainEraseJobStart(PhysicalAddress);
    }
    else /* Job completed successfully */
    {
#if ( FLS_17_DMU_IFX_FEE_USED ==  STD_ON )
      if(StatePtr->FlsEver != FLS_EVER_CHK)
#endif
      {
        /* [cover parentID={07585997-32B0-40db-BA8B-9D5F2EE965E6}]
        1) Set the Job result to JOB_OK
         2) Clear the EVER error in register
        [/cover] */
        /* Set to JOB_OK if no warnings  */
        LastJobResult = MEMIF_JOB_OK;

        /* clear the HW error status flags */
        BitChange = FLS_DMU_ERR_CLR;
        /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
         the object types as the address of the register is being passed.*/
        FLS_17_DMU_LIB_RUNTIME_WRITECPUENDINITPROTREG( \
            (volatile uint32 *)&DMU_HF_CLRE.U, \
            BitChange);

        /* [cover parentID={EAFDF5B9-B692-4d24-A25F-7B3CCFB27C30}]
        Call Job End Notification
        [/cover] */
        if(Fls_ConfigPtr->FlsJobEndNotificationPtr != NULL_PTR)
        {
          Fls_ConfigPtr->FlsStateVarPtr->NotifCaller =
            FLS_17_DMU_ERASE_JOB;
          /* FlsJobEndNotificationPtr should be called */
          (Fls_ConfigPtr->FlsJobEndNotificationPtr)();
          Fls_ConfigPtr->FlsStateVarPtr->NotifCaller =
            FLS_17_DMU_NO_JOB;
        }

        /* Update the global status variables */
        StatePtr->FlsJobResult = LastJobResult;
        /* Clear the Erase Job */
        StatePtr->FlsJobType = FLS_17_DMU_NONE;
        /* Clear JobStarted bit for operation JobType */
        StatePtr->JobStarted.Erase = 0U;
      }/*If the EVER flag is not set*/
#if ( FLS_17_DMU_IFX_FEE_USED ==  STD_ON )
      else
      {
        /* [cover parentID={6410DDB3-2225-441b-9086-D30B5760DB7B}]
        1) Clear EVER error
        2) Set the return value to E_NOT_OK
        [/cover] */
#if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
        Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                                FLS_17_DMU_INSTANCE_ID,
                                FLS_17_DMU_SID_MAIN,
                                FLS_17_DMU_E_ERASE_FAILED);
#endif
        /* MISRA2012_RULE_8_13_JUSTIFICATION: pointer is updated
           so it is not declared const. */
        /*Fls_lEverFlagChkFail*/
        Fls_lEverFlagChkFail();
      }
#endif
    }/* End of Job evaluation */
  }

  /* MISRA2012_RULE_8_13_JUSTIFICATION: pointer is updated
     so it is not declared const. */
}



/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax : static void Fls_lEverFlagChkFail(void)                            **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non-reentrant                                                 **
**                                                                            **
** Parameters (in) : void                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Performs the erase operation during Interrupt/Cyclic         **
**               Job handling                                                 **
*******************************************************************************/
#if (FLS_17_DMU_IFX_FEE_USED == STD_ON)
static void Fls_lEverFlagChkFail(void)
{
  /* MISRA2012_RULE_8_13_JUSTIFICATION: pointer is updated
     so it is not declared const. */
  Fls_17_Dmu_StateType       *StatePtr;
  uint32 BitChange;

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;

  StatePtr->JobStarted.Erase = 0U;

  /* Clear the failed Job  */
  StatePtr->FlsJobType = FLS_17_DMU_NONE;

  /* Update the global status variables */
  StatePtr->FlsJobResult = MEMIF_JOB_FAILED;

  /* [cover parentID={0FF9C214-3F2F-4405-8B4F-E0468E8691B8}]
  Call EVER error handler function
  [/cover] */
  if(Fls_ConfigPtr->FlsEraseVerifyErrNotifPtr != NULL_PTR)
  {
    Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_ERASE_JOB;
    /* Fls EVER Notification should be called */
    (Fls_ConfigPtr->FlsEraseVerifyErrNotifPtr)();
    Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_NO_JOB;
  }

  StatePtr->FlsEver = (uint8)0x00;
  /* [cover parentID={234A9B4E-AAB9-4095-A13A-01049F15F821}]
   Set return value as NOT OK
   [/cover] */
  /*Clear EVER error*/
  BitChange = FLS_DMU_ERR_CLR;
  /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
   the object types as the address of the register is being passed.*/
  FLS_17_DMU_LIB_RUNTIME_WRITECPUENDINITPROTREG( \
      (volatile uint32 *)&DMU_HF_CLRE.U, \
      BitChange);
}
#endif
/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax : static void Fls_lMainEraseJobStart(uint32 PhysicalAddress)        **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non-reentrant                                                 **
**                                                                            **
** Parameters (in) : Physical Address - Physical address for Erase            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Performs the erase operation during Interrupt/Cyclic         **
**               Job handling                                                 **
*******************************************************************************/
static void Fls_lMainEraseJobStart(const uint32 PhysicalAddress)
{
  /* [cover parentID={50FFF2FA-5BE1-47ee-9D53-8F56B149CCC4}]
  [/cover] */
  Fls_17_Dmu_StateType   *StatePtr;
  uint32                  SeqProtErr;

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;

  /* Indicate that the ERASE Job has been started */
  StatePtr->JobStarted.Erase = 1U;

  /* [cover parentID={89F777C5-EE77-4f9b-A44E-D82F5A75D7B6}]
  Clear all error status flags
  [/cover] */
  Fls_ClearStatusCmdCycle();

  Fls_CallEraseCommand(PhysicalAddress);

  SeqProtErr = Fls_lChkSeqProtErrors();
  /* Check for Sequence error,Protection error bit */
  if(SeqProtErr != 0U)
  {
    /* Report Runtime error code to DET */
    /* [cover parentID={2C9D2128-2F41-4b0d-BFFE-44DF7D77CE83}]
    RUNTIME ERROR DETECT  is enable
    [/cover] */
    /* [cover parentID={F83E03A0-A123-44fb-B48A-59E61F1278DE}][/cover] */
#if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
    Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                            FLS_17_DMU_INSTANCE_ID,
                            FLS_17_DMU_SID_MAIN,
                            FLS_17_DMU_E_ERASE_FAILED);
#endif
    /* [cover parentID={87AD13DF-DDF8-4cbf-B05E-EB8DF78D95F6}]
    Call error handler
    [/cover] */
    /* Call to Fls_lErrorHandler local function */
    Fls_lErrorHandler(FLS_17_DMU_ERASE);
  }
  /* Check for command cycle Timeout */
  else if (StatePtr->FlsTimeoutErr == FLS_17_DMU_ERASE)
  {
    /* Call to Fls_lErrorHandler local function */
    Fls_lErrorHandler(FLS_17_DMU_ERASE);
  }
  else
  {
    /* dummy else */
  }
}

/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax : static void Fls_lMainRead(void)                                   **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non-reentrant                                                 **
**                                                                            **
** Parameters (in) : void                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Performs the Read operation during Interrupt/Cyclic          **
**               Job handling                                                 **
*******************************************************************************/
static void Fls_lMainRead(void)
{
  Fls_17_Dmu_StateType       *StatePtr;
  Fls_17_Dmu_LengthType      ReadCount;
  MemIf_JobResultType LastJobResult;
  uint8               *SourcePtr;
  Fls_17_Dmu_LengthType      MaxRead;
  uint32    BitChange;
  /************* Initialise Local Variables *****************************/
  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;

  /* Get max read length according to the FLS mode */
  MaxRead = Fls_lGetReadModeLength();

  /* Check whether the given length is greater than MAX_READ */
  if(StatePtr->FlsReadLength > MaxRead)
  {
    /* [cover parentID={5FB65A2C-AD56-45b9-8C4E-8FEB776CF8C5}]
    1 Load upto maximum byte to read in one cycle
    2 Decreament in the readcount from the read length
    [/cover] */
    /* Load Max Byte to read in one cycle */
    ReadCount = MaxRead;
    /* Decrement the count from the total count to read */
    StatePtr->FlsReadLength = StatePtr->FlsReadLength - ReadCount;
  }
  else
  {
    ReadCount = StatePtr->FlsReadLength;
    StatePtr->FlsReadLength = 0U;
  }

  /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
         type is required to access the FLASH address/target address which
         is defined as unsigned long. */
  /* Obtain the Read Address */
  /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
    is required to check the value of the address of data buffer alignment. */
  SourcePtr = (uint8 *)(StatePtr->FlsReadAddress);

  /*Clear the ECC status bits by writing DMU_HF_ECCC.CLR with 11b to clear
       AERM bit*/

  BitChange= DMU_HF_ECCC.U | FLS_DMU_ECCC_CLR;

  /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
   the object types as the address of the register is being passed.*/
  FLS_17_DMU_LIB_RUNTIME_WRITECPUENDINITPROTREG(\
      (volatile uint32 *)&DMU_HF_ECCC.U, \
      BitChange);

  /*There is a delay of 2-3 cycles in the setting of AERM bit*/
  NOP();
  NOP();
  NOP();

  do
  {
    /* READ DATA AND STORE THE DATA AT DESTINATION */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
          type is required to access the FLASH address/target address which
              is defined as unsigned long. */
    /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
       is required to access the FLASH address/target address which is defined
            as unsigned long by AUTOSAR. */
    if( (ReadCount >= FLS_WORD_SIZE) && \
        ( (((uint32)SourcePtr & FLS_THREE_VALUE) == 0U) && \
          (((uint32)(StatePtr->FlsReadBufferPtr) & FLS_THREE_VALUE) == 0U))
      )
    {
      /* Perform Word Read to save runtime */
      /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
       the object types as the address of the register is being passed.*/
      *((uint32*)(StatePtr->FlsReadBufferPtr)) = *((uint32*)SourcePtr);

      /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
      array indexing used for FLASH address calculation and for subsequent
      traversal.The access range is within the flash address range.*/
      (StatePtr->FlsReadBufferPtr)+= FLS_WORD_SIZE;

      /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
      array indexing used for FLASH address calculation and for subsequent
      traversal.The access range is within the flash address range.*/
      SourcePtr+= FLS_WORD_SIZE;
      ReadCount -= FLS_WORD_SIZE;
    }
    else
    {
      *(StatePtr->FlsReadBufferPtr) = *SourcePtr;
      (StatePtr->FlsReadBufferPtr)++;
      SourcePtr++;
      ReadCount--;
    }

  } while(((ReadCount)) > 0U);

  /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
  type is required to access the FLASH address/target address which
  is defined as unsigned long. */
  /* Update the Read Address */
  /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
       is required to access the FLASH address/target address which is defined
       as unsigned long by AUTOSAR. */
  StatePtr->FlsReadAddress = (uint32)SourcePtr;

  /* Check for single bit or double bit error */
  /* [cover parentID={D4143E91-3525-40a6-AA60-1288984E9CDD}][/cover] */
  /* [cover parentID={302E132C-2856-4b4a-B8AA-91F03C20F774}][/cover] */
  if(Fls_lChkBitErrors() != 0U)
  {
    /* FLS106: Read Job fails due to hardware error */
    /* Report Runtime error code to DET */

#if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
    /* [cover parentID={92669E25-ACD5-4801-B823-1F84B968A8AB}]
    Report DET error
    [/cover] */
    /* [cover parentID={6F22C8E9-7345-4936-9BD1-F7D343DB53B5}][/cover] */
    Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                            FLS_17_DMU_INSTANCE_ID,
                            FLS_17_DMU_SID_MAIN,
                            FLS_17_DMU_E_READ_FAILED);
#endif
    /* Call to Fls_lErrorHandler local function */
    Fls_lErrorHandler(FLS_17_DMU_READ);
  }
  else
  {

    if(StatePtr->FlsReadLength == 0U)
    {
      /* [cover parentID={77587821-AD60-4f95-98BF-8E5C42054191}]
      1 Set the job result as OK
      2 Set that there is no ongoing job
      [/cover] */
      /* Set Job Result to JOB OK if no warnings */
      LastJobResult = MEMIF_JOB_OK;
      /* 1. Clear the Job request */
      StatePtr->FlsJobType = FLS_17_DMU_NONE;

      /* 2. Update the global status variables */
      StatePtr->FlsJobResult = LastJobResult;
      /* [cover parentID={0259A84F-7D9C-4700-8168-DE22E9A1E239}]
      1 Set the notification caller as read
      2 Fls_JobEndNotification
      3 Set notification caller as none
      [/cover] */



      if(Fls_ConfigPtr->FlsJobEndNotificationPtr != NULL_PTR)

      {
        Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_READ_JOB;
        /* FlsJobEndNotificationPtr should be called */
        (Fls_ConfigPtr->FlsJobEndNotificationPtr)();
        Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_NO_JOB;
      }
    }
  }
}

/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax : static void Fls_lMainCompare(void)                                **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non-reentrant                                                 **
**                                                                            **
** Parameters (in) : void                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Performs the Compare operation during Interrupt/Cyclic       **
**               Job handling                                                 **
*******************************************************************************/
static void Fls_lMainCompare(void)
{
  Fls_17_Dmu_StateType       *StatePtr;
  Fls_17_Dmu_LengthType      ReadCount;
  MemIf_JobResultType LastJobResult;
  uint8               *SourcePtr;
  Fls_17_Dmu_LengthType      MaxRead;
  uint32 BitChange;

  /************ Initialise Local variables ****************************/
  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;

  LastJobResult = StatePtr->FlsJobResult;

  /* Get max read length according to the FLS mode */
  MaxRead = Fls_lGetReadModeLength();

  /* Check whether the given length is greater than MAX_READ */
  if(StatePtr->FlsReadLength > MaxRead)
  {
    /* Load Max Byte to read in one cycle */
    ReadCount = MaxRead;
    /* Decrement the count from the totalcount to read */
    StatePtr->FlsReadLength = StatePtr->FlsReadLength - ReadCount;
  }
  else
  {
    ReadCount = StatePtr->FlsReadLength;
    StatePtr->FlsReadLength = 0U;
  }

  /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
         type is required to access the FLASH address/target address which
         is defined as unsigned long. */
  /* Obtain the address for the compare operation */
  /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
    is required to check the value of the address of data buffer alignment. */
  SourcePtr = (uint8 *)(StatePtr->FlsReadAddress);
  /**********************************************************************/
  /*Clear the ECC status bits by writing DMU_HF_ECCC.CLR with 11b to clear
             AERM bit*/
  BitChange= DMU_HF_ECCC.U | FLS_DMU_ECCC_CLR;

  /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
   the object types as the address of the register is being passed.*/
  FLS_17_DMU_LIB_RUNTIME_WRITECPUENDINITPROTREG(\
      (volatile uint32 *)&DMU_HF_ECCC.U, \
      BitChange);
  /*Clearing of AERM takes 2-3 cycles so NOP added*/
  NOP();
  NOP();
  NOP();

  /* [cover parentID={84AD1E8E-BFE0-4fc7-972E-7B9B98589DD5}]
  Load Maximum read length in one cycle
  Decrement the count from the totalcount to read
  [/cover] */
  /* [cover parentID={96D97A74-2893-447e-9ECB-862994692748}]
  Load Maximum read length in one cycle
  Decrement the count from the totalcount to read
  [/cover] */
  do
  {
    /* Check if Address is word aligned */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
               type is required to access the FLASH address/target address which
               is defined as unsigned long. */
    /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
    is required to access the FLASH address/target address which is defined
         as unsigned long by AUTOSAR. */
    if( (((uint32)SourcePtr & (FLS_WORD_SIZE - 1U)) == 0U) && \
        ((((uint32)(StatePtr->FlsReadBufferPtr) & (FLS_WORD_SIZE - 1U)) == 0U) && \
         (ReadCount >= FLS_WORD_SIZE)  )
      )
    {
      /* COMPARE THE FLASH DATA WITH THE BUFFER DATA (Word Compare) */

      /* [cover parentID={5682713B-550E-4420-9B0E-654C2B5D3DCC}]
      Is read data same as the data in application buffer?
      [/cover] */
      /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
       the object types as the address of the register is being passed.*/
      if( *(uint32*)(StatePtr->FlsReadBufferPtr) != *(uint32*)SourcePtr )
      {
        LastJobResult = MEMIF_BLOCK_INCONSISTENT;
        /* No need to compare any more data */
        ReadCount = 0U;
      }
      else
      {

        /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
        array indexing used for FLASH address calculation and for subsequent
        traversal.The access range is within the flash address range.*/
        StatePtr->FlsReadBufferPtr += FLS_WORD_SIZE;
        /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
        array indexing used for FLASH address calculation and for subsequent
        traversal.The access range is within the flash address range.*/
        SourcePtr += FLS_WORD_SIZE;
        ReadCount -= FLS_WORD_SIZE;
      }
    }
    else
    {
      /* COMPARE THE FLASH DATA WITH THE BUFFER DATA (Byte Compare)*/
      if( *(StatePtr->FlsReadBufferPtr) != *SourcePtr )
      {
        LastJobResult = MEMIF_BLOCK_INCONSISTENT;
        /* No need to compare any more data */
        ReadCount = 0U;

      }
      else
      {
        StatePtr->FlsReadBufferPtr++;
        SourcePtr++;
        ReadCount--;
      }
    }
  } while(ReadCount > 0U);

  /* Update the compare address */
  /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
         type is required to access the FLASH address/target address which
         is defined as unsigned long. */
  /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
       is required to access the FLASH address/target address which is defined
       as unsigned long by AUTOSAR. */
  StatePtr->FlsReadAddress = (uint32)SourcePtr;

  /* Check if Non-correctable ECC error was present thus leading to failure */
  /* [cover parentID={DCCFF8A5-DD86-4ecc-A556-28FB6602A239}]
  Is there a double bit error?
  [/cover] */
  if(Fls_lChkBitErrors() != 0U)
  {
    /* FLS154: Compare Job fails due to hardware error */
    /* Report Runtime error code to DET */
#if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
    /* [cover parentID={7591DC07-140C-4b4e-8510-54802D302B2E}]
    Report DET error
    [/cover] */
    /* [cover parentID={19718F5D-689F-4517-9BA3-4A5D885A880D}]
    Runtime error detection enabled
    [/cover] */

    /* [cover parentID={B470BE47-3CD0-4305-9459-571463415BE4}]
    Runtime error detection enabled
    [/cover] */
    /* [cover parentID={A0D1D46A-3DB3-4600-891E-A0FA4EC170A2}][/cover] */
    Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                            FLS_17_DMU_INSTANCE_ID,
                            FLS_17_DMU_SID_MAIN,
                            FLS_17_DMU_E_COMPARE_FAILED);
#endif
    /* Call to Fls_lErrorHandler local function */
    /* [cover parentID={73342B23-2462-499b-972A-3823E7562B71}]
    Call Error Handler Function
    [/cover] */
    /* [cover parentID={BAD53F8B-F256-4532-831D-7D748194502D}]
    Call Error Handler Function
    [/cover] */
    Fls_lErrorHandler(FLS_17_DMU_COMPARE);
  }
  /* Check if block was inconsistent */
  /* [cover parentID={35ED35F9-22F7-4f28-A25B-7D9B60254218}]
  Set job result as inconsistent
  Set job status of compare to 0
  Set there is no ongoing job
  [/cover] */
  else if(LastJobResult == MEMIF_BLOCK_INCONSISTENT)
  {
    /* Update the global status variables */
    StatePtr->FlsJobResult = LastJobResult;

    /* Clear the failed Job  */
    StatePtr->FlsJobType = FLS_17_DMU_NONE;

    /* Clear the errors status flags */
    BitChange = FLS_DMU_ERR_CLR;
    /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
     the object types as the address of the register is being passed.*/
    FLS_17_DMU_LIB_RUNTIME_WRITECPUENDINITPROTREG( \
        (volatile uint32 *)&DMU_HF_CLRE.U, \
        BitChange);


    if(Fls_ConfigPtr->FlsJobErrorNotificationPtr != NULL_PTR)
    {
      Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_COMPARE_JOB;
      /* FlsJobErrorNotificationPtr should be called */
      (Fls_ConfigPtr->FlsJobErrorNotificationPtr)();
      Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_NO_JOB;
    }
  }
  /* No failures detected */
  else
  {
    /* Job completed */
    if ( StatePtr->FlsReadLength == 0U)
    {

      /* [cover parentID= {8FF67721-99AB-45e9-91AA-6D6D80FFC27C}]
      Set job status of compare to zero
      job result as OK
      Set there is no ongoing job type
      Call FlsJobEndNotificationPtr
      [/cover] */
      /* Update the result to JOB_OK if no warnings */
      LastJobResult = MEMIF_JOB_OK;

      /* 1. Update the Global Status variables */
      StatePtr->FlsJobResult = LastJobResult;
      /* [cover parentID={B77444DF-4D03-4166-8254-49CFB07AC5C3}]
      Set job status of compare to zero
      job result as OK
      Set there is no ongoing job type
      Call FlsJobEndNotificationPtr
      [/cover] */
      /* 2. Clear the Job request */
      StatePtr->FlsJobType = FLS_17_DMU_NONE;

      /* [cover parentID={D3413F47-7A16-47e1-AEC4-2342302E38C2}]
      Set notification caller as comapre
      Fls_JobErrorNotification
      Set notification caller as none
      [/cover] */


      if(Fls_ConfigPtr->FlsJobEndNotificationPtr != NULL_PTR)


      {
        Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_COMPARE_JOB;
        /* FlsJobEndNotificationPtr should be called */
        (Fls_ConfigPtr->FlsJobEndNotificationPtr)();
        Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_NO_JOB;
      }

    }
    /* Job not yet completed */
    else
    {
      /* Avoid MISRA error */
    }
  }
}

/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax : static void Fls_lMainBlankCheck(void)                             **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non-reentrant                                                 **
**                                                                            **
** Parameters (in) : void                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Performs the Blank Check operation during Interrupt/Cyclic   **
**               Job handling                                                 **
*******************************************************************************/
static void Fls_lMainBlankCheck(void)
{
  Fls_17_Dmu_StateType       *StatePtr;
  Fls_17_Dmu_LengthType      ReadCount;
  MemIf_JobResultType LastJobResult;
  uint8               *SourcePtr;
  Fls_17_Dmu_LengthType      MaxRead;
  uint32 BitChange;

  /************ Initialise Local variables ****************************/
  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;

  LastJobResult = StatePtr->FlsJobResult;

  /* Get max read length according to the FLS mode */
  MaxRead = Fls_lGetReadModeLength();

  /* Check whether the given length is greater than MAX_READ */
  if(StatePtr->FlsReadLength > MaxRead)
  {
    /* Load Max Byte to read in one cycle */
    ReadCount = MaxRead;
    /* Decrement the count from the totalcount to read */
    StatePtr->FlsReadLength = StatePtr->FlsReadLength - ReadCount;
  }
  else
  {
    ReadCount = StatePtr->FlsReadLength;
    StatePtr->FlsReadLength = 0U;
  }
  /* Obtain the address for the Blank Check operation */
  /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
         type is required to access the FLASH address/target address which
         is defined as unsigned long. */
  /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
       is required to access the FLASH address/target address which is defined
       as unsigned long by AUTOSAR. */
  SourcePtr = (uint8 *)(StatePtr->FlsReadAddress);
  /**********************************************************************/

  /*Clear the ECC status bits by writing DMU_HF_ECCC.CLR with 11b to clear
             AERM bit*/


  BitChange= DMU_HF_ECCC.U | FLS_DMU_ECCC_CLR;

  /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
  the object types as the address of the register is being passed.
  MISRA2012_RULE_11_1_JUSTIFICATION: Pointer cast is required to match
  the object types.*/
  FLS_17_DMU_LIB_RUNTIME_WRITECPUENDINITPROTREG(\
      (volatile uint32 *)&DMU_HF_ECCC.U, \
      BitChange);
  /*Clearing of AERM bits takes 2-3 cyles so added NOP*/
  NOP();
  NOP();
  NOP();
  do
  {
    /* Check if Address is word aligned */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
              type is required to access the FLASH address/target address which
              is defined as unsigned long. */
    /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
     is required to access the FLASH address/target address which is defined
     as unsigned long by AUTOSAR. */
    if((((uint32)SourcePtr & (FLS_WORD_SIZE - 1U)) == 0U) &&
        (ReadCount >= FLS_WORD_SIZE))
    {
      /* Check if the flash data is in erased state? (Word Compare)*/
      /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
       the object types as the address of the register is being passed.*/
      if(FLS_17_DMU_DEFAULT_ERASEVALUE != *(uint32*)SourcePtr )
      {
        /* [cover parentID={E7330B53-EDD0-4308-B861-971923B9CADF}]
        1 Load upto MAX byte to read in one cycle
        2 Decreament of readcount from the read length
        [/cover] */
        LastJobResult = MEMIF_JOB_FAILED;
        /* No need to compare any more data */
        ReadCount = 0U;
      }
      else
      {

        /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
          is required to access the FLASH address/target address which is defined
          as unsigned long by AUTOSAR. */
        /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
        array indexing used for FLASH address calculation and for subsequent
        traversal.The access range is within the flash address range.
        */
        SourcePtr += FLS_WORD_SIZE;
        ReadCount -= FLS_WORD_SIZE;
      }
    }
    else
    {
      /* Check if the flash data is in erased state? (Byte Compare)*/

      /* [cover parentID={CAB7A2DB-9E3D-4253-9E31-7E5EC5616431}]
      [/cover] */
      if( FLS_17_DMU_DEFAULT_ERASEVALUE != *SourcePtr )
      {
        LastJobResult = MEMIF_JOB_FAILED;
        /* No need to compare any more data */
        ReadCount = 0U;

      }
      else
      {
        SourcePtr++;
        ReadCount--;
      }
    }
  } while(ReadCount > 0U);

  /* Update the compare address */
  /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
         type is required to access the FLASH address/target address which
         is defined as unsigned long. */
  /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
       is required to access the FLASH address/target address which is defined
       as unsigned long by AUTOSAR. */
  StatePtr->FlsReadAddress = (uint32)SourcePtr;
  /* [cover parentID={FA4F9C52-6FF3-488f-AA99-3ABA91C3B53B}]
  [/cover] */

  /* [cover parentID={6330B07D-5056-45d5-A964-E6F1D989D1BE}]
  [/cover] */
  /* Check if Non-correctable ECC error was present thus leading to failure */
  if(Fls_lChkBitErrors() != 0U)
  {
    /* [cover parentID={C1F08F76-66E8-49a5-A8AE-3B820D2979E5}]
    [/cover] */
    /* Blank Check Job fails due to hardware error */
    /* Report Runtime error code to DET */
#if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
    Det_ReportRuntimeError((uint16)FLS_17_DMU_MODULE_ID,
                           FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_MAIN,
                           FLS_17_DMU_E_BLANKCHECK_FAILED);
#endif
    /* Call to Fls_lErrorHandler local function */
    Fls_lErrorHandler(FLS_17_DMU_BLANKCHECK);
  }

  /* [cover parentID={66EC1E14-CC95-4ffd-A207-004A4D20237B}]
  1 Job result is inconsistent
  2 Set Job status of Blankcheck to 0
  3 Set flash job type to none
  [/cover] */
  /* Check if block was inconsistent */
  else if(LastJobResult == MEMIF_JOB_FAILED)
  {
    /* Update the global status variables */
    StatePtr->FlsJobResult = LastJobResult;

    /* Clear the failed Job */
    StatePtr->FlsJobType = FLS_17_DMU_NONE;

    /* Clear the errors status flags */
    BitChange = FLS_DMU_ERR_CLR;
    /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
     the object types as the address of the register is being passed.*/
    FLS_17_DMU_LIB_RUNTIME_WRITECPUENDINITPROTREG( \
        (volatile uint32 *)&DMU_HF_CLRE.U, \
        BitChange);


    if(Fls_ConfigPtr->FlsJobErrorNotificationPtr != NULL_PTR)
    {
      Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_BLANKCHECK_JOB;
      /* FlsJobErrorNotificationPtr should be called */
      /* [cover parentID={7343C2F5-4978-41ad-A5DD-F465827A5F2E}]
      Call FlsJobErrorNotificationPtr
      [/cover] */
      (Fls_ConfigPtr->FlsJobErrorNotificationPtr)();
      Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_NO_JOB;
    }

  }
  /* No failures detected */
  else
  {
    /* Job completed */
    if ( StatePtr->FlsReadLength == 0U)
    {
      /* [cover parentID={A6B380AF-9ADE-4208-AC1C-E7CA3AA634C5}]
      1 Set job status to blank check to zero
      2 Set job result to ok
      3 Set job type to none
      [/cover] */
      /* Update the result to JOB_OK if no warnings */
      LastJobResult = MEMIF_JOB_OK;

      /* 1. Update the Global Status variables */
      StatePtr->FlsJobResult = LastJobResult;

      /* 2. Clear the Job request */
      StatePtr->FlsJobType = FLS_17_DMU_NONE;



      if(Fls_ConfigPtr->FlsJobEndNotificationPtr != NULL_PTR)

      {
        Fls_ConfigPtr->FlsStateVarPtr->NotifCaller =
          FLS_17_DMU_BLANKCHECK_JOB;
        /* FlsJobEndNotificationPtr should be called */
        (Fls_ConfigPtr->FlsJobEndNotificationPtr)();
        Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_NO_JOB;
      }

    }
    /* Job not yet completed */
    else
    {
      /* Avoid MISRA error */
    }
  }
}
/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax : static void Fls_lMainWrite(void)                                  **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non-reentrant                                                 **
**                                                                            **
** Parameters (in) : void                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Performs the Write operation during Interrupt/Cyclic         **
**               Job handling                                                 **
*******************************************************************************/
/*CYCLOMATIC_Fls_lMainWrite_JUSTIFICATION:The complexity of this function is 17
 as it has to check for many conditions which include checking for FLS operation
 with both IFX FEE as well as FLS stand-alone mode. Breaking it into another
 local function will break the continuity of the checks */
static void Fls_lMainWrite(void)
{
  Fls_17_Dmu_StateType       *StatePtr;
  MemIf_JobResultType LastJobResult;
  volatile uint32     PhysicalAddress;
  boolean             Error;
  uint8               PageLength;
  uint32     BitChange;

  /******************* Initialise local variables ********************/
  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;

  /* Setting the PhysicalAddress to DF0 start address for Command cycle
    execution */
  /* [cover parentID={0FCF07E2-45ED-4c11-9ED4-304D1A5D5D57}]
  Setting the physical address
  [/cover] */
  PhysicalAddress = FLS_17_DMU_BASE_ADDRESS;

  /* Check for operational error */
  /* [cover parentID={E251B206-AC59-454e-9753-A7F656DA9A39}]
  Is Operation error detected?
  [/cover] */
  if(Fls_lChkOperError() != 0U)
  {
    /* FLS105: Write Job fails due to hardware error */
    /* Report Runtime error code to DET */
    /* [cover parentID={9DBA2EF8-1257-4861-A9E1-FE185EA3057F}]
    Runtime error detect is enabled
    [/cover] */
#if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
    /* [cover parentID={8F543077-AC3A-4c9c-BB33-3D93A7254B8A}]
    Report DET
    [/cover] */
    /* [cover parentID={90B6ED4E-82EC-4caf-8347-06E7DFB7D392}][/cover] */
    Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                            FLS_17_DMU_INSTANCE_ID,
                            FLS_17_DMU_SID_MAIN,
                            FLS_17_DMU_E_WRITE_FAILED);
#endif
    Error = (boolean)TRUE;
  }

  /* [cover parentID= {44BD2BAB-C1B6-4419-A1D1-39B07A345F18}]
  Is PVER detected ?
  [/cover] */
  /* Check for Program verification error */
#if(FLS_17_DMU_IFX_FEE_USED == STD_OFF)
#if(FLS_17_DMU_VER_ERROR_CHECK == STD_ON)
  else if((boolean)TRUE == Fls_lPverChk())
  {
    Error = (boolean)TRUE;
#if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
    /* [cover parentID={8F543077-AC3A-4c9c-BB33-3D93A7254B8A}]
    Report DET
    [/cover] */
    /* [cover parentID={90B6ED4E-82EC-4caf-8347-06E7DFB7D392}][/cover] */
    /* [cover parentID={F302EE24-5CB9-4e2c-9C95-299CAE58EFAC}]
    Report Runtime Error in case PVER.
    [/cover] */
    Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                            FLS_17_DMU_INSTANCE_ID,
                            FLS_17_DMU_SID_MAIN,
                            FLS_17_DMU_E_WRITE_FAILED);
#endif
  }
#endif  /* FLS_VER_ERROR_CHECK == STD_ON */
#endif  /* FLS_17_DMU_IFX_FEE_USED == STD_OFF */
  else
  {
    if( Fls_lGetWriteMode() == FLS_17_DMU_PAGE_WRITE)
    {
      PageLength = FLS_17_DMU_PAGE_SIZE;
    }
    else
    {
      PageLength = FLS_17_DMU_BURST_PAGE_SIZE;
    }

/* [cover parentID={BDE41DC2-AFE0-4d98-A61A-AA6C95323691}][/cover] */
#if (FLS_17_DMU_IFX_FEE_USED == STD_OFF)
#if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
                                (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
    /* Check for DFLASHx Page content equal to Source value */
    /* [cover parentID={1A741C58-2C53-40a7-B9A0-749471C2CF91}]
    Check for DFLASHx Page content equal to Source value
    (check whether written data same as the data in the Write Buffer)
    [/cover] */
    Error = Fls_lCheckWrittenPage((uint32)PageLength);
#else
    Error = (boolean)FALSE;
#endif /* FLS_17_DMU_DEV_ERROR_DETECT == STD_ON */
#else
    Error = (boolean)FALSE;
#endif /* FLS_17_DMU_IFX_FEE_USED == STD_OFF */

    /* PageStartAddress is incremented by PageLength bytes */
    StatePtr->FlsWriteAddress += PageLength;
    /* length is decremented by PageLength */
    StatePtr->FlsWriteLength -= PageLength;

    /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
     array indexing used for FLASH address calculation and for subsequent
       traversal.The access range is within the flash address range.*/
    StatePtr->FlsWriteBufferPtr = (StatePtr->FlsWriteBufferPtr + \
                                   PageLength);

  }

  if(Error == (boolean)FALSE)
  {

    /* [cover parentID={2369B0F7-D19B-4c7c-BEFE-F6B7D389E0A6}]
    Update job result to OK
    Update job type as NONE
    Clear the Write Job Started Status bit
    [/cover] */
    /* [cover parentID={44BD2BAB-C1B6-4419-A1D1-39B07A345F18}]
    Is PVER detected ?
    [/cover] */
    /* Check for Program verification error */
#if(FLS_17_DMU_IFX_FEE_USED == STD_ON)
#if(FLS_17_DMU_VER_ERROR_CHECK == STD_ON)
    if ((boolean)TRUE == Fls_lPverChk())
    {
      /* update FlsPver to be used in CompareWordsSync */
      StatePtr->FlsPver = 1U;
    }
#endif  /* FLS_VER_ERROR_CHECK == STD_ON */
#endif  /* FLS_17_DMU_IFX_FEE_USED == STD_ON */

    /* Check for Flash write Job is finished completely  */
    if(StatePtr->FlsWriteLength == 0U)
    {
#if(FLS_17_DMU_IFX_FEE_USED == STD_ON)
      /* [cover parentID={2885FE31-54BB-4d44-AC7D-61D46743EA2E}]
      Is the PVER flag set ?
      [/cover] */
      if( StatePtr->FlsPver == 0U)
#endif
      {
        /* [cover parentID={66D9DABC-41EA-49b1-9AE6-E7A0C8A49071}]
        Update job result to OK
        Update job type as NONE
        Clear the Write Job Started Status bit
        [/cover] */

        /* Indicate Job successfully completed if no warnings seen till now */
        LastJobResult = MEMIF_JOB_OK;
        /* 1. Update the global status variables */
        StatePtr->FlsJobResult = LastJobResult;
        /* 2. Clear the Write Job */
        StatePtr->FlsJobType = FLS_17_DMU_NONE;
        /* 3. Clear the Write Job Started Status bit */
        StatePtr->JobStarted.Write = 0U;
        /* [cover parentID={C938F682-00F1-4522-850E-78314BCAB1F6}]
          Execute Clear Status command
         [/cover] */
        /* Clear the errors status flags */
        BitChange = FLS_DMU_ERR_CLR;
        /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
         the object types as the address of the register is being passed.*/
        FLS_17_DMU_LIB_RUNTIME_WRITECPUENDINITPROTREG( \
            (volatile uint32 *)&DMU_HF_CLRE.U, \
            BitChange);

        if(Fls_ConfigPtr->FlsJobEndNotificationPtr != NULL_PTR)
        {
          Fls_ConfigPtr->FlsStateVarPtr->NotifCaller =
            FLS_17_DMU_WRITE_JOB;
          /* FlsJobEndNotificationPtr should be called */
          /* [cover parentID={4B4F32E7-87B9-49ce-B939-0A151BE7A414}]
          Call FlsJobEndNotification
          [/cover] */
          (Fls_ConfigPtr->FlsJobEndNotificationPtr)();
          Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_NO_JOB;
        }
      }
#if(FLS_17_DMU_IFX_FEE_USED == STD_ON)
      else
      {
#if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
        Det_ReportRuntimeError( (uint16)FLS_17_DMU_MODULE_ID,
                                FLS_17_DMU_INSTANCE_ID,
                                FLS_17_DMU_SID_MAIN,
                                FLS_17_DMU_E_WRITE_FAILED);
#endif

        /* Update the global status variables */
        StatePtr->FlsJobResult = MEMIF_JOB_FAILED;
        /* 2. Clear the Write Job */
        StatePtr->FlsJobType = FLS_17_DMU_NONE;
        /* 3. Clear the Write Job Started Status bit */
        StatePtr->JobStarted.Write = 0U;

        /* Clear the errors status flags */
        BitChange = FLS_DMU_ERR_CLR;
        /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
         the object types as the address of the register is being passed.*/
        FLS_17_DMU_LIB_RUNTIME_WRITECPUENDINITPROTREG( \
            (volatile uint32 *)&DMU_HF_CLRE.U, \
            BitChange);
        StatePtr->FlsPver = (uint8)0x00;

        if(Fls_ConfigPtr->FlsProgVerifyErrNotifPtr != NULL_PTR)
        {
          Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_WRITE_JOB;
          /* Fls PVER Notification should be called */
          (Fls_ConfigPtr->FlsProgVerifyErrNotifPtr)();
          Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_NO_JOB;
        }
      }
#endif
    }
    else /*Write Operation not finished, writeLength not zero*/
    {
#if (FLS_17_DMU_IFX_FEE_USED == STD_OFF)
#if  (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
                                     (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
      /* CHECK FOR DFLASHx PAGE IS ERASED */
      /* [cover parentID={4FEA93A2-7C3E-4cf1-ABEB-A3C7CE5AC41D}]
      Call function to verify if the page is erased corretly
      [/cover]*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
                type is required to access the FLASH address/target address which
                is defined as unsigned long. */
      /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
            is required to store the FLASH address/target address in state var
                  structure to perform easy arithmetic operations. */
      if(Fls_lPageEraseCheck((uint32 *)(StatePtr->FlsWriteAddress),
                             StatePtr->FlsWriteLength,FLS_17_DMU_SID_MAIN) != E_OK)
      {
        Error = (boolean)TRUE;
        /* [cover parentID={70C26BA9-D5DA-4915-AA93-958065DF6E35}]
        Call error handler
        [/cover] */
        Fls_lErrorHandler(FLS_17_DMU_WRITE);
      }
      /* Check needed only when DET is STD_ON */
      if(Error == (boolean)FALSE)
#endif /* FLS_17_DMU_DEV_ERROR_DETECT == STD_ON */
#endif /* FLS_17_DMU_IFX_FEE_USED == STD_OFF */
      {
        /* Start Write operation */
        Fls_lMainWriteJobStart(PhysicalAddress);
      }
    }
  }
  else
  {
    /*[cover parentID={66F08F3E-6331-476a-9509-C52646D79C4F}][/cover]*/
    /* Call to Fls_lErrorHandler local function */
    Fls_lErrorHandler(FLS_17_DMU_WRITE);
  }
  /*[cover parentID={8B75A26F-E481-48c0-95A2-7BDA263BC235}][/cover]*/
}/* end of Fls_lMainWrite */

/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax : static void Fls_lMainWriteJobStart(uint32 PhysicalAddress)        **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non-reentrant                                                 **
**                                                                            **
** Parameters (in) : Physical Address - Physical address for Write            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Performs the Write operation during Interrupt/Cyclic         **
**               Job handling                                                 **
*******************************************************************************/
static void Fls_lMainWriteJobStart(const uint32 PhysicalAddress)
{
  Fls_17_Dmu_StateType   *StatePtr;
  uint32                  SeqProtErr;
  uint8                   WriteMode;

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;

  /* Mark that the Job has been started */
  StatePtr->JobStarted.Write = 1U;
  /* Obtain the write mode (Page or Burst) */
  WriteMode = Fls_lGetWriteMode();

  /* [cover parentID={D5529673-60AA-40d6-8AB4-8B6CA095B1B2}]
  Clear all error status flags
  [/cover] */
  Fls_ClearStatusCmdCycle();

  /************* Call Write command sequence *************/
  Fls_CallWriteCommand(PhysicalAddress,StatePtr,WriteMode);

  SeqProtErr = Fls_lChkSeqProtErrors();

  /* Check for Sequence error,Protection error bit */
  if(SeqProtErr != 0U)
  {
    /* Report Runtime error code to DET */
    /* [cover parentID={07A17BE6-2107-4b68-AF7F-465E75DEF002}]
    RUNTIME ERROR DETECT is enabled
    [/cover] */
    /* [cover parentID={90B6ED4E-82EC-4caf-8347-06E7DFB7D392}][/cover] */
#if (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
    Det_ReportRuntimeError((uint16)FLS_17_DMU_MODULE_ID,
                           FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_MAIN,
                           FLS_17_DMU_E_WRITE_FAILED);
#endif
    /* Call to Fls_lErrorHandler local function */
    Fls_lErrorHandler(FLS_17_DMU_WRITE);
  }
  /* Check for Command Cycle Timeout Error */
  else if (StatePtr->FlsTimeoutErr == FLS_17_DMU_WRITE)
  {
    /* As per AI00157728 - timeout error need not be reported to DEM */
    /* Call to Fls_lErrorHandler local function */
    Fls_lErrorHandler(FLS_17_DMU_WRITE);
  }
  else
  {
    /* dummy else */
  }
}


/*******************************************************************************
** Traceability :   [cover parentID={F146E9B8-8D93-44e6-B685-4512CD9D7996}]   **
**                                                                            **
** Syntax : void Fls_17_Dmu_Isr(void)                                         **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : void                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : This routine is used instead of Main function if configured  **
** for Erase and Write Jobs.                                                  **
*******************************************************************************/
/*[cover parentID={88F8A5C9-CCDB-40bd-A8A2-5DB65E9BA807}][/cover]*/
#if( FLS_17_DMU_USE_INTERRUPTS == STD_ON)
/* [cover parentID={ACBA93D7-451E-46e4-8042-0709418579B2}]
Flash use interrupts is enable
[/cover] */
/* [cover parentID={C4627507-8FE4-4c06-9B52-A03B36EC1995}][/cover] */
void Fls_17_Dmu_Isr(void)
{
  const Fls_17_Dmu_StateType  *StatePtr;
  uint8 JobType;
  uint32 FlashFsrStatus;

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  JobType = StatePtr->FlsJobType;

  if( JobType != FLS_17_DMU_NONE)
    /* [cover parentID={7846D57A-04E4-4ad7-B320-FDFB964B2EC7}]
    Is there any pending job?
    [/cover] */
  {

    FlashFsrStatus = (uint32)DMU_HF_SUSPEND.B.SPND;
    /************************** ERASE *********************************/
    if(JobType == FLS_17_DMU_ERASE)
    {
      /* [cover parentID={B7670FE3-88FD-4d64-B7F3-F16B62DD9146}]
      Is HW Busy ?
      [/cover] */
      if((Fls_lHWBusyCheck() == 0U) && (FlashFsrStatus == 0U))
      {
        /* Fls_Main_Erase operation should be called  */
        Fls_lMainErase();
      }

#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
      else
      {
        /* [cover parentID={7BDF663C-A923-4b45-AA3F-A684EA2B79D2}]
        Raise Safety Error Invalid ISR
        [/cover] */
        Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID,FLS_17_DMU_INSTANCE_ID,
                               FLS_17_DMU_SID_ISR,FLS_17_DMU_E_INVALID_ISR);
      }
#endif

    }
    /* [cover parentID={B54EA47D-6C51-47a0-856A-126E54F4DB1A}]
    Is write job pending?
    [/cover] */
    /************************** WRITE *********************************/
    else if(JobType == FLS_17_DMU_WRITE)
    {
      if(Fls_lHWBusyCheck() == 0U)
      {
        /* Fls_Main_Wrire operation should be called  */
        Fls_lMainWrite();
      }
#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
      else
      {
        /*Invalid Interrupt Safety error */
        Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID,FLS_17_DMU_INSTANCE_ID,
                               FLS_17_DMU_SID_ISR,FLS_17_DMU_E_INVALID_ISR);
      }
#endif
    }
    else
    {
      /*Avoid MISRA*/
    }
  }
#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  else /*If the Driver is IDLE or main write/erase is not called*/
  {
    /*Invalid Interrupt Safety error */
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID,FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_ISR,FLS_17_DMU_E_INVALID_ISR);
  }
#endif
}
/* FLS_USE_INTERRUPTS == STD_ON */
#endif



/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax : static void Fls_lErrorHandler(uint8 JobType)                      **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : JobType                                                  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : This routine is called when error occurred during            **
**               flash operations                                             **
*******************************************************************************/
static void Fls_lErrorHandler(const uint8 JobType)
{
  Fls_17_Dmu_StateType  *StatePtr;
  uint32 BitChange;

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  if(JobType == FLS_17_DMU_ERASE)
  {
    StatePtr->JobStarted.Erase = 0U;
  }
  else if(JobType == FLS_17_DMU_WRITE)
  {
    StatePtr->JobStarted.Write = 0U;
  }
  else
  {
    /* Avoid MISRA 60 */
  }

  /* Clear the failed Job  */
  if(StatePtr->FlsJobType == JobType)
  {
    StatePtr->FlsJobType = FLS_17_DMU_NONE;
  }
  /* [cover parentID={2FEEDAEA-263F-4340-B44A-6067DDC65352}]
  Clear the failed job
  Set the job result to failed
  Reset job started status for the job failed
  Set that there is no job ongoing
  [/cover] */
  /* Update the global status variables */
  StatePtr->FlsJobResult = MEMIF_JOB_FAILED;

  /* Clear the errors status flags */
  BitChange = FLS_DMU_ERR_CLR;
  /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
   the object types as the address of the register is being passed.*/
  FLS_17_DMU_LIB_RUNTIME_WRITECPUENDINITPROTREG( \
      (volatile uint32 *)&DMU_HF_CLRE.U, \
      BitChange);

  if(Fls_ConfigPtr->FlsJobErrorNotificationPtr != NULL_PTR)
  {
    Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = JobType;
    /* FlsJobErrorNotificationPtr should be called */
    (Fls_ConfigPtr->FlsJobErrorNotificationPtr)();
    Fls_ConfigPtr->FlsStateVarPtr->NotifCaller = FLS_17_DMU_NO_JOB;
  }
}

#if (FLS_17_DMU_USE_ERASESUSPEND == STD_ON)
/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax: LOCAL_INLINE boolean Fls_lSpndTimeout(uint32 TimeOutCount)         **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : TimeOutCount - Value of the Timeout count                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : boolean                                                  **
**                                                                            **
** Description : This routine checks if erase suspend error or timeout error  **
**               occured                                                      **
*******************************************************************************/
LOCAL_INLINE boolean Fls_lSpndTimeout(const uint32 TimeOutCount)
{
  boolean RetVal;
  uint32 BitChange;

  if (DMU_HF_SUSPEND.B.ERR == 1U) /*Suspend Error*/
  {
    /* [cover parentID={3C9E5EF2-E33D-43a2-9B3E-3B318D4BD80E}]
    Raise Safety Error
    [/cover] */
#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_SUSPENDERASE,
                           FLS_17_DMU_E_SUSPNDERASE_FAIL);
#endif
    /* Clear Suspend Error status */

    BitChange = DMU_HF_SUSPEND.U | SUSPEND_CLR_OFF;
    DMU_HF_SUSPEND.U=BitChange;
    /* [cover parentID={5692C14A-E8CC-4aa0-873B-F5ADCE5F77BB}]
    Set the Return Value as TRUE
    [/cover] */
    RetVal = (boolean)TRUE;
  }
  else if (TimeOutCount == 0U) /*Timeout */
  {
#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
    Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID, FLS_17_DMU_INSTANCE_ID,
                           FLS_17_DMU_SID_SUSPENDERASE,
                           FLS_17_DMU_E_HW_TIMEOUT);
#endif
    RetVal = (boolean)TRUE;
  }
  else
  {
    RetVal = (boolean)FALSE;
  }
  return (RetVal);
}
#endif

/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax: LOCAL_INLINE boolean Fls_lPverChk(void)                            **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : boolean                                                  **
**                                                                            **
** Description : This routine checks if PVER error occured                    **
*******************************************************************************/
LOCAL_INLINE boolean Fls_lPverChk(void)
{
  uint32 TempFSR;
  boolean RetVal;

  TempFSR = (uint32)DMU_HF_ERRSR.U;

  if ((((TempFSR >> IFX_DMU_HF_ERRSR_PVER_OFF)) &
       IFX_DMU_HF_ERRSR_PVER_MSK) == 1U)
  {
    RetVal = (boolean)TRUE;
  }
  else
  {
    RetVal = (boolean)FALSE;
  }
  return (RetVal);
}

#if(FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
                                         (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax: LOCAL_INLINE uint8 Fls_lBusyDET_Read                               **
**                                ( const Fls_17_Dmu_StateType* StatePtr)     **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : StatePtr : FLS Global variable structure                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : ErrorFlag - DET has occured (1) or not (0)               **
**                                                                            **
** Description : This routine detects if the new Read job can be accepted     **
*******************************************************************************/
LOCAL_INLINE uint8 Fls_lBusyDET_Read(const
                                     Fls_17_Dmu_StateType *const StatePtr )
{
  uint8 ErrorFlag;

  uint8 JobType;
  JobType = StatePtr->FlsJobType;
  ErrorFlag = 0U;

  /* No other job has been accepted */

  if(JobType != FLS_17_DMU_NONE)
  {
    /* [cover parentID={1F90F1CB-746A-40cf-8D42-4A3384B08521}][/cover] */
    Fls_lReportError(
      FLS_17_DMU_SID_READ,
      FLS_17_DMU_E_BUSY);/* Report to DET */
    ErrorFlag = 1U;
  }

  return(ErrorFlag);
}

#if (FLS_17_DMU_COMPARE_API == STD_ON)
/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax: LOCAL_INLINE uint8 Fls_lBusyDET_Compare                            **
**                                   ( const Fls_17_Dmu_StateType* StatePtr)  **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : StatePtr : FLS Global variable structure                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : ErrorFlag - DET has occured (1) or not (0)               **
**                                                                            **
** Description : This routine detects if the new Compare job can be accepted  **
*******************************************************************************/
LOCAL_INLINE uint8 Fls_lBusyDET_Compare(
  const Fls_17_Dmu_StateType *const StatePtr )
{
  uint8 ErrorFlag;
  uint8 JobType;
  JobType = StatePtr->FlsJobType;
  ErrorFlag = 0U;

  /* No other job has been accepted */

  if(JobType != FLS_17_DMU_NONE)
  { /* [cover parentID={1F90F1CB-746A-40cf-8D42-4A3384B08521}][/cover] */
    Fls_lReportError(
      FLS_17_DMU_SID_COMPARE,
      FLS_17_DMU_E_BUSY);/* Report to DET */
    ErrorFlag = 1U;
  }

  return(ErrorFlag);
}
#endif

/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax: LOCAL_INLINE uint8 Fls_lBusyDET_Write                              **
**                                 ( const Fls_17_Dmu_StateType* StatePtr )   **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : StatePtr : FLS Global variable structure                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : ErrorFlag - DET has occured (1) or not (0)               **
**                                                                            **
** Description : This routine detects if the new Write job can be accepted    **
*******************************************************************************/
LOCAL_INLINE uint8 Fls_lBusyDET_Write(const Fls_17_Dmu_StateType *const
                                      StatePtr)
{
  uint8 ErrorFlag;
  uint8 JobType;
  JobType = StatePtr->FlsJobType;
  ErrorFlag = 0U;

  /* No other job has been accepted */

  if(JobType != FLS_17_DMU_NONE)
  {
    /* [cover parentID={40E62EA1-BCDF-4f8b-88AB-375EB517E9E8}]
    Report DET error
    [/cover] */
    /* [cover parentID={1F90F1CB-746A-40cf-8D42-4A3384B08521}][/cover] */
    Fls_lReportError(
      FLS_17_DMU_SID_WRITE,
      FLS_17_DMU_E_BUSY);/* Report to DET */
    ErrorFlag = 1U;
  }

  return(ErrorFlag);
}

/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax: LOCAL_INLINE uint8 Fls_lBusyDET_Erase                              **
**                                 ( const Fls_17_Dmu_StateType* StatePtr)    **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : StatePtr : FLS Global variable structure                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : ErrorFlag - DET has occured (1) or not (0)               **
**                                                                            **
** Description : This routine detects if the new Erase job can be accepted    **
*******************************************************************************/
LOCAL_INLINE uint8 Fls_lBusyDET_Erase(const Fls_17_Dmu_StateType *const
                                      StatePtr)
{
  uint8 ErrorFlag;

  uint8 JobType;
  JobType = StatePtr->FlsJobType;
  ErrorFlag = 0U;

  /* No other job has been accepted */

  if(JobType != FLS_17_DMU_NONE)
  { /* [cover parentID={1F90F1CB-746A-40cf-8D42-4A3384B08521}][/cover] */
    Fls_lReportError(
      FLS_17_DMU_SID_ERASE,
      FLS_17_DMU_E_BUSY);/* Report to DET */
    ErrorFlag = 1U;
  }

  return(ErrorFlag);
}

/*******************************************************************************
** Traceability :      cover parentID={744CAAD3-0ED4-46d3-AABB-8426E922A937}] **
**                                                                            **
** Syntax: static uint8 Fls_lUninitDET( const uint8 ServiceID )               **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : ServiceID - Service ID of the calling function           **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : ErrorFlag - DET has occured (1) or not (0)               **
**                                                                            **
** Description : This routine performs the UNINIT DET check                   **
*******************************************************************************/
static uint8 Fls_lUninitDET( const uint8 ServiceID )
{
  uint8 ErrorFlag;

  ErrorFlag = 0U;
  if((Fls_ConfigPtr == NULL_PTR) || (FLS_INITIALIZED != Fls_17_Dmu_InitStatus))
  {
    /* [cover parentID={D51C59CB-848B-4a86-8B80-96BD865C8AB4}][/cover] */
    /* Report to DET */
    Fls_lReportError(ServiceID,
                     FLS_17_DMU_E_UNINIT);/* Report to DET */

    ErrorFlag = 1U;
  }

  return (ErrorFlag);
}

/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax: static uint8 Fls_lTimeOutDET( const uint8 ServiceID )              **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : ServiceID - Service ID of the calling function           **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : ErrorFlag - DET has occured (1) or not (0)               **
**                                                                            **
** Description : This routine performs the TIMEOUT DET check                  **
*******************************************************************************/
static uint8 Fls_lTimeOutDET(const uint8 ServiceID)
{
  Fls_17_Dmu_StateType  *StatePtr;
  uint8 ErrorFlag;

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;

  ErrorFlag = 0U;

  if (StatePtr->FlsTimeoutControl != 0U)
  {
    if(StatePtr->JobStarted.Erase != 0U)
    {
      if(StatePtr->FlsEraseTimeoutCycleCount == 0U)
        /* [cover parentID={B2E54AE9-1CA6-46d6-BCC0-AF1CC0E21C56}]
        Is FlsEraseTimeoutCycleCount 0?
        [/cover] */
      {
        ErrorFlag = 1U;
      }
      else
      {
        StatePtr->FlsEraseTimeoutCycleCount--;
      }
    }

    if(StatePtr->JobStarted.Write != 0U)
    {
      if(StatePtr->FlsWriteTimeoutCycleCount == 0U)
        /* [cover parentID={77FC62E9-7412-4f4f-87C6-5B9C2E2D7990}]
        Is FlsWriteTimeoutCycleCount 0?
        [/cover] */
      {
        ErrorFlag = 1U;
      }
      else
      {
        StatePtr->FlsWriteTimeoutCycleCount--;
      }
    }

    if(ErrorFlag == 1U)
    {
      /* Report timeout DEM */
      /* [cover parentID={75771AE4-657F-43bf-BBA3-A601D7D6E46E}]
      Report DET error
      [/cover] */
      /* [cover parentID={6854D0FE-A54C-4536-BC48-683D28ED8194}][/cover] */
      Fls_lReportError(ServiceID,
                       FLS_17_DMU_E_TIMEOUT);/* Report to DET */
    }
  }

  return ErrorFlag;
}

#if (FLS_17_DMU_IFX_FEE_USED == STD_OFF)
/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax: LOCAL_INLINE boolean Fls_lCheckWrittenPage(uint32 PageLength)      **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : PageLength                                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : TRUE - programing error , FALSE - No programming error   **
**                                                                            **
** Description : Checks if the page was written without errors                **
*******************************************************************************/
LOCAL_INLINE boolean Fls_lCheckWrittenPage(uint32 PageLength)
{
  const Fls_17_Dmu_StateType   *StatePtr;
  const uint32          *PageStartAddressPtr;
  const uint32    *SourcePtr;
  uint32          Count;
  uint32 BitChange;
  boolean         Error;

  Count = 0U;
  Error = (boolean)FALSE;

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
   the object types as the address of the register is being passed.*/
  SourcePtr = (const uint32 *)(StatePtr->FlsWriteBufferPtr);
  /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
         type is required to access the FLASH address/target address which
         is defined as unsigned long. */
  /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
      is required to store the FLASH address/target address in state var
      structure to perform easy arithmetic operations. */
  PageStartAddressPtr = (uint32 *)(StatePtr->FlsWriteAddress);

  /*Clear the ECC status bits by writing DMU_HF_ECCC.CLR with 11b to clear
                   AERM bit*/
  BitChange= DMU_HF_ECCC.U | FLS_DMU_ECCC_CLR;

  /*MISRA2012_RULE_11_3_JUSTIFICATION: Pointer cast is required to match
   the object types as the address of the register is being passed.*/
  FLS_17_DMU_LIB_RUNTIME_WRITECPUENDINITPROTREG(\
      (volatile uint32 *)&DMU_HF_ECCC.U, \
      BitChange);

  /*Clearing of AERM bit takes 2-3 cycles so added NOP*/
  NOP();
  NOP();
  NOP();

  do
  {
    /* [cover parentID={085F67D7-90CC-413a-A76B-9CC31408B9F6}]
    Is the page start address equal to source address?
    [/cover] */
    if(*(PageStartAddressPtr)== *(SourcePtr))
    {
      Count++;

      PageStartAddressPtr++;

      SourcePtr++;
    }
    else
    {
      /*  If the block has been not completely reprogrammed  */
      /*         after Writing a Flash block.                       */
#if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
                                    (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
      /* [cover parentID={D7CBA05B-D2E8-4067-AA3A-F77486EC2CF7}]
      Report DET error
      [/cover] */
      /* [cover parentID={DB1B6F9A-42AF-4dc9-A71F-84ABAF7F3F96}][/cover] */
      Fls_lReportError(FLS_17_DMU_SID_MAIN,
                       FLS_17_DMU_E_VERIFY_WRITE_FAILED);/* Report to DET */
#endif
      /* Call to Fls_lErrorHandler local function */
      Error = (boolean)TRUE;
      /*Nothing more to compare */
      Count = (PageLength/FLS_WORD_SIZE);
    }
  } while(Count < (PageLength/FLS_WORD_SIZE));

  if(Error == (boolean)FALSE)
  {
    /* Check for Non-correctable ECC errors during the above check */
    if(Fls_lChkBitErrors() != 0U)
    {
      /* Report to DET */
#if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
                                          (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
      /* [cover parentID={DB1B6F9A-42AF-4dc9-A71F-84ABAF7F3F96}][/cover] */
      Fls_lReportError(FLS_17_DMU_SID_MAIN,
                       FLS_17_DMU_E_VERIFY_WRITE_FAILED);
#endif
      Error = (boolean)TRUE;
    }
  }
  return Error;
}
#endif

/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax: LOCAL_INLINE void Fls_lCalculateWriteTimeoutCount(void)            **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description : Calculates the write timeout count                           **
*******************************************************************************/
LOCAL_INLINE void Fls_lCalculateWriteTimeoutCount(void)
{
  Fls_17_Dmu_StateType   *StatePtr;
  uint32          Length;
  volatile uint32          WriteTimeOutCount;
  uint32          PageStartAddress;

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;

  PageStartAddress = StatePtr->FlsWriteAddress;
  Length = StatePtr->FlsWriteLength;
  /* Update Timeout count for write */
  WriteTimeOutCount =
    (uint32)(FLS_17_DMU_WRITE_TIME / Fls_ConfigPtr->FlsCallCycle);
  if(WriteTimeOutCount == 0U)
  {
    WriteTimeOutCount = 1U;
  }
  else
  {
    if((FLS_17_DMU_WRITE_TIME % Fls_ConfigPtr->FlsCallCycle) != 0U)
    {
      WriteTimeOutCount++;
    }
  }

  StatePtr->FlsWriteTimeoutCycleCount = WriteTimeOutCount;

  while(Length > FLS_17_DMU_PAGE_SIZE)
  {
    if( (Length <= (FLS_17_DMU_BURST_PAGE_SIZE - FLS_17_DMU_PAGE_SIZE)) ||
        ((PageStartAddress & (FLS_17_DMU_BURST_PAGE_SIZE - 1U)) != 0U) )
    {
      Length -= FLS_17_DMU_PAGE_SIZE;
      PageStartAddress += FLS_17_DMU_PAGE_SIZE;
    }
    else
    {
      Length -= FLS_17_DMU_BURST_PAGE_SIZE;
      PageStartAddress += FLS_17_DMU_BURST_PAGE_SIZE;
    }
    StatePtr->FlsWriteTimeoutCycleCount += WriteTimeOutCount;
  }

  /* Add one extra count since MainFunction needs to be called once after
     all the data is written for checking errors and to set status */
  /* MISRA2012_RULE_18_4_JUSTIFICATION: The variable is a normal structure
   variable accessed through structure pointer. There is no array involved
   */
  StatePtr->FlsWriteTimeoutCycleCount += 1U;
}

#if (FLS_17_DMU_IFX_FEE_USED == STD_OFF)
/*******************************************************************************
** Traceability :  [cover parentID={02694C60-A685-40e9-A517-AEACCDE8F330}]    **
**                                                                            **
** Syntax: LOCAL_INLINE Std_ReturnType Fls_lPageEraseCheck(                   **
**                                            uint32* const AddrCheckPtr,     **
**                                                  uint32  Length,           **
**                                            const uint8   ServiceID)        **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : AddrCheckPtr - address of the page, Length - page length **
**                   ServiceID - Service ID of the API for the DET            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK - page was erased correctly                         **
**                   E_NOT_OK - Page was not erased correctly                 **
**                                                                            **
** Description : Checks if the page was erased correctly                      **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fls_lPageEraseCheck(uint32 *const AddrCheckPtr,
    const uint32 Length,
    const uint8 ServiceID)
{
  Std_ReturnType  RetVal;
  uint8           Loop;
  uint8           PageLength;
  uint8       IndexAddrCheckPtr;

  RetVal = E_OK;

  Loop = 0U;

  IndexAddrCheckPtr = 0U;

  if( (Length <= (FLS_17_DMU_BURST_PAGE_SIZE - FLS_17_DMU_PAGE_SIZE)) ||
      /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
        is required to check the value of the address of data buffer alignment. */
      /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
       type is required to access the FLASH address/target address which
      is defined as unsigned long. */
      ((((uint32)AddrCheckPtr) & (FLS_17_DMU_BURST_PAGE_SIZE - 1U)) != 0U) )
  {
    PageLength = FLS_17_DMU_PAGE_SIZE;
  }
  else
  {
    PageLength = FLS_17_DMU_BURST_PAGE_SIZE;
  }

  do
  {

    /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
      array indexing used for FLASH address calculation and for subsequent
            traversal.The access range is within the flash address range.*/
    if((*(AddrCheckPtr + IndexAddrCheckPtr)) == 0U)
    {
      Loop++;
      IndexAddrCheckPtr++;
    }
    else
    {
      /*  Before Writing if block is not completely erased.*/
      /* Call to Fls_lErrorHandler local function */
      /* [cover parentID={1CC73CD8-3252-43cc-A334-114676D7D473}][/cover] */
#if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
                                         (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
      Fls_lReportError(ServiceID,
                       FLS_17_DMU_E_VERIFY_ERASE_FAILED);/* Report to DET */
#endif

      RetVal = E_NOT_OK; /* Return from FSunction */
    }
  } while((RetVal == E_OK) && (Loop < (PageLength/FLS_WORD_SIZE)));

  return RetVal;
}
#endif

/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax : LOCAL_INLINE Std_ReturnType Fls_lCheckEraseDet(                   **
**                                         Fls_AddressType TargetAddress,     **
**                                         Fls_LengthType Length)             **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  TargetAddress and Length                                **
**                                                                            **
** Parameters (out): E_OK: No development Error detected                      **
**                   E_NOT_OK: development Error is detected                  **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                                                                            **
** Description : This routine checks for development error for                **
**               Fls_17_Dmu_Erase API                                         **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fls_lCheckEraseDet(
  const Fls_17_Dmu_AddressType TargetAddress,
  const Fls_17_Dmu_LengthType Length)
{
  const Fls_17_Dmu_StateType*   StatePtr;
  Std_ReturnType   ReturnValue;

  /* API called before initialization? */
  /* [cover parentID={703059FE-8BEE-4dfc-BA84-ED7289C1E42B}]
  Is Uninit DET error detected?
  [/cover] */
  if(Fls_lUninitDET(FLS_17_DMU_SID_ERASE) == 1U)
  {
    ReturnValue = E_NOT_OK;
  }

  /* Checking whether given TargetAddress is valid or not */
  /* [cover parentID={2139AFD5-1DC3-4858-96ED-AAFC1324617E}]
  Is the given TargetAddress valid?
  [/cover] */
  /*[cover parentID={2B120B27-3973-4088-A840-8637F0D4AB2C}][/cover]*/

  /* [cover parentID={2139AFD5-1DC3-4858-96ED-AAFC1324617E}]
  Is the given TargetAddress valid?
  [/cover] */
  else if(((uint32)TargetAddress >= FLS_17_DMU_TOTAL_SIZE) ||
          ((TargetAddress & FLS_MOD4K_MASK )!=0U))
  {
    /* Report to DET */
    /* [cover parentID={685D8E78-D6D4-4c14-915B-9DA926422AF0}]
    Report DET error
    [/cover] */
    /* [cover parentID={A5CB3F8B-F837-492f-90DD-B32C11CD1477}][/cover] */

    /* [cover parentID={9F2FECA4-FAE5-4480-829F-77E92FDC809A}][/cover] */
    Fls_lReportError(FLS_17_DMU_SID_ERASE,FLS_17_DMU_E_PARAM_ADDRESS);
    /* [cover parentID={A2F1E30A-8BF6-45ee-BE40-E3121C8BCFDE}]
    Set the Return Value as NOT OK
    [/cover] */

    ReturnValue = E_NOT_OK;
  }

  /* Checking whether given Length is valid or not */
  /* [cover parentID={F2A57A9F-57D6-434e-A014-BFBD76775BEA}]
  Is the given Length valid?
  [/cover] */
  /*[cover parentID={2B120B27-3973-4088-A840-8637F0D4AB2C}][/cover]*/
  else if((!(( Length >= FLS_ONE_VALUE) &&
             ( Length <= (FLS_17_DMU_TOTAL_SIZE - TargetAddress )))) ||
          ((Length & FLS_MOD4K_MASK) != 0U))
  {
    /* Report to DET */
    /* [cover parentID={685D8E78-D6D4-4c14-915B-9DA926422AF0}]
    Report DET error
    [/cover] */
    /* [cover parentID={39483FE9-5476-47fe-9734-A56F8E6DAC0D}][/cover] */
    Fls_lReportError(FLS_17_DMU_SID_ERASE, FLS_17_DMU_E_PARAM_LENGTH);
    /* [cover parentID={A2F1E30A-8BF6-45ee-BE40-E3121C8BCFDE}]
    Set the Return Value as NOT OK
    [/cover] */
    ReturnValue = E_NOT_OK;
  }
  else
  {
    StatePtr = Fls_ConfigPtr->FlsStateVarPtr;

    if(Fls_lBusyDET_Erase((const Fls_17_Dmu_StateType *)StatePtr) == 1U)
    {
      /* [cover parentID={A2F1E30A-8BF6-45ee-BE40-E3121C8BCFDE}]
      Set the Return Value as NOT OK
      [/cover] */
      ReturnValue = E_NOT_OK;
    }
    else
    {
      ReturnValue = E_OK;
    }
  }
  /* [cover parentID={A93B90B0-2AEA-497e-A630-5DBACCB89CEF}]
  Return
  [/cover] */
  return ReturnValue;
}

/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax : LOCAL_INLINE Std_ReturnType Fls_lCheckWriteDet(                   **
**                                         Fls_AddressType TargetAddress,     **
**                                         const uint8 *SourceAddressPtr,     **
**                                         Fls_LengthType Length)             **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  TargetAddress, SourceAddressPtr and Length              **
**                                                                            **
** Parameters (out): E_OK: No development Error detected                      **
**                   E_NOT_OK: development Error is detected                  **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                                                                            **
** Description : This routine checks for development error for                **
**               Fls_17_Dmu_Write API                                         **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fls_lCheckWriteDet(
  const Fls_17_Dmu_AddressType TargetAddress,
  uint8 *const SourceAddressPtr,
  const Fls_17_Dmu_LengthType Length)

{
  Std_ReturnType  RetVal;

  RetVal = E_OK;

  /* API called before initialization */

  /* [cover parentID={BBF8A325-DA84-4202-929C-F48493B64529}]
  Is Uninit DET error detected?
  [/cover] */
  if(Fls_lUninitDET(FLS_17_DMU_SID_WRITE) == 1U)
  {
    RetVal = E_NOT_OK;
  }
  /* Checking whether given TargetAddress is valid or not */
  /* [cover parentID={10B65A6A-5954-48de-AE99-5341E74DCAD3}]
  Is the given TargetAddress valid?
  [/cover] */
  /*[cover parentID={2B120B27-3973-4088-A840-8637F0D4AB2C}][/cover]*/

  /* [cover parentID={10B65A6A-5954-48de-AE99-5341E74DCAD3}]
  Is the given TargetAddress valid?
  [/cover] */
  else if((((uint32)TargetAddress >= FLS_17_DMU_TOTAL_SIZE)) ||
          ((TargetAddress & FLS_PAGE_SIZE_MASK) != 0U) )
  {
    /* [cover parentID={6D67E4AE-5472-4009-AD54-6F7274A50002}]
    Report DET error
    [/cover] */
    /* [cover parentID={9F2FECA4-FAE5-4480-829F-77E92FDC809A}][/cover] */
    /* Report to DET */
    Fls_lReportError(FLS_17_DMU_SID_WRITE, FLS_17_DMU_E_PARAM_ADDRESS);

    RetVal = E_NOT_OK;
  }
  /* Checking whether given Length is valid or not */
  /* [cover parentID={66607E1C-BF66-4580-8164-0B6F3E37B92F}]
  Is the given Length valid?
  [/cover] */

  else if((!(((uint32)Length >= FLS_ONE_VALUE)&&
             ((uint32)Length <= (FLS_17_DMU_TOTAL_SIZE - TargetAddress)))) ||
          ((Length & FLS_PAGE_SIZE_MASK) != 0U))
  {
    /* [cover parentID={6D67E4AE-5472-4009-AD54-6F7274A50002}]
    Report DET error
    [/cover] */
    /* [cover parentID={39483FE9-5476-47fe-9734-A56F8E6DAC0D}][/cover] */
    /* Report to DET */
    Fls_lReportError(FLS_17_DMU_SID_WRITE,FLS_17_DMU_E_PARAM_LENGTH);

    RetVal = E_NOT_OK;
  }
  /* Check for Pointer to an application buffer */
  /* [cover parentID={EBB93C07-D227-4d1e-A803-487926749C49}]
  Is there a pointer to the application buffer?
  [/cover] */
  /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
  is required to check the value of the address of data buffer alignment.
  */
  /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and integer
         type is required to access the FLASH address/target address which
         is defined as unsigned long. */
  /* MISRA2012_RULE_10_4_JUSTIFICATION: cast from pointer to unsigned long
    is required to check the value of the address of data buffer alignment.
   The implicit conversion will only compare the value*/
  else if((SourceAddressPtr == NULL_PTR) || \
          (((uint32)SourceAddressPtr & FLS_WORD_SIZE_MASK) != 0))
  {
    /* [cover parentID={6D67E4AE-5472-4009-AD54-6F7274A50002}]
    Report DET error
    [/cover] */
    /* [cover parentID={4A144583-41B1-4f65-A9D5-795C172A5387}][/cover] */
    /* Report to DET */
    Fls_lReportError(FLS_17_DMU_SID_WRITE, FLS_17_DMU_E_PARAM_DATA);

    RetVal = E_NOT_OK;
  }
  else
  {
    /* dummy else */
  }

  /* [cover parentID={9B7A1A6F-658D-445b-B2E0-0E20E88BFFF9}]
  Return
  [/cover] */
  return RetVal;

}

#endif
/* FLS_17_DMU_DEV_ERROR_DETECT == STD_ON */

/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax:LOCAL_INLINE uint8 Fls_lGetWriteMode(void);                         **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : FLS_17_DMU_PAGE_WRITE - Page write to be done            **
**                   FLS_17_DMU_BURST_WRITE - Burst write to be done          **
**                                                                            **
** Description : This function checks whether Burst Write can be performed or **
**               Page Write has to be performed                               **
*******************************************************************************/
LOCAL_INLINE uint8 Fls_lGetWriteMode(void)
{
  const Fls_17_Dmu_StateType   *StatePtr;
  uint8           RetVal;

  RetVal = FLS_17_DMU_BURST_WRITE;
  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;

  if((StatePtr->FlsWriteLength <=
      (FLS_17_DMU_BURST_PAGE_SIZE - FLS_17_DMU_PAGE_SIZE))
 || ((StatePtr->FlsWriteAddress & (FLS_17_DMU_BURST_PAGE_SIZE - 1U)) != 0U))
  {
    RetVal = FLS_17_DMU_PAGE_WRITE;
  }

  return RetVal;
}

/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax:LOCAL_INLINE Fls_LengthType Fls_lGetReadModeLength(void);           **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : max read length as per read mode                         **
**                                                                            **
** Description : Get max read length according to the FLS mode                **
*******************************************************************************/
LOCAL_INLINE Fls_17_Dmu_LengthType Fls_lGetReadModeLength(void)
{
  const Fls_17_Dmu_StateType   *StatePtr;
  Fls_17_Dmu_LengthType  MaxRead;

  StatePtr = Fls_ConfigPtr->FlsStateVarPtr;
  MaxRead = Fls_ConfigPtr->FlsFastRead;

  if(StatePtr->FlsMode == MEMIF_MODE_SLOW)
  {
    MaxRead = Fls_ConfigPtr->FlsSlowRead;
  }

  return MaxRead;
}

/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax: LOCAL_INLINE uint32 Fls_lChkSeqProtErrors(void)                    **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Seq and protection bits of FSR                           **
**                                                                            **
** Description : Checks for seq and protection errors                         **
*******************************************************************************/
LOCAL_INLINE uint32 Fls_lChkSeqProtErrors(void)
{
  uint32 RetVal;

  RetVal = ((uint32)DMU_HF_ERRSR.U & FLS_PROER_SQER_ERROR);

  return RetVal;
}

/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax: LOCAL_INLINE uint32 Fls_lChkOperError(void)                        **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : operational error bit of FSR                             **
**                                                                            **
** Description : Checks for operational error                                 **
*******************************************************************************/
LOCAL_INLINE uint32 Fls_lChkOperError(void)
{
  uint32 RetVal;

  /* [cover parentID={76160973-4671-4f08-983C-A0DA155B3A88}]
  Check for operational error ?
  [/cover] */
  RetVal = ((uint32)DMU_HF_ERRSR.U & FLS_OPER_ERROR);

  if(RetVal != 0U)
  {
    RetVal = FLS_OPER_ERROR;
    if(Fls_ConfigPtr->FlsIllegalStateNotificationPtr != NULL_PTR)
    {
      /* FlsIllegalStateNotificationPtr should be called */
      (Fls_ConfigPtr->FlsIllegalStateNotificationPtr)();
    }
  }

  return (RetVal);
}

/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax: LOCAL_INLINE uint32 Fls_lChkBitErrors(void)                        **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Non correctable bit of FSR                               **
**                                                                            **
** Description : Checks for double ECC errors                                 **
*******************************************************************************/
LOCAL_INLINE uint32 Fls_lChkBitErrors(void)
{
  uint32 RetVal;

  /* [cover parentID={B6C1503A-B86D-450f-908C-EADA555D721D}]
  Return the ECC bit error status.
  [/cover] */
  RetVal = ((uint32)DMU_HF_ECCS.U & FLS_BIT_ERROR);

  return RetVal;
}

/*******************************************************************************
**Traceability :                                                              **
**                                                                            **
** Syntax: LOCAL_INLINE uint32 Fls_lHWBusyCheck(void)                         **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Busy bit of FSR                                          **
**                                                                            **
** Description : Checks for Busy status of the Data Flash Bank                **
*******************************************************************************/
LOCAL_INLINE uint32 Fls_lHWBusyCheck(void)
{
  uint32 RetVal;

  RetVal = ((uint32)DMU_HF_STATUS.U & FLS_D0BUSY);

  return RetVal;
}

/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax: LOCAL_INLINE MemIf_ModeType Fls_lSetDefaultMode(void)              **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : MemIf_ModeType                                           **
**                                                                            **
** Description : Returns the default mode of FLS driver                       **
*******************************************************************************/
LOCAL_INLINE MemIf_ModeType Fls_lSetDefaultMode(void)
{
  return (Fls_ConfigPtr->FlsDefaultMode);
}

#if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON)|| \
                                       (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={6D03B66B-576D-4850-ABCD-769EAFF88353}]   **
**                                                                            **
** Syntax          : LOCAL_INLINE void Fls_lReportError                       **
**                                (const uint8 Fls_Sid, const uint8 ErrorId)  **
**                                                                            **
** Description     : Function to report Safety Error and DET                  **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Fls_Sid - Service id of the caller API                   **
**                   ErrorId - ID of the error to be reported                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
*                                                                             **
*******************************************************************************/
static void Fls_lReportError(const uint8 Fls_Sid, const uint8 ErrorId)
{

#if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON)
  Det_ReportError(FLS_17_DMU_MODULE_ID,FLS_17_DMU_INSTANCE_ID,Fls_Sid, ErrorId);
#endif

#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  Mcal_ReportSafetyError(FLS_17_DMU_MODULE_ID,FLS_17_DMU_INSTANCE_ID,Fls_Sid,
                         ErrorId);
#endif
}
#endif/*End of Fls_lReportError*/


#define FLS_17_DMU_STOP_SEC_CODE_ASIL_B_LOCAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Fls_17_Dmu_MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
