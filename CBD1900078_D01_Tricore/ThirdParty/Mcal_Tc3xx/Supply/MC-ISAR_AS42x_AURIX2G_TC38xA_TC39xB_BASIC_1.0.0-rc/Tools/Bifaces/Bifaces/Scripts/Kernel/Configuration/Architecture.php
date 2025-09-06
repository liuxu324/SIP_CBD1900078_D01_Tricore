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
 
namespace Kernel\Configuration;


require_once ('/../ErrorReporting/ErrorReporting.php');

use Kernel\Configuration\Target;
use Kernel\Configuration\Toolchain;
use Kernel\ErrorReporting\ERR;
use Kernel\ErrorReporting\Error;
use Kernel\Configuration\Output;
use Kernel\Configuration\Input;
use Kernel\Configuration\Tool;
use Kernel\Configuration\OptionSet;
use Kernel\Configuration\Argument;

/**
 * Class to contain the cpu architectural information, which are available in the
 * project.
 * @created 21-Jul-2017 15:44:03
 */
class Architecture
{

	public $name = "";     /**< \brief Name of the architecture */
	private $primaryTarget = "";     /**< \brief Name of the primary target used with in this architecture */
	private $primaryToolchain = "";     /**< \brief Name of the primary tool-chain used for targets in this architecture */
	private $enable = true;     /**< \brief Enable or Disable the entire architecture configuration */
	public $targets = Array();     /**< \brief Array of targets with architecture, which are needed for the project */
	public $toolchains = Array();     /**< \brief Array of tool-chains for the architecture */

	/**
	 * Constructor of the class
	 * 
	 * @param archXmlElement    PHP 'simple xml element' for configuration of
	 * architecture.
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function __construct($archXmlElement, $errorReporting)
	{
		/* Call the XML interface to acquire the configuration*/
		$this->xmlInterface($archXmlElement, $errorReporting);
	
		if($this->enable)
		{
			/*Report error in case the name of the architecture is not configured*/
			if($this->name === "")
			{
				$errorText= "One of the architecture configurations has parameter 'name' not configured!";
				$error= new Error(ERR::TE, ERR::ID_E_CONFIG_MISSING_NAME, $errorText);
				$errorReporting->register($error);
			}
	
			/*Check if the primary target configuration matches with any of the targets' configured*/
			if($this->primaryTarget !== "")
			{
				if(!array_key_exists($this->primaryTarget, $this->targets))
				{
					$errorText= "Wrong configuration! Primary Target: '". $this->primaryTarget . "' doesn't exist in the targets with architecture: '" . $this->name . "'!";
					$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
					$errorReporting->register($error);
					break;
				}
			}
			else
			{
				if(count($this->targets) > 0)
				{
					$targetNames= array_keys($this->targets);
					$this->primaryTarget= $targetNames[0];
				}
			}
		
			/*Check if the primary toolchain configuration matches with any of the toolchains configured*/
			if($this->primaryToolchain !== "")
			{
				if(!array_key_exists($this->primaryToolchain, $this->toolchains))
				{
					$errorText= "Wrong configuration! Primary Toolchain: '". $this->primaryToolchain . "' doesn't exist in the toolchains with architecture: '" . $this->name . "'!";
					$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
					$errorReporting->register($error);
					break;
				}
			}
			else
			{
				if(count($this->toolchains) > 0)
				{
					$toolchainNames= array_keys($this->toolchains);
					$this->primaryToolchain= $toolchainNames[0];
				}
			}
		}
	}

	/**
	 * Check if the architecture config is enabled
	 * 
	 * @param enable    Enable status true: enabled, false: disabled
	 */
	public function isEnabled()
	{
		return $this->enable;
	}

	/**
	 * XML interface to gather inputs for configuration
	 * 
	 * @param archXmlElement    PHP 'simple xml element' for configuration of
	 * architecture.
	 * @param errorReporting    Object to report errors in configurations
	 */
	private function xmlInterface($archXmlElement, $errorReporting)
	{
		$archParameters= $archXmlElement->attributes();
	
		/* Run through each parameter to update the data members */
		foreach($archParameters as $archParameter => $value)
		{
			switch(strtolower($archParameter))
			{
				case "name":
					$this->name= trim($value);
					break;
				case "enable":
					$this->enable= strtolower(trim($value)) == "true" ? true : false;
					break;
				case "primarytoolchain":
					$this->primaryToolchain= trim($value);
					break;
				case "primarytarget":
					$this->primaryTarget= trim($value);
					break;
				default:
					$errorText= "Unknown parameter: '". $archParameter . "' with architecture configuration: '" . $this->name . "'!";
					$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
					$errorReporting->register($error);
					break;
			}
		}
	
		if($this->enable)
		{
			$archElements= $archXmlElement->children();
			/*Run through each element to update the data members*/
			foreach($archElements as $archElement)
			{
				$element= $archElement->getName();
				switch(strtolower($element))
				{
					case "target":
						$targetConfig= new Target($archElement, $errorReporting);
						if($targetConfig->isEnabled())
							$this->targets[$targetConfig->getName()]= $targetConfig;
						break;
					case "toolchain":
						$toolchainConfig= new Toolchain($archElement, $errorReporting);
						if($toolchainConfig->isEnabled())
							$this->toolchains[$toolchainConfig->getName()]= $toolchainConfig;
						break;
					default:
						$errorText= "Unknown element: '". $element . "' with architecture configuration: '" . $this->name . "'!";
						$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
						$errorReporting->register($error);
						break;
				}
			}
		}
	}

	/**
	 * Get primary target name
	 * 
	 * @param targetName    Target Name
	 */
	public function getPrimaryTargetName()
	{
		return $this->primaryTarget;
	}

	/**
	 * Get primary tool-chain name
	 * 
	 * @param toolchainName    Tool-chain name
	 */
	public function getPrimaryToolchainName()
	{
		return $this->primaryToolchain;
	}

	/**
	 * Updates the architecture members after all data acquisitions done
	 * 
	 * @param configuration    Configuration object
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function update($configuration, $errorReporting)
	{
		/* update the targets */
		foreach($this->targets as $target)
		{
			$target->update($this->name, $configuration, $errorReporting);
		}
	
		/* update the toolchains */
		foreach($this->toolchains as $toolchain)
		{
			$toolchain->update($this->name, $configuration, $errorReporting);
		}
	}

	/**
	 * Validate the Architecture configurations
	 * 
	 * @param configuration    Configuration object
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function validate($configuration, $errorReporting)
	{
		/* Validate the target configurations */
		foreach($this->targets as $target)
		{
			$target->validate($this->name, $configuration, $errorReporting);
		}
	
		/* Validate the toolchains */
		foreach($this->toolchains as $toolchain)
		{
			$toolchain->validate($this->name, $configuration, $errorReporting);
		}
	}

}

/**
 * Class to handle the target cpu configurations
 * @created 21-Jul-2017 15:44:03
 */
class Target
{

	private $name = "";     /**< \brief Target name */
	private $enable = true;     /**< \brief Enable or Disable the entire target configuration */
	public $outputs = Array();     /**< \brief Target outputs' configurations. */

	/**
	 * Constructor of class
	 * 
	 * @param targetXmlElement    PHP "simple xml object' to configure the target
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function __construct($targetXmlElement, $errorReporting)
	{
		/* Call the XML interface to acquire the configuration*/
		$this->xmlInterface($targetXmlElement, $errorReporting);
	
		if($this->enable)
		{
			/*Report error in case of incorrect config element*/
			if($this->name === "")
			{
				$errorText= "One of the target configurations has parameter 'name' not configured!";
				$error= new Error(ERR::TE, ERR::ID_E_CONFIG_MISSING_NAME, $errorText);
				$errorReporting->register($error);
			}
		}
	}

	/**
	 * XML interface to gather inputs for configuration.
	 * 
	 * @param targetXmlElement    PHP 'simple xml element' for configuration of target.
	 * 
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function xmlInterface($targetXmlElement, $errorReporting)
	{
		/* Extract the attributes*/
		$targetParameters= $targetXmlElement->attributes();
	
		foreach($targetParameters as $targetParameter => $value)
		{
			switch(strtolower($targetParameter))
			{
				case "name":
					$this->name= trim($value);
					break;
				case "enable":
					$this->enable= strtolower(trim($value)) == "true" ? true : false;
					break;
				default:
					$errorText= "Unknown parameter: '". $targetParameter . "' with target configuration: '" . $this->name . "'!";
					$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
					$errorReporting->register($error);
					break;
			}
		}
	
		if($this->enable)
		{
			/* Extract the elements*/
			$targetElements= $targetXmlElement->children();
		
			/*Run through each element to update the data members*/
			foreach($targetElements as $targetElement)
			{
				$element= $targetElement->getName();
				switch(strtolower($element))
				{
					case "output":
						$outputConfig= new Output($targetElement, $errorReporting);
						if($outputConfig->isEnabled())
							$this->outputs[$outputConfig->getType()]= $outputConfig;
						break;
					default:
						$errorText= "Unknown element: '". $element . "' with target configuration: '" . $this->name . "'!";
						$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
						$errorReporting->register($error);
						break;
				}
			}
		}
	}

	/**
	 * Check if the target config is enabled
	 * 
	 * @param enable    Enable status. true: enabled, false: disabled.
	 */
	public function isEnabled()
	{
		return $this->enable;
	}

	/**
	 * Get name of the target
	 * 
	 * @param name    Name of the target
	 */
	public function getName()
	{
		return $this->name;
	}

	/**
	 * Updates the target members after all data acquisitions
	 * 
	 * @param architectureName    Name of the arcitecture where this target is
	 * belonging to
	 * @param configuration    Configuration object to look for tools
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function update($architectureName, $configuration, $errorReporting)
	{
		/* update the outputs */
		foreach($this->outputs as $output)
		{
			$output->update($this->name, $architectureName, $configuration, $errorReporting);
		}
	}

	/**
	 * Validate the Target configurations
	 * 
	 * @param architectureName    Architecture name of the target
	 * @param configuration    Configuration object
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function validate($architectureName, $configuration, $errorReporting)
	{
		if(count($this->outputs) === 0)
		{
			$errorText= "Target configuration: '" . $this->name . "' has no 'outputs' configured!";
			$error= new Error(ERR::TE, ERR::ID_E_CONFIG_MISSING_PARAM, $errorText);
			$errorReporting->register($error);
		}
		else
		{
			/* Validate the output configurations */
			foreach($this->outputs as $output)
			{
				$output->validate($this->name, $architectureName, $configuration, $errorReporting);
			}
		}
	}

}

/**
 * Class to hold information about the executable for a target
 * @created 21-Jul-2017 15:44:03
 */
class Output
{

	private $type = "";     /**< \brief type of the executable file */
	private $enable = true;     /**< \brief Enable to generate such a file */
	private $fileName = "";     /**< \brief Name of the file without extension */
	private $inputs = Array();     /**< \brief Array of inputs (other than obj files) to create output */
	private $toolFullName = "";     /**< \brief Tool to generate the output. */
	private $fullName = "";     /**< \brief Full name of output, format: <architecture name>/<target name> / <output type> */
	private $useObjects = false;     /**< \brief Use object files as inputs */

	/**
	 * Constructor of the class
	 * 
	 * @param outputXmlElement    PHP "simple xml object' to configure the output
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function __construct($outputXmlElement, $errorReporting)
	{
		/* Call the XML interface to acquire the configuration*/
		$this->xmlInterface($outputXmlElement, $errorReporting);
	
		if($this->enable)
		{
			/*Report error in case of missing configurations*/
			if($this->type === "")
			{
				$errorText= "One of the output configurations has parameter 'type' not configured!";
				$error= new Error(ERR::TE, ERR::ID_E_CONFIG_MISSING_PARAM, $errorText);
				$errorReporting->register($error);
			}
	
			/* check if the file name contains the extension, else suffix the type as file extension */
			$pathInfo= pathinfo($this->fileName);
			if($pathInfo['extension'] === "") 
				$this->filename= $this->filename . "." . $this->type;
		}
	}

	/**
	 * Check if the output config is enabled
	 * 
	 * @param enable    Enable status. true: enabled, false: disabled
	 */
	public function isEnabled()
	{
		return $this->enable;
	}

	/**
	 * Get output file type
	 * 
	 * @param type    Output file type
	 */
	public function getType()
	{
		return $this->type;
	}

	/**
	 * XML interface to gather inputs for configuration.
	 * 
	 * @param outputXmlElement    PHP 'simple xml element' for configuration of output.
	 * 
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function xmlInterface($outputXmlElement, $errorReporting)
	{
		/* Extract the attributes*/
		$outputParameters= $outputXmlElement->attributes();
	
		foreach($outputParameters as $outputParameter => $value)
		{
			switch(strtolower($outputParameter))
			{
				case "type":
					$this->type= strtolower(trim($value));
					break;
				case "enable":
					$this->enable= strtolower(trim($value)) == "true" ? true : false;
					break;
				case "filename":
					$this->fileName= trim($value);
					break;
				case "tool":
					$this->toolFullName= trim($value);
					break;
				default:
					$errorText= "Unknown parameter: '". $outputParameter . "' with output configuration: '" . $this->type . "'!";
					$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
					$errorReporting->register($error);
					break;
			}
		}
	
		if($this->enable)
		{
			/* Extract the elements*/
			$outputElements= $outputXmlElement->children();
		
			/*Run through each element to update the data members*/
			foreach($outputElements as $outputElement)
			{
				$element= $outputElement->getName();
				switch(strtolower($element))
				{
					case "input":
						$this->inputs[]= new Input($outputElement, $errorReporting);
						break;
					
					default:
						$errorText= "Unknown element: '". $element . "' with output configuration: '" . $this->type . "'!";
						$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
						$errorReporting->register($error);
						break;
				}
			}
		}
	}

	/**
	 * Get output file name
	 * 
	 * @param filename    Output filename
	 */
	public function getFileName()
	{
		return $this->fileName;
	}

	/**
	 * 
	 * @param toolFullName    Full Name of tool used to generate the output: format:
	 * <architecture name>/<toolchain name>/<tool name>
	 */
	public function getToolFullName()
	{
		return $this->toolFullName;
	}

	/**
	 * Get full name of the output with the format <architecture name>/<target name> /
	 * <output type>
	 * 
	 * @param outputFullName
	 */
	public function getFullName()
	{
		return $this->fullName;
	}

	/**
	 * Updates the output members after all data acquisitions
	 * 
	 * @param targetName    Target Name where this output belongs
	 * @param architectureName    Name of the arcitecture where (for a target output)
	 * the tool is referred
	 * @param configuration    Configuration object to look for tools
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function update($targetName, $architectureName, $configuration, $errorReporting)
	{
		/* Set output full name */
		$this->fullName= $architectureName . "/" . $targetName . "/" . $this->type;
	
		/* Set fullname for the tool */
		$configValue= $this->toolFullName;
		$toolNameParts= explode("/", $configValue);
		$architecture= $configuration->architectures[$architectureName];
	
		/* Analyse the configuration */
		switch(count($toolNameParts))
		{
			case 1:
				/* Only tool name is configured */
				$toolName= $toolNameParts[0];
				$toolchainName= $architecture->getPrimaryToolchainName();
				break;
			
			case 2:
				/* Toolchain name and tool name are configured */
				$toolName= $toolNameParts[1];
				$toolchainName= $toolNameParts[0];
				break;
			
			case 3:
				/* Full name is configured */
				$toolName= $toolNameParts[2];
				$toolchainName= $toolNameParts[1];
				$architectureName= $toolNameParts[0];
				break;
			
			default:
				$errorText= "Wrong tool configuration '" . $configValue . "' with output configuration: '" . $this->type . "'!";
				$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
				$errorReporting->register($error);
				break;
		}
	
		$this->toolFullName= $architectureName . "/" . $toolchainName . "/" . $toolName;
	
		/* there is nothing to update in the inputs
		foreach($this->inputs as $input)
		{
			$input->update($this->type, $targetName, $architectureName, $configuration, $errorReporting);
		}*/
	}

	/**
	 * Validate the output configurations
	 * 
	 * @param targetName    Target name of the output
	 * @param architectureName    Architecture name of the output
	 * @param configuration    Configuration object
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function validate($targetName, $architectureName, $configuration, $errorReporting)
	{
		if($this->enable)
		{
			if($this->fileName === "")
			{
				$errorText= "One of the output configurations has parameter 'filename' not configured!";
				$error= new Error(ERR::TE, ERR::ID_E_CONFIG_MISSING_NAME, $errorText);
				$errorReporting->register($error);
			}
	
			if($this->toolFullName === "")
			{
				$errorText= "Output configuration for: '". $this->fileName . "' has parameter 'tool' not configured!";
				$error= new Error(ERR::TE, ERR::ID_E_CONFIG_MISSING_NAME, $errorText);
				$errorReporting->register($error);
			}
	
			/* Now check the validity of the components which are dependent on other configurations */
			$architecture= $configuration->architectures[$architectureName];
			$target= $architecture->targets[$targetName];
	
			$this->validateToolConfig($configuration, $errorReporting);
		
			foreach($this->inputs as $input)
			{
				$input->validate($this->type, $targetName, $architectureName, $configuration, $errorReporting);
			}
		}
	}

	/**
	 * Get inputs which are dependent on the other output of same target
	 * 
	 * @param configuration    Configuration object to look for tools
	 * @param errorReporting    Object to report errors in configurations
	 */
	private function validateToolConfig($configuration, $errorReporting)
	{
		$toolNameParts= explode("/", $this->toolFullName);
	
		/* Check if the architecture config with name configured, exists */
		$architectureName= $toolNameParts[0];
		if(isset($configuration->architectures[$architectureName]))
		{
			/* Architecture is ok, now check if toolchain config with name configured, exists */
			$architecture= $configuration->architectures[$architectureName];
		
			$toolchainName= $toolNameParts[1];
			if(isset($architecture->toolchains[$toolchainName]))
			{
				$toolchain= $architecture->toolchains[$toolchainName];
			
				$toolName= $toolNameParts[2];
				if(!isset($toolchain->tools[$toolName]))
				{
					$errorText= "Wrong tool configuration '" . $this->toolFullName . "' for output type '" . $this->type . "'. Tool configuration is not available!";
					$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
					$errorReporting->register($error);
				}
			}
			else
			{
				$errorText= "Wrong tool configuration '" . $this->toolFullName . "' for output type '" . $this->type . "'. Toolchain configuration for '" . $toolchainName . "' is not available!";
				$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
				$errorReporting->register($error);
			}
		}
		else
		{
			$errorText= "Wrong tool configuration '" . $this->toolFullName . "' for output type '" . $this->type . "'. Architecture configuration for '" . $architectureName . "' is not available!";
			$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
			$errorReporting->register($error);
		}
	}

	/**
	 * Gets array of inputs assigned
	 * 
	 * @param inputs    Array of input objects
	 */
	public function getInputs()
	{
		return $this->inputs;
	}

	/**
	 * Get inputs which are dependent on the other output of same target
	 * 
	 * @param outputsList    List of outputs to look for
	 * @param errorReporting    Object to report errors in configurations
	 */
	private function validateInputs($outputsList, $errorReporting)
	{
		/* Run through each input an check if configurations are valid */
		foreach($this->inputs as $input)
		{
			$siblingTypes= $input->getSiblingTypes();
			foreach($siblingTypes as $inputType)
			{
				if(!in_array($inputType, array_keys($outputsList)))
				{
					$errorText= "Wrong input type '" . $inputType . "' with output configuration: '" . $this->type . "' not available in any of the outputs of same target!";
					$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
					$errorReporting->register($error);
					break;
				}
			
				if($inputType === $this->type)
				{
					$errorText= "Input type " . $inputType . "' depends on the same output! Cyclic dependency problem!";
					$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
					$errorReporting->register($error);
					break;
				}
			}
		}
	}

	/**
	 * 
	 * @param objectFilesRequired    Object files required, true: Yes required, false:
	 * not required
	 */
	public function areObjectFilesRequired()
	{
		return $this->useObjects;
	}

}

/**
 * Class to handle the input configurations
 * @created 21-Jul-2017 15:44:03
 */
class Input
{

	private $useObjects = true;     /**< \brief Boolean to configure use object files, true: Use object files, false: Don't Use */
	private $siblingTypes = Array();     /**< \brief Sibling output type to use as input */
	private $configFile = "";     /**< \brief Configuration file to use with the tool to create the output */
	private $filePathNames = Array();     /**< \brief File path names which are to be used as inputs to create the output */

	/**
	 * 
	 * @param inputXmlElement    PHP "simple xml object' to configure the input
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function __construct($inputXmlElement, $errorReporting)
	{
		/* Call the XML interface to acquire the configuration*/
		$this->xmlInterface($inputXmlElement, $errorReporting);
	}

	/**
	 * XML interface to gather inputs for configuration.
	 * 
	 * @param inputXmlElement    PHP 'simple xml element' for configuration of input.
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function xmlInterface($inputXmlElement, $errorReporting)
	{
		/* Extract the attributes*/
		$inputParameters= $inputXmlElement->attributes();
	
		foreach($inputParameters as $inputParameter => $value)
		{
			switch(strtolower($inputParameter))
			{
				case "useobjects":
					$this->useObjects= strtolower(trim($value)) == "true" ? true : false;
					break;
				case "siblingtypes":
					$siblingTypes= array_map('trim', explode(',',$value));
					$this->siblingTypes= array_merge($this->siblingTypes, $siblingTypes);
					break;
				case "filepathnames":
					$filePathNames= array_map('trim', explode(',',$value));
					$this->filePathNames= array_merge($this->filePathNames, $filePathNames);
					break;
				default:
					$errorText= "Unknown parameter: '". $inputParameter . "' with input configuration!";
					$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
					$errorReporting->register($error);
					break;
			}
		}
	
	}

	/**
	 * Validate the input configurations
	 * 
	 * @param outputType    Output type
	 * @param targetName    Target name of the output
	 * @param architectureName    Architecture name of the output
	 * @param configuration    Configuration object
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function validate($outputType, $targetName, $architectureName, $configuration, $errorReporting)
	{
		$architecture= $configuration->architectures[$architectureName];
		$target= $architecture->targets[$targetName];
		$outputList= $target->outputs;
	
		$siblingTypes= $this->getSiblingTypes();
		foreach($siblingTypes as $inputType)
		{
			if(!in_array($inputType, array_keys($outputList)))
			{
				$errorText= "Wrong input type '" . $inputType . "' with output configuration: '" . $this->type . "' not available in any of the outputs of same target!";
				$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
				$errorReporting->register($error);
				break;
			}
		
			if($inputType === $this->type)
			{
				$errorText= "Input type " . $inputType . "' depends on the same output! Cyclic dependency problem!";
				$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
				$errorReporting->register($error);
				break;
			}
		}
	
		if(!$this->useObjects)
		{
			if((count($this->siblingTypes) === 0) &&
				(count($this->filePathNames) === 0))
			{
				$errorText= "Input configuration with output configuration: '" . $this->type . "', has parameter 'useObjects= false' either of parameters 'siblingTypes' or 'filePathNames', not configured!";
				$error= new Error(ERR::TE, ERR::ID_E_CONFIG_MISSING_NAME, $errorText);
				$errorReporting->register($error);
			}
		}
	}

	/**
	 * Updates the input members after all data acquisitions
	 * 
	 * @param outputType    Output type
	 * @param targetName    Target Name where this output belongs
	 * @param architectureName    Name of the arcitecture where (for a target output)
	 * the tool is referred
	 * @param configuration    Configuration object to look for tools
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function update($outputType, $targetName, $architectureName, $configuration, $errorReporting)
	{
	}

	/**
	 * Checks if objects are to be used as inputs
	 * 
	 * @param result    True: Objects are needed as inputs, false: objects not needed
	 */
	public function areObjectsAsInput()
	{
		return $this->useObjects;
	}

	/**
	 * Gets sibling types list
	 * 
	 * @param siblingTypes    List of sybling types
	 */
	public function getSiblingTypes()
	{
		return $this->siblingTypes;
	}

	/**
	 * Gets files' path names list
	 * 
	 * @param pathNames    List of files' path names
	 */
	public function getFilePathNames()
	{
		return $this->filePathNames;
	}

	/**
	 * Gets configuration file input
	 * 
	 * @param configFIle    Configuration file input
	 */
	public function getConfigFile()
	{
		return $this->ConfigFile;
	}

}

/**
 * Class to contain tool-chain's configuration
 * @created 21-Jul-2017 15:44:03
 */
class Toolchain
{

	private $name = "";     /**< \brief Name of the tool-chain */
	private $enable = true;     /**< \brief Enable or Disable the entire tool-chain configuration */
	private $command = "";     /**< \brief  */
	private $path = "";     /**< \brief Path to the tools */
	private $architecture;     /**< \brief Architecture object */
	private $configFolder = "";     /**< \brief Path to tool-chain configurations */
	private $configFiles = Array();     /**< \brief Configuration files to configure the tool-chain */
	private $verbose = false;     /**< \brief Verbose configuration, for display of command invocation */
	public $tools = Array();     /**< \brief Configuration for tools in the toolchain */

	/**
	 * Constructor of the class
	 * 
	 * @param toolchainXmlElement    PHP "simple xml object' to configure the
	 * toolchain
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function __construct($toolchainXmlElement, $errorReporting)
	{
		/* Call the XML interface to acquire the configuration*/
		$this->xmlInterface($toolchainXmlElement, $errorReporting);
	
		if($this->enable)
		{
			/*Report error in case of incorrect config element*/
			if($this->name === "")
			{
				$errorText= "One of the toolchain configurations has parameter 'name' not configured!";
				$error= new Error(ERR::TE, ERR::ID_E_CONFIG_MISSING_NAME, $errorText);
				$errorReporting->register($error);
			}
		}
	}

	/**
	 * XML interface to gather inputs for configuration.
	 * 
	 * @param toolchainXmlElement    PHP 'simple xml element' for configuration of
	 * toolchain.
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function xmlInterface($toolchainXmlElement, $errorReporting)
	{
		/* Extract the attributes*/
		$toolchainParameters= $toolchainXmlElement->attributes();
	
		/* Run through toolchain parameters to update the data members */
		foreach($toolchainParameters as $toolchainParameter => $value)
		{
			switch(strtolower($toolchainParameter))
			{
				case "name":
					$this->name= trim($value);
					break;
				case "enable":
					$this->enable= strtolower(trim($value)) == "true" ? true : false;
					break;
				case "configfolder":
					$value= str_replace("\\","/",$value);
					$this->configFolder= str_replace("\\","/",trim($value));
					break;
				case "configfiles":
					$value= str_replace("\\","/",$value);
					$configFiles= explode(',',$value);
					$this->configFiles= array_merge($this->configFiles, array_map('trim', $configFiles));
					break;
				case "path":
					$this->path= str_replace("\\","/",trim($value));
					break;
				case "verbose":
					$this->verbose= strtolower(trim($value)) == "true" ? true : false;
					break;
				default:
					$errorText= "Unknown parameter: '". $toolchainParameter . "' with toolchain configuration: '" . $this->name . "'!";
					$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
					$errorReporting->register($error);
					break;
			}
		}
	
		if($this->enable)
		{
			/* Extract the elements */
			$toolchainElements= $toolchainXmlElement->children();
		
			/*Run through each element to update the data members*/
			foreach($toolchainElements as $toolchainElement)
			{
				$element= $toolchainElement->getName();
				switch(strtolower($element))
				{
					case "tool":
						$toolConfig= new Tool($toolchainElement, $errorReporting);
						$this->tools[$toolConfig->getName()]= $toolConfig;
						break;
					default:
						$errorText= "Unknown element: '". $element . "' with tool configuration: '" . $this->name . "'!";
						$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
						$errorReporting->register($error);
						break;
				}
			}
		}
	}

	/**
	 * Check if the toolchain config is enabled
	 * 
	 * @param enable    Enable status. true: enabled, false: disabled
	 */
	public function isEnabled()
	{
		return $this->enable;
	}

	/**
	 * Get the toolchain name
	 * 
	 * @param name    Name of the toolchain
	 */
	public function getName()
	{
		return $this->name;
	}

	/**
	 * Get the tool-chain installation path
	 * 
	 * @param path    Toolchain installation path
	 */
	public function getPath()
	{
		return $this->path;
	}

	/**
	 * Updates the toolchain members after all data acquisitions
	 * 
	 * @param architectureName    Name of the arcitecture where this toolchain is
	 * belonging to
	 * @param configuration    Configuration object to look for tools
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function update($architectureName, $configuration, $errorReporting)
	{
		/* update the tools */
		foreach($this->tools as $tool)
		{
			$tool->update($this->name, $architectureName, $configuration, $errorReporting);
		}
	}

	/**
	 * Validate the Tool-chain configurations
	 * 
	 * @param architectureName    Architecture name of the toolchain
	 * @param configuration    Configuration object
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function validate($architectureName, $configuration, $errorReporting)
	{
		if($this->path === "")
		{
			$errorText= "Toolchain configuration '" . $this->name . "', has parameter 'path' not configured!";
			$error= new Error(ERR::TE, ERR::ID_E_CONFIG_MISSING_PARAM, $errorText);
			$errorReporting->register($error);
		}
	
		if(count($this->tools) === 0)
		{
			$errorText= "Toolchain configuration '" . $this->name . "', has element 'tool' not configured!";
			$error= new Error(ERR::TE, ERR::ID_E_CONFIG_MISSING_PARAM, $errorText);
			$errorReporting->register($error);
		}
	
		/* Validate each of the configured tool */
		foreach($this->tools as $tool)
		{
			$tool->validate($this->name, $architecture, $configuration, $errorReporting);
		}
	}

	/**
	 * Get tool name
	 * 
	 * @param verbose    Verbose informatin
	 */
	public function isVerbose()
	{
		return $this->verbose;
	}

	/**
	 * Get the tool-chain configuration path
	 * 
	 * @param folderPath    Configuration folder path
	 */
	public function getConfigFolder()
	{
		return $this->configFolder;
	}

	/**
	 * Get the tool-chain installation path
	 * 
	 * @param configFiles    Array of configuration files, which contain the toolchain
	 * configuration
	 */
	public function getConfigFiles()
	{
		return $this->configFiles;
	}

}

/**
 * Class to contain configuration elements for tools such as compilers, linkers e.
 * t.c.
 * @created 21-Jul-2017 15:44:03
 */
class Tool
{

	private $name = "";     /**< \brief Name of the option set. This is important for selection of options at file selection configuration. */
	private $type = 'COMPILER';     /**< \brief Type of the options. Enum values: 'COMPILER', 'ASSEMBLER', 'LINKER' */
	private $command;     /**< \brief Tool command */
	private $path;     /**< \brief Installation path to the tool (tool-chain path) */
	private $primaryOptionSetId = "";     /**< \brief Id of the option set, to be taken by default for a file for an architecture */
	private $nextToolNames = Array();     /**< \brief Next tool names to be used after the recipe for current tool is called. This is an array. (optional) */
	private $fullName = "";     /**< \brief Full name of tool, format: <architecture name>/<tool-chain name> / <tool name> */
	private $verbose = false;     /**< \brief Verbose configuration, for display of command invocation */
	public $optionSets = Array();     /**< \brief Option sets one of which is used during tool usage */
	public $template = "";     /**< \brief Template for the make recipe */
	public $nextTools = Array();     /**< \brief Array of next tool objects */
	public $arguments = Array();     /**< \brief Argument objects */
	public $m_Tool;

	/**
	 * Constructor of the Class
	 * 
	 * @param toolXmlElement    PHP 'simple xml element' for configuration of tools
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function __construct($toolXmlElement, $errorReporting)
	{
		/* Call the XML interface to acquire the configuration*/
		$this->xmlInterface($toolXmlElement, $errorReporting);
	
		/*Reoprt error in case of incorrect config element*/
		if($this->name === "")
		{
			$errorText= "One of the tool configurations has parameter 'name' not configured!";
			$error= new Error(ERR::TE, ERR::ID_E_CONFIG_MISSING_NAME, $errorText);
			$errorReporting->register($error);
		}
		else
		{
			if(($this->type !== 'COMPILER') &&
			   ($this->type !== 'ASSEMBLER') &&
			   ($this->type !== 'LINKER')  &&
			   ($this->type !== 'CBINARRAY') &&
			   ($this->type !== 'ARCHIVER') &&
			   ($this->type !== 'OTHER'))
			{
				$errorText= "With tool configuration '" . $this->name . "', parameter type: '". $this->type . "' is not any of 
				'COMPILER', 'ASSEMBLER', 'LINKER' 'CBINARRAY', 'ARCHIVER' or 'OTHER'!";
				$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
				$errorReporting->register($error);
			}
	
			if($this->command === "")
			{
				$errorText= "With tool configuration '" . $this->name . "', parameter 'command' not configured!";
				$error= new Error(ERR::TE, ERR::ID_E_CONFIG_MISSING_PARAM, $errorText);
				$errorReporting->register($error);
			}
		
			/*Check if the primary optionset configuration matches with any of the optionsets configured*/
			if($this->primaryOptionSetId !== "")
			{
				if(!array_key_exists($this->primaryOptionSetId, $this->optionSets))
				{
					$errorText= "Wrong configuration! Primary Option Set: '". $this->primaryOptionSetId . "' doesn't exist in the option sets with tool: '" . $this->name . "'!";
					$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
					$errorReporting->register($error);
					break;
				}
			}
			else
			{
				if(count($this->optionSets) > 0)
				{
					$optionSetIds= array_keys($this->optionSets);
					$this->primaryOptionSetId= $optionSetIds[0];
				}
			}
		}
	}

	/**
	 * XML interface to gather inputs for configuration.
	 * 
	 * @param toolXmlElement    PHP 'simple xml element' for configuration of tool.
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function xmlInterface($toolXmlElement, $errorReporting)
	{
		$toolParameters= $toolXmlElement->attributes();
	
		/*Run through each parameter to update the data members*/
		foreach($toolParameters as $toolParameter => $value)
		{
			switch(strtolower($toolParameter))
			{
				case "name":
					$this->name= trim($value);
					break;
				case "type":
					$this->type= strtoupper(trim($value));
					break;
				case "command":
					$this->command= trim($value);
					break;
				case "path":
					$this->path= str_replace("\\","/",trim($value));
					break;
				case "verbose":
					$this->verbose= strtolower(trim($value)) == "true" ? true : false;
					break;
				case "nexttools":
					$this->nextToolNames= array_map('trim', explode(',',$value));
					break;
				case "primaryoptionset":
					$this->primaryOptionSetId= trim($value);
					break;
				default:
					$errorText= "Unknown parameter: '". $toolParameter . "' with tool configuration: '" . $this->name . "'!";
					$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
					$errorReporting->register($error);
					break;
			}
		}
	
		/* Extract the elements*/
		$toolElements= $toolXmlElement->children();
	
		/*Run through each element to update the data members*/
		foreach($toolElements as $toolElement)
		{
			$element= $toolElement->getName();
			switch(strtolower($element))
			{
				case "optionset":
					$optionSetConfig= new OptionSet($toolElement, $errorReporting);
					$this->optionSets[$optionSetConfig->getId()]= $optionSetConfig;
					break;
				case "argument":
					$argument= new Argument($toolElement, $errorReporting);
					if($argument->getTemplate() !== "")
					{
						$this->arguments[]= $argument;
					}
					break;
				default:
					$errorText= "Unknown element: '". $element . "' with tool configuration: '" . $this->name . "'!";
					$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
					$errorReporting->register($error);
					break;
			}
		}
	}

	/**
	 * Get tool name
	 * 
	 * @param name    Tool name
	 */
	public function getName()
	{
		return $this->name;
	}

	/**
	 * Get tool type
	 * 
	 * @param type    Tool type
	 */
	public function getType()
	{
		return $this->type;
	}

	/**
	 * Get Primary Option-set Id
	 * 
	 * @param optionSetId    Option-set id
	 */
	public function getPrimaryOptionSetId()
	{
		return $this->primaryOptionSetId;
	}

	/**
	 * Get full name of the tool with the format <architecture name>/<tool-chain name>
	 * / <tool name>
	 * 
	 * @param toolFullName    Tools full name format <architecture name>/<tool-chain
	 * name> / <tool name>
	 */
	public function getFullName()
	{
		return $this->fullName;
	}

	/**
	 * Gets architecture name of the tool
	 * 
	 * @param architectureName    Architecture name
	 */
	public function getArchitectureName()
	{
		$toolFullNameParts= explode("/", $this->fullName); //toolFullname format <architecture name>/<toolchain name>/<tool name>
		return $toolFullNameParts[0];
	}

	/**
	 * Updates the tool members after all data acquisitions
	 * 
	 * @param toolchainName    Parent toolchain name
	 * @param architectureName    Parent arcitecture name
	 * @param configuration    Configuration object
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function update($toolchainName, $architectureName, $configuration, $errorReporting)
	{
		/* Set full name */
		$this->fullName= $architectureName . "/" . $toolchainName . "/" . $this->name;
	
		$architecture= $configuration->architectures[$architectureName];
		$toolchain= $architecture->toolchains[$toolchainName];
	
		/* SetPath for the tool if not configured */
		if(!isset($this->path))
		{
			$this->path= $toolchain->getPath();
		}
	
		/* Update next tools */
		$this->updateNextTools($toolchainName, $architectureName, $configuration, $errorReporting);
	
		/* Update the Optionsets */
		foreach($this->optionSets as $optionSet)
		{
			$optionSet->update($this->name, $toolchainName, $architectureName, $configuration, $errorReporting);  //TODO actually there is nothing to call
		}
	
		/* Update the Arguments */
		$this->updateArgumentIndices($errorReporting);
		foreach($this->arguments as $argument)
		{
			$argument->update($this->name, $toolchainName, $architectureName, $configuration, $errorReporting);
		}
	
		/* Update Verbose */
		if($toolchain->isVerbose())
		{
			$this->verbose= true;
		}
	}

	/**
	 * Get command user interface, command with its tool-chain path
	 * 
	 * @param commandUI    Command User Interface
	 */
	public function getCommandUI()
	{
		$verbose= (!$this->verbose) ? "@" : "";
	
		if($this->path !== "")
		{
			$command= $verbose . 
					"\"" . str_replace("\\", "/", $this->path) . "\"" . "/" . 
					$this->command;
		}
		else
		{
			$command= $verbose . $this->command;
		}
		return $command;
	}

	/**
	 * Get tool name
	 * 
	 * @param verbose    Verbose informatin
	 */
	public function isVerbose()
	{
		return $this->verbose;
	}

	/**
	 * Validate the Tool configurations
	 * 
	 * @param toolchainName    Parent toolchain name
	 * @param architectureName    Parent architecture name
	 * @param configuration    Configuration object
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function validate($toolchainName, $architectureName, $configuration, $errorReporting)
	{
		/* Validate the next tools */
		foreach($this->nextToolNames as $toolFullName)
		{
			$toolNameParts= explode("/", $toolFullName);
	
			/* Check if the architecture config with name configured, exists */
			$architectureName= $toolNameParts[0];
			if(isset($configuration->architectures[$architectureName]))
			{
				/* Architecture is ok, now check if toolchain config with name configured, exists */
				$architecture= $configuration->architectures[$architectureName];
			
				$toolchainName= $toolNameParts[1];
				if(isset($architecture->toolchains[$toolchainName]))
				{
					$toolchain= $architecture->toolchains[$toolchainName];
				
					$toolName= $toolNameParts[2];
					if(!isset($toolchain->tools[$toolName]))
					{
						$errorText= "Wrong configuration for next tool '" . $toolFullName . "', Tool '" . $toolName . "'. configuration is not available!";
						$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
						$errorReporting->register($error);
					}
				}
				else
				{
					$errorText= "Wrong configuration for next tool '" . $toolFullName . "', Toolchain '" . $toolchainName . "'. configuration is not available!";
					$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
					$errorReporting->register($error);
				}
			}
			else
			{
				$errorText= "Wrong configuration for next tool '" . $toolFullName . "', architecture '" . $architectureName . "'. configuration is not available!";
				$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
				$errorReporting->register($error);
			}
		}
	
		/* Validate the option sets */
		foreach($this->optionSets as $optionSet)
		{
			$optionSet->validate($this->name, $toolchainName, $architectureName, $configuration, $errorReporting); //TODO actually there is nothing to call
		}
	
		/* Validate the arguments */
		foreach($this->arguments as $argument)
		{
			$argument->validate($this->name, $toolchainName, $architectureName, $configuration, $errorReporting);
		}
	}

	/**
	 * Creates full name of the tool based on the available information
	 * 
	 * @param architectureName    Architecture name where the tool is to
	 * @param toolName    Tool name to be used
	 */
	public function constructFullName($architectureName, $toolName)
	{
		/* Set fullname for the tool */
		$toolNameParts= explode("/", $toolName);
		$architecture= $configuration->architectures[$architectureName];
	
		/* Analyse the configuration */
		switch(count($toolNameParts))
		{
			case 1:
				/* Only tool name is configured */
				$toolName= $toolNameParts[0];
				break;
			
			case 2:
				/* Toolchain name and tool name are configured */
				$toolName= $toolNameParts[1];
				$toolchainName= $toolNameParts[0];
				break;
			
			case 3:
				/* Full name is configured */
				$toolName= $toolNameParts[2];
				$toolchainName= $toolNameParts[1];
				$architectureName= $toolNameParts[0];
				break;
			
			default:
				$errorText= "Wrong tool configuration '" . $configValue . "' with output configuration: '" . $this->type . "'!";
				$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
				$errorReporting->register($error);
				break;
		}
	
		$this->toolFullName= $architectureName . "/" . $toolchainName . "/" . $toolName;
	}

	/**
	 * Updates the tool members after all data acquisitions
	 * 
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function updateArgumentIndices($errorReporting)
	{
		/* Initialize two empty arrays to separate indexed and non indexed arrays */
		$arguments= Array(); // Initialize an array for the final list
		$indexed= Array();
	
		/* Separate out indexed and non indexed arrays */
		foreach($this->arguments as $argument)
		{
			if($argument->getIndex() === "")
			{
				$arguments[]= $argument;
			}
			else
			{
				$indexed[]= $argument;
			}
		}
	
		/* Insert the indexed argument */
		foreach($indexed as $argument)
		{
			$index= min(count($arguments), $argument->getIndex());
			array_splice($arguments, $index, 0, array($argument));
		}
	
		$this->arguments= $arguments;
	}

	/**
	 * Updates the next tools
	 * 
	 * @param toolchainName    Parent toolchain name
	 * @param architectureName    Parent arcitecture name
	 * @param configuration    Configuration object
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function updateNextTools($toolchainName, $architectureName, $configuration, $errorReporting)
	{
		/* Update next tools */
		$nextToolNames= Array(); // inilialize with empty array
		foreach($this->nextToolNames as $nextToolName)
		{
			$toolNameParts= explode("/", $nextToolName);
	
			$errorVal= false; // Initialize the error value in this iteration
			/* Analyse the configuration */
			switch(count($toolNameParts))
			{
				case 1:
					/* Only tool name is configured */
					$toolName= $toolNameParts[0];
					break;
				
				case 2:
					/* Toolchain name and tool name are configured */
					$toolName= $toolNameParts[1];
					$toolchainName= $toolNameParts[0];
					break;
				
				case 3:
					/* Full name is configured */
					$toolName= $toolNameParts[2];
					$toolchainName= $toolNameParts[1];
					$architectureName= $toolNameParts[0];
					break;
				
				default:
					$errorVal= true;
					$errorText= "Wrong tool configuration '" . $configValue . "' with output configuration: '" . $this->type . "'!";
					$error= new Error(ERR::TE, ERR::ID_E_CONFIG_WRONG_PARAM, $errorText);
					$errorReporting->register($error);
					break;
			}
		
			if(!$errorVal)
			{
				$nextToolNames[]= $architectureName . "/" . $toolchainName . "/" . $toolName;
				$architecture= $configuration->architectures[$architectureName];
				$toolchain= $architecture->toolchains[$toolchainName];
				$this->nextTools[]= $toolchain->tools[$toolName];
			}
		}
		$this->nextToolNames= $nextToolNames;  // Assign the next tool names
	
	}

	/**
	 * Gets tool-chain name of the tool
	 * 
	 * @param toolchainName    Toolchain name
	 */
	public function getToolchainName()
	{
		$toolFullNameParts= explode("/", $this->fullName); //toolFullname format <architecture name>/<toolchain name>/<tool name>
		return $toolFullNameParts[1];
	}

}

/**
 * Class to hold the argument data. Arguments are used with tool commands.
 * @created 21-Jul-2017 15:44:03
 */
class Argument
{

	private $index;     /**< \brief Argument index how it is to be appearing with command */
	private $template = "";     /**< \brief Argument template */

	/**
	 * Constructor of the Class
	 * 
	 * @param argumentXmlElement    PHP 'simple xml element' for configuration of
	 * arguments
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function __construct($argumentXmlElement, $errorReporting)
	{
		/* Call the XML interface to acquire the configuration*/
		$this->xmlInterface($argumentXmlElement, $errorReporting);
	}

	/**
	 * XML interface to gather inputs for configuration.
	 * 
	 * @param argumentXmlElement    PHP 'simple xml element' for configuration of
	 * argument.
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function xmlInterface($argumentXmlElement, $errorReporting)
	{
		$argumentParameters= $argumentXmlElement->attributes();
	
		/*Run through each parameter to update the data members*/
		foreach($argumentParameters as $argumentParameter => $value)
		{
			switch(strtolower($argumentParameter))
			{
				case "index":
					$this->index= trim($value);
					break;
				case "template":
					$this->template= trim($value);
					break;
				default:
					$errorText= "Unknown parameter: '". $argumentParameter . "' with Argument configuration!";
					$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
					$errorReporting->register($error);
					break;
			}
		}
	}

	/**
	 * Validate the Argument configurations
	 * 
	 * @param toolName    Parent tool name
	 * @param toolchainName    Parent toolchain name
	 * @param architectureName    Parent architecture name
	 * @param configuration    Configuration object
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function validate($toolName, $toolchainName, $architectureName, $configuration, $errorReporting)
	{
		/* Validate the arguments */
	
	}

	/**
	 * Updates the argument members after all data acquisitions
	 * 
	 * @param toolName    Parent tool name
	 * @param toolchainName    Parent toolchain name
	 * @param architectureName    Parent arcitecture name
	 * @param configuration    Configuration object
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function update($toolName, $toolchainName, $architectureName, $configuration, $errorReporting)
	{
	}

	/**
	 * Gets the template string of the argument
	 * 
	 * @param template    Template string of the argument
	 */
	public function getTemplate()
	{
		return $this->template;
	}

	/**
	 * Gets the index of the argument
	 * 
	 * @param index    Index of the argument
	 */
	public function getIndex()
	{
		return $this->index;
	}

}

/**
 * Options set required to use the tool
 * @created 21-Jul-2017 15:44:03
 */
class OptionSet
{

	private $id = "";     /**< \brief Identification of the option set */
	public $options = "";     /**< \brief Identification of the option set */

	/**
	 * Constructor of the class
	 * 
	 * @param optionSetXmlElement    PHP "simple xml object' to configure the
	 * optionset
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function __construct($optionSetXmlElement, $errorReporting)
	{
		/* Call the XML interface to acquire the configuration*/
		$this->xmlInterface($optionSetXmlElement, $errorReporting);
	
		/*Reoprt error in case of incorrect config element*/
		if($this->id === "")
		{
			$errorText= "One of the option set configurations has parameter 'id' not configured!";
			$error= new Error(ERR::TE, ERR::ID_E_CONFIG_MISSING_NAME, $errorText);
			$errorReporting->register($error);
		}
	}

	/**
	 * XML interface to gather inputs for configuration.
	 * 
	 * @param optionSetXmlElement    PHP 'simple xml element' for configuration of
	 * option set.
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function xmlInterface($optionSetXmlElement, $errorReporting)
	{
		$optionSetParameters= $optionSetXmlElement->attributes();
	
		/*Run through each parameter to update the data members*/
		foreach($optionSetParameters as $optionSetParameter => $value)
		{
			switch(strtolower($optionSetParameter))
			{
				case "id":
					$this->id= trim($value);
					break;
				default:
					$errorText= "Unknown parameter: '". $optionSetParameter . "' with option set configuration: '" . $this->id . "'!";
					$error= new Error(ERR::TW, ERR::ID_W_CONFIG_UNKNOWN_PARAM, $errorText);
					$errorReporting->register($error);
					break;
			}
		}
	
		$this->options= trim((string)$optionSetXmlElement);
	}

	/**
	 * Get option set id
	 * 
	 * @param id    Option set id
	 */
	public function getId()
	{
		return $this->id;
	}

	/**
	 * Updates the option set members after all data acquisitions
	 * 
	 * @param toolName    Parent tool name
	 * @param toolchainName    Parent toolchain name
	 * @param architectureName    Parent arcitecture name
	 * @param configuration    Configuration object
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function update($toolName, $toolchainName, $architectureName, $configuration, $errorReporting)
	{
	}

	/**
	 * Validate the Option-set configurations
	 * 
	 * @param toolName    Parent tool name
	 * @param toolchainName    Parent toolchain name
	 * @param architectureName    Parent architecture name
	 * @param configuration    Configuration object
	 * @param errorReporting    Object to report errors in configurations
	 */
	public function validate($toolName, $toolchainName, $architectureName, $configuration, $errorReporting)
	{
		/* Validate the optionsets */
	
	}

}
?>