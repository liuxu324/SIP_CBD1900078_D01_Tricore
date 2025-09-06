// TASKING VX-toolset for TriCore
// Eclipse project linker script file
//
#if defined(__PROC_TC39XB__)
#include "tc39xb.lsl"
derivative my_tc39xb extends tc39xb
{
}
#else
#include <cpu.lsl>
#endif

/* ------------ User action required ------------------------- */
/* Please define which cores are used by your OS configuration */
#define CORE0_IS_ASR
#define CORE1_IS_ASR
#define CORE2_IS_ASR
#define CORE3_IS_ASR
#define CORE4_IS_ASR
#define CORE5_IS_ASR
/* ----------------------------------------------------------- */

section_layout mpe:vtc:linear
{
//  #include "DSPR_Core0.lsl"
//  #include "DSPR_Core1.lsl"
//  #include "DSPR_Core2.lsl"
//  #include "DSPR_Core3.lsl"
//  #include "DSPR_Core4.lsl"
//  #include "DSPR_Core5.lsl"

#if defined(__PROC_TC39XB__)
  group OSCodeConst( run_addr = mem:mpe:pflash1 )
#else
  group OSCodeConst( ordered, run_addr = 0x80110000 )
#endif
  {
    #if defined(CORE0_IS_ASR)
     #define OS_LINK_INTVEC_CODE
     #define OS_LINK_EXCVEC_CODE
     #define OS_LINK_CALLOUT_CODE
     #define OS_LINK_CONST
      #include ".\Appl\GenData\Os_Link_Core0.lsl"
    #endif

    #if defined(CORE1_IS_ASR)
     #define OS_LINK_INTVEC_CODE
     #define OS_LINK_EXCVEC_CODE
     #define OS_LINK_CALLOUT_CODE
     #define OS_LINK_CONST
      #include ".\Appl\GenData\Os_Link_Core1.lsl"
    #endif

    #if defined(CORE2_IS_ASR)
     #define OS_LINK_INTVEC_CODE
     #define OS_LINK_EXCVEC_CODE
     #define OS_LINK_CALLOUT_CODE
     #define OS_LINK_CONST
      #include ".\Appl\GenData\Os_Link_Core2.lsl"
    #endif

    #if defined(CORE3_IS_ASR)
     #define OS_LINK_INTVEC_CODE
     #define OS_LINK_EXCVEC_CODE
     #define OS_LINK_CALLOUT_CODE
     #define OS_LINK_CONST
      #include ".\Appl\GenData\Os_Link_Core3.lsl"
    #endif

    #if defined(CORE4_IS_ASR)
     #define OS_LINK_INTVEC_CODE
     #define OS_LINK_EXCVEC_CODE
     #define OS_LINK_CALLOUT_CODE
     #define OS_LINK_CONST
      #include ".\Appl\GenData\Os_Link_Core4.lsl"
    #endif

    #if defined(CORE5_IS_ASR)
     #define OS_LINK_INTVEC_CODE
     #define OS_LINK_EXCVEC_CODE
     #define OS_LINK_CALLOUT_CODE
     #define OS_LINK_CONST
      #include ".\Appl\GenData\Os_Link_Core5.lsl"
    #endif

    #define OS_LINK_CODE
    #define OS_LINK_CALLOUT_CODE
     #include ".\Appl\GenData\Os_Link.lsl"
  }
}
