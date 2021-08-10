/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1999 - 2000 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          Render.cpp

   Description:   

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include <windows.h>
#include <shlobj.h>
#include <strsafe.h>
#define ARRAYSIZE(a)    (sizeof(a)/sizeof(a[0]))
#include "Render.h"

/**************************************************************************
   local function prototypes
**************************************************************************/

LPTSTR GetNextName(LPCTSTR);

/**************************************************************************

   CreateFileGroupDescriptor()

**************************************************************************/

HGLOBAL CreateFileGroupDescriptor(LPCTSTR pszFiles)
{
HGLOBAL              hg;
FILEGROUPDESCRIPTOR  *pfgd;
LPTSTR               pszNext;
DWORD                dwItems;

//get the number of items
for(dwItems = 0, pszNext = (LPTSTR)pszFiles; pszNext; pszNext = GetNextName(pszNext))
   {
   dwItems++;
   }

hg = GlobalAlloc(GMEM_FIXED, sizeof(FILEGROUPDESCRIPTOR) + (dwItems - 1) * sizeof(FILEDESCRIPTOR));
if(hg)
   {
   pfgd = (FILEGROUPDESCRIPTOR*)GlobalLock(hg);
   if(pfgd)
      {
      int   i;

      pfgd->cItems = dwItems;
      
      for(i = 0, pszNext = (LPTSTR)pszFiles; pszNext; pszNext = GetNextName(pszNext), i++)
         {
             pfgd->fgd[i].dwFlags = FD_ATTRIBUTES;
             pfgd->fgd[i].dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
             lstrcpyn(pfgd->fgd[i].cFileName, pszNext, ARRAYSIZE(pfgd->fgd[i].cFileName));
         }
   
      GlobalUnlock(hg);
      }
   }
return hg;
}

/**************************************************************************

   CreateFileContents()

**************************************************************************/

HGLOBAL CreateFileContents(LPCTSTR pszFiles, int nItem)
{
HGLOBAL  hg = NULL;
TCHAR    szText[MAX_PATH];
LPTSTR   pszNext;
int      i, cch;

for(i = 0, pszNext = (LPTSTR)pszFiles; i < nItem; pszNext = GetNextName(pszNext), i++)
   {
   }

StringCchPrintf(szText, ARRAYSIZE(szText), TEXT("This file is %s created from CFSTR_FILECONTENTS"), pszNext);
cch = lstrlen(szText) + 1;
hg = GlobalAlloc(GMEM_FIXED, cch * sizeof(TCHAR));

if(hg)
   {
   LPTSTR psz = (LPSTR)GlobalLock(hg);

   if(psz)
      {
      StringCchCopy(psz, cch, szText);

      GlobalUnlock(hg);
      }
   }

return hg;
}

/**************************************************************************

   GetNextName()

**************************************************************************/

LPTSTR GetNextName(LPCTSTR pszFiles)
{
LPTSTR   pszTemp = (LPTSTR)pszFiles;
while(*pszTemp)
   {
   pszTemp++;
   }

pszTemp++;

return *pszTemp ? pszTemp : NULL;
}

