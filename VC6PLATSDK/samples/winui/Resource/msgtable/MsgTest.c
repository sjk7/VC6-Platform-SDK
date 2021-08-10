/* Microsoft Developer Support
   Copyright 1992 - 2000 Microsoft Corporation */

#include <windows.h>
#include <tchar.h>
#include <stdio.h>

/* messages.h is created by mc.exe when compiling messages.mc */
#include "messages.h"

#define MAX_MESSAGES            5
#define MAX_MSG_LENGTH       1024
#define SEVERITY_MASK  0xC0000000
#define FACILITY_MASK  0x0FFF0000
#define MSG_ID_MASK    0x0000FFFF


/********************************************************************
* FUNCTION: myPutMsg(HINSTANCE hLib, LPVOID lpArgs, DWORD dwMsgId,  *
*                    DWORD dwLangId)                                *
*                                                                   *
* PURPOSE: format and output error dwMsgId, using string defined    *
*          for language dwLangId, with insert strings lpArgs, from  *
*          the messagetable resource in the DLL referenced by       *
*          handle hLib                                              *
*                                                                   *
* INPUT: Library handle, insert strings, message ID number, and     *
*        language ID as defined in the .mc file                     *
*                                                                   *
* RETURNS: none                                                     *
********************************************************************/
VOID myPutMsg (
    HINSTANCE hLib, 
    PVOID pArgs, 
    DWORD dwMsgId, 
    DWORD dwLangId)
{
    BOOL bSuccess  = FALSE;
    PTSTR msgBuf   = NULL;  /* hold text of the error message that we build */
    int dwCode;  /* hold various codes extracted from dwMsgId */

    /* 

    Here is the layout of the message ID:

    3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
    1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
    +---+-+-+-----------------------+-------------------------------+
    |Sev|C|R|     Facility          |               Code            |
    +---+-+-+-----------------------+-------------------------------+

    where

      Sev - is the severity code
      C - is the Customer code flag
      R - is a reserved bit
      Facility - is the facility code
      Code - is the facility's status code
    */

    _tprintf(TEXT("Severity: "));
    /* output the severity and facility code. Mask off the severity */
    /* bits with SEVERITY_MASK and shift them down */
    dwCode = (dwMsgId & SEVERITY_MASK) >> 30;
    switch (dwCode)
    {
        case STATUS_SEVERITY_WARNING:
            _tprintf(TEXT("STATUS_SEVERITY_WARNING  ")); 
            break;
              
        case STATUS_SEVERITY_SUCCESS:
            _tprintf(TEXT("STATUS_SEVERITY_SUCCESS  ")); 
            break;
            
        case STATUS_SEVERITY_INFORMATIONAL:
            _tprintf(TEXT("STATUS_SEVERITY_INFORMATIONAL  ")); 
            break;
            
        case STATUS_SEVERITY_ERROR:
            _tprintf(TEXT("STATUS_SEVERITY_ERROR  ")); 
            break;
            
        default:
            _tprintf(TEXT("Unknown!  ")); 
            break;
    }
    
    _tprintf (TEXT("\nFacility: "));
    /* Mask off the facility bits with FACILITY_MASK and shift them down */
    dwCode = (dwMsgId & FACILITY_MASK) >> 16;
    switch (dwCode)
    {
        case FACILITY_SYSTEM:
            _tprintf(TEXT("FACILITY_SYSTEM  ")); 
            break;
            
        case FACILITY_STUBS:
            _tprintf(TEXT("FACILITY_STUBS  ")); 
            break;
            
        case FACILITY_RUNTIME:
            _tprintf(TEXT("FACILITY_RUNTIME  ")); 
            break;
            
        case FACILITY_IO_ERROR_CODE:
            _tprintf(TEXT("FACILITY_IO_ERROR_CODE  ")); 
            break;
            
        default:
             _tprintf(TEXT("Unknown!  ")); 
             break;
    }
    
    /* retrieve and format the message from the messagetable DLL. */
    bSuccess = FormatMessage(
        FORMAT_MESSAGE_FROM_HMODULE         |   /* get the message from the DLL */
            FORMAT_MESSAGE_ALLOCATE_BUFFER  |   /* allocate the msg buffer for us */
            FORMAT_MESSAGE_ARGUMENT_ARRAY   |   /* pArgs is an array of 32-bit values */
        60,                                     /* line length for the mesages */
        hLib,                                   /* the messagetable DLL handle */
        dwMsgId,                                /* message ID */
        dwLangId,                               /* language ID as defined in .mc file */
        msgBuf,                                 /* address of pointer to buffer for message */
        MAX_MSG_LENGTH,                         /* maximum size of the message buffer */
        pArgs);                                 /* array of insert strings for the message */

    if (!bSuccess)
    {
        _tprintf(TEXT("Error %d from FormatMessage\n"), GetLastError());
    }
    else
    {
        /* mask off the actual message number with MSG_ID_MASK and show it */
        _tprintf(TEXT("\nError: %d: %s"), dwMsgId & MSG_ID_MASK, msgBuf);
        /* Free the buffer that FormatMessage allocated for us. */
        LocalFree((HLOCAL) msgBuf);
    }
    
    _tprintf(TEXT("\n__________\n"));
    CloseHandle(hLib);
}


/********************************************************************
* FUNCTION: _tmain()                                                *
*                                                                   *
* PURPOSE: Load the message resource DLL, and call myPutMsg() to    *
*          format and output error messages to the user             *
*                                                                   *
* INPUT: none                                                       *
*                                                                   *
* RETURNS: none                                                     *
********************************************************************/
int __cdecl _tmain ()
{
    HINSTANCE hLib = NULL;  /* handle to the messagetable DLL */
    PTCHAR aInsertStrs[8] = {0};  /* array of 32-bit insert values for FormatMessage*/
    WORD wLangID;

    /* Check to make sure we are running on Windows NT */
    if( GetVersion() & 0x80000000 )
    {
        MessageBox(NULL, 
            TEXT("Sorry, this application requires Windows NT.\n")
            TEXT("This application will now terminate."),
            TEXT("Error: Windows NT Required to Run"),  MB_OK );
        return(1);
    }
    
    /* 
     * Load the resource library without calling any entry points since 
     * this is a resource-only DLL 
     * Note that in general one should use absolute paths in calls of 
     * LoadLibraries and LoadLibraryEx, because relative paths pose a
     * significant security risk. For more information refer to MSDN for the
     * documentation of LoadLibrary and LoadLibraryEx
     */
    hLib = LoadLibraryEx(TEXT("messages.dll"), NULL, DONT_RESOLVE_DLL_REFERENCES);
    if (!hLib)
    {
        _tprintf(TEXT("Error %d from LoadLibrary\n"), GetLastError());
    }
    
    /* Messages in the .mc file have been defined using standard locale ID's:
       see MAKELANGID and LANG_* definitions in winnt.h */
    wLangID = LANG_USER_DEFAULT;
    
    /* 
     * To force a different language, define the language ID as one of the values
     * defined in the Language statement in the .mc file. Alternatively, you
     * can choose a different language in the International applet in the control
     * panel and stick with LANG_USER_DEFAULT. 
     */
    //wLangID = 0x411;


    /* 
     * Output some error messages from the messagetable DLL 
     * The first three have no insert strings 
     */
    myPutMsg(hLib, NULL, MSG_BAD_COMMAND, wLangID);
    myPutMsg(hLib, NULL, MSG_BAD_PARM1, wLangID);
    myPutMsg(hLib, NULL, MSG_STRIKE_ANY_KEY, wLangID);

    
    /* wait for user to hit enter as per last error message */
    getchar();

    
    /* 
     * The next two messages contain insert strings - set up our array 
     * of insert strings and pass the array to myPutMsg() 
     */
    aInsertStrs[0] = TEXT("foo.c");
    aInsertStrs[1] = TEXT("BAR");
    myPutMsg(hLib, aInsertStrs, MSG_CMD_DELETE, wLangID);
    
    aInsertStrs[0] = (PTCHAR) 47;
    aInsertStrs[1] = (PTCHAR) 5;
    myPutMsg(hLib, aInsertStrs, MSG_RETRYS, wLangID);
    return(0);
}
