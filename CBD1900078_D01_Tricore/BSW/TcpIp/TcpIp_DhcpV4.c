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
 *         \file  TcpIp_DhcpV4.c
 *        \brief  Implementation of Dynamic Host Configuration Protocol for IPv4 - Client (DHCPv4 Client)
 *
 *      \details  This file is part of the TcpIp IPv4 submodule.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file of the TcpIp IPv4 submodule. >> TcpIp_IpV4.h / TcpIp.h (Version 8.xx.xx and higher)
 *********************************************************************************************************************/

/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */
/* PRQA S 0828 EOF */ /* MD_MSR_1.1_828 */

#define TCPIP_DHCPV4_SOURCE
#include "TcpIp_Cfg.h"



#if (TCPIP_SUPPORT_DHCPV4 == STD_ON)
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "TcpIp_Lcfg.h"
#include "TcpIp_DhcpV4.h"
#include "TcpIp_DhcpV4_Cbk.h"
#include "TcpIp_Priv.h"
#include "TcpIp_Udp.h"

#include "TcpIp_IpV4.h"
#include "IpBase.h"
#include "IpBase_Types.h"
#include "IpBase_Copy.h"
#include "EthIf.h"

#if (TCPIP_SUPPORT_DNS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
# include "Dns.h"
#endif


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#if !defined (STATIC)                                                                                                   /* COV_TCPIP_COMPATIBILITY */
# define STATIC static
#endif

#define TCPIP_DHCPV4_TX_BUFFER_MIN_SIZE_BYTE  260  /* size without "DHCP host name" */

#define TCPIP_DHCPV4_HW_TYPE_ETH            1
#define TCPIP_DHCPV4_HW_LEN_ETH             6

#define TCPIP_DHCPV4_OP_BOOTREQUEST         1
#define TCPIP_DHCPV4_OP_BOOTREPLY           2
#define TCPIP_DHCPV4_SERVER_PORT           0x0043U /* Decimal = 67 */
#define TCPIP_DHCPV4_CLIENT_PORT           68


/* DHCP OPTIONS */
#define TCPIP_DHCPV4_OPTION_HDR_BYTE                    2
#define TCPIP_DHCPV4_OPT_PAD_TYPE                       0
#define TCPIP_DHCPV4_OPT_END_TYPE                     255
#define TCPIP_DHCPV4_PARAM_SUBNET_ROUTER_DOMAIN_BYTE    3

#define TCPIP_DHCPV4_OPT_SUBNET_MASK_TYPE               1  /* client subnet mask */
#define TCPIP_DHCPV4_OPT_ROUTER_TYPE                    3  /* Router = Default Gateway */
#define TCPIP_DHCPV4_OPT_DOMAIN_NAME_SERVER_TYPE        6
#define TCPIP_DHCPV4_OPT_HOST_NAME_TYPE                12
#define TCPIP_DHCPV4_OPT_REQ_IP_ADDR_TYPE              50
#define TCPIP_DHCPV4_OPT_IP_ADDR_LEASE_TIME_TYPE       51
#define TCPIP_DHCPV4_OPT_OVERLOAD_TYPE                 52
#define TCPIP_DHCPV4_OPT_DHCPV4_MSG_TYPE               53
#define TCPIP_DHCPV4_OPT_SERVER_ID_TYPE                54  /* IP address of DHCP server */
#define TCPIP_DHCPV4_OPT_PARAM_REQ_LIST_TYPE           55  /* requested DHCP options */
#define TCPIP_DHCPV4_OPT_MSG_TYPE                      56  /* text (e.g. error) message */
#define TCPIP_DHCPV4_OPT_MAX_DHCPV4_MSG_SIZE_TYPE      57
#define TCPIP_DHCPV4_OPT_RENEWAL_TIME_T1_VAL_TYPE      58
#define TCPIP_DHCPV4_OPT_REBINDING_TIME_T2_VAL_TYPE    59

#define TCPIP_DHCPV4_OPT_SUBNET_MASK_LEN                4U
#define TCPIP_DHCPV4_OPT_ROUTER_LEN                     4U /* n times */
#define TCPIP_DHCPV4_OPT_DOMAIN_NAME_SERVER_LEN         4U  /* n times */
#define TCPIP_DHCPV4_OPT_REQ_IP_ADDR_LEN                4U
#define TCPIP_DHCPV4_OPT_IP_ADDR_LEASE_TIME_LEN         4U
#define TCPIP_DHCPV4_OPT_OVERLOAD_LEN                   1U
#define TCPIP_DHCPV4_OPT_DHCPV4_MSG_LEN                 1U
#define TCPIP_DHCPV4_OPT_SERVER_ID_LEN                  4U
#define TCPIP_DHCPV4_OPT_PARAM_REQ_LIST_ID_LEN          1U  /* min size */
#define TCPIP_DHCPV4_OPT_MSG_LEN                        1U  /* min size */
#define TCPIP_DHCPV4_OPT_MAX_DHCPV4_MSG_SIZE_LEN        2U
#define TCPIP_DHCPV4_OPT_RENEWAL_TIME_T1_VAL_LEN        4U
#define TCPIP_DHCPV4_OPT_REBINDING_TIME_T2_VAL_LEN      4U

/* FQDN Option field offset */
#define TCPIP_DHCPV4_OPT_FQDN_CODE                      0U
#define TCPIP_DHCPV4_OPT_FQDN_LEN                       1U
#define TCPIP_DHCPV4_OPT_FQDN_FLAGS                     2U
#define TCPIP_DHCPV4_OPT_FQDN_RCODE1                    3U
#define TCPIP_DHCPV4_OPT_FQDN_RCODE2                    4U
#define TCPIP_DHCPV4_OPT_FQDN_DOMAIN_NAME               5U

/* Dhcp Option Format */
#define TCPIP_DHCPV4_OPTION_FIELD_OFS_CODE              0U
#define TCPIP_DHCPV4_OPTION_FIELD_OFS_LEN               1U
#define TCPIP_DHCPV4_OPTION_FIELD_OFS_TYPE              2U

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define TCPIP_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define TCPIP_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define TCPIP_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define TCPIP_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_GetDhcpMsgLength
 *********************************************************************************************************************/
/*! \brief            Update Dhcp Message Length.
 *  \details          -
 *  \param[in]        MsgType                Indicates which type of message contains received frame 
 *  \param[in,out]    DhcpMsgLenPtr          Pointer to Message length.
 *  \param[in]        DhcpStatusIdx          Indicates Status index for a given Ip controller.
 *  \pre              -
 *  \context          TASK|ISR2
 *  \reentrant        FALSE
 *  \synchronous      TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_GetDhcpMsgLength(
  uint8                                             MsgType,
  P2VAR(uint16, AUTOMATIC, TCPIP_APPL_DATA)         DhcpMsgLenPtr,
  TcpIp_SizeOfDhcpStatusType                        DhcpStatusIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VSetMsgFlags
 *********************************************************************************************************************/
/*! \brief            Update Message Flag.
 *  \details          -
 *  \param[in]        MsgType                Indicates which type of message contains received frame 
 *  \param[in,out]    FlagPtr                Pointer to set the message specific flag.
 *  \param[in]        DhcpStatusIdx          Indicates Status index for a given Ip controller.
  * \param[in,out]    OptOfsPtr              Pointer to Option offset.
 *  \param[in]        OptPtr                 Pointer to the message options.
 *  \pre              -
 *  \context          TASK|ISR2
 *  \reentrant        FALSE
 *  \synchronous      TRUE
 *********************************************************************************************************************/
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VSetMsgFlags(
  uint8                                     MsgType,
  P2VAR(uint16, AUTOMATIC, TCPIP_APPL_DATA) FlagPtr,
  TcpIp_SizeOfDhcpStatusType                DhcpStatusIdx,
  P2VAR(uint16, AUTOMATIC, TCPIP_APPL_DATA) OptOfsPtr,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)  OptPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VUpdateStatus
 *********************************************************************************************************************/
/*! \brief            Update DhcpState pointer.
 *  \details          Returns the current DCHP state of a given IP address that is configured for DHCP address assignment
 *  \param[in]        LocalAddrIdx          Local Ip Address Index.
 *  \param[in,out]    ErrorIdPtr            Pointer to the error Id.
 *  \param[out]       DhcpStatePtr          Pointer to Dhcp States.
 *  \return           E_OK                  DhcpState  pointer is updated successfully.
 *  \return           E_NOT_OK              Ip instance is not active
 *  \pre              -
 *  \context          TASK|ISR2
 *  \reentrant        FALSE
 *  \synchronous      TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_VUpdateStatus(
  TcpIp_SizeOfLocalAddrType                     LocalAddrIdx,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)      ErrorIdPtr,
  CONSTP2VAR(uint8, AUTOMATIC, IPV4_APPL_DATA)  DhcpStatePtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VProcessCtrlState
 *********************************************************************************************************************/
/*! \brief        Starts DhcpV4 state transition process 
 *  \details      -
 *  \param[in]    IpV4CtrlIdx       Index of the IP controller/instance.
 *                                  CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *                                  CONSTRAINT: [One of the following checks must exist as both DhcpStatus and DhcpConfig are identical:
 *                                                  1.(TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
 *                                                  2.(TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE))]
 *  \pre          - 
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VProcessCtrlState(TcpIp_SizeOfIpV4CtrlDynType IpV4CtrlIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VSelectingState
 *********************************************************************************************************************/
/*! \brief        Retransmit DHCPDISCOVER message.
 *  \details      This function transmists discover messages until timout has ocuured.
 *  \param[in]    IpV4CtrlIdx         Index of the IP controller/instance.
 *                                    CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *                                    CONSTRAINT: [One of the following checks must exist as both DhcpStatus and DhcpConfig are identical:
 *                                                   1.(TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
 *                                                   2.(TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE))]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VSelectingState(TcpIp_SizeOfIpV4CtrlDynType IpV4CtrlIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_RenewingState
 *********************************************************************************************************************/
/*! \brief        Transmit DHCPREQUEST (unicast).
 *  \details      This schedules the next transmission after first DHCPRequest has been sent.
 *                After that it changes to rebinding state for the further processing.
 *  \param[in]    IpV4CtrlIdx           Index of the IP controller/instance.
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *                                      CONSTRAINT: [One of the following checks must exist as both DhcpStatus and DhcpConfig are identical:
 *                                                   1.(TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
 *                                                   2.(TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE))]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_RenewingState(TcpIp_SizeOfIpV4CtrlDynType IpV4CtrlIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_RebindingState
 *********************************************************************************************************************/
/*! \brief        Transmit DHCPREQUEST (broadcast).
 *  \details      This function transmits DHCPREQUEST (broadcast) and schedule next retransmission or
 *                cancel DHCP assignment if number of retransmission has been reached.
 *  \param[in]    IpV4CtrlIdx           Index of the IP controller/instance.
 *                                      CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *                                      CONSTRAINT: [One of the following checks must exist as both DhcpStatus and DhcpConfig are identical:
 *                                                    1.(TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
 *                                                    2.(TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE))]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_RebindingState(TcpIp_SizeOfIpV4CtrlDynType IpV4CtrlIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_ProcessAckOrNak
 *********************************************************************************************************************/
/*! \brief            Process incoming acknowledge or refuse server messages.
 *  \details          Process Acks and Nacks messages received from server. 
 *  \param[in]        IpV4CtrlIdx      Index of the IP controller/instance.
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *                                     CONSTRAINT: [One of the following checks must exist as both DhcpStatus and DhcpConfig are identical:
 *                                                    1.(TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
 *                                                    2.(TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE))]
 *  \param[in]        Yiaddr            Client's Ip Address.
 *  \param[in]        MsgType           Indicates which type of message contains received frame 
 *  \param[in]        LocConfigData     Pointer to the local configuration data.
 *  \param[in]        DnsServerOptPtr   DNS server information contained in received message.
 *  \pre              -
 *  \context          TASK|ISR2
 *  \reentrant        FALSE
 *  \synchronous      TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_ProcessAckOrNak(
  TcpIp_IpV4CtrlIterType                                           IpV4CtrlIdx,
  TcpIp_NetAddrType                                                Yiaddr,
  uint8                                                            MsgType,
  P2CONST(TcpIp_DhcpV4_DataStructType, AUTOMATIC, TCPIP_APPL_DATA) LocConfigData,
  P2CONST(TcpIp_DhcpV4_DnsOptInfoType, AUTOMATIC, TCPIP_APPL_DATA) DnsServerOptPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_ProcessOptions
 *********************************************************************************************************************/
/*! \brief            Navigate to the right option and update the relevant information.
 *  \details          -
 *  \param[in]        OptPtr                Pointer to the option field of received message.
 *  \param[out]       MsgTypePtr            Indicates which type of message contains received frame.
 *  \param[in]        LocConfigData         Pointer to the local configuration data.
 *  \param[out]       DnsServerOptPtr       Position of the DNS server information in received message.
 *                                          If no valid DNS server option was found the member 'AddrCount' is set to 0.
 *  \return           E_OK                  If Option length is correct.
 *  \return           E_NOT_OK              If option length is not valid
 *  \pre              -
 *  \context          TASK|ISR2
 *  \reentrant        FALSE
 *  \synchronous      TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_ProcessOptions(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                     OptPtr,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)                       MsgTypePtr,
  P2VAR(TcpIp_DhcpV4_DataStructType, AUTOMATIC, TCPIP_APPL_DATA) LocConfigData,
  P2VAR(TcpIp_DhcpV4_DnsOptInfoType, AUTOMATIC, TCPIP_APPL_DATA) DnsServerOptPtr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VVerifyClientAddr
 *********************************************************************************************************************/
/*! \brief            Verify client Ip address and netmask.
 *  \details          This function checks whether a client ip address and netmask is correct and
 *                    accordingly updates MsgIsValid variable. 
 *  \param[in]        LocConfigData          Pointer to the local configuration data.
 *  \param[out]       MsgIsValidPtr          Pointer to indicate whether the received message is valid or invalid.
 *  \param[in]        MsgType                Indicates which type of message contains received frame.
 *  \pre              -
 *  \context          TASK|ISR2
 *  \reentrant        FALSE
 *  \synchronous      TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VVerifyClientAddr(
  P2CONST(TcpIp_DhcpV4_DataStructType, AUTOMATIC, TCPIP_APPL_DATA) LocConfigData,
  P2VAR(boolean, AUTOMATIC, TCPIP_APPL_DATA)                       MsgIsValidPtr,
  uint8                                                            MsgType);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VDataLengthAndPortCheck
 *********************************************************************************************************************/
/*! \brief            Verify received message data length and Port.
 *  \details          -
 *  \param[in]        DataLen               Contains data length of a received message in bytes.
 *  \param[in]        SrcPort               DhcpV4 Source port.
 *  \param[in]        TgtPort               DhcpV4 Target(Destination) port.
 *  \param[in]        LenByte               Length of the Udp Packet.
 *  \return           E_OK                  Message data length is valid.
 *  \return           E_NOT_OK              Message data length is not valid.
 *  \pre              -
 *  \context          TASK|ISR2
 *  \reentrant        FALSE
 *  \synchronous      TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_VDataLengthAndPortCheck(
  uint16                                    DataLen,
  IpBase_PortType                           SrcPort,
  IpBase_PortType                           TgtPort,
  uint16                                    LenByte);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VProcessDhcpMsg
 *********************************************************************************************************************/
/*! \brief        Store Ip address and other required information provided by DHCPOFFER message. 
 *  \details      It changes state to the DHCPREQUEST for further processing.
 *                It also processes incoming ACKs and NAKs received from server.
 *  \param[in]    IpV4CtrlIdx          Index of the IP controller/instance.
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *                                     CONSTRAINT: [One of the following checks must exist as both DhcpStatus and DhcpConfig are identical:
 *                                                    1.(TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
 *                                                     2.(TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE))]
 *  \param[in]    MsgType              Indicates which type of message contains received frame.
 *  \param[in]    LocConfigData        Pointer to the local configuration data.
 *  \param[in]    DnsServerOptPtr      DNS server information contained in received message.
 *  \param[in]    Yiaddr               Client Ip Address.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VProcessDhcpMsg(
  TcpIp_IpV4CtrlIterType                                           IpV4CtrlIdx,
  uint8                                                            MsgType, 
  P2CONST(TcpIp_DhcpV4_DataStructType, AUTOMATIC, TCPIP_APPL_DATA) LocConfigData,
  P2CONST(TcpIp_DhcpV4_DnsOptInfoType, AUTOMATIC, TCPIP_APPL_DATA) DnsServerOptPtr,
  TcpIp_NetAddrType                                                Yiaddr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VVerifyMsgType
 *********************************************************************************************************************/
/*! \brief        Verifys if message not corrupted.
 *  \details      This function invalidates the message if it is a corrupted packet.
 *                It updates MsgIsValidPtr parameter in order to discard the corrupted message or process further the valid message.
 *  \param[in]    MsgType                         Indicates which type of message contains received frame.
 *  \param[out]   MsgIsValidPtr                   Indicates whether the received message is valid or invalid.
 *  \param[in]    EndOptFound                     End option of a message.
 *  \param[in]    LocConfigData                   Pointer to the local configuration data.
 *  \param[in]    DhcpStatusIdx                   Contains Dhcp status index for a given Ip controller.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VVerifyMsgType( 
  uint8                                                            MsgType,
  P2VAR(boolean, AUTOMATIC, TCPIP_APPL_DATA)                       MsgIsValidPtr,
  boolean                                                          EndOptFound,
  P2CONST(TcpIp_DhcpV4_DataStructType, AUTOMATIC, TCPIP_APPL_DATA) LocConfigData,
  TcpIp_SizeOfDhcpStatusType                                       DhcpStatusIdx);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VEvaluateOptions
 *********************************************************************************************************************/
/*! \brief        Evaluate all supported options.
 *  \details      -
 *  \param[in]    IpV4CtrlIdx          Index of the IP controller/instance.
 *                                     CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *                                     CONSTRAINT: [One of the following checks must exist as both DhcpStatus and DhcpConfig are identical:
 *                                                    1.(TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
 *                                                    2.(TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE))]
 *  \param[in]    DataPtr              Pointer to the data of a  received Dhcp frame.
 *  \param[in]    DataLen              Contains data length of a received message.
 *  \param[in]    PhysAddr             Physical address(Pointer to the destination MAC address).
                                       CONSTRAINT : [Must contains 6 bytes of memory]
 *  \pre          - 
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VEvaluateOptions(
  TcpIp_IpV4CtrlIterType                      IpV4CtrlIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)  DataPtr,
  uint16                                      DataLen,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)    PhysAddr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VSendDhcpMsg
 *********************************************************************************************************************/
/*! \brief        Sends an Dhcp message.
 *  \details      -
 *  \param[in]    IpV4CtrlIdx              Index of the IP controller/instance.
 *                                         CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]    MsgType                  Indicates which type of message contains received frame.
 *  \param[in]    DestAddr                 Destination Ip address. 
 *  \return       E_OK                     Message is sent successfully..
 *  \return       E_NOT_OK                 Message is not sent successfully.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_VSendDhcpMsg(
  TcpIp_SizeOfIpV4CtrlType IpV4CtrlIdx,
  uint8                    MsgType,
  TcpIp_NetAddrType        DestAddr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VAddReqIpAddrOption
 *********************************************************************************************************************/
/*! \brief        Get length of a requested Ip address option and also updates the message option buffer.
 *  \details      -
 *  \param[out]   OptPtr                Pointer to the message options
 *                                      [Pointer can be NULL_PTR.
 *                                       - NULL_PTR:- Update the total length of the Requested Ip address option.
 *                                       - Non NULL_PTR:- Copy Requested Ip address option to the buffer.]
 *                                      CONSTRAINT: CM_TCPIP_DHCPV4_OPT_BUF_VALID_ACCESS
 *  \param[in]    Yiaddr                Your (Client's)Ip address.
 *  \return                             Message length.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(uint8, TCPIP_CODE) TcpIp_DhcpV4_VAddReqIpAddrOption(
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) OptPtr,
  IpBase_AddrInType                       Yiaddr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VAddServerIdOption
 *********************************************************************************************************************/
/*! \brief        Get length of server identifier option also updates the message option buffer.
 *  \details      -
 *  \param[out]   OptPtr            Pointer to the message options
 *                                  [Pointer can be NULL_PTR.
 *                                     - NULL_PTR:- Update the total length of the Server Id option.
 *                                     - Non NULL_PTR:- Copy Server Id Option to the buffer.]
 *                                  CONSTRAINT: CM_TCPIP_DHCPV4_OPT_BUF_VALID_ACCESS
 *  \param[in]    Siaddr            IP address of next server to use in bootstrap, returned in DHCPOFFER, DHCPACK by server.
 *  \return                         Message length.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(uint8, TCPIP_CODE) TcpIp_DhcpV4_VAddServerIdOption(
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) OptPtr,
  IpBase_AddrInType                       Siaddr);

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VAddUserOptions
 *********************************************************************************************************************/
/*! \brief        Get length of all user options and also updates the message option buffer.
 *  \details      -
 *  \param[in]    IpV4CtrlIdx            Index of the IP controller/instance.
 *                                       CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[in]    MsgType                Indicates which type of message contains received frame.
 *  \param[in]    MsgDataPtr             Pointer to the message data.
 *                                       [Pointer can be NULL_PTR.
 *                                        - NULL_PTR:- Update the total length of the User options.
 *                                        - Non NULL_PTR:- Copy user options to the buffer.]
 *                                       CONSTRAINT: CM_TCPIP_DHCPV4_OPT_BUF_VALID_ACCESS
 *  \return                              Message length of all options.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(uint16, TCPIP_CODE) TcpIp_DhcpV4_VAddUserOptions(
    TcpIp_SizeOfIpV4CtrlType                 IpV4CtrlIdx,
    uint8                                    MsgType,
    P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) MsgDataPtr );

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VAddParamReqListOpt
 *********************************************************************************************************************/
/*! \brief        Get length of parameter request option and also updates the message option buffer.
 *  \details      -
 *  \param[in]    IpV4CtrlIdx Index of the IP controller/instance.
 *                            CONSTRAINT: [0...TcpIp_GetSizeOfIpV4Ctrl()-1]
 *  \param[out]   OptPtr      Pointer to the message options.
 *                            [Pointer can be NULL_PTR.
 *                             - NULL_PTR:- Update the total length of the Parameter Request list option.
 *                             - Non NULL_PTR:- Copy information regarding Parameter Request list option to the buffer.]
 *                            CONSTRAINT: CM_TCPIP_DHCPV4_OPT_BUF_VALID_ACCESS
 *  \return                   Message length of parameter request option.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
STATIC FUNC(uint8, TCPIP_CODE) TcpIp_DhcpV4_VAddParamReqListOpt(
  TcpIp_SizeOfIpV4CtrlType                IpV4CtrlIdx,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) OptPtr);

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_Init( void )
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_IpV4CtrlDynIterType ipV4CtrlIdx;/* ip controller index */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all IPv4 controllers that have DHCPv4 address assignment method.*/
  for (ipV4CtrlIdx = 0; ipV4CtrlIdx < TcpIp_GetSizeOfIpV4Ctrl(); ipV4CtrlIdx++)
  {
    /* #20 Check if Dhcp is configured on Ip controller. */
    if (TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(ipV4CtrlIdx) == TRUE)
    {
      TcpIp_SizeOfDhcpStatusType dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(ipV4CtrlIdx);

      TcpIp_SetSecTimerOfDhcpStatus(dhcpStatusIdx, 0);                                                                  /* SBSW_TCPIP_CSL03_IDX_CALLEE */
      TcpIp_SetMsTimerOfDhcpStatus(dhcpStatusIdx, 0);                                                                   /* SBSW_TCPIP_CSL03_IDX_CALLEE */
      TcpIp_SetSecElapsedOfDhcpStatus(dhcpStatusIdx, 0);                                                                /* SBSW_TCPIP_CSL03_IDX_CALLEE */
      TcpIp_SetCtrlStateOfDhcpStatus(dhcpStatusIdx, TCPIP_DHCPV4_CTRL_STATE_OFF);                                       /* SBSW_TCPIP_CSL03_IDX_CALLEE */
      TcpIp_SetHostNameLenOfDhcpStatus(dhcpStatusIdx, 0);                                                               /* SBSW_TCPIP_CSL03_IDX_CALLEE */
      TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->Ciaddr = 0;                                                   /* SBSW_TCPIP_CSL03_IDX_CALLEE */
      TcpIp_SetTimeoutOccurredOfDhcpStatus(dhcpStatusIdx, FALSE);                                                       /* SBSW_TCPIP_CSL03_IDX_CALLEE */
    }
  }

} /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_MainFunction
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */

FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_MainFunction(void)
{

  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_IpV4CtrlDynIterType ipV4CtrlIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all IPv4 controllers that have a local address with DHCPv4 address assignment method. */
  for (ipV4CtrlIdx = 0; ipV4CtrlIdx < TcpIp_GetSizeOfIpV4CtrlDyn(); ipV4CtrlIdx++)
  {
    if (TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(ipV4CtrlIdx) == TRUE)                                                          /* SBSW_TCPIP_CM_R10 */
    {
      TcpIp_SizeOfDhcpConfigType dhcpConfigIdx = TcpIp_GetDhcpConfigIdxOfIpV4Ctrl(ipV4CtrlIdx);
      TcpIp_SizeOfDhcpStatusType dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(ipV4CtrlIdx);

      /* #20 If configured, restart DHCPv4 address assignment if a failure has occurred. */
      if (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_OFF)
      {
        if (   (TcpIp_IsRestartOnFailOfDhcpConfig(dhcpConfigIdx))  /* PRQA S 3415 */ /*  MD_TcpIp_12.4_CslReadOnly */
            && (TcpIp_IsTimeoutOccurredOfDhcpStatus(dhcpStatusIdx)))
        {
          /* restart addr config */
          TcpIp_DhcpV4_TriggerAddrRequest((TcpIp_SizeOfIpV4CtrlType)ipV4CtrlIdx);
        }

        continue;  /* PRQA S 0770 */ /* MD_TCPIP_DHCPV4_14.5_0770 */
      }

      /* #30 Update time variable used for timeout handling. */
      TcpIp_SetMsTimerOfDhcpStatus(dhcpStatusIdx, TcpIp_GetMsTimerOfDhcpStatus(dhcpStatusIdx) + TCPIP_MAIN_FCT_PERIOD_MSEC);/* SBSW_TCPIP_CSL03_IDX_CALLEE */

      if (TcpIp_GetMsTimerOfDhcpStatus(dhcpStatusIdx) >= 1000)
      {
        /* one second passed */
        TcpIp_SetMsTimerOfDhcpStatus(dhcpStatusIdx, TcpIp_GetMsTimerOfDhcpStatus(dhcpStatusIdx) - 1000);                /* SBSW_TCPIP_CSL03_IDX_CALLEE */
        TcpIp_IncSecTimerOfDhcpStatus(dhcpStatusIdx);                                                                   /* SBSW_TCPIP_CSL03_IDX_CALLEE */
        TcpIp_IncSecElapsedOfDhcpStatus(dhcpStatusIdx);                                                                 /* SBSW_TCPIP_CSL03_IDX_CALLEE */
      }

      /* #40 Perform actions based on current DHCP state is necessary. */
      if (TcpIp_GetSecNextEventOfDhcpStatus(dhcpStatusIdx) <= TcpIp_GetSecTimerOfDhcpStatus(dhcpStatusIdx))
      {
        /* -------------------------------------------------------------------- */
        /* start of STATE dependent processing -------------------------------- */
        TcpIp_DhcpV4_VProcessCtrlState( (TcpIp_SizeOfIpV4CtrlDynType)ipV4CtrlIdx);
      }
    }
  }
}  /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_TriggerAddrRequest
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_TriggerAddrRequest(TcpIp_IpV4CtrlIterType IpV4CtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfDhcpStatusType dhcpStatusIdx;
  TcpIp_SizeOfDhcpConfigType dhcpConfigIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE);
  TCPIP_ASSERT(TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE);

  CANOE_WRITE_STRING("TcpIp_DhcpV4_TriggerAddrRequest: function was called")
  dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);
  dhcpConfigIdx = TcpIp_GetDhcpConfigIdxOfIpV4Ctrl(IpV4CtrlIdx);

  TcpIp_SetRetryCounterOfDhcpStatus(dhcpStatusIdx, 0);                                                                  /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
  TcpIp_SetSecTimerOfDhcpStatus(dhcpStatusIdx, 0);                                                                      /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
  TcpIp_SetSecElapsedOfDhcpStatus(dhcpStatusIdx, 0);                                                                    /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
  {
    /* #10 Set timer and event for initial wait. */
    uint16 randTimeMsec;
    randTimeMsec = ( TcpIp_GetRandomNumber() 
                   % (TcpIp_GetInitWaitMaxOfDhcpConfig(dhcpConfigIdx)
                   - TcpIp_GetInitWaitMinOfDhcpConfig(dhcpConfigIdx)) )
                   + TcpIp_GetInitWaitMinOfDhcpConfig(dhcpConfigIdx);                                                   /* SBSW_TCPIP_RANDOM_NUMBER_FUNC */

    TcpIp_SetMsTimerOfDhcpStatus(dhcpStatusIdx, (1000 - (randTimeMsec % 1000)));                                        /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, ((randTimeMsec / 1000) +1));                                       /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
  }
  /* #20 Set State to init */
  TcpIp_SetCtrlStateOfDhcpStatus(dhcpStatusIdx, TCPIP_DHCPV4_CTRL_STATE_INIT);                                          /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */

}  /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_StopAddrRequest
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_StopAddrRequest(
  TcpIp_IpV4CtrlIterType  IpV4CtrlIdx )
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset Dhcp module for this Ip Controller. */
    TcpIp_DhcpV4_Reset(IpV4CtrlIdx);
  
}

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_RxIndication
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
FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_RxIndication(
    TcpIp_IpV4CtrlIterType                                     IpV4CtrlIdx,
    P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)                   DataPtr,
    uint16                                                     DataLen,
    P2CONST(IpBase_SockAddrInType, AUTOMATIC, TCPIP_APPL_DATA) SourcePtr,
    P2CONST(IpBase_SockAddrInType, AUTOMATIC, TCPIP_APPL_DATA) DestinationPtr,
    boolean                                                    ChecksumCalculated)
{
  /* ----- Local Variables ---------------------------------------------- */ 
  uint8 physAddr[TCPIP_PHYS_ADDR_LEN_BYTE];
  IpBase_PortType  srcPort; 
  IpBase_PortType  tgtPort;
  uint16           lenByte; 

  Std_ReturnType   retVal;
  /* ----- Implementation ----------------------------------------------- */ 
  /* In Vector's implementation of the TCPIP-Stack, receiving on UDP sockets always provides a
     linear buffer. So direct DHCP header access via a single struct is possible. */
  TCPIP_ASSERT(DataPtr != NULL_PTR);
  srcPort = TCPIP_GET_UINT16(DataPtr, DHCPV4_SRCPORT_OFS);
  tgtPort = TCPIP_GET_UINT16(DataPtr, DHCPV4_TGTPORT_OFS);
  lenByte = TCPIP_GET_UINT16(DataPtr, DHCPV4_LEN_BYTE_OFS);

  /* #10 Check if DHCP address assignment is enabled for this controller. */
  if (TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx) == FALSE)
  {
    /* DHCP not enabled for this controller */
    retVal = E_NOT_OK;
  }
  /* #20 Check if data length and ports are valid. */
  else
  {
    retVal = TcpIp_DhcpV4_VDataLengthAndPortCheck(DataLen, srcPort, tgtPort, lenByte);
  }

  if (retVal == E_OK)
  {
    /* #30 Verify if the checksum was already checked by the lower layer.*/
    if (ChecksumCalculated == TRUE)
    {
      /* The DHCP checksum was already checked by the lower layer / hardware. If the checksum was wrong the packet will not reach the DHCP at all, so no further check is necessary here. */
    }
    else
    {
      /* #40 calculate checksum. */
      uint32 checksumTmp = TcpIp_VCalcIpV4PseudoHdrChecksum(SourcePtr->sin_addr, DestinationPtr->sin_addr, TCPIP_SOCK_PROT_UDP, DataLen);

      checksumTmp = (uint16)IpBase_TcpIpChecksumAdd(DataPtr, DataLen, checksumTmp, TRUE);                               /* SBSW_TCPIP_DHCPV4_FUNC_CALL_PTR_PASSING_CALLER */

      if (checksumTmp != 0)
      {
        retVal = E_NOT_OK;
      }
    }
  } 

  if (retVal == E_OK)
  {
    uint32 magicPattern;
    /* skip UDP header */
    DataPtr = &DataPtr[TCPIP_UDP_HDR_LEN_BYTE];
    DataLen = (uint16)(lenByte - TCPIP_UDP_HDR_LEN_BYTE); /* PRQA S 3382 */ /* MD_TCPIP_DHCPV4_21.1_3382_a */
    magicPattern = TCPIP_GET_UINT32(DataPtr, TCPIP_DHCPV4_FRAME_MAGICPATTERN_OFS);
    /* #50 Verify the magic pattern. */
    /* Ignore this message if magic pattern at end of DHCP header is not set correctly. */
    if (magicPattern != TCPIP_DHCPV4_MAGIC_PATTERN)
    {
      retVal = E_NOT_OK;
    }
    /* find the corresponding controller */
    /* compare Msg-HW-Addr with own addr (future: compare to all controller addresses) */
    if (retVal == E_OK)
    {
      TcpIp_DhcpV4_VEvaluateOptions(IpV4CtrlIdx, DataPtr, DataLen, &physAddr[0]);                                       /* SBSW_TCPIP_DHCPV4_FUNC_CALL_PTR_PASSING_CALLER */ /* SBSW_TCPIP_DHCPV4_FUNC_CALL_WRITE_ACCESS_ARRAY_PHYSADDR */ 
    }
  }
}  /* PRQA S 6050, 6060 */ /* MD_TcpIp_STCAL_CslAccess, MD_MSR_STPAR */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_Reset
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_Reset(TcpIp_IpV4CtrlIterType IpV4CtrlIdx)
{ 
  /* ----- Implementation ----------------------------------------------- */ 
  /* #10 Reset DHCP module for this controller. */
  if (TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
  {
    TcpIp_SizeOfDhcpStatusType dhcpStatusIdx;
    dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);
    TcpIp_SetCtrlStateOfDhcpStatus(dhcpStatusIdx, TCPIP_DHCPV4_CTRL_STATE_OFF);                                         /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    TcpIp_SetSecTimerOfDhcpStatus(dhcpStatusIdx, 0);                                                                    /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    TcpIp_SetMsTimerOfDhcpStatus(dhcpStatusIdx, 0);                                                                     /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->Ciaddr = 0;                                                     /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    TcpIp_SetReqIpAddrOfDhcpStatus(dhcpStatusIdx, IPV4_ADDR_ANY);                                                       /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    TcpIp_SetTimeoutOccurredOfDhcpStatus(dhcpStatusIdx, FALSE);                                                         /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
  }
} /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_SetHostName
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_SetHostName(
    TcpIp_SizeOfIpV4CtrlType                   IpV4CtrlIdx,
    P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) DataPtr,
    uint8                                      DataLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_SizeOfDhcpStatusType dhcpStatusIdx;
  TcpIp_SizeOfDhcpConfigType dhcpConfigIdx;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(DataPtr != NULL_PTR);

  if (TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
  {
    dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);
    dhcpConfigIdx = TcpIp_GetDhcpConfigIdxOfIpV4Ctrl(IpV4CtrlIdx);
    /* #10 Check if Host name length is bigger than the maximum allowed length.*/
    if (DataLen > TcpIp_GetHostNameLenMaxOfDhcpConfig(dhcpConfigIdx))
    {
      TcpIp_CallDetReportError(TCPIP_DHCPV4_API_ID_SET_HOST_NAME, TCPIP_E_INV_ARG);
    }
    else
    {
      /* set name length */
      TcpIp_SetHostNameLenOfDhcpStatus(dhcpStatusIdx, DataLen);                                                         /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      /* copy name */
      {
        uint8_least                dataIdx;
        TcpIp_DhcpHostnameIterType hostnameByteOfs = TcpIp_GetDhcpHostnameStartIdxOfIpV4Ctrl(IpV4CtrlIdx);
        for (dataIdx = 0; dataIdx < DataLen; dataIdx++)
        {
          TcpIp_SetDhcpHostname(hostnameByteOfs + dataIdx, DataPtr[dataIdx]);                                           /* SBSW_TCPIP_WRITE_DHCPHOSTNAME */
        }
      }
      retVal =  E_OK;
    } 
  }
  return retVal;
} /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_GetDhcpTimeoutInfo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(boolean, TCPIP_CODE) TcpIp_DhcpV4_GetDhcpTimeoutInfo(TcpIp_IpV4CtrlIterType IpV4CtrlIdx)
{ 
  boolean retVal = FALSE;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if address assignment is configured for a given Ip Instance. */
  if (TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE)
  {
    /* #20 Get Dhcp Status Index of a given Ip Instance. */
    TcpIp_SizeOfDhcpStatusType dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);
    retVal = (boolean)(TcpIp_IsTimeoutOccurredOfDhcpStatus(dhcpStatusIdx) == TRUE);
  }
  return retVal;
}

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_GetActiveAddress
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(boolean, TCPIP_CODE) TcpIp_DhcpV4_GetActiveAddress(
    TcpIp_LocalAddrV4IterType                             IpV4CtrlIdx,
    P2VAR(IpV4_IpAddrSetType, AUTOMATIC, TCPIP_APPL_DATA) AddrInfoPtr)
{
  /* ----- Local Variables ----------------------------------------------- */
  TcpIp_SizeOfDhcpStatusType dhcpStatusIdx;
  /* ----- Implementation ----------------------------------------------- */
  boolean retVal = FALSE;
  TCPIP_ASSERT(TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx) == TRUE);
  dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);
  TCPIP_ASSERT(IpV4_Ip_VCfgGetAddrAssignmentPrio(IpV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_DHCP) != 0);
  /* #10 Check if DHCP instance has an active lease from a DHCP server. */
  if (   (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_BOUND)  /* PRQA S 3415 */ /* MD_TcpIp_12.4_CslReadOnly */
      || (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_RENEWING)
      || (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_REBINDING))
  {
    /* #20 Copy address information into provided output structure. */
    AddrInfoPtr->NetAddr   =  TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->Ciaddr;                               /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
    AddrInfoPtr->NetMask   = TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->NetMask;                               /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
    AddrInfoPtr->DefGwAddr = TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->DefGWiaddr;                            /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
    retVal = TRUE;
  }

  return retVal;
}

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VEvaluateOptions
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VEvaluateOptions(
  TcpIp_IpV4CtrlIterType                      IpV4CtrlIdx,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)  DataPtr,
  uint16                                      DataLen,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)    PhysAddr)
{
  /* ----- Local Variables ----------------------------------------------- */
  TcpIp_SizeOfDhcpStatusType dhcpStatusIdx;
  uint8 opcode;                  /* op code: 1 = BOOTREQUEST, 2 = BOOTREPLY */
  uint8 hwType;
  uint8 hwLen;
  uint32 xid;                 /* Transaction ID */  /* PRQA S 0781 */ /* MD_TCPIP_5.6_0781 */
  TcpIp_NetAddrType yiaddr;   /* Your (client) IP address */  /* PRQA S 0781 */ /* MD_TCPIP_5.6_0781 */
  uint8 chaddr[16];          /* Client hardware address */  /* PRQA S 0781 */ /* MD_TCPIP_5.6_0781 */

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_LL_GetPhysAddr(TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(IpV4CtrlIdx), &PhysAddr[0]);                                     /* SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_CALLER */
  /* Read the opcode from the memory and save into the opcode variable */
  opcode = TCPIP_GET_UINT8(     DataPtr, TCPIP_DHCPV4_FRAME_OPCODE_OFS);
  hwType = TCPIP_GET_UINT8(     DataPtr, TCPIP_DHCPV4_FRAME_HWADDR_TYPE_OFS);
  hwLen  = TCPIP_GET_UINT8(     DataPtr, TCPIP_DHCPV4_FRAME_HWADDR_LEN_OFS);
  xid    = TCPIP_GET_UINT32_RAW(DataPtr, TCPIP_DHCPV4_FRAME_XID_OFS);
  yiaddr = TCPIP_GET_UINT32(    DataPtr, TCPIP_DHCPV4_FRAME_YIADDR_OFS);

  yiaddr = TCPIP_NTOHL(yiaddr);
  IpBase_Copy(&chaddr[0], &DataPtr[TCPIP_DHCPV4_FRAME_CLIENT_HW_ADDR_OFS], 16);                                         /* SBSW_TCPIP_IPBASE_COPY_CALLEE */
 
  /* #10 Get Dhcp Status Index for a given Ip controller. */
  dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);
  /* #20 Verify if the message is for this node. */
  if (   (TcpIp_CmpLLAddr(&chaddr[0], &PhysAddr[0]) == TRUE)
      && (opcode == TCPIP_DHCPV4_OP_BOOTREPLY)  /* this message comes from a server */
      && (hwType == TCPIP_DHCPV4_HW_TYPE_ETH)
      && (hwLen  == TCPIP_DHCPV4_HW_LEN_ETH)
      && (xid    == TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->Xid))/* this message corresponds to the current DHCP XID */ /* SBSW_TCPIP_FUNC_CALL_PARAM_PTR_PHYSADDR_CALLER */
  {
    TcpIp_DhcpV4_DataStructType locConfigData;
    uint8 msgType = TCPIP_DHCPV4_DHCPINVALIDMSG;
    uint16 overallOptLen = (uint16)(DataLen - TCPIP_DHCPV4_MIN_HEADER_LENGTH_BYTE);
    uint16 remainingOptLen = overallOptLen;
    const uint8 *optPtr = &DataPtr[TCPIP_DHCPV4_MIN_HEADER_LENGTH_BYTE]; /* set optPtr at starting of option field (code) */
    TcpIp_DhcpV4_DnsOptInfoType dnsServerOpt;
    boolean endOptFound = FALSE;
    boolean msgIsValid = TRUE;
    /* now evaluate DHCP options */
    locConfigData.T1          = 0;
    locConfigData.T2          = 0;
    locConfigData.Ciaddr      = yiaddr;
    locConfigData.NetMask     = 0;
    locConfigData.DefGWiaddr  = 0;
    locConfigData.DhcpSiaddr  = 0;
    locConfigData.LeaseTime   = 0;

    dnsServerOpt.DnsServerAddrCount = 0;
    dnsServerOpt.DnsServerAddrPtr   = NULL_PTR;

    /* #30 Iterate over all supported options. */
    while ((msgIsValid == TRUE) && (remainingOptLen > 0))
    {
      /* evaluate all supported options */
      if (*optPtr == TCPIP_DHCPV4_OPT_PAD_TYPE)
      {
        /* option Pad */
        optPtr = &optPtr[1];
        remainingOptLen--;
      }
      else if (*optPtr == TCPIP_DHCPV4_OPT_END_TYPE)
      {
        /* option End */
        endOptFound = TRUE;
        break;
      }
      else
      { /* Option length is first 2 bytes(code + len) + the value stored at the 2nd byte(optPtr[1]) */
        uint8 optLen = TCPIP_DHCPV4_OPTION_HDR_BYTE + optPtr[1];

        if ((remainingOptLen < TCPIP_DHCPV4_OPTION_HDR_BYTE) || (optLen > remainingOptLen))
        {
           msgIsValid = FALSE;
          /* ERROR:
          - options have at least option type and length fields
          - option length may not be greater than remaining data length */
          break;  /* PRQA S 0771 */ /* MD_TCPIP_DHCPV4_14.6_0771_a */
        }

        if (TcpIp_DhcpV4_ProcessOptions(optPtr, &msgType, &locConfigData, &dnsServerOpt) == E_OK)                       /* SBSW_TCPIP_UPDATE_VARIABLE */ /* SBSW_TCPIP_FUNC_CALL_LOCAL_PTR_OPTION */
        {
          /* Update the option pointer and the remaining option length .*/
          optPtr = &optPtr[optLen];
          remainingOptLen -= optLen;
        }
        else
        {
          msgIsValid = FALSE;
        }
      }
    }  /* while(RemainingOptLen > 0) */

    if (msgIsValid == TRUE)
    {
      TcpIp_DhcpV4_VVerifyMsgType(msgType, &msgIsValid, endOptFound, &locConfigData, dhcpStatusIdx);                    /* SBSW_TCPIP_UPDATE_VARIABLE */
    }

    if (msgIsValid == TRUE)
    {
      TcpIp_DhcpV4_VProcessDhcpMsg(IpV4CtrlIdx, msgType, &locConfigData, &dnsServerOpt, yiaddr);                        /* SBSW_TCPIP_UPDATE_VARIABLE */
    }
  }
} /* PRQA S 6080, 6050 */ /* MD_MSR_STMIF, MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VVerifyMsgType
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VVerifyMsgType( 
  uint8                                                            MsgType,
  P2VAR(boolean, AUTOMATIC, TCPIP_APPL_DATA)                       MsgIsValidPtr,
  boolean                                                          EndOptFound,
  P2CONST(TcpIp_DhcpV4_DataStructType, AUTOMATIC, TCPIP_APPL_DATA) LocConfigData,
  TcpIp_SizeOfDhcpStatusType                                       DhcpStatusIdx)
 {
   /* #10 Check if message type has a valid value */
   if (   (MsgType == TCPIP_DHCPV4_DHCPINVALIDMSG)
       || (MsgType > TCPIP_DHCPV4_DHCPINFORM))
   {
     *MsgIsValidPtr = FALSE;                                                                                            /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
   }
   /* #20 Check if end option is missing.*/
   else if (EndOptFound != TRUE)
   {
     /* end option is missing */
     *MsgIsValidPtr = FALSE;                                                                                            /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
   }
   /* #30 Check if DHCP message is either DHCPOFFER or DHCPACK and lease time is not expired. */
   else if (( LocConfigData->LeaseTime == 0) && ((MsgType == TCPIP_DHCPV4_DHCPACK) || (MsgType == TCPIP_DHCPV4_DHCPOFFER)))
   {
     /* invalid DHCP message type, or invalid lease time */
     *MsgIsValidPtr = FALSE;                                                                                            /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
   }
   else if (   (TcpIp_GetCtrlStateOfDhcpStatus(DhcpStatusIdx) != TCPIP_DHCPV4_CTRL_STATE_SELECTING)
            && (TcpIp_GetAddrDataStructOfDhcpStatus(DhcpStatusIdx)->DhcpSiaddr != LocConfigData->DhcpSiaddr))
   {
     /* discard messages from other servers than the selected one */
     *MsgIsValidPtr = FALSE;                                                                                            /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
   }
   else
   {
     TcpIp_DhcpV4_VVerifyClientAddr(LocConfigData, MsgIsValidPtr, MsgType);                                             /* SBSW_TCPIP_DHCPV4_FUNC_CALL_PTR_PASSING_CALLER */
   }
}
/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VProcessDhcpMsg
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VProcessDhcpMsg(
  TcpIp_IpV4CtrlIterType                                           IpV4CtrlIdx,
  uint8                                                            MsgType,
  P2CONST(TcpIp_DhcpV4_DataStructType, AUTOMATIC, TCPIP_APPL_DATA) LocConfigData,
  P2CONST(TcpIp_DhcpV4_DnsOptInfoType, AUTOMATIC, TCPIP_APPL_DATA) DnsServerOptPtr,
  TcpIp_NetAddrType                                                Yiaddr)
{
  /* ----- Implementation ----------------------------------------------- */
  TcpIp_SizeOfDhcpStatusType  dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);
  /* #10 Verify if the received Dhcp message is valid. */
  if (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_SELECTING)
  {
    /* #20 Verify if the incoming message is DHCPOFFER. */
    if (MsgType == TCPIP_DHCPV4_DHCPOFFER)
    {
      /* incoming offer for IP address */

      /* Always take the first DHCPOFFER and use is for further processing. */
      /*#30.Store addresses of a incoming messages. */
      TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->Ciaddr      = Yiaddr;                                         /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->DhcpSiaddr  = LocConfigData->DhcpSiaddr;                      /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->NetMask     = LocConfigData->NetMask;                         /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->DefGWiaddr  = LocConfigData->DefGWiaddr;                      /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */

      /* switch mode to next state and set timeout (for transmission of request) */
      /* #40 Reset timer because lease times are stored relative to the DHCPREQUEST message. */
      TcpIp_SetSecTimerOfDhcpStatus(dhcpStatusIdx, 0);                                                                  /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_SetMsTimerOfDhcpStatus(dhcpStatusIdx, 0);                                                                   /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, 0);                                                              /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_SetRetryCounterOfDhcpStatus(dhcpStatusIdx, 0);                                                              /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      /* Value of TcpIp_SetSecElapsedOfDhcpStatus is not reset here because this value
      * reflects the time since beginning of address acquisition process. [RFC2131 page 10]
      */
      TcpIp_SetCtrlStateOfDhcpStatus(dhcpStatusIdx, TCPIP_DHCPV4_CTRL_STATE_REQUESTING);                                /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    }
    else
    {
      /* #50 Ignore incoming ACK and NAK in this state. */
    }
  }
  else if (   (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_REQUESTING)   /* PRQA S 3415 */ /* MD_TcpIp_12.4_CslReadOnly */
           || (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_RENEWING)
           || (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_REBINDING))
  {
    TcpIp_DhcpV4_ProcessAckOrNak(IpV4CtrlIdx, Yiaddr, MsgType, LocConfigData, DnsServerOptPtr);                         /* SBSW_TCPIP_DHCPV4_FUNC_CALL_PTR_PASSING_CALLER */
  }
  else
  {
    /* ignore messages in all other states */
  }
  /* end of DHCP message "switch" */
  /* end if(MsgIsValid) */
} /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VDataLengthAndPortCheck
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_VDataLengthAndPortCheck(
  uint16                                    DataLen,
  IpBase_PortType                           SrcPort,
  IpBase_PortType                           TgtPort,
  uint16                                    LenByte)
{
  Std_ReturnType retVal = E_OK;
  /* #10 Verify that data length is bigger than UDP  header length. */
  if (DataLen < TCPIP_UDP_HDR_LEN_BYTE)
  {
    /* invalid length */
    retVal = E_NOT_OK;
  }
  else
  {
    /* #20 Verify that the server port and destination port are correct. */
    if ((SrcPort != TCPIP_DHCPV4_SERVER_PORT) || (TgtPort != TCPIP_DHCPV4_CLIENT_PORT))
    {
      retVal = E_NOT_OK;
    }
    else
    {
      /* #30 Verify if Udp Packet length is valid. */
      if ((LenByte > DataLen) || (LenByte < (TCPIP_UDP_HDR_LEN_BYTE + TCPIP_DHCPV4_MIN_HEADER_LENGTH_BYTE)))
      {
        retVal = E_NOT_OK;
      }
    }
  }
  return retVal;
}
/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VVerifyClientAddr
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VVerifyClientAddr(
  P2CONST(TcpIp_DhcpV4_DataStructType, AUTOMATIC, TCPIP_APPL_DATA) LocConfigData,
  P2VAR(boolean, AUTOMATIC, TCPIP_APPL_DATA)                       MsgIsValidPtr,
  uint8                                                            MsgType)
{ 
  /* #10 Verify if Ciaddr is not zero and Message is DHCPNACK. */
  if ((LocConfigData->Ciaddr == 0) && (MsgType != TCPIP_DHCPV4_DHCPNACK))
  {
    *MsgIsValidPtr = FALSE;                                                                                             /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
  }
  /* #20 Check for invalid client address 'global broadcast. */
  else if (LocConfigData->Ciaddr == TCPIP_INADDR_BROADCAST)
  {
    *MsgIsValidPtr = FALSE;                                                                                             /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
  }
   /* #30 Check for invalid client address 'multicast'. */
  else if ((TCPIP_HTONL(LocConfigData->Ciaddr) & 0xF0000000u) == 0xE0000000u)
  {
    *MsgIsValidPtr = FALSE;                                                                                             /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
  }
   /* #40 Check for invalid network mask. */
  else if (LocConfigData->NetMask != 0)
  {
    uint8_least shiftCnt = 0u;
    uint32 netmaskShifted = TCPIP_HTONL(LocConfigData->NetMask);
    while (((netmaskShifted & 0x01) == 0u)) /* This condition will be false after a maximum of 31 iterations since at least one bit in NetmaskShifted is set. */
    {
      netmaskShifted = netmaskShifted >> 1;
      shiftCnt++;
    }

    while ((shiftCnt < 32u) && ((netmaskShifted & 0x01) == 1u))
    {
      netmaskShifted = netmaskShifted >> 1;
      shiftCnt++;
    }

    if (shiftCnt != 32u)
    {
      /* discard messages, network mask is not a sequence of '1'-bits followed by a sequence of '0'-bits */
      *MsgIsValidPtr = FALSE;                                                                                           /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
    }
  }
  else
  {
  /* nothing to do */
  }
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
/**********************************************************************************************************************
 *  TcpIp_DhcpV4_ProcessOptions
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
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_ProcessOptions(
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA)                     OptPtr,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)                       MsgTypePtr,
  P2VAR(TcpIp_DhcpV4_DataStructType, AUTOMATIC, TCPIP_APPL_DATA) LocConfigData,
  P2VAR(TcpIp_DhcpV4_DnsOptInfoType, AUTOMATIC, TCPIP_APPL_DATA) DnsServerOptPtr)
{
  /* ----- Local Variables ----------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 optLen;
  DnsServerOptPtr->DnsServerAddrCount = 0;
  DnsServerOptPtr->DnsServerAddrPtr   = NULL_PTR;

  /* ----- Implementation ----------------------------------------------- */
  optLen = OptPtr[1];
  switch (*OptPtr)
  {
  case (TCPIP_DHCPV4_OPT_SUBNET_MASK_TYPE):
    {
      /* #10 Verify the length of SUBNET_MASK option. */
      if(optLen == TCPIP_DHCPV4_OPT_SUBNET_MASK_LEN)
      {
        /* Address is stored in host byte-order */
        LocConfigData->NetMask = TCPIP_GET_UINT32_RAW(OptPtr, 2);                                                       /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        /* If the server specifies a subnet mask it must not be zero. */
        if (LocConfigData->NetMask != 0) 
        {
          retVal = E_OK;
        }
      }
      break;
    }

  case (TCPIP_DHCPV4_OPT_ROUTER_TYPE):
    {
      /* #20 Verify the length of ROUTER option to get DefaultGateway address.*/
      if (((optLen % TCPIP_DHCPV4_OPT_ROUTER_LEN) == 0) && (optLen >= TCPIP_DHCPV4_OPT_ROUTER_LEN))
      {
        /* Address is stored in host byte-order */
        LocConfigData->DefGWiaddr = TCPIP_GET_UINT32_RAW(OptPtr, 2);                                                    /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        retVal = E_OK;
      }
      break;
    }

  case (TCPIP_DHCPV4_OPT_IP_ADDR_LEASE_TIME_TYPE):
    {
      /* #30 Verify the length of IP_ADDR_LEASE_TIME option. */
      if(optLen == TCPIP_DHCPV4_OPT_IP_ADDR_LEASE_TIME_LEN)
      {
        
        LocConfigData->LeaseTime = TCPIP_GET_UINT32(OptPtr, 2);                                                         /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        retVal = E_OK;
      }
      break;
    }

  case (TCPIP_DHCPV4_OPT_DHCPV4_MSG_TYPE):
    { 
      if(optLen == TCPIP_DHCPV4_OPT_DHCPV4_MSG_LEN)
      {
        /* option TCPIP_DHCPV4_MSG -> message type (DHCPOFFER, DHCPACK, DHCPNAK) */
       
        *MsgTypePtr = OptPtr[2];                                                                                        /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        retVal = E_OK;
      }
      break;
    }

  case (TCPIP_DHCPV4_OPT_SERVER_ID_TYPE):
    {
      /* #40 Verify the length of SERVER ID option. */
      if(optLen == TCPIP_DHCPV4_OPT_SERVER_ID_LEN)
      {
        /* option SERVER_ID */
        
        /* Address is stored in host byte-order */
        LocConfigData->DhcpSiaddr = TCPIP_GET_UINT32_RAW(OptPtr, 2);                                                    /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        retVal = E_OK;
      }
      break;
    }

  case (TCPIP_DHCPV4_OPT_RENEWAL_TIME_T1_VAL_TYPE):
    { 
      /* #50 Verify the length of Renewal (T1) Time Value option. */
      if(optLen == TCPIP_DHCPV4_OPT_RENEWAL_TIME_T1_VAL_LEN)
      {
      /* option RENEWAL_TIME_T1 */
      
        LocConfigData->T1 = TCPIP_GET_UINT32(OptPtr, 2);                                                                /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        retVal = E_OK;
      }
      break;
    }

  case (TCPIP_DHCPV4_OPT_REBINDING_TIME_T2_VAL_TYPE):
    {
      /* #60 Verify the length of Rebinding (T2) Time Value option. */
      if (optLen == TCPIP_DHCPV4_OPT_REBINDING_TIME_T2_VAL_LEN)
      {
        /* option RENEWAL_TIME_T2 */
      
        LocConfigData->T2 = TCPIP_GET_UINT32(OptPtr, 2);                                                                /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        retVal = E_OK;
      }
      break;
    }

#if (TCPIP_SUPPORT_DNS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
  case (TCPIP_DHCPV4_OPT_DOMAIN_NAME_SERVER_TYPE):
    { 
      /* #70 Verify the length of Domain Name Server option.*/
      /* option DOMAIN_NAME_SERVER */
      uint8 LocOptLen = OptPtr[1];
      if (((LocOptLen % TCPIP_DHCPV4_OPT_DOMAIN_NAME_SERVER_LEN) == 0) && (LocOptLen >= TCPIP_DHCPV4_OPT_DOMAIN_NAME_SERVER_LEN))
      {
        DnsServerOptPtr->DnsServerAddrPtr   = (TCPIP_P2C(IpBase_AddrInType))(&OptPtr[2]);  /* PRQA S 0310 */ /* MD_IpV6_0310_Uint8ToStruct */
        DnsServerOptPtr->DnsServerAddrCount = (uint8)(LocOptLen / TCPIP_DHCPV4_OPT_DOMAIN_NAME_SERVER_LEN);
        retVal = E_OK;
      }
      break;
    }
#endif

  default:
    {
      /* not supported DHCP option -> skip this option */
      retVal = E_OK;
      break;
    }
  }
  return retVal;
} /* PRQA S 6030 */ /* MD_MSR_STCYC */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_ProcessAckOrNak
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_ProcessAckOrNak(
  TcpIp_IpV4CtrlIterType                                           IpV4CtrlIdx,
  TcpIp_NetAddrType                                                Yiaddr,
  uint8                                                            MsgType,
  P2CONST(TcpIp_DhcpV4_DataStructType, AUTOMATIC, TCPIP_APPL_DATA) LocConfigData,
  P2CONST(TcpIp_DhcpV4_DnsOptInfoType, AUTOMATIC, TCPIP_APPL_DATA) DnsServerOptPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  TcpIp_SizeOfDhcpStatusType dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);

  switch (MsgType)
  {
  case TCPIP_DHCPV4_DHCPACK:
    {
      uint32 ElapsedSecSinceFirstRequest;
      /* incoming ack for requested IP address */
      /* According to the RFC, the DHCP module SHOULD probe its address before using it for
      IP module configuration. This implementation does not implement this feature! */

      /* #10 Store addresses received from the server On reception of DHCPACK message. */
      TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->Ciaddr      = Yiaddr;                                         /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->DhcpSiaddr  = LocConfigData->DhcpSiaddr;                      /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->NetMask     = LocConfigData->NetMask;                         /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->DefGWiaddr  = LocConfigData->DefGWiaddr;                      /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->LeaseTime   = LocConfigData->LeaseTime;                       /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
     
      if (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_REQUESTING)
      {
        /* Timer was reset before transmission of first DHCPREQUEST message. */
        ElapsedSecSinceFirstRequest = TcpIp_GetSecTimerOfDhcpStatus(dhcpStatusIdx);
      }
      else if (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_RENEWING)
      {
        /* First DHCPREQUEST message in state RENEWING was send at T1. */
        ElapsedSecSinceFirstRequest = TcpIp_GetSecTimerOfDhcpStatus(dhcpStatusIdx) - TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->T1;
      }
      else
      {
        /* First DHCPREQUEST message in state REBINDING was send at T2. */
        ElapsedSecSinceFirstRequest = TcpIp_GetSecTimerOfDhcpStatus(dhcpStatusIdx) - TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->T2;
      }

      /* #20 Set timeout T1.*/
      if (LocConfigData->T1 != 0)
      {
        TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->T1 = LocConfigData->T1;                                     /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      }
      else
      {
        /* T1 is 0.5 times the lease time */
        TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->T1 = (TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->LeaseTime >> 1);      /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      }
      /*#30 Set timeout T2. */
      if (LocConfigData->T2 != 0)
      {
       TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->T2 = LocConfigData->T2;                                      /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      }
      else
      {
        /* T2 is 0.875 times the lease time */
        TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->T2 = TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->LeaseTime
                                                  - (TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->LeaseTime >> 3);/* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      }

#if (TCPIP_SUPPORT_DNS == STD_ON)                                                                                       /* COV_MSR_UNSUPPORTED */
      /* set DNS server address */
      if (DnsServerOptPtr->DnsServerAddrCount != 0)
      {
        Dns_UpdateIpV4Servers(DnsServerOptPtr->DnsServerAddrPtr, DnsServerOptPtr->DnsServerAddrCount);
      }
#else
      TCPIP_UNUSED_PARAMETER(DnsServerOptPtr);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
#endif
      /* indicate valid address to IP-module */
      if (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_REQUESTING)
      {
        IpV4_Ip_VIpAddrAssignmentReadyNotification(IpV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_DHCP, TRUE);
      }

      /* Reset Timer variable to time of first DHCPREQUEST message. (T1 and T2 are relative to this value) */
      TcpIp_SetSecTimerOfDhcpStatus(dhcpStatusIdx, ElapsedSecSinceFirstRequest);                                        /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_SetMsTimerOfDhcpStatus(dhcpStatusIdx, 0);                                                                   /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      /* set event timer to T1 */
      TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->T1);         /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      CANOE_WRITE_STRING_2("TcpIp_DhcpV4_RxIndication: next event in %d seconds, last state was %d", TcpIp_GetSecNextEventOfDhcpStatus(dhcpStatusIdx), TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx))
      CANOE_WRITE_STRING_2("TcpIp_DhcpV4_RxIndication: event timers are %d seconds and %d milliseconds", TcpIp_GetSecTimerOfDhcpStatus(dhcpStatusIdx), TcpIp_GetMsTimerOfDhcpStatus(dhcpStatusIdx))
      /* switch mode to next state */
      TcpIp_SetCtrlStateOfDhcpStatus(dhcpStatusIdx, TCPIP_DHCPV4_CTRL_STATE_BOUND);                                     /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      break;
    }

  case TCPIP_DHCPV4_DHCPNACK:
    {
      /* incoming NACK (for requested IP address) -> back to INIT */
      if (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) != TCPIP_DHCPV4_CTRL_STATE_REQUESTING)
      {
        /* indicate loss of IP address to IP-module */
        IpV4_Ip_VIpAddrAssignmentReadyNotification(IpV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_DHCP, FALSE);
      }

      TcpIp_DhcpV4_TriggerAddrRequest(IpV4CtrlIdx);
      break;
    }

  default:
    {
      /* no other messages should arrive, ignore them */
      break;
    } 
  }
} /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VProcessCtrlState
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VProcessCtrlState(TcpIp_SizeOfIpV4CtrlDynType IpV4CtrlIdx)
{
  /* ----- Local Variables ----------------------------------------------- */
  IpBase_AddrInType requestedIpAddr;
  /* ----- Implementation ----------------------------------------------- */
  TcpIp_SizeOfDhcpStatusType dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);
  TcpIp_SizeOfDhcpConfigType dhcpConfigIdx = TcpIp_GetDhcpConfigIdxOfIpV4Ctrl(IpV4CtrlIdx);
  switch (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx))
  {
  case TCPIP_DHCPV4_CTRL_STATE_INIT:
    {
      IpV4_DhcpV4RequestedAddrCalloutFuncType RequestedAddrCalloutFuncPtr = TcpIp_GetReqAddrCalloutFuncOfDhcpConfig(dhcpConfigIdx);
      /* #10 [INIT] Send first DHCPDISCOVER message, schedule retransmission and switch to state SELECTING. */
      TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->Ciaddr = IPV4_ADDR_ANY; /* unassign client ip address */      /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
     
      TcpIp_SetReqIpAddrOfDhcpStatus(dhcpStatusIdx, IPV4_ADDR_ANY);                                                     /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */

      TcpIp_SetSecTimerOfDhcpStatus(dhcpStatusIdx, 0);                                                                  /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */ 
      TcpIp_SetSecElapsedOfDhcpStatus(dhcpStatusIdx, 0);                                                                /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */

      if (RequestedAddrCalloutFuncPtr != NULL_PTR)
      {
        TcpIp_SizeOfLocalAddrV4Type localAddrId;
        requestedIpAddr = TcpIp_GetReqIpAddrOfDhcpStatus(dhcpStatusIdx);
        /* Idx to Id Mapping */
        localAddrId = TCPIP_LOCAL_ADDR_IDX_TO_ID(TcpIp_GetLocalAddrV4DhcpIdxOfIpV4Ctrl(IpV4CtrlIdx));
        RequestedAddrCalloutFuncPtr(localAddrId, &requestedIpAddr);                                                     /* SBSW_TCPIP_FUNC_PTR_CALL */
        TcpIp_SetReqIpAddrOfDhcpStatus(dhcpStatusIdx, requestedIpAddr);                                                 /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      }

      /* send first DISCOVER message */
      if (TcpIp_DhcpV4_VSendDhcpMsg(IpV4CtrlIdx, TCPIP_DHCPV4_MSG_DISCOVER, TCPIP_INADDR_BROADCAST) == E_OK )
      {
        /* TX successful. Switch to state SELECTING */

        TcpIp_SetSecNextIntervalOfDhcpStatus(dhcpStatusIdx, TcpIp_GetDiscoverIntervalMinOfDhcpConfig(dhcpConfigIdx));   /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
        TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, TcpIp_GetSecNextIntervalOfDhcpStatus(dhcpStatusIdx));          /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
        TcpIp_SetCtrlStateOfDhcpStatus(dhcpStatusIdx, TCPIP_DHCPV4_CTRL_STATE_SELECTING);                               /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      }
      else
      {
        /* TX failed. Stay in current state and retry in next MainFunction cycle */
      }
      break;
    }

  case TCPIP_DHCPV4_CTRL_STATE_SELECTING:
    {
      /* #20 [SELECTING] Retransmit DHCPDISCOVER message and schedule next retransmission or cancel DHCP assignment if number of retransmission has been reached. */
      /* check if event has to be triggered */
      /* check if another DISCOVER message may be sent */
      TcpIp_DhcpV4_VSelectingState(IpV4CtrlIdx);
      break;
    }

  case TCPIP_DHCPV4_CTRL_STATE_REQUESTING:
    {
      /* #30 [REQUESTING] Send DHCPREQUEST message and schedule next retransmission or cancel DHCP assignment if number of retransmission has been reached. */
      if ((TcpIp_GetRequestMaxNumOfDhcpConfig(dhcpConfigIdx)) > TcpIp_GetRetryCounterOfDhcpStatus(dhcpStatusIdx))
      {
        TcpIp_NetAddrType DhcpServAddr = TCPIP_INADDR_BROADCAST;
        /* send REQUEST message */
        if (TcpIp_DhcpV4_VSendDhcpMsg(IpV4CtrlIdx, TCPIP_DHCPV4_MSG_REQUEST, DhcpServAddr) == E_OK)
        {
          /* TX successful. Schedule next retry if no response is received. */
          TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, TcpIp_GetSecNextEventOfDhcpStatus(dhcpStatusIdx) + TcpIp_GetRequestIntervalOfDhcpConfig(dhcpConfigIdx));  /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
          TcpIp_IncRetryCounterOfDhcpStatus(dhcpStatusIdx);                                                             /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
        }
        else
        {
          /* TX failed. Stay in current state and retry in next MainFunction cycle */
        }
      }
      else
      {
        /* cancel complete DHCP address request */
        TcpIp_SetCtrlStateOfDhcpStatus(dhcpStatusIdx, TCPIP_DHCPV4_CTRL_STATE_OFF);                                     /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
        TcpIp_SetTimeoutOccurredOfDhcpStatus(dhcpStatusIdx, TRUE);                                                      /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      }
      break;
    }

  case TCPIP_DHCPV4_CTRL_STATE_BOUND:
    {
      /* #40 [BOUND] Switch to state RENEWING after T1 timeout has expired. */
      TcpIp_SetCtrlStateOfDhcpStatus(dhcpStatusIdx, TCPIP_DHCPV4_CTRL_STATE_RENEWING);                                  /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      /* Value of 'secs' field in DHCP message shall restart at 0 when beginning address renewal process. [RFC2131 page 10] */
      TcpIp_SetSecElapsedOfDhcpStatus(dhcpStatusIdx, 0);                                                                /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      break;
    }

  case TCPIP_DHCPV4_CTRL_STATE_RENEWING:
    {
      /* #50 [RENEWING] Transmit DHCPREQUEST (unicast) and schedule next retransmission or switch to state REBINDING if T2 timeout has expired. */
      TcpIp_DhcpV4_RenewingState( IpV4CtrlIdx);
      break;
    }

  case TCPIP_DHCPV4_CTRL_STATE_REBINDING:
    {
      TcpIp_DhcpV4_RebindingState( IpV4CtrlIdx);
      break;
    }

  default:
    {
      /* (currently) unhandled state, or nothing to do */
      break;
    }
    /* end of STATE dependend processing ---------------------------------- */
    /* -------------------------------------------------------------------- */
  }
}  /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VSelectingState
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VSelectingState(TcpIp_SizeOfIpV4CtrlDynType IpV4CtrlIdx)
{

  /* ----- Implementation ----------------------------------------------- */
  TcpIp_SizeOfDhcpStatusType dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);
  TcpIp_SizeOfDhcpConfigType dhcpConfigIdx = TcpIp_GetDhcpConfigIdxOfIpV4Ctrl(IpV4CtrlIdx);
   /* #10 Verify if retry limit has reached. */
  if (   (TcpIp_GetDiscoverMaxNumOfDhcpConfig(dhcpConfigIdx) == 0) /* PRQA S 3415 */ /* MD_TcpIp_12.4_CslReadOnly */ /* retry number is not limited */
      || ((TcpIp_GetDiscoverMaxNumOfDhcpConfig(dhcpConfigIdx) -1) > TcpIp_GetRetryCounterOfDhcpStatus(dhcpStatusIdx)))  /* retry limit not yet reached */
  {
    /* #20 Send another DISCOVER message. */
    if (TcpIp_DhcpV4_VSendDhcpMsg(IpV4CtrlIdx, TCPIP_DHCPV4_MSG_DISCOVER, TCPIP_INADDR_BROADCAST) == E_OK)
    {
      /* #30 TX is successful. Schedule next retry if no response is received. */
      uint32 nextSecInterval;

      /* #40 Calculate Next interval for DISCOVER message. */ 
      if (TcpIp_GetSecNextIntervalOfDhcpStatus(dhcpStatusIdx) < TcpIp_GetDiscoverIntervalMaxOfDhcpConfig(dhcpConfigIdx))
      {
        nextSecInterval = TcpIp_GetSecNextIntervalOfDhcpStatus(dhcpStatusIdx) * 2;
        if (nextSecInterval > TcpIp_GetDiscoverIntervalMaxOfDhcpConfig(dhcpConfigIdx))
        {
          nextSecInterval = TcpIp_GetDiscoverIntervalMaxOfDhcpConfig(dhcpConfigIdx);
        }
        TcpIp_SetSecNextIntervalOfDhcpStatus(dhcpStatusIdx, nextSecInterval);                                           /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      }
      else
      {
        nextSecInterval = TcpIp_GetSecNextIntervalOfDhcpStatus(dhcpStatusIdx);
      }
      TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, TcpIp_GetSecNextEventOfDhcpStatus(dhcpStatusIdx) + nextSecInterval);/* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      TcpIp_IncRetryCounterOfDhcpStatus(dhcpStatusIdx);                                                                 /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    }
    else
    {
      /* TX failed. Stay in current state and retry in next MainFunction cycle */
    }
  }
  else
  {
    /* #50 Cancel complete DHCP address request. */
    TcpIp_SetCtrlStateOfDhcpStatus(dhcpStatusIdx, TCPIP_DHCPV4_CTRL_STATE_OFF);                                         /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    TcpIp_SetTimeoutOccurredOfDhcpStatus(dhcpStatusIdx, TRUE);                                                          /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
  }
}  /* PRQA S 6050, 6030 */ /* MD_TcpIp_STCAL_CslAccess, MD_MSR_STCYC */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_RenewingState
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_RenewingState(TcpIp_SizeOfIpV4CtrlDynType IpV4CtrlIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  TcpIp_SizeOfDhcpStatusType dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);
  TcpIp_SizeOfDhcpConfigType dhcpConfigIdx = TcpIp_GetDhcpConfigIdxOfIpV4Ctrl(IpV4CtrlIdx);
  TCPIP_ASSERT(TcpIp_GetSecNextEventOfDhcpStatus(dhcpStatusIdx) <= TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->T2);
  if (TcpIp_GetSecTimerOfDhcpStatus(dhcpStatusIdx) < TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->T2)
  {
    /* #10 Send unicast  DHCP REQUEST.*/
    if (TcpIp_DhcpV4_VSendDhcpMsg(IpV4CtrlIdx, TCPIP_DHCPV4_MSG_REQUEST, TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->DhcpSiaddr) == E_OK)
    {
      /* RFC 2131 4.4.5 In RENEWING state, if the client receives no response to its DHCPREQUEST message, 
         the client SHOULD wait one-half of the remaining time until T2 (in RENEWING state) down to a minimum of
         configured RenewIntervalMin seconds time, before retransmitting the DHCPREQUEST message.*/

      /* #20 Transmission is successful. Calculate the time for the next event and schedule next retransmission. */
      uint32 timeLeft = (TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->T2 - TcpIp_GetSecNextEventOfDhcpStatus(dhcpStatusIdx));
      /* Verify if time left for retransmission is bigger than Renew interval time */
      if (timeLeft > (uint32)TcpIp_GetRenewIntervalMinOfDhcpConfig(dhcpConfigIdx))
      {
        /* Verify if time left for retransmission is one half of the configured RenewIntervalMin seconds. */
        if (timeLeft > ((uint32)TcpIp_GetRenewIntervalMinOfDhcpConfig(dhcpConfigIdx) *2))
        {
          /* Set next event at one half of the time left until T2. */
          TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, TcpIp_GetSecNextEventOfDhcpStatus(dhcpStatusIdx) + (timeLeft >> 1));/* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
        }
        else
        { /* if time left is smaller than half of the minimum configured RenewIntervalMin time, then set next event at RenewIntervalMin.*/
          TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, TcpIp_GetSecNextEventOfDhcpStatus(dhcpStatusIdx) + TcpIp_GetRenewIntervalMinOfDhcpConfig(dhcpConfigIdx));/* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
        }
      }
      else
      { /* When time left is smaller then minimum configured RenewIntervalMin time, then set next event at T2. */
        TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->T2);       /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      }
    }
    else
    {
      /* TX failed. Stay in current state and retry in next MainFunction cycle */
    }
  }
  else
  {
    /* #30 Switch state  to REBINDING. */
    TcpIp_SetCtrlStateOfDhcpStatus(dhcpStatusIdx, TCPIP_DHCPV4_CTRL_STATE_REBINDING);                                   /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
  }
} /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */
/**********************************************************************************************************************
 *  TcpIp_DhcpV4_RebindingState
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
TCPIP_LOCAL FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_RebindingState(TcpIp_SizeOfIpV4CtrlDynType IpV4CtrlIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  TcpIp_SizeOfDhcpStatusType dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);
  TcpIp_SizeOfDhcpConfigType dhcpConfigIdx = TcpIp_GetDhcpConfigIdxOfIpV4Ctrl(IpV4CtrlIdx);

  /* #10 [REBINDING] Transmit DHCPREQUEST (broadcast) and schedule next retransmission or cancel DHCP assignment if number of retransmission has been reached. */
  if (TcpIp_GetSecTimerOfDhcpStatus(dhcpStatusIdx) < TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->LeaseTime)
  {
    TcpIp_NetAddrType dhcpServAddr = TCPIP_INADDR_BROADCAST;
    /* #20 Send Brodcast DHCP REQUEST. */
    if (TcpIp_DhcpV4_VSendDhcpMsg(IpV4CtrlIdx, TCPIP_DHCPV4_MSG_REQUEST, dhcpServAddr) == E_OK)
    {
      /* #30 Transmission is  successful.Schedule next retransmission. */
      uint32 timeLeft = (TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->LeaseTime - TcpIp_GetSecNextEventOfDhcpStatus(dhcpStatusIdx));
      /* RFC 2131 4.4.5 In REBINDING state, if the client receives no response to its DHCPREQUEST message, 
         the client SHOULD wait one-half of the remaining lease time (in REBINDING state), 
         down to a minimum configured RebindIntervalMin seconds, before retransmitting the DHCPREQUEST message.*/
      if (TcpIp_GetRebindIntervalMinOfDhcpConfig(dhcpConfigIdx) < timeLeft)
      {
        if (timeLeft > ((uint32)TcpIp_GetRebindIntervalMinOfDhcpConfig(dhcpConfigIdx) *2))
        {
          TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, TcpIp_GetSecNextEventOfDhcpStatus(dhcpStatusIdx) + (timeLeft >> 1));/* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
        }
        else
        {
         TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, TcpIp_GetSecNextEventOfDhcpStatus(dhcpStatusIdx) + TcpIp_GetRebindIntervalMinOfDhcpConfig(dhcpConfigIdx));  /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
        }
      }
      else
      {
        TcpIp_SetSecNextEventOfDhcpStatus(dhcpStatusIdx, TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->LeaseTime);  /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      }
    }
    else
    {
      /* TX failed. Stay in current state and retry in next MainFunction cycle */
    }
  }
  else
  {
    /* #40 Lease time has just expired.Change state to OFF. */
    CANOE_WRITE_STRING("TcpIp_DhcpV4_MainFunction: lease time has just expired")
    TcpIp_SetCtrlStateOfDhcpStatus(dhcpStatusIdx, TCPIP_DHCPV4_CTRL_STATE_OFF);                                         /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    TcpIp_SetTimeoutOccurredOfDhcpStatus(dhcpStatusIdx, TRUE);                                                          /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
    /* #50 Indicate to IP-module about loss of IP address. */
    IpV4_Ip_VIpAddrAssignmentReadyNotification(IpV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_DHCP, FALSE);
  }
} /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */
/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VUpdateStatus
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
TCPIP_LOCAL FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_VUpdateStatus(
  TcpIp_SizeOfLocalAddrType                     LocalAddrIdx,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)      ErrorIdPtr,
  CONSTP2VAR(uint8, AUTOMATIC, IPV4_APPL_DATA)  DhcpStatePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  
  /* #10 Verify that DHCP is configured for this IP controller. */
  TcpIp_SizeOfLocalAddrV4Type localAddrV4Idx = TCPIP_LOCAL_ADDR_IDX_TO_IPV4(LocalAddrIdx);
  TcpIp_SizeOfIpV4CtrlType ipV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(localAddrV4Idx);

  *DhcpStatePtr = 0;                                                                                                    /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
  if (localAddrV4Idx == TcpIp_GetLocalAddrV4DhcpIdxOfIpV4Ctrl(ipV4CtrlIdx))
  {
    TcpIp_SizeOfDhcpStatusType dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(ipV4CtrlIdx);
    /* #20 Verify that IP instance is in state ONLINE. */
    if (TcpIp_GetStateOfIpV4CtrlDyn(ipV4CtrlIdx) >= IPV4_IP_ONLINE_PASSIVE)
    {
      retVal = E_OK;
      /* #30 Convert the internal IpV4CtrlIdx-specific status to the simplified status desired by the caller. */
      switch (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx))
      {
      case TCPIP_DHCPV4_CTRL_STATE_OFF:
        /* no break; */
      case TCPIP_DHCPV4_CTRL_STATE_INIT:
        *DhcpStatePtr = TCPIP_DHCP_SIMPLIFIED_STATE_NO_DISCVR_SENT;                                                     /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        break;

      case TCPIP_DHCPV4_CTRL_STATE_SELECTING:
        *DhcpStatePtr = TCPIP_DHCP_SIMPLIFIED_STATE_DISCVR_SENT_NO_ANSWR_RCVD_YET;                                      /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */ 
        break;

      case TCPIP_DHCPV4_CTRL_STATE_REQUESTING:
        *DhcpStatePtr = TCPIP_DHCP_SIMPLIFIED_STATE_REQ_SENT_NO_ACK_RCVD_YET;                                           /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        break;

      case TCPIP_DHCPV4_CTRL_STATE_BOUND: /* Address Lease valid. */
        /* no break; */
      case TCPIP_DHCPV4_CTRL_STATE_RENEWING: /* Address Lease valid. */
        /* no break; */
      case TCPIP_DHCPV4_CTRL_STATE_REBINDING: /* Address Lease valid. */
        *DhcpStatePtr = TCPIP_DHCP_SIMPLIFIED_STATE_ACK_RCVD_DHCP_ADDR_ASSIGND;                                         /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        break;

      case TCPIP_DHCPV4_CTRL_STATE_INITREBOOT: /* mode not supported by this DHCP impl. */
        /* no break; */
      case TCPIP_DHCPV4_CTRL_STATE_REBOOTING: /* mode not supported by this DHCP impl. */
        /* no break; */
      default:
        retVal = E_NOT_OK;
        *ErrorIdPtr = IPV4_E_INV_PARAM;                                                                                 /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
      }
    }
    else
    {
      /* DHCP configured but controller not active, i.e. DHCP client must be inactive for sure. */
      *DhcpStatePtr = TCPIP_DHCP_SIMPLIFIED_STATE_NOT_ACTIVE;                                                           /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
      retVal = E_OK;
    }
  }
  else 
  {
    *ErrorIdPtr = IPV4_E_INV_PARAM;                                                                                     /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
  }
  return retVal;
}
/**********************************************************************************************************************
 *  TcpIp_DhcpV4_GetDhcpMsgLength
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_GetDhcpMsgLength(
  uint8                                     MsgType,
  P2VAR(uint16, AUTOMATIC, TCPIP_APPL_DATA) DhcpMsgLenPtr,
  TcpIp_SizeOfDhcpStatusType                DhcpStatusIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  switch (MsgType)
  {
  case TCPIP_DHCPV4_MSG_DISCOVER:
    if (TcpIp_GetReqIpAddrOfDhcpStatus(DhcpStatusIdx) != IPV4_ADDR_ANY)
    {
      /* option 50, requested IP address option */
      *DhcpMsgLenPtr += TcpIp_DhcpV4_VAddReqIpAddrOption(NULL_PTR, 0); /* get length of requested ip address option */  /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */ /* SBSW_TCPIP_NULL_PTR_ALLOWED */
    }   
    break;

  case TCPIP_DHCPV4_MSG_REQUEST:
    if (   (TcpIp_GetCtrlStateOfDhcpStatus(DhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_SELECTING) /* PRQA S 3415 */ /* MD_TcpIp_12.4_CslReadOnly */
        || (TcpIp_GetCtrlStateOfDhcpStatus(DhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_REQUESTING)
      /*  (TCPIP_DHCPV4_CTRL_STATE_INITREBOOT == TcpIp_GetCtrlStateOfDhcpStatus(DhcpStatusIdx)) */ /* mode not supported */ )
    {
      /* #10 Get Length of requested Ip address option 50.*/ 
      *DhcpMsgLenPtr += TcpIp_DhcpV4_VAddReqIpAddrOption(NULL_PTR, 0);                                                  /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */ /* SBSW_TCPIP_NULL_PTR_ALLOWED */
      /* #20 Get Length of Server identifier option 54. */
      *DhcpMsgLenPtr += TcpIp_DhcpV4_VAddServerIdOption(NULL_PTR, 0);                                                   /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */ /* SBSW_TCPIP_NULL_PTR_ALLOWED */
    }
    else
    {
      /* TCPIP_DHCPV4_CTRL_STATE_BOUND, TCPIP_DHCPV4_CTRL_STATE_RENEWING */ /* TCPIP_DHCPV4_CTRL_STATE_REBINDING */
    } 
    break;

  default:

  break;
  }
}

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VSetMsgFlags
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(void, TCPIP_CODE) TcpIp_DhcpV4_VSetMsgFlags(
  uint8                                     MsgType,
  P2VAR(uint16, AUTOMATIC, TCPIP_APPL_DATA) FlagPtr,
  TcpIp_SizeOfDhcpStatusType                DhcpStatusIdx,
  P2VAR(uint16, AUTOMATIC, TCPIP_APPL_DATA) OptOfsPtr,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA)  OptPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  switch (MsgType)
  {
  case TCPIP_DHCPV4_MSG_DISCOVER:
    *FlagPtr = TCPIP_DHCPV4_FLAGS_BROADCAST;                                                                            /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
    if (TcpIp_GetReqIpAddrOfDhcpStatus(DhcpStatusIdx) != IPV4_ADDR_ANY)
    {
      /* option 50, requested IP address option */
      *OptOfsPtr += TcpIp_DhcpV4_VAddReqIpAddrOption(&OptPtr[*OptOfsPtr], TcpIp_GetReqIpAddrOfDhcpStatus(DhcpStatusIdx));/* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */ /* SBSW_TCPIP_FUNC_CALL_PTR_OPTION */
    }
    break;

  default:  /* TCPIP_DHCPV4_MSG_REQUEST: */
    /* #10 Set the Flag if the message is DHCP request. */
    *FlagPtr = TCPIP_DHCPV4_FLAGS_BROADCAST;                                                                            /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
    if (   (TcpIp_GetCtrlStateOfDhcpStatus(DhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_SELECTING)  /* PRQA S 3415 */ /* MD_TcpIp_12.4_CslReadOnly */
        || (TcpIp_GetCtrlStateOfDhcpStatus(DhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_REQUESTING)
      /*  (TCPIP_DHCPV4_CTRL_STATE_INITREBOOT == TcpIp_DhcpV4_RAM_CtrlState(IpV4CtrlIdx)) */ /* mode not supported */ )
    {
      /* option 50, requested IP address option */
      *OptOfsPtr += TcpIp_DhcpV4_VAddReqIpAddrOption(&OptPtr[*OptOfsPtr], TcpIp_GetAddrDataStructOfDhcpStatus(DhcpStatusIdx)->Ciaddr);   /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */ /* SBSW_TCPIP_FUNC_CALL_PTR_OPTION */
      /* option 54, server identifier option */
      *OptOfsPtr += TcpIp_DhcpV4_VAddServerIdOption(&OptPtr[*OptOfsPtr], TcpIp_GetAddrDataStructOfDhcpStatus(DhcpStatusIdx)->DhcpSiaddr);/* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */ /* SBSW_TCPIP_FUNC_CALL_PTR_OPTION */
    }
    else
    { 
      /* TCPIP_DHCPV4_CTRL_STATE_BOUND, TCPIP_DHCPV4_CTRL_STATE_RENEWING */ /* TCPIP_DHCPV4_CTRL_STATE_REBINDING ?? */
    }
  }
}

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VSendDhcpMsg
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
STATIC FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_VSendDhcpMsg(
  TcpIp_SizeOfIpV4CtrlType IpV4CtrlIdx,
  uint8                    MsgType,
  TcpIp_NetAddrType        DestAddr)
{
  /* ----- Local Variables ---------------------------------------------- */
  TcpIp_LocalAddrV4IterType ipV4AddrIdx;
  uint8                 *bufPtr;
  uint16                bufLenByte;
  uint16                udpLenByte;
  uint16                dhcpMsgLen;
  Std_ReturnType        result;
  TcpIp_IpTxRequestDescriptorType ipTxReqestDescr;
  /* UDP */
  IpBase_SockAddrInType dest;

  /* ----- Implementation ----------------------------------------------- */
  TcpIp_SizeOfDhcpStatusType dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);
  dest.sin_family = IPBASE_AF_INET;
  dest.sin_port   = TCPIP_HTONS(TCPIP_DHCPV4_SERVER_PORT);
  dest.sin_addr   = DestAddr;

  /* #10 Calculate length of DHCP message. */
  dhcpMsgLen = TCPIP_DHCPV4_MIN_HEADER_LENGTH_BYTE + (3 + 1); /* at least the DHCP header + 'message type' option + 'end' option must be sent. */
  dhcpMsgLen += TcpIp_DhcpV4_VAddParamReqListOpt(IpV4CtrlIdx, NULL_PTR); /* get length of parameter request option */   /* SBSW_TCPIP_NULL_PTR_ALLOWED */

  /* #20 Add message specific option lengths. */
  TcpIp_DhcpV4_GetDhcpMsgLength(MsgType, &dhcpMsgLen, dhcpStatusIdx);                                                   /* SBSW_TCPIP_UPDATE_VARIABLE */


  /* #30 Add user options lengths. */
  dhcpMsgLen += TcpIp_DhcpV4_VAddUserOptions(IpV4CtrlIdx, MsgType, NULL_PTR); /* get length of all user options */      /* SBSW_TCPIP_NULL_PTR_ALLOWED */
  udpLenByte = dhcpMsgLen + 8;  /* Add UDP Header length */
  bufLenByte = udpLenByte;
  ipV4AddrIdx = TcpIp_GetLocalAddrV4DhcpIdxOfIpV4Ctrl(IpV4CtrlIdx);
  /* request IP buffer */
  if (IpV4_Ip_ProvideTxBuffer(&ipV4AddrIdx, TcpIp_GetIpV4SocketDynDhcpIdxOfIpV4General(TCPIP_IPV4_GENERAL_IDX), &dest, &bufPtr, &bufLenByte, &ipTxReqestDescr, FALSE)  == BUFREQ_OK) /* SBSW_TCPIP_UPDATE_VARIABLE */
  {
    /* #40 Build UDP Header. */
    uint8  chaddr[16];
    uint16 flags;
    TCPIP_PUT_UINT16(bufPtr, DHCPV4_SRCPORT_OFS, TCPIP_DHCPV4_CLIENT_PORT);                                             /* SBSW_TCPIP_WRITE_UINT */
    TCPIP_PUT_UINT16(bufPtr, DHCPV4_TGTPORT_OFS, TCPIP_DHCPV4_SERVER_PORT);                                             /* SBSW_TCPIP_WRITE_UINT */
    TCPIP_PUT_UINT16(bufPtr, DHCPV4_LEN_BYTE_OFS, udpLenByte);                                                          /* SBSW_TCPIP_WRITE_UINT */
    TCPIP_PUT_UINT16(bufPtr, DHCPV4_CHECKSUM_OFS, 0);                                                                   /* SBSW_TCPIP_WRITE_UINT */
    /* Checksum is calculated by lower layer (IPv4) or in hardware) */
    {
      /* Assemble DHCP message into provided tx buffer */
      bufPtr =  &bufPtr[TCPIP_UDP_HDR_LEN_BYTE];/* Skip the Udp Header */
      TCPIP_PUT_UINT8(bufPtr, TCPIP_DHCPV4_FRAME_OPCODE_OFS, TCPIP_DHCPV4_OP_BOOTREQUEST);                              /* SBSW_TCPIP_WRITE_UINT */
      TCPIP_PUT_UINT8(bufPtr, TCPIP_DHCPV4_FRAME_HWADDR_TYPE_OFS, TCPIP_DHCPV4_HW_TYPE_ETH);                            /* SBSW_TCPIP_WRITE_UINT */
      TCPIP_PUT_UINT8(bufPtr, TCPIP_DHCPV4_FRAME_HWADDR_LEN_OFS, TCPIP_PHYS_ADDR_LEN_BYTE);                             /* SBSW_TCPIP_WRITE_UINT */
      TCPIP_PUT_UINT8(bufPtr, TCPIP_DHCPV4_FRAME_HOPS_OFS, 0);                                                          /* SBSW_TCPIP_WRITE_UINT */

      if (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_INIT)
      {
        /* generate new Session ID */
        uint16 RandNo1 = TcpIp_GetRandomNumber();                                                                       /* SBSW_TCPIP_RANDOM_NUMBER_FUNC */
        uint16 RandNo2 = TcpIp_GetRandomNumber();                                                                       /* SBSW_TCPIP_RANDOM_NUMBER_FUNC */
        TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->Xid = ((uint32)RandNo1) | (((uint32)RandNo2)<<16);          /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
      }

      TCPIP_PUT_UINT32(bufPtr, TCPIP_DHCPV4_FRAME_XID_OFS, TCPIP_HTONL(TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->Xid));/* SBSW_TCPIP_WRITE_UINT */
      TCPIP_PUT_UINT16(bufPtr, TCPIP_DHCPV4_FRAME_SECS_OFS, TcpIp_GetSecElapsedOfDhcpStatus(dhcpStatusIdx));            /* SBSW_TCPIP_WRITE_UINT */
      TCPIP_PUT_UINT16(bufPtr, TCPIP_DHCPV4_FRAME_FLAGS_OFS, 0);/* message specific flags will be set below */          /* SBSW_TCPIP_WRITE_UINT */
      flags = 0;

      if (   (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_BOUND)  /* PRQA S 3415 */ /* MD_TcpIp_12.4_CslReadOnly */
          || (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_RENEWING)
          || (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) == TCPIP_DHCPV4_CTRL_STATE_REBINDING))
      {
        TCPIP_PUT_UINT32(bufPtr, TCPIP_DHCPV4_FRAME_CIADDR_OFS, TCPIP_HTONL(TcpIp_GetAddrDataStructOfDhcpStatus(dhcpStatusIdx)->Ciaddr));  /* SBSW_TCPIP_WRITE_UINT */
        /* set client address */
      }
      else
      { /* msg DICOVER, and msg REQUEST in state SELECTING */
        TCPIP_PUT_UINT32(bufPtr, TCPIP_DHCPV4_FRAME_CIADDR_OFS, 0);                                                     /* SBSW_TCPIP_WRITE_UINT */
      }
      TCPIP_PUT_UINT32(bufPtr, TCPIP_DHCPV4_FRAME_YIADDR_OFS, 0);                                                       /* SBSW_TCPIP_WRITE_UINT */
      TCPIP_PUT_UINT32(bufPtr, TCPIP_DHCPV4_FRAME_SIADDR_OFS, 0);                                                       /* SBSW_TCPIP_WRITE_UINT */
      TCPIP_PUT_UINT32(bufPtr, TCPIP_DHCPV4_FRAME_GIADDR_OFS, 0);                                                       /* SBSW_TCPIP_WRITE_UINT */

      TCPIP_LL_GetPhysAddr(0, &chaddr[0]); /* add mac address to first 6 bytes of 16 byte hardware address field */     /* SBSW_TCPIP_DHCPV4_FUNC_CALL_PTR_PASSING_CALLER */
      IpBase_Fill(&chaddr[IPBASE_ETH_PHYS_ADDR_LEN_BYTE], 0, sizeof(chaddr) - IPBASE_ETH_PHYS_ADDR_LEN_BYTE); /* fill with 10 byte padding (zeroes) */         /* SBSW_TCPIP_IPBASE_COPY_CALLEE */
      
      IpBase_Copy(&bufPtr[TCPIP_DHCPV4_FRAME_CLIENT_HW_ADDR_OFS], &chaddr[0], TCPIP_DHCPV4_MSG_LEN_CHADDR);             /* SBSW_TCPIP_IPBASE_COPY_CALLEE */
       /* clear 'server name' field */
      IpBase_Fill(&bufPtr[TCPIP_DHCPV4_FRAME_SERVER_HOSTNAME_OFS], 0, TCPIP_DHCPV4_MSG_LEN_SNAME);                      /* SBSW_TCPIP_IPBASE_COPY_CALLEE */
      /* clear 'boot file' field */  
      IpBase_Fill(&bufPtr[TCPIP_DHCPV4_FRAME_BOOT_FILE_OFS], 0, TCPIP_DHCPV4_MSG_LEN_BOOTFILE);                         /* SBSW_TCPIP_IPBASE_COPY_CALLEE */

      TCPIP_PUT_UINT32(bufPtr, TCPIP_DHCPV4_FRAME_MAGICPATTERN_OFS, TCPIP_DHCPV4_MAGIC_PATTERN);                        /* SBSW_TCPIP_WRITE_UINT */
      /* Append DHCP options */
      {
        uint8  optLen;
        uint8 *optPtr = &(bufPtr)[TCPIP_DHCPV4_MIN_HEADER_LENGTH_BYTE];
        uint16 optOfs = 0;
        TcpIp_SizeOfIpV4SocketDynType        ipV4SocketDhcpIdx    = TcpIp_GetIpV4SocketDynDhcpIdxOfIpV4General(TCPIP_IPV4_GENERAL_IDX);
        TCPIP_P2V(IpV4_Ip_TransferBlockType) ipV4TransferBlockPtr = TcpIp_GetAddrTransferBlockOfIpV4SocketDyn(ipV4SocketDhcpIdx);

        /* option 53, DHCP message type option */
        optLen                                            = TCPIP_DHCPV4_OPT_DHCPV4_MSG_LEN + 2;
        optPtr[optOfs+TCPIP_DHCPV4_OPTION_FIELD_OFS_CODE] = TCPIP_DHCPV4_OPT_DHCPV4_MSG_TYPE;                           /* SBSW_TCPIP_LOCAL_PTR_UPDATE */
        optPtr[optOfs+TCPIP_DHCPV4_OPTION_FIELD_OFS_LEN]  = TCPIP_DHCPV4_OPT_DHCPV4_MSG_LEN;                            /* SBSW_TCPIP_LOCAL_PTR_UPDATE */
        optPtr[optOfs+TCPIP_DHCPV4_OPTION_FIELD_OFS_TYPE] = MsgType;                                                    /* SBSW_TCPIP_LOCAL_PTR_UPDATE */
        optOfs           += optLen; /* Set Option pointer offset to the next option. */

        optOfs += TcpIp_DhcpV4_VAddParamReqListOpt(IpV4CtrlIdx, &optPtr[optOfs]);                                       /* SBSW_TCPIP_FUNC_CALL_LOCAL_PTR_OPTION */
        /* set message specific flags and options */
        TcpIp_DhcpV4_VSetMsgFlags(MsgType, &flags, dhcpStatusIdx, &optOfs, optPtr);                                     /* SBSW_TCPIP_FUNC_CALL_LOCAL_PTR_OPTION */ /* SBSW_TCPIP_UPDATE_VARIABLE */
        TCPIP_PUT_UINT16(bufPtr, TCPIP_DHCPV4_FRAME_FLAGS_OFS, flags);                                                  /* SBSW_TCPIP_WRITE_UINT */
        
        if (((flags & (TCPIP_DHCPV4_FLAGS_BROADCAST)) != 0) && (TcpIp_GetCtrlStateOfDhcpStatus(dhcpStatusIdx) < TCPIP_DHCPV4_CTRL_STATE_BOUND)) /* PRQA S 3415 */ /* MD_TcpIp_12.4_CslReadOnly */
        {
          /* DHCP messages broadcast by a client prior to that client obtaining
             its IP address must have the source address field in the IP header
             set to 0. [RFC2131 4.1 Constructing and sending DHCP messages] */
          IPV4_SET_FLAG_U8(ipV4TransferBlockPtr->Flags, IPV4_IP_TRANSFER_BLOCK_FLAG_ZERO_SRC_ADDR);                     /* SBSW_TCPIP_LOCAL_PTR_UPDATE */
        }
        else
        {
          IPV4_CLR_FLAG_U8(ipV4TransferBlockPtr->Flags, IPV4_IP_TRANSFER_BLOCK_FLAG_ZERO_SRC_ADDR);                     /* SBSW_TCPIP_LOCAL_PTR_UPDATE */
        }
        /* add user options */
        optOfs += TcpIp_DhcpV4_VAddUserOptions(IpV4CtrlIdx, MsgType, &optPtr[optOfs]);                                  /* SBSW_TCPIP_FUNC_CALL_LOCAL_PTR_OPTION */
        /* option 255, end option */
        optPtr[optOfs]  = TCPIP_DHCPV4_OPT_END_TYPE;                                                                    /* SBSW_TCPIP_LOCAL_PTR_UPDATE */
        optOfs++;

#if ( TCPIP_DEV_ERROR_REPORT == STD_ON )
        /* Check that created message is as long as calculated at beginning of this function */
        if ((TCPIP_DHCPV4_MIN_HEADER_LENGTH_BYTE + optOfs) != dhcpMsgLen)
        {
          TcpIp_CallDetReportError(TCPIP_DHCPV4_API_ID_V_SEND_DHCP_MSG, TCPIP_E_INV_ARG);
        }
#endif
      }
    }
    /* send data */
    if (TCPIP_OK == IpV4_Ip_Transmit(&ipTxReqestDescr, udpLenByte, TCPIP_PROTOCOL_UDP, FALSE, 0, FALSE))                /* SBSW_TCPIP_UPDATE_VARIABLE */
    {
      CANOE_WRITE_STRING_1("TcpIp_DhcpV4_VSendDhcpMsg: DHCP message sent with %d byte", udpLenByte);
      result = E_OK;
    }
    else
    {
      result = E_NOT_OK;
      /* if TcpIp_ProvideTxBuffer(), TcpIp_TransmitTo() may not fail */
    }
  }
  else
  {
    result = E_NOT_OK;
  }
  return result;
}  /* PRQA S 2006, 6010, 6030, 6050 */ /* MD_MSR_14.7, MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */
/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VGetTxOption
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_VGetTxOption(
    TcpIp_LocalAddrV4IterType                LocalAddrV4Idx,
    uint8                                    OptId,
    P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) OptLenPtr,
    P2VAR(uint8, AUTOMATIC, TCPIP_APPL_DATA) OptPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  TcpIp_SizeOfIpV4CtrlType ipV4CtrlIdx;

  /* ----- Implementation ----------------------------------------------- */
  TCPIP_ASSERT(LocalAddrV4Idx < TcpIp_GetSizeOfLocalAddrV4());
  ipV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(LocalAddrV4Idx);

  if (TcpIp_GetLocalAddrV4DhcpIdxOfIpV4Ctrl(ipV4CtrlIdx) == LocalAddrV4Idx)
  {
    TcpIp_SizeOfDhcpStatusType dhcpStatusIdx;
    TcpIp_SizeOfDhcpHostnameType dhcpHostNameIndex;

    TCPIP_ASSERT(IpV4_Ip_VCfgGetAddrAssignmentPrio(ipV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_DHCP) != 0);
    
    dhcpHostNameIndex = TcpIp_GetDhcpHostnameStartIdxOfIpV4Ctrl(ipV4CtrlIdx);
    dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(ipV4CtrlIdx);
    
    /* currently only one single option (FQDN-Option) is supported */
    if (OptId == TCPIP_DHCPV4_OPT_ID_CLIENT_FQDN)
    {
      if (*OptLenPtr >= TcpIp_GetHostNameLenOfDhcpStatus(dhcpStatusIdx))
      {
        /* #10 Copy length and host name. */
        *OptLenPtr = TcpIp_GetHostNameLenOfDhcpStatus(dhcpStatusIdx);                                                   /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
        if (*OptLenPtr > 0)
        {
          IpBase_Copy((IpBase_CopyDataType*)OptPtr, (const IpBase_CopyDataType*)TcpIp_GetAddrDhcpHostname(dhcpHostNameIndex), *OptLenPtr); /* SBSW_TCPIP_FUNC_CALL_IpBase_Copy */
        }
        retVal = E_OK;
      }
    }
  }
  return retVal;
} /* End of TcpIp_DhcpV4_VGetTxOption() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VSetTxOption
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_VSetTxOption(
  TcpIp_LocalAddrV4IterType                  LocalAddrV4Idx,
  uint8                                      OptId,
  uint8                                      OptLen,
  P2CONST(uint8, AUTOMATIC, TCPIP_APPL_DATA) OptPtr,
  uint8                                      MsgTypes)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  TcpIp_SizeOfIpV4CtrlType ipV4CtrlIdx; 
  /* ----- Implementation ----------------------------------------------- */
  /* Currently the implementation is limited to one option that is always sent, but the API is already prepared to do a more generic handling */
  IPV4_UNUSED_PARAMETER(MsgTypes);  /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */
  TCPIP_ASSERT(LocalAddrV4Idx < TcpIp_GetSizeOfLocalAddrV4());

  ipV4CtrlIdx = TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(LocalAddrV4Idx);

  if (TcpIp_GetLocalAddrV4DhcpIdxOfIpV4Ctrl(ipV4CtrlIdx) == LocalAddrV4Idx)
  {
    TcpIp_SizeOfDhcpStatusType dhcpStatusIdx;
    TcpIp_SizeOfDhcpConfigType dhcpConfigIdx;
    TcpIp_SizeOfDhcpHostnameType dhcpHostNameIndex;

    TCPIP_ASSERT(IpV4_Ip_VCfgGetAddrAssignmentPrio(ipV4CtrlIdx, TCPIP_IPADDR_ASSIGNMENT_DHCP) != 0);

    dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(ipV4CtrlIdx);
    dhcpConfigIdx = TcpIp_GetDhcpConfigIdxOfIpV4Ctrl(ipV4CtrlIdx);
    dhcpHostNameIndex = TcpIp_GetDhcpHostnameStartIdxOfIpV4Ctrl(ipV4CtrlIdx);

    /* currently only one single option is supported */
    if (OptId == TCPIP_DHCPV4_OPT_ID_CLIENT_FQDN)
    {
      /* An old API for setting a host name was TcpIp_DhcpV4_SetHostName(). */
      /* #10 Verify Host name length. */
      if (OptLen <= TcpIp_GetHostNameLenMaxOfDhcpConfig(dhcpConfigIdx))
      {
        /* #20 Copy length and host name. */
        TcpIp_SetHostNameLenOfDhcpStatus(dhcpStatusIdx, OptLen);                                                        /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
        IpBase_Copy(TcpIp_GetAddrDhcpHostname(dhcpHostNameIndex), (const IpBase_CopyDataType*)OptPtr, OptLen);          /* SBSW_TCPIP_DHCPV4_FUNC_CALL_PTR_PASSING_CALLER */ /* SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER */
        retVal = E_OK;
      }
    }
  }
  return retVal;
} /* End of TcpIp_DhcpV4_VSetTxOption() */  /* PRQA S 6050 */ /* MD_TcpIp_STCAL_CslAccess */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VAddUserOptions
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */

STATIC FUNC(uint16, TCPIP_CODE) TcpIp_DhcpV4_VAddUserOptions(
    TcpIp_SizeOfIpV4CtrlType                IpV4CtrlIdx,
    uint8                                   MsgType,
    P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) MsgDataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 msgDataOfs = 0;
  TcpIp_SizeOfDhcpStatusType dhcpStatusIdx;


  /* Currently the implementation is limited to one option that is always sent, but the API is already prepared to do a more generic handling */
  IPV4_UNUSED_PARAMETER(MsgType);  /* PRQA S 3112 */ /* MD_MSR_14.2 */
  dhcpStatusIdx = TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(IpV4CtrlIdx);

  /* currently only one single option (FQDN-Option) is supported, and this option is sent in all DHCP messages */
  if (TcpIp_GetHostNameLenOfDhcpStatus(dhcpStatusIdx) > 0)
  {
    if (MsgDataPtr != NULL_PTR)
    {
      TcpIp_SizeOfDhcpHostnameType dhcpHostNameIndex = TcpIp_GetDhcpHostnameStartIdxOfIpV4Ctrl(IpV4CtrlIdx);

      /* #10 Copy the option to the buffer. */
      MsgDataPtr[TCPIP_DHCPV4_OPT_FQDN_CODE] = TCPIP_DHCPV4_OPT_ID_CLIENT_FQDN;  /* option id */                        /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
      MsgDataPtr[TCPIP_DHCPV4_OPT_FQDN_LEN]  = TcpIp_GetHostNameLenOfDhcpStatus(dhcpStatusIdx) +3;  /* option length */ /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
      /* IPv4
          0 1 2 3 4 5 6 7(LSB)
         +-+-+-+-+-+-+-+-+
         |  MBZ  |N|E|O|S|
         +-+-+-+-+-+-+-+-+
         S = 0   the server SHOULD NOT perform the A RR (FQDN-to-address) DNS updates (LSB)
         O = 0   must be 0
         E = 1   canonical wire format
         N = 1   the server SHOULD NOT perform any DNS updates
      */
      MsgDataPtr[TCPIP_DHCPV4_OPT_FQDN_FLAGS] = 0x0C;  /* set flags N and E */                                          /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
      MsgDataPtr[TCPIP_DHCPV4_OPT_FQDN_RCODE1] = 0;     /* RCODE1, is always 0 */                                       /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
      MsgDataPtr[TCPIP_DHCPV4_OPT_FQDN_RCODE2] = 0;     /* RCODE2, is always 0 */                                       /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
      IpBase_Copy((IpBase_CopyDataType*)&MsgDataPtr[TCPIP_DHCPV4_OPT_FQDN_DOMAIN_NAME],                                 /* SBSW_TCPIP_DHCPV4_FUNC_CALL_PTR_PASSING_CALLER */
                  (const IpBase_CopyDataType*)TcpIp_GetAddrDhcpHostname(dhcpHostNameIndex), 
                  TcpIp_GetHostNameLenOfDhcpStatus(dhcpStatusIdx));  /* option data */                                  
    }
    /* #20 Update the total length of the user options. */
    msgDataOfs += TCPIP_DHCPV4_OPT_FQDN_DOMAIN_NAME + TcpIp_GetHostNameLenOfDhcpStatus(dhcpStatusIdx);  /* increase the offset */
  }
  return msgDataOfs;
} /* End of TcpIp_DhcpV4_VAddUserOptions() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VAddReqIpAddrOption
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
STATIC FUNC(uint8, TCPIP_CODE) TcpIp_DhcpV4_VAddReqIpAddrOption(
    P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) OptPtr,
    IpBase_AddrInType                       Yiaddr)
{
  /* ----- Implementation ----------------------------------------------- */
  if (OptPtr != NULL_PTR)
  { /* #10 Write your Ip address(Client address) to update option pointer. */
    OptPtr[TCPIP_DHCPV4_OPTION_FIELD_OFS_CODE] = TCPIP_DHCPV4_OPT_REQ_IP_ADDR_TYPE;                                                                      /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
    OptPtr[TCPIP_DHCPV4_OPTION_FIELD_OFS_LEN]  = TCPIP_DHCPV4_OPT_REQ_IP_ADDR_LEN;                                                                       /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */

    Yiaddr = TCPIP_HTONL(Yiaddr);
    TCPIP_PUT_UINT32(OptPtr,2, Yiaddr);                                                                                 /* SBSW_TCPIP_WRITE_UINT */
  }

  return (2 + TCPIP_DHCPV4_OPT_REQ_IP_ADDR_LEN);
} /* End of TcpIp_DhcpV4_VAddReqIpAddrOption() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VAddServerIdOption
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */

STATIC FUNC(uint8, TCPIP_CODE) TcpIp_DhcpV4_VAddServerIdOption(
    P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) OptPtr,
    IpBase_AddrInType                       Siaddr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Verify if Option pointer is valid. */
  if (OptPtr != NULL_PTR)
  { /* #20 Update Option Pointer with server Id information. */
    OptPtr[TCPIP_DHCPV4_OPTION_FIELD_OFS_CODE] = TCPIP_DHCPV4_OPT_SERVER_ID_TYPE;                                                                        /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
    OptPtr[TCPIP_DHCPV4_OPTION_FIELD_OFS_LEN]  = TCPIP_DHCPV4_OPT_SERVER_ID_LEN;                                                                         /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
    Siaddr = TCPIP_HTONL(Siaddr);
    TCPIP_PUT_UINT32(OptPtr,2, Siaddr);                                                                                 /* SBSW_TCPIP_WRITE_UINT */
  }

  return (2 + TCPIP_DHCPV4_OPT_SERVER_ID_LEN);
} /* End of TcpIp_DhcpV4_VAddServerIdOption() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_VAddParamReqListOpt
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */

STATIC FUNC(uint8, TCPIP_CODE) TcpIp_DhcpV4_VAddParamReqListOpt(
  uint8                                   IpV4CtrlIdx,
  P2VAR(uint8, AUTOMATIC, TCPIP_APPL_VAR) OptPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  uint8 OptLen = TCPIP_DHCPV4_PARAM_SUBNET_ROUTER_DOMAIN_BYTE;
 /* #10 Verify if Option pointer is valid. */
  if (OptPtr != NULL_PTR)
  { /* #20 Update Option pointer with Parameter Request List Option informations. */
    OptPtr[TCPIP_DHCPV4_OPTION_FIELD_OFS_CODE]   = TCPIP_DHCPV4_OPT_PARAM_REQ_LIST_TYPE;                                /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
    OptPtr[TCPIP_DHCPV4_OPTION_FIELD_OFS_LEN]    = OptLen; /* Update Option length */                                   /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
    OptPtr[TCPIP_DHCPV4_OPTION_FIELD_OFS_TYPE]   = TCPIP_DHCPV4_OPT_SUBNET_MASK_TYPE;                                   /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
    OptPtr[TCPIP_DHCPV4_OPTION_FIELD_OFS_TYPE+1] = TCPIP_DHCPV4_OPT_ROUTER_TYPE;                                        /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
    OptPtr[TCPIP_DHCPV4_OPTION_FIELD_OFS_TYPE+2] = TCPIP_DHCPV4_OPT_DOMAIN_NAME_SERVER_TYPE;                            /* SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER */
  }

  IPV4_UNUSED_PARAMETER(IpV4CtrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  return (TCPIP_DHCPV4_OPTION_HDR_BYTE + OptLen);
} /* end of TcpIp_DhcpV4_VAddParamReqListOpt() */

/**********************************************************************************************************************
 *  TcpIp_DhcpV4_GetStatus
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_DhcpV4_GetStatus(
    TcpIp_LocalAddrIdType                        LocalAddrId,
    CONSTP2VAR(uint8, AUTOMATIC, IPV4_APPL_DATA) DhcpStatePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType          retVal = E_NOT_OK;
  uint8                   errorId = TCPIP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (TCPIP_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_TCPIP_DEV_ERROR_DETECT */
  /* #10 Verify that IpV4 is initialized. */
  if (IpV4_State != IPV4_STATE_INIT)
  {
    errorId = IPV4_E_NOT_INITIALIZED;
  }
  /* #20 Verify that DhcpStatePtr is a valid pointer. */
  else if (DhcpStatePtr == NULL_PTR)
  {
    errorId = IPV4_E_INV_POINTER;
  }
  /* #30 Verify if LocalAddrId is a valid parameter. */
  else if (!TCPIP_LOCAL_ADDR_ID_IS_VALID(LocalAddrId))
  {
    errorId = IPV4_E_INV_PARAM;
  }
  else
#endif
  {
    TcpIp_SizeOfLocalAddrType localAddrIdx = TCPIP_LOCAL_ADDR_ID_TO_IDX(LocalAddrId);

#if (TCPIP_SUPPORT_IPV6 == STD_ON)                                                                                      /* COV_MSR_UNSUPPORTED */
    if (!TCPIP_LOCAL_ADDR_IDX_IS_IPV4(localAddrIdx)) 
    {
      errorId = IPV4_E_INV_PARAM;
    }
    /* ----- Implementation ----------------------------------------------- */
    else
#endif
    { 
      /* #40 If all Parameters are valid, Call the function to update the status. */
      retVal = TcpIp_DhcpV4_VUpdateStatus( localAddrIdx, &errorId, DhcpStatePtr);                                       /* SBSW_TCPIP_UPDATE_VARIABLE */ /* SBSW_TCPIP_DHCPV4_FUNC_CALL_PTR_PASSING_CALLER */
    }
  } /* else: DHCP not configured, i.e. invalid condition to call this API: Leave retVal E_NOT_OK */

  /* ----- Development Error Report --------------------------------------- */
#if (TCPIP_DEV_ERROR_REPORT == STD_ON)
  if (errorId != TCPIP_E_NO_ERROR) 
  {  
    (void)Det_ReportError(IPV4_MODULE_ID, IPV4_VINSTANCE_ID, TCPIP_DHCPV4_API_ID_GET_STATUS, errorId);
  }
#endif
  return retVal;
}

#define TCPIP_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*
   MICROSAR global MISRA deviations:
   - see file 'WI_MISRA_Compliance_MSR.pdf'

   Justification for module-specific MISRA deviations:

   module global deviations -> see file TcpIp.c
   
   DHCP-specific deviations:
   MD_TCPIP_DHCPV4_14.6_0771_a:
     Reason:     The break statement is used multiple (two) times because parsing a received DHCP message can have
                 multiple fail conditions that should cause stops.
                 Using breaks makes the code much easier to unterstand.
     Risk:       Unstructured code should be avoided.
     Prevention: Covered by code review.

   MD_TCPIP_DHCPV4_14.5_0770: A continue statement has been used.
     Reason:     Avoiding continue statement here would decrease the code readability.
     Risk:       None.
     Prevention: Covered by code review.

   MD_TCPIP_DHCPV4_21.1_3382_a: Unsigned arithmetic apparently results in wraparound past zero.
     Reason:     The DataLength is always bigger than or equal to TCPIP_UDP_HDR_LEN_BYTE.
                 It is assured by the function TcpIp_DhcpV4_VDataLengthAndPortCheck that the calculated DataLen will never be
                 negative.
     Risk:       The calculation udpHdrLen - TCPIP_UDP_HDR_LEN_BYTE would produce a negative result if udpHdrLen is
                 smaller than TCPIP_UDP_HDR_LEN_BYTE.
     Prevention: Covered by code review.

*/

/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_TCPIP_DHCP_OPTIONS_OFFSET
    \DESCRIPTION        Dhcp Options are divided in 3 parts: Code,Length of Data and Data. 
                                Code |  Len|    Data               |
                               +-----+-----+-----+-----+-----+-----+
                               |  1  |  4  |  m1 |  m2 |  m3 |  m4 |
                               +-----+-----+-----+-----+-----+-----+
                        optPtr is set to the first byte of Dhcp options,i.e. Code. Once the optPtr is set it is used as optPtr[0] = Code, optPtr[1] = Len,
                        optPtr[3] = first byte of Data.
                        Option length is calculated  as optLen = TCPIP_DHCPV4_OPTION_HDR_BYTE + optPtr[1] 
                        i.e. first 2 bytes(code + len) + the value stored at 2nd byte (OptPtr[1]).
                        According to the calculated Optlen code, Length and following data bytes are valid to write (Value stored at Len field =  number of bytes are written into the optPtr at the position of optOfs follwing Len field).
                        Exactly that many number of bytes are written into the memory location reserved for dhcp options Data. Caller or Callee ensures that.
                        Ex. In above diagrame value stored at position Len is 4. That's why next 4 bytes of memory location after Len field is valid and can be written. 
                        Thats why it is always a valid optOfs.
    \COUNTERMEASURE \N  OptPtr must set properly as described above. Local function or Caller must ensure that it is a valid pointer and points to the right memory location.

  \ID SBSW_TCPIP_DHCP_VSendDhcpMsg
    \DESCRIPTION        TcpIp_DhcpV4_VAddUserOptions and TcpIp_DhcpV4_VAddParamReqListOpt functions are called two times inside the VSendDhcpMsg
                        1. To calculate the option length.
                        2. To update the buffer.
                        After the first call the buffer and calculated option length + Udp Header length, first passed to the function IpV4_Ip_ProvideTxBuffer().
                        If this function retuns BUFREQ_OK then only the buffer will be updated othewise not.
    \COUNTERMEASURE \N  Validity of the parameters are ensured by the caller.

  \ID SBSW_TCPIP_FUNC_CALL_LOCAL_PTR_OPTION
    \DESCRIPTION        A Pointer is passed to the function as function argument
                        Local pointer is created inside this function and ensured that the pointer is valid and points to the valid memory location as described in 
                        SBSW_TCPIP_DHCP_OPTIONS_OFFSET and SBSW_TCPIP_DHCP_VSendDhcpMsg.
    \COUNTERMEASURE \N  Validity of the pointer is ensured by the caller.

  \ID SBSW_TCPIP_FUNC_CALL_PTR_OPTION
    \DESCRIPTION        A Pointer is passed to the function as function argument
                        A function argument pointer is passed to this callee. Validity of this pointer is ensured by the caller as described in 
                        SBSW_TCPIP_DHCP_OPTIONS_OFFSET
    \COUNTERMEASURE \N  The callee ensures that the pointer parameter is not NULL_PTR and points to a valid memory location.

  \ID SBSW_TCPIP_FUNC_CALL_IpBase_Copy
    \DESCRIPTION        A Pointer is passed to the function as function argument
                        A function argument pointer is passed to this callee. Validity of this pointer is ensured by the caller.
                        OptLenPtr is set to the HostNameLenOfDhcpStatus using csl macro before passing it to the function to make sure that only that much of bytes are copied.
    \COUNTERMEASURE \N  The caller ensures that the pointer parameter are valid.

  \ID SBSW_TCPIP_DHCPSTATUS_DHCPCONFIG_IDX_INDIRECTION_CONSTRAINT
    \DESCRIPTION        Index  derivation to access DhcpConfig or DhcpStatus elements.
                        Validity of the index value(s) of the modelled indirection(s) [is|are] checked using one of the following functions:
                        1. TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(IpV4CtrlIdx)
                        2. TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(IpV4CtrlIdx)
                        If one of these checks indicates a valid indirection, both indirections can be used to access the corresponding arrays.
                        Both functions will always return the identical result. Thats why any of the above mentioned check is enough in order to access the DhcpConfig or DhcpStatus elements.
    \COUNTERMEASURE \N  Index is obtained by indirection (qualified use-case CSL03 of ComStackLib) and presence of one of the mentioned checks or corresponding CONSTRAINT at function declaration.
                    \M  CM_TCPIP_DHCPV4_CONFIG_AND_STATUS

  \ID SBSW_TCPIP_DHCPV4_CSL03_IDX_BASED_ON_CALLER
    \DESCRIPTION        A CSL modelled RAM array is written using an index that is determined using one (or more) modelled indirections according to CSL03.
                        The first index for the lookup(s) is provided and checked by the caller of the function to be within the valid range by using the associated TcpIp_GetSizeOf...() function.
                        Validity of the index value(s) of the modelled indirection(s) [is|are] checked according to SBSW_TCPIP_DHCPSTATUS_DHCPCONFIG_IDX_INDIRECTION_CONSTRAINT by the caller.
    \COUNTERMEASURE \N  Index is obtained by indirection (qualified use-case CSL03 of ComStackLib) of function
                        argument. The valid range of the function argument is defined at the function declaration and
                        has to be ensured by the calling function.

  \ID SBSW_TCPIP_CSL03_IDX_CALLEE
    \DESCRIPTION        A CSL modelled RAM array is written using an index that is determined using one (or more) modelled indirections according to CSL03.
                        The first index for the lookup(s) is created locally and checked inside the local function to be within the valid range by using the associated TcpIp_GetSizeOf...() function.
                        Validity of the index value(s) of the modelled indirection(s) [is|are] checked according to SBSW_TCPIP_DHCPSTATUS_DHCPCONFIG_IDX_INDIRECTION_CONSTRAINT.
                        Memory location accessed using this valid index is always valid
    \COUNTERMEASURE \N  Index is obtained by indirection (qualified use-case CSL03 of ComStackLib) of a local variable. 

  \ID SBSW_TCPIP_FUNC_PTR_CALL
    \DESCRIPTION        Optional function pointer is used in order to notify customer function.
    \COUNTERMEASURE \R  The optional function pointer is checked against NULL_PTR within local function and handled properly.

  \ID SBSW_TCPIP_DHCPV4_FUNC_PARAM_PTR_CALLER
    \DESCRIPTION        Pointer is updated inside the local function without validity check.
                        In case of optPtr and offset, Update is carried out as explained in SBSW_TCPIP_DHCP_OPTIONS_OFFSET
    \COUNTERMEASURE \N  Pointer is passed as a function argument and is updated considering a valid pointer.
                        The validity of the pointer is ensured by the caller.

 \ID SBSW_TCPIP_FUNC_PARAM_PTR_CALLEE
    \DESCRIPTION        Pointer is updated inside the local function without validity check.
    \COUNTERMEASURE \N  Pointer is passed as a function argument to update it.
                        The validity of the pointer is ensured by the callee. Pointer parameter is checked against NULL_PTR within callee function and handled properly.

  \ID SBSW_TCPIP_DHCPV4_FUNC_CALL_PTR_PASSING_CALLER
    \DESCRIPTION        Pointer is passed as a function argument in order to update it.
                        Pointer is a function argument  and passed to the callee function considering a valid pointer.
    \COUNTERMEASURE \N  The validity of the pointer is ensured by the caller.

  \ID SBSW_TCPIP_WRITE_DHCPHOSTNAME
    \DESCRIPTION         A CSL modelled RAM array is written using an index that is determind as described below:
                         DataLen is checked against the maximum allowed length for the dhcp hostname.
                         hostnameByteOfs is set to the start index of the hostname using TcpIp_GetDhcpHostnameStartIdxOfIpV4Ctrl(IpV4CtrlIdx) csl macro.
                         dataIdx is iterated over for loop until (DataLen - 1). So the Index is (hostnameByteOfs + dataIdx). Thats why it is secured to write at the memory location using calculated index.
    \COUNTERMEASURE \R  Validity of the index is ensured by the local function.

  \ID SBSW_TCPIP_LOCAL_PTR_UPDATE
    \DESCRIPTION        Pointer is updated inside the local function.
                        As explained in SBSW_TCPIP_DHCP_OPTIONS_OFFSET optPtr is set at the beginning of options and only 
                        that much of bytes are written into the optPtr at accordingly incremented offset as given in Length field of option format.
    \COUNTERMEASURE \N  A Local pointer is created inside a local function.

  \ID SBSW_TCPIP_WRITE_UINT
    \DESCRIPTION       The function writes 1/2/4 bytes beginning at the position in the buffer provided by the caller as stated in SBSW_IpV4_Ip_ProvideTxBuffer.
                       TcpIp_WriteUInt8(): 1
                       TcpIp_WriteUInt16(): 2
                       TcpIp_WriteUInt32(): 4
    \COUNTERMEASURE \N The caller ensures that there are 1/2/4 bytes available at &BufPtr[BufPos].

  \ID SBSW_TCPIP_IPBASE_COPY_CALLEE
    \DESCRIPTION        Array is passed to the function as argument to update it.
    \COUNTERMEASURE \N  The caller ensures that the Proper size of array is created and points to the valid memory location.
                        The size of array is passed to the callee function in order to make sure that the array is updated  only for the given size as stated in 
                        SBSW_IpV4_Ip_ProvideTxBuffer.

  \ID SBSW_IpV4_Ip_ProvideTxBuffer
    \DESCRIPTION        A local pointer is created inside the caller function and passed to TCPIP_LL_ProvideTxBuffer function in order to validate it.
                        If TCPIP_LL_ProvideTxBuffer function retuns BUFREQ_OK  and if bufLenByte is valid (means buffer pointer is valid) then only it is updated.

  \ID SBSW_TCPIP_DHCPV4_FUNC_CALL_WRITE_ACCESS_ARRAY_PHYSADDR
    \DESCRIPTION        Array is passed as a parameter to the function.
                        Local array  of TCPIP_PHYS_ADDR_LEN_BYTE length is created inside the caller function.
                        The validity of the parameter is ensured by the caller.
    \COUNTERMEASURE \N  Validity is ensured by the caller

   SBSW_JUSTIFICATION_END */

/************************************************************************************************************
*  MSSV Checks
***********************************************************************************************************/
/* \CM CM_TCPIP_DHCPV4_CONFIG_AND_STATUS                 Each IPv4Ctrl which references a valid DhcpConfig, must reference a valid DhcpStatus and vice versa. */


/************************************************************************************************************
*  Runtime Checks
***********************************************************************************************************/
/*  \CM CM_TCPIP_DHCPV4_OPT_BUF_VALID_ACCESS
        Functions used for serialization of Dhcp options are called two times orderly with different buffer pointer values.
        1. In the first call, the buffer pointer is passed to the function as NULL_PTR. In this case, the function returns the calculated option Length.
        2. In the second call, the implementation passes a valid non NULL_PTR pointer. In this case, the function updates the buffer (of a size calculated in 1st step).
        The implementation ensures that the buffer used in the second call corresponds to the length calculated in the fist call.
        This ensures that the buffer is accessed and updated only within a valid range. */

#endif  /* (TCPIP_SUPPORT_IPV4 == STD_ON) && (TCPIP_SUPPORT_DHCPV4 == STD_ON) */
/**********************************************************************************************************************
 *  END OF FILE: TcpIp_DhcpV4.c
 *********************************************************************************************************************/
