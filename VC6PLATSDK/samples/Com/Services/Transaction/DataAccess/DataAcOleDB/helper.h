//==============================================================================
// Filename: Helper.h
//
// Description: HRESULT Helper Macros
//
// This file is part of the Microsoft COM+ Samples
//
// Copyright (C) 1995 - 2000 Microsoft Corporation. All rights reserved
//
// This source code is intended only as a supplement to Microsoft
// Development Tools and/or on-line documentation.  See these other
// materials for detailed information reagrding Microsoft code samples.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
//==============================================================================


#define __LONGSTRING(string) L##string
#define LONGSTRING(string) __LONGSTRING(string)


#define CHECK_HR(hr)																			\
{																									\
   if(FAILED(hr))																				\
      goto error;																				\
}



#define XCHECK_HR(hr)																		\
{																									\
   if(FAILED(myHandleResult(hr, LONGSTRING(__FILE__), __LINE__)))	\
      goto error;																				\
}



HRESULT myHandleResult(HRESULT hrReturned, LPCWSTR pwszFile, ULONG ulLine);
HRESULT myDisplayErrorRecord(HRESULT hrReturned, ULONG iRecord, IErrorRecords* pIErrorRecords, LPCWSTR pwszFile, ULONG ulLine);
HRESULT myDisplayErrorInfo(HRESULT hrReturned, IErrorInfo* pIErrorInfo, LPCWSTR pwszFile, ULONG ulLine);
HRESULT myGetSqlErrorInfo(ULONG iRecord, IErrorRecords* pIErrorRecords, BSTR* pBstr, LONG* plNativeError);


////////////////////////////////////////////////////////////////////////
// myHandleResult
//
// This function is called as part of the XCHECK_HR macro; it takes an
// HRESULT, which is returned by the method called in the XCHECK_HR
// macro, and the file and line number where the method call was made.
// If the method call failed, this function attempts to get and display
// the extended error information for the call from the IErrorInfo,
// IErrorRecords, and ISQLErrorInfo interfaces.
//
////////////////////////////////////////////////////////////////////////
HRESULT myHandleResult
   (
   HRESULT           hrReturned,
   LPCWSTR           pwszFile,
   ULONG             ulLine
   )
{
   HRESULT           hr;
   IErrorInfo *      pIErrorInfo      = NULL;
   IErrorRecords *   pIErrorRecords   = NULL;
   ULONG             cRecords;
   ULONG             iErr;

   // If the method called as part of the XCHECK_HR macro failed,
   // we will attempt to get extended error information for the call
   if( FAILED(hrReturned) )
   {
      // Obtain the current error object, if any, by using the
      // Automation GetErrorInfo function, which will give
      // us back an IErrorInfo interface pointer if successful
      hr = GetErrorInfo(0, &pIErrorInfo);

      // We've got the IErrorInfo interface pointer on the error object
      if( SUCCEEDED(hr) && pIErrorInfo )
      {
         // OLE DB extends the Automation error model by allowing
         // error objects to support the IErrorRecords interface. This
         // interface can expose information on multiple errors.
         hr = pIErrorInfo->QueryInterface(IID_IErrorRecords, 
                  (void**)&pIErrorRecords);
         if( SUCCEEDED(hr) )
         {
            // Get the count of error records from the object
            CHECK_HR(hr = pIErrorRecords->GetRecordCount(&cRecords));
            
            // Loop through the set of error records, and
            // display the error information for each one
            for( iErr = 0; iErr < cRecords; iErr++ )
            {
               myDisplayErrorRecord(hrReturned, iErr, pIErrorRecords,
                  pwszFile, ulLine);
            }
         }
         // The object didn't support IErrorRecords; display
         // the error information for this single error
         else
         {
            myDisplayErrorInfo(hrReturned, pIErrorInfo, pwszFile, ulLine);
         }
      }
      // There was no error object, so just display the HRESULT
      // to the user
      else
      {
         wprintf(L"\nNo Error Info posted; HResult: 0x%08x\n"
            L"File: %s, Line: %d\n", hrReturned, pwszFile, ulLine);
      }
   }

error:
   if( pIErrorInfo )
      pIErrorInfo->Release();
   if( pIErrorRecords )
      pIErrorRecords->Release();
   return hrReturned;
}


////////////////////////////////////////////////////////////////////////
// myDisplayErrorRecord
//
// This function displays the error information for a single error
// record, including information from ISQLErrorInfo, if supported
//
////////////////////////////////////////////////////////////////////////
HRESULT myDisplayErrorRecord
   (
   HRESULT           hrReturned, 
   ULONG             iRecord, 
   IErrorRecords *   pIErrorRecords, 
   LPCWSTR           pwszFile, 
   ULONG             ulLine
   )
{
   HRESULT           hr;
   IErrorInfo *      pIErrorInfo       = NULL;
   BSTR              bstrDescription   = NULL;
   BSTR              bstrSource        = NULL;
   BSTR              bstrSQLInfo       = NULL;

   static LCID       lcid              = GetUserDefaultLCID();

   LONG              lNativeError      = 0;
   ERRORINFO         ErrorInfo;
   WCHAR			 szBuff[1024];

   // Get the IErrorInfo interface pointer for this error record
   CHECK_HR(hr = pIErrorRecords->GetErrorInfo(iRecord, lcid, &pIErrorInfo));
   
   // Get the description of this error
   CHECK_HR(hr = pIErrorInfo->GetDescription(&bstrDescription));
      
   // Get the source of this error
   CHECK_HR(hr = pIErrorInfo->GetSource(&bstrSource));

   // Get the basic error information for this record
   CHECK_HR(hr = pIErrorRecords->GetBasicErrorInfo(iRecord, &ErrorInfo));

   // If the error object supports ISQLErrorInfo, get this information
   myGetSqlErrorInfo(iRecord, pIErrorRecords, &bstrSQLInfo, &lNativeError);

   // Display the error information to the user
   if( bstrSQLInfo )
   {
      _snwprintf(szBuff, 1024, L"\nErrorRecord:  HResult: 0x%08x\nDescription: %s\n"
         L"SQLErrorInfo: %s\nSource: %s\nFile: %s, Line: %d\n", 
         ErrorInfo.hrError, 
         bstrDescription, 
         bstrSQLInfo, 
         bstrSource, 
         pwszFile, 
         ulLine);
   }
   else
   {
      _snwprintf(szBuff, 1024, L"\nErrorRecord:  HResult: 0x%08x\nDescription: %s\n"
         L"Source: %s\nFile: %s, Line: %d\n", 
         ErrorInfo.hrError, 
         bstrDescription, 
         bstrSource, 
         pwszFile, 
         ulLine);
   }
   // Display the formatter buffer
  wsprintf(szBuff);

error:
   if( pIErrorInfo )
      pIErrorInfo->Release();
   SysFreeString(bstrDescription);
   SysFreeString(bstrSource);
   SysFreeString(bstrSQLInfo);
   return hr;
}


////////////////////////////////////////////////////////////////////////
// myDisplayErrorInfo
//
// This function displays basic error information for an error object
// that doesn't support the IErrorRecords interface
//
////////////////////////////////////////////////////////////////////////
HRESULT myDisplayErrorInfo
   (
   HRESULT        hrReturned, 
   IErrorInfo *   pIErrorInfo, 
   LPCWSTR        pwszFile, 
   ULONG          ulLine
   )
{
   HRESULT        hr;
   BSTR           bstrDescription   = NULL;
   BSTR           bstrSource        = NULL;

   // Get the description of the error
   CHECK_HR(hr = pIErrorInfo->GetDescription(&bstrDescription));
      
   // Get the source of the error -- this will be the window title
   CHECK_HR(hr = pIErrorInfo->GetSource(&bstrSource));

   // Display this error information
   wprintf(L"\nErrorInfo:  HResult: 0x%08x, Description: %s\nSource: %s\n"
            L"File: %s, Line: %d\n", 
            hrReturned, 
            bstrDescription, 
            bstrSource, 
            pwszFile, 
            ulLine);

error:
   SysFreeString(bstrDescription);
   SysFreeString(bstrSource);
   return hr;
}


////////////////////////////////////////////////////////////////////////
// myGetSqlErrorInfo
//
// If the error object supports ISQLErrorInfo, get the SQL error
// string and native error code for this error
//
////////////////////////////////////////////////////////////////////////
HRESULT myGetSqlErrorInfo
   (
   ULONG             iRecord, 
   IErrorRecords *   pIErrorRecords, 
   BSTR *            pBstr, 
   LONG *            plNativeError
   )
{
   HRESULT           hr;
   ISQLErrorInfo *   pISQLErrorInfo   = NULL;
   LONG              lNativeError     = 0;

   // Attempt to get the ISQLErrorInfo interface for this error
   // record through GetCustomErrorObject. Note that ISQLErrorInfo
   // is not mandatory, so failure is acceptable here.
   CHECK_HR(hr = pIErrorRecords->GetCustomErrorObject(
            iRecord,                               // iRecord
            IID_ISQLErrorInfo,                     // riid
            (IUnknown**)&pISQLErrorInfo            // ppISQLErrorInfo
            ));

   // If we obtained the ISQLErrorInfo interface, get the SQL
   // error string and native error code for this error
   if( pISQLErrorInfo )
      hr = pISQLErrorInfo->GetSQLInfo(pBstr, &lNativeError);

error:
   if( plNativeError )
      *plNativeError = lNativeError;
   if( pISQLErrorInfo )
      pISQLErrorInfo->Release();
   return hr;
}


