//+--------------------------------------------------------------------------
//
// Microsoft Windows
// Copyright (C) Microsoft Corporation, 1996 - 2000
//
// File:        exit.cpp
//
// Contents:    CCertExitSample implementation
//
//---------------------------------------------------------------------------

#include "pch.cpp"
#pragma hdrstop

#include <stdio.h>
#include <assert.h>
#include "celibw2k.h"
#include "exit.h"
#include "module.h"

#ifndef szOID_CERTTYPE_EXTENSION
# define szOID_CERTTYPE_EXTENSION szOID_ENROLL_CERTTYPE_EXTENSION
#endif

BOOL fDebug = DBG_CERTSRV;

#ifndef DBG_CERTSRV
#error -- DBG_CERTSRV not defined!
#endif

#define ceEXITEVENTS \
	EXITEVENT_CERTISSUED | \
	EXITEVENT_CERTPENDING | \
	EXITEVENT_CERTDENIED | \
	EXITEVENT_CERTREVOKED | \
	EXITEVENT_CERTRETRIEVEPENDING | \
	EXITEVENT_CRLISSUED | \
	EXITEVENT_SHUTDOWN

#define CERTTYPE_ATTR_NAME TEXT("CertificateTemplate")
#define wszCertFile TEXT("CertFile")
#define MAX_CRL_PROP (32 + 10)

extern HINSTANCE g_hInstance;


// worker
HRESULT
GetServerCallbackInterface(
    OUT ICertServerExit** ppServer,
    IN LONG Context)
{
    HRESULT hr;

    if (NULL == ppServer)
    {
        hr = E_POINTER;
	_JumpError(hr, error, "Exit:NULL pointer");
    }

    hr = CoCreateInstance(
                    CLSID_CCertServerExit,
                    NULL,               // pUnkOuter
                    CLSCTX_INPROC_SERVER,
                    IID_ICertServerExit,
                    (VOID **) ppServer);
    _JumpIfError(hr, error, "Exit:CoCreateInstance");

    if (*ppServer == NULL)
    {
        hr = E_UNEXPECTED;
	_JumpError(hr, error, "Exit:NULL *ppServer");
    }

    // only set context if nonzero
    if (0 != Context)
    {
        hr = (*ppServer)->SetContext(Context);
        _JumpIfError(hr, error, "Exit: SetContext");
    }

error:
    return hr;
}


//+--------------------------------------------------------------------------
// CCertExitSample::~CCertExitSample -- destructor
//
// free memory associated with this instance
//+--------------------------------------------------------------------------

CCertExitSample::~CCertExitSample()
{
    if (NULL != m_strCAName)
    {
        SysFreeString(m_strCAName);
    }
    if (NULL != m_wszRegStorageLoc)
    {
        LocalFree(m_wszRegStorageLoc);
    }
    if (NULL != m_hExitKey)
    {
        RegCloseKey(m_hExitKey);
    }
    if (NULL != m_bstrDescription)
    {
        SysFreeString(m_bstrDescription);
    }

}


//+--------------------------------------------------------------------------
// CCertExitSample::Initialize -- initialize for a CA & return interesting Event Mask
//
// Returns S_OK on success.
//+--------------------------------------------------------------------------

STDMETHODIMP
CCertExitSample::Initialize(
    /* [in] */ BSTR const strConfig,
    /* [retval][out] */ LONG __RPC_FAR *pEventMask)
{
    HRESULT hr = S_OK;
    HKEY        hkey = NULL;
    DWORD       cbbuf;
    DWORD       dwType;
    ENUM_CATYPES CAType;
    LPWSTR      pwszCLSIDCertExit = NULL;
    ICertServerExit* pServer = NULL;
    VARIANT varValue;
    
    WCHAR sz[MAX_PATH];

    assert(wcslen(wsz_SAMPLE_DESCRIPTION) < ARRAYSIZE(sz));
    wcscpy(sz, wsz_SAMPLE_DESCRIPTION);

    m_bstrDescription = SysAllocString(sz);
    if (NULL == m_bstrDescription)
    {
        hr = E_OUTOFMEMORY;
        _JumpError(hr, error, "Exit:SysAllocString");
    }


    VariantInit(&varValue);

    m_strCAName = SysAllocString(strConfig);
    if (NULL == m_strCAName)
    {
    	hr = E_OUTOFMEMORY;
        _JumpError(hr, error, "Exit:SysAllocString");
    }

    *pEventMask = ceEXITEVENTS;
    DBGPRINT((fDebug, "Exit:Initialize(%ws) ==> %x\n", m_strCAName, *pEventMask));


    // get server callbacks
    hr = GetServerCallbackInterface(&pServer, 0);
    _JumpIfError(hr, error, "Exit:GetServerCallbackInterface");

    // get storage location
    hr = pServer->GetCertificateProperty(wszPROPMODULEREGLOC, PROPTYPE_STRING, &varValue);
    _JumpIfErrorStr(hr, error, "Exit:GetCertificateProperty", wszPROPMODULEREGLOC);
    
    m_wszRegStorageLoc = (LPWSTR)LocalAlloc(LMEM_FIXED, (wcslen(varValue.bstrVal)+1) *sizeof(WCHAR));
    if (NULL == m_wszRegStorageLoc)
    {
        hr = E_OUTOFMEMORY;
        _JumpError(hr, error, "Exit:LocalAlloc");
    }
    wcscpy(m_wszRegStorageLoc, varValue.bstrVal);
    VariantClear(&varValue);

    // get CA type
    hr = pServer->GetCertificateProperty(wszPROPCATYPE, PROPTYPE_LONG, &varValue);
    _JumpIfErrorStr(hr, error, "Exit:GetCertificateProperty", wszPROPCATYPE);

    CAType = (ENUM_CATYPES)varValue.lVal;
    VariantClear(&varValue);

    hr = RegOpenKeyEx(
                HKEY_LOCAL_MACHINE,
                m_wszRegStorageLoc,
                0,              // dwReserved
                KEY_ENUMERATE_SUB_KEYS | KEY_EXECUTE | KEY_QUERY_VALUE,
                &m_hExitKey);

    if (S_OK != hr)
    {
        if (ERROR_FILE_NOT_FOUND == hr)
        {
            hr = S_OK;
            goto error;
        }
        _JumpError(hr, error, "Exit:RegOpenKeyEx");
    }


    // Initialize the revocation information

    hr = pServer->GetCertificateProperty(wszPROPCERTCOUNT, PROPTYPE_LONG, &varValue);
    _JumpIfErrorStr(hr, error, "Exit:GetCertificateProperty", wszPROPCERTCOUNT);

    m_cCACert = varValue.lVal;



    cbbuf = sizeof(m_cCRLPublishRetryCount);
    hr = RegQueryValueEx(
		    m_hExitKey,
		    wszCRLPUBLISHRETRYCOUNT,
		    NULL,           // lpdwReserved
		    &dwType,
		    (BYTE *) &m_cCRLPublishRetryCount,
		    &cbbuf);
    if (S_OK != hr)
    {
        m_cCRLPublishRetryCount = CRL_PUBLISH_RETRY_DEFAULT;
    }

    cbbuf = sizeof(m_dwExitPublishFlags);
    hr = RegQueryValueEx(
		    m_hExitKey,
		    wszREGCERTPUBLISHFLAGS,
		    NULL,           // lpdwReserved
		    &dwType,
		    (BYTE *) &m_dwExitPublishFlags,
		    &cbbuf);
    if (S_OK != hr)
    {
        m_dwExitPublishFlags = 0;
    }
    hr = S_OK;

error:
    if (NULL != hkey)
    {
        RegCloseKey(hkey);
    }
    VariantClear(&varValue);
    if (NULL != pServer)
    {
        pServer->Release();
    }
    return(ceHError(hr));
}


//+--------------------------------------------------------------------------
// CCertExitSample::_ExpandEnvironmentVariables -- Expand environment variables
//
//+--------------------------------------------------------------------------

HRESULT
CCertExitSample::_ExpandEnvironmentVariables(
    IN WCHAR const *pwszIn,
    OUT WCHAR *pwszOut,
    IN DWORD cwcOut)
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_BUFFER_OVERFLOW);
    WCHAR awcVar[MAX_PATH];
    WCHAR const *pwszSrc;
    WCHAR *pwszDst;
    WCHAR *pwszDstEnd;
    WCHAR *pwszVar;
    DWORD cwc;

    pwszSrc = pwszIn;
    pwszDst = pwszOut;
    pwszDstEnd = &pwszOut[cwcOut];

    while (L'\0' != (*pwszDst = *pwszSrc++))
    {
	if ('%' == *pwszDst)
	{
	    *pwszDst = L'\0';
	    pwszVar = awcVar;

	    while (L'\0' != *pwszSrc)
	    {
		if ('%' == *pwszSrc)
		{
		    pwszSrc++;
		    break;
		}
		*pwszVar++ = *pwszSrc++;
		if (pwszVar >= &awcVar[sizeof(awcVar)/sizeof(awcVar[0]) - 1])
		{
		    _JumpError(hr, error, "Exit:overflow 1");
		}
	    }
	    *pwszVar = L'\0';
	    cwc = (DWORD)GetEnvironmentVariable(awcVar, pwszDst, (DWORD)SAFE_SUBTRACT_POINTERS(pwszDstEnd, pwszDst));
	    if (0 == cwc)
	    {
		hr = ceHLastError();
		_JumpError(hr, error, "Exit:GetEnvironmentVariable");
	    }
	    if ((DWORD) (pwszDstEnd - pwszDst) <= cwc)
	    {
		_JumpError(hr, error, "Exit:overflow 2");
	    }
	    pwszDst += cwc;
	}
	else
	{
	    pwszDst++;
	}
	if (pwszDst >= pwszDstEnd)
	{
	    _JumpError(hr, error, "Exit:overflow 3");
	}
    }
    hr = S_OK;

error:
    return(hr);
}


//+--------------------------------------------------------------------------
// CCertExitSample::_WriteCertToFile -- write binary certificate to a file
//
//+--------------------------------------------------------------------------

HRESULT
CCertExitSample::_WriteCertToFile(
    IN ICertServerExit *pServer,
    IN BYTE const *pbCert,
    IN DWORD cbCert)
{
    HRESULT hr;
    BSTR strCertFile = NULL;
    DWORD cbWritten;
    HANDLE hFile = INVALID_HANDLE_VALUE;
    WCHAR wszPath[MAX_PATH];
    WCHAR const *pwszFile;
    WCHAR const *pwsz;


    hr = pServer->GetRequestAttribute(wszCertFile, &strCertFile);
    if (S_OK != hr)
    {
	DBGPRINT((
	    fDebug,
	    "Exit:GetRequestAttribute(%ws): %x%s\n",
	    wszCertFile,
	    hr,
	    CERTSRV_E_PROPERTY_EMPTY == hr? " EMPTY VALUE" : ""));
	if (CERTSRV_E_PROPERTY_EMPTY == hr)
	{
	    hr = S_OK;
	}
	goto error;
    }

    pwszFile = wcsrchr(strCertFile, L'\\');
    if (NULL == pwszFile)
    {
	pwszFile = strCertFile;
    }
    else
    {
	pwszFile++;
    }
    pwsz = wcsrchr(pwszFile, L'/');
    if (NULL != pwsz)
    {
	pwszFile = &pwsz[1];
    }

    hr = _ExpandEnvironmentVariables(
		    L"%SystemRoot%\\System32\\" wszCERTENROLLSHAREPATH L"\\",
		    wszPath,
		    ARRAYSIZE(wszPath));
    _JumpIfError(hr, error, "_ExpandEnvironmentVariables");

    if (ARRAYSIZE(wszPath) <= wcslen(wszPath) + wcslen(pwszFile))
    {
	hr = HRESULT_FROM_WIN32(ERROR_BUFFER_OVERFLOW);
	_JumpError(hr, error, "Exit:Path too long");
    }
    wcscat(wszPath, pwszFile);

    // open file & write binary cert out.

    hFile = CreateFile(
		    wszPath,
		    GENERIC_WRITE,
		    0,			// dwShareMode
		    NULL,		// lpSecurityAttributes
		    CREATE_NEW,
		    FILE_ATTRIBUTE_NORMAL,
		    NULL);		// hTemplateFile
    if (INVALID_HANDLE_VALUE == hFile)
    {
	hr = ceHLastError();
	_JumpErrorStr(hr, error, "Exit:CreateFile", wszPath);
    }
    if (!WriteFile(hFile, pbCert, cbCert, &cbWritten, NULL))
    {
	hr = ceHLastError();
	_JumpErrorStr(hr, error, "Exit:WriteFile", wszPath);
    }
    if (cbWritten != cbCert)
    {
	hr = STG_E_WRITEFAULT;
	DBGPRINT((
	    fDebug,
	    "Exit:WriteFile(%ws): attempted %x, actual %x bytes: %x\n",
	    wszPath,
	    cbCert,
	    cbWritten,
	    hr));
	goto error;
    }

error:

    if (INVALID_HANDLE_VALUE != hFile)
    {
	CloseHandle(hFile);
    }
    if (NULL != strCertFile)
    {
	SysFreeString(strCertFile);
    }
    return(hr);
}


//+--------------------------------------------------------------------------
// CCertExitSample::_NotifyNewCert -- Notify the exit module of a new certificate
//
//+--------------------------------------------------------------------------

HRESULT
CCertExitSample::_NotifyNewCert(
    /* [in] */ LONG Context)
{
    HRESULT hr;
    HRESULT hr2;
    VARIANT varCert;
    VARIANT varExt;
    ICertServerExit *pServer = NULL;
    BSTR strCertType = NULL;
    CERT_NAME_VALUE *pName = NULL;
    DWORD cbType;

    VariantInit(&varCert);
    VariantInit(&varExt);
    hr = CoCreateInstance(
		    CLSID_CCertServerExit,
		    NULL,               // pUnkOuter
		    CLSCTX_INPROC_SERVER,
		    IID_ICertServerExit,
		    (VOID **) &pServer);
    _JumpIfError(hr, error, "Exit:CoCreateInstance");

    hr = pServer->SetContext(Context);
    _JumpIfError(hr, error, "Exit:SetContext");

    hr = pServer->GetCertificateProperty(
			       wszPROPRAWCERTIFICATE,
			       PROPTYPE_BINARY,
			       &varCert);
    _JumpIfErrorStr(hr, error, "Exit:GetCertificateProperty", wszPROPRAWCERTIFICATE);

    if (VT_BSTR != varCert.vt)
    {
	hr = HRESULT_FROM_WIN32(ERROR_INVALID_DATA);
	_JumpError(hr, error, "Exit:BAD cert var type");
    }

    hr = pServer->GetCertificateExtension(
                                    TEXT(szOID_CERTTYPE_EXTENSION),
                                    PROPTYPE_BINARY,
                                    &varExt);
    if (S_OK == hr)
    {
        // There was a cert type indicator.
        // varExt points to an encoded string

        if (VT_BSTR != varExt.vt)
	{
	    hr = HRESULT_FROM_WIN32(ERROR_INVALID_DATA);
	    _JumpError(hr, error, "Exit:BAD var type");
	}
        if (!ceDecodeObject(
			X509_ASN_ENCODING,
			X509_UNICODE_ANY_STRING,
			(BYTE *) varExt.bstrVal,
			SysStringByteLen(varExt.bstrVal),
			FALSE,
			(VOID **) &pName,
			&cbType))
        {
	    hr = ceHLastError();
	    _JumpError(hr, error, "Exit:ceDecodeObject");
        }
        strCertType = SysAllocStringByteLen(
				(char *) pName->Value.pbData,
				pName->Value.cbData);
        if (NULL == strCertType)
        {
            hr = E_OUTOFMEMORY;
	    _JumpError(hr, error, "Exit:SysAllocStringByteLen");
        }
    }
    else
    {
        // see if there is a type name in the request attributes

        hr = pServer->GetRequestAttribute(CERTTYPE_ATTR_NAME, &strCertType);
	_PrintIfError2(hr, "Exit:GetRequestAttribute", hr);
    }
    DBGPRINT((fDebug, "Exit:CertType = %ws\n", strCertType));

    hr = S_OK;


    if (m_dwExitPublishFlags & EXITPUB_FILE)
    {
	hr2 = _WriteCertToFile(
			pServer,
			(BYTE const *) varCert.bstrVal,
			SysStringByteLen(varCert.bstrVal));
	_PrintIfError(hr2, "_WriteCertToFile");
	if (S_OK == hr)
	{
	    hr = hr2;
	}
    }


error:
    if (NULL != pName)
    {
        LocalFree(pName);
    }
    if (NULL != strCertType)
    {
	SysFreeString(strCertType);
    }
    VariantClear(&varCert);
    VariantClear(&varExt);
    if (NULL != pServer)
    {
	pServer->Release();
    }
    return(hr);
}

//+--------------------------------------------------------------------------
// CCertExitSample::_NotifyCRLIssued -- Notify the exit module of a new certificate
//
//+--------------------------------------------------------------------------

HRESULT
CCertExitSample::_NotifyCRLIssued(
    /* [in] */ LONG Context)
{
    HRESULT hr;
    ICertServerExit *pServer = NULL;
    DWORD i;
    VARIANT varCRL;
    DWORD cbbuf;
    DWORD err;
    DWORD dwType;
    BSTR bstrCRL = NULL;

    VariantInit(&varCRL);


    hr = CoCreateInstance(
		    CLSID_CCertServerExit,
		    NULL,               // pUnkOuter
		    CLSCTX_INPROC_SERVER,
		    IID_ICertServerExit,
		    (VOID **) &pServer);
    _JumpIfError(hr, error, "Exit:CoCreateInstance");

    hr = pServer->SetContext(Context);
    _JumpIfError(hr, error, "Exit:SetContext");


    // How many CRL's are there?

    // Loop for each CRL
    for (i = 0; i < m_cCACert; i++)
    {
        WCHAR wszCRLPROP[MAX_CRL_PROP];

        // Verify the CRL State says we should update this CRL

        wsprintf(wszCRLPROP, wszPROPCRLSTATE L".%u", i);
        hr = pServer->GetCertificateProperty(
			           wszCRLPROP,
			           PROPTYPE_LONG,
			           &varCRL);
        _JumpIfErrorStr(hr, error, "Exit:GetCertificateProperty", wszCRLPROP);

	if (CA_DISP_VALID != varCRL.lVal)
	{
	    continue;
	}


        // Grab the raw CRL

        wsprintf(wszCRLPROP, wszPROPRAWCRL L".%u", i);
        hr = pServer->GetCertificateProperty(
			           wszCRLPROP,
			           PROPTYPE_BINARY,
			           &varCRL);
        _JumpIfErrorStr(hr, error, "Exit:GetCertificateProperty", wszCRLPROP);

        // Publish the CRL

    }

    cbbuf = sizeof(m_cCRLPublishRetryCount);
    err = RegQueryValueEx(
		    m_hExitKey,
		    wszCRLPUBLISHRETRYCOUNT,
		    NULL,           // lpdwReserved
		    &dwType,
		    (LPBYTE)&m_cCRLPublishRetryCount,
		    &cbbuf);
    if(err == ERROR_FILE_NOT_FOUND)
    {
        m_cCRLPublishRetryCount = CRL_PUBLISH_RETRY_DEFAULT;
        err = ERROR_SUCCESS;
    }
    hr = HRESULT_FROM_WIN32(err);
    _JumpIfError(hr, error, "Exit:RegQueryValueEx");

error:
    if (NULL != bstrCRL)
    {
        SysFreeString(bstrCRL);
    }
    if (NULL != pServer)
    {
	pServer->Release();
    }
    VariantClear(&varCRL);


    return(hr);
}


//+--------------------------------------------------------------------------
// CCertExitSample::Notify -- Notify the exit module of an event
//
// Returns S_OK.
//+--------------------------------------------------------------------------

STDMETHODIMP
CCertExitSample::Notify(
    /* [in] */ LONG ExitEvent,
    /* [in] */ LONG Context)
{
    char *psz = "UNKNOWN EVENT";
    HRESULT hr = S_OK;

    switch (ExitEvent)
    {
	case EXITEVENT_CERTISSUED:
	    hr = _NotifyNewCert(Context);
	    psz = "certissued";
	    break;

	case EXITEVENT_CERTPENDING:
	    psz = "certpending";
	    break;

	case EXITEVENT_CERTDENIED:
	    psz = "certdenied";
	    break;

	case EXITEVENT_CERTREVOKED:
	    psz = "certrevoked";
	    break;

	case EXITEVENT_CERTRETRIEVEPENDING:
	    psz = "retrievepending";
	    break;

	case EXITEVENT_CRLISSUED:
	    hr = _NotifyCRLIssued(Context);
	    psz = "crlissued";
	    break;

	case EXITEVENT_SHUTDOWN:
	    psz = "shutdown";
	    break;
    }

    DBGPRINT((fDebug, "Exit:Notify(%s=%x, ctx=%u) rc=%x\n", psz, ExitEvent, Context, hr));
    return(hr);
}


STDMETHODIMP
CCertExitSample::GetDescription(
    /* [retval][out] */ BSTR *pstrDescription)
{
    HRESULT hr = S_OK;
    WCHAR sz[MAX_PATH];

    assert(wcslen(wsz_SAMPLE_DESCRIPTION) < ARRAYSIZE(sz));
    wcscpy(sz, wsz_SAMPLE_DESCRIPTION);

    *pstrDescription = SysAllocString(sz);
    if (NULL == *pstrDescription)
    {
	hr = E_OUTOFMEMORY;
	_JumpError(hr, error, "Exit:SysAllocString");
    }

error:
    return(hr);
}


/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP
CCertExitSample::InterfaceSupportsErrorInfo(REFIID riid)
{
    int i;
    static const IID *arr[] =
    {
	&IID_ICertExit,
    };

    for (i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
    {
	if (IsEqualGUID(*arr[i],riid))
	{
	    return(S_OK);
	}
    }
    return(S_FALSE);
}

