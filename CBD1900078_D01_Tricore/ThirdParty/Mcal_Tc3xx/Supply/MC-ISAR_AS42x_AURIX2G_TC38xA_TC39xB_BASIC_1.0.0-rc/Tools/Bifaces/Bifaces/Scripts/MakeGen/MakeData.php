<?php
/**----------------------------------------------------------------------------
 * \file MakeData.php
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


require_once ('/../Kernel/Project/Project.php');
require_once ('MakeVariable.php');
require_once ('/../Kernel/Configuration/Configuration.php');
require_once ('/../Utilities/FileHandling.php');

use MakeGen\ProjectData;
use Kernel\Project\Project;
use MakeGen\ArchitectureData;
use MakeGen\MakeVariable;
use Kernel\Configuration\Configuration;
use Utilities\FileHandling\FileGenHandle;
use Kernel\Configuration\CFG;
use MakeGen\TargetData;
use MakeGen\ToolchainData;

/**
 * Class to hold information about the project variables and other data
 * @created 21-Jul-2017 15:44:03
 */
class ProjectData
{

	private $project;     /**< \brief Project object */
	private $architectures = Array();     /**< \brief Array of architecture data objects */
	private $dependencyVariable;     /**< \brief  */
	private $projectConfiguration;     /**< \brief Project configuration object */
	private $definesMakePathName;     /**< \brief File path name for defining the make variables */
	private $externalIncludePathsVariable;     /**< \brief External include paths variable */
	private $architectureNameVariables = Array();     /**< \brief Array of architecture name variables */

	/**
	 * Constructor of the class
	 * 
	 * @param project    Project object
	 */
	public function __construct($project)
	{
		$this->project= $project;
		$this->projectConfiguration= $project->getConfiguration();
	
		$dependencyVariableParts= array("DEP_FILES");
		$this->dependencyVariable= new MakeVariable($dependencyVariableParts, ""); // this variable is initialized to empty */
	
		$this->definesMakePathName= CFG::TOOLENV_FOLDERNAME . "/" .
									   CFG::BUILD_FOLDERNAME . "/" .
									   CFG::BUILD_MAKE_FOLDERNAME . "/" .
									   CFG::DEFINES_MAKE_FILENAME;
									   
		$specificInclude= $this->projectConfiguration->specificInclude;
		$extIncVariableParts= array("EXT_INCLUDE_PATHS"); // By default external include path shall contain empty value
		$extIncString= "";
		if(isset($specificInclude))
		{
			$externalIncludePaths= $specificInclude->getExternalIncludePaths();
			if(count($externalIncludePaths) > 0)
			{
				$extIncString= "-I" . implode("  \\" . PHP_EOL . "     -I", $externalIncludePaths);
			}
		
			$this->externalIncludePathsVariable= new MakeVariable($extIncVariableParts, $extIncString);
		}
	}

	/**
	 * Gets project object
	 * 
	 * @param configuration    Project configuration object
	 */
	public function getProject()
	{
		return $this->project;
	}

	/**
	 * Generates the defines make file
	 */
	private function generateDefinesMakeFile()
	{
	
		/* TODO: AOU to user manual */
		/** Assumption of use: The template file name for sub dir make files shall be of following format:
		 * <sub dir make file name where "." replaced with "_">.php
		 */
		$templateFileName= str_replace(".", "_", CFG::DEFINES_MAKE_FILENAME) . ".php";
	
		$templateFilePathName= $this->projectConfiguration->getTemplateFilesPath() . "/" . $templateFileName;
	
		/* generate file */
		// print("Make file for : " . $this->definesMakePathName); // TODO Instrumentation code
		$fileGen= new FileGenHandle($this, $templateFilePathName, $this->definesMakePathName);
		$fileGen->CreateFile();
		// print(" generated!" . PHP_EOL); // TODO Instrumentation code
	}

	/**
	 * Generates the defines make file
	 */
	public function generateFiles()
	{
		$this->updateExtensionVariables();
	
		/* generate include paths list file */
		foreach($this->architectures as $architecture)
		{
			$architecture->updateExtensionVariables();
			$architecture->generateFiles();
		}
	
		/* generate defines make file */
		$this->generateDefinesMakeFile();
	}

	/**
	 * Gets the external include paths variable
	 * 
	 * @param variable    External include paths variable
	 */
	public function getExternalIncludePathsVariable()
	{
		return $this->externalIncludePathsVariable;
	}

	/**
	 * Update variables which hold BIFACES extension variables
	 */
	public function updateExtensionVariables()
	{
		/* Get the architectures in the order they are configured */
		$configuration= $this->project->getConfiguration();
		$architectureNames= array_intersect(array_keys($configuration->architectures), array_keys($this->architectures));
	
		$this->architectureNameVariables[]= new MakeVariable(array("ARCHITECTURE", "PRIMARY"), $configuration->getPrimaryArchitectureName());
		foreach($architectureNames as $index => $archName)
		{
			$this->architectureNameVariables[]= new MakeVariable(array("ARCHITECTURE" . (string)$index), $archName);
		}
	}

	/**
	 * Gets the array of architecture name variables
	 * 
	 * @param variables    Array of architecture name variables
	 */
	public function getArchitectureNameVariables()
	{
		return $this->architectureNameVariables;
	}

	/**
	 * Gets the array of architecture data objects
	 * 
	 * @param architectureName    Architecture name for which architecture data object
	 * is required
	 * @param archictures    Architecture data objects
	 */
	public function getArchitecture($architectureName)
	{
		return $this->architectures[$architectureName];
	}

	/**
	 * Gets the object for dependency variable
	 * 
	 * @param variable    Dependency variable
	 */
	public function getDependencyVariable()
	{
		return $this->dependencyVariable;
	}

	/**
	 * Creates the architecture data object
	 * 
	 * @param architectureName    Architecture name for which data to be created
	 * @param architecture    Architecture data object which is created
	 */
	public function createArchitecture($architectureName)
	{
		if(!isset($this->architectures[$architectureName]))
		{
			$this->architectures[$architectureName]= new ArchitectureData($architectureName, $this);
		}
	
		return $this->architectures[$architectureName];
	}

	/**
	 * Gets the array of architecture data objects
	 * 
	 * @param architectureNames    Array of architecture names
	 */
	public function getArchitectureNames()
	{
		return array_keys($this->architectures);
	}

	/**
	 * Gets defines make file path name
	 * 
	 * @param filePathName    File path name
	 */
	public function getDefinesMakePathName()
	{
		return $this->definesMakePathName;
	}

}

/**
 * Class to hold the make related data for an architecture
 * @created 21-Jul-2017 15:44:03
 */
class ArchitectureData
{

	private $architectureName;     /**< \brief Name of the architecture for which this data object is created */
	private $targets = Array();     /**< \brief Array of target specific data */
	private $toolchains = Array();     /**< \brief Array of target specific data */
	private $projectData;     /**< \brief Project data object */
	private $includePathsListFileVariable;     /**< \brief Make variable to hold include paths list file information */
	private $includePaths = Array();     /**< \brief Array of include paths */
	private $specificIncludePaths = Array();     /**< \brief Array of specific include paths */
	private $outputPath;     /**< \brief Output path where the build outputs are generated */
	private $outputPathVariable;     /**< \brief Make variable to hold output paths */
	private $toolchainNameVariables = Array();     /**< \brief Array of make variables to hold tool-chain names */
	private $targetNameVariables = Array();     /**< \brief Array of make variables to hold target names */

	/**
	 * Constructor of the class
	 * 
	 * @param architectureName    Architecture name
	 * @param projectData    Project data object
	 */
	public function __construct($architectureName, $projectData)
	{
		$this->architectureName= $architectureName;
		$this->projectData= $projectData;
	
		$project= $projectData->getProject();
		$projectConfiguration= $project->getConfiguration();
		$architecture= $projectConfiguration->architectures[$architectureName];
		$primaryToolchainName= $architecture->getPrimaryToolchainName();
	
		$this->outputPath= CFG::EXEOUT_FOLDERNAME . "/" .
						   $architectureName . "_" . 
						   $primaryToolchainName;
						   
		$this->outputPathVariable= new MakeVariable(array("OUT_FOLDER", $architectureName),
															  $this->outputPath);
															  
		$this->toolchainNameVariable= new MakeVariable(array("TOOLCHAIN", $architectureName),
															  $primaryToolchainName);
	
		$includePathsListFilePathName= CFG::TOOLENV_FOLDERNAME . "/" .
									   CFG::BUILD_FOLDERNAME . "/" .
									   CFG::BUILD_MAKE_FOLDERNAME . "/" .
									   $architectureName . "_" .
									   CFG::INCLUDEFILELIST_FILENAME_POSTFIX . "." .
									   CFG::FILELIST_FILENAME_EXTENSION;
									   
		$this->includePathsListFileVariable= new MakeVariable(array("INC_LISTFILE", $architectureName),
															  $includePathsListFilePathName);
															  
		/* Add specific includes if they are set */
		$specificInclude= $projectConfiguration->specificInclude;
	
		if(isset($specificInclude))
		{
			$this->specificIncludePaths= $specificInclude->getIncludePaths($project->getSourceFolders());
		}
	}

	/**
	 * Gets the array of variables for target names
	 * 
	 * @param variables    Array of variable for targets
	 */
	public function getTargetNameVariables()
	{
		return $this->targetNameVariables;
	}

	/**
	 * Gets the target data for required target
	 * 
	 * @param targetNames    Array of target names
	 */
	public function getTargetNames()
	{
		return array_keys($this->targets);
	}

	/**
	 * Adds include path to the list
	 * 
	 * @param includePath    Include path string to be added
	 */
	public function addIncludePath($includePath)
	{
		$this->includePaths[$includePath]= $includePath;  // indexing with path name remove duplicates
	}

	/**
	 * Creates the tool-chain data object
	 * 
	 * @param toolchainName    Toolchain name of the data object to be added
	 * @param toolchainData    Toolchain data object, which is created
	 */
	public function createToolchain($toolchainName)
	{
		if(!isset($this->toolchains[$toolchainName]))
		{
			$this->toolchains[$toolchainName]= new ToolchainData($this->architectureName, $toolchainName);
		}
	
		return $this->toolchains[$toolchainName];
	}

	/**
	 * Creates the target data object
	 * 
	 * @param targetName    Target name of the data object to be added
	 * @param targetData    Target data object, which is created
	 */
	public function createTarget($targetName)
	{
		if(!isset($this->targets[$targetName]))
		{
			$this->targets[$targetName]= new TargetData($this->architectureName, $targetName);
		}
	
		return $this->targets[$targetName];
	}

	/**
	 * Gets the variable for include paths list file
	 * 
	 * @param variable    Variable object for include paths list file
	 */
	public function getIncludePathsListFileVariable()
	{
		return $this->includePathsListFileVariable;
	}

	/**
	 * Gets the target data for required target
	 * 
	 * @param targetName    Target name for which target data is required
	 * @param targets    Array of target data objects
	 */
	public function getTarget($targetName)
	{
		return $this->targets[$targetName];
	}

	/**
	 * Gets output path where the build outputs are generated for the arch targets
	 * 
	 * @param folderPath    Folder path where the build outputs are generated for the
	 * arch targets
	 */
	public function getOutputPath()
	{
		return $this->outputPath;
	}

	/**
	 * Gets the tool-chain data object
	 * 
	 * @param toolchainName    Toolchain name for which toolchain data is required
	 * @param toolchains    Architecture data objects
	 */
	public function getToolchain($toolchainName)
	{
		return $this->toolchains[$toolchainName];
	}

	/**
	 * Gets the array of tool-chain names which are required in the project
	 * 
	 * @param toolchainNames    Array of toolchain names
	 */
	public function getToolchainNames()
	{
		return array_keys($this->toolchains);
	}

	/**
	 * Gets the array of variables for tool-chain names
	 * 
	 * @param variables    Array of variable for toolchains
	 */
	public function getToolchainNameVariables()
	{
		return $this->toolchainNameVariables;
	}

	/**
	 * Updates the variables for the BIFACES extensions
	 */
	public function updateExtensionVariables()
	{
		$project= $this->projectData->getProject();
		$projectConfiguration= $project->getConfiguration();
		$architecture= $projectConfiguration->architectures[$this->architectureName];
	
		/* Get toolchain names as they appear in the configuration */
		$toolchainNames= array_intersect(array_keys($architecture->toolchains), array_keys($this->toolchains));
	
		/* Add the primary toolchain name at the begining */
		$this->toolchainNameVariables[]= new MakeVariable(array("TOOLCHAIN", "PRIMARY", $this->architectureName),
				$architecture->getPrimaryToolchainName());
		foreach($toolchainNames as $index => $toolchainName)
		{
			$this->toolchainNameVariables[]= new MakeVariable(array("TOOLCHAIN" . (string)$index, $this->architectureName), $toolchainName);
		}
	
		/* Get target names as they appear in the configuration */
		$targetNames= array_intersect(array_keys($architecture->targets), array_keys($this->targets));
	
		/* Add the primary toolchain name at the begining */
		$this->targetNameVariables[]= new MakeVariable(array("TARGET", "PRIMARY", $this->architectureName),
				$architecture->getPrimaryTargetName());
		foreach($targetNames as $index => $targetName)
		{
			$this->targetNameVariables[]= new MakeVariable(array("TARGET" . (string)$index, $this->architectureName), $targetName);
		}
	}

	/**
	 * Gets the external include paths variable
	 * 
	 * @param variable    External include paths variable
	 */
	public function getExternalIncludePathsVariable()
	{
		return $this->projectData->getExternalIncludePathsVariable();
	}

	/**
	 * Gets the variable for output paths
	 * 
	 * @param variable    Variable object for include paths list file
	 */
	public function getOutputPathVariable()
	{
		return $this->outputPathVariable;
	}

	/**
	 * Generates the architecture related files
	 */
	public function generateFiles()
	{
		/* generate include paths list file */
		$this->generateIncludePathsListFile();
	
		/* generate obj files list file */
		foreach($this->targets as $target)
		{
			$target->generateFiles();
		}
	}

	/**
	 * Generates the include paths list file
	 */
	private function generateIncludePathsListFile()
	{
		/* Create the file string with -I in the begining of each path */
		$includePaths= array_unique(array_merge($this->includePaths, $this->specificIncludePaths));
		$fileString= "\"-I" . implode("\"" . PHP_EOL . "\"-I", $includePaths) . "\"" . PHP_EOL;
	
		$filePathName= $this->includePathsListFileVariable->getValue();
		$folder= dirname($filePathName);
		if(!file_exists($folder))
		{
			mkdir($folder, 0777, true);	// the number 0777 provides access "Everything" to "All users" and true for recursive mkdir
		}
	
		/* generate file */
		// print("Make file for : " . $filePathName); // TODO Instrumentation code
		$this->outfileHandle = fopen($filePathName, "w");
		fwrite($this->outfileHandle, $fileString);
		fclose($this->outfileHandle);
		// print(" generated!" . PHP_EOL); // TODO Instrumentation code
	}

}

/**
 * Class to hold the make related data for a target
 * @created 21-Jul-2017 15:44:03
 */
class TargetData
{

	private $objectFilesVariable;     /**< \brief Make variable to hold information about object files */
	private $srcObjectFilesVariable;     /**< \brief Make variable to hold information about object files, which are available in source folders */
	private $userMakeObjectFilesVariable;     /**< \brief Make variable to hold information about object files, which are built with user defined make files */
	private $linkerFileVariable;     /**< \brief Make variable to hold include paths list file information */
	private $objectFilesListFileVariable;     /**< \brief Make variable to hold information about object files list file */
	private $outputFileVariables = Array();     /**< \brief Array of make variables to hold information about output file */
	private $objectFilePathNames = Array();     /**< \brief Array of object file path names */
	private $targetName;     /**< \brief Target name */
	private $architectureName;     /**< \brief Architecture name */

	/**
	 * Constructor of the class
	 * 
	 * @param architectureName    Architecture name
	 * @param targetName    Target name
	 */
	public function __construct($architectureName, $targetName)
	{
		$this->targetName= $targetName;
		$this->architectureName= $architectureName;
	
		/* Object files list file variable */
		$objectFilesListFilePathName= CFG::TOOLENV_FOLDERNAME . "/" .
									  CFG::BUILD_FOLDERNAME . "/" .
									  CFG::BUILD_MAKE_FOLDERNAME . "/" .
									  $architectureName . "_" . $targetName . "_" .
									  CFG::OBJFILELIST_FILENAME_POSTFIX . "." .
									  CFG::FILELIST_FILENAME_EXTENSION;
	
		$variableNameParts= array("OBJLIST_FILE", $architectureName, $targetName);
		$this->objectFilesListFileVariable= new MakeVariable($variableNameParts, $objectFilesListFilePathName);
	}

	/**
	 * Gets the array of source object files variable objects
	 * 
	 * @param variable    Array of source object files variables
	 */
	public function getSrcObjectFilesVariable()
	{
		return $this->srcObjectFilesVariable;
	}

	/**
	 * Creates the source object files variable
	 * 
	 * @param variable    Source object files variable, which is created
	 */
	public function createSrcObjectFilesVariable()
	{
		/* Source object files variable */
		$nameParts= array("SRCOBJS", $this->architectureName, $this->targetName);
		$this->srcObjectFilesVariable= new MakeVariable($nameParts, "");  // variable value not required 
	
		return $this->srcObjectFilesVariable;
	}

	/**
	 * Gets the output file variable object
	 * 
	 * @param outputTypes    Array of output types
	 */
	public function getOutputTypes()
	{
		return array_keys($this->outputFileVariables);
	}

	/**
	 * Adds a file path name to the list
	 * 
	 * @param objectFilePathName    Object files path name string
	 */
	public function addObjectFilePathName($objectFilePathName)
	{
		$this->objectFilePathNames[]= $objectFilePathName;
	}

	/**
	 * Creates the output file variable
	 * 
	 * @param output    Output object for which variable is to be created
	 * @param outputPath    Output path where the output file is created
	 * @param variable    Output files variable, which is created
	 */
	public function createOutputFileVariable($output, $outputPath)
	{
		$outputType= $output->getType();
	
		if(!isset($this->outputFileVariables[$outputType]))
		{
			$filePathName= $outputPath . "/" . $output->getFileName();
		
			$variableNameParts= array($outputType, $this->architectureName, $this->targetName);
			$this->outputFileVariables[$outputType]= new MakeVariable($variableNameParts, $filePathName);
		}
	
		return $this->outputFileVariables[$outputType];
	}

	/**
	 * Gets the object files list file variable object
	 * 
	 * @param variable    Object files list file variable object
	 */
	public function getObjectFilesListFileVariable()
	{
		return $this->objectFilesListFileVariable;
	}

	/**
	 * Gets the linker file variable object
	 * 
	 * @param variable    Linker files variable object
	 */
	public function getLinkerFileVariable()
	{
		return $this->linkerFileVariable;
	}

	/**
	 * Creates the user make object files variable
	 * 
	 * @param variable    user male object files variable, which is created
	 */
	public function createUserMakeObjectFilesVariable()
	{
		/* User make object files variable */
		$nameParts= array("CUSTOBJS", $this->architectureName, $this->targetName);
		$this->userMakeObjectFilesVariable= new MakeVariable($nameParts, "");  // variable value not required 
	
		return $this->userMakeObjectFilesVariable;
	}

	/**
	 * Gets the array of user make object files variable objects
	 * 
	 * @param variables    Array of user make object files variables
	 */
	public function getUserMakeObjectFilesVariable()
	{
		return $this->userMakeObjectFilesVariable;
	}

	/**
	 * Creates the object files variable
	 * 
	 * @param variable    Object files variable, which is created
	 */
	public function createObjectFilesVariable()
	{
		/* Object files variable */
		$nameParts= array("OBJS", $this->architectureName, $this->targetName);
		$this->objectFilesVariable= new MakeVariable($nameParts, "");  // variable value not required
	
		return $this->objectFilesVariable;
	}

	/**
	 * Gets the array of object files variable objects
	 * 
	 * @param variables    Array of object files variables
	 */
	public function getObjectFilesVariable()
	{
		return $this->objectFilesVariable;
	}

	/**
	 * Generates the object files list file
	 */
	private function generateObjectFilesListFile()
	{
		/* Create the file string with -I in the begining of each path */
		$fileString= "\"" . implode("\"" . PHP_EOL . "\"", $this->objectFilePathNames) . "\"" . PHP_EOL;
	
		$filePathName= $this->objectFilesListFileVariable->getValue();
		$folder= dirname($filePathName);
		if(!file_exists($folder))
		{
			mkdir($folder, 0777, true);	// the number 0777 provides access "Everything" to "All users" and true for recursive mkdir
		}
	
		/* generate file */
		// print("Make file for : " . $filePathName); // TODO Instrumentation code
		$this->outfileHandle = fopen($filePathName, "w");
		fwrite($this->outfileHandle, $fileString);
		fclose($this->outfileHandle);
		// print(" generated!" . PHP_EOL); // TODO Instrumentation code
	}

	/**
	 * Generates the architecture related files
	 */
	public function generateFiles()
	{
		/* generate defines make file */
		$this->generateObjectFilesListFile();
	}

	/**
	 * Creates the linker file variable
	 * 
	 * @param toolchain    Toolchain object
	 * @param variable    Linker files variable, which is created
	 */
	public function createLinkerFileVariable($toolchain)
	{
		/* Linker file variable */
		if(!isset($this->linkerFileVariable))
		{
			$toolchainConfigFolder= $toolchain->getConfigFolder();
			if($toolchainConfigFolder === "")
			{
				$toolchainConfigFolder= CFG::TOOLENV_FOLDERNAME . "/" . CFG::BUILD_FOLDERNAME . "/" .
										CFG::BUILD_CONFIG_FOLDERNAME;
			}
			$linkerFilePathName= $toolchainConfigFolder . "/" . "Lcf_" . $toolchain->getName() . "_" . 
								 $this->architectureName . "_" . $this->targetName . ".lsl";
	
			$variableNameParts= array("LCF_FILE", $this->architectureName, $this->targetName);
			$this->linkerFileVariable= new MakeVariable($variableNameParts, $linkerFilePathName);
		}
	
		return $this->linkerFileVariable;
	}

	/**
	 * Gets the output file variable object
	 * 
	 * @param outputType    Output type for which variable is requested
	 * @param variable    Array of user make object files variables
	 */
	public function getOutputFileVariable($outputType)
	{
		return $this->outputFileVariables[$outputType];
	}

}

/**
 * Class to hold the make related data for a toolchain
 * @created 21-Jul-2017 15:44:03
 */
class ToolchainData
{

	private $architectureName;     /**< \brief Architecture Name */
	private $toolchainName;     /**< \brief Tool-chain Name */
	private $toolCommandVariables = Array();     /**< \brief Array of make variables to hold information for tool commands */
	private $configFilesVariable;     /**< \brief Make variable for the configuration files used as make dependency */

	/**
	 * Constructor of the class
	 * 
	 * @param architectureName    Architecture name
	 * @param toolchainName    Toolchain name
	 */
	public function __construct($architectureName, $toolchainName)
	{
		$this->architectureName= $architectureName;
		$this->toolchainName= $toolchainName;
	}

	/**
	 * Creates the configuration files variable
	 * 
	 * @param projectData    Project data object
	 * @param variable    Toolchain config files variable, which is created
	 */
	public function createConfigFilesVariable($projectData)
	{
		if(!isset($this->configFilesVariable))
		{
			/* Get configuration file path names from the toolchain configuration */
			$project= $projectData->getProject();
			$projectConfiguration= $project->getConfiguration();
			$architecture= $projectConfiguration->architectures[$this->architectureName];
			$toolchain= $architecture->toolchains[$this->toolchainName];
		
			$configFileNames= $toolchain->getConfigFiles();
			$configFolder= $toolchain->getConfigFolder();
			if($configFolder === "")
			{
				$configFolder= CFG::TOOLENV_FOLDERNAME . "/" . CFG::BUILD_FOLDERNAME . "/" .
							CFG::BUILD_CONFIG_FOLDERNAME;
			}
		
			if(count($configFileNames) > 0)
			{
				$filePathNames= Array();
				foreach($configFileNames as $configFileName)
				{
					if(dirname($configFileName) === ".")
					{
						$filePathNames[]= $configFolder . "/" . $configFileName;
					}
					else
					{
						$filePathNames[]= $configFileName;
					}
				}
				$variableValue= implode(" \\" . PHP_EOL . "   ", $filePathNames);
				$variableNameParts= array("CONFIG", $this->architectureName, $toolchain->getName());
				$this->configFilesVariable= new MakeVariable($variableNameParts, $variableValue);
			}
		}
	
		return $this->configFilesVariable;
	}

	/**
	 * Gets variable for configuration files
	 * 
	 * @param variable    Configuration file variable
	 */
	public function getConfigFilesVariable()
	{
		return $this->configFilesVariable;
	}

	/**
	 * Gets tool command variable object
	 * 
	 * @param toolName    Tool name for which tool command variable is requested
	 * @param variable    Tool command variable
	 */
	public function getToolCommandVariable($toolName)
	{
		return $this->toolCommandVariables[$toolName];
	}

	/**
	 * Creates tool command variable
	 * 
	 * @param tool    Tool object for which tool command variable is to be created
	 */
	public function createToolCommandVariable($tool)
	{
		$toolName= $tool->getName();
	
		if(!isset($this->toolCommandVariables[$toolName]))
		{
			/* Define a tool postfix based on the comment */
			$postFix="";
			switch($tool->getType())
			{
				case "COMPILER":
					$postFix= "CC";
					break;
				case "ASSEMBLER":
					$postFix= "AS";
					break;
				case "LINKER":
					$postFix= "LD";
					break;
				case "CBINARRAY":
					$postFix= "CBA";
					break;
				case "ARCHIVER":
					$postFix= "AR";
					break;
				default:
					$postFix= strtoupper($toolName);
					break;
			}
		
			$variableNameParts= array($this->architectureName, $this->toolchainName, $postFix);
			$this->toolCommandVariables[$toolName]= new MakeVariable($variableNameParts, $tool->getCommandUI());
		}
	
		return $this->toolCommandVariables[$toolName];
	}

	/**
	 * Gets array of tool names
	 * 
	 * @param toolNames    Array of tool names
	 */
	public function getToolNames()
	{
		return array_keys($this->toolCommandVariables);
	}

}
?>