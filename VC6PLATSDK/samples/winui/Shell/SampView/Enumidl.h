/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1998 - 2000 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          EnumIDL.h
   
   Description:   CEnumIDList definitions.

**************************************************************************/

#ifndef ENUMIDLIST_H
#define ENUMIDLIST_H

#include <windows.h>
#include <shlobj.h>

#include "PidlMgr.h"
#include "Utility.h"

/**************************************************************************
   structure defintions
**************************************************************************/

typedef struct tagENUMLIST
   {
   struct tagENUMLIST   *pNext;
   LPITEMIDLIST         pidl;
   }ENUMLIST, FAR *LPENUMLIST;

/**************************************************************************

   CEnumIDList class definition

**************************************************************************/

class CEnumIDList : public IEnumIDList
{
private:
   DWORD       m_ObjRefCount;
   LPMALLOC    m_pMalloc;
   LPENUMLIST  m_pFirst;
   LPENUMLIST  m_pLast;
   LPENUMLIST  m_pCurrent;
   CPidlMgr    *m_pPidlMgr;
   DWORD       m_dwFlags;
   TCHAR       m_szPath[MAX_PATH];
   
public:
   CEnumIDList(LPCTSTR, DWORD);
   ~CEnumIDList();
   
   //IUnknown methods
   STDMETHOD (QueryInterface)(REFIID, LPVOID*);
   STDMETHOD_ (DWORD, AddRef)();
   STDMETHOD_ (DWORD, Release)();
   
   //IEnumIDList
   STDMETHOD (Next) (DWORD, LPITEMIDLIST*, LPDWORD);
   STDMETHOD (Skip) (DWORD);
   STDMETHOD (Reset) (VOID);
   STDMETHOD (Clone) (LPENUMIDLIST*);
   
private:
   BOOL CreateEnumList(VOID);
   BOOL AddToEnumList(LPITEMIDLIST);
   BOOL DeleteList(VOID);
};

#endif   //ENUMIDLIST_H
