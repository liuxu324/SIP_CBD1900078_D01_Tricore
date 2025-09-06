###############################################################################
#                                                                             #
#        Copyright © 2017 Infineon Technologies AG. All rights reserved.      #
#                                                                             #
#                                                                             #
#                              IMPORTANT NOTICE                               #
#                                                                             #
#                                                                             #
# Infineon Technologies AG (Infineon) is supplying this file for use          #
# exclusively with Infineon’s microcontroller products. This file can be      #
# freely distributed within development tools that are supporting such        #
# microcontroller products.                                                   #
#                                                                             #
# THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED #
# OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF          #
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.#
# INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,#
# OR CONSEQUENTIAL DAMAGES, FOR	ANY REASON WHATSOEVER.                        #
#                                                                             #
###############################################################################
<?php $info= $this->infoSourceObject; ?>

<?php if($info->toolPath === false) { /*IF OPEN*/?>
B_DOXYGEN= $(BINUTILS_PATH)/../DocTools/Doxygen/bin/doxygen
<?php } else {/*ELSE OPEN*/?>
B_DOXYGEN= <?php echo $info->toolPath ?>/doxygen
<?php } /*IF CLOSE*/?>

B_DOXYGEN_LOG_DIR= <?php echo $info->rulesFilePath . PHP_EOL ?>
B_DOXYGEN_OUT_DIR= <?php echo $info->docOutPath . PHP_EOL ?>

<?php if(count($info->targetFullNames) === 0) { /*IF OPEN*/?>
B_DOXYGEN_HTML_PATH= <?php echo $info->docOutPath ?>/<?php echo $info->projectName . PHP_EOL?>
B_DOXYGEN_RULES_FILE= <?php echo $info->rulesFilePath ?>/DoxygenRules.txt
<?php if($info->hhcToolPath !== NULL)  { /*IF OPEN*/?>
B_DOXYGEN_CHM_FILE= <?php echo $info->docOutPath . "/" . $info->projectName ?>.chm
B_DOXYGEN_DOC_TARGETS= $(B_DOXYGEN_CHM_FILE)
B_DOXYGEN_CLEAN_TARGETS= $(B_DOXYGEN_HTML_PATH)

$(B_DOXYGEN_CHM_FILE):
	@echo Doxygen generating documents for <?php echo $info->projectName . PHP_EOL ?>
	@echo It takes considerable time please wait ..
	@$(B_DOXYGEN) $(B_DOXYGEN_RULES_FILE) 1>$(B_DOXYGEN_LOG_DIR)/Doxygen_log.txt 2>$(B_DOXYGEN_LOG_DIR)/Doxygen_error.txt
	@cp $(B_DOXYGEN_HTML_PATH)/<?php echo $info->projectName . ".chm"?> $(B_DOXYGEN_OUT_DIR) 2>>$(B_DOXYGEN_LOG_DIR)/Doxygen_error.txt
	@echo ..done
<?php } else {/*ELSE OPEN*/?>
B_DOXYGEN_HTML_INDEX_FILE= $(B_DOXYGEN_HTML_PATH)/Index.html
B_DOXYGEN_DOC_TARGETS= $(B_DOXYGEN_HTML_INDEX_FILE)
B_DOXYGEN_CLEAN_TARGETS= $(B_DOXYGEN_HTML_PATH)


$(B_DOXYGEN_HTML_INDEX_FILE):
	@echo Doxygen generating documents for <?php echo $info->projectName . PHP_EOL ?>
	@echo It takes considerable time please wait ..
	@$(B_DOXYGEN) $(B_DOXYGEN_RULES_FILE) 1>$(B_DOXYGEN_LOG_DIR)/Doxygen_log.txt 2>$(B_DOXYGEN_LOG_DIR)/Doxygen_error.txt
	@echo ..done
<?php } /*IF CLOSE*/?>

<?php } else { /*ELSE OPEN*/?>
B_DOXYGEN_DOC_TARGETS= #empty initialization
B_DOXYGEN_CLEAN_TARGETS= #empty initialization

<?php foreach($info->targetFullNames as $index => $targetFullName) { /*FOR OPEN*/?>
<?php $docName= $info->projectName . "_" . str_replace("/", "_", $targetFullName)?>
B_DOXYGEN_HTML_PATH<?php echo $index?>= <?php echo $info->docOutPath ?>/<?php echo $docName  . PHP_EOL?>
B_DOXYGEN_RULES_FILE<?php echo $index?>= <?php echo $info->rulesFilePath . "/" . "DoxygenRules" . str_replace("/", "", $targetFullName) . ".txt" . PHP_EOL ?>
<?php if($info->hhcToolPath !== NULL)  { /*IF OPEN*/?>
B_DOXYGEN_CHM_FILE<?php echo $index?>= <?php echo $info->docOutPath . "/" . $docName . ".chm" . PHP_EOL ?>
B_DOXYGEN_DOC_TARGETS+= $(B_DOXYGEN_CHM_FILE<?php echo $index?>)
B_DOXYGEN_CLEAN_TARGETS+= $(B_DOXYGEN_HTML_PATH<?php echo $index?>)


$(B_DOXYGEN_CHM_FILE<?php echo $index?>):
	@echo Doxygen generating documents for <?php echo $docName . PHP_EOL ?>
	@echo It takes considerable time please wait ..
	@$(B_DOXYGEN) $(B_DOXYGEN_RULES_FILE<?php echo $index?>) 1>$(B_DOXYGEN_LOG_DIR)/Doxygen_log.txt 2>$(B_DOXYGEN_LOG_DIR)/Doxygen_error.txt
	@cp -f $(B_DOXYGEN_HTML_PATH<?php echo $index?>)/<?php echo $docName . ".chm"?> $(B_DOXYGEN_OUT_DIR) 2>>$(B_DOXYGEN_LOG_DIR)/Doxygen_error.txt
	@echo ..done
<?php } else {/*ELSE OPEN*/?>
B_DOXYGEN_HTML_INDEX_FILE<?php echo $index?>= B_DOXYGEN_HTML_PATH<?php echo $index?>/Index.html
B_DOXYGEN_DOC_TARGETS+= $(B_DOXYGEN_HTML_INDEX_FILE<?php echo $index?>)
B_DOXYGEN_CLEAN_TARGETS+= $(B_DOXYGEN_HTML_PATH<?php echo $index?>)


$(B_DOXYGEN_HTML_INDEX_FILE<?php echo $index?>):
	@echo Doxygen generating documents for <?php echo $docName . PHP_EOL ?>
	@echo It takes considerable time please wait ..
	@$(B_DOXYGEN) $(B_DOXYGEN_RULES_FILE<?php echo $index?>) 1>$(B_DOXYGEN_LOG_DIR)/Doxygen_log.txt 2>$(B_DOXYGEN_LOG_DIR)/Doxygen_error.txt
	@echo ..done
<?php } /*IF CLOSE*/?>
<?php } /*FOR CLOSE*/?>
<?php } /*IF CLOSE*/?>

all: $(B_DOXYGEN_DOC_TARGETS) <?php if(!$info->keepHtml) echo "cleanHtml" . PHP_EOL?>

cleanhtml:
	@echo Cleaning generated HTML files ..
	@-rm -rf $(B_DOXYGEN_CLEAN_TARGETS)

clean:
	@echo Cleaning-up Doc folder..
	@-rm -rf 3_Doc/Doxygen

	