/*----------------------------------------------------------------
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1999 - 2000.  Microsoft Corporation.  All rights reserved.

enumstreams.c

This file contains code that demonstrates using the FindxxxStream
functions implemented by findstream.c.

----------------------------------------------------------------*/

#ifdef _IA64_
#pragma warning(disable: 4127)
#endif

#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#include "findstream.h"

int _tmain(int argc, TCHAR *argv[])
{
   HANDLE hFindStream;
   STREAM_FIND_DATA ffStream;

   if (argc < 2)
   {
      _tprintf(_T("usage: enumstreams file_name\n"));
      return 1;
   }

   hFindStream = FindFirstStream(argv[1], &ffStream);
   if (hFindStream == INVALID_HANDLE_VALUE)
   {
      _tprintf(_T("Cannot get list of streams.  LastError = %d\n"),
               GetLastError());
      return 2;
   }

   // Enumerate the streams
   while (1)
   {
      _tprintf(_T("stream '%s' of size %I64u\n"),
               ffStream.cStreamName,
               ffStream.Size);

      if (!FindNextStream(hFindStream, &ffStream))
         if (GetLastError() == ERROR_NO_MORE_FILES)
            break;
         else
         {
            _tprintf(_T("Error getting next stream data %u\n"),
                     GetLastError());
            break;
         }
   }

   // Close the handle
   FindCloseStream(hFindStream);

   return 0;
}
