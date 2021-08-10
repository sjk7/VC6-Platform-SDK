//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1995 - 2000
//
//  File:       celib.cpp
//
//  Contents:   helper functions
//
//--------------------------------------------------------------------------

#include "pch.cpp"
#pragma hdrstop

#include <stdio.h>
#include <assert.h>
#include "celibw2k.h"

#ifndef wszDURATIONUNITSDAYS
# define wszDURATIONUNITSDAYS		wszPERIODDAYS
# define wszDURATIONUNITSHOURS		wszPERIODHOURS
# define wszDURATIONUNITSMINUTES	wszPERIODMINUTES
# define wszDURATIONUNITSMONTHS		wszPERIODMONTHS
# define wszDURATIONUNITSSECONDS	wszPERIODSECONDS
# define wszDURATIONUNITSWEEKS		wszPERIODWEEKS
# define wszDURATIONUNITSYEARS		wszPERIODYEARS
#endif

//+--------------------------------------------------------------------------
// ceDecodeObject -- call CryptDecodeObject, and allocate memory for output
//
//+--------------------------------------------------------------------------

BOOL
ceDecodeObject(
    IN DWORD dwEncodingType,
    IN LPCSTR lpszStructType,
    IN BYTE const *pbEncoded,
    IN DWORD cbEncoded,
    IN BOOL fCoTaskMemAlloc,
    OUT VOID **ppvStructInfo,
    OUT DWORD *pcbStructInfo)
{
    BOOL b;

    assert(!fCoTaskMemAlloc);
    *ppvStructInfo = NULL;
    *pcbStructInfo = 0;
    while (TRUE)
    {
	b = CryptDecodeObject(
		    dwEncodingType,
		    lpszStructType,
		    pbEncoded,
		    cbEncoded,
		    0,                  // dwFlags
		    *ppvStructInfo,
		    pcbStructInfo);
	if (b && 0 == *pcbStructInfo)
	{
	    SetLastError(HRESULT_FROM_WIN32(ERROR_INVALID_DATA));
	    b = FALSE;
	}
	if (!b)
	{
	    if (NULL != *ppvStructInfo)
	    {
		HRESULT hr = GetLastError();

		LocalFree(*ppvStructInfo);
		*ppvStructInfo = NULL;
		SetLastError(hr);
	    }
	    break;
	}
	if (NULL != *ppvStructInfo)
	{
	    break;
	}
	*ppvStructInfo = (BYTE *) LocalAlloc(LMEM_FIXED, *pcbStructInfo);
	if (NULL == *ppvStructInfo)
	{
	    b = FALSE;
	    break;
	}
    }
    return(b);
}


BOOL
ceEncodeObject(
    IN DWORD dwEncodingType,
    IN LPCSTR lpszStructType,
    IN VOID const *pvStructInfo,
    IN DWORD dwFlags,
    IN BOOL fCoTaskMemAlloc,
    OUT BYTE **ppbEncoded,
    OUT DWORD *pcbEncoded)
{
    BOOL b;

    assert(0 == dwFlags);
    assert(!fCoTaskMemAlloc);
    *ppbEncoded = NULL;
    *pcbEncoded = 0;
    while (TRUE)
    {
	b = CryptEncodeObject(
		    dwEncodingType,
		    lpszStructType,
		    const_cast<VOID *>(pvStructInfo),
		    *ppbEncoded,
		    pcbEncoded);
	if (b && 0 == *pcbEncoded)
	{
	    SetLastError(HRESULT_FROM_WIN32(ERROR_INVALID_DATA));
	    b = FALSE;
	}
	if (!b)
	{
	    if (NULL != *ppbEncoded)
	    {
		HRESULT hr = GetLastError();

		LocalFree(*ppbEncoded);
		*ppbEncoded = NULL;
		SetLastError(hr);
	    }
	    break;
	}
	if (NULL != *ppbEncoded)
	{
	    break;
	}
	*ppbEncoded = (BYTE *) LocalAlloc(LMEM_FIXED, *pcbEncoded);
	if (NULL == *ppbEncoded)
	{
	    b = FALSE;
	    break;
	}
    }
    return(b);
}


// The returned pszObjId is a constant that must not be freed.  CryptFindOIDInfo
// has a static internal database that is valid until crypt32.dll is unloaded.

WCHAR const *
ceGetOIDNameA(
    IN char const *pszObjId)
{
    CRYPT_OID_INFO const *pInfo = NULL;
    WCHAR const *pwszName = L"";

    // First try looking up the ObjectId as an Extension or Attribute, because
    // we get a better Display Name, especially for Subject RDNs: CN, L, etc.
    // If that fails, look it up withoput restricting the group.

    pInfo = CryptFindOIDInfo(
			CRYPT_OID_INFO_OID_KEY,
			(VOID *) pszObjId,
			CRYPT_EXT_OR_ATTR_OID_GROUP_ID);

    if (NULL == pInfo || NULL == pInfo->pwszName || L'\0' == pInfo->pwszName[0])
    {
	pInfo = CryptFindOIDInfo(CRYPT_OID_INFO_OID_KEY, (VOID *) pszObjId, 0);
    }
    if (NULL != pInfo && NULL != pInfo->pwszName && L'\0' != pInfo->pwszName[0])
    {
	pwszName = pInfo->pwszName;
    }
    return(pwszName);
}


WCHAR const *
ceGetOIDName(
    IN WCHAR const *pwszObjId)
{
    char *pszObjId = NULL;
    WCHAR const *pwszName = L"";

    if (!ceConvertWszToSz(&pszObjId, pwszObjId, -1))
    {
	_JumpError(E_OUTOFMEMORY, error, "ceConvertWszToSz");
    }
    pwszName = ceGetOIDNameA(pszObjId);

error:
    if (NULL != pszObjId)
    {
	LocalFree(pszObjId);
    }
    return(pwszName);
}


WCHAR *
ceDuplicateString(
    IN WCHAR const *pwsz)
{
    WCHAR *pwszOut;

    pwszOut = (WCHAR *) LocalAlloc(
				LMEM_FIXED,
				(wcslen(pwsz) + 1) * sizeof(pwsz[0]));
    if (NULL != pwszOut)
    {
	wcscpy(pwszOut, pwsz);
    }
    return(pwszOut);
}


BOOL
ceConvertWszToSz(
    OUT CHAR **ppsz,
    IN WCHAR const *pwc,
    IN LONG cwc)
{
    BOOL fOk = FALSE;
    LONG cch = 0;

    *ppsz = NULL;
    while (TRUE)
    {
	cch = WideCharToMultiByte(
			GetACP(),
			0,          // dwFlags
			pwc,
			cwc,        // cchWideChar, -1 => null terminated
			*ppsz,
			cch,
			NULL,
			NULL);
	if (0 >= cch)
	{
	    DWORD err;

	    err = GetLastError();
	    ceERRORPRINTLINE("WideCharToMultiByte", err);
	    if (NULL != *ppsz)
	    {
		LocalFree(*ppsz);
		*ppsz = NULL;
	    }
	    break;
	}
	if (NULL != *ppsz)
	{
	    fOk = TRUE;
	    break;
	}
	*ppsz = (CHAR *) LocalAlloc(LMEM_FIXED, cch + 1);
	if (NULL == *ppsz)
	{
	    break;
	}
    }
    return(fOk);
}


BOOL
ceConvertWszToBstr(
    OUT BSTR *pbstr,
    IN WCHAR const *pwc,
    IN LONG cb)
{
    BOOL fOk = FALSE;
    BSTR bstr;

    ceFreeBstr(pbstr);
    do
    {
	bstr = NULL;
	if (NULL != pwc)
	{
	    if (-1 == cb)
	    {
		cb = (LONG)(wcslen(pwc) * sizeof(WCHAR));
	    }
	    bstr = SysAllocStringByteLen((char const *) pwc, cb);
	    if (NULL == bstr)
	    {
		break;
	    }
	}
	*pbstr = bstr;
	fOk = TRUE;
    } while (FALSE);
    return(fOk);
}


BOOL
ceConvertSzToWsz(
    OUT WCHAR **ppwsz,
    IN char const *pch,
    IN LONG cch)
{
    BOOL fOk = FALSE;
    LONG cwc = 0;

    *ppwsz = NULL;
    while (TRUE)
    {
	cwc = MultiByteToWideChar(GetACP(), 0, pch, cch, *ppwsz, cwc);
	if (0 >= cwc)
	{
	    DWORD err;

	    err = GetLastError();
	    ceERRORPRINTLINE("MultiByteToWideChar", err);
	    if (NULL != *ppwsz)
	    {
		LocalFree(*ppwsz);
		*ppwsz = NULL;
	    }
	    break;
	}
	if (NULL != *ppwsz)
	{
	    fOk = TRUE;
	    break;
	}
	*ppwsz = (WCHAR *) LocalAlloc(LMEM_FIXED, (cwc + 1) * sizeof(WCHAR));
	if (NULL == *ppwsz)
	{
	    break;
	}
    }
    return(fOk);
}


BOOL
ceConvertSzToBstr(
    OUT BSTR *pbstr,
    IN CHAR const *pch,
    IN LONG cch)
{
    BOOL fOk = FALSE;
    BSTR bstr = NULL;
    LONG cwc = 0;

    ceFreeBstr(pbstr);
    if (-1 == cch)
    {
	cch = (LONG)strlen(pch);
    }
    while (TRUE)
    {
	cwc = MultiByteToWideChar(GetACP(), 0, pch, cch, bstr, cwc);
	if (0 >= cwc)
	{
	    //hr = ceHLastError();
	    //printf("MultiByteToWideChar returned %d (%x)\n", hr, hr);
	    break;
	}
	if (NULL != bstr)
	{
	    bstr[cwc] = L'\0';
	    *pbstr = bstr;
	    fOk = TRUE;
	    break;
	}
	bstr = SysAllocStringLen(NULL, cwc);
	if (NULL == bstr)
	{
	    break;
	}
    }
    return(fOk);
}


VOID
ceFreeBstr(
    IN OUT BSTR *pstr)
{
    if (NULL != *pstr)
    {
	SysFreeString(*pstr);
	*pstr = NULL;
    }
}


HRESULT
ceHError(
    IN HRESULT hr)
{
    assert(S_FALSE != hr);

    if (S_OK != hr && S_FALSE != hr && !FAILED(hr))
    {
        hr = HRESULT_FROM_WIN32(hr);
	if (0 == HRESULT_CODE(hr))
	{
	    // A call failed without properly setting an error condition!
	    hr = E_UNEXPECTED;
	}
	assert(FAILED(hr));
    }
    return(hr);
}


HRESULT
ceHLastError(VOID)
{
    return(ceHError(GetLastError()));
}


VOID
ceErrorPrintLine(
    IN char const *pszFile,
    IN DWORD line,
    IN char const *pszMessage,
    IN HRESULT hr)
{
    wprintf(
	L"CertEnc.Dll: Error: %hs(%u): %hs 0x%x (%d)\n",
	pszFile,
	line,
	pszMessage,
	hr,
	hr);
}


HRESULT
ceDateToFileTime(
    IN DATE const *pDate,
    OUT FILETIME *pft)
{
    SYSTEMTIME st;
    HRESULT hr = S_OK;

    if (*pDate == 0.0)
    {
        GetSystemTime(&st);
    }
    else
    {
	if (!VariantTimeToSystemTime(*pDate, &st))
	{
	    hr = HRESULT_FROM_WIN32(ERROR_INVALID_DATA);
	    _JumpError(hr, error, "VariantTimeToSystemTime");
	}
    }

    if (!SystemTimeToFileTime(&st, pft))
    {
        hr = ceHLastError();
        _JumpError(hr, error, "SystemTimeToFileTime");
    }

error:
    return(hr);
}


HRESULT
ceFileTimeToDate(
    IN FILETIME const *pft,
    OUT DATE *pDate)
{
    SYSTEMTIME st;
    HRESULT hr = S_OK;

    if (!FileTimeToSystemTime(pft, &st))
    {
        hr = ceHLastError();
        _JumpError(hr, error, "FileTimeToSystemTime");
    }
    if (!SystemTimeToVariantTime(&st, pDate))
    {
        hr = HRESULT_FROM_WIN32(ERROR_INVALID_DATA);
        _JumpError(hr, error, "SystemTimeToVariantTime");
    }

error:
    return(hr);
}


VOID
ceMakeExprDateTime(
    IN OUT FILETIME *pft,
    IN LONG lDelta,
    IN enum ENUM_PERIOD enumPeriod)
{
    LONGLONG llDelta;
    BOOL fSysTimeDelta;

    llDelta = lDelta;
    fSysTimeDelta = FALSE;
    switch (enumPeriod)
    {
	case ENUM_PERIOD_WEEKS:   llDelta *= CVT_WEEKS;    break;
	case ENUM_PERIOD_DAYS:    llDelta *= CVT_DAYS;     break;
	case ENUM_PERIOD_HOURS:   llDelta *= CVT_HOURS;    break;
	case ENUM_PERIOD_MINUTES: llDelta *= CVT_MINUTES;  break;
	case ENUM_PERIOD_SECONDS: 			  break;
	default:
	    fSysTimeDelta = TRUE;
	    break;
    }
    if (fSysTimeDelta)
    {
	    SYSTEMTIME SystemTime;

	    FileTimeToSystemTime(pft, &SystemTime);
	    switch (enumPeriod)
	    {
	        case ENUM_PERIOD_MONTHS:
		    if (0 > lDelta)
		    {
		        DWORD dwDelta = (DWORD) -lDelta;

		        SystemTime.wYear -= (WORD) (dwDelta / 12) + 1;
		        SystemTime.wMonth += 12 - (WORD) (dwDelta % 12);
		    }
		    else
		    {
		        SystemTime.wMonth += (WORD) lDelta;
		    }
		    if (12 < SystemTime.wMonth)
		    {
		        SystemTime.wYear += (SystemTime.wMonth - 1) / 12;
		        SystemTime.wMonth = ((SystemTime.wMonth - 1) % 12) + 1;
		    }
		    break;

	        case ENUM_PERIOD_YEARS:
		    SystemTime.wYear += (WORD) lDelta;
		    break;

	        default:
		    SystemTime.wYear += 1;
		    break;
	    }

DoConvert:
        if (!SystemTimeToFileTime(&SystemTime, pft))
        {
            if (GetLastError() != ERROR_INVALID_PARAMETER)
            {
                assert(!"Unable to do time conversion");
                return;
            }

            // In some cases we'll convert to an invalid month-end

            // only one month changes length from year to year
            if (SystemTime.wMonth == 2)
            {
                // > 29? try leap year
                if (SystemTime.wDay > 29)
                {
                    SystemTime.wDay = 29;
                    goto DoConvert;
                }
                // == 29? try non-leap year
                else if (SystemTime.wDay == 29)
                {
                    SystemTime.wDay = 28;
                    goto DoConvert;
                }
            }
            // sept (9), apr(4), jun(6), nov(11) all have 30 days
            else if ((SystemTime.wMonth == 9) ||
                     (SystemTime.wMonth == 4) ||
                     (SystemTime.wMonth == 6) ||
                     (SystemTime.wMonth == 11))
            {
                if (SystemTime.wDay > 30)
                {
                    SystemTime.wDay = 30;
                    goto DoConvert;
                }
            }

            // should never get here
            assert(!"Month/year processing: inaccessible code");
            return;
        }
    }
    else
    {
	    *(LONGLONG *) pft += llDelta * CVT_BASE;
    }
}


HRESULT
ceMakeExprDate(
    IN OUT DATE *pDate,
    IN LONG lDelta,
    IN enum ENUM_PERIOD enumPeriod)
{
    HRESULT hr;
    FILETIME ft;

    hr = ceDateToFileTime(pDate, &ft);
    _JumpIfError(hr, error, "ceDateToFileTime");

    ceMakeExprDateTime(&ft, lDelta, enumPeriod);

    hr = ceFileTimeToDate(&ft, pDate);
    _JumpIfError(hr, error, "ceFileTimeToDate");

error:
    return(hr);
}


typedef struct _UNITSTABLE
{
    WCHAR const     *pwszString;
    enum ENUM_PERIOD enumPeriod;
} UNITSTABLE;


UNITSTABLE g_aut[] =
{
    { wszDURATIONUNITSSECONDS, ENUM_PERIOD_SECONDS },
    { wszDURATIONUNITSMINUTES, ENUM_PERIOD_MINUTES },
    { wszDURATIONUNITSHOURS,   ENUM_PERIOD_HOURS },
    { wszDURATIONUNITSDAYS,    ENUM_PERIOD_DAYS },
    { wszDURATIONUNITSWEEKS,   ENUM_PERIOD_WEEKS },
    { wszDURATIONUNITSMONTHS,  ENUM_PERIOD_MONTHS },
    { wszDURATIONUNITSYEARS,   ENUM_PERIOD_YEARS },
};
#define CUNITSTABLEMAX	(sizeof(g_aut)/sizeof(g_aut[0]))


HRESULT
ceTranslatePeriodUnits(
    IN WCHAR const *pwszPeriod,
    IN LONG lCount,
    OUT enum ENUM_PERIOD *penumPeriod,
    OUT LONG *plCount)
{
    HRESULT hr;
    UNITSTABLE const *put;

    for (put = g_aut; put < &g_aut[CUNITSTABLEMAX]; put++)
    {
	if (0 == lstrcmpi(pwszPeriod, put->pwszString))
	{
	    *penumPeriod = put->enumPeriod;
	    if (0 > lCount)
	    {
		lCount = MAXLONG;
	    }
	    *plCount = lCount;
	    hr = S_OK;
	    goto error;
	}
    }
    hr = HRESULT_FROM_WIN32(ERROR_INVALID_DATA);

error:
    return(hr);
}


HRESULT
ceVerifyObjId(
    IN WCHAR const *pwszObjId)
{
    HRESULT hr;
    CHAR *pszObjId = NULL;
    DWORD cbEncoded;
    CRYPT_ATTRIBUTE ainfo;

    if (!ceConvertWszToSz(&pszObjId, pwszObjId, -1))
    {
	hr = E_OUTOFMEMORY;
        ceERRORPRINTLINE("ceConvertWszToSz", hr);
        goto error;
    }

    ainfo.pszObjId = pszObjId;
    ainfo.cValue = 0;
    if (!CryptEncodeObject(
		     X509_ASN_ENCODING,
		     PKCS_ATTRIBUTE,
		     &ainfo,
		     NULL,
		     &cbEncoded))
    {
        hr = E_INVALIDARG;
        ceERRORPRINTLINE("invalid Obj Id", hr);
        goto error;
    }
    hr = S_OK;

error:
    if (NULL != pszObjId)
    {
    	LocalFree(pszObjId);
    }
    return(hr);
}


HRESULT
ceVerifyAltNameString(
    IN LONG NameChoice,
    IN WCHAR const *pwszName)
{
    HRESULT hr = S_OK;
    CERT_ALT_NAME_INFO AltName;
    CERT_ALT_NAME_ENTRY Entry;
    char *pszObjectId = NULL;
    DWORD cbEncoded;

    ZeroMemory(&AltName, sizeof(AltName));
    AltName.cAltEntry = 1;
    AltName.rgAltEntry = &Entry;

    ZeroMemory(&Entry, sizeof(Entry));
    Entry.dwAltNameChoice = NameChoice;

    switch (NameChoice)
    {
	case CERT_ALT_NAME_RFC822_NAME:
	    Entry.pwszRfc822Name = const_cast<WCHAR *>(pwszName);
	    break;

	case CERT_ALT_NAME_DNS_NAME:
	    Entry.pwszDNSName = const_cast<WCHAR *>(pwszName);
	    break;

	case CERT_ALT_NAME_URL:
	    Entry.pwszURL = const_cast<WCHAR *>(pwszName);
	    break;

	case CERT_ALT_NAME_REGISTERED_ID:
	    if (!ceConvertWszToSz(&pszObjectId, pwszName, -1))
	    {
		hr = E_OUTOFMEMORY;
		ceERRORPRINTLINE("ceConvertWszToSz", hr);
		goto error;
	    }
	    Entry.pszRegisteredID = pszObjectId;
	    break;

	//case CERT_ALT_NAME_DIRECTORY_NAME:
	//case CERT_ALT_NAME_OTHER_NAME:
	//case CERT_ALT_NAME_X400_ADDRESS:
	//case CERT_ALT_NAME_EDI_PARTY_NAME:
	//case CERT_ALT_NAME_IP_ADDRESS:
	default:
	    hr = E_INVALIDARG;
	    ceERRORPRINTLINE("NameChoice", hr);
	    goto error;
		
    }

    // Encode CERT_ALT_NAME_INFO:

    if (!CryptEncodeObject(
		    X509_ASN_ENCODING,
		    X509_ALTERNATE_NAME,
		    &AltName,
		    NULL,
		    &cbEncoded))
    {
	hr = ceHLastError();
	ceERRORPRINTLINE("ceEncodeObject", hr);
	goto error;
    }

error:
    if (NULL != pszObjectId)
    {
	LocalFree(pszObjectId);
    }
    return(hr);
}


HRESULT
ceDispatchSetErrorInfo(
    IN HRESULT hrError,
    IN WCHAR const *pwszDescription,
    OPTIONAL IN WCHAR const *pwszProgId,
    OPTIONAL IN IID const *piid)
{
    HRESULT hr;
    ICreateErrorInfo *pCreateErrorInfo = NULL;
    IErrorInfo *pErrorInfo = NULL;
    WCHAR *pwszError = NULL;
    WCHAR *pwszText = NULL;

    if (NULL == pwszDescription)
    {
        hr = E_POINTER;
        ceERRORPRINTLINE("NULL pointer", hr);        
        goto error;
    }

    assert(FAILED(hrError));
    pwszError = ceGetErrorMessageText(hrError, TRUE);
    if (NULL == pwszError)
    {
	ceERRORPRINTLINE("ceGetErrorMessageText", E_OUTOFMEMORY);
    }
    else
    {
	pwszText = (WCHAR *) LocalAlloc(
	    LMEM_FIXED,
	    (wcslen(pwszDescription) + 1 + wcslen(pwszError) + 1) *
	     sizeof(WCHAR));
	if (NULL == pwszText)
	{
	    ceERRORPRINTLINE("LocalAlloc", E_OUTOFMEMORY);
	}
	else
	{
	    wcscpy(pwszText, pwszDescription);
	    wcscat(pwszText, L" ");
	    wcscpy(pwszText, pwszError);
	}
    }

    hr = CreateErrorInfo(&pCreateErrorInfo);
    if (S_OK != hr)
    {
        ceERRORPRINTLINE("CreateErrorInfo", hr);
        goto error;
    }

    if (NULL != piid)
    {
	hr = pCreateErrorInfo->SetGUID(*piid);
	if (S_OK != hr)
	{
	    ceERRORPRINTLINE("SetGUID", hr);
	}
    }

    hr = pCreateErrorInfo->SetDescription(
		    NULL != pwszText?
			pwszText : const_cast<WCHAR *>(pwszDescription));
    if (S_OK != hr)
    {
	ceERRORPRINTLINE("SetDescription", hr);
    }

    // Set ProgId:

    if (NULL != pwszProgId)
    {
	hr = pCreateErrorInfo->SetSource(const_cast<WCHAR *>(pwszProgId));
	if (S_OK != hr)
	{
	    ceERRORPRINTLINE("SetSource", hr);
	}
    }

    hr = pCreateErrorInfo->QueryInterface(
				    IID_IErrorInfo,
				    (VOID **) &pErrorInfo);
    if (S_OK != hr)
    {
        ceERRORPRINTLINE("QueryInterface", hr);
        goto error;
    }

    SetErrorInfo(0, pErrorInfo);

error:
    if (NULL != pErrorInfo)
    {
	pErrorInfo->Release();
    }
    if (NULL != pCreateErrorInfo)
    {
	pCreateErrorInfo->Release();
    }
    if (NULL != pwszText)
    {
	LocalFree(pwszText);
    }
    if (NULL != pwszError)
    {
	LocalFree(pwszError);
    }
    return(hrError);	// return input error!
}


int 
ceWtoI(
    IN WCHAR const *string,
    OUT BOOL *pfValid)
{
    HRESULT hr;
    WCHAR szBuf[16];
    WCHAR *szTmp = szBuf;
    int cTmp = ARRAYSIZE(szBuf);
    int i = 0;
    WCHAR const *pwsz;
    BOOL fSawDigit = FALSE;
 
    assert(NULL != pfValid);
    cTmp = FoldString(
        MAP_FOLDDIGITS, 
        string,
        -1,
        szTmp,
        cTmp);
    if (cTmp == 0)
    {
        hr = ceHLastError();
        if (HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER) == hr)
        {
            hr = S_OK;
            cTmp = FoldString(
                MAP_FOLDDIGITS, 
                string,
                -1,
                NULL,
                0);

            szTmp = (WCHAR*)LocalAlloc(LMEM_FIXED, cTmp*sizeof(WCHAR));
	    if (NULL == szTmp)
	    {
		hr = E_OUTOFMEMORY;
		_JumpError(hr, error, "LocalAlloc");
	    }

            cTmp = FoldString(
                MAP_FOLDDIGITS, 
                string,
                -1,
                szTmp,
                cTmp);

            if (cTmp == 0)
                hr = ceHLastError();
        }
        _JumpIfError(hr, error, "FoldString");
    }    
    pwsz = szTmp;
    while (iswspace(*pwsz))
    {
	pwsz++;
    }
    while (iswdigit(*pwsz))
    {
	fSawDigit = TRUE;
	pwsz++;
    }
    while (iswspace(*pwsz))
    {
	pwsz++;
    }
    if (L'\0' == *pwsz)
    {
	*pfValid = fSawDigit;
    }
    i = _wtoi(szTmp);

error:
    if (szTmp && (szTmp != szBuf))
       LocalFree(szTmp);

    return i;
}
