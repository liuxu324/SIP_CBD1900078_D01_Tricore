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
 
namespace Doxygen;


require_once ('/../Kernel/Project/Project.php');
require_once ('/../Kernel/Configuration/Configuration.php');
require_once ('/../Utilities/FileHandling.php');
require_once ('/../MakeGen/MakeGen.php');

use Doxygen\DOC;
use Doxygen\DoxygenFile;
use Kernel\Project\Project;
use Kernel\Configuration\CFG;
use Utilities\FileHandling\FileGenHandle;
use Utilities\FileHandling\FileNamePattern;
use MakeGen\CommandLineInput;

/**
 * Doxygen constants
 * @created 21-Jul-2017 15:44:04
 */
class DOC
{

	const DOC_FOLDERNAME = '3_Doc';     /**< \brief Documentation folder */
	const DOXYGEN_FOLDERNAME = 'Doxygen';     /**< \brief Doxygen folder */
	const DOXYGEN_OUT_FOLDERNAME = 'Out';     /**< \brief Doxygen out folder */
	const DOXYGEN_LOG_FOLDERNAME = 'Log';     /**< \brief Doxygen log folder */
	const DOXYGEN_USER_FOLDERNAME = '_UserFiles';     /**< \brief Doxygen log folder */
	const DOXYGEN_RULESFILE_BASENAME = 'DoxygenRules';     /**< \brief Base name for doxygen rules file name */
	const DOXYGEN_DEP_FILENAME = 'DoxygenDep.mk';     /**< \brief Doxygen dependency file name */
	const DOXYGEN_MAKE_FILENAME = 'Doxygen.mk';     /**< \brief Doxygen dependency file name */
	const DOXYGEN_HTMLFOOTER_FILENAME = 'Footer.html';     /**< \brief Doxygen footer file name */

}

/**
 * 
 * @created 21-Jul-2017 15:44:04
 */
class DoxygenFile
{

	public $rulesFilePath;     /**< \brief Path for generated rules file  */
	private $project;     /**< \brief Project object */
	private $sourceFiles = array();     /**< \brief Array of source files per target */
	public $inputs = array();     /**< \brief Array of input files used during file generation */
	public $stripPath;     /**< \brief Strip path which will be stripped off with file names with in the generated docs */
	public $toolPath;     /**< \brief Doxygen tool path */
	public $imageIncludePaths;     /**< \brief Include paths for images as space delimited string */
	public $projectName;     /**< \brief Project name */
	public $docTemplatesPath;     /**< \brief Doc template path */
	public $hhcToolPath;     /**< \brief HTML Help Compiler tool path */
	public $dotToolPath;     /**< \brief Dot tool path */
	public $makeTemplateFilePathName;     /**< \brief Path name of template file */
	public $ruleTemplateFilePathName;     /**< \brief Path name of template file */
	public $footerTemplateFilePathName;     /**< \brief Path name of footer template file */
	public $targetFullNames = array();     /**< \brief List of target full names */
	public $keepHtml;     /**< \brief Boolean to store enable HTML retention or not */
	public $docOutPath;     /**< \brief Output folder path for the documents */
	public $docName;     /**< \brief Document name */
	public $logisticData;     /**< \brief Document Logistic data */

	/**
	 * Constructor of the class
	 * 
	 * @param project    Project object
	 */
	public function __construct($project)
	{
		$this->project= $project;
	
		/* Get information related to the configuration items */
		$projectConfiguration= $project->getConfiguration();
		$doxygenCfg= $projectConfiguration->doxygen;
	
		$this->keepHtml= $doxygenCfg->getKeepHtmlInfo();
	
		$this->targetFullNames= $doxygenCfg->getTargetFullNames();
		$this->updateSourceFilePathNames($this->targetFullNames, $doxygenCfg->getExcludePatterns()); // Updates the variable sourceFiles per target.
	
		$this->docOutPath= DOC::DOC_FOLDERNAME . "/" . DOC::DOXYGEN_FOLDERNAME . "/" . DOC::DOXYGEN_OUT_FOLDERNAME;
	
		$this->stripPath= str_replace("\\", "/", getcwd()); // get the current working dir which is project root
		$this->projectName= basename($this->stripPath);
	
		$imageIncPaths= $doxygenCfg->getImagesPaths();
		$imageIncPaths[]= $doxygenCfg->getTemplatesPath();
		$this->imageIncludePaths= implode(" \\" . PHP_EOL . "                         ", $imageIncPaths);
	
		$this->docTemplatesPath= $doxygenCfg->getTemplatesPath();
	
		$this->toolPath= $doxygenCfg->getToolPath();
		$this->hhcToolPath= $doxygenCfg->getHhcToolPath();
		$this->dotToolPath= $doxygenCfg->getDotToolPath();
	
		$this->logisticData= $doxygenCfg->getLogisticData();
	
		$this->rulesFilePath= DOC::DOC_FOLDERNAME . "/" . DOC::DOXYGEN_FOLDERNAME . "/" . DOC::DOXYGEN_LOG_FOLDERNAME;
	
		$this->ruleTemplateFilePathName= $this->docTemplatesPath . "/" . DOC::DOXYGEN_RULESFILE_BASENAME . ".php";
	
		$templateFileName= str_replace(".", "_", DOC::DOXYGEN_MAKE_FILENAME) . ".php";
		$this->makeTemplateFilePathName= $this->docTemplatesPath . "/" . $templateFileName;
	
		$templateFileName= str_replace(".", "_", DOC::DOXYGEN_HTMLFOOTER_FILENAME) . ".php";
		$this->footerTemplateFilePathName= $this->docTemplatesPath . "/" . $templateFileName;
	}

	/**
	 * Generates files related to doxygen
	 */
	public function generateFiles()
	{
		if(count($this->targetFullNames) > 0)
		{
			foreach($this->targetFullNames as $targetFullName)
			{
				/* generate file for each target */
				$suffix= str_replace(CFG::FULLNAME_DELIMITER, "", $targetFullName);
				$rulesFilePathName= $this->rulesFilePath . "/" . DOC::DOXYGEN_RULESFILE_BASENAME . $suffix . ".txt";
				$docName= $this->projectName . "." . str_replace(CFG::FULLNAME_DELIMITER, ".", $targetFullName);
				$this->generateRulesFile($rulesFilePathName, $docName, $this->sourceFiles[$targetFullName]);
			}
		}
		else
		{
			/* One document for all the sources  */
			$rulesFilePathName= $this->rulesFilePath . "/" . DOC::DOXYGEN_RULESFILE_BASENAME . ".txt";
			$this->generateRulesFile($rulesFilePathName, $this->projectName, $this->sourceFiles);
		}
	
		/* Now generate the make file */
		// print("Doxygen Make file "); // TODO Instrumentation code
		$fileGen= new FileGenHandle($this, $this->makeTemplateFilePathName, $this->rulesFilePath . "/" . DOC::DOXYGEN_MAKE_FILENAME);
		$fileGen->CreateFile();
		// print(" generated!" . PHP_EOL); // TODO Instrumentation code
	
		/* Now generate the footer file */
		// print("Doxygen Make file "); // TODO Instrumentation code
		$fileGen= new FileGenHandle($this, $this->footerTemplateFilePathName, $this->rulesFilePath . "/" . DOC::DOXYGEN_HTMLFOOTER_FILENAME);
		$fileGen->CreateFile();
		// print(" generated!" . PHP_EOL); // TODO Instrumentation code
	}

	/**
	 * 
	 * @param filePathName    Name of the rule file
	 * @param docName    Name of the document
	 * @param inputFiles    Input files
	 */
	private function generateRulesFile($filePathName, $docName, $inputFiles)
	{
		/* Update the inputs for the target */
		$this->inputs= implode(" \\" . PHP_EOL . "                         ", $inputFiles);
		$this->docName= $docName;
	
		// print("Doxygen Rule file for : " . $filePathName); // TODO Instrumentation code
		$fileGen= new FileGenHandle($this, $this->ruleTemplateFilePathName, $filePathName);
		$fileGen->CreateFile();
		// print(" generated!" . PHP_EOL); // TODO Instrumentation code
	
	}

	/**
	 * Updates the source files
	 * 
	 * @param targetFullNames    Array of targets full names
	 * @param excludePatterns    Patterns (folder/file) to exclude from documentation
	 */
	public function updateSourceFilePathNames($targetFullNames, $excludePatterns)
	{
		$sourceFiles= array();
	
		/* Filter at the source folder level */
		$sourceFolders= $this->project->getSourceFolders();
		$sourceFolderPathNames= array_keys($sourceFolders);
	
		if(count($excludePatterns))
		{
			/* Filter the files "OUT", which match the exclude file pattern */
			$flePatterns= new FileNamePattern($excludePatterns);
			$sourceFolderPathNames= $flePatterns->filterFilePathPattern(FileNamePattern::FILTER_OUT, $sourceFolderPathNames);
		}
	
		foreach($sourceFolderPathNames as $sourceFolderPathName)
		{
			$sourceFolder= $sourceFolders[$sourceFolderPathName];
			$filePathNames= array_merge($sourceFolder->getCFilePathNames(),
										$sourceFolder->getHeaderFilePathNames());
		
			/* Again filter for the file path names here */
			if(count($excludePatterns))
			{
				/* Filter the files "OUT", which match the exclude file pattern */
				$filePathNames= $flePatterns->filterFilePathPattern(FileNamePattern::FILTER_OUT, $filePathNames);
			}
		
			if(count($targetFullNames) > 0)
			{
				/* Now for each file check which are the targets are associated and create per target an array*/
				foreach($filePathNames as $filePathName)
				{
					$file= $sourceFolder->getFile($filePathName);
					$tmpTargetFullNames= array_intersect($targetFullNames, $file->getTargetFullNames());
				
					/* Now update array for each targets with this file */
					foreach($tmpTargetFullNames as $targetFullName)
					{
						$this->sourceFiles[$targetFullName][]=$filePathName;
					}
				}
			}
			else
			{
				/* No targets configured use all files for single doc */
				$this->sourceFiles= array_Merge($this->sourceFiles, $filePathNames);
			}
		}
	}

}

/**
 * 
 * @created 21-Jul-2017 15:44:04
 */
class DoxygenMain
{

	private $cli;     /**< \brief Command line input object */
	private $project;     /**< \brief Project object */

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
	
		$doxygenFiles= new DoxygenFile($this->project);
		$doxygenFiles->generateFiles();
	}

}
?>