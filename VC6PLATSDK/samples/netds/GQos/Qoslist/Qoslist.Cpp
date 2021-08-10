// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1998 - 2000  Microsoft Corporation.  All Rights Reserved.
//
// This applications prints out a list (-l) of the names of predefined Qos 
// templates using WSAGetQosByName.  The program also allows a new QoS 
// template to be added to the system (-a), either service provider specific 
// or global to all providers (-g).  Finally, the program allows the added 
// QoS template to be removed.  
//
// To ensure that system-defined templates do not get inadvertantly removed, 
// only the "special" QoS template that is added by this program can be 
// removed.
//
// Usage:
//      List all QoS templates
//          qoslist
//          qoslist -l
//      Add a global QoS template
//          qoslist -a -g
//      Delete a global QoS template 
//          qoslist -d -g
// 
// Build:
//      Use the headers and libs from the NT5 Beta 2 Platform SDK or later.
//      Link with ws2_32.lib and qosname.lib
//      


#define WINVER 0x0500
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ws2spi.h>
#include <qos.h>
#include <qossp.h>
#include <qosname.h>
#include <stdio.h>



#define QOSTEST "qostest"



typedef enum
    {
    CMD_OPTION_ADD,
    CMD_OPTION_DEL,
    CMD_OPTION_LIST
    } TEMPLATE_CMD;

typedef struct _OPTIONS
    {
    TEMPLATE_CMD    template_cmd;
    BOOL            bGlobalTemplate;
    } OPTIONS;


FLOWSPEC default_qostest =
    {
    65000,
    6500,
    135000,
    QOS_NOT_SPECIFIED,
    QOS_NOT_SPECIFIED,
    SERVICETYPE_GUARANTEED,
    350,
    350
    };



static BOOL FindServiceProvider(WSAPROTOCOL_INFO *pProtocolInfo);
static BOOL AddQos(SOCKET sd, BOOL bGlobalTemplate, WSAPROTOCOL_INFO *pProtocolInfo);
static BOOL DeleteQos(SOCKET sd, BOOL bGlobalTemplate, WSAPROTOCOL_INFO *pProtocolInfo);
static BOOL ListQos(SOCKET sd);

static BOOL ValidOptions(char *argv[], int argc, OPTIONS *pOptions);
static void Usage(CHAR *szProgramname);



int main(int argc, char *argv[])
    {
    OPTIONS options;
    WSADATA WSAData; 
    WSAPROTOCOL_INFO protocol_info;
    SOCKET sd;
    int status;

    if (!ValidOptions(argv, argc, &options))
        exit(1);

    status = WSAStartup(MAKEWORD(2,2), &WSAData);
    if (status != NO_ERROR)
        {
        printf("WSAStartup %d", status);
        exit(1);
        }

    if (!FindServiceProvider(&protocol_info))
        {
        printf("Suitable GQOS Service Provider not found\n");
        exit(1);
        }

    sd = WSASocket(FROM_PROTOCOL_INFO, FROM_PROTOCOL_INFO, FROM_PROTOCOL_INFO,
            &protocol_info, 0, WSA_FLAG_OVERLAPPED);
    if (INVALID_SOCKET != sd)
        {
        switch (options.template_cmd)
            {
            case CMD_OPTION_ADD:
                AddQos(sd, options.bGlobalTemplate, &protocol_info);
                break;

            case CMD_OPTION_DEL:
                DeleteQos(sd, options.bGlobalTemplate, &protocol_info);
                break;

            case CMD_OPTION_LIST:
                ListQos(sd);
                break;
            }
        closesocket(sd);
        }   else printf("WSASocket Failed with error %d\n", WSAGetLastError());
    WSACleanup();
    return(0);
    }


// Abstract:
//      Look for a QoS-enabled TCP service provider.  NOTE:  actual 
//      service provider names are different on NT and Win9x when 
//      searching for a service provider, you should not use the service
//      provider name, but instead use the various flags in the protocol
//      structure.
// 
static BOOL FindServiceProvider(
    WSAPROTOCOL_INFO    *pProtocolInfo
    )
    {
    int nRet;
    WSAPROTOCOL_INFO *lpProtocolBuf = NULL;
    DWORD dwBufLen = 0;
    DWORD dwErr;
    BOOL bProtocolFound = FALSE;


    // force WSAEnumProtocols to indicate needed size for buffer
    if (SOCKET_ERROR != WSAEnumProtocols(NULL, lpProtocolBuf, &dwBufLen))
        {
        printf("WSAEnumProtocols: shouldn't be here since initial buffer not large enough\n");
        return(FALSE);
        }
    else if (WSAENOBUFS != (dwErr = WSAGetLastError()))
        {
        // we failed for some reason not relating to buffer size 
        printf("WSAEnumProtocols: %d\n", dwErr);
        return(FALSE);
        }

    // we know the buffer size
    if (NULL == (lpProtocolBuf = (WSAPROTOCOL_INFO *)malloc(dwBufLen)))
        {
        printf("malloc failed in FindServiceProvider\n");
        return(FALSE);
        }

    if (SOCKET_ERROR == (nRet = WSAEnumProtocols(NULL, lpProtocolBuf, &dwBufLen)))
        {
        printf("WSAEnumProtocols: 2nd time %d\n", WSAGetLastError());
        free(lpProtocolBuf);
        return(FALSE);
        }


    // loop thru protocols, looking for the  matching service provider 
    for (int i=0; i<nRet; i++)
        {
        if (AF_INET == lpProtocolBuf[i].iAddressFamily &&
            IPPROTO_TCP == lpProtocolBuf[i].iProtocol)
            {
            if (XP1_QOS_SUPPORTED == (XP1_QOS_SUPPORTED & lpProtocolBuf[i].dwServiceFlags1))
                {
                *pProtocolInfo = lpProtocolBuf[i];
                bProtocolFound = TRUE;
                break;
                }
            }
        }

    free(lpProtocolBuf);

    if (bProtocolFound)
        printf("Using service provider <%s>\n\n", pProtocolInfo->szProtocol);

    return(bProtocolFound);
    }


// Abstract:
//      Add either a service provider QoS template or global QoS template.
// 
static BOOL AddQos(
    SOCKET              sd, 
    BOOL                bGlobalTemplate,
    WSAPROTOCOL_INFO    *pProtocolInfo
    )
    {
    QOS     qos;
    WSABUF  wsabuf;
    CHAR    szQosname[256];


    ZeroMemory((char *)&qos, sizeof(qos));
    qos.SendingFlowspec = default_qostest;

    strcpy(szQosname, QOSTEST);
    if (bGlobalTemplate)
        strcat(szQosname, "_g");

    ZeroMemory((char *)&wsabuf, sizeof(wsabuf));
    wsabuf.len = (int) strlen(szQosname) + 1;
    wsabuf.buf = (char *)malloc(wsabuf.len);
    if (wsabuf.buf == NULL) 
    	{
       printf("malloc failed in AddQos\n");
       return (FALSE);
    	}
    strcpy(wsabuf.buf, szQosname);
    if (!WSCInstallQOSTemplate((bGlobalTemplate ? NULL : &pProtocolInfo->ProviderId), &wsabuf, &qos))
    	{
       printf("WSCInstallQOSTemplate: %d\n", WSAGetLastError());
       free(wsabuf.buf);
       return (FALSE);
    	}
    printf("Added QOS template <%s>\n", szQosname);
    free(wsabuf.buf);

    return(TRUE);
    }


// Abstract:
//      Delete either a service provider QoS template or global QoS 
//      template.
// 
static BOOL DeleteQos(
    SOCKET              sd, 
    BOOL                bGlobalTemplate,
    WSAPROTOCOL_INFO    *pProtocolInfo
    )
    {
    WSABUF  wsabuf;
    CHAR    szQosname[256];


    strcpy(szQosname, QOSTEST);
    if (bGlobalTemplate)
        strcat(szQosname, "_g");

    ZeroMemory((char *)&wsabuf, sizeof(wsabuf));
    wsabuf.len = (int) strlen(szQosname) + 1;
    wsabuf.buf = (char *)malloc(wsabuf.len);
    if (wsabuf.buf == NULL) 
    	{
       printf("malloc fail in DeleteQos\n");
       return(FALSE);
    	}
    strcpy(wsabuf.buf, szQosname);
    if (!(WSCRemoveQOSTemplate((bGlobalTemplate ? NULL : &pProtocolInfo->ProviderId), &wsabuf)))
    	{
        printf("WSCRemoveQOSTemplate: %d\n", WSAGetLastError());
        free(wsabuf.buf);
        return(FALSE);
    	}
    
    printf("Removed QOS template <%s>\n", szQosname);
    free(wsabuf.buf);
    return(TRUE);
    }


// Abstract:
//      Obtain a list of QoS templates and confirm that the QOS structure //      for it can be retreived.
// 
static BOOL ListQos(
    SOCKET sd
    )
    {
    WSABUF qoslist;
    WSABUF qosname;
    QOS qos;


    ZeroMemory(&qoslist, sizeof(qoslist));
    ZeroMemory(&qosname, sizeof(qosname));
    ZeroMemory(&qos, sizeof(qos));  //needed

    // get list of predefined Qos names
    qoslist.len = 2048;   // pick large buffer to hold list of QOS names
    qoslist.buf = (char *)malloc(qoslist.len);
    if (qoslist.buf == NULL)
    	{
    		printf("malloc failed in ListQos\n");
    		return FALSE;
    	}
    
    qoslist.buf[0] = '\0';
    if (!WSAGetQOSByName(sd, &qoslist, &qos)) 
    	{
       printf("WSAGetQOSByName[1]: err: %d len: %d\n", WSAGetLastError(), qoslist.len);
       free(qoslist.buf);
       return (FALSE);
    	}

    char *p = qoslist.buf;
    while (strlen(p))
        {
        qosname.len = (int) (strlen(p)+1);  // advance to next QOS name
        if (NULL == (qosname.buf = (char *)malloc(qosname.len))) 
            {
            printf("malloc failed in ListQos\n");
            free(qoslist.buf);
            return (FALSE);
            }
        
        strcpy(qosname.buf, p);
        // confirm you can retrieve the associated Qos structure 
        if (!WSAGetQOSByName(sd, &qosname, &qos))
            printf("WSAGetQosByName[2] failed: %d - qosname = <%s>\n", 
                WSAGetLastError(), qosname.buf);
        else
                printf("QOS name = <%s>\n", p);
        free(qosname.buf);
  
        p += strlen(p) + 1;  // advance to next name
        }
    
    free(qoslist.buf);

    return(TRUE);
    }


// Abstract:
//      Verify options passed in and set options structure accordingly.
// 
static BOOL ValidOptions(
    char        *argv[], 
    int         argc, 
    OPTIONS     *pOptions
    )
    {
    BOOL bValidOptions = TRUE;


    pOptions->template_cmd    = CMD_OPTION_LIST;
    pOptions->bGlobalTemplate = FALSE;  

    for (int i=1; i<argc; i++)
        {
        if ((argv[i][0] == '-') || (argv[i][0] == '/') ) 
            {
            switch(tolower(argv[i][1])) 
                {
                case 'a' :
                    pOptions->template_cmd = CMD_OPTION_ADD;
                    break;

                case 'r' :
                case 'd' :
                    pOptions->template_cmd = CMD_OPTION_DEL;
                    break;

                case 'l' :
                    pOptions->template_cmd = CMD_OPTION_LIST;
                    break;

                case 'g' :
                    pOptions->bGlobalTemplate = TRUE;
                    break;

                case '?' :
                    Usage(argv[0]);
                    return(FALSE);
                    break;

                default:
                    printf("  unknown options flag %s\n", argv[i]);
                    Usage(argv[0]);
                    return(FALSE);
                    break;
                }
            }
        else
            {
            printf("  unknown option %s\n", argv[i]);
            Usage(argv[0]);
            return(FALSE);
            }
        }

    return(TRUE);
    }


// Abstract:
//      Print out usage table for the program
// 
static void Usage(
    CHAR    *szProgramname
    )
    {
    printf("usage:\n%s [-a | -d | -l]\n", szProgramname);
    printf("%s -?\n", szProgramname);
    printf("  -?\t\tDisplay this help\n");
    printf("  -a\t\tInstall a predefined QOS template called qostest\n");
    printf("  -d|r\t\tRemove the special qostest QOS template\n");
    printf("  -g\t\tInstall/remove a global template versus a provider-specific\n");
    printf("  -l\t\tList out all installed QOS templates and their contents\n");
    return;
    }

