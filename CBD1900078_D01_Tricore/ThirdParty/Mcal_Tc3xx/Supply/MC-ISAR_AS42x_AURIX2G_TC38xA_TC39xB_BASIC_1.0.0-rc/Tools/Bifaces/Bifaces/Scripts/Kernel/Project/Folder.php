<?php
/**----------------------------------------------------------------------------
 * \file Folder.php
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


require_once ('File.php');
require_once ('/../Configuration/Configuration.php');

use Kernel\Project\File;
use Kernel\Configuration\Configuration;
use Kernel\Configuration\CFG;

/**
 * Class to hold the folder related information with BIFACES project.
 * @created 21-Jul-2017 15:44:04
 */
class Folder
{

	private $pathName;     /**< \brief Folder path name */
	private $files = Array();     /**< \brief List of file objects, which are directly under this folder */
	private $cFilePathNames = Array();     /**< \brief List of used C source file path names, which are directly under this folder */
	private $asmFilePathNames = Array();     /**< \brief List of used assembly source file path names, which are directly under this folder */
	private $cHeaderFilePathNames = Array();     /**< \brief List of used C header file path names, which are directly under this folder */
	private $asmHeaderFilePathNames = Array();     /**< \brief List of used assembly header file path names, which are directly under this folder */
	private $makeFilePathNames = Array();     /**< \brief List of user created make file path names under this folder, which are to be included to build */
	private $objectFilePathNames = Array();     /**< \brief List of used pre-built object/library file path names, which are directly under this folder */
	private $configuration;     /**< \brief Project configuration object, to update folder internals */
	private $subFolderPathNames = Array();     /**< \brief Path name of the sub folders, which are used for the project */

	/**
	 * Constructor of folder object
	 * 
	 * @param folderPathName    Path name of the folder (relative or absolute)
	 * @param configuration    Project configurations information as an instance of
	 * Configuration object
	 */
	public function __construct($folderPathName, $configuration)
	{
		//Project configuration provide the information to evaluate the folder validity
		//and store relevant information.
		//From the "select configuration" extract the USE and DISCARD selectors, which
		//are for whole project.
		//The selectors without any targets areapplicabel to whole project. This is used
		//to get the valid pattern.

		$this->pathName= $folderPathName;
		$this->configuration= $configuration;
		//$this->updateFiles();
	}

	/**
	 * Organize the folder to accommodate all latest information gathered.
	 */
	public function classifyFiles()
	{
		$filePathNames= array_keys($this->files);
	
		/* The valid file names for C sources are updated */
		$this->cFilePathNames= $this->filterFiles($filePathNames, explode(',', CFG::C_FILE_EXTENSIONS));
	
		/* The valid file names for asm sources are updated */
		$this->asmFilePathNames= $this->filterFiles($filePathNames, explode(',', CFG::ASM_FILE_EXTENSIONS));
	
		/* The valid file names for pre developed make files are updated */
		$this->makeFilePathNames= $this->filterFiles($filePathNames, explode(',', CFG::MAKE_FILE_EXTENSIONS));
	
		/* The valid file names for C headers are updated */
		$this->cHeaderFilePathNames= $this->filterFiles($filePathNames, explode(',', CFG::CHEADER_FILE_EXTENSIONS));	
	
		/* The valid file names for asm headers are updated */
		$this->asmHeaderFilePathNames= $this->filterFiles($filePathNames, explode(',', CFG::ASMHEADER_FILE_EXTENSIONS));
	
		/* The valid file names for object files are updated */
		$this->objectFilePathNames= $this->filterFiles($filePathNames, explode(',', CFG::OBJECT_FILE_EXTENSIONS));
	}

	/**
	 * Filter the files names of required type. File names' list is passed as
	 * parameter.
	 * Instantiate the file objects for each of them and return if found to be valid.
	 * 
	 * @param filePathNames    Array of file path nams to be filtered.
	 * @param fileTypes    Array of file types to filter the files list.
	 * @param filteredList    Filtered list of files
	 */
	private function filterFiles($filePathNames, $fileTypes)
	{
		/* Step 1: Prepare the reg-ex pattern*/
		$fileTypes=array_map('trim', $fileTypes);
		$regexPattern="#^.*\." . "(?:" . implode("|", $fileTypes) . ")$#i";
	
		/* Step 2: Filter the matching file patterns*/
		$retFileList= preg_grep($regexPattern, $filePathNames);
	
		/* Step 3: Return the list */
		return $retFileList;
	}

	/**
	 * Update the sub folders path names array with sub folder path name
	 * 
	 * @param subFolderPathNames    Return array of sub folder path names
	 */
	public function getSubFolderPathNames()
	{
		return $this->subFolderPathNames;
	}

	/**
	 * 
	 * @param folderList    List of folders to search
	 */
	public function updateSubFolderNames($folderList)
	{
		/* Create pattern to select list of sub folders */
		$regexPattern="#^" . $this->pathName . "/.+$#";
	
		//$this->subFolderPathNames= array_filter(preg_grep($regexPattern, $folderList),
		//			function($value) {return dirname($value) === $this->pathName;});
		foreach(preg_grep($regexPattern, $folderList) as $folderPathName)
		{
			if(dirname($folderPathName) === $this->pathName) $this->subFolderPathNames[]= $folderPathName;
		}
	}

	/**
	 * Add file to the folder
	 * 
	 * @param file    File object to be added
	 */
	public function addFile($file)
	{
		$this->files[$file->pathName]= $file;
	}

	/**
	 * Gets the path name
	 * 
	 * @param pathName    Folder path name
	 */
	public function getPathName()
	{
		return $this->pathName;
	}

	/**
	 * Gets the C and ASM source file path names (but not header file sources)
	 * 
	 * @param sourceFilePathNames    Array of C and ASM source file path names
	 */
	public function getSourceFilePathNames()
	{
		return array_merge($this->cFilePathNames, $this->asmFilePathNames);
	}

	/**
	 * Gets the C and ASM header file path names (but not actual source files)
	 * 
	 * @param headerFilePathNames    Array of C and ASM header file path names
	 */
	public function getHeaderFilePathNames()
	{
		return array_merge($this->cHeaderFilePathNames, $this->asmHeaderFilePathNames);
	}

	/**
	 * Gets the make file path names
	 * 
	 * @param makeFilePathNames    Array of make file path names
	 */
	public function getMakeFilePathNames()
	{
		return $this->makeFilePathNames;
	}

	/**
	 * Gets the object file path names
	 * 
	 * @param objectFilePathNames    Array of object file path names
	 */
	public function getObjectFilePathNames()
	{
		return $this->objectFilePathNames;
	}

	/**
	 * Gets the C source file path names (but not header file sources)
	 * 
	 * @param cFilePathNames    Array of C source file path names
	 */
	public function getCFilePathNames()
	{
		return $this->cFilePathNames;
	}

	/**
	 * Gets the file object
	 * 
	 * @param filePathName    Path name of the file for which file object is requested
	 * @param file    File object
	 */
	public function getFile($filePathName)
	{
		return $this->files[$filePathName];
	}

	/**
	 * Gets the file object
	 * 
	 * @param filePathNames    List of file path names
	 */
	public function getFilePathNames()
	{
		return array_keys($this->files);
	}

}
?>