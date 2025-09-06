<?php
/**----------------------------------------------------------------------------
 * \file ErrorReporting.php
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
 
namespace Kernel\ErrorReporting;




use Kernel\ErrorReporting\ERR;
use Kernel\ErrorReporting\Error;

/**
 * Class to contain the error constants
 * @created 21-Jul-2017 15:44:04
 */
class ERR
{

	const TI = 'INFO   ';     /**< \brief Information Type */
	const TW = 'WARNING';     /**< \brief Warning Type */
	const TE = 'ERROR  ';     /**< \brief Error Type */
	const ID_W_CONFIG_UNKNOWN_PARAM = 300;     /**< \brief Error for unknown configuration element */
	const ID_W_CONFIG_MISSING_FOLDER = 301;     /**< \brief Error for missing parameter with one of the configurations */
	const ID_W_CONFIG_MISSING_CFGITEM = 302;     /**< \brief Error for missing configuration item which is expected by one or more other configurations */
	const ID_E_CONFIG_MISSING_NAME = 500;     /**< \brief Error for missing name with one of the configurations */
	const ID_E_CONFIG_MISSING_PARAM = 501;     /**< \brief Error for missing parameter with one of the configurations */
	const ID_E_CONFIG_WRONG_PARAM = 502;     /**< \brief Error for missing parameter with one of the configurations */
	const ID_E_CONFIG_MISSING_CFGVAL = 503;     /**< \brief Error for missing configuration value which could have been referenced but no found in any config values of any cfg items. */

}

/**
 * Class to contain the error reporting information
 * @created 21-Jul-2017 15:44:04
 */
class ErrorReport
{

	private $records = Array();     /**< \brief Array of error information */
	private $errorExists = false;     /**< \brief Information if there is some error */
	private $displayInfos;     /**< \brief Enable/disable infos' display */
	private $displayWarnings;     /**< \brief Enable/disable warnings' display */
	private $displayErrors;     /**< \brief Enable/disable errors' display */

	/**
	 * Constructor of the class
	 * 
	 * @param displayErrors    Display Errors
	 * @param displayWarnings    Display warnings
	 * @param displayInfos    Enable Display for informations
	 */
	public function __construct($displayErrors = true, $displayWarnings = true, $displayInfos = true)
	{
		$this->displayInfos=$displayInfos;
		$this->displayWarnings=$displayWarnings;
		$this->displayErrors=$displayErrors;
	}

	/**
	 * Register new error
	 * 
	 * @param error    new error to be registered
	 */
	public function register($error)
	{
		$this->records[]=$error;
		if(($this->displayInfos) && ($error->getType()===ERR::TI))
		{
			print($error->getMessage());
		}
	
		if(($this->displayWarnings) && ($error->getType()===ERR::TW))
		{
			print($error->getMessage());
		}
	
		if(($this->displayErrors) && ($error->getType()===ERR::TE))
		{
			$this->errorExists= true;
			print($error->getMessage());
		}
	}

	/**
	 * Returns if there are some errors in the report
	 * 
	 * @param errorsExist    Return information if there is atleast one error in the
	 * error report
	 */
	public function getErrorExists()
	{
		return $this->errorExists;
	}

}

/**
 * Class to contain the error information
 * @created 21-Jul-2017 15:44:04
 */
class Error
{

	private $type;     /**< \brief Type of the error, allowed values 'INFO', 'WARNING', 'ERROR' */
	private $id;     /**< \brief Identifier */
	private $text;     /**< \brief Error text */

	/**
	 * Constructor of the class
	 * 
	 * @param type    Type of the error, allowed values 'INFO', 'WARNING', 'ERROR'
	 * @param id    Error identifier
	 * @param text    Error text
	 */
	public function __construct($type = 'ERROR', $id, $text = "")
	{
		$this->type= $type;
		$this->id= $id;
		$this->text=$text;
	}

	/**
	 * Get the error message string.
	 * 
	 * @param message    Return error message
	 */
	public function getMessage()
	{
		$message= $this->type . ": " . $this->id . ": " . $this->text . PHP_EOL;
		return $message;
	}

	/**
	 * Get the error type
	 * 
	 * @param type    Type of the error to return
	 */
	public function getType()
	{
		return $this->type;
	}

}
?>