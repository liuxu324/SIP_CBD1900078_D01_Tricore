<?php
/**----------------------------------------------------------------------------
 * \file Selection.php
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


require_once ('/../ErrorReporting/ErrorReporting.php');
require_once ('/../../Utilities/FileHandling.php');

use Kernel\Configuration\Selection;
use Kernel\Configuration\UsePattern;
use Kernel\Configuration\DiscardPattern;
use Kernel\Configuration\Varient;
use Kernel\Configuration\Assign;
use Kernel\ErrorReporting\ERR;
use Kernel\ErrorReporting\Error;
use Utilities\FileHandling\FileNamePattern;

/**
 * Class to contain the information about the file selection patterns and its
 * associations with other configurations.
 * @created 21-Jul-2017 15:44:03
 */
class Selection
{

	private $enable = true;     /**< \brief Enable or disable the entire selection configuration */
	public $assigns = Array();     /**< \brief Assign configurations (For what this selection is assigned). Name of the architecture/target. */
	public $usePatterns = Array();     /**< \brief Array of pattern texts to use. */
	public $discardPatterns = Array();     /**< \brief Array of pattern texts to discard. */
	public $variants = Array();     /**< \brief Array of pattern texts where variant folder and branches are specified. */
	public $subSelections = Array();     /**< \brief Sub selections, which are children to the current selection pattern */

	/**
	 * Constructor of the class
	 * 
	 * @param selectionXmlElement    PHP 'simple xml element' for configuration of
	 * selection of files
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function __construct($selectionXmlElement, $errorReporting)
	{
		/* Call the XML interface to acquire the configuration*/
		$this->xmlInterface($selectionXmlElement, $errorReporting);
	}

	/**
	 * Check if the selection config is enabled.
	 * 
	 * @param enable    Enable status. true: enabled, false: disabled
	 */
	public function isEnabled()
	{
		return $this->enable;
	}

	/**
	 * Get the folders filtered through variant patterns. only the specified branch
	 * folder tree would be selected. Other variant branches will be discarded.
	 * 
	 * @param elementList    elements to be filtered
	 * @param returnList    Returnlist after filtering
	 */
	public function filterVariants($elementList)
	{
		//Take out all the elements under the variant root folder from given list.
		//Filter in only the selected branch and add it to the resulting list.

		$returnList= $elementList;
		/* Run through each variant pattern to get the configurations */
		foreach($this->variants as $variant)
		{
			$returnList= $variant->filterElements($returnList);
		}
	
		return $returnList;
	}

	/**
	 * XML interface to gather inputs for configuration.
	 * 
	 * @param selectionXmlElement    PHP 'simple xml element' for configuration of
	 * selection.
	 * @param errorReporting    Object to report errors in configurations
	 */
	private function xmlInterface($selectionXmlElement, $errorReporting)
	{
		/* Extract the attributes*/
		$selectionParameters= $selectionXmlElement->attributes();
	
		/* Run through toolchain parameters to update the data members */
		foreach($selectionParameters as $selectionParameter => $value)
		{
			switch(strtolower($selectionParameter))
			{
				case "enable":
					$this->enable= strtolower(trim($value)) == "true" ? true : false;
					break;
				default:
					$errorText= "Unknown parameter: '". $selectionParameter . "' with one of the selection configurations!";
					$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
					$errorReporting->register($error);
					break;
			}
		}
	
		if($this->enable)
		{
			/* Extract the elements */
			$selectionElements= $selectionXmlElement->children();
		
			/* Run through each element to update the data members */
			foreach($selectionElements as $selectionElement)
			{
				$element= $selectionElement->getName();
				switch(strtolower($element))
				{
					case "use":
						$this->usePatterns[]= new UsePattern($selectionElement, $errorReporting);
						break;
					case "discard":
						$this->discardPatterns[]= new DiscardPattern($selectionElement, $errorReporting);
						break;
					case "variant":
						$this->variants[]= new Varient($selectionElement, $errorReporting); // class name Variant is misspelled to Varient purposely
						break;
					case "assign":
						$this->assigns[]= new Assign($selectionElement, $errorReporting);
						break;
					case "selection":
						$subSelection= new Selection($selectionElement, $errorReporting);  // recursive call !!!!
						if($subSelection->isEnabled())
							$this->subSelections[]= $subSelection;
						break;
					default:
						$errorText= "Unknown element: '". $element . "' with selection configuration: '" . $this->name . "'!";
						$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
						$errorReporting->register($error);
						break;
				}
			}
		}
	}

	/**
	 * Filter the files and folders in general which are assigned to project.
	 * 
	 * @param elementList    Input element list to be filtered
	 * @param filteredList    Resulting file list after filtering
	 */
	private function select($elementList)
	{
		/* Filter the used elements at this level */
		$elementList= $this->filterInUsed($elementList);
	
		/* Filter the used elements at this level */
		$elementList= $this->filteroutDiscarded($elementList);
	
		/* filter for variant configuration  */
		$elementList= $this->filterVariants($elementList);
	
		/* return list */
		return $elementList;
	}

	/**
	 * Assign the assignee to the files based on the configuration.
	 * 
	 * @param inputList    Input element(file) list to be used for assignment
	 * @param returnList    Multi-dimentional array of assign results
	 * resultList[<type>][<assignee>]= file list.
	 */
	public function assignFiles($inputList)
	{
		//Start the latest filtered folder list with complete list of folders passed
		//result list is multi dimentional array indedex by assign type and assignee.
		//resultList[<type>][<assignee>]= file list.

		$resultList= Array();
	
		$filteredList= $this->select($inputList);
	
		/* Check if any one of the assign configurations in this selection is for PROJECT */
		foreach($this->assigns as $assign)
		{
			$targets= $assign->getTargets();
		
			/* Assign new elements to array */
			foreach($targets as $target)
			{
				if(isset($resultList['TARGET'][$target]))
				{
					$newList= array_diff($filteredList, $resultList['TARGET'][$target]);
					$resultList['TARGET'][$target]= array_merge($resultList['TARGET'][$target], $newList);
				}
				else
				{
					$resultList['TARGET'][$target]= $filteredList;
				}
			}
		
			$tools= $assign->getTools();
			foreach($tools as $tool)
			{
				if(isset($resultList['TOOL'][$tool]))
				{
					$newList= array_diff($filteredList, $resultList['TOOL'][$tool]);
					$resultList['TOOL'][$tool]= array_merge($resultList['TOOL'][$tool], $newList);
				}
				else
				{
					$resultList['TOOL'][$tool]= $filteredList;
				}
			}
		
			$optionSets= $assign->getOptionSets();
			foreach($optionSets as $optionSet)
			{
				if(isset($resultList['OPTIONSET'][$optionSet]))
				{
					$newList= array_diff($filteredList, $resultList['OPTIONSET'][$optionSet]);
					$resultList['OPTIONSET'][$optionSet]= array_merge($resultList['OPTIONSET'][$optionSet], $newList);
				}
				else
				{
					$resultList['OPTIONSET'][$optionSet]= $filteredList;
				}
			}
		}
	
		/* Run through sub selections */
		foreach($this->subSelections as $selection)
		{
			$selectList= $selection->assignFiles($filteredList);
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
	
		/* return false if elements are not filtered, else the filtered list*/
		return $resultList;
	}

	/**
	 * Filter the input element list with used patterns and return only used elements.
	 * 
	 * @param elementList    Input element list, which is to be filtered.
	 * @param resultList    Result list after filtering with used files' patterns.
	 */
	public function filterInUsed($elementList)
	{
		/* Merge used file patterns */
		$useFilePatterns= Array();
		foreach($this->usePatterns as $usePattern)
		{
			$useFilePatterns= array_merge($useFilePatterns, $usePattern->patterns);
		}
	
		/* Filter only if there are use file patterns configured */
		if(count($useFilePatterns))
		{
			/* Filter the folders/files "IN", which match the discard file pattern */
			$flePatterns= new FileNamePattern($useFilePatterns);
			$elementList= $flePatterns->filterFilePathPattern(FileNamePattern::FILTER_IN, $elementList);
		}
	
		/* Return the resulting list */
		return $elementList;
	}

	/**
	 * Filter the input element list with discarded patterns and return only used
	 * elements.
	 * 
	 * @param elementList    Input element list, which is to be filtered.
	 * @param resultList    Result list after filtering with used files' patterns.
	 */
	public function filterOutDiscarded($elementList)
	{
		/* Merge used file patterns */
		$discardFilePatterns= Array();
		foreach($this->discardPatterns as $discardPattern)
		{
			$discardFilePatterns= array_merge($discardFilePatterns, $discardPattern->patterns);
		}
	
		/* Filter only if there are discard file patterns configured */
		if(count($discardFilePatterns))
		{
			/* Filter the folders/files "OUT", which match the discard file pattern */
			$flePatterns= new FileNamePattern($discardFilePatterns);
			$elementList= $flePatterns->filterFilePathPattern(FileNamePattern::FILTER_OUT, $elementList);
		}
	
		/* Return the resulting list */
		return $elementList;
	}

	/**
	 * Validates the assign configurations against the architecture configurations
	 * 
	 * @param architectures    Array of architecture configurations
	 * @param errorReporting    Object to report errors in configurations
	 * @param validationPass    Validation Pass: true:OK, false: NOTOK
	 */
	public function validateAssigns($architectures, $errorReporting)
	{
		$retVal= true;
	
		foreach($this->assigns as $assign)
		{
			$retVal &= $assign->validate($architectures, $errorReporting);
		}
	
		/* Run through each sub selections */
		foreach($this->subSelections as $subSelection)
		{
			$retVal &= $subSelection->validateAssigns($architectures, $errorReporting);
		}
	
		return $retVal;
	}

}

/**
 * Class to hold the file pattern definitions to discard from usage according to
 * assignment
 * @created 21-Jul-2017 15:44:03
 */
class DiscardPattern
{

	public $patterns = Array();     /**< \brief File pattern content */

	/**
	 * Constructor of class
	 * 
	 * @param discardXmlElement    PHP "simple xml object' to configure the discard
	 * pattern
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function __construct($discardXmlElement, $errorReporting)
	{
		/* Call the XML interface to acquire the configuration*/
		$this->xmlInterface($discardXmlElement, $errorReporting);
	
		/*Reoprt error in case of incorrect config element*/
		if(count($this->patterns) === 0)
		{
			$errorText= "One of the 'discard' configurations has parameter 'file' either not configured or it is empty! ";
			$errorText.= "Using default '' (empty pattern)!";
			$error= new Error(ERR::TW, ERR::ID_W_CONFIG_MISSING_CFGITEM, $errorText);
			$errorReporting->register($error);
			$this->patterns= array("");
		}
	}

	/**
	 * XML interface to gather inputs for configuration.
	 * 
	 * @param discardXmlElement    PHP 'simple xml element' for configuration of
	 * discard.
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function xmlInterface($discardXmlElement, $errorReporting)
	{
		$discardParameters= $discardXmlElement->attributes();
	
		/*Run through each parameter to update the data members*/
		foreach($discardParameters as $discardParameter => $value)
		{
			switch(strtolower($discardParameter))
			{
				case "files":
					$this->patterns= array_filter(array_map('trim', explode(',',$value))); //Back slash to front slash conversion not required because FilePattern contains this replacement
					break;
				default:
					$errorText= "Unknown parameter: '". $discardParameter . "' with discard configuration!";
					$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
					$errorReporting->register($error);
					break;
			}
		}
	}

}

/**
 * Class to hold the file pattern definitions to use file according to assignment
 * @created 21-Jul-2017 15:44:03
 */
class UsePattern
{

	public $patterns = Array();     /**< \brief File pattern content */

	/**
	 * Constructor of class
	 * 
	 * @param useXmlElement    PHP "simple xml object' to configure the use pattern
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function __construct($useXmlElement, $errorReporting)
	{
		/* Call the XML interface to acquire the configuration*/
		$this->xmlInterface($useXmlElement, $errorReporting);
	
		/*Reoprt error in case of incorrect config element*/
		if(count($this->patterns) === 0)
		{
			$errorText= "One of the 'use' configurations has parameter 'filePatterns' either not configured or it is empty! ";
			$errorText.= " Using default '*' (star pattern)!";
			$error= new Error(ERR::TW, ERR::ID_W_CONFIG_MISSING_CFGITEM, $errorText);
			$errorReporting->register($error);
			$this->patterns= array("*");
		}
	}

	/**
	 * XML interface to gather inputs for configuration.
	 * 
	 * @param useXmlElement    PHP 'simple xml element' for configuration of use.
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function xmlInterface($useXmlElement, $errorReporting)
	{
		$useParameters= $useXmlElement->attributes();
	
		/*Run through each parameter to update the data members*/
		foreach($useParameters as $useParameter => $value)
		{
			switch(strtolower($useParameter))
			{
				case "files":
					$this->patterns= array_filter(array_map('trim', explode(',',$value))); //Back slash to front slash conversion not required because FilePattern contains this replacement
					break;
				default:
					$errorText= "Unknown parameter: '". $useParameter . "' with 'use' configuration!";
					$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
					$errorReporting->register($error);
					break;
			}
		}
	
		/* If any of the parameters is empty put '*' */
		foreach($this->patterns as $index => $pattern) if($pattern="") $this->patterns[$index]="*";
	}

}

/**
 * Class to hold the variant information. Class name is purposely misspelled
 * because PHP5.1 (Linux) does not allow Variant class.
 * @created 21-Jul-2017 15:44:03
 */
class Varient
{

	public $branches = Array();     /**< \brief Name and branch folder name of the variant */
	public $rootPaths = Array();     /**< \brief Root patterns of variant folders */

	/**
	 * Constructor of class
	 * 
	 * @param variantXmlElement    PHP "simple xml object' to configure the variant
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function __construct($variantXmlElement, $errorReporting)
	{
		/* Call the XML interface to acquire the configuration*/
		$this->xmlInterface($variantXmlElement, $errorReporting);
	
		/*Reoprt error in case of incorrect config element*/
		if(count($this->branches) === 0)
		{
			$errorText= "One of the variant configurations has parameter 'branches' not configured!";
			$error= new Error(ERR::TE, ERR::ID_E_CONFIG_MISSING_NAME, $errorText);
			$errorReporting->register($error);
		}
	
		if(count($this->rootPaths) === 0)
		{
			$errorText= "One of the variant configurations has parameter 'rootPaths' not configured!";
			$error= new Error(ERR::TE, ERR::ID_E_CONFIG_MISSING_PARAM, $errorText);
			$errorReporting->register($error);
		}
	}

	/**
	 * XML interface to gather inputs for configuration.
	 * 
	 * @param variantXmlElement    PHP 'simple xml element' for configuration of
	 * variant.
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function xmlInterface($variantXmlElement, $errorReporting)
	{
		$variantParameters= $variantXmlElement->attributes();
	
		/*Run through each parameter to update the data members*/
		foreach($variantParameters as $variantParameter => $value)
		{
			switch(strtolower($variantParameter))
			{
				case "branches":
					$this->branches= array_filter(array_map('trim', explode(',',$value))); //Back slash to front slash conversion not required because FilePattern contains this replacement
					break;
				case "rootpaths":
					$this->rootPaths= array_filter(array_map('trim', explode(',',$value)));
					break;
				default:
					$errorText= "Unknown parameter: '". $variantParameter . "' with variant configuration: '" . $this->name . "'!";
					$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
					$errorReporting->register($error);
					break;
			}
		}
	}

	/**
	 * Filter element for variant configuration
	 * 
	 * @param elementList    List of elements to be filtered
	 * @param filteredList    List of elements after filtering
	 */
	public function filterElements($elementList)
	{
		$returnList= $elementList;
		$rootPaths="(?:" . implode('|', $this->rootPaths) . ")/*";
		$filePattern= new FileNamePattern($rootPaths);
	
		/*Filter-in all the folders with base pattern with wildcard /* at the end to a local list*/
		$tempList= $filePattern->filterFilePathPattern(FileNamePattern::FILTER_IN, $returnList);
	
		/*Filter-out all the folders with base pattern with wildcard "/*" at the end. Add to usable*/
		$returnList= array_diff($returnList, $tempList);
	
		/*for the filtered-in local list of folders, apply the leaf folder pattern and filter-in. Add to usable*/
		$branches="*/(?:" . implode("|", $this->branches) . ")*";
		$filePattern= new FileNamePattern($branches);
		$tempList= $filePattern->filterFilePathPattern(FileNamePattern::FILTER_IN, $tempList);
	
		$returnList= array_merge($returnList, $tempList);
	
		return $returnList;
	}

}

/**
 * Class to contain the information about pattern assign information
 * @created 21-Jul-2017 15:44:03
 */
class Assign
{

	private $targets = Array();     /**< \brief Target assigned files as array */
	private $tools = Array();     /**< \brief Tools assigned files as array */
	private $optionSets = Array();     /**< \brief OptionSets assigned files as array */

	/**
	 * Constructor of class
	 * 
	 * @param assignXmlElement    PHP "simple xml object' to configure the assign
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function __construct($assignXmlElement, $errorReporting)
	{
		/* Call the XML interface to acquire the configuration*/
		$this->xmlInterface($assignXmlElement, $errorReporting);
	
		/*Reoprt error in case of incorrect config element*/
		if((count($this->targets) === 0) && (count($this->tools) === 0) && (count($this->optionSets) === 0))
		{
			$errorText= "With one of the 'assign' is assigned to none of 'targets', 'tools', 'optionSets'!" . PHP_EOL;
			$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
			$errorReporting->register($error);
		}
	}

	/**
	 * XML interface to gather inputs for configuration.
	 * 
	 * @param assignXmlElement    PHP 'simple xml element' for configuration of assign.
	 * 
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function xmlInterface($assignXmlElement, $errorReporting)
	{
		$assignParameters= $assignXmlElement->attributes();
	
		/*Run through each parameter to update the data members*/
		foreach($assignParameters as $assignParameter => $value)
		{
			switch(strtolower($assignParameter))
			{
				case "targets":
					$this->targets= array_merge($this->targets, array_map('trim', explode(',',$value)));
					break;
				case "tools":
					$this->tools= array_merge($this->tools, array_map('trim', explode(',',$value)));
					break;
				case "optionsets":
					$this->optionSets= array_merge($this->optionSets, array_map('trim', explode(',',$value)));
					break;
				default:
					$errorText= "Unknown parameter: '". $assignParameter . "' with assign configuration: '" . $this->type . "'!";
					$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
					$errorReporting->register($error);
					break;
			}
		}
	}

	/**
	 * Get targets and assigned files
	 * 
	 * @param targets    Targets of the assignment
	 */
	public function getTargets()
	{
		return $this->targets;
	}

	/**
	 * Get tools and their assigned files
	 * 
	 * @param tools    Tools of the assignment
	 */
	public function getTools()
	{
		return $this->tools;
	}

	/**
	 * Get options and their assigned files
	 * 
	 * @param tools    Tools of the assignment
	 */
	public function getOptionSets()
	{
		return $this->optionSets;
	}

	/**
	 * Validates the targets architecture name against arch config tree.
	 * 
	 * @param targetName    target name for which architecture name is to be obtained
	 * @param architectures    Array of architecture configurations
	 * @param errorReporting    Object to report errors in configurations
	 * @param architectureName    Name of the resulting architecture. false if
	 * validation failed.
	 */
	private function validateTarget($targetName, $architectures, $errorReporting)
	{
		$validationPass= true;
		$aName= "";
		$tName= "";
	
		$tempArray= array_map('trim', explode('/', $targetName));
		if(count($tempArray) === 2)
		{
			$aName= $tempArray[0];
			$tName= $tempArray[1];
		
			if(array_key_exists($aName, $architectures))
			{
				$architecture= $architectures[$aName];
				if(!array_key_exists($tName, $architecture->targets))
				{
					$errorText= "Target Assignment configuration problem: architecture '" . $aName . "' doesn't contain target '" . $tName ."' !";
					$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
					$errorReporting->register($error);
					$validationPass= false;
				}
			}
			else
			{
				$errorText= "Target Assignment configuration problem: Proj Configuration doesn't contain architecture'" . $aName ."' !";
				$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
				$errorReporting->register($error);
				$validationPass= false;
			}
		}
		else
		{
			$errorText= "Target Assignment configuration problem: Wrong target name format '" . $targetName ."'! expected format: architecture name / target name";
			$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
			$errorReporting->register($error);
			$validationPass= false;
		}
	
		return $validationPass ? $aName . "/" . $tName : false;
	}

	/**
	 * Validates the tools toolchain name against arch config tree.
	 * 
	 * @param toolName    Name of the tool for which toolchain name to be obtained
	 * @param architectures    Array of architecture configurations
	 * @param errorReporting    Object to report errors in configurations
	 * @param toolchainName    Name of the resulting toolchain. false if validation
	 * failed.
	 */
	private function validateTool($toolName, $architectures, $errorReporting)
	{
		$validationPass= true;
		$aName= "";
		$tcName= "";
		$tName= "";
	
		$tempArray= array_map('trim', explode('/', $toolName));
		if(count($tempArray) === 3)
		{
			$aName= $tempArray[0];
			$tcName= $tempArray[1];
			$tName= $tempArray[2];
		
			if(array_key_exists($aName, $architectures))
			{
				$architecture= $architectures[$aName];
				if(array_key_exists($tcName, $architecture->toolchains))
				{
					$toolchain= $architecture->toolchains[$tcName];
					if(!array_key_exists($tName, $toolchain->tools))
					{
						$errorText= "Tool Assignment configuration problem: Toolchain '" . $aName . "/" . $tcName ."' doesn't contain tool '" . $tName ."' !";
						$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
						$errorReporting->register($error);
						$validationPass= false;
					}
				}
				else
				{
					$errorText= "Tool Assignment configuration problem: Architecture '" . $aName ."' doesn't contain toolchain '" . $tcName ."' !";
					$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
					$errorReporting->register($error);
					$validationPass= false;
				}
			}
			else
			{
				$errorText= "Tool Assignment configuration problem: Architecture '" . $aName ."' doesn't contain toolchain '" . $tcName ."' !";
				$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
				$errorReporting->register($error);
				$validationPass= false;
			}
		}
		else
		{
			$errorText= "Tool Assignment configuration problem: Wrong tool name format '" . $toolName ."'! expected format: architecture name / toolchain name / tool name";
			$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
			$errorReporting->register($error);
			$validationPass= false;
		}
	
		return $validationPass ? $aName . "/" . $tcName . "/" . $tName : false;
	}

	/**
	 * Validates the option set's tool name against arch config tree.
	 * 
	 * @param optionSetId    Id of optionset for which toolchain name is to be
	 * obtained
	 * @param architectures    Array of architecture configurations
	 * @param errorReporting    Object to report errors in configurations
	 * @param toolName    Name of resulting tool. false if validation failed.
	 */
	private function validateOptionSet($optionSetId, $architectures, $errorReporting)
	{
		$validationPass= true;
		$aName= "";
		$tcName= "";
		$tName= "";
		$oId= "";
	
		$tempArray= array_map('trim', explode('/', $optionSetId));
		if(count($tempArray) === 4)
		{
			$aName= $tempArray[0];
			$tcName= $tempArray[1];
			$tName= $tempArray[2];
			$oId= $tempArray[3];
		
			if(array_key_exists($aName, $architectures))
			{
				$architecture= $architectures[$aName];
				if(array_key_exists($tcName, $architecture->toolchains))
				{
					$toolchain= $architecture->toolchains[$tcName];
					if(array_key_exists($tName, $toolchain->tools))
					{
						$tool= $toolchain->tools[$tName];
						if(!array_key_exists($oId, $tool->optionSets))
						{
							$errorText= "Optionset Assignment configuration problem: tool '" . $aName . "/" . $tcName . "/" . $tName . "' doesn't contain optionset id '" . $oId ."' !";
							$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
							$errorReporting->register($error);
							$validationPass= false;
						}
					}
					else
					{
						$errorText= "Optionset Assignment configuration problem: Toolchain '" . $aName . "/" . $tcName ."' doesn't contain tool '" . $tName ."' !";
						$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
						$errorReporting->register($error);
						$validationPass= false;
					}
				}
				else
				{
					$errorText= "Optionset Assignment configuration problem: Architecture '" . $aName ."' doesn't contain toolchain '" . $tcName ."' !";
					$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
					$errorReporting->register($error);
					$validationPass= false;
				}
			}
			else
			{
				$errorText= "Optionset Assignment configuration problem: Architecture '" . $aName ."' doesn't contain toolchain '" . $tcName ."' !";
				$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
				$errorReporting->register($error);
				$validationPass= false;
			}
		}
		else
		{
			$errorText= "Optionset Assignment configuration problem: Wrong optionset id format '" . $optionSetId ."'! expected format: architecture name / toolchain name / tool name / optionset id";
			$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
			$errorReporting->register($error);
			$validationPass= false;
		}
	
		return $validationPass ? $aName . "/" . $tcName . "/" . $tName . "/" . $oId : false;
	}

	/**
	 * Validates the assignees
	 * 
	 * @param architectures    Array of architecture configurations
	 * @param errorReporting    Object to report errors in configurations
	 * @param validationPass    Validation Pass: true:OK, false: NOTOK
	 */
	public function validate($architectures, $errorReporting)
	{
		$validationPass= true;
		$targets= Array();
		$tools= Array();
		$optionSets= Array();
	
		foreach($this->targets as $target)
		{
			$tempVar= $this->validateTarget($target, $architectures, $errorReporting);
			if($tempVar !== false)
			{
				$targets[]= $tempVar;
			}
			else
			{
				$validationPass= false;
			}
		}
	
		foreach($this->tools as $tool)
		{
			$tempVar= $this->validateTool($tool, $architectures, $errorReporting);
			if($tempVar !== false)
			{
				$tools[]= $tempVar;
			}
			else
			{
				$validationPass= false;
			}
		}
	
		foreach($this->optionSets as $optionSet)
		{
			$tempVar= $this->validateOptionSet($optionSet, $architectures, $errorReporting);
			if($tempVar !== false) 
			{
				$optionSets[]= $tempVar;
			}
			else
			{
				$validationPass= false;
			}
		}
	
		$this->targets= $targets;
		$this->tools= $tools;
		$this->optionSets= $optionSets;
	
		return $validationPass;
	}

}
?>