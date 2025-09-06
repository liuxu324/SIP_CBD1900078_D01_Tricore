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
**  FILENAME  : Mcu.m                                                         **
**                                                                            **
**  VERSION   : 6.0.0                                                         **
**                                                                            **
**  DATE      : 2018.08.14                                                    **
**                                                                            **
**  VARIANT   : Post-Build                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION :  This file contains the macros used by the code template    **
**                                                                            **
**  SPECIFICATION(S) : Specification of MCU Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : No                                               **
**                                                                            **
*******************************************************************************/
*/!]
/******************************************************************************/
[!/* *** multiple inclusion protection*** */!][!//
[!IF "not(var:defined('MCU_M'))"!][!//
[!VAR "MCU_M"="'true'"!][!//
[!AUTOSPACING!]
[!INDENT "0"!]
/*******************************************************************************
** Name             : Mcu_CG_GetBooleanVal                                    **
**                                                                            **
** Description      : This macro returns TRUE or FALSE value out of boolean   **
**                    parameter                                               **
**                                                                            **
*******************************************************************************/
[!MACRO "Mcu_CG_GetBooleanVal", "InpVal" = ""!][!//
  [!NOCODE!][!//
  [!IF "$InpVal = 'true'"!][!//
    [!VAR "OutVal" = "num:i(1)"!][!//
  [!ELSE!][!//
    [!VAR "OutVal" = "num:i(0)"!][!//
  [!ENDIF!]
  [!ENDNOCODE!][!//
[!ENDMACRO!]

/*******************************************************************************
** Name             : Mcu_GTM_ValFreq                                         **
**                                                                            **
** Description      : Macro to validate the GTM frequecy                      **
**                                                                            **
*******************************************************************************/
[!MACRO "Mcu_GTM_ValFreq"!][!//
  [!NOCODE!][!//
    [!VAR "GtmFreqVal" = "num:i(./McuPllDistributionSettingConfig/McuGTMFrequency)"!][!//
    [!IF "$GtmFreqVal > num:i(0)"!][!//
      [!VAR "CalculatedVal" = "num:i(./McuSystemPllSettingConfig/McuClockReferencePointFrequency0) div num:i(./McuPllDistributionSettingConfig/McuGTMFrequency)"!][!//
       [!IF "floor($CalculatedVal) = num:i(1)"!][!//
         [!IF "num:i(./McuPllDistributionSettingConfig/McuGTMFrequency) != (2*(num:i(./McuPllDistributionSettingConfig/McuSPBFrequency)))"!][!//
           [!ERROR!][!//
             Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: McuGTMFrequency should be twice of McuSPBFrequency. Please configure the correct value.
           [!ENDERROR!][!//
         [!ENDIF!][!//
         [!VAR "CalculatedVal" = "num:i(1)"!][!//
       [!ELSE!][!//
         [!VAR "CalculatedVal" = "num:i(./McuSystemPllSettingConfig/McuClockReferencePointFrequency0) div num:i(./McuPllDistributionSettingConfig/McuGTMFrequency)"!][!//
         [!CALL "Calculate_DivVal", "Val" = "$CalculatedVal","Freq" = "'GTM'"!][!//
       [!ENDIF!]
    [!ELSE!][!//
      [!VAR "CalculatedVal" = "num:i(0)"!][!//
    [!ENDIF!][!//
  [!ENDNOCODE!][!//
[!ENDMACRO!]
/*******************************************************************************
** Name             : Mcu_CG_ValFreq                                          **
**                                                                            **
** Description      : Macro to validate the input frequecy                    **
**                                                                            **
*******************************************************************************/
[!MACRO "Mcu_CG_ValFreq", "Freq" = ""!][!//
  [!NOCODE!][!//
    [!VAR "CurrFreq" = "concat('Mcu', $Freq, 'Frequency')"!]
    [!VAR "CurrFreqMin" = "concat('Mcu.f', $Freq, 'MinFrequency')"!]
    [!VAR "CurrFreqMax" = "concat('Mcu.f', $Freq, 'MaxFrequency')"!]
    [!VAR "CurrFreqValue" = "node:ref(concat('./McuPllDistributionSettingConfig/', $CurrFreq))"!]
    [!VAR "DependentFreqList" = "concat('Mcu.', $Freq, 'ClockDependencies')"!]
    [!VAR "DividerValuePropertyVariable" = "concat('Mcu.', $Freq, 'DividerValues')"!]
    [!IF "$CurrFreqValue > num:i(0)"!][!//
      [!IF "ecu:has($CurrFreqMin) = 'true'"!][!//
        [!IF "$CurrFreqValue < ecu:get($CurrFreqMin)"!][!//
          [!ERROR!][!//
            Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: [!"$Freq"!] frequency is below the mininum allowed value of [!"ecu:get($CurrFreqMin)"!]. Either disable the clock to [!"$Freq"!](by writing 0 to [!"$CurrFreq"!]) or configure the value correctly.
          [!ENDERROR!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!IF "ecu:has($CurrFreqMax) = 'true'"!][!//
        [!IF "$CurrFreqValue > ecu:get($CurrFreqMax)"!][!//
          [!ERROR!][!//
            Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: [!"$Freq"!] frequency is above the maximum allowed value of [!"ecu:get($CurrFreqMax)"!]. Either disable the clock to [!"$Freq"!](by writing 0 to [!"$CurrFreq"!]) or configure the value correctly.
          [!ENDERROR!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!VAR "CalculatedVal" = "num:i(./McuSystemPllSettingConfig/McuClockReferencePointFrequency0) div num:i($CurrFreqValue)"!][!//
      [!CALL "Calculate_DivVal", "Val" = "$CalculatedVal","Freq" = "$CurrFreq"!][!//
      [!IF "ecu:has($DividerValuePropertyVariable) = 'true'"!]
          [!IF "text:contains(ecu:list($DividerValuePropertyVariable),string(num:i($CalculatedVal))) != 'true'"!][!//
            [!ERROR!][!//
              Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: [!"$Freq"!] freq divider is not valid. Allowed divider values are [!"string(ecu:get($DividerValuePropertyVariable))"!]
            [!ENDERROR!][!//
          [!ENDIF!][!//
      [!ENDIF!][!//
      [!IF "ecu:has($DependentFreqList) = 'true'"!][!//
          [!FOR "index" = "num:i(1)" TO "num:i(count(ecu:list($DependentFreqList)))"!]
            [!VAR "DependentFreq" = "concat('Mcu', ecu:list($DependentFreqList)[num:i($index)], 'Frequency')"!]
            [!VAR "DependentFreqValue" = "node:ref(concat('./McuPllDistributionSettingConfig/', $DependentFreq))"!]
            [!VAR "DependentFreqClockRatio" = "concat('Mcu.', $Freq, ecu:list($DependentFreqList)[num:i($index)],'ClockRatios')"!]
            [!IF "ecu:has($DependentFreqClockRatio) = 'true'"!][!//
              [!IF "$DependentFreqValue > $CurrFreqValue"!][!//
                [!IF "text:contains(ecu:list($DependentFreqClockRatio),string(num:i($DependentFreqValue) div num:i($CurrFreqValue))) != 'true'"!][!//
                  [!ERROR!][!//
                    Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: Clock ratio between [!"$DependentFreq"!] and [!"$CurrFreq"!] is not within the allowed ratio. Allowed ratios are [!"string(ecu:get($DependentFreqClockRatio))"!].
                  [!ENDERROR!][!//
                [!ENDIF!][!//
              [!ELSE!][!//
                [!IF "num:i($DependentFreqValue)!= num:i(0)"!]
                  [!IF "text:contains(ecu:list($DependentFreqClockRatio),string(num:i($CurrFreqValue) div num:i($DependentFreqValue))) != 'true'"!][!//
                    [!ERROR!][!//
                      Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: Clock ratio between [!"$CurrFreq"!] and [!"$DependentFreq"!] is not within the allowed ratio. Allowed ratios are [!"string(ecu:get($DependentFreqClockRatio))"!].
                    [!ENDERROR!][!//
                  [!ENDIF!][!//
                [!ENDIF!][!//
              [!ENDIF!][!//
            [!ENDIF!][!//
          [!ENDFOR!]
      [!ENDIF!][!//
    [!ELSE!][!//
      [!VAR "CalculatedVal" = "num:i(0)"!][!//
    [!ENDIF!][!//
  [!ENDNOCODE!][!//
[!ENDMACRO!]

/*******************************************************************************
** Name             : Mcu_CG_CPUFreq                                          **
**                                                                            **
** Description      : Macro to validate the CPU frequecies                    **
**                                                                            **
*******************************************************************************/
[!MACRO "Mcu_CG_CPUFreq", "Freq" = ""!][!//
[!NOCODE!][!//
  [!VAR "CurrFreq" = "concat('Mcu', $Freq, 'Frequency')"!]
  [!VAR "CurrFreqExists" = "concat('Mcu.f', $Freq, 'Exists')"!]
  [!VAR "CurrFreqValue" = "node:ref(concat('./McuPllDistributionSettingConfig/', $CurrFreq))"!]
  [!VAR "DependentFreqList" = "concat('Mcu.', $Freq, 'ClockDependencies')"!]
  [!VAR "DividerValuePropertyVariable" = "concat('Mcu.', $Freq, 'DividerValues')"!]
  [!IF "num:i($CurrFreqValue) > num:i(./McuPllDistributionSettingConfig/McuSRIFrequency)"!][!//
    [!ERROR!][!//
      Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: [!"$Freq"!] Frequency cannot be greater than SRI Frequency.
    [!ENDERROR!][!//
  [!ENDIF!][!//
  [!VAR "CalculatedVal" = "num:i($CurrFreqValue) * num:i(64)"!][!//
  [!VAR "CalculatedVal" = "num:i($CalculatedVal) div num:i(./McuPllDistributionSettingConfig/McuSRIFrequency)"!][!//
  [!VAR "CalculatedVal" = "num:f(64.0) - num:f($CalculatedVal)"!][!//
  [!CALL "Calculate_DivVal", "Val" = "$CalculatedVal","Freq" = "$CurrFreq"!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Mcu_CG_MCNASCLNFreq                                     **
**                                                                            **
** Description      : Macro to validate MCan and ASCLIN Slow frequecies       **
**                                                                            **
*******************************************************************************/
[!MACRO "Mcu_CG_MCNASCLNFreq", "Freq" = "", "ClkSrcSel" = ""!][!//
[!NOCODE!][!//
  [!VAR "CurrFreq" = "concat('Mcu', $Freq, 'Frequency')"!]
  [!VAR "CurrFreqMin" = "concat('Mcu.f', $Freq, 'MinFrequency')"!]
  [!VAR "CurrFreqMax" = "concat('Mcu.f', $Freq, 'MaxFrequency')"!]
  [!VAR "CurrFreqValue" = "node:ref(concat('./McuPllDistributionSettingConfig/', $CurrFreq))"!]
  [!VAR "DependentFreqList" = "concat('Mcu.', $Freq, 'ClockDependencies')"!]
  [!VAR "DividerValuePropertyVariable" = "concat('Mcu.', $Freq, 'DividerValues')"!]
  [!VAR "ClkSrcSel" = "node:ref(concat('./McuPllDistributionSettingConfig/', 'Mcu', $Freq, 'ClockSourceSelection'))"!][!//
  [!VAR "ClkSrcSel" = "text:split($ClkSrcSel,'SEL')[2]"!][!//
  [!VAR "CalculatedVal" = "num:i(0)"!][!//
  [!IF "$ClkSrcSel = num:i(1)"!][!//
    [!IF "num:i($CurrFreqValue) > num:i(0)"!][!//
      [!IF "ecu:has($CurrFreqMin) = 'true'"!][!//
        [!IF "$CurrFreqValue < ecu:get($CurrFreqMin)"!][!//
          [!ERROR!][!//
            Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: [!"$Freq"!] frequency is below the mininum allowed value of [!"ecu:get($CurrFreqMin)"!]. Either disable the clock to [!"$Freq"!](by writing 0 to [!"$CurrFreq"!]) or configure the value correctly.
          [!ENDERROR!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!IF "ecu:has($CurrFreqMax) = 'true'"!][!//
        [!IF "$CurrFreqValue > ecu:get($CurrFreqMax)"!][!//
          [!ERROR!][!//
            Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: [!"$Freq"!] frequency is above the maximum allowed value of [!"ecu:get($CurrFreqMax)"!]. Either disable the clock to [!"$Freq"!](by writing 0 [!"$CurrFreq"!]) or configure the value correctly.
          [!ENDERROR!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!VAR "CalculatedVal" = "num:i(./McuPeripheralPllSettingConfig/McuClockReferencePointFrequency1) div num:i($CurrFreqValue)"!][!//
      [!CALL "Calculate_DivVal", "Val" = "$CalculatedVal","Freq" = "$CurrFreq"!][!//
      [!IF "text:contains(ecu:list($DividerValuePropertyVariable),string(num:i($CalculatedVal))) != 'true'"!][!//
        [!ERROR!][!//
          Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: [!"$Freq"!] freq divider is not a valid divider value. Check the description for allowed values. McuClockReferencePointFrequency1 /n (where n = 0,1,2,3,4,5,6,8,10,12,15)
        [!ENDERROR!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ELSEIF "$ClkSrcSel = num:i(2)"!][!//
    [!IF "num:i($CurrFreqValue) != num:i($OscFrequency)"!][!//
      [!ERROR!][!//
        Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: [!"$Freq"!] shall be equal to Oscillator frequency for selected [!"node:ref(concat('./McuPllDistributionSettingConfig/', 'Mcu', $Freq, 'ClockSourceSelection'))"!].
      [!ENDERROR!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

 /******************************************************************************
** Name             : Mcu_CG_MSCQSPIFreq                                      **
**                                                                            **
** Description      : Macro to validate MSC and QSPI frequecies               **
**                                                                            **
*******************************************************************************/
[!MACRO "Mcu_CG_MSCQSPIFreq", "Freq" = "", "ClkSrcSel"=""!][!//
[!NOCODE!][!//
  [!VAR "CurrFreq" = "concat('Mcu', $Freq, 'Frequency')"!]
    [!VAR "CurrFreqMin" = "concat('Mcu.f', $Freq, 'MinFrequency')"!]
    [!VAR "CurrFreqMax" = "concat('Mcu.f', $Freq, 'MaxFrequency')"!]
    [!VAR "CurrFreqValue" = "node:ref(concat('./McuPllDistributionSettingConfig/', $CurrFreq))"!]
    [!VAR "DependentFreqList" = "concat('Mcu.', $Freq, 'ClockDependencies')"!]
    [!VAR "DividerValuePropertyVariable" = "concat('Mcu.', $Freq, 'DividerValues')"!]
    [!VAR "ClkSrcSel" = "node:ref(concat('./McuPllDistributionSettingConfig/', 'Mcu', $Freq, 'ClockSourceSelection'))"!][!//
    [!VAR "ClkSrcSel" = "text:split($ClkSrcSel,'SEL')[2]"!][!//
    [!VAR "CalculatedVal" = "num:i(0)"!][!//
    [!IF "$ClkSrcSel > num:i(0)"!]
      [!IF "num:i($CurrFreqValue) > num:i(0)"!][!//
        [!IF "ecu:has($CurrFreqMin) = 'true'"!][!//
          [!IF "$CurrFreqValue < ecu:get($CurrFreqMin)"!][!//
            [!ERROR!][!//
              Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: [!"$Freq"!] frequency is below the mininum allowed value of [!"ecu:get($CurrFreqMin)"!]. Either disable the clock to [!"$Freq"!](by writing 0 to [!"$CurrFreq"!]) or configure the value correctly.
            [!ENDERROR!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
        [!IF "ecu:has($CurrFreqMax) = 'true'"!][!//
          [!IF "$CurrFreqValue > ecu:get($CurrFreqMax)"!][!//
            [!ERROR!][!//
              Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: [!"$Freq"!] frequency is above the maximum allowed value of [!"ecu:get($CurrFreqMax)"!]. Either disable the clock to [!"$Freq"!](by writing 0 to [!"$CurrFreq"!]) or configure the value correctly.
            [!ENDERROR!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
        [!IF "$ClkSrcSel = num:i(1)"!][!//
          [!VAR "CalculatedVal" = "num:i(./McuPeripheralPllSettingConfig/McuClockReferencePointFrequency1) div num:i($CurrFreqValue)"!][!//
        [!ELSE!][!//$ClkSrcSel=2
          [!VAR "CalculatedVal" = "num:i(./McuPeripheralPllSettingConfig/McuClockReferencePointFrequency2) div num:i($CurrFreqValue)"!][!//
        [!ENDIF!][!//
        [!CALL "Calculate_DivVal", "Val" = "$CalculatedVal","Freq" = "$CurrFreq"!][!//
        [!IF "text:contains(ecu:list($DividerValuePropertyVariable),string(num:i($CalculatedVal))) != 'true'"!][!//
          [!ERROR!][!//
            Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: [!"$Freq"!] freq divider is not a valid divider value. Check the description for allowed values. McuClockReferencePointFrequency1 /n (where n = 0,1,2,3,4,5,6,8,10,12,15)
          [!ENDERROR!][!//
        [!ENDIF!][!//
      [!ELSE!][!//
        [!VAR "CalculatedVal" = "num:i(./McuPllDistributionSettingConfig/$CurrFreq)"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Mcu_CG_I2CASCLINFFreq                                   **
**                                                                            **
** Description      : Macro to validate I2C ASCLIN Fast frequecies            **
**                                                                            **
*******************************************************************************/
[!MACRO "Mcu_CG_I2CASCLINFFreq", "Freq" = ""!][!//
  [!NOCODE!][!//
    [!VAR "CurrFreq" = "concat('Mcu', $Freq, 'Frequency')"!]
    [!VAR "CurrFreqMin" = "concat('Mcu.f', $Freq, 'MinFrequency')"!]
    [!VAR "CurrFreqMax" = "concat('Mcu.f', $Freq, 'MaxFrequency')"!]
    [!VAR "CurrFreqValue" = "node:ref(concat('./McuPllDistributionSettingConfig/', $CurrFreq))"!]
    [!VAR "DependentFreqList" = "concat('Mcu.', $Freq, 'ClockDependencies')"!]
    [!VAR "DividerValuePropertyVariable" = "concat('Mcu.', $Freq, 'DividerValues')"!]
    [!IF "($CurrFreqValue) > num:i(0)"!][!//
      [!IF "ecu:has($CurrFreqMin) = 'true'"!][!//
        [!IF "$CurrFreqValue < ecu:get($CurrFreqMin)"!][!//
          [!ERROR!][!//
      Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: [!"$Freq"!] frequency is below the mininum allowed value of [!"ecu:get($CurrFreqMin)"!]. Either disable the clock to [!"$Freq"!](by writing 0 to [!"$CurrFreq"!]) or configure the value correctly.
          [!ENDERROR!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!IF "ecu:has($CurrFreqMax) = 'true'"!][!//
        [!IF "$CurrFreqValue > ecu:get($CurrFreqMax)"!][!//
          [!ERROR!][!//
      Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: [!"$Freq"!] frequency is above the maximum allowed value of [!"ecu:get($CurrFreqMax)"!]. Either disable the clock to [!"$Freq"!](by writing 0 to [!"$CurrFreq"!]) or configure the value correctly.
          [!ENDERROR!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!VAR "CalculatedVal" = "num:i(./McuPeripheralPllSettingConfig/McuClockReferencePointFrequency2) div num:i($CurrFreqValue)"!][!//
      [!CALL "Calculate_DivVal", "Val" = "$CalculatedVal","Freq" = "$CurrFreq"!][!//
      [!IF "text:contains(ecu:list($DividerValuePropertyVariable),string(num:i($CalculatedVal))) != 'true'"!][!//
        [!ERROR!][!//
          Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: [!"$Freq"!] freq divider is not a valid divider value. Check the description for allowed values. McuClockReferencePointFrequency1 /n (where n = 0,1,2,3,4,5,6,8,10,12,15)
        [!ENDERROR!][!//
      [!ENDIF!][!//
    [!ELSE!][!//
        [!VAR "CalculatedVal" = "num:i($CurrFreqValue)"!][!//
    [!ENDIF!][!//
  [!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Calculate_DivVal                                        **
**                                                                            **
** Description      : Macro to validate integer divider value                 **
**                                                                            **
*******************************************************************************/
[!MACRO "Calculate_DivVal", "Val" = "", "Freq" = ""!][!//
  [!NOCODE!][!//
    [!IF "($CalculatedVal) > round($CalculatedVal)"!][!//
      [!VAR "DivVal" = "num:f(($CalculatedVal) - round($CalculatedVal))"!][!//
        [!IF "$DivVal > num:f(0.1)"!][!//
          [!ERROR!][!//
      Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: [!"$Freq"!] freq divider is not an integer
          [!ENDERROR!][!//
        [!ELSE!][!//
          [!VAR "CalculatedVal" = "round($CalculatedVal)"!][!//
        [!ENDIF!][!//
    [!ELSE!][!//
      [!VAR "DivVal" = "num:f(round($CalculatedVal) -($CalculatedVal))"!][!//
        [!IF "$DivVal > num:f(0.1)"!][!//
          [!ERROR!][!//
      Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: [!"$Freq"!] freq divider is not an integer
          [!ENDERROR!][!//
        [!ELSE!][!//
          [!VAR "CalculatedVal" = "round($CalculatedVal)"!][!//
        [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!ENDINDENT!]
[!ENDIF!][!// IF "not(var:defined('MCU_M'))