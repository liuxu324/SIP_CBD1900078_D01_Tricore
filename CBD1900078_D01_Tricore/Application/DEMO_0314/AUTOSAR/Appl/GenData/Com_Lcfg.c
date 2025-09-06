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
 *            Module: Com
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: Aurix 2G/TC397 B-Step
 *    License Scope : The usage is restricted to CBD1900078_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Com_Lcfg.c
 *   Generation Time: 2024-12-16 22:29:53
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


/**********************************************************************************************************************
  MISRA / PClint JUSTIFICATIONS
**********************************************************************************************************************/
/* PRQA  S 1881 EOF */ /* MD_MSR_AutosarBoolean */
/* PRQA  S 1882 EOF */ /* MD_MSR_AutosarBoolean */

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#define V_IL_ASRCOMCFG5_LCFG_SOURCE

#include "Com.h"

#include "Com_Lcfg.h"

#include "Rte_Cbk.h"

#include "SchM_Com.h"

/**********************************************************************************************************************
  LOCAL CONSTANT MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL FUNCTION MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL DATA TYPES AND STRUCTURES
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
  Com_ConstValueUInt8
**********************************************************************************************************************/
/** 
  \var    Com_ConstValueUInt8
  \brief  Optimized array of commonly used values like initial or invalid values. (BOOLEAN, UINT8)
*/ 
#define COM_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_ConstValueUInt8Type, COM_CONST) Com_ConstValueUInt8[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     ConstValueUInt8      Referable Keys */
  /*     0 */            0x00u   /* [/ActiveEcuC/Com/ComConfig/sig_State_Copy_1_omsg_Receive_1_oCAN00_0cb08066_RxInitValue, /ActiveEcuC/Com/ComConfig/sig_State_Extend_1_omsg_Receive_Extend_1_oCAN00_184f337d_RxInitValue, /ActiveEcuC/Com/ComConfig/sig_State_Extend_2_omsg_Receive_Extend_2_oCAN01_a5662110_RxInitValue, /ActiveEcuC/Com/ComConfig/sig_State_RearInteriorLight_omsg_Receive_oCAN00_63323183_RxInitValue, /ActiveEcuC/Com/ComConfig/sig_State_RearLeftDoor_omsg_Receive_oCAN00_84ad4140_RxInitValue, /ActiveEcuC/Com/ComConfig/sig_State_RearRightDoor_omsg_Receive_oCAN00_a8945098_RxInitValue] */
};
#define COM_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_PduGrpVector
**********************************************************************************************************************/
/** 
  \var    Com_PduGrpVector
  \brief  Contains an I-PDU-Group vector for each I-PDU, mapping the I-PDU to the corresponding I-PDU-Groups.
*/ 
#define COM_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_PduGrpVectorType, COM_CONST) Com_PduGrpVector[4] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     PduGrpVector      Referable Keys */
  /*     0 */         0x08u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx] */
  /*     1 */         0x04u,  /* [/ActiveEcuC/Com/ComConfig/msg_Receive_Extend_2_oCAN01_c505beb0_Rx] */
  /*     2 */         0x01u,  /* [/ActiveEcuC/Com/ComConfig/msg_Receive_1_oCAN00_e29a6c9c_Rx, /ActiveEcuC/Com/ComConfig/msg_Receive_Extend_1_oCAN00_3c8d89c5_Rx, /ActiveEcuC/Com/ComConfig/msg_Receive_oCAN00_2b456e3f_Rx] */
  /*     3 */         0x02u   /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx, /ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx, /ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx, /ActiveEcuC/Com/ComConfig/msg_Transmit_oCAN00_0723e95e_Tx] */
};
#define COM_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxAccessInfo
**********************************************************************************************************************/
/** 
  \var    Com_RxAccessInfo
  \brief  Contains all signal layout information necessary for signal access within an I-PDU.
  \details
  Element          Description
  InitValueUsed    TRUE, if the 0:1 relation has minimum 1 relation pointing to Com_ConstValueUInt8,Com_ConstValueUInt16,Com_ConstValueUInt32,Com_ConstValueUInt64,Com_ConstValueSInt8,Com_ConstValueSInt16,Com_ConstValueSInt32,Com_ConstValueSInt64,Com_ConstValueFloat32,Com_ConstValueFloat64
  BitPosition      Little endian bit position of the signal or group signal within the I-PDU.
  BusAcc           BUS access algorithm for signal or group signal packing / un-packing.
  RxPduInfoIdx     the index of the 1:1 relation pointing to Com_RxPduInfo
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_RxAccessInfoType, COM_CONST) Com_RxAccessInfo[6] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    InitValueUsed  BitPosition  BusAcc                         RxPduInfoIdx        Referable Keys */
  { /*     0 */          TRUE,          0u, COM_NBIT_BUSACCOFRXACCESSINFO,           0u },  /* [/ActiveEcuC/Com/ComConfig/sig_State_Copy_1_omsg_Receive_1_oCAN00_0cb08066_Rx, /ActiveEcuC/Com/ComConfig/msg_Receive_1_oCAN00_e29a6c9c_Rx] */
  { /*     1 */          TRUE,          1u, COM_NBIT_BUSACCOFRXACCESSINFO,           1u },  /* [/ActiveEcuC/Com/ComConfig/sig_State_Extend_1_omsg_Receive_Extend_1_oCAN00_184f337d_Rx, /ActiveEcuC/Com/ComConfig/msg_Receive_Extend_1_oCAN00_3c8d89c5_Rx] */
  { /*     2 */          TRUE,          1u, COM_NBIT_BUSACCOFRXACCESSINFO,           2u },  /* [/ActiveEcuC/Com/ComConfig/sig_State_Extend_2_omsg_Receive_Extend_2_oCAN01_a5662110_Rx, /ActiveEcuC/Com/ComConfig/msg_Receive_Extend_2_oCAN01_c505beb0_Rx] */
  { /*     3 */          TRUE,          2u, COM_NBIT_BUSACCOFRXACCESSINFO,           3u },  /* [/ActiveEcuC/Com/ComConfig/sig_State_RearInteriorLight_omsg_Receive_oCAN00_63323183_Rx, /ActiveEcuC/Com/ComConfig/msg_Receive_oCAN00_2b456e3f_Rx] */
  { /*     4 */          TRUE,          0u, COM_NBIT_BUSACCOFRXACCESSINFO,           3u },  /* [/ActiveEcuC/Com/ComConfig/sig_State_RearLeftDoor_omsg_Receive_oCAN00_84ad4140_Rx, /ActiveEcuC/Com/ComConfig/msg_Receive_oCAN00_2b456e3f_Rx] */
  { /*     5 */          TRUE,          1u, COM_NBIT_BUSACCOFRXACCESSINFO,           3u }   /* [/ActiveEcuC/Com/ComConfig/sig_State_RearRightDoor_omsg_Receive_oCAN00_a8945098_Rx, /ActiveEcuC/Com/ComConfig/msg_Receive_oCAN00_2b456e3f_Rx] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxCbkFuncPtr
**********************************************************************************************************************/
/** 
  \var    Com_RxCbkFuncPtr
  \brief  Function pointer table containing configured notification and invalid notifications function pointer for signals and signal groups.
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(ComRxCbkType, COM_CONST) Com_RxCbkFuncPtr[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     RxCbkFuncPtr                                                                Referable Keys */
  /*     0 */ Rte_COMCbk_sig_State_RearInteriorLight_omsg_Receive_oCAN00_63323183_Rx    /* [/ActiveEcuC/Com/ComConfig/sig_State_RearInteriorLight_omsg_Receive_oCAN00_63323183_RxAck] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxPduGrpInfo
**********************************************************************************************************************/
/** 
  \var    Com_RxPduGrpInfo
  \brief  Contains all I-PDU-Group relevant information for Rx I-PDUs.
  \details
  Element                 Description
  PduGrpVectorStartIdx    the start index of the 0:n relation pointing to Com_PduGrpVector
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_RxPduGrpInfoType, COM_CONST) Com_RxPduGrpInfo[4] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    PduGrpVectorStartIdx */
  { /*     0 */                   2u },
  { /*     1 */                   2u },
  { /*     2 */                   1u },
  { /*     3 */                   2u }
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxPduInfo
**********************************************************************************************************************/
/** 
  \var    Com_RxPduInfo
  \brief  Contains all relevant common information for Rx I-PDUs.
  \details
  Element                Description
  RxAccessInfoIndUsed    TRUE, if the 0:n relation has 1 relation pointing to Com_RxAccessInfoInd
  RxSigInfoEndIdx        the end index of the 0:n relation pointing to Com_RxSigInfo
  Type                   Defines whether rx Pdu is a NORMAL or TP IPdu.
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_RxPduInfoType, COM_CONST) Com_RxPduInfo[4] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    RxAccessInfoIndUsed  RxSigInfoEndIdx  Type                              Referable Keys */
  { /*     0 */                TRUE,              1u, COM_NORMAL_TYPEOFRXPDUINFO },  /* [/ActiveEcuC/Com/ComConfig/msg_Receive_1_oCAN00_e29a6c9c_Rx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Rx_4cbf71f7] */
  { /*     1 */                TRUE,              2u, COM_NORMAL_TYPEOFRXPDUINFO },  /* [/ActiveEcuC/Com/ComConfig/msg_Receive_Extend_1_oCAN00_3c8d89c5_Rx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Rx_4cbf71f7] */
  { /*     2 */                TRUE,              3u, COM_NORMAL_TYPEOFRXPDUINFO },  /* [/ActiveEcuC/Com/ComConfig/msg_Receive_Extend_2_oCAN01_c505beb0_Rx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN01_Rx_f4031692] */
  { /*     3 */                TRUE,              6u, COM_NORMAL_TYPEOFRXPDUINFO }   /* [/ActiveEcuC/Com/ComConfig/msg_Receive_oCAN00_2b456e3f_Rx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Rx_4cbf71f7] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxSigInfo
**********************************************************************************************************************/
/** 
  \var    Com_RxSigInfo
  \brief  Contains all relevant information for Rx signals.
  \details
  Element               Description
  RxCbkFuncPtrAckIdx    the index of the 0:1 relation pointing to Com_RxCbkFuncPtr
  ValidDlc              Minimum length of PDU required to completely receive the signal or signal group.
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_RxSigInfoType, COM_CONST) Com_RxSigInfo[6] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    RxCbkFuncPtrAckIdx                    ValidDlc        Referable Keys */
  { /*     0 */ COM_NO_RXCBKFUNCPTRACKIDXOFRXSIGINFO,       1u },  /* [/ActiveEcuC/Com/ComConfig/msg_Receive_1_oCAN00_e29a6c9c_Rx] */
  { /*     1 */ COM_NO_RXCBKFUNCPTRACKIDXOFRXSIGINFO,       1u },  /* [/ActiveEcuC/Com/ComConfig/msg_Receive_Extend_1_oCAN00_3c8d89c5_Rx] */
  { /*     2 */ COM_NO_RXCBKFUNCPTRACKIDXOFRXSIGINFO,       1u },  /* [/ActiveEcuC/Com/ComConfig/msg_Receive_Extend_2_oCAN01_c505beb0_Rx] */
  { /*     3 */                                   0u,       1u },  /* [/ActiveEcuC/Com/ComConfig/msg_Receive_oCAN00_2b456e3f_Rx] */
  { /*     4 */ COM_NO_RXCBKFUNCPTRACKIDXOFRXSIGINFO,       1u },  /* [/ActiveEcuC/Com/ComConfig/msg_Receive_oCAN00_2b456e3f_Rx] */
  { /*     5 */ COM_NO_RXCBKFUNCPTRACKIDXOFRXSIGINFO,       1u }   /* [/ActiveEcuC/Com/ComConfig/msg_Receive_oCAN00_2b456e3f_Rx] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxModeFalse
**********************************************************************************************************************/
/** 
  \var    Com_TxModeFalse
  \brief  Contains all relevant information for transmission mode false.
  \details
  Element     Description
  Periodic    TRUE if transmission mode contains a cyclic part.
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_TxModeFalseType, COM_CONST) Com_TxModeFalse[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    Periodic        Referable Keys */
  { /*     0 */     TRUE }   /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx, /ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx, /ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx, /ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx, /ActiveEcuC/Com/ComConfig/msg_Transmit_oCAN00_0723e95e_Tx] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxModeInfo
**********************************************************************************************************************/
/** 
  \var    Com_TxModeInfo
  \brief  Contains all relevant information for transmission mode handling.
  \details
  Element          Description
  InitMode         Initial transmission mode selector of the Tx I-PDU.
  TxModeTrueIdx    the index of the 1:1 relation pointing to Com_TxModeTrue
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_TxModeInfoType, COM_CONST) Com_TxModeInfo[5] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    InitMode  TxModeTrueIdx        Referable Keys */
  { /*     0 */     TRUE,            0u },  /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx] */
  { /*     1 */     TRUE,            0u },  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx] */
  { /*     2 */     TRUE,            0u },  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx] */
  { /*     3 */     TRUE,            0u },  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx] */
  { /*     4 */     TRUE,            0u }   /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_oCAN00_0723e95e_Tx] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxModeTrue
**********************************************************************************************************************/
/** 
  \var    Com_TxModeTrue
  \brief  Contains all relevant information for transmission mode true.
  \details
  Element     Description
  Periodic    TRUE if transmission mode contains a cyclic part.
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_TxModeTrueType, COM_CONST) Com_TxModeTrue[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    Periodic        Referable Keys */
  { /*     0 */     TRUE }   /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx, /ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx, /ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx, /ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx, /ActiveEcuC/Com/ComConfig/msg_Transmit_oCAN00_0723e95e_Tx] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxPduGrpInfo
**********************************************************************************************************************/
/** 
  \var    Com_TxPduGrpInfo
  \brief  Contains all I-PDU-Group relevant information for Tx I-PDUs.
  \details
  Element                 Description
  PduGrpVectorStartIdx    the start index of the 0:n relation pointing to Com_PduGrpVector
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_TxPduGrpInfoType, COM_CONST) Com_TxPduGrpInfo[5] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    PduGrpVectorStartIdx */
  { /*     0 */                   3u },
  { /*     1 */                   3u },
  { /*     2 */                   3u },
  { /*     3 */                   0u },
  { /*     4 */                   3u }
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxPduInfo
**********************************************************************************************************************/
/** 
  \var    Com_TxPduInfo
  \brief  Contains all relevant information for Tx I-PDUs.
  \details
  Element                   Description
  TxPduInitValueUsed        TRUE, if the 0:n relation has 1 relation pointing to Com_TxPduInitValue
  MetaDataLength            Length of MetaData.
  TxBufferLength            the number of relations pointing to Com_TxBuffer
  TxPduInitValueEndIdx      the end index of the 0:n relation pointing to Com_TxPduInitValue
  TxPduInitValueStartIdx    the start index of the 0:n relation pointing to Com_TxPduInitValue
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_TxPduInfoType, COM_CONST) Com_TxPduInfo[5] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    TxPduInitValueUsed  MetaDataLength  TxBufferLength  TxPduInitValueEndIdx  TxPduInitValueStartIdx        Referable Keys */
  { /*     0 */               TRUE,             0u,             8u,                   8u,                     0u },  /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  { /*     1 */               TRUE,             0u,             8u,                  16u,                     8u },  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  { /*     2 */               TRUE,             0u,             8u,                  24u,                    16u },  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  { /*     3 */               TRUE,             0u,             8u,                  32u,                    24u },  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN01_Tx_a259b114] */
  { /*     4 */               TRUE,             0u,             1u,                  33u,                    32u }   /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_oCAN00_0723e95e_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxPduInitValue
**********************************************************************************************************************/
/** 
  \var    Com_TxPduInitValue
  \brief  Initial values used for Tx I-PDU buffer initialization.
*/ 
#define COM_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_TxPduInitValueType, COM_CONST) Com_TxPduInitValue[33] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     TxPduInitValue      Referable Keys */
  /*     0 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx] */
  /*     1 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx] */
  /*     2 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx] */
  /*     3 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx] */
  /*     4 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx] */
  /*     5 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx] */
  /*     6 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx] */
  /*     7 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx] */
  /*     8 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx] */
  /*     9 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx] */
  /*    10 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx] */
  /*    11 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx] */
  /*    12 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx] */
  /*    13 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx] */
  /*    14 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx] */
  /*    15 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx] */
  /*    16 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx] */
  /*    17 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx] */
  /*    18 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx] */
  /*    19 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx] */
  /*    20 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx] */
  /*    21 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx] */
  /*    22 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx] */
  /*    23 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx] */
  /*    24 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx] */
  /*    25 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx] */
  /*    26 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx] */
  /*    27 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx] */
  /*    28 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx] */
  /*    29 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx] */
  /*    30 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx] */
  /*    31 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx] */
  /*    32 */           0x00u   /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_oCAN00_0723e95e_Tx] */
};
#define COM_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxSigInfo
**********************************************************************************************************************/
/** 
  \var    Com_TxSigInfo
  \brief  Contains all relevant information for Tx signals and group signals.
  \details
  Element             Description
  BitLength           Bit length of the signal or group signal.
  BitPosition         Little endian bit position of the signal or group signal within the I-PDU.
  ByteLength          Byte length of the signal or group signal.
  TxBufferLength      the number of relations pointing to Com_TxBuffer
  TxBufferStartIdx    the start index of the 0:n relation pointing to Com_TxBuffer
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_TxSigInfoType, COM_CONST) Com_TxSigInfo[5] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    BitLength  BitPosition  ByteLength  TxBufferLength  TxBufferStartIdx        Referable Keys */
  { /*     0 */        8u,          0u,         1u,             1u,               0u },  /* [/ActiveEcuC/Com/ComConfig/sig_LampCnt_omsg_MyECU_Lamp_oCAN00_f37e68ea_Tx, /ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx] */
  { /*     1 */        1u,          0u,         0u,             1u,               8u },  /* [/ActiveEcuC/Com/ComConfig/sig_RearInteriorLight_Copy_1_omsg_Transmit_Copy_1_oCAN00_bb8c8f19_Tx, /ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx] */
  { /*     2 */        1u,          0u,         0u,             1u,              16u },  /* [/ActiveEcuC/Com/ComConfig/sig_RearInteriorLight_Extend_1_omsg_Transmit_Extended1_oCAN00_4cf4a247_Tx, /ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx] */
  { /*     3 */        1u,          0u,         0u,             1u,              24u },  /* [/ActiveEcuC/Com/ComConfig/sig_RearInteriorLight_Extend_2_omsg_Transmit_Extended2_oCAN01_7c639d8d_Tx, /ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx] */
  { /*     4 */        1u,          0u,         0u,             1u,              32u }   /* [/ActiveEcuC/Com/ComConfig/sig_RearInteriorLight_omsg_Transmit_oCAN00_49a633c1_Tx, /ActiveEcuC/Com/ComConfig/msg_Transmit_oCAN00_0723e95e_Tx] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_CurrentTxMode
**********************************************************************************************************************/
/** 
  \var    Com_CurrentTxMode
  \brief  Current transmission mode state of all Tx I-PDUs.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_CurrentTxModeType, COM_VAR_NOINIT) Com_CurrentTxMode[5];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     2 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     3 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN01_Tx_a259b114] */
  /*     4 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_oCAN00_0723e95e_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_CycleTimeCnt
**********************************************************************************************************************/
/** 
  \var    Com_CycleTimeCnt
  \brief  Current counter value of cyclic transmission.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_CycleTimeCntType, COM_VAR_NOINIT) Com_CycleTimeCnt[5];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     2 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     3 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN01_Tx_a259b114] */
  /*     4 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_oCAN00_0723e95e_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_CyclicSendRequest
**********************************************************************************************************************/
/** 
  \var    Com_CyclicSendRequest
  \brief  Cyclic send request flag used to indicate cyclic transmission mode for all Tx I-PDU.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_CyclicSendRequestType, COM_VAR_NOINIT) Com_CyclicSendRequest[5];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     2 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     3 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN01_Tx_a259b114] */
  /*     4 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_oCAN00_0723e95e_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_DelayTimeCnt
**********************************************************************************************************************/
/** 
  \var    Com_DelayTimeCnt
  \brief  Current counter value of minimum delay counter.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_DelayTimeCntType, COM_VAR_NOINIT) Com_DelayTimeCnt[5];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     2 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     3 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN01_Tx_a259b114] */
  /*     4 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_oCAN00_0723e95e_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_GatewayProcessingISRLockCounter
**********************************************************************************************************************/
#define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_GatewayProcessingISRLockCounterType, COM_VAR_NOINIT) Com_GatewayProcessingISRLockCounter;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_HandleRxPduDeferred
**********************************************************************************************************************/
/** 
  \var    Com_HandleRxPduDeferred
  \brief  Array indicating received Rx I-PDUs to be processed deferred within the next call of Com_MainfunctionRx().
*/ 
#define COM_START_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_HandleRxPduDeferredUType, COM_VAR_NOINIT) Com_HandleRxPduDeferred;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/msg_Receive_1_oCAN00_e29a6c9c_Rx] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/msg_Receive_Extend_1_oCAN00_3c8d89c5_Rx] */
  /*     2 */  /* [/ActiveEcuC/Com/ComConfig/msg_Receive_Extend_2_oCAN01_c505beb0_Rx] */
  /*     3 */  /* [/ActiveEcuC/Com/ComConfig/msg_Receive_oCAN00_2b456e3f_Rx] */

#define COM_STOP_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_Initialized
**********************************************************************************************************************/
/** 
  \var    Com_Initialized
  \brief  Initialization state of Com. TRUE, if Com_Init() has been called, else FALSE.
*/ 
#define COM_START_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_InitializedType, COM_VAR_ZERO_INIT) Com_Initialized = FALSE;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define COM_STOP_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RepCnt
**********************************************************************************************************************/
/** 
  \var    Com_RepCnt
  \brief  Current repetition counter value for replication of transmission requests plus one initial transmit.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_RepCntType, COM_VAR_NOINIT) Com_RepCnt[5];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     2 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     3 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN01_Tx_a259b114] */
  /*     4 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_oCAN00_0723e95e_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RepCycleCnt
**********************************************************************************************************************/
/** 
  \var    Com_RepCycleCnt
  \brief  Current counter value of repetition period for replication of transmission requests.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_RepCycleCntType, COM_VAR_NOINIT) Com_RepCycleCnt[5];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     2 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     3 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN01_Tx_a259b114] */
  /*     4 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_oCAN00_0723e95e_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxDeadlineMonitoringISRLockCounter
**********************************************************************************************************************/
#define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_RxDeadlineMonitoringISRLockCounterType, COM_VAR_NOINIT) Com_RxDeadlineMonitoringISRLockCounter;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxDefPduBuffer
**********************************************************************************************************************/
/** 
  \var    Com_RxDefPduBuffer
  \brief  Rx I-PDU buffer for deferred signal processing.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_RxDefPduBufferUType, COM_VAR_NOINIT) Com_RxDefPduBuffer;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/msg_Receive_1_oCAN00_e29a6c9c_Rx] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/msg_Receive_Extend_1_oCAN00_3c8d89c5_Rx] */
  /*     2 */  /* [/ActiveEcuC/Com/ComConfig/msg_Receive_Extend_2_oCAN01_c505beb0_Rx] */
  /*     3 */  /* [/ActiveEcuC/Com/ComConfig/msg_Receive_oCAN00_2b456e3f_Rx] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxDeferredFctPtrCache
**********************************************************************************************************************/
/** 
  \var    Com_RxDeferredFctPtrCache
  \brief  Cache for deferred Rx (invalid) notification.
*/ 
#define COM_START_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_RxDeferredFctPtrCacheType, COM_VAR_NOINIT) Com_RxDeferredFctPtrCache[1];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define COM_STOP_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxDeferredProcessingISRLockCounter
**********************************************************************************************************************/
#define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_RxDeferredProcessingISRLockCounterType, COM_VAR_NOINIT) Com_RxDeferredProcessingISRLockCounter;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxIPduGroupISRLockCounter
**********************************************************************************************************************/
#define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_RxIPduGroupISRLockCounterType, COM_VAR_NOINIT) Com_RxIPduGroupISRLockCounter;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxPduGrpActive
**********************************************************************************************************************/
/** 
  \var    Com_RxPduGrpActive
  \brief  Rx I-PDU based state (started/stopped) of the corresponding I-PDU-Group.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_RxPduGrpActiveType, COM_VAR_NOINIT) Com_RxPduGrpActive[4];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/msg_Receive_1_oCAN00_e29a6c9c_Rx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Rx_4cbf71f7] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/msg_Receive_Extend_1_oCAN00_3c8d89c5_Rx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Rx_4cbf71f7] */
  /*     2 */  /* [/ActiveEcuC/Com/ComConfig/msg_Receive_Extend_2_oCAN01_c505beb0_Rx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN01_Rx_f4031692] */
  /*     3 */  /* [/ActiveEcuC/Com/ComConfig/msg_Receive_oCAN00_2b456e3f_Rx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Rx_4cbf71f7] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxSigBufferUInt8
**********************************************************************************************************************/
/** 
  \var    Com_RxSigBufferUInt8
  \brief  Rx Signal and Group Signal Buffer. (BOOLEAN, UINT8)
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_RxSigBufferUInt8Type, COM_VAR_NOINIT) Com_RxSigBufferUInt8[6];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/sig_State_Copy_1_omsg_Receive_1_oCAN00_0cb08066_Rx, /ActiveEcuC/Com/ComConfig/sig_State_Copy_1_omsg_Receive_1_oCAN00_0cb08066_Rx_RxSignalBufferRouting] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/sig_State_Extend_1_omsg_Receive_Extend_1_oCAN00_184f337d_Rx, /ActiveEcuC/Com/ComConfig/sig_State_Extend_1_omsg_Receive_Extend_1_oCAN00_184f337d_Rx_RxSignalBufferRouting] */
  /*     2 */  /* [/ActiveEcuC/Com/ComConfig/sig_State_Extend_2_omsg_Receive_Extend_2_oCAN01_a5662110_Rx, /ActiveEcuC/Com/ComConfig/sig_State_Extend_2_omsg_Receive_Extend_2_oCAN01_a5662110_Rx_RxSignalBufferRouting] */
  /*     3 */  /* [/ActiveEcuC/Com/ComConfig/sig_State_RearInteriorLight_omsg_Receive_oCAN00_63323183_Rx, /ActiveEcuC/Com/ComConfig/sig_State_RearInteriorLight_omsg_Receive_oCAN00_63323183_Rx_RxSignalBufferRouting] */
  /*     4 */  /* [/ActiveEcuC/Com/ComConfig/sig_State_RearLeftDoor_omsg_Receive_oCAN00_84ad4140_Rx, /ActiveEcuC/Com/ComConfig/sig_State_RearLeftDoor_omsg_Receive_oCAN00_84ad4140_Rx_RxSignalBufferRouting] */
  /*     5 */  /* [/ActiveEcuC/Com/ComConfig/sig_State_RearRightDoor_omsg_Receive_oCAN00_a8945098_Rx, /ActiveEcuC/Com/ComConfig/sig_State_RearRightDoor_omsg_Receive_oCAN00_a8945098_Rx_RxSignalBufferRouting] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TransmitRequest
**********************************************************************************************************************/
/** 
  \var    Com_TransmitRequest
  \brief  Transmit request flag used for decoupled Tx I-PDU tranmission.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_TransmitRequestType, COM_VAR_NOINIT) Com_TransmitRequest[5];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     2 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     3 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN01_Tx_a259b114] */
  /*     4 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_oCAN00_0723e95e_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxBuffer
**********************************************************************************************************************/
/** 
  \var    Com_TxBuffer
  \brief  Shared uint8 buffer for Tx I-PDUs and ComSignalGroup shadow buffer.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_TxBufferType, COM_VAR_NOINIT) Com_TxBuffer[33];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx, /ActiveEcuC/Com/ComConfig/sig_LampCnt_omsg_MyECU_Lamp_oCAN00_f37e68ea_Tx] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx] */
  /*   ... */  /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx] */
  /*     7 */  /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx] */
  /*     8 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx, /ActiveEcuC/Com/ComConfig/sig_RearInteriorLight_Copy_1_omsg_Transmit_Copy_1_oCAN00_bb8c8f19_Tx] */
  /*     9 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx] */
  /*   ... */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx] */
  /*    15 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx] */
  /*    16 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx, /ActiveEcuC/Com/ComConfig/sig_RearInteriorLight_Extend_1_omsg_Transmit_Extended1_oCAN00_4cf4a247_Tx] */
  /*    17 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx] */
  /*   ... */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx] */
  /*    23 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx] */
  /*    24 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx, /ActiveEcuC/Com/ComConfig/sig_RearInteriorLight_Extend_2_omsg_Transmit_Extended2_oCAN01_7c639d8d_Tx] */
  /*    25 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx] */
  /*   ... */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx] */
  /*    31 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx] */
  /*    32 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_oCAN00_0723e95e_Tx, /ActiveEcuC/Com/ComConfig/sig_RearInteriorLight_omsg_Transmit_oCAN00_49a633c1_Tx] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxCyclicProcessingISRLockCounter
**********************************************************************************************************************/
#define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_TxCyclicProcessingISRLockCounterType, COM_VAR_NOINIT) Com_TxCyclicProcessingISRLockCounter;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxDeadlineMonitoringISRLockCounter
**********************************************************************************************************************/
#define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_TxDeadlineMonitoringISRLockCounterType, COM_VAR_NOINIT) Com_TxDeadlineMonitoringISRLockCounter;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxIPduGroupISRLockCounter
**********************************************************************************************************************/
#define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_TxIPduGroupISRLockCounterType, COM_VAR_NOINIT) Com_TxIPduGroupISRLockCounter;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxPduGrpActive
**********************************************************************************************************************/
/** 
  \var    Com_TxPduGrpActive
  \brief  Tx I-PDU based state (started/stopped) of the corresponding I-PDU-Group.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_TxPduGrpActiveType, COM_VAR_NOINIT) Com_TxPduGrpActive[5];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     2 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     3 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN01_Tx_a259b114] */
  /*     4 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_oCAN00_0723e95e_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxProcessingISRLockCounter
**********************************************************************************************************************/
#define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_TxProcessingISRLockCounterType, COM_VAR_NOINIT) Com_TxProcessingISRLockCounter;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxSduLength
**********************************************************************************************************************/
/** 
  \var    Com_TxSduLength
  \brief  This var Array contains the Com Ipdu Length.
*/ 
#define COM_START_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_TxSduLengthType, COM_VAR_NOINIT) Com_TxSduLength[5];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/msg_MyECU_Lamp_oCAN00_818e1651_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Copy_1_oCAN00_4f60d237_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     2 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended1_oCAN00_1bd55eb9_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */
  /*     3 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_Extended2_oCAN01_e25d69cc_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN01_Tx_a259b114] */
  /*     4 */  /* [/ActiveEcuC/Com/ComConfig/msg_Transmit_oCAN00_0723e95e_Tx, /ActiveEcuC/Com/ComConfig/MyECU_oCAN00_Tx_1ae5d671] */

#define COM_STOP_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA
**********************************************************************************************************************/


/**********************************************************************************************************************
  LOCAL FUNCTION PROTOTYPES
**********************************************************************************************************************/



/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTIONS
**********************************************************************************************************************/






/**********************************************************************************************************************
  END OF FILE: Com_Lcfg.c
**********************************************************************************************************************/

