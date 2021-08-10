//+--------------------------------------------------------------------------
//
// Microsoft Windows
// Copyright (C) Microsoft Corporation, 1996 - 2000
//
// File:        exit.h
//
// Contents:    CCertExitSample definition
//
//---------------------------------------------------------------------------

#include "certxsam.h"
#include "resource.h"       // main symbols

#define wszCLASS_CERTEXITSAMPLEPREFIX TEXT("CertAuthority_Sample")

#define wszCLASS_CERTEXITSAMPLE wszCLASS_CERTEXITSAMPLEPREFIX wszCERTEXITMODULE_POSTFIX
#define wszCLASS_CERTMANAGESAMPLE wszCLASS_CERTEXITSAMPLEPREFIX wszCERTMANAGEEXIT_POSTFIX

#define wsz_SAMPLE_NAME           L"CertXSam.dll"
#define wsz_SAMPLE_DESCRIPTION    L"Sample Exit Module"
#define wsz_SAMPLE_COPYRIGHT      L"(c)1999-2000 Microsoft"
#define wsz_SAMPLE_FILEVER        L"v 1.0"
#define wsz_SAMPLE_PRODUCTVER     L"v 5.00"


#define CRL_PUBLISH_RETRY_DEFAULT 10

HRESULT
GetServerCallbackInterface(
    OUT ICertServerExit** ppServer,
    IN LONG Context);

/////////////////////////////////////////////////////////////////////////////
// certexit

class CCertExitSample: 
    public CComDualImpl<ICertExit, &IID_ICertExit, &LIBID_CERTEXITSAMPLELib>, 
    public ISupportErrorInfo,
    public CComObjectRoot,
    public CComCoClass<CCertExitSample, &CLSID_CCertExitSample>
{
public:
    CCertExitSample() 
    { 
	m_bstrDescription = NULL;
        m_strCAName = NULL;
        m_wszRegStorageLoc = NULL;
        m_hExitKey = NULL;
        m_dwExitPublishFlags = 0;
        m_cCACert = 0;
        m_cCRLPublishRetryCount = CRL_PUBLISH_RETRY_DEFAULT;

    }
    ~CCertExitSample();

BEGIN_COM_MAP(CCertExitSample)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ICertExit)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

DECLARE_NOT_AGGREGATABLE(CCertExitSample) 

DECLARE_REGISTRY(
    CCertExitSample,
    wszCLASS_CERTEXITSAMPLE TEXT(".1"),
    wszCLASS_CERTEXITSAMPLE,
    IDS_CERTEXIT_DESC,
    THREADFLAGS_BOTH)

    // ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

    // ICertExit
public:
    STDMETHOD(Initialize)( 
            /* [in] */ BSTR const strConfig,
            /* [retval][out] */ LONG __RPC_FAR *pEventMask);

    STDMETHOD(Notify)(
            /* [in] */ LONG ExitEvent,
            /* [in] */ LONG Context);

    STDMETHOD(GetDescription)( 
            /* [retval][out] */ BSTR *pstrDescription);

private:
    HRESULT _NotifyNewCert(IN LONG Context);

    HRESULT _NotifyCRLIssued(IN LONG Context);

    HRESULT _WriteCertToFile(
	IN ICertServerExit *pServer,
	IN BYTE const *pbCert,
	IN DWORD cbCert);

    HRESULT _ExpandEnvironmentVariables(
	IN WCHAR const *pwszIn,
	OUT WCHAR *pwszOut,
	IN DWORD cwcOut);


    // Member variables & private methods here:
    BSTR           m_bstrDescription;
    BSTR           m_strCAName;
    LPWSTR         m_wszRegStorageLoc;
    HKEY           m_hExitKey;
    DWORD          m_dwExitPublishFlags;
    DWORD          m_cCACert;
    INT            m_cCRLPublishRetryCount;

};

