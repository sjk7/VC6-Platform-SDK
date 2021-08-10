//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1997 - 2000
//
//  File:       policy.h
//
//--------------------------------------------------------------------------

#include "certpsam.h"
#include "resource.h"

#define wszCLASS_CERTPOLICYSAMPLEPREFIX TEXT("CertAuthority_Sample") 

#define wszCLASS_CERTPOLICYSAMPLE wszCLASS_CERTPOLICYSAMPLEPREFIX  wszCERTPOLICYMODULE_POSTFIX

#define wszCLASS_CERTMANAGESAMPLE wszCLASS_CERTPOLICYSAMPLEPREFIX wszCERTMANAGEPOLICY_POSTFIX

#define wsz_SAMPLE_NAME           L"CertXPol.dll"
#define wsz_SAMPLE_DESCRIPTION    L"Sample Policy Module"
#define wsz_SAMPLE_COPYRIGHT      L"(c)1999-2000 Microsoft"
#define wsz_SAMPLE_FILEVER        L"v 1.0"
#define wsz_SAMPLE_PRODUCTVER     L"v 5.00"

#ifndef wszATTREMAIL1
# define wszATTREMAIL1			TEXT("E")
# define wszATTREMAIL2			TEXT("EMail")
#endif

HRESULT GetServerCallbackInterface(ICertServerPolicy** ppServer, LONG Context);


// 
// Class CCertPolicySample
// 
// Actual policy module for a CA Policy
//
//

class CCertPolicySample: 
    public CComDualImpl<ICertPolicy, &IID_ICertPolicy, &LIBID_CERTPOLICYSAMPLELib>, 
    public ISupportErrorInfo,
    public CComObjectRoot,
    public CComCoClass<CCertPolicySample, &CLSID_CCertPolicySample>
{
public:
    CCertPolicySample()
    {
        m_bstrDescription = NULL;

        // RevocationExtension variables:

	m_dwRevocationFlags = 0;
	m_cCDPRevocationURL = 0;
	m_apstrCDPRevocationURL = NULL;
	m_wszASPRevocationURL = NULL;

        m_dwDispositionFlags = 0;
        m_dwEditFlags = 0;

	// CertTypeExtension variables:

	m_astrSubjectAltNameProp[0] = NULL;
	m_astrSubjectAltNameProp[1] = NULL;
	m_astrSubjectAltNameObjectId[0] = NULL;
	m_astrSubjectAltNameObjectId[1] = NULL;

	// AuthorityInfoAccessExtension variables:

        m_dwIssuerCertURLFlags = 0;
        m_cIssuerCertURL = 0;
	m_apstrIssuerCertURL = NULL;

	m_cEnableRequestExtensions = 0;
	m_apstrEnableRequestExtensions = NULL;

	m_cDisableExtensions = 0;
	m_apstrDisableExtensions = NULL;

	// CA Name
        m_wszRegStorageLoc = NULL;

	m_bstrCAName = NULL;
        m_bstrCASanitizedName = NULL;
        m_bstrCASanitizedDSName = NULL;
        m_bstrMachineDNSName = NULL;

        InitializeCriticalSection(&m_PolicyCriticalSection);

        // CA and cert type info

        m_CAType = ENUM_UNKNOWN_CA;

        m_hrLastUpdateResult = S_OK;
        m_pCert = NULL;
        m_iCRL = 0;

    }
    ~CCertPolicySample();

BEGIN_COM_MAP(CCertPolicySample)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ICertPolicy)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

DECLARE_NOT_AGGREGATABLE(CCertPolicySample) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation.  The default is to support it

DECLARE_REGISTRY(
    CCertPolicySample,
    wszCLASS_CERTPOLICYSAMPLE TEXT(".1"),
    wszCLASS_CERTPOLICYSAMPLE,
    IDS_CERTPOLICY_DESC,
    THREADFLAGS_BOTH)

// ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICertPolicy
public:

    STDMETHOD(Initialize)( 
	    /* [in] */ BSTR const strConfig);

    STDMETHOD(VerifyRequest)( 
	    /* [in] */ BSTR const strConfig,
	    /* [in] */ LONG Context,
	    /* [in] */ LONG bNewRequest,
	    /* [in] */ LONG Flags,
	    /* [out, retval] */ LONG __RPC_FAR *pDisposition);

    STDMETHOD(GetDescription)( 
	    /* [out, retval] */ BSTR __RPC_FAR *pstrDescription);

    STDMETHOD(ShutDown)();

    HRESULT AddBasicConstraintsCommon(
		IN ICertServerPolicy *pServer,
		IN CERT_EXTENSION const *pExtension,
        IN BOOL fCA,
		IN BOOL fEnableExtension);


protected:

    CERT_CONTEXT const *_GetIssuer(
		IN ICertServerPolicy *pServer);

    HRESULT _EnumerateExtensions(
		IN ICertServerPolicy *pServer,
		IN LONG bNewRequest,
		OPTIONAL OUT BOOL *pfCA);

#if DBG_CERTSRV
    VOID _DumpStringArray(
		IN char const *pszType,
		IN DWORD count,
		IN BSTR const *apstr);
#else
    #define _DumpStringArray(pszType, count, apstr)
#endif

    VOID _FreeStringArray(
		IN OUT DWORD *pcString,
		IN OUT LPWSTR **papstr);

    VOID _Cleanup();


    HRESULT _AddStringArray(
		IN WCHAR const *pwszzValue,
		IN BOOL fURL,
		IN OUT DWORD *pcStrings,
		IN OUT LPWSTR **papstrRegValues);

    HRESULT _ReadRegistryString(
		IN HKEY hkey,
		IN BOOL fURL,
		IN WCHAR const *pwszRegName,
		IN WCHAR const *pwszSuffix,
		OUT LPWSTR *pwszRegValue);

    HRESULT _ReadRegistryStringArray(
		IN HKEY hkey,
		IN BOOL fURL,
		IN DWORD dwFlags,
		IN DWORD cRegNames,
		IN DWORD *aFlags,
		IN WCHAR const * const *apwszRegNames,
		IN OUT DWORD *pcStrings,
		IN OUT LPWSTR **papstrRegValues);

    VOID _InitRevocationExtension(
		IN HKEY hkey);

    VOID _InitSubjectAltNameExtension(
		IN HKEY hkey,
		IN WCHAR const *pwszRegName,
		IN WCHAR const *pwszObjectId,
		IN DWORD iAltName);

    VOID _InitAuthorityInfoAccessExtension(
		IN HKEY hkey);

    VOID _InitRequestExtensionList(
		IN HKEY hkey);

    VOID _InitDisableExtensionList(
		IN HKEY hkey);

    HRESULT _AddRevocationExtension(
		IN ICertServerPolicy *pServer);

    HRESULT _AddCertTypeExtension(
		IN ICertServerPolicy *pServer,
		IN BOOL fCA);

    HRESULT _AddSubjectAltNameExtension(
		IN ICertServerPolicy *pServer,
		IN DWORD iAltName);

    HRESULT _AddAuthorityInfoAccessExtension(
		IN ICertServerPolicy *pServer);

    HRESULT _AddAuthorityKeyId(
		IN ICertServerPolicy *pServer);

    HRESULT _AddDefaultKeyUsageExtension(
		IN ICertServerPolicy *pServer,
		IN BOOL fCA);

    HRESULT _AddDefaultBasicConstraintsExtension(
		IN ICertServerPolicy *pServer,
		IN BOOL fCA);

    HRESULT _SetValidityPeriod(
		IN ICertServerPolicy *pServer);


    // RevocationExtension variables:

    PCCERT_CONTEXT m_pCert;

    BSTR  m_bstrDescription;

    DWORD m_dwRevocationFlags;
    DWORD m_cCDPRevocationURL;
    LPWSTR *m_apstrCDPRevocationURL;
    LPWSTR m_wszASPRevocationURL;

    DWORD m_dwDispositionFlags;
    DWORD m_dwEditFlags;
    DWORD m_CAPathLength;

    // AuthorityInfoAccessExtension variables:

    DWORD m_dwIssuerCertURLFlags;
    DWORD m_cIssuerCertURL;
    LPWSTR *m_apstrIssuerCertURL;

    DWORD m_cEnableRequestExtensions;
    LPWSTR *m_apstrEnableRequestExtensions;

    DWORD m_cDisableExtensions;
    LPWSTR *m_apstrDisableExtensions;

    // SubjectAltNameExtension variables:

    BSTR m_astrSubjectAltNameProp[2];
    BSTR m_astrSubjectAltNameObjectId[2];

    // CertTypeExtension variables:

    DWORD m_CertType;

    LPWSTR m_wszRegStorageLoc;
    BSTR m_bstrCAName;

    BSTR m_bstrCASanitizedName;
    BSTR m_bstrCASanitizedDSName;

    BSTR m_bstrMachineDNSName;

    CRITICAL_SECTION m_PolicyCriticalSection;
    
    // CA and cert type info

    ENUM_CATYPES m_CAType;

    DWORD m_hrLastUpdateResult;

    DWORD m_iCert;
    DWORD m_iCRL;

    //+--------------------------------------
    //+--------------------------------------

private:
};

