<?php
/**----------------------------------------------------------------------------
 * \file Architecture.php
 * \brief Class definitions for BIFACES tools
 *
 * \copyright Copyright (c) 2015-2017 Infineon Technologies AG. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation.
 *   and/or other materials provided with the distribution.
 * - Neither the name of the copyright holders nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *   
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * To improve the quality of the software, users are encouraged to share
 * modifications, enhancements or bug fixes with Infineon Technologies AG 
 * (support@infineon.com).
 *
 * ----------------------------------------------------------------------------
 */
 
namespace MakeGen;

require_once ('/../../Bifaces/Scripts/MakeGen/MakeGen.php');
require_once ('IfxSwFw_GlobalVar.php');

use MakeGen\Main;

print(" ______________________________________________________________________" . PHP_EOL);
print("!!!                            IMPORTANT                             !!!" . PHP_EOL);
print("! You are using BIFACES with a project that was made for               !" . PHP_EOL);
print("! Software Framework!                                                  !" . PHP_EOL);
print("! Please note that, all features may not work.                         !" . PHP_EOL);
print("! Backward compatibility for Software Framework would be removed with  !" . PHP_EOL);
print("! next releases of BIFACES.                                            !" . PHP_EOL);
print("!______________________________________________________________________!" . PHP_EOL);

IfxSwFw_GenMake_Generate($argv[1]);

function IfxSwFw_GenMake_Generate($commandString)
{
	global $targetCpuDefaultCompiler;
	global $targetCpuSecondCompiler;
	global $targetCpuThirdCompiler;
	
	$parameters= explode(";", $commandString);							//Separate the input text to an array of commands

	$targetCpuDefault="Tricore";
	$targetCpuSecond="";
	$targetCpuThird="";
	$targetCpuSpecial="";
	$makeTemplateFilePath="";
	$useFilePattern="";
	$discardFilePattern="";
	$externalSrcFolders="";
	
	$error= false;
	
	foreach ($parameters as $parameter)
	{
		// Check if the command is empty
		if($parameter!="")
		{
			$tempParameter= explode("=",$parameter);					//Separate the parameter property and its value
			$property=trim($tempParameter[0]);
			$value=trim($tempParameter[1]);
			switch($property)
			{
				case "DEFAULT_TARGET_TYPE":
					$targetCpuDefault= trim($value);
					break;
	
				case "SECOND_TARGET_TYPE":
					$targetCpuSecond= trim($value);
					break;
						
				case "THIRD_TARGET_TYPE":
					$targetCpuThird= trim($value);
					break;
						
				case "SPECIAL_TARGET_TYPE":
					$targetCpuSpecial= trim($value);
					break;
						
				case "TOOLCHAIN_FOR_DEFAULT_TARGET":
					$targetCpuDefaultCompiler= trim($value);
					break;
	
				case "TOOLCHAIN_FOR_SECOND_TARGET":
					$targetCpuSecondCompiler= trim($value);
					break;
						
				case "TOOLCHAIN_FOR_THIRD_TARGET":
					$targetCpuThirdCompiler= trim($value);
					break;
	
				case "MAKETEMPLATE_FILE_PATH":
					$makeTemplateFilePath= trim($value);
					break;
						
				case "USE_FILE_PATTERN":
					$useFilePattern= trim($value);
					break;
						
				case "DISCARD_FILE_PATTERN":
					$discardFilePattern= trim($value);
					break;
						
				case "EXTERNAL_SRC_FOLDERS":
					$externalSrcFolders= trim($value);
					break;
						
				default:
					break;
			}
		}
	}
	
	if($targetCpuDefault === "") $targetCpuDefault= "Tricore";
	
	$configXmlArch= constructArchitectureDefault($targetCpuDefault, $targetCpuDefaultCompiler);
	
	if($targetCpuSecond !== "")
	{
		if($targetCpuSecondCompiler !== "")
		{
			$configXmlArch.= PHP_EOL . constructArchitectureSecond($targetCpuSecond, $targetCpuSecondCompiler);
		}
		else
		{
			print("ERROR: Compiler for \"CORETYP_SECOND\" is not configured!" . PHP_EOL);
			$error= true;
		}
	}
	
	if($targetCpuThird !== "")
	{
		if($targetCpuThirdCompiler !== "")
		{
			$configXmlArch.= PHP_EOL . constructArchitectureThird($targetCpuThird, $targetCpuThirdCompiler);
		}
		else
		{
			print("ERROR: Compiler for \"CORETYP_SECOND\" is not configured!" . PHP_EOL);
			$error= true;
		}
	}
	
	if($externalSrcFolders !== "")
	{
		$configXmlExtFolder= "
    <sourceFolder paths= \"" . $externalSrcFolders . "\"/>";
	}
	
	$configXmlTemplate="
    <templatefiles path= \"" . getenv('BINUTILS_PATH') . "/../php/Templates\"/>";
	
	$configXmlSpecificInc="
    <specificInclude internalPaths= \"#^.*/(?:1_SrvSw|2_CDrv|3_Os|4_McHal|_Utilities|Tricore|)$#\" />
    <specificInclude externalPaths= \"$(B_GEN_OUT_FOLDER_TRICORE)/Mcs_Files/0_Src/BaseSw/iLLD/TC39A/Mcs\"/>";
	
	// Selection configurations
	// Use and discard file patterns for project
	$projLevelSelection= "";
	if($useFilePattern !== "")
	{
		$projLevelSelection.= "
        <use files=\"" . $useFilePattern . "\"/>";
	}
	
	if($discardFilePattern !== "")
	{
		$projLevelSelection.= "
        <discard files=\"" . $discardFilePattern . "\"/>";
	}		
	
	$defaultTargetSelection= "";
	$secondTargetSelection= "";
	$thirdTargetSelection= "";
	$specialTargetSelection= "";
	
	if($targetCpuSecond !== "")
	{
		$defaultTargetSelection.= "
            <discard files=\"*/" . $targetCpuSecond . "/*\"/>";
		
		$secondTargetSelection.= "
        <selection>
            <use files=\"*/" . $targetCpuSecond . "/*\"/>
            <assign targets= \"Arm/" . $targetCpuSecond . "\"/>
        </selection>";
	}
	
	if($targetCpuThird !== "")
	{
		$defaultTargetSelection.= "
            <discard files=\"*/" . $targetCpuThird . "/*\"/>";
		
		$thirdTargetSelection.= "
        <selection>
	        <use files=\"*/" . $targetCpuThird . "/*\"/>
	        <assign targets= \"8051/" . $targetCpuThird . "\"/>
        </selection>";
	}
	
	if($targetCpuSpecial !== "")
	{
		$defaultTargetSelection.= "
            <discard files=\"*/" . $targetCpuSpecial . "/*\"/>";
		
		$specialTargetSelection.= "
        <selection>
	        <use files=\"*/" . $targetCpuSpecial . "/*\"/>
	        <assign targets=\"" . $targetCpuDefault . "/Tc\" tools= \"" . $targetCpuDefault . "/"  . $targetCpuSpecial . "/Asm\" />
        </selection>";
	}
	
	// Check if there are some selection configurations required for default cpu
	if($defaultTargetSelection !== "")
	{
		$defaultTargetSelection="
        <selection>" .
	$defaultTargetSelection . "
            <assign targets= \"" . $targetCpuDefault . "/Tc\"/>
        </selection>";
	}
	
	
	$targetSelection= $defaultTargetSelection . $secondTargetSelection . $thirdTargetSelection . $specialTargetSelection;
	
	$selection= $projLevelSelection . $targetSelection;
	
	$configXmlFilePattern="";
	if($selection !== "")
	{
		$configXmlFilePattern="
    <selection>" .
	$selection . "
    </selection>";
	}
	
	$cliParam[]="-d";
	$cliParam[]= "<root>" .
			PHP_EOL .
			$configXmlArch .
			$configXmlFilePattern .
			$configXmlExtFolder .
			$configXmlTemplate .
			$configXmlSpecificInc .
			PHP_EOL .
			"</root>";
	
	//print($cliParam[1] . PHP_EOL);
	$makeFileFolderPath= "1_ToolEnv/0_Build/9_Make";
	if(!file_exists($makeFileFolderPath))
	{
		//if not, create it
		mkdir($makeFileFolderPath, 0777, true);	// the number 0777 provides access "Everything" to "All users" and true for recursive mkdir
	}
	$configFileHandle = fopen($makeFileFolderPath . "/Config.xml", 'w');
	fwrite($configFileHandle, $cliParam[1]);
	fclose($configFileHandle);
	
	if($error === false)
	{
		$main= new Main($cliParam);
		
		copy($makeFileFolderPath . "/Project.mk", $makeFileFolderPath . "/0_Src.mk");
		
		// Merge include paths files
		$fileContent="";
		$incPathListFileHandle = fopen($makeFileFolderPath . "/cIncludePathList.opt", 'w');
		foreach($main->projectData->getArchitectureNames() as $archName)
		$fileContent .= file_get_contents($makeFileFolderPath . "/" . $archName . "_IncludePathList.opt");
		fwrite($incPathListFileHandle, $fileContent);
		fclose($incPathListFileHandle);
	}
	
	//print(constructToolchainDefaultGnuc());
}

function constructArchitectureDefault($targetName, $toolchainName)
{
	$configXmlString=
"   <architecture name=\"" . $targetName . "\" primaryToolchain= \"" . $toolchainName . "\" enable=\"true\">
        <target name=\"Tc\" enable= \"true\">
            <output type=\"elf\" enable=\"true\" fileName=\"$(PROJ_NAME)_$(CORETYP_MAIN).elf\" tool=\"Linker\"/>
            <output type=\"hex\" enable=\"true\" fileName=\"$(PROJ_NAME)_$(CORETYP_MAIN).hex\" tool=\"Hex\">
                <input siblingTypes= \"elf\"/>
            </output>
            <output type=\"srec\" enable=\"true\" fileName=\"$(PROJ_NAME)_$(CORETYP_MAIN).srec\" tool=\"Srec\">
                <input siblingTypes= \"elf\"/>
            </output>
            <output type=\"lib\" enable=\"true\" fileName=\"$(PROJ_NAME)_$(CORETYP_MAIN).a\" tool=\"Archiver\"/>
        </target>";
	if($toolchainName === "Gnuc")
	{
		$configXmlString .= constructToolchainDefaultGnuc();
	}
	else if($toolchainName === "Tasking")
	{
		$configXmlString .= constructToolchainDefaultTasking();
	}
	else if($toolchainName === "Dcc")
	{
		$configXmlString .= constructToolchainDefaultDcc();
	}
	else
	{
		print("ERROR: Wrong tool chian " . $toolchainName . " is not configured!" . PHP_EOL);
		$error= true;
	}
	$configXmlString .= constructToolchainSplCpu($targetName, $toolchainName);
	$configXmlString .= PHP_EOL . 
"   </architecture>";
	return $configXmlString;
}

function constructArchitectureSecond($targetName, $toolchainName)
{
	$configXmlString=
"    <architecture name=\"Arm\" primaryToolchain= \"" . $toolchainName . "\" enable=\"true\">
        <target name=\"" . $targetName . "\" enable= \"true\">
            <output type=\"elf\" enable=\"true\" fileName=\"$(PROJ_NAME)_$(CORETYP_SECOND).elf\" tool=\"Linker\"/>
            <output type=\"hex\" enable=\"true\" fileName=\"$(PROJ_NAME)_$(CORETYP_SECOND).hex\" tool=\"Hex\"/>
            <output type=\"srec\" enable=\"true\" fileName=\"$(PROJ_NAME)_$(CORETYP_SECOND).srec\" tool=\"Srec\"/>
            <output type=\"lib\" enable=\"true\" fileName=\"$(PROJ_NAME)_$(CORETYP_SECOND).a\" tool=\"Archiver\"/>
        </target>";
	
	$configXmlString.= constructToolchain2ndCpu();
				
	$configXmlString.= PHP_EOL . 
"    </architecture>";
	return $configXmlString;
}

function constructArchitectureThird($targetName, $toolchainName)
{
	$configXmlString=
"    <architecture name=\"8051\" primaryToolchain= \"" . $toolchainName . "\" enable=\"true\">
        <target name=\"" . $targetName . "\" enable= \"true\">
            <output type=\"elf\" enable=\"true\" fileName=\"$(PROJ_NAME)_$(CORETYP_THIRD).elf\" tool=\"Linker\"/>
            <output type=\"hex\" enable=\"true\" fileName=\"$(PROJ_NAME)_$(CORETYP_THIRD).hex\" tool=\"Hex\"/>
            <output type=\"srec\" enable=\"true\" fileName=\"$(PROJ_NAME)_$(CORETYP_THIRD).srec\" tool=\"Srec\"/>
            <output type=\"lib\" enable=\"true\" fileName=\"$(PROJ_NAME)_$(CORETYP_THIRD).a\" tool=\"Archiver\"/>
        </target>";
	
	$configXmlString.= constructToolchain3rdCpu();
				
	$configXmlString.= PHP_EOL . 
"    </architecture>";
	return $configXmlString;
}

function constructToolchainDefaultGnuc()
{
	$configXmlString="
        <toolchain name=\"Gnuc\" enable=\"true\" path=\"$(COMPILER_DIR_MAIN)/bin\" verbose=\"true\">
            <tool name=\"Compiler\" type=\"COMPILER\" command=\"tricore-gcc\">
                <optionset id=\"Common\">$(CC_OPTS)</optionset>
                <argument template=\"{kw:options} @{kw:incpaths_listfile} -c \${kw:lt} -o $@ -save-temps=obj -MMD\" />
            </tool>
            <tool name=\"cc1\" type=\"OTHER\" command=\"tricore-gcc\">
                <optionset id=\"Common\">$(CC_OPTS)</optionset>
                <argument template=\"{kw:options} @{kw:incpaths_listfile} -c $(@:.o=.c) -o $@ -save-temps=obj -MMD\" />
            </tool>
            <tool name=\"Assembler\"  type=\"ASSEMBLER\" command=\"tricore-gcc\" >
                <optionset id=\"Common\">$(ASM_OPTS)</optionset>
                <argument template=\"{kw:options} @{kw:incpaths_listfile} -c \${kw:lt} -o $@\" />
            </tool>
            <tool name=\"Linker\" type=\"LINKER\" command=\"tricore-gcc\" >
                <optionset id=\"Common\">$(LD_OPTS)</optionset>
                <argument template=\"@{kw:objfiles_listfile} {kw:custobjfiles} -o $@ {kw:options}\" />
            </tool>
            <tool name=\"Hex\" type=\"OTHER\" command=\"tricore-objcopy\" >
                <argument template=\"\${kw:lt} -O ihex $@\" />
            </tool>
            <tool name=\"Srec\" type=\"OTHER\" command=\"tricore-objcopy\" >
                <argument template=\"\${kw:lt} -O srec $@\" />
            </tool>
            <tool name=\"Archiver\" type=\"ARCHIVER\" command=\"tricore-ar\" >
                <argument template=\"rcs $@ @{kw:objfiles_listfile} {kw:custobjfiles}\" />
            </tool>
        </toolchain>";
	return $configXmlString;
}


function constructToolchainDefaultTasking()
{
	$configXmlString="
        <toolchain name=\"Tasking\" enable=\"true\" path=\"$(COMPILER_DIR_MAIN)/bin\" verbose=\"true\"> 
            <tool name=\"Compiler\" type=\"COMPILER\" command=\"ctc\" nextTools=\"cc2, mkdep\" >
                <optionset id=\"Common\">$(CC_OPTS)</optionset>
                <argument index=\"\" template=\"-o $(@:.o=.src) \${kw:lt} --dep-file=$(@:.o=.dep) {kw:options}\" />
                <argument index=\"\" template=\"-f {kw:incpaths_listfile}\" />
            </tool>
            <tool name=\"cc1\" type=\"OTHER\" command=\"ctc\" nextTools=\"cc2\" >
                <optionset id=\"Common\">$(CC_OPTS)</optionset>
                <argument index=\"\" template=\"-o $(@:.o=.src) $(@:.o=.c) --dep-file=$(@:.o=.dep) {kw:options}\" />
                <argument index=\"\" template=\"-f {kw:incpaths_listfile}\" />
            </tool>
            <tool name=\"cc2\"  type=\"OTHER\" command=\"astc\">
                <optionset id=\"Common\">$(ASM_OPTS)</optionset>
                <argument index=\"\" template=\"-o $@ $(@:.o=.src) {kw:options}\" />
            </tool>
            <tool name=\"mkdep\"  type=\"OTHER\" command=\"sed\" path= \" \" >
                <argument index=\"\" template=\"$(call TaskingDepConversionString,$(@F),$(@D)) $(@:.o=.dep) {kw:gt} $(@:.o=.d) ; \" />
                <argument index=\"\" template=\"rm -f $(@:.o=.dep)\" />
            </tool>
            <tool name=\"Assembler\"  type=\"ASSEMBLER\" command=\"astc\" nextTools=\"mkdep\">
                <optionset id=\"Common\">$(ASM_OPTS)</optionset>
                <argument index=\"\" template=\"-o $@ \${kw:lt} --dep-file=$(@:.o=.d) {kw:options} -f {kw:incpaths_listfile}\" />
            </tool>
            <tool name=\"Linker\" type=\"LINKER\" command=\"ltc\" >
                <optionset id=\"Common\">$(LD_OPTS)</optionset>
                <argument index=\"\" template=\"-f {kw:objfiles_listfile} {kw:custobjfiles} {kw:options}\" />
            </tool> 
            <tool name=\"Hex\" type=\"OTHER\" command=\"ltc\" >
                <optionset id=\"Common\">$(LD_OPTS)</optionset>
                <argument index=\"\" template=\"-f {kw:objfiles_listfile} {kw:custobjfiles} -o $@:IHEX {kw:options} $(LIBS) -L$(LIB_DIR)\" />
            </tool>
            <tool name=\"Srec\" type=\"OTHER\" command=\"ltc\" >
                <optionset id=\"Common\">$(LD_OPTS)</optionset>
                <argument index=\"\" template=\"-f {kw:objfiles_listfile} {kw:custobjfiles} -o $@:SREC {kw:options} $(LIBS) -L$(LIB_DIR)\" />
            </tool>
            <tool name=\"Archiver\" type=\"ARCHIVER\" command=\"artc\" >
                <argument template=\"-rc $@ -f {kw:objfiles_listfile} {kw:custobjfiles}\" />
            </tool>
        </toolchain>";
	return $configXmlString;
}

function constructToolchainDefaultDcc()
{
	$configXmlString="
        <toolchain name=\"Dcc\" enable=\"true\" path=\"$(COMPILER_DIR_MAIN)/bin\" verbose=\"true\">
            <tool name=\"Compiler\" type=\"COMPILER\" command=\"dcc\">
                <optionset id=\"Common\">$(CC_OPTS)</optionset>
                <argument template=\"{kw:options} @{kw:incpaths_listfile} -c \${kw:lt} -o $@ -Xmake-dependency=4 -Xmake-dependency-savefile=$(@:.o=.d)\" />
            </tool>
            <tool name=\"cc1\" type=\"OTHER\" command=\"dcc\">
                <optionset id=\"Common\">$(CC_OPTS)</optionset>
                <argument template=\"{kw:options} @{kw:incpaths_listfile} -c $(@:.o=.c) -o $@ -Xmake-dependency=4 -Xmake-dependency-savefile=$(@:.o=.d)\" />
            </tool>
            <tool name=\"Assembler\"  type=\"ASSEMBLER\" command=\"das\" >
                <optionset id=\"Common\">$(ASM_OPTS)</optionset>
                <argument template=\"{kw:options} @{kw:incpaths_listfile} -o $@ -Xmake-dependency=4 -Xmake-dependency-savefile=$(@:.o=.d) \${kw:lt}\" />
            </tool>
            <tool name=\"Linker\" type=\"LINKER\" command=\"dld\" >
                <optionset id=\"Common\">$(LD_OPTS)</optionset>
                <argument template=\"{kw:options} -o $@ $(LIB_DIR) @{kw:objfiles_listfile} {kw:custobjfiles} $(LIBS)\"/>
            </tool>
            <tool name=\"Hex\" type=\"OTHER\" command=\"ddump\" >
                <argument template=\"-R -o $@ \${kw:lt}\" />
            </tool>
            <tool name=\"Srec\" type=\"OTHER\" command=\"ddump\" >
                <argument template=\"-R -o $@ \${kw:lt}\" />
            </tool>
            <tool name=\"Archiver\" type=\"ARCHIVER\" command=\"dar\" >
                <argument template=\"-rc $@ @{kw:objfiles_listfile} {kw:custobjfiles}\" />
            </tool>
        </toolchain>";
	return $configXmlString;
}

function constructToolchainSplCpu($cpuDefault, $compiler)
{//$targetCpuDefault . "/Tc\" tools= \"" . $targetCpuDefault
	$configXmlString="
        <toolchain name=\"Mcs\" enable=\"true\" path=\"1_ToolEnv/0_Build/0_Utilities\" verbose=\"true\">
            <tool name=\"Asm\" type=\"ASSEMBLER\" command=\"caspr-mcs\" nextTools= \"" . $cpuDefault . "/" . $compiler . "/cc1\" >
                <argument template=\"\${kw:lt} $(@:.o=.c) {kw:gt}$(@D)/asm.out\" />
            </tool>
        </toolchain>";
	return $configXmlString;
}


function constructToolchain2ndCpu()
{
	$configXmlString="
        <toolchain name=\"Tool2ndCpu\" enable=\"true\" path=\"__dummy_path__\" verbose=\"true\">
            <tool name=\"Compiler\" type=\"COMPILER\" command=\"$(COMPILE_COMMAND_S)\"/>
            <tool name=\"Assembler\"  type=\"ASSEMBLER\" command=\"$(ASM_COMMAND_S)\" />
            <tool name=\"Linker\" type=\"LINKER\" command=\"$(LD_COMMAND_S)\"/>
            <tool name=\"Hex\" type=\"OTHER\" command=\"$(LD_COMMAND_S)\"/>
            <tool name=\"Srec\" type=\"OTHER\" command=\"$(LD_COMMAND_S)\"/>
            <tool name=\"Archiver\" type=\"ARCHIVER\" command=\"$(AR_COMMAND_S)\"/>
        </toolchain>";
	return $configXmlString;
}

function constructToolchain3rdCpu()
{
	$configXmlString="
        <toolchain name=\"Tool3rdCpu\" enable=\"true\" path=\"__dummy_path__\" verbose=\"true\">
            <tool name=\"Compiler\" type=\"COMPILER\" command=\"$(COMPILE_COMMAND_T)\"/>
            <tool name=\"Assembler\"  type=\"ASSEMBLER\" command=\"$(ASM_COMMAND_T)\" />
            <tool name=\"Linker\" type=\"LINKER\" command=\"$(LD_COMMAND_T)\" />
            <tool name=\"Hex\" type=\"OTHER\" command=\"$(LD_COMMAND_T)\" />
            <tool name=\"Srec\" type=\"OTHER\" command=\"$(LD_COMMAND_T)\" />
            <tool name=\"Archiver\" type=\"ARCHIVER\" command=\"$(AR_COMMAND_T)\"/>
        </toolchain>";
	return $configXmlString;
}

?>