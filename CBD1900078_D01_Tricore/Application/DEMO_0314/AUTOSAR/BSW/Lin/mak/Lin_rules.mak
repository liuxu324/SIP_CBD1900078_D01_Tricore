############################################################################### 
# File Name  : Lin_rules.mak 
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
# 14.00.00  2018-02-28  jgl     Initial Version
# 14.00.01  2018-09-06  jgl     Change to new template and TASK-81282
# 14.01.00  2019-02-06  vircbl  Added support of component-based SIP structure
#------------------------------------------------------------------------------
# TemplateVersion = 1.02
###############################################################################

# Component Files
CC_FILES_TO_BUILD       += Lin$(BSW_SRC_DIR)\Lin.c
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\Lin_*.c

# Library Settings
LIBRARIES_TO_BUILD      += Lin
Lin_FILES               = Lin$(BSW_SRC_DIR)\Lin.c

