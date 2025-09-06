<?php
/**----------------------------------------------------------------------------
 * \file Configuration.php
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
 
namespace Kernel\Configuration;


require_once ('Architecture.php');
require_once ('Selection.php');
require_once ('/../ErrorReporting/ErrorReporting.php');
require_once ('Doxygen.php');
require_once ('/../../Utilities/FileHandling.php');

use Kernel\Configuration\Architecture;
use Kernel\Configuration\Selection;
use Kernel\Configuration\SpecificInclude;
use Kernel\ErrorReporting\Error;
use Kernel\ErrorReporting\ERR;
use Kernel\Configuration\Doxygen;
use Utilities\FileHandling\FileNamePattern;

/**
 * Class to hold configuration constants
 * @created 21-Jul-2017 15:44:03
 */
class CFG
{

	const SRC_ROOT_FOLDERNAME = '0_Src';     /**< \brief Internal Source folder */
	const TOOLENV_FOLDERNAME = '1_ToolEnv';     /**< \brief Tool Environment Folder */
	const EXEOUT_FOLDERNAME = '2_Out';     /**< \brief Folder for Build Generated Outputs */
	const C_FILE_EXTENSIONS = 'c,cpp';     /**< \brief File Extensions for C and CPP */
	const ASM_FILE_EXTENSIONS = 's,asm';     /**< \brief File Extensions for Assembly Source Files */
	const CHEADER_FILE_EXTENSIONS = 'h,hpp';     /**< \brief File Extensions for C and CPP headers */
	const ASMHEADER_FILE_EXTENSIONS = 'inc';     /**< \brief File Extensions for Assembly headers */
	const MAKE_FILE_EXTENSIONS = 'mk,mak';     /**< \brief File Extensions for Make Files */
	const OBJECT_FILE_EXTENSIONS = 'o,a,lib';     /**< \brief File Extensions for Object Files or Library Files */
	const FILELIST_FILENAME_PREFIX = 'IfxBifaces_';     /**< \brief Prefix for the list file to list object files and include files */
	const OBJFILELIST_FILENAME_POSTFIX = 'ObjList';     /**< \brief Postfix for the list file to list object files */
	const INCLUDEFILELIST_FILENAME_POSTFIX = 'IncludePathList';     /**< \brief Postfix for the list file to list include files */
	const FILELIST_FILENAME_EXTENSION = 'opt';     /**< \brief Extension for the list file to list object files and include files */
	const BUILD_FOLDERNAME = '0_Build';     /**< \brief Folder for Build Related Files */
	const BUILD_CONFIG_FOLDERNAME = '1_Config';     /**< \brief Folder for Build Configuration Files */
	const BUILD_UTILITY_FOLDERNAME = '0_Utilities';     /**< \brief Folder for Build Utility Files */
	const BUILD_MAKE_FOLDERNAME = '9_Make';     /**< \brief Folder for Build Make Files */
	const GEN_FOLDER_FOR_EXTERN_SRC = 'ExtSrc';     /**< \brief Folder for Generating Make or Build Outputs for External Referenced Source Files */
	const SUBFOLDER_MAKE_FILENAME = 'SubDirectory.mk';     /**< \brief File name for sub dir make files */
	const PROJECT_MAKE_FILENAME = 'Project.mk';     /**< \brief File name for project make file */
	const PROJECT_DEPMAKE_FILENAME = 'ProjectDep.mk';     /**< \brief File name for project dependency make file */
	const DEFINES_MAKE_FILENAME = 'Defines.mk';     /**< \brief File name for define make files */
	const GEN_MAKE_VAR_PREFIX = 'B_GEN_';     /**< \brief Prefix for generated make variables */
	const FULLNAME_DELIMITER = '/';     /**< \brief Delimiter for the full name configurations */

}

/**
 * This class contains all the configurable elements for the project build
 * environment
 * @created 21-Jul-2017 15:44:03
 */
class Configuration
{

	private $templateFilesPath = "";     /**< \brief Folder path for template files */
	private $toolEnvFolderPath = CFG::TOOLENV_FOLDERNAME;     /**< \brief Tool Environment Folder */
	private $outFolderPath = CFG::EXEOUT_FOLDERNAME;     /**< \brief Folder for Build Generated Outputs */
	private $buildMakeFolderPath = CFG::BUILD_MAKE_FOLDERNAME;     /**< \brief Folder for Build Generated Outputs */
	private $buildUtilityFolderPath = CFG::BUILD_UTILITY_FOLDERNAME;     /**< \brief Folder for Build Utility Files */
	private $configFilePathNames = "";     /**< \brief File path names for configuration files */
	private $primaryArchitectureName = "";     /**< \brief Primary architecture name */
	public $architectures = Array();     /**< \brief Array of architecture names corresponding to the name of architecture objects */
	public $selections = Array();     /**< \brief Configuration for selection patterns and associating them to targets and options. Array of SelectionConfiguration objects. */
	public $sourceFolders = array(CFG::SRC_ROOT_FOLDERNAME);     /**< \brief Source folders within the project */
	public $fileExtensions;     /**< \brief File extensions used in the project as array of arrays for each type */
	public $specificInclude;     /**< \brief Configuration for specific includes */
	public $doxygen;     /**< \brief  */

	/**
	 * Constructor of class
	 * 
	 * @param configurations    XML string for the BIFACES project configurations
	 * @param errorReporting    Error reporting obect from project
	 */
	public function __construct($configurations, $errorReporting)
	{
		//Check if the supplied input is file or array of files or string and process
		//accordingly

		$configXmls= Array();
		if(is_array($configurations))
		{
			/* It array, and it is only possible to have array of files */
			foreach($configurations as $configurationFileName)
			{
				$cgfLoad= simplexml_load_file($configurationFileName);
				if($cgfLoad !== false)
				{
					$dom = dom_import_simplexml($cgfLoad);
					$incRes= $dom->ownerDocument->xinclude(LIBXML_NOERROR);
					if($incRes !== -1)
					{
						$cgfLoad = simplexml_import_dom($dom);
					}
					else
					{
						$errorText= "Config XML file '". $configurationFileName . "' one or more include files which are not valid!";
						$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
						$errorReporting->register($error);
					}
					$configXmls[]= $cgfLoad;
				}
				else
				{
					$errorText= "Config XML file '". $configurationFileName . "' could not be opened!";
					$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
					$errorReporting->register($error);
				}
			}
		}
		else
		{
			/* If it is neither a file nor an array of files, it is string input */
			$cgfLoad= simplexml_load_string($configurations);
			if($cgfLoad !== false)
			{
				$configXmls[]= $cgfLoad;
			}
			else
			{
				$errorText= "Config XML string could not be loaded, check the format!";
				$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
				$errorReporting->register($error);
			}
		}
	
		$this->updateFileExtensions();
	
		/* Call the XML interface to acquire the configuration*/
		foreach($configXmls as $configXml)
			$this->xmlInterface($configXml, $errorReporting);
	
		/* Update the configuration once data aquisition is done */
		$this->update($errorReporting);
	
		/* Validate the configuration once aquisition is done */
		$this->validate($errorReporting);
	}

	/**
	 * Updates the source folders
	 * 
	 * @param sourceFoldersXmlElement    PHP 'simple xml element' for source folders'
	 * configuration.
	 * @param errorReporting
	 */
	private function updateSourceFolders($sourceFoldersXmlElement, $errorReporting)
	{
		$sourceFolderParameters= $sourceFoldersXmlElement->attributes();
	
		/* Run through each parameter to update the data members */
		foreach($sourceFolderParameters as $sourceFolderParameter => $value)
		{
			switch(strtolower($sourceFolderParameter))
			{
				case "paths":
					$value= str_replace("\\","/",$value);
					$folderPaths= explode(',',$value);
					foreach($folderPaths as $folderPath)
					{
						$folderPath= trim($folderPath);
					
						/* Remove the last "/" character if entered */
						while(substr($folderPath, -1) === "/")
						{
							$folderPath= substr($folderPath, 0, strlen($folderPath) - 1); // get rid of last char
							$folderPath= trim($folderPath); // Trim it again to avoid some space in between the slashes
						}
					
						/* Enter the folder path if it is really existing */
						if($folderPath != "")
						{
							if(realpath($folderPath) !== false)
							{
								$this->sourceFolders[realpath($folderPath)]= $folderPath;
							}
							else
							{
								$errorText= "Path '" . $folderPath . "', configured with 'sourceFolder' configuration doesn't exist! this path is ignored!";
								$error= new Error(ERR::TW, ERR::ID_W_CONFIG_MISSING_FOLDER, $errorText);
								$errorReporting->register($error);
							}
						}
					}
					break;
				default:
					$errorText= "Unknown parameter: '". $sourceFolderParameter . "' with Source Folders configuration!";
					$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
					$errorReporting->register($error);
					break;
			}
		}
	}

	/**
	 * XML interface to gather inputs for configuration
	 * 
	 * @param configXmlElement    PHP 'simple xml element' for configuration.
	 * @param errorReporting    Object to report errors in configurations
	 */
	private function xmlInterface($configXmlElement, $errorReporting)
	{
		/* Run through each configuration record to register the configuration elements */
		foreach ($configXmlElement->children() as $configElement)
		{
			switch(strtolower($configElement->getName()))
			{
				case "architecture":
					$archConfig= new Architecture($configElement, $errorReporting);
					if($archConfig->isEnabled())
						$this->architectures[$archConfig->name]= $archConfig;
					break;
				case "selection":
					$selectionConfig= new Selection($configElement, $errorReporting);
					if($selectionConfig->isEnabled())
						$this->selections[]= $selectionConfig;
					break;
				case "sourcefolder":
					$this->updateSourceFolders($configElement, $errorReporting);
					break;
				case "configfile":
					//$this->updateConfigFile($configElement, $errorReporting);
					break;
				case "specificinclude":
					if(isset($this->specificInclude)) 
						$this->specificInclude->addConfiguration($configElement, $errorReporting);
					else
						$this->specificInclude= new SpecificInclude($configElement, $errorReporting);
					break;
				case "templatefiles":
					$this->updateTemplateFiles($configElement, $errorReporting);
					break;
				case "primaryarchitecture":
					$this->updatePrimaryArchitectureConfig($configElement, $errorReporting);
					break;
				case "doxygen":
					$this->doxygen= new Doxygen($configElement, $errorReporting);
					break;
				case "indent":
					// Ignore this configuration here !
					break;
				default:
					$errorText= "Unknown configuration element '". $configElement->getName() . "'";
					$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
					$errorReporting->register($error);
					break;
			}
		}
	}

	private function updateFileExtensions()
	{
		/* Get the extensions as array */
		$cExtns= array_map('trim', explode(',', CFG::C_FILE_EXTENSIONS));
		$asmExtns= array_map('trim', explode(',', CFG::ASM_FILE_EXTENSIONS));
		$cHeaderExtns= array_map('trim', explode(',', CFG::CHEADER_FILE_EXTENSIONS));
		$asmHeaderExtns= array_map('trim', explode(',', CFG::ASMHEADER_FILE_EXTENSIONS));
		$makeExtns= array_map('trim', explode(',', CFG::MAKE_FILE_EXTENSIONS));
		$objectExtns= array_map('trim', explode(',', CFG::OBJECT_FILE_EXTENSIONS));
	
		/* Assign above array to the dict with type as index*/
		$this->fileExtensions['C']= $cExtns;
		$this->fileExtensions['ASM']= $asmExtns;
		$this->fileExtensions['CHEADER']= $cHeaderExtns;
		$this->fileExtensions['ASMHEADER']= $asmHeaderExtns;
		$this->fileExtensions['MAKE']= $makeExtns;
		$this->fileExtensions['OBJECT']= $objectExtns;
	}

	/**
	 * Selects the files which is resulting after removing discarded files and unused
	 * variants.
	 * 
	 * @param elementList    Input element list to be filtered
	 * @param resultList    Selected list of elements.
	 */
	public function selectForProject($elementList)
	{
		/* Start with an empty result list */
		$resultList= Array();
		$filtered= false;
	
		/* Run through each selections to get the files */
		foreach($this->selections as $selection)
		{
			/* Filter for the discarded elements and remove them */
			$newList= $selection->filterOutDiscarded($elementList);
		
			/* Filter for the used elements and add them */
			$newList= $selection->filterInUsed($newList);
		
			/* Filter for the variants and remove only the unused */
			$newList= $selection->filterVariants($newList);
		
			/* Merge the new elements compared to last iteration */
			$newList= array_diff($newList, $resultList);
			$resultList= array_merge($resultList, $newList);
		
			$filtered= true;
		}
	
		/* return the passed list if elements are not filtered by any of the selections, else the filtered list*/
		return $filtered ? $resultList : $elementList;
	}

	/**
	 * Assign the assignee to the files based on the configuration
	 * 
	 * @param inputList    Input element(file) list to be used for assignment
	 * @param errorReporting    Object to report errors in configurations
	 * @param resultList    Multi-dimentional array of assign results
	 * resultList[<type>][<assignee>]= file list.
	 */
	public function assignFiles($inputList, $errorReporting)
	{
		//Result list is multi dimentional array indedex by assign type and assignee.
		//resultList[<type>][<assignee>]= file list

		$resultList= Array();
	
		/* Run through each selections */
		foreach($this->selections as $selection)
		{
			/* First of all, validate the assign configurations */
			if($selection->validateAssigns($this->architectures, $errorReporting))
			{
				$selectList= $selection->assignFiles($inputList);
				foreach($selectList as $type => $assignList)
				{
					foreach($assignList as $assignee => $fileList)
					{
						/* Assign new elements to array */
						if(isset($resultList[$type]))
						{
							if(isset($resultList[$type][$assignee]))
							{
								$newList= array_diff($fileList, $resultList[$type][$assignee]);
								$resultList[$type][$assignee]= array_merge($resultList[$type][$assignee], $newList);
							}
							else
							{
								$resultList[$type][$assignee]= $fileList;
							}
						}
						else
						{
							$resultList[$type][$assignee]= $fileList;
						}
					}
				}
			}
		}
	
		/* return false if elements are not filtered, else the filtered list*/
		return $resultList;
	}

	/**
	 * Updates the Template Files Configuration
	 * 
	 * @param templateFilesXmlElement    PHP 'simple xml element' for template files '
	 * configuration.
	 * @param errorReporting
	 */
	private function updateTemplateFiles($templateFilesXmlElement, $errorReporting)
	{
		$templateFilesParameters= $templateFilesXmlElement->attributes();
	
		/* Run through each parameter to update the data members */
		foreach($templateFilesParameters as $templateFilesParameter => $value)
		{
			switch(strtolower($templateFilesParameter))
			{
				case "path":
					$this->templateFilesPath= trim($value);
					break;
				default:
					$errorText= "Unknown parameter: '". $templateFilesParameter . "' with Template Files configuration!";
					$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
					$errorReporting->register($error);
					break;
			}
		}
	}

	/**
	 * Updates the configuration data after all data acquisitions
	 * 
	 * @param errorReporting    Object to report errors in configurations
	 */
	private function update($errorReporting)
	{
		/* Update template files if not configured */
		if($this->templateFilesPath === "")
		{
			$this->templateFilesPath= str_replace("\\", "/", getenv('BINUTILS_PATH')) . "/../Bifaces/Templates";
		}
	
		/* Remove source folder's keys */
		$this->sourceFolders= array_values($this->sourceFolders);
	
		/* Update the primary architecture if not configured */
		if($this->primaryArchitectureName === "")
		{
			$architectureNames= array_keys($this->architectures);
			$this->primaryArchitectureName= $architectureNames[0];
		}
	
		/* update the architectures */
		foreach($this->architectures as $architecture)
		{
			$architecture->update($this, $errorReporting);
		}
	
		/* update the doxygen */
		if(!isset($this->doxygen))
		{
			$this->doxygen= new Doxygen($doxygenCongif, $errorReporting);
		}
		$this->doxygen->update($this, $errorReporting);
	}

	/**
	 * Validate the configurations
	 * 
	 * @param errorReporting    Object to report errors in configurations
	 */
	private function validate($errorReporting)
	{
		/* Validate primary architecture name */
		if(count($this->architectures) > 0) 
		{
			if(!in_array($this->primaryArchitectureName, array_keys($this->architectures)))
			{
				$errorText= "Primary architecture configured '" . $this->primaryArchitectureName . "' doesn't exist in any of architectures configured!";
				$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
				$errorReporting->register($error);
			
				/* Update primary architecture name with first arcthitecture name available */
				$architectureNames= array_keys($this->architectures);
				$this->primaryArchitectureName= $architectureNames[0];
			}
		}
	
		/* Validate the architecture configurations */
		foreach($this->architectures as $architecture)
		{
			$architecture->validate($this, $errorReporting);
		}
	
		/* Validate the doxygen configurations */
		$this->doxygen->validate($this, $errorReporting);
	}

	/**
	 * Gets the primary architecture name
	 * 
	 * @param architectureName    Primary architecture name
	 */
	public function getPrimaryArchitectureName()
	{
		return $this->primaryArchitectureName;
	}

	/**
	 * Updates the source folders
	 * 
	 * @param primaryArchXmlElement    PHP 'simple xml element' for  primary
	 * architecture' configuration.
	 * @param errorReporting
	 */
	private function updatePrimaryArchitectureConfig($primaryArchXmlElement, $errorReporting)
	{
		$primaryArchitectureParameters= $primaryArchXmlElement->attributes();
	
		/* Run through each parameter to update the data members */
		foreach($primaryArchitectureParameters as $primaryArchitectureParameter => $value)
		{
			switch(strtolower($primaryArchitectureParameter))
			{
				case "name":
					$this->primaryArchitectureName= trim($value);
					break;
				default:
					$errorText= "Unknown parameter: '". $primaryArchitectureParameter . "' with Primary Architecture configuration!";
					$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
					$errorReporting->register($error);
					break;
			}
		}
	}

	/**
	 * Gets the template files path
	 * 
	 * @param templateFilesPath    Template files path
	 */
	public function getTemplateFilesPath()
	{
		return $this->templateFilesPath;
	}

}

/**
 * Class to hold specific include paths
 * @created 21-Jul-2017 15:44:03
 */
class SpecificInclude
{

	private $internalPaths = Array();     /**< \brief Array of file patterns for the internal folders */
	private $externalPaths = Array();     /**< \brief Array of file paths for the external folders */

	/**
	 * Constructor of the class
	 * 
	 * @param specificIncludeXmlElement    PHP "simple xml object' to configure the
	 * specific include
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function __construct($specificIncludeXmlElement, $errorReporting)
	{
		/* Call the XML interface to acquire the configuration*/
		$this->xmlInterface($specificIncludeXmlElement, $errorReporting);
	}

	/**
	 * Checks if internal paths list after filtering the folder
	 * 
	 * @param result    Result list
	 */
	public function getExternalIncludePaths()
	{
		return $this->externalPaths;
	}

	/**
	 * Updates the specific include members after all data acquisitions
	 * 
	 * @param configuration    Configuration object
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function update($configuration, $errorReporting)
	{
	}

	/**
	 * Validate the specific include configurations
	 * 
	 * @param configuration    Configuration object
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function validate($configuration, $errorReporting)
	{
	}

	/**
	 * Checks if internal paths list after filtering the folder
	 * 
	 * @param folders    folder path names to be filtered
	 * @param result    Result list
	 */
	public function getIncludePaths($folders)
	{
		/* Check if the file matches with one of the patterns */
		$flePatterns= new FileNamePattern($this->internalPaths);
		$result= $flePatterns->filterFilePathPattern(FileNamePattern::FILTER_IN, array_keys($folders));
		return array_merge($result);
	}

	/**
	 * Add configuration values to specific include object
	 * 
	 * @param specificIncludeXmlElement    PHP 'simple xml element' for configuration
	 * of specific include.
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function addConfiguration($specificIncludeXmlElement, $errorReporting)
	{
		/* Call the XML interface to acquire the configuration*/
		$this->xmlInterface($specificIncludeXmlElement, $errorReporting);
	}

	/**
	 * XML interface to gather specific include configurations.
	 * 
	 * @param specificIncludeXmlElement    PHP 'simple xml element' for configuration
	 * of specific include.
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function xmlInterface($specificIncludeXmlElement, $errorReporting)
	{
		/* Extract the attributes*/
		$specificIncludeParameters= $specificIncludeXmlElement->attributes();
	
		foreach($specificIncludeParameters as $specificIncludeParameter => $value)
		{
			switch(strtolower($specificIncludeParameter))
			{
				case "internalpaths":
					foreach(array_map('trim', explode(',',$value)) as $internalPath)
					{
						if($internalPath !== "")
						{
							$this->internalPaths[]= str_replace("\\","/",$internalPath);
						}
					}
					break;
				case "externalpaths":
					foreach(array_map('trim', explode(',',$value)) as $externalPath)
					{
						if($externalPath !== "")
						{
							$this->externalPaths[]= str_replace("\\","/",$externalPath);
						}
					}
					break;
				default:
					$errorText= "Unknown parameter: '". $specificIncludeParameter . "' with specific include configuration!";
					$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
					$errorReporting->register($error);
					break;
			}
		}
	
	}

}
?>