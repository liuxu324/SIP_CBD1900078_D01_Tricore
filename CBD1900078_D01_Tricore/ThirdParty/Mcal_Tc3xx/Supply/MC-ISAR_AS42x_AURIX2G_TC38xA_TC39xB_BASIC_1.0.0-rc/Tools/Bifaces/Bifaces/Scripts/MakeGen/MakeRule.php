<?php
/**----------------------------------------------------------------------------
 * \file MakeRule.php
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


require_once ('MakeVariable.php');

use MakeGen\MakeRule;
use MakeGen\MakeVariable;

/**
 * Class to hold data for make rule
 * @created 21-Jul-2017 15:44:04
 */
class MakeRule
{

	public $preRequisite;     /**< \brief Pre requisite of the make rule */
	public $target;     /**< \brief Target of make rule */
	public $recipes = Array();     /**< \brief Recipe of make rule */
	protected $projectData;     /**< \brief Project data object */

	/**
	 * Updates the pre requisite
	 * 
	 * @param architectureName    target data object
	 * @param tool    Tool object
	 * @param projectData    Project data object
	 */
	protected function updatePreRequisiteForConfigRef($architectureName, $tool, $projectData)
	{
		$toolchainName= $tool->getToolchainName();
	
		/* create/ get the toolchain data object */
		$architectureData= $projectData->createArchitecture($architectureName);
		$toolchainData= $architectureData->createToolchain($toolchainName);
	
		$toolchainConfigFilesVariable= $toolchainData->createConfigFilesVariable($projectData);
		if(isset($toolchainConfigFilesVariable))
		{
			$this->preRequisite= $this->preRequisite . " " . $toolchainConfigFilesVariable->getReference($toolchain);
		}
	}

	/**
	 * Get command (command with arguments) line for a recipe
	 * 
	 * @param optionSetId    Option-set id to be used with tool
	 * @param tool    Tool object
	 * @param commandLine    Command line for the recipe
	 */
	protected function getCommandLine($optionSetId, $tool)
	{
		$architectureData= $this->projectData->getArchitecture($tool->getArchitectureName());
		$toolchainData= $architectureData->getToolchain($tool->getToolchainName());
		$toolCommandVariable= $toolchainData->createToolCommandVariable($tool);
	
		/* get optionset string */
		$optionSet= $tool->optionSets[$optionSetId];
		if(isset($optionSet))
			$optionsString= $optionSet->options;
		else
			$optionsString= "";
	
		$commandLine= $toolCommandVariable->getReference();
	
		foreach($tool->arguments as $argument)
		{
			$commandLine= $commandLine . " " . $this->getCommandArgument($optionsString, $argument->getTemplate());
		}
	
		return $commandLine;
	}

	/**
	 * Updates the recipes list
	 * 
	 * @param tool    Tool object for which recipe is being prepared
	 * @param optionSetId    Option-set id for the command
	 * @param projectData    Project data object
	 */
	protected function updateRecipes($tool, $optionSetId, $projectData)
	{
		$toolFullNameParts= explode("/", $tool->getFullName());
		$architectureName= $toolFullNameParts[0];
		$toolchainName= $toolFullNameParts[1];
	
	
		$project= $projectData->getProject();
		$projectConfiguration= $project->getConfiguration();
		$architectureData= $projectData->createArchitecture($architectureName);
	
		$toolchainData= $architectureData->createToolchain($toolchainName);
	
		$toolCommandVariable= $toolchainData->createToolCommandVariable($tool); // TODO remove this line??
	
		/* Construct recipie */
		$this->recipes[]= $this->getCommandLine($optionSetId, $tool);
	
		/* Get toolchain for each next tool */
		/* TODO : IFU to user manual */
		/** Infrormation for usage: The "next tools" are able to use the optionsets which are
		 * assigned as "primary option set" for the respective tool.
		 */
		foreach($tool->nextTools as $nextTool)
		{
			$this->updateRecipes($nextTool, $nextTool->getPrimaryOptionSetId(), $projectData); //recursive call
		}
	}

}

/**
 * Class to hold make rules for project make file
 * @created 21-Jul-2017 15:44:04
 */
class MakeRuleProject extends MakeRule
{

	private $outputFileVariable;     /**< \brief Make variable for the output */
	private $objectFilesReference;     /**< \brief Make variable reference for the object files */
	private $userMakeObjectFilesReference;     /**< \brief Make variable reference for user made make files */
	private $objectFilesListFileReference;     /**< \brief Make variable reference to object files list file */
	private $srcObjectFilesReference;     /**< \brief Make variable reference for the object files */
	private $linkerFileReference;     /**< \brief Make variable reference for the linker file */
	private $inputFilePathNames = "";     /**< \brief Input file path name configured for target output */

	/**
	 * Constructor of the class
	 * 
	 * @param output    Output object
	 * @param target    Target object
	 * @param architectureName    Architecture name
	 * @param projectData    Project data object
	 */
	public function __construct($output, $target, $architectureName, $projectData)
	{
		/* Get required variables from output object */
		$outputType= $output->getType();
		$this->projectData= $projectData;
	
		/* Get Target data */ 
		$architectureData= $projectData->getArchitecture($architectureName);
		$targetData= $architectureData->getTarget($target->getName());
	
		/* Get the make target */
		$outputFileVariable= $targetData->getOutputFileVariable($outputType);
		$this->outputFileVariable= $outputFileVariable;
		$this->target= $outputFileVariable->getReference();
	
		/* update obj file list file reference */
		$objfilesListFileVariable= $targetData->getObjectFilesListFileVariable();
		$this->objectFilesListFileReference= $objfilesListFileVariable->getReference();
	
		/* Get the tool used */
		$toolNameParts= explode("/", $output->getToolFullName());
		$project= $projectData->getProject();
		$projectConfiguration= $project->getConfiguration();
		$architecture= $projectConfiguration->architectures[$architectureName];
		$toolchain= $architecture->toolchains[$toolNameParts[1]];
		$tool= $toolchain->tools[$toolNameParts[2]];
	
		/* Update linker file reference */
		$linkerFileVariable= $targetData->createLinkerFileVariable($toolchain);
		$this->linkerFileReference= $linkerFileVariable->getReference();
	
		/* Update pre-requisite */
		$this->updatePreRequisite($architectureName, $outputType, $tool, $target);
	
		/* Construct recipie */
		$this->updateRecipes($tool, $tool->getPrimaryOptionSetId(), $projectData);
	}

	/**
	 * Gets command argument from the template
	 * 
	 * @param optionString    Option set as string of options
	 * @param template    Template of the argument
	 * @param argument
	 */
	protected function getCommandArgument($optionString, $template)
	{
		$dl= '$';
		$lt= '<';
		$gt= '>';
		$dq= '"';
		$input= $this->preRequisite;
		$output= $this->target;
		$objfiles= trim($this->objectFilesReference . $this->srcObjectFilesReference);
		$custobjfiles= $this->userMakeObjectFilesReference;
		$linkerfile= $this->linkerFileReference;
		$objfiles_listfile= $this->objectFilesListFileReference;
		$inputFiles= $this->inputFilePathNames;
		$options= $optionString;
	
		/* Get map file name */
		$pathParts= pathinfo($this->outputFileVariable->getValue());
		$mapfile= "$(@:." . $pathParts['extension'] . "=.map)";
	
		$newTemplate= preg_replace("#\{kw:(\w+?)}#", "\${\$1}", $template);
	
		eval("\$argument= \"$newTemplate\";");
	
		return $argument;
	}

	/**
	 * Get required pre-requisites for make rule
	 * 
	 * @param architectureName    Architecture for which make rule is targeted
	 * @param outputType    Output type
	 * @param tool    Tool object
	 * @param target    Target object
	 * @param preRequisite    Pre-requisite string for the make rule
	 */
	private function updatePreRequisite($architectureName, $outputType, $tool, $target)
	{
		$projectData= $this->projectData;
		$architectureData= $projectData->getArchitecture($architectureName);
		$targetData= $architectureData->getTarget($target->getName());
		$preRequisite= Array();
	
		/* get inputs required for the output */
		$output= $target->outputs[$outputType];
	
		/* Initialize the vaiable */
		$this->inputFilePathNames= "";
		$objFilesRequired= false;
	
		$inputs= $output->getInputs();
		/* TODO: IFU to user manual */
		/** Information for use: If an output is not configured with any inputs,
		 * then obj files are considered as inputs.
		 */
		if(count($inputs) === 0) $objFilesRequired= true;
	
		$inputFilePathNames= Array();
		/* Run through each output and get the inputs information */
		foreach($inputs as $input)
		{
			if($input->areObjectsAsInput()) $objFilesRequired= true;
		
			foreach($input->getSiblingTypes() as $siblingOutputType)
			{
				$inputVariable= $targetData->getOutputFileVariable($siblingOutputType,
																	$architectureData->getOutputPath());
				$inputFilePathNames[]= $inputVariable->getReference(); // update the temp array
			}
		
			$inputFilePathNames= array_merge($inputFilePathNames, $input->getFilePathNames());
		}
	
		$this->inputFilePathNames= implode(" ", $inputFilePathNames);
	
		/* Object files variables */
		$objectFilesVariable= $targetData->getObjectFilesVariable();
		if(isset($objectFilesVariable))
		{
			$variableReference= $objectFilesVariable->getReference();
			$preRequisite[]= $variableReference;
			$this->objectFilesReference= $variableReference;
		}
	
		/* Source object file variables */
		$srcObjectFilesVariable= $targetData->getSrcObjectFilesVariable();
		if(isset($srcObjectFilesVariable))
		{
			$variableReference= $srcObjectFilesVariable->getReference();
			$preRequisite[]= $variableReference;
			$this->srcObjectFilesReference= $variableReference;
		}
									  
		/* User Make object file variables */
		$userMakeObjectFilesVariable= $targetData->getUserMakeObjectFilesVariable();
		if(isset($userMakeObjectFilesVariable))
		{
			$variableReference= $userMakeObjectFilesVariable->getReference();
			$preRequisite[]= $variableReference;
			$this->userMakeObjectFilesReference= $variableReference;
		}
									  
		/* Linker file variables */
		$preRequisite[]= $this->linkerFileReference;
	
		if($objFilesRequired)
		{
			$this->preRequisite= implode(" ", array_merge($preRequisite, $inputFilePathNames));
		}
		else
		{
			$this->preRequisite= $this->inputFilePathNames;
		}
	
		$this->updatePreRequisiteForConfigRef($architectureName, $tool, $projectData);
	}

}

/**
 * Make rule to compile / assemble the source files. An inherited class of
 * MakeRule
 * @created 21-Jul-2017 15:44:04
 */
class MakeRuleCompile extends MakeRule
{

	public $architectureName;     /**< \brief Architecture for which make rule targeted */
	public $dependencyFilesVariable;     /**< \brief Make variable define for dependency file */
	public $objectFilesVariables = Array();     /**< \brief Array of object files make variable defines */
	public $buildOutputReferences = Array();     /**< \brief Array of make references to build outputs make variables, which are affected by this make rule */
	public $includePathsReferences;     /**< \brief Make reference to include path list file variable */
	public $sourceFileName;     /**< \brief Source file name */

	/**
	 * Constructor of the class
	 * 
	 * @param sourceFile    file object for which make rule to be created
	 * @param architectureName    Architecture name for which the make rule is made
	 * @param mappedSourceFilePath    Mapped path (which is changed for the external
	 * files) for source file
	 * @param projectData    Variable define make file object
	 */
	public function __construct($sourceFile, $architectureName, $mappedSourceFilePath, $projectData)
	{
		$this->architectureName= $architectureName;
		$this->projectData= $projectData;
	
		/* Update prerequisite */
		$this->preRequisite= $sourceFile->pathName;
		$this->sourceFileName= basename($sourceFile->pathName);
	
		/* Furhter, update the pre requisite with the configuration file */
		$tool= $sourceFile->getTool($architectureName);
		$this->updatePreRequisiteForConfigRef($architectureName, $tool, $projectData);
	
		/* Get architecture object for the architecture */
		$architectureData= $projectData->getArchitecture($architectureName);
	
		/* update the object files variable */
		$this->updateIncludePathsReferences($architectureData); // Actual include paths are updated later
	
		/* Extract file names for object files and dependencie files */
		$fileName= basename($sourceFile->pathName);
		$objFileName= $this->modifyFileExtension($fileName, "o");
		$depFileName= $this->modifyFileExtension($fileName, "d");
	
		$objectFilePath= $this->getObjectFilePath($architectureData->getOutputPath(),
												$tool->getToolchainName(),
												$mappedSourceFilePath);
											
		$objFilePathName= $objectFilePath . "/" . $objFileName;
		$depFilePathName= $objectFilePath . "/" . $depFileName;
	
		$this->target= $objFilePathName;
	
		/* update the dependency files variable */
		$this->updateDependencyFilesVariable($depFilePathName, $projectData);
	
		/* update project target data objects */
		$this->updateTargetData($objFilePathName, $sourceFile, 	$projectData);
	
		$this->updateRecipes($tool, $sourceFile->getOptionSetId($architectureName), $projectData);
	}

	/**
	 * Modifies the file extension to new file extension
	 * 
	 * @param fileName    Filename to be modified
	 * @param newExtension    New extension
	 * @param newFileName    New file name after extension modified
	 */
	private function modifyFileExtension($fileName, $newExtension)
	{
		$fileParts= pathinfo($fileName);
		$extension= $fileParts['extension'];
		if($extension !== "")
		{
			$fileName= substr($fileName, 0, strlen($fileName) - strlen($extension)) . $newExtension;
		}
	
		return $fileName;
	}

	/**
	 * Updates the include paths variable for the make rule
	 * 
	 * @param architectureData    Architecture data object
	 */
	private function updateIncludePathsReferences($architectureData)
	{
		/* Get reference to the include paths list file */
		$includePathsListFileVariable= $architectureData->getIncludePathsListFileVariable();
		$this->includePathsReferences= $includePathsListFileVariable->getReference();
	
		$externalIncludePathsVariable= $architectureData->getExternalIncludePathsVariable();
		if(isset($externalIncludePathsVariable))
		{
			$this->includePathsReferences .= " " . $externalIncludePathsVariable->getReference();
		}
	}

	/**
	 * 
	 * @param targetOutPath    Target output path
	 * @param toolchainName    Toolchain name
	 * @param mappedSourceFilePath    Mapped path (which is changed for the external
	 * files) for source file
	 * @param objFilePath    Object file path
	 */
	private function getObjectFilePath($targetOutPath, $toolchainName, $mappedSourceFilePath)
	{
		/* Construct the object file path */
		$objectFilePath= $targetOutPath . "/" . 
						$toolchainName . "_Files/" . 
						$mappedSourceFilePath;
	
		return $objectFilePath;
	}

	/**
	 * Updates the dependency file variable for the make rule
	 * 
	 * @param filePathName    Dependency file path name
	 * @param projectData    Project data object
	 */
	private function updateDependencyFilesVariable($filePathName, $projectData)
	{
		$variable= $projectData->getDependencyVariable();
		$variableParts= $variable->getNameParts();
	
		/* Instanciate dependency files variable object */
		$this->dependencyFilesVariable= new MakeVariable($variableParts, $filePathName);
	}

	/**
	 * Updates the object files variables for the make rule
	 * 
	 * @param filePathName    Object file path name
	 * @param targetData    Target data
	 */
	private function updateObjectFilesVariables($filePathName, $targetData)
	{
		/* Update information to the target data object */
		$variable= $targetData->getObjectFilesVariable();
	
		/* Instanciate object files variable object */
		$variableNameParts= $variable->getNameParts();
		$this->objectFilesVariables[]= new MakeVariable($variableNameParts, $filePathName);
	
		/* Add object file path name to target data */
		$targetData->addObjectFilePathName($filePathName);
	}

	/**
	 * Updates the argument members after all data acquisitions
	 * 
	 * @param optionString    Option set string as string of options
	 * @param template    Template of the argument
	 * @param argument
	 */
	protected function getCommandArgument($optionString, $template)
	{
		$dl= '$';
		$lt= '<';
		$gt= '>';
		$dq= '"';
		$input= $this->preRequisite;
		$output= $this->target;
		$incpaths= $this->includePathsReferences;
		$incpaths_listfile= $this->includePathsReferences;
		$options= $optionString;
	
		$newTemplate= preg_replace("#\{kw:(\w+?)}#", "\${\$1}", $template);
	
		eval("\$argument= \"$newTemplate\";");
	
		return $argument;
	}

	/**
	 * Updates the make variables related to make rule
	 * 
	 * @param objectFilePathName    Path name of the object file
	 * @param sourceFile    Source file object
	 * @param projectData    Project data object
	 */
	private function updateTargetData($objectFilePathName, $sourceFile, $projectData)
	{
		$architectureData= $projectData->getArchitecture($this->architectureName);
		$project= $projectData->getProject();
		$projectConfiguration= $project->getConfiguration();
		$architecture= $projectConfiguration->architectures[$this->architectureName];
	
		/* Run through targets for which the make rule is created */
		foreach($sourceFile->getTargetNames($this->architectureName) as $targetName)
		{
			/* update the object files variable names to make rule*/
			$targetData= $architectureData->getTarget($targetName);  // Get target data
			$this->updateObjectFilesVariables($objectFilePathName, $targetData);
		
			/* Update the output variable references */
			$target= $architecture->targets[$targetName];
		
			/* Update build output reference info */
			$this->updateBuildOutputReferences($target->outputs, $architectureData->getOutputPath(), $targetData);
		}
	}

	/**
	 * Updates the build out variable references for the make rule
	 * 
	 * @param outputs    Array of output objects
	 * @param outputPath    Output path, where the output is to be generated
	 * @param targetData    Target data
	 */
	private function updateBuildOutputReferences($outputs, $outputPath, $targetData)
	{
		foreach($outputs as $output)
		{
			if($output->isEnabled())
			{
				$outputType= $output->getType();
				$outputFileVariable= $targetData->createOutputFileVariable($output, $outputPath);
			
				$this->buildOutputReferences[]= $outputFileVariable->getReference();
			}
		}
	}

}
?>