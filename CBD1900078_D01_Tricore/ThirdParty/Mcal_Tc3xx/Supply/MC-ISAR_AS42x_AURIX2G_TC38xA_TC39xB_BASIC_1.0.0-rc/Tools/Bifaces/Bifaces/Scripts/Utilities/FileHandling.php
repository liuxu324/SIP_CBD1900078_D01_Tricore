<?php
/**----------------------------------------------------------------------------
 * \file FileHandling.php
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
 
namespace Utilities\FileHandling;




/**
 * Class to for file generation operation
 * @created 21-Jul-2017 15:44:04
 */
class FileGenHandle
{

	private $outfileHandle;     /**< \brief File IO handler to write to output file */
	private $outFile;     /**< \brief File path name of the output file to be created */
	private $templateFile;     /**< \brief Template file to be used to create the output file */
	public $infoSourceObject;     /**< \brief Object to be used inside the template file to access the data */

	/**
	 * Constructor of the FileGenHandle
	 * 
	 * @param infoObject    The object to be passed to the template
	 * @param templateFilePathName    Path and File Name of the template file
	 * @param outputFilePathName    Path and file name of the file to be generated
	 */
	public function __construct($infoObject, $templateFilePathName, $outputFilePathName)
	{
		//Assign the outputFilePathName to outFile
		$this->outFile= $outputFilePathName;
	
		//Assign the templateFilePathName to templateFile
		$this->templateFile= $templateFilePathName;
	
		//Assign the infoObject to infoSourceObject
		$this->infoSourceObject= $infoObject;
	}

	/**
	 * Call back function to get the output buffer back.
	 * This Api is called once file output string is ready to be written. This is
	 * specific to the PHP, that the call back function (ob_start configured) is
	 * automatically triggered when ob_end_flush is done.
	 * 
	 * @param string    file output string, buffer from ob functionality of PHP
	 */
	private function outputCallBack($string)
	{
		// Write the content of the string to the file buffer pointed by outfileHandle
		fwrite($this->outfileHandle,$string);
	}

	/**
	 * Create the directory for the file to be created by this class
	 * This Api checks if the folder path for the file already exists and if not,
	 * creates it. This Api is called internally while creating the file.
	 */
	private function makeDirectory()
	{
		//Get the dir part of the file path name
		$tempFolderPath= str_replace("/", DIRECTORY_SEPARATOR, pathinfo ( $this->outFile, PATHINFO_DIRNAME));
		//Check if folder exists
		if(!file_exists($tempFolderPath))
		{
			//if not, create it
			mkdir($tempFolderPath, 0777, true);	// the number 0777 provides access "Everything" to "All users" and true for recursive mkdir
		}
	}

	/**
	 * Create the file from the template.
	 * This Api takes the template file as input and creates the output file.
	 */
	public function createFile()
	{
		// Following operations are specific to PHP
	
		// Open a file handle with the output file path name
		$this->makeDirectory();
		$this->outfileHandle = fopen($this->outFile, "w");
	
		// If successful, start the out buffer handling process
		ob_start(array($this,"outputCallBack"));
	
		// Include the template file
		require($this->templateFile);
	
		// Stop out buffering process and flush out the buffer
		ob_end_flush();
	
		// close the file handle opened for writing
		fclose($this->outfileHandle);
	}

}

/**
 * This class handles the file / folder name patterns
 * @created 21-Jul-2017 15:44:04
 */
class FileNamePattern
{

	const FILTER_IN = true;     /**< \brief Constant to define filter type as "filter in" matching patterns */
	const FILTER_OUT = false;     /**< \brief Constant to define filter type as "filter out" matching patterns */
	private $regExPatterns = Array();     /**< \brief Array of file patterns as Regular Expression */

	/**
	 * Convert the file pattern represented in wild card file pattern to Regular
	 * Expression format
	 * 
	 * @param patterns    Wildcard file patterns which need to be used for file
	 * pattern handling
	 */
	public function __construct($patterns)
	{
		$tempPatterns=array();
	
		/* Check if the passed paramter is an array, if not convert it */
		$tempPatterns=is_array($patterns)? $patterns : array($patterns);
	
		/* Convert each of the wild card pattern to regex pattern */
		foreach($tempPatterns as $pattern)
		{
			$this->regExPatterns[]= $this->convertFilePatternToRegEx(trim($pattern));
		}
	}

	/**
	 * Convert the file pattern represented in wild card file pattern to Regular
	 * Expression format
	 * 
	 * @param pattern    Wildcard file pattern which need to be converted
	 */
	private function convertFilePatternToRegEx($pattern)
	{
		if((substr($pattern, 0, 2) !== "#^") || (substr($pattern, -2, 2) !== "$#"))
		{
			/* Convert file filter pattern to reg ex */
			$pattern=str_replace("\\","/",$pattern);	//back slash to forward slash with escape char
			$pattern=str_replace(".","\\.",$pattern);	//replace the . for file extension to \.
			$pattern=str_replace("?",".",$pattern);		//replace the ? for wild char to .
			$pattern=str_replace("(.:","(?:",$pattern);	//replace the (.: back to (?: as ? was replaced earlier
			$pattern=str_replace("*",".*",$pattern);	//replace the * for multiple char to \.
			$pattern="#^" . $pattern . "$#";     		//use # as delimiter because # cannot be in file name
		}
		return $pattern;
	}

	/**
	 * Function to filter the files with path names based on the patterns specified in
	 * regex
	 * 
	 * @param filterType    filterType filter type: FILTER_IN= The result of filter
	 * will extract the files which match the pattern, FILTER_OUT= filters out the
	 * matching files
	 * @param filePaths    File path name or names (as array)
	 */
	public function filterFilePathPattern($filterType, $filePaths)
	{
		$tempFilePaths=array();
		$retPatternIn= array();
	
		/* Check if the passed paramter is an array, if not convert it */
		$tempFilePaths=is_array($filePaths)? $filePaths : array($filePaths);
	
		/* Check if a matching file path exists for each of the regex pattern */
		foreach($this->regExPatterns as $pattern)
		{
			$retPatternIn=array_merge($retPatternIn, preg_grep($pattern, $tempFilePaths));	// checks if there are a matching file paths and return them
		}
	
		/* return the array depending on the type of filtering, to include or exclude */
		return $filterType==self::FILTER_IN? $retPatternIn : array_diff($tempFilePaths,$retPatternIn);
	}

}
?>