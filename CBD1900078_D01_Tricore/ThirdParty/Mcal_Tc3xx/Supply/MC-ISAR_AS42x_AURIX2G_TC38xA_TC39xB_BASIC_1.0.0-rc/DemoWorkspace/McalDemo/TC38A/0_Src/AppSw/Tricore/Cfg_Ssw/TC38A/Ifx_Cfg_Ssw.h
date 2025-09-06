/**
 * \file Ifx_Cfg_Ssw.h
 * \brief Configuration header file for the Startup Software
 * \ingroup
 *
 * \copyright Copyright (c) 2017 Infineon Technologies AG. All rights reserved.
 *
 * $Date: 2017-05-12 08:52:44
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

#ifndef IFX_CFG_SSW_H_
#define IFX_CFG_SSW_H_

#include "Ifx_Cfg.h"
#include "Ifx_Ssw.h"
//#include "IfxScuCcu.h"

extern void Ifx_Ssw_Mbist(void);
extern void Ifx_Ssw_PLL_Init(void);

#define IFX_CFG_SSW_ENABLE_PMS_INIT       (0U)

#define IFX_CFG_SSW_ENABLE_PMS_INIT_CHECK (0U)

#define IFX_CFG_SSW_ENABLE_LBIST          (0U)

#define IFX_CFG_SSW_ENABLE_MMIC_CHECK     (0U)

#define IFX_CFG_SSW_ENABLE_PLL_INIT       (0U)

#define IFX_CFG_SSW_ENABLE_MBIST          (0U)

#define IFX_CFG_SSW_ENABLE_SMU            (0U)


/* Function calls are not allowed */
#if IFX_CFG_SSW_ENABLE_PMS_INIT == 1
#include "IfxPmsEvr.h"
#define IFX_CFG_SSW_CALLOUT_PMS_INIT()                                     \
    {                                                                      \
        if (IfxPmsEvr_runInitSequence(&IfxPmsEvr_cfgSequenceDefault) == 0) \
        {                                                                  \
            __debug();                                                     \
        }                                                                  \
        else                                                               \
        {                                                                  \
            IFX_CFG_SSW_CALLOUT_PMS_CHECK()                                \
        }                                                                  \
    }
#endif

#if IFX_CFG_SSW_ENABLE_PMS_INIT_CHECK == 1
#define IFX_CFG_SSW_CALLOUT_PMS_CHECK()                                       \
    {                                                                         \
        if (IfxPmsEvr_areInitValuesRight(&IfxPmsEvr_checkRegCfgDefault) == 0) \
        {                                                                     \
            __debug();                                                        \
        }                                                                     \
    }
#endif

#if IFX_CFG_SSW_ENABLE_LBIST == 1
#include "IfxScuLbist.h"
#define IFX_CFG_SSW_CALLOUT_LBIST()                                          \
    {                                                                        \
        if (!IfxScuLbist_isDone())                                           \
        {                                                                    \
            IfxScuLbist_triggerInline(&IfxScuLbist_defaultConfig);           \
        }                                                                    \
        if (IfxScuLbist_evaluateResult(IfxScuLbist_defaultConfig.signature)) \
        {                                                                    \
            __debug();                                                       \
        }                                                                    \
    }
#endif

#if IFX_CFG_SSW_ENABLE_PLL_INIT == 1
#define IFX_CFG_SSW_CALLOUT_PLL_INIT() \
    {                                  \
        Ifx_Ssw_PLL_Init();            \
    }
#endif

#if IFX_CFG_SSW_ENABLE_MBIST == 1
#include "IfxMtu.h"
#define IFX_CFG_SSW_CALLOUT_MBIST() \
    {                               \
        Ifx_Ssw_Mbist();            \
    }
#endif

#if IFX_CFG_SSW_ENABLE_MMIC_CHECK == 1
#define IFX_CFG_SSW_CALLOUT_MMIC_CHECK()
#endif

#if IFX_CFG_SSW_ENABLE_SMU == 1
#define IFX_CFG_SSW_CALLOUT_SMU()
#endif

#endif /* IFX_CFG_SSW_H_ */
