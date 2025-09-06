<?php
/**----------------------------------------------------------------------------
 * \file MakeFile.php
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


require_once ('MakeRule.php');
require_once ('/../Kernel/Project/Project.php');
require_once ('/../Utilities/FileHandling.php');
require_once ('/../Kernel/Configuration/Configuration.php');
require_once ('/../Kernel/Project/Folder.php');
require_once ('MakeData.php');
require_once ('MakeVariable.php');

use MakeGen\MakeFile;
use MakeGen\MakeRule;
use MakeGen\MakeRuleProject;
use MakeGen\MakeRuleCompile;
use Kernel\Project\Project;
use Utilities\FileHandling\FileGenHandle;
use Kernel\Configuration\CFG;
use Kernel\Project\Folder;
use MakeGen\ProjectData;
use MakeGen\MakeVariable;

/**
 * 
 * @created 21-Jul-2017 15:44:04
 */
class MakeFile
{

	protected $pathName;     /**< \brief Path name of make file */
	public $makeRules = Array();     /**< \brief Make rules for the files in the folder */
	public $subFolderMakePathNames = Array();     /**< \brief Array of path names for sub folder make files */
	public $templateFilePathName;     /**< \brief Path name of template make file */
	protected $projectConfiguration;     /**< \brief Project configuration object */
	public $m_MakeRuleProject;
	public $m_MakeRuleCompile;

	/**
	 * Generate make file
	 */
	public function generate()
	{
		if($this->pathName !== "")
		{
			// print("Make file for : " . $this->pathName); // TODO Instrumentation code
			$fileGen= new FileGenHandle($this, $this->templateFilePathName, $this->pathName);
			$fileGen->CreateFile();
			// print(" generated!" . PHP_EOL); // TODO Instrumentation code
		}
	}

	/**
	 * get path name for this make file
	 * 
	 * @param pathName    Make file path name
	 */
	public function getPathName()
	{
		return $this->pathName;
	}

	/**
	 * Get make variable name definition for target outputs
	 * 
	 * @param output    Output object
	 * @param makeVariable    Make variable name for the target output
	 */
	public function getTargetOutMakeVarDef($output, $makeVariable)
	{
		/* construct the variable based on the full name */
		/* TODO : AOU to user manual */
		/** Assumption of use: The architecture name, target name and output type shall not contain gnu make reserved chars.
		 */
		$variableName= strtoupper(str_replace("/", "_", $output->fullName));
	
		return "B_GEN_" . $variableName;
	}

}

/**
 * 
 * @created 21-Jul-2017 15:44:04
 */
class ProjectMakeFile extends MakeFile
{

	private $project;     /**< \brief Project object */
	private $definesMakePathName;     /**< \brief Path name for the make file which defines the variables */
	private $dependencyReference;     /**< \brief Make variable to refer the build dependency files */
	public $outputPaths = Array();     /**< \brief Array of output paths */

	/**
	 * Constructor of the class
	 * 
	 * @param project    Project object
	 * @param projectData    Project data object
	 */
	public function __construct($project, $projectData)
	{
		$this->project= $project;
	
		/* Update the make file path name */
		$this->pathName= CFG::TOOLENV_FOLDERNAME . "/" . 
		                 CFG::BUILD_FOLDERNAME . "/" .
						 CFG::BUILD_MAKE_FOLDERNAME . "/" .
						 CFG::PROJECT_MAKE_FILENAME;
						 
	
		$project= $projectData->getProject();
		$projectConfiguration= $project->getConfiguration();
	
		/* Get the build dependency variable to refer */
		$variable= $projectData->getDependencyVariable();
		$this->dependencyReference= $variable->getReference();
	
		/* Get defines make file path name */
		$this->definesMakePathName= $projectData->getDefinesMakePathName();
	
		/* TODO: AOU to user manual */
		/** Assumption of use: The template file name for sub dir make files shall be of following format:
		 * <sub dir make file name where "." replaced with "_">.php
		 */
		$templateFileName= str_replace(".", "_", CFG::PROJECT_MAKE_FILENAME) . ".php";
		$this->templateFilePathName= $projectConfiguration->getTemplateFilesPath() . "/" . $templateFileName;
	
		/* Run through the targets for which the outputs are required */
		foreach($projectData->getArchitectureNames() as $architectureName)
		{
			$architecture= $projectConfiguration->architectures[$architectureName];
			$architectureData= $projectData->getArchitecture($architectureName);
		
			/* Update output path */
			$this->outputPaths[]= $architectureData->getOutputPath();
		
			/* Update make rules */
			foreach($architectureData->getTargetNames() as $targetName)
			{
				$target= $architecture->targets[$targetName];
				$targetData= $architectureData->getTarget($targetName);
			
				foreach($targetData->getOutputTypes() as $outputType)
				{
					$output= $target->outputs[$outputType];
				
					/* Construct the make rules */
					$makeRule= new MakeRuleProject($output,
												   $target,
												   $architectureName,
												   $projectData);
				
					$this->makeRules[$architectureName][$targetName][$outputType]= $makeRule;
				}
			}
		}
	}

	/**
	 * Sets define make file path name
	 * 
	 * @param filePathName    File path name to be set
	 */
	public function setDefinesMakeFilePathName($filePathName)
	{
		$this->definesMakeFilePathName= $filePathName;
	}

	/**
	 * Gets build dependency file variable reference
	 * 
	 * @param variableReference    Variable name to refer in a make file
	 */
	public function getDependencyReference()
	{
		return $this->dependencyReference;
	}

	/**
	 * Gets define make file path name
	 * 
	 * @param filePathName    File path name
	 */
	public function getDefinesMakePathName()
	{
		return $this->definesMakePathName;
	}

}

/**
 * Class to hold make file information for each folder
 * @created 21-Jul-2017 15:44:04
 */
class SubFolderMakeFile extends MakeFile
{

	private $folder;     /**< \brief Folder object */
	private $makeFileRequired = false;     /**< \brief Does the folder has either c files, asm files, make files or any of the sub folders need make files */
	private $mappedPath;     /**< \brief Mapped file/folder path, which is different for external source folders and files  */
	private $projectData;     /**< \brief Project data object */
	private $srcObjectFilesVariables = Array();     /**< \brief Array of make variables for source object files in the folder */
	public $srcObjectFilesVariable;

	/**
	 * Constructor of the class
	 * 
	 * @param folder    Folder object
	 * @param projectData    Project Data object
	 */
	public function __construct($folder, $projectData)
	{
		/* Update the make file path name first */
		$this->folder= $folder;
		$this->projectData= $projectData;
		$this->updateMakeFileRequired();
	
		$project= $projectData->getProject();
		$projectConfiguration= $project->getConfiguration();
	
		$this->updateMappedPath($folder->getPathName());  // mapped path is truncated path of external folders to internal one
		$this->updatePathName();  // path name for the make file
	
		/* TODO: AOU to user manual */
		/** Assumption of use: The template file name for sub dir make files shall be of following format:
		 * <sub dir make file name where "." replaced with "_">.php
		 */
		$templateFileName= str_replace(".", "_", CFG::SUBFOLDER_MAKE_FILENAME) . ".php";
		$this->templateFilePathName= $projectConfiguration->getTemplateFilesPath() . "/" . 
									 $templateFileName;
	
		/* Update target data for source files */
		foreach($folder->getSourceFilePathNames() as $sourceFileName)
		{
			$this->updateMakeData($sourceFileName, "SRC");
		}
	
		/* Update target data for object files */
		foreach($folder->getObjectFilePathNames() as $objectFileName)
		{
			$this->updateMakeData($objectFileName, "OBJ");
		}
	
		/* Update target data for make files */
		foreach($folder->getMakeFilePathNames() as $makeFileName)
		{
			$this->updateMakeData($makeFileName, "MAK");
			$this->subFolderMakePathNames[]= $makeFileName;
		}
	
		/* Update data for header files */
		foreach($folder->getHeaderFilePathNames() as $headerFileName)
		{
			$this->updateIncludePathData($headerFileName);
		}
	}

	/**
	 * Get the adjusted path after removing the external root with prefixing indexed
	 * prefix
	 */
	private function updateMappedPath()
	{
		$pathName= $this->folder->getPathName();
		$this->mappedPath= $pathName; // default value
	
		/* Check if the root folder is internal folder */
		if(substr($pathName, 0, strlen(CFG::SRC_ROOT_FOLDERNAME)) !== CFG::SRC_ROOT_FOLDERNAME)
		{
			$project= $this->projectData->getProject();
			$configuration= $project->getConfiguration();
			$rootFolders= array_diff($configuration->sourceFolders, array('0_Src'));  // remove internal root folder
		
			/* Sort root folder based on its length */
			$sortedStringLengths= array_map('strlen', $rootFolders);
			arsort($sortedStringLengths, SORT_NUMERIC);
		
			foreach($sortedStringLengths as $index => $stringLength)
			{	
				/* TODO: AOU Entry to user manual */
				/** This part of the code modify the path name with first matching root folder.
				 * If there are two (or more) source folders, where one of them is under the folder
				 * tree of the other, they are not differenciated.
				 * Assumption of use: "external source folders shall hierarchically be independent".
				 */
				$regexPattern="#^" . $rootFolders[$index] . "/?.*$#";
				if(preg_match($regexPattern, $pathName) === 1)
				{
					/* Get the root folder path replaced */
					$this->mappedPath= substr_replace($pathName,
												$index . "_" . CFG::GEN_FOLDER_FOR_EXTERN_SRC,
												0,
												$stringLength);
					break;
				}
			}
		}
	}

	/**
	 * Updates the make file path name for a folder
	 */
	public function updatePathName()
	{
		$this->pathName= CFG::TOOLENV_FOLDERNAME . "/" . 
		                 CFG::BUILD_FOLDERNAME . "/" .
						 CFG::BUILD_MAKE_FOLDERNAME . "/" .
						 $this->mappedPath . "/" . 
						 CFG::SUBFOLDER_MAKE_FILENAME;
	}

	/**
	 * Gets true if make file required else false
	 * 
	 * @param result    Result if make file required. true: Make file required, false:
	 * Make file not required.
	 */
	public function isMakeFileRequired()
	{
		return $this->makeFileRequired;
	}

	/**
	 * Update make rules and related variables
	 * 
	 * @param fileName    File name for which the variables to be updated
	 */
	private function updateIncludePathData($fileName)
	{
		$sourceFile= $this->folder->getFile($fileName);
	
		$specificInclude= $this->projectData->configuration->specificInclude;
		foreach($sourceFile->getArchitectureNames() as $architectureName)
		{
			/* create/get an architecture object for the architecture */
			$architectureData= $this->projectData->createArchitecture($architectureName);
			$architectureData->addIncludePath($this->folder->getPathName());  // Add include path to respective architecture data
		}
	}

	/**
	 * Updates the variable make file required / not
	 */
	private function updateMakeFileRequired()
	{
		$folder= $this->folder;
		$folderFiles= array_merge($folder->getSourceFilePathNames(),
								  $folder->getMakeFilePathNames(),
								  $folder->getObjectFilePathNames());
								  
		if(count($folderFiles) > 0) 
		{
			$this->makeFileRequired= true; // register that make file is required for this folder
		}
	}

	/**
	 * Update the parent make file tree sub folder make files
	 * 
	 * @param subFolderMakeFilesList    List of sub folder make file objects
	 */
	public function updateParentTree($subFolderMakeFilesList)
	{
		/* Update parents only if make file required for this subfolder*/
		if($this->makeFileRequired)
		{
			/* Get the make file folder path to check the root folder make files */
			$buildMakeFolderPath= CFG::TOOLENV_FOLDERNAME . "/" .
							  CFG::BUILD_FOLDERNAME . "/" .
							  CFG::BUILD_MAKE_FOLDERNAME;
		
			$parentPath= dirname(dirname($this->pathName));
			$subFolderMakePathName= $this->pathName;
		
			/* Run from current folder level, all the way up till root source folder levels */
			while($parentPath !== $buildMakeFolderPath)
			{
				$parentPathName= $parentPath . "/" . CFG::SUBFOLDER_MAKE_FILENAME;
				$parentFolderMakeFile= $subFolderMakeFilesList[$parentPathName]; // Get parent folder make file object
			
				/* There is a chance that a subfolder path name is already updated due to one of the previous iterations */
				if(!in_array($subFolderMakePathName, $parentFolderMakeFile->subFolderMakePathNames))
				{
					$parentFolderMakeFile->subFolderMakePathNames[]= $subFolderMakePathName;
				}
			
				if($parentFolderMakeFile->makeFileRequired === false)
				{
					$parentFolderMakeFile->makeFileRequired= true;
					$subFolderMakePathName= $parentFolderMakeFile->pathName;
					$parentPath= dirname($parentPath); // go to next upper level
				}
				else
				{
					/* Parent tree for this folder is either updated or to be updated due to other iteration */
					break;
				}
			}
		}
	}

	/**
	 * Update information related to object files which are available in source
	 * folders
	 * 
	 * @param fileName    File name for which the variables to be updated
	 * @param fileType    File type as string: "SRC": for c or asm files, "OBJ": for
	 * object files and "MAK": for make files.
	 * @param targetData    Target data object
	 */
	private function updateObjectFilesVariables($fileName, $fileType, $targetData)
	{
		/* Create object files depending on the file type */
		switch($fileType)
		{
			case "SRC":
				/* For source files add make rules for compilation */
				$variable= $targetData->createObjectFilesVariable();
				break;
			
			case "OBJ":
				/* For object files, add variables data */
				$variable= $targetData->createSrcObjectFilesVariable();
			
				/* Instanciate object files variable object */
				$variableNameParts= $variable->getNameParts();
				$variable= new MakeVariable($variableNameParts, $fileName);
				$this->srcObjectFilesVariables[]= $variable;
			
				/* Add object file path name to the target */
				$targetData->addObjectFilePathName($fileName);
			
				break;
			
			case "MAK":
				/* For make files, add variables data to target */
				$variable= $targetData->createUserMakeObjectFilesVariable();
				break;
			
			default:
				break;
		}
	}

	/**
	 * Update make rules and related variables
	 * 
	 * @param fileName    File name for which the variables to be updated
	 * @param fileType    File type as string: "SRC": for c or asm files, "OBJ": for
	 * object files and "MAK": for make files.
	 */
	private function updateMakeData($fileName, $fileType)
	{
		$sourceFile= $this->folder->getFile($fileName);
	
		foreach($sourceFile->getArchitectureNames() as $architectureName)
		{
			/* create/get an architecture object for the architecture */
			$architectureData= $this->projectData->createArchitecture($architectureName);
			$project= $this->projectData->getProject();
			$projectConfiguration= $project->getConfiguration();
			$architecture= $projectConfiguration->architectures[$architectureName];
	
			$targetNames= $sourceFile->getTargetNames($architectureName);
			$outputFileVariables= Array();  // Initialize the array
		
			/* Run through each target to update the target related data/variables */
			foreach($targetNames as $targetName)
			{
				/* Create/get target data in to architecture data object */
				$targetData= $architectureData->createTarget($targetName);
				$target= $architecture->targets[$targetName];
			
				$this->updateObjectFilesVariables($fileName, $fileType, $targetData);
			}
		
			/* Update the make rules for the source files (to compile them) */
			if($fileType === "SRC")
			{
				$makeRule= new MakeRuleCompile($sourceFile,
									$architectureName,
									$this->mappedPath,
									$this->projectData);
	
				$this->makeRules[$architectureName][basename($fileName)]= $makeRule;
			}
		}
	}

	/**
	 * Gets folder path for which the sub dir make file is made
	 * 
	 * @param path    Path for which the sub dir make file is made
	 */
	public function getFolderPath()
	{
		return $this->folder->getPathName();
	}

	/**
	 * Gets array of variables for source object files
	 * 
	 * @param variables    Array of make variables for each target's source object
	 * files 
	 */
	public function getSrcObjectFilesVariables()
	{
		return $this->srcObjectFilesVariables;
	}

}
?>