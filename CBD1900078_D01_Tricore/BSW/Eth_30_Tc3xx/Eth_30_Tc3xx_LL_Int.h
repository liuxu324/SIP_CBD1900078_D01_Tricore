/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  Eth_30_Tc3xx_LL_Int.h
 *        \brief  Lower layer private header file
 *
 *      \details  Private data of lower layer part of component.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the version history in Eth_30_Tc3xx_LL.h
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the newest version in Eth_30_Tc3xx_LL.h
 *********************************************************************************************************************/

#if !defined( ETH_30_TC3XX_LL_INT_H )
# define      ETH_30_TC3XX_LL_INT_H

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* ISR related */
# define ETH_30_TC3XX_TXQ0                                    (0x0u)
# define ETH_30_TC3XX_RXQ0                                    (0x0u)
# define ETH_30_TC3XX_TXQ1                                    (0x1u)
# define ETH_30_TC3XX_RXQ1                                    (0x1u)
# define ETH_30_TC3XX_TXQ2                                    (0x2u)
# define ETH_30_TC3XX_RXQ2                                    (0x2u)
# define ETH_30_TC3XX_TXQ3                                    (0x3u)
# define ETH_30_TC3XX_RXQ3                                    (0x3u)

# define ETH_30_TC3XX_NSEC_PER_SEC                    (1000000000ul)

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Appl_UnlockEndinit()
 *********************************************************************************************************************/
/*! \brief       Appl_UnlockEndinit
 *  \details     -
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
FUNC(void, ETH_30_TC3XX_APPL_CODE) Appl_UnlockEndinit(void);

/**********************************************************************************************************************
 *  Appl_LockEndinit()
 *********************************************************************************************************************/
/*! \brief       Appl_LockEndinit
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
FUNC(void, ETH_30_TC3XX_APPL_CODE) Appl_LockEndinit(void);

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ETH_30_TC3XX_LL_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_Int.h
 *********************************************************************************************************************/
 
