// IADsError.cpp : Implementation of CADsErrorApp and DLL registration.

#include "stdafx.h"
#include "ADsError.h"
#include "IADsError.h"


/////////////////////////////////////////////////////
//
// Private Functions
HRESULT GetADSIError( HRESULT hr, CComBSTR &bstr );
HRESULT GetErrorMessage( HRESULT hr, CComBSTR &bstr );
BOOL GetMessageHelper(DWORD flags, HMODULE hModule, HRESULT hr, CComBSTR &bstr );


/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP ADsError::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IADsError,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP ADsError::GetErrorMessage(long hResult, BSTR *pbMsg)
{
	CComBSTR bstr;
	HRESULT hr;
	hr = ::GetErrorMessage( hResult, bstr );

	if ( SUCCEEDED(hr) )
	{
		*pbMsg = SysAllocString(bstr);
	}
	

	return hr;
}



////////////////////////////////////////////////////////
//
// ADSI Error Message
//
////////////////////////////////////////////////////////

#define FACILITY_ADSI	 0x00005000



HRESULT GetErrorMessage( HRESULT hr, CComBSTR &bstr )
{

	bstr.Empty();
	if ( SUCCEEDED(hr) )
	{
		bstr = _T("SUCCESS");
		return S_OK;
	}

	int code = HRESULT_CODE(hr);

    if (code == -1)
    {
       bstr = _T("Unknown Error Code");
	   return S_OK;
    }

	// default is the system error message table
   HMODULE hModule = 0;

   DWORD dwFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS |FORMAT_MESSAGE_FROM_SYSTEM;

   int facility = HRESULT_FACILITY(hr);
   if ( hr & FACILITY_ADSI ) // standard ADSI Errors 
   {
		
        static HMODULE adsi_err_res_dll = 0;
        // use the net error message resource dll
        if (adsi_err_res_dll == 0)
        {
               adsi_err_res_dll =LoadLibraryEx(_T("activeds.dll"), NULL, LOAD_LIBRARY_AS_DATAFILE);
        }

        hModule = adsi_err_res_dll;
        dwFlags |= FORMAT_MESSAGE_FROM_HMODULE;

        // the message dll expects the entire error code
        code = hr;

   }
   else
   {

		switch (facility)
		{

			case FACILITY_WIN32:    // 0x7
			{
				// included here:
				// lanman error codes (in it's own dll)
				// dns
				// winsock

		         static HMODULE lm_err_res_dll = 0;
				 if (code >= NERR_BASE && code <= MAX_NERR)
				 {
					// use the net error message resource dll
					if (lm_err_res_dll == 0)
					{
						lm_err_res_dll = LoadLibraryEx(_T("netmsg.dll"), NULL, LOAD_LIBRARY_AS_DATAFILE);
					}

					hModule = lm_err_res_dll;
					dwFlags |= FORMAT_MESSAGE_FROM_HMODULE;
				 }
			}
			break;

			case FACILITY_SSPI: // 0x9
			{
				// some of these are in their own dll (those declared in issperr.h),
				// some are in the system message tables.
				// first try the system message tables.
				CComBSTR bTest;
				if( !GetMessageHelper( dwFlags, 0, code, bTest ) )
				{
					// not found.  try the secur32.dll resources
		            // @@ use SafeDLL here.
					static HMODULE sec_err_res_dll = 0;
					if (sec_err_res_dll == 0)
					{
						sec_err_res_dll = LoadLibraryEx(_T("secur32.dll"), NULL, LOAD_LIBRARY_AS_DATAFILE);
					}

					hModule = sec_err_res_dll;
					dwFlags |= FORMAT_MESSAGE_FROM_HMODULE;
				}
				break;
			}

			default:
			{
				//do nothing;
				break;
			}


		} // switch




   } // end else


	// Retrieve the message
    GetMessageHelper( dwFlags, hModule, code, bstr );




	
	//////////////////////////////////////////////////////////////////
	//
	// Extended error message may be occured. 
	//
	// IADs, IADsContainer, IDirectoryObject or IDirectorySearch may return
	// this extended error message
	//
	////////////////////////////////////////////////////////////////////

	if (  (hr & FACILITY_ADSI)  ||         //adsi
		  facility == FACILITY_WIN32  )   // and win32
	{
		WCHAR szBuffer[MAX_PATH];
		WCHAR szName[MAX_PATH];
		DWORD dwError;
	

		hr = ADsGetLastError( &dwError, szBuffer, (sizeof(szBuffer)/sizeof(WCHAR))-1,
			                  szName, (sizeof(szName)/sizeof(WCHAR))-1 );
	
	
		if ( SUCCEEDED(hr) && dwError != ERROR_INVALID_DATA  && wcslen(szBuffer))
		{
			USES_CONVERSION;
			bstr.Append(_T("  -- Extended Error:"));
			bstr.Append(szName);
			bstr.Append(_T(" : "));
			bstr.Append( szBuffer );
		}
	}


	return S_OK;
}






BOOL GetMessageHelper(DWORD dwFlags, HMODULE hModule, HRESULT hr, CComBSTR &bstr )
{
	    BOOL bRet;
		LPTSTR lpBuffer=NULL;

		/////////////////////////////////////////////
		//
		// Retrieve the Error message
		//
		/////////////////////////////////////////////////

		bRet = FormatMessage(dwFlags,
							 hModule,  hr,
							 MAKELANGID(LANG_NEUTRAL, SUBLANG_SYS_DEFAULT),
							 (LPTSTR) &lpBuffer, 0, NULL);

		if ( !bRet )
		{
			TCHAR szErr[256];
			wsprintf(szErr, _T("Error %X"), hr );
			bstr =  szErr;
		}

		if ( lpBuffer )
		{
			bstr.Append( lpBuffer );
			LocalFree( lpBuffer );
		}

		return bRet;
	
}
