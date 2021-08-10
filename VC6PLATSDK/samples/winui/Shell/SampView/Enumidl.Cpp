/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1998 - 2000 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          EnumIDL.cpp
   
   Description:   Implements IEnumIDList.

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "EnumIDL.h"
#include "ShlFldr.h"
#include <shlwapi.h>

/**************************************************************************

   CEnumIDList::CEnumIDList

**************************************************************************/

CEnumIDList::CEnumIDList(LPCTSTR pszPath, DWORD dwFlags)
{
g_DllRefCount++;

m_pFirst = m_pLast = m_pCurrent = NULL;

m_szPath[0] = 0;
if(pszPath)
   lstrcpyn(m_szPath, pszPath, MAX_PATH);

m_dwFlags = dwFlags;

m_pPidlMgr = new CPidlMgr();
if(!m_pPidlMgr)
   {
   delete this;
   return;
   }

//get the shell's IMalloc pointer
//we'll keep this until we get destroyed
if(FAILED(SHGetMalloc(&m_pMalloc)))
   {
   delete this;
   return;
   }

if(!CreateEnumList())
   {
   delete this;
   return;
   }

m_ObjRefCount = 1;
}

/**************************************************************************

   CEnumIDList::~CEnumIDList

**************************************************************************/

CEnumIDList::~CEnumIDList()
{
DeleteList();

if(m_pMalloc)
   m_pMalloc->Release();

if(m_pPidlMgr)
   delete m_pPidlMgr;

g_DllRefCount--;
}

/**************************************************************************

   CEnumIDList::QueryInterface

**************************************************************************/

STDMETHODIMP CEnumIDList::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
*ppReturn = NULL;

//IUnknown
if(IsEqualIID(riid, IID_IUnknown))
   {
   *ppReturn = this;
   }
   
//IEnumIDList
else if(IsEqualIID(riid, IID_IEnumIDList))
   {
   *ppReturn = (IEnumIDList*)this;
   }   

if(*ppReturn)
   {
   (*(LPUNKNOWN*)ppReturn)->AddRef();
   return S_OK;
   }

return E_NOINTERFACE;
}                                             

/**************************************************************************

   CEnumIDList::AddRef

**************************************************************************/

STDMETHODIMP_(DWORD) CEnumIDList::AddRef()
{
return ++m_ObjRefCount;
}


/**************************************************************************

   CEnumIDList::Release

**************************************************************************/

STDMETHODIMP_(DWORD) CEnumIDList::Release()
{
if(--m_ObjRefCount == 0)
   {
   delete this;
   return 0;
   }
   
return m_ObjRefCount;
}

/**************************************************************************

   CEnumIDList::Next()
   
**************************************************************************/

STDMETHODIMP CEnumIDList::Next(DWORD dwElements, LPITEMIDLIST apidl[], LPDWORD pdwFetched)
{
DWORD    dwIndex;
HRESULT  hr = S_OK;

if(dwElements > 1 && !pdwFetched)
   return E_INVALIDARG;

for(dwIndex = 0; dwIndex < dwElements; dwIndex++)
   {
   //is this the last item in the list?
   if(!m_pCurrent)
      {
      hr =  S_FALSE;
      break;
      }

   apidl[dwIndex] = m_pPidlMgr->Copy(m_pCurrent->pidl);

   m_pCurrent = m_pCurrent->pNext;
   }

if(pdwFetched)
   *pdwFetched = dwIndex;

return hr;
}

/**************************************************************************

   CEnumIDList::Skip()
   
**************************************************************************/

STDMETHODIMP CEnumIDList::Skip(DWORD dwSkip)
{
DWORD    dwIndex;
HRESULT  hr = S_OK;

for(dwIndex = 0; dwIndex < dwSkip; dwIndex++)
   {
   //is this the last item in the list?
   if(!m_pCurrent)
      {
      hr = S_FALSE;
      break;
      }

   m_pCurrent = m_pCurrent->pNext;
   }

return hr;
}

/**************************************************************************

   CEnumIDList::Reset()
   
**************************************************************************/

STDMETHODIMP CEnumIDList::Reset(VOID)
{
m_pCurrent = m_pFirst;

return S_OK;
}

/**************************************************************************

   CEnumIDList::Clone()
   
**************************************************************************/

STDMETHODIMP CEnumIDList::Clone(LPENUMIDLIST *ppEnum)
{
HRESULT  hr = E_OUTOFMEMORY;

*ppEnum = new CEnumIDList(m_szPath, m_dwFlags);

if(*ppEnum)
   {
   LPENUMLIST  pTemp;

   //synchronize the current pointer
   for(pTemp = m_pFirst; pTemp != m_pCurrent; pTemp = pTemp->pNext)
      {
      (*ppEnum)->Skip(1);
      }
   hr = S_OK;
   }

return hr;
}

/**************************************************************************

   CEnumIDList::CreateEnumList()
   
**************************************************************************/

BOOL CEnumIDList::CreateEnumList(VOID)
{
LPITEMIDLIST   pidl;

//enumerate the folders
if(m_dwFlags & SHCONTF_FOLDERS)
   {
   HANDLE            hFind;
   WIN32_FIND_DATA   wfd;
   TCHAR             szTemp[MAX_PATH];

   lstrcpyn(szTemp, m_szPath, ARRAYSIZE(szTemp));
   SmartAppendBackslash(szTemp, ARRAYSIZE(szTemp));
   StrCatBuff(szTemp, TEXT("*.*"), ARRAYSIZE(szTemp));
   
   hFind = FindFirstFile(szTemp, &wfd);

   if(INVALID_HANDLE_VALUE != hFind)
      {
      do
         {
         if((FILE_ATTRIBUTE_DIRECTORY & wfd.dwFileAttributes) && 
            ((wfd.dwFileAttributes & FILTER_ATTRIBUTES) == FILTER_ATTRIBUTES) &&
            lstrcmpi(wfd.cFileName, TEXT(".")) && 
            lstrcmpi(wfd.cFileName, TEXT("..")))
            {
            //We found one of our directories. Make sure it contains a data file.
            TCHAR szFolder[MAX_PATH];
            lstrcpyn(szFolder, wfd.cFileName, ARRAYSIZE(szFolder));

            //build the path of the directory or file found
            lstrcpyn(szTemp, m_szPath, ARRAYSIZE(szTemp));
            SmartAppendBackslash(szTemp, ARRAYSIZE(szTemp));
            StrCatBuff(szTemp, wfd.cFileName, ARRAYSIZE(szTemp));
            SmartAppendBackslash(szTemp, ARRAYSIZE(szTemp));
            StrCatBuff(szTemp, c_szDataFile, ARRAYSIZE(szTemp));
            HANDLE   hDataFile = FindFirstFile(szTemp, &wfd);
            if(INVALID_HANDLE_VALUE != hDataFile)
               {
               FindClose(hDataFile);

               pidl = m_pPidlMgr->CreateFolderPidl(szFolder);

               if(pidl)
                  AddToEnumList(pidl);
               }
            
            }
         }
      while(FindNextFile(hFind, &wfd));
   
      FindClose(hFind);
      }

   }   

//enumerate the non-folder items
if(m_dwFlags & SHCONTF_NONFOLDERS)
   {
   TCHAR    szDataFile[MAX_PATH];
   TCHAR    szKeys[10000] = TEXT("");
   LPTSTR   pStr;

   BuildDataFileName(szDataFile, m_szPath, MAX_PATH);

   //get the items from the [Items] section

   //now enumerate the items in the INI file
   GetPrivateProfileString(   c_szSection, 
                              NULL, 
                              TEXT(""), 
                              szKeys, 
                              sizeof(szKeys), 
                              szDataFile);

   for(pStr = szKeys; *pStr; pStr += lstrlen(pStr) + 1)
      {
      TCHAR szData[MAX_DATA];
   
      GetPrivateProfileString(   c_szSection, 
                                 pStr, 
                                 TEXT(""), 
                                 szData, 
                                 MAX_DATA, 
                                 szDataFile);
   
      pidl = m_pPidlMgr->CreateItemPidl(pStr, szData);

      if(pidl)
         AddToEnumList(pidl);
      }
   }
   
return TRUE;
}

/**************************************************************************

   CEnumIDList::AddToEnumList()
   
**************************************************************************/

BOOL CEnumIDList::AddToEnumList(LPITEMIDLIST pidl)
{
LPENUMLIST  pNew;

pNew = (LPENUMLIST)m_pMalloc->Alloc(sizeof(ENUMLIST));

if(pNew)
   {
   //set the next pointer
   pNew->pNext = NULL;
   pNew->pidl = pidl;

   //is this the first item in the list?
   if(!m_pFirst)
      {
      m_pFirst = pNew;
      m_pCurrent = m_pFirst;
      }

   if(m_pLast)
      {
      //add the new item to the end of the list
      m_pLast->pNext = pNew;
      }
   
   //update the last item pointer
   m_pLast = pNew;

   return TRUE;
   }

return FALSE;
}

/**************************************************************************

   CEnumIDList::DeleteList()
   
**************************************************************************/

BOOL CEnumIDList::DeleteList(VOID)
{
LPENUMLIST  pDelete;

while(m_pFirst)
   {
   pDelete = m_pFirst;
   m_pFirst = pDelete->pNext;

   //free the pidl
   m_pPidlMgr->Delete(pDelete->pidl);
   
   //free the list item
   m_pMalloc->Free(pDelete);
   }

m_pFirst = m_pLast = m_pCurrent = NULL;

return TRUE;
}

