/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1998 - 2000 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          PidlMgr.h
   
   Description:   CPidlMgr definitions.

**************************************************************************/

#ifndef PIDLMGR_H
#define PIDLMGR_H

#include <windows.h>
#include <shlobj.h>

/**************************************************************************
   data types
**************************************************************************/

#define MAX_NAME MAX_PATH
#define MAX_DATA 128

typedef struct tagPIDLDATA
   {
   BOOL fFolder;
   /*
   The character types must be the same on all platforms no matter if UNICODE 
   is defined. This allows a PIDL created on one machine to work on another 
   machine that has the extension installed.
   */
   WCHAR wszName[MAX_NAME];
   WCHAR wszData[MAX_DATA];
   }PIDLDATA, FAR *LPPIDLDATA;

/**************************************************************************

   CPidlMgr class definition

**************************************************************************/

class CPidlMgr
{
public:
   CPidlMgr();
   ~CPidlMgr();

   VOID Delete(LPITEMIDLIST);
   LPITEMIDLIST GetNextItem(LPCITEMIDLIST);
   LPITEMIDLIST Copy(LPCITEMIDLIST);
   LPITEMIDLIST CopySingleItem(LPCITEMIDLIST);
   LPITEMIDLIST GetLastItem(LPCITEMIDLIST);
   LPITEMIDLIST Concatenate(LPCITEMIDLIST, LPCITEMIDLIST);
   LPITEMIDLIST CreateFolderPidl(LPCTSTR);
   LPITEMIDLIST CreateItemPidl(LPCTSTR, LPCTSTR);
   
   int GetName(LPCITEMIDLIST, LPTSTR, DWORD);
   int GetRelativeName(LPCITEMIDLIST, LPTSTR, DWORD);
   int GetData(LPCITEMIDLIST, LPTSTR, DWORD);
   BOOL IsFolder(LPCITEMIDLIST);
   int SetData(LPCITEMIDLIST, LPCTSTR);
   UINT GetSize(LPCITEMIDLIST);

private:
   LPMALLOC m_pMalloc;

   LPITEMIDLIST Create(VOID);
   LPPIDLDATA GetDataPointer(LPCITEMIDLIST);
};

#endif   //PIDLMGR_H
