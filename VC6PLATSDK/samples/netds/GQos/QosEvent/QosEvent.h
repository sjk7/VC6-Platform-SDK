// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1998 - 2000  Microsoft Corporation.  All Rights Reserved.
//
// Module:
//      qosevent.h
//
// Abstract:
//      Definitions and prototypes specific to this application
//
// Author:
//      Barry R. Butterklee
//

#ifndef QOSEVENT_H
#define QOSEVENT_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <qos.h>
#include <qossp.h>
#include <stdio.h>
#include <stdlib.h> 


#define MY_DEFPORT (5001)



// Application specific define - there is NO specific invalid send priority.
// This value is simply used to indicate whether or not to even set priority.
#define INVALID_SEND_PRIORITY 255


// application specific define - there is no "default" QOS template in GQoS,
// only for this particular application does "default" have meaning.
#define QOS_DEFAULTNAME "default"       

// Use an arbitrary multicast group if none is specified on the command line
#define DEFAULT_MULTICASTGROUP        "234.5.6.7"

typedef struct _SP_OPTIONS
    {
    int  iProtocol;             // protocol to use
    BOOL bQos;                  // enable QOS
    BOOL bMulticast;            // enable multicasting
    } SP_OPTIONS;


typedef enum 
    {
    QOS_IOCTL_SET_DURING,       // do not use ioctl to set Qos
    QOS_IOCTL_SET_BEFORE,       // set qos with ioctl before connection/accept
    QOS_IOCTL_SET_AFTER,        // set qos with ioctl after connection/accept
    QOS_IOCTL_SET_QOS           // set qos in receiver during FD_QOS, note that 
                                //  qos must be set prior to wsaeventselect in 
                                //  order to ever receive fd_qos
    } QOS_IOCTL_SET;


typedef struct _QOS_OPTIONS
    {
    BOOL    bReceiver;          // act as receiver if TRUE
    BOOL    bWaitToSend;        // sender must wait for RESV before sending
    BOOL    bConfirmResv;       // have receiver request RESV confirmation
    BOOL    bQueryBufferSize;   // have WSAioctl return size of buffer needed 
                                //      when using SIO_GET_QOS (behaviour not
                                //      avail on Win98).
    BOOL    bMustSetQosInAccept;// Will be set for Win98 only.  Win98 currently
                                //      needs valid qos structure to be set in
                                //      wsaaccept condition func in lpSQos is valid
    BOOL    bDisableSignalling; // If TRUE do not emit RSVP signalling, just use 
                                //      traffic control
    BOOL    bAlternateQos;      // Alternate between enabling and disabling QOS on 
                                //      a socket every N sends
    UCHAR   SendPriority;       // create QOS_OBJECT_PRIORITY structure, and
                                //  set valid priority 0-7
    BOOL    bSetDestaddr;       // TRUE if unconnected UDP and QOS is used (not multicast)
    BOOL    bProviderSpecific;  // TRUE if a provider-specific object must be set
    BOOL    bFineGrainErrorAvail;   // TRUE if Win2000beta3 availability of
                                    //   fine grain errors on SIO_SET_QOS
    BOOL    bQosabilityIoctls;   // TRUE if Win2000beta3 qosablity ioctls 
    BOOL    bFixTemplate;       // TRUE if Win98 to divide ToeknRate and PeakBandwidth
                                //   by 8 when using WSAGetQOSByName 
    QOS_IOCTL_SET qosIoctlSet;  // when to set QOS
    CHAR    szTemplate[64];     // qos template
    } QOS_OPTIONS;


typedef struct _OPTIONS
    {
    CHAR            szHostname[64];
    unsigned short  port;
    int             nRepeat;
    CHAR            fillchar;
    int             nBufSize;
    CHAR *          buf;
    DWORD           dwSleep;
    DWORD           dwTotalClients;
    QOS_OPTIONS     qosOptions;
    SP_OPTIONS      spOptions;
    } OPTIONS;
    

extern FLOWSPEC default_notraffic;
extern FLOWSPEC default_g711;
extern SOCKADDR_IN g_destaddr;

extern BOOL FindServiceProvider(
    int iProtocol,
    BOOL bQos,
    BOOL bMulticast,
    WSAPROTOCOL_INFO *pProtocolInfo);

extern VOID Receiver(
    OPTIONS *pOptions, 
    WSAPROTOCOL_INFO *pProtocolInfo);

extern VOID Sender(
    OPTIONS *pOptions, 
    WSAPROTOCOL_INFO *pProtocolInfo);

extern BOOL SetQos(
    SOCKET sd, 
    QOS_OPTIONS *pQosOptions, 
    BOOL bSetQos, 
    QOS *pQos, 
    DWORD *cbQosLen);

extern BOOL GetQos(
    SOCKET sd, 
    BOOL bQueryBufferSize,
    QOS **pQos);

extern void PrintQos(
    QOS *qos, 
    CHAR *lpszIndent);

extern BOOL ChkQosSend(
    SOCKET sd);

#endif
