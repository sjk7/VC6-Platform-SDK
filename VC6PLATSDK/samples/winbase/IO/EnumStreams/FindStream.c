/*----------------------------------------------------------------
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1999 - 2000.  Microsoft Corporation.  All rights reserved.

findstream.c

This file contains the FindFirstStream, FindNextStream,
FindCloseStream functions used to enumerate streams in files.
----------------------------------------------------------------*/

#include <windows.h>
#include <tchar.h>

#ifndef UNICODE
   #include <stdio.h>
#endif

#include "findstream.h"

// FFSTREAMMAGIC is a magic number used to identify a block of memory as FFSTREAM type
#define FFSTREAMMAGIC 0x54534646

// FFSTREAM is used to track where we are in the process of enumerating streams.
typedef struct _FFSTREAM
{
   DWORD   dwFFStreamMagic;
   HANDLE  hFile;
   LPVOID  lpContext;
} FFSTREAM, *LPFFSTREAM;

#define lenof(x)  ((sizeof(x) / sizeof(TCHAR)) - 1)

// DATASTUFFIX is a suffix at the end of stream names returned from BackupRead
#define DATASUFFIX  _T(":$DATA")

/*----------------------------------------------------------------
ffproc(LPFFSTREAM lpFFStream, LPSTREAM_FIND_DATA lpFindStreamData)

This function is the core function used by FindFirstStream and FindNextStream.
Its purpose is to use BackupRead to read the stream header and get the stream
name.  It will then skip the data portion of the backup stream using BackupSeek.
It returns once it finds a backup stream of type ID BACKUP_DATA or
BACKUP_ALTERNATE_DATA or when there is no more data to read.

lpFFStream
    Buffer used internally by FindxxxStream to keep track of
    context.
lpFindStreamData
    Buffer passed thru FindxxxStream used to return stream
    information to the caller

Returns TRUE if successful, FALSE if not.

On failure GetLastError can return:

ERROR_NO_MORE_FILES
    There are no more stream in the file
ERROR_READ_FAULT
    BackupRead returned an error
ERROR_OUTOFMEMROY
   Could not allocate memory to hold internal status information

----------------------------------------------------------------*/

static BOOL ffproc(LPFFSTREAM lpFFStream, LPSTREAM_FIND_DATA lpFindStreamData)
{
   WIN32_STREAM_ID BackupStreamHeader;
   LPWSTR lpStreamName;
   DWORD dwLoToSeek, dwHiToSeek;
   DWORD dwLoSeek, dwHiSeek;
   DWORD dwToRead, dwRead;
   BOOL bFoundDataStream;

   // Enumerate the streams now
   // we loop here until we get a stream with ID BACKUP_DATA or
   // BACKUP_ALTERNATE_DATA
   bFoundDataStream = FALSE;
   while (!bFoundDataStream)
   {
      // Read the backup stream header
      // We read up to the stream name
      dwToRead = (DWORD)((LPBYTE)&(BackupStreamHeader.cStreamName[0]) -
                 (LPBYTE)&BackupStreamHeader.dwStreamId);

      if (!BackupRead(lpFFStream->hFile, (BYTE *)&BackupStreamHeader, dwToRead,
                      &dwRead, FALSE, TRUE, &(lpFFStream->lpContext)))
      {
         SetLastError(ERROR_READ_FAULT);
         return FALSE;
      }

      if (dwRead == 0)
      {
         SetLastError(ERROR_NO_MORE_FILES);
         return FALSE;
      }

      // if there is a stream name (length > 0), then process it
      if (BackupStreamHeader.dwStreamNameSize > 0)
      {
         // the stream name is a Unicode string.  BackupRead returns the
         // stream name length in bytes.

         // allocate enough memory to hold the stream name (including the
         // terminating null)
         if ((lpStreamName = (LPWSTR)HeapAlloc(GetProcessHeap(), 0,
                                               BackupStreamHeader.dwStreamNameSize +
                                               sizeof(WCHAR))) == NULL)
         {
            SetLastError(ERROR_OUTOFMEMORY);
            return FALSE;
         }


         if (!BackupRead(lpFFStream->hFile, (LPBYTE)lpStreamName,
                         BackupStreamHeader.dwStreamNameSize, &dwRead, FALSE, TRUE,
                         &(lpFFStream->lpContext)))
         {
            SetLastError(ERROR_READ_FAULT);
            return FALSE;
         }

         // Fill in the terminating nul for the string
         lpStreamName[BackupStreamHeader.dwStreamNameSize / sizeof(WCHAR)] =
         _T('\0');
      }
      else
         lpStreamName = L"";


      if (BackupStreamHeader.dwStreamId == BACKUP_DATA ||
          BackupStreamHeader.dwStreamId == BACKUP_ALTERNATE_DATA)
      {
         bFoundDataStream = TRUE;

         // Record the size of the stream in structure passed by caller
         lpFindStreamData->Size.QuadPart = BackupStreamHeader.Size.QuadPart;

#ifdef UNICODE
         // if Unicode, then copy the name to the structure passed by caller
         lstrcpy(lpFindStreamData->cStreamName, lpStreamName);
#else
         // if ANSI then convert the name into the structure passed by caller.
         // Because the source string is NULL terminated, we can pass -1 
         // as the string length and rely on the conversion function to
         // calculate the string length, including the NULL terminator.
         WideCharToMultiByte(CP_ACP, 0, lpStreamName, -1,
                             lpFindStreamData->cStreamName,
                             sizeof(lpFindStreamData->cStreamName), NULL, NULL);
#endif

         // remove :$DATA at end...  
         if (lstrcmp(lpFindStreamData->cStreamName +
                     lstrlen(lpFindStreamData->cStreamName) -
                     lenof(DATASUFFIX),
                     DATASUFFIX) == 0)
         {
            lpFindStreamData->cStreamName[
                                         lstrlen(lpFindStreamData->cStreamName) -
                                         lenof(DATASUFFIX)] = _T('\0');
         }

         // remove : at beginning. 
         // Use MoveMemory here because the source and destination overlap.
         if (*lpFindStreamData->cStreamName == _T(':'))
            MoveMemory(lpFindStreamData->cStreamName,
                       lpFindStreamData->cStreamName + 1,
                       sizeof(lpFindStreamData->cStreamName) - 1);
      }

      // if the stream had a name, then free the memory used to hold it
      if (BackupStreamHeader.dwStreamNameSize > 0)
         HeapFree(GetProcessHeap(), 0, lpStreamName);

      // Skip the stream data
      dwLoToSeek = BackupStreamHeader.Size.LowPart;
      dwHiToSeek = BackupStreamHeader.Size.HighPart;
      if (!BackupSeek(lpFFStream->hFile, dwLoToSeek, dwHiToSeek, &dwLoSeek,
                      &dwHiSeek, &(lpFFStream->lpContext)))
      {
         SetLastError(ERROR_READ_FAULT);
         return FALSE;
      }
   }

   return TRUE;
}

/*----------------------------------------------------------------
FindFirstStream(LPCTSTR lpFileName,
                LPSTREAM_FIND_DATA lpFindStreamData)

The FindFirstStream function enumerates the streams contained in the
file specified by lpFileName.  Use FindNextStream to continue
enumerating streams.  Use FindCloseStream when done.

lpFileName
    Null terminated string contains the name of file to enumerate
    streams
lpFindStreamData
    Buffer used to return stream information to the caller

Returns INVALID_HANDLE_VALUE if it fails, a HANDLE otherwise

On failure GetLastError can return:

ERROR_FILE_NOT_FOUND
   The file does not exist or it does not contain any streams.
   Note that empty files do not contain any streams.
ERROR_READ_FAULT
   Could not read the names of the streams
ERROR_OUTOFMEMROY
   Could not allocate memory to hold internal status information

Other error codes could be passed from lower level APIs
----------------------------------------------------------------*/

HANDLE FindFirstStream(LPCTSTR lpFileName, LPSTREAM_FIND_DATA lpFindStreamData)
{
   LPFFSTREAM lpFFStream;

   if ((lpFFStream = HeapAlloc(GetProcessHeap(), 0, sizeof(FFSTREAM))) == NULL)
   {
      SetLastError(ERROR_OUTOFMEMORY);
      return INVALID_HANDLE_VALUE;
   }

   // set the magic number which mark the handle as valid...
   lpFFStream->dwFFStreamMagic = FFSTREAMMAGIC;
   lpFFStream->lpContext = NULL;

   if ((lpFFStream->hFile = CreateFile(lpFileName, GENERIC_READ,
                                       FILE_SHARE_READ | FILE_SHARE_WRITE,
                                       NULL, OPEN_EXISTING,
                                       FILE_FLAG_BACKUP_SEMANTICS, NULL)) ==
       INVALID_HANDLE_VALUE)
   {
      HeapFree(GetProcessHeap(), 0, lpFFStream);
      // pass on error from CreateFile...
      return INVALID_HANDLE_VALUE;
   }

   if (!ffproc(lpFFStream, lpFindStreamData))
   {
      // free resource on failure...
      CloseHandle(lpFFStream->hFile);

      HeapFree(GetProcessHeap(), 0, lpFFStream);

      // pass on error...
      if (GetLastError() == ERROR_NO_MORE_FILES)
         SetLastError(ERROR_FILE_NOT_FOUND);
      return INVALID_HANDLE_VALUE;
   }

   return (HANDLE)lpFFStream;
}

/*----------------------------------------------------------------
FindNextStream(HANDLE hFindStream,
                LPSTREAM_FIND_DATA lpFindStreamData)

The FindNextStream function continues enumerating the streams
specified by hFindStream.  Use FindFirstStream to start the
enumeration.  Use FindCloseStream when done.

hFindStream
    Handle returned from FindFirstStream
lpFindStreamData
    Buffer used to return stream information to the caller

Returns TRUE if it succeeds, FALSE otherwise.

On failure GetLastError can return:

ERROR_INVALID_HANDLE
    The passed handle was not created using FindFirstStream or
    was closed already.
ERROR_NO_MORE_FILES
    There are no more stream in the file
ERROR_READ_FAULT
    There was a problem reading stream names using the Backup
    APIs.
ERROR_OUTOFMEMROY
    Could not allocate memory to hold internal status information

----------------------------------------------------------------*/

BOOL FindNextStream(HANDLE hFindStream, LPSTREAM_FIND_DATA lpFindStreamData)
{
   LPFFSTREAM lpFFStream = (LPFFSTREAM)hFindStream;

   // verify that the passed structure is a FFSTREAM structure...
   if (lpFFStream->dwFFStreamMagic != FFSTREAMMAGIC)
   {
      SetLastError(ERROR_INVALID_HANDLE);
      return FALSE;
   }

   if (!ffproc(lpFFStream, lpFindStreamData))
   {
      // pass on error...
      return FALSE;
   }

   return TRUE;
}

/*----------------------------------------------------------------
FindCloseStream(HANDLE hFindStream)

The FindCloseStream function releases the resources used to
enumerate the streams specified by hFindStream.  Use FindFirstStream
to start the enumeration.

hFindStream
    Handle returned from FindFirstStream

Returns TRUE if it succeeds, FALSE otherwise.

On failure GetLastError can return:

ERROR_INVALID_HANDLE
    The passed handle was not created using FindFirstStream or
    was closed already.

----------------------------------------------------------------*/
BOOL FindCloseStream(HANDLE hFindStream)
{
   LPFFSTREAM lpFFStream = (LPFFSTREAM)hFindStream;

   // verify that the passed structure is a FFSTREAM structure...
   if (lpFFStream->dwFFStreamMagic != FFSTREAMMAGIC)
   {
      SetLastError(ERROR_INVALID_HANDLE);
      return FALSE;
   }

   // Release the context memory
   BackupRead(0, NULL, 0, NULL, TRUE, FALSE, &(lpFFStream->lpContext));

   // Close the file handle
   CloseHandle(lpFFStream->hFile);

   // obliterate the magic number of handle making it invalid...
   lpFFStream->dwFFStreamMagic = 0;

   // Free the handle...
   HeapFree(GetProcessHeap(), 0, lpFFStream);

   return TRUE;
}
