/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1998 - 2000 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          DropTgt.cpp

   Description:   

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "DropTgt.h"          

/**************************************************************************
   global variables and definitions
**************************************************************************/

extern HWND g_hwndMain;

/**************************************************************************

   CDropTarget::CDropTarget()

**************************************************************************/

CDropTarget::CDropTarget(void)
{
m_cRefCount = 1; 
m_fAcceptFmt = FALSE;
m_pDropTargetHelper = NULL;

CoCreateInstance( CLSID_DragDropHelper,
                  NULL,
                  CLSCTX_INPROC_SERVER,
                  IID_IDropTargetHelper,
                  (LPVOID*)&m_pDropTargetHelper);
}   

/**************************************************************************

   CDropTarget::~CDropTarget()

**************************************************************************/

CDropTarget::~CDropTarget(void)
{
if(m_pDropTargetHelper)
   {
   m_pDropTargetHelper->Release();
   m_pDropTargetHelper = NULL;
   }
}   

///////////////////////////////////////////////////////////////////////////
//
// IUnknown Implementation
//

/**************************************************************************

   CDropTarget::QueryInterface()

**************************************************************************/

STDMETHODIMP CDropTarget::QueryInterface(REFIID riid, LPVOID *ppvOut) 
{
*ppvOut = NULL;

//IUnknown
if(IsEqualIID(riid, IID_IUnknown))
   {
   *ppvOut = this;
   }

//IDropTarget
else if(IsEqualIID(riid, IID_IDropTarget))
   {
   *ppvOut = (IDropTarget*)this;
   }

if(*ppvOut)
   {
   (*(LPUNKNOWN*)ppvOut)->AddRef();
   return S_OK;
   }

return E_NOINTERFACE;
}

/**************************************************************************

   CDropTarget::AddRef()

**************************************************************************/

STDMETHODIMP_(ULONG) CDropTarget::AddRef(void)
{
return ++m_cRefCount;
}

/**************************************************************************

   CDropTarget::Release()

**************************************************************************/

STDMETHODIMP_(ULONG) CDropTarget::Release(void)
{
if(--m_cRefCount == 0)
   {
   delete this;
   return 0;
   }
   
return m_cRefCount;
}  

///////////////////////////////////////////////////////////////////////////
//
// IDropTarget Implementation
//

/**************************************************************************

   CDropTarget::DragEnter()

**************************************************************************/

STDMETHODIMP CDropTarget::DragEnter(   LPDATAOBJECT pDataObj, 
                                       DWORD grfKeyState, 
                                       POINTL pt, 
                                       LPDWORD pdwEffect)
{
if(m_pDropTargetHelper)
   m_pDropTargetHelper->DragEnter(g_hwndMain, pDataObj, (LPPOINT)&pt, *pdwEffect);

FORMATETC fe;
       
fe.cfFormat = CF_HDROP;
fe.ptd      = NULL;
fe.dwAspect = DVASPECT_CONTENT;  
fe.lindex   = -1;
fe.tymed    = TYMED_HGLOBAL; 
    
// Does the drag source provide the clipboard format we are looking for?
m_fAcceptFmt = (S_OK == pDataObj->QueryGetData(&fe)) ? TRUE : FALSE;    
    
QueryDrop(grfKeyState, pdwEffect);

return S_OK;
}

/**************************************************************************

   CDropTarget::DragOver()

**************************************************************************/

STDMETHODIMP CDropTarget::DragOver( DWORD grfKeyState, 
                                    POINTL pt, 
                                    LPDWORD pdwEffect)
{
if(m_pDropTargetHelper)
   m_pDropTargetHelper->DragOver((LPPOINT)&pt, *pdwEffect);

QueryDrop(grfKeyState, pdwEffect);

return S_OK;
}

/**************************************************************************

   CDropTarget::DragLeave()

**************************************************************************/

STDMETHODIMP CDropTarget::DragLeave()
{
if(m_pDropTargetHelper)
   m_pDropTargetHelper->DragLeave();

m_fAcceptFmt = FALSE;   
return S_OK;
}

/**************************************************************************

   CDropTarget::Drop()

**************************************************************************/

STDMETHODIMP CDropTarget::Drop(  LPDATAOBJECT pDataObj, 
                                 DWORD grfKeyState, 
                                 POINTL pt, 
                                 LPDWORD pdwEffect)  
{
if(m_pDropTargetHelper)
   m_pDropTargetHelper->Drop(pDataObj, (LPPOINT)&pt, *pdwEffect);

FORMATETC   fe;
STGMEDIUM   sm;
HRESULT     hr = E_FAIL;
     
if(QueryDrop(grfKeyState, pdwEffect))
   {      
   fe.cfFormat = CF_HDROP;
   fe.ptd = NULL;
   fe.dwAspect = DVASPECT_CONTENT;  
   fe.lindex = -1;
   fe.tymed = TYMED_HGLOBAL;       
        
   // User has dropped on us. Get the data from drag source
   hr = pDataObj->GetData(&fe, &sm);
   if(SUCCEEDED(hr))
      {
      // Display the data and release it.
      DisplayFileNames(g_hwndMain, sm.hGlobal);
      
      ReleaseStgMedium(&sm);
      }
   }

*pdwEffect = DROPEFFECT_NONE;

return hr; 
}   

/* OleStdGetDropEffect
** -------------------
**
** Convert a keyboard state into a DROPEFFECT.
**
** returns the DROPEFFECT value derived from the key state.
**    the following is the standard interpretation:
**          no modifier -- Default Drop     (0 is returned)
**          CTRL        -- DROPEFFECT_COPY
**          SHIFT       -- DROPEFFECT_MOVE
**          CTRL-SHIFT  -- DROPEFFECT_LINK
**
**    Default Drop: this depends on the type of the target application.
**    this is re-interpretable by each target application. a typical
**    interpretation is if the drag is local to the same document
**    (which is source of the drag) then a MOVE operation is
**    performed. if the drag is not local, then a COPY operation is
**    performed.
*/
#define OleStdGetDropEffect(grfKeyState)    \
    ( (grfKeyState & MK_CONTROL) ?          \
        ( (grfKeyState & MK_SHIFT) ? DROPEFFECT_LINK : DROPEFFECT_COPY ) :  \
        ( (grfKeyState & MK_SHIFT) ? DROPEFFECT_MOVE : 0 ) )

/**************************************************************************

   CDropTarget::QueryDrop()

**************************************************************************/

BOOL CDropTarget::QueryDrop(DWORD grfKeyState, LPDWORD pdwEffect)
{  
DWORD dwOKEffects = *pdwEffect; 

if(!m_fAcceptFmt)
   {
   *pdwEffect = DROPEFFECT_NONE;
   return FALSE;
   }
     
*pdwEffect = OleStdGetDropEffect(grfKeyState);
if(*pdwEffect == 0) 
   {
   // No modifier keys used by user while dragging. 
   if (DROPEFFECT_COPY & dwOKEffects)
      *pdwEffect = DROPEFFECT_COPY;
   else if (DROPEFFECT_MOVE & dwOKEffects)
      *pdwEffect = DROPEFFECT_MOVE; 
   else if (DROPEFFECT_LINK & dwOKEffects)
      *pdwEffect = DROPEFFECT_LINK; 
   else 
      {
      *pdwEffect = DROPEFFECT_NONE;
      }
   } 
else
   {
   // Check if the drag source application allows the drop effect desired by user.
   // The drag source specifies this in DoDragDrop
   if(!(*pdwEffect & dwOKEffects))
      *pdwEffect = DROPEFFECT_NONE;

   // We don't accept links
   if(*pdwEffect == DROPEFFECT_LINK)
      *pdwEffect = DROPEFFECT_NONE;
   }  

return (DROPEFFECT_NONE == *pdwEffect) ? FALSE : TRUE;
}   

/**************************************************************************

   CDropTarget::DisplayFileNames()

**************************************************************************/

void CDropTarget::DisplayFileNames(HWND hwndOwner, HGLOBAL hgFiles)
{
UINT     i,
         nFiles;
LPTSTR   pszFiles;
UINT     cchSize;

nFiles = DragQueryFile((HDROP)hgFiles, 0xFFFFFFFF, NULL, 0);

// MAX_PATH + 1 for the "\n" at the end of each path, and another 1 for the null terminator
cchSize = nFiles * (MAX_PATH + 1) + 1;
pszFiles = new TCHAR[cchSize];

if(pszFiles)
   {
   LPTSTR   pszTemp;

   for(i = 0, pszTemp = pszFiles; i < nFiles; i++, pszTemp += lstrlen(pszTemp))
      {
      DragQueryFile((HDROP)hgFiles, i, pszTemp, MAX_PATH);
      lstrcat(pszTemp, TEXT("\n")); // we have room for this \n at the end of each path
      }

   SetForegroundWindow(hwndOwner);
   
   MessageBox(hwndOwner, pszFiles, TEXT("Files Dropped"), MB_OK | MB_ICONINFORMATION);
   
   delete [] pszFiles;
   }
}
