/*----------------------------------------------------------------
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1999 - 2000.  Microsoft Corporation.  All rights reserved.

----------------------------------------------------------------*/

// it is assumed that windows.h and tchar.h have been included before this file

#if !defined(_FINDSTREAM_H)

   #define _FINDSTREAM_H

   #pragma once

typedef struct _STREAM_FIND_DATA
{
   LARGE_INTEGER Size;
   TCHAR cStreamName[MAX_PATH];
} STREAM_FIND_DATA, *LPSTREAM_FIND_DATA;

HANDLE FindFirstStream(LPCTSTR lpFileName, LPSTREAM_FIND_DATA lpFindStreamData);
BOOL FindNextStream(HANDLE hFindStream, LPSTREAM_FIND_DATA lpFindStreamData);
BOOL FindCloseStream(HANDLE hFindStream);

#endif
