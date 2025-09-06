<?php 
$info= $this->infoSourceObject;
$makeFile= $info;
?>
# -----------------------------------------------------------------------------
#
# Copyright (C) 2015-2017 Infineon Technologies AG. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# - Redistributions of source code must retain the above copyright notice,
#   this list of conditions and the following disclaimer.
# - Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation.
#   and/or other materials provided with the distribution.
# - Neither the name of the copyright holders nor the names of its
#   contributors may be used to endorse or promote products derived from this
#   software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
# TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
# To improve the quality of the software, users are encouraged to share
# modifications, enhancements or bug fixes with Infineon Technologies AG
# (support@infineon.com).
# 
# -----------------------------------------------------------------------------
# Subdirectory make file for <?php echo $makeFile->getFolderPath() . PHP_EOL ?>
# !! Generated make file, modifications could be overwritten !!
#------------------------------------------------------------------------------

<?php if(count($makeFile->subFolderMakePathNames) > 0){ /* OPEN: INCLUDE IF */ ?>

# Include sub folder make files
<?php foreach($makeFile->subFolderMakePathNames as $incPath){ /* OPEN: INCLUDE FOR */ ?>
include <?php echo $incPath . PHP_EOL ?>
<?php } /* CLOSE: INCLUDE FOR */ ?>
<?php } /* CLOSE: INCLUDE IF */ ?>
<?php $objSrcs= $makeFile->getSrcObjectFilesVariables();
if(count($objSrcs) > 0){ /* OPEN: SRC_OBJECT IF */ ?>

# Update pre existing object files to each target
<?php foreach($objSrcs as $objSrc){ /* OPEN: SRC_OBJECT FOR */ ?>
<?php echo $objSrc->getName() ?>+= <?php echo $objSrc->getValue() . PHP_EOL ?>
<?php } /* CLOSE: SRC_OBJECT FOR */ ?>
<?php } /* CLOSE: SRC_OBJECT IF */ ?>
<?php $rules= $makeFile->makeRules;
if(count($rules) > 0){ /* OPEN: RULES IF */ ?>

# Make-Rules:
<?php foreach($rules as $archName => $rulesList){ /* OPEN: RULESLIST FOR */ ?>
# Make-rules for architecture: <?php echo $archName . PHP_EOL ?>
<?php foreach($rulesList as $fileName => $rule){ /* OPEN: RULES FOR */ ?>

#Make-rule to build file: <?php echo $fileName . PHP_EOL ?>
<?php echo $rule->dependencyFilesVariable->getName() ?>+= <?php echo $rule->dependencyFilesVariable->getValue() . PHP_EOL ?>
<?php foreach($rule->objectFilesVariables as $objFilesVariable){ /* OPEN: OBJFILES FOR */ ?>
<?php echo $objFilesVariable->getName() ?>+= <?php echo $objFilesVariable->getValue() . PHP_EOL ?>
<?php } /* CLOSE: OBJFILES FOR */ ?>

<?php echo $rule->target ?>: <?php echo $rule->preRequisite . PHP_EOL ?>
	@mkdir -p $(@D)
	@-rm -f<?php foreach($rule->buildOutputReferences as $outputRef) echo " " . $outputRef?><?php echo PHP_EOL ?>
	@echo 'Building source file <?php echo $rule->sourceFileName ?> for <?php echo $archName ?>'
<?php foreach($rule->recipes as $recipe){ /* OPEN: RECIPES FOR */ ?>
	<?php echo $recipe . PHP_EOL ?>
<?php } /* CLOSE: RECIPES FOR */ ?>
<?php } /* CLOSE: RULES FOR */ ?>
<?php } /* CLOSE: RULESLIST FOR */ ?>
<?php } /* CLOSE: RULES IF */ ?>