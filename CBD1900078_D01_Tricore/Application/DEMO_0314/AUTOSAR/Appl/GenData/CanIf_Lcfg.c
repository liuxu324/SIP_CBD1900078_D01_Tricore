/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: CanIf
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: Aurix 2G/TC397 B-Step
 *    License Scope : The usage is restricted to CBD1900078_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: CanIf_Lcfg.c
 *   Generation Time: 2024-12-18 22:20:50
 *           Project: TC397START - Version 1.0
 *          Delivery: CBD1900078_D01
 *      Tool Version: DaVinci Configurator (beta) 5.18.42 SP2
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 ! BETA VERSION                                                                                                       !
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 ! This version of DaVinci Configurator Pro and/or the related Basic Software Package is BETA software.               !
 ! BETA Software is basically operable, but not sufficiently tested, verified and/or qualified for use in series      !
 ! production and/or in vehicles operating on public or non-public roads.                                             !
 ! In particular, without limitation, BETA Software may cause unpredictable ECU behavior, may not provide all         !
 ! functions necessary for use in series production and/or may not comply with quality requirements which are         !
 ! necessary according to the state of the art. BETA Software must not be used in series production.                  !
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
**********************************************************************************************************************/

#define CANIF_LCFG_SOURCE

/* PRQA S 0850 EOF */ /* MD_MSR_19.8 */
/* PRQA S 0857 EOF */ /* MD_CanIf_1.1_NumberOfMacroDefinitions */
/* PRQA S 0779 EOF */ /* MD_CanIf_5.1 */
/* PRQA S 0777 EOF */ /* MD_CanIf_5.1 */
/* PRQA S 1330, 1334 EOF */ /* MD_CanIf_16.4, MD_CanIf_16.4 */

/**********************************************************************************************************************
  \file  Includes
**********************************************************************************************************************/
/** 
  \brief  Required external files.
*/ 

#include "CanIf_Cfg.h"

 /*  CanNm Header Files  */ 
#include "CanNm_Cfg.h"
#include "CanNm_Cbk.h"
 /*  CanTp Header Files  */ 
#include "CanTp_Cfg.h"
#include "CanTp_Cbk.h"
 /*  PduR Header Files  */ 
#include "PduR_Cfg.h"
#include "PduR_CanIf.h"
 /*  CanSM Header Files  */ 
#include "CanSM_Cbk.h"

#define CANIF_START_SEC_APPL_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

/**********************************************************************************************************************
  \var  Prototypes of callback functions
**********************************************************************************************************************/

/** 
  \brief  Tx confirmation functions.
*/



/** 
  \brief  Rx indication functions.
*/





#define CANIF_STOP_SEC_APPL_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

/**********************************************************************************************************************
  ComStackLib
**********************************************************************************************************************/
/**********************************************************************************************************************
  LOCAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/


/**********************************************************************************************************************
  LOCAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: LOCAL DATA
**********************************************************************************************************************/


/**********************************************************************************************************************
  GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  CanIf_BusOffNotificationFctPtr
**********************************************************************************************************************/
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(CanIf_BusOffNotificationFctType, CANIF_CONST) CanIf_BusOffNotificationFctPtr = CanSM_ControllerBusOff;
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_CanIfCtrlId2MappedTxBuffersConfig
**********************************************************************************************************************/
/** 
  \var    CanIf_CanIfCtrlId2MappedTxBuffersConfig
  \brief  CAN controller configuration - mapped Tx-buffer(s).
  \details
  Element                          Description
  MappedTxBuffersConfigEndIdx      the end index of the 1:n relation pointing to CanIf_MappedTxBuffersConfig
  MappedTxBuffersConfigStartIdx    the start index of the 1:n relation pointing to CanIf_MappedTxBuffersConfig
*/ 
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(CanIf_CanIfCtrlId2MappedTxBuffersConfigType, CANIF_CONST) CanIf_CanIfCtrlId2MappedTxBuffersConfig[2] = {
    /* Index    MappedTxBuffersConfigEndIdx                                                                      MappedTxBuffersConfigStartIdx                                                                            Referable Keys */
  { /*     0 */                         1uL  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN00_9df8a959 */,                           0uL  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN00_9df8a959 */ },  /* [/ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN00_9df8a959] */
  { /*     1 */                         2uL  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN01_eaff99cf */,                           1uL  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN01_eaff99cf */ }   /* [/ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN01_eaff99cf] */
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_CtrlModeIndicationFctPtr
**********************************************************************************************************************/
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(CanIf_CtrlModeIndicationFctType, CANIF_CONST) CanIf_CtrlModeIndicationFctPtr = CanSM_ControllerModeIndication;
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_MailBoxConfig
**********************************************************************************************************************/
/** 
  \var    CanIf_MailBoxConfig
  \brief  Mailbox table.
  \details
  Element                 Description
  CtrlStatesIdx           the index of the 1:1 relation pointing to CanIf_CtrlStates
  PduIdFirst              "First" PDU mapped to mailbox.
  PduIdLast               "Last" PDU mapped to mailbox.
  TxBufferCfgIdx          the index of the 0:1 relation pointing to CanIf_TxBufferPrioByCanIdByteQueueConfig
  TxBufferHandlingType
  MailBoxType             Type of mailbox: Rx-/Tx- BasicCAN/FullCAN/unused.
*/ 
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(CanIf_MailBoxConfigType, CANIF_CONST) CanIf_MailBoxConfig[5] = {
    /* Index    CtrlStatesIdx                                                                      PduIdFirst                           PduIdLast                           TxBufferCfgIdx                                                                              TxBufferHandlingType                     MailBoxType                    Referable Keys */
  { /*     0 */           0uL  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN00_9df8a959 */,         0u  /* Unused, TxPduId 0 */,        0u  /* Unused, TxPduId 5 */,                                    0uL  /* /ActiveEcuC/CanIf/CanIfInitCfg/CHNL_0fb271d2 */, CANIF_TXBUFFER_HANDLINGTYPE_PRIOBYCANID, CANIF_TxBasicCANMailbox },  /* [/ActiveEcuC/Can/CanConfigSet/CN_CAN00_5e566ad9_Tx] */
  { /*     1 */           0uL  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN00_9df8a959 */,         1u  /* RxPduId */          ,        5u  /* RxPduId  */         , CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG  /* unusedIndex1 */                                , CANIF_TXBUFFER_HANDLINGTYPE_NONE       , CANIF_RxBasicCANMailbox },  /* [/ActiveEcuC/Can/CanConfigSet/CN_CAN00_4240a648_Rx] */
  { /*     2 */           0uL  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN00_9df8a959 */,         0u  /* Unused object */    ,        0u  /* Unused object */    , CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG  /* unusedIndex2 */                                , CANIF_TXBUFFER_HANDLINGTYPE_NONE       , CANIF_UnusedCANMailbox  },  /* [/ActiveEcuC/Can/CanConfigSet/CN_CAN00_770af0b0_Rx] */
  { /*     3 */           1uL  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN01_eaff99cf */,         0u  /* Unused, TxPduId 6 */,        0u  /* Unused, TxPduId 6 */,                                    1uL  /* /ActiveEcuC/CanIf/CanIfInitCfg/CHNL_c4eea277 */, CANIF_TXBUFFER_HANDLINGTYPE_PRIOBYCANID, CANIF_TxBasicCANMailbox },  /* [/ActiveEcuC/Can/CanConfigSet/CN_CAN01_29515a4f_Tx] */
  { /*     4 */           1uL  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN01_eaff99cf */,         6u  /* RxPduId */          ,        6u  /* RxPduId  */         , CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG  /* unusedIndex4 */                                , CANIF_TXBUFFER_HANDLINGTYPE_NONE       , CANIF_RxBasicCANMailbox }   /* [/ActiveEcuC/Can/CanConfigSet/CN_CAN01_ad82cd76_Rx] */
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_MappedTxBuffersConfig
**********************************************************************************************************************/
/** 
  \var    CanIf_MappedTxBuffersConfig
  \brief  Mapped Tx-buffer(s)
  \details
  Element             Description
  MailBoxConfigIdx    the index of the 1:1 relation pointing to CanIf_MailBoxConfig
*/ 
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(CanIf_MappedTxBuffersConfigType, CANIF_CONST) CanIf_MappedTxBuffersConfig[2] = {
    /* Index    MailBoxConfigIdx                                                                 Referable Keys */
  { /*     0 */              0uL  /* /ActiveEcuC/Can/CanConfigSet/CN_CAN00_5e566ad9_Tx */ },  /* [/ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN00_9df8a959] */
  { /*     1 */              3uL  /* /ActiveEcuC/Can/CanConfigSet/CN_CAN01_29515a4f_Tx */ }   /* [/ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN01_eaff99cf] */
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_RxIndicationFctList
**********************************************************************************************************************/
/** 
  \var    CanIf_RxIndicationFctList
  \brief  Rx indication functions table.
  \details
  Element               Description
  RxIndicationFct       Rx indication function.
  RxIndicationLayout    Layout of Rx indication function.
*/ 
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(CanIf_RxIndicationFctListType, CANIF_CONST) CanIf_RxIndicationFctList[4] = {
    /* Index    RxIndicationFct                                               RxIndicationLayout                                                            Referable Keys */
  { /*     0 */  { (CanIf_SimpleRxIndicationFctType)NULL_PTR }              , CanIf_SimpleRxIndicationLayout    /* PRQA S 313 */ /* MD_CanIf_11.1 */ },  /* [NULL_PTR] */
  { /*     1 */  { (CanIf_SimpleRxIndicationFctType)CanNm_RxIndication }    , CanIf_AdvancedRxIndicationLayout  /* PRQA S 313 */ /* MD_CanIf_11.1 */ },  /* [CanNm_RxIndication] */
  { /*     2 */  { (CanIf_SimpleRxIndicationFctType)CanTp_RxIndication }    , CanIf_AdvancedRxIndicationLayout  /* PRQA S 313 */ /* MD_CanIf_11.1 */ },  /* [CanTp_RxIndication] */
  { /*     3 */  { (CanIf_SimpleRxIndicationFctType)PduR_CanIfRxIndication }, CanIf_AdvancedRxIndicationLayout  /* PRQA S 313 */ /* MD_CanIf_11.1 */ }   /* [PduR_CanIfRxIndication] */
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_RxPduConfig
**********************************************************************************************************************/
/** 
  \var    CanIf_RxPduConfig
  \brief  Rx-PDU configuration table.
  \details
  Element                   Description
  RxPduCanId                Rx-PDU: CAN identifier.
  RxPduMask                 Rx-PDU: CAN identifier mask.
  UpperPduId                PDU ID defined by upper layer.
  Dlc                       Data length code.
  RxIndicationFctListIdx    the index of the 1:1 relation pointing to CanIf_RxIndicationFctList
*/ 
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(CanIf_RxPduConfigType, CANIF_CONST) CanIf_RxPduConfig[7] = {
    /* Index    RxPduCanId                                                                        RxPduMask                                                         UpperPduId                                  Dlc  RxIndicationFctListIdx                                      Comment                                                                       Referable Keys */
  { /*     0 */ 0x00000400uL  /* Lower CanId of range: MyECU_f835e395_Rx, 2.0- or FD-PDU */     , 0x6000043FuL  /* Upper CanId of range: MyECU_f835e395_Rx */     , CanNmConf_CanNmRxPdu_CAN00_CAN_5faa4e95_Rx,  8u,                    1uL  /* CanNm_RxIndication */     },  /* [PDU: MyECU_f835e395_Rx, Lower CanId of range: 0x400]             */  /* [CanIfConf_CanIfRxPduCfg_MyECU_f835e395_Rx] */
  { /*     1 */ 0x98DBFFF9uL  /* msg_Receive_Extend_1_oCAN00_8798d8dc_Rx, 2.0- or FD-PDU */     , 0x9FFFFFFFuL  /* msg_Receive_Extend_1_oCAN00_8798d8dc_Rx */     , PduRConf_PduRSrcPdu_PduRSrcPdu_f20a19ef   ,  1u,                    3uL  /* PduR_CanIfRxIndication */ },  /* [PDU: msg_Receive_Extend_1_oCAN00_8798d8dc_Rx, CanId: 0x18dbfff9] */  /* [CanIfConf_CanIfRxPduCfg_msg_Receive_Extend_1_oCAN00_8798d8dc_Rx] */
  { /*     2 */ 0x00000614uL  /* msg_diag_RequestGlobal_Tp_oCAN00_5c56b065_Rx, 2.0- or FD-PDU */, 0x000007FFuL  /* msg_diag_RequestGlobal_Tp_oCAN00_5c56b065_Rx */, CanTpConf_CanTpRxNPdu_CanTpRxNPdu_55155daa,  8u,                    2uL  /* CanTp_RxIndication */     },  /* [PDU: msg_diag_RequestGlobal_Tp_oCAN00_5c56b065_Rx, CanId: 0x614] */  /* [CanIfConf_CanIfRxPduCfg_msg_diag_RequestGlobal_Tp_oCAN00_5c56b065_Rx] */
  { /*     3 */ 0x00000610uL  /* msg_diag_Request_MyECU_Tp_oCAN00_2c5ccddc_Rx, 2.0- or FD-PDU */, 0x000007FFuL  /* msg_diag_Request_MyECU_Tp_oCAN00_2c5ccddc_Rx */, CanTpConf_CanTpRxNPdu_CanTpRxNPdu_7fe257d9,  8u,                    2uL  /* CanTp_RxIndication */     },  /* [PDU: msg_diag_Request_MyECU_Tp_oCAN00_2c5ccddc_Rx, CanId: 0x610] */  /* [CanIfConf_CanIfRxPduCfg_msg_diag_Request_MyECU_Tp_oCAN00_2c5ccddc_Rx] */
  { /*     4 */ 0x00000211uL  /* msg_Receive_1_oCAN00_c6c44320_Rx, 2.0- or FD-PDU */            , 0x000007FFuL  /* msg_Receive_1_oCAN00_c6c44320_Rx */            , PduRConf_PduRSrcPdu_PduRSrcPdu_2f777849   ,  1u,                    3uL  /* PduR_CanIfRxIndication */ },  /* [PDU: msg_Receive_1_oCAN00_c6c44320_Rx, CanId: 0x211]             */  /* [CanIfConf_CanIfRxPduCfg_msg_Receive_1_oCAN00_c6c44320_Rx] */
  { /*     5 */ 0x00000210uL  /* msg_Receive_oCAN00_76f25845_Rx, 2.0- or FD-PDU */              , 0x000007FFuL  /* msg_Receive_oCAN00_76f25845_Rx */              , PduRConf_PduRSrcPdu_PduRSrcPdu_16740ed0   ,  1u,                    3uL  /* PduR_CanIfRxIndication */ },  /* [PDU: msg_Receive_oCAN00_76f25845_Rx, CanId: 0x210]               */  /* [CanIfConf_CanIfRxPduCfg_msg_Receive_oCAN00_76f25845_Rx] */
  { /*     6 */ 0x98DBFFF8uL  /* msg_Receive_Extend_2_oCAN01_3b324635_Rx, 2.0- or FD-PDU */     , 0xDFFFFFFFuL  /* msg_Receive_Extend_2_oCAN01_3b324635_Rx */     , PduRConf_PduRSrcPdu_PduRSrcPdu_5a39f2bb   ,  1u,                    3uL  /* PduR_CanIfRxIndication */ }   /* [PDU: msg_Receive_Extend_2_oCAN01_3b324635_Rx, CanId: 0x18dbfff8] */  /* [CanIfConf_CanIfRxPduCfg_msg_Receive_Extend_2_oCAN01_3b324635_Rx] */
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_TxBufferPrioByCanIdByteQueueConfig
**********************************************************************************************************************/
/** 
  \var    CanIf_TxBufferPrioByCanIdByteQueueConfig
  \brief  Tx-buffer: PRIO_BY_CANID as BYTE_QUEUE
  \details
  Element                                             Description
  TxBufferPrioByCanIdBaseIdx                          the index of the 1:1 relation pointing to CanIf_TxBufferPrioByCanIdBase
  TxBufferPrioByCanIdByteQueueMappedTxPdusEndIdx      the end index of the 1:n relation pointing to CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus
  TxBufferPrioByCanIdByteQueueMappedTxPdusLength      the number of relations pointing to CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus
  TxBufferPrioByCanIdByteQueueMappedTxPdusStartIdx    the start index of the 1:n relation pointing to CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus
*/ 
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(CanIf_TxBufferPrioByCanIdByteQueueConfigType, CANIF_CONST) CanIf_TxBufferPrioByCanIdByteQueueConfig[2] = {
    /* Index    TxBufferPrioByCanIdBaseIdx                                                      TxBufferPrioByCanIdByteQueueMappedTxPdusEndIdx                                                      TxBufferPrioByCanIdByteQueueMappedTxPdusLength                                                      TxBufferPrioByCanIdByteQueueMappedTxPdusStartIdx                                                            Referable Keys */
  { /*     0 */                        0uL  /* /ActiveEcuC/CanIf/CanIfInitCfg/CHNL_0fb271d2 */,                                            6uL  /* /ActiveEcuC/CanIf/CanIfInitCfg/CHNL_0fb271d2 */,                                            6uL  /* /ActiveEcuC/CanIf/CanIfInitCfg/CHNL_0fb271d2 */,                                              0uL  /* /ActiveEcuC/CanIf/CanIfInitCfg/CHNL_0fb271d2 */ },  /* [/ActiveEcuC/CanIf/CanIfInitCfg/CHNL_0fb271d2] */
  { /*     1 */                        1uL  /* /ActiveEcuC/CanIf/CanIfInitCfg/CHNL_c4eea277 */,                                            7uL  /* /ActiveEcuC/CanIf/CanIfInitCfg/CHNL_c4eea277 */,                                            1uL  /* /ActiveEcuC/CanIf/CanIfInitCfg/CHNL_c4eea277 */,                                              6uL  /* /ActiveEcuC/CanIf/CanIfInitCfg/CHNL_c4eea277 */ }   /* [/ActiveEcuC/CanIf/CanIfInitCfg/CHNL_c4eea277] */
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus
**********************************************************************************************************************/
/** 
  \var    CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus
  \brief  Tx-buffer: PRIO_BY_CANID as BYTE_QUEUE: Mapped Tx-PDUs
  \details
  Element           Description
  TxPduConfigIdx    the index of the 1:1 relation pointing to CanIf_TxPduConfig
*/ 
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdusType, CANIF_CONST) CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus[7] = {
    /* Index    TxPduConfigIdx                                                                                            Referable Keys */
  { /*     0 */            0uL  /* /ActiveEcuC/CanIf/CanIfInitCfg/msg_Transmit_Extended1_oCAN00_f3b05f8f_Tx */     },  /* [/ActiveEcuC/CanIf/CanIfInitCfg/CHNL_0fb271d2] */
  { /*     1 */            1uL  /* /ActiveEcuC/CanIf/CanIfInitCfg/msg_diag_Response_MyECU_Tp_oCAN00_59e48f7a_Tx */ },  /* [/ActiveEcuC/CanIf/CanIfInitCfg/CHNL_0fb271d2] */
  { /*     2 */            2uL  /* /ActiveEcuC/CanIf/CanIfInitCfg/msg_MyECU_Lamp_oCAN00_41befc25_Tx */             },  /* [/ActiveEcuC/CanIf/CanIfInitCfg/CHNL_0fb271d2] */
  { /*     3 */            3uL  /* /ActiveEcuC/CanIf/CanIfInitCfg/msg_nm_MyECU_oCAN00_dfbc2140_Tx */               },  /* [/ActiveEcuC/CanIf/CanIfInitCfg/CHNL_0fb271d2] */
  { /*     4 */            4uL  /* /ActiveEcuC/CanIf/CanIfInitCfg/msg_Transmit_Copy_1_oCAN00_990cfc00_Tx */        },  /* [/ActiveEcuC/CanIf/CanIfInitCfg/CHNL_0fb271d2] */
  { /*     5 */            5uL  /* /ActiveEcuC/CanIf/CanIfInitCfg/msg_Transmit_oCAN00_29db34a4_Tx */               },  /* [/ActiveEcuC/CanIf/CanIfInitCfg/CHNL_0fb271d2] */
  { /*     6 */            6uL  /* /ActiveEcuC/CanIf/CanIfInitCfg/msg_Transmit_Extended2_oCAN01_f0f4fa20_Tx */     }   /* [/ActiveEcuC/CanIf/CanIfInitCfg/CHNL_c4eea277] */
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_TxConfirmationFctList
**********************************************************************************************************************/
/** 
  \var    CanIf_TxConfirmationFctList
  \brief  Tx confirmation functions table.
*/ 
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(CanIf_TxConfirmationFctType, CANIF_CONST) CanIf_TxConfirmationFctList[4] = {
  /* Index     TxConfirmationFctList                      Referable Keys */
  /*     0 */ (CanIf_TxConfirmationFctType)NULL_PTR ,  /* [NULL_PTR] */
  /*     1 */ CanNm_TxConfirmation                  ,  /* [CanNm_TxConfirmation] */
  /*     2 */ CanTp_TxConfirmation                  ,  /* [CanTp_TxConfirmation] */
  /*     3 */ PduR_CanIfTxConfirmation                 /* [PduR_CanIfTxConfirmation] */
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_TxPduConfig
**********************************************************************************************************************/
/** 
  \var    CanIf_TxPduConfig
  \brief  Tx-PDUs - configuration.
  \details
  Element                     Description
  CanId                       CAN identifier (16bit / 32bit).
  UpperLayerTxPduId           Upper layer handle ID (8bit / 16bit).
  CtrlStatesIdx               the index of the 1:1 relation pointing to CanIf_CtrlStates
  Dlc                         Data length code.
  MailBoxConfigIdx            the index of the 1:1 relation pointing to CanIf_MailBoxConfig
  TxConfirmationFctListIdx    the index of the 1:1 relation pointing to CanIf_TxConfirmationFctList
*/ 
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(CanIf_TxPduConfigType, CANIF_CONST) CanIf_TxPduConfig[7] = {
    /* Index    CanId         UpperLayerTxPduId                                               CtrlStatesIdx                                                                      Dlc  MailBoxConfigIdx                                                           TxConfirmationFctListIdx                                        Comment                                                          Referable Keys */
  { /*     0 */ 0x98DAF913uL, PduRConf_PduRDestPdu_msg_Transmit_Extended1_oCAN00_ff88358c_Tx,           0uL  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN00_9df8a959 */,  8u,              0uL  /* /ActiveEcuC/Can/CanConfigSet/CN_CAN00_5e566ad9_Tx */,                      3uL  /* PduR_CanIfTxConfirmation */ },  /* [PDU: msg_Transmit_Extended1_oCAN00_f3b05f8f_Tx]     */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/msg_Transmit_Extended1_oCAN00_f3b05f8f_Tx] */
  { /*     1 */ 0x00000612uL, CanTpConf_CanTpTxFcNPdu_CanTpTxFcNPdu_7fe257d9                ,           0uL  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN00_9df8a959 */,  8u,              0uL  /* /ActiveEcuC/Can/CanConfigSet/CN_CAN00_5e566ad9_Tx */,                      2uL  /* CanTp_TxConfirmation */     },  /* [PDU: msg_diag_Response_MyECU_Tp_oCAN00_59e48f7a_Tx] */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/msg_diag_Response_MyECU_Tp_oCAN00_59e48f7a_Tx] */
  { /*     2 */ 0x00000511uL, PduRConf_PduRDestPdu_msg_MyECU_Lamp_oCAN00_26f3473b_Tx        ,           0uL  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN00_9df8a959 */,  8u,              0uL  /* /ActiveEcuC/Can/CanConfigSet/CN_CAN00_5e566ad9_Tx */,                      3uL  /* PduR_CanIfTxConfirmation */ },  /* [PDU: msg_MyECU_Lamp_oCAN00_41befc25_Tx]             */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/msg_MyECU_Lamp_oCAN00_41befc25_Tx] */
  { /*     3 */ 0x00000400uL, CanNmConf_CanNmTxPdu_msg_nm_MyECU_oCAN00_077ec9e6_Tx          ,           0uL  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN00_9df8a959 */,  8u,              0uL  /* /ActiveEcuC/Can/CanConfigSet/CN_CAN00_5e566ad9_Tx */,                      1uL  /* CanNm_TxConfirmation */     },  /* [PDU: msg_nm_MyECU_oCAN00_dfbc2140_Tx]               */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/msg_nm_MyECU_oCAN00_dfbc2140_Tx] */
  { /*     4 */ 0x00000201uL, PduRConf_PduRDestPdu_msg_Transmit_Copy_1_oCAN00_70bbb9d5_Tx   ,           0uL  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN00_9df8a959 */,  8u,              0uL  /* /ActiveEcuC/Can/CanConfigSet/CN_CAN00_5e566ad9_Tx */,                      3uL  /* PduR_CanIfTxConfirmation */ },  /* [PDU: msg_Transmit_Copy_1_oCAN00_990cfc00_Tx]        */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/msg_Transmit_Copy_1_oCAN00_990cfc00_Tx] */
  { /*     5 */ 0x00000200uL, PduRConf_PduRDestPdu_msg_Transmit_oCAN00_9631a86b_Tx          ,           0uL  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN00_9df8a959 */,  1u,              0uL  /* /ActiveEcuC/Can/CanConfigSet/CN_CAN00_5e566ad9_Tx */,                      3uL  /* PduR_CanIfTxConfirmation */ },  /* [PDU: msg_Transmit_oCAN00_29db34a4_Tx]               */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/msg_Transmit_oCAN00_29db34a4_Tx] */
  { /*     6 */ 0x98DAF914uL, PduRConf_PduRDestPdu_msg_Transmit_Extended2_oCAN01_5002adb6_Tx,           1uL  /* /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN01_eaff99cf */,  8u,              3uL  /* /ActiveEcuC/Can/CanConfigSet/CN_CAN01_29515a4f_Tx */,                      3uL  /* PduR_CanIfTxConfirmation */ }   /* [PDU: msg_Transmit_Extended2_oCAN01_f0f4fa20_Tx]     */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/msg_Transmit_Extended2_oCAN01_f0f4fa20_Tx] */
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_TxPduQueueIndex
**********************************************************************************************************************/
/** 
  \var    CanIf_TxPduQueueIndex
  \brief  Indirection table: Tx-PDU handle ID to corresponding Tx buffer handle ID. NOTE: Only BasicCAN Tx-PDUs have a valid indirection into the Tx buffer.
  \details
  Element       Description
  TxQueueIdx    the index of the 0:1 relation pointing to CanIf_TxQueue
*/ 
#define CANIF_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(CanIf_TxPduQueueIndexType, CANIF_CONST) CanIf_TxPduQueueIndex[7] = {
    /* Index    TxQueueIdx                                                                                            Comment                                                                                    Referable Keys */
  { /*     0 */        0uL  /* /ActiveEcuC/CanIf/CanIfInitCfg/msg_Transmit_Extended1_oCAN00_f3b05f8f_Tx */     },  /* [msg_Transmit_Extended1_oCAN00_f3b05f8f_Tx, BasicCAN TxPdu with Tx-buffer]     */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/msg_Transmit_Extended1_oCAN00_f3b05f8f_Tx, /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN00_9df8a959] */
  { /*     1 */        1uL  /* /ActiveEcuC/CanIf/CanIfInitCfg/msg_diag_Response_MyECU_Tp_oCAN00_59e48f7a_Tx */ },  /* [msg_diag_Response_MyECU_Tp_oCAN00_59e48f7a_Tx, BasicCAN TxPdu with Tx-buffer] */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/msg_diag_Response_MyECU_Tp_oCAN00_59e48f7a_Tx, /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN00_9df8a959] */
  { /*     2 */        2uL  /* /ActiveEcuC/CanIf/CanIfInitCfg/msg_MyECU_Lamp_oCAN00_41befc25_Tx */             },  /* [msg_MyECU_Lamp_oCAN00_41befc25_Tx, BasicCAN TxPdu with Tx-buffer]             */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/msg_MyECU_Lamp_oCAN00_41befc25_Tx, /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN00_9df8a959] */
  { /*     3 */        3uL  /* /ActiveEcuC/CanIf/CanIfInitCfg/msg_nm_MyECU_oCAN00_dfbc2140_Tx */               },  /* [msg_nm_MyECU_oCAN00_dfbc2140_Tx, BasicCAN TxPdu with Tx-buffer]               */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/msg_nm_MyECU_oCAN00_dfbc2140_Tx, /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN00_9df8a959] */
  { /*     4 */        4uL  /* /ActiveEcuC/CanIf/CanIfInitCfg/msg_Transmit_Copy_1_oCAN00_990cfc00_Tx */        },  /* [msg_Transmit_Copy_1_oCAN00_990cfc00_Tx, BasicCAN TxPdu with Tx-buffer]        */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/msg_Transmit_Copy_1_oCAN00_990cfc00_Tx, /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN00_9df8a959] */
  { /*     5 */        5uL  /* /ActiveEcuC/CanIf/CanIfInitCfg/msg_Transmit_oCAN00_29db34a4_Tx */               },  /* [msg_Transmit_oCAN00_29db34a4_Tx, BasicCAN TxPdu with Tx-buffer]               */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/msg_Transmit_oCAN00_29db34a4_Tx, /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN00_9df8a959] */
  { /*     6 */        6uL  /* /ActiveEcuC/CanIf/CanIfInitCfg/msg_Transmit_Extended2_oCAN01_f0f4fa20_Tx */     }   /* [msg_Transmit_Extended2_oCAN01_f0f4fa20_Tx, BasicCAN TxPdu with Tx-buffer]     */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/msg_Transmit_Extended2_oCAN01_f0f4fa20_Tx, /ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN01_eaff99cf] */
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_CtrlStates
**********************************************************************************************************************/
/** 
  \var    CanIf_CtrlStates
  \details
  Element     Description
  CtrlMode    Controller mode.
  PduMode     PDU mode state.
*/ 
#define CANIF_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(CanIf_CtrlStatesUType, CANIF_VAR_NOINIT) CanIf_CtrlStates;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
  /* Index        Referable Keys  */
  /*     0 */  /* [/ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN00_9df8a959] */
  /*     1 */  /* [/ActiveEcuC/CanIf/CanIfCtrlDrvCfg_7d254554/CT_CAN01_eaff99cf] */

#define CANIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_TxBufferPrioByCanIdBase
**********************************************************************************************************************/
/** 
  \var    CanIf_TxBufferPrioByCanIdBase
  \brief  Variable declaration - Tx-buffer: PRIO_BY_CANID as byte/bit-queue. Stores at least the QueueCounter.
*/ 
#define CANIF_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(CanIf_TxBufferPrioByCanIdBaseUType, CANIF_VAR_NOINIT) CanIf_TxBufferPrioByCanIdBase;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
  /* Index        Referable Keys  */
  /*     0 */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/CHNL_0fb271d2] */
  /*     1 */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/CHNL_c4eea277] */

#define CANIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  CanIf_TxQueue
**********************************************************************************************************************/
/** 
  \var    CanIf_TxQueue
  \brief  Variable declaration - Tx byte queue.
*/ 
#define CANIF_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(CanIf_TxQueueUType, CANIF_VAR_NOINIT) CanIf_TxQueue;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
  /* Index        Referable Keys  */
  /*     0 */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/msg_Transmit_Extended1_oCAN00_f3b05f8f_Tx] */
  /*     1 */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/msg_diag_Response_MyECU_Tp_oCAN00_59e48f7a_Tx] */
  /*     2 */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/msg_MyECU_Lamp_oCAN00_41befc25_Tx] */
  /*     3 */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/msg_nm_MyECU_oCAN00_dfbc2140_Tx] */
  /*     4 */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/msg_Transmit_Copy_1_oCAN00_990cfc00_Tx] */
  /*     5 */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/msg_Transmit_oCAN00_29db34a4_Tx] */
  /*     6 */  /* [/ActiveEcuC/CanIf/CanIfInitCfg/msg_Transmit_Extended2_oCAN01_f0f4fa20_Tx] */

#define CANIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA
**********************************************************************************************************************/



