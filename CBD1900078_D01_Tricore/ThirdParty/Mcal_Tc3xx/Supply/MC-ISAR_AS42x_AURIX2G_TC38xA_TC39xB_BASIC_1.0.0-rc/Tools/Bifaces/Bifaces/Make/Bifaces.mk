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

# Automatically fetch the project name
PROJ_NAME= $(lastword $(subst /, ,$(CURDIR)))

B_VERSION_INFO= BIFACES V1.0.0

B_TOOLENV_CONFIG_PATH= 1_ToolEnv/0_Build/1_Config

B_PROJECT_MAKE= 1_ToolEnv/0_Build/9_Make/Project.mk
B_PROJECT_DEP_MAKE= 1_ToolEnv/0_Build/9_Make/ProjectDep.mk

B_INDENT_MAKE= $(BINUTILS_PATH)/../Bifaces/Make/Indent.mk

B_DOXYGEN_RULES_FILE= 3_Doc/Doxygen/Log/DoxygenRules.txt
B_DOXYGEN_MAKE_FILE= 3_Doc/Doxygen/Log/Doxygen.mk

B_OSCONFIGGEN_MAKE_FILE= "$(BINUTILS_PATH)"/../OsTools/OsCfgGen.mk
ifneq ($(wildcard 1_ToolEnv/0_Build/1_Config/CfgErikaOS.oil),)
PRE_BUILD_TARGET:= oscfg
endif

# PHP Configuration ###############
B_PHP_PATH?="$(BINUTILS_PATH)"/../Php
B_PHP_MAKEGEN_SCRIPT?="$(BINUTILS_PATH)"/../Bifaces/Scripts/MakeGen/MainCall.php
B_PHP_DOXYGEN_SCRIPT?="$(BINUTILS_PATH)"/../Bifaces/Scripts/DoxyGen/MainCall.php
B_PHP= $(B_PHP_PATH)/php
