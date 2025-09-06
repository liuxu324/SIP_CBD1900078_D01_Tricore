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
**  FILENAME     : Fee.c                                                     **
**                                                                           **
**  VERSION      : 13.0.0                                                    **
**                                                                           **
**  DATE         : 2018-09-29                                                **
**                                                                           **
**  VARIANT      : Variant PB                                                **
**                                                                           **
**  PLATFORM     : Infineon AURIX2G                                          **
**                                                                           **
**  AUTHOR       : DL-AUTOSAR-Engineering                                    **
**                                                                           **
**  VENDOR       : Infineon Technologies                                     **
**                                                                           **
**  DESCRIPTION  : Fee Driver source file                                    **
**                                                                           **
**  SPECIFICATION(S) : Specification of Fee Driver, AUTOSAR Release 4.2.2    **
**                                                                           **
**  MAY BE CHANGED BY USER : no                                              **
**                                                                           **
******************************************************************************/
/* [cover parentID={540C6CF8-E5A3-47b2-9A71-B1EFD849D042}] Fee.c
[/cover] */
/* [cover parentID={21DDC179-B28F-4c4d-9045-F9A7AAB29407}]
Platform independent module
[/cover] */
/* [cover parentID={056FA7C0-7DE5-427e-8FD1-01B6F7EFEAB2}]*/
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]*/
/******************************************************************************
**                      Includes                                             **
******************************************************************************/

/* Inclusion of Flash header file */
#include "Fee.h"

/* Inclusion of FEE Callback functionality */
#include "Fee_Cbk.h"

#if (FEE_DEM_ENABLED == STD_ON)
/* Inclusion of Dem.h  */
#include "Dem.h"
#endif

/* Conditional Inclusion of Developement Error Tracer File */
#if  (FEE_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#if (FEE_SAFETY_ENABLE == STD_ON)
#include "Mcal_SafetyError.h"
#endif

/*AUTOSAR File*/
#include "SchM_Fee.h"
/******************************************************************************
**                      Imported Compiler Switch Check                       **
******************************************************************************/

/*
    AUTOSAR VERSION CHECK FOR FEE MODULE INCLUSION
*/

#ifndef FEE_AR_RELEASE_MAJOR_VERSION
#error "FEE_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#ifndef FEE_AR_RELEASE_MINOR_VERSION
#error "FEE_AR_RELEASE_MINOR_VERSION is not defined. "
#endif

#ifndef FEE_AR_RELEASE_REVISION_VERSION
#error "FEE_AR_RELEASE_REVISION_VERSION is not defined. "
#endif

#if ( FEE_AR_RELEASE_MAJOR_VERSION != 4U )
#error "FEE_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#if ( FEE_AR_RELEASE_MINOR_VERSION != 2U )
#error "FEE_AR_RELEASE_MINOR_VERSION does not match. "
#endif

/*
    DRIVER VERSION CHECK FOR FEE MODULE INCLUSION
*/

#ifndef FEE_SW_MAJOR_VERSION
#error "FEE_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef FEE_SW_MINOR_VERSION
#error "FEE_SW_MINOR_VERSION is not defined. "
#endif

#ifndef FEE_SW_PATCH_VERSION
#error "FEE_SW_PATCH_VERSION is not defined. "
#endif

#if ( FEE_SW_MAJOR_VERSION != 3U )
#error "FEE_SW_MAJOR_VERSION does not match. "
#endif

#if ( FEE_SW_MINOR_VERSION != 0U )
#error "FEE_SW_MINOR_VERSION does not match. "
#endif

/*
    VERSION CHECK FOR DET MODULE INCLUSION
*/

#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)

#ifndef DET_AR_RELEASE_MAJOR_VERSION
#error "DET_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif



#if ( DET_AR_RELEASE_MAJOR_VERSION != 4U )
#error "DET_AR_RELEASE_MAJOR_VERSION does not match. "
#endif



#endif /* (FEE_DEV_ERROR_DETECT == STD_ON) */

/*
    VERSION CHECK FOR DEM MODULE INCLUSION
*/

#if (FEE_DEM_ENABLED == STD_ON)

#ifndef DEM_AR_RELEASE_MAJOR_VERSION
#error "DEM_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#if ( DEM_AR_RELEASE_MAJOR_VERSION != 4U )
#error "DEM_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#endif /* (FEE_DEM_ENABLED == STD_ON) */

/*
    VERSION CHECK FOR FLS MODULE INCLUSION
*/

#ifndef FLS_17_DMU_AR_RELEASE_MAJOR_VERSION
#error "FLS_17_DMU_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#ifndef FLS_17_DMU_AR_RELEASE_MINOR_VERSION
#error "FLS_17_DMU_AR_RELEASE_MINOR_VERSION is not defined. "
#endif

#if ( FLS_17_DMU_AR_RELEASE_MAJOR_VERSION != 4U )
#error "FLS_17_DMU_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#if ( FLS_17_DMU_AR_RELEASE_MINOR_VERSION != 2U )
#error "FLS_17_DMU_AR_RELEASE_MINOR_VERSION does not match. "
#endif

/******************************************************************************
**                      Private Macro Definitions                            **
******************************************************************************/

/*---------- Garbage Collection related constant------------------------*/

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

/* 1. User operation allowed states */
#define FEE_GC_REQUESTED                            (0x5U)
/*Read states of GC */
#define FEE_GC_UNCFG_START_COPY                     (0x10U)
#define FEE_GC_START_COPY                           (0x1U)

/* Erase states of GC */
#define FEE_GC_ERASE_PREV_SECTOR                    (0x3U)
#define FEE_GC_INIT_ERASE_PREV_SECTOR               (0x4U)

/* 2. User operation NOT allowed states */
/*Read states of GC */
#define FEE_GC_UNCFG_COPY_READ_NXTPAGE              (0x0U)
#define FEE_GC_COPY_READ_NXTPAGE                    (0x2U)

/* Write states of GC */
/* SECTOR0 -> Current/Prev Sector; SECTOR1 -> Next Sector */
/* V -> Valid; E -> Erased */
/* SP -> State Page; M -> Marker */

#define FEE_GC_UNCFG_COPY_WRITE          (0x6U)
#define FEE_GC_COPY_WRITE                (0x7U)
#define FEE_GC_MARK_SECTOR1_V_SP         (0x8U)
#define FEE_GC_MARK_SECTOR1_V_M          (0x9U)
#define FEE_GC_MARK_SECTOR0_E_SP         (0xAU)
#define FEE_GC_MARK_SECTOR0_E_M          (0xBU)
#define FEE_GC_INIT_MARK_SECTOR0_E_SP    (0xCU)
#define FEE_GC_INIT_MARK_SECTOR0_E_M     (0xDU)

#if (FEE_CANCELL_ALL_API == STD_ON) && \
    (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
/* Cancel GC related */
#define FEE_GC_NOT_CANCLD                   (0U)
#define FEE_GC_CANCLD                     (1U)
#define FEE_GC_CANCLD_CACHEUPDATE            (2U)

#endif

#endif

/* 3. Non operational states of GC */
#define FEE_GC_IDLE                                 (0xEU)

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

#define FEE_GC_FAIL                                 (0xFU)

#endif

/* Fee_Init States - Used for detecting the Garbage Collection Interruption */
#define FEE_INITGC_IDLE                      (0U)

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

#define FEE_INITGC_HANDLE_INVALID            (1U)
#define FEE_INITGC_HANDLE_DIRTY              (2U)
#define FEE_INITGC_NORMAL                    (3U)
#define FEE_INITGC_PREPARE_DFLASH            (4U)
#define FEE_INITGC_COMPLETE                  (5U)
#define FEE_INITGC_FAIL                      (6U)
/* States to monitor Garbage Collection completion, if it was interrupted */
/* earlier due to reset */
#define FEE_INITGC_NORMAL_S1                (0x1DU)
#define FEE_INITGC_NORMAL_S0                (0xD1U)
#define FEE_INITGC_DATA_COPY_S1_S0          (0x5DU)
#define FEE_INITGC_DATA_COPY_S0_S1          (0xD5U)
#define FEE_INITGC_ERASE_S1                 (0xDFU)
#define FEE_INITGC_ERASE_S0                 (0xFDU)

#endif

/*---------- Garbage Collection related constant End -------------------*/


/*---------- Erase suspend related constant ----------------------------*/


#if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
/* Erase-Suspend Status */
#define FEE_ERASE_NOT_SUSPENDED                     ((uint8)0)
#define FEE_ERASE_SUSPENDED                         ((uint8)1)
/* FeeEraseSuspendStatus > 1  : Resume-Erase failed */
/* FEE_RESUME_ERASE_LIMIT - 1 : No. of times Resume-Erase will be attempted */

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

#define FEE_RESUME_ERASE_LIMIT                      ((uint8)4)

#endif

#endif

/*---------- Erase suspend related constant End -------------------------*/

/*---------- Common constant start -------------------------*/
#define FEE_ZERO      (0U)

#define FEE_RESET     (0U)
#define FEE_SET       (1U)

#if(FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

#if (FEE_GET_CYCLE_COUNT_API == STD_ON)

#define FEE_STATE_PAGE_NUMBER (0U)

#endif

#define FEE_BLOCK_HDR_PAGE        (0U)
#define FEE_INVALID_BLOCK_LEN     (1U)
#define FEE_INVALID_BLOCK         (0U)
#define FEE_NEW_WL_BEGIN          (0U)
#define FEE_DATA_NEXT_PAGE_ID_POS (0U)
#define FEE_INVALID_BLOCK_PAGES   (2U)
#define FEE_BLOCK_NUM_MSB_POS     (2U)
#define FEE_BLOCK_NUM_LSB_POS     (1U)
#define FEE_BLOCK_MANGMNT_PAGES   (2U)
#define FEE_BLOCK_CYL_CNT_POS     (2U)
#define FEE_PAGE_TO_BYTE          (3U)
#define FEE_BYTE_TO_PAGE          (3U)
#define FEE_BLOCK_NUM_POS         (6U)
#endif

#define FEE_ONE       (1U)
#define FEE_TWO       (2U)
#define FEE_THREE     (3U)
#define FEE_FOUR      (4U)
#define FEE_FIVE      (5U)
#define FEE_SIX       (6U)
#define FEE_SEVEN     (7U)
#define FEE_EIGHT     (8U)
#define FEE_SIXTEEN   (16U)

/*---------- Common constant constant End -------------------------*/




/*---------- State page related constant End ---------------------------*/

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

#define FEE_STATE_FIRSTFIVE_COPY_OFFSET (40U)
#define FEE_STATE_ALLONES_OFFSET        (80U)
#define FEE_STATE_CRC_OFFSET            (116U)
#define FEE_STATE_WLCOUNT_MASK          (0xFFFFFF00U)
#define FEE_STATEPAGE_DATA_SIZE         (120U)
#define FEE_STATEPAGE_MARKER_SIZE       (8U)
#define FEE_STATEPAGE_SIZE              (128U)
#define FEE_STATEPAGE_PROGRAM_SIZE      (120U)
#define FEE_PROGRAM_STATEPAGE           (1U)
#define FEE_PROGRAM_MARKER              (2U)
/* State page Status */
#define FEE_SP_CLEAN                    (0U)
#define FEE_SP_DIRTY                    (1U)
#define FEE_SP_INVALID                  (2U)
#define FEE_VALID                       (0xD1U)
#define FEE_ERASED                      (0x1EU)
/* Page Identifier */
#define FEE_STATE_FIRST_PAGE_ID         (0x59U)
#define FEE_STATE_NEXT_PAGE_ID          (0xC6U)
#define FEE_STATE_PAGE_ID_POS           (0U)
#define FEE_STATE_PAGE_STATE_POS        (1U)
#define FEE_STATE_PAGE_UERWL_POS        (3U)
#define FEE_STATE_PAGE_STATE_CNT_POS    (4U)
#define FEE_STATE_PAGE_HDR_PAGES        (10U)

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)

#define FEE_STATE_PAGE_QS_OFFSET_LSB    (2U)
#define FEE_STATE_PAGE_QS_OFFSET_MSB    (3U)

/* Mask to extract the QS Data offset which is stored in State Page */
#define FEE_QS_DATA_OFFSET_MASK         (0x0FFF0000U)
/* Bit position indicating the start of the the QS Data offset which is stored 
  in State Page */
#define FEE_QS_DATA_OFFSET_START        (16U)

#endif

#define FEE_STATE_PAGE_UERWL1_ADDRS_POS (12U)
#define FEE_STATE_PAGE_UERWL2_ADDRS_POS (20U)

/* State Page field for verification */
#define FEE_SP_MARKERFIELD_START        (120U)
#define FEE_SP_MARKER_WORD_1            (0xAFAFF53AU)
#define FEE_SP_MARKER_WORD_2            (0xAFAFF5F5U)
#define FEE_CRC_START_VAL              (0U)

#endif

/* State page Repair stages */
#define FEE_REPAIR_IDLE                (0U)


/*---------- State page related constant End ---------------------------*/

/*---------- Data block related constant -------------------------------*/

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/* Sector page offsets */
#define FEE_PAGE1_DATA_OFFSET            (8U)
#define FEE_VALID_BIT                    (0x80U)
#define FEE_PAGE_COUNT_MASK              (0x7FFFU)
#define FEE_VALID_MASK                   (0x80U)
/* Page Identifier */
#define FEE_DATA_FIRST_PAGE_ID           (0xA3U)
#define FEE_DATA_NEXT_PAGE_ID            (0x9CU)
#define FEE_DATA_MARKER_PAGE_ID          (0x65U)
#define FEE_DP_MARKER_WORD               (0xF5F5AF65U)
#define FEE_DP_MARKER_BYTE_2             (0xAFU)
#define FEE_DP_MARKER_BYTE_3             (0xF5U)
#define FEE_DP_MARKER_BYTE_4             (0xF5U)
#define FEE_LWB_DIRTY                    (1U)
#define FEE_LWB_CHECK_FOR_DIRTY          (2U)

#endif

/* Last Written Block Dirty Status */
#define FEE_LWB_NOT_DIRTY        (0U)

/*---------- Data block related constant end ----------------------------*/



#define FEE_16_BIT_ALL_ONES           (0xFFFFU)
#define FEE_32_BIT_ALL_ONES           (0xFFFFFFFFU)

#define FEE_DFLASH_WORDLINE_SIZE_1    (FEE_DFLASH_WORDLINE_SIZE - 1U)

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

#define FEE_WRITE_LEN_MAX             (FEE_MAX_BYTES_PER_CYCLE)
#define FEE_COMPARE_LEN_MAX           (FEE_MAX_BYTES_PER_CYCLE)


/*---------- Word line related constant --------------------------------*/

/* Data bytes in a word-line = ((WordLine Size / 8) * 7) */
#define FEE_DATA_BYTES_IN_WORDLINE    (448U)

/* Word-Line Affected Type */
/* 2. Block sharing the last written WL boundary is (also) affected */
#define FEE_LWB_ACROSS_WL_AFFECTED                ((uint8)0x01U)
/* 3. Only the block(s) present in the last written WL is affected */
#define FEE_LWB_WITHIN_WL_AFFECTED                ((uint8)0x02U)
/* 4. Continue copying block pages in last written WL */
#define FEE_LWB_WITHIN_WL_AFFECTED_CONT           ((uint8)0x03U)
/* 5. Copy marker page in last written WL */
#define FEE_LWB_MARKER_COPY_PENDING               ((uint8)0x04U)

#endif

/* 1. WL not affected */
#define FEE_LWB_NOT_AFFECTED                      ((uint8)0x00U)

/*---------- Word line related constant End ----------------------------*/

/*---------- Data flash related constant -------------------------------*/

#define FEE_DFLASH_WORD_SIZE              (4U)
/* Fee Prepare DFlash States */
#define FEE_PREPDF_ERASE_S0               (0U)


#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/* Sector states */
#define FEE_STATELESS                     (0U)

#define FEE_PREPDF_ERASE_S1               (1U)
#define FEE_PREPDF_MARK_S0_ERASED_SP      (2U)
#define FEE_PREPDF_MARK_S0_ERASED_M       (3U)
#define FEE_PREPDF_MARK_S0_VALID_SP       (4U)
#define FEE_PREPDF_MARK_S0_VALID_M        (5U)
#define FEE_PREPDF_MARK_S1_ERASED_SP      (6U)
#define FEE_PREPDF_MARK_S1_ERASED_M       (7U)
/*Two sector enabled, represents the NVM sector size*/
#define FLS_SECTOR0_SIZE                  (FLS_17_DMU_NVMSECTOR_SIZE)
/* Sector page values, used to store current status of the DFLASH */
#define FEE_DFLASH_SECTOR_SIZE            (FLS_SECTOR0_SIZE)
#define FEE_DFLASH_BANK1_BASE             (FEE_DFLASH_SECTOR_SIZE)
#define FEE_SECTOR0                       (0U)
#define FEE_SECTOR1                       (1U)
#define FEE_DFLASH_BANK0_BASE             (0x0000U)
/*Name to be changed*/
#define FLS_ERASE_SECTORS                 (FLS_17_DMU_NVMSECTOR_SIZE/4096)
/* Sector status */
#define FEE_SP_INIT                       (0U)
#define FEE_SP_DONE                       (1U)
/* DFlash status at Initialization */
#define FEE_S0_S1_EMPTY                   (0x0U)
#define FEE_S0_VALID                      (0x1U)
#define FEE_S1_VALID                      (0x2U)
#define FEE_S0_S1_VALID                   (0x3U)
#define FEE_S0_S1_INVALID                 (0x4U)


#endif

/*---------- Data flash related constant End ---------------------------*/

/*---------- Cache table related constant  -----------------------------*/

/* Cache Update states */
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

#define FEE_CACHE_FIND_NEXT_BLK            (1U)
#define FEE_CACHE_UPDATE_COMPLETE          (3U)

/* This macro is used as dummy parameter. This will be used while calling 
 Fee_lGCErrorHandler when GC write/erase/GC on GC error occurred */
#define FEE_UNUSED_PARAM                   ((uint16)0xFFFFU)
#else

#define FEE_CACHE_IDLE_QS                  (4U)

#endif

#define FEE_CACHE_IDLE                     (0U)
#define FEE_LOG_BLOCK_NOT_FOUND            ((uint16)0xFFFFU)



/*---------- Cache table related constant End --------------------------*/

/*---------- Fee Job related constant  ---------------------------------*/

/* Pending request types */
#define FEE_PEND_PREV_NO_REQ                (1U)
#define FEE_PEND_PREV_READ_REQ              (3U)
#define FEE_PEND_PREV_READ_NOTIF            (5U)
#define FEE_REQ_READ                        (6U)
#define FEE_REQ_NORM_WRITE                  (8U)
#define FEE_REQ_IMM_WRITE                   (9U)
#define FEE_PEND_PREV_COMPARE               (10U)
#define FEE_PEND_INTR_COMPARE               (12U)

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

#define FEE_PEND_INTR_READ                  (13U)
#define FEE_PEND_INTR_WRITE                 (14U)
#define FEE_PEND_PREV_WRITE_REQ             (2U)

#endif

#define FEE_WRITE_FAIL                      (15U)

/* Job states */
#define FEE_JOB_IDLE                        (0U)
#define FEE_JOB_REQSTD                      (1U)
#define FEE_JOB_DONE                        (2U)
/* Job results */
#define FEE_JOB_PASS                        (0U)
#define FEE_JOB_FAIL                        (1U)
/* FEE JOBS */
#define FEE_WRITE_JOB                       (FLS_17_DMU_WRITE_JOB)
#define FEE_READ_JOB                        (FLS_17_DMU_READ_JOB)
#define FEE_ERASE_JOB                       (FLS_17_DMU_ERASE_JOB)
#define FEE_NO_JOB                          (FLS_17_DMU_NO_JOB)
#define FEE_CANCEL_JOB                      (FLS_17_DMU_CANCEL_JOB)

/*---------- Fee Job related constant End ------------------------------*/

/*---------- Fee Main state machine related constant -------------------*/

/* Fee Main Function States */
#define FEE_MAIN_UNINIT         (0U)
#define FEE_MAIN_INITGC         (1U)
#define FEE_MAIN_CACHEUPDATE    (2U)
#define FEE_MAIN_READ           (3U)
#define FEE_MAIN_WRITE          (4U)
#define FEE_MAIN_GC             (5U)

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)

#define FEE_MAIN_INITQS         (6U)
#define FEE_MAIN_QS             (7U)

#endif

#define FEE_MAIN_NONE           (10U)

/*---------- Fee Main state machine related constant End ----------------*/

/*---------- Fee Error related constant ---------------------------------*/

/* Error events during User/Internal operations */
#define FEE_CANCEL              ((uint8)0x0)
#define FEE_WRITE               ((uint8)0x1)
#define FEE_READ                ((uint8)0x2)
#define FEE_INVALIDATE          ((uint8)0x6)

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

#define FEE_GC_E_OK             ((uint8)0x0)
#define FEE_GC_WRITE            ((uint8)0x3)
#define FEE_GC_READ             ((uint8)0x4)
#define FEE_GC_ERASE            ((uint8)0x5)
#define FEE_GC_TRIG             ((uint8)0x7)


/* Un-configured block related constants */
#define FEE_UNCONFIG_BLK_LIMIT_CROSSED    ((uint8)0xFF)

#endif

/*---------- Fee Error related constant End ----------------------------*/

/*---------- QS data related constant End ----------  ------------------*/

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)

/* Macros for QS STATE values in DFLASH0 */
#define FEE_QS_STATE_DFERASE_STATE       (0x00000000U)
#define FEE_QS_STATE_WRITE_COMPLETE_LSW  (0x33334444U)
#define FEE_QS_STATE_WRITE_COMPLETE_MSW  (0x55556666U)
#define FEE_QS_STATE_WRITE_STARTED_LSW   (0x11112222U)
#define FEE_QS_STATE_WRITE_STARTED_MSW   (0x77778888U)
#define FEE_QS_STATE_ERASE_COMPLETE_LSW  FEE_QS_STATE_WRITE_COMPLETE_LSW
#define FEE_QS_STATE_ERASE_COMPLETE_MSW  FEE_QS_STATE_WRITE_COMPLETE_MSW
#define FEE_QS_STATE_ERASE_STARTED_LSW   FEE_QS_STATE_WRITE_STARTED_LSW
#define FEE_QS_STATE_ERASE_STARTED_MSW   FEE_QS_STATE_WRITE_STARTED_MSW
#define FEE_QS_STATE_DESTROY             (0xFFFFFFFFU)
/* quasi static block intermediate states */
#define FEE_REQ_QUASI_READ                        (16U)
#define FEE_REQ_QUASI_WRITE                       (17U)
#define FEE_REQ_QUASI_ERASE                       (18U)
#define FEE_INITQS_COMPLETE                       (7U)
#define FEE_MAX_BCC_QS                            (65535U)
#define FEE_QS_STATE_ERASE_STARTED_OFFSET         (24U)
#define FEE_QS_STATE_WRITE_COMPLETED_OFFSET       (16U)
#define FEE_QS_STATE_WRITE_STARTED_OFFSET         (8U)
#define FEE_QS_STATE_CYCLE_COUNT_OFFSET           (32U)

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)


#define FEE_PAGES_IN_WL                       ((uint8)64)
#define FEE_DFLASH_QS_SIZE               (FLS_17_DMU_QSDATA_SIZE)

/* quasi static region hardening Frequency */
/* The check and hardening is performed on a scalable part of QS area,
Here desired checking rate  is chosen as 4% of the QS area as per the concept*/
#define FEE_HARDENING_RATE \
        ((((FEE_DFLASH_QS_SIZE * 4U)/(100U * FEE_DFLASH_WORDLINE_SIZE)) + 1U))

#define FEE_GC_HARDEN_QS_SECTOR          (0x11U)
#define FEE_QS_SECTOR_BASE               (FLS_17_DMU_QSDATA_STARTADDRESS)
#define FEE_HARDEN_CHK_PAGE              ((uint8)0x55)
#define FEE_HARDEN_CHK_WL                ((uint8)0xAA)
#define FEE_HARDEN_NOT_REQRD             ((uint8)0U)
#define FEE_HARDEN_REQRD                 ((uint8)1U)
#define FEE_HARDEN_REQ_ERROR             ((uint8)2U)
#define FEE_NO_HARDEN_RET_ADDRESS        (0xFFFFFFFFU)

#endif

#define FEE_QS_IDLE                      ((uint8)0)
#define FEE_REPAIR_JOB                   ((uint8)20)
#define FEE_QS_DATA_OFFSET               36
#define FEE_QS_STATUS_PAGES              5U
#define FEE_QS_HARDING_IDLE              (0U)
#define FEE_QS_DATA_OFFSET_SECOND_PAGE   (40U)

#endif

/*---------- QS data related constant End ------------------------------*/

/******************************************************************************
**                      Private Type Definitions                             **
******************************************************************************/

/******************************************************************************
**                      Private Function Declarations                        **
******************************************************************************/

#define FEE_START_SEC_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safe gaurd. It complies to Autosar guidelines. */
#include "Fee_MemMap.h"

static void Fee_lDecideMainJob(void);

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
static boolean Fee_lIsUnerasableAddr(const uint32 Addr);
#endif

static void Fee_lHandleWriteFail(void);

static void Fee_lHandleUsrJobFailure(const uint8 Error);

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

static void Fee_lUpdateBlockInfo(const Fee_CacheStatusType Status,
                                 const uint16 Index, const uint16 pageCount);

static void Fee_lUpdateUnconfigBlockInfo(const uint16 BlockNumber, \
    const uint16 PageCount);

#endif

static void Fee_lRegisterWriteRequest(const uint8 * const DataWriteBufferPtr,
                                      const Fee_BlockType * const BlockPtr);

static Std_ReturnType Fee_lRegisterNvmRead(const uint16 BlockNumber,
    const uint16 BlockOffset, uint8 * const DataBufferPtr, const uint16 Length,
    const uint8 GetPrevCopy );

static Std_ReturnType Fee_lRegisterNvmWrite( \
    const uint8 * const DataWriteBufferPtr, \
    const Fee_BlockType * const BlockPtr);

static uint16  Fee_lGetUsrBlockIndex(const uint16 BlockNumber);

static Fls_17_Dmu_Job_Type Fee_lGetUserJob(const uint8 PendReqType);

static MemIf_StatusType Fee_lGetStatus(void);

LOCAL_INLINE void Fee_lMainNoneTransHdlr(void);

LOCAL_INLINE void Fee_lMainReadTransHdlr(void);

LOCAL_INLINE void Fee_lMainWriteTransHdlr(void);

LOCAL_INLINE void Fee_lMainCacheUpdtTransHdlr(void);

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

LOCAL_INLINE void Fee_lCheckPrevPage(const uint32 EndAddr);

LOCAL_INLINE void Fee_lPrepareInvldReqBuff(const uint32 BlockCycleCount,
    uint8 * const ReadWriteBuffPtr,
    const uint16 BlockIndex);

LOCAL_INLINE void Fee_lHandleBlkHeaderFound(const uint8  PotentialMarkerPage,
    const uint32 DataNextPageCount);

LOCAL_INLINE void Fee_lHandleBlkMarkerFound(const uint32 LWBHeaderAddress,
    const uint32 LWBMarkerAddress,
    const uint16 PageCount);
LOCAL_INLINE void Fee_lComputeNextWLAddr( Fee_SectorInfoType * \
    const SectorInfoPtr);

LOCAL_INLINE uint8 Fee_lEvaluateStatePage(void);

LOCAL_INLINE uint8 Fee_lEvaluateStatePageFormat(void);

LOCAL_INLINE uint8 Fee_lEvaluateStatePageMarker(void);

LOCAL_INLINE uint32 Fee_lEvaluateStatePageCrc(const uint32 * const DataPtr,
    const uint32 Length);

LOCAL_INLINE uint32 Fee_lIsWLBeginning(const uint32 address);
#endif

LOCAL_INLINE uint32 Fee_lGetNextWLAddr(const uint32 address);

LOCAL_INLINE uint32 Fee_lGetWLBeginning(const uint32 address);

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

LOCAL_INLINE boolean Fee_lIsBlockAffected(const uint16 BlockNumber,
    const uint32 BlockAddr);

LOCAL_INLINE Std_ReturnType Fee_lEvaluateBlkHeader(const uint16 BlockNumber,
    const uint16 BlockPageCount);

LOCAL_INLINE Std_ReturnType Fee_lPerformReadCheck(const uint16 UserBlockIndex);

LOCAL_INLINE Std_ReturnType Fee_lCheckBlkCycleCnt(
  const Fee_BlockType *const BlockPtr,
  const uint32 BlockCycleCount);

LOCAL_INLINE boolean Fee_lIsSectorEmpty(const uint8 state, const uint8 used);

#endif

LOCAL_INLINE boolean Fee_lIsUserReadReqstd(const Fee_StateDataType * \
    const s_ptr);

LOCAL_INLINE boolean Fee_lIsUserWriteInvldReqstd
(const Fee_StateDataType * const s_ptr);

#if (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
static void Fee_lGcHardenQsSector(void);

static boolean Fee_lIsQsWriteReadAllowedbyGC(void);
static Fls_17_Dmu_AddressType Fee_lGcHardenReqChk(void);

#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

static uint32 Fee_lGetBlkCycleCount(const uint16 Index);

static void Fee_lClearFeeReadWriteBuffer(void);

static void Fee_lPrepareMarkerBuffer(void);

static void Fee_lClearMarkerBuffer(void);

static void Fee_lHandleIntrWrite(void);

static void Fee_lLastPgHandler(void);

static void Fee_lUpdateCache(void);

static void Fee_lPrepareStatePageBuffer(const uint8 Bank, \
                                        const uint8 SectorState);

static void Fee_lHandleUserWrite(const uint16 UserBlockIndex);

static void Fee_lHandleWritePrepDFLASH(const uint8 *const SrcPtr);

static void Fee_lInitGC(void);

static void Fee_lLocalRead(void);

static uint16 Fee_lCheckReadLength(const Fls_17_Dmu_AddressType ActualAddr,
                                   const uint16 Length);

static void Fee_lLocalWrite(void);

static void Fee_lGCErrorHandler(const uint8 Error , const uint16 Index);

static void Fee_lGcRead(const Fls_17_Dmu_AddressType Position,
                        const uint16 Offset);

static void Fee_lGcPrologue(void);

static void Fee_lGcStartCopy(void);

static void Fee_lGcDiscardUnconfigBlk(const uint16 Index);
static void Fee_lGcDiscardConfigBlk(const uint16 Index);

static void Fee_lClearFeeGcReadWriteBuffer(void);

static void Fee_lHandleInitGcFail(void);

static void Fee_lGcCopyReadNxtPage(void);

static void Fee_lGarbageCollection(void);

static void Fee_lUpdateNonZeroWLInfo(Fee_SectorInfoType *const SectorInfoPtr, \
                                     const uint32 SrcAddr);

static boolean Fee_lIsReadAllowedbyGC(void);

static boolean Fee_lIsWriteInvldAllowedbyGC(void);

static boolean Fee_lIsLastWrittenWLAffected(const uint16 StartOffset);

static boolean Fee_lGcCheckBlkCopy(void);

static uint8 Fee_lGcStartCopyWrite(void);

static uint8 Fee_lGcWrite(const Fls_17_Dmu_AddressType Position,
                          const uint16 Offset);

static uint8 Fee_lGcErasePrevSector(const uint8 GcState);

static uint8 Fee_lGcProgramStatePage(const uint8 GcState);

static Fee_PageType Fee_lGetDFLASHPages(const uint16 Size);

static uint32 Fee_lGetFreeDFLASHPages(const uint8 BankNumber,
                                      const uint32 StartAddr);

LOCAL_INLINE void Fee_lHandleIntrRead(void);

LOCAL_INLINE void Fee_lComputeNextFreePageAddr(const uint32 BankNumber);

LOCAL_INLINE void Fee_lUpdateCacheTable(const uint32 BankNumber, \
                                        const uint32 EndAddr);

LOCAL_INLINE Std_ReturnType Fee_lPerformWriteCheck( \
    const Fee_BlockType * const BlockPtr);

LOCAL_INLINE Std_ReturnType Fee_lPerformCurrBlkCheck(
  const Fee_BlockType * const BlockPtr);

LOCAL_INLINE uint32 Fee_lGetBlockHeaderAddress(const uint32 LWBMarkerAddress,
    const uint16 PageCount);

LOCAL_INLINE boolean Fee_lIsGcTriggeredOnce
(const Fee_StateDataType *const StateDataPtr);

LOCAL_INLINE boolean Fee_lIsSectorThresholdCrossed(const uint32 FreePages,
    const uint32 PageCount);

LOCAL_INLINE boolean Fee_lIsSectorEndCrossed(const uint32 FreePages,
    const uint32 PageCount);

LOCAL_INLINE boolean Fee_lGcCheckUnconfigBlkCopy(void);

LOCAL_INLINE uint16 Fee_lLocalReadStart(const Std_ReturnType ReturnValue,
                                        const uint16 UserBlockIndex);

LOCAL_INLINE void Fee_lMainGCTransHdlr(void);

LOCAL_INLINE void Fee_lHandleErasePrepDFLASH(void);

LOCAL_INLINE void Fee_lIDSM(void);

LOCAL_INLINE void Fee_lINSM(void);

LOCAL_INLINE void Fee_lIPrepDFlashSM(void);

LOCAL_INLINE void Fee_lInitGCDSMTransHandler(void);

LOCAL_INLINE void Fee_lInitGCPrepDFlSTransHandler(void);

LOCAL_INLINE void Fee_lInitGCTransHandler(void);

LOCAL_INLINE void Fee_lHandleGcFail(void);

LOCAL_INLINE void Fee_lGcRequested(void);

LOCAL_INLINE void Fee_lGcBlkCompare(void);

LOCAL_INLINE void Fee_lHandleUnConfigGcCopyError(void);

LOCAL_INLINE void Fee_lHandleConfigGcCopyError(void);

LOCAL_INLINE void Fee_lGcEraseCompare(const uint8 GcState);

LOCAL_INLINE void Fee_lGcStatePageCompare(const uint8 GcState);

LOCAL_INLINE uint8 Fee_lCheckPrevWordline(Fee_SectorInfoType * const \
    SectorInfoPtr, const uint32 EndAddr);

LOCAL_INLINE void Fee_lSetInitGc(const uint8 DFlashStatus);

LOCAL_INLINE uint8 Fee_lBuildDFlashStatus(void);

LOCAL_INLINE uint8 Fee_lGetSectorInfo(const uint32 BankNumber, \
                                      const uint32 EndAddr);

LOCAL_INLINE void Fee_lPerformPrevBlkCheck(void);

LOCAL_INLINE void Fee_lUpdateGcCurrBlockInfo(void);

LOCAL_INLINE void Fee_lperformStuffCheck(const uint16 UserBlockIndex);


LOCAL_INLINE void Fee_lPrepareWriteReqBuff(const uint32 BlockCycleCount,
    uint8 * const ReadWriteBuffPtr,
    const uint16 BlockIndex,
    const uint16 BlockSize);

LOCAL_INLINE void Fee_lHandleUserWriteReq(const uint16 UserBlockIndex);

LOCAL_INLINE void Fee_lHandleIntrWriteCompare(const uint16 UserBlockIndex);
LOCAL_INLINE void Fee_lMainGCHdlr(void);
LOCAL_INLINE uint8 Fee_lHandleGcCopy(void);
#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)

static void Fee_lQsInit(void);

static void Fee_lMainQsTransHdlr(void);

static void Fee_lEvalQsBlockState(Fee_CacheType *const Cacheptr);

static void Fee_lHandleQsJobSuccess(void);

static void Fee_lHandleQsJobFailure(const uint8 Error);

static void Fee_lQsBlockErase(void);

static void Fee_lQsBccWrite(void);

static void Fee_lQsBlockWrite(void);

static void Fee_lQsProgState(void);

static void Fee_lQsIDSM(void);

static void Fee_lMainQs(void);

#if (FEE_CANCELL_ALL_API == STD_ON)
static void Fee_lCancelAll (void);


#if (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
static void Fee_lCancelWrite(void);

static void Fee_lCancelAllGCrestart(void);
#endif

#endif
static Std_ReturnType Fee_lRegisterQsRead( const uint16 BlockNumber,
    const uint16 BlockOffset,  uint8 * const DataBufferPtr,
    const uint16 Length);

static Std_ReturnType Fee_lRegisterQsWrite( \
    const uint8 * const DataWriteBufferPtr, \
    const Fee_BlockType * const BlockPtr);

static Fee_QsBlock_StateType Fee_lEvalQsBlockWriteStatus(void);

static Fee_QsBlock_StateType Fee_lEvalQsBlockEraseStatus(void);

static uint16 Fee_lQsGetBcc(const uint16 Blkindex);
static Std_ReturnType Fee_lEvalQsBlockVirginStatus(void);
static void Fee_lHandleQsVirginBlocks(void);


#endif

#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
static void Fee_lReportError(uint8 ApiId, uint8 ErrorId);

LOCAL_INLINE Std_ReturnType Fee_lReadDetSafetyCheck(const uint16 BlockNumber,
    const uint16 BlockOffset,
    const uint8 *const DataBufferPtr,
    const uint16 Length,
    uint8 ApiId);

LOCAL_INLINE Std_ReturnType Fee_lCancelDetSafetyCheck(void);
#endif

LOCAL_INLINE void Fee_lHandleCancelNotification(void);
LOCAL_INLINE void Fee_lHandleUsrJobErrorNotification(Fls_17_Dmu_Job_Type Job);
LOCAL_INLINE void Fee_lHandleReadJobEndNotification(void);
#if (FEE_INITCHECK_API == STD_ON)
LOCAL_INLINE uint32 Fee_lCalDataStructCrc(void); 
#endif

#define FEE_STOP_SEC_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safe gaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"

/******************************************************************************
**                      Global Constant Definitions                          **
******************************************************************************/

/******************************************************************************
**                      Global Variable Definitions                          **
******************************************************************************/
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FEE_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
/*MISRA2012_RULE_19_01_JUSTIFICATION:File inclusion after pre-processor
directives is
 allowed only for MemMap.h*/
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safe gaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"
/* [cover parentID={5C702DD9-D7F5-4c61-9ED1-45F6D8353DFB}][/cover] */
static const Fee_ConfigType * Fee_CfgPtr ;
/* [cover parentID= {E7D4FCB6-8209-4943-99E3-209E2F7CC616}][/cover] */
#if (FEE_INITCHECK_API == STD_ON)

static uint32 Fee_DataStrcutInitCrc;

#endif

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FEE_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
/*MISRA2012_RULE_19_01_JUSTIFICATION:File inclusion after
pre-processor directives is
 allowed only for MemMap.h*/
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safe gaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"



/******************************************************************************
**                      Private Constant Definitions                          *
******************************************************************************/
/* FEE state page Non Zero Data structure */
#define FEE_START_SEC_CONST_ASIL_B_LOCAL_32
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

static const uint32 Fee_StateHalf[] = { 0xFFFFFFC6U, 0xFFFFFFFFU,
                                        0xFFFFFFC6U, 0xFFFFFFFFU,
                                        0xFFFFFFC6U, 0xFFFFFFFFU,
                                        0xFFFFFFC6U, 0xFFFFFFFFU,
                                        0xFAFA5FC6U
                                      };

#endif

#define FEE_STOP_SEC_CONST_ASIL_B_LOCAL_32
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"
/******************************************************************************
**                      Private Variable Definitions                         **
******************************************************************************/

/******************************************************************************
**                      Global Function Definitions                          **
******************************************************************************/
#define FEE_START_SEC_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safe gaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"

/******************************************************************************
** TRACEABILITY: [cover parentID={35CCD881-754A-4bd0-94B3-858BE25F259C}]     **
**                                                                           **
** Syntax : void Fee_Init (const Fee_ConfigType* const ConfigPtr)            **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID:  0x00                                                         **
**                                                                           **
** Sync/Async:  Asynchronous                                                 **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) : ConfigPtr - Pointer to the selected configuration set.  **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  void                                                   **
**                                                                           **
** Description : Driver Module Initialization function                       **
**               This service shall initialize the Flash EEPROM Emulation    **
**               module using the values provided in the configuration set.  **
**                                                                           **
******************************************************************************/
/* [cover parentID={8C26701C-9198-4408-8462-33D3FEF6D160}]
Fee_Init
[/cover] */
/* [cover parentID={5ADF6F97-3CF5-4ef0-9522-0E11F965AAFB}]
Resistance against Resets and Power Failures
[/cover] */

void Fee_Init (const Fee_ConfigType* const ConfigPtr)
{

  Fee_StateDataType  *StateDataPtr;
  Fee_GcBlkInfoType  *GcBlkInfoPtr;
  Fee_CacheType      *BlockPtr;
  Fee_SectorInfoType *SectorInfoPtr;
  Fee_LastWrittenBlkInfoType  *LastBlkInfoPtr;

  uint32 Index;
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
  uint32 EndAddr;
  uint8  DFlashStatus;
  uint8  ReturnVal;
#endif

  /* [cover parentID={C8F64E4E-6C3A-4ac0-92C0-385C6AEEE49F}]
     Is Configuration pointer is NULL?
     [/cover] */
  /* [cover parentID={63531847-F84D-4dc2-B0E1-A33E2FBE6E94}]
     Imported SW interfaces
     [/cover] */
  if (ConfigPtr == NULL_PTR)
  {
  /* [cover parentID={C16B81AE-C6F3-4d6e-9CA2-AD009DDE7613}]
      DET or Safety is Enbaled
      [/cover] */    
#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
    
    Fee_lReportError(FEE_SID_INIT, FEE_E_PARAM_POINTER);
#endif
  }   /*Check for state variable and block config pointer*/
  else if((ConfigPtr->FeeStatePtr != NULL_PTR) &&
          (ConfigPtr->FeeBlockConfigPtr != NULL_PTR))
  {
    Fee_CfgPtr = ConfigPtr;
    StateDataPtr = Fee_CfgPtr->FeeStatePtr;
    SectorInfoPtr = StateDataPtr->FeeSectorInfo;


    /* Initialize the state variables of various state machines */

    /* Initialize the cache related variables */
    Index = FEE_RESET;
    do
    {
      BlockPtr = &(StateDataPtr->FeeBlockInfo[Index]);
      BlockPtr->Address = FEE_RESET;
      BlockPtr->BlockSize = FEE_RESET;
      BlockPtr->BlockNumber = FEE_RESET;
      BlockPtr->Status.Valid = FEE_RESET;
      BlockPtr->Status.Consistent = FEE_RESET;
      BlockPtr->Status.Copied = FEE_RESET;
      BlockPtr->Status.PrevCopyValid = FEE_RESET;
      BlockPtr->Status.PrevCopyConsistent = FEE_RESET;
      BlockPtr->Status.PrevCopyCopied = FEE_RESET;
      BlockPtr->PrevCopyAddress = FEE_RESET;
      BlockPtr->PrevBlkSize = FEE_RESET;

      Index++;
    }
    while(Index < (uint32)(FEE_TOTAL_BLOCK_COUNT));
    StateDataPtr->FeeCacheState = FEE_CACHE_IDLE;

    StateDataPtr->FeeGCUnconfigBlkCopyIndex = FEE_RESET;
    StateDataPtr->FeeUncfgBlksExceeded = FEE_RESET;
    StateDataPtr->FeeUnConfigBlockCount = FEE_RESET;

    GcBlkInfoPtr = &(StateDataPtr->FeeGcCurrBlkInfo);
    GcBlkInfoPtr->BlockNumber = FEE_RESET;
    GcBlkInfoPtr->PageCount = FEE_RESET;
    GcBlkInfoPtr->Addr = FEE_RESET;
    GcBlkInfoPtr->Consistent = FEE_RESET;

    for(Index = FEE_RESET; Index < FEE_MAX_NUM_OF_BLKS_IN_WL; Index++)
    {
      StateDataPtr->FeeGcLWBGcSrcAddr[Index] = FEE_RESET;
    }
    StateDataPtr->FeeGcBlkIndexInWL = FEE_RESET;

    StateDataPtr->FeeGcState = FEE_GC_IDLE;
    StateDataPtr->FeeGCCopyIndex = FEE_RESET;
    StateDataPtr->FeeGcSrcAddr = FEE_RESET;
    StateDataPtr->FeeGcDestAddr = FEE_RESET;
    StateDataPtr->FeeDisableGCStart = (boolean)FALSE;
    StateDataPtr->FeeGCImmBlkWrite = (boolean)FALSE;

#if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
    StateDataPtr->FeeEraseSuspendStatus = FEE_ERASE_NOT_SUSPENDED;
    StateDataPtr->FeeEraseResumeDemReported = FEE_RESET;
#endif

    /* Initialize the InitGC related variables */
    StateDataPtr->FeeInitGCState = FEE_INITGC_IDLE;
    StateDataPtr->FeePrepDFLASHState = FEE_PREPDF_ERASE_S0;
    StateDataPtr->FeeRepairStep = FEE_REPAIR_IDLE;
    StateDataPtr->FeeGcResumeState = FEE_RESET;

    /* Initialize the Read and Write related variables */
    StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_NO_REQ;
    StateDataPtr->FeeLastWrittenBlockDirty = FEE_LWB_NOT_DIRTY;

    LastBlkInfoPtr = &(StateDataPtr->FeeLastWrittenBlkInfo);
    LastBlkInfoPtr->Addr = FEE_RESET;
    LastBlkInfoPtr->BlockNumber = FEE_RESET;
    LastBlkInfoPtr->PageCount = FEE_RESET;
    LastBlkInfoPtr->Status.Valid = FEE_RESET;
    LastBlkInfoPtr->Status.Consistent = FEE_RESET;
    LastBlkInfoPtr->Status.Copied = FEE_RESET;
    LastBlkInfoPtr->Status.PrevCopyValid = FEE_RESET;
    LastBlkInfoPtr->Status.PrevCopyConsistent = FEE_RESET;
    LastBlkInfoPtr->Status.PrevCopyCopied = FEE_RESET;

    StateDataPtr->FeeNextFreePageAddr = FEE_RESET;
    StateDataPtr->FeeBlockStartAddr = FEE_RESET;

    StateDataPtr->FeeUserReadDestPtr = (uint8*)NULL_PTR;
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
    /* Initialize common variables */
    Fee_lClearFeeReadWriteBuffer();
    Fee_lClearFeeGcReadWriteBuffer();
#endif

    StateDataPtr->FeeBlkPageCount = (Fee_PageType)FEE_RESET;
    StateDataPtr->FeeCurrReqBlockNum = FEE_RESET;
    StateDataPtr->FeeUserWriteBytesCount = FEE_RESET;
    StateDataPtr->FeeUserJobFailCount = FEE_RESET;

    StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus = FEE_RESET;
    StateDataPtr->FeeStatusFlags.FeeBlkModified = FEE_RESET;
    StateDataPtr->FeeStatusFlags.FeeWriteInvldAPICalled = FEE_RESET;
    StateDataPtr->FeeStatusFlags.FeeStartInitGC = FEE_RESET;
    StateDataPtr->FeeStatusFlags.FeeCurrSector = FEE_RESET;

    StateDataPtr->FeeMainJob = FEE_MAIN_UNINIT;
    StateDataPtr->FeeJobResult = MEMIF_JOB_OK;
    StateDataPtr->FeeIntrJob = FEE_NO_JOB;
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
    StateDataPtr->FeeIntrJobResult = FEE_JOB_PASS;
    StateDataPtr->FeeUserJobStatus = FEE_JOB_IDLE;
    StateDataPtr->FeeUserJobResult = FEE_JOB_PASS;
    StateDataPtr->FeeIntrJobFailCount = FEE_RESET;

    StateDataPtr->FeeWLAffectedType = FEE_LWB_NOT_AFFECTED;
    StateDataPtr->FeeWriteAffectedAddr = FEE_RESET;

    /* Initialize Sector State information */
    for(Index = FEE_RESET; Index < FEE_SECTORS; Index++)
    {
      /*MISRA2012_RULE_18_4_JUSTIFICATION:This warning is for the core FEE
      structures which are containing the Block and sector info and affects the
      entire FEE functionality.Changing these would increase the risk of major
      functional impact on the entire FEE code,thereby putting the complete
      functionality of FEE at risk. */
      SectorInfoPtr = SectorInfoPtr + Index;
      SectorInfoPtr->State = FEE_RESET;
      SectorInfoPtr->StateCount = FEE_RESET;
      SectorInfoPtr->UnerasableWLCount = FEE_RESET;
      SectorInfoPtr->UnerasableWLAddr[0] = FEE_RESET;
      SectorInfoPtr->UnerasableWLAddr[1] = FEE_RESET;
      SectorInfoPtr->Status.Dirty = FEE_RESET;
      SectorInfoPtr->Status.Used = FEE_RESET;
      SectorInfoPtr->StatePageAddr = FEE_RESET;
      SectorInfoPtr->NextFreeWLAddr = FEE_RESET;
      SectorInfoPtr->NonZeroWLCount = FEE_RESET;
      SectorInfoPtr->NonZeroWLAddr[0] = FEE_RESET;
      SectorInfoPtr->NonZeroWLAddr[1] = FEE_RESET;
    }
    StateDataPtr->FeeStateCount = FEE_RESET;
    StateDataPtr->FeeSectorCount = FEE_RESET;
    StateDataPtr->FeeComparedLen = FEE_RESET;
    StateDataPtr->FeeReadLen = FEE_RESET;
    StateDataPtr->FeeUnErasableWLAddrTemp[0] = FEE_RESET;
    StateDataPtr->FeeUnErasableWLAddrTemp[1] = FEE_RESET;
    StateDataPtr->FeeUnErasableWLCountTemp = FEE_RESET;
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
    /* Read sector information */
    for(Index = FEE_RESET; Index < FEE_SECTORS; Index++)
    {
      if(Index == FEE_RESET)
      {
        EndAddr = FEE_DFLASH_BANK0_BASE;
      }
      else
      {
        EndAddr = FEE_DFLASH_BANK1_BASE;
      }
      StateDataPtr->FeeCurrSectSrcAddr = EndAddr +
                                         (FEE_DFLASH_SECTOR_SIZE -
                                          FEE_DFLASH_WORDLINE_SIZE);
      do
      {
        ReturnVal = Fee_lGetSectorInfo(Index, EndAddr);
      }
      while(ReturnVal == FEE_SP_INIT);
    }

    DFlashStatus = Fee_lBuildDFlashStatus();

    /* Initialize for quasi static blocks if configured */
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)

    StateDataPtr->FeeQsBlockVirginCount = FEE_RESET;
    Fee_lQsInit();

#endif

#if (FEE_CANCELL_ALL_API == STD_ON) && \
    (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)

    StateDataPtr->FeeCancelallGCstate = FEE_GC_NOT_CANCLD;

#endif

    StateDataPtr->FeeEraseVerErr = FEE_RESET;
    StateDataPtr->FeeProgVerErr  = FEE_RESET;
    Fee_lSetInitGc(DFlashStatus);

    if( Fee_CfgPtr->FeeGCConfigSetting.FeeGcRestartPoint ==
        (uint32)FEE_GC_RESTART_INIT )
    {
      /* [cover parentID={14D5A81B-1A65-400a-B2D0-A89AAE9BED19}]
      Assign FeeStartInitGC = 1
      [/cover] */
      /* Start Init GC:
      Check the current state of the sectors and bring them to normal state*/
      StateDataPtr->FeeStatusFlags.FeeStartInitGC = FEE_SET ;
    }

#else
    StateDataPtr->FeeQsBlockVirginCount = FEE_RESET;
    Fee_lQsInit();
    /* [cover parentID={EFCEB24D-1879-4c0d-97A3-39C9A8BE68F1}]
        Set FeeInitAPICalled , indicating Fee Init API is called
       [/cover] */
    
    /* [cover parentID={4A8624DD-3BB9-46c2-B5FB-EB8A9341D14B}]
       Check for init GC restart
       [/cover] */
    if( Fee_CfgPtr->FeeGCConfigSetting.FeeGcRestartPoint ==
        (uint32)FEE_GC_RESTART_INIT )
    {
      /* [cover parentID={14D5A81B-1A65-400a-B2D0-A89AAE9BED19}]
         Start init GC
         [/cover] */
      /* Start Init GC:
      Check the current state of the sectors and bring them to normal state*/
      StateDataPtr->FeeStatusFlags.FeeStartInitGC = FEE_SET ;
    }
#endif
 
#if (FEE_INITCHECK_API == STD_ON)    
 
     Fee_DataStrcutInitCrc = Fee_lCalDataStructCrc();     
     
#endif

  }  
  else
  {

#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)

    Fee_lReportError(FEE_SID_INIT, FEE_E_PARAM_POINTER);
#endif
    /* Report DET-Safety error if DET-Safety is Enabled */
  }
   /* [cover parentID={5F24109C-8447-4116-B653-3A53C9716F11}]
       Return
      [/cover] */

} /*End of Fee_Init*/

#if (FEE_SET_MODE_SUPPORTED == STD_ON) && \
    (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** TRACEABILITY: []                                                           **
**                                                                            **
** Syntax : void Fee_SetMode( const MemIf_ModeType Mode )                     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x01                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  MemIf_ModeType - Desired mode for the underlying flash  **
**                                      driver.                               **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : This API sets the mode of the underlying flash driver        **
**                                                                            **
*******************************************************************************/
/* [cover parentID={272C7054-BCB3-4896-8A50-62B33C986E77}]Fee_SetMode[/cover] */
/* [cover parentID={1905C7A8-06F4-4ae3-9AD0-A438DBF66138}]
Fee_SetMode
[/cover] */
void Fee_SetMode(const MemIf_ModeType Mode)
{
  /* [cover parentID={2632D8CE-7764-4eef-84D2-AF09AC67A8EA}]
      DET enabled
     [/cover] */

#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
 
  MemIf_StatusType   FeeStatus;
  uint8              Error;
   
   /* [cover parentID={2E09D74B-AC0E-4f9f-8ACD-59AF9D9BA2D0}]
       Is the configuration pointer NULL?
       [/cover] */
  /*Check for configuration pointer(Fee_CfgPtr)for null as part safety check */
  if(Fee_CfgPtr != NULL_PTR)
#endif
  {
   /* [cover parentID={2632D8CE-7764-4eef-84D2-AF09AC67A8EA}]
       DET or safety enabled
      [/cover] */
#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
    
    Error = FEE_RESET;
    /* [cover parentID={CCE44DC3-B99E-4da5-8892-DC625DA7592C}]
        Get Fee status
        [/cover] */
    /* Get the FEE status */
    FeeStatus = Fee_lGetStatus();
    /* [cover parentID={5AEA0B9D-1A43-4a9f-B405-2DC210601C39}]
        Is any user job ongoing?
        [/cover] */
    if(FeeStatus == MEMIF_BUSY)
    {
     /* [cover parentID={57D00748-5476-41f7-A9B3-07A4186C0828}]
        Report FEE_E_BUSY DET
        [/cover] */
        /* If busy, report error */
        Fee_lReportError(FEE_SID_SETMODE, FEE_E_BUSY);
        Error = FEE_SET;
    }
 
    if(Error == FEE_RESET)
#endif/* #if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)*/
    {
      /* set mode of FLS */
      Fls_17_Dmu_SetMode(Mode);
    }

  }
#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
  else
  {
   /* [cover parentID={73D8CF32-6D88-4c5d-919D-8A233A83931D}]
       Report FEE_E_UNINIT DET
      [/cover] */
    Fee_lReportError(FEE_SID_SETMODE, FEE_E_UNINIT);
  }
#endif
  /* [cover parentID={BA05C25B-11F6-4fe4-86EA-96E6EFF55374}]
      Return
     [/cover] */
}/* End of Fee_SetMode */

#endif /* #if (FEE_SET_MODE_SUPPORTED == STD_ON) */


/*******************************************************************************
** TRACEABILITY: [cover parentID={01E4E203-8396-4c5a-8D69-7498B9450CF6}]      **
**                                                                            **
** Syntax : Std_ReturnType Fee_Read(const uint16 BlockNumber,                 **
**           const uint16 BlockOffset,uint8 * const DataBufferPtr,            **
**           uint16 Length )                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID: 0x02                                                           **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockNumber - Logical Block Number                      **
**                    BlockOffset - Read address offset inside the block      **
**                    Length - Number of bytes to read                        **
**                                                                            **
** Parameters (out):  DataBufferPtr - Pointer to data buffer                  **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                    E_OK : Request accepted                                 **
**                    E_NOT_OK : Request is not accepted accepted. FEE module **
**                    is busy in servicing other request.                     **
** Description : This function shall take the block start address and         **
** offset and calculate the corresponding memory read address. The address    **
** offset and length parameter can take any value within the given block      **
** this allows reading of an arbitrary number of bytes from an arbitrary start**
** address inside a logical block.                                            **
**                                                                            **
*******************************************************************************/
/* [cover parentID={98AD05C0-8E14-4115-8F67-B9A8041F57A7}]
Fee_Read
[/cover] */
Std_ReturnType Fee_Read(const uint16 BlockNumber,
                        const uint16 BlockOffset,
                        uint8 *const DataBufferPtr,
                        const uint16 Length)
{


  Std_ReturnType       ReturnValue;
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  uint16               BlkIdx;
  Fee_StateDataType    *StateDataPtr;
#endif

  if (Fee_CfgPtr != NULL_PTR)
  {
   /* [cover parentID={DA1C5A03-C9D9-41cc-9994-F09270D9341C}]
      DET or safety enabled
      [/cover] */
    
#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
    /* [cover parentID={EA3ECE0D-3FA4-478c-94E9-4178292BE386}]*/
    /* [cover parentID={E43F3552-DD01-4714-89B2-CD53085F7B35}]*/
    ReturnValue = Fee_lReadDetSafetyCheck(BlockNumber, BlockOffset,
                                          DataBufferPtr, Length, FEE_SID_READ );
    if(ReturnValue != E_NOT_OK)
#endif
    {
     /* [cover parentID={27ABBB41-5DB3-41dd-9393-3C3C997010FB}]
        QS data block supported
        [/cover] */
#if(FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)

      StateDataPtr = Fee_CfgPtr->FeeStatePtr;
      BlkIdx = Fee_lGetUsrBlockIndex(BlockNumber);
      
      StateDataPtr->FeePendReqInfo.CacheIndex = BlkIdx;
      /* [cover parentID={13FCC1DB-57DE-45d3-AADD-472C333D926B}]
          Is it for QS user?
          [/cover] */
      /* [cover parentID={4FFD7EF7-6FB8-4845-A2E3-2760C7BE6563}]
          Get block index
         [/cover] */
      /* [cover parentID={331E8782-EC9A-442d-AD29-C2D2E5206977}]
          Test for request type
         [/cover] */
      if(Fee_CfgPtr->FeeBlockConfigPtr[BlkIdx].FeeUser ==
          (uint8)FEE_QUASI_STATIC_USER)
      {
       /* [cover parentID={09217FC4-21E4-4728-AD66-7C8F9476839B}]
          Register QS read request and update Flag status
          [/cover] */
        /* register quasi static block request */
        ReturnValue = Fee_lRegisterQsRead(BlockNumber, BlockOffset,
                                          DataBufferPtr, Length);
      }
      else
#endif
      {
        /* [cover parentID={88ECB633-69AC-4911-8F23-AD56B2B19A9B}]
Register NVM read request and update Flag status
[/cover] */
        /* register nvm request */
        ReturnValue = Fee_lRegisterNvmRead(BlockNumber, BlockOffset,
                                           DataBufferPtr, Length, FEE_RESET);
      }
    }

  }
  else
  { 
/* [cover parentID={08827D4A-F03C-4c07-8B21-1A66B88D2E9B}]
Set Flag as E_NOT_OK
[/cover] */
    ReturnValue = E_NOT_OK;
#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
    Fee_lReportError(FEE_SID_READ, FEE_E_UNINIT);
#endif
  }

  /* [cover parentID={CEBB81F8-0C10-40d8-A895-2DBA80493D87}]
Return Flag status
[/cover] */
  return(ReturnValue);
  /* [cover parentID={9ED72611-8C9A-46d5-93B5-457408211296}]
Return
[/cover] */

} /* End of Fee_Read */

/*******************************************************************************
** TRACEABILITY: [cover parentID={D93EC71E-D34B-46ed-99C1-8FCF19C0E7DB}]      **
**                                                                            **
** Syntax : Std_ReturnType Fee_Write(const uint16 BlockNumber,                **
**                    const uint8 *const DataBufferPtr)                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID: 0x03                                                           **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockNumber - Logical Block Number                      **
**                    DataBufferPtr - Pointer to data buffer                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                    E_OK : Request accepted                                 **
**                    E_NOT_OK : Request is not accepted accepted. FEE module **
**                    is busy in servicing other request.                     **
**                                                                            **
** Description : This function shall take the logical block number and        **
** determine the corresponding memory write address. This routine will        **
** perform the block write operation on DFLASH (DF_EEPROM).                   **
**                                                                            **
*******************************************************************************/
/* [cover parentID={9BF2094B-1F02-4294-978A-3CC5BEE6F977}]
Fee_write
[/cover] */

Std_ReturnType Fee_Write(const uint16 BlockNumber,
                         const uint8 *const DataBufferPtr)
{
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  Fee_StateDataType     *StateDataPtr;
#endif

  const Fee_BlockType*   BlockPtr;
  uint16                 UserBlockIndex;
  Std_ReturnType         ReturnValue;

  /*Check for configuration pointer(Fee_CfgPtr)for null as part safety check */
   /* [cover parentID={C330EC19-1B27-483d-9F93-50A8BBEF137B}]
Is configuration pointer NULL?
[/cover] */
  if(Fee_CfgPtr != NULL_PTR)
  {
    UserBlockIndex = Fee_lGetUsrBlockIndex(BlockNumber);
    /*MISRA2012_RULE_18_4_JUSTIFICATION:This warning is for the core FEE
    structures which are containing the Block and sector info and affects the
    entire FEE functionality.Changing these would increase the risk of major
    functional impact on the entire FEE code,thereby putting the complete
    functionality of FEE at risk. */
    BlockPtr = Fee_CfgPtr->FeeBlockConfigPtr + UserBlockIndex;

   /* [cover parentID={5D986A7A-A25D-46e0-B1A2-C507BD67870D}]
DET and SAFETY enabled
[/cover] */
#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
    ReturnValue = E_OK;
   
    /* [cover parentID={54C7D2CF-C17A-4808-A87B-E6E44C955019}]
       [/cover] */
       
    /* [cover parentID={CD11A821-E091-4690-8B0E-E0C7C168377F}]
Is block number invalid?
[/cover] */
    /* Check if the block number is correct */
    if(UserBlockIndex == FEE_LOG_BLOCK_NOT_FOUND)
    {
      /* [cover parentID={035716BA-D7A0-4e6d-BA03-266CDC60C242}]
Report FEE_E_INVALID_BLOCK_NO DET
[/cover] */
      Fee_lReportError(FEE_SID_WRITE, FEE_E_INVALID_BLOCK_NO);

      /* [cover parentID={54C7D2CF-C17A-4808-A87B-E6E44C955019}]
      Set Flag status as E_NOT_OK
      [/cover] */
      ReturnValue = E_NOT_OK;
    }
    /* [cover parentID={90D30799-F868-486d-BCF9-6A9E81AFC230}]
Is buffer pointer NULL?
[/cover] */
    /* Check if the buffer pointer is NULL */
    else if(DataBufferPtr == (uint8*)NULL_PTR)
    {
      /* [cover parentID={A51384D5-E04A-49de-A1FE-A37570AD26A9}]
Report FEE_E_PARAM_POINTER DET
[/cover] */
      Fee_lReportError(FEE_SID_WRITE, FEE_E_PARAM_POINTER);
      /* [cover parentID={54C7D2CF-C17A-4808-A87B-E6E44C955019}]
Set Flag status as E_NOT_OK
[/cover] */
      ReturnValue = E_NOT_OK;
    }
    else
    {
      /* dummy else */
    }

    if (ReturnValue != E_NOT_OK)
#endif /* End of FEE_DEV_ERROR_DETECT == STD_ON */
    {

  /* [cover parentID={9408C6E1-78CA-44d9-A113-984559B0BC0C}]
Check for Fee user
[/cover] */    
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
      StateDataPtr = Fee_CfgPtr->FeeStatePtr;
      StateDataPtr->FeePendReqInfo.CacheIndex = UserBlockIndex;

      /* [cover parentID={F5E19301-3D1B-464f-B8DF-D5AB7426A10D}]
Is it for Quasi static user?
[/cover] */
      if(Fee_CfgPtr->FeeBlockConfigPtr[UserBlockIndex].FeeUser ==
          (uint8)FEE_QUASI_STATIC_USER)
      {
        /* [cover parentID={5E7361C7-B818-4fdc-8798-94B5D8FDB1BA}]
Register QS write request and update Flag status
[/cover] */
        /* register quasi static block request */
        ReturnValue = Fee_lRegisterQsWrite(DataBufferPtr, BlockPtr);
      }
      else
#endif
      {
        /* [cover parentID={9CF0435A-C83A-4862-A4D6-F6B24EBF01FF}]
Register NVM write request and update Flag status
[/cover] */
        /* register nvm request */
        ReturnValue = Fee_lRegisterNvmWrite(DataBufferPtr, BlockPtr);
      }

    }

  }
  else
  {

    ReturnValue = E_NOT_OK;
#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={85CF0E69-4B89-4693-B69C-D559725B6FDF}]
Report FEE_E_UNINIT DET
[/cover] */
    Fee_lReportError(FEE_SID_WRITE, FEE_E_UNINIT);
#endif

  }


  /* [cover parentID={B5FAF6DF-269B-495a-A2FB-882234AA9528}]
Return Flag status
[/cover] */
  return(ReturnValue);
  /* [cover parentID={AE18F765-4BBD-4d68-AF6A-3FD069990AE6}]
Return
[/cover] */
}
/* End of Fee_Write */


/******************************************************************************
** TRACEABILITY: [cover parentID={1AC3C3C4-3B3C-468d-A5B2-684E3D5D03F1}]     **
**                                                                           **
** Syntax : void Fee_Cancel(void)                                            **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID: 0x04                                                          **
**                                                                           **
** Sync/Async:  Synchronous                                                  **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) :  None                                                   **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  void                                                   **
**                                                                           **
** Description : Service to call the cancel function of the underlying flash **
** driver.                                                                   **
** This functions shall cancel a pending request.                            **
** Note: An ongoing write request is not cancelled. However, a queued        **
** write request is cancelled. Any read request either queued or under       **
** execution is cancelled.                                                   **
**                                                                           **
******************************************************************************/
/* [cover parentID={43CB653F-D9FC-41ef-B842-8DD9AF9F04F2},
{7B564D5D-0FF2-4354-930B-A2008C7B3245}]
Fee_Cancel
[/cover] */
void Fee_Cancel(void)
{
  
  const Fee_StateDataType  *StateDataPtr;
  uint8 NotifyCancel;
  /* [cover parentID={DFB202B8-0D31-4b6a-8130-72239FDE002D}][/cover] */
  /* [cover parentID={A8F80E20-A667-4bcf-BED4-73D9BC7BBE34}]
DET or safety enabled
[/cover] */
#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
  Std_ReturnType  Error;
#endif
  /* [cover parentID={431752DA-0ABE-4d79-AB16-D26A3C494824}][/cover] */

  NotifyCancel  = FEE_RESET;
  if(Fee_CfgPtr != NULL_PTR)
  {
#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={431752DA-0ABE-4d79-AB16-D26A3C494824}]
Get the error status through calling the function
[/cover] */
    Error = Fee_lCancelDetSafetyCheck();
    if(Error == E_OK)
#endif
    {
      StateDataPtr = Fee_CfgPtr->FeeStatePtr;
      switch(StateDataPtr->FeePendReqStatus)
      {

        /* All these cases mean that the job is requested but not started */
        case FEE_REQ_READ:
        case FEE_REQ_NORM_WRITE:
        case FEE_REQ_IMM_WRITE:
          {

            /* Job is in pending state and their is no job requested to fls.
            Set flag  NotifyCancel for triggering notification to user */
            NotifyCancel  = FEE_SET;
            break;
          }

        /* The following cases mean that the read job is on-going */
        case FEE_PEND_PREV_READ_REQ:
        case FEE_PEND_PREV_READ_NOTIF:
          {

            if(StateDataPtr->FeeUserJobStatus == FEE_JOB_REQSTD)
            { 
    /* [cover parentID={65DDD0F0-B824-4acf-8670-5B83B01098A7}]
Set flag  NotifyCancel for triggering notification to user
(Notify cancel only if UserJobStatus is Job Requested)
Cancel the read job
[/cover] */
              /* Cancels the read job , notification to user will be triggered
              job fee_error notification function. This function is called by
              fls driver when cancel is requested */
              Fls_17_Dmu_CancelNonEraseJobs();
            }
            else
            {
              /* Their is no request sent to fls , so
              Set flag  NotifyCancel for triggering notification to user */
              NotifyCancel  = FEE_SET;
            }

            break;
          }

        /* All other pend request states
        Example: FEE_PEND_PREV_NO_REQ:
        */
        default:
          {
            break;
          }
      }
     
      /* [cover parentID={2E4DCC84-5788-4f1e-9B45-DF4D6B11F6C3}]
Is cancel notification call required?
[/cover] */
        /* Check if cancel notification call is required */
      if(NotifyCancel  == FEE_SET)
      {  
  /* [cover parentID={76226842-41D1-47d1-A7DD-5630D1F55A1C}]
Trigger the error notification implying the job is cancelled
[/cover] */
          /*call handle user job with error = FEE_CANCELto trigger only error
          notification */
          Fee_lHandleUsrJobFailure(FEE_CANCEL);

      }
              
    }

  }
#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
  else
  {
    Fee_lReportError(FEE_SID_CANCEL, FEE_E_UNINIT);
  }
#endif

  /* [cover parentID={2C015858-96DC-4466-AB3B-0913BD68009C}]
Return
[/cover] */
}
/*******************************************************************************
** TRACEABILITY: [cover parentID={226C491E-1CDC-467b-B1C7-34265C1D5390}]      **
**                                                                            **
** Syntax : MemIf_StatusType Fee_GetStatus(void)                              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID: 0x05                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  MemIf_StatusType                                        **
**                                                                            **
** Description : Service to return the status of the driver.                  **
**                                                                            **
*******************************************************************************/
/* [cover parentID={257B750D-C0C9-47d1-B1E1-641B3FB9964D}]
Fee_GetStatus
[/cover] */
MemIf_StatusType Fee_GetStatus(void)
{
  
  MemIf_StatusType   ReturnStatus;

  /* Check if the Fee_Init API is called */
  
  if(Fee_CfgPtr != NULL_PTR)
  {
    
    /* [cover parentID={63DFD354-F0AB-41f7-A591-A9D6689DAAB5}]
Update Fee status accordingly
[/cover] */
    ReturnStatus = Fee_lGetStatus();
    
  }
  else
  {
    /* [cover parentID={D174448D-7278-4e80-86C9-23521CD2EDBF}]
Set return status as Fee uinitialised (MEMIF_UNINIT)
[/cover] */
    ReturnStatus = MEMIF_UNINIT;
  }
/* [cover parentID={BD705C64-BA6E-40b4-95A4-AEB95915D59F}]
Return the status value
[/cover] */
  return(ReturnStatus);

}/*End of Fee_GetStatus */

/*******************************************************************************
** TRACEABILITY: [cover parentID={851BA7DF-094F-4a18-99EB-5961F8038283}]      **
**                                                                            **
** Syntax : MemIf_JobResultType Fee_GetJobResult(void)                        **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID: 0x06                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  MemIf_JobResultType                                     **
**                                                                            **
** Description : Service to query the result of the last accepted job issued  **
** by NVM.                                                                    **
**                                                                            **
*******************************************************************************/
/* [cover parentID={D12859D4-DC09-4009-AE0B-66AA09D02D76}]
Fee_GetJobResult
[/cover] */
MemIf_JobResultType Fee_GetJobResult(void)
{
  const Fee_StateDataType  *StateDataPtr;
  MemIf_JobResultType ReturnValue;

  /*Check for configuration pointer(Fee_CfgPtr)for null as part safety check */
  /* Check if the Fee_Init API is called */
  /* [cover parentID={BE5ECEE5-E2F8-4b33-A628-3A2ED53FADE0}]*/
#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
  if(Fee_CfgPtr != NULL_PTR)
#endif
  {
    StateDataPtr = Fee_CfgPtr->FeeStatePtr;
    ReturnValue = StateDataPtr->FeeJobResult;
  }
  /* [cover parentID={FD197E65-EE8B-493a-ADC6-6C2BFA4F2601}]
DET or safety enabled
[/cover] */
#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
  else
  {
    
   /* [cover parentID={2939037D-26A7-4b0a-A227-653F5D286757}]
Report DET error as FEE_E_UNINIT
[/cover] */
    
     /* [cover parentID={3782FDE0-A93B-4780-8567-D0FDE7BC4D93}]
Return MEMIF_JOB_FAILED
[/cover] */
     
    Fee_lReportError(FEE_SID_GETJOBRESULT, FEE_E_UNINIT);
    ReturnValue = MEMIF_JOB_FAILED;
  }

#endif
  /* [cover parentID={09E392A4-0F42-4cd7-8A98-F2E95A884302}]
Return Fee job result
[/cover] */
  return (ReturnValue);
/* [cover parentID={1D49459A-C72F-416f-89D4-8F5D33736EF8}]
Return the job result type
[/cover] */
}/*End of Fee_GetJobResult */

/*******************************************************************************
** TRACEABILITY: [cover parentID={1D45F947-1794-4611-A1D4-C4FCB2C5F847}]      **
**                                                                            **
** Syntax : Std_ReturnType Fee_InvalidateBlock(const uint16 BlockNumber)      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID: 0x07                                                           **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockNumber : Logical Block Number                      **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                                                                            **
** Description : This function shall invalidate the given logical             **
** block                                                                      **
**                                                                            **
*******************************************************************************/
/* [cover parentID={53FDE5DD-D4B5-4fe3-889B-3ED80C47E6B7}]
Fee_InvalidateBlock
[/cover] */
Std_ReturnType Fee_InvalidateBlock(const uint16 BlockNumber)
{
  
  Fee_StateDataType   *StateDataPtr;
  const Fee_BlockType *BlockPtr;
  uint16               UserBlockIndex;
  MemIf_StatusType    ReturnStatus;

  Std_ReturnType       ReturnValue;
  /* [cover parentID={08905859-5E52-4608-A637-C88C8F2D83C8}]
Return E_OK
[/cover] */
  ReturnValue = E_OK;
  /*Check Fee_CfgPtr is null if yes return E_not_ok . This done to avoid trap
  if fee_init is not called */
  
  
  /* Check if the Fee_Init API is called */
  /* [cover parentID={EC251CE2-4ABC-4b2c-8B0B-64631235D3FA}]
Is the configuration pointer NULL?
[/cover] */
  if(Fee_CfgPtr != NULL_PTR)
  {
    StateDataPtr = Fee_CfgPtr->FeeStatePtr;
    /* [cover parentID={032A4BEF-3F1A-43ed-BFE2-E359C539C84F}]
Get user block index
[/cover] */
    UserBlockIndex = Fee_lGetUsrBlockIndex(BlockNumber);
    /* [cover parentID={512DF666-A64F-44c0-8088-1BAFF548E94C}]
DET or safety enabled
[/cover] */
    /* [cover parentID={E7FBF8C4-C598-4c4f-9A02-E6F2E9073DC3}]*/
#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)

    /* [cover parentID={5C5DF49B-F830-4660-A219-6FFAE66F0A89}]
Is user block index valid?
[/cover] */
    if( UserBlockIndex == FEE_LOG_BLOCK_NOT_FOUND)
    {
     /* [cover parentID={48F1F75A-0C5E-436a-A2F0-636ECC141E4F}]
Report FEE_E_INVALID_BLOCK_NO DET
[/cover] */
      /* Block is not configured */
      Fee_lReportError(FEE_SID_INVALIDATEBLOCK, FEE_E_INVALID_BLOCK_NO);
      /* [cover parentID={0AAA8D6D-89EF-4d2a-82F7-92D6AB2B2E36}]
Return E_NOT_OK
[/cover] */
      ReturnValue = E_NOT_OK;
    }
  
    else
    {
      
      ReturnStatus = Fee_lGetStatus();
    /* [cover parentID={FDED4E44-602B-415e-8236-1CD52721E19D}]
Check for Fee status
[/cover] */
      /* [cover parentID={11F3085D-A819-43f2-8115-66E7876D5797}]
Is Fee busy in internal operations?
[/cover] */
      if(ReturnStatus == MEMIF_BUSY_INTERNAL)
      {
        /* [cover parentID={150C65F1-92E0-4029-8384-79B0B828E3A2}]
Reject the invalidation request
[/cover] */
        /* [cover parentID={0AAA8D6D-89EF-4d2a-82F7-92D6AB2B2E36}]
        Return E_NOT_OK
        [/cover] */
        ReturnValue = E_NOT_OK;
      }
    }
/* [cover parentID={E7FBF8C4-C598-4c4f-9A02-E6F2E9073DC3}]
If no errors were detected and Fee is not internally busy
[/cover] */
    if (ReturnValue != E_NOT_OK)
#endif /*End of FEE_DEV_ERROR_DETECT == STD_ON */

    {
      /* [cover parentID={8A852F26-A7B3-47c2-B4E8-AEA266A0F7FF}]
      Any pending request?
      [/cover] */
      ReturnStatus = Fee_lGetStatus();
    /* [cover parentID={8A852F26-A7B3-47c2-B4E8-AEA266A0F7FF}]
No pending request and Return Status is Idle?
[/cover] */
      /* Execute only if there is no pending request */
      if(( StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_NO_REQ ) &&
          (ReturnStatus == MEMIF_IDLE))
      {
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)

        if(Fee_CfgPtr->FeeBlockConfigPtr[UserBlockIndex].FeeUser ==
            (uint8)FEE_QUASI_STATIC_USER)
        {
          ReturnValue = E_NOT_OK;
      /* [cover parentID={589953FB-C89B-4c27-9639-A54471518253}]
DET or safety enabled
[/cover] */
#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={E0F6C690-EC5E-4434-86D3-4406D8C9930E}]
Report FEE_E_INVALIDATE_BLOCK_NO DET
[/cover] */
          Fee_lReportError(FEE_SID_INVALIDATEBLOCK, FEE_E_INVALID_BLOCK_NO);

#endif

        }
        else
#endif
        {
          /*MISRA2012_RULE_18_4_JUSTIFICATION:This warning is for the core FEE
          structures which are containing the Block and sector info and affects
          the entire FEE functionality.Changing these would increase the risk of
          major functional impact on the entire FEE code,thereby putting the
          complete functionality of FEE at risk. */
          BlockPtr = Fee_CfgPtr->FeeBlockConfigPtr + UserBlockIndex;
          /* register invalidate request */
          StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus = FEE_SET ;
          Fee_lRegisterWriteRequest(StateDataPtr->FeeReadWriteBuffer, BlockPtr);
        }
      }
      else
      {
        /* [cover parentID={589953FB-C89B-4c27-9639-A54471518253}]
        DET enabled
        [/cover] */
#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
        /* [cover parentID={E0F6C690-EC5E-4434-86D3-4406D8C9930E}]
        Report error to DET/SAFETY
        [/cover] */
        /* FEE is busy with another request; raise BUSY DET */
        if(ReturnStatus == MEMIF_BUSY)
        {
          Fee_lReportError(FEE_SID_INVALIDATEBLOCK, FEE_E_BUSY);
        }

#endif
        /* [cover parentID={0AAA8D6D-89EF-4d2a-82F7-92D6AB2B2E36}]
        Return E_NOT_OK
        [/cover] */
        ReturnValue = E_NOT_OK;
      }
    }
    /* [cover parentID={11A5BFD3-42A1-41d9-A529-62D808D10C35}]
    Return
    [/cover] */
  }
  else
  {
    /* [cover parentID={975D3BE2-0390-4d10-B7DD-03ED14113F6C}]
      Report error to DET/SAFETY
      [/cover] */
     
    /* [cover parentID={0AAA8D6D-89EF-4d2a-82F7-92D6AB2B2E36}]
      Return E_NOT_OK
     [/cover] */  
    ReturnValue = E_NOT_OK;
    
#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={975D3BE2-0390-4d10-B7DD-03ED14113F6C}]
Report FEE_E_UNINIT DET
[/cover] */
    Fee_lReportError(FEE_SID_INVALIDATEBLOCK, FEE_E_UNINIT);
#endif
  }

  return(ReturnValue);

}/*End of Fee_InvalidateBlock */

/*******************************************************************************
** TRACEABILITY:                                                              **
**                                                                            **
** Syntax : Std_ReturnType Fee_EraseImmediateBlock( const uint16 BlockNumber )**
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID: 0x09                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockNumber - Logical Block Number                      **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                                                                            **
** Description : Service to erase an immediate logical block.                 **
** Since double-sector algorithm is used with threshold limit                 **
** for triggering GC, immediate block's write requests during GC can be       **
** accommodated within the pre-erased threshold area of the active FEE sector.**
** Hence, this API is implemented as a dummy function returning E_NOT_OK.     **
**                                                                            **
*******************************************************************************/
/* [cover parentID={B5C7D98C-B3CA-4ccb-8205-08765E4FEC01}][/cover]*/
Std_ReturnType Fee_EraseImmediateBlock(const uint16 BlockNumber)
{
  UNUSED_PARAMETER (BlockNumber);
  /* [cover parentID={32D1C713-6EBC-40ab-9BE1-E3A9FE9A7DF1}]
Set Return flag as E_NOT_OK
[/cover] */
  return(E_NOT_OK);
  /* [cover parentID={CBDA1633-EB6D-4568-B28B-4EFB2FF1388D}]
Return
[/cover] */
}


#if (FEE_INITCHECK_API == STD_ON)

/******************************************************************************
** TRACEABILITY:                                                             **
**                                                                           **
**                                                                           **
** Syntax : Std_ReturnType Fee_17_InitCheck(const Fee_ConfigType             **
**                                           * const ConfigPtr)              **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID: 0x30                                                          **
**                                                                           **
** Sync/Async:  Synchronous                                                  **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) : ConfigPtr - Pointer to the selected configuration set   **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  Std_ReturnType                                         **
**                    E_OK :  Module is initialized properly.                **
**                    E_NOT_OK : Module is not initialized properly due to   **
**                               1) Fee_CfgPtr is NULL                       **
**                               2) Fee_CfgPtr is not matching with given    **
**                                  ConfigPtr.                               **
**                               3) Fee is not yet completely  initialized   **
** Description : Service to check module Initialization status. if module is **
**               not initialized properly  it will return E_NOT_OK           **
******************************************************************************/

/* [cover parentID={49FACB51-3230-4929-A415-2FB4E3231C33}]
Fee_17_InitCheck
[/cover] */
/*[cover parentID={F75EA151-84A9-44e8-A44B-ACE43C4B809C}] [/cover] */
Std_ReturnType Fee_17_InitCheck(const Fee_ConfigType * const ConfigPtr )
{
  
  const Fee_StateDataType   *StateDataPtr;
  Std_ReturnType      RetVal;
   
  RetVal = E_NOT_OK;
  
  /* Check if given ConfigPtr pointer is null */
  if(ConfigPtr != NULL_PTR)
  {
    /*Check if module is initialize properly*/
    if((Fee_CfgPtr != NULL_PTR) && (Fee_CfgPtr == ConfigPtr))
    {
      StateDataPtr = Fee_CfgPtr->FeeStatePtr;
        
      /*Check if FeeStatePtr and FeeBlockConfigPtr is not null */
      if((StateDataPtr!= NULL_PTR) &&
          (Fee_CfgPtr->FeeBlockConfigPtr != NULL_PTR ))
      { 
       /* [cover parentID={EDD76789-ED56-4235-A235-F8D5372C5912}]
Check if  state variable CRC is same as the CRC at initialization?
[/cover] */
/* [cover parentID={EC6BC55F-7761-475d-86DD-6E188D93BF71}]
Calculate the CRC of state structure variable
[/cover] */
        /*Check if state variable CRC is matching with state variable 
        initialization CRC*/
        if(Fee_DataStrcutInitCrc == Fee_lCalDataStructCrc())
        {
           RetVal = E_OK; 
        }

      }
    
    }

  }

  return(RetVal);
  /* [cover parentID={74824B0A-B019-46df-82A0-0DE29ABAD076}]
Return
[/cover] */
} /*End of Fee_17_InitCheck */

/******************************************************************************
** TRACEABILITY:                                                             **
**                                                                           **
**                                                                           **
** Syntax : LOCAL_INLINE uint32 Fee_lCalDataStructCrc(void)                  **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID:                                                               **
**                                                                           **
** Sync/Async:  Synchronous                                                  **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) : ConfigPtr - Pointer to the selected configuration set   **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  uint32                                                 **
**                    CRC of Fee state variable data structure               **
** Description : Service to calculate CRC for fee state variable data        **
**               structure                                                   **
******************************************************************************/
/*[cover parentID={FF96A077-065F-419a-8271-9A7EBABD3682}][/cover]*/
LOCAL_INLINE  uint32 Fee_lCalDataStructCrc(void) 
{
  uint32              FeeDataStructSize;
  uint32              Index;
  uint32              Crc32;  
  const uint8        *FeeDataStructPtr;             
   
  /*Get the szie of Fee state variable data structure */
  FeeDataStructSize  = sizeof(Fee_StateDataType);
  /*Set the initial CRC value as 0*/
  Crc32 = FEE_RESET;

  FeeDataStructPtr = (uint8*)Fee_CfgPtr->FeeStatePtr;
        
  /*CRC32 calculation byte-wise*/
  for(Index = FEE_RESET; Index < FeeDataStructSize; Index++)
  {
    /*MISRA2012_RULE_4_6_JUSTIFICATION: Basic numerical type - int/
    unsigned int is used while invoking compiler intrinsic functions. 
    These compiler intrinsic functions are implemented specific to 
    tricore.Hence to align with compiler declaration use of unsigned int
    is mandatory. */
     Crc32 = CRC32B(Crc32, FeeDataStructPtr[Index]);
  }
  
  return(Crc32);
  
}

#endif

/* Memory Map of the FEE Code */
#define FEE_STOP_SEC_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"


#define FEE_START_SEC_JOBENDNOTIF_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"
/*CYCLOMATIC_Fee_JobEndNotification_JUSTIFICATION:
Fee_JobEndNotification is called when the Fls module has successfully completed
 the requested job.Operations performed here are logically decomposed into local
 functions. Further decomposition might lead to
 maintenance/ readability concerns.
*/
/*******************************************************************************
** TRACEABILITY: [cover parentID={E921028D-82B0-4ac6-9AAB-2553676A53FC}]      **
**                                                                            **
** Syntax : void Fee_JobEndNotification(void)                                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID: 0x10                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : Service to report to FEE module the successful end of an     **
** asynchronous operation performed by the underlying flash driver.       **
*******************************************************************************/
void Fee_JobEndNotification(void)
{
  Fee_StateDataType  *StateDataPtr;
  Fls_17_Dmu_Job_Type Job;

#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
  /* Check if the Fee_Init API is called */
  if(Fee_CfgPtr != NULL_PTR)
#endif
  {

    StateDataPtr = Fee_CfgPtr->FeeStatePtr;
    /* [cover parentID={B3E5D775-72A1-4bcd-BDAE-4A78BFBC18BC},
    {59E623D3-CB36-4c9c-A9A9-D28CA4495A23}]
Get the FLS job that raised the notification
[/cover] */
    Job = Fls_17_Dmu_GetNotifCaller();
  /* [cover parentID={041587D2-B988-4bc3-9B98-0B11B23D483C}]
Is it internal job?
[/cover] */
    if(Job == StateDataPtr->FeeIntrJob)
    {
      /* If job is internal job */
    /* [cover parentID={AF3250D3-AA49-4950-AD26-EEA51428ABB9}]
Reset the pending request status and set the Fee job result to MEMIF_JOB_OK
FeePendReqInfo.GetPrevCopy = FEE_ZERO
[/cover] */
      /* [cover parentID={041587D2-B988-4bc3-9B98-0B11B23D483C}]*/
      StateDataPtr->FeeIntrJobStatus = FEE_JOB_DONE;
      StateDataPtr->FeeIntrJobResult = FEE_JOB_PASS;
      StateDataPtr->FeeIntrJob = FEE_NO_JOB;
    }
  /* [cover parentID={27BCAA74-DD8C-4b18-BEAE-993FF9E1F6B4}]
Is it NVM Job?
[/cover] */
    else if( Fee_lGetUserJob(StateDataPtr->FeePendReqStatus) == Job)
    {
      /* if job is user job */
      StateDataPtr->FeeUserJobStatus = FEE_JOB_IDLE;
      StateDataPtr->FeeUserJobResult = FEE_JOB_PASS;
    /* [cover parentID={A96EAB68-61B5-4230-B9DC-E56735E5BDBC}]
Is it read job?
[/cover] */
      
      if(Job == FEE_READ_JOB)
      {
        Fee_lHandleReadJobEndNotification();
      }
      /* FLS_WRITE_JOB: Handling last page write is done as part of
       Write State Machine itself */
    }/* End of User Job Handling */
    
    /* [cover parentID={27BCAA74-DD8C-4b18-BEAE-993FF9E1F6B4}]*/
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  /* [cover parentID={D9A935CB-8E11-4693-8466-8FC0D198370A}]
Is it QS job?
[/cover] */
    
    else if(StateDataPtr->FeeQsJob != FEE_NO_JOB)
    {
      /* reset job status */
      StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
      if((StateDataPtr->FeeQsJob == FEE_READ_JOB) ||
         (StateDataPtr->FeeQsJob == FEE_REPAIR_JOB))
      {
        /* do handling only for read job */
        Fee_lHandleQsJobSuccess();
      }
    }
#endif
    else
    {
      /* do nothing */
    }
    
  }
#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
  else
  {

    Fee_lReportError(FEE_SID_JOBENDNOTIF, FEE_E_UNINIT);


  }
#endif
  /* [cover parentID={260D257B-9490-4d7f-B1B7-7FA08BFFD26D}]
Return
[/cover] */

}/*End of Fee_JobEndNotification */
#define FEE_STOP_SEC_JOBENDNOTIF_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safe gaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#define FEE_START_SEC_JOBERRNOTIF_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safe gaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"

/*CYCLOMATIC_Fee_JobErrorNotification_JUSTIFICATION:
Fee_JobErrorNotification is called when the Fls module has encounter error in
 the requested job.Operations performed here are logically decomposed into
 local functions. IMPORTANT: This will be fixed for 1.0.0 beta
*/

/*******************************************************************************
** TRACEABILITY: [cover parentID={AA095DA4-6739-4654-BDB4-BEEA3B44ECA7}]      **
**                                                                            **
** Syntax : void Fee_JobErrorNotification(void)                               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID: 0x11                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Service to report to FEE module the failure of an            **
** asynchronous operation performed by the underlying flash driver.           **
*******************************************************************************/
/* [cover parentID={9870766D-AAE4-46f4-8DC3-CF8DB4AD87EB}]
Fee_JobErrorNotification
[/cover] */
void Fee_JobErrorNotification(void)
{
  /* [cover parentID={1DD0346F-7BB3-45d9-AC1D-9DB28C979CA8}]*/
  Fee_StateDataType  *StateDataPtr;
  Fls_17_Dmu_Job_Type Job;

#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
  /* Check if the Fee_Init API is called */
  if(Fee_CfgPtr != NULL_PTR)
#endif
  {  /* [cover parentID={A5487785-AF69-4e3b-9F91-54359044A202}]
     Get the FLS job that raised the notification
     [/cover] */
    /* [cover parentID={9870766D-AAE4-46f4-8DC3-CF8DB4AD87EB}]*/
    StateDataPtr = Fee_CfgPtr->FeeStatePtr;
    Job = Fls_17_Dmu_GetNotifCaller();
    if(Job == FEE_CANCEL_JOB)
    {
      Fee_lHandleCancelNotification();
    }
    else if(Job == StateDataPtr->FeeIntrJob)
    {
      /* if job is internal job */
      StateDataPtr->FeeIntrJobStatus = FEE_JOB_DONE;
      StateDataPtr->FeeIntrJobResult = FEE_JOB_FAIL;
      StateDataPtr->FeeIntrJob = FEE_NO_JOB;
    }
    else if( Job == Fee_lGetUserJob(StateDataPtr->FeePendReqStatus))
    {
       /* Internal Write activity has failed */
      if( StateDataPtr->FeePendReqStatus == FEE_PEND_INTR_COMPARE)
      {
         Fee_lHandleWriteFail();
      }
      /* User Write / Read activity has failed */
      else
      {
        Fee_lHandleUsrJobErrorNotification(Job);
      }
    } /* End of User Job */
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
    else if(StateDataPtr->FeeQsJob != FEE_NO_JOB)
    {
      /* Call the Fee_lHandleQsJobFailure with  (~FEE_CANCEL) to notify
      user about failed of job*/
      Fee_lHandleQsJobFailure((~FEE_CANCEL));
    }
#endif
    else
    {
      /* do nothing, in case if FLS is used as stand alone and this
       notification function being used */
    }
    
  }
  /* [cover parentID={1DD0346F-7BB3-45d9-AC1D-9DB28C979CA8}]
DET or safety is enabled
[/cover] */
#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
  else
  {  
    /* [cover parentID={872B3E91-55B6-4eac-963B-F400E12DF732}]
Report DET error as FEE_E_UNINIT
[/cover] */
    Fee_lReportError(FEE_SID_JOBERRORNOTIF, FEE_E_UNINIT);

  }
#endif
  /*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline. */
}/*End of Fee_JobErrorNotification */
#define FEE_STOP_SEC_JOBERRNOTIF_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#define FEE_START_SEC_ILLEGALNOTIF_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"

/*******************************************************************************
** Syntax : void Fee_17_IllegalStateNotification(void)                        **
**                                                                            **
** Traceability   : [cover parentID={32EEA8A2-7EB6-459a-9B3B-761D4C673810}]   **
**                                                                            **
** Service ID: 0x24                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : This routine shall be called by the underlying flash         **
**                  driver when it reaches the illegal state                  **
*******************************************************************************/
/* [cover parentID={5B7ED9EA-E19F-4c18-813F-6EAACC6E85F6}]
Fee_17_IllegalStateNotification
[/cover] */
void Fee_17_IllegalStateNotification(void)
{
  /* [cover parentID={5B7ED9EA-E19F-4c18-813F-6EAACC6E85F6}]*/
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  const Fee_StateDataType   *StateDataPtr;
#endif

/* [cover parentID={58B938B8-38DF-4a9d-ADBD-D089D462AAE6}]
FEE_SAFETY_ENABLE is enabled
[/cover] */
#if (FEE_SAFETY_ENABLE == STD_ON)
  if(Fee_CfgPtr != NULL_PTR)
#endif
  {

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
    StateDataPtr = Fee_CfgPtr->FeeStatePtr;

    if(StateDataPtr->FeeQsJob == FEE_NO_JOB)
    {
      if(Fee_CfgPtr->FeeNvmIllegalStateNotification != NULL_PTR)
      {
        Fee_CfgPtr->FeeNvmIllegalStateNotification();
      }
    }
    else
    {
      /* QS illegal notification will be called */
      if(Fee_CfgPtr->FeeQsIllegalStateNotification != NULL_PTR)
      {
        Fee_CfgPtr->FeeQsIllegalStateNotification();
      }
    }

#else
    if(Fee_CfgPtr->FeeNvmIllegalStateNotification != NULL_PTR)
    {

      /* Call the Notification function */
      Fee_CfgPtr->FeeNvmIllegalStateNotification();
    }
#endif
  }
#if (FEE_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={34FD9AE4-8FE3-433d-8EA0-BBBC79DB10B5}]
Report error FEE_E_UNINIT
[/cover] */
    Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                           FEE_SID_ILLEGALSTATENOTIFICATION, FEE_E_UNINIT);
  }
#endif
  /*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline. */
}/*End of Fee_17_IllegalStateNotification */
#define FEE_STOP_SEC_ILLEGALNOTIF_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safe gaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* Memory Map of the FEE Code */
#define FEE_START_SEC_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safe gaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"



#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

#if (FEE_GET_CYCLE_COUNT_API == STD_ON)
/*******************************************************************************
** Syntax : Std_ReturnType Fee_17_GetCycleCount(const uint16 BlockNumber,     **
**                                              uint32 * const CountPtr)      **
**                                                                            **
** Traceability   : [cover parentID={CA460132-35A7-4725-933B-DBF822A5B00F}]   **
**                                                                            **
** Service ID:    0x20                                                        **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in):  BlockNumber - Logical Block Number                       **
**                                                                            **
** Parameters (out) :  CountPtr - Pointer to the variable to which the Erase  **
**                               cycle count is to be updated                 **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                    E_OK: Block cycle count read successfully               **
**                    E_NOT_OK: Block cycle count can not be read due to      **
**                              1) Cache is not yet updated or                **
**                              2) Flash driver is busy with other request or **
**                              3) Garbage collection is ongoing              **
**                                                                            **
** Description : When called with BlockNumber = 0, this routine delivers the  **
** FEE sector erase cycle count. When called with a configured BlockNumber,   **
** the write cycle count of the given block is returned.                      **
**                                                                            **
*******************************************************************************/
Std_ReturnType Fee_17_GetCycleCount(const uint16 BlockNumber,
                                    uint32 * const CountPtr)
{
  uint32               RawCnt;
  const Fee_StateDataType   *StateDataPtr;
  uint16               BlockIndex;
  Std_ReturnType       ReturnValue;
  MemIf_StatusType     Status;

  ReturnValue = E_NOT_OK;
#if (FEE_SAFETY_ENABLE == STD_ON)
  /*Check for configuration pointer(Fee_CfgPtr)for null as part safety check */
  if((Fee_CfgPtr != NULL_PTR) && (CountPtr != NULL_PTR))

#endif
  {
    /* [cover parentID={066C5C76-67C7-4ead-A465-1629BD66AD41},
    {EA4A7BB3-1CF8-4396-B891-C03D8ED2CDDB}]
    [/cover] */
    /* if the cache is not updated, or if GC is on going, return.
     else, proceed with Get block cycle count */
    /* [cover parentID={00DE57D6-FE1C-47aa-94F1-5A98A2F933A9}]
    Check for cache and GC status
    [/cover] */
    /* [cover parentID={3E4D0D11-A15E-4fc5-9EF9-2F3D39340B9F}]
    Check for valid block index
    [/cover] */
    /* [cover parentID={1BD5B167-F038-4142-BA3D-9C4C1ACE7849}]
    Is block index valid?
    [/cover] */
    /* [cover parentID={E0D91688-3A24-4c0e-838F-93CC2A6C3034}]
    Read block cycle count
    [/cover] */
    /* [cover parentID={C471858B-5677-4eec-8C8D-B609771A9937}]
    Check if block cycle count was read
    [/cover] */

    StateDataPtr = Fee_CfgPtr->FeeStatePtr;
    Status = Fee_lGetStatus();
    /* [cover parentID={00DE57D6-FE1C-47aa-94F1-5A98A2F933A9}]
Check for cache and GC status
[/cover] */ 
/* [cover parentID={066C5C76-67C7-4ead-A465-1629BD66AD41}]
Is the module state idle?
[/cover] */
    if (Status == MEMIF_IDLE)
    {
      if((StateDataPtr->FeeCacheState == FEE_CACHE_UPDATE_COMPLETE) &&
         (StateDataPtr->FeeGcState == FEE_GC_IDLE))
      {
        /* [cover parentID={222C72BC-61FF-4369-A797-DFD73214ADDE}]
Is block number zero?
[/cover] */
        if (BlockNumber == FEE_STATE_PAGE_NUMBER)
        {
          /* Erase Cycle count is derived from the latest state count
           State Count is incremented at every state page write.
          At the start / After preparation of DFLASH, the state count is 3.
          Since then the state count is incremented twice during GC
          (once for VALID SP programming and again for ERASED SP programming).
          Hence the Erase Cycle Count shall be (StateCount - 3)/2 */
         /* [cover parentID={75DEB242-F51C-46cd-9FA5-D93BF5CA2A8E}]
Calculate erase cycle count
[/cover] */
          RawCnt = ((StateDataPtr->FeeStateCount - FEE_THREE) >> FEE_ONE);
          *CountPtr = RawCnt;
      /* [cover parentID={EF577DD8-E8A2-4b24-B74C-1F3BD936E082}]
Return E_OK
[/cover] */
          ReturnValue = E_OK;
        }
        /* [cover parentID={222C72BC-61FF-4369-A797-DFD73214ADDE}]
        Is block number zero?
        [/cover] */
        /* [cover parentID={75DEB242-F51C-46cd-9FA5-D93BF5CA2A8E}]
        [/cover] */
        /* [cover parentID={7397E5C1-5866-4ebb-B366-7652FB3B9A87}]
        [/cover] */
        else
        {  
        /* [cover parentID={7397E5C1-5866-4ebb-B366-7652FB3B9A87}]
Get index of the block info stored in cache
[/cover] */
          /* Get index of the block info stored in cache */
          BlockIndex = Fee_lGetUsrBlockIndex(BlockNumber);
      /* [cover parentID={3E4D0D11-A15E-4fc5-9EF9-2F3D39340B9F}]
Check for valid block index
[/cover] */
/* [cover parentID={1BD5B167-F038-4142-BA3D-9C4C1ACE7849}]
Is block index valid?
[/cover] */

          if(BlockIndex != FEE_LOG_BLOCK_NOT_FOUND)
          {
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
            if(Fee_CfgPtr->FeeBlockConfigPtr[BlockIndex].FeeUser ==
                (uint8)FEE_QUASI_STATIC_USER)
            {
              ReturnValue = E_NOT_OK;
        
#if (FEE_SAFETY_ENABLE == STD_ON)
              Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                                   FEE_SID_GETCYCLECOUNT,FEE_E_INVALID_BLOCK_NO);
#endif
            }
            else
#endif
            {
              /* [cover parentID={E0D91688-3A24-4c0e-838F-93CC2A6C3034}]
Read block cycle count
[/cover] */
              /* Read block cycle count */
              RawCnt = Fee_lGetBlkCycleCount(BlockIndex);
        /* [cover parentID={C471858B-5677-4eec-8C8D-B609771A9937}]
Check if block cycle count was read
[/cover] */
/* [cover parentID={F7CB7631-7C7D-4c7a-A556-B66C41A663C6}]
Is read performed and was successful ?
[/cover] */
              /* Check if the read was performed */
              if(RawCnt != FEE_32_BIT_ALL_ONES)
              {
          /* [cover parentID={2F9059CE-8C6C-4c64-99FE-5B9567CC56D6}]
Return the block cycle counter via countptr
Return E_OK
[/cover] */
                *CountPtr = RawCnt;
                ReturnValue = E_OK;
                /* [cover parentID={EF577DD8-E8A2-4b24-B74C-1F3BD936E082}]
                Return E_OK
                [/cover] */

              }
            }
          }
  /* [cover parentID={E494297C-E13F-43fc-BDD4-FA7C6BAC86C2}]
Safety error is enabled
[/cover] */
    
#if (FEE_SAFETY_ENABLE == STD_ON)
          else
          {
      /* [cover parentID={DF9E2968-4B59-4d87-A408-B2B81AF8DDB3}]
Report safety error as FEE_E_INVALID_BLOCK_NO
[/cover] */  
            Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                                 FEE_SID_GETCYCLECOUNT,FEE_E_INVALID_BLOCK_NO);
          }
#endif


      
        } /* end of if ( BlockNumber == FEE_ZERO ) */
      }/* end of if FEE_CACHE_UPDATE_COMPLETE*/
    } /* end of if the module was idle*/  

#if (FEE_SAFETY_ENABLE == STD_ON)
    else
    {
       if(Status == MEMIF_BUSY )
       { 
        /* [cover parentID={435AF9EA-B66D-4fef-A54F-A1F53DD0B9F0}]
Report error to FEE_SID_GETCYCLECOUNT and FEE_E_BUSY
[/cover] */
          Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                                 FEE_SID_GETCYCLECOUNT, FEE_E_BUSY);
       }
    }

#endif

  }
/* [cover parentID={C5A6D713-AFFC-409f-B213-30381AD138CC}]
Safety error is enabled
[/cover] */
#if (FEE_SAFETY_ENABLE == STD_ON)
  else
  {

    if(Fee_CfgPtr == NULL_PTR)
    {
      /* [cover parentID={1BF7F81D-3FDD-46be-B948-C9932D669042}]
Report safety error as FEE_E_UNINIT 
[/cover] */
      Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                             FEE_SID_GETCYCLECOUNT, FEE_E_UNINIT);
    }
    else
    {
      /* [cover parentID={A801042E-36A0-475a-B9A6-4A87F67211E1}]
Report safety error as FEE_E_PARAM_POINTER
[/cover] */
      Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                             FEE_SID_GETCYCLECOUNT, FEE_E_PARAM_POINTER);
    }
     /* [cover parentID={8F5D3017-260D-43f6-9DAD-699DE19349E9}]
Set return value as E_NOT_OK
[/cover] */
    ReturnValue = E_NOT_OK;
  }
#endif
/* [cover parentID={F0094B24-7E3F-416a-81DB-690C29CF0DF5}]
Return
[/cover] */
  return(ReturnValue);

}/*End of Fee_GetCycleCount */
#endif
/* End of FEE_GET_CYCLE_COUNT_API == STD_ON */

/******************************************************************************
** Syntax : void Fee_17_EnableGcStart( void )                                **
**                                                                           **
** Traceability   : [cover parentID={2CE2C6D5-740D-450d-9A6C-CD3FFCEE43B1}]  **
**                                                                           **
** Service ID:     0x21                                                      **
**                                                                           **
** Sync/Async:  Synchronous                                                  **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) :  None                                                   **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  void                                                   **
**                                                                           **
** Description : This service allows enabling the trigger of GC, if GC was   **
** disabled earlier by calling the API Fee_17_DisableGcStart. After this API **
** is called,if the sector is filled up to the threshold level and additional**
** write / invalidate request is issued, then GC will be initiated.          **
**                                                                           **
******************************************************************************/
/* [cover parentID={0459E2CC-247D-4693-B08D-A503D87E4DCA}]
Fee_17_EnableGcStart
[/cover] */
void Fee_17_EnableGcStart(void)
{
  
  Fee_StateDataType  *StateDataPtr;
/* [cover parentID={ADE93B08-FF37-464a-BFB7-1260BE7E629A}]
Safety error is enabled
[/cover] */
#if (FEE_SAFETY_ENABLE == STD_ON)
  /*Check for configuration pointer(Fee_CfgPtr)for null as part safety check */
/* [cover parentID={3595E30F-067D-458c-B731-E407B13DA9A3}]
Is configuration pointer NULL?
[/cover] */
  if(Fee_CfgPtr != NULL_PTR)
#endif
  {
    StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /* [cover parentID={B9BEB9C6-ACD9-474a-A0F1-781C9EC20873}]
Enable the GC start functionality
[/cover] */

    StateDataPtr->FeeDisableGCStart = (boolean)FALSE;
  }
#if(FEE_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={0C13789A-C15D-4b72-B987-040CA7CCB813}]
Report error as FEE_E_UNINIT
[/cover] */
    Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                           FEE_SID_ENABLEGCSTART, FEE_E_UNINIT);
  }
#endif
}

/*******************************************************************************
** Syntax : void Fee_17_DisableGcStart( void )                                **
**                                                                            **
** Traceability   : [cover parentID={36D8B89D-6D66-4d21-B473-9731A9FDB6A1}]   **
**                                                                            **
** Service ID:      0x22                                                      **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : This API prevents the GC from being started in case the      **
** threshold is crossed in the active FEE sector. This API does not stop an   **
** ongoing GC but only prevents the GC from being triggered by the            **
** Write/Invalidate request issued by the user.                               **
** Note: This API will disable the GC from starting only if,                  **
** 1. GC is not ongoing                                                       **
** 2. Initialization activities are complete (i.e. the state pages are read   **
** and the GC state is determined)                                            **
**                                                                            **
*******************************************************************************/
/* [cover parentID={AB6DB1F5-CD73-4523-81DE-7D95DF009FCB}]
Fee_17_DisableGcStart
[/cover] */
void Fee_17_DisableGcStart(void)
{
  
  Fee_StateDataType  *StateDataPtr;
/* [cover parentID={5A355946-411E-44bc-A97B-E7B5FED152BE}]
Safety error is enabled
[/cover] */
#if (FEE_SAFETY_ENABLE == STD_ON)
  /*Check for configuration pointer(Fee_CfgPtr)for null as part safety check */
  if(Fee_CfgPtr != NULL_PTR)
#endif
  {
    StateDataPtr = Fee_CfgPtr->FeeStatePtr;
    /* Check if InitGC is COMPLETE */
   /* [cover parentID={67C5A6D4-7610-4679-A8BC-49105171E8EC}]
Check for GC init state
[/cover] */
    if(StateDataPtr->FeeInitGCState == FEE_INITGC_COMPLETE)
    {
      /* [cover parentID={78FC3E5F-7999-43b5-AFBC-D14FA2225FCE}]
Check if GC is idle
[/cover] */
      /* Check if the GC is not started (= IDLE) */
      /* [cover parentID={9F8B0BCF-713E-4691-B403-F7BA77E711C6}]
Check for GC state
[/cover] */

      if(StateDataPtr->FeeGcState == FEE_GC_IDLE)
      {
        /* [cover parentID={4C4E1F37-5052-4840-8EDF-0F19DB915E39}]
Disable GC start functionality
[/cover] */
        /* Disable the GC start functionality */
        StateDataPtr->FeeDisableGCStart = (boolean)TRUE;
      }
    }
  }
  
#if (FEE_SAFETY_ENABLE == STD_ON)
  else
  {  
/* [cover parentID={342CE27A-26A2-442f-B305-17905172F157}]
Report safety error as FEE_E_UNINIT
[/cover] */
    Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                           FEE_SID_DISABLEGCSTART, FEE_E_UNINIT);
  }
#endif
/* [cover parentID={9C48E59F-EAF7-4827-A2CA-565730D5B4FC}]
Return
[/cover] */
}/*End of Fee_17_DisableGcStart*/
#endif

/*CYCLOMATIC_Fee_MainFunction_JUSTIFICATION: Fee_MainFunction is the main
scheduling function, depending on states the corresponding function would be
called accordingly, it is implemented through switch case which already
maintains good code readability.
*/
/*******************************************************************************
** TRACEABILITY: [cover parentID={6DA9A0A4-6B27-454f-B64A-FC27DD7DFCF2}]      **
**                                                                            **
** Syntax : void Fee_MainFunction(void)                                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID: 0x12                                                           **
**                                                                            **
** Sync/Async:  NA                                                            **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : The scheduled function helps to drive asynchronous jobs-     **
** read, write, erase and internal management jobs like garbage collection.   **
**                                                                            **
*******************************************************************************/
/* [cover parentID={9DE37884-A9F6-4342-AF5C-CDD9507959A7},
{AAB72093-60CA-413e-9DFC-4037C25368F8}]
Fee_MainFunction
[/cover] */
void Fee_MainFunction(void)
{
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
  const Fee_StateDataType  *StateDataPtr;
#else
  Fee_StateDataType  *StateDataPtr;
#endif
  /* [cover parentID={09B3C16C-44DF-49c3-A26D-C308340D5BB0}]
Is ConfigPtr non-null?
[/cover] */
  if(Fee_CfgPtr != NULL_PTR)
  {
    StateDataPtr = Fee_CfgPtr->FeeStatePtr;

    /* 1. Determine & switch Main Job,if required, based on input conditions */
    Fee_lDecideMainJob();

    /* 2. Execute the Main Job */
    switch(StateDataPtr->FeeMainJob)
    {
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
      case FEE_MAIN_INITGC:
        {
          if(StateDataPtr->FeeIntrJobStatus != FEE_JOB_REQSTD)
          {
            Fee_lInitGC();
          }
          break;
        }
#endif
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
      case FEE_MAIN_INITQS:
        {
          if(StateDataPtr->FeeQsJobStatus != FEE_JOB_REQSTD)
          {
            if(StateDataPtr->FeeQsBlockVirginCount == FEE_NUM_QUASI_BLOCKS)
            {
              Fee_lHandleQsVirginBlocks();
            }
            else
            {
              Fee_lQsIDSM();
            }

          }
          break;
        }
#endif
      case FEE_MAIN_CACHEUPDATE:
        {
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
          Fee_lUpdateCache();
#else
          StateDataPtr->FeeCacheState = FEE_CACHE_IDLE_QS;
#endif
          break;
        }

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)

      case FEE_MAIN_QS:
        {
          if(StateDataPtr->FeeQsJobStatus != FEE_JOB_REQSTD)
          {
            Fee_lMainQs();
          }
          break;
        }
#endif
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
      case FEE_MAIN_WRITE:
        {
          if(StateDataPtr->FeeUserJobStatus != FEE_JOB_REQSTD)
          {
            Fee_lLocalWrite();
          }
          break;
        }

      case FEE_MAIN_READ:
        {
          if(StateDataPtr->FeeUserJobStatus != FEE_JOB_REQSTD)
          {
            /* [cover parentID={BF603D11-73F7-45d2-A05D-E780561CCBC9}]
Call local read
[/cover] */
            Fee_lLocalRead();
          }
          break;
        }

      case FEE_MAIN_GC:
        {
          Fee_lMainGCHdlr();
          break;
        }
#endif
      /*case FEE_MAIN_NONE, FEE_MAIN_UNINIT belong here */
      default:
        {
          break;
        }
    }
  }
  /* [cover parentID={AB625C41-29D4-4b63-91EC-0646C75E58AB}]
Return
[/cover] */

}/*  End of Fee_MainFunction */


#if (FEE_GET_PREV_DATA_API == STD_ON)
/*******************************************************************************
** Syntax : Std_ReturnType Fee_17_GetPrevData(const uint16 BlockNumber,       **
**                                            const uint16 BlockOffset,       **
**                                            uint8 *const DataBufferPtr,     **
**                                            const uint16 Length)            **
**                                                                            **
** Traceability   : [cover parentID={FD1EBB5B-3408-414d-8872-281BC6442041}]   **
**                                                                            **
** Service ID: 0x23                                                           **
**                                                                            **
** Sync/Async: Asynchronous                                                   **
**                                                                            **
** Reentrancy: Non reentrant                                                  **
**                                                                            **
** Parameters (in) :  BlockNumber - Logical Block Number                      **
**                    BlockOffset - Read address offset inside the block      **
**                    Length - Number of bytes to read                        **
**                                                                            **
** Parameters (out):  DataBufferPtr - Pointer to data buffer                  **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                    E_OK : Request accepted                                 **
**                    E_NOT_OK : Request is not accepted accepted due to      **
**                    1) FEE module is busy in servicing other request. or    **
**                    2) Requested block number is not a NVM data block       **
**Description : The user can call this API to read one occurrence old data of **
**the given block. This API accepts the request and updates the FEE internal  **
**variables. However the actual reading of the data is done by the            **
**Fee_MainFunction after the cache is built.                                  **
**                                                                            **
*******************************************************************************/
/* [cover parentID={099DBE0A-0F91-49a8-9D6D-081A0C24CEB3}]
Fee_17_GetPrevData
[/cover] */
Std_ReturnType Fee_17_GetPrevData(const uint16 BlockNumber,
                                  const uint16 BlockOffset,
                                  uint8 *const DataBufferPtr,
                                  const uint16 Length)
{
  /* [cover parentID={099DBE0A-0F91-49a8-9D6D-081A0C24CEB3}]*/
  Std_ReturnType        RetVal;

#if((FEE_SAFETY_ENABLE == STD_ON) || \
(FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY))
  uint16               BlkIdx;

#endif

#if(FEE_SAFETY_ENABLE == STD_ON)
  uint32               BlkSize = FEE_RESET;
  /*Check for configuration pointer(Fee_CfgPtr)for null as part safety check */
  if((Fee_CfgPtr != NULL_PTR) && (DataBufferPtr != NULL_PTR))
#endif
  {

    /* [cover parentID={14D8388C-3115-4aa5-9C66-A64D6B220D96}]

    [/cover] */

#if((FEE_SAFETY_ENABLE == STD_ON) || \
(FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY))
    /*Check if block is configured and given block number is not qs block*/
    BlkIdx = Fee_lGetUsrBlockIndex(BlockNumber);
#endif
     /* [cover parentID={438B5AC6-DAB6-48f5-B667-34334D1E862C}]
Check safety errors
[/cover] */
#if (FEE_SAFETY_ENABLE == STD_ON)
    if(BlkIdx != FEE_LOG_BLOCK_NOT_FOUND)
    {
      BlkSize = Fee_CfgPtr->FeeBlockConfigPtr[BlkIdx].Size;
    }
  /* [cover parentID={87FA473A-5986-4cf2-827B-D0DB2C0C6136}]
Log block not found?
[/cover] */
    if(BlkIdx == FEE_LOG_BLOCK_NOT_FOUND)
    {
      RetVal = E_NOT_OK;
    /* [cover parentID={A8D87388-ED6C-4e08-B3E9-F5F3736AA91A}]
Report safety error as FEE_E_INVALID_BLOCK_NO
[/cover] */
      Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                             FEE_SID_GETPREVDATA, FEE_E_INVALID_BLOCK_NO);
    }
    else if(BlockOffset >= BlkSize)
    {
      RetVal = E_NOT_OK;
    /* [cover parentID={E33169E2-5B89-4c56-B991-C05852FB5A7D}]
Report safety error as FEE_E_INVALID_BLOCK_OFS
[/cover] */
      Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                             FEE_SID_GETPREVDATA, FEE_E_INVALID_BLOCK_OFS);
    }
    /* Check if the Length (from the given offset) is valid */
    else if ( ((uint32)BlockOffset + Length) > BlkSize )
    {
      /* [cover parentID={88CE8E63-B96F-40f9-8069-FB585A6C1FF9}]
Report error as FEE_E_INVALID_BLOCK_LEN
[/cover] */
      RetVal = E_NOT_OK;
      Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                             FEE_SID_GETPREVDATA, FEE_E_INVALID_BLOCK_LEN);

    }
    else
#endif
    {
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  

      if(Fee_CfgPtr->FeeBlockConfigPtr[BlkIdx].FeeUser ==
          (uint8)FEE_NVM_USER)
#endif
      {
        /* [cover parentID={CCDD13FA-6F39-4e3f-B48B-9AF7DE1FC299}]

[/cover] */
        RetVal = Fee_lRegisterNvmRead(BlockNumber, BlockOffset,
                                      DataBufferPtr, Length, FEE_SET);

      }
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
      else
      {
        /* [cover parentID={14D8388C-3115-4aa5-9C66-A64D6B220D96}]
Return E_NOT_OK
[/cover] */
        RetVal = E_NOT_OK;
  /* [cover parentID={85958C19-89C5-4634-90CC-30FF5A1303F7}]
Fee Safety is enabled
[/cover] */ 
#if (FEE_SAFETY_ENABLE == STD_ON)
        Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                               FEE_SID_GETPREVDATA, FEE_E_INVALID_BLOCK_NO);
#endif

      }
#endif
    }

  }
#if (FEE_SAFETY_ENABLE == STD_ON)
  else
  {

    if(Fee_CfgPtr == NULL_PTR)
    { 
/* [cover parentID={3F17237B-D727-4aa6-9BC8-B7777862BBA9},
      {0DA47D5E-3A0B-4244-8FF9-EA6CE1653932}]
Report error to FEE_SID_GETPREVDATA
[/cover] */
      Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                             FEE_SID_GETPREVDATA, FEE_E_UNINIT);
    }
    else
    {
      Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                             FEE_SID_GETPREVDATA, FEE_E_PARAM_POINTER);
    }
    /* [cover parentID={207E879F-CE45-4b94-8DB8-74F9A3AAF126}]
Return E_NOT_OK
[/cover] */
    RetVal = E_NOT_OK;
  }
#endif
/* [cover parentID={1566E231-D1FA-4dd6-A8BA-E662C3FD3A84}]
Merge
[/cover] */
  /* [cover parentID={CA1FE649-9DFC-45d4-98C2-268C7D65D4E4}]
Return
[/cover] */
  return(RetVal);

}
#endif /* #if (FEE_GET_PREV_DATA_API == STD_ON) */

#if (FEE_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** TRACEABILITY: [cover parentID={C8E8D26B-C335-4eaf-8F42-C2646611E65E}]      **
**                                                                            **
** Syntax :void Fee_GetVersionInfo(Std_VersionInfoType * const VersionInfoPtr)**
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:      0x08                                                      **
**                                                                            **
** Sync/Async:      Synchronous                                               **
**                                                                            **
** Reentrancy:      Reentrant                                                 **
**                                                                            **
** Parameters (out): VersionInfoPtr - Pointer to standard version information **
**           structure                                                        **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Return value:    void                                                      **
**                                                                            **
** Description :    This service returns the version information of           **
**                  this module.                                              **
**                  The version information includes:                         **
**                  Module Id, Vendor Id, Vendor specific version numbers     **
**                                                                            **
*******************************************************************************/
/* [cover parentID={A60B63DC-1A6F-4048-B92A-213AB0E88AC8}]
Fee_GetVersionInfo
[/cover] */
void Fee_GetVersionInfo(Std_VersionInfoType * const VersionInfoPtr)
{
  /* [cover parentID={7D1F1883-FDF9-4fef-8DD2-99D904DC4678}]
DET enabled
[/cover] */
#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
 /* [cover parentID={602A3EF9-A774-4da2-B06F-44CF452D6C49}]
Is VersionInfoPtr NULL?
[/cover] */
  if ((VersionInfoPtr) == NULL_PTR)
  {
    /* [cover parentID={9C33444C-8F98-4c37-AD80-F438CD0DFA76}]
Report DET error as FEE_E_PARAM_POINTER
[/cover] */
    Fee_lReportError(FEE_SID_GETVERSIONINFO, FEE_E_PARAM_POINTER);
  }
  else
#endif
  {
    /* [cover parentID={3161645F-3505-46a0-8EA4-A6356B1D3D11}]
Update Version Information in the location referenced by “VersionInfoPtr”
[/cover] */
    /* FEE Module ID */
    ((Std_VersionInfoType*)(VersionInfoPtr))->moduleID = FEE_MODULE_ID;
    /* FEE Vendor ID */
    ((Std_VersionInfoType*)(VersionInfoPtr))->vendorID = FEE_VENDOR_ID;
    /* major version of FEE */
    ((Std_VersionInfoType*)(VersionInfoPtr))->sw_major_version =
      (uint8)FEE_SW_MAJOR_VERSION;
    /* minor version of FEE */
    ((Std_VersionInfoType*)(VersionInfoPtr))->sw_minor_version =
      (uint8)FEE_SW_MINOR_VERSION;
    /* patch version of FEE */
    ((Std_VersionInfoType*)(VersionInfoPtr))->sw_patch_version =
      (uint8)FEE_SW_PATCH_VERSION;
  }
  /* [cover parentID={5ABE883B-1B58-444c-A871-81DC7F9533FA}]
Return
[/cover] */
}
#endif


/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

/*******************************************************************************
** Syntax: LOCAL_INLINE boolean Fee_lIsUserReadReqstd(                        **
**                                     const Fee_StateDataType * const s_ptr) **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : s_ptr - Pointer to state data                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : boolean                                                  **
**                   TRUE : Read operation requested                          **
**                   FALSE :Read operation not requested                      **
**                                                                            **
** Description : This routine checks if user read is requested                **
*******************************************************************************/
LOCAL_INLINE boolean Fee_lIsUserReadReqstd(const Fee_StateDataType * \
    const s_ptr)
{
  boolean RetVal;

  if (s_ptr->FeePendReqStatus == FEE_REQ_READ)
  {
    RetVal = (boolean)TRUE;
  }
  else
  {
    RetVal = (boolean)FALSE;
  }
  return(RetVal);
}

/*******************************************************************************
** Syntax: LOCAL_INLINE boolean Fee_lIsUserWriteInvldReqstd                   **
**                                (const Fee_StateDataType * const s_ptr)     **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : s_ptr - Pointer to state data                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : boolean                                                  **
**                   TRUE : write/invalidate operation requested              **
**                   FALSE :write/invalidate operation not requested          **
**                                                                            **
** Description : This routine checks if user write/invalidate is requested    **
*******************************************************************************/
LOCAL_INLINE boolean Fee_lIsUserWriteInvldReqstd
(const Fee_StateDataType * const s_ptr)
{
  boolean RetVal;

  if(((s_ptr)->FeePendReqStatus == FEE_REQ_NORM_WRITE) ||
      ((s_ptr)->FeePendReqStatus == FEE_REQ_IMM_WRITE))
  {
    RetVal = (boolean)TRUE;
  }
  else
  {
    RetVal = (boolean)FALSE;
  }
  return(RetVal);
}

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** Syntax: LOCAL_INLINE boolean Fee_lIsSectorEmpty(const uint8 state,         **
**                                                 const uint8 used)          **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Reentrant                                                 **
**                                                                            **
** Parameters (in) : state - Sector state                                     **
**                   used - Sector used status                                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : boolean                                                  **
**                 TRUE: Sector is empty , no data or state page is available **
**                 FALSE:Sector is  not empty , data or state page is         **
**                       available                                            **
** Description : This routine checks if sector is empty                       **
*******************************************************************************/
/* [cover parentID={ECEF61D1-8F31-4d29-B2BB-9FD0A24C0AF3}]
Fee_lIsSectorEmpty
[/cover] */
LOCAL_INLINE boolean Fee_lIsSectorEmpty(const uint8 state, const uint8 used)
{
  boolean RetVal;

  if((state == FEE_STATELESS) && (used == FEE_RESET))
  {
    RetVal = (boolean)TRUE;
  }
  else
  {
    RetVal = (boolean)FALSE;
  }
  return(RetVal);
}


/*******************************************************************************
** Syntax: LOCAL_INLINE uint32 Fee_lIsWLBeginning(const uint32 address)       **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in) : address - address to be checked                          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : uint32                                                   **
**                                                                            **
** Description : This routine returns the masked value of address w.r.t. WL   **
*******************************************************************************/
/* [cover parentID={8F8F02D5-8532-4a9f-8706-E0FBDB005C24}]
Fee_lIsWLBeginning
[/cover] */
LOCAL_INLINE uint32 Fee_lIsWLBeginning(const uint32 address)
{
  return(address & ((uint32)FEE_DFLASH_WORDLINE_SIZE_1));
}
#endif

/*******************************************************************************
** Syntax: LOCAL_INLINE uint32 Fee_lGetWLBeginning(const uint32 address)      **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : (uint32)address - address to be processed                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : uint32                                                   **
**                                                                            **
** Description : This routine returns the start address of the WL             **
*******************************************************************************/
LOCAL_INLINE uint32 Fee_lGetWLBeginning(const uint32 address)
{
  return(address & ((uint32)(~((uint32)FEE_DFLASH_WORDLINE_SIZE_1))));
}

/*******************************************************************************
** Syntax: LOCAL_INLINE uint32 Fee_lGetNextWLAddr(const uint32 address)       **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : (uint32)address - address to be processed                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : uint32                                                   **
**                                                                            **
** Description : This routine returns the start address of the next WL        **
*******************************************************************************/
LOCAL_INLINE uint32 Fee_lGetNextWLAddr(const uint32 address)
{
  /*Beginning of WL from current address + WL -> next free WL*/
  return((Fee_lGetWLBeginning(address)) + FEE_DFLASH_WORDLINE_SIZE);
}
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** Syntax: LOCAL_INLINE boolean Fee_lIsGcTriggeredOnce(const Fee_StateDataType**
**                                                      *const StateDataPtr)  **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : StateDataPtr - Pointer to state data                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : boolean                                                  **
**                 TRUE: GC is was never triggered after initialization       **
**                 FALSE: GC is was  triggered after initialization           **                                                 **
** Description : This routine checks whether GC was never triggered after     **
**               This is done by checking whether Fee_Write was never called  **
**               in the FEE_GC_RESTART_WRITE configuration                    **
*******************************************************************************/
/* [cover parentID={BA9DCE16-6576-4411-B7AF-D3331416BD3E}]
Fee_lIsGcTriggeredOnce
[/cover] */
LOCAL_INLINE boolean Fee_lIsGcTriggeredOnce(const Fee_StateDataType
    * const StateDataPtr)
{
  boolean RetVal;

  if ((Fee_CfgPtr->FeeGCConfigSetting.FeeGcRestartPoint ==
       (uint32)FEE_GC_RESTART_WRITE)
      && (StateDataPtr->FeeStatusFlags.FeeWriteInvldAPICalled ==
          (uint32)FEE_RESET))
  {
    RetVal = (boolean)TRUE;
  }
  else
  {
    RetVal = (boolean)FALSE;
  }
  return(RetVal);
}

/*******************************************************************************
** Syntax: LOCAL_INLINE boolean Fee_lIsSectorThresholdCrossed(                **
**                                                    const uint32 FreePages, **
**                                                    const uint32 PageCount) **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : FreePages - Number of free pages                         **
**                   PageCount - Page count                                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : boolean                                                  **
**                   TRUE : Sector Threshold is crossed.                      **
**                   FALSE: Sector Threshold is not crossed.                  **
**                                                                            **
** Description : This routine checks whether sector threshold will be crossed **
*******************************************************************************/
/* [cover parentID={414557E8-31F9-496c-AD2A-B0555A816D4D}]
Fee_lIsSectorThresholdCrossed
[/cover] */
LOCAL_INLINE boolean Fee_lIsSectorThresholdCrossed(const uint32 FreePages,
    const uint32 PageCount)
{
  boolean RetVal;

  if ((sint32)(((sint32)FreePages - (sint32)PageCount)
               * (sint32)FEE_DFLASH_PAGE_SIZE)
      < (sint32)(Fee_CfgPtr->FeeThresholdLimit))
  {
    RetVal = (boolean)TRUE;
  }
  else
  {
    RetVal = (boolean)FALSE;
  }
  return(RetVal);
}

/*******************************************************************************
** Syntax: LOCAL_INLINE boolean Fee_lIsSectorEndCrossed(                      **
**                                                const uint32 FreePages,     **
**                                                const uint32 PageCount)     **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : FreePages - Number of free pages                         **
**                   PageCount - Page count                                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : boolean                                                  **
**                   TRUE : Sector end will be crossed.                       **
**                   FALSE: Sector end will not be crossed.                   **
**                                                                            **
** Description : This routine checks whether sector end will be crossed       **
*******************************************************************************/
/* [cover parentID={08E7BF93-2A90-4024-9FA2-E0BDF8973430}]
Fee_lIsSectorEndCrossed
[/cover] */
LOCAL_INLINE boolean Fee_lIsSectorEndCrossed(const uint32 FreePages,
    const uint32 PageCount)
{
  boolean RetVal;

  if (FreePages < PageCount)
  {
    RetVal = (boolean)TRUE;
  }
  else
  {
    RetVal = (boolean)FALSE;
  }
  return(RetVal);
}
#endif
/*******************************************************************************
** TRACEABILITY: []                                                           **
**                                                                            **
** Syntax : static void Fee_lHandleUsrJobFailure(const uint8 Error)           **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : Error : Type of user job failure                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function handles the user job failure occuring due to   **
**               FLS operation failure                                        **
*******************************************************************************/
/* [cover parentID={F93CF5D6-8C82-4a59-A5FB-9A4A154CF19E},
{3D4E0F4A-DBE1-47ae-8344-313B4E73FAC9}]
Fee_lHandleUsrJobFailure
[/cover] */
static void Fee_lHandleUsrJobFailure(const uint8 Error)
{
  Fee_StateDataType     *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /* Set StateDataPtr->FeeJobResult as Failed */
  /* [cover parentID={F93CF5D6-8C82-4a59-A5FB-9A4A154CF19E}]*/

  if(Error != FEE_CANCEL )
  {
    StateDataPtr->FeeJobResult = MEMIF_JOB_FAILED;
  }
  else
  {
    StateDataPtr->FeeJobResult = MEMIF_JOB_CANCELED;
  }
#if((FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA ) && \
    (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON))
  /*Check if QS erase was suspended. If yes then set FeePendReqStatus to
  FEE_REQ_QUASI_ERASE to set module status to busy.*/
  if(StateDataPtr->FeeQsEraseSuspend == FEE_ERASE_SUSPENDED)
  {
    StateDataPtr->FeePendReqStatus = FEE_REQ_QUASI_ERASE;
    StateDataPtr->FeeQsJob = FEE_ERASE_JOB;
  }
  else
#endif
  {
    StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_NO_REQ;
  }

  /* Reset the Invalid Status flag */
  StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus = FEE_RESET;
  StateDataPtr->FeeUserJobStatus = FEE_JOB_IDLE;
  StateDataPtr->FeeUserJobResult = FEE_JOB_FAIL;
  StateDataPtr->FeeUserJobFailCount = FEE_RESET;
  StateDataPtr->FeeBlkPageCount = FEE_RESET;

  /* Raise Job Failed DEM */
#if (FEE_WRITE_DEM_REPORT == FEE_ENABLE_DEM_REPORT)
  if (Error == FEE_WRITE)
  {
    /* [cover parentID={85B21C01-71F7-4c33-AE93-125C456302CE}]
Report write error to DEM FEE_E_WRITE
[/cover] */
    Dem_ReportErrorStatus(FEE_E_WRITE, DEM_EVENT_STATUS_FAILED);
  }
#endif

#if (FEE_INVALIDATE_DEM_REPORT == FEE_ENABLE_DEM_REPORT)
  if (Error == FEE_INVALIDATE)
  {
    /* [cover parentID={F0B26CA2-58F4-4983-AF2C-69D7A8B445BE}]
Report invalidate error to DEM FEE_E_INVALIDATE
[/cover] */
    Dem_ReportErrorStatus(FEE_E_INVALIDATE, DEM_EVENT_STATUS_FAILED);
  }
#endif

#if (FEE_READ_DEM_REPORT == FEE_ENABLE_DEM_REPORT)
  if (Error == FEE_READ)
  {
    /* [cover parentID={296972F3-33FE-4420-B8E2-32CC87327906}]
Report read error to DEM FEE_E_READ
[/cover] */
    Dem_ReportErrorStatus(FEE_E_READ, DEM_EVENT_STATUS_FAILED);
  }
#endif

#if (FEE_WRITE_DEM_REPORT != FEE_ENABLE_DEM_REPORT)
#if (FEE_INVALIDATE_DEM_REPORT != FEE_ENABLE_DEM_REPORT)
#if (FEE_READ_DEM_REPORT != FEE_ENABLE_DEM_REPORT)
  /* To avoid compiler warning */
  UNUSED_PARAMETER (Error);
#endif
#endif
#endif
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
  /* Report job Error notification */
  if(Fee_CfgPtr->FeeNvmJobErrorNotification != NULL_PTR )
  {
    /* [cover parentID={FC5E8027-B173-41e5-9BFC-5DBB1466ED54}]
Call the NVM job error notification function
[/cover] */
    (Fee_CfgPtr->FeeNvmJobErrorNotification)();
  }
#endif
}

/*******************************************************************************
** Syntax : static MemIf_StatusType Fee_lGetStatus(void)                      **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  MemIf_StatusType                                        **
**                                                                            **
** Description : This function returns the status of the FEE driver           **
*******************************************************************************/
/*[cover parentID={17ECE2B2-88D5-4cb8-A467-57835E79CD09}][/cover]*/
static MemIf_StatusType Fee_lGetStatus(void)
{
  const Fee_StateDataType  *StateDataPtr;
  MemIf_StatusType   ReturnStatus;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  ReturnStatus = MEMIF_IDLE;
  /* [cover parentID={11105008-76C8-431b-91C3-49D5F0DE2B07}]
Return status as MEMIF_IDLE
[/cover] */
  if(StateDataPtr->FeePendReqStatus == FEE_WRITE_FAIL)
  {
    /* ReturnStatus is MEMIF_IDLE */
  }
  /* If there is a request pending */
  else if(StateDataPtr->FeePendReqStatus != FEE_PEND_PREV_NO_REQ)
  {
    /* [cover parentID={1E38F4F8-84B8-4278-9D72-057D620E3EA7}]
Return status as MEMIF_BUSY
[/cover] */
    ReturnStatus = MEMIF_BUSY;
  }
  /* [cover parentID={4BE544DA-5C4E-4ff8-99F7-4CA2BD9118E6}]
Return status as MEMIF_IDLE
[/cover] */
  /* Init activities NOT triggered */
  else if(StateDataPtr->FeeStatusFlags.FeeStartInitGC == (uint32)FEE_RESET)
  {
    /* ReturnStatus is MEMIF_IDLE */
  }
  /* [cover parentID={A5B248A0-FCDA-4d8b-9EB1-41ACA8BCC8C9}]
Return status as MEMIF_IDLE
[/cover] */
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
  /* If the GC/InitGC has failed */
  else if((StateDataPtr->FeeGcState == FEE_GC_FAIL) ||
          (StateDataPtr->FeeInitGCState == FEE_INITGC_FAIL))
  {
    /* ReturnStatus is MEMIF_IDLE */
  }

  /* if Cache update activities ongoing */
  else if(StateDataPtr->FeeCacheState != FEE_CACHE_UPDATE_COMPLETE)
  {
    /* [cover parentID={DB4C4736-67E3-478c-945D-263CA89FE9FB}]
Return status as MEMIF_BUSY_INTERNAL
[/cover] */
    ReturnStatus = MEMIF_BUSY_INTERNAL;
  }
#else
  else if(StateDataPtr->FeeCacheState != FEE_CACHE_IDLE_QS)

  {
    /* [cover parentID={E252153D-5632-4a82-B5A2-BC4D7D254DBD}]
    Return status as MEMIF_BUSY_INTERNAL
    [/cover] */
    ReturnStatus = MEMIF_BUSY_INTERNAL;
  }
#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
  else if(StateDataPtr->FeeGcState != FEE_GC_IDLE)
  {
    /* Scenario: First Fee write is not called but Fee_Read  */
    /* is already called                                     */
    /* [cover parentID={47C71766-E860-48a1-B791-ED113036B9FC}]
Return status as MEMIF_IDLE
[/cover] */
    if((boolean)FALSE != Fee_lIsGcTriggeredOnce(StateDataPtr))
    {
      /* ReturnStatus is MEMIF_IDLE */
    }
    else
    {
      /* [cover parentID={E252153D-5632-4a82-B5A2-BC4D7D254DBD}]
Return status as MEMIF_BUSY_INTERNAL
[/cover] */
      ReturnStatus = MEMIF_BUSY_INTERNAL;
    }
  }
#endif
  /* [cover parentID={CCA822AB-3230-44ea-B00B-055A7594D8F1}]
Return status as MEMIF_IDLE
[/cover] */
  else
  {
    /* ReturnStatus is MEMIF_IDLE */
  }

  return(ReturnStatus);

}/*End of Fee_GetStatus */
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** Syntax : LOCAL_INLINE boolean Fee_lGcCheckUnconfigBlkCopy(void)            **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  TRUE : At least one un-configured block is to be copied **
**                    FALSE: All un-configured blocks are copied              **
**                                                                            **
** Description : This function checks whether any un-configured block needs   **
**               to be copied                                                 **
*******************************************************************************/
/* [cover parentID={8B763DD8-7779-4ef2-9186-791AFD8AD157}]
Fee_lGcCheckUnconfigBlkCopy
[/cover] */
LOCAL_INLINE boolean Fee_lGcCheckUnconfigBlkCopy(void)
{
  /* [cover parentID={8B763DD8-7779-4ef2-9186-791AFD8AD157}]*/
  const Fee_StateDataType     *StateDataPtr;
  boolean               RetVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* if any un-configured block is yet to be copied then, return TRUE */
  if(StateDataPtr->FeeGCUnconfigBlkCopyIndex <
      StateDataPtr->FeeUnConfigBlockCount)
  {
    RetVal = (boolean)TRUE;
  }
  else
  {
    RetVal = (boolean)FALSE;
  }

  return(RetVal);
}
#endif
/*******************************************************************************
** Syntax: static Fls_17_Dmu_Job_Type Fee_lGetUserJob(const uint8 PendReqType)**
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :(uint8)PendReqType : Type of pending request              **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Fls_17_Dmu_Job_Type                                     **
**                                                                            **
** Description : This function returns the ongoing user job                   **
*******************************************************************************/
/*[cover parentID={B13D305A-1DCD-4fd2-941E-37FD1B4248B9}][/cover]*/
static Fls_17_Dmu_Job_Type Fee_lGetUserJob(const uint8 PendReqType)
{
  Fls_17_Dmu_Job_Type RetVal;

  switch(PendReqType)
  {
    /* These states mean that the write job is going on */
    case FEE_PEND_PREV_COMPARE:
    case FEE_PEND_INTR_COMPARE:
      {
        RetVal = FEE_WRITE_JOB;
        break;
      }

    /* The following are the states for read job */
    case FEE_PEND_PREV_READ_REQ:
    case FEE_PEND_PREV_READ_NOTIF:
      {
        RetVal = FEE_READ_JOB;
        break;
      }

    default:
      {
        RetVal = FEE_NO_JOB;
        break;
      }
  }

  return(RetVal);

}/*End of Fee_lGetUserJob */
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** TRACEABILITY: []                                                           **
**                                                                            **
** Syntax : static boolean Fee_lIsReadAllowedbyGC(void )                      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Bool                                                    **
**                   TRUE: Read Request execution is allowed during GC        **
**                   FALSE: Read Request execution not is allowed during GC   **
**                                                                            **
** Description : This function checks if the user read is allowed by GC       **
**                                                                            **
*******************************************************************************/
/* [cover parentID={1C4E2854-85A3-4a9d-A2EC-F0B8BB42000F}]
Fee_lIsReadAllowedbyGC
[/cover] */
static boolean Fee_lIsReadAllowedbyGC(void)
{

#if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
  Fee_StateDataType *StateDataPtr;
  Std_ReturnType     FlsRetVal;
#else
  const Fee_StateDataType *StateDataPtr;
#endif
  boolean            RetVal;
  /* [cover parentID={1C4E2854-85A3-4a9d-A2EC-F0B8BB42000F}]*/
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  RetVal = (boolean)FALSE;
   /* [cover parentID={9DF016FA-2FB7-4a8f-AEF7-B9A77418CBDA}]
Is GC requested and not yet started?
[/cover] */
  /* GC is requested and not yet started */
  if(StateDataPtr->FeeGcState == FEE_GC_REQUESTED)
  {
    RetVal = (boolean)TRUE;
  }
  /* [cover parentID={8A62EE37-5298-4088-8DC6-DCC4F0F1C2C6}]
Is copying of unconfigured blocks done and copy of next unconfigured block has not yet started?
[/cover] */
  /* GC is in Un-configured block copy state and copy of current block is done 
  and  next block copy is not yet started */
  else if((StateDataPtr->FeeGcState == FEE_GC_UNCFG_START_COPY) &&
          (StateDataPtr->FeeIntrJobStatus == FEE_JOB_IDLE))
  {
    RetVal = (boolean)TRUE;
  }
  /* [cover parentID={7E7F6DEA-EB6C-4caa-8CA8-7B8B4270BBCE}]
Is copying of configured blocks done and copy of next configured block has not yet started?
[/cover] */
  /* GC is in configured block copy state and copy of current block is done 
  and  next block copy is not yet started */
  else if((StateDataPtr->FeeGcState == FEE_GC_START_COPY) &&
          (StateDataPtr->FeeIntrJobStatus == FEE_JOB_IDLE))
  {
    RetVal = (boolean)TRUE;
  }

 /*Check if GC in erase state as part of normal GC opertaion.Pending request 
  can not be executed when GC in erase state as part init GC beacuse of cache
  table is not yet build and initializtion activity is not finished */
  else if(StateDataPtr->FeeGcState == FEE_GC_ERASE_PREV_SECTOR)
  {
    /*check if erased operation is requested to fls*/ 
    if(StateDataPtr->FeeIntrJobStatus == FEE_JOB_REQSTD)
    {
      /* call fls erase suspend function if supported by hardware */
#if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)     
      if(Fee_CfgPtr->FeeGCConfigSetting.FeeUseEraseSuspend ==
        (uint32)FEE_ERASE_SUSPEND_ENABLED)
      {
        if(FEE_ERASE_NOT_SUSPENDED == StateDataPtr->FeeEraseSuspendStatus)
        {
          FlsRetVal = Fls_17_Dmu_SuspendErase();
          if(E_OK == FlsRetVal)
          {
            RetVal = (boolean)TRUE;
            StateDataPtr->FeeEraseSuspendStatus = FEE_ERASE_SUSPENDED;
          }
        }
        else
        {
          RetVal = (boolean)TRUE;
          /* In the case of a suspend request, when previous attempt of resume
          had failed at least once, then the count shall be
          reset back to 1, as it is a new request for suspend. */
          StateDataPtr->FeeEraseSuspendStatus = FEE_ERASE_SUSPENDED;
        }
      }
#endif    
    }
    else
    {
      /* Erase operation is not started or completed */
      RetVal = (boolean)TRUE;   
    } 
  }
  else
  {
    /* dummy else */
  }

  return(RetVal);

}/* End of Fee_lIsReadAllowedbyGC */

/*******************************************************************************
** TRACEABILITY: []                                                           **
**                                                                            **
** Syntax : static boolean Fee_lIsWriteInvldAllowedbyGC(void)                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Bool                                                    **
**                   FALSE: Write/Invalidate Request execution not allowed    **
**                   TRUE: Write/Invalidate  Request execution allowed        **
**                                                                            **
** Description : Checks if the Write/Invalidate request execution is allowed  **
**               by GC depending on the erase suspend feature configuration.  **
*******************************************************************************/
/* [cover parentID={6DB78D22-11ED-43f9-838E-5B61C20B9627}]
Fee_lIsWriteInvldAllowedbyGC
[/cover] */
static boolean Fee_lIsWriteInvldAllowedbyGC(void)
{
#if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
  Fee_StateDataType *StateDataPtr;
  Std_ReturnType     FlsRetVal;
#else
  const Fee_StateDataType *StateDataPtr;
#endif
  boolean            RetVal;
  uint16             PendReqBlkNum;
  uint16             PendReqBlkIndex;
  Std_ReturnType     PendBlkWritable;
  const Fee_BlockType  *PendReqBlkPtr;

  /* [cover parentID={6DB78D22-11ED-43f9-838E-5B61C20B9627}]*/
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  RetVal = (boolean)FALSE;

  /* Immediate write has been requested */
  if((StateDataPtr->FeePendReqStatus == (uint8)FEE_REQ_IMM_WRITE) &&
      (StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus == (uint32)FEE_RESET) &&
      ((StateDataPtr->FeeGcState == FEE_GC_UNCFG_START_COPY)
       ||(StateDataPtr->FeeGcState == FEE_GC_START_COPY)))
  {  /* [cover parentID={51BA216E-4E3B-4bde-8BAE-2A8640681293}]
Is the GC read/write job requested to FLS ?
[/cover] */
    /* Copying of an un-configure /configured block is done.Copy of next 
    un-configured / configured block has not yet started */
    if (StateDataPtr->FeeIntrJobStatus == FEE_JOB_IDLE)
    {
      RetVal = (boolean)TRUE;
    }

  }
  else /* Immediate/Normal write has been requested during GC erase state */
  {
    /*Check if GC in erase state as part of normal GC opertaion.Pending request 
    can not be executed when GC in erase state as part init GC beacuse of cache
    table is not yet build and initializtion activity is not finished */
    if(StateDataPtr->FeeGcState == FEE_GC_ERASE_PREV_SECTOR)
    {
      PendReqBlkNum = StateDataPtr->FeePendReqInfo.BlockNumber;
      PendReqBlkIndex = Fee_lGetUsrBlockIndex(PendReqBlkNum);
      /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic is used for
      for faster access of Block traversal.It is ensured that PendReqBlkIndex
      is within the desired boundary*/
      PendReqBlkPtr = Fee_CfgPtr->FeeBlockConfigPtr + PendReqBlkIndex;
      PendBlkWritable = Fee_lPerformCurrBlkCheck(PendReqBlkPtr);

      if(StateDataPtr->FeeIntrJobStatus == FEE_JOB_REQSTD)
      {
        /* call fls erase suspend function if supported by hardware and can be
        suspended*/
#if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
        if(Fee_CfgPtr->FeeGCConfigSetting.FeeUseEraseSuspend ==
            (uint32)FEE_ERASE_SUSPEND_ENABLED)
        {

          if(PendBlkWritable == E_OK)
          {
            if(FEE_ERASE_NOT_SUSPENDED == StateDataPtr->FeeEraseSuspendStatus)
            { /* [cover parentID={F62D61CA-CF0C-4fd0-9A74-8EE630EF26B1}]
Call fls erase suspend function (Only if the erase is not suspended already )
[/cover] */
              FlsRetVal = Fls_17_Dmu_SuspendErase();
              if(E_OK == FlsRetVal)
              {
                RetVal = (boolean)TRUE;
                StateDataPtr->FeeEraseSuspendStatus = FEE_ERASE_SUSPENDED;
              }
            }
            else
            {
              RetVal = (boolean)TRUE;
              /* In the case of a suspend request, when previous attempt of
              resume had failed at least once, then the count shall be
              reset back to 1, as it is a new request for suspend. */
              StateDataPtr->FeeEraseSuspendStatus = FEE_ERASE_SUSPENDED;
            }
          }
        }
#endif
      }
      else
      {
        /* Erase operation is not started or completed*/
        if(PendBlkWritable == E_OK)
        {
          RetVal = (boolean)TRUE;
        }

      }
    }
  }

  return(RetVal);

}/* End of Fee_lIsWriteInvldAllowedbyGC */


/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lMainGCTransHdlr(void)                      **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function determines and performs the state transition   **
** for the main function when in FEE_MAIN_GC state                            **
*******************************************************************************/
LOCAL_INLINE void Fee_lMainGCTransHdlr(void)
{
  Fee_StateDataType *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* Check if GC is completed */
  if((FEE_MAIN_GC == StateDataPtr->FeeMainJob) &&
      (FEE_GC_IDLE == StateDataPtr->FeeGcState))
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_NONE;
  }

  /* Check if the Read request is pending & can be executed */
  else if((boolean)TRUE == Fee_lIsUserReadReqstd(StateDataPtr))
  {
    if(Fee_lIsReadAllowedbyGC() == (boolean)TRUE)
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_READ;
    }
  }
  /* Check if the Write request is pending & can be executed */
  else if(((boolean)TRUE == Fee_lIsUserWriteInvldReqstd(StateDataPtr)) &&
          (FEE_MAIN_GC == StateDataPtr->FeeMainJob))
  {
    if(Fee_lIsWriteInvldAllowedbyGC() == (boolean)TRUE)
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_WRITE;
    }
  }
#if(FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
  else if(Fee_lIsQsWriteReadAllowedbyGC() == TRUE)
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_QS;
  }
#endif
  else
  {
    /* dummy for MISRA */
  }


}
#endif
/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lMainNoneTransHdlr(void)                    **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function determines and performs the state transition   **
** for the main function when in FEE_MAIN_NONE state                          **
*******************************************************************************/
LOCAL_INLINE void Fee_lMainNoneTransHdlr(void)
{
  Fee_StateDataType *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* Check if User Read request is registered */
  if( (boolean)TRUE == Fee_lIsUserReadReqstd(StateDataPtr) )
  {

#if (FEE_CANCELL_ALL_API == STD_ON) && \
    (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
    /* Check if there is GC cancelled by cancel all */
    if(StateDataPtr->FeeCancelallGCstate == FEE_GC_CANCLD)
    {
      /* Call the Fee_lCancelAllGCrestart to restart the GC*/
      Fee_lCancelAllGCrestart();

      /* Set the FeeCancelallGCstate to FEE_GC_CANCLD_CACHEUPDATE and set main
      state to FEE_MAIN_INITGC */
      StateDataPtr->FeeCancelallGCstate = FEE_GC_CANCLD_CACHEUPDATE;
      StateDataPtr->FeeMainJob = FEE_MAIN_INITGC;

    }
    else
#endif
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_READ;
    }



  }
  /* Check if User Write, Invalidate request is registered */
  else if( (boolean)TRUE == Fee_lIsUserWriteInvldReqstd(StateDataPtr) )
  {
#if (FEE_CANCELL_ALL_API == STD_ON) && \
    (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
    /* Check if there is GC cancelled by cancel all */
    if(StateDataPtr->FeeCancelallGCstate == FEE_GC_CANCLD)
    {
      /* Call the Fee_lCancelAllGCrestart to restart the GC*/
      Fee_lCancelAllGCrestart();

      /* Set the FeeCancelallGCstate to FEE_GC_CANCLD_CACHEUPDATE and set main
      state to FEE_MAIN_INITGC */
      StateDataPtr->FeeCancelallGCstate = FEE_GC_CANCLD_CACHEUPDATE;
      StateDataPtr->FeeMainJob = FEE_MAIN_INITGC;

    }
    else
#endif
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_WRITE;
    }
  }
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  else if( StateDataPtr->FeeQsJob != FEE_NO_JOB)
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_QS;
  }
#if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
  else if( StateDataPtr->FeeQsEraseSuspend == FEE_SET )
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_QS;
  }
#endif
#endif
  else
  {
    /* Fee_MainStateVar will be FEE_MAIN_NONE */
  }
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lMainCacheUpdtTransHdlr(void)               **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function determines and performs the state transition   **
** for the main function when in FEE_MAIN_CACHEUPDATE state                   **
*******************************************************************************/
/* [cover parentID={3829EAB5-02D8-4257-9893-60F48BF58519}]
Fee_lMainCacheUpdtTransHdlr
[/cover] */
LOCAL_INLINE void Fee_lMainCacheUpdtTransHdlr(void)
{
  Fee_StateDataType *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* Check if User Read request is registered */
  if((boolean)TRUE == Fee_lIsUserReadReqstd(StateDataPtr))
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_READ;
  }
  /* Check if User Write, Invalidate request is registered
    and the write can be accommodated */
  else if((boolean)TRUE == Fee_lIsUserWriteInvldReqstd(StateDataPtr))
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_WRITE;
  }
  else if(StateDataPtr->FeeGcState != FEE_GC_IDLE)
    /* Check for !Fee_lIsGcTriggeredOnce() is not required as it will be true
       else FEE would not be in Cache Update state */
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_GC;
  }
  else
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_NONE;
  }
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lMainReadTransHdlr(void)                    **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function determines and performs the state transition   **
** for the main function when in FEE_MAIN_READ state                          **
*******************************************************************************/
LOCAL_INLINE void Fee_lMainReadTransHdlr(void)
{
  Fee_StateDataType *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* Check if the Write/Read/Invalidate job is finished */
  if(StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_NO_REQ)
  {
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
    /* Check if GC job is ongoing/requested */
    if(((boolean)FALSE == Fee_lIsGcTriggeredOnce(StateDataPtr)) &&
        (StateDataPtr->FeeGcState != FEE_GC_IDLE))
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_GC;
    }
    else
#endif
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_NONE;
    }
  }
  /* Check if user write/invalidate is requested */
  else if((boolean)TRUE == Fee_lIsUserWriteInvldReqstd(StateDataPtr))
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_WRITE;
  }

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  /* Check if Qs Erase job is requested */
  else if(StateDataPtr->FeeQsJob == FEE_ERASE_JOB)
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_QS;
  }

  /*Check if QS read is requested*/
  else if(StateDataPtr->FeePendReqStatus == FEE_REQ_QUASI_READ)
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_QS;
  }

  /*Check if QS write is requested*/
  else if(StateDataPtr->FeePendReqStatus == FEE_REQ_QUASI_WRITE)
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_QS;
  }

#endif
  else
  {
    /* dummy else */
  }
}

/*CYCLOMATIC_Fee_lMainWriteTransHdlr_JUSTIFICATION:
Fee_lMainWriteTransHdlr has to pass through many states for interrupted read
during write,if it is broken into more functions, the readability will get
affected.
*/
/*******************************************************************************
** Syntax: LOCAL_INLINE void Fee_lMainWriteTransHdlr(void)                    **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function determines and performs the state transition   **
** for the main function when in FEE_MAIN_WRITE state                         **
*******************************************************************************/
LOCAL_INLINE void Fee_lMainWriteTransHdlr(void)
{
  Fee_StateDataType *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;


  /* Check if the Write/Read/Invalidate job is finished */
  if(StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_NO_REQ)
  {
    /* Check for !Fee_lIsGcTriggeredOnce() is not required as it is True
    when the main job is WRITE */
    if (StateDataPtr->FeeGcState != FEE_GC_IDLE)
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_GC;
    }
    else
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_NONE;
    }
  }
  else if( (StateDataPtr->FeePendReqStatus == FEE_REQ_NORM_WRITE) ||
           (StateDataPtr->FeePendReqStatus == FEE_REQ_IMM_WRITE)
         )
  {

    /* Check for !Fee_lIsGcTriggeredOnce() is not required as it is always
    true when FeePendReqStatus = FEE_REQ_NORM_WRITE / FEE_REQ_IMM_WRITE */
    if ((StateDataPtr->FeeGcState != FEE_GC_IDLE) &&
        (StateDataPtr->FeeReadLen == 0U))
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_GC;
    }

  }

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  /*Check for QS Write*/
  else if(StateDataPtr->FeePendReqStatus == FEE_REQ_QUASI_WRITE)
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_QS;
  }

#endif

  /* Check if user read is requested */
  else if((boolean)TRUE == Fee_lIsUserReadReqstd(StateDataPtr))
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_READ;
  }

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  /*Check for QS read*/
  else if(StateDataPtr->FeePendReqStatus == FEE_REQ_QUASI_READ)
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_QS;
  }
  else if(StateDataPtr->FeePendReqStatus == FEE_REQ_QUASI_ERASE)
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_QS;
  }

#endif
  else
  {
    /* Remain in FEE_MAIN_WRITE */
    /* i.e.
    FEE_PEND_PREV_WRITE_REQ : Current block write is not yet completed
    */
  }
}

/*******************************************************************************
** Syntax : static void Fee_lDecideMainJob(void)                              **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function determines and performs the state transition   **
** for the main function                                                      **
*******************************************************************************/
/*[cover parentID={1C5B8136-C85D-45c1-A9F9-612767538334}][/cover]*/
static void Fee_lDecideMainJob(void)
{
  Fee_StateDataType     *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;


  switch(StateDataPtr->FeeMainJob)
  {
    case FEE_MAIN_INITGC:
      {
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
        /* Check if InitGC activity is ongoing */
        if(StateDataPtr->FeeInitGCState == FEE_INITGC_COMPLETE)
        {
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)

#if ((FEE_CANCELL_ALL_API == STD_ON) && \
    (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA))
          if(StateDataPtr->FeeCancelallGCstate == FEE_GC_CANCLD_CACHEUPDATE)
          {
            StateDataPtr->FeeMainJob = FEE_MAIN_CACHEUPDATE;
            StateDataPtr->FeeCancelallGCstate = FEE_GC_NOT_CANCLD;
          }
          else
          {
            StateDataPtr->FeeMainJob = FEE_MAIN_INITQS;
          }
#else
          StateDataPtr->FeeMainJob = FEE_MAIN_INITQS;
#endif

#else
          StateDataPtr->FeeMainJob = FEE_MAIN_CACHEUPDATE;
#endif
        }
#else
        /* Checking GC activity is not required for QS */
        StateDataPtr->FeeMainJob = FEE_MAIN_INITQS;
#endif
        break;
      }
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
    case FEE_MAIN_INITQS:
      {
        if(StateDataPtr->FeeInitQSState == FEE_INITQS_COMPLETE)
        {
          StateDataPtr->FeeMainJob = FEE_MAIN_CACHEUPDATE;
        }
        break;
      }
#endif
    case FEE_MAIN_NONE:
      {
        Fee_lMainNoneTransHdlr();
        break;
      }

    case FEE_MAIN_CACHEUPDATE:
      {
        Fee_lMainCacheUpdtTransHdlr();
        break;
      }

    case FEE_MAIN_READ:
      {
        Fee_lMainReadTransHdlr();
        break;
      }

    case FEE_MAIN_WRITE:
      {
        Fee_lMainWriteTransHdlr();
        break;

      }
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
    case FEE_MAIN_QS:
      {
        Fee_lMainQsTransHdlr();
        break;
      }
#endif
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
    case FEE_MAIN_GC:
      {
        Fee_lMainGCTransHdlr();
        break;
      }
#endif

    /* remaining case - FEE_MAIN_UNINIT */
    default:
      {
        /* Check if InitGC activity is requested */
        if(StateDataPtr->FeeStatusFlags.FeeStartInitGC == (uint32)FEE_SET )
        {
          StateDataPtr->FeeMainJob = FEE_MAIN_INITGC;
        }
        break;
      }
  }
}/*End of Fee_lDecideMainJob */
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lHandleErasePrepDFLASH(void)                **
**                                                                            **
** Service ID:                                                                **
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
** Description : This function handles the erase operations for DFLASH        **
**               preparation                                                  **
*******************************************************************************/
/* [cover parentID={17A84697-3D49-41a4-9B9E-AB77738D3081}]
Fee_lHandleErasePrepDFLASH
[/cover] */
LOCAL_INLINE void Fee_lHandleErasePrepDFLASH(void)
{
  Fee_StateDataType   *StateDataPtr;
  Fls_17_Dmu_AddressType      DestAddr;
  Std_ReturnType       ReturnValueFls;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  DestAddr = StateDataPtr->FeeCurrSectSrcAddr;
  StateDataPtr->FeeIntrJobStatus = FEE_JOB_REQSTD;
  StateDataPtr->FeeIntrJob = FEE_ERASE_JOB;

  /* erase current sector */
  ReturnValueFls = Fls_17_Dmu_Erase(DestAddr,
                                    (Fls_17_Dmu_LengthType)FEE_DFLASH_SECTOR_SIZE);
  if(ReturnValueFls == E_NOT_OK)
  {
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
    StateDataPtr->FeeIntrJob = FEE_NO_JOB;
    Fee_lHandleInitGcFail();
  }
}

/*******************************************************************************
** Syntax : static void Fee_lHandleWritePrepDFLASH(const uint8 *const SrcPtr) **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  SrcPtr:  Pointer to the buffer with state page data     **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description : This function handles the write operations for DFLASH        **
**               preparation                                                  **
*******************************************************************************/
/* [cover parentID={F9397328-6B85-4b1d-9735-4462DBD22FE2}]
Fee_lHandleWritePrepDFLASH
[/cover] */
static void Fee_lHandleWritePrepDFLASH(const uint8 *const SrcPtr)
{
  Fee_StateDataType   *StateDataPtr;
  Fls_17_Dmu_AddressType      DestAddr;
  Std_ReturnType       ReturnValueFls;
  uint8                PrepDFlashState;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  DestAddr = StateDataPtr->FeeCurrSectSrcAddr;
  while(Fee_lIsUnerasableAddr(DestAddr) == TRUE)
  {

    DestAddr += (FEE_DFLASH_WORDLINE_SIZE);
  }
  StateDataPtr->FeeCurrSectSrcAddr = DestAddr;
  StateDataPtr->FeeIntrJobStatus = FEE_JOB_REQSTD;
  StateDataPtr->FeeIntrJob = FEE_WRITE_JOB;

  PrepDFlashState = StateDataPtr->FeePrepDFLASHState;

  switch (PrepDFlashState)
  {
    case FEE_PREPDF_MARK_S0_ERASED_SP:
    case FEE_PREPDF_MARK_S0_VALID_SP:
    case FEE_PREPDF_MARK_S1_ERASED_SP:
      {
        ReturnValueFls = Fls_17_Dmu_Write(DestAddr, SrcPtr,
                                          (Fls_17_Dmu_LengthType)FEE_STATEPAGE_PROGRAM_SIZE);
      }
      break;

    /*
      Remaining cases:
        FEE_PREPDF_MARK_S0_ERASED_M
        FEE_PREPDF_MARK_S0_VALID_M
        FEE_PREPDF_MARK_S1_ERASED_M
    */
    default:
      {
        DestAddr += FEE_STATEPAGE_DATA_SIZE;
        ReturnValueFls = Fls_17_Dmu_Write(DestAddr, SrcPtr,
                                          (Fls_17_Dmu_LengthType)FEE_STATEPAGE_MARKER_SIZE);
      }
      break;
  }

  if(ReturnValueFls == E_NOT_OK)
  {
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
    StateDataPtr->FeeIntrJob = FEE_NO_JOB;
    Fee_lHandleInitGcFail();
  }
}/*End of Fee_lHandleWritePrepDFLASH */

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lIDSM(void)                                 **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function implements the Init Dirty State Machine which  **
** repairs the identified state pages before handing over to the INSM         **
*******************************************************************************/
/* [cover parentID={0BDE2A71-D5BF-447c-8DCF-7A8C8B87E5F8}]
Fee_lIDSM
[/cover] */
LOCAL_INLINE void Fee_lIDSM(void)
{
  Fee_StateDataType     *StateDataPtr;
  Fee_SectorInfoType    *SectorInfoPtr;
  uint8           *ReadWriteBuffPtr;
  Fls_17_Dmu_AddressType        DestWriteAddress;
  uint32                 BankNumber;
  uint32                 WriteLength;
  Std_ReturnType         ReturnValueFls;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  BankNumber =  StateDataPtr->FeeStatusFlags.FeeCurrSector;
  SectorInfoPtr = &StateDataPtr->FeeSectorInfo[BankNumber];
  if(SectorInfoPtr->Status.Dirty == (uint32)FEE_RESET)
  {
    BankNumber = BankNumber ^ FEE_SECTOR1;
    SectorInfoPtr = &StateDataPtr->FeeSectorInfo[BankNumber];
  }

  switch(StateDataPtr->FeeRepairStep)
  {
    case FEE_PROGRAM_MARKER:
      {
        StateDataPtr->FeeCurrSectSrcAddr = SectorInfoPtr->StatePageAddr;
        if (StateDataPtr->FeeIntrJobFailCount == FEE_RESET)
        {
          Fee_lClearFeeGcReadWriteBuffer();
          ReadWriteBuffPtr = StateDataPtr->FeeGcReadWriteBuffer;
          (void) Fls_17_Dmu_ReadWordsSync(
            (Fls_17_Dmu_AddressType)StateDataPtr->FeeCurrSectSrcAddr,
            /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing
             with FLS.FEE is passing parameters to FLS APIs.Changing this will
             break the interfacing and will cause major functional issues both
             on FLS and FEE side. */
            (uint32 *)ReadWriteBuffPtr,
            (Fls_17_Dmu_LengthType)(FEE_STATEPAGE_DATA_SIZE / FEE_DFLASH_WORD_SIZE));
          /*MISRA2012_RULE_18_4_JUSTIFICATION:This warning is for the core
          FEE structures which are containing the Block and sector info and
          affects the entire FEE functionality.Changing these would increase
          the risk of major functional impact on the entire FEE code,thereby
           putting the complete functionality of FEE at risk. */
        }
        Fee_lPrepareMarkerBuffer();

        ReadWriteBuffPtr = StateDataPtr->FeeGcReadWriteBuffer +
                           /*MISRA2012_RULE_18_4_JUSTIFICATION:This warning is
                            for the core FEE structures which are containing
                            the Block and sector info and affects the entire FEE
                           functionality.Changing these would increase the risk
                            of major functional impact on the entire FEE code,
                            thereby putting the complete functionality of FEE at
                            risk. */
                           FEE_STATEPAGE_DATA_SIZE;
        WriteLength = FEE_DFLASH_PAGE_SIZE;
        DestWriteAddress = StateDataPtr->FeeCurrSectSrcAddr +
                           FEE_STATEPAGE_DATA_SIZE;
        break;
      }

    /* remaining case FEE_PROGRAM_STATEPAGE */
    default:
      {
        while(Fee_lIsUnerasableAddr(SectorInfoPtr->NextFreeWLAddr) == TRUE)
        {

          (SectorInfoPtr->NextFreeWLAddr) += (FEE_DFLASH_WORDLINE_SIZE);
        }
        StateDataPtr->FeeCurrSectSrcAddr = SectorInfoPtr->NextFreeWLAddr;
        ReadWriteBuffPtr = StateDataPtr->FeeGcReadWriteBuffer;
        /* Update the new state page address and the next free WL address */
        SectorInfoPtr->StatePageAddr = StateDataPtr->FeeCurrSectSrcAddr;
        SectorInfoPtr->NextFreeWLAddr =
          Fee_lGetNextWLAddr(StateDataPtr->FeeCurrSectSrcAddr);
        WriteLength = FEE_STATEPAGE_PROGRAM_SIZE;
        DestWriteAddress = StateDataPtr->FeeCurrSectSrcAddr;
        break;
      }
  }/* END OF SWITCH */
  StateDataPtr->FeeIntrJob = FEE_WRITE_JOB;
  StateDataPtr->FeeIntrJobStatus = FEE_JOB_REQSTD;
  ReturnValueFls = Fls_17_Dmu_Write(DestWriteAddress,
                                    ReadWriteBuffPtr,
                                    (Fls_17_Dmu_LengthType)WriteLength);
  if(ReturnValueFls == E_NOT_OK)
  {
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
    StateDataPtr->FeeIntrJob = FEE_NO_JOB;
    Fee_lHandleInitGcFail();
  }
}


/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lINSM(void)                                 **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function implements the Init Normal State Machine which **
** detects the resumption point of the previously interrupted GC              **
*******************************************************************************/
/* [cover parentID={DD28E5F3-C60D-4fe1-AA91-FEDA8F328CBE}]
Fee_lINSM
[/cover] */
LOCAL_INLINE void Fee_lINSM(void)
{
  Fee_StateDataType  *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  switch (StateDataPtr->FeeGcResumeState)
  {
    /* Copy of Sector1 to Sector0 was ongoing */
    case FEE_INITGC_DATA_COPY_S1_S0:
      {
        StateDataPtr->FeeCurrSectSrcAddr = FEE_DFLASH_BANK1_BASE;
        StateDataPtr->FeeGcSrcAddr = FEE_DFLASH_BANK1_BASE;
        StateDataPtr->FeeGcDestAddr = FEE_DFLASH_BANK0_BASE;
        StateDataPtr->FeeGcState = FEE_GC_INIT_ERASE_PREV_SECTOR;

        break;
      }

    /* Copy of Sector0 to Sector1 was ongoing */
    case FEE_INITGC_DATA_COPY_S0_S1:
      {
        StateDataPtr->FeeCurrSectSrcAddr = FEE_DFLASH_BANK0_BASE;
        StateDataPtr->FeeGcSrcAddr = FEE_DFLASH_BANK0_BASE;
        StateDataPtr->FeeGcDestAddr = FEE_DFLASH_BANK1_BASE;
        StateDataPtr->FeeGcState = FEE_GC_INIT_ERASE_PREV_SECTOR;

        break;
      }

    /* Erase of Sector0 was ongoing */
    case FEE_INITGC_ERASE_S0:
      {
        StateDataPtr->FeeCurrSectSrcAddr = FEE_DFLASH_BANK1_BASE;
        StateDataPtr->FeeGcSrcAddr = FEE_DFLASH_BANK1_BASE;
        StateDataPtr->FeeGcDestAddr = FEE_DFLASH_BANK0_BASE;
        StateDataPtr->FeeGcState = FEE_GC_ERASE_PREV_SECTOR;

        break;
      }

    /* Erase of Sector1 was ongoing */
    case FEE_INITGC_ERASE_S1:
      {
        StateDataPtr->FeeCurrSectSrcAddr = FEE_DFLASH_BANK0_BASE;
        StateDataPtr->FeeGcSrcAddr = FEE_DFLASH_BANK0_BASE;
        StateDataPtr->FeeGcDestAddr = FEE_DFLASH_BANK1_BASE;
        StateDataPtr->FeeGcState = FEE_GC_ERASE_PREV_SECTOR;

        break;
      }

    /*
      Remaining normal cases:
        case FEE_INITGC_NORMAL_S1
        case FEE_INITGC_NORMAL_S0
    */
    default:
      {
        /* Set Garbage Collection state to Idle */
        StateDataPtr->FeeGcState = FEE_GC_IDLE;

        /* Update the FeeCurrSectSrcAddr */
        if(StateDataPtr->FeeStatusFlags.FeeCurrSector == (uint32)FEE_SECTOR0)
        {
          StateDataPtr->FeeCurrSectSrcAddr = FEE_DFLASH_BANK0_BASE;
        }
        else
        {
          StateDataPtr->FeeCurrSectSrcAddr = FEE_DFLASH_BANK1_BASE;
        }

        break;
      }
  }/* End Switch */

  /* Mark end of initialization */
  StateDataPtr->FeeInitGCState = FEE_INITGC_COMPLETE;
}


/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lIPrepDFlashSM(void)                        **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function implements the DFlash preparation State        **
** Machine which prepares an empty DFlash                                     **
*******************************************************************************/
/* [cover parentID={1004EDAC-5B40-4685-BB70-EB8A98D46DCA}]
Fee_lIPrepDFlashSM
[/cover] */
LOCAL_INLINE void Fee_lIPrepDFlashSM(void)
{
  const Fee_StateDataType  *StateDataPtr;
  const uint8              *BufferPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  switch(StateDataPtr->FeePrepDFLASHState)
  {
    case FEE_PREPDF_ERASE_S0:
    case FEE_PREPDF_ERASE_S1:
      {
        Fee_lHandleErasePrepDFLASH();
        break;
      }
    case FEE_PREPDF_MARK_S0_ERASED_SP:
      {
        /* Step1: Program first 120bytes of state page */
        if (StateDataPtr->FeeIntrJobFailCount == FEE_RESET)
        {
          Fee_lPrepareStatePageBuffer(FEE_SECTOR0, FEE_ERASED);
        }
        else
        {
          /* The state page is being re-attempted after one compare failure
             Clear the last 8bytes of GcReadWriteBuffer for comparison of SP */
          Fee_lClearMarkerBuffer();
        }
        /* State page data is prepared in the first 128 pages of RWBuffer */
        BufferPtr = StateDataPtr->FeeGcReadWriteBuffer;
        Fee_lHandleWritePrepDFLASH(BufferPtr);
        break;
      }
    case FEE_PREPDF_MARK_S0_VALID_SP:
      {
        /* Step1: Program first 120bytes of state page */
        if (StateDataPtr->FeeIntrJobFailCount == FEE_RESET)
        {
          Fee_lPrepareStatePageBuffer(FEE_SECTOR0, FEE_VALID);
        }
        else
        {
          /* The state page is being re-attempted after one compare failure
             Clear the last 8bytes of GcReadWriteBuffer for comparison of SP */
          Fee_lClearMarkerBuffer();
        }
        /* State page data is prepared in the first 128 pages of RWBuffer */
        BufferPtr = StateDataPtr->FeeGcReadWriteBuffer;
        Fee_lHandleWritePrepDFLASH(BufferPtr);
        break;
      }
    case FEE_PREPDF_MARK_S1_ERASED_SP:
      {
        /* Step1: Program first 120bytes of state page */
        if (StateDataPtr->FeeIntrJobFailCount == FEE_RESET)
        {
          Fee_lPrepareStatePageBuffer(FEE_SECTOR1, FEE_ERASED);
        }
        else
        {
          /* The state page is being re-attempted after one compare failure
             Clear the last 8bytes of GcReadWriteBuffer for comparison of SP */
          Fee_lClearMarkerBuffer();
        }
        /* State page data is prepared in the first 128 pages of RWBuffer */
        BufferPtr = StateDataPtr->FeeGcReadWriteBuffer;
        Fee_lHandleWritePrepDFLASH(BufferPtr);
        break;
      }
    /*
      Remaining cases:
        FEE_PREPDF_MARK_S0_ERASED_M
        FEE_PREPDF_MARK_S0_VALID_M
        FEE_PREPDF_MARK_S1_ERASED_M
    */
    default:
      {
        /* Step1: Program marker of state page */
        Fee_lPrepareMarkerBuffer();

        BufferPtr =&(StateDataPtr->FeeGcReadWriteBuffer[FEE_STATEPAGE_DATA_SIZE]);
                   
        Fee_lHandleWritePrepDFLASH(BufferPtr);
        break;
      }
  }/* END OF SWITCH */
}

/*CYCLOMATIC_Fee_lInitGCDSMTransHandler_JUSTIFICATION:
Fee_lInitGCDSMTransHandler has to pass through many for finding the compare 
failures and take the action accordingly.if it is broken into more functions, 
the readability will get affected.
*/

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lInitGCDSMTransHandler(void)                **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function shall handle the transitions required by the   **
** Init Dirty State Machine                                                   **
*******************************************************************************/
/* [cover parentID={3C7A1D9A-651A-4620-A87F-9970082C0112}]
Fee_lInitGCDSMTransHandler
[/cover] */
LOCAL_INLINE void Fee_lInitGCDSMTransHandler(void)
{
  Fee_StateDataType  *StateDataPtr;
  Fee_SectorInfoType *SectorInfoPtr;
  const uint8        *ReadWriteBuffPtr;
  uint32              BankNumber;
  uint32              EndAddr;
  Fls_17_Dmu_AddressType     DestAddr;
  Std_ReturnType      ReturnVal1;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  ReturnVal1   = E_OK;

  DestAddr = (Fls_17_Dmu_AddressType)StateDataPtr->FeeCurrSectSrcAddr;
  /* Get the active sector number */
  BankNumber =  StateDataPtr->FeeStatusFlags.FeeCurrSector;
  SectorInfoPtr = &StateDataPtr->FeeSectorInfo[BankNumber];
  /* Is active sector state page dirty and being repaired?
     If yes - BankNumber = active sector,
     else - Bank Number = other sector */
  if(SectorInfoPtr->Status.Dirty == (uint32)FEE_RESET)
  {
    BankNumber = BankNumber ^ FEE_SECTOR1;
    SectorInfoPtr = &StateDataPtr->FeeSectorInfo[BankNumber];
  }

  switch(StateDataPtr->FeeRepairStep)
  {
    case FEE_PROGRAM_MARKER:
      {
        /*Do compare only if PVER is not set*/
        if(StateDataPtr->FeeProgVerErr == FEE_RESET)
        {
          ReadWriteBuffPtr = StateDataPtr->FeeGcReadWriteBuffer;
          ReturnVal1 = Fls_17_Dmu_CompareWordsSync(
                       (Fls_17_Dmu_AddressType)DestAddr,
                       /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for
                       interfacing with FLS.FEE is passing parameters to FLS
                       APIs.Changing this will break the interfacing and will
                       cause major functional issues both on FLS and FEE side.*/
                       (const uint32 *)ReadWriteBuffPtr,
                       (Fls_17_Dmu_LengthType)
                       (FEE_STATEPAGE_SIZE / FEE_DFLASH_WORD_SIZE));
        }
        /* Compare failed or PVR bit set. Retry the Write operation */
        if((ReturnVal1 == E_NOT_OK) || 
           (StateDataPtr->FeeProgVerErr == FEE_SET))
        {
          /*Reset the FeeProgVerErr flag*/
          StateDataPtr->FeeProgVerErr = FEE_RESET;
          /* Compare failed for the first time */
          if(StateDataPtr->FeeIntrJobFailCount == FEE_RESET)
          {
            /* Check if there is space in the sector for state page */
            if(BankNumber == FEE_SECTOR0)
            {
              EndAddr = FEE_DFLASH_BANK0_BASE;
            }
            else
            {
              EndAddr = FEE_DFLASH_BANK1_BASE;
            }
            EndAddr = EndAddr +
                      (FEE_DFLASH_SECTOR_SIZE - FEE_DFLASH_WORDLINE_SIZE);
            if (SectorInfoPtr->NextFreeWLAddr > EndAddr)
            {
              /* No space - skip writing State Page and proceed */
              SectorInfoPtr->Status.Dirty = FEE_RESET;
              if ((StateDataPtr->FeeSectorInfo[0].Status.Dirty ==
                   (uint32)FEE_RESET) &&
                  (StateDataPtr->FeeSectorInfo[1].Status.Dirty ==
                   (uint32)FEE_RESET))
              {
                /* Go to Init Normal State Machine */
                StateDataPtr->FeeInitGCState = FEE_INITGC_NORMAL;
              }
              else
              {
                /* Other sector state page needs repair -
                   remain in the same state */
              }
            }
            else
            {
              StateDataPtr->FeeIntrJobFailCount++;
              StateDataPtr->FeeRepairStep = FEE_PROGRAM_STATEPAGE;
            }
          }
          /* Compare/write failed twice - enter Fail state*/
          else
          {
            Fee_lHandleInitGcFail();
          }
        }
        /* Repair successful */
        else
        {
          StateDataPtr->FeeIntrJobFailCount = FEE_RESET;
          SectorInfoPtr->Status.Dirty = FEE_RESET;
          if((StateDataPtr->FeeSectorInfo[0].Status.Dirty
              == (uint32)FEE_RESET) &&
              (StateDataPtr->FeeSectorInfo[1].Status.Dirty
               == (uint32)FEE_RESET))
          {
            /* Go to Init Normal State Machine */
            StateDataPtr->FeeInitGCState = FEE_INITGC_NORMAL;
          }
          else
          {
            /* Other sector state page needs repair -
               remain in the same state */
          }
        }
        break;
      }

    /* Remaining case FEE_PROGRAM_STATEPAGE */
    default:
      {
        
        /*Do compare only if PVER is not set*/
        if(StateDataPtr->FeeProgVerErr == FEE_RESET)
        {
          ReadWriteBuffPtr = StateDataPtr->FeeGcReadWriteBuffer;
          ReturnVal1 = Fls_17_Dmu_CompareWordsSync(
                       (Fls_17_Dmu_AddressType)DestAddr,
                       /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for
                       interfacing with FLS.FEE is passing parameters to FLS
                       APIs.Changing this will break the interfacing and will
                       cause major functional issues both on FLS and FEE side.*/
                       (const uint32 *)ReadWriteBuffPtr,
                       (Fls_17_Dmu_LengthType)
                       (FEE_STATEPAGE_DATA_SIZE / FEE_DFLASH_WORD_SIZE));
        }
        /* Check if compare failed twice or write retry failed due to PVER. If 
        yes then go to fail state */
        if((ReturnVal1 == E_NOT_OK) ||
          ((StateDataPtr->FeeProgVerErr == FEE_SET)))
        {
          /*Reset the FeeProgVerErr flag*/
          StateDataPtr->FeeProgVerErr = FEE_RESET;
          Fee_lHandleInitGcFail();
        }
        else
        {
          StateDataPtr->FeeRepairStep = FEE_PROGRAM_MARKER;
        }
        break;
      }
  }/* END OF SWITCH */
}

/*CYCLOMATIC_Fee_lInitGCPrepDFlSTransHandler_JUSTIFICATION:
Fee_lInitGCPrepDFlSTransHandler handles the transitions of GC state machines
If broken into more functions, the maintenance/readability  will get affected.
*/
/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lInitGCPrepDFlSTransHandler(void)           **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function shall handle the transitions required by the   **
** InitGC state machine during preparation of DFlash                          **
*******************************************************************************/
/* [cover parentID={B01B0434-2BE4-4779-97C8-B266F6F21AE5}]
Fee_lInitGCPrepDFlSTransHandler
[/cover] */
LOCAL_INLINE void Fee_lInitGCPrepDFlSTransHandler(void)
{
  Fee_StateDataType  *StateDataPtr;
  Fee_SectorInfoType *SectorInfoPtr0;
  Fee_SectorInfoType *SectorInfoPtr1;
  const uint8              *SrcAddr;
  uint32              DestAddr;
  uint8               PrepDFlashState;
  Std_ReturnType      ReturnVal1;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  StateDataPtr->FeeUnErasableWLCountTemp = FEE_RESET;
  StateDataPtr->FeeUnErasableWLAddrTemp[0] = FEE_RESET;
  StateDataPtr->FeeUnErasableWLAddrTemp[1] = FEE_RESET;
  SectorInfoPtr0 = &(StateDataPtr->FeeSectorInfo[0]);
  SectorInfoPtr1 = &(StateDataPtr->FeeSectorInfo[1]);

  PrepDFlashState = StateDataPtr->FeePrepDFLASHState;
  DestAddr = (Fls_17_Dmu_AddressType)(StateDataPtr->FeeCurrSectSrcAddr);
  ReturnVal1 = E_OK;

  /****** CASE FEE_PREPDF_ERASE_S0 ******************/
  if (PrepDFlashState == FEE_PREPDF_ERASE_S0)
  {
    ReturnVal1 = Fls_17_Dmu_VerifyErase((Fls_17_Dmu_AddressType)FEE_DFLASH_BANK0_BASE,
                                        &(StateDataPtr->FeeUnErasableWLAddrTemp[0]),
                                        &(StateDataPtr->FeeUnErasableWLCountTemp));

    /* Check if compare failed */
    if(ReturnVal1 == E_NOT_OK)
    {
      Fee_lHandleInitGcFail();
    }
    else
    {
      SectorInfoPtr0->UnerasableWLCount = StateDataPtr->FeeUnErasableWLCountTemp;
      SectorInfoPtr0->UnerasableWLAddr[0] =
        StateDataPtr->FeeUnErasableWLAddrTemp[0];
      SectorInfoPtr0->UnerasableWLAddr[1] =
        StateDataPtr->FeeUnErasableWLAddrTemp[1];
      StateDataPtr->FeeCurrSectSrcAddr = FEE_DFLASH_BANK1_BASE;
      PrepDFlashState = FEE_PREPDF_ERASE_S1;
    }
  }

  /****** CASE FEE_PREPDF_ERASE_S1 ******************/
  else if (PrepDFlashState == FEE_PREPDF_ERASE_S1)
  {
    ReturnVal1 = Fls_17_Dmu_VerifyErase((Fls_17_Dmu_AddressType)FEE_DFLASH_BANK1_BASE,
                                        &(StateDataPtr->FeeUnErasableWLAddrTemp[0]),
                                        &(StateDataPtr->FeeUnErasableWLCountTemp));
    /* Check if compare failed */
    if(ReturnVal1 == E_NOT_OK)
    {
      Fee_lHandleInitGcFail();
    }
    else
    {
      SectorInfoPtr1->UnerasableWLCount = StateDataPtr->FeeUnErasableWLCountTemp;
      SectorInfoPtr1->UnerasableWLAddr[0] =
        StateDataPtr->FeeUnErasableWLAddrTemp[0];
      SectorInfoPtr1->UnerasableWLAddr[1] =
        StateDataPtr->FeeUnErasableWLAddrTemp[1];
      StateDataPtr->FeeCurrSectSrcAddr = FEE_DFLASH_BANK0_BASE;
      PrepDFlashState = FEE_PREPDF_MARK_S0_ERASED_SP;
    }
  }

  /****** All other state page program cases******************/
  else
  {
    if(StateDataPtr->FeeProgVerErr == FEE_RESET)
    {
      SrcAddr = StateDataPtr->FeeGcReadWriteBuffer;
      ReturnVal1 = Fls_17_Dmu_CompareWordsSync(
                   (Fls_17_Dmu_AddressType)DestAddr,
                   /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for
                   interfacing with FLS.FEE is passing parameters to FLS APIs.
                   Changing this will break the interfacing and will cause major
                   functional issues both on FLS and FEE side.*/
                   (const uint32 *)SrcAddr,
                   (Fls_17_Dmu_LengthType)
                   (FEE_STATEPAGE_SIZE / FEE_DFLASH_WORD_SIZE));
    }               
    /* Compare failed or PVER error is set.*/
    if((ReturnVal1 == E_NOT_OK) || (StateDataPtr->FeeProgVerErr == FEE_SET))
    {
      StateDataPtr->FeeProgVerErr = FEE_RESET;
      /* Compare failed the first time */
      if(StateDataPtr->FeeIntrJobFailCount == FEE_RESET)
      {
        StateDataPtr->FeeIntrJobFailCount++;
        DestAddr = Fee_lGetNextWLAddr(DestAddr);
        DestAddr = Fee_lGetNextWLAddr(DestAddr);
        StateDataPtr->FeeCurrSectSrcAddr = DestAddr;

        switch (PrepDFlashState)
        {
          case FEE_PREPDF_MARK_S0_ERASED_SP:
          case FEE_PREPDF_MARK_S0_ERASED_M:
            {
              PrepDFlashState = FEE_PREPDF_MARK_S0_ERASED_SP;
              break;
            }
          case FEE_PREPDF_MARK_S0_VALID_SP:
          case FEE_PREPDF_MARK_S0_VALID_M:
            {
              PrepDFlashState = FEE_PREPDF_MARK_S0_VALID_SP;
              break;
            }

          /*
            Remaining cases:
              FEE_PREPDF_MARK_S1_ERASED_SP
              FEE_PREPDF_MARK_S1_ERASED_M
          */
          default:
            {
              PrepDFlashState = FEE_PREPDF_MARK_S1_ERASED_SP;
              break;
            }
        }
      }
      /* Compare failed/PVER error set twice */
      else
      {
        Fee_lHandleInitGcFail();
      } /* End of if if(StateDataPtr->FeeIntrJobFailCount == FEE_RESET) */
    }
    /* Compare successful */
    else
    {
      switch (PrepDFlashState)
      {
        case FEE_PREPDF_MARK_S0_ERASED_SP:
          {
            PrepDFlashState = FEE_PREPDF_MARK_S0_ERASED_M;
            break;
          }

        case FEE_PREPDF_MARK_S0_ERASED_M:
          {
            StateDataPtr->FeeIntrJobFailCount = FEE_RESET;
            DestAddr = Fee_lGetNextWLAddr(DestAddr);
            StateDataPtr->FeeCurrSectSrcAddr = DestAddr;
            PrepDFlashState = FEE_PREPDF_MARK_S0_VALID_SP;
            break;
          }

        case FEE_PREPDF_MARK_S0_VALID_SP:
          {
            PrepDFlashState = FEE_PREPDF_MARK_S0_VALID_M;
            break;
          }

        case FEE_PREPDF_MARK_S0_VALID_M:
          {
            StateDataPtr->FeeIntrJobFailCount = FEE_RESET;
            SectorInfoPtr0->StatePageAddr = DestAddr;
            DestAddr = Fee_lGetNextWLAddr(DestAddr);
            StateDataPtr->FeeNextFreePageAddr = DestAddr;
            SectorInfoPtr0->NextFreeWLAddr = DestAddr;
            StateDataPtr->FeeCurrSectSrcAddr = FEE_DFLASH_BANK1_BASE;
            PrepDFlashState = FEE_PREPDF_MARK_S1_ERASED_SP;
            break;
          }

        case FEE_PREPDF_MARK_S1_ERASED_SP:
          {
            PrepDFlashState = FEE_PREPDF_MARK_S1_ERASED_M;
            break;
          }

        /*
          Remaining case FEE_PREPDF_MARK_S1_ERASED_M
        */
        default:
          {
            StateDataPtr->FeeIntrJobFailCount = FEE_RESET;
            SectorInfoPtr1->StatePageAddr = DestAddr;
            DestAddr = Fee_lGetNextWLAddr(DestAddr);
            SectorInfoPtr1->NextFreeWLAddr = DestAddr;
            /* Set Garbage Collection state to Idle */
            StateDataPtr->FeeGcState = FEE_GC_IDLE;
            /* Mark end of initialization */
            StateDataPtr->FeeInitGCState = FEE_INITGC_COMPLETE;
            break;
          }
      }/* End of SWITCH */
    }/* End of if ( (ReturnVal1 == E_NOT_OK) || (ReturnVal1 == E_NOT_OK) )*/
  }

  StateDataPtr->FeePrepDFLASHState = PrepDFlashState;
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lInitGCTransHandler(void)                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function shall handle the transitions required by the   **
** InitGC state machine                                                       **
*******************************************************************************/
/* [cover parentID={59E06514-D891-4ce0-9084-6645DC6BF67B}]
Fee_lInitGCTransHandler
[/cover] */
LOCAL_INLINE void Fee_lInitGCTransHandler(void)
{
  Fee_StateDataType  *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /**********************************************************************/
  /*                1.AYSNC STATE MACHINE TRANSITIONS                   */
  /**********************************************************************/

  /* Is the Job finished i.e. Should the State machine Transition be made */
  if(StateDataPtr->FeeIntrJobStatus == FEE_JOB_DONE)
  {
    /* If the Job has failed because of other than PVER/EVER error then go to 
    init GC fail state*/
    if((StateDataPtr->FeeIntrJobResult == FEE_JOB_FAIL) && 
       (StateDataPtr->FeeProgVerErr  == FEE_RESET) &&
       (StateDataPtr->FeeEraseVerErr == FEE_RESET))
    {
      Fee_lHandleInitGcFail();
    }
    /* Job has passed */
    else
    {
      /***************** CASE 2: INITGC DIRTY STATE MACHINE ****************/
      if( StateDataPtr->FeeInitGCState == FEE_INITGC_HANDLE_DIRTY)
      {
        Fee_lInitGCDSMTransHandler();
      }/* End of FEE_INITGC_HANDLE_DIRTY */


      /***************** CASE 4: DFLASH PREPARATION STATE MACHINE *********/
      if(StateDataPtr->FeeInitGCState == FEE_INITGC_PREPARE_DFLASH)
      {
        Fee_lInitGCPrepDFlSTransHandler();
      } /* END OF IF (PREPARE_DFLASH) */
    }/* END OF JOB PASS check */
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
  }
  else
  {
    /* State Transition not required as no job was requested */
    /* Nothing to do */
  }
}

/*******************************************************************************
** TRACEABILITY: []                                                           **
********************************************************************************
** Syntax : static void Fee_lInitGC(void)                                     **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function shall detect if there was any interruption in  **
** the ongoing Garbage Collection procedure. If yes, then this routine shall  **
** get the DFLASH contents in the normal state.                               **
*******************************************************************************/
/* [cover parentID={3CA9D03E-7534-42a6-AC68-42F7510841A9},
{FB8B1E13-5374-4a91-90FE-0A9A984F338E}]
Fee_lInitGC
[/cover] */
static void Fee_lInitGC(void)
{
  Fee_StateDataType  *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /**********************************************************************/
  /*                1.AYSNC STATE MACHINE TRANSITIONS                   */
  /**********************************************************************/

  Fee_lInitGCTransHandler();

  /**********************************************************************/
  /*                       2.STATE MACHINE EXECUTION                    */
  /**********************************************************************/

  /***************** CASE 1: INITGC INVALID STATE MACHINE ********************/
   /* [cover parentID={674702C3-F543-4ada-B85E-BD04698BA3E9}]
INITGC INVALID STATE MACHINE
[/cover] */
  if(StateDataPtr->FeeInitGCState == FEE_INITGC_HANDLE_INVALID)
  {
    /* Check if DFLASH erase is enabled. if enabled go for DFLAS preparation
    with erase of DFLASH. Else go to illegal state  */
    if(Fee_CfgPtr->FeeEraseAllEnable == (boolean)TRUE)
    {
      StateDataPtr->FeeInitGCState = FEE_INITGC_PREPARE_DFLASH;
      StateDataPtr->FeePrepDFLASHState = FEE_PREPDF_ERASE_S0;
      StateDataPtr->FeeCurrSectSrcAddr = FEE_DFLASH_BANK0_BASE;
      StateDataPtr->FeeStateCount = FEE_RESET;
    }
    else
    { /* [cover parentID={F103A7E1-60A8-41c5-9C2C-B21BC4734F0F}]
Call the function to raise the init GC DEM and illegal notification and set the FeeInitGCState to fail 
[/cover] */
      /*Raise the init GC DEM and illegal notification and set the 
      FeeInitGCState to fail */
      Fee_lHandleInitGcFail();
    }
  }

  /***************** CASE 2: INITGC DIRTY STATE MACHINE ********************/

  if(StateDataPtr->FeeInitGCState == FEE_INITGC_HANDLE_DIRTY)
  {
    Fee_lIDSM();
  }

  /***************** CASE 3: INITGC NORMAL STATE MACHINE *******************/

  if(StateDataPtr->FeeInitGCState == FEE_INITGC_NORMAL)
  {
    Fee_lINSM();
  }

  /*********** CASE 4: DFLASH PREPARATION STATE MACHINE ********************/

  if( StateDataPtr->FeeInitGCState == FEE_INITGC_PREPARE_DFLASH)
  {
    /* Check if DFlash Preparation request came from Invalid or virgin state. */
    if( StateDataPtr->FeePrepDFLASHState == FEE_PREPDF_ERASE_S0)
    {
      /* DFlash Preparation request came from invalid state*/
      Fee_lIPrepDFlashSM();
    }
    else
    { 
      /* DFlash Preparation request came from virgin state.*/
#if (FEE_VIRGIN_FLASH_ILLEGAL_STATE == STD_OFF)
      Fee_lIPrepDFlashSM();
#else
      
      /* [cover parentID={F5542422-75D3-47bf-B931-2DD1BE426138}]
         [/cover] */
      /* [cover parentID={81E10AAF-3572-4e8d-924C-0698CACFB24F}]
Call the function to raise the init GC DEM and illegal notification and set the FeeInitGCState to fail
[/cover] */   
      /*Raise the init GC DEM and illegal notification and set the 
      FeeInitGCState to fail */
      Fee_lHandleInitGcFail();
#endif
    }
  }

}/*End of Fee_lInitGC */


/*******************************************************************************
** Syntax : static void Fee_lLastPgHandler(void)                              **
**                                                                            **
** Service ID:                                                                **
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
** Description : This routine will perform end of job handling activities     **
**    for Write, Invalidate requests                                          **
*******************************************************************************/
static void Fee_lLastPgHandler(void)
{
  Fee_StateDataType           *StateDataPtr;
  Fee_LastWrittenBlkInfoType  *LastBlkInfoPtr;
  Fee_CacheType               *BlkPtr;
  const Fee_BlockType         *BlockCfgPtr;
  uint32                       LWBMarkerAddress;
  uint32                       NextFreePageWLAddr;
  uint16                       BlockIndex;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  BlockIndex = Fee_lGetUsrBlockIndex(StateDataPtr->FeeCurrReqBlockNum);
  /*MISRA2012_RULE_18_4_JUSTIFICATION:This warning is for the core FEE
  structures which are containing the Block and sector info and affects the
  entire FEE functionality.Changing these would increase the risk of major
  functional impact on the entire FEE code,thereby putting the complete
  functionality of FEE at risk. */
  BlockCfgPtr = Fee_CfgPtr->FeeBlockConfigPtr + BlockIndex;
  BlkPtr = &(StateDataPtr->FeeBlockInfo[BlockIndex]);
  /*****************   UPDATE THE CACHE TABLE *********************/

  /* Update latest copy information in the cache table */
  BlkPtr->Address = StateDataPtr->FeeBlockStartAddr;
  BlkPtr->Status.Consistent = FEE_SET ;

  /* If Invalidate request was ongoing then reset the flag */
  if(StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus == (uint32)FEE_SET )
  {
    BlkPtr->Status.Valid = FEE_RESET;
  }
  else
  {
    BlkPtr->Status.Valid = FEE_SET ;
    BlkPtr->BlockSize = BlockCfgPtr->Size;
  }

  /* if Garbage Collection is pending */
  if(StateDataPtr->FeeGcState != FEE_GC_IDLE)
  {
    /*Check if the block was copied as part of GC already . If yes then
    copy the status .*/
    if((StateDataPtr->FeeGcState != FEE_GC_ERASE_PREV_SECTOR) &&
       (StateDataPtr->FeeGcState != FEE_GC_INIT_ERASE_PREV_SECTOR))
    {
      if(BlkPtr->Status.Copied != FEE_RESET)
      {
        BlkPtr->Status.PrevCopyCopied = FEE_SET ;
      }
      else
      {
        BlkPtr->Status.PrevCopyCopied = FEE_RESET;
      }
      BlkPtr->Status.Copied = FEE_RESET;
      StateDataPtr->FeeStatusFlags.FeeBlkModified = FEE_SET ; 
    }
  }

  /* Update Last written block information */
  LWBMarkerAddress = StateDataPtr->FeeNextFreePageAddr - FEE_DFLASH_PAGE_SIZE;
  NextFreePageWLAddr = Fee_lGetWLBeginning(StateDataPtr->FeeNextFreePageAddr);
  if(((StateDataPtr->FeeBlockStartAddr) < NextFreePageWLAddr) &&
      (LWBMarkerAddress >= NextFreePageWLAddr))
  {
    LastBlkInfoPtr = &(StateDataPtr->FeeLastWrittenBlkInfo);
    LastBlkInfoPtr->BlockNumber = StateDataPtr->FeeCurrReqBlockNum;
    LastBlkInfoPtr->PageCount = StateDataPtr->FeeBlkPageCount;
    LastBlkInfoPtr->Addr = StateDataPtr->FeeBlockStartAddr;
    LastBlkInfoPtr->Status.Consistent = FEE_SET ; /*Consistent = 1 */
  }

  /************** RESET/UPDATE GLOBAL VARIABLES USED *******************/
  StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_NO_REQ;
  StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus = FEE_RESET;
  StateDataPtr->FeeJobResult = MEMIF_JOB_OK;
  StateDataPtr->FeeUserJobFailCount = FEE_RESET;
  StateDataPtr->FeeBlkPageCount = FEE_RESET;

  if(StateDataPtr->FeeGcState != FEE_GC_REQUESTED)
  {
    /* Call user configured job End notification */
    if ( Fee_CfgPtr->FeeNvmJobEndNotification != NULL_PTR )
    {
      /* [cover parentID={008484B1-69EE-4726-93C3-2E367C5D61FB}]
Call the notification function
[/cover] */
      (Fee_CfgPtr->FeeNvmJobEndNotification)();
    }
  }
  else
  {
    /* Check if immediate data is written beyond threshold */
    if(StateDataPtr->FeeGCImmBlkWrite == TRUE)
    {
      /* Call user configured job End notification */
      if ( Fee_CfgPtr->FeeNvmJobEndNotification != NULL_PTR )
      {
        /* [cover parentID={4D8817D5-A123-46ff-A686-B0FA4DB492AB}]
Call the notification function
[/cover] */
        (Fee_CfgPtr->FeeNvmJobEndNotification)();
      }
      StateDataPtr->FeeGCImmBlkWrite = FALSE;
    }
    StateDataPtr->FeeMainJob = FEE_MAIN_GC;
  }

}/* End of Fee_lLastPgHandler */
#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lPrepareInvldReqBuff(                       **
**                                          const uint32 BlockCycleCount,     **
**                                          uint8 * const ReadWriteBuffPtr    **
**                                          const uint16 BlockIndex           **
**                                       )                                    **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockCycleCount : Block cycle count of block to be      **
**                                      written                               **
**                    ReadWriteBuffPtr : Buffer pointer used for invalidate   **
**                    BlockIndex : Index at which block details are           **
**                       stored in the Configuration Block Array              **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine will fill the read/write buffer with data       **
** for invalidation.                                                          **
*******************************************************************************/
LOCAL_INLINE void Fee_lPrepareInvldReqBuff(const uint32 BlockCycleCount,
    uint8 * const ReadWriteBuffPtr,
    const uint16 BlockIndex)
{
  Fee_StateDataType     *StateDataPtr;
  Fee_CacheType         *BlkPtr;
  uint16                 BlockNumber;
  uint32                 NewBlockCycleCount;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  BlockNumber = StateDataPtr->FeePendReqInfo.BlockNumber;
  StateDataPtr->FeeCurrReqBlockNum = BlockNumber;
  NewBlockCycleCount = BlockCycleCount + FEE_ONE;

  /* Compose the write buffer with page ID and other details */
  if(StateDataPtr->FeeBlkPageCount == FEE_BLOCK_HDR_PAGE)
  {
    /* First Page write */
    *(ReadWriteBuffPtr)  = FEE_DATA_FIRST_PAGE_ID;
    ReadWriteBuffPtr[1U] = (uint8)(BlockNumber);
    ReadWriteBuffPtr[2U] = (uint8)(BlockNumber >> FEE_EIGHT);
    ReadWriteBuffPtr[3U] = (uint8)(NewBlockCycleCount);
    ReadWriteBuffPtr[4U] = (uint8)(NewBlockCycleCount >> FEE_EIGHT);
    ReadWriteBuffPtr[5U] = (uint8)(NewBlockCycleCount >> FEE_SIXTEEN);
    ReadWriteBuffPtr[6U] = FEE_INVALID_BLOCK_LEN; /* Page length = 1 */
    /* Page length = 1, Valid bit zero */
    ReadWriteBuffPtr[7U] = FEE_INVALID_BLOCK;
    /* Push latest copy details of the block into Previous copy */
    /* Update previous copy information */
    BlkPtr = &(StateDataPtr->FeeBlockInfo[BlockIndex]);
    BlkPtr->Status.PrevCopyValid = BlkPtr->Status.Valid;
    BlkPtr->Status.PrevCopyConsistent = BlkPtr->Status.Consistent;
    BlkPtr->Status.PrevCopyCopied = BlkPtr->Status.Copied;
    BlkPtr->PrevCopyAddress = BlkPtr->Address;
    BlkPtr->PrevBlkSize = BlkPtr->BlockSize;

    /* Mark the block as inconsistent */
    BlkPtr->Status.Consistent = FEE_RESET;

    StateDataPtr->FeeBlkPageCount = FEE_SET ;
  }
  else
  {
    *(ReadWriteBuffPtr)  = FEE_DATA_MARKER_PAGE_ID;
    ReadWriteBuffPtr[1U] = FEE_DP_MARKER_BYTE_2;
    ReadWriteBuffPtr[2U] = FEE_DP_MARKER_BYTE_3;
    ReadWriteBuffPtr[3U] = FEE_DP_MARKER_BYTE_4;
    ReadWriteBuffPtr[4U] = (uint8)(BlockNumber);
    ReadWriteBuffPtr[5U] = (uint8)(BlockNumber >> FEE_EIGHT);
    /* Page length = 1, Valid bit zero */
    ReadWriteBuffPtr[6U] = FEE_INVALID_BLOCK_LEN;
    ReadWriteBuffPtr[7U] = FEE_INVALID_BLOCK; 

    StateDataPtr->FeeBlkPageCount = FEE_INVALID_BLOCK_PAGES;
  }
  StateDataPtr->FeeReadLen = FEE_DFLASH_PAGE_SIZE;
  StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_COMPARE;
}

/*******************************************************************************
** TRACEABILITY: []                                                           **
**                                                                            **
** Syntax : LOCAL_INLINE void Fee_lPrepareWriteReqBuff                        **
**                                        (                                   **
**                                           const uint32 BlockCycleCount,    **
**                                           uint8 * const ReadWriteBuffPtr   **
**                                           const uint16  BlockIndex,        **
**                                           const uint16 BlockSize           **
**                                        )                                   **
** [/cover]                                                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockCycleCount : Blk count of block to be written      **
**                    ReadWriteBuffPtr : Buffer Pointer to be filled for write**
**                    BlockIndex : Index at which block details are           **
**                       stored in the Configuration Block Array              **
**                    BlockSize : Size of the block to be written             **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine will fill the read write buffer with data       **
*******************************************************************************/
/* [cover parentID={1B0BEFCC-11AD-4518-BD83-ED8489F3E535},
{4CB52C85-7505-48aa-A652-ED1E1CB18AF9}]
Fee_lPrepareWriteReqBuff
[/cover] */
LOCAL_INLINE void Fee_lPrepareWriteReqBuff(const uint32 BlockCycleCount,
    uint8 * const ReadWriteBuffPtr,
    const uint16 BlockIndex,
    const uint16 BlockSize)
{
  Fee_StateDataType     *StateDataPtr;
  Fee_CacheType         *BlkPtr;
  const uint8       *DataBufferPtr;
  Fee_PageType           BlockPages_1;
  uint16                 DataByteCnt;
  uint16                 BlockNumber;
  uint8                  EndOfWLReached;
  uint32                 NewBlockCycleCount;

  EndOfWLReached = FEE_RESET;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  BlockNumber = StateDataPtr->FeePendReqInfo.BlockNumber;
  DataBufferPtr =
    ( const uint8*)StateDataPtr->FeePendReqInfo.DataWriteBufferPtr;

  NewBlockCycleCount = BlockCycleCount + FEE_ONE;
  BlockPages_1 = Fee_lGetDFLASHPages(BlockSize) - FEE_ONE;
  /* Update the block number */
  StateDataPtr->FeeCurrReqBlockNum = BlockNumber;

  /* Compose the write buffer with page ID and other details */
  if(StateDataPtr->FeeBlkPageCount == BlockPages_1)
  {

    *(ReadWriteBuffPtr)  = FEE_DATA_MARKER_PAGE_ID;
    ReadWriteBuffPtr[1U] = FEE_DP_MARKER_BYTE_2;
    ReadWriteBuffPtr[2U] = FEE_DP_MARKER_BYTE_3;
    ReadWriteBuffPtr[3U] = FEE_DP_MARKER_BYTE_4;
    ReadWriteBuffPtr[4U] = (uint8)(BlockNumber);
    ReadWriteBuffPtr[5U] = (uint8)(BlockNumber >> FEE_EIGHT);
    ReadWriteBuffPtr[6U] = (uint8)(BlockPages_1);
    ReadWriteBuffPtr[7U] = (uint8)((BlockPages_1 >> FEE_EIGHT)|(FEE_VALID_BIT));
    
    StateDataPtr->FeeBlkPageCount++;

    StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_COMPARE;
    StateDataPtr->FeeReadLen = FEE_PAGE1_DATA_OFFSET;
  }
  else
  {
    if(StateDataPtr->FeeBlkPageCount == FEE_BLOCK_HDR_PAGE)
    {
      /* First Page write */
      *(ReadWriteBuffPtr)  = FEE_DATA_FIRST_PAGE_ID;
      ReadWriteBuffPtr[1U] = (uint8)(BlockNumber);
      ReadWriteBuffPtr[2U] = (uint8)(BlockNumber >> FEE_EIGHT);
      ReadWriteBuffPtr[3U] = (uint8)(NewBlockCycleCount);
      ReadWriteBuffPtr[4U] = (uint8)(NewBlockCycleCount >> FEE_EIGHT);
      ReadWriteBuffPtr[5U] = (uint8)(NewBlockCycleCount >> FEE_SIXTEEN);
      ReadWriteBuffPtr[6U] = (uint8)(BlockPages_1);
      ReadWriteBuffPtr[7U] = (uint8)((BlockPages_1 >> FEE_EIGHT)|
                                     (FEE_VALID_BIT));

      StateDataPtr->FeeReadLen = FEE_PAGE1_DATA_OFFSET;
      /* Push latest copy details of the block into Previous copy */
      /* Update previous copy information */
      BlkPtr = &(StateDataPtr->FeeBlockInfo[BlockIndex]);
      BlkPtr->Status.PrevCopyValid = BlkPtr->Status.Valid;
      BlkPtr->Status.PrevCopyConsistent = BlkPtr->Status.Consistent;
      BlkPtr->Status.PrevCopyCopied = BlkPtr->Status.Copied;
      BlkPtr->PrevCopyAddress = BlkPtr->Address;
      BlkPtr->PrevBlkSize = BlkPtr->BlockSize;

      /* Mark the block as inconsistent */
      BlkPtr->Status.Consistent = FEE_RESET;

      StateDataPtr->FeeBlkPageCount++;


      if(Fee_lIsWLBeginning(StateDataPtr->FeeNextFreePageAddr +
                            StateDataPtr->FeeReadLen) ==
          FEE_NEW_WL_BEGIN)
      {
        EndOfWLReached = FEE_SET ;
        StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_COMPARE;

      }
    }

    if (EndOfWLReached == FEE_RESET)
    {
      /* Add data to the write buffer from the user specified pointer */
      DataByteCnt = StateDataPtr->FeeReadLen;
      do
      {
        if((StateDataPtr->FeeReadLen & FEE_SEVEN) == FEE_DATA_NEXT_PAGE_ID_POS)
        {
          ReadWriteBuffPtr[StateDataPtr->FeeReadLen] = FEE_DATA_NEXT_PAGE_ID;
          
          StateDataPtr->FeeBlkPageCount++;
          StateDataPtr->FeeReadLen++;
        }
        else
        {
          
          ReadWriteBuffPtr[StateDataPtr->FeeReadLen] = *(DataBufferPtr);
          StateDataPtr->FeeReadLen++;

          DataBufferPtr++;
          StateDataPtr->FeeUserWriteBytesCount++;
        }
      }
      while((Fee_lIsWLBeginning(StateDataPtr->FeeNextFreePageAddr +
                                StateDataPtr->FeeReadLen) != FEE_NEW_WL_BEGIN) &&
            (StateDataPtr->FeeUserWriteBytesCount != BlockSize) &&
            ((StateDataPtr->FeeReadLen - DataByteCnt) <
             (uint16)(FEE_WRITE_LEN_MAX)));


      /* If this is the last page being written for the write request */
      if(StateDataPtr->FeeUserWriteBytesCount == BlockSize)
      {
        /* If there is a scope for stuff bits(all-one) */
        while((StateDataPtr->FeeReadLen & FEE_SEVEN) != FEE_RESET)
        {
          ReadWriteBuffPtr[StateDataPtr->FeeReadLen] = FEE_RESET;
          StateDataPtr->FeeReadLen++;
        }
        StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_COMPARE;

      }
      /* If this is beginning of next word line */
      else if(Fee_lIsWLBeginning(StateDataPtr->FeeNextFreePageAddr +
                                 StateDataPtr->FeeReadLen) == FEE_NEW_WL_BEGIN)
      {
        StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_COMPARE;
      }
      else
      {
        /* dummy else to avoid MISRA */
      }

      /* Store the request parameters in last request buffer */
      StateDataPtr->FeePendReqInfo.DataWriteBufferPtr = DataBufferPtr;
    }
  }

} /* End of User Write req handling */

/*******************************************************************************
** Syntax : LOCAL_INLINE Std_ReturnType Fee_lCheckBlkCycleCnt(                **
**                                      const Fee_BlockType *const BlockPtr   **
**                                            const uint32 BlockCycleCount)   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockPtr                                                **
**                    BlockCycleCount                                         **
**                                                                            **
** Parameters (out):  Std_ReturnType                                          **
**                    E_NOT_OK: Block cycle count is reached to maximum limit **
**                    E_OK    : Block cycle count is within limit.            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine checks if the block cycle count of the          **
** requested user block has reached the configured maximum                    **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fee_lCheckBlkCycleCnt(
  const Fee_BlockType *const BlockPtr,
  const uint32 BlockCycleCount)
{
  Fee_StateDataType     *StateDataPtr;
  uint32                 CycleCountCfg;
  Std_ReturnType         RetVal;

  RetVal = E_OK;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  CycleCountCfg = BlockPtr->CycleCountLimit;

  /* If the cycle count limit is reached then
     report FEE_E_WRITE_CYCLES_EXHAUSTED to DEM  */
  if( (CycleCountCfg != FEE_RESET) && (BlockCycleCount == CycleCountCfg ))
  {
    /* [cover parentID={C316CEB1-87D8-4ba9-8419-77E9B94918D2}]
DEM enabled
[/cover] */
#if (FEE_WRITE_CYCLES_DEM_REPORT == FEE_ENABLE_DEM_REPORT)

    /* [cover parentID={80CD3675-1B2C-4a5f-A60A-86B40CA8B370}]
Report error to DEM FEE_E_WRITE_CYCLES_EXHAUSTED
[/cover] */
    Dem_ReportErrorStatus(FEE_E_WRITE_CYCLES_EXHAUSTED,
                          DEM_EVENT_STATUS_FAILED);
#endif

    StateDataPtr->FeeJobResult = MEMIF_JOB_FAILED;
    StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_NO_REQ;

    /* Clear the DFLASH access for FEE */
    if ( Fee_CfgPtr->FeeNvmJobErrorNotification != NULL_PTR )
    {
      /* [cover parentID={4A35611F-D07E-4e52-9B13-943732082C3C}]
Call the NVM job error notification function
[/cover] */
      (Fee_CfgPtr->FeeNvmJobErrorNotification)();
    }
    RetVal = E_NOT_OK;
  }

  return(RetVal);

}

#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lHandleUserWriteReq(                        **
**                                               const uint16 UserBlockIndex) **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  UserBlockIndex: Index of the requested block            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine handles the functionality of FEE_REQ_NORM_WRITE **
** / FEE_REQ_IMM_WRITE state of Write state machine                           **
*******************************************************************************/
LOCAL_INLINE void Fee_lHandleUserWriteReq(const uint16 UserBlockIndex)
{
  Fee_StateDataType           *StateDataPtr;
  const Fee_BlockType         *BlockPtr;
  uint8                       *PendReqStatePtr;
  Fee_LastWrittenBlkInfoType  *LastWrittenBlkPtr;
  uint32                       BlockCycleCount;
  uint32                       DestAddr;
  uint32                       TempAddr;
  uint32                       Index;
  uint16                       Offset;
  Fls_17_Dmu_LengthType               Length;
  Std_ReturnType               ReturnValue;

  BlockCycleCount = FEE_RESET;
  ReturnValue = E_OK;
  Length = FEE_RESET;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  BlockPtr = &(Fee_CfgPtr->FeeBlockConfigPtr[UserBlockIndex]);
  PendReqStatePtr = &(StateDataPtr->FeePendReqStatus);
  LastWrittenBlkPtr = &(StateDataPtr->FeeLastWrittenBlkInfo);
  if(StateDataPtr->FeeReadLen == (uint16)FEE_RESET)
  { 
    /* Read block cycle count */
    if (StateDataPtr->FeeBlockInfo[UserBlockIndex].Address != FEE_RESET)
    { 
     /* [cover parentID={EA1567CC-22C3-436a-BEE2-5A97E1D3EBC8}]
Get block cycle count
[/cover] */
      BlockCycleCount = Fee_lGetBlkCycleCount(UserBlockIndex);
    }
  /* [cover parentID={FFA81AE1-FFA8-4d8a-9867-773A52F73EAF}]
Check if block cycle count has reached the maximum and update flag status
[/cover] */
    /* Check if Block Cycle Count has reached the maximum */
    if (StateDataPtr->FeeUserJobFailCount == FEE_RESET)
    {
      ReturnValue = Fee_lCheckBlkCycleCnt(BlockPtr, BlockCycleCount);
    }

    if (ReturnValue != E_NOT_OK) /* If block cycle count not exceeded */
    {
      /* Check if request can be performed */
      ReturnValue = Fee_lPerformWriteCheck(BlockPtr);
    }
  }
  /* If write is to be started */
  if( ReturnValue == E_OK )
  {
    DestAddr = StateDataPtr->FeeNextFreePageAddr;

    /* If it is not a new word line and if previous data is consistent */
    if(Fee_lIsWLBeginning(DestAddr) != FEE_NEW_WL_BEGIN)
    {
      /* Read the previous page content to LastWrittenBlkBuff.
      This is used for comparison after the 1st page of current block is 
      written */
      TempAddr = Fee_lGetWLBeginning(DestAddr);
      Length = (Fls_17_Dmu_LengthType)(DestAddr & FEE_DFLASH_WORDLINE_SIZE_1);
      Length -= StateDataPtr->FeeReadLen;
      if(Length > FEE_WRITE_LEN_MAX)
      {
        Length = FEE_WRITE_LEN_MAX;
      }
      if(Length != (Fls_17_Dmu_LengthType)FEE_ZERO)
      {
        TempAddr += StateDataPtr->FeeReadLen;
        
       /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with FLS
       .FEE is passing parameters to FLS APIs. hanging this will break the
       interfacing and will cause major functional issues both on FLS and FEE 
       side.*/
        ReturnValue = Fls_17_Dmu_ReadWordsSync( \
                        (Fls_17_Dmu_AddressType)TempAddr,\
                        (uint32 *)(&(StateDataPtr->FeeLastWrittenBlkBuffer[\
                                                 StateDataPtr->FeeReadLen])),\
                        Length / FEE_DFLASH_WORD_SIZE);

        if(ReturnValue == E_NOT_OK)
        {
          StateDataPtr->FeeReadLen = FEE_RESET;
          Length = FEE_RESET;
          /* Update the Copied status so that the last page of the prev block
             is skipped from comparison */
          LastWrittenBlkPtr->Status.Consistent = FEE_RESET;
          LastWrittenBlkPtr->BlockNumber = FEE_RESET;
          DestAddr = Fee_lGetNextWLAddr(DestAddr);
          while (Fee_lIsUnerasableAddr(DestAddr) == TRUE)
          {

            DestAddr += (FEE_DFLASH_WORDLINE_SIZE);
          }
        }
        else
        {

          Offset = (uint16)(Length);
          Offset += StateDataPtr->FeeReadLen;
          /* Copy FeeLastWrittenBlkBuffer to ReadWriteBuffer
             for WL compare after first page write */
          for(Index = StateDataPtr->FeeReadLen; Index < Offset; Index++)
          {
            StateDataPtr->FeeReadWriteBuffer[Index] =
              StateDataPtr->FeeLastWrittenBlkBuffer[Index];
          } /* End of for(Index =0... */
          StateDataPtr->FeeReadLen += (uint16)(Length);
        } /* end of if(ReturnValue == E_NOT_OK) */
      }
    } /* end of if ( (Fee_lIsWLBeginning(DestAddr) != FEE_ZERO).. */

    /* initialize variables */
    if(Length == (Fls_17_Dmu_LengthType)FEE_ZERO)
    {
      StateDataPtr->FeeReadLen = FEE_RESET;
      StateDataPtr->FeeBlkPageCount = FEE_RESET;
      StateDataPtr->FeeUserWriteBytesCount = FEE_RESET;
      StateDataPtr->FeeBlockStartAddr = DestAddr;
      StateDataPtr->FeeNextFreePageAddr = DestAddr;
      *PendReqStatePtr = FEE_PEND_PREV_WRITE_REQ;
    }
  }
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lHandleUserWriteCompare                     **
**                                             (const uint16 UserBlockIndex)  **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  UserBlockIndex: Index of the requested block            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine handles the functionality of                    **
** FEE_PEND_PREV_COMPARE state of Write state machine                         **
*******************************************************************************/
LOCAL_INLINE void Fee_lHandleUserWriteCompare(const uint16 UserBlockIndex)
{
  Fee_StateDataType           *StateDataPtr;
  uint8                       *PendReqStatePtr;
  const Fee_BlockType         *BlockPtr;
  const Fee_LastWrittenBlkInfoType  *LastWrittenBlkPtr;
  uint32                       DestAddr;
  uint32                       TempAddr;
  Fls_17_Dmu_LengthType               CompareLength;
  Fls_17_Dmu_LengthType               TmpCompareLength;
  Std_ReturnType               ReturnValueFls;
  uint8                        Error;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  ReturnValueFls = E_OK;
  
  BlockPtr = &(Fee_CfgPtr->FeeBlockConfigPtr[UserBlockIndex]);
  LastWrittenBlkPtr = &(StateDataPtr->FeeLastWrittenBlkInfo);
  PendReqStatePtr = &(StateDataPtr->FeePendReqStatus);

  DestAddr = StateDataPtr->FeeNextFreePageAddr;
  /* Compare entire WL content */
  TempAddr = Fee_lGetWLBeginning(DestAddr);
  CompareLength = DestAddr - TempAddr;
  CompareLength += StateDataPtr->FeeLastWriteSize;
  TmpCompareLength = CompareLength;
  CompareLength -=  StateDataPtr->FeeComparedLen;
  if(CompareLength > FEE_COMPARE_LEN_MAX)
  {
    /* [cover parentID={1FF97F07-FEAA-44f8-9B78-29163F0AB006}]
    [/cover] */
  /* [cover parentID={1FF97F07-FEAA-44f8-9B78-29163F0AB006}]
Set the maximum value configured as the compare length
[/cover] */
    CompareLength = FEE_COMPARE_LEN_MAX;
  }

  if(StateDataPtr->FeeProgVerErr == FEE_RESET)
  {  
    /* [cover parentID={AF63CF49-94DA-4341-BB21-D6CA84E6950F}]
Check if the state page marker reprogrammed correctly by comparing marker written in a Flash with the intended marker value
[/cover] */
    /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with FLS.
    FEE is passing parameters to FLS APIs.Changing this will break the side.*/
    ReturnValueFls = Fls_17_Dmu_CompareWordsSync(\
                     (Fls_17_Dmu_AddressType)(TempAddr + \
                         StateDataPtr->FeeComparedLen),\
                     (uint32 *)(&(StateDataPtr->FeeReadWriteBuffer\
                     [StateDataPtr->FeeComparedLen])), \
                     (Fls_17_Dmu_LengthType)\
                    (CompareLength / FEE_DFLASH_WORD_SIZE));

    StateDataPtr->FeeComparedLen += (uint16)CompareLength;
  }
  /* Compare failed or PVER error set */
  if((ReturnValueFls == E_NOT_OK) || 
     (StateDataPtr->FeeProgVerErr == FEE_SET))
  {
    StateDataPtr->FeeComparedLen = FEE_RESET;
    /*Reset the FeeProgVerErr flag*/
    StateDataPtr->FeeProgVerErr = FEE_RESET;
    /* Compare failed /PVER error set  first time */
    if(StateDataPtr->FeeUserJobFailCount == FEE_RESET)
    {
      StateDataPtr->FeeUserJobFailCount++;
      StateDataPtr->FeeWriteAffectedAddr = StateDataPtr->FeeBlockStartAddr;
      /*Switch to next to next free WL*/
      TempAddr  = Fee_lGetNextWLAddr(DestAddr);
      TempAddr += FEE_DFLASH_WORDLINE_SIZE;
      StateDataPtr->FeeNextFreePageAddr = TempAddr;
      /* Point to the start of the user data buffer to re-write user block */

      StateDataPtr->FeePendReqInfo.DataWriteBufferPtr -=
        StateDataPtr->FeeUserWriteBytesCount;
      /* Last Written Block affected? */
      if(LastWrittenBlkPtr->Status.Consistent == (uint32)FEE_SET )
      {
        StateDataPtr->FeeWLAffectedType = FEE_LWB_ACROSS_WL_AFFECTED;
        /* Point to address of the affected previous block */
        StateDataPtr->FeeCurrSectSrcAddr = LastWrittenBlkPtr->Addr;
        StateDataPtr->FeeCurrReqBlockNum = LastWrittenBlkPtr->BlockNumber;
        /* Initialize variables for next write operation */
        StateDataPtr->FeeBlkPageCount = FEE_RESET;
        StateDataPtr->FeeBlockStartAddr = TempAddr;
        /* Move to Internal read */
        *PendReqStatePtr = FEE_PEND_INTR_READ;
      }
      else if(Fee_lIsLastWrittenWLAffected(FEE_ZERO) == (boolean)TRUE)
      {
        StateDataPtr->FeeWLAffectedType = FEE_LWB_WITHIN_WL_AFFECTED;
        /* Affected data is within the last written block buffer */
        /* Initialize variables */
        StateDataPtr->FeeBlkPageCount = FEE_RESET;
        StateDataPtr->FeeBlockStartAddr = TempAddr;
        /* Move to Internal read */
        *PendReqStatePtr = FEE_PEND_INTR_READ;
      }
      else
      {
        /* Re-write the current block */
        Fee_lRegisterWriteRequest(
          StateDataPtr->FeePendReqInfo.DataWriteBufferPtr,
          BlockPtr);
      }
    }
    /* Compare failed / PVER error set twice */
    else
    {
      /* Update Next Free Page Address to next to next free WL*/
      StateDataPtr->FeeNextFreePageAddr  = Fee_lGetNextWLAddr(DestAddr);
      StateDataPtr->FeeNextFreePageAddr += FEE_DFLASH_WORDLINE_SIZE;

      /* Handle job failure: Raise DEM and Job error notification */
      if(StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus
          == (uint32)FEE_SET )
      {
        StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus = FEE_RESET;
        Error = FEE_INVALIDATE;
      }
      else
      {
        Error = FEE_WRITE;
      }
      Fee_lHandleUsrJobFailure(Error); /* DEM & Job Error Notification */
    }
  }
  /* Compare Successful */
  else
  {
    if(StateDataPtr->FeeComparedLen == TmpCompareLength)
    {
      StateDataPtr->FeeComparedLen = FEE_RESET;
      StateDataPtr->FeeNextFreePageAddr += StateDataPtr->FeeLastWriteSize;
      /* Is it Invalidate request? */
      if((StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus
          == (uint32)FEE_SET ) &&
          (StateDataPtr->FeeBlkPageCount == FEE_INVALID_BLOCK_PAGES))
      {
        Fee_lLastPgHandler();
      }
      /* Write request - All pages written? */
      else if(StateDataPtr->FeeBlkPageCount ==
              Fee_lGetDFLASHPages((uint16)(BlockPtr->Size)))
      {
        Fee_lLastPgHandler();
      }
      else
      {
        *PendReqStatePtr = FEE_PEND_PREV_WRITE_REQ;
      }
    }
  }
}

/*******************************************************************************
** Syntax : static boolean Fee_lIsLastWrittenWLAffected(                      **
**                                                const uint16 StartOffset)   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  StartOffset - Offset                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  boolean                                                 **
**                                                                            **
** Description : This function checks if the last written word-line is        **
**               affected                                                     **
*******************************************************************************/
static boolean Fee_lIsLastWrittenWLAffected(const uint16 StartOffset)
{
  const Fee_StateDataType  *StateDataPtr;
  const uint8              *LWBBufferPtr;
  uint32              WLAddr;
  uint16              EndOffset;
  uint16              BlockNumber;
  boolean             RetVal;
  uint16              NewStartOffset;

  RetVal = (boolean)FALSE;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  LWBBufferPtr = &(StateDataPtr->FeeLastWrittenBlkBuffer[0]);
  EndOffset = (uint16)((StateDataPtr->FeeWriteAffectedAddr) &
                       FEE_DFLASH_WORDLINE_SIZE_1);
  NewStartOffset = (uint16)StartOffset;

  /* Check if any block header is present in the last written word-line */
  if(EndOffset > (uint16)FEE_DFLASH_PAGE_SIZE)
  {
    WLAddr = Fee_lGetWLBeginning(StateDataPtr->FeeWriteAffectedAddr);
    EndOffset -= FEE_DFLASH_PAGE_SIZE;
    do
    {
      /* if any block header is found */

      if(LWBBufferPtr[NewStartOffset] == (uint8)FEE_DATA_FIRST_PAGE_ID)
      {

        BlockNumber = ((uint16)(((uint16)LWBBufferPtr[NewStartOffset + FEE_BLOCK_NUM_MSB_POS]) <<
                                FEE_EIGHT) | ((uint16)LWBBufferPtr[NewStartOffset + FEE_BLOCK_NUM_LSB_POS]));
        /* check if the block and its address is in cache table */
        RetVal = Fee_lIsBlockAffected(BlockNumber, (WLAddr + NewStartOffset));
      }
      NewStartOffset += FEE_DFLASH_PAGE_SIZE;
    }
    while((NewStartOffset < EndOffset) && (RetVal == (boolean)FALSE));
  }

  return(RetVal);
}

/*******************************************************************************
** Syntax : LOCAL_INLINE boolean Fee_lIsBlockAffected(                        **
**                                                  const uint16 BlockNumber, **
**                                                  const uint32 BlockAddr)   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockNumber - Block Number                              **
**                    BlockAddr   - Block Address                             **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  boolean                                                 **
**                  TRUE : Block is affected due to write operation fail.     **
**                  Block entry is available in cache                         **
**                  FALSE: Block is not affected due to write operation fail. **
**                  Block entry is not available in cache                     **
** Description : This function checks if the block is affected                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE boolean Fee_lIsBlockAffected(const uint16 BlockNumber,
    const uint32 BlockAddr)
{
  Fee_StateDataType     *StateDataPtr;
  const Fee_CacheType         *CachePtr;
  const Fee_CacheType         *UnconfigBlockPtr;
  uint16 TempIndex;
  uint16 BlockIndex;
  boolean RetVal;

  RetVal = (boolean)FALSE;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  BlockIndex = Fee_lGetUsrBlockIndex(BlockNumber);
  if(BlockIndex == FEE_LOG_BLOCK_NOT_FOUND)
  {
    /* un-configured block */
    TempIndex = FEE_RESET;

    UnconfigBlockPtr = &(StateDataPtr->FeeBlockInfo[Fee_CfgPtr->FeeBlkCnt]);
 
    while((TempIndex < (StateDataPtr->FeeUnConfigBlockCount)) &&
          (RetVal == (boolean)FALSE))
    {

      /* check if the block and its address is in cache table */
      if((UnconfigBlockPtr->BlockNumber == BlockNumber) &&
          (UnconfigBlockPtr->Address == BlockAddr))
      {
        RetVal = (boolean)TRUE;
      }
      else
      {
        TempIndex++;
      }

      UnconfigBlockPtr++;
    }
  }
  else
  {
    CachePtr = &(StateDataPtr->FeeBlockInfo[BlockIndex]);
    /* check if the block and its address is in cache table */
    if(CachePtr->Address == BlockAddr)
    {
      RetVal = (boolean)TRUE;
    }
  }
  if(RetVal == (boolean)TRUE)
  {
    /* if the block and its address exists in cache table then, update the
       current request */
    StateDataPtr->FeeCurrReqBlockNum = BlockNumber;
    StateDataPtr->FeeCurrSectSrcAddr = BlockAddr;
  }

  return(RetVal);
}
#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** TRACEABILITY: []                                                           **
**                                                                            **
** Syntax : static void Fee_lHandleUserWrite(const uint16 UserBlockIndex)     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  UserBlockIndex: Index of the requested block            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine handles the functionality of                    **
** FEE_PEND_PREV_WRITE_REQ state of Write state machine                       **
*******************************************************************************/
/* [cover parentID={77B16520-BE1D-4f0a-B22A-954EE6B5E82F}]
Fee_lHandleUserWrite
[/cover] */
static void Fee_lHandleUserWrite(const uint16 UserBlockIndex)
{
  Fee_StateDataType     *StateDataPtr;
  const Fee_BlockType   *BlockPtr;
  uint8                 *ReadWriteBuffPtr;
  uint32                 DestAddr;
  uint32                 BlockCycleCount;
  uint16                 BlockSize;
  uint16                 Offset;
  Std_ReturnType         RetVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* [cover parentID={77B16520-BE1D-4f0a-B22A-954EE6B5E82F}]*/
  BlockPtr = &(Fee_CfgPtr->FeeBlockConfigPtr[UserBlockIndex]);
  BlockSize = (uint16)BlockPtr->Size;
  BlockCycleCount = FEE_RESET;

  /* Read block cycle count */
  if (StateDataPtr->FeeBlockInfo[UserBlockIndex].Address != FEE_RESET)
  {
    BlockCycleCount = Fee_lGetBlkCycleCount(UserBlockIndex);
  }

  DestAddr = StateDataPtr->FeeNextFreePageAddr;
  Offset = (uint16) (DestAddr & (uint32)FEE_DFLASH_WORDLINE_SIZE_1);
  if (Offset == FEE_ZERO)
  {

    /* Check against unersable WL*/
    while (Fee_lIsUnerasableAddr(DestAddr) == TRUE)
    {  /* [cover parentID={F6EC2232-5C32-4d13-9D94-D839BCCCF265}]
          Add WL size to next free page address and assign it to destination address
         [/cover] */
      
      DestAddr = Fee_lGetNextWLAddr(DestAddr);
    }
    StateDataPtr->FeeNextFreePageAddr = DestAddr;
    StateDataPtr->FeeLastWrittenBlkInfo.BlockNumber = FEE_RESET;
    StateDataPtr->FeeLastWrittenBlkInfo.Status.Consistent = FEE_RESET;
  }

  ReadWriteBuffPtr = &(StateDataPtr->FeeReadWriteBuffer[Offset]);

  /* if block invalidation is ongoing */
  if(StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus == (uint32)FEE_SET )
  {
    Fee_lPrepareInvldReqBuff(BlockCycleCount, ReadWriteBuffPtr, UserBlockIndex);
  }
  else
  {
    Fee_lPrepareWriteReqBuff(BlockCycleCount, ReadWriteBuffPtr,
                             UserBlockIndex, BlockSize);
  }
  if(StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_COMPARE)
  {

    StateDataPtr->FeeLastWriteSize = ((Fls_17_Dmu_LengthType)
                                      StateDataPtr->FeeReadLen);

    StateDataPtr->FeeUserJobStatus = FEE_JOB_REQSTD;

    /* Call Fls_17_Dmu_Write to write data in the DFLASH */
    RetVal = Fls_17_Dmu_Write((Fls_17_Dmu_AddressType)DestAddr,
                              (ReadWriteBuffPtr),
                              (Fls_17_Dmu_LengthType)(
                              StateDataPtr->FeeLastWriteSize));
    StateDataPtr->FeeReadLen = FEE_RESET;
    /* DET from FLS is not expected here */
    /* Hence, only check for Flash Sequence Error, Protection Error */
    /* In case of error, Fee_JobErrorNotification will be called */
    /* which would un-necessarily update FeeNextFreePageAddr */
    /* Hence the below code reverts FeeNextFreePageAddr back to its */
    /* original value */
    if(E_NOT_OK == RetVal)
    {
      StateDataPtr->FeeNextFreePageAddr -= StateDataPtr->FeeLastWriteSize;
    }
  }
}

/*CYCLOMATIC_Fee_lHandleIntrRead_JUSTIFICATION:
Fee_lHandleIntrRead has to pass through many states for interrupted read during
write,if it is broken into more functions, the readability will get affected.
*/
/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lHandleIntrRead(void)                       **
**                                                                            **
** Service ID:                                                                **
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
** Description : This routine handles the functionality of                    **
** FEE_PEND_INTR_READ state of Write state machine                            **
*******************************************************************************/
/* [cover parentID={50715C99-90C8-455f-B489-28C878A12B84}]
Fee_lHandleIntrRead
[/cover] */
LOCAL_INLINE void Fee_lHandleIntrRead(void)
{
  /* [cover parentID={50715C99-90C8-455f-B489-28C878A12B84}]*/
  Fee_StateDataType  *StateDataPtr;
  uint8              *ReadWriteBuffPtr;
  const uint8              *LWBBufferPtr;
  uint32              SrcAddr;
  uint32              AffectedWLAddr;
  uint32              SrcAddrNextWLAddr;
  uint16              Offset;
  uint16              ReadLength;
  uint16              ReadLengthInWL;
  uint16              TempIndex;
  uint16              RemainingPageCount;
  uint16              LWBPageCount;
  uint16              ReadLengthMax;
  Std_ReturnType      ReturnValueFls;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  AffectedWLAddr = Fee_lGetWLBeginning(StateDataPtr->FeeWriteAffectedAddr);
  SrcAddr = StateDataPtr->FeeCurrSectSrcAddr;
  Offset = (uint16)((StateDataPtr->FeeNextFreePageAddr) &
                    (uint32)FEE_DFLASH_WORDLINE_SIZE_1);
  if (Offset == FEE_ZERO)
  {
    Fee_lClearFeeReadWriteBuffer();
  }

  ReadWriteBuffPtr = &(StateDataPtr->FeeReadWriteBuffer[Offset]);
  ReadLengthMax = (uint16)FEE_DFLASH_WORDLINE_SIZE - Offset;

  /* if block(s) across the last written word line is affected */
  if(StateDataPtr->FeeWLAffectedType == FEE_LWB_ACROSS_WL_AFFECTED)
  {
    /* if current address is within the last written word line */
    if(SrcAddr >= AffectedWLAddr)
    {
      Offset = (uint16)(SrcAddr & (uint32)FEE_DFLASH_WORDLINE_SIZE_1);
      LWBBufferPtr = &(StateDataPtr->FeeLastWrittenBlkBuffer[0]);
      LWBPageCount = (uint16)(StateDataPtr->FeeLastWrittenBlkInfo.PageCount);
      RemainingPageCount = LWBPageCount - (uint16)StateDataPtr->FeeBlkPageCount;
      if(RemainingPageCount == FEE_ONE)
      {
        /* After marker write, change affected type to within word line */
        ReadLength = FEE_DFLASH_PAGE_SIZE;
        StateDataPtr->FeeWLAffectedType = FEE_LWB_WITHIN_WL_AFFECTED;
      }
      else
      {
        ReadLength = ((RemainingPageCount - FEE_ONE) << FEE_PAGE_TO_BYTE);
        if(ReadLengthMax < ReadLength)
        {
          ReadLength = ReadLengthMax;
        }
      }
      for(TempIndex = FEE_RESET; TempIndex < ReadLength; TempIndex++)
      {
        /* copy from last written block buffer to read-write buffer */

        ReadWriteBuffPtr[TempIndex] = LWBBufferPtr[TempIndex + Offset];
      }
      StateDataPtr->FeeCurrSectSrcAddr += ReadLength;
      StateDataPtr->FeePendReqStatus = FEE_PEND_INTR_WRITE;
    }
    else
    {
      /* if current address is before the last written word line */
      ReadLength = (uint16)FEE_DFLASH_WORDLINE_SIZE - Offset;
      SrcAddrNextWLAddr = Fee_lGetNextWLAddr(SrcAddr);
      ReadLengthInWL = (uint16)(SrcAddrNextWLAddr - SrcAddr);
      if(ReadLength > ReadLengthInWL)
      {
        if (((boolean)FALSE != Fee_lIsUnerasableAddr(SrcAddrNextWLAddr)) ||
            (SrcAddrNextWLAddr >= AffectedWLAddr))
        {
          ReadLength = ReadLengthInWL;
        }
      }

      /* copy from flash to read-write buffer */
      
      /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with FLS.
      FEE is passing parameters to FLS APIs, for example,
      Fls_17_Dmu_ReadWordsSync.Changing this will break the interfacing and will
      cause major functional issues both on FLS and FEE side. */
      ReturnValueFls = Fls_17_Dmu_ReadWordsSync(\
                         (Fls_17_Dmu_AddressType)SrcAddr,\
                         (uint32 *)ReadWriteBuffPtr,\
                         (Fls_17_Dmu_LengthType)\
                         ReadLength / FEE_DFLASH_WORD_SIZE);

      SrcAddr += ReadLength;

      while (Fee_lIsUnerasableAddr(SrcAddr) == TRUE)
      {
        SrcAddr = Fee_lGetNextWLAddr(SrcAddr);
      }
      StateDataPtr->FeeCurrSectSrcAddr = SrcAddr;

      if(ReturnValueFls == E_OK)
      {
        /* proceed to internal write */
        StateDataPtr->FeePendReqStatus = FEE_PEND_INTR_WRITE;
      }
      else
      {
        /* handle error */
        Fee_lHandleWriteFail();
      }
    }
  }
  else
  {
    /* if block(s) within the last written word line is affected */

    Offset = (uint16)(SrcAddr & (uint32)FEE_DFLASH_WORDLINE_SIZE_1);
    LWBBufferPtr = &(StateDataPtr->FeeLastWrittenBlkBuffer[0]);

    /* If last written block's marker copy pending */
    if(StateDataPtr->FeeWLAffectedType == FEE_LWB_MARKER_COPY_PENDING)
    {
      ReadLength = FEE_DFLASH_PAGE_SIZE;
      StateDataPtr->FeeWLAffectedType = FEE_LWB_WITHIN_WL_AFFECTED;
    }

    else if(StateDataPtr->FeeWLAffectedType == FEE_LWB_WITHIN_WL_AFFECTED)
    {
      StateDataPtr->FeeIntrCurrReqPageCount = (uint16)
                                              ((uint16)(LWBBufferPtr[Offset + FEE_SEVEN]) << FEE_EIGHT) |
                                              (LWBBufferPtr[Offset + FEE_SIX]);
      (StateDataPtr->FeeIntrCurrReqPageCount) &= ((uint16)FEE_PAGE_COUNT_MASK);
      ReadLength = (StateDataPtr->FeeIntrCurrReqPageCount) << FEE_PAGE_TO_BYTE;
      if(ReadLength > ReadLengthMax)
      {
        ReadLength = ReadLengthMax;
        StateDataPtr->FeeWLAffectedType = FEE_LWB_WITHIN_WL_AFFECTED_CONT;
      }
      else
      {
        StateDataPtr->FeeWLAffectedType = FEE_LWB_MARKER_COPY_PENDING;
      }
    }
    else /* FeeWLAffectedType == FEE_LWB_WITHIN_WL_AFFECTED_CONT */
    {
      ReadLength = (uint16)((StateDataPtr->FeeIntrCurrReqPageCount) -
                            (StateDataPtr->FeeBlkPageCount));
      ReadLength = (ReadLength << FEE_PAGE_TO_BYTE);

      StateDataPtr->FeeWLAffectedType = FEE_LWB_MARKER_COPY_PENDING;
    }

    /* copy from last written block buffer to read-write buffer */
    for(TempIndex = FEE_RESET; TempIndex < ReadLength; TempIndex++)
    {

      ReadWriteBuffPtr[TempIndex] = LWBBufferPtr[TempIndex + Offset];
    }
    StateDataPtr->FeeCurrSectSrcAddr = SrcAddr + ReadLength;
    StateDataPtr->FeePendReqStatus = FEE_PEND_INTR_WRITE;
  }

  StateDataPtr->FeeLastReadSize = ReadLength;
}

/*******************************************************************************
** Syntax : static void Fee_lHandleIntrWrite(void)                            **
**                                                                            **
** Service ID:                                                                **
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
** Description : This routine handles the functionality of                    **
** FEE_PEND_INTR_WRITE state of Write state machine                           **
*******************************************************************************/
/* [cover parentID={7646FA6A-066B-4036-BFC5-5832EEAA6FCC}]
Fee_lHandleIntrWrite
[/cover] */
static void Fee_lHandleIntrWrite(void)
{
  /* [cover parentID={7646FA6A-066B-4036-BFC5-5832EEAA6FCC}]*/
  Fee_StateDataType     *StateDataPtr;
  const uint8                 *ReadWriteBuffPtr;
  uint32                 DestAddr;
  uint16                 Offset;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  StateDataPtr->FeeLastWriteSize = StateDataPtr->FeeLastReadSize;
  DestAddr = StateDataPtr->FeeNextFreePageAddr;
  Offset = (uint16) (DestAddr & (uint32)FEE_DFLASH_WORDLINE_SIZE_1);

  /* Skip un-erasable word line, if any */
  if (Offset == FEE_ZERO)
  {
    while (Fee_lIsUnerasableAddr(DestAddr) == TRUE)
    {

      DestAddr = Fee_lGetNextWLAddr(DestAddr);
    }
    /* [cover parentID={62815483-801C-4c5a-A703-7AC69C8FB74F}]
Assign the destination address to next free page address
[/cover] */
    StateDataPtr->FeeNextFreePageAddr = DestAddr;
  }
  if(StateDataPtr->FeeBlkPageCount == FEE_ZERO)
  {
    /* [cover parentID={9989D3F6-A7A0-420d-AFF9-F4C842AA7D9C}]
Assign the block start address as destination address
[/cover] */
    StateDataPtr->FeeBlockStartAddr = DestAddr;
  }

  ReadWriteBuffPtr = &(StateDataPtr->FeeReadWriteBuffer[Offset]);
  StateDataPtr->FeeBlkPageCount +=
    (Fee_PageType)((StateDataPtr->FeeLastWriteSize) >> FEE_BYTE_TO_PAGE);
  StateDataPtr->FeeUserJobStatus = FEE_JOB_REQSTD;
  StateDataPtr->FeePendReqStatus = FEE_PEND_INTR_COMPARE;

  /* initiate FLS write */
  (void) Fls_17_Dmu_Write((Fls_17_Dmu_AddressType)DestAddr,
                          ReadWriteBuffPtr,
                          (Fls_17_Dmu_LengthType)
                          (StateDataPtr->FeeLastWriteSize));
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lHandleIntrWriteCompare                     **
**                                             (const uint16 UserBlockIndex)  **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  UserBlockIndex: Index of the requested block            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine handles the functionality of                    **
** FEE_PEND_INTR_COMPARE state of Write state machine                         **
*******************************************************************************/
/* [cover parentID={D902E00D-373D-4fe0-8187-30A6B19CBFE9}]
Fee_lHandleIntrWriteCompare
[/cover] */
LOCAL_INLINE void Fee_lHandleIntrWriteCompare(const uint16 UserBlockIndex)
{
  /* [cover parentID={D902E00D-373D-4fe0-8187-30A6B19CBFE9}]*/
  Fee_StateDataType     *StateDataPtr;
  uint8                 *PendReqStatePtr;
  const Fee_BlockType   *BlockPtr;
  Fee_CacheType         *UnconfigBlockPtr;
  uint32                DestAddr;
  uint32                TempAddr;
  uint16                BlockNumber;
  uint16                CompareLength;
  uint16                TmpCompareLength;
  uint32                StartOffset;
  uint16                UnconfigBlockIndex;
  Std_ReturnType        ReturnValueFls;
  boolean               RetVal;
  uint16                NewUserBlockIndex;
  RetVal = (boolean)FALSE;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  
  BlockPtr = &(Fee_CfgPtr->FeeBlockConfigPtr[UserBlockIndex]);
  UnconfigBlockPtr = &(StateDataPtr->FeeBlockInfo[Fee_CfgPtr->FeeBlkCnt]);
  PendReqStatePtr = &(StateDataPtr->FeePendReqStatus);
  ReturnValueFls = E_OK;
  
  DestAddr = StateDataPtr->FeeNextFreePageAddr;
  TempAddr = Fee_lGetWLBeginning(DestAddr);
  /* [cover parentID={4B7F1597-A85F-4b1c-AAF8-9661B6F9A753}]
Limit the length to be compared to maximum configured value
[/cover] */
  CompareLength = (uint16)((DestAddr + (StateDataPtr->FeeLastWriteSize)) -
                           TempAddr);
  TmpCompareLength = CompareLength;
  CompareLength -=  StateDataPtr->FeeComparedLen;
  if(CompareLength > FEE_COMPARE_LEN_MAX)
  {
    /* [cover parentID={4B7F1597-A85F-4b1c-AAF8-9661B6F9A753}]
    [/cover] */
    CompareLength = FEE_COMPARE_LEN_MAX;
  }
  /*Check PVR error is occurred in last write if yes then no need of compare */
  if(StateDataPtr->FeeProgVerErr == FEE_RESET)
  {
     /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with FLS.
     FEE is passing parameters to FLS APIs.Changing this will break the side.*/
    ReturnValueFls = Fls_17_Dmu_CompareWordsSync( \
                     (Fls_17_Dmu_AddressType)\
                     (TempAddr + StateDataPtr->FeeComparedLen),\
                     (uint32 *)(&(StateDataPtr->FeeReadWriteBuffer\
                     [StateDataPtr->FeeComparedLen])),\
                     ((Fls_17_Dmu_LengthType)
                     CompareLength / FEE_DFLASH_WORD_SIZE));

    StateDataPtr->FeeComparedLen += CompareLength;
  }
  /* Compare failed or PVR is set raise the illegal notification with write DEM 
   */
  if((ReturnValueFls == E_NOT_OK) || 
     (StateDataPtr->FeeProgVerErr == FEE_SET))
  {
    StateDataPtr->FeeComparedLen = FEE_RESET;
    Fee_lHandleWriteFail();
  }
  else if(StateDataPtr->FeeComparedLen != TmpCompareLength)
  {
    /*dummy else if to skip else for in between loops */
  }
  /* Compare successful */
  else
  {
    StateDataPtr->FeeComparedLen = FEE_RESET;
    /* Update cache table for previous block - both configured and unconfigured
       blocks needs only address update, the status remains the same */
    StartOffset = DestAddr & FEE_DFLASH_WORDLINE_SIZE_1;
    if((StateDataPtr->FeeLastWriteSize == FEE_EIGHT) &&
        ((StateDataPtr->FeeReadWriteBuffer[StartOffset]) ==
         FEE_DATA_MARKER_PAGE_ID))
    {
      BlockNumber = StateDataPtr->FeeCurrReqBlockNum;

      NewUserBlockIndex = Fee_lGetUsrBlockIndex(BlockNumber);
      if(NewUserBlockIndex != FEE_LOG_BLOCK_NOT_FOUND)
      {
        StateDataPtr->FeeBlockInfo[NewUserBlockIndex].Address =
          StateDataPtr->FeeBlockStartAddr;
      }
      else
      {
        UnconfigBlockIndex = FEE_RESET;
        while((UnconfigBlockIndex < (StateDataPtr->FeeUnConfigBlockCount)) &&
              (RetVal == (boolean)FALSE))
        {

          UnconfigBlockPtr = &(UnconfigBlockPtr[UnconfigBlockIndex]);
                             
          if((UnconfigBlockPtr->BlockNumber) == BlockNumber)
          {
            UnconfigBlockPtr->Address = StateDataPtr->FeeBlockStartAddr;
            RetVal = (boolean)TRUE;
          }
          else
          {
            UnconfigBlockIndex++;
          }
        }
      }
    }

    StateDataPtr->FeeNextFreePageAddr += (StateDataPtr->FeeLastWriteSize);
    *PendReqStatePtr = FEE_PEND_INTR_READ;

    /* if affected type is within the last written word line */
    if(StateDataPtr->FeeWLAffectedType == FEE_LWB_WITHIN_WL_AFFECTED)
    {
      StateDataPtr->FeeBlkPageCount = FEE_RESET;
      StartOffset = StateDataPtr->FeeCurrSectSrcAddr &
                    FEE_DFLASH_WORDLINE_SIZE_1;
      if(Fee_lIsLastWrittenWLAffected((uint16)(StartOffset)) == (boolean)FALSE)
      {
        /* Previous block is written, now write the current user requested block
          register write request */
        Fee_lRegisterWriteRequest(
          StateDataPtr->FeePendReqInfo.DataWriteBufferPtr,
          BlockPtr);
        StateDataPtr->FeeBlockStartAddr = StateDataPtr->FeeNextFreePageAddr;
      }
    }
  }
}

/*******************************************************************************
** Syntax : static void Fee_lLocalWrite(void)                                 **
**                                                                            **
** Service ID:                                                                **
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
** Description : This routine will perform the write operation on DFLASH. It  **
** is called by Fee_MainFunction                                              **
*******************************************************************************/
/*[cover parentID={5F758A15-CC83-4226-B568-5939E096E4B2}][/cover]*/
static void Fee_lLocalWrite(void)
{
  const Fee_StateDataType     *StateDataPtr;
  const uint8                 *PendReqStatePtr;
  uint16                 BlockNumber;
  uint16                 UserBlockIndex;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  BlockNumber = StateDataPtr->FeePendReqInfo.BlockNumber;
  UserBlockIndex = Fee_lGetUsrBlockIndex(BlockNumber);

  PendReqStatePtr = &(StateDataPtr->FeePendReqStatus);

  /**********************************************************************/
  /*                       2.STATE MACHINE EXECUTION                    */
  /**********************************************************************/

  /*********** CASE 1: USER WRITE REQSTD STATE *******************/
  if ((boolean)TRUE == Fee_lIsUserWriteInvldReqstd(StateDataPtr))
  {
    Fee_lHandleUserWriteReq(UserBlockIndex);
  }


  /*********** CASE: USER WRITE COMPARE STATE *******************/
  if(*PendReqStatePtr == FEE_PEND_PREV_COMPARE)
  {
    Fee_lHandleUserWriteCompare(UserBlockIndex);
  }

  /*********** CASE: USER WRITE ONGOING STATE *******************/
  if(*PendReqStatePtr == FEE_PEND_PREV_WRITE_REQ)
  {
    Fee_lHandleUserWrite(UserBlockIndex);
  }


  /*********** CASE: INTERNAL WRITE COMPARE STATE *******************/
  if (*PendReqStatePtr == FEE_PEND_INTR_COMPARE)
  {
    Fee_lHandleIntrWriteCompare(UserBlockIndex);
  }

  /*********** CASE: INTERNAL WRITE BLOCK READ STATE *******************/
  if (*PendReqStatePtr == FEE_PEND_INTR_READ)
  {
    Fee_lHandleIntrRead();
  }


  /*********** CASE: INTERNAL WRITE ONGOING STATE *******************/
  if (*PendReqStatePtr == FEE_PEND_INTR_WRITE)
  {
    Fee_lHandleIntrWrite();
  }
}/* End of Fee_lLocalWrite */

#endif
/*******************************************************************************
** Syntax : static void Fee_lRegisterWriteRequest(                            **
**                                   const uint8 * const DataWriteBufferPtr,  **
**                                   const Fee_BlockType * const BlockPtr)    **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in):  DataWriteBufferPtr -  Pointer to Data buffer             **
**                    BlockPtr - Pointer to block data structure              **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine will register the write request in the pending  **
** request buffer.                                                            **
*******************************************************************************/
/*[cover parentID={B498F3F5-2BF7-47e2-94BB-9E97DE112B78}] [/cover]*/
static void Fee_lRegisterWriteRequest(const uint8 * const DataWriteBufferPtr,
                                      const Fee_BlockType * const BlockPtr)
{
  Fee_StateDataType     *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  StateDataPtr->FeeStatusFlags.FeeWriteInvldAPICalled = FEE_SET ;
  StateDataPtr->FeeStatusFlags.FeeStartInitGC = FEE_SET ; /*TRUE*/

  /* if the logical block is of immediate in nature */
  if ( ( BlockPtr->FeeImmediateData == (uint32)FEE_IMMEDIATE_DATA ) &&
       /* This request is not for invalidation    */
       ( StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus
         == (uint32)FEE_RESET )
     )
  {

    StateDataPtr->FeePendReqStatus = FEE_REQ_IMM_WRITE;
  }
  else
  {
    StateDataPtr->FeePendReqStatus = FEE_REQ_NORM_WRITE;
  }

  /* [cover parentID={46A7C871-0E1F-4a3a-803D-E0BA815B03F5}]
Update the job result to MEMIF_JOB_PENDING
[/cover] */
  StateDataPtr->FeeJobResult = MEMIF_JOB_PENDING;
  /* [cover parentID={A31CEE06-AEE1-4063-812D-7BE780C3A9C4}]
Store the pending request parameters in the pending request buffer
[/cover] */
  /* Store the pending request parameters in the pending request buffer*/
  StateDataPtr->FeePendReqInfo.BlockNumber  = BlockPtr->BlockNumber;
  StateDataPtr->FeePendReqInfo.DataWriteBufferPtr = DataWriteBufferPtr;

  /* Update the current requested logical block number */
  StateDataPtr->FeeCurrReqBlockNum = BlockPtr->BlockNumber;
}/* End of Fee_lRegisterWriteRequest */
/* [cover parentID={3F9907AD-6E65-4d53-882A-1F19726962C7}]
NVM data block supported
[/cover] */
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** TRACEABILITY: []                                                           **
**                                                                            **
** Syntax : static void Fee_lLocalRead(void)                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine will perform the read operation on DFLASH. It   **
** is called by Fee_MainFunction                                              **
*******************************************************************************/
/* [cover parentID={2D9604F9-0837-4b8c-9F7B-22B3C0BE5ED8},
{83815BF6-33EE-45ff-AC9A-6D522CD1D384}]
Fee_lLocalRead
[/cover] */
static void Fee_lLocalRead(void)
{
  Fee_PendReqBufType   *PendReqPtr;
  Fee_StateDataType    *StateDataPtr;
  uint8                *DataBufferPtr;
  uint32                ActualAddr;

  uint16                ReadLength;
  uint16                BlockNumber;
  uint16                BlockOffset;
  uint16                Length;
  uint16                UserBlockIndex;
  uint16                DataByteCount;
  Std_ReturnType        ReturnValue;
  uint8                 LoopIndex;


  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  PendReqPtr = &StateDataPtr->FeePendReqInfo;
  BlockNumber = PendReqPtr->BlockNumber;
  BlockOffset = PendReqPtr->BlockOffset;
  DataBufferPtr = PendReqPtr->DataBufferPtr;
  DataByteCount = FEE_ONE;

  ReturnValue = E_OK;
  UserBlockIndex = Fee_lGetUsrBlockIndex(BlockNumber);

  /* [cover parentID={2D9604F9-0837-4b8c-9F7B-22B3C0BE5ED8}]*/
  /**********************************************************************/
  /*                1.AYSNC STATE MACHINE TRANSITIONS                   */
  /**********************************************************************/
  /*These transitions are handled in Fee_JobEndNotification and
    Fee_JobErrorNotification as specified by AUTOSAR*/


  /**********************************************************************/
  /*                       2.STATE MACHINE EXECUTION                    */
  /**********************************************************************/

  /*********** CASE 1: READ REQSTD STATE *******************/
  if((boolean)TRUE == Fee_lIsUserReadReqstd(StateDataPtr))
  {
    /*********************** PERFORM CHECKS START **********************/
    /* [cover parentID={D9445F4C-D14A-48d2-A91C-A6463D3D5F8B}]
Perform read check
[/cover] */
    ReturnValue = Fee_lPerformReadCheck(UserBlockIndex);

    /* [cover parentID={1FCDC8C5-DBAE-451c-A93D-D8237738A3C7}]
Call
[/cover] */
  if(ReturnValue == E_OK)
    {
      Fee_lperformStuffCheck(UserBlockIndex);
    }

    /* [cover parentID={18E22B35-ECF5-4a71-B0F7-8DEDB4362C85}]
Perform initial operations for local read
[/cover] */
    BlockOffset = Fee_lLocalReadStart(ReturnValue, UserBlockIndex);
    
    /*Chek if the job is finished*/
    if(StateDataPtr->FeeJobResult != MEMIF_JOB_PENDING)
    {
       /* set ReturnValue to E_NOT_OK. This will avoid further processing */ 
       ReturnValue = E_NOT_OK;
    }
  }

  /*********** CASE 2: READ REQSTD STATE *******************/

  StateDataPtr->FeeUserReadDestPtr = DataBufferPtr;

  /* PERFORM READ START */
  if (StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_READ_REQ)
  {
    if(BlockOffset > FEE_ZERO)
    {
      while(BlockOffset < FEE_SEVEN)
      {

        StateDataPtr->FeeUserReadDestPtr[0] =
          StateDataPtr->FeeReadWriteBuffer[DataByteCount + BlockOffset];
        BlockOffset++;

        StateDataPtr->FeeUserReadDestPtr++;
      }
      BlockOffset = FEE_RESET;
      DataByteCount += FEE_EIGHT;
    }
    while(DataByteCount < StateDataPtr->FeeLastReadSize)
    {
      for(LoopIndex = FEE_RESET; LoopIndex < FEE_SEVEN; LoopIndex++)
      {

        StateDataPtr->FeeUserReadDestPtr[LoopIndex] =
          StateDataPtr->FeeReadWriteBuffer[DataByteCount + LoopIndex];
      }
      /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
            array indexing used for FEE application buffers.
            Pointers are accessing the correct memory range locations.
            The access range is within the boundaries of the buffer. */
      StateDataPtr->FeeUserReadDestPtr += FEE_SEVEN;
      DataByteCount += FEE_EIGHT;
    }
  }

  if (((ReturnValue == E_OK) &&
       (StateDataPtr->FeePendReqStatus != FEE_PEND_PREV_NO_REQ)) ||
      (StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_READ_REQ)
     )
  {
    /* [cover parentID={C2FAE471-2275-4229-8D16-88623013D999}]
Calculate actual address where data is needed to be read
(current sector source address)
[/cover] */
    /* calculate actual address where data is needed to be read */
    ActualAddr = StateDataPtr->FeeCurrSectSrcAddr;


    /*Store the block offset in pending buffer structure*/

    PendReqPtr->BlockOffset = BlockOffset;
    Length = PendReqPtr->Length;

    ReadLength = Fee_lCheckReadLength(ActualAddr, Length);

    Fee_lClearFeeReadWriteBuffer();

    StateDataPtr->FeeLastReadSize = (Fls_17_Dmu_LengthType)ReadLength;

    (void) Fls_17_Dmu_Read((Fls_17_Dmu_AddressType)ActualAddr,
                           StateDataPtr->FeeReadWriteBuffer,
                           (Fls_17_Dmu_LengthType)ReadLength);
    /* Return value above is ignored */

    StateDataPtr->FeeCurrReqBlockNum = BlockNumber;

    /* If the current request is set to previous pending */
    if(StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_READ_REQ)
    {
      /* Increment FeeCurrSectSrcAddr to point to next page */

      ActualAddr += ReadLength;
      while (Fee_lIsUnerasableAddr(ActualAddr) == TRUE)
      {
        ActualAddr = Fee_lGetNextWLAddr(ActualAddr);
      }
      StateDataPtr->FeeCurrSectSrcAddr = ActualAddr;
    }

    /* Store the read request parameters in the Pending buffer structure */
    PendReqPtr->BlockOffset = BlockOffset;
    /* PendReqPtr->Length = Length;*/
    PendReqPtr->DataBufferPtr = StateDataPtr->FeeUserReadDestPtr;
    /* PERFORM READ ENDS */
  }
}/* End of Fee_lLocalRead */


/*******************************************************************************
** TRACEABILITY: []                                                           **
**                                                                            **
** Syntax : static uint16 Fee_lCheckReadLength(const Fls_17_Dmu_AddressType   **
**                                               ActualAddr,                  **
**                                               const uint16 Length)         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  ActualAddr - Address of read location                   **
**                    Length     -  Length to be read                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Actual Read length for reading data from flash.         **
**                                                                            **
** Description : This routine will perform the check of the read length       **
**                                                                            **
*******************************************************************************/
static uint16 Fee_lCheckReadLength(const Fls_17_Dmu_AddressType ActualAddr,
                                   const uint16 Length)
{
  Fee_StateDataType    *StateDataPtr;
  Fee_PendReqBufType   *PendReqPtr;
  uint8                 ReadLengthPages;
  uint16                ReadLimit;
  uint16                ReadLength;
  uint16                LengthChk;
  uint16                BlockOffset;
  uint16                BlockNumber;
  uint16                SizeInCurrentWL;
  uint32                TempAddress;
  uint16                DflashBlkSize;
  uint16                UserBlockIndex;
  uint16                NewLength;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  PendReqPtr = &StateDataPtr->FeePendReqInfo;
  BlockOffset = PendReqPtr->BlockOffset;
  BlockNumber = PendReqPtr->BlockNumber;
  NewLength = (uint16)Length;
  UserBlockIndex = Fee_lGetUsrBlockIndex(BlockNumber);
  
#if (FEE_GET_PREV_DATA_API == STD_ON)
  if(StateDataPtr->FeePendReqInfo.GetPrevCopy == FEE_SET )
  {
    DflashBlkSize = (uint16)StateDataPtr->
                    FeeBlockInfo[UserBlockIndex].PrevBlkSize;
  }
  else
#endif
  {
    DflashBlkSize =(uint16)StateDataPtr->
    FeeBlockInfo[UserBlockIndex].BlockSize;
  }
 
  if(Fee_lIsWLBeginning(ActualAddr) == FEE_NEW_WL_BEGIN)
  {
    ReadLimit = FEE_DATA_BYTES_IN_WORDLINE;
  }
  else
  {
    SizeInCurrentWL = (uint16)FEE_DFLASH_WORDLINE_SIZE -
                      (uint16)(ActualAddr & FEE_DFLASH_WORDLINE_SIZE_1);
    ReadLimit = (SizeInCurrentWL >> FEE_BYTE_TO_PAGE) * FEE_SEVEN;
  }

  if (Length > (ReadLimit - BlockOffset))
  {
    if(Fee_lIsWLBeginning(ActualAddr) != FEE_NEW_WL_BEGIN)
    {
      TempAddress = Fee_lGetNextWLAddr(ActualAddr);
      if((boolean)FALSE == Fee_lIsUnerasableAddr(TempAddress))
      {
        ReadLimit = FEE_DATA_BYTES_IN_WORDLINE;
      }
    }
  }

  ReadLimit = ReadLimit - BlockOffset;
  if (Length > ReadLimit)
  {
    ReadLength = ReadLimit;
    NewLength = Length - ReadLimit;
    StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_READ_REQ;
  }
  else
  {
    if (Length > DflashBlkSize)
    {
      LengthChk = DflashBlkSize;
      ReadLength = LengthChk;
    }
    else
    {
      ReadLength = Length;
    }
    StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_READ_NOTIF;
  }

  /* Call Fls_Read to read the data from DFLASH */
  StateDataPtr->FeeUserJobStatus = FEE_JOB_REQSTD;

  if((ReadLength + BlockOffset) > FEE_SEVEN)
  {
    ReadLength = ReadLength - (FEE_SEVEN - BlockOffset);
    if (NewLength > DflashBlkSize)
    {
      ReadLengthPages = (uint8)Fee_lGetDFLASHPages(ReadLength) - FEE_TWO;
    }
    else
    {
      ReadLengthPages = (uint8)Fee_lGetDFLASHPages(ReadLength) - FEE_ONE;
    }
  }
  else
  {
    ReadLengthPages = (uint8)Fee_lGetDFLASHPages(ReadLength) - FEE_TWO;
  }

  ReadLength = (uint16)ReadLengthPages << FEE_PAGE_TO_BYTE;
  PendReqPtr->Length = NewLength;

  return (ReadLength);
}/*End of Fee_lCheckReadLength*/


/*******************************************************************************
** Syntax : LOCAL_INLINE uint16 Fee_lLocalReadStart                           **
**                                        (const Std_ReturnType ReturnValue,  **
**                                              const uint16 UserBlockIndex)  **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  ReturnValue - Return value of Fee_lPerformReadCheck     **
**                    UserBlockIndex - User block index                       **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  uint16 - Block Offset                                   **
**                                                                            **
** Description : This routine will perform the initial operations of          **
**               Fee_lLocalRead()                                             **
*******************************************************************************/
LOCAL_INLINE uint16 Fee_lLocalReadStart(const Std_ReturnType ReturnValue,
                                        const uint16 UserBlockIndex)
{
  const Fee_PendReqBufType   *PendReqPtr;
  Fee_StateDataType    *StateDataPtr;
  uint32                StartAddr;
  uint16                BlockOffset;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  PendReqPtr = &StateDataPtr->FeePendReqInfo;
  BlockOffset = PendReqPtr->BlockOffset;

  if(ReturnValue == E_NOT_OK )
  {
    /*Check if QS erase was suspended. If yes then set FeePendReqStatus to
     FEE_REQ_QUASI_ERASE to set module status to busy.*/
#if((FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA ) && \
    (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON))
    if(StateDataPtr->FeeQsEraseSuspend == FEE_ERASE_SUSPENDED)
    {
      StateDataPtr->FeePendReqStatus = FEE_REQ_QUASI_ERASE;
      StateDataPtr->FeeQsJob = FEE_ERASE_JOB;
    }
    else
#endif
    {
      StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_NO_REQ;
    }

    if ( Fee_CfgPtr->FeeNvmJobErrorNotification != NULL_PTR )
    {
      /* [cover parentID={7E0A6A25-41BA-4a6e-9758-B1AB3941C27D}]
Call the notification function
[/cover] */
      (Fee_CfgPtr->FeeNvmJobErrorNotification)();
    }
  }
  /* ReturnValue is E_OK here */
  else
  {
    /* Load the start address of the block */
#if (FEE_GET_PREV_DATA_API == STD_ON)
    if(PendReqPtr->GetPrevCopy == FEE_SET )
    {
      StartAddr = (StateDataPtr->FeeBlockInfo[UserBlockIndex].PrevCopyAddress)
                  + FEE_DFLASH_PAGE_SIZE;
    }
    else
#endif
    {
      StartAddr = (StateDataPtr->FeeBlockInfo[UserBlockIndex].Address)
                  + FEE_DFLASH_PAGE_SIZE;
    }

    /*Calculate the address of data page using block offset.Read will be
    start from this page. */

    do
    {
      if(Fee_lIsWLBeginning(StartAddr) == FEE_NEW_WL_BEGIN)
      {
        while (Fee_lIsUnerasableAddr(StartAddr) == TRUE)
        {
          StartAddr = Fee_lGetNextWLAddr(StartAddr);
        }
      }
      if (BlockOffset >= FEE_SEVEN)
      {
        StartAddr += FEE_DFLASH_PAGE_SIZE;
        BlockOffset -= FEE_SEVEN;
      }
    }
    while(BlockOffset >= FEE_SEVEN);

    StateDataPtr->FeeCurrSectSrcAddr = StartAddr;
  }

  return(BlockOffset);
}

/******************************************************************************
** Syntax : static void Fee_lGCErrorHandler(const uint8 Error                **
**                                            const uint16 Index)            **
**                                                                           **
** Service ID:                                                               **
**                                                                           **
** Sync/Async:  Synchronous                                                  **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) :  uint8  Error                                           **
**                    uint16 Block index in cache table                      **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  None                                                   **
**                                                                           **
** Description : This routine is responsible for handling GC transitions     **
**               in case of errors.                                          **
******************************************************************************/
/* [cover parentID={3F9907AD-6E65-4d53-882A-1F19726962C7}]
NVM data block supported
[/cover] */
static void Fee_lGCErrorHandler(const uint8 Error , const uint16 Index)
{
  Fee_StateDataType  *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  switch(Error)
  {
    /* Write Failure */
    case FEE_GC_WRITE:
      {
        /* [cover parentID={977693FB-9D15-4328-9118-281929FCDA91}]
DEM enabled
[/cover] */
        /* Report Dem */
#if (FEE_GC_WRITE_DEM_REPORT == FEE_ENABLE_DEM_REPORT)

        /* [cover parentID={625A4011-7623-4fb7-998D-4E6038401297}]
Report write error to DEM FEE_E_GC_WRITE
[/cover] */
        Dem_ReportErrorStatus(FEE_E_GC_WRITE, DEM_EVENT_STATUS_FAILED);
#endif
        Fee_lHandleGcFail();
        break;
      }

    /* Read Failure */
    case FEE_GC_READ:
      {
        /* [cover parentID={82304E5E-B10F-41b2-99CB-9168EE0163DF}]
DEM enabled
[/cover] */
    /* Report Dem */
#if (FEE_GC_READ_DEM_REPORT == FEE_ENABLE_DEM_REPORT)

        /* [cover parentID={37FED89C-E60B-4289-99CC-D1480A538B50}]
Report read error to DEM FEE_E_GC_READ
[/cover] */
        Dem_ReportErrorStatus(FEE_E_GC_READ, DEM_EVENT_STATUS_FAILED);
#endif
        if((StateDataPtr->FeeGcState == FEE_GC_UNCFG_START_COPY) || 
          (StateDataPtr->FeeGcState == FEE_GC_UNCFG_COPY_READ_NXTPAGE))
          {
            /* GC in unconfigured block copy state ,discard the current 
            unconfigured block and continue GC*/
            Fee_lGcDiscardUnconfigBlk(Index);
            StateDataPtr->FeeGcState = FEE_GC_UNCFG_START_COPY;
          }
          else
          {
            /* GC in configure block copy state ,discard the current configured
             block and continue GC*/
            Fee_lGcDiscardConfigBlk(Index);
            StateDataPtr->FeeGcState = FEE_GC_START_COPY;  
          }
        break;
      }

    /* Erase Failure */
    case FEE_GC_ERASE:
      {
        /* Report Dem */
#if (FEE_GC_ERASE_DEM_REPORT == FEE_ENABLE_DEM_REPORT)

        /* [cover parentID={8DD26F81-EE1C-448f-93C1-5C8BC9E3C417}]
Report erase error to DEM FEE_E_GC_ERASE
[/cover] */
        Dem_ReportErrorStatus(FEE_E_GC_ERASE, DEM_EVENT_STATUS_FAILED);
#endif
        Fee_lHandleGcFail();
        break;
      }

    /* GC Trig failure - a case where the Gc triggers another Gc */
    default:
      {
        /* [cover parentID={82304E5E-B10F-41b2-99CB-9168EE0163DF}]
        DEM enabled
        [/cover] */
        /* Report Dem */
#if (FEE_GC_TRIG_DEM_REPORT == FEE_ENABLE_DEM_REPORT)

        /* [cover parentID={65B83B6F-AB0F-4a30-B718-3183A9FA7E2C}]
Report to DEM on account of GC trigger failure FEE_E_GC_TRIG
[/cover] */
        Dem_ReportErrorStatus(FEE_E_GC_TRIG, DEM_EVENT_STATUS_FAILED);
#endif
        Fee_lHandleGcFail();
        break;
      }
  }

 
}/*End of Fee_lGCErrorHandler */

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lHandleGcFail(void)                     **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function shall handle the severe error case or          **
** internal job fail case during Garbage collection                           **
*******************************************************************************/
LOCAL_INLINE void Fee_lHandleGcFail(void)
{
  Fee_StateDataType     *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* Enter GC Fail state */
  StateDataPtr->FeeGcState = FEE_GC_FAIL;
  /* [cover parentID={5B785984-4A46-4d77-A92C-F7F5C38E8602}]
Is illegal state notification configured?
[/cover] */
  /* Raise Illegal state notification if configured */
  if(Fee_CfgPtr->FeeNvmIllegalStateNotification != NULL_PTR)
  {
    /* [cover parentID={7D8E6AA9-44D9-4f7f-8BE8-D7B5F5DABABC}]
Call the notification function
[/cover] */
    /* Call the Notification function */
    Fee_CfgPtr->FeeNvmIllegalStateNotification();
  }
}

/******************************************************************************
** Syntax : static void Fee_lGcRead(const Fls_17_Dmu_AddressType Position,   **
**                                  const uint16 Offset)                     **
**                                                                           **
** Service ID:                                                               **
**                                                                           **
** Sync/Async:  Asynchronous                                                 **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) :(uint32)  Position: Dflash Addr to read from             **
**                  (uint16) Offset: Offset of read write buffer             **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  None                                                   **
**                                                                           **
** Description : Gives a read request during Gc                              **
******************************************************************************/
static void Fee_lGcRead(const Fls_17_Dmu_AddressType Position,
                        const uint16 Offset)
{
  Fee_StateDataType    *StateDataPtr;
  uint8                *GcReadWriteBufferPtr;
  Fee_PageType          PendingPageCount;
  Fls_17_Dmu_LengthType        ReadLength;
  uint32                PendingBlockSize;
  uint16                GcSrcAddrOffset;
  uint8               Error;
  uint16              BlockIndex;


  ReadLength = FEE_DFLASH_PAGE_SIZE;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  PendingPageCount = StateDataPtr->FeeGcCurrBlkInfo.PageCount -
                     StateDataPtr->FeeBlkPageCount;
  PendingBlockSize = ((uint32)PendingPageCount << FEE_PAGE_TO_BYTE);

  if(PendingPageCount > FEE_ZERO)
  {
    if(PendingBlockSize > (FEE_DFLASH_WORDLINE_SIZE - ((uint32)Offset)))
    {
      ReadLength = (Fls_17_Dmu_LengthType)FEE_DFLASH_WORDLINE_SIZE - Offset;
    }
    else
    {
      ReadLength = (Fls_17_Dmu_LengthType)PendingBlockSize;
    }
    GcSrcAddrOffset = (uint16)(Position & FEE_DFLASH_WORDLINE_SIZE_1);
    if(ReadLength > ((Fls_17_Dmu_LengthType)FEE_DFLASH_WORDLINE_SIZE - GcSrcAddrOffset))
    {
      if(Fee_lIsUnerasableAddr(Position + FEE_DFLASH_WORDLINE_SIZE) == TRUE)
      {
        ReadLength = (Fls_17_Dmu_LengthType)FEE_DFLASH_WORDLINE_SIZE - GcSrcAddrOffset;
      }
    }
  }

  /* [cover parentID={3E97A7D6-D344-49ae-9E23-70E8FA850B90}]
Assign GcReadWriteBufferPtr as destination address by adding offset to FeeGcReadWriteBuffer
[/cover] */

  GcReadWriteBufferPtr = &(StateDataPtr->FeeGcReadWriteBuffer[Offset]);

  /* initiate FLS read */
  Error = Fls_17_Dmu_Read(Position, GcReadWriteBufferPtr, ReadLength);

  if(Error == E_OK)
  {
    StateDataPtr->FeeLastReadSize = ReadLength;
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_REQSTD;
    StateDataPtr->FeeIntrJob = FEE_READ_JOB;
  }
  else
  {
    BlockIndex = Fee_lGetUsrBlockIndex(
                     StateDataPtr->FeeGcCurrBlkInfo.BlockNumber);
  /* [cover parentID={E42C759A-946D-4896-B9A5-28A3FE05189D}]
Call error handler with GC read error. Pass the block index for which read error is occured. This block will be marked as inconsistent and discarded from the GC.
[/cover] */        
    Fee_lGCErrorHandler(FEE_GC_READ,BlockIndex);
  }
}

/*******************************************************************************
** Syntax : static uint8 Fee_lGcWrite(const Fls_17_Dmu_AddressType Position,  **
**                                    const uint16 Offset)                    **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  Position: Dflash Addr to write to                       **
**                    Offset: Offset of read write buffer (page0 / page1)     **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  uint8                                                   **
**                 FEE_GC_E_OK: Write request is accepted by underlying flash **
**                  driver                                                    **
**                 FEE_GC_WRITE : Write request is accepted by underlying     **
**                 flash driver                                               **
** Description : Gives a write request and sets the error flag                **
**               in case of an error.                                         **
*******************************************************************************/
/* [cover parentID={E8C77A0A-929A-4ef6-A01E-23CCE785236A}]
Fee_lGcWrite
[/cover] */
static uint8 Fee_lGcWrite(const Fls_17_Dmu_AddressType Position,
                          const uint16 Offset)
{
  Std_ReturnType      ReturnValueFls;
  Fee_StateDataType  *StateDataPtr;
  const uint8              *GcReadWriteBufferPtr;
  uint8               Error;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  Error = FEE_GC_E_OK;
 
  GcReadWriteBufferPtr = &(StateDataPtr->FeeGcReadWriteBuffer[Offset]);
  StateDataPtr->FeeIntrJobStatus = FEE_JOB_REQSTD;
  StateDataPtr->FeeIntrJob = FEE_WRITE_JOB;
  StateDataPtr->FeeLastWriteSize = StateDataPtr->FeeLastReadSize;

  ReturnValueFls = Fls_17_Dmu_Write(Position,
                                    GcReadWriteBufferPtr,
                                    StateDataPtr->FeeLastWriteSize);
  /* if the Fls routine did not accept the request         */
  /* then report Dem error and Set GC state to FEE_GC_IDLE */
  if(ReturnValueFls == E_NOT_OK)
  {
    /* Any failure from FLS (both DET,DEM) will trigger Illegal notification
       and FEE DEM. Note Fee_JobErrorNotification will NOT raise any
       illegal notification / DEM in case of internal job failures */
    Error = FEE_GC_WRITE;
  }

  return(Error);
}

/******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lGcRequested(void)                         **
**                                                                           **
** Service ID:  NA                                                           **
**                                                                           **
** Sync/Async:  Synchronous                                                 **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) :  None                                                   **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  None                                                   **
**                                                                           **
** Description : This routine is responsible for handling Garbage Collection **
**                GC REQUESTED state                                         **
******************************************************************************/
LOCAL_INLINE void Fee_lGcRequested(void)
{
  Fee_CacheType         *CachePtr;
  Fee_StateDataType     *StateDataPtr;
  Fee_CacheType         *UnconfigBlockPtr;
  uint16                 BlockCount;
  uint8                  GcState;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /* Initialize the copied status for all the logical blocks */
  CachePtr = StateDataPtr->FeeBlockInfo;
  BlockCount = FEE_RESET;

  do
  {
    CachePtr->Status.Copied = FEE_RESET;
    CachePtr->Status.PrevCopyCopied = FEE_RESET;
    BlockCount++;

    CachePtr++;
  }
  while(BlockCount != Fee_CfgPtr->FeeBlkCnt);

  /* Update the soruce and destination pointers based on the current sector */
  if(StateDataPtr->FeeStatusFlags.FeeCurrSector == (uint32)FEE_SECTOR0)
  {
    StateDataPtr->FeeGcDestAddr = StateDataPtr->FeeSectorInfo[1].NextFreeWLAddr;
    StateDataPtr->FeeGcSrcAddr = FEE_DFLASH_BANK0_BASE;
  }
  else
  {
    StateDataPtr->FeeGcDestAddr = StateDataPtr->FeeSectorInfo[0].NextFreeWLAddr;
    StateDataPtr->FeeGcSrcAddr = FEE_DFLASH_BANK1_BASE;
  }
  StateDataPtr->FeeBlkPageCount = FEE_RESET;
  StateDataPtr->FeeStatusFlags.FeeBlkModified = FEE_RESET;
  StateDataPtr->FeeGCCopyIndex = FEE_RESET;
  /* Functionality to take care of unconfigured blocks starts ******/

  GcState = FEE_GC_START_COPY;

  StateDataPtr->FeeGcBlkIndexInWL = FEE_RESET;

  /* Clear the copied status of un-configured blocks */
  /* [cover parentID={91A4BB0F-5AB6-47bb-B0E9-39F545A33212}]
Is FeeUnconfigBlock set to FEE_UNCONFIG_BLOCK_KEEP
and are there 1 or more unconfigured blocks?
[/cover] */
  /* [cover parentID={1D42BAE6-EE9D-4cb7-9420-35D5764EE134}]
Check for unconfigured blocks
[/cover] */
  if ((Fee_CfgPtr->FeeGCConfigSetting.FeeUnconfigBlock ==
       FEE_UNCONFIG_BLOCK_KEEP)
      && (StateDataPtr->FeeUnConfigBlockCount != FEE_RESET))
  {
    BlockCount = FEE_RESET;

    while(BlockCount < StateDataPtr->FeeUnConfigBlockCount)
    {

      UnconfigBlockPtr = &(StateDataPtr->FeeBlockInfo[(Fee_CfgPtr->FeeBlkCnt
                                                      + BlockCount)]);
      UnconfigBlockPtr->Status.Copied = FEE_RESET;
      BlockCount++;
    }

    StateDataPtr->FeeGCUnconfigBlkCopyIndex = FEE_RESET;
    GcState = FEE_GC_UNCFG_START_COPY;
  }

  StateDataPtr->FeeGcState = GcState;
  /* [cover parentID={75D2F6B5-7ED5-4679-A8F6-59A377E70A69}]
Return
[/cover] */
}

/******************************************************************************
** Syntax : static void Fee_lGcPrologue(void)                                **
**                                                                           **
** Service ID:                                                               **
**                                                                           **
** Sync/Async:  Asynchronous                                                 **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) :  None                                                   **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  None                                                   **
**                                                                           **
** Description : This routine is responsible for handling transitions from   **
** FEE_GC_UNCONFIG_BLOCK_READ_NXTPAGE and  FEE_GC_COPY_READ_NXTPAGE states.  **
** The transitions from the above states are handled as Prologue and not as  **
** part of the state itself. This is to avoid one main cycle delay           **
** in executing the next pass state (FEE_GC_UNCONFIG_BLOCK_WRITE or          **
** FEE_GC_START_COPY_WRITE)                                                  **
******************************************************************************/
/* [cover parentID={C7C60798-A48A-4406-BB9E-BD60DC582F8D}]
Fee_lGcPrologue
[/cover] */
static void Fee_lGcPrologue(void)
{
  Fee_StateDataType     *StateDataPtr;
  uint16                 BlockIndex;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  if (StateDataPtr->FeeIntrJobStatus == FEE_JOB_DONE)
  {
    if (StateDataPtr->FeeGcState == FEE_GC_UNCFG_COPY_READ_NXTPAGE)
    {
      /* Reset the job status */
      StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
      if(StateDataPtr->FeeIntrJobResult == FEE_JOB_FAIL)
      {
        BlockIndex = Fee_lGetUsrBlockIndex(
                     StateDataPtr->FeeGcCurrBlkInfo.BlockNumber);
        Fee_lGCErrorHandler(FEE_GC_READ,BlockIndex);
      }
      else
      {
        StateDataPtr->FeeGcState = FEE_GC_UNCFG_COPY_WRITE;
      }
    }

    else if (StateDataPtr->FeeGcState == FEE_GC_COPY_READ_NXTPAGE)
    {
      StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
      if(StateDataPtr->FeeIntrJobResult == FEE_JOB_FAIL)
      {
        BlockIndex = Fee_lGetUsrBlockIndex(
                     StateDataPtr->FeeGcCurrBlkInfo.BlockNumber);
        Fee_lGCErrorHandler(FEE_GC_READ,BlockIndex);
      }
      else
      {
        StateDataPtr->FeeGcState = FEE_GC_COPY_WRITE;
      }
    }
    else
    {
      /* dummy else */
    }
  }
}

/*******************************************************************************
** Syntax : static void Fee_lGcDiscardUnconfigBlk(void)                       **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async: Synchronous                                                    **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : uint16 Block index in cache table                        **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : This function discards the un-configured block               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={B1EFBE21-A5EE-42b3-8409-37091234EE38}]
Fee_lGcDiscardUnconfigBlk
[/cover] */
static void Fee_lGcDiscardUnconfigBlk(const uint16 Index)
{
  Fee_StateDataType     *StateDataPtr;
  Fee_CacheType         *UnconfigBlockPtr;
  uint16                 BlockIndex;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /* Check if the block index is in range. if not find the block index using 
  the FeeGcCurrBlkInfo. FeeGcCurrBlkInfo is updated only we are able read the 
  header of the block properly. In case we are not able read header of block
  given index will have valid value. */
  if(FEE_LOG_BLOCK_NOT_FOUND != Index)
  {
    BlockIndex = Index;    
    UnconfigBlockPtr= &(StateDataPtr->FeeBlockInfo[Index]);
  }
  else
  {
    /*Find the block index for unconfigured block*/
    BlockIndex = FEE_RESET;
    UnconfigBlockPtr= &(StateDataPtr->FeeBlockInfo[Fee_CfgPtr->FeeBlkCnt]);
    while((BlockIndex < (StateDataPtr->FeeUnConfigBlockCount)) &&
         (StateDataPtr->FeeGcCurrBlkInfo.BlockNumber !=
         UnconfigBlockPtr->BlockNumber))
    {
      BlockIndex++;
      UnconfigBlockPtr++;
    }  
  }
  
  /* Discard the block from cache table and reduce the number of un-configured
  by 1 and update the cache table for un-configured block */
  (StateDataPtr->FeeUnConfigBlockCount)--;
  while(BlockIndex < (StateDataPtr->FeeUnConfigBlockCount))
  {

    UnconfigBlockPtr[BlockIndex].BlockNumber = 
    UnconfigBlockPtr[BlockIndex + FEE_ONE].BlockNumber;
    
    UnconfigBlockPtr[BlockIndex].Address = 
    UnconfigBlockPtr[BlockIndex + FEE_ONE].Address;
    BlockIndex++;

  }
}

/*******************************************************************************
** Syntax : static void Fee_lGcDiscardConfigBlk(const uint16 Index)           **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async: Synchronous                                                    **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  uint16 Block index in cache table.                      **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : This function discards the configured block which has the ECC**
**               error while reading the block during GC.Also mark this block **
**               as inconsistent in cache table.                              **
**                                                                            **
*******************************************************************************/
/* [cover parentID={1370397F-B0B8-4f50-80A8-04D9EA12F60E}]
Fee_lGcDiscardConfigBlk
[/cover] */
static void Fee_lGcDiscardConfigBlk(const uint16 Index)
{
  Fee_StateDataType     *StateDataPtr;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  
  /*Mark the block as inconsistent*/
  StateDataPtr->FeeBlockInfo[Index].Status.Consistent = FEE_RESET;

}

/*******************************************************************************
** Syntax : static boolean Fee_lGcCheckBlkCopy(void)                          **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  boolean RetVal:                                         **
**                    TRUE: There is a block to be copied                     **
**                    FALSE:No block is to be copied                          **
**                                                                            **
** Description : This routine checks the cache table starting from the        **
**  FeeGCCopyIndex and finds if any block needs to be copied                  **
*******************************************************************************/
static boolean Fee_lGcCheckBlkCopy(void)
{
  Fee_StateDataType    *StateDataPtr;
  const Fee_CacheType        *CachePtr;
  uint16                BlockCount;
  boolean                 RetVal;

  RetVal = FALSE;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  BlockCount = StateDataPtr->FeeGCCopyIndex;
 
  CachePtr = &(StateDataPtr->FeeBlockInfo[BlockCount]);

  while ((RetVal == FALSE) && (BlockCount != Fee_CfgPtr->FeeBlkCnt))
  {
    /* If block is consistent and not copied */
    if ((CachePtr->Status.Consistent == (uint32)FEE_SET ) &&
        (CachePtr->Status.Copied == (uint32)FEE_RESET))
    {
      RetVal = TRUE ;
    }
    else
    {
      BlockCount++;

      CachePtr++;
    }
  }
  StateDataPtr->FeeGCCopyIndex = BlockCount;

  return(RetVal);
}

/*******************************************************************************
** Syntax : static void Fee_lGcStartCopy(void)                                **
**                                                                            **
** Service ID:  NA                                                            **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine is responsible for handling Garbage Collection  **
**                GC START COPY state                                         **
*******************************************************************************/
static void Fee_lGcStartCopy(void)
{
  Fee_CacheType         *CachePtr;
  const Fee_CacheType         *UnconfigBlockPtr;
  Fee_StateDataType     *StateDataPtr;
  uint32                 DestAddr;
  uint16                 Offset;
  uint16                 Index;
  boolean                StateFlag;
  Std_ReturnType         Error;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  if (StateDataPtr->FeeIntrJobStatus == FEE_JOB_DONE)
  {
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
    if(StateDataPtr->FeeIntrJobResult == FEE_JOB_FAIL)
    {
      Index = Fee_lGetUsrBlockIndex(StateDataPtr->FeeGcCurrBlkInfo.BlockNumber);
      Fee_lGCErrorHandler(FEE_GC_READ,Index);
    }
    else
    {
      if(StateDataPtr->FeeGcState == FEE_GC_START_COPY)
      {
        StateDataPtr->FeeGcState = FEE_GC_COPY_WRITE;
      }
      else
      {
        StateDataPtr->FeeGcState = FEE_GC_UNCFG_COPY_WRITE;
      }
    }
  }
  else
  {
    /* i.e. StateDataPtr->FeeGcState == FEE_GC_START_COPY */
    DestAddr = (uint32)StateDataPtr->FeeGcDestAddr;

    /* No more blocks to be copied in the current pass -
       check if any block is modified during GC */
    if(StateDataPtr->FeeGcState == FEE_GC_UNCFG_START_COPY)
    {
      StateFlag = Fee_lGcCheckUnconfigBlkCopy();
    }
    else /* if(StateDataPtr->FeeGcState == FEE_GC_START_COPY) */
    {
      /* Check if there are any more blocks to be copied */
      StateFlag = Fee_lGcCheckBlkCopy();
      if (StateFlag == (boolean)FALSE)
      {
        /* if any of the logical blocks were modified */
        if(StateDataPtr->FeeStatusFlags.FeeBlkModified == (uint32)FEE_SET )
        {
          StateDataPtr->FeeStatusFlags.FeeBlkModified = FEE_RESET;
          StateDataPtr->FeeGCCopyIndex = FEE_RESET;
          StateFlag = Fee_lGcCheckBlkCopy();
        }
      }
    }

    /* Block copying not yet completed */
    if(StateFlag == (boolean)TRUE)
    {
      /* [cover parentID={087B5551-47F4-481c-9FC1-8C2BFABCCEED}]*/
      if(StateDataPtr->FeeGcState == FEE_GC_UNCFG_START_COPY)
      {

        UnconfigBlockPtr = &(StateDataPtr->FeeBlockInfo[(Fee_CfgPtr->FeeBlkCnt)
                                   +(StateDataPtr->FeeGCUnconfigBlkCopyIndex)]);
             
        StateDataPtr->FeeGcSrcAddr = UnconfigBlockPtr->Address;
        
        /*Store cache index of block for passing in Fee_lGCErrorHandler in case 
        of read error while reading header page  */
        Index = StateDataPtr->FeeGCUnconfigBlkCopyIndex;
        
      }

      else /* FeeGcState == FEE_GC_START_COPY */
      {
        CachePtr = &(StateDataPtr->FeeBlockInfo[StateDataPtr->FeeGCCopyIndex]);
        StateDataPtr->FeeGcSrcAddr = CachePtr->Address;
        
         /*Store cache index of block for passing in Fee_lGCErrorHandler in case 
        of read error while reading header page  */
        Index = StateDataPtr->FeeGCCopyIndex;
      }
      StateDataPtr->FeeBlkPageCount = FEE_RESET;
      Offset = (uint16) (DestAddr & (uint32)FEE_DFLASH_WORDLINE_SIZE_1);
      if (Offset == FEE_ZERO)
      {
        Fee_lClearFeeGcReadWriteBuffer();
      }
      /* Fill Curr Block information */
      /* Read the header (first 8bytes) of the block to update the
        Gc Curr Blk information */

      /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with FLS.
      FEE is passing parameters to FLS APIs, for example,
      Fls_17_Dmu_ReadWordsSync.Changing this will break the interfacing and will
       cause major functional issues both on FLS and FEE side.*/
      Error = Fls_17_Dmu_ReadWordsSync(\
                (Fls_17_Dmu_AddressType)StateDataPtr->FeeGcSrcAddr,\
                (uint32 *)(&(StateDataPtr->FeeGcReadWriteBuffer[Offset])),\
                (Fls_17_Dmu_LengthType)\
                (FEE_DFLASH_PAGE_SIZE / FEE_DFLASH_WORD_SIZE));
      if(Error == E_OK)
      {
        Fee_lUpdateGcCurrBlockInfo();
        Fee_lGcRead((Fls_17_Dmu_AddressType)
                    (StateDataPtr->FeeGcSrcAddr),Offset);
      }
      else
      {
        /*Not able read the block , trigger the GC_READ_DEM and discard the 
        block*/
        Fee_lGCErrorHandler(FEE_GC_READ,Index);
    
      }

    }
    /* Finished copying all the configured OR unconfigured blocks */
    else
    {
      if (Fee_lIsWLBeginning(DestAddr) != FEE_NEW_WL_BEGIN)
      {
        DestAddr = Fee_lGetNextWLAddr(DestAddr);
      }
      Fee_lClearFeeGcReadWriteBuffer();
      StateDataPtr->FeeGcDestAddr = DestAddr;

      /* Clear the compare fail count*/
      StateDataPtr->FeeIntrJobFailCount = FEE_RESET;

      if(StateDataPtr->FeeGcState == FEE_GC_START_COPY)
      {
        /* Finished copying all the configured blocks */
        /* Mark the previous copy of blocks as inconsistent for the blocks which
        are not updated during GC - this means that only the latest data is
        copied during GC and there is no previoud copy in the new sector */
        Index = FEE_RESET;
        do
        {
          CachePtr = &(StateDataPtr->FeeBlockInfo[Index]);
          if (CachePtr->Status.PrevCopyCopied == (uint32)FEE_RESET)
          {

            CachePtr->PrevCopyAddress = FEE_RESET;
            CachePtr->Status.PrevCopyValid = FEE_RESET;
            CachePtr->Status.PrevCopyConsistent = FEE_RESET;
            CachePtr->Status.PrevCopyCopied = FEE_RESET;
          }
          Index++;
        }
        while(Index < Fee_CfgPtr->FeeBlkCnt);

        /* Move to next state */
        StateDataPtr->FeeGcState = FEE_GC_MARK_SECTOR1_V_SP;
      }
      else
      {
        /* Finished copying all the unconfigured blocks */
        /* Now copy all the configured blocks */
        StateDataPtr->FeeGcState = FEE_GC_START_COPY;
      }
    }
  }
}

/*******************************************************************************
** Syntax : static uint8 Fee_lGcStartCopyWrite(void)                          **
**                                                                            **
** Service ID:  NA                                                            **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  uint8                                                   **
**                    FEE_GC_E_OK : No error operation is successful          **
**                    FEE_GC_WRITE: GC write operation is failed              **
**                    FEE_GC_TRIG : GC operation triggers the another GC      **
**                                  Operation                                 **
** Description : This routine is responsible for handling Garbage Collection  **
**                GC START COPY WRITE state                                   **
*******************************************************************************/
/* [cover parentID={48FEEE58-E3FE-4956-9C37-B6ED1BA854FF}]
Fee_lGcStartCopyWrite
[/cover] */
static uint8 Fee_lGcStartCopyWrite(void)
{
  Fee_StateDataType    *StateDataPtr;
  const Fee_GcBlkInfoType    *GcCurrBlkPtr;
  uint32                DestAddr;
  uint32                PageCount;
  uint32                FreePages;
  uint16                Offset;
  uint8                 BankNumber;
  uint8                 Error;

  Error = FEE_GC_E_OK;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  GcCurrBlkPtr = &(StateDataPtr->FeeGcCurrBlkInfo);

  if (StateDataPtr->FeeIntrJobStatus == FEE_JOB_DONE)
  {
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
    
    /*Check if write operation is failed due other than PVER. If yes then 
    report the FEE_GC_WRITE error otherwise retry write operation. */
    if((StateDataPtr->FeeIntrJobResult == FEE_JOB_FAIL) && 
       (StateDataPtr->FeeProgVerErr == FEE_RESET))
    {
      Error = FEE_GC_WRITE;
    }
    else
    {
      Fee_lGcBlkCompare();
    }
  }
  else if(StateDataPtr->FeeComparedLen != (uint16)FEE_ZERO)
  {
    Fee_lGcBlkCompare();
  }
  else
  {
    /* i.e. StateDataPtr->FeeGcState == FEE_GC_COPY_WRITE */
    DestAddr = (uint32)StateDataPtr->FeeGcDestAddr;
    while(Fee_lIsUnerasableAddr(DestAddr) == TRUE)
    {
      DestAddr = Fee_lGetNextWLAddr(DestAddr);
    }
    StateDataPtr->FeeGcDestAddr = DestAddr;

    /*************** CHECK for the case of GC TRIGGERING GC *****************/
    if (StateDataPtr->FeeBlkPageCount == FEE_ZERO)
    {
      /* Get the Destination sector - It is the sector other than curr sector*/
      BankNumber = (uint8)StateDataPtr->FeeStatusFlags.FeeCurrSector ^ FEE_SECTOR1;
      /* Find the free pages in the destination sector */
      FreePages = Fee_lGetFreeDFLASHPages(BankNumber, DestAddr);
      /* Get the block page count */
      PageCount = (uint32)StateDataPtr->FeeGcCurrBlkInfo.PageCount;
      /* Check if the block is crossing the threshold */
      if ((boolean)TRUE == Fee_lIsSectorThresholdCrossed(FreePages, PageCount))
      {
        Error = FEE_GC_TRIG;
      }
    }
    if (Error == FEE_RESET)
    {
      Offset = (uint16) (DestAddr & FEE_DFLASH_WORDLINE_SIZE_1);
      if(Offset == FEE_ZERO)
      {
        StateDataPtr->FeeGcFirstBlkNumInWL = GcCurrBlkPtr->BlockNumber;
        StateDataPtr->FeeGcBlkIndexInWL = FEE_RESET;
      }
      if(StateDataPtr->FeeBlkPageCount == FEE_RESET)
      {
        StateDataPtr->FeeBlockStartAddr = DestAddr;
      }
      Error = Fee_lGcWrite((Fls_17_Dmu_AddressType)DestAddr, Offset);
    }
  }

  return(Error);
}

/*******************************************************************************
** Syntax : static void Fee_lGcCopyReadNxtPage(void)                          **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine is responsible for handling Garbage Collection  **
**                FEE_GC_COPY_READ_NXTPAGE state                              **
*******************************************************************************/
/* [cover parentID={5A35275E-BE0A-4017-9492-A74355CB54BD}]
Fee_lGcCopyReadNxtPage
[/cover] */
static void Fee_lGcCopyReadNxtPage(void)
{
  uint32                 SrcAddr;
  Fee_StateDataType     *StateDataPtr;
  uint16                 Offset;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* The transitions from this state are handled as part of Fee_lGcPrologue
     Hence only state actions are done here */

  Offset = (uint16) ((StateDataPtr->FeeGcDestAddr) &
                     (uint32)FEE_DFLASH_WORDLINE_SIZE_1);
  SrcAddr = StateDataPtr->FeeGcSrcAddr;
  while(Fee_lIsUnerasableAddr(SrcAddr) == TRUE)
  {
    SrcAddr = Fee_lGetNextWLAddr(SrcAddr);
  }
  StateDataPtr->FeeGcSrcAddr = SrcAddr;
  Fee_lGcRead((Fls_17_Dmu_AddressType)(StateDataPtr->FeeGcSrcAddr), Offset);
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lGcBlkCompare(void)                         **
**                                                                            **
** Service ID: NA                                                             **
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
** Description : Performs compare actions on FEE_GC_START_COPY_WRITE          **
**               during Garbage collection                                    **
*******************************************************************************/
/* [cover parentID={16B182B9-FE60-4d9d-AFFA-B333EFE37022}]
Fee_lGcBlkCompare
[/cover] */
LOCAL_INLINE void Fee_lGcBlkCompare(void)
{
  Fee_StateDataType     *StateDataPtr;
  const Fee_GcBlkInfoType     *GcCurrBlkPtr;
  Fee_CacheType         *CachePtr;
  Fee_CacheType         *UnconfigBlockPtr;
  uint32                 DestAddr;
  Fls_17_Dmu_AddressType        CompAddr;
  Fls_17_Dmu_LengthType         CompLength;
  Fls_17_Dmu_LengthType         TmpCompareLength;
  uint16                 BlockNumber;
  uint16                 Index;
  Std_ReturnType         ReturnVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  CachePtr = StateDataPtr->FeeBlockInfo;
  ReturnVal = E_OK;
  UnconfigBlockPtr = &(StateDataPtr->FeeBlockInfo[Fee_CfgPtr->FeeBlkCnt]);

  GcCurrBlkPtr = &(StateDataPtr->FeeGcCurrBlkInfo);

  DestAddr = StateDataPtr->FeeGcDestAddr;
  /* Compare entire WL */
  CompAddr = (Fls_17_Dmu_AddressType)Fee_lGetWLBeginning(DestAddr);

  CompLength = (StateDataPtr->FeeGcDestAddr) &
               (Fls_17_Dmu_LengthType)FEE_DFLASH_WORDLINE_SIZE_1;
  CompLength += (StateDataPtr->FeeLastWriteSize);
  TmpCompareLength = CompLength;

  CompLength -=  StateDataPtr->FeeComparedLen;
  if(CompLength > FEE_COMPARE_LEN_MAX)
  {
    CompLength = FEE_COMPARE_LEN_MAX;
  }
  
  if(StateDataPtr->FeeProgVerErr == FEE_RESET)
  {
    /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with FLS.
    FEE is passing parameters to FLS APIs, for example,
    Fls_17_Dmu_CompareWordsSync.Changing this will break the interfacing and
     will cause major functional issues both on FLS and FEE side. */
    ReturnVal = Fls_17_Dmu_CompareWordsSync( \
                (CompAddr + StateDataPtr->FeeComparedLen),\
                (uint32 *)(&(StateDataPtr->FeeGcReadWriteBuffer\
                [StateDataPtr->FeeComparedLen])),\
                (CompLength / FEE_DFLASH_WORD_SIZE));
  
    StateDataPtr->FeeComparedLen += (uint16)CompLength;
  }
  
  /* Compare failed or PVER error is set.*/
  if((ReturnVal == E_NOT_OK) || 
    (StateDataPtr->FeeProgVerErr == FEE_SET))
  {
    StateDataPtr->FeeComparedLen = FEE_RESET;
    /*Reset the FeeProgVerErr flag*/
    StateDataPtr->FeeProgVerErr = FEE_RESET;
    if(StateDataPtr->FeeIntrJobFailCount == FEE_RESET)
    {
      StateDataPtr->FeeIntrJobFailCount++;

      if(StateDataPtr->FeeGcState == FEE_GC_UNCFG_COPY_WRITE)
      {
        if(StateDataPtr->FeeGcBlkIndexInWL != FEE_RESET)
        {
          Fee_lHandleUnConfigGcCopyError();
        }
        StateDataPtr->FeeGcState = FEE_GC_UNCFG_START_COPY;
      }
      else /* FeeGcState == FEE_GC_COPY_WRITE */
      {
        if(StateDataPtr->FeeGcBlkIndexInWL != FEE_RESET)
        {
          Fee_lHandleConfigGcCopyError();
        }
        StateDataPtr->FeeGcState = FEE_GC_START_COPY;
      }
      /* Switch the destination address to next to next free WL*/
      DestAddr = Fee_lGetNextWLAddr(DestAddr);
      DestAddr = Fee_lGetNextWLAddr(DestAddr);
      StateDataPtr->FeeGcDestAddr = DestAddr;
    }
    else
    {
      /* Write Fail two time raise the illegal notification.block index 
      parameters is not used for write error , so passed as parameter not used.
      Block index is used only for read error to drop the block from GC process.
      */
      Fee_lGCErrorHandler(FEE_GC_WRITE , FEE_UNUSED_PARAM);
    }
  }
  else if(StateDataPtr->FeeComparedLen != (uint16)TmpCompareLength)
  {
    /* dummy else if to skip else for inbetween loops */
  }
  /* Compare successful */
  else
  {
    StateDataPtr->FeeComparedLen = FEE_RESET;
    StateDataPtr->FeeGcSrcAddr += StateDataPtr->FeeLastWriteSize;
    StateDataPtr->FeeGcDestAddr += StateDataPtr->FeeLastWriteSize;

    StateDataPtr->FeeBlkPageCount +=
      (Fee_PageType)(StateDataPtr->FeeLastWriteSize >> FEE_BYTE_TO_PAGE);
    if (StateDataPtr->FeeBlkPageCount == (GcCurrBlkPtr->PageCount + FEE_ONE))
    {
      /* Clear the compare fail count if the block write is complete */
      /* Count shall not be cleared upon completion of previous block write */
      if (GcCurrBlkPtr->BlockNumber != StateDataPtr->FeeGcPrevBlockNumber)
      {
        StateDataPtr->FeeIntrJobFailCount = FEE_RESET;
      }
      /* Update the cache table for current block */
      BlockNumber = GcCurrBlkPtr->BlockNumber;

      if(StateDataPtr->FeeGcState == FEE_GC_UNCFG_COPY_WRITE)
      {

        UnconfigBlockPtr = (&UnconfigBlockPtr
        [StateDataPtr->FeeGCUnconfigBlkCopyIndex]);
        UnconfigBlockPtr->Status.Copied = FEE_SET ;
        StateDataPtr->FeeGcLWBGcSrcAddr[StateDataPtr->FeeGcBlkIndexInWL] =
          UnconfigBlockPtr->Address;
        UnconfigBlockPtr->Address = StateDataPtr->FeeBlockStartAddr;
        StateDataPtr->FeeGCUnconfigBlkCopyIndex++;

        /* Move to next state */
        StateDataPtr->FeeGcState = FEE_GC_UNCFG_START_COPY;
      }
      else /* FEE_GC_COPY_WRITE */
      {
        Index = Fee_lGetUsrBlockIndex(BlockNumber);

        CachePtr = &(CachePtr[Index]);
        CachePtr->Status.Copied = FEE_SET ;
        StateDataPtr->FeeGcLWBGcSrcAddr[StateDataPtr->FeeGcBlkIndexInWL] =
          CachePtr->Address;
        CachePtr->Address = StateDataPtr->FeeBlockStartAddr;
        StateDataPtr->FeeGCCopyIndex++;

        /* Move to next state */
        StateDataPtr->FeeGcState = FEE_GC_START_COPY;
      }

      /* Update LastBlock with Current block info */
      StateDataPtr->FeeGcPrevBlockNumber = GcCurrBlkPtr->BlockNumber;

      (StateDataPtr->FeeGcBlkIndexInWL)++;
    }
    else
    {
      if(StateDataPtr->FeeGcState == FEE_GC_UNCFG_COPY_WRITE)
      {
        StateDataPtr->FeeGcState = FEE_GC_UNCFG_COPY_READ_NXTPAGE;
      }
      else /* FEE_GC_COPY_WRITE */
      {
        StateDataPtr->FeeGcState = FEE_GC_COPY_READ_NXTPAGE;
      }
    }
  }
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lHandleUnConfigGcCopyError(void)            **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : This function handles un-configured block's copy error       **
**                                                                            **
*******************************************************************************/
/* [cover parentID={B02A666C-094D-47c0-9DB6-AC87FEB69334}]
Fee_lHandleUnConfigGcCopyError
[/cover] */
LOCAL_INLINE void Fee_lHandleUnConfigGcCopyError(void)
{
  Fee_StateDataType     *StateDataPtr;
  Fee_CacheType         *UnconfigBlockPtr;
  uint16                 BlockIndex;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  UnconfigBlockPtr = &(StateDataPtr->FeeBlockInfo[Fee_CfgPtr->FeeBlkCnt]);
  BlockIndex = FEE_RESET;

  /* Find the index of the first affected un-configured block */
  while((BlockIndex < (StateDataPtr->FeeUnConfigBlockCount)) &&
        ((UnconfigBlockPtr->BlockNumber) != StateDataPtr->FeeGcFirstBlkNumInWL))
  {
    BlockIndex++;

    UnconfigBlockPtr++;
  }
  StateDataPtr->FeeGCUnconfigBlkCopyIndex = BlockIndex;

  /* Clear the Copied status of all the affected un-configured blocks */
  for(BlockIndex = FEE_RESET;
      BlockIndex < StateDataPtr->FeeGcBlkIndexInWL;
      BlockIndex++)
  {
    UnconfigBlockPtr->Status.Copied = FEE_RESET;
    UnconfigBlockPtr->Address = StateDataPtr->FeeGcLWBGcSrcAddr[BlockIndex];

    UnconfigBlockPtr++;
  }
  StateDataPtr->FeeGcBlkIndexInWL = FEE_RESET;
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lHandleConfigGcCopyError(void)              **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : This function handles configured block's copy error. Undoes  **
** the markings for the configured blocks (in the WL) affected during the GC  **
** copy operation.                                                            **
**                                                                            **
*******************************************************************************/
/* [cover parentID={BEA2009F-01BC-4277-A216-C597C15BAB19}]
Fee_lHandleConfigGcCopyError
[/cover] */
LOCAL_INLINE void Fee_lHandleConfigGcCopyError(void)
{
  Fee_StateDataType     *StateDataPtr;
  Fee_CacheType         *CachePtr;
  uint16                 BlockIndex;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  BlockIndex = Fee_lGetUsrBlockIndex(StateDataPtr->FeeGcFirstBlkNumInWL);
  CachePtr = &(StateDataPtr->FeeBlockInfo[BlockIndex]);

  StateDataPtr->FeeGCCopyIndex = BlockIndex;
  for(BlockIndex = FEE_RESET;
      BlockIndex < StateDataPtr->FeeGcBlkIndexInWL;
      BlockIndex++)
  {
    if(CachePtr->Status.Copied == (uint32)FEE_SET )
    {
      /* Latest copy not available. Move GcLogBlkCount to previous block Index
       and switch to Start Copy state */
      CachePtr->Status.Copied = FEE_RESET;
      CachePtr->Address = StateDataPtr->FeeGcLWBGcSrcAddr[BlockIndex];
    }
    else
    {
      /* Latest copy of the block is available: no need to copy the affected 
      previous block.Just make the PrevCopyStatus as zero. This is needed to
      mark the affected previous copy as inconsistent */
      CachePtr->Status.PrevCopyCopied = FEE_RESET;
    }

    CachePtr++;
  }
  StateDataPtr->FeeGcBlkIndexInWL = FEE_RESET;
}

/*******************************************************************************
** Syntax : static uint8 Fee_lGcErasePrevSector(const uint8 GcState)          **
**                                                                            **
** Service ID:  NA                                                            **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  GcState: Current Gc State                               **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  uint8                                                   **
**                    FEE_GC_E_OK : No error erase operation is successful    **
**                    FEE_GC_ERASE: GC Erase request is not accepted by flash **
**                    driver or erase operation failed                        **
** Description : This routine is responsible for handling Garbage Collection  **
**    FEE_GC_ERASE_PREV_SECTOR / FEE_GC_INIT_ERASE_PREV_SECTOR state          **
*******************************************************************************/
/* [cover parentID={2EF44D40-9EF0-4773-ACE9-8DB14FDA91F4}]
Fee_lGcErasePrevSector
[/cover] */
static uint8 Fee_lGcErasePrevSector(const uint8 GcState)
{
  Fee_StateDataType   *StateDataPtr;
  Std_ReturnType       ReturnValueFls;
  uint8                Error;
  uint32                BankNumber;

  Error = FEE_GC_E_OK;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  if (StateDataPtr->FeeIntrJobStatus == FEE_JOB_DONE)
  {
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
    /* Check if Erase operation is failed because of EVR bit set.If yes then
    do set GC error. This is done to find out unerasble WL address. */
    if((StateDataPtr->FeeIntrJobResult == FEE_JOB_FAIL) &&
        (StateDataPtr->FeeEraseVerErr == FEE_RESET ))
    {
      Error = FEE_GC_ERASE;
    }
    else if(StateDataPtr->FeeIntrJobResult == FEE_JOB_PASS)
    {
      if(GcState == FEE_GC_ERASE_PREV_SECTOR)
      {
        StateDataPtr->FeeGcState = FEE_GC_MARK_SECTOR0_E_SP;
      }
      /*  Case FEE_GC_INIT_ERASE_PREV_SECTOR */
      else
      {
        /* Erase of previous sector is happening as part of INIT GC.
           The FeeStateCount shall be incremented by 2 to mark one sector
           erase. Increment FeeStateCount by 1 here. FeeStateCount is
           incremented again while preparing the state page buffer in
           FEE_GC_INIT_MARK_SECTOR0_E_SP */
        StateDataPtr->FeeStateCount += FEE_ONE;
        StateDataPtr->FeeGcState = FEE_GC_INIT_MARK_SECTOR0_E_SP;
      }
      
      /*Erase is successful , reset the un-erasable WL addrress information 
      for this sector. */
      if(StateDataPtr->FeeGcDestAddr == FEE_DFLASH_BANK1_BASE)
      {
        BankNumber = FEE_SECTOR1;
      }
      else
      {
        BankNumber = FEE_SECTOR0;
      }
      StateDataPtr->FeeSectorInfo[BankNumber].UnerasableWLCount = FEE_RESET;
      StateDataPtr->FeeSectorInfo[BankNumber].UnerasableWLAddr[0] = FEE_RESET;
      StateDataPtr->FeeSectorInfo[BankNumber].UnerasableWLAddr[1] = FEE_RESET;
    
    }
    else
    {
      /* No need to check FeeEraseVerErr,because code flow will reach here
      when FeeEraseVerErr and erase operation is failed. Also when erase
      operation is successful in this FeeEraseVerErr will be 0 */
      StateDataPtr->FeeEraseVerErr = FEE_RESET;
      Fee_lGcEraseCompare(GcState);
    }
  }
  /*MISRA2012_RULE_10_4_JUSTIFICATION:Typecasting is done. Types are same */
  else if(StateDataPtr->FeeSectorCount > (uint8)FEE_ZERO)
  {
    Fee_lGcEraseCompare(GcState);
  }
  else
  {
    /* i.e. StateDataPtr->FeeGcState == FEE_GC_ERASE_PREV_SECTOR or
                                      FEE_GC_INIT_ERASE_PREV_SECTOR  */
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_REQSTD;
    StateDataPtr->FeeIntrJob = FEE_ERASE_JOB;

    ReturnValueFls = Fls_17_Dmu_Erase(
                       (Fls_17_Dmu_AddressType)StateDataPtr->FeeGcDestAddr,
                       (Fls_17_Dmu_LengthType)FEE_DFLASH_SECTOR_SIZE);

    /* if the Fls routine did not accept the request */
    if(ReturnValueFls == E_NOT_OK)
    {
      /* Any failure from FLS (both DET,DEM) will trigger Illegal notification
         and FEE DEM */
      Error = FEE_GC_ERASE;
    }
  }

  return(Error);
}/*End of Fee_lGcErasePrevSector*/


/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lGcEraseCompare(const uint8 GcState)        **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  GcState: Current Gc State                               **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : Performs state transitions from FEE_GC_ERASE_PREV_SECT or    **
**  FEE_GC_INIT_ERASE_PREV_SECTOR during Garbage collection                   **
*******************************************************************************/
LOCAL_INLINE void Fee_lGcEraseCompare(const uint8 GcState)
{
  Fee_StateDataType    *StateDataPtr;
  uint32                BankNumber;
  Std_ReturnType        ReturnVal;
  uint8                 NewGcState;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  if(StateDataPtr->FeeSectorCount == 0U)
  {
    StateDataPtr->FeeUnErasableWLAddrTemp[0] = FEE_RESET;
    StateDataPtr->FeeUnErasableWLAddrTemp[1] = FEE_RESET;
    StateDataPtr->FeeUnErasableWLCountTemp = FEE_RESET;
  }

  if(StateDataPtr->FeeGcDestAddr == FEE_DFLASH_BANK1_BASE)
  {
    BankNumber = FEE_SECTOR1;
  }
  else
  {
    BankNumber = FEE_SECTOR0;
  }
   /* [cover parentID={7CF3728A-3577-4582-9375-96CB793399A0}]
Verify erase of the flash sector
[/cover] */
  ReturnVal = Fls_17_Dmu_VerifySectorErase(StateDataPtr->FeeGcDestAddr,
              &(StateDataPtr->FeeUnErasableWLAddrTemp[0]),
              &(StateDataPtr->FeeUnErasableWLCountTemp),
              StateDataPtr->FeeSectorCount);
  if(ReturnVal == E_NOT_OK)
  { 
   /* [cover parentID={B7FCE4D1-0B08-471e-A477-F8504E2424B3}]
Call the error handler, pass the block address as block not found
[/cover] */
    /* block index is not used for erase error , so passed as parameter unused.
    Block index is used only for read error to drop the block from GC process.
    */
    Fee_lGCErrorHandler(FEE_GC_ERASE , FEE_UNUSED_PARAM);
  }
  else
  {
    StateDataPtr->FeeSectorCount++;

    /*MISRA2012_RULE_10_4_JUSTIFICATION:Typecasting is done. Types are same */
    if(StateDataPtr->FeeSectorCount == (uint8)FLS_ERASE_SECTORS)
    {
      StateDataPtr->FeeSectorInfo[BankNumber].UnerasableWLCount =
        StateDataPtr->FeeUnErasableWLCountTemp;
      StateDataPtr->FeeSectorInfo[BankNumber].UnerasableWLAddr[0] =
        StateDataPtr->FeeUnErasableWLAddrTemp[0];
      StateDataPtr->FeeSectorInfo[BankNumber].UnerasableWLAddr[1] =
        StateDataPtr->FeeUnErasableWLAddrTemp[1];

      if(GcState == FEE_GC_ERASE_PREV_SECTOR)
      {
        NewGcState = FEE_GC_MARK_SECTOR0_E_SP;
      }
      /*  Case FEE_GC_INIT_ERASE_PREV_SECTOR */
      else
      {
        /* Erase of previous sector is happening as part of INIT GC.
           The FeeStateCount shall be incremented by 2 to mark one sector
           erase. Increment FeeStateCount by 1 here. FeeStateCount is
           incremented again while preparing the state page buffer in
           FEE_GC_INIT_MARK_SECTOR0_E_SP */
        StateDataPtr->FeeStateCount += FEE_ONE;
        NewGcState = FEE_GC_INIT_MARK_SECTOR0_E_SP;
      }
      /* Move to next state */
      StateDataPtr->FeeGcState = NewGcState;
      StateDataPtr->FeeSectorCount = FEE_RESET;
    }
  }
}

/******************************************************************************
** Syntax : static uint8 Fee_lGcProgramStatePage(const uint8 GcState)        **
**                                                                           **
** Service ID:                                                               **
**                                                                           **
** Sync/Async:  Asynchronous                                                 **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) : uint8  GcState: Current Gc State                        **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  uint8                                                  **
**                   FEE_GC_E_OK: Operation is successful                    **
**                   FEE_GC_WRITE: GC write operation is failed              **
**                   FEE_GC_TRIG: GC operation triggers the another GC       **
**                                Operation                                  **
** Description : This routine is responsible for marking state page during   **
**               Garbage Collection                                          **
******************************************************************************/
/* [cover parentID={54190B01-DE09-4565-8C2B-3F8B97E1354C}]
Fee_lGcProgramStatePage
[/cover] */
static uint8 Fee_lGcProgramStatePage(const uint8 GcState)
{
  uint32                 DestAddr;
  uint32                 FreePages;
  uint32                 PageCount;
  Fee_StateDataType     *StateDataPtr;
  uint8                  BankNumber;
  uint8                  Error;

  Error = FEE_GC_E_OK;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  if (StateDataPtr->FeeIntrJobStatus == FEE_JOB_DONE)
  {
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
    if((StateDataPtr->FeeIntrJobResult == FEE_JOB_FAIL) && 
       (StateDataPtr->FeeProgVerErr == FEE_RESET))
    {
      Error = FEE_GC_WRITE;
    }
    else
    {
      Fee_lGcStatePageCompare(GcState);
    }
  }
  else
  {
    DestAddr = StateDataPtr->FeeGcDestAddr;
    if(DestAddr >= FEE_DFLASH_BANK1_BASE)
    {
      BankNumber = FEE_SECTOR1;
    }
    else
    {
      BankNumber = FEE_SECTOR0;
    }

    switch (GcState)
    {
      case FEE_GC_MARK_SECTOR1_V_SP:
      case FEE_GC_MARK_SECTOR0_E_SP:
      case FEE_GC_INIT_MARK_SECTOR0_E_SP:
        {
          if (StateDataPtr->FeeIntrJobFailCount == FEE_RESET)
          {
            if (GcState == FEE_GC_MARK_SECTOR1_V_SP)
            {
              Fee_lPrepareStatePageBuffer(BankNumber, FEE_VALID);
            }
            else
            {
              Fee_lPrepareStatePageBuffer(BankNumber, FEE_ERASED);
            }
          }
          else
          {
            /* The state page is being re-attempted after one compare failure
            Clear the last 8bytes of GcReadWriteBuffer for comparison of SP */
            Fee_lClearMarkerBuffer();
          }
          while(Fee_lIsUnerasableAddr(DestAddr) == TRUE)
          {
            DestAddr = Fee_lGetNextWLAddr(DestAddr);
          }
          StateDataPtr->FeeGcDestAddr = DestAddr;

          /************* CHECK for the case of GC TRIGGERING GC *************/
          /* Get the Destination sector - the sector other than current sector
          */
          BankNumber = (uint8)StateDataPtr->FeeStatusFlags.FeeCurrSector ^ FEE_SECTOR1;
          /* Find the free pages in the destination sector */
          FreePages = Fee_lGetFreeDFLASHPages(BankNumber, DestAddr);
          /* Get the state page count */
          PageCount = FEE_DFLASH_WORDLINE_SIZE / FEE_DFLASH_PAGE_SIZE;
          /* Check if there is space in the new sector for state page */
          if ((boolean)TRUE == Fee_lIsSectorEndCrossed(FreePages, PageCount))
          {
            Error = FEE_GC_TRIG;
          }
          else
          {
            StateDataPtr->FeeLastReadSize = FEE_STATEPAGE_PROGRAM_SIZE;
            Error = Fee_lGcWrite((Fls_17_Dmu_AddressType)DestAddr, FEE_ZERO);
          }
          break;
        }

      /*
        Remaining cases:
          FEE_GC_MARK_SECTOR1_V_M
          FEE_GC_MARK_SECTOR0_E_M
          FEE_GC_INIT_MARK_SECTOR0_E_M
      */
      default:
        {
          Fee_lPrepareMarkerBuffer();
          StateDataPtr->FeeLastReadSize = FEE_STATEPAGE_MARKER_SIZE;
          Error = Fee_lGcWrite((Fls_17_Dmu_AddressType)
                               (DestAddr + FEE_STATEPAGE_DATA_SIZE),
                               FEE_STATEPAGE_DATA_SIZE);
          break;
        }
    }
  }

  return(Error);
}

/*CYCLOMATIC_Fee_lGcStatePageCompare_JUSTIFICATION: Fee_lGcStatePageCompare has
to determine all the states transitions of GC thereby causing the complexity to
become greater than 15, it is implemented through switch case which maintains
good readability, trying to break it will affect the readability.
*/
/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lGcStatePageCompare(const uint8 GcState)    **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  GcState: Current Gc State                               **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : Performs compare actions on state page programming           **
**               during Garbage collection                                    **
*******************************************************************************/
/* [cover parentID={A0DC241F-C69E-400b-AFF3-42C1376A57E8}]
Fee_lGcStatePageCompare
[/cover] */
LOCAL_INLINE void Fee_lGcStatePageCompare(const uint8 GcState)
{
  Fee_StateDataType    *StateDataPtr;
  Fee_SectorInfoType   *SectorInfoPtr;
  const uint8          *SrcAddr;
  uint32                DestAddr;
  uint8                 BankNumber;
  Std_ReturnType        ReturnVal1;
  uint32                PageCount;
  uint32                FreePages;
  const uint8          *PendReqStatePtr;
  uint8                 NewGcState;
  uint16             PendReqBlkNum;
  uint16             PendReqBlkIndex; 
  const Fee_BlockType  *PendReqBlkPtr; 


  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  PendReqStatePtr = &(StateDataPtr->FeePendReqStatus);
  DestAddr = StateDataPtr->FeeGcDestAddr;
  SrcAddr = StateDataPtr->FeeGcReadWriteBuffer;
  ReturnVal1 = E_OK;
  
  if(StateDataPtr->FeeProgVerErr == FEE_RESET)
  {  
/* [cover parentID={7A521C74-670B-48e3-B5F7-6EA67238D8D3}]
Compare the state page which was just written
[/cover] */
    ReturnVal1 = Fls_17_Dmu_CompareWordsSync(
                 (Fls_17_Dmu_AddressType)DestAddr,
                 /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for 
                 interfacing with FLS.FEE is passing parameters to FLS APIs, 
                 for example, Fls_17_Dmu_CompareWordsSync.Changing this will 
                 break the interfacing and will cause major functional
                 issues both on FLS and FEE side. */
                 (const uint32 *)SrcAddr,
                 (Fls_17_Dmu_LengthType)
                 FEE_STATEPAGE_SIZE / FEE_DFLASH_WORD_SIZE);
  }
  
  /* Compare failed or PVER error is set.*/
  if((ReturnVal1 == E_NOT_OK) || (StateDataPtr->FeeProgVerErr == FEE_SET))
  {
    if(StateDataPtr->FeeIntrJobFailCount == FEE_RESET)
    {
      /*Reset the FeeProgVerErr flag*/
      StateDataPtr->FeeProgVerErr = FEE_RESET;
      StateDataPtr->FeeIntrJobFailCount++;
      DestAddr = Fee_lGetNextWLAddr(DestAddr);
      StateDataPtr->FeeGcDestAddr =(DestAddr + FEE_DFLASH_WORDLINE_SIZE);

      switch (GcState)
      {
        case FEE_GC_MARK_SECTOR1_V_SP:
        case FEE_GC_MARK_SECTOR1_V_M:
          {
            NewGcState = FEE_GC_MARK_SECTOR1_V_SP;
            break;
          }

        case FEE_GC_MARK_SECTOR0_E_SP:
        case FEE_GC_MARK_SECTOR0_E_M:
          {
            NewGcState = FEE_GC_MARK_SECTOR0_E_SP;
            break;
          }

        /*
          Remaining cases:
            FEE_GC_INIT_MARK_SECTOR0_E_SP
            FEE_GC_INIT_MARK_SECTOR0_E_M
        */
        default:
          {
            NewGcState = FEE_GC_INIT_MARK_SECTOR0_E_SP;
            break;
          }
      }
      StateDataPtr->FeeGcState = NewGcState;
    }
    else
    {
      /* Write Fail two time raise the illegal notification. Pass the block 
      index as unused parameter , because block index is not used when write 
      error occurred. Block index is used only for read error to drop the block
      from GC process. */
      Fee_lGCErrorHandler(FEE_GC_WRITE , FEE_UNUSED_PARAM);
    }
  }
  else
  {
    switch (GcState)
    {
      case FEE_GC_MARK_SECTOR1_V_SP:
        {
          NewGcState = FEE_GC_MARK_SECTOR1_V_M;
          break;
        }
      case FEE_GC_MARK_SECTOR1_V_M:
        {
          StateDataPtr->FeeIntrJobFailCount = FEE_RESET;
          /* Update the current sector to next sector */
          StateDataPtr->FeeStatusFlags.FeeCurrSector ^= FEE_SECTOR1;

          /* Update FreeWLAddr and StatePage Address and NextFreePageAddr */
          BankNumber = StateDataPtr->FeeStatusFlags.FeeCurrSector;
          SectorInfoPtr = &StateDataPtr->FeeSectorInfo[BankNumber];
          SectorInfoPtr->StatePageAddr = DestAddr;
          SectorInfoPtr->NextFreeWLAddr = Fee_lGetNextWLAddr(DestAddr);
          /* Update NextFreePageAddr */
          StateDataPtr->FeeNextFreePageAddr = SectorInfoPtr->NextFreeWLAddr;

          StateDataPtr->FeeLastWrittenBlkInfo.BlockNumber = FEE_RESET;
          StateDataPtr->FeeLastWrittenBlkInfo.Status.Consistent = FEE_RESET;
          /*Check for the GC on GC*/
          FreePages = (uint32)Fee_lGetFreeDFLASHPages(
                        BankNumber, SectorInfoPtr->NextFreeWLAddr);
          /* Get the state page count */
          PageCount = FEE_DFLASH_WORDLINE_SIZE / FEE_DFLASH_PAGE_SIZE;
          /* Check if there is space in the new sector for state page */
          if ((boolean)TRUE ==
              Fee_lIsSectorThresholdCrossed(FreePages, PageCount))
          {
            
            /* Pass the block index as unused parameter,because block index is
             not used when GC on GC error occurred. Block index is used only 
             for read error to drop the block from GC process. */ 
              
            Fee_lGCErrorHandler(FEE_GC_TRIG , FEE_UNUSED_PARAM );
            /*set the flag to previous state,so that driver remains in busy
             state.*/
            StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_COMPARE;
            StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
            StateDataPtr->FeeIntrJobResult = FEE_JOB_FAIL;
            NewGcState = FEE_GC_FAIL;
#if (FEE_GET_PREV_DATA_API == STD_ON)
            StateDataPtr->FeePendReqInfo.GetPrevCopy = FEE_RESET;
#endif
            break;
          }

          if(BankNumber == FEE_SECTOR0)
          {
            StateDataPtr->FeeGcDestAddr = FEE_DFLASH_BANK1_BASE;
          }
          else
          {
            StateDataPtr->FeeGcDestAddr = FEE_DFLASH_BANK0_BASE;
          }

          /*Checking for Pending write during GC*/
          if((*PendReqStatePtr == FEE_REQ_NORM_WRITE) ||
              (*PendReqStatePtr == FEE_REQ_IMM_WRITE))
          {
            /* Check if there is space in the new sector for writing pending 
            block.if no space available then raise the GC on GC DEM and illegal
            state notification */
            PendReqBlkNum = StateDataPtr->FeePendReqInfo.BlockNumber;
            PendReqBlkIndex = Fee_lGetUsrBlockIndex(PendReqBlkNum); 
            PendReqBlkPtr = &(Fee_CfgPtr->FeeBlockConfigPtr[PendReqBlkIndex]); 
        
            if (E_NOT_OK == Fee_lPerformCurrBlkCheck(PendReqBlkPtr))
            {
              /* Pass the block index as unused parameter,because block index is
              not used when GC on GC error occurred. Block index is used only 
              for read error to drop the block from GC process. */ 
              Fee_lGCErrorHandler(FEE_GC_TRIG , FEE_UNUSED_PARAM);
              
              StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_NO_REQ;
              StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
              StateDataPtr->FeeIntrJobResult = FEE_JOB_FAIL;
              NewGcState = FEE_GC_FAIL;
#if (FEE_GET_PREV_DATA_API == STD_ON)
              StateDataPtr->FeePendReqInfo.GetPrevCopy = FEE_RESET;
#endif
              break;
            }

          }
#if (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
          /* Move to next state */
          NewGcState = FEE_GC_HARDEN_QS_SECTOR;

#else
          /* Move to next state */
          NewGcState = FEE_GC_ERASE_PREV_SECTOR;
#endif
          break;
        }
      case FEE_GC_MARK_SECTOR0_E_SP:
        {

          NewGcState = FEE_GC_MARK_SECTOR0_E_M;
          break;
        }
      case FEE_GC_INIT_MARK_SECTOR0_E_SP:
        {
          NewGcState = FEE_GC_INIT_MARK_SECTOR0_E_M;
          break;
        }
      /*
        Remaining cases:
          FEE_GC_MARK_SECTOR0_E_M
          FEE_GC_INIT_MARK_SECTOR0_E_M
      */
      default:
        {
          StateDataPtr->FeeIntrJobFailCount = FEE_RESET;
          /* Get the current active sector number */
          BankNumber = StateDataPtr->FeeStatusFlags.FeeCurrSector;
          /* calculate the previous sector number */
          BankNumber = BankNumber ^ FEE_SECTOR1;
          /* Update FreeWLAddr and StatePage Address */
          SectorInfoPtr = &StateDataPtr->FeeSectorInfo[BankNumber];
          SectorInfoPtr->StatePageAddr = DestAddr;
          SectorInfoPtr->NextFreeWLAddr = Fee_lGetNextWLAddr(DestAddr);
          if (GcState == FEE_GC_MARK_SECTOR0_E_M)
          {
            NewGcState = FEE_GC_IDLE;
          }
          else
          {
            NewGcState = FEE_GC_REQUESTED;
          }
          break;
        }
    }
    StateDataPtr->FeeGcState = NewGcState;
  }
}

/*CYCLOMATIC_Fee_lGarbageCollection_JUSTIFICATION: Fee_lGarbageCollection has
to determine all the states of configure/unconfigure block and then generate 
DEM.It should also handle the hardening feature during GC, if it is broken into
more functions to fix RSM, the code readability will get affected.
*/
/*******************************************************************************
** Syntax : static void Fee_lGarbageCollection(void)                          **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine is responsible for handling Garbage Collection  **
** which is done once the Sector reaches the threshold limit.                 **
*******************************************************************************/
/* [cover parentID={6F6B5F25-8CB4-48f1-9634-938B72007142}]
Fee_lGarbageCollection
[/cover] */
static void Fee_lGarbageCollection(void)
{
  /* [cover parentID={6F6B5F25-8CB4-48f1-9634-938B72007142}]*/
  Fee_StateDataType     *StateDataPtr;
  uint8                  Error;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;


  /* Asynchronous Transitions based ONLY on IntrJobStatus are done here */
  Fee_lGcPrologue();

  /**********************************************************************/
  /*         STATE MACHINE EXECUTION and STATE TRANSITIONS              */
  /**********************************************************************/

  /*********** GC REQSTD STATE *******************/
  /*  Initialization of variables is done here */
  if(StateDataPtr->FeeGcState == FEE_GC_REQUESTED)
  {
#if (FEE_UNCFG_BLK_OVERFLOW_HANDLE == FEE_STOP_AT_GC)
    if(StateDataPtr->FeeUncfgBlksExceeded != FEE_UNCONFIG_BLK_LIMIT_CROSSED)
#endif
    {
      Fee_lGcRequested();
    }
  }


  Error = Fee_lHandleGcCopy();

  /***** FEE_GC_INIT_ERASE_PREV_SECTOR / FEE_GC_ERASE_PREV_SECTOR *********/
  /*  Erasing the previous sector is done here */
  if (StateDataPtr->FeeGcState == FEE_GC_ERASE_PREV_SECTOR)
  {
    Error = Fee_lGcErasePrevSector(FEE_GC_ERASE_PREV_SECTOR);
  }
  if (StateDataPtr->FeeGcState == FEE_GC_INIT_ERASE_PREV_SECTOR)
  {
    Error = Fee_lGcErasePrevSector(FEE_GC_INIT_ERASE_PREV_SECTOR);
  }


  /***** FEE_GC_INIT_MARK_SECTOR0_E_SP /
        FEE_GC_MARK_SECTOR0_E_SP *********/
  /*  Writing the erased state page content is done here */
  if (StateDataPtr->FeeGcState == FEE_GC_MARK_SECTOR0_E_SP)
  {
    Error = Fee_lGcProgramStatePage(FEE_GC_MARK_SECTOR0_E_SP);
  }
  if (StateDataPtr->FeeGcState == FEE_GC_INIT_MARK_SECTOR0_E_SP)
  {
    Error = Fee_lGcProgramStatePage(FEE_GC_INIT_MARK_SECTOR0_E_SP);
  }

  /***** FEE_GC_INIT_MARK_SECTOR0_E_M /
        FEE_GC_MARK_SECTOR0_E_M *********/
  /*  Writing the erased state page marker is done here */
  if (StateDataPtr->FeeGcState == FEE_GC_MARK_SECTOR0_E_M)
  {
    Error = Fee_lGcProgramStatePage(FEE_GC_MARK_SECTOR0_E_M);
  }

  if (StateDataPtr->FeeGcState == FEE_GC_INIT_MARK_SECTOR0_E_M)
  {
    Error = Fee_lGcProgramStatePage(FEE_GC_INIT_MARK_SECTOR0_E_M);
  }
  /* [cover parentID={A53CCA55-0E57-4a1d-A649-CE140A625038}]*/
#if (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
  if(StateDataPtr->FeeGcState == FEE_GC_HARDEN_QS_SECTOR)
  {  
    /* [cover parentID={A53CCA55-0E57-4a1d-A649-CE140A625038}]
Check if hardening is required
[/cover] */
    Fee_lGcHardenQsSector();
  }
#endif
  /* Report Dem, if Error occurred */
  if (Error != FEE_GC_E_OK)
  {
    /* Clear all variables */
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
    StateDataPtr->FeeIntrJobResult = FEE_JOB_FAIL;
    StateDataPtr->FeeIntrJob = FEE_NO_JOB;

    /* Write/erased failed raise the illegal notification.block index 
    parameter is not used for write/erase error,so passed as parameter not 
    used.Block index is used only for read error to drop the block from GC 
    process. */
    Fee_lGCErrorHandler(Error, FEE_UNUSED_PARAM );
  }
}/*End of Fee_lGarbageCollection */

/*******************************************************************************
** Syntax : static Fee_PageType Fee_lGetDFLASHPages(const uint16 Size)        **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  (uint16)size                                            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Fee_PageType                                            **
**                                                                            **
** Description : This routine will calculate and return the number of DFLASH  **
** pages required for a logical block size.                                   **
*******************************************************************************/
static Fee_PageType Fee_lGetDFLASHPages(const uint16 Size)
{
  Fee_PageType  PhysicalPages;
  uint16        NewSize;

  PhysicalPages = FEE_BLOCK_MANGMNT_PAGES;
  NewSize       = Size;

  while (NewSize >= FEE_SEVEN)
  {
    PhysicalPages++;
    NewSize -= FEE_SEVEN;
  }

  if (NewSize > FEE_ZERO)
  {
    PhysicalPages++;
  }

  return(PhysicalPages);

}/*End of Fee_lGetDFLASHPages */


/*******************************************************************************
** Syntax : static uint32 Fee_lGetFreeDFLASHPages(const uint8 BankNumber      **
**                                               const uint32 StartAddr)      **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :(uint8)BankNumber : Bank Number                           **
**                  (uint32)StartAddr  : Current address                      **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  uint32                                                  **
**                                                                            **
** Description : This routine will calculate the number of empty DFLASH  pages**
** remaining in the sector.                                                   **
*******************************************************************************/
static uint32 Fee_lGetFreeDFLASHPages(const uint8 BankNumber,
                                      const uint32 StartAddr)
{
  const Fee_StateDataType *StateDataPtr;
  uint32             FreePages;
  uint32             EndAddr;
  uint32             WLAddr;
  sint32             RemainingPages;
  uint8              Count;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* Get the sector end address */
  if (BankNumber == FEE_SECTOR0)
  {
    EndAddr = FEE_DFLASH_BANK0_BASE + FEE_DFLASH_SECTOR_SIZE;
  }
  else
  {
    EndAddr = FEE_DFLASH_BANK1_BASE + FEE_DFLASH_SECTOR_SIZE;
  }

  RemainingPages = ( ((sint32)EndAddr - (sint32)StartAddr) /
                     (sint32)FEE_DFLASH_PAGE_SIZE );

  /* Subtract the pages of un-erasable word line, if any */
  Count = FEE_RESET;
  while(Count < StateDataPtr->FeeSectorInfo[BankNumber].UnerasableWLCount)
  {
    WLAddr = StateDataPtr->FeeSectorInfo[BankNumber].UnerasableWLAddr[Count];
    if ( (StartAddr <= WLAddr) && (WLAddr <= EndAddr) )
    {
      RemainingPages = RemainingPages -
                       (sint32)(FEE_DFLASH_WORDLINE_SIZE / FEE_DFLASH_PAGE_SIZE);
    }
    Count++;
  }


  if (RemainingPages > (sint32)FEE_ZERO)
  {
    FreePages = (uint32)RemainingPages;
  }
  else
  {
    FreePages = FEE_RESET;
  }

  return(FreePages);

}/*End of Fee_lGetFreeDFLASHPages */

#endif
/*******************************************************************************
** Syntax : static uint16 Fee_lGetUsrBlockIndex(const uint16 BlockNumber)     **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : (uint16) BlockNumber - Number of logical block           **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  uint16                                                  **
**                                                                            **
** Description : This utility function will return the Index (location)of the **
** block in the user configuration.                                           **
*******************************************************************************/
/*[cover parentID={AFA436A3-0ED3-4e88-B7DD-8E552415D1EB}][/cover]*/
static uint16 Fee_lGetUsrBlockIndex(const uint16 BlockNumber)
{
  const Fee_BlockType  *BlockPtr;
  uint16                Index;
  uint16                BlockNumberRef;

  Index = FEE_RESET;

  BlockPtr = &(Fee_CfgPtr->FeeBlockConfigPtr[Index]);

  BlockNumberRef = BlockPtr->BlockNumber;

  while( (Index < Fee_CfgPtr->FeeBlkCnt) &&
         (BlockNumberRef != BlockNumber)
       )
  {
    Index++;

    if(Index < Fee_CfgPtr->FeeBlkCnt )
    {
      BlockNumberRef = BlockPtr[Index].BlockNumber;
    }

  }

  /* if block is not configured, return invalid block index */
  if( Index == Fee_CfgPtr->FeeBlkCnt )
  {
    Index = FEE_LOG_BLOCK_NOT_FOUND;
  }

  return(Index);

}/* End of Fee_lGetUsrBlockIndex */

/*CYCLOMATIC_Fee_lComputeNextFreePageAddr_JUSTIFICATION:
The complexity of this is marginally over 15(complexity is 16).
Fee_lComputeNextFreePageAddr has to determine the next free page address,
for which it checks for the un-erasable WL, the checks are simple and few.
so, these cannot be avoided as the readability will get affected, if it is
broken into multiple functions.
*/
/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lComputeNextFreePageAddr                    **
**                                            (const uint32 BankNumber)       **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :BankNumber                                            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This utility function computes the first free page address   **
** of the sector based on NextFreeWLAddr                                      **
*******************************************************************************/
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/* [cover parentID={6C36A6FC-E37D-489b-A42E-CC3C75D504D3}]
Fee_lComputeNextFreePageAddr
[/cover] */
LOCAL_INLINE void Fee_lComputeNextFreePageAddr(const uint32 BankNumber)
{
  Fee_StateDataType  *StateDataPtr;
  const Fee_SectorInfoType *SectorInfoPtr;
  const uint32             *TempDataPtr;
  uint32              TempAddr;
  uint32              TempAddrPrevWL;
  Std_ReturnType      RetVal;
  uint8               LoopEnd;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  SectorInfoPtr = &StateDataPtr->FeeSectorInfo[BankNumber];
  LoopEnd = FEE_RESET;

  /* Get the WL before the Next Free WL of the sector */
  StateDataPtr->FeeNextFreePageAddr = SectorInfoPtr->NextFreeWLAddr;

  /* Check if the WL before the free WL is state page */
  TempAddrPrevWL = SectorInfoPtr->NextFreeWLAddr - FEE_DFLASH_WORDLINE_SIZE;

  /* If previous word line contains a state page OR
     if it is an un-erasable word line, then next free page address is same
     as next free word line address; otherwise proceed to identify the
     next free page address */
  if((TempAddrPrevWL != SectorInfoPtr->StatePageAddr) &&
      (!((SectorInfoPtr->UnerasableWLCount != FEE_RESET) &&
         ((SectorInfoPtr->UnerasableWLAddr[0]  == TempAddrPrevWL) ||
          (SectorInfoPtr->UnerasableWLAddr[1]  == TempAddrPrevWL)))))
  {
    TempAddr = SectorInfoPtr->NextFreeWLAddr ;

    TempAddrPrevWL += FEE_DFLASH_PAGE_SIZE;

    do
    {
      TempAddr -= FEE_DFLASH_PAGE_SIZE;
      /* Read the header (2 Words) */
      
       /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with 
       FLS.FEE is passing parameters to FLS APIs, for example, 
       Fls_17_Dmu_ReadWordsSync Changing this will break the interfacing and 
       will cause major functional issues both on FLS and FEE side. */
      
      RetVal = Fls_17_Dmu_ReadWordsSync((Fls_17_Dmu_AddressType)TempAddr,\
                                 (uint32 *)StateDataPtr->FeeReadWriteBuffer,\
                                 (Fls_17_Dmu_LengthType)
                                 (FEE_DFLASH_PAGE_SIZE / FEE_DFLASH_WORD_SIZE));
                                 
      /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
      TempDataPtr = (uint32 *)StateDataPtr->FeeReadWriteBuffer;

      if((RetVal == E_OK) && (*(TempDataPtr) == (uint32)FEE_RESET) &&
          (TempDataPtr[1] == (uint32)FEE_RESET))
      {
        StateDataPtr->FeeNextFreePageAddr = TempAddr;
      }
      else
      {
        LoopEnd = FEE_SET ;
        if ((RetVal == E_OK) &&
            ((StateDataPtr->FeeReadWriteBuffer[0] == FEE_DATA_NEXT_PAGE_ID) ||
             (StateDataPtr->FeeReadWriteBuffer[0] == FEE_DATA_FIRST_PAGE_ID)))
        {
          StateDataPtr->FeeLastWrittenBlockDirty = FEE_LWB_CHECK_FOR_DIRTY;
        }
        else if (RetVal != E_OK)
        {
          StateDataPtr->FeeNextFreePageAddr = SectorInfoPtr->NextFreeWLAddr;
        }
        else
        {
          /* dummy else */
        }
      }
    }
    while ((TempAddr > TempAddrPrevWL) && (LoopEnd == FEE_RESET));
  }
}

/*******************************************************************************
** Syntax : static void Fee_lUpdateCache(void)                                **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This utility function  will update the cache which contains  **
** the latest information about the DFLASH contents.                          **
*******************************************************************************/
/* [cover parentID={7EF281BE-B4A1-44d3-B03F-F5841091218F}][/cover] */ 
static void Fee_lUpdateCache(void)
{
  Fee_StateDataType      *StateDataPtr;
  Fee_SectorInfoType     *SectorInfoPtr;
  uint32                  EndAddr;
  uint32                  BankNumber;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  if(StateDataPtr->FeeStatusFlags.FeeCurrSector == (uint32)FEE_SECTOR0)
  {
    EndAddr = FEE_DFLASH_BANK0_BASE;
    BankNumber = FEE_SECTOR0;
  }
  else
  {
    EndAddr = FEE_DFLASH_BANK1_BASE;
    BankNumber = FEE_SECTOR1;
  }

  SectorInfoPtr = &StateDataPtr->FeeSectorInfo[BankNumber];

  /* Identifies next free page */
  Fee_lComputeNextFreePageAddr(BankNumber);

  /* Point to last written page of the valid sector */
  StateDataPtr->FeeCurrSectSrcAddr = StateDataPtr->FeeNextFreePageAddr -
                                     FEE_DFLASH_PAGE_SIZE;

  /* Reset the number of pages in the block */
  StateDataPtr->FeeBlkPageCount = FEE_RESET;

  /* Start the Cache Update state machine */
  StateDataPtr->FeeCacheState = FEE_CACHE_FIND_NEXT_BLK;

  Fee_lUpdateCacheTable(BankNumber, EndAddr);

  /* check if marker is missing for the last written block */
  if(StateDataPtr->FeeLastWrittenBlockDirty == FEE_LWB_DIRTY)
  {
    /* move next free page address to next page */
    /* to avoid any further write attempts on the missing marker location */
    StateDataPtr->FeeNextFreePageAddr += FEE_DFLASH_PAGE_SIZE;
    /* If next free page is the beginning of a word line */
    if(Fee_lIsWLBeginning(StateDataPtr->FeeNextFreePageAddr) == 
       FEE_NEW_WL_BEGIN)
    {
      /* clear last written block info */
      StateDataPtr->FeeLastWrittenBlkInfo.BlockNumber = FEE_RESET;
      StateDataPtr->FeeLastWrittenBlkInfo.Status.Consistent = FEE_RESET;
    }
    /* if next free page address is beyond next free word line address */
    if(StateDataPtr->FeeNextFreePageAddr > SectorInfoPtr->NextFreeWLAddr)
    {
      /* move next free word line to its next word line */
      SectorInfoPtr->NextFreeWLAddr += (FEE_DFLASH_WORDLINE_SIZE);
    }
  }

}/* End of Fee_lUpdateCache */
#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lComputeNextWLAddr                          **
**                               (Fee_SectorInfoType * const SectorInfoPtr)   **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : SectorInfoPtr - Pointer to Sector Info               **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This utility function will confirm the next free WL address  **
*******************************************************************************/
/* [cover parentID={70343C38-995B-41b2-B7E7-7CB215F859C6}]
Fee_lComputeNextWLAddr
[/cover] */
LOCAL_INLINE void Fee_lComputeNextWLAddr(Fee_SectorInfoType * const \
    SectorInfoPtr)
{
  uint32 index;
  const uint32 *SrcPtr;
  Fee_StateDataType  *StateDataPtr;
  Std_ReturnType      ReturnValueFls;
  uint32 Length;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  SrcPtr =
    /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for qualified pointer
    MISRA11.3 is applicable for unqualified pointers*/
    (const uint32 *)(StateDataPtr->FeeReadWriteBuffer);
  Length = FEE_DFLASH_WORDLINE_SIZE / FEE_DFLASH_WORD_SIZE;

  /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with FLS.
  FEE is passing parameters to FLS APIs, for example, Fls_17_Dmu_ReadWordsSync.
  Changing this will break the interfacing and will cause major functional 
  issues both on FLS and FEE side. */
  
  ReturnValueFls = Fls_17_Dmu_ReadWordsSync(\
                     (Fls_17_Dmu_AddressType)SectorInfoPtr->NextFreeWLAddr,\
                     (uint32 *)(StateDataPtr->FeeReadWriteBuffer),\
                     (Fls_17_Dmu_LengthType)(Length));

  /* If read error -> word line is not empty */
  if(ReturnValueFls == E_NOT_OK)
  {
    SectorInfoPtr->NextFreeWLAddr =
      Fee_lGetNextWLAddr(SectorInfoPtr->NextFreeWLAddr);
  }
  else
  {
    /* check if word line is empty */
    index = FEE_RESET;
    while((index < Length) && (*SrcPtr == (uint32)FEE_RESET))
    {

      SrcPtr++;
      index++;
    }
    /* if word line is not empty, move to next word line */
    if(index < Length)
    {
      SectorInfoPtr->NextFreeWLAddr =
        Fee_lGetNextWLAddr(SectorInfoPtr->NextFreeWLAddr);
    }
  }
} /* End of Fee_lComputeNextWLAddr */

/*CYCLOMATIC_Fee_lUpdateCacheTable_JUSTIFICATION: Fee_lUpdateCacheTable is the
 function will search for data block and update cache table from free page of
 the sector.If broken into more functions, the maintenance/readability will get
  affected.
*/
/*******************************************************************************
** TRACEABILITY: []                                                           **
**                                                                            **
** Syntax : LOCAL_INLINE void Fee_lUpdateCacheTable(                          **
**                                      const uint32 BankNumber,              **
**                                      const uint32 EndAddr                  **
**                                    )                                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :BankNumber                                            **
**                      EndAddr                                               **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This utility function  will search through the DFLASH from   **
**  the free page of the sector until the start page of a data block is found **
*******************************************************************************/
LOCAL_INLINE void Fee_lUpdateCacheTable(const uint32 BankNumber, \
                                        const uint32 EndAddr)
{
  Fee_StateDataType       *StateDataPtr;
  uint8             *ReadWriteBufferPtr;
  uint32                   WordValue[2];
  uint32                   LWBHeaderAddress;
  uint32                   LWBMarkerAddress;
  uint32                   DataNextPageCount;
  uint16                   PageCount;
  uint16                   PageCount1;
  uint16                   BlockNumber;
  uint8                    PageId;
  uint8                    PotentialMarkerPage;
  Std_ReturnType           RetVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  ReadWriteBufferPtr = StateDataPtr->FeeReadWriteBuffer;
  PotentialMarkerPage = FEE_RESET;
  DataNextPageCount = FEE_RESET;
   /* [cover parentID={072E5B18-2913-4d67-8623-1683EAE5D122}]
      Fee_lUpdateCacheTable
      [/cover] */
  do
  {
    /* Check for unerasable WL */
    while((Fee_lIsUnerasableAddr(StateDataPtr->FeeCurrSectSrcAddr) == TRUE) &&
          (StateDataPtr->FeeCacheState != FEE_CACHE_UPDATE_COMPLETE))
    {
      Fee_lCheckPrevPage(EndAddr);
    }

    if (StateDataPtr->FeeCacheState != FEE_CACHE_UPDATE_COMPLETE)
    {
      /* Read the header (2 Words) */
      /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with FLS.
      FEE is passing parameters to FLS APIs.MISRA 11.3 is applicable only to the
      unqualified pointers.Here qualified typecasting has been used*/
      
      RetVal = Fls_17_Dmu_ReadWordsSync(\
                 (Fls_17_Dmu_AddressType)StateDataPtr->FeeCurrSectSrcAddr,\
                 (uint32 *)ReadWriteBufferPtr,\
                 (Fls_17_Dmu_LengthType)\
                 (FEE_DFLASH_PAGE_SIZE / FEE_DFLASH_WORD_SIZE));

      if(StateDataPtr->FeeLastWrittenBlockDirty == FEE_LWB_CHECK_FOR_DIRTY)
      {

        if((RetVal == E_NOT_OK) ||
            ((ReadWriteBufferPtr[0] != FEE_DATA_FIRST_PAGE_ID) &&
             (ReadWriteBufferPtr[0] != FEE_DATA_NEXT_PAGE_ID)))
        {
          StateDataPtr->FeeLastWrittenBlockDirty = FEE_LWB_NOT_DIRTY;
        }
      }

      if(RetVal == E_NOT_OK)
      {
        /*Reading of page is failed due to error (ECC error or HW busy)
        and if this marker page then clear PotentialMarkerPage. This will
        avoid storing block data in cache with corrupted marker page and
        illegal notification while GC */
        PotentialMarkerPage = FEE_RESET;
        DataNextPageCount = FEE_RESET;
      }
      else
      {
        /* Evaluate the header read */
        PageId = *ReadWriteBufferPtr;
        /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array 
        buffer*/
        WordValue[0] = *((const uint32 *)ReadWriteBufferPtr);
        /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array
         buffer*/
        WordValue[1]=*(const uint32 *)&(ReadWriteBufferPtr[FEE_DFLASH_WORD_SIZE]);

        /* Check for data continuation page */
        if (WordValue[0] == FEE_DP_MARKER_WORD)
        {
         
          DataNextPageCount = FEE_RESET;


          PageCount1 = ((uint16)((uint16)(ReadWriteBufferPtr[7]) << FEE_EIGHT) |
                        ReadWriteBufferPtr[6]);
          PageCount = (PageCount1 & (uint16)FEE_PAGE_COUNT_MASK);

          BlockNumber =((uint16)((uint16)(ReadWriteBufferPtr[5]) << FEE_EIGHT) |
                         ReadWriteBufferPtr[4]);
          LWBMarkerAddress = StateDataPtr->FeeCurrSectSrcAddr;
          if(StateDataPtr->FeeSectorInfo[BankNumber].UnerasableWLCount ==
              FEE_RESET)
          {
            LWBHeaderAddress = LWBMarkerAddress - (
                                         (uint32)PageCount << FEE_PAGE_TO_BYTE);
          }
          else
          {
            LWBHeaderAddress = Fee_lGetBlockHeaderAddress(LWBMarkerAddress,
                               PageCount);
          }
          if((LWBHeaderAddress > EndAddr) && (PageCount1 != FEE_RESET) && 
             (LWBHeaderAddress < (FEE_DFLASH_SECTOR_SIZE * FEE_TWO )))
          {

            /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing 
            with FLS.FEE is passing parameters to FLS APIs, for example,
            Fls_17_Dmu_ReadWordsSync. Changing this will break the interfacing
            and will cause major functional issues both on FLS and FEE side.*/   
            RetVal = Fls_17_Dmu_ReadWordsSync(\
                       (Fls_17_Dmu_AddressType)LWBHeaderAddress,\
                       (uint32 *)ReadWriteBufferPtr,\
                       (Fls_17_Dmu_LengthType)\
                       (FEE_DFLASH_PAGE_SIZE / FEE_DFLASH_WORD_SIZE));

            if(RetVal == E_OK)
            {

              RetVal = Fee_lEvaluateBlkHeader(BlockNumber, PageCount1);
              if(RetVal == E_OK)
              {
                Fee_lHandleBlkMarkerFound(LWBHeaderAddress, LWBMarkerAddress,
                                          PageCount);
                PotentialMarkerPage = FEE_RESET;
               /* Block Header page is valid and no need to scan the data pages
                for ECC error because ECC error will be detected during the
                read and GC.Block with ECC error in data pages will be treated
                as inconsistent during GC and will be not be copied to another
                sector. This will reduce the  the time for cache table build.
                skipping of data pages is done by setting the
               StateDataPtr->FeeCurrSectSrcAddr address to LWBHeaderAddress */
               StateDataPtr->FeeCurrSectSrcAddr = LWBHeaderAddress;
              }
              else
              {
                               
                /* Block Header page is not valid and no need to scan the data
                pages.Skiping of data pages is done by setting the
                StateDataPtr->FeeCurrSectSrcAddr address to LWBHeaderAddress */
                 PotentialMarkerPage = FEE_RESET;
                 StateDataPtr->FeeCurrSectSrcAddr = LWBHeaderAddress;
              }
            }
            else
            {
               PotentialMarkerPage = FEE_RESET;
               /* Block Header page is not valid and no need to scan the data
               pages.Skiping of data pages is done by setting the
               StateDataPtr->FeeCurrSectSrcAddr address to LWBHeaderAddress */
               StateDataPtr->FeeCurrSectSrcAddr = LWBHeaderAddress;
            }
          }
          else
          {
            PotentialMarkerPage = FEE_SET ;
            DataNextPageCount = FEE_RESET;
          }
        }
        else if (PageId == FEE_DATA_NEXT_PAGE_ID)
        {
          DataNextPageCount++;
        }
        /* Check for data first page */
        else if (PageId == FEE_DATA_FIRST_PAGE_ID)
        {
          Fee_lHandleBlkHeaderFound(PotentialMarkerPage, DataNextPageCount);
          DataNextPageCount = FEE_RESET;
          PotentialMarkerPage = FEE_RESET;
        }
        else
        {
          DataNextPageCount = FEE_RESET;

          if(((WordValue[0] == (uint32)FEE_RESET) &&
              (WordValue[1] == (uint32)FEE_RESET)) ||
              (ReadWriteBufferPtr[0] == FEE_STATE_FIRST_PAGE_ID))
          {
            PotentialMarkerPage = FEE_RESET;
          }
          else
          {
            /* Current page data is corrupted and if this marker page then
               clear PotentialMarkerPage. This will avoid storing block data
               in cache with corrupted marker page and illegal notification
               while GC  */
            PotentialMarkerPage = FEE_RESET;
          }
        }
      }
      Fee_lCheckPrevPage(EndAddr);
    }
  }
  while(StateDataPtr->FeeCacheState == FEE_CACHE_FIND_NEXT_BLK);
}
#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** Syntax : LOCAL_INLINE Std_ReturnType Fee_lEvaluateBlkHeader                **
**                                         (const uint16 BlockNumber,         **
**                                          const uint16 BlockPageCount)      **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockNumber - Logical block number                      **
**                    BlockPageCount - Page Count of the corresponding block  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                   E_OK:Block Header page is matching with marker page.     **
**                   E_NOT_OK:Block Header page is not matching with marker   **
**                   page.                                                    **
**                                                                            **
** Description : This function evaluates block header page with respect to    **
**               block marker page                                            **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fee_lEvaluateBlkHeader(const uint16 BlockNumber,
    const uint16 BlockPageCount)
{
  const Fee_StateDataType          *StateDataPtr;
  const uint8                *ReadWriteBufferPtr;
  uint16                      BlockNumber1;
  uint16                      PageCount1;
  Std_ReturnType              RetVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  ReadWriteBufferPtr = StateDataPtr->FeeReadWriteBuffer;

  BlockNumber1 = (uint16)((uint16)ReadWriteBufferPtr[2] << FEE_EIGHT) |
                 ReadWriteBufferPtr[1];

  PageCount1   = (uint16)((uint16)ReadWriteBufferPtr[7] << FEE_EIGHT) |
                 ReadWriteBufferPtr[6];


  if((BlockNumber == BlockNumber1) &&
      (BlockPageCount == PageCount1) &&
      (ReadWriteBufferPtr[0] == FEE_DATA_FIRST_PAGE_ID))
  {
    RetVal = E_OK;
  }
  else
  {
    RetVal = E_NOT_OK;
  }

  return(RetVal);
}

/*******************************************************************************
** Syntax : LOCAL_INLINE uint32 Fee_lGetBlockHeaderAddress                    **
**                                           (const uint32 LWBMarkerAddress,  **
**                                            const uint16 PageCount)         **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  (uint32)LWBMarkerAddress - Last Written Block's Marker  **
                                                 Address                      **
**                    (uint16)PageCount - Page Count of the corresponding     **
**                                          block                             **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  uint32 - Block header address                           **
**                                                                            **
** Description : This function returns the address of the block's header      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Fee_lGetBlockHeaderAddress(const uint32 LWBMarkerAddress,
    const uint16 PageCount)
{
  uint32 BlockSize;
  uint32 NewLWBMarkerAddress;

  BlockSize = (uint32)PageCount << FEE_PAGE_TO_BYTE;
  NewLWBMarkerAddress = (uint32)LWBMarkerAddress;

  do
  {
    NewLWBMarkerAddress -= FEE_DFLASH_PAGE_SIZE;
    if(Fee_lIsUnerasableAddr(NewLWBMarkerAddress) == (boolean)FALSE)
    {
      BlockSize -= FEE_DFLASH_PAGE_SIZE;
    }
  }
  while(BlockSize > FEE_ZERO);

  return(NewLWBMarkerAddress);
}

/******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lHandleBlkMarkerFound                      **
**                                        (const uint32 LWBHeaderAddress,    **
**                                         const uint32 LWBMarkerAddress,    **
**                                         const uint16 PageCount)           **
**                                                                           **
** Service ID:                                                               **
**                                                                           **
** Sync/Async:  Synchronous                                                  **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) : (uint32) LWBHeaderAddress - Last Written Block's Header **
                                                 Address                     **
**                   (uint32) LWBMarkerAddress - Last Written Block's Marker **
                                                  Address                    **
**                   (uint16) PageCount - Page Count of the corresponding    **
                                           block                             **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  void                                                   **
**                                                                           **
** Description:This function does the cache table update and other necessary **
**             handling when the block's marker is found during cache build  **
******************************************************************************/
/* [cover parentID={37A9C2EB-D1A4-442b-BBF2-9540B6A49AF5}]
Fee_lHandleBlkMarkerFound
[/cover] */
LOCAL_INLINE void Fee_lHandleBlkMarkerFound(const uint32 LWBHeaderAddress,
    const uint32 LWBMarkerAddress,
    const uint16 PageCount)
{
  Fee_StateDataType          *StateDataPtr;
  Fee_LastWrittenBlkInfoType *LastWrittenBlkPtr;
  const uint8                      *ReadWriteBufferPtr;
  Fee_CacheStatusType         Status;
  uint32                      NextFreePageWLAddr;
  uint16                      BlockNumber;
  uint16                      Index;

  Status.Valid = FEE_RESET;
  Status.Consistent = FEE_RESET;
  Status.Copied = FEE_RESET;
  Status.PrevCopyValid = FEE_RESET;
  Status.PrevCopyConsistent = FEE_RESET;
  Status.PrevCopyCopied = FEE_RESET;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  ReadWriteBufferPtr = StateDataPtr->FeeReadWriteBuffer;
  LastWrittenBlkPtr = &(StateDataPtr->FeeLastWrittenBlkInfo);
  StateDataPtr->FeeCurrSectSrcAddr = LWBHeaderAddress;

  BlockNumber = (uint16)((uint16)ReadWriteBufferPtr[2] << FEE_EIGHT) |
                ReadWriteBufferPtr[1];
  Index = Fee_lGetUsrBlockIndex(BlockNumber);


  if((ReadWriteBufferPtr[7] & FEE_VALID_MASK) != FEE_RESET)
  {
    Status.Valid = FEE_SET ;
  }
  else
  {
    Status.Valid = FEE_RESET;
  }
  Status.Consistent = FEE_SET ;

  /* Updated cache table */
  if ((Index != FEE_LOG_BLOCK_NOT_FOUND))
  {

      Fee_lUpdateBlockInfo(Status, Index, PageCount);
    
  }
  else
  {
    Fee_lUpdateUnconfigBlockInfo(BlockNumber, PageCount);
  }

  /* Updated last written block info, if not done */
  if(LastWrittenBlkPtr->BlockNumber == FEE_RESET)
  {
    NextFreePageWLAddr = Fee_lGetWLBeginning(StateDataPtr->FeeNextFreePageAddr);
    if((LWBHeaderAddress < NextFreePageWLAddr) &&
        (LWBMarkerAddress >= NextFreePageWLAddr))
    {
      LastWrittenBlkPtr->PageCount = PageCount + FEE_ONE;
      LastWrittenBlkPtr->Addr = LWBHeaderAddress;
      LastWrittenBlkPtr->BlockNumber = BlockNumber;
      LastWrittenBlkPtr->Status.Consistent = FEE_SET ;
    }
    else if (LWBMarkerAddress < NextFreePageWLAddr)
    {
      LastWrittenBlkPtr->BlockNumber = FEE_16_BIT_ALL_ONES;
    }
    else
    {
      /* dummy else */
    }
  }
}

/******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lHandleBlkHeaderFound                      **
**                                        (const uint8 PotentialMarkerPage,  **
**                                         const uint32 DataNextPageCount)   **
**                                                                           **
** Service ID:                                                               **
**                                                                           **
** Sync/Async:  Synchronous                                                  **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in): (uint8) PotentialMarkerPage - Potential Marker Page was  **
**                                                found or not.              **
**                  (uint32) DataNextPageCount - Count of Data block's       **
**                                               continuation page           **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  void                                                   **
**                                                                           **
** Description:This function does the cache table update and other necessary **
**              handling when the block's header is found during cache build **
******************************************************************************/
/* [cover parentID={6638B201-B37C-4967-B11C-91C2490F46B7}]
Fee_lHandleBlkHeaderFound
[/cover] */
LOCAL_INLINE void Fee_lHandleBlkHeaderFound(const uint8 PotentialMarkerPage,
    const uint32 DataNextPageCount)
{
  Fee_StateDataType          *StateDataPtr;
  const uint8                      *ReadWriteBufferPtr;
  uint16                      PageCount;
  
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  ReadWriteBufferPtr = StateDataPtr->FeeReadWriteBuffer;

  UNUSED_PARAMETER (PotentialMarkerPage);
  /* extract page count */
  PageCount = (uint16)((uint16)ReadWriteBufferPtr[7] << FEE_EIGHT) |
              ReadWriteBufferPtr[6];
  PageCount = (PageCount & (uint16)FEE_PAGE_COUNT_MASK) - FEE_ONE;

  if(StateDataPtr->FeeLastWrittenBlockDirty == FEE_LWB_CHECK_FOR_DIRTY)
  {
    if(PageCount == DataNextPageCount)
    {
      StateDataPtr->FeeLastWrittenBlockDirty = FEE_LWB_DIRTY;
    }
    else
    {
      StateDataPtr->FeeLastWrittenBlockDirty = FEE_LWB_NOT_DIRTY;
    }
  }
  /* AI00194692 - Do not update cache table as block is inconsistent */
  /*            - Continue the search for consistent copy of the block */

}

#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lCheckPrevPage(const uint32 EndAddr)        **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :EndAddr - BaseAddr of the sector                      **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : This utility function will check if the CurrSectSrcAddr      **
**  has reached the base address. If not, it decrements the CurrSectSrcAddr   **
**  by page size                                                              **
*******************************************************************************/
/* [cover parentID={0C4F21DC-2ECA-437b-AAB5-3D5340FC7FA2}]
Fee_lCheckPrevPage
[/cover] */
LOCAL_INLINE void Fee_lCheckPrevPage(const uint32 EndAddr)
{
  Fee_StateDataType       *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* Check if all pages have been read */
  if( StateDataPtr->FeeCurrSectSrcAddr != EndAddr )
  {
    /* Move to the next page */
    StateDataPtr->FeeCurrSectSrcAddr -= FEE_DFLASH_PAGE_SIZE;
  }
  else
  {
    /* Goto the next state */
    StateDataPtr->FeeCacheState = FEE_CACHE_UPDATE_COMPLETE;
  }
}

/*******************************************************************************
** Syntax : static uint32 Fee_lGetBlkCycleCount(const uint16 Index)           **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  Index      Cache Index for targeted logical block       **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Return value    :  uint32     Fetches the cycle count for the logical block**
**                                                                            **
** Description : This utility function fetches the cycle count for a          **
**               logical block from DFLASH.                                   **
*******************************************************************************/
/*[cover parentID={DD7D4A15-7749-4849-8E49-A96FE968B15D}][/cover]*/
static uint32 Fee_lGetBlkCycleCount(const uint16 Index)
{
  Fee_StateDataType  *StateDataPtr;
  const uint8        *TempArrayPtr;
  uint32              Address;
  uint32              BlockCycleCount;
  uint32              TempVal;
  Std_ReturnType      RetVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  BlockCycleCount = FEE_32_BIT_ALL_ONES;

  /* Initialize the temp array */
  StateDataPtr->FeeTempArray[0U] = (uint32)FEE_RESET;
  StateDataPtr->FeeTempArray[1U] = (uint32)FEE_RESET;

  /* Read block cycle count */
  Address = (StateDataPtr->FeeBlockInfo[Index]).Address;
  if( Address != FEE_RESET )
  {
    /* Read the header (2 Words) */
    /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with FLS.
    FEE is passing parameters to FLS APIs, for example, Fls_17_Dmu_ReadWordsSync
    Changing this will break the interfacing and will cause major functional
    issues both on FLS and FEE side. */
    
    RetVal = Fls_17_Dmu_ReadWordsSync((Fls_17_Dmu_AddressType)Address,\
                                      (uint32 *)(StateDataPtr->FeeTempArray),\
                                      (Fls_17_Dmu_LengthType)\
                                      (FEE_DFLASH_PAGE_SIZE / 
                                      FEE_DFLASH_WORD_SIZE));
    if( RetVal != E_OK )
    {
      
      /*Check if the previous copy of block is available.if yes then read the 
      BCC from this block*/
      Address = (StateDataPtr->FeeBlockInfo[Index]).PrevCopyAddress;
      if( Address != FEE_RESET )
      {
         /* Read the header (2 Words) */
        RetVal = Fls_17_Dmu_ReadWordsSync(Address,(StateDataPtr->FeeTempArray),
        (FEE_DFLASH_PAGE_SIZE / FEE_DFLASH_WORD_SIZE));
        
        if(RetVal == E_OK) 
        {
          /* Block Cycle count is 24 bits starting from 3rd byte of FeeTempArray
          Read the word from second byte and extract the upper 24bits */
          TempArrayPtr = (uint8 *)(StateDataPtr->FeeTempArray);
          /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
          array indexing used for FEE application buffers.
          Pointers are accessing the correct memory range locations.
          The access range is within the boundaries of the buffer. */
          TempArrayPtr += FEE_BLOCK_CYL_CNT_POS;
          /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array
           buffer*/
          TempVal = *((const uint32 *)TempArrayPtr);
          BlockCycleCount = (TempVal >> FEE_EIGHT); 
          /*Add the 1 to BCC of previous copy of block. This will give the
          BCC of current copy of block*/
          BlockCycleCount = BlockCycleCount + FEE_ONE;
        }
        else
        {
      BlockCycleCount = FEE_32_BIT_ALL_ONES;
        }
      }
      else
      {
        BlockCycleCount = FEE_32_BIT_ALL_ONES;  
      }
    }
    else
    {
      /* Block Cycle count is 24 bits starting from 3rd byte of FeeTempArray.
         Read the word from second byte and extract the upper 24bits */
      TempArrayPtr = (uint8 *)(StateDataPtr->FeeTempArray);
      /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
      array indexing used for FEE application buffers.
      Pointers are accessing the correct memory range locations.
      The access range is within the boundaries of the buffer. */
      TempArrayPtr += FEE_BLOCK_CYL_CNT_POS;
      /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
      TempVal = *((const uint32 *)TempArrayPtr);
      BlockCycleCount = (TempVal >> FEE_EIGHT);
    }
  }
   /* [cover parentID={34F26C48-1097-4c68-A607-71E65034E132}]
Return
[/cover] */
  return(BlockCycleCount);

}/*End of Fee_lGetBlkCycleCount */

/*******************************************************************************
** Syntax : LOCAL_INLINE uint8 Fee_lCheckPrevWordline(                        **
**                                 Fee_SectorInfoType *const SectorInfoPtr,   **
**                                 const uint32 EndAddr                       **
**                                      )                                     **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :SectorInfoPtr: Pointer to Sector Info                 **
**                     :EndAddr: Sector base addr                             **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  uint8                                                   **
**                  FEE_SP_INIT: Sector end is not reached                    **
**                  FEE_SP_DONE: Sector end reached                           **
** Description : This utility function will check if the CurrSectSrcAddr      **
**  has reached the end address. If not, it decrements the CurrSectSrcAddr    **
**  by wordline size. If the end addr is reached, this function computes      **
**  the first free WL address and the sector used status.                     **
*******************************************************************************/
/* [cover parentID={C29C319E-7350-4cc0-9D7A-DD9D9E708951}]
Fee_lCheckPrevWordline
[/cover] */
LOCAL_INLINE uint8 Fee_lCheckPrevWordline(Fee_SectorInfoType *const
    SectorInfoPtr, const uint32 EndAddr)
{
  Fee_StateDataType   *StateDataPtr;
  uint32               UnerasableWlAddr1;
  uint32               UnerasableWlAddr2;
  uint32               NonZeroWlAddr[2];
  uint32               StatePageAddr;
  uint32               NonZeroWlCount;
  uint8                UnerasableWlCount;
  uint8                SectorState;
  uint8                RetVal;

  RetVal = FEE_SP_INIT;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  UnerasableWlAddr1 = SectorInfoPtr->UnerasableWLAddr[0];
  UnerasableWlAddr2 = SectorInfoPtr->UnerasableWLAddr[1];
  UnerasableWlCount = SectorInfoPtr->UnerasableWLCount;
  NonZeroWlAddr[0] = SectorInfoPtr->NonZeroWLAddr[0];
  NonZeroWlAddr[1] = SectorInfoPtr->NonZeroWLAddr[1];
  NonZeroWlCount = SectorInfoPtr->NonZeroWLCount;
  StatePageAddr = SectorInfoPtr->StatePageAddr;
  SectorState = SectorInfoPtr->State;

  /* Check if all pages have been read */
  if ( StateDataPtr->FeeCurrSectSrcAddr == EndAddr )
  {
    /* EndAddr reached - State page search complete */
    RetVal = FEE_SP_DONE;

    /************ Compile NextFreeWL Address and Sector used state **********/
    if (NonZeroWlCount == FEE_RESET)
    {
      /* The sector is empty -
         NextFreeWlAddr = BaseAddr, Sector status = Unused (default value) */
      SectorInfoPtr->NextFreeWLAddr = EndAddr;
    }
    else
    {
      /* Updating NextFreeWLAddr of the sector */
      if ( ((NonZeroWlAddr[0] == UnerasableWlAddr1) &&
            (UnerasableWlCount != FEE_RESET)) ||
           ((NonZeroWlAddr[0] == UnerasableWlAddr2) &&
            (UnerasableWlCount != FEE_RESET)))
      {
        SectorInfoPtr->NextFreeWLAddr = Fee_lGetNextWLAddr(NonZeroWlAddr[1]);
    /* [cover parentID={0BC3D5AC-2ED3-4db9-9ABB-8385B24E8533}]
Check for unerasable wordlines
[/cover] */
        if((SectorInfoPtr->NextFreeWLAddr == UnerasableWlAddr1) ||
            (SectorInfoPtr->NextFreeWLAddr == UnerasableWlAddr2))
        {
          SectorInfoPtr->NextFreeWLAddr =
            Fee_lGetNextWLAddr(SectorInfoPtr->NextFreeWLAddr);
        }
      }
      else
      {
        SectorInfoPtr->NextFreeWLAddr = Fee_lGetNextWLAddr(NonZeroWlAddr[0]);
      }

      /* Refer UTP AI00238899 - Don't verify if sector end is reached */
      if((SectorInfoPtr->NextFreeWLAddr) < (EndAddr + FEE_DFLASH_SECTOR_SIZE))
      {
        /* Refer UTP AI00194703 - Identify/confirm next empty word line */
        Fee_lComputeNextWLAddr(SectorInfoPtr);
      }

      /* Determine Sector Used state */
      if (SectorState == FEE_ERASED)
      {
        if ( (NonZeroWlAddr[0] == StatePageAddr) ||
             ((NonZeroWlAddr[1] == StatePageAddr) &&
              (NonZeroWlAddr[0] == UnerasableWlAddr1)
             )
           )
        {
          /* Sector is unused (Default value) */
        }
        else
        {
          SectorInfoPtr->Status.Used = FEE_SET ;
        } /* if ( (NonZeroWlAddr[0] == StatePageAddr) || .... */
      } /* if (SectorState == FEE_ERASED) */
      else
      {
        SectorInfoPtr->Status.Used = FEE_SET ;
      }
    } /* if (NonZeroWlCount == FEE_RESET) */
  }
  else
  {
    /* Move to the previous wordline */
    StateDataPtr->FeeCurrSectSrcAddr -= FEE_DFLASH_WORDLINE_SIZE;
  }

  return(RetVal);

}
#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** Syntax : LOCAL_INLINE uint8 Fee_lEvaluateStatePageMarker(void)             **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  FEE_SP_CLEAN: if the State Page Marker is Valid         **
**                    FEE_SP_DIRTY: if the State Page Marker is Non Zero      **
**                    FEE_SP_INVALID: if the State Page Marker is Zero        **
**                                                                            **
** Description : This utility function will evaluate the state page Marker    **
**  content and returns the status                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Fee_lEvaluateStatePageMarker(void)
{
  Fee_StateDataType *StateDataPtr;
  uint8             *BufferPtr;
  uint32             Marker[2];
  Std_ReturnType     FlsRetVal;
  uint8              ReturnVal;

  ReturnVal = FEE_SP_CLEAN;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* Read the marker (last 8 bytes) of the current page */
  /* Offset will be 120 */
  
  BufferPtr = &(StateDataPtr->FeeReadWriteBuffer[FEE_SP_MARKERFIELD_START]);
  
  /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with FLS.FEE
  is passing parameters to FLS APIs, for example, Fls_17_Dmu_ReadWordsSync.
  Changing this will break the interfacing and will cause major functional 
  ssues both on FLS and FEE side.*/
  
  FlsRetVal = Fls_17_Dmu_ReadWordsSync(\
                (Fls_17_Dmu_AddressType)(StateDataPtr->FeeCurrSectSrcAddr + \
                                         FEE_SP_MARKERFIELD_START),\
                (uint32 *)(BufferPtr),\
                (Fls_17_Dmu_LengthType)(FEE_STATEPAGE_MARKER_SIZE /
                 FEE_DFLASH_WORD_SIZE));

  if(FlsRetVal == E_NOT_OK)
  {
    ReturnVal = FEE_SP_DIRTY;
  }
  else
  {
    /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
    Marker[0] = *((const uint32*)(BufferPtr));
    /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
    Marker[1] = *((const uint32*)&(BufferPtr[FEE_DFLASH_WORD_SIZE]));
    if((Marker[0] == FEE_RESET) && (Marker[1] == FEE_RESET))
    {
      ReturnVal = FEE_SP_INVALID;
    }
    else
    {
      /* if ReturnVal is FEE_SP_CLEAN */
      if ((Marker[0] != FEE_SP_MARKER_WORD_1) ||
          (Marker[1] != FEE_SP_MARKER_WORD_2))
      {
        ReturnVal = FEE_SP_DIRTY;
      }
    }
  }
  return(ReturnVal);
}

/******************************************************************************
** Syntax : LOCAL_INLINE uint8 Fee_lEvaluateStatePageFormat(void)            **
**                                                                           **
** Service ID: NA                                                            **
**                                                                           **
** Sync/Async:  Synchronous                                                  **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in-out) :None                                                 **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    : uint8                                                   **
**                    FEE_SP_CLEAN: if the state page is of New Format       **
**                    FEE_SP_INVALID: if the state page is invalid           **
**                                                                           **
** Description : This utility function will evaluate the state page content  **
**  with respect to New Format and returns the status                        **
******************************************************************************/
LOCAL_INLINE uint8 Fee_lEvaluateStatePageFormat(void)
{
  const Fee_StateDataType *StateDataPtr;
  const uint32             *BufferPtr;
  const uint32             *BufferPtr2;
  uint32             Data;
  uint32             Index;
  uint32             Length;
  uint8              ReturnVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  ReturnVal = FEE_SP_CLEAN;
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
  BufferPtr = (const uint32*)(StateDataPtr->FeeReadWriteBuffer);
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
  BufferPtr2 = (const uint32*)(&(StateDataPtr->FeeReadWriteBuffer[ \
                              FEE_STATE_FIRSTFIVE_COPY_OFFSET]));

  /* check that the first word content is redundant below except page id */
  if((*BufferPtr & FEE_STATE_WLCOUNT_MASK) != \
      (*BufferPtr2 & FEE_STATE_WLCOUNT_MASK))
  {
    ReturnVal = FEE_SP_INVALID;
  }
  else
  {
    /* Check the state page header pages(starting from Byte-4) with its
     * duplicate copy.when Both copy matches then header pages are
     *  considered as valid */
    for(Index = FEE_RESET; Index < (FEE_STATE_PAGE_HDR_PAGES - FEE_ONE); Index++)
    {

      BufferPtr++;
      BufferPtr2++;

      if(*BufferPtr != *BufferPtr2)
      {
        ReturnVal = FEE_SP_INVALID;
        break; /* break */
      }

    }
    /* Check for second half of state page */
    if(ReturnVal != FEE_SP_INVALID)
    {

      /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
      BufferPtr = (const uint32*)(&(StateDataPtr->FeeReadWriteBuffer[ \
                                 FEE_STATE_ALLONES_OFFSET]));
      /* get the length excluding CRC */


      Length = sizeof(Fee_StateHalf) / sizeof(Fee_StateHalf[0]);

      for(Index = FEE_RESET; Index < Length; Index++)
      {
        if(*BufferPtr != Fee_StateHalf[Index])
        {
          ReturnVal = FEE_SP_INVALID;
          break; /* break */
        }

        BufferPtr++;
      }
    }
    /* verify the CRC */
    if(ReturnVal != FEE_SP_INVALID)
    {
      /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
      BufferPtr = (const uint32*)(&(StateDataPtr->FeeReadWriteBuffer[ \
                                    FEE_STATE_CRC_OFFSET]));
      /* Length will give the number of pages to Generate CRC */
      Length = FEE_STATE_CRC_OFFSET / FEE_DFLASH_WORD_SIZE;
      
      /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
      Data = Fee_lEvaluateStatePageCrc(\
                      (const uint32*)(StateDataPtr->FeeReadWriteBuffer), \
                      Length);
      if( Data != *BufferPtr)
      {
        ReturnVal = FEE_SP_INVALID;
      }

    }
  }
  return(ReturnVal);
}

/*******************************************************************************
** Syntax : LOCAL_INLINE uint32 Fee_lEvaluateStatePageCrc                     **
**            (const uint32 * const DataPtr, const uint32 Length)             **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  DataPtr : Pointer to Data                               **
**                    Length : Data Length in Word                            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  32 bit CRC value                                        **
**                                                                            **
** Description : This utility function will evaluate 32 bit CRC value over    **
**               data pointed by DataPtr for the requested Length             **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Fee_lEvaluateStatePageCrc(const uint32 * const DataPtr,
    const uint32 Length)
{
  uint32             Index;
  uint32             Crc32;

  Crc32 = FEE_CRC_START_VAL;
  for(Index = FEE_RESET; Index < Length; Index++)
  {
    /*MISRA2012_RULE_4_6_JUSTIFICATION: Basic numerical type - int/unsigned int
     is used while invoking compiler intrinsic functions. These compiler
     intrinsic functions are implemented specific to tricore.Hence to align with
      compiler declaration use of unsigned int is mandatory. */
    Crc32 = CRC32(Crc32, DataPtr[Index]);

  }
  return(Crc32);
}

/******************************************************************************
** Syntax : LOCAL_INLINE uint8 Fee_lEvaluateStatePage(void)                  **
**                                                                           **
** Service ID: NA                                                            **
**                                                                           **
** Sync/Async:  Synchronous                                                  **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in-out) :None                                                 **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    : uint8                                                   **
**                    FEE_SP_CLEAN: if the state page is valid               **
**                    FEE_SP_DIRTY: if the state page is dirty               **
**                    FEE_SP_INVALID: if the state page is invalid           **
**                                                                           **
** Description : This utility function will evaluate the state page content  **
**  and returns the state page status                                        **
******************************************************************************/
LOCAL_INLINE uint8 Fee_lEvaluateStatePage(void)
{
  Fee_StateDataType *StateDataPtr;
  const uint8             *BufferPtr;
  Std_ReturnType     FlsRetVal;
  uint8              State;
  uint8              ReturnVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* Read the state page content (first 120 bytes) of the current page */
  FlsRetVal = Fls_17_Dmu_ReadWordsSync(
                (Fls_17_Dmu_AddressType)StateDataPtr->FeeCurrSectSrcAddr,
                /*MISRA2012_RULE_11_3_JUSTIFICATION:*/
                (uint32 *)StateDataPtr->FeeReadWriteBuffer,
                (Fls_17_Dmu_LengthType)
                (FEE_STATEPAGE_DATA_SIZE / FEE_DFLASH_WORD_SIZE));
  BufferPtr = StateDataPtr->FeeReadWriteBuffer;
  State = BufferPtr[FEE_ONE];

  if( (FlsRetVal == E_NOT_OK) ||
      (!((State == FEE_VALID) || (State == FEE_ERASED))) )
  {
    ReturnVal = FEE_SP_INVALID;
  }
  else
  {
    ReturnVal = Fee_lEvaluateStatePageFormat();

  }

  if(FEE_SP_INVALID != ReturnVal)
  {
    /* Check the marker field */
    ReturnVal = Fee_lEvaluateStatePageMarker();
  }

  return(ReturnVal);
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lSetInitGc(const uint8 DFlashStatus)        **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :DFlashStatus: State of DFlash sectors                     **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This utility function sets the InitGc state based on         **
**  the DFlashStatus                                                          **
*******************************************************************************/
/* [cover parentID= {73069EFB-0578-40c2-8DCF-BAD3CAFF16D5}][/cover]*/
LOCAL_INLINE void Fee_lSetInitGc(const uint8 DFlashStatus)
{

  Fee_StateDataType  *StateDataPtr;
  Fee_SectorInfoType *SectorInfoPtr0;
  Fee_SectorInfoType *SectorInfoPtr1;
  uint32              S0StateCnt;
  uint32              S1StateCnt;
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  uint16              S0HardeningCnt;
  uint16              S1HardeningCnt;
#endif
  uint8               S0Used;
  uint8               S1Used;
  uint8               S0Dirty;
  uint8               S1Dirty;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  SectorInfoPtr0 = &StateDataPtr->FeeSectorInfo[0];
  SectorInfoPtr1 = &StateDataPtr->FeeSectorInfo[1];

  StateDataPtr->FeeInitGCState = FEE_INITGC_NORMAL;

  S0StateCnt = SectorInfoPtr0->StateCount;
  S1StateCnt = SectorInfoPtr1->StateCount;
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  S0HardeningCnt = SectorInfoPtr0->QsHardeningOffset;
  S1HardeningCnt = SectorInfoPtr1->QsHardeningOffset;
#endif
  S0Used = SectorInfoPtr0->Status.Used;
  S1Used = SectorInfoPtr1->Status.Used;
  S0Dirty = SectorInfoPtr0->Status.Dirty;
  S1Dirty = SectorInfoPtr1->Status.Dirty;

  /* Update the state count */
  if (S0StateCnt > S1StateCnt)
  {
    StateDataPtr->FeeStateCount = S0StateCnt;
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
    StateDataPtr->FeeQsHardeningOffset = S0HardeningCnt;
#endif
  }
  else
  {
    StateDataPtr->FeeStateCount = S1StateCnt;
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
    StateDataPtr->FeeQsHardeningOffset = S1HardeningCnt;
#endif
  }

  switch (DFlashStatus)
  {
    /* Both the sectors empty */
    case FEE_S0_S1_EMPTY:
      {
        StateDataPtr->FeeInitGCState = FEE_INITGC_PREPARE_DFLASH;
        StateDataPtr->FeePrepDFLASHState = FEE_PREPDF_MARK_S0_ERASED_SP;
        StateDataPtr->FeeCurrSectSrcAddr =
          StateDataPtr->FeeSectorInfo[0].NextFreeWLAddr;
        S0Dirty = FEE_RESET;
        S1Dirty = FEE_RESET;
        break;
      }
    /* S0 is valid */
    case FEE_S0_VALID:
      {
        /* Check if copy was interrupted */
        if(S1Used == FEE_SET )
        {
          StateDataPtr->FeeGcResumeState = FEE_INITGC_DATA_COPY_S0_S1;
          S1Dirty = FEE_RESET;
        }
        else
        {
          StateDataPtr->FeeGcResumeState = FEE_INITGC_NORMAL_S0;
        }
        break;
      }
    /* S1 is valid */
    case FEE_S1_VALID:
      {
        /* Change the current sector to SECTOR1 */
        StateDataPtr->FeeStatusFlags.FeeCurrSector = FEE_SECTOR1;
        /* Check if copy was interrupted */
        if(S0Used == FEE_SET )
        {
          StateDataPtr->FeeGcResumeState = FEE_INITGC_DATA_COPY_S1_S0;
          S0Dirty = FEE_RESET;
        }
        else
        {
          StateDataPtr->FeeGcResumeState = FEE_INITGC_NORMAL_S1;
        }
        break;
      }
    /* Erase interrupted */
    case FEE_S0_S1_VALID:
      {
        if (S0StateCnt > S1StateCnt)
        {
          StateDataPtr->FeeGcResumeState = FEE_INITGC_ERASE_S1;
          S1Dirty = FEE_RESET;
        }
        else
        {
          /* Change the current sector to SECTOR1 */
          StateDataPtr->FeeStatusFlags.FeeCurrSector = FEE_SECTOR1;
          StateDataPtr->FeeGcResumeState = FEE_INITGC_ERASE_S0;
          S0Dirty = FEE_RESET;
        }
        break;
      }
    default:
      {
        S0Dirty = FEE_RESET;
        S1Dirty = FEE_RESET;
        StateDataPtr->FeeInitGCState = FEE_INITGC_HANDLE_INVALID;
        break;
      }
  }

  if ( (S0Dirty != FEE_RESET) || (S1Dirty != FEE_RESET) )
  {
    StateDataPtr->FeeInitGCState = FEE_INITGC_HANDLE_DIRTY;
    StateDataPtr->FeeRepairStep = FEE_PROGRAM_MARKER;
  }

  SectorInfoPtr0->Status.Dirty = S0Dirty;
  SectorInfoPtr1->Status.Dirty = S1Dirty;

}

/*******************************************************************************
** Syntax : LOCAL_INLINE uint8 Fee_lBuildDFlashStatus(void)                   **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  DFlash status                                           **
**                                                                            **
** Description : This utility function compiles the DFLASH status based on    **
**  sector0 and sector1 state contents                                        **
*******************************************************************************/
/*[cover parentID={361664FB-92BB-45d0-96FD-3DB7EB1BAAC5}][/cover]*/
LOCAL_INLINE uint8 Fee_lBuildDFlashStatus(void)
{
  const Fee_StateDataType *StateDataPtr;
  uint8              S0State;
  uint8              S1State;
  uint8              S0Used;
  uint8              S1Used;
  uint8              RetVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  S0State = StateDataPtr->FeeSectorInfo[0].State;
  S1State = StateDataPtr->FeeSectorInfo[1].State;
  S0Used = StateDataPtr->FeeSectorInfo[0].Status.Used;
  S1Used = StateDataPtr->FeeSectorInfo[1].Status.Used;

  if ( (S0State == FEE_VALID) && (S1State == FEE_ERASED) )
  {
    RetVal = FEE_S0_VALID;
  }
  else if ( (S0State == FEE_ERASED) && (S1State == FEE_VALID) )
  {
    RetVal = FEE_S1_VALID;
  }
  else if ( (S0State == FEE_VALID) && (S1State == FEE_VALID) )
  {
    /* This happens when Erase of S0 / S1 is interrupted just before the start
       of Erase */
    RetVal = FEE_S0_S1_VALID;
  }
  else if ( (S0State == FEE_VALID) && (S1State == FEE_STATELESS) )
  {
    /* This happens when Erase of S1 is interrupted. Handle it the same way as
       S0_S1_VALID so that S1 can be erased as part of INIT GC */
    RetVal = FEE_S0_S1_VALID;
  }
  else if ( (S0State == FEE_STATELESS) && (S1State == FEE_VALID) )
  {
    /* This happens when Erase of S0 is interrupted. Handle it the same way as
       S0_S1_VALID so that S0 can be erased as part of INIT GC */
    RetVal = FEE_S0_S1_VALID;
  }
  else if ( ((boolean)TRUE == Fee_lIsSectorEmpty(S0State, S0Used)) &&
            ((boolean)TRUE == Fee_lIsSectorEmpty(S1State, S1Used)) )
  {
    RetVal = FEE_S0_S1_EMPTY;
  }
  /* Any other combination leads to invalid state */
  else
  {
    RetVal = FEE_S0_S1_INVALID;
  }

  return(RetVal);

}

/*******************************************************************************
** Syntax : static void Fee_lUpdateNonZeroWLInfo(                             **
**                                   Fee_SectorInfoType *const SectorInfoPtr, **
**                                   const uint32        SrcAddr              **
**                                  )                                         **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :SectInfoPtr: Pointer to Sector Info                   **
**                     :SrcAddr: Current non zero page addr                   **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This utility function will update the NonZeroWLAddr and      **
**  NonZeroWLCount                                                            **
*******************************************************************************/
static void Fee_lUpdateNonZeroWLInfo(Fee_SectorInfoType *const SectorInfoPtr, \
                                     const uint32 SrcAddr)
{
  uint32 NonZeroWlCount;
  NonZeroWlCount = SectorInfoPtr->NonZeroWLCount;
  /* [cover parentID={23D31021-77A8-40d0-9BD2-D6F00E8008AC}]
      Fee_lUpdateNonZeroWLInfo
     [/cover] */
  /* Update the non-zero WL location if not updated */
  if (NonZeroWlCount <= FEE_ONE)
  {
    SectorInfoPtr->NonZeroWLAddr[NonZeroWlCount] = SrcAddr;
  }

  /* Increment non-zero WL count */
  SectorInfoPtr->NonZeroWLCount++;
}

/*******************************************************************************
** Syntax : LOCAL_INLINE uint8 Fee_lGetSectorInfo (                           **
**                                     const uint32 BankNumber,               **
**                                     const uint32 EndAddr                   **
**                                   )                                        **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :(uint32)BankNumber: Sector number                     **
**                      (uint32)EndAddr: Base of Sector                       **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  uint8                                                   **
**                  FEE_SP_INIT: Sector scanning for state page is on going.  **
**                  FEE_SP_DONE: Sector scanning is completed                 **
** Description : This utility function will search through the DFLASH from    **
**  the bottom till base of the sector and get sector state information       **
*******************************************************************************/
/* [cover parentID={130CBADC-2E4F-4603-8D5C-F91DA268D7C3},
{804DB87B-2AE9-421f-97F0-0D69563B9824},
{FC609CF8-1846-43bc-8922-86A42976F7A3}]
Fee_lGetSectorInfo
[/cover] */
LOCAL_INLINE uint8 Fee_lGetSectorInfo(const uint32 BankNumber,
                                      const uint32 EndAddr)
{
  Fee_StateDataType   *StateDataPtr;
  Fee_SectorInfoType  *SectorInfoPtr;
  const uint32              *BuffPtr;
  uint32               SrcAddr;
  uint32               StateCount1;
  uint32               StateCount2;
  Std_ReturnType       RetVal;
  uint8                ReturnVal;
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY) 
  uint32               QsOffset;
#endif
  

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  SectorInfoPtr = &StateDataPtr->FeeSectorInfo[BankNumber];

  SrcAddr = StateDataPtr->FeeCurrSectSrcAddr;

  /* Read the header of status page */
  RetVal = Fls_17_Dmu_ReadWordsSync((Fls_17_Dmu_AddressType)SrcAddr,
                                    /* MISRA2012_RULE_11_3_JUSTIFICATION:*/
                                    (uint32 *)StateDataPtr->FeeReadWriteBuffer,
                                    (Fls_17_Dmu_LengthType)
                                    ((FEE_DFLASH_PAGE_SIZE * FEE_TWO)
                                     / FEE_DFLASH_WORD_SIZE));

  /* Check if DBER is found in the header */
  /* DBER is NOT found */
  if(RetVal == E_OK)
  {
    /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
    BuffPtr = (uint32 *)StateDataPtr->FeeReadWriteBuffer;
    /* Check if the header is zero */
   
    if ((*BuffPtr == FEE_RESET) && ((BuffPtr[FEE_ONE]) == FEE_RESET) &&
       ((BuffPtr[FEE_TWO]) == FEE_RESET) && ((BuffPtr[FEE_THREE]) == FEE_RESET))
    {
      /* Zero page */
      /* Move to previous wordline */
    }
    /* Non-zero page */
    else
    {
      Fee_lUpdateNonZeroWLInfo(SectorInfoPtr, SrcAddr);
      /* Check if it is state page */
      if ( StateDataPtr->FeeReadWriteBuffer[FEE_STATE_PAGE_ID_POS] ==
           FEE_STATE_FIRST_PAGE_ID )
      {
        RetVal = Fee_lEvaluateStatePage();
        if ( (RetVal == FEE_SP_CLEAN) || (RetVal == FEE_SP_DIRTY))
        {
          /* State Count is at byte 4 of the buffer - move Ptr by one word */
      
          StateCount2 = BuffPtr[FEE_ONE];
          StateCount1 = SectorInfoPtr->StateCount;
          if (StateCount2 > StateCount1)
          {
            SectorInfoPtr->Status.Dirty = RetVal;
            SectorInfoPtr->State =
              StateDataPtr->FeeReadWriteBuffer[FEE_STATE_PAGE_STATE_POS];
            SectorInfoPtr->UnerasableWLCount =
              (StateDataPtr->FeeReadWriteBuffer[FEE_STATE_PAGE_UERWL_POS] >>
               FEE_FOUR) & 0x0FU;
            SectorInfoPtr->StateCount = StateCount2;
            /* Unerasable WL Addr is at byte 12 of the buffer -
               move Ptr by three words */
           
            SectorInfoPtr->UnerasableWLAddr[FEE_ZERO] = BuffPtr[FEE_THREE];
            SectorInfoPtr->UnerasableWLAddr[FEE_ONE]  = BuffPtr[FEE_FIVE];
            SectorInfoPtr->StatePageAddr = SrcAddr;
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
/* QS Data offset stored in state page is extracted and stored, so that  */
            QsOffset = BuffPtr[0];
            QsOffset = (QsOffset & FEE_QS_DATA_OFFSET_MASK);
            QsOffset = QsOffset >> FEE_QS_DATA_OFFSET_START;
            SectorInfoPtr->QsHardeningOffset= (uint16) QsOffset;
#endif            
          }/* if(StateCount2 > StateCount1) */
        }/* if ((RetVal == FEE_SP_CLEAN) || (RetVal == FEE_SP_DIRTY)) */
      }/* if(StateDataPtr->FeeReadWriteBuffer[0] == FEE_STATE_FIRST_PAGE_ID)*/
    }/* if( (*BuffPtr == FEE_ZERO) && (*(BuffPtr + 1U) == FEE_ZERO) ) */
  }
  else
  {
    Fee_lUpdateNonZeroWLInfo(SectorInfoPtr, SrcAddr);
  }

  ReturnVal = Fee_lCheckPrevWordline(SectorInfoPtr, EndAddr);

  return(ReturnVal);

}
#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

/*******************************************************************************
** Syntax : static boolean Fee_lIsUnerasableAddr(const uint32 Addr)           **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :Addr                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  TRUE: if Addr is part of unerasable WL                  **
**                    FALSE: if Addr is not part of unerasable WL             **
**                                                                            **
** Description : This utility function checks if the Addr is part of          **
** unerasable Wordline                                                        **
*******************************************************************************/
/* [cover parentID={38625665-C299-405c-8245-9981344A0772}]
Fee_lIsUnerasableAddr
[/cover] */
static boolean Fee_lIsUnerasableAddr(const uint32 Addr)
{
  const Fee_StateDataType *StateDataPtr;
  boolean            RetVal;
  uint8              UnErCount;
  uint32             NewAddr;
  /* [cover parentID={38625665-C299-405c-8245-9981344A0772}] */
  uint8              BankNumber;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* Get the FEE sector index */
  if(Addr >= FEE_DFLASH_BANK1_BASE)
  {
    BankNumber = FEE_SECTOR1;
  }
  else
  {
    BankNumber = FEE_SECTOR0;
  }

  UnErCount = FEE_RESET;

  RetVal = (boolean)FALSE;

  /* Get word line beginning address of the address to be checked */

  NewAddr = (uint32)(Fee_lGetWLBeginning(Addr));

  /* Loop through to check whether Address is uneraseble */
  while((UnErCount != StateDataPtr->FeeSectorInfo[BankNumber].UnerasableWLCount)
        && (RetVal == FALSE))
  {
    if(NewAddr ==
        StateDataPtr->FeeSectorInfo[BankNumber].UnerasableWLAddr[UnErCount])
    {
      RetVal = (boolean)TRUE;
    }
    else
    {
      UnErCount++;
    }
  }
  return(RetVal);
}
#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** Syntax : static void Fee_lPrepareStatePageBuffer(const uint8 Bank,         **
**                                                  const uint8 SectorState)  **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  Bank: Sector Number                                     **
**                    SectorState: Erased / Valid                             **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine will update the write buffer for state page     **
** programming of a sector                                                    **
*******************************************************************************/
/* [cover parentID={9E1839E0-2F3B-4038-B42B-DEF7C312D59B}]
Fee_lPrepareStatePageBuffer
[/cover] */
static void Fee_lPrepareStatePageBuffer(const uint8 Bank,
                                        const uint8 SectorState)
{
  uint32              StateCnt;
  uint32              WordlineAddr;
  uint32              WordlineAddr2;
  uint32              Index;
  uint32              Length;
  Fee_StateDataType  *StateDataPtr;
  uint8              *ArrPtr;
  uint8               WordlineCnt;
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  uint8              QsHardenOffsetLSB;
  uint8              QsHardenOffsetMSB;
  uint16             QsHardenOffset;
#endif

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  Fee_lClearFeeGcReadWriteBuffer();
  ArrPtr = StateDataPtr->FeeGcReadWriteBuffer;

  /* Get the State count */
  StateCnt = StateDataPtr->FeeStateCount;
  StateCnt = StateCnt + FEE_ONE;

  /* Get the UnerasableWL count */
  WordlineCnt = StateDataPtr->FeeSectorInfo[Bank].UnerasableWLCount;
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  QsHardenOffset = (uint16)(StateDataPtr->FeeQsHardeningOffset);
  QsHardenOffsetLSB = (uint8)QsHardenOffset;
  QsHardenOffsetMSB = (uint8)(QsHardenOffset >> 8);
#endif
  /* Get the UnerasableWL Addr */
  WordlineAddr = StateDataPtr->FeeSectorInfo[Bank].UnerasableWLAddr[0];
  WordlineAddr2 = StateDataPtr->FeeSectorInfo[Bank].UnerasableWLAddr[1];

  /* Update the page id of the 1st page of state page */

  *ArrPtr = FEE_STATE_FIRST_PAGE_ID;
   ArrPtr[FEE_STATE_PAGE_STATE_POS] = SectorState;
   ArrPtr[FEE_STATE_PAGE_STATE_POS + FEE_STATE_FIRSTFIVE_COPY_OFFSET] = 
   SectorState;
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  
  ArrPtr[FEE_STATE_PAGE_QS_OFFSET_LSB] = QsHardenOffsetLSB;
  ArrPtr[FEE_STATE_PAGE_QS_OFFSET_MSB] =
    (((WordlineCnt << 4) & 0xF0U) + ((QsHardenOffsetMSB) & 0x0FU));
  ArrPtr[FEE_STATE_PAGE_QS_OFFSET_LSB + FEE_STATE_FIRSTFIVE_COPY_OFFSET] =
  QsHardenOffsetLSB;
  ArrPtr[FEE_STATE_PAGE_QS_OFFSET_MSB + FEE_STATE_FIRSTFIVE_COPY_OFFSET]=
    (((WordlineCnt << 4) & 0xF0U) + ((QsHardenOffsetMSB) & 0x0FU));
#else
  
  ArrPtr[FEE_STATE_PAGE_UERWL_POS]= ((WordlineCnt << 4) & 0xF0U );
 
  ArrPtr[FEE_STATE_PAGE_UERWL_POS + FEE_STATE_FIRSTFIVE_COPY_OFFSET] =
    ((WordlineCnt << 4) & 0xF0U);
#endif
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
  /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than array 
  indexing used for FEE application buffers.Pointers are accessing the correct
   memory range locations.The access range is within the boundaries of the 
   buffer. */
  *((uint32 *)(ArrPtr + FEE_STATE_PAGE_STATE_CNT_POS)) = StateCnt;
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
  /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than array 
  indexing used for FEE application buffers.Pointers are accessing the correct
  memory range locations.The access range is within the boundaries of the
  buffer. */
  *((uint32 *)(ArrPtr + FEE_STATE_PAGE_STATE_CNT_POS + FEE_STATE_FIRSTFIVE_COPY_OFFSET)) \
    = StateCnt;


  if(WordlineCnt > FEE_ZERO)
  {

    /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
    /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
          array indexing used for FEE application buffers.
          Pointers are accessing the correct memory range locations.
          The access range is within the boundaries of the buffer. */
    *((uint32 *)(ArrPtr + FEE_STATE_PAGE_UERWL1_ADDRS_POS)) = WordlineAddr;
    /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
    /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
          array indexing used for FEE application buffers.
          Pointers are accessing the correct memory range locations.
          The access range is within the boundaries of the buffer. */
    *((uint32 *)(ArrPtr + FEE_STATE_PAGE_UERWL2_ADDRS_POS)) = WordlineAddr2;
    /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
    /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
          array indexing used for FEE application buffers.
          Pointers are accessing the correct memory range locations.
          The access range is within the boundaries of the buffer. */
    *((uint32 *)(ArrPtr + FEE_STATE_PAGE_UERWL1_ADDRS_POS + \
                 /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
                 array indexing used for FEE application buffers.
                 Pointers are accessing the correct memory range locations.
                  The access range is within the boundaries of the buffer. */
                 FEE_STATE_FIRSTFIVE_COPY_OFFSET)) = WordlineAddr;
    /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
    /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
          array indexing used for FEE application buffers.
          Pointers are accessing the correct memory range locations.
          The access range is within the boundaries of the buffer. */
    *((uint32 *)(ArrPtr + FEE_STATE_PAGE_UERWL2_ADDRS_POS + \
                 /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
                       array indexing used for FEE application buffers.
                       Pointers are accessing the correct memory range locations.
                       The access range is within the boundaries of the buffer. */
                 FEE_STATE_FIRSTFIVE_COPY_OFFSET)) = WordlineAddr2;
  }
  /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
        array indexing used for FEE application buffers.
        Pointers are accessing the correct memory range locations.
        The access range is within the boundaries of the buffer. */
  ArrPtr = StateDataPtr->FeeGcReadWriteBuffer + FEE_DFLASH_PAGE_SIZE;

  for(Index = FEE_ONE; Index < (FEE_STATE_PAGE_HDR_PAGES); Index++)
  {
    *ArrPtr = FEE_STATE_NEXT_PAGE_ID;
    /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
          array indexing used for FEE application buffers.
          Pointers are accessing the correct memory range locations.
          The access range is within the boundaries of the buffer. */
    ArrPtr += FEE_DFLASH_PAGE_SIZE;
  }

  ArrPtr = &(StateDataPtr->FeeGcReadWriteBuffer[FEE_STATE_ALLONES_OFFSET]);
  /* get the length excluding crc from All 1's field */

  Length = sizeof(Fee_StateHalf) / sizeof(Fee_StateHalf[0]);

  /* Write second half state page */
  for(Index = FEE_RESET; Index < Length; Index++)
  {
    /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
    *(uint32 *)(ArrPtr) = Fee_StateHalf[Index];
    /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
    array indexing used for FEE application buffers.
     Pointers are accessing the correct memory range locations.
     The access range is within the boundaries of the buffer. */
    ArrPtr += FEE_DFLASH_WORD_SIZE;
  }

  /* prepare the CRC field */

  ArrPtr = &(StateDataPtr->FeeGcReadWriteBuffer[FEE_STATE_CRC_OFFSET]);
  /* Length will give the number of pages to Generate CRC */
  Length = FEE_STATE_CRC_OFFSET / FEE_DFLASH_WORD_SIZE;
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
  *(uint32 *)(ArrPtr) =
    Fee_lEvaluateStatePageCrc(
      /*MISRA2012_RULE_11_3_JUSTIFICATION:*/
      (uint32 *)StateDataPtr->FeeGcReadWriteBuffer, Length);

  StateDataPtr->FeeStateCount = StateCnt;

}/* End of Fee_lPrepareStatePageBuffer */
/*******************************************************************************
** Syntax : static void Fee_lPrepareMarkerBuffer(void)                        **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This utility function prepares the Write buffer array for    **
**  marker programming of the state page                                      **
*******************************************************************************/
/* [cover parentID={46730273-C0EE-4a50-8C56-4F2718C6952A}]
Fee_lPrepareMarkerBuffer
[/cover] */
static void Fee_lPrepareMarkerBuffer(void)
{
  Fee_StateDataType  *StateDataPtr;
  uint8              *BufferPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  
  BufferPtr = &(StateDataPtr->FeeGcReadWriteBuffer[FEE_STATEPAGE_DATA_SIZE]);
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
  *((uint32*)(BufferPtr)) = FEE_SP_MARKER_WORD_1;
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
  *((uint32*)(&(BufferPtr[4U]))) = FEE_SP_MARKER_WORD_2;
}/* End of Fee_lPrepareMarkerBuffer */

/*******************************************************************************
** Syntax : static void Fee_lClearMarkerBuffer(void)                          **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This utility function clears the marker field of             **
**  write buffer for comparison                                               **
*******************************************************************************/
static void Fee_lClearMarkerBuffer(void)
{
  Fee_StateDataType  *StateDataPtr;
  uint8              *BufferPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  BufferPtr = &(StateDataPtr->FeeGcReadWriteBuffer[FEE_STATEPAGE_DATA_SIZE]);
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
  *((uint32*)(BufferPtr)) = (uint32)FEE_RESET;
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
  *((uint32*)(&(BufferPtr[4U]))) = (uint32)FEE_RESET;
}/* End of Fee_lClearMarkerBuffer */

/*******************************************************************************
** Syntax : static void Fee_lClearFeeReadWriteBuffer(void)                    **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This utility function clears the user read write buffer      **
*******************************************************************************/
/*[cover parentID={77BD326B-E54A-46ff-BF3B-E0185DD7372B}][/cover]*/
static void Fee_lClearFeeReadWriteBuffer(void)
{
  Fee_StateDataType  *StateDataPtr;
  uint32*             ReadWriteBuffPtr;
  uint16              DataByteCnt;
  uint32              Length;

  DataByteCnt = FEE_RESET;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
  ReadWriteBuffPtr = (uint32 *)StateDataPtr->FeeReadWriteBuffer;
  Length = FEE_DFLASH_WORDLINE_SIZE / FEE_DFLASH_WORD_SIZE;
  /* Clear the fee read write buffer */
  do
  {
    
    ReadWriteBuffPtr[DataByteCnt]= FEE_RESET;
    DataByteCnt++;
  }
  while (DataByteCnt != Length);
}

/*******************************************************************************
** Syntax : static void Fee_lClearFeeGcReadWriteBuffer(void)                  **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This utility function clears the Gc read write buffer        **
*******************************************************************************/
/*[cover parentID={0581E5CF-D0C5-407c-8996-FAB05B434301}][/cover]*/
static void Fee_lClearFeeGcReadWriteBuffer(void)
{
  Fee_StateDataType  *StateDataPtr;
  uint32*             GcReadWriteBuffPtr;
  uint16              DataByteCnt;
  uint32              Length;

  DataByteCnt = FEE_RESET;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
  GcReadWriteBuffPtr = (uint32 *)StateDataPtr->FeeGcReadWriteBuffer;
  Length = FEE_DFLASH_WORDLINE_SIZE / FEE_DFLASH_WORD_SIZE;

  /* Clear the fee GC read write buffer */
  do
  {
    GcReadWriteBuffPtr[DataByteCnt] = FEE_RESET;
    DataByteCnt++;
  }
  while (DataByteCnt != Length);
}

/*******************************************************************************
** Syntax : static void Fee_lHandleInitGcFail(void)                           **
**                                                                            **
** Service ID:                                                                **
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
** Description : This function shall handle the fail cases during             **
** InitGC state machine                                                       **
*******************************************************************************/
static void Fee_lHandleInitGcFail(void)
{
  Fee_StateDataType     *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* Enter InitGc fail state */
  StateDataPtr->FeeInitGCState = FEE_INITGC_FAIL;

  /* [cover parentID={483DFBF2-4B28-4570-9B30-58F0ED547A35}]
DEM enabled
[/cover] */
  /* Raise DEM */
#if (FEE_GC_INIT_DEM_REPORT == FEE_ENABLE_DEM_REPORT)
  /* [cover parentID={3F7C17A3-C6D0-4dbc-82EC-0B296B787768}]
Report error to DEM FEE_E_GC_INIT
[/cover] */
  Dem_ReportErrorStatus(FEE_E_GC_INIT, DEM_EVENT_STATUS_FAILED);
#endif
  /* [cover parentID={38EF0E49-29B4-479a-B002-217D55DC4F46}]
Is illegal state notification function configured?
[/cover] */
  /* Raise Illegal state notification if configured */
  if(Fee_CfgPtr->FeeNvmIllegalStateNotification != NULL_PTR)
  {
    /* [cover parentID={129A9B2F-A577-408f-9B20-F25A26D2F51A}]
Call the notification function
[/cover] */
    /* Call the Notification function */
    Fee_CfgPtr->FeeNvmIllegalStateNotification();
  }
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lPerformPrevBlkCheck (void)                 **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description :  Checks if there is enough space to accommodate the          **
** Last Written Block in case there is a wordline issue                       **
*******************************************************************************/
LOCAL_INLINE void Fee_lPerformPrevBlkCheck(void)
{
  Fee_StateDataType *StateDataPtr;
  uint32             DestAddr;
  uint32             Offset;
  uint32             WLAddr;
  uint8              LWBType;
  Fee_PageType       LWBPageCount;
  uint32             RemainingPages;
  uint16             LWBNum;
  uint16             LWBIndex;
  uint8              BankNumber;


  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  BankNumber = StateDataPtr->FeeStatusFlags.FeeCurrSector;
  DestAddr = StateDataPtr->FeeNextFreePageAddr;

  LWBNum = StateDataPtr->FeeLastWrittenBlkInfo.BlockNumber;
  LWBPageCount = StateDataPtr->FeeLastWrittenBlkInfo.PageCount;
  LWBIndex = Fee_lGetUsrBlockIndex(LWBNum);

  /* Get the next but one free WL address. Then calculate number free pages,
     because in case of write failure we will retry from next but one free WL */

  WLAddr = Fee_lGetNextWLAddr(DestAddr);
  WLAddr = WLAddr + FEE_DFLASH_WORDLINE_SIZE;

  RemainingPages = Fee_lGetFreeDFLASHPages(BankNumber,
                   WLAddr);
  Offset = DestAddr & FEE_DFLASH_WORDLINE_SIZE_1;

  /* Unconfig blocks are treated as Normal blocks */
  if(LWBIndex == FEE_LOG_BLOCK_NOT_FOUND)
  {
    LWBType = (uint8)FEE_NORMAL_DATA;
  }
  else
  {
    LWBType = (uint8)(Fee_CfgPtr->FeeBlockConfigPtr[LWBIndex].FeeImmediateData);
  }

  /* Affected page count (in the worst-case) = Page Count of the block which
     crossed the current word-line boundary + filled pages in the current WL */
  LWBPageCount = LWBPageCount + (Fee_PageType)(Offset >> FEE_BYTE_TO_PAGE);

  /*Get the remaining frees pages from next but on free WL. This is because
  in case of write failure will start writing from next but one free WL*/


  if ((LWBType == (uint8)FEE_NORMAL_DATA) &&
      ((boolean)TRUE == Fee_lIsSectorThresholdCrossed((uint32)RemainingPages,
          (uint32)LWBPageCount)))
  {
    /* In case of a compare failure, the affected previously written blocks
       cannot be accommodated before the threshold boundary of the current
       sector. Hence, start the current request at next free WL */
    DestAddr = Fee_lGetNextWLAddr(DestAddr);
  }
  else if ((LWBType == (uint8)FEE_IMMEDIATE_DATA) &&
           (RemainingPages < (uint32)LWBPageCount))
  {
    /* Previous Block cannot be accommodated if there is a compare failure
       Start the current request at new WL */
    DestAddr = Fee_lGetNextWLAddr(DestAddr);
  }
  else
  {
    /* Previous Block can be accommodated if there is a compare failure */
  }

  while (Fee_lIsUnerasableAddr(DestAddr) == TRUE)
  {
    DestAddr = Fee_lGetNextWLAddr(DestAddr);
  }
  StateDataPtr->FeeNextFreePageAddr = DestAddr;
}

/*******************************************************************************
** Syntax : LOCAL_INLINE Std_ReturnType Fee_lPerformCurrBlkCheck              **
**                                   (const Fee_BlockType * const BlockPt     **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockPtr                                                **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                   E_OK : Block can be accommodate in current sector        **
**                   E_NOT_OK : Block can not be accommodate in current sector**
**                                                                            **
** Description :  Checks if there is enough space to accommodate the          **
** Current requested Block                                                    **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fee_lPerformCurrBlkCheck(
  const Fee_BlockType * const BlockPtr)
{
  Fee_StateDataType *StateDataPtr;
  uint32             DestAddr;
  uint32             WLAddr;
  uint32             Offset;
  Fee_PageType       BlkPages;
  uint32             RemainingPages;
  uint8              BankNumber;
  Std_ReturnType     ReturnValue;

  ReturnValue = E_NOT_OK;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  BankNumber = StateDataPtr->FeeStatusFlags.FeeCurrSector;
  DestAddr = StateDataPtr->FeeNextFreePageAddr;


  if (StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus == (uint32)FEE_SET )
  {
    BlkPages = FEE_INVALID_BLOCK_PAGES;
  }
  else
  {
    BlkPages = Fee_lGetDFLASHPages((uint16)(BlockPtr->Size));
  }

  /*Check if next free page is beginning of WL. if yes then means no need to
    write old data in case of write failure.*/
  if(Fee_lIsWLBeginning(DestAddr) == FEE_NEW_WL_BEGIN)
  {
    RemainingPages = Fee_lGetFreeDFLASHPages(BankNumber, DestAddr);
  }
  else
  {
    /*This is not a WL beginning and there is some block data available in WL ,
      so in case of write failure we need write this data also. We will retry
      write from next to next free WL. So calculate the free pages from next
      to next free WL.This is done to avoid crossing sector boundary while
      write retry.
    */
    WLAddr = (Fee_lGetNextWLAddr(DestAddr) + FEE_DFLASH_WORDLINE_SIZE);

    RemainingPages = Fee_lGetFreeDFLASHPages(BankNumber, WLAddr);

    /*Total BlkPages = BlkPages + Number of filled pages in current WL*/

    Offset = (DestAddr & FEE_DFLASH_WORDLINE_SIZE_1);
    /* Convert the number of byte into pages */
    Offset = (Offset >> 3);

    Offset += BlkPages;

    /* Check if threshold will crossed in case of write retry . If yes mean we
     can not accommodate old data in current WL + requested block data.
     Switch next free page address to next free WL this will avoid corruption
     of old data in current WL in case write fail.
    */
    if ((boolean)TRUE == Fee_lIsSectorThresholdCrossed((uint32)RemainingPages,
        (uint32)Offset))
    {
      StateDataPtr->FeeNextFreePageAddr = Fee_lGetNextWLAddr(DestAddr);
      DestAddr = StateDataPtr->FeeNextFreePageAddr;
    }

    /*Now check if threshold crossed for current write request  */
    RemainingPages = Fee_lGetFreeDFLASHPages(BankNumber, DestAddr);

  }

  if ((boolean)TRUE == Fee_lIsSectorThresholdCrossed((uint32)RemainingPages,
      (uint32)BlkPages))
  {

    /*GC start is disabled by user keep the request in pending state*/
    /****** Check if it is a NORMAL REQUEST *******/
    if( (BlockPtr->FeeImmediateData == (uint32)FEE_NORMAL_DATA) ||
        (StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus
         == (uint32)FEE_SET )
      )
    {
      /* Do nothing */
    }
    /****** Check if it is a IMMEDIATE REQUEST *******/
    else
    {
      /* if this block cannot be accommodated in the DFLASH */
      if(RemainingPages < BlkPages)
      {
        /* Do nothing */
      }
      /**** Block can be accommodated within the current DFLASH Sector */
      else
      {
        StateDataPtr->FeeGCImmBlkWrite = (boolean)TRUE;
        ReturnValue = E_OK;
      }
    }/* End of immediate write check */


    if (StateDataPtr->FeeGcState == FEE_GC_IDLE)
    {
      /* GC should be triggered only if DisableGCStart is FALSE */
      if(StateDataPtr->FeeDisableGCStart == (boolean)FALSE)
      {
        /* Request for Garbage Collection and continue */
        StateDataPtr->FeeGcState = FEE_GC_REQUESTED;
      }
    }
  }
  /* Threshold NOT Crossed*/
  else
  {
    ReturnValue = E_OK;
  }

  return(ReturnValue);
}

/*******************************************************************************
** Syntax : LOCAL_INLINE Std_ReturnType Fee_lPerformWriteCheck                **
**                               ( const Fee_BlockType * const BlockPtr)      **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockPtr                                                **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Return value    :  E_NOT_OK / E_OK                                         **
**                                                                            **
** Description :  Checks if there is enough space to accommodate the request  **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fee_lPerformWriteCheck(
  const Fee_BlockType * const BlockPtr)
{
  uint32             DestAddr;
  Fee_StateDataType *StateDataPtr;
  Std_ReturnType     ReturnValue;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  DestAddr = StateDataPtr->FeeNextFreePageAddr;
  while(Fee_lIsUnerasableAddr(DestAddr) == TRUE)
  {
    DestAddr = Fee_lGetNextWLAddr(DestAddr);
  }
  StateDataPtr->FeeNextFreePageAddr = DestAddr;

  /* Check if Previous Block can be accommodated if there is a compare failure
   */
  if( (Fee_lIsWLBeginning(DestAddr) != FEE_NEW_WL_BEGIN) &&
      (StateDataPtr->FeeLastWrittenBlkInfo.Status.Consistent ==
       (uint32)FEE_SET ))
  {
    Fee_lPerformPrevBlkCheck();
  }

  /* Check if Current Block can be accommodated */
  ReturnValue = Fee_lPerformCurrBlkCheck(BlockPtr);

  return(ReturnValue);
}
#endif
/*******************************************************************************
** Syntax : static void Fee_lHandleWriteFail(void)                            **
**                                                                            **
** Service ID:                                                                **
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
** Description : This function shall handle the severe error                  **
** (compare failed twice or internal write fail) case during                  **
** write state machine                                                        **
*******************************************************************************/
/*[cover parentID={786A84CA-3DC9-4f2e-AC4D-4F37A18654E2}][/cover]*/
static void Fee_lHandleWriteFail(void)
{
  Fee_StateDataType  *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* Enter Write Fail State */
  StateDataPtr->FeePendReqStatus = FEE_WRITE_FAIL;

  /* [cover parentID={FA984E1B-1BF3-4870-AC78-8D5F47D8F68F}]
DEM enabled
[/cover] */
  /* Raise Job Failed DEM */
#if (FEE_WRITE_DEM_REPORT == FEE_ENABLE_DEM_REPORT)
  /* [cover parentID={45A51475-D8A1-4f4f-A794-971AE5C1303F}]
Report error to DEM FEE_E_WRITE
[/cover] */
  Dem_ReportErrorStatus(FEE_E_WRITE, DEM_EVENT_STATUS_FAILED);
#endif

  /* [cover parentID={F2A40B82-4348-489d-A08A-E96C4D4B9A9E}]
Is illegal state notification configured?
[/cover] */
  /* Raise Illegal state notification if configured */
  if(Fee_CfgPtr->FeeNvmIllegalStateNotification != NULL_PTR)
  {
    /* [cover parentID={8205126C-3839-46e9-9217-41FBA246ABD5}]
Call the notification function
[/cover] */
    /* Call the Notification function */
    Fee_CfgPtr->FeeNvmIllegalStateNotification();
  }
}

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

/*******************************************************************************
** TRACEABILITY: []                                                           **
**                                                                            **
** Syntax : LOCAL_INLINE Std_ReturnType Fee_lPerformReadCheck                 **
**                                              (const uint16 UserBlockIndex) **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  UserBlockIndex       block index                        **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Return value    :                                                          **
**                  E_NOT_OK : Block is not valid or inconsistent             **
**                  E_OK : Block is  valid and consistent                     **
**                                                                            **
** Description :  This utility function checks if the requested copy of the   **
** logical data block is consistent and valid                                 **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fee_lPerformReadCheck(const uint16 UserBlockIndex)
{
  Fee_StateDataType     *StateDataPtr;
  const Fee_CacheType         *BlockPtr;
  Std_ReturnType         RetVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  BlockPtr = &StateDataPtr->FeeBlockInfo[UserBlockIndex];

#if (FEE_GET_PREV_DATA_API == STD_ON)
  if (StateDataPtr->FeePendReqInfo.GetPrevCopy == FEE_SET )
  {
    /* [cover parentID={AD46AE06-503D-4882-AA6C-7D8A55EA85B5}]
Is the logical block inconsistent?
[/cover] */
    if (BlockPtr->Status.PrevCopyConsistent == (uint32)FEE_RESET)
    {
      /* [cover parentID={94D9D304-CF44-48f6-BB78-CF09C9B05E89}]
Update Fee job result as block MEMIF_BLOCK_INCONSISTENT
[/cover] */
      StateDataPtr->FeeJobResult = MEMIF_BLOCK_INCONSISTENT;
      RetVal = E_NOT_OK;
    }
    /* [cover parentID={6EE8825D-927C-4fcc-A417-C16110628F48}]
Is the logical block invalid?
[/cover] */
    /* If the logical block is invalid */
    else if (BlockPtr->Status.PrevCopyValid == (uint32)FEE_RESET)
    {
      /* [cover parentID={77F3C9CE-CA24-40aa-B913-D26A9F163082}]
Update Fee job result as MEMIF_BLOCK_INVALID
[/cover] */
      StateDataPtr->FeeJobResult = MEMIF_BLOCK_INVALID;
      RetVal = E_NOT_OK;
    }
    else
    {
      RetVal = E_OK;
    }
  }
  else
#endif
  {
    /* [cover parentID={0D4A8E30-6FC8-4406-A285-B15DAC21978D}]
Is the current block inconsistent?
[/cover] */
    /* If the logical block is inconsistent */
    if (BlockPtr->Status.Consistent == (uint32)FEE_RESET)
    {
      /* [cover parentID={E4EF58C8-FA1D-4cc1-9DCE-22EF5B1093EE}]
Update Fee job result as block MEMIF_BLOCK_INCONSISTENT
[/cover] */
      StateDataPtr->FeeJobResult = MEMIF_BLOCK_INCONSISTENT;
      RetVal = E_NOT_OK;
    }
    /* [cover parentID={77388B83-623E-41a1-A3D0-BAB58D4D8800}]
Is the current logical block invalid?
[/cover] */
    /* If the logical block is invalid */
    else if (BlockPtr->Status.Valid == (uint32)FEE_RESET)
    {
      /* [cover parentID={5D5C5B38-2F93-47c5-AFCF-AEEF745F2C1B}]
Update Fee job result as MEMIF_BLOCK_INVALID
[/cover] */
      StateDataPtr->FeeJobResult = MEMIF_BLOCK_INVALID;
      RetVal = E_NOT_OK;
    }
    else
    {
      RetVal = E_OK;
    }
  }

  return(RetVal);
}



/*******************************************************************************
** Syntax : static void Fee_lUpdateBlockInfo(const Fee_CacheStatusType Status,**
**                               const uint16 Index, const uint16 pageCount)  **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :Status: State of data block                               **
**                   Index: Block Index in cache table                        **
**                   pageCount: Page count                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : This utility function updates the cache table with the       **
** block info                                                                 **
*******************************************************************************/
static void Fee_lUpdateBlockInfo(const Fee_CacheStatusType Status,
                                 const uint16 Index, const uint16 pageCount)
{
  Fee_CacheType           *CachePtr;
  Fee_StateDataType       *StateDataPtr;
  uint32                   NewPageCount;
  uint32                   BlockCycleCount;
  uint32                   PrvBlockCycleCount;
  const uint8              *TempArrayPtr;
  
  /* [cover parentID={30EAC34E-D3B0-4a50-A537-95F31B835280}]
    Point the Cacheptr to the block using block index
     [/cover] */
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  CachePtr = &(StateDataPtr->FeeBlockInfo[Index]);



  NewPageCount = pageCount;
  NewPageCount = (NewPageCount - FEE_ONE);
  /* [cover parentID={037D3D77-B1DD-4e8f-98E5-06FE5FC7B626}]
      Was cache update done for the block?
      [/cover] */
  if(CachePtr->Address == FEE_RESET)
  {
    /* [cover parentID={0A64E26F-7A17-411d-A3E1-C7F100221AFF}]
    Update the cache with block address
    Update valid, consistent and copied fields
    [/cover] */
    /* Update the cache with block Address */
    CachePtr->Address = StateDataPtr->FeeCurrSectSrcAddr;
    CachePtr->Status.Valid = Status.Valid;
    CachePtr->Status.Consistent = Status.Consistent;
    CachePtr->Status.Copied = Status.Copied;
    CachePtr->BlockSize = (NewPageCount * FEE_SEVEN);
  }
  /* [cover parentID={5ED60E83-4A2D-41b3-BEBC-CCF626AF975F}]
     Is the previous copy address reset?
     [/cover] */
  else if(CachePtr->PrevCopyAddress == FEE_RESET)
  {
    
    /*Get the cycle count of the current copy of block*/
    BlockCycleCount = Fee_lGetBlkCycleCount(Index);

    /*Get the cycle count of block from FeeReadWriteBuffer*/
    /*Here the intention is to read Bytes 3,4,5 from the data block 
      which together indicates BCC. First bytes 2 to 5 are read and BCC bytes
      are extracted */
    TempArrayPtr = &(StateDataPtr->FeeReadWriteBuffer[FEE_BLOCK_CYL_CNT_POS]);
    /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
    PrvBlockCycleCount = *((const uint32*)TempArrayPtr);
    /*Remove the MSB of number of data pages */
    PrvBlockCycleCount = (PrvBlockCycleCount >> FEE_EIGHT);
    /* [cover parentID={BE4264CB-8FAB-4f96-87A2-4ABED6C04875}]
       Update the cache with block address of previous copy
      Merk the previous copy as consistent
      [/cover] */
    /*Check if the cycle count of previous copy of block is 1 less than of cycle
    count of current copy of block if yes then only update cache table.*/
    if(PrvBlockCycleCount == (BlockCycleCount - FEE_ONE))
    {
      /* Update the cache with block Address of previous copy */
      CachePtr->PrevCopyAddress = StateDataPtr->FeeCurrSectSrcAddr;
      CachePtr->PrevBlkSize = (NewPageCount * FEE_SEVEN);
      CachePtr->Status.PrevCopyValid = Status.Valid;
      CachePtr->Status.PrevCopyConsistent = Status.Consistent;
      CachePtr->Status.PrevCopyCopied = Status.Copied;
    }
  }
  /* [cover parentID={0A64E26F-7A17-411d-A3E1-C7F100221AFF}]
        Update the cache with block address
       Update valid, consistent and copied fields
      [/cover] */
  else
  {
     /*Dummy Else to avoid MISRA*/
  }
}



/*******************************************************************************
** Syntax : static void Fee_lUpdateUnconfigBlockInfo(const uint16 BlockNumber,**
**                                                   const uint16 PageCount)  **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockNumber - Block Number                              **
**                    PageCount   - page count                                **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : This function does the cache table update of the             **
**               un-configured block                                          **
*******************************************************************************/
static void Fee_lUpdateUnconfigBlockInfo(const uint16 BlockNumber, \
    const uint16 PageCount)
{
  Fee_StateDataType       *StateDataPtr;
  Fee_CacheType           *UnconfigBlockPtr;
  uint16                   UnconfigBlockIndex;
  uint16                   TempUnConfigBlockCount;


  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  TempUnConfigBlockCount = StateDataPtr->FeeUnConfigBlockCount;

  UnconfigBlockIndex = FEE_RESET;

  UnconfigBlockPtr = &(StateDataPtr->FeeBlockInfo[Fee_CfgPtr->FeeBlkCnt]);


  while((UnconfigBlockIndex < TempUnConfigBlockCount) &&
        (UnconfigBlockPtr->BlockNumber != BlockNumber))
  {
    UnconfigBlockIndex++;

    UnconfigBlockPtr++;
  }
  if(UnconfigBlockIndex == TempUnConfigBlockCount)
  {
    /* check if the cache table has space */
    if(((Fee_CfgPtr->FeeBlkCnt) + TempUnConfigBlockCount) <
        (uint16)(FEE_TOTAL_BLOCK_COUNT))
    {
      /* [cover parentID={C63246F2-315E-401f-9747-82A5A030B401}]
      DEM enabled
      [/cover] */
#if (FEE_UNCFG_BLK_DEM_REPORT == FEE_ENABLE_DEM_REPORT)
      if(((Fee_CfgPtr->FeeBlkCnt) + TempUnConfigBlockCount) ==
          FEE_MAX_BLOCK_COUNT)
      {
        /* [cover parentID={45BBF021-539B-42c1-96BB-232F0BA519E2}]
           Report error to DEM FEE_E_UNCONFIG_BLK_EXCEEDED
           [/cover] */
        Dem_ReportErrorStatus(FEE_E_UNCONFIG_BLK_EXCEEDED,
                              DEM_EVENT_STATUS_FAILED);
      }
#endif

      if(UnconfigBlockPtr->Address == FEE_RESET )
      {
      UnconfigBlockPtr->Address = StateDataPtr->FeeCurrSectSrcAddr;
      UnconfigBlockPtr->BlockNumber = BlockNumber;
      UnconfigBlockPtr->BlockSize = (uint32)((uint32)PageCount * FEE_SEVEN);
      TempUnConfigBlockCount++;
      }
      
    }
    else
    {
      /* Un-configured blocks cache table is already full */
      StateDataPtr->FeeUncfgBlksExceeded = FEE_UNCONFIG_BLK_LIMIT_CROSSED;
    }
  }
  StateDataPtr->FeeUnConfigBlockCount = TempUnConfigBlockCount;
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lUpdateGcCurrBlockInfo(void)                **
**                                                                            **
** Service ID: NA                                                             **
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
** Description : Updates the block information of the block being written     **
**               during Garbage collection                                    **
*******************************************************************************/
LOCAL_INLINE void Fee_lUpdateGcCurrBlockInfo(void)
{
  Fee_StateDataType    *StateDataPtr;
  Fee_GcBlkInfoType    *GcBlkPtr;
  const uint8                *ReadWriteBufferPtr;
  Fee_PageType          PageCount;
  uint32                WordValue;
  uint16                BlockNumber;
  uint16                Offset;
   /* [cover parentID={414D95EA-8C04-4a5c-8591-8DC77E0EBE19}]
   Fee_lUpdateGcCurrBlockInfo
   [/cover] */
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  GcBlkPtr = &(StateDataPtr->FeeGcCurrBlkInfo);
  Offset = (uint16)((StateDataPtr->FeeGcDestAddr) & FEE_DFLASH_WORDLINE_SIZE_1);
  ReadWriteBufferPtr = &(StateDataPtr->FeeGcReadWriteBuffer[Offset]);

  /* Extract block number and page count */
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
  WordValue = *(const uint32 *)ReadWriteBufferPtr;
  BlockNumber = (uint16)(WordValue >> FEE_EIGHT);

  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
  PageCount = *((const uint16*)(&ReadWriteBufferPtr[FEE_BLOCK_NUM_POS]));
  PageCount = (PageCount & (uint16)FEE_PAGE_COUNT_MASK);

  /* Update FeeGcCurrBlkInfo */
  GcBlkPtr->Addr = StateDataPtr->FeeGcSrcAddr;
  GcBlkPtr->BlockNumber = BlockNumber;
  GcBlkPtr->PageCount = PageCount;
  GcBlkPtr->Consistent = FEE_SET ;
}
#endif
/*******************************************************************************
** Syntax : static Std_ReturnType Fee_lRegisterNvmRead(                       **
**                            const uint16 BlockNumber,                       **
**                            const uint16 BlockOffset,                       **
**                            uint8 * const DataBufferPtr,                    **
**                            const uint16 Length)                            **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockNumber : Logical block number                      **
**                    BlockOffset : Read address offset within the block      **
**                    Length      : Number of bytes to be read                **
**                    DataBufferPtr : pointer to data buffer                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                    E_OK : Request is registered.                           **
**                    E_NOT_OK : Request is not registered. FEE module is busy**
**                     in servicing other request.                            **                                                                            **
** Description : This function will register the NVM read request in the      **
** pending request buffer if FEE is Idle or If erase suspend enabled and QS   **
** Erase is ongoing                                                           **
*******************************************************************************/
/* [cover parentID={24E7F068-5567-4b01-9D6C-6A80C21B9E4A}][/cover] */
static Std_ReturnType Fee_lRegisterNvmRead( const uint16 BlockNumber,
    const uint16 BlockOffset, uint8 * const DataBufferPtr, const uint16 Length,
    const uint8 GetPrevCopy)
{
  Fee_StateDataType  *StateDataPtr;
  Std_ReturnType RetVal;
  Fee_PendReqBufType   *PendReqPtr;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /* [cover parentID={6A1D98CD-158F-4702-8165-6C5C726CD8BB}]
Set Flag as E_NOT_OK
[/cover] */
  RetVal = E_NOT_OK;

  PendReqPtr = &(StateDataPtr->FeePendReqInfo);

  if(StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_NO_REQ)
  {
    /* [cover parentID={E8DF5530-B41E-4d87-A006-C3611C761B94}]
Set Flag as E_OK
[/cover] */
    RetVal = E_OK;
  }
#if(FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY) && \
   (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
  else
  {
    /* [cover parentID={399A2610-BEB7-48e8-94B0-57E9486B0762}]
Check for QS job status
[/cover] */
    if((StateDataPtr->FeeQsState == (uint8)FEE_QS_PROG_STATE_ERASE_COMPLETE) &&
        (StateDataPtr->FeeQsJobStatus == FEE_JOB_REQSTD))
    {
      RetVal = Fls_17_Dmu_SuspendErase();

      if(RetVal == E_OK)
      {
        StateDataPtr->FeeQsEraseSuspend = FEE_ERASE_SUSPENDED;
        StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
        StateDataPtr->FeeQsJob = FEE_NO_JOB;
      }
    }
    else if(StateDataPtr->FeeQsEraseSuspend == FEE_ERASE_SUSPENDED)
    {
      RetVal =  E_OK;
      StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
      StateDataPtr->FeeQsJob = FEE_NO_JOB;
    }
    else
    {
      /*Dummy else for misra */
    }
  }
#endif
  if(RetVal == E_OK)
  {
    /* [cover parentID={CB7A79BC-C5B6-4331-B3C0-7179A6CD5D2A}]
Store the read request parameters in the pending buffer structure
Update pending request status as 'read requested' and job result as 'MEMIF_JOB_PENDING'
[/cover] */
    /* Store the read request parameters in the Pending buffer structure */
    PendReqPtr->BlockNumber = BlockNumber;
    PendReqPtr->BlockOffset = BlockOffset;
    PendReqPtr->DataBufferPtr = DataBufferPtr;
    PendReqPtr->Length = Length;

#if (FEE_GET_PREV_DATA_API == STD_ON)
    if(GetPrevCopy == FEE_SET)
    {
      PendReqPtr->GetPrevCopy = FEE_SET;
    }
    else
    {
      PendReqPtr->GetPrevCopy = FEE_RESET;
    }
#else
    UNUSED_PARAMETER (GetPrevCopy);
#endif
    StateDataPtr->FeeStatusFlags.FeeStartInitGC = FEE_SET ;
    /* [cover parentID={CB7A79BC-C5B6-4331-B3C0-7179A6CD5D2A}]
    Store the read request parameters in the pending buffer structure
    Update pending request status as 'read requested' and job result as
    'MEMIF_JOB_PENDING'
    [/cover] */
    StateDataPtr->FeePendReqStatus = FEE_REQ_READ;
    StateDataPtr->FeeJobResult = MEMIF_JOB_PENDING;
  }
  else
  { /* [cover parentID={F649153E-80B1-4dbf-9EF1-E647F532C64B}]
DET or safety is enabled
[/cover] */
    /* FEE is busy with another request; raise BUSY DET */
#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
    /* [cover parentID={8C968070-3390-4bc2-8D73-62CDEF71B014}]
    Report error to DET/SAFETY
    [/cover] */
#if (FEE_GET_PREV_DATA_API == STD_ON)
    if(GetPrevCopy == FEE_SET)
    {
      /* If get previous copy is set then only report safety error. Because
      request came from non autosar API */
#if (FEE_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={24DA148C-A961-4d92-BECC-20FA7400C850}]
Report error to API GetPrevData
[/cover] */
      Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                             FEE_SID_GETPREVDATA, FEE_E_BUSY);
#endif
    }
    else
#endif
    {
     /* [cover parentID={8C968070-3390-4bc2-8D73-62CDEF71B014}]
Report error to DET FEE_SID_READ
[/cover] */
      Fee_lReportError(FEE_SID_READ, FEE_E_BUSY);
    }
#endif
  }
  /* [cover parentID={138DF8B8-2FED-407d-AF0C-3015C8E3F599}]
Return Flag status
[/cover] */
  return(RetVal);
  /* [cover parentID={D6919DDB-986F-49ac-BBC4-FE6D936C3127}]
Return
[/cover] */
}

/*******************************************************************************
** Syntax : static Std_ReturnType                                             **
**   Fee_lRegisterNvmWrite(const uint8 * const DataWriteBufferPtr,            **
**                                      const Fee_BlockType * const BlockPtr) **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  DataWriteBufferPtr : Data buffer pointer                **
**                    BlockPtr      : Block cache pointer                     **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                    E_OK : Request is registered.                           **
**                    E_NOT_OK : Request is not registered. FEE module is busy**
**                     in servicing other request.                            **
** Description : This function will register the NVM write request in the     **
** pending request buffer if FEE is Idle or If erase suspend enabled and QS   **
** Erase is ongoing                                                           **
*******************************************************************************/
/* [cover parentID={71B119F7-AF7C-487b-8BD3-C20F63E92269},
{754520DC-4BD9-4c7d-AB85-FB6AB5BC9EAF}]
Fee_lRegisterNvmWrite
[/cover] */
static Std_ReturnType Fee_lRegisterNvmWrite( \
    const uint8 * const DataWriteBufferPtr, \
    const Fee_BlockType * const BlockPtr)
{
  /* [cover parentID={71B119F7-AF7C-487b-8BD3-C20F63E92269}]*/
  Fee_StateDataType  *StateDataPtr;
  Std_ReturnType RetVal;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  if(StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_NO_REQ)
  {
    /* [cover parentID={3940BCA6-5C15-4d8a-A009-DFB34F58D94A}]
Register write request
[/cover] */
    /* Register the write request */
    StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus = FEE_RESET;
    Fee_lRegisterWriteRequest(DataWriteBufferPtr, BlockPtr);
    /* [cover parentID={197B7188-11D0-4aaa-8350-F7B78E20EAFD}]
Return E_OK
[/cover] */
    RetVal = E_OK;
  }
  else
  {
    /* FEE is busy with other request; raise BUSY DET */
    /* [cover parentID={89275CDB-C274-4144-A84F-EB6BFDACBFC9}]*/
    /* [cover parentID={2010672E-36A5-49cd-A0DB-29F149E19143}]*/
  /* [cover parentID={3D6AEEC1-308A-4936-9F67-E0D66B51C3E5}]
FEE_DEV_ERROR_DETECT is enabled FEE_SAFETY_ENABLE is enabled
[/cover] */
#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={2010672E-36A5-49cd-A0DB-29F149E19143}]
Report FEE_E_BUSY error
[/cover] */
    Fee_lReportError(FEE_SID_WRITE, FEE_E_BUSY);
#endif
/* [cover parentID={89275CDB-C274-4144-A84F-EB6BFDACBFC9}]
Report E_NOT_OK
[/cover] */
    RetVal = E_NOT_OK;

  }
  return(RetVal);
}
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** Syntax : void Fee_lperformStuffCheck(const uint16 UserBlockIndex)          **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  UserBlockIndex : Block Index                            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This utility function checks if the requested block size is  **
**               different in DFlash & configured value and performs          **
**               stuffing the extra user bytes with zero if necessary         **
*******************************************************************************/
LOCAL_INLINE void Fee_lperformStuffCheck(const uint16 UserBlockIndex)
{
  Fee_StateDataType  *StateDataPtr;
  uint8*             DataBufPtr;
  uint16             Count;
  uint16             DflashBlkSize;
  uint16             BlkOffset;
  uint16             BlkLength;
  uint16             TmpCount;
  uint16             StuffLen;
 
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
#if (FEE_GET_PREV_DATA_API == STD_ON)
  if(StateDataPtr->FeePendReqInfo.GetPrevCopy == FEE_SET )
  {
    DflashBlkSize = (uint16)StateDataPtr->FeeBlockInfo[UserBlockIndex].PrevBlkSize;
  }
  else
#endif
  {
    DflashBlkSize = (uint16)StateDataPtr->FeeBlockInfo[UserBlockIndex].BlockSize;
  }
  BlkOffset = StateDataPtr->FeePendReqInfo.BlockOffset;
  BlkLength = StateDataPtr->FeePendReqInfo.Length;

  DataBufPtr = StateDataPtr->FeePendReqInfo.DataBufferPtr;

  if(BlkLength > (uint16)0)
  {
    /* [cover parentID={733A15E7-7C0F-46d0-B83E-B42D2FC0930E}]
Is block offset greater than configured block size?
[/cover] */
    /* check whether block offset is greater than configured block size */
    if(BlkOffset > DflashBlkSize)
    {
      for(Count = FEE_RESET; Count <= BlkLength; Count++)
      {
        DataBufPtr[Count] = FEE_RESET;
      }
#if((FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA ) && \
    (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON))
      /*Check if QS erase was suspended. If yes then set FeePendReqStatus to
      FEE_REQ_QUASI_ERASE to set module status to busy.*/
      if(StateDataPtr->FeeQsEraseSuspend == FEE_ERASE_SUSPENDED)
      {
        StateDataPtr->FeePendReqStatus = FEE_REQ_QUASI_ERASE;
        StateDataPtr->FeeQsJob = FEE_ERASE_JOB;
      }
      else
#endif
      {
        /* reset the pending request status */
        StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_NO_REQ;
      }
      /* Set the job result */
      StateDataPtr->FeeJobResult = MEMIF_JOB_OK;
      /* Call user configured job End notification */
      if ( Fee_CfgPtr->FeeNvmJobEndNotification != NULL_PTR )
      {
        /* [cover parentID={3A7A259F-C7F7-4a71-B8B2-52A71CE93270}]
Call the notification function
[/cover] */
        (Fee_CfgPtr->FeeNvmJobEndNotification)();
      }
       
      
    }
    else if( (BlkOffset + BlkLength) > DflashBlkSize)
    {
      TmpCount = DflashBlkSize - BlkOffset;
      StuffLen = BlkLength - TmpCount;
      StateDataPtr->FeePendReqInfo.Length = TmpCount;
      DataBufPtr = &(StateDataPtr->FeePendReqInfo.DataBufferPtr[TmpCount]);

      /* [cover parentID={FFDEF83C-CEA1-4473-BB90-168255B48FD5}]
Stuff the buffer with zero data upto stuff length
[/cover] */
      for(Count = FEE_RESET; Count <= StuffLen; Count++)
      {
        DataBufPtr[Count] = FEE_RESET;
      }
    }
    else
    {
      /* Do Nothing */
    }
  }
  /* If length is zero, then reset the status*/
  else
  {
#if((FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA ) && \
    (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON))
    /*Check if QS erase was suspended. If yes then set FeePendReqStatus to
    FEE_REQ_QUASI_ERASE to set module status to busy.*/
    if(StateDataPtr->FeeQsEraseSuspend == FEE_ERASE_SUSPENDED)
    {
      StateDataPtr->FeePendReqStatus = FEE_REQ_QUASI_ERASE;
      StateDataPtr->FeeQsJob = FEE_ERASE_JOB;
    }
    else
#endif
    {
      StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_NO_REQ;
    }
    /*************   RESET JOB VARIABLES ******************/
    StateDataPtr->FeeJobResult = MEMIF_JOB_OK;
#if (FEE_GET_PREV_DATA_API == STD_ON)
    StateDataPtr->FeePendReqInfo.GetPrevCopy = FEE_RESET;
#endif
    /*****************************************************/

    /* Call user configured job End notification */
    if ( Fee_CfgPtr->FeeNvmJobEndNotification != NULL_PTR )
    {
      (Fee_CfgPtr->FeeNvmJobEndNotification)();
    }
  }

}
#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
/*******************************************************************************
** Syntax : static void Fee_lQsInit(void)                                     **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function will initialize the QS Block Management        **
** Environment variables and also update status of each QS block in cache     **
*******************************************************************************/
/*[cover parentID={0A218B3E-DFB2-4f73-BECF-72D47C85062D}][/cover]*/
static void Fee_lQsInit(void)
{
  Fee_CacheType       *CachePtr;
  const Fee_BlockType *BlockPtr;
  uint32               Index;
  Fee_StateDataType   *StateDataPtr;
  const uint8         *TgtAddr;
  uint32               SrcAddr;


  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  StateDataPtr->FeeQuasiBlkInstanceTemp = FEE_RESET;
#if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
  StateDataPtr->FeeQsEraseSuspend = FEE_ERASE_NOT_SUSPENDED;
#endif
  StateDataPtr->FeeQsState = FEE_QS_IDLE;
  StateDataPtr->FeeQsJob = FEE_NO_JOB;
  StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
  StateDataPtr->FeeQsRepairIndex = FEE_RESET;
  StateDataPtr->FeeInitQSState = FEE_RESET;
  StateDataPtr->FeeQsJobResult = MEMIF_JOB_OK;
  StateDataPtr->FeeHardeningWLCount = FEE_RESET;
  StateDataPtr->FeeHardeningPageCount = FEE_RESET;
  StateDataPtr->FeeQsHardeningOffset = FEE_RESET;
  StateDataPtr->FeeQsCancelAll = FEE_RESET;
  StateDataPtr->FeeHardenFlag = FEE_QS_HARDING_IDLE;

  CachePtr = &(StateDataPtr->FeeBlockInfo[FEE_QSBLOCK_BEGIN_INDEX]);
  BlockPtr = &(Fee_CfgPtr->FeeBlockConfigPtr[FEE_QSBLOCK_BEGIN_INDEX]);
  Index = FEE_RESET;
  TgtAddr = StateDataPtr->FeeReadWriteBuffer;

  while(Index < FEE_NUM_QUASI_BLOCKS)
  {

    SrcAddr = BlockPtr->Address;
    CachePtr->Address = SrcAddr;
    CachePtr->Status.QsDirtyErase = 0;
    CachePtr->Status.QsDirtyWrite = 0;
    CachePtr->Status.State = FEE_QS_INVALID;

    (void)Fls_17_Dmu_ReadWordsSync(
      (Fls_17_Dmu_AddressType)SrcAddr,
      /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with FLS.
      FEE is passing parameters to FLS APIs, for example,
      Fls_17_Dmu_CompareWordsSync. Changing this will break the interfacing and
      will cause major functional issues both on FLS and FEE side. */
      /*MISRA2012_RULE_11_8_JUSTIFICATION:Agreed Violation.
      solvable but gives compiler warnings buffer*/
      (uint32*)(TgtAddr),
      (Fls_17_Dmu_LengthType)(
        (FEE_QS_STATUS_PAGES * FEE_DFLASH_PAGE_SIZE)/FEE_DFLASH_WORD_SIZE));

    Fee_lEvalQsBlockState(CachePtr);

    Index++;
    CachePtr++;
    BlockPtr++;
  }

  StateDataPtr->FeeQsJob = FEE_REPAIR_JOB;
}

/******************************************************************************
** Syntax : Std_ReturnType Fee_17_EraseQuasiStaticData(                      **
**          const uint16 BlockNumber, const uint16 Instances)                **
**                                                                           **
** Traceability   : [cover parentID={49B35985-54F0-4ae0-B288-8C77E3121785}]  **
**                                                                           **
** Service ID:        0x25                                                   **
**                                                                           **
** Sync/Async:  Asynchronous                                                 **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) :  BlockNumber : Logical block number                     **
**                    Instances   : Number of block instances                **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  Std_ReturnType                                         **
**            E_OK : Erase Request is accepted                               **
**                    E_NOT_OK : Erase Request is not accepted               **
**                                                                           **
** Description : Service to initialize an erase job for one or               **
** multiple consecutive instances of a quasi-static data block               **
******************************************************************************/
/* [cover parentID={FA53B348-A966-4d6d-A389-EFC4E28BEA98}]
Fee_17_EraseQuasiStaticData
[/cover] */
Std_ReturnType Fee_17_EraseQuasiStaticData(const uint16 BlockNumber,
    const uint16 Instances)
{
  /* [cover parentID={FA53B348-A966-4d6d-A389-EFC4E28BEA98}]*/
  Fee_StateDataType  *StateDataPtr;
  uint16               BlockIndex;
  Std_ReturnType       RetVal;
  RetVal = E_NOT_OK;
#if (FEE_SAFETY_ENABLE == STD_ON)
  /*Check Fee_CfgPtr is null if yes return E_not_ok . This done to avoid trap
  if fee_init is not called */
  if(Fee_CfgPtr != NULL_PTR)
#endif
  {
    StateDataPtr = Fee_CfgPtr->FeeStatePtr;

    if(StateDataPtr->FeeInitQSState == FEE_INITQS_COMPLETE)
    {

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
  /* [cover parentID={BC67202F-81F1-4360-BA20-E8E49607151D}]
Is GC idle and no pending request?
[/cover] */
      if(( StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_NO_REQ ) &&
          ( StateDataPtr->FeeGcState == FEE_GC_IDLE))
#else
  /* [cover parentID={E03222E8-DFF9-4218-96EC-F2960E28FA4B}]
If GC is not idle or pending request exsists?
[/cover] */
      if(StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_NO_REQ )
#endif
      { 
    /* [cover parentID={6A2F02C4-16B3-4795-B6C4-7BD1D53D3324}]
Get the block index of the requested QS block
[/cover] */
        /* Get index of the block info stored in cache */
        BlockIndex = Fee_lGetUsrBlockIndex(BlockNumber);

        /*Accept the request only for QS block*/
        if((BlockIndex != FEE_LOG_BLOCK_NOT_FOUND) &&
            (Fee_CfgPtr->FeeBlockConfigPtr[BlockIndex].FeeUser ==
             (uint8)FEE_QUASI_STATIC_USER))
        {
          if(Instances == FEE_ZERO)
          {
            /*Invalid block instances value, raise safety error
             if configured */
            RetVal = E_NOT_OK;
      /* [cover parentID={706A3FE2-81A4-4f2e-9F94-F2114A858C94}]
Safety error is enabled
[/cover] */
#if(FEE_SAFETY_ENABLE == STD_ON)
      /* [cover parentID={27F3883E-18DB-49f2-81A9-8AF55E32DD9A}]
Report error FEE_E_INVALID_BLOCK_INTS
[/cover] */
            Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                                   FEE_SID_ERASEQUASISTATICDATA,
                                   FEE_E_INVALID_BLOCK_INSTANCES);
#endif
          }
      /* [cover parentID={F11117B3-1478-48a4-B55F-6FED8871BFE0}]
(Input instances is less than the configured block instances) or (is configured block instances equals zero and given instances is 1) ?
[/cover] */
          else if((Instances <= Fee_CfgPtr->FeeBlockConfigPtr[BlockIndex].Instances)
                  || ((Fee_CfgPtr->FeeBlockConfigPtr[BlockIndex].Instances == FEE_ZERO)
                      && (Instances == FEE_ONE)))
          {
            StateDataPtr->FeePendEraseInfo.CacheIndex = BlockIndex;
            StateDataPtr->FeePendEraseInfo.BlockInstances = Instances;
            StateDataPtr->FeePendEraseInfo.BlockNumber = BlockNumber;
            StateDataPtr->FeeQuasiBlkInstanceTemp = FEE_RESET;
            StateDataPtr->FeePendReqStatus = FEE_REQ_QUASI_ERASE;
            StateDataPtr->FeeQsJobResult = MEMIF_JOB_PENDING;
            StateDataPtr->FeeQsJob = FEE_ERASE_JOB;
            StateDataPtr->FeeQsState = (uint8)FEE_QS_PROG_STATE_ERASE_STARTED;
            StateDataPtr->FeeCurrReqBlockNum = BlockNumber;
            RetVal = E_OK;
            
            /* Set this flag to start GC and cache update process before 
            serving Erase request.This will insure proper Erase operation in 
            case GC is disabled during FEE initialization */
            StateDataPtr->FeeStatusFlags.FeeStartInitGC = FEE_SET ;
          }
          else
          {
            /*Invalid block instances value, raise safety error
              if configured */
            RetVal = E_NOT_OK;
      
#if(FEE_SAFETY_ENABLE == STD_ON)
            Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                                   FEE_SID_ERASEQUASISTATICDATA,
                                   FEE_E_INVALID_BLOCK_INSTANCES);
#endif
          }


        }
    /* [cover parentID={6AF8CD71-96CC-45b2-8317-6F6F2D9DEDF5}]
Safety error enabled
[/cover] */
#if(FEE_SAFETY_ENABLE == STD_ON)
        else
        {
        /* [cover parentID={F2CAB662-7CEC-49a4-8680-D9D98BCCBD0C}]
Report Error as FEE_E_INVALID_BLOCK_NO
[/cover] */
          Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                                 FEE_SID_ERASEQUASISTATICDATA,
                                 FEE_E_INVALID_BLOCK_NO);
        }
#endif
      }
#if (FEE_SAFETY_ENABLE == STD_ON)
    /* [cover parentID={43E98CDF-05E2-4253-A47F-63B5DF7DA8D3}]
Check safety error
[/cover] */    
  else
      {
#if (FEE_DATA_BLOCK_SUPPORTED == FEE_QUASI_STATIC_DATA_ONLY)
  /* [cover parentID={8D8C4FEA-82DB-4be0-ABC3-A0ACF2D4360D}]
Report safety error as FEE_E_BUSY
[/cover] */
        Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                               FEE_SID_ERASEQUASISTATICDATA, FEE_E_BUSY);
#else
        if(StateDataPtr->FeePendReqStatus != FEE_PEND_PREV_NO_REQ )
        {
      /* [cover parentID={8DFE14B2-C30A-403b-A42B-8F6948446815}]
Report safety error FEE_E_BUSY
[/cover] */
          Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                                 FEE_SID_ERASEQUASISTATICDATA, FEE_E_BUSY);
        }
#endif
      }
#endif
    }
  }
  /* [cover parentID={F06CEEFC-7F1C-402d-938F-2C4DC6DC3B2F}]
Safety is enabled
[/cover] */
#if (FEE_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={719E219D-8499-4ddb-96FE-EF62A63F3C83}]
Report safety error as FEE_E_UNINIT
[/cover] */
    Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                           FEE_SID_ERASEQUASISTATICDATA, FEE_E_UNINIT);
  }
#endif
/* [cover parentID={40565740-7EE4-4c46-97D3-2B98D709C215}]
Return
[/cover] */
  return(RetVal);
}

/*******************************************************************************
** TRACEABILITY: [cover parentID={003CA79B-BA5C-442a-B315-3DAED23EC898}]      **
**                                                                            **
** Syntax : MemIf_JobResultType Fee_17_GetQuasiStaticJobResult(void)          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x27                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  MemIf_JobResultType                                     **
**                                                                            **
** Description : Service to query the result of the last accepted job issued  **
** by QS Manager                                                              **
**                                                                            **
*******************************************************************************/
/* [cover parentID={AAD5F634-CB70-4b60-996F-D6DD5CFC274C}]
Fee_17_GetQuasiStaticJobResult
[/cover] */
MemIf_JobResultType Fee_17_GetQuasiStaticJobResult(void)
{
  
  const Fee_StateDataType  *StateDataPtr;
  MemIf_JobResultType ReturnValue;
/* [cover parentID={0BA4CE80-3F48-4ea2-9D52-80DF2A5A07C1}]
Safety is enabled
[/cover] */
#if (FEE_SAFETY_ENABLE == STD_ON)
  /*Check Fee_CfgPtr is null if yes return E_not_ok . This done to avoid trap
  if fee_init is not called */
  if(Fee_CfgPtr != NULL_PTR)
#endif
  {

    StateDataPtr = Fee_CfgPtr->FeeStatePtr;
    ReturnValue = StateDataPtr->FeeQsJobResult;
     
  }
#if (FEE_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={C6EE60F6-34E1-42f7-BEF6-61683C73D0E4}]
Report safety error as FEE_E_UNINIT
[/cover] */
    Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                           FEE_SID_GETQUASISTATICJOBRESULT, FEE_E_UNINIT);
    ReturnValue = MEMIF_JOB_FAILED;
  }

#endif
  /* [cover parentID={9A9BED7E-067C-4da1-9F5A-3DB8151AA8A7}]
Return the quasi static job result
[/cover] */
  return(ReturnValue);
  /* [cover parentID={D2BEC781-8CBC-4464-BD83-25999ADC4808}]
Return
[/cover] */

}/*End of Fee_17_GetQuasiStaticJobResult */

/*******************************************************************************
** TRACEABILITY: [cover parentID={9CE9B6A6-08CB-48c3-91C3-1E6C24970EAC}]      **
**                                                                            **
** Syntax : MemIf_JobResultType Fee_17_GetQuasiStaticBlockInfo(               **
**          const uint16 BlockNumber,                                         **
**          Fee_QuasiStaticBlockInfoType * const BlockInfoPtr)                **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x26                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockNumber : Logical block number                      **
**                                                                            **
** Parameters (out):  BlockInfoPtr : constant pointer to BlockInfo structure  **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                    E_OK : QS block info was read successfully              **
**                    E_NOT_OK : QS block info not available                  **
**                                                                            **
** Description : Service to read the Block State and the Block Cycle Counter  **
** of the given quasi-static data block instance.                             **
**                                                                            **
*******************************************************************************/
/* [cover parentID={C92C92E6-B01A-47ef-BD7D-BA7E974C2FD9}]
Fee_17_GetQuasiStaticBlockInfo
[/cover] */
Std_ReturnType Fee_17_GetQuasiStaticBlockInfo(const uint16 BlockNumber,
    Fee_QuasiStaticBlockInfoType * const BlockInfoPtr)
{
  /* [cover parentID={C92C92E6-B01A-47ef-BD7D-BA7E974C2FD9}]*/
  const Fee_StateDataType  *StateDataPtr;
  uint32              BlkAddress;
  Std_ReturnType      ReadStat;
  uint32              BccBuffer[2];
  uint16              Bcc;
  uint16              BlockIndex;
  uint16              BccComp;
  Std_ReturnType      RetVal;


  RetVal = E_NOT_OK;
  ReadStat = E_OK;
  Bcc = FEE_RESET;

  /* [cover parentID={296AAE10-EE87-4580-BAA6-A3B234EC4342}]
Safety is enabled
[/cover] */
#if (FEE_SAFETY_ENABLE == STD_ON)
   /* [cover parentID={33C7D674-911A-4fbb-901E-B69EF510837C}]
Check det error
[/cover] */
  /*Check Fee_CfgPtr is null if yes return E_not_ok . This done to avoid trap
  if fee_init is not called */
  if((Fee_CfgPtr != NULL_PTR) && (BlockInfoPtr != NULL_PTR ))
#endif
  {
    StateDataPtr = Fee_CfgPtr->FeeStatePtr;

    if((StateDataPtr->FeeInitQSState == FEE_INITQS_COMPLETE)  &&
        ( StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_NO_REQ ))
    {
     /* [cover parentID={91B0DB6B-5BAB-45c7-A448-AA7998BF85F2}]
Get the block index of the requested quasi block
[/cover] */
      /* Get index of the block info stored in cache */
      BlockIndex = Fee_lGetUsrBlockIndex(BlockNumber);
     /* [cover parentID={C1FB5201-9E3C-4ee8-B4AD-F0A15C742A41}]
If the block is found and it is a QS block?
[/cover] */
      /*Accept the request only for QS block*/
      if((BlockIndex != FEE_LOG_BLOCK_NOT_FOUND) &&
          (Fee_CfgPtr->FeeBlockConfigPtr[BlockIndex].FeeUser ==
           (uint8)FEE_QUASI_STATIC_USER))
      {
      /* [cover parentID={03607BAC-F3D3-44a2-A037-4F1E06365A07}]
Make a local copy of block address
Update Cache Status state
[/cover] */
        BlkAddress = StateDataPtr->FeeBlockInfo[BlockIndex].Address;
        BlockInfoPtr->State = 
        StateDataPtr->FeeBlockInfo[BlockIndex].Status.State;

        /*Check if the block state is FEE_QS_WRITE_COMPLETE if yes then read the 
        BCC value from block , otherwise return BCC as 0 */
        if(BlockInfoPtr->State == FEE_QS_WRITE_COMPLETE)
        {
          BlkAddress += FEE_QS_STATE_CYCLE_COUNT_OFFSET;
          ReadStat = Fls_17_Dmu_ReadWordsSync(
                          (Fls_17_Dmu_AddressType)BlkAddress,
                          /*MISRA2012_RULE_1_3_JUSTIFICATION:This rule violation
                          is agreed as we need to store the address passed is in
                          the called function in many scenarios.*/
                          (uint32 *)BccBuffer,
                          (FEE_DFLASH_PAGE_SIZE / FEE_DFLASH_WORD_SIZE));

          if(ReadStat == E_OK)
          {
            Bcc = (uint16)(BccBuffer[0] & FEE_16_BIT_ALL_ONES);
            BccComp = (uint16)((BccBuffer[0] >> 16) & FEE_16_BIT_ALL_ONES);

            if(BccComp != (~Bcc & FEE_16_BIT_ALL_ONES))
            {
              Bcc = FEE_RESET;
            }
          }

        }
    /* [cover parentID={EEBCD590-E211-40d0-8470-7BBF5C94D55A}]
Set flag as E_OK
[/cover] */
        RetVal = E_OK;
        BlockInfoPtr->Bcc = Bcc;
    /* [cover parentID={84022884-66C0-4364-947A-9AA24DDED927}]
Check for ECC error
[/cover] */
        /*Check if FLS returns E_NOT_OK due to ECC error*/
        if(ReadStat == E_NOT_OK)
        {
          /* [cover parentID={7D8259E7-347D-437b-A75F-6F09AD98B67F}]
Set flag as E_NOT_OK
[/cover] */
      RetVal = E_NOT_OK;
        }
      }
#if (FEE_SAFETY_ENABLE == STD_ON)
      else
      {
        /* [cover parentID={466FD2BA-81EE-4f43-8BAF-D8E78D7B642E}]
Report safety error as FEE_E_INVALID_BLOCK_NO
[/cover] */
        Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                               FEE_SID_GETQUASISTATICBLOCKINFO,
                               FEE_E_INVALID_BLOCK_NO);
      }

#endif

    }
  /* [cover parentID={301B7C86-C443-415b-A3D7-61557C698A08}]
Safety is enabled
[/cover] */
#if (FEE_SAFETY_ENABLE == STD_ON)
    else
    {
      if(StateDataPtr->FeePendReqStatus != FEE_PEND_PREV_NO_REQ)
      {
      /* [cover parentID={4CE036EC-ABC7-4c19-AC85-79C8DF8E4C50}]
Report error FEE_E_BUSY
[/cover] */
        Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                               FEE_SID_GETQUASISTATICBLOCKINFO, FEE_E_BUSY);
      }
    }

#endif

  }
  /* [cover parentID={F9339422-88E3-4ff0-A521-1B07D811FC03}]
Safety is enabled
[/cover] */
#if (FEE_SAFETY_ENABLE == STD_ON)
  else
  {

    if(Fee_CfgPtr == NULL_PTR)
    {
     /* [cover parentID={EAF57C11-B041-471d-A505-EE70B441077D}]
Report safety error as FEE_E_UNINIT
[/cover] */
      Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                             FEE_SID_GETQUASISTATICBLOCKINFO, FEE_E_UNINIT);
    }
    else
    {
     /* [cover parentID={20CB4689-C944-4dee-923B-34A4586DC950}]
Report safety error as FEE_E_PARAM_POINTER
[/cover] */
      Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                             FEE_SID_GETQUASISTATICBLOCKINFO,
                             FEE_E_PARAM_POINTER);
    }

    RetVal = E_NOT_OK;
  }
#endif
/* [cover parentID={5C0A2BB8-3CA9-45a1-8A1F-6FC37B34FEB9}]
Return
[/cover] */
  return(RetVal);

}/*End of Fee_17_GetQuasiStaticBlockInfo */

/*******************************************************************************
** Syntax : static void Fee_lQsErase(void)                                    **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function Performs various state transition handling     **
** during QS Block erase operation                                            **
*******************************************************************************/
/* [cover parentID={DBDCD90B-D850-47cd-9774-802FFDF31256}]
Fee_lQsErase
[/cover] */
static void Fee_lQsErase(void)
{
  uint16                UserBlockIndex;
  uint16        BlockInstances;
  Fee_StateDataType  *StateDataPtr;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  UserBlockIndex = StateDataPtr->FeePendEraseInfo.CacheIndex;

  /* [cover parentID={089BD1C3-CB3E-4fe3-A592-9C5B14AC8786}]
Has QS erase started?
[/cover] */
  if(StateDataPtr->FeeQsState == (uint8)FEE_QS_START_ERASE)
  {
    Fee_lQsBlockErase();

    StateDataPtr->FeeQuasiBlkInstanceTemp = FEE_RESET;
    /* set the cache state to erase started */
  }
  else if(StateDataPtr->FeeQsState == (uint8)FEE_QS_ERASE_COMPLETE)
  {
    StateDataPtr->FeeQuasiBlkInstanceTemp = FEE_RESET;
    BlockInstances = StateDataPtr->FeePendEraseInfo.BlockInstances;
    /* set the cache state to erase completed */
    /*MISRA2012_RULE_10_4_JUSTIFICATION:Types are same. It is unsigned int*/
    while(BlockInstances != 0)
    {
      StateDataPtr->FeeBlockInfo[UserBlockIndex].Status.State =
        FEE_QS_ERASE_COMPLETE;
      BlockInstances--;
      UserBlockIndex++;
    }
    StateDataPtr->FeePendEraseInfo.BlockInstances = FEE_RESET;
    Fee_lHandleQsJobSuccess();
  }
  else
  {
    Fee_lQsProgState();
  }
}/*End of Fee_lQsErase */

#if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
/*******************************************************************************
** Syntax : static void Fee_lQsResumeErase(void)                              **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function resumes the previous erase operation which was **
** suspended due to another Read/Write User job                               **
*******************************************************************************/
static void Fee_lQsResumeErase(void)
{
  Fee_StateDataType  *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  if(E_OK == Fls_17_Dmu_ResumeErase())
  {
    StateDataPtr->FeeQsEraseSuspend = FEE_ERASE_NOT_SUSPENDED;
    StateDataPtr->FeeQsState = (uint8)FEE_QS_PROG_STATE_ERASE_COMPLETE;
    StateDataPtr->FeeQsJobStatus = FEE_JOB_REQSTD;
    StateDataPtr->FeeQsJob = FEE_ERASE_JOB;
    StateDataPtr->FeeQsJobResult = MEMIF_JOB_PENDING;
    StateDataPtr->FeePendReqStatus = FEE_REQ_QUASI_ERASE;

  }
  else
  {
    /* Raise the job error and illegal notification*/
    
    Fee_lHandleQsJobFailure((~FEE_CANCEL));
    if(Fee_CfgPtr->FeeQsIllegalStateNotification != NULL_PTR)
    {
        Fee_CfgPtr->FeeQsIllegalStateNotification();
    }

  }
}/*End of Fee_lQsResumeErase */
#endif
/*******************************************************************************
** Syntax : static void Fee_lRegisterQsRead(const uint16 BlockNumber,         **
** const uint16 BlockOffset, uint8 *const DataBufferPtr, const uint16 Length) **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockNumber : Logical block numberNone                  **
**                    BlockOffset : Read address offset within the block      **
**                    Length      : Number of bytes to be read                **
**                    DataBufferPtr : pointer to data buffer where the qs     **
**                                    block data in Dflash will be updated    **
** Parameters (out):  DataBufferPtr : None                                    **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                    E_OK : Request is registered.                           **
**                    E_NOT_OK : Request is not registered. FEE module is busy**
**                     in servicing other request.                            **
** Description : This function will register the QS read request in the       **
** pending request buffer if FEE is Idle or QS Erase is ongoing and erase     **
** suspend enabled                                                            **
*******************************************************************************/
/* [cover parentID={1E4145B5-4D70-49de-B122-D8AB268DAD76},
{A8409AA6-4B75-47f3-82BA-1756DBF2FB5B}]
Fee_lRegisterQsRead
[/cover] */
static Std_ReturnType Fee_lRegisterQsRead( const uint16 BlockNumber,
    const uint16 BlockOffset, uint8 * const DataBufferPtr, const uint16 Length)
{
  Fee_StateDataType  *StateDataPtr;
  Std_ReturnType RetVal;
  MemIf_StatusType   ReturnStatus;
  Fee_PendReqBufType   *PendReqPtr;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  PendReqPtr = &(StateDataPtr->FeePendReqInfo);




#if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)

  /* check whether quasi erase job is ongoing */

  if((StateDataPtr->FeeQsState == (uint8)FEE_QS_PROG_STATE_ERASE_COMPLETE) &&
      (StateDataPtr->FeeQsJobStatus == FEE_JOB_REQSTD))
  {  
  /* [cover parentID={AFAF3581-1296-4dfa-A9C2-109D92694AE7}]
Initiate suspend erase and update flag status
[/cover] */
    /* erase is ongoing and can be suspended */
    RetVal = Fls_17_Dmu_SuspendErase();
    if(RetVal == E_OK)
    {
      StateDataPtr->FeeQsEraseSuspend = FEE_ERASE_SUSPENDED;
      StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
    }
  }
  
  else if(StateDataPtr->FeeQsEraseSuspend == FEE_ERASE_SUSPENDED)
  {
    RetVal =  E_OK;
    StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
  }
  else
#endif
  {
    /* [cover parentID={B16224CA-4556-4831-9F2C-0C75397128F7}]
Check FEE driver status
[/cover] */
    /* check the Fee Driver status */
    ReturnStatus = Fee_lGetStatus();
    /* [cover parentID={A280A970-50B9-4fa9-B2D2-BB5AE5A9C9B4}]
Is the driver busy?
[/cover] */
    /* As per new request read should be accepted for MEMIF_BUSY_INTERNAL */
    if(ReturnStatus == MEMIF_BUSY)
    {
      /* [cover parentID={9D93D99A-D25E-4f2b-BD80-09B18D88B192}]
Set Flag as NOT OK
[/cover] */
      RetVal = E_NOT_OK;
    /* [cover parentID={459EF6D6-2BC5-4b0e-A9A0-70846B9354CD}]
DET or Safety enabled
[/cover] */
#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
      Fee_lReportError(FEE_SID_READ, FEE_E_BUSY);
#endif
    }
    else
    {
      /* [cover parentID={763A9DFF-B6D9-4c82-9D76-AE6D7E6E8045}]
Set Flag as OK
[/cover] */
      RetVal = E_OK;
    }
  }
  if(RetVal == E_OK)
  {
    /* [cover parentID={04623D01-D44E-43c8-B774-DF745FF3D1E7}]
Store the read request parameters in the Pending buffer structure
Update QS job as read job and job result as MEMIF_JOB_PENDING
[/cover] */
    /* Store the read request parameters in the Pending buffer structure */
    PendReqPtr->BlockNumber = BlockNumber;
    PendReqPtr->BlockOffset = BlockOffset;
    PendReqPtr->DataBufferPtr = DataBufferPtr;
    PendReqPtr->Length = Length;

    StateDataPtr->FeePendReqStatus = FEE_REQ_QUASI_READ;
    StateDataPtr->FeeQsJobResult = MEMIF_JOB_PENDING;
    StateDataPtr->FeeQsJob = FEE_READ_JOB;
    StateDataPtr->FeeCurrReqBlockNum = BlockNumber;

    /* Set this flag to start GC and cache update process before serving write
       request.This will insure proper write operation in case GC is disabled
       during FEE initialization */
    StateDataPtr->FeeStatusFlags.FeeStartInitGC = FEE_SET ;
  }
  /* [cover parentID={A2ACCDE5-7C17-4956-9768-481F8D5BA8B4}]
Return Flag status
[/cover] */
  return(RetVal);
  /* [cover parentID={66C90A49-B70B-45e0-A449-F0345D62201C}]
Return
[/cover] */
}/*End of Fee_lRegisterQsRead */

/*******************************************************************************
** Syntax : static void Fee_lQsRead(void)                                     **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function Triggers QS Block Data read on D-Flash as per  **
** Block details in pending Request buffer                                    **
*******************************************************************************/
/* [cover parentID={F130D237-0765-4aad-A128-2C2018AA1647}]
Fee_lQsRead
[/cover] */
static void Fee_lQsRead(void)
{
  Fee_StateDataType    *StateDataPtr;
  const Fee_BlockType  *PendReqBlkPtr;
  uint32                SrcAddress;
  uint16                PendReqBlkNum;
  uint16                PendReqBlkIndex;
  uint16        Length;
  Std_ReturnType        RetVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  Length = StateDataPtr->FeePendReqInfo.Length;
  PendReqBlkNum = StateDataPtr->FeePendReqInfo.BlockNumber;

  if(Length > ((uint16)0))
  {
    PendReqBlkIndex = Fee_lGetUsrBlockIndex(PendReqBlkNum);
    PendReqBlkPtr = &(Fee_CfgPtr->FeeBlockConfigPtr[PendReqBlkIndex]);
    SrcAddress = PendReqBlkPtr->Address;
    /* [cover parentID={8B308AEE-F808-4f1c-B189-863340AC1B16}]
Update the source address by accessing the address of the block required and adding QS data offset to it(36 bytes)
[/cover] */
    /* point it to right offset location */
    /*MISRA2012_RULE_10_4_JUSTIFICATION:Types are same. It is unsigned int*/
    SrcAddress += StateDataPtr->FeePendReqInfo.BlockOffset + FEE_QS_DATA_OFFSET;

    RetVal = Fls_17_Dmu_Read((Fls_17_Dmu_AddressType)SrcAddress,
                             StateDataPtr->FeePendReqInfo.DataBufferPtr,
                             (Fls_17_Dmu_LengthType)StateDataPtr->FeePendReqInfo.Length);

    if(RetVal == E_OK)
    {
      StateDataPtr->FeeQsState = FEE_REQ_QUASI_READ;
      StateDataPtr->FeeQsJobStatus = FEE_JOB_REQSTD;
    }
    else
    {
      /* Call the Fee_lHandleQsJobFailure with  (~FEE_CANCEL) to notify
        user about failed of job*/
      Fee_lHandleQsJobFailure((~FEE_CANCEL));
    }
  }
  /*Reset the status if length is zero*/
  else
  {
    
    Fee_lHandleQsJobSuccess();

  }
}/*End of Fee_lQsRead */

/*******************************************************************************
** Syntax : static void Fee_lRegisterQsWrite(                                 **
**                               const uint8 * const DataWriteBufferPtr,      **
**                               const Fee_BlockType * const BlockPtr)        **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockPtr    : Pointer to block configuration            **
**                 :  DataWriteBufferPtr : pointer to data buffer             **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                    E_OK : Request is registered.                           **
**                    E_NOT_OK : Request is not registered. FEE module is busy**
**                     in servicing other request.                            **
** Description : This function will register the QS write request in the      **
** pending request buffer if FEE is Idle or QS Erase is ongoing and erase     **
** suspend is enabled                                                         **
*******************************************************************************/
/* [cover parentID={EA51FD4F-7011-4d3c-BDE6-69A23D11E8D0},
                     {64B68921-2DA4-4e1e-A7DC-5947FA87E4C7}]
Fee_lRegisterQsWrite
[/cover] */
static Std_ReturnType Fee_lRegisterQsWrite( \
    const uint8 * const DataWriteBufferPtr, \
    const Fee_BlockType * const BlockPtr)
{
  Fee_StateDataType  *StateDataPtr;
  Std_ReturnType      RetVal;
  MemIf_StatusType    ReturnStatus;
  Fee_PendReqBufType  *PendReqPtr;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  PendReqPtr = &(StateDataPtr->FeePendReqInfo);

#if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)

  if((StateDataPtr->FeeQsState == (uint8)FEE_QS_PROG_STATE_ERASE_COMPLETE) &&
      (StateDataPtr->FeeQsJobStatus == FEE_JOB_REQSTD))
  { 
  /* [cover parentID={F8D319B0-90A3-4f96-968B-EA48DF7EC5CE}]
Initiate suspend erase and update flag status
[/cover] */
    RetVal = Fls_17_Dmu_SuspendErase();
    if(RetVal == E_OK)
    {
      StateDataPtr->FeeQsEraseSuspend = FEE_ERASE_SUSPENDED;
      StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
    }
  }
  
  else if(StateDataPtr->FeeQsEraseSuspend == FEE_ERASE_SUSPENDED)
  {
    RetVal =  E_OK;
    StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
  }
  else
#endif
  {
    /* [cover parentID={47EC0F19-3082-46ca-AF45-9400AEDE4752}]
Get Fee job status
[/cover] */
    ReturnStatus = Fee_lGetStatus();

    /*Check if module is busy with NVM request. if not accept job else reject
    job */

    if(ReturnStatus == MEMIF_BUSY)
    {
      /* [cover parentID={3869D8A5-6BEF-45b8-9C1E-FFC51AE85BE0}]
      Update Flag status as E_NOT_OK
      [/cover] */
    /* [cover parentID={D8F77F0F-8A00-497a-AE2F-F167B87F5FD9}]
DET or Safety enabled
[/cover] */
#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
      Fee_lReportError(FEE_SID_WRITE, FEE_E_BUSY);
#endif
/* [cover parentID={3869D8A5-6BEF-45b8-9C1E-FFC51AE85BE0}]
Update Flag status as E_NOT_OK
[/cover] */
      RetVal = E_NOT_OK;
    }
    else
    {
      /* [cover parentID={A2A1E98F-3B35-43d1-BA0A-0AA02CFB2CBA}]
Update Flag status as E_OK
[/cover] */
      RetVal = E_OK;
    }
  }
  if(RetVal == E_OK)
  {
    /* [cover parentID={288C8F43-5267-4d50-A935-106DD5EFE509}]
Store the read request parameters in the pending buffer structure
Set QsJobResult to MEMIF_JOB_PENDING
Set Pending request status as FEE_REQ_QUASI_WRITE
Set QsJob as FEE_WRITE_JOB
Set QsState as FEE_QS_PROG_STATE_WRITE_STARTED
[/cover] */
    /* Store the read request parameters in the Pending buffer structure */
    PendReqPtr->BlockNumber = BlockPtr->BlockNumber;
    PendReqPtr->DataWriteBufferPtr = DataWriteBufferPtr;
    PendReqPtr->Length = BlockPtr->Size;
    StateDataPtr->FeePendReqStatus = FEE_REQ_QUASI_WRITE;
    StateDataPtr->FeeQsJobResult = MEMIF_JOB_PENDING;
    StateDataPtr->FeeQsJob = FEE_WRITE_JOB;
    StateDataPtr->FeeQsState = (uint8)FEE_QS_PROG_STATE_WRITE_STARTED;
    StateDataPtr->FeeCurrReqBlockNum = BlockPtr->BlockNumber;

    /* Set this flag to start GC and cache update process before serving write
       request.This will insure proper write operation in case GC is disabled
       during FEE initialization */
    StateDataPtr->FeeStatusFlags.FeeStartInitGC = FEE_SET ;
  }
  /* [cover parentID={565EC67C-EC86-415f-8FCA-BEA8EDD945A6}]
Return Flag status
[/cover] */
  return(RetVal);
  /* [cover parentID={7FAEC9EB-835A-4aae-83AC-B22032F0BD02}]
Return
[/cover] */
}/*End of Fee_lRegisterQsWrite */

/*******************************************************************************
** Syntax : static void Fee_lQsWrite(void)                                    **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function Performs various state transition handling     **
** during QS Block write operation                                            **
*******************************************************************************/
/* [cover parentID={243E4334-3CBC-489d-BA93-F61DE6961841}]
Fee_lQsWrite
[/cover] */
static void Fee_lQsWrite(void)
{
  Fee_StateDataType  *StateDataPtr;
  uint16                UserBlockIndex;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  UserBlockIndex = StateDataPtr->FeePendReqInfo.CacheIndex;
  switch(StateDataPtr->FeeQsState)
  {

    case (uint8)FEE_QS_START_BCC_WRITE:
      {
        /* set the cache state to write started */
        StateDataPtr->FeeBlockInfo[UserBlockIndex].Status.State =
          FEE_QS_WRITE_STARTED;
        Fee_lQsBccWrite();
        break;
      }

    case (uint8)FEE_QS_START_BLOCK_WRITE:
      {
        Fee_lQsBlockWrite();
        break;
      }

    case (uint8)FEE_QS_WRITE_COMPLETE:
      {
        /* set the cache state to write complete */
        StateDataPtr->FeeBlockInfo[UserBlockIndex].Status.State =
          FEE_QS_WRITE_COMPLETE;
        Fee_lHandleQsJobSuccess();
        break;
      }
    default:
      {
        Fee_lQsProgState();
        break;
      }
  }
}/*End of Fee_lQsWrite */

/*******************************************************************************
** Syntax : static void Fee_lQsBccWrite(void)                                 **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function Performs QS Block BCC write operation          **
*******************************************************************************/
static void Fee_lQsBccWrite(void)
{
  uint32                DestAddr;
  const uint32*         SrcPtr;
  Fee_StateDataType    *StateDataPtr;
  const Fee_BlockType  *PendReqBlkPtr;
  Std_ReturnType        RetVal;
  uint32                Bcc;
  uint32                BccComp;
  uint16                PendReqBlkNum;
  uint16                PendReqBlkIndex;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  PendReqBlkNum = StateDataPtr->FeePendReqInfo.BlockNumber;
  PendReqBlkIndex = Fee_lGetUsrBlockIndex(PendReqBlkNum);
  PendReqBlkPtr = &(Fee_CfgPtr->FeeBlockConfigPtr[PendReqBlkIndex]);
  Bcc = (uint32)Fee_lQsGetBcc(PendReqBlkIndex);
  /* Bcc += FEE_ONE; */
  BccComp = ~Bcc;
  BccComp &= BccComp;

  StateDataPtr->FeeTempArray[0] = (BccComp << FEE_SIXTEEN);
  StateDataPtr->FeeTempArray[0] |= (Bcc);

  StateDataPtr->FeeTempArray[1] =
    /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer*/
    /*MISRA2012_RULE_11_8_JUSTIFICATION:Agreed Violation.
    solvable but gives compiler warnings buffer*/
    *(uint32*)(StateDataPtr->FeePendReqInfo.DataWriteBufferPtr);
  /* [cover parentID={EEC90E79-187D-446e-8FE9-1A46DD94F90F}]
Set Write address to BCC page of block
[/cover] */
  DestAddr = PendReqBlkPtr->Address + (FEE_QS_STATE_CYCLE_COUNT_OFFSET);
  SrcPtr = StateDataPtr->FeeTempArray;
  /* [cover parentID={3E07EA18-F991-4f55-969F-5F6A77C38AA6}]
Initiate FLS write
[/cover] */
  /*MISRA2012_RULE_11_8_JUSTIFICATION:Agreed Violation.
  solvable but gives compiler warnings buffer*/
  RetVal = Fls_17_Dmu_Write(DestAddr, (uint8*)SrcPtr,
                            (Fls_17_Dmu_LengthType)FEE_DFLASH_PAGE_SIZE);

  if( RetVal == E_OK)
  {
    StateDataPtr->FeeQsState = (uint8)FEE_QS_START_BLOCK_WRITE;
    StateDataPtr->FeeQsJobStatus = (uint8)FEE_JOB_REQSTD;
  }
  else
  {
    /* Call the Fee_lHandleQsJobFailure with  (~FEE_CANCEL) to notify
    user about failed of job*/

    Fee_lHandleQsJobFailure((~FEE_CANCEL));
  }
}/*End of Fee_lQsBccWrite */

/*******************************************************************************
** Syntax : static Uint16 Fee_lQsGetBcc(const uint16 Blkindex)                **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  Blkindex    : Block index in configuration table        **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  BCC value which is highest among all the instances      **
** of the QS Block                                                            **
**                                                                            **
** Description : This function will Calculates the highest bcc value among    **
** the written QS Block instances and returns the value to the caller         **
*******************************************************************************/
/* [cover parentID={91987F5F-298F-4670-A378-51F55A1D71A9}]
Fee_lQsGetBcc
[/cover] */
static uint16 Fee_lQsGetBcc(const uint16 Blkindex)
{
  Fee_StateDataType    *StateDataPtr;
  uint32                SrcAddr;
  Fee_CacheType  *CachePtr;
  Fee_CacheType  *TempCachePtr;
  const Fee_BlockType  *BlkPtr;
  const Fee_BlockType  *TempBlkptr;
  Std_ReturnType        ReturnValue;
  uint16                Instances;
  uint16                Bcc;
  uint16                TempBcc;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /*MISRA2012_RULE_18_1_JUSTIFICATION: Pointer arithmetic other than
        array indexing used for FEE application buffers.
        Pointers are accessing the correct memory range locations.
        The access range is within the boundaries of the buffer. */
  CachePtr = &(StateDataPtr->FeeBlockInfo[Blkindex]);
  TempCachePtr = CachePtr;
  TempBlkptr = &(Fee_CfgPtr->FeeBlockConfigPtr[FEE_QSBLOCK_BEGIN_INDEX]);
  BlkPtr = &(TempBlkptr[(Blkindex - FEE_QSBLOCK_BEGIN_INDEX)]);
  Instances = BlkPtr->Instances;

  while((Instances == FEE_RESET) && (BlkPtr != TempBlkptr))
  {
    BlkPtr--;
    CachePtr--;
    Instances = BlkPtr->Instances;
  }

  Bcc = FEE_RESET;

  /* Block with 1 instance */
 
   /*MISRA2012_RULE_18_1_JUSTIFICATION: Pointer arithmetic other than array 
   indexing used for FEE application buffers.Pointers are accessing the correct
   memory range locations.The access range is within the boundaries of the 
   buffer. */
  if((Instances == FEE_ONE) && \
     (CachePtr->Status.State == FEE_QS_WRITE_STARTED))
  {
    /*MISRA2012_RULE_18_1_JUSTIFICATION: Pointer arithmetic other than
          array indexing used for FEE application buffers.
          Pointers are accessing the correct memory range locations.
          The access range is within the boundaries of the buffer. */
    CachePtr->Blkcylcnt++;
    /*MISRA2012_RULE_18_1_JUSTIFICATION: Pointer arithmetic other than
          array indexing used for FEE application buffers.
          Pointers are accessing the correct memory range locations.
          The access range is within the boundaries of the buffer. */
    Bcc = CachePtr->Blkcylcnt;
  }
  else
  {
    /* Block with more than 1 instance */

    while(Instances != FEE_RESET)
    {
      /*MISRA2012_RULE_18_1_JUSTIFICATION: Pointer arithmetic other than
            array indexing used for FEE application buffers.
            Pointers are accessing the correct memory range locations.
            The access range is within the boundaries of the buffer. */
      if(CachePtr->Status.State == FEE_QS_WRITE_STARTED)
      {
        TempCachePtr = CachePtr;
      }
      /*MISRA2012_RULE_18_1_JUSTIFICATION: Pointer arithmetic other than
            array indexing used for FEE application buffers.
            Pointers are accessing the correct memory range locations.
            The access range is within the boundaries of the buffer. */
      if(CachePtr->Blkcylcnt > Bcc)
      {
        /*MISRA2012_RULE_18_1_JUSTIFICATION: Pointer arithmetic other than
              array indexing used for FEE application buffers.
              Pointers are accessing the correct memory range locations.
              The access range is within the boundaries of the buffer. */
        Bcc = CachePtr->Blkcylcnt;
      }
      
      /*MISRA2012_RULE_18_1_JUSTIFICATION: Pointer arithmetic other than
            array indexing used for FEE application buffers.
            Pointers are accessing the correct memory range locations.
            The access range is within the boundaries of the buffer. */
      if(CachePtr->Status.State == FEE_QS_WRITE_COMPLETE)
      {
        SrcAddr = BlkPtr->Address + (FEE_QS_STATE_CYCLE_COUNT_OFFSET);

        ReturnValue = Fls_17_Dmu_ReadWordsSync(
                        (Fls_17_Dmu_AddressType)SrcAddr,
                        (uint32 *)StateDataPtr->FeeTempArray,
                        (Fls_17_Dmu_LengthType)
                        (FEE_DFLASH_PAGE_SIZE/FEE_DFLASH_WORD_SIZE));

        if(ReturnValue == E_OK)
        {
          TempBcc = (uint16)(StateDataPtr->FeeTempArray[0] 
                             & FEE_16_BIT_ALL_ONES);
          if(TempBcc > Bcc)
          {
            Bcc = TempBcc;
            /*MISRA2012_RULE_18_1_JUSTIFICATION: Pointer arithmetic other than
                  array indexing used for FEE application buffers.
                  Pointers are accessing the correct memory range locations.
                  The access range is within the boundaries of the buffer. */
            CachePtr->Blkcylcnt = TempBcc;
          }
        }

      }
      /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
            array indexing used for FEE application buffers.
            Pointers are accessing the correct memory range locations.
            The access range is within the boundaries of the buffer. */
      /*MISRA2012_RULE_18_1_JUSTIFICATION: Pointer arithmetic other than
            array indexing used for FEE application buffers.
            Pointers are accessing the correct memory range locations.
            The access range is within the boundaries of the buffer. */
      BlkPtr += FEE_ONE;
      /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
            array indexing used for FEE application buffers.
            Pointers are accessing the correct memory range locations.
            The access range is within the boundaries of the buffer. */
      /*MISRA2012_RULE_18_1_JUSTIFICATION: Pointer arithmetic other than
            array indexing used for FEE application buffers.
            Pointers are accessing the correct memory range locations.
            The access range is within the boundaries of the buffer. */
      CachePtr += FEE_ONE;
      Instances--;
    };
    
    Bcc++;
    /*MISRA2012_RULE_18_1_JUSTIFICATION: Pointer arithmetic other than
          array indexing used for FEE application buffers.
          Pointers are accessing the correct memory range locations.
          The access range is within the boundaries of the buffer. */
    TempCachePtr->Blkcylcnt = Bcc;
  }

  if(Bcc >= FEE_MAX_BCC_QS)
  {
    Bcc = FEE_MAX_BCC_QS;
  }
  return(Bcc);
}/*End of Fee_lQsGetBcc */

/*******************************************************************************
** Syntax : static void Fee_lQsProgState(void)                                **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function Triggers programming of QS Block state         **
** information on D-Flash as per FeeQsState Global Variable                   **
*******************************************************************************/
/* [cover parentID={97D8B4FE-A233-48ab-956D-F8505B433CBB}]
Fee_lQsProgState
[/cover] */
static void Fee_lQsProgState(void)
{
  Fee_StateDataType    *StateDataPtr;
  const Fee_BlockType  *TempBlkptr;
  uint32                DestAddr;
  uint32               *SrcAddr;
  uint16                BlkIndex;
  uint32                BlkSize;
  Fls_17_Dmu_LengthType        DataLength;
  Std_ReturnType        RetVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  if(StateDataPtr->FeePendReqStatus == FEE_REQ_QUASI_ERASE)
  {
    BlkIndex = StateDataPtr->FeePendEraseInfo.CacheIndex;
  }
  else
  {
    BlkIndex = StateDataPtr->FeePendReqInfo.CacheIndex;
  }
  
  TempBlkptr = &(Fee_CfgPtr->FeeBlockConfigPtr[BlkIndex]);
  BlkSize = TempBlkptr->Size;
  DestAddr = TempBlkptr->Address +

             (StateDataPtr->FeeQuasiBlkInstanceTemp * BlkSize);
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array
    buffer*/
  SrcAddr = (uint32 *)(StateDataPtr->FeeReadWriteBuffer);
  DataLength = FEE_DFLASH_PAGE_SIZE;

  switch(StateDataPtr->FeeQsState)
  {

    case (uint8)FEE_QS_PROG_STATE_ERASE_STARTED:
      {
        DestAddr += FEE_QS_STATE_ERASE_STARTED_OFFSET;
        *SrcAddr = FEE_QS_STATE_ERASE_STARTED_LSW;
         SrcAddr[1] = FEE_QS_STATE_ERASE_STARTED_MSW;
        StateDataPtr->FeeQsState = (uint8)FEE_QS_PROG_STATE_DESTROY;
        StateDataPtr->FeeBlockInfo[BlkIndex].Status.State =
          FEE_QS_ERASE_STARTED;
        break;
      }

    case (uint8)FEE_QS_PROG_STATE_DESTROY:
      {
        DataLength = FEE_DFLASH_PAGE_SIZE * FEE_THREE;
        StateDataPtr->FeeQuasiBlkInstanceTemp += FEE_ONE;
        *SrcAddr = FEE_QS_STATE_DESTROY;
        
        SrcAddr[1] = FEE_QS_STATE_DESTROY;
       
        SrcAddr[2] = FEE_QS_STATE_DESTROY;
        
        SrcAddr[3] = FEE_QS_STATE_DESTROY;
      
        SrcAddr[4] = FEE_QS_STATE_DESTROY;
     
        SrcAddr[5] = FEE_QS_STATE_DESTROY;
        if(StateDataPtr->FeeQuasiBlkInstanceTemp ==
            StateDataPtr->FeePendEraseInfo.BlockInstances)
        {
          StateDataPtr->FeeQsState = (uint8)FEE_QS_START_ERASE;
        }
        else
        {
          StateDataPtr->FeeQsState = (uint8)FEE_QS_PROG_STATE_ERASE_STARTED;
        }
        break;
      }

    case (uint8)FEE_QS_PROG_STATE_ERASE_COMPLETE:
      {
        *SrcAddr = FEE_QS_STATE_ERASE_COMPLETE_LSW;
         SrcAddr[FEE_ONE] = FEE_QS_STATE_ERASE_COMPLETE_MSW;
        StateDataPtr->FeeQuasiBlkInstanceTemp += FEE_ONE;

        if(StateDataPtr->FeeQuasiBlkInstanceTemp ==
            StateDataPtr->FeePendEraseInfo.BlockInstances)
        {
          StateDataPtr->FeeQsState = (uint8)FEE_QS_ERASE_COMPLETE;
        }
        break;
      }

    case (uint8)FEE_QS_PROG_STATE_WRITE_COMPLETE:
      {

        DestAddr += FEE_QS_STATE_WRITE_COMPLETED_OFFSET;
        *SrcAddr = FEE_QS_STATE_WRITE_COMPLETE_LSW;
        SrcAddr[FEE_ONE] = FEE_QS_STATE_WRITE_COMPLETE_MSW;
        StateDataPtr->FeeQsState = (uint8)FEE_QS_WRITE_COMPLETE;
        break;
      }

    case (uint8)FEE_QS_PROG_STATE_WRITE_STARTED:
      {
        DestAddr += FEE_QS_STATE_WRITE_STARTED_OFFSET;
        *SrcAddr = FEE_QS_STATE_WRITE_STARTED_LSW;
        SrcAddr[FEE_ONE] = FEE_QS_STATE_WRITE_STARTED_MSW;
        StateDataPtr->FeeQsState = (uint8)FEE_QS_START_BCC_WRITE;
        break;
      }
    default:
      {
        break;
      }
  }

  RetVal = Fls_17_Dmu_Write((Fls_17_Dmu_AddressType)DestAddr, (uint8 *)SrcAddr,
                            DataLength);

  if( RetVal == E_OK)
  {
    StateDataPtr->FeeQsJobStatus = FEE_JOB_REQSTD;
  }
  else
  {
    /* Call the Fee_lHandleQsJobFailure with  (~FEE_CANCEL) to notify
    user about failed of job*/
    Fee_lHandleQsJobFailure((~FEE_CANCEL));
  }
}/*End of Fee_lQsProgState */

/*******************************************************************************
** Syntax : static void Fee_lQsBlockErase(void)                               **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function Triggers Erase of QS Block on D-Flash as per   **
** Block details in pending Request buffer                                    **
*******************************************************************************/
/* [cover parentID={4E00F903-9413-4788-B3B8-2F8B449891C9}]
Fee_lQsBlockErase
[/cover] */
static void Fee_lQsBlockErase(void)
{
  Fee_StateDataType     *StateDataPtr;
  const Fee_BlockType   *TempBlkptr;
  uint32                 DestAddr;
  uint16                 BlkIndex;
  uint32                 BlkSize;
  Std_ReturnType         RetVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  BlkIndex = StateDataPtr->FeePendEraseInfo.CacheIndex;
  TempBlkptr = &(Fee_CfgPtr->FeeBlockConfigPtr[BlkIndex]);
  BlkSize = TempBlkptr->Size;
  BlkSize = BlkSize * (StateDataPtr->FeePendEraseInfo.BlockInstances);
  DestAddr = TempBlkptr->Address;

  /* erase logical sector */
  RetVal = Fls_17_Dmu_Erase(DestAddr, (Fls_17_Dmu_LengthType)BlkSize);

  if( RetVal == E_OK)
  {
    StateDataPtr->FeeQsJobStatus = FEE_JOB_REQSTD;
    StateDataPtr->FeeQsState = (uint8)FEE_QS_PROG_STATE_ERASE_COMPLETE;
  }
  else
  {
    /* Call the Fee_lHandleQsJobFailure with  (~FEE_CANCEL) to notify
    user about failed of job*/

    Fee_lHandleQsJobFailure((~FEE_CANCEL));
  }
}/*End of Fee_lQsBlockErase */

/*******************************************************************************
** Syntax : static void Fee_lQsBlockWrite(void)                               **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function Triggers write of QS Block on D-Flash as per   **
** Block details in pending Request buffer                                    **
*******************************************************************************/
static void Fee_lQsBlockWrite(void)
{
  Fee_StateDataType     *StateDataPtr;
  const Fee_BlockType   *TempBlkptr;
  uint32                 DestAddr;
  const uint32          *SrcAddr;
  uint16                 BlkIndex;
  uint16                 BlkSize;
  Std_ReturnType         RetVal;
  uint16                 PendReqBlkNum;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  PendReqBlkNum = StateDataPtr->FeePendReqInfo.BlockNumber;
  BlkIndex = Fee_lGetUsrBlockIndex(PendReqBlkNum);


  TempBlkptr = &(Fee_CfgPtr->FeeBlockConfigPtr[BlkIndex]);
  BlkSize = (uint16)TempBlkptr->Size;
  BlkSize = BlkSize - (uint16)(FEE_QS_DATA_OFFSET_SECOND_PAGE);
  DestAddr = TempBlkptr->Address + (FEE_QS_DATA_OFFSET_SECOND_PAGE);
  /* [cover parentID={3E900673-9AA8-4412-9E35-9059BC781487}]
Set writing address to starting data page of block
[/cover] */
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is done for array buffer
  */
  /*MISRA2012_RULE_11_8_JUSTIFICATION:Agreed Violation.Solvable but
  gives compiler warnings.*/
  SrcAddr = (uint32 *)StateDataPtr->FeePendReqInfo.DataWriteBufferPtr;
  /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than array
  indexing used for FEE application buffers.
  Pointers are accessing the correct memory range locations.
  The access range is within the boundaries of the buffer.*/
  SrcAddr += 1;

  /* [cover parentID={E9626BC0-439E-4e6a-AA5C-CD3361CDDD81}]
Initiate FLS write
[/cover] */
  /* program logical sector */
  /*MISRA2012_RULE_11_8_JUSTIFICATION:Agreed violation. Solvable but the
  solution gives compiler warnings*/
  RetVal = Fls_17_Dmu_Write((Fls_17_Dmu_AddressType)DestAddr, (uint8 *)SrcAddr,
                            BlkSize);

  if( RetVal == E_OK)
  {
    StateDataPtr->FeeQsJobStatus = FEE_JOB_REQSTD;
    StateDataPtr->FeeQsState = (uint8)FEE_QS_PROG_STATE_WRITE_COMPLETE;
  }
  else
  {
    /* Call the Fee_lHandleQsJobFailure with  (~FEE_CANCEL) to notify
    user about failed of job*/

    Fee_lHandleQsJobFailure((~FEE_CANCEL));
  }
}/*End of Fee_lQsBlockWrite */

/*******************************************************************************
** Syntax : static void Fee_lMainQs(void)                                     **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine is responsible for handling QS Block state      **
**               machine                                                      **
*******************************************************************************/
/*[cover parentID={79707214-F807-47e8-B575-7208309EC646}][/cover]*/
static void Fee_lMainQs(void)
{
  const Fee_StateDataType     *StateDataPtr;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
#if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)

  /* If qs erase job is suspended and there is qs write request. first complete
   write request and then resume suspended erase job.*/
  if((StateDataPtr->FeeQsEraseSuspend == FEE_ERASE_SUSPENDED) &&
      (StateDataPtr->FeePendReqStatus == FEE_REQ_QUASI_ERASE))
  {
    Fee_lQsResumeErase();
  }
  else
#endif
  {
    switch(StateDataPtr->FeeQsJob)
    {
      case FEE_READ_JOB:
        {
          Fee_lQsRead();
          break;
        }
      case FEE_WRITE_JOB:
        {
          Fee_lQsWrite();
          break;
        }
      case FEE_ERASE_JOB:
        {
          Fee_lQsErase();
          break;
        }
      default:
        {
          break;
        }
    }
  }
}/*End of Fee_lMainQs */

/*******************************************************************************
** Syntax : static void Fee_lHandleQsJobFailure(void)                         **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function handles the QS job failure occurring due to    **
**               FLS operation failure                                        **
*******************************************************************************/
/*[cover parentID={AE8F8DFA-2242-48d5-9150-45C3A7469B0C}][/cover]*/
static void Fee_lHandleQsJobFailure(const uint8 Error)
{
  Fee_StateDataType     *StateDataPtr;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* This function is  called in Fee_JobErrorNotification which is triggered by
  underlying flash driver and internal qs state machine.so to avoid the double
  error notification for same job check for job status is idle and result is job
  failed if true error notification already done*/
  if((StateDataPtr->FeeQsJob == FEE_REPAIR_JOB) ||
      ((StateDataPtr->FeeQsJobStatus == FEE_JOB_IDLE) &&
       (StateDataPtr->FeeQsJobResult == MEMIF_JOB_FAILED)))
  {
    StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
    /*Internal QS job is failed. Set FeeQsJobResultto fail to trigger the
    Qs illegal notification in Fee_lHandleQsVirginBlocks()  */
    if(StateDataPtr->FeeQsJob == FEE_REPAIR_JOB)
    {
      StateDataPtr->FeeQsJobResult = MEMIF_JOB_FAILED;
    }
  }
  else
  {
#if(FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
    /*Check if QS erase was suspended. If yes then set FeePendReqStatus to
    FEE_REQ_QUASI_ERASE to set module status to busy. If the FeePendReqStatus
    is FEE_REQ_QUASI_ERASE this mean resume failed so set FeePendReqStatus to
    FEE_PEND_PREV_NO_REQ */
    if((StateDataPtr->FeeQsEraseSuspend == FEE_ERASE_SUSPENDED) && 
       (StateDataPtr->FeePendReqStatus != FEE_REQ_QUASI_ERASE))
    {
      StateDataPtr->FeePendReqStatus = FEE_REQ_QUASI_ERASE;
      StateDataPtr->FeeQsJob = FEE_ERASE_JOB;
    }
    else
#endif
    {
      StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_NO_REQ;
      StateDataPtr->FeeQsJob = FEE_NO_JOB;
    }
    StateDataPtr->FeeQsState = FEE_QS_IDLE;
    StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;

    if( FEE_CANCEL != Error)
    {
      StateDataPtr->FeeQsJobResult = MEMIF_JOB_FAILED;
    }
    else
    {
      StateDataPtr->FeeQsJobResult = MEMIF_JOB_CANCELED;
    }
    /* Call user configured job Error notification */
    if( Fee_CfgPtr->FeeQsJobErrorNotification != NULL_PTR )
    {
      /* [cover parentID={F41FCFA0-2BD2-4b1d-9686-AA9314115E08}]
Call the notification function
[/cover] */
      (Fee_CfgPtr->FeeQsJobErrorNotification)();
    }
  }
}/*End of Fee_lHandleQsJobFailure */

/*******************************************************************************
** Syntax : static void Fee_lHandleQsJobSuccess(void)                         **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function performs QS global var status update after     **
**               successful completion of QS job operation                    **
*******************************************************************************/
/*[cover parentID={67E2E638-3877-4d78-83AE-E443573796F2}][/cover]*/
static void Fee_lHandleQsJobSuccess(void)
{
  Fee_StateDataType     *StateDataPtr;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  if(StateDataPtr->FeeQsJob == FEE_REPAIR_JOB)
  {
    StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
    StateDataPtr->FeeQsJobResult = MEMIF_JOB_OK;
  }
  else
  {
#if(FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
    /*Check if QS erase was suspended. If yes then set FeePendReqStatus to
    FEE_REQ_QUASI_ERASE to set module status to busy.*/
    if(StateDataPtr->FeeQsEraseSuspend == FEE_ERASE_SUSPENDED)
    {
      StateDataPtr->FeePendReqStatus = FEE_REQ_QUASI_ERASE;
      StateDataPtr->FeeQsJob = FEE_ERASE_JOB;
    }
    else
#endif
    {
      StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_NO_REQ;
      StateDataPtr->FeeQsJob = FEE_NO_JOB;
    }
    StateDataPtr->FeeQsState = FEE_QS_IDLE;
    StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
    StateDataPtr->FeeQsJobResult = MEMIF_JOB_OK;
    /* Call user configured job End notification */
    if( Fee_CfgPtr->FeeQsJobEndNotification != NULL_PTR )
    {
      /* [cover parentID={33AE7770-BDD2-44d4-9A6F-3BF930911C40}]
Call the notification function
[/cover] */
      (Fee_CfgPtr->FeeQsJobEndNotification)();
    }
  }
}/*End of Fee_lHandleQsJobSuccess */

/*******************************************************************************
** Syntax : static Void Fee_lEvalQsBlockState(Fee_CacheType *const Cacheptr)  **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  Cacheptr    : Pointer to Cache Index                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function will evaluate the Block status and updates     **
**               the Cache accordingly                                        **
*******************************************************************************/
static void Fee_lEvalQsBlockState(Fee_CacheType *const Cacheptr)
{
  Fee_QsBlock_StateType QsBlkWriteStat;
  Fee_QsBlock_StateType QsBlkEraseStat;
  Fee_StateDataType     *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  if(Fee_lEvalQsBlockVirginStatus() == E_OK)
  {
    StateDataPtr->FeeQsBlockVirginCount += FEE_ONE;
  }
  else
  {
    QsBlkWriteStat = Fee_lEvalQsBlockWriteStatus();
    QsBlkEraseStat = Fee_lEvalQsBlockEraseStatus();

    Cacheptr->Status.State = FEE_QS_INVALID;

    if(QsBlkEraseStat != FEE_QS_INVALID)
    {
      if(QsBlkEraseStat == FEE_QS_DIRTY_ERASE)
      {
        Cacheptr->Status.QsDirtyErase = FEE_SET ;
      }
      Cacheptr->Status.State = FEE_QS_ERASE_COMPLETE;
    }
    if(QsBlkWriteStat != FEE_QS_INVALID)
    {
      if(QsBlkWriteStat == FEE_QS_DIRTY_WRITE)
      {
        Cacheptr->Status.QsDirtyWrite = FEE_SET ;
        Cacheptr->Status.State = FEE_QS_WRITE_COMPLETE;
      }
      else
      {
        Cacheptr->Status.State = QsBlkWriteStat;
      }
    }
  }

}/*End of Fee_lEvalQsBlockState */


/*******************************************************************************
** Syntax : static Std_ReturnType Fee_lEvalQsBlockVirginStatus(void)          **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                    E_OK: Block is virgin                                   **
**                    E_NOT_OK : Block is not virgin                          **
** Description : This function will evaluate the Block  virgin status.        **
** all the state page and block cycle count is check for all 0 bits           **
*******************************************************************************/
/* [cover parentID={24F506EE-F27A-4813-B18B-86DD5823289B}]
Fee_lEvalQsBlockVirginStatus
[/cover] */
static Std_ReturnType Fee_lEvalQsBlockVirginStatus(void)
{
  /* [cover parentID={24F506EE-F27A-4813-B18B-86DD5823289B}]*/
  const Fee_StateDataType     *StateDataPtr;
  Std_ReturnType        RetVal;
  const uint32*         TmpPtr;
  uint8                 Index;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /*MISRA2012_RULE_11_3_JUSTIFICATION:This is applicable only for unqualified
  pointers and not for qualified pointers*/
  /*MISRA2012_RULE_11_8_JUSTIFICATION:Agreed violation. solvable but the
  solution gives compiler warnings*/
  TmpPtr = (uint32 *)(StateDataPtr->FeeReadWriteBuffer);

  RetVal = E_OK;
  /*Check the all status pages for zero.In single iteration half page is checked
   */
  for(Index = FEE_RESET ; Index < (FEE_QS_STATUS_PAGES + FEE_QS_STATUS_PAGES) ; Index++ )
  {
    if(TmpPtr[Index] != FEE_RESET )
    {
      RetVal = E_NOT_OK;
      break;
    }
  }

  return(RetVal);
}/*End of Fee_lEvalQsBlockVirginStatus */

/*******************************************************************************
** Syntax : Fee_lHandleQsVirginBlocks(void)                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                    E_OK: Block is virgin                                   **
**                    E_NOT_OK : Block is not virgin                          **
** Description : This function will write Erase complete state marker as part **
** Qs virgin blocks handling only if enabled otherwise triggers the qs        **
** illegal notification.                                                      **
*******************************************************************************/
/* [cover parentID={FAF5624C-FAC7-4d71-B111-2B5DE2F2EAB8},
{1D9DB568-A982-4a59-86B1-DC1395215AED}]
Fee_lHandleQsVirginBlocks
[/cover] */
static void Fee_lHandleQsVirginBlocks(void)
{
  /* [cover parentID={FAF5624C-FAC7-4d71-B111-2B5DE2F2EAB8}]*/
  Fee_StateDataType   *StateDataPtr;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;  

#if (FEE_VIRGIN_FLASH_ILLEGAL_STATE == STD_OFF)
  Fee_CacheType       *CachePtr;
  uint32*              SrcPtr;
  uint32               DestAddr;
  Std_ReturnType        RetVal;

  CachePtr = &(StateDataPtr->FeeBlockInfo[StateDataPtr->FeeQsRepairIndex +
                                          FEE_QSBLOCK_BEGIN_INDEX]);
  /*MISRA2012_RULE_11_3_JUSTIFICATION:This is applicable only for unqualified
  pointers and not for qualified pointers*/
  /*MISRA2012_RULE_11_8_JUSTIFICATION:Agreed violation. solvable but the
  solution gives compiler warnings*/
  SrcPtr = (uint32 *)(StateDataPtr->FeeReadWriteBuffer);

  SrcPtr[0] = FEE_QS_STATE_ERASE_COMPLETE_LSW;
  SrcPtr[1] = FEE_QS_STATE_ERASE_COMPLETE_MSW;

  if((StateDataPtr->FeeQsJobStatus == FEE_JOB_IDLE) &&
      (StateDataPtr->FeeQsJobResult == MEMIF_JOB_OK))
  {
    /* Check if all the qs blocks are marked as erase complete */
    if(StateDataPtr->FeeQsRepairIndex < FEE_NUM_QUASI_BLOCKS)
    {
      DestAddr = CachePtr->Address;
      RetVal = Fls_17_Dmu_Write((Fls_17_Dmu_AddressType)DestAddr, (uint8 *)SrcPtr,
                                FEE_DFLASH_PAGE_SIZE);
      if( RetVal == E_OK)
      {
        CachePtr->Status.QsDirtyErase = 0;
        CachePtr->Status.QsDirtyWrite = 0;
        CachePtr->Status.State = FEE_QS_ERASE_COMPLETE;
        StateDataPtr->FeeQsRepairIndex ++ ;
        StateDataPtr->FeeQsJobStatus = FEE_JOB_REQSTD;
      }
      else
      {
        if(Fee_CfgPtr->FeeQsIllegalStateNotification != NULL_PTR)
        {
          Fee_CfgPtr->FeeQsIllegalStateNotification();
        }
        StateDataPtr->FeeQsJob = FEE_NO_JOB;
        StateDataPtr->FeeInitQSState = FEE_INITQS_COMPLETE;        
      }
    }
    else
    {
      StateDataPtr->FeeQsJob = FEE_NO_JOB;
      StateDataPtr->FeeInitQSState = FEE_INITQS_COMPLETE;
    }
  }
  else
#endif
  {
    if(Fee_CfgPtr->FeeQsIllegalStateNotification != NULL_PTR)
    {
      Fee_CfgPtr->FeeQsIllegalStateNotification();
    }
    StateDataPtr->FeeQsJob = FEE_NO_JOB;
    StateDataPtr->FeeInitQSState = FEE_INITQS_COMPLETE;
  }
}


/*******************************************************************************
** Syntax : static Fee_QsBlock_StateType Fee_lEvalQsBlockEraseStatus(void)    **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  QS Block erase state in DFlash                          **
**                 FEE_QS_INVALID : Block erase state is not valid            **
**                 FEE_QS_ERASE_COMPLETE : Block erase state is erase         **
**                 completed                                                  **
**                 FEE_QS_DIRTY_ERASE : Block erase state is erase            **
**                 dirty, block erase is not completed                        **
** Description : This function will evaluate the Block erase completion status**
*******************************************************************************/
static Fee_QsBlock_StateType Fee_lEvalQsBlockEraseStatus(void)
{
  const Fee_StateDataType     *StateDataPtr;
  Fee_QsBlock_StateType RetVal;
  uint32                TempData;
  uint32                Bcc;
  const uint32*         TmpPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /*MISRA2012_RULE_11_3_JUSTIFICATION:This is applicable only for unqualified
  pointers and not for qualified pointers*/
  /*MISRA2012_RULE_11_8_JUSTIFICATION:Agreed violation. solvable but the
  solution gives compiler warnings*/
  TmpPtr = (uint32 *)(StateDataPtr->FeeReadWriteBuffer);
  
  Bcc = TmpPtr[(FEE_QS_STATE_CYCLE_COUNT_OFFSET/FEE_DFLASH_WORD_SIZE)] &
        FEE_32_BIT_ALL_ONES;
  RetVal = FEE_QS_INVALID;
  /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than array
  indexing used for FEE application buffers.
  Pointers are accessing the correct memory range locations.
  The access range is within the boundaries of the buffer.*/
  TempData = (TmpPtr[FEE_TWO])  | (TmpPtr[FEE_THREE]) | (TmpPtr[FEE_FOUR]) |
             (TmpPtr[FEE_FIVE]) | (TmpPtr[FEE_SIX])   | (TmpPtr[FEE_SEVEN]);

  if(TempData == FEE_RESET)
  {
    if(Bcc == FEE_RESET)
    {
      if((*(TmpPtr) == FEE_QS_STATE_ERASE_COMPLETE_LSW) &&
         (TmpPtr[FEE_ONE] == FEE_QS_STATE_ERASE_COMPLETE_MSW))
      {
        RetVal = FEE_QS_ERASE_COMPLETE;
      }
      else if( (*(TmpPtr) | (TmpPtr[FEE_ONE])) != FEE_RESET)
      {
        RetVal = FEE_QS_DIRTY_ERASE;
      }
      else
      {
        /* To avoid misra warning */
      }
    }
  }

  return(RetVal);
}/*End of Fee_lEvalQsBlockEraseStatus */

/*******************************************************************************
** Syntax : static Fee_QsBlock_StateType Fee_lEvalQsBlockWriteStatus(void)    **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  QS Block write state in DFlash                          **
**                                                                            **
** Description : This function will evaluate the Block write completion status**
*******************************************************************************/
static Fee_QsBlock_StateType Fee_lEvalQsBlockWriteStatus(void)
{
  const Fee_StateDataType     *StateDataPtr;
  Fee_QsBlock_StateType  RetVal;
  uint32                 Bcc;
  uint32                 Bcc_Comp;
  const uint32*          TmpPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /*MISRA2012_RULE_11_3_JUSTIFICATION:Applies only for unqualified pointers
  Here qualified pointers are used*/
  /*MISRA2012_RULE_11_8_JUSTIFICATION:Applies only for unqualified pointers
  Here qualified pointers are used*/
  TmpPtr = (uint32 *)(StateDataPtr->FeeReadWriteBuffer);
  
  Bcc = ((TmpPtr[FEE_EIGHT]) & FEE_16_BIT_ALL_ONES);
  Bcc_Comp = (((TmpPtr[FEE_EIGHT]) >> FEE_SIXTEEN) &
              FEE_16_BIT_ALL_ONES);

  RetVal = FEE_QS_INVALID;

  /* FEE_QS_STATE_DFERASE_STATE is also checked to handle power failure
   * during virgin flash preparation. */
  if(((*TmpPtr == FEE_QS_STATE_ERASE_COMPLETE_LSW) &&
     
      ((TmpPtr[FEE_ONE]) == FEE_QS_STATE_ERASE_COMPLETE_MSW))
      || (*TmpPtr == FEE_QS_STATE_DFERASE_STATE))
  {

    if(((TmpPtr[FEE_TWO]) == FEE_QS_STATE_WRITE_STARTED_LSW) &&
       
        ((TmpPtr[FEE_THREE]) == FEE_QS_STATE_WRITE_STARTED_MSW))
    {
    
      if(((TmpPtr[FEE_SIX]) | (TmpPtr[FEE_SEVEN])) == FEE_RESET)
      {
        if(Bcc == (~Bcc_Comp & FEE_16_BIT_ALL_ONES))
        {
          
          if(((TmpPtr[FEE_FOUR]) == FEE_QS_STATE_WRITE_COMPLETE_LSW) &&
            ((TmpPtr[FEE_FIVE]) == FEE_QS_STATE_WRITE_COMPLETE_MSW))
          {
            RetVal = FEE_QS_WRITE_COMPLETE;
          }
          else if(((TmpPtr[FEE_FOUR]) | (TmpPtr[FEE_FIVE])) == FEE_RESET)
          {
            RetVal = FEE_QS_WRITE_STARTED;

          }
          else
          {
            RetVal = FEE_QS_DIRTY_WRITE;
          }
        }
      }
    }
  }
  return(RetVal);
}/*End of Fee_lEvalQsBlockWriteStatus */

/*******************************************************************************
** Syntax : static Void Fee_lQsIDSM(void)                                     **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function will repair QS Blocks which are identified     **
**               in Init as Dirty                                             **
*******************************************************************************/
/* [cover parentID={81DD7816-C7F3-4c48-BE2B-9C7601A2A086},
{34019D92-D6C9-4d4e-ABEE-808DA8F12A11}]
Check for QS job status
[/cover] */
static void Fee_lQsIDSM(void)
{
  Fee_StateDataType    *StateDataPtr;
  uint32                BlkAddr;
  Fee_CacheType  *CachePtr;
  Std_ReturnType        RetVal;
  Std_ReturnType        TempRetVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  CachePtr = &(StateDataPtr->FeeBlockInfo[StateDataPtr->FeeQsRepairIndex +
                                          FEE_QSBLOCK_BEGIN_INDEX]);
  StateDataPtr->FeeTempArray[0] = FEE_QS_STATE_WRITE_COMPLETE_LSW;
  StateDataPtr->FeeTempArray[1] = FEE_QS_STATE_WRITE_COMPLETE_MSW;
  TempRetVal = E_OK;
  BlkAddr = CachePtr->Address;

  if((StateDataPtr->FeeQsJobStatus == FEE_JOB_IDLE) && 
    (StateDataPtr->FeeQsJobResult == MEMIF_JOB_FAILED))
  {
     /*Repair of the block is failed mark the block as invalid*/
     CachePtr->Status.State = FEE_QS_INVALID;
  }
  
  while((StateDataPtr->FeeQsRepairIndex < FEE_NUM_QUASI_BLOCKS) &&
        (TempRetVal == E_OK))
  {

    if(CachePtr->Status.QsDirtyErase == (uint32)1)
    {
      BlkAddr = CachePtr->Address;
      /* reset the Dirty Status */
      CachePtr->Status.QsDirtyErase = FEE_RESET;
      TempRetVal = E_NOT_OK;
    }
    else if(CachePtr->Status.QsDirtyWrite == (uint32)1)
    {
      BlkAddr = CachePtr->Address + FEE_QS_STATE_WRITE_COMPLETED_OFFSET;
      /* reset the Dirty Status */
      CachePtr->Status.QsDirtyWrite = FEE_RESET;
      TempRetVal = E_NOT_OK;
    }
    else
    {
      StateDataPtr->FeeQsRepairIndex++;
      CachePtr++;
    }

    if(TempRetVal == E_NOT_OK)
    {
      /* program logical sector */
      RetVal = Fls_17_Dmu_Write((Fls_17_Dmu_AddressType)BlkAddr,
                                (uint8 *)(StateDataPtr->FeeTempArray),
                                FEE_DFLASH_PAGE_SIZE);

      if(RetVal == E_OK)
      {
        StateDataPtr->FeeQsJobStatus = FEE_JOB_REQSTD;
      }
      else
      {
        /*Repair of the block is failed mark the block as invalid.Continue the 
        repair of other blocks*/
        CachePtr->Status.State = FEE_QS_INVALID;  
        TempRetVal = E_OK;
      }
    }
  }
  if(StateDataPtr->FeeQsRepairIndex == FEE_NUM_QUASI_BLOCKS)
  {
    StateDataPtr->FeeQsJob = FEE_NO_JOB;
    StateDataPtr->FeeInitQSState = FEE_INITQS_COMPLETE;
  }
}/*End of Fee_lQsIDSM */

/*******************************************************************************
** Syntax : static Void Fee_lMainQsTransHdlr(void)                            **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function Performs the state transition for the main     **
**               function when in FEE_MAIN_QS state                           **
*******************************************************************************/
static void Fee_lMainQsTransHdlr(void)
{
  Fee_StateDataType    *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  if(StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_NO_REQ)
  {

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
    if(StateDataPtr->FeeGcState != FEE_GC_IDLE)
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_GC;
    }
    else
#endif
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_NONE;
    }
  }

#if (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
  /*Check for NVM write after QS write*/
  else if( (boolean)TRUE == Fee_lIsUserWriteInvldReqstd(StateDataPtr) )
  {
#if (FEE_CANCELL_ALL_API == STD_ON)
    /* Switch to main none to Check if there is GC cancelled by cancel all */
    StateDataPtr->FeeMainJob = FEE_MAIN_NONE;

#else
    StateDataPtr->FeeMainJob = FEE_MAIN_WRITE;
#endif

  }

#endif


#if (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
  /*Check for NVM read after QS write*/
  else if( (boolean)TRUE == Fee_lIsUserReadReqstd(StateDataPtr) )
  {
#if (FEE_CANCELL_ALL_API == STD_ON)

    /* Switch to main none to Check if there is GC cancelled by cancel all */

    StateDataPtr->FeeMainJob = FEE_MAIN_NONE;

#else
    StateDataPtr->FeeMainJob = FEE_MAIN_READ;
#endif
  }
  else
  {
    /* To aviod misra warning */
  }

#endif
  /*else - fix
  {
     StateDataPtr->FeeMainJob = FEE_MAIN_NONE;
  }*/
}/*End of Fee_lMainQsTransHdlr */

#if (FEE_CANCELL_ALL_API == STD_ON) && \
   (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
/*******************************************************************************
** Traceability   : [cover parentID={910989B6-08AC-4a55-9E86-1BE2C74C6FAC}]   **
**                                                                            **
** Syntax : void Fee_17_CancelAll (void)                                      **
**                                                                            **
** Service ID: 0x28                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : Service to cancel any ongoing Internal/User read or write    **
** job. However, ongoing erase cannot be cancelled.                           **
*******************************************************************************/
/* [cover parentID={7C10DE66-A21A-47db-8A13-D456A64C30B2}]
Fee_17_CancelAll
[/cover] */
void Fee_17_CancelAll(void)
{
  
  MemIf_StatusType   FeeStatus;
  
/* [cover parentID={BC39E052-0028-4c12-851B-8B5724774BA5}]
Safety error is enabled
[/cover] */
#if(FEE_SAFETY_ENABLE == STD_ON)

  /*Check for configuration pointer(Fee_CfgPtr)for null as part safety check */
  /* Check if the Fee_Init API is called */
  
   /* [cover parentID={9215E9C4-C1AF-42b7-B5B1-D70924A5D6F5}]
 Is the configuration pointer NULL?
[/cover] */ 
  if(Fee_CfgPtr != NULL_PTR)

#endif
  { 
  /* [cover parentID={FE83D752-5E24-4d57-8348-62C72A9EFC7B}]
Get Fee status
[/cover] */
    FeeStatus = Fee_lGetStatus();
    /*any internal or User job ongoing*/
    /* [cover parentID={14E0C734-498B-4a77-B86F-404F91446F1C}]
Is Fee busy?
[/cover] */
    if((FeeStatus == MEMIF_BUSY_INTERNAL) || (FeeStatus == MEMIF_BUSY))
    {
      /* [cover parentID={BCE9C3B0-AFD8-4536-8FAC-A19693551C59}]
Cancel the ongoing job
[/cover] */
     
      Fee_lCancelAll();
    }
  /* [cover parentID={F77E1C4F-6258-4a9c-B0E8-8D73015FA394}]
Safety is enabled
[/cover] */
#if(FEE_SAFETY_ENABLE == STD_ON)
    else
    { /* [cover parentID={4E0263ED-0EDF-4276-8B16-636C7999B44E}]
Report error as FEE_E_INVALID_CANCEL
[/cover] */
      Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_SID_CANCELALL,
                               FEE_E_INVALID_CANCEL);
    }
#endif

    
  }
#if(FEE_SAFETY_ENABLE == STD_ON)
  else
  { 
/* [cover parentID={7CF34432-255A-4503-BE86-4D3FC9CA3328}]
Report error as FEE_E_UNINIT
[/cover] */
    Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_SID_CANCELALL,
                           FEE_E_UNINIT);
  }
#endif

}
#endif

/*CYCLOMATIC_Fee_lCancelAll_JUSTIFICATION: Fee_lCancelAll has
to determine all the states of ongoing operation and then cancel.
It broken properly into various stages using switch case which cannot be broken
further. If it is broken into more functions to fix RSM, the code readability
will get affected.
*/
/*******************************************************************************
** Syntax : void Fee_lCancelAll(void)                                         **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function Performs the cancellation of ongoing           **
**               Fee Job operation including GC.                               **
*******************************************************************************/
#if (FEE_CANCELL_ALL_API == STD_ON) && \
   (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
/* [cover parentID={41BC93C6-486B-45f8-A095-EF6CFF2E1828},
{07F854EA-9B94-4496-8129-90F411D55A37}]
Fee_lCancelAll
[/cover] */
   static void Fee_lCancelAll (void)
{

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
  Fee_StateDataType     *StateDataPtr;
  uint8                  CancelGC;
#else
  const Fee_StateDataType     *StateDataPtr;
#endif

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  switch(StateDataPtr->FeePendReqStatus)
  {
      
      
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
    /* there was a write/read request registered only */
    case FEE_REQ_IMM_WRITE:
    case FEE_REQ_NORM_WRITE:
    case FEE_REQ_READ:
    case FEE_PEND_PREV_READ_REQ:
    case FEE_PEND_PREV_READ_NOTIF:
      {
        /* Is any job requested to Fls, if yes then cncel the job.
        notification will be triggered to user by fee_job_error notification.*/
        if(StateDataPtr->FeeUserJobStatus == FEE_JOB_REQSTD)
        {

          Fls_17_Dmu_Cancel();
        }
        else
        {
          /* Call the Fee_lHandleUsrJobFailure with  FEE_CANCEL to notify
          user about cancelled of job*/
          Fee_lHandleUsrJobFailure(FEE_CANCEL);
        }
        break;
      }

#endif

    case FEE_REQ_QUASI_WRITE:
    case FEE_REQ_QUASI_READ:
    case FEE_REQ_QUASI_ERASE:
      {

        if(StateDataPtr->FeeQsJobStatus == FEE_JOB_REQSTD)
        {
          if(StateDataPtr->FeePendReqStatus == FEE_REQ_QUASI_ERASE)
          {
            /* Only cancel the fls write request in qs erase job. fls Erase
                request can not be canceled */
            if((StateDataPtr->FeeQuasiBlkInstanceTemp != FEE_ZERO) &&
                (StateDataPtr->FeeQsState != (uint8)FEE_QS_PROG_STATE_ERASE_COMPLETE))
            {
              Fls_17_Dmu_Cancel();
            }

          }
          else
          {
            Fls_17_Dmu_Cancel();
          }

        }
        else
        {
          /* Call the Fee_lHandleQsJobFailure with  FEE_CANCEL to notify
          user about cancelled of job*/
          Fee_lHandleQsJobFailure(FEE_CANCEL);
        }
        break;
      }

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
    /* write ongoing when this was called */
    case FEE_PEND_PREV_COMPARE:
    case FEE_PEND_INTR_COMPARE:
      {
        /* cancel ongoing write*/
        Fee_lCancelWrite();

        break;
      }
#endif

    default:
      {
        /*Do nothing*/

        /*The QS erase job can not be canceled */
        break;
      }
  }


#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

  /* remember : before exit, there cannot be any pending jobs.
     We should be in some kind of an idle state so that new jobs
   can be accepted. This is a good test case */

  switch(StateDataPtr->FeeGcState)
  {
    case FEE_GC_IDLE:
      {
        CancelGC = FEE_RESET;
        break;
      }

    case FEE_GC_ERASE_PREV_SECTOR:
    case FEE_GC_INIT_ERASE_PREV_SECTOR:
      {
        if(StateDataPtr->FeeIntrJobStatus == FEE_JOB_IDLE)
        {
          CancelGC = FEE_SET;
        }
        else
        {
          CancelGC = FEE_RESET;
        }
        break;
      }

    default:
      {
        CancelGC = FEE_SET;
        break;
      }

  }

  if(CancelGC == FEE_SET)
  {
    Fee_lCancelWrite();
    StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_NO_REQ;
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
    StateDataPtr->FeeIntrJobResult = (uint8)MEMIF_JOB_CANCELED;
    StateDataPtr->FeeIntrJob = FEE_NO_JOB;
    StateDataPtr->FeeGcState = FEE_GC_IDLE;
    /*Set  FeeCancelallGCstate to FEE_GC_CANCLD notify GC is cancelled by
    cancel all */
    StateDataPtr->FeeCancelallGCstate = FEE_GC_CANCLD;

  }

#endif


}/*End of Fee_lCancelAll */

#endif

/* [cover parentID={DDA2DC38-6BEC-43ec-9880-430191057143}]
FEE_CANCELL_ALL_API enabled and QS data block supported
[/cover] */
#if (FEE_CANCELL_ALL_API == STD_ON) && \
   (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)

/*******************************************************************************
** Syntax : void Fee_lCancelAllGCrestart(void)                                **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function Performs reset of sector info and will build   **
**               DFLASH and Set fee main to INITGC state.                     **
*******************************************************************************/
static void Fee_lCancelAllGCrestart(void)
{


  Fee_StateDataType     *StateDataPtr;
  Fee_SectorInfoType    *SectorInfoPtr;
  uint32 Index;
  uint32 EndAddr;
  uint8  DFlashStatus;
  uint8  ReturnVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  SectorInfoPtr = StateDataPtr->FeeSectorInfo;
  /* Initialize Sector State information */
  for(Index = FEE_RESET; Index < FEE_SECTORS; Index++)
  {
    /*MISRA2012_RULE_18_4_JUSTIFICATION:This warning is for the core FEE
    structures   which are containing the Block and sector info and affects the
    entire FEE   functionality.Changing these would increase the risk of major
    functional impact on the entire FEE code,thereby putting the complete
    functionality of FEE at risk. */
    SectorInfoPtr = SectorInfoPtr + Index;
    SectorInfoPtr->State = FEE_RESET;
    SectorInfoPtr->StateCount = FEE_RESET;
    SectorInfoPtr->UnerasableWLCount = FEE_RESET;
    SectorInfoPtr->UnerasableWLAddr[0] = FEE_RESET;
    SectorInfoPtr->UnerasableWLAddr[1] = FEE_RESET;
    SectorInfoPtr->Status.Dirty = FEE_RESET;
    SectorInfoPtr->Status.Used = FEE_RESET;
    SectorInfoPtr->StatePageAddr = FEE_RESET;
    SectorInfoPtr->NextFreeWLAddr = FEE_RESET;
    SectorInfoPtr->NonZeroWLCount = FEE_RESET;
    SectorInfoPtr->NonZeroWLAddr[0] = FEE_RESET;
    SectorInfoPtr->NonZeroWLAddr[1] = FEE_RESET;
  }

  StateDataPtr->FeeStateCount = FEE_RESET;
  StateDataPtr->FeeSectorCount = FEE_RESET;
  StateDataPtr->FeeComparedLen = FEE_RESET;
  StateDataPtr->FeeReadLen = FEE_RESET;
  StateDataPtr->FeeUnErasableWLAddrTemp[0] = FEE_RESET;
  StateDataPtr->FeeUnErasableWLAddrTemp[1] = FEE_RESET;
  StateDataPtr->FeeUnErasableWLCountTemp = FEE_RESET;

  /* Read sector information */
  /*Clear the fee read/write buffer*/
  Fee_lClearFeeReadWriteBuffer();
  for(Index = FEE_RESET; Index < FEE_SECTORS; Index++)
  {
    if(Index == FEE_RESET)
    {
      EndAddr = FEE_DFLASH_BANK0_BASE;
    }
    else
    {
      EndAddr = FEE_DFLASH_BANK1_BASE;
    }
    StateDataPtr->FeeCurrSectSrcAddr = EndAddr +
                                       (FEE_DFLASH_SECTOR_SIZE -
                                        FEE_DFLASH_WORDLINE_SIZE);
    do
    {
      ReturnVal = Fee_lGetSectorInfo(Index, EndAddr);
    }
    while(ReturnVal == FEE_SP_INIT);
  }

  DFlashStatus = Fee_lBuildDFlashStatus();

  /* Set the init GC state*/
  Fee_lSetInitGc(DFlashStatus);



}


/*******************************************************************************
** Syntax : static void Fee_lCancelWrite (void)                               **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : Performs canceling of ongoing write operation and resets     **
**               job status variables                                         **
*******************************************************************************/
/* [cover parentID={4C58F967-ACB1-4990-8787-235646670441}]
Fee_lCancelWrite
[/cover] */
static void Fee_lCancelWrite(void)
{
  /* [cover parentID={4C58F967-ACB1-4990-8787-235646670441}]*/
  /* [cover parentID={DDA2DC38-6BEC-43ec-9880-430191057143}]*/
  Fls_17_Dmu_Job_Type RetVal;
  Fee_StateDataType  *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  RetVal = Fee_lGetUserJob(StateDataPtr->FeePendReqStatus);

  if(RetVal == FEE_NO_JOB)
  {
    /* GC is cancelled check if there is any request to FLS. If yes then cancel
     the request. GC will be restarted by next NVM read/write request.*/
    if( StateDataPtr->FeeIntrJobStatus == FEE_JOB_REQSTD)
    {
      /* Cancel ongoing FLS request */
      Fls_17_Dmu_Cancel();
    }

  }
  /*User write job is cancelled check if there is any request to FLS.
  If yes then cancel the request. */
  else if(StateDataPtr->FeeUserJobStatus == FEE_JOB_REQSTD)
  {
    /* NVM job error notification will be triggered by fee_error notification
    called by FLS when job is cancel*/
    Fls_17_Dmu_Cancel();
  }
  else
  {
    /* write job is cancelled then increase free page address to next
    but one WL. This will avoid write on same page for next write job.
    Also trigger NVM job error notification */

    Fee_lHandleUsrJobFailure(FEE_CANCEL);
    StateDataPtr->FeeNextFreePageAddr += StateDataPtr->FeeLastWriteSize;
    StateDataPtr->FeeNextFreePageAddr = Fee_lGetNextWLAddr(
                                          StateDataPtr->FeeNextFreePageAddr);
    StateDataPtr->FeeNextFreePageAddr += FEE_DFLASH_WORDLINE_SIZE;
  }
}

#endif

#if (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
/*******************************************************************************
** Syntax : static void Fee_lGcHardenQsSector(void)                           **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function Checks and performs Hardening operation on     **
** part of QS region                                                          **
*******************************************************************************/
/* [cover parentID={3D1C82A1-9719-4283-9359-A662A4B1A3C0}]
Fee_lGcHardenQsSector
[/cover] */
static void Fee_lGcHardenQsSector(void)
{

  Fee_StateDataType   *StateDataPtr;
  Std_ReturnType       ReturnValue;
  uint8          *ReadWriteBuffPtr;
  Fls_17_Dmu_AddressType      Addr;


  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
   /* [cover parentID={3D1C82A1-9719-4283-9359-A662A4B1A3C0}]*/
  if (StateDataPtr->FeeIntrJobStatus == FEE_JOB_DONE)
  {
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
    if(StateDataPtr->FeeIntrJobResult == FEE_JOB_FAIL)
    {
      /* [cover parentID={9729EC09-099B-463e-A28F-24169C9B39A8}]*/
      /* Error is encountered while write operation as part of hardening
      switch GC state to erase previous sector state. */
      if(Fee_CfgPtr->FeeQsHardenErrorNotification != NULL_PTR)
      { 
  /* [cover parentID={9729EC09-099B-463e-A28F-24169C9B39A8}]
Call QS harden error notification (provided the notification function is configured)
[/cover] */
        Fee_CfgPtr->FeeQsHardenErrorNotification();
      }
    }
  }

  /*This function checks if hardening is required or not with the help
  of Fls functionality and returns the page address where hardening is to
  be done. If hardening is not required, 0xFFFFFFFF will be obtained   */
  Addr = Fee_lGcHardenReqChk();

  if(FEE_NO_HARDEN_RET_ADDRESS  != Addr)
  {
    /* [cover parentID={39DB863C-C2E8-4ccc-8967-FAF339519FED}]*/
    ReadWriteBuffPtr = StateDataPtr->FeeGcReadWriteBuffer;
  /* [cover parentID={39DB863C-C2E8-4ccc-8967-FAF339519FED}]
Read word data from flash bank synchronously
[/cover] */
    /*MISRA2012_RULE_11_3_JUSTIFICATION:MISRA 11.3 not applicable due to
    exception that it applies only to unqualified pointer types and not to
    the qualified pointer types. Qualified pointer types used here. */
    ReturnValue = Fls_17_Dmu_ReadWordsSync(Addr, (uint32 *)ReadWriteBuffPtr,
                   (FEE_DFLASH_PAGE_SIZE / FEE_DFLASH_WORD_SIZE));
    if(E_NOT_OK == ReturnValue)
    {
      /* [cover parentID={C53A6B1C-22A9-4bfc-8EDA-E5F4C877AA24}]*/
      if(Fee_CfgPtr->FeeQsHardenErrorNotification != NULL_PTR)
      {
      /* [cover parentID={C53A6B1C-22A9-4bfc-8EDA-E5F4C877AA24}]
Call QS harden error notification (provided the notification function is configured)
[/cover] */
        /* Error is encountered while performing reading as
        part of hardening operation. */
        Fee_CfgPtr->FeeQsHardenErrorNotification();
      }
    }
    else
    {
      ReturnValue = Fls_17_Dmu_Write(Addr, ReadWriteBuffPtr,
                                     FEE_DFLASH_PAGE_SIZE);
      if(E_NOT_OK == ReturnValue)
      {
        if(Fee_CfgPtr->FeeQsHardenErrorNotification != NULL_PTR)
        {
          /* Error is encountered while requesting write
          operation as part of hardening. */
          Fee_CfgPtr->FeeQsHardenErrorNotification();
        }
      }
      else
      {
        StateDataPtr->FeeIntrJobStatus = FEE_JOB_REQSTD;
        StateDataPtr->FeeIntrJob = FEE_WRITE_JOB;
      }
    }
  }

  return;

}/*End of Fee_lGcHardenQsSector */

/*CYCLOMATIC_Fee_lGcHardenReqChk_JUSTIFICATION:
  In this function, address of the wordline or address of the corresponding
  page is calculated.Further splitting (though it might not be a logical
  decomposition) would mean, these address calculations
  have to be repeated again in the split function or introduce new global static
  variables to handle the scenario.
*/
/*******************************************************************************
** Syntax : static Fls_17_Dmu_AddressType Fee_lGcHardenReqChk(void)           **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function checks whether hardening is required or not    **
** with the help of Fls functionality                                         **
*******************************************************************************/
static Fls_17_Dmu_AddressType Fee_lGcHardenReqChk(void)
{
  Fee_StateDataType   *StateDataPtr;
  uint8 RetPageChk = FEE_HARDEN_NOT_REQRD;
  uint8 RetWLChk = FEE_HARDEN_NOT_REQRD;
  uint8 HardeningRateReached = 0U;
  Fls_17_Dmu_AddressType      Addr;
  Fls_17_Dmu_AddressType      RetAddrToBeHardened;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;


  RetAddrToBeHardened = FEE_NO_HARDEN_RET_ADDRESS;
  do
  {
    /*Check if the hardening check and hardening is completed for the required
    portion of QS area */
    if(FEE_HARDENING_RATE == StateDataPtr->FeeHardeningWLCount)
    {
      if(StateDataPtr->FeeQsHardeningOffset < 
        ((FEE_DFLASH_QS_SIZE /FEE_DFLASH_WORDLINE_SIZE) - FEE_HARDENING_RATE))
      {
        /* This offset is stored in the state page so that Hardening check can 
        be started from this address of the QS area in the next GC */
        StateDataPtr->FeeQsHardeningOffset += FEE_HARDENING_RATE;
      }
      else
      {
        StateDataPtr->FeeQsHardeningOffset = FEE_RESET;
      }
      StateDataPtr->FeeHardeningWLCount = FEE_RESET;
      HardeningRateReached = 1U ;
      /* Since Hardening is completed for the required portion, GC state is
       switched to erase previous sector state. */
      StateDataPtr->FeeGcState = FEE_GC_ERASE_PREV_SECTOR;
    }
    else
    {
      /* Wordline Address is calculated for which Hardening check is to be done.
        Offset address is passed here as Fls driver adds this offset to the
        DFlash base address*/
      Addr = ((((StateDataPtr->FeeQsHardeningOffset  +
             StateDataPtr->FeeHardeningWLCount) * (FEE_DFLASH_WORDLINE_SIZE))
             + FEE_QS_SECTOR_BASE) - FLS_17_DMU_BASE_ADDRESS);
      /*if Hardening page count is 0, it means hardening check
        is to be done at fresh/new wordline */
      if (0U == StateDataPtr->FeeHardeningPageCount)
      { 
  /* [cover parentID={608FEC0D-CC01-40c8-9646-B3CFB7D12A73}]
Call FLS function to find out whether hardening is required for fresh wordline or not
[/cover] */
      /*Check for Hardening required or not at Wordline level granularity */
      RetWLChk = Fls_17_Dmu_IsHardeningRequired(Addr,FEE_HARDEN_CHK_WL);
      }
      /*if Hardening page count is not 0, it means hardening check
      is to be done at page level. Also this is done to find which page is to be
      checked for Hardening for the wordline which requires Hardening */
      if ((FEE_HARDEN_REQRD == RetWLChk) ||
          (0U != StateDataPtr->FeeHardeningPageCount))
      {
        do
        {
          /*Page address is calculated for which Hardening check is
           to be done.*/
           Addr += (StateDataPtr->FeeHardeningPageCount * FEE_DFLASH_PAGE_SIZE);
          /*Check for Hardening required or not at Page level granularity */
          RetPageChk = Fls_17_Dmu_IsHardeningRequired(Addr,FEE_HARDEN_CHK_PAGE);
          if (FEE_HARDEN_REQ_ERROR == RetPageChk)
          {
            if(Fee_CfgPtr->FeeQsHardenErrorNotification != NULL_PTR)
            {
              Fee_CfgPtr->FeeQsHardenErrorNotification();
            }
          }
          if (FEE_HARDEN_REQRD == RetPageChk)
          {
            /* Page address for which hardening is to be done is returned  */
            RetAddrToBeHardened = Addr;
          }
          /*If Hardening check is not required for this page or if the
          Hardening check API from Fls encounters any error, then the check
          is continued for the remaining pages*/
          StateDataPtr->FeeHardeningPageCount += 1U;
        }
        while((FEE_HARDEN_REQRD != RetPageChk) &&
              (StateDataPtr->FeeHardeningPageCount < FEE_PAGES_IN_WL));
        if (FEE_PAGES_IN_WL == StateDataPtr->FeeHardeningPageCount)
        {
          /* Hardening page count is reset to 0 if it reaches maximum count.
          This reset is needed to arrive at the correct calculation of the
          corresponding page address of the Wordline if hardening had to be done
          for one or more pages in that wordline  */
          StateDataPtr->FeeHardeningPageCount = 0U;
          /* 64 pages in the wordline are checked for Hardening, hence move to
          next wordline */
          StateDataPtr->FeeHardeningWLCount += 1U;
        }
      }
      else if (FEE_HARDEN_REQ_ERROR == RetWLChk)
      {
        if(Fee_CfgPtr->FeeQsHardenErrorNotification != NULL_PTR)
        {
          Fee_CfgPtr->FeeQsHardenErrorNotification();
        }
        /*If Hardening check API from Fls encounters any error, then the check
            is continued for the remaining Wordlines after raising the
            HardenErrorNotification */
        StateDataPtr->FeeHardeningWLCount += 1U;
      }
      else
      {
      /*If Hardening check is not required for this Wordline then the check
          is continued for the remaining wordlines*/
      StateDataPtr->FeeHardeningWLCount += 1U;
      }
    }
  }
  while((FEE_HARDEN_REQRD  != RetPageChk) && (FEE_HARDEN_REQRD  != RetWLChk)
        && (FEE_RESET == HardeningRateReached));

  return (RetAddrToBeHardened);
}

#endif
#endif


#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Syntax :  static void Fee_lReportError(uint8 ApiId,uint8 ErrorId)          **
**                                                                            **
**                                                                            **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Ssynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : (uint8) ApiId   - Service id of the caller API           **
**                   (uint8) ErrorId - ID of the error to be reported         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
** Description : Function to report Safety Error and DET                      **
*******************************************************************************/
/* [cover parentID={25435F35-A888-4723-B287-226507149FDF}][/cover] */
static void Fee_lReportError(uint8 ApiId, uint8 ErrorId)
{
/* [cover parentID={83E19753-FDEB-4992-814C-2E0E46A7B40B}]
DET enabled
[/cover] */
#if (FEE_DEV_ERROR_DETECT == STD_ON)
/* [cover parentID={619A9DAB-D6AA-4ab0-9BD8-5B4D6045C873}]
Call DET reporting with FEE_MODULE_ID, FEE_INSTANCE_ID, ApiId, ErrorId

[/cover] */
  Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, ApiId, ErrorId);

#endif
/* [cover parentID={12098A7C-2D7F-47dd-98E6-31801ADEEECF}]
Safety enabled
[/cover] */
#if (FEE_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={B17C4A42-EAA9-4623-B004-81338746ACB4}]
Reporting Safety Error, calling with FEE_MODULE_ID, FEE_INSTANCE_ID, ApiId, ErrorId

[/cover] */
  Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID, ApiId,
                         ErrorId);
#endif

} /*End of Fee_lReportError*/

/******************************************************************************
** Syntax : LOCAL_INLINE Std_ReturnType Fee_lReadDetSafetyCheck(const uint16 **
**            BlockNumber,                                                   **
**            const uint16 BlockOffset,                                      **
**            const uint8 *const DataBufferPtr,                              **
**            const uint16 Length,                                           **
**            uint8 ApiId)                                                   **
**                                                                           **
**                                                                           **
**                                                                           **
** Service ID:                                                               **
**                                                                           **
** Sync/Async:  Synchronous                                                  **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) :  BlockNumber - Logical Block Number                     **
**                    BlockOffset - Read address offset inside the block     **
**                    DataBufferPtr - Pointer to data buffer                 **
**                    Length - Number of bytes to read                       **
**                    ApiId   - Service id of the caller API                 **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  Std_ReturnType                                         **
**                    E_OK: Check Pass                                       **
**                    E_NOT_OK: Check Fail                                   **
** Description : Function will check the input parameters of read api.       **
** if parameters are not in valid range it will trigger DET/Safety Error     **
** and return E_NOT_OK                                                       **
******************************************************************************/
 /* [cover parentID={23ABBD8D-A68F-4aaf-AE18-F48AB2807A4D}][/cover] */
LOCAL_INLINE Std_ReturnType Fee_lReadDetSafetyCheck(const uint16 BlockNumber,
    const uint16 BlockOffset,
    const uint8 *const DataBufferPtr,
    const uint16 Length,
    uint8 ApiId)
{

  uint16               BlkIdx;
  Std_ReturnType       ReturnValue;
  uint32               BlkSize;

  ReturnValue = E_OK;
  
  BlkIdx = Fee_lGetUsrBlockIndex(BlockNumber);

  /* If BlockNumber exists in the user configuration and is within range */
  if (BlkIdx == FEE_LOG_BLOCK_NOT_FOUND)
  {
    /* [cover parentID={ECA67BD8-EE6E-4430-ACA3-48B5E6C73DF7}]
Call FEE_E_INVALID_BLOCK_NO DET
[/cover] */
    Fee_lReportError( ApiId, FEE_E_INVALID_BLOCK_NO);

    /* [cover parentID={08827D4A-F03C-4c07-8B21-1A66B88D2E9B}]
    Set Flag as E_NOT_OK
    [/cover] */
    ReturnValue = E_NOT_OK;
  }
  else
  {

    BlkSize = Fee_CfgPtr->FeeBlockConfigPtr[BlkIdx].Size;

#if(FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)

    if(Fee_CfgPtr->FeeBlockConfigPtr[BlkIdx].FeeUser ==
        (uint8)FEE_QUASI_STATIC_USER)
    {
      BlkSize = (BlkSize - (uint32)FEE_QS_DATA_OFFSET);
    }

#endif

    /* Check if the offset is valid i.e. within the block size */
    if ((uint32)BlockOffset >= BlkSize)
    {
    /* [cover parentID={E2D729FE-30D6-44a7-A6B7-FD2B03DBBB7F}]
Call FEE_E_INVALID_BLOCK_LEN DET
[/cover] */
      Fee_lReportError(ApiId, FEE_E_INVALID_BLOCK_OFS);

      /* [cover parentID={08827D4A-F03C-4c07-8B21-1A66B88D2E9B}]
      Set Flag as E_NOT_OK
      [/cover] */
      ReturnValue = E_NOT_OK;
    }
    /* [cover parentID={8F216F9D-8347-4daf-85DB-47B00524726E}]*/
    /* Check if the buffer pointer is non-NULL */
    else if (DataBufferPtr == (uint8*) NULL_PTR)
    {
      /* [cover parentID={8F216F9D-8347-4daf-85DB-47B00524726E}]
Call FEE_E_PARAM_POINTER DET
[/cover] */
      Fee_lReportError(ApiId, FEE_E_PARAM_POINTER);

      /* [cover parentID={08827D4A-F03C-4c07-8B21-1A66B88D2E9B}]
      Set Flag as E_NOT_OK
      [/cover] */
      
      /* [cover parentID={08827D4A-F03C-4c07-8B21-1A66B88D2E9B}]
      Set Flag as E_NOT_OK
      [/cover] */
    
      ReturnValue = E_NOT_OK;
    }

    /* Check if the Length (from the given offset) is valid */
    /* [cover parentID={E2D729FE-30D6-44a7-A6B7-FD2B03DBBB7F}]*/
    else if ( ((uint32)BlockOffset + Length) > BlkSize )
    {

      Fee_lReportError(ApiId, FEE_E_INVALID_BLOCK_LEN);

      /* [cover parentID={08827D4A-F03C-4c07-8B21-1A66B88D2E9B}]
      Set Flag as E_NOT_OK
      [/cover] */
      ReturnValue = E_NOT_OK;
    }
    else
    {
      /* dummy else */
    }
  }
  return(ReturnValue);

} /*End of Fee_lReadDetSafetyCheck*/

/******************************************************************************
** Syntax : LOCAL_INLINE Std_ReturnType Fee_lCancelDetSafetyCheck(void)      **
**                                                                           **
**                                                                           **
**                                                                           **
** Service ID:                                                               **
**                                                                           **
** Sync/Async:  Synchronous                                                 **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) :  None                                                   **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  Std_ReturnType                                         **
**                    E_OK: Check Pass                                       **
**                    E_NOT_OK: Check Fail                                   **
** Description : Function will check configuration pointer against the null  **
** and module status. if check fails it will trigger DET/Safety Error and    **
** return E_NOT_OK                                                           **
******************************************************************************/
/*[cover parentID={DEE5A0C3-3D9A-4d4a-8649-C7FFA0F0C5BD}][/cover]*/
LOCAL_INLINE Std_ReturnType Fee_lCancelDetSafetyCheck(void)
{
  MemIf_StatusType   FeeStatus;
  Std_ReturnType     ReturnValue;

  
  /* [cover parentID={A8F80E20-A667-4bcf-BED4-73D9BC7BBE34}]
    DET enabled
    [/cover] */

  ReturnValue = E_OK;
  FeeStatus = Fee_lGetStatus();
  
  if(FeeStatus != MEMIF_BUSY)
  {
    
      
    
    Fee_lReportError(FEE_SID_CANCEL, FEE_E_INVALID_CANCEL);
    ReturnValue = E_NOT_OK;
  }
  return(ReturnValue);
} /*End of Fee_lCancelDetSafetyCheck*/

#endif

/*******************************************************************************
** TRACEABILITY: TBD                                                          **
**                                                                            **
** Syntax : LOCAL_INLINE void Fee_lHandleCancelNotification(void)             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **k
**
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Service to handle the cancel job notification. This function **
** is called from  Fee_JobErrorNotification                                   **
*******************************************************************************/
/*[cover parentID={ECCF5152-94AC-4ae0-8779-8E757F46D24F}][/cover]*/
LOCAL_INLINE void Fee_lHandleCancelNotification(void)
{
  Fee_StateDataType  *StateDataPtr;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)

  /* check if it is QS read/write/erase job */
  if(StateDataPtr->FeeQsJob != FEE_NO_JOB)
  {
    /* Call the Fee_lHandleQsJobFailure with  FEE_CANCEL to notify
    user about cancelled of job*/
    Fee_lHandleQsJobFailure(FEE_CANCEL);
  }
  else
#endif
  {
    /*Call the nvm error notification using Fee_lHandleUsrJobFailure
    to notify cancelled job*/

    /*If write job is cancelled then increase free page address to next
    but one WL. This will avoid write on same page for next write job*/
    if(Fee_lGetUserJob(StateDataPtr->FeePendReqStatus) == FEE_WRITE_JOB)
    {
      StateDataPtr->FeeNextFreePageAddr += StateDataPtr->FeeLastWriteSize;
      StateDataPtr->FeeNextFreePageAddr = Fee_lGetNextWLAddr(
                                            StateDataPtr->FeeNextFreePageAddr);
      StateDataPtr->FeeNextFreePageAddr += FEE_DFLASH_WORDLINE_SIZE;
      Fee_lHandleUsrJobFailure(FEE_CANCEL);
      StateDataPtr->FeeUserJobStatus = FEE_JOB_IDLE;
      StateDataPtr->FeeUserJobResult = FEE_JOB_FAIL;
    }
    else if(Fee_lGetUserJob(StateDataPtr->FeePendReqStatus)
            == FEE_READ_JOB)
    {
      Fee_lHandleUsrJobFailure(FEE_CANCEL);
      StateDataPtr->FeeUserJobStatus = FEE_JOB_IDLE;
      StateDataPtr->FeeUserJobResult = FEE_JOB_FAIL;
    }
    else
    {
      /* Internal job(GC related)is cancelled only reset internal
      variables NVM error notification is not needed for internal job*/
      StateDataPtr->FeeIntrJobStatus = FEE_JOB_DONE;
      StateDataPtr->FeeIntrJobResult = FEE_JOB_FAIL;
      StateDataPtr->FeeIntrJob = FEE_NO_JOB;
    }

  }
}  /* End of Fee_lHandleCancelNotification() */


/*******************************************************************************
** TRACEABILITY: TBD                                                          **
**                                                                            **
** Syntax : LOCAL_INLINE void Fee_lHandleUsrJobErrorNotification(             **
**                                           Fls_17_Dmu_Job_Type Job)         **
** [/cover]                                                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  Fls_17_Dmu_Job_Type Job: give the job type Write/Read   **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Service to handle the failed job notification. This function **
** is called from Fee_JobErrorNotification                                    **
*******************************************************************************/
/* [cover parentID={783AEE17-3F9A-4e7d-9F8B-287916DEA8FD},
{3A8E66AE-97FF-474d-9C6B-03FB9E8F4473}]
Fee_lHandleUsrJobErrorNotification
[/cover] */
LOCAL_INLINE void Fee_lHandleUsrJobErrorNotification(Fls_17_Dmu_Job_Type Job)
{
  /* [cover parentID={783AEE17-3F9A-4e7d-9F8B-287916DEA8FD}]*/
  Fee_StateDataType  *StateDataPtr;
  uint8               Error;
  uint16              BlockIndex;
  Fee_CacheType      *BlkPtr;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
#if (FEE_GET_PREV_DATA_API == STD_ON)
  Fee_PendReqBufType *PendReqPtr;
  PendReqPtr = &(StateDataPtr->FeePendReqInfo);
#endif
  if(Job == FEE_WRITE_JOB)
  {
    /* if job is write job */
    if(StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus ==
        (uint32)FEE_SET )
    {
      StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus = FEE_RESET;
      Error = FEE_INVALIDATE;
    }
    else
    {
      Error = FEE_WRITE;
    }

    /* Update Next Free Page Address to next but one WL  */
    StateDataPtr->FeeNextFreePageAddr += StateDataPtr->FeeLastWriteSize;

    StateDataPtr->FeeNextFreePageAddr = Fee_lGetNextWLAddr(
                                          StateDataPtr->FeeNextFreePageAddr);
    StateDataPtr->FeeNextFreePageAddr += FEE_DFLASH_WORDLINE_SIZE;


  }
  else /*if(job == FLS_READ_JOB)*/
  {
    /* job is read job */
    /* Update block state as Inconsistent in Cache */
    BlockIndex =
      Fee_lGetUsrBlockIndex(StateDataPtr->FeeCurrReqBlockNum);
    if(BlockIndex != FEE_LOG_BLOCK_NOT_FOUND )
    {
      BlkPtr = &(StateDataPtr->FeeBlockInfo[BlockIndex]);

#if (FEE_GET_PREV_DATA_API == STD_ON)
      if(PendReqPtr->GetPrevCopy == FEE_SET )
      {
        PendReqPtr->GetPrevCopy = FEE_RESET;
        BlkPtr->Status.PrevCopyConsistent = FEE_RESET;
      }
      else
#endif
      {
        BlkPtr->Status.Consistent = FEE_RESET;
        if(StateDataPtr->FeeCurrReqBlockNum ==
            StateDataPtr->FeeLastWrittenBlkInfo.BlockNumber)
        {
          StateDataPtr->FeeLastWrittenBlkInfo.Status.Consistent =
            FEE_RESET;
        }
      }
    }
    Error = FEE_READ;
  }

  Fee_lHandleUsrJobFailure(Error);

} /* End of Fee_lHandleUsrJobErrorNotification() */

/*******************************************************************************
** TRACEABILITY: TBD                                                          **
**                                                                            **
** Syntax : LOCAL_INLINE void Fee_lHandleReadJobEndNotification(Void)         **
** [/cover]                                                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Service to handle the Read job completed notification. This  **
** function is called from Fee_JobEndNotification                             **
*******************************************************************************/
/*[cover parentID={99174D42-6191-4f33-AD96-AC2AF1DB0CF9}][/cover]*/
LOCAL_INLINE void Fee_lHandleReadJobEndNotification(void)
{
  Fee_StateDataType  *StateDataPtr;
  uint16             DataByteCount;
  uint16             BlockOffset;
  uint16             Length;
  uint16             LoopIndex;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /* Is this last data set of block if yes then copy data into user buffer and
  trigger job completed notification if configured */
  if(StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_READ_NOTIF)
  {
    Length = StateDataPtr->FeePendReqInfo.Length;
    BlockOffset = StateDataPtr->FeePendReqInfo.BlockOffset;
    DataByteCount = FEE_ONE;

    /* Copy read data to user buffer */
    if(BlockOffset > FEE_ZERO)
    {
      while((BlockOffset < FEE_SEVEN) && (Length > FEE_ZERO))
      {

        StateDataPtr->FeePendReqInfo.DataBufferPtr[0] =
          StateDataPtr->FeeReadWriteBuffer[DataByteCount + BlockOffset];
        BlockOffset++;

        StateDataPtr->FeePendReqInfo.DataBufferPtr++;
        Length--;
      }
      DataByteCount += FEE_EIGHT;
    }
    while(DataByteCount < StateDataPtr->FeeLastReadSize)
    {
      for(LoopIndex = FEE_RESET;
          (LoopIndex < FEE_SEVEN) && (Length > FEE_ZERO);
          LoopIndex++)
      {

        StateDataPtr->FeePendReqInfo.DataBufferPtr[LoopIndex] =
          StateDataPtr->FeeReadWriteBuffer[DataByteCount + LoopIndex];
        Length--;
      }
      /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
            array indexing used for FEE application buffers.
            Pointers are accessing the correct memory range locations.
            The access range is within the boundaries of the buffer. */
      StateDataPtr->FeePendReqInfo.DataBufferPtr += FEE_SEVEN;
      DataByteCount += FEE_EIGHT;
    }
    /* [cover parentID={AF3250D3-AA49-4950-AD26-EEA51428ABB9}]
    Reset the pending request status and set the Fee job result
    to MEMIF_JOB_OK [/cover] */
    /*************   RESET JOB VARIABLES ******************/
    /* [cover parentID={AC80BD0C-E228-4020-AF90-282FD8EFC9A9}]*/

#if((FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA ) && \
    (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON))
    /*Check if QS erase was suspended. If yes then set FeePendReqStatus to
    FEE_REQ_QUASI_ERASE to set module status to busy.*/
    if(StateDataPtr->FeeQsEraseSuspend == FEE_ERASE_SUSPENDED)
    {
      StateDataPtr->FeePendReqStatus = FEE_REQ_QUASI_ERASE;
      StateDataPtr->FeeQsJob = FEE_ERASE_JOB;
    }
    else
#endif
    {
      StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_NO_REQ;
    }
  /* [cover parentID={AC80BD0C-E228-4020-AF90-282FD8EFC9A9}]
Set the Fee job result to MEMIF_JOB_OK
FeePendReqInfo.GetPrevCopy = FEE_ZERO
[/cover] */
    StateDataPtr->FeeJobResult = MEMIF_JOB_OK;
#if (FEE_GET_PREV_DATA_API == STD_ON)
    StateDataPtr->FeePendReqInfo.GetPrevCopy = FEE_RESET;
#endif
    /*****************************************************/
    /* [cover parentID={EA288A88-8827-4749-B1DB-2D9D779BB9DA}]*/
  /* [cover parentID={EA288A88-8827-4749-B1DB-2D9D779BB9DA}]
NVM data block supported
[/cover] */
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
    /* [cover parentID={1F1E8365-8DFB-4a44-BAF9-12C4871659B7}]
        Call NVM Job end notification function
        [/cover] */
    /* [cover parentID={9515D550-3494-4e38-9569-591E0716E944}]
       Check for notification function
       [/cover] */
    /* Call user configured job End notification */
    /* [cover parentID={1F1E8365-8DFB-4a44-BAF9-12C4871659B7}]*/
    if ( Fee_CfgPtr->FeeNvmJobEndNotification != NULL_PTR )
    {
      (Fee_CfgPtr->FeeNvmJobEndNotification)();
    }
#endif
  }

} /* Emd of Fee_lHandleReadJobEndNotification() */

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lMainGCHdlr(void)                           **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function determines and performs the action required for**
** GC .This function is called from main function  in FEE_MAIN_GC state. This **
*******************************************************************************/
/*[cover parentID={97BA7538-907D-47b5-96EC-5905C1F50E27}][/cover]*/
LOCAL_INLINE void Fee_lMainGCHdlr(void)
{

#if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
  Fee_StateDataType  *StateDataPtr;
#else
  const Fee_StateDataType  *StateDataPtr;
#endif
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
#if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
  if(FEE_ERASE_NOT_SUSPENDED == StateDataPtr->FeeEraseSuspendStatus)
  {
#endif
    if(StateDataPtr->FeeIntrJobStatus != FEE_JOB_REQSTD)
    {
      Fee_lGarbageCollection();
    }
#if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
  }
  else
  {
    if(StateDataPtr->FeeEraseSuspendStatus < FEE_RESUME_ERASE_LIMIT)
    {
      /* [cover parentID={80C27FFF-BC04-4758-B6E5-3696C361C36F}]
Resume erase operation
[/cover] */
      if(E_OK == Fls_17_Dmu_ResumeErase())
      {
        StateDataPtr->FeeEraseSuspendStatus = FEE_ERASE_NOT_SUSPENDED;
      }
      else
      {
        StateDataPtr->FeeEraseSuspendStatus++;
        if(FEE_RESET == StateDataPtr->FeeEraseResumeDemReported)
        { /* [cover parentID={9E85D234-B457-4074-B933-C9C6DA3043BA}]
Check for erase suspend status
[/cover] */
          if(FEE_RESUME_ERASE_LIMIT ==
              StateDataPtr->FeeEraseSuspendStatus)
          {
            /* Erased failed raise the illegal notification.block index 
            parameter is not used for erase error,so passed as parameter not 
            used.Block index is used only for read error to drop the block 
            from GC process. */
            Fee_lGCErrorHandler(FEE_GC_ERASE, FEE_UNUSED_PARAM);
          }
        }
      }
    }
  }
#endif
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lHandleGcCopy(void)                         **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Uint8 : GC error code                                   **
**                    FEE_GC_WRITE : GC write operation failed.               **
**                    FEE_GC_READ : GC Read operation failed.                 **
** Description : This function handle the GC read , write operation as per GS **
** state . This function is called from Fee_lGarbageCollection function.      **
*******************************************************************************/
LOCAL_INLINE  uint8 Fee_lHandleGcCopy(void)
{
  const Fee_StateDataType  *StateDataPtr;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  uint8                  Error;
  Error = FEE_GC_E_OK;

  /********* FEE_GC_UNCFG_START_COPY *******/
  /*  Reading the first page of an Unconfig block is done here */
  if(StateDataPtr->FeeGcState == FEE_GC_UNCFG_START_COPY)
  {
    Fee_lGcStartCopy();

  }

  /*********** FEE_GC_UNCFG_COPY_WRITE *******************/
  /* [cover parentID={78F787F6-47A6-4077-9E99-7681FB79AD9A}]
Check if GC has to start to write unconfig block
[/cover] */
  /*  Writing a page of an unconfigure block is done here */
  if(StateDataPtr->FeeGcState == FEE_GC_UNCFG_COPY_WRITE)
  {
    Error = Fee_lGcStartCopyWrite();
  }

  /*********** FEE_GC_UNCFG_COPY_READ_NXTPAGE *******************/
  /*  Reading the subsequent pages of an Unconfigure block is done here */
  if(StateDataPtr->FeeGcState == FEE_GC_UNCFG_COPY_READ_NXTPAGE)
  {
    Fee_lGcCopyReadNxtPage();

  }


  /*********** FEE_GC_START_COPY *******************/
  /* [cover parentID={9125A3B6-EBF3-4c87-BB26-7DBDCC8511FA}]
Check if GC has to start copying unconfig blocks
[/cover] */
  /*  Reading the first page of a Configure block is done here */
  if(StateDataPtr->FeeGcState == FEE_GC_START_COPY)
  {
    Fee_lGcStartCopy();

  }


  /*********** FEE_GC_COPY_WRITE *******************/
  /*  Writing a page of a Configure block is done here */
  if(StateDataPtr->FeeGcState == FEE_GC_COPY_WRITE)
  {
    Error = Fee_lGcStartCopyWrite();
  }


  /*********** FEE_GC_COPY_READ_NXTPAGE *******************/
  /*  Reading the subsequent pages of a Configure block is done here */
  if(StateDataPtr->FeeGcState == FEE_GC_COPY_READ_NXTPAGE)
  {
    Fee_lGcCopyReadNxtPage();

  }

  /*********** FEE_GC_MARK_SECTOR1_V_SP *******************/
  /*  Writing the valid state page content is done here */
  if(StateDataPtr->FeeGcState == FEE_GC_MARK_SECTOR1_V_SP)
  {
    Error = Fee_lGcProgramStatePage(FEE_GC_MARK_SECTOR1_V_SP);
  }


  /*********** FEE_GC_MARK_SECTOR1_V_M *******************/
  /*  Writing the valid state page marker is done here */
  if(StateDataPtr->FeeGcState == FEE_GC_MARK_SECTOR1_V_M)
  {
    Error = Fee_lGcProgramStatePage(FEE_GC_MARK_SECTOR1_V_M);
  }

  return(Error);
}

#if (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)

/*******************************************************************************
** Syntax : Std_ReturnType  Fee_lIsQsWriteReadAllowed(void)                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  boolean : GC error code                                 **
**                    TRUE : QS Read/Write is allowed                         **
**                    FALSE :QS Read/Write is not allowed .                   **
** Description : This function will check if there Qs write or read is        **
** pending and can be executed                                                **
*******************************************************************************/
/* [cover parentID={45200610-4BB9-47b9-8FA8-69777362FF35}]
Fee_lIsQsWriteReadAllowedbyGC
[/cover] */
static boolean Fee_lIsQsWriteReadAllowedbyGC(void)
{
#if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
  Fee_StateDataType *StateDataPtr;
  Std_ReturnType     FlsRetVal;

#else
  const Fee_StateDataType *StateDataPtr;
#endif
  boolean            RetVal;

  RetVal = (boolean)FALSE;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  if((StateDataPtr->FeePendReqStatus == FEE_REQ_QUASI_WRITE) ||
      (StateDataPtr->FeePendReqStatus == FEE_REQ_QUASI_READ))
  {
    /*Check if GC in erase state as part of normal GC opertaion.Pending request 
    can not be executed when GC in erase state as part init GC beacuse of cache
    table is not yet build and initializtion activity is not finished */
    if(StateDataPtr->FeeGcState == FEE_GC_ERASE_PREV_SECTOR) 
    {
      if(StateDataPtr->FeeIntrJobStatus == FEE_JOB_REQSTD)
      {
        /*Check if erase operation can be suspended*/
#if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
        if(Fee_CfgPtr->FeeGCConfigSetting.FeeUseEraseSuspend ==
            (uint32)FEE_ERASE_SUSPEND_ENABLED)
        {
          if(FEE_ERASE_NOT_SUSPENDED == StateDataPtr->FeeEraseSuspendStatus)
          {
            FlsRetVal = Fls_17_Dmu_SuspendErase();
            if(E_OK == FlsRetVal)
            {
              RetVal = (boolean)TRUE;
              StateDataPtr->FeeEraseSuspendStatus = FEE_ERASE_SUSPENDED;
            }

          }
          else
          {
            RetVal = (boolean)TRUE;
            StateDataPtr->FeeEraseSuspendStatus = FEE_ERASE_SUSPENDED;
          }
        }
#endif

      }
      else
      {
        /*Erase is not started or finshed. QS request can be executed*/
        RetVal = (boolean)TRUE;

      }
    }
  }

  return(RetVal);

}

#endif

#endif

/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* Memory Map of the FEE Code */
#define FEE_STOP_SEC_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"

#define FEE_START_SEC_ERASEERRORNOTI_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"


/*******************************************************************************
** TRACEABILITY: TBD                                                          **
**                                                                            **
** Syntax : void Fee_17_JobEraseErrorNotification(void)                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x29                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Service to report to FEE module the failure of an  Erase     **
** operation and EVR(Erase Verify ) Error occurred.                           **
*******************************************************************************/
/* [cover parentID={F0283E12-60D5-4eef-B6EE-538CD842131D}]
Fee_17_JobEraseErrorNotification
[/cover] */
void Fee_17_JobEraseErrorNotification(void)
{
  /* [cover parentID={436E0729-5394-4d12-97E0-CF59109131FF}]*/

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
  Fls_17_Dmu_Job_Type Job;
  Fee_StateDataType  *StateDataPtr;
#else
  const Fee_StateDataType  *StateDataPtr;
#endif
/* [cover parentID={039EA806-07C1-488a-886B-B0799058E979}]
SAFETY ENABLE
[/cover] */
#if (FEE_SAFETY_ENABLE == STD_ON)
  if(Fee_CfgPtr != NULL_PTR)
#endif
  {
    StateDataPtr = Fee_CfgPtr->FeeStatePtr;

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
    Job = Fls_17_Dmu_GetNotifCaller();
    if(Job == StateDataPtr->FeeIntrJob)
    {
      /* GC Erase is operation is failed.(Internal Operation) */
      StateDataPtr->FeeIntrJobStatus = FEE_JOB_DONE;
      StateDataPtr->FeeIntrJobResult = FEE_JOB_FAIL;
      StateDataPtr->FeeIntrJob = FEE_NO_JOB;
      StateDataPtr->FeeEraseVerErr = FEE_SET ;
    }
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
    else
    {
      if(StateDataPtr->FeeQsJob != FEE_NO_JOB)
      {
        Fee_lHandleQsJobFailure((~FEE_CANCEL));
      }

    }
#endif

#else
    if(StateDataPtr->FeeQsJob != FEE_NO_JOB)
    {
      Fee_lHandleQsJobFailure((~FEE_CANCEL));
    }
#endif
    
  }
#if(FEE_SAFETY_ENABLE == STD_ON)
  else
  { 
   /* [cover parentID={0123A4A1-A624-4c22-A827-E1334FE6BFEF}]
Report error FEE_E_UNINIT
[/cover] */
    Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                           FEE_SID_JOBERASEERRORNOTIF, FEE_E_UNINIT);
  }
#endif

}

#define FEE_STOP_SEC_ERASEERRORNOTI_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"



#define FEE_START_SEC_PROGERRORNOTI_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"


/*******************************************************************************
** TRACEABILITY: TBD                                                          **
**                                                                            **
** Syntax : void Fee_17_JobProgErrorNotification(void)                        **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x31                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Service to report to FEE module if Program Verify Error      **
**  occurred while programming/writing.                                       **
*******************************************************************************/
/* [cover parentID={ABEBA1F6-6119-4326-9549-FB898E5A4E86},
{2B346D07-6920-4f9c-90AC-DA91AD86E39E}]
Fee_17_JobProgErrorNotification
[/cover] */
/* [cover parentID={828AE813-7199-4dd4-A7F7-A89D3FB90B98}]
Program verify error notfication
[/cover] */
void Fee_17_JobProgErrorNotification(void)
{

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
  Fls_17_Dmu_Job_Type Job;
#endif
   Fee_StateDataType  *StateDataPtr;
/* [cover parentID={8647E160-A868-4483-AD03-7DABDE73F7C7}]
Safety is enabled
[/cover] */
#if (FEE_SAFETY_ENABLE == STD_ON)
  if(Fee_CfgPtr != NULL_PTR)
#endif
  {
    StateDataPtr = Fee_CfgPtr->FeeStatePtr;

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
    Job = Fls_17_Dmu_GetNotifCaller();
    if(Job == StateDataPtr->FeeIntrJob)
    {
      /* GC Write operation is failed.(Internal Operation) */
      StateDataPtr->FeeIntrJobStatus = FEE_JOB_DONE;
      StateDataPtr->FeeIntrJobResult = FEE_JOB_FAIL;
      StateDataPtr->FeeIntrJob = FEE_NO_JOB;
      StateDataPtr->FeeProgVerErr = FEE_SET ;
    }
    else if( Job == Fee_lGetUserJob(StateDataPtr->FeePendReqStatus))
    {
      /* User write Job is failed  */
      StateDataPtr->FeeUserJobStatus = FEE_JOB_DONE;
      StateDataPtr->FeeUserJobResult = FEE_JOB_FAIL; 
      StateDataPtr->FeeProgVerErr = FEE_SET ; 
    }
    else
    {
      /*Check if the Qs job is on going.*/
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
      if(StateDataPtr->FeeQsJob != FEE_NO_JOB)
      {
        
        /*Check if erase started marker or destroying of all marker write failed
        in this case ignore the error and continue. All other case raise the 
        job error notification.*/
        if((StateDataPtr->FeeQsJob == FEE_ERASE_JOB ) && 
        ((StateDataPtr->FeeQsState == (uint8)FEE_QS_PROG_STATE_ERASE_STARTED )||
        (StateDataPtr->FeeQsState == (uint8)FEE_QS_PROG_STATE_DESTROY)))
        {
          /*Reset the StateDataPtr->FeeQsJobStatus to idle.So Fee_lMainQs
          get served*/  
          StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
        }
        else
        {
           Fee_lHandleQsJobFailure((~FEE_CANCEL));
        }
     
      }
#endif
    }


#else
    if(StateDataPtr->FeeQsJob != FEE_NO_JOB)
    {
      /*Check if erase started marker or destroying of all marker write failed
      in this case ignore the error and continue. All other case raise the 
      job error notification.*/
      if((StateDataPtr->FeeQsJob == FEE_ERASE_JOB ) && 
        ((StateDataPtr->FeeQsState == (uint8)FEE_QS_PROG_STATE_ERASE_STARTED) ||
        (StateDataPtr->FeeQsState == (uint8)FEE_QS_PROG_STATE_DESTROY)))
      {
        /*Reset the StateDataPtr->FeeQsJobStatus to idle.So Fee_lMainQs
        get served*/  
        StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
      }
      else
      {
         Fee_lHandleQsJobFailure((~FEE_CANCEL));
      }
    }
#endif
    
  }
#if(FEE_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={83CC42E0-B3A9-41a3-B6FC-2ADDB075E8B8}]
Report safety error with FEE_E_UNINIT
[/cover] */
    Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID,
                           FEE_SID_JOBPROGERRORNOTIF, FEE_E_UNINIT);
  }
#endif

}

#define FEE_STOP_SEC_PROGERRORNOTI_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"
