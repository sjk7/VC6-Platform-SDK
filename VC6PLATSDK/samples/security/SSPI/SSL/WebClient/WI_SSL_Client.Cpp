
/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1999 - 2000  Microsoft Corporation.  All rights reserved.

Module Name:

    WI_SSL_Client.c

Abstract:

    Companion module for WebServer/WebClient sample that shows an
    alternate method of interacting with the WebServer. This module
    demonstrates how to use the WinInet APIs to make a secure
    connection with the server application.

Revision History:

    4-1-99  davemo     created

Required Libraries:
    
    wininet.lib
    user32.lib

--*/

#include <windows.h>
#include <wininet.h>
#include <stdio.h>

void main(int argc, char *argv[])
{

    if(argc<2)
    {
        printf("USAGE: %s [webserver]\n", argv[0]);
        return;
    }

    // Open Internet session.
    HINTERNET hSession = InternetOpen(
                            "Wininet Client App",
                            PRE_CONFIG_INTERNET_ACCESS,
                            NULL, 
                            INTERNET_INVALID_PORT_NUMBER,
                            0) ;

    // Connect to server\website.
    // NOTE: There must be a client authentication certificate
    // available that corresponds to the name of the server or 
    // website that you are connecting to.
    // For instance, if I am running WebServer on machine davemo1,
    // then I can specify "davemo1" as the webserver. I must have a
    // client authentication certificate available 
    HINTERNET hConnect = InternetConnect(
                            hSession,
                            argv[1],
                            INTERNET_DEFAULT_HTTPS_PORT,
                            "",
                            "",
                            INTERNET_SERVICE_HTTP,
                            0,
                            0) ;



    // Request the file default.htm from the server.
    HINTERNET hHttpFile = HttpOpenRequest(
                            hConnect,
                            "GET",
                            "default.htm",
                            HTTP_VERSION,
                            "",
                            NULL,
                            INTERNET_FLAG_SECURE,
                            0) ;

    //
    // Send the request and check for success
    //
    while(!HttpSendRequest(hHttpFile, NULL, 0, 0, 0))
    {

        // If the server requires a client certificate I'll invoke
        // this nifty dialogue to select a certificate and
        // reset the options for the request.

        printf("HttpSendRequest error : (%lu)\n", GetLastError());

        InternetErrorDlg (
            GetDesktopWindow(),
            hHttpFile,
            ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED,
            FLAGS_ERROR_UI_FILTER_FOR_ERRORS |
            FLAGS_ERROR_UI_FLAGS_GENERATE_DATA |
            FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS,
            NULL);


    }

    // Get the length of the file.            
    char bufQuery[32] ;

    DWORD dwLengthBufQuery;
    dwLengthBufQuery = sizeof(bufQuery);

    DWORD dwIndex;
    dwIndex=0;

    BOOL bQuery;
    
    bQuery = HttpQueryInfo(
                hHttpFile,
                HTTP_QUERY_CONTENT_LENGTH, 
                bufQuery, 
                &dwLengthBufQuery,
                &dwIndex) ;

    if(!bQuery)
        printf("HttpQueryInfo error : <%lu>\n", GetLastError());


    // Convert length from ASCII string to a DWORD.
    DWORD dwFileSize;
    
    dwFileSize = (DWORD)atol(bufQuery) ;

    // Allocate a buffer for the file.   
    char* buffer;
    
    buffer = new char[dwFileSize+1] ;

    printf("Trying to read %lu bytes from the server\n", dwFileSize);

    // Read the file into the buffer. 
    DWORD dwBytesRead ;
    BOOL bRead;
    
    bRead = InternetReadFile(
                hHttpFile,
                buffer,
                dwFileSize+1, 
                &dwBytesRead);

    if(!bRead)
    {
        printf("InternetReadFile error : <%lu>\n", GetLastError());
    }
    else
    {
        // Put a zero on the end of the buffer.
        buffer[dwBytesRead] = 0 ;

        // Print the buffer contents.
        printf("Retrieved %lu data bytes: %s\n", dwBytesRead, buffer) ;
    }

    // Close all of the Internet handles.
    InternetCloseHandle(hHttpFile); 
    InternetCloseHandle(hConnect) ;
    InternetCloseHandle(hSession) ;


}