/**
 * \file IfxCpu_Bmhd.c
 * \brief This file contains the Bmhd for Aurix Plus.
 * \version
 * \copyright Copyright (c) 2016 Infineon Technologies AG. All rights reserved.
 *
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Ifx_Ssw.h"

/*******************************************************************************
**                      Type definitions                                     **
*******************************************************************************/

/*******************************************************************************
**                              BMHD constants                                **
*******************************************************************************/

#if defined(__GNUC__)
#pragma section
#pragma section ".bmhd_0_orig" a
#endif
#if defined(__TASKING__)
#pragma section farrom "bmhd_0_orig"
#endif
#if defined(__DCC__)
#pragma section CONST ".bmhd_0_orig" far-absolute R
#endif
#if defined(__ghs__)
#pragma ghs section rodata=".bmhd_0_org"
#endif
const Ifx_Ssw_Bmhd bmhd_0_orig = {
    0x00FE,                                                                     /**< \brief 0x000: .bmi: Boot Mode Index (BMI)*/
    0xB359,                                                                     /**< \brief 0x002: .bmhdid: Boot Mode Header ID (CODE) = B359H*/
    0xA0000000,                                                                 /**< \brief 0x004: .stad: User Code start address*/
    0x31795570,                                                                 /**< \brief 0x008: .crc: Check Result for the BMI Header (offset 000H - 007H)*/
    0xCE86AA8F,                                                                 /**< \brief 0x00C: .crcInv: Inverted Check Result for the BMI Header (offset 000H - 007H)*/
    {                                                                           /*Col:1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12 */
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 1*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 2*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 3*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 4*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 5*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 6*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 7*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 8*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 9*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row:10*/
    },                                                                          /**< \brief 0x010: Reserved area 120 x 4= 480 bytes filled with zeros */
    0x43211234                                                                  /**< \brief 0x1F0: .confirmation: 32-bit CODE, (always same)*/
};

#if defined(__GNUC__)
#pragma section
#pragma section ".bmhd_0_copy" a
#endif
#if defined(__TASKING__)
#pragma section farrom "bmhd_0_copy"
#endif
#if defined(__DCC__)
#pragma section CONST ".bmhd_0_copy" far-absolute R
#endif
#if defined(__ghs__)
#pragma ghs section rodata=".bmhd_0_copy"
#endif
const Ifx_Ssw_Bmhd bmhd_0_copy = {
    0x00FE,                                                                     /**< \brief 0x000: .bmi: Boot Mode Index (BMI)*/
    0xB359,                                                                     /**< \brief 0x002: .bmhdid: Boot Mode Header ID (CODE) = B359H*/
    0xA0000000,                                                                 /**< \brief 0x004: .stad: User Code start address*/
    0x31795570,                                                                 /**< \brief 0x008: .crc: Check Result for the BMI Header (offset 000H - 007H)*/
    0xCE86AA8F,                                                                 /**< \brief 0x00C: .crcInv: Inverted Check Result for the BMI Header (offset 000H - 007H)*/
    {                                                                           /*Col:1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12 */
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 1*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 2*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 3*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 4*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 5*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 6*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 7*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 8*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 9*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row:10*/
    },                                                                          /**< \brief 0x010: Reserved area 120 x 4= 480 bytes filled with zeros */
    0x43211234                                                                  /**< \brief 0x1F0: .confirmation: 32-bit CODE, (always same)*/
};

#if defined(__GNUC__)
#pragma section
#pragma section ".bmhd_1_orig" a
#endif
#if defined(__TASKING__)
#pragma section farrom "bmhd_1_orig"
#endif
#if defined(__DCC__)
#pragma section CONST ".bmhd_1_orig" far-absolute R
#endif
#if defined(__ghs__)
#pragma ghs section rodata=".bmhd_1_org"
#endif
const Ifx_Ssw_Bmhd bmhd_1_orig = {
    0x00FE,                                                                     /**< \brief 0x000: .bmi: Boot Mode Index (BMI)*/
    0xB359,                                                                     /**< \brief 0x002: .bmhdid: Boot Mode Header ID (CODE) = B359H*/
    0xA0000000,                                                                 /**< \brief 0x004: .stad: User Code start address*/
    0x31795570,                                                                 /**< \brief 0x008: .crc: Check Result for the BMI Header (offset 000H - 007H)*/
    0xCE86AA8F,                                                                 /**< \brief 0x00C: .crcInv: Inverted Check Result for the BMI Header (offset 000H - 007H)*/
    {                                                                           /*Col:1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12 */
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 1*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 2*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 3*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 4*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 5*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 6*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 7*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 8*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 9*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row:10*/
    },                                                                          /**< \brief 0x010: Reserved area 120 x 4= 480 bytes filled with zeros */
    0x43211234                                                                  /**< \brief 0x1F0: .confirmation: 32-bit CODE, (always same)*/
};

#if defined(__GNUC__)
#pragma section
#pragma section ".bmhd_1_copy" a
#endif
#if defined(__TASKING__)
#pragma section farrom "bmhd_1_copy"
#endif
#if defined(__DCC__)
#pragma section CONST ".bmhd_1_copy" far-absolute R
#endif
#if defined(__ghs__)
#pragma ghs section rodata=".bmhd_1_copy"
#endif
const Ifx_Ssw_Bmhd bmhd_1_copy = {
    0x00FE,                                                                     /**< \brief 0x000: .bmi: Boot Mode Index (BMI)*/
    0xB359,                                                                     /**< \brief 0x002: .bmhdid: Boot Mode Header ID (CODE) = B359H*/
    0xA0000000,                                                                 /**< \brief 0x004: .stad: User Code start address*/
    0x31795570,                                                                 /**< \brief 0x008: .crc: Check Result for the BMI Header (offset 000H - 007H)*/
    0xCE86AA8F,                                                                 /**< \brief 0x00C: .crcInv: Inverted Check Result for the BMI Header (offset 000H - 007H)*/
    {                                                                           /*Col:1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12 */
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 1*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 2*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 3*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 4*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 5*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 6*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 7*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 8*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 9*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row:10*/
    },                                                                          /**< \brief 0x010: Reserved area 120 x 4= 480 bytes filled with zeros */
    0x43211234                                                                  /**< \brief 0x1F0: .confirmation: 32-bit CODE, (always same)*/
};

#if defined(__GNUC__)
#pragma section
#pragma section ".bmhd_2_orig" a
#endif
#if defined(__TASKING__)
#pragma section farrom "bmhd_2_orig"
#endif
#if defined(__DCC__)
#pragma section CONST ".bmhd_2_orig" far-absolute R
#endif
#if defined(__ghs__)
#pragma ghs section rodata=".bmhd_2_org"
#endif
const Ifx_Ssw_Bmhd bmhd_2_orig = {
    0x00FE,                                                                     /**< \brief 0x000: .bmi: Boot Mode Index (BMI)*/
    0xB359,                                                                     /**< \brief 0x002: .bmhdid: Boot Mode Header ID (CODE) = B359H*/
    0xA0000000,                                                                 /**< \brief 0x004: .stad: User Code start address*/
    0x31795570,                                                                 /**< \brief 0x008: .crc: Check Result for the BMI Header (offset 000H - 007H)*/
    0xCE86AA8F,                                                                 /**< \brief 0x00C: .crcInv: Inverted Check Result for the BMI Header (offset 000H - 007H)*/
    {                                                                           /*Col:1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12 */
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 1*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 2*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 3*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 4*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 5*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 6*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 7*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 8*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 9*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row:10*/
    },                                                                          /**< \brief 0x010: Reserved area 120 x 4= 480 bytes filled with zeros */
    0x43211234                                                                  /**< \brief 0x1F0: .confirmation: 32-bit CODE, (always same)*/
};

#if defined(__GNUC__)
#pragma section
#pragma section ".bmhd_2_copy" a
#endif
#if defined(__TASKING__)
#pragma section farrom "bmhd_2_copy"
#endif
#if defined(__DCC__)
#pragma section CONST ".bmhd_2_copy" far-absolute R
#endif
#if defined(__ghs__)
#pragma ghs section rodata=".bmhd_2_copy"
#endif
const Ifx_Ssw_Bmhd bmhd_2_copy = {
    0x00FE,                                                                     /**< \brief 0x000: .bmi: Boot Mode Index (BMI)*/
    0xB359,                                                                     /**< \brief 0x002: .bmhdid: Boot Mode Header ID (CODE) = B359H*/
    0xA0000000,                                                                 /**< \brief 0x004: .stad: User Code start address*/
    0x31795570,                                                                 /**< \brief 0x008: .crc: Check Result for the BMI Header (offset 000H - 007H)*/
    0xCE86AA8F,                                                                 /**< \brief 0x00C: .crcInv: Inverted Check Result for the BMI Header (offset 000H - 007H)*/
    {                                                                           /*Col:1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12 */
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 1*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 2*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 3*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 4*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 5*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 6*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 7*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 8*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 9*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row:10*/
    },                                                                          /**< \brief 0x010: Reserved area 120 x 4= 480 bytes filled with zeros */
    0x43211234                                                                  /**< \brief 0x1F0: .confirmation: 32-bit CODE, (always same)*/
};

#if defined(__GNUC__)
#pragma section
#pragma section ".bmhd_3_orig" a
#endif
#if defined(__TASKING__)
#pragma section farrom "bmhd_3_orig"
#endif
#if defined(__DCC__)
#pragma section CONST ".bmhd_3_orig" far-absolute R
#endif
#if defined(__ghs__)
#pragma ghs section rodata=".bmhd_3_org"
#endif
const Ifx_Ssw_Bmhd bmhd_3_orig = {
    0x00FE,                                                                     /**< \brief 0x000: .bmi: Boot Mode Index (BMI)*/
    0xB359,                                                                     /**< \brief 0x002: .bmhdid: Boot Mode Header ID (CODE) = B359H*/
    0xA0000000,                                                                 /**< \brief 0x004: .stad: User Code start address*/
    0x31795570,                                                                 /**< \brief 0x008: .crc: Check Result for the BMI Header (offset 000H - 007H)*/
    0xCE86AA8F,                                                                 /**< \brief 0x00C: .crcInv: Inverted Check Result for the BMI Header (offset 000H - 007H)*/
    {                                                                           /*Col:1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12 */
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 1*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 2*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 3*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 4*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 5*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 6*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 7*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 8*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 9*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row:10*/
    },                                                                          /**< \brief 0x010: Reserved area 120 x 4= 480 bytes filled with zeros */
    0x43211234                                                                  /**< \brief 0x1F0: .confirmation: 32-bit CODE, (always same)*/
};

#if defined(__GNUC__)
#pragma section
#pragma section ".bmhd_3_copy" a
#endif
#if defined(__TASKING__)
#pragma section farrom "bmhd_3_copy"
#endif
#if defined(__DCC__)
#pragma section CONST ".bmhd_3_copy" far-absolute R
#endif
#if defined(__ghs__)
#pragma ghs section rodata=".bmhd_3_copy"
#endif
const Ifx_Ssw_Bmhd bmhd_3_copy = {
    0x00FE,                                                                     /**< \brief 0x000: .bmi: Boot Mode Index (BMI)*/
    0xB359,                                                                     /**< \brief 0x002: .bmhdid: Boot Mode Header ID (CODE) = B359H*/
    0xA0000000,                                                                 /**< \brief 0x004: .stad: User Code start address*/
    0x31795570,                                                                 /**< \brief 0x008: .crc: Check Result for the BMI Header (offset 000H - 007H)*/
    0xCE86AA8F,                                                                 /**< \brief 0x00C: .crcInv: Inverted Check Result for the BMI Header (offset 000H - 007H)*/
    {                                                                           /*Col:1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12 */
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 1*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 2*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 3*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 4*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 5*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 6*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 7*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 8*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row: 9*/
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*Row:10*/
    },                                                                          /**< \brief 0x010: Reserved area 120 x 4= 480 bytes filled with zeros */
    0x43211234                                                                  /**< \brief 0x1F0: .confirmation: 32-bit CODE, (always same)*/
};

#if defined(__GNUC__)
#pragma section
#endif
