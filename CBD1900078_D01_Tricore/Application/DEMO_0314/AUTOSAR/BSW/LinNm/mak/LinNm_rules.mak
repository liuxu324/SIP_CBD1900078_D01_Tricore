############################################################################### 
# File Name  : LinNm_rules.mak 
# Description: Rules makefile 
#------------------------------------------------------------------------------
# COPYRIGHT
#------------------------------------------------------------------------------
# Copyright (c) 2019 by Vector Informatik GmbH.  All rights reserved.
#------------------------------------------------------------------------------
# REVISION HISTORY
#------------------------------------------------------------------------------
# Version   Date        Author  Description
#------------------------------------------------------------------------------
# 1.00.00   2012-08-28  visbmo  Initial Version
# 1.01.00   2017-07-16  visbmo  Update to latest template (1.01)
# 1.01.01   2019-02-06  vircbl  Added support of component-based SIP structure
#------------------------------------------------------------------------------
# TemplateVersion = 1.02
###############################################################################

# Component Files
CC_FILES_TO_BUILD       += LinNm$(BSW_SRC_DIR)\LinNm.c
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\LinNm_Lcfg.c

# Library Settings
LIBRARIES_TO_BUILD      += LinNm
LinNm_FILES              = LinNm$(BSW_SRC_DIR)\LinNm.c

