[!/*******************************************************************************
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
**  FILENAME  : Can_17_McmCan.m                                               **
**                                                                            **
**  VERSION   : 4.0.0                                                         **
**                                                                            **
**  DATE      : 2018-08-24                                                    **
**                                                                            **
**  BSW MODULE DESCRIPTION : Can_17_McmCan.bmd                                **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY :                                                            **
**                                                                            **
**  DESCRIPTION  : Code template macro file for Can Driver                    **
**                                                                            **
**                                                                            **
**                                                                            **
**  SPECIFICATION(S) : Specification of Can Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/!][!//
[!//
[!/* *** multiple inclusion protection *** */!][!//
[!IF "not(var:defined('CAN_17_MCMCAN_M'))"!][!//
[!VAR "CAN_17_MCMCAN_M"="'true'"!][!//
[!//
[!VAR "StdNodeType" = "'STANDARD'"!][!//
[!VAR "ExtNodeType" = "'EXTENDED'"!][!//
[!VAR "EventPolling" = "'POLLING'"!][!//
[!//
[!/*
    MACRO: CAN_CG_ConfigSwitch
    Macro to generate configuration switch Values STD_ON/STD_OFF based on
    configuration true/false
*/!][!//
[!MACRO "CAN_CG_ConfigSwitch", "nodeval" = ""!][!//
[!//
[!IF "$nodeval = 'true'"!][!//
(STD_ON)[!//
[!ELSE!][!//
(STD_OFF)[!//
[!ENDIF!][!//
[!ENDMACRO!][!//
[!/*

*/!][!//
[!/*
    MACRO: CAN_CG_IsEventPolled Macro to get the event notification mechanism
*/!][!//
[!MACRO "CAN_CG_IsEventPolled", "event" = ""!][!//
[!IF "$event = $EventPolling"!][!//
(CAN_17_MCMCAN_POLLING)[!//
[!ELSE!][!//
(CAN_17_MCMCAN_INTERRUPT)[!//
[!ENDIF!][!//
[!ENDMACRO!][!//
[!/*

*/!][!//
[!/*
    MACRO: CAN_CG_GetMasterCoreId Macro to get the master core ID
*/!][!//
[!MACRO "CAN_CG_GetMasterCoreId"!][!//
[!SELECT "as:modconf('ResourceM')[1]"!][!//
[!/* Extract the Master Core ID value */!]
[!VAR "CGMasterCoreId" = "text:join(concat('CORE',substring(node:value(ResourceMMcalConfig/*[1]/ResourceMMasterCore),5,1)))"!][!//
[!ENDSELECT!][!//
[!ENDMACRO!][!//
[!/*

*/!][!//
[!/*
    MACRO: CAN_CG_GetContInCore Macro to get the Numer of controllers in the core
*/!][!//
[!MACRO "CAN_CG_GetContInCore", "CoreName" = ""!][!//
[!VAR "NoOfCont" = "num:i(0)"!][!//
[!VAR "NoOfBaud" = "num:i(0)"!][!//
[!VAR "NoOfFdBaud" = "num:i(0)"!][!//
[!VAR "BaudCount" = "num:i(0)"!][!//
[!VAR "FdBaudCount" = "num:i(0)"!][!//
[!VAR "ContCnt" = "num:i(count(./CanController/*))"!][!//
[!VAR "CoreCnt" = "num:i(count(text:split($CGAllocCore, ',')))"!][!//
[!FOR "ContIndex" = "0" TO "$ContCnt -'1'"!][!//
[!VAR "CoreContName" = "text:join(concat('CON',$ContIndex,'_',$CoreName))"!][!//
[!IF "text:contains( text:split($CGResCoreMap,','), $CoreContName )"!][!//
[!VAR "NoOfCont" = "num:i($NoOfCont +1)"!][!//
[!VAR "ContPosIndex" = "num:i($ContIndex +1)"!][!//
[!VAR "BaudCount" = "num:i(count(./CanController/*[position()=$ContPosIndex]/CanControllerBaudrateConfig/*))"!][!//
[!VAR "FdBaudCount" = "num:i(count(./CanController/*[position()=$ContPosIndex]/CanControllerBaudrateConfig/*/CanControllerFdBaudrateConfig/*))"!][!//
[!VAR "NoOfBaud" = "num:i($NoOfBaud + $BaudCount)"!][!//
[!VAR "NoOfFdBaud" = "num:i($NoOfFdBaud + $FdBaudCount)"!][!//
[!ENDIF!][!//
[!ENDFOR!][!//
[!ENDMACRO!][!//
[!/*

*/!][!//
[!/*****************************************************************************
** Name             : CG_GenerateModuleMap                                    **
**                                                                            **
** Description      : Macro to generate core-channel mappings for a module    **
**                                                                            **
********************************************************************************/!][!//
[!MACRO "CAN_CG_GenerateModuleMap", "Module" = ""!][!//
[!NOCODE!][!//
[!VAR "Indx" = "num:i(0)"!][!//
[!VAR "CGKernalMap" = "''"!][!//
[!VAR "CGUnAllocRes" = "''"!][!//
[!VAR "CGMasterAlloc" = "num:i(0)"!][!//
[!VAR "CGUnAllocResKerName" = "''"!][!//
[!VAR "CGUnAllocResName" = "''"!][!//
[!VAR "CGUnAllocKerName" = "''"!][!//
[!VAR "CGAllocCore" = "''"!][!//
[!VAR "CGResourceAlloc" = "''"!][!//
[!VAR "CGCoreMap" = "''"!][!//
[!VAR "CGResCoreMap" = "''"!][!//
[!CALL "CAN_CG_GetMasterCoreId"!][!//
[!SELECT "as:modconf('ResourceM')[1]"!][!//
  [!/* Loop through resource manager core allocations */!]
  [!LOOP "ResourceMMcalConfig/*[1]/ResourceMMcalCore/*"!][!//
    [!/* Retrieve current Core ID */!][!//
    [!VAR "CGCoreID" = "./ResourceMCoreID"!][!//
    [!/* Loop through resources allocated */!][!//
    [!LOOP "ResourceMAllocation/*"!][!//
      [!/* Check if resource allocated matches with the module in concern */!]
      [!IF "'CAN' = ./ResourceMModuleName"!][!//
        [!/* Check if resource reference is valid */!]
        [!IF "node:refvalid(./ResourceMResourceRef)"!][!//
          [!/* Extract the number of / in the reference */!]
          [!VAR "index" = "num:i(count(text:split(./ResourceMResourceRef, '/')))"!][!//
          [!/* Get the controller base address for the resource reffered */!][!//
          [!VAR "ControllerAdress"= "num:i(node:ref(./ResourceMResourceRef)/CanControllerBaseAddress)"!][!//
          [!/* Check controller is assigned to which kernel */!][!//
          [!FOR "KerIndx" = "0" TO "$MaxKernel - '1'"!][!//
            [!VAR "CGKernelID" = "text:join(concat('KERNEL',$KerIndx))"!]
            [!FOR "CtrlIndx" = "0" TO "$MaxController - '1'"!][!//
              [!VAR "NodeName" = "text:join(concat('Can.Node',$KerIndx,$CtrlIndx,'BaseAddress'))"!][!//
              [!VAR "CGResourceID" = "text:join(concat('CON',num:i(node:ref(./ResourceMResourceRef)/CanControllerId)))"!][!//
              [!IF "$ControllerAdress = num:hextoint(ecu:get($NodeName))"!][!//
                [!IF "$CGMasterCoreId = $CGCoreID"!][!//
                [!VAR "CGMasterAlloc" = "num:i(1)"!][!//
                [!ENDIF!][!//
                [!IF "not(text:contains( text:split($CGKernalMap,','), $CGKernelID ))"!][!//
                  [!VAR "CGCoreKernel" = "text:join(concat($CGKernelID,'_',$CGCoreID))"!]
                  [!VAR "CGKernalMap" = "text:join(concat($CGKernalMap,$CGKernelID,','))"!][!//
                [!ENDIF!][!//
                [!VAR "CGResourceAlloc" = "text:join(concat($CGResourceAlloc,$CGResourceID,'_',$CGKernelID,','))"!][!//
                [!VAR "CGCoreMap" = "text:toupper(concat($CGCoreMap, $CGResourceID, '_',$CGKernelID ,'_', $CGCoreID, ','))"!][!//
                [!VAR "CGResCoreMap" = "text:toupper(concat($CGResCoreMap, $CGResourceID, '_',$CGCoreID, ','))"!][!//
                [!IF "not(text:contains( text:split($CGAllocCore,','), $CGCoreID ))"!][!//
                  [!VAR "CGAllocCore" = "text:toupper(concat($CGAllocCore,$CGCoreID, ','))"!][!//
                [!ENDIF!][!//
              [!ENDIF!][!//
            [!ENDFOR!][!//
          [!ENDFOR!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ENDLOOP!][!//
  [!VAR "CGUnAllocRes" = "text:join(text:difference(text:split($CGConfigResKerID,','),text:split($CGResourceAlloc,',')),',')"!][!//
  [!IF "not($CGUnAllocRes = '')"!][!//
    [!VAR "index" = "num:i(count(text:split($CGUnAllocRes, ',')))"!][!//
    [!VAR "CGMasterAlloc" = "num:i(1)"!][!//
    [!FOR "Indx" = "1" TO "$index"!][!//
      [!VAR "CGUnAllocResKerName" = "text:split($CGUnAllocRes, ',')[num:i($Indx)]"!][!//
      [!VAR "CGUnAllocResName" = "text:split($CGUnAllocResKerName, '_')[num:i(1)]"!][!//
      [!VAR "CGUnAllocKerName" = "text:split($CGUnAllocResKerName, '_')[num:i(2)]"!][!//
      [!IF "not(text:contains( text:split($CGKernalMap,','), $CGUnAllocKerName ))"!][!//
        [!VAR "CGKernalMap" = "text:toupper(concat($CGKernalMap,$CGUnAllocKerName,','))"!][!//
      [!ENDIF!][!//
      [!VAR "CGResourceAlloc" = "text:join(concat($CGResourceAlloc,$CGUnAllocResName,'_',$CGUnAllocKerName,','))"!][!//
      [!VAR "CGCoreMap" = "text:toupper(concat($CGCoreMap,$CGUnAllocResName,'_',$CGUnAllocKerName,'_',$CGMasterCoreId,','))"!][!//
      [!VAR "CGResCoreMap" = "text:toupper(concat($CGResCoreMap,$CGUnAllocResName,'_',$CGMasterCoreId,','))"!][!//
      [!IF "not(text:contains( text:split($CGAllocCore,','), $CGMasterCoreId ))"!][!//
        [!VAR "CGAllocCore" = "text:toupper(concat($CGAllocCore,$CGMasterCoreId, ','))"!][!//
      [!ENDIF!][!//
    [!ENDFOR!][!//
  [!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!/*

*/!][!//
[!/*
     Macro that takes care of activated controller allocations
*/!][!//
[!MACRO "CAN_CG_ControllerAllocation"!][!//
[!NOCODE!][!//
[!VAR "MaxKernel" = "num:i(ecu:get('Can.MaxKernels'))"!][!//
[!VAR "MaxController" = "num:i(ecu:get('Can.MaxCtrlKer'))"!][!//
[!VAR "MaxConfigCont"= "num:i(ecu:get('Can.MaxControllers'))"!][!//
[!VAR "MaxCore" = "num:i(ecu:get('Mcu.NoOfCoreAvailable'))"!][!//
[!VAR "CGResourceID" = "num:i(0)"!][!//
[!VAR "CGNodeID" = "num:i(0)"!][!//
[!VAR "ControllerFound" = "num:i(0)"!][!//
[!VAR "CGConfigKernelID" = "''"!][!//
[!VAR "CGKernelID" = "''"!][!//
[!VAR "CGConfigResKerID" = "''"!][!//
[!VAR "CGConfigNodeKerID" = "''"!][!//
[!VAR "CGConfigConNodeKerID" = "''"!][!//
[!VAR "CGConfigResID" = "''"!][!//
[!VAR "BaseAddress" = "num:i(0)"!][!//
[!VAR "ContCount" = "num:i(0)"!][!//
[!VAR "ContIdPrev" = "num:i(0)"!][!//
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Can')[1]/CanConfigSet"!][!//
[!/* Set loop for read the configured controller and corresponding MCMCAN kernel information*/!]
[!LOOP "./CanController/*"!][!//
  [!VAR "ContCount" = "num:i($ContCount +1)"!][!//
  [!VAR "ControllerBRConfigTemp" = "num:i(count(../*[position()=$ContCount]/CanControllerBaudrateConfig/*))"!][!//
  [!FOR "BaudrateIndx" = "1" TO "$ControllerBRConfigTemp"!][!//
      [!IF "(node:exists(../*[position()=$ContCount]/CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*))"!][!//
        [!VAR "FDNodesPresent" = "num:i(1)"!][!//
      [!ENDIF!][!//
  [!ENDFOR!][!//
  [!IF "CanControllerActivation = 'true'"!][!//
    [!IF "$ContIdPrev <= num:i(CanControllerId)"!][!//
      [!VAR "ContIdPrev" = "num:i(CanControllerId)"!][!//
      [!VAR "ControllerFound" = "num:i(0)"!][!//
      [!VAR "BaseAddress" = "num:i(CanControllerBaseAddress)"!][!//
      [!FOR "KerIndx" = "0" TO "$MaxKernel - '1'"!][!//
        [!VAR "CGKernelID" = "text:join(concat('KERNEL',$KerIndx))"!]
        [!FOR "CtrlIndx" = "0" TO "$MaxController - '1'"!][!//
          [!/* Get node base address name */!]
          [!VAR "NodeName" = "text:join(concat('Can.Node',$KerIndx,$CtrlIndx,'BaseAddress'))"!][!//
          [!/* Retrive base address for the node and compare with base address available */!]
          [!IF "$BaseAddress = num:hextoint(ecu:get($NodeName))"!][!//
            [!VAR "ControllerFound" = "num:i(1)"!][!//
            [!VAR "CGResourceID" = "text:join(concat('CON',num:i(CanControllerId)))"!][!//
            [!VAR "CGNodeID" = "text:join(concat('NODE',$CtrlIndx))"!][!//
            [!VAR "CGConfigResID" = "text:join(concat($CGConfigResID,$CGResourceID,','))"!][!//
            [!VAR "CGConfigResKerID" = "text:join(concat($CGConfigResKerID,$CGResourceID,'_',$CGKernelID,','))"!][!//
            [!VAR "CGConfigNodeKerID" = "text:join(concat($CGConfigNodeKerID,$CGNodeID,'_',$CGKernelID,','))"!][!//
            [!VAR "CGConfigConNodeKerID" = "text:join(concat($CGConfigConNodeKerID,$CGResourceID,'_',$CGNodeID,'_',$CGKernelID,','))"!][!//
            [!IF "not(text:contains(text:split($CGConfigKernelID,','),$CGKernelID))"!][!//
              [!VAR "CGConfigKernelID" = "text:toupper(concat($CGConfigKernelID,$CGKernelID,','))"!][!//
            [!ENDIF!]
          [!ENDIF!][!//
        [!ENDFOR!][!//
      [!ENDFOR!][!//
      [!IF "$ControllerFound = '0'"!]
        [!ERROR!][!//
          The Base address configured for CancontrollerId [!"CanControllerId"!] is wrong.
        [!ENDERROR!][!//
      [!ENDIF!][!//
    [!ELSE!]
      [!ERROR!][!//
        The CancontrollerId's need to be positioned in ascending order in the list.
      [!ENDERROR!][!//  
    [!ENDIF!]
  [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!//
[!ENDIF!]
