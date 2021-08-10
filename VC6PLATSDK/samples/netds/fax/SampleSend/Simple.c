    /*++
    
    Copyright (c) 1998 - 2000  Microsoft Corporation
    
    Module Name:
    
       simple.c
    
    Abstract:
    
        This module implements a simple command line fax-send utility 
        
    --*/
    
    #include <windows.h>
    #include <winbase.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <winfax.h>
    #include <tchar.h>
    #include <assert.h>
    #include <shellapi.h>
    
    
    #ifdef DBG
TCHAR   szDebugBuffer[80]={0};
        #define DEBUG_SIMPLE(parm1,parm2) \
        {\
            _sntprintf(szDebugBuffer, (sizeof(szDebugBuffer)/sizeof(szDebugBuffer[0])-1), parm1, parm2);\
            OutputDebugString(szDebugBuffer);\
        }
    #else   
        #define DEBUG_SIMPLE(parm1,parm2)
    #endif
    
    #define ARR_SIZE(a) (sizeof(a)/sizeof(a[0]))

    void GiveUsage(LPTSTR AppName)
    {
        _tprintf( TEXT("Usage : %s /d <full path to doc> /n <number>\n --send a fax\n"),AppName);
        _tprintf( TEXT("Usage : %s /? -- this message\n"),AppName);
    
    }
    
    void PrintDeviceStatus(PFAX_DEVICE_STATUS fds)
    {
        TCHAR SubmitBuffer[100];
        TCHAR StartBuffer[100];
        SYSTEMTIME SystemTime;
    
        if (!fds)
        {
            return;
        }
    
        _tprintf(TEXT("Device Id:\t\t%d\n"),fds->DeviceId );
        _tprintf(TEXT("Device Name:\t\t%s\n"),fds->DeviceName );
        _tprintf(TEXT("CallerId:\t\t%s\n"),fds->CallerId );
        _tprintf(TEXT("CSID:\t\t\t%s\n"),fds->Csid );
        _tprintf(TEXT("TSID:\t\t\t%s\n"),fds->Tsid );
        _tprintf(TEXT("Page:\t\t\t%d of %d\n"),fds->CurrentPage,fds->TotalPages );
        _tprintf(TEXT("DocumentName:\t\t%s\n"),fds->DocumentName);
        _tprintf(TEXT("JobType:\t\t%d\n"),fds->JobType);
        _tprintf(TEXT("PhoneNumber:\t\t%s\n"),fds->PhoneNumber);
        _tprintf(TEXT("SenderName:\t\t%s\n"),fds->SenderName);
        _tprintf(TEXT("RecipientName:\t\t%s\n"),fds->RecipientName);
        _tprintf(TEXT("Size (in bytes):\t%d\n"),fds->Size);
        _tprintf(TEXT("Status (see FPS flags):\t0x%x\n"),fds->Status);
    
        FileTimeToSystemTime(&fds->StartTime,&SystemTime);
    
        GetTimeFormat(
            LOCALE_SYSTEM_DEFAULT,
            LOCALE_NOUSEROVERRIDE,
            &SystemTime,
            NULL,
            StartBuffer,
            ARR_SIZE(StartBuffer)
            );
    
        FileTimeToSystemTime(&fds->SubmittedTime,&SystemTime);
        SystemTimeToTzSpecificLocalTime(NULL,&SystemTime,&SystemTime);
    
        GetTimeFormat(
            LOCALE_SYSTEM_DEFAULT,
            LOCALE_NOUSEROVERRIDE,
            &SystemTime,
            NULL,
            SubmitBuffer,
            ARR_SIZE(SubmitBuffer)
            );
    
        _tprintf(TEXT("Job Submited at %s\n"),SubmitBuffer);
        _tprintf(TEXT("Job transmission started at %s\n\n"),StartBuffer);
    }
    
    int main(int argc,char *argvA[]) 
    /*++
    
    Routine Description:
    
        Entry point to the setup program
    
    Arguments:
    
        argc - Number of args.
        argvA - the commandline arguments.
    
    
    Return Value:
    
    
    --*/
    {
        LPTSTR *argv;
        int argcount = 0;
        TCHAR Document[MAX_PATH] = {0};
        TCHAR Number[64] = {0};
    
        HANDLE hFax;
        HANDLE hCompletionPort = INVALID_HANDLE_VALUE;
        HANDLE hFile;
        PFAX_JOB_PARAM JobParam;
        PFAX_COVERPAGE_INFO CoverpageInfo;
        DWORD JobId;
        DWORD dwBytes, CompletionKey;
        PFAX_EVENT FaxEvent;
        BOOL bTerminate = FALSE;
        HANDLE hPort;
        PFAX_DEVICE_STATUS DeviceStatus;
    
        //
        // do commandline stuff
        //
    #ifdef UNICODE
        argv = CommandLineToArgvW( GetCommandLine(), &argc );
    #else
        argv = argvA;
    #endif
    
        DEBUG_SIMPLE ("Number of arguments = %d\n",argc);
        for (argcount=0;argcount<argc;argcount++)
        {
            DEBUG_SIMPLE ("Arg %d:",argcount);
            DEBUG_SIMPLE (" %s\n",argv[argcount]);
        }
    
        // check for commandline switches
        for (argcount=0; argcount<argc; argcount++)
        {
            if ((argv[argcount][0] == L'/') || (argv[argcount][0] == L'-'))
            {
                switch (towlower(argv[argcount][1]))
                {
                case 'n':
                   lstrcpyn(Number, argv[argcount+1],ARR_SIZE(Number));
                   break;
                case 'd':
                   lstrcpyn(Document, argv[argcount+1],ARR_SIZE(Document));
                   //check to see if the file exists and if it is a disk file
                   hFile = CreateFile(Document, 
                                      GENERIC_READ, 
                                      FILE_SHARE_READ, 
                                      NULL, 
                                      OPEN_EXISTING,
                                      FILE_ATTRIBUTE_NORMAL,
                                      NULL);
                   if ((hFile == INVALID_HANDLE_VALUE)||(GetFileType(hFile) != FILE_TYPE_DISK))
                   {
                        _tprintf( TEXT("Error with file : %s \n"),Document);
                        GiveUsage(argv[0]);
                        return -1;
                   }
                   CloseHandle(hFile);
                   break;
                case '?':
                   GiveUsage(argv[0]);
                   return 0;
                default:
                   break;
                }
            }
        }
    
        if (!Number[0] || !Document[0])
        {
            _tprintf( TEXT("Missing args.\n") );
            GiveUsage(argv[0]);
            return -1;
        }
    
        //
        // connect to fax service
        //
        if (!FaxConnectFaxServer(NULL,&hFax))
        {
            _tprintf( TEXT("FaxConnectFaxServer failed, ec = %d\n"),GetLastError() );
            return -1;
        }
    
        assert (hFax != NULL);
    
        hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,0);
    
        if (!hCompletionPort)
        {
            _tprintf( TEXT("CreateIoCompletionPort failed, ec = %d\n"), GetLastError() );
            FaxClose( hFax );
            return -1;
        }
    
        if (!FaxInitializeEventQueue(
            hFax,
            hCompletionPort,
            0,
            NULL,
            0
            ))
        {
            _tprintf( TEXT("FaxInitializeEventQueue failed, ec = %d\n"), GetLastError() );
            FaxClose( hFax );
            return -1;
        }
    
        FaxCompleteJobParams(&JobParam,&CoverpageInfo);
        JobParam->RecipientNumber = Number;
        if (!FaxSendDocument( hFax, Document, JobParam, NULL , &JobId) )
        {
            _tprintf( TEXT("FaxSendDocument failed, ec = %d \n"), GetLastError() );
            FaxClose( hFax );
            CloseHandle( hCompletionPort );
            FaxFreeBuffer(JobParam);
            FaxFreeBuffer(CoverpageInfo);
            return -1;
        }
    
        _tprintf(
            TEXT("Queued document %s for transmition to %s, JobID = %d\n"),
            Document,
            Number,
            JobId
            );
    
        FaxFreeBuffer( JobParam );
        FaxFreeBuffer( CoverpageInfo );
    
        while (
            !bTerminate && 
            GetQueuedCompletionStatus(
                hCompletionPort,
                &dwBytes,
                &CompletionKey,
                (LPOVERLAPPED *)&FaxEvent,
                INFINITE
                )
            )
       {
    
            _tprintf( TEXT("Received event 0x%x\n"),FaxEvent->EventId);
    
            switch (FaxEvent->EventId) {
                case FEI_IDLE:
                case FEI_COMPLETED:
                case FEI_MODEM_POWERED_ON: 
                case FEI_MODEM_POWERED_OFF:
                case FEI_FAXSVC_ENDED:     
                    bTerminate = TRUE;
                    break;
    
                case FEI_JOB_QUEUED:
                    _tprintf( TEXT("JobId 0x%x queued\n"),FaxEvent->JobId );
                    break;
    
                case FEI_DIALING:          
                case FEI_SENDING:          
                case FEI_RECEIVING:              
                case FEI_BUSY:             
                case FEI_NO_ANSWER:        
                case FEI_BAD_ADDRESS:      
                case FEI_NO_DIAL_TONE:     
                case FEI_DISCONNECTED:           
                case FEI_FATAL_ERROR:      
                if (FaxOpenPort( hFax, FaxEvent->DeviceId,PORT_OPEN_QUERY, &hPort) )
                {
                    if (FaxGetDeviceStatus(hPort,&DeviceStatus) )
                    {
                        PrintDeviceStatus(DeviceStatus);
                        FaxFreeBuffer( DeviceStatus );
                    }
                    FaxClose( hPort );
                }
                break;
            }
        }
    
        FaxClose( hFax );
        CloseHandle( hCompletionPort );
        return 1;
    }
    
