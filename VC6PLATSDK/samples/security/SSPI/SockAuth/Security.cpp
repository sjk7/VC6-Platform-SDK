/*++

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

    security.c

Abstract:

    Handles communication with the SSP package.

Revision History:

--*/

#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <stdlib.h>
#define SECURITY_WIN32
#include "sspi.h"
#include "security.h"
#include "collect.h"

//static DWORD      g_cbMaxToken;
static TCHAR      g_lpPackageName[1024];
static BOOL       g_fVerbose;


// structure storing the state of the authentication sequence
//
typedef struct _AUTH_SEQ {
    BOOL _fNewConversation;
    CredHandle _hcred;
    BOOL _fHaveCredHandle;
    BOOL _fHaveCtxtHandle;
    struct _SecHandle  _hctxt;
    ULONG cbMaxSignature;
    ULONG cbSecurityTrailer;
} AUTH_SEQ, *PAUTH_SEQ;

#define SEC_SUCCESS(Status) ((Status) >= 0)

#define NT_DLL_NAME           "secur32.dll"

// Target name for the security package
//
#define TOKEN_SOURCE_NAME     "AuthSamp"


BOOL InitPackage (TCHAR *lpPackageName, BOOL fVerbose)
/*++

 Routine Description:

    Finds, loads and initializes the security package

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
   SECURITY_STATUS ss;
   PSecPkgInfo pkgInfo;

   // Query for the package we're interested in
   //
   ss = QuerySecurityPackageInfo (lpPackageName, &pkgInfo);

   if (!SEC_SUCCESS(ss)) {
      fprintf (stderr, "Couldn't query package info for %s, error 0x%08x\n",
               lpPackageName, ss);
      return(FALSE);
   }

   lstrcpy (g_lpPackageName, lpPackageName);

   FreeContextBuffer (pkgInfo);

   g_fVerbose = fVerbose;

   printf ("Using package: %s\n", g_lpPackageName);

   return TRUE;
}

BOOL TermPackage ()
{
   
   return(TRUE);
}

BOOL GenClientContext (
         DWORD dwKey,
         BYTE *pIn,
         DWORD cbIn,
         BYTE **pOut,
         DWORD *pcbOut,
         BOOL *pfDone,
         ULONG *pAttribs,
         CHAR *pszTarget)
/*++

 Routine Description:

    Optionally takes an input buffer coming from the server and returns
   a buffer of information to send back to the server.  Also returns
   an indication of whether or not the context is complete.

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
   SECURITY_STATUS   ss;
   TimeStamp         Lifetime;
   SecBufferDesc     OutBuffDesc;
   SecBuffer         OutSecBuff;
   SecBufferDesc     InBuffDesc;
   SecBuffer         InSecBuff;
   ULONG             ContextAttributes;
   PAUTH_SEQ         pAS;
   SecPkgContext_Sizes SecPkgContextSizes;
   SecPkgContext_NegotiationInfo SecPkgNegInfo;
   SecPkgContext_Flags SecPkgFlags;

   // Lookup pAS based on Key
   //
   if (!GetEntry (dwKey, (PVOID*) &pAS))
      return(FALSE);

   if (pAS->_fNewConversation)  {
      ss = AcquireCredentialsHandle (
               NULL, // principal
               g_lpPackageName,
               SECPKG_CRED_OUTBOUND,
               NULL, // LOGON id
               NULL, // auth data
               NULL, // get key fn
               NULL, // get key arg
               &pAS->_hcred,
               &Lifetime
               );
      if (SEC_SUCCESS (ss))
         pAS->_fHaveCredHandle = TRUE;
      else {
         fprintf (stderr, "AcquireCreds failed: 0x%08x\n", ss);
         return(FALSE);
      }
   }

   // prepare output buffer
   //
   OutBuffDesc.ulVersion = 0;
   OutBuffDesc.cBuffers = 1;
   OutBuffDesc.pBuffers = &OutSecBuff;

   OutSecBuff.cbBuffer = 0;
   OutSecBuff.BufferType = SECBUFFER_TOKEN;
   OutSecBuff.pvBuffer = NULL;

   // prepare input buffer
   //
   if (!pAS->_fNewConversation)  {
      InBuffDesc.ulVersion = 0;
      InBuffDesc.cBuffers = 1;
      InBuffDesc.pBuffers = &InSecBuff;

      InSecBuff.cbBuffer = cbIn;
      InSecBuff.BufferType = SECBUFFER_TOKEN;
      InSecBuff.pvBuffer = pIn;

      if(g_fVerbose)
      {
         printf ("token buffer recieved(%lu bytes):\n", InSecBuff.cbBuffer);
         PrintHexDump (InSecBuff.cbBuffer, (PBYTE)InSecBuff.pvBuffer);
      }

   }

   // Always have the package allocate the memory
   *pAttribs |= ISC_REQ_ALLOCATE_MEMORY;

   ss = InitializeSecurityContext (
            &pAS->_hcred,
            pAS->_fNewConversation ? NULL : &pAS->_hctxt,
            pszTarget,
            *pAttribs, 
            0, // reserved1
            SECURITY_NATIVE_DREP,
            pAS->_fNewConversation ? NULL : &InBuffDesc,
            0, // reserved2
            &pAS->_hctxt,
            &OutBuffDesc,
            &ContextAttributes,
            &Lifetime
            );

   if (!SEC_SUCCESS (ss))  {
      fprintf (stderr, "InitializeSecurityContext failed: 0x%08x\n", ss);
      return FALSE;
   }

   pAS->_fHaveCtxtHandle = TRUE;

   // Complete token -- if applicable
   //
   if ((SEC_I_COMPLETE_NEEDED == ss) || (SEC_I_COMPLETE_AND_CONTINUE == ss))  {
      ss = CompleteAuthToken (&pAS->_hctxt, &OutBuffDesc);
      if (!SEC_SUCCESS(ss))  {
         fprintf (stderr, "complete failed: 0x%08x\n", ss);
         return FALSE;
      }
   }

   *pcbOut = OutSecBuff.cbBuffer;
   *pOut = (PBYTE)OutSecBuff.pvBuffer;

   if (pAS->_fNewConversation)
      pAS->_fNewConversation = FALSE;

   *pfDone = !((SEC_I_CONTINUE_NEEDED == ss) ||
            (SEC_I_COMPLETE_AND_CONTINUE == ss));

   if(g_fVerbose)
   {
      printf ("token buffer generated (%lu bytes):\n", OutSecBuff.cbBuffer);
      PrintHexDump (OutSecBuff.cbBuffer, (PBYTE)OutSecBuff.pvBuffer);
   }


   if(*pfDone) {

      // find size of signature block
      //
      ss = QueryContextAttributes(
               &pAS->_hctxt,
               SECPKG_ATTR_SIZES,
               &SecPkgContextSizes );

      if (!SEC_SUCCESS(ss))  {
         fprintf (stderr, "QueryContextAttributes failed: 0x%08x\n", ss);
         printf("here");
         return FALSE;
      }

      // these values are used for encryption and signing
      //
      pAS->cbMaxSignature = SecPkgContextSizes.cbMaxSignature;
      pAS->cbSecurityTrailer = SecPkgContextSizes.cbSecurityTrailer;

      // return the attributes we ended up with
      //
      *pAttribs = ContextAttributes;

      // find out what package was negotiated
      //
      ss = QueryContextAttributes(
           &pAS->_hctxt,
           SECPKG_ATTR_NEGOTIATION_INFO,
           &SecPkgNegInfo );

      if (!SEC_SUCCESS(ss))  
      {
         fprintf (stderr, "QueryContextAttributes failed: 0x%08x\n", ss);
         return FALSE;
      }
      else
      {
         printf("Package Name: %s\n", SecPkgNegInfo.PackageInfo->Name);
         // free up the allocated buffer
         // 
         FreeContextBuffer(SecPkgNegInfo.PackageInfo);

      }

      // find out what flags are really used
      //
      ss = QueryContextAttributes(
           &pAS->_hctxt,
           SECPKG_ATTR_FLAGS,
           &SecPkgFlags );

      if (!SEC_SUCCESS(ss))  
      {
         fprintf (stderr, "QueryContextAttributes failed: 0x%08x\n", ss);
         return FALSE;
      }
      else
      {
         printf("FLags: %x\n", SecPkgFlags.Flags);

      }

   }
   
   if(g_fVerbose)
      printf("InitializeSecurityContext result = 0x%08x\n", ss);


   return TRUE;
}

BOOL GenServerContext (
         DWORD dwKey,
         BYTE *pIn,
         DWORD cbIn,
         BYTE **pOut,
         DWORD *pcbOut,
         BOOL *pfDone,
         ULONG *pAttribs)
/*++

 Routine Description:

    Takes an input buffer coming from the client and returns a buffer
   to be sent to the client.  Also returns an indication of whether or
   not the context is complete.

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
   SECURITY_STATUS   ss;
   TimeStamp         Lifetime;
   SecBufferDesc     OutBuffDesc;
   SecBuffer         OutSecBuff;
   SecBufferDesc     InBuffDesc;
   SecBuffer         InSecBuff;
   ULONG             ContextAttributes;
   PAUTH_SEQ         pAS;
   SecPkgContext_Sizes SecPkgContextSizes;
   SecPkgContext_NegotiationInfo SecPkgNegInfo;

   // Lookup pAS based on Key
   //
   if (!GetEntry (dwKey, (PVOID*) &pAS))
      return(FALSE);

   if (pAS->_fNewConversation)  {
      ss = AcquireCredentialsHandle (
               NULL, // principal
               g_lpPackageName,
               SECPKG_CRED_INBOUND,
               NULL, // LOGON id
               NULL, // auth data
               NULL, // get key fn
               NULL, // get key arg
               &pAS->_hcred,
               &Lifetime
               );
      if (SEC_SUCCESS (ss))
         pAS->_fHaveCredHandle = TRUE;
      else {
         fprintf (stderr, "AcquireCreds failed: 0x%08x\n", ss);
         return(FALSE);
      }
   }

   // prepare output buffer
   //
   OutBuffDesc.ulVersion = 0;
   OutBuffDesc.cBuffers = 1;
   OutBuffDesc.pBuffers = &OutSecBuff;

   OutSecBuff.cbBuffer = 0;
   OutSecBuff.BufferType = SECBUFFER_TOKEN;
   OutSecBuff.pvBuffer = NULL;

   // prepare input buffer
   //
   InBuffDesc.ulVersion = 0;
   InBuffDesc.cBuffers = 1;
   InBuffDesc.pBuffers = &InSecBuff;

   InSecBuff.cbBuffer = cbIn;
   InSecBuff.BufferType = SECBUFFER_TOKEN;
   InSecBuff.pvBuffer = pIn;

   if(g_fVerbose)
   {
      printf ("token buffer recieved (%lu bytes):\n", InSecBuff.cbBuffer);
      PrintHexDump (InSecBuff.cbBuffer, (PBYTE)InSecBuff.pvBuffer);
   }

   // Always have the package allocate the memory
   *pAttribs |= ISC_REQ_ALLOCATE_MEMORY;

   ss = AcceptSecurityContext (
            &pAS->_hcred,
            pAS->_fNewConversation ? NULL : &pAS->_hctxt,
            &InBuffDesc,
            *pAttribs, // context requirements
            SECURITY_NATIVE_DREP,
            &pAS->_hctxt,
            &OutBuffDesc,
            &ContextAttributes,
            &Lifetime
            );
   if (!SEC_SUCCESS (ss))  {
      fprintf (stderr, "AcceptSecurityContext failed: 0x%08x\n", ss);
      return FALSE;
   }

   pAS->_fHaveCtxtHandle = TRUE;

   // Complete token -- if applicable
   //
   if ((SEC_I_COMPLETE_NEEDED == ss) || (SEC_I_COMPLETE_AND_CONTINUE == ss))  {
      ss = CompleteAuthToken (&pAS->_hctxt, &OutBuffDesc);
      if (!SEC_SUCCESS(ss))  {
         fprintf (stderr, "complete failed: 0x%08x\n", ss);
         return FALSE;
      }
   }

   *pcbOut = OutSecBuff.cbBuffer;
   *pOut = (PBYTE)OutSecBuff.pvBuffer;

   if (pAS->_fNewConversation)
      pAS->_fNewConversation = FALSE;

   if(g_fVerbose)
   {
      printf ("token buffer generated (%lu bytes):\n", OutSecBuff.cbBuffer);
      PrintHexDump (OutSecBuff.cbBuffer, (PBYTE)OutSecBuff.pvBuffer);
   }


   *pfDone = !((SEC_I_CONTINUE_NEEDED == ss) ||
            (SEC_I_COMPLETE_AND_CONTINUE == ss));

   // find size of token
   //
   if(*pfDone) {

      // find size of signature and trailer blocks
      //
      ss = QueryContextAttributes(
               &pAS->_hctxt,
               SECPKG_ATTR_SIZES,
               &SecPkgContextSizes );

      if (!SEC_SUCCESS(ss))  {
         fprintf (stderr, "QueryContextAttributes failed: 0x%08x\n", ss);
         return FALSE;
      }

      // these values are used for encryption and signing
      //
      pAS->cbMaxSignature = SecPkgContextSizes.cbMaxSignature;
      pAS->cbSecurityTrailer = SecPkgContextSizes.cbSecurityTrailer;

      // return the attributes we ended up with
      //
      *pAttribs = ContextAttributes;

            // find out what package was negotiated
      //
      ss = QueryContextAttributes(
           &pAS->_hctxt,
           SECPKG_ATTR_NEGOTIATION_INFO,
           &SecPkgNegInfo );

      if (!SEC_SUCCESS(ss))  
      {
         fprintf (stderr, "QueryContextAttributes failed: 0x%08x\n", ss);
         return FALSE;
      }
      else
      {
         printf("Package Name: %s\n", SecPkgNegInfo.PackageInfo->Name);

         // free up the allocated buffer
         // 
         FreeContextBuffer(SecPkgNegInfo.PackageInfo);
      }



   }

   if(g_fVerbose)
      printf("AcceptSecurityContext result = 0x%08x\n", ss);

   return TRUE;
}

BOOL ImpersonateContext (DWORD dwKey)
/*++

 Routine Description:

    Impersonates the client whose context is associated with the
   supplied key.

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
   SECURITY_STATUS   ss;
   PAUTH_SEQ         pAS;

   // Lookup pAS based on Key
   //
   if (!GetEntry (dwKey, (PVOID*) &pAS))
      return(FALSE);

   ss = ImpersonateSecurityContext (&pAS->_hctxt);
   if (!SEC_SUCCESS(ss)) {
      fprintf (stderr, "Impersonate failed: 0x%08x\n", ss);
      return(FALSE);
   }

   return(TRUE);
}

BOOL RevertContext (DWORD dwKey)
/*++

 Routine Description:

    Reverts to the original server context.

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
   SECURITY_STATUS   ss;
   PAUTH_SEQ         pAS;

   // Lookup pAS based on Key
   //
   if (!GetEntry (dwKey, (PVOID*) &pAS))
      return(FALSE);

   ss = RevertSecurityContext (&pAS->_hctxt);
   if (!SEC_SUCCESS(ss)) {
      fprintf (stderr, "Revert failed: 0x%08x\n", ss);
      return(FALSE);
   }

   return(TRUE);
}

BOOL EncryptThis (
         DWORD dwKey, 
         PBYTE pMessage, 
         ULONG cbMessage,
         BYTE ** ppOutput,
         ULONG * pcbOutput)
/*++

 Routine Description:

    Encrypts a message

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
   SECURITY_STATUS   ss;
   PAUTH_SEQ         pAS;
   SecBufferDesc     BuffDesc;
   SecBuffer         SecBuff[2];
   ULONG             ulQop = 0;
   ULONG             SigBufferSize;


   // Lookup pAS based on Key
   //
   if (!GetEntry (dwKey, (PVOID*) &pAS))
      return(FALSE);

   // the size of the trailer (signature + padding) block is 
   // determined from this value
   //
   SigBufferSize = pAS->cbSecurityTrailer;

   if(g_fVerbose)
      printf ("data before encryption: %s\n", pMessage);
   
   // allocate a buffer big enough to hold the 
   // signature + encrypted data + a dword that 
   // will tell the other side how big the trailer block is
   //
   * ppOutput = (PBYTE) malloc (SigBufferSize + cbMessage + sizeof(DWORD));

   // prepare buffers
   //
   BuffDesc.ulVersion = 0;
   BuffDesc.cBuffers = 2;
   BuffDesc.pBuffers = SecBuff;

   SecBuff[0].cbBuffer = SigBufferSize;
   SecBuff[0].BufferType = SECBUFFER_TOKEN;
   SecBuff[0].pvBuffer = *ppOutput + sizeof(DWORD);

   SecBuff[1].cbBuffer = cbMessage;
   SecBuff[1].BufferType = SECBUFFER_DATA;
   SecBuff[1].pvBuffer = pMessage;


   ss = EncryptMessage(
      &pAS->_hctxt,
      ulQop,
      &BuffDesc,
      0
      );

   if (!SEC_SUCCESS(ss)) {
      fprintf (stderr, "EncryptMessage failed: 0x%08x\n", ss);
      return(FALSE);
   }

   // indicate in the first DWORD of our output buffer how big 
   // the trailer block is
   //
   *((DWORD *) *ppOutput) = SecBuff[0].cbBuffer;

   // Here we append the encrypted data to our trailer block
   // to form a single block. And yes, it's confusing that we put the trailer
   // in the beginning of our data to send to the client, but it worked out 
   // better that way.
   //
   memcpy (*ppOutput+SecBuff[0].cbBuffer+sizeof(DWORD), pMessage, cbMessage);

   *pcbOutput = cbMessage + SecBuff[0].cbBuffer + sizeof(DWORD);

   if(g_fVerbose)
   {
      printf ("data after encryption including trailer (%lu bytes):\n", *pcbOutput);
      PrintHexDump (*pcbOutput, *ppOutput);
   }

   return TRUE;

}


PBYTE DecryptThis(
          DWORD dwKey, 
          PBYTE pBuffer, 
          LPDWORD pcbMessage)
/*++

 Routine Description:

    Decrypts a message

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
   SECURITY_STATUS   ss;
   PAUTH_SEQ         pAS;
   SecBufferDesc     BuffDesc;
   SecBuffer         SecBuff[2];
   ULONG             ulQop = 0;
   PBYTE             pSigBuffer;
   PBYTE             pDataBuffer;
   DWORD             SigBufferSize;

                  
   // Lookup pAS based on Key
   //
   if (!GetEntry (dwKey, (PVOID*) &pAS))
      return(FALSE);

   // When the server encrypted the message it set the size
   // of the trailer block to be just what it needed. We have to
   // tell DecryptMessage how big the trailer block turned out to be,
   // so we sent the size of the trailer as the first dword of the 
   // message. 
   //
   SigBufferSize = *((DWORD *) pBuffer);

   if(g_fVerbose)
   {
      printf ("data before decryption including trailer (%lu bytes):\n", *pcbMessage);
      PrintHexDump (*pcbMessage, (PBYTE) pBuffer);
   }

   // we know the trailer is at the beginning of the blob
   // but after the trailer size dword
   //
   pSigBuffer = pBuffer + sizeof(DWORD);

   // and that the data is after the trailer
   //
   pDataBuffer = pSigBuffer + SigBufferSize;

   // reset the size of the data to reflect just the encrypted blob
   //
   *pcbMessage = *pcbMessage - SigBufferSize - sizeof(DWORD);

   // prepare buffer
   //
   BuffDesc.ulVersion = 0;
   BuffDesc.cBuffers = 2;
   BuffDesc.pBuffers = SecBuff;

   SecBuff[0].cbBuffer = SigBufferSize;
   SecBuff[0].BufferType = SECBUFFER_TOKEN;
   SecBuff[0].pvBuffer = pSigBuffer;

   SecBuff[1].cbBuffer = *pcbMessage;
   SecBuff[1].BufferType = SECBUFFER_DATA;
   SecBuff[1].pvBuffer = pDataBuffer;

   ss = DecryptMessage(
      &pAS->_hctxt,
      &BuffDesc,
      0,
      &ulQop
      );

   if (!SEC_SUCCESS(ss)) {
      fprintf (stderr, "DecryptMessage failed: 0x%08x\n", ss);
      return(FALSE);
   }

   // only return a pointer to the data which we decrypted - 
   // discard the trailer data
   return pDataBuffer;

}

BOOL SignThis (
         DWORD dwKey, 
         PBYTE pMessage, 
         ULONG cbMessage,
         BYTE ** ppOutput,
         LPDWORD pcbOutput)

/*++

 Routine Description:

    Signs a message

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
   SECURITY_STATUS   ss;
   PAUTH_SEQ         pAS;
   SecBufferDesc     BuffDesc;
   SecBuffer         SecBuff[2];
   ULONG             ulQop = 0;
   PBYTE             pSigBuffer;
   DWORD             SigBufferSize;


   // Lookup pAS based on Key
   //
   if (!GetEntry (dwKey, (PVOID*) &pAS))
      return(FALSE);

   // the size of the signature block is determined from this value
   //
   SigBufferSize = pAS->cbMaxSignature;
 
   // for reasons apparent later, we are going to allocate
   // a buffer big enough to hold the signature + signed data
   pSigBuffer = (PBYTE) malloc (SigBufferSize + cbMessage);

   // prepare buffers
   //
   BuffDesc.ulVersion = 0;
   BuffDesc.cBuffers = 2;
   BuffDesc.pBuffers = SecBuff;

   SecBuff[0].cbBuffer = SigBufferSize;
   SecBuff[0].BufferType = SECBUFFER_TOKEN;
   SecBuff[0].pvBuffer = pSigBuffer;

   SecBuff[1].cbBuffer = cbMessage;
   SecBuff[1].BufferType = SECBUFFER_DATA;
   SecBuff[1].pvBuffer = pMessage;

   ss = MakeSignature(
      &pAS->_hctxt,
      ulQop,
      &BuffDesc,
      0
      );

   if (!SEC_SUCCESS(ss)) {
      fprintf (stderr, "MakeSignature failed: 0x%08x\n", ss);
      return(FALSE);
   }

   // here we append the signed data to our signature block
   // and also reducing the size of our signature buffer if
   // the package did not use the size that we provided
   //
   memcpy (pSigBuffer+SecBuff[0].cbBuffer, pMessage, cbMessage);

   // point the data buffer to our new blob and reset the size
   //
   *ppOutput = pSigBuffer;

   *pcbOutput = cbMessage + SecBuff[0].cbBuffer;

   if(g_fVerbose)
   {
      printf ("data after signing including signature (%lu bytes):\n", *pcbOutput);
      PrintHexDump (*pcbOutput, *ppOutput);
   }

   return TRUE;

}


PBYTE VerifyThis(
          DWORD   dwKey, 
          PBYTE   pBuffer, 
          LPDWORD pcbMessage)
/*++

 Routine Description:

    Decrypts a message

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
   SECURITY_STATUS   ss;
   PAUTH_SEQ         pAS;
   SecBufferDesc     BuffDesc;
   SecBuffer         SecBuff[2];
   ULONG             ulQop = 0;
   PBYTE             pSigBuffer;
   PBYTE             pDataBuffer;
   DWORD             SigBufferSize;
                  
   // Lookup pAS based on Key
   //
   if (!GetEntry (dwKey, (PVOID*) &pAS))
      return(FALSE);

   // the size of the signature block is determined from this value
   //
   SigBufferSize = pAS->cbMaxSignature;

   if(g_fVerbose)
   {
      printf ("data before verifying (including signature):\n");
      PrintHexDump (*pcbMessage, pBuffer);
   }
   // we know the signature is at the beginning of the blob
   //
   pSigBuffer = pBuffer;

   // and that the data is after the signature
   //
   pDataBuffer = pBuffer + SigBufferSize;

   // reset the size of the data to reflect just the data
   //
   *pcbMessage = *pcbMessage - (SigBufferSize);

   // prepare buffer
   //
   BuffDesc.ulVersion = 0;
   BuffDesc.cBuffers = 2;
   BuffDesc.pBuffers = SecBuff;

   SecBuff[0].cbBuffer = SigBufferSize;
   SecBuff[0].BufferType = SECBUFFER_TOKEN;
   SecBuff[0].pvBuffer = pSigBuffer;

   SecBuff[1].cbBuffer = *pcbMessage;
   SecBuff[1].BufferType = SECBUFFER_DATA;
   SecBuff[1].pvBuffer = pDataBuffer;

   ss = VerifySignature(
      &pAS->_hctxt,
      &BuffDesc,
      0,
      &ulQop
      );

   if (!SEC_SUCCESS(ss)) {
      fprintf (stderr, "VerifyMessage failed: 0x%08x\n", ss);
      return(FALSE);
   }
   else
      printf("Message was properly signed.\n");

   return pDataBuffer;

}


BOOL InitSession (DWORD dwKey)
/*++

 Routine Description:

    Initializes the context associated with a key and adds it to the
   collection.

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
   PAUTH_SEQ pAS;

   pAS = (PAUTH_SEQ) malloc (sizeof (AUTH_SEQ));
   if (NULL == pAS)
      return(FALSE);

   pAS->_fNewConversation = TRUE;
   pAS->_fHaveCredHandle = FALSE;
   pAS->_fHaveCtxtHandle = FALSE;
      
   if (!AddEntry (dwKey, (PVOID)pAS))  {
      free (pAS);
      return(FALSE);
   }

   return(TRUE);
}

BOOL TermSession (DWORD dwKey)
/*++

 Routine Description:

    Releases the resources associated with a key and removes it from
   the collection.

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
   PAUTH_SEQ pAS;

   if (!DeleteEntry (dwKey, (LPVOID*)&pAS))  
      return(FALSE);

   if (pAS->_fHaveCtxtHandle)
      DeleteSecurityContext (&pAS->_hctxt);

   if (pAS->_fHaveCredHandle)
      FreeCredentialHandle (&pAS->_hcred);

   free (pAS);
   
   return(TRUE);
}  

void PrintHexDump(DWORD length, PBYTE buffer)
{
   DWORD i,count,index;
   CHAR rgbDigits[]="0123456789abcdef";
   CHAR rgbLine[100];
   char cbLine;

   for(index = 0; length; length -= count, buffer += count, index += count) 
   {
      count = (length > 16) ? 16:length;

      sprintf(rgbLine, "%4.4x  ",index);
      cbLine = 6;

      for(i=0;i<count;i++) 
      {
         rgbLine[cbLine++] = rgbDigits[buffer[i] >> 4];
         rgbLine[cbLine++] = rgbDigits[buffer[i] & 0x0f];
         if(i == 7) 
         {
            rgbLine[cbLine++] = ':';
         } 
         else 
         {
            rgbLine[cbLine++] = ' ';
         }
      }
      for(; i < 16; i++) 
      {
         rgbLine[cbLine++] = ' ';
         rgbLine[cbLine++] = ' ';
         rgbLine[cbLine++] = ' ';
      }

      rgbLine[cbLine++] = ' ';

      for(i = 0; i < count; i++) 
      {
         if(buffer[i] < 32 || buffer[i] > 126) 
         {
            rgbLine[cbLine++] = '.';
         } 
         else 
         {
            rgbLine[cbLine++] = buffer[i];
         }
      }

      rgbLine[cbLine++] = 0;
      printf("%s\n", rgbLine);
   }
}

