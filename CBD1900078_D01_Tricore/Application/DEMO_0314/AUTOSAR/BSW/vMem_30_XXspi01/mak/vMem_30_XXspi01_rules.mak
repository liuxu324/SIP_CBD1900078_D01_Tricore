############################################################################### 
# File Name  : vMem_30_XXspi01_rules.mak 
# Description: Rules makefile 
#-----------------------------------------------------------------------------
# COPYRIGHT
#-----------------------------------------------------------------------------
# Copyright (c) 2019 by Vector Informatik GmbH.  All rights reserved.
#-----------------------------------------------------------------------------
# REVISION HISTORY
#-----------------------------------------------------------------------------
# Date         Version  Sign Description
# ----------   -------  ---- -------------------------------------------------
# 2019-11-29   1.00.00  rdl  Initial creation.
#                       mid
# 2019-03-28   1.01.00  Added support of component-based SIP structure.
############################################################################### 

# Component Files
CC_FILES_TO_BUILD       += vMem_30_XXspi01$(BSW_SRC_DIR)\vMem_30_XXspi01.c vMem_30_XXspi01$(BSW_SRC_DIR)\vMem_30_XXspi01_LL.c vMem_30_XXspi01$(BSW_SRC_DIR)\vMem_30_XXspi01_LL_FlsCmdSeqBuilder.c vMem_30_XXspi01$(BSW_SRC_DIR)\vMem_30_XXspi01_LL_FlsCmdSeqExecuter.c
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\vMem_30_XXspi01_Lcfg.c $(GENDATA_DIR)\vMem_30_XXspi01_Cbk.c

# Library Settings
LIBRARIES_TO_BUILD      += vMem_30_XXspi01
vMem_30_XXspi01_FILES   += vMem_30_XXspi01$(BSW_SRC_DIR)\vMem_30_XXspi01.c vMem_30_XXspi01$(BSW_SRC_DIR)\vMem_30_XXspi01_LL.c

