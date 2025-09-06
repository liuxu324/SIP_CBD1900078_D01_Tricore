[!/*
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
**  FILENAME  : Dma.m                                                         **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE      : 2018-08-30                                                    **
**                                                                            **
**  BSW MODULE DESCRIPTION : NA                                               **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={AA260054-50EB-4298-BACA-2BA573321E43}]    **
**                 [cover parentID={8E589868-A200-419b-99A4-1EE0D5746294}]    **
**                                                                            **
**  DESCRIPTION  : Code template macro file for Dma Driver                    **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
*/!]
/******************************************************************************/
[!/* *** multiple inclusion protection*** */!][!//
[!IF "not(var:defined('DMA_M'))"!][!//
[!VAR "DMA_M"="'true'"!][!//
[!AUTOSPACING!]

[!/*****************************************************************************
** Name             : Dma_TsrConfig                                           **
**                                                                            **
** Description      : Macro to calculate Value for TSR register from          **
**                    Configuration                                           **
**                                                                            **
**                                                                            **
*****************************************************************************/!]
[!MACRO "Dma_TsrConfig", "DmaTRLConf" = "", "DmaTsrReg"=""!][!//
[!NOCODE!][!//
    [!IF "$DmaTRLConf = 'true'"!][!//
        [!VAR "DmaTsrReg" = "bit:or($DmaTsrReg,bit:shl(1,4))"!][!//
    [!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
** Name             : Dma_AdicrConfig                                         **
**                                                                            **
** Description      : Macro to calculate Value for ADICR register from        **
**                    Configuration                                           **
**                                                                            **
** [cover parentID={AA260054-50EB-4298-BACA-2BA573321E43}]                    **
** Dma_AdicrConfig                                                            **
** [/cover]                                                                   **
**                                                                            **
*****************************************************************************/!]
[!MACRO "Dma_AdicrConfig", "SrcModFactor"="", "SrcCirclBufferLen"="", "IncrementSrcAddr"="", "DestModFactor"="", "DestCirclBufferLen"="", "IncrementDestAddr"="", "IntEnable"=""  ,"IntCtrl"="", "TcountThreshold"="0", "WrpSrc"="", "WrpDest"="","ShadowCtrl"="", "SrcCirclBuffEn"="", "DestCirclBuffEn"="", "TimeStampEn"="", "DmaAddrIntControl"=""!][!//
[!NOCODE!]
[!IF "$SrcModFactor = 'DMA_FACTOR_2'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(1,0))"!][!//
[!ELSEIF "$SrcModFactor = 'DMA_FACTOR_4'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(2,0))"!][!//
[!ELSEIF "$SrcModFactor = 'DMA_FACTOR_8'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(3,0))"!][!//
[!ELSEIF "$SrcModFactor = 'DMA_FACTOR_16'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(4,0))"!][!//
[!ELSEIF "$SrcModFactor = 'DMA_FACTOR_32'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(5,0))"!][!//
[!ELSEIF "$SrcModFactor = 'DMA_FACTOR_64'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(6,0))"!][!//
[!ELSEIF "$SrcModFactor = 'DMA_FACTOR_128'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(7,0))"!][!//
[!ENDIF!][!//
[!IF "$IncrementSrcAddr = 'DMA_INCREASING'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(1,3))"!][!//
[!ENDIF!][!//
[!IF "$DestModFactor = 'DMA_FACTOR_2'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(1,4))"!][!//
[!ELSEIF "$DestModFactor = 'DMA_FACTOR_4'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(2,4))"!][!//
[!ELSEIF "$DestModFactor = 'DMA_FACTOR_8'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(3,4))"!][!//
[!ELSEIF "$DestModFactor = 'DMA_FACTOR_16'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(4,4))"!][!//
[!ELSEIF "$DestModFactor = 'DMA_FACTOR_32'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(5,4))"!][!//
[!ELSEIF "$DestModFactor = 'DMA_FACTOR_64'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(6,4))"!][!//
[!ELSEIF "$DestModFactor = 'DMA_FACTOR_128'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(7,4))"!][!//
[!ENDIF!][!//
[!IF "$IncrementDestAddr = 'DMA_INCREASING'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(1,7))"!][!//
[!ENDIF!][!//
[!IF "$SrcCirclBuffEn = 'true'"!][!//
[!IF "$SrcCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_2BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(1,8))"!][!//
[!ELSEIF "$SrcCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_4BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(2,8))"!][!//
[!ELSEIF "$SrcCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_8BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(3,8))"!][!//
[!ELSEIF "$SrcCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_16BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(4,8))"!][!//
[!ELSEIF "$SrcCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_32BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(5,8))"!][!//
[!ELSEIF "$SrcCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_64BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(6,8))"!][!//
[!ELSEIF "$SrcCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_128BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(7,8))"!][!//
[!ELSEIF "$SrcCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_256BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(8,8))"!][!//
[!ELSEIF "$SrcCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_512BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(9,8))"!][!//
[!ELSEIF "$SrcCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_1024BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(10,8))"!][!//
[!ELSEIF "$SrcCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_2048BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(11,8))"!][!//
[!ELSEIF "$SrcCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_4096BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(12,8))"!][!//
[!ELSEIF "$SrcCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_8192BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(13,8))"!][!//
[!ELSEIF "$SrcCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_16384BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(14,8))"!][!//
[!ELSEIF "$SrcCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_32768BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(15,8))"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "$DestCirclBuffEn = 'true'"!][!//
[!IF "$DestCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_2BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(1,12))"!][!//
[!ELSEIF "$DestCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_4BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(2,12))"!][!//
[!ELSEIF "$DestCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_8BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(3,12))"!][!//
[!ELSEIF "$DestCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_16BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(4,12))"!][!//
[!ELSEIF "$DestCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_32BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(5,12))"!][!//
[!ELSEIF "$DestCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_64BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(6,12))"!][!//
[!ELSEIF "$DestCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_128BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(7,12))"!][!//
[!ELSEIF "$DestCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_256BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(8,12))"!][!//
[!ELSEIF "$DestCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_512BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(9,12))"!][!//
[!ELSEIF "$DestCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_1024BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(10,12))"!][!//
[!ELSEIF "$DestCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_2048BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(11,12))"!][!//
[!ELSEIF "$DestCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_4096BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(12,12))"!][!//
[!ELSEIF "$DestCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_8192BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(13,12))"!][!//
[!ELSEIF "$DestCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_16384BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(14,12))"!][!//
[!ELSEIF "$DestCirclBufferLen = 'DMA_CIRCULAR_BUFFER_LENGTH_32768BYTE'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(15,12))"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "$ShadowCtrl = 'DMA_SOURCE_ADDRESS_BUFFERING_RO'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(1,16))"!][!//
[!ELSEIF "$ShadowCtrl = 'DMA_DEST_ADDRESS_BUFFERING_RO'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(2,16))"!][!//
[!ELSEIF "$ShadowCtrl = 'DMA_SOURCE_ADDRESS_BUFFERING_RW'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(5,16))"!][!//
[!ELSEIF "$ShadowCtrl = 'DMA_DEST_ADDRESS_BUFFERING_RW'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(6,16))"!][!//
[!ELSEIF "$ShadowCtrl = 'DMA_SOURCE_DOUBLE_BUFFERING_SW_SWITCH'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(8,16))"!][!//
[!ELSEIF "$ShadowCtrl = 'DMA_SOURCE_DOUBLE_BUFFERING_HW_SW_SWITCH'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(9,16))"!][!//
[!ELSEIF "$ShadowCtrl = 'DMA_DEST_DOUBLE_BUFFERING_SW_SWITCH'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(10,16))"!][!//
[!ELSEIF "$ShadowCtrl = 'DMA_DEST_DOUBLE_BUFFERING_HW_SW_SWITCH'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(11,16))"!][!//
[!ELSEIF "$ShadowCtrl = 'DMA_LINKED_LIST'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(12,16))"!][!//
[!ELSEIF "$ShadowCtrl = 'DMA_ACCUMULATED_LINKED_LIST'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(13,16))"!][!//
[!ELSEIF "$ShadowCtrl = 'DMA_SAFE_LINKED_LIST'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(14,16))"!][!//
[!ELSEIF "$ShadowCtrl = 'DMA_CONDITIONAL_LINKED_LIST'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(15,16))"!][!//
[!ENDIF!][!//
[!IF "$SrcCirclBuffEn = 'true'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(1,20))"!][!//
[!ENDIF!][!//
[!IF "$DestCirclBuffEn = 'true'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(1,21))"!][!//
[!ENDIF!][!//
[!IF "$TimeStampEn = 'true'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(1,22))"!][!//
[!ENDIF!][!//
[!IF "$WrpSrc = 'true'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(1,24))"!][!//
[!ENDIF!][!//
[!IF "$WrpDest = 'true'"!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(1,25))"!][!//
[!ENDIF!][!//
[!IF "$IntEnable = 'true'"!][!//
    [!IF "$IntCtrl = 'DMA_INTERRUPT_PER_TRANSFER'"!][!//
        [!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(3,26))"!][!//
    [!ELSEIF "$IntCtrl = 'DMA_INTERRUPT_PER_TRANSACTION'"!][!//
        [!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(2,26))"!][!//
    [!ELSEIF "$IntCtrl = 'DMA_INTERRUPT_AFTER_THRESHOLD'"!][!//
        [!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl(2,26))"!][!//
    [!ENDIF!][!//
[!ENDIF!][!//
[!VAR "DmaAddrIntControl" = "bit:or($DmaAddrIntControl,bit:shl($TcountThreshold,28))"!][!//
[!ENDNOCODE!]
[!ENDMACRO!]

[!/*****************************************************************************
** Name             : Dma_ChcfgrConfig                                        **
**                                                                            **
** Description      : Macro to calculate Value for Chcfgr register from       **
**                    Configuration                                           **
**                                                                            **
** [cover parentID={86E785B3-97D1-49c9-B259-BA050FD1794E}]                    **
** Dma_ChcfgrConfig                                                           **
** [/cover]                                                                   **
**                                                                            **
*****************************************************************************/!]
[!MACRO "Dma_ChcfgrConfig", "DataWidth"="","BlockMode"="","TransactionLenght"="", "DmaTransferReqState"="","HwMode"="", "PeripheralSelect"="","Priority"="","CrcSwapOrder"="","DmaChcfgrControl"=""!][!//
[!NOCODE!]
[!VAR "DmaChcfgrControl" = "bit:or($DmaChcfgrControl, bit:shl($TransactionLenght,0))"!][!//
[!IF "$BlockMode='DMA_MOVES_2'"!][!//
[!VAR "DmaChcfgrControl" = "bit:or($DmaChcfgrControl, bit:shl(1,16))"!][!//
[!ELSEIF "$BlockMode='DMA_MOVES_4'"!][!//
[!VAR "DmaChcfgrControl" = "bit:or($DmaChcfgrControl, bit:shl(2,16))"!][!//
[!ELSEIF "$BlockMode='DMA_MOVES_8'"!][!//
[!VAR "DmaChcfgrControl" = "bit:or($DmaChcfgrControl, bit:shl(3,16))"!][!//
[!ELSEIF "$BlockMode='DMA_MOVES_16'"!][!//
[!VAR "DmaChcfgrControl" = "bit:or($DmaChcfgrControl, bit:shl(4,16))"!][!//
[!ELSEIF "$BlockMode='DMA_MOVES_3'"!][!//
[!VAR "DmaChcfgrControl" = "bit:or($DmaChcfgrControl, bit:shl(5,16))"!][!//
[!ELSEIF "$BlockMode='DMA_MOVES_5'"!][!//
[!VAR "DmaChcfgrControl" = "bit:or($DmaChcfgrControl, bit:shl(6,16))"!][!//
[!ELSEIF "$BlockMode='DMA_MOVES_9'"!][!//
[!VAR "DmaChcfgrControl" = "bit:or($DmaChcfgrControl, bit:shl(7,16))"!][!//
[!ENDIF!][!//
[!IF "$DmaTransferReqState='DMA_TRANSACTION_PER_TRIGGER'"!][!//
[!VAR "DmaChcfgrControl" = "bit:or($DmaChcfgrControl,bit:shl(1,19))"!][!//
[!ENDIF!][!//
[!IF "$HwMode='DMA_HARDWARE_TRIGGER_CONTINUOUS_MODE'"!][!//
[!VAR "DmaChcfgrControl" = "bit:or($DmaChcfgrControl,bit:shl(1,20))"!][!//
[!ENDIF!][!//
[!IF "$DataWidth='DMA_WIDTH_16BITS'"!][!//
[!VAR "DmaChcfgrControl" = "bit:or($DmaChcfgrControl, bit:shl(1,21))"!][!//
[!ELSEIF "$DataWidth='DMA_WIDTH_32BITS'"!][!//
[!VAR "DmaChcfgrControl" = "bit:or($DmaChcfgrControl, bit:shl(2,21))"!][!//
[!ELSEIF "$DataWidth='DMA_WIDTH_64BITS'"!][!//
[!VAR "DmaChcfgrControl" = "bit:or($DmaChcfgrControl, bit:shl(3,21))"!][!//
[!ELSEIF "$DataWidth='DMA_WIDTH_128BITS'"!][!//
[!VAR "DmaChcfgrControl" = "bit:or($DmaChcfgrControl, bit:shl(4,21))"!][!//
[!ELSEIF "$DataWidth='DMA_WIDTH_256BITS'"!][!//
[!VAR "DmaChcfgrControl" = "bit:or($DmaChcfgrControl, bit:shl(5,21))"!][!//
[!ENDIF!][!//
[!IF "$CrcSwapOrder='true'"!][!//
[!VAR "DmaChcfgrControl" = "bit:or($DmaChcfgrControl,bit:shl(1,27))"!][!//
[!ENDIF!][!//
[!IF "$PeripheralSelect='true'"!][!//
[!VAR "DmaChcfgrControl" = "bit:or($DmaChcfgrControl,bit:shl(1,28))"!][!//
[!ENDIF!][!//
[!ENDNOCODE!]
[!ENDMACRO!]

[!/*****************************************************************************
** Name             : Dma_ErrEnConfig                                         **
**                                                                            **
** Description      : Macro to calculate Value for MoveEngine configuration   **
**                                                                            **
** [cover parentID={6AA4A90A-D2A6-4984-9A33-91FE6733E16C}]                    **
** Dma_ErrEnConfig                                                            **
** [/cover]                                                                   **
**                                                                            **
*****************************************************************************/!]
[!MACRO "Dma_ErrEnConfig", "SrcErr"="","DstErr"="", "LLErr"="", "Dma_ErrEnControl" =""!][!//
[!IF "$SrcErr = 'true'"!][!//
[!VAR "Dma_ErrEnControl"="bit:or($Dma_ErrEnControl,bit:shl(1,16))"!][!//
[!ENDIF!][!//
[!IF "$DstErr = 'true'"!][!//
[!VAR "Dma_ErrEnControl"="bit:or($Dma_ErrEnControl,bit:shl(1,17))"!][!//
[!ENDIF!][!//
[!IF "$LLErr = 'true'"!][!//
[!VAR "Dma_ErrEnControl"="bit:or($Dma_ErrEnControl,bit:shl(1,26))"!][!//
[!ENDIF!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
** Name             : Dma_ResourcePartitionConfig                             **
**                                                                            **
** Description      : Macro to get partition value for user and supervisor    **
**                    mode                                                    **
**                                                                            **
*****************************************************************************/!]
[!MACRO "Dma_ResourcePartitionConfig", "BusMode"="","Dma_ResourcePartitionControl" =""!][!//
[!IF "$BusMode = 'DMA_RP_USER_MODE'"!][!//
[!VAR "Dma_ResourcePartitionControl" = "bit:or($Dma_ResourcePartitionControl,0)"!][!//
[!ELSEIF "$BusMode = 'DMA_RP_SUPERVISOR_MODE'"!][!//
[!VAR "Dma_ResourcePartitionControl" = "bit:or($Dma_ResourcePartitionControl,bit:shl(1,0))"!][!//
[!ENDIF!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
** Name             : Dma_DoubleBufferConfig                                  **
**                                                                            **
** Description      : Macro to calculate double buffering enabled or not      **
**                                                                            **
**                                                                            **
*****************************************************************************/!]
[!MACRO "Dma_DoubleBufferConfig", "ShadowMode"="","Dma_DoubleBufferControl" =""!][!//
[!IF "$ShadowMode = 'DMA_SOURCE_DOUBLE_BUFFERING_SW_SWITCH'"!][!//
[!VAR "Dma_DoubleBufferControl" = "'STD_ON'"!][!//
[!ELSEIF "$ShadowMode = 'DMA_SOURCE_DOUBLE_BUFFERING_HW_SW_SWITCH'"!][!//
[!VAR "Dma_DoubleBufferControl" = "'STD_ON'"!][!//
[!ELSEIF "$ShadowMode = 'DMA_DEST_DOUBLE_BUFFERING_SW_SWITCH'"!][!//
[!VAR "Dma_DoubleBufferControl" = "'STD_ON'"!][!//
[!ELSEIF "$ShadowMode = 'DMA_DEST_DOUBLE_BUFFERING_HW_SW_SWITCH'"!][!//
[!VAR "Dma_DoubleBufferControl" = "'STD_ON'"!][!//
[!ENDIF!][!//
[!ENDMACRO!][!//


[!/*******************************************************************************
** Name             : Dma_CG_GenerateModuleMap                                **
**                                                                            **
** Description      : Macro to generate core-channel mappings for a module    **
**                                                                            **
*******************************************************************************/!]
[!MACRO "Dma_CG_GenerateModuleMap", "Module" = ""!][!//
    [!NOCODE!][!//
        [!/* Variable to hold the list of the cores which are under use */!]
        [!VAR "CGCoreUsed" = "''"!][!//
        [!/* Variable to hold the full mapping of the core and the resources which are allocated */!]
        [!VAR "CGModuleMap" = "''"!][!//
        [!/* Variable to hold the resource names which got allocated in the resource maanger. Note that the core information is not included in this */!]
        [!VAR "CGAllocatedResources" = "''"!][!//
        [!/* Variable to hold the number of allocation in each core */!]
        [!VAR "CGCoreAllocationCount" = "''"!][!//
        [!/* Select the resource manager */!]
        [!SELECT "as:modconf('ResourceM')[1]"!][!//
            [!/* Find the master core ID which is configured. Only get the core number, not the entire string. */!]
            [!VAR "CGMasterCoreId" = "substring(node:value(ResourceMMcalConfig/*[1]/ResourceMMasterCore),5,1)"!][!//
            [!/* Now, enter into the list of all the cores  */!]
            [!LOOP "ResourceMMcalConfig/*[1]/ResourceMMcalCore/*"!][!// /**/
                [!/* An offset of 1000 is needed here to ease the string manipulation, else its a pain to manage the digits from 0 to 127 */!][!//
                [!VAR "AllocationCounter" = "num:i(1000)"!]
                [!/* Lets get into the core specific configurations */!]
                [!VAR "CGCoreID" = "./ResourceMCoreID"!][!//
                [!/* Lets loop through the allocated resources */!]
                [!LOOP "ResourceMAllocation/*"!][!//
                    [!/* Is this resource for the module under consideration? */!]
                    [!IF "$Module = ./ResourceMModuleName"!][!//
                        [!/* Is that a valid node or not? */!]
                        [!IF "node:refvalid(./ResourceMResourceRef)"!][!//
                            [!/* Split the resource string based on '/' */!][!//
                            [!VAR "index" = "num:i(count(text:split(./ResourceMResourceRef, '/')))"!][!//
                            [!/* Get the resource name */!][!//
                            [!VAR "ResourceName" = "text:split(./ResourceMResourceRef, '/')[num:i($index)]"!][!//
                            [!/* Get the corresponding DMA channel number */!][!//
                            [!CALL "Dma_CG_GetTheDmaChannelNumber", "AllocationName" = "$ResourceName", "ChannelNum" = "255"!][!//
                            [!/* Create the core-module map, with the core name appended */!][!//
                            [!VAR "CGModuleMap" = "concat($CGModuleMap, '<', $CGCoreID, '__ALCH#', $ChannelNum, '__', $ResourceName, '>', ',')"!][!//
                            [!/* Create the module map, with the allocated resources */!][!//
                            [!VAR "CGAllocatedResources" = "concat($CGAllocatedResources, '<', '__ALCH#', $ChannelNum, '__', $ResourceName, '>', ',')"!][!//
                            [!/* Add the core number to the list, if it is not there in the list already */!][!//
                            [!IF "not(contains(text:split($CGCoreUsed), $CGCoreID))"!][!//
                                [!VAR "CGCoreUsed" = "concat($CGCoreUsed, $CGCoreID, ',')"!][!//
                            [!ENDIF!][!//
                            [!/* Maintain an allocation counter to keep track of the allocations of this core */!]
                            [!VAR "AllocationCounter" = "$AllocationCounter + num:i(1)"!][!//
                        [!ELSE!][!//
                            [!WARNING!][!//
                                Warning: The resource [!"node:value(./ResourceMResourceRef)"!] does not exists.
                            [!ENDWARNING!][!//
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
                [!/* Mark the allocation count againist each core */!][!//
                [!VAR "CGCoreAllocationCount" = "concat($CGCoreAllocationCount, '<', $CGCoreID, '_', num:i($AllocationCounter), '>', ',')"!][!//
            [!ENDLOOP!][!//
        [!ENDSELECT!][!//
    [!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
** Name             : Dma_CG_GetTheDmaChannelNumber                           **
**                                                                            **
** Description      : Macro to find the channel number of a particular config **
**                                                                            **
*******************************************************************************/!]
[!MACRO "Dma_CG_GetTheDmaChannelNumber", "AllocationName" = "", "ChannelNum" = ""!][!//
    [!NOCODE!][!//
        [!VAR "ChannelNum" = "num:i(255)"!][!//
        [!VAR "AllocationName" = "concat($AllocationName, '#')"!]
        [!VAR "NodeName" = "''"!][!//
        [!SELECT "as:modconf('Dma')[1]"!][!//
            [!IF "node:exists(./DmaChannelConfig)"!][!//
                [!VAR "NoOfDmaCh" = "num:i(count(DmaChannelConfig/*))"!][!//
                [!FOR "ChannelIndex" = "num:i(0)" TO "num:i($NoOfDmaCh) -1"!][!//
                    [!SELECT "DmaChannelConfig/*[@index=$ChannelIndex]"!][!//
                        [!VAR "NodeName" = "node:name(.)"!][!//
                        [!VAR "NodeName" = "concat($NodeName, '#')"!][!//
                        [!IF "text:match($NodeName, $AllocationName) = 'true'"!][!//
                            [!VAR "ChannelNum" = "num:i(DmaChannelId)"!][!//
                        [!ENDIF!][!//
                    [!ENDSELECT!][!//
                [!ENDFOR!][!//
            [!ENDIF!][!//
        [!ENDSELECT!][!//
    [!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/*******************************************************************************
** Name             : Dma_CG_GetTheCoreAssignmentOfChannel                    **
**                                                                            **
** Description      : Macro to find the core to which a channel belongs to    **
**                                                                            **
*******************************************************************************/!]
[!MACRO "Dma_CG_GetTheCoreAssignmentOfChannel", "LocalChannelID" = "", "CoreOfChannel" = ""!][!//
    [!NOCODE!][!//
        [!/* Lets find the core to which this channel belongs to */!][!//
        [!/* Make the pattern which will indicate whether the channel is allocated at all. This will not contain any core information. */!][!//
        [!VAR "DmaChannelRefName" = "concat('<','__ALCH#', num:i($LocalChannelID), '__')"!][!//
        [!/* We need a channel pattern to make a regular expression later-on. Lets keep that as well. Note the absence of < and > here. */!][!//
        [!VAR "DmaChannelListRegEx" = "concat('DmaChannelConfig_', num:i($LocalChannelID))"!][!//
        [!/* Does the allocation contain the channel that we are interested in? */!][!//
        [!IF "contains($CGAllocatedResources, $DmaChannelRefName)"!][!//
            [!/* The channel is allocated in the RM */!][!//
            [!VAR "DmaModuleMapRegEx" = "concat('<', 'CORE[0-6]','__ALCH#', num:i($LocalChannelID), '__', '[^>]*', '>')"!][!//
            [!/* Check for our channel in the list */!][!//
            [!VAR "DmaPatternSearchResult" = "text:grep(text:split($CGModuleMap,','), $DmaModuleMapRegEx )"!][!//
            [!/* Get the core number */!][!//
            [!VAR "CoreOfChannel" = "substring($DmaPatternSearchResult, 7, 1)"!][!//
        [!ELSE!][!//
            [!/* This channel is not allocated. Indicate it as not allocated. */!]
            [!VAR "CoreOfChannel" = "'NOCORE'"!][!//
        [!ENDIF!][!//
    [!ENDNOCODE!][!//
[!ENDMACRO!][!//


[!/***************************************************************************************
** Name             : Dma_CG_GetResourceNumbers                                         **
**                                                                                      **
** Description      : Macro to get the count of the resources for a particular core     **
**                                                                                      **
****************************************************************************************/!]
[!MACRO "Dma_CG_GetResourceNumbers", "LocalCoreId" = "", "AllocationTotalCount" = ""!][!//
    [!NOCODE!][!//
        [!VAR "LocalCoreName" = "concat('CORE', $LocalCoreId)"!]
        [!/* Any resources allocated to this core? */!]
        [!IF "(contains($CGCoreAllocationCount, $LocalCoreName))"!][!//
            [!/* Lets make the regex which can match the channel number. Note that the offset of 1000 is given for ease of string manipulation */!]
            [!VAR "AllocCountRegEx" = "concat('<', $LocalCoreName, '_', '1[0-1][0-9][0-9]', '>')"!][!//
            [!/* Check for the allocation pattern for this core */!]
            [!VAR "AllocPatternSearchResult" = "text:grep(text:split($CGCoreAllocationCount, ','), $AllocCountRegEx )"!][!//
            [!/* Get the number of allocated resources here */!]
            [!VAR "AllocationTotalCount" = "num:i(substring($AllocPatternSearchResult, 10, 3))"!][!//
        [!ELSE!][!//
            [!/* Nothing is allocated for this core */!]
            [!VAR "AllocationTotalCount" = "num:i(0)"!]
        [!ENDIF!][!//
    [!ENDNOCODE!][!//
[!ENDMACRO!][!//


[!/***************************************************************************************
** Name             : Dma_CG_GetChannelIndex                                            **
**                                                                                      **
** Description      : Macro to get the index of the channel                             **
**                                                                                      **
****************************************************************************************/!]
[!MACRO "Dma_CG_GetChannelIndex", "LocalChannelNumber" = "", "IndexLocation" = ""!][!//
    [!NOCODE!][!//
        [!VAR "IndexLocation" = "num:i(255)"!]
        [!VAR "LocalNoOfDmaChannels" = "num:i(count(DmaChannelConfig/*))"!][!//
        [!VAR "LocalChannelIndex" = "num:i(0)"!][!//
        [!FOR "LocalChannelIndex" = "num:i(0)" TO "num:i($LocalNoOfDmaChannels) -1"!][!//
            [!IF "node:exists(./DmaChannelConfig/*[@index=$LocalChannelIndex])"!][!//
                [!IF "node:exists(./DmaChannelConfig/*[@index=$LocalChannelIndex]/DmaChannelId)"!][!//
                    [!VAR "LocalChannelIDAtIndex" = "num:i(./DmaChannelConfig/*[@index=$LocalChannelIndex]/DmaChannelId)"!][!//
                    [!IF "num:i($LocalChannelIDAtIndex) = num:i($LocalChannelNumber)"!]
                        [!VAR "IndexLocation" = "num:i($LocalChannelIndex)"!]
                    [!ENDIF!]
                [!ENDIF!][!//
            [!ENDIF!][!//
        [!ENDFOR!][!//
    [!ENDNOCODE!][!//
[!ENDMACRO!][!//


[!/***************************************************************************************
** Name             : Dma_CG_GetTcsConfIndex                                            **
**                                                                                      **
** Description      : Macro to get the index of the TCS configuration                   **
**                                                                                      **
****************************************************************************************/!]
[!MACRO "Dma_CG_GetTcsConfIndex", "LocalTcsId" = "", "TcsConfIndexLocation" = ""!][!//
    [!NOCODE!][!//
        [!VAR "TcsConfIndexLocation" = "num:i(255)"!]
        [!VAR "LocalNoOfTcs" = "num:i(count(./../../DmaChannelTransactionSet/*))"!][!//
        [!VAR "LocalTcsIndex" = "num:i(0)"!][!//
        [!FOR "LocalTcsIndex" = "num:i(0)" TO "num:i($LocalNoOfTcs) -1"!][!//
            [!IF "node:exists(./../../DmaChannelTransactionSet/*[@index=$LocalTcsIndex])"!][!//
                [!IF "node:exists(./../../DmaChannelTransactionSet/*[@index=$LocalTcsIndex]/DmaTcsIndex )"!][!//
                    [!VAR "LocalTcsIDAtIndex" = "num:i(./../../DmaChannelTransactionSet/*[@index=$LocalTcsIndex]/DmaTcsIndex)"!][!//
                    [!IF "num:i($LocalTcsIDAtIndex) = num:i($LocalTcsId)"!]
                        [!VAR "TcsConfIndexLocation" = "num:i($LocalTcsIndex)"!]
                    [!ENDIF!]
                [!ENDIF!][!//
            [!ENDIF!][!//
        [!ENDFOR!][!//
    [!ENDNOCODE!][!//
[!ENDMACRO!][!//


[!/***************************************************************************************
** Name             : Dma_CG_GetNoOfUnallocatedChannels                                 **
**                                                                                      **
** Description      : Macro to get the number of unallocated channels                   **
**                                                                                      **
****************************************************************************************/!]
[!MACRO "Dma_CG_GetNoOfUnallocatedChannels", "NoOfUnassignedChannels" = ""!][!//
    [!NOCODE!][!//
        [!/* Get the count of the unassigned channels */!][!//
        [!VAR "NoOfUnassignedChannels" = "num:i(0)"!][!//
        [!FOR "ChannelIndex" = "num:i(0)" TO "num:i($NoOfDmaChannels) - num:i(1)"!][!//
            [!SELECT "DmaChannelConfig/*[@index=$ChannelIndex]"!][!//
                [!CALL "Dma_CG_GetTheCoreAssignmentOfChannel", "LocalChannelID" = "num:i(DmaChannelId)", "CoreOfChannel" = "num:i(0)"!][!//
                [!/* Is the channel under consideration belong to the core, for which we are 'iterating'? */!][!//
                [!IF "$CoreOfChannel = 'NOCORE'"!][!//
                    [!VAR "NoOfUnassignedChannels" = "$NoOfUnassignedChannels + num:i(1)"!][!//
                [!ENDIF!][!//
            [!ENDSELECT!][!//
        [!ENDFOR!][!//
    [!ENDNOCODE!][!//
[!ENDMACRO!][!//


[!/***************************************************************************************
** Name             : Dma_CG_GetMasterCoreNumber                                        **
**                                                                                      **
** Description      : Macro to get the master core number                               **
**                                                                                      **
****************************************************************************************/!]
[!MACRO "Dma_CG_GetMasterCoreNumber", "MasterCoreNumber" = ""!][!//
    [!NOCODE!][!//
        [!SELECT "as:modconf('ResourceM')[1]"!][!//
            [!VAR "MasterCoreName" = "as:modconf('ResourceM')[1]/ResourceMMcalConfig/*[1]/ResourceMMasterCore"!][!//
            [!VAR "MasterCoreNumber" = "num:i(substring($MasterCoreName, 5, 1))"!][!//
        [!ENDSELECT!][!//
    [!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!ENDIF!][!// IF "not(var:defined('DMA_M'))