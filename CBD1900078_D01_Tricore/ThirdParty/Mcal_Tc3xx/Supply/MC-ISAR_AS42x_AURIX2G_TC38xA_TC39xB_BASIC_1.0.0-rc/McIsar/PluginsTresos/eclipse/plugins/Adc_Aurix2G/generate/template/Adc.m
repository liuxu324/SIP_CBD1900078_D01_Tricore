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
**  FILENAME  : Adc.m                                                         **
**                                                                            **
**  VERSION   : 4.0.0                                                         **
**                                                                            **
**  DATE      : 2018-03-28                                                    **
**                                                                            **
**  BSW MODULE DESCRIPTION : Adc.bmd                                          **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={CE6EE5FD-EB8B-44b3-B1D2-F4476C1AD69F}]    **
**                                                                            **
**  DESCRIPTION  : Code template macro file for ADC Driver                    **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of ADC Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
*/!]

[!/* *** multiple inclusion protection*** */!][!//
[!IF "not(var:defined('ADC_M'))"!][!//
[!VAR "ADC_M"="'true'"!][!//
[!AUTOSPACING!]

/*******************************************************************************
** Name             : Adc_ConfigGlobalCfgVal                                  **
**                                                                            **
** Description      : This macro generates the value to be configured in      **
**                    the GLOBCFG register                                    **
**                                                                            **
*******************************************************************************/
[!MACRO "Adc_ConfigGlobalCfgVal",
         "SyncClockDisable"= "","SupplyVoltage"="","AdcGlobCfgVal"=""!][!//
[!NOCODE!]
[!VAR "AdcGlobCfgVal" = "num:i(0)"!]

[!IF "$SupplyVoltage = 'ADC_VOLTAGE_5V'"!]
  [!VAR "AdcGlobCfgVal" = "bit:or($AdcGlobCfgVal, bit:shl(1,13))"!]
[!ELSEIF "$SupplyVoltage = 'ADC_VOLTAGE_3P3V'"!]
  [!VAR "AdcGlobCfgVal" = "bit:or($AdcGlobCfgVal, bit:shl(2,13))"!]
[!ENDIF!]

[!IF "$SyncClockDisable = 'true'"!]
  [!VAR "AdcGlobCfgVal" = "bit:or($AdcGlobCfgVal, bit:shl(1,12))"!]
[!ENDIF!]

[!ENDNOCODE!][!//
[!ENDMACRO!][!//


/*******************************************************************************
** Name             : Adc_ConfigIClassVal                                     **
**                                                                            **
** Description      : This macro generates the value to be configured in the  **
**                    GLOBICLASS0/1 or GxICLASS0/1 register                   **
**                                                                            **
*******************************************************************************/
[!MACRO "Adc_ConfigIClassVal","ChSampleTime" ="","ChPreChargeClkCycles"= "",
"ChConvMode"="","ChSESPSEnable"="", "AdcChClassVal"=""!][!//
[!NOCODE!]
[!VAR "AdcChClassVal" = "num:i($ChSampleTime)"!]
[!IF "$ChSESPSEnable = 'true'"!]
  [!VAR "AdcChClassVal" = "bit:or($AdcChClassVal, bit:shl(1,10))"!]
[!ENDIF!]

[!IF "$ChPreChargeClkCycles = 'ADC_INPUT_PRECHARGE_CYCLES_32'"!]
  [!VAR "AdcChClassVal" = "bit:or($AdcChClassVal, bit:shl(3,6))"!]
[!ELSEIF "$ChPreChargeClkCycles = 'ADC_INPUT_PRECHARGE_CYCLES_16'"!]
  [!VAR "AdcChClassVal" = "bit:or($AdcChClassVal, bit:shl(2,6))"!]
[!ELSEIF "$ChPreChargeClkCycles = 'ADC_INPUT_PRECHARGE_CYCLES_8'"!]
  [!VAR "AdcChClassVal" = "bit:or($AdcChClassVal, bit:shl(1,6))"!]
[!ENDIF!]

[!IF "$ChConvMode = 'ADC_NOISE_REDUCTION_STEPS_7'"!]
  [!VAR "AdcChClassVal" = "bit:or($AdcChClassVal, bit:shl(3,8))"!]
[!ELSEIF "$ChConvMode = 'ADC_NOISE_REDUCTION_STEPS_3'"!]
  [!VAR "AdcChClassVal" = "bit:or($AdcChClassVal, bit:shl(2,8))"!]
[!ELSEIF "$ChConvMode = 'ADC_NOISE_REDUCTION_STEPS_1'"!]
  [!VAR "AdcChClassVal" = "bit:or($AdcChClassVal, bit:shl(1,8))"!]
[!ENDIF!]

[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Adc_ConfigAnCfgVal                                      **
**                                                                            **
** Description      : This macro generates the value to be configured in      **
**                    GxANCFG register                                        **
*******************************************************************************/
[!MACRO "Adc_ConfigAnCfgVal","IdlePrechargeEnable" ="","InputBufferEnable"= "",
"PrechargeReference"="","ReferencePrechargePhases"="", "CalibrationSampleTime"="",
"PostCalibrationDisable"="", "AnalogClockSyncDelay"="", "SampleSyncEnable"="",
"Prescale"="", "MSBDoubleClkEnable"="","AdcAnCfgVal"=""!][!//
[!NOCODE!]
[!VAR "AdcAnCfgVal" = "num:i(0)"!]

[!IF "$IdlePrechargeEnable = 'true'"!]
  [!VAR "AdcAnCfgVal" = "bit:or($AdcAnCfgVal,1)"!]
[!ENDIF!]

[!IF "$InputBufferEnable = 'true'"!]
  [!VAR "AdcAnCfgVal" = "bit:or($AdcAnCfgVal,bit:shl(1,1))"!]
[!ENDIF!]

[!IF "$PrechargeReference = 'ADC_VDD_VSM_USED'"!]
  [!VAR "AdcAnCfgVal" = "bit:or($AdcAnCfgVal,bit:shl(1,2))"!]
[!ENDIF!]

[!IF "$ReferencePrechargePhases = 'ADC_PRECHARGE_PHASE_2'"!]
  [!VAR "AdcAnCfgVal" = "bit:or($AdcAnCfgVal,bit:shl(1,3))"!]
[!ENDIF!]

[!IF "$CalibrationSampleTime = 'ADC_CAL_TIME_4_TIMES_TADCI'"!]
  [!VAR "AdcAnCfgVal" = "bit:or($AdcAnCfgVal, bit:shl(1,4))"!]
[!ELSEIF "$CalibrationSampleTime = 'ADC_CAL_TIME_6_TIMES_TADCI'"!]
  [!VAR "AdcAnCfgVal" = "bit:or($AdcAnCfgVal, bit:shl(2,4))"!]
[!ELSEIF "$CalibrationSampleTime = 'ADC_CAL_TIME_8_TIMES_TADCI'"!]
  [!VAR "AdcAnCfgVal" = "bit:or($AdcAnCfgVal, bit:shl(3,4))"!]
[!ENDIF!]

[!IF "$PostCalibrationDisable = 'true'"!]
  [!VAR "AdcAnCfgVal" = "bit:or($AdcAnCfgVal,bit:shl(1,6))"!]
[!ENDIF!]

[!VAR "AdcAnCfgVal" = "bit:or($AdcAnCfgVal,bit:shl(num:i($AnalogClockSyncDelay),16))"!]

[!IF "$SampleSyncEnable = 'true'"!]
  [!VAR "AdcAnCfgVal" = "bit:or($AdcAnCfgVal,bit:shl(1,19))"!]
[!ENDIF!]

[!VAR "AdcAnCfgVal" = "bit:or($AdcAnCfgVal,bit:shl(num:i($Prescale - 1),20))"!]

[!IF "$MSBDoubleClkEnable = 'true'"!]
  [!VAR "AdcAnCfgVal" = "bit:or($AdcAnCfgVal,bit:shl(1,25))"!]
[!ENDIF!]

[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Adc_ConfigArbPrioVal                                    **
**                                                                            **
** Description      : This macro generates the value to be configured in      **
**                    GxARBPRIO register                                      **
*******************************************************************************/
[!MACRO "Adc_ConfigArbPrioVal",
"RequestSource0ConvMode"= "","RequestSource1ConvMode"= "","RequestSource2ConvMode"= "","PrioImplementation"="",
"AdcArbPrioVal"=""!][!//
[!NOCODE!][!//

[!VAR "AdcArbPrioVal" = "num:i(0)"!]

[!IF "$PrioImplementation = 'ADC_PRIORITY_NONE'"!]
  [!VAR "AdcArbPrioVal" = "bit:or($AdcArbPrioVal,bit:shl(1,24))"!]
[!ELSE!]
  [!IF "$RequestSource0ConvMode = 'ADC_CANCEL_INJECT_REPEAT_MODE'"!]
    [!VAR "AdcArbPrioVal" = "bit:or($AdcArbPrioVal,bit:shl(1,3))"!]
  [!ENDIF!]
  [!IF "$RequestSource1ConvMode = 'ADC_CANCEL_INJECT_REPEAT_MODE'"!]
    [!VAR "AdcArbPrioVal" = "bit:or($AdcArbPrioVal,bit:shl(1,7))"!]
  [!ENDIF!]
  [!IF "$RequestSource2ConvMode = 'ADC_CANCEL_INJECT_REPEAT_MODE'"!]
    [!VAR "AdcArbPrioVal" = "bit:or($AdcArbPrioVal,bit:shl(1,11))"!]
  [!ENDIF!]

  [!VAR "AdcArbPrioVal" = "bit:or($AdcArbPrioVal,bit:shl(7,24))"!]
  [!VAR "AdcArbPrioVal" = "bit:or($AdcArbPrioVal, bit:shl(num:i(0),0))"!]
  [!VAR "AdcArbPrioVal" = "bit:or($AdcArbPrioVal, bit:shl(num:i(1),4))"!]
  [!VAR "AdcArbPrioVal" = "bit:or($AdcArbPrioVal, bit:shl(num:i(2),8))"!]
[!ENDIF!]

[!ENDNOCODE!][!//
[!ENDMACRO!][!//


/*******************************************************************************
** Name             : Adc_ConfigChctrVal                                      **
**                                                                            **
** Description      : This macro generates the value to be configured in      **
**                    GxCHCTR register                                        **
*******************************************************************************/
[!MACRO "Adc_ConfigChctrVal","InputClassSelection" ="",
"ChannelRangeSelect"= "","ChLimitChk"= "","ChSyncConv"= "","ChannelRefVoltsrcHigh"="",
"ResultAlignment"="","AdcChctrVal"=""!][!//
[!NOCODE!][!//

[!IF "$InputClassSelection = 'ADC_GLOBAL_CLASS_1'"!]
  [!VAR "AdcChctrVal"="num:i(3)"!]
[!ELSEIF "$InputClassSelection = 'ADC_GLOBAL_CLASS_0'"!]
  [!VAR "AdcChctrVal"="num:i(2)"!]
[!ELSEIF "$InputClassSelection = 'ADC_HWUNIT_CLASS_1'"!]
  [!VAR "AdcChctrVal"="num:i(1)"!]
[!ELSE!]
  [!VAR "AdcChctrVal"="num:i(0)"!]
[!ENDIF!]

[!IF "$ChLimitChk = num:i(1)"!]
[!/* [cover parentID={10E9C966-15D6-40c9-B05E-C1B8253F7135}]Channel limitcheck is enabled[/cover] */!][!//
  [!VAR "AdcChctrVal"="bit:or($AdcChctrVal, bit:shl(1,6))"!]
[!/* [cover parentID={67E75697-0DE0-4641-9080-E333D0947014}]Channel Range Selection configuration bit extraction[/cover] */!][!//
  [!IF "($ChannelRangeSelect = 'ADC_RANGE_BETWEEN') or ($ChannelRangeSelect = 'ADC_RANGE_NOT_OVER_HIGH') or ($ChannelRangeSelect = 'ADC_RANGE_NOT_UNDER_LOW')"!]
    [!VAR "AdcChctrVal"="bit:or($AdcChctrVal, bit:shl(1,8))"!]
  [!ELSEIF "($ChannelRangeSelect = 'ADC_RANGE_NOT_BETWEEN') or ($ChannelRangeSelect = 'ADC_RANGE_UNDER_LOW') or ($ChannelRangeSelect = 'ADC_RANGE_OVER_HIGH')"!]
    [!VAR "AdcChctrVal"="bit:or($AdcChctrVal, bit:shl(2,8))"!]
  [!ELSE!]
    [!VAR "AdcChctrVal"="bit:or($AdcChctrVal, bit:shl(3,8))"!]
  [!ENDIF!]
[!ENDIF!]

[!IF "$ChSyncConv = num:i(1)"!]
  [!VAR "AdcChctrVal"="bit:or($AdcChctrVal, bit:shl(1,10))"!]
[!ENDIF!]

[!IF "$ChannelRefVoltsrcHigh = 'ADC_USES_CH0'"!]
  [!VAR "AdcChctrVal"="bit:or($AdcChctrVal, bit:shl(1,11))"!]
[!ENDIF!]
[!/* [cover parentID={B255D054-507E-4f84-B5D0-83E60A6DC5B3}]Result Alignment configuration bit exraction[/cover] */!][!//
[!IF "$ResultAlignment = 'ADC_ALIGN_LEFT'"!]
  [!VAR "AdcChctrVal"="bit:or($AdcChctrVal, bit:shl(1,21))"!]
[!ENDIF!]

[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Adc_ConfigBoundVal                                      **
**                                                                            **
** Description      : This macro generates the value to be configured in      **
**                    GxBOUND register                                        **
*******************************************************************************/
[!MACRO "Adc_ConfigBoundVal","ChannelRangeSelect"= "","ChannelHighLimit" ="",
"ChannelLowLimit"= "","AdcBoundVal"=""!][!//
[!NOCODE!][!//
[!/* [cover parentID={456AE855-2BFA-42a7-B771-2504100A9014}]Generate the boundary values based on the High Limit, Low Limit and range selection criteria[/cover] */!][!//
[!IF "$ChannelRangeSelect = 'ADC_RANGE_ALWAYS'"!]
  [!VAR "AdcBoundVal"="num:i(0)"!]
[!ELSEIF "$ChannelRangeSelect = 'ADC_RANGE_BETWEEN'"!]
  [!VAR "AdcBoundVal"="num:i($ChannelLowLimit+1)"!]
  [!VAR "AdcBoundVal"="bit:or($AdcBoundVal, bit:shl($ChannelHighLimit,16))"!]
[!ELSEIF "$ChannelRangeSelect = 'ADC_RANGE_NOT_BETWEEN'"!]
  [!VAR "AdcBoundVal"="num:i($ChannelLowLimit+1)"!]
  [!VAR "AdcBoundVal"="bit:or($AdcBoundVal, bit:shl($ChannelHighLimit,16))"!]
[!ELSEIF "$ChannelRangeSelect = 'ADC_RANGE_NOT_OVER_HIGH'"!]
  [!VAR "AdcBoundVal"="num:i(0)"!]
  [!VAR "AdcBoundVal"="bit:or($AdcBoundVal, bit:shl($ChannelHighLimit,16))"!]
[!ELSEIF "$ChannelRangeSelect = 'ADC_RANGE_NOT_UNDER_LOW'"!]
  [!VAR "AdcBoundVal"="num:i($ChannelLowLimit+1)"!]
  [!VAR "AdcBoundVal"="bit:or($AdcBoundVal, bit:shl(4095,16))"!]
[!ELSEIF "$ChannelRangeSelect = 'ADC_RANGE_OVER_HIGH'"!]
  [!VAR "AdcBoundVal"="num:i(0)"!]
  [!VAR "AdcBoundVal"="bit:or($AdcBoundVal, bit:shl($ChannelHighLimit,16))"!]
[!ELSEIF "$ChannelRangeSelect = 'ADC_RANGE_UNDER_LOW'"!]
  [!VAR "AdcBoundVal"="num:i($ChannelLowLimit+1)"!]
  [!VAR "AdcBoundVal"="bit:or($AdcBoundVal, bit:shl(4095,16))"!]
[!ENDIF!]

[!ENDNOCODE!][!//
[!ENDMACRO!][!//


/*******************************************************************************
** Name             : Adc_ConfigGroupQModeVal                                 **
**                                                                            **
** Description      : This macro generates the value to be configured in      **
**                    GxQMRy  register                                        **
*******************************************************************************/
[!MACRO "Adc_ConfigGroupQModeVal","GroupTriggSrc"= "","HwTrigSignal" ="",
"HwExtTrigSelect"= "","HwExtGateSelect"= "","HwGateSignal"= "","ReqTimerVal"="",
"AdcGroupQModeVal"=""!][!//
[!NOCODE!][!//
[!VAR "AdcGroupQModeVal" = "num:i(0)"!]

[!IF "$GroupTriggSrc = 'ADC_TRIGG_SRC_SW'"!]
  [!VAR "AdcGroupQModeVal" = "num:i(1)"!]
[!ELSE!]
  [!IF "$HwExtTrigSelect != 'ADC_TRIG_NONE' or $ReqTimerVal != num:i(0)"!]
    [!VAR "AdcGroupQModeVal"="bit:or($AdcGroupQModeVal, bit:shl(1,2))"!]
  [!ENDIF!]
  [!IF "$HwExtGateSelect = 'ADC_GATE_NONE' or $HwExtTrigSelect = 'ADC_TRIG_15_GxREQTRP_GxREQGTySEL'"!][!// IF triggered via gate then trigger should not be GATED. Case of Thru gate
    [!VAR "AdcGroupQModeVal"="bit:or($AdcGroupQModeVal,1)"!]
  [!ELSEIF "contains($HwExtGateSelect,'ERUPDOUT')"!][!//
    [!VAR "AdcGroupQModeVal"="bit:or($AdcGroupQModeVal,2)"!]
  [!ELSEIF "$HwGateSignal = 'ADC_GATE_LVL_HIGH'"!]
    [!VAR "AdcGroupQModeVal"="bit:or($AdcGroupQModeVal,2)"!]
  [!ELSE!]
    [!VAR "AdcGroupQModeVal"="bit:or($AdcGroupQModeVal,3)"!]
  [!ENDIF!]
[!ENDIF!]

[!ENDNOCODE!][!//
[!ENDMACRO!][!//
/*******************************************************************************
** Name             : Adc_ConfigGroupQCtrlVal                                 **
**                                                                            **
** Description      : This macro generates the value to be configured in      **
**                    GxQMRy  register                                        **
*******************************************************************************/
[!MACRO "Adc_ConfigGroupQCtrlVal","GroupTriggSrc"= "","HwTrigSignal" ="",[!//
"HwExtTrigSelect"= "","HwExtGateSelect"= "","HwGateSignal"= "","ReqTimerVal"= "","AdcGroupQCtrlVal"=""!][!//
[!NOCODE!][!//
[!VAR "AdcGroupQCtrlVal" = "num:i(0)"!]
[!IF "$ReqTimerVal != num:i(0)"!]
  [!VAR "AdcGroupQCtrlVal" = "bit:shl(1,28)"!]
[!ELSE!]
  [!IF "$GroupTriggSrc = 'ADC_TRIGG_SRC_HW'"!]
    [!IF "$HwExtTrigSelect != 'ADC_TRIG_NONE'"!]
      [!VAR "AdcGroupQCtrlVal" = "text:split($HwExtTrigSelect,'_')[3]"!]
      [!VAR "AdcGroupQCtrlVal" = "bit:shl($AdcGroupQCtrlVal,8)"!]
      [!IF "contains($HwExtTrigSelect,'ERUIOUT')"!]
        [!VAR "AdcGroupQCtrlVal" = "bit:or($AdcGroupQCtrlVal,bit:shl(2,13))"!][!// Only trigger pulse come from ERU hence only rising edge is configured, actual edge is set in ERU EICR reg.
      [!ELSE!]
        [!IF "$HwTrigSignal = 'ADC_HW_TRIG_FALLING_EDGE'"!]
          [!VAR "AdcGroupQCtrlVal" = "bit:or($AdcGroupQCtrlVal,bit:shl(1,13))"!]
        [!ELSEIF "$HwTrigSignal = 'ADC_HW_TRIG_RISING_EDGE'"!]
          [!VAR "AdcGroupQCtrlVal" = "bit:or($AdcGroupQCtrlVal,bit:shl(2,13))"!]
        [!ELSE!]
          [!VAR "AdcGroupQCtrlVal" = "bit:or($AdcGroupQCtrlVal,bit:shl(3,13))"!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
    [!IF "$HwExtGateSelect != 'ADC_GATE_NONE'"!]
      [!VAR "AdcGroupQCtrlVal" = "bit:or($AdcGroupQCtrlVal,bit:shl(text:split($HwExtGateSelect,'_')[3],16))"!]
    [!ENDIF!]
  [!ENDIF!]
[!ENDIF!]
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Adc_GenerateModuleMap                                   **
**                                                                            **
** Description      : Macro to generate core-channel mappings for a module    **
**                                                                            **
*******************************************************************************/
[!MACRO "Adc_GenerateModuleMap", "Module" = ""!][!//
[!NOCODE!][!//
[!SELECT "as:modconf('ResourceM')[1]"!][!//
  [!VAR "CGMasterCoreId" = "substring(node:value(ResourceMMcalConfig/*[1]/ResourceMMasterCore),5,1)"!][!//
    [!LOOP "ResourceMMcalConfig/*[1]/ResourceMMcalCore/*"!][!//
      [!VAR "CGCoreID" = "./ResourceMCoreID"!][!//
      [!LOOP "ResourceMAllocation/*"!][!//
        [!IF "$Module = ./ResourceMModuleName"!][!//
          [!/* TBD: Check needs to be added to check if ResourceMResourceRef exists */!]
          [!VAR "index" = "num:i(count(text:split(./ResourceMResourceRef, '/')))"!][!//
          [!VAR "ResourceName" = "text:split(./ResourceMResourceRef, '/')[num:i($index)]"!][!//
          [!VAR "CGModuleMap" = "concat($CGModuleMap, $CGCoreID, '_', $ResourceName, ',')"!][!//
          [!VAR "CGAllocatedResources" = "concat($CGAllocatedResources, $ResourceName, ',')"!][!//
          [!IF "not(contains(text:split($CGCoreUsed), $CGCoreID))"!][!//
            [!VAR "CGCoreUsed" = "concat($CGCoreUsed, $CGCoreID, ',')"!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDLOOP!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!/* If no resource is allocated to master core, add master core to CGCoreUsed as dummy core */!][!//
[!VAR "pattern" = "concat('CORE', $CGMasterCoreId)"!][!//
[!IF "not(contains(text:split($CGCoreUsed),$pattern))"!][!//
  [!VAR "CGCoreUsed" = "concat($CGCoreUsed, $pattern, ',')"!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Adc_GetHwUnitCoreId                                     **
**                                                                            **
** Description      : Macro to get the CoreId, an HwUnit is assigned to       **
**                                                                            **
*******************************************************************************/
[!MACRO "Adc_GetHwUnitCoreId", "ModuleMap" = "", "Item"=""!][!//
[!NOCODE!][!//
[!VAR "HwUnitCoreId"="num:i(-1)"!][!//
[!FOR "CoreIndex" = "num:i(1)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable'))"!][!//
  [!VAR "corePattern" = "concat( 'CORE', num:i($CoreIndex - 1) )"!][!//
  [!VAR "matchPattern" = "concat( '^.*(', $corePattern, '_', $Item, ',' ,').*$' )"!][!//
  [!IF "text:match($ModuleMap, $matchPattern)"!][!//
    [!VAR "HwUnitCoreId"="num:i($CoreIndex - 1)"!][!//
  [!ENDIF!][!//
[!ENDFOR!][!//
[!IF "num:i($HwUnitCoreId) = num:i(-1)"!][!//
  [!ERROR!][!//
    ADC Code Generator: Missing CPU Core allocation for HwUnit "[!"$Item"!]".
  [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Adc_ValidateChAllocation                                **
**                                                                            **
** Description      : Macro to validate if a channel is allocated to the core **
**                                                                            **
** Pre-requisite    : Adc_GenerateModuleMap macro should be called before     **
**                    calling this macro                                      **
*******************************************************************************/
[!MACRO "Adc_ValidateChAllocation", "Item" = ""!][!//
[!NOCODE!][!//
[!VAR "CGResult" = "'FALSE'"!][!//
[!IF "text:contains(text:split($CGAllocatedResources,','), $Item)"!][!//
  [!VAR "CGResult" = "'TRUE'"!][!//
[!ELSE!][!//
  [!VAR "CGResult" = "'FALSE'"!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Adc_ConfigGetGtmParams                                  **
**                                                                            **
** Description      : This macro generates ticks for the GTM timer            **
*******************************************************************************/
[!/* [cover parentID={C1572ECC-84EF-4ef8-B815-9007B5AF1953}]Adc_ConfigGetGtmParams[/cover] */!][!//
[!MACRO "Adc_ConfigGetGtmParams","GtmChannelRef"= "","GtmTimePeriod"="","GtmTimerContainer"="",
"GtmClockRef"="","GtmTimerTicks"="","GtmTimerType"="",
"GtmTimerModNo"="",,"GtmTimerChNo"=""!][!//
[!NOCODE!][!//

[!VAR "GtmTimerType" = "substring-before(substring-after(text:split(($GtmChannelRef),'/')[6],'McuGtm'),'AllocationConf')"!]
[!VAR "GtmTimerType" = "text:toupper($GtmTimerType)"!]
[!VAR "GtmTimerModNo" = "text:split($GtmChannelRef, 'AllocationConf_')[4]"!]
[!VAR "GtmTimerModNo" = "text:split($GtmTimerModNo,'/')[1]"!]
[!VAR "GtmTimerChNo" = "text:split($GtmChannelRef,'ChannelAllocationConf_')[2]"!]

[!IF "$GtmTimePeriod != num:i(0)"!][!//CM0 ticks are directly available
  [!VAR "McuModuleConfig"="node:path(node:ref($GtmClockRef)/../../..)"!]
  [!VAR "GtmNumerator" = "node:ref($McuModuleConfig)/GtmGlobalConfiguration/*[1]/McuGtmClockManagementConf/GtmCmuGlobalClockNumerator"!]
  [!VAR "GtmDenominator" = "node:ref($McuModuleConfig)/GtmGlobalConfiguration/*[1]/McuGtmClockManagementConf/GtmCmuGlobalClockDenominator"!]
  [!VAR "fScuGtm" = "node:ref($GtmClockRef)/McuPllDistributionSettingConfig/McuGTMFrequency"!][!//Clock frequecy from MCU
  [!VAR "fGtm"="num:f((num:f($fScuGtm) * num:f($GtmDenominator)) div num:f($GtmNumerator))"!][!//Clock frequecy GTM Global - CMU_GCLK
  [!VAR "GtmClusterNodeName" = "concat('GtmClusterConf_',num:i($GtmTimerModNo))"!]
  [!VAR "GtmClusterXDivider" = "node:ref($McuModuleConfig)/GtmGlobalConfiguration/*[1]/GtmClusterConf/*[@name=$GtmClusterNodeName]/GtmCmuClusterInputClockDividerEnable"!]
  [!VAR "GtmCluster0Divider" = "node:ref($McuModuleConfig)/GtmGlobalConfiguration/*[1]/GtmClusterConf/*[@name='GtmClusterConf_0']/GtmCmuClusterInputClockDividerEnable"!]
  [!IF "$GtmCluster0Divider= 'CLS_CLK_CFG_ENABLED_WITH_DIV_SEL2'"!]
    [!VAR "GtmClusterDivVal" = "num:f(2.0)"!]
  [!ELSEIF "$GtmCluster0Divider= 'CLS_CLK_CFG_ENABLED_WITHOUT_DIV_SEL1'"!]
    [!IF "$GtmClusterXDivider= 'CLS_CLK_CFG_ENABLED_WITH_DIV_SEL2'"!]
      [!VAR "GtmClusterDivVal" = "num:f(2.0)"!]
    [!ELSE!]
      [!VAR "GtmClusterDivVal" = "num:f(1.0)"!]
    [!ENDIF!]
  [!ENDIF!]
  [!IF "$GtmCluster0Divider = 'CLS_CLK_CFG_DISABLED_SEL0' or $GtmClusterXDivider = 'CLS_CLK_CFG_DISABLED_SEL0'"!]
    [!ERROR!]
      ADC Code Generator: GTM cluster level divider (GtmCmuClusterInputClockDividerEnable) is swiched off of Cluster0 or Cluster[!"$GtmTimerModNo"!].
    [!ENDERROR!]
  [!ENDIF!]
  [!VAR "fGtm"="num:f(num:f($fGtm) div num:f($GtmClusterDivVal))"!]
  [!VAR "ChannelClkDiv"="node:value(node:ref($GtmTimerContainer)/GtmTimerClockSelect)"!][!//Clock divider used by the channel

  [!VAR "ClockType" ="num:i(0)"!]
  [!VAR "ClockId" ="num:i(255)"!]
  [!IF "contains($ChannelClkDiv,'_CONFIGURABLE_')= 'true'"!][!//ATOM channel using a configurable clock
    [!VAR "ConfigClkId" = "text:split($ChannelClkDiv,'_')[4]"!]
    [!SELECT "node:ref($McuModuleConfig)/GtmGlobalConfiguration/*[1]/GtmClusterConf/*[@name=$GtmClusterNodeName]"!][!//Select the GTM Cluster
    [!VAR "TempNodeName"= "concat('./GtmClusterConfClockSetting/','GtmClusterConfClock',$ConfigClkId,'Src')"!][!//Clock Source select node for config clock in GTM cluster
    [!IF "contains(node:value($TempNodeName),'CLOCK8_SEL1')"!]
      [!VAR "ClockId"="num:i(8)"!]
      [!VAR "ClockType"="'CONF_CLOCK'"!]
    [!ELSEIF "contains(node:value($TempNodeName),'_SEL0')"!]
      [!VAR "ClockId"="num:i($ConfigClkId)"!]
      [!VAR "ClockType"="'CONF_CLOCK'"!]
    [!ELSE!]
      [!ERROR!]
      ADC Code Generator: Unable to calculate the clock frequency for the GTM timer cell at NODE: NODE: [!"node:path(.)"!]/[!"text:split($GtmTimerContainer,'/')[2]"!]. Please enter the CM0 ticks directly in GtmTimerCM0Ticks parameter
      [!ENDERROR!]
    [!ENDIF!]
    [!ENDSELECT!]
  [!ELSEIF "contains($ChannelClkDiv,'_FIXED_')= 'true'"!][!//TOM channel using a fixed clock
    [!SELECT "node:ref($McuModuleConfig)/GtmGlobalConfiguration/*[1]/GtmClusterConf/*[@name=$GtmClusterNodeName]"!]
    [!IF "(contains(node:value(./GtmClusterFixedClockSetting/GtmClusterFixedClockSrc),'CLOCK8_SEL1') = 'true') and
          ($ChannelClkDiv = 'GTM_FIXED_CLOCK_0')"!]
      [!VAR "ClockId"="num:i(8)"!]
      [!VAR "ClockType"="'CONF_CLOCK'"!]
    [!ELSE!]
      [!VAR "ClockId"="num:i(0)"!]
      [!VAR "ClockType"="'FIXED_CLOCK'"!]
    [!ENDIF!]
    [!IF "../../../*[1]/McuGtmClockManagementConf/GtmFixedClockSetting/GtmCmuFixedClockEnable = 'false'"!]
      [!ERROR!]
        ADC Code Generator: McuGtmClockManagementConf/GtmFixedClockSetting/GtmCmuFixedClockEnable cannot be false when fixed clock is used.
      [!ENDERROR!]
    [!ENDIF!]
    [!ENDSELECT!]
  [!ELSE!]
    [!ERROR!]
      ADC Code Generator: Incorrect clock divider selected for [!"$GtmTimerContainer"!]
    [!ENDERROR!]
  [!ENDIF!]
  [!SELECT "node:ref($McuModuleConfig)/GtmGlobalConfiguration/*[1]/McuGtmClockManagementConf"!]
  [!IF "$ClockType = 'FIXED_CLOCK'"!]
    [!VAR "TempNodeValue"="GtmFixedClockSetting/GtmCmuFixedClockSel"!]
    [!IF "$TempNodeValue != 'CMU_GLOBAL_CLOCK_SEL0'"!][!// Configurable clock is the source of fixed clock
      [!VAR "CmuClkId" = "text:split(text:split($TempNodeValue,'_')[2],'CLOCK')[1]"!]
      [!VAR "TempNodeName"= "concat('./GtmConfigClockSetting/','GtmCmuConfigClock',$CmuClkId,'Enable')"!]
      [!IF "node:value($TempNodeName) != 'true'"!]
      [!ERROR!]
       ADC Code Generator:Configurable clock [!"$CmuClkId"!] is not enabled. Enable configurable clock via [!"$TempNodeName"!]
      [!ENDERROR!]
      [!ENDIF!]
      [!VAR "TempNodeName"= "concat('./GtmConfigClockSetting/','GtmCmuConfigClock',$CmuClkId,'Div')"!]
      [!VAR "ClockDivider"="num:i(node:value($TempNodeName)+1)"!]
      [!VAR "fGtm" = "num:i(num:f($fGtm) div num:f($ClockDivider))"!]
    [!ENDIF!]
    [!VAR "Exponent" = "text:split($ChannelClkDiv,'_')[4]"!]
    [!VAR "Exponent" = "num:i($Exponent) * num:i(4)"!]
    [!VAR "ClockDivider" = "num:i(1)"!]
    [!IF "Exponent != num:i(0)"!]
      [!FOR "LoopCtr" = "num:i(0)" TO "num:i(($Exponent)- num:i(1))"!]
      [!VAR "ClockDivider" = "num:i($ClockDivider) * num:i(2)"!]
      [!ENDFOR!]
    [!ENDIF!]
    [!VAR "fGtm" = "$fGtm div $ClockDivider"!]
  [!ELSEIF "$ClockType = 'CONF_CLOCK' and ($ClockId < num:i(8))"!]
    [!VAR "TempNodeName"= "concat('./GtmConfigClockSetting/','GtmCmuConfigClock',$ClockId,'Enable')"!]
    [!IF "node:value($TempNodeName) != 'true'"!]
      [!ERROR!]
       ADC Code Generator:Configurable clock [!"$ClockId"!] is not enabled. Enable configurable clock via [!"$TempNodeName"!]
      [!ENDERROR!]
    [!ENDIF!]
    [!VAR "TempNodeName"= "concat('./GtmConfigClockSetting/','GtmCmuConfigClock',$ClockId,'Div')"!]
    [!VAR "ClockDivider"="num:i(node:value($TempNodeName)+1)"!]
    [!VAR "fGtm" = "$fGtm div $ClockDivider"!]
  [!ELSEIF "$ClockType = 'CONF_CLOCK' and ($ClockId = num:i(8))"!]
    [!ERROR!]
     ADC Code Generator:Unable to calculate the clock frequency for the GTM timer cell at NODE: [!"node:path(.)"!]/[!"text:split($GtmTimerContainer,'/')[2]"!]. Please enter the CM0 ticks directly in GtmTimerCM0Ticks parameter.
    [!ENDERROR!]
  [!ELSE!]
    [!ERROR!]
     ADC Code Generator:Unable to calculate the clock frequency for the GTM timer cell at NODE: [!"node:path(.)"!]/[!"text:split($GtmTimerContainer,'/')[2]"!]. Please enter the CM0 ticks directly in GtmTimerCM0Ticks parameter.
    [!ENDERROR!]
  [!ENDIF!]
  [!ENDSELECT!]
  [!VAR "GtmTimerTicks" = "num:i((num:f($GtmTimePeriod) * num:f($fGtm)) div num:i(1000000))"!]
[!ENDIF!]

[!IF "$GtmTimerType = 'TOM'"!][!//
  [!IF "node:ref($GtmChannelRef)/McuGtmTomChannelAllocationConf != 'GTM_TOM_CHANNEL_USED_BY_ADC'"!][!//
    [!ERROR!][!//
      ADC Code Generator: The TOM channel configured at [!"node:path(.)"!]/[!"text:split($GtmTimerContainer,'/')[2]"!] is not reserved for ADC in the MCU container - [!"$GtmChannelRef"!]
    [!ENDERROR!][!//
  [!ENDIF!][!//
  [!IF "$GtmTimerTicks > num:i(65535)"!]
    [!ERROR!]
      ADC Code Generator:Timer ticks calculates is beyond 65535 for the NODE: [!"node:path(.)"!]/[!"text:split($GtmTimerContainer,'/')[2]"!]. Reduce TimePeriod or Timer frequency.
    [!ENDERROR!]
  [!ENDIF!]
[!ELSEIF "$GtmTimerType = 'ATOM'"!][!//
  [!IF "node:ref($GtmChannelRef)/McuGtmAtomChannelAllocationConf != 'GTM_ATOM_CHANNEL_USED_BY_ADC'"!][!//
    [!ERROR!][!//
     ADC Code Generator: The ATOM channel configured at [!"node:path(.)"!]/[!"text:split($GtmTimerContainer,'/')[2]"!] is not reserved for ADC in the MCU container - [!"$GtmChannelRef"!]
    [!ENDERROR!][!//
  [!ENDIF!][!//
  [!IF "$GtmTimerTicks > num:i(16777215)"!]
    [!ERROR!]
     ADC Code Generator: Timer ticks calculated is beyond 16777215 for the NODE: [!"node:path(.)"!]/[!"text:split($GtmTimerContainer,'/')[2]"!]. Reduce TimePeriod or Timer frequency.
    [!ENDERROR!]
  [!ENDIF!][!//
[!ELSE!][!//
  [!ERROR!]
   ADC Code Generator: Undeterminable Timer Type at NODE: [!"node:path(.)"!]/[!"text:split($GtmTimerContainer,'/')[2]"!].
  [!ENDERROR!]
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Adc_ConfigPreCompileSwitch                              **
**                                                                            **
** Description      : Macro to generate configuration switch Values ON/OFF    **
**                    based on configuration true/false                       **
**                                                                            **
*******************************************************************************/
[!MACRO "Adc_ConfigPreCompileSwitch", "NodeVal" = ""!][!//
[!//
[!IF "$NodeVal = 'true'"!][!//
(STD_ON)[!//
[!ELSE!][!//
(STD_OFF)[!//
[!ENDIF!][!//
[!ENDMACRO!][!//

[!ENDIF!][!// IF "not(var:defined('ADC_M'))[!//
