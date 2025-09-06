<?php
/**----------------------------------------------------------------------------
 * \file Doxygen.php
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

use Kernel\ErrorReporting\Error;
use Kernel\ErrorReporting\ERR;

/**
 * Class for documentation tool
 * @created 21-Jul-2017 15:44:04
 */
class Doxygen
{

	private $excludePatterns = array();     /**< \brief Array of exclude patterns for doxygen doc generation */
	private $targetFullNames = array();     /**< \brief Names of those targets which need documentation */
	private $keepHtml;     /**< \brief Boolean to enable/disable the retaining of HTML files */
	private $toolPath = "";     /**< \brief Path to doxygen tool */
	private $dotToolPath = "";     /**< \brief Path to graphwiz tool */
	private $hhcToolPath;     /**< \brief Path to html help compiler tool */
	private $templatesPath = "";     /**< \brief Path to template files */
	private $imagesPaths = array();     /**< \brief Array of paths to image files */
	private $logisticData;     /**< \brief Array of logistic data of the document */

	/**
	 * Constructor of class
	 * 
	 * @param doxygenXmlElement    PHP "simple xml object' to configure the doxygen
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function __construct($doxygenXmlElement, $errorReporting)
	{
		/* Call the XML interface to acquire the configuration*/
		if(isset($doxygenXmlElement))
		{
			$this->xmlInterface($doxygenXmlElement, $errorReporting);
		
			/* Check if the keep Html is configured by user, if not keep it based on hhc tool path */
			if($this->keepHtml === NULL)
			{
				if($this->hhcToolPath === NULL) 
					$this->keepHtml=true;
				else
					$this->keepHtml=false;
			}
		}
		else
		{
			/* When there is no doxygen element at all.. */
			$this->excludePatterns=array("*Os/*","*_Reg/*");
			$this->keepHtml=true;
			$this->updateLogisticData("version: Vx.y.z, status: Draft/Release, type: MC User Manual/Application Note, control: Internal, issuemonth: Mmm, issueyear: YYYY");
		
			/*
			$errorText= "Doxygen not configured! Please add configuration at Config.xml!" . PHP_EOL;
			$errorText.= ".. Default values configured for following parameters:" . PHP_EOL;
			$errorText.= "... excludePatterns= *Os/*, *_Reg/*" . PHP_EOL;
			$errorText.= "... keepHtml= true" . PHP_EOL;
			$errorText.= "... logisticData= version: Vx.y.z, status: Draft/Release, type: UM/AN, control: Internal, issuemonth: Mmm, issueyear: YYYY";
			$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
			$errorReporting->register($error);
			*/
		}
	}

	/**
	 * XML interface to gather inputs for configuration.
	 * 
	 * @param doxygenXmlElement    PHP 'simple xml element' for configuration of
	 * doxygen
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function xmlInterface($doxygenXmlElement, $errorReporting)
	{
		/* Extract the attributes*/
		$doxygenParameters= $doxygenXmlElement->attributes();
	
		foreach($doxygenParameters as $doxygenParameter => $value)
		{
			switch(strtolower($doxygenParameter))
			{
				case "excludepatterns":
					$this->excludePatterns= array_map('trim', explode(',',$value)); //Back slash to front slash conversion not required because FilePattern contains this replacement
					break;
				case "targetfullnames":
					$this->targetFullNames= array_map('trim', explode(',',$value));
					break;
				case "keephtml":
					$this->keepHtml= strtolower(trim($value)) == "true" ? true : false;
					break;
				case "toolpath":
					$this->toolPath= str_replace("\\","/",trim($value));
					break;
				case "dottoolpath":
					$this->dotToolPath= str_replace("\\","/",trim($value));
					break;
				case "hhctoolpath":
					$this->hhcToolPath= str_replace("\\","/",trim($value));
					break;
				case "templatespath":
					$this->templatesPath= str_replace("\\","/",trim($value));
					break;
				case "imagespaths":
					$value= str_replace("\\","/",$value);
					$this->imagesPaths= array_map('trim', explode(',',$value));
					break;
				case "logisticdata":
					$this->updateLogisticData($value);
					break;
				default:
					$errorText= "Unknown parameter: '". $doxygenParameter . "' with doxygen configuration!";
					$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
					$errorReporting->register($error);
					break;
			}
		}
	
	}

	/**
	 * Updates the doxygen configuration
	 * 
	 * @param configuration    Configuration object
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function update($configuration, $errorReporting)
	{
		/* Update the targets to default value if they are not configured */
		//If the target name is not configured doxygen generates the document for all the files
	
		/* get the path which is configured by environment variable till the Doc tools */
		$docToolsPath= realpath(getEnv('BINUTILS_PATH') . "/../DocTools");
		if($docToolsPath != NULL)
		{
			$docToolsPath= str_replace("\\", "/", $docToolsPath);
		}
		else
		{
			$errorText= "Doxygen Target configuration problem: architecture '" . $docToolsPath . "' is not available!";
			$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
			$errorReporting->register($error);
		}
	
		/* Update the all the tool paths if they are not configured */
		if($this->toolPath === "")
		{
			$this->toolPath= $docToolsPath . "/doxygen/bin";
		}
	
		if($this->dotToolPath === "")
		{
			$this->dotToolPath= $docToolsPath . "/Graphviz/bin";
		}
	
		if(($this->hhcToolPath !== NULL) && ($this->hhcToolPath === ""))
		{
			$this->hhcToolPath= $docToolsPath . "/HTMLHelpWorkshop";
		}
	
		/* Update the template path if it is not configured */
		if($this->templatesPath === "")
		{
			$this->templatesPath= $docToolsPath . "/DocTemplates";
		}
	
		/* Update image paths to include the default paths */
		//To be updated later
	}

	/**
	 * Get the Dot tool path
	 * 
	 * @param toolpath    Dot tool path
	 */
	public function getDotToolPath()
	{
		return $this->dotToolPath;
	}

	/**
	 * Get the HTML Help Compiler tool path
	 * 
	 * @param toolpath    HTML Help Compiler tool path
	 */
	public function getHhcToolPath()
	{
		return $this->hhcToolPath;
	}

	/**
	 * Get path to template files
	 * 
	 * @param path    Path to template files
	 */
	public function getTemplatesPath()
	{
		return $this->templatesPath;
	}

	/**
	 * Get path to image files
	 * 
	 * @param paths    Array of paths to image files
	 */
	public function getImagesPaths()
	{
		return $this->imagesPaths;
	}

	/**
	 * Get the exclude patterns array
	 * 
	 * @param patterns    Array of exclude patterns
	 */
	public function getExcludePatterns()
	{
		return $this->excludePatterns;
	}

	/**
	 * Get the exclude patterns array
	 * 
	 * @param targetFullNames    Array of target full names
	 */
	public function getTargetFullNames()
	{
		return $this->targetFullNames;
	}

	/**
	 * Get enable/disable config info for generated html files
	 * 
	 * @param keepHtml    HTML info for enable/disable of generated Htmls
	 */
	public function getKeepHtmlInfo()
	{
		return $this->keepHtml;
	}

	/**
	 * Get the doxygen tool path
	 * 
	 * @param toolpath    doxygen tool path
	 */
	public function getToolPath()
	{
		return $this->toolPath;
	}

	/**
	 * Updates the logistic data compiled
	 * 
	 * @param dataString    Data string to be compiled
	 */
	public function updateLogisticData($dataString)
	{
		$dataString= trim($dataString);
	
		$tempData= explode(",", $dataString);
		$data= array();
	
		foreach($tempData as $tempDatum)
		{
			if(trim($tempDatum) !== "")
			{
				$datumParts= explode(":", $tempDatum);
				$data[trim($datumParts[0])]= trim($datumParts[1]);
			}
		}
	
		$this->logisticData= $data;
	}

	/**
	 * Get the logistic data
	 * 
	 * @param data    Data array
	 */
	public function getLogisticData()
	{
		return $this->logisticData;
	}

	/**
	 * Validates the targets architecture name against arch config tree.
	 * 
	 * @param targetFullName    target full name which is to be validated
	 * @param architectures    Array of architecture configurations
	 * @param errorReporting    Object to report errors in configurations
	 * @param result    result of validation: true=passed, false= failed
	 */
	private function validateTarget($targetFullName, $architectures, $errorReporting)
	{
		$validationPass= true;
		$aName= "";
		$tName= "";
	
		$tempArray= array_map('trim', explode(CFG::FULLNAME_DELIMITER, $targetFullName));
		if(count($tempArray) === 2)
		{
			$aName= $tempArray[0];
			$tName= $tempArray[1];
		
			if(array_key_exists($aName, $architectures))
			{
				$architecture= $architectures[$aName];
				if(!array_key_exists($tName, $architecture->targets))
				{
					$errorText= "Doxygen Target configuration problem: architecture '" . $aName . "' doesn't contain target '" . $tName ."' !";
					$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
					$errorReporting->register($error);
					$validationPass= false;
				}
			}
			else
			{
				$errorText= "Doxygen Target configuration problem: Proj Configuration doesn't contain architecture'" . $aName ."' !";
				$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
				$errorReporting->register($error);
				$validationPass= false;
			}
		}
		else
		{
			$errorText= "Doxygen Target configuration problem: Wrong target name format '" . $targetFullName ."'! expected format: <architecture name>" . CFG::FULLNAME_DELIMITER . "<target name>";
			$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
			$errorReporting->register($error);
			$validationPass= false;
		}
	
		return $validationPass;
	}

	/**
	 * Updates the doxygen configuration
	 * 
	 * @param configuration    Configuration object
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function validate($configuration, $errorReporting)
	{
		$validationPass= true;
	
		/* Validate targets */
		if(count($this->targetFullNames) !== 0)
		{
			$validTargets= array();
			foreach($this->targetFullNames as $targetFullName)
			{
				if($this->validateTarget($targetFullName, $configuration->architectures, $errorReporting) === false)
				{
					$validationPass= false;
				}
				else
				{
					$validTargets[$targetFullName]= $targetFullName;
				}
			}
		
			$this->targetFullNames= array_keys($validTargets);
		}
		 return $validationPass;
	}

}
?>