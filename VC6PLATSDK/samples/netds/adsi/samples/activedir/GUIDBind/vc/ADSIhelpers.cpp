/*

    ADSIHelpers.CPP

    General helper rountines for Debugging ADSI applications


*/

#define INC_OLE2
#define UNICODE 1
#define _WIN32_DCOM

// If defined, will throw a WCHAR * on an error 
// in AdsMsagBox()
//#define THROW_CHARPTR_ONERROR

#include "ADSIhelpers.h"



#include <windows.h>
#include <OBJIDL.H>
#include <OAIDL.H>
#include <COMCAT.H>
#include <DOCOBJ.H>
#include <HLINK.H>
#include <MTX.H>
#include <MTXSPM.H>
#include <stdio.h>
#include <string.h> 
#include <stdio.h>
#include <string.h>
#include <assert.h>

//////////////////////////////////////////////
//  Debugging Functions



// Will display a message box for a BAD Hresult.
// Will do nothing for a S_OK HRESULT
// Pass in the HRESULT to be tested and a char * describing the
// area in the code 
void CheckHRESULT(HRESULT hr, const char *pszCause)
{
    if (FAILED(hr))
    {
        char sz[1024];
        char szCaption[1024];
        strcpy(szCaption, pszCause);
        strcat(szCaption, " failed!");
        if (!FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, 0, hr, 0, sz, 1024, 0))
            strcpy(sz, "Unknown error");
        MessageBoxA(0, sz, szCaption, MB_SETFOREGROUND);
       // DebugBreak();
    }
}


// When passed a VARIANT vt member, will return a string describing
// all the bitmask settings...
const char * GetVariantStyle(VARTYPE vt)
{
	static char pRet[200]; 

	pRet[0] = NULL;
	
	if (vt == VT_EMPTY) strcat(pRet,"VT_EMPTY ");

	if (HAS_BIT_STYLE(vt, VT_BYREF)) strcat(pRet,"VT_BYREF ");
	if (HAS_BIT_STYLE(vt, VT_UI1)) strcat(pRet,"VT_UI1 ");
	if (HAS_BIT_STYLE(vt, VT_I2)) strcat(pRet,"VT_I2 ");
	if (HAS_BIT_STYLE(vt, VT_I4)) strcat(pRet,"VT_I4 ");
	if (HAS_BIT_STYLE(vt, VT_R4)) strcat(pRet,"VT_R4 ");
	if (HAS_BIT_STYLE(vt, VT_R8)) strcat(pRet,"VT_R8 ");
	if (HAS_BIT_STYLE(vt, VT_CY)) strcat(pRet,"VT_CY ");
	if (HAS_BIT_STYLE(vt, VT_BSTR)) strcat(pRet,"VT_BSTR ");
	if (HAS_BIT_STYLE(vt, VT_NULL)) strcat(pRet,"VT_NULL ");
	if (HAS_BIT_STYLE(vt, VT_ERROR)) strcat(pRet,"VT_ERROR ");
	if (HAS_BIT_STYLE(vt, VT_BOOL)) strcat(pRet,"VT_BOOL ");
	if (HAS_BIT_STYLE(vt, VT_DATE)) strcat(pRet,"VT_DATE ");
	if (HAS_BIT_STYLE(vt, VT_DISPATCH)) strcat(pRet,"VT_DISPATCH ");
	if (HAS_BIT_STYLE(vt, VT_VARIANT)) strcat(pRet,"VT_VARIANT ");
	if (HAS_BIT_STYLE(vt, VT_UNKNOWN)) strcat(pRet,"VT_UNKNOWN ");
	if (HAS_BIT_STYLE(vt, VT_ARRAY)) strcat(pRet,"VT_ARRAY ");

	return pRet;  	    
}

// Pass in the interface ptr to the property value
// will return a BSTR value of the data.
// The IADsPropertyValue::get_ADsType()  is called to retrieve the 
// ADSTYPE valued enum 
// This enum is then used to determine which IADsPropertyValue method
// to call to receive the actual data

// CALLER assumes responsibility for freeing returned BSTR
HRESULT	GetIADsPropertyValueAsBSTR(BSTR * pbsRet,IADsPropertyValue * pAdsPV)
{
	HRESULT hr = S_OK;

	long lAdsType;
	hr = pAdsPV->get_ADsType(&lAdsType);
	
	if (FAILED(hr))
		return hr;

	switch (lAdsType)
	{
		case ADSTYPE_INVALID :
		{
			*pbsRet = SysAllocString(L"<ADSTYPE_INVALID>");
		}
		break;

		case ADSTYPE_DN_STRING :
		{
			hr = pAdsPV->get_DNString(pbsRet);
		}
		break;
		case ADSTYPE_CASE_EXACT_STRING :
		{
			hr = pAdsPV->get_CaseExactString(pbsRet);
		}
		break;
		case ADSTYPE_CASE_IGNORE_STRING :
		{
			hr = pAdsPV->get_CaseIgnoreString(pbsRet);
		}
		break;
		case ADSTYPE_PRINTABLE_STRING :
		{
			hr = pAdsPV->get_PrintableString(pbsRet);
		}
		break;
		case ADSTYPE_NUMERIC_STRING :
		{
			hr = pAdsPV->get_NumericString(pbsRet);
		}
		break;
		case ADSTYPE_BOOLEAN :
		{
			long b;
			hr = pAdsPV->get_Boolean(&b);
			if (SUCCEEDED(hr))
			{
				if (b)
					*pbsRet = SysAllocString(L"<TRUE>");
				else
					*pbsRet = SysAllocString(L"<FALSE>");
			}
		}
		break;
		case ADSTYPE_INTEGER :
		{
			long lInt;
			hr = pAdsPV->get_Integer(&lInt);
			if (SUCCEEDED(hr))
			{
				WCHAR wOut[100];
				wsprintf(wOut,L"%d",lInt);
				*pbsRet = SysAllocString(wOut);
			}
		}
		break;
		case ADSTYPE_OCTET_STRING :
		{
			*pbsRet = SysAllocString(L"<ADSTYPE_LARGE_INTEGER>");
			//	hr = pAdsPV->get_OctetString(pbsRet);
		}
		break;
		case ADSTYPE_UTC_TIME :
		{
			DATE daUTCTime;
			WCHAR wDateOut[255];
			hr = pAdsPV->get_UTCTime(&daUTCTime);
			
			if (SUCCEEDED(hr))
			{			
			/*	wsprintf(wDateout,L"%02d/%02d/%04d %02d:%02d:%02d", 
					pValues->UTCTime.wMonth, pValues->UTCTime.wDay, pValues->UTCTime.wYear,
					pValues->UTCTime.wHour, pValues->UTCTime.wMinute, pValues->UTCTime.wSecond );
			*/
				*pbsRet = SysAllocString(wDateOut);
			}
		}
		break;
		case ADSTYPE_LARGE_INTEGER :
		{
			*pbsRet = SysAllocString(L"<ADSTYPE_LARGE_INTEGER>");
		}
		break;
		case ADSTYPE_PROV_SPECIFIC :
		{
			*pbsRet = SysAllocString(L"<ADSTYPE_PROV_SPECIFIC>");
		}
		break;
		case ADSTYPE_OBJECT_CLASS :
		{
			*pbsRet = SysAllocString(L"<ADSTYPE_OBJECT_CLASS>");
		}
		break;
		case ADSTYPE_PATH :
		{
			*pbsRet = SysAllocString(L"<ADSTYPE_PATH>");
		}
		break;
		case ADSTYPE_NT_SECURITY_DESCRIPTOR :
		{
			*pbsRet = SysAllocString(L"<ADSTYPE_NT_SECURITY_DESCRIPTOR>");
		}
		break;
    
		default: 
			*pbsRet = SysAllocString(L"<UNRECOGNIZED>");
		break;
			
	}	
	return hr;
}

// Displays a Messagebox with a BAD Hresult
// Supports standard system COM errors
// And Active Directory Errors
void ADErrMsgBox(HRESULT passedhr)
{
    
    if (SUCCEEDED(passedhr))
        return;

    HRESULT hr;
    DWORD lError;
    WCHAR pwErrBuff[2048];
    WCHAR pwADErrBuff[512];

    WCHAR * pADErrCodeStr;
    
    pwErrBuff[0] = NULL;
    pADErrCodeStr = CrackADError( passedhr);

    // If an ADSI error code was returned, display it
    if (pADErrCodeStr[0] != NULL)
    {
        wcscat(pwErrBuff,L"\t<*> ADSI Error HRESULT Returns: <*> \n");
        wcscat(pwErrBuff,pADErrCodeStr);
        wcscat(pwErrBuff,L"\n");
    }           
    
    // Call ADsGetLastError() to retrieve the error text from ADSI
    wcscat(pwErrBuff,L"\t<*> ADSI Error: <*>\n");
    
    hr = ADsGetLastError(
        &lError,
        pwADErrBuff,
        2047,
        L"",
        0
        );


    if (FAILED(hr))
        wcscat(pwErrBuff,L"<Unable to retrieve ADs Error>");
    else
        wcscat(pwErrBuff,pwADErrBuff);

    wcscat(pwErrBuff,L"\n");
    
    WCHAR sz[1024];
    
    wcscat(pwErrBuff,L"\t<*> System Error: <*> \n");

    // Check the standard system to crack the bad HRESULT into a string
    if (!FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, 0, passedhr, 0, sz, 1024, 0))
        wcscat(sz, L"Unknown HRESULT error");
    else
        wcscat(pwErrBuff, sz);
        
    // Display
    OutputDebugStringW(pwErrBuff);
    OutputDebugStringW(L"\r\n");
    MessageBoxW(NULL,pwErrBuff,L"ADErrMsgBox():",MB_OK);

    #ifdef _DEBUG
        DebugBreak();
    #endif

    #ifdef THROW_CHARPTR_ONERROR
        throw pwErrBuff;
    #endif


}


WCHAR * CrackADError(HRESULT hResult)
{
   static WCHAR szwText[ 128 ];
   szwText[0] = 0l;

   switch( hResult )
   {
      case  E_ADS_BAD_PATHNAME:
         return L"E_ADS_BAD_PATHNAME";
         break;

      case  E_ADS_INVALID_DOMAIN_OBJECT:
         return L"E_ADS_INVALID_DOMAIN_OBJECT";
         break;

      case  E_ADS_INVALID_USER_OBJECT:
         return L"E_ADS_INVALID_USER_OBJECT";
         break;

      case  E_ADS_INVALID_COMPUTER_OBJECT:
         return L"E_ADS_INVALID_COMPUTER_OBJECT";
         break;

      case  E_ADS_UNKNOWN_OBJECT:
         return L"E_ADS_UNKNOWN_OBJECT";
         break;

      case  E_ADS_PROPERTY_NOT_SET:
         return L"E_ADS_PROPERTY_NOT_SET";
         break;

      case  E_ADS_PROPERTY_NOT_SUPPORTED:
         return L"E_ADS_PROPERTY_NOT_SUPPORTED";
         break;

      case  E_ADS_PROPERTY_INVALID:
         return L"E_ADS_PROPERTY_INVALID";
         break;

      case  E_ADS_BAD_PARAMETER:
         return L"E_ADS_BAD_PARAMETER";
         break;

      case  E_ADS_OBJECT_UNBOUND:
         return L"E_ADS_OBJECT_UNBOUND";
         break;

      case  E_ADS_PROPERTY_NOT_MODIFIED:
         return L"E_ADS_PROPERTY_NOT_MODIFIED";
         break;

      case  E_ADS_PROPERTY_MODIFIED:
         return L"E_ADS_PROPERTY_MODIFIED";
         break;

      case  E_ADS_CANT_CONVERT_DATATYPE:
         return L"E_ADS_CANT_CONVERT_DATATYPE";
         break;

      case  E_ADS_PROPERTY_NOT_FOUND:
         return L"E_ADS_PROPERTY_NOTFOUND";
         break;

      case  E_ADS_OBJECT_EXISTS:
         return L"E_ADS_OBJECT_EXISTS";
         break;

      case  E_ADS_SCHEMA_VIOLATION:
         return L"E_ADS_SCHEMA_VIOLATION";
         break;

      case  E_ADS_COLUMN_NOT_SET:
         return L"E_ADS_COLUMN_NOT_SET";
         break;

      case  E_ADS_INVALID_FILTER:
         return L"E_ADS_INVALID_FILTER";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_OPERATIONS_ERROR):
         return L"ERROR_DS_OPERATIONS_ERROR";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_PROTOCOL_ERROR):
         return L"ERROR_DS_PROTOCOL_ERROR";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_TIMELIMIT_EXCEEDED):
         return L"ERROR_DS_TIMELIMIT_EXCEEDED";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_SIZELIMIT_EXCEEDED):
         return L"ERROR_DS_SIZELIMIT_EXCEEDED";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_COMPARE_FALSE):
         return L"ERROR_DS_COMPARE_FALSE";
         break;


      case  HRESULT_FROM_WIN32(ERROR_DS_COMPARE_TRUE):
         return L"ERROR_DS_COMPARE_TRUE";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_AUTH_METHOD_NOT_SUPPORTED):
         return L"ERROR_DS_AUTH_METHOD_NOT_SUPPORTED";
         break;


      case  HRESULT_FROM_WIN32(ERROR_DS_STRONG_AUTH_REQUIRED):
         return L"ERROR_DS_STRONG_AUTH_REQUIRED";
         break;


      case  HRESULT_FROM_WIN32(ERROR_MORE_DATA):
         return L"ERROR_MORE_DATA";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_REFERRAL):
         return L"(ERROR_DS_REFERRAL";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_ADMIN_LIMIT_EXCEEDED):
         return L"ERROR_DS_ADMIN_LIMIT_EXCEEDED";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_UNAVAILABLE_CRIT_EXTENSION):
         return L"(ERROR_DS_UNAVAILABLE_CRIT_EXTENSION";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_CONFIDENTIALITY_REQUIRED):
         return L"HRESULT_FROM_WIN32(ERROR_DS_CONFIDENTIALITY_REQUIRED";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_NO_ATTRIBUTE_OR_VALUE):
         return L"ERROR_DS_NO_ATTRIBUTE_OR_VALUE";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_ATTRIBUTE_TYPE_UNDEFINED):
         return L"(ERROR_DS_ATTRIBUTE_TYPE_UNDEFINED";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_INAPPROPRIATE_MATCHING):
         return L"(ERROR_DS_INAPPROPRIATE_MATCHING";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_CONSTRAINT_VIOLATION):
         return L"ERROR_DS_CONSTRAINT_VIOLATION";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_ATTRIBUTE_OR_VALUE_EXISTS):
         return L"ERROR_DS_ATTRIBUTE_OR_VALUE_EXISTS";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_INVALID_ATTRIBUTE_SYNTAX):
         return L"ERROR_DS_INVALID_ATTRIBUTE_SYNTAX";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_NO_SUCH_OBJECT):
         return L"ERROR_DS_NO_SUCH_OBJECT";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_INVALID_DN_SYNTAX):
         return L"ERROR_DS_INVALID_DN_SYNTAX";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_IS_LEAF):
         return L"ERROR_DS_IS_LEAF";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_ALIAS_DEREF_PROBLEM):
         return L"ERROR_DS_ALIAS_DEREF_PROBLEM";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_INAPPROPRIATE_AUTH):
         return L"ERROR_DS_INAPPROPRIATE_AUTH";
         break;

      case  HRESULT_FROM_WIN32(ERROR_INVALID_PASSWORD):
         return L"ERROR_INVALID_PASSWORD";
         break;

      case  HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED):
         return L"ERROR_ACCESS_DENIED";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_BUSY):
         return L"ERROR_DS_BUSY";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_UNAVAILABLE):
         return L"ERROR_DS_UNAVAILABLE";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_UNWILLING_TO_PERFORM):
         return L"ERROR_DS_UNWILLING_TO_PERFORM";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_LOOP_DETECT):
         return L"ERROR_DS_LOOP_DETECT";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_NAMING_VIOLATION):
         return L"ERROR_DS_NAMING_VIOLATION";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_OBJ_CLASS_VIOLATION):
         return L"ERROR_DS_OBJ_CLASS_VIOLATION";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_CANT_ON_NON_LEAF):
         return L"ERROR_DS_CANT_ON_NONLEAF";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_CANT_ON_RDN):
         return L"ERROR_DS_CANT_ON_RDN";
         break;

      case  HRESULT_FROM_WIN32(ERROR_ALREADY_EXISTS):
         return L"ERROR_ALREADY_EXISTS";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_CANT_MOD_OBJ_CLASS):
         return L"ERROR_DS_CANT_MOD_OBJ_CLASS";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_OBJECT_RESULTS_TOO_LARGE):
         return L"ERROR_DS_OBJECT_RESULTS_TOO_LARGE";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_AFFECTS_MULTIPLE_DSAS):
         return L"ERROR_DS_AFFECTS_MULTIPLE_DSAS";
         break;

      case  HRESULT_FROM_WIN32(ERROR_GEN_FAILURE):
         return L"(ERROR_GEN_FAILURE";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_SERVER_DOWN):
         return L"ERROR_DS_SERVER_DOWN";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_LOCAL_ERROR):
         return L"ERROR_DS_LOCAL_ERROR";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_ENCODING_ERROR):
         return L"ERROR_DS_ENCODING_ERROR";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_DECODING_ERROR):
         return L"(ERROR_DS_DECODING_ERROR";
         break;

      case  HRESULT_FROM_WIN32(ERROR_TIMEOUT):
         return L"(ERROR_TIMEOUT";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_AUTH_UNKNOWN):
         return L"ERROR_DS_AUTH_UNKNOWN";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_FILTER_UNKNOWN):
         return L"(ERROR_DS_FILTER_UNKNOWN";
         break;

      case  HRESULT_FROM_WIN32(ERROR_CANCELLED):
         return L"(ERROR_CANCELLED";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_PARAM_ERROR):
         return L"ERROR_DS_PARAM_ERROR";
         break;

      case  HRESULT_FROM_WIN32(ERROR_NOT_ENOUGH_MEMORY):
         return L"ERROR_NOT_ENOUGH_MEMORY";
         break;

      case  HRESULT_FROM_WIN32(ERROR_CONNECTION_REFUSED):
         return L"ERROR_CONNECTION_REFUSED";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_NOT_SUPPORTED):
         return L"ERROR_DS_NOT_SUPPORTED";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_NO_RESULTS_RETURNED):
         return L"ERROR_DS_NO_RESULTS_RETURNED";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_CONTROL_NOT_FOUND):
         return L"ERROR_DS_CONTROL_NOT_FOUND";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_CLIENT_LOOP):
         return L"(ERROR_DS_CLIENT_LOOP";
         break;

      case  HRESULT_FROM_WIN32(ERROR_DS_REFERRAL_LIMIT_EXCEEDED):
         return L"ERROR_DS_REFERRAL_LIMIT_EXCEEDED";
         break;

      case  E_FAIL:
         return L"E_FAIL";
         break;

      case  E_NOTIMPL:
         return L"E_NOIMPL";
         break;

      case  S_OK:
         return L"OK";
         break;

      case  0x800704b8:
      // we have an extended error
      {
         WCHAR szErrorBuff[ 1024 ];
         WCHAR szNameBuff[ 1024 ];
         DWORD dwError;

         ADsGetLastError( &dwError,
                          szErrorBuff,
                          1023,
                          szNameBuff,
                          1023 );
         wcscat( szNameBuff, L" : " );
         wcscat( szNameBuff, szErrorBuff );
         wcscpy( szwText,szNameBuff);

         return szwText;
      }

   }

    return szwText; 
}



// Takes an ADSTYPE and converts it to a string
const char * AdsTypeToChar(long AdsType)
{
	static char pAdsChar[200];
	pAdsChar[0] = NULL;

	switch (AdsType)
	{
	
		case ADSTYPE_INVALID :
			strcpy(pAdsChar,"ADSTYPE_INVALID");
		break;
		case ADSTYPE_DN_STRING :
			strcpy(pAdsChar,"ADSTYPE_DN_STRING");
		break;
		case ADSTYPE_CASE_EXACT_STRING :
			strcpy(pAdsChar,"ADSTYPE_CASE_EXACT_STRING");
		break;
		case ADSTYPE_CASE_IGNORE_STRING :
			strcpy(pAdsChar,"ADSTYPE_CASE_IGNORE_STRING");
		break;
		case ADSTYPE_PRINTABLE_STRING :
			strcpy(pAdsChar,"ADSTYPE_PRINTABLE_STRING");
		break;
		case ADSTYPE_NUMERIC_STRING :
			strcpy(pAdsChar,"ADSTYPE_NUMERIC_STRING");
		break;
		case ADSTYPE_BOOLEAN :
			strcpy(pAdsChar,"ADSTYPE_BOOLEAN");
		break;
		case ADSTYPE_INTEGER :
			strcpy(pAdsChar,"ADSTYPE_INTEGER");
		break;
		case ADSTYPE_OCTET_STRING :
			strcpy(pAdsChar,"ADSTYPE_OCTET_STRING");
		break;
		case ADSTYPE_UTC_TIME :
			strcpy(pAdsChar,"ADSTYPE_UTC_TIME");
		break;
		case ADSTYPE_LARGE_INTEGER :
			strcpy(pAdsChar,"ADSTYPE_LARGE_INTEGER");
		break;
		case ADSTYPE_PROV_SPECIFIC :
			strcpy(pAdsChar,"ADSTYPE_PROV_SPECIFIC");
		break;
		case ADSTYPE_OBJECT_CLASS :
			strcpy(pAdsChar,"ADSTYPE_OBJECT_CLASS");
		break;
		case ADSTYPE_PATH :
			strcpy(pAdsChar,"ADSTYPE_PATH");
		break;
		case ADSTYPE_NT_SECURITY_DESCRIPTOR :
			strcpy(pAdsChar,"ADSTYPE_NT_SECURITY_DESCRIPTOR");
		break;
    
		default: 
			strcpy(pAdsChar,"<UNRECOGNIZED>");
		break;
			
	}	
	return pAdsChar;


}


								   
struct IIDLookUp
{
	GUID id;
	char * pIDName;

	IIDLookUp(GUID iNewID,char * pNewIDName) :
	id(iNewID), pIDName(pNewIDName) {};
};


IIDLookUp    arIDs [] = 
{
IIDLookUp(IID_IEnumGUID,							"IID_IEnumGUID"),                         
IIDLookUp(IID_IEnumCATEGORYINFO,					"IID_IEnumCATEGORYINFO"),                 
IIDLookUp(IID_ICatRegister,							"IID_ICatRegister"),                      
IIDLookUp(IID_ICatInformation,						"IID_ICatInformation"),                   
IIDLookUp(IID_IOleDocument,							"IID_IOleDocument"),                      
IIDLookUp(IID_IOleDocumentSite,						"IID_IOleDocumentSite"),                  
IIDLookUp(IID_IOleDocumentView,						"IID_IOleDocumentView"),                  
IIDLookUp(IID_IEnumOleDocumentViews,				"IID_IEnumOleDocumentViews"),             
IIDLookUp(IID_IContinueCallback,					"IID_IContinueCallback"),                 
IIDLookUp(IID_IPrint,								"IID_IPrint"),                            
IIDLookUp(IID_IOleCommandTarget,					"IID_IOleCommandTarget"),                 
IIDLookUp(IID_IHlink,								"IID_IHlink"),                            
IIDLookUp(IID_IHlinkSite,							"IID_IHlinkSite"),                        
IIDLookUp(IID_IHlinkTarget,							"IID_IHlinkTarget"),                      
IIDLookUp(IID_IHlinkFrame,							"IID_IHlinkFrame"),                       
IIDLookUp(IID_IEnumHLITEM,							"IID_IEnumHLITEM"),                       
IIDLookUp(IID_IHlinkBrowseContext,					"IID_IHlinkBrowseContext"),               
IIDLookUp(IID_ICreateTypeInfo,						"IID_ICreateTypeInfo"),                   
IIDLookUp(IID_ICreateTypeInfo2,						"IID_ICreateTypeInfo2"),                  
IIDLookUp(IID_ICreateTypeLib,						"IID_ICreateTypeLib"),                    
IIDLookUp(IID_ICreateTypeLib2,						"IID_ICreateTypeLib2"),                   
IIDLookUp(IID_IDispatch,							"IID_IDispatch"),                         
IIDLookUp(IID_IEnumVARIANT,							"IID_IEnumVARIANT"),                      
IIDLookUp(IID_ITypeComp,							"IID_ITypeComp"),                         
IIDLookUp(IID_ITypeInfo,							"IID_ITypeInfo"),                         
IIDLookUp(IID_ITypeInfo2,							"IID_ITypeInfo2"),                        
IIDLookUp(IID_ITypeLib,								"IID_ITypeLib"),                          
IIDLookUp(IID_ITypeLib2,							"IID_ITypeLib2"),                         
IIDLookUp(IID_ITypeChangeEvents,					"IID_ITypeChangeEvents"),                 
IIDLookUp(IID_IErrorInfo,							"IID_IErrorInfo"),                        
IIDLookUp(IID_ICreateErrorInfo,						"IID_ICreateErrorInfo"),                  
IIDLookUp(IID_ISupportErrorInfo,					"IID_ISupportErrorInfo"),                 
IIDLookUp(IID_IMarshal,								"IID_IMarshal"),                          
IIDLookUp(IID_IMalloc,								"IID_IMalloc"),                           
IIDLookUp(IID_IMallocSpy,							"IID_IMallocSpy"),                        
IIDLookUp(IID_IStdMarshalInfo,						"IID_IStdMarshalInfo"),                   
IIDLookUp(IID_IExternalConnection,					"IID_IExternalConnection"),               
IIDLookUp(IID_IMultiQI,								"IID_IMultiQI"),                          
IIDLookUp(IID_IEnumUnknown,							"IID_IEnumUnknown"),                      
IIDLookUp(IID_IBindCtx,								"IID_IBindCtx"),                          
IIDLookUp(IID_IEnumMoniker,							"IID_IEnumMoniker"),                      
IIDLookUp(IID_IRunnableObject,						"IID_IRunnableObject"),                   
IIDLookUp(IID_IRunningObjectTable,					"IID_IRunningObjectTable"),               
IIDLookUp(IID_IPersist,								"IID_IPersist"),                          
IIDLookUp(IID_IPersistStream,						"IID_IPersistStream"),                    
IIDLookUp(IID_IMoniker,								"IID_IMoniker"),                          
IIDLookUp(IID_IROTData,								"IID_IROTData"),                          
IIDLookUp(IID_IEnumString,							"IID_IEnumString"),                       
IIDLookUp(IID_ISequentialStream,					"IID_ISequentialStream"),                 
IIDLookUp(IID_IStream,								"IID_IStream"),                           
IIDLookUp(IID_IEnumSTATSTG,							"IID_IEnumSTATSTG"),                      
IIDLookUp(IID_IStorage,								"IID_IStorage"),                          
IIDLookUp(IID_IPersistFile,							"IID_IPersistFile"),                      
IIDLookUp(IID_IPersistStorage,						"IID_IPersistStorage"),                   
IIDLookUp(IID_ILockBytes,							"IID_ILockBytes"),                        
IIDLookUp(IID_IEnumFORMATETC,						"IID_IEnumFORMATETC"),                    
IIDLookUp(IID_IEnumSTATDATA,						"IID_IEnumSTATDATA"),                     
IIDLookUp(IID_IRootStorage,							"IID_IRootStorage"),                      
IIDLookUp(IID_IAdviseSink,							"IID_IAdviseSink"),                       
IIDLookUp(IID_IAdviseSink2,							"IID_IAdviseSink2"),                      
IIDLookUp(IID_IDataObject,							"IID_IDataObject"),                       
IIDLookUp(IID_IDataAdviseHolder,					"IID_IDataAdviseHolder"),                 
IIDLookUp(IID_IMessageFilter,						"IID_IMessageFilter"),                    
IIDLookUp(IID_IRpcChannelBuffer,					"IID_IRpcChannelBuffer"),                 
IIDLookUp(IID_IRpcProxyBuffer,						"IID_IRpcProxyBuffer"),                   
IIDLookUp(IID_IRpcStubBuffer,						"IID_IRpcStubBuffer"),                    
IIDLookUp(IID_IPSFactoryBuffer,						"IID_IPSFactoryBuffer"),                  
IIDLookUp(IID_IPropertyStorage,						"IID_IPropertyStorage"),                  
IIDLookUp(IID_IPropertySetStorage,					"IID_IPropertySetStorage"),               
IIDLookUp(IID_IEnumSTATPROPSTG,						"IID_IEnumSTATPROPSTG"),                  
IIDLookUp(IID_IEnumSTATPROPSETSTG,					"IID_IEnumSTATPROPSETSTG"),               
IIDLookUp(IID_IFillLockBytes,						"IID_IFillLockBytes"),                    
IIDLookUp(IID_IProgressNotify,						"IID_IProgressNotify"),                   
IIDLookUp(IID_ILayoutStorage,						"IID_ILayoutStorage"),                    
IIDLookUp(IID_IEnumConnections,						"IID_IEnumConnections"),                  
IIDLookUp(IID_IConnectionPoint,						"IID_IConnectionPoint"),                  
IIDLookUp(IID_IEnumConnectionPoints,				"IID_IEnumConnectionPoints"),             
IIDLookUp(IID_IConnectionPointContainer,			"IID_IConnectionPointContainer"),         
IIDLookUp(IID_IClassFactory2,						"IID_IClassFactory2"),                    
IIDLookUp(IID_IProvideClassInfo,					"IID_IProvideClassInfo"),                 
IIDLookUp(IID_IProvideClassInfo2,					"IID_IProvideClassInfo2"),                
IIDLookUp(IID_IOleControl,							"IID_IOleControl"),                       
IIDLookUp(IID_IOleControlSite,						"IID_IOleControlSite"),                   
IIDLookUp(IID_IPropertyPage,						"IID_IPropertyPage"),                     
IIDLookUp(IID_IPropertyPage2,						"IID_IPropertyPage2"),                    
IIDLookUp(IID_IPropertyPageSite,					"IID_IPropertyPageSite"),                 
IIDLookUp(IID_IPropertyNotifySink,					"IID_IPropertyNotifySink"),               
IIDLookUp(IID_ISpecifyPropertyPages,				"IID_ISpecifyPropertyPages"),             
IIDLookUp(IID_IPersistMemory,						"IID_IPersistMemory"),                    
IIDLookUp(IID_IPersistStreamInit,					"IID_IPersistStreamInit"),                
IIDLookUp(IID_IPersistPropertyBag,					"IID_IPersistPropertyBag"),               
IIDLookUp(IID_ISimpleFrameSite,						"IID_ISimpleFrameSite"),                  
IIDLookUp(IID_IFont,								"IID_IFont"),                             
IIDLookUp(IID_IPicture,								"IID_IPicture"),                          
IIDLookUp(IID_IFontDisp,							"IID_IFontDisp"),                         
IIDLookUp(IID_IPictureDisp,							"IID_IPictureDisp"),                      
IIDLookUp(IID_IAdviseSinkEx,						"IID_IAdviseSinkEx"),                     
IIDLookUp(IID_IOleInPlaceObjectWindowless,			"IID_IOleInPlaceObjectWindowless"),       
IIDLookUp(IID_IOleInPlaceSiteEx,					"IID_IOleInPlaceSiteEx"),                 
IIDLookUp(IID_IOleInPlaceSiteWindowless,			"IID_IOleInPlaceSiteWindowless"),         
IIDLookUp(IID_IViewObjectEx,						"IID_IViewObjectEx"),                     
IIDLookUp(IID_IOleUndoUnit,							"IID_IOleUndoUnit"),                      
IIDLookUp(IID_IOleParentUndoUnit,					"IID_IOleParentUndoUnit"),                
IIDLookUp(IID_IEnumOleUndoUnits,					"IID_IEnumOleUndoUnits"),                 
IIDLookUp(IID_IOleUndoManager,						"IID_IOleUndoManager"),                   
IIDLookUp(IID_IQuickActivate,						"IID_IQuickActivate"),                    
IIDLookUp(IID_IPointerInactive,						"IID_IPointerInactive"),                  
IIDLookUp(IID_IObjectWithSite,						"IID_IObjectWithSite"),                   
IIDLookUp(IID_IErrorLog,							"IID_IErrorLog"),                         
IIDLookUp(IID_IPropertyBag,							"IID_IPropertyBag"),                      
IIDLookUp(IID_IPerPropertyBrowsing,					"IID_IPerPropertyBrowsing"),              
IIDLookUp(IID_StdOle,								"IID_StdOle"),                            
IIDLookUp(IID_IOleAdviseHolder,						"IID_IOleAdviseHolder"),                  
IIDLookUp(IID_IOleCache,							"IID_IOleCache"),                         
IIDLookUp(IID_IOleCache2,							"IID_IOleCache2"),                        
IIDLookUp(IID_IOleCacheControl,						"IID_IOleCacheControl"),                  
IIDLookUp(IID_IParseDisplayName,					"IID_IParseDisplayName"),                 
IIDLookUp(IID_IOleContainer,						"IID_IOleContainer"),                     
IIDLookUp(IID_IOleClientSite,						"IID_IOleClientSite"),                    
IIDLookUp(IID_IOleObject,							"IID_IOleObject"),                        
IIDLookUp(IID_IOleWindow,							"IID_IOleWindow"),                        
IIDLookUp(IID_IOleLink,								"IID_IOleLink"),                          
IIDLookUp(IID_IOleItemContainer,					"IID_IOleItemContainer"),                 
IIDLookUp(IID_IOleInPlaceUIWindow,					"IID_IOleInPlaceUIWindow"),               
IIDLookUp(IID_IOleInPlaceActiveObject,				"IID_IOleInPlaceActiveObject"),           
IIDLookUp(IID_IOleInPlaceFrame,						"IID_IOleInPlaceFrame"),                  
IIDLookUp(IID_IOleInPlaceObject,					"IID_IOleInPlaceObject"),                 
IIDLookUp(IID_IOleInPlaceSite,						"IID_IOleInPlaceSite"),                   
IIDLookUp(IID_IContinue,							"IID_IContinue"),                         
IIDLookUp(IID_IViewObject,							"IID_IViewObject"),                       
IIDLookUp(IID_IViewObject2,							"IID_IViewObject2"),                      
IIDLookUp(IID_IDropSource,							"IID_IDropSource"),                       
IIDLookUp(IID_IDropTarget,							"IID_IDropTarget"),                       
IIDLookUp(IID_IEnumOLEVERB,							"IID_IEnumOLEVERB"),                      
IIDLookUp(IID_IServiceProvider,						"IID_IServiceProvider"),                  
IIDLookUp(IID_IUnknown,								"IID_IUnknown"),                          
IIDLookUp(IID_IClassFactory,						"IID_IClassFactory"),                     
IIDLookUp(IID_IAsyncMoniker,   						"IID_IAsyncMoniker"),                     
IIDLookUp(CLSID_StdURLMoniker, 						"CLSID_StdURLMoniker"),                   
IIDLookUp(CLSID_HttpProtocol,   					"CLSID_HttpProtocol"),                    
IIDLookUp(CLSID_FtpProtocol,    					"CLSID_FtpProtocol"),                     
IIDLookUp(CLSID_GopherProtocol, 					"CLSID_GopherProtocol"),                  
IIDLookUp(CLSID_HttpSProtocol,  					"CLSID_HttpSProtocol"),                   
IIDLookUp(CLSID_FileProtocol,   					"CLSID_FileProtocol"),                    
IIDLookUp(CLSID_MkProtocol,     					"CLSID_MkProtocol"),                      
IIDLookUp(IID_IPersistMoniker,						"IID_IPersistMoniker"),                   
IIDLookUp(IID_IBindProtocol,						"IID_IBindProtocol"),                     
IIDLookUp(IID_IBinding,								"IID_IBinding"),                          
IIDLookUp(IID_IBindStatusCallback,					"IID_IBindStatusCallback"),               
IIDLookUp(IID_IAuthenticate,						"IID_IAuthenticate"),                     
IIDLookUp(IID_IHttpNegotiate,						"IID_IHttpNegotiate"),                    
IIDLookUp(IID_IWindowForBindingUI,					"IID_IWindowForBindingUI"),               
IIDLookUp(IID_ICodeInstall,							"IID_ICodeInstall"),                      
IIDLookUp(IID_IWinInetInfo,							"IID_IWinInetInfo"),                      
IIDLookUp(IID_IHttpSecurity,						"IID_IHttpSecurity"),                     
IIDLookUp(IID_IWinInetHttpInfo,						"IID_IWinInetHttpInfo"),                  
IIDLookUp(IID_IBindHost,							"IID_IBindHost"),
IIDLookUp(IID_IUnknown,								"IID_IUnknown"),

// ADSI stuff
IIDLookUp(IID_IADs,									"IID_IADs"),
IIDLookUp(IID_IADsContainer,						"IID_IADsContainer"),
IIDLookUp(IID_IADsCollection,						"IID_IADsCollection"),
IIDLookUp(IID_IADsMembers,							"IID_IADsMembers"),
IIDLookUp(IID_IADsPropertyList,						"IID_IADsPropertyList"),
IIDLookUp(IID_IADsPropertyEntry,					"IID_IADsPropertyEntry"),
IIDLookUp(IID_IADsPropertyValue,					"IID_IADsPropertyValue"),
//IIDLookUp(IID_IADsPropertyValueEx,					"IID_IADsPropertyValueEx"),
//IIDLookUp(IID_IADsValue,							"IID_IADsValue"),
IIDLookUp(IID_IPrivateDispatch,						"IID_IPrivateDispatch"),
IIDLookUp(IID_IPrivateUnknown,						"IID_IPrivateUnknown"),
IIDLookUp(IID_IADsExtension,						"IID_IADsExtension"),
IIDLookUp(IID_IADsDeleteOps,						"IID_IADsDeleteOps"),
IIDLookUp(IID_IADsNamespaces,						"IID_IADsNamespaces"),
IIDLookUp(IID_IADsClass,							"IID_IADsClass"),
IIDLookUp(IID_IADsProperty,							"IID_IADsProperty"),
IIDLookUp(IID_IADsSyntax,							"IID_IADsSyntax"),
IIDLookUp(IID_IADsLocality,							"IID_IADsLocality"),
IIDLookUp(IID_IADsO,								"IID_IADsO"),
IIDLookUp(IID_IADsOU,								"IID_IADsOU"),
IIDLookUp(IID_IADsDomain,							"IID_IADsDomain"),
IIDLookUp(IID_IADsComputer,							"IID_IADsComputer"),
IIDLookUp(IID_IADsComputerOperations,				"IID_IADsComputerOperations"),
IIDLookUp(IID_IADsGroup,							"IID_IADsGroup"),
IIDLookUp(IID_IADsUser,								"IID_IADsUser"),
IIDLookUp(IID_IADsPrintQueue,						"IID_IADsPrintQueue"),
IIDLookUp(IID_IADsPrintQueueOperations,				"IID_IADsPrintQueueOperations"),
IIDLookUp(IID_IADsPrintJob,							"IID_IADsPrintJob"),
IIDLookUp(IID_IADsPrintJobOperations,				"IID_IADsPrintJobOperations"),
IIDLookUp(IID_IADsService,							"IID_IADsService"),
IIDLookUp(IID_IADsServiceOperations,				"IID_IADsServiceOperations"),
IIDLookUp(IID_IADsFileService,						"IID_IADsFileService"),
IIDLookUp(IID_IADsFileServiceOperations,			"IID_IADsFileServiceOperations"),
IIDLookUp(IID_IADsFileShare,						"IID_IADsFileShare"),
IIDLookUp(IID_IADsSession,							"IID_IADsSession"),
IIDLookUp(IID_IADsResource,							"IID_IADsResource"),
IIDLookUp(IID_IADsOpenDSObject,						"IID_IADsOpenDSObject"),
IIDLookUp(IID_IDirectoryObject,						"IID_IDirectoryObject"),
IIDLookUp(IID_IDirectorySearch,						"IID_IDirectorySearch"),
//IIDLookUp(IID_IDirectoryAttrMgmt,					"IID_IDirectoryAttrMgmt"),
IIDLookUp(IID_IADsAccessControlEntry,				"IID_IADsAccessControlEntry"),
IIDLookUp(IID_IADsAccessControlList,				"IID_IADsAccessControlList"),
IIDLookUp(IID_IADsSecurityDescriptor,				"IID_IADsSecurityDescriptor"),
IIDLookUp(IID_IADsLargeInteger,						"IID_IADsLargeInteger"),
IIDLookUp(IID_IADsNameTranslate,					"IID_IADsNameTranslate"),
IIDLookUp(IID_IADsCaseIgnoreList,					"IID_IADsCaseIgnoreList"),
IIDLookUp(IID_IADsFaxNumber,						"IID_IADsFaxNumber"),
IIDLookUp(IID_IADsNetAddress,						"IID_IADsNetAddress"),
IIDLookUp(IID_IADsOctetList,						"IID_IADsOctetList"),
IIDLookUp(IID_IADsEmail,							"IID_IADsEmail"),
IIDLookUp(IID_IADsPath,								"IID_IADsPath"),
IIDLookUp(IID_IADsReplicaPointer,					"IID_IADsReplicaPointer"),
IIDLookUp(IID_IADsAcl,								"IID_IADsAcl"),
IIDLookUp(IID_IADsTimestamp,						"IID_IADsTimestamp"),
IIDLookUp(IID_IADsPostalAddress,					"IID_IADsPostalAddress"),
IIDLookUp(IID_IADsBackLink,							"IID_IADsBackLink"),
IIDLookUp(IID_IADsTypedName,						"IID_IADsTypedName"),
IIDLookUp(IID_IADsHold,								"IID_IADsHold"),
IIDLookUp(IID_IADsObjectOptions,					"IID_IADsObjectOptions"),

// Last ONE
IIDLookUp(IID_IUnknown,NULL)
};


inline BOOL AretheGUIDsEqual(REFGUID rguid1, REFGUID rguid2)
{
   return (
	  ((PLONG) &rguid1)[0] == ((PLONG) &rguid2)[0] &&
	  ((PLONG) &rguid1)[1] == ((PLONG) &rguid2)[1] &&
	  ((PLONG) &rguid1)[2] == ((PLONG) &rguid2)[2] &&
	  ((PLONG) &rguid1)[3] == ((PLONG) &rguid2)[3]);
}


// Returns a string descriing the passed GUID
char * GetCharFromGUID(GUID idtofind)
{
	int x =0;

	while(arIDs[x].pIDName && !AretheGUIDsEqual(arIDs[x].id ,idtofind))
		x++;

	return arIDs[x].pIDName ;
}

char pQueryAllInterfacesOut[5000];

// Queries ALL the interfaces of passed in IUNknown
// returns a string with a space delimited list of the
// interfaces
const char * QueryAllInterfaces(IUnknown * pUnk)
{

	int x = 0;
	int iLen = sizeof(arIDs)/sizeof(IIDLookUp);
	pQueryAllInterfacesOut[0] = NULL;
	IUnknown * pGetUnk = NULL;

	for (x = 0; x < iLen; x++)
	{
		if(SUCCEEDED(pUnk->QueryInterface(arIDs[x].id,(void **) &pGetUnk)))
		{
			if (arIDs[x].pIDName)
			{
				strcat (pQueryAllInterfacesOut,arIDs[x].pIDName );
				strcat (pQueryAllInterfacesOut,"\n ");
				pGetUnk->Release();
				pGetUnk = NULL;
			}		
		}	
	}
	return pQueryAllInterfacesOut;
}
