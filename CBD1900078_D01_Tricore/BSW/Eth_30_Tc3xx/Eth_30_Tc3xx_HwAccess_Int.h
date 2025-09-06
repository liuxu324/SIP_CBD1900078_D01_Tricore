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
/**        \file  Eth_30_Tc3xx_HwAccess_Int.h
 *        \brief  Register access abstraction of Ethernet driver
 *
 *      \details  Abstraction of Ethernet driver register access
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#if !defined (ETH_30_TC3XX_REG_ACCESS_INT_H)
# define ETH_30_TC3XX_REG_ACCESS_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_GeneralTypes.h"
# include "Eth_30_Tc3xx_LL_Regs.h"
# include "Eth_30_Tc3xx_Lcfg.h"
# if (ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API == STD_ON)
#  include "Os.h"
# endif /* ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API */

/**********************************************************************************************************************
 *  GLOBAL TYPES
 *********************************************************************************************************************/
/*! Width of a register */
typedef uint32                                                     Eth_30_Tc3xx_RegWidthType;
/*! Offset within the register space of the Ethernet controller */
typedef uint16                                                     Eth_30_Tc3xx_RegOffsetType;
/*! Register access type */
typedef volatile Eth_30_Tc3xx_RegWidthType                          Eth_30_Tc3xx_RegAccessType;
/*! Pointer to a register */
typedef P2VAR(Eth_30_Tc3xx_RegAccessType, AUTOMATIC, MSR_REGSPACE)  Eth_30_Tc3xx_RegPtrType;

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# if !defined (ETH_30_TC3XX_REG_ACCESS_INLINE)
#  define ETH_30_TC3XX_REG_ACCESS_INLINE LOCAL_INLINE
# endif /* ETH_30_TC3XX_REG_ACCESS_INLINE */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetRegBaseAddress
 *********************************************************************************************************************/
/*! \brief       Retrieves the register base address of the Ethernet controller
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *  \return      Register base address
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(uint32, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRegBaseAddress(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_CreateRegPtr
 *********************************************************************************************************************/
/*! \brief       Creates a pointer to the register addressed by the offset into the Ethernet controllers register space
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \return      Pointer to the register addressed
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(Eth_30_Tc3xx_RegPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_CreateRegPtr(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_Write
 *********************************************************************************************************************/
/*! \brief       Writes the given value to the addressed register
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \param[in]   regValue   Value to be written to the register
 *  \context     ANY
 *  \reentrant   TRUE for different registers
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_Write(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  regValue);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_Write_Protected
 *********************************************************************************************************************/
/*! \brief       Writes the given value to the addressed register by using protected access method if necessary
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \param[in]   regValue   Value to be written to the register
 *  \context     ANY
 *  \reentrant   TRUE for different registers
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_Write_Protected(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  regValue);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_Read
 *********************************************************************************************************************/
/*! \brief       Reads the value of the addressed register
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \return      Value of the register
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(Eth_30_Tc3xx_RegWidthType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_Read(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_Read_Protected
 *********************************************************************************************************************/
/*! \brief       Reads the value of the addressed register by using protected access method if necessary
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \return      Value of the register
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(Eth_30_Tc3xx_RegWidthType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_Read_Protected(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_ReadBits
 *********************************************************************************************************************/
/*! \brief       Reads the value of the addressed register and applies bit mask
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \param[in]   bitMask    Bit mask to apply on register value
 *  \return      Value of the register
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(Eth_30_Tc3xx_RegWidthType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_ReadBits(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType bitMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_ReadBits_Protected
 *********************************************************************************************************************/
/*! \brief       Reads the value of the addressed register by using protected access method if necessary and applies bit mask
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \param[in]   bitMask    Bit mask to apply on register value
 *  \return      Value of the register
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(Eth_30_Tc3xx_RegWidthType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_ReadBits_Protected(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType bitMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_SetBitMask
 *********************************************************************************************************************/
/*! \brief       Sets the bits given by the bit mask in the addressed register
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \param[in]   bitMask    Bits to be set
 *  \context     ANY
 *  \reentrant   TRUE for different registers
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_SetBitMask(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_SetBitMask_Protected
 *********************************************************************************************************************/
/*! \brief       Sets the bits given by the bit mask in the addressed register by using protected access method if necessary
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \param[in]   bitMask    Bits to be set
 *  \context     ANY
 *  \reentrant   TRUE for different registers
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_SetBitMask_Protected(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_ClearBitMask
 *********************************************************************************************************************/
/*! \brief       Clears the bits given by the bit mask in the addressed register
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \param[in]   bitMask    Bits to be cleared
 *  \context     ANY
 *  \reentrant   TRUE for different registers
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_ClearBitMask(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_ClearBitMask_Protected
 *********************************************************************************************************************/
/*! \brief       Clears the bits given by the bit mask in the addressed register by using protected access method if necessary
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \param[in]   bitMask    Bits to be cleared
 *  \context     ANY
 *  \reentrant   TRUE for different registers
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_ClearBitMask_Protected(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_IsBitMaskSet
 *********************************************************************************************************************/
/*! \brief       Checks if all of the bits given by the bit mask are set in the addressed register
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \param[in]   bitMask    Bits to be checked for being set
 *  \return      FALSE - at least one bit of the bit mask isn't set in the register
 *  \return      TRUE - all bits of the bit mask are set in the register
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_IsBitMaskSet(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_IsBitMaskSet_Protected
 *********************************************************************************************************************/
/*! \brief       Checks if all of the bits given by the bit mask are set in the addressed register by using protected access method if necessary
 *  \details     -
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *  \param[in]   regOffset  Offset in bytes into the Ethernet controllers register space
 *  \param[in]   bitMask    Bits to be checked for being set
 *  \return      FALSE - at least one bit of the bit mask isn't set in the register
 *  \return      TRUE - all bits of the bit mask are set in the register
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_IsBitMaskSet_Protected(
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetRegBaseAddress
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(uint32, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRegBaseAddress( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx)
{
  return Eth_30_Tc3xx_RegBaseAddrRAM[ctrlIdx];
} /* Eth_30_Tc3xx_GetRegBaseAddress() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_CreateRegPtr
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(Eth_30_Tc3xx_RegPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_CreateRegPtr( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset)
{
  return (Eth_30_Tc3xx_RegPtrType)(Eth_30_Tc3xx_GetRegBaseAddress(ctrlIdx) + regOffset); /* PRQA S 0303 */ /* MD_Eth_30_Tc3xx_0303 */
} /* Eth_30_Tc3xx_CreateRegPtr() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_Write
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_Write( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  regValue)
{
  Eth_30_Tc3xx_RegPtrType reg = Eth_30_Tc3xx_CreateRegPtr(ctrlIdx, regOffset);
  (*reg) = regValue;
} /* Eth_30_Tc3xx_Reg_Write() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_Write_Protected
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_Write_Protected( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  regValue)
{
#if (ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API == STD_ON)
  osWritePeripheral32(Eth_30_Tc3xx_Ctrl2ProtectedAreaIdMap[ctrlIdx], (uint32)(Eth_30_Tc3xx_GetRegBaseAddress(ctrlIdx) + regOffset), regValue);
#else
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffset, regValue);
#endif /* ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API */
} /* Eth_30_Tc3xx_Reg_Write_Protected() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_Read
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(Eth_30_Tc3xx_RegWidthType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_Read( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset)
{
  Eth_30_Tc3xx_RegPtrType reg = Eth_30_Tc3xx_CreateRegPtr(ctrlIdx, regOffset);
  return (*reg);
} /* Eth_30_Tc3xx_Reg_Read() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_Read_Protected
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(Eth_30_Tc3xx_RegWidthType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_Read_Protected( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset)
{
#if (ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API == STD_ON)
  return osReadPeripheral32(Eth_30_Tc3xx_Ctrl2ProtectedAreaIdMap[ctrlIdx], (uint32)(Eth_30_Tc3xx_GetRegBaseAddress(ctrlIdx) + regOffset));
#else
  return Eth_30_Tc3xx_Reg_Read(ctrlIdx, regOffset);
#endif /* ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API */
} /* Eth_30_Tc3xx_Reg_Read_Protected() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_ReadBits
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(Eth_30_Tc3xx_RegWidthType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_ReadBits( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType bitMask)
{
  return (Eth_30_Tc3xx_Reg_Read(ctrlIdx, regOffset) & bitMask);
} /* Eth_30_Tc3xx_Reg_ReadBits() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_ReadBits_Protected
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(Eth_30_Tc3xx_RegWidthType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_ReadBits_Protected( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType bitMask)
{
#if (ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API == STD_ON)
  return (Eth_30_Tc3xx_Reg_Read_Protected(ctrlIdx, regOffset) & bitMask);
#else
  return Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, regOffset, bitMask);
#endif /* ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API */
} /* Eth_30_Tc3xx_Reg_ReadBits_Protected() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_SetBitMask
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_SetBitMask( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask)
{
  Eth_30_Tc3xx_RegPtrType reg = Eth_30_Tc3xx_CreateRegPtr(ctrlIdx, regOffset);
  (*reg) |= bitMask;
} /* Eth_30_Tc3xx_Reg_SetBitMask() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_SetBitMask_Protected
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_SetBitMask_Protected( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask)
{
#if (ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API == STD_ON)
  osModifyPeripheral32(Eth_30_Tc3xx_Ctrl2ProtectedAreaIdMap[ctrlIdx], (Eth_30_Tc3xx_RegWidthType)(Eth_30_Tc3xx_GetRegBaseAddress(ctrlIdx) + regOffset),
                       (uint32)0xFFFFFFFFul, (uint32)bitMask);
#else
  Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, regOffset, bitMask);

#endif /* ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API */
} /* Eth_30_Tc3xx_Reg_SetBitMask_Protected() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_ClearBitMask
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_ClearBitMask( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask)
{
  Eth_30_Tc3xx_RegPtrType reg = Eth_30_Tc3xx_CreateRegPtr(ctrlIdx, regOffset);

  (*reg) = (*reg) & ~bitMask;
} /* Eth_30_Tc3xx_Reg_ClearBitMask() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_ClearBitMask_Protected
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_ClearBitMask_Protected( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask)
{
#if (ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API == STD_ON)
  osModifyPeripheral32(Eth_30_Tc3xx_Ctrl2ProtectedAreaIdMap[ctrlIdx], (uint32)(Eth_30_Tc3xx_GetRegBaseAddress(ctrlIdx) + regOffset),
                       ~((uint32)bitMask), (uint32)0u);
#else
  Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, regOffset, bitMask);
#endif /* ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API */
} /* Eth_30_Tc3xx_Reg_ClearBitMask_Protected() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_IsBitMaskSet
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_IsBitMaskSet( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask)
{
  boolean               result = FALSE;
  Eth_30_Tc3xx_RegPtrType reg    = Eth_30_Tc3xx_CreateRegPtr(ctrlIdx, regOffset);

  if( ((*reg) & bitMask) == bitMask )
  {
    result = TRUE;
  }

  return result;
} /* Eth_30_Tc3xx_Reg_IsBitMaskSet() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Reg_IsBitMaskSet_Protected
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_REG_ACCESS_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Reg_IsBitMaskSet_Protected( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8                     ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType regOffset,
  Eth_30_Tc3xx_RegWidthType  bitMask)
{
#if (ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API == STD_ON)
  boolean               result = FALSE;
  Eth_30_Tc3xx_RegWidthType reg = osReadPeripheral32(Eth_30_Tc3xx_Ctrl2ProtectedAreaIdMap[ctrlIdx],
                                                     (uint32)(Eth_30_Tc3xx_GetRegBaseAddress(ctrlIdx) + regOffset));

  if( (reg & bitMask) == bitMask )
  {
    result = TRUE;
  }

  return result;
#else
  return Eth_30_Tc3xx_Reg_IsBitMaskSet(ctrlIdx, regOffset, bitMask);
#endif /* ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API */
} /* Eth_30_Tc3xx_Reg_IsBitMaskSet_Protected() */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# endif /* ETH_30_TC3XX_REG_ACCESS_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_HwAccess_Int.h
 *********************************************************************************************************************/

