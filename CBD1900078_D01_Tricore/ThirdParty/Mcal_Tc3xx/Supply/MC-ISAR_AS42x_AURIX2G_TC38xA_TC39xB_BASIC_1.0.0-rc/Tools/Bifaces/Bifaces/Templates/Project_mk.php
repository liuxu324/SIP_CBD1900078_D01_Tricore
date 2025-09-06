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
# Subdirectory make file for Project
# !! Generated make file, modifications could be overwritten !!
#------------------------------------------------------------------------------

SHELL = /bin/sh

include $(BINUTILS_PATH)/../Bifaces/Make/Bifaces.mk           # Get the common macros and variables
include 1_ToolEnv/0_Build/1_Config/Config.mk                  # Configuration make file for the project
include <?php echo $makeFile->getDefinesMakePathName() ?>     # To get required make variables
<?php if(count($makeFile->subFolderMakePathNames) > 0){ /* OPEN: INCLUDE IF */ ?>

# Include sub folder make files
<?php foreach($makeFile->subFolderMakePathNames as $subFolderMakePathNames){ /* OPEN: INCLUDE FOR */ ?>
include <?php echo $subFolderMakePathNames . PHP_EOL ?>
<?php } /* CLOSE: INCLUDE FOR */ ?>
<?php } /* CLOSE: INCLUDE IF */?>
<?php $rules= $makeFile->makeRules;
if(count($rules) > 0){ /* OPEN: RULES IF */ ?>

.PHONY: all clean

all: $(B_BUILD_TARGETS)

# Make-Rules:
<?php foreach($rules as $archName => $archRules){ /* OPEN: ARCHRULES FOR */ ?>

# Make-rules for architecture: <?php echo $archName ?> <?php echo str_repeat("-", 80 - 32 - strlen($archName)) . PHP_EOL ?>
<?php foreach($archRules as $targetName => $targetRules){ /* OPEN: TARGETRULES FOR */?>

# Make-rules for target: <?php echo $targetName ?> <?php echo str_repeat("-", 80 - 26 - strlen($targetName)) . PHP_EOL ?>
<?php foreach($targetRules as $outType => $rule){ /* OPEN: RULES FOR */ ?>

# Make-rule to build: <?php echo $outType . PHP_EOL ?>
<?php echo $rule->target ?>: <?php echo $rule->preRequisite . PHP_EOL ?>
	@mkdir -p $(@D)
	@-rm -f $@
	@echo 'Building output <?php echo $rule->target ?>'
<?php foreach($rule->recipes as $recipe){ /* OPEN: RECIPES FOR */ ?>
	<?php echo $recipe . PHP_EOL ?>
<?php } /* CLOSE: RECIPES FOR */ ?>
<?php } /* CLOSE: RULES FOR */ ?>
<?php } /* CLOSE: TARGETRULES FOR */ ?>
<?php } /* CLOSE: ARCHRULES FOR */ ?>
<?php } else { /* ELSE: RULES IF */ ?>
all: 
	@echo No source files to build !!!
<?php } /* CLOSE: RULES IF */ ?>

# Make-Rule for clean
clean:
	@-rm -rf <?php foreach($makeFile->outputPaths as $outputPath) echo $outputPath . " " ?>


#include dependency make files
-include <?php echo $makeFile->getDependencyReference() . PHP_EOL ?>