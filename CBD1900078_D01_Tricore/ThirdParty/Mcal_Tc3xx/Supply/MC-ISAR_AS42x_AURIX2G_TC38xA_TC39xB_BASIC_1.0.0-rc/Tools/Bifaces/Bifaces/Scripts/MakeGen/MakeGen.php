<?php
/**----------------------------------------------------------------------------
 * \file MakeGen.php
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
require_once ('MakeFile.php');
require_once ('MakeData.php');
require_once ('/../Kernel/Configuration/Configuration.php');

use MakeGen\CommandLineInput;
use Kernel\Project\Project;
use MakeGen\SubFolderMakeFile;
use MakeGen\ProjectMakeFile;
use MakeGen\ProjectData;
use Kernel\Configuration\CFG;

/**
 * Class to hold command line input info
 * @created 21-Jul-2017 15:44:03
 */
class CommandLineInput
{

	public $files = Array();     /**< \brief Array of file names */
	private $displayErrors = false;     /**< \brief Switch to enable or disable the error messages for configurations */
	public $string = "";     /**< \brief String type of parameter which carries the configurations */
	private $sInputAvailable = false;     /**< \brief Indicator to indicate string input is already available */
	private $fInput = false;     /**< \brief Indicator to indicate up-comming inputs are file type */
	private $sInput = true;     /**< \brief Indicator to indicate up-coming input is string type */

	/**
	 * Constructor of the class
	 * 
	 * @param arguments    Arguments passed with the application
	 */
	public function __construct($arguments)
	{
		for($index=1; $index < count($arguments); $index++)
		{
			$argument= $arguments[$index];
			switch($argument)
			{
				case '-d':
				case '--displayerrors':
					$this->displayErrors= true;
					break;
			
				case '-f':
				case '--files':
					if($this->sInputAvailable)
					{
						print("No inputs as file expected at command line after string input!" . PHP_EOL);
					}
					else
					{
						$this->fInput= true;
						$this->sInput= false;
					}
					break;
			
				default:
					$this->updateInputs($argument);
					break;
			}
		}
	}

	/**
	 * Function to update the inputs
	 * 
	 * @param argument    Argument to be updated
	 */
	private function updateInputs($argument)
	{
		if($this->fInput)
		{
			$this->files[]= $argument;
		}
		else if($this->sInput) 
		{
			if($this->sInputAvailable)
			{
				print("No inputs as file is expected at command line after string input!" . PHP_EOL);
			}
			else
			{
				$this->string= $argument;
				$this->sInputAvailable= true;
			}
		}
		else 
		{
			print("Unknown Parameter from commandline : " . $argument . PHP_EOL);
		}
	}

}

/**
 * Main class for the application to generate build make related files.
 * Call the following line manually after the file is generated:
 * $main= new Main($argv);
 * @created 21-Jul-2017 15:44:03
 */
class Main
{

	private $project;     /**< \brief Project object */
	private $cli;     /**< \brief Command line input object */
	public $subDirMakeFiles = Array();     /**< \brief Array of make file objects */
	public $projectMakeFile;     /**< \brief Make file object for the project */
	public $projectData;     /**< \brief Make file object for the variable defines */
	public $makeFiles;

	/**
	 * Constructor of the class
	 * 
	 * @param arguments    Arguments passed with the application
	 */
	public function __construct($arguments)
	{
		$this->cli= new CommandLineInput($arguments);
	
		if($this->cli->string !== "")
		{
			$this->project= new Project($this->cli->string);
		}
		else
		{
			$this->project= new Project($this->cli->files);
		}
	
		$this->updateMakeFiles();
		$this->generateFiles();
	}

	/**
	 * Generate the make files
	 */
	public function generateFiles()
	{
		$errorReport= $this->project->getErrorReport();
		if($errorReport->getErrorExists()===false)
		{
			foreach($this->subFolderMakeFiles as $subFolderMakeFile)
			{
				if($subFolderMakeFile->isMakeFileRequired()) $subFolderMakeFile->generate();
			}
		
			$this->projectMakeFile->generate();
			$this->projectData->generateFiles();
			$this->generateMakeGenDependencyFile();
		}
	}

	/**
	 * Instantiate Make files
	 */
	private function updateMakeFiles()
	{
		/* Instanciate the project data object */
		$this->projectData= new ProjectData($this->project);
	
		$rootSrcFolderMakeFiles= Array(); // instanciate an array to register the make files for root source folders
	
		/* get project configuration */
		$projectConfiguration= $this->project->getConfiguration();
	
		/* Instanciate and list the make files for sub folders */
	
		foreach($this->project->getSourceFolders() as $folder)
		{
			$makeFile= new SubFolderMakeFile($folder, $this->projectData);
			$this->subFolderMakeFiles[$makeFile->getPathName()]= $makeFile;
		
			/* List the make file, if the folder path is one of the root source folders */
			if(in_array($folder->getPathName(), $projectConfiguration->sourceFolders))
			{
				$rootSrcFolderMakeFiles[]= $makeFile; // register this make file
			}
		}
	
		/* Each sub folder make file shall update its sub folder path name list */
		foreach($this->subFolderMakeFiles as $makeFile)
		{
			$makeFile->updateParentTree($this->subFolderMakeFiles);
		}
	
		/* Instanciate the project make file */
		$this->projectMakeFile= new ProjectMakeFile($this->project, $this->projectData);
	
		/* update sub folder make path names, as already registered */ 
		foreach($rootSrcFolderMakeFiles as $rootSrcFolderMakeFile)
		{
			if($rootSrcFolderMakeFile->isMakeFileRequired())
			{
				$this->projectMakeFile->subFolderMakePathNames[]= $rootSrcFolderMakeFile->getPathName();
			}
		}
	}

	/**
	 * Generates the defines make file
	 */
	private function generateMakeGenDependencyFile()
	{
		/* Get project make file path name */
		$projectMakePathName= $this->projectMakeFile->getPathName();
	
		/* Get all subfolder paths */
		$sourceFolderPaths= array_keys($this->project->getSourceFolders());
	
		/* Create the file string with -I in the begining of each path */
		$fileString= $projectMakePathName . ": \\" . PHP_EOL;
	
		$fileString= $fileString . " " . implode(" \\" . PHP_EOL . " ", $sourceFolderPaths) . PHP_EOL;
	
		$fileString= $fileString . PHP_EOL . PHP_EOL . implode(":" . PHP_EOL . PHP_EOL, $sourceFolderPaths) . ":" . PHP_EOL;
	
		$filePathName= CFG::TOOLENV_FOLDERNAME . "/" .
						CFG::BUILD_FOLDERNAME . "/" .
						CFG::BUILD_MAKE_FOLDERNAME . "/" .
						CFG::PROJECT_DEPMAKE_FILENAME;
									  
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
?>