/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.

 Copyright (C) 1998 - 2000.  Microsoft Corporation.  All rights reserved.

 Module:      PropCert.cpp

 Abstract:    Main program of PropCert sample for Smart Card SDK sample. See
              ReadMe.txt for more detailed information about this sample.

 Environment: Win32 console, C++ w/SEH, UNICODE ready.

------------------------------------------------------------------------------*/

#define _WIN32_WINNT 0x0400

///////////////
//
// INCLUDE
//

#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winscard.h>
#include <wincrypt.h>


///////////////
//
// Macros
//

#define MALLOC(size)  ((LPBYTE) LocalAlloc(LPTR, size))
#define FREE(buffer)  (LocalFree((LPBYTE) buffer))


///////////////
//
// Prototypes
//

LONG SCardPropCert (IN SCARDCONTEXT hContext,
                    IN LPCTSTR mszReaderNames,
                    IN LPCTSTR szStoreName);

LONG CryptPropCert (IN HCRYPTPROV hCryptProv,
                    IN LPCTSTR szCSPName,
                    IN LPCTSTR szStoreName);

LONG GetCert (IN HCRYPTPROV hCryptProv,
              IN DWORD dwKeySpec,
              OUT LPBYTE * lplpbCert,
              OUT DWORD * lpdwCertLength);

LONG AddCert (IN HCRYPTPROV hCryptProv,
              IN LPBYTE lpbCert,
              IN DWORD dwCertLength,
              IN DWORD dwKeySpec,
              IN LPCWSTR szCertFriendlyName,
              IN LPCWSTR zContainerName,
              IN LPCWSTR szCSPName,
              IN LPCWSTR szStoreName);

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 Function : _tmain

 Synopsis : Entry point of PropCert.

 Parameter: Standard ANSI C command line parameters.

 Return   : SCARD_S_SUCCESS or error code.

 Remarks  :

------------------------------------------------------------------------------*/

int __cdecl _tmain (int argc, _TCHAR  * argv[])
{
   LONG lResult;
   DWORD dwNumReaders = 0;
   SCARDCONTEXT hContext = NULL;
   LPTSTR mszReaderNames = NULL;

   __try
   {
      //
      // Establish context with the resource manager.
      //
      lResult = SCardEstablishContext(SCARD_SCOPE_USER,
                                      NULL,
                                      NULL,
                                      &hContext);
      if (lResult != SCARD_S_SUCCESS)
      {
         __leave;
      }

      //
      // Get the list of reader(s) associated with the specified group(s).
      // Note: The buffer is automatically allocated and must be freed
      //       by SCardFreeMemory().
      //
      DWORD dwAutoAllocate = SCARD_AUTOALLOCATE;

      lResult = SCardListReaders(hContext,
                                 SCARD_DEFAULT_READERS,
                                 (LPTSTR) &mszReaderNames,
                                 &dwAutoAllocate);
      if (lResult != SCARD_S_SUCCESS)
      {
         __leave;
      }

      //
      // Propagate all digital certificate(s) found in all reader(s) to the
      // local "My" store.
      //
      lResult = SCardPropCert(hContext, mszReaderNames, _T("My"));
   }

   __finally
   {
      LONG lReturn;

      //
      // Don't forget to free resources, if allocated.
      //
      if (mszReaderNames != NULL)
      {
         lReturn = SCardFreeMemory(hContext, (LPVOID) mszReaderNames);

         //
         // If successful so far, then capture the return code
         // from SCFree(); otherwise, don't bother.
         //
         if (lResult == SCARD_S_SUCCESS)
         {
            lResult = lReturn;
         }
      }

      if (hContext != NULL)
      {
         lReturn = SCardReleaseContext(hContext);

         //
         // If successful so far, then capture the SCardReleaseContext()
         // return code; otherwise, don't bother.
         //
         if (lResult == SCARD_S_SUCCESS)
         {
            lResult = lReturn;
         }
      }
   }

   //
   // Inform user if an error had occurred.
   //
   if (lResult != SCARD_S_SUCCESS)
   {
      _tprintf(_T("\nError [0x%x]: Program terminated abnormally.\n"), lResult);
   }

   return lResult;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 Function : SCardPropCert

 Synopsis : Propagate the digital certificate from any smart card found in the
            specified reader(s) to the specified local store.

 Parameter: - IN SCARDCONTEXT hContext

              Resource manager context returned by SCardEstablishContext(), or
              NULL if the query is not directed towards a specific context.

            - IN LPCTSTR mszReaderNames

              Pointer to multi-string structure of reader names for which the
              digital certificate in the smart card, if found,  will be
              propagated to the specified local store.

            - IN szStoreName

              Ponter to the local store name (ie "My") where the certificate
              will be stored.

 Return   : SCARD_S_SUCCESS or error code

 Remarks  :

------------------------------------------------------------------------------*/

LONG SCardPropCert (IN SCARDCONTEXT hContext,
                    IN LPCTSTR mszReaderNames,
                    IN LPCTSTR szStoreName)
{
   LONG lResult;
   LPSCARD_READERSTATE lpReaderStates = NULL;

   //
   // Make sure pointer parameters are not NULL.
   //
   if (mszReaderNames == NULL || szStoreName == NULL)
   {
      return SCARD_E_INVALID_PARAMETER;
   }

   __try
   {
      DWORD dwNumReaders;
      LPCTSTR szReaderName;

      //
      // Count number of readers.
      //
      for (dwNumReaders = 0, szReaderName = mszReaderNames;
           *szReaderName != _T('\0');
           dwNumReaders++)
      {
         szReaderName += lstrlen(szReaderName) + 1;
      }

      //
      // Allocate memory for SCARD_READERSTATE array.
      //
      lpReaderStates = (LPSCARD_READERSTATE)
                       MALLOC(dwNumReaders * sizeof(SCARD_READERSTATE));
      if (lpReaderStates == NULL)
      {
         lResult = SCARD_E_NO_MEMORY;
         __leave;
      }

      //
      // Prepare state array.
      //
      ZeroMemory((LPVOID) lpReaderStates,
                 dwNumReaders * sizeof(SCARD_READERSTATE));

      DWORD i;
      for (i = 0, szReaderName = mszReaderNames;
           i < dwNumReaders;
           i++)
      {
         lpReaderStates[i].szReader = (LPCTSTR) szReaderName;
         lpReaderStates[i].dwCurrentState = SCARD_STATE_UNAWARE;

         szReaderName += lstrlen(szReaderName) + 1;
      }

      //
      // Initialize card status.
      //
      lResult = SCardGetStatusChange(hContext,
                                     INFINITE,
                                     lpReaderStates,
                                     dwNumReaders);
      if (lResult != SCARD_S_SUCCESS)
      {
         __leave;
      }

      //
      // For each card found, find the proper CSP and propagate the
      // certificate(s) to the specified local store.
      //
      for (i = 0; i < dwNumReaders && lResult == SCARD_S_SUCCESS; i++)
      {
         DWORD dwAutoAllocate;
         LPTSTR szCardName = NULL;
         LPTSTR szCSPName = NULL;
         LPTSTR szContainerName = NULL;
         HCRYPTPROV hCryptProv = NULL;

         __try
         {
            //
            // Card in this reader?
            //
            if (!(lpReaderStates[i].dwEventState & SCARD_STATE_PRESENT))
            {
               //
               // No card in this reader.
               //
               continue;
            }

            //
            // Get card name.
            //
            dwAutoAllocate = SCARD_AUTOALLOCATE;
            lResult = SCardListCards(hContext,
                                     lpReaderStates[i].rgbAtr,
                                     NULL,
                                     0,
                                     (LPTSTR) &szCardName,
                                     &dwAutoAllocate);
            if (lResult != SCARD_S_SUCCESS)
            {
               __leave;
            }

            //
            // Get card's CSP name.
            //

            //
            // Note: SCardGetCardTypeProviderName is not available
            //       in Smart Card Base Component v1.0. Please see
            //       ReadMe.txt for more information.
            //
            dwAutoAllocate = SCARD_AUTOALLOCATE;
            lResult = SCardGetCardTypeProviderName(hContext,
                                                   szCardName,
                                                   SCARD_PROVIDER_CSP,
                                                   (LPTSTR) &szCSPName,
                                                   &dwAutoAllocate);
            if (lResult != SCARD_S_SUCCESS)
            {
               __leave;
            }

            //
            // Prepare fully qualified container name.
            //
            szContainerName = (LPTSTR) MALLOC((sizeof(_T("\\\\.\\")) +
                              lstrlen(lpReaderStates[i].szReader) +
                              sizeof(_T("\\\0"))) * sizeof(TCHAR));

            if (szContainerName == NULL)
            {
               lResult = SCARD_E_NO_MEMORY;
               __leave;
            }

            wsprintf(szContainerName, _T("\\\\.\\%s\\"),
                     lpReaderStates[i].szReader);

            //
            // Obtain the crypto context.
                        //
                        // CRYPT_SILENT forces the CSP to raise no UI. The fully qualified
                        // container name indicates which reader to connect to, so the
                        // user should not be prompted to insert or select a card.
            //
            if (!CryptAcquireContext(&hCryptProv,
                                     szContainerName,
                                     szCSPName,
                                     PROV_RSA_FULL,
                                     CRYPT_SILENT))
            {
               lResult = GetLastError();
               __leave;
            }

            //
            // Propagate the cert.
            //
            lResult = CryptPropCert(hCryptProv,
                                    szCSPName,
                                    szStoreName);
         }

         __finally
         {
            LONG lReturn;

            //
            // Don't forget to free resources, if allocated.
            //
            if (hCryptProv != NULL)
            {
               if (!CryptReleaseContext(hCryptProv, 0))
               {
                  if (lResult == SCARD_S_SUCCESS)
                  {
                     lResult = GetLastError();
                  }
               }
            }

            if (szContainerName != NULL)
            {
               FREE((LPVOID) szContainerName);
            }

            if (szCSPName != NULL)
            {
               lReturn = SCardFreeMemory(hContext, (LPVOID) szCSPName);
               if (lResult == SCARD_S_SUCCESS)
               {
                  lResult = lReturn;
               }
            }

            if (szCardName != NULL)
            {
               lReturn = SCardFreeMemory(hContext, (LPVOID) szCardName);
               if (lResult == SCARD_S_SUCCESS)
               {
                  lResult = lReturn;
               }
            }
         }
      }
   }

   __finally
   {
      //
      // Don't forget to free resources, if allocated.
      //
      if (lpReaderStates != NULL)
      {
         FREE((LPVOID) lpReaderStates);
      }
   }

   return lResult;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 Function : CryptPropCert

 Synopsis : Propagate the digital certificate associated with the specified
            crypto context to the specified local store.

 Parameter: - IN HCRYPTPROV hCryptProv

              Crypto context returned by CryptAcquireContext().

            - IN LPCTSTR szCSPName

              Pointer to Crypto Service Provider name string.

            - IN szStoreName

              Ponter to the local store name (ie "My") where the certificate
              will be stored.

 Return   : SCARD_S_SUCCESS or error code

 Remarks  :

------------------------------------------------------------------------------*/

LONG CryptPropCert (IN HCRYPTPROV hCryptProv,
                    IN LPCTSTR szCSPName,
                    IN LPCTSTR szStoreName)
{
   LONG lResult;
   LPCTSTR szContainerName = NULL;

   //
   // Make sure pointer parameters are not NULL.
   //
   if (szCSPName == NULL || szStoreName == NULL)
   {
      return SCARD_E_INVALID_PARAMETER;
   }

   __try
   {
      //
      // Query length of key container name.
      //
      DWORD cbContainerName = 0;

      if (!CryptGetProvParam(hCryptProv,
                             PP_CONTAINER,
                             NULL,  // NULL to query container name length
                             &cbContainerName,
                             0))
      {
         lResult = GetLastError();
         __leave;
      }

      //
      // Allocate memory for key container name.
      //
      szContainerName = (LPCTSTR) MALLOC(cbContainerName);

      //
      // Now get the key container name.
      //
      if (!CryptGetProvParam(hCryptProv,
                             PP_CONTAINER,
                             (PBYTE) szContainerName,
                             &cbContainerName,
                             0))
      {
         lResult = GetLastError();
         __leave;
      }

      //
      // For each key pair found in the smart card, store the corresponding
      // digital certificate to the specified local store.
      //
      const DWORD rgdwKeys[] = {AT_KEYEXCHANGE, AT_SIGNATURE};
      const DWORD cdwKeys = sizeof(rgdwKeys) / sizeof(rgdwKeys[0]);

      for (DWORD i = 0; i < cdwKeys; i++)
      {
         DWORD dwCertLength = 0;
         LPBYTE lpbCert = NULL;

         LPWSTR wszCertFriendlyName = NULL;
         LPWSTR wszContainerName = NULL;
         LPWSTR wszCSPName = NULL;
         LPWSTR wszStoreName = NULL;

         __try
         {
            //
            // Get the certificate data.
            //
            lResult = GetCert(hCryptProv,
                              rgdwKeys[i],
                              &lpbCert,
                              &dwCertLength);
            if (lResult != SCARD_S_SUCCESS)
            {
               if (lResult == NTE_NO_KEY)
               {
                  //
                  // We are OK if there is no key of such type.
                  // It means there is nothing to do.
                  //
                  lResult = SCARD_S_SUCCESS;
               }

               __leave;
            }

            //
            // Allocate memory for UNICODE strings.
            //
            TCHAR szCertFriendlyName[] = "";
            DWORD cchCertFriendlyName = (lstrlen(szCertFriendlyName) + 1)
                                        * sizeof(WCHAR);
            DWORD cchContainerName = (lstrlen(szContainerName) + 1)
                                     * sizeof(WCHAR);
            DWORD cchCSPName = (lstrlen(szCSPName) + 1) * sizeof(WCHAR);
            DWORD cchStoreName = (lstrlen(szStoreName) + 1) * sizeof(WCHAR);

            wszCertFriendlyName = (LPWSTR) MALLOC(cchCertFriendlyName);
            wszContainerName = (LPWSTR) MALLOC(cchContainerName);
            wszCSPName = (LPWSTR) MALLOC(cchCSPName);
            wszStoreName = (LPWSTR) MALLOC(cchStoreName);

            if (wszCertFriendlyName == NULL ||
                wszContainerName == NULL ||
                wszCSPName == NULL ||
                wszStoreName == NULL)
            {
               lResult = SCARD_E_NO_MEMORY;
               __leave;
            }

            //
            // Setup UNICODE strings.
            //
#ifdef _UNICODE
            lstrcpy(wszCertFriendlyName, szCertFriendlyName);
            lstrcpy(wszContainerName, szContainerName);
            lstrcpy(wszCSPName, szCSPName);
            lstrcpy(wszStoreName, szStoreName);
#else
            mbstowcs(wszCertFriendlyName, szCertFriendlyName,
                     cchCertFriendlyName);
            mbstowcs(wszContainerName, szContainerName, cchContainerName);
            mbstowcs(wszCSPName, szCSPName, cchCSPName);
            mbstowcs(wszStoreName, szStoreName, cchStoreName);
#endif
            //
            // Add the certificate to the specified local store.
            //
            lResult = AddCert(hCryptProv,
                              lpbCert,
                              dwCertLength,
                              rgdwKeys[i],
                              wszCertFriendlyName,
                              wszContainerName,
                              wszCSPName,
                              wszStoreName);
            if (lResult != SCARD_S_SUCCESS)
            {
               __leave;
            }
            else
            {
				_tprintf(
					_T("\nPropagated cert from %s to \"%s\" certificate store.\n"),
					szCSPName,
					szStoreName);
			}
         }

         __finally
         {
            //
            // Don't forget to free resources, if allocated.
            //
            if (lpbCert != NULL)
            {
               FREE(lpbCert);
            }

            if (wszCertFriendlyName != NULL)
            {
               FREE(wszCertFriendlyName);
            }

            if (wszContainerName != NULL)
            {
               FREE(wszContainerName);
            }

            if (wszCSPName != NULL)
            {
               FREE(wszCSPName);
            }

            if (wszStoreName != NULL)
            {
               FREE(wszStoreName);
            }

            if (lResult != SCARD_S_SUCCESS)
            {
               __leave;
            }
         }
      }
   }

   __finally
   {
      //
      // Don't forget to free resources, if allocated.
      //
      if (szContainerName != NULL)
      {
         FREE(szContainerName);
      }
   }

   return lResult;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 Function : GetCert

 Synopsis : Get the cert from the specified CSP for the specified key type.

 Parameter: - IN HCRYPTPROV hCryptProv

              Crypto context returned by CryptAcquireContext().

            - IN DWORD dwKeySpec

              AT_KEYEXCHANGZE or AT_SIGNATURE.

            - OUT LPBYTE * lplpbCert

              Ponter to pointer to cert data. Upon success, the buffer is
              automatically allocated and must be later freed by LocalFree().

            - OUT DWORD * lpdwCertLength

              Pointer to cert data length. Upon success, receive the length
              of the cert data.

 Return   : SCARD_S_SUCCESS or error code

 Remarks  :

------------------------------------------------------------------------------*/

LONG GetCert (IN HCRYPTPROV hCryptProv,
              IN DWORD dwKeySpec,
              OUT LPBYTE * lplpbCert,
              OUT DWORD * lpdwCertLength)
{
   LONG lResult = SCARD_S_SUCCESS;
   HCRYPTKEY hCryptKey = NULL;
   LPBYTE lpbCert = NULL;
   DWORD dwCertLength = 0;

   //
   // Make sure pointer parameters are not NULL.
   //
   if (lplpbCert == NULL || lpdwCertLength == NULL)
   {
      return SCARD_E_INVALID_PARAMETER;
   }

   __try
   {
      //
      // Get key handle.
      //
      if (!CryptGetUserKey(hCryptProv, dwKeySpec, &hCryptKey))
      {
         lResult = GetLastError();
         __leave;
      }

      //
      // Query certificate data length.
      //
      if (!CryptGetKeyParam(hCryptKey,
                            KP_CERTIFICATE,
                            NULL,  // NULL to query certificate data length
                            &dwCertLength,
                            0))
      {
         //
         // We expect ERROR_MORE_DATA. If that's not the case, then
         // something is not right.
         //
         lResult = GetLastError();
         if (lResult == ERROR_MORE_DATA)
         {
            lResult = SCARD_S_SUCCESS;
         }
         else
         {
            __leave;
         }
      }

      //
      // Allocate memory for certificate data.
      //
      lpbCert = (LPBYTE) MALLOC(dwCertLength);
      if (lpbCert == NULL)
      {
         lResult = SCARD_E_NO_MEMORY;
         __leave;
      }

      //
      // Now read the certificate data.
      //
      if (!CryptGetKeyParam(hCryptKey,
                            KP_CERTIFICATE,
                            lpbCert,
                            &dwCertLength,
                            0))
      {
         lResult = GetLastError();
         __leave;
      }
   }

   __finally
   {
      //
      // Don't forget to free resources, if allocated.
      //
      if (lResult == SCARD_S_SUCCESS)
      {
         *lplpbCert = lpbCert;
         *lpdwCertLength = dwCertLength;
      }
      else if (lpbCert != NULL)
      {
         FREE(lpbCert);
      }

      if (hCryptKey != NULL)
      {
         if (!CryptDestroyKey(hCryptKey))
         {
            if (lResult == SCARD_S_SUCCESS)
            {
               lResult = GetLastError();
            }
         }
      }
   }

   return lResult;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 Function : AddCert

 Synopsis : Add the specified certificate to the specified local store.

 Parameter: - IN HCRYPTPROV hCryptProv

              Crypto context returned by CryptAcquireContext().

            - IN LPBYTE * lpbCert

              Pointer to cert data to be added.

            - IN DWORD dwCertLength

              Length of cert data.

            - IN DWORD dwKeySpec

              AT_KEYEXCHANGZE or AT_SIGNATURE.

 Return   : SCARD_S_SUCCESS or error code

 Remarks  :

------------------------------------------------------------------------------*/

LONG AddCert (IN HCRYPTPROV hCryptProv,
              IN LPBYTE lpbCert,
              IN DWORD dwCertLength,
              IN DWORD dwKeySpec,
              IN LPCWSTR wszCertFriendlyName,
              IN LPCWSTR wszContainerName,
              IN LPCWSTR wszCSPName,
              IN LPCWSTR wszStoreName)
{
   LONG lResult = SCARD_S_SUCCESS;
   HCERTSTORE hCertStore = NULL;
   PCCERT_CONTEXT pCertContext = NULL;

   //
   // Make sure pointer parameters are not NULL.
   //
   if (lpbCert == NULL ||
       wszContainerName == NULL ||
       wszCSPName == NULL ||
       wszStoreName == NULL)
   {
      return SCARD_E_INVALID_PARAMETER;
   }

   __try
   {
      //
      // Open the user's specified store for writing.
      //
      hCertStore = CertOpenStore(CERT_STORE_PROV_SYSTEM_W,
                                 0,
                                 hCryptProv,
                                 CERT_STORE_NO_CRYPT_RELEASE_FLAG |
                                 CERT_SYSTEM_STORE_CURRENT_USER,
                                 wszStoreName);
      if (NULL == hCertStore)
      {
         lResult = GetLastError();
         __leave;
      }

      //
      // Build certificate context for this certificate.
      //
      pCertContext = CertCreateCertificateContext(X509_ASN_ENCODING,
                                                  lpbCert,
                                                  dwCertLength);
      if (pCertContext == NULL)
      {
         lResult = GetLastError();
         __leave;
      }

      //
      // Add the friendly name, if provided.
      //
      if (wszCertFriendlyName != NULL)
      {
         CRYPT_DATA_BLOB DataBlob;

         ZeroMemory((PVOID)&DataBlob, sizeof(CRYPT_DATA_BLOB));

         DataBlob.cbData = (wcslen(wszCertFriendlyName) + 1) * sizeof(WCHAR);
         DataBlob.pbData = (LPBYTE) wszCertFriendlyName;

         if (!CertSetCertificateContextProperty(pCertContext,
                                                CERT_FRIENDLY_NAME_PROP_ID,
                                                0,
                                                (const void *) &DataBlob))
         {
            lResult = GetLastError();
            __leave;
         }
      }

      //
      // Add the CSP & key container info. This is used by CAPI to load the
      // CSP and find the keyset when the user indicates this certificate.
      //
      CRYPT_KEY_PROV_INFO KeyProvInfo;

      ZeroMemory((PVOID)&KeyProvInfo, sizeof(CRYPT_KEY_PROV_INFO));

      KeyProvInfo.pwszContainerName = (LPWSTR) wszContainerName;
      KeyProvInfo.pwszProvName      = (LPWSTR) wszCSPName;
      KeyProvInfo.dwProvType        = PROV_RSA_FULL;
      KeyProvInfo.dwFlags           = 0;
      KeyProvInfo.dwKeySpec         = dwKeySpec;

      if (!CertSetCertificateContextProperty(pCertContext,
                                             CERT_KEY_PROV_INFO_PROP_ID,
                                             0,
                                             (const void *) &KeyProvInfo))
      {
         lResult = GetLastError();
         __leave;
      }

      //
      // Put the cert in the store!
      //
      if (!CertAddCertificateContextToStore(hCertStore,
                                            pCertContext,
                                            CERT_STORE_ADD_REPLACE_EXISTING,
                                            // or CERT_STORE_ADD_NEW
                                            NULL))
      {
         lResult = GetLastError();
         __leave;
      }
   }

   __finally
   {
      //
      // Don't forget to free resources, if allocated.
      //
      if (pCertContext != NULL)
      {
         CertFreeCertificateContext(pCertContext);
      }

      if (hCertStore != NULL)
      {
         CertCloseStore(hCertStore, CERT_CLOSE_STORE_FORCE_FLAG);
      }
   }

   return lResult;
}

