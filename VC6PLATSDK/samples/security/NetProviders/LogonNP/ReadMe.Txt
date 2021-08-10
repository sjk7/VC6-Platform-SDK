THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998-1999.  Microsoft Corporation.  All rights reserved.


Sample:  LogonNP.DLL

Purpose: This Windows NT Sample Network provider implements a small
   subsection of the NP interface. What it shows is how you can
   sample logon information when a logon is performed.
   This "credential sampling" is often useful for implementing
   unified logons with differing OS platforms. Once you gather
   the information in the NP, you can then communicate the
   credentials to another platform for verification and
   establishment of network resources.

Not covered: This sample does not implement the complete Network
   Provider interface. For complete documentation of the Windows
   NT Network Provider Interface, see the Windows NT DDK and
   NTNP.DOC.

Caution: Since this sample shows how to easily gather user
   credentials, including user names and passwords, extreme
   care should be taken to insure adequate safeguards
   are in place for any information gathered.

Platform: Windows NT only

Once the LogonNP.dll file is built, there are a couple of things
that need to be done to install it.

 - Copy LogonNP.dll to %SystemRoot%\system32.   This is not
    strictly necessary, but it's consistent.

 - Add a "LogonNP" subkey to the\HKEY_LOCAL_MACHINE\SYSTEM\
    CurrentControlSet\Services key.

 - Add a "networkprovider" subkey to the LogonNP key.

 - Add the following values to the "networkprovider" key:

    Value Name      Type            Value
    ----------      --------        ---------
    Class           REG_DWORD       2
    Name            REG_SZ          Logon Network Provider
    ProviderPath    REG_EXPAND_SZ   %SystemRoot%\system32\logonnp.dll

    The name is just for display purposes, so it's flexible.

 - Add "LogonNP" to the ProviderOrder list in the \HKEY_LOCAL_MACHINE\
    SYSTEM\CurrentControlSet\Control\NetworkProvider\Order key.
    (The list is comma separated).



