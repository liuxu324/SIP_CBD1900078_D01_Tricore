ECHO OFF

set LM_LICENSE_FILE=7594@blrla042.blr.infineon.com
set RLM_LICENSE=7594@sinlal01.sin.infineon.com
set WRSD_LICENSE_FILE=4230@blrla042.blr.infineon.com
set TSK_LICENSE_KEY_SW160800=6dfa-5f5c-946c-4277
set TSK_LICENSE_SERVER=sinlal01.sin.infineon.com:9090;vihlal21.vih.infineon.com:9090
set GHS_LMHOST=blrla042.blr.infineon.com
set GHS_LMPORT=2009
SET HIGHTEC_LM=C:\sofit\aurix2g_sw_mcal\hightec\licensemanager
set TSK_NO_ANONYMOUS=1
set BINUTILS_PATH=C:\sofit\aurix2g_sw_mcal\bifaces\bin
set PATH=%BINUTILS_PATH%;%PATH%
set PATH=%PATH%;C:\sofit\aurix2g_sw_mcal\hightec\licensemanager
SET PERL_LIB_PATH=C:\sofit\aurix2g_sw_mcal\perl\c\bin
SET MAKECMD_WITH_APP= "SW framework Tools" 
SET BUILDENV=DEV
 
REM -----------------------------------------------------
SET PATH=%BINUTILS_PATH%;%PERL_LIB_PATH%;%HIGHTEC_LM%;%PATH%

START %MAKECMD_WITH_APP%
EXIT
