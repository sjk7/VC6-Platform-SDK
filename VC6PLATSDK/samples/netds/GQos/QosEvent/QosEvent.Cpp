// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1998 - 2000  Microsoft Corporation.  All Rights Reserved.
//
// Module:
//      qosevent.cpp
//
// Abstract:
//      This application demonstrates how to GQOS-enable a simple Winsock 
//      application.  This application makes no attempt to do anything useful 
//      per se, but concentrates on illustrating key techniques to use when 
//      developing your GQOS-enabled application.  Additionally, this 
//      application demonstrates several Winsock2-specific APIs and techniques 
//      that are useful whether or not your main interest is GQOS-enabling your
//      application.
//
//      Commandline parameters determine whether this application functions as 
//      either a sender (-n) or a receiver (default).  Use the -? commandline 
//      switch to determine available options.
//
//      This application simply sends a buffer of data when acting as the 
//      sender, to an instance of itself acting as a receiver.  Any number of 
//      senders (up to MAXCLIENTS) can be started to interact with one instance
//      of a receiver.The size of the data buffer (-b), its contents (-d), and 
//      the number of times to send (-l) this buffer are controllable via 
//      commandline switches. A repeat value of 0 implies continuous sending.  
//      The (-c) commandline switch allows enabling/disabling QOS on the socket
//      every 5 sends and will cause any repeat count entered to be overridden 
//      and set to continuous mode. A delay commandline switch (-s:#), measured
//      in milliseconds can be specified for the sender to insure the total 
//      transfer spans a measured unit of time (this would be interesting for 
//      observing RSVP PATH/RESV message refresh).
//
//      The sender and receiver can choose to use either UDP or TCP (default) 
//      for data transfers by using the -p commandline option.  The port number
//      (endpoint) used by TCP and UDP is also controllable via commandline 
//      switch (-e).  
//
//      The application is also multicast capable. A multicast receiver must 
//      specify the multicast option (-m) and the multicast IP address to join 
//      or allow a default to be used.  If the multicast option is not specified
//      but the sender attempts to send data directly to that multicast address,
//      the -m is implicitly set by the program. When both -n and -m values are 
//      used (by a multicast sender) any address specified in -n is overriden by
//      the value used in -m.
//
//      This application can be enabled to support GQOS by specifying a specific 
//      GQOS template to use (-q) for transfers.  Additionally, when to enable 
//      GQOS (i.e. when to inform the GQOS Service Provider) can be controlled 
//      via a commandline switch (-i).  The priority to use for sending data is 
//      also controllable via a commandline switch (-tc-priority). 
//
// Entry Points:
//      main - this is where it all starts
//
// Usage:
//      Act as a TCP receiver and enable QOS using g711 codec
//          qosevent -q:g711
//      Act as a TCP sender and enable QOS using g711 and send buffer 10 times
//          qosevent -n:receiver_host -q:g711 -l:10
//      Act as a UDP sender and enable QOS using g711, set QOS during connect,
//      send buffer 30 times with a 2 second delay between sends
//          qosevent -p:udp -n:receiver_host -q:g711 -i:d -l:30 -s:2000
//      Act as a TCP sender, no QOS, and send buffer once
//          qosevent -n:receiver_host
//      Act as a UDP sender, no QOS, and send buffer once
//          qosevent -n:receiver_host
//      Act as a multicast receiver and enable QOS using g711
//          qosevent -q:g711 -m:234.5.6.7
//
// Build:
//      Use the headers and libs from the June98 Platform SDK or later.
//      Link with ws2_32.lib
//      
// Author:
//      Barry R. Butterklee
//
// Changes:
//      8/99 - Correct handling of SIO_GET_QOS for Windows 2000 (and workaround 
//             for Windows 98) added to GetQos().
//      8/99 - Fix handling of RSVP_RESERVE_INFO in PrintQos() and SetQos()
//      8/99 - Remove obsolete QOS_OBJECT_PRIORITY
//      8/99 - Update comments in CreateSendingSocket


#include "qosevent.h"

OPTIONS default_options = 
    {
    "localhost",
    MY_DEFPORT,
    1,
    'c',
    4096,
    NULL,
    0,
    0,
    {TRUE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, INVALID_SEND_PRIORITY, 
        TRUE, TRUE, TRUE, TRUE, FALSE, QOS_IOCTL_SET_BEFORE, QOS_DEFAULTNAME},
    {IPPROTO_TCP, FALSE, FALSE}
    };

FLOWSPEC default_notraffic =
    {
    QOS_NOT_SPECIFIED,
    QOS_NOT_SPECIFIED,
    QOS_NOT_SPECIFIED,
    QOS_NOT_SPECIFIED,
    QOS_NOT_SPECIFIED,
    SERVICETYPE_NOTRAFFIC,
    QOS_NOT_SPECIFIED,
    QOS_NOT_SPECIFIED
    };
    

FLOWSPEC default_g711 =
    {
    8500,
    680,
    17000,
    QOS_NOT_SPECIFIED,
    QOS_NOT_SPECIFIED,
    SERVICETYPE_GUARANTEED,
    340,
    340
    };


SOCKADDR_IN g_destaddr;   

static BOOL ValidOptions(char *argv[], int argc, OPTIONS *pOptions);
static VOID PrintOptions(OPTIONS *pOptions);
static VOID Usage(CHAR *szProgramname);




int _cdecl main(int argc, char *argv[])
{
    int ret, err;
    OPTIONS options;
    WSADATA WSAData; 
    WSAPROTOCOL_INFO protocol_info;

    ret = NO_ERROR;
    options.buf = NULL;

    // Process the Command Line Options
    if (!ValidOptions(argv, argc, &options))
        exit(1);

    // Startup Winsock
    err = WSAStartup(MAKEWORD(2,2), &WSAData);
    if (err)
    {
        printf("WSAStartup Failed (%d) Exiting\n", err);
        goto cleanup;
    }

    // Look for a Service Provider to handle what 
    // we need from the options
    if (!FindServiceProvider(
                    options.spOptions.iProtocol, 
                    options.spOptions.bQos,
                    options.spOptions.bMulticast,
                    &protocol_info))
    {
        printf("No matching service provider found. Exiting\n");
        goto cleanup;
    } 

    // Show the user what they have selected
    PrintOptions(&options);

    // Become a Sender or a Reciever
    if (options.qosOptions.bReceiver)
        Receiver(&options, &protocol_info);
    else
        Sender(&options, &protocol_info);

cleanup:

    if (options.buf) 
        free(options.buf);

    WSACleanup();
    return(0);
}




// Abstract:
//      Verify options passed in and set options structure accordingly.
//
BOOL ValidOptions(char *argv[], int argc, OPTIONS *pOptions)
{
	OSVERSIONINFO   verInfo;
	char *errReason = NULL;
	int i;

	// Initialize the options to default values
	*pOptions = default_options;

	for (i=1; i<argc; i++)
	{
		if ((argv[i][0] != '-') && (argv[i][0] != '/') ) 
			goto err;
		    
		switch(tolower(argv[i][1])) 
		{
		case 'b' :
			if (strlen(argv[i]) <= 3)
				goto err;
			pOptions->nBufSize = 1024*atoi(&argv[i][3]);
			break;

		case 'c' :
			pOptions->qosOptions.bAlternateQos = TRUE;
			break;

		case 'd' :
			if (strlen(argv[i]) <= 3)
				goto err;
			pOptions->fillchar = argv[i][3];
			break;

		case 'e' :
			if (strlen(argv[i]) <= 3)
				goto err;
			pOptions->port = (USHORT) atoi(&argv[i][3]);
			break;

		case 'i' :
			if (strlen(argv[i]) <= 3)
				goto err;

            switch(tolower(argv[i][3]))
            {
                case 'a':
                    pOptions->qosOptions.qosIoctlSet = QOS_IOCTL_SET_AFTER;
                    break;
                case 'b':
                    pOptions->qosOptions.qosIoctlSet = QOS_IOCTL_SET_BEFORE;
                    break;
                case 'd':
					pOptions->qosOptions.qosIoctlSet = QOS_IOCTL_SET_DURING;
					break;
		        case 'q':
					pOptions->qosOptions.qosIoctlSet = QOS_IOCTL_SET_QOS;
					break;
		        default:
					goto err;
            }
			break;

		case 'l' :
			if (strlen(argv[i]) <= 3)
				goto err;
			pOptions->nRepeat = atoi(&argv[i][3]);
			break;

		case 'm' :
			pOptions->spOptions.bMulticast = TRUE;
			if (strlen(argv[i]) <= 3) 
				break;
				
			// we are getting passed a hostname, Is it too big?
			if (strlen(&argv[i][3]) >= sizeof(pOptions->szHostname)) 
			{
				errReason = "specified hostname too long, max 64 characters";
				goto err;
			}

			strcpy(pOptions->szHostname, &argv[i][3]);
			break;

		case 'n' : 
			pOptions->qosOptions.bReceiver = FALSE; 
			if (strlen(argv[i]) <= 3)
				break;

			// we are trying to specify a hostname
			// but multicast group overrides hostname on -n
			if (pOptions->spOptions.bMulticast) 
			{
				printf("Warning: Hostname specified in -n is ignored when multicast is set\n");
				break;
			}

			// Is it too big?
			if (strlen(&argv[i][3]) >= sizeof(pOptions->szHostname)) 
			{
				errReason = "specified hostname too long, max 64 characters";
				goto err;
			}
			
			strcpy(pOptions->szHostname, &argv[i][3]);			
			break;

		case 'p' :
			if (strlen(argv[i]) <= 3)
				goto err;
			
            switch(tolower(argv[i][3]))
            {
                case 'u':
					pOptions->spOptions.iProtocol = IPPROTO_UDP;
                    break;
                case 't':
					pOptions->spOptions.iProtocol = IPPROTO_TCP;
					break;
		        default:
					goto err;
            }
			break;

		case 'q' : 
			pOptions->spOptions.bQos = TRUE; 
			if (strlen(argv[i]) <= 3)
				break;

			// We are being given the template name, Is it too long?
			if (strlen(&argv[i][3]) >= sizeof(pOptions->qosOptions.szTemplate))
			{
				errReason = "specified template name too long, max 64 characters";
				goto err;
			}
			
			strcpy(pOptions->qosOptions.szTemplate, &argv[i][3]);
			break;

		case 'r' :
			if (strlen(argv[i]) <= 3)					
				goto err;
			
			if ((_stricmp(argv[i], "-rsvp-confirm") == 0) ||
				(_stricmp(argv[i], "-rsvp_confirm") == 0))
			{
				pOptions->qosOptions.bConfirmResv = TRUE;
				pOptions->qosOptions.bProviderSpecific = TRUE;
			}
			else if ((_stricmp(argv[i], "-rsvp-wait") == 0) ||
					(_stricmp(argv[i], "-rsvp_wait") == 0))
			{
				pOptions->qosOptions.bWaitToSend = TRUE;
				pOptions->qosOptions.bProviderSpecific = TRUE;
			} 
			else 
				goto err;
			
			break;

		case 's' :
			if (strlen(argv[i]) <= 3) 
				goto err;
			
			pOptions->dwSleep = atoi(&argv[i][3]);
			break;

        case '?':
            i=0; //reset i to not print a specific location error
            
		default:
			goto err;
		}
	}


	if (pOptions->qosOptions.bReceiver)
		pOptions->fillchar = 0;

	if (pOptions->spOptions.bMulticast)
	{
		pOptions->spOptions.iProtocol = IPPROTO_UDP;
		pOptions->qosOptions.bSetDestaddr = FALSE;
	}

	if (IPPROTO_TCP == pOptions->spOptions.iProtocol)
	{
		pOptions->spOptions.bMulticast = FALSE;
		pOptions->qosOptions.bSetDestaddr = FALSE;
	}
	else if (!pOptions->spOptions.bMulticast)
		pOptions->qosOptions.bSetDestaddr = TRUE;

	if (pOptions->spOptions.bQos)
	{
		if (pOptions->qosOptions.bReceiver)
	    {
		    if (pOptions->qosOptions.bWaitToSend)
                // not a valid sender option
    			pOptions->qosOptions.bWaitToSend = FALSE; 
	    		                                          
        }   
        else
        {
            if (pOptions->qosOptions.bConfirmResv)
                // not a valid sender option
			    pOptions->qosOptions.bConfirmResv = FALSE;
        }

		if (pOptions->qosOptions.bAlternateQos)
			pOptions->nRepeat = 0;  // override repeat count to continuous mode

		if (    (IPPROTO_UDP == pOptions->spOptions.iProtocol) 
		    &&  (!pOptions->spOptions.bMulticast))
			// using UDP, there WSAAccept will not be called, therefore do 
			// not wait to set qos
			pOptions->qosOptions.qosIoctlSet = QOS_IOCTL_SET_BEFORE;

		verInfo.dwOSVersionInfoSize = sizeof(verInfo);
		GetVersionEx(&verInfo);
		switch (verInfo.dwPlatformId)
		{
		case VER_PLATFORM_WIN32_NT:
			pOptions->qosOptions.bQueryBufferSize = TRUE;
			pOptions->qosOptions.bMustSetQosInAccept = FALSE;
			pOptions->qosOptions.bFineGrainErrorAvail = TRUE;
			pOptions->qosOptions.bQosabilityIoctls = TRUE;
			printf("running on NT\n");
			break;

		case VER_PLATFORM_WIN32_WINDOWS:
			pOptions->qosOptions.bQueryBufferSize = FALSE;
			pOptions->qosOptions.bMustSetQosInAccept = TRUE;
			pOptions->qosOptions.bFineGrainErrorAvail = FALSE;
			pOptions->qosOptions.bQosabilityIoctls = FALSE;
			printf("running on 9x\n");
			break;

		default:
			printf ("requires Windows NT or Windows 98\n");
			pOptions->qosOptions.bQueryBufferSize = FALSE;
			pOptions->qosOptions.bMustSetQosInAccept = TRUE;
			pOptions->qosOptions.bFineGrainErrorAvail = FALSE;
			pOptions->qosOptions.bQosabilityIoctls = FALSE;
			break;
		}
	}

	pOptions->buf = (char *)malloc(pOptions->nBufSize);
	if (!pOptions->buf) {
		printf("Unable to allocate buffer for sends of size (%d). Exiting.\n",
		            pOptions->nBufSize);
		return(FALSE);
	}
	
	FillMemory(pOptions->buf, pOptions->nBufSize, pOptions->fillchar);
	return(TRUE);
	
err:
	if (i>0) 
	{
		if (errReason)
			printf("  invalid option syntax (%s): %s\n", argv[i], errReason);
		else
			printf("  invalid option syntax (%s)\n", argv[i]);
	}
	Usage(argv[0]);
	return(FALSE);
}




// Abstract:
//      Just print the options to be used for this run.
//
static VOID PrintOptions(OPTIONS *pOptions)
{
	printf("Options\n");
	printf("  Protocol %d\n", pOptions->spOptions.iProtocol);
	printf("  Port %d\n", pOptions->port);
	
	if (pOptions->qosOptions.bReceiver)
		printf("  Act as Receiver\n");
	else
	{
		printf("  Act as sender and send to %s\n", pOptions->szHostname);
		printf("  Sleep %d milliseconds between sends\n", pOptions->dwSleep);
		printf("  Fill buffer with <%c>\n", pOptions->fillchar);
		if (pOptions->nRepeat)
			printf("  Repeat sending the buffer %d times\n", pOptions->nRepeat);
		else
			printf("  Repeat sending the buffer continually\n");
	}
	
	printf("  Bufsize %d (1K increments)\n", pOptions->nBufSize);
	printf("  Multicast is %s\n", 
	        (pOptions->spOptions.bMulticast ? "Enabled" : "Disabled"));

	if (pOptions->spOptions.bQos)
	{
		printf("  Qos template %s\n", pOptions->qosOptions.szTemplate);
		printf("  Qos to be set ");
		
		switch (pOptions->qosOptions.qosIoctlSet)
		{
		case QOS_IOCTL_SET_BEFORE: 
			printf("Before accept/connect/joinleaf\n");
			break;
			
		case QOS_IOCTL_SET_AFTER:  
			printf("After accept/connect/joinleaf\n"); 
			break;
			
		case QOS_IOCTL_SET_DURING: 
			printf("During accept/connect/joinleaf\n");
			break;
			
		case QOS_IOCTL_SET_QOS: 
			if (pOptions->qosOptions.bReceiver)
				printf("During FD_QOS, implies QOS with no signaling set before accept/connect (eventually)\n");
			else
			{
				pOptions->qosOptions.qosIoctlSet = QOS_IOCTL_SET_BEFORE;
				printf("Before connect\n");
			}
			break;
	    default:
	        _assume(0);
		}

		if (pOptions->qosOptions.bConfirmResv )
			printf("  RESV confirmation to be requested\n");
		
		if (INVALID_SEND_PRIORITY != pOptions->qosOptions.SendPriority)
			printf("  Qos TC SendPriority to be set to %d\n", 
					pOptions->qosOptions.SendPriority);

		if (!pOptions->qosOptions.bReceiver)
		{
			if (pOptions->qosOptions.bWaitToSend)
				printf("  Wait for RESV before sending data\n");
			else
				printf("  Do not wait for RESV to start sending data\n");
		} else
			printf("  Qos must be set during Accept = %s\n", 
				(pOptions->qosOptions.bMustSetQosInAccept?"TRUE":"FALSE"));

		printf("  Query for QOS buffer size: %s\n",
				(pOptions->qosOptions.bQueryBufferSize?"TRUE":"FALSE"));
	}

	printf("\n");
	return;
}




// Abstract:
//      Print out usage table for the program
//
VOID Usage(CHAR *szProgramname)
{
    printf("usage:\n  %s -?\n\n", szProgramname);
    printf("  %s [-b:#] [-d:c] [-e:#] [-l:#] [-m:group] [-n:host] [-s:#] [-u]\n\t[-q:template [-i:[a|b|d|q]] [-c] [-rsvp-confirm] [-rsvp-wait]]\n\n",
            szProgramname);
    printf("  -?\t\tDisplay this help\n");
    printf("\n");
    printf("  -b:bufsize\tSize of send/recv buffer; in 1K increments (Def:%d)\n",
            default_options.nBufSize);
    printf("  -d:c\t\tCharacter used to fill buffer (Def:%c)\n",
            default_options.fillchar);
    printf("  -e:port\tEndpoint number (port) to use (Def:%d)\n",
            default_options.port);
    printf("  -l:loop\tLoop count for sending buffer (0==>continuous) (Def:%d)\n",
            default_options.nRepeat);
    printf("  -m:group\tMulticast group (IP) to join (Def:%s)\n", 
            DEFAULT_MULTICASTGROUP);
    printf("  -n:host\tAct as the client and connect to 'host' (Def:%s)\n",
            default_options.szHostname);
    printf("  -p:protocol\tTCP or UDP (def:TCP)\n");
    printf("  -s:#\t\tSleep # milliseconds between sends (def: 0)\n");
    printf("\n");
    printf("  -q:template\tEnable QoS and use 'template' to specify the name (Def:%s)\n",
            default_options.qosOptions.szTemplate);
    printf("  -c\t\tCycle enabling/disabling QOS on sending socket (Def: no cycling)\n");
    printf("  -i:[a|b|d|q]\tSet Qos After, Before, During accept/connect, or during FD_QOS\n\t\t\t(def: Before)\n");
    printf("  -rsvp-confirm\t\tRequest RESV confirmation be sent (Def: no confirmation) (not for Windows XP and later)\n");
    printf("  -rsvp-wait\t\tWait for RESV from receiver before sending data (not for Windows XP and later)\n");
    return;
}

