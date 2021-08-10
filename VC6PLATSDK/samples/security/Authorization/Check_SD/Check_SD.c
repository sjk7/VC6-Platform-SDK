/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1997 - 2000.  Microsoft Corporation.  All rights reserved

Module Name:

    check_sd.c

Abstract:

    This module calls a variety of different functions in the
    other modules to obtain security descriptor information
    associated with the object name passed to this module.

--*/

#include "check_sd.h"
#include <tchar.h>
#include <stdio.h>

void DisplayUsage(void)
{
     _tprintf(TEXT("\nUsage: check_sd [object] [name]\n"));
         _tprintf(TEXT(" -a : mailslot, use \\\\[server]\\mailslot\\[mailslotname]\n"));
     _tprintf(TEXT(" -d : directory or driver letter, use \\\\.\\[driveletter]\n"));
     _tprintf(TEXT(" -e : event\n"));
     _tprintf(TEXT(" -f : file\n"));
     _tprintf(TEXT(" -i : memory mapped file\n"));
     _tprintf(TEXT(" -k : desktop, use [window station\\desktop]\n"));
     _tprintf(TEXT(" -l : printer, use \\\\[server]\\[printername]\n"));
     _tprintf(TEXT(" -m : mutex\n"));
     _tprintf(TEXT(" -n : named pipe, use \\\\[server or .]\\pipe\\[pipename]\n"));
     _tprintf(TEXT(" -o : process access token, use pid instead of name\n"));
     _tprintf(TEXT(" -p : process, use pid instead of name\n"));
     _tprintf(TEXT(" -r : registry key\n"));
     _tprintf(TEXT(" -s : sempahore\n"));
     _tprintf(TEXT(" -t : network share, use [server\\sharename]\n"));
     _tprintf(TEXT(" -v : service\n"));
     _tprintf(TEXT(" -w : window station\n"));
     return;
}

void _tmain(int argc, TCHAR *argv[])
{
     int u = 0;

     //
     // display usage
     //
     if (argc != 3){
          DisplayUsage();
          return;
     }


	 //
	 // Do validation on the user input to help avoid buffer overruns.   
	 //

	 _try{
	    //
		// argv[1] should be a null terminated string 
	    // of exactly two characters in length (not including the NULL). 
		//
		if ((_T('-') != argv[1][0]) || (_T('\0') == argv[1][1]) || (_T('\0') != argv[1][2])){
			 DisplayUsage();
			 return;
		}

		//
		// argv[2] should have at least one non-NULL character before a NULL character.
		//
		if (_T('\0') == argv[2][0]){
	         DisplayUsage();
			 return;	 
	    }

		//
		// argv[2] should not be a string of more than MAX_PATH characters.
		//
		u = 0;
		while (_T('\0') != argv[2][u]){
			 if (MAX_PATH == u){
			      DisplayUsage();
			      return;	 
			 }
			 u++;
		}

	 } 
	 _except(EXCEPTION_EXECUTE_HANDLER){
          DisplayUsage();
          return;	 
	 }

     _tprintf(TEXT(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"));
     _tprintf(TEXT(">>                 SECURITY INFORMATION                >>\n"));
     _tprintf(TEXT(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n"));
     _tprintf(TEXT("object name ........ %s\n"), argv[2]);
     _tprintf(TEXT("object type ........ "));

     switch (argv[1][1])
     {
          case 'a':
               _tprintf(TEXT("mailslot\n"));
               DumpKernelObject(argv[2], argv[1][1]);
               break;
          case 'e':
               _tprintf(TEXT("event\n"));
               DumpKernelObject(argv[2], argv[1][1]);
               break;
          case 'f':
               _tprintf(TEXT("file\n"));
               DumpFile(argv[2], argv[1][1]);
               break;
          case 'd':
               _tprintf(TEXT("directory\n"));
               DumpFile(argv[2], argv[1][1]);
               break;
          case 'm':
               _tprintf(TEXT("mutex\n"));
               DumpKernelObject(argv[2], argv[1][1]);
               break;
          case 'r':
               _tprintf(TEXT("registry\n"));
               DumpRegistryKey(argv[2]);
               break;
          case 's':
               _tprintf(TEXT("semaphore\n"));
               DumpKernelObject(argv[2], argv[1][1]);
               break;
          case 'p':
               _tprintf(TEXT("process\n"));
               DumpKernelObject(argv[2], argv[1][1]);
               break;
          case 'i':
               _tprintf(TEXT("memory mapped file\n"));
               DumpKernelObject(argv[2], argv[1][1]);
               break;
          case 'v':
               _tprintf(TEXT("service\n"));
               DumpService(NULL, argv[2]);
               break;
          case 'w':
               _tprintf(TEXT("window station\n"));
               DumpUserObject(argv[2], argv[1][1]);
               break;
          case 'k':
               _tprintf(TEXT("desktop\n"));
               DumpUserObject(argv[2], argv[1][1]);
               break;
          case 'n':
               _tprintf(TEXT("named pipe\n"));
               DumpKernelObject(argv[2], argv[1][1]);
               break;
          case 'o':
               _tprintf(TEXT("process access token\n"));
               DumpKernelObject(argv[2], argv[1][1]);
               break;
          case 'l':
               _tprintf(TEXT("printer\n"));
               DumpPrinter(argv[2]);
               break;
          case 't':
               _tprintf(TEXT("network share\n"));
               DumpNetShare(argv[2]);
               break;
          default:
               DisplayUsage();
     }
}