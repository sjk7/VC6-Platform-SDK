//////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (C) 1999 - 2000  Microsoft Corporation.  All rights reserved.
//
//  NullDacl.cpp
//
//      Provides functions to allocate and free a SECURITY_DESCRIPTOR
//      with a NULL DACL
//
//////////////////////////////////////////////////////////////////////


#include "Cleanup.h"
#include <sddl.h>
#include <accctrl.h>
#include <aclapi.h>

#if _WIN32_WINNT >= 0x0500
PSECURITY_DESCRIPTOR WINAPI CreateDacl(void)
{
    OSVERSIONINFO           osvi    = {0};
    PSECURITY_DESCRIPTOR    psd     = NULL;
    static WCHAR *pwszSD=L"D:(A;OICI;GA;;;SY)(A;OICI;GA;;;BA)(A;OICI;GA;;;CO)(A;OICI;GRGWGX;;;IU)";

    //
    //  Get the OS version info. If not on NT, return NULL
    //
    osvi.dwOSVersionInfoSize    = sizeof (OSVERSIONINFO);
    GetVersionEx (&osvi);
    if (osvi.dwPlatformId != VER_PLATFORM_WIN32_NT)
    {
        SetLastError (NOERROR);
	goto err;
    }

    //
    //  Allocate memory for the security descriptor
    //

    ConvertStringSecurityDescriptorToSecurityDescriptorW(pwszSD,
							SDDL_REVISION_1, 
							&psd, 
							NULL);
 err:
    return psd;
}

#elif _WIN32_WINNT >= 0x0400
PSECURITY_DESCRIPTOR CreateDacl(void)
{

  // ACL creates two ACES - Everyone (R) and Administrator (FC)
  
  DWORD dwRes;
  PSID pEveryoneSID = NULL, pAdminSID = NULL;
  PACL pACL = NULL;
  PSECURITY_DESCRIPTOR pSD = NULL;
  EXPLICIT_ACCESS ea[2];
  SID_IDENTIFIER_AUTHORITY SIDAuthWorld = SECURITY_WORLD_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY SIDAuthNT = SECURITY_NT_AUTHORITY;
  HKEY hkSub = NULL;
  
  // Create a well-known SID for the Everyone group.
  
  if(! AllocateAndInitializeSid( &SIDAuthWorld, 1,
				 SECURITY_WORLD_RID,
				 0, 0, 0, 0, 0, 0, 0,
				 &pEveryoneSID) ) {
    goto Cleanup;
  }
  
  // Initialize an EXPLICIT_ACCESS structure for an ACE.
  // The ACE will allow Everyone read access to the key.
  
  ZeroMemory(&ea, 2 * sizeof(EXPLICIT_ACCESS));
  ea[0].grfAccessPermissions = KEY_READ;
  ea[0].grfAccessMode = SET_ACCESS;
  ea[0].grfInheritance= NO_INHERITANCE;
  ea[0].Trustee.TrusteeForm = TRUSTEE_IS_SID;
  ea[0].Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
  ea[0].Trustee.ptstrName  = (LPTSTR) pEveryoneSID;
  
  // Create a SID for the BUILTIN\Administrators group.
  
  if(! AllocateAndInitializeSid( &SIDAuthNT, 2,
				 SECURITY_BUILTIN_DOMAIN_RID,
				 DOMAIN_ALIAS_RID_ADMINS,
				 0, 0, 0, 0, 0, 0,
				 &pAdminSID) ) {
    goto Cleanup; 
  }
  
  // Initialize an EXPLICIT_ACCESS structure for an ACE.
  // The ACE will allow the Administrators group full access to the key.
  
  ea[1].grfAccessPermissions = KEY_ALL_ACCESS;
  ea[1].grfAccessMode = SET_ACCESS;
  ea[1].grfInheritance= NO_INHERITANCE;
  ea[1].Trustee.TrusteeForm = TRUSTEE_IS_SID;
  ea[1].Trustee.TrusteeType = TRUSTEE_IS_GROUP;
  ea[1].Trustee.ptstrName  = (LPTSTR) pAdminSID;
  
  // Create a new ACL that contains the new ACEs.
  
  dwRes = SetEntriesInAcl(2, ea, NULL, &pACL);
  if (ERROR_SUCCESS != dwRes) {
    goto Cleanup;
  }
  
  // Initialize a security descriptor.  
  
  pSD = (PSECURITY_DESCRIPTOR) LocalAlloc(LPTR, 
					  SECURITY_DESCRIPTOR_MIN_LENGTH); 
  if (pSD != NULL) { 
    if (InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION)) {  
  
      // Add the ACL to the security descriptor. 
      
      if (SetSecurityDescriptorDacl(pSD, 
				    TRUE,     // fDaclPresent flag   
				    pACL, 
				    FALSE))   // not a default DACL 
	{  
	  return pSD;
	} 
    }
  }
  
  
  
 Cleanup:
  
  if (pEveryoneSID) 
    FreeSid(pEveryoneSID);
  if (pAdminSID) 
    FreeSid(pAdminSID);
  if (pACL) 
        LocalFree(pACL);
  if (pSD) 
    LocalFree(pSD);

  return NULL;

}
#endif
