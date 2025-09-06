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

include $(BINUTILS_PATH)/../Bifaces/Make/Bifaces.mk
include 1_ToolEnv/0_Build/1_Config/Config.mk
include $(BINUTILS_PATH)/../Bifaces/Make/Targets.mk

.PHONY:all clean cleanmake rmall rebuild indent doc cleandoc oscfg prebuild postbuild help

all: $(PRE_BUILD_TARGET) build $(POST_BUILD_TARGET)

build: $(B_PROJECT_MAKE)
	@echo Now Build started !!!
	@$(MAKE) $(B_MULTI_PROC) --no-print-directory -f $(B_PROJECT_MAKE) all

#The target "clean" will remove obj + executables	
clean: $(B_PROJECT_MAKE) $(CLEAN_TARGETS)
	@echo Deleting build generated files !!!
	@$(MAKE) $(B_MULTI_PROC) --no-print-directory -f $(B_PROJECT_MAKE) clean

#The target "cleanMake" will remove generated make files	
cleanmake:
	@-rm -rf 1_ToolEnv/0_Build/9_Make

#The target "rmall" will remove obj + executables and also generated make files	
rmall: cleanMake
	@-rm -rf 2_Out
	@-rm -rf 1_ToolEnv/0_Build/9_Make
	
#The target "clean" will remove obj + executables + generated make files then rebuilds the whole project
rebuild: rmall all

#The target "indent" will make standard indentation and standard styling for the c and h files
indent:
	@echo Indent feature is not supported in this version of BIFACES!	
#indent: $(B_INDENT_MAKE)
#	@$(MAKE) -i $(MULTI_PROC) --no-print-directory -f $(B_INDENT_MAKE) all
	
#The target "doc" invokes the doxygen tool to generate the doxygen files
doc: $(B_DOXYGEN_RULES_FILE) $(B_DOXYGEN_MAKE_FILE)
	@$(MAKE) --no-print-directory -f $(B_DOXYGEN_MAKE_FILE) all
	
#The target "cleandoc" makes the output of documentation removed
cleandoc: $(B_DOXYGEN_RULES_FILE) $(B_DOXYGEN_MAKE_FILE)
	@$(MAKE) --no-print-directory -f $(B_DOXYGEN_MAKE_FILE) clean

#The target "oscfg" generates the Erika OS configurations
oscfg:
	@$(MAKE) --no-print-directory -f $(B_OSCONFIGGEN_MAKE_FILE) all

#The target "preBuild" simply runs the $(PRE_BUILD_TARGET)
prebuild: $(PRE_BUILD_TARGET)

#The target "postBuild" simply runs the $(POST_BUILD_TARGET)
postbuild: $(POST_BUILD_TARGET)

#The target "help" will provide the help on this make targets	
help:
	@echo BIFACES Version Information:
	@echo $(B_VERSION_INFO)
	@echo "Used iLLD version in examples: $(ILLD_VERSION)"
	@echo "Copyright © 2017 Infineon Technologies AG. All rights reserved."
	@echo
	@echo "GnuWin32 tool versions used with Software Framework Tools:"
	@make --version
	@sed --version
	@find --version
	@echo
	@echo "PHP tool versions used with Software Framework Tools:"
	$(B_PHP) --version
	@echo
	@echo ______________________________________________________________________________
	@echo "Usage: make -f Makefile <target>"
	@echo "following are the make targets"
	@echo  
	@echo "all: Recursive project build"
	@echo "example: make -f Makefile all"
	@echo  
	@echo "clean: removes the generated object files and executables for the configured toolchain"
	@echo "example: make -f Makefile clean"
	@echo  
	@echo "rmall: removes generated make files object files and executables. This command shall always be used when toolchain configuration changed"
	@echo "example: make -f Makefile rmall"
	@echo  
	@echo "rebuild: removes generated make files object files and executables. builds the projects"
	@echo "example: make -f Makefile rebuild"
	@echo  
	@echo "indent: Format the c and header files for non excluded part of the project. Exclude of required part shall be done with the file 1_ToolEnv/0_Build/1_Config/CfgIndent.mk"
	@echo "example: make -f Makefile indent"
	@echo  
	@echo "doc: Generate the doxygen docuement for non excluded part of the project. Exclude of required part shall be done with the file 1_ToolEnv/0_Build/1_Config/CfgDoxygen.mk"
	@echo "example: make -f Makefile indent"
	@echo  
	@echo "cleandoc: Removes generated the doxygen docuements "
	@echo "example: make -f Makefile cleandoc"
	@echo  
	@echo "oscfg: generate the configuration files for Erika OS "
	@echo "example: make -f Makefile oscfg"
	@echo 
	@echo "preBuild: Invoke the pre-build target "
	@echo "example: make -f Makefile preBuild"
	@echo 
	@echo "postBuild: Invoke the post-build target "
	@echo "example: make -f Makefile postBuild"
	@echo 
	@echo "help: displays this help message "
	@echo "example: make -f Makefile help"
	@echo  
	