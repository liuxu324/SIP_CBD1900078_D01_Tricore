[!/*****************************************************************************
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
**  FILENAME  : Can_17_McmCan_PBCfg.c                                         **
**                                                                            **
**  VERSION   : 9.0.0                                                         **
**                                                                            **
**  DATE      : 2018-10-04                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Can_17_McmCan.bmd                                 **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={97DAC804-6076-4363-ABA1-A586E57B4955}]    **
**                 [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]    **
**                 [cover parentID={A7B6579C-0625-4f54-9CC9-6C4981949D65}]    **
**                 [cover parentID={8346EF3F-408D-417a-9CD2-2852FBA846C9}]    **
**                                                                            **
**  DESCRIPTION  : Code template source file for Can Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Can Driver, AUTOSAR Release 4.2.2     **
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
**  FILENAME  : Can_17_McmCan_PBCfg.c                                         **
**                                                                            **
**  VERSION   : 6.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                                          **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                                            **
**                                                                            **
**  BSW MODULE DECRIPTION : Can_17_McmCan.bmd                                 **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Can configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Can Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
[!//
[!/* Include Code Generator Macros */!][!//
[!INCLUDE "Can_17_McmCan.m"!][!//
[!//

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/* Include CAN Driver Header File */
#include "Can_17_McmCan.h"

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
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
[!/* [cover parentID={720574CD-C6BB-42f5-8D23-B70C74C282BD}]
[/cover] */!][!//
[!/* [cover parentID={A76860CA-435C-4783-A830-4A9AB6D92946}]
[/cover] */!][!//
[!//
[!VAR "MaxKernel" = "num:i(ecu:get('Can.MaxKernels'))"!][!//
[!VAR "MaxController" = "num:i(ecu:get('Can.MaxCtrlKer'))"!][!//
[!VAR "MaxConfigCont"= "num:i(ecu:get('Can.MaxControllers'))"!][!//
[!VAR "MaxCore" = "num:i(ecu:get('Mcu.NoOfCoreAvailable'))"!][!//
[!VAR "MsgRAMAddress0" = "num:hextoint(ecu:get(text:join(concat('Can.MCMCAN','0','BASERAM'))))"!][!//
[!VAR "MsgRAMAddress1" = "num:hextoint(ecu:get(text:join(concat('Can.MCMCAN','1','BASERAM'))))"!][!//
[!VAR "MsgRAMAddress2" = "num:hextoint(ecu:get(text:join(concat('Can.MCMCAN','2','BASERAM'))))"!][!//
[!VAR "TNoOfHth" = "num:i(0)"!][!//
[!VAR "ResKerCoreIndName" = "''"!][!//
[!VAR "CoreHthIndexName" = "''"!][!//
[!VAR "TNoOfHrh" = "num:i(0)"!][!//
[!VAR "ControllerConfigMax" = "num:i(0)"!][!//
[!VAR "Cntrlindx" = "num:i(0)"!][!//
[!VAR "HwObjindx" = "num:i(0)"!][!//
[!VAR "HwObjctMaxTemp" = "num:i(0)"!][!//
[!VAR "StandardIdOnly" = "num:i(0)"!][!//
[!VAR "MixedOnly" = "num:i(0)"!][!//
[!VAR "ExtendedOnly" = "num:i(0)"!][!//
[!VAR "TxObjectCountMax" = "num:i(0)"!][!//
[!VAR "RxObjectCountMax" = "num:i(0)"!][!//
[!VAR "FDNodesPresent" = "num:i(0)"!][!//
[!VAR "TxQueueUsedStatus" = "num:i(0)"!][!//
[!VAR "RXFIFO0UsedStatus" = "num:i(0)"!][!//
[!VAR "RXFIFO1UsedStatus" = "num:i(0)"!][!//
[!VAR "RXFIFOBuffFlag" = "num:i(0)"!][!//
[!VAR "ControllerBRConfigTemp" = "num:i(0)"!][!//
[!VAR "MainFunctTxPolling" = "num:i(0)"!][!//
[!VAR "MainFunctRxPolling" = "num:i(0)"!][!//
[!VAR "BaudrateIndx" = "num:i(0)"!][!//
[!VAR "PublicIcomSupport" = "num:i(0)"!][!//
[!VAR "NoOfIcomConfig" = "num:i(0)"!][!//
[!VAR "MultiCycleWriteOperCfg" = "num:i(0)"!][!//
[!VAR "MultiCycleReadOperCfg" = "num:i(0)"!][!//
[!VAR "HrhRefNameCheckMax" = "num:i(0)"!][!//
[!VAR "HthRefNameCheckMax" = "num:i(0)"!][!//
[!VAR "MainFuncNameHth" = "''"!][!//
[!VAR "MainFuncNameHrh" = "''"!][!//
[!/* Can Activated controller identification and allocation */!][!//
[!CALL "CAN_CG_ControllerAllocation"!][!//
[!/* Bring in core specific configuration of the CAN controllers */!][!//
[!CALL "CAN_CG_GenerateModuleMap","Module" = "'CAN'"!][!//
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Can')[1]/CanConfigSet"!][!//
[!VAR "ConfigPath" = "node:path(.)"!][!//
[!VAR "ConfigShortNamePath" = "substring-after($ConfigPath, 'CanConfigSet/')"!][!//
[!IF "../CanGeneral/CanPublicIcomSupport = 'true'"!][!//
    [!VAR "PublicIcomSupport" = "num:i(1)"!][!//
[!ENDIF!][!//
[!IF "node:exists(CanIcom/*[1]) = 'true'"!][!//
[!VAR "NoOfIcomConfig" = "num:i(1)"!][!//
[!ENDIF!][!//
[!IF "$PublicIcomSupport > num:i(0) and $NoOfIcomConfig = num:i(0)"!][!//
[!ERROR!][!//
Atleast one instance CanIcomConfig container should be configured when CanPublicIcomSupport in CanGeneral container is configured as 'true'.
[!ENDERROR!][!//
[!ENDIF!][!//
[!NOCODE!][!//
[!VAR "ControllerConfigMaxTemp" = "num:i(count(./CanController/*))"!][!//
[!FOR "Cntrlindx" = "1" TO "$ControllerConfigMaxTemp"!][!//
  [!IF "./CanController/*[position()=$Cntrlindx]/CanTxProcessing = 'POLLING'"!][!//
  [!VAR "MainFunctTxPolling" = "num:i(1)"!][!//
  [!ENDIF!][!//
  [!IF "./CanController/*[position()=$Cntrlindx]/CanRxProcessing = 'POLLING'"!][!//
  [!VAR "MainFunctRxPolling" = "num:i(1)"!][!//
  [!ENDIF!][!//
  [!VAR "ControllerBRConfigTemp" = "num:i(count(CanController/*[position()=$Cntrlindx]/CanControllerBaudrateConfig/*))"!][!//
  [!FOR "BaudrateIndx" = "1" TO "$ControllerBRConfigTemp"!][!//
    [!IF "(node:exists(CanController/*[position()=$Cntrlindx]/CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*))"!][!//
      [!VAR "FDNodesPresent" = "num:i(1)"!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
[!ENDFOR!][!//
[!VAR "HwObjctMaxTemp" = "num:i(count(./CanHardwareObject/*))"!][!//
[!FOR "HwObjindx" = "1" TO "$HwObjctMaxTemp"!][!//
    [!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanObjectType = 'TRANSMIT'"!][!//
        [!VAR "TxObjectCountMax" = "num:i($TxObjectCountMax+1)"!][!//
        [!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanHwObjectCount > 1"!][!//
            [!VAR "TxQueueUsedStatus" = "num:i(1)"!][!//
        [!ENDIF!][!//
        [!IF "node:refexists(./CanHardwareObject/*[position()=$HwObjindx]/CanMainFunctionRWPeriodRef/*[1])"!][!//
        [!VAR "TxMode"= "(node:value(./CanHardwareObject/*[position()=$HwObjindx]/CanControllerRef))"!][!//
        [!IF "node:ref($TxMode)/CanTxProcessing = 'POLLING'"!][!//
            [!VAR "MainFuncNameConfig"= "(node:value(./CanHardwareObject/*[position()=$HwObjindx]/CanMainFunctionRWPeriodRef/*[1]))"!][!//
            [!VAR "HthRefNameCheckMax" = "num:i($HthRefNameCheckMax+1)"!][!//
            [!IF "$HthRefNameCheckMax = num:i(1)"!][!//
                [!VAR "MainFuncNameHth" = "$MainFuncNameConfig"!][!//
            [!ENDIF!][!//
            [!IF "$MainFuncNameConfig != $MainFuncNameHth"!]
                [!VAR "MultiCycleWriteOperCfg" = "num:i(1)"!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDIF!][!//
    [!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanObjectType = 'RECEIVE'"!][!//
        [!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanHwObjectCount > 1"!][!//
            [!VAR "HwControllerId" = "num:i(node:ref(./CanHardwareObject/*[position()=$HwObjindx]/CanControllerRef)/CanControllerId)"!][!//
            [!IF "$RXFIFOBuffFlag = 1"!][!//
                [!IF "$HwControllerId = $LastCntrlId"!][!//
                    [!VAR "RXFIFO1UsedStatus" = "num:i(1)"!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
            [!IF "$RXFIFOBuffFlag = 0"!][!//
                [!VAR "RXFIFO0UsedStatus" = "num:i(1)"!][!//
                [!VAR "RXFIFOBuffFlag" = "num:i($RXFIFOBuffFlag+1)"!][!//
            [!ENDIF!][!//
            [!VAR "LastCntrlId" = "num:i($HwControllerId)"!][!//
            [!IF "$HwControllerId != $LastCntrlId"!][!//
                    [!VAR "RXFIFOBuffFlag" = "num:i(0)"!][!//
            [!ENDIF!][!//
            [!VAR "LastCntrlId" = "num:i($HwControllerId)"!][!//
        [!ENDIF!][!//
        [!VAR "RxObjectCountMax" = "num:i($RxObjectCountMax+1)"!][!//
        [!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanIdType = 'STANDARD'"!][!//
            [!VAR "StandardIdOnly" = "num:i(1)"!][!//
        [!ENDIF!][!//
        [!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanIdType = 'MIXED'"!][!//
            [!VAR "MixedOnly" = "num:i(1)"!][!//
        [!ENDIF!][!//
        [!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanIdType = 'EXTENDED'"!][!//
            [!VAR "ExtendedOnly" = "num:i(1)"!][!//
        [!ENDIF!][!//
        [!IF "node:refexists(./CanHardwareObject/*[position()=$HwObjindx]/CanMainFunctionRWPeriodRef/*[1])"!][!//
        [!VAR "RxMode"= "(node:value(./CanHardwareObject/*[position()=$HwObjindx]/CanControllerRef))"!][!//
        [!IF "node:ref($RxMode)/CanRxProcessing = 'POLLING'"!][!//
            [!VAR "MainFuncNameConfig"= "(node:value(./CanHardwareObject/*[position()=$HwObjindx]/CanMainFunctionRWPeriodRef/*[1]))"!][!//
            [!VAR "HrhRefNameCheckMax" = "num:i($HrhRefNameCheckMax+1)"!][!//
        [!IF "$HrhRefNameCheckMax = num:i(1)"!][!//
            [!VAR "MainFuncNameHrh" = "$MainFuncNameConfig"!][!//
        [!ENDIF!][!//
        [!IF "$MainFuncNameHrh != $MainFuncNameConfig"!][!//
            [!VAR "MultiCycleReadOperCfg" = "num:i(1)"!][!//
        [!ENDIF!][!//
        [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDFOR!][!//
[!ENDNOCODE!][!//
[!ENDSELECT!][!//
[!/* ICOM Related Calculations */!][!//
[!SELECT "as:modconf('Can')[1]/CanConfigSet"!][!//
[!VAR "IcomConfigCount" = "num:i(count(./CanIcom/*/CanIcomConfig/*))"!][!//
[!VAR "ICOMMsgSignalSupport" = " 0 "!][!//
[!VAR "IcomRxMsgSignalCount" = " 0 "!][!//
[!LOOP "CanIcom/*[1]/CanIcomConfig/*"!][!//
[!FOR "Index" = "1" TO "num:i($IcomConfigCount)"!][!//
[!IF "$Index = num:i(./CanIcomConfigId)"!][!//
[!VAR "IcomRxMsgCount" = "num:i(count(./CanIcomWakeupCauses/CanIcomRxMessage/*))"!][!//
[!FOR "Rxindx" = "1" TO "num:i($IcomRxMsgCount)"!][!//
[!IF "node:exists(./CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomRxMessageSignalConfig/*) = 'true'"!][!//
[!VAR "ICOMMsgSignalSupport" = "1"!][!//
[!VAR "IcomRxMsgSignalCount" = "num:i(count(./CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomRxMessageSignalConfig/*))"!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!VAR "InstanceHth" = "num:i(0)"!][!//
[!VAR "InstanceHrh" = "num:i(0)"!][!//
[!SELECT "as:modconf('Can')[1]/CanConfigSet"!][!//
[!VAR "ContAllocIndex" = "''"!][!//
[!VAR "HthIndexName" = "''"!][!//
[!FOR "CoreIndx" = "0" TO "$MaxCore - '1'"!][!//
[!VAR "NoOfSidFilt" = "num:i(0)"!][!//
[!VAR "NoOfXidFilt" = "num:i(0)"!][!//
[!VAR "NoOfTxObj" = "num:i(0)"!][!//
[!VAR "NoOfRxObj" = "num:i(0)"!][!//
[!VAR "NoOfTxPollObj" = "num:i(0)"!][!//
[!VAR "NoOfRxPollObj" = "num:i(0)"!][!//
[!VAR "CheckText" = "text:toupper(concat('CORE',$CoreIndx))"!][!//
[!VAR "Text" = "text:join(concat('Core', $CoreIndx))"!][!//
[!IF "text:contains( text:split($CGAllocCore,','), $CheckText )"!][!//
[!VAR "StandardIdOnlyTmp" = "num:i(0)"!][!//
[!VAR "MixedOnlyTmp" = "num:i(0)"!][!//
[!VAR "ExtendedOnlyTmp" = "num:i(0)"!][!//
[!VAR "TxObjectCountMaxTmp" = "num:i(0)"!][!//
[!VAR "RxObjectCountMaxTmp" = "num:i(0)"!][!//
[!VAR "TxQueueUsedStatusTmp" = "num:i(0)"!][!//
[!VAR "RXFIFO0UsedStatusTmp" = "num:i(0)"!][!//
[!VAR "RXFIFO1UsedStatusTmp" = "num:i(0)"!][!//
[!VAR "RXFIFOBuffFlagTmp" = "num:i(0)"!][!//
[!VAR "MultiCycleWriteOperCfgTmp" = "num:i(0)"!][!//
[!VAR "MainFunctTxPollingTmp" = "num:i(0)"!][!//
[!VAR "MainFunctTxPollUsedTmp" = "num:i(0)"!][!//
[!VAR "MainFunctRxPollUsedTmp" = "num:i(0)"!][!//
[!VAR "MainFunctRxPollingTmp" = "num:i(0)"!][!//
[!VAR "MultiCycleReadOperCfgTmp" = "num:i(0)"!][!//
[!VAR "HrhRefNameCheckMaxTmp" = "num:i(0)"!][!//
[!VAR "HthRefNameCheckMaxTmp" = "num:i(0)"!][!//
[!VAR "MainFuncNameHthTmp" = "''"!][!//
[!VAR "MainFuncNameHrhTmp" = "''"!][!//
[!VAR "FDNodesPresentTmp" = "num:i(0)"!][!//
[!VAR "ContConfigCount" = "num:i(count(./CanController/*))"!][!//
[!FOR "ContIndexPointing" = "0" TO "$ContConfigCount - 1"!][!//
[!VAR "ContCoreName" = "text:toupper(concat('CON',$ContIndexPointing,'_',$CheckText))"!][!//
[!IF "text:contains(text:split($CGResCoreMap,','),$ContCoreName)"!][!//
[!IF "./CanController/*[position()=($ContIndexPointing +num:i(1))]/CanTxProcessing = 'POLLING'"!][!//
[!VAR "MainFunctTxPollingTmp" = "num:i(1)"!][!//
[!ENDIF!][!//
[!IF "./CanController/*[position()=($ContIndexPointing +num:i(1))]/CanRxProcessing = 'POLLING'"!][!//
[!VAR "MainFunctRxPollingTmp" = "num:i(1)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!VAR "HwObjctMaxTemp" = "num:i(count(./CanHardwareObject/*))"!][!//
[!FOR "HwObjindx" = "1" TO "$HwObjctMaxTemp"!][!//
[!VAR "HwControllerId" = "num:i(node:ref(./CanHardwareObject/*[position()=$HwObjindx]/CanControllerRef)/CanControllerId)"!][!//
[!FOR "KerIndex" = "0" TO "$MaxKernel -'1'"!][!//
[!VAR "ResKerCoreName" = "text:toupper(concat('CON',$HwControllerId,'_','KERNEL',$KerIndex,'_',$CheckText))"!][!//
[!IF "text:contains(text:split($CGCoreMap,','),$ResKerCoreName)"!][!//
    [!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanObjectType = 'TRANSMIT'"!][!//
      [!IF "$MainFunctTxPollingTmp = num:i(1)"!][!//
        [!VAR "MainFunctTxPollUsedTmp" = "num:i(1)"!][!//
      [!ENDIF!][!//
        [!VAR "TxObjectCountMaxTmp" = "num:i($TxObjectCountMaxTmp+1)"!][!//
        [!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanHwObjectCount > 1"!][!//
            [!VAR "TxQueueUsedStatusTmp" = "num:i(1)"!][!//
        [!ENDIF!][!//
        [!IF "node:refexists(./CanHardwareObject/*[position()=$HwObjindx]/CanMainFunctionRWPeriodRef/*[1])"!][!//
        [!VAR "TxMode"= "(node:value(./CanHardwareObject/*[position()=$HwObjindx]/CanControllerRef))"!][!//
        [!IF "node:ref($TxMode)/CanTxProcessing = 'POLLING'"!][!//
            [!VAR "MainFuncNameConfigTmp"= "(node:value(./CanHardwareObject/*[position()=$HwObjindx]/CanMainFunctionRWPeriodRef/*[1]))"!][!//
            [!VAR "HthRefNameCheckMaxTmp" = "num:i($HthRefNameCheckMaxTmp+1)"!][!//
            [!IF "$HthRefNameCheckMaxTmp = num:i(1)"!][!//
                [!VAR "MainFuncNameHthTmp" = "$MainFuncNameConfigTmp"!][!//
            [!ENDIF!][!//
            [!IF "$MainFuncNameConfigTmp != $MainFuncNameHthTmp"!]
                [!VAR "MultiCycleWriteOperCfgTmp" = "num:i(1)"!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDIF!][!//
    [!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanObjectType = 'RECEIVE'"!][!//
      [!IF "$MainFunctRxPollingTmp = num:i(1)"!][!//
        [!VAR "MainFunctRxPollUsedTmp" = "num:i(1)"!][!//
      [!ENDIF!][!//
        [!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanHwObjectCount > 1"!][!//
            [!VAR "HwControllerId" = "num:i(node:ref(./CanHardwareObject/*[position()=$HwObjindx]/CanControllerRef)/CanControllerId)"!][!//
            [!IF "$RXFIFOBuffFlagTmp = 1"!][!//
                [!IF "$HwControllerId = $LastCntrlIdTmp"!][!//
                    [!VAR "RXFIFO1UsedStatusTmp" = "num:i(1)"!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
            [!IF "$RXFIFOBuffFlagTmp = 0"!][!//
                [!VAR "RXFIFO0UsedStatusTmp" = "num:i(1)"!][!//
                [!VAR "RXFIFOBuffFlagTmp" = "num:i($RXFIFOBuffFlagTmp+1)"!][!//
            [!ENDIF!][!//
            [!VAR "LastCntrlIdTmp" = "num:i($HwControllerId)"!][!//
            [!IF "$HwControllerId != $LastCntrlIdTmp"!][!//
                    [!VAR "RXFIFOBuffFlagTmp" = "num:i(0)"!][!//
            [!ENDIF!][!//
            [!VAR "LastCntrlIdTmp" = "num:i($HwControllerId)"!][!//
        [!ENDIF!][!//
        [!VAR "RxObjectCountMaxTmp" = "num:i($RxObjectCountMaxTmp+1)"!][!//
        [!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanIdType = 'STANDARD'"!][!//
            [!VAR "StandardIdOnlyTmp" = "num:i(1)"!][!//
        [!ENDIF!][!//
        [!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanIdType = 'MIXED'"!][!//
            [!VAR "MixedOnlyTmp" = "num:i(1)"!][!//
        [!ENDIF!][!//
        [!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanIdType = 'EXTENDED'"!][!//
            [!VAR "ExtendedOnlyTmp" = "num:i(1)"!][!//
        [!ENDIF!][!//
        [!IF "node:refexists(./CanHardwareObject/*[position()=$HwObjindx]/CanMainFunctionRWPeriodRef/*[1])"!][!//
        [!VAR "RxMode"= "(node:value(./CanHardwareObject/*[position()=$HwObjindx]/CanControllerRef))"!][!//
        [!IF "node:ref($RxMode)/CanRxProcessing = 'POLLING'"!][!//
            [!VAR "MainFuncNameConfigTmp"= "(node:value(./CanHardwareObject/*[position()=$HwObjindx]/CanMainFunctionRWPeriodRef/*[1]))"!][!//
            [!VAR "HrhRefNameCheckMaxTmp" = "num:i($HrhRefNameCheckMaxTmp+1)"!][!//
        [!IF "$HrhRefNameCheckMaxTmp = num:i(1)"!][!//
            [!VAR "MainFuncNameHrhTmp" = "$MainFuncNameConfigTmp"!][!//
        [!ENDIF!][!//
        [!IF "$MainFuncNameHrhTmp != $MainFuncNameConfigTmp"!][!//
            [!VAR "MultiCycleReadOperCfgTmp" = "num:i(1)"!][!//
        [!ENDIF!][!//
        [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDFOR!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
#define [!"text:toupper(concat('CAN_17_MCMCAN_START_SEC_CONFIG_DATA_QM_',$CheckText,'_UNSPECIFIED'))"!]
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"

/*******************************************************************************
               Can Controller Configurations for [!"$Text"!]
********************************************************************************
    { Can node Base Address,Combination value of Rx pin select and
    Loopback mode Support,{First Tx Hardware Object, No.of Tx Hardware Objects,
    First Rx Standard Hardware Object, No.of Rx Standard Hardware Objects,
    First Rx Extended Hardware Object, No.of Rx Extended Hardware Objects},
    Default baudrate Config index,First baudrate index for the controller,
    No.of baudrate configuration,Associated kernel Id, Controller Hw Id,
    Logical controller Id,[FD support status] }
********************************************************************************
       Note: [1] The configuration shall be generated only for the activated
                 controller
             [2] The Generation of FD support status Shall be enabled only if
             atleast one of the baudrates configured in the configuration set is
             FD.
*******************************************************************************/
[!VAR "BaudrateIndex" = "num:i(0)"!][!//
[!VAR "ControllerIndex" = "num:i(0)"!][!//
[!VAR "HwControllerCount" = "num:i(count(./CanController/*))"!][!//
[!/* Bring in core specific CAN controller count */!][!//
[!CALL "CAN_CG_GetContInCore","CoreName" = "$CheckText"!][!//
[!/* [cover parentID={2F633CE6-51CC-41a5-AD87-89E790BE38A6}]
[/cover] */!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
static const Can_17_McmCan_ControllerConfigType \
  Can_17_McmCan_kControllerConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][[!"$NoOfCont"!]] =
{
[!NOCODE!][!//
[!VAR "FirstTxIndx" = "num:i(0)"!][!//
[!VAR "NoOfTx" = "num:i(0)"!][!//
[!VAR "FirstSIDIndx" = "num:i(0)"!][!//
[!VAR "NoOfSID" = "num:i(0)"!][!//
[!VAR "FirstXIDIndx" = "num:i(0)"!][!//
[!VAR "NoOfXID" = "num:i(0)"!][!//
[!VAR "NoOfTxTemp" = "num:i(0)"!][!//
[!VAR "NoOfSIDTemp" = "num:i(0)"!][!//
[!VAR "NoOfXIDTemp" = "num:i(0)"!][!//
[!VAR "FDNodes" = "num:i(0)"!][!//
[!VAR "IndexCnt" = "num:i(0)"!][!//
[!ENDNOCODE!][!//
[!AUTOSPACING!]
[!INDENT "4"!]
[!NOCODE!][!//
[!/* Set loop for read all the configured controller informations */!][!//
[!LOOP "./CanController/*"!][!//
[!VAR "NPCRTemp" = "num:i(0)"!][!//
    [!VAR "TempControllerId" = "num:i(CanControllerId)"!][!//
    [!IF "CanControllerActivation = 'true'"!][!//
    [!FOR "KerIndex" = "0" TO "$MaxKernel -'1'"!][!//
    [!VAR "ResKerCoreName" = "text:toupper(concat('CON',$TempControllerId,'_','KERNEL',$KerIndex,'_',$CheckText))"!][!//
    [!IF "text:contains(text:split($CGCoreMap,','),$ResKerCoreName)"!][!//
    [!VAR "ResKerCoreConIndName" = "text:toupper(concat($ResKerCoreName,'_','CONIND',$ControllerIndex))"!][!//
    [!VAR "ControllerIndex" = "num:i($ControllerIndex+1)"!][!//
        [!IF "$IndexCnt > '0'"!][!//
        [!CODE!][!//
        ,
        [!ENDCODE!][!//
        [!ENDIF!][!//
        [!VAR "IndexCnt" = "num:i($IndexCnt+1)"!][!//
    [!VAR "BaseAddress" = "num:i(CanControllerBaseAddress)"!][!//
[!CODE!][!//
  {
    /* Can controller Base Node address */
    /* MISRA2012_RULE_11_6_JUSTIFICATION: The pointer cast is used to
    cast the generated address with CAN Node structure type */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and
    integer type. Permitted for special function registers.*/
    (volatile Ifx_CAN_N*)[!"num:inttohex($BaseAddress)"!]U,
[!ENDCODE!][!//
    [!IF "CanControllerLoopbackEnable = 'true'"!][!//
        [!VAR "NPCRTemp" = "bit:bitset($NPCRTemp,8)"!][!//
    [!ELSEIF "CanRxInputSelection = 'CANxx_RXDB'"!][!//
        [!VAR "NPCRTemp" = "bit:or($NPCRTemp,1)"!][!//
    [!ELSEIF "CanRxInputSelection = 'CANxx_RXDC'"!][!//
        [!VAR "NPCRTemp" = "bit:or($NPCRTemp,2)"!][!//
    [!ELSEIF "CanRxInputSelection = 'CANxx_RXDD'"!][!//
        [!VAR "NPCRTemp" = "bit:or($NPCRTemp,3)"!][!//
    [!ELSEIF "CanRxInputSelection = 'CANxx_RXDE'"!][!//
        [!VAR "NPCRTemp" = "bit:or($NPCRTemp,4)"!][!//
    [!ELSEIF "CanRxInputSelection = 'CANxx_RXDF'"!][!//
        [!VAR "NPCRTemp" = "bit:or($NPCRTemp,5)"!][!//
    [!ELSEIF "CanRxInputSelection = 'CANxx_RXDG'"!][!//
        [!VAR "NPCRTemp" = "bit:or($NPCRTemp,6)"!][!//
    [!ELSEIF "CanRxInputSelection = 'CANxx_RXDH'"!][!//
        [!VAR "NPCRTemp" = "bit:or($NPCRTemp,7)"!][!//
    [!ENDIF!][!//
    [!CODE!][!//
    /* combination of Loopback and receive input pin selection setting */
    [!"num:inttohex($NPCRTemp)"!]U,
    [!ENDCODE!][!//
    [!LOOP "../../CanHardwareObject/*"!][!//
        [!IF "node:refexists(CanControllerRef) ='true'"!][!//
            [!VAR "HwControllerId" = "num:i(node:ref(CanControllerRef)/CanControllerId)"!][!//
            [!IF "$HwControllerId = $TempControllerId"!][!//
                [!IF "CanObjectType = 'TRANSMIT'"!][!//
                    [!VAR "NoOfTxTemp" = "num:i($NoOfTxTemp+1)"!][!//
                [!ENDIF!][!//
                [!IF "CanObjectType = 'RECEIVE'"!][!//
                    [!VAR "HwFilterCount" = "num:i(count(CanHwFilter/*))"!][!//
                    [!FOR "HwFilterindx" = "1" TO "$HwFilterCount"!][!//
                        [!VAR "HwFilterValue" = "num:i(CanHwFilter/*[position()=$HwFilterindx]/CanHwFilterCode)"!][!//
                        [!IF "CanIdType = 'STANDARD' or CanIdType = 'MIXED' "!][!//
                            [!VAR "NoOfSIDTemp" = "num:i($NoOfSIDTemp+1)"!][!//
                        [!ENDIF!][!//
                        [!IF "CanIdType = 'EXTENDED' or CanIdType = 'MIXED' "!][!//
                            [!VAR "NoOfXIDTemp" = "num:i($NoOfXIDTemp+1)"!][!//
                        [!ENDIF!][!//
                    [!ENDFOR!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    /* 1.Set first Index with Tx start Index*/
    /* 2.Set Second Index with total no of HTH configuration */
    /* 3.Set Third Index with SID filter mask start Index */
    /* 4.Set Fourth Index with total no of SID filter mask configuration */
    /* 5.Set Fifth Index with XID filter mask start Index */
    /* 6.Set Sixth Index with total no of XID filter mask configuration */
    [!CODE!][!//
    /* The controller Hw object configuration mapping information */
    {
[!INDENT "6"!]
      /* Tx Message storage start Index */
      [!"num:inttohex($FirstTxIndx)"!]U,
    [!VAR "FirstTxIndx" = "num:i($FirstTxIndx+$NoOfTxTemp)"!][!//
      /* Total no of Tx Message configured */
      [!"num:inttohex($NoOfTxTemp)"!]U,
    [!VAR "NoOfTxTemp" = "num:i(0)"!][!//
      /* Rx Message SID filter mask start Index */
      [!"num:inttohex($FirstSIDIndx)"!]U,
    [!VAR "FirstSIDIndx" = "num:i($FirstSIDIndx+$NoOfSIDTemp)"!][!//
      /* Total no of SID filter mask configured */
      [!"num:inttohex($NoOfSIDTemp)"!]U,
    [!VAR "NoOfSIDTemp" = "num:i(0)"!][!//
      /* Rx Message XID filter mask start Index */
      [!"num:inttohex($FirstXIDIndx)"!]U,
    [!VAR "FirstXIDIndx" = "num:i($FirstXIDIndx+$NoOfXIDTemp)"!][!//
      /* Total no of XID filter mask configured */
      [!"num:inttohex($NoOfXIDTemp)"!]U
[!ENDINDENT!]
    },
    [!VAR "NoOfXIDTemp" = "num:i(0)"!][!//
    [!ENDCODE!][!//
    [!IF "node:refexists(CanControllerDefaultBaudrate) ='true'"!][!//
    [!VAR "CanDefaultBaudrateRef" = "node:path(node:ref(CanControllerDefaultBaudrate))"!][!//
    [!IF "contains($CanDefaultBaudrateRef, node:path(.)) = 'true'"!][!//
    [!ELSE!][!//
    [!ERROR!][!//
    [!VAR "CanConfigSetName" = "substring-after(node:path(.), "CanConfigSet/")"!][!//
    [!VAR "CanConfigSetName" = "substring-before($CanConfigSetName, "/")"!][!//
    The CanControllerId[!"CanControllerId"!] is referred to a default baudrate which does not belong to the same CanController.[!//
    [!ENDERROR!][!//
    [!ENDIF!][!//
    [!ENDIF!][!//
    [!VAR "DefaultBaudrateCfgIndx" = "num:i(node:ref(CanControllerDefaultBaudrate)/CanControllerBaudRateConfigID)"!][!//
    /* Set DefaultBaudrateCfgIndx value */
    [!CODE!][!//
    /* Default baudrate configuration Index */
    [!"num:inttohex($DefaultBaudrateCfgIndx+$BaudrateIndex)"!]U,
    [!ENDCODE!][!//
    /* Set CanBaudrateCfgIndx value */
    [!CODE!][!//
    /* Start index value of Baudrate configuration */
    [!"num:inttohex($BaudrateIndex)"!]U,
    [!ENDCODE!][!//
    [!VAR "NoOfBaudrateCfg" = "num:i(count(./CanControllerBaudrateConfig/*))"!][!//
    /* Set Total no of Baudrate configurations (NoOfBaudrateCfg) value */
    [!CODE!][!//
    /* Total no of Baudrate configuration */
    [!"num:inttohex($NoOfBaudrateCfg)"!]U,
    [!ENDCODE!][!//
    [!VAR "BaudrateIndex" = "num:i($BaudrateIndex + $NoOfBaudrateCfg)"!][!//
  [!VAR "Node0Present" = "num:i(1)"!][!//
    /* Set CanKernelHwId parameter with Kernel Hw configuration index number */
    [!CODE!][!//
    /* The controller Associated Kernel configuration Index */
    [!"num:inttohex($KerIndex)"!]U,
    [!ENDCODE!][!//
    [!FOR "ContIndex" = "0" TO "$MaxController -'1'"!][!//
    [!VAR "Nodename" = "text:join(concat('Can.Node',$KerIndex,$ContIndex,'BaseAddress'))"!][!//
    [!IF "($BaseAddress = num:hextoint(ecu:get($Nodename)))"!][!//
    [!VAR "ResKerCoreIndName" = "text:toupper(concat($ResKerCoreIndName,$ResKerCoreConIndName,'_','NODEIND',$ContIndex,','))"!][!//
    [!CODE!][!//
    /* The CAN controller Hw Index */
    [!"text:join(concat('0x0',$ContIndex,'U'))"!],
    /* The CAN controller Logical Hw Index - Controller ID defined by user */
    [!"$TempControllerId"!][!//
    [!ENDCODE!][!//
    [!ENDIF!][!//
    [!ENDFOR!][!//
    [!IF "$FDNodesPresent = '1'"!][!//
        [!VAR "FDNodes" = "num:i(0)"!][!//
        [!VAR "ControllerBRConfigTemp" = "num:i(count(./CanControllerBaudrateConfig/*))"!][!//
        [!FOR "BaudrateIndx" = "1" TO "$ControllerBRConfigTemp"!][!//
            [!IF "(node:exists(CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*))"!][!//
            [!VAR "FDNodes" = "num:i(1)"!][!//
            [!ENDIF!][!//
        [!ENDFOR!][!//
        [!CODE!][!//
        ,
        [!IF "$FDNodes = '1'"!][!//
            /* FD support status of the controller */
            TRUE
        [!ELSE!][!//
            /* FD support status of the controller */
            FALSE
        [!ENDIF!][!//
        }[!//
        [!ENDCODE!][!//
    [!ELSE!][!//
    [!CODE!][!//

    }[!//
    [!ENDCODE!][!//
    [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDFOR!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!][!//
[!ENDINDENT!]

};

/*******************************************************************************
              Controller Id to Index Map configuration for [!"$Text"!]
********************************************************************************
    {Array holding the respective logical Controller ID at the core specific
    controller index }
********************************************************************************
           Note: This shall be generated only for the controllers allocated
           for the current core.
*******************************************************************************/
[!VAR "Count1" = "num:i(0)"!][!//
[!/* [cover parentID={B1ED8A4F-BF15-4aac-BF2C-E9DF09DE4E12}]
[/cover] */!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
static const Can_17_McmCan_ControllerIndexType \
  Can_17_McmCan_kControllerIndexing[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][[!"$NoOfCont"!]] =
{[!//
[!FOR "CoreSpecContIndex" = "0" TO "$NoOfCont -'1'"!][!//
[!VAR "ControllerExists" = "num:i(0)"!][!//
[!LOOP "./CanController/*"!][!//
[!VAR "TempControllerId" = "num:i(CanControllerId)"!][!//
[!FOR "KerIndex" = "0" TO "$MaxKernel -'1'"!][!//
[!FOR "NodeIndex" = "0" TO "$MaxController -'1'"!][!//
[!VAR "ResKerCoreIndexTmp" = "text:toupper(concat('CON',$TempControllerId,'_','KERNEL',$KerIndex,'_',$CheckText,'_','CONIND',$CoreSpecContIndex,'_','NODEIND',$NodeIndex))"!][!//
[!IF "text:contains(text:split($ResKerCoreIndName,','),$ResKerCoreIndexTmp)"!][!//
  [!VAR "ControllerExists" = "num:i(1)"!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDFOR!][!//
[!IF "$ControllerExists = num:i(1)"!][!//
[!IF "$Count1 > '0'"!][!//
,[!//
[!ENDIF!][!//
[!VAR "Count1" = "num:i($Count1+'1')"!][!//
[!"$TempControllerId"!][!//
[!ENDIF!][!//
[!VAR "ControllerExists" = "num:i(0)"!][!//
[!ENDLOOP!]
[!ENDFOR!][!//
};

[!VAR "IndexCnt" = "num:i(0)"!][!//
/*******************************************************************************
              Message RAM partition configuration for [!"$Text"!]
********************************************************************************
      {{start address of SID section,start address of XID section,
      start address of FIFO0 section,start address of FIFO1 section,start
      address of Rx dedicated buffer section,start address of Tx Event section,
      start address of Tx dedicated buffer section},Tx_ded_Buff size,
      Tx_Evnt size,[Rx_FIFO0 size],[Rx_FIFO0 Threshold],[Rx_FIFO1 size],
      [Rx_FIFO1 Threshold],[Tx_Queue size],[Tx_Queue Enable Status]}
********************************************************************************
           Note: This shall be generated only for the activated controller
*******************************************************************************/
[!/* [cover parentID={458A463B-CDD8-47d9-896B-26A7350B2E5E}]
[/cover] */!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
static const Can_17_McmCan_ControllerMsgRAMConfigType \
  Can_17_McmCan_kControllerMsgRAMMapConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][[!"$NoOfCont"!]] =
{
[!VAR "NODEENDADDRESS" = "num:i(0)"!][!//
[!VAR "HwControllerCount" = "num:i(count(./CanController/*))"!][!//
[!FOR "HwIndex" = "0" TO "$HwControllerCount - '1'"!][!//
[!LOOP "./CanController/*"!][!//
[!VAR "TempControllerId" = "num:i(CanControllerId)"!][!//
[!IF "$HwIndex = $TempControllerId"!][!//
[!IF "CanControllerActivation = 'true'"!][!//
[!FOR "KerIndex" = "0" TO "$MaxKernel -'1'"!][!//
[!VAR "ResKerCoreName" = "text:toupper(concat('CON',$TempControllerId,'_','KERNEL',$KerIndex,'_',$CheckText))"!][!//
[!IF "text:contains(text:split($CGCoreMap,','),$ResKerCoreName)"!][!//
[!IF "$KerIndex = num:i(0)"!][!//
  [!VAR "FLSSA" = "$MsgRAMAddress0"!][!//
[!ELSEIF "$KerIndex = num:i(1)"!][!//
  [!VAR "FLSSA" = "$MsgRAMAddress1"!][!//
[!ELSE!][!//
  [!VAR "FLSSA" = "$MsgRAMAddress2"!][!//
[!ENDIF!][!//
[!VAR "NoOfTxDedBuff" = "num:i(0)"!][!//
[!VAR "NoOfRxDedBuff" = "num:i(0)"!][!//
[!VAR "SizeOfTxQue" = "num:i(0)"!][!//
[!VAR "RxFIFOCount" = "num:i(0)"!][!//
[!VAR "TxQueueCount" = "num:i(0)"!][!//
[!VAR "SizeOfRxFIFO1" = "num:i(0)"!][!//
[!VAR "SizeOfRxFIFO0" = "num:i(0)"!][!//
[!VAR "RxFIFO1Threshold" = "num:i(0)"!][!//
[!VAR "RxFIFO0Threshold" = "num:i(0)"!][!//
[!VAR "NoOfSIDTemp" = "num:i(0)"!][!//
[!VAR "NoOfXIDTemp" = "num:i(0)"!][!//
[!LOOP "../../CanHardwareObject/*"!][!//
    [!IF "node:refexists(CanControllerRef) ='true'"!][!//
    [!VAR "HwControllerId" = "num:i(node:ref(CanControllerRef)/CanControllerId)"!][!//
    [!IF "$HwControllerId = $TempControllerId"!][!//
    [!IF "CanObjectType = 'TRANSMIT' and CanHwObjectCount = '1' "!][!//
    [!VAR "NoOfTxDedBuff" = "num:i($NoOfTxDedBuff+1)"!][!//
    [!IF "node:ref(CanControllerRef)/CanTxProcessing = 'POLLING'"!][!//
    [!VAR "NoOfTxPollObj" = "num:i($NoOfTxPollObj + 1)"!][!//
    [!ENDIF!]
    [!VAR "CanObjectIdTemp" = "num:i(CanObjectId)"!][!//
    [!ENDIF!][!//
    [!IF "CanObjectType = 'TRANSMIT' and CanHwObjectCount > '1' and CanHwObjectCount < '33' "!][!//
    [!IF "node:ref(CanControllerRef)/CanTxProcessing = 'POLLING'"!][!//
    [!VAR "NoOfTxPollObj" = "num:i($NoOfTxPollObj + 1)"!][!//
    [!ENDIF!]
    [!VAR "SizeOfTxQue" = "num:i(CanHwObjectCount)"!][!//
    [!IF "$TxQueueCount > '0' "!][!//
    [!ERROR!][!//
    The Cancontroller [!"$HwControllerId"!] is configured with more than <1> HTH with the CanHwObjectCount is greater than value <1>.This type of configuration is allowed for
    a specific controller is limited with <1> since controller is supported with one TxQueue.
    [!ENDERROR!][!//
    [!ENDIF!][!//
    [!VAR "TxQueueCount" = "num:i($TxQueueCount+1)"!][!//
    [!ENDIF!][!//
    [!IF "CanObjectType = 'RECEIVE' and CanHwObjectCount = '1' "!][!//
    [!VAR "NoOfRxDedBuff" = "num:i($NoOfRxDedBuff+1)"!][!//
    [!IF "node:ref(CanControllerRef)/CanRxProcessing = 'POLLING'"!][!//
    [!VAR "NoOfRxPollObj" = "num:i($NoOfRxPollObj + 1)"!][!//
    [!ENDIF!]
    [!ENDIF!][!//
    [!IF "CanObjectType = 'RECEIVE' and CanHwObjectCount > '1' "!][!//
    [!IF "$RxFIFOCount > '1' "!][!//
    [!ERROR!][!//
    The Cancontroller[!"$HwControllerId"!] is configured with more than <2> HRH which contains the CanHwObjectCount is greater than value <1>.This type of configuration is allowed for
    a specific controller is limited with <2> since controller is supported with 2 RXFIFOs only.
    [!ENDERROR!][!//
    [!ENDIF!][!//
    [!IF "$RxFIFOCount = '1' "!][!//
    [!VAR "SizeOfRxFIFO1" = "num:i(CanHwObjectCount)"!][!//
    [!VAR "RxFIFO1Threshold" = "num:i(CanHwFIFOThreshold)"!][!//
    [!VAR "RxFIFOCount" = "num:i($RxFIFOCount+1)"!][!//
    [!IF "node:ref(CanControllerRef)/CanRxProcessing = 'POLLING'"!][!//
    [!VAR "NoOfRxPollObj" = "num:i($NoOfRxPollObj + 1)"!][!//
    [!ENDIF!]
    [!ENDIF!][!//
    [!IF "$RxFIFOCount = '0' "!][!//
    [!VAR "SizeOfRxFIFO0" = "num:i(CanHwObjectCount)"!][!//
    [!VAR "RxFIFO0Threshold" = "num:i(CanHwFIFOThreshold)"!][!//
    [!VAR "RxFIFOCount" = "num:i($RxFIFOCount+1)"!][!//
    [!IF "node:ref(CanControllerRef)/CanRxProcessing = 'POLLING'"!][!//
    [!VAR "NoOfRxPollObj" = "num:i($NoOfRxPollObj + 1)"!][!//
    [!ENDIF!]
    [!ENDIF!][!//
    [!ENDIF!][!//
    [!IF "CanObjectType = 'RECEIVE'"!][!//
    [!VAR "HwFilterCount" = "num:i(count(CanHwFilter/*))"!][!//
    [!FOR "HwFilterindx" = "1" TO "$HwFilterCount"!][!//
    [!VAR "HwFilterValue" = "num:i(CanHwFilter/*[position()=$HwFilterindx]/CanHwFilterCode)"!][!//
    [!IF "CanIdType = 'STANDARD' or CanIdType = 'MIXED' "!][!//
    [!VAR "NoOfSIDTemp" = "num:i($NoOfSIDTemp+1)"!][!//
    [!ENDIF!][!//
    [!IF "CanIdType = 'EXTENDED' or CanIdType = 'MIXED' "!][!//
    [!VAR "NoOfXIDTemp" = "num:i($NoOfXIDTemp+1)"!][!//
    [!ENDIF!][!//
    [!ENDFOR!][!//
    [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!IF "$SizeOfRxFIFO1 < $RxFIFO1Threshold "!][!//
   [!ERROR!][!//
   The configurtion value of CanHwFIFOThreshold of HRH refernced by Cancontroller [!"$TempControllerId"!] is wrong.The value of CanHwFIFOThreshold
   shall be less than or equal with CanHwObjectCount.
[!ENDERROR!][!//
[!ENDIF!][!//
[!IF "$SizeOfRxFIFO0 < $RxFIFO0Threshold "!][!//
  [!ERROR!][!//
  The configurtion value of CanHwFIFOThreshold of HRH refernced by Cancontroller [!"$TempControllerId"!] is wrong.The value of CanHwFIFOThreshold
  shall be less than or equal with CanHwObjectCount.
  [!ENDERROR!][!//
[!ENDIF!][!//
[!IF "$NoOfSIDTemp > 128 "!][!//
  [!ERROR!][!//
  The toatl number of standard message filter elements configuration for controller [!"$TempControllerId"!] is greater than limit value <128>
  [!ENDERROR!][!//
[!ENDIF!][!//
[!IF "$NoOfXIDTemp > 64 "!][!//
  [!ERROR!][!//
  The total number of Extended message filter elements configuration for controller [!"$TempControllerId"!] is greater than limit value <64>
  [!ENDERROR!][!//
[!ENDIF!][!//
[!IF "$NoOfRxDedBuff > 64 "!][!//
[!ERROR!][!//
The total number of HRH configuration for the controller [!"$TempControllerId"!] is greater than limit value <64>
[!ENDERROR!][!//
[!ENDIF!][!//
[!IF "$NoOfTxDedBuff > 32 "!][!//
[!ERROR!][!//
The total number of HTH is configured for the controller [!"$TempControllerId"!]is greater than limit value <32>
[!ENDERROR!][!//
[!ENDIF!][!//
[!IF "(($NoOfTxDedBuff+$SizeOfTxQue) > 32 )"!][!//
[!ERROR!][!//
The total number of Hardware objects (sum of all HTH CanHwObjectCount) used by the controller[!"$TempControllerId"!] is greater than limit value <32>
[!ENDERROR!][!//
[!ENDIF!][!//
[!VAR "MsgRAMElementSize" = "num:i(4)"!][!//
[!IF "$FDNodesPresent = '1'"!][!//
[!VAR "ControllerBRConfigTemp" = "num:i(count(./CanControllerBaudrateConfig/*))"!][!//
[!FOR "BaudrateIndx" = "1" TO "$ControllerBRConfigTemp"!][!//
[!IF "(node:exists(CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*))"!][!//
[!VAR "MsgRAMElementSize" = "num:i(18)"!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!VAR "FLESA" = "num:i($FLSSA)  +(num:i($NoOfSIDTemp) * num:i(4)) "!][!//
[!VAR "F0SA"  = "num:i($FLESA)  +(num:i($NoOfXIDTemp)  * num:i(2) * num:i(4)) "!][!//
[!VAR "F1SA"  = "num:i($F0SA)   +(num:i($SizeOfRxFIFO0) * num:i($MsgRAMElementSize) * num:i(4)) "!][!//
[!VAR "RBSA"  = "num:i($F1SA)   +(num:i($SizeOfRxFIFO1) * num:i($MsgRAMElementSize) * num:i(4)) "!][!//
[!VAR "EFSA"  = "num:i($RBSA) +(num:i($NoOfRxDedBuff) * num:i($MsgRAMElementSize) * num:i(4)) "!][!//
[!VAR "TBSA"  = "num:i($EFSA) +((num:i($NoOfTxDedBuff)+num:i($SizeOfTxQue)) * num:i(2) * num:i(4)) "!][!//
[!VAR "NODEENDADDRESS" = "num:i($TBSA) +((num:i($NoOfTxDedBuff) + num:i($SizeOfTxQue)) * num:i($MsgRAMElementSize) * num:i(4)) "!][!//
[!IF "$KerIndex = '0' "!][!//
  [!VAR "MsgRAMAddress0" = "num:i($NODEENDADDRESS)"!][!//
[!ELSEIF "$KerIndex = '1' "!][!//
  [!VAR "MsgRAMAddress1" = "num:i($NODEENDADDRESS)"!][!//
[!ELSE!][!//
  [!VAR "MsgRAMAddress2" = "num:i($NODEENDADDRESS)"!][!//
[!ENDIF!][!//
[!IF "$NODEENDADDRESS > ecu:get(text:join(concat('Can.MCMCAN',$KerIndex,'ENDRAM')))"!][!//
  [!ERROR!][!//
    M_CAN is configured to use more MessageRAM than allowed by CAN Kernel
  [!ENDERROR!][!//
[!ENDIF!][!//
[!IF "$IndexCnt > '0'"!][!//
,

[!ENDIF!][!//
[!AUTOSPACING!]
[!INDENT "2"!][!//
[!VAR "IndexCnt" = "num:i($IndexCnt+1)"!][!//
 {
   /* Start Address of each section within the Message RAM */
  {
[!IF "$NoOfSIDTemp > 0 "!][!//
 [!"num:inttohex($FLSSA)"!]UL,
[!ELSE!][!//
 0x00000000UL,
[!ENDIF!][!//
[!IF "$NoOfXIDTemp > 0 "!][!//
 [!"num:inttohex($FLESA)"!]UL,
[!ELSE!][!//
 0x00000000UL,
[!ENDIF!][!//
[!IF "$SizeOfRxFIFO0 > 0 "!][!//
 [!"num:inttohex($F0SA)"!]UL,
[!ELSE!][!//
 0x00000000UL,
[!ENDIF!][!//
[!IF "$SizeOfRxFIFO1 > 0 "!][!//
 [!"num:inttohex($F1SA)"!]UL,
[!ELSE!][!//
 0x00000000UL,
[!ENDIF!][!//
[!IF "$NoOfRxDedBuff > 0 "!][!//
 [!"num:inttohex($RBSA)"!]UL,
[!ELSE!][!//
 0x00000000UL,
[!ENDIF!][!//
[!IF "($NoOfTxDedBuff+$TxQueueCount) > 0"!][!//
 [!"num:inttohex($EFSA)"!]UL,
 [!"num:inttohex($TBSA)"!]UL
 },
[!ELSE!][!//
 0x00000000UL,
 0x00000000UL
},
[!ENDIF!][!//
 [!"num:inttohex($NoOfTxDedBuff)"!]U, [!//
[!"num:inttohex($NoOfTxDedBuff+$SizeOfTxQue)"!]U, [!//
[!"num:inttohex($SizeOfRxFIFO0)"!]U, [!//
[!"num:inttohex($RxFIFO0Threshold)"!]U, [!//
[!"num:inttohex($SizeOfRxFIFO1)"!]U, [!//
[!"num:inttohex($RxFIFO1Threshold)"!]U[!//
[!IF "../../../CanGeneral/CanMultiplexedTransmission = 'true'"!][!//
,[!//
[!"num:inttohex($SizeOfTxQue)"!]U, [!//
[!IF "$SizeOfTxQue = '0'"!][!//
[!"('FALSE')"!]
[!ELSE!][!//
[!"('TRUE')"!]
[!ENDIF!][!//
[!ENDIF!][!//
}[!//
[!ENDINDENT!][!//
[!VAR "NoOfSidFilt" = "num:i($NoOfSidFilt + $NoOfSIDTemp)"!][!//
[!VAR "NoOfXidFilt" = "num:i($NoOfXidFilt + $NoOfXIDTemp)"!][!//
[!VAR "NoOfTxObj" = "num:i($NoOfTxObj + $NoOfTxDedBuff + $TxQueueCount)"!][!//
[!VAR "NoOfRxObj" = "num:i($NoOfRxObj + $NoOfRxDedBuff + $RXFIFO0UsedStatus + $RXFIFO1UsedStatus)"!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDFOR!]

};

/*******************************************************************************
            CAN Controller Baudrate Configurations for [!"$Text"!]
********************************************************************************
           { CANx_NBTP value, Configured Baudrate ,FDBaudrate config Index ,
             FD Support Status  }
********************************************************************************
                           Baudrate Setting
    (uint32)((NSJW << 25)|(NBRP << 16)|(TSEG1 << 8)|(TSEG2))
    NSJW   -> CanControllerSyncJumpWidth - 1
    NTSEG1 -> CanControllerPropSeg + CanControllerSeg1 - 1
    NTSEG2 -> CanControllerSeg2 - 1
*******************************************************************************/
[!VAR "CanMcuClockRef" = "''"!][!//
[!VAR "FDIndex" = "num:i(0)"!][!//
[!LOOP "./CanController/*"!][!//
[!IF "./CanControllerActivation = 'true'"!][!//
[!IF "node:refexists(./CanCpuClockRef) ='true'"!][!//
[!VAR "CanMcuClockRefNext" = "node:path(node:ref(./CanCpuClockRef))"!][!//
[!IF "$CanMcuClockRef = ''"!][!//
[!VAR "CanMcuClockRef" = "$CanMcuClockRefNext"!][!//
[!ENDIF!][!//
[!IF "$CanMcuClockRefNext != $CanMcuClockRef"!][!//
[!ERROR!][!//
CanCpuClockRef is wrong for the controller[!"num:i(CanControllerId)"!] should refer to the same MCU clock in all CanController Configurations of the CanConfigset.!
[!ENDERROR!][!//
 [!ENDIF!][!//
[!VAR "CanMcuClockRef" = "$CanMcuClockRefNext"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!/* [cover parentID={3B5A3C99-966F-4a77-8A27-0D860A0CC362}]
[/cover] */!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
static const Can_17_McmCan_ControllerBaudrateConfigType \
  Can_17_McmCan_kBaudrateConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][[!"$NoOfBaud"!]] =
{
[!VAR "HwControllerCount" = "num:i(count(./CanController/*))"!][!//
[!VAR "IndexCnt" = "num:i(0)"!][!//
[!FOR "HwIndex" = "0" TO "$HwControllerCount - '1'"!][!//
[!LOOP "./CanController/*"!][!//
[!NOCODE!][!//
[!VAR "CANModuleRefClk" = "node:ref(./CanCpuClockRef)/../../McuClockReferencePointConfig/McuPllDistributionSettingConfig/McuMCanClockSourceSelection"!][!//
[!IF "$CANModuleRefClk ='MCAN_CLOCK_SOURCE_DISABLED_SEL0'"!][!//
   [!ERROR!][!//
    [!CODE!][!//
    The CAN module clock source (McuMCanClockSourceSelection)shall be configured with MCAN_CLOCK_SOURCE_MCANI_SEL1 or MCAN_CLOCK_SOURCE_OSC_SEL2 with in the MCU configuration
    [!ENDCODE!][!//
   [!ENDERROR!][!//
[!ENDIF!][!//
[!SELECT "as:modconf('Mcu')"!][!//
    [!IF "$CANModuleRefClk ='MCAN_CLOCK_SOURCE_OSC_SEL2'"!][!//
        [!VAR "CANModuleClock" = "(num:i(1000000)) *(num:i(McuGeneralConfiguration/McuMainOscillatorFrequency))"!][!//
    [!ENDIF!][!//
[!ENDSELECT!][!//
[!IF "$CANModuleRefClk ='MCAN_CLOCK_SOURCE_MCANI_SEL1'"!][!//
 [!VAR "CANModuleClock" = "node:ref(./CanCpuClockRef)/../../McuClockReferencePointConfig/McuPllDistributionSettingConfig/McuMCanFrequency"!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!IF "$HwIndex = num:i(CanControllerId)"!][!//
[!IF "CanControllerActivation ='true'"!][!//
[!FOR "KerIndex" = "0" TO "$MaxKernel -'1'"!][!//
[!VAR "ResKerCoreName" = "text:toupper(concat('CON',$HwIndex,'_','KERNEL',$KerIndex,'_',$CheckText))"!][!//
[!IF "text:contains(text:split($CGCoreMap,','),$ResKerCoreName)"!][!//
[!IF "$IndexCnt > 0"!][!//
,
[!ENDIF!][!//
[!VAR "IndexCnt" = "num:i($IndexCnt+1)"!][!//
[!VAR "MaxConfigCount" = "num:i(count(./CanControllerBaudrateConfig/*))"!][!//
[!VAR "NBRP" = "num:i(0)"!][!//
[!FOR "i" = "1" TO "$MaxConfigCount"!][!//
[!VAR "TimeQuantaNanoSecond" = "num:i(1000000000) div ( ((num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerPropSeg))+(num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerSeg1))+(num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerSeg2))+1) * (num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerBaudRate)*num:i(1000)))"!][!//
[!VAR "NBRP" = "num:i((((($TimeQuantaNanoSecond) * num:i($CANModuleClock)) div num:i(1000000000)) - 1)+ 0.5)"!][!//
[!//
[!VAR "GetMinReqBR" = "(($CANModuleClock) div (512 * (3+ (num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerPropSeg + ./CanControllerBaudrateConfig/*[position()=$i]/CanControllerSeg1 - 1))+(num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerSeg2 - 1)))))"!][!//

[!VAR "GetMaxReqBR" = "(($CANModuleClock) div (3+ (num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerPropSeg + ./CanControllerBaudrateConfig/*[position()=$i]/CanControllerSeg1 - 1))+(num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerSeg2 - 1))))"!][!//
[!IF "(( num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerBaudRate)*num:i(1000)) < $GetMinReqBR)"!][!//
[!ERROR!]
Configured Baud rate [!"num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerBaudRate)"!] kbps for controller Id [!"num:i(CanControllerId)"!] of CanConfigSet [!"node:name(../..)"!] is Less than the Minimum allowed Baud rate [!"num:i($GetMinReqBR + 1)"!].
Acceptable Baud rate range depends upon configured CAN Module clock, CanControllerPropSeg, CanControllerSeg1 and CanControllerSeg2.
Change baud rate or any of the above parameters to get configured baud rate with in allowed range.
[!ENDERROR!][!//
[!ENDIF!][!//
[!//
[!IF "(( num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerBaudRate)*num:i(1000)) > $GetMaxReqBR)"!][!//
[!ERROR!]
Configured Baud rate [!"num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerBaudRate)"!] kbps for controller Id [!"num:i(CanControllerId)"!] of CanConfigSet [!"node:name(../..)"!] is greater than the Maximum allowed Baud rate [!"num:i($GetMaxReqBR - 1)"!].
Acceptable Baud rate range depends upon configured CAN Module clock, CanControllerPropSeg, CanControllerSeg1 and CanControllerSeg2.
Change baud rate or any of the above parameters to get configured baud rate with in allowed range.
[!ENDERROR!][!//
[!ENDIF!][!//
[!IF "(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerSeg1) < (./CanControllerBaudrateConfig/*[position()=$i]/CanControllerSyncJumpWidth)"!][!//
[!ERROR!]
 CanControllerSeg1 should be greater than or equal to CanControllerSyncJumpWidth in CanControllerBaudrateConfig [!"node:name(./CanControllerBaudrateConfig/*[position()=$i])"!] of CanController [!"node:name(.)"!] of CanConfigSet [!"node:name(../..)"!]!
[!ENDERROR!]
[!ENDIF!][!//
[!IF "(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerSeg2) < (./CanControllerBaudrateConfig/*[position()=$i]/CanControllerSyncJumpWidth)"!][!//
 [!ERROR!]
 CanControllerSeg2 should be greater than or equal to CanControllerSyncJumpWidth in CanControllerBaudrateConfig [!"node:name(./CanControllerBaudrateConfig/*[position()=$i])"!] of CanController [!"node:name(.)"!] of CanConfigSet [!"node:name(../..)"!]!
 [!ENDERROR!]
[!ENDIF!][!//
[!IF "num:i(4)> num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerPropSeg + ./CanControllerBaudrateConfig/*[position()=$i]/CanControllerSeg1 + ./CanControllerBaudrateConfig/*[position()=$i]/CanControllerSeg2)"!][!//
 [!ERROR!]
CanControllerBaudrateConfig [!"node:name(./CanControllerBaudrateConfig/*[position()=$i])"!] of CanController [!"node:name(.)"!] of CanConfigSet [!"node:name(../..)"!] violates the allowed range: 4<=(CanControllerPropSeg + CanControllerSeg1 + CanControllerSeg2)<=385.
 [!ENDERROR!]
[!ENDIF!][!//
[!IF "num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerPropSeg + ./CanControllerBaudrateConfig/*[position()=$i]/CanControllerSeg1 + ./CanControllerBaudrateConfig/*[position()=$i]/CanControllerSeg2) > num:i(385)"!][!//
 [!ERROR!]
CanControllerBaudrateConfig [!"node:name(./CanControllerBaudrateConfig/*[position()=$i])"!] of CanController [!"node:name(.)"!] of CanConfigSet [!"node:name(../..)"!] violates the allowed range: 4<=(CanControllerPropSeg + CanControllerSeg1 + CanControllerSeg2)<=385.
 [!ENDERROR!]
[!ENDIF!][!//
[!IF "num:i($NBRP) > num:i(511) "!][!//
  [!ERROR!]
The Calculated NBRP value by using the configured baudrate parameters and CAN module clock greater than the allowed range value.Change any of the above parameters to get NBRP value with in allowed range.
 [!ENDERROR!]
[!ENDIF!][!//
[!VAR "ActualBRP" = "num:i($NBRP)"!][!//
[!IF "(node:exists(CanControllerBaudrateConfig/*[position()=$i]/CanControllerFdBaudrateConfig/*))"!][!//
[!VAR "TimeQuantaNanoSecond" = "num:i(1000000000) div (((num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerFdBaudrateConfig/*[position()=1]/CanControllerPropSeg))+(num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerFdBaudrateConfig/*[position()=1]/CanControllerSeg1))+(num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerFdBaudrateConfig/*[position()=1]/CanControllerSeg2))+1) * (num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerFdBaudrateConfig/*[position()=1]/CanControllerFdBaudRate)*num:i(1000)))"!][!//
[!VAR "FBRP" = "num:i((((($TimeQuantaNanoSecond) * num:i($CANModuleClock)) div num:i(1000000000)) - 1)+ 0.5)"!][!//
[!IF "num:i($FBRP)< num:i($ActualBRP)"!][!//
 [!ERROR!]
The Calculated DBRP value by using the configured FD baudrate parameters in the container CanControllerFdBaudrateConfig belonging to CanControllerBaudrateConfig [!"node:name(./CanControllerBaudrateConfig/*[position()=$i])"!] should be greater than or equal to the calculated NBRP value by using the configured baudrate parameters in CanControllerBaudrateConfig [!"node:name(./CanControllerBaudrateConfig/*[position()=$i])"!] of CanController [!"node:name(.)"!] of CanConfigSet [!"node:name(../..)"!]!
 [!ENDERROR!]
[!ENDIF!][!//
[!ENDIF!][!//
[!VAR "NBRP" = "bit:shl((num:i($NBRP)),16)"!][!//
[!VAR "SJW" = "bit:shl((num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerSyncJumpWidth - 1)),25)"!][!//
[!VAR "TSEG1" = "bit:shl((num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerPropSeg + ./CanControllerBaudrateConfig/*[position()=$i]/CanControllerSeg1 - 1)),8)"!][!//
[!VAR "TSEG2" = "num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerSeg2 - 1)"!][!//
[!VAR "tempNBTR" = "bit:or($NBRP,$SJW)"!][!//
[!VAR "tempNBTR" = "bit:or($tempNBTR,$TSEG1)"!][!//
[!VAR "tempNBTR" = "bit:or($tempNBTR,$TSEG2)"!][!//
  {
    /* Configured Baudrate -> [!"num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerBaudRate)"!] kbps */
    /* Actual Baudrate     -> [!"(num:i($CANModuleClock) div (((num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerPropSeg + ./CanControllerBaudrateConfig/*[position()=$i]/CanControllerSeg1))+(num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerSeg2))+1) * (num:i($ActualBRP)+1))) div 1000"!] kbps */
    /* NBRP   -> [!"num:i($ActualBRP)"!] */
    /* NSJW   -> [!"num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerSyncJumpWidth - 1)"!]  */
    /* NTSEG1 -> [!"num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerPropSeg + ./CanControllerBaudrateConfig/*[position()=$i]/CanControllerSeg1 - 1)"!]  */
    /* NTSEG2 -> [!"num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerSeg2 - 1)"!]  */
    [!"num:inttohex($tempNBTR)"!]U,
    [!"num:i(./CanControllerBaudrateConfig/*[position()=$i]/CanControllerBaudRate)"!]U[!//
[!IF "$FDNodesPresent = '1'"!][!//
,
[!IF "(node:exists(CanControllerBaudrateConfig/*[position()=$i]/CanControllerFdBaudrateConfig/*))"!][!//
    [!"num:inttohex($FDIndex)"!]U,
[!VAR "FDIndex" = "num:i($FDIndex + 1)"!][!//
    TRUE
[!ELSE!][!//
    0x0U,
    FALSE
[!ENDIF!][!//
[!ENDIF!][!//
  }[!//
[!IF "$i < $MaxConfigCount"!][!//
,
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDFOR!][!//

};

[!IF "$FDNodesPresent != 0"!][!//
[!VAR "FDNodesPresentTmp" = "num:i(0)"!][!//
[!VAR "ControllerConfigMaxTemp" = "num:i(count(./CanController/*))"!][!//
[!FOR "Cntrlindx" = "1" TO "$ControllerConfigMaxTemp"!][!//
[!FOR "KerIndex" = "0" TO "$MaxKernel -'1'"!][!//
[!VAR "HwControllerId" = "num:i(CanController/*[position()=$Cntrlindx]/CanControllerId)"!][!//
[!VAR "ResKerCoreName" = "text:toupper(concat('CON',$HwControllerId,'_','KERNEL',$KerIndex,'_',$CheckText))"!][!//
[!IF "text:contains(text:split($CGCoreMap,','),$ResKerCoreName)"!][!//
    [!VAR "ControllerBRConfigTemp" = "num:i(count(CanController/*[position()=$Cntrlindx]/CanControllerBaudrateConfig/*))"!][!//
    [!FOR "BaudrateIndx" = "1" TO "$ControllerBRConfigTemp"!][!//
        [!IF "(node:exists(CanController/*[position()=$Cntrlindx]/CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]))"!][!//
            [!VAR "FDNodesPresentTmp" = "num:i(1)"!][!//
        [!ENDIF!][!//
    [!ENDFOR!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDFOR!][!//
[!IF "$FDNodesPresentTmp != 0"!][!//
/*******************************************************************************
                CAN Controller FD Config Parameters for [!"$Text"!]
********************************************************************************
           { CANx_DBTP value, TrcvDelayCompensationOffset, BRS Status }
********************************************************************************

        (uint32)((DBRP << 16)|(DTSEG1 << 8)|(DTSEG2 << 4)|(DSJW ))
        DSJW   -> CanControllerSyncJumpWidth - 1
        DTSEG1 -> CanControllerPropSeg + CanControllerSeg1 - 1
        DTSEG2 -> CanControllerSeg2 - 1
*******************************************************************************/
[!/* [cover parentID={8CB12FB6-185F-480c-B83D-F16396E18BA8}]
[/cover] */!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
static const Can_17_McmCan_ControllerFDBaudrateConfigType \
  Can_17_McmCan_kFDBaudrateConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][[!"$NoOfFdBaud"!]] =
{
[!VAR "HwControllerCount" = "num:i(count(./CanController/*))"!][!//
[!VAR "InstanceCnt" = "num:i(0)"!][!//
[!FOR "HwIndex" = "0" TO "$HwControllerCount - '1'"!][!//
[!LOOP "./CanController/*"!][!//
[!NOCODE!][!//
[!VAR "CANModuleRefClk" = "(node:ref(./CanCpuClockRef)/../../McuClockReferencePointConfig/McuPllDistributionSettingConfig/McuMCanClockSourceSelection)"!][!//
[!IF "$CANModuleRefClk ='MCAN_CLOCK_SOURCE_DISABLED_SEL0'"!][!//
   [!ERROR!][!//
    [!CODE!][!//
    The CAN module clock source (McuMCanClockSourceSelection  )shall be configured with MCAN_CLOCK_SOURCE_MCANI_SEL1 or MCAN_CLOCK_SOURCE_OSC_SEL2 with in the MCU configuration
    [!ENDCODE!][!//
   [!ENDERROR!][!//
[!ENDIF!][!//
[!SELECT "as:modconf('Mcu')/*"!][!//
    [!IF "$CANModuleRefClk ='MCAN_CLOCK_SOURCE_OSC_SEL2'"!][!//
        [!VAR "CANModuleClock" = "(num:i(1000000)) *(num:i(McuGeneralConfiguration/McuMainOscillatorFrequency))"!][!//
    [!ENDIF!][!//
[!ENDSELECT!][!//
[!IF "$CANModuleRefClk ='MCAN_CLOCK_SOURCE_MCANI_SEL1'"!][!//
    [!VAR "CANModuleClock" = "node:ref(CanCpuClockRef)/../../McuClockReferencePointConfig/McuPllDistributionSettingConfig/McuMCanFrequency"!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!IF "CanControllerActivation ='true'"!][!//
[!IF "$HwIndex = num:i(CanControllerId)"!][!//
[!FOR "KerIndex" = "0" TO "$MaxKernel -'1'"!][!//
[!VAR "ResKerCoreName" = "text:toupper(concat('CON',$HwIndex,'_','KERNEL',$KerIndex,'_',$CheckText))"!][!//
[!IF "text:contains(text:split($CGCoreMap,','),$ResKerCoreName)"!][!//
[!VAR "ControllerBRConfigTemp" = "num:i(count(./CanControllerBaudrateConfig/*))"!][!//
[!FOR "BaudrateIndx" = "1" TO "$ControllerBRConfigTemp"!][!//
[!IF "(node:exists(CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]))"!][!//
[!IF "$InstanceCnt > 0"!][!//
,
[!ENDIF!][!//
[!VAR "InstanceCnt" = "num:i($InstanceCnt + 1)"!][!//
[!VAR "i" = "num:i(1)"!][!//
[!VAR "TimeQuantaNanoSecond" = "num:i(1000000000) div (((num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerPropSeg))+(num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerSeg1))+(num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerSeg2))+1) * (num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerFdBaudRate)*num:i(1000)))"!][!//
[!VAR "FBRP" = "num:i((((($TimeQuantaNanoSecond) * num:i($CANModuleClock)) div num:i(1000000000)) - 1)+ 0.5)"!][!//
[!//
[!VAR "GetMinReqBR" = "(($CANModuleClock) div (512 * (3+ (num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerPropSeg + ./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerSeg1 - 1))+(num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerSeg2 - 1)))))"!][!//
[!VAR "GetMaxReqBR" = "(($CANModuleClock) div (3+ (num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerPropSeg + ./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerSeg1 - 1))+(num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerSeg2 - 1))))"!][!//
[!//
[!IF "( (num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerFdBaudRate)*num:i(1000)) < $GetMinReqBR)"!][!//
[!ERROR!]
Configured Baud rate [!"num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerFdBaudRate)"!] kbps for controller Id [!"num:i(CanControllerId)"!] of CanConfigSet [!"node:name(../..)"!] is Less than the Minimum allowed Baud rate [!"num:i($GetMinReqBR + 1)"!].
Acceptable Baud rate range depends upon configured CAN Module clock, CanControllerPropSeg, CanControllerSeg1 and CanControllerSeg2.
Change baud rate or any of the above parameters to get configured baud rate with in allowed range.
[!ENDERROR!]
[!ENDIF!][!//
[!//
[!IF "(( num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerFdBaudRate)*num:i(1000)) > $GetMaxReqBR)"!][!//
[!ERROR!]
Configured Baud rate [!"num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerFdBaudRate)"!] kbps for controller Id [!"num:i(CanControllerId)"!] of CanConfigSet [!"node:name(../..)"!] is greater than the Maximum allowed Baud rate [!"num:i($GetMaxReqBR - 1)"!].
Acceptable Baud rate range depends upon configured CAN Module clock, CanControllerPropSeg, CanControllerSeg1 and CanControllerSeg2.
Change baud rate or any of the above parameters to get configured baud rate with in allowed range.
[!ENDERROR!]
[!ENDIF!]
[!//
[!IF "num:i(4) > num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerPropSeg + ./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerSeg1 + ./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerSeg2) > num:i(49)"!][!//
 [!ERROR!]
 CanControllerFdBaudrateConfig [!"node:name(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig)"!] of CanController [!"node:name(.)"!] of CanConfigSet [!"node:name(../..)"!] violates the allowed range: 4<=(CanControllerPropSeg + CanControllerSeg1 + CanControllerSeg2)<=49.
 [!ENDERROR!]
[!ENDIF!][!//
[!IF "num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerSeg1) < num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerSyncJumpWidth)"!][!//
 [!ERROR!]
  The CanControllerSeg1 should be greater than or equal to CanControllerSyncJumpWidth in CanControllerFDBaudrateConfig [!"node:name(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig)"!] of CanController [!"node:name(.)"!] of CanConfigSet [!"node:name(../..)"!]
 [!ENDERROR!]
 [!ENDIF!][!//
[!IF "num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerSeg2) < num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerSyncJumpWidth)"!][!//
 [!ERROR!]
  The CanControllerSeg2 should be greater than or equal to CanControllerSyncJumpWidth in CanControllerFDBaudrateConfig [!"node:name(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig)"!] of CanController [!"node:name(.)"!] of CanConfigSet [!"node:name(../..)"!]
 [!ENDERROR!]
[!ENDIF!][!//
[!IF "num:i($FBRP) > num:i(31)"!][!//
 [!ERROR!]
  The Calculated DBRP value by using the configured baudrate parameters and CAN module clock greater than the allowed range value.Change any of the above parameters to get NBRP value with in allowed range.
 [!ENDERROR!]
[!ENDIF!][!//
[!VAR "DSJW" = "num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerSyncJumpWidth - 1)"!][!//
[!VAR "DTSEG1" = "bit:shl((num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerPropSeg + ./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerSeg1 - 1)),8)"!][!//
[!VAR "DTSEG2" = "bit:shl((num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerSeg2 - 1)),4)"!][!//
[!VAR "ActualFBRP" = "num:i($FBRP)"!][!//
[!VAR "FBRP" = "bit:shl((num:i($FBRP)),16)"!][!//
[!VAR "tempFNBTR" = "bit:or($FBRP,$DSJW)"!][!//
[!VAR "tempFNBTR" = "bit:or($tempFNBTR,$DTSEG1)"!][!//
[!VAR "tempFNBTR" = "bit:or($tempFNBTR,$DTSEG2)"!][!//
[!IF "(node:exists(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerTrcvDelayCompensationOffset/*[1]) = 'true')"!][!//
[!VAR "TDCO" = "num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerTrcvDelayCompensationOffset/*[1])"!][!//
[!ELSE!][!//
[!VAR "TDCO" = "0"!][!//
[!ENDIF!][!//
[!VAR "TDCEnable" = "0"!][!//
[!VAR "TDC" = "0"!][!//
[!IF "$TDCO > (num:i(0))"!][!//
[!VAR "TDCEnable" = "1"!][!//
[!ENDIF!][!//
[!VAR "TDC" = "bit:shl((num:i($TDCEnable)),23)"!][!//
[!VAR "tempNTDCR" = "$TDCO"!][!//
[!VAR "tempFNBTR" = "bit:or($tempFNBTR,$TDC)"!][!//
  {
  /* Configured FD Baudrate -> [!"num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerFdBaudRate)"!] kbps */
  /* Actual Baudrate     -> [!"(num:i($CANModuleClock) div (((num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerPropSeg + ./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerSeg1))+(num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerSeg2))+1) * (num:i($ActualFBRP)+1))) div 1000"!] kbps */
  /* DBRP   -> [!"num:i($ActualFBRP)"!] */
  /* DSJW   -> [!"num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerSyncJumpWidth - 1)"!]  */
  /* DTSEG1 -> [!"num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerPropSeg + ./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerSeg1 - 1)"!]  */
  /* DTSEG2 -> [!"num:i(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerSeg2 - 1)"!]  */
  [!"num:inttohex($tempFNBTR)"!]U,
  [!"num:inttohex($tempNTDCR)"!]U,
[!IF "./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]/CanControllerTxBitRateSwitch = 'true'"!][!//
  TRUE
[!ELSE!][!//
  FALSE
[!ENDIF!][!//
  }[!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDFOR!]

};
[!ENDIF!]
[!ENDIF!]

/*******************************************************************************
    CAN Controller Handling of Events for [!"$Text"!] : Interrupt/Polling
********************************************************************************
        { CanTxProcessing Mode, CanRxProcessing Mode,
          CanBusoffProcessing Mode, CanWakeupProcessing Mode }
********************************************************************************
           Note: If the CAN controller is not activated then,
                 { 0U, 0U, 0U, 0U } will be generated
*******************************************************************************/
[!VAR "NumControllers" = "num:i(count(./CanController/*))"!][!//
[!VAR "IndexCnt" = "num:i(0)"!][!//
/* [!"./@name"!] -> CAN Controller - Handling of Events */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
static const Can_17_McmCan_EventHandlingType \
  Can_17_McmCan_kEventHandlingConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][[!"$NoOfCont"!]] =
{
[!FOR "TempIndex" = "0" TO "$NumControllers - 1"!][!//
[!LOOP "./CanController/*"!][!//
[!IF "CanControllerId = $TempIndex"!][!//
[!IF "CanControllerActivation = 'true'"!][!//
[!FOR "KerIndex" = "0" TO "$MaxKernel -'1'"!][!//
[!VAR "ResKerCoreName" = "text:toupper(concat('CON',$TempIndex,'_','KERNEL',$KerIndex,'_',$CheckText))"!][!//
[!IF "text:contains(text:split($CGCoreMap,','),$ResKerCoreName)"!][!//
[!NOCODE!][!//
    [!IF "CanRxProcessing != CanWakeupProcessing"!][!//
    [!CODE!][!//
        [!ERROR!][!//
The CanWakeupProcessing and RxProcessing for the Can controller[!"CanControllerId"!] shall be configured as same (ie both are Polling or Interrupt)
        [!ENDERROR!][!//
    [!ENDCODE!][!//
    [!ENDIF!][!//
[!ENDNOCODE!][!//
[!IF "$IndexCnt > 0"!][!//
,
[!ENDIF!][!//
[!VAR "IndexCnt" = "num:i($IndexCnt+1)"!]
 { { [!//
[!CALL "CAN_CG_IsEventPolled", "event" = "CanTxProcessing "!],[!//
[!CALL "CAN_CG_IsEventPolled", "event" = "CanRxProcessing"!],[!//
[!CALL "CAN_CG_IsEventPolled", "event" = "CanBusoffProcessing"!],[!//
[!CALL "CAN_CG_IsEventPolled", "event" = "CanWakeupProcessing"!][!//
} }[!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDFOR!]

};
[!IF "$StandardIdOnlyTmp = '1' or $MixedOnlyTmp = '1' "!][!//
/*******************************************************************************
               Receive Hardware Object Configurations for [!"$Text"!]
********************************************************************************
        This is the combination of SID filter elements
        Rx Object -> { Combination of Mask and filter value S0, HRH HwObject Id,
        Hw Controller Id, Rx BufferType, [Pretended Support Status] }
********************************************************************************
       Note: [1] If the associated CAN Controller is not activated then,
                   Hw Controller Id -> 255
             [2] If CanFilterMaskRef is not configured then,
                   Mask -> 0x7ff - for STANDARD Msg Id Type
*******************************************************************************/
[!VAR "HwObjctMaxTemp" = "num:i(count(./CanHardwareObject/*))"!][!//
[!/* [cover parentID={AE40A44A-BD73-4d3e-9E8D-F3DFAAE846DB}]
[/cover] */!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
static const Can_17_McmCan_SIDFilterConfigType \
  Can_17_McmCan_kSIDFilterConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][[!"$NoOfSidFilt"!]] =
{
[!VAR "NoOfInstance" = "num:i(0)"!][!//
[!VAR "RxFIFOCount" = "num:i(0)"!][!//
[!VAR "LastCfgCntrlId" = "num:i(0)"!][!//
[!VAR "RxDedicatedbuffIndex" = "num:i(0)"!][!//
[!FOR "Cntrlindx" = "0" TO "$HwObjctMaxTemp"!][!//
[!FOR "HwObjindx" = "1" TO "$HwObjctMaxTemp"!][!//
[!VAR "RxBufferType" = "','"!][!//
[!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanObjectType = 'RECEIVE'"!][!//
[!IF "node:refexists(./CanHardwareObject/*[position()=$HwObjindx]/CanControllerRef) ='true'"!][!//
[!IF "(node:ref(./CanHardwareObject/*[position()=$HwObjindx]/CanControllerRef)/CanControllerActivation = 'true')"!][!//
[!VAR "TempObjId" = "./CanHardwareObject/*[position()=$HwObjindx]/CanObjectId"!][!//
[!IF "$TempObjId = $Cntrlindx"!][!//
[!VAR "HwControllerId" = "num:i(node:ref(./CanHardwareObject/*[position()=$HwObjindx]/CanControllerRef)/CanControllerId)"!][!//
[!FOR "KerIndex" = "0" TO "$MaxKernel -'1'"!][!//
[!VAR "ResKerCoreName" = "text:toupper(concat('CON',$HwControllerId,'_','KERNEL',$KerIndex,'_',$CheckText))"!][!//
[!IF "text:contains(text:split($CGCoreMap,','),$ResKerCoreName)"!][!//
[!IF "(node:ref(./CanHardwareObject/*[position()=$HwObjindx]/CanControllerRef)/CanRxProcessing = 'POLLING')"!][!//
[!IF "(node:exists(./CanHardwareObject/*[position()=$HwObjindx]/CanMainFunctionRWPeriodRef/*[1]))"!][!//
[!ELSE!]
[!ERROR!][!//
The HRH Hardare object[!"$TempObjId"!] shall be referenced or enabled (CanMainFunctionRWPeriodRef) with cyclic period,since the referenced controller is configured with Rx processing mode as POLLING
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "$LastCfgCntrlId > $HwControllerId"!][!//
[!ERROR!][!//
The HRH Hardare object shall be configured in the increasing order of refrenced CanControllerId
Eg.: HRH object in order: HRHs of CanControllerId 0, HRHs of CanControllerId 1, etc..
[!ENDERROR!][!//
[!ENDIF!][!//
[!IF "$LastCfgCntrlId != $HwControllerId"!][!//
[!VAR "RxFIFOCount" = "num:i(0)"!][!//
[!VAR "RxDedicatedbuffIndex" = "num:i(0)"!][!//
[!ENDIF!][!//
[!VAR "LastCfgCntrlId" = "num:i($HwControllerId)"!][!//
[!VAR "HwFilterCount" = "num:i(count(./CanHardwareObject/*[position()=$HwObjindx]/CanHwFilter/*))"!][!//
[!IF "$HwFilterCount = '0'"!][!//
[!ERROR!][!//
The CanHwFilter  contianer shall be configured for the CanHwObjectId[!"$TempObjId"!] since CanHwObjectType is configured as "RECEIVE"
[!ENDERROR!][!//
[!ENDIF!][!//
[!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanHwObjectCount = '1'"!][!//
[!VAR "RxBufferType" = "concat(RxBufferType,'CAN_17_MCMCAN_RX_DED_BUFFER')"!][!//
[!VAR "SFEC" = "bit:shl(num:i(7),27)"!][!//
[!ELSE!][!//
[!IF "$RxFIFOCount = '1'"!][!//
[!VAR "RxBufferType" = "concat(RxBufferType,'CAN_17_MCMCAN_RX_FIFO1')"!][!//
[!VAR "SFEC" = "bit:shl(num:i(2),27)"!][!//
[!VAR "RxFIFOCount" = "num:i($RxFIFOCount+1)"!][!//
[!ELSEIF "$RxFIFOCount = '0'"!][!//
[!VAR "RxBufferType" = "concat(RxBufferType,'CAN_17_MCMCAN_RX_FIFO0')"!][!//
[!VAR "SFEC" = "bit:shl(num:i(1),27)"!][!//
[!VAR "RxFIFOCount" = "num:i($RxFIFOCount+1)"!][!//
[!ELSE!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!FOR "HwFilterindx" = "1" TO "$HwFilterCount"!][!//
[!IF "((./CanHardwareObject/*[position()=$HwObjindx]/CanIdType = 'STANDARD') or(./CanHardwareObject/*[position()=$HwObjindx]/CanIdType = 'MIXED'))"!][!//
[!VAR "HwFilterValue" = "num:i(./CanHardwareObject/*[position()=$HwObjindx]/CanHwFilter/*[position()=$HwFilterindx]/CanHwFilterCode)"!][!//
[!VAR "HwFilterMaskValue" = "num:i(./CanHardwareObject/*[position()=$HwObjindx]/CanHwFilter/*[position()=$HwFilterindx]/CanHwFilterMask)"!][!//
[!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanIdType = 'STANDARD'"!][!//
[!IF "$RxBufferType = 'CAN_17_MCMCAN_RX_DED_BUFFER'"!][!//
[!IF "$HwFilterValue > 2047 or $HwFilterMaskValue > 2047"!][!//
[!ERROR!][!//
Error in the configurtion of "CanHwFilterCode" or "CanHwFilterMask" value for the CanHwObjectId[!"$TempObjId"!]: Allowed range for STANDARD CanIdType is: 0 to 0x7FF.
[!ENDERROR!][!//
[!ENDIF!][!//
[!ELSE!][!//
[!IF "$HwFilterValue > 2047"!][!//
[!ERROR!][!//
Error in the configurtion of "CanHwFilterCode" value for the CanHwObjectId[!"$TempObjId"!]: Allowed range for STANDARD CanIdType is: 0 to 0x7FF.
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanIdType = 'MIXED'"!][!//
[!IF "$HwFilterValue != 0"!][!//
[!IF "$HwFilterValue < 262144 or $HwFilterValue > 536608768"!][!//
[!ERROR!][!//
Error in the configurtion of "CanHwFilterCode" value for the CanHwObjectId[!"$TempObjId"!]: The value
of CanHwFilterMask and CanHwFilterCode shall be within range 0x0 and 0x40000 to 0x1FFC0000 value If the CanIdType is MIXED.
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!VAR "HwFilterValue" = "bit:and($HwFilterValue,536608768)"!][!//
[!VAR "HwFilterValue" = "bit:shr($HwFilterValue,18)"!][!//
[!VAR "HwFilterMaskValue" = "bit:and($HwFilterMaskValue,536608768)"!][!//
[!VAR "HwFilterMaskValue" = "bit:shr($HwFilterMaskValue,18)"!][!//
[!ENDIF!][!//
[!IF "$NoOfInstance > 0 "!][!//
,
[!ENDIF!][!//
[!VAR "PretendedSupportMsg" = "num:i(0)"!][!//
[!IF "$PublicIcomSupport > num:i(0)"!][!//
[!SELECT "as:modconf('Can')[1]/CanConfigSet"!][!//
[!LOOP "CanIcom/*/CanIcomConfig/*"!][!//
[!VAR "IcomRxMsgCount" = "num:i(count(./CanIcomWakeupCauses/CanIcomRxMessage/*))"!][!//
[!FOR "Rxindx" = "1" TO "num:i($IcomRxMsgCount)"!][!//
[!VAR "IcomMsgIdValue" = "num:i(./CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomMessageId)"!][!//
[!IF "$RxBufferType != 'CAN_17_MCMCAN_RX_DED_BUFFER'"!][!//
[!VAR "CheckHwFilterValue" = "bit:and($HwFilterValue,$HwFilterMaskValue)"!][!//
[!VAR "CheckIcomFilterValue" = "bit:and($IcomMsgIdValue,$HwFilterMaskValue)"!][!//
[!ELSE!][!//
[!VAR "CheckHwFilterValue" = "$HwFilterValue"!][!//
[!VAR "CheckIcomFilterValue" = "$IcomMsgIdValue"!][!//
[!ENDIF!][!//
[!IF " $CheckHwFilterValue = $CheckIcomFilterValue"!][!//
[!VAR "PretendedSupportMsg" = "num:i(1)"!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDIF!][!//
[!VAR "NoOfInstance" = "$NoOfInstance + num:i(1)"!][!//
[!VAR "SFT" = "bit:shl(num:i(2),30)"!][!//
[!VAR "SFID1" = "bit:shl(num:i($HwFilterValue),16)"!][!//
[!IF "$RxBufferType = 'CAN_17_MCMCAN_RX_DED_BUFFER'"!][!//
[!VAR "SFID2" = "(num:i($RxDedicatedbuffIndex))"!][!//
[!ELSE!][!//
[!VAR "SFID2" = "num:i($HwFilterMaskValue)"!][!//
[!ENDIF!][!//
[!VAR "SIDFilterElementS0" = "bit:or($SFT,$SFEC)"!][!//
[!VAR "SIDFilterElementS0" = "bit:or($SIDFilterElementS0,$SFID1)"!][!//
[!VAR "SIDFilterElementS0" = "bit:or($SIDFilterElementS0,$SFID2)"!][!//
 {[!"num:inttohex($SIDFilterElementS0)"!]U,[!//
 [!"num:i(./CanHardwareObject/*[position()=$HwObjindx]/CanObjectId)"!]U,[!//
 [!"num:i($HwControllerId)"!]U,[!//
 [!"$RxBufferType"!][!//
[!IF "$PublicIcomSupport > num:i(0)"!][!//
,[!//
[!IF "$PretendedSupportMsg = 1 "!][!//
TRUE[!//
[!ELSE!][!//
FALSE[!//
[!ENDIF!][!//
[!ENDIF!][!//
 }[!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!VAR "RxDedicatedbuffIndex" = "num:i($RxDedicatedbuffIndex+1)"!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDFOR!]

};
[!ENDIF!][!//
[!IF "$ExtendedOnlyTmp = '1' or $MixedOnlyTmp = '1'"!][!//
/*******************************************************************************
      This is the combination of XID filer elements for [!"$Text"!]
      Rx Object -> { Combination of Mask and filter valueF0,Combination of
      Mask and filter valueF1, HRH HwObject Id, Hw Controller Id, Rx BufferType,
            [Pretended Support Status]  }
********************************************************************************
       Note: [1] If the associated CAN Controller is not activated then,
                   this shall not be generated
             [2] If CanFilterMaskRef is not configured then,
                   Mask -> 0x1fffffff - for EXTENDED/MIXED Msg Id Type
*******************************************************************************/
[!VAR "HwObjctMaxTemp" = "num:i(count(./CanHardwareObject/*))"!][!//
[!/* [cover parentID={3C7ADE55-6E5E-40b9-B0EB-869481E9CEAD}]
[/cover] */!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
static const Can_17_McmCan_XIDFilterConfigType \
  Can_17_McmCan_kXIDFilterConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][[!"$NoOfXidFilt"!]] =
{
[!VAR "NoOfInstance" = "num:i(0)"!][!//
[!VAR "ControllerConfigMaxTemp" = "num:i(count(./CanController/*))"!][!//
[!FOR "Cntrlindx" = "0" TO "$ControllerConfigMaxTemp - 1"!][!//
[!VAR "RxDedicatedbuffIndex" = "num:i(0)"!][!//
[!VAR "RxFIFOCount" = "num:i(0)"!][!//
[!FOR "HwObjindx" = "1" TO "$HwObjctMaxTemp"!][!//
[!VAR "RxBufferType" = "','"!][!//
[!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanObjectType = 'RECEIVE'"!][!//
[!IF "node:refexists(./CanHardwareObject/*[position()=$HwObjindx]/CanControllerRef) ='true'"!][!//
[!IF "(node:ref(./CanHardwareObject/*[position()=$HwObjindx]/CanControllerRef)/CanControllerActivation = 'true')"!][!//
[!VAR "HwControllerId" = "num:i(node:ref(./CanHardwareObject/*[position()=$HwObjindx]/CanControllerRef)/CanControllerId)"!][!//
[!FOR "KerIndex" = "0" TO "$MaxKernel -'1'"!][!//
[!VAR "ResKerCoreName" = "text:toupper(concat('CON',$HwControllerId,'_','KERNEL',$KerIndex,'_',$CheckText))"!][!//
[!IF "text:contains(text:split($CGCoreMap,','),$ResKerCoreName)"!][!//
[!IF "(node:ref(./CanHardwareObject/*[position()=$HwObjindx]/CanControllerRef)/CanRxProcessing = 'POLLING')"!][!//
[!IF "(node:exists(./CanHardwareObject/*[position()=$HwObjindx]/CanMainFunctionRWPeriodRef/*[1]))"!][!//
[!ELSE!]
[!ERROR!][!//
The HRH Hardware object[!"num:i(./CanHardwareObject/*[position()=$HwObjindx]/CanObjectId)"!] shall be referenced or enabled (CanMainFunctionRWPeriodRef) with cyclic period,since the referenced controller is configured with Rx processing mode as POLLING
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "$Cntrlindx = $HwControllerId"!][!//
[!VAR "HwFilterCount" = "num:i(count(./CanHardwareObject/*[position()=$HwObjindx]/CanHwFilter/*))"!][!//
[!VAR "ValidIndx" = "num:i(0)"!][!//
[!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanHwObjectCount = '1'"!][!//
[!VAR "RxBufferType" = "concat(RxBufferType,'CAN_17_MCMCAN_RX_DED_BUFFER')"!][!//
[!VAR "EFEC" = "bit:shl(num:i(7),29)"!][!//
[!ELSE!][!//
[!IF "$RxFIFOCount = '1'"!][!//
[!VAR "RxBufferType" = "concat(RxBufferType,'CAN_17_MCMCAN_RX_FIFO1')"!][!//
[!VAR "EFEC" = "bit:shl(num:i(2),29)"!][!//
[!VAR "RxFIFOCount" = "num:i($RxFIFOCount+1)"!][!//
[!ENDIF!][!//
[!IF "$RxFIFOCount = '0'"!][!//
[!VAR "RxBufferType" = "concat(RxBufferType,'CAN_17_MCMCAN_RX_FIFO0')"!][!//
[!VAR "EFEC" = "bit:shl(num:i(1),29)"!][!//
[!VAR "RxFIFOCount" = "num:i($RxFIFOCount+1)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!FOR "HwFilterindx" = "1" TO "$HwFilterCount"!][!//
[!VAR "HwFilterValue" = "num:i(./CanHardwareObject/*[position()=$HwObjindx]/CanHwFilter/*[position()=$HwFilterindx]/CanHwFilterCode)"!][!//
[!VAR "CanHwFilterMaskValue" = "num:i(./CanHardwareObject/*[position()=$HwObjindx]/CanHwFilter/*[position()=$HwFilterindx]/CanHwFilterMask)"!][!//
[!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanIdType = 'EXTENDED'"!][!//
[!IF "$HwFilterValue > 536870911"!][!//
[!ERROR!][!//
Error in the configurtion of "CanHwFilterCode" value for the CanHwObjectId
[!"num:i(./CanHardwareObject/*[position()=$HwObjindx]/CanObjectId)"!]: Allowed range for EXTENDED CanIdType is: 0 to 0x1FFFFFFF.
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanIdType = 'MIXED'"!][!//
[!IF "$HwFilterValue != 0"!][!//
[!IF "$HwFilterValue < 262144 or $HwFilterValue > 536608768"!][!//
[!ERROR!][!//
Error in the configurtion of "CanHwFilterCode" value for the CanHwObjectId [!"num:i(./CanHardwareObject/*[position()=$HwObjindx]/CanObjectId)"!]: The value
of CanHwFilterCode shall be within range 0x0 and 0x40000 to 0x1FFC0000 value If the CanIdType is MIXED
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanIdType = 'MIXED' or ./CanHardwareObject/*[position()=$HwObjindx]/CanIdType = 'EXTENDED'"!][!//
[!IF "$ValidIndx > 0 or $NoOfInstance > 0 "!][!//
,
[!ENDIF!][!//
[!VAR "NoOfInstance" = "$NoOfInstance + num:i(1)"!][!//
[!VAR "ValidIndx" = "$ValidIndx + num:i(1)"!][!//
[!VAR "EFT" = "bit:shl(num:i(2),30)"!][!//
[!VAR "XIDFilterElemntF0" = "num:i($HwFilterValue)"!][!//
[!IF "$RxBufferType = 'CAN_17_MCMCAN_RX_DED_BUFFER'"!][!//
[!VAR "EFID2" = "(num:i($RxDedicatedbuffIndex))"!][!//
[!ELSE!][!//
[!VAR "EFID2" = "num:i(./CanHardwareObject/*[position()=$HwObjindx]/CanHwFilter/*[position()=$HwFilterindx]/CanHwFilterMask)"!][!//
[!VAR "EFID2" = "bit:and($EFID2,536870911)"!][!//
[!ENDIF!][!//
[!VAR "PretendedSupportMsg" = "num:i(0)"!][!//
[!IF "$PublicIcomSupport > num:i(0)"!][!//
[!SELECT "as:modconf('Can')[1]/CanConfigSet"!][!//
[!LOOP "./CanIcom/./*[1]/CanIcomConfig/*"!][!//
[!VAR "IcomRxMsgCount" = "num:i(count(./CanIcomWakeupCauses/CanIcomRxMessage/*))"!][!//
[!FOR "Rxindx" = "1" TO "num:i($IcomRxMsgCount)"!][!//
[!VAR "IcomMsgIdValue" = "num:i(./CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomMessageId)"!][!//
[!IF "$RxBufferType != 'CAN_17_MCMCAN_RX_DED_BUFFER'"!][!//
[!VAR "CheckHwFilterValue" = "bit:and($HwFilterValue,$CanHwFilterMaskValue)"!][!//
[!VAR "CheckIcomFilterValue" = "bit:and($IcomMsgIdValue,$CanHwFilterMaskValue)"!][!//
[!ELSE!][!//
[!VAR "CheckHwFilterValue" = "$HwFilterValue"!][!//
[!VAR "CheckIcomFilterValue" = "$IcomMsgIdValue"!][!//
[!ENDIF!][!//
[!IF " $CheckHwFilterValue = $CheckIcomFilterValue"!][!//
[!VAR "PretendedSupportMsg" = "num:i(1)"!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDIF!][!//
[!VAR "XIDFilterElemntF0" = "bit:or($XIDFilterElemntF0,$EFEC)"!][!//
[!VAR "XIDFilterElemntF1" = "bit:or($EFID2,$EFT)"!][!//
 {[!"num:inttohex($XIDFilterElemntF0)"!]U,[!//
 [!"num:inttohex($XIDFilterElemntF1)"!]U,[!//
 [!"num:i(./CanHardwareObject/*[position()=$HwObjindx]/CanObjectId)"!]U,[!//
 [!"num:i($HwControllerId)"!]U,[!//
 [!"$RxBufferType"!][!//
[!IF "$PublicIcomSupport > num:i(0)"!][!//
,[!//
 [!IF "$PretendedSupportMsg = 1 "!][!//
 TRUE[!//
[!ELSE!][!//
 FALSE[!//
[!ENDIF!][!//
[!ENDIF!][!//
}[!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!VAR "RxDedicatedbuffIndex" = "num:i($RxDedicatedbuffIndex+1)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDFOR!]

};
[!ENDIF!][!//
[!IF "$TxObjectCountMaxTmp != 0"!][!//
/*******************************************************************************
           Transmit Hardware Object Configurations for [!"$Text"!]
********************************************************************************
 Tx Object -> { CanTxHwObjId, CanTxBuffIndx, HwControllerId, [CanFdPaddValue],
               CanTxHwObjIdType , CanTxBufferType, CanTrigTxStatus}
********************************************************************************
       Note: [1] If the associated CAN Controller is not activated then,
                   this shall not be generated.
*******************************************************************************/
[!VAR "HwObjctMaxTemp" = "num:i(count(./CanHardwareObject/*))"!][!//
[!/* [cover parentID={FBF7AEDA-33C6-44e7-B9EB-79F1C8971BB4}]
[/cover] */!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
static const Can_17_McmCan_TxHwObjectConfigType \
  Can_17_McmCan_kTxHwObjectConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][[!"$NoOfTxObj"!]] =
{
[!VAR "CoreTxObjCnt" = "num:i(0)"!][!//
[!VAR "NoOfInstance" = "num:i(0)"!][!//
[!VAR "TxHwObjCount" = "num:i(0)"!][!//
[!VAR "TxDedicatedBuffIndex" = "num:i(0)"!][!//
[!VAR "LastCfgCntrlId" = "num:i(0)"!][!//
[!VAR "LastCfgHrhId" = "num:i(0)"!][!//
[!FOR "HwObjindx" = "1" TO "$HwObjctMaxTemp"!][!//
[!IF "CanHardwareObject/*[CanObjectId= $HwObjindx]/CanObjectType = 'RECEIVE'"!][!//
[!VAR "LastCfgHrhId" = "num:i($HwObjindx+1)"!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!FOR "Cntrlindx" = "$LastCfgHrhId" TO "$HwObjctMaxTemp - '1'"!][!//
[!FOR "HwObjindx" = "1" TO "$HwObjctMaxTemp"!][!//
[!IF "CanHardwareObject/*[position()=$HwObjindx]/CanObjectType = 'TRANSMIT'"!][!//
[!IF "node:refexists(./CanHardwareObject/*[position()=$HwObjindx]/CanControllerRef) ='true'"!][!//
[!IF "node:ref(./CanHardwareObject/*[position()=$HwObjindx]/CanControllerRef)/CanControllerActivation = 'true'"!][!//
[!VAR "HwControllerId" = "num:i(node:ref(./CanHardwareObject/*[position()=$HwObjindx]/CanControllerRef)/CanControllerId)"!][!//
[!FOR "KerIndex" = "0" TO "$MaxKernel -'1'"!][!//
[!VAR "ResKerCoreName" = "text:toupper(concat('CON',$HwControllerId,'_','KERNEL',$KerIndex,'_',$CheckText))"!][!//
[!IF "text:contains(text:split($CGCoreMap,','),$ResKerCoreName)"!][!//
[!VAR "TempObjId" = "./CanHardwareObject/*[position()=$HwObjindx]/CanObjectId"!][!//
[!IF "$LastCfgHrhId > $TempObjId"!][!//
[!ERROR!][!//
  ERROR: All HTHs should have greater CanObjectId than all HRHs.
    Eg.: CanObjectId in increasing order: HRHs of CanControllerId 0, HRHs of CanControllerId
    1, HTHs of CanControllerId 0, HTHs of CanControllerId 1, etc..
[!ENDERROR!][!//
[!ENDIF!][!//
[!IF "$Cntrlindx = $TempObjId"!][!//
[!IF "(node:ref(./CanHardwareObject/*[position()=$HwObjindx]/CanControllerRef)/CanTxProcessing = 'POLLING')"!][!//
[!IF "(node:exists(./CanHardwareObject/*[position()=$HwObjindx]/CanMainFunctionRWPeriodRef/*[1]))"!][!//
[!ELSE!]
[!ERROR!][!//
The HTH Hardare object[!"$TempObjId"!] shall be referenced or enabled (CanMainFunctionRWPeriodRef) with cyclic period,since the referenced controller is configured with Tx processing mode as POLLING
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "$LastCfgCntrlId != $HwControllerId"!][!//
[!VAR "TxDedicatedBuffIndex" = "num:i(0)"!][!//
[!ENDIF!][!//
[!IF "$LastCfgCntrlId > $HwControllerId"!][!//
[!ERROR!][!//
The HTH shall be configured in the increasing order of refrenced CanControllerId
Eg.: HTH object in order: HTHs of CanControllerId 0, HTHs of CanControllerId 1, etc..
[!ENDERROR!][!//
[!ENDIF!][!//
[!IF "$TxDedicatedBuffIndex > 0 or $NoOfInstance > 0"!][!//
,
[!ENDIF!][!//
[!VAR "LastCfgCntrlId" = "num:i($HwControllerId)"!][!//
[!VAR "TxHwObjCount" = "num:i(./CanHardwareObject/*[position()=$HwObjindx]/CanHwObjectCount)"!][!//
[!IF "$TxHwObjCount > 32"!][!//
[!ERROR!][!//
The value of CanHwobjectCount of HTH with CanHwObjectId [!"num:i(CanHardwareObject/*[position()=$HwObjindx]/CanObjectId)"!] is gretaer than value 32
[!ENDERROR!][!//
[!ENDIF!][!//
[!VAR "NoOfInstance" = "$NoOfInstance + num:i(1)"!][!//
[!VAR "CoreHthIndexName" = "text:toupper(concat($CoreHthIndexName,'HOHHTH',$TempObjId,'_','COREHTH',$CoreTxObjCnt,'_','CON',$HwControllerId,'_',$CheckText,','))"!][!//
[!VAR "CoreTxObjCnt" = "num:i($CoreTxObjCnt + '1')"!][!//
[!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanHwObjectCount = '1'"!][!//
 {[!"num:i(./CanHardwareObject/*[position()=$HwObjindx]/CanObjectId)"!]U,[!//
 [!"num:i($TxDedicatedBuffIndex)"!]U,[!//
 [!"num:i($HwControllerId)"!]U,[!//
[!VAR "TxDedicatedBuffIndex" = "$TxDedicatedBuffIndex + num:i(1)"!][!//
[!ELSE!][!//
 {[!//
[!"num:i(./CanHardwareObject/*[position()=$HwObjindx]/CanObjectId)"!]U,[!//
 [!"num:i(255)"!]U,[!//
 [!"num:i($HwControllerId)"!]U,[!//
[!ENDIF!][!//
[!IF "$FDNodesPresent = 1"!][!//
[!IF "$FDNodesPresentTmp = 1"!][!//
[!IF "(node:exists(./CanHardwareObject/*[position()=$HwObjindx]/CanFdPaddingValue/*[1]) = 'true' )"!][!//
 [!"num:i(./CanHardwareObject/*[position()=$HwObjindx]/CanFdPaddingValue/*[1])"!]U,[!//
[!ELSE!][!//
 0U,[!//
[!ENDIF!][!//
[!ELSE!][!//
 0U,[!//
[!ENDIF!][!//
[!ENDIF!][!//
 CAN_17_MCMCAN_ID_[!"./CanHardwareObject/*[position()=$HwObjindx]/CanIdType"!],[!//
[!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanHwObjectCount = '1'"!][!//
 [!"('CAN_17_MCMCAN_TX_DED_BUFFER')"!][!//
[!ELSE!][!//
 [!"('CAN_17_MCMCAN_TX_QUEUE')"!][!//
[!ENDIF!][!//
[!VAR "TrigTransmit" = "num:i(0)"!][!//
[!VAR "CanHwObjectCount" = "num:i(count(./CanHardwareObject/*))"!][!//
[!FOR "HwObjIndx2" = "1" TO "num:i($CanHwObjectCount)"!][!//
[!IF "node:exists(./CanHardwareObject/*[position()=$HwObjIndx2]/CanTriggerTransmitEnable/*[1]) = 'true'"!][!//
[!IF "node:value(./CanHardwareObject/*[position()=$HwObjIndx2]/CanTriggerTransmitEnable/*[1]) = 'true'"!][!//
[!VAR "TrigTransmit" = "num:i(1)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!IF "$TrigTransmit = num:i(1)"!][!//
[!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanTriggerTransmitEnable/*[1] ='true'"!][!//
, [!"('TRUE')"!]}[!//
[!ELSE!][!//
, [!"('FALSE')"!]}[!//
[!ENDIF!][!//
[!ELSE!][!//
}[!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!ELSE!][!//
[!ERROR!][!//
CanControllerRef is not Configured for CanHardwareObject [!"num:i(CanHardwareObject/*[position()=$HwObjindx]/CanObjectId)"!]
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDFOR!][!//

};
[!ENDIF!][!//
[!IF "num:i(count(../CanGeneral/CanMainFunctionRWPeriods/*)) > 1"!][!//
[!VAR "NoOfPeriods" = "num:i(count(../CanGeneral/CanMainFunctionRWPeriods/*))"!][!//
[!IF "$MainFunctTxPollingTmp = num:i(1)"!][!//
[!IF "$MainFunctTxPollUsedTmp = num:i(1)"!][!//
/*******************************************************************************
        Transmit Hardware Object Configurations for multiple period selected
                         for [!"$Text"!]
********************************************************************************
 Tx Object -> { TxbufferMaskvalue,HW MO Id,HwControllerId}
********************************************************************************
           Note:
*******************************************************************************/
[!VAR "Count" = "num:i(0)"!][!//
[!/* [cover parentID={114BDC47-084F-4da0-9321-0FEE3F91C71C}]
[/cover] */!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
static const Can_17_McmCan_HthMaskObjectConfigType \
  Can_17_McmCan_kHthMaskObjectConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][[!"$NoOfTxPollObj"!]] =
{
[!VAR "TxPeriodsIndex" = "''"!][!//
[!VAR "HthPeriodsCnt" = "num:i(0)"!][!//
[!VAR "TxPeriodExists" = "num:i(0)"!][!//
[!VAR "HthPeriodsIndex" = "num:i(0)"!][!//
[!VAR "ConfigPeriodIndex" = "num:i(0)"!][!//
[!AUTOSPACING!]
[!NOCODE!]
[!INDENT "2"!]
[!VAR "ControllerConfigMaxTemp" = "num:i(count(./CanController/*))"!][!//
[!LOOP "../CanGeneral/CanMainFunctionRWPeriods/*"!][!//
    [!VAR "MainFuncName" = "node:name(.)"!][!//
    [!LOOP "../../../CanConfigSet/CanController/*"!][!//
        [!VAR "BUFFR" = "num:i('00000000')"!][!//
        [!VAR "HwMainFuncNameConfig" = "''"!][!//
        [!VAR "Maskval" = "num:i('00000000')"!][!//
        [!VAR "BuffIndex" = "num:i(0)"!][!//
        [!VAR "TotHwObjCnt" = "num:i(0)"!][!//
        [!VAR "TotHwObjID" = "num:i(0)"!][!//
        [!VAR "TotHwObjCntID" = "num:i(0)"!][!//
        [!VAR "TxQueueIndex" = "num:i(0)"!][!//
        [!VAR "FifoCnt" = "num:i(0)"!][!//
        [!IF "CanControllerActivation = 'true'"!][!//
        [!IF "CanTxProcessing   = 'POLLING'"!][!//
            [!VAR "CntrlId" = "num:i(CanControllerId)"!][!//
            [!FOR "KerIndex" = "0" TO "$MaxKernel -'1'"!][!//
            [!VAR "ResKerCoreName" = "text:toupper(concat('CON',$CntrlId,'_','KERNEL',$KerIndex,'_',$CheckText))"!][!//
            [!IF "text:contains(text:split($CGCoreMap,','),$ResKerCoreName)"!][!//
            [!LOOP "../../../CanConfigSet/CanHardwareObject/*"!][!//
                [!IF "CanObjectType = 'TRANSMIT'"!][!//
                    [!IF "node:refexists(CanMainFunctionRWPeriodRef/*[1])='true'"!][!//
                        [!IF "$CntrlId = num:i(node:ref(CanControllerRef)/CanControllerId)"!][!//
                            [!IF "num:i(CanHwObjectCount) > 1 "!][!//
                                [!VAR "FifoCnt" = "num:i($FifoCnt + 1)"!][!//
                                [!VAR "TotHwObjCnt" = "num:i(CanHwObjectCount)"!][!//
                                [!VAR "TotHwObjID" = "num:i(CanObjectId)"!][!//
                                [!VAR "TotHwObjCntID" = "num:i($CntrlId)"!][!//
                              [!VAR "HwMainFuncNameConfig"= "substring-after(CanMainFunctionRWPeriodRef/*[1],'Can/Can/')"!][!//
                              [!VAR "HwMainFuncNameConfig"= "substring-after($HwMainFuncNameConfig,'/')"!][!//
                            [!ELSE!]
                                [!VAR "BuffIndex" = "num:i($BuffIndex + 1)"!][!//
                            [!ENDIF!][!//
                        [!ENDIF!][!//
                        [!VAR "MainFuncNameConfig"= "substring-after(CanMainFunctionRWPeriodRef/*[1],'Can/Can/')"!][!//
                        [!VAR "MainFuncNameConfig"= "substring-after($MainFuncNameConfig,'/')"!][!//
                        [!IF "$MainFuncNameConfig = $MainFuncName and $CntrlId = num:i(node:ref(CanControllerRef)/CanControllerId)"!][!//
                            [!IF "num:i(CanHwObjectCount) = 1 "!][!//
                                [!VAR "TxPeriodExists" = "num:i(1)"!][!//
                                [!VAR "BUFFR" = "bit:bitset($BUFFR,($BuffIndex - 1))"!][!//
                                [!VAR "Maskval" = "bit:or($BUFFR,'00000000')"!][!//
                            [!CODE!]
[!IF "$Count > '0'"!][!//
,
[!ENDIF!][!//
[!VAR "Count" = "num:i($Count+'1')"!][!//
{[!"num:inttohex($Maskval)"!]U, [!//
 [!"num:i(CanObjectId)"!]U, [!//
 [!"num:i($CntrlId)"!]U[!//
}[!//
[!ENDCODE!][!//
                            [!ENDIF!][!//
                            [!VAR "BUFFR" = "num:i(0)"!][!//
                            [!VAR "Maskval" = "num:i(00000000)"!][!//
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDLOOP!]
            [!ENDIF!][!//
            [!ENDFOR!][!//
        [!ENDIF!][!//
        [!ENDIF!][!//
        [!IF "$HwMainFuncNameConfig = $MainFuncName"!][!//
        [!IF "num:i($TotHwObjCnt) > 1 "!][!//
        [!VAR "TxPeriodExists" = "num:i(1)"!][!//
        [!FOR "TxQueueIndex" = "$BuffIndex" TO "$BuffIndex + $TotHwObjCnt - 1"!][!//
        [!VAR "BUFFR" = "bit:bitset($BUFFR,($TxQueueIndex))"!][!//
        [!VAR "Maskval" = "bit:or($BUFFR,'00000000')"!][!//
        [!ENDFOR!][!//
                            [!CODE!]
,
{[!"num:inttohex($Maskval)"!]U, [!//
 [!"num:i($TotHwObjID)"!]U, [!//
 [!"num:i($TotHwObjCntID)"!]U[!//
}[!//
[!ENDCODE!][!//
[!VAR "TotHwObjCnt" = "num:i(0)"!][!//
        [!ENDIF!][!//
        [!ENDIF!][!//
        [!ENDLOOP!]
[!IF "$TxPeriodExists = num:i(1)"!][!//
[!VAR "TxPeriodsIndex" = "text:toupper(concat($TxPeriodsIndex,$ConfigPeriodIndex,'_',$HthPeriodsIndex,'_',$CheckText,','))"!][!//
[!VAR "ConfigPeriodIndex" = "num:i($ConfigPeriodIndex + 1)"!][!//
[!VAR "HthPeriodsCnt" = "num:i($HthPeriodsCnt + 1)"!][!//
[!VAR "TxPeriodExists" = "num:i(0)"!][!//
[!ENDIF!][!//
[!VAR "HthPeriodsIndex" = "num:i($HthPeriodsIndex + 1)"!][!//
[!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//

};
/*******************************************************************************
   Tx HwObject handling for Multiple index is selected for [!"$Text"!]
********************************************************************************
     Each Period informations -> { Startindex , Endindex}
********************************************************************************

*******************************************************************************/
[!VAR "Count1" = "num:i(0)"!][!//
[!/* [cover parentID={99BB9C2A-CC1F-455f-9080-DD6A9A7FF276}]
[/cover] */!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
static const Can_17_McmCan_PeriodHthMaskConfigType \
  Can_17_McmCan_kPeriodHthMaskConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][[!"$HthPeriodsCnt"!]] =
{
[!VAR "StartIndx" = "num:i(0)"!][!//
[!VAR "PeriodTempName" = "''"!][!//
[!LOOP "../CanGeneral/CanMainFunctionRWPeriods/*"!][!//
[!VAR "Count" = "num:i(0)"!][!//
[!VAR "EndIndex" = "num:i(0)"!][!//
[!VAR "MainFuncName" = "node:name(.)"!][!//
[!LOOP "../../../CanConfigSet/CanHardwareObject/*"!][!//
[!VAR "CntrlId" = "num:i(node:ref(CanControllerRef)/CanControllerId)"!][!//
[!FOR "KerIndex" = "0" TO "$MaxKernel -'1'"!][!//
[!VAR "ResKerCoreName" = "text:toupper(concat('CON',$CntrlId,'_','KERNEL',$KerIndex,'_',$CheckText))"!][!//
[!IF "text:contains(text:split($CGCoreMap,','),$ResKerCoreName)"!][!//
[!IF "CanObjectType = 'TRANSMIT'"!][!//
[!IF "(node:ref(CanControllerRef)/CanTxProcessing) = 'POLLING'"!][!//
[!VAR "MainFuncNameConfig"= "substring-after(CanMainFunctionRWPeriodRef/*[1],'Can/Can/')"!][!//
[!VAR "MainFuncNameConfig"= "substring-after($MainFuncNameConfig,'/')"!][!//
[!IF "$MainFuncNameConfig = $MainFuncName"!][!//
[!VAR "Count" = "num:i(1)"!][!//
[!VAR "EndIndex" = "num:i($EndIndex+ '1')"!][!//
[!IF "$MainFuncNameConfig != $PeriodTempName"!][!//
[!VAR "InstanceHth" = "num:i($InstanceHth+ '1')"!][!//
[!ENDIF!][!//
[!VAR "PeriodTempName" = "$MainFuncNameConfig"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDLOOP!][!//
[!IF "$Count > '0'"!][!//
[!IF "$Count1 > '0'"!][!//
,
[!ENDIF!][!//
[!VAR "Count1" = "num:i($Count1+'1')"!][!//
{[!"num:i($StartIndx)"!]U, [!//
[!"num:i($EndIndex)"!]U}[!//
[!VAR "StartIndx" = "num:i($StartIndx + $EndIndex)"!][!//
[!VAR "Count" = "num:i(0)"!][!//
[!ENDIF!][!//
[!ENDLOOP!]

};
/******************************************************************************/
        /* Core Specific Multi Tx Period Indexing Configuration */
/******************************************************************************/
      /* Core Specific Multi Tx Period indexing indicating the
         core specific indexing for a configured period index passed*/
/******************************************************************************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
static const Can_17_McmCan_HthPeriodIndexType \
  Can_17_McmCan_kHthPeriodIndex[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][[!"num:i(count(../CanGeneral/CanMainFunctionRWPeriods/*))"!]] =
{[!//
[!VAR "HthPeriodDetected" = "num:i(0)"!][!//
[!VAR "Count1" = "num:i(0)"!][!//
[!FOR "RwPeriodIndex" = "0" TO "$NoOfPeriods -'1'"!][!//
[!FOR "HthPeriodIndex" = "0" TO "$NoOfPeriods -'1'"!][!//
[!VAR "CheckVal" = "text:toupper(concat($HthPeriodIndex,'_',$RwPeriodIndex,'_',$CheckText))"!][!//
[!IF "text:contains(text:split($TxPeriodsIndex,','),$CheckVal)"!][!//
[!IF "$Count1 > '0'"!][!//
,[!//
[!ENDIF!][!//
[!VAR "Count1" = "num:i($Count1+'1')"!][!//
[!VAR "HthPeriodDetected" = "num:i(1)"!][!//
[!"$HthPeriodIndex"!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!IF "$HthPeriodDetected = num:i(0)"!][!//
[!IF "$Count1 > '0'"!][!//
,[!//
[!ENDIF!][!//
[!VAR "Count1" = "num:i($Count1+'1')"!][!//
255[!//
[!ENDIF!][!//
[!VAR "HthPeriodDetected" = "num:i(0)"!][!//
[!ENDFOR!][!//
};
[!ENDIF!][!//
[!ENDIF!][!//

[!IF "$MainFunctRxPollingTmp = num:i(1)"!][!//
[!IF "$MainFunctRxPollUsedTmp = num:i(1)"!][!//
/*******************************************************************************
    Receive Hardware Object Configurations for multiple period selected
                               for [!"$Text"!]
********************************************************************************
Rx Object -> { CanPerRxbufferMaskvalue0,CanPerRxbufferMaskvalue1,
               CanPerHrhHwObjId,HwControllerId,CanPerHrhBufferType}
********************************************************************************

*******************************************************************************/
[!VAR "Count" = "num:i(0)"!][!//
[!/* [cover parentID={3C45073E-8BED-4d56-B147-8512C596C39A}]
[/cover] */!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
static const Can_17_McmCan_HrhMaskObjectConfigType \
  Can_17_McmCan_kHrhMaskObjectConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][[!"$NoOfRxPollObj"!]] =
{
[!VAR "HrhPeriodsCnt" = "num:i(0)"!][!//
[!VAR "RxPeriodExists" = "num:i(0)"!][!//
[!VAR "RxPeriodsIndex" = "''"!][!//
[!VAR "HrhPeriodsIndex" = "num:i(0)"!][!//
[!VAR "ConfigPeriodIndex" = "num:i(0)"!][!//
[!AUTOSPACING!]
[!NOCODE!]
[!INDENT "2"!]
[!VAR "ControllerConfigMaxTemp" = "num:i(count(./CanController/*))"!][!//
[!LOOP "../CanGeneral/CanMainFunctionRWPeriods/*"!][!//
    [!VAR "MainFuncName" = "node:name(.)"!][!//
    [!LOOP "../../../CanConfigSet/CanController/*"!][!//
        [!VAR "BUFFR" = "num:i('00000000')"!][!//
        [!VAR "BUFFR2" = "num:i('00000000')"!][!//
        [!VAR "Maskval" = "num:i('00000000')"!][!//
        [!VAR "Maskval2" = "num:i('00000000')"!][!//
        [!VAR "BuffIndexCount" = "num:i(0)"!][!//
        [!VAR "BuffIndex" = "num:i(0)"!][!//
        [!VAR "BuffIndex2" = "num:i(0)"!][!//
        [!VAR "BuffIndexExtAvail" = "num:i(0)"!][!//
        [!VAR "FifoCnt" = "num:i(0)"!][!//
        [!IF "CanControllerActivation = 'true'"!][!//
        [!IF "CanRxProcessing   = 'POLLING'"!][!//
            [!VAR "CntrlId" = "num:i(CanControllerId)"!][!//
            [!FOR "KerIndex" = "0" TO "$MaxKernel -'1'"!][!//
            [!VAR "ResKerCoreName" = "text:toupper(concat('CON',$CntrlId,'_','KERNEL',$KerIndex,'_',$CheckText))"!][!//
            [!IF "text:contains(text:split($CGCoreMap,','),$ResKerCoreName)"!][!//
            [!LOOP "../../../CanConfigSet/CanHardwareObject/*"!][!//
                [!IF "CanObjectType = 'RECEIVE'"!][!//
                    [!IF "node:refexists(CanMainFunctionRWPeriodRef/*[1])='true'"!][!//
                        [!IF "$CntrlId = num:i(node:ref(CanControllerRef)/CanControllerId)"!][!//
                            [!IF "num:i(CanHwObjectCount) > 1 "!][!//
                                [!VAR "FifoCnt" = "num:i($FifoCnt + 1)"!][!//
                            [!ELSE!]
                                [!VAR "BuffIndexCount" = "num:i($BuffIndexCount + 1)"!][!//
                                [!VAR "BuffIndex" = "num:i($BuffIndex + 1)"!][!//
                                [!IF "num:i($BuffIndexCount) > 32 "!][!//
                                [!VAR "BuffIndex" = "num:i(0)"!][!//
                                [!VAR "BuffIndexExtAvail" = "num:i(1)"!][!//
                                [!VAR "BuffIndex2" = "num:i($BuffIndex2 + 1)"!][!//
                                [!ENDIF!][!//
                            [!ENDIF!][!//
                        [!ENDIF!][!//
                        [!VAR "MainFuncNameConfig"= "substring-after(CanMainFunctionRWPeriodRef/*[1],'Can/Can/')"!][!//
                        [!VAR "MainFuncNameConfig"= "substring-after($MainFuncNameConfig,'/')"!][!//
                        [!IF "$MainFuncNameConfig = $MainFuncName and $CntrlId = num:i(node:ref(CanControllerRef)/CanControllerId)"!][!//
                            [!IF "num:i(CanHwObjectCount) = 1 "!][!//
                                [!VAR "RxPeriodExists" = "num:i(1)"!][!//
                                [!IF "num:i($BuffIndexExtAvail) = 1 "!][!//
                                [!VAR "BUFFR" = "num:i(0)"!][!//
                                [!VAR "Maskval" = "bit:or($BUFFR,'00000000')"!][!//
                                [!VAR "BUFFR2" = "bit:bitset($BUFFR2,($BuffIndex2 - 1))"!][!//
                                [!VAR "Maskval2" = "bit:or($BUFFR2,'00000000')"!][!//
                                [!ELSE!][!//
                                [!VAR "BUFFR" = "bit:bitset($BUFFR,($BuffIndex - 1))"!][!//
                                [!VAR "Maskval" = "bit:or($BUFFR,'00000000')"!][!//
                                [!ENDIF!][!//
                            [!ENDIF!][!//
[!CODE!]
[!IF "$Count > '0'"!][!//
,
[!ENDIF!][!//
[!VAR "Count" = "num:i($Count+'1')"!][!//
{[!"num:inttohex($Maskval)"!]U, [!//
 [!"num:inttohex($Maskval2)"!]U, [!//
 [!"num:i(CanObjectId)"!]U, [!//
 [!"num:i($CntrlId)"!]U, [!//
[!IF "num:i(CanHwObjectCount) = 1 "!][!//
 CAN_17_MCMCAN_RX_DED_BUFFER[!//
[!ELSE!][!//
[!IF "$FifoCnt = 1 "!][!//
[!VAR "RxPeriodExists" = "num:i(1)"!][!//
 CAN_17_MCMCAN_RX_FIFO0[!//
[!ELSE!][!//
[!VAR "RxPeriodExists" = "num:i(1)"!][!//
 CAN_17_MCMCAN_RX_FIFO1[!//
[!ENDIF!][!//
[!ENDIF!][!//
}[!//
[!ENDCODE!][!//
                            [!VAR "BUFFR" = "num:i(0)"!][!//
                            [!VAR "Maskval" = "num:i(00000000)"!][!//
                            [!VAR "BUFFR2" = "num:i(0)"!][!//
                            [!VAR "Maskval2" = "num:i(00000000)"!][!//
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDLOOP!]
        [!ENDIF!][!//
        [!ENDFOR!][!//
        [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDLOOP!]
[!IF "$RxPeriodExists = num:i(1)"!][!//
[!VAR "RxPeriodsIndex" = "text:toupper(concat($RxPeriodsIndex,$ConfigPeriodIndex,'_',$HrhPeriodsIndex,'_',$CheckText,','))"!][!//
[!VAR "ConfigPeriodIndex" = "num:i($ConfigPeriodIndex + 1)"!][!//
[!VAR "HrhPeriodsCnt" = "num:i($HrhPeriodsCnt + 1)"!][!//
[!VAR "RxPeriodExists" = "num:i(0)"!][!//
[!ENDIF!][!//
[!VAR "HrhPeriodsIndex" = "num:i($HrhPeriodsIndex + 1)"!][!//
[!ENDLOOP!]
[!ENDINDENT!]
[!ENDNOCODE!]

};
/*******************************************************************************
      Rx HwObject handling for Multiple index is selected for [!"$Text"!]
********************************************************************************
      Each Rx Period informations -> { Startindex , Endindex }
********************************************************************************
           Note:
*******************************************************************************/
[!VAR "Count1" = "num:i(0)"!][!//
[!/* [cover parentID={8D97235B-324D-4fb4-ABA0-55F09A79DF18}]
[/cover] */!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
static const Can_17_McmCan_PeriodHrhMaskConfigType \
  Can_17_McmCan_kPeriodHrhMaskConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][[!"$HrhPeriodsCnt"!]] =
{
[!VAR "StartIndx" = "num:i(0)"!][!//
[!VAR "PeriodTempName" = "''"!][!//
[!LOOP "../CanGeneral/CanMainFunctionRWPeriods/*"!][!//
[!VAR "Count" = "num:i(0)"!][!//
[!VAR "EndIndex" = "num:i(0)"!][!//
[!VAR "MainFuncName" = "node:name(.)"!][!//
[!LOOP "../../../CanConfigSet/CanHardwareObject/*"!][!//
[!IF "CanObjectType = 'RECEIVE'"!][!//
[!IF "(node:ref(CanControllerRef)/CanRxProcessing) = 'POLLING'"!][!//
[!VAR "CntrlId" = "num:i(node:ref(CanControllerRef)/CanControllerId)"!][!//
[!FOR "KerIndex" = "0" TO "$MaxKernel -'1'"!][!//
[!VAR "ResKerCoreName" = "text:toupper(concat('CON',$CntrlId,'_','KERNEL',$KerIndex,'_',$CheckText))"!][!//
[!IF "text:contains(text:split($CGCoreMap,','),$ResKerCoreName)"!][!//
[!IF "node:refexists(CanMainFunctionRWPeriodRef/*[1])='true'"!][!//
[!VAR "MainFuncNameConfig" = "substring-after(CanMainFunctionRWPeriodRef/*[1],'Can/Can/')"!][!//
[!VAR "MainFuncNameConfig" = "substring-after($MainFuncNameConfig,'/')"!][!//
[!IF "$MainFuncNameConfig = $MainFuncName"!][!//
[!VAR "EndIndex" = "num:i($EndIndex + '1')"!][!//
[!VAR "Count" = "num:i(1)"!][!//
[!IF "$MainFuncNameConfig != $PeriodTempName"!][!//
[!VAR "InstanceHrh" = "num:i($InstanceHrh + '1')"!][!//
[!ENDIF!][!//
[!VAR "PeriodTempName" = "$MainFuncNameConfig"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!IF "$Count > '0'"!][!//
[!IF "$Count1 > '0'"!][!//
,
[!ENDIF!][!//
[!VAR "Count1" = "num:i($Count1+'1')"!][!//
{[!"num:i($StartIndx)"!]U, [!//
[!"num:i($EndIndex)"!]U}[!//
[!VAR "StartIndx" = "num:i($StartIndx + $EndIndex)"!][!//
[!ENDIF!][!//
[!ENDLOOP!]

};
/******************************************************************************/
        /* Core Specific Multi Rx Period Indexing Configuration */
/******************************************************************************/
      /* Core Specific Multi Rx Period indexing indicating the
         core specific indexing for a configured period index passed*/
/******************************************************************************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
static const Can_17_McmCan_HrhPeriodIndexType \
  Can_17_McmCan_kHrhPeriodIndex[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][[!"num:i(count(../CanGeneral/CanMainFunctionRWPeriods/*))"!]] =
{[!//
[!VAR "HrhPeriodDetected" = "num:i(0)"!][!//
[!VAR "Count1" = "num:i(0)"!][!//
[!FOR "RwPeriodIndex" = "0" TO "$NoOfPeriods -'1'"!][!//
[!FOR "HrhPeriodIndex" = "0" TO "$NoOfPeriods -'1'"!][!//
[!VAR "CheckVal" = "text:toupper(concat($HrhPeriodIndex,'_',$RwPeriodIndex,'_',$CheckText))"!][!//
[!IF "text:contains(text:split($RxPeriodsIndex,','),$CheckVal)"!][!//
[!IF "$Count1 > '0'"!][!//
,[!//
[!ENDIF!][!//
[!VAR "Count1" = "num:i($Count1+'1')"!][!//
[!VAR "HrhPeriodDetected" = "num:i(1)"!][!//
[!"$HrhPeriodIndex"!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!IF "$HrhPeriodDetected = num:i(0)"!][!//
[!IF "$Count1 > '0'"!][!//
,[!//
[!ENDIF!][!//
[!VAR "Count1" = "num:i($Count1+'1')"!][!//
255[!//
[!ENDIF!][!//
[!VAR "HrhPeriodDetected" = "num:i(0)"!][!//
[!ENDFOR!][!//
};
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//

/******************************************************************************/
             /* CAN Configuration Pointer for [!"$Text"!] */
/******************************************************************************/
    /* Core sepcific CAN configurations */
/******************************************************************************/
[!/* [cover parentID={44E1A912-8120-4508-AD66-83117EAE13F0}]
[/cover] */!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
static const Can_17_McmCan_CoreConfigType \
  Can_17_McmCan_kMcmCanConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!] =
{
    /* Number of controllers configured for the core */
    [!"$NoOfCont"!],
    /* Array of all the controllers configured */
    &Can_17_McmCan_kControllerIndexing[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][0],
    /* Pointer to CAN controller configuration settings */
    &Can_17_McmCan_kControllerConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][0],
    /* Pointer to Message RAM configuration settings */
    &Can_17_McmCan_kControllerMsgRAMMapConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][0],
    /* Pointer to CAN Controller Handling of Events : Interrupt/Polling */
    &Can_17_McmCan_kEventHandlingConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][0],
    /* Pointer to Baudrate configuration settings */
    &Can_17_McmCan_kBaudrateConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][0],
[!IF "$FDNodesPresent != 0"!][!//
[!IF "$FDNodesPresentTmp != 0"!][!//
    /* Pointer to FDBaudrate configuration settings */
    &Can_17_McmCan_kFDBaudrateConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][0],
[!ELSE!][!//
    /* Pointer to FDBaudrate configuration settings */
    NULL_PTR,
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "$TxObjectCountMaxTmp != 0"!][!//
    /* Pointer to CAN Controller <-> Tx Hardware Objects Mapping */
    &Can_17_McmCan_kTxHwObjectConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][0],
[!ELSE!][!//
    /* Pointer to CAN Controller <-> Tx Hardware Objects Mapping */
    NULL_PTR,
[!ENDIF!][!//
[!IF "$StandardIdOnlyTmp = '1' or $MixedOnlyTmp = '1' "!][!//
    /* Pointer to CAN Controller <-> Rx Hardware Objects Mapping for Standard
       messages */
    &Can_17_McmCan_kSIDFilterConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][0],
[!ELSE!][!//
    /* Pointer to CAN Controller <-> Rx Hardware Objects Mapping for Standard
    messages */
    NULL_PTR,
[!ENDIF!][!//
[!IF "$ExtendedOnlyTmp = '1' or $MixedOnlyTmp = '1'"!][!//
    /* Pointer to CAN Controller <-> Rx Hardware Objects Mapping for Extended
    messages */
    &Can_17_McmCan_kXIDFilterConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][0][!//
[!ELSE!][!//
    /* Pointer to CAN Controller <-> Rx Hardware Objects Mapping for Extended
    messages */
    NULL_PTR[!//
[!ENDIF!][!//
[!IF "$MainFunctTxPolling = num:i(1)"!][!//
[!IF "num:i(count(../CanGeneral/CanMainFunctionRWPeriods/*)) > 1"!][!//
[!IF "$MainFunctTxPollingTmp = num:i(1)"!][!//
[!IF "$MainFunctTxPollUsedTmp = num:i(1)"!][!//
,
    /* Transmit Period to core specific period mapping*/
    &Can_17_McmCan_kHthPeriodIndex[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][0],
    /* Pointer to CAN Controller <-> Tx Hardware Objects Mapping for Multiple
    period */
    &Can_17_McmCan_kHthMaskObjectConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][0],
    /* Pointer to CAN Controller <-> Tx Hardware Index Mapping for Multiple
    period */
    &Can_17_McmCan_kPeriodHthMaskConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][0][!//
[!ELSE!][!//
,
    /* Transmit Period to core specific period mapping*/
    NULL_PTR,
    /* Pointer to CAN Controller <-> Tx Hardware Objects Mapping for Multiple
    period */
    NULL_PTR,
    /* Pointer to CAN Controller <-> Tx Hardware Index Mapping for Multiple
    period */
    NULL_PTR[!//
[!ENDIF!][!//
[!ELSE!][!//
,
    /* Transmit Period to core specific period mapping*/
    NULL_PTR,
    /* Pointer to CAN Controller <-> Tx Hardware Objects Mapping for Multiple
    period */
    NULL_PTR,
    /* Pointer to CAN Controller <-> Tx Hardware Index Mapping for Multiple
    period */
    NULL_PTR[!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "$MainFunctRxPolling = num:i(1)"!][!//
[!IF "num:i(count(../CanGeneral/CanMainFunctionRWPeriods/*)) > 1"!][!//
[!IF "$MainFunctRxPollingTmp = num:i(1)"!][!//
[!IF "$MainFunctRxPollUsedTmp = num:i(1)"!][!//
,
    /* Recieve Period to core specific period mapping*/
    &Can_17_McmCan_kHrhPeriodIndex[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][0],
    /* Pointer to CAN Controller <-> Rx Hardware Objects Mapping for Multiple
    period */
    &Can_17_McmCan_kHrhMaskObjectConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][0],
    /* Pointer to CAN Controller <-> Rx Hardware Index Mapping for Multiple
    period */
    &Can_17_McmCan_kPeriodHrhMaskConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][0][!//
[!ELSE!][!//
,
    /* Recieve Period to core specific period mapping*/
    NULL_PTR,
    /* Pointer to CAN Controller <-> Rx Hardware Objects Mapping for Multiple
    period */
    NULL_PTR,
    /* Pointer to CAN Controller <-> Rx Hardware Index Mapping for Multiple
    period */
    NULL_PTR[!//
[!ENDIF!][!//
[!ELSE!][!//
,
    /* Recieve Period to core specific period mapping*/
    NULL_PTR,
    /* Pointer to CAN Controller <-> Rx Hardware Objects Mapping for Multiple
    period */
    NULL_PTR,
    /* Pointer to CAN Controller <-> Rx Hardware Index Mapping for Multiple
    period */
    NULL_PTR[!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//

};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
#define [!"text:toupper(concat('CAN_17_MCMCAN_STOP_SEC_CONFIG_DATA_QM_',$CheckText,'_UNSPECIFIED'))"!]
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"

[!ENDIF!][!//
[!VAR "ContAllocIndex" = "text:toupper(concat($ContAllocIndex,$ResKerCoreIndName))"!][!//
[!VAR "HthIndexName" = "text:toupper(concat($HthIndexName,$CoreHthIndexName))"!][!//
[!VAR "CoreHthIndexName" = "''"!][!//
[!ENDFOR!][!//
[!/* Calculating the total Hrh and Hth Values */!][!//
[!VAR "HwObjctCnt" = "num:i(count(./CanHardwareObject/*))"!][!//
[!FOR "HwObjindx" = "1" TO "$HwObjctCnt"!][!//
[!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanObjectType = 'RECEIVE'"!][!//
[!VAR "TNoOfHrh" = "num:i($TNoOfHrh + '1')"!][!//
[!ENDIF!][!//
[!IF "./CanHardwareObject/*[position()=$HwObjindx]/CanObjectType = 'TRANSMIT'"!][!//
[!VAR "TNoOfHth" = "num:i($TNoOfHth + '1')"!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDSELECT!]
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"

[!IF "$PublicIcomSupport > num:i(0)"!][!//
/*******************************************************************************
              CAN ICOM Configuration Parameters
********************************************************************************
         {CanIcomFirstMsgIndx, CanIcomNoOfMsgIndx, CanIcomWakeOnBusOff}
********************************************************************************
           Note:
 1. CanIcomFirstMsgIndx : First Receive message configuration index value
 2. CanIcomNoOfMsgIndx: Total no of RxMsg configured  for the ICOM configuration
 3. CanIcomWakeOnBusOff:  ICOM Wake On Bus off status
*******************************************************************************/
[!SELECT "as:modconf('Can')[1]/CanConfigSet"!][!//
[!VAR "IcomConfigCount" = "num:i(count(./CanIcom/*[1]/CanIcomConfig/*))"!][!//
[!VAR "StartIndx1" = "num:i(0)"!][!//
[!VAR "EndIndx1" = "num:i(0)"!][!//
[!/* [cover parentID={9CFEA617-17A3-4a56-98AD-3C96F99BD842}]
[/cover] */!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
static const Can_17_McmCan_IcomConfigType \
  Can_17_McmCan_kMcmCanIcomConfig[!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][CAN_17_MCMCAN_NOOF_ICOM_CONFIGURATIONS] =
{
[!LOOP "CanIcom/*[1]/CanIcomConfig/*"!][!//
[!FOR "Index" = "1" TO "num:i($IcomConfigCount)"!][!//
[!IF "$Index = num:i(./CanIcomConfigId)"!][!//
[!IF "$Index > 1 "!][!//
,
[!ENDIF!][!//
[!VAR "EndIndx1" = "num:i(count(./CanIcomWakeupCauses/CanIcomRxMessage/*))"!][!//
 {
 [!"num:i($StartIndx1)"!]U, [!//
[!"num:i($EndIndx1)"!]U, [!//
[!IF "(./CanIcomWakeOnBusOff  ) = 'true' "!][!//
TRUE
[!ELSE!][!//
FALSE
[!ENDIF!][!//
 }[!//
[!VAR "StartIndx1" = "num:i($StartIndx1+$EndIndx1)"!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDLOOP!]

};
[!ENDSELECT!][!//

/*******************************************************************************
            CAN ICOM Rx Message Configuration
********************************************************************************
        {CanIcomMsgId,CanIcomMaskRef,CanIcomCntrVal,[IcomFirstSignalIndex,
        IcomNoOfSignalIndex,]IcomPayloadLength, IcomLengthErrr}
********************************************************************************
1. CanIcomMsgId            : ICOM receive Message Id value.
2. CanIcomMaskRef          : ICOM receive Message filter mask value.
3. CanIcomCntrVal          : Counter value for receive no of times of a
                          specified ID Message.
4. IcomPayloadLength    : ICOM receive message payload length.
5. IcomFirstSignalIndex : First RxSignal index value of the message signal
                          configuration.
6. IcomNoOfSignalIndex  : Total no of message signal configurations.
7. CanIcomLengthErr        : Defines that the MCU shall wake if a payload error
                          occur.
                          TRUE  :MCU shall wake if a payload error
                          occur.
                          FALSE :MCU shall not wake if a payload error
                          occur.
*******************************************************************************/
[!SELECT "as:modconf('Can')[1]/CanConfigSet"!][!//
[!VAR "IcomConfigCount" = "num:i(count(./CanIcom/*[1]/CanIcomConfig/*))"!][!//
[!VAR "StartIndx" = "num:i(0)"!][!//
[!VAR "EndIndx" = "num:i(0)"!][!//
[!VAR "PosIndx" = "num:i(0)"!][!//
[!/* [cover parentID={A0BEE4C9-30BF-4825-A5C2-10DA464EEBF4}]
[/cover] */!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
static const Can_17_McmCan_IcomRxMsgConfigType \
  Can_17_McmCan_kMcmCanIcomRxMsgConfig[!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][CAN_17_MCMCAN_NOOF_ICOM_MSGCONFIGURATIONS] =
{
[!LOOP "CanIcom/*[1]/CanIcomConfig/*"!][!//
[!FOR "Index" = "1" TO "num:i($IcomConfigCount)"!][!//
[!IF "$Index = num:i(./CanIcomConfigId)"!][!//
[!VAR "IcomRxMsgCount" = "num:i(count(./CanIcomWakeupCauses/CanIcomRxMessage/*))"!][!//
[!FOR "Rxindx" = "1" TO "num:i($IcomRxMsgCount)"!][!//
[!IF "$PosIndx > 0 "!][!//
,
[!ENDIF!][!//
[!VAR "PosIndx" = "num:i($PosIndx+ 1)"!][!//
[!VAR "NormalMsgSupport" = "num:i(0)"!][!//
[!VAR "IcomMsgId" = "num:i(./CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomMessageId)"!][!//
[!SELECT "as:modconf('Can')[1]/CanConfigSet"!][!//
[!LOOP "./CanHardwareObject/*"!][!//
[!IF "CanObjectType = 'RECEIVE' "!][!//
[!VAR "HwFilterCount" = "num:i(count(CanHwFilter/*))"!][!//
[!FOR "HwFilterindx" = "1" TO "$HwFilterCount"!][!//
[!VAR "MsgId" = "num:i(CanHwFilter/*[position()=$HwFilterindx]/CanHwFilterCode)"!][!//
[!VAR "HwFilterMaskValue" = "num:i(CanHwFilter/*[position()=$HwFilterindx]/CanHwFilterMask)"!][!//
[!IF "./CanIdType = 'MIXED'"!][!//
[!VAR "HwFilterValue" = "bit:and($HwFilterValue,536608768)"!][!//
[!VAR "HwFilterValue" = "bit:shr($HwFilterValue,18)"!][!//
[!VAR "HwFilterMaskValue" = "bit:and($HwFilterMaskValue,536608768)"!][!//
[!VAR "HwFilterMaskValue" = "bit:shr($HwFilterMaskValue,18)"!][!//
[!ENDIF!][!//
[!IF "$RxBufferType != 'CAN_17_MCMCAN_RX_DED_BUFFER'"!][!//
[!VAR "CheckHwFilterValue" = "bit:and($MsgId,$HwFilterMaskValue)"!][!//
[!VAR "CheckIcomFilterValue" = "bit:and($IcomMsgId,$HwFilterMaskValue)"!][!//
[!ELSE!][!//
[!VAR "CheckHwFilterValue" = "$MsgId"!][!//
[!VAR "CheckIcomFilterValue" = "$IcomMsgId"!][!//
[!ENDIF!][!//
[!IF " $CheckHwFilterValue = $CheckIcomFilterValue"!][!//
[!VAR "NormalMsgSupport" = "num:i(1)"!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!IF "$NormalMsgSupport = num:i(0)"!][!//
[!ERROR!][!//
 In the CanIcomConfigId [!"$Rxindx"!] Message Id configured [!"$IcomMsgId"!] cannot be recieved by any of the recieve object CanHwFilters configured
[!ENDERROR!][!//
[!ENDIF!][!//
{[!"num:i(./CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomMessageId)"!]U, [!//
[!IF "(node:exists(CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomMessageIdMask/*[1]))"!][!//
[!"num:i(./CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomMessageIdMask/*[1])"!]U, [!//
[!ELSE!][!//
0U, [!//
[!ENDIF!][!//
[!IF "(node:exists(./CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomCounterValue/*[1]))"!][!//
[!"num:i(./CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomCounterValue/*[1])"!]U, [!//
[!ELSE!][!//
0U, [!//
[!ENDIF!][!//
[!"num:i(./CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomPayloadLength)"!]U,[!//
[!IF "node:exists(./CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomRxMessageSignalConfig/*) = 'true'"!][!//
[!VAR "EndIndx" = "num:i(count(./CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomRxMessageSignalConfig/*))"!][!//
 [!"num:i($StartIndx)"!]U, [!//
 [!"num:i($EndIndx)"!]U, [!//
[!VAR "StartIndx" = "num:i($StartIndx+$EndIndx)"!][!//
[!ELSE!][!//
 0U, [!//
 0U, [!//
[!ENDIF!][!//
[!IF "(./CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomPayloadLengthError) = 'true'"!][!//
TRUE[!//
[!ELSE!][!//
FALSE[!//
[!ENDIF!][!//
}[!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDLOOP!]

};
[!ENDSELECT!][!//
[!IF "$IcomRxMsgSignalCount > 0 "!][!//
/*******************************************************************************
          CAN ICOM Rx Signal Configuration
********************************************************************************
        { CanIcomSignalMask, CanIcomSignalValue, CanIcomSignalOper }
********************************************************************************
           Note:
1. CanIcomSignalMask  :ICOM receive signal filter mask value.
2. CanIcomSignalValue :ICOM receive signal value for the comparison with
                    CanIcomSignalMask value
3. CanIcomSignalOper  :Defines the operation, which shall be used to verify the
                    signal value creates a wakeup condition
*******************************************************************************/
[!SELECT "as:modconf('Can')[1]/CanConfigSet"!][!//
[!VAR "IcomConfigCount" = "num:i(count(./CanIcom/*/CanIcomConfig/*))"!][!//
[!VAR "StartIndx" = "num:i(0)"!][!//
[!VAR "SignalMaskByte1" = "num:i(255)"!][!//
[!VAR "SignalMaskByte2" = "num:i(65280)"!][!//
[!VAR "SignalMaskByte3" = "num:i(16711680)"!][!//
[!VAR "SignalMaskByte4" = "num:i(4278190080)"!][!//
[!VAR "SignalMaskByte5" = "num:i(255)"!][!//
[!VAR "SignalMaskByte6" = "num:i(65280)"!][!//
[!VAR "SignalMaskByte7" = "num:i(16711680)"!][!//
[!VAR "SignalMaskByte8" = "num:i(4278190080)"!][!//
[!/* [cover parentID={95671FD1-CFAD-47c0-AC23-DD83C757A90C}]
[/cover] */!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
static const Can_17_McmCan_IcomRxMsgSignalConfigType \
  Can_17_McmCan_kMcmCanIcomRxMsgSignalConfig[!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][CAN_17_MCMCAN_NOOF_ICOM_SIGNALCONFIGURATIONS] =
{
[!LOOP "CanIcom/*/CanIcomConfig/*"!][!//
[!FOR "Index" = "1" TO "num:i($IcomConfigCount)"!][!//
[!IF "$Index = num:i(./CanIcomConfigId)"!][!//
[!VAR "IcomRxMsgCount" = "num:i(count(./CanIcomWakeupCauses/CanIcomRxMessage/*))"!][!//
[!FOR "Rxindx" = "0" TO "num:i($IcomRxMsgCount)"!][!//
[!IF "node:exists(./CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomRxMessageSignalConfig/*[1]) = 'true'"!][!//
[!VAR "IcomRxMsgSignalCount" = "num:i(count(./CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomRxMessageSignalConfig/*))"!][!//
[!FOR "RxSignalindx" = "1" TO "num:i($IcomRxMsgSignalCount)"!][!//
[!IF "$StartIndx > 0 "!][!//
,
[!ENDIF!][!//
{
[!VAR "StartIndx" = "num:i($StartIndx+ 1)"!][!//
[!VAR "IcomSignalMaskUpper32" = "num:i(./CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomRxMessageSignalConfig/*[position()=$RxSignalindx]/CanIcomSignalMaskUpper32bits)"!][!//
[!VAR "IcomSignalMaskLower32" = "num:i(./CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomRxMessageSignalConfig/*[position()=$RxSignalindx]/CanIcomSignalMaskLower32bits)"!][!//
[!VAR "IcomSignalValueUpper32" = "num:i(./CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomRxMessageSignalConfig/*[position()=$RxSignalindx]/CanIcomSignalValueUpper32bits)"!][!//
[!VAR "IcomSignalValueLower32" = "num:i(./CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomRxMessageSignalConfig/*[position()=$RxSignalindx]/CanIcomSignalValueLower32bits)"!][!//
[!VAR "TempByte1" = "bit:and($IcomSignalMaskLower32,$SignalMaskByte1)"!][!//
[!VAR "TempByte2" = "bit:and($IcomSignalMaskLower32,$SignalMaskByte2)"!][!//
[!VAR "TempByte3" = "bit:and($IcomSignalMaskLower32,$SignalMaskByte3)"!][!//
[!VAR "TempByte4" = "bit:and($IcomSignalMaskLower32,$SignalMaskByte4)"!][!//
[!VAR "TempByte5" = "bit:and($IcomSignalMaskUpper32,$SignalMaskByte5)"!][!//
[!VAR "TempByte6" = "bit:and($IcomSignalMaskUpper32,$SignalMaskByte6)"!][!//
[!VAR "TempByte7" = "bit:and($IcomSignalMaskUpper32,$SignalMaskByte7)"!][!//
[!VAR "TempByte8" = "bit:and($IcomSignalMaskUpper32,$SignalMaskByte8)"!][!//
[!VAR "Byte2" = "bit:shr($TempByte2,8)"!][!//
[!VAR "Byte3" = "bit:shr($TempByte3,16)"!][!//
[!VAR "Byte4" = "bit:shr($TempByte4,24)"!][!//
[!VAR "Byte5" = "bit:shr($TempByte5,32)"!][!//
[!VAR "Byte6" = "bit:shr($TempByte6,8)"!][!//
[!VAR "Byte7" = "bit:shr($TempByte7,16)"!][!//
[!VAR "Byte8" = "bit:shr($TempByte8,24)"!][!//
  {[!"num:inttohex($TempByte1)"!]U, [!"num:inttohex($Byte2)"!]U, [!"num:inttohex($Byte3)"!]U, [!"num:inttohex($Byte4)"!]U, [!"num:inttohex($TempByte5)"!]U, [!"num:inttohex($Byte6)"!]U, [!"num:inttohex($Byte7)"!]U, [!"num:inttohex($Byte8)"!]U },
[!VAR "TempByte1" = "bit:and($IcomSignalValueLower32,$SignalMaskByte1)"!][!//
[!VAR "TempByte2" = "bit:and($IcomSignalValueLower32,$SignalMaskByte2)"!][!//
[!VAR "TempByte3" = "bit:and($IcomSignalValueLower32,$SignalMaskByte3)"!][!//
[!VAR "TempByte4" = "bit:and($IcomSignalValueLower32,$SignalMaskByte4)"!][!//
[!VAR "TempByte5" = "bit:and($IcomSignalValueUpper32,$SignalMaskByte5)"!][!//
[!VAR "TempByte6" = "bit:and($IcomSignalValueUpper32,$SignalMaskByte6)"!][!//
[!VAR "TempByte7" = "bit:and($IcomSignalValueUpper32,$SignalMaskByte7)"!][!//
[!VAR "TempByte8" = "bit:and($IcomSignalValueUpper32,$SignalMaskByte8)"!][!//
[!VAR "Byte2" = "bit:shr($TempByte2,8)"!][!//
[!VAR "Byte3" = "bit:shr($TempByte3,16)"!][!//
[!VAR "Byte4" = "bit:shr($TempByte4,24)"!][!//
[!VAR "Byte5" = "bit:shr($TempByte5,32)"!][!//
[!VAR "Byte6" = "bit:shr($TempByte6,8)"!][!//
[!VAR "Byte7" = "bit:shr($TempByte7,16)"!][!//
[!VAR "Byte8" = "bit:shr($TempByte8,24)"!][!//
  {[!"num:inttohex($TempByte1)"!]U, [!"num:inttohex($Byte2)"!]U, [!"num:inttohex($Byte3)"!]U, [!"num:inttohex($Byte4)"!]U, [!"num:inttohex($TempByte5)"!]U, [!"num:inttohex($Byte6)"!]U, [!"num:inttohex($Byte7)"!]U, [!"num:inttohex($Byte8)"!]U },
  CAN_17_MCMCAN_ICOM_OPER_[!"./CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomRxMessageSignalConfig/*[position()=$RxSignalindx]/CanIcomSignalOperation "!]
}[!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDLOOP!]

};
[!ENDSELECT!]
[!ENDIF!][!//
[!ENDIF!][!//
/*******************************************************************************
              CAN Kernel configuration parameters
********************************************************************************
     { CAN Global Kernel Address, The status of the nodes in the configured
     kernel }
********************************************************************************
           Note: 1. If any of CAN controllers in the kernel is not activated
                 then, the configuration for that kernel will not be generated.
                 2. CAN controllers that are activated in the kernel will be
                 set to True state and the pending controller nodes shall be
                 set to False state.
*******************************************************************************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
[!VAR "NoOfKernel" = "num:i(count(text:split($CGKernalMap, ',')))"!][!//
[!/* [cover parentID={2AF361D1-ADFF-414a-9237-633FD938CE6C}]
[/cover] */!][!//
static const Can_17_McmCan_McmModuleConfigType \
      Can_17_McmCan_kMcmCanModuleConfig[!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][[!"$NoOfKernel"!]] =
{
[!VAR "Count" = "num:i(0)"!][!//
[!FOR "KerIndex" = "1" TO "$NoOfKernel"!][!//
[!VAR "KerExtract" = "text:split($CGKernalMap, ',')[num:i($KerIndex)]"!][!//
[!VAR "KerName" = "num:i(text:split($KerExtract, 'KERNEL'))"!][!//
[!VAR "BaseRamAddress" = "text:join(concat('Can.MCMCAN',$KerName,'BASERAM'))"!][!//
[!IF "$Count > '0'"!][!//
,

[!ENDIF!][!//
[!VAR "Count" = "num:i($Count+'1')"!][!//
  {
    /* The Global Base address of Kernel module */
    /* MISRA2012_RULE_11_6_JUSTIFICATION: The pointer cast is used to
    cast the generated address with CAN Kernel structure type */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and
    integer type. Permitted for special function registers.*/
    (volatile Ifx_CAN*) [!"num:inttohex(num:hextoint(ecu:get($BaseRamAddress)))"!]U,
    /* The CAN node is enabled or not within the kernel*/
    {
[!VAR "Count1" = "num:i(0)"!][!//
[!FOR "Index" = "0" TO "3"!][!//
[!IF "$Count1 > '0'"!][!//
,
[!ENDIF!][!//
[!VAR "Count1" = "num:i($Count1+'1')"!][!//
[!VAR "KerNodeInfo" = "text:join(concat('NODE',$Index,'_',$KerExtract))"!][!//
      /* Node [!"$Index"!] of kernel enable state */
[!IF "text:contains(text:split($CGConfigNodeKerID,','),$KerNodeInfo)"!][!//
      TRUE[!//
[!ELSE!][!//
      FALSE[!//
[!ENDIF!][!//
[!ENDFOR!][!//

    }
  }[!ENDFOR!][!//

};
[!IF "$TNoOfHth > '0'"!][!//
/*******************************************************************************
              Overall CAN Hth Indexing Configuration
********************************************************************************
     { Hth handle Core assignment, Hth handle logical index (HOH ID),
     Hth handle core specific index}
********************************************************************************
           Note: 1. If there are no Transmit objects configured, this structure
           shall not be generated.
*******************************************************************************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
[!VAR "TotNoOfCont" = "num:i(0)"!][!//
[!VAR "TotNoOfCont" = "num:i(count(text:split($CGConfigResID, ',')))"!][!//
static const Can_17_McmCan_HthIndexType \
  Can_17_McmCan_kMcmCanHthIndexConfig[!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][[!"$TNoOfHth"!]] =
{
[!VAR "Count1" = "num:i(0)"!][!//
[!FOR "HohObjIndx" = "0" TO "$TNoOfHth - '1'"!][!//
[!FOR "CoreTxObjIndx" = "0" TO "$TNoOfHth - '1'"!][!//
[!FOR "LogiIndex" = "0" TO "$TotNoOfCont - '1'"!][!//
[!FOR "CoreIndex" = "0" TO "$MaxCore - '1'"!][!//
[!VAR "CheckIndex" = "text:toupper(concat('HOHHTH',num:i($HohObjIndx+$TNoOfHrh),'_','COREHTH',$CoreTxObjIndx,'_','CON',$LogiIndex,'_','CORE',$CoreIndex))"!][!//
[!IF "text:contains(text:split($HthIndexName,','),$CheckIndex)"!][!//
[!IF "$Count1 > '0'"!][!//
,
[!ENDIF!][!//
[!VAR "Count1" = "num:i($Count1+'1')"!][!//
  {[!//
[!"$CoreIndex"!],[!//
[!"$LogiIndex"!],[!//
[!"$CoreTxObjIndx"!][!//
}[!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDFOR!][!//
[!ENDFOR!][!//
[!ENDFOR!][!//

};
[!ENDIF!][!//
/*******************************************************************************
              Overall CAN Logical Controller Indexing Configuration
********************************************************************************
     { CAN Controller Core assignment, CAN logical indexing indicating the core
       specific indexing,Physical node index and kernel index}
********************************************************************************
           Note:
*******************************************************************************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
[!VAR "TotNoOfCont" = "num:i(0)"!][!//
[!VAR "TotNoOfCont" = "num:i(count(text:split($CGConfigResID, ',')))"!][!//
static const Can_17_McmCan_LogicalControllerIndexType \
  Can_17_McmCan_kMcmCanLogicContIndexConfig[!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][[!"$TotNoOfCont"!]] =
{
[!VAR "Count1" = "num:i(0)"!][!//
[!FOR "LogiIndex" = "0" TO "$TotNoOfCont - '1'"!][!//
[!FOR "CoreIndex" = "0" TO "$MaxCore - '1'"!][!//
[!FOR "KerIndex" = "0" TO "$MaxKernel -'1'"!][!//
[!FOR "NodeIndex" = "0" TO "$MaxController -'1'"!][!//
[!FOR "CoreContIndex" = "0" TO "$TotNoOfCont -'1'"!][!//
[!VAR "CheckIndex" = "text:toupper(concat('CON',$LogiIndex,'_','KERNEL',$KerIndex,'_','CORE',$CoreIndex,'_','CONIND',$CoreContIndex,'_','NODEIND',$NodeIndex))"!][!//
[!IF "text:contains(text:split($ContAllocIndex,','),$CheckIndex)"!][!//
[!IF "$Count1 > '0'"!][!//
,
[!ENDIF!][!//
[!VAR "Count1" = "num:i($Count1+'1')"!][!//
  {[!//
[!"$CoreIndex"!],[!//
[!"$CoreContIndex"!],[!//
[!"$NodeIndex"!],[!//
[!"$KerIndex"!][!//
}[!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDFOR!][!//
[!ENDFOR!][!//
[!ENDFOR!][!//
[!ENDFOR!][!//

};
/******************************************************************************/
        /* Overall Physical CAN Controller Indexing Configuration */
/******************************************************************************/
      /* Physical CAN indexing indicating the Logical controller ID,
         Core specific controller ID and Core assignment.
         This has a constant array size of 12
         i.e.(PhyKernelID * No of Node in kernel)+(PhyNodeID)*/
/******************************************************************************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
static const Can_17_McmCan_PhyControllerIndexType \
  Can_17_McmCan_kMcmCanPhyContIndexConfig[!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][[!"$MaxConfigCont"!]] =
{
[!VAR "ContDetected" = "num:i(0)"!][!//
[!VAR "Count1" = "num:i(0)"!][!//
[!FOR "KerIndex" = "0" TO "$MaxKernel -'1'"!][!//
[!FOR "NodeIndex" = "0" TO "$MaxController -'1'"!][!//
[!FOR "LogiIndex" = "0" TO "$TotNoOfCont - '1'"!][!//
[!FOR "CoreIndex" = "0" TO "$MaxCore - '1'"!][!//
[!FOR "CoreContIndex" = "0" TO "$TotNoOfCont -'1'"!][!//
[!VAR "CheckIndex" = "text:toupper(concat('CON',$LogiIndex,'_','KERNEL',$KerIndex,'_','CORE',$CoreIndex,'_','CONIND',$CoreContIndex,'_','NODEIND',$NodeIndex))"!][!//
[!IF "text:contains(text:split($ContAllocIndex,','),$CheckIndex)"!][!//
[!IF "$Count1 > '0'"!][!//
,
[!ENDIF!][!//
[!VAR "Count1" = "num:i($Count1+'1')"!][!//
[!VAR "ContDetected" = "num:i(1)"!][!//
  {[!//
[!"$LogiIndex"!],[!//
[!"$CoreContIndex"!],[!//
[!"$CoreIndex"!][!//
}[!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDFOR!][!//
[!ENDFOR!][!//
[!IF "$ContDetected = num:i(0)"!]
[!IF "$Count1 > '0'"!][!//
,
[!ENDIF!][!//
[!VAR "Count1" = "num:i($Count1+'1')"!][!//
[!VAR "ContDetected" = "num:i(0)"!][!//
  {[!//
255,[!//
255,[!//
255[!//
}[!//
[!ENDIF!][!//
[!VAR "ContDetected" = "num:i(0)"!][!//
[!ENDFOR!][!//
[!ENDFOR!][!//

};
/******************************************************************************/
                  /* Overall CAN Configuration */
/******************************************************************************/
      /* Over all CAN configurations, structure that points to one of the
           configuration is passed as parameter to Can_Init API */
/******************************************************************************/

[!/* [cover parentID={D1C5F32D-7096-4fc0-8D5D-90CBC614DBB8}]
[/cover] */!][!//
/* MISRA2012_RULE_8_7_JUSTIFICATION: Module configuration data structure
   declaration as per Autosar guidelines. This data structure may be needed
   by SW units using CAN Driver APIs */
/* MISRA2012_RULE_8_4_JUSTIFICATION: Definition is as per Autosar guidelines */
const Can_17_McmCan_ConfigType \
  Can_17_McmCan_Config[!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!] =
{
  /********************* Core specific configuration set **********************/

  /* Pointer to the Core specific CAN configuration set */
  {
[!AUTOSPACING!]
[!INDENT "4"!]
[!IF "$MaxCore > 1"!]
[!FOR "CoreIndx" = "0" TO "$MaxCore - '1'"!][!//
[!VAR "CheckText" = "text:toupper(concat('CORE',$CoreIndx))"!][!//
[!VAR "Text" = "text:join(concat('Core', $CoreIndx))"!][!//
[!IF "text:contains( text:split($CGAllocCore,','), $CheckText )"!][!//
   &Can_17_McmCan_kMcmCanConfig[!"$Text"!][!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][!IF "$CoreIndx != $MaxCore - 1"!],
[!ENDIF!]
[!ELSE!][!//
   NULL_PTR[!IF "$CoreIndx != $MaxCore - 1"!],
[!ENDIF!]
[!ENDIF!]
[!ENDFOR!]

[!ENDIF!][!//
[!ENDINDENT!]
  },

  /****************** Global data shared amongst all cores ********************/

  /* Number of Kernels configured */
[!VAR "NoOfKernel" = "num:i(count(text:split($CGKernalMap, ',')))"!][!//
  [!"$NoOfKernel"!],
  /* Number of Hrh configured */
  [!"$TNoOfHrh"!],
  /* Pointer to CAN Kernel configuration */
  &Can_17_McmCan_kMcmCanModuleConfig[!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][0],
  /* Pointer holding physical controller index data */
  &Can_17_McmCan_kMcmCanPhyContIndexConfig[!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][0],
  /* Pointer holding logical controller index data */
  &Can_17_McmCan_kMcmCanLogicContIndexConfig[!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][0],
  [!IF "$TNoOfHth > '0'"!][!//
  /* Pointer holding configured Hth index data */
  &Can_17_McmCan_kMcmCanHthIndexConfig[!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][0][!IF "$PublicIcomSupport = num:i(1)"!],[!ENDIF!]
  [!ELSE!]
  NULL_PTR[!IF "$PublicIcomSupport = num:i(1)"!],[!ENDIF!]
  [!ENDIF!][!//
  [!IF "$PublicIcomSupport = num:i(1)"!][!//
  /* Pointer to the ICOM configurations set */
  &Can_17_McmCan_kMcmCanIcomConfig[!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][0],
  /* Pointer to the ICOM Rx message configurations */
  &Can_17_McmCan_kMcmCanIcomRxMsgConfig[!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][0][!//
[!IF "$IcomRxMsgSignalCount > 0 "!][!//
,
  /* Pointer to the ICOM Rx message signal configurations */
  &Can_17_McmCan_kMcmCanIcomRxMsgSignalConfig[!IF "$VariantsConfigured = num:i(1)"!]_[!"$PredefinedVarName"!][!ENDIF!][0][!//
[!ENDIF!][!//
  [!ENDIF!][!//

};
[!SELECT "as:modconf('Can')[1]/CanGeneral"!][!//
[!VAR "HwObjMaxIndx" = "num:i(count(./CanMainFunctionRWPeriods/*))"!][!//
[!IF "$HwObjMaxIndx>1"!][!//
[!IF "$MainFunctRxPolling = num:i(1)"!][!//
/*******************************************************************************
        Can_MainFunction_Read() API supported with multiple cycle
*******************************************************************************/
[!FOR "HwObjindx" = "0" TO "$HwObjMaxIndx - 1"!][!//
/* [cover parentID={A2266E18-95A8-4ad5-9E3D-670D9F3BB95F}]
[/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
void Can_17_McmCan_MainFunction_Read_[!"$HwObjindx"!](void)
{
 Can_17_McmCan_lRxPeriodHandler([!"$HwObjindx"!]);
}
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDIF!][!//

[!VAR "HwObjMaxIndx" = "num:i(count(./CanMainFunctionRWPeriods/*))"!][!//
[!IF "$HwObjMaxIndx>1"!][!//
[!IF "$MainFunctTxPolling = num:i(1)"!][!//
/*******************************************************************************
        Can_MainFunction_Write() API supported with multiple cycle
*******************************************************************************/
[!FOR "HwObjindx" = "0" TO "$HwObjMaxIndx - 1"!][!//
/* [cover parentID={809BFB2C-E302-45b1-8B4A-881B00FC5C7E}]
[/cover] */
/* [cover parentID={809BFB2C-E302-45b1-8B4A-881B00FC5C7E}]
[/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
void Can_17_McmCan_MainFunction_Write_[!"$HwObjindx"!](void)
{
 Can_17_McmCan_lTxPeriodHandler([!"$HwObjindx"!]);
 /* [cover parentID={CE488F2F-F189-447d-9D1F-1C6737067BFA}]
 [/cover] */
}

[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
in generated code due to Autosar Naming constraints.*/
#define CAN_17_MCMCAN_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
[/cover] */
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
/*[cover parentID={A4F3B858-B167-4b5c-AB7F-390C5F5D2185}]
[/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Can_17_McmCan_MemMap.h"

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
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/