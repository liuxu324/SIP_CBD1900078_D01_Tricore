[!/*****************************************************************************
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
**  FILENAME  : Irq_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 2.2.0                                                         **
**                                                                            **
**  DATE      : 2018-07-16                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Irq.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID= ]                                         **
**                                                                            **
**  DESCRIPTION  : Code template header file for Irq Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : na                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*****************************************************************************/!]
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
**  FILENAME  : Irq_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 2.2.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                                      **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                                          ** 
**                                                                            **
**  BSW MODULE DECRIPTION : Irq.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Irq configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : na                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#ifndef IRQ_CFG_H 
#define IRQ_CFG_H 
[!//
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Irq')[1]"!][!//
[!//
[!//
[!VAR "Readbit" = "num:i(0)"!][!//
[!VAR "ErrorFlag" = "num:i(0)"!][!//
[!VAR "Variable0" = "num:i(0)"!][!//
[!VAR "Variable1" = "num:i(0)"!][!//
[!VAR "Variable2" = "num:i(0)"!][!//
[!VAR "Variable3" = "num:i(0)"!][!//
[!VAR "Variable4" = "num:i(0)"!][!//
[!VAR "Variable5" = "num:i(0)"!][!//
[!VAR "Variable6" = "num:i(0)"!][!//
[!VAR "Variable7" = "num:i(0)"!][!//
[!VAR "ErrorFlagDma" = "num:i(0)"!][!//
[!VAR "Variable0Dma" = "num:i(0)"!][!//
[!VAR "Variable1Dma" = "num:i(0)"!][!//
[!VAR "Variable2Dma" = "num:i(0)"!][!//
[!VAR "Variable3Dma" = "num:i(0)"!][!//
[!VAR "Variable4Dma" = "num:i(0)"!][!//
[!VAR "DmaMaxPrio" = "num:i(ecu:get('Irq.DmaMaxPrio'))"!][!//

[!//
[!/*****************************************************************************
  MACRO: CG_PriorityCheck 
  
  Macro to determine whether the configured priorities are different or not
  
  Input Parameters:
  Givenno - Value of the node (SrnId: Priority Number)
  cont - Module Name
*****************************************************************************/!]
[!MACRO "CG_PriorityCheck", "Givenno" = "","cont" = ""!][!//
[!IF "($Givenno != num:i(0))"!][!//
[!VAR "Givenno1" = "num:i($Givenno div num:i(32))"!][!//
[!VAR "Givenno2" = "num:i($Givenno mod num:i(32))"!][!//
[!IF "($Givenno1 = num:i(0))"!][!//
[!IF "bit:getbit($Variable0,$Givenno2) != 'true'"!][!//
[!VAR "Variable0" = "bit:bitset($Variable0,$Givenno2)"!][!//
[!ELSE!][!//
[!VAR "ErrorFlag" = "num:i(1)"!]
[!ENDIF!][!//			
[!ELSEIF "($Givenno1 = num:i(1))"!][!//
[!IF "bit:getbit($Variable1,$Givenno2) != 'true'"!][!//
[!VAR "Variable1" = "bit:bitset($Variable1, $Givenno2)"!][!//	
[!ELSE!][!//
[!VAR "ErrorFlag" = "num:i(1)"!][!//
[!ENDIF!][!//
[!ELSEIF "($Givenno1 = num:i(2))"!][!//
[!IF "bit:getbit($Variable2,$Givenno2) != 'true'"!][!//
[!VAR "Variable2" = "bit:bitset($Variable2, $Givenno2)"!][!//	
[!ELSE!][!//
[!VAR "ErrorFlag" = "num:i(1)"!][!//
[!ENDIF!][!//
[!ELSEIF "($Givenno1 = num:i(3))"!][!//
[!IF "bit:getbit($Variable3,$Givenno2) != 'true'"!][!//
[!VAR "Variable3" = "bit:bitset($Variable3, $Givenno2)"!][!//	
[!ELSE!][!//
[!VAR "ErrorFlag" = "num:i(1)"!][!//
[!ENDIF!][!//
[!ELSEIF "($Givenno1 = num:i(4))"!][!//
[!IF "bit:getbit($Variable4,$Givenno2) != 'true'"!][!//
[!VAR "Variable4" = "bit:bitset($Variable4, $Givenno2)"!][!//	
[!ELSE!][!//
[!VAR "ErrorFlag" = "num:i(1)"!][!//
[!ENDIF!][!//
[!ELSEIF "($Givenno1 = num:i(5))"!][!//
[!IF "bit:getbit($Variable5,$Givenno2) != 'true'"!][!//
[!VAR "Variable5" = "bit:bitset($Variable5, $Givenno2)"!][!//	
[!ELSE!][!//
[!VAR "ErrorFlag" = "num:i(1)"!][!//
[!ENDIF!][!//
[!ELSEIF "($Givenno1 = num:i(6))"!][!//
[!IF "bit:getbit($Variable6,$Givenno2) != 'true'"!][!//
[!VAR "Variable6" = "bit:bitset($Variable6, $Givenno2)"!][!//	
[!ELSE!][!//
[!VAR "ErrorFlag" = "num:i(1)"!][!//
[!ENDIF!][!//
[!ELSEIF "($Givenno1 = num:i(7))"!][!//
[!IF "bit:getbit($Variable7,$Givenno2) != 'true'"!][!//
[!VAR "Variable7" = "bit:bitset($Variable7, $Givenno2)"!][!//	
[!ELSE!][!//
[!VAR "ErrorFlag" = "num:i(1)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "($ErrorFlag != num:i(0))"!][!//
[!ERROR!][!//
Same Priority is configured in two places, check [!"$cont"!] and some other container.
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDMACRO!][!//

[!//
[!/*****************************************************************************
  MACRO: CG_PriorityCheckDma 
  
  Macro to determine whether the configured priorities are different or not
  
  Input Parameters:
  Givenno - Value of the node (SrnId: Priority Number)
  cont - Module Name
*****************************************************************************/!]
[!MACRO "CG_PriorityCheckDma", "Givenno" = "","cont" = ""!][!//
[!IF "($Givenno != num:i(0))"!][!//
[!VAR "Givenno1" = "num:i($Givenno div num:i(32))"!][!//
[!VAR "Givenno2" = "num:i($Givenno mod num:i(32))"!][!//
[!IF "($Givenno1 = num:i(0))"!][!//
[!IF "bit:getbit($Variable0Dma,$Givenno2) != 'true'"!][!//
[!VAR "Variable0Dma" = "bit:bitset($Variable0Dma,$Givenno2)"!][!//
[!ELSE!][!//
[!VAR "ErrorFlagDma" = "num:i(1)"!]
[!ENDIF!][!//			
[!ELSEIF "($Givenno1 = num:i(1))"!][!//
[!IF "bit:getbit($Variable1Dma,$Givenno2) != 'true'"!][!//
[!VAR "Variable1Dma" = "bit:bitset($Variable1Dma, $Givenno2)"!][!//	
[!ELSE!][!//
[!VAR "ErrorFlagDma" = "num:i(1)"!][!//
[!ENDIF!][!//
[!ELSEIF "($Givenno1 = num:i(2))"!][!//
[!IF "bit:getbit($Variable2Dma,$Givenno2) != 'true'"!][!//
[!VAR "Variable2Dma" = "bit:bitset($Variable2Dma, $Givenno2)"!][!//	
[!ELSE!][!//
[!VAR "ErrorFlagDma" = "num:i(1)"!][!//
[!ENDIF!][!//
[!ELSEIF "($Givenno1 = num:i(3))"!][!//
[!IF "bit:getbit($Variable3Dma,$Givenno2) != 'true'"!][!//
[!VAR "Variable3Dma" = "bit:bitset($Variable3Dma, $Givenno2)"!][!//	
[!ELSE!][!//
[!VAR "ErrorFlagDma" = "num:i(1)"!][!//
[!ENDIF!][!//
[!ELSEIF "($Givenno1 = num:i(4))"!][!//
[!IF "bit:getbit($Variable4Dma,$Givenno2) != 'true'"!][!//
[!VAR "Variable4Dma" = "bit:bitset($Variable4Dma, $Givenno2)"!][!//	
[!ELSE!][!//
[!VAR "ErrorFlagDma" = "num:i(1)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "($ErrorFlagDma != num:i(0))"!][!//
[!ERROR!][!//
Same Priority is configured in two places, check [!"$cont"!] and some other container.
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDMACRO!][!//
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/************************* interrupt CATEGORY *********************************/
#define IRQ_CAT1                    (0)
#define IRQ_CAT2                    (1)
/************************* interrupt Type of Service **************************/
#define IRQ_TOS_CPU0                (0x0000)
#define IRQ_TOS_CPU1                (0x1000)
#define IRQ_TOS_CPU2                (0x1800)
#define IRQ_TOS_CPU3                (0x2000)
#define IRQ_TOS_CPU4                (0x2800)
#define IRQ_TOS_CPU5                (0x3000)
#define IRQ_TOS_DMA                 (0x0800)
/*
                     Container : IrqGeneralConfiguration
*/

/*
Configuration: IRQ_OS_ENABLE 
- if TRUE, OSEK RTOS is used, 
  Both CAT1 and CAT2 interrupt categories can be configured 
  Any CAT2 interrupt priority should be greater than CAT1 interrupt priority
- if FALSE,OSEK RTOS is not used
  Only CAT1 interrupt category can be configured 
*/

#define IRQ_OSEK_ENABLE  [!IF "IrqGeneral/IrqOsekEnable = 'true'"!][!//
           (STD_ON)[!//
[!ELSE!][!//
           (STD_OFF)[!//
[!ENDIF!]

[!NOCODE!][!//
[!VAR "MIN_CAT1_LEVEL" = "num:i(255)"!][!//
[!VAR "MAX_CAT2_LEVEL" = "num:i(0)"!][!//
[!VAR "PREVIOUS"       = "num:i(0)"!][!// 
[!ENDNOCODE!][!//
	  

/*
                     Container : IrqGPTinterruptConfiguration
*/
[!IF "num:i(count(IrqGPT120Config/*)) = 1"!][!//
[!IF "contains( ecu:get('Irq.GPT12Available'), 'IrqGPT120' )"!][!//
/* GPT120 interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGPT120Config/*[1]/IrqGPT120CatConfig/*))"!][!//
[!IF "($SrnId <= 1)"!][!//
#define IRQ_GPT120_CARPEL_CAT       (IRQ_[!"IrqGPT120Config/*[1]/IrqGPT120CatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ELSE!][!//
#define IRQ_GPT120_T[!"num:i($SrnId)"!]_CAT           (IRQ_[!"IrqGPT120Config/*[1]/IrqGPT120CatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDIF!][!//
[!ENDFOR!][!//

/*  GPT120 interrupt Priority setting  */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGPT120Config/*[1]/IrqGPT120PrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqGPT120Config/*[1]/IrqGPT120PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGPT120Config/*[1]/IrqGPT120TosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqGPT120Config/*[1]/IrqGPT120PrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!IF "($SrnId <= 1)"!][!//
#define IRQ_GPT120_CARPEL_PRIO      [!"num:inttohex(IrqGPT120Config/*[1]/IrqGPT120PrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!ELSE!][!//
#define IRQ_GPT120_T[!"num:i($SrnId)"!]_PRIO          [!"num:inttohex(IrqGPT120Config/*[1]/IrqGPT120PrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!ENDIF!][!//
[!NOCODE!][!//
[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OS_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqGPT120Config/*[1]/IrqGPT120PrioConfig/*[num:i($SrnId)])"!][!//    
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqGPT120Config/*[1]/IrqGPT120CatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OS_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OS_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of GPT120 interrupt Priority Setting for loop */!][!//

/* GPT120 interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGPT120Config/*[1]/IrqGPT120TosConfig/*))"!][!//
[!IF "($SrnId <= 1)"!][!//
#define IRQ_GPT120_CARPEL_TOS       (IRQ_TOS_[!"IrqGPT120Config/*[1]/IrqGPT120TosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ELSE!][!//
#define IRQ_GPT120_T[!"num:i($SrnId)"!]_TOS           (IRQ_TOS_[!"IrqGPT120Config/*[1]/IrqGPT120TosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDIF!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqGPT120Config/*[1]/IrqGPT120PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGPT120Config/*[1]/IrqGPT120TosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDIF!][!//[!/* End of GPT interrupt */!] 

[!VAR "IrqQspiExist" = "'STD_OFF'"!][!//
[!IF "num:i(count(IrqQSPIConfig/*)) = 1"!][!//
/*
                     Container : IrqQspi interruptConfiguration
*/
[!VAR "IrqQspiExist" = "'STD_ON'"!][!//
[!//
/* Qspi Tx interrupt Category Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqQSPIConfig/*[1]/IrqQspiCatConfig/IrqQspiTxCatConfig/*))"!][!//
#define IRQ_QSPI[!"num:i($SrnId - 1)"!]_TX_CAT            (IRQ_[!"IrqQSPIConfig/*[1]/IrqQspiCatConfig/IrqQspiTxCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/* Qspi Tx interrupt Priority Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiTxPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiTxPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqQSPIConfig/*[1]/IrqQspiTosConfig/IrqQspiTxTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiTxPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_QSPI[!"num:i($SrnId - 1)"!]_TX_PRIO           [!"num:inttohex(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiTxPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//
[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OS_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//

[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiTxPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqQSPIConfig/*[1]/IrqQspiCatConfig/IrqQspiTxCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OS_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
	   Portnewa[!"$MIN_CAT1_LEVEL"!][!//
	   Portnewa[!"$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OS_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of QSPITX interrupt Priority Setting for loop */!][!//

/* Qspi Tx interrupt type of service Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqQSPIConfig/*[1]/IrqQspiTosConfig/IrqQspiTxTosConfig/*))"!][!//
#define IRQ_QSPI[!"num:i($SrnId - 1)"!]_TX_TOS            (IRQ_TOS_[!"IrqQSPIConfig/*[1]/IrqQspiTosConfig/IrqQspiTxTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiTxPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqQSPIConfig/*[1]/IrqQspiTosConfig/IrqQspiTxTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//

/* Qspi Rx interrupt Category Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqQSPIConfig/*[1]/IrqQspiCatConfig/IrqQspiRxCatConfig/*))"!][!//
#define IRQ_QSPI[!"num:i($SrnId - 1)"!]_RX_CAT            (IRQ_[!"IrqQSPIConfig/*[1]/IrqQspiCatConfig/IrqQspiRxCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/* Qspi Rx interrupt Priority Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiRxPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiRxPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqQSPIConfig/*[1]/IrqQspiTosConfig/IrqQspiRxTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiRxPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_QSPI[!"num:i($SrnId - 1)"!]_RX_PRIO           [!"num:inttohex(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiRxPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//
[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OS_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//

[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiRxPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqQSPIConfig/*[1]/IrqQspiCatConfig/IrqQspiRxCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OS_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OS_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of QSPIRX interrupt Priority Setting for loop */!][!//

/* Qspi Rx interrupt type of service Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqQSPIConfig/*[1]/IrqQspiTosConfig/IrqQspiRxTosConfig/*))"!][!//
#define IRQ_QSPI[!"num:i($SrnId - 1)"!]_RX_TOS            (IRQ_TOS_[!"IrqQSPIConfig/*[1]/IrqQspiTosConfig/IrqQspiRxTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiRxPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqQSPIConfig/*[1]/IrqQspiTosConfig/IrqQspiRxTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//

/* Qspi Err interrupt Category Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqQSPIConfig/*[1]/IrqQspiCatConfig/IrqQspiErrCatConfig/*))"!][!//
#define IRQ_QSPI[!"num:i($SrnId - 1)"!]_ERR_CAT           (IRQ_[!"IrqQSPIConfig/*[1]/IrqQspiCatConfig/IrqQspiErrCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/* Qspi Err interrupt Priority Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiErrPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiErrPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqQSPIConfig/*[1]/IrqQspiTosConfig/IrqQspiErrTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiErrPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_QSPI[!"num:i($SrnId - 1)"!]_ERR_PRIO          [!"num:inttohex(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiErrPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//
[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OS_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//

[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiErrPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqQSPIConfig/*[1]/IrqQspiCatConfig/IrqQspiErrCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OS_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OS_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of QSPIERR interrupt Priority Setting for loop */!][!//

/* Qspi Err interrupt type of service Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqQSPIConfig/*[1]/IrqQspiTosConfig/IrqQspiErrTosConfig/*))"!][!//
#define IRQ_QSPI[!"num:i($SrnId - 1)"!]_ERR_TOS           (IRQ_TOS_[!"IrqQSPIConfig/*[1]/IrqQspiTosConfig/IrqQspiErrTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiErrPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqQSPIConfig/*[1]/IrqQspiTosConfig/IrqQspiErrTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//

/* Qspi PT interrupt Category Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqQSPIConfig/*[1]/IrqQspiCatConfig/IrqQspiPTCatConfig/*))"!][!//
#define IRQ_QSPI[!"num:i($SrnId - 1)"!]_PT_CAT            (IRQ_[!"IrqQSPIConfig/*[1]/IrqQspiCatConfig/IrqQspiPTCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/* Qspi PT interrupt Priority Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiPTPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiPTPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqQSPIConfig/*[1]/IrqQspiTosConfig/IrqQspiPTTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiPTPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_QSPI[!"num:i($SrnId - 1)"!]_PT_PRIO           [!"num:inttohex(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiPTPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//
[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OS_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//

[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiPTPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqQSPIConfig/*[1]/IrqQspiCatConfig/IrqQspiPTCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OS_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OS_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of QSPIPT interrupt Priority Setting for loop */!][!//

/* Qspi PT interrupt type of service Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqQSPIConfig/*[1]/IrqQspiTosConfig/IrqQspiPTTosConfig/*))"!][!//
#define IRQ_QSPI[!"num:i($SrnId - 1)"!]_PT_TOS            (IRQ_TOS_[!"IrqQSPIConfig/*[1]/IrqQspiTosConfig/IrqQspiPTTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiPTPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqQSPIConfig/*[1]/IrqQspiTosConfig/IrqQspiPTTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//

/* Qspi HC interrupt Category Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqQSPIConfig/*[1]/IrqQspiCatConfig/IrqQspiHCCatConfig/*))"!][!//
[!VAR "Nm" = "num:i(substring-before(substring-after(node:name(IrqQSPIConfig/*[1]/IrqQspiCatConfig/IrqQspiHCCatConfig/*[num:i($SrnId)]),'IrqQspi'),'HCCat'))"!][!//
#define IRQ_QSPI[!"$Nm"!]_HC_CAT            (IRQ_[!"IrqQSPIConfig/*[1]/IrqQspiCatConfig/IrqQspiHCCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/* Qspi HC interrupt Priority Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiHCPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiHCPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqQSPIConfig/*[1]/IrqQspiTosConfig/IrqQspiHCTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiHCPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!VAR "Nm" = "num:i(substring-before(substring-after(node:name(IrqQSPIConfig/*[1]/IrqQspiCatConfig/IrqQspiHCCatConfig/*[num:i($SrnId)]),'IrqQspi'),'HCCat'))"!][!//
#define IRQ_QSPI[!"$Nm"!]_HC_PRIO           [!"num:inttohex(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiHCPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//
[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OS_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//

[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiHCPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqQSPIConfig/*[1]/IrqQspiCatConfig/IrqQspiHCCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OS_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OS_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of QSPIHC interrupt Priority Setting for loop */!][!//

/* Qspi HC interrupt type of service Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqQSPIConfig/*[1]/IrqQspiTosConfig/IrqQspiHCTosConfig/*))"!][!//
[!VAR "Nm" = "num:i(substring-before(substring-after(node:name(IrqQSPIConfig/*[1]/IrqQspiCatConfig/IrqQspiHCCatConfig/*[num:i($SrnId)]),'IrqQspi'),'HCCat'))"!][!//
#define IRQ_QSPI[!"$Nm"!]_HC_TOS            (IRQ_TOS_[!"IrqQSPIConfig/*[1]/IrqQspiTosConfig/IrqQspiHCTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiHCPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqQSPIConfig/*[1]/IrqQspiTosConfig/IrqQspiHCTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//

/* Qspi UD interrupt Category Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqQSPIConfig/*[1]/IrqQspiCatConfig/IrqQspiUDCatConfig/*))"!][!//
#define IRQ_QSPI[!"num:i($SrnId - 1)"!]_UD_CAT            (IRQ_[!"IrqQSPIConfig/*[1]/IrqQspiCatConfig/IrqQspiUDCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/* Qspi UD interrupt Priority Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiUDPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiUDPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqQSPIConfig/*[1]/IrqQspiTosConfig/IrqQspiUDTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiUDPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_QSPI[!"num:i($SrnId - 1)"!]_UD_PRIO           [!"num:inttohex(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiUDPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//
[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OS_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//

[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiUDPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqQSPIConfig/*[1]/IrqQspiCatConfig/IrqQspiUDCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OS_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OS_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of QSPIUD interrupt Priority Setting for loop */!][!//

/* Qspi UD interrupt type of service Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqQSPIConfig/*[1]/IrqQspiTosConfig/IrqQspiUDTosConfig/*))"!][!//
#define IRQ_QSPI[!"num:i($SrnId - 1)"!]_UD_TOS            (IRQ_TOS_[!"IrqQSPIConfig/*[1]/IrqQspiTosConfig/IrqQspiUDTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqQSPIConfig/*[1]/IrqQspiPrioConfig/IrqQspiUDPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqQSPIConfig/*[1]/IrqQspiTosConfig/IrqQspiUDTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!VAR "IrqDmaExist" = "'STD_OFF'"!][!//
[!IF "num:i(count(IrqDmaConfig/*)) = 1"!][!//
/*
                     Container : IrqDMAinterruptConfiguration
*/
[!VAR "IrqDmaExist" = "'STD_ON'"!][!//
/* DMA interrupt Category settings */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqDmaConfig/*[1]/IrqDmaCatConfig/*))"!][!//
[!VAR "ParamName" = "node:name(IrqDmaConfig/*[1]/IrqDmaCatConfig/*[num:i($SrnId)])"!][!//
[!IF "contains($ParamName,'Err0')"!][!//
#define IRQ_DMA_ERR0_SR_CAT           (IRQ_[!"IrqDmaConfig/*[1]/IrqDmaCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ELSEIF "contains($ParamName,'Err1')"!][!//
#define IRQ_DMA_ERR1_SR_CAT           (IRQ_[!"IrqDmaConfig/*[1]/IrqDmaCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ELSEIF "contains($ParamName,'Err2')"!][!//
#define IRQ_DMA_ERR2_SR_CAT           (IRQ_[!"IrqDmaConfig/*[1]/IrqDmaCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ELSEIF "contains($ParamName,'Err3')"!][!//
#define IRQ_DMA_ERR3_SR_CAT           (IRQ_[!"IrqDmaConfig/*[1]/IrqDmaCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ELSE!][!//
[!VAR "ChNum" = "substring-after($ParamName,'IrqDmaCh')"!][!//
[!VAR "ChNum" = "substring-before($ChNum,'SRCat')"!][!//
[!IF "($ChNum <= 9)"!][!//
#define IRQ_DMA_CHANNEL[!"num:i($ChNum)"!]_SR_CAT      (IRQ_[!"IrqDmaConfig/*[1]/IrqDmaCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ELSE!][!//
#define IRQ_DMA_CHANNEL[!"num:i($ChNum)"!]_SR_CAT     (IRQ_[!"IrqDmaConfig/*[1]/IrqDmaCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDFOR!][!//

/* DMA interrupt Priority settings */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqDmaConfig/*[1]/IrqDmaPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqDmaConfig/*[1]/IrqDmaPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqDmaConfig/*[1]/IrqDmaTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqDmaConfig/*[1]/IrqDmaPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!VAR "ParamName" = "node:name(IrqDmaConfig/*[1]/IrqDmaPrioConfig/*[num:i($SrnId)])"!][!//
[!IF "contains($ParamName,'Err0')"!][!//
#define IRQ_DMA_ERR0_SR_PRIO          [!"num:inttohex(IrqDmaConfig/*[1]/IrqDmaPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!ELSEIF "contains($ParamName,'Err1')"!][!//
#define IRQ_DMA_ERR1_SR_PRIO          [!"num:inttohex(IrqDmaConfig/*[1]/IrqDmaPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!ELSEIF "contains($ParamName,'Err2')"!][!//
#define IRQ_DMA_ERR2_SR_PRIO          [!"num:inttohex(IrqDmaConfig/*[1]/IrqDmaPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!ELSEIF "contains($ParamName,'Err3')"!][!//
#define IRQ_DMA_ERR3_SR_PRIO          [!"num:inttohex(IrqDmaConfig/*[1]/IrqDmaPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!ELSE!][!//
[!VAR "ChNum" = "substring-after($ParamName,'IrqDmaCh')"!][!//
[!VAR "ChNum" = "substring-before($ChNum,'SRPrio')"!][!//
#define IRQ_DMA_CHANNEL[!"num:i($ChNum)"!]_SR_PRIO    [!"num:inttohex(IrqDmaConfig/*[1]/IrqDmaPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!ENDIF!][!//
[!NOCODE!][!//
[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqDmaConfig/*[1]/IrqDmaPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqDmaConfig/*[1]/IrqDmaCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of DMA interrupt Priority Setting for loop */!][!//

/* DMA interrupt type of service settings */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqDmaConfig/*[1]/IrqDmaTosConfig/*))"!][!//
[!VAR "ParamName" = "node:name(IrqDmaConfig/*[1]/IrqDmaTosConfig/*[num:i($SrnId)])"!][!//
[!IF "contains($ParamName,'Err0')"!][!//
#define IRQ_DMA_ERR0_SR_TOS           (IRQ_TOS_[!"IrqDmaConfig/*[1]/IrqDmaTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ELSEIF "contains($ParamName,'Err1')"!][!//
#define IRQ_DMA_ERR1_SR_TOS           (IRQ_TOS_[!"IrqDmaConfig/*[1]/IrqDmaTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ELSEIF "contains($ParamName,'Err2')"!][!//
#define IRQ_DMA_ERR2_SR_TOS           (IRQ_TOS_[!"IrqDmaConfig/*[1]/IrqDmaTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ELSEIF "contains($ParamName,'Err3')"!][!//
#define IRQ_DMA_ERR3_SR_TOS           (IRQ_TOS_[!"IrqDmaConfig/*[1]/IrqDmaTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ELSE!][!//
[!VAR "ChNum" = "substring-after($ParamName,'IrqDmaCh')"!][!//
[!VAR "ChNum" = "substring-before($ChNum,'SRTos')"!][!//
#define IRQ_DMA_CHANNEL[!"num:i($ChNum)"!]_SR_TOS     (IRQ_TOS_[!"IrqDmaConfig/*[1]/IrqDmaTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDIF!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqDmaConfig/*[1]/IrqDmaPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqDmaConfig/*[1]/IrqDmaTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//

[!ENDIF!][!/* End of DMA interrupt Setting */!][!//

[!VAR "IrqGPSRGroupExist" = "'STD_OFF'"!][!//
[!IF "num:i(count(IrqGPSRGroupConfig/*)) = 1"!][!//
/*
                     Container : IrqGPSRGroupinterruptConfiguration
*/
[!VAR "IrqGPSRGroupExist" = "'STD_ON'"!][!//
[!IF "contains( ecu:get('Irq.GpsrAvailable'), 'IrqGpsr0' )"!][!//
/* GPSRGROUP0 interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup0_Config/Irq_GPSRGroup0Cat_Config/*))"!][!//
#define IRQ_GPSRGROUP0_SR[!"num:i($SrnId - 1)"!]_CAT      (IRQ_[!"IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup0_Config/Irq_GPSRGroup0Cat_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* GPSRGROUP0 interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup0_Config/Irq_GPSRGroup0Prio_Config/*))"!][!//
[!VAR "Givenno" = "num:i(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup0_Config/Irq_GPSRGroup0Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup0_Config/Irq_GPSRGroup0Tos_Config/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup0_Config/Irq_GPSRGroup0Prio_Config/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_GPSRGROUP0_SR[!"num:i($SrnId - 1)"!]_PRIO     [!"num:inttohex(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup0_Config/Irq_GPSRGroup0Prio_Config/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup0_Config/Irq_GPSRGroup0Prio_Config/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup0_Config/Irq_GPSRGroup0Cat_Config/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of GPSRGROUP0 interrupt Priority Setting for loop */!][!//

/* GPSRGROUP0 interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup0_Config/Irq_GPSRGroup0Tos_Config/*))"!][!//
#define IRQ_GPSRGROUP0_SR[!"num:i($SrnId - 1)"!]_TOS      (IRQ_TOS_[!"IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup0_Config/Irq_GPSRGroup0Tos_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup0_Config/Irq_GPSRGroup0Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup0_Config/Irq_GPSRGroup0Tos_Config/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.GpsrAvailable'), 'IrqGpsr1' )"!][!//
/* GPSRGROUP1 interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup1_Config/Irq_GPSRGroup1Cat_Config/*))"!][!//
#define IRQ_GPSRGROUP1_SR[!"num:i($SrnId - 1)"!]_CAT      (IRQ_[!"IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup1_Config/Irq_GPSRGroup1Cat_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* GPSRGROUP1 interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup1_Config/Irq_GPSRGroup1Prio_Config/*))"!][!//
[!VAR "Givenno" = "num:i(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup1_Config/Irq_GPSRGroup1Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup1_Config/Irq_GPSRGroup1Tos_Config/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup1_Config/Irq_GPSRGroup1Prio_Config/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_GPSRGROUP1_SR[!"num:i($SrnId - 1)"!]_PRIO     [!"num:inttohex(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup1_Config/Irq_GPSRGroup1Prio_Config/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup1_Config/Irq_GPSRGroup1Prio_Config/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup1_Config/Irq_GPSRGroup1Cat_Config/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of GPSRGROUP1 interrupt Priority Setting for loop */!][!//

/* GPSRGROUP1 interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup1_Config/Irq_GPSRGroup1Tos_Config/*))"!][!//
#define IRQ_GPSRGROUP1_SR[!"num:i($SrnId - 1)"!]_TOS      (IRQ_TOS_[!"IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup1_Config/Irq_GPSRGroup1Tos_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup1_Config/Irq_GPSRGroup1Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup1_Config/Irq_GPSRGroup1Tos_Config/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.GpsrAvailable'), 'IrqGpsr2' )"!][!//
/* GPSRGROUP2 interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup2_Config/Irq_GPSRGroup2Cat_Config/*))"!][!//
#define IRQ_GPSRGROUP2_SR[!"num:i($SrnId - 1)"!]_CAT      (IRQ_[!"IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup2_Config/Irq_GPSRGroup2Cat_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* GPSRGROUP2 interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup2_Config/Irq_GPSRGroup2Prio_Config/*))"!][!//
[!VAR "Givenno" = "num:i(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup2_Config/Irq_GPSRGroup2Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup2_Config/Irq_GPSRGroup2Tos_Config/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup2_Config/Irq_GPSRGroup2Prio_Config/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_GPSRGROUP2_SR[!"num:i($SrnId - 1)"!]_PRIO     [!"num:inttohex(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup2_Config/Irq_GPSRGroup2Prio_Config/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup2_Config/Irq_GPSRGroup2Prio_Config/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup2_Config/Irq_GPSRGroup2Cat_Config/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of GPSRGROUP2 interrupt Priority Setting for loop */!][!//

/* GPSRGROUP2 interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup2_Config/Irq_GPSRGroup2Tos_Config/*))"!][!//
#define IRQ_GPSRGROUP2_SR[!"num:i($SrnId - 1)"!]_TOS      (IRQ_TOS_[!"IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup2_Config/Irq_GPSRGroup2Tos_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup2_Config/Irq_GPSRGroup2Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup2_Config/Irq_GPSRGroup2Tos_Config/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.GpsrAvailable'), 'IrqGpsr3' )"!][!//
/* GPSRGROUP3 interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup3_Config/Irq_GPSRGroup3Cat_Config/*))"!][!//
#define IRQ_GPSRGROUP3_SR[!"num:i($SrnId - 1)"!]_CAT      (IRQ_[!"IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup3_Config/Irq_GPSRGroup3Cat_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* GPSRGROUP3 interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup3_Config/Irq_GPSRGroup3Prio_Config/*))"!][!//
[!VAR "Givenno" = "num:i(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup3_Config/Irq_GPSRGroup3Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup3_Config/Irq_GPSRGroup3Tos_Config/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup3_Config/Irq_GPSRGroup3Prio_Config/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_GPSRGROUP3_SR[!"num:i($SrnId - 1)"!]_PRIO     [!"num:inttohex(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup3_Config/Irq_GPSRGroup3Prio_Config/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup3_Config/Irq_GPSRGroup3Prio_Config/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup3_Config/Irq_GPSRGroup3Cat_Config/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of GPSRGROUP3 interrupt Priority Setting for loop */!][!//

/* GPSRGROUP3 interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup3_Config/Irq_GPSRGroup3Tos_Config/*))"!][!//
#define IRQ_GPSRGROUP3_SR[!"num:i($SrnId - 1)"!]_TOS      (IRQ_TOS_[!"IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup3_Config/Irq_GPSRGroup3Tos_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup3_Config/Irq_GPSRGroup3Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup3_Config/Irq_GPSRGroup3Tos_Config/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.GpsrAvailable'), 'IrqGpsr4' )"!][!//
/* GPSRGROUP2 interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup4_Config/Irq_GPSRGroup4Cat_Config/*))"!][!//
#define IRQ_GPSRGROUP4_SR[!"num:i($SrnId - 1)"!]_CAT      (IRQ_[!"IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup4_Config/Irq_GPSRGroup4Cat_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* GPSRGROUP2 interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup4_Config/Irq_GPSRGroup4Prio_Config/*))"!][!//
[!VAR "Givenno" = "num:i(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup4_Config/Irq_GPSRGroup4Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup4_Config/Irq_GPSRGroup4Tos_Config/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup4_Config/Irq_GPSRGroup4Prio_Config/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_GPSRGROUP4_SR[!"num:i($SrnId - 1)"!]_PRIO     [!"num:inttohex(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup4_Config/Irq_GPSRGroup4Prio_Config/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup4_Config/Irq_GPSRGroup4Prio_Config/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup4_Config/Irq_GPSRGroup4Cat_Config/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of GPSRGROUP4 interrupt Priority Setting for loop */!][!//

/* GPSRGROUP4 interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup4_Config/Irq_GPSRGroup4Tos_Config/*))"!][!//
#define IRQ_GPSRGROUP4_SR[!"num:i($SrnId - 1)"!]_TOS      (IRQ_TOS_[!"IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup4_Config/Irq_GPSRGroup4Tos_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup4_Config/Irq_GPSRGroup4Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup4_Config/Irq_GPSRGroup4Tos_Config/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.GpsrAvailable'), 'IrqGpsr5' )"!][!//
/* GPSRGROUP5 interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup5_Config/Irq_GPSRGroup5Cat_Config/*))"!][!//
#define IRQ_GPSRGROUP5_SR[!"num:i($SrnId - 1)"!]_CAT      (IRQ_[!"IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup5_Config/Irq_GPSRGroup5Cat_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* GPSRGROUP2 interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup5_Config/Irq_GPSRGroup5Prio_Config/*))"!][!//
[!VAR "Givenno" = "num:i(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup5_Config/Irq_GPSRGroup5Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup5_Config/Irq_GPSRGroup5Tos_Config/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup5_Config/Irq_GPSRGroup5Prio_Config/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_GPSRGROUP5_SR[!"num:i($SrnId - 1)"!]_PRIO     [!"num:inttohex(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup5_Config/Irq_GPSRGroup5Prio_Config/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup5_Config/Irq_GPSRGroup5Prio_Config/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup5_Config/Irq_GPSRGroup5Cat_Config/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of GPSRGROUP5 interrupt Priority Setting for loop */!][!//

/* GPSRGROUP5 interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup5_Config/Irq_GPSRGroup5Tos_Config/*))"!][!//
#define IRQ_GPSRGROUP5_SR[!"num:i($SrnId - 1)"!]_TOS      (IRQ_TOS_[!"IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup5_Config/Irq_GPSRGroup5Tos_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup5_Config/Irq_GPSRGroup5Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGPSRGroupConfig/*[1]/Irq_GPSRGroup5_Config/Irq_GPSRGroup5Tos_Config/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!ENDIF!][!//

[!VAR "IrqFlexRayExist" = "'STD_OFF'"!][!//
[!IF "num:i(count(IrqFlexRayConfig/*)) = 1"!][!//
/*
                     Container : IrqFLEXRAYinterruptConfiguration
*/
[!VAR "IrqFlexRayExist" = "'STD_ON'"!][!//
[!IF "contains( ecu:get('Irq.FlexRayAvailable'), 'IrqFlexRay0' )"!][!//
/* FLEXRAY0 interrupt Category Setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqFlexRayConfig/*[1]/Irq_FlexRay0_Config/Irq_FlexRay0Cat_Config/*))"!][!//
#define IRQ_FLEXRAY0_[!"substring-before(substring-after(node:name(IrqFlexRayConfig/*[1]/Irq_FlexRay0_Config/Irq_FlexRay0Cat_Config/*[num:i($SrnId)]), 'Irq_FlexRay0'),'_Cat')"!]_CAT         (IRQ_[!"IrqFlexRayConfig/*[1]/Irq_FlexRay0_Config/Irq_FlexRay0Cat_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/* FLEXRAY0 interrupt Priority Setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqFlexRayConfig/*[1]/Irq_FlexRay0_Config/Irq_FlexRay0Prio_Config/*))"!][!//
[!VAR "Givenno" = "num:i(IrqFlexRayConfig/*[1]/Irq_FlexRay0_Config/Irq_FlexRay0Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqFlexRayConfig/*[1]/Irq_FlexRay0_Config/Irq_FlexRay0Tos_Config/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqFlexRayConfig/*[1]/Irq_FlexRay0_Config/Irq_FlexRay0Prio_Config/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_FLEXRAY0_[!"substring-before(substring-after(node:name(IrqFlexRayConfig/*[1]/Irq_FlexRay0_Config/Irq_FlexRay0Prio_Config/*[num:i($SrnId)]), 'Irq_FlexRay0'),'_Prio')"!]_PRIO         [!"num:inttohex(IrqFlexRayConfig/*[1]/Irq_FlexRay0_Config/Irq_FlexRay0Prio_Config/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//
[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqFlexRayConfig/*[1]/Irq_FlexRay0_Config/Irq_FlexRay0Prio_Config/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqFlexRayConfig/*[1]/Irq_FlexRay0_Config/Irq_FlexRay0Cat_Config/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of FlexRay0 interrupt Priority Setting for loop */!][!//

/* FLEXRAY0 interrupt type of service Setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqFlexRayConfig/*[1]/Irq_FlexRay0_Config/Irq_FlexRay0Tos_Config/*))"!][!//
#define IRQ_FLEXRAY0_[!"substring-before(substring-after(node:name(IrqFlexRayConfig/*[1]/Irq_FlexRay0_Config/Irq_FlexRay0Tos_Config/*[num:i($SrnId)]), 'Irq_FlexRay0'),'_Tos')"!]_TOS         (IRQ_TOS_[!"IrqFlexRayConfig/*[1]/Irq_FlexRay0_Config/Irq_FlexRay0Tos_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqFlexRayConfig/*[1]/Irq_FlexRay0_Config/Irq_FlexRay0Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqFlexRayConfig/*[1]/Irq_FlexRay0_Config/Irq_FlexRay0Tos_Config/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.FlexRayAvailable'), 'IrqFlexRay1' )"!][!//
/* FLEXRAY1 interrupt Category Setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqFlexRayConfig/*[1]/Irq_FlexRay1_Config/Irq_FlexRay1Cat_Config/*))"!][!//
#define IRQ_FLEXRAY1_[!"substring-before(substring-after(node:name(IrqFlexRayConfig/*[1]/Irq_FlexRay1_Config/Irq_FlexRay1Cat_Config/*[num:i($SrnId)]), 'Irq_FlexRay1'),'_Cat')"!]_CAT         (IRQ_[!"IrqFlexRayConfig/*[1]/Irq_FlexRay1_Config/Irq_FlexRay1Cat_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/* FLEXRAY1 interrupt Priority Setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqFlexRayConfig/*[1]/Irq_FlexRay1_Config/Irq_FlexRay1Prio_Config/*))"!][!//
[!VAR "Givenno" = "num:i(IrqFlexRayConfig/*[1]/Irq_FlexRay1_Config/Irq_FlexRay1Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqFlexRayConfig/*[1]/Irq_FlexRay1_Config/Irq_FlexRay1Tos_Config/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqFlexRayConfig/*[1]/Irq_FlexRay1_Config/Irq_FlexRay1Prio_Config/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_FLEXRAY1_[!"substring-before(substring-after(node:name(IrqFlexRayConfig/*[1]/Irq_FlexRay1_Config/Irq_FlexRay1Prio_Config/*[num:i($SrnId)]), 'Irq_FlexRay1'),'_Prio')"!]_PRIO         [!"num:inttohex(IrqFlexRayConfig/*[1]/Irq_FlexRay1_Config/Irq_FlexRay1Prio_Config/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//
[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqFlexRayConfig/*[1]/Irq_FlexRay1_Config/Irq_FlexRay1Prio_Config/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqFlexRayConfig/*[1]/Irq_FlexRay1_Config/Irq_FlexRay1Cat_Config/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of FlexRay1 interrupt Priority Setting for loop */!][!//

/* FLEXRAY1 interrupt type of service Setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqFlexRayConfig/*[1]/Irq_FlexRay1_Config/Irq_FlexRay1Tos_Config/*))"!][!//
#define IRQ_FLEXRAY1_[!"substring-before(substring-after(node:name(IrqFlexRayConfig/*[1]/Irq_FlexRay1_Config/Irq_FlexRay1Tos_Config/*[num:i($SrnId)]), 'Irq_FlexRay1'),'_Tos')"!]_TOS         (IRQ_TOS_[!"IrqFlexRayConfig/*[1]/Irq_FlexRay1_Config/Irq_FlexRay1Tos_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqFlexRayConfig/*[1]/Irq_FlexRay1_Config/Irq_FlexRay1Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqFlexRayConfig/*[1]/Irq_FlexRay1_Config/Irq_FlexRay1Tos_Config/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!//
[!ENDIF!][!//


[!IF "num:i(count(IrqScuConfig/*)) = 1"!][!//
/*
                     Container : Scu interrupt Configuration
*/
/* Scu interrupt Category Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqScuConfig/*[1]/Irq_ScuCat_Config/*))"!][!//
#define IRQ_SCU_ERU_SR[!"num:i($SrnId - 1)"!]_CAT         (IRQ_[!"IrqScuConfig/*[1]/Irq_ScuCat_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/* Scu interrupt Priority Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqScuConfig/*[1]/Irq_ScuPrio_Config/*))"!][!//
[!VAR "Givenno" = "num:i(IrqScuConfig/*[1]/Irq_ScuPrio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqScuConfig/*[1]/Irq_ScuTos_Config/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqScuConfig/*[1]/Irq_ScuPrio_Config/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_SCU_ERU_SR[!"num:i($SrnId - 1)"!]_PRIO        [!"num:inttohex(IrqScuConfig/*[1]/Irq_ScuPrio_Config/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//
[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqScuConfig/*[1]/Irq_ScuPrio_Config/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqScuConfig/*[1]/Irq_ScuCat_Config/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of Scu interrupt Priority Setting for loop */!][!//

/* Scu interrupt type of service Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqScuConfig/*[1]/Irq_ScuTos_Config/*))"!][!//
#define IRQ_SCU_ERU_SR[!"num:i($SrnId - 1)"!]_TOS         (IRQ_TOS_[!"IrqScuConfig/*[1]/Irq_ScuTos_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqScuConfig/*[1]/Irq_ScuPrio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqScuConfig/*[1]/Irq_ScuTos_Config/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!VAR "IrqCCU6Exist" = "'STD_OFF'"!][!//
[!IF "num:i(count(IrqCCU6Config/*)) = 1"!][!//
/*
                     Container : IrqCCU6 interruptConfiguration
*/
[!VAR "IrqCCU6Exist" = "'STD_ON'"!][!//
[!IF "contains( ecu:get('Irq.CCU6Available'), 'IrqCCU60' )"!][!//
/*CCU60 interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqCCU6Config/*[1]/Irq_CCU60_Config/Irq_CCU60Cat_Config/*))"!][!//
#define IRQ_CCU60_SR[!"num:i($SrnId - 1)"!]_CAT           (IRQ_[!"IrqCCU6Config/*[1]/Irq_CCU60_Config/Irq_CCU60Cat_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/*CCU60 interrupt Priority setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqCCU6Config/*[1]/Irq_CCU60_Config/Irq_CCU60Prio_Config/*))"!][!//
[!VAR "Givenno" = "num:i(IrqCCU6Config/*[1]/Irq_CCU60_Config/Irq_CCU60Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqCCU6Config/*[1]/Irq_CCU60_Config/Irq_CCU60Tos_Config/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqCCU6Config/*[1]/Irq_CCU60_Config/Irq_CCU60Prio_Config/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_CCU60_SR[!"num:i($SrnId - 1)"!]_PRIO          [!"num:inttohex(IrqCCU6Config/*[1]/Irq_CCU60_Config/Irq_CCU60Prio_Config/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//
[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqCCU6Config/*[1]/Irq_CCU60_Config/Irq_CCU60Prio_Config/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqCCU6Config/*[1]/Irq_CCU60_Config/Irq_CCU60Cat_Config/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of CCU60 interrupt Priority Setting for loop */!][!//

/*CCU60 interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqCCU6Config/*[1]/Irq_CCU60_Config/Irq_CCU60Tos_Config/*))"!][!//
#define IRQ_CCU60_SR[!"num:i($SrnId - 1)"!]_TOS           (IRQ_TOS_[!"IrqCCU6Config/*[1]/Irq_CCU60_Config/Irq_CCU60Tos_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqCCU6Config/*[1]/Irq_CCU60_Config/Irq_CCU60Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqCCU6Config/*[1]/Irq_CCU60_Config/Irq_CCU60Tos_Config/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.CCU6Available'), 'IrqCCU61' )"!][!//
/*CCU61 interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqCCU6Config/*[1]/Irq_CCU61_Config/Irq_CCU61Cat_Config/*))"!][!//
#define IRQ_CCU61_SR[!"num:i($SrnId - 1)"!]_CAT           (IRQ_[!"IrqCCU6Config/*[1]/Irq_CCU61_Config/Irq_CCU61Cat_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/*CCU61 interrupt Priority setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqCCU6Config/*[1]/Irq_CCU61_Config/Irq_CCU61Prio_Config/*))"!][!//
[!VAR "Givenno" = "num:i(IrqCCU6Config/*[1]/Irq_CCU61_Config/Irq_CCU61Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqCCU6Config/*[1]/Irq_CCU61_Config/Irq_CCU61Tos_Config/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqCCU6Config/*[1]/Irq_CCU61_Config/Irq_CCU61Prio_Config/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_CCU61_SR[!"num:i($SrnId - 1)"!]_PRIO          [!"num:inttohex(IrqCCU6Config/*[1]/Irq_CCU61_Config/Irq_CCU61Prio_Config/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//
[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqCCU6Config/*[1]/Irq_CCU61_Config/Irq_CCU61Prio_Config/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqCCU6Config/*[1]/Irq_CCU61_Config/Irq_CCU61Cat_Config/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of CCU61 interrupt Priority Setting for loop */!][!//

/*CCU61 interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqCCU6Config/*[1]/Irq_CCU61_Config/Irq_CCU61Tos_Config/*))"!][!//
#define IRQ_CCU61_SR[!"num:i($SrnId - 1)"!]_TOS           (IRQ_TOS_[!"IrqCCU6Config/*[1]/Irq_CCU61_Config/Irq_CCU61Tos_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqCCU6Config/*[1]/Irq_CCU61_Config/Irq_CCU61Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqCCU6Config/*[1]/Irq_CCU61_Config/Irq_CCU61Tos_Config/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDIF!][!//

/*
                     Container : DMU interrupt Configuration
*/
/* DMU interrupt Category Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqDMUConfig/*[1]/IrqDMUCatConfig/*))"!][!//
[!IF "contains(node:name(IrqDMUConfig/*[1]/IrqDMUCatConfig/*[num:i($SrnId)]), 'HOST')"!][!//
#define IRQ_DMU_HOST_CAT            (IRQ_[!"IrqDMUConfig/*[1]/IrqDMUCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ELSE!][!//
#define IRQ_DMU_FSI_CAT            (IRQ_[!"IrqDMUConfig/*[1]/IrqDMUCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDIF!]
[!ENDFOR!][!//

/* DMU interrupt Category Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqDMUConfig/*[1]/IrqDMUPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqDMUConfig/*[1]/IrqDMUPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqDMUConfig/*[1]/IrqDMUTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqDMUConfig/*[1]/IrqDMUPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!IF "contains(node:name(IrqDMUConfig/*[1]/IrqDMUCatConfig/*[num:i($SrnId)]), 'HOST')"!][!//
#define IRQ_DMU_HOST_PRIO           [!"num:inttohex(IrqDMUConfig/*[1]/IrqDMUPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!ELSE!][!//
#define IRQ_DMU_FSI_PRIO           [!"num:inttohex(IrqDMUConfig/*[1]/IrqDMUPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!ENDIF!]
[!NOCODE!][!//
[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqDMUConfig/*[1]/IrqDMUPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqDMUConfig/*[1]/IrqDMUCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of DMU interrupt Priority Setting for loop */!][!//

/* DMU interrupt type of service Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqDMUConfig/*[1]/IrqDMUTosConfig/*))"!][!//
[!IF "contains(node:name(IrqDMUConfig/*[1]/IrqDMUCatConfig/*[num:i($SrnId)]), 'HOST')"!][!//
#define IRQ_DMU_HOST_TOS            (IRQ_TOS_[!"IrqDMUConfig/*[1]/IrqDMUTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ELSE!][!//
#define IRQ_DMU_FSI_TOS            (IRQ_TOS_[!"IrqDMUConfig/*[1]/IrqDMUTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDIF!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqDMUConfig/*[1]/IrqDMUPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqDMUConfig/*[1]/IrqDMUTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//

[!VAR "IrqETHExist" = "'STD_OFF'"!][!//
[!IF "num:i(count(IrqETHConfig/*)) = 1"!][!//
/*
                     Container : Ethernet interrupt Configuration
*/
[!NOCODE!][!//
[!VAR "IrqETHExist" = "'STD_ON'"!][!//	
[!ENDNOCODE!][!//
/* Ethernet interrupt Category Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqETHConfig/*[1]/IrqETHCatConfig/*))"!][!//
#define IRQ_ETH_SR[!"num:i($SrnId - 1)"!]_CAT              (IRQ_[!"IrqETHConfig/*[1]/IrqETHCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/* Ethernet interrupt Category Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqETHConfig/*[1]/IrqETHPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqETHConfig/*[1]/IrqETHPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqETHConfig/*[1]/IrqETHTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqETHConfig/*[1]/IrqETHPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_ETH_SR[!"num:i($SrnId - 1)"!]_PRIO             [!"num:inttohex(IrqETHConfig/*[1]/IrqETHPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//
[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqETHConfig/*[1]/IrqETHPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqETHConfig/*[1]/IrqETHCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of Ethernet interrupt Priority Setting for loop */!][!//

/* Ethernet interrupt type of service Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqETHConfig/*[1]/IrqETHTosConfig/*))"!][!//
#define IRQ_ETH_SR[!"num:i($SrnId - 1)"!]_TOS              (IRQ_TOS_[!"IrqETHConfig/*[1]/IrqETHTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqETHConfig/*[1]/IrqETHPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqETHConfig/*[1]/IrqETHTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//


[!VAR "IrqCanExist" = "'STD_OFF'"!][!//
[!IF "num:i(count(IrqCanConfig/*)) = 1"!][!//
/*
                     Container : IrqCaninterruptConfiguration
*/
[!VAR "IrqCanExist" = "'STD_ON'"!][!//
[!IF "contains( ecu:get('Irq.CanModulesAvailable'), 'IrqCan0' )"!][!//
/* CAN0 interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqCanConfig/*[1]/IrqCan0Config/IrqCanCatConfig/*))"!][!//
#define IRQ_CAN0_SR[!"substring-before(substring-after(node:name(IrqCanConfig/*[1]/IrqCan0Config/IrqCanCatConfig/*[num:i($SrnId)]), 'IrqCanSR'),'Cat')"!]_CAT      (IRQ_[!"IrqCanConfig/*[1]/IrqCan0Config/IrqCanCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* CAN0 interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqCanConfig/*[1]/IrqCan0Config/IrqCanPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqCanConfig/*[1]/IrqCan0Config/IrqCanPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqCanConfig/*[1]/IrqCan0Config/IrqCanTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "'CAN0'"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_CAN0_SR[!"substring-before(substring-after(node:name(IrqCanConfig/*[1]/IrqCan0Config/IrqCanPrioConfig/*[num:i($SrnId)]), 'IrqCanSR'),'Prio')"!]_PRIO     [!"num:inttohex(IrqCanConfig/*[1]/IrqCan0Config/IrqCanPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqCanConfig/*[1]/IrqCan0Config/IrqCanPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqCanConfig/*[1]/IrqCan0Config/IrqCanCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of CAN0 interrupt Priority Setting for loop */!][!//

/* CAN0 interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqCanConfig/*[1]/IrqCan0Config/IrqCanTosConfig/*))"!][!//
#define IRQ_CAN0_SR[!"substring-before(substring-after(node:name(IrqCanConfig/*[1]/IrqCan0Config/IrqCanTosConfig/*[num:i($SrnId)]), 'IrqCanSR'),'Tos')"!]_TOS      (IRQ_TOS_[!"IrqCanConfig/*[1]/IrqCan0Config/IrqCanTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqCanConfig/*[1]/IrqCan0Config/IrqCanPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqCanConfig/*[1]/IrqCan0Config/IrqCanTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.CanModulesAvailable'), 'IrqCan1' )"!][!//
/* CAN1 interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqCanConfig/*[1]/IrqCan1Config/IrqCanCatConfig/*))"!][!//
#define IRQ_CAN1_SR[!"substring-before(substring-after(node:name(IrqCanConfig/*[1]/IrqCan1Config/IrqCanCatConfig/*[num:i($SrnId)]), 'IrqCanSR'),'Cat')"!]_CAT      (IRQ_[!"IrqCanConfig/*[1]/IrqCan1Config/IrqCanCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* CAN1 interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqCanConfig/*[1]/IrqCan1Config/IrqCanPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqCanConfig/*[1]/IrqCan1Config/IrqCanPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqCanConfig/*[1]/IrqCan1Config/IrqCanTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "'CAN1'"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_CAN1_SR[!"substring-before(substring-after(node:name(IrqCanConfig/*[1]/IrqCan1Config/IrqCanPrioConfig/*[num:i($SrnId)]), 'IrqCanSR'),'Prio')"!]_PRIO     [!"num:inttohex(IrqCanConfig/*[1]/IrqCan1Config/IrqCanPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqCanConfig/*[1]/IrqCan1Config/IrqCanPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqCanConfig/*[1]/IrqCan1Config/IrqCanCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of CAN1 interrupt Priority Setting for loop */!][!//

/* CAN1 interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqCanConfig/*[1]/IrqCan1Config/IrqCanTosConfig/*))"!][!//
#define IRQ_CAN1_SR[!"substring-before(substring-after(node:name(IrqCanConfig/*[1]/IrqCan1Config/IrqCanTosConfig/*[num:i($SrnId)]), 'IrqCanSR'),'Tos')"!]_TOS      (IRQ_TOS_[!"IrqCanConfig/*[1]/IrqCan1Config/IrqCanTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqCanConfig/*[1]/IrqCan1Config/IrqCanPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqCanConfig/*[1]/IrqCan1Config/IrqCanTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.CanModulesAvailable'), 'IrqCan2' )"!][!//
/* CAN2 interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqCanConfig/*[1]/IrqCan2Config/IrqCanCatConfig/*))"!][!//
#define IRQ_CAN2_SR[!"substring-before(substring-after(node:name(IrqCanConfig/*[1]/IrqCan2Config/IrqCanCatConfig/*[num:i($SrnId)]), 'IrqCanSR'),'Cat')"!]_CAT      (IRQ_[!"IrqCanConfig/*[1]/IrqCan2Config/IrqCanCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* CAN2 interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqCanConfig/*[1]/IrqCan2Config/IrqCanPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqCanConfig/*[1]/IrqCan2Config/IrqCanPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqCanConfig/*[1]/IrqCan2Config/IrqCanTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "'CAN2'"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_CAN2_SR[!"substring-before(substring-after(node:name(IrqCanConfig/*[1]/IrqCan2Config/IrqCanPrioConfig/*[num:i($SrnId)]), 'IrqCanSR'),'Prio')"!]_PRIO     [!"num:inttohex(IrqCanConfig/*[1]/IrqCan2Config/IrqCanPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqCanConfig/*[1]/IrqCan2Config/IrqCanPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqCanConfig/*[1]/IrqCan2Config/IrqCanCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of CAN2 interrupt Priority Setting for loop */!][!//

/* CAN2 interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqCanConfig/*[1]/IrqCan2Config/IrqCanTosConfig/*))"!][!//
#define IRQ_CAN2_SR[!"substring-before(substring-after(node:name(IrqCanConfig/*[1]/IrqCan2Config/IrqCanTosConfig/*[num:i($SrnId)]), 'IrqCanSR'),'Tos')"!]_TOS      (IRQ_TOS_[!"IrqCanConfig/*[1]/IrqCan2Config/IrqCanTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqCanConfig/*[1]/IrqCan2Config/IrqCanPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqCanConfig/*[1]/IrqCan2Config/IrqCanTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!ENDIF!][!//

[!//  ADC configuration
[!VAR "IrqAdcExist" = "'STD_OFF'"!][!//
[!IF "num:i(count(IrqAdcConfig/*)) = 1"!][!//

/*
                     Container : Irq ADC configuration
*/
[!VAR "IrqAdcExist" = "'STD_ON'"!][!//
[!IF "contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADC0' )"!][!//
/*ADC0 interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc0Config/IrqAdc0CatConfig/*))"!][!//
#define IRQ_ADC0_SR[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqAdcConfig/*[1]/IrqAdc0Config/IrqAdc0CatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*ADC0 interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc0Config/IrqAdc0PrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqAdcConfig/*[1]/IrqAdc0Config/IrqAdc0PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdc0Config/IrqAdc0TosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqAdcConfig/*[1]/IrqAdc0Config/IrqAdc0PrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_ADC0_SR[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqAdcConfig/*[1]/IrqAdc0Config/IrqAdc0PrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqAdcConfig/*[1]/IrqAdc0Config/IrqAdc0PrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqAdcConfig/*[1]/IrqAdc0Config/IrqAdc0CatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of ADC0 interrupt Priority Setting for loop */!][!//

/*ADC0 interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc0Config/IrqAdc0TosConfig/*))"!][!//
#define IRQ_ADC0_SR[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqAdcConfig/*[1]/IrqAdc0Config/IrqAdc0TosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqAdcConfig/*[1]/IrqAdc0Config/IrqAdc0PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdc0Config/IrqAdc0TosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADC1' )"!][!//
/*ADC1 interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc1Config/IrqAdc1CatConfig/*))"!][!//
#define IRQ_ADC1_SR[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqAdcConfig/*[1]/IrqAdc1Config/IrqAdc1CatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*ADC1 interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc1Config/IrqAdc1PrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqAdcConfig/*[1]/IrqAdc1Config/IrqAdc1PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdc1Config/IrqAdc1TosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqAdcConfig/*[1]/IrqAdc1Config/IrqAdc1PrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_ADC1_SR[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqAdcConfig/*[1]/IrqAdc1Config/IrqAdc1PrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqAdcConfig/*[1]/IrqAdc1Config/IrqAdc1PrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqAdcConfig/*[1]/IrqAdc1Config/IrqAdc1CatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of ADC1 interrupt Priority Setting for loop */!][!//

/*ADC1 interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc1Config/IrqAdc1TosConfig/*))"!][!//
#define IRQ_ADC1_SR[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqAdcConfig/*[1]/IrqAdc1Config/IrqAdc1TosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqAdcConfig/*[1]/IrqAdc1Config/IrqAdc1PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdc1Config/IrqAdc1TosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADC2' )"!][!//
/*ADC2 interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc2Config/IrqAdc2CatConfig/*))"!][!//
#define IRQ_ADC2_SR[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqAdcConfig/*[1]/IrqAdc2Config/IrqAdc2CatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*ADC2 interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc2Config/IrqAdc2PrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqAdcConfig/*[1]/IrqAdc2Config/IrqAdc2PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdc2Config/IrqAdc2TosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqAdcConfig/*[1]/IrqAdc2Config/IrqAdc2PrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_ADC2_SR[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqAdcConfig/*[1]/IrqAdc2Config/IrqAdc2PrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqAdcConfig/*[1]/IrqAdc2Config/IrqAdc2PrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqAdcConfig/*[1]/IrqAdc2Config/IrqAdc2CatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of ADC2 interrupt Priority Setting for loop */!][!//

/*ADC2 interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc2Config/IrqAdc2TosConfig/*))"!][!//
#define IRQ_ADC2_SR[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqAdcConfig/*[1]/IrqAdc2Config/IrqAdc2TosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqAdcConfig/*[1]/IrqAdc2Config/IrqAdc2PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdc2Config/IrqAdc2TosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADC3' )"!][!//
/*ADC3 interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc3Config/IrqAdc3CatConfig/*))"!][!//
#define IRQ_ADC3_SR[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqAdcConfig/*[1]/IrqAdc3Config/IrqAdc3CatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*ADC3 interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc3Config/IrqAdc3PrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqAdcConfig/*[1]/IrqAdc3Config/IrqAdc3PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdc3Config/IrqAdc3TosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqAdcConfig/*[1]/IrqAdc3Config/IrqAdc3PrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_ADC3_SR[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqAdcConfig/*[1]/IrqAdc3Config/IrqAdc3PrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqAdcConfig/*[1]/IrqAdc3Config/IrqAdc3PrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqAdcConfig/*[1]/IrqAdc3Config/IrqAdc3CatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of ADC3 interrupt Priority Setting for loop */!][!//

/*ADC3 interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc3Config/IrqAdc3TosConfig/*))"!][!//
#define IRQ_ADC3_SR[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqAdcConfig/*[1]/IrqAdc3Config/IrqAdc3TosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqAdcConfig/*[1]/IrqAdc3Config/IrqAdc3PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdc3Config/IrqAdc3TosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADC4' )"!][!//
/*ADC4 interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc4Config/IrqAdc4CatConfig/*))"!][!//
#define IRQ_ADC4_SR[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqAdcConfig/*[1]/IrqAdc4Config/IrqAdc4CatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*ADC4 interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc4Config/IrqAdc4PrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqAdcConfig/*[1]/IrqAdc4Config/IrqAdc4PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdc4Config/IrqAdc4TosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqAdcConfig/*[1]/IrqAdc4Config/IrqAdc4PrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_ADC4_SR[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqAdcConfig/*[1]/IrqAdc4Config/IrqAdc4PrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqAdcConfig/*[1]/IrqAdc4Config/IrqAdc4PrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqAdcConfig/*[1]/IrqAdc4Config/IrqAdc4CatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of ADC4 interrupt Priority Setting for loop */!][!//

/*ADC4 interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc4Config/IrqAdc4TosConfig/*))"!][!//
#define IRQ_ADC4_SR[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqAdcConfig/*[1]/IrqAdc4Config/IrqAdc4TosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqAdcConfig/*[1]/IrqAdc4Config/IrqAdc4PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdc4Config/IrqAdc4TosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADC5' )"!][!//
/*ADC5 interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc5Config/IrqAdc5CatConfig/*))"!][!//
#define IRQ_ADC5_SR[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqAdcConfig/*[1]/IrqAdc5Config/IrqAdc5CatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*ADC5 interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc5Config/IrqAdc5PrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqAdcConfig/*[1]/IrqAdc5Config/IrqAdc5PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdc5Config/IrqAdc5TosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqAdcConfig/*[1]/IrqAdc5Config/IrqAdc5PrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_ADC5_SR[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqAdcConfig/*[1]/IrqAdc5Config/IrqAdc5PrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqAdcConfig/*[1]/IrqAdc5Config/IrqAdc5PrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqAdcConfig/*[1]/IrqAdc5Config/IrqAdc5CatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of ADC5 interrupt Priority Setting for loop */!][!//

/*ADC5 interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc5Config/IrqAdc5TosConfig/*))"!][!//
#define IRQ_ADC5_SR[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqAdcConfig/*[1]/IrqAdc5Config/IrqAdc5TosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqAdcConfig/*[1]/IrqAdc5Config/IrqAdc5PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdc5Config/IrqAdc5TosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADC6' )"!][!//
/*ADC6 interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc6Config/IrqAdc6CatConfig/*))"!][!//
#define IRQ_ADC6_SR[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqAdcConfig/*[1]/IrqAdc6Config/IrqAdc6CatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*ADC6 interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc6Config/IrqAdc6PrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqAdcConfig/*[1]/IrqAdc6Config/IrqAdc6PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdc6Config/IrqAdc6TosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqAdcConfig/*[1]/IrqAdc6Config/IrqAdc6PrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_ADC6_SR[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqAdcConfig/*[1]/IrqAdc6Config/IrqAdc6PrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqAdcConfig/*[1]/IrqAdc6Config/IrqAdc6PrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqAdcConfig/*[1]/IrqAdc6Config/IrqAdc6CatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of ADC6 interrupt Priority Setting for loop */!][!//

/*ADC6 interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc6Config/IrqAdc6TosConfig/*))"!][!//
#define IRQ_ADC6_SR[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqAdcConfig/*[1]/IrqAdc6Config/IrqAdc6TosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqAdcConfig/*[1]/IrqAdc6Config/IrqAdc6PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdc6Config/IrqAdc6TosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADC7' )"!][!//
/*ADC7 interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc7Config/IrqAdc7CatConfig/*))"!][!//
#define IRQ_ADC7_SR[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqAdcConfig/*[1]/IrqAdc7Config/IrqAdc7CatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*ADC7 interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc7Config/IrqAdc7PrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqAdcConfig/*[1]/IrqAdc7Config/IrqAdc7PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdc7Config/IrqAdc7TosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqAdcConfig/*[1]/IrqAdc7Config/IrqAdc7PrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_ADC7_SR[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqAdcConfig/*[1]/IrqAdc7Config/IrqAdc7PrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqAdcConfig/*[1]/IrqAdc7Config/IrqAdc7PrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqAdcConfig/*[1]/IrqAdc7Config/IrqAdc7CatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of ADC7 interrupt Priority Setting for loop */!][!//

/*ADC7 interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc7Config/IrqAdc7TosConfig/*))"!][!//
#define IRQ_ADC7_SR[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqAdcConfig/*[1]/IrqAdc7Config/IrqAdc7TosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqAdcConfig/*[1]/IrqAdc7Config/IrqAdc7PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdc7Config/IrqAdc7TosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADC8' )"!][!//
/*ADC8 interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc8Config/IrqAdc8CatConfig/*))"!][!//
#define IRQ_ADC8_SR[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqAdcConfig/*[1]/IrqAdc8Config/IrqAdc8CatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*ADC8 interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc8Config/IrqAdc8PrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqAdcConfig/*[1]/IrqAdc8Config/IrqAdc8PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdc8Config/IrqAdc8TosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqAdcConfig/*[1]/IrqAdc8Config/IrqAdc8PrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_ADC8_SR[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqAdcConfig/*[1]/IrqAdc8Config/IrqAdc8PrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqAdcConfig/*[1]/IrqAdc8Config/IrqAdc8PrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqAdcConfig/*[1]/IrqAdc8Config/IrqAdc8CatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of ADC8 interrupt Priority Setting for loop */!][!//

/*ADC8 interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc8Config/IrqAdc8TosConfig/*))"!][!//
#define IRQ_ADC8_SR[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqAdcConfig/*[1]/IrqAdc8Config/IrqAdc8TosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqAdcConfig/*[1]/IrqAdc8Config/IrqAdc8PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdc8Config/IrqAdc8TosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADC9' )"!][!//
/*ADC9 interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc9Config/IrqAdc9CatConfig/*))"!][!//
#define IRQ_ADC9_SR[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqAdcConfig/*[1]/IrqAdc9Config/IrqAdc9CatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*ADC9 interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc9Config/IrqAdc9PrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqAdcConfig/*[1]/IrqAdc9Config/IrqAdc9PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdc9Config/IrqAdc9TosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqAdcConfig/*[1]/IrqAdc9Config/IrqAdc9PrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_ADC9_SR[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqAdcConfig/*[1]/IrqAdc9Config/IrqAdc9PrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqAdcConfig/*[1]/IrqAdc9Config/IrqAdc9PrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqAdcConfig/*[1]/IrqAdc9Config/IrqAdc9CatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of ADC9 interrupt Priority Setting for loop */!][!//

/*ADC9 interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc9Config/IrqAdc9TosConfig/*))"!][!//
#define IRQ_ADC9_SR[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqAdcConfig/*[1]/IrqAdc9Config/IrqAdc9TosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqAdcConfig/*[1]/IrqAdc9Config/IrqAdc9PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdc9Config/IrqAdc9TosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADC10' )"!][!//
/*ADC10 interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc10Config/IrqAdc10CatConfig/*))"!][!//
#define IRQ_ADC10_SR[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqAdcConfig/*[1]/IrqAdc10Config/IrqAdc10CatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*ADC10 interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc10Config/IrqAdc10PrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqAdcConfig/*[1]/IrqAdc10Config/IrqAdc10PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdc10Config/IrqAdc10TosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqAdcConfig/*[1]/IrqAdc10Config/IrqAdc10PrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_ADC10_SR[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqAdcConfig/*[1]/IrqAdc10Config/IrqAdc10PrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqAdcConfig/*[1]/IrqAdc10Config/IrqAdc10PrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqAdcConfig/*[1]/IrqAdc10Config/IrqAdc10CatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of ADC10 interrupt Priority Setting for loop */!][!//

/*ADC10 interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc10Config/IrqAdc10TosConfig/*))"!][!//
#define IRQ_ADC10_SR[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqAdcConfig/*[1]/IrqAdc10Config/IrqAdc10TosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqAdcConfig/*[1]/IrqAdc10Config/IrqAdc10PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdc10Config/IrqAdc10TosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADC11' )"!][!//
/*ADC11 interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc11Config/IrqAdc11CatConfig/*))"!][!//
#define IRQ_ADC11_SR[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqAdcConfig/*[1]/IrqAdc11Config/IrqAdc11CatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*ADC11 interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc11Config/IrqAdc11PrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqAdcConfig/*[1]/IrqAdc11Config/IrqAdc11PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdc11Config/IrqAdc11TosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqAdcConfig/*[1]/IrqAdc11Config/IrqAdc11PrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_ADC11_SR[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqAdcConfig/*[1]/IrqAdc11Config/IrqAdc11PrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqAdcConfig/*[1]/IrqAdc11Config/IrqAdc11PrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqAdcConfig/*[1]/IrqAdc11Config/IrqAdc11CatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of ADC11 interrupt Priority Setting for loop */!][!//

/*ADC11 interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdc11Config/IrqAdc11TosConfig/*))"!][!//
#define IRQ_ADC11_SR[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqAdcConfig/*[1]/IrqAdc11Config/IrqAdc11TosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqAdcConfig/*[1]/IrqAdc11Config/IrqAdc11PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdc11Config/IrqAdc11TosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//


[!IF "contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADCCG0' )"!][!//
/*ADC CG0 interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdcCG0Config/IrqAdcCG0CatConfig/*))"!][!//
#define IRQ_ADCCG0_SR[!"num:i($SrnId - 1)"!]_CAT          (IRQ_[!"IrqAdcConfig/*[1]/IrqAdcCG0Config/IrqAdcCG0CatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*ADC CG0 interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdcCG0Config/IrqAdcCG0PrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqAdcConfig/*[1]/IrqAdcCG0Config/IrqAdcCG0PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdcCG0Config/IrqAdcCG0TosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqAdcConfig/*[1]/IrqAdcCG0Config/IrqAdcCG0PrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_ADCCG0_SR[!"num:i($SrnId - 1)"!]_PRIO         [!"num:inttohex(IrqAdcConfig/*[1]/IrqAdcCG0Config/IrqAdcCG0PrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqAdcConfig/*[1]/IrqAdcCG0Config/IrqAdcCG0PrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqAdcConfig/*[1]/IrqAdcCG0Config/IrqAdcCG0CatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of ADC CG0 interrupt Priority Setting for loop */!][!//

/*ADC CG0 interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdcCG0Config/IrqAdcCG0TosConfig/*))"!][!//
#define IRQ_ADCCG0_SR[!"num:i($SrnId - 1)"!]_TOS          (IRQ_TOS_[!"IrqAdcConfig/*[1]/IrqAdcCG0Config/IrqAdcCG0TosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqAdcConfig/*[1]/IrqAdcCG0Config/IrqAdcCG0PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdcCG0Config/IrqAdcCG0TosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADCCG1' )"!][!//
/*ADC CG1 interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdcCG1Config/IrqAdcCG1CatConfig/*))"!][!//
#define IRQ_ADCCG1_SR[!"num:i($SrnId - 1)"!]_CAT          (IRQ_[!"IrqAdcConfig/*[1]/IrqAdcCG1Config/IrqAdcCG1CatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*ADC CG1 interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdcCG1Config/IrqAdcCG1PrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqAdcConfig/*[1]/IrqAdcCG1Config/IrqAdcCG1PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdcCG1Config/IrqAdcCG1TosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqAdcConfig/*[1]/IrqAdcCG1Config/IrqAdcCG1PrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_ADCCG1_SR[!"num:i($SrnId - 1)"!]_PRIO         [!"num:inttohex(IrqAdcConfig/*[1]/IrqAdcCG1Config/IrqAdcCG1PrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqAdcConfig/*[1]/IrqAdcCG1Config/IrqAdcCG1PrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqAdcConfig/*[1]/IrqAdcCG1Config/IrqAdcCG1CatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of ADC CG1 interrupt Priority Setting for loop */!][!//

/*ADC CG1 interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqAdcConfig/*[1]/IrqAdcCG1Config/IrqAdcCG1TosConfig/*))"!][!//
#define IRQ_ADCCG1_SR[!"num:i($SrnId - 1)"!]_TOS          (IRQ_TOS_[!"IrqAdcConfig/*[1]/IrqAdcCG1Config/IrqAdcCG1TosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqAdcConfig/*[1]/IrqAdcCG1Config/IrqAdcCG1PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqAdcConfig/*[1]/IrqAdcCG1Config/IrqAdcCG1TosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDIF!][!//


[!VAR "IrqGtmExist" = "'STD_OFF'"!][!//
[!IF "num:i(count(IrqGtmConfig/*)) = 1"!][!//
/*
                     Container : Irq GTM interruptConfiguration
*/
[!VAR "IrqGtmExist" = "'STD_ON'"!][!//
[!IF "contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmAei' )"!][!//
/* GTM AEI interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmAEI_Config/Irq_GtmAEICat_Config/*))"!][!//
#define IRQ_GTM_AEI_CAT             (IRQ_[!"IrqGtmConfig/*[1]/Irq_GtmAEI_Config/Irq_GtmAEICat_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* GTM AEI interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmAEI_Config/Irq_GtmAEIPrio_Config/*))"!][!//
[!VAR "Givenno" = "num:i(IrqGtmConfig/*[1]/Irq_GtmAEI_Config/Irq_GtmAEIPrio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmAEI_Config/Irq_GtmAEITos_Config/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqGtmConfig/*[1]/Irq_GtmAEI_Config/Irq_GtmAEIPrio_Config/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_GTM_AEI_PRIO            [!"num:inttohex(IrqGtmConfig/*[1]/Irq_GtmAEI_Config/Irq_GtmAEIPrio_Config/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqGtmConfig/*[1]/Irq_GtmAEI_Config/Irq_GtmAEIPrio_Config/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqGtmConfig/*[1]/Irq_GtmAEI_Config/Irq_GtmAEICat_Config/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of GTM AEI interrupt Priority Setting for loop */!][!//

/* GTM AEI interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmAEI_Config/Irq_GtmAEITos_Config/*))"!][!//
#define IRQ_GTM_AEI_TOS             (IRQ_TOS_[!"IrqGtmConfig/*[1]/Irq_GtmAEI_Config/Irq_GtmAEITos_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqGtmConfig/*[1]/Irq_GtmAEI_Config/Irq_GtmAEIPrio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmAEI_Config/Irq_GtmAEITos_Config/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmAru' )"!][!//
/* GTM ARU interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmARU_Config/Irq_GtmARUCat_Config/*))"!][!//
#define IRQ_GTM_ARU_SR[!"num:i($SrnId - 1)"!]_CAT         (IRQ_[!"IrqGtmConfig/*[1]/Irq_GtmARU_Config/Irq_GtmARUCat_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* GTM ARU interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmARU_Config/Irq_GtmARUPrio_Config/*))"!][!//
[!VAR "Givenno" = "num:i(IrqGtmConfig/*[1]/Irq_GtmARU_Config/Irq_GtmARUPrio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmARU_Config/Irq_GtmARUTos_Config/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqGtmConfig/*[1]/Irq_GtmARU_Config/Irq_GtmARUPrio_Config/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_GTM_ARU_SR[!"num:i($SrnId - 1)"!]_PRIO        [!"num:inttohex(IrqGtmConfig/*[1]/Irq_GtmARU_Config/Irq_GtmARUPrio_Config/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqGtmConfig/*[1]/Irq_GtmARU_Config/Irq_GtmARUPrio_Config/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqGtmConfig/*[1]/Irq_GtmARU_Config/Irq_GtmARUCat_Config/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of GTM ARU interrupt Priority Setting for loop */!][!//

/* GTM ARU interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmARU_Config/Irq_GtmARUTos_Config/*))"!][!//
#define IRQ_GTM_ARU_SR[!"num:i($SrnId - 1)"!]_TOS         (IRQ_TOS_[!"IrqGtmConfig/*[1]/Irq_GtmARU_Config/Irq_GtmARUTos_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqGtmConfig/*[1]/Irq_GtmARU_Config/Irq_GtmARUPrio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmARU_Config/Irq_GtmARUTos_Config/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//
                                                                                                           
[!IF "contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmBrc' )"!][!//
/* GTM BRC interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmBRC_Config/Irq_GtmBRCCat_Config/*))"!][!//
#define IRQ_GTM_BRC_CAT             (IRQ_[!"IrqGtmConfig/*[1]/Irq_GtmBRC_Config/Irq_GtmBRCCat_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* GTM BRC interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmBRC_Config/Irq_GtmBRCPrio_Config/*))"!][!//
[!VAR "Givenno" = "num:i(IrqGtmConfig/*[1]/Irq_GtmBRC_Config/Irq_GtmBRCPrio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmBRC_Config/Irq_GtmBRCTos_Config/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqGtmConfig/*[1]/Irq_GtmBRC_Config/Irq_GtmBRCPrio_Config/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_GTM_BRC_PRIO            [!"num:inttohex(IrqGtmConfig/*[1]/Irq_GtmBRC_Config/Irq_GtmBRCPrio_Config/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqGtmConfig/*[1]/Irq_GtmBRC_Config/Irq_GtmBRCPrio_Config/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqGtmConfig/*[1]/Irq_GtmBRC_Config/Irq_GtmBRCCat_Config/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of GTM BRC interrupt Priority Setting for loop */!][!//

/* GTM BRC interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmBRC_Config/Irq_GtmBRCTos_Config/*))"!][!//
#define IRQ_GTM_BRC_TOS             (IRQ_TOS_[!"IrqGtmConfig/*[1]/Irq_GtmBRC_Config/Irq_GtmBRCTos_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqGtmConfig/*[1]/Irq_GtmBRC_Config/Irq_GtmBRCPrio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmBRC_Config/Irq_GtmBRCTos_Config/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmCmp' )"!][!//
/* GTM CMP interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmCMP_Config/Irq_GtmCMPCat_Config/*))"!][!//
#define IRQ_GTM_CMP_CAT             (IRQ_[!"IrqGtmConfig/*[1]/Irq_GtmCMP_Config/Irq_GtmCMPCat_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* GTM CMP interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmCMP_Config/Irq_GtmCMPPrio_Config/*))"!][!//
[!VAR "Givenno" = "num:i(IrqGtmConfig/*[1]/Irq_GtmCMP_Config/Irq_GtmCMPPrio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmCMP_Config/Irq_GtmCMPTos_Config/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqGtmConfig/*[1]/Irq_GtmCMP_Config/Irq_GtmCMPPrio_Config/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_GTM_CMP_PRIO            [!"num:inttohex(IrqGtmConfig/*[1]/Irq_GtmCMP_Config/Irq_GtmCMPPrio_Config/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqGtmConfig/*[1]/Irq_GtmCMP_Config/Irq_GtmCMPPrio_Config/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqGtmConfig/*[1]/Irq_GtmCMP_Config/Irq_GtmCMPCat_Config/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of GTM CMP interrupt Priority Setting for loop */!][!//

/* GTM CMP interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmCMP_Config/Irq_GtmCMPTos_Config/*))"!][!//
#define IRQ_GTM_CMP_TOS             (IRQ_TOS_[!"IrqGtmConfig/*[1]/Irq_GtmCMP_Config/Irq_GtmCMPTos_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqGtmConfig/*[1]/Irq_GtmCMP_Config/Irq_GtmCMPPrio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmCMP_Config/Irq_GtmCMPTos_Config/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmSpe' )"!][!//
/* GTM SPE interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmSPE_Config/Irq_GtmSPECat_Config/*))"!][!//
#define IRQ_GTM_SPE[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqGtmConfig/*[1]/Irq_GtmSPE_Config/Irq_GtmSPECat_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* GTM SPE interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmSPE_Config/Irq_GtmSPEPrio_Config/*))"!][!//
[!VAR "Givenno" = "num:i(IrqGtmConfig/*[1]/Irq_GtmSPE_Config/Irq_GtmSPEPrio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmSPE_Config/Irq_GtmSPETos_Config/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqGtmConfig/*[1]/Irq_GtmSPE_Config/Irq_GtmSPEPrio_Config/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_GTM_SPE[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqGtmConfig/*[1]/Irq_GtmSPE_Config/Irq_GtmSPEPrio_Config/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqGtmConfig/*[1]/Irq_GtmSPE_Config/Irq_GtmSPEPrio_Config/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqGtmConfig/*[1]/Irq_GtmSPE_Config/Irq_GtmSPECat_Config/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of GTM SPE interrupt Priority Setting for loop */!][!//

/* GTM SPE interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmSPE_Config/Irq_GtmSPETos_Config/*))"!][!//
#define IRQ_GTM_SPE[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqGtmConfig/*[1]/Irq_GtmSPE_Config/Irq_GtmSPETos_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqGtmConfig/*[1]/Irq_GtmSPE_Config/Irq_GtmSPEPrio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmSPE_Config/Irq_GtmSPETos_Config/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmPsm0' )"!][!//
/* GTM PSM0 interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmPSM0_Config/Irq_GtmPSM0Cat_Config/*))"!][!//
#define IRQ_GTM_PSM0_SR[!"num:i($SrnId - 1)"!]_CAT        (IRQ_[!"IrqGtmConfig/*[1]/Irq_GtmPSM0_Config/Irq_GtmPSM0Cat_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* GTM PSM0 interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmPSM0_Config/Irq_GtmPSM0Prio_Config/*))"!][!//
[!VAR "Givenno" = "num:i(IrqGtmConfig/*[1]/Irq_GtmPSM0_Config/Irq_GtmPSM0Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmPSM0_Config/Irq_GtmPSM0Tos_Config/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqGtmConfig/*[1]/Irq_GtmPSM0_Config/Irq_GtmPSM0Prio_Config/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_GTM_PSM0_SR[!"num:i($SrnId - 1)"!]_PRIO       [!"num:inttohex(IrqGtmConfig/*[1]/Irq_GtmPSM0_Config/Irq_GtmPSM0Prio_Config/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqGtmConfig/*[1]/Irq_GtmPSM0_Config/Irq_GtmPSM0Prio_Config/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqGtmConfig/*[1]/Irq_GtmPSM0_Config/Irq_GtmPSM0Cat_Config/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of GTM PSM0 interrupt Priority Setting for loop */!][!//

/* GTM PSM0 interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmPSM0_Config/Irq_GtmPSM0Tos_Config/*))"!][!//
#define IRQ_GTM_PSM0_SR[!"num:i($SrnId - 1)"!]_TOS        (IRQ_TOS_[!"IrqGtmConfig/*[1]/Irq_GtmPSM0_Config/Irq_GtmPSM0Tos_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqGtmConfig/*[1]/Irq_GtmPSM0_Config/Irq_GtmPSM0Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmPSM0_Config/Irq_GtmPSM0Tos_Config/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmPsm1' )"!][!//
/* GTM PSM1 interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmPSM1_Config/Irq_GtmPSM1Cat_Config/*))"!][!//
#define IRQ_GTM_PSM1_SR[!"num:i($SrnId - 1)"!]_CAT        (IRQ_[!"IrqGtmConfig/*[1]/Irq_GtmPSM1_Config/Irq_GtmPSM1Cat_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* GTM PSM1 interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmPSM1_Config/Irq_GtmPSM1Prio_Config/*))"!][!//
[!VAR "Givenno" = "num:i(IrqGtmConfig/*[1]/Irq_GtmPSM1_Config/Irq_GtmPSM1Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmPSM1_Config/Irq_GtmPSM1Tos_Config/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqGtmConfig/*[1]/Irq_GtmPSM1_Config/Irq_GtmPSM1Prio_Config/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_GTM_PSM1_SR[!"num:i($SrnId - 1)"!]_PRIO       [!"num:inttohex(IrqGtmConfig/*[1]/Irq_GtmPSM1_Config/Irq_GtmPSM1Prio_Config/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqGtmConfig/*[1]/Irq_GtmPSM1_Config/Irq_GtmPSM1Prio_Config/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqGtmConfig/*[1]/Irq_GtmPSM1_Config/Irq_GtmPSM1Cat_Config/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of GTM PSM1 interrupt Priority Setting for loop */!][!//

/* GTM PSM1 interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmPSM1_Config/Irq_GtmPSM1Tos_Config/*))"!][!//
#define IRQ_GTM_PSM1_SR[!"num:i($SrnId - 1)"!]_TOS        (IRQ_TOS_[!"IrqGtmConfig/*[1]/Irq_GtmPSM1_Config/Irq_GtmPSM1Tos_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqGtmConfig/*[1]/Irq_GtmPSM1_Config/Irq_GtmPSM1Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmPSM1_Config/Irq_GtmPSM1Tos_Config/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmPsm2' )"!][!//
/* GTM PSM2 interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmPSM2_Config/Irq_GtmPSM2Cat_Config/*))"!][!//
#define IRQ_GTM_PSM2_SR[!"num:i($SrnId - 1)"!]_CAT        (IRQ_[!"IrqGtmConfig/*[1]/Irq_GtmPSM2_Config/Irq_GtmPSM2Cat_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* GTM PSM2 interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmPSM2_Config/Irq_GtmPSM2Prio_Config/*))"!][!//
[!VAR "Givenno" = "num:i(IrqGtmConfig/*[1]/Irq_GtmPSM2_Config/Irq_GtmPSM2Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmPSM2_Config/Irq_GtmPSM2Tos_Config/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqGtmConfig/*[1]/Irq_GtmPSM2_Config/Irq_GtmPSM2Prio_Config/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_GTM_PSM2_SR[!"num:i($SrnId - 1)"!]_PRIO       [!"num:inttohex(IrqGtmConfig/*[1]/Irq_GtmPSM2_Config/Irq_GtmPSM2Prio_Config/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqGtmConfig/*[1]/Irq_GtmPSM2_Config/Irq_GtmPSM2Prio_Config/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqGtmConfig/*[1]/Irq_GtmPSM2_Config/Irq_GtmPSM2Cat_Config/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of GTM PSM2 interrupt Priority Setting for loop */!][!//

/* GTM PSM2 interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmPSM2_Config/Irq_GtmPSM2Tos_Config/*))"!][!//
#define IRQ_GTM_PSM2_SR[!"num:i($SrnId - 1)"!]_TOS        (IRQ_TOS_[!"IrqGtmConfig/*[1]/Irq_GtmPSM2_Config/Irq_GtmPSM2Tos_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqGtmConfig/*[1]/Irq_GtmPSM2_Config/Irq_GtmPSM2Prio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmPSM2_Config/Irq_GtmPSM2Tos_Config/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmDpll' )"!][!//
/* GTM DPLL interrupt Category Setting */ 
[!FOR "Num" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmDPLL_Config/*))"!][!//
#define IRQ_GTM_DPLL_SR[!"substring-before(substring-after(node:name(IrqGtmConfig/*[1]/Irq_GtmDPLL_Config/*[num:i($Num)]),'Irq_GtmDPLLSR'),'_Config')"!]_CAT        (IRQ_[!"IrqGtmConfig/*[1]/Irq_GtmDPLL_Config/*[num:i($Num)]/Irq_GtmDPLLSR_Cat"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* GTM DPLL interrupt Priority Setting */  
[!FOR "Num" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmDPLL_Config/*))"!][!//
[!VAR "Givenno" = "num:i(IrqGtmConfig/*[1]/Irq_GtmDPLL_Config/*[num:i($Num)]/Irq_GtmDPLLSR_Prio)"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmDPLL_Config/*[num:i($Num)]/Irq_GtmDPLLSR_Tos"!][!//
[!VAR "cont" = "node:name(IrqGtmConfig/*[1]/Irq_GtmDPLL_Config/*[num:i($Num)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!IF "($Num <= 10)"!][!//
#define IRQ_GTM_DPLL_SR[!"substring-before(substring-after(node:name(IrqGtmConfig/*[1]/Irq_GtmDPLL_Config/*[num:i($Num)]),'Irq_GtmDPLLSR'),'_Config')"!]_PRIO       [!"num:inttohex(IrqGtmConfig/*[1]/Irq_GtmDPLL_Config/*[num:i($Num)]/Irq_GtmDPLLSR_Prio)"!][!CR!][!//
[!ELSE!][!//
#define IRQ_GTM_DPLL_SR[!"substring-before(substring-after(node:name(IrqGtmConfig/*[1]/Irq_GtmDPLL_Config/*[num:i($Num)]),'Irq_GtmDPLLSR'),'_Config')"!]_PRIO      [!"num:inttohex(IrqGtmConfig/*[1]/Irq_GtmDPLL_Config/*[num:i($Num)]/Irq_GtmDPLLSR_Prio)"!][!CR!][!//
[!ENDIF!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqGtmConfig/*[1]/Irq_GtmDPLL_Config/*[num:i($Num)]/Irq_GtmDPLLSR_Prio)"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqGtmConfig/*[1]/Irq_GtmDPLL_Config/*[num:i($Num)]/Irq_GtmDPLLSR_Cat"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of GTM DPLL interrupt Priority Setting for loop */!][!//

/* GTM DPLL interrupt type of service Setting */ 
[!FOR "Num" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmDPLL_Config/*))"!][!//
[!IF "($Num <= 10)"!][!//
#define IRQ_GTM_DPLL_SR[!"substring-before(substring-after(node:name(IrqGtmConfig/*[1]/Irq_GtmDPLL_Config/*[num:i($Num)]),'Irq_GtmDPLLSR'),'_Config')"!]_TOS        (IRQ_TOS_[!"IrqGtmConfig/*[1]/Irq_GtmDPLL_Config/*[num:i($Num)]/Irq_GtmDPLLSR_Tos"!])[!CR!][!//
[!ELSE!][!//
#define IRQ_GTM_DPLL_SR[!"substring-before(substring-after(node:name(IrqGtmConfig/*[1]/Irq_GtmDPLL_Config/*[num:i($Num)]),'Irq_GtmDPLLSR'),'_Config')"!]_TOS       (IRQ_TOS_[!"IrqGtmConfig/*[1]/Irq_GtmDPLL_Config/*[num:i($Num)]/Irq_GtmDPLLSR_Tos"!])[!CR!][!//
[!ENDIF!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqGtmConfig/*[1]/Irq_GtmDPLL_Config/*[num:i($Num)]/Irq_GtmDPLLSR_Prio)"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmDPLL_Config/*[num:i($Num)]/Irq_GtmDPLLSR_Tos"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmErr' )"!][!//
/* GTM ERR interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmERR_Config/Irq_GtmERRCat_Config/*))"!][!//
#define IRQ_GTM_ERR_SR_CAT          (IRQ_[!"IrqGtmConfig/*[1]/Irq_GtmERR_Config/Irq_GtmERRCat_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* GTM ERR interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmERR_Config/Irq_GtmERRPrio_Config/*))"!][!//
[!VAR "Givenno" = "num:i(IrqGtmConfig/*[1]/Irq_GtmERR_Config/Irq_GtmERRPrio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmERR_Config/Irq_GtmERRTos_Config/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqGtmConfig/*[1]/Irq_GtmERR_Config/Irq_GtmERRPrio_Config/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_GTM_ERR_SR_PRIO         [!"num:inttohex(IrqGtmConfig/*[1]/Irq_GtmERR_Config/Irq_GtmERRPrio_Config/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqGtmConfig/*[1]/Irq_GtmERR_Config/Irq_GtmERRPrio_Config/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqGtmConfig/*[1]/Irq_GtmERR_Config/Irq_GtmERRCat_Config/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of GTM ERR interrupt Priority Setting for loop */!][!//

/* GTM ERR interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmERR_Config/Irq_GtmERRTos_Config/*))"!][!//
#define IRQ_GTM_ERR_SR_TOS          (IRQ_TOS_[!"IrqGtmConfig/*[1]/Irq_GtmERR_Config/Irq_GtmERRTos_Config/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqGtmConfig/*[1]/Irq_GtmERR_Config/Irq_GtmERRPrio_Config/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmERR_Config/Irq_GtmERRTos_Config/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmTim' )"!][!//
[!FOR "Num" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmTIM_Config/*))"!][!//
/* GTM TIM[!"num:i($Num - 1)"!] interrupt Category Setting */  

[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmTIM_Config/*[num:i($Num)]/IrqGtmTIMCatConfig/*))"!][!//
#define IRQ_GTM_TIM[!"num:i($Num - 1)"!]_SR[!"num:i($SrnId - 1)"!]_CAT        (IRQ_[!"IrqGtmConfig/*[1]/Irq_GtmTIM_Config/*[num:i($Num)]/IrqGtmTIMCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
 
/* GTM TIM[!"num:i($Num - 1)"!] interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmTIM_Config/*[num:i($Num)]/IrqGtmTIMPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqGtmConfig/*[1]/Irq_GtmTIM_Config/*[num:i($Num)]/IrqGtmTIMPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmTIM_Config/*[num:i($Num)]/IrqGtmTIMTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqGtmConfig/*[1]/Irq_GtmTIM_Config/*[num:i($Num)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_GTM_TIM[!"num:i($Num - 1)"!]_SR[!"num:i($SrnId - 1)"!]_PRIO       [!"num:inttohex(IrqGtmConfig/*[1]/Irq_GtmTIM_Config/*[num:i($Num)]/IrqGtmTIMPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqGtmConfig/*[1]/Irq_GtmTIM_Config/*[num:i($Num)]/IrqGtmTIMPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqGtmConfig/*[1]/Irq_GtmTIM_Config/*[num:i($Num)]/IrqGtmTIMCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of GTM TIM interrupt Priority Setting for loop */!][!//

/* GTM TIM[!"num:i($Num - 1)"!] interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmTIM_Config/*[num:i($Num)]/IrqGtmTIMTosConfig/*))"!][!//
#define IRQ_GTM_TIM[!"num:i($Num - 1)"!]_SR[!"num:i($SrnId - 1)"!]_TOS        (IRQ_TOS_[!"IrqGtmConfig/*[1]/Irq_GtmTIM_Config/*[num:i($Num)]/IrqGtmTIMTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqGtmConfig/*[1]/Irq_GtmTIM_Config/*[num:i($Num)]/IrqGtmTIMPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmTIM_Config/*[num:i($Num)]/IrqGtmTIMTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmMcs' )"!][!//
[!FOR "Num" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmMCS_Config/*))"!][!//
/* GTM MCS[!"num:i($Num - 1)"!] interrupt Category Setting */  

[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmMCS_Config/*[num:i($Num)]/IrqGtmMCSCatConfig/*))"!][!//
#define IRQ_GTM_MCS[!"num:i($Num - 1)"!]_SR[!"num:i($SrnId - 1)"!]_CAT        (IRQ_[!"IrqGtmConfig/*[1]/Irq_GtmMCS_Config/*[num:i($Num)]/IrqGtmMCSCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
 
/* GTM MCS[!"num:i($Num - 1)"!] interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmMCS_Config/*[num:i($Num)]/IrqGtmMCSPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqGtmConfig/*[1]/Irq_GtmMCS_Config/*[num:i($Num)]/IrqGtmMCSPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmMCS_Config/*[num:i($Num)]/IrqGtmMCSTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqGtmConfig/*[1]/Irq_GtmMCS_Config/*[num:i($Num)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_GTM_MCS[!"num:i($Num - 1)"!]_SR[!"num:i($SrnId - 1)"!]_PRIO       [!"num:inttohex(IrqGtmConfig/*[1]/Irq_GtmMCS_Config/*[num:i($Num)]/IrqGtmMCSPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqGtmConfig/*[1]/Irq_GtmMCS_Config/*[num:i($Num)]/IrqGtmMCSPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqGtmConfig/*[1]/Irq_GtmMCS_Config/*[num:i($Num)]/IrqGtmMCSCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of GTM MCS0 interrupt Priority Setting for loop */!][!//

/* GTM MCS[!"num:i($Num - 1)"!] interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmMCS_Config/*[num:i($Num)]/IrqGtmMCSTosConfig/*))"!][!//
#define IRQ_GTM_MCS[!"num:i($Num - 1)"!]_SR[!"num:i($SrnId - 1)"!]_TOS        (IRQ_TOS_[!"IrqGtmConfig/*[1]/Irq_GtmMCS_Config/*[num:i($Num)]/IrqGtmMCSTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqGtmConfig/*[1]/Irq_GtmMCS_Config/*[num:i($Num)]/IrqGtmMCSPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmMCS_Config/*[num:i($Num)]/IrqGtmMCSTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmTom' )"!][!//
[!FOR "Num" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmTOM_Config/*))"!][!//
/* GTM TOM[!"num:i($Num - 1)"!] interrupt Category Setting */  

[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmTOM_Config/*[num:i($Num)]/IrqGtmTOMCatConfig/*))"!][!//
#define IRQ_GTM_TOM[!"num:i($Num - 1)"!]_SR[!"num:i($SrnId - 1)"!]_CAT        (IRQ_[!"IrqGtmConfig/*[1]/Irq_GtmTOM_Config/*[num:i($Num)]/IrqGtmTOMCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
 
/* GTM TOM[!"num:i($Num - 1)"!] interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmTOM_Config/*[num:i($Num)]/IrqGtmTOMPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqGtmConfig/*[1]/Irq_GtmTOM_Config/*[num:i($Num)]/IrqGtmTOMPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmTOM_Config/*[num:i($Num)]/IrqGtmTOMTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqGtmConfig/*[1]/Irq_GtmTOM_Config/*[num:i($Num)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_GTM_TOM[!"num:i($Num - 1)"!]_SR[!"num:i($SrnId - 1)"!]_PRIO       [!"num:inttohex(IrqGtmConfig/*[1]/Irq_GtmTOM_Config/*[num:i($Num)]/IrqGtmTOMPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqGtmConfig/*[1]/Irq_GtmTOM_Config/*[num:i($Num)]/IrqGtmTOMPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqGtmConfig/*[1]/Irq_GtmTOM_Config/*[num:i($Num)]/IrqGtmTOMCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of GTM TOM0 interrupt Priority Setting for loop */!][!//

/* GTM TOM[!"num:i($Num - 1)"!] interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmTOM_Config/*[num:i($Num)]/IrqGtmTOMTosConfig/*))"!][!//
#define IRQ_GTM_TOM[!"num:i($Num - 1)"!]_SR[!"num:i($SrnId - 1)"!]_TOS        (IRQ_TOS_[!"IrqGtmConfig/*[1]/Irq_GtmTOM_Config/*[num:i($Num)]/IrqGtmTOMTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqGtmConfig/*[1]/Irq_GtmTOM_Config/*[num:i($Num)]/IrqGtmTOMPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmTOM_Config/*[num:i($Num)]/IrqGtmTOMTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmAtom' )"!][!//
[!FOR "Num" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmATOM_Config/*))"!][!//
/* GTM ATOM[!"substring-before(substring-after(node:name(IrqGtmConfig/*[1]/Irq_GtmATOM_Config/*[num:i($Num)]),'Irq_GtmATOM'),'_Config')"!] interrupt Category Setting */  

[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmATOM_Config/*[num:i($Num)]/IrqGtmATOMCatConfig/*))"!][!//
#define IRQ_GTM_ATOM[!"substring-before(substring-after(node:name(IrqGtmConfig/*[1]/Irq_GtmATOM_Config/*[num:i($Num)]),'Irq_GtmATOM'),'_Config')"!]_SR[!"num:i($SrnId - 1)"!]_CAT        (IRQ_[!"IrqGtmConfig/*[1]/Irq_GtmATOM_Config/*[num:i($Num)]/IrqGtmATOMCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
 
/* GTM ATOM[!"substring-before(substring-after(node:name(IrqGtmConfig/*[1]/Irq_GtmATOM_Config/*[num:i($Num)]),'Irq_GtmATOM'),'_Config')"!] interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmATOM_Config/*[num:i($Num)]/IrqGtmATOMPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqGtmConfig/*[1]/Irq_GtmATOM_Config/*[num:i($Num)]/IrqGtmATOMPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmATOM_Config/*[num:i($Num)]/IrqGtmATOMTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqGtmConfig/*[1]/Irq_GtmATOM_Config/*[num:i($Num)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_GTM_ATOM[!"substring-before(substring-after(node:name(IrqGtmConfig/*[1]/Irq_GtmATOM_Config/*[num:i($Num)]),'Irq_GtmATOM'),'_Config')"!]_SR[!"num:i($SrnId - 1)"!]_PRIO       [!"num:inttohex(IrqGtmConfig/*[1]/Irq_GtmATOM_Config/*[num:i($Num)]/IrqGtmATOMPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqGtmConfig/*[1]/Irq_GtmATOM_Config/*[num:i($Num)]/IrqGtmATOMPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqGtmConfig/*[1]/Irq_GtmATOM_Config/*[num:i($Num)]/IrqGtmATOMCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of GTM ATOM0 interrupt Priority Setting for loop */!][!//

/* GTM ATOM[!"substring-before(substring-after(node:name(IrqGtmConfig/*[1]/Irq_GtmATOM_Config/*[num:i($Num)]),'Irq_GtmATOM'),'_Config')"!] interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmATOM_Config/*[num:i($Num)]/IrqGtmATOMTosConfig/*))"!][!//
#define IRQ_GTM_ATOM[!"substring-before(substring-after(node:name(IrqGtmConfig/*[1]/Irq_GtmATOM_Config/*[num:i($Num)]),'Irq_GtmATOM'),'_Config')"!]_SR[!"num:i($SrnId - 1)"!]_TOS        (IRQ_TOS_[!"IrqGtmConfig/*[1]/Irq_GtmATOM_Config/*[num:i($Num)]/IrqGtmATOMTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqGtmConfig/*[1]/Irq_GtmATOM_Config/*[num:i($Num)]/IrqGtmATOMPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmATOM_Config/*[num:i($Num)]/IrqGtmATOMTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmMcsw' )"!][!//
/* GTM MCSW interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmMCSW_Config/IrqGtmMCSWCatConfig/*))"!][!//
#define IRQ_GTM_MCSW[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqGtmConfig/*[1]/Irq_GtmMCSW_Config/IrqGtmMCSWCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* GTM MCSW interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmMCSW_Config/IrqGtmMCSWPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqGtmConfig/*[1]/Irq_GtmMCSW_Config/IrqGtmMCSWPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmMCSW_Config/IrqGtmMCSWTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqGtmConfig/*[1]/Irq_GtmMCSW_Config/IrqGtmMCSWPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_GTM_MCSW[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqGtmConfig/*[1]/Irq_GtmMCSW_Config/IrqGtmMCSWPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqGtmConfig/*[1]/Irq_GtmMCSW_Config/IrqGtmMCSWPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqGtmConfig/*[1]/Irq_GtmMCSW_Config/IrqGtmMCSWCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of GTM MCSW interrupt Priority Setting for loop */!][!//

/* GTM MCSW interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqGtmConfig/*[1]/Irq_GtmMCSW_Config/IrqGtmMCSWTosConfig/*))"!][!//
#define IRQ_GTM_MCSW[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqGtmConfig/*[1]/Irq_GtmMCSW_Config/IrqGtmMCSWTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqGtmConfig/*[1]/Irq_GtmMCSW_Config/IrqGtmMCSWPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqGtmConfig/*[1]/Irq_GtmMCSW_Config/IrqGtmMCSWTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!ENDIF!][!//
[!//

[!VAR "IrqStmExist" = "'STD_OFF'"!][!//
[!IF "num:i(count(IrqStmConfig/*)) = 1"!][!//
/*
                     Container : IrqSTMinterruptConfiguration
*/
[!VAR "IrqStmExist" = "'STD_ON'"!][!//
[!IF "contains( ecu:get('Irq.STMAvailable'), 'IrqSTM0' )"!][!//
/* STM0 interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqStmConfig/*[1]/IrqStm0Config/IrqStm0CatConfig/*))"!][!//
#define IRQ_STM0_SR[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqStmConfig/*[1]/IrqStm0Config/IrqStm0CatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* STM0 interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqStmConfig/*[1]/IrqStm0Config/IrqStm0PrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqStmConfig/*[1]/IrqStm0Config/IrqStm0PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqStmConfig/*[1]/IrqStm0Config/IrqStm0TosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqStmConfig/*[1]/IrqStm0Config/IrqStm0PrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_STM0_SR[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqStmConfig/*[1]/IrqStm0Config/IrqStm0PrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqStmConfig/*[1]/IrqStm0Config/IrqStm0PrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqStmConfig/*[1]/IrqStm0Config/IrqStm0CatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of STM0 interrupt Priority Setting for loop */!][!//

/* STM0 interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqStmConfig/*[1]/IrqStm0Config/IrqStm0TosConfig/*))"!][!//
#define IRQ_STM0_SR[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqStmConfig/*[1]/IrqStm0Config/IrqStm0TosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqStmConfig/*[1]/IrqStm0Config/IrqStm0PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqStmConfig/*[1]/IrqStm0Config/IrqStm0TosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.STMAvailable'), 'IrqSTM1' )"!][!//
/* STM1 interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqStmConfig/*[1]/IrqStm1Config/IrqStm1CatConfig/*))"!][!//
#define IRQ_STM1_SR[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqStmConfig/*[1]/IrqStm1Config/IrqStm1CatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* STM1 interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqStmConfig/*[1]/IrqStm1Config/IrqStm1PrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqStmConfig/*[1]/IrqStm1Config/IrqStm1PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqStmConfig/*[1]/IrqStm1Config/IrqStm1TosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqStmConfig/*[1]/IrqStm1Config/IrqStm1PrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_STM1_SR[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqStmConfig/*[1]/IrqStm1Config/IrqStm1PrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqStmConfig/*[1]/IrqStm1Config/IrqStm1PrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqStmConfig/*[1]/IrqStm1Config/IrqStm1CatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of STM1 interrupt Priority Setting for loop */!][!//

/* STM1 interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqStmConfig/*[1]/IrqStm1Config/IrqStm1TosConfig/*))"!][!//
#define IRQ_STM1_SR[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqStmConfig/*[1]/IrqStm1Config/IrqStm1TosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqStmConfig/*[1]/IrqStm1Config/IrqStm1PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqStmConfig/*[1]/IrqStm1Config/IrqStm1TosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.STMAvailable'), 'IrqSTM2' )"!][!//
/* STM2 interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqStmConfig/*[1]/IrqStm2Config/IrqStm2CatConfig/*))"!][!//
#define IRQ_STM2_SR[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqStmConfig/*[1]/IrqStm2Config/IrqStm2CatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* STM2 interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqStmConfig/*[1]/IrqStm2Config/IrqStm2PrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqStmConfig/*[1]/IrqStm2Config/IrqStm2PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqStmConfig/*[1]/IrqStm2Config/IrqStm2TosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqStmConfig/*[1]/IrqStm2Config/IrqStm2PrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_STM2_SR[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqStmConfig/*[1]/IrqStm2Config/IrqStm2PrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqStmConfig/*[1]/IrqStm2Config/IrqStm2PrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqStmConfig/*[1]/IrqStm2Config/IrqStm2CatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of STM2 interrupt Priority Setting for loop */!][!//

/* STM2 interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqStmConfig/*[1]/IrqStm2Config/IrqStm2TosConfig/*))"!][!//
#define IRQ_STM2_SR[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqStmConfig/*[1]/IrqStm2Config/IrqStm2TosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqStmConfig/*[1]/IrqStm2Config/IrqStm2PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqStmConfig/*[1]/IrqStm2Config/IrqStm2TosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.STMAvailable'), 'IrqSTM3' )"!][!//
/* STM3 interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqStmConfig/*[1]/IrqStm3Config/IrqStm3CatConfig/*))"!][!//
#define IRQ_STM3_SR[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqStmConfig/*[1]/IrqStm3Config/IrqStm3CatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* STM3 interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqStmConfig/*[1]/IrqStm3Config/IrqStm3PrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqStmConfig/*[1]/IrqStm3Config/IrqStm3PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqStmConfig/*[1]/IrqStm3Config/IrqStm3TosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqStmConfig/*[1]/IrqStm3Config/IrqStm3PrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_STM3_SR[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqStmConfig/*[1]/IrqStm3Config/IrqStm3PrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqStmConfig/*[1]/IrqStm3Config/IrqStm3PrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqStmConfig/*[1]/IrqStm3Config/IrqStm3CatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of STM3 interrupt Priority Setting for loop */!][!//

/* STM3 interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqStmConfig/*[1]/IrqStm3Config/IrqStm3TosConfig/*))"!][!//
#define IRQ_STM3_SR[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqStmConfig/*[1]/IrqStm3Config/IrqStm3TosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqStmConfig/*[1]/IrqStm3Config/IrqStm3PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqStmConfig/*[1]/IrqStm3Config/IrqStm3TosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.STMAvailable'), 'IrqSTM4' )"!][!//
/* STM4 interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqStmConfig/*[1]/IrqStm4Config/IrqStm4CatConfig/*))"!][!//
#define IRQ_STM4_SR[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqStmConfig/*[1]/IrqStm4Config/IrqStm4CatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* STM4 interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqStmConfig/*[1]/IrqStm4Config/IrqStm4PrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqStmConfig/*[1]/IrqStm4Config/IrqStm4PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqStmConfig/*[1]/IrqStm4Config/IrqStm4TosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqStmConfig/*[1]/IrqStm4Config/IrqStm4PrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_STM4_SR[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqStmConfig/*[1]/IrqStm4Config/IrqStm4PrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqStmConfig/*[1]/IrqStm4Config/IrqStm4PrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqStmConfig/*[1]/IrqStm4Config/IrqStm4CatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of STM4 interrupt Priority Setting for loop */!][!//

/* STM4 interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqStmConfig/*[1]/IrqStm4Config/IrqStm4TosConfig/*))"!][!//
#define IRQ_STM4_SR[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqStmConfig/*[1]/IrqStm4Config/IrqStm4TosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqStmConfig/*[1]/IrqStm4Config/IrqStm4PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqStmConfig/*[1]/IrqStm4Config/IrqStm4TosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.STMAvailable'), 'IrqSTM5' )"!][!//
/* STM5 interrupt Category Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqStmConfig/*[1]/IrqStm5Config/IrqStm5CatConfig/*))"!][!//
#define IRQ_STM5_SR[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqStmConfig/*[1]/IrqStm5Config/IrqStm5CatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//
                                                                                                           
/* STM5 interrupt Priority Setting */  
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqStmConfig/*[1]/IrqStm5Config/IrqStm5PrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqStmConfig/*[1]/IrqStm5Config/IrqStm5PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqStmConfig/*[1]/IrqStm5Config/IrqStm5TosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqStmConfig/*[1]/IrqStm5Config/IrqStm5PrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_STM5_SR[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqStmConfig/*[1]/IrqStm5Config/IrqStm5PrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqStmConfig/*[1]/IrqStm5Config/IrqStm5PrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqStmConfig/*[1]/IrqStm5Config/IrqStm5CatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of STM5 interrupt Priority Setting for loop */!][!//

/* STM5 interrupt type of service Setting */ 
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqStmConfig/*[1]/IrqStm5Config/IrqStm5TosConfig/*))"!][!//
#define IRQ_STM5_SR[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqStmConfig/*[1]/IrqStm5Config/IrqStm5TosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqStmConfig/*[1]/IrqStm5Config/IrqStm5PrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqStmConfig/*[1]/IrqStm5Config/IrqStm5TosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!ENDIF!][!//

[!VAR "IrqAsclinExist" = "'STD_OFF'"!][!//
[!IF "num:i(count(IrqASCLINConfig/*)) = 1"!][!//
/*
                     Container : IrqAsclin interruptConfiguration
*/
[!VAR "IrqAsclinExist" = "'STD_ON'"!][!//
[!//
/* Asclin Tx interrupt Category Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqASCLINConfig/*[1]/IrqAsclinCatConfig/IrqAsclinTxCatConfig/*))"!][!//
#define IRQ_ASCLIN[!"substring-before(substring-after(node:name(IrqASCLINConfig/*[1]/IrqAsclinCatConfig/IrqAsclinTxCatConfig/*[num:i($SrnId)]), 'IrqAsclin'), 'TxCat')"!]_TX_CAT            (IRQ_[!"IrqASCLINConfig/*[1]/IrqAsclinCatConfig/IrqAsclinTxCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/* Asclin Tx interrupt Priority Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqASCLINConfig/*[1]/IrqAsclinPrioConfig/IrqAsclinTxPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqASCLINConfig/*[1]/IrqAsclinPrioConfig/IrqAsclinTxPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqASCLINConfig/*[1]/IrqAsclinTosConfig/IrqAsclinTxTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqASCLINConfig/*[1]/IrqAsclinPrioConfig/IrqAsclinTxPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_ASCLIN[!"substring-before(substring-after(node:name(IrqASCLINConfig/*[1]/IrqAsclinPrioConfig/IrqAsclinTxPrioConfig/*[num:i($SrnId)]), 'IrqAsclin'), 'TxPrio')"!]_TX_PRIO           [!"num:inttohex(IrqASCLINConfig/*[1]/IrqAsclinPrioConfig/IrqAsclinTxPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//
[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OS_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//

[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqASCLINConfig/*[1]/IrqAsclinPrioConfig/IrqAsclinTxPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqASCLINConfig/*[1]/IrqAsclinCatConfig/IrqAsclinTxCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OS_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
	   Portnewa[!"$MIN_CAT1_LEVEL"!][!//
	   Portnewa[!"$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OS_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of ASCLINTX interrupt Priority Setting for loop */!][!//

/* Asclin Tx interrupt type of service Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqASCLINConfig/*[1]/IrqAsclinTosConfig/IrqAsclinTxTosConfig/*))"!][!//
#define IRQ_ASCLIN[!"substring-before(substring-after(node:name(IrqASCLINConfig/*[1]/IrqAsclinTosConfig/IrqAsclinTxTosConfig/*[num:i($SrnId)]), 'IrqAsclin'), 'TxTos')"!]_TX_TOS            (IRQ_TOS_[!"IrqASCLINConfig/*[1]/IrqAsclinTosConfig/IrqAsclinTxTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqASCLINConfig/*[1]/IrqAsclinPrioConfig/IrqAsclinTxPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqASCLINConfig/*[1]/IrqAsclinTosConfig/IrqAsclinTxTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//

/* Asclin Rx interrupt Category Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqASCLINConfig/*[1]/IrqAsclinCatConfig/IrqAsclinRxCatConfig/*))"!][!//
#define IRQ_ASCLIN[!"substring-before(substring-after(node:name(IrqASCLINConfig/*[1]/IrqAsclinCatConfig/IrqAsclinRxCatConfig/*[num:i($SrnId)]), 'IrqAsclin'), 'RxCat')"!]_RX_CAT            (IRQ_[!"IrqASCLINConfig/*[1]/IrqAsclinCatConfig/IrqAsclinRxCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/* Asclin Rx interrupt Priority Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqASCLINConfig/*[1]/IrqAsclinPrioConfig/IrqAsclinRxPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqASCLINConfig/*[1]/IrqAsclinPrioConfig/IrqAsclinRxPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqASCLINConfig/*[1]/IrqAsclinTosConfig/IrqAsclinRxTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqASCLINConfig/*[1]/IrqAsclinPrioConfig/IrqAsclinRxPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_ASCLIN[!"substring-before(substring-after(node:name(IrqASCLINConfig/*[1]/IrqAsclinPrioConfig/IrqAsclinRxPrioConfig/*[num:i($SrnId)]), 'IrqAsclin'), 'RxPrio')"!]_RX_PRIO           [!"num:inttohex(IrqASCLINConfig/*[1]/IrqAsclinPrioConfig/IrqAsclinRxPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//
[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OS_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//

[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqASCLINConfig/*[1]/IrqAsclinPrioConfig/IrqAsclinRxPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqASCLINConfig/*[1]/IrqAsclinCatConfig/IrqAsclinRxCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OS_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OS_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of ASCLINRX interrupt Priority Setting for loop */!][!//

/* Asclin Rx interrupt type of service Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqASCLINConfig/*[1]/IrqAsclinTosConfig/IrqAsclinRxTosConfig/*))"!][!//
#define IRQ_ASCLIN[!"substring-before(substring-after(node:name(IrqASCLINConfig/*[1]/IrqAsclinTosConfig/IrqAsclinRxTosConfig/*[num:i($SrnId)]), 'IrqAsclin'), 'RxTos')"!]_RX_TOS            (IRQ_TOS_[!"IrqASCLINConfig/*[1]/IrqAsclinTosConfig/IrqAsclinRxTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqASCLINConfig/*[1]/IrqAsclinPrioConfig/IrqAsclinRxPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqASCLINConfig/*[1]/IrqAsclinTosConfig/IrqAsclinRxTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//

/* Asclin Err interrupt Category Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqASCLINConfig/*[1]/IrqAsclinCatConfig/IrqAsclinErrCatConfig/*))"!][!//
#define IRQ_ASCLIN[!"substring-before(substring-after(node:name(IrqASCLINConfig/*[1]/IrqAsclinCatConfig/IrqAsclinErrCatConfig/*[num:i($SrnId)]), 'IrqAsclin'), 'ErrCat')"!]_ERR_CAT           (IRQ_[!"IrqASCLINConfig/*[1]/IrqAsclinCatConfig/IrqAsclinErrCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/* Asclin Err interrupt Priority Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqASCLINConfig/*[1]/IrqAsclinPrioConfig/IrqAsclinErrPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqASCLINConfig/*[1]/IrqAsclinPrioConfig/IrqAsclinErrPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqASCLINConfig/*[1]/IrqAsclinTosConfig/IrqAsclinErrTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqASCLINConfig/*[1]/IrqAsclinPrioConfig/IrqAsclinErrPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_ASCLIN[!"substring-before(substring-after(node:name(IrqASCLINConfig/*[1]/IrqAsclinPrioConfig/IrqAsclinErrPrioConfig/*[num:i($SrnId)]), 'IrqAsclin'), 'ErrPrio')"!]_ERR_PRIO          [!"num:inttohex(IrqASCLINConfig/*[1]/IrqAsclinPrioConfig/IrqAsclinErrPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//
[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OS_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//

[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqASCLINConfig/*[1]/IrqAsclinPrioConfig/IrqAsclinErrPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqASCLINConfig/*[1]/IrqAsclinCatConfig/IrqAsclinErrCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OS_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OS_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of ASCLINERR interrupt Priority Setting for loop */!][!//

/* Asclin Err interrupt type of service Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqASCLINConfig/*[1]/IrqAsclinTosConfig/IrqAsclinErrTosConfig/*))"!][!//
#define IRQ_ASCLIN[!"substring-before(substring-after(node:name(IrqASCLINConfig/*[1]/IrqAsclinTosConfig/IrqAsclinErrTosConfig/*[num:i($SrnId)]), 'IrqAsclin'), 'ErrTos')"!]_ERR_TOS           (IRQ_TOS_[!"IrqASCLINConfig/*[1]/IrqAsclinTosConfig/IrqAsclinErrTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqASCLINConfig/*[1]/IrqAsclinPrioConfig/IrqAsclinErrPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqASCLINConfig/*[1]/IrqAsclinTosConfig/IrqAsclinErrTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//


/*
                     Container : Irq HSSL configuration
*/

[!IF "contains( ecu:get('Irq.HsslAvailable'), 'IrqHssl0' )"!][!//
/*HSSl0 COK interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0CatConfig/IrqHssl0COKCatConfig/*))"!][!//
#define IRQ_HSSL0_COK[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0CatConfig/IrqHssl0COKCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*HSSl0 RDI interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0CatConfig/IrqHssl0RDICatConfig/*))"!][!//
#define IRQ_HSSL0_RDI[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0CatConfig/IrqHssl0RDICatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*HSSl0 ERR interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0CatConfig/IrqHssl0ERRCatConfig/*))"!][!//
#define IRQ_HSSL0_ERR[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0CatConfig/IrqHssl0ERRCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*HSSl0 TRG interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0CatConfig/IrqHssl0TRGCatConfig/*))"!][!//
#define IRQ_HSSL0_TRG[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0CatConfig/IrqHssl0TRGCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*HSSl0 EXI interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0CatConfig/IrqHssl0EXICatConfig/*))"!][!//
#define IRQ_HSSL0_EXI[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0CatConfig/IrqHssl0EXICatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*HSSL0 COK interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0COKPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0COKPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0TosConfig/IrqHssl0COKTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0COKPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_HSSL0_COK[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0COKPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0COKPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0CatConfig/IrqHssl0COKCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of HSSL0 COK interrupt Priority Setting for loop */!][!//

/*HSSL0 RDI interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0RDIPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0RDIPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0TosConfig/IrqHssl0RDITosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0RDIPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_HSSL0_RDI[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0RDIPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0RDIPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0CatConfig/IrqHssl0RDICatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of HSSL0 RDI interrupt Priority Setting for loop */!][!//

/*HSSL0 ERR interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0ERRPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0ERRPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0TosConfig/IrqHssl0ERRTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0ERRPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_HSSL0_ERR[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0ERRPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0ERRPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0CatConfig/IrqHssl0ERRCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of HSSL0 ERR interrupt Priority Setting for loop */!][!//

/*HSSL0 TRG interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0TRGPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0TRGPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0TosConfig/IrqHssl0TRGTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0TRGPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_HSSL0_TRG[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0TRGPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0TRGPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0CatConfig/IrqHssl0TRGCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of HSSL0 TRG interrupt Priority Setting for loop */!][!//

/*HSSL0 EXI interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0EXIPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0EXIPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0TosConfig/IrqHssl0EXITosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0EXIPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_HSSL0_EXI[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0EXIPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0EXIPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0CatConfig/IrqHssl0EXICatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of HSSL0 EXI interrupt Priority Setting for loop */!][!//

/*HSSL0 COK interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0TosConfig/IrqHssl0COKTosConfig/*))"!][!//
#define IRQ_HSSL0_COK[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0TosConfig/IrqHssl0COKTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0COKPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0TosConfig/IrqHssl0COKTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//

/*HSSL0 RDI interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0TosConfig/IrqHssl0RDITosConfig/*))"!][!//
#define IRQ_HSSL0_RDI[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0TosConfig/IrqHssl0RDITosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0RDIPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0TosConfig/IrqHssl0RDITosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//

/*HSSL0 ERR interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0TosConfig/IrqHssl0ERRTosConfig/*))"!][!//
#define IRQ_HSSL0_ERR[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0TosConfig/IrqHssl0ERRTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0ERRPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0TosConfig/IrqHssl0ERRTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//

/*HSSL0 TRG interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0TosConfig/IrqHssl0TRGTosConfig/*))"!][!//
#define IRQ_HSSL0_TRG[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0TosConfig/IrqHssl0TRGTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0TRGPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0TosConfig/IrqHssl0TRGTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//

/*HSSL0 EXI interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0TosConfig/IrqHssl0EXITosConfig/*))"!][!//
#define IRQ_HSSL0_EXI[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0TosConfig/IrqHssl0EXITosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0PrioConfig/IrqHssl0EXIPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqHsslConfig/*[1]/IrqHssl0Config/IrqHssl0TosConfig/IrqHssl0EXITosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//

[!ENDIF!][!//



[!IF "contains( ecu:get('Irq.HsslAvailable'), 'IrqHssl1' )"!][!//
/*HSSL1 COK interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1CatConfig/IrqHssl1COKCatConfig/*))"!][!//
#define IRQ_HSSL1_COK[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1CatConfig/IrqHssl1COKCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*HSSL1 RDI interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1CatConfig/IrqHssl1RDICatConfig/*))"!][!//
#define IRQ_HSSL1_RDI[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1CatConfig/IrqHssl1RDICatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*HSSL1 ERR interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1CatConfig/IrqHssl1ERRCatConfig/*))"!][!//
#define IRQ_HSSL1_ERR[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1CatConfig/IrqHssl1ERRCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*HSSL1 TRG interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1CatConfig/IrqHssl1TRGCatConfig/*))"!][!//
#define IRQ_HSSL1_TRG[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1CatConfig/IrqHssl1TRGCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*HSSL1 EXI interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1CatConfig/IrqHssl1EXICatConfig/*))"!][!//
#define IRQ_HSSL1_EXI[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1CatConfig/IrqHssl1EXICatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*HSSL1 COK interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1COKPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1COKPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1TosConfig/IrqHssl1COKTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1COKPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_HSSL1_COK[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1COKPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1COKPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1CatConfig/IrqHssl1COKCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of HSSL1 COK interrupt Priority Setting for loop */!][!//

/*HSSL1 RDI interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1RDIPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1RDIPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1TosConfig/IrqHssl1RDITosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1RDIPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_HSSL1_RDI[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1RDIPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1RDIPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1CatConfig/IrqHssl1RDICatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of HSSL1 RDI interrupt Priority Setting for loop */!][!//

/*HSSL1 ERR interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1ERRPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1ERRPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1TosConfig/IrqHssl1ERRTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1ERRPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_HSSL1_ERR[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1ERRPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1ERRPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1CatConfig/IrqHssl1ERRCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of HSSL1 ERR interrupt Priority Setting for loop */!][!//

/*HSSL1 TRG interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1TRGPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1TRGPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1TosConfig/IrqHssl1TRGTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1TRGPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_HSSL1_TRG[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1TRGPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1TRGPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1CatConfig/IrqHssl1TRGCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of HSSL1 TRG interrupt Priority Setting for loop */!][!//

/*HSSL1 EXI interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1EXIPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1EXIPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1TosConfig/IrqHssl1EXITosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1EXIPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_HSSL1_EXI[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1EXIPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1EXIPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1CatConfig/IrqHssl1EXICatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of HSSL1 EXI interrupt Priority Setting for loop */!][!//

/*HSSL1 COK interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1TosConfig/IrqHssl1COKTosConfig/*))"!][!//
#define IRQ_HSSL1_COK[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1TosConfig/IrqHssl1COKTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1COKPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1TosConfig/IrqHssl1COKTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//

/*HSSL1 RDI interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1TosConfig/IrqHssl1RDITosConfig/*))"!][!//
#define IRQ_HSSL1_RDI[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1TosConfig/IrqHssl1RDITosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1RDIPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1TosConfig/IrqHssl1RDITosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//

/*HSSL1 ERR interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1TosConfig/IrqHssl1ERRTosConfig/*))"!][!//
#define IRQ_HSSL1_ERR[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1TosConfig/IrqHssl1ERRTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1ERRPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1TosConfig/IrqHssl1ERRTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//

/*HSSL1 TRG interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1TosConfig/IrqHssl1TRGTosConfig/*))"!][!//
#define IRQ_HSSL1_TRG[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1TosConfig/IrqHssl1TRGTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1TRGPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1TosConfig/IrqHssl1TRGTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//

/*HSSL1 EXI interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1TosConfig/IrqHssl1EXITosConfig/*))"!][!//
#define IRQ_HSSL1_EXI[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1TosConfig/IrqHssl1EXITosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1PrioConfig/IrqHssl1EXIPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqHsslConfig/*[1]/IrqHssl1Config/IrqHssl1TosConfig/IrqHssl1EXITosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//

[!ENDIF!][!//





[!//  SENT configuration
[!VAR "IrqSentExist" = "'STD_OFF'"!][!//
[!IF "num:i(count(IrqSentConfig/*)) = 1"!][!//

/*
                     Container : Irq SENT configuration
*/
[!VAR "IrqSentExist" = "'STD_ON'"!][!//
/*Sent interrupt Category setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqSentConfig/*[1]/IrqSentCatConfig/*))"!][!//
#define IRQ_SENT_SR[!"num:i($SrnId - 1)"!]_CAT            (IRQ_[!"IrqSentConfig/*[1]/IrqSentCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/*Sent interrupt Priority setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqSentConfig/*[1]/IrqSentPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqSentConfig/*[1]/IrqSentPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqSentConfig/*[1]/IrqSentTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqSentConfig/*[1]/IrqSentPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_SENT_SR[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqSentConfig/*[1]/IrqSentPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//

[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OSEK_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//
[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqSentConfig/*[1]/IrqSentPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqSentConfig/*[1]/IrqSentCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OSEK_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OSEK_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of Sent interrupt Priority Setting for loop */!][!//

/*Sent interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqSentConfig/*[1]/IrqSentTosConfig/*))"!][!//
#define IRQ_SENT_SR[!"num:i($SrnId - 1)"!]_TOS            (IRQ_TOS_[!"IrqSentConfig/*[1]/IrqSentTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqSentConfig/*[1]/IrqSentPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqSentConfig/*[1]/IrqSentTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//
[!ENDIF!][!//

[!VAR "IrqDsadcExist" = "'STD_OFF'"!][!//
[!IF "num:i(count(IrqDsadcConfig/*)) = 1"!][!//
/*
                     Container : IrqDsadc interruptConfiguration
*/
[!VAR "IrqDsadcExist" = "'STD_ON'"!][!//
[!//
/* Dsadc RM interrupt Category Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqDsadcConfig/*[1]/IrqDsadcCatConfig/IrqDsadcSRMCatConfig/*))"!][!//
#define IRQ_DSADC_SRM[!"substring-before(substring-after(node:name(IrqDsadcConfig/*[1]/IrqDsadcCatConfig/IrqDsadcSRMCatConfig/*[num:i($SrnId)]), 'IrqDSAdcSRM'),'Cat')"!]_CAT            (IRQ_[!"IrqDsadcConfig/*[1]/IrqDsadcCatConfig/IrqDsadcSRMCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/* Dsadc RM interrupt Priority Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqDsadcConfig/*[1]/IrqDsadcPrioConfig/IrqDsadcSRMPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqDsadcConfig/*[1]/IrqDsadcPrioConfig/IrqDsadcSRMPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqDsadcConfig/*[1]/IrqDsadcTosConfig/IrqDsadcSRMTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqDsadcConfig/*[1]/IrqDsadcPrioConfig/IrqDsadcSRMPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_DSADC_SRM[!"substring-before(substring-after(node:name(IrqDsadcConfig/*[1]/IrqDsadcPrioConfig/IrqDsadcSRMPrioConfig/*[num:i($SrnId)]), 'IrqDsadcSRM'),'Prio')"!]_PRIO           [!"num:inttohex(IrqDsadcConfig/*[1]/IrqDsadcPrioConfig/IrqDsadcSRMPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//
[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OS_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//

[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqDsadcConfig/*[1]/IrqDsadcPrioConfig/IrqDsadcSRMPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqDsadcConfig/*[1]/IrqDsadcCatConfig/IrqDsadcSRMCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OS_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
	   Portnewa[!"$MIN_CAT1_LEVEL"!][!//
	   Portnewa[!"$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OS_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of DSADCTX interrupt Priority Setting for loop */!][!//

/* Dsadc RM interrupt type of service Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqDsadcConfig/*[1]/IrqDsadcTosConfig/IrqDsadcSRMTosConfig/*))"!][!//
#define IRQ_DSADC_SRM[!"substring-before(substring-after(node:name(IrqDsadcConfig/*[1]/IrqDsadcTosConfig/IrqDsadcSRMTosConfig/*[num:i($SrnId)]),'IrqDsadcSRM'),'Tos')"!]_TOS            (IRQ_TOS_[!"IrqDsadcConfig/*[1]/IrqDsadcTosConfig/IrqDsadcSRMTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqDsadcConfig/*[1]/IrqDsadcPrioConfig/IrqDsadcSRMPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqDsadcConfig/*[1]/IrqDsadcTosConfig/IrqDsadcSRMTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//

/* Dsadc RA interrupt Category Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqDsadcConfig/*[1]/IrqDsadcCatConfig/IrqDsadcSRACatConfig/*))"!][!//
#define IRQ_DSADC_SRA[!"substring-before(substring-after(node:name(IrqDsadcConfig/*[1]/IrqDsadcCatConfig/IrqDsadcSRACatConfig/*[num:i($SrnId)]),'IrqDSAdcSRA'),'Cat')"!]_CAT            (IRQ_[!"IrqDsadcConfig/*[1]/IrqDsadcCatConfig/IrqDsadcSRACatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//

/* Dsadc RA interrupt Priority Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqDsadcConfig/*[1]/IrqDsadcPrioConfig/IrqDsadcSRAPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqDsadcConfig/*[1]/IrqDsadcPrioConfig/IrqDsadcSRAPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqDsadcConfig/*[1]/IrqDsadcTosConfig/IrqDsadcSRATosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqDsadcConfig/*[1]/IrqDsadcPrioConfig/IrqDsadcSRAPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_DSADC_SRA[!"substring-before(substring-after(node:name(IrqDsadcConfig/*[1]/IrqDsadcPrioConfig/IrqDsadcSRAPrioConfig/*[num:i($SrnId)]),'IrqDsadcSRA'),'Prio')"!]_PRIO           [!"num:inttohex(IrqDsadcConfig/*[1]/IrqDsadcPrioConfig/IrqDsadcSRAPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//
[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OS_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//

[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqDsadcConfig/*[1]/IrqDsadcPrioConfig/IrqDsadcSRAPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqDsadcConfig/*[1]/IrqDsadcCatConfig/IrqDsadcSRACatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OS_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
	   Portnewa[!"$MIN_CAT1_LEVEL"!][!//
	   Portnewa[!"$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OS_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of DSADCTX interrupt Priority Setting for loop */!][!//

/* Dsadc RA interrupt type of service Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqDsadcConfig/*[1]/IrqDsadcTosConfig/IrqDsadcSRATosConfig/*))"!][!//
#define IRQ_DSADC_SRA[!"substring-before(substring-after(node:name(IrqDsadcConfig/*[1]/IrqDsadcTosConfig/IrqDsadcSRATosConfig/*[num:i($SrnId)]),'IrqDsadcSRA'),'Tos')"!]_TOS            (IRQ_TOS_[!"IrqDsadcConfig/*[1]/IrqDsadcTosConfig/IrqDsadcSRATosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqDsadcConfig/*[1]/IrqDsadcPrioConfig/IrqDsadcSRAPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqDsadcConfig/*[1]/IrqDsadcTosConfig/IrqDsadcSRATosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//


[!ENDIF!][!//



[!IF "num:i(count(IrqI2cConfig/*)) = 1"!][!//
/*
                     Container : I2C interrupt Configuration
*/
/* I2C interrupt Category Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqI2cConfig/*[1]/IrqI2cCatConfig/IrqI2cDtrCatConfig/*))"!][!//
#define IRQ_I2C_DTR_SR[!"num:i($SrnId - 1)"!]_CAT         (IRQ_[!"IrqI2cConfig/*[1]/IrqI2cCatConfig/IrqI2cDtrCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//


[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqI2cConfig/*[1]/IrqI2cCatConfig/IrqI2cErrCatConfig/*))"!][!//
#define IRQ_I2C_ERR_SR[!"num:i($SrnId - 1)"!]_CAT         (IRQ_[!"IrqI2cConfig/*[1]/IrqI2cCatConfig/IrqI2cErrCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//


[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqI2cConfig/*[1]/IrqI2cCatConfig/IrqI2cPCatConfig/*))"!][!//
#define IRQ_I2C_P_SR[!"num:i($SrnId - 1)"!]_CAT           (IRQ_[!"IrqI2cConfig/*[1]/IrqI2cCatConfig/IrqI2cPCatConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!ENDFOR!][!//


/* I2C Dtr interrupt Priority Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqI2cConfig/*[1]/IrqI2cPrioConfig/IrqI2cDtrPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqI2cConfig/*[1]/IrqI2cPrioConfig/IrqI2cDtrPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqI2cConfig/*[1]/IrqI2cTosConfig/IrqI2cDtrTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqI2cConfig/*[1]/IrqI2cPrioConfig/IrqI2cErrPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_I2C_DTR_SR[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqI2cConfig/*[1]/IrqI2cPrioConfig/IrqI2cDtrPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//
[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OS_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//

[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqI2cConfig/*[1]/IrqI2cPrioConfig/IrqI2cDtrPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqI2cConfig/*[1]/IrqI2cCatConfig/IrqI2cDtrCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OS_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
	   Portnewa[!"$MIN_CAT1_LEVEL"!][!//
	   Portnewa[!"$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OS_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of I2C DTR interrupt Priority Setting for loop */!][!//


/* I2C Err interrupt Priority Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqI2cConfig/*[1]/IrqI2cPrioConfig/IrqI2cErrPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqI2cConfig/*[1]/IrqI2cPrioConfig/IrqI2cErrPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqI2cConfig/*[1]/IrqI2cTosConfig/IrqI2cErrTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqI2cConfig/*[1]/IrqI2cPrioConfig/IrqI2cErrPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_I2C_ERR_SR[!"num:i($SrnId - 1)"!]_PRIO           [!"num:inttohex(IrqI2cConfig/*[1]/IrqI2cPrioConfig/IrqI2cErrPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//
[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OS_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//

[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqI2cConfig/*[1]/IrqI2cPrioConfig/IrqI2cErrPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqI2cConfig/*[1]/IrqI2cCatConfig/IrqI2cErrCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OS_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
	   Portnewa[!"$MIN_CAT1_LEVEL"!][!//
	   Portnewa[!"$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OS_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of I2C Err interrupt Priority Setting for loop */!][!//


/* I2C Protocol interrupt Priority Setting*/
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqI2cConfig/*[1]/IrqI2cPrioConfig/IrqI2cPPrioConfig/*))"!][!//
[!VAR "Givenno" = "num:i(IrqI2cConfig/*[1]/IrqI2cPrioConfig/IrqI2cPPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqI2cConfig/*[1]/IrqI2cTosConfig/IrqI2cPTosConfig/*[num:i($SrnId)]"!][!//
[!VAR "cont" = "node:name(IrqI2cConfig/*[1]/IrqI2cPrioConfig/IrqI2cPPrioConfig/*[num:i($SrnId)])"!][!//
[!NOCODE!][!//
[!IF "$TypeOfService != 'DMA'"!][!//
[!CALL "CG_PriorityCheck", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ELSE!][!//
[!CALL "CG_PriorityCheckDma", "Givenno" = "$Givenno","cont" = "$cont"!][!// 
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define IRQ_I2C_P_SR[!"num:i($SrnId - 1)"!]_PRIO             [!"num:inttohex(IrqI2cConfig/*[1]/IrqI2cPrioConfig/IrqI2cPPrioConfig/*[num:i($SrnId)])"!][!CR!][!//
[!NOCODE!][!//
[!/* Following lines of code is used to test if Priority of Category 2 Interrupts 
     is Less than the lowest priority of Catagory 1 Interrupts  */!][!//
[!/* Check only if IRQ_OS_ENABLE is ON */!][!//
[!IF "(IrqGeneral/IrqOsekEnable = 'true')"!][!//

[!/* Assign current priority to variable "PRIORITY" */!][!//
[!VAR "PRIORITY" = "num:i(IrqI2cConfig/*[1]/IrqI2cPrioConfig/IrqI2cPPrioConfig/*[num:i($SrnId)])"!][!//  
 [!/* Assign current category to variable "CATEGORY" */!][!//
 [!VAR "CATEGORY" = "IrqI2cConfig/*[1]/IrqI2cCatConfig/IrqI2cPCatConfig/*[num:i($SrnId)]"!][!//
   [!/* Check if Priority value 1 and 2 are not used if IRQ_OS_ENABLE is ON */!][!//
   [!IF "((num:i($PRIORITY) = num:i(1))or (num:i($PRIORITY)= num:i(2)))"!][!//
     [!WARNING "Priority 1 and 2 of CPU Interrupts are used by OSEK for Task Switching!"!][!//
   [!ENDIF!][!//
      [!/* If TypeOfService is DMA then relax the checking of CAT1 and CAT2 */!][!//   
[!IF "$TypeOfService != 'DMA'"!][!//
[!/* Check if current category is "CAT1" */!][!//
   [!IF "($CATEGORY) = 'CAT1'"!][!//
    [!/* Check if priority is less than MIN_CAT1_LEVEL */!][!// 
    [!IF "((num:i($PRIORITY) < num:i($MIN_CAT1_LEVEL))and(num:i($PRIORITY)!= 0))"!][!//
      [!/* Reassign MIN_CAT1_LEVEL with current priority  */!][!// 
      [!VAR "MIN_CAT1_LEVEL" = "$PRIORITY"!][!//
	   Portnewa[!"$MIN_CAT1_LEVEL"!][!//
	   Portnewa[!"$PRIORITY"!][!//
    [!ENDIF!][!//
   [!/* Check if current category is "CAT2" */!][!//
   [!ELSEIF "($CATEGORY) ='CAT2'"!][!//
    [!/* Check if priority is greater than MAX_CAT2_LEVEL reassign MAX_CAT2_LEVEL with current priority  */!][!//
    [!IF "((num:i($PRIORITY) > num:i($MAX_CAT2_LEVEL))and(num:i($PRIORITY)!= num:i(0)))"!][!//
      [!/* Reassign MAX_CAT2_LEVEL with current priority  */!][!//
      [!VAR "MAX_CAT2_LEVEL" = "$PRIORITY "!][!//
    [!ENDIF!][!//
   [!ENDIF!][!//    
   [!IF "num:i($MIN_CAT1_LEVEL) <= num:i($MAX_CAT2_LEVEL)"!][!//
   [!ERROR!][!//
     Priority of Category 2 Interrupts should be Less than lowest priority of Catagory 1 Interrupts!
   [!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!/* End of "TypeOfService is DMA then relax the checking of CAT1 and CAT2" */!][!//
[!ENDIF!][!/* End of "Check only if IRQ_OS_ENABLE is ON " */!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!/* End of I2C Protocol interrupt Priority Setting for loop */!][!//

/* I2C Err interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqI2cConfig/*[1]/IrqI2cTosConfig/IrqI2cDtrTosConfig/*))"!][!//
#define IRQ_I2C_DTR_SR[!"num:i($SrnId - 1)"!]_TOS           (IRQ_TOS_[!"IrqI2cConfig/*[1]/IrqI2cTosConfig/IrqI2cDtrTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqI2cConfig/*[1]/IrqI2cPrioConfig/IrqI2cDtrPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqI2cConfig/*[1]/IrqI2cTosConfig/IrqI2cDtrTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//

/* I2C Err interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqI2cConfig/*[1]/IrqI2cTosConfig/IrqI2cErrTosConfig/*))"!][!//
#define IRQ_I2C_ERR_SR[!"num:i($SrnId - 1)"!]_TOS           (IRQ_TOS_[!"IrqI2cConfig/*[1]/IrqI2cTosConfig/IrqI2cErrTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqI2cConfig/*[1]/IrqI2cPrioConfig/IrqI2cErrPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqI2cConfig/*[1]/IrqI2cTosConfig/IrqI2cErrTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//

/* I2C Err interrupt type of service setting */
[!FOR "SrnId" ="num:i(1)" TO "num:i(count(IrqI2cConfig/*[1]/IrqI2cTosConfig/IrqI2cPTosConfig/*))"!][!//
#define IRQ_I2C_P_SR[!"num:i($SrnId - 1)"!]_TOS           (IRQ_TOS_[!"IrqI2cConfig/*[1]/IrqI2cTosConfig/IrqI2cPTosConfig/*[num:i($SrnId)]"!])[!CR!][!//
[!NOCODE!][!//
[!VAR "PrioVal" = "num:i(IrqI2cConfig/*[1]/IrqI2cPrioConfig/IrqI2cPPrioConfig/*[num:i($SrnId)])"!][!//
[!VAR "TypeOfService" = "IrqI2cConfig/*[1]/IrqI2cTosConfig/IrqI2cPTosConfig/*[num:i($SrnId)]"!][!//
[!IF "$TypeOfService = 'DMA'"!][!//
[!IF "num:i($PrioVal) > num:i($DmaMaxPrio)"!][!//
[!ERROR!][//
	Type of service is selected as DMA for [!"$cont"!]_SR[!"num:i($SrnId - 1)"!] and the priority is configured as [!"num:i($PrioVal)"!]. Priority should not be more than [!"num:i($DmaMaxPrio)"!]!
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDFOR!][!//

[!ENDIF!][!/* End of I2C interrupt */!] [!//

[!VAR "ModAdded" = "'false'"!][!//
[!SELECT "as:modconf('Spi')[1]"!][!//
[!VAR "ModAdded" = "'true'"!][!//
[!ENDSELECT!][!//
[!//
[!IF "($ModAdded = 'true')"!][!//
#define IRQ_QSPI_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_QSPI_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.QspiSrnAvailable'), 'IrqQspi0' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_QSPI0_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_QSPI0_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.QspiSrnAvailable'), 'IrqQspi1' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_QSPI1_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_QSPI1_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.QspiSrnAvailable'), 'IrqQspi2' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_QSPI2_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_QSPI2_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.QspiSrnAvailable'), 'IrqQspi3' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_QSPI3_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_QSPI3_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.QspiSrnAvailable'), 'IrqQspi4' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_QSPI4_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_QSPI4_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.QspiSrnAvailable'), 'IrqQspi5' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_QSPI5_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_QSPI5_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "ecu:get('Irq.QspiHCSrnAvailable') = ''"!][!//
#define IRQ_QSPI_HC_SRN_EXIST       (STD_OFF)
[!ELSE!][!//
#define IRQ_QSPI_HC_SRN_EXIST       (STD_ON)
[!ENDIF!][!//


[!VAR "ModAdded" = "'false'"!][!//
[!SELECT "as:modconf('Icu')[1]"!][!//
[!VAR "ModAdded" = "'true'"!][!//
[!ENDSELECT!][!//
[!SELECT "as:modconf('Pwm')[1]"!][!//
[!VAR "ModAdded" = "'true'"!][!//
[!ENDSELECT!][!//
[!//
[!IF "($ModAdded = 'true')"!][!//
#define IRQ_CCU6_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CCU6_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.CCU6Available'), 'IrqCCU60' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CCU60_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_CCU60_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.CCU6Available'), 'IrqCCU61' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CCU61_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_CCU61_EXIST             (STD_OFF)
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.ModAvailable'), 'IrqGpt' )"!][!//
#define IRQ_GPT12_EXIST               (STD_ON)
[!ELSE!][!//
#define IRQ_GPT12_EXIST               (STD_OFF)
[!ENDIF!][!//
[!IF "contains( ecu:get('Irq.GPT12Available'), 'IrqGPT120' )"!][!//
#define IRQ_GPT120_EXIST            (STD_ON)
[!ELSE!][!//
#define IRQ_GPT120_EXIST            (STD_OFF)
[!ENDIF!][!//
[!/* STM timer is used by STM or WDG. If STM or WDG module is configured STM is enabled */!]
[!VAR "ModAdded" = "'false'"!][!//
[!SELECT "as:modconf('Wdg')[1]"!][!//
[!VAR "ModAdded" = "'true'"!][!//
[!ENDSELECT!][!//
[!//
[!SELECT "as:modconf('Stm')[1]"!][!//
[!VAR "ModAdded" = "'true'"!][!//
[!ENDSELECT!][!//
[!//
[!IF "($ModAdded = 'true')"!][!//
#define IRQ_STM_EXIST               (STD_ON)
[!ELSE!][!//
#define IRQ_STM_EXIST               (STD_OFF)
[!ENDIF!][!//
[!IF "contains( ecu:get('Irq.STMAvailable'), 'IrqSTM0' )"!][!//
#define IRQ_STM0_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_STM0_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "contains( ecu:get('Irq.STMAvailable'), 'IrqSTM1' )"!][!//
#define IRQ_STM1_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_STM1_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "contains( ecu:get('Irq.STMAvailable'), 'IrqSTM2' )"!][!//
#define IRQ_STM2_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_STM2_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "contains( ecu:get('Irq.STMAvailable'), 'IrqSTM3' )"!][!//
#define IRQ_STM3_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_STM3_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "contains( ecu:get('Irq.STMAvailable'), 'IrqSTM4' )"!][!//
#define IRQ_STM4_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_STM4_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "contains( ecu:get('Irq.STMAvailable'), 'IrqSTM5' )"!][!//
#define IRQ_STM5_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_STM5_EXIST              (STD_OFF)
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.ModAvailable'), 'IrqDma' )"!][!//
#define IRQ_DMA_EXIST               (STD_ON)
[!ELSE!][!//
#define IRQ_DMA_EXIST               (STD_OFF)
[!ENDIF!][!//
[!IF "contains( ecu:get('Irq.NoOfDmaChannels'), 'IrqDMAErr0To3' )"!][!//
#define IRQ_DMA_ERR0TO3_EXIST       (STD_ON)
[!ELSE!][!//
#define IRQ_DMA_ERR0TO3_EXIST       (STD_OFF)
[!ENDIF!][!//
[!IF "contains( ecu:get('Irq.NoOfDmaChannels'), 'IrqDmaCh0To15' )"!][!//
#define IRQ_DMA_CH0TO15_EXIST       (STD_ON)
[!ELSE!][!//
#define IRQ_DMA_CH0TO15_EXIST       (STD_OFF)
[!ENDIF!][!//
[!IF "contains( ecu:get('Irq.NoOfDmaChannels'), 'IrqDmaCh16To63' )"!][!//
#define IRQ_DMA_CH16TO63_EXIST      (STD_ON)
[!ELSE!][!//
#define IRQ_DMA_CH16TO63_EXIST      (STD_OFF)
[!ENDIF!][!//
[!IF "contains( ecu:get('Irq.NoOfDmaChannels'), 'IrqDmaCh64To127' )"!][!//
#define IRQ_DMA_CH64TO127_EXIST     (STD_ON)
[!ELSE!][!//
#define IRQ_DMA_CH64TO127_EXIST     (STD_OFF)
[!ENDIF!][!//

[!VAR "ModAdded" = "'false'"!][!//
[!SELECT "as:modconf('Eth')[1]"!][!//
[!VAR "ModAdded" = "'true'"!][!//
[!ENDSELECT!][!//
[!//
[!IF "($ModAdded = 'true')"!][!//
#define IRQ_ETH_EXIST               (STD_ON)
[!ELSE!][!//
#define IRQ_ETH_EXIST               (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.EthSrnAvailable'), 'IrqEth0' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ETH0_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_ETH0_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.EthSrnAvailable'), 'IrqEth1' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ETH1_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_ETH1_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.EthSrnAvailable'), 'IrqEth2' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ETH2_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_ETH2_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.EthSrnAvailable'), 'IrqEth3' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ETH3_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_ETH3_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.EthSrnAvailable'), 'IrqEth4' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ETH4_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_ETH4_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.EthSrnAvailable'), 'IrqEth5' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ETH5_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_ETH5_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.EthSrnAvailable'), 'IrqEth6' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ETH6_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_ETH6_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.EthSrnAvailable'), 'IrqEth7' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ETH7_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_ETH7_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.EthSrnAvailable'), 'IrqEth8' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ETH8_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_ETH8_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.EthSrnAvailable'), 'IrqEth9' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ETH9_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_ETH9_EXIST              (STD_OFF)
[!ENDIF!][!//

[!VAR "ModAdded" = "'false'"!][!//
[!SELECT "as:modconf('Can')[1]"!][!//
[!VAR "ModAdded" = "'true'"!][!//
[!ENDSELECT!][!//
[!//
[!IF "($ModAdded = 'true')"!][!//
#define IRQ_CAN_EXIST               (STD_ON)
[!ELSE!][!//
#define IRQ_CAN_EXIST               (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.CanModulesAvailable'), 'IrqCan0' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN0_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN0_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.CanModulesAvailable'), 'IrqCan1' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN1_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN1_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.CanModulesAvailable'), 'IrqCan2' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN2_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN2_EXIST              (STD_OFF)
[!ENDIF!][!//


[!IF "(contains( ecu:get('Irq.Can0SrnAvailable'), 'IrqCanSrn0' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN0SRN0_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN0SRN0_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can0SrnAvailable'), 'IrqCanSrn1' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN0SRN1_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN0SRN1_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can0SrnAvailable'), 'IrqCanSrn2' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN0SRN2_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN0SRN2_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can0SrnAvailable'), 'IrqCanSrn3' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN0SRN3_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN0SRN3_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can0SrnAvailable'), 'IrqCanSrn4' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN0SRN4_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN0SRN4_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can0SrnAvailable'), 'IrqCanSrn5' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN0SRN5_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN0SRN5_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can0SrnAvailable'), 'IrqCanSrn6' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN0SRN6_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN0SRN6_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can0SrnAvailable'), 'IrqCanSrn7' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN0SRN7_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN0SRN7_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can0SrnAvailable'), 'IrqCanSrn8' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN0SRN8_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN0SRN8_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can0SrnAvailable'), 'IrqCanSrn9' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN0SRN9_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN0SRN9_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can0SrnAvailable'), 'IrqCanSrn10' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN0SRN10_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_CAN0SRN10_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can0SrnAvailable'), 'IrqCanSrn11' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN0SRN11_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_CAN0SRN11_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can0SrnAvailable'), 'IrqCanSrn12' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN0SRN12_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_CAN0SRN12_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can0SrnAvailable'), 'IrqCanSrn13' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN0SRN13_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_CAN0SRN13_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can0SrnAvailable'), 'IrqCanSrn14' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN0SRN14_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_CAN0SRN14_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can0SrnAvailable'), 'IrqCanSrn15' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN0SRN15_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_CAN0SRN15_EXIST             (STD_OFF)
[!ENDIF!][!//


[!IF "(contains( ecu:get('Irq.Can1SrnAvailable'), 'IrqCanSrn0' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN1SRN0_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN1SRN0_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can1SrnAvailable'), 'IrqCanSrn1' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN1SRN1_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN1SRN1_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can1SrnAvailable'), 'IrqCanSrn2' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN1SRN2_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN1SRN2_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can1SrnAvailable'), 'IrqCanSrn3' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN1SRN3_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN1SRN3_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can1SrnAvailable'), 'IrqCanSrn4' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN1SRN4_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN1SRN4_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can1SrnAvailable'), 'IrqCanSrn5' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN1SRN5_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN1SRN5_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can1SrnAvailable'), 'IrqCanSrn6' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN1SRN6_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN1SRN6_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can1SrnAvailable'), 'IrqCanSrn7' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN1SRN7_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN1SRN7_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can1SrnAvailable'), 'IrqCanSrn8' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN1SRN8_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN1SRN8_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can1SrnAvailable'), 'IrqCanSrn9' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN1SRN9_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN1SRN9_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can1SrnAvailable'), 'IrqCanSrn10' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN1SRN10_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_CAN1SRN10_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can1SrnAvailable'), 'IrqCanSrn11' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN1SRN11_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_CAN1SRN11_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can1SrnAvailable'), 'IrqCanSrn12' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN1SRN12_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_CAN1SRN12_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can1SrnAvailable'), 'IrqCanSrn13' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN1SRN13_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_CAN1SRN13_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can1SrnAvailable'), 'IrqCanSrn14' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN1SRN14_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_CAN1SRN14_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can1SrnAvailable'), 'IrqCanSrn15' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN1SRN15_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_CAN1SRN15_EXIST             (STD_OFF)
[!ENDIF!][!//

[!IF "(contains( ecu:get('Irq.Can2SrnAvailable'), 'IrqCanSrn0' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN2SRN0_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN2SRN0_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can2SrnAvailable'), 'IrqCanSrn1' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN2SRN1_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN2SRN1_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can2SrnAvailable'), 'IrqCanSrn2' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN2SRN2_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN2SRN2_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can2SrnAvailable'), 'IrqCanSrn3' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN2SRN3_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN2SRN3_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can2SrnAvailable'), 'IrqCanSrn4' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN2SRN4_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN2SRN4_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can2SrnAvailable'), 'IrqCanSrn5' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN2SRN5_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN2SRN5_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can2SrnAvailable'), 'IrqCanSrn6' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN2SRN6_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN2SRN6_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can2SrnAvailable'), 'IrqCanSrn7' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN2SRN7_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN2SRN7_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can2SrnAvailable'), 'IrqCanSrn8' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN2SRN8_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN2SRN8_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can2SrnAvailable'), 'IrqCanSrn9' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN2SRN9_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_CAN2SRN9_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can2SrnAvailable'), 'IrqCanSrn10' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN2SRN10_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_CAN2SRN10_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can2SrnAvailable'), 'IrqCanSrn11' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN2SRN11_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_CAN2SRN11_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can2SrnAvailable'), 'IrqCanSrn12' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN2SRN12_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_CAN2SRN12_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can2SrnAvailable'), 'IrqCanSrn13' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN2SRN13_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_CAN2SRN13_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can2SrnAvailable'), 'IrqCanSrn14' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN2SRN14_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_CAN2SRN14_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.Can2SrnAvailable'), 'IrqCanSrn15' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_CAN2SRN15_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_CAN2SRN15_EXIST             (STD_OFF)
[!ENDIF!][!//


[!VAR "ModAdded" = "'false'"!][!//
[!SELECT "as:modconf('Adc')[1]"!][!//
[!VAR "ModAdded" = "'true'"!][!//
[!ENDSELECT!][!//
[!//
[!IF "($ModAdded = 'true')"!][!//
#define IRQ_ADC_EXIST               (STD_ON)
[!ELSE!][!//
#define IRQ_ADC_EXIST               (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADC0' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ADC0_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_ADC0_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADC1' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ADC1_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_ADC1_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADC2' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ADC2_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_ADC2_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADC3' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ADC3_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_ADC3_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADC4' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ADC4_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_ADC4_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADC5' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ADC5_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_ADC5_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADC6' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ADC6_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_ADC6_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADC7' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ADC7_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_ADC7_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADC8' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ADC8_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_ADC8_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADC9' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ADC9_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_ADC9_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADC10' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ADC10_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ADC10_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADC11' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ADC11_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ADC11_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADCCG0' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ADCCG0_EXIST            (STD_ON)
[!ELSE!][!//
#define IRQ_ADCCG0_EXIST            (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.VAdcAvailable'), 'IrqVADCCG0' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ADCCG1_EXIST            (STD_ON)
[!ELSE!][!//
#define IRQ_ADCCG1_EXIST            (STD_OFF)
[!ENDIF!][!//



[!VAR "ModAdded" = "'false'"!][!//
[!SELECT "as:modconf('Fr')[1]"!][!//
[!VAR "ModAdded" = "'true'"!][!//
[!ENDSELECT!][!//
[!//
[!IF "($ModAdded = 'true')"!][!//
#define IRQ_FLEXRAY_EXIST           (STD_ON)
[!ELSE!][!//
#define IRQ_FLEXRAY_EXIST           (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.FlexRayAvailable'), 'IrqFlexRay0' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_FLEXRAY0_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_FLEXRAY0_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.FlexRayAvailable'), 'IrqFlexRay1' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_FLEXRAY1_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_FLEXRAY1_EXIST          (STD_OFF)
[!ENDIF!][!//

[!VAR "ModAdded" = "'false'"!][!//
[!SELECT "as:modconf('Fls')[1]"!][!//
[!VAR "ModAdded" = "'true'"!][!//
[!ENDSELECT!][!//
[!//
[!IF "($ModAdded = 'true')"!][!//
#define IRQ_DMU_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_DMU_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DmuSrnAvailable'), 'IrqDmuSr0' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DMU_HOST_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_DMU_HOST_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DmuSrnAvailable'), 'IrqDmuSr1' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DMU_FSI_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_DMU_FSI_EXIST          (STD_OFF)
[!ENDIF!][!//

[!VAR "ModAdded" = "'false'"!][!//
[!SELECT "as:modconf('Icu')[1]"!][!//
[!VAR "ModAdded" = "'true'"!][!//
[!ENDSELECT!][!//
[!SELECT "as:modconf('Dsadc')[1]"!][!//
[!VAR "ModAdded" = "'true'"!][!//
[!ENDSELECT!][!//
[!//
[!IF "($ModAdded = 'true')"!][!//
#define IRQ_SCU_EXIST               (STD_ON)
[!ELSE!][!//
#define IRQ_SCU_EXIST               (STD_OFF)
[!ENDIF!][!//

[!IF "contains( ecu:get('Irq.ModAvailable'), 'IrqGpsr' )"!][!//
#define IRQ_GPSRGROUP_EXIST         (STD_ON)
[!ELSE!][!//
#define IRQ_GPSRGROUP_EXIST         (STD_OFF)
[!ENDIF!][!//
[!IF "contains( ecu:get('Irq.GpsrAvailable'), 'IrqGpsr0' )"!][!//
#define IRQ_GPSRGROUP0_EXIST        (STD_ON)
[!ELSE!][!//
#define IRQ_GPSRGROUP0_EXIST        (STD_OFF)
[!ENDIF!][!//
[!IF "contains( ecu:get('Irq.GpsrAvailable'), 'IrqGpsr1' )"!][!//
#define IRQ_GPSRGROUP1_EXIST        (STD_ON)
[!ELSE!][!//
#define IRQ_GPSRGROUP1_EXIST        (STD_OFF)
[!ENDIF!][!//
[!IF "contains( ecu:get('Irq.GpsrAvailable'), 'IrqGpsr2' )"!][!//
#define IRQ_GPSRGROUP2_EXIST        (STD_ON)
[!ELSE!][!//
#define IRQ_GPSRGROUP2_EXIST        (STD_OFF)
[!ENDIF!][!//
[!IF "contains( ecu:get('Irq.GpsrAvailable'), 'IrqGpsr3' )"!][!//
#define IRQ_GPSRGROUP3_EXIST        (STD_ON)
[!ELSE!][!//
#define IRQ_GPSRGROUP3_EXIST        (STD_OFF)
[!ENDIF!][!//
[!IF "contains( ecu:get('Irq.GpsrAvailable'), 'IrqGpsr4' )"!][!//
#define IRQ_GPSRGROUP4_EXIST        (STD_ON)
[!ELSE!][!//
#define IRQ_GPSRGROUP4_EXIST        (STD_OFF)
[!ENDIF!][!//
[!IF "contains( ecu:get('Irq.GpsrAvailable'), 'IrqGpsr5' )"!][!//
#define IRQ_GPSRGROUP5_EXIST        (STD_ON)
[!ELSE!][!//
#define IRQ_GPSRGROUP5_EXIST        (STD_OFF)
[!ENDIF!][!//


/* Global macros that determines whether a module / SRN is in use or not
*/
[!VAR "ModAdded" = "'false'"!][!//
[!SELECT "as:modconf('Lin')[1]"!][!//
[!VAR "ModAdded" = "'true'"!][!//
[!ENDSELECT!][!//
[!SELECT "as:modconf('Uart')[1]"!][!//
[!VAR "ModAdded" = "'true'"!][!//
[!ENDSELECT!][!//
[!INDENT "0"!][!//
    [!IF "($ModAdded = 'true')"!][!//
    #define IRQ_ASCLIN_CH_NOT_USED 0x0
    #define IRQ_ASCLIN_CH_USED_BY_LIN_DRIVER 0x1
    #define IRQ_ASCLIN_CH_USED_BY_UART_DRIVER 0x2


        [!SELECT "as:modconf('Mcu')[1]/McuHardwareResourceAllocationConf/*[1]/McuAscLinAllocationConf"!][!//
            [!VAR "TotalUnits" = "num:i(count(./*))"!][!//
            [!FOR "count"="num:i(1)" TO "$TotalUnits"!][!//
                [!INDENT "0"!][!//
                     #define IRQ_ASCLIN_CHANNEL[!"num:i($count - 1)"!]_USED IRQ_[!"./*[num:i($count)]/McuAscLinChannelAllocationConf/*[1]"!]
                [!ENDINDENT!][!//
            [!ENDFOR!][!//
        [!ENDSELECT!][!//
    [!ENDIF!][!//
[!ENDINDENT!][!//


[!IF "($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.AsclinSrnAvailable'), 'IrqAsclin0' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN0_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN0_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.AsclinSrnAvailable'), 'IrqAsclin1' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN1_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN1_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.AsclinSrnAvailable'), 'IrqAsclin2' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN2_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN2_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.AsclinSrnAvailable'), 'IrqAsclin3' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN3_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN3_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.AsclinSrnAvailable'), 'IrqAsclin4' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN4_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN4_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.AsclinSrnAvailable'), 'IrqAsclin5' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN5_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN5_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.AsclinSrnAvailable'), 'IrqAsclin6' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN6_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN6_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.AsclinSrnAvailable'), 'IrqAsclin7' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN7_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN7_EXIST             (STD_OFF)
[!ENDIF!][!//

[!IF "(contains( ecu:get('Irq.AsclinSrnAvailable'), 'IrqAsclin8' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN8_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN8_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.AsclinSrnAvailable'), 'IrqAsclin9' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN9_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN9_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.AsclinSrnAvailable'), 'IrqAsclin10' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN10_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN10_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.AsclinSrnAvailable'), 'IrqAsclin11' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN11_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN11_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.AsclinSrnAvailable'), 'IrqAsclin12' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN12_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN12_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.AsclinSrnAvailable'), 'IrqAsclin13' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN13_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN13_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.AsclinSrnAvailable'), 'IrqAsclin14' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN14_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN14_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.AsclinSrnAvailable'), 'IrqAsclin15' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN15_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN15_EXIST             (STD_OFF)
[!ENDIF!][!//

[!IF "(contains( ecu:get('Irq.AsclinSrnAvailable'), 'IrqAsclin16' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN16_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN16_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.AsclinSrnAvailable'), 'IrqAsclin17' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN17_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN17_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.AsclinSrnAvailable'), 'IrqAsclin18' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN18_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN18_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.AsclinSrnAvailable'), 'IrqAsclin19' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN19_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN19_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.AsclinSrnAvailable'), 'IrqAsclin20' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN20_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN20_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.AsclinSrnAvailable'), 'IrqAsclin21' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN21_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN21_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.AsclinSrnAvailable'), 'IrqAsclin22' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN22_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN22_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.AsclinSrnAvailable'), 'IrqAsclin23' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_ASCLIN23_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_ASCLIN23_EXIST             (STD_OFF)
[!ENDIF!][!//

/* Global macros that determines whether a module / SRN is in use or not
*/
[!VAR "ModAdded" = "'false'"!][!//
[!SELECT "as:modconf('Hssl')[1]"!][!//
[!VAR "ModAdded" = "'true'"!][!//
[!ENDSELECT!][!//
[!//
[!IF "($ModAdded = 'true')"!][!//
#define IRQ_HSSL_EXIST              (STD_ON)
[!ELSE!][!//
#define IRQ_HSSL_EXIST              (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.HsslAvailable'), 'IrqHssl0' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_HSSL0_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_HSSL0_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.HsslAvailable'), 'IrqHssl1' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_HSSL1_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_HSSL1_EXIST             (STD_OFF)
[!ENDIF!][!//


[!VAR "ModAdded" = "'false'"!][!//
[!SELECT "as:modconf('Sent')[1]"!][!//
[!VAR "ModAdded" = "'true'"!][!//
[!ENDSELECT!][!//
[!//
[!IF "($ModAdded = 'true')"!][!//
#define IRQ_SENT_EXIST               (STD_ON)
[!ELSE!][!//
#define IRQ_SENT_EXIST               (STD_OFF)
[!ENDIF!][!//

[!VAR "ModAdded" = "'false'"!][!//
[!SELECT "as:modconf('Dsadc')[1]"!][!//
[!VAR "ModAdded" = "'true'"!][!//
[!ENDSELECT!][!//
[!//
[!IF "($ModAdded = 'true')"!][!//
#define IRQ_DSADC_EXIST               (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_EXIST               (STD_OFF)
[!ENDIF!][!//

[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrM0' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRM0_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRM0_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrM1' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRM1_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRM1_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrM2' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRM2_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRM2_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrM3' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRM3_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRM3_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrM4' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRM4_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRM4_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrM5' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRM5_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRM5_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrM6' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRM6_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRM6_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrM7' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRM7_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRM7_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrM8' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRM8_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRM8_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrM9' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRM9_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRM9_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrM10' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRM10_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRM10_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrM11' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRM11_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRM11_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrM12' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRM12_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRM12_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrM13' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRM13_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRM13_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrA0' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRA0_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRA0_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrA1' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRA1_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRA1_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrA2' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRA2_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRA2_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrA3' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRA3_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRA3_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrA4' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRA4_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRA4_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrA5' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRA5_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRA5_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrA6' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRA6_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRA6_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrA7' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRA7_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRA7_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrA8' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRA8_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRA8_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrA9' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRA9_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRA9_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrA10' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRA10_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRA10_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrA11' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRA11_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRA11_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrA12' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRA12_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRA12_EXIST             (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.DSAdcSrnAvailable'), 'IrqDSAdcSrA13' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_DSADC_SRA13_EXIST             (STD_ON)
[!ELSE!][!//
#define IRQ_DSADC_SRA13_EXIST             (STD_OFF)
[!ENDIF!][!//


[!VAR "ModAdded" = "'false'"!][!//
[!NOCODE!]
[!SELECT "as:modconf('Mcu')[1]"!]
[!VAR "Count" = "num:i(count(McuModuleConfiguration/GtmGlobalConfiguration/*))"!]
[!IF "$Count > num:i(0)"!]		
[!VAR "ModAdded" = "'true'"!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!]
[!//
[!IF "($ModAdded = 'true')"!][!//
#define IRQ_GTM_EXIST               (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_EXIST               (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmAei' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_AEI_EXIST           (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_AEI_EXIST           (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmAru' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_ARU_EXIST           (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_ARU_EXIST           (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmBrc' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_BRC_EXIST           (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_BRC_EXIST           (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmCmp' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_CMP_EXIST           (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_CMP_EXIST           (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmSpe' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_SPE_EXIST           (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_SPE_EXIST           (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GtmSpeSrnAvailable'), 'IrqGtmSpe0Sr' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_SPE0_EXIST           (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_SPE0_EXIST           (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GtmSpeSrnAvailable'), 'IrqGtmSpe1Sr' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_SPE1_EXIST           (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_SPE1_EXIST           (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GtmSpeSrnAvailable'), 'IrqGtmSpe2Sr' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_SPE2_EXIST           (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_SPE2_EXIST           (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GtmSpeSrnAvailable'), 'IrqGtmSpe3Sr' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_SPE3_EXIST           (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_SPE3_EXIST           (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GtmSpeSrnAvailable'), 'IrqGtmSpe4Sr' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_SPE4_EXIST           (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_SPE4_EXIST           (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GtmSpeSrnAvailable'), 'IrqGtmSpe5Sr' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_SPE5_EXIST           (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_SPE5_EXIST           (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmPsm0' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_PSM0_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_PSM0_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmPsm1' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_PSM1_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_PSM1_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmPsm2' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_PSM2_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_PSM2_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmDpll' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_DPLL_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_DPLL_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmErr' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_ERR_EXIST           (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_ERR_EXIST           (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMTimAvailable'), 'IrqGtmTim0' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_TIM0_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_TIM0_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMTimAvailable'), 'IrqGtmTim1' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_TIM1_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_TIM1_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMTimAvailable'), 'IrqGtmTim2' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_TIM2_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_TIM2_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMTimAvailable'), 'IrqGtmTim3' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_TIM3_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_TIM3_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMTimAvailable'), 'IrqGtmTim4' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_TIM4_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_TIM4_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMTimAvailable'), 'IrqGtmTim5' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_TIM5_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_TIM5_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMTimAvailable'), 'IrqGtmTim6' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_TIM6_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_TIM6_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMTimAvailable'), 'IrqGtmTim7' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_TIM7_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_TIM7_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMMcsAvailable'), 'IrqGtmMcs0' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_MCS0_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_MCS0_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMMcsAvailable'), 'IrqGtmMcs1' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_MCS1_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_MCS1_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMMcsAvailable'), 'IrqGtmMcs2' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_MCS2_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_MCS2_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMMcsAvailable'), 'IrqGtmMcs3' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_MCS3_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_MCS3_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMMcsAvailable'), 'IrqGtmMcs4' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_MCS4_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_MCS4_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMMcsAvailable'), 'IrqGtmMcs5' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_MCS5_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_MCS5_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMMcsAvailable'), 'IrqGtmMcs6' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_MCS6_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_MCS6_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMMcsAvailable'), 'IrqGtmMcs7' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_MCS7_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_MCS7_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMMcsAvailable'), 'IrqGtmMcs8' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_MCS8_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_MCS8_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMMcsAvailable'), 'IrqGtmMcs9' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_MCS9_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_MCS9_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMTomAvailable'), 'IrqGtmTom0' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_TOM0_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_TOM0_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMTomAvailable'), 'IrqGtmTom1' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_TOM1_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_TOM1_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMTomAvailable'), 'IrqGtmTom2' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_TOM2_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_TOM2_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMTomAvailable'), 'IrqGtmTom3' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_TOM3_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_TOM3_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMTomAvailable'), 'IrqGtmTom4' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_TOM4_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_TOM4_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMTomAvailable'), 'IrqGtmTom5' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_TOM5_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_TOM5_EXIST          (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMAtomAvailable'), 'IrqGtmAtom0' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_ATOM0_EXIST         (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_ATOM0_EXIST         (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMAtomAvailable'), 'IrqGtmAtom1' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_ATOM1_EXIST         (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_ATOM1_EXIST         (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMAtomAvailable'), 'IrqGtmAtom2' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_ATOM2_EXIST         (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_ATOM2_EXIST         (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMAtomAvailable'), 'IrqGtmAtom3' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_ATOM3_EXIST         (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_ATOM3_EXIST         (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMAtomAvailable'), 'IrqGtmAtom4' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_ATOM4_EXIST         (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_ATOM4_EXIST         (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMAtomAvailable'), 'IrqGtmAtom5' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_ATOM5_EXIST         (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_ATOM5_EXIST         (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMAtomAvailable'), 'IrqGtmAtom6' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_ATOM6_EXIST         (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_ATOM6_EXIST         (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMAtomAvailable'), 'IrqGtmAtom7' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_ATOM7_EXIST         (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_ATOM7_EXIST         (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMAtomAvailable'), 'IrqGtmAtom8' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_ATOM8_EXIST         (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_ATOM8_EXIST         (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMAtomAvailable'), 'IrqGtmAtom9' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_ATOM9_EXIST         (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_ATOM9_EXIST         (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMAtomAvailable'), 'IrqGtmAtom10' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_ATOM10_EXIST        (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_ATOM10_EXIST        (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMAtomAvailable'), 'IrqGtmAtom11' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_ATOM11_EXIST        (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_ATOM11_EXIST        (STD_OFF)
[!ENDIF!][!//
[!IF "(contains( ecu:get('Irq.GTMAvailable'), 'IrqGtmMcsw' ))  and ($ModAdded = 'true')"!][!//
#define IRQ_GTM_MCSW_EXIST          (STD_ON)
[!ELSE!][!//
#define IRQ_GTM_MCSW_EXIST          (STD_OFF)
[!ENDIF!][!//


[!VAR "ModAdded" = "'false'"!][!//
[!SELECT "as:modconf('I2c')[1]"!][!//
[!VAR "ModAdded" = "'true'"!][!//
[!ENDSELECT!][!//
[!IF "($ModAdded = 'true')"!][!//
#define IRQ_I2C_EXIST               (STD_ON)
[!ELSE!][!//
#define IRQ_I2C_EXIST               (STD_OFF)
[!ENDIF!][!//


[!ENDSELECT!][!//
/* IRQ_CFG_H */
#endif
