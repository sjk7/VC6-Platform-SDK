//****************************************************************************
//  Module:     PLUGTRANSPORT.EXE     
//  File:       UTILS.CPP
//  Content:    
//              
//
//  Copyright (c) Microsoft Corporation 1995-2002
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************


#include "precomp.h"


//****************************************************************************
//
// CLASS RefCount
//
//****************************************************************************

//****************************************************************************
//
//    FUNCTION:   RefCount::RefCount(void)
//
//    PURPOSE:    Construction

//    COMMENTS:
//
//        
//        
//        
//
//****************************************************************************

RefCount::RefCount(void)
{
    m_cRef = 1;
}


//****************************************************************************
//
//    FUNCTION:   RefCount::~RefCount(void)
//
//    PURPOSE:    Destruction

//    COMMENTS:
//      
//
//****************************************************************************

RefCount::~RefCount(void)
{}


//****************************************************************************
//
//    FUNCTION:   ULONG STDMETHODCALLTYPE RefCount::AddRef(void)
//
//    PURPOSE:    Implementetion of AddRef

//    COMMENTS:
//       
//
//****************************************************************************

ULONG STDMETHODCALLTYPE RefCount::AddRef(void)
{
    ASSERT(m_cRef >= 0);

    InterlockedIncrement(&m_cRef);

    return (ULONG) m_cRef;
}


//****************************************************************************
//
//    FUNCTION:   ULONG STDMETHODCALLTYPE RefCount::Release(void)
//
//    PURPOSE:    Implementation of Release

//    COMMENTS:
//      
//
//****************************************************************************

ULONG STDMETHODCALLTYPE RefCount::Release(void)
{
    if (0 == InterlockedDecrement(&m_cRef))
    {
        delete this;
        return 0;
    }

    ASSERT(m_cRef > 0);
    return (ULONG) m_cRef;
}


//****************************************************************************
//
// CLASS CNotify
//
//****************************************************************************

//****************************************************************************
//
//    FUNCTION:   CNotify::CNotify()
//
//    PURPOSE: 

//    COMMENTS:
//     
//
//****************************************************************************

CNotify::CNotify() :
    m_pcnpcnt(NULL),
    m_pcnp(NULL),
    m_dwCookie(0),
    m_pUnk(NULL)
{}


//****************************************************************************
//
//    FUNCTION:   CNotify::~CNotify()
//
//    PURPOSE: 

//    COMMENTS:
//   
//
//****************************************************************************

CNotify::~CNotify()
{
    Disconnect(); // Make sure we're disconnected
}


//****************************************************************************
//
//    FUNCTION:   HRESULT CNotify::Connect(IUnknown *pUnk, REFIID riid, IUnknown *pUnkN)
//
//    PURPOSE: 

//    COMMENTS:
//      
//
//****************************************************************************

HRESULT CNotify::Connect(IUnknown *pUnk, REFIID riid, IUnknown *pUnkN)
{
    HRESULT hr;

    ASSERT(0 == m_dwCookie);
    ASSERT(NULL == m_pcnpcnt);
    ASSERT(NULL == m_pcnp);
    ASSERT(NULL == m_pUnk);

    if (NULL == pUnk)
        return E_POINTER;

    if (NULL == pUnkN)
        return E_POINTER;

    // Get the connection container
    hr = pUnk->QueryInterface(IID_IConnectionPointContainer, (void **)&m_pcnpcnt);
    if (SUCCEEDED(hr))
    {
        // Find an appropriate connection point
        hr = m_pcnpcnt->FindConnectionPoint(riid, &m_pcnp);
        if (SUCCEEDED(hr))
        {
            ASSERT(NULL != m_pcnp);
            // Connect the sink object
            hr = m_pcnp->Advise((IUnknown *)pUnkN, &m_dwCookie);
        }
    }

    if (FAILED(hr))
    {
        m_dwCookie = 0;
    }
    else
    {
        m_pUnk = pUnk; // keep around for caller
        m_pUnk->AddRef();
    }

    return hr;
}


//****************************************************************************
//
//    FUNCTION:   HRESULT CNotify::Disconnect (void)
//
//    PURPOSE: 

//    COMMENTS:
//     
//
//****************************************************************************

HRESULT CNotify::Disconnect (void)
{
    if (0 != m_dwCookie)
    {

        // Disconnect the sink object
        m_pcnp->Unadvise(m_dwCookie);
        m_dwCookie = 0;

        m_pcnp->Release();
        m_pcnp = NULL;

        m_pcnpcnt->Release();
        m_pcnpcnt = NULL;

        m_pUnk->Release();
        m_pUnk = NULL;
    }

    return S_OK;
}


/*****************************************************/
//  BSTR to LPSTR converison functions
/*********************************************************/

//****************************************************************************
//
//    FUNCTION:   BSTR LPSTR2BSTR(LPSTR pszString)
//
//    PURPOSE:    Converts a string to BSTR

//    COMMENTS:
//     
//
//****************************************************************************

BSTR LPSTR2BSTR(LPSTR pszString)
{
    WCHAR wszConnID[CONNIDMAXLENGTH];

    if (::MultiByteToWideChar(CP_ACP, 0, pszString, -1, wszConnID, CONNIDMAXLENGTH))
    {
        return ::SysAllocString(wszConnID);
    }

    return NULL;
}


//****************************************************************************
//
//    FUNCTION:   BOOL BSTR2LPSTR(BSTR bstrConnID, LPSTR pszConnID)
//
//    PURPOSE:    Converts a BSTR to a string

//    COMMENTS:
//      
//
//****************************************************************************

BOOL BSTR2LPSTR(BSTR bstrConnID, LPSTR pszConnID)
{
    *pszConnID = '\0';
    return ::WideCharToMultiByte(CP_ACP, 0, bstrConnID, -1, pszConnID, CONNIDMAXLENGTH, NULL, NULL);
}
