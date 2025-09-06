###############################################################################
#                                                                             #
#       Copyright (C) 2017 Infineon Technologies AG. All rights reserved.     #
#                                                                             #
#                                                                             #
#                              IMPORTANT NOTICE                               #
#                                                                             #
#                                                                             #
# Infineon Technologies AG (Infineon) is supplying this file for use          #
# exclusively with Infineon’s microcontroller products. This file can be      #
# freely distributed within development tools that are supporting such        #
# microcontroller products.                                                   #
#                                                                             #
# THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED #
# OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF          #
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.#
# INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,#
# OR CONSEQUENTIAL DAMAGES, FOR	ANY REASON WHATSOEVER.                        #
#                                                                             #
###############################################################################

B_GNUC_TRICORE_PATH?= C:\sofit\aurix2g_sw_mcal\hightec\toolchains\tricore\v4.9.2.0

B_GNUC_TRICORE_CC_OPTIONS= -DGNU -Wall -std=c99 -c -O2 -mtc162 -meabi -fno-short-enums \
		 -ffunction-sections -fdata-sections -fstrict-volatile-bitfields

B_GNUC_TRICORE_LD_OPTIONS= -Wl,--mcpu=tc162 -Wl,--gc-sections -nostartfiles -n

B_GNUC_TRICORE_ASM_OPTIONS= $(B_GNUC_TRICORE_CC_OPTIONS)

#Include path for library directories. Add each path with following format as shown below.
#Each path prefixed with -L and separated by a space.
#B_GNUC_TRICORE_LIB_INC=-Wl,-L<path>[ -Wl,-L<path>][..]
B_GNUC_TRICORE_LIB_INC=

#Libraries to include shall be listed with option -l, with following format.
#B_GNUC_TRICORE_LIBS=-l<lib name>[ -l<lib name>][..]
B_GNUC_TRICORE_LIBS=

