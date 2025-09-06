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
# Subdirectory make file for Defines
# !! Generated make file, modifications could be overwritten !!
#------------------------------------------------------------------------------

# ---------------------- Make variables for TOOL COMMANDS ---------------------
<?php $archNames= $makeFile->getArchitectureNames()?>
<?php foreach($archNames as $archName){ /* OPEN: ARCHNAMES FOR */ 
	$archData= $makeFile->getArchitecture($archName) ?>

# Architecture: <?php echo $archName. PHP_EOL ?>
<?php $tcNames= $archData->getToolchainNames()?>
<?php foreach($tcNames as $tcName){ /* OPEN: TCNAMES FOR */ 
	$tcData= $archData->getToolchain($tcName) ?>
# Toolchain: <?php echo $tcName ?> <?php echo str_repeat("-", 80 -15 - strlen($tcName)) . PHP_EOL ?>
<?php $toolNames= $tcData->getToolNames()?>
<?php foreach($toolNames as $toolName){ /* OPEN: TOOLNAMES FOR */ 
	$cmdVariable= $tcData->getToolCommandVariable($toolName) ?>
# Tool: <?php echo $toolName. PHP_EOL ?>
<?php echo $cmdVariable->getName() ?>= $(EXPOSE)<?php echo str_replace("\"__dummy_path__\"/","",$cmdVariable->getValue()) . PHP_EOL ?>
<?php } /* CLOSE: TOOLNAMES FOR */ ?>
<?php } /* CLOSE: TCNAMES FOR */ ?>
<?php } /* CLOSE: ARCHNAMES FOR */ ?>

# -------------- Make variables for TOOLCHAIN CONFIGURATION FILES -------------
<?php foreach($archNames as $archName){ /* OPEN: ARCHNAMES FOR */ 
	$archData= $makeFile->getArchitecture($archName) ?>

# Architecture: <?php echo $archName. PHP_EOL ?>
<?php $tcNames= $archData->getToolchainNames()?>
<?php foreach($tcNames as $tcName){ /* OPEN: TCNAMES FOR */ 
	$tcData= $archData->getToolchain($tcName) ?>
# Toolchain: <?php echo $tcName ?> <?php echo str_repeat("-", 80 -15 - strlen($tcName)) . PHP_EOL ?>
<?php $cfgFilesVariable= $tcData->getConfigFilesVariable() ?>
<?php if(isset($cfgFilesVariable)){ /* OPEN: CONFIGFILESVAR IF */ ?>
<?php echo $cfgFilesVariable->getName() ?>:= <?php echo $cfgFilesVariable->getValue() . PHP_EOL ?>
<?php } /* CLOSE: CONFIGFILESVAR IF */ ?>
<?php } /* CLOSE: TCNAMES FOR */ ?>
<?php } /* CLOSE: ARCHNAMES FOR */ ?>

# ------------------- Make variables for TARGET OUTPUT FILES ------------------

B_BUILD_TARGETS:=	# Initialized to empty
<?php foreach($archNames as $archName){ /* OPEN: ARCHNAMES FOR */ 
	$archData= $makeFile->getArchitecture($archName) ?>

# Architecture: <?php echo $archName. PHP_EOL ?>
<?php $trgtNames= $archData->getTargetNames()?>
<?php foreach($trgtNames as $trgtName){ /* OPEN: TRGTNAMES FOR */ 
	$trgtData= $archData->getTarget($trgtName) ?>
# Target: <?php echo $trgtName ?> <?php echo str_repeat("-", 80 -12 - strlen($trgtName)) . PHP_EOL ?>
<?php $buildTargets="" /* Init variable */?>
<?php $outTypes= $trgtData->getOutputTypes() ?>
<?php foreach($outTypes as $outType){ /* OPEN: OUTTYPES FOR */ 
	$outVariable= $trgtData->getOutputFileVariable($outType) ?>
# target output: <?php echo $outType ?>: <?php echo basename($outVariable->getValue()). PHP_EOL ?>
<?php if($outType==hex){ /* OPEN: OUTTYPES IF */ ?>
ifeq ($(strip $(CREATE_OUT_HEX_FILES)),yes)
<?php echo $outVariable->getName() ?>:= <?php echo $outVariable->getValue() . PHP_EOL ?>
else
<?php echo $outVariable->getName() ?>:=
endif
<?php } else if($outType==="srec"){ /* ELSE: TARGETTYPE IF */?>
ifeq ($(strip $(CREATE_OUT_SREC_FILES)),yes)
<?php echo $outVariable->getName() ?>:= <?php echo $outVariable->getValue() . PHP_EOL ?>
else
<?php echo $outVariable->getName() ?>:=
endif
<?php } else { /* ELSE: TARGETTYPE IF */?>
<?php echo $outVariable->getName() ?>:= <?php echo $outVariable->getValue() . PHP_EOL ?>
<?php } /* CLOSE: TARGETTYPE IF */?>

<?php if($outType==="lib"){ /* OPEN: TARGETTYPE IF */?>

B_BUILD_TARGETS_LIB+= <?php echo $outVariable->getReference() ?>
<?php } else { /* ELSE: TARGETTYPE IF */?>
<?php $buildTargets .= " " . $outVariable->getReference() ?>
<?php } /* CLOSE: TARGETTYPE IF */?>
<?php if($archName === "Arm"){ /* OPEN: ARCHNAMES IF */?>
<?php if($outType==="elf"){ /* OPEN: TARGETTYPE IF */?>
ELF_BIN_SECOND= <?php echo $outVariable->getReference() . PHP_EOL ?>
<?php } else if($outType==="hex"){ /* ELSE: TARGETTYPE IF */?>
HEX_BIN_SECOND= <?php echo $outVariable->getReference()  . PHP_EOL ?>
<?php } else if($outType==="srec"){ /* ELSE: TARGETTYPE IF */?>
SREC_BIN_SECOND= <?php echo $outVariable->getReference() . PHP_EOL  ?>
<?php } /* CLOSE: TARGETTYPE IF */?>
<?php } else if($archName == "8051"){ /* ELSE: ARCHNAMES IF */?>
<?php if($outType==="elf"){ /* OPEN: TARGETTYPE IF */?>
ELF_BIN_THIRD= <?php echo $outVariable->getReference() . PHP_EOL  ?>
<?php } else if($outType==="hex"){ /* ELSE: TARGETTYPE IF */?>
HEX_BIN_THIRD= <?php echo $outVariable->getReference() . PHP_EOL  ?>
<?php } else if($outType==="srec"){ /* ELSE: TARGETTYPE IF */?>
SREC_BIN_THIRD= <?php echo $outVariable->getReference() . PHP_EOL  ?>
<?php } /* CLOSE: TARGETTYPE IF */?>
<?php } else { /* ELSE: ARCHNAMES IF */?>
<?php if($outType==="elf"){ /* OPEN: TARGETTYPE IF */?>
ELF_BIN_MAIN= <?php echo $outVariable->getReference() . PHP_EOL  ?>
<?php } else if($outType==="hex"){ /* ELSE: TARGETTYPE IF */?>
HEX_BIN_MAIN= <?php echo $outVariable->getReference() . PHP_EOL  ?>
<?php } else if($outType==="srec"){ /* ELSE: TARGETTYPE IF */?>
SREC_BIN_MAIN= <?php echo $outVariable->getReference() . PHP_EOL  ?>
<?php } /* CLOSE: TARGETTYPE IF */?>
<?php } /* CLOSE: ARCHNAMES IF */?>
<?php } /* CLOSE: OUTTYPES FOR */ ?>

# Target output collection:
B_BUILD_TARGETS+= <?php echo $buildTargets  . PHP_EOL ?>
<?php } /* CLOSE: TRGTNAMES FOR */ ?>
<?php } /* CLOSE: ARCHNAMES FOR */ ?>

ifeq ("$(TOOL_CHAIN_MAIN)","Tasking")
LD_OPTS:= $(OUT_FILE_OPT) \
-I$(PROJ_DIR)/1_ToolEnv/0_Build/1_Config --lsl-file=$(LSL_MAIN_FILE) \
$(LIBS) $(LD_OPTIONS_MAIN)
endif

# ---------------------- Make variables for OBJECT FILES ----------------------
<?php foreach($archNames as $archName){ /* OPEN: ARCHNAMES FOR */ 
	$archData= $makeFile->getArchitecture($archName) ?>

# Architecture: <?php echo $archName. PHP_EOL ?>
<?php $trgtNames= $archData->getTargetNames()?>
<?php foreach($trgtNames as $trgtName){ /* OPEN: TRGTNAMES FOR */ 
	$trgtData= $archData->getTarget($trgtName) ?>
# Target: <?php echo $trgtName ?> <?php echo str_repeat("-", 80 -12 - strlen($trgtName)) . PHP_EOL ?>
<?php $objVariable= $trgtData->getObjectFilesVariable() ?>
<?php if(isset($objVariable)){ /* OPEN: OBJVAR IF */ ?>
<?php if($trgtName === "Tc"){ /* OPEN: OBJVAR1 IF */ ?>
<?php echo $objVariable->getName() ?>= $(USER_MAKE_OBJS_MAIN)
<?php } else if($archName === "Arm"){ /* ELSE: OBJVAR1 IF */?>
<?php echo $objVariable->getName() ?>= $(USER_MAKE_OBJS_SECOND)
<?php } else if($archName == "8051"){ /* ELSE: OBJVAR1 IF */?>
<?php echo $objVariable->getName() ?>= $(USER_MAKE_OBJS_THIRD)
<?php } else { /* ELSE: OBJVAR1 IF */?>
<?php echo $objVariable->getName() ?>:=  # Initialized to empty
<?php } /* CLOSE: OBJVAR1 IF */?>
<?php if($archName === "Arm"){ /* ELSE: OBJVAR1 IF */?>
OBJ_FILES_SECOND= <?php echo $objVariable->getReference()  . PHP_EOL ?>
<?php } else if($archName == "8051"){ /* ELSE: OBJVAR1 IF */?>
OBJ_FILES_THIRD= <?php echo $objVariable->getReference()  . PHP_EOL ?>
<?php } /* CLOSE: OBJVAR1 IF */?>
<?php } /* CLOSE: OBJVAR IF */ ?>

<?php $srcObjVariable= $trgtData->getSrcObjectFilesVariable() ?>
<?php if(isset($srcObjVariable)){ /* OPEN: SRCOBJVAR IF */ ?>
<?php echo $srcObjVariable->getName() ?>:=  # Initialized to empty
<?php if($archName === "Arm"){ /* ELSE: SRCOBJVAR IF */?>
PROJ_OBJS_SECOND= <?php echo $srcObjVariable->getReference()  . PHP_EOL ?>
<?php } else if($archName == "8051"){ /* ELSE: CUSTOBJVAR1 IF */?>
PROJ_OBJS_THIRD= <?php echo $srcObjVariable->getReference()  . PHP_EOL ?>
<?php } /* CLOSE: SRCOBJVAR IF */?>
<?php } /* CLOSE: SRCOBJVAR IF */ ?>
<?php $custObjVariable= $trgtData->getUserMakeObjectFilesVariable() ?>
<?php if(isset($custObjVariable)){ /* OPEN: CUSTOBJVAR IF */ ?>
<?php echo $custObjVariable->getName() ?>:=  # Initialized to empty
<?php } /* CLOSE: CUSTOBJVAR IF */ ?>
<?php } /* CLOSE: TRGTNAMES FOR */ ?>
<?php } /* CLOSE: ARCHNAMES FOR */ ?>

# ------------------ Make variables for OBJECTS LIST FILES --------------------
<?php foreach($archNames as $archName){ /* OPEN: ARCHNAMES FOR */ 
	$archData= $makeFile->getArchitecture($archName) ?>

# Architecture: <?php echo $archName. PHP_EOL ?>
<?php $trgtNames= $archData->getTargetNames()?>
<?php foreach($trgtNames as $trgtName){ /* OPEN: TRGTNAMES FOR */ 
	$trgtData= $archData->getTarget($trgtName) ?>
# Target: <?php echo $trgtName ?> <?php echo str_repeat("-", 80 -12 - strlen($trgtName)) . PHP_EOL ?>
<?php $objLstVariable= $trgtData->getObjectFilesListFileVariable() ?>
<?php if($trgtName === "Tc"){ /* OPEN: CUSTOBJVAR1 IF */ ?>
<?php echo $objLstVariable->getName() ?>= <?php echo $objLstVariable->getValue() ?> $(USER_MAKE_OBJS_MAIN)
<?php } else if($archName === "Arm"){ /* ELSE: CUSTOBJVAR1 IF */?>
<?php echo $objLstVariable->getName() ?>= <?php echo $objLstVariable->getValue() ?> $(USER_MAKE_OBJS_SECOND)
<?php } else if($archName == "8051"){ /* ELSE: CUSTOBJVAR1 IF */?>
<?php echo $objLstVariable->getName() ?>= <?php echo $objLstVariable->getValue() ?> $(USER_MAKE_OBJS_THIRD)
<?php } else { /* ELSE: CUSTOBJVAR1 IF */?>
<?php echo $objLstVariable->getName() ?>:= <?php echo $objLstVariable->getValue() . PHP_EOL ?>
<?php } /* CLOSE: CUSTOBJVAR1 IF */?>
<?php } /* CLOSE: TRGTNAMES FOR */ ?>
<?php } /* CLOSE: ARCHNAMES FOR */ ?>

# ---------------- Make variables for INCLUDE PATHS LIST FILES ----------------
<?php foreach($archNames as $archName){ /* OPEN: ARCHNAMES FOR */ 
	$archData= $makeFile->getArchitecture($archName) ?>
# Architecture: <?php echo $archName. PHP_EOL ?>
<?php $incLstVariable= $archData->getIncludePathsListFileVariable() ?>
<?php echo $incLstVariable->getName() ?>:= <?php echo $incLstVariable->getValue() . PHP_EOL ?>
<?php } /* CLOSE: ARCHNAMES FOR */ ?>
<?php $extIncPathVariable= $makeFile->getExternalIncludePathsVariable() ?>
<?php if(isset($extIncPathVariable)){ /* OPEN: EXTINCPATHSVAR IF */ ?>

# ----------------- Make variables for EXTERNAL INCLUDE PATHS -----------------
<?php echo $extIncPathVariable->getName() ?>:= <?php echo $extIncPathVariable->getValue() . PHP_EOL ?>
<?php } /* CLOSE: EXTINCPATHSVAR IF */ ?>

# ------------------ Make variables for LINKER COMMAND FILES ------------------
B_GEN_LCF_FILE_TRICORE_TC:= $(LSL_MAIN_FILE)
B_GEN_LCF_FILE_ARM_TC:= $(LSL_SECOND_FILE)
B_GEN_LCF_FILE_8051_TC:= $(LSL_THIRD_FILE)

# ------------------------ Make variables for extensions ----------------------
# Architecture Names:
<?php foreach($makeFile->getArchitectureNameVariables() as  $archVariable){ /* OPEN: ARCHNAMEVARS FOR */ ?>
<?php echo $archVariable->getName() ?>:= <?php echo $archVariable->getValue() . PHP_EOL ?>
<?php } /* CLOSE: ARCHNAMEVARS FOR */ ?>

# Target Names:
<?php foreach($archNames as $archName){ /* OPEN: ARCHNAMES FOR */ 
	$archData= $makeFile->getArchitecture($archName) ?>
# Architecture: <?php echo $archName ?> <?php echo str_repeat("-", 80 -18 - strlen($archName)) . PHP_EOL ?>
<?php foreach($archData->getTargetNameVariables() as $targetNameVariable){ /* OPEN: TRGTNAMEVARS FOR */ ?>
<?php echo $targetNameVariable->getName() ?>:= <?php echo $targetNameVariable->getValue() . PHP_EOL ?>
<?php } /* CLOSE: TRGTNAMEVARS FOR */ ?>
<?php } /* CLOSE: ARCHNAMES FOR */ ?>

# Toolchain Names:
<?php foreach($archNames as $archName){ /* OPEN: ARCHNAMES FOR */ 
	$archData= $makeFile->getArchitecture($archName) ?>
# Architecture: <?php echo $archName ?> <?php echo str_repeat("-", 80 -18 - strlen($archName)) . PHP_EOL ?>
<?php foreach($archData->getToolchainNameVariables() as $toolchainNameVariable){ /* OPEN: TCNAMEVARS FOR */ ?>
<?php echo $toolchainNameVariable->getName() ?>:= <?php echo $toolchainNameVariable->getValue() . PHP_EOL ?>
<?php } /* CLOSE: TCNAMEVARS FOR */ ?>
<?php } /* CLOSE: ARCHNAMES FOR */ ?>

# Output Path:
<?php foreach($archNames as $archName){ /* OPEN: ARCHNAMES FOR */ 
	$archData= $makeFile->getArchitecture($archName) ?>
# Architecture: <?php echo $archName ?> <?php echo str_repeat("-", 80 -18 - strlen($archName)) . PHP_EOL ?>
<?php $outPathVariable= $archData->getOutputPathVariable() ?>
<?php echo $outPathVariable->getName() ?>:= <?php echo $outPathVariable->getValue() . PHP_EOL ?>
<?php } /* CLOSE: ARCHNAMES FOR */ ?>

# ------------------ Make variable for BUILD DEPENDENCY FILE ------------------
<?php $depVariable= $makeFile->getDependencyVariable() ?>
<?php echo $depVariable->getName() ?>:=  # Initialized to empty