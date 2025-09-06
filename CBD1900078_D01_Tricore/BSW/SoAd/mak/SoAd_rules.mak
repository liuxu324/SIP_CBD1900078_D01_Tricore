############################################################################### 
# File Name  : SoAd_rules.mak 
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
# 2008-11-19   1.00.00  alr  Created
# 2009-10-08   1.00.01  alr  bugfix library support
# 2009-10-08   1.00.02  alr  file names changed
# 2009-11-18   1.00.03  alr  deleted path variables
# 2012-09-26   1.00.04  mda  changed comments and add path variables
# 2013-01-18   1.01.00  mda  added SoAd_XcpRoute.c
# 2013-09-27   2.00.00  mda  branch for ASR 4.1.1
# 2015-11-09   3.00.00  mda  added SoAd_PBcfg.c
#                            version history in <Msn>_rules.mak only
# 2017-11-21   4.00.00  mda  updated to new template
#-----------------------------------------------------------------------------
# TemplateVersion = 1.01
############################################################################### 

# Component Files
CC_FILES_TO_BUILD       += SoAd\SoAd*.c
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\SoAd_Lcfg.c $(GENDATA_DIR)\SoAd_PBcfg.c

# Library Settings
LIBRARIES_TO_BUILD      += SoAd
SoAd_FILES              += SoAd\SoAd*.c

