PropCert illustrates how to propagate a digital certificate from a
smart card to the local "My" store. A digital certificate needs to be
in the local "My" store in order for an application, such as Internet
Explorer, to use the certificate for authentication or other
cryptographic operations.

Note that the API, SCardGetCardTypeProviderName, is used in this
sample to locate the CSP for the corresponding card. This API is only
available in Windows 2000 Beta 2 or above.  That means this sample will
not run with smart card base component v1.0 which is used in Win9x and
NT 4 platforms. To get around this problem, one can hardcode the CSP
name instead of depending on using SCardGetCardTypeProviderName to
locate the CSP for the card in question.

If you get an error claiming that the symbol SCardGetCardTypeProviderName
is not defined, then you are linking against an older version of the
winscard.lib library.

Fully qualified container names were first implemented in
Windows 2000 Beta 2, and may not be available in CSPs built for
previous Windows platforms.  Substituting NULL for a conatiner name
indicates the default container.

Files included in this sample
=============================

1) ReadMe.txt   - This file
2) PropCert.cpp - Main program
3) MAKEFILE     - Makefile for NMAKE utility

SCard functions used in this sample
===================================

- SCardEstablishContext
- SCardListReaders
- SCardFreeMemory
- SCardReleaseContext
- SCardGetStatusChange
- SCardListCards
- SCardGetCardTypeProviderName

Crypto functions used in this sample
====================================

- CryptAcquireContext
- CryptReleaseContex
- CryptGetProvParam
- CryptGetUserKey
- CryptGetKeyParam
- CryptDestroyKey

Cert functions used in this sample
==================================

- CertOpenStore
- CertCreateCertificateContext
- CertSetCertificateContextProperty
- CertAddCertificateContextToStore
- CertFreeCertificateContext
- CertCloseStore

How to compile
==============

1) Make sure all smart card hardware and software components have been setup
   correctly per %MSSDK%\Samples\Winbase\SCard\ReadMe.txt.
2) From the PropCert directory, run NMAKE to make PropCert.exe.

See %MSSDK%\ReadMe.txt for more information.

