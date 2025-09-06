############################################################################### 
# File Name  : EthTSyn_rules.mak 
# Description: Rules makefile 
#-----------------------------------------------------------------------------
# COPYRIGHT
#-----------------------------------------------------------------------------
# Copyright (c) 2017 by Vector Informatik GmbH.  All rights reserved.
#-----------------------------------------------------------------------------
# REVISION HISTORY
#-----------------------------------------------------------------------------
# Date         Version  Sign Description
# ----------   -------  ---- -------------------------------------------------
# 2014-08-28   1.00.00  Lje  Created
# 2016-07-29   2.00.00  Sem  EthTSyn Switch Management submodule source file
#                            added
# 2017-06-08   3.00.00  Sem  Introduced Wildecard to match all EthTSyn
#                            source files without further adoptions
# 2017-11-20   4.00.00  Sem  Updated to template version 1.01
#-----------------------------------------------------------------------------
# TemplateVersion = 1.01
###############################################################################

# Component Files
CC_FILES_TO_BUILD       += EthTSyn\EthTSyn*.c
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\EthTSyn_Lcfg.c

# Library Settings
LIBRARIES_TO_BUILD      += EthTSyn
EthTSyn_FILES            = EthTSyn\EthTSyn*.c