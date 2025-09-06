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

ifeq ($(strip $(B_PARALLEL_BUILD)),yes)
B_MULTI_PROC=-j --output-sync=target
else
B_MULTI_PROC=
endif

#Define dependency files which impact in make file generation process
B_MAKEGEN_DEPENDENCIES?= $(wildcard $(B_CONFIG_FILES_FOLDER)/*.xml \
				$(B_CONFIG_FILES_FOLDER)/*/*.xml \
				$(B_CONFIG_FILES_FOLDER)/*/*/*.xml)

#Define make gen configuration files which are inputs to the make gen process
B_MAKEGEN_CONFIGFILES?= $(wildcard $(B_CONFIG_FILES_FOLDER)/Config.xml \
				$(B_CONFIG_FILES_FOLDER)/Config*/Config.xml \
				$(B_CONFIG_FILES_FOLDER)/Config*/Config*/Config.xml)

$(B_PROJECT_MAKE): $(B_MAKEGEN_DEPENDENCIES)
	@echo Make files being generated !!!
	@$(B_PHP) $(B_PHP_MAKEGEN_SCRIPT) -d -f $(B_MAKEGEN_CONFIGFILES)
	@echo

$(B_DOXYGEN_RULES_FILE) $(B_DOXYGEN_MAKE_FILE): $(B_MAKEGEN_CONFIGFILES)
	@echo Doxygen rule and make files being generated !!!
	@$(B_PHP) $(B_PHP_DOXYGEN_SCRIPT) -d -f $(B_MAKEGEN_CONFIGFILES)
	@echo

-include $(B_PROJECT_DEP_MAKE)
