/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         \file  TcpIp_DhcpV6.c
 *        \brief  Implementation of Dynamic Host Configuration Protocol for IPv6 - Client (DHCPv6 Client)
 *
 *      \details  This file is part of the TcpIp IPv6 submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp IPv6 submodule. >> TcpIp_IpV6.h / TcpIp.h (Version 8.xx.xx and higher)
 *********************************************************************************************************************/

/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */
/* PRQA S 0828 EOF */ /* MD_MSR_1.1_828 */

#define TCPIP_DHCPV6_SOURCE

#include "TcpIp_Cfg.h"
#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
# if (TCPIP_SUPPORT_DHCPV6 == STD_ON)
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "TcpIp.h"
#include "TcpIp_Priv.h"
#include "TcpIp_DhcpV6.h"
#include "TcpIp_DhcpV6_Cbk.h"
#include "TcpIp_Lcfg.h"
#include "IpBase.h"
#include "vstdlib.h"

#include "TcpIp_IpV6_Priv.h"

#if (TCPIP_SUPPORT_DNS == STD_ON)
# include "Dns.h"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#if !defined (STATIC)
# define STATIC static
#endif

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
# define TCPIP_DHCPV6_VENABLE_CANOE_WRITE_STRING  STD_OFF
# define TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS STD_ON
#else
# define TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS STD_OFF
#endif

#define TCPIP_DHCPV6_MAX_TRANS_ID 0x00FFFFFFU
#define TCPIP_DHCPV6_INV_TRANS_ID 0xFF000000U

#define TCPIP_DHCPV6_USE_RAND_FUNCTION STD_ON

#define TCPIP_DHCPV6_OPT_REQ_OPT_LIST_LEN            3U
#define TCPIP_DHCPV6_OPT_REQ_OPT_LIST_EXTRA_OPT_OFS  1U

/* dhcp Iana options offset */
#define TCPIP_DHCPV6_IANA_OPT_OFF_IAIDNBO   0U
#define TCPIP_DHCPV6_IANA_OPT_OFF_T1NBO     (TCPIP_DHCPV6_IANA_OPT_OFF_IAIDNBO + 4U)
#define TCPIP_DHCPV6_IANA_OPT_OFF_T2NBO     (TCPIP_DHCPV6_IANA_OPT_OFF_T1NBO + 4U)

/* dhcp Iana address option offset */
#define TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_ADDR  0U
#define TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_PREFLIFENBO     (TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_ADDR + 16U)
#define TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_VALDLIFENBO     (TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_PREFLIFENBO + 4U)

/* dhcp elapsed time option offset */
#define TCPIP_DHCPV6_ELAPSEDTIME_OPT_OFF_ELAPSEDTIMENBO  0U

/* dhcp elapsed time option offset */
#define TCPIP_DHCPV6_STATUSCODE_OPT_OFF_STATUSCODENBO    0U

/* dhcp duid type 1 option offset */
#define TCPIP_DHCPV6_DUID1_OPT_OFF_TYPENBO               0U
#define TCPIP_DHCPV6_DUID1_OPT_OFF_HWTYPENBO             (TCPIP_DHCPV6_DUID1_OPT_OFF_TYPENBO + 2u)
#define TCPIP_DHCPV6_DUID1_OPT_OFF_TIMENBO               (TCPIP_DHCPV6_DUID1_OPT_OFF_HWTYPENBO + 2u)
#define TCPIP_DHCPV6_DUID1_OPT_OFF_PHYSADDR              (TCPIP_DHCPV6_DUID1_OPT_OFF_TIMENBO + 4u)


/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/*  */
#define TCPIP_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
# if (TCPIP_DHCPV6_VENABLE_CANOE_WRITE_STRING == STD_ON)
STATIC sint8 VCanoeWriteStrBuffer[256];
# endif
#endif

#define TCPIP_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*  */
#define TCPIP_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define TCPIP_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*  */
#define TCPIP_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define TCPIP_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/*  */
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (TCPIP_DHCPV6_ENABLE_DYNAMIC_IA_NA == STD_ON)
STATIC VAR(TcpIp_DhcpV6_IaAddrLeaseType, TCPIP_VAR_NOINIT) TcpIp_DhcpV6_IaAddrLeases[1];
#endif

#if (TCPIP_DHCPV6_ENABLE_DYNAMIC_IA_NA == STD_ON)
STATIC VAR(TcpIp_DhcpV6_OptIaAddrType,   TCPIP_VAR_NOINIT) TcpIp_DhcpV6_IaAddrBuf[1];
#endif

STATIC VAR(TcpIp_DhcpV6_TimeType, TCPIP_VAR_NOINIT) TcpIp_DhcpV6_Time;

#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/*  */
#define TCPIP_START_SEC_CONST_16BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

STATIC CONST(uint16, TCPIP_CONST) TcpIp_DhcpV6_OptionRequestList[TCPIP_DHCPV6_OPT_REQ_OPT_LIST_LEN] =
              { TCPIP_DHCPV6_OPT_IA_NA, TCPIP_DHCPV6_OPT_DNS_SERVERS, TCPIP_DHCPV6_OPT_DOMAIN_LIST };

#define TCPIP_STOP_SEC_CONST_16BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*  */
#define TCPIP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* link-local multicast address for all DHCPv6 server and relay agents */
/* PRQA S 0759 5 */ /* MD_TcpIp_18.4 */
CONST(IpBase_AddrIn6Type, TCPIP_CONST) TcpIp_DhcpV6_Addr_All_DHCP_Relay_Agents_and_Servers =
{
  {
    0xFF, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02
  }
};

#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*  */
#define TCPIP_START_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define TCPIP_STOP_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */




/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VGetNextOption()
 *********************************************************************************************************************/
/*! \brief          Obtain DhcpV6 option offset and option code from the payload 
 *  \details        -
 *  \param[in]      DataPtr    DhcpV6 payload buffer
 *  \param[in]      DataLen    DhcpV6 packet length
 *  \param[in,out]  OptPosPtr  This structure stores information of the DhcpV6 option
 *  \return         TRUE       The Dhcpv6 option was processed and information stored in OptPosPtr
 *  \return         FALSE      The Dhcpv6 option could not be processed, OptPosPtr does not contain valid information
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *********************************************************************************************************************/
STATIC FUNC(boolean, TCPIP_CODE) TcpIp_DhcpV6_VGetNextOption(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen,
  P2VAR(TcpIp_DhcpV6_OptLocationType, AUTOMATIC, TCPIP_APPL_VAR) OptPosPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VDecodeOptIaNa()
 *********************************************************************************************************************/
/*! \brief          Decode the IaNa non temporary address options in dhcpv6 packet
 *  \details        -
 *  \param[in]      DataPtr   DhcpV6 payload buffer
 *  \param[in]      DataLen   DhcpV6 packet length
 *  \param[in,out]  IaNaPtr   IaNa option information is stored here
 *                            The information in IaNa is valid only if Valid flag is set in IaNa
 *  \return         E_OK      The IaNa option was processed successfully, IaNaPtr has valid information
 *  \return         E_NOT_OK  The IaNa option was not processed, IaNaPtr is not valid
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VDecodeOptIaNa(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                 DataPtr,
  uint16                                                     DataLen,
  P2VAR(TcpIp_DhcpV6_OptIaNaType, AUTOMATIC, TCPIP_APPL_VAR) IaNaPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VAddRawOpt()
 *********************************************************************************************************************/
/*! \brief        Add dhcpv6 user option into the message buffer
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller 
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    MsgPtr           Dhcpv6 message buffer, cannot be NULL_PTR
 *  \param[in]    OptType          Type of user option -
 *                                 TCPIP_DHCPV6_OPT_CLIENTID          Client identifier option
 *                                 TCPIP_DHCPV6_OPT_SERVERID          Server identifier option
 *                                 TCPIP_DHCPV6_OPT_ID_CLIENT_FQDN    Client fqdn option
 *  \param[out]   OptDataPtr       Option data buffer, cannot be NULL_PTR
 *  \param[out]   OptDataLen       Option data length
 *  \return       E_OK             Option added successfully
 *  \pre          Message buffer and option data buffers are valid pointers
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VAddRawOpt(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr,
  uint16                                                 OptType,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)             OptDataPtr,
  uint16                                                 OptDataLen);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VDecodeOptStatusCode()
 *********************************************************************************************************************/
/*! \brief        Validate and process status code option in dhcpv6 messages
 *  \details      -
 *  \param[in]    DataPtr         DhcpV6 payload buffer
 *  \param[in]    DataLen         DhcpV6 packet length
 *  \param[out]   StatusCodePtr   Processed status code is stored here
 *  \return       E_OK            Status code processed successfully
 *  \return       E_NOT_OK        Invalid header length of status code
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VDecodeOptStatusCode(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                       DataPtr,
  uint16                                                           DataLen,
  P2VAR(TcpIp_DhcpV6_OptStatusCodeType, AUTOMATIC, TCPIP_APPL_VAR) StatusCodePtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VDecodeOptIaAddr()
 *********************************************************************************************************************/
/*! \brief        Validate and process Iana Address option in dhcpv6 message
 *  \details      Process Iana address options (including Iana address status code)
 *  \param[in]    DataPtr           DhcpV6 payload buffer
 *  \param[in]    DataLen           DhcpV6 packet length
 *  \param[out]   DynIaAddrPtr      Dynamic Iana addresses is stored here
 *  \param[in]    DynIaAddrCount    Number of dynamic Iana addresses
 *  \param[out]   IaAddrPtr         Ia Address option values are stored here
 *  \return       E_OK              Ia Address processed successfully
 *  \return       E_NOT_OK          Invalid header length / error code in option
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VDecodeOptIaAddr(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                   DataPtr,
  uint16                                                       DataLen,
#if (TCPIP_DHCPV6_ENABLE_DYNAMIC_IA_NA == STD_ON)
  P2VAR(TcpIp_DhcpV6_OptIaAddrType, AUTOMATIC, TCPIP_APPL_VAR) DynIaAddrPtr,
  uint8                                                        DynIaAddrCount
#else
  P2VAR(TcpIp_DhcpV6_OptIaAddrType, AUTOMATIC, TCPIP_APPL_VAR) IaAddrPtr
#endif
);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VRxReply()
 *********************************************************************************************************************/
/*! \brief        Function to handle dhcpv6 replies
 *  \details      Invokes processing routines for different dhcpv6 reply messages
 *  \param[in]    IpCtrlIdx        Index of IP controller 
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    DataPtr          DhcpV6 payload buffer
 *  \param[in]    DataLen          DhcpV6 packet length
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VRxReply(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VRestartAddressAssignment()
 *********************************************************************************************************************/
/*! \brief        Restart address assignment for dhcpv6 configured address of Ip controller
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller 
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    DelayMs          Idle time in millisecondss
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VRestartAddressAssignment(TcpIp_IpV6CtrlIterType IpCtrlIdx, uint32 DelayMs);

#if (TCPIP_SUPPORT_DHCPV6_OPTIONS == STD_ON)

# if (TCPIP_DHCPV6_TX_OPTION_CNT > 0)
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VAddUserOptions()
 *********************************************************************************************************************/
/*! \brief        Add client fqdn option
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller 
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr           Message data buffer
 *  \return       E_OK             User option added successfully (always returns successful)
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VAddUserOptions(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);
# endif

# if (TCPIP_DHCPV6_RX_OPTION_CNT > 0)
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VHandleUserOptions()
 *********************************************************************************************************************/
/*! \brief        Handler for user options
 *  \details      -
 *  \param[in]    MsgType    Type of dhcpv6 message
 *  \param[in]    DataPtr    DhcpV6 payload buffer
 *  \param[in]    DataLen    DhcpV6 packet length
 *  \return       E_OK       User option processed successfully (always returns successful)
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VHandleUserOptions(
  uint8                                      MsgType,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen);
# endif

#endif

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VCompareBytes()
 *********************************************************************************************************************/
/*! \brief        Compare bytes of two buffers
 *  \details      -
 *  \param[in]    Data1Ptr          Buffer 1
 *  \param[in]    Data1Len          Buffer 1 length
 *  \param[in]    Data2Ptr          Buffer 2
 *  \param[in]    Data2Len          Buffer 2 length
 *  \return       TRUE              Buffers match
 *  \return       FALSE             Buffers are different
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(boolean, TCPIP_CODE) TcpIp_DhcpV6_VCompareBytes(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) Data1Ptr,
  uint16                                     Data1Len,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) Data2Ptr,
  uint16                                     Data2Len);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VInitClientId()
 *********************************************************************************************************************/
/*! \brief        Initialize client identifier
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller 
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VInitClientId(TcpIp_IpV6CtrlIterType IpCtrlIdx);

#if (TCPIP_DHCPV6_USE_RAND_FUNCTION == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VGetRandomValue()
 *********************************************************************************************************************/
/*! \brief        Generate random value within given range
 *  \details      -
 *  \param[in]    MinValue      Lower range
 *  \param[in]    MaxValue      Upper range
 *  \return       RndValue      Random value generated
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(sint32, TCPIP_CODE) TcpIp_DhcpV6_VGetRandomValue(
  sint32 MinValue, 
  sint32 MaxValue);
#endif

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VSetEventTime()
 *********************************************************************************************************************/
/*! \brief             Configure the next event timestamp by adding value to the IpV6 time
 *  \details           -
 *  \param[in,out]     TimestampPtr    Time object to add to
 *  \param[in]         Milliseconds    Time to be added in milliseconds
 *  \pre               -
 *  \context           TASK|ISR
 *  \reentrant         FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, IPV6_CODE) TcpIp_DhcpV6_VSetEventTime(
  P2VAR(TcpIp_DhcpV6_TimeType, AUTOMATIC, TCPIP_APPL_DATA)  TimestampPtr,
  uint32                                                    Milliseconds);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VTimeAddMs()
 *********************************************************************************************************************/
/*! \brief             Add time in milliseconds to a given timestamp
 *  \details           -
 *  \param[in,out]     TimestampPtr    Time object to add to
 *  \param[in]         Milliseconds    Time to be added in milliseconds
 *  \pre               -
 *  \context           TASK|ISR
 *  \reentrant         FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VTimeAddMs(
  P2VAR(TcpIp_DhcpV6_TimeType, AUTOMATIC, TCPIP_APPL_DATA) TimestampPtr,
  uint32                                                   Milliseconds);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VTimeSet()
 *********************************************************************************************************************/
/*! \brief        Set timestamp with given values
 *  \details      -
 *  \param[out]   TimestampPtr    Time variable to update
 *  \param[in]    Seconds         Seconds to add
 *  \param[in]    Milliseconds    Milliseconds to add
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(void, IPV6_CODE) TcpIp_DhcpV6_VTimeSet(
  P2VAR(TcpIp_DhcpV6_TimeType, AUTOMATIC, TCPIP_APPL_DATA)  TimestampPtr,
  uint32                                                    Seconds,
  uint32                                                    Milliseconds);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VTimeCompare()
 *********************************************************************************************************************/
/*! \brief        Compare two timestamps and return which is lower
 *  \details      -
 *  \param[in]    RefTimestamp      Reference time variable
 *  \param[in]    Timestamp         Time variable to check 
 *  \return       TRUE              Reference time is lower
 *  \return       FALSE             Given time is lower
 *  \pre          -
 *  \synchronous  TRUE
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
TCPIP_LOCAL_INLINE FUNC(boolean, IPV6_CODE) TcpIp_DhcpV6_VTimeCompare(
  TcpIp_DhcpV6_TimeType  RefTimestamp,
  TcpIp_DhcpV6_TimeType  Timestamp);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VSetLifetimeS()
 *********************************************************************************************************************/
/*! \brief            Calculate and store lifetime into given time object
 *  \details          -
 *  \param[in]        TimestampPtr       Current time in dhcpv6
 *  \param[in]        LifetimeS          Lifetime to be updated
 *  \param[out]       NextEventTimePtr   Updated valid lifetime is stored in this
 *  \pre              -
 *  \context          TASK|ISR
 *  \reentrant        FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VSetLifetimeS(
  P2VAR(TcpIp_DhcpV6_TimeType, AUTOMATIC, TCPIP_APPL_VAR) TimestampPtr,
  uint32                                                  LifetimeS,
  P2VAR(TcpIp_DhcpV6_TimeType, AUTOMATIC, TCPIP_APPL_VAR) NextEventTimePtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VChangeState()
 *********************************************************************************************************************/
/*! \brief            Update the state of DhcpV6
 *  \details          -
 *  \param[in]        DhcpV6DataIdx     Index of the DhcpV6 data structure
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfDhcpV6Data()-1]
 *  \param[in]        NewState          New state to be updated
 *  \pre              -
 *  \context          TASK
 *  \reentrant        TRUE
 *********************************************************************************************************************/
STATIC INLINE FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VChangeState(
  TcpIp_SizeOfDhcpV6DataType    DhcpV6DataIdx,
  uint8                         NewState);


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VWriteOptionCode()
 *********************************************************************************************************************/
/*! \brief        Helper function to update option code into data buffer
 *  \details      -
 *  \param[out]   DataPtr          DhcpV6 payload buffer
 *  \param[in]    OptCode          Option code to write
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC INLINE FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VWriteOptionCode(
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) DataPtr,
  uint16                                  OptCode);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VWriteOptionLen()
 *********************************************************************************************************************/
/*! \brief        Helper function to write option length into data buffer
 *  \details      -
 *  \param[in]    DataPtr          DhcpV6 payload buffer
 *  \param[in]    OptLen           Option length to write
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC INLINE FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VWriteOptionLen(
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) DataPtr,
  uint16                                  OptLen);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VReadOptionCode()
 *********************************************************************************************************************/
/*! \brief        Helper function to read option code from dhcpv6 data buffer
 *  \details      -
 *  \param[in]    DataPtr          DhcpV6 payload buffer
 *  \return       optCode          Option code
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC INLINE FUNC(uint16, TCPIP_CODE) TcpIp_DhcpV6_VReadOptionCode(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VSetRetransParams()
 *********************************************************************************************************************/
/*! \brief        Update retransmission parameters for dhcpv6 messages
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller 
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    IRT              Init Retransmission time
 *  \param[in]    MRT              Maximum retransmission time
 *  \param[in]    MRC              Maximumm retransmission count
 *  \param[in]    MRD              Maximum retransmission duration
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VSetRetransParams(
  TcpIp_IpV6CtrlIterType IpCtrlIdx,
  uint32                 IRT, 
  uint32                 MRT, 
  uint8                  MRC, 
  uint32                 MRD);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VCalcTimeout()
 *********************************************************************************************************************/
/*! \brief        Calculate and update timeout values for dhcpv6 message retransmission
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller 
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   TimePtr          Time object to store updated timeout value
 *  \param[in]    IsSolicit        Solicited request flag
 *  \return       E_OK             Timeout value has been updated successfully
 *  \return       E_NOT_OK         Maximum retries of dhcpv6 message has been reached or maximum retransmission
 *                                 duration expired
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VCalcTimeout(
  TcpIp_IpV6CtrlIterType                                  IpCtrlIdx, 
  P2VAR(TcpIp_DhcpV6_TimeType, AUTOMATIC, TCPIP_APPL_VAR) TimePtr, 
  boolean                                                 IsSolicit);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VOptStackPushDataPos()
 *********************************************************************************************************************/
/*! \brief             Push dhcpv6 option offset value into options stack
 *  \details           -
 *  \param[in,out]     MsgPtr    Dhcpv6 message buffer
 *  \return            E_OK      Option offset pushed into stack successfully
 *  \return            E_NOT_OK  Stack full, push operation failed
 *  \pre               -
 *  \context           TASK|ISR
 *  \reentrant         FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VOptStackPushDataPos(
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VOptStackPopDataPos()
 *********************************************************************************************************************/
/*! \brief        Pop dhcpv6 option offset value from options stack
 *  \details      -
 *  \param[in]    MsgPtr       Dhcpv6 message buffer
 *  \param[out]   DataPosPtr   Option offset is stored here
 *  \return       E_OK         Offset popped successfully
 *  \return       E_NOT_OK     Stack empty, no data to pop
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VOptStackPopDataPos(
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr,
  P2VAR(uint16, AUTOMATIC, TCPIP_APPL_VAR)               DataPosPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBeginMessage()
 *********************************************************************************************************************/
/*! \brief        Update the dhcpv6 message buffer with the message parameters
 *  \details      Message type, transaction id are updated
 *  \param[in]    IpCtrlIdx        Index of IP controller 
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr           Message data buffer
 *  \param[in]    MsgType          Message type
 *  \return       E_OK             Message built successfully (always return success)
 *  \return       E_NOT_OK         Invalid Ip controller index (DhcpV6 not configured)
 *  \pre          Message data buffer is a valid pointer
 *                DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBeginMessage(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr,
  uint8                                                  MsgType);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VEndMessage()
 *********************************************************************************************************************/
/*! \brief        Update the user options into the dhcpv6 message buffer
 *  \details      Add user into options if enabled
 *  \param[in]    IpCtrlIdx        Index of IP controller 
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr           Message data buffer
 *  \return       MsgBufPos        The end offset of the message buffer
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(uint16, TCPIP_CODE) TcpIp_DhcpV6_VEndMessage(
  TcpIp_IpV6CtrlIterType                                  IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_DATA) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VAddOptClientIdent()
 *********************************************************************************************************************/
/*! \brief        Update client identifier info into the message buffer
 *  \details      -
 *  \param[in]    IpCtrlIdx    Index of IP controller 
 *                             CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr       Message data buffer
 *  \return       E_OK         Client option added successfully
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VAddOptClientIdent(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx, 
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VAddOptServerIdent()
 *********************************************************************************************************************/
/*! \brief        Update server identifier info into the message buffer
 *  \details      -
 *  \param[in]    IpCtrlIdx    Index of IP controller 
 *                             CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr       Message data buffer
 *  \return       E_OK         Server option added successfully
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VAddOptServerIdent(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx, 
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBeginOptIaNa()
 *********************************************************************************************************************/
/*! \brief        Build Iana option header into the message buffer 
 *  \details      -
 *  \param[in]    IpCtrlIdx    Index of IP controller 
 *                             CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr       Message data buffer
 *  \param[in]    IaId         Ia address Id
 *  \param[in]    T1           Timeout 1 value (in dhcpv6 Iana option)
 *  \param[in]    T2           Timeout 2 value (in dhcpv6 Iana option)
 *  \return       E_OK         Iana option header created successfully
 *  \return       E_NOT_OK     No space in message stack to store option values
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBeginOptIaNa(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx, 
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr, 
  uint32                                                 IaId, 
  uint32                                                 T1, 
  uint32                                                 T2);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VEndOptIaNa()
 *********************************************************************************************************************/
/*! \brief        Update the Iana Option length into the iana header in message buffer
 *  \details      -
 *  \param[in]    IpCtrlIdx    Index of IP controller 
 *                             CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr       Message data buffer
 *  \return       E_OK         Iana option built successfully
 *  \return       E_NOT_OK     Iana option not built successfully
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VEndOptIaNa(
  TcpIp_IpV6CtrlIterType                                  IpCtrlIdx, 
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR)  MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBeginOptIaAddr()
 *********************************************************************************************************************/
/*! \brief        Update the Ia address header information into message buffer
 *  \details      -
 *  \param[in]    IpCtrlIdx           Index of IP controller 
 *                                    CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr              Message data buffer
 *  \param[in]    AddrPtr             Ia address
 *  \param[in]    PreferredLifetime   Preferred lifetime
 *  \param[in]    ValidLifetime       Valid lifetime
 *  \return       E_OK                Iana address header created successfully
 *  \return       E_NOT_OK            No space in message stack to store option values
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBeginOptIaAddr(
  TcpIp_IpV6CtrlIterType                                   IpCtrlIdx, 
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR)   MsgPtr, 
  P2CONST(IpBase_AddrIn6Type, AUTOMATIC, TCPIP_APPL_DATA)  AddrPtr, 
  uint32                                                   PreferredLifetime, 
  uint32                                                   ValidLifetime);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VEndOptIaAddr()
 *********************************************************************************************************************/
/*! \brief        Update the Ia address option length into the Ia address option header
 *  \details      -
 *  \param[in]    IpCtrlIdx    Index of IP controller 
 *                             CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr       Message data buffer
 *  \return       E_OK         Iana address option added successfully
 *  \return       E_NOT_OK     Iana address option not built successfully
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VEndOptIaAddr(
  TcpIp_IpV6CtrlIterType                                  IpCtrlIdx, 
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR)  MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VAddOptReqOpt()
 *********************************************************************************************************************/
/*! \brief        Add array of options into message buffer
 *  \details      -
 *  \param[in]    IpCtrlIdx      Index of IP controller 
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr         Message data buffer
 *  \param[in]    OptCodeArray   Array of options to add into message buffer
 *  \param[in]    OptCodeCount   Number of options in the array
 *  \return       E_OK           Option list added successfully
 *  \pre          OptCodeArray is valid
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VAddOptReqOpt(
  TcpIp_IpV6CtrlIterType                                  IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR)  MsgPtr,
  P2CONST(uint16, AUTOMATIC, TCPIP_APPL_DATA)             OptCodeArray,
  uint8                                                   OptCodeCount);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VAddOptElapsedTime()
 *********************************************************************************************************************/
/*! \brief        Add elapsed time option into dhcpv6 message buffer
 *  \details      -
 *  \param[in]    IpCtrlIdx      Index of IP controller 
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr         Message data buffer
 *  \return       E_OK           Option added successfully
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VAddOptElapsedTime(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildSolicit()
 *********************************************************************************************************************/
/*! \brief        Build dhcpv6 solicit message
 *  \details      Invoke helper functions to build a solicit message (as per [RFC3315 17.1.1. Creation of Solicit Messages])
 *  \param[in]    IpCtrlIdx      Index of IP controller 
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr         Message data buffer
 *  \return       E_OK           Message built successfully
 *  \return       E_NOT_         Message build failed
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildSolicit(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildInfoRequest()
 *********************************************************************************************************************/
/*! \brief        Build dhcpv6 info request message
 *  \details      -
 *  \param[in]    IpCtrlIdx      Index of IP controller 
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr         Message data buffer
 *  \return       E_OK           Message built successfully
 *  \return       E_NOT_         Message build failed
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildInfoRequest(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildRelease()
 *********************************************************************************************************************/
/*! \brief        Build dhcpv6 reelase message
 *  \details      -
 *  \param[in]    IpCtrlIdx      Index of IP controller 
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr         Message data buffer
 *  \return       E_OK           Message built successfully
 *  \return       E_NOT_         Message build failed
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildRelease(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildRenew()
 *********************************************************************************************************************/
/*! \brief        Build dhcpv6 renew message
 *  \details      -
 *  \param[in]    IpCtrlIdx      Index of IP controller 
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr         Message data buffer
 *  \return       E_OK           Message built successfully
 *  \return       E_NOT_         Message build failed
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildRenew(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildRebind()
 *********************************************************************************************************************/
/*! \brief        Build dhcpv6 rebind message
 *  \details      -
 *  \param[in]    IpCtrlIdx      Index of IP controller 
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr         Message data buffer
 *  \return       E_OK           Message built successfully
 *  \return       E_NOT_         Message build failed
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildRebind(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildDecline()
 *********************************************************************************************************************/
/*! \brief        Build dhcpv6 decline message
 *  \details      -
 *  \param[in]    IpCtrlIdx      Index of IP controller 
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr         Message data buffer
 *  \return       E_OK           Message built successfully
 *  \return       E_NOT_         Message build failed
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildDecline(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildConfirm()
 *********************************************************************************************************************/
/*! \brief        Build dhcpv6 confirm message
 *  \details      -
 *  \param[in]    IpCtrlIdx      Index of IP controller 
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr         Message data buffer
 *  \return       E_OK           Message built successfully
 *  \return       E_NOT_         Message build failed
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildConfirm(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildRequest()
 *********************************************************************************************************************/
/*! \brief        Build dhcpv6 request message
 *  \details      -
 *  \param[in]    IpCtrlIdx      Index of IP controller 
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr         Message data buffer
 *  \return       E_OK           Message built successfully
 *  \return       E_NOT_         Message build failed
 *  \return       BUFREQ_E_BUSY    
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildRequest(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VTriggerTx()
 *********************************************************************************************************************/
/*! \brief        Trigger tx for the dhcpv6 message
 *  \details      -
 *  \param[out]   MsgPtr         Message data buffer
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VTriggerTx(P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VTxMessage()
 *********************************************************************************************************************/
/*! \brief        Transmit dhcpv6 message as Udp packet
 *  \details      -
 *  \param[in]    IpCtrlIdx      Index of IP controller 
 *                               CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr         Message data buffer
 *  \return       E_OK           Packet transmission successful
 *  \return       E_NOT_OK       Packet not transmitted successfully
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VTxMessage(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VDecodeOptPreference()
 *********************************************************************************************************************/
/*! \brief        Validate and process the preference option
 *  \details      -
 *  \param[in]    DataPtr              Data buffer
 *  \param[in]    DataLen              Length of dhcpv6 message
 *  \param[out]   PreferenceValuePtr   Preference value is stored here . Valid if return is E_OK
 *  \return       E_OK                 Preference option processed successfully
 *  \return       E_NOT_OK             Preference option not obtained
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VDecodeOptPreference(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR)    PreferenceValuePtr);

#if (TCPIP_SUPPORT_DNS == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VDecodeOptDnsServers()
 *********************************************************************************************************************/
/*! \brief        Decode dns server options
 *  \details      -
 *  \param[in]    DataPtr              Data buffer
 *  \param[in]    DataLen              Length of dhcpv6 message
 *  \param[in]    DnsServersOptPtr     Dns server values are stored here
 *  \return       E_OK                 Dns server option processed successfully
 *  \return       E_NOT_OK             Dns server option not obtained
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VDecodeOptDnsServers(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                       DataPtr,
  uint16                                                           DataLen,
  P2VAR(TcpIp_DhcpV6_OptDnsServersType, AUTOMATIC, TCPIP_APPL_VAR) DnsServersOptPtr);
#endif

#if (TCPIP_SUPPORT_DNS == STD_ON)
/**********************************************************************************************************************
 *  ()
 *********************************************************************************************************************/
/*! \brief        Decode and obtain Dns domainlist from dhcpv6 reply
 *  \details      -
 *  \param[in]    DataPtr              Data buffer
 *  \param[in]    DataLen              Length of dhcpv6 message
 *  \param[in]    DomainListOptPtr     Domain list is stored here
 *  \return       E_OK                 Domain list processed successfully
 *  \return       E_NOT_OK             Domain list not obtained
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VDecodeOptDomainList(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                       DataPtr,
  uint16                                                           DataLen,
  P2VAR(TcpIp_DhcpV6_OptDomainListType, AUTOMATIC, TCPIP_APPL_VAR) DomainListOptPtr);
#endif

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VRxAdvertise()
 *********************************************************************************************************************/
/*! \brief        Process dhcpv6 Rx advertise message
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller 
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    DataPtr          Data buffer
 *  \param[in]    DataLen          Length of dhcpv6 message
 *  \return       E_OK             Rx advertise message processed successfully
 *  \return       E_NOT_OK         Rx advertise message not valid
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VRxAdvertise(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen);


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VCalcRetransTimeout()
 *********************************************************************************************************************/
/*! \brief        Calculate and update retransmission time for dhcpv6 message
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller 
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    IsSolicit        Solicit Flag
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VCalcRetransTimeout(
  TcpIp_IpV6CtrlIterType   IpCtrlIdx,
  boolean                  IsSolicit);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VProcessValidateRxReplyOptions()
 *********************************************************************************************************************/
/*! \brief        Process the options in dhcpv6 reply messages
 *  \details      -
 *  \param[in]    IpCtrlIdx         Index of IP controller 
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   OptStatusCodePtr  Status code of option is stored here
 *  \param[out]   OptDnsServersPtr  DNS server option is stored here
 *  \param[out]   OptDomainListPtr  Domain name option is stored here
 *  \param[in]    DataPtr           Dhcpv6 data buffer
 *  \param[in]    DataLen           Length of dhcpv6 message
 *  \return       E_OK              Reply message options processed successfully
 *  \return       E_NOT_OK          Reply message options has invalid client/server id/ error code
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VProcessValidateRxReplyOptions(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx,
  IPV6_P2V(TcpIp_DhcpV6_OptStatusCodeType)   OptStatusCodePtr,
#if (TCPIP_SUPPORT_DNS == STD_ON)
  IPV6_P2V(TcpIp_DhcpV6_OptDnsServersType)   OptDnsServersPtr,
  IPV6_P2V(TcpIp_DhcpV6_OptDomainListType)   OptDomainListPtr,
#endif
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VProcessRxReplyIanaOption()
 *********************************************************************************************************************/
/*! \brief        Process Iana options in dhcpv6 reply messages
 *  \details      -
 *  \param[in]    DataPtr           Dhcpv6 data buffer       (only valid if rx options is enabled)
 *  \param[in]    DataLen           Length of dhcpv6 message (only valid if rx options is enabled)
 *  \param[in]    IpCtrlIdx         Index of IP controller 
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VProcessRxReplyIanaOption(
#if ((TCPIP_SUPPORT_DHCPV6_OPTIONS == STD_ON) && (TCPIP_DHCPV6_RX_OPTION_CNT > 0))
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr, 
  uint16                                     DataLen, 
#endif
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx
);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VCalcElapsedTime()
 *********************************************************************************************************************/
/*! \brief        This API calculates elapsed time since start of DHCPv6 address assignment.
 *  \details      -
 *  \param[in]    DhcpDataIdx      Index to the Dhcp data struct
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfDhcpV6Config()-1]
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VCalcElapsedTime(
    TcpIp_SizeOfDhcpV6DataType DhcpDataIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VTxPendingMessages()
 *********************************************************************************************************************/
/*! \brief        This API transmits pending DHCPv6 message.
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller 
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    DhcpDataIdx      Index to the Dhcp data struct
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfDhcpV6Config()-1]
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK
 *  \reentrant    TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VTxPendingMessages(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  TcpIp_SizeOfDhcpV6DataType DhcpDataIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VHandleStateRenewMessage()
 *********************************************************************************************************************/
/*! \brief        This API sends RENEW message or switch to REBIND if number of retransmissions has been reached
 *                for Renew State
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller 
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    DhcpDataIdx      Index to the Dhcp data struct
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfDhcpV6Config()-1]
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK
 *  \reentrant    TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VHandleStateRenewMessage(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  TcpIp_SizeOfDhcpV6DataType DhcpDataIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VHandleStateSolicitMessage()
 *********************************************************************************************************************/
/*! \brief        This API moves to state REQUEST if valid ADVERTISE message has been received from DHCPv6 server.
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller 
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    DhcpDataIdx      Index to the Dhcp data struct
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfDhcpV6Config()-1]
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK
 *  \reentrant    TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VHandleStateSolicitMessage(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  TcpIp_SizeOfDhcpV6DataType DhcpDataIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VHandleStateReqDecRebMessage()
 *********************************************************************************************************************/
/*! \brief        This API (Re-)Transmit message or restart DHCPv6 address assignment if number of retransmissions 
 *                has been reached for Request Decline or Rebind message
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller 
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    DhcpDataIdx      Index to the Dhcp data struct
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfDhcpV6Config()-1]
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK
 *  \reentrant    TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VHandleStateReqDecRebMessage(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  TcpIp_SizeOfDhcpV6DataType DhcpDataIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VHandleStateReleaseMessage()
 *********************************************************************************************************************/
/*! \brief        This API (re-)transmit Release message if number of retransmissions has been reached
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller 
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    DhcpDataIdx      Index to the Dhcp data struct
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfDhcpV6Config()-1]
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VHandleStateReleaseMessage(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  TcpIp_SizeOfDhcpV6DataType DhcpDataIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VRxHandleStateMsgAdv()
 *********************************************************************************************************************/
/*! \brief        This API handles Rx of DHCPv6 advertise messages
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller 
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    DhcpDataIdx      Index to the Dhcp data struct
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfDhcpV6Config()-1]
 *  \param[in]    DataPtr          Dhcpv6 data buffer
 *  \param[in]    DataLen          Length of dhcpv6 message
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VRxHandleStateMsgAdv(
  TcpIp_IpV6CtrlIterType                      IpCtrlIdx,
  TcpIp_SizeOfDhcpV6DataType                  DhcpDataIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)  DataPtr,
  uint16                                      DataLen);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VRxProcessMessage()
 *********************************************************************************************************************/
/*! \brief      This API handles Rx of DHCPv6 messages
 *  \details      -
 *  \param[in]    IpCtrlIdx        Index of IP controller 
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[in]    MsgType          Dhcpv6 message type
 *  \param[in]    DhcpDataIdx      Index to the Dhcp data struct
 *                                 CONSTRAINT: [0...TcpIp_GetSizeOfDhcpV6Config()-1]
 *  \param[in]    DataPtr          Dhcpv6 data buffer
 *  \param[in]    DataLen          Length of dhcpv6 message
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VRxProcessMessage(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx,
  uint8                                      MsgType,
  TcpIp_SizeOfDhcpV6DataType                 DhcpDataIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VUpdateRxReplyDhcpState()
 *********************************************************************************************************************/
/*! \brief        Handle the dhcpv6 reply message based on the dhcpv6 state
 *  \details      -
 *  \param[in]    IpCtrlIdx          Index of IP controller 
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   OptStatusCodePtr   Status code of the option is stored here
 *  \param[in]    OptDnsServersPtr   DNS server list option content
 *  \param[in]    OptDomainListPtr   DNS domain list option content
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VUpdateRxReplyDhcpState(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx,
#if (TCPIP_SUPPORT_DNS == STD_ON)
  IPV6_P2C(TcpIp_DhcpV6_OptDnsServersType)   OptDnsServersPtr,
  IPV6_P2C(TcpIp_DhcpV6_OptDomainListType)   OptDomainListPtr,
#endif
  IPV6_P2C(TcpIp_DhcpV6_OptStatusCodeType)   OptStatusCodePtr
  );

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VProcessRxReplyStatusCode()
 *********************************************************************************************************************/
/*! \brief        Process the status codes in dhcpv6 reply messages
 *  \details      -
 *  \param[in]    IpCtrlIdx          Index of IP controller 
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VProcessRxReplyStatusCode(
  TcpIp_IpV6CtrlIterType IpCtrlIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildIa()
 *********************************************************************************************************************/
/*! \brief        Build Iana option
 *  \details      -
 *  \param[in]    IpCtrlIdx          Index of IP controller 
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr             Message buffer
 *  \return       E_OK               Iana option built successfully
 *  \return       E_NOT_OK           Iana option not built 
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildIa(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildIaAddr()
 *********************************************************************************************************************/
/*! \brief        Build Ia address option
 *  \details      -
 *  \param[in]    IpCtrlIdx          Index of IP controller 
 *                                   CONSTRAINT: [0...TcpIp_GetSizeOfIpV6ctrl()-1]
 *  \param[out]   MsgPtr             Message buffer
 *  \return       E_OK               Iana option built successfully
 *  \return       E_NOT_OK           Iana option not built 
 *  \pre          DhcpV6 should be configured for the controller index
 *  \context      TASK|ISR
 *  \reentrant    FALSE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildIaAddr(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr);

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/* PRQA S 3453 FctLikeMacros */ /* MD_MSR_19.7 */

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
# if (defined(TCPIP_PROCESSOR_CANOEEMU) && (TCPIP_DHCPV6_VENABLE_CANOE_WRITE_STRING == STD_ON))
#  include "stdio.h"

#  define CANOE_DBG_MODULE_NAME "DHCPv6"

#  define CANOE_WRITE_STRING0(Txt) \
  CANoeAPI_WriteString("[" CANOE_DBG_MODULE_NAME "] " Txt);

/* PRQA S 1030,5013 5 */ /* MD_TcpIp_CANoeEmuDebug */
#  define CANOE_WRITE_STRINGF(Txt, ...) \
  _snprintf((char*)VCanoeWriteStrBuffer, sizeof(VCanoeWriteStrBuffer), \
  "[" CANOE_DBG_MODULE_NAME "] " Txt, __VA_ARGS__); \
  CANoeAPI_WriteString((const char *)(VCanoeWriteStrBuffer));

#  define CANOE_WRITE_STRING1(txt, p1)                     CANOE_WRITE_STRINGF(txt, p1)
#  define CANOE_WRITE_STRING2(txt, p1, p2)                 CANOE_WRITE_STRINGF(txt, p1, p2)
#  define CANOE_WRITE_STRING3(txt, p1, p2, p3)             CANOE_WRITE_STRINGF(txt, p1, p2, p3)
#  define CANOE_WRITE_STRING4(txt, p1, p2, p3, p4)         CANOE_WRITE_STRINGF(txt, p1, p2, p3, p4)
#  define CANOE_WRITE_STRING5(txt, p1, p2, p3, p4, p5)     CANOE_WRITE_STRINGF(txt, p1, p2, p3, p4, p5)
#  define CANOE_WRITE_STRING6(txt, p1, p2, p3, p4, p5, p6) CANOE_WRITE_STRINGF(txt, p1, p2, p3, p4, p5, p6)
# else
#  define CANOE_WRITE_STRING0(txt)
#  define CANOE_WRITE_STRING1(txt, p1)
#  define CANOE_WRITE_STRING2(txt, p1, p2)
#  define CANOE_WRITE_STRING3(txt, p1, p2, p3)
#  define CANOE_WRITE_STRING4(txt, p1, p2, p3, p4)
#  define CANOE_WRITE_STRING5(txt, p1, p2, p3, p4, p5)
#  define CANOE_WRITE_STRING6(txt, p1, p2, p3, p4, p5, p6)
# endif /* (defined(TCPIP_PROCESSOR_CANOEEMU) && (TCPIP_DHCPV6_VENABLE_CANOE_WRITE_STRING == STD_ON)) */
#endif

#define TCPIP_DHCPV6_GET_MSG_TYPE(MsgPtr) ((MsgPtr)->BufPtr[0])

/* PRQA S 0342 1 */ /* MD_MSR_19.13_0342 */
#define TCPIP_DHCPV6_CHANGE_STATE(DhcpV6DataIdx, NEW_STATE) TcpIp_DhcpV6_VChangeState((DhcpV6DataIdx), TCPIP_DHCPV6_STATE_##NEW_STATE)

/* PRQA S 0342, 0881 4 */ /* MD_MSR_19.13_0342, MD_DhcpV6_19.12_0881 */
#define TCPIP_DHCPV6_INIT_RETRANS_PARAMS(IpV6CtrlIdx, MSG) (TcpIp_DhcpV6_VSetRetransParams(IpV6CtrlIdx, \
                                              TCPIP_DHCPV6_##MSG##_TIMEOUT, TCPIP_DHCPV6_##MSG##_MAX_RT, \
                                              TCPIP_DHCPV6_##MSG##_MAX_RC, TCPIP_DHCPV6_##MSG##_MAX_RD))


#define TCPIP_DHCPV6_GENERATE_TRANS_ID(VAR)   ((VAR) = ((((VAR) + (uint32)(TcpIp_GetRandomNumber()) + 1) & 0x00FFFFFF) \
                                                        + ((uint32)IpCtrlIdx << 16)))

#define TCPIP_DHCPV6_RAND_FACTOR(BASE_VALUE)  (((BASE_VALUE) / 10) - (2 * TCPIP_MAIN_FCT_PERIOD_MSEC))


/* PRQA L:FctLikeMacros */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VCompareBytes()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(boolean, TCPIP_CODE) TcpIp_DhcpV6_VCompareBytes(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) Data1Ptr,
  uint16                                     Data1Len,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) Data2Ptr,
  uint16                                     Data2Len)
{
  uint16 IdIdx;
  boolean result = TRUE;

  if (Data1Len != Data2Len)
  {
    result = FALSE;
  }
  else
  {
    IdIdx = Data1Len;

    while (0 < IdIdx)
    {
      IdIdx--;

      if (Data1Ptr[IdIdx] != Data2Ptr[IdIdx])
      {
        result = FALSE;
        break;
      }
    }
  }

  return result;
} /* End of TcpIp_DhcpV6_VCompareBytes() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VInitClientId()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VInitClientId(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx     = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);
  TcpIp_SizeOfDhcpV6ConfigType dhcpConfigIdx = TcpIp_GetDhcpV6ConfigIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpDataIdx != TCPIP_NO_DHCPV6DATAIDXOFIPV6CTRL); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpDataIdx)->TypeNbo   = TCPIP_HTONS(0x01U);
  TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpDataIdx)->HwTypeNbo = TCPIP_HTONS(0x01U);
  TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpDataIdx)->TimeNbo   = 
                       TCPIP_HTONL((uint32)TcpIp_GetDuidTimeOfDhcpV6Config(dhcpConfigIdx));
  /* get physical address for client DUID */

  IpV6_GetPhysAddr(IpCtrlIdx, &(TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpDataIdx)->PhysAddr[0]));

} /* End of TcpIp_DhcpV6_VInitClientId() */


#if (TCPIP_DHCPV6_USE_RAND_FUNCTION == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VGetRandomValue()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(sint32, TCPIP_CODE) TcpIp_DhcpV6_VGetRandomValue(
  sint32 MinValue, 
  sint32 MaxValue)
{
  uint32 ValueRange;
  uint32 RndValue;

  if (MinValue < MaxValue)
  {
    ValueRange = ((uint32)(MaxValue - MinValue)) + 1;

    if (ValueRange <= 0xFFFFU)
    {
      /* 16bit random number [0..0xFFFF] is sufficient */
      RndValue = (uint32)(TcpIp_GetRandomNumber());
    }
    else
    {
      /* create 32bit random number [0..0xFFFFFFFF] by combining two 16bit random numbers */
      RndValue = (uint32)(((uint32)(TcpIp_GetRandomNumber()) << 16) | (uint32)(TcpIp_GetRandomNumber()));
    }

    RndValue %= ValueRange;
  }
  else
  {
    RndValue = 0;
  }

  return MinValue + (sint32)RndValue;

} /* End of TcpIp_DhcpV6_VGetRandomValue() */
#endif


/* TIMESTAMP FUNCTIONS */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VTimeCompare()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(boolean, IPV6_CODE) TcpIp_DhcpV6_VTimeCompare(
  TcpIp_DhcpV6_TimeType  RefTimestamp,
  TcpIp_DhcpV6_TimeType  Timestamp)
{
  boolean result = FALSE;
  if((RefTimestamp.S < Timestamp.S) || ((RefTimestamp.S == Timestamp.S) && (RefTimestamp.Ms < Timestamp.Ms)))
  {
    result = TRUE;
  }
  return result;
} /* End of TcpIp_DhcpV6_VTimeCompare() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VTimeSet()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, IPV6_CODE) TcpIp_DhcpV6_VTimeSet(
  P2VAR(TcpIp_DhcpV6_TimeType, AUTOMATIC, TCPIP_APPL_DATA)  TimestampPtr,
  uint32                                                    Seconds,
  uint32                                                    Milliseconds)
{
  TimestampPtr->S = Seconds;
  TimestampPtr->Ms = Milliseconds;
} /* End of TcpIp_DhcpV6_VTimeSet() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VTimeAddMs()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VTimeAddMs(
  P2VAR(TcpIp_DhcpV6_TimeType, AUTOMATIC, TCPIP_APPL_DATA) TimestampPtr,
  uint32                                                   Milliseconds)
{
  TimestampPtr->Ms += Milliseconds;

  if (TimestampPtr->Ms >= 1000)
  {
    TimestampPtr->S += (TimestampPtr->Ms / 1000);
    TimestampPtr->Ms = (TimestampPtr->Ms % 1000);
  }
} /* End of TcpIp_DhcpV6_VTimeAddMs() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VSetEventTime()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
TCPIP_LOCAL_INLINE FUNC(void, IPV6_CODE) TcpIp_DhcpV6_VSetEventTime(
  P2VAR(TcpIp_DhcpV6_TimeType, AUTOMATIC, TCPIP_APPL_DATA)  TimestampPtr,
  uint32                                                    Milliseconds)
{
   *TimestampPtr = TcpIp_DhcpV6_Time; 
   TcpIp_DhcpV6_VTimeAddMs(TimestampPtr, Milliseconds);
} /* End of TcpIp_DhcpV6_VSetEventTime() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VSetLifetimeS()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VSetLifetimeS(
  P2VAR(TcpIp_DhcpV6_TimeType, AUTOMATIC, TCPIP_APPL_VAR) TimestampPtr,
  uint32                                                  LifetimeS,
  P2VAR(TcpIp_DhcpV6_TimeType, AUTOMATIC, TCPIP_APPL_VAR) NextEventTimePtr)
{
  if (TCPIP_DHCPV6_LIFETIME_UNLIMITED > LifetimeS)
  {
    TimestampPtr->S  = TcpIp_DhcpV6_Time.S + LifetimeS;
    TimestampPtr->Ms = TcpIp_DhcpV6_Time.Ms;
  }
  else
  {
    TimestampPtr->S  = TCPIP_DHCPV6_LIFETIME_UNLIMITED;
    TimestampPtr->Ms = 0;
  }

  if ((NULL_PTR != NextEventTimePtr) && (TCPIP_DHCPV6_TIME_IS_LOWER(*TimestampPtr, *NextEventTimePtr) == TRUE)) /* PRQA S 3415 */ /* MD_TcpIp_12.4_CslReadOnly */
  {
    *NextEventTimePtr = *TimestampPtr;
  }

} /* End of TcpIp_DhcpV6_VSetLifetimeS() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VChangeState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC INLINE FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VChangeState(TcpIp_SizeOfDhcpV6DataType DhcpV6DataIdx, uint8 NewState)
{
  TcpIp_SetLastStateOfDhcpV6Data(DhcpV6DataIdx, TcpIp_GetStateOfDhcpV6Data(DhcpV6DataIdx));
  TcpIp_SetStateOfDhcpV6Data(DhcpV6DataIdx, NewState);

} /* End of TcpIp_DhcpV6_VChangeState() */

/* MISC FUNCTIONS */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VWriteOptionCode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC INLINE FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VWriteOptionCode(
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) DataPtr,
  uint16                                  OptCode)
{
  DataPtr[0] = (uint8)(OptCode >> 8);
  DataPtr[1] = (uint8)(OptCode);
}


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VSetRetransParams()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC INLINE FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VWriteOptionLen(
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) DataPtr,
  uint16                                  OptLen)
{
  DataPtr[2] = (uint8)(OptLen >> 8);
  DataPtr[3] = (uint8)(OptLen);
}


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VSetRetransParams()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC INLINE FUNC(uint16, TCPIP_CODE) TcpIp_DhcpV6_VReadOptionCode(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr)
{
  return (uint16)((uint16)DataPtr[0] << 8) | (DataPtr[1]);
}

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VSetRetransParams()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VSetRetransParams(
  TcpIp_IpV6CtrlIterType IpCtrlIdx, 
  uint32                 IRT, 
  uint32                 MRT, 
  uint8                  MRC, 
  uint32                 MRD
)
{
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->TxCount = 0;
  TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->InitRetransTimeout = IRT;
  TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->MaxRetransTime = MRT;
  TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->MaxRetransCount = MRC;

  if (MRD > 0)
  {
    TCPIP_DHCPV6_SET_EVENT_TIME_MS(TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->AbsRetransTimeout, MRD);
  }
  else
  {
    TCPIP_DHCPV6_SET_LIFETIME_S(TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->AbsRetransTimeout, 
                                TCPIP_DHCPV6_LIFETIME_UNLIMITED, (TcpIp_DhcpV6_TimeType*)NULL_PTR);
  }

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
  CANOE_WRITE_STRING4("Retrans Params: IRT: %dmsec, MRT: %dmsec, MRC: %d, MRD: %dmsec", IRT, MRT, MRC, MRD);
#endif
} /* End of TcpIp_DhcpV6_VSetRetransParams() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VCalcRetransTimeout()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VCalcRetransTimeout(
  TcpIp_IpV6CtrlIterType   IpCtrlIdx,
  boolean                  IsSolicit)
{
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);
  TcpIp_SizeOfDhcpV6ConfigType dhcpConfigIdx = TcpIp_GetDhcpV6ConfigIdxOfIpV6Ctrl(IpCtrlIdx);
  uint32 RndOffset = 0;

  TCPIP_ASSERT(dhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  /* #10 Check if retransmitting for the first time */
  if (TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->TxCount == 0)
  {
    /* #20 Calculate first retransmission based on Initial Retransmission Timeout (IRT) */
    TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->Timeout = 
                         TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->InitRetransTimeout;

    if (TcpIp_IsRandomizeTimeoutsOfDhcpV6Config(dhcpConfigIdx) == TRUE)
    {
      RndOffset = TCPIP_DHCPV6_RAND_FACTOR(TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->InitRetransTimeout);

      if (TRUE == IsSolicit)
      {
        TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->Timeout += (uint32)TcpIp_DhcpV6_VGetRandomValue(0, (sint32)RndOffset);
      }
      else
      {
        sint32 RndValue = (sint32)TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->Timeout;

        RndValue += TcpIp_DhcpV6_VGetRandomValue(-(sint32)RndOffset, (sint32)RndOffset);

        if (RndValue > 0)
        {
          TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->Timeout = (uint32)RndValue;
        }
        else
        {
          TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->Timeout = 0;
        }
      }
    }
  }
  else
  {
    /* #30 Calculate next retransmission based on previous retransmission timeout */

    if (TcpIp_IsRandomizeTimeoutsOfDhcpV6Config(dhcpConfigIdx) == TRUE)
    {
      RndOffset = TCPIP_DHCPV6_RAND_FACTOR(TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->Timeout);
    }

    TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->Timeout <<= TCPIP_DHCPV6_LSHIFT_MUL_2;

    if (TcpIp_IsRandomizeTimeoutsOfDhcpV6Config(dhcpConfigIdx) == TRUE)
    {
      sint32 RndValue = (sint32)TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->Timeout;

      RndValue += TcpIp_DhcpV6_VGetRandomValue(-(sint32)RndOffset, (sint32)RndOffset);

      TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->Timeout = (RndValue > 0) ? ((uint32)RndValue) : 0;
    }
  }
}
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VCalcTimeout()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VCalcTimeout(
  TcpIp_IpV6CtrlIterType                                  IpCtrlIdx, 
  P2VAR(TcpIp_DhcpV6_TimeType, AUTOMATIC, TCPIP_APPL_VAR) TimePtr, 
  boolean                                                 IsSolicit)
{
  uint32 RndOffset = 0;
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);
  TcpIp_SizeOfDhcpV6ConfigType dhcpConfigIdx = TcpIp_GetDhcpV6ConfigIdxOfIpV6Ctrl(IpCtrlIdx);
  Std_ReturnType result = E_OK;

  TCPIP_ASSERT(dhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  if (TCPIP_DHCPV6_TIME_EXPIRED(TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->AbsRetransTimeout) == TRUE)
  {
    result = E_NOT_OK;
  }

  /* RT = [-(IRT/10)...(IRT/10)] */

  /* #10 Check if maximum number of retransmission reached */
  else if (   ((TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->MaxRetransCount) > 0)
           && (TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->TxCount > TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->MaxRetransCount))
  {
    
    result = E_NOT_OK;
  }
  else
  {
    /* #20 Calculate retransmission timeout */
    TcpIp_DhcpV6_VCalcRetransTimeout(IpCtrlIdx, IsSolicit);

    if (   (TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->MaxRetransTime > 0)
        && (TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->Timeout > TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->MaxRetransTime))
    {
      /* limit Maximum Retransmission Time */

      if (TcpIp_IsRandomizeTimeoutsOfDhcpV6Config(dhcpConfigIdx) == TRUE)
      {
        RndOffset = TCPIP_DHCPV6_RAND_FACTOR(TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->MaxRetransTime);
      }

      TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->Timeout =
          TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->MaxRetransTime;

      if (TcpIp_IsRandomizeTimeoutsOfDhcpV6Config(dhcpConfigIdx) == TRUE)
      {
        sint32 RndValue = (sint32)TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->Timeout;

        RndValue += TcpIp_DhcpV6_VGetRandomValue(-(sint32)RndOffset, (sint32)RndOffset);

        TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->Timeout = (RndValue > 0) ? ((uint32)RndValue) : 0;
      }
    }

    *TimePtr = TcpIp_DhcpV6_Time;
    TcpIp_DhcpV6_VTimeAddMs(TimePtr, TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->Timeout);

    if (TCPIP_DHCPV6_TIME_IS_LOWER(TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->AbsRetransTimeout, *TimePtr) == TRUE)
    {
      /* maximum retransmission duration reached */
      *TimePtr = TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->AbsRetransTimeout;
    }

    TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->TxCount++;

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
    {
      uint32 AbsTimeout = 0;
      if (TCPIP_DHCPV6_LIFETIME_UNLIMITED > TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->AbsRetransTimeout.S)
      {

        AbsTimeout = TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->AbsRetransTimeout.S - TcpIp_DhcpV6_Time.S;
      }

      CANOE_WRITE_STRING5("Calculated retransmission timeout: %d/%d ms, transmission: %d/%d, abs timeout: %d", 
        TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->Timeout, 
        TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->MaxRetransTime, 
        TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->TxCount, 
        TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->MaxRetransCount, AbsTimeout);
    }
#endif
  }
  return result;
} /* End of TcpIp_DhcpV6_VCalcTimeout() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/* MESSAGE BUILDING FUNCTIONS */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VOptStackPushDataPos()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VOptStackPushDataPos(
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  Std_ReturnType Result;
#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* #10 Push current option onto stack if stack is not full */
  if (MsgPtr->OptStackPos < TCPIP_DHCPV6_OPT_STACK_SIZE)
  {
    MsgPtr->OptStartPos[MsgPtr->OptStackPos] = MsgPtr->MsgBufPos;
    MsgPtr->OptStackPos++;
    Result = E_OK;
  }
  else
  {
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
    CANOE_WRITE_STRING0("TcpIp_DhcpV6_VOptStackPushDataPos() Option Stack overflow!");
#endif
    Result = E_NOT_OK;
  }

  return Result;
} /* End of TcpIp_DhcpV6_VOptStackPushDataPos() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VOptStackPopDataPos()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VOptStackPopDataPos(
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr,
  P2VAR(uint16, AUTOMATIC, TCPIP_APPL_VAR)               DataPosPtr)
{
  Std_ReturnType Result;

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* #10 Pop current option from stack if stack is not empty */
  if (0 < MsgPtr->OptStackPos)
  {
    MsgPtr->OptStackPos--;
    *DataPosPtr = MsgPtr->OptStartPos[MsgPtr->OptStackPos];
    Result = E_OK;
  }
  else
  {
    Result = E_NOT_OK;
  }

  return Result;
} /* End of TcpIp_DhcpV6_VOptStackPopDataPos() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBeginMessage()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBeginMessage(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr,
  uint8                                                  MsgType)
{
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);
  TcpIp_CurrentTransIdOfDhcpV6DataType currTransId = TcpIp_GetCurrentTransIdOfDhcpV6Data(dhcpDataIdx);

  TCPIP_ASSERT(dhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 3 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr->MsgBufPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_PARAM,   E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(TCPIP_DHCPV6_MSG_HDR_LEN <= MsgPtr->MsgBufLen, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_PARAM,   E_NOT_OK);
#endif

  MsgPtr->MsgBufPos = 0;
  MsgPtr->TxPending = FALSE;

  /* #10 Write message type code */
  MsgPtr->MsgBufPtr[0] = MsgType;

  MsgPtr->OptStackPos = 0;

  /* #20 Generate and write 24bit transaction id */
  TCPIP_DHCPV6_GENERATE_TRANS_ID(currTransId);
  MsgPtr->MsgBufPtr[1] = (uint8)(currTransId >> 16);
  MsgPtr->MsgBufPtr[2] = (uint8)(currTransId >> 8);
  MsgPtr->MsgBufPtr[3] = (uint8)(currTransId);

  TcpIp_SetCurrentTransIdOfDhcpV6Data(dhcpDataIdx, currTransId);

  TcpIp_SetElapsedTimeMsOfDhcpV6Data(dhcpDataIdx, 0);

  MsgPtr->MsgBufPos = 4;

  /* #30 Add client identifier option into the dhcpv6 message */
  (void)TcpIp_DhcpV6_VAddOptClientIdent(IpCtrlIdx, MsgPtr); /* ignore return value, option should always fit into dhcp message */

  return E_OK;
} /* End of TcpIp_DhcpV6_VBeginMessage() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VEndMessage()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(uint16, TCPIP_CODE) TcpIp_DhcpV6_VEndMessage(
  TcpIp_IpV6CtrlIterType                                  IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_DATA) MsgPtr)
{

#if ((TCPIP_SUPPORT_DHCPV6_OPTIONS == STD_ON) && (TCPIP_DHCPV6_TX_OPTION_CNT > 0))
  (void)TcpIp_DhcpV6_VAddUserOptions(IpCtrlIdx, MsgPtr);
#endif

  return MsgPtr->MsgBufPos;
} /* End of TcpIp_DhcpV6_VEndMessage() */


/* OPTION ENCODING FUNCTIONS */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VAddRawOpt()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VAddRawOpt(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr,
  uint16                                                 OptType,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)             OptDataPtr,
  uint16                                                 OptDataLen)
{
  IPV6_UNUSED_PARAMETER(IpCtrlIdx);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 3 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != OptDataPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(0 < OptDataLen, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_PARAM,   E_NOT_OK);
#endif

  TcpIp_DhcpV6_VWriteOptionCode(&MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos], OptType);
  if (OptType == TCPIP_DHCPV6_OPT_ID_CLIENT_FQDN)
  {
    TcpIp_DhcpV6_VWriteOptionLen(&MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos], (OptDataLen +1));
  }
  else
  {
    TcpIp_DhcpV6_VWriteOptionLen(&MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos], OptDataLen);
  }

  MsgPtr->MsgBufPos += TCPIP_DHCPV6_OPT_HDR_LEN;

  if (OptType == TCPIP_DHCPV6_OPT_ID_CLIENT_FQDN)
  {
    /* IPv6
        0 1 2 3 4 5 6 7
       +-+-+-+-+-+-+-+-+
       |  MBZ    |N|O|S|
       +-+-+-+-+-+-+-+-+
       S = 0   the server SHOULD NOT perform the A RR (FQDN-to-address) DNS updates
       O = 0   must be 0
       N = 1   the server SHOULD NOT perform any DNS updates
    */
    MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos] = 0x04;  /* set flag N */
    MsgPtr->MsgBufPos++;
  }

  VStdMemCpy(&MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos], OptDataPtr, OptDataLen);

  MsgPtr->MsgBufPos += OptDataLen;

  return E_OK;
} /* End of TcpIp_DhcpV6_VAddRawOpt() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VAddOptClientIdent()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VAddOptClientIdent(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);
  uint8 ClientDuidOfDhcpV6Data[sizeof(TcpIp_DhcpV6_DuIdType1)]; /* PRQA S 0781 */ /* MD_TCPIP_5.6_0781 */

  TCPIP_ASSERT(dhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  TCPIP_PUT_UINT16_RAW(ClientDuidOfDhcpV6Data, TCPIP_DHCPV6_DUID1_OPT_OFF_TYPENBO,   TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpDataIdx)->TypeNbo);
  TCPIP_PUT_UINT16_RAW(ClientDuidOfDhcpV6Data, TCPIP_DHCPV6_DUID1_OPT_OFF_HWTYPENBO, TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpDataIdx)->HwTypeNbo);
  TCPIP_PUT_UINT32_RAW(ClientDuidOfDhcpV6Data, TCPIP_DHCPV6_DUID1_OPT_OFF_TIMENBO,   TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpDataIdx)->TimeNbo);
  IPV6_LL_ADDR_COPY(&ClientDuidOfDhcpV6Data[TCPIP_DHCPV6_DUID1_OPT_OFF_PHYSADDR], &(TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpDataIdx)->PhysAddr[0]));

  return TcpIp_DhcpV6_VAddRawOpt(IpCtrlIdx, MsgPtr, TCPIP_DHCPV6_OPT_CLIENTID, ClientDuidOfDhcpV6Data, TCPIP_DHCPV6_CLIENT_DUID_LEN);
} /* End of TcpIp_DhcpV6_VAddOptClientIdent() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VAddOptServerIdent()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VAddOptServerIdent(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx, 
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  return TcpIp_DhcpV6_VAddRawOpt(IpCtrlIdx, MsgPtr, TCPIP_DHCPV6_OPT_SERVERID, 
    (P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA))&(TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpDataIdx)->ServerId[0]),
    TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpDataIdx)->ServerIdLen);
} /* End of TcpIp_DhcpV6_VAddOptServerIdent() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBeginOptIaNa()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBeginOptIaNa(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr,
  uint32                                                 IaId,
  uint32                                                 T1,
  uint32                                                 T2)
{
  Std_ReturnType result = E_OK;
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) OptIaNaHdrPtr;

  IPV6_UNUSED_PARAMETER(IpCtrlIdx);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  if (E_OK != TcpIp_DhcpV6_VOptStackPushDataPos(MsgPtr))
  {
    result = E_NOT_OK;
  }
  else
  {
    /* #10 Update option code and Iana header params */
    TcpIp_DhcpV6_VWriteOptionCode(&MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos], TCPIP_DHCPV6_OPT_IA_NA);

    /* option length currently unknown, since it depends on the options contained in this option */
    MsgPtr->MsgBufPos += TCPIP_DHCPV6_OPT_HDR_LEN;

    OptIaNaHdrPtr = &MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos];

    TCPIP_PUT_UINT32(OptIaNaHdrPtr, TCPIP_DHCPV6_IANA_OPT_OFF_IAIDNBO, TCPIP_HTONL(IaId));
    TCPIP_PUT_UINT32(OptIaNaHdrPtr, TCPIP_DHCPV6_IANA_OPT_OFF_T1NBO, TCPIP_HTONL(T1));
    TCPIP_PUT_UINT32(OptIaNaHdrPtr, TCPIP_DHCPV6_IANA_OPT_OFF_T2NBO, TCPIP_HTONL(T2));

    MsgPtr->MsgBufPos += sizeof(TcpIp_DhcpV6_OptIaNaHdrRawType);
  }

  return result;
} /* End of TcpIp_DhcpV6_VBeginOptIaNa() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VEndOptIaNa()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VEndOptIaNa(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  uint16 TmpOptStartPos;
  Std_ReturnType result = E_OK;

  IPV6_UNUSED_PARAMETER(IpCtrlIdx);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif
  /* #10 Validate if the iana option has been successfully constructed */
  if (E_OK != TcpIp_DhcpV6_VOptStackPopDataPos(MsgPtr, &TmpOptStartPos))
  {
    result = E_NOT_OK;
  }
  else if (TCPIP_DHCPV6_OPT_IA_NA != TcpIp_DhcpV6_VReadOptionCode(&MsgPtr->MsgBufPtr[TmpOptStartPos]))
  {
    result = E_NOT_OK;
  }
  else
  {
    /* #20 Write the option length value into the Iana option header */
    TcpIp_DhcpV6_VWriteOptionLen(&MsgPtr->MsgBufPtr[TmpOptStartPos],
      (uint16)(MsgPtr->MsgBufPos - TmpOptStartPos - TCPIP_DHCPV6_OPT_HDR_LEN));
  }

  return result;
} /* End of TcpIp_DhcpV6_VEndOptIaNa() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBeginOptIaAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBeginOptIaAddr(
  TcpIp_IpV6CtrlIterType                                  IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR)  MsgPtr,
  P2CONST(IpBase_AddrIn6Type, AUTOMATIC, TCPIP_APPL_DATA) AddrPtr,
  uint32                                                  PreferredLifetime,
  uint32                                                  ValidLifetime)
{
  Std_ReturnType result = E_OK;
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) OptIaAddrHdrPtr;

  IPV6_UNUSED_PARAMETER(IpCtrlIdx);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 2 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != AddrPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* push current option onto stack */
  if (E_OK != TcpIp_DhcpV6_VOptStackPushDataPos(MsgPtr))
  {
    result = E_NOT_OK;
  }
  else
  {
    /* #10 Update option code and Iana header params */
    TcpIp_DhcpV6_VWriteOptionCode(&MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos], TCPIP_DHCPV6_OPT_IAADDR);

    /* option length currently unknown, since it depends on the options contined in this option */
    MsgPtr->MsgBufPos += TCPIP_DHCPV6_OPT_HDR_LEN;
    OptIaAddrHdrPtr = &MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos];

    IPV6_ADDR_COPY(OptIaAddrHdrPtr[TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_ADDR], *AddrPtr);
    TCPIP_PUT_UINT32(OptIaAddrHdrPtr, TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_PREFLIFENBO, TCPIP_HTONL(PreferredLifetime));
    TCPIP_PUT_UINT32(OptIaAddrHdrPtr, TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_VALDLIFENBO, TCPIP_HTONL(ValidLifetime));

    MsgPtr->MsgBufPos += sizeof(TcpIp_DhcpV6_OptIaAddrHdrRawType);
  }
  return result;
} /* End of TcpIp_DhcpV6_VBeginOptIaAddr() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VEndOptIaAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VEndOptIaAddr(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  uint16 TmpOptStartPos;
  Std_ReturnType result = E_OK;
  IPV6_UNUSED_PARAMETER(IpCtrlIdx);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* #10 Validate if the ia address option has been successfully constructed */
  if (E_OK != TcpIp_DhcpV6_VOptStackPopDataPos(MsgPtr, &TmpOptStartPos))
  {
    result = E_NOT_OK;
  }
  else if (TcpIp_DhcpV6_VReadOptionCode(&MsgPtr->MsgBufPtr[TmpOptStartPos]) != TCPIP_DHCPV6_OPT_IAADDR)
  {
    result = E_NOT_OK;
  }
  else
  {
    /* #20 Write the option length value into the Ia address option header */
    TcpIp_DhcpV6_VWriteOptionLen(&MsgPtr->MsgBufPtr[TmpOptStartPos], 
      (uint16)(MsgPtr->MsgBufPos - TmpOptStartPos - TCPIP_DHCPV6_OPT_HDR_LEN));
  }
  return result;
} /* End of TcpIp_DhcpV6_VEndOptIaAddr() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VAddOptReqOpt()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VAddOptReqOpt(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr,
  P2CONST(uint16, AUTOMATIC, TCPIP_APPL_DATA)            OptCodeArray,
  uint8                                                  OptCodeCount)
{
  uint8 OptCodeIdx;

  IPV6_UNUSED_PARAMETER(IpCtrlIdx);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 2 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(((0 == OptCodeCount) || (NULL_PTR != OptCodeArray)), TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* #10 Write option code and length into message buffer */
  TcpIp_DhcpV6_VWriteOptionCode(&MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos], TCPIP_DHCPV6_OPT_ORO);

#if ((TCPIP_SUPPORT_DHCPV6_OPTIONS == STD_ON) && (TCPIP_DHCPV6_REQ_OPTION_CNT > 0))
  TcpIp_DhcpV6_VWriteOptionLen(&MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos], ((OptCodeCount + TCPIP_DHCPV6_REQ_OPTION_CNT) << TCPIP_DHCPV6_LSHIFT_MUL_2));
#else
  TcpIp_DhcpV6_VWriteOptionLen(&MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos], (uint16)(OptCodeCount << TCPIP_DHCPV6_LSHIFT_MUL_2));
#endif

  MsgPtr->MsgBufPos += TCPIP_DHCPV6_OPT_HDR_LEN;

  /* #20 Add the options list into the message buffer */
  for (OptCodeIdx = 0; OptCodeIdx < OptCodeCount; OptCodeIdx++)
  {
    MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos]   = (uint8)(OptCodeArray[OptCodeIdx] >> 8);
    MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos+1] = (uint8)(OptCodeArray[OptCodeIdx]);
    MsgPtr->MsgBufPos += 2;
  }

#if ((TCPIP_SUPPORT_DHCPV6_OPTIONS == STD_ON) && (TCPIP_DHCPV6_REQ_OPTION_CNT > 0))
  {
    uint8 RxOptIdx;
    for (RxOptIdx = 0; RxOptIdx < TCPIP_DHCPV6_REQ_OPTION_CNT; RxOptIdx++)
    {
      if (   (TRUE == TcpIp_DhcpV6_ReqOptConstData[RxOptIdx].SendOnAllCtrls)
          || (MsgPtr->CtrlIdx == TcpIp_DhcpV6_ReqOptConstData[RxOptIdx].CtrlIdx))
      {
        MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos]   = (uint8)(TcpIp_DhcpV6_ReqOptConstData[RxOptIdx].OptId >> 8);
        MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos+1] = (uint8)(TcpIp_DhcpV6_ReqOptConstData[RxOptIdx].OptId);
        MsgPtr->MsgBufPos += 2;
      }
    }
  }
#endif

  return E_OK;
} /* End of TcpIp_DhcpV6_VAddOptReqOpt() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VAddOptElapsedTime()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VAddOptElapsedTime(
  TcpIp_IpV6CtrlIterType                                  IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR)  MsgPtr)
{
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);
  uint32 ElapsedTime;

  TCPIP_ASSERT(dhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  TcpIp_DhcpV6_VWriteOptionCode(&MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos], TCPIP_DHCPV6_OPT_ELAPSED_TIME);
  TcpIp_DhcpV6_VWriteOptionLen( &MsgPtr->MsgBufPtr[MsgPtr->MsgBufPos], TCPIP_DHCPV6_OPT_ELAPSED_TIME_LEN);

  MsgPtr->MsgBufPos += TCPIP_DHCPV6_OPT_HDR_LEN;

  ElapsedTime = (TcpIp_GetElapsedTimeMsOfDhcpV6Data(dhcpDataIdx) / 10);

  if (ElapsedTime > 0x0000FFFF)
  {
    ElapsedTime = 0xFFFF;
  }

  TCPIP_PUT_UINT16(MsgPtr->MsgBufPtr, (MsgPtr->MsgBufPos + TCPIP_DHCPV6_ELAPSEDTIME_OPT_OFF_ELAPSEDTIMENBO), (uint16)ElapsedTime);
  MsgPtr->MsgBufPos += sizeof(TcpIp_DhcpV6_OptElapsedTimeRawType);

  return E_OK;
} /* End of TcpIp_DhcpV6_VAddOptElapsedTime() */

#if ((TCPIP_SUPPORT_DHCPV6_OPTIONS == STD_ON) && (TCPIP_DHCPV6_TX_OPTION_CNT > 0))
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VAddUserOptions()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VAddUserOptions(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  TcpIp_SizeOfDhcpV6TxOption39InfoType txOptInfoIdx = TcpIp_GetDhcpV6TxOption39InfoIdxOfIpV6Ctrl(IpCtrlIdx);

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  if (0 < TcpIp_GetOptLenOfDhcpV6TxOption39Info(txOptInfoIdx))
  {
    TcpIp_SizeOfDhcpV6TxOption39Type txOpt39Idx = TcpIp_GetDhcpV6TxOption39StartIdxOfIpV6Ctrl(IpCtrlIdx);
    (void)TcpIp_DhcpV6_VAddRawOpt(IpCtrlIdx, MsgPtr, 
      TCPIP_DHCPV6_OPT_ID_CLIENT_FQDN, TcpIp_GetAddrDhcpV6TxOption39(txOpt39Idx), 
      TcpIp_GetOptLenOfDhcpV6TxOption39Info(txOptInfoIdx));
  }
  return E_OK;
} /* End of TcpIp_DhcpV6_VAddUserOptions() */
#endif


/******************************
 * MESSAGE ENCODING FUNCTIONS *
 ******************************/

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildSolicit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildSolicit(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  Std_ReturnType Result;
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
  CANOE_WRITE_STRING0("TcpIp_DhcpV6_VTxSolicit()");
#endif
  /* #10 Begin dhcpv6 message */
  Result = TcpIp_DhcpV6_VBeginMessage(IpCtrlIdx, MsgPtr, TCPIP_DHCPV6_MSG_SOL);

  /* #20 Add option request option [RFC3315 17.1.1. Creation of Solicit Messages] */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VAddOptReqOpt(IpCtrlIdx, MsgPtr, &TcpIp_DhcpV6_OptionRequestList[0],
      TCPIP_DHCPV6_OPT_REQ_OPT_LIST_LEN);
  }
  /* #30 Add Iana option */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VBeginOptIaNa(IpCtrlIdx, MsgPtr,
      TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->IaId, 0, 0);
  }
  /* #40 End Iana option */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VEndOptIaNa(IpCtrlIdx, MsgPtr);
  }
  /* #50 End dhcpv6 message */
  if (E_OK == Result)
  {
    (void)TcpIp_DhcpV6_VEndMessage(IpCtrlIdx, MsgPtr);
  }

  return Result;
} /* End of TcpIp_DhcpV6_VBuildSolicit() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildInfoRequest()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildInfoRequest(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  Std_ReturnType Result;

  TCPIP_ASSERT(TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(IpCtrlIdx) == TRUE); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
  CANOE_WRITE_STRING0("TcpIp_DhcpV6_VBuildInfoRequest()");
#endif
  /* #10 Begin dhcpv6 message */
  Result = TcpIp_DhcpV6_VBeginMessage(IpCtrlIdx, MsgPtr, TCPIP_DHCPV6_MSG_INF);

  /* #20 Add option request option [RFC3315 18.1.5. Creation and Transmission of Information-request Messages] */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VAddOptReqOpt(IpCtrlIdx, MsgPtr,
      &TcpIp_DhcpV6_OptionRequestList[TCPIP_DHCPV6_OPT_REQ_OPT_LIST_EXTRA_OPT_OFS],
      TCPIP_DHCPV6_OPT_REQ_OPT_LIST_LEN - TCPIP_DHCPV6_OPT_REQ_OPT_LIST_EXTRA_OPT_OFS);
  }
  /* #30 End dhcpv6 message */
  if (E_OK == Result)
  {
    (void)TcpIp_DhcpV6_VEndMessage(IpCtrlIdx, MsgPtr);
  }

  return Result;
} /* End of TcpIp_DhcpV6_VBuildInfoRequest() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildRelease()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildRelease(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  Std_ReturnType Result;

  TCPIP_ASSERT(TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(IpCtrlIdx) == TRUE); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
  CANOE_WRITE_STRING0("TcpIp_DhcpV6_VBuildRelease()");
#endif
  /* #10 Begin dhcpv6 message */
  Result = TcpIp_DhcpV6_VBeginMessage(IpCtrlIdx, MsgPtr, TCPIP_DHCPV6_MSG_REL);
  
  /* #20 Add server identifier */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VAddOptServerIdent(IpCtrlIdx, MsgPtr);
  }

  /* #30 Add Ia address option */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VBuildIa(IpCtrlIdx, MsgPtr);
  }

  /* #40 End dhcpv6 message */
  if (E_OK == Result)
  {
    (void)TcpIp_DhcpV6_VEndMessage(IpCtrlIdx, MsgPtr);
  }

  return Result;
} /* End of TcpIp_DhcpV6_VBuildRelease() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildIaAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildIaAddr(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  Std_ReturnType Result;
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  /* invoke IA Address option build begin and end functions */
  Result = TcpIp_DhcpV6_VBeginOptIaAddr(IpCtrlIdx, MsgPtr,
    &(TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->AddrLease.Addr), 0, 0);

  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VEndOptIaAddr(IpCtrlIdx, MsgPtr);
  }
  return Result;
}

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildIa()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildIa(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  Std_ReturnType Result;
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  Result = TcpIp_DhcpV6_VBeginOptIaNa(IpCtrlIdx, MsgPtr, TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->IaId, 0, 0);

  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VBuildIaAddr(IpCtrlIdx, MsgPtr);
  }

  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VEndOptIaNa(IpCtrlIdx, MsgPtr);
  }
  return Result;
}

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildRenew()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildRenew(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  Std_ReturnType Result;

  TCPIP_ASSERT(TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(IpCtrlIdx) == TRUE); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
  CANOE_WRITE_STRING0("TcpIp_DhcpV6_VBuildRenew()");
#endif

  /* #10 Begin dhcpv6 message */
  Result = TcpIp_DhcpV6_VBeginMessage(IpCtrlIdx, MsgPtr, TCPIP_DHCPV6_MSG_REN);

  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VAddOptServerIdent(IpCtrlIdx, MsgPtr);
  }

  /* #20 Add ia address option */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VBuildIa(IpCtrlIdx, MsgPtr);
  }

  /* #30 Add option request option [RFC3315 18.1.3. Creation and Transmission of Renew Messages] */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VAddOptReqOpt(IpCtrlIdx, MsgPtr, &TcpIp_DhcpV6_OptionRequestList[0],
      TCPIP_DHCPV6_OPT_REQ_OPT_LIST_LEN);
  }

  /* #40 End dhcpv6 message */
  if (E_OK == Result)
  {
    (void)TcpIp_DhcpV6_VEndMessage(IpCtrlIdx, MsgPtr);
  }

  return Result;
} /* End of TcpIp_DhcpV6_VBuildRenew() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildRebind()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildRebind(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  Std_ReturnType Result;

  TCPIP_ASSERT(TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(IpCtrlIdx) == TRUE); /* Assert that DhcpV6 is configured for the IpCtrlIdx */
#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
  CANOE_WRITE_STRING0("TcpIp_DhcpV6_VBuildRebind()");
#endif
  /* #10 Begin dhcpv6 message */
  Result = TcpIp_DhcpV6_VBeginMessage(IpCtrlIdx, MsgPtr, TCPIP_DHCPV6_MSG_REB);

  /* #20 Add ia address option */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VBuildIa(IpCtrlIdx, MsgPtr);
  }

  /* #30 Add option request list */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VAddOptReqOpt(IpCtrlIdx, MsgPtr,
      &TcpIp_DhcpV6_OptionRequestList[0], TCPIP_DHCPV6_OPT_REQ_OPT_LIST_LEN);
  }
  /* #40 End dhcpv6 message */
  if (E_OK == Result)
  {
    (void)TcpIp_DhcpV6_VEndMessage(IpCtrlIdx, MsgPtr);
  }

  return Result;
} /* End of TcpIp_DhcpV6_VBuildRebind() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildDecline()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildDecline(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  Std_ReturnType Result;

  TCPIP_ASSERT(TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(IpCtrlIdx) == TRUE); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
  CANOE_WRITE_STRING0("TcpIp_DhcpV6_VBuildDecline()");
#endif
  /* #10 Begin dhcpv6 message */
  Result = TcpIp_DhcpV6_VBeginMessage(IpCtrlIdx, MsgPtr, TCPIP_DHCPV6_MSG_DEC);

  /* #20 Add server identifier */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VAddOptServerIdent(IpCtrlIdx, MsgPtr);
  }

  /* #30 Add ia address option */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VBuildIa(IpCtrlIdx, MsgPtr);
  }

  /* #40 End dhcpv6 message */
  if (E_OK == Result)
  {
    (void)TcpIp_DhcpV6_VEndMessage(IpCtrlIdx, MsgPtr);
  }

  return Result;
} /* End of TcpIp_DhcpV6_VBuildDecline() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildConfirm()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildConfirm(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  Std_ReturnType Result;

  TCPIP_ASSERT(TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(IpCtrlIdx) == TRUE); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 3 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr->MsgBufPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_PARAM,   E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(TCPIP_DHCPV6_MSG_HDR_LEN <= MsgPtr->MsgBufLen, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_PARAM,   E_NOT_OK);
#endif

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
  CANOE_WRITE_STRING0("TcpIp_DhcpV6_VBuildConfirm()");
#endif
  /* #10 Begin dhcpv6 message */
  Result = TcpIp_DhcpV6_VBeginMessage(IpCtrlIdx, MsgPtr, TCPIP_DHCPV6_MSG_CNF);

  /* #20 Add ia address option */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VBuildIa(IpCtrlIdx, MsgPtr);
  }

  /* #30 End dhcpv6 message */
  if (E_OK == Result)
  {
    (void)TcpIp_DhcpV6_VEndMessage(IpCtrlIdx, MsgPtr);
  }

  return Result;
} /* End of TcpIp_DhcpV6_VBuildConfirm() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VBuildRequest()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VBuildRequest(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  Std_ReturnType Result;
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* #10 Begin dhcpv6 message */
  Result = TcpIp_DhcpV6_VBeginMessage(IpCtrlIdx, MsgPtr, TCPIP_DHCPV6_MSG_REQ);

  /* #20 Add server identifier */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VAddOptServerIdent(IpCtrlIdx, MsgPtr);
  }

  /* #30 Add option request option [RFC3315 18.1.1. Creation and Transmission of Request Messages ] */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VAddOptReqOpt(IpCtrlIdx, MsgPtr,
      &TcpIp_DhcpV6_OptionRequestList[0], TCPIP_DHCPV6_OPT_REQ_OPT_LIST_LEN);
  }


  /* #40 Add IA_NA option */
  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VBeginOptIaNa(IpCtrlIdx, MsgPtr,
      TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->IaId, 0, 0);
  }

  if (E_OK == Result)
  {
    Result = TcpIp_DhcpV6_VEndOptIaNa(IpCtrlIdx, MsgPtr);
  }

  /* #50 End dhcpv6 message */
  if (E_OK == Result)
  {
    (void)TcpIp_DhcpV6_VEndMessage(IpCtrlIdx, MsgPtr);
  }

  return Result;
} /* End of TcpIp_DhcpV6_VBuildRequest() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/* DHCPv6 MESSATE TX */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VTriggerTx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VTriggerTx(P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR) MsgPtr)
{
  MsgPtr->TxPending = TRUE;
} /* End of TcpIp_DhcpV6_VTriggerTx() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VTxMessage()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VTxMessage(
  TcpIp_IpV6CtrlIterType                                  IpCtrlIdx,
  P2VAR(TcpIp_DhcpV6_MsgType, AUTOMATIC, TCPIP_APPL_VAR)  MsgPtr)
{
  Std_ReturnType                   result;
  uint16                           oldBufPos;
  uint8                            *bufPtr;
  TcpIp_IpTxRequestDescriptorType  ipTxReqDesc;
  uint16                           bufLenByte;
  uint16                           lenByte;

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 1 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != MsgPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif
  
  TCPIP_ASSERT(TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(IpCtrlIdx) == TRUE); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  /* store current message length */
  oldBufPos = MsgPtr->MsgBufPos;

  result = TcpIp_DhcpV6_VAddOptElapsedTime(IpCtrlIdx, MsgPtr);

  if (E_OK == result)
  {
    TcpIp_LocalAddrV6IterType ipAddrIdx = TcpIp_GetLocalAddrV6BcIdxOfIpV6Ctrl(IpCtrlIdx);

    lenByte = MsgPtr->MsgBufPos +  sizeof(TcpIp_Udp_HdrType);
    bufLenByte = lenByte;  /* Add UDP Header length */

    if (BUFREQ_OK == IpV6_ProvideTxBuffer(&ipAddrIdx, TcpIp_GetIpV6SocketDynDhcpIdxOfIpV6General(TCPIP_IPV6_GENERAL_IDX), &TcpIp_DhcpV6_Addr_All_DHCP_Relay_Agents_and_Servers, &bufPtr, &bufLenByte, &ipTxReqDesc, FALSE))
    {
      /* Fill up UDP Header fields */
      TCPIP_PUT_UINT16(bufPtr, UDP_HDR_OFF_SRCPORT, TCPIP_DHCPV6_CLIENT_PORT);
      TCPIP_PUT_UINT16(bufPtr, UDP_HDR_OFF_TGTPORT, TCPIP_DHCPV6_SERVER_PORT);
      TCPIP_PUT_UINT16(bufPtr, UDP_HDR_OFF_LENBYTE, lenByte);
      TCPIP_PUT_UINT16(bufPtr, UDP_HDR_OFF_CHKSUM, 0);

      IpBase_Copy((IpBase_CopyDataType*)&bufPtr[sizeof(TcpIp_Udp_HdrType)], (IpBase_CopyDataType*)&MsgPtr->MsgBufPtr[0], MsgPtr->MsgBufPos);

      /* UDP checksum is claculated by lower layer (IPv6 or in hardware) */
      result = IpV6_Transmit(TcpIp_GetIpV6SocketDynDhcpIdxOfIpV6General(TCPIP_IPV6_GENERAL_IDX), &ipTxReqDesc, TCPIP_PROTOCOL_UDP, lenByte, FALSE, 0, FALSE);
    }

    /* remove elapsed time option from message buffer */
    MsgPtr->MsgBufPos = oldBufPos;
  }

  return result;
} /* End of TcpIp_DhcpV6_VTxMessage() */


/* OPTION DECODING */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VGetNextOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
STATIC FUNC(boolean, TCPIP_CODE) TcpIp_DhcpV6_VGetNextOption(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                     DataPtr,
  uint16                                                         DataLen,
  P2VAR(TcpIp_DhcpV6_OptLocationType, AUTOMATIC, TCPIP_APPL_VAR) OptPosPtr)
{
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) OptPtr;
  boolean result = TRUE;
#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 2 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != DataPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != OptPosPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  if (TCPIP_DHCPV6_GET_OPT_OK != OptPosPtr->ErrCode)
  {
    /* #10 Return False if the previous get option operation failed */
    result = FALSE;
    /* Clear parameters of the OptPos argument */
    OptPosPtr->OptCode = 0;
    OptPosPtr->OptOfs = sizeof(TcpIp_DhcpV6_OptIaNaHdrRawType);
    OptPosPtr->OptLen = 0;
  }
  else
  {
    OptPosPtr->OptOfs += OptPosPtr->OptLen;

    if (OptPosPtr->OptOfs == DataLen)
    {
      /* #20 return False if all options have been read */
      result = FALSE;
      OptPosPtr->OptLen  = 0;
      OptPosPtr->OptCode = 0;
    }
    else  if ((OptPosPtr->OptOfs + TCPIP_DHCPV6_OPT_HDR_LEN) > DataLen)
    {
      /* #30 Return False if there is not enough space left in buffer for header of next option */
      result = FALSE;
      /* Update error code in the OptPos */
      OptPosPtr->ErrCode = TCPIP_DHCPV6_GET_OPT_INV_HDR_LENGTH;
      OptPosPtr->OptLen  = 0;
      OptPosPtr->OptCode = 0;
    }
    else
    {
      /* #40 Process next option in the data buffer and store in the OptPos */
      OptPtr = &DataPtr[OptPosPtr->OptOfs];

      OptPosPtr->OptCode = (uint16)(((uint16)OptPtr[0] << 8) | ((uint16)OptPtr[1]));
      OptPosPtr->OptLen  = (uint16)(((uint16)OptPtr[2] << 8) | ((uint16)OptPtr[3]));

      OptPosPtr->OptOfs += TCPIP_DHCPV6_OPT_HDR_LEN;

      if ((OptPosPtr->OptOfs + OptPosPtr->OptLen) > DataLen)
      {
        /* #50 Return False if the option data length exceeds data buffer length */
        OptPosPtr->ErrCode = TCPIP_DHCPV6_GET_OPT_INV_LENGTH;
        result = FALSE;
      }
    }
  }
  return result;
} /* End of TcpIp_DhcpV6_VGetNextOption() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VDecodeOptIaAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VDecodeOptIaAddr(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                   DataPtr,
  uint16                                                       DataLen,
#if (TCPIP_DHCPV6_ENABLE_DYNAMIC_IA_NA == STD_ON)
  P2VAR(TcpIp_DhcpV6_OptIaAddrType, AUTOMATIC, TCPIP_APPL_VAR) DynIaAddrPtr,
  uint8                                                        DynIaAddrCount
#else
  P2VAR(TcpIp_DhcpV6_OptIaAddrType, AUTOMATIC, TCPIP_APPL_VAR) IaAddrPtr
#endif
)
{
  TcpIp_DhcpV6_OptLocationType OptLoc;

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 2 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != DataPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(0 < DataLen, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_PARAM,   E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != IaAddrPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* check minimum length of IAADDR option */
  if (TCPIP_DHCPV6_OPT_IAADDR_HDR_LEN > DataLen)
  {
    return E_NOT_OK;
  }

  OptLoc.OptOfs = sizeof(TcpIp_DhcpV6_OptIaAddrHdrRawType);
  OptLoc.OptLen = 0;
  OptLoc.ErrCode = TCPIP_DHCPV6_GET_OPT_OK;

#if (TCPIP_DHCPV6_ENABLE_DYNAMIC_IA_NA == STD_ON)
  {
    boolean IaAddrIdxValid = FALSE;

    for (IaAddrIdx = 0; IaAddrIdx < DynIaAddrCount; IaAddrIdx++)
    {
      if (FALSE == DynIaAddrPtr[IaAddrIdx].Valid)
      {
        IPV6_ADDR_COPY(DynIaAddrPtr[IaAddrIdx].Addr, DataPtr[TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_ADDR]);
        DynIaAddrPtr[IaAddrIdx].PreferredLifetime = TCPIP_GET_UINT32(DataPtr, TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_PREFLIFENBO);
        DynIaAddrPtr[IaAddrIdx].ValidLifetime     = TCPIP_GET_UINT32(DataPtr, TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_VALDLIFENBO);

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
        CANOE_WRITE_STRING3("Opt IA_NA, Addr: %s, PreferredLifetime: %d, ValidLifetime: %d",
          IpV6_VNetAddr2String(&DynIaAddrPtr[IaAddrIdx].Addr.addr), DynIaAddrPtr[IaAddrIdx].PreferredLifetime,
          DynIaAddrPtr[IaAddrIdx].ValidLifetime);
#endif

        IaAddrIdxValid = TRUE;
        break;
      }
    }

    if (FALSE == IaAddrIdxValid)
    {
      return E_NOT_OK;
    }
  }
#else

  IPV6_ADDR_COPY(IaAddrPtr->Addr, DataPtr[TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_ADDR]);
  IaAddrPtr->PreferredLifetime = TCPIP_GET_UINT32(DataPtr, TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_PREFLIFENBO);
  IaAddrPtr->ValidLifetime     = TCPIP_GET_UINT32(DataPtr, TCPIP_DHCPV6_IANA_ADDR_OPT_OFF_VALDLIFENBO);

  if (IaAddrPtr->PreferredLifetime <= IaAddrPtr->ValidLifetime)
  {
    IaAddrPtr->Valid = TRUE;
  }
  else
  {
    IaAddrPtr->Valid = FALSE;
  }
#endif

  IaAddrPtr->StatusCode.StatusCode = TCPIP_DHCPV6_STATUS_CODE_SUCCESS;
  IaAddrPtr->StatusCode.StatusTextLen = 0;

  while (TRUE == TcpIp_DhcpV6_VGetNextOption(DataPtr, DataLen, &OptLoc))
  {
    switch (OptLoc.OptCode)
    {
    case TCPIP_DHCPV6_OPT_STATUS_CODE:
      if (E_OK == TcpIp_DhcpV6_VDecodeOptStatusCode(&DataPtr[OptLoc.OptOfs], OptLoc.OptLen, &IaAddrPtr->StatusCode))
      {

      }
      break;

    default:
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
      CANOE_WRITE_STRING3("TcpIp_DhcpV6_VDecodeOptIaAddr() Skipping unknown option code %d, length %d at offset %d",
        OptLoc.OptCode, OptLoc.OptLen, OptLoc.OptOfs);
#endif
      break;
    }
  } /* option loop */

  if (TCPIP_DHCPV6_GET_OPT_OK != OptLoc.ErrCode)
  {
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
    CANOE_WRITE_STRING0("TcpIp_DhcpV6_VRxReply() Option parsing error!");
#endif
    return E_NOT_OK;
  }

  return E_OK;
  /* PRQA S 2006 1 */ /* MD_MSR_14.7 */
} /* End of TcpIp_DhcpV6_VDecodeOptIaAddr() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VDecodeOptIaNa()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VDecodeOptIaNa(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                 DataPtr,
  uint16                                                     DataLen,
  P2VAR(TcpIp_DhcpV6_OptIaNaType, AUTOMATIC, TCPIP_APPL_VAR) IaNaPtr)
{
  TcpIp_DhcpV6_OptLocationType optLoc;
  uint32 RecIaId;

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 3 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != DataPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(0 < DataLen, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_PARAM,   E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != IaNaPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* check minimum length of IA_NA option */
  if (TCPIP_DHCPV6_OPT_IA_NA_HDR_LEN > DataLen)
  {
    IaNaPtr->Valid = FALSE;
    return E_NOT_OK;
  }

  RecIaId = TCPIP_GET_UINT32(DataPtr, TCPIP_DHCPV6_IANA_OPT_OFF_IAIDNBO);

  /* Check if received Ia Id is same as the stored IA NA option */
  if (RecIaId != IaNaPtr->IaId)
  {
    IaNaPtr->Valid = FALSE;
    return E_NOT_OK;
  }

  IaNaPtr->T1 = TCPIP_GET_UINT32(DataPtr, TCPIP_DHCPV6_IANA_OPT_OFF_T1NBO);
  IaNaPtr->T2 = TCPIP_GET_UINT32(DataPtr, TCPIP_DHCPV6_IANA_OPT_OFF_T2NBO);

  if ((IaNaPtr->T2 > 0) && (IaNaPtr->T1 > IaNaPtr->T2))
  {
    /* Ignore option with invalid lifetimes */
    IaNaPtr->Valid = FALSE;
    return E_NOT_OK;
  }

  IaNaPtr->Valid = TRUE;

#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
  CANOE_WRITE_STRING3("Opt IA_NA, IAID: %08x, T1: %d, T2: %d", IaNaPtr->IaId, IaNaPtr->T1, IaNaPtr->T2);
#endif

  optLoc.OptOfs  = sizeof(TcpIp_DhcpV6_OptIaNaHdrRawType);
  optLoc.OptLen  = 0;
  optLoc.ErrCode = TCPIP_DHCPV6_GET_OPT_OK;

  IaNaPtr->StatusCode.StatusCode    = TCPIP_DHCPV6_STATUS_CODE_SUCCESS;
  IaNaPtr->StatusCode.StatusTextLen = 0;

#if (TCPIP_DHCPV6_ENABLE_DYNAMIC_IA_NA == STD_ON)
  for (IaAddrIdx = 0; IaAddrIdx < IaNaPtr->IaAddrCount; IaAddrIdx++)
  {
    IaNaPtr->IaAddrPtr[IaAddrIdx].Valid = FALSE;
  }
#endif

  /* Iterate over all options */
  while (TRUE == TcpIp_DhcpV6_VGetNextOption(DataPtr, DataLen, &optLoc))
  {
    switch (optLoc.OptCode)
    {
    case TCPIP_DHCPV6_OPT_IAADDR:
      (void)TcpIp_DhcpV6_VDecodeOptIaAddr(&DataPtr[optLoc.OptOfs],
        optLoc.OptLen, &IaNaPtr->IaAddr);
      break;

    case TCPIP_DHCPV6_OPT_STATUS_CODE:
      (void)TcpIp_DhcpV6_VDecodeOptStatusCode(&DataPtr[optLoc.OptOfs], optLoc.OptLen, &IaNaPtr->StatusCode);
      break;

    default:
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
      CANOE_WRITE_STRING3("TcpIp_DhcpV6_VDecodeOptIaNa() Skipping unknown option code %d, length %d at offset %d", optLoc.OptCode, optLoc.OptLen, optLoc.OptOfs);
#endif
      break;
    }
  } /* option loop */

  if (TCPIP_DHCPV6_GET_OPT_OK != optLoc.ErrCode)
  {
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
    CANOE_WRITE_STRING0("TcpIp_DhcpV6_VRxReply() Option parsing error!");
#endif
    IaNaPtr->Valid = FALSE;
    return E_NOT_OK;
  }

  return E_OK;
  /* PRQA S 2006 1 */ /* MD_MSR_14.7 */
} /* End of TcpIp_DhcpV6_VDecodeOptIaNa() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VDecodeOptStatusCode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VDecodeOptStatusCode(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                       DataPtr,
  uint16                                                           DataLen,
  P2VAR(TcpIp_DhcpV6_OptStatusCodeType, AUTOMATIC, TCPIP_APPL_VAR) StatusCodePtr)
{
  Std_ReturnType result = E_OK;

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 3 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != DataPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION,   TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(0 < DataLen, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION,   TCPIP_DHCPV6_E_INV_PARAM,   E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != StatusCodePtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* #10 Check minimum length of status code option */
  if (TCPIP_DHCPV6_OPT_STATUS_CODE_HDR_LEN > DataLen)
  {
    result = E_NOT_OK;
  }
  else
  {
    /* #20 Update status code options */
    StatusCodePtr->StatusCode = TCPIP_GET_UINT16(DataPtr, TCPIP_DHCPV6_STATUSCODE_OPT_OFF_STATUSCODENBO);
    StatusCodePtr->StatusTextPtr = &DataPtr[sizeof(TcpIp_DhcpV6_OptStatusCodeHdrRawType)];
    StatusCodePtr->StatusTextLen = (uint16)(DataLen - sizeof(TcpIp_DhcpV6_OptStatusCodeHdrRawType));
  }

  return result;
} /* End of TcpIp_DhcpV6_VDecodeOptStatusCode() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VDecodeOptPreference()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VDecodeOptPreference(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR)    PreferenceValuePtr)
{
  Std_ReturnType result = E_OK;
#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 3 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != DataPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(0 < DataLen, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_PARAM,   E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != PreferenceValuePtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* #10 Check minimum length of status code option */
  if (TCPIP_DHCPV6_OPT_PREFERENCE_LEN != DataLen)
  {
    result = E_NOT_OK;
  }
  else
  {
    /* #20 Update preference value */
    *PreferenceValuePtr = DataPtr[0];
  }

  return result;
} /* End of TcpIp_DhcpV6_VDecodeOptPreference() */


#if (TCPIP_SUPPORT_DNS == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VDecodeOptDnsServers()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VDecodeOptDnsServers(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                       DataPtr,
  uint16                                                           DataLen,
  P2VAR(TcpIp_DhcpV6_OptDnsServersType, AUTOMATIC, TCPIP_APPL_VAR) DnsServersOptPtr)
{
#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 3 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != DataPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(0 < DataLen, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_PARAM,   E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != DnsServersOptPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* check minimum length of dns servers option */
  if (0 != (DataLen & TCPIP_DHCPV6_MASK_MOD_16))
  {
    /* "Length of the list of DNS recursive name servers in octets;
     *  must be a multiple of 16"
     *  [RFC3646 3. DNS Recursive Name Server option]
     */

    DnsServersOptPtr->Valid = FALSE;
    return E_NOT_OK;
  }

  DnsServersOptPtr->Valid = TRUE;
  DnsServersOptPtr->Addrs = (TCPIP_P2C(IpBase_AddrIn6Type))DataPtr;  /* PRQA S 0310 */ /* MD_IpV6_0310_Uint8ToStruct */
  DnsServersOptPtr->AddrCount = (uint8)(DataLen >> TCPIP_DHCPV6_RSHIFT_DIV_16);

  return E_OK;
} /* End of TcpIp_DhcpV6_VDecodeOptDnsServers() */ /* PRQA S 2006 */ /* MD_MSR_14.7 */
#endif


#if (TCPIP_SUPPORT_DNS == STD_ON)
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VDecodeOptDomainList()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VDecodeOptDomainList(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                       DataPtr,
  uint16                                                           DataLen,
  P2VAR(TcpIp_DhcpV6_OptDomainListType, AUTOMATIC, TCPIP_APPL_VAR) DomainListOptPtr)
{
#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 3 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != DataPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(0 < DataLen, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_PARAM,   E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != DomainListOptPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  DomainListOptPtr->Valid = TRUE;
  DomainListOptPtr->List = DataPtr;
  DomainListOptPtr->ListLength = DataLen;

  return E_OK;
} /* End of TcpIp_DhcpV6_VDecodeOptDomainList() */
#endif

#if ((TCPIP_SUPPORT_DHCPV6_OPTIONS == STD_ON) && (TCPIP_DHCPV6_RX_OPTION_CNT > 0))
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VHandleUserOptions()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VHandleUserOptions(
  uint8                                      MsgType,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen)
{
  TcpIp_DhcpV6_OptLocationType OptLoc;

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 2 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != DataPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(0 < DataLen, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_PARAM,   E_NOT_OK);
#endif

  OptLoc.OptOfs = 0;
  OptLoc.OptLen = 0;
  OptLoc.ErrCode = TCPIP_DHCPV6_GET_OPT_OK;

  while (TRUE == TcpIp_DhcpV6_VGetNextOption(DataPtr, DataLen, &OptLoc))
  {
    TcpIp_RxDhcpV6OptFcts(0, OptLoc.OptCode, OptLoc.OptLen, &DataPtr[OptLoc.OptOfs], MsgType);
  }

  return E_OK;
} /* End of TcpIp_DhcpV6_VHandleUserOptions() */
#endif


/* MESSAGE RECEPTION */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VRxAdvertise()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VRxAdvertise(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen)
{
  Std_ReturnType Result;
  TcpIp_DhcpV6_OptLocationType OptLoc;
  boolean ClientDuidValid = FALSE;
  boolean ServerDuidValid = FALSE;
  uint16  ServerDuidOfs = 0;
  uint16  ServerDuidLen = 0;
  TcpIp_DhcpV6_OptStatusCodeType OptStCode;
  uint8 ServerPreference = 0;
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 2 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != DataPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(0 < DataLen, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  /* assume status success if no status code option present */
  OptStCode.StatusCode = TCPIP_DHCPV6_STATUS_CODE_SUCCESS;
  OptStCode.StatusTextLen = 0;

  TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpDataIdx)->Valid = FALSE;

  OptLoc.OptOfs = 0;
  OptLoc.OptLen = 0;
  OptLoc.ErrCode = TCPIP_DHCPV6_GET_OPT_OK;

  /* #10 Obtain and parse options inside advertise message */
  while (TRUE == TcpIp_DhcpV6_VGetNextOption(DataPtr, DataLen, &OptLoc))
  {
    switch (OptLoc.OptCode)
    {
    case TCPIP_DHCPV6_OPT_CLIENTID:
      {
        uint8 ClientDuidOfDhcpV6Data[sizeof(TcpIp_DhcpV6_DuIdType1)]; /* PRQA S 0781 */ /* MD_TCPIP_5.6_0781 */
      /* check client identifier */
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
        TcpIp_DhcpV6_VDbgPrintOptId(&DataPtr[OptLoc.OptOfs], OptLoc.OptLen);
#endif
        TCPIP_PUT_UINT16_RAW(ClientDuidOfDhcpV6Data, TCPIP_DHCPV6_DUID1_OPT_OFF_TYPENBO,   TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpDataIdx)->TypeNbo);
        TCPIP_PUT_UINT16_RAW(ClientDuidOfDhcpV6Data, TCPIP_DHCPV6_DUID1_OPT_OFF_HWTYPENBO, TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpDataIdx)->HwTypeNbo);
        TCPIP_PUT_UINT32_RAW(ClientDuidOfDhcpV6Data, TCPIP_DHCPV6_DUID1_OPT_OFF_TIMENBO,   TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpDataIdx)->TimeNbo);
        IPV6_LL_ADDR_COPY(&ClientDuidOfDhcpV6Data[TCPIP_DHCPV6_DUID1_OPT_OFF_PHYSADDR], &(TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpDataIdx)->PhysAddr[0]));

        if (TRUE == TcpIp_DhcpV6_VCompareBytes(&DataPtr[OptLoc.OptOfs], OptLoc.OptLen,
          ClientDuidOfDhcpV6Data, TCPIP_DHCPV6_CLIENT_DUID_LEN))
        {
          /* valid client identifier */
          ClientDuidValid = TRUE;
        }
        else
        {
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
          CANOE_WRITE_STRING0("TcpIp_DhcpV6_VRxAdvertise() invalid client identifier!");
#endif
        }
      }
      break;

    case TCPIP_DHCPV6_OPT_SERVERID:
      if ((0 < OptLoc.OptLen) && (TCPIP_DHCPV6_DUID_MAX_LEN >= OptLoc.OptLen))
      {
        ServerDuidValid = TRUE;
        ServerDuidOfs = OptLoc.OptOfs;
        ServerDuidLen = OptLoc.OptLen;
      }
      else
      {
        TcpIp_DhcpV6_DetReportError(TCPIP_DHCPV6_API_ID_RX_INDICATION,
          TCPIP_DHCPV6_E_SERVER_ID_OVFL);
      }
      break;

    case TCPIP_DHCPV6_OPT_STATUS_CODE:
      (void)TcpIp_DhcpV6_VDecodeOptStatusCode(&DataPtr[OptLoc.OptOfs],
        OptLoc.OptLen, &OptStCode);
      break;

    case TCPIP_DHCPV6_OPT_IA_NA:
      (void)TcpIp_DhcpV6_VDecodeOptIaNa(&DataPtr[OptLoc.OptOfs], OptLoc.OptLen,
        TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpDataIdx));

      break;

    case TCPIP_DHCPV6_OPT_PREFERENCE:
      (void)TcpIp_DhcpV6_VDecodeOptPreference(&DataPtr[OptLoc.OptOfs], OptLoc.OptLen, &ServerPreference);
      break;

    default:
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
      CANOE_WRITE_STRING3("TcpIp_DhcpV6_VRxAdvertise() Skipping unknown option code %d, length %d at offset %d",
        OptLoc.ErrCode, OptLoc.OptLen, OptLoc.OptOfs);
#endif
      break;
    }
  } /* option loop */

  if (TCPIP_DHCPV6_GET_OPT_OK != OptLoc.ErrCode)
  {
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
    CANOE_WRITE_STRING0("TcpIp_DhcpV6_VRxReply() Option parsing error!");
#endif
    Result = E_NOT_OK;
  }
  else
  {
    /* #20 Validate received advertisement */
    if (   ((TRUE == ClientDuidValid) && (TRUE == ServerDuidValid) &&(TCPIP_DHCPV6_STATUS_CODE_SUCCESS == OptStCode.StatusCode))
        && ((TRUE == TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpDataIdx)->Valid) && (TCPIP_DHCPV6_STATUS_CODE_SUCCESS == TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpDataIdx)->StatusCode.StatusCode))
        && ((TRUE == TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpDataIdx)->IaAddr.Valid) && (TCPIP_DHCPV6_STATUS_CODE_SUCCESS == TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpDataIdx)->IaAddr.StatusCode.StatusCode))
        && ((FALSE == TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpDataIdx)->Valid) || (TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpDataIdx)->Preference < ServerPreference)))
    {
        TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpDataIdx)->Valid = TRUE;
        TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpDataIdx)->Preference  = ServerPreference;
        TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpDataIdx)->ServerIdLen = (uint8)ServerDuidLen;
        VStdMemCpy(&TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpDataIdx)->ServerId[0], &DataPtr[ServerDuidOfs],
          TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpDataIdx)->ServerIdLen);
    }

    Result = (TRUE == TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpDataIdx)->Valid) ? E_OK : E_NOT_OK;
  }
  return Result;

} /* End of TcpIp_DhcpV6_VRxAdvertise() */ /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VProcessValidateRxReplyOptions()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VProcessValidateRxReplyOptions(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx,
  IPV6_P2V(TcpIp_DhcpV6_OptStatusCodeType)   OptStatusCodePtr,
#if (TCPIP_SUPPORT_DNS == STD_ON)
  IPV6_P2V(TcpIp_DhcpV6_OptDnsServersType)   OptDnsServersPtr,
  IPV6_P2V(TcpIp_DhcpV6_OptDomainListType)   OptDomainListPtr,
#endif
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen)
{
  Std_ReturnType Result = E_OK;
  TcpIp_DhcpV6_OptLocationType OptLoc;
  TcpIp_SizeOfDhcpV6DataType   dhcpDataIdx   = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);
#if (TCPIP_SUPPORT_DNS == STD_ON)
  TcpIp_SizeOfDhcpV6ConfigType dhcpConfigIdx = TcpIp_GetDhcpV6ConfigIdxOfIpV6Ctrl(IpCtrlIdx);
#endif
  boolean ValidClientId = FALSE;
  boolean ValidServerId = FALSE;

  TCPIP_ASSERT(dhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  OptLoc.OptOfs = 0;
  OptLoc.OptLen = 0;
  OptLoc.ErrCode = TCPIP_DHCPV6_GET_OPT_OK;

  /* #10 Obtain and parse options in reply message */
  while (TRUE == TcpIp_DhcpV6_VGetNextOption(DataPtr, DataLen, &OptLoc))
  {
    switch (OptLoc.OptCode)
    {
    case TCPIP_DHCPV6_OPT_CLIENTID:
      {
        uint8 ClientDuidOfDhcpV6Data[sizeof(TcpIp_DhcpV6_DuIdType1)]; /* PRQA S 0781 */ /* MD_TCPIP_5.6_0781 */
        TCPIP_PUT_UINT16_RAW(ClientDuidOfDhcpV6Data, TCPIP_DHCPV6_DUID1_OPT_OFF_TYPENBO,   TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpDataIdx)->TypeNbo);
        TCPIP_PUT_UINT16_RAW(ClientDuidOfDhcpV6Data, TCPIP_DHCPV6_DUID1_OPT_OFF_HWTYPENBO, TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpDataIdx)->HwTypeNbo);
        TCPIP_PUT_UINT32_RAW(ClientDuidOfDhcpV6Data, TCPIP_DHCPV6_DUID1_OPT_OFF_TIMENBO,   TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpDataIdx)->TimeNbo);

        IPV6_LL_ADDR_COPY(&ClientDuidOfDhcpV6Data[TCPIP_DHCPV6_DUID1_OPT_OFF_PHYSADDR], &(TcpIp_GetAddrClientDuidOfDhcpV6Data(dhcpDataIdx)->PhysAddr[0]));

        if (TRUE == TcpIp_DhcpV6_VCompareBytes(&DataPtr[OptLoc.OptOfs], OptLoc.OptLen, ClientDuidOfDhcpV6Data, TCPIP_DHCPV6_CLIENT_DUID_LEN))
        {
          ValidClientId = TRUE;
        }
      }
      break;

    case TCPIP_DHCPV6_OPT_SERVERID:
      if (TRUE == TcpIp_DhcpV6_VCompareBytes(&DataPtr[OptLoc.OptOfs], OptLoc.OptLen, &(TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpDataIdx)->ServerId[0]), TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpDataIdx)->ServerIdLen))
      {
        ValidServerId = TRUE;
      }
      break;

    case TCPIP_DHCPV6_OPT_STATUS_CODE:
      {
        (void)TcpIp_DhcpV6_VDecodeOptStatusCode(&DataPtr[OptLoc.OptOfs], OptLoc.OptLen, OptStatusCodePtr);
      }
      break;

    case TCPIP_DHCPV6_OPT_IA_NA:
      if (E_OK != TcpIp_DhcpV6_VDecodeOptIaNa(&DataPtr[OptLoc.OptOfs],
        OptLoc.OptLen, TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpDataIdx)))
      {
        /* invalid IA_NA option */
      }
      break;

#if (TCPIP_SUPPORT_DNS == STD_ON)
    case TCPIP_DHCPV6_OPT_DNS_SERVERS:
      if (TcpIp_IsEnableRdnssOptOfDhcpV6Config(dhcpConfigIdx) == TRUE)
      {
        if (E_OK != TcpIp_DhcpV6_VDecodeOptDnsServers(&DataPtr[OptLoc.OptOfs], OptLoc.OptLen, OptDnsServersPtr))
        {
          /* invalid DNS_SERVERS option */
        }
      }
      break;

    case TCPIP_DHCPV6_OPT_DOMAIN_LIST:
      if (TcpIp_IsEnableDnsslOptOfDhcpV6Config(dhcpConfigIdx) == TRUE)
      {
        if (E_OK != TcpIp_DhcpV6_VDecodeOptDomainList(&DataPtr[OptLoc.OptOfs], OptLoc.OptLen, OptDomainListPtr))
        {
          /* invalid DOMAIN_LIST option */
        }
      }
      break;
#endif


    default:
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
      CANOE_WRITE_STRING3("TcpIp_DhcpV6_VRxReply() Skipping unknown option code %d, length %d at offset %d",
        OptLoc.OptCode, OptLoc.OptLen, OptLoc.OptOfs);
#endif
      break;
    }
  }

  if (   (TCPIP_DHCPV6_GET_OPT_OK != OptLoc.ErrCode)/* Opt code procesing failed */
      || (FALSE == ValidClientId)
      || (FALSE == ValidServerId))
  {
    /* #20 Ignore reply messages with invalid client or server identifier or error status code */
    Result = E_NOT_OK;
  }

  return Result;
} /* TcpIp_DhcpV6_VProcessValidateRxReplyOptions() */ /* PRQA S 6030, 6050, 6060 */ /* MD_MSR_STCYC, MD_TcpIp_STCAL_CslAccess, MD_MSR_STPAR */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VProcessRxReplyIanaOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VProcessRxReplyIanaOption(
#if ((TCPIP_SUPPORT_DHCPV6_OPTIONS == STD_ON) && (TCPIP_DHCPV6_RX_OPTION_CNT > 0))
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr, 
  uint16                                     DataLen, 
#endif
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx)
{
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->Valid = TRUE;
  TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->T1Timeout =
    (TcpIp_DhcpV6_Time.S + TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpDataIdx)->T1);

  TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->T2Timeout =
    (TcpIp_DhcpV6_Time.S + TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpDataIdx)->T2);

  /* #10 Check if iana option contains valid address */
  if (   (TRUE == TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpDataIdx)->IaAddr.Valid)
      && (TCPIP_DHCPV6_STATUS_CODE_SUCCESS == TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpDataIdx)->IaAddr.StatusCode.StatusCode))
  {
    TcpIp_SizeOfLocalAddrV6Type localAddrIdx = 
      TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(TcpIp_GetIpV6SourceAddressDhcpIdxOfIpV6Ctrl(IpCtrlIdx));
    /* IA_NA option contains valid address */

#if ((TCPIP_SUPPORT_DHCPV6_OPTIONS == STD_ON) && (TCPIP_DHCPV6_RX_OPTION_CNT > 0))
    TcpIp_DhcpV6_VHandleUserOptions(TCPIP_DHCPV6_MSG_REP, DataPtr, DataLen);
#endif

    /* #20 update address lease information and add to source address table */

    IPV6_ADDR_COPY(TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->AddrLease.Addr, 
      TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpDataIdx)->IaAddr.Addr);

    TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->AddrLease.PreferredUntil =
      (TcpIp_DhcpV6_Time.S + TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpDataIdx)->IaAddr.PreferredLifetime);

    TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->AddrLease.ValidUntil     =
      (TcpIp_DhcpV6_Time.S + TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpDataIdx)->IaAddr.ValidLifetime);

    if (E_OK == IpV6_SetAddress(localAddrIdx, &(TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->AddrLease.Addr),
      TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpDataIdx)->IaAddr.PreferredLifetime,
      TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpDataIdx)->IaAddr.ValidLifetime, FALSE))
    {
      TCPIP_DHCPV6_CHANGE_STATE(dhcpDataIdx, BOUND);

      /* wait until T1 has been expired */
      TCPIP_DHCPV6_TIME_SET(*TcpIp_GetAddrIdleTimeOfDhcpV6Data(dhcpDataIdx),
        TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->T1Timeout, 0);
    }
    else
    {
      TCPIP_DHCPV6_CHANGE_STATE(dhcpDataIdx, FAIL);
    }
  }
} /* TcpIp_DhcpV6_VProcessRxReplyIanaOption() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VProcessRxReplyStatusCode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VProcessRxReplyStatusCode(
  TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  if (TCPIP_DHCPV6_STATUS_CODE_SUCCESS == TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpDataIdx)->StatusCode.StatusCode)
  {
    /* #10 Process iana option if it has positive status code */

    TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->Valid = TRUE;
    TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->T1Timeout =
      (TcpIp_DhcpV6_Time.S + TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpDataIdx)->T1);

    TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->T2Timeout = 
      (TcpIp_DhcpV6_Time.S + TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpDataIdx)->T2);

    TcpIp_DhcpV6_VProcessRxReplyIanaOption(IpCtrlIdx);
  }
  else if (TCPIP_DHCPV6_STATUS_CODE_NOT_ON_LINK == 
    TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpDataIdx)->StatusCode.StatusCode)
  {
    /* #20 If status code is Not on link, the requested address is not on-link and must not be used, 
     * restart address assignment
     */

    TcpIp_DhcpV6_VRestartAddressAssignment(IpCtrlIdx, 0);
  }
  else if (TCPIP_DHCPV6_STATUS_CODE_NO_BINDING == 
    TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpDataIdx)->StatusCode.StatusCode)
  {
    /* #30 If status code is No binding, dhcpv6 server has no valid binding. request new address */

    (void)TcpIp_DhcpV6_VBuildRequest(IpCtrlIdx, TcpIp_GetAddrMsgOfDhcpV6Data(dhcpDataIdx));
    TCPIP_DHCPV6_INIT_RETRANS_PARAMS(IpCtrlIdx, REQ);
    TCPIP_DHCPV6_CHANGE_STATE(dhcpDataIdx, TX_REQ);
    TCPIP_DHCPV6_SET_IDLE_TIME_S(dhcpDataIdx, 0);
  }
  else
  {
    /* Unknown status code in IA_NA option. Ignore the reply */
  }

} /* TcpIp_DhcpV6_VProcessRxReplyStatusCode() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VUpdateRxReplyDhcpState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VUpdateRxReplyDhcpState(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx,
#if (TCPIP_SUPPORT_DNS == STD_ON)
  IPV6_P2C(TcpIp_DhcpV6_OptDnsServersType)   OptDnsServersPtr,
  IPV6_P2C(TcpIp_DhcpV6_OptDomainListType)   OptDomainListPtr,
#endif
  IPV6_P2C(TcpIp_DhcpV6_OptStatusCodeType)   OptStatusCodePtr)
{
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx   = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);
#if (TCPIP_SUPPORT_DNS == STD_ON)
  TcpIp_SizeOfDhcpV6ConfigType dhcpConfigIdx = TcpIp_GetDhcpV6ConfigIdxOfIpV6Ctrl(IpCtrlIdx);
#endif

  TCPIP_ASSERT(dhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  switch (TcpIp_GetStateOfDhcpV6Data(dhcpDataIdx))
  {
  case TCPIP_DHCPV6_STATE_TX_REL: /* Release */
  case TCPIP_DHCPV6_STATE_TX_DEC: /* Decline */
    /* #10 Ignore reply received in response to release or decline message */
    TCPIP_DHCPV6_CHANGE_STATE(dhcpDataIdx, UNBOUND);
    break;

  case TCPIP_DHCPV6_STATE_TX_REQ: /* Request */
  case TCPIP_DHCPV6_STATE_TX_CNF: /* Confirm */
  case TCPIP_DHCPV6_STATE_TX_REB: /* Rebind */
  case TCPIP_DHCPV6_STATE_TX_REN: /* Renew */

    /* #20 Process reply received in response to request, confirm, rebind or renew message */

    if (TCPIP_DHCPV6_STATUS_CODE_SUCCESS == OptStatusCodePtr->StatusCode)
    {
#if (TCPIP_SUPPORT_DNS == STD_ON)
      if (TcpIp_IsEnableRdnssOptOfDhcpV6Config(dhcpConfigIdx) == TRUE)
      {
        if (TRUE == OptDnsServersPtr->Valid)
        {
          Dns_UpdateIpV6Servers(OptDnsServersPtr->Addrs, OptDnsServersPtr->AddrCount, TCPIP_DHCPV6_LIFETIME_UNLIMITED, 0);
        }
      }

      TCPIP_UNUSED_PARAMETER(OptDomainListPtr);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
#endif
      if (TRUE == TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx))->Valid)
      {
        /* #30 Process matching IA_NA option if status code is success */
        TcpIp_DhcpV6_VProcessRxReplyStatusCode(IpCtrlIdx);
      }
      else
      {
        /* reply message does not contain matching IA_NA option. Ignore reply. */
      }
    }
    else if (   (TCPIP_DHCPV6_STATUS_CODE_NO_BINDING == OptStatusCodePtr->StatusCode)
             || (TCPIP_DHCPV6_STATUS_CODE_NOT_ON_LINK == OptStatusCodePtr->StatusCode))
    {
      /* #40 If reply message contains negative status code NO_BINDING or NOT_ON_LINK, restart address assignment procedure */

      TcpIp_DhcpV6_VRestartAddressAssignment(IpCtrlIdx, 0);
    }
    else
    {
      /* reply message contains negative status code. Do not handle reply. */
    }

    break;


  default:
    /* ignore reply */
    break;
  }
}  /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VRxReply()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VRxReply(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen)
{
  TcpIp_DhcpV6_OptStatusCodeType OptStatusCode;
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

#if (TCPIP_SUPPORT_DNS == STD_ON)
  TcpIp_DhcpV6_OptDnsServersType OptDnsServers;
  TcpIp_DhcpV6_OptDomainListType OptDomainList;
#endif

  TCPIP_ASSERT(dhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

#if (TCPIP_DHCPV6_VENABLE_INTERNAL_DET_CHECKS == STD_ON)
  /* PRQA S 3109 2 */ /* MD_MSR_14.3 */
  TcpIp_DhcpV6_CheckDetErrorReturnValue(NULL_PTR != DataPtr, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
  TcpIp_DhcpV6_CheckDetErrorReturnValue(0 < DataLen, TCPIP_DHCPV6_API_ID_INTERNAL_FUNCTION, TCPIP_DHCPV6_E_INV_POINTER, E_NOT_OK);
#endif

  TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpDataIdx)->Valid = FALSE;
  OptStatusCode.StatusCode = TCPIP_DHCPV6_STATUS_CODE_SUCCESS;
  OptStatusCode.StatusTextLen = 0;

#if (TCPIP_SUPPORT_DNS == STD_ON)
  OptDnsServers.Valid = FALSE;
  OptDomainList.Valid = FALSE;
#endif

  if (E_OK == TcpIp_DhcpV6_VProcessValidateRxReplyOptions(IpCtrlIdx, &OptStatusCode,
#if (TCPIP_SUPPORT_DNS == STD_ON)
    &OptDnsServers, &OptDomainList,
#endif
    DataPtr, DataLen))
  {
    TcpIp_DhcpV6_VUpdateRxReplyDhcpState(IpCtrlIdx, 
#if (TCPIP_SUPPORT_DNS == STD_ON)
      &OptDnsServers, &OptDomainList,
#endif
    &OptStatusCode);
  }
  else
  {
    /* validation failed */
  }
} /* End of TcpIp_DhcpV6_VRxReply() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VRestartAddressAssignment()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VRestartAddressAssignment(TcpIp_IpV6CtrlIterType IpCtrlIdx, uint32 DelayMs)
{
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpDataIdx)->Valid = FALSE;
  TcpIp_GetAddrAdvInfoOfDhcpV6Data(dhcpDataIdx)->ServerIdLen = 0;

  if (TRUE == TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->Valid)
  {
    /* #10 remove dhcpv6 assigned address from source address table */
    TcpIp_IpV6SourceAddressIterType srcAddrIdx = TcpIp_GetIpV6SourceAddressDhcpIdxOfIpV6Ctrl(IpCtrlIdx);

    (void)IpV6_SetAddress(TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(srcAddrIdx),
      &(TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->AddrLease.Addr), 0, 0, FALSE);

    TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->Valid = FALSE;
  }

  TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->IaId = 0;

#if (TCPIP_DHCPV6_ENABLE_DYNAMIC_IA_NA == STD_ON)
  TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->AddrLeasePtr   = &TcpIp_DhcpV6_IaAddrLeases[0];
  TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->AddrLeaseCount = 1;

  TcpIp_DhcpV6_IaAddrLeases[0].ValidUntil = 0;
  TcpIp_DhcpV6_IaAddrLeases[0].PreferredUntil = 0;
#endif

  TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpDataIdx)->Valid = FALSE;
  TcpIp_GetAddrIaNaOptBufOfDhcpV6Data(dhcpDataIdx)->IaId = TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->IaId;

#if (TCPIP_DHCPV6_ENABLE_DYNAMIC_IA_NA == STD_ON)
  TcpIp_DhcpV6_IaNaBuf.IaAddrPtr = &TcpIp_DhcpV6_IaAddrBuf[0];
  TcpIp_DhcpV6_IaNaBuf.IaAddrCount = 1;
#endif

  /* #20 Send dhcpv6 solicit message for address assignment */
  (void)TcpIp_DhcpV6_VBuildSolicit(IpCtrlIdx, TcpIp_GetAddrMsgOfDhcpV6Data(dhcpDataIdx));
  TCPIP_DHCPV6_INIT_RETRANS_PARAMS(IpCtrlIdx, SOL);
  TCPIP_DHCPV6_CHANGE_STATE(dhcpDataIdx, TX_SOL);
  TCPIP_DHCPV6_SET_IDLE_TIME_MS(dhcpDataIdx, DelayMs);
} /* TcpIp_DhcpV6_VRestartAddressAssignment() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/* PUBLIC FUNCTIONS */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_IsActive()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, TCPIP_CODE) TcpIp_DhcpV6_IsActive(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  boolean result = TRUE;
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  /* PRQA S 3415 2 */ /* MD_TcpIp_12.4_CslReadOnly */
  if (   (TCPIP_DHCPV6_STATE_INIT == TcpIp_GetStateOfDhcpV6Data(dhcpDataIdx))
      || (TCPIP_DHCPV6_STATE_FAIL == TcpIp_GetStateOfDhcpV6Data(dhcpDataIdx)))
  {
    result = FALSE;
  }

  return result;
} /* End of TcpIp_DhcpV6_IsActive() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_StartAddressAssignment()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_StartAddressAssignment(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  TcpIp_SizeOfDhcpV6ConfigType dhcpConfigIdx = TcpIp_GetDhcpV6ConfigIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpConfigIdx < TcpIp_GetSizeOfDhcpV6Config()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */
  TCPIP_ASSERT(TCPIP_DHCPV6_IS_INITIALIZED(TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx)));

  TcpIp_DhcpV6_VInitClientId(IpCtrlIdx);

  /* delay sending of first solicit message */
  if (TcpIp_GetSolicitDelayMinOfDhcpV6Config(dhcpConfigIdx) == TcpIp_GetSolicitDelayMaxOfDhcpV6Config(dhcpConfigIdx))
  {
    TcpIp_DhcpV6_VRestartAddressAssignment(IpCtrlIdx, TcpIp_GetSolicitDelayMinOfDhcpV6Config(dhcpConfigIdx));
  }
  else
  {
    TcpIp_DhcpV6_VRestartAddressAssignment(IpCtrlIdx,
      (uint32)TcpIp_DhcpV6_VGetRandomValue((sint32)TcpIp_GetSolicitDelayMinOfDhcpV6Config(dhcpConfigIdx), (sint32)TcpIp_GetSolicitDelayMaxOfDhcpV6Config(dhcpConfigIdx)));
  }

  return E_OK;
} /* End of TcpIp_DhcpV6_StartAddressAssignment() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_StartAddressAssignmentForAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_StartAddressAssignmentForAddr(TcpIp_SizeOfLocalAddrV6Type IpAddrIdx)
{
  Std_ReturnType result = E_NOT_OK;
  TcpIp_IpV6CtrlIterType ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(IpAddrIdx); /* PRQA S 0781 */ /* MD_TCPIP_5.6_0781 */

  if (TcpIp_IsIpV6SourceAddressUsedOfLocalAddrV6(IpAddrIdx) == TRUE)
  {
    TcpIp_IpV6SourceAddressIterType srcAddrIdx = TcpIp_GetIpV6SourceAddressIdxOfLocalAddrV6(IpAddrIdx);
    /* Trigger address assignment only if the Ip address index is Dhcp configurable */
    if (TcpIp_GetAddressAssignVariantOfIpV6SourceAddress(srcAddrIdx) == TCPIP_IPADDR_ASSIGNMENT_DHCP)
    {
      TCPIP_ASSERT(TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(ipCtrlIdx) == TRUE); /* Assert that DhcpV6 is configured for the IpCtrlIdx */
      result = TcpIp_DhcpV6_StartAddressAssignment(ipCtrlIdx);
    }
  }

  return result;
}


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_RequestInformation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_RequestInformation(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  Std_ReturnType Result;
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);
  TcpIp_SizeOfDhcpV6ConfigType dhcpConfigIdx = TcpIp_GetDhcpV6ConfigIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */
  TCPIP_ASSERT(TCPIP_DHCPV6_IS_INITIALIZED(dhcpDataIdx));
  TcpIp_DhcpV6_VInitClientId(IpCtrlIdx);

  Result = TcpIp_DhcpV6_VBuildInfoRequest(IpCtrlIdx, TcpIp_GetAddrMsgOfDhcpV6Data(dhcpDataIdx));

  if (E_OK == Result)
  {
    TCPIP_DHCPV6_INIT_RETRANS_PARAMS(IpCtrlIdx, INF);
    TCPIP_DHCPV6_CHANGE_STATE(dhcpDataIdx, TX_INF);
    TcpIp_DhcpV6_VTriggerTx(TcpIp_GetAddrMsgOfDhcpV6Data(dhcpDataIdx));

    /* delay sending of first confirm message */
    if (TcpIp_GetInfoRequestDelayMinOfDhcpV6Config(dhcpConfigIdx) == TcpIp_GetInfoRequestDelayMaxOfDhcpV6Config(dhcpConfigIdx))
    {
      TCPIP_DHCPV6_SET_IDLE_TIME_MS(dhcpDataIdx, TcpIp_GetInfoRequestDelayMinOfDhcpV6Config(dhcpConfigIdx));
    }
    else
    {
      TCPIP_DHCPV6_SET_IDLE_TIME_MS(dhcpDataIdx, 
        (uint32)TcpIp_DhcpV6_VGetRandomValue((sint32)TcpIp_GetInfoRequestDelayMinOfDhcpV6Config(dhcpConfigIdx), 
        (sint32)TcpIp_GetInfoRequestDelayMaxOfDhcpV6Config(dhcpConfigIdx)));
    }
  }

  return Result;
} /* End of TcpIp_DhcpV6_RequestInformation() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_Decline()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_Decline(
  TcpIp_IpV6CtrlIterType                                 IpCtrlIdx,
  P2CONST(IpBase_AddrIn6Type, AUTOMATIC, IPV6_APPL_DATA) AddrPtr)
{
  Std_ReturnType Result;
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */
  TCPIP_ASSERT(TCPIP_DHCPV6_IS_INITIALIZED(dhcpDataIdx));
  TCPIP_ASSERT(NULL_PTR != AddrPtr);

  /* PRQA S 3415 2 */ /* MD_TcpIp_12.4_CslReadOnly */
  if (   (TRUE == TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->Valid)
      && (TRUE == IpV6_CmpNetAddr(AddrPtr, &(TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->AddrLease.Addr))))
  {
    /* #10 Invoke routine to build a dhcpv6 decline message for the given Ip address */
    Result = TcpIp_DhcpV6_VBuildDecline(IpCtrlIdx, TcpIp_GetAddrMsgOfDhcpV6Data(dhcpDataIdx));

    if (E_OK == Result)
    {
      /* #20 Update retransmission params and state for decline messages */
      TCPIP_DHCPV6_INIT_RETRANS_PARAMS(IpCtrlIdx, DEC);
      TCPIP_DHCPV6_CHANGE_STATE(dhcpDataIdx, TX_DEC);
      TCPIP_DHCPV6_SET_IDLE_TIME_S(dhcpDataIdx, 0);
    }
  }
  else
  {
    Result = E_NOT_OK;
  }

  return Result;
} /* End of TcpIp_DhcpV6_Decline() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_Confirm()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_Confirm(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  Std_ReturnType Result;
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);
  TcpIp_SizeOfDhcpV6ConfigType dhcpConfigIdx = TcpIp_GetDhcpV6ConfigIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data());  /* Assert that DhcpV6 is configured for the IpCtrlIdx */
  TCPIP_ASSERT(TCPIP_DHCPV6_IS_INITIALIZED(dhcpDataIdx));

  if (TRUE == TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->Valid)
  {
    /* #10 Build dhcpv6 confirm message for te assigned address */
    Result = TcpIp_DhcpV6_VBuildConfirm(IpCtrlIdx, TcpIp_GetAddrMsgOfDhcpV6Data(dhcpDataIdx));

    if (E_OK == Result)
    {
      TCPIP_DHCPV6_INIT_RETRANS_PARAMS(IpCtrlIdx, CNF);
      TCPIP_DHCPV6_CHANGE_STATE(dhcpDataIdx, TX_CNF);

      /* #20 Generate random delay for resending confirm message */
      if (TcpIp_GetConfirmDelayMinOfDhcpV6Config(dhcpConfigIdx) == TcpIp_GetConfirmDelayMaxOfDhcpV6Config(dhcpConfigIdx))
      {
        /* delay sending of first confirm message */
        TCPIP_DHCPV6_SET_IDLE_TIME_MS(dhcpDataIdx, TcpIp_GetConfirmDelayMinOfDhcpV6Config(dhcpConfigIdx));
      }
      else
      {
        TCPIP_DHCPV6_SET_IDLE_TIME_MS(dhcpDataIdx, 
          (uint32)TcpIp_DhcpV6_VGetRandomValue((sint32)TcpIp_GetConfirmDelayMinOfDhcpV6Config(dhcpConfigIdx), 
          (sint32)TcpIp_GetConfirmDelayMaxOfDhcpV6Config(dhcpConfigIdx)));
      }
    }
  }
  else
  {
    Result = E_NOT_OK;
  }

  return Result;
} /* End of TcpIp_DhcpV6_Confirm() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_ReleaseAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_ReleaseAddress(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  Std_ReturnType Result;
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */
  TCPIP_ASSERT(TCPIP_DHCPV6_IS_INITIALIZED(dhcpDataIdx));

  if (TRUE == TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->Valid)
  {
    /* #10 Build dhcpv6 release message for assigned address */
    Result = TcpIp_DhcpV6_VBuildRelease(IpCtrlIdx, TcpIp_GetAddrMsgOfDhcpV6Data(dhcpDataIdx));

    if (E_OK == Result)
    {
      /* #20 Remove the released dhcpv6 address from source address table */
      TcpIp_IpV6SourceAddressIterType srcAddrIdx = TcpIp_GetIpV6SourceAddressDhcpIdxOfIpV6Ctrl(IpCtrlIdx);

      (void)IpV6_SetAddress(TcpIp_GetLocalAddrV6IdxOfIpV6SourceAddress(srcAddrIdx), 
        &(TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->AddrLease.Addr), 0, 0, FALSE);
      /* #30 Update retransmission params and state for release message */
      TCPIP_DHCPV6_INIT_RETRANS_PARAMS(IpCtrlIdx, REL);
      TCPIP_DHCPV6_CHANGE_STATE(dhcpDataIdx, TX_REL);
      TCPIP_DHCPV6_SET_IDLE_TIME_S(dhcpDataIdx, 0);
    }
  }
  else
  {
    Result = E_NOT_OK;
  }

  return Result;
} /* End of TcpIp_DhcpV6_ReleaseAddress() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_Reset()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_Reset(TcpIp_IpV6CtrlIterType IpCtrlIdx)
{
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);
  TcpIp_SizeOfDhcpV6MsgTxBufferType dhcpTxBufIdx = TcpIp_GetDhcpV6MsgTxBufferStartIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  /* #10 Reset all dhcpv6 configuration parameters */
  TcpIp_SetCurrentTransIdOfDhcpV6Data(dhcpDataIdx, TCPIP_DHCPV6_INV_TRANS_ID);
  TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->Valid = FALSE;
  TCPIP_DHCPV6_SET_IDLE_TIME_MS(dhcpDataIdx, 1000);
  TCPIP_DHCPV6_CHANGE_STATE(dhcpDataIdx, INIT);

  TcpIp_GetAddrMsgOfDhcpV6Data(dhcpDataIdx)->TxPending = FALSE;
  TcpIp_GetAddrMsgOfDhcpV6Data(dhcpDataIdx)->MsgBufPtr = TcpIp_GetAddrDhcpV6MsgTxBuffer(dhcpTxBufIdx);
  TcpIp_GetAddrMsgOfDhcpV6Data(dhcpDataIdx)->MsgBufLen = TcpIp_GetSizeOfDhcpV6MsgTxBuffer();

  /* #20 Clear all tx options */
#if ((TCPIP_SUPPORT_DHCPV6_OPTIONS == STD_ON)  && (TCPIP_DHCPV6_TX_OPTION_CNT > 0))
  {
    TcpIp_SizeOfDhcpV6TxOption39InfoType txOptInfoIdx = TcpIp_GetDhcpV6TxOption39InfoIdxOfIpV6Ctrl(IpCtrlIdx);
    TcpIp_SetOptLenOfDhcpV6TxOption39Info(txOptInfoIdx, 0);
  }
#endif
} /* End of TcpIp_DhcpV6_Reset() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */


#if (TCPIP_SUPPORT_DHCPV6_OPTIONS == STD_ON)
# if (TCPIP_DHCPV6_TX_OPTION_CNT > 0)
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VGetTxOption
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VGetTxOption(
    TcpIp_SizeOfLocalAddrV6Type               IpAddrIdx,
    uint16                                    OptId,
    P2VAR(uint16, AUTOMATIC, TCPIP_APPL_DATA) OptLenPtr,
    P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)  OptPtr)
{
  Std_ReturnType            RetValue = E_NOT_OK;
  TcpIp_IpV6CtrlIterType    ipCtrlIdx;/* PRQA S 0781 */ /* MD_TCPIP_5.6_0781 */
  TcpIp_IpV6SourceAddressIterType srcAddrIdx;

  srcAddrIdx = TcpIp_GetIpV6SourceAddressIdxOfLocalAddrV6(IpAddrIdx);
  ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(IpAddrIdx);
  if (TcpIp_GetIpV6SourceAddressDhcpIdxOfIpV6Ctrl(ipCtrlIdx) == srcAddrIdx)
  {
    /* #10 Obtain supported tx option (FQDN-Option) */
    if ((OptId == TCPIP_DHCPV6_OPT_ID_CLIENT_FQDN) && (TcpIp_IsDhcpV6TxOption39InfoUsedOfIpV6Ctrl(ipCtrlIdx) == TRUE))  /* PRQA S 3415 */ /* MD_TcpIp_12.4_CslReadOnly */
    {
      TcpIp_SizeOfDhcpV6TxOption39InfoType txOptInfoIdx = TcpIp_GetDhcpV6TxOption39InfoIdxOfIpV6Ctrl(ipCtrlIdx);

      if (*OptLenPtr >= TcpIp_GetOptLenOfDhcpV6TxOption39Info(txOptInfoIdx))
      {
        /* copy length and host name */
        *OptLenPtr = TcpIp_GetOptLenOfDhcpV6TxOption39Info(txOptInfoIdx);
        if (*OptLenPtr > 0)
        {
          TcpIp_SizeOfDhcpV6TxOption39Type txOpt39Idx = TcpIp_GetDhcpV6TxOption39StartIdxOfIpV6Ctrl(ipCtrlIdx);
          IpBase_Copy(OptPtr, TcpIp_GetAddrDhcpV6TxOption39(txOpt39Idx), *OptLenPtr);
        }
        RetValue = E_OK;
      }
    }
  }

  return RetValue;
} /* End of TcpIp_DhcpV6_VGetTxOption() */  /* PRQA S 2006, 6050 */ /* MD_MSR_14.7, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VSetTxOption
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV6_VSetTxOption(
    TcpIp_SizeOfLocalAddrV6Type                IpAddrIdx,
    uint16                                     OptId,
    uint16                                     OptLen,
    P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) OptPtr,
    uint16                                     MsgTypes)
{

  TcpIp_IpV6CtrlIterType     ipCtrlIdx;  /* PRQA S 0781 */ /* MD_TCPIP_5.6_0781 */
  Std_ReturnType             retValue = E_NOT_OK;
  TcpIp_SizeOfDhcpV6TxOption39InfoType txOptInfoIdx;
  TcpIp_IpV6SourceAddressIterType srcAddrIdx;

  srcAddrIdx = TcpIp_GetIpV6SourceAddressIdxOfLocalAddrV6(IpAddrIdx);
  ipCtrlIdx = TcpIp_GetIpV6CtrlIdxOfLocalAddrV6(IpAddrIdx);
  txOptInfoIdx = TcpIp_GetDhcpV6TxOption39InfoIdxOfIpV6Ctrl(ipCtrlIdx);

  /* #10 Check if valid Address Index has been passed */
  if (TcpIp_GetIpV6SourceAddressDhcpIdxOfIpV6Ctrl(ipCtrlIdx) == srcAddrIdx)
  {
    /* Process request only if the address index is DHCPv6 configurable */
    if ((OptId == TCPIP_DHCPV6_OPT_ID_CLIENT_FQDN) && (TcpIp_IsDhcpV6TxOption39InfoUsedOfIpV6Ctrl(ipCtrlIdx) == TRUE))  /* PRQA S 3415 */ /* MD_TcpIp_12.4_CslReadOnly */
    {
      /* Process request only if Tx Option 39 Info is valid for the Controller index */
      TcpIp_SizeOfDhcpV6TxOption39Type txOption39_OptLen = 
        TcpIp_GetDhcpV6TxOption39EndIdxOfIpV6Ctrl(ipCtrlIdx) - TcpIp_GetDhcpV6TxOption39StartIdxOfIpV6Ctrl(ipCtrlIdx);
      /* An old API for setting a host name was TcpIp_DhcpV6_SetHostName(). */
      if (OptLen <= txOption39_OptLen)
      {
        /* #20 Set tx option parameters */
        TcpIp_SizeOfDhcpV6TxOption39Type txOpt39Idx = TcpIp_GetDhcpV6TxOption39StartIdxOfIpV6Ctrl(ipCtrlIdx);
        /* copy length, flags and host name */
        TcpIp_SetOptLenOfDhcpV6TxOption39Info(txOptInfoIdx, OptLen);
        TcpIp_SetMsgFlagsOfDhcpV6TxOption39Info(txOptInfoIdx, MsgTypes);
        IpBase_Copy(TcpIp_GetAddrDhcpV6TxOption39(txOpt39Idx), OptPtr, OptLen);
        retValue = E_OK;
      }
    }
  }

  return retValue;
} /* End of TcpIp_DhcpV6_VSetTxOption() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */
# endif
#endif


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_InitMemory()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_InitMemory(void)
{
  TcpIp_IpV6CtrlIterType ipCtrlIdx; /* PRQA S 0781 */ /* MD_TCPIP_5.6_0781 */
  

  for (ipCtrlIdx = 0; ipCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl(); ipCtrlIdx++)
  {
    if (TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(ipCtrlIdx) == TRUE)
    {
      TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(ipCtrlIdx);

      TcpIp_SetStateOfDhcpV6Data(dhcpDataIdx, TCPIP_DHCPV6_STATE_UNINIT);
      TcpIp_SetLastStateOfDhcpV6Data(dhcpDataIdx, TCPIP_DHCPV6_STATE_UNINIT);
    }
  }
} /* End of TcpIp_DhcpV6_InitMemory() */


/**********************************************************************************************************************
 *  TcpIp_DhcpV6_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_Init(
    P2CONST(TcpIp_DhcpV6_ConfigType, TCPIP_PBCFG, TCPIP_CONST) CfgPtr)
{
  TcpIp_IpV6CtrlIterType ipCtrlIdx; /* PRQA S 0781 */ /* MD_TCPIP_5.6_0781 */

  IPV6_UNUSED_PARAMETER(CfgPtr);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */

  TCPIP_DHCPV6_TIME_SET(TcpIp_DhcpV6_Time, 0, 0);

  for (ipCtrlIdx = 0; ipCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl(); ipCtrlIdx++)
  {
    if (TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(ipCtrlIdx) == TRUE)
    {
      TcpIp_DhcpV6_Reset(ipCtrlIdx);
    }
  }

} /* End of TcpIp_DhcpV6_Init() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VCalcElapsedTime()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VCalcElapsedTime(
    TcpIp_SizeOfDhcpV6DataType DhcpDataIdx)
{
  TcpIp_ElapsedTimeMsOfDhcpV6DataType dhcpElapsedTimeMs = TcpIp_GetElapsedTimeMsOfDhcpV6Data(DhcpDataIdx);
  
  if (0xFFFFFFFFU > dhcpElapsedTimeMs)
  {
    if ((0xFFFFFFFFU - dhcpElapsedTimeMs) > TCPIP_MAIN_FCT_PERIOD_MSEC)
    {
      TcpIp_SetElapsedTimeMsOfDhcpV6Data(DhcpDataIdx, dhcpElapsedTimeMs + TCPIP_MAIN_FCT_PERIOD_MSEC);
    }
    else
    {
      TcpIp_SetElapsedTimeMsOfDhcpV6Data(DhcpDataIdx, 0xFFFFFFFFU);
    }
  }
  else
  {
    /* do nothing */
  }
}

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VTxPendingMessages()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VTxPendingMessages(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  TcpIp_SizeOfDhcpV6DataType DhcpDataIdx)
{
  TCPIP_ASSERT(DhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  /* #10 Check for dhcpv6 messages pending transmission */
  if (TRUE == TcpIp_GetMsgOfDhcpV6Data(DhcpDataIdx).TxPending)
  {
    if (1 == TcpIp_GetAddrRetransParamsOfDhcpV6Data(DhcpDataIdx)->TxCount)
    {
      TcpIp_SetElapsedTimeMsOfDhcpV6Data(DhcpDataIdx, 0);
    }

    /* #20 Invoke transmit api to transmit pending message */
    if (E_OK == TcpIp_DhcpV6_VTxMessage(IpCtrlIdx, TcpIp_GetAddrMsgOfDhcpV6Data(DhcpDataIdx)))
    {
      /* #30 set pending flag to false if transmit successful */
      TcpIp_GetAddrMsgOfDhcpV6Data(DhcpDataIdx)->TxPending = FALSE;
    }
  }
  else
  {
    /* Do nothing */
  }
}

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VHandleStateRenewMessage()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VHandleStateRenewMessage(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  TcpIp_SizeOfDhcpV6DataType DhcpDataIdx)
{
  TCPIP_ASSERT(DhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  /* #10 Check if timeout for maximum retransmission has been reached */
  if (E_OK == TcpIp_DhcpV6_VCalcTimeout(IpCtrlIdx, TcpIp_GetAddrIdleTimeOfDhcpV6Data(DhcpDataIdx), FALSE))
  {
    /* #20 transmit/retransmit renew message if timeout not reached */
    TcpIp_DhcpV6_VTriggerTx(TcpIp_GetAddrMsgOfDhcpV6Data(DhcpDataIdx));
  }
  else
  {
    /* #30 If timeout expired and reply has been received to renew message, 
     * switch to sending rebind messages 
     */
    if (E_OK == TcpIp_DhcpV6_VBuildRebind(IpCtrlIdx, TcpIp_GetAddrMsgOfDhcpV6Data(DhcpDataIdx)))
    {
      TCPIP_DHCPV6_INIT_RETRANS_PARAMS(IpCtrlIdx, REB);

      /* #40 Send rebind messages until valid lifetime expires */
      TCPIP_DHCPV6_TIME_SET(TcpIp_GetAddrRetransParamsOfDhcpV6Data(DhcpDataIdx)->AbsRetransTimeout,
        TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(DhcpDataIdx)->AddrLease.ValidUntil, 0);

      TCPIP_DHCPV6_CHANGE_STATE(DhcpDataIdx, TX_REB);
    }
    else
    {
      TCPIP_DHCPV6_CHANGE_STATE(DhcpDataIdx, FAIL);
    }
  }
} /* TcpIp_DhcpV6_VHandleStateRenewMessage() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VHandleStateSolicitMessage()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VHandleStateSolicitMessage(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  TcpIp_SizeOfDhcpV6DataType DhcpDataIdx)
{
  TCPIP_ASSERT(DhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  if (TRUE == TcpIp_GetAddrAdvInfoOfDhcpV6Data(DhcpDataIdx)->Valid)
  {
    /* #10 If valid advertisement received, build and send dhcpv6 request */
    (void)TcpIp_DhcpV6_VBuildRequest(IpCtrlIdx, TcpIp_GetAddrMsgOfDhcpV6Data(DhcpDataIdx));
    TCPIP_DHCPV6_INIT_RETRANS_PARAMS(IpCtrlIdx, REQ);
    TCPIP_DHCPV6_CHANGE_STATE(DhcpDataIdx, TX_REQ);
  }
  /* #20 Retransmit SOLICIT message if number of retransmits has not been reached yet */
  else if (E_OK == TcpIp_DhcpV6_VCalcTimeout(IpCtrlIdx, TcpIp_GetAddrIdleTimeOfDhcpV6Data(DhcpDataIdx), TRUE))
  {
    /* (re)transmit solicit message */
    TcpIp_DhcpV6_VTriggerTx(TcpIp_GetAddrMsgOfDhcpV6Data(DhcpDataIdx));
  }
  else
  {
    TCPIP_DHCPV6_CHANGE_STATE(DhcpDataIdx, FAIL);
  }
} /* TcpIp_DhcpV6_VHandleStateSolicitMessage() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VHandleStateReqDecRebMessage()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VHandleStateReqDecRebMessage(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  TcpIp_SizeOfDhcpV6DataType DhcpDataIdx)
{
  TCPIP_ASSERT(DhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  if (E_OK == TcpIp_DhcpV6_VCalcTimeout(IpCtrlIdx, TcpIp_GetAddrIdleTimeOfDhcpV6Data(DhcpDataIdx), FALSE))
  {
    /* #10 Retransmit rebind message if maximum retransmissions not done */
    TcpIp_DhcpV6_VTriggerTx(TcpIp_GetAddrMsgOfDhcpV6Data(DhcpDataIdx));
  }
  else
  {
    /* #20 Restart dhcpv6 address assignment if maximum retries reached */
    if (E_OK == TcpIp_DhcpV6_StartAddressAssignment(IpCtrlIdx))
    {
      TCPIP_DHCPV6_CHANGE_STATE(DhcpDataIdx, FAIL);
    }
  }
} /* TcpIp_DhcpV6_VHandleStateReqDecRebMessage() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VHandleStateReleaseMessage()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VHandleStateReleaseMessage(
  TcpIp_IpV6CtrlIterType     IpCtrlIdx,
  TcpIp_SizeOfDhcpV6DataType DhcpDataIdx)
{
  TCPIP_ASSERT(DhcpDataIdx < TcpIp_GetSizeOfDhcpV6Data()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  if (E_OK == TcpIp_DhcpV6_VCalcTimeout(IpCtrlIdx, TcpIp_GetAddrIdleTimeOfDhcpV6Data(DhcpDataIdx), FALSE))
  {
    /* #10 Retransmit release message if maximum retransmissions not done */
    TcpIp_DhcpV6_VTriggerTx(TcpIp_GetAddrMsgOfDhcpV6Data(DhcpDataIdx));
  }
  else
  {
    /* #20 Change dhcpv6 state to fail if maximum retransmissions reached */
    TCPIP_DHCPV6_CHANGE_STATE(DhcpDataIdx, FAIL);
  }
}
/**********************************************************************************************************************
 *  TcpIp_DhcpV6_MainFunction
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_MainFunction(void)
{
  /* #10 Iterate over all IPv6 controllers that have a local address with DHCPv6 address assignment method */
  TcpIp_IpV6CtrlIterType ipCtrlIdx; /* PRQA S 0781 */ /* MD_TCPIP_5.6_0781 */

  for (ipCtrlIdx = 0; ipCtrlIdx < TcpIp_GetSizeOfIpV6Ctrl(); ipCtrlIdx++)
  {
    TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(ipCtrlIdx);

    /* PRQA S 3415 2 */ /* MD_TcpIp_12.4_CslReadOnly */
    if ((TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(ipCtrlIdx)) && TCPIP_DHCPV6_IS_INITIALIZED(dhcpDataIdx)) 
    {
      TCPIP_DHCPV6_TIME_ADD_MS(TcpIp_DhcpV6_Time, TCPIP_MAIN_FCT_PERIOD_MSEC);

      /* #20 Calculate elapsed time since start of DHCPv6 address assignment */
      TcpIp_DhcpV6_VCalcElapsedTime(dhcpDataIdx);

      /* #30 Transmit pending DHCPv6 message */
      TcpIp_DhcpV6_VTxPendingMessages(ipCtrlIdx, dhcpDataIdx);

      /* #40 Check if action is required for the DCHPv6 instance depending on current state: */ 
      if (TCPIP_DHCPV6_TIME_EXPIRED(TcpIp_GetIdleTimeOfDhcpV6Data(dhcpDataIdx)) == TRUE)
      {
        switch (TcpIp_GetStateOfDhcpV6Data(dhcpDataIdx))
        {
        case TCPIP_DHCPV6_STATE_TX_REN: /* Renew */
          /* #50 [RENEW] Send RENEW message or switch to REBIND if number of retransmissions has been reached */
          TcpIp_DhcpV6_VHandleStateRenewMessage(ipCtrlIdx, dhcpDataIdx);
          break;

        case TCPIP_DHCPV6_STATE_TX_SOL: /* Solicit */
          /* #60 [SOLICIT] Move to state REQUEST if valid ADVERTISE message has been received from DHCPv6 server
           *     else retransmit SOLICIT message if number of retransmits has not been reached yet 
           */
          TcpIp_DhcpV6_VHandleStateSolicitMessage(ipCtrlIdx, dhcpDataIdx);
          break;

        case TCPIP_DHCPV6_STATE_TX_CNF: /* Confirm */
          /* #70 [CONFIRM] (Re-)Transmit CONFIRM message */
          if (E_OK == TcpIp_DhcpV6_VCalcTimeout(ipCtrlIdx, TcpIp_GetAddrIdleTimeOfDhcpV6Data(dhcpDataIdx), FALSE))
          {
            /* (re)transmit message */
            TcpIp_DhcpV6_VTriggerTx(TcpIp_GetAddrMsgOfDhcpV6Data(dhcpDataIdx));
          }
          else
          {
            TCPIP_DHCPV6_CHANGE_STATE(dhcpDataIdx, FAIL);
          }
          break;

        case TCPIP_DHCPV6_STATE_TX_REQ: /* Request */
        case TCPIP_DHCPV6_STATE_TX_DEC: /* Decline */
        case TCPIP_DHCPV6_STATE_TX_REB: /* Rebind */
          /* #80 [REQUEST,DECLINE,REBIND] (Re-)Transmit message or restart DHCPv6 address assignment if 
           * number of retransmissions has been reached 
           */
          TcpIp_DhcpV6_VHandleStateReqDecRebMessage(ipCtrlIdx, dhcpDataIdx);
          break;

        case TCPIP_DHCPV6_STATE_TX_REL: /* Release */
          /* #90 [RELEASE] (Re-)Transmit Release message */
          TcpIp_DhcpV6_VHandleStateReleaseMessage(ipCtrlIdx, dhcpDataIdx);

          break;

        case TCPIP_DHCPV6_STATE_BOUND: /* Bound */
          /* #100 [BOUND] Schedule idle time until first Renew message must be sent and switch to state RENEW */
          (void)TcpIp_DhcpV6_VBuildRenew(ipCtrlIdx, TcpIp_GetAddrMsgOfDhcpV6Data(dhcpDataIdx));
          TCPIP_DHCPV6_INIT_RETRANS_PARAMS(ipCtrlIdx, REN);

          /* send renew messages until T2 is reached */
          TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->AbsRetransTimeout.S =
            TcpIp_GetAddrIaNaLeaseOfDhcpV6Data(dhcpDataIdx)->T2Timeout;
          TcpIp_GetAddrRetransParamsOfDhcpV6Data(dhcpDataIdx)->AbsRetransTimeout.Ms = 0;

          TCPIP_DHCPV6_CHANGE_STATE(dhcpDataIdx, TX_REN);
          break;

        default:
             /**/
          break;
        }
      }
      else
      {
        /* do nothing else until idle time has expired. e.g. message rx timeout has expired. */
      }
    }
  }
} /* End of TcpIp_DhcpV6_MainFunction() */ /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VRxHandleStateMsgAdv()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VRxHandleStateMsgAdv(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx, 
  TcpIp_SizeOfDhcpV6DataType                 DhcpDataIdx, 
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr, 
  uint16                                     DataLen)
{
  uint16 PayloadPos = TCPIP_DHCPV6_MSG_HDR_LEN;
  TcpIp_SizeOfDhcpV6ConfigType dhcpConfigIdx = TcpIp_GetDhcpV6ConfigIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(dhcpConfigIdx < TcpIp_GetSizeOfDhcpV6Config()); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  /* #10 If dhcpv6 is in solicit state, process packet and update state */
  if (   (TCPIP_DHCPV6_STATE_TX_SOL == TcpIp_GetStateOfDhcpV6Data(DhcpDataIdx))  /* PRQA S 3415 2 */ /* MD_TcpIp_12.4_ReadOnly */
      && (E_OK == TcpIp_DhcpV6_VRxAdvertise(IpCtrlIdx, &DataPtr[PayloadPos], (DataLen - PayloadPos))))
  {
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
    CANOE_WRITE_STRING0("TcpIp_DhcpV6_RxIndication() RxAdvertise");
#endif

    if (TcpIp_IsUseFirstValidAdvOfDhcpV6Config(dhcpConfigIdx) == TRUE)
    {
      TCPIP_DHCPV6_SET_IDLE_TIME_S(DhcpDataIdx, 0);
    }
    else if (   (TCPIP_DHCPV6_MAX_PREFERENCE == TcpIp_GetAddrAdvInfoOfDhcpV6Data(DhcpDataIdx)->Preference)
             || (1 < TcpIp_GetAddrRetransParamsOfDhcpV6Data(DhcpDataIdx)->TxCount))
    {
      /* #20 If valid advertisement with maximum preference received, move dhcpv6 state to request */
      TCPIP_DHCPV6_SET_IDLE_TIME_S(DhcpDataIdx, 0);
    }
    else
    {
      /* #30 If not advertisement with maximum preference, wait for more advertisements */
    }
  }
  else
  {
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
    CANOE_WRITE_STRING0("TcpIp_DhcpV6_RxIndication() RxAdvertise in WRONG STATE");
#endif
  }
} /* TcpIp_DhcpV6_VRxHandleStateMsgAdv() */ /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_VRxProcessMessage()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_VRxProcessMessage(
  TcpIp_IpV6CtrlIterType                     IpCtrlIdx,
  uint8                                      MsgType,
  TcpIp_SizeOfDhcpV6DataType                 DhcpDataIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
  uint16                                     DataLen)
{
  uint16 PayloadPos = TCPIP_DHCPV6_MSG_HDR_LEN;
  
  TCPIP_ASSERT(TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(IpCtrlIdx) == TRUE); /* Assert that DhcpV6 is configured for the IpCtrlIdx */

  /* #10 Process the received dhcpv6 message based on the type */
  switch (MsgType)
  {
  case TCPIP_DHCPV6_MSG_ADV:
    /* #20 Process dhcpv6 advertisements if dhcpv6 is in solicit state */
    TcpIp_DhcpV6_VRxHandleStateMsgAdv(IpCtrlIdx, DhcpDataIdx, DataPtr, DataLen);
    break;

  case TCPIP_DHCPV6_MSG_REP:
    /* #30 Process dhcpv6 replies only if dhcpv6 is valid */
    if (   (TCPIP_DHCPV6_STATE_TX_SOL <= TcpIp_GetStateOfDhcpV6Data(DhcpDataIdx)) /* PRQA S 3415 2 */ /* MD_TcpIp_12.4_CslReadOnly */
        && (TCPIP_DHCPV6_STATE_TX_REL >= TcpIp_GetStateOfDhcpV6Data(DhcpDataIdx)))
    {
      TcpIp_DhcpV6_VRxReply(IpCtrlIdx, &DataPtr[PayloadPos], (DataLen - PayloadPos));
    }
    break;

  case TCPIP_DHCPV6_MSG_REC:
    /* #40 Process dhcpv6 reconfiguration requests - not implemented yet */
    break;

    default:
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
      CANOE_WRITE_STRING1("Unkown Message Type: %d", MsgType);
#endif
      break;
  }
}

/**********************************************************************************************************************
 *  TcpIp_DhcpV6_RxIndication
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV6_RxIndication(
  TcpIp_IpV6CtrlIterType        IpCtrlIdx,
  TCPIP_P2V(uint8)              DataPtr,
  uint16                        DataLen,
  boolean                       ChecksumCalculated, 
  TCPIP_P2C(IpBase_AddrIn6Type) SourcePtr,
  TCPIP_P2C(IpBase_AddrIn6Type) DestinationPtr)
{
  Std_ReturnType result = E_OK;
  uint32 TransId, dhcpV6CurrTransId;
  uint8 MsgType;
  TcpIp_SizeOfDhcpV6DataType dhcpDataIdx = TcpIp_GetDhcpV6DataIdxOfIpV6Ctrl(IpCtrlIdx);

  TCPIP_ASSERT(DataPtr   != NULL_PTR);
  TCPIP_ASSERT(SourcePtr != NULL_PTR);

  /* #10 Check if dhcp is enabled for the controller */
  if (   (!TcpIp_IsDhcpV6ConfigUsedOfIpV6Ctrl(IpCtrlIdx)) /* PRQA S 3415 */ /* MD_TcpIp_12.4_CslReadOnly */
      || (!TCPIP_DHCPV6_IS_INITIALIZED(dhcpDataIdx)))
  {
    result = E_NOT_OK;
  }
  /* #20 Check if packet has minimum required length. */
  else if (DataLen < sizeof(TcpIp_Udp_HdrType))
  {
    result = E_NOT_OK;
  }
  else if (TCPIP_GET_UINT16(DataPtr, UDP_HDR_OFF_LENBYTE) > DataLen)
  {
    result = E_NOT_OK;
  }
  /* #30 Check if the source and destination ports in the udp header is valid */
  else if (   (TCPIP_GET_UINT16(DataPtr, UDP_HDR_OFF_SRCPORT) != TCPIP_DHCPV6_SERVER_PORT)
           || (TCPIP_GET_UINT16(DataPtr, UDP_HDR_OFF_TGTPORT) != TCPIP_DHCPV6_CLIENT_PORT))
  {
    result = E_NOT_OK;
  }
  /* #40 Validate the checksum of the received packet */
  else if (ChecksumCalculated == FALSE)
  {
    uint32 checksumTmp = TcpIp_VCalcIpV6PseudoHdrChecksum(SourcePtr, DestinationPtr, TCPIP_SOCK_PROT_UDP, DataLen);

    checksumTmp = IpBase_TcpIpChecksumAdd(DataPtr, DataLen, checksumTmp, TRUE);

    if (checksumTmp != 0)
    {
      result = E_NOT_OK;
    }
  }
  else
  {
    /* no error */
  }

  if (result == E_OK)
  {
    /* skip UDP header */
    DataLen = TCPIP_GET_UINT16(DataPtr, UDP_HDR_OFF_LENBYTE) - sizeof(TcpIp_Udp_HdrType);
    DataPtr = &DataPtr[sizeof(TcpIp_Udp_HdrType)];

    MsgType = DataPtr[0];
    TransId = ((uint32)DataPtr[1] << 16) | ((uint32)DataPtr[2] << 8) | ((uint32)DataPtr[3]);

    dhcpV6CurrTransId = TcpIp_GetCurrentTransIdOfDhcpV6Data(dhcpDataIdx);
    /* #50 Check if dhcpv6 message received with valid transaction Id */
    if (TransId != dhcpV6CurrTransId)
    {
      /* drop message with unexpected transaction id */
#if defined(TCPIP_DHCPV6_V_CANOE_DEBUG)
      CANOE_WRITE_STRING2("TcpIp_DhcpV6_RxIndication() discarding message. Expected transaction id %d but received %d.",
        TcpIp_DhcpV6_CurrentTransId, TransId);
#endif
    }
    else
    {
      /* #60 Invoke function to process the validated dhcpv6 message */
      TcpIp_DhcpV6_VRxProcessMessage(IpCtrlIdx, MsgType, dhcpDataIdx, DataPtr, DataLen);
    }
  }

} /* End of TcpIp_DhcpV6_RxIndication() */ /* PRQA S 6060, 6080 */ /* MD_MSR_STPAR, MD_MSR_STMIF */


#define TCPIP_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# endif /* (TCPIP_SUPPORT_DHCPV6 == STD_ON) */
#endif  /* (TCPIP_SUPPORT_IPV6 == STD_ON) */


/*
   MICROSAR global MISRA deviations:
   - see file 'WI_MISRA_Compliance_MSR.pdf'

   module specific MISRA deviations:

   MD_DhcpV6_19.12_0881: There shall be at most one occurrence of the # or ## preprocessor operators in a single macro definition. 
     Reason:     Multiple ## prepocessor operator is used to For efficient code.
     Risk:       Order of evaluation of the operator may be incorrect
     Prevention: Review of code wherever multiple glue operators are used

*/


/**********************************************************************************************************************
 *  END OF FILE: TcpIp_DhcpV6.c
 *********************************************************************************************************************/
