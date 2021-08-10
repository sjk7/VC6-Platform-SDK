/*======================================================================
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
PURPOSE.

Copyright 1998 - 2000. Microsoft Corporation.  All Right Reserved.

Module Name:
    RequestCert.cpp

Abstract:
    Requests certificate from Microsoft Certificate Server

History
    Created     June 1998
=======================================================================*/


// Include Headers
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <wincrypt.h>
#include <objbase.h>
#include <certsrv.h>
#include <xenroll.h>

#define BUFFERSIZE   512
void PrintUsage(void);

// Global variables
TCHAR szCertReq[BUFFERSIZE];
WCHAR szwTempBuffer[BUFFERSIZE];

// ProgID for ICEnroll control
OLECHAR *ICEnrollProgID = OLESTR("CEnroll.CEnroll.1");

extern "C"
void _cdecl _tmain(int argc, TCHAR *argv[])
{
   HRESULT hr;
   ICEnroll4 *CertEnroll = NULL;
   ICertRequest *CertRequest = NULL;
   ICertConfig *CertConfig = NULL;
   CLSID CLSID_CCertEnroll;
   BSTR pPKCS10 = NULL, pConfig = NULL, pPKCS7 = NULL;
   BSTR bstrTemp = NULL;
   BSTR bstrCertReq = NULL;
   LONG Disposition, RequestId;
   int n;

   __try {
      if (argc == 1)
      {
         PrintUsage();
         return;
      }

      // Append Common name to Certificate request string
      lstrcpy(szCertReq, TEXT("CN="));
      lstrcat(szCertReq, argv[1]);

      // Parse command line and append to Certificate Request String
      for (n = 2; n < argc; n++)
      {
         // Append common string identifier
         if (lstrcmp(argv[n], TEXT("/ou")) == 0) lstrcat(szCertReq, TEXT(",OU="));
         else if (lstrcmp(argv[n], TEXT("/o")) == 0) lstrcat(szCertReq, TEXT(",O="));
         else if (lstrcmp(argv[n], TEXT("/l")) == 0) lstrcat(szCertReq, TEXT(",L="));
         else if (lstrcmp(argv[n], TEXT("/s")) == 0) lstrcat(szCertReq, TEXT(",S="));
         else if (lstrcmp(argv[n], TEXT("/c")) == 0) lstrcat(szCertReq, TEXT(",C="));
         else if (lstrcmp(argv[n], TEXT("/e")) == 0) lstrcat(szCertReq, TEXT(",E="));
         else
         {
            PrintUsage();
            return;
         }

         // Append string
         if ((n + 1) < argc) lstrcat(szCertReq, argv[++n]);
         else
         {
            PrintUsage();
            return;
         }
      }

      // Convert Certificate Request String to BSTR
#ifdef UNICODE
      bstrCertReq = SysAllocString(szCertReq);
#else
      n = MultiByteToWideChar(CP_ACP, 0, szCertReq, -1, szwTempBuffer, BUFFERSIZE);
      if (n == 0)
      {
            _tprintf(TEXT("MultiByteToWideChar failed with %d\n"), GetLastError());
            __leave;
      }
      bstrCertReq = SysAllocString(szwTempBuffer);
#endif

      // Initialize COM library
      hr = CoInitialize(NULL);
      if (FAILED(hr))
      {
            _tprintf(TEXT("CoInitialize failed\n"));
            __leave;
      }

      // Get CLSID for ICEnroll
      hr = CLSIDFromProgID(ICEnrollProgID, &CLSID_CCertEnroll);
      if (FAILED(hr))
      {
         _tprintf(TEXT("CLSIDFromProgID failed\n"));
         __leave;
      }

      // get pointer to ICEnroll interface
      hr = CoCreateInstance(
               CLSID_CCertEnroll,
               NULL,
               CLSCTX_INPROC_SERVER,
               IID_ICEnroll4,
               (void **)&CertEnroll);
      if (FAILED(hr))
      {
         _tprintf(TEXT("CoCreateInstance with IID_ICEnroll4 failed\n"));
         __leave;
      }

      // get pointer to ICertRequest interface
      hr = CoCreateInstance(
                CLSID_CCertRequest,
                NULL,
                CLSCTX_INPROC_SERVER,
                IID_ICertRequest,
                (void **)&CertRequest);
      if (FAILED(hr))
      {
            _tprintf(TEXT("CoCreateInstance with IID_ICertRequest failed\n"));
            __leave;
      }

      // get pointer to ICertConfig interface
      hr = CoCreateInstance(
                CLSID_CCertConfig,
                NULL,
                CLSCTX_INPROC_SERVER,
                IID_ICertConfig,
                (void **)&CertConfig);
      if (FAILED(hr))
      {
         _tprintf(TEXT("CoCreateInstance with IID_ICertConfig failed\n"));
         __leave;
      }

      // Set KeySpec to be Exchange key
      // An exchange key makes this certificate a client certificate.
      // The server encrypts something with the certificate's
      // public key. The client can decrypt it with the private key
      // and verify itself
      hr = CertEnroll->put_KeySpec(AT_KEYEXCHANGE);
      if (FAILED(hr))
      {
         _tprintf(TEXT("CertEnroll->putKeySpec failed\n"));
         __leave;
      }

      // Create Certificate Request (PKCS10)
      // Second paramter is the OID that describes the purpose of the certificate.
      // 1.3.6.1.5.5.7.3.2 is the OID for Client Authentication
      // 1.3.6.1.5.5.7.3.3 is the OID for Code Signing
      // 1.3.6.1.5.5.7.3.1 is the OID for Server Authentication
      // 1.3.6.1.5.5.7.3.4 is the OID for email protection
      bstrTemp = SysAllocString(OLESTR("1.3.6.1.5.5.7.3.2"));
      hr = CertEnroll->createPKCS10(
                bstrCertReq,
                bstrTemp,
                &pPKCS10);
      if (FAILED(hr))
      {
         _tprintf(TEXT("CertEnroll->CreatePKCS10 failed\n"));
         __leave;
      }
      SysFreeString(bstrTemp);
      bstrTemp = NULL;

      // Get Default configuration
      hr = CertConfig->GetConfig(0, &pConfig);
      if (FAILED(hr))
      {
         _tprintf(TEXT("CertConfig->GetConfig failed\n"));
         __leave;
      }

      // Submit the Certificate Request
      // Second parameter specifies the attributes for the
      // certificate request. We don't set any attributes
      // in this sample.  Attributes may be a BSTR of type
      // "AttributeName1:AttributeValue1\nAttributeName2:AttributeValue2"
      // where each attribute is a name/value pair separated
      // by new line characters.
      bstrTemp = SysAllocString(OLESTR(""));
      hr = CertRequest->Submit(
                CR_IN_BASE64|CR_IN_PKCS10,
                pPKCS10,
                bstrTemp,
                pConfig,
                &Disposition);
      if (FAILED(hr))
      {
         _tprintf(TEXT("CertRequest->Submit failed\n"));
         __leave;
      }
      SysFreeString(bstrTemp);
      bstrTemp = NULL;

      _tprintf(TEXT("Certificate request submitted\n"));

      // if Certificate Server issued certificate Get Certificate
      if (Disposition == CR_DISP_ISSUED)
      {
         // Get the issued Certificate in a BASE64 PKCS#7 message
         hr = CertRequest->GetCertificate(CR_OUT_BASE64 | CR_OUT_CHAIN, &pPKCS7);
         if (FAILED(hr))
         {
            _tprintf(TEXT("CertRequest->GetCertificate failed\n"));
            __leave;
         }

         // save PKCS#7 message to file in binary format when accepting it
         // This is not necessary, but can be used later to look at the
         // certificate information.
         bstrTemp = SysAllocString(OLESTR("PKCS7BinaryFile"));
         hr = CertEnroll->put_SPCFileName(bstrTemp);
         if (FAILED(hr))
         {
            _tprintf(TEXT("CertEnroll->put_SPCFileName failed\n"));
            __leave;
         }
         SysFreeString(bstrTemp);
         bstrTemp = NULL;

         // accept the encoded certificate and place it in the store
         // The store will automatically be the "MY" store.
         // This behavior can be change by setting the
         // CertEnroll::MyStoreName property.  Use
         // CertEnroll::put_MyStoreName when using C++
         hr = CertEnroll->acceptPKCS7(pPKCS7);
         if (FAILED(hr))
         {
            _tprintf(TEXT("CertEnroll->acceptPKCS7 failed\n"));
            __leave;
         }

         _tprintf(TEXT("Certificate accepted and installed\n"));
      }
      else
      {
         // Certificate Server did not issue certificate
         _tprintf(TEXT("Certificate Server did not issue certificate\n"));
         _tprintf(TEXT("Dispostion returned:\n"));

         // Get Disposition message
         hr = CertRequest->GetDispositionMessage(&bstrTemp);
         if (FAILED(hr))
         {
            _tprintf(TEXT("CertRequest->GetDispositionMessage failed\n"));
            __leave;
         }

         wcscpy(szwTempBuffer, bstrTemp);
         wprintf(szwTempBuffer);
         wprintf(L"\n");
         SysFreeString(bstrTemp);
         bstrTemp = NULL;
      }

      // Get Request Id
      hr = CertRequest->GetRequestId(&RequestId);
      if (FAILED(hr))
      {
         _tprintf(TEXT("CertRequest->GetRequestId failed\n"));
         __leave;
      }

      // Display request Id
      _tprintf(TEXT("Request Id = %d\n"), RequestId);

   }
   __finally {
      // Clean up
      if (CertEnroll != NULL) CertEnroll->Release();
      if (CertRequest != NULL) CertRequest->Release();
      if (CertConfig != NULL) CertConfig->Release();
      if (bstrCertReq != NULL) SysFreeString(bstrCertReq);
      if (pPKCS10 != NULL) SysFreeString(pPKCS10);
      if (pPKCS7 != NULL) SysFreeString(pPKCS7);
      if (pConfig != NULL) SysFreeString(pConfig);
      if (bstrTemp != NULL) SysFreeString(bstrTemp);
      CoUninitialize();
   }
}

/*---------------------------------------------------------------
 Print Program's Usage
----------------------------------------------------------------*/
void PrintUsage(void)
{
   _tprintf(TEXT("Usage : RequestCert <common name> [options]\n"));
   _tprintf(TEXT("options:\n\t/ou <organizational unit>\n"));
   _tprintf(TEXT("\t/o <organization>\n"));
   _tprintf(TEXT("\t/l <locale>\n"));
   _tprintf(TEXT("\t/s <state>\n"));
   _tprintf(TEXT("\t/c <country>\n"));
   _tprintf(TEXT("\t/e <email address>\n"));
}