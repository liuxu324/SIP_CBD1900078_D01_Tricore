@ECHO OFF
REM ****************************************************************************
REM *                                                                         **
REM * Copyright (C) Infineon Technologies (2016)                              **
REM *                                                                         **
REM * All rights reserved.                                                    **
REM *                                                                         **
REM * This document contains proprietary information belonging to Infineon    **
REM * Technologies. Passing on and copying of this document, and communication**
REM * of its contents is not permitted without prior written authorization.   **
REM *                                                                         **
REM ****************************************************************************
REM *                                                                         **
REM *  FILENAME  : DemoAppBuild.bat                                           **
REM *                                                                         **
REM *  VERSION   : 1.0.0                                                      **
REM *                                                                         **
REM *  DATE      : 2016.10.04                                                 **
REM *                                                                         **
REM *  PLATFORM  : Infineon AURIX2G                                           **
REM *                                                                         **
REM *  AUTHOR    : DL-AUTOSAR-Engineering                                     **
REM *                                                                         **
REM *  VENDOR    : Infineon Technologies                                      **
REM *                                                                         **
REM *  DESCRIPTION  : This file builds MCAL Demo Applications                 **
REM *                                                                         **
REM *  MAY BE CHANGED BY USER [yes\no]: YES                                   **
REM *                                                                         **
REM ***************************************************************************\

@ECHO OFF
REM ****************************************************************************
REM  Get Root Path
REM ****************************************************************************
set BINUTILS_PATH=..\..\..\Tools\Bifaces\bin
set PATH=%BINUTILS_PATH%;%PATH%
set PATH=%PATH%;C:\sofit\aurix2g_sw_mcal\hightec\licensemanager
SET BUILDENV=DEMOAPP
SET BUILD_DEMOAPP_PACKAGE=1
SET WITHOUT_TRESOS_WITHOUT_FR=0

REM ****************************************************************************
REM Get the Compiler and Tresos Installation Path
REM ***************************************************************************
IF "%1" == "" SET COMPILER=Tasking
IF "%1" == "TASKING" SET COMPILER=Tasking
IF "%1" == "GNU" SET COMPILER=Gnuc
IF "%1" == "DCC" SET COMPILER=Dcc
IF "%1" == "GHS" (
	ECHO Sorry, GHS compiler not supported for this Release
	PAUSE
	EXIT /B
)

IF "%COMPILER%" == "Tasking" SET B_Tasking_COMPILER_PATH=C:/sofit/aurix2g_sw_mcal/tasking/ctc/bin
IF "%COMPILER%" == "Gnuc" SET B_Gnuc_COMPILER_PATH=C:/sofit/aurix2g_sw_mcal/hightec/toolchains/tricore/v4.9.2.0/bin
IF "%COMPILER%" == "Dcc" SET B_DCC_TRICORE_PATH=C:/sofit/aurix2g_sw_mcal/windriver/compilers/diab-5.9.6.4/WIN32

IF "%2" == "" SET TRESOS_BUILD=YES
IF "%2" == "WITHOUT_TRESOS" SET TRESOS_BUILD=NO
IF "%2" == "WITHOUT_TRESOS_WITHOUT_FR" ( 
	SET WITHOUT_TRESOS_WITHOUT_FR=1
	SET TRESOS_BUILD=NO
)	
IF "%2" == "WITH_TRESOS" SET TRESOS_BUILD=YES

IF "%3" == "" SET TRESOS_BIN_PATH=C:/sofit/aurix2g_sw_mcal/tresos/tresos/bin
IF NOT "%3" == "" SET TRESOS_BIN_PATH=%3

IF NOT "%4" == "" SET B_%COMPILER%_COMPILER_PATH=%4

REM Copy the Config.xml file for DemoApp
xcopy /y ..\..\..\Tools\Compiler_Configs\TC38A_Config_%COMPILER%.xml 1_ToolEnv\0_Build\1_Config\Config.xml
make all

PAUSE

