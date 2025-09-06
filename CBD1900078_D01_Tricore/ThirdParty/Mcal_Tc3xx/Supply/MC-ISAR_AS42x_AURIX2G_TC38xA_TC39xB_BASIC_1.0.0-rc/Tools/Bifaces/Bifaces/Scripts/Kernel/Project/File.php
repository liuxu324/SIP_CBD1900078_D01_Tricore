<?php
/**----------------------------------------------------------------------------
 * \file File.php
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
 
namespace Kernel\Project;


require_once ('/../Configuration/Architecture.php');
require_once ('/../Configuration/Configuration.php');

use Kernel\Configuration\Tool;
use Kernel\Configuration\Configuration;
use Kernel\Configuration\CFG;

/**
 * File to represent information for a file in a project
 * @created 21-Jul-2017 15:44:04
 */
class File
{

	public $pathName;     /**< \brief File path name */
	private $targetFullNames = Array();     /**< \brief Array of targets full names with format <architecture name> / <target name> */
	public $toolchainNames_ToBeRemoved = Array();     /**< \brief REMOVE: Array of tool-chain names <architecture name> / <tool-chain name> */
	private $tools = Array();     /**< \brief Array of tools which are to be used to build the file per architecture */
	private $optionSetIds = Array();     /**< \brief Option set array for source file per architecture */
	private $configuration;     /**< \brief Project configuration object */
	private $buildToolType = "COMPILER";     /**< \brief type of tool to build file during build phases */
	private $targetNames = Array();     /**< \brief Array of target names with format per architecture */

	/**
	 * Constructor of File
	 * 
	 * @param pathName    Path name of the file
	 * @param configuration    Project configuration object
	 */
	public function __construct($pathName, $configuration)
	{
		/* Step 1: Initialize path name and project configuration object */
		$this->pathName= $pathName;
		$this->configuration= $configuration;
	
		/* Step 2: Get the requied build tool type; Extract from file extension */
		$pathInfo= pathinfo($pathName);
		$fileExtn= strtoupper($pathInfo['extension']);
		$cExtns= array_map('strtoupper', explode(',',CFG::C_FILE_EXTENSIONS));  //makes all elements to uppercase
		$asmExtns= array_map('strtoupper', explode(',',CFG::ASM_FILE_EXTENSIONS));  //makes all elements to uppercase
	
		if(in_array($fileExtn, $cExtns))
		{
			$this->buildToolType= 'COMPILER'; // For C or CPP files tool required is COMPILER
		}
		else if(in_array($fileExtn, $asmExtns))
		{
			$this->buildToolType= 'ASSEMBLER'; // For ASM files tool required is ASSEMBLER
		}
		else
		{
			$this->buildToolType= 'OTHER'; // Need no build tool which is file specific (Linker would be for Target with all obj files)
		}
	}

	/**
	 * Get the tool which is required to build the file for the target archicture
	 * 
	 * @param targetName    Name of the target which is to be built from the file
	 * object
	 * @param toolName    Return tool names as a string
	 */
	public function getToolName_ToBeRemoved($targetName)
	{
		return $this->toolNames[$targetName];
	}

	/**
	 * Updates tool for all the targets which are supported by the tool.
	 * 
	 * @param toolFullName    Tool full name with complete name format: Architecture
	 * Name / Toolchain name / Tool Name
	 */
	public function updateTool($toolFullName)
	{
		/* get the target names which are affected by the tool */
		$toolFullNameParts= array_map('trim', explode('/', $toolFullName));
		$architectureName= $toolFullNameParts[0];
		$architecture= $this->configuration->architectures[$architectureName];
	
		$targetsInArchitecture= Array(); // initialize
		foreach(array_keys($architecture->targets) as $targetName)
		{
			$targetsInArchitecture[]= $architectureName . "/" . $targetName;
		}
	
		$targetFullNames= array_intersect($this->targetFullNames, $targetsInArchitecture);
	
		/* Get the tool */
		$toolchain= $architecture->toolchains[$toolFullNameParts[1]];
		$tool= $toolchain->tools[$toolFullNameParts[2]];
	
		if($this->buildToolType === $tool->getType())
		{
			/* Run through affected target names */
			if(count($targetFullNames) > 0)
			{
				/* Update tool object */
				$this->tools[$architectureName]= $tool;
			
				/* Assign the primary option set of the tool */
				$this->optionSetIds[$architectureName]= $tool->getPrimaryOptionSetId();
			}
		}
	}

	/**
	 * Updates all the information which are associated with target, which is passed
	 * as string archName/targetName.
	 * For target, get the architecture, which contains this target and assign the
	 * tool from configured primary tool-chains of such architecture.
	 * 
	 * @param targetFullName    Target full name as string with format <architecture
	 * name> / <target name>
	 */
	public function updateTarget($targetFullName)
	{
		/* Update target names array if the elements are not existing already */
		if(!in_array($targetFullName, $this->targetFullNames))
		{
			/* Extract architecture name */
			$targetFullNameParts= explode("/", $targetFullName);
			$architectureName= $targetFullNameParts[0];
	
			/* Update targetnames array variables */
			$this->targetFullNames[]= $targetFullName;
			$this->targetNames[$architectureName][]= $targetFullNameParts[1];
		
			/* Update all target related data towards building the file */
			{
				/* Get the primary toolchain of the architecture */
				$architecture= $this->configuration->architectures[$architectureName];
				$primToolchainName= $architecture->getPrimaryToolchainName();
				$primToolchain= $architecture->toolchains[$primToolchainName];
	
				/* Findout required type of tool based on file name */
				foreach($primToolchain->tools as $tool)
				{
					if($this->buildToolType === $tool->getType())
					{
						/* Update tool object */
						$this->tools[$architectureName]= $tool;
					
						/* Assign the primary option set id of the tool */
						$this->optionSetIds[$architectureName]= $tool->getPrimaryOptionSetId();
					}
				}
			}
		}
	}

	/**
	 * Gets the targets as an array
	 * 
	 * @param targetFullNames    Return target's full names as array
	 */
	public function getTargetFullNames()
	{
		return $this->targetFullNames;
	}

	/**
	 * Updates the option sets for the affected target's tools
	 * 
	 * @param optionSetFullName    Complete name of the option set with format:
	 * Architecture Name / Toolchain name / Tool Name / OptionSetId
	 */
	public function updateOptionSet($optionSetFullName)
	{
		/* get the target names which are affected by the tool */
		$optionSetFullNameParts= array_map('trim', explode('/', $optionSetFullName));
		$architectureName= $optionSetFullNameParts[0];
		$architecture= $this->configuration->architectures[$architectureName];
	
		$targetsInArchitecture= Array(); // initialize
		foreach(array_keys($architecture->targets) as $targetName)
		{
			$targetsInArchitecture[]= $architectureName . "/" . $targetName;
		}
	
		$targetFullNames= array_intersect($this->targetFullNames, $targetsInArchitecture);
	
		/* Get the tool */
		$toolchain= $architecture->toolchains[$optionSetFullNameParts[1]];
		$tool= $toolchain->tools[$optionSetFullNameParts[2]];
	
		if($this->buildToolType === $tool->getType())
		{
			/* Run through affected target names */
			if(count($targetFullNames) > 0)
			{	
				/* Assign the option set id of the tool */
				$this->optionSetIds[$architectureName]= $optionSetFullNameParts[3];
			}
		}
	}

	/**
	 * Get the file assigned tool object for the requested architecture name
	 * 
	 * @param architectureName    Architecture name for which tool is requested
	 * @param tools    Array of tool objects
	 */
	public function getTool($architectureName)
	{
		return $this->tools[$architectureName];
	}

	/**
	 * Get list of architecture names for which the file is targeted to be built
	 * 
	 * @param architectureNames    Array of architecture names for which the file is
	 * targeted to be built
	 */
	public function getArchitectureNames()
	{
		return array_keys($this->targetNames);
	}

	/**
	 * Get the file assigned option-set id for the requested architecture name
	 * 
	 * @param architectureName    Architecture name for which option set is requested
	 * @param optionSetId    Requested optionset id
	 */
	public function getOptionSetId($architectureName)
	{
		return $this->optionSetIds[$architectureName];
	}

	/**
	 * Gets the targets as an array
	 * 
	 * @param architectureName    Architecture name for which target names are
	 * requested
	 * @param targetNames    Return target names as array
	 */
	public function getTargetNames($architectureName)
	{
		return $this->targetNames[$architectureName];
	}

}
?>