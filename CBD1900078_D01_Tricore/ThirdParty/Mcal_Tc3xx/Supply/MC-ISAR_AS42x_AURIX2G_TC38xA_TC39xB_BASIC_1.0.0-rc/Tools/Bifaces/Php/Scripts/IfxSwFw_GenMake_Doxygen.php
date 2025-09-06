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
 

define('IFX_SWFW_RELEASE_FOLDERNAME',IFX_SWFW_CFG_EXEOUT_FOLDERNAME . '/Release');

$usageHint=
"Uasge: Php.exe IfxSwFw_GenMake_Doxygen.php \"EXTERNAL_SRC_FOLDERS=<Names of external folders separated by comma>;
                                            DOXYGEN_EXCLUDE_CFG=<Doxygen Exclude Files Patterns sepatated by comma>;
                                            DOXYGEN_IMAGE_FILE_PATH=<Folders to search for images separated by comma>;
											DOXYGEN_OUT_PATHNAME=<Path for the doxygen output>;
											DOXYGEN_RULES_FILE_PATHNAME=<File names for the generated rules file>;
                                            DOXYGEN_DOT_TOOL_PATH=<DOT tool path>;
                                            DOXYGEN_HHC_TOOL_PATHNAME=<MS Help compiler path>\"" . PHP_EOL;
switch(count($argv))
{
	case 1:
	default:
	{
		print("Wrong number of arguments!\n".$usageHint);
		break;
	}
	case 2:
	{
		// Main call
		mainCall($argv[1]);
		
		break;
	}
}

class DoxygenConfig
{
	public $inputFilePaths="";
	public $outputFolderPath;
	public $stripPath;
	public $excludePatterns="";
	public $imageIncludePaths="";
	public $projectName="";
	public $rulesFileName="";
	public $chmFileName="";
	public $hhcToolPathName="";
	public $dotToolPath="";

	public function __construct()
	{
		//Get the project name
		$tempPathInfo= pathinfo(getcwd());
		$this->projectName= $tempPathInfo['basename'];
		//$this->stripPath= str_replace("\\", "/", getcwd());
		$this->stripPath=&$this->inputFilePaths;
		$this->chmFileName= $this->projectName . ".chm";
	}
	
	public function createRulesFile()
	{
		$dirPath= str_replace("/", DIRECTORY_SEPARATOR, pathinfo($this->rulesFileName, PATHINFO_DIRNAME));
		//Check if folder exists
		if(!file_exists($dirPath))
		{
			//if not, create it
			mkdir($dirPath, 0777, true);	// the number 0777 provides access "Everything" to "All users" and true for recursive mkdir
		}
		$outfileHandle = fopen($this->rulesFileName, "w");
		fwrite($outfileHandle, $this->getDoxygenConfigText());
		fclose($outfileHandle);
	}
	
	public function getDoxygenConfigText()
{
	$doxyConfigText=
"INPUT                  =  " . $this->inputFilePaths . " 
INCLUDE_PATH           = 
OUTPUT_DIRECTORY       = " . $this->outputFolderPath . "
FULL_PATH_NAMES        = YES
STRIP_FROM_PATH        = " . $this->stripPath . "
STRIP_FROM_INC_PATH    = " . $this->stripPath . "
INPUT_ENCODING         = UTF-8
FILE_PATTERNS          = *.c \\
                         *.h
RECURSIVE              = YES
EXCLUDE                = 
EXCLUDE_SYMLINKS       = NO
EXCLUDE_PATTERNS       = " . $this->excludePatterns . "
EXCLUDE_SYMBOLS        = 
EXAMPLE_PATH           = 
EXAMPLE_PATTERNS       = *
EXAMPLE_RECURSIVE      = NO
IMAGE_PATH             = " . $this->imageIncludePaths . "
INPUT_FILTER           = 
FILTER_PATTERNS        = 
FILTER_SOURCE_FILES    = NO
DOXYFILE_ENCODING      = UTF-8
PROJECT_NAME           = " . $this->projectName . "
PROJECT_NUMBER         = 
CREATE_SUBDIRS         = NO
OUTPUT_LANGUAGE        = English
BRIEF_MEMBER_DESC      = YES
REPEAT_BRIEF           = YES
ABBREVIATE_BRIEF       = \"The \$name class\" \\
                         \"The \$name widget\" \\
                         \"The \$name file\" \\
                         is \\
                         provides \\
                         specifies \\
                         contains \\
                         represents \\
                         a \\
                         an \\
                         the
ALWAYS_DETAILED_SEC    = NO
INLINE_INHERITED_MEMB  = NO
SHORT_NAMES            = NO
JAVADOC_AUTOBRIEF      = NO
QT_AUTOBRIEF           = NO
MULTILINE_CPP_IS_BRIEF = NO
INHERIT_DOCS           = YES
SEPARATE_MEMBER_PAGES  = NO
TAB_SIZE               = 8
ALIASES                = 
OPTIMIZE_OUTPUT_FOR_C  = YES
OPTIMIZE_OUTPUT_JAVA   = NO
OPTIMIZE_FOR_FORTRAN   = NO
OPTIMIZE_OUTPUT_VHDL   = NO
EXTENSION_MAPPING      = 
BUILTIN_STL_SUPPORT    = NO
CPP_CLI_SUPPORT        = NO
SIP_SUPPORT            = NO
IDL_PROPERTY_SUPPORT   = YES
DISTRIBUTE_GROUP_DOC   = NO
SUBGROUPING            = YES
TYPEDEF_HIDES_STRUCT   = NO
SYMBOL_CACHE_SIZE      = 0
EXTRACT_ALL            = NO
EXTRACT_PRIVATE        = NO
EXTRACT_STATIC         = NO
EXTRACT_LOCAL_CLASSES  = YES
EXTRACT_LOCAL_METHODS  = NO
EXTRACT_ANON_NSPACES   = NO
HIDE_UNDOC_MEMBERS     = NO
HIDE_UNDOC_CLASSES     = NO
HIDE_FRIEND_COMPOUNDS  = NO
HIDE_IN_BODY_DOCS      = NO
INTERNAL_DOCS          = NO
CASE_SENSE_NAMES       = NO
HIDE_SCOPE_NAMES       = YES
SHOW_INCLUDE_FILES     = YES
INLINE_INFO            = YES
SORT_MEMBER_DOCS       = YES
SORT_BRIEF_DOCS        = NO
SORT_GROUP_NAMES       = NO
SORT_BY_SCOPE_NAME     = NO
GENERATE_TODOLIST      = YES
GENERATE_TESTLIST      = YES
GENERATE_BUGLIST       = YES
GENERATE_DEPRECATEDLIST= YES
ENABLED_SECTIONS       = 
MAX_INITIALIZER_LINES  = 30
SHOW_DIRECTORIES       = NO
SHOW_FILES             = YES
SHOW_NAMESPACES        = YES
FILE_VERSION_FILTER    = 
LAYOUT_FILE            = 
QUIET                  = NO
WARNINGS               = YES
WARN_IF_UNDOCUMENTED   = YES
WARN_IF_DOC_ERROR      = YES
WARN_NO_PARAMDOC       = NO
WARN_FORMAT            = \"\$file:\$line: \$text\"
WARN_LOGFILE           = 
SOURCE_BROWSER         = YES
INLINE_SOURCES         = NO
STRIP_CODE_COMMENTS    = YES
REFERENCED_BY_RELATION = NO
REFERENCES_RELATION    = NO
REFERENCES_LINK_SOURCE = YES
USE_HTAGS              = NO
VERBATIM_HEADERS       = YES
ALPHABETICAL_INDEX     = NO
COLS_IN_ALPHA_INDEX    = 5
IGNORE_PREFIX          = 
GENERATE_HTML          = YES
HTML_OUTPUT            = html
HTML_FILE_EXTENSION    = .html
HTML_HEADER            = 
HTML_FOOTER            = 
HTML_STYLESHEET        = 
HTML_ALIGN_MEMBERS     = YES
HTML_DYNAMIC_SECTIONS  = NO
GENERATE_DOCSET        = NO
DOCSET_FEEDNAME        = \"Doxygen generated docs\"
DOCSET_BUNDLE_ID       = org.doxygen.Project
GENERATE_HTMLHELP      = YES
CHM_FILE               = " . $this->chmFileName . "
HHC_LOCATION           = \"" . $this->hhcToolPathName . "\"
GENERATE_CHI           = NO
CHM_INDEX_ENCODING     = 
BINARY_TOC             = YES
TOC_EXPAND             = YES
GENERATE_QHP           = NO
QCH_FILE               = 
QHP_NAMESPACE          = 
QHP_VIRTUAL_FOLDER     = doc
QHP_CUST_FILTER_NAME   = 
QHP_CUST_FILTER_ATTRS  = 
QHP_SECT_FILTER_ATTRS  = 
QHG_LOCATION           = 
DISABLE_INDEX          = NO
ENUM_VALUES_PER_LINE   = 4
GENERATE_TREEVIEW      = YES
TREEVIEW_WIDTH         = 250
FORMULA_FONTSIZE       = 10
GENERATE_LATEX         = NO
LATEX_OUTPUT           = latex
LATEX_CMD_NAME         = latex
MAKEINDEX_CMD_NAME     = makeindex
COMPACT_LATEX          = NO
PAPER_TYPE             = a4wide
EXTRA_PACKAGES         = 
LATEX_HEADER           = 
PDF_HYPERLINKS         = YES
USE_PDFLATEX           = YES
LATEX_BATCHMODE        = NO
LATEX_HIDE_INDICES     = NO
LATEX_SOURCE_CODE      = NO
GENERATE_RTF           = NO
RTF_OUTPUT             = rtf
COMPACT_RTF            = NO
RTF_HYPERLINKS         = NO
RTF_STYLESHEET_FILE    = 
RTF_EXTENSIONS_FILE    = 
GENERATE_MAN           = NO
MAN_OUTPUT             = man
MAN_EXTENSION          = .3
MAN_LINKS              = NO
GENERATE_XML           = NO
XML_OUTPUT             = xml
XML_SCHEMA             = 
XML_DTD                = 
XML_PROGRAMLISTING     = YES
GENERATE_AUTOGEN_DEF   = NO
GENERATE_PERLMOD       = NO
PERLMOD_LATEX          = NO
PERLMOD_PRETTY         = YES
PERLMOD_MAKEVAR_PREFIX = 
ENABLE_PREPROCESSING   = YES
MACRO_EXPANSION        = NO
EXPAND_ONLY_PREDEF     = NO
SEARCH_INCLUDES        = YES
INCLUDE_FILE_PATTERNS  = 
PREDEFINED             = 
EXPAND_AS_DEFINED      = 
SKIP_FUNCTION_MACROS   = YES
TAGFILES               = 
GENERATE_TAGFILE       = 
ALLEXTERNALS           = NO
EXTERNAL_GROUPS        = YES
PERL_PATH              = /usr/bin/perl
CLASS_DIAGRAMS         = YES
MSCGEN_PATH            = 
HIDE_UNDOC_RELATIONS   = YES
HAVE_DOT               = YES
DOT_FONTNAME           = FreeSans
DOT_FONTSIZE           = 10
DOT_FONTPATH           = 
CLASS_GRAPH            = YES
COLLABORATION_GRAPH    = YES
GROUP_GRAPHS           = YES
UML_LOOK               = NO
TEMPLATE_RELATIONS     = NO
INCLUDE_GRAPH          = YES
INCLUDED_BY_GRAPH      = YES
CALL_GRAPH             = YES
CALLER_GRAPH           = YES
GRAPHICAL_HIERARCHY    = YES
DIRECTORY_GRAPH        = YES
DOT_IMAGE_FORMAT       = png
DOT_PATH               = \"" . $this->dotToolPath . "\"
DOTFILE_DIRS           = " . $this->outputFolderPath . "
DOT_GRAPH_MAX_NODES    = 50
MAX_DOT_GRAPH_DEPTH    = 0
DOT_TRANSPARENT        = NO
DOT_MULTI_TARGETS      = NO
GENERATE_LEGEND        = YES
DOT_CLEANUP            = YES
SEARCHENGINE           = NO
";
		return $doxyConfigText;
	}
}

function mainCall($param)
{
	$cmdInput= new CommandInput($param);
	$srcFolders=array();
	$excludePaths=array();
	$imageIncludePaths=array();
	
	$doxygenCfg= new DoxygenConfig();
	
	foreach($cmdInput->parameters as $param)
	{
		$tempValues=array();
		switch(trim($param->attribute))
		{
			default:
				break;
			case "EXTERNAL_SRC_FOLDERS":
				foreach(explode(",",$param->value) as $tempValue) if(trim($tempValue)!=="") $tempValues[]= trim($tempValue);
				$doxygenCfg->inputFilePaths= implode(" ", $tempValues);
				break;
			case "DOXYGEN_EXCLUDE_CFG":
				foreach(explode(",",$param->value) as $tempValue) if(trim($tempValue)!=="") $tempValues[]= trim($tempValue);
				$doxygenCfg->excludePatterns= implode(" ", $tempValues);
				break;
			case "DOXYGEN_IMAGE_FILE_PATH":
				foreach(explode(",",$param->value) as $tempValue) if(trim($tempValue)!=="") $tempValues[]= trim($tempValue);
				$doxygenCfg->imageIncludePaths= implode(" ", $tempValues);
				break;
			case "DOXYGEN_OUT_PATHNAME":
				$doxygenCfg->outputFolderPath=$param->value;
				break;
			case "DOXYGEN_RULES_FILE_PATHNAME":
				$doxygenCfg->rulesFileName=$param->value;
				break;
			case "DOXYGEN_DOT_TOOL_PATH":
				$doxygenCfg->dotToolPath=$param->value;
				break;
			case "DOXYGEN_HHC_TOOL_PATHNAME":
				$doxygenCfg->hhcToolPathName=$param->value;
				break;
		}
	}
	
	$doxygenCfg->createRulesFile();
	//print($doxygenCfg->getDoxygenConfigText());
}
?>