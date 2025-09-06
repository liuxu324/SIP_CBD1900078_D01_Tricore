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
**  FILENAME  : Wdg_17_Scu.m                                                  **
**                                                                            **
**  VERSION   : 3.0.0                                                         **
**                                                                            **
**  DATE      : 2018-07-19                                                    **
**                                                                            **
**  BSW MODULE DESCRIPTION : Wdg.bmd                                          **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : NA                                                         **
**                                                                            **
**  DESCRIPTION  : Code template macro file for Wdg Driver                    **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Wdg Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
*/!]


[!//
[!/* *** multiple inclusion protection*** */!][!//
[!IF "not(var:defined('WDG_17_M'))"!][!//
[!VAR "WDG_17_M"="'true'"!][!//

[!/*
MACRO: WDG_CG_ConfigSwitch 
Macro to generate configuration switch Values STD_ON/STD_OFF based on configuration
true/false
*/!]
[!MACRO "WDG_CG_ConfigSwitch", "nodeval" = ""!][!//
[!//
[!IF "$nodeval = 'true'"!][!//
(STD_ON)[!//
[!ELSE!][!//
(STD_OFF)[!//
[!ENDIF!]
[!ENDMACRO!]

[!/*****************************************************************************
** Name             : Wdg_RefreshTimeValidation                               **
**                                                                            **
** Description      : Macro to validate Refresh time                          **
**                                                                            **
*****************************************************************************/!]
/* [cover parentID={3369DCF5-DB7C-4515-AA76-0CECE8F35FF6}][/cover] */
[!MACRO "Wdg_RefreshTimeValidation", "RefreshTime"="", "WdgTout"="","ModeString"="","PathVar" = "","WdgCoreID" = ""!][!//
[!NOCODE!]
[!IF "($RefreshTime >= $WdgTout)"!]
[!IF "$ModeString = 'SLOW'"!]
 [!ERROR!]
  WDG Config Error: WdgSlowRefreshTime [!"$PathVar"!] in core [!"$WdgCoreID"!] should be less than WdgSlowModeTimeoutValue
 [!ENDERROR!]
[!ELSEIF "$ModeString = 'FAST'"!]
 [!ERROR!]
  WDG Config Error: WdgFastRefreshTime  [!"$PathVar"!] in core [!"$WdgCoreID"!] should be less than WdgFastModeTimeoutValue
 [!ENDERROR!]
[!ELSE!]
 [!ERROR!]
  WDG Config Error: WdgFastRefreshTime  [!"$PathVar"!] in core [!"$WdgCoreID"!] should be less than WdgSlowRefreshTime
 [!ENDERROR!]
[!ENDIF!]
[!ENDIF!]
[!ENDNOCODE!]
[!ENDMACRO!]
[!/*****************************************************************************
** Name             : Wdg_ValidateInitialTout                                 **
**                                                                            **
** Description      : Macro to validate WDG Initial Timeout                   **
**                                                                            **
*****************************************************************************/!]
/* [cover parentID={160891A5-632B-4b96-861D-1E215D61CB1D}][/cover] */
[!MACRO "Wdg_ValidateInitialTout", "InitialTout" = "", "MaxTout" = "", "SlowRefrehT" = "","FastRefreshT" = "","WdgCoreID" = ""!]
[!NOCODE!]
[!IF "$InitialTout > $MaxTout"!]
[!ERROR!]
 WDG Config Error: WdgInitialTimeout value  for core [!"$WdgCoreID"!] exceeds WdgMaxTimeout.
[!ENDERROR!]
[!ENDIF!]
[!IF "$SlowRefrehT >= $InitialTout"!]
[!ERROR!]
 WDG Config Error: WdgSlowRefreshTime for core [!"$WdgCoreID"!] should be less than WdgInitialTimeout.
[!ENDERROR!]
[!ENDIF!]
[!IF "$FastRefreshT >= $InitialTout"!]
[!ERROR!]
 WDG Config Error: WdgFastRefreshTime for core [!"$WdgCoreID"!] should be less than WdgInitialTimeout.
[!ENDERROR!]
[!ENDIF!]
[!ENDNOCODE!]
[!ENDMACRO!]

[!/*****************************************************************************
** Name             : Wdg_TimingValidation                                    **
**                                                                            **
** Description      : Macro to validate WDG Ticks                             **
**                                                                            **
*****************************************************************************/!]
/* [cover parentID={7D67D9F8-9B65-421d-83EC-1A647D99CDC0}][/cover] */
[!MACRO "Wdg_TimingValidation", "ReloadValue"="", "WdgTimeNodeName"="","MaxReloadTime"=""!][!//
[!NOCODE!]
[!IF "$ReloadValue > num:i(65536)"!][!//
  [!ERROR!][!//
  WDG Error: The value configured for the parameter [!"$WdgTimeNodeName"!] in the configuration [!"node:name(WdgSettingsConfig/*[@index = $Index])"!] exceeds the 16 bit timer value of watchdog for the configured system clock.
  Maximum time which could be configured for the configured system frequency should be [!"num:i($MaxReloadTime)div num:i(1000)"!] s.
  [!ENDERROR!][!//
[!ELSEIF "$ReloadValue < num:i(1)"!][!//
  [!ERROR!][!//
  WDG Error: The value configured for the parameter [!"$WdgTimeNodeName"!] in the configuration [!"node:name(WdgSettingsConfig/*[@index = $Index])"!] is less than minimum resolution of timer value of watchdog for the configured system clock.
  Minimum time which could be configured for the configured system frequency should be greater than or equal to [!"num:i(1) div num:i(1000)"!] s.
  [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDNOCODE!]
[!ENDMACRO!]


[!/*****************************************************************************
** Name             : Wdg_ValidateGtmChannel                                  **
**                                                                            **
** Description      : Macro to validate GTM SRV                               **
**                                                                            **
*****************************************************************************/!]
/* [cover parentID={231D90EC-1AA7-4dfb-89B2-D0A924C3DF1A}][/cover] */
[!MACRO "Wdg_ValidateGtmChannel", "WdgGtmChannelTemp"="", "WdgCoreID" = ""!][!//
[!NOCODE!]
[!VAR "TempStrng" = "''"!]
[!IF "contains(node:ref($WdgGtmChannelTemp)/*[1],'WDG')"!]
  [!VAR "WdgTimerUnit" = "contains(node:ref($WdgGtmChannelTemp)/*[1],'ATOM')"!]
   [!IF "$WdgTimerUnit = 'true'"!]
    [!/*" ATOM channel Used "*/!]
    [!VAR "GtmWdgModuleNumber" = "substring-after(text:split($WdgGtmChannelTemp,'/')[num:i(6)],'_')"!]
    [!VAR "GtmWdgChannelNumber" = "substring-after(text:split($WdgGtmChannelTemp,'/')[num:i(7)],'_')"!]
    [!VAR "GtmchnlArry" = "concat($GtmchnlArry,'ATOM',$GtmWdgModuleNumber,$GtmWdgChannelNumber,'#')"!]
    [!VAR "TempStrng" = "concat('ATOM',$GtmWdgModuleNumber,$GtmWdgChannelNumber)"!]
    [!VAR "GtmModule" = "'MCU_GTM_TIMER_ATOM'"!]
   [!ELSE!]
    [!/*" TOM channel Used "*/!]
    [!VAR "GtmWdgModuleNumber" = "substring-after(text:split($WdgGtmChannelTemp,'/')[num:i(6)],'_')"!]
    [!VAR "GtmWdgChannelNumber" = "substring-after(text:split($WdgGtmChannelTemp,'/')[num:i(7)],'_')"!]
    [!VAR "GtmchnlArry" = "concat($GtmchnlArry,'TOM',$GtmWdgModuleNumber,$GtmWdgChannelNumber,'#')"!]
    [!VAR "TempStrng" = "concat('TOM',$GtmWdgModuleNumber,$GtmWdgChannelNumber)"!]
    [!VAR "GtmModule" = "'MCU_GTM_TIMER_TOM'"!]
   [!ENDIF!]
  [!VAR "GtmChnlCount" = "$GtmChnlCount + num:i(1)"!][!//
  [!ELSE!]
  [!ERROR!]
   WDG Config Error: GtmTimerUsed in core [!"$WdgCoreID"!] is not referenced to WDG
  [!ENDERROR!]
[!ENDIF!]
[!FOR "LoopCount" = "num:i(2)" TO "num:i($GtmChnlCount)"!]
[!IF "(text:split($GtmchnlArry,'#')[num:i($LoopCount - num:i(1))]) = $TempStrng"!]
[!ERROR!]
 WDG Config Error : Reference for GtmTimerUsed [!"$WdgGtmChannelTemp"!] in core [!"$WdgCoreID"!] is already assigned to other core
[!ENDERROR!]
[!ENDIF!]
[!ENDFOR!]
[!VAR "GtmModuleNo" = "$GtmWdgModuleNumber"!]
[!VAR "GtmChannelNo" = "$GtmWdgChannelNumber"!][!//
[!ENDNOCODE!]
[!ENDMACRO!]


[!/*****************************************************************************
** Name             : Wdg_StmTimerValidation                                  **
**                                                                            **
** Description      : Macro to validate STM allocation in Resource Manager    **
**                                                                            **
*****************************************************************************/!]
/* [cover parentID={6C7F2978-8021-43a8-B603-4D804D3BE1CC}][/cover] */
/* [cover parentID={47F78919-1780-4457-9F21-8A2FC20BC765}][/cover] */
[!MACRO "Wdg_StmTimerValidation", "WdgCoreID" = "", "StmTimerUsed"="", "StmCmpRegUsed" = ""!][!//
[!NOCODE!]
[!SELECT "as:modconf('ResourceM')[1]"!][!//
[!VAR "CoreConfigured" = "num:i(0)"!]
/* [cover parentID={D1BE3760-FBD6-4fcd-B73D-A2A4D94A6F05}]Loop untill the last core available in the list.[/cover] */
[!LOOP "ResourceMMcalConfig/*[1]/ResourceMMcalCore/*"!][!//
    [!VAR "CGCoreID" = "./ResourceMCoreID"!][!//
    [!VAR "RMCoreArry" = "concat($RMCoreArry,$CGCoreID,'#')"!]
    [!VAR "StmConfigured" = "num:i(0)"!]
    /* [cover parentID={002C8076-99E1-455b-BB4E-0DEE9C8DCE29}]If Core Id is equal to Wdg Core Id[/cover] */
    [!IF "$CGCoreID = concat('CORE',num:i($WdgCoreID))"!]
      [!VAR "CoreConfigured" = "num:i(1)"!]
        /* [cover parentID={BB2F1C87-1804-4f61-81EA-BA470209FD43}]If Allocation container is added for that core[/cover] */
        [!IF "node:exists(./ResourceMAllocation/*[1])"!]
                /* [cover parentID={3B344E1A-D3F7-4c55-9914-BBA1F3FEFE3C}]Loop untill last available resource for that core[/cover] */
                [!LOOP "ResourceMAllocation/*"!][!//
                    /* [cover parentID={2B223DEB-22C9-48ef-8287-4D1165F535AE}]If STM timer is allocated to the Core[/cover] */
                    [!IF "'STM' = ./ResourceMModuleName"!]
                    [!VAR "StmConfigured" = "num:i(1)"!]
                      [!VAR "StmTimerUsed" = "text:split(node:value(./ResourceMResourceRef),'_')[3]"!]
                      /* [cover parentID={B3F1B485-7DBE-4de7-ADA5-75114FE5841C}]If Compare registers are allocated to the STM timer in MCU[/cover] */
                      [!IF "(node:value(node:ref(./ResourceMResourceRef)/McuStmCmp0RegAllocationConf) = 'STM_CMP0_USED_BY_WDG')"!]
                        [!VAR "StmCmpRegUsed" = "num:i(0)"!]
                      /* [cover parentID={B3F1B485-7DBE-4de7-ADA5-75114FE5841C}]If Compare registers are allocated to the STM timer in MCU[/cover] */
                      [!ELSEIF "(node:value(node:ref(./ResourceMResourceRef)/McuStmCmp1RegAllocationConf) = 'STM_CMP1_USED_BY_WDG')"!]
                        [!VAR "StmCmpRegUsed" = "num:i(1)"!]
                      [!ELSE!]
                          /* [cover parentID={BED7FF73-B738-4465-971D-07B63013B109}][/cover] */
                          [!ERROR!]
                                WDG Config Error :STM timer [!"$StmTimerUsed"!] compare register is not configured for WDG driver in MCU for CORE[!"$WdgCoreID"!].
                                [!ENDERROR!]
                            [!ENDIF!]
                    [!ELSE!]
                      [!IF "$StmConfigured = num:i(0)"!]
                       [!VAR "StmConfigured" = "num:i(2)"!]     
                      [!ENDIF!]
                  [!ENDIF!][!//
                [!ENDLOOP!][!//
                
                [!IF "$StmConfigured = num:i(2)"!]
                /* [cover parentID={4E4D024F-8B9F-4760-9133-2607C74142A2}][/cover] */
                [!ERROR!][!//
                WDG Config Error : STM timer has to be allocated to [!"$CGCoreID"!] in Resource Manager with a valid reference.
                [!ENDERROR!][!//    
                [!ENDIF!]
        [!ELSE!]
        /* [cover parentID={2324F31F-AFEE-4250-B63C-6E1AB91AA2FD}][/cover] */
        [!ERROR!][!//
        WDG Config Error : STM timer has to be allocated to [!"$CGCoreID"!] in Resource Manager with a valid reference.
        [!ENDERROR!][!//    

      [!ENDIF!]
    [!ELSE!]
      [!VAR "CoreConfigured" = "num:i(0)"!]
  [!ENDIF!]
[!ENDLOOP!][!//
    /* [cover parentID={0A642A70-BF24-4b0c-8053-11E4995FA970}]If the Wdg core Id is present int the array of cores in Resource manager[/cover] */
[!IF "text:match($RMCoreArry,concat('CORE',$WdgCoreID))"!]
[!ELSE!]
/* [cover parentID={DB8E5291-C964-4b2e-9F0F-98D2A9BB92AD}][/cover] */
[!ERROR!]
WDG Config Error : The STM timer is not allocated to CORE[!"$WdgCoreID"!] in Resource Manager.
[!ENDERROR!]
[!ENDIF!]
[!ENDSELECT!][!// 
  
[!ENDNOCODE!]
[!ENDMACRO!]


/*******************************************************************************
** Name             : Wdg_ConfigGetGtmParams                                  **
**                                                                            **
** Description      : This macro generates ticks for the GTM timer            **
*******************************************************************************/
[!MACRO "Wdg_ConfigGetGtmParams","GtmChannelRef"= "","GtmTimePeriod"="","GtmTimerContainer"="",
"GtmClockRef"="","GtmTimerTicks"=""!][!//
[!NOCODE!][!//

[!VAR "GtmTimerType" = "substring-before(substring-after(text:split(($GtmChannelRef),'/')[6],'McuGtm'),'AllocationConf')"!]
[!VAR "GtmTimerType" = "text:toupper($GtmTimerType)"!]
[!VAR "GtmTimerModNo" = "substring-after(text:split($GtmChannelRef,'/')[num:i(5)],'_')"!]
[!VAR "GtmTimerChNo" = "text:split($GtmChannelRef,'ChannelAllocationConf_')[2]"!]

/* [cover parentID={88855C8A-B48C-40bc-9899-0446701AD3D8}]If GtmTimePeriod not equal to ZERO[/cover] */
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
  /* [cover parentID={4CF88CC6-91A6-4e50-A775-26968C9A36EE}]Cluster0 is Disabled or ClusterX is Disabled[/cover] */
  [!IF "$GtmCluster0Divider = 'CLS_CLK_CFG_DISABLED_SEL0' or $GtmClusterXDivider = 'CLS_CLK_CFG_DISABLED_SEL0'"!]
      /* [cover parentID={0E6E5503-83D8-44db-A5FB-6DE3F0FBE897}][/cover] */
      /* [cover parentID={1E5D0365-EE8E-4cf6-ABA1-9912DA353D62}][/cover] */
      /* [cover parentID={2E66F873-D3DE-4009-A672-597569F41414}][/cover] */
      /* [cover parentID={8B822DC5-3FB6-4580-AC72-4AD4B31EF9A6}][/cover] */
      /* [cover parentID={9C448473-F47A-4e4a-A08D-A4E9C6D32F11}][/cover] */
      /* [cover parentID={57711CB6-9010-4903-8139-3579A6C017E5}][/cover] */
      /* [cover parentID={B9FF9343-5C07-4af8-89DB-C68E491C7412}][/cover] */
      /* [cover parentID={A71B49A1-389F-42d0-8904-1B45A7134C84}]Generate Error: GTM Cluster level divider is OFF[/cover] */
    [!ERROR!]
      WDG Code Generator: GTM cluster level divider (GtmCmuClusterInputClockDividerEnable) is swiched off of Cluster0 or Cluster[!"$GtmTimerModNo"!].
    [!ENDERROR!]
  [!ENDIF!]
  /* [cover parentID={FF7FAD7D-D1B4-40b8-8A3C-228D97284183}]Calculate the Gtm Frequency based on Clustor divider value[/cover] */
  [!VAR "fGtm"="num:f(num:f($fGtm) div num:f($GtmClusterDivVal))"!]
  [!VAR "ChannelClkDiv"="node:value(node:ref($GtmTimerContainer)/GtmTimerClockSelect)"!][!//Clock divider used by the channel

  [!VAR "ClockType" ="num:i(0)"!]
  [!VAR "ClockId" ="num:i(255)"!]
  /* [cover parentID={76C04DE7-160F-4afd-9FAA-50E7C5435EF4}]If GTM Timer Container contains Configurable or GTM Channel Clock Divider contains Configurable[/cover] */
  [!IF "contains($ChannelClkDiv,'_CONFIGURABLE_')= 'true'"!][!//ATOM channel using a configurable clock
    /* [cover parentID={3D38FF96-2FAA-4168-9FA3-0D4FCCCA6F08}]Retrieve the config clock Id from Channel clock divider[/cover] */
    [!VAR "ConfigClkId" = "text:split($ChannelClkDiv,'_')[4]"!]
    [!SELECT "node:ref($McuModuleConfig)/GtmGlobalConfiguration/*[1]/GtmClusterConf/*[@name=$GtmClusterNodeName]"!][!//Select the GTM Cluster
    [!VAR "TempNodeName"= "concat('./GtmClusterConfClockSetting/','GtmClusterConfClock',$ConfigClkId,'Src')"!][!//Clock Source select node for config clock in GTM cluster
    /* [cover parentID={EBBCB644-655D-419d-A512-C1B580C65B34}]If Configured Clock Source contains CLOCK8_SEL1[/cover] */
    [!IF "contains(node:value($TempNodeName),'CLOCK8_SEL1')"!]
      /* [cover parentID={4BB02822-43E9-44bc-A096-F1A9423180DA}]Retrieve Clock Id and Clock Type[/cover] */
      [!VAR "ClockId"="num:i(8)"!]
      [!VAR "ClockType"="'CONF_CLOCK'"!]
    /* [cover parentID={870D8289-C315-48ed-82D8-678A3F63DFC0}]If Configured Clock Source contains _SEL0[/cover] */
    [!ELSEIF "contains(node:value($TempNodeName),'_SEL0')"!]
      /* [cover parentID={FE520AAB-83FD-4526-BC75-B0DF220E8038}]Retrieve the Clock Id and Clock Type[/cover] */
      [!VAR "ClockId"="num:i($ConfigClkId)"!]
      [!VAR "ClockType"="'CONF_CLOCK'"!]
    [!ELSE!]
      /* [cover parentID={0E6E5503-83D8-44db-A5FB-6DE3F0FBE897}][/cover] */
      /* [cover parentID={1E5D0365-EE8E-4cf6-ABA1-9912DA353D62}][/cover] */
      /* [cover parentID={2E66F873-D3DE-4009-A672-597569F41414}][/cover] */
      /* [cover parentID={8B822DC5-3FB6-4580-AC72-4AD4B31EF9A6}][/cover] */
      /* [cover parentID={9C448473-F47A-4e4a-A08D-A4E9C6D32F11}][/cover] */
      /* [cover parentID={57711CB6-9010-4903-8139-3579A6C017E5}][/cover] */
      /* [cover parentID={B9FF9343-5C07-4af8-89DB-C68E491C7412}][/cover] */
      [!ERROR!]
      WDG Code Generator: Unable to calculate the clock frequency for the GTM timer cell at NODE: NODE: [!"node:path(.)"!]/[!"text:split($GtmTimerContainer,'/')[2]"!]. Please enter the CM0 ticks directly in GtmTimerCM0Ticks parameter
      [!ENDERROR!]
    [!ENDIF!]
    [!ENDSELECT!]
   /* [cover parentID={DC7A8957-5C46-4c23-9017-3F77EBD8A8B3}]If GTM Timer Container or Gtm Timer Clock Selects contains Fixed[/cover] */
  [!ELSEIF "contains($ChannelClkDiv,'_FIXED_')= 'true'"!][!//TOM channel using a fixed clock
    [!SELECT "node:ref($McuModuleConfig)/GtmGlobalConfiguration/*[1]/GtmClusterConf/*[@name=$GtmClusterNodeName]"!]
    /* [cover parentID={D7BB7CD3-1E27-40c4-8CE0-50DEB3ABEE40}]If Configured Clock Source contains with CLOCK8_SEL1 and ChannelClockDivider is GTM_FIXED_CLOCK_0[/cover] */
    [!IF "(contains(node:value(./GtmClusterFixedClockSetting/GtmClusterFixedClockSrc),'CLOCK8_SEL1') = 'true') and
          ($ChannelClkDiv = 'GTM_FIXED_CLOCK_0')"!]
      /* [cover parentID={46B83845-E8F3-4329-84C7-7B9AA06C7B90}]Retrieve the Gtm Cmu FixedClock Selection[/cover] */
      [!VAR "ClockId"="num:i(8)"!]
      [!VAR "ClockType"="'CONF_CLOCK'"!]
    [!ELSE!]
      [!VAR "ClockId"="num:i(0)"!]
      [!VAR "ClockType"="'FIXED_CLOCK'"!]
    [!ENDIF!]
    /* [cover parentID={0C4E6C86-67B1-46f8-BF3B-9B9EAA7CF9D4}]If GtmCmuFixedClockEnable is False[/cover] */
    [!IF "../../../*[1]/McuGtmClockManagementConf/GtmFixedClockSetting/GtmCmuFixedClockEnable = 'false'"!]
      /* [cover parentID={0E6E5503-83D8-44db-A5FB-6DE3F0FBE897}][/cover] */
      /* [cover parentID={1E5D0365-EE8E-4cf6-ABA1-9912DA353D62}][/cover] */
      /* [cover parentID={2E66F873-D3DE-4009-A672-597569F41414}][/cover] */
      /* [cover parentID={8B822DC5-3FB6-4580-AC72-4AD4B31EF9A6}][/cover] */
      /* [cover parentID={9C448473-F47A-4e4a-A08D-A4E9C6D32F11}][/cover] */
      /* [cover parentID={57711CB6-9010-4903-8139-3579A6C017E5}][/cover] */
      /* [cover parentID={B9FF9343-5C07-4af8-89DB-C68E491C7412}][/cover] */
      [!ERROR!]
        WDG Code Generator: McuGtmClockManagementConf/GtmFixedClockSetting/GtmCmuFixedClockEnable cannot be false when fixed clock is used.
      [!ENDERROR!]
    [!ENDIF!]
    [!ENDSELECT!]
  [!ELSE!]
      /* [cover parentID={0E6E5503-83D8-44db-A5FB-6DE3F0FBE897}][/cover] */
      /* [cover parentID={1E5D0365-EE8E-4cf6-ABA1-9912DA353D62}][/cover] */
      /* [cover parentID={2E66F873-D3DE-4009-A672-597569F41414}][/cover] */
      /* [cover parentID={8B822DC5-3FB6-4580-AC72-4AD4B31EF9A6}][/cover] */
      /* [cover parentID={9C448473-F47A-4e4a-A08D-A4E9C6D32F11}][/cover] */
      /* [cover parentID={57711CB6-9010-4903-8139-3579A6C017E5}][/cover] */
      /* [cover parentID={B9FF9343-5C07-4af8-89DB-C68E491C7412}][/cover] */
    [!ERROR!]
      WDG Code Generator: Incorrect clock divider selected for [!"$GtmTimerContainer"!]
    [!ENDERROR!]
  [!ENDIF!]
  [!SELECT "node:ref($McuModuleConfig)/GtmGlobalConfiguration/*[1]/McuGtmClockManagementConf"!]
  /* [cover parentID={01EF2135-2F45-4aaf-A33E-A75A38F75F31}]Clock type is FIXED_CLOCK[/cover] */
  [!IF "$ClockType = 'FIXED_CLOCK'"!]
    /* [cover parentID={46B83845-E8F3-4329-84C7-7B9AA06C7B90}]Retrieve the Gtm Cmu FixedClock Selection[/cover] */
    [!VAR "TempNodeValue"="GtmFixedClockSetting/GtmCmuFixedClockSel"!]
    /* [cover parentID={B2F959A3-E355-4c0f-AA0A-D12A1375CDDD}]If Configurable clock is the source of fixed clock[/cover] */
    [!IF "$TempNodeValue != 'CMU_GLOBAL_CLOCK_SEL0'"!][!// Configurable clock is the source of fixed clock
      /* [cover parentID={CCD1F3F3-EFB3-4f7c-9C3E-7B8D934E1074}]Retrieve Cmu Clock Id[/cover] */
      [!VAR "CmuClkId" = "text:split(text:split($TempNodeValue,'_')[2],'CLOCK')[1]"!]
      [!VAR "TempNodeName"= "concat('./GtmConfigClockSetting/','GtmCmuConfigClock',$CmuClkId,'Enable')"!]
      [!IF "node:value($TempNodeName) != 'true'"!]
      /* [cover parentID={0E6E5503-83D8-44db-A5FB-6DE3F0FBE897}][/cover] */
      /* [cover parentID={1E5D0365-EE8E-4cf6-ABA1-9912DA353D62}][/cover] */
      /* [cover parentID={2E66F873-D3DE-4009-A672-597569F41414}][/cover] */
      /* [cover parentID={8B822DC5-3FB6-4580-AC72-4AD4B31EF9A6}][/cover] */
      /* [cover parentID={9C448473-F47A-4e4a-A08D-A4E9C6D32F11}][/cover] */
      /* [cover parentID={57711CB6-9010-4903-8139-3579A6C017E5}][/cover] */
      /* [cover parentID={B9FF9343-5C07-4af8-89DB-C68E491C7412}][/cover] */
      /* [cover parentID={0543E0A3-2CAF-4e1c-BE12-3EBAE8978308}]If Cmu Clock Id is Enabled [/cover] */
      [!ERROR!]
       WDG Code Generator:Configurable clock [!"$CmuClkId"!] is not enabled. Enable configurable clock via [!"$TempNodeName"!]
      [!ENDERROR!]
      [!ENDIF!]
      [!VAR "TempNodeName"= "concat('./GtmConfigClockSetting/','GtmCmuConfigClock',$CmuClkId,'Div')"!]
      [!VAR "ClockDivider"="num:i(node:value($TempNodeName)+1)"!]
      /* [cover parentID={2B89708A-D9B9-4786-9A2A-3D48F5FA1D88}]Calculate the Gtm Frequency using the Clock Divider Value[/cover] */
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
  /* [cover parentID={0015804A-C7DA-4c60-A010-6A8C243816AF}]If Clock type is Configurable and ClockId is less than 8[/cover] */
  [!ELSEIF "$ClockType = 'CONF_CLOCK' and ($ClockId < num:i(8))"!]
    [!VAR "TempNodeName"= "concat('./GtmConfigClockSetting/','GtmCmuConfigClock',$ClockId,'Enable')"!]
    /* [cover parentID={F654DAF6-CDDC-45e9-8870-E857E767EB8D}]If Cmu Clock Id is Enabled[/cover] */
    [!IF "node:value($TempNodeName) != 'true'"!]
      /* [cover parentID={0E6E5503-83D8-44db-A5FB-6DE3F0FBE897}][/cover] */
      /* [cover parentID={1E5D0365-EE8E-4cf6-ABA1-9912DA353D62}][/cover] */
      /* [cover parentID={2E66F873-D3DE-4009-A672-597569F41414}][/cover] */
      /* [cover parentID={8B822DC5-3FB6-4580-AC72-4AD4B31EF9A6}][/cover] */
      /* [cover parentID={9C448473-F47A-4e4a-A08D-A4E9C6D32F11}][/cover] */
      /* [cover parentID={57711CB6-9010-4903-8139-3579A6C017E5}][/cover] */
      /* [cover parentID={B9FF9343-5C07-4af8-89DB-C68E491C7412}][/cover] */
      [!ERROR!]
       WDG Code Generator:Configurable clock [!"$ClockId"!] is not enabled. Enable configurable clock via [!"$TempNodeName"!]
      [!ENDERROR!]
    [!ENDIF!]
    [!VAR "TempNodeName"= "concat('./GtmConfigClockSetting/','GtmCmuConfigClock',$ClockId,'Div')"!]
    [!VAR "ClockDivider"="num:i(node:value($TempNodeName)+1)"!]
    [!VAR "fGtm" = "$fGtm div $ClockDivider"!]
    /* [cover parentID={883859E8-F31C-4ef2-8DD6-4B31BD780999}]Clock type is Configurable and ClockId is equal to 8[/cover] */
  [!ELSEIF "$ClockType = 'CONF_CLOCK' and ($ClockId = num:i(8))"!]
    /* [cover parentID={83C6A1D2-2C48-4dee-842F-4B1033841753}]Scu Gtm frequency as Gtm Frequency [/cover] */
    [!VAR "fGtm" = "$fScuGtm"!]
  [!ELSE!]
    [!ERROR!]
      /* [cover parentID={0E6E5503-83D8-44db-A5FB-6DE3F0FBE897}][/cover] */
      /* [cover parentID={1E5D0365-EE8E-4cf6-ABA1-9912DA353D62}][/cover] */
      /* [cover parentID={2E66F873-D3DE-4009-A672-597569F41414}][/cover] */
      /* [cover parentID={8B822DC5-3FB6-4580-AC72-4AD4B31EF9A6}][/cover] */
      /* [cover parentID={9C448473-F47A-4e4a-A08D-A4E9C6D32F11}][/cover] */
      /* [cover parentID={57711CB6-9010-4903-8139-3579A6C017E5}][/cover] */
      /* [cover parentID={B9FF9343-5C07-4af8-89DB-C68E491C7412}][/cover] */
     WDG Code Generator:Unable to calculate the clock frequency for the GTM timer cell at NODE: [!"node:path(.)"!]/[!"text:split($GtmTimerContainer,'/')[2]"!]. Please enter the CM0 ticks directly in GtmTimerCM0Ticks parameter
    [!ENDERROR!]
  [!ENDIF!]
  [!ENDSELECT!]
  /* [cover parentID={7D9E4582-E598-4db7-8716-11D881BD10A7}]Calculate the Gtm Timer Ticks[/cover] */
  [!VAR "GtmTimerTicks" = "num:i((num:f($GtmTimePeriod) * num:f($fGtm)) div num:i(1000))"!]
[!ENDIF!]
/* [cover parentID={EF34CB62-0958-4f4f-AE0D-8920B82FFA62}]If GtmTimerType isTOM[/cover] */
[!IF "$GtmTimerType = 'TOM'"!][!//
  /* [cover parentID={AB1D891F-213C-4802-9BBF-C767489A29AB}]If GtmTimerTicks is greater than 65534[/cover] */
  [!IF "$GtmTimerTicks > num:i(65534)"!]
     /* [cover parentID={0E6E5503-83D8-44db-A5FB-6DE3F0FBE897}][/cover] */
      /* [cover parentID={1E5D0365-EE8E-4cf6-ABA1-9912DA353D62}][/cover] */
      /* [cover parentID={2E66F873-D3DE-4009-A672-597569F41414}][/cover] */
      /* [cover parentID={8B822DC5-3FB6-4580-AC72-4AD4B31EF9A6}][/cover] */
      /* [cover parentID={9C448473-F47A-4e4a-A08D-A4E9C6D32F11}][/cover] */
      /* [cover parentID={57711CB6-9010-4903-8139-3579A6C017E5}][/cover] */
      /* [cover parentID={B9FF9343-5C07-4af8-89DB-C68E491C7412}][/cover] */
    [!ERROR!]
      WDG Code Generator:Timer ticks calculates is beyond 65534 for the NODE: [!"node:path(.)"!]/[!"text:split($GtmTimerContainer,'/')[2]"!]. Reduce TimePeriod or Timer frequency.
    [!ENDERROR!]
  [!ENDIF!]
/* [cover parentID={7471B14B-9351-4bb6-B75B-A71B8F377F4D}]If Gtm Timer Type is ATOM[/cover] */
[!ELSEIF "$GtmTimerType = 'ATOM'"!][!//
  /* [cover parentID={5F4F7042-A22A-4cf9-BD0F-D92CBA5FC503}]If GtmTimerTicks is greater than 16777214[/cover] */
  [!IF "$GtmTimerTicks > num:i(16777214)"!]
      /* [cover parentID={0E6E5503-83D8-44db-A5FB-6DE3F0FBE897}][/cover] */
      /* [cover parentID={1E5D0365-EE8E-4cf6-ABA1-9912DA353D62}][/cover] */
      /* [cover parentID={2E66F873-D3DE-4009-A672-597569F41414}][/cover] */
      /* [cover parentID={8B822DC5-3FB6-4580-AC72-4AD4B31EF9A6}][/cover] */
      /* [cover parentID={9C448473-F47A-4e4a-A08D-A4E9C6D32F11}][/cover] */
      /* [cover parentID={57711CB6-9010-4903-8139-3579A6C017E5}][/cover] */
      /* [cover parentID={B9FF9343-5C07-4af8-89DB-C68E491C7412}][/cover] */
      /* [cover parentID={CC244B2F-0218-406d-B854-F5F792554356}][/cover] */
    [!ERROR!]
     WDG Code Generator: Timer ticks calculated is beyond 16777214 for the NODE: [!"node:path(.)"!]/[!"text:split($GtmTimerContainer,'/')[2]"!]. Reduce TimePeriod or Timer frequency.
    [!ENDERROR!]
  [!ENDIF!][!//
[!ELSE!][!//
      /* [cover parentID={0E6E5503-83D8-44db-A5FB-6DE3F0FBE897}][/cover] */
      /* [cover parentID={1E5D0365-EE8E-4cf6-ABA1-9912DA353D62}][/cover] */
      /* [cover parentID={2E66F873-D3DE-4009-A672-597569F41414}][/cover] */
      /* [cover parentID={8B822DC5-3FB6-4580-AC72-4AD4B31EF9A6}][/cover] */
      /* [cover parentID={9C448473-F47A-4e4a-A08D-A4E9C6D32F11}][/cover] */
      /* [cover parentID={57711CB6-9010-4903-8139-3579A6C017E5}][/cover] */
      /* [cover parentID={B9FF9343-5C07-4af8-89DB-C68E491C7412}][/cover] */
      /* [cover parentID={14A574CC-4B7B-4600-89EB-E18B648B3EA6}]Generate Error[/cover] */
  [!ERROR!]
   WDG Code Generator: Undeterminable Timer Type at NODE: [!"node:path(.)"!]/[!"text:split($GtmTimerContainer,'/')[2]"!].
  [!ENDERROR!]
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!/*******************************************************************************
** Name             : Wdg_ReloadValue                                         **
**                                                                            **
** Description      : Macro to calculate WDG reload value                     **
**                                                                            **
*******************************************************************************/!]
[!MACRO "Wdg_ReloadValue", "SystemClockVal" = "", "TimeoutVal"="", "ClockDivider"="", "ReloadValue"=""!]
[!NOCODE!]
[!VAR "Numerator_ReloadValue" = "(num:i($SystemClockVal)*$TimeoutVal) div 1000.0"!]
[!VAR "ReloadValue" = "num:i(ceiling($Numerator_ReloadValue div $ClockDivider))"!]
[!ENDNOCODE!]
[!ENDMACRO!]
/*******************************************************************************
** Name             : Wdg_MaxReloadTime                                       **
**                                                                            **
** Description      : Macro to calculate max reload time for WDG              **
**                                                                            **
*******************************************************************************/
[!//
[!MACRO "Wdg_MaxReloadTime", "SystemClockVal" = "", "ClockDivider"="", "MaxReloadTime"=""!]
[!NOCODE!]
[!VAR "Numerator_MaxReloadTime" = "num:i(65536)* num:i($ClockDivider)"!]
[!VAR "Denominator_MaxReloadTime" = "num:i($SystemClockVal) div 1000.0"!]
[!VAR "MaxReloadTime" = "$Numerator_MaxReloadTime div $Denominator_MaxReloadTime"!]
[!ENDNOCODE!]
[!ENDMACRO!]


[!ENDIF!][!// IF "not(var:defined('WDG_17_M'))