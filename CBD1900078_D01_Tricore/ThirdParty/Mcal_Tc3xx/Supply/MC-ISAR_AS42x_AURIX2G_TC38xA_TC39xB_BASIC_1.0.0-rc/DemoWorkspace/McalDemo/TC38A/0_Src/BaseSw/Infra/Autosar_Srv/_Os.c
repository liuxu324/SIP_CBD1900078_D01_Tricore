/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2018)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Os.c                                                       **
**                                                                            **
**  VERSION      : 2.0.0                                                      **
**                                                                            **
**  DATE         : 2018-03-28                                                 **
**                                                                            **
**  VARIANT      : NA                                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION : This file contains                                          **
**                 OS functionality.                                          **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : Yes                                              **
**                                                                            **
*******************************************************************************/
  /*[cover parentID={DD8F98D3-2665-43fc-A5BF-05EC9E6B7E26}][/cover] */
    /*[cover parentID={A9BBFB04-E13A-42f9-A6F1-FD133B63A7C4}][/cover] */

#include "Os.h"
#if ((APP_SW == TEST_APP) || (APP_SW == DEMO_APP))
#include "Traps.h"
#endif
#include "IFX_Os.h"
#include "McalLib.h"

extern volatile uint32 SFR_Return_Value;


void TRUSTED_Mcal_WritePeripEndInitProtReg
                     ( volatile void* const RegAddress, const uint32 DataValue)
{
  /*function to enter supervisory mode*/
  /*functionality for WritePeripEndInitProtReg*/
#if ((APP_SW == TEST_APP) || (APP_SW == DEMO_APP))
  SYSCALL(MCAL_CALL_TIN_WRITE_PERIP_ENDINIT);
  UNUSED_PARAMETER(RegAddress);
  UNUSED_PARAMETER(DataValue);
#endif
}
void TRUSTED_Mcal_WriteSafetyEndInitProtReg
                      ( volatile void* const RegAddress, const uint32 DataValue)
{
  /*function to enter supervisory mode*/
  /*functionality for WriteSafetyEndInitProtReg*/
#if ((APP_SW == TEST_APP) || (APP_SW == DEMO_APP))
  SYSCALL(MCAL_CALL_TIN_WRITE_SAFETY_ENDINIT);
  UNUSED_PARAMETER(RegAddress);
  UNUSED_PARAMETER(DataValue);
#endif
}

void TRUSTED_Mcal_WriteSafetyEndInitProtRegMask
                     (volatile void* const RegAdd,const uint32 Data,uint32 Mask)
{
  /*function to enter supervisory mode*/
  /*functionality for WriteSafetyEndInitProtReg*/
#if ((APP_SW == TEST_APP) || (APP_SW == DEMO_APP))
    SYSCALL(MCAL_CALL_TIN_WRITE_SAFETY_ENDINIT_MASK);
    UNUSED_PARAMETER(RegAdd);
    UNUSED_PARAMETER(Data);
    UNUSED_PARAMETER(Mask);
#endif
}
void TRUSTED_Mcal_WriteCpuEndInitProtReg
                                (volatile void* const RegAdd,const uint32 Data)
{
  /*function to enter supervisory mode*/
  /*functionality for WriteCpuEndInitProtReg*/
#if ((APP_SW == TEST_APP) || (APP_SW == DEMO_APP))
    SYSCALL(MCAL_CALL_TIN_WRITE_CPU_ENDINIT);
    UNUSED_PARAMETER(RegAdd);
    UNUSED_PARAMETER(Data);
#endif
}
void TRUSTED_Mcal_SetBitAtomic
                        (volatile void* DataPtr,uint8 BitPos,uint8 BitLen,uint32 Data)
{
  /*function to enter supervisory mode*/
  /*functionality for SetBitAtomic*/
#if ((APP_SW == TEST_APP) || (APP_SW == DEMO_APP))
    SYSCALL(MCAL_CALL_TIN_SET_BIT_ATOMIC);
    UNUSED_PARAMETER(DataPtr);
    UNUSED_PARAMETER(BitPos);
    UNUSED_PARAMETER(BitLen);
    UNUSED_PARAMETER(Data);
#endif
}
void osWritePeripheral32
                     (uint32 Area, volatile void* Address,uint32 value)
{
  /*function to enter supervisory mode*/
  /*functionality for OS_WritePeripheral32*/
#if ((APP_SW == TEST_APP) || (APP_SW == DEMO_APP))
    SYSCALL(MCAL_TIN_CALL_WRITE32);
    UNUSED_PARAMETER(Area);
    UNUSED_PARAMETER(Address);
    UNUSED_PARAMETER(value);
#endif
}
uint32 osReadPeripheral32
                        (uint32 Area, volatile void* Address)
{
  /*function to enter supervisory mode*/
  /*functionality for OS_ReadPeripheral32*/
  volatile uint32 value =0U;
#if ((APP_SW == TEST_APP) || (APP_SW == DEMO_APP))
  SYSCALL(MCAL_TIN_CALL_READ32);
  value = SFR_Return_Value;
  UNUSED_PARAMETER(Area);
  UNUSED_PARAMETER(Address);
#endif
  return value;

}
void osModifyPeripheral32
  (uint32 Area, volatile void* Address,uint32 clearmask,uint32 setmask)
{
  /*function to enter supervisory mode*/
  /*functionality for OS_ModifyPeripheral32*/
#if ((APP_SW == TEST_APP) || (APP_SW == DEMO_APP))
  SYSCALL(MCAL_TIN_CALL_MODIFY32);
  UNUSED_PARAMETER(Area);
  UNUSED_PARAMETER(Address);
  UNUSED_PARAMETER(clearmask);
  UNUSED_PARAMETER(setmask);
#endif
}

