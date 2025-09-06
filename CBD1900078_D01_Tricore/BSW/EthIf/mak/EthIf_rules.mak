############################################################################### 
# File Name  : EthIf_rules.mak 
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
# 2008/11/19   1.00    visalr  Created
# 2009/10/08   1.00.03 visalr  bugfix library support
# 2013/08/05   2.00.00 vishaw  MSR4-R8 support
# 2014/03/04   2.01.00 vishaw  PTP support
# 2014/07/08   2.02.00 vishaw  ESCAN00077151: AR4-500:
#                              AUTOSAR CONC_600_SwitchConfiguration
# 2015/02/16   2.03.00 vismha  Removed PB config related parts
# 2015/06/22   2.04.00 vismha  Extended Traffic Handling source files added
# 2015/11/25   2.05.00 vismha  Introduced files containing switch hardware
#                              abstraction implementation
# 2016/06/15   3.00.00 vismha  Introduced files for Zero Copy extensions
#                              Renamed EthIf_Ptp.h/.c files to EthIf_Time.h/.c
# 2017/09/29   4.00.00 vismha  Introduced wildcard for defining files to
#                              compile
# 2017/11/16   5.00.00 vismha  Updated to latest template
#-----------------------------------------------------------------------------
# TemplateVersion = 1.01
############################################################################### 

# Component Files
CC_FILES_TO_BUILD       += EthIf\EthIf*.c
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\EthIf_Lcfg.c

# Library Settings
LIBRARIES_TO_BUILD      += EthIf
EthIf_FILES             += EthIf\EthIf*.c

