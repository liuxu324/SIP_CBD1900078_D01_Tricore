############################################################################### 
# File Name  : LinIf_rules.mak 
# Description: Rules makefile 
#-----------------------------------------------------------------------------
# COPYRIGHT
#-----------------------------------------------------------------------------
# Copyright (c) 2018 by Vector Informatik GmbH.  All rights reserved.
#-----------------------------------------------------------------------------
# REVISION HISTORY
#-----------------------------------------------------------------------------
# Date         Version  Sign    Description
# ----------   -------  ----    -------------------------------------------------
# 2012-08-30   1.00.00  visbmo  Initial Version
# 2018-07-16   1.01.00  visbmo  Update to latest template (1.01)
#-----------------------------------------------------------------------------
# TemplateVersion = 1.01
############################################################################### 

# Component Files
CC_FILES_TO_BUILD       += LinIf\LinIf.c

GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\LinIf_Lcfg.c $(GENDATA_DIR)\LinIf_PBcfg.c
ifeq ($(LINIF_USE_LINTP),1)
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\LinTp_Lcfg.c $(GENDATA_DIR)\LinTp_PBcfg.c
endif

# Library Settings
LIBRARIES_TO_BUILD      += LinIf
LinIf_FILES             = LinIf\LinIf.c
