// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1998 - 2000  Microsoft Corporation.  All Rights Reserved.
//
// Module:
//      printqos.cpp
//
// Abstract:
//      This file contains one public entry point PrintQos, which is used to
//      print out a QOS structure.  The remaining static functions are merely 
//      helper functions devoted to specific parts of a QOS structure.  The
//      QOS structure contains 3 components:
//          Sending FLOWSPEC
//          Receiving FLOWSPEC
//          ProviderSpecific buffer consisting of 0 or more QOS objects
//
// Entry Points:
//      PrintQos - print out a QOS structure including Provider-specific data
//
// Author:
//      Barry R. Butterklee


#include "qosevent.h"


// print functions for major components of a QOS structure  
static void PrintFlowspec(FLOWSPEC *pFlowspec, CHAR *lpszIndent);
static void PrintProviderSpecific(WSABUF *pProviderSpecific, CHAR *lpszIndent);

// print functions for QOS objects (part of provider-specific buffer)
static void PrintRsvpStatus(RSVP_STATUS_INFO *pRsvpStatus, CHAR *lpszIndent);
static void PrintRsvpResv(RSVP_RESERVE_INFO *pRsvpResv, CHAR *lpszIndent);
static void PrintRsvpAdspec(RSVP_ADSPEC *pRsvpAdspec, CHAR *lpszIndent);
static void PrintRsvpPolicy(RSVP_POLICY_INFO *pRsvpPolicy, CHAR *lpszIndent);
static void PrintQosSDMode(QOS_SD_MODE *pQosSDMode, CHAR *lpszIndent);
static void PrintQosDestaddr(QOS_DESTADDR *pQosDestaddr, CHAR *lpszIndent);

static void PrintAdGeneralParams(AD_GENERAL_PARAMS *pGeneralParams, CHAR *lpszIndent);
static void PrintPolicy(RSVP_POLICY PolicyElement[], ULONG NumPolicyElement, CHAR *lpszIndent);
static void PrintSendersList(QOS_OBJECT_HDR *pObj, CHAR *lpszIndent);

static CHAR *ServiceTypeToStr(SERVICETYPE ServiceType);



// Abstract:
//      Print out the passed in QOS structure.  Printouts start out indent by
//      the specified amount.  Major subcomponents of the QOS structure get
//      indented an extra 2 spaces.
//
void PrintQos(QOS *qos, CHAR *lpszIndent)
{
    CHAR szIndent[24];
    
    strncpy(szIndent, lpszIndent, sizeof(szIndent));
    szIndent[sizeof(szIndent)-1] = '\0';

    if (NULL == qos)
    {
        printf("%sQOS structure is NULL\n", szIndent);
        return;
    }

    printf("%sSendingFlowSpec\n", szIndent);
    PrintFlowspec(&qos->SendingFlowspec, szIndent);
    
    printf("%sReceivingingFlowSpec\n", szIndent);
    PrintFlowspec(&qos->ReceivingFlowspec, szIndent);
    
    printf("%sProviderSpecific - len = %d\n", szIndent, 
                qos->ProviderSpecific.len);
    PrintProviderSpecific(&qos->ProviderSpecific, szIndent);
    
    printf("\n");
    return;
}




static void PrintFlowspec(FLOWSPEC *pFlowspec, CHAR *lpszIndent)
{
    CHAR szIndent[24];

    strncpy(szIndent, lpszIndent, sizeof(szIndent));
    strncat(szIndent, "  ", sizeof(szIndent));
    szIndent[sizeof(szIndent)-1] = '\0';

    if (QOS_NOT_SPECIFIED == pFlowspec->TokenRate)
        printf("%sTokenRate          = QOS_NOT_SPECIFIED\n", szIndent);
    else
        printf("%sTokenRate          = %d\n", szIndent, pFlowspec->TokenRate);

    if (QOS_NOT_SPECIFIED == pFlowspec->TokenBucketSize)
        printf("%sTokenBucketSize    = QOS_NOT_SPECIFIED\n", szIndent);
    else
        printf("%sTokenBucketSize    = %d\n", szIndent, pFlowspec->TokenBucketSize);

    if (QOS_NOT_SPECIFIED == pFlowspec->PeakBandwidth)
        printf("%sPeakBandwidth      = QOS_NOT_SPECIFIED\n", szIndent);
    else
        printf("%sPeakBandwidth      = %d\n", szIndent, pFlowspec->PeakBandwidth);

    if (QOS_NOT_SPECIFIED == pFlowspec->Latency)
        printf("%sLatency            = QOS_NOT_SPECIFIED\n", szIndent);
    else
        printf("%sLatency            = %d\n", szIndent, pFlowspec->Latency);

    if (QOS_NOT_SPECIFIED == pFlowspec->DelayVariation)
        printf("%sDelayVariation     = QOS_NOT_SPECIFIED\n", szIndent);
    else
        printf("%sDelayVariation     = %d\n", szIndent, pFlowspec->DelayVariation);

    printf("%sServiceType        = %s\n", 
        szIndent, ServiceTypeToStr(pFlowspec->ServiceType));

    if (QOS_NOT_SPECIFIED == pFlowspec->MaxSduSize)
        printf("%sMaxSduSize         = QOS_NOT_SPECIFIED\n", szIndent);
    else
        printf("%sMaxSduSize         = %d\n", szIndent, pFlowspec->MaxSduSize);

    if (QOS_NOT_SPECIFIED == pFlowspec->MinimumPolicedSize)
        printf("%sMinimumPolicedSize = QOS_NOT_SPECIFIED\n", szIndent);
    else
        printf("%sMinimumPolicedSize = %d\n", szIndent, pFlowspec->MinimumPolicedSize);

    return;
}





static void PrintProviderSpecific(WSABUF *pProviderSpecific, CHAR *lpszIndent)
{
    CHAR *pBuf = pProviderSpecific->buf;
    QOS_OBJECT_HDR *pObjectHdr = (QOS_OBJECT_HDR *)pBuf;
    ULONG length = 0;
    CHAR szIndent[24];


    strncpy(szIndent, lpszIndent, sizeof(szIndent));
    strncat(szIndent, "  ", sizeof(szIndent));
    szIndent[sizeof(szIndent)-1] = '\0';

    if (0 == pProviderSpecific->len)
        return;

    do 
    {
        switch (pObjectHdr->ObjectType)
        {
        case RSVP_OBJECT_STATUS_INFO:
            printf("%sRSVP_OBJECT_STATUS_INFO\n", szIndent);
            PrintRsvpStatus((RSVP_STATUS_INFO *)pObjectHdr, szIndent);
            break;

        case RSVP_OBJECT_RESERVE_INFO:
            printf("%sRSVP_OBJECT_RESERVE_INFO\n", szIndent);
            PrintRsvpResv((RSVP_RESERVE_INFO *)pObjectHdr, szIndent);
            break;

        case RSVP_OBJECT_ADSPEC:
            printf("%sRSVP_OBJECT_ADSPEC\n", szIndent);
            PrintRsvpAdspec((RSVP_ADSPEC *)pObjectHdr, szIndent);
            break;

        case RSVP_OBJECT_POLICY_INFO:
            printf("%sRSVP_OBJECT_POLICY_INFO\n", szIndent);
            PrintRsvpPolicy((RSVP_POLICY_INFO *)pObjectHdr, szIndent);
            break;

// since this is added for Windows XP, we need to make sure it is there first
#ifdef RSVP_OBJECT_FILTERSPEC_LIST
        case RSVP_OBJECT_FILTERSPEC_LIST :
			printf("%sRSVP_OBJECT_FILTERSPEC_LIST Object Present\n",szIndent);
			PrintSendersList(pObjectHdr, szIndent);
			break;
#endif

        case QOS_OBJECT_SD_MODE:
            printf("%sQOS_SD_MODE\n", szIndent);
            PrintQosSDMode((QOS_SD_MODE *)pObjectHdr, szIndent);
            break;

        case QOS_OBJECT_DESTADDR:
            printf("%sQOS_OBJECT_DESTADDR\n", szIndent);
            PrintQosDestaddr((QOS_DESTADDR *)pObjectHdr, szIndent);
            break;

        case QOS_OBJECT_END_OF_LIST:
            printf("%sQOS_END_OF_LIST - no more objects\n", szIndent);
            return;

        default:
            printf("%sUnknown ObjectType %08x in QosObjectHdr\n", 
                szIndent, pObjectHdr->ObjectType);
            return;
        }

        // advance past the current object
        length += pObjectHdr->ObjectLength;
        if (length < pProviderSpecific->len)
        {
            // ok to advance pointer becasue we will not exceed the provider 
            // specific buffer
            pBuf += pObjectHdr->ObjectLength;
            pObjectHdr = (QOS_OBJECT_HDR *)pBuf;
            continue;
        } 

        break;
    }while (TRUE);
    return;
}




static void PrintRsvpStatus(RSVP_STATUS_INFO *pRsvpStatus, CHAR *lpszIndent)
{
    CHAR szIndent[24];

    strncpy(szIndent, lpszIndent, sizeof(szIndent));
    strncat(szIndent, "  ", sizeof(szIndent));
    szIndent[sizeof(szIndent)-1] = '\0';

    printf("%sStatusCode = ", szIndent);
    switch (pRsvpStatus->StatusCode)
    {
    case WSA_QOS_RECEIVERS:             // at least one Reserve has arrived 
        printf("WSA_QOS_RECEIVERS"); 
        break;
        
    case WSA_QOS_SENDERS:               // at least one Path has arrived 
        printf("WSA_QOS_SENDERS"); 
        break;
        
    case WSA_QOS_NO_SENDERS:            // there are no senders
        printf("WSA_QOS_NO_SENDERS"); 
        break;
        
    case WSA_QOS_NO_RECEIVERS:          // there are no receivers
        printf("WSA_QOS_NO_RECEIVERS"); 
        break;
        
    case WSA_QOS_REQUEST_CONFIRMED:     // Reserve has been confirmed
        printf("WSA_QOS_REQUEST_CONFIRMED"); 
        break;
        
    case WSA_QOS_ADMISSION_FAILURE:     // error due to lack of resources
        printf("WSA_QOS_ADMISSION_FAILURE"); 
        break;
        
    case WSA_QOS_POLICY_FAILURE:        // rejected for administrative reasons
                                        //      bad credentials
        printf("WSA_QOS_POLICY_FAILURE"); 
        break;
        
    case WSA_QOS_BAD_STYLE:             // unknown or conflicting style
        printf("WSA_QOS_BAD_STYLE"); 
        break;
        
    case WSA_QOS_BAD_OBJECT:            // problem with some part of the filterspec/
                                        //      providerspecific buffer in general 
        printf("WSA_QOS_BAD_OBJECT"); 
        break;
        
    case WSA_QOS_TRAFFIC_CTRL_ERROR:    // problem with some part of the flowspec
        printf("WSA_QOS_TRAFFIC_CTRL_ERROR"); 
        break;
        
    case WSA_QOS_GENERIC_ERROR:         // general error 
        printf("WSA_QOS_GENERIC_ERROR");
        break;
        
    default:
        printf("Unknown RSVP StatusCode %lu", pRsvpStatus->StatusCode); 
        break;
    }

    printf("\n");
    printf("%sExtendedStatus1=%lu\n", szIndent, pRsvpStatus->ExtendedStatus1); 
    printf("%sExtendedStatus2=%lu\n", szIndent, pRsvpStatus->ExtendedStatus2); 

    return;
}




static void PrintRsvpResv(RSVP_RESERVE_INFO *pRsvpResv, CHAR *lpszIndent)
{
    CHAR    szIndent[24];
    ULONG   i;

    strncpy(szIndent, lpszIndent, sizeof(szIndent));
    strncat(szIndent, "  ", sizeof(szIndent));
    szIndent[sizeof(szIndent)-1] = '\0';

    printf("%sStyle = ",szIndent);
    switch (pRsvpResv->Style)
    {
    case RSVP_DEFAULT_STYLE:
        printf("RSVP_DEFAULT_STYLE\n");
        break;
    case RSVP_WILDCARD_STYLE:
        printf("RSVP_WILDCARD_STYLE\n");
        break;
    case RSVP_FIXED_FILTER_STYLE:
        printf("RSVP_FIXED_FILTER_STYLE\n");
        break;
    case RSVP_SHARED_EXPLICIT_STYLE:
        printf("RSVP_SHARED_EXPLICIT_STYLE\n");
        break;
    default:
        printf("Unknown style %d\n", pRsvpResv->Style);
        break;
    }
    
    printf("%sConfirmRequest %s\n", szIndent, (pRsvpResv->ConfirmRequest?"yes":"no"));
    printf("%sNumFlowDesc = %lu\n", szIndent, pRsvpResv->NumFlowDesc);
    
    for (i=0; i<pRsvpResv->NumFlowDesc; i++)
    {
        ULONG   j;

        PrintFlowspec(&pRsvpResv->FlowDescList[i].FlowSpec, szIndent);
        printf("%s  NumFilters = %lu\n", szIndent, pRsvpResv->FlowDescList[i].NumFilters);
        for (j=0; j<pRsvpResv->FlowDescList[i].NumFilters; j++)
        {
            printf("%s  FilterType = ", szIndent);
            switch (pRsvpResv->FlowDescList[i].FilterList[j].Type)
            {
                case FILTERSPECV4:
                {
                    PCHAR   lpszIPv4;
                    struct in_addr in;

                    in.S_un.S_addr = pRsvpResv->FlowDescList[i].FilterList[j].FilterSpecV4.Address.Addr;
                    lpszIPv4 = inet_ntoa(in);

                    if (lpszIPv4 != NULL)
                    {
                        printf("FILTERSPECV4\n");
                        printf("%s    Address = %s\n", szIndent, lpszIPv4);
                        printf("%s    Port    = %hu\n", szIndent, 
                            pRsvpResv->FlowDescList[i].FilterList[j].FilterSpecV4.Port);
                    }
                }
                break;
                case FILTERSPECV6:
                {
                    CHAR    szIPv6[32];
                    DWORD   dwIPv6Len = sizeof(szIPv6);
                    DWORD   dwConvResult;
                
                    dwConvResult = 
                        WSAAddressToString(
                            (LPSOCKADDR)&pRsvpResv->FlowDescList[i].FilterList[j].FilterSpecV6.Address,
                            sizeof(IN_ADDR_IPV6),
                            NULL,
                            szIPv6,
                            &dwIPv6Len);

                    if (0 == dwConvResult)
                    {
                        printf("FILTERSPECV6\n");
                        printf("%s    Address = %s\n", szIndent, szIPv6);
                        printf("%s    Port    = %hu\n", szIndent, 
                            pRsvpResv->FlowDescList[i].FilterList[j].FilterSpecV6.Port);
                    }
                }
                break;
                case FILTERSPECV6_FLOW:
                {
                    CHAR    szIPv6[32];
                    DWORD   dwIPv6Len = sizeof(szIPv6);
                    DWORD   dwConvResult;
                
                    dwConvResult = 
                        WSAAddressToString(
                            (LPSOCKADDR)&pRsvpResv->FlowDescList[i].FilterList[j].FilterSpecV6Flow.Address,
                            sizeof(IN_ADDR_IPV6),
                            NULL,
                            szIPv6,
                            &dwIPv6Len);

                    if (0 == dwConvResult)
                    {
                        printf("FILTERSPECV6_FLOW\n");
                        printf("%s    Address = %s\n", szIndent, szIPv6);
                        printf("%s    FlowLabel = %s\n", szIndent,
                            pRsvpResv->FlowDescList[i].FilterList[j].FilterSpecV6Flow.FlowLabel);
                    }
                }
                break;
                case FILTERSPECV4_GPI:
                {
                    PCHAR   lpszIPv4;
                    struct in_addr in;

                    in.S_un.S_addr = pRsvpResv->FlowDescList[i].FilterList[j].FilterSpecV4.Address.Addr;
                    lpszIPv4 = inet_ntoa(in);

                    if (lpszIPv4 != NULL)
                    {
                        printf("FILTERSPECV4_GPI\n");
                        printf("%s    Address = %s\n", szIndent, lpszIPv4);
                        printf("%s    Port    = %hu\n", szIndent, 
                            pRsvpResv->FlowDescList[i].FilterList[j].FilterSpecV4Gpi.GeneralPortId);
                    }
                }
                break;
                case FILTERSPECV6_GPI:
                {
                    CHAR    szIPv6[32];
                    DWORD   dwIPv6Len = sizeof(szIPv6);
                    DWORD   dwConvResult;
                
                    dwConvResult = 
                        WSAAddressToString(
                            (LPSOCKADDR)&pRsvpResv->FlowDescList[i].FilterList[j].FilterSpecV6Gpi.Address,
                            sizeof(IN_ADDR_IPV6),
                            NULL,
                            szIPv6,
                            &dwIPv6Len);

                    if (0 == dwConvResult)
                    {
                        printf("FILTERSPECV6_GPI\n");
                        printf("%s    Address = %s\n", szIndent, szIPv6);
                        printf("%s    Port    = %hu\n", szIndent, 
                            pRsvpResv->FlowDescList[i].FilterList[j].FilterSpecV6Gpi.GeneralPortId);
                    }
                }
                break;
            }
        }
    }
    
    return;
}




static void PrintRsvpAdspec(RSVP_ADSPEC *pRsvpAdspec, CHAR *lpszIndent)
{
    CHAR szIndent[24];

    strncpy(szIndent, lpszIndent, sizeof(szIndent));
    strncat(szIndent, "  ", sizeof(szIndent));
    szIndent[sizeof(szIndent)-1] = '\0';

    printf("%sGeneralParams\n", szIndent);
    PrintAdGeneralParams(&pRsvpAdspec->GeneralParams, szIndent);
    printf("%sNumberOfServices = %lu\n", szIndent, pRsvpAdspec->NumberOfServices);
    for (ULONG i=0; i<pRsvpAdspec->NumberOfServices; i++)
    {
        printf("%sServices[%lu].Length = %lu\n",
            szIndent, i, pRsvpAdspec->Services[i].Length);
        printf("%sServices[%lu].ServiceType = %s\n",
            szIndent, i, ServiceTypeToStr(pRsvpAdspec->Services[i].Service));
        printf("%sServices[%lu].Overrides\n", szIndent, i);
        PrintAdGeneralParams(&pRsvpAdspec->Services[i].Overrides, szIndent);
        if (SERVICETYPE_GUARANTEED == pRsvpAdspec->Services[i].Service)
        {
            printf("%s  Services[%lu].CTotal    = %ld\n", 
                szIndent, i, pRsvpAdspec->Services[i].Guaranteed.CTotal);
            printf("%s  Services[%lu].DTotal    = %ld\n", 
                szIndent, i, pRsvpAdspec->Services[i].Guaranteed.DTotal);
            printf("%s  Services[%lu].CSum      = %ld\n", 
                szIndent, i, pRsvpAdspec->Services[i].Guaranteed.CSum);
            printf("%s  Services[%lu].DSum      = %ld\n", 
                szIndent, i, pRsvpAdspec->Services[i].Guaranteed.DSum);
        } else {
            printf("%sServices[%lu].ParamBuffer[].ParameterId  = %lu\n",
                szIndent, i, pRsvpAdspec->Services[i].ParamBuffer->ParameterId);
            printf("%sServices[%lu].ParamBuffer[].Length       = %lu\n",
                szIndent, i, pRsvpAdspec->Services[i].ParamBuffer->Length);
        }
    }
    return;
}




static void PrintRsvpPolicy(RSVP_POLICY_INFO *pRsvpPolicy, CHAR *lpszIndent)
{
    CHAR szIndent[24];

    strncpy(szIndent, lpszIndent, sizeof(szIndent));
    strncat(szIndent, "  ", sizeof(szIndent));
    szIndent[sizeof(szIndent)-1] = '\0';

    PrintPolicy(pRsvpPolicy->PolicyElement, pRsvpPolicy->NumPolicyElement, szIndent);
    return;
}




static void PrintQosSDMode(QOS_SD_MODE *pQosSDMode, CHAR *lpszIndent)
{
    CHAR szIndent[24];

    strncpy(szIndent, lpszIndent, sizeof(szIndent));
    strncat(szIndent, "  ", sizeof(szIndent));
    szIndent[sizeof(szIndent)-1] = '\0';

    printf("%sShapeDiscardMode = ", szIndent);
    switch (pQosSDMode->ShapeDiscardMode)
    {
    case TC_NONCONF_BORROW:
        printf("TC_NONCONF_BORROW\n"); 
        break;
        
    case TC_NONCONF_SHAPE:
        printf("TC_NONCONF_SHAPE\n"); 
        break;
        
    case TC_NONCONF_DISCARD:
        printf("TC_NONCONF_DISCARD\n"); 
        break;
        
    default:
        printf("Unknown traffic class %lu\n", pQosSDMode->ShapeDiscardMode);
        break;
    }
    return;
}




static void PrintQosDestaddr(QOS_DESTADDR *pQosDestaddr, CHAR *lpszIndent)
{
    CHAR    szIndent[24];
    CHAR    szIP[32];
    DWORD   dwIPLen = sizeof(szIP);
    DWORD   dwConvResult;

    strncpy(szIndent, lpszIndent, sizeof(szIndent));
    strncat(szIndent, "  ", sizeof(szIndent));
    szIndent[sizeof(szIndent)-1] = '\0';

    dwConvResult = WSAAddressToString(
                        (LPSOCKADDR)pQosDestaddr->SocketAddress,
                        pQosDestaddr->SocketAddressLength,
                        NULL,
                        szIP,
                        &dwIPLen);

    if (0 == dwConvResult)
    {
        printf("%sDestAddress     = %s\n", szIndent, szIP);
        printf("%sDestAddress Len = %d\n", szIndent, pQosDestaddr->SocketAddressLength);
    }
    return;
}





static void PrintAdGeneralParams(AD_GENERAL_PARAMS *pGeneralParams, CHAR *lpszIndent)
{
    CHAR szIndent[24];

    strncpy(szIndent, lpszIndent, sizeof(szIndent));
    strncat(szIndent, "  ", sizeof(szIndent));
    szIndent[sizeof(szIndent)-1] = '\0';

    printf("%sIntServAwareHopCount  = %ld\n", szIndent, pGeneralParams->IntServAwareHopCount);
    
    if (POSITIVE_INFINITY_RATE == pGeneralParams->PathBandwidthEstimate)
        printf("%sPathBandwidthEstimate = <POSITIVE INFINITY>\n", szIndent);
    else
        printf("%sPathBandwidthEstimate = %ld\n", szIndent, pGeneralParams->PathBandwidthEstimate);
    
    printf("%sMinimumLatency        = %ld\n", szIndent, pGeneralParams->MinimumLatency);
    printf("%sPathMTU               = %ld\n", szIndent, pGeneralParams->PathMTU);
    printf("%sFlags                 = %ld\n", szIndent, pGeneralParams->Flags);
    return;
}




static void PrintPolicy(RSVP_POLICY PolicyElement[], ULONG NumPolicyElement, CHAR *lpszIndent)
{
    CHAR szIndent[24];

    strncpy(szIndent, lpszIndent, sizeof(szIndent));
    strncat(szIndent, "  ", sizeof(szIndent));
    szIndent[sizeof(szIndent)-1] = '\0';

    printf("%sNum Policy Elements %d\n", lpszIndent, NumPolicyElement);
    for (ULONG i=0; i<NumPolicyElement; i++)
    {
        printf("%s  [%d] Len  = %hu\n", szIndent, i, PolicyElement[i].Len);
        printf("%s  [%d] Type = %hu\n", szIndent, i, PolicyElement[i].Type);
    }
    return;
}



static CHAR *ServiceTypeToStr(SERVICETYPE ServiceType)
{
    static CHAR szServiceType[128];

    if (QOS_NOT_SPECIFIED == ServiceType)
    {
        strcpy(szServiceType, "QOS_NOT_SPECIFIED");
        return(szServiceType);
    }

    switch ((ServiceType & 0x0000FFFF))
    {
    case SERVICETYPE_NOTRAFFIC : 
        strcpy(szServiceType, "SERVICETYPE_NOTRAFFIC"); 
        break;
        
    case SERVICETYPE_BESTEFFORT : 
        strcpy(szServiceType, "SERVICETYPE_BESTEFFORT"); 
        break;
        
    case SERVICETYPE_CONTROLLEDLOAD : 
        strcpy(szServiceType, "SERVICETYPE_CONTROLLEDLOAD"); 
        break;
        
    case SERVICETYPE_GUARANTEED : 
        strcpy(szServiceType, "SERVICETYPE_GUARANTEED"); 
        break;
        
    case SERVICETYPE_NETWORK_UNAVAILABLE : 
        strcpy(szServiceType, "SERVICETYPE_NETWORK_UNAVAILABLE"); 
        break;
        
    case SERVICETYPE_GENERAL_INFORMATION : 
        strcpy(szServiceType, "SERVICETYPE_GENERAL_INFORMATION"); 
        break;
        
    case SERVICETYPE_NOCHANGE : 
        strcpy(szServiceType, "SERVICETYPE_NOCHANGE"); 
        break;
        
    case SERVICETYPE_NONCONFORMING :
        strcpy(szServiceType, "SERVICETYPE_NONCONFORMING"); 
        break;
        
    case SERVICETYPE_NETWORK_CONTROL :
        strcpy(szServiceType, "SERVICETYPE_NETWORK_CONTROL");
        break;
        
    case SERVICETYPE_QUALITATIVE :
        strcpy(szServiceType, "SERVICETYPE_QUALITATIVE");
        break;
        
    default:
        sprintf(szServiceType, "Unknown service type %lu  zzz", ServiceType);
        break;
    }

    if (ServiceType & SERVICE_NO_TRAFFIC_CONTROL)
        strcat(szServiceType, " | SERVICE_NO_TRAFFIC_CONTROL");
    else if (ServiceType & SERVICE_NO_QOS_SIGNALING)
        strcat(szServiceType, " | SERVICE_NO_QOS_SIGNALING");

    return(szServiceType);
}

static void PrintSendersList(QOS_OBJECT_HDR *pObj, CHAR *lpszIndent)
{
    CHAR    szIndent[24];
    LPRSVP_FILTERSPEC pFilterSpec = NULL;
    int nFilters = 0;

    strncpy(szIndent, lpszIndent, sizeof(szIndent));
    strncat(szIndent, "  ", sizeof(szIndent));
    szIndent[sizeof(szIndent)-1] = '\0';

    pFilterSpec = (LPRSVP_FILTERSPEC) ((char *)pObj + sizeof(QOS_OBJECT_HDR));
    nFilters = (pObj->ObjectLength - sizeof (QOS_OBJECT_HDR)) 
    							/ sizeof (RSVP_FILTERSPEC);
    
    printf("%sNumber of Filters present = %d\n", szIndent,nFilters);
    while (nFilters--)
    {
        PCHAR lpszFilter = inet_ntoa(*(struct in_addr*)&pFilterSpec->FilterSpecV4.Address.Addr);

        if (!lpszFilter)
            return;

        printf("%ssender ip = %s:%d\n", szIndent, lpszFilter, pFilterSpec->FilterSpecV4.Port);	
        pFilterSpec++;
    }
}


